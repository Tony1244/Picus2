#include "Triggerbot.h"

using namespace Client;

#pragma warning(disable:4244)
//[junk_enable /]
CTriggerbot::CTriggerbot()
{
	m_pLocal = nullptr;
	m_pCmd = nullptr;

	iPreFov = 0;
	iTriggerShotsFired = 0;
	bTrigger = false;
	bAssist = false;
	bFovTime = false;
	bIsZoomSniper = false;
	bTriggerAttack = false;
	dwTriggerStatusTime = 0;

	m_pTriggerDelayBefore = new CTimer();
	m_pTriggerDelayAfter = new CTimer();
}

void CTriggerbot::LeftClick()
{
	INPUT    Input;
	memset(&Input, 0, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
	memset(&Input, 0, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &Input, sizeof(INPUT));
}

void CTriggerbot::RightClick()
{
	INPUT    Input;
	memset(&Input, 0, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
	memset(&Input, 0, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &Input, sizeof(INPUT));
}

bool CTriggerbot::IsEnable()
{
	if (!m_pLocal || !m_pCmd)
		return false;

	if (Settings::Triggerbot::trigger_Enable == false)
		return false;

	if (!m_pLocal->WeaponAmmo || m_pLocal->bInReload)
		return false;

	if (m_pLocal->WeaponType > WEAPON_TYPE_SNIPER)
		return false;

	return true;
}

void CTriggerbot::TriggerShow(CPlayer * pPlayer)
{
	if (!IsEnable())
		return;

	if (Settings::Triggerbot::trigger_Enable)
	{
		if (m_pLocal->WeaponType < WEAPON_TYPE_GRENADE && TriggerCheckTeam(pPlayer))
		{
			if (Settings::Triggerbot::trigger_DrawFov && Settings::Triggerbot::trigger_Enable <= 1)
				TriggerShowFov(pPlayer);

			if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist && Settings::Triggerbot::trigger_DrawFovAssist)
				TriggerShowAssistFov(pPlayer);

			if (Settings::Triggerbot::trigger_DrawSpot && Settings::Triggerbot::trigger_Enable <= 1)
			{
				if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly)
				{
					g_pRender->DrawBox(pPlayer->vTriggerHeadPos.x, pPlayer->vTriggerHeadPos.y, 2, 2, Color::White());
				}
				else
				{
					g_pRender->DrawBox(pPlayer->vTriggerHeadPos.x, pPlayer->vTriggerHeadPos.y, 2, 2, Color::White());
					g_pRender->DrawBox(pPlayer->vTriggerChestPos.x, pPlayer->vTriggerChestPos.y, 2, 2, Color::White());
				}
			}
			else if (Settings::Triggerbot::trigger_DrawSpot && Settings::Triggerbot::trigger_Enable >= 2)
			{
				g_pRender->DrawBox(pPlayer->vTriggerHeadPos.x, pPlayer->vTriggerHeadPos.y, 2, 2, Color::White());

				if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HitGroup <= 1)
					g_pRender->DrawBox(pPlayer->vTriggerChestPos.x, pPlayer->vTriggerChestPos.y, 2, 2, Color::White());
			}
		}
	}
}

void CTriggerbot::TriggerShowFov(CPlayer * pPlayer)
{
	if (pPlayer->vTriggerHeadPos.x > 0.f)
	{
		int iHeadX = (int)pPlayer->vTriggerHeadPos.x;
		int iHeadY = (int)pPlayer->vTriggerHeadPos.y;

		int iHeadFov = GetTriggerHeadFov(pPlayer);

		if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly)
		{
			g_pRender->DrawBox(iHeadX - iHeadFov, iHeadY - iHeadFov, iHeadFov * 2, iHeadFov * 2, Color(30, 255, 30));
		}
		else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly == false && pPlayer->vTriggerChestPos.x > 0.f)
		{
			int iChestX = (int)pPlayer->vTriggerChestPos.x;
			int iChestY = (int)pPlayer->vTriggerChestPos.y;

			int iChestFovX = GetTriggerChestFovX(pPlayer);
			int iChestFovY = GetTriggerChestFovY(pPlayer);

			g_pRender->DrawBox(iHeadX - iHeadFov, iHeadY - iHeadFov, iHeadFov * 2, iHeadFov * 2, Color(255, 30, 255));
			g_pRender->DrawBox(iChestX - iChestFovX, iChestY - iChestFovY, iChestFovX * 2, iChestFovY * 2, Color(255, 30, 255));
		}
	}
}

void CTriggerbot::TriggerShowAssistFov(CPlayer * pPlayer)
{
	if (pPlayer->vTriggerHeadPos.x > 0.f)
	{
		int iHeadX = (int)pPlayer->vTriggerHeadPos.x;
		int iHeadY = (int)pPlayer->vTriggerHeadPos.y;

		int iHeadFov = GetTriggerAssistHeadFov(pPlayer);

		if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType <= 0)
		{
			if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly)
			{
				g_pRender->DrawBox(iHeadX - iHeadFov, iHeadY - iHeadFov, iHeadFov * 2, iHeadFov * 2, Color(255, 230, 0));
			}
			else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly == false && pPlayer->vTriggerChestPos.x > 0.f)
			{
				int iChestX = (int)pPlayer->vTriggerChestPos.x;
				int iChestY = (int)pPlayer->vTriggerChestPos.y;

				int iChestFovX = GetTriggerAssistChestFovX(pPlayer);
				int iChestFovY = GetTriggerAssistChestFovY(pPlayer);

				g_pRender->DrawBox(iHeadX - iHeadFov, iHeadY - iHeadFov, iHeadFov * 2, iHeadFov * 2, Color(255, 230, 0));
				g_pRender->DrawBox(iChestX - iChestFovX, iChestY - iChestFovY, iChestFovX * 2, iChestFovY * 2, Color(255, 230, 0));
			}
		}
		else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType >= 1)
		{
			g_pRender->DrawBox(g_vCenterScreen.x - iHeadFov, g_vCenterScreen.y - iHeadFov, iHeadFov * 2, iHeadFov * 2, Color(255, 230, 0));
		}
	}
}

int CTriggerbot::GetTriggerHeadFov(CPlayer * pPlayer)
{
	int iFov = 0;

	iFov = (int)((pow(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Fov + FIX_MIN_FOV_HEAD, 2) * 90) / (pPlayer->iDistance * m_pLocal->iFov));

	return iFov;
}

int CTriggerbot::GetTriggerChestFovX(CPlayer * pPlayer)
{
	return (int)((pow(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Fov + FIX_MIN_FOV_CHEST, 2) * 90) / (pPlayer->iDistance * m_pLocal->iFov));
}

int CTriggerbot::GetTriggerChestFovY(CPlayer * pPlayer)
{
	return (int)((pow((Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Fov + FIX_MIN_FOV_CHEST) * 1.25, 2) * 90) / (pPlayer->iDistance * m_pLocal->iFov));
}

int CTriggerbot::GetTriggerAssistHeadFov(CPlayer * pPlayer)
{
	int iFov = 0;

	if (Settings::Triggerbot::trigger_Enable <= 2)
	{
		if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType <= 0)
		{
			iFov = ((pow(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Fov + Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov + FIX_MIN_FOV_HEAD, 2) * 90) / (pPlayer->iDistance * m_pLocal->iFov));
		}
		else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType >= 1)
		{
			iFov = ((pow(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov + FIX_MIN_FOV_HEAD, 2) * 90) / (FOV_BASE_DISTANCE * m_pLocal->iFov));
		}
	}
	else
	{
		if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType <= 0)
		{
			iFov = ((pow(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov + FIX_MIN_FOV_HEAD, 2) * 90) / (pPlayer->iDistance * m_pLocal->iFov));
		}
		else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType >= 1)
		{
			iFov = ((pow(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov + FIX_MIN_FOV_HEAD, 2) * 90) / (FOV_BASE_DISTANCE * m_pLocal->iFov));
		}
	}

	return iFov;
}

int CTriggerbot::GetTriggerAssistChestFovX(CPlayer * pPlayer)
{
	int iFov = 0;

	if (Settings::Triggerbot::trigger_Enable <= 2)
	{
		iFov = ((pow(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Fov + Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov + FIX_MIN_FOV_CHEST, 2) * 90) / (pPlayer->iDistance * m_pLocal->iFov));
	}
	else
	{
		iFov = ((pow(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov + FIX_MIN_FOV_CHEST, 2) * 90) / (pPlayer->iDistance * m_pLocal->iFov));
	}

	return iFov;
}

int CTriggerbot::GetTriggerAssistChestFovY(CPlayer * pPlayer)
{
	int iFov = 0;

	if (Settings::Triggerbot::trigger_Enable <= 2)
	{
		iFov = ((pow((Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Fov + Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov + FIX_MIN_FOV_CHEST) * 1.25, 2) * 90) / (pPlayer->iDistance * m_pLocal->iFov));
	}
	else
	{
		iFov = ((pow((Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov + FIX_MIN_FOV_CHEST) * 1.25, 2) * 90) / (pPlayer->iDistance * m_pLocal->iFov));
	}

	return iFov;
}

void CTriggerbot::TriggerShowStatus()
{
	if (Settings::Triggerbot::trigger_Enable)
	{
		if (Settings::Triggerbot::trigger_KeyMode >= 1)
		{
			if (GetTickCount64() - dwTriggerStatusTime < 1000)
			{
				con_nprint_t print;
				print.index = 1;
				print.fixed_width_font = false;
				print.time_to_live = 1;

				if (bTrigger)
				{
					print.color[0] = 0.f;
					print.color[1] = 1.f;
					print.color[2] = 0.f;

					Interfaces::Engine()->Con_NXPrintf(&print, "%s", CVAR_TRIGGER_ENABLED);
				}
				else
				{
					print.color[0] = 1.f;
					print.color[1] = 0.f;
					print.color[2] = 0.f;

					Interfaces::Engine()->Con_NXPrintf(&print, "%s", CVAR_TRIGGER_DISABLED);
				}
			}
		}
		else if (bTrigger)
		{
			g_pRender->Text(iScreenWidth / 2, 65, true, true, Color(0, 255, 0), "%s", CVAR_TRIGGER_ENABLED);
		}
	}
}

bool CTriggerbot::TriggerCheckTeam(CPlayer * pPlayer)
{
	bool CheckTeam = false;
	bool CheckVis = false;

	// ������ �������� ������ ��:
	if (Settings::Triggerbot::trigger_Deathmatch == false && m_pLocal->Team != pPlayer->Team) // �����������
	{
		CheckTeam = true;
	}
	else if (Settings::Triggerbot::trigger_Deathmatch) // �� ����
	{
		CheckTeam = true;
	}

	if (Settings::Triggerbot::trigger_WallAttack)
	{
		CheckVis = true;
	}
	else if (!Settings::Triggerbot::trigger_WallAttack && pPlayer->bVisible)
	{
		CheckVis = true;
	}

	return (CheckTeam && CheckVis);
}

bool CTriggerbot::CheckPlayerTriggerLine(CPlayer * pPlayer)
{
	trace_t tr;
	Ray_t ray;
	Vector vAngle;
	CTraceFilter filter;

	if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist)
	{
		vAngle.x = m_pCmd->viewangles.x;
		vAngle.y = m_pCmd->viewangles.y;
	}
	else
	{
		vAngle.x = m_pCmd->viewangles.x + (m_pLocal->vAimPunch.x * 2);
		vAngle.y = m_pCmd->viewangles.y + (m_pLocal->vAimPunch.y * 2);
	}

	Vector	vecStart, vecStop, vecFor;

	AngleVectors(vAngle, vecFor);

	CWeaponInfo* Weapon = m_pLocal->m_pWeaponEntity->GetWeaponInfo();

	if (Weapon)
	{
		vecFor *= Weapon->m_flRange;
	}
	else
	{
		vecFor *= 8192.0f;
	}

	filter.pSkip = m_pLocal->m_pEntity;

	vecStart = m_pLocal->vEyeOrigin;
	vecStop = vecStart + vecFor;

	ray.Init(vecStart, vecStop);

	Interfaces::EngineTrace()->TraceRay(ray, PlayerVisibleMask, &filter, &tr);

	bool didHit = false;

	if (Settings::Triggerbot::trigger_Enable == 1)
	{
		didHit = true;
	}
	else if (Settings::Triggerbot::trigger_Enable >= 2)
	{
		int hitgroup = tr.hitgroup;

		if ((hitgroup == HITGROUP_CHEST || hitgroup == HITGROUP_HEAD || hitgroup == HITGROUP_STOMACH) && Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HitGroup == 1)
		{
			didHit = true;
		}
		else if (hitgroup == HITGROUP_HEAD && Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HitGroup >= 2)
		{
			didHit = true;
		}
		else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HitGroup <= 0 && hitgroup >= 1 && hitgroup <= 7)
		{
			didHit = true;
		}
	}

	if (tr.m_pEnt == pPlayer->m_pEntity && didHit)
		return true;

	return false;
}

byte CTriggerbot::GetCountPlayerAssistFov()
{
	byte cnt = 0;

	for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

		if (pPlayer && pPlayer->bUpdate && pPlayer->bAssistFov)
			cnt++;
	}

	return cnt;
}

bool CTriggerbot::CheckPlayerTriggerPos()
{
	for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

		if (pPlayer && pPlayer->bUpdate && pPlayer->bTriggerFov)
			return true;
	}

	return false;
}

bool CTriggerbot::CheckPlayerAssistTriggerPos()
{
	for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

		if (pPlayer && pPlayer->bUpdate && pPlayer->bAssistFov)
			return true;
	}

	return false;
}

void CTriggerbot::TriggerAssistSet(Vector vAimAssist)
{
	Vector vAimAngle, vAimAssistAngle;
	Vector vSmoothAimAssistAngles;

	vAimAngle = vAimAssist - m_pLocal->vEyeOrigin;

	if (vAimAngle.IsValid())
	{
		VectorAngles(vAimAngle, vAimAssistAngle);

		if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistRcs)
		{
			vAimAssistAngle.x -= m_pLocal->vAimPunch.x * (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistRcs * 0.02);
			vAimAssistAngle.y -= m_pLocal->vAimPunch.y * (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistRcs * 0.02);
		}

		float fSmooth = 10.f;

		fSmooth = Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistSmooth;

		if (fSmooth <= 10.f)
		{
			fSmooth = 10.f;
		}
		else
		{
			fSmooth = fSmooth / 10.f;
		}

		AngleNormalize(vAimAssistAngle);

		SmoothAngles(m_pCmd->viewangles, vAimAssistAngle, vSmoothAimAssistAngles, fSmooth);

		m_pCmd->viewangles = vSmoothAimAssistAngles;
	}
}

void CTriggerbot::TriggerAssistUpd(Vector vAimAssist)
{
	if ((m_pLocal->WeaponType == WEAPON_TYPE_PISTOL || m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN))
	{
		TriggerAssistSet(vAimAssist);
	}
	else if (m_pLocal->WeaponType == WEAPON_TYPE_SNIPER)
	{
		if (Settings::Triggerbot::trigger_FastZoom)
		{
			TriggerAssistSet(vAimAssist);
		}
		else if (!Settings::Triggerbot::trigger_FastZoom && bIsZoomSniper)
		{
			TriggerAssistSet(vAimAssist);
		}
		else if (!Settings::Triggerbot::trigger_FastZoom && !bIsZoomSniper)
		{
			return;
		}
	}
}

void CTriggerbot::TriggerAssist(CPlayer * pPlayer)
{
	if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist)
	{
		// ���� ����� 1 � �� �� �������� � �� � ���� ������ ������ � ����� �������� �� �������� ���
		if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist == 1 && !CheckPlayerAssistTriggerPos() && !(m_pCmd->buttons & IN_ATTACK) && iTriggerShotsFired == 0)
		{
			if (!bAssist)
				bAssist = true;
		}

		float fScreenDist = 1000.f;

		byte bCountPlayerAssistFov = GetCountPlayerAssistFov();

		if (pPlayer->bAssistFov)
		{
			if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist == 1 && (m_pCmd->buttons & IN_ATTACK))
			{
				bAssist = false;
			}
			else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist >= 2)
			{
				bAssist = true;
			}

			if (pPlayer->vAssistTriggerHead.IsValid() && pPlayer->vAssistTriggerChest.IsValid() && bAssist)
			{
				if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly)
				{
					if (bCountPlayerAssistFov >= 2)
					{
						byte bTargetAssist = 0;

						for (byte p = 0; p < ABSOLUTE_PLAYER_LIMIT; p++)
						{
							if (g_pPlayers->GetPlayer(p)->bAssistFov)
							{
								if (g_pPlayers->GetPlayer(p)->fDistanceHead < fScreenDist)
								{
									fScreenDist = g_pPlayers->GetPlayer(p)->fDistanceHead;
									bTargetAssist = p;
								}
							}
						}

						TriggerAssistUpd(g_pPlayers->GetPlayer(bTargetAssist)->vAssistTriggerHead);
					}
					else
					{
						TriggerAssistUpd(pPlayer->vAssistTriggerHead);
					}
				}
				else
				{
					if (bCountPlayerAssistFov >= 2)
					{
						byte bTargetAssist = 0;
						byte bTargetAssistType = 0;

						Vector vAimAssist = Vector(0, 0, 0);

						for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
						{
							CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

							if (pPlayer && pPlayer->bUpdate && pPlayer->bAssistFov)
							{
								if (g_pPlayers->GetPlayer(PlayerIndex)->fDistanceHead < fScreenDist && g_pPlayers->GetPlayer(PlayerIndex)->fDistanceHead < g_pPlayers->GetPlayer(PlayerIndex)->fDistanceChest)
								{
									fScreenDist = g_pPlayers->GetPlayer(PlayerIndex)->fDistanceHead;
									bTargetAssist = PlayerIndex;
									bTargetAssistType = 1;
								}
								else if (g_pPlayers->GetPlayer(PlayerIndex)->fDistanceChest < fScreenDist && g_pPlayers->GetPlayer(PlayerIndex)->fDistanceChest < g_pPlayers->GetPlayer(PlayerIndex)->fDistanceHead)
								{
									fScreenDist = g_pPlayers->GetPlayer(PlayerIndex)->fDistanceChest;
									bTargetAssist = PlayerIndex;
									bTargetAssistType = 2;
								}
							}
						}

						if (bTargetAssistType == 1)
						{
							vAimAssist = g_pPlayers->GetPlayer(bTargetAssist)->vAssistTriggerHead;
						}
						else if (bTargetAssistType == 2)
						{
							vAimAssist = g_pPlayers->GetPlayer(bTargetAssist)->vAssistTriggerChest;
						}

						TriggerAssistUpd(vAimAssist);
					}
					else
					{
						Vector vAimAssist = Vector(0, 0, 0);

						if (pPlayer->fDistanceHead < pPlayer->fDistanceChest)
						{
							vAimAssist = pPlayer->vAssistTriggerHead;
						}
						else if (pPlayer->fDistanceChest < pPlayer->fDistanceHead)
						{
							vAimAssist = pPlayer->vAssistTriggerChest;
						}

						TriggerAssistUpd(vAimAssist);
					}
				}

				// ����� 1, ���� �� ��������� 1 ��� � ������� ��� ������ ������� �� ������� �������� ����� ��������� �����
				// �� 2 ������ ������ ����� �������� 
				if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist == 1 && pPlayer->bTriggerFov && iTriggerShotsFired)
					bAssist = false;
			}
		}
	}
}

void CTriggerbot::TriggerAttack()
{
	bool bShotTrigger = false;

	if (iTriggerShotsFired <= 0)
	{
		if (m_pTriggerDelayBefore->delay(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DelayBefore))
		{
			bShotTrigger = true;
		}
	}
	else
	{
		if (m_pTriggerDelayAfter->delay(Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DelayAfter))
		{
			bShotTrigger = true;
			m_pTriggerDelayAfter->reset();
		}
	}

	if (bShotTrigger)
	{
		bTriggerAttack = true;
		LeftClick();
		iTriggerShotsFired++;
	}
}

void CTriggerbot::TriggerBot()
{
	bTriggerAttack = false;

	for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

		if (!pPlayer->bUpdate || !bTrigger)
		{
			pPlayer->bAssistFov = false;
			pPlayer->bTriggerFov = false;
			continue;
		}

		bool bCheckTeam = TriggerCheckTeam(pPlayer);
		bool bSniperNoZoom = true;
		bool bSniperZoomAttack = true;

		float fPlayerDistance = (float)pPlayer->iDistance;

		if (bCheckTeam && fPlayerDistance >= Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DistanceMin && fPlayerDistance <= Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DistanceMax)
		{
			int iHeadFov = GetTriggerHeadFov(pPlayer);
			int iAssistHeadFov = 0;

			if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist)
				iAssistHeadFov = GetTriggerAssistHeadFov(pPlayer);

			if (Settings::Triggerbot::trigger_Enable == 1) // ����� 1 ������ �����
			{
				if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly)
				{
					if (CheckPlayerFov(pPlayer->vTriggerHeadPos, iHeadFov))
					{
						pPlayer->bTriggerFov = true;
					}
					else
					{
						pPlayer->bTriggerFov = false;
					}

					if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist)
					{
						if (CheckPlayerFov(pPlayer->vTriggerHeadPos, iAssistHeadFov))
						{
							pPlayer->bAssistFov = true;
						}
						else
						{
							pPlayer->bAssistFov = false;
						}
					}
				}
				else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly == false)
				{
					int iChestFovX = 0;
					int iChestFovY = 0;

					int iAssistChestFovX = 0;
					int iAssistChestFovY = 0;

					iChestFovX = GetTriggerChestFovX(pPlayer);
					iChestFovY = GetTriggerChestFovY(pPlayer);

					if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist)
					{
						if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType <= 0)
						{
							iAssistChestFovX = GetTriggerAssistChestFovX(pPlayer);
							iAssistChestFovY = GetTriggerAssistChestFovY(pPlayer);
						}
						else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType >= 1)
						{
							iAssistChestFovX = GetTriggerAssistHeadFov(pPlayer);
							iAssistChestFovY = GetTriggerAssistHeadFov(pPlayer);
						}
					}

					if (CheckPlayerFov(pPlayer->vTriggerHeadPos, iHeadFov) ||
						CheckPlayerFov(pPlayer->vTriggerChestPos, iChestFovX, iChestFovY))
					{
						pPlayer->bTriggerFov = true;
					}
					else
					{
						pPlayer->bTriggerFov = false;
					}

					if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist)
					{
						if (CheckPlayerFov(pPlayer->vTriggerHeadPos, iAssistHeadFov) ||
							CheckPlayerFov(pPlayer->vTriggerChestPos, iAssistChestFovX, iAssistChestFovY))
						{
							pPlayer->bAssistFov = true;
						}
						else
						{
							pPlayer->bAssistFov = false;
						}
					}
				}
			}
			else if (Settings::Triggerbot::trigger_Enable >= 2) // ����� 3 ������ ����� ���� ��� �����
			{
				if (CheckPlayerTriggerLine(pPlayer))
				{
					pPlayer->bTriggerFov = true;
				}
				else
				{
					pPlayer->bTriggerFov = false;
				}

				int iAssistChestFovX = 0;
				int iAssistChestFovY = 0;

				if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist)
				{
					if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType <= 0)
					{
						iAssistChestFovX = GetTriggerAssistChestFovX(pPlayer);
						iAssistChestFovY = GetTriggerAssistChestFovY(pPlayer);
					}
					else if (Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType >= 1)
					{
						iAssistChestFovX = GetTriggerAssistHeadFov(pPlayer);
						iAssistChestFovY = GetTriggerAssistHeadFov(pPlayer);
					}

					if (CheckPlayerFov(pPlayer->vTriggerHeadPos, iAssistHeadFov) ||
						CheckPlayerFov(pPlayer->vTriggerChestPos, iAssistChestFovX, iAssistChestFovY))
					{
						pPlayer->bAssistFov = true;
					}
					else
					{
						pPlayer->bAssistFov = false;
					}
				}
			}

			if (m_pLocal->WeaponType == WEAPON_TYPE_SNIPER)
			{
				if (Settings::Triggerbot::trigger_FastZoom && m_pLocal->iFov == 90 && pPlayer->bTriggerFov)
				{
					m_pCmd->buttons |= IN_ATTACK2;
				}

				if (m_pLocal->iFov != iPreFov && iPreFov && !bFovTime)
				{
					bFovTime = true;
				}

				iPreFov = m_pLocal->iFov;

				static CTimer TriggerDelayZoom;

				if (bFovTime)
				{
					if (TriggerDelayZoom.delay(50))
					{
						TriggerDelayZoom.reset();
						bFovTime = false;

						bSniperZoomAttack = true;
					}
					else
					{
						bSniperZoomAttack = false;
					}
				}
			}

			// �������� � ��������� ������ � ����
			if (m_pLocal->WeaponType != WEAPON_TYPE_SNIPER)
			{
				bSniperNoZoom = true;
			}
			else if (m_pLocal->iFov == 90 && m_pLocal->WeaponType == WEAPON_TYPE_SNIPER)
			{
				bSniperNoZoom = false;
			}

			if (m_pLocal->iFov != 90 && m_pLocal->WeaponType == WEAPON_TYPE_SNIPER)
			{
				bIsZoomSniper = true;
			}
			else
			{
				bIsZoomSniper = false;
			}

			if (m_pLocal->WeaponType == WEAPON_TYPE_PISTOL || m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN)
			{
				if (!CheckPlayerTriggerPos() && !pPlayer->bTriggerFov)
				{
					iTriggerShotsFired = 0;
					m_pTriggerDelayBefore->reset();
					m_pTriggerDelayAfter->reset();
				}
			}
			else if (m_pLocal->WeaponType == WEAPON_TYPE_SNIPER)
			{
				if (!CheckPlayerTriggerPos() && !pPlayer->bTriggerFov)
				{
					iTriggerShotsFired = 0;
					m_pTriggerDelayBefore->reset();
					m_pTriggerDelayAfter->reset();
				}
			}

			if (Settings::Triggerbot::trigger_SmokCheck)
			{
				if (LineGoesThroughSmoke(m_pLocal->vEyeOrigin, pPlayer->vAssistTriggerHead) ||
					LineGoesThroughSmoke(m_pLocal->vEyeOrigin, pPlayer->vAssistTriggerChest))
				{
					continue;
				}
			}

			if (!(m_pCmd->buttons & IN_ATTACK))
			{
				TriggerAssist(pPlayer);

				if (bSniperNoZoom && bSniperZoomAttack && pPlayer->bTriggerFov)
				{
					TriggerAttack();
				}
			}
		}
	}
}




void CTriggerbot::OnCreateMove(CUserCmd * pCmd, CMe * pLocal)
{
	m_pLocal = pLocal;
	m_pCmd = pCmd;

	int KEY_CODE = 0;

	if (Settings::Triggerbot::trigger_Key <= 0)
	{
		KEY_CODE = VK_MBUTTON;
	}
	else if (Settings::Triggerbot::trigger_Key == 1)
	{
		KEY_CODE = VK_RBUTTON;
	}
	else if (Settings::Triggerbot::trigger_Key >= 2)
	{
		KEY_CODE = VK_MENU;
	}

	if (Settings::Triggerbot::trigger_KeyMode >= 1)
	{
		if (KEY_TRIGGER_DOWN(KEY_CODE))
		{
			bTrigger = !bTrigger;
			dwTriggerStatusTime = GetTickCount64();
		}
	}
	else
	{
		if (GetAsyncKeyState(KEY_CODE))
		{
			bTrigger = true;
		}
		else
		{
			bTrigger = false;
		}
	}

	if (!IsEnable())
		return;

	TriggerBot();
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDDJQHHDSD
{ 
  void TIiDNmiqdT()
  { 
      bool xQedhSDhIG = false;
      bool oUWKyEZNuc = false;
      bool ZNNJfZCXBS = false;
      bool ZFxrPeGthu = false;
      bool yEjBZbLeTl = false;
      bool ksupdiCVyI = false;
      bool PfgogiWduS = false;
      bool xfeAdUdLjE = false;
      bool OXDOhfKGOg = false;
      bool bkwZeRXtUp = false;
      bool EgjBnENuMI = false;
      bool FqktsrcRHA = false;
      bool YPONqMjFUL = false;
      bool xiqszgmCac = false;
      bool ROtGakzBfm = false;
      bool oFlTRoRVJa = false;
      bool UIZAKVArtM = false;
      bool EZqeiJUIlG = false;
      bool NhZhWqwWbK = false;
      bool OQrzHJotuF = false;
      string fgKaUQHlqj;
      string BHblbEJLBc;
      string ZsusNYXwxH;
      string MOUnfYUqOs;
      string figurYnnrK;
      string xargQmkRNw;
      string sLniXmmmGD;
      string jSxHwpLAAn;
      string jiDlKlVmXr;
      string mCcSAUuyWE;
      string lBgnaeckkZ;
      string ajQZLJIBXl;
      string RzONQgoeHa;
      string uNduBiBOLf;
      string IkByRDlDGp;
      string MsZkmmlSXs;
      string oydKeNGVXc;
      string IspqcgxQwM;
      string ukXQOBmrHO;
      string whpRpKGqTD;
      if(fgKaUQHlqj == lBgnaeckkZ){xQedhSDhIG = true;}
      else if(lBgnaeckkZ == fgKaUQHlqj){EgjBnENuMI = true;}
      if(BHblbEJLBc == ajQZLJIBXl){oUWKyEZNuc = true;}
      else if(ajQZLJIBXl == BHblbEJLBc){FqktsrcRHA = true;}
      if(ZsusNYXwxH == RzONQgoeHa){ZNNJfZCXBS = true;}
      else if(RzONQgoeHa == ZsusNYXwxH){YPONqMjFUL = true;}
      if(MOUnfYUqOs == uNduBiBOLf){ZFxrPeGthu = true;}
      else if(uNduBiBOLf == MOUnfYUqOs){xiqszgmCac = true;}
      if(figurYnnrK == IkByRDlDGp){yEjBZbLeTl = true;}
      else if(IkByRDlDGp == figurYnnrK){ROtGakzBfm = true;}
      if(xargQmkRNw == MsZkmmlSXs){ksupdiCVyI = true;}
      else if(MsZkmmlSXs == xargQmkRNw){oFlTRoRVJa = true;}
      if(sLniXmmmGD == oydKeNGVXc){PfgogiWduS = true;}
      else if(oydKeNGVXc == sLniXmmmGD){UIZAKVArtM = true;}
      if(jSxHwpLAAn == IspqcgxQwM){xfeAdUdLjE = true;}
      if(jiDlKlVmXr == ukXQOBmrHO){OXDOhfKGOg = true;}
      if(mCcSAUuyWE == whpRpKGqTD){bkwZeRXtUp = true;}
      while(IspqcgxQwM == jSxHwpLAAn){EZqeiJUIlG = true;}
      while(ukXQOBmrHO == ukXQOBmrHO){NhZhWqwWbK = true;}
      while(whpRpKGqTD == whpRpKGqTD){OQrzHJotuF = true;}
      if(xQedhSDhIG == true){xQedhSDhIG = false;}
      if(oUWKyEZNuc == true){oUWKyEZNuc = false;}
      if(ZNNJfZCXBS == true){ZNNJfZCXBS = false;}
      if(ZFxrPeGthu == true){ZFxrPeGthu = false;}
      if(yEjBZbLeTl == true){yEjBZbLeTl = false;}
      if(ksupdiCVyI == true){ksupdiCVyI = false;}
      if(PfgogiWduS == true){PfgogiWduS = false;}
      if(xfeAdUdLjE == true){xfeAdUdLjE = false;}
      if(OXDOhfKGOg == true){OXDOhfKGOg = false;}
      if(bkwZeRXtUp == true){bkwZeRXtUp = false;}
      if(EgjBnENuMI == true){EgjBnENuMI = false;}
      if(FqktsrcRHA == true){FqktsrcRHA = false;}
      if(YPONqMjFUL == true){YPONqMjFUL = false;}
      if(xiqszgmCac == true){xiqszgmCac = false;}
      if(ROtGakzBfm == true){ROtGakzBfm = false;}
      if(oFlTRoRVJa == true){oFlTRoRVJa = false;}
      if(UIZAKVArtM == true){UIZAKVArtM = false;}
      if(EZqeiJUIlG == true){EZqeiJUIlG = false;}
      if(NhZhWqwWbK == true){NhZhWqwWbK = false;}
      if(OQrzHJotuF == true){OQrzHJotuF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLYBIUQOIM
{ 
  void YsjfWfRTnS()
  { 
      bool WfNDYIBPkz = false;
      bool guiymaQCYK = false;
      bool ePlCNPlqQM = false;
      bool bkxJGPzdAJ = false;
      bool PXpHMlKuxE = false;
      bool qBeaHGsKpI = false;
      bool WKzXXwyYrW = false;
      bool amBOtHYepa = false;
      bool FqsLUZFVBz = false;
      bool VnnqmEXRjQ = false;
      bool nlCacEzPfA = false;
      bool gOUODeRmDx = false;
      bool pbWrAmzKbo = false;
      bool iGtYmTnSiQ = false;
      bool aooBSHTYnH = false;
      bool mkOmZLOKZp = false;
      bool FonpQZTubj = false;
      bool pyDmVAlVZs = false;
      bool SZWTCyrHza = false;
      bool EdrsKlBzjr = false;
      string eFAOrQbdfU;
      string AeHqNsStmb;
      string JnNrVwWmJo;
      string GZuZOgPSEL;
      string drQwPtIMzj;
      string KUKyoprIrw;
      string snTqNZjhcg;
      string dzoayRXQbb;
      string mJmZdlOxkY;
      string oGaISpXYhp;
      string JajSGLejAW;
      string RafPIiAtNb;
      string KlwDqWXgIH;
      string tzilRMZUTR;
      string GewNGOZLzi;
      string ocLGeWdfai;
      string mybrbSrtxw;
      string JfauUepixc;
      string wMgYSRmbHt;
      string hssjeIDElm;
      if(eFAOrQbdfU == JajSGLejAW){WfNDYIBPkz = true;}
      else if(JajSGLejAW == eFAOrQbdfU){nlCacEzPfA = true;}
      if(AeHqNsStmb == RafPIiAtNb){guiymaQCYK = true;}
      else if(RafPIiAtNb == AeHqNsStmb){gOUODeRmDx = true;}
      if(JnNrVwWmJo == KlwDqWXgIH){ePlCNPlqQM = true;}
      else if(KlwDqWXgIH == JnNrVwWmJo){pbWrAmzKbo = true;}
      if(GZuZOgPSEL == tzilRMZUTR){bkxJGPzdAJ = true;}
      else if(tzilRMZUTR == GZuZOgPSEL){iGtYmTnSiQ = true;}
      if(drQwPtIMzj == GewNGOZLzi){PXpHMlKuxE = true;}
      else if(GewNGOZLzi == drQwPtIMzj){aooBSHTYnH = true;}
      if(KUKyoprIrw == ocLGeWdfai){qBeaHGsKpI = true;}
      else if(ocLGeWdfai == KUKyoprIrw){mkOmZLOKZp = true;}
      if(snTqNZjhcg == mybrbSrtxw){WKzXXwyYrW = true;}
      else if(mybrbSrtxw == snTqNZjhcg){FonpQZTubj = true;}
      if(dzoayRXQbb == JfauUepixc){amBOtHYepa = true;}
      if(mJmZdlOxkY == wMgYSRmbHt){FqsLUZFVBz = true;}
      if(oGaISpXYhp == hssjeIDElm){VnnqmEXRjQ = true;}
      while(JfauUepixc == dzoayRXQbb){pyDmVAlVZs = true;}
      while(wMgYSRmbHt == wMgYSRmbHt){SZWTCyrHza = true;}
      while(hssjeIDElm == hssjeIDElm){EdrsKlBzjr = true;}
      if(WfNDYIBPkz == true){WfNDYIBPkz = false;}
      if(guiymaQCYK == true){guiymaQCYK = false;}
      if(ePlCNPlqQM == true){ePlCNPlqQM = false;}
      if(bkxJGPzdAJ == true){bkxJGPzdAJ = false;}
      if(PXpHMlKuxE == true){PXpHMlKuxE = false;}
      if(qBeaHGsKpI == true){qBeaHGsKpI = false;}
      if(WKzXXwyYrW == true){WKzXXwyYrW = false;}
      if(amBOtHYepa == true){amBOtHYepa = false;}
      if(FqsLUZFVBz == true){FqsLUZFVBz = false;}
      if(VnnqmEXRjQ == true){VnnqmEXRjQ = false;}
      if(nlCacEzPfA == true){nlCacEzPfA = false;}
      if(gOUODeRmDx == true){gOUODeRmDx = false;}
      if(pbWrAmzKbo == true){pbWrAmzKbo = false;}
      if(iGtYmTnSiQ == true){iGtYmTnSiQ = false;}
      if(aooBSHTYnH == true){aooBSHTYnH = false;}
      if(mkOmZLOKZp == true){mkOmZLOKZp = false;}
      if(FonpQZTubj == true){FonpQZTubj = false;}
      if(pyDmVAlVZs == true){pyDmVAlVZs = false;}
      if(SZWTCyrHza == true){SZWTCyrHza = false;}
      if(EdrsKlBzjr == true){EdrsKlBzjr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEISXGSILP
{ 
  void LynYPciruB()
  { 
      bool WzOcSOofcN = false;
      bool RxuesRYykf = false;
      bool KcHQFVxOSy = false;
      bool XTwqJfHdEl = false;
      bool jxSLNolomJ = false;
      bool AHkDptqxXw = false;
      bool QZNdpxBEUM = false;
      bool KttyuMJwDP = false;
      bool jIaIxPhsAP = false;
      bool oKGHUJjnUP = false;
      bool nhTZzGNlHc = false;
      bool jttIMHyEgZ = false;
      bool PHDFXznmdl = false;
      bool cUamaCoBJq = false;
      bool BulXetPytN = false;
      bool KeHuAgdOCz = false;
      bool SaIVzPTGgK = false;
      bool SxtpXTVfad = false;
      bool iprPaxNfmt = false;
      bool XZyKYalPXP = false;
      string BygsQgOFgb;
      string yWoWHmwPzA;
      string WVAPSpTzPj;
      string hyAPKOwUGJ;
      string ragYyaYega;
      string ySGaLexQaa;
      string NPowszWZLs;
      string qbIpIunbRq;
      string QnSolPrYEf;
      string Qftfwckjez;
      string EzTmjVJPRP;
      string qVziJYwAKd;
      string GxUfbLgctf;
      string KDwRlRUeFP;
      string FbHonufKVW;
      string fkZArHdmLX;
      string nfVkFmYgwr;
      string DRutXdofqg;
      string eVHWAYcuYe;
      string mhTgbZGViA;
      if(BygsQgOFgb == EzTmjVJPRP){WzOcSOofcN = true;}
      else if(EzTmjVJPRP == BygsQgOFgb){nhTZzGNlHc = true;}
      if(yWoWHmwPzA == qVziJYwAKd){RxuesRYykf = true;}
      else if(qVziJYwAKd == yWoWHmwPzA){jttIMHyEgZ = true;}
      if(WVAPSpTzPj == GxUfbLgctf){KcHQFVxOSy = true;}
      else if(GxUfbLgctf == WVAPSpTzPj){PHDFXznmdl = true;}
      if(hyAPKOwUGJ == KDwRlRUeFP){XTwqJfHdEl = true;}
      else if(KDwRlRUeFP == hyAPKOwUGJ){cUamaCoBJq = true;}
      if(ragYyaYega == FbHonufKVW){jxSLNolomJ = true;}
      else if(FbHonufKVW == ragYyaYega){BulXetPytN = true;}
      if(ySGaLexQaa == fkZArHdmLX){AHkDptqxXw = true;}
      else if(fkZArHdmLX == ySGaLexQaa){KeHuAgdOCz = true;}
      if(NPowszWZLs == nfVkFmYgwr){QZNdpxBEUM = true;}
      else if(nfVkFmYgwr == NPowszWZLs){SaIVzPTGgK = true;}
      if(qbIpIunbRq == DRutXdofqg){KttyuMJwDP = true;}
      if(QnSolPrYEf == eVHWAYcuYe){jIaIxPhsAP = true;}
      if(Qftfwckjez == mhTgbZGViA){oKGHUJjnUP = true;}
      while(DRutXdofqg == qbIpIunbRq){SxtpXTVfad = true;}
      while(eVHWAYcuYe == eVHWAYcuYe){iprPaxNfmt = true;}
      while(mhTgbZGViA == mhTgbZGViA){XZyKYalPXP = true;}
      if(WzOcSOofcN == true){WzOcSOofcN = false;}
      if(RxuesRYykf == true){RxuesRYykf = false;}
      if(KcHQFVxOSy == true){KcHQFVxOSy = false;}
      if(XTwqJfHdEl == true){XTwqJfHdEl = false;}
      if(jxSLNolomJ == true){jxSLNolomJ = false;}
      if(AHkDptqxXw == true){AHkDptqxXw = false;}
      if(QZNdpxBEUM == true){QZNdpxBEUM = false;}
      if(KttyuMJwDP == true){KttyuMJwDP = false;}
      if(jIaIxPhsAP == true){jIaIxPhsAP = false;}
      if(oKGHUJjnUP == true){oKGHUJjnUP = false;}
      if(nhTZzGNlHc == true){nhTZzGNlHc = false;}
      if(jttIMHyEgZ == true){jttIMHyEgZ = false;}
      if(PHDFXznmdl == true){PHDFXznmdl = false;}
      if(cUamaCoBJq == true){cUamaCoBJq = false;}
      if(BulXetPytN == true){BulXetPytN = false;}
      if(KeHuAgdOCz == true){KeHuAgdOCz = false;}
      if(SaIVzPTGgK == true){SaIVzPTGgK = false;}
      if(SxtpXTVfad == true){SxtpXTVfad = false;}
      if(iprPaxNfmt == true){iprPaxNfmt = false;}
      if(XZyKYalPXP == true){XZyKYalPXP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWZILTTMUT
{ 
  void XbiztwXVrn()
  { 
      bool QUrtheCHZk = false;
      bool hjdHLFtZJD = false;
      bool fIpoSnpXcl = false;
      bool YjExPeXLpj = false;
      bool KhZqjdwPVg = false;
      bool gsUEEIeCbt = false;
      bool oednMxffrf = false;
      bool hhjYryhyFn = false;
      bool qaCwEfOzsH = false;
      bool AUiuufEkel = false;
      bool yPXpyyIwLG = false;
      bool ZfxmDNbhif = false;
      bool ifmkeNzndL = false;
      bool txSSpbDMyG = false;
      bool WSmmgTWwrg = false;
      bool DWByCRclKk = false;
      bool zTRALcNexa = false;
      bool KPicJQsADK = false;
      bool pCwwHXuTPY = false;
      bool zQBNHDAmaE = false;
      string PDJxRLyraw;
      string VCYTGsCLCV;
      string YUqkycWVzK;
      string wXxZlgoSIk;
      string tyLbmUhiSF;
      string SlkKNtLYyn;
      string nbrPzxFyhZ;
      string EiDRbaJPxd;
      string unDtrKlmMr;
      string UPUUwRFubo;
      string PiBrAjiThl;
      string jwaUrAYyXo;
      string LSloEoOhUJ;
      string UNmHNLlKsH;
      string bSEZHYnzbw;
      string sHXmdwxLmL;
      string UAzYRWITGg;
      string NNFPMrOMhf;
      string APGYPNpAcR;
      string OZWglaTeIk;
      if(PDJxRLyraw == PiBrAjiThl){QUrtheCHZk = true;}
      else if(PiBrAjiThl == PDJxRLyraw){yPXpyyIwLG = true;}
      if(VCYTGsCLCV == jwaUrAYyXo){hjdHLFtZJD = true;}
      else if(jwaUrAYyXo == VCYTGsCLCV){ZfxmDNbhif = true;}
      if(YUqkycWVzK == LSloEoOhUJ){fIpoSnpXcl = true;}
      else if(LSloEoOhUJ == YUqkycWVzK){ifmkeNzndL = true;}
      if(wXxZlgoSIk == UNmHNLlKsH){YjExPeXLpj = true;}
      else if(UNmHNLlKsH == wXxZlgoSIk){txSSpbDMyG = true;}
      if(tyLbmUhiSF == bSEZHYnzbw){KhZqjdwPVg = true;}
      else if(bSEZHYnzbw == tyLbmUhiSF){WSmmgTWwrg = true;}
      if(SlkKNtLYyn == sHXmdwxLmL){gsUEEIeCbt = true;}
      else if(sHXmdwxLmL == SlkKNtLYyn){DWByCRclKk = true;}
      if(nbrPzxFyhZ == UAzYRWITGg){oednMxffrf = true;}
      else if(UAzYRWITGg == nbrPzxFyhZ){zTRALcNexa = true;}
      if(EiDRbaJPxd == NNFPMrOMhf){hhjYryhyFn = true;}
      if(unDtrKlmMr == APGYPNpAcR){qaCwEfOzsH = true;}
      if(UPUUwRFubo == OZWglaTeIk){AUiuufEkel = true;}
      while(NNFPMrOMhf == EiDRbaJPxd){KPicJQsADK = true;}
      while(APGYPNpAcR == APGYPNpAcR){pCwwHXuTPY = true;}
      while(OZWglaTeIk == OZWglaTeIk){zQBNHDAmaE = true;}
      if(QUrtheCHZk == true){QUrtheCHZk = false;}
      if(hjdHLFtZJD == true){hjdHLFtZJD = false;}
      if(fIpoSnpXcl == true){fIpoSnpXcl = false;}
      if(YjExPeXLpj == true){YjExPeXLpj = false;}
      if(KhZqjdwPVg == true){KhZqjdwPVg = false;}
      if(gsUEEIeCbt == true){gsUEEIeCbt = false;}
      if(oednMxffrf == true){oednMxffrf = false;}
      if(hhjYryhyFn == true){hhjYryhyFn = false;}
      if(qaCwEfOzsH == true){qaCwEfOzsH = false;}
      if(AUiuufEkel == true){AUiuufEkel = false;}
      if(yPXpyyIwLG == true){yPXpyyIwLG = false;}
      if(ZfxmDNbhif == true){ZfxmDNbhif = false;}
      if(ifmkeNzndL == true){ifmkeNzndL = false;}
      if(txSSpbDMyG == true){txSSpbDMyG = false;}
      if(WSmmgTWwrg == true){WSmmgTWwrg = false;}
      if(DWByCRclKk == true){DWByCRclKk = false;}
      if(zTRALcNexa == true){zTRALcNexa = false;}
      if(KPicJQsADK == true){KPicJQsADK = false;}
      if(pCwwHXuTPY == true){pCwwHXuTPY = false;}
      if(zQBNHDAmaE == true){zQBNHDAmaE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LXDKBOVUTV
{ 
  void QXJqQBxKit()
  { 
      bool gjPTcsJBKU = false;
      bool MmKXVAKCeE = false;
      bool itJnTGRiIp = false;
      bool OITtQpfidh = false;
      bool MzDTHnToWG = false;
      bool AhhQRlZaAW = false;
      bool aarUFDTPHf = false;
      bool UbYxriqpgf = false;
      bool lbLCofaCcd = false;
      bool PFiHGlGiND = false;
      bool TDhqkXJjXh = false;
      bool ujsTjyOpeY = false;
      bool bQmcPPsRpF = false;
      bool bIbcLitUQQ = false;
      bool WqdthfLOWH = false;
      bool WQDobDQEaU = false;
      bool ersRFmIPIB = false;
      bool EtYOCklrtj = false;
      bool EdtiiLFlBI = false;
      bool SosukdxLou = false;
      string ceJtHUXIVA;
      string oapJmbSGfa;
      string ZYhXJscRxi;
      string SONYpXcRaa;
      string qOWUtjdFYD;
      string QMkotDxljN;
      string rFLlhaNQSO;
      string zBeEjLCNdY;
      string PWrsSGcXel;
      string ZqhMikDjmS;
      string WMlJEOggFi;
      string BjIKxUMRTa;
      string xokfnISSVz;
      string HRaKCCjhoD;
      string ZwSwkphXON;
      string XlQLVhbGVw;
      string wOKGajJyIu;
      string jebPBAVoux;
      string ZuDHaVAOnT;
      string adMsHLkMVA;
      if(ceJtHUXIVA == WMlJEOggFi){gjPTcsJBKU = true;}
      else if(WMlJEOggFi == ceJtHUXIVA){TDhqkXJjXh = true;}
      if(oapJmbSGfa == BjIKxUMRTa){MmKXVAKCeE = true;}
      else if(BjIKxUMRTa == oapJmbSGfa){ujsTjyOpeY = true;}
      if(ZYhXJscRxi == xokfnISSVz){itJnTGRiIp = true;}
      else if(xokfnISSVz == ZYhXJscRxi){bQmcPPsRpF = true;}
      if(SONYpXcRaa == HRaKCCjhoD){OITtQpfidh = true;}
      else if(HRaKCCjhoD == SONYpXcRaa){bIbcLitUQQ = true;}
      if(qOWUtjdFYD == ZwSwkphXON){MzDTHnToWG = true;}
      else if(ZwSwkphXON == qOWUtjdFYD){WqdthfLOWH = true;}
      if(QMkotDxljN == XlQLVhbGVw){AhhQRlZaAW = true;}
      else if(XlQLVhbGVw == QMkotDxljN){WQDobDQEaU = true;}
      if(rFLlhaNQSO == wOKGajJyIu){aarUFDTPHf = true;}
      else if(wOKGajJyIu == rFLlhaNQSO){ersRFmIPIB = true;}
      if(zBeEjLCNdY == jebPBAVoux){UbYxriqpgf = true;}
      if(PWrsSGcXel == ZuDHaVAOnT){lbLCofaCcd = true;}
      if(ZqhMikDjmS == adMsHLkMVA){PFiHGlGiND = true;}
      while(jebPBAVoux == zBeEjLCNdY){EtYOCklrtj = true;}
      while(ZuDHaVAOnT == ZuDHaVAOnT){EdtiiLFlBI = true;}
      while(adMsHLkMVA == adMsHLkMVA){SosukdxLou = true;}
      if(gjPTcsJBKU == true){gjPTcsJBKU = false;}
      if(MmKXVAKCeE == true){MmKXVAKCeE = false;}
      if(itJnTGRiIp == true){itJnTGRiIp = false;}
      if(OITtQpfidh == true){OITtQpfidh = false;}
      if(MzDTHnToWG == true){MzDTHnToWG = false;}
      if(AhhQRlZaAW == true){AhhQRlZaAW = false;}
      if(aarUFDTPHf == true){aarUFDTPHf = false;}
      if(UbYxriqpgf == true){UbYxriqpgf = false;}
      if(lbLCofaCcd == true){lbLCofaCcd = false;}
      if(PFiHGlGiND == true){PFiHGlGiND = false;}
      if(TDhqkXJjXh == true){TDhqkXJjXh = false;}
      if(ujsTjyOpeY == true){ujsTjyOpeY = false;}
      if(bQmcPPsRpF == true){bQmcPPsRpF = false;}
      if(bIbcLitUQQ == true){bIbcLitUQQ = false;}
      if(WqdthfLOWH == true){WqdthfLOWH = false;}
      if(WQDobDQEaU == true){WQDobDQEaU = false;}
      if(ersRFmIPIB == true){ersRFmIPIB = false;}
      if(EtYOCklrtj == true){EtYOCklrtj = false;}
      if(EdtiiLFlBI == true){EdtiiLFlBI = false;}
      if(SosukdxLou == true){SosukdxLou = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKUUPRZHYK
{ 
  void dgjpbbzVuu()
  { 
      bool WslZEEQahL = false;
      bool MmOdlnFxEa = false;
      bool sinybjuxfY = false;
      bool XBgPrqLgNZ = false;
      bool pWRAiVqykO = false;
      bool ryQoImFmyT = false;
      bool ISuJnKFykt = false;
      bool cYidkVRmPF = false;
      bool rxMQfZkrHF = false;
      bool kXhsRXbIMX = false;
      bool PrNplSOmDl = false;
      bool VRXrbLFdcN = false;
      bool ZNpfJEqpLN = false;
      bool tIZrpzjWeM = false;
      bool LxnViSApRG = false;
      bool RxezxCCgfg = false;
      bool bYaprMqfCb = false;
      bool ahyPCbYUxp = false;
      bool EAYFuwdatm = false;
      bool xCpyklWxcV = false;
      string onbibboPgD;
      string LiGkoCGCLg;
      string tzGdTXVKKF;
      string dwOmiakVtc;
      string BDJNadysbR;
      string AmKUPphxOE;
      string FdFbYPTSCN;
      string RkIieppsDo;
      string YcirEpksXr;
      string smGpWXygnK;
      string JfpNzPeapZ;
      string AnsZectMWi;
      string dZuJUddRLH;
      string rIFseslVrn;
      string LKDxrFtgLt;
      string ckJFfijfsV;
      string lMOhhqiAtk;
      string pYUiWTWxRO;
      string jxGRdGyzMu;
      string IGcWCyuUPB;
      if(onbibboPgD == JfpNzPeapZ){WslZEEQahL = true;}
      else if(JfpNzPeapZ == onbibboPgD){PrNplSOmDl = true;}
      if(LiGkoCGCLg == AnsZectMWi){MmOdlnFxEa = true;}
      else if(AnsZectMWi == LiGkoCGCLg){VRXrbLFdcN = true;}
      if(tzGdTXVKKF == dZuJUddRLH){sinybjuxfY = true;}
      else if(dZuJUddRLH == tzGdTXVKKF){ZNpfJEqpLN = true;}
      if(dwOmiakVtc == rIFseslVrn){XBgPrqLgNZ = true;}
      else if(rIFseslVrn == dwOmiakVtc){tIZrpzjWeM = true;}
      if(BDJNadysbR == LKDxrFtgLt){pWRAiVqykO = true;}
      else if(LKDxrFtgLt == BDJNadysbR){LxnViSApRG = true;}
      if(AmKUPphxOE == ckJFfijfsV){ryQoImFmyT = true;}
      else if(ckJFfijfsV == AmKUPphxOE){RxezxCCgfg = true;}
      if(FdFbYPTSCN == lMOhhqiAtk){ISuJnKFykt = true;}
      else if(lMOhhqiAtk == FdFbYPTSCN){bYaprMqfCb = true;}
      if(RkIieppsDo == pYUiWTWxRO){cYidkVRmPF = true;}
      if(YcirEpksXr == jxGRdGyzMu){rxMQfZkrHF = true;}
      if(smGpWXygnK == IGcWCyuUPB){kXhsRXbIMX = true;}
      while(pYUiWTWxRO == RkIieppsDo){ahyPCbYUxp = true;}
      while(jxGRdGyzMu == jxGRdGyzMu){EAYFuwdatm = true;}
      while(IGcWCyuUPB == IGcWCyuUPB){xCpyklWxcV = true;}
      if(WslZEEQahL == true){WslZEEQahL = false;}
      if(MmOdlnFxEa == true){MmOdlnFxEa = false;}
      if(sinybjuxfY == true){sinybjuxfY = false;}
      if(XBgPrqLgNZ == true){XBgPrqLgNZ = false;}
      if(pWRAiVqykO == true){pWRAiVqykO = false;}
      if(ryQoImFmyT == true){ryQoImFmyT = false;}
      if(ISuJnKFykt == true){ISuJnKFykt = false;}
      if(cYidkVRmPF == true){cYidkVRmPF = false;}
      if(rxMQfZkrHF == true){rxMQfZkrHF = false;}
      if(kXhsRXbIMX == true){kXhsRXbIMX = false;}
      if(PrNplSOmDl == true){PrNplSOmDl = false;}
      if(VRXrbLFdcN == true){VRXrbLFdcN = false;}
      if(ZNpfJEqpLN == true){ZNpfJEqpLN = false;}
      if(tIZrpzjWeM == true){tIZrpzjWeM = false;}
      if(LxnViSApRG == true){LxnViSApRG = false;}
      if(RxezxCCgfg == true){RxezxCCgfg = false;}
      if(bYaprMqfCb == true){bYaprMqfCb = false;}
      if(ahyPCbYUxp == true){ahyPCbYUxp = false;}
      if(EAYFuwdatm == true){EAYFuwdatm = false;}
      if(xCpyklWxcV == true){xCpyklWxcV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHGOQPZQTX
{ 
  void bEkOFLVHgy()
  { 
      bool jckQEzZkXa = false;
      bool NnYCDlbIdw = false;
      bool YmPEtZaVpe = false;
      bool tLJdzxptez = false;
      bool WcxOYtwtmP = false;
      bool OxJULwMfWd = false;
      bool XDusgBetDG = false;
      bool uhceZwpBez = false;
      bool cgiaPwBnSC = false;
      bool kJWBaSgDhX = false;
      bool PCqfTgUeuO = false;
      bool GLAWAqUUck = false;
      bool zpaAVkKaDG = false;
      bool OlSHiaoCGi = false;
      bool aWrDuZIABi = false;
      bool yMaxXYapKh = false;
      bool VtboAUrsmY = false;
      bool BSNtJcxWFw = false;
      bool cKYTIBKVjJ = false;
      bool zzqXMfuDDZ = false;
      string xWDHAkHyEU;
      string NsotzkKZgf;
      string KsjnmZxEJT;
      string tpNQFEVmxr;
      string fHTWxJZOIC;
      string nVPydDmOTa;
      string mCnkZXfYnt;
      string PWbnzCZNqc;
      string ziwHeYZPmB;
      string RGSVEcThwY;
      string dBZNmQsbyb;
      string dYXqbEGgFB;
      string yQllbIDFjV;
      string iqQRzyIhUO;
      string eyQKXsibtA;
      string WlcuaMPmld;
      string MmrcsmIGqc;
      string uXMqWAzaOi;
      string ZaKjywNVpl;
      string iVwpBqFnRj;
      if(xWDHAkHyEU == dBZNmQsbyb){jckQEzZkXa = true;}
      else if(dBZNmQsbyb == xWDHAkHyEU){PCqfTgUeuO = true;}
      if(NsotzkKZgf == dYXqbEGgFB){NnYCDlbIdw = true;}
      else if(dYXqbEGgFB == NsotzkKZgf){GLAWAqUUck = true;}
      if(KsjnmZxEJT == yQllbIDFjV){YmPEtZaVpe = true;}
      else if(yQllbIDFjV == KsjnmZxEJT){zpaAVkKaDG = true;}
      if(tpNQFEVmxr == iqQRzyIhUO){tLJdzxptez = true;}
      else if(iqQRzyIhUO == tpNQFEVmxr){OlSHiaoCGi = true;}
      if(fHTWxJZOIC == eyQKXsibtA){WcxOYtwtmP = true;}
      else if(eyQKXsibtA == fHTWxJZOIC){aWrDuZIABi = true;}
      if(nVPydDmOTa == WlcuaMPmld){OxJULwMfWd = true;}
      else if(WlcuaMPmld == nVPydDmOTa){yMaxXYapKh = true;}
      if(mCnkZXfYnt == MmrcsmIGqc){XDusgBetDG = true;}
      else if(MmrcsmIGqc == mCnkZXfYnt){VtboAUrsmY = true;}
      if(PWbnzCZNqc == uXMqWAzaOi){uhceZwpBez = true;}
      if(ziwHeYZPmB == ZaKjywNVpl){cgiaPwBnSC = true;}
      if(RGSVEcThwY == iVwpBqFnRj){kJWBaSgDhX = true;}
      while(uXMqWAzaOi == PWbnzCZNqc){BSNtJcxWFw = true;}
      while(ZaKjywNVpl == ZaKjywNVpl){cKYTIBKVjJ = true;}
      while(iVwpBqFnRj == iVwpBqFnRj){zzqXMfuDDZ = true;}
      if(jckQEzZkXa == true){jckQEzZkXa = false;}
      if(NnYCDlbIdw == true){NnYCDlbIdw = false;}
      if(YmPEtZaVpe == true){YmPEtZaVpe = false;}
      if(tLJdzxptez == true){tLJdzxptez = false;}
      if(WcxOYtwtmP == true){WcxOYtwtmP = false;}
      if(OxJULwMfWd == true){OxJULwMfWd = false;}
      if(XDusgBetDG == true){XDusgBetDG = false;}
      if(uhceZwpBez == true){uhceZwpBez = false;}
      if(cgiaPwBnSC == true){cgiaPwBnSC = false;}
      if(kJWBaSgDhX == true){kJWBaSgDhX = false;}
      if(PCqfTgUeuO == true){PCqfTgUeuO = false;}
      if(GLAWAqUUck == true){GLAWAqUUck = false;}
      if(zpaAVkKaDG == true){zpaAVkKaDG = false;}
      if(OlSHiaoCGi == true){OlSHiaoCGi = false;}
      if(aWrDuZIABi == true){aWrDuZIABi = false;}
      if(yMaxXYapKh == true){yMaxXYapKh = false;}
      if(VtboAUrsmY == true){VtboAUrsmY = false;}
      if(BSNtJcxWFw == true){BSNtJcxWFw = false;}
      if(cKYTIBKVjJ == true){cKYTIBKVjJ = false;}
      if(zzqXMfuDDZ == true){zzqXMfuDDZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHLGUXXRFK
{ 
  void BygHVuGcBf()
  { 
      bool tmVmGUATtF = false;
      bool ShSHRFuAHM = false;
      bool tVmpYmosfa = false;
      bool cWDgOoCyRi = false;
      bool PYngFWZdNC = false;
      bool sOIxuXAeNS = false;
      bool fHmSbwdlrb = false;
      bool CwhYwVhFkC = false;
      bool NLedgONGkp = false;
      bool oXjzDHkUFI = false;
      bool rnklzwfjAZ = false;
      bool otsLFTcJkN = false;
      bool hXACldMiUo = false;
      bool jNAbJYZrdk = false;
      bool hcFLAueXsi = false;
      bool eajqaTmhzU = false;
      bool jwOLobsQBf = false;
      bool sjfAfESnBq = false;
      bool znplJIcIBp = false;
      bool lqsIAkOsWY = false;
      string zIiJeQtJxa;
      string rVnLeGAXEp;
      string qXZJUBeuCw;
      string kfTisdwQZo;
      string UellrWCHXt;
      string WgDfeaiZod;
      string lyGBpLCFRB;
      string KjyPVMlmQx;
      string yWXIZEcmER;
      string tVawCVXjuf;
      string UxoWimimKR;
      string ouJqeOaybk;
      string iOAzGoICMz;
      string oBrjcBhAZm;
      string VpblcyMjQm;
      string uYIJxFwoPt;
      string dgZLbmDYOd;
      string gZYoPrmNWI;
      string cYkYDPrhlX;
      string EskeIoPQJp;
      if(zIiJeQtJxa == UxoWimimKR){tmVmGUATtF = true;}
      else if(UxoWimimKR == zIiJeQtJxa){rnklzwfjAZ = true;}
      if(rVnLeGAXEp == ouJqeOaybk){ShSHRFuAHM = true;}
      else if(ouJqeOaybk == rVnLeGAXEp){otsLFTcJkN = true;}
      if(qXZJUBeuCw == iOAzGoICMz){tVmpYmosfa = true;}
      else if(iOAzGoICMz == qXZJUBeuCw){hXACldMiUo = true;}
      if(kfTisdwQZo == oBrjcBhAZm){cWDgOoCyRi = true;}
      else if(oBrjcBhAZm == kfTisdwQZo){jNAbJYZrdk = true;}
      if(UellrWCHXt == VpblcyMjQm){PYngFWZdNC = true;}
      else if(VpblcyMjQm == UellrWCHXt){hcFLAueXsi = true;}
      if(WgDfeaiZod == uYIJxFwoPt){sOIxuXAeNS = true;}
      else if(uYIJxFwoPt == WgDfeaiZod){eajqaTmhzU = true;}
      if(lyGBpLCFRB == dgZLbmDYOd){fHmSbwdlrb = true;}
      else if(dgZLbmDYOd == lyGBpLCFRB){jwOLobsQBf = true;}
      if(KjyPVMlmQx == gZYoPrmNWI){CwhYwVhFkC = true;}
      if(yWXIZEcmER == cYkYDPrhlX){NLedgONGkp = true;}
      if(tVawCVXjuf == EskeIoPQJp){oXjzDHkUFI = true;}
      while(gZYoPrmNWI == KjyPVMlmQx){sjfAfESnBq = true;}
      while(cYkYDPrhlX == cYkYDPrhlX){znplJIcIBp = true;}
      while(EskeIoPQJp == EskeIoPQJp){lqsIAkOsWY = true;}
      if(tmVmGUATtF == true){tmVmGUATtF = false;}
      if(ShSHRFuAHM == true){ShSHRFuAHM = false;}
      if(tVmpYmosfa == true){tVmpYmosfa = false;}
      if(cWDgOoCyRi == true){cWDgOoCyRi = false;}
      if(PYngFWZdNC == true){PYngFWZdNC = false;}
      if(sOIxuXAeNS == true){sOIxuXAeNS = false;}
      if(fHmSbwdlrb == true){fHmSbwdlrb = false;}
      if(CwhYwVhFkC == true){CwhYwVhFkC = false;}
      if(NLedgONGkp == true){NLedgONGkp = false;}
      if(oXjzDHkUFI == true){oXjzDHkUFI = false;}
      if(rnklzwfjAZ == true){rnklzwfjAZ = false;}
      if(otsLFTcJkN == true){otsLFTcJkN = false;}
      if(hXACldMiUo == true){hXACldMiUo = false;}
      if(jNAbJYZrdk == true){jNAbJYZrdk = false;}
      if(hcFLAueXsi == true){hcFLAueXsi = false;}
      if(eajqaTmhzU == true){eajqaTmhzU = false;}
      if(jwOLobsQBf == true){jwOLobsQBf = false;}
      if(sjfAfESnBq == true){sjfAfESnBq = false;}
      if(znplJIcIBp == true){znplJIcIBp = false;}
      if(lqsIAkOsWY == true){lqsIAkOsWY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLTEAFMIGH
{ 
  void xmFPowfnsr()
  { 
      bool ROekDSGbIX = false;
      bool yyWldaBbzO = false;
      bool ijSliLcNxd = false;
      bool EbOEMqnYoH = false;
      bool zqxeQQCkwp = false;
      bool BcPsFhwsCq = false;
      bool prdeTVjRZl = false;
      bool mclrOrlnUR = false;
      bool JqQHbbLVze = false;
      bool utVyRGMSLu = false;
      bool gjLKDYpWdM = false;
      bool uHYjgyaVCq = false;
      bool KNRuqrGnaH = false;
      bool eTbZkYfGDD = false;
      bool knrmimVkQS = false;
      bool fpQTjSSQTL = false;
      bool RCwVgbfyyH = false;
      bool SUSzGVUeLD = false;
      bool VVWHbnCIoS = false;
      bool GOmrkhrWFH = false;
      string NuCcMuKhRB;
      string sgDcrsGUcu;
      string SZdntWdcyk;
      string lemHpKHUIe;
      string pbyzhSQnkM;
      string fSAZLmQNho;
      string QgifOOtumg;
      string klMxEqbeFb;
      string GprkFTdMwC;
      string ttlSOJrRjT;
      string XUADbtFDVT;
      string LkIFiZoyau;
      string khzjmqzthu;
      string zJulEkonJL;
      string OapbqIkfin;
      string TtqohoVQQj;
      string tLVaUCpWBy;
      string kAnOfJqWsd;
      string GTKsaFSGDO;
      string PYXZRCFPHn;
      if(NuCcMuKhRB == XUADbtFDVT){ROekDSGbIX = true;}
      else if(XUADbtFDVT == NuCcMuKhRB){gjLKDYpWdM = true;}
      if(sgDcrsGUcu == LkIFiZoyau){yyWldaBbzO = true;}
      else if(LkIFiZoyau == sgDcrsGUcu){uHYjgyaVCq = true;}
      if(SZdntWdcyk == khzjmqzthu){ijSliLcNxd = true;}
      else if(khzjmqzthu == SZdntWdcyk){KNRuqrGnaH = true;}
      if(lemHpKHUIe == zJulEkonJL){EbOEMqnYoH = true;}
      else if(zJulEkonJL == lemHpKHUIe){eTbZkYfGDD = true;}
      if(pbyzhSQnkM == OapbqIkfin){zqxeQQCkwp = true;}
      else if(OapbqIkfin == pbyzhSQnkM){knrmimVkQS = true;}
      if(fSAZLmQNho == TtqohoVQQj){BcPsFhwsCq = true;}
      else if(TtqohoVQQj == fSAZLmQNho){fpQTjSSQTL = true;}
      if(QgifOOtumg == tLVaUCpWBy){prdeTVjRZl = true;}
      else if(tLVaUCpWBy == QgifOOtumg){RCwVgbfyyH = true;}
      if(klMxEqbeFb == kAnOfJqWsd){mclrOrlnUR = true;}
      if(GprkFTdMwC == GTKsaFSGDO){JqQHbbLVze = true;}
      if(ttlSOJrRjT == PYXZRCFPHn){utVyRGMSLu = true;}
      while(kAnOfJqWsd == klMxEqbeFb){SUSzGVUeLD = true;}
      while(GTKsaFSGDO == GTKsaFSGDO){VVWHbnCIoS = true;}
      while(PYXZRCFPHn == PYXZRCFPHn){GOmrkhrWFH = true;}
      if(ROekDSGbIX == true){ROekDSGbIX = false;}
      if(yyWldaBbzO == true){yyWldaBbzO = false;}
      if(ijSliLcNxd == true){ijSliLcNxd = false;}
      if(EbOEMqnYoH == true){EbOEMqnYoH = false;}
      if(zqxeQQCkwp == true){zqxeQQCkwp = false;}
      if(BcPsFhwsCq == true){BcPsFhwsCq = false;}
      if(prdeTVjRZl == true){prdeTVjRZl = false;}
      if(mclrOrlnUR == true){mclrOrlnUR = false;}
      if(JqQHbbLVze == true){JqQHbbLVze = false;}
      if(utVyRGMSLu == true){utVyRGMSLu = false;}
      if(gjLKDYpWdM == true){gjLKDYpWdM = false;}
      if(uHYjgyaVCq == true){uHYjgyaVCq = false;}
      if(KNRuqrGnaH == true){KNRuqrGnaH = false;}
      if(eTbZkYfGDD == true){eTbZkYfGDD = false;}
      if(knrmimVkQS == true){knrmimVkQS = false;}
      if(fpQTjSSQTL == true){fpQTjSSQTL = false;}
      if(RCwVgbfyyH == true){RCwVgbfyyH = false;}
      if(SUSzGVUeLD == true){SUSzGVUeLD = false;}
      if(VVWHbnCIoS == true){VVWHbnCIoS = false;}
      if(GOmrkhrWFH == true){GOmrkhrWFH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WROZWJCKRC
{ 
  void qjuccXzzNm()
  { 
      bool QQSLSoWhlq = false;
      bool NKVuoNgNBJ = false;
      bool rwnTrfHeMk = false;
      bool KlRJjFTxXG = false;
      bool sScGgIRlrH = false;
      bool YmaOlUcySl = false;
      bool hrVBgarLKi = false;
      bool tjptQYSgmi = false;
      bool OVlEMXLCWO = false;
      bool bVdkYBwbZF = false;
      bool QFaJNnxfyN = false;
      bool BuKiXMFRoI = false;
      bool PoowGXFFVP = false;
      bool cqHhSItcqX = false;
      bool aeEJMgLtML = false;
      bool uelQobPeCo = false;
      bool irJhjKmbQO = false;
      bool RbZRhjjfiZ = false;
      bool MLrKUxEqrq = false;
      bool sPaBniVWYC = false;
      string uiyAURKKja;
      string zcJbAORjQq;
      string MyYohZincq;
      string Xxsqfpzhzk;
      string TWMRUyLQjA;
      string CGMuPxKISu;
      string hWhrDBjRuJ;
      string PijeXolGUi;
      string NRDcoQkxai;
      string fpPECxoTOT;
      string NsVZjTVgXa;
      string LDmigPSFDl;
      string PmqLdYSfca;
      string ARrBUUwdrV;
      string uEYzXcCfWl;
      string djQcDaBJwK;
      string AoDxasLlNL;
      string ToMhpLNqnB;
      string VlIpwQBPyt;
      string SmggVFAbYe;
      if(uiyAURKKja == NsVZjTVgXa){QQSLSoWhlq = true;}
      else if(NsVZjTVgXa == uiyAURKKja){QFaJNnxfyN = true;}
      if(zcJbAORjQq == LDmigPSFDl){NKVuoNgNBJ = true;}
      else if(LDmigPSFDl == zcJbAORjQq){BuKiXMFRoI = true;}
      if(MyYohZincq == PmqLdYSfca){rwnTrfHeMk = true;}
      else if(PmqLdYSfca == MyYohZincq){PoowGXFFVP = true;}
      if(Xxsqfpzhzk == ARrBUUwdrV){KlRJjFTxXG = true;}
      else if(ARrBUUwdrV == Xxsqfpzhzk){cqHhSItcqX = true;}
      if(TWMRUyLQjA == uEYzXcCfWl){sScGgIRlrH = true;}
      else if(uEYzXcCfWl == TWMRUyLQjA){aeEJMgLtML = true;}
      if(CGMuPxKISu == djQcDaBJwK){YmaOlUcySl = true;}
      else if(djQcDaBJwK == CGMuPxKISu){uelQobPeCo = true;}
      if(hWhrDBjRuJ == AoDxasLlNL){hrVBgarLKi = true;}
      else if(AoDxasLlNL == hWhrDBjRuJ){irJhjKmbQO = true;}
      if(PijeXolGUi == ToMhpLNqnB){tjptQYSgmi = true;}
      if(NRDcoQkxai == VlIpwQBPyt){OVlEMXLCWO = true;}
      if(fpPECxoTOT == SmggVFAbYe){bVdkYBwbZF = true;}
      while(ToMhpLNqnB == PijeXolGUi){RbZRhjjfiZ = true;}
      while(VlIpwQBPyt == VlIpwQBPyt){MLrKUxEqrq = true;}
      while(SmggVFAbYe == SmggVFAbYe){sPaBniVWYC = true;}
      if(QQSLSoWhlq == true){QQSLSoWhlq = false;}
      if(NKVuoNgNBJ == true){NKVuoNgNBJ = false;}
      if(rwnTrfHeMk == true){rwnTrfHeMk = false;}
      if(KlRJjFTxXG == true){KlRJjFTxXG = false;}
      if(sScGgIRlrH == true){sScGgIRlrH = false;}
      if(YmaOlUcySl == true){YmaOlUcySl = false;}
      if(hrVBgarLKi == true){hrVBgarLKi = false;}
      if(tjptQYSgmi == true){tjptQYSgmi = false;}
      if(OVlEMXLCWO == true){OVlEMXLCWO = false;}
      if(bVdkYBwbZF == true){bVdkYBwbZF = false;}
      if(QFaJNnxfyN == true){QFaJNnxfyN = false;}
      if(BuKiXMFRoI == true){BuKiXMFRoI = false;}
      if(PoowGXFFVP == true){PoowGXFFVP = false;}
      if(cqHhSItcqX == true){cqHhSItcqX = false;}
      if(aeEJMgLtML == true){aeEJMgLtML = false;}
      if(uelQobPeCo == true){uelQobPeCo = false;}
      if(irJhjKmbQO == true){irJhjKmbQO = false;}
      if(RbZRhjjfiZ == true){RbZRhjjfiZ = false;}
      if(MLrKUxEqrq == true){MLrKUxEqrq = false;}
      if(sPaBniVWYC == true){sPaBniVWYC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUCUZEIJBH
{ 
  void QIDyVGyyIc()
  { 
      bool zQZZjaDfPA = false;
      bool aVbKGctwpu = false;
      bool WalLgugeix = false;
      bool WXTENkIxiy = false;
      bool RpidQoJCNM = false;
      bool mEbNTXeOsn = false;
      bool sXxRdCCXwU = false;
      bool TxMrcfqIuq = false;
      bool keRVJRwGjp = false;
      bool GtEtEtsQAN = false;
      bool mlGrspqjjm = false;
      bool fVSBCOFbIL = false;
      bool GwmGOYsSmh = false;
      bool maIgDzXZcT = false;
      bool aMVxJjaCro = false;
      bool nQInHqyAcT = false;
      bool xYwCzFNlyD = false;
      bool pfzojsZpwe = false;
      bool xqaxsWRTYM = false;
      bool AXwIVCPSxD = false;
      string TdHNcNVpFH;
      string OQQdYPEkIZ;
      string ZnkbDTIsuE;
      string VKACnofAcO;
      string cXgNOFLtwa;
      string cOtHoeseKJ;
      string FbtBlDQNpj;
      string jDItwBHWMx;
      string HNxTaGQsMI;
      string wApTJAdebK;
      string oyELqYGAKn;
      string WVSMBqeaZf;
      string mXAgniNoku;
      string XbuBIJJkbB;
      string zPhYlZgdRR;
      string VCEwXQxWXI;
      string LRPPQtaQDr;
      string htzXfWpbuN;
      string BiWSZVWzdq;
      string LlMTohARIq;
      if(TdHNcNVpFH == oyELqYGAKn){zQZZjaDfPA = true;}
      else if(oyELqYGAKn == TdHNcNVpFH){mlGrspqjjm = true;}
      if(OQQdYPEkIZ == WVSMBqeaZf){aVbKGctwpu = true;}
      else if(WVSMBqeaZf == OQQdYPEkIZ){fVSBCOFbIL = true;}
      if(ZnkbDTIsuE == mXAgniNoku){WalLgugeix = true;}
      else if(mXAgniNoku == ZnkbDTIsuE){GwmGOYsSmh = true;}
      if(VKACnofAcO == XbuBIJJkbB){WXTENkIxiy = true;}
      else if(XbuBIJJkbB == VKACnofAcO){maIgDzXZcT = true;}
      if(cXgNOFLtwa == zPhYlZgdRR){RpidQoJCNM = true;}
      else if(zPhYlZgdRR == cXgNOFLtwa){aMVxJjaCro = true;}
      if(cOtHoeseKJ == VCEwXQxWXI){mEbNTXeOsn = true;}
      else if(VCEwXQxWXI == cOtHoeseKJ){nQInHqyAcT = true;}
      if(FbtBlDQNpj == LRPPQtaQDr){sXxRdCCXwU = true;}
      else if(LRPPQtaQDr == FbtBlDQNpj){xYwCzFNlyD = true;}
      if(jDItwBHWMx == htzXfWpbuN){TxMrcfqIuq = true;}
      if(HNxTaGQsMI == BiWSZVWzdq){keRVJRwGjp = true;}
      if(wApTJAdebK == LlMTohARIq){GtEtEtsQAN = true;}
      while(htzXfWpbuN == jDItwBHWMx){pfzojsZpwe = true;}
      while(BiWSZVWzdq == BiWSZVWzdq){xqaxsWRTYM = true;}
      while(LlMTohARIq == LlMTohARIq){AXwIVCPSxD = true;}
      if(zQZZjaDfPA == true){zQZZjaDfPA = false;}
      if(aVbKGctwpu == true){aVbKGctwpu = false;}
      if(WalLgugeix == true){WalLgugeix = false;}
      if(WXTENkIxiy == true){WXTENkIxiy = false;}
      if(RpidQoJCNM == true){RpidQoJCNM = false;}
      if(mEbNTXeOsn == true){mEbNTXeOsn = false;}
      if(sXxRdCCXwU == true){sXxRdCCXwU = false;}
      if(TxMrcfqIuq == true){TxMrcfqIuq = false;}
      if(keRVJRwGjp == true){keRVJRwGjp = false;}
      if(GtEtEtsQAN == true){GtEtEtsQAN = false;}
      if(mlGrspqjjm == true){mlGrspqjjm = false;}
      if(fVSBCOFbIL == true){fVSBCOFbIL = false;}
      if(GwmGOYsSmh == true){GwmGOYsSmh = false;}
      if(maIgDzXZcT == true){maIgDzXZcT = false;}
      if(aMVxJjaCro == true){aMVxJjaCro = false;}
      if(nQInHqyAcT == true){nQInHqyAcT = false;}
      if(xYwCzFNlyD == true){xYwCzFNlyD = false;}
      if(pfzojsZpwe == true){pfzojsZpwe = false;}
      if(xqaxsWRTYM == true){xqaxsWRTYM = false;}
      if(AXwIVCPSxD == true){AXwIVCPSxD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSBNLVJGES
{ 
  void nGGUfGMWfj()
  { 
      bool efzTjitxaf = false;
      bool EKDXDOnQok = false;
      bool LFlxZYmbaU = false;
      bool ftlVCBwUuI = false;
      bool OTzNaVkIZh = false;
      bool ZqrXxZtCtK = false;
      bool uSWFAKYgVB = false;
      bool RSVfVqFXVE = false;
      bool neBsunBOYb = false;
      bool HsajMwxsNQ = false;
      bool wEmYPGVMBF = false;
      bool UVgpWQRcKL = false;
      bool JKIttXrkSZ = false;
      bool tLKFHjqccn = false;
      bool SnMSHkMkNw = false;
      bool eTiBGlusdr = false;
      bool NjsbKIKbim = false;
      bool YnAVrUxolI = false;
      bool LHWWuabJyV = false;
      bool nyykahukIy = false;
      string MHeLwuuhwc;
      string sLDQcVloHO;
      string KLWLlJlCUX;
      string OUdsAKXrGs;
      string FgYAkDPOQb;
      string ecoliBkSYm;
      string IsMXOYgJPS;
      string ysiOIdlVZi;
      string sWkrslfrJz;
      string ZETTjMTAlM;
      string VGzydksacF;
      string OOspslHTeb;
      string sozQrsZPdw;
      string JljNMmXmOH;
      string rEOEkKLcZy;
      string EAUJTfGiFk;
      string LdwgubeecG;
      string OUFXinaueh;
      string gwofrJQZsf;
      string fogdwOIgII;
      if(MHeLwuuhwc == VGzydksacF){efzTjitxaf = true;}
      else if(VGzydksacF == MHeLwuuhwc){wEmYPGVMBF = true;}
      if(sLDQcVloHO == OOspslHTeb){EKDXDOnQok = true;}
      else if(OOspslHTeb == sLDQcVloHO){UVgpWQRcKL = true;}
      if(KLWLlJlCUX == sozQrsZPdw){LFlxZYmbaU = true;}
      else if(sozQrsZPdw == KLWLlJlCUX){JKIttXrkSZ = true;}
      if(OUdsAKXrGs == JljNMmXmOH){ftlVCBwUuI = true;}
      else if(JljNMmXmOH == OUdsAKXrGs){tLKFHjqccn = true;}
      if(FgYAkDPOQb == rEOEkKLcZy){OTzNaVkIZh = true;}
      else if(rEOEkKLcZy == FgYAkDPOQb){SnMSHkMkNw = true;}
      if(ecoliBkSYm == EAUJTfGiFk){ZqrXxZtCtK = true;}
      else if(EAUJTfGiFk == ecoliBkSYm){eTiBGlusdr = true;}
      if(IsMXOYgJPS == LdwgubeecG){uSWFAKYgVB = true;}
      else if(LdwgubeecG == IsMXOYgJPS){NjsbKIKbim = true;}
      if(ysiOIdlVZi == OUFXinaueh){RSVfVqFXVE = true;}
      if(sWkrslfrJz == gwofrJQZsf){neBsunBOYb = true;}
      if(ZETTjMTAlM == fogdwOIgII){HsajMwxsNQ = true;}
      while(OUFXinaueh == ysiOIdlVZi){YnAVrUxolI = true;}
      while(gwofrJQZsf == gwofrJQZsf){LHWWuabJyV = true;}
      while(fogdwOIgII == fogdwOIgII){nyykahukIy = true;}
      if(efzTjitxaf == true){efzTjitxaf = false;}
      if(EKDXDOnQok == true){EKDXDOnQok = false;}
      if(LFlxZYmbaU == true){LFlxZYmbaU = false;}
      if(ftlVCBwUuI == true){ftlVCBwUuI = false;}
      if(OTzNaVkIZh == true){OTzNaVkIZh = false;}
      if(ZqrXxZtCtK == true){ZqrXxZtCtK = false;}
      if(uSWFAKYgVB == true){uSWFAKYgVB = false;}
      if(RSVfVqFXVE == true){RSVfVqFXVE = false;}
      if(neBsunBOYb == true){neBsunBOYb = false;}
      if(HsajMwxsNQ == true){HsajMwxsNQ = false;}
      if(wEmYPGVMBF == true){wEmYPGVMBF = false;}
      if(UVgpWQRcKL == true){UVgpWQRcKL = false;}
      if(JKIttXrkSZ == true){JKIttXrkSZ = false;}
      if(tLKFHjqccn == true){tLKFHjqccn = false;}
      if(SnMSHkMkNw == true){SnMSHkMkNw = false;}
      if(eTiBGlusdr == true){eTiBGlusdr = false;}
      if(NjsbKIKbim == true){NjsbKIKbim = false;}
      if(YnAVrUxolI == true){YnAVrUxolI = false;}
      if(LHWWuabJyV == true){LHWWuabJyV = false;}
      if(nyykahukIy == true){nyykahukIy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CNLBFWGCYT
{ 
  void MqscwtNmcR()
  { 
      bool nZXbazKcxw = false;
      bool rTYRQXsSyl = false;
      bool jtVUFHibbB = false;
      bool LRsqnuCJwh = false;
      bool DlhTNcxaPF = false;
      bool gGpnhtDDWT = false;
      bool QiAwjaZhcU = false;
      bool VjWPhxMBGb = false;
      bool JILVTFaFIt = false;
      bool qzlcRUkljm = false;
      bool DPxtjwiaFj = false;
      bool gCwtJIWebd = false;
      bool zUYhcVxtyN = false;
      bool MaRTYsKRkX = false;
      bool VAzYMoDrSI = false;
      bool yGJFmhqORO = false;
      bool zocrXGkbUP = false;
      bool yFsEIzUAVn = false;
      bool SEaoOFQMgq = false;
      bool CuzVYgXHAF = false;
      string ieOIQwmtRI;
      string wmdPSmzIrc;
      string nUryuIEzff;
      string cNAXcgLtZd;
      string dJEiRNotYt;
      string edfoNOmQNH;
      string qnNkehmFml;
      string bFiOydQIgg;
      string TJZlBzgLKN;
      string sufSlouSEi;
      string aiGmSYuRpi;
      string xejgmgObif;
      string BbuYrfZPbJ;
      string hyEyFkDmSc;
      string EPUaQOLzeE;
      string aTiYhzngtl;
      string yepfAzZlaC;
      string daIGakGTIc;
      string UakWhOOfPG;
      string xVrgdZYnZR;
      if(ieOIQwmtRI == aiGmSYuRpi){nZXbazKcxw = true;}
      else if(aiGmSYuRpi == ieOIQwmtRI){DPxtjwiaFj = true;}
      if(wmdPSmzIrc == xejgmgObif){rTYRQXsSyl = true;}
      else if(xejgmgObif == wmdPSmzIrc){gCwtJIWebd = true;}
      if(nUryuIEzff == BbuYrfZPbJ){jtVUFHibbB = true;}
      else if(BbuYrfZPbJ == nUryuIEzff){zUYhcVxtyN = true;}
      if(cNAXcgLtZd == hyEyFkDmSc){LRsqnuCJwh = true;}
      else if(hyEyFkDmSc == cNAXcgLtZd){MaRTYsKRkX = true;}
      if(dJEiRNotYt == EPUaQOLzeE){DlhTNcxaPF = true;}
      else if(EPUaQOLzeE == dJEiRNotYt){VAzYMoDrSI = true;}
      if(edfoNOmQNH == aTiYhzngtl){gGpnhtDDWT = true;}
      else if(aTiYhzngtl == edfoNOmQNH){yGJFmhqORO = true;}
      if(qnNkehmFml == yepfAzZlaC){QiAwjaZhcU = true;}
      else if(yepfAzZlaC == qnNkehmFml){zocrXGkbUP = true;}
      if(bFiOydQIgg == daIGakGTIc){VjWPhxMBGb = true;}
      if(TJZlBzgLKN == UakWhOOfPG){JILVTFaFIt = true;}
      if(sufSlouSEi == xVrgdZYnZR){qzlcRUkljm = true;}
      while(daIGakGTIc == bFiOydQIgg){yFsEIzUAVn = true;}
      while(UakWhOOfPG == UakWhOOfPG){SEaoOFQMgq = true;}
      while(xVrgdZYnZR == xVrgdZYnZR){CuzVYgXHAF = true;}
      if(nZXbazKcxw == true){nZXbazKcxw = false;}
      if(rTYRQXsSyl == true){rTYRQXsSyl = false;}
      if(jtVUFHibbB == true){jtVUFHibbB = false;}
      if(LRsqnuCJwh == true){LRsqnuCJwh = false;}
      if(DlhTNcxaPF == true){DlhTNcxaPF = false;}
      if(gGpnhtDDWT == true){gGpnhtDDWT = false;}
      if(QiAwjaZhcU == true){QiAwjaZhcU = false;}
      if(VjWPhxMBGb == true){VjWPhxMBGb = false;}
      if(JILVTFaFIt == true){JILVTFaFIt = false;}
      if(qzlcRUkljm == true){qzlcRUkljm = false;}
      if(DPxtjwiaFj == true){DPxtjwiaFj = false;}
      if(gCwtJIWebd == true){gCwtJIWebd = false;}
      if(zUYhcVxtyN == true){zUYhcVxtyN = false;}
      if(MaRTYsKRkX == true){MaRTYsKRkX = false;}
      if(VAzYMoDrSI == true){VAzYMoDrSI = false;}
      if(yGJFmhqORO == true){yGJFmhqORO = false;}
      if(zocrXGkbUP == true){zocrXGkbUP = false;}
      if(yFsEIzUAVn == true){yFsEIzUAVn = false;}
      if(SEaoOFQMgq == true){SEaoOFQMgq = false;}
      if(CuzVYgXHAF == true){CuzVYgXHAF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLRFVBPOGE
{ 
  void APHURiQPmw()
  { 
      bool AKYQrjSWSA = false;
      bool FgiCiynTVs = false;
      bool PmDpVYmbXo = false;
      bool cMzOwkKzmX = false;
      bool nspFmfPoje = false;
      bool wJiIoMHiuS = false;
      bool wqzcXrhTGx = false;
      bool mofyEWwyCo = false;
      bool IxqrsScpZi = false;
      bool dbETaxsMgt = false;
      bool ywimrHdjER = false;
      bool QIfFKzzGjE = false;
      bool PrtWTKkLXH = false;
      bool diQHpLNEAk = false;
      bool orlHRUuyJa = false;
      bool ylcceGCMSg = false;
      bool VSMwngrYPy = false;
      bool ktGyPWFlEy = false;
      bool PmCwJqGncj = false;
      bool JBkTOVfoTj = false;
      string ARXmWaZjHG;
      string NgJMCWpwUD;
      string bHCzzFkSwJ;
      string dGudzMPsyg;
      string twhmwKTXhC;
      string XSiKCsPYmR;
      string oHnybGlfMp;
      string GxxnJeYOCo;
      string kNjtkLXjaG;
      string wpFgrmIjLp;
      string YnKruZUuAX;
      string UAVyfbWtMQ;
      string iBEGsQqQwW;
      string WnDMPxDqyL;
      string pbiDlwTHAQ;
      string POXtGWiDze;
      string hEzdBfwJhi;
      string XeuAaGRBUw;
      string wjPfHHPJFr;
      string NzrSckcFCF;
      if(ARXmWaZjHG == YnKruZUuAX){AKYQrjSWSA = true;}
      else if(YnKruZUuAX == ARXmWaZjHG){ywimrHdjER = true;}
      if(NgJMCWpwUD == UAVyfbWtMQ){FgiCiynTVs = true;}
      else if(UAVyfbWtMQ == NgJMCWpwUD){QIfFKzzGjE = true;}
      if(bHCzzFkSwJ == iBEGsQqQwW){PmDpVYmbXo = true;}
      else if(iBEGsQqQwW == bHCzzFkSwJ){PrtWTKkLXH = true;}
      if(dGudzMPsyg == WnDMPxDqyL){cMzOwkKzmX = true;}
      else if(WnDMPxDqyL == dGudzMPsyg){diQHpLNEAk = true;}
      if(twhmwKTXhC == pbiDlwTHAQ){nspFmfPoje = true;}
      else if(pbiDlwTHAQ == twhmwKTXhC){orlHRUuyJa = true;}
      if(XSiKCsPYmR == POXtGWiDze){wJiIoMHiuS = true;}
      else if(POXtGWiDze == XSiKCsPYmR){ylcceGCMSg = true;}
      if(oHnybGlfMp == hEzdBfwJhi){wqzcXrhTGx = true;}
      else if(hEzdBfwJhi == oHnybGlfMp){VSMwngrYPy = true;}
      if(GxxnJeYOCo == XeuAaGRBUw){mofyEWwyCo = true;}
      if(kNjtkLXjaG == wjPfHHPJFr){IxqrsScpZi = true;}
      if(wpFgrmIjLp == NzrSckcFCF){dbETaxsMgt = true;}
      while(XeuAaGRBUw == GxxnJeYOCo){ktGyPWFlEy = true;}
      while(wjPfHHPJFr == wjPfHHPJFr){PmCwJqGncj = true;}
      while(NzrSckcFCF == NzrSckcFCF){JBkTOVfoTj = true;}
      if(AKYQrjSWSA == true){AKYQrjSWSA = false;}
      if(FgiCiynTVs == true){FgiCiynTVs = false;}
      if(PmDpVYmbXo == true){PmDpVYmbXo = false;}
      if(cMzOwkKzmX == true){cMzOwkKzmX = false;}
      if(nspFmfPoje == true){nspFmfPoje = false;}
      if(wJiIoMHiuS == true){wJiIoMHiuS = false;}
      if(wqzcXrhTGx == true){wqzcXrhTGx = false;}
      if(mofyEWwyCo == true){mofyEWwyCo = false;}
      if(IxqrsScpZi == true){IxqrsScpZi = false;}
      if(dbETaxsMgt == true){dbETaxsMgt = false;}
      if(ywimrHdjER == true){ywimrHdjER = false;}
      if(QIfFKzzGjE == true){QIfFKzzGjE = false;}
      if(PrtWTKkLXH == true){PrtWTKkLXH = false;}
      if(diQHpLNEAk == true){diQHpLNEAk = false;}
      if(orlHRUuyJa == true){orlHRUuyJa = false;}
      if(ylcceGCMSg == true){ylcceGCMSg = false;}
      if(VSMwngrYPy == true){VSMwngrYPy = false;}
      if(ktGyPWFlEy == true){ktGyPWFlEy = false;}
      if(PmCwJqGncj == true){PmCwJqGncj = false;}
      if(JBkTOVfoTj == true){JBkTOVfoTj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCMUSHPFFH
{ 
  void cIyTQUhbqu()
  { 
      bool wSrOozffbz = false;
      bool KfZVTGbnMW = false;
      bool FwqYpsHTHD = false;
      bool IpwoJrfabH = false;
      bool eaTepwQhQr = false;
      bool zuLYmAaSYw = false;
      bool qMYYpUjjMb = false;
      bool aBMFrdbLis = false;
      bool bZDODNeWBI = false;
      bool QMBfQSBunV = false;
      bool LfVoRxhFgI = false;
      bool XPjeTRIKUc = false;
      bool pMhDLOzfnY = false;
      bool cfXMgwDNxF = false;
      bool eYpskBbWMy = false;
      bool JqaKfzxRdC = false;
      bool xCRHfqqWxW = false;
      bool NuMOyQVoSJ = false;
      bool lcToPkFNgh = false;
      bool yljtHbHiMs = false;
      string DESolOyLUC;
      string qjbnsmqlYa;
      string acYieWnCxi;
      string tZuumPMeOe;
      string BVKnpWauzE;
      string iLoNkafiJO;
      string ZuOlHRogAd;
      string aMWtYESjsI;
      string usCsAhjgKM;
      string jcUAEFHXgX;
      string gtuVcVnunf;
      string HupBSgsVkY;
      string gHVmtyqWoT;
      string xtDUaAxfPd;
      string tosdFnmSgX;
      string LlmHqZXHbe;
      string eRFUhMrUaS;
      string iMFGerOrhF;
      string KXoQHLHwdB;
      string bpEkzbiYur;
      if(DESolOyLUC == gtuVcVnunf){wSrOozffbz = true;}
      else if(gtuVcVnunf == DESolOyLUC){LfVoRxhFgI = true;}
      if(qjbnsmqlYa == HupBSgsVkY){KfZVTGbnMW = true;}
      else if(HupBSgsVkY == qjbnsmqlYa){XPjeTRIKUc = true;}
      if(acYieWnCxi == gHVmtyqWoT){FwqYpsHTHD = true;}
      else if(gHVmtyqWoT == acYieWnCxi){pMhDLOzfnY = true;}
      if(tZuumPMeOe == xtDUaAxfPd){IpwoJrfabH = true;}
      else if(xtDUaAxfPd == tZuumPMeOe){cfXMgwDNxF = true;}
      if(BVKnpWauzE == tosdFnmSgX){eaTepwQhQr = true;}
      else if(tosdFnmSgX == BVKnpWauzE){eYpskBbWMy = true;}
      if(iLoNkafiJO == LlmHqZXHbe){zuLYmAaSYw = true;}
      else if(LlmHqZXHbe == iLoNkafiJO){JqaKfzxRdC = true;}
      if(ZuOlHRogAd == eRFUhMrUaS){qMYYpUjjMb = true;}
      else if(eRFUhMrUaS == ZuOlHRogAd){xCRHfqqWxW = true;}
      if(aMWtYESjsI == iMFGerOrhF){aBMFrdbLis = true;}
      if(usCsAhjgKM == KXoQHLHwdB){bZDODNeWBI = true;}
      if(jcUAEFHXgX == bpEkzbiYur){QMBfQSBunV = true;}
      while(iMFGerOrhF == aMWtYESjsI){NuMOyQVoSJ = true;}
      while(KXoQHLHwdB == KXoQHLHwdB){lcToPkFNgh = true;}
      while(bpEkzbiYur == bpEkzbiYur){yljtHbHiMs = true;}
      if(wSrOozffbz == true){wSrOozffbz = false;}
      if(KfZVTGbnMW == true){KfZVTGbnMW = false;}
      if(FwqYpsHTHD == true){FwqYpsHTHD = false;}
      if(IpwoJrfabH == true){IpwoJrfabH = false;}
      if(eaTepwQhQr == true){eaTepwQhQr = false;}
      if(zuLYmAaSYw == true){zuLYmAaSYw = false;}
      if(qMYYpUjjMb == true){qMYYpUjjMb = false;}
      if(aBMFrdbLis == true){aBMFrdbLis = false;}
      if(bZDODNeWBI == true){bZDODNeWBI = false;}
      if(QMBfQSBunV == true){QMBfQSBunV = false;}
      if(LfVoRxhFgI == true){LfVoRxhFgI = false;}
      if(XPjeTRIKUc == true){XPjeTRIKUc = false;}
      if(pMhDLOzfnY == true){pMhDLOzfnY = false;}
      if(cfXMgwDNxF == true){cfXMgwDNxF = false;}
      if(eYpskBbWMy == true){eYpskBbWMy = false;}
      if(JqaKfzxRdC == true){JqaKfzxRdC = false;}
      if(xCRHfqqWxW == true){xCRHfqqWxW = false;}
      if(NuMOyQVoSJ == true){NuMOyQVoSJ = false;}
      if(lcToPkFNgh == true){lcToPkFNgh = false;}
      if(yljtHbHiMs == true){yljtHbHiMs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUDWAIVNBV
{ 
  void wkBfkfVQBq()
  { 
      bool bwnLejYwCr = false;
      bool HDfDjtiRVx = false;
      bool oLGNCqqfbj = false;
      bool puPZXcuBiL = false;
      bool SjkXhDoJsR = false;
      bool LSARQQoZIm = false;
      bool rrTRBMmFeG = false;
      bool zhhJdEahez = false;
      bool ChmKXXuyIH = false;
      bool mUruSaQSWV = false;
      bool PielSdjpmM = false;
      bool pHtJkKFIsd = false;
      bool RowWSdplpD = false;
      bool nHLJiTCArt = false;
      bool mEKwQfZhKH = false;
      bool UHZsEalHSn = false;
      bool nxzjXiukaR = false;
      bool HEQypMdAGm = false;
      bool DHbihggSFI = false;
      bool guhDFoEaXh = false;
      string lOxUanTwEm;
      string UknCKuAVXa;
      string RSUwMXrALg;
      string wbplgnaQVh;
      string eOmuCWSoCW;
      string mcaASSsAHD;
      string wSkXprtBUW;
      string TizpwDfZsp;
      string FCxosTBpSN;
      string taISkLdOEK;
      string bQTfCDckDO;
      string lTGRytVudW;
      string qDhHbsZgEk;
      string ZQUiNohQlo;
      string qQmDaaTqUq;
      string ohkhSXhMEJ;
      string cufRoUyWDJ;
      string MEJnfaQefA;
      string ZiMNwrfmQp;
      string GUMcLujVOF;
      if(lOxUanTwEm == bQTfCDckDO){bwnLejYwCr = true;}
      else if(bQTfCDckDO == lOxUanTwEm){PielSdjpmM = true;}
      if(UknCKuAVXa == lTGRytVudW){HDfDjtiRVx = true;}
      else if(lTGRytVudW == UknCKuAVXa){pHtJkKFIsd = true;}
      if(RSUwMXrALg == qDhHbsZgEk){oLGNCqqfbj = true;}
      else if(qDhHbsZgEk == RSUwMXrALg){RowWSdplpD = true;}
      if(wbplgnaQVh == ZQUiNohQlo){puPZXcuBiL = true;}
      else if(ZQUiNohQlo == wbplgnaQVh){nHLJiTCArt = true;}
      if(eOmuCWSoCW == qQmDaaTqUq){SjkXhDoJsR = true;}
      else if(qQmDaaTqUq == eOmuCWSoCW){mEKwQfZhKH = true;}
      if(mcaASSsAHD == ohkhSXhMEJ){LSARQQoZIm = true;}
      else if(ohkhSXhMEJ == mcaASSsAHD){UHZsEalHSn = true;}
      if(wSkXprtBUW == cufRoUyWDJ){rrTRBMmFeG = true;}
      else if(cufRoUyWDJ == wSkXprtBUW){nxzjXiukaR = true;}
      if(TizpwDfZsp == MEJnfaQefA){zhhJdEahez = true;}
      if(FCxosTBpSN == ZiMNwrfmQp){ChmKXXuyIH = true;}
      if(taISkLdOEK == GUMcLujVOF){mUruSaQSWV = true;}
      while(MEJnfaQefA == TizpwDfZsp){HEQypMdAGm = true;}
      while(ZiMNwrfmQp == ZiMNwrfmQp){DHbihggSFI = true;}
      while(GUMcLujVOF == GUMcLujVOF){guhDFoEaXh = true;}
      if(bwnLejYwCr == true){bwnLejYwCr = false;}
      if(HDfDjtiRVx == true){HDfDjtiRVx = false;}
      if(oLGNCqqfbj == true){oLGNCqqfbj = false;}
      if(puPZXcuBiL == true){puPZXcuBiL = false;}
      if(SjkXhDoJsR == true){SjkXhDoJsR = false;}
      if(LSARQQoZIm == true){LSARQQoZIm = false;}
      if(rrTRBMmFeG == true){rrTRBMmFeG = false;}
      if(zhhJdEahez == true){zhhJdEahez = false;}
      if(ChmKXXuyIH == true){ChmKXXuyIH = false;}
      if(mUruSaQSWV == true){mUruSaQSWV = false;}
      if(PielSdjpmM == true){PielSdjpmM = false;}
      if(pHtJkKFIsd == true){pHtJkKFIsd = false;}
      if(RowWSdplpD == true){RowWSdplpD = false;}
      if(nHLJiTCArt == true){nHLJiTCArt = false;}
      if(mEKwQfZhKH == true){mEKwQfZhKH = false;}
      if(UHZsEalHSn == true){UHZsEalHSn = false;}
      if(nxzjXiukaR == true){nxzjXiukaR = false;}
      if(HEQypMdAGm == true){HEQypMdAGm = false;}
      if(DHbihggSFI == true){DHbihggSFI = false;}
      if(guhDFoEaXh == true){guhDFoEaXh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORYGZLMBEI
{ 
  void UVwPEFmybV()
  { 
      bool mYZGzqiwpt = false;
      bool wMLZoqbqRW = false;
      bool DcLkOzbznd = false;
      bool JgxRyNhjcm = false;
      bool iuKdBRbBVF = false;
      bool AbEwIJNnqA = false;
      bool OiHLjOOtba = false;
      bool JrOdmIRgjw = false;
      bool XadhchcBJn = false;
      bool AsrbYAmzsl = false;
      bool CgYuwIMZIz = false;
      bool qfEucnFZhC = false;
      bool lNkmZQzlFm = false;
      bool VSnytpBhlU = false;
      bool UCsJxUoxzj = false;
      bool tNQqzowlUf = false;
      bool IaTUdXrFBm = false;
      bool lWmNgiUapF = false;
      bool aCmUsICwzE = false;
      bool sPNGLtiXfY = false;
      string GkewMNGjeG;
      string ChByVzszjp;
      string ByHLyAsNaj;
      string zRWPkXKlKU;
      string ezKHZfooLO;
      string WwxhEIcTxL;
      string TrJuGkKkNx;
      string oGnPLCnzkR;
      string LEBMMDUoLb;
      string tqozBlpPAn;
      string UDaOZQHhVB;
      string TchfAOqwhD;
      string QVZlCxQoNZ;
      string LYyxwHcmmw;
      string umSJHRJJyl;
      string tsgxXzcoLb;
      string zSTwpudjir;
      string lDJkHcDQdk;
      string mHpbeSqBYx;
      string dmbKxcTVSM;
      if(GkewMNGjeG == UDaOZQHhVB){mYZGzqiwpt = true;}
      else if(UDaOZQHhVB == GkewMNGjeG){CgYuwIMZIz = true;}
      if(ChByVzszjp == TchfAOqwhD){wMLZoqbqRW = true;}
      else if(TchfAOqwhD == ChByVzszjp){qfEucnFZhC = true;}
      if(ByHLyAsNaj == QVZlCxQoNZ){DcLkOzbznd = true;}
      else if(QVZlCxQoNZ == ByHLyAsNaj){lNkmZQzlFm = true;}
      if(zRWPkXKlKU == LYyxwHcmmw){JgxRyNhjcm = true;}
      else if(LYyxwHcmmw == zRWPkXKlKU){VSnytpBhlU = true;}
      if(ezKHZfooLO == umSJHRJJyl){iuKdBRbBVF = true;}
      else if(umSJHRJJyl == ezKHZfooLO){UCsJxUoxzj = true;}
      if(WwxhEIcTxL == tsgxXzcoLb){AbEwIJNnqA = true;}
      else if(tsgxXzcoLb == WwxhEIcTxL){tNQqzowlUf = true;}
      if(TrJuGkKkNx == zSTwpudjir){OiHLjOOtba = true;}
      else if(zSTwpudjir == TrJuGkKkNx){IaTUdXrFBm = true;}
      if(oGnPLCnzkR == lDJkHcDQdk){JrOdmIRgjw = true;}
      if(LEBMMDUoLb == mHpbeSqBYx){XadhchcBJn = true;}
      if(tqozBlpPAn == dmbKxcTVSM){AsrbYAmzsl = true;}
      while(lDJkHcDQdk == oGnPLCnzkR){lWmNgiUapF = true;}
      while(mHpbeSqBYx == mHpbeSqBYx){aCmUsICwzE = true;}
      while(dmbKxcTVSM == dmbKxcTVSM){sPNGLtiXfY = true;}
      if(mYZGzqiwpt == true){mYZGzqiwpt = false;}
      if(wMLZoqbqRW == true){wMLZoqbqRW = false;}
      if(DcLkOzbznd == true){DcLkOzbznd = false;}
      if(JgxRyNhjcm == true){JgxRyNhjcm = false;}
      if(iuKdBRbBVF == true){iuKdBRbBVF = false;}
      if(AbEwIJNnqA == true){AbEwIJNnqA = false;}
      if(OiHLjOOtba == true){OiHLjOOtba = false;}
      if(JrOdmIRgjw == true){JrOdmIRgjw = false;}
      if(XadhchcBJn == true){XadhchcBJn = false;}
      if(AsrbYAmzsl == true){AsrbYAmzsl = false;}
      if(CgYuwIMZIz == true){CgYuwIMZIz = false;}
      if(qfEucnFZhC == true){qfEucnFZhC = false;}
      if(lNkmZQzlFm == true){lNkmZQzlFm = false;}
      if(VSnytpBhlU == true){VSnytpBhlU = false;}
      if(UCsJxUoxzj == true){UCsJxUoxzj = false;}
      if(tNQqzowlUf == true){tNQqzowlUf = false;}
      if(IaTUdXrFBm == true){IaTUdXrFBm = false;}
      if(lWmNgiUapF == true){lWmNgiUapF = false;}
      if(aCmUsICwzE == true){aCmUsICwzE = false;}
      if(sPNGLtiXfY == true){sPNGLtiXfY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TTIIESABYL
{ 
  void LzdYPOqzEu()
  { 
      bool GEdlmXTCaz = false;
      bool BtlFWxMmcV = false;
      bool dsaMPgNdoS = false;
      bool HQlYhWuUbI = false;
      bool WwZdhyNiaT = false;
      bool zwrshNdRWF = false;
      bool JoMHrkIMXz = false;
      bool BrLUzhTwdR = false;
      bool TeDUTKXspU = false;
      bool rdyVygiRlw = false;
      bool pBKaSHkXtA = false;
      bool shmFlelrng = false;
      bool MOVDGWsoVR = false;
      bool yBKhbRTbCM = false;
      bool YAzpaKqsjT = false;
      bool tqdEiaeGUu = false;
      bool NwBbCrWEcT = false;
      bool KKpaIMPfcu = false;
      bool fzECWGWFyA = false;
      bool mMHHycyXmh = false;
      string ekaqJBChnq;
      string PkcgTLoEEm;
      string YdKNstaufe;
      string YNaZcbtsIy;
      string TVPkXOdDaA;
      string RTphBAaNyO;
      string aGCIRBJCEq;
      string QuwFTDOZpd;
      string QWTeMFWsYb;
      string BgusXNSGSV;
      string FazjiWXjOx;
      string lAXUyEmXwM;
      string dQdbojzChG;
      string kIGTXpWjwo;
      string gmdbpAIZuT;
      string ZuJGqnwXty;
      string WUCIMctDwI;
      string gCaHeqlCln;
      string bZHOfpzAcj;
      string szoxRMjVPM;
      if(ekaqJBChnq == FazjiWXjOx){GEdlmXTCaz = true;}
      else if(FazjiWXjOx == ekaqJBChnq){pBKaSHkXtA = true;}
      if(PkcgTLoEEm == lAXUyEmXwM){BtlFWxMmcV = true;}
      else if(lAXUyEmXwM == PkcgTLoEEm){shmFlelrng = true;}
      if(YdKNstaufe == dQdbojzChG){dsaMPgNdoS = true;}
      else if(dQdbojzChG == YdKNstaufe){MOVDGWsoVR = true;}
      if(YNaZcbtsIy == kIGTXpWjwo){HQlYhWuUbI = true;}
      else if(kIGTXpWjwo == YNaZcbtsIy){yBKhbRTbCM = true;}
      if(TVPkXOdDaA == gmdbpAIZuT){WwZdhyNiaT = true;}
      else if(gmdbpAIZuT == TVPkXOdDaA){YAzpaKqsjT = true;}
      if(RTphBAaNyO == ZuJGqnwXty){zwrshNdRWF = true;}
      else if(ZuJGqnwXty == RTphBAaNyO){tqdEiaeGUu = true;}
      if(aGCIRBJCEq == WUCIMctDwI){JoMHrkIMXz = true;}
      else if(WUCIMctDwI == aGCIRBJCEq){NwBbCrWEcT = true;}
      if(QuwFTDOZpd == gCaHeqlCln){BrLUzhTwdR = true;}
      if(QWTeMFWsYb == bZHOfpzAcj){TeDUTKXspU = true;}
      if(BgusXNSGSV == szoxRMjVPM){rdyVygiRlw = true;}
      while(gCaHeqlCln == QuwFTDOZpd){KKpaIMPfcu = true;}
      while(bZHOfpzAcj == bZHOfpzAcj){fzECWGWFyA = true;}
      while(szoxRMjVPM == szoxRMjVPM){mMHHycyXmh = true;}
      if(GEdlmXTCaz == true){GEdlmXTCaz = false;}
      if(BtlFWxMmcV == true){BtlFWxMmcV = false;}
      if(dsaMPgNdoS == true){dsaMPgNdoS = false;}
      if(HQlYhWuUbI == true){HQlYhWuUbI = false;}
      if(WwZdhyNiaT == true){WwZdhyNiaT = false;}
      if(zwrshNdRWF == true){zwrshNdRWF = false;}
      if(JoMHrkIMXz == true){JoMHrkIMXz = false;}
      if(BrLUzhTwdR == true){BrLUzhTwdR = false;}
      if(TeDUTKXspU == true){TeDUTKXspU = false;}
      if(rdyVygiRlw == true){rdyVygiRlw = false;}
      if(pBKaSHkXtA == true){pBKaSHkXtA = false;}
      if(shmFlelrng == true){shmFlelrng = false;}
      if(MOVDGWsoVR == true){MOVDGWsoVR = false;}
      if(yBKhbRTbCM == true){yBKhbRTbCM = false;}
      if(YAzpaKqsjT == true){YAzpaKqsjT = false;}
      if(tqdEiaeGUu == true){tqdEiaeGUu = false;}
      if(NwBbCrWEcT == true){NwBbCrWEcT = false;}
      if(KKpaIMPfcu == true){KKpaIMPfcu = false;}
      if(fzECWGWFyA == true){fzECWGWFyA = false;}
      if(mMHHycyXmh == true){mMHHycyXmh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JROEBALKBW
{ 
  void ZpVTqoynnP()
  { 
      bool AkuwwgFKUA = false;
      bool YfrNCGYTkV = false;
      bool kJqRtrjttm = false;
      bool FNLFiDYRBh = false;
      bool bYRfQxZeTf = false;
      bool RsiKZqscBD = false;
      bool xKPhuKUmdy = false;
      bool hGSCtLqLAx = false;
      bool SEZOULeBfr = false;
      bool JuQykQIikG = false;
      bool bmAVyKafPN = false;
      bool zhcDkrjBMi = false;
      bool fTHlolpURd = false;
      bool CIZtUfDEQK = false;
      bool kykRsbRMMr = false;
      bool fHVBaIfOgL = false;
      bool TGOlKqHiiF = false;
      bool ofjByghosM = false;
      bool TdHZxulYTL = false;
      bool znXFqejyGB = false;
      string GQgQNWnOix;
      string WPhGFJqFIP;
      string wyunIgFDdg;
      string tVUKjxbObK;
      string NnlGTDaZkY;
      string YxTaQIUsIg;
      string RkkBDAuXWI;
      string hccyBHMnTE;
      string FeSFIxBssa;
      string ciGuscDjDS;
      string IDDcpwUVYI;
      string wfYDalSfsF;
      string zBduezVhEY;
      string EbjAwCapOL;
      string cfTkewJCTH;
      string JWqyTGYIxq;
      string ZlRADUuXHX;
      string KcRgcThrPi;
      string oTNxPgjlgo;
      string dSrWlpNTgK;
      if(GQgQNWnOix == IDDcpwUVYI){AkuwwgFKUA = true;}
      else if(IDDcpwUVYI == GQgQNWnOix){bmAVyKafPN = true;}
      if(WPhGFJqFIP == wfYDalSfsF){YfrNCGYTkV = true;}
      else if(wfYDalSfsF == WPhGFJqFIP){zhcDkrjBMi = true;}
      if(wyunIgFDdg == zBduezVhEY){kJqRtrjttm = true;}
      else if(zBduezVhEY == wyunIgFDdg){fTHlolpURd = true;}
      if(tVUKjxbObK == EbjAwCapOL){FNLFiDYRBh = true;}
      else if(EbjAwCapOL == tVUKjxbObK){CIZtUfDEQK = true;}
      if(NnlGTDaZkY == cfTkewJCTH){bYRfQxZeTf = true;}
      else if(cfTkewJCTH == NnlGTDaZkY){kykRsbRMMr = true;}
      if(YxTaQIUsIg == JWqyTGYIxq){RsiKZqscBD = true;}
      else if(JWqyTGYIxq == YxTaQIUsIg){fHVBaIfOgL = true;}
      if(RkkBDAuXWI == ZlRADUuXHX){xKPhuKUmdy = true;}
      else if(ZlRADUuXHX == RkkBDAuXWI){TGOlKqHiiF = true;}
      if(hccyBHMnTE == KcRgcThrPi){hGSCtLqLAx = true;}
      if(FeSFIxBssa == oTNxPgjlgo){SEZOULeBfr = true;}
      if(ciGuscDjDS == dSrWlpNTgK){JuQykQIikG = true;}
      while(KcRgcThrPi == hccyBHMnTE){ofjByghosM = true;}
      while(oTNxPgjlgo == oTNxPgjlgo){TdHZxulYTL = true;}
      while(dSrWlpNTgK == dSrWlpNTgK){znXFqejyGB = true;}
      if(AkuwwgFKUA == true){AkuwwgFKUA = false;}
      if(YfrNCGYTkV == true){YfrNCGYTkV = false;}
      if(kJqRtrjttm == true){kJqRtrjttm = false;}
      if(FNLFiDYRBh == true){FNLFiDYRBh = false;}
      if(bYRfQxZeTf == true){bYRfQxZeTf = false;}
      if(RsiKZqscBD == true){RsiKZqscBD = false;}
      if(xKPhuKUmdy == true){xKPhuKUmdy = false;}
      if(hGSCtLqLAx == true){hGSCtLqLAx = false;}
      if(SEZOULeBfr == true){SEZOULeBfr = false;}
      if(JuQykQIikG == true){JuQykQIikG = false;}
      if(bmAVyKafPN == true){bmAVyKafPN = false;}
      if(zhcDkrjBMi == true){zhcDkrjBMi = false;}
      if(fTHlolpURd == true){fTHlolpURd = false;}
      if(CIZtUfDEQK == true){CIZtUfDEQK = false;}
      if(kykRsbRMMr == true){kykRsbRMMr = false;}
      if(fHVBaIfOgL == true){fHVBaIfOgL = false;}
      if(TGOlKqHiiF == true){TGOlKqHiiF = false;}
      if(ofjByghosM == true){ofjByghosM = false;}
      if(TdHZxulYTL == true){TdHZxulYTL = false;}
      if(znXFqejyGB == true){znXFqejyGB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WILITDLKHJ
{ 
  void hRkmImzpXk()
  { 
      bool eyYWHKsolD = false;
      bool SnNGElyuoV = false;
      bool WQOLgKXGmF = false;
      bool bGtWgbdDVw = false;
      bool GcyNENJyVs = false;
      bool zsDLsOiNow = false;
      bool lmBfaLtqYb = false;
      bool ItYsOsRBGT = false;
      bool BZktGiChcS = false;
      bool sPOYJTbSlr = false;
      bool SSYtkFUKwA = false;
      bool wgGVuLCGZr = false;
      bool JLOFirfziu = false;
      bool RzPOAhAqJA = false;
      bool OrlbWLIrdx = false;
      bool RUssiHETKr = false;
      bool ZUaBixRrVN = false;
      bool LKxYdQZlhX = false;
      bool imVkcxFWes = false;
      bool dgfQasQksZ = false;
      string McatMurPTg;
      string GdbUfFsSnO;
      string nZKWYtWEiL;
      string cTIsHbBBaV;
      string dwDTlbeFRp;
      string qyMbplSDUR;
      string XngHElViND;
      string DqqSjqWpkw;
      string OQlrTdHfCU;
      string JxfJxoPuPz;
      string GwrNlzHtqy;
      string PbSXCGBnmZ;
      string eofrtGKhUt;
      string baZloSXYGT;
      string WNoEFgeHGp;
      string naIoURQATf;
      string oYYwWoBfij;
      string icgSDQzbmM;
      string aCadGASkQW;
      string CXEaexnsgQ;
      if(McatMurPTg == GwrNlzHtqy){eyYWHKsolD = true;}
      else if(GwrNlzHtqy == McatMurPTg){SSYtkFUKwA = true;}
      if(GdbUfFsSnO == PbSXCGBnmZ){SnNGElyuoV = true;}
      else if(PbSXCGBnmZ == GdbUfFsSnO){wgGVuLCGZr = true;}
      if(nZKWYtWEiL == eofrtGKhUt){WQOLgKXGmF = true;}
      else if(eofrtGKhUt == nZKWYtWEiL){JLOFirfziu = true;}
      if(cTIsHbBBaV == baZloSXYGT){bGtWgbdDVw = true;}
      else if(baZloSXYGT == cTIsHbBBaV){RzPOAhAqJA = true;}
      if(dwDTlbeFRp == WNoEFgeHGp){GcyNENJyVs = true;}
      else if(WNoEFgeHGp == dwDTlbeFRp){OrlbWLIrdx = true;}
      if(qyMbplSDUR == naIoURQATf){zsDLsOiNow = true;}
      else if(naIoURQATf == qyMbplSDUR){RUssiHETKr = true;}
      if(XngHElViND == oYYwWoBfij){lmBfaLtqYb = true;}
      else if(oYYwWoBfij == XngHElViND){ZUaBixRrVN = true;}
      if(DqqSjqWpkw == icgSDQzbmM){ItYsOsRBGT = true;}
      if(OQlrTdHfCU == aCadGASkQW){BZktGiChcS = true;}
      if(JxfJxoPuPz == CXEaexnsgQ){sPOYJTbSlr = true;}
      while(icgSDQzbmM == DqqSjqWpkw){LKxYdQZlhX = true;}
      while(aCadGASkQW == aCadGASkQW){imVkcxFWes = true;}
      while(CXEaexnsgQ == CXEaexnsgQ){dgfQasQksZ = true;}
      if(eyYWHKsolD == true){eyYWHKsolD = false;}
      if(SnNGElyuoV == true){SnNGElyuoV = false;}
      if(WQOLgKXGmF == true){WQOLgKXGmF = false;}
      if(bGtWgbdDVw == true){bGtWgbdDVw = false;}
      if(GcyNENJyVs == true){GcyNENJyVs = false;}
      if(zsDLsOiNow == true){zsDLsOiNow = false;}
      if(lmBfaLtqYb == true){lmBfaLtqYb = false;}
      if(ItYsOsRBGT == true){ItYsOsRBGT = false;}
      if(BZktGiChcS == true){BZktGiChcS = false;}
      if(sPOYJTbSlr == true){sPOYJTbSlr = false;}
      if(SSYtkFUKwA == true){SSYtkFUKwA = false;}
      if(wgGVuLCGZr == true){wgGVuLCGZr = false;}
      if(JLOFirfziu == true){JLOFirfziu = false;}
      if(RzPOAhAqJA == true){RzPOAhAqJA = false;}
      if(OrlbWLIrdx == true){OrlbWLIrdx = false;}
      if(RUssiHETKr == true){RUssiHETKr = false;}
      if(ZUaBixRrVN == true){ZUaBixRrVN = false;}
      if(LKxYdQZlhX == true){LKxYdQZlhX = false;}
      if(imVkcxFWes == true){imVkcxFWes = false;}
      if(dgfQasQksZ == true){dgfQasQksZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJUNRAZQNN
{ 
  void orURwYHJfF()
  { 
      bool FVepYPFHbK = false;
      bool XAxaVQCFSc = false;
      bool HSTLQPsIqM = false;
      bool DCaqsFqgGB = false;
      bool zwAJSxNQzZ = false;
      bool VROwwmCSZJ = false;
      bool WxQOHUZGgQ = false;
      bool ZVyQcLSJrS = false;
      bool BcIQqkndtG = false;
      bool CYHxeCekCy = false;
      bool XHiiAATxTk = false;
      bool UsZGItnzXV = false;
      bool gwLZNANAla = false;
      bool fgGtussZQq = false;
      bool QpKIlJyAoj = false;
      bool OfNgQauIVz = false;
      bool lSLrFmmeLO = false;
      bool ANhfEplDnD = false;
      bool CMLBLzTZcT = false;
      bool xjEREyeRDz = false;
      string etfFjVthri;
      string NKStuSrpZO;
      string KgVJqKkBeI;
      string yCocRKbBtO;
      string ullhgfzeKa;
      string kybVxyYWOZ;
      string ksCjjKVock;
      string qqwKTYtnbK;
      string KFqEXAaTfS;
      string kElTdCiBxV;
      string KKCZjsCRBX;
      string DktDOeByMj;
      string jCIJzlFbfR;
      string orpGAADRTe;
      string yJRIOAKiEz;
      string AjoNkIBrZy;
      string mZkjhKunDO;
      string ajehkajAuz;
      string bWWfRFDbUq;
      string yLqVqXXgZE;
      if(etfFjVthri == KKCZjsCRBX){FVepYPFHbK = true;}
      else if(KKCZjsCRBX == etfFjVthri){XHiiAATxTk = true;}
      if(NKStuSrpZO == DktDOeByMj){XAxaVQCFSc = true;}
      else if(DktDOeByMj == NKStuSrpZO){UsZGItnzXV = true;}
      if(KgVJqKkBeI == jCIJzlFbfR){HSTLQPsIqM = true;}
      else if(jCIJzlFbfR == KgVJqKkBeI){gwLZNANAla = true;}
      if(yCocRKbBtO == orpGAADRTe){DCaqsFqgGB = true;}
      else if(orpGAADRTe == yCocRKbBtO){fgGtussZQq = true;}
      if(ullhgfzeKa == yJRIOAKiEz){zwAJSxNQzZ = true;}
      else if(yJRIOAKiEz == ullhgfzeKa){QpKIlJyAoj = true;}
      if(kybVxyYWOZ == AjoNkIBrZy){VROwwmCSZJ = true;}
      else if(AjoNkIBrZy == kybVxyYWOZ){OfNgQauIVz = true;}
      if(ksCjjKVock == mZkjhKunDO){WxQOHUZGgQ = true;}
      else if(mZkjhKunDO == ksCjjKVock){lSLrFmmeLO = true;}
      if(qqwKTYtnbK == ajehkajAuz){ZVyQcLSJrS = true;}
      if(KFqEXAaTfS == bWWfRFDbUq){BcIQqkndtG = true;}
      if(kElTdCiBxV == yLqVqXXgZE){CYHxeCekCy = true;}
      while(ajehkajAuz == qqwKTYtnbK){ANhfEplDnD = true;}
      while(bWWfRFDbUq == bWWfRFDbUq){CMLBLzTZcT = true;}
      while(yLqVqXXgZE == yLqVqXXgZE){xjEREyeRDz = true;}
      if(FVepYPFHbK == true){FVepYPFHbK = false;}
      if(XAxaVQCFSc == true){XAxaVQCFSc = false;}
      if(HSTLQPsIqM == true){HSTLQPsIqM = false;}
      if(DCaqsFqgGB == true){DCaqsFqgGB = false;}
      if(zwAJSxNQzZ == true){zwAJSxNQzZ = false;}
      if(VROwwmCSZJ == true){VROwwmCSZJ = false;}
      if(WxQOHUZGgQ == true){WxQOHUZGgQ = false;}
      if(ZVyQcLSJrS == true){ZVyQcLSJrS = false;}
      if(BcIQqkndtG == true){BcIQqkndtG = false;}
      if(CYHxeCekCy == true){CYHxeCekCy = false;}
      if(XHiiAATxTk == true){XHiiAATxTk = false;}
      if(UsZGItnzXV == true){UsZGItnzXV = false;}
      if(gwLZNANAla == true){gwLZNANAla = false;}
      if(fgGtussZQq == true){fgGtussZQq = false;}
      if(QpKIlJyAoj == true){QpKIlJyAoj = false;}
      if(OfNgQauIVz == true){OfNgQauIVz = false;}
      if(lSLrFmmeLO == true){lSLrFmmeLO = false;}
      if(ANhfEplDnD == true){ANhfEplDnD = false;}
      if(CMLBLzTZcT == true){CMLBLzTZcT = false;}
      if(xjEREyeRDz == true){xjEREyeRDz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWRFUUWPPT
{ 
  void cQXwXSEjYS()
  { 
      bool UwAICehTKh = false;
      bool VGVyBnrdoP = false;
      bool ShHUhDOsnw = false;
      bool qTegSFfoQQ = false;
      bool TzuIobDaWw = false;
      bool ElgmImneay = false;
      bool PnfOpCboeu = false;
      bool IDNYuTlyeG = false;
      bool AmWqrFmqYe = false;
      bool RAOSAeSgSm = false;
      bool zOubnBYHro = false;
      bool BpzTxbRnWk = false;
      bool PkQAcIntXP = false;
      bool AFfrHlrtCp = false;
      bool gezicaAtUX = false;
      bool MdJhXOytyf = false;
      bool MdjbowJHMK = false;
      bool jXlfDkkgWB = false;
      bool HsYzDVuyTr = false;
      bool nxwWdDtXtg = false;
      string GROhEpfRpo;
      string FmtcMXYDWo;
      string FYUouAxlyX;
      string EXiCsGAYRH;
      string KLpWtNjnpW;
      string iALcNgxZlD;
      string rtTSkhErjG;
      string WAlOesixth;
      string PJuanDLGnM;
      string JalNOQrWlM;
      string JrDjziOxyT;
      string yzfEniyrdg;
      string VxDXxwNXzN;
      string BLLgXWFLaF;
      string nOHUNJtgZf;
      string RzrEpLoflD;
      string UqxkRlnygQ;
      string dmRYsHphJn;
      string BfyTuCSGqL;
      string hZYXkxQWDb;
      if(GROhEpfRpo == JrDjziOxyT){UwAICehTKh = true;}
      else if(JrDjziOxyT == GROhEpfRpo){zOubnBYHro = true;}
      if(FmtcMXYDWo == yzfEniyrdg){VGVyBnrdoP = true;}
      else if(yzfEniyrdg == FmtcMXYDWo){BpzTxbRnWk = true;}
      if(FYUouAxlyX == VxDXxwNXzN){ShHUhDOsnw = true;}
      else if(VxDXxwNXzN == FYUouAxlyX){PkQAcIntXP = true;}
      if(EXiCsGAYRH == BLLgXWFLaF){qTegSFfoQQ = true;}
      else if(BLLgXWFLaF == EXiCsGAYRH){AFfrHlrtCp = true;}
      if(KLpWtNjnpW == nOHUNJtgZf){TzuIobDaWw = true;}
      else if(nOHUNJtgZf == KLpWtNjnpW){gezicaAtUX = true;}
      if(iALcNgxZlD == RzrEpLoflD){ElgmImneay = true;}
      else if(RzrEpLoflD == iALcNgxZlD){MdJhXOytyf = true;}
      if(rtTSkhErjG == UqxkRlnygQ){PnfOpCboeu = true;}
      else if(UqxkRlnygQ == rtTSkhErjG){MdjbowJHMK = true;}
      if(WAlOesixth == dmRYsHphJn){IDNYuTlyeG = true;}
      if(PJuanDLGnM == BfyTuCSGqL){AmWqrFmqYe = true;}
      if(JalNOQrWlM == hZYXkxQWDb){RAOSAeSgSm = true;}
      while(dmRYsHphJn == WAlOesixth){jXlfDkkgWB = true;}
      while(BfyTuCSGqL == BfyTuCSGqL){HsYzDVuyTr = true;}
      while(hZYXkxQWDb == hZYXkxQWDb){nxwWdDtXtg = true;}
      if(UwAICehTKh == true){UwAICehTKh = false;}
      if(VGVyBnrdoP == true){VGVyBnrdoP = false;}
      if(ShHUhDOsnw == true){ShHUhDOsnw = false;}
      if(qTegSFfoQQ == true){qTegSFfoQQ = false;}
      if(TzuIobDaWw == true){TzuIobDaWw = false;}
      if(ElgmImneay == true){ElgmImneay = false;}
      if(PnfOpCboeu == true){PnfOpCboeu = false;}
      if(IDNYuTlyeG == true){IDNYuTlyeG = false;}
      if(AmWqrFmqYe == true){AmWqrFmqYe = false;}
      if(RAOSAeSgSm == true){RAOSAeSgSm = false;}
      if(zOubnBYHro == true){zOubnBYHro = false;}
      if(BpzTxbRnWk == true){BpzTxbRnWk = false;}
      if(PkQAcIntXP == true){PkQAcIntXP = false;}
      if(AFfrHlrtCp == true){AFfrHlrtCp = false;}
      if(gezicaAtUX == true){gezicaAtUX = false;}
      if(MdJhXOytyf == true){MdJhXOytyf = false;}
      if(MdjbowJHMK == true){MdjbowJHMK = false;}
      if(jXlfDkkgWB == true){jXlfDkkgWB = false;}
      if(HsYzDVuyTr == true){HsYzDVuyTr = false;}
      if(nxwWdDtXtg == true){nxwWdDtXtg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQNVPJHKVM
{ 
  void EUSdNEtUDK()
  { 
      bool DKChHuhTQa = false;
      bool LXcQJWUmlk = false;
      bool JPLiagorAC = false;
      bool LyDEnaUGcN = false;
      bool ZOPTMAGpzL = false;
      bool gUdcsnySHa = false;
      bool FoTNONTXbh = false;
      bool COJYKuzrWZ = false;
      bool ZzsnVqTaLz = false;
      bool cBzBHjtCEz = false;
      bool ghNQJRKERy = false;
      bool oFwhBGwerX = false;
      bool trMcEAPIRa = false;
      bool AxmWrqkbeD = false;
      bool fOJMKWFQAA = false;
      bool nOJgFnUkLI = false;
      bool CCmpxqSYoJ = false;
      bool UUAoqeiARh = false;
      bool uyHRmlmFRE = false;
      bool VAPVAdbSPS = false;
      string REawyUbSzn;
      string ejZhSJZzaZ;
      string XkWtlIZDNg;
      string iQBIFdtajG;
      string ZrimJjfQoM;
      string atCuPgggJp;
      string uYFSENhRbo;
      string PzPUAeCjkC;
      string cJOAFoNGrY;
      string xMRtKBmPiu;
      string COnzxbdhtk;
      string dxwHMlKEMO;
      string AaYCqCgUJz;
      string qlAozNUODc;
      string KfMHuAQJgY;
      string qiDTuaokHt;
      string tJXusrwGHz;
      string QuAiDTORHq;
      string kWnkIIhftY;
      string YjGIiBHQNC;
      if(REawyUbSzn == COnzxbdhtk){DKChHuhTQa = true;}
      else if(COnzxbdhtk == REawyUbSzn){ghNQJRKERy = true;}
      if(ejZhSJZzaZ == dxwHMlKEMO){LXcQJWUmlk = true;}
      else if(dxwHMlKEMO == ejZhSJZzaZ){oFwhBGwerX = true;}
      if(XkWtlIZDNg == AaYCqCgUJz){JPLiagorAC = true;}
      else if(AaYCqCgUJz == XkWtlIZDNg){trMcEAPIRa = true;}
      if(iQBIFdtajG == qlAozNUODc){LyDEnaUGcN = true;}
      else if(qlAozNUODc == iQBIFdtajG){AxmWrqkbeD = true;}
      if(ZrimJjfQoM == KfMHuAQJgY){ZOPTMAGpzL = true;}
      else if(KfMHuAQJgY == ZrimJjfQoM){fOJMKWFQAA = true;}
      if(atCuPgggJp == qiDTuaokHt){gUdcsnySHa = true;}
      else if(qiDTuaokHt == atCuPgggJp){nOJgFnUkLI = true;}
      if(uYFSENhRbo == tJXusrwGHz){FoTNONTXbh = true;}
      else if(tJXusrwGHz == uYFSENhRbo){CCmpxqSYoJ = true;}
      if(PzPUAeCjkC == QuAiDTORHq){COJYKuzrWZ = true;}
      if(cJOAFoNGrY == kWnkIIhftY){ZzsnVqTaLz = true;}
      if(xMRtKBmPiu == YjGIiBHQNC){cBzBHjtCEz = true;}
      while(QuAiDTORHq == PzPUAeCjkC){UUAoqeiARh = true;}
      while(kWnkIIhftY == kWnkIIhftY){uyHRmlmFRE = true;}
      while(YjGIiBHQNC == YjGIiBHQNC){VAPVAdbSPS = true;}
      if(DKChHuhTQa == true){DKChHuhTQa = false;}
      if(LXcQJWUmlk == true){LXcQJWUmlk = false;}
      if(JPLiagorAC == true){JPLiagorAC = false;}
      if(LyDEnaUGcN == true){LyDEnaUGcN = false;}
      if(ZOPTMAGpzL == true){ZOPTMAGpzL = false;}
      if(gUdcsnySHa == true){gUdcsnySHa = false;}
      if(FoTNONTXbh == true){FoTNONTXbh = false;}
      if(COJYKuzrWZ == true){COJYKuzrWZ = false;}
      if(ZzsnVqTaLz == true){ZzsnVqTaLz = false;}
      if(cBzBHjtCEz == true){cBzBHjtCEz = false;}
      if(ghNQJRKERy == true){ghNQJRKERy = false;}
      if(oFwhBGwerX == true){oFwhBGwerX = false;}
      if(trMcEAPIRa == true){trMcEAPIRa = false;}
      if(AxmWrqkbeD == true){AxmWrqkbeD = false;}
      if(fOJMKWFQAA == true){fOJMKWFQAA = false;}
      if(nOJgFnUkLI == true){nOJgFnUkLI = false;}
      if(CCmpxqSYoJ == true){CCmpxqSYoJ = false;}
      if(UUAoqeiARh == true){UUAoqeiARh = false;}
      if(uyHRmlmFRE == true){uyHRmlmFRE = false;}
      if(VAPVAdbSPS == true){VAPVAdbSPS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSMFMKXVAC
{ 
  void VPzDSYyRWJ()
  { 
      bool AOLmEOLNQL = false;
      bool sKhJnpGLLp = false;
      bool ZIEOZKfiCz = false;
      bool cqCyDxgjxm = false;
      bool qUWkyAqoIb = false;
      bool MHWcfqKxNt = false;
      bool ibLRiBIiGq = false;
      bool JVOYzElSPY = false;
      bool SpaZlUUZRL = false;
      bool miWDDOJFCx = false;
      bool rIiRRpsycb = false;
      bool FqhobsBkeN = false;
      bool giRtEazLUj = false;
      bool ufQSgKHJIu = false;
      bool aWwpGuBhbK = false;
      bool NXZnPIpnMq = false;
      bool qhcsfYaOHQ = false;
      bool lrcjmKmanJ = false;
      bool YRjKWWFbCX = false;
      bool TSwQDrsCKg = false;
      string iXyGfzcIGA;
      string tkimiTJkjn;
      string spazgxhJCo;
      string FaDDfPULkF;
      string FbVyGarNhb;
      string rcltEsxyYh;
      string RSFRuThfGT;
      string yxAeiQTbrF;
      string ETaawboIym;
      string SVlCmlWDDm;
      string sMGOctcGLm;
      string YUGTcxqeVS;
      string eYgTAbLxrw;
      string tQXFMrMMyB;
      string zhxLOxPSYo;
      string trhjIUfmNA;
      string ieOOrIxBGk;
      string jefUTwaUED;
      string LrXCCChnxr;
      string LZzxRTTiSG;
      if(iXyGfzcIGA == sMGOctcGLm){AOLmEOLNQL = true;}
      else if(sMGOctcGLm == iXyGfzcIGA){rIiRRpsycb = true;}
      if(tkimiTJkjn == YUGTcxqeVS){sKhJnpGLLp = true;}
      else if(YUGTcxqeVS == tkimiTJkjn){FqhobsBkeN = true;}
      if(spazgxhJCo == eYgTAbLxrw){ZIEOZKfiCz = true;}
      else if(eYgTAbLxrw == spazgxhJCo){giRtEazLUj = true;}
      if(FaDDfPULkF == tQXFMrMMyB){cqCyDxgjxm = true;}
      else if(tQXFMrMMyB == FaDDfPULkF){ufQSgKHJIu = true;}
      if(FbVyGarNhb == zhxLOxPSYo){qUWkyAqoIb = true;}
      else if(zhxLOxPSYo == FbVyGarNhb){aWwpGuBhbK = true;}
      if(rcltEsxyYh == trhjIUfmNA){MHWcfqKxNt = true;}
      else if(trhjIUfmNA == rcltEsxyYh){NXZnPIpnMq = true;}
      if(RSFRuThfGT == ieOOrIxBGk){ibLRiBIiGq = true;}
      else if(ieOOrIxBGk == RSFRuThfGT){qhcsfYaOHQ = true;}
      if(yxAeiQTbrF == jefUTwaUED){JVOYzElSPY = true;}
      if(ETaawboIym == LrXCCChnxr){SpaZlUUZRL = true;}
      if(SVlCmlWDDm == LZzxRTTiSG){miWDDOJFCx = true;}
      while(jefUTwaUED == yxAeiQTbrF){lrcjmKmanJ = true;}
      while(LrXCCChnxr == LrXCCChnxr){YRjKWWFbCX = true;}
      while(LZzxRTTiSG == LZzxRTTiSG){TSwQDrsCKg = true;}
      if(AOLmEOLNQL == true){AOLmEOLNQL = false;}
      if(sKhJnpGLLp == true){sKhJnpGLLp = false;}
      if(ZIEOZKfiCz == true){ZIEOZKfiCz = false;}
      if(cqCyDxgjxm == true){cqCyDxgjxm = false;}
      if(qUWkyAqoIb == true){qUWkyAqoIb = false;}
      if(MHWcfqKxNt == true){MHWcfqKxNt = false;}
      if(ibLRiBIiGq == true){ibLRiBIiGq = false;}
      if(JVOYzElSPY == true){JVOYzElSPY = false;}
      if(SpaZlUUZRL == true){SpaZlUUZRL = false;}
      if(miWDDOJFCx == true){miWDDOJFCx = false;}
      if(rIiRRpsycb == true){rIiRRpsycb = false;}
      if(FqhobsBkeN == true){FqhobsBkeN = false;}
      if(giRtEazLUj == true){giRtEazLUj = false;}
      if(ufQSgKHJIu == true){ufQSgKHJIu = false;}
      if(aWwpGuBhbK == true){aWwpGuBhbK = false;}
      if(NXZnPIpnMq == true){NXZnPIpnMq = false;}
      if(qhcsfYaOHQ == true){qhcsfYaOHQ = false;}
      if(lrcjmKmanJ == true){lrcjmKmanJ = false;}
      if(YRjKWWFbCX == true){YRjKWWFbCX = false;}
      if(TSwQDrsCKg == true){TSwQDrsCKg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYXHPFEOFA
{ 
  void qdYtCgFoZa()
  { 
      bool aDcmVDBUCX = false;
      bool MqcWtoRnZH = false;
      bool IFVCadqaCr = false;
      bool BmPNHhbEfe = false;
      bool LQNuiUxmps = false;
      bool zUewOVhZLq = false;
      bool MaRKWYbOOM = false;
      bool NNHtwqqZTF = false;
      bool fDjIsfHSzl = false;
      bool zBroRkyDYK = false;
      bool siXcfkNkAX = false;
      bool dHGFLJpJRp = false;
      bool QJPcNMVSbK = false;
      bool snAIMxeGcH = false;
      bool SWRbHqumcI = false;
      bool tolitiStPT = false;
      bool PuIodpHxrO = false;
      bool djfJWsqnVV = false;
      bool QhoTPDBROc = false;
      bool dkpJrXObxQ = false;
      string RXyLthjLJV;
      string EoBVopzlSB;
      string OLDLwCgPFn;
      string jeUjMOYqfV;
      string pxsgQhWaMc;
      string jhOINGTlOr;
      string BTGUkZUQJa;
      string QIGxKRRWtO;
      string eGCcECQMVG;
      string tlbnUWqXuq;
      string NGQlLabRxw;
      string nxrAMtRcQi;
      string IHtCfefRbn;
      string atbCBYoQRd;
      string ZyOZRxsbaZ;
      string ENHLhFLOGf;
      string tJoJUtVpyn;
      string EBLlIKsTki;
      string kEqBiNlPTu;
      string MaKkiQIFEW;
      if(RXyLthjLJV == NGQlLabRxw){aDcmVDBUCX = true;}
      else if(NGQlLabRxw == RXyLthjLJV){siXcfkNkAX = true;}
      if(EoBVopzlSB == nxrAMtRcQi){MqcWtoRnZH = true;}
      else if(nxrAMtRcQi == EoBVopzlSB){dHGFLJpJRp = true;}
      if(OLDLwCgPFn == IHtCfefRbn){IFVCadqaCr = true;}
      else if(IHtCfefRbn == OLDLwCgPFn){QJPcNMVSbK = true;}
      if(jeUjMOYqfV == atbCBYoQRd){BmPNHhbEfe = true;}
      else if(atbCBYoQRd == jeUjMOYqfV){snAIMxeGcH = true;}
      if(pxsgQhWaMc == ZyOZRxsbaZ){LQNuiUxmps = true;}
      else if(ZyOZRxsbaZ == pxsgQhWaMc){SWRbHqumcI = true;}
      if(jhOINGTlOr == ENHLhFLOGf){zUewOVhZLq = true;}
      else if(ENHLhFLOGf == jhOINGTlOr){tolitiStPT = true;}
      if(BTGUkZUQJa == tJoJUtVpyn){MaRKWYbOOM = true;}
      else if(tJoJUtVpyn == BTGUkZUQJa){PuIodpHxrO = true;}
      if(QIGxKRRWtO == EBLlIKsTki){NNHtwqqZTF = true;}
      if(eGCcECQMVG == kEqBiNlPTu){fDjIsfHSzl = true;}
      if(tlbnUWqXuq == MaKkiQIFEW){zBroRkyDYK = true;}
      while(EBLlIKsTki == QIGxKRRWtO){djfJWsqnVV = true;}
      while(kEqBiNlPTu == kEqBiNlPTu){QhoTPDBROc = true;}
      while(MaKkiQIFEW == MaKkiQIFEW){dkpJrXObxQ = true;}
      if(aDcmVDBUCX == true){aDcmVDBUCX = false;}
      if(MqcWtoRnZH == true){MqcWtoRnZH = false;}
      if(IFVCadqaCr == true){IFVCadqaCr = false;}
      if(BmPNHhbEfe == true){BmPNHhbEfe = false;}
      if(LQNuiUxmps == true){LQNuiUxmps = false;}
      if(zUewOVhZLq == true){zUewOVhZLq = false;}
      if(MaRKWYbOOM == true){MaRKWYbOOM = false;}
      if(NNHtwqqZTF == true){NNHtwqqZTF = false;}
      if(fDjIsfHSzl == true){fDjIsfHSzl = false;}
      if(zBroRkyDYK == true){zBroRkyDYK = false;}
      if(siXcfkNkAX == true){siXcfkNkAX = false;}
      if(dHGFLJpJRp == true){dHGFLJpJRp = false;}
      if(QJPcNMVSbK == true){QJPcNMVSbK = false;}
      if(snAIMxeGcH == true){snAIMxeGcH = false;}
      if(SWRbHqumcI == true){SWRbHqumcI = false;}
      if(tolitiStPT == true){tolitiStPT = false;}
      if(PuIodpHxrO == true){PuIodpHxrO = false;}
      if(djfJWsqnVV == true){djfJWsqnVV = false;}
      if(QhoTPDBROc == true){QhoTPDBROc = false;}
      if(dkpJrXObxQ == true){dkpJrXObxQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGJBJWZFGF
{ 
  void hkBtpFZTyx()
  { 
      bool AAwTecbSld = false;
      bool gneGdoEymE = false;
      bool DObaQsxUKN = false;
      bool GulpCwtzCo = false;
      bool jZZWVfCHoT = false;
      bool xNVFzkXUCl = false;
      bool eHIXXlBoDg = false;
      bool uEwxUdnFEj = false;
      bool qpepQrYfpR = false;
      bool XYwPKbRCyj = false;
      bool dNDIYrRYkV = false;
      bool wSQRuocRHf = false;
      bool MVylJVIfmr = false;
      bool MlGUGclWRX = false;
      bool azuTUEIdUU = false;
      bool zztSWIORyD = false;
      bool jklrJJLwLR = false;
      bool CGAiFMZdQE = false;
      bool MdLRsMqnxy = false;
      bool NTXOnoNCKK = false;
      string lyLKUepCrl;
      string cSdPNLQSXu;
      string CbCgxOVxYt;
      string fGVmoPhGAw;
      string QbwxcCAtld;
      string HMurTJweNF;
      string IscxGVwqZy;
      string dKSaeafFEt;
      string OaKtmSLcTe;
      string SDsumWyypG;
      string FIUnAxtTNr;
      string dqZSpghhKn;
      string KTXueZQWnH;
      string bgOxoFGWtp;
      string XrOaAbcZEG;
      string oPnCwkkYIa;
      string fWfFQxbcdk;
      string aLnUPREwtC;
      string wpSgSLsMAD;
      string TgNTJBLJKD;
      if(lyLKUepCrl == FIUnAxtTNr){AAwTecbSld = true;}
      else if(FIUnAxtTNr == lyLKUepCrl){dNDIYrRYkV = true;}
      if(cSdPNLQSXu == dqZSpghhKn){gneGdoEymE = true;}
      else if(dqZSpghhKn == cSdPNLQSXu){wSQRuocRHf = true;}
      if(CbCgxOVxYt == KTXueZQWnH){DObaQsxUKN = true;}
      else if(KTXueZQWnH == CbCgxOVxYt){MVylJVIfmr = true;}
      if(fGVmoPhGAw == bgOxoFGWtp){GulpCwtzCo = true;}
      else if(bgOxoFGWtp == fGVmoPhGAw){MlGUGclWRX = true;}
      if(QbwxcCAtld == XrOaAbcZEG){jZZWVfCHoT = true;}
      else if(XrOaAbcZEG == QbwxcCAtld){azuTUEIdUU = true;}
      if(HMurTJweNF == oPnCwkkYIa){xNVFzkXUCl = true;}
      else if(oPnCwkkYIa == HMurTJweNF){zztSWIORyD = true;}
      if(IscxGVwqZy == fWfFQxbcdk){eHIXXlBoDg = true;}
      else if(fWfFQxbcdk == IscxGVwqZy){jklrJJLwLR = true;}
      if(dKSaeafFEt == aLnUPREwtC){uEwxUdnFEj = true;}
      if(OaKtmSLcTe == wpSgSLsMAD){qpepQrYfpR = true;}
      if(SDsumWyypG == TgNTJBLJKD){XYwPKbRCyj = true;}
      while(aLnUPREwtC == dKSaeafFEt){CGAiFMZdQE = true;}
      while(wpSgSLsMAD == wpSgSLsMAD){MdLRsMqnxy = true;}
      while(TgNTJBLJKD == TgNTJBLJKD){NTXOnoNCKK = true;}
      if(AAwTecbSld == true){AAwTecbSld = false;}
      if(gneGdoEymE == true){gneGdoEymE = false;}
      if(DObaQsxUKN == true){DObaQsxUKN = false;}
      if(GulpCwtzCo == true){GulpCwtzCo = false;}
      if(jZZWVfCHoT == true){jZZWVfCHoT = false;}
      if(xNVFzkXUCl == true){xNVFzkXUCl = false;}
      if(eHIXXlBoDg == true){eHIXXlBoDg = false;}
      if(uEwxUdnFEj == true){uEwxUdnFEj = false;}
      if(qpepQrYfpR == true){qpepQrYfpR = false;}
      if(XYwPKbRCyj == true){XYwPKbRCyj = false;}
      if(dNDIYrRYkV == true){dNDIYrRYkV = false;}
      if(wSQRuocRHf == true){wSQRuocRHf = false;}
      if(MVylJVIfmr == true){MVylJVIfmr = false;}
      if(MlGUGclWRX == true){MlGUGclWRX = false;}
      if(azuTUEIdUU == true){azuTUEIdUU = false;}
      if(zztSWIORyD == true){zztSWIORyD = false;}
      if(jklrJJLwLR == true){jklrJJLwLR = false;}
      if(CGAiFMZdQE == true){CGAiFMZdQE = false;}
      if(MdLRsMqnxy == true){MdLRsMqnxy = false;}
      if(NTXOnoNCKK == true){NTXOnoNCKK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFEAECNXAO
{ 
  void YkItqgkWeX()
  { 
      bool XkyulOxLMX = false;
      bool FCbNGlWOgl = false;
      bool aPjMJgolUV = false;
      bool pCJGZmraqR = false;
      bool uaARDHXLWg = false;
      bool kqjsXHBklF = false;
      bool YKqpgDsVmS = false;
      bool twXPpzPRJC = false;
      bool IdPmkzSQiS = false;
      bool lGolrjjJjA = false;
      bool OBXEmoTTCX = false;
      bool qibjwuuEFh = false;
      bool jbmUfmGlWG = false;
      bool PGgImGGKzu = false;
      bool fyOKaCdFox = false;
      bool oeECPlOCXz = false;
      bool hgxwHkCTwo = false;
      bool ojEJClNctc = false;
      bool IBwZQjBerB = false;
      bool rDlzMyARCp = false;
      string BjlklBfHZG;
      string mREQaoOYGM;
      string SbXYcXHkOF;
      string nFPPltJfAb;
      string XcErxXebps;
      string VESMXYMMHO;
      string ttsTRhBodf;
      string ehXdnoXeaE;
      string reuVijlDqN;
      string hwXlhdjjZP;
      string WpyJNmfnXi;
      string BgkDVOzXjh;
      string uyyQyiKlwK;
      string EmELhCgkHw;
      string DyeIMAKTPS;
      string dMArUYrgLd;
      string ctrNdNcZVT;
      string gOPnewSoEx;
      string XpWcgrmMpI;
      string KAYcTIGQey;
      if(BjlklBfHZG == WpyJNmfnXi){XkyulOxLMX = true;}
      else if(WpyJNmfnXi == BjlklBfHZG){OBXEmoTTCX = true;}
      if(mREQaoOYGM == BgkDVOzXjh){FCbNGlWOgl = true;}
      else if(BgkDVOzXjh == mREQaoOYGM){qibjwuuEFh = true;}
      if(SbXYcXHkOF == uyyQyiKlwK){aPjMJgolUV = true;}
      else if(uyyQyiKlwK == SbXYcXHkOF){jbmUfmGlWG = true;}
      if(nFPPltJfAb == EmELhCgkHw){pCJGZmraqR = true;}
      else if(EmELhCgkHw == nFPPltJfAb){PGgImGGKzu = true;}
      if(XcErxXebps == DyeIMAKTPS){uaARDHXLWg = true;}
      else if(DyeIMAKTPS == XcErxXebps){fyOKaCdFox = true;}
      if(VESMXYMMHO == dMArUYrgLd){kqjsXHBklF = true;}
      else if(dMArUYrgLd == VESMXYMMHO){oeECPlOCXz = true;}
      if(ttsTRhBodf == ctrNdNcZVT){YKqpgDsVmS = true;}
      else if(ctrNdNcZVT == ttsTRhBodf){hgxwHkCTwo = true;}
      if(ehXdnoXeaE == gOPnewSoEx){twXPpzPRJC = true;}
      if(reuVijlDqN == XpWcgrmMpI){IdPmkzSQiS = true;}
      if(hwXlhdjjZP == KAYcTIGQey){lGolrjjJjA = true;}
      while(gOPnewSoEx == ehXdnoXeaE){ojEJClNctc = true;}
      while(XpWcgrmMpI == XpWcgrmMpI){IBwZQjBerB = true;}
      while(KAYcTIGQey == KAYcTIGQey){rDlzMyARCp = true;}
      if(XkyulOxLMX == true){XkyulOxLMX = false;}
      if(FCbNGlWOgl == true){FCbNGlWOgl = false;}
      if(aPjMJgolUV == true){aPjMJgolUV = false;}
      if(pCJGZmraqR == true){pCJGZmraqR = false;}
      if(uaARDHXLWg == true){uaARDHXLWg = false;}
      if(kqjsXHBklF == true){kqjsXHBklF = false;}
      if(YKqpgDsVmS == true){YKqpgDsVmS = false;}
      if(twXPpzPRJC == true){twXPpzPRJC = false;}
      if(IdPmkzSQiS == true){IdPmkzSQiS = false;}
      if(lGolrjjJjA == true){lGolrjjJjA = false;}
      if(OBXEmoTTCX == true){OBXEmoTTCX = false;}
      if(qibjwuuEFh == true){qibjwuuEFh = false;}
      if(jbmUfmGlWG == true){jbmUfmGlWG = false;}
      if(PGgImGGKzu == true){PGgImGGKzu = false;}
      if(fyOKaCdFox == true){fyOKaCdFox = false;}
      if(oeECPlOCXz == true){oeECPlOCXz = false;}
      if(hgxwHkCTwo == true){hgxwHkCTwo = false;}
      if(ojEJClNctc == true){ojEJClNctc = false;}
      if(IBwZQjBerB == true){IBwZQjBerB = false;}
      if(rDlzMyARCp == true){rDlzMyARCp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIBOQGHOZU
{ 
  void bnWIjeTqXN()
  { 
      bool rYZOytFFSN = false;
      bool tIICWnuKJF = false;
      bool zGcoJbufbR = false;
      bool DiaHgXlPfi = false;
      bool bVQqYNepiA = false;
      bool DAHYXlujFV = false;
      bool yYdBJLgAUz = false;
      bool BfdZccpkPu = false;
      bool wExaNCbBju = false;
      bool bCJKjDrOgN = false;
      bool geVjzXWgwt = false;
      bool uJTKYsbCmG = false;
      bool jePYWyVTpZ = false;
      bool kaECOQiMbp = false;
      bool ftFozRhzkp = false;
      bool boaZdBPwNA = false;
      bool BCqVJUFRuH = false;
      bool KOaxaoYaZE = false;
      bool QWizyuzdXM = false;
      bool BlzbndDjee = false;
      string hxLEqKPNWX;
      string IIZcJtxerN;
      string DkoSRGWyzi;
      string HLDYWERtut;
      string JVNrpDkZqA;
      string yheCtxIslk;
      string nQNnPwEAFF;
      string bDixEhXwbN;
      string UwHzjYgBdZ;
      string uXHKFrHZbs;
      string ykTlXuzgyM;
      string ZLQYPrJODq;
      string PDWfJDuYrL;
      string ZxUiOjbUan;
      string ZADQzjGitN;
      string isVkcuNnbT;
      string AZnllbqhJf;
      string PnmPRPAFfZ;
      string wMddcgbjFT;
      string VmrGnzLQdX;
      if(hxLEqKPNWX == ykTlXuzgyM){rYZOytFFSN = true;}
      else if(ykTlXuzgyM == hxLEqKPNWX){geVjzXWgwt = true;}
      if(IIZcJtxerN == ZLQYPrJODq){tIICWnuKJF = true;}
      else if(ZLQYPrJODq == IIZcJtxerN){uJTKYsbCmG = true;}
      if(DkoSRGWyzi == PDWfJDuYrL){zGcoJbufbR = true;}
      else if(PDWfJDuYrL == DkoSRGWyzi){jePYWyVTpZ = true;}
      if(HLDYWERtut == ZxUiOjbUan){DiaHgXlPfi = true;}
      else if(ZxUiOjbUan == HLDYWERtut){kaECOQiMbp = true;}
      if(JVNrpDkZqA == ZADQzjGitN){bVQqYNepiA = true;}
      else if(ZADQzjGitN == JVNrpDkZqA){ftFozRhzkp = true;}
      if(yheCtxIslk == isVkcuNnbT){DAHYXlujFV = true;}
      else if(isVkcuNnbT == yheCtxIslk){boaZdBPwNA = true;}
      if(nQNnPwEAFF == AZnllbqhJf){yYdBJLgAUz = true;}
      else if(AZnllbqhJf == nQNnPwEAFF){BCqVJUFRuH = true;}
      if(bDixEhXwbN == PnmPRPAFfZ){BfdZccpkPu = true;}
      if(UwHzjYgBdZ == wMddcgbjFT){wExaNCbBju = true;}
      if(uXHKFrHZbs == VmrGnzLQdX){bCJKjDrOgN = true;}
      while(PnmPRPAFfZ == bDixEhXwbN){KOaxaoYaZE = true;}
      while(wMddcgbjFT == wMddcgbjFT){QWizyuzdXM = true;}
      while(VmrGnzLQdX == VmrGnzLQdX){BlzbndDjee = true;}
      if(rYZOytFFSN == true){rYZOytFFSN = false;}
      if(tIICWnuKJF == true){tIICWnuKJF = false;}
      if(zGcoJbufbR == true){zGcoJbufbR = false;}
      if(DiaHgXlPfi == true){DiaHgXlPfi = false;}
      if(bVQqYNepiA == true){bVQqYNepiA = false;}
      if(DAHYXlujFV == true){DAHYXlujFV = false;}
      if(yYdBJLgAUz == true){yYdBJLgAUz = false;}
      if(BfdZccpkPu == true){BfdZccpkPu = false;}
      if(wExaNCbBju == true){wExaNCbBju = false;}
      if(bCJKjDrOgN == true){bCJKjDrOgN = false;}
      if(geVjzXWgwt == true){geVjzXWgwt = false;}
      if(uJTKYsbCmG == true){uJTKYsbCmG = false;}
      if(jePYWyVTpZ == true){jePYWyVTpZ = false;}
      if(kaECOQiMbp == true){kaECOQiMbp = false;}
      if(ftFozRhzkp == true){ftFozRhzkp = false;}
      if(boaZdBPwNA == true){boaZdBPwNA = false;}
      if(BCqVJUFRuH == true){BCqVJUFRuH = false;}
      if(KOaxaoYaZE == true){KOaxaoYaZE = false;}
      if(QWizyuzdXM == true){QWizyuzdXM = false;}
      if(BlzbndDjee == true){BlzbndDjee = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZLRCGAPQC
{ 
  void TAwWqFKNMX()
  { 
      bool CXNownWCoO = false;
      bool jUEYyBVRlZ = false;
      bool wOyBhzswzy = false;
      bool jHKkwGBWsV = false;
      bool bAeakwVJFW = false;
      bool eIwgrmZMHx = false;
      bool uZDqdbKScr = false;
      bool AzXQxuiWPl = false;
      bool dipbSaKdsI = false;
      bool goOwZCxmxJ = false;
      bool lCfNWfkfiw = false;
      bool ECxVTLiaXC = false;
      bool RfZTKLjbpu = false;
      bool xuZFzaCcFm = false;
      bool pdtwEeqscO = false;
      bool TWOtrFcMDL = false;
      bool uJonyIbqVs = false;
      bool IGUkMmlcPf = false;
      bool TpzbbagfNs = false;
      bool xpYtqgnGyw = false;
      string LahVbedLsw;
      string jPXeNCRXjS;
      string ZUDxKoIhYZ;
      string umtBEByOdW;
      string ttFXPREPTX;
      string TcisapXjLm;
      string VwlSBxVWZM;
      string EDsNXeOfgr;
      string ksNBGSDAaN;
      string cNDqAyIlWS;
      string whoHTQjUVu;
      string arCSCchjMh;
      string sVwLipzBNZ;
      string WcIOwCDGho;
      string iheelkLjoW;
      string PXZnYalcXc;
      string QhHuYyimWz;
      string ZbBWyKpQYy;
      string dPMpJyCUoV;
      string QZiEXAaiGn;
      if(LahVbedLsw == whoHTQjUVu){CXNownWCoO = true;}
      else if(whoHTQjUVu == LahVbedLsw){lCfNWfkfiw = true;}
      if(jPXeNCRXjS == arCSCchjMh){jUEYyBVRlZ = true;}
      else if(arCSCchjMh == jPXeNCRXjS){ECxVTLiaXC = true;}
      if(ZUDxKoIhYZ == sVwLipzBNZ){wOyBhzswzy = true;}
      else if(sVwLipzBNZ == ZUDxKoIhYZ){RfZTKLjbpu = true;}
      if(umtBEByOdW == WcIOwCDGho){jHKkwGBWsV = true;}
      else if(WcIOwCDGho == umtBEByOdW){xuZFzaCcFm = true;}
      if(ttFXPREPTX == iheelkLjoW){bAeakwVJFW = true;}
      else if(iheelkLjoW == ttFXPREPTX){pdtwEeqscO = true;}
      if(TcisapXjLm == PXZnYalcXc){eIwgrmZMHx = true;}
      else if(PXZnYalcXc == TcisapXjLm){TWOtrFcMDL = true;}
      if(VwlSBxVWZM == QhHuYyimWz){uZDqdbKScr = true;}
      else if(QhHuYyimWz == VwlSBxVWZM){uJonyIbqVs = true;}
      if(EDsNXeOfgr == ZbBWyKpQYy){AzXQxuiWPl = true;}
      if(ksNBGSDAaN == dPMpJyCUoV){dipbSaKdsI = true;}
      if(cNDqAyIlWS == QZiEXAaiGn){goOwZCxmxJ = true;}
      while(ZbBWyKpQYy == EDsNXeOfgr){IGUkMmlcPf = true;}
      while(dPMpJyCUoV == dPMpJyCUoV){TpzbbagfNs = true;}
      while(QZiEXAaiGn == QZiEXAaiGn){xpYtqgnGyw = true;}
      if(CXNownWCoO == true){CXNownWCoO = false;}
      if(jUEYyBVRlZ == true){jUEYyBVRlZ = false;}
      if(wOyBhzswzy == true){wOyBhzswzy = false;}
      if(jHKkwGBWsV == true){jHKkwGBWsV = false;}
      if(bAeakwVJFW == true){bAeakwVJFW = false;}
      if(eIwgrmZMHx == true){eIwgrmZMHx = false;}
      if(uZDqdbKScr == true){uZDqdbKScr = false;}
      if(AzXQxuiWPl == true){AzXQxuiWPl = false;}
      if(dipbSaKdsI == true){dipbSaKdsI = false;}
      if(goOwZCxmxJ == true){goOwZCxmxJ = false;}
      if(lCfNWfkfiw == true){lCfNWfkfiw = false;}
      if(ECxVTLiaXC == true){ECxVTLiaXC = false;}
      if(RfZTKLjbpu == true){RfZTKLjbpu = false;}
      if(xuZFzaCcFm == true){xuZFzaCcFm = false;}
      if(pdtwEeqscO == true){pdtwEeqscO = false;}
      if(TWOtrFcMDL == true){TWOtrFcMDL = false;}
      if(uJonyIbqVs == true){uJonyIbqVs = false;}
      if(IGUkMmlcPf == true){IGUkMmlcPf = false;}
      if(TpzbbagfNs == true){TpzbbagfNs = false;}
      if(xpYtqgnGyw == true){xpYtqgnGyw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITRBPMGKOA
{ 
  void AAekSiKJDz()
  { 
      bool hPrjzgKbcm = false;
      bool OMIHYhDKBr = false;
      bool YrectqVYcY = false;
      bool USJYNOjSEl = false;
      bool jIhMIYwUuu = false;
      bool bzjlhokOpH = false;
      bool LlzDSwDisJ = false;
      bool xkGOHPKSTU = false;
      bool tAdhwViWqY = false;
      bool dUcxayJdtM = false;
      bool VMbkxqsUeR = false;
      bool eSuVNKIQGw = false;
      bool NfrUfbHInI = false;
      bool FfXGygYrkE = false;
      bool bNqYsKZGjQ = false;
      bool osWxzoTGFU = false;
      bool jjgWLztnWf = false;
      bool kQfCUzoTbU = false;
      bool CAYWSMIaGI = false;
      bool MSmPUqfUMt = false;
      string XTHmZrOQaG;
      string kwUVGIyCAa;
      string CtEOeMRPzJ;
      string xpLJZtnrxN;
      string MjwkUNRixy;
      string mgBjEcOsIN;
      string ZzQRJtkKuM;
      string UFEmNRyTtR;
      string tiRBVQnbEw;
      string ftjjmNSdaZ;
      string bGnkdgbOVm;
      string euzpTqgPus;
      string FJGygZVUzA;
      string zTrTpmtgWn;
      string nZFRRjusQu;
      string gDihTRAoED;
      string LHOUmKCeAf;
      string wzrGFfDnfw;
      string ecDDTukKAX;
      string lFcTcfKkdH;
      if(XTHmZrOQaG == bGnkdgbOVm){hPrjzgKbcm = true;}
      else if(bGnkdgbOVm == XTHmZrOQaG){VMbkxqsUeR = true;}
      if(kwUVGIyCAa == euzpTqgPus){OMIHYhDKBr = true;}
      else if(euzpTqgPus == kwUVGIyCAa){eSuVNKIQGw = true;}
      if(CtEOeMRPzJ == FJGygZVUzA){YrectqVYcY = true;}
      else if(FJGygZVUzA == CtEOeMRPzJ){NfrUfbHInI = true;}
      if(xpLJZtnrxN == zTrTpmtgWn){USJYNOjSEl = true;}
      else if(zTrTpmtgWn == xpLJZtnrxN){FfXGygYrkE = true;}
      if(MjwkUNRixy == nZFRRjusQu){jIhMIYwUuu = true;}
      else if(nZFRRjusQu == MjwkUNRixy){bNqYsKZGjQ = true;}
      if(mgBjEcOsIN == gDihTRAoED){bzjlhokOpH = true;}
      else if(gDihTRAoED == mgBjEcOsIN){osWxzoTGFU = true;}
      if(ZzQRJtkKuM == LHOUmKCeAf){LlzDSwDisJ = true;}
      else if(LHOUmKCeAf == ZzQRJtkKuM){jjgWLztnWf = true;}
      if(UFEmNRyTtR == wzrGFfDnfw){xkGOHPKSTU = true;}
      if(tiRBVQnbEw == ecDDTukKAX){tAdhwViWqY = true;}
      if(ftjjmNSdaZ == lFcTcfKkdH){dUcxayJdtM = true;}
      while(wzrGFfDnfw == UFEmNRyTtR){kQfCUzoTbU = true;}
      while(ecDDTukKAX == ecDDTukKAX){CAYWSMIaGI = true;}
      while(lFcTcfKkdH == lFcTcfKkdH){MSmPUqfUMt = true;}
      if(hPrjzgKbcm == true){hPrjzgKbcm = false;}
      if(OMIHYhDKBr == true){OMIHYhDKBr = false;}
      if(YrectqVYcY == true){YrectqVYcY = false;}
      if(USJYNOjSEl == true){USJYNOjSEl = false;}
      if(jIhMIYwUuu == true){jIhMIYwUuu = false;}
      if(bzjlhokOpH == true){bzjlhokOpH = false;}
      if(LlzDSwDisJ == true){LlzDSwDisJ = false;}
      if(xkGOHPKSTU == true){xkGOHPKSTU = false;}
      if(tAdhwViWqY == true){tAdhwViWqY = false;}
      if(dUcxayJdtM == true){dUcxayJdtM = false;}
      if(VMbkxqsUeR == true){VMbkxqsUeR = false;}
      if(eSuVNKIQGw == true){eSuVNKIQGw = false;}
      if(NfrUfbHInI == true){NfrUfbHInI = false;}
      if(FfXGygYrkE == true){FfXGygYrkE = false;}
      if(bNqYsKZGjQ == true){bNqYsKZGjQ = false;}
      if(osWxzoTGFU == true){osWxzoTGFU = false;}
      if(jjgWLztnWf == true){jjgWLztnWf = false;}
      if(kQfCUzoTbU == true){kQfCUzoTbU = false;}
      if(CAYWSMIaGI == true){CAYWSMIaGI = false;}
      if(MSmPUqfUMt == true){MSmPUqfUMt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BABRKNRDGB
{ 
  void AtYiNEZIyo()
  { 
      bool GpVAHkJrWR = false;
      bool tWHLPmqfkl = false;
      bool sgmXbiqFnL = false;
      bool ozGsTjomLt = false;
      bool TZNdoORcTy = false;
      bool ofKauZCxYY = false;
      bool tEDLbuQNre = false;
      bool yETpSSSJhM = false;
      bool QOkoVJofys = false;
      bool hqNlAPVBBt = false;
      bool yDjnAjLTIb = false;
      bool GsPLIeSOoS = false;
      bool GkPzxGphpD = false;
      bool xRHnNMdxok = false;
      bool xUXVmobBdU = false;
      bool wHLinNnkqs = false;
      bool tddFeolbyu = false;
      bool AUYEVkMsLH = false;
      bool eoEUGoFXzA = false;
      bool YsGuqTpSqy = false;
      string yPiHRtyRxc;
      string DtJqJCSSSQ;
      string higjCMkfkM;
      string gxMwMXZRKw;
      string rsQOmeyAVT;
      string nnEldPiyFF;
      string ISfjuFhMdl;
      string bAHWXnRRxW;
      string OkKRXrsaRx;
      string naMFmZMfSg;
      string xkViqmghOp;
      string xQBhqWHOMD;
      string MHugxAnCix;
      string alzQZcOaZk;
      string LKLbzXZdOP;
      string RyTOTppolp;
      string yeyQOLQjIN;
      string IgnarBuSgZ;
      string aKmSfcSjwj;
      string lZoilgLuMn;
      if(yPiHRtyRxc == xkViqmghOp){GpVAHkJrWR = true;}
      else if(xkViqmghOp == yPiHRtyRxc){yDjnAjLTIb = true;}
      if(DtJqJCSSSQ == xQBhqWHOMD){tWHLPmqfkl = true;}
      else if(xQBhqWHOMD == DtJqJCSSSQ){GsPLIeSOoS = true;}
      if(higjCMkfkM == MHugxAnCix){sgmXbiqFnL = true;}
      else if(MHugxAnCix == higjCMkfkM){GkPzxGphpD = true;}
      if(gxMwMXZRKw == alzQZcOaZk){ozGsTjomLt = true;}
      else if(alzQZcOaZk == gxMwMXZRKw){xRHnNMdxok = true;}
      if(rsQOmeyAVT == LKLbzXZdOP){TZNdoORcTy = true;}
      else if(LKLbzXZdOP == rsQOmeyAVT){xUXVmobBdU = true;}
      if(nnEldPiyFF == RyTOTppolp){ofKauZCxYY = true;}
      else if(RyTOTppolp == nnEldPiyFF){wHLinNnkqs = true;}
      if(ISfjuFhMdl == yeyQOLQjIN){tEDLbuQNre = true;}
      else if(yeyQOLQjIN == ISfjuFhMdl){tddFeolbyu = true;}
      if(bAHWXnRRxW == IgnarBuSgZ){yETpSSSJhM = true;}
      if(OkKRXrsaRx == aKmSfcSjwj){QOkoVJofys = true;}
      if(naMFmZMfSg == lZoilgLuMn){hqNlAPVBBt = true;}
      while(IgnarBuSgZ == bAHWXnRRxW){AUYEVkMsLH = true;}
      while(aKmSfcSjwj == aKmSfcSjwj){eoEUGoFXzA = true;}
      while(lZoilgLuMn == lZoilgLuMn){YsGuqTpSqy = true;}
      if(GpVAHkJrWR == true){GpVAHkJrWR = false;}
      if(tWHLPmqfkl == true){tWHLPmqfkl = false;}
      if(sgmXbiqFnL == true){sgmXbiqFnL = false;}
      if(ozGsTjomLt == true){ozGsTjomLt = false;}
      if(TZNdoORcTy == true){TZNdoORcTy = false;}
      if(ofKauZCxYY == true){ofKauZCxYY = false;}
      if(tEDLbuQNre == true){tEDLbuQNre = false;}
      if(yETpSSSJhM == true){yETpSSSJhM = false;}
      if(QOkoVJofys == true){QOkoVJofys = false;}
      if(hqNlAPVBBt == true){hqNlAPVBBt = false;}
      if(yDjnAjLTIb == true){yDjnAjLTIb = false;}
      if(GsPLIeSOoS == true){GsPLIeSOoS = false;}
      if(GkPzxGphpD == true){GkPzxGphpD = false;}
      if(xRHnNMdxok == true){xRHnNMdxok = false;}
      if(xUXVmobBdU == true){xUXVmobBdU = false;}
      if(wHLinNnkqs == true){wHLinNnkqs = false;}
      if(tddFeolbyu == true){tddFeolbyu = false;}
      if(AUYEVkMsLH == true){AUYEVkMsLH = false;}
      if(eoEUGoFXzA == true){eoEUGoFXzA = false;}
      if(YsGuqTpSqy == true){YsGuqTpSqy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRYIFSALRY
{ 
  void xNYzhgIoKV()
  { 
      bool HpPluHJIGM = false;
      bool fDObQBcNyW = false;
      bool etMVeOsSaW = false;
      bool ufhVBfcAiW = false;
      bool WKEVGYbHnd = false;
      bool gmTcdNdtGg = false;
      bool NpgiRAVsZk = false;
      bool XbeaAUopOG = false;
      bool llexpHLEqn = false;
      bool BisBIfcVDG = false;
      bool CigDFEIrcJ = false;
      bool XmeAtbLirJ = false;
      bool nQBlinhcRT = false;
      bool qTlIDDEbql = false;
      bool zTbgPOEsHg = false;
      bool UsctRlguTR = false;
      bool VeZISEAVwq = false;
      bool WjrFKTnTWU = false;
      bool joVkyxprpQ = false;
      bool VIHZQUsTOK = false;
      string AxdALwsXYf;
      string LzGlqlXLVz;
      string TmFynIkURJ;
      string HGVBEGFJRB;
      string FFJQFAZQsc;
      string YopkfMqfMD;
      string KYFPYFcFgk;
      string gNtUtOdorm;
      string hUbnjSPkUr;
      string OYxOpfztrA;
      string WUiHuLtVpR;
      string iCmYUpwReF;
      string prjoVHQfdN;
      string OixrQMkTsY;
      string YstCJMkXsA;
      string jhPmJdktkm;
      string tOrbDzEuIH;
      string FbYGgwygfJ;
      string WslddfTKhl;
      string bpiFeJBRzJ;
      if(AxdALwsXYf == WUiHuLtVpR){HpPluHJIGM = true;}
      else if(WUiHuLtVpR == AxdALwsXYf){CigDFEIrcJ = true;}
      if(LzGlqlXLVz == iCmYUpwReF){fDObQBcNyW = true;}
      else if(iCmYUpwReF == LzGlqlXLVz){XmeAtbLirJ = true;}
      if(TmFynIkURJ == prjoVHQfdN){etMVeOsSaW = true;}
      else if(prjoVHQfdN == TmFynIkURJ){nQBlinhcRT = true;}
      if(HGVBEGFJRB == OixrQMkTsY){ufhVBfcAiW = true;}
      else if(OixrQMkTsY == HGVBEGFJRB){qTlIDDEbql = true;}
      if(FFJQFAZQsc == YstCJMkXsA){WKEVGYbHnd = true;}
      else if(YstCJMkXsA == FFJQFAZQsc){zTbgPOEsHg = true;}
      if(YopkfMqfMD == jhPmJdktkm){gmTcdNdtGg = true;}
      else if(jhPmJdktkm == YopkfMqfMD){UsctRlguTR = true;}
      if(KYFPYFcFgk == tOrbDzEuIH){NpgiRAVsZk = true;}
      else if(tOrbDzEuIH == KYFPYFcFgk){VeZISEAVwq = true;}
      if(gNtUtOdorm == FbYGgwygfJ){XbeaAUopOG = true;}
      if(hUbnjSPkUr == WslddfTKhl){llexpHLEqn = true;}
      if(OYxOpfztrA == bpiFeJBRzJ){BisBIfcVDG = true;}
      while(FbYGgwygfJ == gNtUtOdorm){WjrFKTnTWU = true;}
      while(WslddfTKhl == WslddfTKhl){joVkyxprpQ = true;}
      while(bpiFeJBRzJ == bpiFeJBRzJ){VIHZQUsTOK = true;}
      if(HpPluHJIGM == true){HpPluHJIGM = false;}
      if(fDObQBcNyW == true){fDObQBcNyW = false;}
      if(etMVeOsSaW == true){etMVeOsSaW = false;}
      if(ufhVBfcAiW == true){ufhVBfcAiW = false;}
      if(WKEVGYbHnd == true){WKEVGYbHnd = false;}
      if(gmTcdNdtGg == true){gmTcdNdtGg = false;}
      if(NpgiRAVsZk == true){NpgiRAVsZk = false;}
      if(XbeaAUopOG == true){XbeaAUopOG = false;}
      if(llexpHLEqn == true){llexpHLEqn = false;}
      if(BisBIfcVDG == true){BisBIfcVDG = false;}
      if(CigDFEIrcJ == true){CigDFEIrcJ = false;}
      if(XmeAtbLirJ == true){XmeAtbLirJ = false;}
      if(nQBlinhcRT == true){nQBlinhcRT = false;}
      if(qTlIDDEbql == true){qTlIDDEbql = false;}
      if(zTbgPOEsHg == true){zTbgPOEsHg = false;}
      if(UsctRlguTR == true){UsctRlguTR = false;}
      if(VeZISEAVwq == true){VeZISEAVwq = false;}
      if(WjrFKTnTWU == true){WjrFKTnTWU = false;}
      if(joVkyxprpQ == true){joVkyxprpQ = false;}
      if(VIHZQUsTOK == true){VIHZQUsTOK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GAPUIKMLGD
{ 
  void JiDPaDWCxg()
  { 
      bool zAljDcbYOU = false;
      bool lnrKzLbJqG = false;
      bool SKVPnPNUXs = false;
      bool MoZtTBXAbI = false;
      bool OppszpdIts = false;
      bool QFanQodWwn = false;
      bool OHAVIxOxqy = false;
      bool nahhrcTcPx = false;
      bool kFZecGOkde = false;
      bool WBEntGoUjC = false;
      bool afQwFoXsun = false;
      bool UBGyCIgVrC = false;
      bool hcTLalVsnk = false;
      bool mzsMWFncZm = false;
      bool hUopKVtGlk = false;
      bool ZTbgTxMFUS = false;
      bool SeFJAUHsbw = false;
      bool TDwFUNncBF = false;
      bool rPHCLSXLsY = false;
      bool siIGTDPeoo = false;
      string BOFReTbbiz;
      string KDMuaiJSsM;
      string VdrSCOhnkj;
      string BNedlHRmXF;
      string bpFrbWEYeD;
      string puyJIWWlOP;
      string lmpyyxYhIS;
      string RVumkfXApe;
      string JIIgtFPUUO;
      string kfXHSnzGse;
      string yWPLlTAKYc;
      string yWuiFddJEr;
      string gDMthkymUw;
      string fRGLgmrxua;
      string FFurQOjnCo;
      string JpCBxtJVdA;
      string VMocwgPjCR;
      string kgOdlbHUdS;
      string BJkflpOFNl;
      string dVStFrPRui;
      if(BOFReTbbiz == yWPLlTAKYc){zAljDcbYOU = true;}
      else if(yWPLlTAKYc == BOFReTbbiz){afQwFoXsun = true;}
      if(KDMuaiJSsM == yWuiFddJEr){lnrKzLbJqG = true;}
      else if(yWuiFddJEr == KDMuaiJSsM){UBGyCIgVrC = true;}
      if(VdrSCOhnkj == gDMthkymUw){SKVPnPNUXs = true;}
      else if(gDMthkymUw == VdrSCOhnkj){hcTLalVsnk = true;}
      if(BNedlHRmXF == fRGLgmrxua){MoZtTBXAbI = true;}
      else if(fRGLgmrxua == BNedlHRmXF){mzsMWFncZm = true;}
      if(bpFrbWEYeD == FFurQOjnCo){OppszpdIts = true;}
      else if(FFurQOjnCo == bpFrbWEYeD){hUopKVtGlk = true;}
      if(puyJIWWlOP == JpCBxtJVdA){QFanQodWwn = true;}
      else if(JpCBxtJVdA == puyJIWWlOP){ZTbgTxMFUS = true;}
      if(lmpyyxYhIS == VMocwgPjCR){OHAVIxOxqy = true;}
      else if(VMocwgPjCR == lmpyyxYhIS){SeFJAUHsbw = true;}
      if(RVumkfXApe == kgOdlbHUdS){nahhrcTcPx = true;}
      if(JIIgtFPUUO == BJkflpOFNl){kFZecGOkde = true;}
      if(kfXHSnzGse == dVStFrPRui){WBEntGoUjC = true;}
      while(kgOdlbHUdS == RVumkfXApe){TDwFUNncBF = true;}
      while(BJkflpOFNl == BJkflpOFNl){rPHCLSXLsY = true;}
      while(dVStFrPRui == dVStFrPRui){siIGTDPeoo = true;}
      if(zAljDcbYOU == true){zAljDcbYOU = false;}
      if(lnrKzLbJqG == true){lnrKzLbJqG = false;}
      if(SKVPnPNUXs == true){SKVPnPNUXs = false;}
      if(MoZtTBXAbI == true){MoZtTBXAbI = false;}
      if(OppszpdIts == true){OppszpdIts = false;}
      if(QFanQodWwn == true){QFanQodWwn = false;}
      if(OHAVIxOxqy == true){OHAVIxOxqy = false;}
      if(nahhrcTcPx == true){nahhrcTcPx = false;}
      if(kFZecGOkde == true){kFZecGOkde = false;}
      if(WBEntGoUjC == true){WBEntGoUjC = false;}
      if(afQwFoXsun == true){afQwFoXsun = false;}
      if(UBGyCIgVrC == true){UBGyCIgVrC = false;}
      if(hcTLalVsnk == true){hcTLalVsnk = false;}
      if(mzsMWFncZm == true){mzsMWFncZm = false;}
      if(hUopKVtGlk == true){hUopKVtGlk = false;}
      if(ZTbgTxMFUS == true){ZTbgTxMFUS = false;}
      if(SeFJAUHsbw == true){SeFJAUHsbw = false;}
      if(TDwFUNncBF == true){TDwFUNncBF = false;}
      if(rPHCLSXLsY == true){rPHCLSXLsY = false;}
      if(siIGTDPeoo == true){siIGTDPeoo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYWSRPJMBN
{ 
  void xnRSWtPjgf()
  { 
      bool xMobSNYtbP = false;
      bool bkLhgkumMQ = false;
      bool nwPbYVcOPm = false;
      bool OufOtVcPKL = false;
      bool iIjZnWlkgZ = false;
      bool xWBigAwMCw = false;
      bool kKenBfExmK = false;
      bool IecAhfMpnB = false;
      bool jqgopqswgt = false;
      bool ZPMNaYcuXI = false;
      bool SnxVRRsBBA = false;
      bool mFYBMscpxJ = false;
      bool lHQskrRPYI = false;
      bool DQReiutLWX = false;
      bool yrufGTpLBh = false;
      bool wlyNVKXEkY = false;
      bool AdbsxWnsSQ = false;
      bool zRSYLtMjlR = false;
      bool CGNqMRSDJY = false;
      bool XpaxXTQCij = false;
      string zzYcyNaOGy;
      string POgGeQElWq;
      string ZAjSgqKUOz;
      string UHeNdyLZVE;
      string GGQwxgrWDV;
      string hCzHDzPGwG;
      string CGzGcIiSbf;
      string FePRjSimUA;
      string znQsRRIXKd;
      string iEdPBzHKSo;
      string xZtXPDmgWj;
      string QcluGOoFoL;
      string ALHyxBAAQj;
      string KYTeCZtscN;
      string eaBZNFShIm;
      string KCVHolRwZO;
      string CmQlZrIGsg;
      string UwcafYJgjq;
      string hRqcZIDLpQ;
      string IyTNLrKOAV;
      if(zzYcyNaOGy == xZtXPDmgWj){xMobSNYtbP = true;}
      else if(xZtXPDmgWj == zzYcyNaOGy){SnxVRRsBBA = true;}
      if(POgGeQElWq == QcluGOoFoL){bkLhgkumMQ = true;}
      else if(QcluGOoFoL == POgGeQElWq){mFYBMscpxJ = true;}
      if(ZAjSgqKUOz == ALHyxBAAQj){nwPbYVcOPm = true;}
      else if(ALHyxBAAQj == ZAjSgqKUOz){lHQskrRPYI = true;}
      if(UHeNdyLZVE == KYTeCZtscN){OufOtVcPKL = true;}
      else if(KYTeCZtscN == UHeNdyLZVE){DQReiutLWX = true;}
      if(GGQwxgrWDV == eaBZNFShIm){iIjZnWlkgZ = true;}
      else if(eaBZNFShIm == GGQwxgrWDV){yrufGTpLBh = true;}
      if(hCzHDzPGwG == KCVHolRwZO){xWBigAwMCw = true;}
      else if(KCVHolRwZO == hCzHDzPGwG){wlyNVKXEkY = true;}
      if(CGzGcIiSbf == CmQlZrIGsg){kKenBfExmK = true;}
      else if(CmQlZrIGsg == CGzGcIiSbf){AdbsxWnsSQ = true;}
      if(FePRjSimUA == UwcafYJgjq){IecAhfMpnB = true;}
      if(znQsRRIXKd == hRqcZIDLpQ){jqgopqswgt = true;}
      if(iEdPBzHKSo == IyTNLrKOAV){ZPMNaYcuXI = true;}
      while(UwcafYJgjq == FePRjSimUA){zRSYLtMjlR = true;}
      while(hRqcZIDLpQ == hRqcZIDLpQ){CGNqMRSDJY = true;}
      while(IyTNLrKOAV == IyTNLrKOAV){XpaxXTQCij = true;}
      if(xMobSNYtbP == true){xMobSNYtbP = false;}
      if(bkLhgkumMQ == true){bkLhgkumMQ = false;}
      if(nwPbYVcOPm == true){nwPbYVcOPm = false;}
      if(OufOtVcPKL == true){OufOtVcPKL = false;}
      if(iIjZnWlkgZ == true){iIjZnWlkgZ = false;}
      if(xWBigAwMCw == true){xWBigAwMCw = false;}
      if(kKenBfExmK == true){kKenBfExmK = false;}
      if(IecAhfMpnB == true){IecAhfMpnB = false;}
      if(jqgopqswgt == true){jqgopqswgt = false;}
      if(ZPMNaYcuXI == true){ZPMNaYcuXI = false;}
      if(SnxVRRsBBA == true){SnxVRRsBBA = false;}
      if(mFYBMscpxJ == true){mFYBMscpxJ = false;}
      if(lHQskrRPYI == true){lHQskrRPYI = false;}
      if(DQReiutLWX == true){DQReiutLWX = false;}
      if(yrufGTpLBh == true){yrufGTpLBh = false;}
      if(wlyNVKXEkY == true){wlyNVKXEkY = false;}
      if(AdbsxWnsSQ == true){AdbsxWnsSQ = false;}
      if(zRSYLtMjlR == true){zRSYLtMjlR = false;}
      if(CGNqMRSDJY == true){CGNqMRSDJY = false;}
      if(XpaxXTQCij == true){XpaxXTQCij = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UFLOZWLONS
{ 
  void MCbdGFBWDl()
  { 
      bool ohWLKDWmrH = false;
      bool mTDWTZnOQg = false;
      bool qGOphwSIXQ = false;
      bool bmIpjCVJfx = false;
      bool LjigJcDwRx = false;
      bool aTBtkhTgcO = false;
      bool jOObfzKMmQ = false;
      bool DehSUGWgfF = false;
      bool sVqZoHlNFB = false;
      bool hofRNxUHBJ = false;
      bool RpJAtuliYd = false;
      bool KmAXVNWolX = false;
      bool NwHliNyQFX = false;
      bool lPfVmCMpft = false;
      bool VDoapuoIwz = false;
      bool ZfUcwUiWRf = false;
      bool wVcBrtGdkS = false;
      bool AgJrCKHfum = false;
      bool YpTFxGuCZR = false;
      bool ToYAxAZmiu = false;
      string sQprCCNKkm;
      string aWNWSEmHts;
      string FyECotJBJh;
      string pVndDRkscp;
      string GCXaZPOzst;
      string SyRwUtLnDI;
      string rLACxFhjSB;
      string TteElDadcY;
      string eKIPPrDrIJ;
      string FxoTxtCUcU;
      string hefrZXTNJR;
      string ShLddhDjmE;
      string BoaJuVEKGr;
      string BFAIpzdQoq;
      string YpiqpWkKpO;
      string qRhYSsDWwE;
      string TIGRPNhDne;
      string DmtufLFjSY;
      string jsUqAiWbox;
      string wHTkXPiRab;
      if(sQprCCNKkm == hefrZXTNJR){ohWLKDWmrH = true;}
      else if(hefrZXTNJR == sQprCCNKkm){RpJAtuliYd = true;}
      if(aWNWSEmHts == ShLddhDjmE){mTDWTZnOQg = true;}
      else if(ShLddhDjmE == aWNWSEmHts){KmAXVNWolX = true;}
      if(FyECotJBJh == BoaJuVEKGr){qGOphwSIXQ = true;}
      else if(BoaJuVEKGr == FyECotJBJh){NwHliNyQFX = true;}
      if(pVndDRkscp == BFAIpzdQoq){bmIpjCVJfx = true;}
      else if(BFAIpzdQoq == pVndDRkscp){lPfVmCMpft = true;}
      if(GCXaZPOzst == YpiqpWkKpO){LjigJcDwRx = true;}
      else if(YpiqpWkKpO == GCXaZPOzst){VDoapuoIwz = true;}
      if(SyRwUtLnDI == qRhYSsDWwE){aTBtkhTgcO = true;}
      else if(qRhYSsDWwE == SyRwUtLnDI){ZfUcwUiWRf = true;}
      if(rLACxFhjSB == TIGRPNhDne){jOObfzKMmQ = true;}
      else if(TIGRPNhDne == rLACxFhjSB){wVcBrtGdkS = true;}
      if(TteElDadcY == DmtufLFjSY){DehSUGWgfF = true;}
      if(eKIPPrDrIJ == jsUqAiWbox){sVqZoHlNFB = true;}
      if(FxoTxtCUcU == wHTkXPiRab){hofRNxUHBJ = true;}
      while(DmtufLFjSY == TteElDadcY){AgJrCKHfum = true;}
      while(jsUqAiWbox == jsUqAiWbox){YpTFxGuCZR = true;}
      while(wHTkXPiRab == wHTkXPiRab){ToYAxAZmiu = true;}
      if(ohWLKDWmrH == true){ohWLKDWmrH = false;}
      if(mTDWTZnOQg == true){mTDWTZnOQg = false;}
      if(qGOphwSIXQ == true){qGOphwSIXQ = false;}
      if(bmIpjCVJfx == true){bmIpjCVJfx = false;}
      if(LjigJcDwRx == true){LjigJcDwRx = false;}
      if(aTBtkhTgcO == true){aTBtkhTgcO = false;}
      if(jOObfzKMmQ == true){jOObfzKMmQ = false;}
      if(DehSUGWgfF == true){DehSUGWgfF = false;}
      if(sVqZoHlNFB == true){sVqZoHlNFB = false;}
      if(hofRNxUHBJ == true){hofRNxUHBJ = false;}
      if(RpJAtuliYd == true){RpJAtuliYd = false;}
      if(KmAXVNWolX == true){KmAXVNWolX = false;}
      if(NwHliNyQFX == true){NwHliNyQFX = false;}
      if(lPfVmCMpft == true){lPfVmCMpft = false;}
      if(VDoapuoIwz == true){VDoapuoIwz = false;}
      if(ZfUcwUiWRf == true){ZfUcwUiWRf = false;}
      if(wVcBrtGdkS == true){wVcBrtGdkS = false;}
      if(AgJrCKHfum == true){AgJrCKHfum = false;}
      if(YpTFxGuCZR == true){YpTFxGuCZR = false;}
      if(ToYAxAZmiu == true){ToYAxAZmiu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTCYUFRROJ
{ 
  void DdlFfKkrJy()
  { 
      bool cWmIuxFDwt = false;
      bool HRxsccChxk = false;
      bool wgzogWammg = false;
      bool GiQBKSMMmS = false;
      bool JAIVffIUrZ = false;
      bool DkFmjuXxbY = false;
      bool VRPPmYBwiJ = false;
      bool PptebwXcIA = false;
      bool OGuNcUcdQO = false;
      bool uOjOwqjriG = false;
      bool eLkhJNqaKn = false;
      bool XunaKOWCmR = false;
      bool uWeUOBFehk = false;
      bool LetCVCVMDP = false;
      bool dCSbqAZIEg = false;
      bool UhFQLHgPTH = false;
      bool HMrZcrAlEH = false;
      bool sJzWnsDCdO = false;
      bool bwaAQdYcpO = false;
      bool UFsuIRJszy = false;
      string feVBPXTbwx;
      string nHYszNIKZM;
      string ZTOILGbFuF;
      string WWXLtGyReg;
      string loGatfgtbK;
      string iMPqLMPMpI;
      string uOfqaQjMyr;
      string OqfrajMnNe;
      string YhdjWKHgzh;
      string plaWkXIOzd;
      string wUwiwqgWQb;
      string zazKiNjuUQ;
      string JCNQCcPIGC;
      string bynjhEkune;
      string djQXhOlPmX;
      string mMtiTtGfgS;
      string bXQNzBlOcd;
      string boHplZlohm;
      string pzUiPOEFPn;
      string xFNUCFSDXg;
      if(feVBPXTbwx == wUwiwqgWQb){cWmIuxFDwt = true;}
      else if(wUwiwqgWQb == feVBPXTbwx){eLkhJNqaKn = true;}
      if(nHYszNIKZM == zazKiNjuUQ){HRxsccChxk = true;}
      else if(zazKiNjuUQ == nHYszNIKZM){XunaKOWCmR = true;}
      if(ZTOILGbFuF == JCNQCcPIGC){wgzogWammg = true;}
      else if(JCNQCcPIGC == ZTOILGbFuF){uWeUOBFehk = true;}
      if(WWXLtGyReg == bynjhEkune){GiQBKSMMmS = true;}
      else if(bynjhEkune == WWXLtGyReg){LetCVCVMDP = true;}
      if(loGatfgtbK == djQXhOlPmX){JAIVffIUrZ = true;}
      else if(djQXhOlPmX == loGatfgtbK){dCSbqAZIEg = true;}
      if(iMPqLMPMpI == mMtiTtGfgS){DkFmjuXxbY = true;}
      else if(mMtiTtGfgS == iMPqLMPMpI){UhFQLHgPTH = true;}
      if(uOfqaQjMyr == bXQNzBlOcd){VRPPmYBwiJ = true;}
      else if(bXQNzBlOcd == uOfqaQjMyr){HMrZcrAlEH = true;}
      if(OqfrajMnNe == boHplZlohm){PptebwXcIA = true;}
      if(YhdjWKHgzh == pzUiPOEFPn){OGuNcUcdQO = true;}
      if(plaWkXIOzd == xFNUCFSDXg){uOjOwqjriG = true;}
      while(boHplZlohm == OqfrajMnNe){sJzWnsDCdO = true;}
      while(pzUiPOEFPn == pzUiPOEFPn){bwaAQdYcpO = true;}
      while(xFNUCFSDXg == xFNUCFSDXg){UFsuIRJszy = true;}
      if(cWmIuxFDwt == true){cWmIuxFDwt = false;}
      if(HRxsccChxk == true){HRxsccChxk = false;}
      if(wgzogWammg == true){wgzogWammg = false;}
      if(GiQBKSMMmS == true){GiQBKSMMmS = false;}
      if(JAIVffIUrZ == true){JAIVffIUrZ = false;}
      if(DkFmjuXxbY == true){DkFmjuXxbY = false;}
      if(VRPPmYBwiJ == true){VRPPmYBwiJ = false;}
      if(PptebwXcIA == true){PptebwXcIA = false;}
      if(OGuNcUcdQO == true){OGuNcUcdQO = false;}
      if(uOjOwqjriG == true){uOjOwqjriG = false;}
      if(eLkhJNqaKn == true){eLkhJNqaKn = false;}
      if(XunaKOWCmR == true){XunaKOWCmR = false;}
      if(uWeUOBFehk == true){uWeUOBFehk = false;}
      if(LetCVCVMDP == true){LetCVCVMDP = false;}
      if(dCSbqAZIEg == true){dCSbqAZIEg = false;}
      if(UhFQLHgPTH == true){UhFQLHgPTH = false;}
      if(HMrZcrAlEH == true){HMrZcrAlEH = false;}
      if(sJzWnsDCdO == true){sJzWnsDCdO = false;}
      if(bwaAQdYcpO == true){bwaAQdYcpO = false;}
      if(UFsuIRJszy == true){UFsuIRJszy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPTZJBVTGA
{ 
  void EDSFMQODPJ()
  { 
      bool xwxBBFIUfo = false;
      bool cSqXbWVYVH = false;
      bool EHsdoEhZSS = false;
      bool lzhEVMSCFo = false;
      bool ftOxzwQadO = false;
      bool PBLpGoDSLw = false;
      bool XiCNCcjlBO = false;
      bool ESSfaJrues = false;
      bool mHuEDknqyg = false;
      bool JzpIRwrBtW = false;
      bool MeYOKwifOx = false;
      bool wHnSJQmxKR = false;
      bool ornUFEbJOd = false;
      bool QqAHgIhftG = false;
      bool CHcBjBLXzA = false;
      bool JtqcgTpDJG = false;
      bool UYRjfFGflB = false;
      bool hGDDPgPmkD = false;
      bool sDKNUWAXZM = false;
      bool RdWmkcprUe = false;
      string OxieHCkPUc;
      string uZZcsNoMBY;
      string qKlEFDFMaI;
      string RVrgrrcWcn;
      string gBQJtZQlLJ;
      string aVOrODKeYE;
      string wXoMLZhrjA;
      string kRjNrotcJe;
      string lSBQhwHASn;
      string gyxYrJMEyU;
      string rYCKYIkBAY;
      string JgUsRcWXdO;
      string ShZuTmULVh;
      string coeomNQprZ;
      string KFzsezcDGO;
      string lnZiBKyHql;
      string nZfRuTCfGE;
      string MffEDMhfPT;
      string JQEGunPumb;
      string OIyGlkZhxK;
      if(OxieHCkPUc == rYCKYIkBAY){xwxBBFIUfo = true;}
      else if(rYCKYIkBAY == OxieHCkPUc){MeYOKwifOx = true;}
      if(uZZcsNoMBY == JgUsRcWXdO){cSqXbWVYVH = true;}
      else if(JgUsRcWXdO == uZZcsNoMBY){wHnSJQmxKR = true;}
      if(qKlEFDFMaI == ShZuTmULVh){EHsdoEhZSS = true;}
      else if(ShZuTmULVh == qKlEFDFMaI){ornUFEbJOd = true;}
      if(RVrgrrcWcn == coeomNQprZ){lzhEVMSCFo = true;}
      else if(coeomNQprZ == RVrgrrcWcn){QqAHgIhftG = true;}
      if(gBQJtZQlLJ == KFzsezcDGO){ftOxzwQadO = true;}
      else if(KFzsezcDGO == gBQJtZQlLJ){CHcBjBLXzA = true;}
      if(aVOrODKeYE == lnZiBKyHql){PBLpGoDSLw = true;}
      else if(lnZiBKyHql == aVOrODKeYE){JtqcgTpDJG = true;}
      if(wXoMLZhrjA == nZfRuTCfGE){XiCNCcjlBO = true;}
      else if(nZfRuTCfGE == wXoMLZhrjA){UYRjfFGflB = true;}
      if(kRjNrotcJe == MffEDMhfPT){ESSfaJrues = true;}
      if(lSBQhwHASn == JQEGunPumb){mHuEDknqyg = true;}
      if(gyxYrJMEyU == OIyGlkZhxK){JzpIRwrBtW = true;}
      while(MffEDMhfPT == kRjNrotcJe){hGDDPgPmkD = true;}
      while(JQEGunPumb == JQEGunPumb){sDKNUWAXZM = true;}
      while(OIyGlkZhxK == OIyGlkZhxK){RdWmkcprUe = true;}
      if(xwxBBFIUfo == true){xwxBBFIUfo = false;}
      if(cSqXbWVYVH == true){cSqXbWVYVH = false;}
      if(EHsdoEhZSS == true){EHsdoEhZSS = false;}
      if(lzhEVMSCFo == true){lzhEVMSCFo = false;}
      if(ftOxzwQadO == true){ftOxzwQadO = false;}
      if(PBLpGoDSLw == true){PBLpGoDSLw = false;}
      if(XiCNCcjlBO == true){XiCNCcjlBO = false;}
      if(ESSfaJrues == true){ESSfaJrues = false;}
      if(mHuEDknqyg == true){mHuEDknqyg = false;}
      if(JzpIRwrBtW == true){JzpIRwrBtW = false;}
      if(MeYOKwifOx == true){MeYOKwifOx = false;}
      if(wHnSJQmxKR == true){wHnSJQmxKR = false;}
      if(ornUFEbJOd == true){ornUFEbJOd = false;}
      if(QqAHgIhftG == true){QqAHgIhftG = false;}
      if(CHcBjBLXzA == true){CHcBjBLXzA = false;}
      if(JtqcgTpDJG == true){JtqcgTpDJG = false;}
      if(UYRjfFGflB == true){UYRjfFGflB = false;}
      if(hGDDPgPmkD == true){hGDDPgPmkD = false;}
      if(sDKNUWAXZM == true){sDKNUWAXZM = false;}
      if(RdWmkcprUe == true){RdWmkcprUe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKBVFPJKLG
{ 
  void tigqhzhnNp()
  { 
      bool sIGykSZIXb = false;
      bool WxbLbRgssX = false;
      bool ZHOzQOARqE = false;
      bool xqprLlcVJL = false;
      bool QCzAdHTlNa = false;
      bool lFISulsHgW = false;
      bool SIQTdeGizo = false;
      bool oLjgHWIOVJ = false;
      bool tNEQSrhXwY = false;
      bool rVnlsHlfWy = false;
      bool AjmXkaUbKY = false;
      bool dekWcEEzBk = false;
      bool wilaxTWxnA = false;
      bool jbqWJJafeq = false;
      bool WGMXuNjRJo = false;
      bool DmekBQxLaR = false;
      bool EWnKnBmNNS = false;
      bool cXTJNpVOei = false;
      bool iFnzwxxGUr = false;
      bool MOFNmASCit = false;
      string qTWNCdeVOb;
      string rGZiocCyfd;
      string LWIWxueIcu;
      string UmrwQkrnhs;
      string BqsxNxtezB;
      string HHSxGTLAQG;
      string yVsTGENcSE;
      string kOQlbUdKIz;
      string AAJanMTupx;
      string ZqXateyYpI;
      string iQMuPrqfUk;
      string pAqQFyMRft;
      string jSlVetqoqx;
      string WEUAQjmOKu;
      string VnZFGYzGUw;
      string RfswXPeqQV;
      string BBoXOkfqAV;
      string KyGkXwsgOF;
      string tjUuepLXbA;
      string EwxosTyBpV;
      if(qTWNCdeVOb == iQMuPrqfUk){sIGykSZIXb = true;}
      else if(iQMuPrqfUk == qTWNCdeVOb){AjmXkaUbKY = true;}
      if(rGZiocCyfd == pAqQFyMRft){WxbLbRgssX = true;}
      else if(pAqQFyMRft == rGZiocCyfd){dekWcEEzBk = true;}
      if(LWIWxueIcu == jSlVetqoqx){ZHOzQOARqE = true;}
      else if(jSlVetqoqx == LWIWxueIcu){wilaxTWxnA = true;}
      if(UmrwQkrnhs == WEUAQjmOKu){xqprLlcVJL = true;}
      else if(WEUAQjmOKu == UmrwQkrnhs){jbqWJJafeq = true;}
      if(BqsxNxtezB == VnZFGYzGUw){QCzAdHTlNa = true;}
      else if(VnZFGYzGUw == BqsxNxtezB){WGMXuNjRJo = true;}
      if(HHSxGTLAQG == RfswXPeqQV){lFISulsHgW = true;}
      else if(RfswXPeqQV == HHSxGTLAQG){DmekBQxLaR = true;}
      if(yVsTGENcSE == BBoXOkfqAV){SIQTdeGizo = true;}
      else if(BBoXOkfqAV == yVsTGENcSE){EWnKnBmNNS = true;}
      if(kOQlbUdKIz == KyGkXwsgOF){oLjgHWIOVJ = true;}
      if(AAJanMTupx == tjUuepLXbA){tNEQSrhXwY = true;}
      if(ZqXateyYpI == EwxosTyBpV){rVnlsHlfWy = true;}
      while(KyGkXwsgOF == kOQlbUdKIz){cXTJNpVOei = true;}
      while(tjUuepLXbA == tjUuepLXbA){iFnzwxxGUr = true;}
      while(EwxosTyBpV == EwxosTyBpV){MOFNmASCit = true;}
      if(sIGykSZIXb == true){sIGykSZIXb = false;}
      if(WxbLbRgssX == true){WxbLbRgssX = false;}
      if(ZHOzQOARqE == true){ZHOzQOARqE = false;}
      if(xqprLlcVJL == true){xqprLlcVJL = false;}
      if(QCzAdHTlNa == true){QCzAdHTlNa = false;}
      if(lFISulsHgW == true){lFISulsHgW = false;}
      if(SIQTdeGizo == true){SIQTdeGizo = false;}
      if(oLjgHWIOVJ == true){oLjgHWIOVJ = false;}
      if(tNEQSrhXwY == true){tNEQSrhXwY = false;}
      if(rVnlsHlfWy == true){rVnlsHlfWy = false;}
      if(AjmXkaUbKY == true){AjmXkaUbKY = false;}
      if(dekWcEEzBk == true){dekWcEEzBk = false;}
      if(wilaxTWxnA == true){wilaxTWxnA = false;}
      if(jbqWJJafeq == true){jbqWJJafeq = false;}
      if(WGMXuNjRJo == true){WGMXuNjRJo = false;}
      if(DmekBQxLaR == true){DmekBQxLaR = false;}
      if(EWnKnBmNNS == true){EWnKnBmNNS = false;}
      if(cXTJNpVOei == true){cXTJNpVOei = false;}
      if(iFnzwxxGUr == true){iFnzwxxGUr = false;}
      if(MOFNmASCit == true){MOFNmASCit = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFCUCRJOFT
{ 
  void ZyNUbebRmE()
  { 
      bool fqcXyrYjMm = false;
      bool LuEliaDeQQ = false;
      bool juMYRPXtzm = false;
      bool RpRRbfOVLS = false;
      bool CsWRItNhFT = false;
      bool QdtzLkdEFi = false;
      bool UdkZUUdlJC = false;
      bool LhSxOqXuQW = false;
      bool BooeVnuSFp = false;
      bool BKPcyXIxwm = false;
      bool PaXCHiKwjU = false;
      bool NinigenFDg = false;
      bool ZLgTABSozp = false;
      bool iZycHZRmWm = false;
      bool czhkcRWgwS = false;
      bool jCtPNDtECG = false;
      bool QUxskmkKaG = false;
      bool NBiQEZdwph = false;
      bool eksfGgfiPD = false;
      bool fMjPVHBnzp = false;
      string GqlmmMnrry;
      string BYwBtBKtbO;
      string IoHxgbUFkm;
      string kxYYxefBQo;
      string aqsHqAptcG;
      string pySNqRjoFL;
      string qiHFMDzWDP;
      string VJcmnRuzFg;
      string lZbewmdLhf;
      string upuExqintm;
      string ASpNkgUfYZ;
      string VjiYZRGbJZ;
      string ZnoXTeNXpw;
      string hHERfSjOsO;
      string RymHJLHVef;
      string kHeUNMcRtF;
      string SxobqNeQrH;
      string grhtHaAgNI;
      string WrsKLacjET;
      string pRTnuUIKPw;
      if(GqlmmMnrry == ASpNkgUfYZ){fqcXyrYjMm = true;}
      else if(ASpNkgUfYZ == GqlmmMnrry){PaXCHiKwjU = true;}
      if(BYwBtBKtbO == VjiYZRGbJZ){LuEliaDeQQ = true;}
      else if(VjiYZRGbJZ == BYwBtBKtbO){NinigenFDg = true;}
      if(IoHxgbUFkm == ZnoXTeNXpw){juMYRPXtzm = true;}
      else if(ZnoXTeNXpw == IoHxgbUFkm){ZLgTABSozp = true;}
      if(kxYYxefBQo == hHERfSjOsO){RpRRbfOVLS = true;}
      else if(hHERfSjOsO == kxYYxefBQo){iZycHZRmWm = true;}
      if(aqsHqAptcG == RymHJLHVef){CsWRItNhFT = true;}
      else if(RymHJLHVef == aqsHqAptcG){czhkcRWgwS = true;}
      if(pySNqRjoFL == kHeUNMcRtF){QdtzLkdEFi = true;}
      else if(kHeUNMcRtF == pySNqRjoFL){jCtPNDtECG = true;}
      if(qiHFMDzWDP == SxobqNeQrH){UdkZUUdlJC = true;}
      else if(SxobqNeQrH == qiHFMDzWDP){QUxskmkKaG = true;}
      if(VJcmnRuzFg == grhtHaAgNI){LhSxOqXuQW = true;}
      if(lZbewmdLhf == WrsKLacjET){BooeVnuSFp = true;}
      if(upuExqintm == pRTnuUIKPw){BKPcyXIxwm = true;}
      while(grhtHaAgNI == VJcmnRuzFg){NBiQEZdwph = true;}
      while(WrsKLacjET == WrsKLacjET){eksfGgfiPD = true;}
      while(pRTnuUIKPw == pRTnuUIKPw){fMjPVHBnzp = true;}
      if(fqcXyrYjMm == true){fqcXyrYjMm = false;}
      if(LuEliaDeQQ == true){LuEliaDeQQ = false;}
      if(juMYRPXtzm == true){juMYRPXtzm = false;}
      if(RpRRbfOVLS == true){RpRRbfOVLS = false;}
      if(CsWRItNhFT == true){CsWRItNhFT = false;}
      if(QdtzLkdEFi == true){QdtzLkdEFi = false;}
      if(UdkZUUdlJC == true){UdkZUUdlJC = false;}
      if(LhSxOqXuQW == true){LhSxOqXuQW = false;}
      if(BooeVnuSFp == true){BooeVnuSFp = false;}
      if(BKPcyXIxwm == true){BKPcyXIxwm = false;}
      if(PaXCHiKwjU == true){PaXCHiKwjU = false;}
      if(NinigenFDg == true){NinigenFDg = false;}
      if(ZLgTABSozp == true){ZLgTABSozp = false;}
      if(iZycHZRmWm == true){iZycHZRmWm = false;}
      if(czhkcRWgwS == true){czhkcRWgwS = false;}
      if(jCtPNDtECG == true){jCtPNDtECG = false;}
      if(QUxskmkKaG == true){QUxskmkKaG = false;}
      if(NBiQEZdwph == true){NBiQEZdwph = false;}
      if(eksfGgfiPD == true){eksfGgfiPD = false;}
      if(fMjPVHBnzp == true){fMjPVHBnzp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYDZFASCAS
{ 
  void XWOHNYkpys()
  { 
      bool bogYgRjNkl = false;
      bool AxSdQeFHrR = false;
      bool csncXzPjeV = false;
      bool iHPypiffOH = false;
      bool meUXLSVSsV = false;
      bool DbneViBEBh = false;
      bool CziOCshTnh = false;
      bool zYskdxXPQE = false;
      bool dwpJSGTjcH = false;
      bool gaegEnwGUS = false;
      bool kBeLWdiCAX = false;
      bool KknwEFIYuu = false;
      bool YyqgAXsMfp = false;
      bool BRuyTbRemo = false;
      bool XQiEwwmiby = false;
      bool eWKYsmJyLy = false;
      bool jVWKWroocb = false;
      bool ndlFXHOmjD = false;
      bool jKjgLdHVEf = false;
      bool RSTnFBsYgE = false;
      string nAFeaiKBxP;
      string VqdmrIfWLX;
      string oYtLKaJRKz;
      string UEjysCugbj;
      string fORJfhpZgM;
      string bXuOSPFtTz;
      string ZrqxuRGftp;
      string MytarZGjec;
      string kikyXwIUfc;
      string wBNbKmXTOO;
      string aKfpzdcTWr;
      string IUOqOpHsZy;
      string IlAQsKjSQE;
      string CmVQBaDtyt;
      string TnymTamWNU;
      string eetPGoJOwn;
      string sKDRpVzyon;
      string mMtfeTnMwS;
      string XNFuZXsFJM;
      string QnxJAIjfxy;
      if(nAFeaiKBxP == aKfpzdcTWr){bogYgRjNkl = true;}
      else if(aKfpzdcTWr == nAFeaiKBxP){kBeLWdiCAX = true;}
      if(VqdmrIfWLX == IUOqOpHsZy){AxSdQeFHrR = true;}
      else if(IUOqOpHsZy == VqdmrIfWLX){KknwEFIYuu = true;}
      if(oYtLKaJRKz == IlAQsKjSQE){csncXzPjeV = true;}
      else if(IlAQsKjSQE == oYtLKaJRKz){YyqgAXsMfp = true;}
      if(UEjysCugbj == CmVQBaDtyt){iHPypiffOH = true;}
      else if(CmVQBaDtyt == UEjysCugbj){BRuyTbRemo = true;}
      if(fORJfhpZgM == TnymTamWNU){meUXLSVSsV = true;}
      else if(TnymTamWNU == fORJfhpZgM){XQiEwwmiby = true;}
      if(bXuOSPFtTz == eetPGoJOwn){DbneViBEBh = true;}
      else if(eetPGoJOwn == bXuOSPFtTz){eWKYsmJyLy = true;}
      if(ZrqxuRGftp == sKDRpVzyon){CziOCshTnh = true;}
      else if(sKDRpVzyon == ZrqxuRGftp){jVWKWroocb = true;}
      if(MytarZGjec == mMtfeTnMwS){zYskdxXPQE = true;}
      if(kikyXwIUfc == XNFuZXsFJM){dwpJSGTjcH = true;}
      if(wBNbKmXTOO == QnxJAIjfxy){gaegEnwGUS = true;}
      while(mMtfeTnMwS == MytarZGjec){ndlFXHOmjD = true;}
      while(XNFuZXsFJM == XNFuZXsFJM){jKjgLdHVEf = true;}
      while(QnxJAIjfxy == QnxJAIjfxy){RSTnFBsYgE = true;}
      if(bogYgRjNkl == true){bogYgRjNkl = false;}
      if(AxSdQeFHrR == true){AxSdQeFHrR = false;}
      if(csncXzPjeV == true){csncXzPjeV = false;}
      if(iHPypiffOH == true){iHPypiffOH = false;}
      if(meUXLSVSsV == true){meUXLSVSsV = false;}
      if(DbneViBEBh == true){DbneViBEBh = false;}
      if(CziOCshTnh == true){CziOCshTnh = false;}
      if(zYskdxXPQE == true){zYskdxXPQE = false;}
      if(dwpJSGTjcH == true){dwpJSGTjcH = false;}
      if(gaegEnwGUS == true){gaegEnwGUS = false;}
      if(kBeLWdiCAX == true){kBeLWdiCAX = false;}
      if(KknwEFIYuu == true){KknwEFIYuu = false;}
      if(YyqgAXsMfp == true){YyqgAXsMfp = false;}
      if(BRuyTbRemo == true){BRuyTbRemo = false;}
      if(XQiEwwmiby == true){XQiEwwmiby = false;}
      if(eWKYsmJyLy == true){eWKYsmJyLy = false;}
      if(jVWKWroocb == true){jVWKWroocb = false;}
      if(ndlFXHOmjD == true){ndlFXHOmjD = false;}
      if(jKjgLdHVEf == true){jKjgLdHVEf = false;}
      if(RSTnFBsYgE == true){RSTnFBsYgE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTNWNAZYNQ
{ 
  void mFEOqCEkBB()
  { 
      bool gdzmCHldbu = false;
      bool YhMxumUUaK = false;
      bool cTkXZZgUuo = false;
      bool saHIadUwgb = false;
      bool nDibQVwKqo = false;
      bool eDeltNrbMb = false;
      bool ZRilCxaEWR = false;
      bool SYmyVYjJGE = false;
      bool dVdGJowUON = false;
      bool kriEBWTxZT = false;
      bool trnYVGQfPU = false;
      bool ciVIyEmcbM = false;
      bool AFpJfZoiwz = false;
      bool FlimJkhEjD = false;
      bool YPEsjBWZFx = false;
      bool jqUNSnCdsu = false;
      bool QhjQPqziyM = false;
      bool VirYmjAwZd = false;
      bool DOcyONQVTU = false;
      bool iELolqfnds = false;
      string aBpQQlqLFx;
      string PmqBGFiLDY;
      string smDzIbwAWV;
      string uSgKOSZeZL;
      string qfsNFIIqMf;
      string tnQYTmypIo;
      string oqniBwFfmn;
      string fEkqhMsotz;
      string TFmpaHCHqa;
      string UiVkVAqJLI;
      string DbEYApDZqH;
      string sIuIUjDxIt;
      string txoMTwhzVg;
      string UicluqANpk;
      string EbQjgLnMQl;
      string xsBRNFmrFD;
      string IDDKlKeJNd;
      string ioHXpRgEeH;
      string IUiijahLXp;
      string DIIlbAXFxW;
      if(aBpQQlqLFx == DbEYApDZqH){gdzmCHldbu = true;}
      else if(DbEYApDZqH == aBpQQlqLFx){trnYVGQfPU = true;}
      if(PmqBGFiLDY == sIuIUjDxIt){YhMxumUUaK = true;}
      else if(sIuIUjDxIt == PmqBGFiLDY){ciVIyEmcbM = true;}
      if(smDzIbwAWV == txoMTwhzVg){cTkXZZgUuo = true;}
      else if(txoMTwhzVg == smDzIbwAWV){AFpJfZoiwz = true;}
      if(uSgKOSZeZL == UicluqANpk){saHIadUwgb = true;}
      else if(UicluqANpk == uSgKOSZeZL){FlimJkhEjD = true;}
      if(qfsNFIIqMf == EbQjgLnMQl){nDibQVwKqo = true;}
      else if(EbQjgLnMQl == qfsNFIIqMf){YPEsjBWZFx = true;}
      if(tnQYTmypIo == xsBRNFmrFD){eDeltNrbMb = true;}
      else if(xsBRNFmrFD == tnQYTmypIo){jqUNSnCdsu = true;}
      if(oqniBwFfmn == IDDKlKeJNd){ZRilCxaEWR = true;}
      else if(IDDKlKeJNd == oqniBwFfmn){QhjQPqziyM = true;}
      if(fEkqhMsotz == ioHXpRgEeH){SYmyVYjJGE = true;}
      if(TFmpaHCHqa == IUiijahLXp){dVdGJowUON = true;}
      if(UiVkVAqJLI == DIIlbAXFxW){kriEBWTxZT = true;}
      while(ioHXpRgEeH == fEkqhMsotz){VirYmjAwZd = true;}
      while(IUiijahLXp == IUiijahLXp){DOcyONQVTU = true;}
      while(DIIlbAXFxW == DIIlbAXFxW){iELolqfnds = true;}
      if(gdzmCHldbu == true){gdzmCHldbu = false;}
      if(YhMxumUUaK == true){YhMxumUUaK = false;}
      if(cTkXZZgUuo == true){cTkXZZgUuo = false;}
      if(saHIadUwgb == true){saHIadUwgb = false;}
      if(nDibQVwKqo == true){nDibQVwKqo = false;}
      if(eDeltNrbMb == true){eDeltNrbMb = false;}
      if(ZRilCxaEWR == true){ZRilCxaEWR = false;}
      if(SYmyVYjJGE == true){SYmyVYjJGE = false;}
      if(dVdGJowUON == true){dVdGJowUON = false;}
      if(kriEBWTxZT == true){kriEBWTxZT = false;}
      if(trnYVGQfPU == true){trnYVGQfPU = false;}
      if(ciVIyEmcbM == true){ciVIyEmcbM = false;}
      if(AFpJfZoiwz == true){AFpJfZoiwz = false;}
      if(FlimJkhEjD == true){FlimJkhEjD = false;}
      if(YPEsjBWZFx == true){YPEsjBWZFx = false;}
      if(jqUNSnCdsu == true){jqUNSnCdsu = false;}
      if(QhjQPqziyM == true){QhjQPqziyM = false;}
      if(VirYmjAwZd == true){VirYmjAwZd = false;}
      if(DOcyONQVTU == true){DOcyONQVTU = false;}
      if(iELolqfnds == true){iELolqfnds = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPZWWUBUXI
{ 
  void heEmWdzRAj()
  { 
      bool tRRhBlOdYb = false;
      bool cxiXaEldgq = false;
      bool ZeaIAiOCpP = false;
      bool MTWifpKOXm = false;
      bool eoMEwlHcMy = false;
      bool QonBdOpJgR = false;
      bool WLmIOIZzrk = false;
      bool sWFtMkSWLO = false;
      bool bkorzWfUFR = false;
      bool ABhFPTCDpm = false;
      bool LHkbEsitor = false;
      bool wTxSpkVtJq = false;
      bool cEtajroAds = false;
      bool hOfYCTANnF = false;
      bool mkfMUfDOPe = false;
      bool xHsyJGMKqL = false;
      bool EiQwKgmYPV = false;
      bool kIFEDrYhFE = false;
      bool oZjzuZUhOw = false;
      bool GpVcADUjCn = false;
      string BUcFEyGYle;
      string YTfhHSmpiO;
      string AWFjxVsGPL;
      string quoVNSOieS;
      string SechmRRaWX;
      string PITdGePsHi;
      string EAIamceJTn;
      string EEKPuVsWxf;
      string DSirwiaLPi;
      string DVawNSVCtJ;
      string mHGiSKxEik;
      string kruaelQQeD;
      string CStkkicOBb;
      string zqbmswLAYk;
      string kWceyKZzQb;
      string CFXqHTMVyj;
      string hiDGktQHhi;
      string ZQqsRfpPmZ;
      string IcxZYsTkfZ;
      string ipBnCCSVsD;
      if(BUcFEyGYle == mHGiSKxEik){tRRhBlOdYb = true;}
      else if(mHGiSKxEik == BUcFEyGYle){LHkbEsitor = true;}
      if(YTfhHSmpiO == kruaelQQeD){cxiXaEldgq = true;}
      else if(kruaelQQeD == YTfhHSmpiO){wTxSpkVtJq = true;}
      if(AWFjxVsGPL == CStkkicOBb){ZeaIAiOCpP = true;}
      else if(CStkkicOBb == AWFjxVsGPL){cEtajroAds = true;}
      if(quoVNSOieS == zqbmswLAYk){MTWifpKOXm = true;}
      else if(zqbmswLAYk == quoVNSOieS){hOfYCTANnF = true;}
      if(SechmRRaWX == kWceyKZzQb){eoMEwlHcMy = true;}
      else if(kWceyKZzQb == SechmRRaWX){mkfMUfDOPe = true;}
      if(PITdGePsHi == CFXqHTMVyj){QonBdOpJgR = true;}
      else if(CFXqHTMVyj == PITdGePsHi){xHsyJGMKqL = true;}
      if(EAIamceJTn == hiDGktQHhi){WLmIOIZzrk = true;}
      else if(hiDGktQHhi == EAIamceJTn){EiQwKgmYPV = true;}
      if(EEKPuVsWxf == ZQqsRfpPmZ){sWFtMkSWLO = true;}
      if(DSirwiaLPi == IcxZYsTkfZ){bkorzWfUFR = true;}
      if(DVawNSVCtJ == ipBnCCSVsD){ABhFPTCDpm = true;}
      while(ZQqsRfpPmZ == EEKPuVsWxf){kIFEDrYhFE = true;}
      while(IcxZYsTkfZ == IcxZYsTkfZ){oZjzuZUhOw = true;}
      while(ipBnCCSVsD == ipBnCCSVsD){GpVcADUjCn = true;}
      if(tRRhBlOdYb == true){tRRhBlOdYb = false;}
      if(cxiXaEldgq == true){cxiXaEldgq = false;}
      if(ZeaIAiOCpP == true){ZeaIAiOCpP = false;}
      if(MTWifpKOXm == true){MTWifpKOXm = false;}
      if(eoMEwlHcMy == true){eoMEwlHcMy = false;}
      if(QonBdOpJgR == true){QonBdOpJgR = false;}
      if(WLmIOIZzrk == true){WLmIOIZzrk = false;}
      if(sWFtMkSWLO == true){sWFtMkSWLO = false;}
      if(bkorzWfUFR == true){bkorzWfUFR = false;}
      if(ABhFPTCDpm == true){ABhFPTCDpm = false;}
      if(LHkbEsitor == true){LHkbEsitor = false;}
      if(wTxSpkVtJq == true){wTxSpkVtJq = false;}
      if(cEtajroAds == true){cEtajroAds = false;}
      if(hOfYCTANnF == true){hOfYCTANnF = false;}
      if(mkfMUfDOPe == true){mkfMUfDOPe = false;}
      if(xHsyJGMKqL == true){xHsyJGMKqL = false;}
      if(EiQwKgmYPV == true){EiQwKgmYPV = false;}
      if(kIFEDrYhFE == true){kIFEDrYhFE = false;}
      if(oZjzuZUhOw == true){oZjzuZUhOw = false;}
      if(GpVcADUjCn == true){GpVcADUjCn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBHGMVZPJT
{ 
  void mQqCPWnViK()
  { 
      bool IpEwNkJBYy = false;
      bool AukqKeFYAa = false;
      bool csgNDSLDaE = false;
      bool IcPJznSjOL = false;
      bool bcnwmUzWzk = false;
      bool UjNWhPIqst = false;
      bool YGZUpXeaqW = false;
      bool LVJozzFkZi = false;
      bool TnDpiXOsbj = false;
      bool ebqTlUDSGP = false;
      bool pXfcZzaYXi = false;
      bool JWRJakCjkR = false;
      bool IlzHqjeoCd = false;
      bool uleJruIaQi = false;
      bool xpUraHJgsB = false;
      bool STgnGEXXlo = false;
      bool UkWtmWrHRe = false;
      bool bbTBUSQHgi = false;
      bool ZxwALbFqDn = false;
      bool XkoaOMTaFD = false;
      string xiXLAnAZRd;
      string iJzllzWWlo;
      string ZqxfyxMXaE;
      string oAlsCZwCNk;
      string dhQjbUocko;
      string DruRNFkqMC;
      string bcyMnhXFjM;
      string CUIBKraNEd;
      string IimlBwFTfx;
      string nFoKIBiDws;
      string wisXlhjtHU;
      string eXmitroMKq;
      string cEZmXxexrJ;
      string IWRKgZpOzT;
      string MKMKSPSGQP;
      string LWrEQrJFAo;
      string DlBxMHGbBT;
      string CaMqeRqOUI;
      string eXgbxkdMtn;
      string PjOJQaJOyK;
      if(xiXLAnAZRd == wisXlhjtHU){IpEwNkJBYy = true;}
      else if(wisXlhjtHU == xiXLAnAZRd){pXfcZzaYXi = true;}
      if(iJzllzWWlo == eXmitroMKq){AukqKeFYAa = true;}
      else if(eXmitroMKq == iJzllzWWlo){JWRJakCjkR = true;}
      if(ZqxfyxMXaE == cEZmXxexrJ){csgNDSLDaE = true;}
      else if(cEZmXxexrJ == ZqxfyxMXaE){IlzHqjeoCd = true;}
      if(oAlsCZwCNk == IWRKgZpOzT){IcPJznSjOL = true;}
      else if(IWRKgZpOzT == oAlsCZwCNk){uleJruIaQi = true;}
      if(dhQjbUocko == MKMKSPSGQP){bcnwmUzWzk = true;}
      else if(MKMKSPSGQP == dhQjbUocko){xpUraHJgsB = true;}
      if(DruRNFkqMC == LWrEQrJFAo){UjNWhPIqst = true;}
      else if(LWrEQrJFAo == DruRNFkqMC){STgnGEXXlo = true;}
      if(bcyMnhXFjM == DlBxMHGbBT){YGZUpXeaqW = true;}
      else if(DlBxMHGbBT == bcyMnhXFjM){UkWtmWrHRe = true;}
      if(CUIBKraNEd == CaMqeRqOUI){LVJozzFkZi = true;}
      if(IimlBwFTfx == eXgbxkdMtn){TnDpiXOsbj = true;}
      if(nFoKIBiDws == PjOJQaJOyK){ebqTlUDSGP = true;}
      while(CaMqeRqOUI == CUIBKraNEd){bbTBUSQHgi = true;}
      while(eXgbxkdMtn == eXgbxkdMtn){ZxwALbFqDn = true;}
      while(PjOJQaJOyK == PjOJQaJOyK){XkoaOMTaFD = true;}
      if(IpEwNkJBYy == true){IpEwNkJBYy = false;}
      if(AukqKeFYAa == true){AukqKeFYAa = false;}
      if(csgNDSLDaE == true){csgNDSLDaE = false;}
      if(IcPJznSjOL == true){IcPJznSjOL = false;}
      if(bcnwmUzWzk == true){bcnwmUzWzk = false;}
      if(UjNWhPIqst == true){UjNWhPIqst = false;}
      if(YGZUpXeaqW == true){YGZUpXeaqW = false;}
      if(LVJozzFkZi == true){LVJozzFkZi = false;}
      if(TnDpiXOsbj == true){TnDpiXOsbj = false;}
      if(ebqTlUDSGP == true){ebqTlUDSGP = false;}
      if(pXfcZzaYXi == true){pXfcZzaYXi = false;}
      if(JWRJakCjkR == true){JWRJakCjkR = false;}
      if(IlzHqjeoCd == true){IlzHqjeoCd = false;}
      if(uleJruIaQi == true){uleJruIaQi = false;}
      if(xpUraHJgsB == true){xpUraHJgsB = false;}
      if(STgnGEXXlo == true){STgnGEXXlo = false;}
      if(UkWtmWrHRe == true){UkWtmWrHRe = false;}
      if(bbTBUSQHgi == true){bbTBUSQHgi = false;}
      if(ZxwALbFqDn == true){ZxwALbFqDn = false;}
      if(XkoaOMTaFD == true){XkoaOMTaFD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXUNVZMCTN
{ 
  void zllszrQViQ()
  { 
      bool PyMAiLuQfG = false;
      bool YVWDCpuGUE = false;
      bool WNTkffkurl = false;
      bool GETrgCUSrN = false;
      bool zHecRpHfJo = false;
      bool ISzMgBdbUD = false;
      bool azYszUCdWz = false;
      bool UbOGEPiqSo = false;
      bool YEkCdmEHLe = false;
      bool Xryomzikcw = false;
      bool ncJKUfEsHR = false;
      bool SlJedVNVPL = false;
      bool QtSqabdYTE = false;
      bool fxOVButahx = false;
      bool iLAtMkiSKQ = false;
      bool lMVQfsKRir = false;
      bool CeYCkUXndi = false;
      bool amnRcFtXep = false;
      bool sKOCSTbxoH = false;
      bool jcrouDlxJq = false;
      string AByNruKwuq;
      string tKutlYgSuC;
      string oPmbSBbkEW;
      string prHgqHwCyW;
      string KRndepXQPi;
      string YwdrTjNVuq;
      string TZrXBCDOCe;
      string ceTYqWbIxc;
      string dLUUxtNPMH;
      string sZHGCkZPcb;
      string lINkFtbEAw;
      string IEYSNIEWaH;
      string onBukCWMVG;
      string xMfVpUxjOD;
      string RIOPznBost;
      string fCnUmyHSzD;
      string XOhtzuYCbs;
      string KUHXofYkww;
      string BgTbZtXKiq;
      string MdjLeDZUQD;
      if(AByNruKwuq == lINkFtbEAw){PyMAiLuQfG = true;}
      else if(lINkFtbEAw == AByNruKwuq){ncJKUfEsHR = true;}
      if(tKutlYgSuC == IEYSNIEWaH){YVWDCpuGUE = true;}
      else if(IEYSNIEWaH == tKutlYgSuC){SlJedVNVPL = true;}
      if(oPmbSBbkEW == onBukCWMVG){WNTkffkurl = true;}
      else if(onBukCWMVG == oPmbSBbkEW){QtSqabdYTE = true;}
      if(prHgqHwCyW == xMfVpUxjOD){GETrgCUSrN = true;}
      else if(xMfVpUxjOD == prHgqHwCyW){fxOVButahx = true;}
      if(KRndepXQPi == RIOPznBost){zHecRpHfJo = true;}
      else if(RIOPznBost == KRndepXQPi){iLAtMkiSKQ = true;}
      if(YwdrTjNVuq == fCnUmyHSzD){ISzMgBdbUD = true;}
      else if(fCnUmyHSzD == YwdrTjNVuq){lMVQfsKRir = true;}
      if(TZrXBCDOCe == XOhtzuYCbs){azYszUCdWz = true;}
      else if(XOhtzuYCbs == TZrXBCDOCe){CeYCkUXndi = true;}
      if(ceTYqWbIxc == KUHXofYkww){UbOGEPiqSo = true;}
      if(dLUUxtNPMH == BgTbZtXKiq){YEkCdmEHLe = true;}
      if(sZHGCkZPcb == MdjLeDZUQD){Xryomzikcw = true;}
      while(KUHXofYkww == ceTYqWbIxc){amnRcFtXep = true;}
      while(BgTbZtXKiq == BgTbZtXKiq){sKOCSTbxoH = true;}
      while(MdjLeDZUQD == MdjLeDZUQD){jcrouDlxJq = true;}
      if(PyMAiLuQfG == true){PyMAiLuQfG = false;}
      if(YVWDCpuGUE == true){YVWDCpuGUE = false;}
      if(WNTkffkurl == true){WNTkffkurl = false;}
      if(GETrgCUSrN == true){GETrgCUSrN = false;}
      if(zHecRpHfJo == true){zHecRpHfJo = false;}
      if(ISzMgBdbUD == true){ISzMgBdbUD = false;}
      if(azYszUCdWz == true){azYszUCdWz = false;}
      if(UbOGEPiqSo == true){UbOGEPiqSo = false;}
      if(YEkCdmEHLe == true){YEkCdmEHLe = false;}
      if(Xryomzikcw == true){Xryomzikcw = false;}
      if(ncJKUfEsHR == true){ncJKUfEsHR = false;}
      if(SlJedVNVPL == true){SlJedVNVPL = false;}
      if(QtSqabdYTE == true){QtSqabdYTE = false;}
      if(fxOVButahx == true){fxOVButahx = false;}
      if(iLAtMkiSKQ == true){iLAtMkiSKQ = false;}
      if(lMVQfsKRir == true){lMVQfsKRir = false;}
      if(CeYCkUXndi == true){CeYCkUXndi = false;}
      if(amnRcFtXep == true){amnRcFtXep = false;}
      if(sKOCSTbxoH == true){sKOCSTbxoH = false;}
      if(jcrouDlxJq == true){jcrouDlxJq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIVFOSQKYI
{ 
  void bKlAbaerQT()
  { 
      bool QMqcTuYWOj = false;
      bool WYfGNxwLcy = false;
      bool ugWBQUPbuj = false;
      bool qUFfNUDWPV = false;
      bool kqtYScEXhb = false;
      bool pFcsxippMz = false;
      bool fxberCTzrs = false;
      bool sYwGNEmyhm = false;
      bool QrsSslrLhe = false;
      bool eNKPpnOPfQ = false;
      bool JEeoiRJVes = false;
      bool wqHYimDIkF = false;
      bool KHRNNfNfQZ = false;
      bool oXRRdLMEjb = false;
      bool cVgoimFlgC = false;
      bool kGdZFCmRaC = false;
      bool DcFFDXZotW = false;
      bool ayXIcnacea = false;
      bool ZbyNoisqLb = false;
      bool YuchYzQakK = false;
      string oQEIEJhXdY;
      string juYMiUCwMI;
      string YozKPYujoE;
      string uyQJSHTIQi;
      string yzERxDiZxX;
      string QWhMqAQtrf;
      string OxiZckdPta;
      string AtfdJZjhNM;
      string pUlQmYQDRS;
      string pZPjTBQdnM;
      string YSfWXVqEDR;
      string PiffotKRlD;
      string TaxbkaduJI;
      string IGsAnWoPsQ;
      string hLAACGsiuZ;
      string pyrjrxVEkw;
      string ruutIJpfrR;
      string FtYUVIZwYd;
      string huzjRKNIIp;
      string BjewYlQFqs;
      if(oQEIEJhXdY == YSfWXVqEDR){QMqcTuYWOj = true;}
      else if(YSfWXVqEDR == oQEIEJhXdY){JEeoiRJVes = true;}
      if(juYMiUCwMI == PiffotKRlD){WYfGNxwLcy = true;}
      else if(PiffotKRlD == juYMiUCwMI){wqHYimDIkF = true;}
      if(YozKPYujoE == TaxbkaduJI){ugWBQUPbuj = true;}
      else if(TaxbkaduJI == YozKPYujoE){KHRNNfNfQZ = true;}
      if(uyQJSHTIQi == IGsAnWoPsQ){qUFfNUDWPV = true;}
      else if(IGsAnWoPsQ == uyQJSHTIQi){oXRRdLMEjb = true;}
      if(yzERxDiZxX == hLAACGsiuZ){kqtYScEXhb = true;}
      else if(hLAACGsiuZ == yzERxDiZxX){cVgoimFlgC = true;}
      if(QWhMqAQtrf == pyrjrxVEkw){pFcsxippMz = true;}
      else if(pyrjrxVEkw == QWhMqAQtrf){kGdZFCmRaC = true;}
      if(OxiZckdPta == ruutIJpfrR){fxberCTzrs = true;}
      else if(ruutIJpfrR == OxiZckdPta){DcFFDXZotW = true;}
      if(AtfdJZjhNM == FtYUVIZwYd){sYwGNEmyhm = true;}
      if(pUlQmYQDRS == huzjRKNIIp){QrsSslrLhe = true;}
      if(pZPjTBQdnM == BjewYlQFqs){eNKPpnOPfQ = true;}
      while(FtYUVIZwYd == AtfdJZjhNM){ayXIcnacea = true;}
      while(huzjRKNIIp == huzjRKNIIp){ZbyNoisqLb = true;}
      while(BjewYlQFqs == BjewYlQFqs){YuchYzQakK = true;}
      if(QMqcTuYWOj == true){QMqcTuYWOj = false;}
      if(WYfGNxwLcy == true){WYfGNxwLcy = false;}
      if(ugWBQUPbuj == true){ugWBQUPbuj = false;}
      if(qUFfNUDWPV == true){qUFfNUDWPV = false;}
      if(kqtYScEXhb == true){kqtYScEXhb = false;}
      if(pFcsxippMz == true){pFcsxippMz = false;}
      if(fxberCTzrs == true){fxberCTzrs = false;}
      if(sYwGNEmyhm == true){sYwGNEmyhm = false;}
      if(QrsSslrLhe == true){QrsSslrLhe = false;}
      if(eNKPpnOPfQ == true){eNKPpnOPfQ = false;}
      if(JEeoiRJVes == true){JEeoiRJVes = false;}
      if(wqHYimDIkF == true){wqHYimDIkF = false;}
      if(KHRNNfNfQZ == true){KHRNNfNfQZ = false;}
      if(oXRRdLMEjb == true){oXRRdLMEjb = false;}
      if(cVgoimFlgC == true){cVgoimFlgC = false;}
      if(kGdZFCmRaC == true){kGdZFCmRaC = false;}
      if(DcFFDXZotW == true){DcFFDXZotW = false;}
      if(ayXIcnacea == true){ayXIcnacea = false;}
      if(ZbyNoisqLb == true){ZbyNoisqLb = false;}
      if(YuchYzQakK == true){YuchYzQakK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTLPZPBVHY
{ 
  void OuHOZsrloU()
  { 
      bool DxRachpgut = false;
      bool pLMGgcBpaC = false;
      bool zYdlrBTqHO = false;
      bool eKzLeXRbrM = false;
      bool lBVMGzWOYC = false;
      bool bjpDAeSfha = false;
      bool NyZfPfMBbI = false;
      bool LZxOQxCRes = false;
      bool dFSFmtTwKA = false;
      bool FksQynbpwa = false;
      bool lVmPpBlalD = false;
      bool cBBoxIfTrU = false;
      bool LQqbCafgPb = false;
      bool VLUDGIRCOk = false;
      bool IrJHWEjETp = false;
      bool HIybPVdLMP = false;
      bool VFLJhQfxhn = false;
      bool qcFGMSHiEy = false;
      bool pbMZUMNsnk = false;
      bool dFoyPDgzZG = false;
      string bslUcuoXuD;
      string kHBlQrfXcz;
      string TgfAYMUKCX;
      string FRNfSBMucj;
      string FMZMGabogm;
      string gimjAuNkwQ;
      string aeUXxTsUTP;
      string ejustGHSsx;
      string jecPpWedeX;
      string mazLJZrCOm;
      string hHVRHxntpt;
      string ntryfuBFga;
      string nPpwbEjiiT;
      string OEEGPcJLIs;
      string hjnkjsiBeO;
      string YlVmyRQZoC;
      string MFKWeiokiD;
      string kpwnrEbFMi;
      string ViDUubiQHx;
      string LjVFfcZRFA;
      if(bslUcuoXuD == hHVRHxntpt){DxRachpgut = true;}
      else if(hHVRHxntpt == bslUcuoXuD){lVmPpBlalD = true;}
      if(kHBlQrfXcz == ntryfuBFga){pLMGgcBpaC = true;}
      else if(ntryfuBFga == kHBlQrfXcz){cBBoxIfTrU = true;}
      if(TgfAYMUKCX == nPpwbEjiiT){zYdlrBTqHO = true;}
      else if(nPpwbEjiiT == TgfAYMUKCX){LQqbCafgPb = true;}
      if(FRNfSBMucj == OEEGPcJLIs){eKzLeXRbrM = true;}
      else if(OEEGPcJLIs == FRNfSBMucj){VLUDGIRCOk = true;}
      if(FMZMGabogm == hjnkjsiBeO){lBVMGzWOYC = true;}
      else if(hjnkjsiBeO == FMZMGabogm){IrJHWEjETp = true;}
      if(gimjAuNkwQ == YlVmyRQZoC){bjpDAeSfha = true;}
      else if(YlVmyRQZoC == gimjAuNkwQ){HIybPVdLMP = true;}
      if(aeUXxTsUTP == MFKWeiokiD){NyZfPfMBbI = true;}
      else if(MFKWeiokiD == aeUXxTsUTP){VFLJhQfxhn = true;}
      if(ejustGHSsx == kpwnrEbFMi){LZxOQxCRes = true;}
      if(jecPpWedeX == ViDUubiQHx){dFSFmtTwKA = true;}
      if(mazLJZrCOm == LjVFfcZRFA){FksQynbpwa = true;}
      while(kpwnrEbFMi == ejustGHSsx){qcFGMSHiEy = true;}
      while(ViDUubiQHx == ViDUubiQHx){pbMZUMNsnk = true;}
      while(LjVFfcZRFA == LjVFfcZRFA){dFoyPDgzZG = true;}
      if(DxRachpgut == true){DxRachpgut = false;}
      if(pLMGgcBpaC == true){pLMGgcBpaC = false;}
      if(zYdlrBTqHO == true){zYdlrBTqHO = false;}
      if(eKzLeXRbrM == true){eKzLeXRbrM = false;}
      if(lBVMGzWOYC == true){lBVMGzWOYC = false;}
      if(bjpDAeSfha == true){bjpDAeSfha = false;}
      if(NyZfPfMBbI == true){NyZfPfMBbI = false;}
      if(LZxOQxCRes == true){LZxOQxCRes = false;}
      if(dFSFmtTwKA == true){dFSFmtTwKA = false;}
      if(FksQynbpwa == true){FksQynbpwa = false;}
      if(lVmPpBlalD == true){lVmPpBlalD = false;}
      if(cBBoxIfTrU == true){cBBoxIfTrU = false;}
      if(LQqbCafgPb == true){LQqbCafgPb = false;}
      if(VLUDGIRCOk == true){VLUDGIRCOk = false;}
      if(IrJHWEjETp == true){IrJHWEjETp = false;}
      if(HIybPVdLMP == true){HIybPVdLMP = false;}
      if(VFLJhQfxhn == true){VFLJhQfxhn = false;}
      if(qcFGMSHiEy == true){qcFGMSHiEy = false;}
      if(pbMZUMNsnk == true){pbMZUMNsnk = false;}
      if(dFoyPDgzZG == true){dFoyPDgzZG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBVJWUIEPQ
{ 
  void JBVHJVegCh()
  { 
      bool xKKmOHagyb = false;
      bool nxoggFMwGf = false;
      bool xPwnIkYXLq = false;
      bool aNQklUTbIo = false;
      bool ujFTxARQGH = false;
      bool JNlUsgOVec = false;
      bool iDUHAZgEuL = false;
      bool lknQkNKcpH = false;
      bool TIQEhMburE = false;
      bool GxxfGrOySX = false;
      bool TNUuVXZVif = false;
      bool WkfWJZlQYn = false;
      bool ykLpEnnIKs = false;
      bool yLKRnGmViJ = false;
      bool mGMLhUQZVf = false;
      bool FyYdZhBepg = false;
      bool jRKphKaOiC = false;
      bool lQhPArYAIi = false;
      bool XNldnzlfrF = false;
      bool EIeBYVuVdW = false;
      string TjiwwlbbJw;
      string PfYxjSiONd;
      string KkJAJZwHWw;
      string zYAkYdjdmM;
      string kDnURdZXYc;
      string COyYThailV;
      string oTFNwpemYF;
      string iFbBsHwoif;
      string AXhtskabQq;
      string DBqQXQxZXa;
      string ylzStxlxfM;
      string kkzGVQlKUL;
      string ODVhBhNKdb;
      string JWQHgOYOzw;
      string ydwEFRBjuG;
      string elFMMuPRQM;
      string ibTDDOUqZH;
      string rWLYNkGRbj;
      string fdPWxWQEul;
      string yGxmMVKrBq;
      if(TjiwwlbbJw == ylzStxlxfM){xKKmOHagyb = true;}
      else if(ylzStxlxfM == TjiwwlbbJw){TNUuVXZVif = true;}
      if(PfYxjSiONd == kkzGVQlKUL){nxoggFMwGf = true;}
      else if(kkzGVQlKUL == PfYxjSiONd){WkfWJZlQYn = true;}
      if(KkJAJZwHWw == ODVhBhNKdb){xPwnIkYXLq = true;}
      else if(ODVhBhNKdb == KkJAJZwHWw){ykLpEnnIKs = true;}
      if(zYAkYdjdmM == JWQHgOYOzw){aNQklUTbIo = true;}
      else if(JWQHgOYOzw == zYAkYdjdmM){yLKRnGmViJ = true;}
      if(kDnURdZXYc == ydwEFRBjuG){ujFTxARQGH = true;}
      else if(ydwEFRBjuG == kDnURdZXYc){mGMLhUQZVf = true;}
      if(COyYThailV == elFMMuPRQM){JNlUsgOVec = true;}
      else if(elFMMuPRQM == COyYThailV){FyYdZhBepg = true;}
      if(oTFNwpemYF == ibTDDOUqZH){iDUHAZgEuL = true;}
      else if(ibTDDOUqZH == oTFNwpemYF){jRKphKaOiC = true;}
      if(iFbBsHwoif == rWLYNkGRbj){lknQkNKcpH = true;}
      if(AXhtskabQq == fdPWxWQEul){TIQEhMburE = true;}
      if(DBqQXQxZXa == yGxmMVKrBq){GxxfGrOySX = true;}
      while(rWLYNkGRbj == iFbBsHwoif){lQhPArYAIi = true;}
      while(fdPWxWQEul == fdPWxWQEul){XNldnzlfrF = true;}
      while(yGxmMVKrBq == yGxmMVKrBq){EIeBYVuVdW = true;}
      if(xKKmOHagyb == true){xKKmOHagyb = false;}
      if(nxoggFMwGf == true){nxoggFMwGf = false;}
      if(xPwnIkYXLq == true){xPwnIkYXLq = false;}
      if(aNQklUTbIo == true){aNQklUTbIo = false;}
      if(ujFTxARQGH == true){ujFTxARQGH = false;}
      if(JNlUsgOVec == true){JNlUsgOVec = false;}
      if(iDUHAZgEuL == true){iDUHAZgEuL = false;}
      if(lknQkNKcpH == true){lknQkNKcpH = false;}
      if(TIQEhMburE == true){TIQEhMburE = false;}
      if(GxxfGrOySX == true){GxxfGrOySX = false;}
      if(TNUuVXZVif == true){TNUuVXZVif = false;}
      if(WkfWJZlQYn == true){WkfWJZlQYn = false;}
      if(ykLpEnnIKs == true){ykLpEnnIKs = false;}
      if(yLKRnGmViJ == true){yLKRnGmViJ = false;}
      if(mGMLhUQZVf == true){mGMLhUQZVf = false;}
      if(FyYdZhBepg == true){FyYdZhBepg = false;}
      if(jRKphKaOiC == true){jRKphKaOiC = false;}
      if(lQhPArYAIi == true){lQhPArYAIi = false;}
      if(XNldnzlfrF == true){XNldnzlfrF = false;}
      if(EIeBYVuVdW == true){EIeBYVuVdW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVPCZJTUFW
{ 
  void aZjRYzAbLS()
  { 
      bool dewXyhALKH = false;
      bool XdxluDSdAS = false;
      bool McTBrjmkQo = false;
      bool zyIAUfaNXt = false;
      bool wzdVhkGjOl = false;
      bool mWqXOBLteN = false;
      bool uPuUHZVwRO = false;
      bool bFFGVNyyTH = false;
      bool cDWdCbHjlS = false;
      bool UfhKygDINH = false;
      bool PKRzKhRkBB = false;
      bool CMaXkrrRSf = false;
      bool SkKytuWuHo = false;
      bool JpkMrRkWST = false;
      bool JWhjPHFKYG = false;
      bool nlogodASEO = false;
      bool LWcMqMbOfS = false;
      bool HVyzVwDZil = false;
      bool pLVABXBDWN = false;
      bool RRSEHmsVsD = false;
      string XarUVOWeXl;
      string tODBfhNPSh;
      string kBGQxoOUFf;
      string AgleWckEPE;
      string IhhyWCJghr;
      string LUWVMVUaXg;
      string ACYqkMbYdC;
      string xIzNYCTItu;
      string eglMTeKQRB;
      string IJghEGIpMJ;
      string ZkCfuCUIwK;
      string BMgcCSPMXF;
      string CLHctnbRIS;
      string sdujUsdGRQ;
      string JBUHzubEfl;
      string pwSGHOdZkH;
      string aDAcQXQwHI;
      string nIuGuApzcz;
      string LXkWbxKncG;
      string PEVJpGBrqb;
      if(XarUVOWeXl == ZkCfuCUIwK){dewXyhALKH = true;}
      else if(ZkCfuCUIwK == XarUVOWeXl){PKRzKhRkBB = true;}
      if(tODBfhNPSh == BMgcCSPMXF){XdxluDSdAS = true;}
      else if(BMgcCSPMXF == tODBfhNPSh){CMaXkrrRSf = true;}
      if(kBGQxoOUFf == CLHctnbRIS){McTBrjmkQo = true;}
      else if(CLHctnbRIS == kBGQxoOUFf){SkKytuWuHo = true;}
      if(AgleWckEPE == sdujUsdGRQ){zyIAUfaNXt = true;}
      else if(sdujUsdGRQ == AgleWckEPE){JpkMrRkWST = true;}
      if(IhhyWCJghr == JBUHzubEfl){wzdVhkGjOl = true;}
      else if(JBUHzubEfl == IhhyWCJghr){JWhjPHFKYG = true;}
      if(LUWVMVUaXg == pwSGHOdZkH){mWqXOBLteN = true;}
      else if(pwSGHOdZkH == LUWVMVUaXg){nlogodASEO = true;}
      if(ACYqkMbYdC == aDAcQXQwHI){uPuUHZVwRO = true;}
      else if(aDAcQXQwHI == ACYqkMbYdC){LWcMqMbOfS = true;}
      if(xIzNYCTItu == nIuGuApzcz){bFFGVNyyTH = true;}
      if(eglMTeKQRB == LXkWbxKncG){cDWdCbHjlS = true;}
      if(IJghEGIpMJ == PEVJpGBrqb){UfhKygDINH = true;}
      while(nIuGuApzcz == xIzNYCTItu){HVyzVwDZil = true;}
      while(LXkWbxKncG == LXkWbxKncG){pLVABXBDWN = true;}
      while(PEVJpGBrqb == PEVJpGBrqb){RRSEHmsVsD = true;}
      if(dewXyhALKH == true){dewXyhALKH = false;}
      if(XdxluDSdAS == true){XdxluDSdAS = false;}
      if(McTBrjmkQo == true){McTBrjmkQo = false;}
      if(zyIAUfaNXt == true){zyIAUfaNXt = false;}
      if(wzdVhkGjOl == true){wzdVhkGjOl = false;}
      if(mWqXOBLteN == true){mWqXOBLteN = false;}
      if(uPuUHZVwRO == true){uPuUHZVwRO = false;}
      if(bFFGVNyyTH == true){bFFGVNyyTH = false;}
      if(cDWdCbHjlS == true){cDWdCbHjlS = false;}
      if(UfhKygDINH == true){UfhKygDINH = false;}
      if(PKRzKhRkBB == true){PKRzKhRkBB = false;}
      if(CMaXkrrRSf == true){CMaXkrrRSf = false;}
      if(SkKytuWuHo == true){SkKytuWuHo = false;}
      if(JpkMrRkWST == true){JpkMrRkWST = false;}
      if(JWhjPHFKYG == true){JWhjPHFKYG = false;}
      if(nlogodASEO == true){nlogodASEO = false;}
      if(LWcMqMbOfS == true){LWcMqMbOfS = false;}
      if(HVyzVwDZil == true){HVyzVwDZil = false;}
      if(pLVABXBDWN == true){pLVABXBDWN = false;}
      if(RRSEHmsVsD == true){RRSEHmsVsD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AMHOBKLLQK
{ 
  void IoaxZQntiY()
  { 
      bool uULQHxoIdm = false;
      bool zTsWMwQKfj = false;
      bool mEngkydhmj = false;
      bool GKJLVfluuD = false;
      bool poiVcoSHHG = false;
      bool OtZtDpfdeI = false;
      bool THVsfnJgAg = false;
      bool JUOcsyUSEw = false;
      bool fVZfVLjPHe = false;
      bool zHPmiiSoon = false;
      bool fkGZwsewAF = false;
      bool UNYibxgoXU = false;
      bool DsZUgCEasJ = false;
      bool efcQQtPAjb = false;
      bool fnPCKlhgLk = false;
      bool CcRUjlLkrt = false;
      bool nECpZojISg = false;
      bool hgFunPdWKu = false;
      bool TXPIHBNIfe = false;
      bool idHpmbkYbV = false;
      string cOoSizWiKp;
      string ZXjOwDYprV;
      string ZNTyGOyPjN;
      string JruTZgNirl;
      string lagxMuGPgV;
      string DzoVlOuqLU;
      string BHzwghbPoP;
      string opxGjzgWlK;
      string IhiOKJCYgK;
      string lWWXkdbjPd;
      string SpaQfNCilm;
      string hYEBMSYjlW;
      string eDhedSTYUF;
      string WwGHqRHRhw;
      string HTltbMRVLR;
      string FqysyPIumN;
      string tcNgPkRxJt;
      string KHCoOLQnCQ;
      string AyMDAfyNIb;
      string JLdUCeFFdq;
      if(cOoSizWiKp == SpaQfNCilm){uULQHxoIdm = true;}
      else if(SpaQfNCilm == cOoSizWiKp){fkGZwsewAF = true;}
      if(ZXjOwDYprV == hYEBMSYjlW){zTsWMwQKfj = true;}
      else if(hYEBMSYjlW == ZXjOwDYprV){UNYibxgoXU = true;}
      if(ZNTyGOyPjN == eDhedSTYUF){mEngkydhmj = true;}
      else if(eDhedSTYUF == ZNTyGOyPjN){DsZUgCEasJ = true;}
      if(JruTZgNirl == WwGHqRHRhw){GKJLVfluuD = true;}
      else if(WwGHqRHRhw == JruTZgNirl){efcQQtPAjb = true;}
      if(lagxMuGPgV == HTltbMRVLR){poiVcoSHHG = true;}
      else if(HTltbMRVLR == lagxMuGPgV){fnPCKlhgLk = true;}
      if(DzoVlOuqLU == FqysyPIumN){OtZtDpfdeI = true;}
      else if(FqysyPIumN == DzoVlOuqLU){CcRUjlLkrt = true;}
      if(BHzwghbPoP == tcNgPkRxJt){THVsfnJgAg = true;}
      else if(tcNgPkRxJt == BHzwghbPoP){nECpZojISg = true;}
      if(opxGjzgWlK == KHCoOLQnCQ){JUOcsyUSEw = true;}
      if(IhiOKJCYgK == AyMDAfyNIb){fVZfVLjPHe = true;}
      if(lWWXkdbjPd == JLdUCeFFdq){zHPmiiSoon = true;}
      while(KHCoOLQnCQ == opxGjzgWlK){hgFunPdWKu = true;}
      while(AyMDAfyNIb == AyMDAfyNIb){TXPIHBNIfe = true;}
      while(JLdUCeFFdq == JLdUCeFFdq){idHpmbkYbV = true;}
      if(uULQHxoIdm == true){uULQHxoIdm = false;}
      if(zTsWMwQKfj == true){zTsWMwQKfj = false;}
      if(mEngkydhmj == true){mEngkydhmj = false;}
      if(GKJLVfluuD == true){GKJLVfluuD = false;}
      if(poiVcoSHHG == true){poiVcoSHHG = false;}
      if(OtZtDpfdeI == true){OtZtDpfdeI = false;}
      if(THVsfnJgAg == true){THVsfnJgAg = false;}
      if(JUOcsyUSEw == true){JUOcsyUSEw = false;}
      if(fVZfVLjPHe == true){fVZfVLjPHe = false;}
      if(zHPmiiSoon == true){zHPmiiSoon = false;}
      if(fkGZwsewAF == true){fkGZwsewAF = false;}
      if(UNYibxgoXU == true){UNYibxgoXU = false;}
      if(DsZUgCEasJ == true){DsZUgCEasJ = false;}
      if(efcQQtPAjb == true){efcQQtPAjb = false;}
      if(fnPCKlhgLk == true){fnPCKlhgLk = false;}
      if(CcRUjlLkrt == true){CcRUjlLkrt = false;}
      if(nECpZojISg == true){nECpZojISg = false;}
      if(hgFunPdWKu == true){hgFunPdWKu = false;}
      if(TXPIHBNIfe == true){TXPIHBNIfe = false;}
      if(idHpmbkYbV == true){idHpmbkYbV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTSXDEZKYO
{ 
  void bxhuAddDWz()
  { 
      bool HVqeMkYMlX = false;
      bool utrZiiRKiS = false;
      bool qzLHEIGGBp = false;
      bool kPlOCyOKKK = false;
      bool jFNkTSnnTL = false;
      bool iurBwHKiZE = false;
      bool eRLumeIcXj = false;
      bool TGAXillaml = false;
      bool TRloGpXjSt = false;
      bool nfjGfRtRxo = false;
      bool JKQirbuTSK = false;
      bool ViunjMfVnx = false;
      bool HYKcwnWsrQ = false;
      bool qTcycJBCxe = false;
      bool uDQIYEjwVS = false;
      bool lXdzgjzmmE = false;
      bool FBbBSCFwKZ = false;
      bool LcYJCDHCEq = false;
      bool DaXYeSocRr = false;
      bool JOPrYsaOoV = false;
      string eXBVuyTecZ;
      string UqBYPyDzBa;
      string mconKtIznF;
      string UtDfmQzxfJ;
      string urLiUYZizP;
      string OPzNOChNKB;
      string pUqWFZnUly;
      string yFSretQGSl;
      string TYAYqFupRj;
      string hlleSaBndt;
      string jFxAQIwHiU;
      string lbtYgRURfA;
      string eyDBQMTnYD;
      string rbcYBObzHi;
      string InGwyGqNxB;
      string GiIcPlBujE;
      string nHhfbKzUWS;
      string oUKwqqqGDJ;
      string UFpWwISzJO;
      string NgODtBFaUn;
      if(eXBVuyTecZ == jFxAQIwHiU){HVqeMkYMlX = true;}
      else if(jFxAQIwHiU == eXBVuyTecZ){JKQirbuTSK = true;}
      if(UqBYPyDzBa == lbtYgRURfA){utrZiiRKiS = true;}
      else if(lbtYgRURfA == UqBYPyDzBa){ViunjMfVnx = true;}
      if(mconKtIznF == eyDBQMTnYD){qzLHEIGGBp = true;}
      else if(eyDBQMTnYD == mconKtIznF){HYKcwnWsrQ = true;}
      if(UtDfmQzxfJ == rbcYBObzHi){kPlOCyOKKK = true;}
      else if(rbcYBObzHi == UtDfmQzxfJ){qTcycJBCxe = true;}
      if(urLiUYZizP == InGwyGqNxB){jFNkTSnnTL = true;}
      else if(InGwyGqNxB == urLiUYZizP){uDQIYEjwVS = true;}
      if(OPzNOChNKB == GiIcPlBujE){iurBwHKiZE = true;}
      else if(GiIcPlBujE == OPzNOChNKB){lXdzgjzmmE = true;}
      if(pUqWFZnUly == nHhfbKzUWS){eRLumeIcXj = true;}
      else if(nHhfbKzUWS == pUqWFZnUly){FBbBSCFwKZ = true;}
      if(yFSretQGSl == oUKwqqqGDJ){TGAXillaml = true;}
      if(TYAYqFupRj == UFpWwISzJO){TRloGpXjSt = true;}
      if(hlleSaBndt == NgODtBFaUn){nfjGfRtRxo = true;}
      while(oUKwqqqGDJ == yFSretQGSl){LcYJCDHCEq = true;}
      while(UFpWwISzJO == UFpWwISzJO){DaXYeSocRr = true;}
      while(NgODtBFaUn == NgODtBFaUn){JOPrYsaOoV = true;}
      if(HVqeMkYMlX == true){HVqeMkYMlX = false;}
      if(utrZiiRKiS == true){utrZiiRKiS = false;}
      if(qzLHEIGGBp == true){qzLHEIGGBp = false;}
      if(kPlOCyOKKK == true){kPlOCyOKKK = false;}
      if(jFNkTSnnTL == true){jFNkTSnnTL = false;}
      if(iurBwHKiZE == true){iurBwHKiZE = false;}
      if(eRLumeIcXj == true){eRLumeIcXj = false;}
      if(TGAXillaml == true){TGAXillaml = false;}
      if(TRloGpXjSt == true){TRloGpXjSt = false;}
      if(nfjGfRtRxo == true){nfjGfRtRxo = false;}
      if(JKQirbuTSK == true){JKQirbuTSK = false;}
      if(ViunjMfVnx == true){ViunjMfVnx = false;}
      if(HYKcwnWsrQ == true){HYKcwnWsrQ = false;}
      if(qTcycJBCxe == true){qTcycJBCxe = false;}
      if(uDQIYEjwVS == true){uDQIYEjwVS = false;}
      if(lXdzgjzmmE == true){lXdzgjzmmE = false;}
      if(FBbBSCFwKZ == true){FBbBSCFwKZ = false;}
      if(LcYJCDHCEq == true){LcYJCDHCEq = false;}
      if(DaXYeSocRr == true){DaXYeSocRr = false;}
      if(JOPrYsaOoV == true){JOPrYsaOoV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGVNSRRXDH
{ 
  void yZEizLaqSL()
  { 
      bool zJNmxccxhw = false;
      bool DYfexKRxCF = false;
      bool AFfSkQAcfy = false;
      bool eGuLVeCUSy = false;
      bool rAtiCOqkOd = false;
      bool jLEVXtdtCg = false;
      bool bARjQxcTJR = false;
      bool HxeENzLxQV = false;
      bool ZPNBNSBZnb = false;
      bool BHRlVqiJRE = false;
      bool kWbwVlgzHY = false;
      bool igdfGMlPVy = false;
      bool uDfhQAfriW = false;
      bool PBfLjCnQfb = false;
      bool lCSOrTdkeJ = false;
      bool ETnSJhqsfV = false;
      bool GnQkIgBRuD = false;
      bool YVjtLsjQow = false;
      bool WtNYRwMMCC = false;
      bool LtkKVxkgGK = false;
      string crCYYOKXhG;
      string XOMONnITOh;
      string btfNmNcErH;
      string GVfWUkiVez;
      string jjbKAzJRgz;
      string PifwGhMnkK;
      string lGeaAChotb;
      string EmnPyrSUNn;
      string DKWsqWoiQm;
      string YujTMcEBKx;
      string QUXEuctQyO;
      string PqaxHailic;
      string MyYHDJCUCU;
      string mQJPXimRxO;
      string bXkCWgUmMk;
      string tRRhkRuQBl;
      string ZZOdaygKYY;
      string nQnUAnNWjV;
      string oPHQaUybeG;
      string mWQLnCJHaX;
      if(crCYYOKXhG == QUXEuctQyO){zJNmxccxhw = true;}
      else if(QUXEuctQyO == crCYYOKXhG){kWbwVlgzHY = true;}
      if(XOMONnITOh == PqaxHailic){DYfexKRxCF = true;}
      else if(PqaxHailic == XOMONnITOh){igdfGMlPVy = true;}
      if(btfNmNcErH == MyYHDJCUCU){AFfSkQAcfy = true;}
      else if(MyYHDJCUCU == btfNmNcErH){uDfhQAfriW = true;}
      if(GVfWUkiVez == mQJPXimRxO){eGuLVeCUSy = true;}
      else if(mQJPXimRxO == GVfWUkiVez){PBfLjCnQfb = true;}
      if(jjbKAzJRgz == bXkCWgUmMk){rAtiCOqkOd = true;}
      else if(bXkCWgUmMk == jjbKAzJRgz){lCSOrTdkeJ = true;}
      if(PifwGhMnkK == tRRhkRuQBl){jLEVXtdtCg = true;}
      else if(tRRhkRuQBl == PifwGhMnkK){ETnSJhqsfV = true;}
      if(lGeaAChotb == ZZOdaygKYY){bARjQxcTJR = true;}
      else if(ZZOdaygKYY == lGeaAChotb){GnQkIgBRuD = true;}
      if(EmnPyrSUNn == nQnUAnNWjV){HxeENzLxQV = true;}
      if(DKWsqWoiQm == oPHQaUybeG){ZPNBNSBZnb = true;}
      if(YujTMcEBKx == mWQLnCJHaX){BHRlVqiJRE = true;}
      while(nQnUAnNWjV == EmnPyrSUNn){YVjtLsjQow = true;}
      while(oPHQaUybeG == oPHQaUybeG){WtNYRwMMCC = true;}
      while(mWQLnCJHaX == mWQLnCJHaX){LtkKVxkgGK = true;}
      if(zJNmxccxhw == true){zJNmxccxhw = false;}
      if(DYfexKRxCF == true){DYfexKRxCF = false;}
      if(AFfSkQAcfy == true){AFfSkQAcfy = false;}
      if(eGuLVeCUSy == true){eGuLVeCUSy = false;}
      if(rAtiCOqkOd == true){rAtiCOqkOd = false;}
      if(jLEVXtdtCg == true){jLEVXtdtCg = false;}
      if(bARjQxcTJR == true){bARjQxcTJR = false;}
      if(HxeENzLxQV == true){HxeENzLxQV = false;}
      if(ZPNBNSBZnb == true){ZPNBNSBZnb = false;}
      if(BHRlVqiJRE == true){BHRlVqiJRE = false;}
      if(kWbwVlgzHY == true){kWbwVlgzHY = false;}
      if(igdfGMlPVy == true){igdfGMlPVy = false;}
      if(uDfhQAfriW == true){uDfhQAfriW = false;}
      if(PBfLjCnQfb == true){PBfLjCnQfb = false;}
      if(lCSOrTdkeJ == true){lCSOrTdkeJ = false;}
      if(ETnSJhqsfV == true){ETnSJhqsfV = false;}
      if(GnQkIgBRuD == true){GnQkIgBRuD = false;}
      if(YVjtLsjQow == true){YVjtLsjQow = false;}
      if(WtNYRwMMCC == true){WtNYRwMMCC = false;}
      if(LtkKVxkgGK == true){LtkKVxkgGK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMHGYYZVIU
{ 
  void GNmwFZktmc()
  { 
      bool HQPKkmfgqj = false;
      bool PmiPgqXYwr = false;
      bool YEtRpiPQDr = false;
      bool SkbiRIwMql = false;
      bool pLzsbfGqeI = false;
      bool modsCDWyUB = false;
      bool XPdyRdKzyX = false;
      bool uKhJBNEAoK = false;
      bool cYkuFcGhgN = false;
      bool kxroOahAax = false;
      bool UGrHMbHUqo = false;
      bool yVIJYydiso = false;
      bool XbSjmySsua = false;
      bool fDZroVfdhc = false;
      bool VlpqPPohPP = false;
      bool xzHkZrnITO = false;
      bool JNZQJtwQTD = false;
      bool SAAPTklaUX = false;
      bool JjcecgwnRx = false;
      bool gXJTSHMYhU = false;
      string lbLqeWSYZi;
      string CqzFMOdAQc;
      string iSFeGQeklY;
      string azcjKEpnKL;
      string MttNSAfuYu;
      string edtXkTWfjN;
      string rgmBHDOOuI;
      string YpoFQnXqLG;
      string kiMpswFEyp;
      string gJDxSeHsGP;
      string lQzPWoonHw;
      string weTdcITxHL;
      string yJPFaPlrlk;
      string gdkwTTjwTD;
      string HQxBsBoZTJ;
      string KJktRbAtoG;
      string DwBVPRtXJJ;
      string YXcDDgMNLY;
      string ZLXbZWspdr;
      string SoHMALOalb;
      if(lbLqeWSYZi == lQzPWoonHw){HQPKkmfgqj = true;}
      else if(lQzPWoonHw == lbLqeWSYZi){UGrHMbHUqo = true;}
      if(CqzFMOdAQc == weTdcITxHL){PmiPgqXYwr = true;}
      else if(weTdcITxHL == CqzFMOdAQc){yVIJYydiso = true;}
      if(iSFeGQeklY == yJPFaPlrlk){YEtRpiPQDr = true;}
      else if(yJPFaPlrlk == iSFeGQeklY){XbSjmySsua = true;}
      if(azcjKEpnKL == gdkwTTjwTD){SkbiRIwMql = true;}
      else if(gdkwTTjwTD == azcjKEpnKL){fDZroVfdhc = true;}
      if(MttNSAfuYu == HQxBsBoZTJ){pLzsbfGqeI = true;}
      else if(HQxBsBoZTJ == MttNSAfuYu){VlpqPPohPP = true;}
      if(edtXkTWfjN == KJktRbAtoG){modsCDWyUB = true;}
      else if(KJktRbAtoG == edtXkTWfjN){xzHkZrnITO = true;}
      if(rgmBHDOOuI == DwBVPRtXJJ){XPdyRdKzyX = true;}
      else if(DwBVPRtXJJ == rgmBHDOOuI){JNZQJtwQTD = true;}
      if(YpoFQnXqLG == YXcDDgMNLY){uKhJBNEAoK = true;}
      if(kiMpswFEyp == ZLXbZWspdr){cYkuFcGhgN = true;}
      if(gJDxSeHsGP == SoHMALOalb){kxroOahAax = true;}
      while(YXcDDgMNLY == YpoFQnXqLG){SAAPTklaUX = true;}
      while(ZLXbZWspdr == ZLXbZWspdr){JjcecgwnRx = true;}
      while(SoHMALOalb == SoHMALOalb){gXJTSHMYhU = true;}
      if(HQPKkmfgqj == true){HQPKkmfgqj = false;}
      if(PmiPgqXYwr == true){PmiPgqXYwr = false;}
      if(YEtRpiPQDr == true){YEtRpiPQDr = false;}
      if(SkbiRIwMql == true){SkbiRIwMql = false;}
      if(pLzsbfGqeI == true){pLzsbfGqeI = false;}
      if(modsCDWyUB == true){modsCDWyUB = false;}
      if(XPdyRdKzyX == true){XPdyRdKzyX = false;}
      if(uKhJBNEAoK == true){uKhJBNEAoK = false;}
      if(cYkuFcGhgN == true){cYkuFcGhgN = false;}
      if(kxroOahAax == true){kxroOahAax = false;}
      if(UGrHMbHUqo == true){UGrHMbHUqo = false;}
      if(yVIJYydiso == true){yVIJYydiso = false;}
      if(XbSjmySsua == true){XbSjmySsua = false;}
      if(fDZroVfdhc == true){fDZroVfdhc = false;}
      if(VlpqPPohPP == true){VlpqPPohPP = false;}
      if(xzHkZrnITO == true){xzHkZrnITO = false;}
      if(JNZQJtwQTD == true){JNZQJtwQTD = false;}
      if(SAAPTklaUX == true){SAAPTklaUX = false;}
      if(JjcecgwnRx == true){JjcecgwnRx = false;}
      if(gXJTSHMYhU == true){gXJTSHMYhU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWOXHCBVNG
{ 
  void WNObnVRLam()
  { 
      bool zWaPqJsefd = false;
      bool ODlWeuVDdo = false;
      bool kxquZQoiPp = false;
      bool abGJBAykgY = false;
      bool uWdSJOuJLR = false;
      bool TVFpWCefpa = false;
      bool UKPoCmxcUe = false;
      bool wjWFtNSYkK = false;
      bool UeXyWFWPlz = false;
      bool USuFDkHnQW = false;
      bool RSogVizzuJ = false;
      bool iGteGolQSx = false;
      bool PgqUJcoQBJ = false;
      bool GeINsBpqcm = false;
      bool FWTcQOYPzN = false;
      bool yqVSGjbTWr = false;
      bool tiylCEyflE = false;
      bool ztmeqsNOEt = false;
      bool EYQmKPIoHI = false;
      bool ZWUjrWXhZL = false;
      string EXErQOXRdd;
      string QBYbgHtQEl;
      string ccTgtXaLWw;
      string qXUfUnyLAO;
      string RhArYNeXZs;
      string YxfwhaEXys;
      string mLuhmrgsHr;
      string JhQpTucaHf;
      string sClcXsqYxt;
      string jaNHaFlSFf;
      string gkQgjpfpbm;
      string ycPSzkZSKs;
      string BHwMIhUJOO;
      string IKVayHlErg;
      string MAwKuGKuHp;
      string eTILeZoDYC;
      string UWbNdmGnTr;
      string yUZcfAKlRB;
      string WZBXioCJwY;
      string RhfpMoYifI;
      if(EXErQOXRdd == gkQgjpfpbm){zWaPqJsefd = true;}
      else if(gkQgjpfpbm == EXErQOXRdd){RSogVizzuJ = true;}
      if(QBYbgHtQEl == ycPSzkZSKs){ODlWeuVDdo = true;}
      else if(ycPSzkZSKs == QBYbgHtQEl){iGteGolQSx = true;}
      if(ccTgtXaLWw == BHwMIhUJOO){kxquZQoiPp = true;}
      else if(BHwMIhUJOO == ccTgtXaLWw){PgqUJcoQBJ = true;}
      if(qXUfUnyLAO == IKVayHlErg){abGJBAykgY = true;}
      else if(IKVayHlErg == qXUfUnyLAO){GeINsBpqcm = true;}
      if(RhArYNeXZs == MAwKuGKuHp){uWdSJOuJLR = true;}
      else if(MAwKuGKuHp == RhArYNeXZs){FWTcQOYPzN = true;}
      if(YxfwhaEXys == eTILeZoDYC){TVFpWCefpa = true;}
      else if(eTILeZoDYC == YxfwhaEXys){yqVSGjbTWr = true;}
      if(mLuhmrgsHr == UWbNdmGnTr){UKPoCmxcUe = true;}
      else if(UWbNdmGnTr == mLuhmrgsHr){tiylCEyflE = true;}
      if(JhQpTucaHf == yUZcfAKlRB){wjWFtNSYkK = true;}
      if(sClcXsqYxt == WZBXioCJwY){UeXyWFWPlz = true;}
      if(jaNHaFlSFf == RhfpMoYifI){USuFDkHnQW = true;}
      while(yUZcfAKlRB == JhQpTucaHf){ztmeqsNOEt = true;}
      while(WZBXioCJwY == WZBXioCJwY){EYQmKPIoHI = true;}
      while(RhfpMoYifI == RhfpMoYifI){ZWUjrWXhZL = true;}
      if(zWaPqJsefd == true){zWaPqJsefd = false;}
      if(ODlWeuVDdo == true){ODlWeuVDdo = false;}
      if(kxquZQoiPp == true){kxquZQoiPp = false;}
      if(abGJBAykgY == true){abGJBAykgY = false;}
      if(uWdSJOuJLR == true){uWdSJOuJLR = false;}
      if(TVFpWCefpa == true){TVFpWCefpa = false;}
      if(UKPoCmxcUe == true){UKPoCmxcUe = false;}
      if(wjWFtNSYkK == true){wjWFtNSYkK = false;}
      if(UeXyWFWPlz == true){UeXyWFWPlz = false;}
      if(USuFDkHnQW == true){USuFDkHnQW = false;}
      if(RSogVizzuJ == true){RSogVizzuJ = false;}
      if(iGteGolQSx == true){iGteGolQSx = false;}
      if(PgqUJcoQBJ == true){PgqUJcoQBJ = false;}
      if(GeINsBpqcm == true){GeINsBpqcm = false;}
      if(FWTcQOYPzN == true){FWTcQOYPzN = false;}
      if(yqVSGjbTWr == true){yqVSGjbTWr = false;}
      if(tiylCEyflE == true){tiylCEyflE = false;}
      if(ztmeqsNOEt == true){ztmeqsNOEt = false;}
      if(EYQmKPIoHI == true){EYQmKPIoHI = false;}
      if(ZWUjrWXhZL == true){ZWUjrWXhZL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYZJOKWYIS
{ 
  void zpiUqAmyBz()
  { 
      bool lxVDYLnfTF = false;
      bool XfJMPmsDTl = false;
      bool gMmAuAkeXi = false;
      bool ljPNKLrmGM = false;
      bool cGODrRQEFa = false;
      bool EWBGnYKVIY = false;
      bool aJHkTmPuBE = false;
      bool tFxGJZyiHd = false;
      bool igYwePiJZl = false;
      bool BVehlTydjE = false;
      bool BUCBgzYtxN = false;
      bool aaOdosjKFE = false;
      bool EGUPDXZPTo = false;
      bool aTzCcOdWPe = false;
      bool pnLMKZHAsr = false;
      bool inXeAtzmyI = false;
      bool YJZHlGaLBZ = false;
      bool PNtaNPuIEc = false;
      bool QYWbGmwTCi = false;
      bool OpYHFgOEZE = false;
      string SRjBxLfplM;
      string FRQwldqCzG;
      string sSkwBkhrWQ;
      string rMDFMtGumY;
      string dDqjgLFyez;
      string ymoIzAgmzL;
      string dnSUUsOKir;
      string WwOZbpaAOp;
      string fiMXRFXtFM;
      string NSubuojVPm;
      string wtPmcCXOfJ;
      string YfYJetbuCO;
      string VTFWdDAmem;
      string FFjbslTZuP;
      string hJOwnhtlwA;
      string NnSBRcorIY;
      string BjisDSuwPr;
      string aBAmgLFIiw;
      string IOqeYQliJP;
      string xaQVOxZUsU;
      if(SRjBxLfplM == wtPmcCXOfJ){lxVDYLnfTF = true;}
      else if(wtPmcCXOfJ == SRjBxLfplM){BUCBgzYtxN = true;}
      if(FRQwldqCzG == YfYJetbuCO){XfJMPmsDTl = true;}
      else if(YfYJetbuCO == FRQwldqCzG){aaOdosjKFE = true;}
      if(sSkwBkhrWQ == VTFWdDAmem){gMmAuAkeXi = true;}
      else if(VTFWdDAmem == sSkwBkhrWQ){EGUPDXZPTo = true;}
      if(rMDFMtGumY == FFjbslTZuP){ljPNKLrmGM = true;}
      else if(FFjbslTZuP == rMDFMtGumY){aTzCcOdWPe = true;}
      if(dDqjgLFyez == hJOwnhtlwA){cGODrRQEFa = true;}
      else if(hJOwnhtlwA == dDqjgLFyez){pnLMKZHAsr = true;}
      if(ymoIzAgmzL == NnSBRcorIY){EWBGnYKVIY = true;}
      else if(NnSBRcorIY == ymoIzAgmzL){inXeAtzmyI = true;}
      if(dnSUUsOKir == BjisDSuwPr){aJHkTmPuBE = true;}
      else if(BjisDSuwPr == dnSUUsOKir){YJZHlGaLBZ = true;}
      if(WwOZbpaAOp == aBAmgLFIiw){tFxGJZyiHd = true;}
      if(fiMXRFXtFM == IOqeYQliJP){igYwePiJZl = true;}
      if(NSubuojVPm == xaQVOxZUsU){BVehlTydjE = true;}
      while(aBAmgLFIiw == WwOZbpaAOp){PNtaNPuIEc = true;}
      while(IOqeYQliJP == IOqeYQliJP){QYWbGmwTCi = true;}
      while(xaQVOxZUsU == xaQVOxZUsU){OpYHFgOEZE = true;}
      if(lxVDYLnfTF == true){lxVDYLnfTF = false;}
      if(XfJMPmsDTl == true){XfJMPmsDTl = false;}
      if(gMmAuAkeXi == true){gMmAuAkeXi = false;}
      if(ljPNKLrmGM == true){ljPNKLrmGM = false;}
      if(cGODrRQEFa == true){cGODrRQEFa = false;}
      if(EWBGnYKVIY == true){EWBGnYKVIY = false;}
      if(aJHkTmPuBE == true){aJHkTmPuBE = false;}
      if(tFxGJZyiHd == true){tFxGJZyiHd = false;}
      if(igYwePiJZl == true){igYwePiJZl = false;}
      if(BVehlTydjE == true){BVehlTydjE = false;}
      if(BUCBgzYtxN == true){BUCBgzYtxN = false;}
      if(aaOdosjKFE == true){aaOdosjKFE = false;}
      if(EGUPDXZPTo == true){EGUPDXZPTo = false;}
      if(aTzCcOdWPe == true){aTzCcOdWPe = false;}
      if(pnLMKZHAsr == true){pnLMKZHAsr = false;}
      if(inXeAtzmyI == true){inXeAtzmyI = false;}
      if(YJZHlGaLBZ == true){YJZHlGaLBZ = false;}
      if(PNtaNPuIEc == true){PNtaNPuIEc = false;}
      if(QYWbGmwTCi == true){QYWbGmwTCi = false;}
      if(OpYHFgOEZE == true){OpYHFgOEZE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQSCDGYRDW
{ 
  void letexRRTFR()
  { 
      bool pMQbFEwQsl = false;
      bool bMHQTWJmGJ = false;
      bool rxDtYLEfEs = false;
      bool iZqGnYSRwq = false;
      bool FVRzOpyGUO = false;
      bool bSnGasIWDt = false;
      bool zQLzDCUBct = false;
      bool ErqOEWeEeh = false;
      bool MxKoQPlket = false;
      bool QuNBqoJRuM = false;
      bool UxdZKibYBE = false;
      bool ODqUgBFVhn = false;
      bool QiVhdIeoWP = false;
      bool MMJSNPTjeh = false;
      bool nMjafMErUo = false;
      bool iniHukawwB = false;
      bool ElBlqBtXHQ = false;
      bool hVpAzDzuBR = false;
      bool ElThfYcBWb = false;
      bool nXndcBLxid = false;
      string MNOkAJZmRD;
      string hHghlcTbuV;
      string rAnkJZEleu;
      string pkNojQiEcm;
      string QpOIKHxGto;
      string IzYkhLYdba;
      string FnHWMxsryU;
      string tPyIFClfaB;
      string bxrplpLcHY;
      string rFcBgciruM;
      string NFIYtsAQfe;
      string YsDZyIuQjV;
      string kQjZcnlwac;
      string TtjNnWoSus;
      string puxbzyCCDY;
      string gRHYbwUhuG;
      string GDoCLeIola;
      string SbUqfoTHae;
      string lisBwBlLkq;
      string CGXollGtPT;
      if(MNOkAJZmRD == NFIYtsAQfe){pMQbFEwQsl = true;}
      else if(NFIYtsAQfe == MNOkAJZmRD){UxdZKibYBE = true;}
      if(hHghlcTbuV == YsDZyIuQjV){bMHQTWJmGJ = true;}
      else if(YsDZyIuQjV == hHghlcTbuV){ODqUgBFVhn = true;}
      if(rAnkJZEleu == kQjZcnlwac){rxDtYLEfEs = true;}
      else if(kQjZcnlwac == rAnkJZEleu){QiVhdIeoWP = true;}
      if(pkNojQiEcm == TtjNnWoSus){iZqGnYSRwq = true;}
      else if(TtjNnWoSus == pkNojQiEcm){MMJSNPTjeh = true;}
      if(QpOIKHxGto == puxbzyCCDY){FVRzOpyGUO = true;}
      else if(puxbzyCCDY == QpOIKHxGto){nMjafMErUo = true;}
      if(IzYkhLYdba == gRHYbwUhuG){bSnGasIWDt = true;}
      else if(gRHYbwUhuG == IzYkhLYdba){iniHukawwB = true;}
      if(FnHWMxsryU == GDoCLeIola){zQLzDCUBct = true;}
      else if(GDoCLeIola == FnHWMxsryU){ElBlqBtXHQ = true;}
      if(tPyIFClfaB == SbUqfoTHae){ErqOEWeEeh = true;}
      if(bxrplpLcHY == lisBwBlLkq){MxKoQPlket = true;}
      if(rFcBgciruM == CGXollGtPT){QuNBqoJRuM = true;}
      while(SbUqfoTHae == tPyIFClfaB){hVpAzDzuBR = true;}
      while(lisBwBlLkq == lisBwBlLkq){ElThfYcBWb = true;}
      while(CGXollGtPT == CGXollGtPT){nXndcBLxid = true;}
      if(pMQbFEwQsl == true){pMQbFEwQsl = false;}
      if(bMHQTWJmGJ == true){bMHQTWJmGJ = false;}
      if(rxDtYLEfEs == true){rxDtYLEfEs = false;}
      if(iZqGnYSRwq == true){iZqGnYSRwq = false;}
      if(FVRzOpyGUO == true){FVRzOpyGUO = false;}
      if(bSnGasIWDt == true){bSnGasIWDt = false;}
      if(zQLzDCUBct == true){zQLzDCUBct = false;}
      if(ErqOEWeEeh == true){ErqOEWeEeh = false;}
      if(MxKoQPlket == true){MxKoQPlket = false;}
      if(QuNBqoJRuM == true){QuNBqoJRuM = false;}
      if(UxdZKibYBE == true){UxdZKibYBE = false;}
      if(ODqUgBFVhn == true){ODqUgBFVhn = false;}
      if(QiVhdIeoWP == true){QiVhdIeoWP = false;}
      if(MMJSNPTjeh == true){MMJSNPTjeh = false;}
      if(nMjafMErUo == true){nMjafMErUo = false;}
      if(iniHukawwB == true){iniHukawwB = false;}
      if(ElBlqBtXHQ == true){ElBlqBtXHQ = false;}
      if(hVpAzDzuBR == true){hVpAzDzuBR = false;}
      if(ElThfYcBWb == true){ElThfYcBWb = false;}
      if(nXndcBLxid == true){nXndcBLxid = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQMOADHSWR
{ 
  void xcTqeMtfzF()
  { 
      bool cJdRHiBJrI = false;
      bool mCFJeBURoa = false;
      bool oBzBmbVOri = false;
      bool HMZxDTPtsf = false;
      bool aAAttsocCA = false;
      bool dYTJsaJcef = false;
      bool MmQJAacHFL = false;
      bool laYIznAEGt = false;
      bool lrLrFirPEc = false;
      bool JlPMTniqtT = false;
      bool QhWqODAKKE = false;
      bool ZEWjtTaYDR = false;
      bool hMCcCzKLoL = false;
      bool EJKmdDVUdB = false;
      bool igFADEPeSz = false;
      bool NKmbkDetnO = false;
      bool rnVyzQsiGp = false;
      bool yFuBiBGCZx = false;
      bool jesoytViBZ = false;
      bool XafOJtLHAl = false;
      string SPHsSJUoiX;
      string kfgVEnoUVa;
      string kupOjCeKJs;
      string gSWOQMUuLK;
      string oUlgkBeClS;
      string tEJxwWYrIQ;
      string dKfpqSIRFr;
      string SsILlQJJdi;
      string WbXqybIYSs;
      string mblufdnuoR;
      string rMwtzBuyLe;
      string MPOZsCloqO;
      string JiyLEpGNeH;
      string bNTLpKecqx;
      string gKNngXMMBd;
      string rzEaHINjpI;
      string uhSEDyuDii;
      string WJxthzVKef;
      string csMAOcJsDh;
      string wumhCzqJjh;
      if(SPHsSJUoiX == rMwtzBuyLe){cJdRHiBJrI = true;}
      else if(rMwtzBuyLe == SPHsSJUoiX){QhWqODAKKE = true;}
      if(kfgVEnoUVa == MPOZsCloqO){mCFJeBURoa = true;}
      else if(MPOZsCloqO == kfgVEnoUVa){ZEWjtTaYDR = true;}
      if(kupOjCeKJs == JiyLEpGNeH){oBzBmbVOri = true;}
      else if(JiyLEpGNeH == kupOjCeKJs){hMCcCzKLoL = true;}
      if(gSWOQMUuLK == bNTLpKecqx){HMZxDTPtsf = true;}
      else if(bNTLpKecqx == gSWOQMUuLK){EJKmdDVUdB = true;}
      if(oUlgkBeClS == gKNngXMMBd){aAAttsocCA = true;}
      else if(gKNngXMMBd == oUlgkBeClS){igFADEPeSz = true;}
      if(tEJxwWYrIQ == rzEaHINjpI){dYTJsaJcef = true;}
      else if(rzEaHINjpI == tEJxwWYrIQ){NKmbkDetnO = true;}
      if(dKfpqSIRFr == uhSEDyuDii){MmQJAacHFL = true;}
      else if(uhSEDyuDii == dKfpqSIRFr){rnVyzQsiGp = true;}
      if(SsILlQJJdi == WJxthzVKef){laYIznAEGt = true;}
      if(WbXqybIYSs == csMAOcJsDh){lrLrFirPEc = true;}
      if(mblufdnuoR == wumhCzqJjh){JlPMTniqtT = true;}
      while(WJxthzVKef == SsILlQJJdi){yFuBiBGCZx = true;}
      while(csMAOcJsDh == csMAOcJsDh){jesoytViBZ = true;}
      while(wumhCzqJjh == wumhCzqJjh){XafOJtLHAl = true;}
      if(cJdRHiBJrI == true){cJdRHiBJrI = false;}
      if(mCFJeBURoa == true){mCFJeBURoa = false;}
      if(oBzBmbVOri == true){oBzBmbVOri = false;}
      if(HMZxDTPtsf == true){HMZxDTPtsf = false;}
      if(aAAttsocCA == true){aAAttsocCA = false;}
      if(dYTJsaJcef == true){dYTJsaJcef = false;}
      if(MmQJAacHFL == true){MmQJAacHFL = false;}
      if(laYIznAEGt == true){laYIznAEGt = false;}
      if(lrLrFirPEc == true){lrLrFirPEc = false;}
      if(JlPMTniqtT == true){JlPMTniqtT = false;}
      if(QhWqODAKKE == true){QhWqODAKKE = false;}
      if(ZEWjtTaYDR == true){ZEWjtTaYDR = false;}
      if(hMCcCzKLoL == true){hMCcCzKLoL = false;}
      if(EJKmdDVUdB == true){EJKmdDVUdB = false;}
      if(igFADEPeSz == true){igFADEPeSz = false;}
      if(NKmbkDetnO == true){NKmbkDetnO = false;}
      if(rnVyzQsiGp == true){rnVyzQsiGp = false;}
      if(yFuBiBGCZx == true){yFuBiBGCZx = false;}
      if(jesoytViBZ == true){jesoytViBZ = false;}
      if(XafOJtLHAl == true){XafOJtLHAl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZAFPTPQZOE
{ 
  void eXpQEQIXzM()
  { 
      bool GyMdehsroA = false;
      bool BRRjOVRsBX = false;
      bool JntkcVmQWb = false;
      bool yNaicWjNkr = false;
      bool IkmMarTxKy = false;
      bool JHNVfSDaBI = false;
      bool ubUMCmphGr = false;
      bool kDIJPXAhKj = false;
      bool CpGYSpAFDK = false;
      bool SJMbxfQaKm = false;
      bool BkpRNFzEFH = false;
      bool RVPRGFUwtL = false;
      bool mkewYaqfMi = false;
      bool HYWXhQznKM = false;
      bool quzurxttUr = false;
      bool LTgyAQGtsl = false;
      bool NSrWAsyrip = false;
      bool FfkgUqkiDb = false;
      bool gwKTWmrYWR = false;
      bool JFuYyXDctz = false;
      string kMxzVtIIud;
      string qRYpHTnVER;
      string eEZHXNpNkl;
      string kLAJLsQVKb;
      string RIZZmQpWmO;
      string IfoEfgloaI;
      string EtWJseQPeN;
      string CRLbzVeAUG;
      string XTZVdEWwcd;
      string HatCXWkPfH;
      string AZqZLpTMEK;
      string CkUUjjUBen;
      string IUmAGbWJDc;
      string kOUMGxbAJm;
      string kJqSbWGZRm;
      string CjjrzempTj;
      string SJJbYmQHNm;
      string ITqrDydUXi;
      string UxrPZBdcNb;
      string KlgZUaAPso;
      if(kMxzVtIIud == AZqZLpTMEK){GyMdehsroA = true;}
      else if(AZqZLpTMEK == kMxzVtIIud){BkpRNFzEFH = true;}
      if(qRYpHTnVER == CkUUjjUBen){BRRjOVRsBX = true;}
      else if(CkUUjjUBen == qRYpHTnVER){RVPRGFUwtL = true;}
      if(eEZHXNpNkl == IUmAGbWJDc){JntkcVmQWb = true;}
      else if(IUmAGbWJDc == eEZHXNpNkl){mkewYaqfMi = true;}
      if(kLAJLsQVKb == kOUMGxbAJm){yNaicWjNkr = true;}
      else if(kOUMGxbAJm == kLAJLsQVKb){HYWXhQznKM = true;}
      if(RIZZmQpWmO == kJqSbWGZRm){IkmMarTxKy = true;}
      else if(kJqSbWGZRm == RIZZmQpWmO){quzurxttUr = true;}
      if(IfoEfgloaI == CjjrzempTj){JHNVfSDaBI = true;}
      else if(CjjrzempTj == IfoEfgloaI){LTgyAQGtsl = true;}
      if(EtWJseQPeN == SJJbYmQHNm){ubUMCmphGr = true;}
      else if(SJJbYmQHNm == EtWJseQPeN){NSrWAsyrip = true;}
      if(CRLbzVeAUG == ITqrDydUXi){kDIJPXAhKj = true;}
      if(XTZVdEWwcd == UxrPZBdcNb){CpGYSpAFDK = true;}
      if(HatCXWkPfH == KlgZUaAPso){SJMbxfQaKm = true;}
      while(ITqrDydUXi == CRLbzVeAUG){FfkgUqkiDb = true;}
      while(UxrPZBdcNb == UxrPZBdcNb){gwKTWmrYWR = true;}
      while(KlgZUaAPso == KlgZUaAPso){JFuYyXDctz = true;}
      if(GyMdehsroA == true){GyMdehsroA = false;}
      if(BRRjOVRsBX == true){BRRjOVRsBX = false;}
      if(JntkcVmQWb == true){JntkcVmQWb = false;}
      if(yNaicWjNkr == true){yNaicWjNkr = false;}
      if(IkmMarTxKy == true){IkmMarTxKy = false;}
      if(JHNVfSDaBI == true){JHNVfSDaBI = false;}
      if(ubUMCmphGr == true){ubUMCmphGr = false;}
      if(kDIJPXAhKj == true){kDIJPXAhKj = false;}
      if(CpGYSpAFDK == true){CpGYSpAFDK = false;}
      if(SJMbxfQaKm == true){SJMbxfQaKm = false;}
      if(BkpRNFzEFH == true){BkpRNFzEFH = false;}
      if(RVPRGFUwtL == true){RVPRGFUwtL = false;}
      if(mkewYaqfMi == true){mkewYaqfMi = false;}
      if(HYWXhQznKM == true){HYWXhQznKM = false;}
      if(quzurxttUr == true){quzurxttUr = false;}
      if(LTgyAQGtsl == true){LTgyAQGtsl = false;}
      if(NSrWAsyrip == true){NSrWAsyrip = false;}
      if(FfkgUqkiDb == true){FfkgUqkiDb = false;}
      if(gwKTWmrYWR == true){gwKTWmrYWR = false;}
      if(JFuYyXDctz == true){JFuYyXDctz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MTFNDKLPED
{ 
  void AJXjlgkgTz()
  { 
      bool kgfzdhDNXT = false;
      bool MwYWEypPly = false;
      bool ORYlhsbpYj = false;
      bool LHOXgdRjGF = false;
      bool oPKPqNaNuG = false;
      bool tSSduTHsRk = false;
      bool GMomIFhBoZ = false;
      bool fGIfIzHIuT = false;
      bool ROuRprnkcN = false;
      bool VYSUzcZXHl = false;
      bool eZXUZnJmUw = false;
      bool LzxxTqQWxP = false;
      bool QxXaDHnmff = false;
      bool YjBJorparB = false;
      bool hBPgBWaUBH = false;
      bool LCZqUhBxQS = false;
      bool AVGnWbxnIa = false;
      bool BpeugOhqYg = false;
      bool gSkYUWJKnG = false;
      bool qsJZBLuaKZ = false;
      string KJGKrmuYne;
      string NCTQQpPjGJ;
      string RGdIuEnlps;
      string gnTLRwtEXX;
      string qgQZRAGoQL;
      string aQscODfxOn;
      string zIiuyYhIyU;
      string wKMhSkpDqu;
      string xyVdRQupxO;
      string PwpiYhyUbr;
      string RyquPQDKKd;
      string McGTqAmEdh;
      string drKiFAUcJj;
      string lUbycyHZOA;
      string MjfTBloWrX;
      string usqsOYnHpO;
      string waBaqrAIpr;
      string sMpcVtMqhS;
      string KyjknsdhjD;
      string KAjzEkiEbJ;
      if(KJGKrmuYne == RyquPQDKKd){kgfzdhDNXT = true;}
      else if(RyquPQDKKd == KJGKrmuYne){eZXUZnJmUw = true;}
      if(NCTQQpPjGJ == McGTqAmEdh){MwYWEypPly = true;}
      else if(McGTqAmEdh == NCTQQpPjGJ){LzxxTqQWxP = true;}
      if(RGdIuEnlps == drKiFAUcJj){ORYlhsbpYj = true;}
      else if(drKiFAUcJj == RGdIuEnlps){QxXaDHnmff = true;}
      if(gnTLRwtEXX == lUbycyHZOA){LHOXgdRjGF = true;}
      else if(lUbycyHZOA == gnTLRwtEXX){YjBJorparB = true;}
      if(qgQZRAGoQL == MjfTBloWrX){oPKPqNaNuG = true;}
      else if(MjfTBloWrX == qgQZRAGoQL){hBPgBWaUBH = true;}
      if(aQscODfxOn == usqsOYnHpO){tSSduTHsRk = true;}
      else if(usqsOYnHpO == aQscODfxOn){LCZqUhBxQS = true;}
      if(zIiuyYhIyU == waBaqrAIpr){GMomIFhBoZ = true;}
      else if(waBaqrAIpr == zIiuyYhIyU){AVGnWbxnIa = true;}
      if(wKMhSkpDqu == sMpcVtMqhS){fGIfIzHIuT = true;}
      if(xyVdRQupxO == KyjknsdhjD){ROuRprnkcN = true;}
      if(PwpiYhyUbr == KAjzEkiEbJ){VYSUzcZXHl = true;}
      while(sMpcVtMqhS == wKMhSkpDqu){BpeugOhqYg = true;}
      while(KyjknsdhjD == KyjknsdhjD){gSkYUWJKnG = true;}
      while(KAjzEkiEbJ == KAjzEkiEbJ){qsJZBLuaKZ = true;}
      if(kgfzdhDNXT == true){kgfzdhDNXT = false;}
      if(MwYWEypPly == true){MwYWEypPly = false;}
      if(ORYlhsbpYj == true){ORYlhsbpYj = false;}
      if(LHOXgdRjGF == true){LHOXgdRjGF = false;}
      if(oPKPqNaNuG == true){oPKPqNaNuG = false;}
      if(tSSduTHsRk == true){tSSduTHsRk = false;}
      if(GMomIFhBoZ == true){GMomIFhBoZ = false;}
      if(fGIfIzHIuT == true){fGIfIzHIuT = false;}
      if(ROuRprnkcN == true){ROuRprnkcN = false;}
      if(VYSUzcZXHl == true){VYSUzcZXHl = false;}
      if(eZXUZnJmUw == true){eZXUZnJmUw = false;}
      if(LzxxTqQWxP == true){LzxxTqQWxP = false;}
      if(QxXaDHnmff == true){QxXaDHnmff = false;}
      if(YjBJorparB == true){YjBJorparB = false;}
      if(hBPgBWaUBH == true){hBPgBWaUBH = false;}
      if(LCZqUhBxQS == true){LCZqUhBxQS = false;}
      if(AVGnWbxnIa == true){AVGnWbxnIa = false;}
      if(BpeugOhqYg == true){BpeugOhqYg = false;}
      if(gSkYUWJKnG == true){gSkYUWJKnG = false;}
      if(qsJZBLuaKZ == true){qsJZBLuaKZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KHCSWHWTBS
{ 
  void qCRrsfAiic()
  { 
      bool VRYHUVheie = false;
      bool BmexOUybyf = false;
      bool rUqcOpFzZz = false;
      bool yhPyteaqmU = false;
      bool sRAWUspZpU = false;
      bool ccmpQAaure = false;
      bool PhEjfTXfDj = false;
      bool tHocmaUTIV = false;
      bool zeJFVVtYgt = false;
      bool DfyHFKMPpA = false;
      bool UJWGaVmKDp = false;
      bool fGlWfjYzOK = false;
      bool ZzzJfNIgXc = false;
      bool NEdIAoICdz = false;
      bool hjUqNxsabU = false;
      bool kNBeaVKMaN = false;
      bool NGlacbbdWp = false;
      bool bWVObpdIuh = false;
      bool TgFDqzCyge = false;
      bool dubPlbxtNl = false;
      string YBoJEAVATI;
      string njNRBbtPLc;
      string kZsyOEfOwk;
      string hfmweifIGV;
      string WMHlkKHeWN;
      string eIPjuzHqtz;
      string UHDiaIwQlS;
      string ulIpFXRGNE;
      string xAqhFZPDAf;
      string anNGAPIYLb;
      string NprERszZdW;
      string gAdpCTQVcA;
      string ssPFqHXCop;
      string OrukpGIlPL;
      string ZoZdyaKXDg;
      string zmwKiUZlNK;
      string VxjnHoFszw;
      string LdFQaDSlHP;
      string wAyIpawjBV;
      string gVXFpbEkWJ;
      if(YBoJEAVATI == NprERszZdW){VRYHUVheie = true;}
      else if(NprERszZdW == YBoJEAVATI){UJWGaVmKDp = true;}
      if(njNRBbtPLc == gAdpCTQVcA){BmexOUybyf = true;}
      else if(gAdpCTQVcA == njNRBbtPLc){fGlWfjYzOK = true;}
      if(kZsyOEfOwk == ssPFqHXCop){rUqcOpFzZz = true;}
      else if(ssPFqHXCop == kZsyOEfOwk){ZzzJfNIgXc = true;}
      if(hfmweifIGV == OrukpGIlPL){yhPyteaqmU = true;}
      else if(OrukpGIlPL == hfmweifIGV){NEdIAoICdz = true;}
      if(WMHlkKHeWN == ZoZdyaKXDg){sRAWUspZpU = true;}
      else if(ZoZdyaKXDg == WMHlkKHeWN){hjUqNxsabU = true;}
      if(eIPjuzHqtz == zmwKiUZlNK){ccmpQAaure = true;}
      else if(zmwKiUZlNK == eIPjuzHqtz){kNBeaVKMaN = true;}
      if(UHDiaIwQlS == VxjnHoFszw){PhEjfTXfDj = true;}
      else if(VxjnHoFszw == UHDiaIwQlS){NGlacbbdWp = true;}
      if(ulIpFXRGNE == LdFQaDSlHP){tHocmaUTIV = true;}
      if(xAqhFZPDAf == wAyIpawjBV){zeJFVVtYgt = true;}
      if(anNGAPIYLb == gVXFpbEkWJ){DfyHFKMPpA = true;}
      while(LdFQaDSlHP == ulIpFXRGNE){bWVObpdIuh = true;}
      while(wAyIpawjBV == wAyIpawjBV){TgFDqzCyge = true;}
      while(gVXFpbEkWJ == gVXFpbEkWJ){dubPlbxtNl = true;}
      if(VRYHUVheie == true){VRYHUVheie = false;}
      if(BmexOUybyf == true){BmexOUybyf = false;}
      if(rUqcOpFzZz == true){rUqcOpFzZz = false;}
      if(yhPyteaqmU == true){yhPyteaqmU = false;}
      if(sRAWUspZpU == true){sRAWUspZpU = false;}
      if(ccmpQAaure == true){ccmpQAaure = false;}
      if(PhEjfTXfDj == true){PhEjfTXfDj = false;}
      if(tHocmaUTIV == true){tHocmaUTIV = false;}
      if(zeJFVVtYgt == true){zeJFVVtYgt = false;}
      if(DfyHFKMPpA == true){DfyHFKMPpA = false;}
      if(UJWGaVmKDp == true){UJWGaVmKDp = false;}
      if(fGlWfjYzOK == true){fGlWfjYzOK = false;}
      if(ZzzJfNIgXc == true){ZzzJfNIgXc = false;}
      if(NEdIAoICdz == true){NEdIAoICdz = false;}
      if(hjUqNxsabU == true){hjUqNxsabU = false;}
      if(kNBeaVKMaN == true){kNBeaVKMaN = false;}
      if(NGlacbbdWp == true){NGlacbbdWp = false;}
      if(bWVObpdIuh == true){bWVObpdIuh = false;}
      if(TgFDqzCyge == true){TgFDqzCyge = false;}
      if(dubPlbxtNl == true){dubPlbxtNl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJLOMELSDA
{ 
  void AzuEKxKjdj()
  { 
      bool AYSCVdMExy = false;
      bool rWpSqQIrPx = false;
      bool HIDCHGqzmA = false;
      bool HcXWtBqytK = false;
      bool TtkAADCeDP = false;
      bool FXLNgqVPtO = false;
      bool mMQwpOzSYp = false;
      bool YJxFdMWDCE = false;
      bool DLwWujRJpC = false;
      bool ebDfWGcoJk = false;
      bool EjGMqwZFjT = false;
      bool URMpKbQsBG = false;
      bool xocVKxGRiX = false;
      bool ihtRATEifz = false;
      bool KLZVhNONUu = false;
      bool oimDmOGjBs = false;
      bool pHWLklXupq = false;
      bool WgNCukOGnx = false;
      bool irxmhAtpdk = false;
      bool MTgmJCoOku = false;
      string yeotrshqDB;
      string kHrDZQgMVF;
      string xyyajQsWEY;
      string xTeQXKNJaR;
      string ezcDlLFnNX;
      string UfymMzgNKa;
      string AKmdERcaeO;
      string CWkDayVtoY;
      string LEJgERUqDY;
      string dAzARTMyzT;
      string hdIyUxtuLO;
      string dlXkPuAGZl;
      string xkXGkCXklH;
      string lWuVpguLMG;
      string WYfntqbNkV;
      string SFXMWxGCMR;
      string ZIIEcGqCuh;
      string AosTOXEiLt;
      string aJAQnfziyr;
      string asytfOPbLn;
      if(yeotrshqDB == hdIyUxtuLO){AYSCVdMExy = true;}
      else if(hdIyUxtuLO == yeotrshqDB){EjGMqwZFjT = true;}
      if(kHrDZQgMVF == dlXkPuAGZl){rWpSqQIrPx = true;}
      else if(dlXkPuAGZl == kHrDZQgMVF){URMpKbQsBG = true;}
      if(xyyajQsWEY == xkXGkCXklH){HIDCHGqzmA = true;}
      else if(xkXGkCXklH == xyyajQsWEY){xocVKxGRiX = true;}
      if(xTeQXKNJaR == lWuVpguLMG){HcXWtBqytK = true;}
      else if(lWuVpguLMG == xTeQXKNJaR){ihtRATEifz = true;}
      if(ezcDlLFnNX == WYfntqbNkV){TtkAADCeDP = true;}
      else if(WYfntqbNkV == ezcDlLFnNX){KLZVhNONUu = true;}
      if(UfymMzgNKa == SFXMWxGCMR){FXLNgqVPtO = true;}
      else if(SFXMWxGCMR == UfymMzgNKa){oimDmOGjBs = true;}
      if(AKmdERcaeO == ZIIEcGqCuh){mMQwpOzSYp = true;}
      else if(ZIIEcGqCuh == AKmdERcaeO){pHWLklXupq = true;}
      if(CWkDayVtoY == AosTOXEiLt){YJxFdMWDCE = true;}
      if(LEJgERUqDY == aJAQnfziyr){DLwWujRJpC = true;}
      if(dAzARTMyzT == asytfOPbLn){ebDfWGcoJk = true;}
      while(AosTOXEiLt == CWkDayVtoY){WgNCukOGnx = true;}
      while(aJAQnfziyr == aJAQnfziyr){irxmhAtpdk = true;}
      while(asytfOPbLn == asytfOPbLn){MTgmJCoOku = true;}
      if(AYSCVdMExy == true){AYSCVdMExy = false;}
      if(rWpSqQIrPx == true){rWpSqQIrPx = false;}
      if(HIDCHGqzmA == true){HIDCHGqzmA = false;}
      if(HcXWtBqytK == true){HcXWtBqytK = false;}
      if(TtkAADCeDP == true){TtkAADCeDP = false;}
      if(FXLNgqVPtO == true){FXLNgqVPtO = false;}
      if(mMQwpOzSYp == true){mMQwpOzSYp = false;}
      if(YJxFdMWDCE == true){YJxFdMWDCE = false;}
      if(DLwWujRJpC == true){DLwWujRJpC = false;}
      if(ebDfWGcoJk == true){ebDfWGcoJk = false;}
      if(EjGMqwZFjT == true){EjGMqwZFjT = false;}
      if(URMpKbQsBG == true){URMpKbQsBG = false;}
      if(xocVKxGRiX == true){xocVKxGRiX = false;}
      if(ihtRATEifz == true){ihtRATEifz = false;}
      if(KLZVhNONUu == true){KLZVhNONUu = false;}
      if(oimDmOGjBs == true){oimDmOGjBs = false;}
      if(pHWLklXupq == true){pHWLklXupq = false;}
      if(WgNCukOGnx == true){WgNCukOGnx = false;}
      if(irxmhAtpdk == true){irxmhAtpdk = false;}
      if(MTgmJCoOku == true){MTgmJCoOku = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHAQNXBXCJ
{ 
  void EfNkJXVyyl()
  { 
      bool mYuxCgEjNh = false;
      bool hSrNiHExbN = false;
      bool gTXAMoCHKB = false;
      bool DTpGizYBMt = false;
      bool dTVNjBXemB = false;
      bool LdDeETBukN = false;
      bool dwYMeOckdj = false;
      bool hDkgiMxJPK = false;
      bool QXUIoZQLCO = false;
      bool xdPyQhuIhV = false;
      bool YmACSIsVuq = false;
      bool VqeZxGbQWF = false;
      bool yRiPlEmlQB = false;
      bool RnatlcXRog = false;
      bool gtPKrGzoBJ = false;
      bool FdlcXGDjQO = false;
      bool UGFtYhPjnT = false;
      bool hKapYDCXWf = false;
      bool FxkGumCyWe = false;
      bool ZmAaLZoUkK = false;
      string lkTcglAeUd;
      string jTqCkSXmKC;
      string MbjFxldAQS;
      string rtyUYLgKbX;
      string zEKCTjscYL;
      string XqWJTJANeu;
      string HANBloVWdZ;
      string kNKmCHQglN;
      string rAbFuAXoAO;
      string KTegPzpJQd;
      string NWzzZJgjGM;
      string rTaRCGXIFk;
      string RgVOORhcXD;
      string QHPHzVBcek;
      string TmhnWqrNeI;
      string bhDfMgAjkI;
      string bDMDwkDSSg;
      string FtdTRdyhrW;
      string YTyOahDjuR;
      string UQrVJPaerk;
      if(lkTcglAeUd == NWzzZJgjGM){mYuxCgEjNh = true;}
      else if(NWzzZJgjGM == lkTcglAeUd){YmACSIsVuq = true;}
      if(jTqCkSXmKC == rTaRCGXIFk){hSrNiHExbN = true;}
      else if(rTaRCGXIFk == jTqCkSXmKC){VqeZxGbQWF = true;}
      if(MbjFxldAQS == RgVOORhcXD){gTXAMoCHKB = true;}
      else if(RgVOORhcXD == MbjFxldAQS){yRiPlEmlQB = true;}
      if(rtyUYLgKbX == QHPHzVBcek){DTpGizYBMt = true;}
      else if(QHPHzVBcek == rtyUYLgKbX){RnatlcXRog = true;}
      if(zEKCTjscYL == TmhnWqrNeI){dTVNjBXemB = true;}
      else if(TmhnWqrNeI == zEKCTjscYL){gtPKrGzoBJ = true;}
      if(XqWJTJANeu == bhDfMgAjkI){LdDeETBukN = true;}
      else if(bhDfMgAjkI == XqWJTJANeu){FdlcXGDjQO = true;}
      if(HANBloVWdZ == bDMDwkDSSg){dwYMeOckdj = true;}
      else if(bDMDwkDSSg == HANBloVWdZ){UGFtYhPjnT = true;}
      if(kNKmCHQglN == FtdTRdyhrW){hDkgiMxJPK = true;}
      if(rAbFuAXoAO == YTyOahDjuR){QXUIoZQLCO = true;}
      if(KTegPzpJQd == UQrVJPaerk){xdPyQhuIhV = true;}
      while(FtdTRdyhrW == kNKmCHQglN){hKapYDCXWf = true;}
      while(YTyOahDjuR == YTyOahDjuR){FxkGumCyWe = true;}
      while(UQrVJPaerk == UQrVJPaerk){ZmAaLZoUkK = true;}
      if(mYuxCgEjNh == true){mYuxCgEjNh = false;}
      if(hSrNiHExbN == true){hSrNiHExbN = false;}
      if(gTXAMoCHKB == true){gTXAMoCHKB = false;}
      if(DTpGizYBMt == true){DTpGizYBMt = false;}
      if(dTVNjBXemB == true){dTVNjBXemB = false;}
      if(LdDeETBukN == true){LdDeETBukN = false;}
      if(dwYMeOckdj == true){dwYMeOckdj = false;}
      if(hDkgiMxJPK == true){hDkgiMxJPK = false;}
      if(QXUIoZQLCO == true){QXUIoZQLCO = false;}
      if(xdPyQhuIhV == true){xdPyQhuIhV = false;}
      if(YmACSIsVuq == true){YmACSIsVuq = false;}
      if(VqeZxGbQWF == true){VqeZxGbQWF = false;}
      if(yRiPlEmlQB == true){yRiPlEmlQB = false;}
      if(RnatlcXRog == true){RnatlcXRog = false;}
      if(gtPKrGzoBJ == true){gtPKrGzoBJ = false;}
      if(FdlcXGDjQO == true){FdlcXGDjQO = false;}
      if(UGFtYhPjnT == true){UGFtYhPjnT = false;}
      if(hKapYDCXWf == true){hKapYDCXWf = false;}
      if(FxkGumCyWe == true){FxkGumCyWe = false;}
      if(ZmAaLZoUkK == true){ZmAaLZoUkK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSEKCSNOJJ
{ 
  void ClVrDpfBTs()
  { 
      bool paquBtjNyj = false;
      bool xqDLsUpYlT = false;
      bool EaGlKkpXDO = false;
      bool ZRZQUZPeHJ = false;
      bool aZxubDUOjh = false;
      bool RKydZPTEjQ = false;
      bool DMKiJfRlpS = false;
      bool FLRcrddKKG = false;
      bool PbmUwOSuqF = false;
      bool GKtpFOPNlu = false;
      bool lhXRcGrUku = false;
      bool lItdBbYpmu = false;
      bool MWukLtQaXd = false;
      bool NQYOUgDVqo = false;
      bool VyJuSxPQoc = false;
      bool oYZqhPmmFh = false;
      bool pRwHhUieIT = false;
      bool YDyxYOMARN = false;
      bool ezkunnphfE = false;
      bool tPPIzEBBNy = false;
      string ZlTeEBSioU;
      string jfAWtSVLTO;
      string VMPNqHkMdr;
      string GlWpjVeaPH;
      string cOAgTncBUx;
      string enPpiMVFnw;
      string PFFwOyJKmY;
      string nuuMlGLitD;
      string ejrgMRVfHW;
      string zYmTqXJDRV;
      string dSNuIirDEb;
      string AmLjRfMYjw;
      string bdDPYOIbUN;
      string wIQYYLVwXd;
      string YSaeVMNCBL;
      string KkTVsAPxWt;
      string aQhpfrVlLG;
      string JPAFWJCXtL;
      string BGZJDLnufY;
      string uYZcCIjkyd;
      if(ZlTeEBSioU == dSNuIirDEb){paquBtjNyj = true;}
      else if(dSNuIirDEb == ZlTeEBSioU){lhXRcGrUku = true;}
      if(jfAWtSVLTO == AmLjRfMYjw){xqDLsUpYlT = true;}
      else if(AmLjRfMYjw == jfAWtSVLTO){lItdBbYpmu = true;}
      if(VMPNqHkMdr == bdDPYOIbUN){EaGlKkpXDO = true;}
      else if(bdDPYOIbUN == VMPNqHkMdr){MWukLtQaXd = true;}
      if(GlWpjVeaPH == wIQYYLVwXd){ZRZQUZPeHJ = true;}
      else if(wIQYYLVwXd == GlWpjVeaPH){NQYOUgDVqo = true;}
      if(cOAgTncBUx == YSaeVMNCBL){aZxubDUOjh = true;}
      else if(YSaeVMNCBL == cOAgTncBUx){VyJuSxPQoc = true;}
      if(enPpiMVFnw == KkTVsAPxWt){RKydZPTEjQ = true;}
      else if(KkTVsAPxWt == enPpiMVFnw){oYZqhPmmFh = true;}
      if(PFFwOyJKmY == aQhpfrVlLG){DMKiJfRlpS = true;}
      else if(aQhpfrVlLG == PFFwOyJKmY){pRwHhUieIT = true;}
      if(nuuMlGLitD == JPAFWJCXtL){FLRcrddKKG = true;}
      if(ejrgMRVfHW == BGZJDLnufY){PbmUwOSuqF = true;}
      if(zYmTqXJDRV == uYZcCIjkyd){GKtpFOPNlu = true;}
      while(JPAFWJCXtL == nuuMlGLitD){YDyxYOMARN = true;}
      while(BGZJDLnufY == BGZJDLnufY){ezkunnphfE = true;}
      while(uYZcCIjkyd == uYZcCIjkyd){tPPIzEBBNy = true;}
      if(paquBtjNyj == true){paquBtjNyj = false;}
      if(xqDLsUpYlT == true){xqDLsUpYlT = false;}
      if(EaGlKkpXDO == true){EaGlKkpXDO = false;}
      if(ZRZQUZPeHJ == true){ZRZQUZPeHJ = false;}
      if(aZxubDUOjh == true){aZxubDUOjh = false;}
      if(RKydZPTEjQ == true){RKydZPTEjQ = false;}
      if(DMKiJfRlpS == true){DMKiJfRlpS = false;}
      if(FLRcrddKKG == true){FLRcrddKKG = false;}
      if(PbmUwOSuqF == true){PbmUwOSuqF = false;}
      if(GKtpFOPNlu == true){GKtpFOPNlu = false;}
      if(lhXRcGrUku == true){lhXRcGrUku = false;}
      if(lItdBbYpmu == true){lItdBbYpmu = false;}
      if(MWukLtQaXd == true){MWukLtQaXd = false;}
      if(NQYOUgDVqo == true){NQYOUgDVqo = false;}
      if(VyJuSxPQoc == true){VyJuSxPQoc = false;}
      if(oYZqhPmmFh == true){oYZqhPmmFh = false;}
      if(pRwHhUieIT == true){pRwHhUieIT = false;}
      if(YDyxYOMARN == true){YDyxYOMARN = false;}
      if(ezkunnphfE == true){ezkunnphfE = false;}
      if(tPPIzEBBNy == true){tPPIzEBBNy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQCMDMMTEN
{ 
  void SEPSonRkEB()
  { 
      bool CkTAmhuexL = false;
      bool LCehsOoKSi = false;
      bool VrnXZRYFQR = false;
      bool CtWWCkXdfn = false;
      bool YsIfJBNBOR = false;
      bool LuYdHJxwZU = false;
      bool JoNeJRfIeH = false;
      bool pLeeKbiHOY = false;
      bool DWqyGGVsPr = false;
      bool naDKdjedWq = false;
      bool UFWGaAPsSe = false;
      bool ZohBRlyOYC = false;
      bool wmrlTPHUAZ = false;
      bool wFjWEyAjXF = false;
      bool qbZjSzsCrr = false;
      bool lPFUugMjmL = false;
      bool stsshUELxT = false;
      bool lNqSLTNITT = false;
      bool WFbInfzPbW = false;
      bool kQxLMwhfCx = false;
      string FddrQebqXc;
      string CRyIAZzHuy;
      string ZBcMxQSiep;
      string mcSzTXbUyu;
      string PErymOlqUD;
      string qlwkCDARtz;
      string MsLgpZzynb;
      string yeIAiVJeYh;
      string dbObyAfgxQ;
      string WJZziVrKHN;
      string PmCrELduBf;
      string sVrMUjejip;
      string sRAWFnFJRM;
      string czWLSqYVWl;
      string VkfQWARNdy;
      string qIaQTxmelP;
      string GUdnDtyfsd;
      string LIMwTIkjAE;
      string WreSVTXGqU;
      string EsjHfBGqMc;
      if(FddrQebqXc == PmCrELduBf){CkTAmhuexL = true;}
      else if(PmCrELduBf == FddrQebqXc){UFWGaAPsSe = true;}
      if(CRyIAZzHuy == sVrMUjejip){LCehsOoKSi = true;}
      else if(sVrMUjejip == CRyIAZzHuy){ZohBRlyOYC = true;}
      if(ZBcMxQSiep == sRAWFnFJRM){VrnXZRYFQR = true;}
      else if(sRAWFnFJRM == ZBcMxQSiep){wmrlTPHUAZ = true;}
      if(mcSzTXbUyu == czWLSqYVWl){CtWWCkXdfn = true;}
      else if(czWLSqYVWl == mcSzTXbUyu){wFjWEyAjXF = true;}
      if(PErymOlqUD == VkfQWARNdy){YsIfJBNBOR = true;}
      else if(VkfQWARNdy == PErymOlqUD){qbZjSzsCrr = true;}
      if(qlwkCDARtz == qIaQTxmelP){LuYdHJxwZU = true;}
      else if(qIaQTxmelP == qlwkCDARtz){lPFUugMjmL = true;}
      if(MsLgpZzynb == GUdnDtyfsd){JoNeJRfIeH = true;}
      else if(GUdnDtyfsd == MsLgpZzynb){stsshUELxT = true;}
      if(yeIAiVJeYh == LIMwTIkjAE){pLeeKbiHOY = true;}
      if(dbObyAfgxQ == WreSVTXGqU){DWqyGGVsPr = true;}
      if(WJZziVrKHN == EsjHfBGqMc){naDKdjedWq = true;}
      while(LIMwTIkjAE == yeIAiVJeYh){lNqSLTNITT = true;}
      while(WreSVTXGqU == WreSVTXGqU){WFbInfzPbW = true;}
      while(EsjHfBGqMc == EsjHfBGqMc){kQxLMwhfCx = true;}
      if(CkTAmhuexL == true){CkTAmhuexL = false;}
      if(LCehsOoKSi == true){LCehsOoKSi = false;}
      if(VrnXZRYFQR == true){VrnXZRYFQR = false;}
      if(CtWWCkXdfn == true){CtWWCkXdfn = false;}
      if(YsIfJBNBOR == true){YsIfJBNBOR = false;}
      if(LuYdHJxwZU == true){LuYdHJxwZU = false;}
      if(JoNeJRfIeH == true){JoNeJRfIeH = false;}
      if(pLeeKbiHOY == true){pLeeKbiHOY = false;}
      if(DWqyGGVsPr == true){DWqyGGVsPr = false;}
      if(naDKdjedWq == true){naDKdjedWq = false;}
      if(UFWGaAPsSe == true){UFWGaAPsSe = false;}
      if(ZohBRlyOYC == true){ZohBRlyOYC = false;}
      if(wmrlTPHUAZ == true){wmrlTPHUAZ = false;}
      if(wFjWEyAjXF == true){wFjWEyAjXF = false;}
      if(qbZjSzsCrr == true){qbZjSzsCrr = false;}
      if(lPFUugMjmL == true){lPFUugMjmL = false;}
      if(stsshUELxT == true){stsshUELxT = false;}
      if(lNqSLTNITT == true){lNqSLTNITT = false;}
      if(WFbInfzPbW == true){WFbInfzPbW = false;}
      if(kQxLMwhfCx == true){kQxLMwhfCx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWRMUGNQNG
{ 
  void xHEuJByLcI()
  { 
      bool EPolbxEfNr = false;
      bool oHLQuUjBqe = false;
      bool lpTNFPytxU = false;
      bool sCUGjPJoqx = false;
      bool ZXNFpeHWMz = false;
      bool OsQVSOwbfM = false;
      bool yKhsymmEfe = false;
      bool KuKsEObOXa = false;
      bool HahxFAkynV = false;
      bool TgJezPoUGC = false;
      bool rCpgoTiXRD = false;
      bool mhEEFXbkmy = false;
      bool BnPKLdletn = false;
      bool ZGHUiEjAIl = false;
      bool QNgkikbEZa = false;
      bool nEhIBDmfVK = false;
      bool hDdcdfZjUA = false;
      bool mbbBgmGebZ = false;
      bool BgFSAVXySe = false;
      bool REexDMjEHC = false;
      string yzstLrbJWs;
      string KWVbPdrQzo;
      string cCwfraunBb;
      string lkLghDoGXi;
      string zzyWNMzYdd;
      string mJRDYuDNBj;
      string xmItHZKnsM;
      string olsQocEZRe;
      string aWJWobSHHl;
      string AbEmkLqDOn;
      string BKeRnBQBOw;
      string qcuVIZdkFf;
      string GCgHLMgFec;
      string lBKddQqrin;
      string KRsLuWghdK;
      string hGxigydXFa;
      string TLVlJpRQrr;
      string ikBRUoJVLo;
      string fzaTueDbxe;
      string lTmHTzuHBE;
      if(yzstLrbJWs == BKeRnBQBOw){EPolbxEfNr = true;}
      else if(BKeRnBQBOw == yzstLrbJWs){rCpgoTiXRD = true;}
      if(KWVbPdrQzo == qcuVIZdkFf){oHLQuUjBqe = true;}
      else if(qcuVIZdkFf == KWVbPdrQzo){mhEEFXbkmy = true;}
      if(cCwfraunBb == GCgHLMgFec){lpTNFPytxU = true;}
      else if(GCgHLMgFec == cCwfraunBb){BnPKLdletn = true;}
      if(lkLghDoGXi == lBKddQqrin){sCUGjPJoqx = true;}
      else if(lBKddQqrin == lkLghDoGXi){ZGHUiEjAIl = true;}
      if(zzyWNMzYdd == KRsLuWghdK){ZXNFpeHWMz = true;}
      else if(KRsLuWghdK == zzyWNMzYdd){QNgkikbEZa = true;}
      if(mJRDYuDNBj == hGxigydXFa){OsQVSOwbfM = true;}
      else if(hGxigydXFa == mJRDYuDNBj){nEhIBDmfVK = true;}
      if(xmItHZKnsM == TLVlJpRQrr){yKhsymmEfe = true;}
      else if(TLVlJpRQrr == xmItHZKnsM){hDdcdfZjUA = true;}
      if(olsQocEZRe == ikBRUoJVLo){KuKsEObOXa = true;}
      if(aWJWobSHHl == fzaTueDbxe){HahxFAkynV = true;}
      if(AbEmkLqDOn == lTmHTzuHBE){TgJezPoUGC = true;}
      while(ikBRUoJVLo == olsQocEZRe){mbbBgmGebZ = true;}
      while(fzaTueDbxe == fzaTueDbxe){BgFSAVXySe = true;}
      while(lTmHTzuHBE == lTmHTzuHBE){REexDMjEHC = true;}
      if(EPolbxEfNr == true){EPolbxEfNr = false;}
      if(oHLQuUjBqe == true){oHLQuUjBqe = false;}
      if(lpTNFPytxU == true){lpTNFPytxU = false;}
      if(sCUGjPJoqx == true){sCUGjPJoqx = false;}
      if(ZXNFpeHWMz == true){ZXNFpeHWMz = false;}
      if(OsQVSOwbfM == true){OsQVSOwbfM = false;}
      if(yKhsymmEfe == true){yKhsymmEfe = false;}
      if(KuKsEObOXa == true){KuKsEObOXa = false;}
      if(HahxFAkynV == true){HahxFAkynV = false;}
      if(TgJezPoUGC == true){TgJezPoUGC = false;}
      if(rCpgoTiXRD == true){rCpgoTiXRD = false;}
      if(mhEEFXbkmy == true){mhEEFXbkmy = false;}
      if(BnPKLdletn == true){BnPKLdletn = false;}
      if(ZGHUiEjAIl == true){ZGHUiEjAIl = false;}
      if(QNgkikbEZa == true){QNgkikbEZa = false;}
      if(nEhIBDmfVK == true){nEhIBDmfVK = false;}
      if(hDdcdfZjUA == true){hDdcdfZjUA = false;}
      if(mbbBgmGebZ == true){mbbBgmGebZ = false;}
      if(BgFSAVXySe == true){BgFSAVXySe = false;}
      if(REexDMjEHC == true){REexDMjEHC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBGJAAPIZN
{ 
  void ERZXEhWIsK()
  { 
      bool OYlKtHlNLI = false;
      bool otRLDMkbaG = false;
      bool ldTADQBPSU = false;
      bool jNqLZZOPix = false;
      bool OhtIuMwRsr = false;
      bool juppZjFkGc = false;
      bool GVtpYaDFld = false;
      bool yVsdqDjLFq = false;
      bool UiWZknXAlo = false;
      bool UdIFqrnDjT = false;
      bool IpePtOCMyV = false;
      bool AsfPIWzUEk = false;
      bool DDTxJTMnlz = false;
      bool PfbkheEHeW = false;
      bool kLBPnayswU = false;
      bool sSzyQFVhFa = false;
      bool BOZzGURtgd = false;
      bool SqohzqBEIh = false;
      bool VTqRGwfcTb = false;
      bool IVBEUWlCIT = false;
      string YgKELnBklW;
      string VlgQkSFJIJ;
      string xtLHFstcLk;
      string NzkenKfPoA;
      string UkffXAciMz;
      string daONTeVCyR;
      string sYYAIVBCba;
      string mpTInLNejF;
      string QLPMHmjXKJ;
      string ocQXGuLfXC;
      string yZHlMmGGYH;
      string QqSsBhIMsV;
      string kdqRlJYwBr;
      string AhHgGpDdzT;
      string fcyDsxKXVY;
      string lzlBQUhpAC;
      string NKFgGhiklL;
      string deMYpHenXn;
      string zAZcFAwFQk;
      string HNdwFUXQwL;
      if(YgKELnBklW == yZHlMmGGYH){OYlKtHlNLI = true;}
      else if(yZHlMmGGYH == YgKELnBklW){IpePtOCMyV = true;}
      if(VlgQkSFJIJ == QqSsBhIMsV){otRLDMkbaG = true;}
      else if(QqSsBhIMsV == VlgQkSFJIJ){AsfPIWzUEk = true;}
      if(xtLHFstcLk == kdqRlJYwBr){ldTADQBPSU = true;}
      else if(kdqRlJYwBr == xtLHFstcLk){DDTxJTMnlz = true;}
      if(NzkenKfPoA == AhHgGpDdzT){jNqLZZOPix = true;}
      else if(AhHgGpDdzT == NzkenKfPoA){PfbkheEHeW = true;}
      if(UkffXAciMz == fcyDsxKXVY){OhtIuMwRsr = true;}
      else if(fcyDsxKXVY == UkffXAciMz){kLBPnayswU = true;}
      if(daONTeVCyR == lzlBQUhpAC){juppZjFkGc = true;}
      else if(lzlBQUhpAC == daONTeVCyR){sSzyQFVhFa = true;}
      if(sYYAIVBCba == NKFgGhiklL){GVtpYaDFld = true;}
      else if(NKFgGhiklL == sYYAIVBCba){BOZzGURtgd = true;}
      if(mpTInLNejF == deMYpHenXn){yVsdqDjLFq = true;}
      if(QLPMHmjXKJ == zAZcFAwFQk){UiWZknXAlo = true;}
      if(ocQXGuLfXC == HNdwFUXQwL){UdIFqrnDjT = true;}
      while(deMYpHenXn == mpTInLNejF){SqohzqBEIh = true;}
      while(zAZcFAwFQk == zAZcFAwFQk){VTqRGwfcTb = true;}
      while(HNdwFUXQwL == HNdwFUXQwL){IVBEUWlCIT = true;}
      if(OYlKtHlNLI == true){OYlKtHlNLI = false;}
      if(otRLDMkbaG == true){otRLDMkbaG = false;}
      if(ldTADQBPSU == true){ldTADQBPSU = false;}
      if(jNqLZZOPix == true){jNqLZZOPix = false;}
      if(OhtIuMwRsr == true){OhtIuMwRsr = false;}
      if(juppZjFkGc == true){juppZjFkGc = false;}
      if(GVtpYaDFld == true){GVtpYaDFld = false;}
      if(yVsdqDjLFq == true){yVsdqDjLFq = false;}
      if(UiWZknXAlo == true){UiWZknXAlo = false;}
      if(UdIFqrnDjT == true){UdIFqrnDjT = false;}
      if(IpePtOCMyV == true){IpePtOCMyV = false;}
      if(AsfPIWzUEk == true){AsfPIWzUEk = false;}
      if(DDTxJTMnlz == true){DDTxJTMnlz = false;}
      if(PfbkheEHeW == true){PfbkheEHeW = false;}
      if(kLBPnayswU == true){kLBPnayswU = false;}
      if(sSzyQFVhFa == true){sSzyQFVhFa = false;}
      if(BOZzGURtgd == true){BOZzGURtgd = false;}
      if(SqohzqBEIh == true){SqohzqBEIh = false;}
      if(VTqRGwfcTb == true){VTqRGwfcTb = false;}
      if(IVBEUWlCIT == true){IVBEUWlCIT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LONTYXQFYS
{ 
  void nkSwRaygKi()
  { 
      bool imACutpCzE = false;
      bool FrluknFaBw = false;
      bool wamPRocdYG = false;
      bool lKVtEdcqHi = false;
      bool NrtiVwecfN = false;
      bool KpzWaIAkjF = false;
      bool QMdrRtVrpH = false;
      bool LOSRiEgDsV = false;
      bool KAxKwuLySw = false;
      bool crHCRBNBQa = false;
      bool ZllYCwXgnV = false;
      bool bwqNtQPTuW = false;
      bool iXYteSGQAh = false;
      bool pelSwYNYHA = false;
      bool XdJwUfAsHA = false;
      bool ktFtqCNrtj = false;
      bool oHgGfwKYRV = false;
      bool DpLuyFNbZy = false;
      bool RNIzwwYqat = false;
      bool LVeXLQxDQX = false;
      string yAJCbUaTtU;
      string ShaDZbtXjS;
      string QgqjYhskAo;
      string NqKBtwLBgE;
      string rVgQhcRqEy;
      string ftNdmQJZdt;
      string boSFHaWYJd;
      string QrpfauAZCw;
      string PBgCITcgNd;
      string mkXmbCDaJG;
      string FshZhmDhCr;
      string PiWgdZHQxm;
      string yoKeqeUDEX;
      string qYPwqWTGUV;
      string PteUNDOpJB;
      string umdWHPhDiC;
      string SzddBqTapG;
      string GAwaWDKpQn;
      string QdtCcEtsna;
      string nQXRCQQATW;
      if(yAJCbUaTtU == FshZhmDhCr){imACutpCzE = true;}
      else if(FshZhmDhCr == yAJCbUaTtU){ZllYCwXgnV = true;}
      if(ShaDZbtXjS == PiWgdZHQxm){FrluknFaBw = true;}
      else if(PiWgdZHQxm == ShaDZbtXjS){bwqNtQPTuW = true;}
      if(QgqjYhskAo == yoKeqeUDEX){wamPRocdYG = true;}
      else if(yoKeqeUDEX == QgqjYhskAo){iXYteSGQAh = true;}
      if(NqKBtwLBgE == qYPwqWTGUV){lKVtEdcqHi = true;}
      else if(qYPwqWTGUV == NqKBtwLBgE){pelSwYNYHA = true;}
      if(rVgQhcRqEy == PteUNDOpJB){NrtiVwecfN = true;}
      else if(PteUNDOpJB == rVgQhcRqEy){XdJwUfAsHA = true;}
      if(ftNdmQJZdt == umdWHPhDiC){KpzWaIAkjF = true;}
      else if(umdWHPhDiC == ftNdmQJZdt){ktFtqCNrtj = true;}
      if(boSFHaWYJd == SzddBqTapG){QMdrRtVrpH = true;}
      else if(SzddBqTapG == boSFHaWYJd){oHgGfwKYRV = true;}
      if(QrpfauAZCw == GAwaWDKpQn){LOSRiEgDsV = true;}
      if(PBgCITcgNd == QdtCcEtsna){KAxKwuLySw = true;}
      if(mkXmbCDaJG == nQXRCQQATW){crHCRBNBQa = true;}
      while(GAwaWDKpQn == QrpfauAZCw){DpLuyFNbZy = true;}
      while(QdtCcEtsna == QdtCcEtsna){RNIzwwYqat = true;}
      while(nQXRCQQATW == nQXRCQQATW){LVeXLQxDQX = true;}
      if(imACutpCzE == true){imACutpCzE = false;}
      if(FrluknFaBw == true){FrluknFaBw = false;}
      if(wamPRocdYG == true){wamPRocdYG = false;}
      if(lKVtEdcqHi == true){lKVtEdcqHi = false;}
      if(NrtiVwecfN == true){NrtiVwecfN = false;}
      if(KpzWaIAkjF == true){KpzWaIAkjF = false;}
      if(QMdrRtVrpH == true){QMdrRtVrpH = false;}
      if(LOSRiEgDsV == true){LOSRiEgDsV = false;}
      if(KAxKwuLySw == true){KAxKwuLySw = false;}
      if(crHCRBNBQa == true){crHCRBNBQa = false;}
      if(ZllYCwXgnV == true){ZllYCwXgnV = false;}
      if(bwqNtQPTuW == true){bwqNtQPTuW = false;}
      if(iXYteSGQAh == true){iXYteSGQAh = false;}
      if(pelSwYNYHA == true){pelSwYNYHA = false;}
      if(XdJwUfAsHA == true){XdJwUfAsHA = false;}
      if(ktFtqCNrtj == true){ktFtqCNrtj = false;}
      if(oHgGfwKYRV == true){oHgGfwKYRV = false;}
      if(DpLuyFNbZy == true){DpLuyFNbZy = false;}
      if(RNIzwwYqat == true){RNIzwwYqat = false;}
      if(LVeXLQxDQX == true){LVeXLQxDQX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UWXVZZBSDR
{ 
  void YTHdNSxPjo()
  { 
      bool XHNZmmULPE = false;
      bool XBmcWQaPoq = false;
      bool EtqEyIZMay = false;
      bool lIrzytARjJ = false;
      bool ARYMPAqtKB = false;
      bool ylyqLdQIae = false;
      bool MIjQRPJmdb = false;
      bool PIefqlUdoy = false;
      bool QfCZzAKAnU = false;
      bool dqpFwqhHuz = false;
      bool pDPhkoGRzY = false;
      bool IlTbNfGJQR = false;
      bool EIzJxXSZiA = false;
      bool EMioINPTnJ = false;
      bool trAOLqXNqP = false;
      bool kXqcugEFjN = false;
      bool WgizUuDdTA = false;
      bool QlUGWMIjxF = false;
      bool AEiSOfVFta = false;
      bool IKjamNJBsQ = false;
      string tREmKJBlCe;
      string LICeFjVrHS;
      string GDbFsypcpR;
      string lHxlDIhxTN;
      string eJcwZyRras;
      string WJfGsppysM;
      string SXujrEKQaw;
      string BXYsnxafft;
      string fyCwucaqrN;
      string RiEGuGNsDV;
      string mBQdqyjlSw;
      string PKSyfUVzoP;
      string cTXNdSTRyg;
      string ihbKGegXFw;
      string roYwyHQFaa;
      string kOEmrTcCAY;
      string eSmkMhiIrA;
      string mysrXnuaPW;
      string COqXwUcnRm;
      string BdXgRZBmiP;
      if(tREmKJBlCe == mBQdqyjlSw){XHNZmmULPE = true;}
      else if(mBQdqyjlSw == tREmKJBlCe){pDPhkoGRzY = true;}
      if(LICeFjVrHS == PKSyfUVzoP){XBmcWQaPoq = true;}
      else if(PKSyfUVzoP == LICeFjVrHS){IlTbNfGJQR = true;}
      if(GDbFsypcpR == cTXNdSTRyg){EtqEyIZMay = true;}
      else if(cTXNdSTRyg == GDbFsypcpR){EIzJxXSZiA = true;}
      if(lHxlDIhxTN == ihbKGegXFw){lIrzytARjJ = true;}
      else if(ihbKGegXFw == lHxlDIhxTN){EMioINPTnJ = true;}
      if(eJcwZyRras == roYwyHQFaa){ARYMPAqtKB = true;}
      else if(roYwyHQFaa == eJcwZyRras){trAOLqXNqP = true;}
      if(WJfGsppysM == kOEmrTcCAY){ylyqLdQIae = true;}
      else if(kOEmrTcCAY == WJfGsppysM){kXqcugEFjN = true;}
      if(SXujrEKQaw == eSmkMhiIrA){MIjQRPJmdb = true;}
      else if(eSmkMhiIrA == SXujrEKQaw){WgizUuDdTA = true;}
      if(BXYsnxafft == mysrXnuaPW){PIefqlUdoy = true;}
      if(fyCwucaqrN == COqXwUcnRm){QfCZzAKAnU = true;}
      if(RiEGuGNsDV == BdXgRZBmiP){dqpFwqhHuz = true;}
      while(mysrXnuaPW == BXYsnxafft){QlUGWMIjxF = true;}
      while(COqXwUcnRm == COqXwUcnRm){AEiSOfVFta = true;}
      while(BdXgRZBmiP == BdXgRZBmiP){IKjamNJBsQ = true;}
      if(XHNZmmULPE == true){XHNZmmULPE = false;}
      if(XBmcWQaPoq == true){XBmcWQaPoq = false;}
      if(EtqEyIZMay == true){EtqEyIZMay = false;}
      if(lIrzytARjJ == true){lIrzytARjJ = false;}
      if(ARYMPAqtKB == true){ARYMPAqtKB = false;}
      if(ylyqLdQIae == true){ylyqLdQIae = false;}
      if(MIjQRPJmdb == true){MIjQRPJmdb = false;}
      if(PIefqlUdoy == true){PIefqlUdoy = false;}
      if(QfCZzAKAnU == true){QfCZzAKAnU = false;}
      if(dqpFwqhHuz == true){dqpFwqhHuz = false;}
      if(pDPhkoGRzY == true){pDPhkoGRzY = false;}
      if(IlTbNfGJQR == true){IlTbNfGJQR = false;}
      if(EIzJxXSZiA == true){EIzJxXSZiA = false;}
      if(EMioINPTnJ == true){EMioINPTnJ = false;}
      if(trAOLqXNqP == true){trAOLqXNqP = false;}
      if(kXqcugEFjN == true){kXqcugEFjN = false;}
      if(WgizUuDdTA == true){WgizUuDdTA = false;}
      if(QlUGWMIjxF == true){QlUGWMIjxF = false;}
      if(AEiSOfVFta == true){AEiSOfVFta = false;}
      if(IKjamNJBsQ == true){IKjamNJBsQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NACEMHZROR
{ 
  void BeEgRsOhxc()
  { 
      bool BSUocJCUUU = false;
      bool zdfcxfHMhC = false;
      bool AgBuXcbbYF = false;
      bool kYparsSqyz = false;
      bool rYbOBXtLwF = false;
      bool gayXBURZRA = false;
      bool hawPjamEkE = false;
      bool MPNhJaEmsz = false;
      bool iPfTXKZSZW = false;
      bool asZyRQcMdZ = false;
      bool koaqrRMPNZ = false;
      bool QefRRRtcqZ = false;
      bool ATeNcTpPQs = false;
      bool yrITOsonaF = false;
      bool yKFzGwNHgA = false;
      bool VAUEYQJMNY = false;
      bool bwzTaXVMDX = false;
      bool bGBkbpOeHf = false;
      bool GhhQWyXDtx = false;
      bool icZCdBLkYh = false;
      string sxgmfydwTK;
      string UhuwqtkMzW;
      string UFOruhrtqb;
      string buIVEAILgX;
      string lDlTTHGZlM;
      string yPWKhnhnqx;
      string FiEriYZZqq;
      string kZfakRSuYn;
      string bSHecMXxmQ;
      string RTUjSCysjt;
      string hfiuaYjwZQ;
      string UmPCUmbZOW;
      string AclZYQFuHi;
      string TYKdGuiLDE;
      string cbXWweEROf;
      string ZYeNtEsIWJ;
      string TnnqwuckwZ;
      string DQVJsYFPct;
      string MmgbIttwjB;
      string BZnsknmfZB;
      if(sxgmfydwTK == hfiuaYjwZQ){BSUocJCUUU = true;}
      else if(hfiuaYjwZQ == sxgmfydwTK){koaqrRMPNZ = true;}
      if(UhuwqtkMzW == UmPCUmbZOW){zdfcxfHMhC = true;}
      else if(UmPCUmbZOW == UhuwqtkMzW){QefRRRtcqZ = true;}
      if(UFOruhrtqb == AclZYQFuHi){AgBuXcbbYF = true;}
      else if(AclZYQFuHi == UFOruhrtqb){ATeNcTpPQs = true;}
      if(buIVEAILgX == TYKdGuiLDE){kYparsSqyz = true;}
      else if(TYKdGuiLDE == buIVEAILgX){yrITOsonaF = true;}
      if(lDlTTHGZlM == cbXWweEROf){rYbOBXtLwF = true;}
      else if(cbXWweEROf == lDlTTHGZlM){yKFzGwNHgA = true;}
      if(yPWKhnhnqx == ZYeNtEsIWJ){gayXBURZRA = true;}
      else if(ZYeNtEsIWJ == yPWKhnhnqx){VAUEYQJMNY = true;}
      if(FiEriYZZqq == TnnqwuckwZ){hawPjamEkE = true;}
      else if(TnnqwuckwZ == FiEriYZZqq){bwzTaXVMDX = true;}
      if(kZfakRSuYn == DQVJsYFPct){MPNhJaEmsz = true;}
      if(bSHecMXxmQ == MmgbIttwjB){iPfTXKZSZW = true;}
      if(RTUjSCysjt == BZnsknmfZB){asZyRQcMdZ = true;}
      while(DQVJsYFPct == kZfakRSuYn){bGBkbpOeHf = true;}
      while(MmgbIttwjB == MmgbIttwjB){GhhQWyXDtx = true;}
      while(BZnsknmfZB == BZnsknmfZB){icZCdBLkYh = true;}
      if(BSUocJCUUU == true){BSUocJCUUU = false;}
      if(zdfcxfHMhC == true){zdfcxfHMhC = false;}
      if(AgBuXcbbYF == true){AgBuXcbbYF = false;}
      if(kYparsSqyz == true){kYparsSqyz = false;}
      if(rYbOBXtLwF == true){rYbOBXtLwF = false;}
      if(gayXBURZRA == true){gayXBURZRA = false;}
      if(hawPjamEkE == true){hawPjamEkE = false;}
      if(MPNhJaEmsz == true){MPNhJaEmsz = false;}
      if(iPfTXKZSZW == true){iPfTXKZSZW = false;}
      if(asZyRQcMdZ == true){asZyRQcMdZ = false;}
      if(koaqrRMPNZ == true){koaqrRMPNZ = false;}
      if(QefRRRtcqZ == true){QefRRRtcqZ = false;}
      if(ATeNcTpPQs == true){ATeNcTpPQs = false;}
      if(yrITOsonaF == true){yrITOsonaF = false;}
      if(yKFzGwNHgA == true){yKFzGwNHgA = false;}
      if(VAUEYQJMNY == true){VAUEYQJMNY = false;}
      if(bwzTaXVMDX == true){bwzTaXVMDX = false;}
      if(bGBkbpOeHf == true){bGBkbpOeHf = false;}
      if(GhhQWyXDtx == true){GhhQWyXDtx = false;}
      if(icZCdBLkYh == true){icZCdBLkYh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBZNJOYMTO
{ 
  void ROyUdxicqB()
  { 
      bool sASypndpjs = false;
      bool NNGOlTBVnq = false;
      bool zYcuWNTuuH = false;
      bool GisipDGWqi = false;
      bool zuyamUyxyc = false;
      bool XssErUXWbc = false;
      bool ThucmeTXXh = false;
      bool MddErEaCHC = false;
      bool OWxRiNonpV = false;
      bool fiuOPQAUnI = false;
      bool AaYPQsOoMn = false;
      bool sUPYNxkcsZ = false;
      bool oegBCciPoa = false;
      bool EFOyBmxhBp = false;
      bool yAbCcKTVAS = false;
      bool fWbNSUsXMm = false;
      bool JyzkinGQWZ = false;
      bool zCaCaoDeYr = false;
      bool JMOWtgdAeg = false;
      bool sZUOfzAqSn = false;
      string rCRBHoLSjg;
      string bJLNtfMtMH;
      string sCFxIaFWsg;
      string KWEhYDziZB;
      string BpSOJqjcaZ;
      string KQGIKoxUrg;
      string jnZDVFEcoq;
      string gdTKFDjqmR;
      string qbuTVsPwXi;
      string GepsRNQPrE;
      string lGnjrgxwDH;
      string FFgaoHrGgb;
      string oIEFkCnZrr;
      string mTyiejnLao;
      string wTrPdAyOEJ;
      string UJhPOdBhzp;
      string rWEKUkHxwF;
      string TgfrfVPnbj;
      string EYVhWckhTB;
      string hFMjwYOgur;
      if(rCRBHoLSjg == lGnjrgxwDH){sASypndpjs = true;}
      else if(lGnjrgxwDH == rCRBHoLSjg){AaYPQsOoMn = true;}
      if(bJLNtfMtMH == FFgaoHrGgb){NNGOlTBVnq = true;}
      else if(FFgaoHrGgb == bJLNtfMtMH){sUPYNxkcsZ = true;}
      if(sCFxIaFWsg == oIEFkCnZrr){zYcuWNTuuH = true;}
      else if(oIEFkCnZrr == sCFxIaFWsg){oegBCciPoa = true;}
      if(KWEhYDziZB == mTyiejnLao){GisipDGWqi = true;}
      else if(mTyiejnLao == KWEhYDziZB){EFOyBmxhBp = true;}
      if(BpSOJqjcaZ == wTrPdAyOEJ){zuyamUyxyc = true;}
      else if(wTrPdAyOEJ == BpSOJqjcaZ){yAbCcKTVAS = true;}
      if(KQGIKoxUrg == UJhPOdBhzp){XssErUXWbc = true;}
      else if(UJhPOdBhzp == KQGIKoxUrg){fWbNSUsXMm = true;}
      if(jnZDVFEcoq == rWEKUkHxwF){ThucmeTXXh = true;}
      else if(rWEKUkHxwF == jnZDVFEcoq){JyzkinGQWZ = true;}
      if(gdTKFDjqmR == TgfrfVPnbj){MddErEaCHC = true;}
      if(qbuTVsPwXi == EYVhWckhTB){OWxRiNonpV = true;}
      if(GepsRNQPrE == hFMjwYOgur){fiuOPQAUnI = true;}
      while(TgfrfVPnbj == gdTKFDjqmR){zCaCaoDeYr = true;}
      while(EYVhWckhTB == EYVhWckhTB){JMOWtgdAeg = true;}
      while(hFMjwYOgur == hFMjwYOgur){sZUOfzAqSn = true;}
      if(sASypndpjs == true){sASypndpjs = false;}
      if(NNGOlTBVnq == true){NNGOlTBVnq = false;}
      if(zYcuWNTuuH == true){zYcuWNTuuH = false;}
      if(GisipDGWqi == true){GisipDGWqi = false;}
      if(zuyamUyxyc == true){zuyamUyxyc = false;}
      if(XssErUXWbc == true){XssErUXWbc = false;}
      if(ThucmeTXXh == true){ThucmeTXXh = false;}
      if(MddErEaCHC == true){MddErEaCHC = false;}
      if(OWxRiNonpV == true){OWxRiNonpV = false;}
      if(fiuOPQAUnI == true){fiuOPQAUnI = false;}
      if(AaYPQsOoMn == true){AaYPQsOoMn = false;}
      if(sUPYNxkcsZ == true){sUPYNxkcsZ = false;}
      if(oegBCciPoa == true){oegBCciPoa = false;}
      if(EFOyBmxhBp == true){EFOyBmxhBp = false;}
      if(yAbCcKTVAS == true){yAbCcKTVAS = false;}
      if(fWbNSUsXMm == true){fWbNSUsXMm = false;}
      if(JyzkinGQWZ == true){JyzkinGQWZ = false;}
      if(zCaCaoDeYr == true){zCaCaoDeYr = false;}
      if(JMOWtgdAeg == true){JMOWtgdAeg = false;}
      if(sZUOfzAqSn == true){sZUOfzAqSn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGZFHVZZZC
{ 
  void EryINaTfAi()
  { 
      bool kdiJHWCVVw = false;
      bool zUGIeMhxry = false;
      bool iocTePbBHD = false;
      bool qxBUSikUon = false;
      bool bhHliWhPHK = false;
      bool TOrxyuAPer = false;
      bool tBNSEBSlpw = false;
      bool aNIDWBhpjH = false;
      bool gLsxibFEWW = false;
      bool hVowtZTohg = false;
      bool DwZLiFGnaw = false;
      bool NJeWLhIQib = false;
      bool wOOSNFYLJw = false;
      bool hrICDklgNc = false;
      bool VQcZJYpSkL = false;
      bool RCFFkogHyd = false;
      bool gtdeOUAcSZ = false;
      bool waDGGfkoIo = false;
      bool PFaydelDRO = false;
      bool DdiiwamyLn = false;
      string ufSGNnIyVq;
      string NBqnnKBTZw;
      string iJGdTgDOFq;
      string ipEzACYpuA;
      string DDQFjAgVHf;
      string ywdeclZolg;
      string kssdIXwrmk;
      string lKYZrerBtT;
      string zgHYsmLZVO;
      string ciENPJKmwL;
      string DohVtnXElx;
      string sXtSgDlTkU;
      string LVVYICGKJh;
      string UFEhPKzkeF;
      string PHnXVEokfM;
      string WqBaAgSJMr;
      string gMtDbmSLCW;
      string EAnfFEhxDE;
      string MUdxKdDchi;
      string roYmXCMjuh;
      if(ufSGNnIyVq == DohVtnXElx){kdiJHWCVVw = true;}
      else if(DohVtnXElx == ufSGNnIyVq){DwZLiFGnaw = true;}
      if(NBqnnKBTZw == sXtSgDlTkU){zUGIeMhxry = true;}
      else if(sXtSgDlTkU == NBqnnKBTZw){NJeWLhIQib = true;}
      if(iJGdTgDOFq == LVVYICGKJh){iocTePbBHD = true;}
      else if(LVVYICGKJh == iJGdTgDOFq){wOOSNFYLJw = true;}
      if(ipEzACYpuA == UFEhPKzkeF){qxBUSikUon = true;}
      else if(UFEhPKzkeF == ipEzACYpuA){hrICDklgNc = true;}
      if(DDQFjAgVHf == PHnXVEokfM){bhHliWhPHK = true;}
      else if(PHnXVEokfM == DDQFjAgVHf){VQcZJYpSkL = true;}
      if(ywdeclZolg == WqBaAgSJMr){TOrxyuAPer = true;}
      else if(WqBaAgSJMr == ywdeclZolg){RCFFkogHyd = true;}
      if(kssdIXwrmk == gMtDbmSLCW){tBNSEBSlpw = true;}
      else if(gMtDbmSLCW == kssdIXwrmk){gtdeOUAcSZ = true;}
      if(lKYZrerBtT == EAnfFEhxDE){aNIDWBhpjH = true;}
      if(zgHYsmLZVO == MUdxKdDchi){gLsxibFEWW = true;}
      if(ciENPJKmwL == roYmXCMjuh){hVowtZTohg = true;}
      while(EAnfFEhxDE == lKYZrerBtT){waDGGfkoIo = true;}
      while(MUdxKdDchi == MUdxKdDchi){PFaydelDRO = true;}
      while(roYmXCMjuh == roYmXCMjuh){DdiiwamyLn = true;}
      if(kdiJHWCVVw == true){kdiJHWCVVw = false;}
      if(zUGIeMhxry == true){zUGIeMhxry = false;}
      if(iocTePbBHD == true){iocTePbBHD = false;}
      if(qxBUSikUon == true){qxBUSikUon = false;}
      if(bhHliWhPHK == true){bhHliWhPHK = false;}
      if(TOrxyuAPer == true){TOrxyuAPer = false;}
      if(tBNSEBSlpw == true){tBNSEBSlpw = false;}
      if(aNIDWBhpjH == true){aNIDWBhpjH = false;}
      if(gLsxibFEWW == true){gLsxibFEWW = false;}
      if(hVowtZTohg == true){hVowtZTohg = false;}
      if(DwZLiFGnaw == true){DwZLiFGnaw = false;}
      if(NJeWLhIQib == true){NJeWLhIQib = false;}
      if(wOOSNFYLJw == true){wOOSNFYLJw = false;}
      if(hrICDklgNc == true){hrICDklgNc = false;}
      if(VQcZJYpSkL == true){VQcZJYpSkL = false;}
      if(RCFFkogHyd == true){RCFFkogHyd = false;}
      if(gtdeOUAcSZ == true){gtdeOUAcSZ = false;}
      if(waDGGfkoIo == true){waDGGfkoIo = false;}
      if(PFaydelDRO == true){PFaydelDRO = false;}
      if(DdiiwamyLn == true){DdiiwamyLn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JVAILHFQBC
{ 
  void QjKtqrRYeU()
  { 
      bool uwbiQedLaB = false;
      bool VHVyMnMYDq = false;
      bool iHcpKuumNP = false;
      bool AiHEHkKlBQ = false;
      bool wMZlEygezF = false;
      bool uAHzhnSlYU = false;
      bool ipyLBlzRpa = false;
      bool caXltVgplL = false;
      bool OPmHTzbHWT = false;
      bool RXMfhGOOkR = false;
      bool yPoYcTcUEM = false;
      bool GcAMGSDqqC = false;
      bool KrtVJENrEn = false;
      bool HRFTNyaOeA = false;
      bool WHCKMoXAYO = false;
      bool CWXhHGUTOX = false;
      bool FkPQEoWfzH = false;
      bool rnMpeCojIT = false;
      bool gNSpkjtWMG = false;
      bool dGzGtlrlFX = false;
      string WLIHbNMYMF;
      string wfdcIEnZeI;
      string VklpralTYJ;
      string uLQoKlNLcl;
      string AiyXFiBEee;
      string hATHJlYSOB;
      string brADJjOnSV;
      string pbxsHmmOkJ;
      string YgntaurJfX;
      string NuxbKHiuNU;
      string TNlJnFDazW;
      string zJhEbtEFbO;
      string rEHtHteUiz;
      string EqAQoLueFU;
      string qRKJYENrzP;
      string DcSzbPFrBs;
      string ahqzRHIQPQ;
      string zYzHXZtyVD;
      string gmUSuaYBnZ;
      string FDcMtIZKqQ;
      if(WLIHbNMYMF == TNlJnFDazW){uwbiQedLaB = true;}
      else if(TNlJnFDazW == WLIHbNMYMF){yPoYcTcUEM = true;}
      if(wfdcIEnZeI == zJhEbtEFbO){VHVyMnMYDq = true;}
      else if(zJhEbtEFbO == wfdcIEnZeI){GcAMGSDqqC = true;}
      if(VklpralTYJ == rEHtHteUiz){iHcpKuumNP = true;}
      else if(rEHtHteUiz == VklpralTYJ){KrtVJENrEn = true;}
      if(uLQoKlNLcl == EqAQoLueFU){AiHEHkKlBQ = true;}
      else if(EqAQoLueFU == uLQoKlNLcl){HRFTNyaOeA = true;}
      if(AiyXFiBEee == qRKJYENrzP){wMZlEygezF = true;}
      else if(qRKJYENrzP == AiyXFiBEee){WHCKMoXAYO = true;}
      if(hATHJlYSOB == DcSzbPFrBs){uAHzhnSlYU = true;}
      else if(DcSzbPFrBs == hATHJlYSOB){CWXhHGUTOX = true;}
      if(brADJjOnSV == ahqzRHIQPQ){ipyLBlzRpa = true;}
      else if(ahqzRHIQPQ == brADJjOnSV){FkPQEoWfzH = true;}
      if(pbxsHmmOkJ == zYzHXZtyVD){caXltVgplL = true;}
      if(YgntaurJfX == gmUSuaYBnZ){OPmHTzbHWT = true;}
      if(NuxbKHiuNU == FDcMtIZKqQ){RXMfhGOOkR = true;}
      while(zYzHXZtyVD == pbxsHmmOkJ){rnMpeCojIT = true;}
      while(gmUSuaYBnZ == gmUSuaYBnZ){gNSpkjtWMG = true;}
      while(FDcMtIZKqQ == FDcMtIZKqQ){dGzGtlrlFX = true;}
      if(uwbiQedLaB == true){uwbiQedLaB = false;}
      if(VHVyMnMYDq == true){VHVyMnMYDq = false;}
      if(iHcpKuumNP == true){iHcpKuumNP = false;}
      if(AiHEHkKlBQ == true){AiHEHkKlBQ = false;}
      if(wMZlEygezF == true){wMZlEygezF = false;}
      if(uAHzhnSlYU == true){uAHzhnSlYU = false;}
      if(ipyLBlzRpa == true){ipyLBlzRpa = false;}
      if(caXltVgplL == true){caXltVgplL = false;}
      if(OPmHTzbHWT == true){OPmHTzbHWT = false;}
      if(RXMfhGOOkR == true){RXMfhGOOkR = false;}
      if(yPoYcTcUEM == true){yPoYcTcUEM = false;}
      if(GcAMGSDqqC == true){GcAMGSDqqC = false;}
      if(KrtVJENrEn == true){KrtVJENrEn = false;}
      if(HRFTNyaOeA == true){HRFTNyaOeA = false;}
      if(WHCKMoXAYO == true){WHCKMoXAYO = false;}
      if(CWXhHGUTOX == true){CWXhHGUTOX = false;}
      if(FkPQEoWfzH == true){FkPQEoWfzH = false;}
      if(rnMpeCojIT == true){rnMpeCojIT = false;}
      if(gNSpkjtWMG == true){gNSpkjtWMG = false;}
      if(dGzGtlrlFX == true){dGzGtlrlFX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZGPRLKGSP
{ 
  void eipLygBLTQ()
  { 
      bool ljAkWusnmZ = false;
      bool kgxMDHYCGJ = false;
      bool KYMgTYneBU = false;
      bool PiTHUJtmoy = false;
      bool tVGljlGndb = false;
      bool JtOjqMWSQy = false;
      bool GOlRKCNort = false;
      bool MkMHPnSaxh = false;
      bool RAAZKUTiQH = false;
      bool lbWqqfinbh = false;
      bool YRwjOXgHUC = false;
      bool swVifGNMHo = false;
      bool hdXjHkOVPi = false;
      bool EeyOIAEQKl = false;
      bool mMONOpGmLk = false;
      bool SWgmAtsLcd = false;
      bool JLqkyOyGZe = false;
      bool CwBUBUPJVQ = false;
      bool ebKeQhyLOO = false;
      bool GrngcbVcPz = false;
      string NYEyRcLwHW;
      string VTFPqxVWYa;
      string TeIZJAqAVA;
      string FMxSJXMFtY;
      string EZBtSjltzm;
      string PZazjhPenR;
      string kKaGRJVmGT;
      string kPbzWsdNHZ;
      string OxBhkelxha;
      string HgRcmsztcI;
      string OzmfCzxacq;
      string ECXODmJsVl;
      string WYEfLDyzMc;
      string tijyKOKUfk;
      string hLUqWEJDZz;
      string jGYqlouGTy;
      string ByOzxUSYDn;
      string coMkELENJH;
      string ttYMsmKsMV;
      string TDAhiiwUsB;
      if(NYEyRcLwHW == OzmfCzxacq){ljAkWusnmZ = true;}
      else if(OzmfCzxacq == NYEyRcLwHW){YRwjOXgHUC = true;}
      if(VTFPqxVWYa == ECXODmJsVl){kgxMDHYCGJ = true;}
      else if(ECXODmJsVl == VTFPqxVWYa){swVifGNMHo = true;}
      if(TeIZJAqAVA == WYEfLDyzMc){KYMgTYneBU = true;}
      else if(WYEfLDyzMc == TeIZJAqAVA){hdXjHkOVPi = true;}
      if(FMxSJXMFtY == tijyKOKUfk){PiTHUJtmoy = true;}
      else if(tijyKOKUfk == FMxSJXMFtY){EeyOIAEQKl = true;}
      if(EZBtSjltzm == hLUqWEJDZz){tVGljlGndb = true;}
      else if(hLUqWEJDZz == EZBtSjltzm){mMONOpGmLk = true;}
      if(PZazjhPenR == jGYqlouGTy){JtOjqMWSQy = true;}
      else if(jGYqlouGTy == PZazjhPenR){SWgmAtsLcd = true;}
      if(kKaGRJVmGT == ByOzxUSYDn){GOlRKCNort = true;}
      else if(ByOzxUSYDn == kKaGRJVmGT){JLqkyOyGZe = true;}
      if(kPbzWsdNHZ == coMkELENJH){MkMHPnSaxh = true;}
      if(OxBhkelxha == ttYMsmKsMV){RAAZKUTiQH = true;}
      if(HgRcmsztcI == TDAhiiwUsB){lbWqqfinbh = true;}
      while(coMkELENJH == kPbzWsdNHZ){CwBUBUPJVQ = true;}
      while(ttYMsmKsMV == ttYMsmKsMV){ebKeQhyLOO = true;}
      while(TDAhiiwUsB == TDAhiiwUsB){GrngcbVcPz = true;}
      if(ljAkWusnmZ == true){ljAkWusnmZ = false;}
      if(kgxMDHYCGJ == true){kgxMDHYCGJ = false;}
      if(KYMgTYneBU == true){KYMgTYneBU = false;}
      if(PiTHUJtmoy == true){PiTHUJtmoy = false;}
      if(tVGljlGndb == true){tVGljlGndb = false;}
      if(JtOjqMWSQy == true){JtOjqMWSQy = false;}
      if(GOlRKCNort == true){GOlRKCNort = false;}
      if(MkMHPnSaxh == true){MkMHPnSaxh = false;}
      if(RAAZKUTiQH == true){RAAZKUTiQH = false;}
      if(lbWqqfinbh == true){lbWqqfinbh = false;}
      if(YRwjOXgHUC == true){YRwjOXgHUC = false;}
      if(swVifGNMHo == true){swVifGNMHo = false;}
      if(hdXjHkOVPi == true){hdXjHkOVPi = false;}
      if(EeyOIAEQKl == true){EeyOIAEQKl = false;}
      if(mMONOpGmLk == true){mMONOpGmLk = false;}
      if(SWgmAtsLcd == true){SWgmAtsLcd = false;}
      if(JLqkyOyGZe == true){JLqkyOyGZe = false;}
      if(CwBUBUPJVQ == true){CwBUBUPJVQ = false;}
      if(ebKeQhyLOO == true){ebKeQhyLOO = false;}
      if(GrngcbVcPz == true){GrngcbVcPz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZQOIAZDRUZ
{ 
  void XPTFOkZyNS()
  { 
      bool QwaIcgVjLc = false;
      bool pQjdUzMyei = false;
      bool SqKHmzKoMr = false;
      bool IRTdXabYXa = false;
      bool WKNEVLsmyk = false;
      bool kooQaYlSVd = false;
      bool VfXSTXxGGs = false;
      bool WnZDMIdGka = false;
      bool FXqaHTcCCy = false;
      bool oJDtFpmujy = false;
      bool OmgENwOkES = false;
      bool ufgtXxowLA = false;
      bool utDHENjfxV = false;
      bool UiVmMSplNK = false;
      bool EqyjDJbJVH = false;
      bool BpijDUiYAA = false;
      bool LinhxMJtgF = false;
      bool GDiAwDwTEu = false;
      bool laJpUezkjr = false;
      bool iRlMyUDPmp = false;
      string EcUALewKLg;
      string RCNEYDcdru;
      string IZYFfqoKXp;
      string DkAsbcCYVM;
      string HljNoVzPkG;
      string DJoqTeDOTU;
      string olmUcfBUbw;
      string ADHfmVpLPJ;
      string qZYRltwJYw;
      string ZnFBWVzOjJ;
      string UemoFABIDy;
      string oqzJcPMUhi;
      string jrueVMyGIQ;
      string WaaGoMljLl;
      string rmGaHhouYH;
      string JdfBYbjHSr;
      string CtzlaNQrUP;
      string dcIwpwlTXn;
      string XChBHrtYgM;
      string bdRTjymTAt;
      if(EcUALewKLg == UemoFABIDy){QwaIcgVjLc = true;}
      else if(UemoFABIDy == EcUALewKLg){OmgENwOkES = true;}
      if(RCNEYDcdru == oqzJcPMUhi){pQjdUzMyei = true;}
      else if(oqzJcPMUhi == RCNEYDcdru){ufgtXxowLA = true;}
      if(IZYFfqoKXp == jrueVMyGIQ){SqKHmzKoMr = true;}
      else if(jrueVMyGIQ == IZYFfqoKXp){utDHENjfxV = true;}
      if(DkAsbcCYVM == WaaGoMljLl){IRTdXabYXa = true;}
      else if(WaaGoMljLl == DkAsbcCYVM){UiVmMSplNK = true;}
      if(HljNoVzPkG == rmGaHhouYH){WKNEVLsmyk = true;}
      else if(rmGaHhouYH == HljNoVzPkG){EqyjDJbJVH = true;}
      if(DJoqTeDOTU == JdfBYbjHSr){kooQaYlSVd = true;}
      else if(JdfBYbjHSr == DJoqTeDOTU){BpijDUiYAA = true;}
      if(olmUcfBUbw == CtzlaNQrUP){VfXSTXxGGs = true;}
      else if(CtzlaNQrUP == olmUcfBUbw){LinhxMJtgF = true;}
      if(ADHfmVpLPJ == dcIwpwlTXn){WnZDMIdGka = true;}
      if(qZYRltwJYw == XChBHrtYgM){FXqaHTcCCy = true;}
      if(ZnFBWVzOjJ == bdRTjymTAt){oJDtFpmujy = true;}
      while(dcIwpwlTXn == ADHfmVpLPJ){GDiAwDwTEu = true;}
      while(XChBHrtYgM == XChBHrtYgM){laJpUezkjr = true;}
      while(bdRTjymTAt == bdRTjymTAt){iRlMyUDPmp = true;}
      if(QwaIcgVjLc == true){QwaIcgVjLc = false;}
      if(pQjdUzMyei == true){pQjdUzMyei = false;}
      if(SqKHmzKoMr == true){SqKHmzKoMr = false;}
      if(IRTdXabYXa == true){IRTdXabYXa = false;}
      if(WKNEVLsmyk == true){WKNEVLsmyk = false;}
      if(kooQaYlSVd == true){kooQaYlSVd = false;}
      if(VfXSTXxGGs == true){VfXSTXxGGs = false;}
      if(WnZDMIdGka == true){WnZDMIdGka = false;}
      if(FXqaHTcCCy == true){FXqaHTcCCy = false;}
      if(oJDtFpmujy == true){oJDtFpmujy = false;}
      if(OmgENwOkES == true){OmgENwOkES = false;}
      if(ufgtXxowLA == true){ufgtXxowLA = false;}
      if(utDHENjfxV == true){utDHENjfxV = false;}
      if(UiVmMSplNK == true){UiVmMSplNK = false;}
      if(EqyjDJbJVH == true){EqyjDJbJVH = false;}
      if(BpijDUiYAA == true){BpijDUiYAA = false;}
      if(LinhxMJtgF == true){LinhxMJtgF = false;}
      if(GDiAwDwTEu == true){GDiAwDwTEu = false;}
      if(laJpUezkjr == true){laJpUezkjr = false;}
      if(iRlMyUDPmp == true){iRlMyUDPmp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXRIYUMOBF
{ 
  void bPZxylAUYF()
  { 
      bool TiziJuDpZw = false;
      bool zXnrsyDKMQ = false;
      bool FlkHiNiNlR = false;
      bool AUgSEygIJY = false;
      bool gNZqDEQtnN = false;
      bool SMZVihyqzw = false;
      bool MpEHweqVnu = false;
      bool QuBnjqLsEe = false;
      bool wnYXzmtLiW = false;
      bool zpINLqJSuX = false;
      bool MuGswXLlkq = false;
      bool VEmUzXQfIJ = false;
      bool kflQualmbs = false;
      bool hsyfRBhfbb = false;
      bool aIZrBuCmOm = false;
      bool ZdKlmgJoxV = false;
      bool kYJqJbFHDx = false;
      bool pkEfhbFtPA = false;
      bool XyXnSEiMrj = false;
      bool qrhFqCzhhY = false;
      string OjEMDhKDGD;
      string MGaWVRUtSB;
      string TuENwAJhYG;
      string xEouRkixeW;
      string VgbXFBfGgz;
      string syYAWTfqQC;
      string XbdAFIRfEk;
      string hXPuflSfHt;
      string UDBZMzfoXy;
      string FrfbysDbSx;
      string jzBwQVhcTj;
      string AziVgUaEnF;
      string bbHFepqmxl;
      string iqNJKUBEIp;
      string RDUnyGIKuc;
      string RymNVHrwRa;
      string euehBJlYLL;
      string TVuxnYHTHY;
      string ggqTUjDznD;
      string cFmhLVXmlo;
      if(OjEMDhKDGD == jzBwQVhcTj){TiziJuDpZw = true;}
      else if(jzBwQVhcTj == OjEMDhKDGD){MuGswXLlkq = true;}
      if(MGaWVRUtSB == AziVgUaEnF){zXnrsyDKMQ = true;}
      else if(AziVgUaEnF == MGaWVRUtSB){VEmUzXQfIJ = true;}
      if(TuENwAJhYG == bbHFepqmxl){FlkHiNiNlR = true;}
      else if(bbHFepqmxl == TuENwAJhYG){kflQualmbs = true;}
      if(xEouRkixeW == iqNJKUBEIp){AUgSEygIJY = true;}
      else if(iqNJKUBEIp == xEouRkixeW){hsyfRBhfbb = true;}
      if(VgbXFBfGgz == RDUnyGIKuc){gNZqDEQtnN = true;}
      else if(RDUnyGIKuc == VgbXFBfGgz){aIZrBuCmOm = true;}
      if(syYAWTfqQC == RymNVHrwRa){SMZVihyqzw = true;}
      else if(RymNVHrwRa == syYAWTfqQC){ZdKlmgJoxV = true;}
      if(XbdAFIRfEk == euehBJlYLL){MpEHweqVnu = true;}
      else if(euehBJlYLL == XbdAFIRfEk){kYJqJbFHDx = true;}
      if(hXPuflSfHt == TVuxnYHTHY){QuBnjqLsEe = true;}
      if(UDBZMzfoXy == ggqTUjDznD){wnYXzmtLiW = true;}
      if(FrfbysDbSx == cFmhLVXmlo){zpINLqJSuX = true;}
      while(TVuxnYHTHY == hXPuflSfHt){pkEfhbFtPA = true;}
      while(ggqTUjDznD == ggqTUjDznD){XyXnSEiMrj = true;}
      while(cFmhLVXmlo == cFmhLVXmlo){qrhFqCzhhY = true;}
      if(TiziJuDpZw == true){TiziJuDpZw = false;}
      if(zXnrsyDKMQ == true){zXnrsyDKMQ = false;}
      if(FlkHiNiNlR == true){FlkHiNiNlR = false;}
      if(AUgSEygIJY == true){AUgSEygIJY = false;}
      if(gNZqDEQtnN == true){gNZqDEQtnN = false;}
      if(SMZVihyqzw == true){SMZVihyqzw = false;}
      if(MpEHweqVnu == true){MpEHweqVnu = false;}
      if(QuBnjqLsEe == true){QuBnjqLsEe = false;}
      if(wnYXzmtLiW == true){wnYXzmtLiW = false;}
      if(zpINLqJSuX == true){zpINLqJSuX = false;}
      if(MuGswXLlkq == true){MuGswXLlkq = false;}
      if(VEmUzXQfIJ == true){VEmUzXQfIJ = false;}
      if(kflQualmbs == true){kflQualmbs = false;}
      if(hsyfRBhfbb == true){hsyfRBhfbb = false;}
      if(aIZrBuCmOm == true){aIZrBuCmOm = false;}
      if(ZdKlmgJoxV == true){ZdKlmgJoxV = false;}
      if(kYJqJbFHDx == true){kYJqJbFHDx = false;}
      if(pkEfhbFtPA == true){pkEfhbFtPA = false;}
      if(XyXnSEiMrj == true){XyXnSEiMrj = false;}
      if(qrhFqCzhhY == true){qrhFqCzhhY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHQBYFSIYO
{ 
  void KQRQoOowVi()
  { 
      bool fVHfsiHRDi = false;
      bool nUdrWNbdEL = false;
      bool RthVJEstNa = false;
      bool zkOlpewrmP = false;
      bool rTXrKHFURg = false;
      bool VHEWFknlWo = false;
      bool oNEcjDGrBq = false;
      bool QipoSxWoLB = false;
      bool yYbgEqfqgF = false;
      bool qKVyZePuIH = false;
      bool BNTZPmQPDH = false;
      bool OyZUpQkXXr = false;
      bool WOKwAFMrOn = false;
      bool hagEAkEBQR = false;
      bool ZPmZprjBHJ = false;
      bool srWPjlCXYJ = false;
      bool ZYBPYmQVTF = false;
      bool LiGGSHakFI = false;
      bool ULjFtpDRUO = false;
      bool hgcGqAOXAD = false;
      string OmzklAAJKk;
      string EJNrEGMeHf;
      string goLxOztDsa;
      string ZCCaQDmAmz;
      string UDfKBtuznZ;
      string MjgBeYaBVl;
      string GxQjLBGlbB;
      string TMrHLcIBuU;
      string EtOTNoUBuq;
      string bldAsXmwyA;
      string mIXmGAqYpB;
      string QZFBhLhwVW;
      string fFpjYhhqOm;
      string pMDuguWaNN;
      string xwLsaCfcSh;
      string opZbThRmOY;
      string SAKCLDVJUl;
      string nGiIYjtwJW;
      string BEYgyzlaby;
      string cjMotxkIhW;
      if(OmzklAAJKk == mIXmGAqYpB){fVHfsiHRDi = true;}
      else if(mIXmGAqYpB == OmzklAAJKk){BNTZPmQPDH = true;}
      if(EJNrEGMeHf == QZFBhLhwVW){nUdrWNbdEL = true;}
      else if(QZFBhLhwVW == EJNrEGMeHf){OyZUpQkXXr = true;}
      if(goLxOztDsa == fFpjYhhqOm){RthVJEstNa = true;}
      else if(fFpjYhhqOm == goLxOztDsa){WOKwAFMrOn = true;}
      if(ZCCaQDmAmz == pMDuguWaNN){zkOlpewrmP = true;}
      else if(pMDuguWaNN == ZCCaQDmAmz){hagEAkEBQR = true;}
      if(UDfKBtuznZ == xwLsaCfcSh){rTXrKHFURg = true;}
      else if(xwLsaCfcSh == UDfKBtuznZ){ZPmZprjBHJ = true;}
      if(MjgBeYaBVl == opZbThRmOY){VHEWFknlWo = true;}
      else if(opZbThRmOY == MjgBeYaBVl){srWPjlCXYJ = true;}
      if(GxQjLBGlbB == SAKCLDVJUl){oNEcjDGrBq = true;}
      else if(SAKCLDVJUl == GxQjLBGlbB){ZYBPYmQVTF = true;}
      if(TMrHLcIBuU == nGiIYjtwJW){QipoSxWoLB = true;}
      if(EtOTNoUBuq == BEYgyzlaby){yYbgEqfqgF = true;}
      if(bldAsXmwyA == cjMotxkIhW){qKVyZePuIH = true;}
      while(nGiIYjtwJW == TMrHLcIBuU){LiGGSHakFI = true;}
      while(BEYgyzlaby == BEYgyzlaby){ULjFtpDRUO = true;}
      while(cjMotxkIhW == cjMotxkIhW){hgcGqAOXAD = true;}
      if(fVHfsiHRDi == true){fVHfsiHRDi = false;}
      if(nUdrWNbdEL == true){nUdrWNbdEL = false;}
      if(RthVJEstNa == true){RthVJEstNa = false;}
      if(zkOlpewrmP == true){zkOlpewrmP = false;}
      if(rTXrKHFURg == true){rTXrKHFURg = false;}
      if(VHEWFknlWo == true){VHEWFknlWo = false;}
      if(oNEcjDGrBq == true){oNEcjDGrBq = false;}
      if(QipoSxWoLB == true){QipoSxWoLB = false;}
      if(yYbgEqfqgF == true){yYbgEqfqgF = false;}
      if(qKVyZePuIH == true){qKVyZePuIH = false;}
      if(BNTZPmQPDH == true){BNTZPmQPDH = false;}
      if(OyZUpQkXXr == true){OyZUpQkXXr = false;}
      if(WOKwAFMrOn == true){WOKwAFMrOn = false;}
      if(hagEAkEBQR == true){hagEAkEBQR = false;}
      if(ZPmZprjBHJ == true){ZPmZprjBHJ = false;}
      if(srWPjlCXYJ == true){srWPjlCXYJ = false;}
      if(ZYBPYmQVTF == true){ZYBPYmQVTF = false;}
      if(LiGGSHakFI == true){LiGGSHakFI = false;}
      if(ULjFtpDRUO == true){ULjFtpDRUO = false;}
      if(hgcGqAOXAD == true){hgcGqAOXAD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFVIDHKIPQ
{ 
  void kigutnCHZR()
  { 
      bool PEmEPpQawn = false;
      bool yNersHyMlk = false;
      bool UIEoCnJwet = false;
      bool ihjCibpsLE = false;
      bool WJnrShCKBo = false;
      bool NmRgNGAxCb = false;
      bool fTuCEQdcIQ = false;
      bool QFAhOKUMVT = false;
      bool lzupfuPCnc = false;
      bool bspjXCNlmB = false;
      bool DZBjXImjSD = false;
      bool kmahogYFVI = false;
      bool BanfoXOPJL = false;
      bool whYTQMxKRW = false;
      bool IfjkqnSIuq = false;
      bool dIPdAbkUuA = false;
      bool tWZHGCNGRc = false;
      bool jOnzAUqCnA = false;
      bool FFUSgnSuSn = false;
      bool abORckFceo = false;
      string LZtVVqlkam;
      string giJmULBKiM;
      string OOpIBojmIa;
      string RRxBeYNYuN;
      string HxMlKrRxtr;
      string kMYinwjkTg;
      string HzbzUPkHIw;
      string xcOVFRBDyJ;
      string WmrPpFrONi;
      string nbENGIUNQt;
      string GKoyuIxDdV;
      string tfmKKTGMJO;
      string XWtYHUXAOw;
      string wnlDCMxtUg;
      string InkrnIntDl;
      string CIDCWjPPqZ;
      string kwngZFsjHy;
      string VMqbGikCky;
      string fcxbtnkjfR;
      string whCtwMzDSh;
      if(LZtVVqlkam == GKoyuIxDdV){PEmEPpQawn = true;}
      else if(GKoyuIxDdV == LZtVVqlkam){DZBjXImjSD = true;}
      if(giJmULBKiM == tfmKKTGMJO){yNersHyMlk = true;}
      else if(tfmKKTGMJO == giJmULBKiM){kmahogYFVI = true;}
      if(OOpIBojmIa == XWtYHUXAOw){UIEoCnJwet = true;}
      else if(XWtYHUXAOw == OOpIBojmIa){BanfoXOPJL = true;}
      if(RRxBeYNYuN == wnlDCMxtUg){ihjCibpsLE = true;}
      else if(wnlDCMxtUg == RRxBeYNYuN){whYTQMxKRW = true;}
      if(HxMlKrRxtr == InkrnIntDl){WJnrShCKBo = true;}
      else if(InkrnIntDl == HxMlKrRxtr){IfjkqnSIuq = true;}
      if(kMYinwjkTg == CIDCWjPPqZ){NmRgNGAxCb = true;}
      else if(CIDCWjPPqZ == kMYinwjkTg){dIPdAbkUuA = true;}
      if(HzbzUPkHIw == kwngZFsjHy){fTuCEQdcIQ = true;}
      else if(kwngZFsjHy == HzbzUPkHIw){tWZHGCNGRc = true;}
      if(xcOVFRBDyJ == VMqbGikCky){QFAhOKUMVT = true;}
      if(WmrPpFrONi == fcxbtnkjfR){lzupfuPCnc = true;}
      if(nbENGIUNQt == whCtwMzDSh){bspjXCNlmB = true;}
      while(VMqbGikCky == xcOVFRBDyJ){jOnzAUqCnA = true;}
      while(fcxbtnkjfR == fcxbtnkjfR){FFUSgnSuSn = true;}
      while(whCtwMzDSh == whCtwMzDSh){abORckFceo = true;}
      if(PEmEPpQawn == true){PEmEPpQawn = false;}
      if(yNersHyMlk == true){yNersHyMlk = false;}
      if(UIEoCnJwet == true){UIEoCnJwet = false;}
      if(ihjCibpsLE == true){ihjCibpsLE = false;}
      if(WJnrShCKBo == true){WJnrShCKBo = false;}
      if(NmRgNGAxCb == true){NmRgNGAxCb = false;}
      if(fTuCEQdcIQ == true){fTuCEQdcIQ = false;}
      if(QFAhOKUMVT == true){QFAhOKUMVT = false;}
      if(lzupfuPCnc == true){lzupfuPCnc = false;}
      if(bspjXCNlmB == true){bspjXCNlmB = false;}
      if(DZBjXImjSD == true){DZBjXImjSD = false;}
      if(kmahogYFVI == true){kmahogYFVI = false;}
      if(BanfoXOPJL == true){BanfoXOPJL = false;}
      if(whYTQMxKRW == true){whYTQMxKRW = false;}
      if(IfjkqnSIuq == true){IfjkqnSIuq = false;}
      if(dIPdAbkUuA == true){dIPdAbkUuA = false;}
      if(tWZHGCNGRc == true){tWZHGCNGRc = false;}
      if(jOnzAUqCnA == true){jOnzAUqCnA = false;}
      if(FFUSgnSuSn == true){FFUSgnSuSn = false;}
      if(abORckFceo == true){abORckFceo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELKXIOLYLY
{ 
  void EJCedRARST()
  { 
      bool tefCDxKOEf = false;
      bool ygxKPopfuL = false;
      bool IVUPXENmQf = false;
      bool OulMmZYUnX = false;
      bool hujENTlRyL = false;
      bool gqDEEYJQdz = false;
      bool iWxYRCukXp = false;
      bool PVrWdMkQBD = false;
      bool SwoFyXqgHO = false;
      bool PIpooKyLlK = false;
      bool YAtHwLygaq = false;
      bool msOZfmhqZt = false;
      bool LNdJZGeDhS = false;
      bool OZeqeRCgJm = false;
      bool YKGPaWtQIB = false;
      bool cGkryLWjhp = false;
      bool fuyHcMOWuN = false;
      bool kAhmUBGNhD = false;
      bool LOtfoIolrT = false;
      bool uRzSHdLymN = false;
      string dYuGCdqZQW;
      string RjEXNoYQkY;
      string jmXkRCBdrE;
      string ngfyeNEaiO;
      string NfEeiIMTdw;
      string ErdmQqAKnz;
      string bMgMijEFrz;
      string jygVLEhrBJ;
      string phAuAuDrhn;
      string MsljlByruz;
      string EGaeMFKHbL;
      string IHIeItMkLm;
      string gLXElpLxjK;
      string GpxCEjGVit;
      string juQVeEkGar;
      string nMfHRsiWrV;
      string tMXQFSKFaY;
      string nqBRDktCYg;
      string FFWqVsJojL;
      string AicNAWWzQM;
      if(dYuGCdqZQW == EGaeMFKHbL){tefCDxKOEf = true;}
      else if(EGaeMFKHbL == dYuGCdqZQW){YAtHwLygaq = true;}
      if(RjEXNoYQkY == IHIeItMkLm){ygxKPopfuL = true;}
      else if(IHIeItMkLm == RjEXNoYQkY){msOZfmhqZt = true;}
      if(jmXkRCBdrE == gLXElpLxjK){IVUPXENmQf = true;}
      else if(gLXElpLxjK == jmXkRCBdrE){LNdJZGeDhS = true;}
      if(ngfyeNEaiO == GpxCEjGVit){OulMmZYUnX = true;}
      else if(GpxCEjGVit == ngfyeNEaiO){OZeqeRCgJm = true;}
      if(NfEeiIMTdw == juQVeEkGar){hujENTlRyL = true;}
      else if(juQVeEkGar == NfEeiIMTdw){YKGPaWtQIB = true;}
      if(ErdmQqAKnz == nMfHRsiWrV){gqDEEYJQdz = true;}
      else if(nMfHRsiWrV == ErdmQqAKnz){cGkryLWjhp = true;}
      if(bMgMijEFrz == tMXQFSKFaY){iWxYRCukXp = true;}
      else if(tMXQFSKFaY == bMgMijEFrz){fuyHcMOWuN = true;}
      if(jygVLEhrBJ == nqBRDktCYg){PVrWdMkQBD = true;}
      if(phAuAuDrhn == FFWqVsJojL){SwoFyXqgHO = true;}
      if(MsljlByruz == AicNAWWzQM){PIpooKyLlK = true;}
      while(nqBRDktCYg == jygVLEhrBJ){kAhmUBGNhD = true;}
      while(FFWqVsJojL == FFWqVsJojL){LOtfoIolrT = true;}
      while(AicNAWWzQM == AicNAWWzQM){uRzSHdLymN = true;}
      if(tefCDxKOEf == true){tefCDxKOEf = false;}
      if(ygxKPopfuL == true){ygxKPopfuL = false;}
      if(IVUPXENmQf == true){IVUPXENmQf = false;}
      if(OulMmZYUnX == true){OulMmZYUnX = false;}
      if(hujENTlRyL == true){hujENTlRyL = false;}
      if(gqDEEYJQdz == true){gqDEEYJQdz = false;}
      if(iWxYRCukXp == true){iWxYRCukXp = false;}
      if(PVrWdMkQBD == true){PVrWdMkQBD = false;}
      if(SwoFyXqgHO == true){SwoFyXqgHO = false;}
      if(PIpooKyLlK == true){PIpooKyLlK = false;}
      if(YAtHwLygaq == true){YAtHwLygaq = false;}
      if(msOZfmhqZt == true){msOZfmhqZt = false;}
      if(LNdJZGeDhS == true){LNdJZGeDhS = false;}
      if(OZeqeRCgJm == true){OZeqeRCgJm = false;}
      if(YKGPaWtQIB == true){YKGPaWtQIB = false;}
      if(cGkryLWjhp == true){cGkryLWjhp = false;}
      if(fuyHcMOWuN == true){fuyHcMOWuN = false;}
      if(kAhmUBGNhD == true){kAhmUBGNhD = false;}
      if(LOtfoIolrT == true){LOtfoIolrT = false;}
      if(uRzSHdLymN == true){uRzSHdLymN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRBBUSOZLD
{ 
  void RKrZAeyaMi()
  { 
      bool sCpdDbIkbR = false;
      bool BknleeaPnL = false;
      bool yQmFyViprT = false;
      bool McWIjbdufU = false;
      bool ZTmDUOSadX = false;
      bool ZjkCTcPjeh = false;
      bool sRsIEYOeBD = false;
      bool BfiSlediki = false;
      bool CHMUscqUoH = false;
      bool MsPybHadzw = false;
      bool AnYaVtARQn = false;
      bool zgzwekEXPb = false;
      bool gsotpHQkqd = false;
      bool EzinhOhlyz = false;
      bool bYEAHftSTq = false;
      bool DCOXOHyejO = false;
      bool cPaljzxKOQ = false;
      bool CSYPAIonlK = false;
      bool NyRzZBkLZa = false;
      bool PDCjVLxRQH = false;
      string quMgjqISSa;
      string zPZgJeWBGi;
      string hiXLleIleg;
      string BXlqVnUPCM;
      string SPQrTtuYoK;
      string szIVBIWAtF;
      string hVnlYbdhLU;
      string JHysQRRerq;
      string jjxTnCOPpN;
      string QTUxdwbeTq;
      string QNNTAkAOFi;
      string pqICUyYTyV;
      string MNqyDplAPT;
      string plLAZWVcTC;
      string BzKGWYKRbf;
      string WIgxeDVPPK;
      string zzzksEfIby;
      string buzuUMCjbd;
      string eTYjwhFOVW;
      string AGMJCBAZNS;
      if(quMgjqISSa == QNNTAkAOFi){sCpdDbIkbR = true;}
      else if(QNNTAkAOFi == quMgjqISSa){AnYaVtARQn = true;}
      if(zPZgJeWBGi == pqICUyYTyV){BknleeaPnL = true;}
      else if(pqICUyYTyV == zPZgJeWBGi){zgzwekEXPb = true;}
      if(hiXLleIleg == MNqyDplAPT){yQmFyViprT = true;}
      else if(MNqyDplAPT == hiXLleIleg){gsotpHQkqd = true;}
      if(BXlqVnUPCM == plLAZWVcTC){McWIjbdufU = true;}
      else if(plLAZWVcTC == BXlqVnUPCM){EzinhOhlyz = true;}
      if(SPQrTtuYoK == BzKGWYKRbf){ZTmDUOSadX = true;}
      else if(BzKGWYKRbf == SPQrTtuYoK){bYEAHftSTq = true;}
      if(szIVBIWAtF == WIgxeDVPPK){ZjkCTcPjeh = true;}
      else if(WIgxeDVPPK == szIVBIWAtF){DCOXOHyejO = true;}
      if(hVnlYbdhLU == zzzksEfIby){sRsIEYOeBD = true;}
      else if(zzzksEfIby == hVnlYbdhLU){cPaljzxKOQ = true;}
      if(JHysQRRerq == buzuUMCjbd){BfiSlediki = true;}
      if(jjxTnCOPpN == eTYjwhFOVW){CHMUscqUoH = true;}
      if(QTUxdwbeTq == AGMJCBAZNS){MsPybHadzw = true;}
      while(buzuUMCjbd == JHysQRRerq){CSYPAIonlK = true;}
      while(eTYjwhFOVW == eTYjwhFOVW){NyRzZBkLZa = true;}
      while(AGMJCBAZNS == AGMJCBAZNS){PDCjVLxRQH = true;}
      if(sCpdDbIkbR == true){sCpdDbIkbR = false;}
      if(BknleeaPnL == true){BknleeaPnL = false;}
      if(yQmFyViprT == true){yQmFyViprT = false;}
      if(McWIjbdufU == true){McWIjbdufU = false;}
      if(ZTmDUOSadX == true){ZTmDUOSadX = false;}
      if(ZjkCTcPjeh == true){ZjkCTcPjeh = false;}
      if(sRsIEYOeBD == true){sRsIEYOeBD = false;}
      if(BfiSlediki == true){BfiSlediki = false;}
      if(CHMUscqUoH == true){CHMUscqUoH = false;}
      if(MsPybHadzw == true){MsPybHadzw = false;}
      if(AnYaVtARQn == true){AnYaVtARQn = false;}
      if(zgzwekEXPb == true){zgzwekEXPb = false;}
      if(gsotpHQkqd == true){gsotpHQkqd = false;}
      if(EzinhOhlyz == true){EzinhOhlyz = false;}
      if(bYEAHftSTq == true){bYEAHftSTq = false;}
      if(DCOXOHyejO == true){DCOXOHyejO = false;}
      if(cPaljzxKOQ == true){cPaljzxKOQ = false;}
      if(CSYPAIonlK == true){CSYPAIonlK = false;}
      if(NyRzZBkLZa == true){NyRzZBkLZa = false;}
      if(PDCjVLxRQH == true){PDCjVLxRQH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILDDXTPZAT
{ 
  void GtLLKSWHYX()
  { 
      bool gyQYKBBXhZ = false;
      bool ZTtuPgnChJ = false;
      bool sjBKbNalMq = false;
      bool odYjTVoGJx = false;
      bool EVWBUhQHTw = false;
      bool nOEQDxwFxw = false;
      bool ZPLpjwuKat = false;
      bool qgskEWMAps = false;
      bool xSRQCaZHfW = false;
      bool YjJMWoKgQY = false;
      bool mFgZFHVSLg = false;
      bool jwPEzGxunJ = false;
      bool VneEUHWfNP = false;
      bool LfjRGqlrLt = false;
      bool FGuylcTFNQ = false;
      bool qOsGCyZcEx = false;
      bool joFwUELxyH = false;
      bool UFjsEPrfRr = false;
      bool mRRxXxmdPH = false;
      bool RJnNJPBzdh = false;
      string CcMReIXTZK;
      string iwezbWPVht;
      string meIBJCSagn;
      string sgeLClTWgj;
      string FzEjYtZnIh;
      string IrVzeWUKIc;
      string owmkRCQTwo;
      string DrnxnnaYbP;
      string bdSyfAKfff;
      string RIOEtJLSRW;
      string cGqTePEYLq;
      string uuhrALdoFQ;
      string qkmQWtcjCd;
      string bIGFlVlzTP;
      string wlTojVaWDi;
      string fWNBeqSawj;
      string mTVgOmobFe;
      string YdVoTFRyfB;
      string TGfTyFtEat;
      string CKDjccQmZw;
      if(CcMReIXTZK == cGqTePEYLq){gyQYKBBXhZ = true;}
      else if(cGqTePEYLq == CcMReIXTZK){mFgZFHVSLg = true;}
      if(iwezbWPVht == uuhrALdoFQ){ZTtuPgnChJ = true;}
      else if(uuhrALdoFQ == iwezbWPVht){jwPEzGxunJ = true;}
      if(meIBJCSagn == qkmQWtcjCd){sjBKbNalMq = true;}
      else if(qkmQWtcjCd == meIBJCSagn){VneEUHWfNP = true;}
      if(sgeLClTWgj == bIGFlVlzTP){odYjTVoGJx = true;}
      else if(bIGFlVlzTP == sgeLClTWgj){LfjRGqlrLt = true;}
      if(FzEjYtZnIh == wlTojVaWDi){EVWBUhQHTw = true;}
      else if(wlTojVaWDi == FzEjYtZnIh){FGuylcTFNQ = true;}
      if(IrVzeWUKIc == fWNBeqSawj){nOEQDxwFxw = true;}
      else if(fWNBeqSawj == IrVzeWUKIc){qOsGCyZcEx = true;}
      if(owmkRCQTwo == mTVgOmobFe){ZPLpjwuKat = true;}
      else if(mTVgOmobFe == owmkRCQTwo){joFwUELxyH = true;}
      if(DrnxnnaYbP == YdVoTFRyfB){qgskEWMAps = true;}
      if(bdSyfAKfff == TGfTyFtEat){xSRQCaZHfW = true;}
      if(RIOEtJLSRW == CKDjccQmZw){YjJMWoKgQY = true;}
      while(YdVoTFRyfB == DrnxnnaYbP){UFjsEPrfRr = true;}
      while(TGfTyFtEat == TGfTyFtEat){mRRxXxmdPH = true;}
      while(CKDjccQmZw == CKDjccQmZw){RJnNJPBzdh = true;}
      if(gyQYKBBXhZ == true){gyQYKBBXhZ = false;}
      if(ZTtuPgnChJ == true){ZTtuPgnChJ = false;}
      if(sjBKbNalMq == true){sjBKbNalMq = false;}
      if(odYjTVoGJx == true){odYjTVoGJx = false;}
      if(EVWBUhQHTw == true){EVWBUhQHTw = false;}
      if(nOEQDxwFxw == true){nOEQDxwFxw = false;}
      if(ZPLpjwuKat == true){ZPLpjwuKat = false;}
      if(qgskEWMAps == true){qgskEWMAps = false;}
      if(xSRQCaZHfW == true){xSRQCaZHfW = false;}
      if(YjJMWoKgQY == true){YjJMWoKgQY = false;}
      if(mFgZFHVSLg == true){mFgZFHVSLg = false;}
      if(jwPEzGxunJ == true){jwPEzGxunJ = false;}
      if(VneEUHWfNP == true){VneEUHWfNP = false;}
      if(LfjRGqlrLt == true){LfjRGqlrLt = false;}
      if(FGuylcTFNQ == true){FGuylcTFNQ = false;}
      if(qOsGCyZcEx == true){qOsGCyZcEx = false;}
      if(joFwUELxyH == true){joFwUELxyH = false;}
      if(UFjsEPrfRr == true){UFjsEPrfRr = false;}
      if(mRRxXxmdPH == true){mRRxXxmdPH = false;}
      if(RJnNJPBzdh == true){RJnNJPBzdh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSXSAUKSAI
{ 
  void AfIwGAaMYP()
  { 
      bool jJFzfaeohF = false;
      bool lQiQKRmHuL = false;
      bool YQNDgkaqbi = false;
      bool oDMPKWLfOr = false;
      bool ADSUpuSToh = false;
      bool LUjIYSwCSt = false;
      bool AnMzQhDSFm = false;
      bool FGrCLVyrNl = false;
      bool SHBsXTTEpq = false;
      bool ZJNUrMpTEH = false;
      bool rzNBbEcgxD = false;
      bool UDogbrlSaw = false;
      bool OzcNNurXKz = false;
      bool ednFtSsARS = false;
      bool qlGlWVUgsz = false;
      bool ZWsHsrWzng = false;
      bool MFWyXpPilI = false;
      bool zkBHFcrpqq = false;
      bool ZLdKYIkgLB = false;
      bool wtMjGkOINf = false;
      string RlwaDfUxKo;
      string ecycALLejF;
      string DCPnwtUFBa;
      string cihAHLttGQ;
      string HzNeRwqwym;
      string EQkSwPWIdI;
      string LOwiMutyUn;
      string QRXTyEnkVA;
      string DYGNWLxPDq;
      string okPyFsDdRW;
      string BraKWlsRTr;
      string blmdElHhMA;
      string yetdyeCZOF;
      string AKSzyKywqj;
      string SfuLPDyksT;
      string lVRQXVywLq;
      string jTCOqRSnfs;
      string mKpbhRjhNu;
      string gRfuTerBab;
      string MBjzAycfUy;
      if(RlwaDfUxKo == BraKWlsRTr){jJFzfaeohF = true;}
      else if(BraKWlsRTr == RlwaDfUxKo){rzNBbEcgxD = true;}
      if(ecycALLejF == blmdElHhMA){lQiQKRmHuL = true;}
      else if(blmdElHhMA == ecycALLejF){UDogbrlSaw = true;}
      if(DCPnwtUFBa == yetdyeCZOF){YQNDgkaqbi = true;}
      else if(yetdyeCZOF == DCPnwtUFBa){OzcNNurXKz = true;}
      if(cihAHLttGQ == AKSzyKywqj){oDMPKWLfOr = true;}
      else if(AKSzyKywqj == cihAHLttGQ){ednFtSsARS = true;}
      if(HzNeRwqwym == SfuLPDyksT){ADSUpuSToh = true;}
      else if(SfuLPDyksT == HzNeRwqwym){qlGlWVUgsz = true;}
      if(EQkSwPWIdI == lVRQXVywLq){LUjIYSwCSt = true;}
      else if(lVRQXVywLq == EQkSwPWIdI){ZWsHsrWzng = true;}
      if(LOwiMutyUn == jTCOqRSnfs){AnMzQhDSFm = true;}
      else if(jTCOqRSnfs == LOwiMutyUn){MFWyXpPilI = true;}
      if(QRXTyEnkVA == mKpbhRjhNu){FGrCLVyrNl = true;}
      if(DYGNWLxPDq == gRfuTerBab){SHBsXTTEpq = true;}
      if(okPyFsDdRW == MBjzAycfUy){ZJNUrMpTEH = true;}
      while(mKpbhRjhNu == QRXTyEnkVA){zkBHFcrpqq = true;}
      while(gRfuTerBab == gRfuTerBab){ZLdKYIkgLB = true;}
      while(MBjzAycfUy == MBjzAycfUy){wtMjGkOINf = true;}
      if(jJFzfaeohF == true){jJFzfaeohF = false;}
      if(lQiQKRmHuL == true){lQiQKRmHuL = false;}
      if(YQNDgkaqbi == true){YQNDgkaqbi = false;}
      if(oDMPKWLfOr == true){oDMPKWLfOr = false;}
      if(ADSUpuSToh == true){ADSUpuSToh = false;}
      if(LUjIYSwCSt == true){LUjIYSwCSt = false;}
      if(AnMzQhDSFm == true){AnMzQhDSFm = false;}
      if(FGrCLVyrNl == true){FGrCLVyrNl = false;}
      if(SHBsXTTEpq == true){SHBsXTTEpq = false;}
      if(ZJNUrMpTEH == true){ZJNUrMpTEH = false;}
      if(rzNBbEcgxD == true){rzNBbEcgxD = false;}
      if(UDogbrlSaw == true){UDogbrlSaw = false;}
      if(OzcNNurXKz == true){OzcNNurXKz = false;}
      if(ednFtSsARS == true){ednFtSsARS = false;}
      if(qlGlWVUgsz == true){qlGlWVUgsz = false;}
      if(ZWsHsrWzng == true){ZWsHsrWzng = false;}
      if(MFWyXpPilI == true){MFWyXpPilI = false;}
      if(zkBHFcrpqq == true){zkBHFcrpqq = false;}
      if(ZLdKYIkgLB == true){ZLdKYIkgLB = false;}
      if(wtMjGkOINf == true){wtMjGkOINf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNIPDOSIEW
{ 
  void FWMewmUPoo()
  { 
      bool ndXPGdteqk = false;
      bool QfYhqgHYbn = false;
      bool fKqAETzVTR = false;
      bool KiJOGeQIBQ = false;
      bool oihJNYHKqx = false;
      bool XUihydlXKm = false;
      bool eXKZZhVKbM = false;
      bool PzWLzwchlf = false;
      bool MneWspAbQc = false;
      bool rsxOkQXHjf = false;
      bool CwiehYxWiB = false;
      bool AEleZqsnfj = false;
      bool httzTWBIZi = false;
      bool YUyFdPEznU = false;
      bool rcrObnGRos = false;
      bool WjbzyHCiKL = false;
      bool WnxAceGfBJ = false;
      bool lszKqECfWf = false;
      bool PjTgLnryHV = false;
      bool NVocyDfqkx = false;
      string UBHbBpqzPP;
      string AUJzNdyjVc;
      string QMyeYUCGyA;
      string TwShTYQdiw;
      string XqrpYqOQln;
      string jeXtgHDcDg;
      string mjAPwEBaeo;
      string NTAZFZUHFg;
      string FlUKQoYXAL;
      string UnaCImpctU;
      string omlxZPdxoG;
      string mwWWbAPpzG;
      string edaSTZsyQR;
      string irMjqRzWjA;
      string KaisYYQDZI;
      string WAdmoLMSdA;
      string VfgWWtjleJ;
      string BrFywEtgsu;
      string IoXIuiOYte;
      string EgsidesLWe;
      if(UBHbBpqzPP == omlxZPdxoG){ndXPGdteqk = true;}
      else if(omlxZPdxoG == UBHbBpqzPP){CwiehYxWiB = true;}
      if(AUJzNdyjVc == mwWWbAPpzG){QfYhqgHYbn = true;}
      else if(mwWWbAPpzG == AUJzNdyjVc){AEleZqsnfj = true;}
      if(QMyeYUCGyA == edaSTZsyQR){fKqAETzVTR = true;}
      else if(edaSTZsyQR == QMyeYUCGyA){httzTWBIZi = true;}
      if(TwShTYQdiw == irMjqRzWjA){KiJOGeQIBQ = true;}
      else if(irMjqRzWjA == TwShTYQdiw){YUyFdPEznU = true;}
      if(XqrpYqOQln == KaisYYQDZI){oihJNYHKqx = true;}
      else if(KaisYYQDZI == XqrpYqOQln){rcrObnGRos = true;}
      if(jeXtgHDcDg == WAdmoLMSdA){XUihydlXKm = true;}
      else if(WAdmoLMSdA == jeXtgHDcDg){WjbzyHCiKL = true;}
      if(mjAPwEBaeo == VfgWWtjleJ){eXKZZhVKbM = true;}
      else if(VfgWWtjleJ == mjAPwEBaeo){WnxAceGfBJ = true;}
      if(NTAZFZUHFg == BrFywEtgsu){PzWLzwchlf = true;}
      if(FlUKQoYXAL == IoXIuiOYte){MneWspAbQc = true;}
      if(UnaCImpctU == EgsidesLWe){rsxOkQXHjf = true;}
      while(BrFywEtgsu == NTAZFZUHFg){lszKqECfWf = true;}
      while(IoXIuiOYte == IoXIuiOYte){PjTgLnryHV = true;}
      while(EgsidesLWe == EgsidesLWe){NVocyDfqkx = true;}
      if(ndXPGdteqk == true){ndXPGdteqk = false;}
      if(QfYhqgHYbn == true){QfYhqgHYbn = false;}
      if(fKqAETzVTR == true){fKqAETzVTR = false;}
      if(KiJOGeQIBQ == true){KiJOGeQIBQ = false;}
      if(oihJNYHKqx == true){oihJNYHKqx = false;}
      if(XUihydlXKm == true){XUihydlXKm = false;}
      if(eXKZZhVKbM == true){eXKZZhVKbM = false;}
      if(PzWLzwchlf == true){PzWLzwchlf = false;}
      if(MneWspAbQc == true){MneWspAbQc = false;}
      if(rsxOkQXHjf == true){rsxOkQXHjf = false;}
      if(CwiehYxWiB == true){CwiehYxWiB = false;}
      if(AEleZqsnfj == true){AEleZqsnfj = false;}
      if(httzTWBIZi == true){httzTWBIZi = false;}
      if(YUyFdPEznU == true){YUyFdPEznU = false;}
      if(rcrObnGRos == true){rcrObnGRos = false;}
      if(WjbzyHCiKL == true){WjbzyHCiKL = false;}
      if(WnxAceGfBJ == true){WnxAceGfBJ = false;}
      if(lszKqECfWf == true){lszKqECfWf = false;}
      if(PjTgLnryHV == true){PjTgLnryHV = false;}
      if(NVocyDfqkx == true){NVocyDfqkx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWWIBPZREO
{ 
  void PpZUXIOjnZ()
  { 
      bool wPxYRQhqpA = false;
      bool pQYRUrhgCD = false;
      bool baONVYXLyA = false;
      bool HDPPdCzrWr = false;
      bool FxkMhNnqQO = false;
      bool FNdJMUAjDs = false;
      bool sWspslBImR = false;
      bool soJJyepCfH = false;
      bool jguitsZFDJ = false;
      bool BPodziEuTu = false;
      bool LeEyUPETLg = false;
      bool eyDuIMaJuz = false;
      bool MuFdQdAfKO = false;
      bool auikuFcxOd = false;
      bool oGtVdDLsUm = false;
      bool HtzTiQZZgp = false;
      bool PYIwGjPSzD = false;
      bool jdtRKGBizM = false;
      bool SGKXHfuOCe = false;
      bool eCPXOQxyPt = false;
      string ikmQpzQAzP;
      string WFqKFGsIPU;
      string LzTJjUpQKg;
      string KVTtqYNxTp;
      string gqQJWmWIyo;
      string QfoHejRdfV;
      string JApREAlwSg;
      string swoZnTiJlx;
      string ygSUQdgLPH;
      string HiQxffAyEV;
      string AZpRwTqPTK;
      string BHqhXchVBa;
      string TagLZJeqsH;
      string SjFPxXqAXw;
      string mRqEGzqiZD;
      string yewdCYsdrm;
      string ozWLqQCbkA;
      string kgxFmCibFZ;
      string RwRoJnnaMX;
      string dMIkHmufMo;
      if(ikmQpzQAzP == AZpRwTqPTK){wPxYRQhqpA = true;}
      else if(AZpRwTqPTK == ikmQpzQAzP){LeEyUPETLg = true;}
      if(WFqKFGsIPU == BHqhXchVBa){pQYRUrhgCD = true;}
      else if(BHqhXchVBa == WFqKFGsIPU){eyDuIMaJuz = true;}
      if(LzTJjUpQKg == TagLZJeqsH){baONVYXLyA = true;}
      else if(TagLZJeqsH == LzTJjUpQKg){MuFdQdAfKO = true;}
      if(KVTtqYNxTp == SjFPxXqAXw){HDPPdCzrWr = true;}
      else if(SjFPxXqAXw == KVTtqYNxTp){auikuFcxOd = true;}
      if(gqQJWmWIyo == mRqEGzqiZD){FxkMhNnqQO = true;}
      else if(mRqEGzqiZD == gqQJWmWIyo){oGtVdDLsUm = true;}
      if(QfoHejRdfV == yewdCYsdrm){FNdJMUAjDs = true;}
      else if(yewdCYsdrm == QfoHejRdfV){HtzTiQZZgp = true;}
      if(JApREAlwSg == ozWLqQCbkA){sWspslBImR = true;}
      else if(ozWLqQCbkA == JApREAlwSg){PYIwGjPSzD = true;}
      if(swoZnTiJlx == kgxFmCibFZ){soJJyepCfH = true;}
      if(ygSUQdgLPH == RwRoJnnaMX){jguitsZFDJ = true;}
      if(HiQxffAyEV == dMIkHmufMo){BPodziEuTu = true;}
      while(kgxFmCibFZ == swoZnTiJlx){jdtRKGBizM = true;}
      while(RwRoJnnaMX == RwRoJnnaMX){SGKXHfuOCe = true;}
      while(dMIkHmufMo == dMIkHmufMo){eCPXOQxyPt = true;}
      if(wPxYRQhqpA == true){wPxYRQhqpA = false;}
      if(pQYRUrhgCD == true){pQYRUrhgCD = false;}
      if(baONVYXLyA == true){baONVYXLyA = false;}
      if(HDPPdCzrWr == true){HDPPdCzrWr = false;}
      if(FxkMhNnqQO == true){FxkMhNnqQO = false;}
      if(FNdJMUAjDs == true){FNdJMUAjDs = false;}
      if(sWspslBImR == true){sWspslBImR = false;}
      if(soJJyepCfH == true){soJJyepCfH = false;}
      if(jguitsZFDJ == true){jguitsZFDJ = false;}
      if(BPodziEuTu == true){BPodziEuTu = false;}
      if(LeEyUPETLg == true){LeEyUPETLg = false;}
      if(eyDuIMaJuz == true){eyDuIMaJuz = false;}
      if(MuFdQdAfKO == true){MuFdQdAfKO = false;}
      if(auikuFcxOd == true){auikuFcxOd = false;}
      if(oGtVdDLsUm == true){oGtVdDLsUm = false;}
      if(HtzTiQZZgp == true){HtzTiQZZgp = false;}
      if(PYIwGjPSzD == true){PYIwGjPSzD = false;}
      if(jdtRKGBizM == true){jdtRKGBizM = false;}
      if(SGKXHfuOCe == true){SGKXHfuOCe = false;}
      if(eCPXOQxyPt == true){eCPXOQxyPt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLXLGPYCSA
{ 
  void LiBuriNnpW()
  { 
      bool zrbmaVFdRQ = false;
      bool amHarYqAMc = false;
      bool PrXWRHQNOW = false;
      bool BtLYfuPnjC = false;
      bool oJwXfPCddF = false;
      bool GdtYMHUFUT = false;
      bool FrOtOgahuw = false;
      bool JCQJnGwApC = false;
      bool EliJPXzlMX = false;
      bool aJSPxwtBIz = false;
      bool nThhuDMkkG = false;
      bool KUOSOTJFeq = false;
      bool goVWVzjAMq = false;
      bool LtqpNkDBNL = false;
      bool KOAGNFuzBc = false;
      bool mnWQSzyLLw = false;
      bool TMXttQcXEd = false;
      bool PHrSgRnPJP = false;
      bool EjziDXXZXO = false;
      bool lroQryqGLx = false;
      string HqSAUGkKnr;
      string knUuzJPNAI;
      string yaHKbDQxyr;
      string lFuzYyMuxS;
      string PnGfBRKKrW;
      string iSyxRgjHYQ;
      string pmMwFesVWA;
      string xTPgsKTbIJ;
      string rFEaITHxgq;
      string OEVfcbaKZV;
      string YonrYOCQDH;
      string MIzPXjikml;
      string XuneksyjER;
      string iJBmkDRMCt;
      string QqsZeGFGIs;
      string roWmycAIGf;
      string PSLlXCGMdU;
      string RWisVgBNAe;
      string nqbLYtmOnH;
      string CJFVdyeHCb;
      if(HqSAUGkKnr == YonrYOCQDH){zrbmaVFdRQ = true;}
      else if(YonrYOCQDH == HqSAUGkKnr){nThhuDMkkG = true;}
      if(knUuzJPNAI == MIzPXjikml){amHarYqAMc = true;}
      else if(MIzPXjikml == knUuzJPNAI){KUOSOTJFeq = true;}
      if(yaHKbDQxyr == XuneksyjER){PrXWRHQNOW = true;}
      else if(XuneksyjER == yaHKbDQxyr){goVWVzjAMq = true;}
      if(lFuzYyMuxS == iJBmkDRMCt){BtLYfuPnjC = true;}
      else if(iJBmkDRMCt == lFuzYyMuxS){LtqpNkDBNL = true;}
      if(PnGfBRKKrW == QqsZeGFGIs){oJwXfPCddF = true;}
      else if(QqsZeGFGIs == PnGfBRKKrW){KOAGNFuzBc = true;}
      if(iSyxRgjHYQ == roWmycAIGf){GdtYMHUFUT = true;}
      else if(roWmycAIGf == iSyxRgjHYQ){mnWQSzyLLw = true;}
      if(pmMwFesVWA == PSLlXCGMdU){FrOtOgahuw = true;}
      else if(PSLlXCGMdU == pmMwFesVWA){TMXttQcXEd = true;}
      if(xTPgsKTbIJ == RWisVgBNAe){JCQJnGwApC = true;}
      if(rFEaITHxgq == nqbLYtmOnH){EliJPXzlMX = true;}
      if(OEVfcbaKZV == CJFVdyeHCb){aJSPxwtBIz = true;}
      while(RWisVgBNAe == xTPgsKTbIJ){PHrSgRnPJP = true;}
      while(nqbLYtmOnH == nqbLYtmOnH){EjziDXXZXO = true;}
      while(CJFVdyeHCb == CJFVdyeHCb){lroQryqGLx = true;}
      if(zrbmaVFdRQ == true){zrbmaVFdRQ = false;}
      if(amHarYqAMc == true){amHarYqAMc = false;}
      if(PrXWRHQNOW == true){PrXWRHQNOW = false;}
      if(BtLYfuPnjC == true){BtLYfuPnjC = false;}
      if(oJwXfPCddF == true){oJwXfPCddF = false;}
      if(GdtYMHUFUT == true){GdtYMHUFUT = false;}
      if(FrOtOgahuw == true){FrOtOgahuw = false;}
      if(JCQJnGwApC == true){JCQJnGwApC = false;}
      if(EliJPXzlMX == true){EliJPXzlMX = false;}
      if(aJSPxwtBIz == true){aJSPxwtBIz = false;}
      if(nThhuDMkkG == true){nThhuDMkkG = false;}
      if(KUOSOTJFeq == true){KUOSOTJFeq = false;}
      if(goVWVzjAMq == true){goVWVzjAMq = false;}
      if(LtqpNkDBNL == true){LtqpNkDBNL = false;}
      if(KOAGNFuzBc == true){KOAGNFuzBc = false;}
      if(mnWQSzyLLw == true){mnWQSzyLLw = false;}
      if(TMXttQcXEd == true){TMXttQcXEd = false;}
      if(PHrSgRnPJP == true){PHrSgRnPJP = false;}
      if(EjziDXXZXO == true){EjziDXXZXO = false;}
      if(lroQryqGLx == true){lroQryqGLx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQPEXIVAGN
{ 
  void lbLfbTBpqO()
  { 
      bool qXNbRnNLrl = false;
      bool fOyGSQERwy = false;
      bool bcFJaExZgJ = false;
      bool ZPDIhMWjGy = false;
      bool kDoTGyPzuC = false;
      bool wbGAQNRDAN = false;
      bool pneiMQLpYG = false;
      bool sTKyNYnkDc = false;
      bool nyddNyICqT = false;
      bool uTisHwXGHp = false;
      bool mZaoIbQImr = false;
      bool ZgzXYrJBUN = false;
      bool HIyELZjRqQ = false;
      bool AgcMpOXoUk = false;
      bool gAPztNTLTP = false;
      bool lWksieaVdi = false;
      bool rzRVrrDmhK = false;
      bool UUgjgGrzKx = false;
      bool GXxbdcwjdK = false;
      bool mCLlsgitHC = false;
      string FnZoaDKplF;
      string FoDTgkNPah;
      string QcdaKKWZrA;
      string SPfGfHIYBy;
      string TGSPCQNYfB;
      string jIddJcJydQ;
      string fjxklpJwnY;
      string coOcOKJOYt;
      string wyspPKkCwD;
      string yJtkSiIhdL;
      string HRjHXutAOz;
      string SuZjTgpGUa;
      string EHzkaTtcKe;
      string BbjNmeNlSU;
      string QjmxjCiKQk;
      string rCMCGARzfD;
      string AQpixqLLxo;
      string SEnAJTTCBY;
      string jjMYlzPhGm;
      string NOGOTAtDzr;
      if(FnZoaDKplF == HRjHXutAOz){qXNbRnNLrl = true;}
      else if(HRjHXutAOz == FnZoaDKplF){mZaoIbQImr = true;}
      if(FoDTgkNPah == SuZjTgpGUa){fOyGSQERwy = true;}
      else if(SuZjTgpGUa == FoDTgkNPah){ZgzXYrJBUN = true;}
      if(QcdaKKWZrA == EHzkaTtcKe){bcFJaExZgJ = true;}
      else if(EHzkaTtcKe == QcdaKKWZrA){HIyELZjRqQ = true;}
      if(SPfGfHIYBy == BbjNmeNlSU){ZPDIhMWjGy = true;}
      else if(BbjNmeNlSU == SPfGfHIYBy){AgcMpOXoUk = true;}
      if(TGSPCQNYfB == QjmxjCiKQk){kDoTGyPzuC = true;}
      else if(QjmxjCiKQk == TGSPCQNYfB){gAPztNTLTP = true;}
      if(jIddJcJydQ == rCMCGARzfD){wbGAQNRDAN = true;}
      else if(rCMCGARzfD == jIddJcJydQ){lWksieaVdi = true;}
      if(fjxklpJwnY == AQpixqLLxo){pneiMQLpYG = true;}
      else if(AQpixqLLxo == fjxklpJwnY){rzRVrrDmhK = true;}
      if(coOcOKJOYt == SEnAJTTCBY){sTKyNYnkDc = true;}
      if(wyspPKkCwD == jjMYlzPhGm){nyddNyICqT = true;}
      if(yJtkSiIhdL == NOGOTAtDzr){uTisHwXGHp = true;}
      while(SEnAJTTCBY == coOcOKJOYt){UUgjgGrzKx = true;}
      while(jjMYlzPhGm == jjMYlzPhGm){GXxbdcwjdK = true;}
      while(NOGOTAtDzr == NOGOTAtDzr){mCLlsgitHC = true;}
      if(qXNbRnNLrl == true){qXNbRnNLrl = false;}
      if(fOyGSQERwy == true){fOyGSQERwy = false;}
      if(bcFJaExZgJ == true){bcFJaExZgJ = false;}
      if(ZPDIhMWjGy == true){ZPDIhMWjGy = false;}
      if(kDoTGyPzuC == true){kDoTGyPzuC = false;}
      if(wbGAQNRDAN == true){wbGAQNRDAN = false;}
      if(pneiMQLpYG == true){pneiMQLpYG = false;}
      if(sTKyNYnkDc == true){sTKyNYnkDc = false;}
      if(nyddNyICqT == true){nyddNyICqT = false;}
      if(uTisHwXGHp == true){uTisHwXGHp = false;}
      if(mZaoIbQImr == true){mZaoIbQImr = false;}
      if(ZgzXYrJBUN == true){ZgzXYrJBUN = false;}
      if(HIyELZjRqQ == true){HIyELZjRqQ = false;}
      if(AgcMpOXoUk == true){AgcMpOXoUk = false;}
      if(gAPztNTLTP == true){gAPztNTLTP = false;}
      if(lWksieaVdi == true){lWksieaVdi = false;}
      if(rzRVrrDmhK == true){rzRVrrDmhK = false;}
      if(UUgjgGrzKx == true){UUgjgGrzKx = false;}
      if(GXxbdcwjdK == true){GXxbdcwjdK = false;}
      if(mCLlsgitHC == true){mCLlsgitHC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDCKKSLCMD
{ 
  void oOeexpBgat()
  { 
      bool VrpykEnkbk = false;
      bool luVWbfPphI = false;
      bool cREAdCneAn = false;
      bool ysDWdCSplM = false;
      bool HVrsVOSNoO = false;
      bool DBxCIDnpTi = false;
      bool QJjmmrrysZ = false;
      bool NYDVAHZKdO = false;
      bool jZoljwwBOZ = false;
      bool OcVDuykEGc = false;
      bool WTUPBexaBB = false;
      bool ccLEzpTyCp = false;
      bool wqiSKjCAZC = false;
      bool VVEBrPFZjF = false;
      bool yVANwkQRDF = false;
      bool elCPgfjBEQ = false;
      bool bxByeHYKMi = false;
      bool jtOwqaqVVZ = false;
      bool TkwUXjSnTM = false;
      bool eEUSdBTBio = false;
      string OXfoDlbgkq;
      string dqXtGacsDT;
      string nkQMbhDOPT;
      string IQPpWDlqTS;
      string TlfxiqWdeh;
      string jFyrmcHTNV;
      string hNRQhNahWC;
      string olZkABEScj;
      string KYigiDSWCs;
      string wScxkGUPOV;
      string PoHcsyfNrl;
      string YopdKIdjge;
      string tDecGWIbzs;
      string goDGUURGnk;
      string WEeQUHbzmb;
      string bjhjaLKdVW;
      string oDNzFjkjIo;
      string pXwwHoYOIz;
      string tJnXQwGTeI;
      string KnjRuTqeLk;
      if(OXfoDlbgkq == PoHcsyfNrl){VrpykEnkbk = true;}
      else if(PoHcsyfNrl == OXfoDlbgkq){WTUPBexaBB = true;}
      if(dqXtGacsDT == YopdKIdjge){luVWbfPphI = true;}
      else if(YopdKIdjge == dqXtGacsDT){ccLEzpTyCp = true;}
      if(nkQMbhDOPT == tDecGWIbzs){cREAdCneAn = true;}
      else if(tDecGWIbzs == nkQMbhDOPT){wqiSKjCAZC = true;}
      if(IQPpWDlqTS == goDGUURGnk){ysDWdCSplM = true;}
      else if(goDGUURGnk == IQPpWDlqTS){VVEBrPFZjF = true;}
      if(TlfxiqWdeh == WEeQUHbzmb){HVrsVOSNoO = true;}
      else if(WEeQUHbzmb == TlfxiqWdeh){yVANwkQRDF = true;}
      if(jFyrmcHTNV == bjhjaLKdVW){DBxCIDnpTi = true;}
      else if(bjhjaLKdVW == jFyrmcHTNV){elCPgfjBEQ = true;}
      if(hNRQhNahWC == oDNzFjkjIo){QJjmmrrysZ = true;}
      else if(oDNzFjkjIo == hNRQhNahWC){bxByeHYKMi = true;}
      if(olZkABEScj == pXwwHoYOIz){NYDVAHZKdO = true;}
      if(KYigiDSWCs == tJnXQwGTeI){jZoljwwBOZ = true;}
      if(wScxkGUPOV == KnjRuTqeLk){OcVDuykEGc = true;}
      while(pXwwHoYOIz == olZkABEScj){jtOwqaqVVZ = true;}
      while(tJnXQwGTeI == tJnXQwGTeI){TkwUXjSnTM = true;}
      while(KnjRuTqeLk == KnjRuTqeLk){eEUSdBTBio = true;}
      if(VrpykEnkbk == true){VrpykEnkbk = false;}
      if(luVWbfPphI == true){luVWbfPphI = false;}
      if(cREAdCneAn == true){cREAdCneAn = false;}
      if(ysDWdCSplM == true){ysDWdCSplM = false;}
      if(HVrsVOSNoO == true){HVrsVOSNoO = false;}
      if(DBxCIDnpTi == true){DBxCIDnpTi = false;}
      if(QJjmmrrysZ == true){QJjmmrrysZ = false;}
      if(NYDVAHZKdO == true){NYDVAHZKdO = false;}
      if(jZoljwwBOZ == true){jZoljwwBOZ = false;}
      if(OcVDuykEGc == true){OcVDuykEGc = false;}
      if(WTUPBexaBB == true){WTUPBexaBB = false;}
      if(ccLEzpTyCp == true){ccLEzpTyCp = false;}
      if(wqiSKjCAZC == true){wqiSKjCAZC = false;}
      if(VVEBrPFZjF == true){VVEBrPFZjF = false;}
      if(yVANwkQRDF == true){yVANwkQRDF = false;}
      if(elCPgfjBEQ == true){elCPgfjBEQ = false;}
      if(bxByeHYKMi == true){bxByeHYKMi = false;}
      if(jtOwqaqVVZ == true){jtOwqaqVVZ = false;}
      if(TkwUXjSnTM == true){TkwUXjSnTM = false;}
      if(eEUSdBTBio == true){eEUSdBTBio = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYQHCCGSOR
{ 
  void dVaQjLSKPR()
  { 
      bool zOoKPJhXbu = false;
      bool PLySoxftBy = false;
      bool UsuNToZxuB = false;
      bool gLGtBXikZc = false;
      bool xFnYmkaozD = false;
      bool SrzPKGSaqa = false;
      bool jjbaOEEDQR = false;
      bool NtTXAPFWZh = false;
      bool NjyrhoLpiu = false;
      bool FItysMcMKi = false;
      bool fWXgoYXaPu = false;
      bool BwBINzljrZ = false;
      bool rOUVMFzUem = false;
      bool lrLqCpLQCJ = false;
      bool QkamtIGlks = false;
      bool asTkpRCCUi = false;
      bool YDwbJIjKGW = false;
      bool nUgiIHngbD = false;
      bool zNjkMrXZAj = false;
      bool nJwSkNoydk = false;
      string HGmIOZZJBW;
      string GOQukHwbnx;
      string MWFDzAlIwI;
      string TqEeNNNNid;
      string SlhHRneKBm;
      string jrPxGkAjJO;
      string mQMsCPJlgW;
      string tirKeZnxkL;
      string VbGJXaaHYb;
      string MdEUpBYoEC;
      string esderAAERf;
      string xDyysLJDUb;
      string nBMFKQeXUd;
      string ByshgbxbQX;
      string aVoreJeGad;
      string qUUcNcfYTb;
      string VbjndyJQRQ;
      string NhmxASMUZB;
      string lYwplfdQUD;
      string wYIoBzlBNf;
      if(HGmIOZZJBW == esderAAERf){zOoKPJhXbu = true;}
      else if(esderAAERf == HGmIOZZJBW){fWXgoYXaPu = true;}
      if(GOQukHwbnx == xDyysLJDUb){PLySoxftBy = true;}
      else if(xDyysLJDUb == GOQukHwbnx){BwBINzljrZ = true;}
      if(MWFDzAlIwI == nBMFKQeXUd){UsuNToZxuB = true;}
      else if(nBMFKQeXUd == MWFDzAlIwI){rOUVMFzUem = true;}
      if(TqEeNNNNid == ByshgbxbQX){gLGtBXikZc = true;}
      else if(ByshgbxbQX == TqEeNNNNid){lrLqCpLQCJ = true;}
      if(SlhHRneKBm == aVoreJeGad){xFnYmkaozD = true;}
      else if(aVoreJeGad == SlhHRneKBm){QkamtIGlks = true;}
      if(jrPxGkAjJO == qUUcNcfYTb){SrzPKGSaqa = true;}
      else if(qUUcNcfYTb == jrPxGkAjJO){asTkpRCCUi = true;}
      if(mQMsCPJlgW == VbjndyJQRQ){jjbaOEEDQR = true;}
      else if(VbjndyJQRQ == mQMsCPJlgW){YDwbJIjKGW = true;}
      if(tirKeZnxkL == NhmxASMUZB){NtTXAPFWZh = true;}
      if(VbGJXaaHYb == lYwplfdQUD){NjyrhoLpiu = true;}
      if(MdEUpBYoEC == wYIoBzlBNf){FItysMcMKi = true;}
      while(NhmxASMUZB == tirKeZnxkL){nUgiIHngbD = true;}
      while(lYwplfdQUD == lYwplfdQUD){zNjkMrXZAj = true;}
      while(wYIoBzlBNf == wYIoBzlBNf){nJwSkNoydk = true;}
      if(zOoKPJhXbu == true){zOoKPJhXbu = false;}
      if(PLySoxftBy == true){PLySoxftBy = false;}
      if(UsuNToZxuB == true){UsuNToZxuB = false;}
      if(gLGtBXikZc == true){gLGtBXikZc = false;}
      if(xFnYmkaozD == true){xFnYmkaozD = false;}
      if(SrzPKGSaqa == true){SrzPKGSaqa = false;}
      if(jjbaOEEDQR == true){jjbaOEEDQR = false;}
      if(NtTXAPFWZh == true){NtTXAPFWZh = false;}
      if(NjyrhoLpiu == true){NjyrhoLpiu = false;}
      if(FItysMcMKi == true){FItysMcMKi = false;}
      if(fWXgoYXaPu == true){fWXgoYXaPu = false;}
      if(BwBINzljrZ == true){BwBINzljrZ = false;}
      if(rOUVMFzUem == true){rOUVMFzUem = false;}
      if(lrLqCpLQCJ == true){lrLqCpLQCJ = false;}
      if(QkamtIGlks == true){QkamtIGlks = false;}
      if(asTkpRCCUi == true){asTkpRCCUi = false;}
      if(YDwbJIjKGW == true){YDwbJIjKGW = false;}
      if(nUgiIHngbD == true){nUgiIHngbD = false;}
      if(zNjkMrXZAj == true){zNjkMrXZAj = false;}
      if(nJwSkNoydk == true){nJwSkNoydk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVPFCUWKXZ
{ 
  void UTOKmwjjpF()
  { 
      bool WNxrYKNbDk = false;
      bool HpNOOYzsMl = false;
      bool LTmFFUkRsY = false;
      bool aDMFKBddZN = false;
      bool DqznHHrmxF = false;
      bool UDorjCarmD = false;
      bool YuidJDdHEN = false;
      bool tUTzhTUzxx = false;
      bool byTmDXOTVH = false;
      bool alqVoHIUeE = false;
      bool dkhjLAjpJP = false;
      bool hatpbZauak = false;
      bool nJkwlHcxJZ = false;
      bool LzUsSqPibC = false;
      bool mYKGZzrBtO = false;
      bool fMtsPTzkxD = false;
      bool XmfiEhGBWj = false;
      bool JqTYyPzeWm = false;
      bool PaCusyFbcy = false;
      bool relXeAraBq = false;
      string TabtTFxWBd;
      string LmtrLewqqA;
      string TAYaSCAnoZ;
      string PPEdrSVotz;
      string twdtTmTpQd;
      string AkiMjTBBbQ;
      string FJgbNuiQzr;
      string JGwrGXVeGf;
      string hKWKYegrsX;
      string QUNdtjOCfY;
      string DDpXTsnpFM;
      string yWtwhulVCi;
      string OqWabosSyV;
      string JSzhbeUyqe;
      string pplgZtZRuz;
      string yrzwJMfOwd;
      string AVrjCeWLTD;
      string ZneXsYFpBg;
      string PbWyXQTCYO;
      string yFCMeTxBdu;
      if(TabtTFxWBd == DDpXTsnpFM){WNxrYKNbDk = true;}
      else if(DDpXTsnpFM == TabtTFxWBd){dkhjLAjpJP = true;}
      if(LmtrLewqqA == yWtwhulVCi){HpNOOYzsMl = true;}
      else if(yWtwhulVCi == LmtrLewqqA){hatpbZauak = true;}
      if(TAYaSCAnoZ == OqWabosSyV){LTmFFUkRsY = true;}
      else if(OqWabosSyV == TAYaSCAnoZ){nJkwlHcxJZ = true;}
      if(PPEdrSVotz == JSzhbeUyqe){aDMFKBddZN = true;}
      else if(JSzhbeUyqe == PPEdrSVotz){LzUsSqPibC = true;}
      if(twdtTmTpQd == pplgZtZRuz){DqznHHrmxF = true;}
      else if(pplgZtZRuz == twdtTmTpQd){mYKGZzrBtO = true;}
      if(AkiMjTBBbQ == yrzwJMfOwd){UDorjCarmD = true;}
      else if(yrzwJMfOwd == AkiMjTBBbQ){fMtsPTzkxD = true;}
      if(FJgbNuiQzr == AVrjCeWLTD){YuidJDdHEN = true;}
      else if(AVrjCeWLTD == FJgbNuiQzr){XmfiEhGBWj = true;}
      if(JGwrGXVeGf == ZneXsYFpBg){tUTzhTUzxx = true;}
      if(hKWKYegrsX == PbWyXQTCYO){byTmDXOTVH = true;}
      if(QUNdtjOCfY == yFCMeTxBdu){alqVoHIUeE = true;}
      while(ZneXsYFpBg == JGwrGXVeGf){JqTYyPzeWm = true;}
      while(PbWyXQTCYO == PbWyXQTCYO){PaCusyFbcy = true;}
      while(yFCMeTxBdu == yFCMeTxBdu){relXeAraBq = true;}
      if(WNxrYKNbDk == true){WNxrYKNbDk = false;}
      if(HpNOOYzsMl == true){HpNOOYzsMl = false;}
      if(LTmFFUkRsY == true){LTmFFUkRsY = false;}
      if(aDMFKBddZN == true){aDMFKBddZN = false;}
      if(DqznHHrmxF == true){DqznHHrmxF = false;}
      if(UDorjCarmD == true){UDorjCarmD = false;}
      if(YuidJDdHEN == true){YuidJDdHEN = false;}
      if(tUTzhTUzxx == true){tUTzhTUzxx = false;}
      if(byTmDXOTVH == true){byTmDXOTVH = false;}
      if(alqVoHIUeE == true){alqVoHIUeE = false;}
      if(dkhjLAjpJP == true){dkhjLAjpJP = false;}
      if(hatpbZauak == true){hatpbZauak = false;}
      if(nJkwlHcxJZ == true){nJkwlHcxJZ = false;}
      if(LzUsSqPibC == true){LzUsSqPibC = false;}
      if(mYKGZzrBtO == true){mYKGZzrBtO = false;}
      if(fMtsPTzkxD == true){fMtsPTzkxD = false;}
      if(XmfiEhGBWj == true){XmfiEhGBWj = false;}
      if(JqTYyPzeWm == true){JqTYyPzeWm = false;}
      if(PaCusyFbcy == true){PaCusyFbcy = false;}
      if(relXeAraBq == true){relXeAraBq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LNGEGYFMWI
{ 
  void sKCDtzmLgT()
  { 
      bool wsQcYCaqFZ = false;
      bool YlUXiMdgFs = false;
      bool fBacbnuAPn = false;
      bool NpZxftDrFu = false;
      bool RFicVEGxIE = false;
      bool PQiUYuRmBk = false;
      bool HabRMiLWqn = false;
      bool JlbJbZSyHW = false;
      bool gxqKYwGFXk = false;
      bool bPpTnqdQQm = false;
      bool riFTucoYsy = false;
      bool bTedEJiQsP = false;
      bool bFyFMsuIVj = false;
      bool wBhUdxqWOu = false;
      bool HhMZIIkMPe = false;
      bool IMXAKmjAHC = false;
      bool hfDICalKzG = false;
      bool RLByHtsYxD = false;
      bool IisqbidgJq = false;
      bool MqPMNaeDWh = false;
      string lDphEIJxVO;
      string GydjrQXxwK;
      string YGrWmllfoz;
      string brKnOSLEyY;
      string kjcBXOFdqo;
      string JQCuneLTtR;
      string VcIWlNmoVY;
      string ESyWYndqzY;
      string gHoAoLpPAj;
      string HrKgDHbGOJ;
      string aPISjpReVz;
      string BTTVjOnIga;
      string WXokQMIRSR;
      string MWcoxRzWPz;
      string sKsAinXnwn;
      string TTZmlDaWBX;
      string gzLEmdqdXS;
      string PQrhgMenCc;
      string nTVeysxoDt;
      string qbVrRsyoNF;
      if(lDphEIJxVO == aPISjpReVz){wsQcYCaqFZ = true;}
      else if(aPISjpReVz == lDphEIJxVO){riFTucoYsy = true;}
      if(GydjrQXxwK == BTTVjOnIga){YlUXiMdgFs = true;}
      else if(BTTVjOnIga == GydjrQXxwK){bTedEJiQsP = true;}
      if(YGrWmllfoz == WXokQMIRSR){fBacbnuAPn = true;}
      else if(WXokQMIRSR == YGrWmllfoz){bFyFMsuIVj = true;}
      if(brKnOSLEyY == MWcoxRzWPz){NpZxftDrFu = true;}
      else if(MWcoxRzWPz == brKnOSLEyY){wBhUdxqWOu = true;}
      if(kjcBXOFdqo == sKsAinXnwn){RFicVEGxIE = true;}
      else if(sKsAinXnwn == kjcBXOFdqo){HhMZIIkMPe = true;}
      if(JQCuneLTtR == TTZmlDaWBX){PQiUYuRmBk = true;}
      else if(TTZmlDaWBX == JQCuneLTtR){IMXAKmjAHC = true;}
      if(VcIWlNmoVY == gzLEmdqdXS){HabRMiLWqn = true;}
      else if(gzLEmdqdXS == VcIWlNmoVY){hfDICalKzG = true;}
      if(ESyWYndqzY == PQrhgMenCc){JlbJbZSyHW = true;}
      if(gHoAoLpPAj == nTVeysxoDt){gxqKYwGFXk = true;}
      if(HrKgDHbGOJ == qbVrRsyoNF){bPpTnqdQQm = true;}
      while(PQrhgMenCc == ESyWYndqzY){RLByHtsYxD = true;}
      while(nTVeysxoDt == nTVeysxoDt){IisqbidgJq = true;}
      while(qbVrRsyoNF == qbVrRsyoNF){MqPMNaeDWh = true;}
      if(wsQcYCaqFZ == true){wsQcYCaqFZ = false;}
      if(YlUXiMdgFs == true){YlUXiMdgFs = false;}
      if(fBacbnuAPn == true){fBacbnuAPn = false;}
      if(NpZxftDrFu == true){NpZxftDrFu = false;}
      if(RFicVEGxIE == true){RFicVEGxIE = false;}
      if(PQiUYuRmBk == true){PQiUYuRmBk = false;}
      if(HabRMiLWqn == true){HabRMiLWqn = false;}
      if(JlbJbZSyHW == true){JlbJbZSyHW = false;}
      if(gxqKYwGFXk == true){gxqKYwGFXk = false;}
      if(bPpTnqdQQm == true){bPpTnqdQQm = false;}
      if(riFTucoYsy == true){riFTucoYsy = false;}
      if(bTedEJiQsP == true){bTedEJiQsP = false;}
      if(bFyFMsuIVj == true){bFyFMsuIVj = false;}
      if(wBhUdxqWOu == true){wBhUdxqWOu = false;}
      if(HhMZIIkMPe == true){HhMZIIkMPe = false;}
      if(IMXAKmjAHC == true){IMXAKmjAHC = false;}
      if(hfDICalKzG == true){hfDICalKzG = false;}
      if(RLByHtsYxD == true){RLByHtsYxD = false;}
      if(IisqbidgJq == true){IisqbidgJq = false;}
      if(MqPMNaeDWh == true){MqPMNaeDWh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDGBALPPGO
{ 
  void kfGkjNGgrr()
  { 
      bool nepEApQMlZ = false;
      bool sSWZNMLyfY = false;
      bool SeqFMlBlnP = false;
      bool FqQuuVPBQW = false;
      bool MXRSSMbWbi = false;
      bool IxRuzImkrN = false;
      bool ndYVUCBbdr = false;
      bool wKgJLuNYmz = false;
      bool JeKFHHZUwm = false;
      bool heJCiizuxP = false;
      bool LAsilyQHjE = false;
      bool tNxrEJTSNN = false;
      bool cffpJRAdZc = false;
      bool uRbWnJkaSJ = false;
      bool pRkqsUgQyZ = false;
      bool OfhjmeUDZU = false;
      bool xlhGIblZEt = false;
      bool XrADWKtnwo = false;
      bool jjfANPjrjI = false;
      bool ohByMEjeiR = false;
      string oeHTtxBIPt;
      string JCePxPeZAU;
      string iYAtuUTYuR;
      string KOhVXKgtxm;
      string WmtejkWNCM;
      string TzhsWPeNXY;
      string cbNxiuUIrl;
      string ikbNxwdVJK;
      string xGWhyKgnyH;
      string fSVXJuYwuo;
      string PNUPdiWUwa;
      string kIEMaWFfzY;
      string NgJjGPODEC;
      string WhZTuikGDP;
      string nMqXVWOIxl;
      string osxWbiEkJO;
      string TSPsDDijRr;
      string lzbjkBolNj;
      string AGGRNdkDrM;
      string ezxouUwxUS;
      if(oeHTtxBIPt == PNUPdiWUwa){nepEApQMlZ = true;}
      else if(PNUPdiWUwa == oeHTtxBIPt){LAsilyQHjE = true;}
      if(JCePxPeZAU == kIEMaWFfzY){sSWZNMLyfY = true;}
      else if(kIEMaWFfzY == JCePxPeZAU){tNxrEJTSNN = true;}
      if(iYAtuUTYuR == NgJjGPODEC){SeqFMlBlnP = true;}
      else if(NgJjGPODEC == iYAtuUTYuR){cffpJRAdZc = true;}
      if(KOhVXKgtxm == WhZTuikGDP){FqQuuVPBQW = true;}
      else if(WhZTuikGDP == KOhVXKgtxm){uRbWnJkaSJ = true;}
      if(WmtejkWNCM == nMqXVWOIxl){MXRSSMbWbi = true;}
      else if(nMqXVWOIxl == WmtejkWNCM){pRkqsUgQyZ = true;}
      if(TzhsWPeNXY == osxWbiEkJO){IxRuzImkrN = true;}
      else if(osxWbiEkJO == TzhsWPeNXY){OfhjmeUDZU = true;}
      if(cbNxiuUIrl == TSPsDDijRr){ndYVUCBbdr = true;}
      else if(TSPsDDijRr == cbNxiuUIrl){xlhGIblZEt = true;}
      if(ikbNxwdVJK == lzbjkBolNj){wKgJLuNYmz = true;}
      if(xGWhyKgnyH == AGGRNdkDrM){JeKFHHZUwm = true;}
      if(fSVXJuYwuo == ezxouUwxUS){heJCiizuxP = true;}
      while(lzbjkBolNj == ikbNxwdVJK){XrADWKtnwo = true;}
      while(AGGRNdkDrM == AGGRNdkDrM){jjfANPjrjI = true;}
      while(ezxouUwxUS == ezxouUwxUS){ohByMEjeiR = true;}
      if(nepEApQMlZ == true){nepEApQMlZ = false;}
      if(sSWZNMLyfY == true){sSWZNMLyfY = false;}
      if(SeqFMlBlnP == true){SeqFMlBlnP = false;}
      if(FqQuuVPBQW == true){FqQuuVPBQW = false;}
      if(MXRSSMbWbi == true){MXRSSMbWbi = false;}
      if(IxRuzImkrN == true){IxRuzImkrN = false;}
      if(ndYVUCBbdr == true){ndYVUCBbdr = false;}
      if(wKgJLuNYmz == true){wKgJLuNYmz = false;}
      if(JeKFHHZUwm == true){JeKFHHZUwm = false;}
      if(heJCiizuxP == true){heJCiizuxP = false;}
      if(LAsilyQHjE == true){LAsilyQHjE = false;}
      if(tNxrEJTSNN == true){tNxrEJTSNN = false;}
      if(cffpJRAdZc == true){cffpJRAdZc = false;}
      if(uRbWnJkaSJ == true){uRbWnJkaSJ = false;}
      if(pRkqsUgQyZ == true){pRkqsUgQyZ = false;}
      if(OfhjmeUDZU == true){OfhjmeUDZU = false;}
      if(xlhGIblZEt == true){xlhGIblZEt = false;}
      if(XrADWKtnwo == true){XrADWKtnwo = false;}
      if(jjfANPjrjI == true){jjfANPjrjI = false;}
      if(ohByMEjeiR == true){ohByMEjeiR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIBFTUTLBD
{ 
  void SlOaxUuENG()
  { 
      bool DcSJKMEpwp = false;
      bool hBqMrgOLry = false;
      bool qwNmumzexa = false;
      bool XFBRfqEjZz = false;
      bool cgFLKthBOI = false;
      bool GPhZWGPeNX = false;
      bool MYsVRcAYgA = false;
      bool bdkrVJqCcB = false;
      bool EyQnTHXauY = false;
      bool aYVCmDnish = false;
      bool sJUNfbdoDM = false;
      bool ONBMSOIECJ = false;
      bool EYcHZDHiES = false;
      bool UHJuHtcDHq = false;
      bool dhXhJNXIiY = false;
      bool tigicUfMmc = false;
      bool TukkrGEFFY = false;
      bool kFwKfVBtyM = false;
      bool ezzfXkaZSl = false;
      bool NQPeWhxlpC = false;
      string AplJzqTaLy;
      string UfITebUJCA;
      string GYkWmMGDeI;
      string qTzZSzOJBP;
      string OoNYPGleMm;
      string lKqcTaFOVm;
      string jPwDGBgiAe;
      string NKImlQLMHg;
      string ZaqrVfbVGr;
      string tAnNezsKSO;
      string ZDegZaCDqC;
      string PrHnNIYDgZ;
      string YKcIkNWtHm;
      string WAtrHVwKSt;
      string dXeDbBrzAW;
      string apcrpOaWuM;
      string EIwEfOyOfq;
      string MNkmwAfYfi;
      string UXsjMgXBBs;
      string uYOGpVbZXN;
      if(AplJzqTaLy == ZDegZaCDqC){DcSJKMEpwp = true;}
      else if(ZDegZaCDqC == AplJzqTaLy){sJUNfbdoDM = true;}
      if(UfITebUJCA == PrHnNIYDgZ){hBqMrgOLry = true;}
      else if(PrHnNIYDgZ == UfITebUJCA){ONBMSOIECJ = true;}
      if(GYkWmMGDeI == YKcIkNWtHm){qwNmumzexa = true;}
      else if(YKcIkNWtHm == GYkWmMGDeI){EYcHZDHiES = true;}
      if(qTzZSzOJBP == WAtrHVwKSt){XFBRfqEjZz = true;}
      else if(WAtrHVwKSt == qTzZSzOJBP){UHJuHtcDHq = true;}
      if(OoNYPGleMm == dXeDbBrzAW){cgFLKthBOI = true;}
      else if(dXeDbBrzAW == OoNYPGleMm){dhXhJNXIiY = true;}
      if(lKqcTaFOVm == apcrpOaWuM){GPhZWGPeNX = true;}
      else if(apcrpOaWuM == lKqcTaFOVm){tigicUfMmc = true;}
      if(jPwDGBgiAe == EIwEfOyOfq){MYsVRcAYgA = true;}
      else if(EIwEfOyOfq == jPwDGBgiAe){TukkrGEFFY = true;}
      if(NKImlQLMHg == MNkmwAfYfi){bdkrVJqCcB = true;}
      if(ZaqrVfbVGr == UXsjMgXBBs){EyQnTHXauY = true;}
      if(tAnNezsKSO == uYOGpVbZXN){aYVCmDnish = true;}
      while(MNkmwAfYfi == NKImlQLMHg){kFwKfVBtyM = true;}
      while(UXsjMgXBBs == UXsjMgXBBs){ezzfXkaZSl = true;}
      while(uYOGpVbZXN == uYOGpVbZXN){NQPeWhxlpC = true;}
      if(DcSJKMEpwp == true){DcSJKMEpwp = false;}
      if(hBqMrgOLry == true){hBqMrgOLry = false;}
      if(qwNmumzexa == true){qwNmumzexa = false;}
      if(XFBRfqEjZz == true){XFBRfqEjZz = false;}
      if(cgFLKthBOI == true){cgFLKthBOI = false;}
      if(GPhZWGPeNX == true){GPhZWGPeNX = false;}
      if(MYsVRcAYgA == true){MYsVRcAYgA = false;}
      if(bdkrVJqCcB == true){bdkrVJqCcB = false;}
      if(EyQnTHXauY == true){EyQnTHXauY = false;}
      if(aYVCmDnish == true){aYVCmDnish = false;}
      if(sJUNfbdoDM == true){sJUNfbdoDM = false;}
      if(ONBMSOIECJ == true){ONBMSOIECJ = false;}
      if(EYcHZDHiES == true){EYcHZDHiES = false;}
      if(UHJuHtcDHq == true){UHJuHtcDHq = false;}
      if(dhXhJNXIiY == true){dhXhJNXIiY = false;}
      if(tigicUfMmc == true){tigicUfMmc = false;}
      if(TukkrGEFFY == true){TukkrGEFFY = false;}
      if(kFwKfVBtyM == true){kFwKfVBtyM = false;}
      if(ezzfXkaZSl == true){ezzfXkaZSl = false;}
      if(NQPeWhxlpC == true){NQPeWhxlpC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLRAEIOWXY
{ 
  void eQzofbYWZG()
  { 
      bool IFSkLWZsrP = false;
      bool mrnfRblpMH = false;
      bool zolhGHOuLb = false;
      bool AeJqoRcJDf = false;
      bool ILnAoKCVXq = false;
      bool BnJoBSSjdE = false;
      bool HdhPOIixpz = false;
      bool zcmfynBksu = false;
      bool EsXTZMUUoW = false;
      bool zrfzXecYlf = false;
      bool bEfXrYAcpN = false;
      bool QgqhzNGNpB = false;
      bool mNHSAGxmHT = false;
      bool KczNSzNzbB = false;
      bool LrebFRBxzK = false;
      bool XPhjrOwMXk = false;
      bool bMUVCnhdOz = false;
      bool AHloptifMh = false;
      bool FzmxuutPUE = false;
      bool CBapYyXIZR = false;
      string mznCKFythn;
      string eutfDEAPTz;
      string WhEGmCaMZU;
      string LBVeskCUQM;
      string WyJVmxHUZW;
      string dUlgIFtgPI;
      string dkUNbdYPmS;
      string BeyHbXXiTo;
      string uGmCpqOnWm;
      string pVFIhldusJ;
      string YrgGVyVeEj;
      string gLNaNXySWk;
      string OjszcfZoYp;
      string tcoKQCYffr;
      string UjjlGeIduK;
      string nLXItnzhdp;
      string XfFOpEWCKK;
      string yRleQeAGsx;
      string XwtOChEgPb;
      string DqCpTndVwB;
      if(mznCKFythn == YrgGVyVeEj){IFSkLWZsrP = true;}
      else if(YrgGVyVeEj == mznCKFythn){bEfXrYAcpN = true;}
      if(eutfDEAPTz == gLNaNXySWk){mrnfRblpMH = true;}
      else if(gLNaNXySWk == eutfDEAPTz){QgqhzNGNpB = true;}
      if(WhEGmCaMZU == OjszcfZoYp){zolhGHOuLb = true;}
      else if(OjszcfZoYp == WhEGmCaMZU){mNHSAGxmHT = true;}
      if(LBVeskCUQM == tcoKQCYffr){AeJqoRcJDf = true;}
      else if(tcoKQCYffr == LBVeskCUQM){KczNSzNzbB = true;}
      if(WyJVmxHUZW == UjjlGeIduK){ILnAoKCVXq = true;}
      else if(UjjlGeIduK == WyJVmxHUZW){LrebFRBxzK = true;}
      if(dUlgIFtgPI == nLXItnzhdp){BnJoBSSjdE = true;}
      else if(nLXItnzhdp == dUlgIFtgPI){XPhjrOwMXk = true;}
      if(dkUNbdYPmS == XfFOpEWCKK){HdhPOIixpz = true;}
      else if(XfFOpEWCKK == dkUNbdYPmS){bMUVCnhdOz = true;}
      if(BeyHbXXiTo == yRleQeAGsx){zcmfynBksu = true;}
      if(uGmCpqOnWm == XwtOChEgPb){EsXTZMUUoW = true;}
      if(pVFIhldusJ == DqCpTndVwB){zrfzXecYlf = true;}
      while(yRleQeAGsx == BeyHbXXiTo){AHloptifMh = true;}
      while(XwtOChEgPb == XwtOChEgPb){FzmxuutPUE = true;}
      while(DqCpTndVwB == DqCpTndVwB){CBapYyXIZR = true;}
      if(IFSkLWZsrP == true){IFSkLWZsrP = false;}
      if(mrnfRblpMH == true){mrnfRblpMH = false;}
      if(zolhGHOuLb == true){zolhGHOuLb = false;}
      if(AeJqoRcJDf == true){AeJqoRcJDf = false;}
      if(ILnAoKCVXq == true){ILnAoKCVXq = false;}
      if(BnJoBSSjdE == true){BnJoBSSjdE = false;}
      if(HdhPOIixpz == true){HdhPOIixpz = false;}
      if(zcmfynBksu == true){zcmfynBksu = false;}
      if(EsXTZMUUoW == true){EsXTZMUUoW = false;}
      if(zrfzXecYlf == true){zrfzXecYlf = false;}
      if(bEfXrYAcpN == true){bEfXrYAcpN = false;}
      if(QgqhzNGNpB == true){QgqhzNGNpB = false;}
      if(mNHSAGxmHT == true){mNHSAGxmHT = false;}
      if(KczNSzNzbB == true){KczNSzNzbB = false;}
      if(LrebFRBxzK == true){LrebFRBxzK = false;}
      if(XPhjrOwMXk == true){XPhjrOwMXk = false;}
      if(bMUVCnhdOz == true){bMUVCnhdOz = false;}
      if(AHloptifMh == true){AHloptifMh = false;}
      if(FzmxuutPUE == true){FzmxuutPUE = false;}
      if(CBapYyXIZR == true){CBapYyXIZR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYXRVATXCM
{ 
  void xcagtBZBnW()
  { 
      bool ADTrrTnsTR = false;
      bool LAhgHlGPIR = false;
      bool JdLpQQoIzP = false;
      bool hGEXJmMMto = false;
      bool XdBFaIxZti = false;
      bool uqtHjWrdab = false;
      bool eesEjEuKWU = false;
      bool ZtVTtecGOI = false;
      bool TOOQUpMwnm = false;
      bool thkSJskwVW = false;
      bool MmCYJBVaNE = false;
      bool tlOSHPQcjs = false;
      bool rzWjZqIDJA = false;
      bool tfjrugMoHS = false;
      bool UlhisITRKs = false;
      bool bHMcdNQRyR = false;
      bool rRQMJNBVXa = false;
      bool DaVQXGQmqQ = false;
      bool XprPYmSHOg = false;
      bool QtqoZDUUYe = false;
      string LsLjMGEWqD;
      string uZkMCSgzMf;
      string VgNTtwEOht;
      string eKjGYlpWwS;
      string zAVomnsfQE;
      string IjXYLeeroQ;
      string BpowYjpemP;
      string bKCsgVLXfF;
      string CYxcltmLtt;
      string GygfRIKYQD;
      string yOsAbxhdqo;
      string TGLjNbsLKd;
      string xdjrJcdWbY;
      string KlHcGnfxBo;
      string MIUEazmxRo;
      string PyOlFUeApy;
      string SKCRdgzicZ;
      string wuKURnJeRJ;
      string pgElJMXVWl;
      string IfGCVBGCZs;
      if(LsLjMGEWqD == yOsAbxhdqo){ADTrrTnsTR = true;}
      else if(yOsAbxhdqo == LsLjMGEWqD){MmCYJBVaNE = true;}
      if(uZkMCSgzMf == TGLjNbsLKd){LAhgHlGPIR = true;}
      else if(TGLjNbsLKd == uZkMCSgzMf){tlOSHPQcjs = true;}
      if(VgNTtwEOht == xdjrJcdWbY){JdLpQQoIzP = true;}
      else if(xdjrJcdWbY == VgNTtwEOht){rzWjZqIDJA = true;}
      if(eKjGYlpWwS == KlHcGnfxBo){hGEXJmMMto = true;}
      else if(KlHcGnfxBo == eKjGYlpWwS){tfjrugMoHS = true;}
      if(zAVomnsfQE == MIUEazmxRo){XdBFaIxZti = true;}
      else if(MIUEazmxRo == zAVomnsfQE){UlhisITRKs = true;}
      if(IjXYLeeroQ == PyOlFUeApy){uqtHjWrdab = true;}
      else if(PyOlFUeApy == IjXYLeeroQ){bHMcdNQRyR = true;}
      if(BpowYjpemP == SKCRdgzicZ){eesEjEuKWU = true;}
      else if(SKCRdgzicZ == BpowYjpemP){rRQMJNBVXa = true;}
      if(bKCsgVLXfF == wuKURnJeRJ){ZtVTtecGOI = true;}
      if(CYxcltmLtt == pgElJMXVWl){TOOQUpMwnm = true;}
      if(GygfRIKYQD == IfGCVBGCZs){thkSJskwVW = true;}
      while(wuKURnJeRJ == bKCsgVLXfF){DaVQXGQmqQ = true;}
      while(pgElJMXVWl == pgElJMXVWl){XprPYmSHOg = true;}
      while(IfGCVBGCZs == IfGCVBGCZs){QtqoZDUUYe = true;}
      if(ADTrrTnsTR == true){ADTrrTnsTR = false;}
      if(LAhgHlGPIR == true){LAhgHlGPIR = false;}
      if(JdLpQQoIzP == true){JdLpQQoIzP = false;}
      if(hGEXJmMMto == true){hGEXJmMMto = false;}
      if(XdBFaIxZti == true){XdBFaIxZti = false;}
      if(uqtHjWrdab == true){uqtHjWrdab = false;}
      if(eesEjEuKWU == true){eesEjEuKWU = false;}
      if(ZtVTtecGOI == true){ZtVTtecGOI = false;}
      if(TOOQUpMwnm == true){TOOQUpMwnm = false;}
      if(thkSJskwVW == true){thkSJskwVW = false;}
      if(MmCYJBVaNE == true){MmCYJBVaNE = false;}
      if(tlOSHPQcjs == true){tlOSHPQcjs = false;}
      if(rzWjZqIDJA == true){rzWjZqIDJA = false;}
      if(tfjrugMoHS == true){tfjrugMoHS = false;}
      if(UlhisITRKs == true){UlhisITRKs = false;}
      if(bHMcdNQRyR == true){bHMcdNQRyR = false;}
      if(rRQMJNBVXa == true){rRQMJNBVXa = false;}
      if(DaVQXGQmqQ == true){DaVQXGQmqQ = false;}
      if(XprPYmSHOg == true){XprPYmSHOg = false;}
      if(QtqoZDUUYe == true){QtqoZDUUYe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZAQDKBXSMZ
{ 
  void VWlGPVCufN()
  { 
      bool QSMGAIPHXN = false;
      bool ArRAuIDIeB = false;
      bool EfBWYRXbxY = false;
      bool rNhldnxMGo = false;
      bool DSxQIEwZsy = false;
      bool TCslHkRogh = false;
      bool kmKzVmKeWH = false;
      bool KqCoykikOU = false;
      bool VxiyEpTues = false;
      bool WHeXDPIytU = false;
      bool sQDlnbzDnW = false;
      bool CfaMLnELtf = false;
      bool SPAdjCMeli = false;
      bool ckptaFtwKb = false;
      bool pQHHppgRLP = false;
      bool KwDOBdPZBk = false;
      bool PUREtRpfkF = false;
      bool sHBRpCHrmt = false;
      bool VtSVXfgarx = false;
      bool pUuZLUzCNY = false;
      string zwPVxtJBVf;
      string ScqMQguAWK;
      string izIuWJwJst;
      string eLDiKwxUwp;
      string bwTJCADJdr;
      string xUhRGznUym;
      string yAIbAHZIBU;
      string iZDfhmfyrV;
      string GleAxKclcL;
      string HcVIrbnqJu;
      string atHIJWQCiT;
      string TocbgLUHep;
      string dnfpMGDtmF;
      string ynnwuLeWqZ;
      string saCJqRzsbg;
      string HfMTRlOQuC;
      string SVPdUeBffV;
      string fyQEwDlWyu;
      string HKSGySaUeJ;
      string wNanHXKXnL;
      if(zwPVxtJBVf == atHIJWQCiT){QSMGAIPHXN = true;}
      else if(atHIJWQCiT == zwPVxtJBVf){sQDlnbzDnW = true;}
      if(ScqMQguAWK == TocbgLUHep){ArRAuIDIeB = true;}
      else if(TocbgLUHep == ScqMQguAWK){CfaMLnELtf = true;}
      if(izIuWJwJst == dnfpMGDtmF){EfBWYRXbxY = true;}
      else if(dnfpMGDtmF == izIuWJwJst){SPAdjCMeli = true;}
      if(eLDiKwxUwp == ynnwuLeWqZ){rNhldnxMGo = true;}
      else if(ynnwuLeWqZ == eLDiKwxUwp){ckptaFtwKb = true;}
      if(bwTJCADJdr == saCJqRzsbg){DSxQIEwZsy = true;}
      else if(saCJqRzsbg == bwTJCADJdr){pQHHppgRLP = true;}
      if(xUhRGznUym == HfMTRlOQuC){TCslHkRogh = true;}
      else if(HfMTRlOQuC == xUhRGznUym){KwDOBdPZBk = true;}
      if(yAIbAHZIBU == SVPdUeBffV){kmKzVmKeWH = true;}
      else if(SVPdUeBffV == yAIbAHZIBU){PUREtRpfkF = true;}
      if(iZDfhmfyrV == fyQEwDlWyu){KqCoykikOU = true;}
      if(GleAxKclcL == HKSGySaUeJ){VxiyEpTues = true;}
      if(HcVIrbnqJu == wNanHXKXnL){WHeXDPIytU = true;}
      while(fyQEwDlWyu == iZDfhmfyrV){sHBRpCHrmt = true;}
      while(HKSGySaUeJ == HKSGySaUeJ){VtSVXfgarx = true;}
      while(wNanHXKXnL == wNanHXKXnL){pUuZLUzCNY = true;}
      if(QSMGAIPHXN == true){QSMGAIPHXN = false;}
      if(ArRAuIDIeB == true){ArRAuIDIeB = false;}
      if(EfBWYRXbxY == true){EfBWYRXbxY = false;}
      if(rNhldnxMGo == true){rNhldnxMGo = false;}
      if(DSxQIEwZsy == true){DSxQIEwZsy = false;}
      if(TCslHkRogh == true){TCslHkRogh = false;}
      if(kmKzVmKeWH == true){kmKzVmKeWH = false;}
      if(KqCoykikOU == true){KqCoykikOU = false;}
      if(VxiyEpTues == true){VxiyEpTues = false;}
      if(WHeXDPIytU == true){WHeXDPIytU = false;}
      if(sQDlnbzDnW == true){sQDlnbzDnW = false;}
      if(CfaMLnELtf == true){CfaMLnELtf = false;}
      if(SPAdjCMeli == true){SPAdjCMeli = false;}
      if(ckptaFtwKb == true){ckptaFtwKb = false;}
      if(pQHHppgRLP == true){pQHHppgRLP = false;}
      if(KwDOBdPZBk == true){KwDOBdPZBk = false;}
      if(PUREtRpfkF == true){PUREtRpfkF = false;}
      if(sHBRpCHrmt == true){sHBRpCHrmt = false;}
      if(VtSVXfgarx == true){VtSVXfgarx = false;}
      if(pUuZLUzCNY == true){pUuZLUzCNY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWKGSAPXMY
{ 
  void jYzIRosRCk()
  { 
      bool QqzEmmufKT = false;
      bool joiHMNYJgN = false;
      bool iSkULeaGRY = false;
      bool WBLMuieCRc = false;
      bool skSwkPxmeM = false;
      bool aWAMYxGdsI = false;
      bool LoOlxhcVLd = false;
      bool iVrDTxAnju = false;
      bool hnaExzBynx = false;
      bool bAIIREWgzD = false;
      bool maaBcFewra = false;
      bool xStyaWNJnx = false;
      bool fdgNBiMilP = false;
      bool aSnfIGMZbr = false;
      bool UFGMzJGKgt = false;
      bool pMrBXIsNzt = false;
      bool ruJbzddNpU = false;
      bool JnhwcZXUNq = false;
      bool bCCrZOamIA = false;
      bool MzZgzYwdMU = false;
      string YtrIStgPVq;
      string iwwDVqGhzz;
      string xElqKxhqze;
      string uYkNWclSmE;
      string hobkfqZPkM;
      string AEMlwUIByU;
      string MpQqwKLhgs;
      string EnuuQIbAKT;
      string XSGmepMzRC;
      string TkURrrXkoV;
      string eqirHLJRUm;
      string rHqewtidLF;
      string yMQeYTTcCY;
      string jqLonfiNeS;
      string guddJMspVy;
      string ItYiXSaDTm;
      string rfOwDBuCpQ;
      string KVyrYDilUM;
      string ZdHEPoRcQU;
      string FftraAfgaI;
      if(YtrIStgPVq == eqirHLJRUm){QqzEmmufKT = true;}
      else if(eqirHLJRUm == YtrIStgPVq){maaBcFewra = true;}
      if(iwwDVqGhzz == rHqewtidLF){joiHMNYJgN = true;}
      else if(rHqewtidLF == iwwDVqGhzz){xStyaWNJnx = true;}
      if(xElqKxhqze == yMQeYTTcCY){iSkULeaGRY = true;}
      else if(yMQeYTTcCY == xElqKxhqze){fdgNBiMilP = true;}
      if(uYkNWclSmE == jqLonfiNeS){WBLMuieCRc = true;}
      else if(jqLonfiNeS == uYkNWclSmE){aSnfIGMZbr = true;}
      if(hobkfqZPkM == guddJMspVy){skSwkPxmeM = true;}
      else if(guddJMspVy == hobkfqZPkM){UFGMzJGKgt = true;}
      if(AEMlwUIByU == ItYiXSaDTm){aWAMYxGdsI = true;}
      else if(ItYiXSaDTm == AEMlwUIByU){pMrBXIsNzt = true;}
      if(MpQqwKLhgs == rfOwDBuCpQ){LoOlxhcVLd = true;}
      else if(rfOwDBuCpQ == MpQqwKLhgs){ruJbzddNpU = true;}
      if(EnuuQIbAKT == KVyrYDilUM){iVrDTxAnju = true;}
      if(XSGmepMzRC == ZdHEPoRcQU){hnaExzBynx = true;}
      if(TkURrrXkoV == FftraAfgaI){bAIIREWgzD = true;}
      while(KVyrYDilUM == EnuuQIbAKT){JnhwcZXUNq = true;}
      while(ZdHEPoRcQU == ZdHEPoRcQU){bCCrZOamIA = true;}
      while(FftraAfgaI == FftraAfgaI){MzZgzYwdMU = true;}
      if(QqzEmmufKT == true){QqzEmmufKT = false;}
      if(joiHMNYJgN == true){joiHMNYJgN = false;}
      if(iSkULeaGRY == true){iSkULeaGRY = false;}
      if(WBLMuieCRc == true){WBLMuieCRc = false;}
      if(skSwkPxmeM == true){skSwkPxmeM = false;}
      if(aWAMYxGdsI == true){aWAMYxGdsI = false;}
      if(LoOlxhcVLd == true){LoOlxhcVLd = false;}
      if(iVrDTxAnju == true){iVrDTxAnju = false;}
      if(hnaExzBynx == true){hnaExzBynx = false;}
      if(bAIIREWgzD == true){bAIIREWgzD = false;}
      if(maaBcFewra == true){maaBcFewra = false;}
      if(xStyaWNJnx == true){xStyaWNJnx = false;}
      if(fdgNBiMilP == true){fdgNBiMilP = false;}
      if(aSnfIGMZbr == true){aSnfIGMZbr = false;}
      if(UFGMzJGKgt == true){UFGMzJGKgt = false;}
      if(pMrBXIsNzt == true){pMrBXIsNzt = false;}
      if(ruJbzddNpU == true){ruJbzddNpU = false;}
      if(JnhwcZXUNq == true){JnhwcZXUNq = false;}
      if(bCCrZOamIA == true){bCCrZOamIA = false;}
      if(MzZgzYwdMU == true){MzZgzYwdMU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCVRQWROYW
{ 
  void nPrruMxYpY()
  { 
      bool GneHpefOIr = false;
      bool OoLfVtWJic = false;
      bool yXNRLckrCf = false;
      bool dpIMwUMSBA = false;
      bool AlpXlopHqb = false;
      bool fgUbTiZMuM = false;
      bool snMcOXgyjA = false;
      bool hEIicLgpfW = false;
      bool ldAazwVgrN = false;
      bool uzWnGMZNIN = false;
      bool HqXqsbYkzI = false;
      bool BigXZPnldR = false;
      bool CAGVFhgUbQ = false;
      bool lTgSPuFJgW = false;
      bool XjhjLMSyNq = false;
      bool XmjqLGkBkL = false;
      bool tEJhWhBOIe = false;
      bool JeFGtRSVJs = false;
      bool PhGjryipHI = false;
      bool JDXUcTazNd = false;
      string VgXymcNGbj;
      string JmluAqxwOb;
      string neyImEVbHR;
      string gkFUubojDD;
      string njaeBFtnnH;
      string lMameqiPKh;
      string HkzJCYgQAY;
      string BNsKmDETGh;
      string KgmzeTJSpE;
      string rZYUwCkQbc;
      string XdmPGYTQzb;
      string mPIbXZyzdi;
      string OOawfanXOj;
      string SmrdKgsXsG;
      string zsTNRcRwxW;
      string EllrNJCqie;
      string kwBOJzWdRp;
      string fZFXiVuMeC;
      string IqZqefBzPA;
      string dCnNVDqEER;
      if(VgXymcNGbj == XdmPGYTQzb){GneHpefOIr = true;}
      else if(XdmPGYTQzb == VgXymcNGbj){HqXqsbYkzI = true;}
      if(JmluAqxwOb == mPIbXZyzdi){OoLfVtWJic = true;}
      else if(mPIbXZyzdi == JmluAqxwOb){BigXZPnldR = true;}
      if(neyImEVbHR == OOawfanXOj){yXNRLckrCf = true;}
      else if(OOawfanXOj == neyImEVbHR){CAGVFhgUbQ = true;}
      if(gkFUubojDD == SmrdKgsXsG){dpIMwUMSBA = true;}
      else if(SmrdKgsXsG == gkFUubojDD){lTgSPuFJgW = true;}
      if(njaeBFtnnH == zsTNRcRwxW){AlpXlopHqb = true;}
      else if(zsTNRcRwxW == njaeBFtnnH){XjhjLMSyNq = true;}
      if(lMameqiPKh == EllrNJCqie){fgUbTiZMuM = true;}
      else if(EllrNJCqie == lMameqiPKh){XmjqLGkBkL = true;}
      if(HkzJCYgQAY == kwBOJzWdRp){snMcOXgyjA = true;}
      else if(kwBOJzWdRp == HkzJCYgQAY){tEJhWhBOIe = true;}
      if(BNsKmDETGh == fZFXiVuMeC){hEIicLgpfW = true;}
      if(KgmzeTJSpE == IqZqefBzPA){ldAazwVgrN = true;}
      if(rZYUwCkQbc == dCnNVDqEER){uzWnGMZNIN = true;}
      while(fZFXiVuMeC == BNsKmDETGh){JeFGtRSVJs = true;}
      while(IqZqefBzPA == IqZqefBzPA){PhGjryipHI = true;}
      while(dCnNVDqEER == dCnNVDqEER){JDXUcTazNd = true;}
      if(GneHpefOIr == true){GneHpefOIr = false;}
      if(OoLfVtWJic == true){OoLfVtWJic = false;}
      if(yXNRLckrCf == true){yXNRLckrCf = false;}
      if(dpIMwUMSBA == true){dpIMwUMSBA = false;}
      if(AlpXlopHqb == true){AlpXlopHqb = false;}
      if(fgUbTiZMuM == true){fgUbTiZMuM = false;}
      if(snMcOXgyjA == true){snMcOXgyjA = false;}
      if(hEIicLgpfW == true){hEIicLgpfW = false;}
      if(ldAazwVgrN == true){ldAazwVgrN = false;}
      if(uzWnGMZNIN == true){uzWnGMZNIN = false;}
      if(HqXqsbYkzI == true){HqXqsbYkzI = false;}
      if(BigXZPnldR == true){BigXZPnldR = false;}
      if(CAGVFhgUbQ == true){CAGVFhgUbQ = false;}
      if(lTgSPuFJgW == true){lTgSPuFJgW = false;}
      if(XjhjLMSyNq == true){XjhjLMSyNq = false;}
      if(XmjqLGkBkL == true){XmjqLGkBkL = false;}
      if(tEJhWhBOIe == true){tEJhWhBOIe = false;}
      if(JeFGtRSVJs == true){JeFGtRSVJs = false;}
      if(PhGjryipHI == true){PhGjryipHI = false;}
      if(JDXUcTazNd == true){JDXUcTazNd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KZSWXNGHZG
{ 
  void HQOZHgzGBI()
  { 
      bool IMWsETtyXU = false;
      bool SmBwXPwkOZ = false;
      bool VixqDjkgsi = false;
      bool pZiJpTgMRM = false;
      bool NkjsorPGkg = false;
      bool wKfJIYPepU = false;
      bool iNEoerEqFE = false;
      bool iiSCMjyDBK = false;
      bool TduMlesZAQ = false;
      bool EBWxdzguNw = false;
      bool nXBgxMrdwY = false;
      bool aMdeAFSqCA = false;
      bool zeqnzgMUXN = false;
      bool CDoEWwcNOZ = false;
      bool lOcbprXrxY = false;
      bool gorMxIgMhQ = false;
      bool AXGhVWWYHE = false;
      bool cEbcOjBPyH = false;
      bool ITXzgMLbHO = false;
      bool PPfyYOIuFS = false;
      string lanpspOjPA;
      string jxnCWSGaWO;
      string OlzotwRiBw;
      string yIEJPZFOti;
      string bbPWXuUzpY;
      string lRVYPAazuw;
      string YfiSCbselw;
      string MrgmlmVcRz;
      string bSrbKfletO;
      string yGSxKwrxUu;
      string CpMsLskimb;
      string dygwUFmGHV;
      string oNjXyGZibp;
      string tYHVxkFyPQ;
      string tDrRjzYVcE;
      string IlozGnFouF;
      string TCHwhFqLzi;
      string AnqqakVSny;
      string gDGWgHjIOI;
      string fQDJxruuid;
      if(lanpspOjPA == CpMsLskimb){IMWsETtyXU = true;}
      else if(CpMsLskimb == lanpspOjPA){nXBgxMrdwY = true;}
      if(jxnCWSGaWO == dygwUFmGHV){SmBwXPwkOZ = true;}
      else if(dygwUFmGHV == jxnCWSGaWO){aMdeAFSqCA = true;}
      if(OlzotwRiBw == oNjXyGZibp){VixqDjkgsi = true;}
      else if(oNjXyGZibp == OlzotwRiBw){zeqnzgMUXN = true;}
      if(yIEJPZFOti == tYHVxkFyPQ){pZiJpTgMRM = true;}
      else if(tYHVxkFyPQ == yIEJPZFOti){CDoEWwcNOZ = true;}
      if(bbPWXuUzpY == tDrRjzYVcE){NkjsorPGkg = true;}
      else if(tDrRjzYVcE == bbPWXuUzpY){lOcbprXrxY = true;}
      if(lRVYPAazuw == IlozGnFouF){wKfJIYPepU = true;}
      else if(IlozGnFouF == lRVYPAazuw){gorMxIgMhQ = true;}
      if(YfiSCbselw == TCHwhFqLzi){iNEoerEqFE = true;}
      else if(TCHwhFqLzi == YfiSCbselw){AXGhVWWYHE = true;}
      if(MrgmlmVcRz == AnqqakVSny){iiSCMjyDBK = true;}
      if(bSrbKfletO == gDGWgHjIOI){TduMlesZAQ = true;}
      if(yGSxKwrxUu == fQDJxruuid){EBWxdzguNw = true;}
      while(AnqqakVSny == MrgmlmVcRz){cEbcOjBPyH = true;}
      while(gDGWgHjIOI == gDGWgHjIOI){ITXzgMLbHO = true;}
      while(fQDJxruuid == fQDJxruuid){PPfyYOIuFS = true;}
      if(IMWsETtyXU == true){IMWsETtyXU = false;}
      if(SmBwXPwkOZ == true){SmBwXPwkOZ = false;}
      if(VixqDjkgsi == true){VixqDjkgsi = false;}
      if(pZiJpTgMRM == true){pZiJpTgMRM = false;}
      if(NkjsorPGkg == true){NkjsorPGkg = false;}
      if(wKfJIYPepU == true){wKfJIYPepU = false;}
      if(iNEoerEqFE == true){iNEoerEqFE = false;}
      if(iiSCMjyDBK == true){iiSCMjyDBK = false;}
      if(TduMlesZAQ == true){TduMlesZAQ = false;}
      if(EBWxdzguNw == true){EBWxdzguNw = false;}
      if(nXBgxMrdwY == true){nXBgxMrdwY = false;}
      if(aMdeAFSqCA == true){aMdeAFSqCA = false;}
      if(zeqnzgMUXN == true){zeqnzgMUXN = false;}
      if(CDoEWwcNOZ == true){CDoEWwcNOZ = false;}
      if(lOcbprXrxY == true){lOcbprXrxY = false;}
      if(gorMxIgMhQ == true){gorMxIgMhQ = false;}
      if(AXGhVWWYHE == true){AXGhVWWYHE = false;}
      if(cEbcOjBPyH == true){cEbcOjBPyH = false;}
      if(ITXzgMLbHO == true){ITXzgMLbHO = false;}
      if(PPfyYOIuFS == true){PPfyYOIuFS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LEYDMKMWDH
{ 
  void LgZmjwQtKM()
  { 
      bool rWWKYNdwkT = false;
      bool BZicOFPWbM = false;
      bool LiANgyORNp = false;
      bool MgUTIEADzc = false;
      bool emTGGSSewa = false;
      bool TJTwTIWIca = false;
      bool yMitHUEOUK = false;
      bool FMWzhXPsGN = false;
      bool ejVlWCMXAz = false;
      bool hqaXdRDYzl = false;
      bool OEKlVHlUOu = false;
      bool scBOuOpxXE = false;
      bool HfNUbNkzUP = false;
      bool UptTzaZjPO = false;
      bool QqJFGFoLcO = false;
      bool bGBtehpoJI = false;
      bool VmAyaChgOU = false;
      bool oGhInQVIOW = false;
      bool YZVGnNoAoR = false;
      bool jjZHsdqLdD = false;
      string LIWqgAhPTA;
      string LPmKUcluxR;
      string rUpoZzXaRN;
      string WWSLmCrSon;
      string ylzbUSoedz;
      string LhCLrqRhQg;
      string cGyFcnxbWR;
      string jSFISFUOTH;
      string KrxRCoUGSw;
      string jKCHKrntyf;
      string UNILPsbsrm;
      string VDNIWkIfDm;
      string TqJZhYQyyZ;
      string QaPmlwjlCJ;
      string NaNeagxsjZ;
      string jHpKMdDhdq;
      string bduRVunaWZ;
      string AWdtZrcdzB;
      string bWNXpIjEaI;
      string sCHLgjfwJe;
      if(LIWqgAhPTA == UNILPsbsrm){rWWKYNdwkT = true;}
      else if(UNILPsbsrm == LIWqgAhPTA){OEKlVHlUOu = true;}
      if(LPmKUcluxR == VDNIWkIfDm){BZicOFPWbM = true;}
      else if(VDNIWkIfDm == LPmKUcluxR){scBOuOpxXE = true;}
      if(rUpoZzXaRN == TqJZhYQyyZ){LiANgyORNp = true;}
      else if(TqJZhYQyyZ == rUpoZzXaRN){HfNUbNkzUP = true;}
      if(WWSLmCrSon == QaPmlwjlCJ){MgUTIEADzc = true;}
      else if(QaPmlwjlCJ == WWSLmCrSon){UptTzaZjPO = true;}
      if(ylzbUSoedz == NaNeagxsjZ){emTGGSSewa = true;}
      else if(NaNeagxsjZ == ylzbUSoedz){QqJFGFoLcO = true;}
      if(LhCLrqRhQg == jHpKMdDhdq){TJTwTIWIca = true;}
      else if(jHpKMdDhdq == LhCLrqRhQg){bGBtehpoJI = true;}
      if(cGyFcnxbWR == bduRVunaWZ){yMitHUEOUK = true;}
      else if(bduRVunaWZ == cGyFcnxbWR){VmAyaChgOU = true;}
      if(jSFISFUOTH == AWdtZrcdzB){FMWzhXPsGN = true;}
      if(KrxRCoUGSw == bWNXpIjEaI){ejVlWCMXAz = true;}
      if(jKCHKrntyf == sCHLgjfwJe){hqaXdRDYzl = true;}
      while(AWdtZrcdzB == jSFISFUOTH){oGhInQVIOW = true;}
      while(bWNXpIjEaI == bWNXpIjEaI){YZVGnNoAoR = true;}
      while(sCHLgjfwJe == sCHLgjfwJe){jjZHsdqLdD = true;}
      if(rWWKYNdwkT == true){rWWKYNdwkT = false;}
      if(BZicOFPWbM == true){BZicOFPWbM = false;}
      if(LiANgyORNp == true){LiANgyORNp = false;}
      if(MgUTIEADzc == true){MgUTIEADzc = false;}
      if(emTGGSSewa == true){emTGGSSewa = false;}
      if(TJTwTIWIca == true){TJTwTIWIca = false;}
      if(yMitHUEOUK == true){yMitHUEOUK = false;}
      if(FMWzhXPsGN == true){FMWzhXPsGN = false;}
      if(ejVlWCMXAz == true){ejVlWCMXAz = false;}
      if(hqaXdRDYzl == true){hqaXdRDYzl = false;}
      if(OEKlVHlUOu == true){OEKlVHlUOu = false;}
      if(scBOuOpxXE == true){scBOuOpxXE = false;}
      if(HfNUbNkzUP == true){HfNUbNkzUP = false;}
      if(UptTzaZjPO == true){UptTzaZjPO = false;}
      if(QqJFGFoLcO == true){QqJFGFoLcO = false;}
      if(bGBtehpoJI == true){bGBtehpoJI = false;}
      if(VmAyaChgOU == true){VmAyaChgOU = false;}
      if(oGhInQVIOW == true){oGhInQVIOW = false;}
      if(YZVGnNoAoR == true){YZVGnNoAoR = false;}
      if(jjZHsdqLdD == true){jjZHsdqLdD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WBHUMBJKJH
{ 
  void WOglDVekBr()
  { 
      bool QpnYaEnqSA = false;
      bool grBXZHHUys = false;
      bool WmZONoVRgO = false;
      bool QFXGucuCHl = false;
      bool ERWzWQSZiG = false;
      bool VWBKXcPYKl = false;
      bool iVKEjaUucx = false;
      bool LENMoFQaqw = false;
      bool VuhZrsDMhR = false;
      bool MVrVChHRPu = false;
      bool wXxltQJoVR = false;
      bool MohOPmnjLp = false;
      bool XHMKkoMrJH = false;
      bool yzKuAyxwfa = false;
      bool jOpQFWndGP = false;
      bool tWFYXnLlAE = false;
      bool EQeOTMdlNQ = false;
      bool oqDkFJRwFN = false;
      bool BiktMaslXL = false;
      bool mLwaWSibwr = false;
      string ItZocEWLNN;
      string FjphtAKdyy;
      string KDBODLPtya;
      string qfrjFQNDLJ;
      string FHXlobtJUQ;
      string oXLxyEsKlQ;
      string ocMlWZqFcd;
      string mHRnrDePZb;
      string RFZglSTulA;
      string XCQuUcukOP;
      string jngpdgGXFt;
      string YdkKziDezE;
      string FwTcGjpWTP;
      string ItAKqcYiDF;
      string MwpqatQGuk;
      string YPkKJmTDjs;
      string qiDolecaSW;
      string KUbtqIGbCL;
      string SibhprIoAE;
      string IUyJNcrAEu;
      if(ItZocEWLNN == jngpdgGXFt){QpnYaEnqSA = true;}
      else if(jngpdgGXFt == ItZocEWLNN){wXxltQJoVR = true;}
      if(FjphtAKdyy == YdkKziDezE){grBXZHHUys = true;}
      else if(YdkKziDezE == FjphtAKdyy){MohOPmnjLp = true;}
      if(KDBODLPtya == FwTcGjpWTP){WmZONoVRgO = true;}
      else if(FwTcGjpWTP == KDBODLPtya){XHMKkoMrJH = true;}
      if(qfrjFQNDLJ == ItAKqcYiDF){QFXGucuCHl = true;}
      else if(ItAKqcYiDF == qfrjFQNDLJ){yzKuAyxwfa = true;}
      if(FHXlobtJUQ == MwpqatQGuk){ERWzWQSZiG = true;}
      else if(MwpqatQGuk == FHXlobtJUQ){jOpQFWndGP = true;}
      if(oXLxyEsKlQ == YPkKJmTDjs){VWBKXcPYKl = true;}
      else if(YPkKJmTDjs == oXLxyEsKlQ){tWFYXnLlAE = true;}
      if(ocMlWZqFcd == qiDolecaSW){iVKEjaUucx = true;}
      else if(qiDolecaSW == ocMlWZqFcd){EQeOTMdlNQ = true;}
      if(mHRnrDePZb == KUbtqIGbCL){LENMoFQaqw = true;}
      if(RFZglSTulA == SibhprIoAE){VuhZrsDMhR = true;}
      if(XCQuUcukOP == IUyJNcrAEu){MVrVChHRPu = true;}
      while(KUbtqIGbCL == mHRnrDePZb){oqDkFJRwFN = true;}
      while(SibhprIoAE == SibhprIoAE){BiktMaslXL = true;}
      while(IUyJNcrAEu == IUyJNcrAEu){mLwaWSibwr = true;}
      if(QpnYaEnqSA == true){QpnYaEnqSA = false;}
      if(grBXZHHUys == true){grBXZHHUys = false;}
      if(WmZONoVRgO == true){WmZONoVRgO = false;}
      if(QFXGucuCHl == true){QFXGucuCHl = false;}
      if(ERWzWQSZiG == true){ERWzWQSZiG = false;}
      if(VWBKXcPYKl == true){VWBKXcPYKl = false;}
      if(iVKEjaUucx == true){iVKEjaUucx = false;}
      if(LENMoFQaqw == true){LENMoFQaqw = false;}
      if(VuhZrsDMhR == true){VuhZrsDMhR = false;}
      if(MVrVChHRPu == true){MVrVChHRPu = false;}
      if(wXxltQJoVR == true){wXxltQJoVR = false;}
      if(MohOPmnjLp == true){MohOPmnjLp = false;}
      if(XHMKkoMrJH == true){XHMKkoMrJH = false;}
      if(yzKuAyxwfa == true){yzKuAyxwfa = false;}
      if(jOpQFWndGP == true){jOpQFWndGP = false;}
      if(tWFYXnLlAE == true){tWFYXnLlAE = false;}
      if(EQeOTMdlNQ == true){EQeOTMdlNQ = false;}
      if(oqDkFJRwFN == true){oqDkFJRwFN = false;}
      if(BiktMaslXL == true){BiktMaslXL = false;}
      if(mLwaWSibwr == true){mLwaWSibwr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FLMALDEULB
{ 
  void TcHISOAJhX()
  { 
      bool PFWUFlGtZG = false;
      bool jusoMIyasJ = false;
      bool HTQZfOUHIJ = false;
      bool rQDbVFGYCB = false;
      bool WfcxxRwnzK = false;
      bool LIURGunwnq = false;
      bool RykPOSrRSG = false;
      bool BZXrmbqScO = false;
      bool RfHyyiulUa = false;
      bool RKjLiXtMid = false;
      bool YeVrJkkcee = false;
      bool EVTZYkpmRe = false;
      bool WGwroppLIO = false;
      bool gdjyolKPoM = false;
      bool ySHpVwqJmx = false;
      bool gHtDGSidCS = false;
      bool uYTPxakUkm = false;
      bool aaxFgEzFVs = false;
      bool zfYKhZifrV = false;
      bool DgNWRYyqru = false;
      string FfdfGNfUIY;
      string xfTTOVGjct;
      string JczHtTjdVe;
      string BgIYElDShT;
      string mcemrKNmbb;
      string gALKVbfVlm;
      string cCydWPWtOc;
      string SnBJHgxMOi;
      string GxBtxAVyCb;
      string FgfupjdBPc;
      string mSXyJsyCDo;
      string eTHCgeAEfV;
      string tYrmXkHGSW;
      string CwwlumZDjE;
      string BStNxlZdNK;
      string iZVthOZjZX;
      string lqiflhWUHs;
      string ExTaTbeepk;
      string KdsImcaCEg;
      string NpcMSKiNaO;
      if(FfdfGNfUIY == mSXyJsyCDo){PFWUFlGtZG = true;}
      else if(mSXyJsyCDo == FfdfGNfUIY){YeVrJkkcee = true;}
      if(xfTTOVGjct == eTHCgeAEfV){jusoMIyasJ = true;}
      else if(eTHCgeAEfV == xfTTOVGjct){EVTZYkpmRe = true;}
      if(JczHtTjdVe == tYrmXkHGSW){HTQZfOUHIJ = true;}
      else if(tYrmXkHGSW == JczHtTjdVe){WGwroppLIO = true;}
      if(BgIYElDShT == CwwlumZDjE){rQDbVFGYCB = true;}
      else if(CwwlumZDjE == BgIYElDShT){gdjyolKPoM = true;}
      if(mcemrKNmbb == BStNxlZdNK){WfcxxRwnzK = true;}
      else if(BStNxlZdNK == mcemrKNmbb){ySHpVwqJmx = true;}
      if(gALKVbfVlm == iZVthOZjZX){LIURGunwnq = true;}
      else if(iZVthOZjZX == gALKVbfVlm){gHtDGSidCS = true;}
      if(cCydWPWtOc == lqiflhWUHs){RykPOSrRSG = true;}
      else if(lqiflhWUHs == cCydWPWtOc){uYTPxakUkm = true;}
      if(SnBJHgxMOi == ExTaTbeepk){BZXrmbqScO = true;}
      if(GxBtxAVyCb == KdsImcaCEg){RfHyyiulUa = true;}
      if(FgfupjdBPc == NpcMSKiNaO){RKjLiXtMid = true;}
      while(ExTaTbeepk == SnBJHgxMOi){aaxFgEzFVs = true;}
      while(KdsImcaCEg == KdsImcaCEg){zfYKhZifrV = true;}
      while(NpcMSKiNaO == NpcMSKiNaO){DgNWRYyqru = true;}
      if(PFWUFlGtZG == true){PFWUFlGtZG = false;}
      if(jusoMIyasJ == true){jusoMIyasJ = false;}
      if(HTQZfOUHIJ == true){HTQZfOUHIJ = false;}
      if(rQDbVFGYCB == true){rQDbVFGYCB = false;}
      if(WfcxxRwnzK == true){WfcxxRwnzK = false;}
      if(LIURGunwnq == true){LIURGunwnq = false;}
      if(RykPOSrRSG == true){RykPOSrRSG = false;}
      if(BZXrmbqScO == true){BZXrmbqScO = false;}
      if(RfHyyiulUa == true){RfHyyiulUa = false;}
      if(RKjLiXtMid == true){RKjLiXtMid = false;}
      if(YeVrJkkcee == true){YeVrJkkcee = false;}
      if(EVTZYkpmRe == true){EVTZYkpmRe = false;}
      if(WGwroppLIO == true){WGwroppLIO = false;}
      if(gdjyolKPoM == true){gdjyolKPoM = false;}
      if(ySHpVwqJmx == true){ySHpVwqJmx = false;}
      if(gHtDGSidCS == true){gHtDGSidCS = false;}
      if(uYTPxakUkm == true){uYTPxakUkm = false;}
      if(aaxFgEzFVs == true){aaxFgEzFVs = false;}
      if(zfYKhZifrV == true){zfYKhZifrV = false;}
      if(DgNWRYyqru == true){DgNWRYyqru = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGQZKUMIYG
{ 
  void UyqJVJRICP()
  { 
      bool nazfumbYjX = false;
      bool SxdwjeMLIQ = false;
      bool pFXcOtIVcB = false;
      bool ABSHhpGCMV = false;
      bool EGaSgKqnaM = false;
      bool saCEVhDWRA = false;
      bool dGwhXReWOs = false;
      bool XJylLjeEuD = false;
      bool CUuPIZyNlz = false;
      bool mjkMryKruP = false;
      bool fUYgnibPrl = false;
      bool DzaNxJLfZx = false;
      bool SQkPGmYltN = false;
      bool ZmIeXhuNaY = false;
      bool xiVzwnIWOi = false;
      bool ldSxxPjJaA = false;
      bool KoUdMPpwpP = false;
      bool NxFAAjtkSR = false;
      bool eBXLawUKhH = false;
      bool ykmaOHNrmf = false;
      string SYoCsSqPdZ;
      string qsGexDHgSx;
      string UEBKupKtxh;
      string dzRstwmoXD;
      string bYlxzwFmuZ;
      string krDekNXeGC;
      string HwSuuqbNjA;
      string PRIPVwRELz;
      string kXyWxlwlHf;
      string YIiVueFqBH;
      string TqCtJTinIo;
      string wTSHRjxuxJ;
      string uoGEbHhmTq;
      string qZCDesUDNc;
      string CHcSiFpbEK;
      string gJsqLekySC;
      string kwURxWQOcX;
      string PthUHnLmUV;
      string RGiIJgfKqz;
      string IVkLqFmKUM;
      if(SYoCsSqPdZ == TqCtJTinIo){nazfumbYjX = true;}
      else if(TqCtJTinIo == SYoCsSqPdZ){fUYgnibPrl = true;}
      if(qsGexDHgSx == wTSHRjxuxJ){SxdwjeMLIQ = true;}
      else if(wTSHRjxuxJ == qsGexDHgSx){DzaNxJLfZx = true;}
      if(UEBKupKtxh == uoGEbHhmTq){pFXcOtIVcB = true;}
      else if(uoGEbHhmTq == UEBKupKtxh){SQkPGmYltN = true;}
      if(dzRstwmoXD == qZCDesUDNc){ABSHhpGCMV = true;}
      else if(qZCDesUDNc == dzRstwmoXD){ZmIeXhuNaY = true;}
      if(bYlxzwFmuZ == CHcSiFpbEK){EGaSgKqnaM = true;}
      else if(CHcSiFpbEK == bYlxzwFmuZ){xiVzwnIWOi = true;}
      if(krDekNXeGC == gJsqLekySC){saCEVhDWRA = true;}
      else if(gJsqLekySC == krDekNXeGC){ldSxxPjJaA = true;}
      if(HwSuuqbNjA == kwURxWQOcX){dGwhXReWOs = true;}
      else if(kwURxWQOcX == HwSuuqbNjA){KoUdMPpwpP = true;}
      if(PRIPVwRELz == PthUHnLmUV){XJylLjeEuD = true;}
      if(kXyWxlwlHf == RGiIJgfKqz){CUuPIZyNlz = true;}
      if(YIiVueFqBH == IVkLqFmKUM){mjkMryKruP = true;}
      while(PthUHnLmUV == PRIPVwRELz){NxFAAjtkSR = true;}
      while(RGiIJgfKqz == RGiIJgfKqz){eBXLawUKhH = true;}
      while(IVkLqFmKUM == IVkLqFmKUM){ykmaOHNrmf = true;}
      if(nazfumbYjX == true){nazfumbYjX = false;}
      if(SxdwjeMLIQ == true){SxdwjeMLIQ = false;}
      if(pFXcOtIVcB == true){pFXcOtIVcB = false;}
      if(ABSHhpGCMV == true){ABSHhpGCMV = false;}
      if(EGaSgKqnaM == true){EGaSgKqnaM = false;}
      if(saCEVhDWRA == true){saCEVhDWRA = false;}
      if(dGwhXReWOs == true){dGwhXReWOs = false;}
      if(XJylLjeEuD == true){XJylLjeEuD = false;}
      if(CUuPIZyNlz == true){CUuPIZyNlz = false;}
      if(mjkMryKruP == true){mjkMryKruP = false;}
      if(fUYgnibPrl == true){fUYgnibPrl = false;}
      if(DzaNxJLfZx == true){DzaNxJLfZx = false;}
      if(SQkPGmYltN == true){SQkPGmYltN = false;}
      if(ZmIeXhuNaY == true){ZmIeXhuNaY = false;}
      if(xiVzwnIWOi == true){xiVzwnIWOi = false;}
      if(ldSxxPjJaA == true){ldSxxPjJaA = false;}
      if(KoUdMPpwpP == true){KoUdMPpwpP = false;}
      if(NxFAAjtkSR == true){NxFAAjtkSR = false;}
      if(eBXLawUKhH == true){eBXLawUKhH = false;}
      if(ykmaOHNrmf == true){ykmaOHNrmf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOGECJCNON
{ 
  void UTCrOxjibS()
  { 
      bool dotDAzFmOc = false;
      bool YNuYeWntUF = false;
      bool xFUALLADQM = false;
      bool dhQDEjhTFI = false;
      bool sbihROaTUZ = false;
      bool bIGDoYUsro = false;
      bool yBVByqwrTu = false;
      bool oUnLMUVliw = false;
      bool jgiqjUaMNf = false;
      bool OoaQJrGgja = false;
      bool RiAYjHUtqU = false;
      bool ChJwERRdRc = false;
      bool PidmfAtXBU = false;
      bool OoCIdBfKHc = false;
      bool AfVsdgedLr = false;
      bool ZbPGKhEMrj = false;
      bool MwsVFNfBRD = false;
      bool lHWocjNkJz = false;
      bool UPMJtmZwyu = false;
      bool wTRWPEmzmP = false;
      string MUHIkHEpAy;
      string XLcEoKBHMz;
      string IFqoVlgkah;
      string otKNjBqmuz;
      string IhdFXzrwLU;
      string ZlCXmGcSly;
      string ZTPRIcBPTn;
      string TNLNqZblQV;
      string sjYGHDrlad;
      string XXAwYnSLxu;
      string xcbXALaofM;
      string dqBPEpuJJF;
      string kPnpPuMOoC;
      string HQoVYQHBFw;
      string bDFNAgVkri;
      string sJBqKhnkHF;
      string zLAdEMCfqn;
      string htDNcgJZpi;
      string ZbWFIyPxLp;
      string cWsAwQDbJm;
      if(MUHIkHEpAy == xcbXALaofM){dotDAzFmOc = true;}
      else if(xcbXALaofM == MUHIkHEpAy){RiAYjHUtqU = true;}
      if(XLcEoKBHMz == dqBPEpuJJF){YNuYeWntUF = true;}
      else if(dqBPEpuJJF == XLcEoKBHMz){ChJwERRdRc = true;}
      if(IFqoVlgkah == kPnpPuMOoC){xFUALLADQM = true;}
      else if(kPnpPuMOoC == IFqoVlgkah){PidmfAtXBU = true;}
      if(otKNjBqmuz == HQoVYQHBFw){dhQDEjhTFI = true;}
      else if(HQoVYQHBFw == otKNjBqmuz){OoCIdBfKHc = true;}
      if(IhdFXzrwLU == bDFNAgVkri){sbihROaTUZ = true;}
      else if(bDFNAgVkri == IhdFXzrwLU){AfVsdgedLr = true;}
      if(ZlCXmGcSly == sJBqKhnkHF){bIGDoYUsro = true;}
      else if(sJBqKhnkHF == ZlCXmGcSly){ZbPGKhEMrj = true;}
      if(ZTPRIcBPTn == zLAdEMCfqn){yBVByqwrTu = true;}
      else if(zLAdEMCfqn == ZTPRIcBPTn){MwsVFNfBRD = true;}
      if(TNLNqZblQV == htDNcgJZpi){oUnLMUVliw = true;}
      if(sjYGHDrlad == ZbWFIyPxLp){jgiqjUaMNf = true;}
      if(XXAwYnSLxu == cWsAwQDbJm){OoaQJrGgja = true;}
      while(htDNcgJZpi == TNLNqZblQV){lHWocjNkJz = true;}
      while(ZbWFIyPxLp == ZbWFIyPxLp){UPMJtmZwyu = true;}
      while(cWsAwQDbJm == cWsAwQDbJm){wTRWPEmzmP = true;}
      if(dotDAzFmOc == true){dotDAzFmOc = false;}
      if(YNuYeWntUF == true){YNuYeWntUF = false;}
      if(xFUALLADQM == true){xFUALLADQM = false;}
      if(dhQDEjhTFI == true){dhQDEjhTFI = false;}
      if(sbihROaTUZ == true){sbihROaTUZ = false;}
      if(bIGDoYUsro == true){bIGDoYUsro = false;}
      if(yBVByqwrTu == true){yBVByqwrTu = false;}
      if(oUnLMUVliw == true){oUnLMUVliw = false;}
      if(jgiqjUaMNf == true){jgiqjUaMNf = false;}
      if(OoaQJrGgja == true){OoaQJrGgja = false;}
      if(RiAYjHUtqU == true){RiAYjHUtqU = false;}
      if(ChJwERRdRc == true){ChJwERRdRc = false;}
      if(PidmfAtXBU == true){PidmfAtXBU = false;}
      if(OoCIdBfKHc == true){OoCIdBfKHc = false;}
      if(AfVsdgedLr == true){AfVsdgedLr = false;}
      if(ZbPGKhEMrj == true){ZbPGKhEMrj = false;}
      if(MwsVFNfBRD == true){MwsVFNfBRD = false;}
      if(lHWocjNkJz == true){lHWocjNkJz = false;}
      if(UPMJtmZwyu == true){UPMJtmZwyu = false;}
      if(wTRWPEmzmP == true){wTRWPEmzmP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AMVSRGBEWB
{ 
  void PcqTNgdhpK()
  { 
      bool fzSDHRpUGG = false;
      bool wgARWDgEeQ = false;
      bool PpxPLMnHZt = false;
      bool ztMDDIAfWq = false;
      bool CxYnqqVMgJ = false;
      bool qAOdhoBCqt = false;
      bool dhtLHBUwON = false;
      bool DBhnNRRJYU = false;
      bool qaaPDyfhVO = false;
      bool HxnbMUDMfo = false;
      bool WZySGpSaQP = false;
      bool XrdWDDHdIJ = false;
      bool VlazGFMGas = false;
      bool OEcixQbHIN = false;
      bool eFRFqPSQXJ = false;
      bool MYEWTjyzLB = false;
      bool cMzWBSOtYl = false;
      bool aAVudQTVHq = false;
      bool muhRgpAGPN = false;
      bool SbuHjSFuEY = false;
      string OdEhGXpmUQ;
      string EOmRIjzJjk;
      string BDMxYrIVeB;
      string cScNytwIAO;
      string FGyXnsbCBR;
      string EyZMBLQGIO;
      string OUHTnklZTO;
      string nqJVetEoIf;
      string PGTMxerPMl;
      string coAlzkyeiD;
      string HChmdMnEhG;
      string HbxcyIAuWJ;
      string rVMgkzpWVs;
      string wZFFYNXgij;
      string pnhFeBqWnq;
      string kCHZKkoBBe;
      string WQinKgVrDj;
      string jSMmTEnHBi;
      string HSidIsRetn;
      string YWeEMYFsux;
      if(OdEhGXpmUQ == HChmdMnEhG){fzSDHRpUGG = true;}
      else if(HChmdMnEhG == OdEhGXpmUQ){WZySGpSaQP = true;}
      if(EOmRIjzJjk == HbxcyIAuWJ){wgARWDgEeQ = true;}
      else if(HbxcyIAuWJ == EOmRIjzJjk){XrdWDDHdIJ = true;}
      if(BDMxYrIVeB == rVMgkzpWVs){PpxPLMnHZt = true;}
      else if(rVMgkzpWVs == BDMxYrIVeB){VlazGFMGas = true;}
      if(cScNytwIAO == wZFFYNXgij){ztMDDIAfWq = true;}
      else if(wZFFYNXgij == cScNytwIAO){OEcixQbHIN = true;}
      if(FGyXnsbCBR == pnhFeBqWnq){CxYnqqVMgJ = true;}
      else if(pnhFeBqWnq == FGyXnsbCBR){eFRFqPSQXJ = true;}
      if(EyZMBLQGIO == kCHZKkoBBe){qAOdhoBCqt = true;}
      else if(kCHZKkoBBe == EyZMBLQGIO){MYEWTjyzLB = true;}
      if(OUHTnklZTO == WQinKgVrDj){dhtLHBUwON = true;}
      else if(WQinKgVrDj == OUHTnklZTO){cMzWBSOtYl = true;}
      if(nqJVetEoIf == jSMmTEnHBi){DBhnNRRJYU = true;}
      if(PGTMxerPMl == HSidIsRetn){qaaPDyfhVO = true;}
      if(coAlzkyeiD == YWeEMYFsux){HxnbMUDMfo = true;}
      while(jSMmTEnHBi == nqJVetEoIf){aAVudQTVHq = true;}
      while(HSidIsRetn == HSidIsRetn){muhRgpAGPN = true;}
      while(YWeEMYFsux == YWeEMYFsux){SbuHjSFuEY = true;}
      if(fzSDHRpUGG == true){fzSDHRpUGG = false;}
      if(wgARWDgEeQ == true){wgARWDgEeQ = false;}
      if(PpxPLMnHZt == true){PpxPLMnHZt = false;}
      if(ztMDDIAfWq == true){ztMDDIAfWq = false;}
      if(CxYnqqVMgJ == true){CxYnqqVMgJ = false;}
      if(qAOdhoBCqt == true){qAOdhoBCqt = false;}
      if(dhtLHBUwON == true){dhtLHBUwON = false;}
      if(DBhnNRRJYU == true){DBhnNRRJYU = false;}
      if(qaaPDyfhVO == true){qaaPDyfhVO = false;}
      if(HxnbMUDMfo == true){HxnbMUDMfo = false;}
      if(WZySGpSaQP == true){WZySGpSaQP = false;}
      if(XrdWDDHdIJ == true){XrdWDDHdIJ = false;}
      if(VlazGFMGas == true){VlazGFMGas = false;}
      if(OEcixQbHIN == true){OEcixQbHIN = false;}
      if(eFRFqPSQXJ == true){eFRFqPSQXJ = false;}
      if(MYEWTjyzLB == true){MYEWTjyzLB = false;}
      if(cMzWBSOtYl == true){cMzWBSOtYl = false;}
      if(aAVudQTVHq == true){aAVudQTVHq = false;}
      if(muhRgpAGPN == true){muhRgpAGPN = false;}
      if(SbuHjSFuEY == true){SbuHjSFuEY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRWPOBGTDR
{ 
  void TIPmfhAuVG()
  { 
      bool kHDdekqoxf = false;
      bool UbqkctbHEm = false;
      bool NOrOQiMUOs = false;
      bool REkpTPrpLd = false;
      bool ToBFAZzitz = false;
      bool eBCcwWOnNu = false;
      bool XVZDOQpARM = false;
      bool BluaTYMmOq = false;
      bool jcaPOQCItx = false;
      bool BDcQFyOxqi = false;
      bool iyRhxsFaIX = false;
      bool JaZVLttKox = false;
      bool NgGUKxIeVV = false;
      bool KOweIkLsRU = false;
      bool KaAVmZdGFK = false;
      bool DEIsVBrxWz = false;
      bool jaFmMteuNZ = false;
      bool hArTmmgjgj = false;
      bool TCZKRGGCJG = false;
      bool rOWSkjVMJr = false;
      string uyxMOzLzpY;
      string clKpmXpgGF;
      string hHixEpKNFp;
      string xxXnLYHgTA;
      string LqpfShQcIZ;
      string gcyuhmOAHX;
      string oytAafOVdN;
      string QINFtpRCeV;
      string ZgFfIUzbFY;
      string KHYuLMxoFm;
      string TtytJYPrBq;
      string ULVlyHsOqG;
      string glPFDIiRth;
      string sbxqCfiLWi;
      string FGaODykmxD;
      string SixyGgdrpA;
      string pxyTyrNdjS;
      string YhrIBZLBBE;
      string XuUpOKdzkU;
      string BpUWsHIHPK;
      if(uyxMOzLzpY == TtytJYPrBq){kHDdekqoxf = true;}
      else if(TtytJYPrBq == uyxMOzLzpY){iyRhxsFaIX = true;}
      if(clKpmXpgGF == ULVlyHsOqG){UbqkctbHEm = true;}
      else if(ULVlyHsOqG == clKpmXpgGF){JaZVLttKox = true;}
      if(hHixEpKNFp == glPFDIiRth){NOrOQiMUOs = true;}
      else if(glPFDIiRth == hHixEpKNFp){NgGUKxIeVV = true;}
      if(xxXnLYHgTA == sbxqCfiLWi){REkpTPrpLd = true;}
      else if(sbxqCfiLWi == xxXnLYHgTA){KOweIkLsRU = true;}
      if(LqpfShQcIZ == FGaODykmxD){ToBFAZzitz = true;}
      else if(FGaODykmxD == LqpfShQcIZ){KaAVmZdGFK = true;}
      if(gcyuhmOAHX == SixyGgdrpA){eBCcwWOnNu = true;}
      else if(SixyGgdrpA == gcyuhmOAHX){DEIsVBrxWz = true;}
      if(oytAafOVdN == pxyTyrNdjS){XVZDOQpARM = true;}
      else if(pxyTyrNdjS == oytAafOVdN){jaFmMteuNZ = true;}
      if(QINFtpRCeV == YhrIBZLBBE){BluaTYMmOq = true;}
      if(ZgFfIUzbFY == XuUpOKdzkU){jcaPOQCItx = true;}
      if(KHYuLMxoFm == BpUWsHIHPK){BDcQFyOxqi = true;}
      while(YhrIBZLBBE == QINFtpRCeV){hArTmmgjgj = true;}
      while(XuUpOKdzkU == XuUpOKdzkU){TCZKRGGCJG = true;}
      while(BpUWsHIHPK == BpUWsHIHPK){rOWSkjVMJr = true;}
      if(kHDdekqoxf == true){kHDdekqoxf = false;}
      if(UbqkctbHEm == true){UbqkctbHEm = false;}
      if(NOrOQiMUOs == true){NOrOQiMUOs = false;}
      if(REkpTPrpLd == true){REkpTPrpLd = false;}
      if(ToBFAZzitz == true){ToBFAZzitz = false;}
      if(eBCcwWOnNu == true){eBCcwWOnNu = false;}
      if(XVZDOQpARM == true){XVZDOQpARM = false;}
      if(BluaTYMmOq == true){BluaTYMmOq = false;}
      if(jcaPOQCItx == true){jcaPOQCItx = false;}
      if(BDcQFyOxqi == true){BDcQFyOxqi = false;}
      if(iyRhxsFaIX == true){iyRhxsFaIX = false;}
      if(JaZVLttKox == true){JaZVLttKox = false;}
      if(NgGUKxIeVV == true){NgGUKxIeVV = false;}
      if(KOweIkLsRU == true){KOweIkLsRU = false;}
      if(KaAVmZdGFK == true){KaAVmZdGFK = false;}
      if(DEIsVBrxWz == true){DEIsVBrxWz = false;}
      if(jaFmMteuNZ == true){jaFmMteuNZ = false;}
      if(hArTmmgjgj == true){hArTmmgjgj = false;}
      if(TCZKRGGCJG == true){TCZKRGGCJG = false;}
      if(rOWSkjVMJr == true){rOWSkjVMJr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZNHDIRAUA
{ 
  void gDuNJRFLMS()
  { 
      bool pTfWyAFbXD = false;
      bool DBnuPrCeRO = false;
      bool waltOrilcP = false;
      bool jxXSCUPDLM = false;
      bool itxaZGgzDS = false;
      bool enaxeOglIG = false;
      bool RTzITGcVsu = false;
      bool bzSFfCcLUI = false;
      bool KihJkwVamm = false;
      bool nduFtOtoHS = false;
      bool cKGIqeUVRc = false;
      bool lUQzuhkoWW = false;
      bool jCiFGxEMKQ = false;
      bool HmDBfzbYSF = false;
      bool aAJKASNuKL = false;
      bool cFRjiZbABs = false;
      bool aIKAUzQOTu = false;
      bool FMWRuisXEn = false;
      bool jICzmCUTSF = false;
      bool WaXYeSpIoB = false;
      string loEkymoYUM;
      string MJlsyGkAen;
      string MkZyEuqasl;
      string shzPCqshQb;
      string FVpAuULNZq;
      string thOEtBOFgC;
      string wNfhTdJWpH;
      string MDiCipuYCj;
      string jcBCrKTtUB;
      string bnBNfqpHfR;
      string KnXSdqyLVE;
      string GoCxSSMdpJ;
      string KPBoeYBVWq;
      string AmskYuFiXB;
      string LHXQtlkEuM;
      string eLQWGumimE;
      string ocoeDSwRXX;
      string NdFoyCqktr;
      string nwaKMoVVec;
      string IVuTLhSsMb;
      if(loEkymoYUM == KnXSdqyLVE){pTfWyAFbXD = true;}
      else if(KnXSdqyLVE == loEkymoYUM){cKGIqeUVRc = true;}
      if(MJlsyGkAen == GoCxSSMdpJ){DBnuPrCeRO = true;}
      else if(GoCxSSMdpJ == MJlsyGkAen){lUQzuhkoWW = true;}
      if(MkZyEuqasl == KPBoeYBVWq){waltOrilcP = true;}
      else if(KPBoeYBVWq == MkZyEuqasl){jCiFGxEMKQ = true;}
      if(shzPCqshQb == AmskYuFiXB){jxXSCUPDLM = true;}
      else if(AmskYuFiXB == shzPCqshQb){HmDBfzbYSF = true;}
      if(FVpAuULNZq == LHXQtlkEuM){itxaZGgzDS = true;}
      else if(LHXQtlkEuM == FVpAuULNZq){aAJKASNuKL = true;}
      if(thOEtBOFgC == eLQWGumimE){enaxeOglIG = true;}
      else if(eLQWGumimE == thOEtBOFgC){cFRjiZbABs = true;}
      if(wNfhTdJWpH == ocoeDSwRXX){RTzITGcVsu = true;}
      else if(ocoeDSwRXX == wNfhTdJWpH){aIKAUzQOTu = true;}
      if(MDiCipuYCj == NdFoyCqktr){bzSFfCcLUI = true;}
      if(jcBCrKTtUB == nwaKMoVVec){KihJkwVamm = true;}
      if(bnBNfqpHfR == IVuTLhSsMb){nduFtOtoHS = true;}
      while(NdFoyCqktr == MDiCipuYCj){FMWRuisXEn = true;}
      while(nwaKMoVVec == nwaKMoVVec){jICzmCUTSF = true;}
      while(IVuTLhSsMb == IVuTLhSsMb){WaXYeSpIoB = true;}
      if(pTfWyAFbXD == true){pTfWyAFbXD = false;}
      if(DBnuPrCeRO == true){DBnuPrCeRO = false;}
      if(waltOrilcP == true){waltOrilcP = false;}
      if(jxXSCUPDLM == true){jxXSCUPDLM = false;}
      if(itxaZGgzDS == true){itxaZGgzDS = false;}
      if(enaxeOglIG == true){enaxeOglIG = false;}
      if(RTzITGcVsu == true){RTzITGcVsu = false;}
      if(bzSFfCcLUI == true){bzSFfCcLUI = false;}
      if(KihJkwVamm == true){KihJkwVamm = false;}
      if(nduFtOtoHS == true){nduFtOtoHS = false;}
      if(cKGIqeUVRc == true){cKGIqeUVRc = false;}
      if(lUQzuhkoWW == true){lUQzuhkoWW = false;}
      if(jCiFGxEMKQ == true){jCiFGxEMKQ = false;}
      if(HmDBfzbYSF == true){HmDBfzbYSF = false;}
      if(aAJKASNuKL == true){aAJKASNuKL = false;}
      if(cFRjiZbABs == true){cFRjiZbABs = false;}
      if(aIKAUzQOTu == true){aIKAUzQOTu = false;}
      if(FMWRuisXEn == true){FMWRuisXEn = false;}
      if(jICzmCUTSF == true){jICzmCUTSF = false;}
      if(WaXYeSpIoB == true){WaXYeSpIoB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IADGLRBSRE
{ 
  void njkEZXMWOy()
  { 
      bool EjeFuxlOJJ = false;
      bool XxjPTRIWkT = false;
      bool WkoQKbZmfm = false;
      bool XjQmNrsqTX = false;
      bool ZqyLuoToJB = false;
      bool HjwnVTuOuT = false;
      bool XyhVlnfxCb = false;
      bool XQDMtflcUU = false;
      bool HjdefmmcQt = false;
      bool xdwzAaIcZH = false;
      bool JVmgcqgito = false;
      bool gRtZLmTDpy = false;
      bool ACfHdtUDMS = false;
      bool XJDMLlxwBn = false;
      bool GDiaNfjVmM = false;
      bool GElbHHoeDi = false;
      bool VcWaRWNhOZ = false;
      bool pWCBqxSFty = false;
      bool JyPzMSXbFD = false;
      bool wRsRRcfIJp = false;
      string GSdqOUgpMm;
      string HujiTzyKeG;
      string sPthwSfWDO;
      string nMwoLmLCDO;
      string IhVlIscrgI;
      string ZMrDGqXuuu;
      string nKmxztzuXg;
      string muHQxKsIZC;
      string pnounaUsiU;
      string OPHHayuXlO;
      string thTAUdFbFu;
      string xPVrFzUrJY;
      string YFLDRWnzoz;
      string PUVKIIUoaJ;
      string VsnmWztPCa;
      string dDONooVQix;
      string pFlGfctKjw;
      string efQzDfQYfS;
      string cYxOVLFIVT;
      string lDFcSPHgHs;
      if(GSdqOUgpMm == thTAUdFbFu){EjeFuxlOJJ = true;}
      else if(thTAUdFbFu == GSdqOUgpMm){JVmgcqgito = true;}
      if(HujiTzyKeG == xPVrFzUrJY){XxjPTRIWkT = true;}
      else if(xPVrFzUrJY == HujiTzyKeG){gRtZLmTDpy = true;}
      if(sPthwSfWDO == YFLDRWnzoz){WkoQKbZmfm = true;}
      else if(YFLDRWnzoz == sPthwSfWDO){ACfHdtUDMS = true;}
      if(nMwoLmLCDO == PUVKIIUoaJ){XjQmNrsqTX = true;}
      else if(PUVKIIUoaJ == nMwoLmLCDO){XJDMLlxwBn = true;}
      if(IhVlIscrgI == VsnmWztPCa){ZqyLuoToJB = true;}
      else if(VsnmWztPCa == IhVlIscrgI){GDiaNfjVmM = true;}
      if(ZMrDGqXuuu == dDONooVQix){HjwnVTuOuT = true;}
      else if(dDONooVQix == ZMrDGqXuuu){GElbHHoeDi = true;}
      if(nKmxztzuXg == pFlGfctKjw){XyhVlnfxCb = true;}
      else if(pFlGfctKjw == nKmxztzuXg){VcWaRWNhOZ = true;}
      if(muHQxKsIZC == efQzDfQYfS){XQDMtflcUU = true;}
      if(pnounaUsiU == cYxOVLFIVT){HjdefmmcQt = true;}
      if(OPHHayuXlO == lDFcSPHgHs){xdwzAaIcZH = true;}
      while(efQzDfQYfS == muHQxKsIZC){pWCBqxSFty = true;}
      while(cYxOVLFIVT == cYxOVLFIVT){JyPzMSXbFD = true;}
      while(lDFcSPHgHs == lDFcSPHgHs){wRsRRcfIJp = true;}
      if(EjeFuxlOJJ == true){EjeFuxlOJJ = false;}
      if(XxjPTRIWkT == true){XxjPTRIWkT = false;}
      if(WkoQKbZmfm == true){WkoQKbZmfm = false;}
      if(XjQmNrsqTX == true){XjQmNrsqTX = false;}
      if(ZqyLuoToJB == true){ZqyLuoToJB = false;}
      if(HjwnVTuOuT == true){HjwnVTuOuT = false;}
      if(XyhVlnfxCb == true){XyhVlnfxCb = false;}
      if(XQDMtflcUU == true){XQDMtflcUU = false;}
      if(HjdefmmcQt == true){HjdefmmcQt = false;}
      if(xdwzAaIcZH == true){xdwzAaIcZH = false;}
      if(JVmgcqgito == true){JVmgcqgito = false;}
      if(gRtZLmTDpy == true){gRtZLmTDpy = false;}
      if(ACfHdtUDMS == true){ACfHdtUDMS = false;}
      if(XJDMLlxwBn == true){XJDMLlxwBn = false;}
      if(GDiaNfjVmM == true){GDiaNfjVmM = false;}
      if(GElbHHoeDi == true){GElbHHoeDi = false;}
      if(VcWaRWNhOZ == true){VcWaRWNhOZ = false;}
      if(pWCBqxSFty == true){pWCBqxSFty = false;}
      if(JyPzMSXbFD == true){JyPzMSXbFD = false;}
      if(wRsRRcfIJp == true){wRsRRcfIJp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HJSRTETHQW
{ 
  void dwpYyAPWtI()
  { 
      bool RyEqYzZUxq = false;
      bool HnRzVAZdOT = false;
      bool nBzXOFTIjq = false;
      bool ntkmmxmIro = false;
      bool tyHJBJLhIf = false;
      bool efHAUPzfcT = false;
      bool eRkFCNDdMX = false;
      bool NQlYZotpVF = false;
      bool skzEMImjSW = false;
      bool yGfYKcNBGn = false;
      bool GhVjRNsiae = false;
      bool VJKWZsRfst = false;
      bool ZSLpZHkNNw = false;
      bool brihzLPPly = false;
      bool OEImAnuIyQ = false;
      bool LgILOnVfKK = false;
      bool cfUeDdZcXO = false;
      bool cBtteVJYok = false;
      bool LbPxkuiWSL = false;
      bool ojFaVijdiW = false;
      string kxXiYefAWm;
      string bCgOPprjkj;
      string XpYBVNjSFp;
      string DzsiYEIOUc;
      string DsIETXJRtu;
      string xsaZCtYVNK;
      string tNugjbJxpK;
      string gdOHgegTgx;
      string ESXKrJYSgd;
      string elBKipxaUr;
      string OLajNTeTsW;
      string NFnPFaojoa;
      string DpQMetbEYp;
      string hFyohsrmxX;
      string eFYJQZykEH;
      string BMlsoYuNFS;
      string qZuDoHHzgM;
      string iBmQwyQGwF;
      string wqAQoUTFAJ;
      string ydhegEJVUI;
      if(kxXiYefAWm == OLajNTeTsW){RyEqYzZUxq = true;}
      else if(OLajNTeTsW == kxXiYefAWm){GhVjRNsiae = true;}
      if(bCgOPprjkj == NFnPFaojoa){HnRzVAZdOT = true;}
      else if(NFnPFaojoa == bCgOPprjkj){VJKWZsRfst = true;}
      if(XpYBVNjSFp == DpQMetbEYp){nBzXOFTIjq = true;}
      else if(DpQMetbEYp == XpYBVNjSFp){ZSLpZHkNNw = true;}
      if(DzsiYEIOUc == hFyohsrmxX){ntkmmxmIro = true;}
      else if(hFyohsrmxX == DzsiYEIOUc){brihzLPPly = true;}
      if(DsIETXJRtu == eFYJQZykEH){tyHJBJLhIf = true;}
      else if(eFYJQZykEH == DsIETXJRtu){OEImAnuIyQ = true;}
      if(xsaZCtYVNK == BMlsoYuNFS){efHAUPzfcT = true;}
      else if(BMlsoYuNFS == xsaZCtYVNK){LgILOnVfKK = true;}
      if(tNugjbJxpK == qZuDoHHzgM){eRkFCNDdMX = true;}
      else if(qZuDoHHzgM == tNugjbJxpK){cfUeDdZcXO = true;}
      if(gdOHgegTgx == iBmQwyQGwF){NQlYZotpVF = true;}
      if(ESXKrJYSgd == wqAQoUTFAJ){skzEMImjSW = true;}
      if(elBKipxaUr == ydhegEJVUI){yGfYKcNBGn = true;}
      while(iBmQwyQGwF == gdOHgegTgx){cBtteVJYok = true;}
      while(wqAQoUTFAJ == wqAQoUTFAJ){LbPxkuiWSL = true;}
      while(ydhegEJVUI == ydhegEJVUI){ojFaVijdiW = true;}
      if(RyEqYzZUxq == true){RyEqYzZUxq = false;}
      if(HnRzVAZdOT == true){HnRzVAZdOT = false;}
      if(nBzXOFTIjq == true){nBzXOFTIjq = false;}
      if(ntkmmxmIro == true){ntkmmxmIro = false;}
      if(tyHJBJLhIf == true){tyHJBJLhIf = false;}
      if(efHAUPzfcT == true){efHAUPzfcT = false;}
      if(eRkFCNDdMX == true){eRkFCNDdMX = false;}
      if(NQlYZotpVF == true){NQlYZotpVF = false;}
      if(skzEMImjSW == true){skzEMImjSW = false;}
      if(yGfYKcNBGn == true){yGfYKcNBGn = false;}
      if(GhVjRNsiae == true){GhVjRNsiae = false;}
      if(VJKWZsRfst == true){VJKWZsRfst = false;}
      if(ZSLpZHkNNw == true){ZSLpZHkNNw = false;}
      if(brihzLPPly == true){brihzLPPly = false;}
      if(OEImAnuIyQ == true){OEImAnuIyQ = false;}
      if(LgILOnVfKK == true){LgILOnVfKK = false;}
      if(cfUeDdZcXO == true){cfUeDdZcXO = false;}
      if(cBtteVJYok == true){cBtteVJYok = false;}
      if(LbPxkuiWSL == true){LbPxkuiWSL = false;}
      if(ojFaVijdiW == true){ojFaVijdiW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HVXRKEPLIS
{ 
  void SaXuOqmsft()
  { 
      bool BjAdfPCPGF = false;
      bool wqUyNUGeol = false;
      bool NeSrjxoBLZ = false;
      bool LGfdCpcahh = false;
      bool YkGStduMKr = false;
      bool XLqIOVRIsi = false;
      bool aAEgtoLquW = false;
      bool rewHMbYzxG = false;
      bool BbqSBzPXOf = false;
      bool XUgzHXgYXF = false;
      bool SDRmArPjum = false;
      bool xSKmgyJkfu = false;
      bool ZnbOzXxxzn = false;
      bool tzarnxKDSI = false;
      bool jebbiFJtRJ = false;
      bool OwscedbDnc = false;
      bool uRjGryqSzi = false;
      bool mGRWLuLAfs = false;
      bool NDepZxFyNJ = false;
      bool VHOpNRtVij = false;
      string HXFOYrMluE;
      string WzKCZHZhTD;
      string TqZCnragxo;
      string QuTFLLETMN;
      string JCdtXWENQt;
      string RXHwgQyDag;
      string QeoGnaeFqN;
      string DGVFtQMedR;
      string mNQDWsmWXt;
      string NAsexeNXGw;
      string qzWCqLCCCQ;
      string DSYJtDNlit;
      string nHgwACNpIO;
      string DoYgZmpNLL;
      string pkUHpubjks;
      string QbnLIiRZCn;
      string yLtnMOsqiG;
      string MAZXECmZFE;
      string acFOyaBNYp;
      string VPKXMdqgtb;
      if(HXFOYrMluE == qzWCqLCCCQ){BjAdfPCPGF = true;}
      else if(qzWCqLCCCQ == HXFOYrMluE){SDRmArPjum = true;}
      if(WzKCZHZhTD == DSYJtDNlit){wqUyNUGeol = true;}
      else if(DSYJtDNlit == WzKCZHZhTD){xSKmgyJkfu = true;}
      if(TqZCnragxo == nHgwACNpIO){NeSrjxoBLZ = true;}
      else if(nHgwACNpIO == TqZCnragxo){ZnbOzXxxzn = true;}
      if(QuTFLLETMN == DoYgZmpNLL){LGfdCpcahh = true;}
      else if(DoYgZmpNLL == QuTFLLETMN){tzarnxKDSI = true;}
      if(JCdtXWENQt == pkUHpubjks){YkGStduMKr = true;}
      else if(pkUHpubjks == JCdtXWENQt){jebbiFJtRJ = true;}
      if(RXHwgQyDag == QbnLIiRZCn){XLqIOVRIsi = true;}
      else if(QbnLIiRZCn == RXHwgQyDag){OwscedbDnc = true;}
      if(QeoGnaeFqN == yLtnMOsqiG){aAEgtoLquW = true;}
      else if(yLtnMOsqiG == QeoGnaeFqN){uRjGryqSzi = true;}
      if(DGVFtQMedR == MAZXECmZFE){rewHMbYzxG = true;}
      if(mNQDWsmWXt == acFOyaBNYp){BbqSBzPXOf = true;}
      if(NAsexeNXGw == VPKXMdqgtb){XUgzHXgYXF = true;}
      while(MAZXECmZFE == DGVFtQMedR){mGRWLuLAfs = true;}
      while(acFOyaBNYp == acFOyaBNYp){NDepZxFyNJ = true;}
      while(VPKXMdqgtb == VPKXMdqgtb){VHOpNRtVij = true;}
      if(BjAdfPCPGF == true){BjAdfPCPGF = false;}
      if(wqUyNUGeol == true){wqUyNUGeol = false;}
      if(NeSrjxoBLZ == true){NeSrjxoBLZ = false;}
      if(LGfdCpcahh == true){LGfdCpcahh = false;}
      if(YkGStduMKr == true){YkGStduMKr = false;}
      if(XLqIOVRIsi == true){XLqIOVRIsi = false;}
      if(aAEgtoLquW == true){aAEgtoLquW = false;}
      if(rewHMbYzxG == true){rewHMbYzxG = false;}
      if(BbqSBzPXOf == true){BbqSBzPXOf = false;}
      if(XUgzHXgYXF == true){XUgzHXgYXF = false;}
      if(SDRmArPjum == true){SDRmArPjum = false;}
      if(xSKmgyJkfu == true){xSKmgyJkfu = false;}
      if(ZnbOzXxxzn == true){ZnbOzXxxzn = false;}
      if(tzarnxKDSI == true){tzarnxKDSI = false;}
      if(jebbiFJtRJ == true){jebbiFJtRJ = false;}
      if(OwscedbDnc == true){OwscedbDnc = false;}
      if(uRjGryqSzi == true){uRjGryqSzi = false;}
      if(mGRWLuLAfs == true){mGRWLuLAfs = false;}
      if(NDepZxFyNJ == true){NDepZxFyNJ = false;}
      if(VHOpNRtVij == true){VHOpNRtVij = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AMMCGYWEZP
{ 
  void NbtQMmtnfQ()
  { 
      bool gURMGllemx = false;
      bool IOfSIpbdhL = false;
      bool efnJurFSXF = false;
      bool BaedKDgCqq = false;
      bool uwHqkAsPAC = false;
      bool XlUxhBgIQO = false;
      bool fSHhugiCHE = false;
      bool JYmqPhXwXu = false;
      bool ypSUhOGgwJ = false;
      bool WYlcLboZuD = false;
      bool QqIusyzdhz = false;
      bool ckjVPpAlzf = false;
      bool aBFxhjmJen = false;
      bool syAUdGgWbj = false;
      bool PczwglnPNU = false;
      bool aDZPcOkKNI = false;
      bool KpysGdjPqI = false;
      bool IcKPQyBJQw = false;
      bool wWuJMoYkrO = false;
      bool VVJSYZdGpD = false;
      string KZcIWWILSA;
      string ThkGZtOTDA;
      string RLjOPjYazX;
      string hLIExIssjn;
      string oqqHiFZrZF;
      string eMQbOzoNrl;
      string xgLtSHZfJR;
      string BUiOLaUbfK;
      string KgAtsUufpy;
      string TeBxpHewob;
      string fsiIDJcBQn;
      string dMggaQgRAx;
      string LspKyWTkXE;
      string uXmEeRxrpi;
      string qsPBTGxTVZ;
      string ZNwrPlCXJg;
      string prcMrGZcCJ;
      string SnbQFRdnqq;
      string YzPydgbtos;
      string OZhIszQDIM;
      if(KZcIWWILSA == fsiIDJcBQn){gURMGllemx = true;}
      else if(fsiIDJcBQn == KZcIWWILSA){QqIusyzdhz = true;}
      if(ThkGZtOTDA == dMggaQgRAx){IOfSIpbdhL = true;}
      else if(dMggaQgRAx == ThkGZtOTDA){ckjVPpAlzf = true;}
      if(RLjOPjYazX == LspKyWTkXE){efnJurFSXF = true;}
      else if(LspKyWTkXE == RLjOPjYazX){aBFxhjmJen = true;}
      if(hLIExIssjn == uXmEeRxrpi){BaedKDgCqq = true;}
      else if(uXmEeRxrpi == hLIExIssjn){syAUdGgWbj = true;}
      if(oqqHiFZrZF == qsPBTGxTVZ){uwHqkAsPAC = true;}
      else if(qsPBTGxTVZ == oqqHiFZrZF){PczwglnPNU = true;}
      if(eMQbOzoNrl == ZNwrPlCXJg){XlUxhBgIQO = true;}
      else if(ZNwrPlCXJg == eMQbOzoNrl){aDZPcOkKNI = true;}
      if(xgLtSHZfJR == prcMrGZcCJ){fSHhugiCHE = true;}
      else if(prcMrGZcCJ == xgLtSHZfJR){KpysGdjPqI = true;}
      if(BUiOLaUbfK == SnbQFRdnqq){JYmqPhXwXu = true;}
      if(KgAtsUufpy == YzPydgbtos){ypSUhOGgwJ = true;}
      if(TeBxpHewob == OZhIszQDIM){WYlcLboZuD = true;}
      while(SnbQFRdnqq == BUiOLaUbfK){IcKPQyBJQw = true;}
      while(YzPydgbtos == YzPydgbtos){wWuJMoYkrO = true;}
      while(OZhIszQDIM == OZhIszQDIM){VVJSYZdGpD = true;}
      if(gURMGllemx == true){gURMGllemx = false;}
      if(IOfSIpbdhL == true){IOfSIpbdhL = false;}
      if(efnJurFSXF == true){efnJurFSXF = false;}
      if(BaedKDgCqq == true){BaedKDgCqq = false;}
      if(uwHqkAsPAC == true){uwHqkAsPAC = false;}
      if(XlUxhBgIQO == true){XlUxhBgIQO = false;}
      if(fSHhugiCHE == true){fSHhugiCHE = false;}
      if(JYmqPhXwXu == true){JYmqPhXwXu = false;}
      if(ypSUhOGgwJ == true){ypSUhOGgwJ = false;}
      if(WYlcLboZuD == true){WYlcLboZuD = false;}
      if(QqIusyzdhz == true){QqIusyzdhz = false;}
      if(ckjVPpAlzf == true){ckjVPpAlzf = false;}
      if(aBFxhjmJen == true){aBFxhjmJen = false;}
      if(syAUdGgWbj == true){syAUdGgWbj = false;}
      if(PczwglnPNU == true){PczwglnPNU = false;}
      if(aDZPcOkKNI == true){aDZPcOkKNI = false;}
      if(KpysGdjPqI == true){KpysGdjPqI = false;}
      if(IcKPQyBJQw == true){IcKPQyBJQw = false;}
      if(wWuJMoYkrO == true){wWuJMoYkrO = false;}
      if(VVJSYZdGpD == true){VVJSYZdGpD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKGFGSOVHJ
{ 
  void NKkftdAqxV()
  { 
      bool bMrNOCniiN = false;
      bool YzgmlHOXlU = false;
      bool pEsrlwGMSW = false;
      bool PRgTjVbmdW = false;
      bool YkwRXsdXQk = false;
      bool DzZQKWTzaS = false;
      bool waQLyGSNDQ = false;
      bool fasPuFHaUr = false;
      bool RiwgTQqPIM = false;
      bool CbMLZyUkTR = false;
      bool aQTAFcFKVF = false;
      bool OsehANdjrg = false;
      bool PDEpOEOhow = false;
      bool jWGCRAOwap = false;
      bool KgsCxJwdKM = false;
      bool TkrlBWMdkB = false;
      bool OXUYUrlbQA = false;
      bool zhIBWiJBsE = false;
      bool HjWcbzeTBt = false;
      bool njKZbmMTgF = false;
      string SQjqiYuPhG;
      string uLhfXKtcOz;
      string IyWYuZGiMC;
      string lCcdIwATuJ;
      string IxGSSoIIAy;
      string ErjxKTtKwI;
      string SLDeTriEXa;
      string JZgFqLqEGG;
      string QyiNytSeSo;
      string CpXlpwsbyZ;
      string GEjYodKeGz;
      string bpEorUbofY;
      string ZDlhYTCuOt;
      string RPFfzMNKYU;
      string imYTNMkhsV;
      string UEuZACSCzU;
      string bPQMhLjYpf;
      string HRQLpldSUM;
      string hTBrZMUffx;
      string sLKDsSWMkB;
      if(SQjqiYuPhG == GEjYodKeGz){bMrNOCniiN = true;}
      else if(GEjYodKeGz == SQjqiYuPhG){aQTAFcFKVF = true;}
      if(uLhfXKtcOz == bpEorUbofY){YzgmlHOXlU = true;}
      else if(bpEorUbofY == uLhfXKtcOz){OsehANdjrg = true;}
      if(IyWYuZGiMC == ZDlhYTCuOt){pEsrlwGMSW = true;}
      else if(ZDlhYTCuOt == IyWYuZGiMC){PDEpOEOhow = true;}
      if(lCcdIwATuJ == RPFfzMNKYU){PRgTjVbmdW = true;}
      else if(RPFfzMNKYU == lCcdIwATuJ){jWGCRAOwap = true;}
      if(IxGSSoIIAy == imYTNMkhsV){YkwRXsdXQk = true;}
      else if(imYTNMkhsV == IxGSSoIIAy){KgsCxJwdKM = true;}
      if(ErjxKTtKwI == UEuZACSCzU){DzZQKWTzaS = true;}
      else if(UEuZACSCzU == ErjxKTtKwI){TkrlBWMdkB = true;}
      if(SLDeTriEXa == bPQMhLjYpf){waQLyGSNDQ = true;}
      else if(bPQMhLjYpf == SLDeTriEXa){OXUYUrlbQA = true;}
      if(JZgFqLqEGG == HRQLpldSUM){fasPuFHaUr = true;}
      if(QyiNytSeSo == hTBrZMUffx){RiwgTQqPIM = true;}
      if(CpXlpwsbyZ == sLKDsSWMkB){CbMLZyUkTR = true;}
      while(HRQLpldSUM == JZgFqLqEGG){zhIBWiJBsE = true;}
      while(hTBrZMUffx == hTBrZMUffx){HjWcbzeTBt = true;}
      while(sLKDsSWMkB == sLKDsSWMkB){njKZbmMTgF = true;}
      if(bMrNOCniiN == true){bMrNOCniiN = false;}
      if(YzgmlHOXlU == true){YzgmlHOXlU = false;}
      if(pEsrlwGMSW == true){pEsrlwGMSW = false;}
      if(PRgTjVbmdW == true){PRgTjVbmdW = false;}
      if(YkwRXsdXQk == true){YkwRXsdXQk = false;}
      if(DzZQKWTzaS == true){DzZQKWTzaS = false;}
      if(waQLyGSNDQ == true){waQLyGSNDQ = false;}
      if(fasPuFHaUr == true){fasPuFHaUr = false;}
      if(RiwgTQqPIM == true){RiwgTQqPIM = false;}
      if(CbMLZyUkTR == true){CbMLZyUkTR = false;}
      if(aQTAFcFKVF == true){aQTAFcFKVF = false;}
      if(OsehANdjrg == true){OsehANdjrg = false;}
      if(PDEpOEOhow == true){PDEpOEOhow = false;}
      if(jWGCRAOwap == true){jWGCRAOwap = false;}
      if(KgsCxJwdKM == true){KgsCxJwdKM = false;}
      if(TkrlBWMdkB == true){TkrlBWMdkB = false;}
      if(OXUYUrlbQA == true){OXUYUrlbQA = false;}
      if(zhIBWiJBsE == true){zhIBWiJBsE = false;}
      if(HjWcbzeTBt == true){HjWcbzeTBt = false;}
      if(njKZbmMTgF == true){njKZbmMTgF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCZBMLODPX
{ 
  void AAKdDSRIOc()
  { 
      bool tOfrtTUpXX = false;
      bool TmeOLetuUW = false;
      bool zcMJGIgJjy = false;
      bool YVUorBuJyH = false;
      bool OugPZJlVLX = false;
      bool woQtKRCVll = false;
      bool mKFYyxRoWJ = false;
      bool jkxMIDuxix = false;
      bool VKxMCiFaeZ = false;
      bool zYXLTDpIQc = false;
      bool qxzCnKrDkG = false;
      bool WElnQcNrVO = false;
      bool qqKwJKNksF = false;
      bool NmfGFYKtYq = false;
      bool qCpXDtliuq = false;
      bool oxlCkAmDsc = false;
      bool xHKesjYfir = false;
      bool RSTdXoAmsO = false;
      bool YeoBPPAdVE = false;
      bool lGBwtirLdS = false;
      string PWjgzZbYYL;
      string xgDXcOfahI;
      string ucNXaRjPiF;
      string ziDcgkxOEe;
      string DZpDhqKPJZ;
      string hQFNNlJLGh;
      string pLpSMOcZpr;
      string RRVCEUlJoi;
      string HUFIXicoPu;
      string bkHWoqjXqT;
      string OjYRIPuCIr;
      string zzVXaUFhud;
      string kmKuPfKyNM;
      string kOSVUWunAH;
      string magXubOiwT;
      string lCcNhaZdCb;
      string FwouGkgADD;
      string YRgmpKGlzm;
      string QaBsaikEms;
      string xQkXCqkkRK;
      if(PWjgzZbYYL == OjYRIPuCIr){tOfrtTUpXX = true;}
      else if(OjYRIPuCIr == PWjgzZbYYL){qxzCnKrDkG = true;}
      if(xgDXcOfahI == zzVXaUFhud){TmeOLetuUW = true;}
      else if(zzVXaUFhud == xgDXcOfahI){WElnQcNrVO = true;}
      if(ucNXaRjPiF == kmKuPfKyNM){zcMJGIgJjy = true;}
      else if(kmKuPfKyNM == ucNXaRjPiF){qqKwJKNksF = true;}
      if(ziDcgkxOEe == kOSVUWunAH){YVUorBuJyH = true;}
      else if(kOSVUWunAH == ziDcgkxOEe){NmfGFYKtYq = true;}
      if(DZpDhqKPJZ == magXubOiwT){OugPZJlVLX = true;}
      else if(magXubOiwT == DZpDhqKPJZ){qCpXDtliuq = true;}
      if(hQFNNlJLGh == lCcNhaZdCb){woQtKRCVll = true;}
      else if(lCcNhaZdCb == hQFNNlJLGh){oxlCkAmDsc = true;}
      if(pLpSMOcZpr == FwouGkgADD){mKFYyxRoWJ = true;}
      else if(FwouGkgADD == pLpSMOcZpr){xHKesjYfir = true;}
      if(RRVCEUlJoi == YRgmpKGlzm){jkxMIDuxix = true;}
      if(HUFIXicoPu == QaBsaikEms){VKxMCiFaeZ = true;}
      if(bkHWoqjXqT == xQkXCqkkRK){zYXLTDpIQc = true;}
      while(YRgmpKGlzm == RRVCEUlJoi){RSTdXoAmsO = true;}
      while(QaBsaikEms == QaBsaikEms){YeoBPPAdVE = true;}
      while(xQkXCqkkRK == xQkXCqkkRK){lGBwtirLdS = true;}
      if(tOfrtTUpXX == true){tOfrtTUpXX = false;}
      if(TmeOLetuUW == true){TmeOLetuUW = false;}
      if(zcMJGIgJjy == true){zcMJGIgJjy = false;}
      if(YVUorBuJyH == true){YVUorBuJyH = false;}
      if(OugPZJlVLX == true){OugPZJlVLX = false;}
      if(woQtKRCVll == true){woQtKRCVll = false;}
      if(mKFYyxRoWJ == true){mKFYyxRoWJ = false;}
      if(jkxMIDuxix == true){jkxMIDuxix = false;}
      if(VKxMCiFaeZ == true){VKxMCiFaeZ = false;}
      if(zYXLTDpIQc == true){zYXLTDpIQc = false;}
      if(qxzCnKrDkG == true){qxzCnKrDkG = false;}
      if(WElnQcNrVO == true){WElnQcNrVO = false;}
      if(qqKwJKNksF == true){qqKwJKNksF = false;}
      if(NmfGFYKtYq == true){NmfGFYKtYq = false;}
      if(qCpXDtliuq == true){qCpXDtliuq = false;}
      if(oxlCkAmDsc == true){oxlCkAmDsc = false;}
      if(xHKesjYfir == true){xHKesjYfir = false;}
      if(RSTdXoAmsO == true){RSTdXoAmsO = false;}
      if(YeoBPPAdVE == true){YeoBPPAdVE = false;}
      if(lGBwtirLdS == true){lGBwtirLdS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJINSBKOQO
{ 
  void MSQODygxmy()
  { 
      bool zoBLRKhYbX = false;
      bool fqnmrHOdem = false;
      bool SJjITLTFCS = false;
      bool MyOpbXkcTx = false;
      bool AmrZMecNNh = false;
      bool GoQQqpErrF = false;
      bool qbWJKhcyLU = false;
      bool VlJhmeRJwo = false;
      bool iFrULXhyzl = false;
      bool SsjOFXQhPd = false;
      bool BdCsMUfhcL = false;
      bool XtwDVkjBxm = false;
      bool AezZBcBubO = false;
      bool OitRmFCyHq = false;
      bool rzUmNYwgrT = false;
      bool nOjbdWecqi = false;
      bool SjFNxnzdPQ = false;
      bool hktGuAJLLc = false;
      bool fTCIazzSnP = false;
      bool ZZHXXHtGpY = false;
      string wGtCLnhLGQ;
      string fajeVSaAQz;
      string kMbjKEPHmM;
      string hloSlWVOhE;
      string rpmMMnTaUl;
      string tNIgsjdKqH;
      string YZXshskRsy;
      string wMRMGtYPWW;
      string jnmBRUdIYB;
      string rLWafSRsdT;
      string DCgVphuuZz;
      string KOmUXjlWbN;
      string OcrqFkoqgm;
      string cekDSgGRKi;
      string YhhZpdYCCu;
      string ftRQEaKoPE;
      string sDOmVfdiBp;
      string cULrnftSAb;
      string MlnkHhMTyr;
      string WRBGoVSuDK;
      if(wGtCLnhLGQ == DCgVphuuZz){zoBLRKhYbX = true;}
      else if(DCgVphuuZz == wGtCLnhLGQ){BdCsMUfhcL = true;}
      if(fajeVSaAQz == KOmUXjlWbN){fqnmrHOdem = true;}
      else if(KOmUXjlWbN == fajeVSaAQz){XtwDVkjBxm = true;}
      if(kMbjKEPHmM == OcrqFkoqgm){SJjITLTFCS = true;}
      else if(OcrqFkoqgm == kMbjKEPHmM){AezZBcBubO = true;}
      if(hloSlWVOhE == cekDSgGRKi){MyOpbXkcTx = true;}
      else if(cekDSgGRKi == hloSlWVOhE){OitRmFCyHq = true;}
      if(rpmMMnTaUl == YhhZpdYCCu){AmrZMecNNh = true;}
      else if(YhhZpdYCCu == rpmMMnTaUl){rzUmNYwgrT = true;}
      if(tNIgsjdKqH == ftRQEaKoPE){GoQQqpErrF = true;}
      else if(ftRQEaKoPE == tNIgsjdKqH){nOjbdWecqi = true;}
      if(YZXshskRsy == sDOmVfdiBp){qbWJKhcyLU = true;}
      else if(sDOmVfdiBp == YZXshskRsy){SjFNxnzdPQ = true;}
      if(wMRMGtYPWW == cULrnftSAb){VlJhmeRJwo = true;}
      if(jnmBRUdIYB == MlnkHhMTyr){iFrULXhyzl = true;}
      if(rLWafSRsdT == WRBGoVSuDK){SsjOFXQhPd = true;}
      while(cULrnftSAb == wMRMGtYPWW){hktGuAJLLc = true;}
      while(MlnkHhMTyr == MlnkHhMTyr){fTCIazzSnP = true;}
      while(WRBGoVSuDK == WRBGoVSuDK){ZZHXXHtGpY = true;}
      if(zoBLRKhYbX == true){zoBLRKhYbX = false;}
      if(fqnmrHOdem == true){fqnmrHOdem = false;}
      if(SJjITLTFCS == true){SJjITLTFCS = false;}
      if(MyOpbXkcTx == true){MyOpbXkcTx = false;}
      if(AmrZMecNNh == true){AmrZMecNNh = false;}
      if(GoQQqpErrF == true){GoQQqpErrF = false;}
      if(qbWJKhcyLU == true){qbWJKhcyLU = false;}
      if(VlJhmeRJwo == true){VlJhmeRJwo = false;}
      if(iFrULXhyzl == true){iFrULXhyzl = false;}
      if(SsjOFXQhPd == true){SsjOFXQhPd = false;}
      if(BdCsMUfhcL == true){BdCsMUfhcL = false;}
      if(XtwDVkjBxm == true){XtwDVkjBxm = false;}
      if(AezZBcBubO == true){AezZBcBubO = false;}
      if(OitRmFCyHq == true){OitRmFCyHq = false;}
      if(rzUmNYwgrT == true){rzUmNYwgrT = false;}
      if(nOjbdWecqi == true){nOjbdWecqi = false;}
      if(SjFNxnzdPQ == true){SjFNxnzdPQ = false;}
      if(hktGuAJLLc == true){hktGuAJLLc = false;}
      if(fTCIazzSnP == true){fTCIazzSnP = false;}
      if(ZZHXXHtGpY == true){ZZHXXHtGpY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTBHKBEWNB
{ 
  void oOJCMgUPPc()
  { 
      bool bGpxkjVQPr = false;
      bool bDCrKxyrgh = false;
      bool xclrwMbIZx = false;
      bool QjdMILfSHZ = false;
      bool IlrNrTZyXM = false;
      bool rKSexzUyBX = false;
      bool IMpRbrYoiy = false;
      bool RekHZKjXAc = false;
      bool mckNFFQzPJ = false;
      bool qhRiQuwalz = false;
      bool tkOYuNZKFm = false;
      bool OxyXkebcMV = false;
      bool aZYZHiMBpd = false;
      bool OJkAhCOLRr = false;
      bool fFtctsjsyl = false;
      bool STNQYULoQL = false;
      bool AXTaXFLxph = false;
      bool QQKUoUeweN = false;
      bool zTDELuuUbN = false;
      bool qZuFrHkSEo = false;
      string ySHrtxIiQc;
      string JZbghmUyuR;
      string YWHGgfVdbe;
      string gLBibXKEOc;
      string RUCuSMDUkV;
      string IeVEGaKAKN;
      string bdHkwyYrFK;
      string bQiSAEUMnT;
      string cBsFVBpwbB;
      string MKsBAmNQyU;
      string nKOZtrwCEC;
      string FyLqkakBOt;
      string HbQEyQXgRM;
      string pENTfRlSLd;
      string FmrYwNyBQZ;
      string CLBEMLtKbc;
      string TOjqMAkrLS;
      string nRpknTjqIj;
      string SVQrJdDIGT;
      string WbphKpDAMu;
      if(ySHrtxIiQc == nKOZtrwCEC){bGpxkjVQPr = true;}
      else if(nKOZtrwCEC == ySHrtxIiQc){tkOYuNZKFm = true;}
      if(JZbghmUyuR == FyLqkakBOt){bDCrKxyrgh = true;}
      else if(FyLqkakBOt == JZbghmUyuR){OxyXkebcMV = true;}
      if(YWHGgfVdbe == HbQEyQXgRM){xclrwMbIZx = true;}
      else if(HbQEyQXgRM == YWHGgfVdbe){aZYZHiMBpd = true;}
      if(gLBibXKEOc == pENTfRlSLd){QjdMILfSHZ = true;}
      else if(pENTfRlSLd == gLBibXKEOc){OJkAhCOLRr = true;}
      if(RUCuSMDUkV == FmrYwNyBQZ){IlrNrTZyXM = true;}
      else if(FmrYwNyBQZ == RUCuSMDUkV){fFtctsjsyl = true;}
      if(IeVEGaKAKN == CLBEMLtKbc){rKSexzUyBX = true;}
      else if(CLBEMLtKbc == IeVEGaKAKN){STNQYULoQL = true;}
      if(bdHkwyYrFK == TOjqMAkrLS){IMpRbrYoiy = true;}
      else if(TOjqMAkrLS == bdHkwyYrFK){AXTaXFLxph = true;}
      if(bQiSAEUMnT == nRpknTjqIj){RekHZKjXAc = true;}
      if(cBsFVBpwbB == SVQrJdDIGT){mckNFFQzPJ = true;}
      if(MKsBAmNQyU == WbphKpDAMu){qhRiQuwalz = true;}
      while(nRpknTjqIj == bQiSAEUMnT){QQKUoUeweN = true;}
      while(SVQrJdDIGT == SVQrJdDIGT){zTDELuuUbN = true;}
      while(WbphKpDAMu == WbphKpDAMu){qZuFrHkSEo = true;}
      if(bGpxkjVQPr == true){bGpxkjVQPr = false;}
      if(bDCrKxyrgh == true){bDCrKxyrgh = false;}
      if(xclrwMbIZx == true){xclrwMbIZx = false;}
      if(QjdMILfSHZ == true){QjdMILfSHZ = false;}
      if(IlrNrTZyXM == true){IlrNrTZyXM = false;}
      if(rKSexzUyBX == true){rKSexzUyBX = false;}
      if(IMpRbrYoiy == true){IMpRbrYoiy = false;}
      if(RekHZKjXAc == true){RekHZKjXAc = false;}
      if(mckNFFQzPJ == true){mckNFFQzPJ = false;}
      if(qhRiQuwalz == true){qhRiQuwalz = false;}
      if(tkOYuNZKFm == true){tkOYuNZKFm = false;}
      if(OxyXkebcMV == true){OxyXkebcMV = false;}
      if(aZYZHiMBpd == true){aZYZHiMBpd = false;}
      if(OJkAhCOLRr == true){OJkAhCOLRr = false;}
      if(fFtctsjsyl == true){fFtctsjsyl = false;}
      if(STNQYULoQL == true){STNQYULoQL = false;}
      if(AXTaXFLxph == true){AXTaXFLxph = false;}
      if(QQKUoUeweN == true){QQKUoUeweN = false;}
      if(zTDELuuUbN == true){zTDELuuUbN = false;}
      if(qZuFrHkSEo == true){qZuFrHkSEo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVCGBSZIQH
{ 
  void WjndcqSmeM()
  { 
      bool sMtAYfSIuY = false;
      bool ErLpspOPVE = false;
      bool cMycEDgCJx = false;
      bool BRetcSbnPp = false;
      bool RPfPbrEmRD = false;
      bool VFIPpfNRwU = false;
      bool yPyyWlMRMZ = false;
      bool NZzflMgiBM = false;
      bool ytjGawIPDw = false;
      bool FKrtqCRhso = false;
      bool emZrowFccd = false;
      bool zdPjWEerXa = false;
      bool cxNQUDgFnj = false;
      bool uyoMgLUrQd = false;
      bool pflZwatIXl = false;
      bool WYJSMhYIXl = false;
      bool PAnrhAoDCK = false;
      bool jmasjxKnUs = false;
      bool IYhBNVnWAy = false;
      bool mLUeOoqsqu = false;
      string byYJgRCeIo;
      string iekxDcIgBw;
      string KgAXRrEytE;
      string tdjPDYYmuQ;
      string sOZuwPTDtH;
      string JVUHBtyAro;
      string MDjEuEuVse;
      string EVlkCuHEbB;
      string YBEmtYIbOJ;
      string aYtGEpdVzq;
      string UxKPDnjjEF;
      string msYpPLzxJW;
      string uTHjDeafgM;
      string QkEjgaqoiG;
      string oYWIVhAEpr;
      string pgMcuBpZLX;
      string MEDrnCnnJo;
      string TKNDhWwyNV;
      string eWonVjYbof;
      string jQcLskUeTT;
      if(byYJgRCeIo == UxKPDnjjEF){sMtAYfSIuY = true;}
      else if(UxKPDnjjEF == byYJgRCeIo){emZrowFccd = true;}
      if(iekxDcIgBw == msYpPLzxJW){ErLpspOPVE = true;}
      else if(msYpPLzxJW == iekxDcIgBw){zdPjWEerXa = true;}
      if(KgAXRrEytE == uTHjDeafgM){cMycEDgCJx = true;}
      else if(uTHjDeafgM == KgAXRrEytE){cxNQUDgFnj = true;}
      if(tdjPDYYmuQ == QkEjgaqoiG){BRetcSbnPp = true;}
      else if(QkEjgaqoiG == tdjPDYYmuQ){uyoMgLUrQd = true;}
      if(sOZuwPTDtH == oYWIVhAEpr){RPfPbrEmRD = true;}
      else if(oYWIVhAEpr == sOZuwPTDtH){pflZwatIXl = true;}
      if(JVUHBtyAro == pgMcuBpZLX){VFIPpfNRwU = true;}
      else if(pgMcuBpZLX == JVUHBtyAro){WYJSMhYIXl = true;}
      if(MDjEuEuVse == MEDrnCnnJo){yPyyWlMRMZ = true;}
      else if(MEDrnCnnJo == MDjEuEuVse){PAnrhAoDCK = true;}
      if(EVlkCuHEbB == TKNDhWwyNV){NZzflMgiBM = true;}
      if(YBEmtYIbOJ == eWonVjYbof){ytjGawIPDw = true;}
      if(aYtGEpdVzq == jQcLskUeTT){FKrtqCRhso = true;}
      while(TKNDhWwyNV == EVlkCuHEbB){jmasjxKnUs = true;}
      while(eWonVjYbof == eWonVjYbof){IYhBNVnWAy = true;}
      while(jQcLskUeTT == jQcLskUeTT){mLUeOoqsqu = true;}
      if(sMtAYfSIuY == true){sMtAYfSIuY = false;}
      if(ErLpspOPVE == true){ErLpspOPVE = false;}
      if(cMycEDgCJx == true){cMycEDgCJx = false;}
      if(BRetcSbnPp == true){BRetcSbnPp = false;}
      if(RPfPbrEmRD == true){RPfPbrEmRD = false;}
      if(VFIPpfNRwU == true){VFIPpfNRwU = false;}
      if(yPyyWlMRMZ == true){yPyyWlMRMZ = false;}
      if(NZzflMgiBM == true){NZzflMgiBM = false;}
      if(ytjGawIPDw == true){ytjGawIPDw = false;}
      if(FKrtqCRhso == true){FKrtqCRhso = false;}
      if(emZrowFccd == true){emZrowFccd = false;}
      if(zdPjWEerXa == true){zdPjWEerXa = false;}
      if(cxNQUDgFnj == true){cxNQUDgFnj = false;}
      if(uyoMgLUrQd == true){uyoMgLUrQd = false;}
      if(pflZwatIXl == true){pflZwatIXl = false;}
      if(WYJSMhYIXl == true){WYJSMhYIXl = false;}
      if(PAnrhAoDCK == true){PAnrhAoDCK = false;}
      if(jmasjxKnUs == true){jmasjxKnUs = false;}
      if(IYhBNVnWAy == true){IYhBNVnWAy = false;}
      if(mLUeOoqsqu == true){mLUeOoqsqu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWYDKUFSBW
{ 
  void HMOjYCrJFq()
  { 
      bool TKcxnNPPWY = false;
      bool XgWGSjnHct = false;
      bool rxbBKVoKJZ = false;
      bool CaZkbLgiKM = false;
      bool aSfNDDArps = false;
      bool HAPePVhamS = false;
      bool YEFxVxGkeH = false;
      bool DEwPSZQOyH = false;
      bool VxUQRCLtVF = false;
      bool cGwrnVNhqF = false;
      bool wOMhoDDzMp = false;
      bool ESbewbinfT = false;
      bool lLPZdxIDaw = false;
      bool LiXrKHjlaO = false;
      bool yLheAJdQwM = false;
      bool mYCXSkymEr = false;
      bool tAXPdVujTo = false;
      bool qxNRUackYT = false;
      bool TrHOJmfAYZ = false;
      bool IxhiTymSAe = false;
      string TcjwxXVUHb;
      string TWhhWhuAgP;
      string XHDSYcFPWN;
      string fpdEHpbaXi;
      string wyIblzUUxp;
      string eVmAjLYQWT;
      string SGxswcsdZf;
      string FUcyTZzbfZ;
      string HjRghJDdTw;
      string RKDDQpAOeJ;
      string GquQjKsngJ;
      string MxkxLhnQLl;
      string ZOJdOuQYgc;
      string ZkwVTQoAxX;
      string QOwJiTYGrh;
      string BiCsjqgRBn;
      string tUGEjaAOdt;
      string snTmVKSztu;
      string VJfzaphDlb;
      string jWyIdwHrZI;
      if(TcjwxXVUHb == GquQjKsngJ){TKcxnNPPWY = true;}
      else if(GquQjKsngJ == TcjwxXVUHb){wOMhoDDzMp = true;}
      if(TWhhWhuAgP == MxkxLhnQLl){XgWGSjnHct = true;}
      else if(MxkxLhnQLl == TWhhWhuAgP){ESbewbinfT = true;}
      if(XHDSYcFPWN == ZOJdOuQYgc){rxbBKVoKJZ = true;}
      else if(ZOJdOuQYgc == XHDSYcFPWN){lLPZdxIDaw = true;}
      if(fpdEHpbaXi == ZkwVTQoAxX){CaZkbLgiKM = true;}
      else if(ZkwVTQoAxX == fpdEHpbaXi){LiXrKHjlaO = true;}
      if(wyIblzUUxp == QOwJiTYGrh){aSfNDDArps = true;}
      else if(QOwJiTYGrh == wyIblzUUxp){yLheAJdQwM = true;}
      if(eVmAjLYQWT == BiCsjqgRBn){HAPePVhamS = true;}
      else if(BiCsjqgRBn == eVmAjLYQWT){mYCXSkymEr = true;}
      if(SGxswcsdZf == tUGEjaAOdt){YEFxVxGkeH = true;}
      else if(tUGEjaAOdt == SGxswcsdZf){tAXPdVujTo = true;}
      if(FUcyTZzbfZ == snTmVKSztu){DEwPSZQOyH = true;}
      if(HjRghJDdTw == VJfzaphDlb){VxUQRCLtVF = true;}
      if(RKDDQpAOeJ == jWyIdwHrZI){cGwrnVNhqF = true;}
      while(snTmVKSztu == FUcyTZzbfZ){qxNRUackYT = true;}
      while(VJfzaphDlb == VJfzaphDlb){TrHOJmfAYZ = true;}
      while(jWyIdwHrZI == jWyIdwHrZI){IxhiTymSAe = true;}
      if(TKcxnNPPWY == true){TKcxnNPPWY = false;}
      if(XgWGSjnHct == true){XgWGSjnHct = false;}
      if(rxbBKVoKJZ == true){rxbBKVoKJZ = false;}
      if(CaZkbLgiKM == true){CaZkbLgiKM = false;}
      if(aSfNDDArps == true){aSfNDDArps = false;}
      if(HAPePVhamS == true){HAPePVhamS = false;}
      if(YEFxVxGkeH == true){YEFxVxGkeH = false;}
      if(DEwPSZQOyH == true){DEwPSZQOyH = false;}
      if(VxUQRCLtVF == true){VxUQRCLtVF = false;}
      if(cGwrnVNhqF == true){cGwrnVNhqF = false;}
      if(wOMhoDDzMp == true){wOMhoDDzMp = false;}
      if(ESbewbinfT == true){ESbewbinfT = false;}
      if(lLPZdxIDaw == true){lLPZdxIDaw = false;}
      if(LiXrKHjlaO == true){LiXrKHjlaO = false;}
      if(yLheAJdQwM == true){yLheAJdQwM = false;}
      if(mYCXSkymEr == true){mYCXSkymEr = false;}
      if(tAXPdVujTo == true){tAXPdVujTo = false;}
      if(qxNRUackYT == true){qxNRUackYT = false;}
      if(TrHOJmfAYZ == true){TrHOJmfAYZ = false;}
      if(IxhiTymSAe == true){IxhiTymSAe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPSVAGVSCD
{ 
  void RtzZMlmanO()
  { 
      bool sjqQYRqrrW = false;
      bool UlRCcDEisR = false;
      bool UcxEHSUlEe = false;
      bool bBQyqlaIUu = false;
      bool xgmZqxVfRE = false;
      bool ZuhJmQmmIG = false;
      bool wFmMtSVTLq = false;
      bool cwNxUnoWNJ = false;
      bool wnTAEgSHKa = false;
      bool znzOyqsZfX = false;
      bool bBUabdgjny = false;
      bool aPYyJIlmIN = false;
      bool AOJjrowzzc = false;
      bool uOqohtTsXa = false;
      bool zhSLziOBFo = false;
      bool FGRRXNrjhm = false;
      bool ggkLDMXiQO = false;
      bool nsOhNRuxkI = false;
      bool ZutJXowYRU = false;
      bool CiKksSxHHm = false;
      string xxcAMjPSAP;
      string WTJSHolgwu;
      string ntHnHqRtuh;
      string ctnkffncjS;
      string QYQGUnaVzA;
      string GIgSjCpnsV;
      string RUWSlbfYma;
      string AJwcdPcASS;
      string PwtuaTMVBc;
      string pziOBwBxTr;
      string IBiXAwLEnT;
      string ZoUaFUZbrR;
      string OKXJkAahah;
      string NegaJNNVtd;
      string IIggDBeIIg;
      string VYFBdydYmz;
      string VddFGtHtQr;
      string HDgNJGcqGj;
      string VRYtMnYexL;
      string jniuIedbaI;
      if(xxcAMjPSAP == IBiXAwLEnT){sjqQYRqrrW = true;}
      else if(IBiXAwLEnT == xxcAMjPSAP){bBUabdgjny = true;}
      if(WTJSHolgwu == ZoUaFUZbrR){UlRCcDEisR = true;}
      else if(ZoUaFUZbrR == WTJSHolgwu){aPYyJIlmIN = true;}
      if(ntHnHqRtuh == OKXJkAahah){UcxEHSUlEe = true;}
      else if(OKXJkAahah == ntHnHqRtuh){AOJjrowzzc = true;}
      if(ctnkffncjS == NegaJNNVtd){bBQyqlaIUu = true;}
      else if(NegaJNNVtd == ctnkffncjS){uOqohtTsXa = true;}
      if(QYQGUnaVzA == IIggDBeIIg){xgmZqxVfRE = true;}
      else if(IIggDBeIIg == QYQGUnaVzA){zhSLziOBFo = true;}
      if(GIgSjCpnsV == VYFBdydYmz){ZuhJmQmmIG = true;}
      else if(VYFBdydYmz == GIgSjCpnsV){FGRRXNrjhm = true;}
      if(RUWSlbfYma == VddFGtHtQr){wFmMtSVTLq = true;}
      else if(VddFGtHtQr == RUWSlbfYma){ggkLDMXiQO = true;}
      if(AJwcdPcASS == HDgNJGcqGj){cwNxUnoWNJ = true;}
      if(PwtuaTMVBc == VRYtMnYexL){wnTAEgSHKa = true;}
      if(pziOBwBxTr == jniuIedbaI){znzOyqsZfX = true;}
      while(HDgNJGcqGj == AJwcdPcASS){nsOhNRuxkI = true;}
      while(VRYtMnYexL == VRYtMnYexL){ZutJXowYRU = true;}
      while(jniuIedbaI == jniuIedbaI){CiKksSxHHm = true;}
      if(sjqQYRqrrW == true){sjqQYRqrrW = false;}
      if(UlRCcDEisR == true){UlRCcDEisR = false;}
      if(UcxEHSUlEe == true){UcxEHSUlEe = false;}
      if(bBQyqlaIUu == true){bBQyqlaIUu = false;}
      if(xgmZqxVfRE == true){xgmZqxVfRE = false;}
      if(ZuhJmQmmIG == true){ZuhJmQmmIG = false;}
      if(wFmMtSVTLq == true){wFmMtSVTLq = false;}
      if(cwNxUnoWNJ == true){cwNxUnoWNJ = false;}
      if(wnTAEgSHKa == true){wnTAEgSHKa = false;}
      if(znzOyqsZfX == true){znzOyqsZfX = false;}
      if(bBUabdgjny == true){bBUabdgjny = false;}
      if(aPYyJIlmIN == true){aPYyJIlmIN = false;}
      if(AOJjrowzzc == true){AOJjrowzzc = false;}
      if(uOqohtTsXa == true){uOqohtTsXa = false;}
      if(zhSLziOBFo == true){zhSLziOBFo = false;}
      if(FGRRXNrjhm == true){FGRRXNrjhm = false;}
      if(ggkLDMXiQO == true){ggkLDMXiQO = false;}
      if(nsOhNRuxkI == true){nsOhNRuxkI = false;}
      if(ZutJXowYRU == true){ZutJXowYRU = false;}
      if(CiKksSxHHm == true){CiKksSxHHm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QRZIQHFZLB
{ 
  void FIUkTwUoiK()
  { 
      bool PZXWYNRULl = false;
      bool cyCEqBRSYd = false;
      bool dAIUCzZUcp = false;
      bool eqFDWkiWnC = false;
      bool ofUiwcycmM = false;
      bool UpImNOQDUZ = false;
      bool nwqUGlrygG = false;
      bool SteWoyfYXY = false;
      bool AwgQVoiRpH = false;
      bool TfCONsnzbK = false;
      bool kzugsZLkyP = false;
      bool hqeuYqOayR = false;
      bool CZIZlmrPJw = false;
      bool JgxMmBAAWu = false;
      bool cyTZYbAGoW = false;
      bool dNBKIKpVuG = false;
      bool hubBFBtRIX = false;
      bool pODCnEFhAK = false;
      bool lkalRuflEc = false;
      bool KeEQNhVSTW = false;
      string ENfWwkqaXD;
      string izeYRzLNGT;
      string sbcBVcSKAF;
      string ZsGrqjIsts;
      string hXprxriAJG;
      string AXhKeckdBT;
      string SgZRcprmhh;
      string qRTNkVkjDc;
      string sRAtECKwMO;
      string ydqZZBxYPG;
      string zwRaOiEUYJ;
      string qBaYZAffMa;
      string fwaSjNZsmj;
      string XMUwcxAYfV;
      string xpWDWxDSzZ;
      string URLnaDVyqB;
      string IKgokegduc;
      string AHzqcoZXwm;
      string KGsNPGAfUZ;
      string aBheNlJhRr;
      if(ENfWwkqaXD == zwRaOiEUYJ){PZXWYNRULl = true;}
      else if(zwRaOiEUYJ == ENfWwkqaXD){kzugsZLkyP = true;}
      if(izeYRzLNGT == qBaYZAffMa){cyCEqBRSYd = true;}
      else if(qBaYZAffMa == izeYRzLNGT){hqeuYqOayR = true;}
      if(sbcBVcSKAF == fwaSjNZsmj){dAIUCzZUcp = true;}
      else if(fwaSjNZsmj == sbcBVcSKAF){CZIZlmrPJw = true;}
      if(ZsGrqjIsts == XMUwcxAYfV){eqFDWkiWnC = true;}
      else if(XMUwcxAYfV == ZsGrqjIsts){JgxMmBAAWu = true;}
      if(hXprxriAJG == xpWDWxDSzZ){ofUiwcycmM = true;}
      else if(xpWDWxDSzZ == hXprxriAJG){cyTZYbAGoW = true;}
      if(AXhKeckdBT == URLnaDVyqB){UpImNOQDUZ = true;}
      else if(URLnaDVyqB == AXhKeckdBT){dNBKIKpVuG = true;}
      if(SgZRcprmhh == IKgokegduc){nwqUGlrygG = true;}
      else if(IKgokegduc == SgZRcprmhh){hubBFBtRIX = true;}
      if(qRTNkVkjDc == AHzqcoZXwm){SteWoyfYXY = true;}
      if(sRAtECKwMO == KGsNPGAfUZ){AwgQVoiRpH = true;}
      if(ydqZZBxYPG == aBheNlJhRr){TfCONsnzbK = true;}
      while(AHzqcoZXwm == qRTNkVkjDc){pODCnEFhAK = true;}
      while(KGsNPGAfUZ == KGsNPGAfUZ){lkalRuflEc = true;}
      while(aBheNlJhRr == aBheNlJhRr){KeEQNhVSTW = true;}
      if(PZXWYNRULl == true){PZXWYNRULl = false;}
      if(cyCEqBRSYd == true){cyCEqBRSYd = false;}
      if(dAIUCzZUcp == true){dAIUCzZUcp = false;}
      if(eqFDWkiWnC == true){eqFDWkiWnC = false;}
      if(ofUiwcycmM == true){ofUiwcycmM = false;}
      if(UpImNOQDUZ == true){UpImNOQDUZ = false;}
      if(nwqUGlrygG == true){nwqUGlrygG = false;}
      if(SteWoyfYXY == true){SteWoyfYXY = false;}
      if(AwgQVoiRpH == true){AwgQVoiRpH = false;}
      if(TfCONsnzbK == true){TfCONsnzbK = false;}
      if(kzugsZLkyP == true){kzugsZLkyP = false;}
      if(hqeuYqOayR == true){hqeuYqOayR = false;}
      if(CZIZlmrPJw == true){CZIZlmrPJw = false;}
      if(JgxMmBAAWu == true){JgxMmBAAWu = false;}
      if(cyTZYbAGoW == true){cyTZYbAGoW = false;}
      if(dNBKIKpVuG == true){dNBKIKpVuG = false;}
      if(hubBFBtRIX == true){hubBFBtRIX = false;}
      if(pODCnEFhAK == true){pODCnEFhAK = false;}
      if(lkalRuflEc == true){lkalRuflEc = false;}
      if(KeEQNhVSTW == true){KeEQNhVSTW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYNPYJCNOB
{ 
  void BQblYLgaVO()
  { 
      bool GoJjVtBsZp = false;
      bool CwZoKdqcLU = false;
      bool kOOdBXewuW = false;
      bool QtwmxyYcfG = false;
      bool FFVNwaQleA = false;
      bool dPnGhraeiy = false;
      bool OFxDYIAmqM = false;
      bool ENwFPerAhZ = false;
      bool HrQurBFoFF = false;
      bool XtshqzHSom = false;
      bool ZctSuPSiqC = false;
      bool zawIpVoCKX = false;
      bool DLglnKUOOP = false;
      bool WYLuzdyxAc = false;
      bool iWyCFwykqU = false;
      bool KFIRjOwIdk = false;
      bool uDUafZPBIM = false;
      bool XqBhngNefr = false;
      bool LiWsFQQsLk = false;
      bool hpSOheBWVf = false;
      string WQrLCSbYXr;
      string kzOYTKTfdV;
      string qUwlksTNJk;
      string ZPRKIIjliU;
      string qfTBCkCGaW;
      string OYZriCTFZI;
      string zOOlSVgEPL;
      string agxIdLAujA;
      string qNllWBoZbF;
      string odMaVcQhhf;
      string DypPwgaRNW;
      string CXVZRkbcOR;
      string gGcJVwUWlB;
      string uRMDwrWVpp;
      string ZXMEDRIlJj;
      string AnSQzxUftz;
      string LEeMbjKScY;
      string OGlYqJtYGE;
      string nhNCAGzuEz;
      string XpbpdUrAbS;
      if(WQrLCSbYXr == DypPwgaRNW){GoJjVtBsZp = true;}
      else if(DypPwgaRNW == WQrLCSbYXr){ZctSuPSiqC = true;}
      if(kzOYTKTfdV == CXVZRkbcOR){CwZoKdqcLU = true;}
      else if(CXVZRkbcOR == kzOYTKTfdV){zawIpVoCKX = true;}
      if(qUwlksTNJk == gGcJVwUWlB){kOOdBXewuW = true;}
      else if(gGcJVwUWlB == qUwlksTNJk){DLglnKUOOP = true;}
      if(ZPRKIIjliU == uRMDwrWVpp){QtwmxyYcfG = true;}
      else if(uRMDwrWVpp == ZPRKIIjliU){WYLuzdyxAc = true;}
      if(qfTBCkCGaW == ZXMEDRIlJj){FFVNwaQleA = true;}
      else if(ZXMEDRIlJj == qfTBCkCGaW){iWyCFwykqU = true;}
      if(OYZriCTFZI == AnSQzxUftz){dPnGhraeiy = true;}
      else if(AnSQzxUftz == OYZriCTFZI){KFIRjOwIdk = true;}
      if(zOOlSVgEPL == LEeMbjKScY){OFxDYIAmqM = true;}
      else if(LEeMbjKScY == zOOlSVgEPL){uDUafZPBIM = true;}
      if(agxIdLAujA == OGlYqJtYGE){ENwFPerAhZ = true;}
      if(qNllWBoZbF == nhNCAGzuEz){HrQurBFoFF = true;}
      if(odMaVcQhhf == XpbpdUrAbS){XtshqzHSom = true;}
      while(OGlYqJtYGE == agxIdLAujA){XqBhngNefr = true;}
      while(nhNCAGzuEz == nhNCAGzuEz){LiWsFQQsLk = true;}
      while(XpbpdUrAbS == XpbpdUrAbS){hpSOheBWVf = true;}
      if(GoJjVtBsZp == true){GoJjVtBsZp = false;}
      if(CwZoKdqcLU == true){CwZoKdqcLU = false;}
      if(kOOdBXewuW == true){kOOdBXewuW = false;}
      if(QtwmxyYcfG == true){QtwmxyYcfG = false;}
      if(FFVNwaQleA == true){FFVNwaQleA = false;}
      if(dPnGhraeiy == true){dPnGhraeiy = false;}
      if(OFxDYIAmqM == true){OFxDYIAmqM = false;}
      if(ENwFPerAhZ == true){ENwFPerAhZ = false;}
      if(HrQurBFoFF == true){HrQurBFoFF = false;}
      if(XtshqzHSom == true){XtshqzHSom = false;}
      if(ZctSuPSiqC == true){ZctSuPSiqC = false;}
      if(zawIpVoCKX == true){zawIpVoCKX = false;}
      if(DLglnKUOOP == true){DLglnKUOOP = false;}
      if(WYLuzdyxAc == true){WYLuzdyxAc = false;}
      if(iWyCFwykqU == true){iWyCFwykqU = false;}
      if(KFIRjOwIdk == true){KFIRjOwIdk = false;}
      if(uDUafZPBIM == true){uDUafZPBIM = false;}
      if(XqBhngNefr == true){XqBhngNefr = false;}
      if(LiWsFQQsLk == true){LiWsFQQsLk = false;}
      if(hpSOheBWVf == true){hpSOheBWVf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KABGSSVNCH
{ 
  void ikJxPyDitF()
  { 
      bool eOCRkZbGkp = false;
      bool IlZCDFPUzb = false;
      bool jCuDxtmTuD = false;
      bool iQCJHVhqjG = false;
      bool oXkjwCZRrc = false;
      bool XzaoucSzTp = false;
      bool lHKhGqjQug = false;
      bool XXkslMQKGu = false;
      bool UVbSejpMOe = false;
      bool DiWsTgNDcF = false;
      bool RJWKEANgCi = false;
      bool LHrYVQfrDW = false;
      bool AWCPdoAqZE = false;
      bool yNhBcKzQOd = false;
      bool VJKfSupyXC = false;
      bool BUAGFuHGgO = false;
      bool AWGyjyZpuK = false;
      bool RPdYApMWwi = false;
      bool yBTWDdMawh = false;
      bool DrizdzCMwT = false;
      string jLESPsxyRn;
      string qLUPrjAqEX;
      string yCKpDGUnAG;
      string kfKaHaoksN;
      string JrzhQzcHxF;
      string ykgJKhAOPJ;
      string XIxLCLAtIR;
      string uOypOFDcYD;
      string cNpuIzzBPY;
      string aZVjpAuneF;
      string ziyfJimptE;
      string eWoLfJRBCD;
      string MydipVsNAO;
      string KPyTEsOKkY;
      string MJGKtDjJEf;
      string hskbsAFOon;
      string pYofsOYVHl;
      string uHQdpCrSom;
      string kjJUfReWZE;
      string nAUwimTaQe;
      if(jLESPsxyRn == ziyfJimptE){eOCRkZbGkp = true;}
      else if(ziyfJimptE == jLESPsxyRn){RJWKEANgCi = true;}
      if(qLUPrjAqEX == eWoLfJRBCD){IlZCDFPUzb = true;}
      else if(eWoLfJRBCD == qLUPrjAqEX){LHrYVQfrDW = true;}
      if(yCKpDGUnAG == MydipVsNAO){jCuDxtmTuD = true;}
      else if(MydipVsNAO == yCKpDGUnAG){AWCPdoAqZE = true;}
      if(kfKaHaoksN == KPyTEsOKkY){iQCJHVhqjG = true;}
      else if(KPyTEsOKkY == kfKaHaoksN){yNhBcKzQOd = true;}
      if(JrzhQzcHxF == MJGKtDjJEf){oXkjwCZRrc = true;}
      else if(MJGKtDjJEf == JrzhQzcHxF){VJKfSupyXC = true;}
      if(ykgJKhAOPJ == hskbsAFOon){XzaoucSzTp = true;}
      else if(hskbsAFOon == ykgJKhAOPJ){BUAGFuHGgO = true;}
      if(XIxLCLAtIR == pYofsOYVHl){lHKhGqjQug = true;}
      else if(pYofsOYVHl == XIxLCLAtIR){AWGyjyZpuK = true;}
      if(uOypOFDcYD == uHQdpCrSom){XXkslMQKGu = true;}
      if(cNpuIzzBPY == kjJUfReWZE){UVbSejpMOe = true;}
      if(aZVjpAuneF == nAUwimTaQe){DiWsTgNDcF = true;}
      while(uHQdpCrSom == uOypOFDcYD){RPdYApMWwi = true;}
      while(kjJUfReWZE == kjJUfReWZE){yBTWDdMawh = true;}
      while(nAUwimTaQe == nAUwimTaQe){DrizdzCMwT = true;}
      if(eOCRkZbGkp == true){eOCRkZbGkp = false;}
      if(IlZCDFPUzb == true){IlZCDFPUzb = false;}
      if(jCuDxtmTuD == true){jCuDxtmTuD = false;}
      if(iQCJHVhqjG == true){iQCJHVhqjG = false;}
      if(oXkjwCZRrc == true){oXkjwCZRrc = false;}
      if(XzaoucSzTp == true){XzaoucSzTp = false;}
      if(lHKhGqjQug == true){lHKhGqjQug = false;}
      if(XXkslMQKGu == true){XXkslMQKGu = false;}
      if(UVbSejpMOe == true){UVbSejpMOe = false;}
      if(DiWsTgNDcF == true){DiWsTgNDcF = false;}
      if(RJWKEANgCi == true){RJWKEANgCi = false;}
      if(LHrYVQfrDW == true){LHrYVQfrDW = false;}
      if(AWCPdoAqZE == true){AWCPdoAqZE = false;}
      if(yNhBcKzQOd == true){yNhBcKzQOd = false;}
      if(VJKfSupyXC == true){VJKfSupyXC = false;}
      if(BUAGFuHGgO == true){BUAGFuHGgO = false;}
      if(AWGyjyZpuK == true){AWGyjyZpuK = false;}
      if(RPdYApMWwi == true){RPdYApMWwi = false;}
      if(yBTWDdMawh == true){yBTWDdMawh = false;}
      if(DrizdzCMwT == true){DrizdzCMwT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIBBZLQXNE
{ 
  void iZhnESiixF()
  { 
      bool ofCaeBcgnm = false;
      bool BgTYdZRcVK = false;
      bool cNCyVKDgRV = false;
      bool FQMUxxcTAN = false;
      bool YZnhuJFCjY = false;
      bool NoKVLbcDET = false;
      bool xwPSgjUzag = false;
      bool xycIkDYUDM = false;
      bool FBwsIQGpIV = false;
      bool TYOfPcJVBK = false;
      bool nFaDaPLBkH = false;
      bool CIArOwzWKP = false;
      bool cepFMXixsI = false;
      bool tDTrYAasRs = false;
      bool FEFBSKYWRT = false;
      bool dlLkgIOUpD = false;
      bool fOIbNzoHSO = false;
      bool UGFQKYZomC = false;
      bool zMfYeHqhLP = false;
      bool kFCONpwcmT = false;
      string USQofdoDDP;
      string EfNdGiLfCW;
      string cEKZmUaGfr;
      string jcTofxxrdF;
      string fMeLkbnLnX;
      string DxzWFPHqCL;
      string CiXKebMXyI;
      string lTCwqPZznL;
      string gPRHomcwjP;
      string oFoSCwoTgJ;
      string OPMeljuCeo;
      string pICqdmQPVr;
      string yPniTfditt;
      string aFRewRClUF;
      string qaRuYfDynO;
      string fYyoKzadLG;
      string FMIkNjqWuM;
      string jduQAXysJm;
      string cfteOCHcUw;
      string pYaNzeRggo;
      if(USQofdoDDP == OPMeljuCeo){ofCaeBcgnm = true;}
      else if(OPMeljuCeo == USQofdoDDP){nFaDaPLBkH = true;}
      if(EfNdGiLfCW == pICqdmQPVr){BgTYdZRcVK = true;}
      else if(pICqdmQPVr == EfNdGiLfCW){CIArOwzWKP = true;}
      if(cEKZmUaGfr == yPniTfditt){cNCyVKDgRV = true;}
      else if(yPniTfditt == cEKZmUaGfr){cepFMXixsI = true;}
      if(jcTofxxrdF == aFRewRClUF){FQMUxxcTAN = true;}
      else if(aFRewRClUF == jcTofxxrdF){tDTrYAasRs = true;}
      if(fMeLkbnLnX == qaRuYfDynO){YZnhuJFCjY = true;}
      else if(qaRuYfDynO == fMeLkbnLnX){FEFBSKYWRT = true;}
      if(DxzWFPHqCL == fYyoKzadLG){NoKVLbcDET = true;}
      else if(fYyoKzadLG == DxzWFPHqCL){dlLkgIOUpD = true;}
      if(CiXKebMXyI == FMIkNjqWuM){xwPSgjUzag = true;}
      else if(FMIkNjqWuM == CiXKebMXyI){fOIbNzoHSO = true;}
      if(lTCwqPZznL == jduQAXysJm){xycIkDYUDM = true;}
      if(gPRHomcwjP == cfteOCHcUw){FBwsIQGpIV = true;}
      if(oFoSCwoTgJ == pYaNzeRggo){TYOfPcJVBK = true;}
      while(jduQAXysJm == lTCwqPZznL){UGFQKYZomC = true;}
      while(cfteOCHcUw == cfteOCHcUw){zMfYeHqhLP = true;}
      while(pYaNzeRggo == pYaNzeRggo){kFCONpwcmT = true;}
      if(ofCaeBcgnm == true){ofCaeBcgnm = false;}
      if(BgTYdZRcVK == true){BgTYdZRcVK = false;}
      if(cNCyVKDgRV == true){cNCyVKDgRV = false;}
      if(FQMUxxcTAN == true){FQMUxxcTAN = false;}
      if(YZnhuJFCjY == true){YZnhuJFCjY = false;}
      if(NoKVLbcDET == true){NoKVLbcDET = false;}
      if(xwPSgjUzag == true){xwPSgjUzag = false;}
      if(xycIkDYUDM == true){xycIkDYUDM = false;}
      if(FBwsIQGpIV == true){FBwsIQGpIV = false;}
      if(TYOfPcJVBK == true){TYOfPcJVBK = false;}
      if(nFaDaPLBkH == true){nFaDaPLBkH = false;}
      if(CIArOwzWKP == true){CIArOwzWKP = false;}
      if(cepFMXixsI == true){cepFMXixsI = false;}
      if(tDTrYAasRs == true){tDTrYAasRs = false;}
      if(FEFBSKYWRT == true){FEFBSKYWRT = false;}
      if(dlLkgIOUpD == true){dlLkgIOUpD = false;}
      if(fOIbNzoHSO == true){fOIbNzoHSO = false;}
      if(UGFQKYZomC == true){UGFQKYZomC = false;}
      if(zMfYeHqhLP == true){zMfYeHqhLP = false;}
      if(kFCONpwcmT == true){kFCONpwcmT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOFBSGNTQU
{ 
  void RRuSBZJBhE()
  { 
      bool BLeXonLYyA = false;
      bool uZGLqgZUGw = false;
      bool rOJraMkxJZ = false;
      bool DxHaffKFHZ = false;
      bool NZjhMlxSoA = false;
      bool SVNsjmBlxb = false;
      bool COPYxyRefL = false;
      bool VUNgiRdbfn = false;
      bool PSHIHhjOqs = false;
      bool dYIeWzKLkO = false;
      bool TRldeyHgKR = false;
      bool JZGIMiHGQP = false;
      bool NDmmgxLhJj = false;
      bool HRpQTxgcdI = false;
      bool ZCDZjDRzSm = false;
      bool qDtVAQezwg = false;
      bool lYXaJqiooO = false;
      bool CdcIoKzMDd = false;
      bool fMPVrEWUQC = false;
      bool RgfxVAecQr = false;
      string hSzIItqrQR;
      string OGyMRtozqn;
      string ctfDuPWEAS;
      string IiXmPlWQbF;
      string dbNscDudGD;
      string SRFwmnlwNr;
      string WlqyJfiKxf;
      string XYXkJAflZq;
      string UsywAqcbza;
      string zaCiirkPjx;
      string UjfZfssUlm;
      string HAVWXcntyR;
      string CHLWgwVoCR;
      string PQCcVkMXQG;
      string xIoMSzEfKF;
      string DpRStNYJsi;
      string XERUWqxrAm;
      string QPdrTtRyDg;
      string rpdwNZziiI;
      string MDdghspUpb;
      if(hSzIItqrQR == UjfZfssUlm){BLeXonLYyA = true;}
      else if(UjfZfssUlm == hSzIItqrQR){TRldeyHgKR = true;}
      if(OGyMRtozqn == HAVWXcntyR){uZGLqgZUGw = true;}
      else if(HAVWXcntyR == OGyMRtozqn){JZGIMiHGQP = true;}
      if(ctfDuPWEAS == CHLWgwVoCR){rOJraMkxJZ = true;}
      else if(CHLWgwVoCR == ctfDuPWEAS){NDmmgxLhJj = true;}
      if(IiXmPlWQbF == PQCcVkMXQG){DxHaffKFHZ = true;}
      else if(PQCcVkMXQG == IiXmPlWQbF){HRpQTxgcdI = true;}
      if(dbNscDudGD == xIoMSzEfKF){NZjhMlxSoA = true;}
      else if(xIoMSzEfKF == dbNscDudGD){ZCDZjDRzSm = true;}
      if(SRFwmnlwNr == DpRStNYJsi){SVNsjmBlxb = true;}
      else if(DpRStNYJsi == SRFwmnlwNr){qDtVAQezwg = true;}
      if(WlqyJfiKxf == XERUWqxrAm){COPYxyRefL = true;}
      else if(XERUWqxrAm == WlqyJfiKxf){lYXaJqiooO = true;}
      if(XYXkJAflZq == QPdrTtRyDg){VUNgiRdbfn = true;}
      if(UsywAqcbza == rpdwNZziiI){PSHIHhjOqs = true;}
      if(zaCiirkPjx == MDdghspUpb){dYIeWzKLkO = true;}
      while(QPdrTtRyDg == XYXkJAflZq){CdcIoKzMDd = true;}
      while(rpdwNZziiI == rpdwNZziiI){fMPVrEWUQC = true;}
      while(MDdghspUpb == MDdghspUpb){RgfxVAecQr = true;}
      if(BLeXonLYyA == true){BLeXonLYyA = false;}
      if(uZGLqgZUGw == true){uZGLqgZUGw = false;}
      if(rOJraMkxJZ == true){rOJraMkxJZ = false;}
      if(DxHaffKFHZ == true){DxHaffKFHZ = false;}
      if(NZjhMlxSoA == true){NZjhMlxSoA = false;}
      if(SVNsjmBlxb == true){SVNsjmBlxb = false;}
      if(COPYxyRefL == true){COPYxyRefL = false;}
      if(VUNgiRdbfn == true){VUNgiRdbfn = false;}
      if(PSHIHhjOqs == true){PSHIHhjOqs = false;}
      if(dYIeWzKLkO == true){dYIeWzKLkO = false;}
      if(TRldeyHgKR == true){TRldeyHgKR = false;}
      if(JZGIMiHGQP == true){JZGIMiHGQP = false;}
      if(NDmmgxLhJj == true){NDmmgxLhJj = false;}
      if(HRpQTxgcdI == true){HRpQTxgcdI = false;}
      if(ZCDZjDRzSm == true){ZCDZjDRzSm = false;}
      if(qDtVAQezwg == true){qDtVAQezwg = false;}
      if(lYXaJqiooO == true){lYXaJqiooO = false;}
      if(CdcIoKzMDd == true){CdcIoKzMDd = false;}
      if(fMPVrEWUQC == true){fMPVrEWUQC = false;}
      if(RgfxVAecQr == true){RgfxVAecQr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKNVZNYFUP
{ 
  void YeTDPSMJiL()
  { 
      bool otsFQKcFnC = false;
      bool gxCJQlzWNf = false;
      bool KcGcCemEXa = false;
      bool wBtIKbTKGG = false;
      bool kuWJRwJZxJ = false;
      bool KNoyjLnPCl = false;
      bool WYhMGeCszo = false;
      bool SoPGtPGwLG = false;
      bool UMGNQhMwXy = false;
      bool nEHUiMNJDl = false;
      bool tQaIqVyhDU = false;
      bool EqEwQKRTwY = false;
      bool SGUAANguXh = false;
      bool BxsYLDlxWt = false;
      bool ierDswAKDX = false;
      bool usMeTmwZHc = false;
      bool nDJVTHyejM = false;
      bool YTxConORGE = false;
      bool NVqzmHjNFY = false;
      bool HLpsFfUVil = false;
      string HZPciyFIRA;
      string DZoBcwDxKy;
      string pDeIPjFDLW;
      string cigLxwirNL;
      string ANkIQMyVUk;
      string sSaZgEtHNy;
      string sBwtWUrdEf;
      string MLizxbRVrD;
      string kjiadKHHes;
      string CbdPRzRqlw;
      string UUQnXgjbbF;
      string lXOJMJRVQM;
      string MjyKdjgTgy;
      string KajuiPStCw;
      string affZGdNTCI;
      string gwZZijVGKn;
      string zPudtLnSaw;
      string qWSUkgDYEA;
      string WMQXQOAKMy;
      string sLjOwKkCeu;
      if(HZPciyFIRA == UUQnXgjbbF){otsFQKcFnC = true;}
      else if(UUQnXgjbbF == HZPciyFIRA){tQaIqVyhDU = true;}
      if(DZoBcwDxKy == lXOJMJRVQM){gxCJQlzWNf = true;}
      else if(lXOJMJRVQM == DZoBcwDxKy){EqEwQKRTwY = true;}
      if(pDeIPjFDLW == MjyKdjgTgy){KcGcCemEXa = true;}
      else if(MjyKdjgTgy == pDeIPjFDLW){SGUAANguXh = true;}
      if(cigLxwirNL == KajuiPStCw){wBtIKbTKGG = true;}
      else if(KajuiPStCw == cigLxwirNL){BxsYLDlxWt = true;}
      if(ANkIQMyVUk == affZGdNTCI){kuWJRwJZxJ = true;}
      else if(affZGdNTCI == ANkIQMyVUk){ierDswAKDX = true;}
      if(sSaZgEtHNy == gwZZijVGKn){KNoyjLnPCl = true;}
      else if(gwZZijVGKn == sSaZgEtHNy){usMeTmwZHc = true;}
      if(sBwtWUrdEf == zPudtLnSaw){WYhMGeCszo = true;}
      else if(zPudtLnSaw == sBwtWUrdEf){nDJVTHyejM = true;}
      if(MLizxbRVrD == qWSUkgDYEA){SoPGtPGwLG = true;}
      if(kjiadKHHes == WMQXQOAKMy){UMGNQhMwXy = true;}
      if(CbdPRzRqlw == sLjOwKkCeu){nEHUiMNJDl = true;}
      while(qWSUkgDYEA == MLizxbRVrD){YTxConORGE = true;}
      while(WMQXQOAKMy == WMQXQOAKMy){NVqzmHjNFY = true;}
      while(sLjOwKkCeu == sLjOwKkCeu){HLpsFfUVil = true;}
      if(otsFQKcFnC == true){otsFQKcFnC = false;}
      if(gxCJQlzWNf == true){gxCJQlzWNf = false;}
      if(KcGcCemEXa == true){KcGcCemEXa = false;}
      if(wBtIKbTKGG == true){wBtIKbTKGG = false;}
      if(kuWJRwJZxJ == true){kuWJRwJZxJ = false;}
      if(KNoyjLnPCl == true){KNoyjLnPCl = false;}
      if(WYhMGeCszo == true){WYhMGeCszo = false;}
      if(SoPGtPGwLG == true){SoPGtPGwLG = false;}
      if(UMGNQhMwXy == true){UMGNQhMwXy = false;}
      if(nEHUiMNJDl == true){nEHUiMNJDl = false;}
      if(tQaIqVyhDU == true){tQaIqVyhDU = false;}
      if(EqEwQKRTwY == true){EqEwQKRTwY = false;}
      if(SGUAANguXh == true){SGUAANguXh = false;}
      if(BxsYLDlxWt == true){BxsYLDlxWt = false;}
      if(ierDswAKDX == true){ierDswAKDX = false;}
      if(usMeTmwZHc == true){usMeTmwZHc = false;}
      if(nDJVTHyejM == true){nDJVTHyejM = false;}
      if(YTxConORGE == true){YTxConORGE = false;}
      if(NVqzmHjNFY == true){NVqzmHjNFY = false;}
      if(HLpsFfUVil == true){HLpsFfUVil = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWROBNBVRV
{ 
  void hRmdzwjCaO()
  { 
      bool QRxexYKOoY = false;
      bool zQgUjVEDUP = false;
      bool CdCeSxRATY = false;
      bool TTFIpXUIlh = false;
      bool XNZtkagxuV = false;
      bool OFZRalOSMA = false;
      bool HJuPEeKYeL = false;
      bool BuQlroEItr = false;
      bool QUFyKOtmgD = false;
      bool ICwlaNSKoF = false;
      bool PHRiTSnmZl = false;
      bool hGXUimEwFp = false;
      bool kWraDzzdLd = false;
      bool WsSnbICWdq = false;
      bool ZHMtVCdbDm = false;
      bool JVFyUrPqeU = false;
      bool TKawPomjrZ = false;
      bool khSNPcKxEB = false;
      bool UXaYUAnTTj = false;
      bool sKqIWPfQeg = false;
      string YlDRqlWuKK;
      string JSrcxPrqnK;
      string GXJUEQxDIV;
      string YHOVqcLmUq;
      string GKEYaEwBNE;
      string XqdxSAbiMZ;
      string oTlnlBEWlT;
      string EEWwDwSjsz;
      string UwoDygcRCp;
      string BcZtCmXQmY;
      string AYOtASUgsW;
      string gqoNFsdhpE;
      string XlTuRbebtQ;
      string XCxTyugtDe;
      string LuXfIKmMnJ;
      string IoZhBNETcY;
      string nrmcyesVOJ;
      string LieKsbOnlH;
      string oRnjHhbPSj;
      string qNReqTIthd;
      if(YlDRqlWuKK == AYOtASUgsW){QRxexYKOoY = true;}
      else if(AYOtASUgsW == YlDRqlWuKK){PHRiTSnmZl = true;}
      if(JSrcxPrqnK == gqoNFsdhpE){zQgUjVEDUP = true;}
      else if(gqoNFsdhpE == JSrcxPrqnK){hGXUimEwFp = true;}
      if(GXJUEQxDIV == XlTuRbebtQ){CdCeSxRATY = true;}
      else if(XlTuRbebtQ == GXJUEQxDIV){kWraDzzdLd = true;}
      if(YHOVqcLmUq == XCxTyugtDe){TTFIpXUIlh = true;}
      else if(XCxTyugtDe == YHOVqcLmUq){WsSnbICWdq = true;}
      if(GKEYaEwBNE == LuXfIKmMnJ){XNZtkagxuV = true;}
      else if(LuXfIKmMnJ == GKEYaEwBNE){ZHMtVCdbDm = true;}
      if(XqdxSAbiMZ == IoZhBNETcY){OFZRalOSMA = true;}
      else if(IoZhBNETcY == XqdxSAbiMZ){JVFyUrPqeU = true;}
      if(oTlnlBEWlT == nrmcyesVOJ){HJuPEeKYeL = true;}
      else if(nrmcyesVOJ == oTlnlBEWlT){TKawPomjrZ = true;}
      if(EEWwDwSjsz == LieKsbOnlH){BuQlroEItr = true;}
      if(UwoDygcRCp == oRnjHhbPSj){QUFyKOtmgD = true;}
      if(BcZtCmXQmY == qNReqTIthd){ICwlaNSKoF = true;}
      while(LieKsbOnlH == EEWwDwSjsz){khSNPcKxEB = true;}
      while(oRnjHhbPSj == oRnjHhbPSj){UXaYUAnTTj = true;}
      while(qNReqTIthd == qNReqTIthd){sKqIWPfQeg = true;}
      if(QRxexYKOoY == true){QRxexYKOoY = false;}
      if(zQgUjVEDUP == true){zQgUjVEDUP = false;}
      if(CdCeSxRATY == true){CdCeSxRATY = false;}
      if(TTFIpXUIlh == true){TTFIpXUIlh = false;}
      if(XNZtkagxuV == true){XNZtkagxuV = false;}
      if(OFZRalOSMA == true){OFZRalOSMA = false;}
      if(HJuPEeKYeL == true){HJuPEeKYeL = false;}
      if(BuQlroEItr == true){BuQlroEItr = false;}
      if(QUFyKOtmgD == true){QUFyKOtmgD = false;}
      if(ICwlaNSKoF == true){ICwlaNSKoF = false;}
      if(PHRiTSnmZl == true){PHRiTSnmZl = false;}
      if(hGXUimEwFp == true){hGXUimEwFp = false;}
      if(kWraDzzdLd == true){kWraDzzdLd = false;}
      if(WsSnbICWdq == true){WsSnbICWdq = false;}
      if(ZHMtVCdbDm == true){ZHMtVCdbDm = false;}
      if(JVFyUrPqeU == true){JVFyUrPqeU = false;}
      if(TKawPomjrZ == true){TKawPomjrZ = false;}
      if(khSNPcKxEB == true){khSNPcKxEB = false;}
      if(UXaYUAnTTj == true){UXaYUAnTTj = false;}
      if(sKqIWPfQeg == true){sKqIWPfQeg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGAOLCAPZS
{ 
  void BDZQABmloE()
  { 
      bool bTOhibJpKI = false;
      bool ykonpMNPOI = false;
      bool yZPKKEbEdn = false;
      bool foGRdaNUAL = false;
      bool SpEMHoFHsW = false;
      bool rwpOzCDDXd = false;
      bool zFMVcJeWKO = false;
      bool zsPDoIVDDU = false;
      bool zTKGuiyrSb = false;
      bool WJxVMNdhix = false;
      bool KhxdXzgmYp = false;
      bool fAACeetGZs = false;
      bool LmDirpuspa = false;
      bool emTFKQWfiw = false;
      bool CKScuWItqg = false;
      bool SXHplWdNlg = false;
      bool DnwxLsfurN = false;
      bool INWdqAUanV = false;
      bool gBBJIHedSm = false;
      bool lItBsNOUQB = false;
      string ZiILNqBQon;
      string oyUdWQVeru;
      string zfkVwwoaEd;
      string NEuOoXBNNm;
      string qRCwqzGnQz;
      string GEXustxmOR;
      string CZMKakCGoy;
      string OIREEgcodw;
      string pAJEXJfzUu;
      string aOzukQFqVG;
      string wzzSjymTqM;
      string QIIRbBPHmQ;
      string EDktXAJVTn;
      string akTWApBqTY;
      string WMIIdRFgTi;
      string AyEEBsOFtj;
      string oQzCkfolRl;
      string AYnNtrtcPG;
      string tbCjmcgOVG;
      string auwijGMFWx;
      if(ZiILNqBQon == wzzSjymTqM){bTOhibJpKI = true;}
      else if(wzzSjymTqM == ZiILNqBQon){KhxdXzgmYp = true;}
      if(oyUdWQVeru == QIIRbBPHmQ){ykonpMNPOI = true;}
      else if(QIIRbBPHmQ == oyUdWQVeru){fAACeetGZs = true;}
      if(zfkVwwoaEd == EDktXAJVTn){yZPKKEbEdn = true;}
      else if(EDktXAJVTn == zfkVwwoaEd){LmDirpuspa = true;}
      if(NEuOoXBNNm == akTWApBqTY){foGRdaNUAL = true;}
      else if(akTWApBqTY == NEuOoXBNNm){emTFKQWfiw = true;}
      if(qRCwqzGnQz == WMIIdRFgTi){SpEMHoFHsW = true;}
      else if(WMIIdRFgTi == qRCwqzGnQz){CKScuWItqg = true;}
      if(GEXustxmOR == AyEEBsOFtj){rwpOzCDDXd = true;}
      else if(AyEEBsOFtj == GEXustxmOR){SXHplWdNlg = true;}
      if(CZMKakCGoy == oQzCkfolRl){zFMVcJeWKO = true;}
      else if(oQzCkfolRl == CZMKakCGoy){DnwxLsfurN = true;}
      if(OIREEgcodw == AYnNtrtcPG){zsPDoIVDDU = true;}
      if(pAJEXJfzUu == tbCjmcgOVG){zTKGuiyrSb = true;}
      if(aOzukQFqVG == auwijGMFWx){WJxVMNdhix = true;}
      while(AYnNtrtcPG == OIREEgcodw){INWdqAUanV = true;}
      while(tbCjmcgOVG == tbCjmcgOVG){gBBJIHedSm = true;}
      while(auwijGMFWx == auwijGMFWx){lItBsNOUQB = true;}
      if(bTOhibJpKI == true){bTOhibJpKI = false;}
      if(ykonpMNPOI == true){ykonpMNPOI = false;}
      if(yZPKKEbEdn == true){yZPKKEbEdn = false;}
      if(foGRdaNUAL == true){foGRdaNUAL = false;}
      if(SpEMHoFHsW == true){SpEMHoFHsW = false;}
      if(rwpOzCDDXd == true){rwpOzCDDXd = false;}
      if(zFMVcJeWKO == true){zFMVcJeWKO = false;}
      if(zsPDoIVDDU == true){zsPDoIVDDU = false;}
      if(zTKGuiyrSb == true){zTKGuiyrSb = false;}
      if(WJxVMNdhix == true){WJxVMNdhix = false;}
      if(KhxdXzgmYp == true){KhxdXzgmYp = false;}
      if(fAACeetGZs == true){fAACeetGZs = false;}
      if(LmDirpuspa == true){LmDirpuspa = false;}
      if(emTFKQWfiw == true){emTFKQWfiw = false;}
      if(CKScuWItqg == true){CKScuWItqg = false;}
      if(SXHplWdNlg == true){SXHplWdNlg = false;}
      if(DnwxLsfurN == true){DnwxLsfurN = false;}
      if(INWdqAUanV == true){INWdqAUanV = false;}
      if(gBBJIHedSm == true){gBBJIHedSm = false;}
      if(lItBsNOUQB == true){lItBsNOUQB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVLYHMKUIC
{ 
  void PjKSVIliMh()
  { 
      bool cKnpmfBNBH = false;
      bool KXbOgWcBLp = false;
      bool ZYTbCtIrUN = false;
      bool RZjFDlVEML = false;
      bool HPQUcpjqHG = false;
      bool GeXmcDpMms = false;
      bool WIsnpjmWLt = false;
      bool AXnAhKHyzL = false;
      bool JQjNHlBxbz = false;
      bool uJQTnyWcer = false;
      bool CNeNFhqXER = false;
      bool wrMbiFYefE = false;
      bool hptLzpHULi = false;
      bool ndTHJwlWIZ = false;
      bool tdrKDDxojh = false;
      bool ZqwZJMTTNO = false;
      bool aVLVdRXFRm = false;
      bool TBWGJExjIu = false;
      bool sRjcIwhtyw = false;
      bool bRJszYRWfl = false;
      string ksPAACohAQ;
      string VoFLqeDhhZ;
      string VlMOILFZcm;
      string dNQtyLmQKr;
      string apeptmlLba;
      string hxknYzgAqo;
      string wOEMlIXLNf;
      string qmWoyeGVUV;
      string ZtyCFgcbVy;
      string emYVwLlSDl;
      string OaywiuZuos;
      string rKeVPCQBHE;
      string fuoOAENBsl;
      string snRiGzuBTJ;
      string HhlbGUHDGs;
      string ujKzFTkjud;
      string gXBDzDrwOQ;
      string GOhxxyIMHf;
      string xKuAqJcScm;
      string NLGocigicC;
      if(ksPAACohAQ == OaywiuZuos){cKnpmfBNBH = true;}
      else if(OaywiuZuos == ksPAACohAQ){CNeNFhqXER = true;}
      if(VoFLqeDhhZ == rKeVPCQBHE){KXbOgWcBLp = true;}
      else if(rKeVPCQBHE == VoFLqeDhhZ){wrMbiFYefE = true;}
      if(VlMOILFZcm == fuoOAENBsl){ZYTbCtIrUN = true;}
      else if(fuoOAENBsl == VlMOILFZcm){hptLzpHULi = true;}
      if(dNQtyLmQKr == snRiGzuBTJ){RZjFDlVEML = true;}
      else if(snRiGzuBTJ == dNQtyLmQKr){ndTHJwlWIZ = true;}
      if(apeptmlLba == HhlbGUHDGs){HPQUcpjqHG = true;}
      else if(HhlbGUHDGs == apeptmlLba){tdrKDDxojh = true;}
      if(hxknYzgAqo == ujKzFTkjud){GeXmcDpMms = true;}
      else if(ujKzFTkjud == hxknYzgAqo){ZqwZJMTTNO = true;}
      if(wOEMlIXLNf == gXBDzDrwOQ){WIsnpjmWLt = true;}
      else if(gXBDzDrwOQ == wOEMlIXLNf){aVLVdRXFRm = true;}
      if(qmWoyeGVUV == GOhxxyIMHf){AXnAhKHyzL = true;}
      if(ZtyCFgcbVy == xKuAqJcScm){JQjNHlBxbz = true;}
      if(emYVwLlSDl == NLGocigicC){uJQTnyWcer = true;}
      while(GOhxxyIMHf == qmWoyeGVUV){TBWGJExjIu = true;}
      while(xKuAqJcScm == xKuAqJcScm){sRjcIwhtyw = true;}
      while(NLGocigicC == NLGocigicC){bRJszYRWfl = true;}
      if(cKnpmfBNBH == true){cKnpmfBNBH = false;}
      if(KXbOgWcBLp == true){KXbOgWcBLp = false;}
      if(ZYTbCtIrUN == true){ZYTbCtIrUN = false;}
      if(RZjFDlVEML == true){RZjFDlVEML = false;}
      if(HPQUcpjqHG == true){HPQUcpjqHG = false;}
      if(GeXmcDpMms == true){GeXmcDpMms = false;}
      if(WIsnpjmWLt == true){WIsnpjmWLt = false;}
      if(AXnAhKHyzL == true){AXnAhKHyzL = false;}
      if(JQjNHlBxbz == true){JQjNHlBxbz = false;}
      if(uJQTnyWcer == true){uJQTnyWcer = false;}
      if(CNeNFhqXER == true){CNeNFhqXER = false;}
      if(wrMbiFYefE == true){wrMbiFYefE = false;}
      if(hptLzpHULi == true){hptLzpHULi = false;}
      if(ndTHJwlWIZ == true){ndTHJwlWIZ = false;}
      if(tdrKDDxojh == true){tdrKDDxojh = false;}
      if(ZqwZJMTTNO == true){ZqwZJMTTNO = false;}
      if(aVLVdRXFRm == true){aVLVdRXFRm = false;}
      if(TBWGJExjIu == true){TBWGJExjIu = false;}
      if(sRjcIwhtyw == true){sRjcIwhtyw = false;}
      if(bRJszYRWfl == true){bRJszYRWfl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUJSYJROAN
{ 
  void ohoxpYSsnX()
  { 
      bool jbwxhmTSOg = false;
      bool QhtpSDEeoL = false;
      bool jGYigFCnbr = false;
      bool hewnebdUEE = false;
      bool oYEeWwOsJS = false;
      bool rAQbjdDNPc = false;
      bool jepWzklGKq = false;
      bool ZiZjWKCsMj = false;
      bool pJdIzgOTDB = false;
      bool YQFbTJigfk = false;
      bool KIhSsJZfFZ = false;
      bool aJBflZAgWS = false;
      bool VRCJSJdyPM = false;
      bool aUNaYhbLPp = false;
      bool GiNdZPOYot = false;
      bool IBKMPrFYAj = false;
      bool ebPryGuaGD = false;
      bool yoRgLmDXiD = false;
      bool tFIVEZKALf = false;
      bool bDLeLeSVfT = false;
      string dcfHnpXJwp;
      string JuuafgWVIF;
      string JRmbkaDeBV;
      string KArhqyKzdG;
      string qLqxOZVnML;
      string wpCKMLoEVN;
      string mrHZfJDMih;
      string WXrCOyapML;
      string FOSoZTygVf;
      string IFdQTyDRRF;
      string WIEdoYyAwO;
      string kyrKHXZSAL;
      string KVqDYRtahP;
      string tIYGnwKnAB;
      string UxkHuJNSIu;
      string YkQFtBRBFW;
      string eXRfTbZkVL;
      string NlRypNjiHO;
      string DaSmqIqTMm;
      string eIicWxfFmT;
      if(dcfHnpXJwp == WIEdoYyAwO){jbwxhmTSOg = true;}
      else if(WIEdoYyAwO == dcfHnpXJwp){KIhSsJZfFZ = true;}
      if(JuuafgWVIF == kyrKHXZSAL){QhtpSDEeoL = true;}
      else if(kyrKHXZSAL == JuuafgWVIF){aJBflZAgWS = true;}
      if(JRmbkaDeBV == KVqDYRtahP){jGYigFCnbr = true;}
      else if(KVqDYRtahP == JRmbkaDeBV){VRCJSJdyPM = true;}
      if(KArhqyKzdG == tIYGnwKnAB){hewnebdUEE = true;}
      else if(tIYGnwKnAB == KArhqyKzdG){aUNaYhbLPp = true;}
      if(qLqxOZVnML == UxkHuJNSIu){oYEeWwOsJS = true;}
      else if(UxkHuJNSIu == qLqxOZVnML){GiNdZPOYot = true;}
      if(wpCKMLoEVN == YkQFtBRBFW){rAQbjdDNPc = true;}
      else if(YkQFtBRBFW == wpCKMLoEVN){IBKMPrFYAj = true;}
      if(mrHZfJDMih == eXRfTbZkVL){jepWzklGKq = true;}
      else if(eXRfTbZkVL == mrHZfJDMih){ebPryGuaGD = true;}
      if(WXrCOyapML == NlRypNjiHO){ZiZjWKCsMj = true;}
      if(FOSoZTygVf == DaSmqIqTMm){pJdIzgOTDB = true;}
      if(IFdQTyDRRF == eIicWxfFmT){YQFbTJigfk = true;}
      while(NlRypNjiHO == WXrCOyapML){yoRgLmDXiD = true;}
      while(DaSmqIqTMm == DaSmqIqTMm){tFIVEZKALf = true;}
      while(eIicWxfFmT == eIicWxfFmT){bDLeLeSVfT = true;}
      if(jbwxhmTSOg == true){jbwxhmTSOg = false;}
      if(QhtpSDEeoL == true){QhtpSDEeoL = false;}
      if(jGYigFCnbr == true){jGYigFCnbr = false;}
      if(hewnebdUEE == true){hewnebdUEE = false;}
      if(oYEeWwOsJS == true){oYEeWwOsJS = false;}
      if(rAQbjdDNPc == true){rAQbjdDNPc = false;}
      if(jepWzklGKq == true){jepWzklGKq = false;}
      if(ZiZjWKCsMj == true){ZiZjWKCsMj = false;}
      if(pJdIzgOTDB == true){pJdIzgOTDB = false;}
      if(YQFbTJigfk == true){YQFbTJigfk = false;}
      if(KIhSsJZfFZ == true){KIhSsJZfFZ = false;}
      if(aJBflZAgWS == true){aJBflZAgWS = false;}
      if(VRCJSJdyPM == true){VRCJSJdyPM = false;}
      if(aUNaYhbLPp == true){aUNaYhbLPp = false;}
      if(GiNdZPOYot == true){GiNdZPOYot = false;}
      if(IBKMPrFYAj == true){IBKMPrFYAj = false;}
      if(ebPryGuaGD == true){ebPryGuaGD = false;}
      if(yoRgLmDXiD == true){yoRgLmDXiD = false;}
      if(tFIVEZKALf == true){tFIVEZKALf = false;}
      if(bDLeLeSVfT == true){bDLeLeSVfT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RXCHIILHIZ
{ 
  void LnAcxHiCEk()
  { 
      bool chiVJglBsk = false;
      bool oomVhJUSZb = false;
      bool UtkcbJOUHt = false;
      bool FpAGKmhlJD = false;
      bool RwummeNjnK = false;
      bool YnxQrhwFsA = false;
      bool RRszfyngKt = false;
      bool ahJWJXzxow = false;
      bool uefxUQsjNb = false;
      bool pbsJkADuHo = false;
      bool qgYsipeZGU = false;
      bool izQwEmkweO = false;
      bool EESiEyoAkI = false;
      bool UEpAFOFmNd = false;
      bool lScssqLwEy = false;
      bool PGQrjmNpok = false;
      bool BdoyzdIPqp = false;
      bool gxiAbkaZoM = false;
      bool msulsNmyQS = false;
      bool APxccHdesO = false;
      string FRMNKcNsiI;
      string oZlgLKOMmS;
      string fetGAIyEmj;
      string WOAgDqckTP;
      string tCAeeWFjex;
      string JwwVsaWGNB;
      string eIGylZZFcU;
      string hcrWYdePac;
      string CNYoaaSenc;
      string TVXRjluBsE;
      string xAGKPfDYxO;
      string wGejzQiRXK;
      string GuRABLEalm;
      string hcWVeCGOZu;
      string WtgYgMpnST;
      string CddhyChGJD;
      string aclKfTjIFw;
      string JUqbnMNsTn;
      string UQHSjEyoXb;
      string UAFWUtHWrN;
      if(FRMNKcNsiI == xAGKPfDYxO){chiVJglBsk = true;}
      else if(xAGKPfDYxO == FRMNKcNsiI){qgYsipeZGU = true;}
      if(oZlgLKOMmS == wGejzQiRXK){oomVhJUSZb = true;}
      else if(wGejzQiRXK == oZlgLKOMmS){izQwEmkweO = true;}
      if(fetGAIyEmj == GuRABLEalm){UtkcbJOUHt = true;}
      else if(GuRABLEalm == fetGAIyEmj){EESiEyoAkI = true;}
      if(WOAgDqckTP == hcWVeCGOZu){FpAGKmhlJD = true;}
      else if(hcWVeCGOZu == WOAgDqckTP){UEpAFOFmNd = true;}
      if(tCAeeWFjex == WtgYgMpnST){RwummeNjnK = true;}
      else if(WtgYgMpnST == tCAeeWFjex){lScssqLwEy = true;}
      if(JwwVsaWGNB == CddhyChGJD){YnxQrhwFsA = true;}
      else if(CddhyChGJD == JwwVsaWGNB){PGQrjmNpok = true;}
      if(eIGylZZFcU == aclKfTjIFw){RRszfyngKt = true;}
      else if(aclKfTjIFw == eIGylZZFcU){BdoyzdIPqp = true;}
      if(hcrWYdePac == JUqbnMNsTn){ahJWJXzxow = true;}
      if(CNYoaaSenc == UQHSjEyoXb){uefxUQsjNb = true;}
      if(TVXRjluBsE == UAFWUtHWrN){pbsJkADuHo = true;}
      while(JUqbnMNsTn == hcrWYdePac){gxiAbkaZoM = true;}
      while(UQHSjEyoXb == UQHSjEyoXb){msulsNmyQS = true;}
      while(UAFWUtHWrN == UAFWUtHWrN){APxccHdesO = true;}
      if(chiVJglBsk == true){chiVJglBsk = false;}
      if(oomVhJUSZb == true){oomVhJUSZb = false;}
      if(UtkcbJOUHt == true){UtkcbJOUHt = false;}
      if(FpAGKmhlJD == true){FpAGKmhlJD = false;}
      if(RwummeNjnK == true){RwummeNjnK = false;}
      if(YnxQrhwFsA == true){YnxQrhwFsA = false;}
      if(RRszfyngKt == true){RRszfyngKt = false;}
      if(ahJWJXzxow == true){ahJWJXzxow = false;}
      if(uefxUQsjNb == true){uefxUQsjNb = false;}
      if(pbsJkADuHo == true){pbsJkADuHo = false;}
      if(qgYsipeZGU == true){qgYsipeZGU = false;}
      if(izQwEmkweO == true){izQwEmkweO = false;}
      if(EESiEyoAkI == true){EESiEyoAkI = false;}
      if(UEpAFOFmNd == true){UEpAFOFmNd = false;}
      if(lScssqLwEy == true){lScssqLwEy = false;}
      if(PGQrjmNpok == true){PGQrjmNpok = false;}
      if(BdoyzdIPqp == true){BdoyzdIPqp = false;}
      if(gxiAbkaZoM == true){gxiAbkaZoM = false;}
      if(msulsNmyQS == true){msulsNmyQS = false;}
      if(APxccHdesO == true){APxccHdesO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZXCJLZBOP
{ 
  void sppuudWNUI()
  { 
      bool oOJsGVfWEK = false;
      bool LnWriHqQFD = false;
      bool JlykJxKEKd = false;
      bool NQLnSOzsmA = false;
      bool FAfEtmVOiZ = false;
      bool IBUkCCQYjI = false;
      bool KbMawuchZU = false;
      bool HxdEyJGtpW = false;
      bool bwVjUMuZlP = false;
      bool xaJdpcmEHz = false;
      bool KmoOSKXQmr = false;
      bool uWiMgOGcFj = false;
      bool zCuJWgnzOU = false;
      bool WBlpMnGGRK = false;
      bool oemtTaqwxa = false;
      bool WKzXAHrfqk = false;
      bool VYBRUsjrAs = false;
      bool HzKuuTOBow = false;
      bool oqBmxMCOpE = false;
      bool waOgnPcUYZ = false;
      string lUKooEKHiC;
      string MjaoOLSZpg;
      string wVZpjyMMKP;
      string WZAjeuNGYu;
      string JCaTlfLcmO;
      string nxuKZPtUEp;
      string qxxSfljpJT;
      string xMAtWtuFDE;
      string mjYuaZdpKO;
      string ArBiEMEHnz;
      string wVSSQbwBme;
      string UnQADHXBqG;
      string IsfuTEKRpK;
      string omREIRQGdz;
      string ccCetLaBew;
      string nDPhpCoXzM;
      string QdKbpgWMql;
      string pRWrcfqABH;
      string cJmsWlXjOG;
      string bsGRhzRZoM;
      if(lUKooEKHiC == wVSSQbwBme){oOJsGVfWEK = true;}
      else if(wVSSQbwBme == lUKooEKHiC){KmoOSKXQmr = true;}
      if(MjaoOLSZpg == UnQADHXBqG){LnWriHqQFD = true;}
      else if(UnQADHXBqG == MjaoOLSZpg){uWiMgOGcFj = true;}
      if(wVZpjyMMKP == IsfuTEKRpK){JlykJxKEKd = true;}
      else if(IsfuTEKRpK == wVZpjyMMKP){zCuJWgnzOU = true;}
      if(WZAjeuNGYu == omREIRQGdz){NQLnSOzsmA = true;}
      else if(omREIRQGdz == WZAjeuNGYu){WBlpMnGGRK = true;}
      if(JCaTlfLcmO == ccCetLaBew){FAfEtmVOiZ = true;}
      else if(ccCetLaBew == JCaTlfLcmO){oemtTaqwxa = true;}
      if(nxuKZPtUEp == nDPhpCoXzM){IBUkCCQYjI = true;}
      else if(nDPhpCoXzM == nxuKZPtUEp){WKzXAHrfqk = true;}
      if(qxxSfljpJT == QdKbpgWMql){KbMawuchZU = true;}
      else if(QdKbpgWMql == qxxSfljpJT){VYBRUsjrAs = true;}
      if(xMAtWtuFDE == pRWrcfqABH){HxdEyJGtpW = true;}
      if(mjYuaZdpKO == cJmsWlXjOG){bwVjUMuZlP = true;}
      if(ArBiEMEHnz == bsGRhzRZoM){xaJdpcmEHz = true;}
      while(pRWrcfqABH == xMAtWtuFDE){HzKuuTOBow = true;}
      while(cJmsWlXjOG == cJmsWlXjOG){oqBmxMCOpE = true;}
      while(bsGRhzRZoM == bsGRhzRZoM){waOgnPcUYZ = true;}
      if(oOJsGVfWEK == true){oOJsGVfWEK = false;}
      if(LnWriHqQFD == true){LnWriHqQFD = false;}
      if(JlykJxKEKd == true){JlykJxKEKd = false;}
      if(NQLnSOzsmA == true){NQLnSOzsmA = false;}
      if(FAfEtmVOiZ == true){FAfEtmVOiZ = false;}
      if(IBUkCCQYjI == true){IBUkCCQYjI = false;}
      if(KbMawuchZU == true){KbMawuchZU = false;}
      if(HxdEyJGtpW == true){HxdEyJGtpW = false;}
      if(bwVjUMuZlP == true){bwVjUMuZlP = false;}
      if(xaJdpcmEHz == true){xaJdpcmEHz = false;}
      if(KmoOSKXQmr == true){KmoOSKXQmr = false;}
      if(uWiMgOGcFj == true){uWiMgOGcFj = false;}
      if(zCuJWgnzOU == true){zCuJWgnzOU = false;}
      if(WBlpMnGGRK == true){WBlpMnGGRK = false;}
      if(oemtTaqwxa == true){oemtTaqwxa = false;}
      if(WKzXAHrfqk == true){WKzXAHrfqk = false;}
      if(VYBRUsjrAs == true){VYBRUsjrAs = false;}
      if(HzKuuTOBow == true){HzKuuTOBow = false;}
      if(oqBmxMCOpE == true){oqBmxMCOpE = false;}
      if(waOgnPcUYZ == true){waOgnPcUYZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNZATDKVAZ
{ 
  void UaemyBwNJH()
  { 
      bool kmPBBbDxPK = false;
      bool PYUGjeCBgx = false;
      bool FMfyzPCJVD = false;
      bool kDbueybGLG = false;
      bool sOqICLfsFu = false;
      bool ruNJPXGRCk = false;
      bool ZsaLYMxYbk = false;
      bool CwpZDpUXwm = false;
      bool jIEaKooSfG = false;
      bool qKDZfzneip = false;
      bool OGRTrwFmFY = false;
      bool CiUOBRnABi = false;
      bool WdsUtrrQtD = false;
      bool CpnGYcpkhO = false;
      bool jCNGDHooXO = false;
      bool LndATkNwZA = false;
      bool EosBWMuOpX = false;
      bool aDRmzUPlRl = false;
      bool CDrfrOLnln = false;
      bool PsKgJuILjq = false;
      string iDwLMzAgfo;
      string taWlocbnqB;
      string mSXlPzYQSr;
      string ZufwYZHYds;
      string kaZhlPQAFO;
      string zPqsEPeKwN;
      string ZiOmOytZMO;
      string UCKxPLrozA;
      string iYLEsKEmrJ;
      string txcQSCMmSm;
      string UpnpswEscr;
      string WpKwdBXKsE;
      string tHhCTXYteN;
      string zFVLeskVKx;
      string FLJzlElglR;
      string eCsOsMHkVV;
      string WKOPsRTzQj;
      string PCzwyixhQP;
      string krHMiwLHSR;
      string kAzoZuxtGU;
      if(iDwLMzAgfo == UpnpswEscr){kmPBBbDxPK = true;}
      else if(UpnpswEscr == iDwLMzAgfo){OGRTrwFmFY = true;}
      if(taWlocbnqB == WpKwdBXKsE){PYUGjeCBgx = true;}
      else if(WpKwdBXKsE == taWlocbnqB){CiUOBRnABi = true;}
      if(mSXlPzYQSr == tHhCTXYteN){FMfyzPCJVD = true;}
      else if(tHhCTXYteN == mSXlPzYQSr){WdsUtrrQtD = true;}
      if(ZufwYZHYds == zFVLeskVKx){kDbueybGLG = true;}
      else if(zFVLeskVKx == ZufwYZHYds){CpnGYcpkhO = true;}
      if(kaZhlPQAFO == FLJzlElglR){sOqICLfsFu = true;}
      else if(FLJzlElglR == kaZhlPQAFO){jCNGDHooXO = true;}
      if(zPqsEPeKwN == eCsOsMHkVV){ruNJPXGRCk = true;}
      else if(eCsOsMHkVV == zPqsEPeKwN){LndATkNwZA = true;}
      if(ZiOmOytZMO == WKOPsRTzQj){ZsaLYMxYbk = true;}
      else if(WKOPsRTzQj == ZiOmOytZMO){EosBWMuOpX = true;}
      if(UCKxPLrozA == PCzwyixhQP){CwpZDpUXwm = true;}
      if(iYLEsKEmrJ == krHMiwLHSR){jIEaKooSfG = true;}
      if(txcQSCMmSm == kAzoZuxtGU){qKDZfzneip = true;}
      while(PCzwyixhQP == UCKxPLrozA){aDRmzUPlRl = true;}
      while(krHMiwLHSR == krHMiwLHSR){CDrfrOLnln = true;}
      while(kAzoZuxtGU == kAzoZuxtGU){PsKgJuILjq = true;}
      if(kmPBBbDxPK == true){kmPBBbDxPK = false;}
      if(PYUGjeCBgx == true){PYUGjeCBgx = false;}
      if(FMfyzPCJVD == true){FMfyzPCJVD = false;}
      if(kDbueybGLG == true){kDbueybGLG = false;}
      if(sOqICLfsFu == true){sOqICLfsFu = false;}
      if(ruNJPXGRCk == true){ruNJPXGRCk = false;}
      if(ZsaLYMxYbk == true){ZsaLYMxYbk = false;}
      if(CwpZDpUXwm == true){CwpZDpUXwm = false;}
      if(jIEaKooSfG == true){jIEaKooSfG = false;}
      if(qKDZfzneip == true){qKDZfzneip = false;}
      if(OGRTrwFmFY == true){OGRTrwFmFY = false;}
      if(CiUOBRnABi == true){CiUOBRnABi = false;}
      if(WdsUtrrQtD == true){WdsUtrrQtD = false;}
      if(CpnGYcpkhO == true){CpnGYcpkhO = false;}
      if(jCNGDHooXO == true){jCNGDHooXO = false;}
      if(LndATkNwZA == true){LndATkNwZA = false;}
      if(EosBWMuOpX == true){EosBWMuOpX = false;}
      if(aDRmzUPlRl == true){aDRmzUPlRl = false;}
      if(CDrfrOLnln == true){CDrfrOLnln = false;}
      if(PsKgJuILjq == true){PsKgJuILjq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNMJKPEREC
{ 
  void PVsfgKynJf()
  { 
      bool BGmMGwmDxq = false;
      bool UCULuoHCtE = false;
      bool zkgeGzaELl = false;
      bool lxyaBgfmLg = false;
      bool YHxKKFQwFd = false;
      bool bilNVQZIFH = false;
      bool UirLFWEsKO = false;
      bool JTqNermWTB = false;
      bool idyhJCLjEj = false;
      bool GXgELpPkEn = false;
      bool AWlpUHrYhd = false;
      bool dDnEXqjJBC = false;
      bool KTnZHkmlCo = false;
      bool bBRfALrINB = false;
      bool KlCaGDibfT = false;
      bool GFjBcgiMii = false;
      bool UFWrBbkHEM = false;
      bool zbwzrYQMSD = false;
      bool BKGhiVRPDT = false;
      bool cfYdgFPKYe = false;
      string QzYLjsTBml;
      string IkylbPmnyV;
      string qeKOLEIlUd;
      string AwRAWPykwM;
      string WKxQFANKMb;
      string baNfzlnJzf;
      string jgfIkMTyOM;
      string QCrkzghtJL;
      string pyYsBYikAk;
      string bokQcodner;
      string gPuAKZhcgS;
      string EtznolImGM;
      string dhxdkbQaIJ;
      string CsOQdZCYhb;
      string pFDhggoxbp;
      string gqhSOySRPh;
      string IHUWPKfiJO;
      string jjEdVXdPxD;
      string mTzRcLKuBe;
      string HkIASikfRV;
      if(QzYLjsTBml == gPuAKZhcgS){BGmMGwmDxq = true;}
      else if(gPuAKZhcgS == QzYLjsTBml){AWlpUHrYhd = true;}
      if(IkylbPmnyV == EtznolImGM){UCULuoHCtE = true;}
      else if(EtznolImGM == IkylbPmnyV){dDnEXqjJBC = true;}
      if(qeKOLEIlUd == dhxdkbQaIJ){zkgeGzaELl = true;}
      else if(dhxdkbQaIJ == qeKOLEIlUd){KTnZHkmlCo = true;}
      if(AwRAWPykwM == CsOQdZCYhb){lxyaBgfmLg = true;}
      else if(CsOQdZCYhb == AwRAWPykwM){bBRfALrINB = true;}
      if(WKxQFANKMb == pFDhggoxbp){YHxKKFQwFd = true;}
      else if(pFDhggoxbp == WKxQFANKMb){KlCaGDibfT = true;}
      if(baNfzlnJzf == gqhSOySRPh){bilNVQZIFH = true;}
      else if(gqhSOySRPh == baNfzlnJzf){GFjBcgiMii = true;}
      if(jgfIkMTyOM == IHUWPKfiJO){UirLFWEsKO = true;}
      else if(IHUWPKfiJO == jgfIkMTyOM){UFWrBbkHEM = true;}
      if(QCrkzghtJL == jjEdVXdPxD){JTqNermWTB = true;}
      if(pyYsBYikAk == mTzRcLKuBe){idyhJCLjEj = true;}
      if(bokQcodner == HkIASikfRV){GXgELpPkEn = true;}
      while(jjEdVXdPxD == QCrkzghtJL){zbwzrYQMSD = true;}
      while(mTzRcLKuBe == mTzRcLKuBe){BKGhiVRPDT = true;}
      while(HkIASikfRV == HkIASikfRV){cfYdgFPKYe = true;}
      if(BGmMGwmDxq == true){BGmMGwmDxq = false;}
      if(UCULuoHCtE == true){UCULuoHCtE = false;}
      if(zkgeGzaELl == true){zkgeGzaELl = false;}
      if(lxyaBgfmLg == true){lxyaBgfmLg = false;}
      if(YHxKKFQwFd == true){YHxKKFQwFd = false;}
      if(bilNVQZIFH == true){bilNVQZIFH = false;}
      if(UirLFWEsKO == true){UirLFWEsKO = false;}
      if(JTqNermWTB == true){JTqNermWTB = false;}
      if(idyhJCLjEj == true){idyhJCLjEj = false;}
      if(GXgELpPkEn == true){GXgELpPkEn = false;}
      if(AWlpUHrYhd == true){AWlpUHrYhd = false;}
      if(dDnEXqjJBC == true){dDnEXqjJBC = false;}
      if(KTnZHkmlCo == true){KTnZHkmlCo = false;}
      if(bBRfALrINB == true){bBRfALrINB = false;}
      if(KlCaGDibfT == true){KlCaGDibfT = false;}
      if(GFjBcgiMii == true){GFjBcgiMii = false;}
      if(UFWrBbkHEM == true){UFWrBbkHEM = false;}
      if(zbwzrYQMSD == true){zbwzrYQMSD = false;}
      if(BKGhiVRPDT == true){BKGhiVRPDT = false;}
      if(cfYdgFPKYe == true){cfYdgFPKYe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRIDHBVXGR
{ 
  void JdEZhCMwVK()
  { 
      bool iRIOZwzFKf = false;
      bool kHUoMVwkLD = false;
      bool OqQOHiMVVg = false;
      bool fogDGWxxIV = false;
      bool XFyrGoLFJY = false;
      bool OMktMqAsGq = false;
      bool jcidzwZRhp = false;
      bool XybpeJsXIS = false;
      bool WGMwRSElpP = false;
      bool VEpRltVTrJ = false;
      bool OsXTAPkuPD = false;
      bool ycjnTcQmMg = false;
      bool rnaRTTHKEk = false;
      bool mYfyDciruB = false;
      bool hIWmQsTCyI = false;
      bool ciHLRaSFAg = false;
      bool IZqdPZxkkp = false;
      bool sYqLyiQnBZ = false;
      bool zFMuIERTgc = false;
      bool KcqOsIRsWq = false;
      string CCMoDbTbgF;
      string ONIiNOQJzA;
      string bGMASnVIoY;
      string jJclAopIWp;
      string uyQjLTNMdT;
      string FbADUupMVP;
      string FKmHUEjViY;
      string XHmIFcpboz;
      string aJeUTIIYRE;
      string ydlHkjLJPG;
      string iqcFwxnqyr;
      string FNXWnufRmL;
      string wLEdZtVfXU;
      string QfMiPjfYYW;
      string TRZYzjGPSo;
      string DsVDKXmzeB;
      string bITcaYBoHE;
      string PGsQrdledp;
      string nFMhRXKJXr;
      string wgtWuLywya;
      if(CCMoDbTbgF == iqcFwxnqyr){iRIOZwzFKf = true;}
      else if(iqcFwxnqyr == CCMoDbTbgF){OsXTAPkuPD = true;}
      if(ONIiNOQJzA == FNXWnufRmL){kHUoMVwkLD = true;}
      else if(FNXWnufRmL == ONIiNOQJzA){ycjnTcQmMg = true;}
      if(bGMASnVIoY == wLEdZtVfXU){OqQOHiMVVg = true;}
      else if(wLEdZtVfXU == bGMASnVIoY){rnaRTTHKEk = true;}
      if(jJclAopIWp == QfMiPjfYYW){fogDGWxxIV = true;}
      else if(QfMiPjfYYW == jJclAopIWp){mYfyDciruB = true;}
      if(uyQjLTNMdT == TRZYzjGPSo){XFyrGoLFJY = true;}
      else if(TRZYzjGPSo == uyQjLTNMdT){hIWmQsTCyI = true;}
      if(FbADUupMVP == DsVDKXmzeB){OMktMqAsGq = true;}
      else if(DsVDKXmzeB == FbADUupMVP){ciHLRaSFAg = true;}
      if(FKmHUEjViY == bITcaYBoHE){jcidzwZRhp = true;}
      else if(bITcaYBoHE == FKmHUEjViY){IZqdPZxkkp = true;}
      if(XHmIFcpboz == PGsQrdledp){XybpeJsXIS = true;}
      if(aJeUTIIYRE == nFMhRXKJXr){WGMwRSElpP = true;}
      if(ydlHkjLJPG == wgtWuLywya){VEpRltVTrJ = true;}
      while(PGsQrdledp == XHmIFcpboz){sYqLyiQnBZ = true;}
      while(nFMhRXKJXr == nFMhRXKJXr){zFMuIERTgc = true;}
      while(wgtWuLywya == wgtWuLywya){KcqOsIRsWq = true;}
      if(iRIOZwzFKf == true){iRIOZwzFKf = false;}
      if(kHUoMVwkLD == true){kHUoMVwkLD = false;}
      if(OqQOHiMVVg == true){OqQOHiMVVg = false;}
      if(fogDGWxxIV == true){fogDGWxxIV = false;}
      if(XFyrGoLFJY == true){XFyrGoLFJY = false;}
      if(OMktMqAsGq == true){OMktMqAsGq = false;}
      if(jcidzwZRhp == true){jcidzwZRhp = false;}
      if(XybpeJsXIS == true){XybpeJsXIS = false;}
      if(WGMwRSElpP == true){WGMwRSElpP = false;}
      if(VEpRltVTrJ == true){VEpRltVTrJ = false;}
      if(OsXTAPkuPD == true){OsXTAPkuPD = false;}
      if(ycjnTcQmMg == true){ycjnTcQmMg = false;}
      if(rnaRTTHKEk == true){rnaRTTHKEk = false;}
      if(mYfyDciruB == true){mYfyDciruB = false;}
      if(hIWmQsTCyI == true){hIWmQsTCyI = false;}
      if(ciHLRaSFAg == true){ciHLRaSFAg = false;}
      if(IZqdPZxkkp == true){IZqdPZxkkp = false;}
      if(sYqLyiQnBZ == true){sYqLyiQnBZ = false;}
      if(zFMuIERTgc == true){zFMuIERTgc = false;}
      if(KcqOsIRsWq == true){KcqOsIRsWq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BNKVGIMCZK
{ 
  void eNdQujHrjO()
  { 
      bool wZGTXxJJQF = false;
      bool QUilkwEuol = false;
      bool sKtJZNxIzs = false;
      bool DEkJINGhtY = false;
      bool CtKngKJhIH = false;
      bool LLBeZlfxsK = false;
      bool zAKWCMiYcW = false;
      bool oWAPiyzGbP = false;
      bool DOArhrCFjW = false;
      bool hJnjYCjnlU = false;
      bool ajFlRoKkua = false;
      bool lYUdGjARnJ = false;
      bool JcoGnfhQpg = false;
      bool OLTGoTJOZs = false;
      bool gRKIjIoKdn = false;
      bool CRzbLxtzxl = false;
      bool HttOMaFNol = false;
      bool alrucqSgVf = false;
      bool pWlCexLruq = false;
      bool YJRnlmWuwJ = false;
      string TyNwbNAyTf;
      string gWTWcdRixs;
      string EDBJQfqfhy;
      string tXbPxSPKbL;
      string NxDrEBqfoo;
      string uotcdPwDeu;
      string WTPVkIuDZK;
      string NHGkeGAIFP;
      string oKpsCEdzlg;
      string VLefoshgGu;
      string GmFeamhJxW;
      string PmyPGLdVSg;
      string ewQsnBcawl;
      string YSBJIBFLSO;
      string WTBPQhNOYd;
      string PMNZQKVMqY;
      string KGNLyxlnHF;
      string GRCDJKtBcF;
      string nNCRVMEasx;
      string erUsEPGpQS;
      if(TyNwbNAyTf == GmFeamhJxW){wZGTXxJJQF = true;}
      else if(GmFeamhJxW == TyNwbNAyTf){ajFlRoKkua = true;}
      if(gWTWcdRixs == PmyPGLdVSg){QUilkwEuol = true;}
      else if(PmyPGLdVSg == gWTWcdRixs){lYUdGjARnJ = true;}
      if(EDBJQfqfhy == ewQsnBcawl){sKtJZNxIzs = true;}
      else if(ewQsnBcawl == EDBJQfqfhy){JcoGnfhQpg = true;}
      if(tXbPxSPKbL == YSBJIBFLSO){DEkJINGhtY = true;}
      else if(YSBJIBFLSO == tXbPxSPKbL){OLTGoTJOZs = true;}
      if(NxDrEBqfoo == WTBPQhNOYd){CtKngKJhIH = true;}
      else if(WTBPQhNOYd == NxDrEBqfoo){gRKIjIoKdn = true;}
      if(uotcdPwDeu == PMNZQKVMqY){LLBeZlfxsK = true;}
      else if(PMNZQKVMqY == uotcdPwDeu){CRzbLxtzxl = true;}
      if(WTPVkIuDZK == KGNLyxlnHF){zAKWCMiYcW = true;}
      else if(KGNLyxlnHF == WTPVkIuDZK){HttOMaFNol = true;}
      if(NHGkeGAIFP == GRCDJKtBcF){oWAPiyzGbP = true;}
      if(oKpsCEdzlg == nNCRVMEasx){DOArhrCFjW = true;}
      if(VLefoshgGu == erUsEPGpQS){hJnjYCjnlU = true;}
      while(GRCDJKtBcF == NHGkeGAIFP){alrucqSgVf = true;}
      while(nNCRVMEasx == nNCRVMEasx){pWlCexLruq = true;}
      while(erUsEPGpQS == erUsEPGpQS){YJRnlmWuwJ = true;}
      if(wZGTXxJJQF == true){wZGTXxJJQF = false;}
      if(QUilkwEuol == true){QUilkwEuol = false;}
      if(sKtJZNxIzs == true){sKtJZNxIzs = false;}
      if(DEkJINGhtY == true){DEkJINGhtY = false;}
      if(CtKngKJhIH == true){CtKngKJhIH = false;}
      if(LLBeZlfxsK == true){LLBeZlfxsK = false;}
      if(zAKWCMiYcW == true){zAKWCMiYcW = false;}
      if(oWAPiyzGbP == true){oWAPiyzGbP = false;}
      if(DOArhrCFjW == true){DOArhrCFjW = false;}
      if(hJnjYCjnlU == true){hJnjYCjnlU = false;}
      if(ajFlRoKkua == true){ajFlRoKkua = false;}
      if(lYUdGjARnJ == true){lYUdGjARnJ = false;}
      if(JcoGnfhQpg == true){JcoGnfhQpg = false;}
      if(OLTGoTJOZs == true){OLTGoTJOZs = false;}
      if(gRKIjIoKdn == true){gRKIjIoKdn = false;}
      if(CRzbLxtzxl == true){CRzbLxtzxl = false;}
      if(HttOMaFNol == true){HttOMaFNol = false;}
      if(alrucqSgVf == true){alrucqSgVf = false;}
      if(pWlCexLruq == true){pWlCexLruq = false;}
      if(YJRnlmWuwJ == true){YJRnlmWuwJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVBHAGNHKG
{ 
  void BVCzJBaqhy()
  { 
      bool mWOlGsqcNQ = false;
      bool xJeSmGNHil = false;
      bool blqJQtKYxm = false;
      bool hVskYTkQKJ = false;
      bool VUfViDWIyE = false;
      bool MMUMiAfFVM = false;
      bool hSeZhbQssS = false;
      bool UwxZPGGUaM = false;
      bool XBZrZVBfCX = false;
      bool nfuyaDpFmH = false;
      bool mdOejQPtxc = false;
      bool tKeIofrlzM = false;
      bool ZjqUdnBzyM = false;
      bool QAgSZsmuIJ = false;
      bool GGiZddBlJt = false;
      bool KDFagCmtAw = false;
      bool PQujLscLiu = false;
      bool sxdpGTBRqA = false;
      bool lOoDBMuGlW = false;
      bool GrtMspKyNj = false;
      string OYisBngksX;
      string UOJZXSknpm;
      string SKTbHzZYdp;
      string ohlJxYqiLr;
      string gfOPDPrlIu;
      string MNsazDFHkB;
      string NIHDhlbAbz;
      string aCcyGmuDXq;
      string HnPicboLJs;
      string TjxJdXYLhR;
      string nrJJTKjtUM;
      string IBjssZrXaF;
      string xQpheqETUh;
      string NiVGDPdGOR;
      string qtpxkSAEPD;
      string eAkbTXCbec;
      string GQZlyZfcod;
      string wlJIODZrxL;
      string pADRCMxslf;
      string NBakKaUEyL;
      if(OYisBngksX == nrJJTKjtUM){mWOlGsqcNQ = true;}
      else if(nrJJTKjtUM == OYisBngksX){mdOejQPtxc = true;}
      if(UOJZXSknpm == IBjssZrXaF){xJeSmGNHil = true;}
      else if(IBjssZrXaF == UOJZXSknpm){tKeIofrlzM = true;}
      if(SKTbHzZYdp == xQpheqETUh){blqJQtKYxm = true;}
      else if(xQpheqETUh == SKTbHzZYdp){ZjqUdnBzyM = true;}
      if(ohlJxYqiLr == NiVGDPdGOR){hVskYTkQKJ = true;}
      else if(NiVGDPdGOR == ohlJxYqiLr){QAgSZsmuIJ = true;}
      if(gfOPDPrlIu == qtpxkSAEPD){VUfViDWIyE = true;}
      else if(qtpxkSAEPD == gfOPDPrlIu){GGiZddBlJt = true;}
      if(MNsazDFHkB == eAkbTXCbec){MMUMiAfFVM = true;}
      else if(eAkbTXCbec == MNsazDFHkB){KDFagCmtAw = true;}
      if(NIHDhlbAbz == GQZlyZfcod){hSeZhbQssS = true;}
      else if(GQZlyZfcod == NIHDhlbAbz){PQujLscLiu = true;}
      if(aCcyGmuDXq == wlJIODZrxL){UwxZPGGUaM = true;}
      if(HnPicboLJs == pADRCMxslf){XBZrZVBfCX = true;}
      if(TjxJdXYLhR == NBakKaUEyL){nfuyaDpFmH = true;}
      while(wlJIODZrxL == aCcyGmuDXq){sxdpGTBRqA = true;}
      while(pADRCMxslf == pADRCMxslf){lOoDBMuGlW = true;}
      while(NBakKaUEyL == NBakKaUEyL){GrtMspKyNj = true;}
      if(mWOlGsqcNQ == true){mWOlGsqcNQ = false;}
      if(xJeSmGNHil == true){xJeSmGNHil = false;}
      if(blqJQtKYxm == true){blqJQtKYxm = false;}
      if(hVskYTkQKJ == true){hVskYTkQKJ = false;}
      if(VUfViDWIyE == true){VUfViDWIyE = false;}
      if(MMUMiAfFVM == true){MMUMiAfFVM = false;}
      if(hSeZhbQssS == true){hSeZhbQssS = false;}
      if(UwxZPGGUaM == true){UwxZPGGUaM = false;}
      if(XBZrZVBfCX == true){XBZrZVBfCX = false;}
      if(nfuyaDpFmH == true){nfuyaDpFmH = false;}
      if(mdOejQPtxc == true){mdOejQPtxc = false;}
      if(tKeIofrlzM == true){tKeIofrlzM = false;}
      if(ZjqUdnBzyM == true){ZjqUdnBzyM = false;}
      if(QAgSZsmuIJ == true){QAgSZsmuIJ = false;}
      if(GGiZddBlJt == true){GGiZddBlJt = false;}
      if(KDFagCmtAw == true){KDFagCmtAw = false;}
      if(PQujLscLiu == true){PQujLscLiu = false;}
      if(sxdpGTBRqA == true){sxdpGTBRqA = false;}
      if(lOoDBMuGlW == true){lOoDBMuGlW = false;}
      if(GrtMspKyNj == true){GrtMspKyNj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUBGZWWZNW
{ 
  void urfFthVKKB()
  { 
      bool DlwONUzeuR = false;
      bool fHZCtAjKoI = false;
      bool RutlMmfiGO = false;
      bool uDbcqxfMyk = false;
      bool ageRlFRFuB = false;
      bool MrsHBIrKBa = false;
      bool oQXgWbfwKw = false;
      bool UWLDhkPbzG = false;
      bool UZmEBCJTbi = false;
      bool FVKXwJIyuJ = false;
      bool YUtygpfpYP = false;
      bool rPKtFOcSeU = false;
      bool SMUbqyLnGX = false;
      bool bRgohzfoWL = false;
      bool VTtLpoKPSh = false;
      bool goSZqMASGh = false;
      bool driBmaiUMF = false;
      bool inuTyyRIlB = false;
      bool nuVYqlyGyU = false;
      bool yMhohdjsXO = false;
      string wqcJMjxPuK;
      string tPzDiNORxa;
      string UnhHDTNjYQ;
      string HTLbikRuWH;
      string MGJbQlOjOZ;
      string bWRXuIIVGs;
      string VNpeCaDXUx;
      string uTtpNOeFpR;
      string EdVynjBnfa;
      string cuodkzPeYo;
      string hqPQdHbbJg;
      string dCennrqrpS;
      string YPqsUAdQEO;
      string yAgBjNNETg;
      string HZdzxZQBor;
      string HXnGQRzVwd;
      string dLWuidVdEa;
      string emXJKylqwt;
      string jcbLGZLajR;
      string NqHoCwDhPS;
      if(wqcJMjxPuK == hqPQdHbbJg){DlwONUzeuR = true;}
      else if(hqPQdHbbJg == wqcJMjxPuK){YUtygpfpYP = true;}
      if(tPzDiNORxa == dCennrqrpS){fHZCtAjKoI = true;}
      else if(dCennrqrpS == tPzDiNORxa){rPKtFOcSeU = true;}
      if(UnhHDTNjYQ == YPqsUAdQEO){RutlMmfiGO = true;}
      else if(YPqsUAdQEO == UnhHDTNjYQ){SMUbqyLnGX = true;}
      if(HTLbikRuWH == yAgBjNNETg){uDbcqxfMyk = true;}
      else if(yAgBjNNETg == HTLbikRuWH){bRgohzfoWL = true;}
      if(MGJbQlOjOZ == HZdzxZQBor){ageRlFRFuB = true;}
      else if(HZdzxZQBor == MGJbQlOjOZ){VTtLpoKPSh = true;}
      if(bWRXuIIVGs == HXnGQRzVwd){MrsHBIrKBa = true;}
      else if(HXnGQRzVwd == bWRXuIIVGs){goSZqMASGh = true;}
      if(VNpeCaDXUx == dLWuidVdEa){oQXgWbfwKw = true;}
      else if(dLWuidVdEa == VNpeCaDXUx){driBmaiUMF = true;}
      if(uTtpNOeFpR == emXJKylqwt){UWLDhkPbzG = true;}
      if(EdVynjBnfa == jcbLGZLajR){UZmEBCJTbi = true;}
      if(cuodkzPeYo == NqHoCwDhPS){FVKXwJIyuJ = true;}
      while(emXJKylqwt == uTtpNOeFpR){inuTyyRIlB = true;}
      while(jcbLGZLajR == jcbLGZLajR){nuVYqlyGyU = true;}
      while(NqHoCwDhPS == NqHoCwDhPS){yMhohdjsXO = true;}
      if(DlwONUzeuR == true){DlwONUzeuR = false;}
      if(fHZCtAjKoI == true){fHZCtAjKoI = false;}
      if(RutlMmfiGO == true){RutlMmfiGO = false;}
      if(uDbcqxfMyk == true){uDbcqxfMyk = false;}
      if(ageRlFRFuB == true){ageRlFRFuB = false;}
      if(MrsHBIrKBa == true){MrsHBIrKBa = false;}
      if(oQXgWbfwKw == true){oQXgWbfwKw = false;}
      if(UWLDhkPbzG == true){UWLDhkPbzG = false;}
      if(UZmEBCJTbi == true){UZmEBCJTbi = false;}
      if(FVKXwJIyuJ == true){FVKXwJIyuJ = false;}
      if(YUtygpfpYP == true){YUtygpfpYP = false;}
      if(rPKtFOcSeU == true){rPKtFOcSeU = false;}
      if(SMUbqyLnGX == true){SMUbqyLnGX = false;}
      if(bRgohzfoWL == true){bRgohzfoWL = false;}
      if(VTtLpoKPSh == true){VTtLpoKPSh = false;}
      if(goSZqMASGh == true){goSZqMASGh = false;}
      if(driBmaiUMF == true){driBmaiUMF = false;}
      if(inuTyyRIlB == true){inuTyyRIlB = false;}
      if(nuVYqlyGyU == true){nuVYqlyGyU = false;}
      if(yMhohdjsXO == true){yMhohdjsXO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TZEFMNQOSU
{ 
  void PqpupuamsC()
  { 
      bool rwyGXUxPfr = false;
      bool TSHzlLmNlU = false;
      bool fEKJVbPipW = false;
      bool TyHiVjlTHq = false;
      bool gsuKdhQHri = false;
      bool tpEYXnloju = false;
      bool ENYIYUKXcB = false;
      bool ZSFtmlIzen = false;
      bool LIqHccsiKh = false;
      bool ywjMmSTllJ = false;
      bool WrdpJakKkk = false;
      bool elJwjwWRfw = false;
      bool abMuDcisHT = false;
      bool RVNVQSdBxB = false;
      bool qixYCMmmbp = false;
      bool wBGphteimg = false;
      bool qrDQTJYneR = false;
      bool RVUdErdmrq = false;
      bool pwQQXQPXnW = false;
      bool muOQKzegFs = false;
      string OioSzGmSlO;
      string CNKIILtSzq;
      string xZsDHYsYAf;
      string CmohiFcguE;
      string zmjwzMpADs;
      string BosuzookKZ;
      string MORGMPYbZC;
      string iNXuqKowDu;
      string isVHdMtshs;
      string QqVUqkUdjj;
      string nNaAKmQxEo;
      string ArgOqSrKbz;
      string UetflqqDDF;
      string oKMSHUSUxq;
      string uxossXKGcX;
      string rKBjPJTtNS;
      string wNsyzofNHW;
      string AXNkEWoBmN;
      string gjZfMeJbDy;
      string AXHdtgDpsD;
      if(OioSzGmSlO == nNaAKmQxEo){rwyGXUxPfr = true;}
      else if(nNaAKmQxEo == OioSzGmSlO){WrdpJakKkk = true;}
      if(CNKIILtSzq == ArgOqSrKbz){TSHzlLmNlU = true;}
      else if(ArgOqSrKbz == CNKIILtSzq){elJwjwWRfw = true;}
      if(xZsDHYsYAf == UetflqqDDF){fEKJVbPipW = true;}
      else if(UetflqqDDF == xZsDHYsYAf){abMuDcisHT = true;}
      if(CmohiFcguE == oKMSHUSUxq){TyHiVjlTHq = true;}
      else if(oKMSHUSUxq == CmohiFcguE){RVNVQSdBxB = true;}
      if(zmjwzMpADs == uxossXKGcX){gsuKdhQHri = true;}
      else if(uxossXKGcX == zmjwzMpADs){qixYCMmmbp = true;}
      if(BosuzookKZ == rKBjPJTtNS){tpEYXnloju = true;}
      else if(rKBjPJTtNS == BosuzookKZ){wBGphteimg = true;}
      if(MORGMPYbZC == wNsyzofNHW){ENYIYUKXcB = true;}
      else if(wNsyzofNHW == MORGMPYbZC){qrDQTJYneR = true;}
      if(iNXuqKowDu == AXNkEWoBmN){ZSFtmlIzen = true;}
      if(isVHdMtshs == gjZfMeJbDy){LIqHccsiKh = true;}
      if(QqVUqkUdjj == AXHdtgDpsD){ywjMmSTllJ = true;}
      while(AXNkEWoBmN == iNXuqKowDu){RVUdErdmrq = true;}
      while(gjZfMeJbDy == gjZfMeJbDy){pwQQXQPXnW = true;}
      while(AXHdtgDpsD == AXHdtgDpsD){muOQKzegFs = true;}
      if(rwyGXUxPfr == true){rwyGXUxPfr = false;}
      if(TSHzlLmNlU == true){TSHzlLmNlU = false;}
      if(fEKJVbPipW == true){fEKJVbPipW = false;}
      if(TyHiVjlTHq == true){TyHiVjlTHq = false;}
      if(gsuKdhQHri == true){gsuKdhQHri = false;}
      if(tpEYXnloju == true){tpEYXnloju = false;}
      if(ENYIYUKXcB == true){ENYIYUKXcB = false;}
      if(ZSFtmlIzen == true){ZSFtmlIzen = false;}
      if(LIqHccsiKh == true){LIqHccsiKh = false;}
      if(ywjMmSTllJ == true){ywjMmSTllJ = false;}
      if(WrdpJakKkk == true){WrdpJakKkk = false;}
      if(elJwjwWRfw == true){elJwjwWRfw = false;}
      if(abMuDcisHT == true){abMuDcisHT = false;}
      if(RVNVQSdBxB == true){RVNVQSdBxB = false;}
      if(qixYCMmmbp == true){qixYCMmmbp = false;}
      if(wBGphteimg == true){wBGphteimg = false;}
      if(qrDQTJYneR == true){qrDQTJYneR = false;}
      if(RVUdErdmrq == true){RVUdErdmrq = false;}
      if(pwQQXQPXnW == true){pwQQXQPXnW = false;}
      if(muOQKzegFs == true){muOQKzegFs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQEBMEGKGC
{ 
  void JbMcCrTOBk()
  { 
      bool bneLgzqowL = false;
      bool KhfbNqfKMj = false;
      bool ceGAIXyFNG = false;
      bool RemfUlkYXb = false;
      bool TOTPzgDzke = false;
      bool actRIwgdCJ = false;
      bool BlbpsetzHb = false;
      bool GGmjPOLqBa = false;
      bool UyTifnjVXX = false;
      bool EGVOahmcWU = false;
      bool mDrJXTpKBs = false;
      bool kpcanDRrKE = false;
      bool tYbiXzkXJh = false;
      bool ahUgnRFKKL = false;
      bool yZUdmOctZW = false;
      bool QtSRZNaIlY = false;
      bool iRASRCVwmW = false;
      bool xGgyFUEywJ = false;
      bool WpylRgOCGa = false;
      bool pxYlcfYBLj = false;
      string YmNrjSQVOl;
      string MBhTsjXEyU;
      string EAzSniOxDO;
      string yofyDgqKsd;
      string SHlfyBpzEd;
      string YscrzYntDB;
      string DSRAnWVjPM;
      string sMKTBwNSTl;
      string rPrYoEMmyd;
      string rwHraAokrb;
      string fGirkMhIpC;
      string KVZRImZsLi;
      string KikkTwFSrB;
      string HcZrGkgAnb;
      string VDwwTWVpin;
      string ZwYJRwVxXn;
      string GPPouhuhKX;
      string GZEiMGlnRw;
      string ZPjEbKEPaJ;
      string OibzVGnHBl;
      if(YmNrjSQVOl == fGirkMhIpC){bneLgzqowL = true;}
      else if(fGirkMhIpC == YmNrjSQVOl){mDrJXTpKBs = true;}
      if(MBhTsjXEyU == KVZRImZsLi){KhfbNqfKMj = true;}
      else if(KVZRImZsLi == MBhTsjXEyU){kpcanDRrKE = true;}
      if(EAzSniOxDO == KikkTwFSrB){ceGAIXyFNG = true;}
      else if(KikkTwFSrB == EAzSniOxDO){tYbiXzkXJh = true;}
      if(yofyDgqKsd == HcZrGkgAnb){RemfUlkYXb = true;}
      else if(HcZrGkgAnb == yofyDgqKsd){ahUgnRFKKL = true;}
      if(SHlfyBpzEd == VDwwTWVpin){TOTPzgDzke = true;}
      else if(VDwwTWVpin == SHlfyBpzEd){yZUdmOctZW = true;}
      if(YscrzYntDB == ZwYJRwVxXn){actRIwgdCJ = true;}
      else if(ZwYJRwVxXn == YscrzYntDB){QtSRZNaIlY = true;}
      if(DSRAnWVjPM == GPPouhuhKX){BlbpsetzHb = true;}
      else if(GPPouhuhKX == DSRAnWVjPM){iRASRCVwmW = true;}
      if(sMKTBwNSTl == GZEiMGlnRw){GGmjPOLqBa = true;}
      if(rPrYoEMmyd == ZPjEbKEPaJ){UyTifnjVXX = true;}
      if(rwHraAokrb == OibzVGnHBl){EGVOahmcWU = true;}
      while(GZEiMGlnRw == sMKTBwNSTl){xGgyFUEywJ = true;}
      while(ZPjEbKEPaJ == ZPjEbKEPaJ){WpylRgOCGa = true;}
      while(OibzVGnHBl == OibzVGnHBl){pxYlcfYBLj = true;}
      if(bneLgzqowL == true){bneLgzqowL = false;}
      if(KhfbNqfKMj == true){KhfbNqfKMj = false;}
      if(ceGAIXyFNG == true){ceGAIXyFNG = false;}
      if(RemfUlkYXb == true){RemfUlkYXb = false;}
      if(TOTPzgDzke == true){TOTPzgDzke = false;}
      if(actRIwgdCJ == true){actRIwgdCJ = false;}
      if(BlbpsetzHb == true){BlbpsetzHb = false;}
      if(GGmjPOLqBa == true){GGmjPOLqBa = false;}
      if(UyTifnjVXX == true){UyTifnjVXX = false;}
      if(EGVOahmcWU == true){EGVOahmcWU = false;}
      if(mDrJXTpKBs == true){mDrJXTpKBs = false;}
      if(kpcanDRrKE == true){kpcanDRrKE = false;}
      if(tYbiXzkXJh == true){tYbiXzkXJh = false;}
      if(ahUgnRFKKL == true){ahUgnRFKKL = false;}
      if(yZUdmOctZW == true){yZUdmOctZW = false;}
      if(QtSRZNaIlY == true){QtSRZNaIlY = false;}
      if(iRASRCVwmW == true){iRASRCVwmW = false;}
      if(xGgyFUEywJ == true){xGgyFUEywJ = false;}
      if(WpylRgOCGa == true){WpylRgOCGa = false;}
      if(pxYlcfYBLj == true){pxYlcfYBLj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMTTLOBRYU
{ 
  void qmWOPkGQaS()
  { 
      bool OVkzKaKohV = false;
      bool prwEGSMbFB = false;
      bool jJzuJKIfrR = false;
      bool EVHwKfPAfb = false;
      bool azOjsaSsTj = false;
      bool zMWgBEVppz = false;
      bool RdwPQTjzsa = false;
      bool CMwcajuOBh = false;
      bool qPLIRqzatG = false;
      bool JZJfKwDyTY = false;
      bool pTzshmQsFQ = false;
      bool IHnHICSmxY = false;
      bool UJEmQbCQSd = false;
      bool gxubqXPRae = false;
      bool aFUdyClCWI = false;
      bool dQBtEgOMcF = false;
      bool kAabjLMLPk = false;
      bool lAMSyPoaoN = false;
      bool pzsJAQuAXK = false;
      bool JDoUsZdstl = false;
      string izXEMeqyOR;
      string axrnDzSlVH;
      string eHKIxbsFml;
      string xYePkYSdwp;
      string ETfkTuZbDR;
      string bgXxCaoPHj;
      string llLcUCSbDe;
      string fopeDLbZnC;
      string CRBUJQAgNJ;
      string jDVLERICQR;
      string byXYkmqstq;
      string yObFhTjpSD;
      string BlNstcSdak;
      string DYIVZEtciW;
      string YHlWLUaQdj;
      string hRjMPpjddI;
      string TMRImYGFed;
      string ZHGuetzqhZ;
      string BBApDkowGj;
      string TPyaCMocil;
      if(izXEMeqyOR == byXYkmqstq){OVkzKaKohV = true;}
      else if(byXYkmqstq == izXEMeqyOR){pTzshmQsFQ = true;}
      if(axrnDzSlVH == yObFhTjpSD){prwEGSMbFB = true;}
      else if(yObFhTjpSD == axrnDzSlVH){IHnHICSmxY = true;}
      if(eHKIxbsFml == BlNstcSdak){jJzuJKIfrR = true;}
      else if(BlNstcSdak == eHKIxbsFml){UJEmQbCQSd = true;}
      if(xYePkYSdwp == DYIVZEtciW){EVHwKfPAfb = true;}
      else if(DYIVZEtciW == xYePkYSdwp){gxubqXPRae = true;}
      if(ETfkTuZbDR == YHlWLUaQdj){azOjsaSsTj = true;}
      else if(YHlWLUaQdj == ETfkTuZbDR){aFUdyClCWI = true;}
      if(bgXxCaoPHj == hRjMPpjddI){zMWgBEVppz = true;}
      else if(hRjMPpjddI == bgXxCaoPHj){dQBtEgOMcF = true;}
      if(llLcUCSbDe == TMRImYGFed){RdwPQTjzsa = true;}
      else if(TMRImYGFed == llLcUCSbDe){kAabjLMLPk = true;}
      if(fopeDLbZnC == ZHGuetzqhZ){CMwcajuOBh = true;}
      if(CRBUJQAgNJ == BBApDkowGj){qPLIRqzatG = true;}
      if(jDVLERICQR == TPyaCMocil){JZJfKwDyTY = true;}
      while(ZHGuetzqhZ == fopeDLbZnC){lAMSyPoaoN = true;}
      while(BBApDkowGj == BBApDkowGj){pzsJAQuAXK = true;}
      while(TPyaCMocil == TPyaCMocil){JDoUsZdstl = true;}
      if(OVkzKaKohV == true){OVkzKaKohV = false;}
      if(prwEGSMbFB == true){prwEGSMbFB = false;}
      if(jJzuJKIfrR == true){jJzuJKIfrR = false;}
      if(EVHwKfPAfb == true){EVHwKfPAfb = false;}
      if(azOjsaSsTj == true){azOjsaSsTj = false;}
      if(zMWgBEVppz == true){zMWgBEVppz = false;}
      if(RdwPQTjzsa == true){RdwPQTjzsa = false;}
      if(CMwcajuOBh == true){CMwcajuOBh = false;}
      if(qPLIRqzatG == true){qPLIRqzatG = false;}
      if(JZJfKwDyTY == true){JZJfKwDyTY = false;}
      if(pTzshmQsFQ == true){pTzshmQsFQ = false;}
      if(IHnHICSmxY == true){IHnHICSmxY = false;}
      if(UJEmQbCQSd == true){UJEmQbCQSd = false;}
      if(gxubqXPRae == true){gxubqXPRae = false;}
      if(aFUdyClCWI == true){aFUdyClCWI = false;}
      if(dQBtEgOMcF == true){dQBtEgOMcF = false;}
      if(kAabjLMLPk == true){kAabjLMLPk = false;}
      if(lAMSyPoaoN == true){lAMSyPoaoN = false;}
      if(pzsJAQuAXK == true){pzsJAQuAXK = false;}
      if(JDoUsZdstl == true){JDoUsZdstl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COGKVZPDHK
{ 
  void idDjqjJpix()
  { 
      bool RgBNFNecax = false;
      bool zqsYgjZAnL = false;
      bool bfUfRADTjY = false;
      bool qFkMfQJoiR = false;
      bool waKjalgMwX = false;
      bool aLCOlkMVuF = false;
      bool KLsCFtGgrQ = false;
      bool akQWPBVjEf = false;
      bool SpWLxeCVat = false;
      bool EmscHjgHeg = false;
      bool fAUexotfyk = false;
      bool PbQPlTnhEZ = false;
      bool qjFxLmqnOe = false;
      bool TNFXzRVqOI = false;
      bool jWXpdbVcpn = false;
      bool uzDEoutWSJ = false;
      bool yGQSRCWsPU = false;
      bool ywTwpTMPTi = false;
      bool RNxajTKAhE = false;
      bool XyXFKdGEYb = false;
      string aQeJqOHWFV;
      string HdNYQyyKpy;
      string DaSGEKDuqo;
      string AsFjBptrQQ;
      string NPiZScEPgS;
      string VhioezyYFg;
      string LMeQVNYcXa;
      string EGtZknrrma;
      string GnOXTRJQEB;
      string qVliEBjSEE;
      string EaqGOPnJEq;
      string GGkdaXxHwD;
      string EIYVihTKUi;
      string EZmhWewIJE;
      string dALNukjIIg;
      string DcVBAwCUWf;
      string ucnUmgSCGu;
      string aoxrZDwKay;
      string yKCnfaElha;
      string cakdIBLqZO;
      if(aQeJqOHWFV == EaqGOPnJEq){RgBNFNecax = true;}
      else if(EaqGOPnJEq == aQeJqOHWFV){fAUexotfyk = true;}
      if(HdNYQyyKpy == GGkdaXxHwD){zqsYgjZAnL = true;}
      else if(GGkdaXxHwD == HdNYQyyKpy){PbQPlTnhEZ = true;}
      if(DaSGEKDuqo == EIYVihTKUi){bfUfRADTjY = true;}
      else if(EIYVihTKUi == DaSGEKDuqo){qjFxLmqnOe = true;}
      if(AsFjBptrQQ == EZmhWewIJE){qFkMfQJoiR = true;}
      else if(EZmhWewIJE == AsFjBptrQQ){TNFXzRVqOI = true;}
      if(NPiZScEPgS == dALNukjIIg){waKjalgMwX = true;}
      else if(dALNukjIIg == NPiZScEPgS){jWXpdbVcpn = true;}
      if(VhioezyYFg == DcVBAwCUWf){aLCOlkMVuF = true;}
      else if(DcVBAwCUWf == VhioezyYFg){uzDEoutWSJ = true;}
      if(LMeQVNYcXa == ucnUmgSCGu){KLsCFtGgrQ = true;}
      else if(ucnUmgSCGu == LMeQVNYcXa){yGQSRCWsPU = true;}
      if(EGtZknrrma == aoxrZDwKay){akQWPBVjEf = true;}
      if(GnOXTRJQEB == yKCnfaElha){SpWLxeCVat = true;}
      if(qVliEBjSEE == cakdIBLqZO){EmscHjgHeg = true;}
      while(aoxrZDwKay == EGtZknrrma){ywTwpTMPTi = true;}
      while(yKCnfaElha == yKCnfaElha){RNxajTKAhE = true;}
      while(cakdIBLqZO == cakdIBLqZO){XyXFKdGEYb = true;}
      if(RgBNFNecax == true){RgBNFNecax = false;}
      if(zqsYgjZAnL == true){zqsYgjZAnL = false;}
      if(bfUfRADTjY == true){bfUfRADTjY = false;}
      if(qFkMfQJoiR == true){qFkMfQJoiR = false;}
      if(waKjalgMwX == true){waKjalgMwX = false;}
      if(aLCOlkMVuF == true){aLCOlkMVuF = false;}
      if(KLsCFtGgrQ == true){KLsCFtGgrQ = false;}
      if(akQWPBVjEf == true){akQWPBVjEf = false;}
      if(SpWLxeCVat == true){SpWLxeCVat = false;}
      if(EmscHjgHeg == true){EmscHjgHeg = false;}
      if(fAUexotfyk == true){fAUexotfyk = false;}
      if(PbQPlTnhEZ == true){PbQPlTnhEZ = false;}
      if(qjFxLmqnOe == true){qjFxLmqnOe = false;}
      if(TNFXzRVqOI == true){TNFXzRVqOI = false;}
      if(jWXpdbVcpn == true){jWXpdbVcpn = false;}
      if(uzDEoutWSJ == true){uzDEoutWSJ = false;}
      if(yGQSRCWsPU == true){yGQSRCWsPU = false;}
      if(ywTwpTMPTi == true){ywTwpTMPTi = false;}
      if(RNxajTKAhE == true){RNxajTKAhE = false;}
      if(XyXFKdGEYb == true){XyXFKdGEYb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCPZEZQVYI
{ 
  void ySbdtzABGu()
  { 
      bool fSBmZKiHhh = false;
      bool dpaTrrxnZQ = false;
      bool rQqVpEbuIf = false;
      bool Uxkyywmtfl = false;
      bool fbiVJmPUNG = false;
      bool HbgqGPafwV = false;
      bool hnzCMgEcUw = false;
      bool FCInkPhVLC = false;
      bool oHhBYsPsri = false;
      bool UHxKDqcfJb = false;
      bool hmzQBETsGp = false;
      bool hFTtgaFxdS = false;
      bool QLjlaxEyjs = false;
      bool mBLjUBHQAT = false;
      bool ZWmBBPnDcc = false;
      bool leCpLWCNoD = false;
      bool zVIMDgsjYe = false;
      bool TnxKstXikL = false;
      bool JAUHGHzVYx = false;
      bool zsbwTDOZyU = false;
      string eaoUMqqwtV;
      string nfCuzsFcDf;
      string IEjiDAYClr;
      string yJaAZYlKAx;
      string XIELuSUQUq;
      string cucDfZqFRM;
      string RoJCXeECVa;
      string HtbGIzAXnk;
      string eIhuOCgXUz;
      string gfsneizBmQ;
      string ORtsiiSVuf;
      string ZSRggJGNmU;
      string xfhVsbBnaY;
      string AyjWVNOoMf;
      string jLcnZONMGU;
      string bkOSThjXzG;
      string getVfbhuKT;
      string uRBGklDswe;
      string OogGwOiRDn;
      string dpoFyEQGIy;
      if(eaoUMqqwtV == ORtsiiSVuf){fSBmZKiHhh = true;}
      else if(ORtsiiSVuf == eaoUMqqwtV){hmzQBETsGp = true;}
      if(nfCuzsFcDf == ZSRggJGNmU){dpaTrrxnZQ = true;}
      else if(ZSRggJGNmU == nfCuzsFcDf){hFTtgaFxdS = true;}
      if(IEjiDAYClr == xfhVsbBnaY){rQqVpEbuIf = true;}
      else if(xfhVsbBnaY == IEjiDAYClr){QLjlaxEyjs = true;}
      if(yJaAZYlKAx == AyjWVNOoMf){Uxkyywmtfl = true;}
      else if(AyjWVNOoMf == yJaAZYlKAx){mBLjUBHQAT = true;}
      if(XIELuSUQUq == jLcnZONMGU){fbiVJmPUNG = true;}
      else if(jLcnZONMGU == XIELuSUQUq){ZWmBBPnDcc = true;}
      if(cucDfZqFRM == bkOSThjXzG){HbgqGPafwV = true;}
      else if(bkOSThjXzG == cucDfZqFRM){leCpLWCNoD = true;}
      if(RoJCXeECVa == getVfbhuKT){hnzCMgEcUw = true;}
      else if(getVfbhuKT == RoJCXeECVa){zVIMDgsjYe = true;}
      if(HtbGIzAXnk == uRBGklDswe){FCInkPhVLC = true;}
      if(eIhuOCgXUz == OogGwOiRDn){oHhBYsPsri = true;}
      if(gfsneizBmQ == dpoFyEQGIy){UHxKDqcfJb = true;}
      while(uRBGklDswe == HtbGIzAXnk){TnxKstXikL = true;}
      while(OogGwOiRDn == OogGwOiRDn){JAUHGHzVYx = true;}
      while(dpoFyEQGIy == dpoFyEQGIy){zsbwTDOZyU = true;}
      if(fSBmZKiHhh == true){fSBmZKiHhh = false;}
      if(dpaTrrxnZQ == true){dpaTrrxnZQ = false;}
      if(rQqVpEbuIf == true){rQqVpEbuIf = false;}
      if(Uxkyywmtfl == true){Uxkyywmtfl = false;}
      if(fbiVJmPUNG == true){fbiVJmPUNG = false;}
      if(HbgqGPafwV == true){HbgqGPafwV = false;}
      if(hnzCMgEcUw == true){hnzCMgEcUw = false;}
      if(FCInkPhVLC == true){FCInkPhVLC = false;}
      if(oHhBYsPsri == true){oHhBYsPsri = false;}
      if(UHxKDqcfJb == true){UHxKDqcfJb = false;}
      if(hmzQBETsGp == true){hmzQBETsGp = false;}
      if(hFTtgaFxdS == true){hFTtgaFxdS = false;}
      if(QLjlaxEyjs == true){QLjlaxEyjs = false;}
      if(mBLjUBHQAT == true){mBLjUBHQAT = false;}
      if(ZWmBBPnDcc == true){ZWmBBPnDcc = false;}
      if(leCpLWCNoD == true){leCpLWCNoD = false;}
      if(zVIMDgsjYe == true){zVIMDgsjYe = false;}
      if(TnxKstXikL == true){TnxKstXikL = false;}
      if(JAUHGHzVYx == true){JAUHGHzVYx = false;}
      if(zsbwTDOZyU == true){zsbwTDOZyU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFYSEMQORO
{ 
  void QPLqNpCXlf()
  { 
      bool jCSudwhkVi = false;
      bool bAwINEdbDT = false;
      bool IKnjBbByPW = false;
      bool PyCiMWnsKy = false;
      bool xIzmDecBBt = false;
      bool TcXzTZOhsB = false;
      bool tiUyTcyMwp = false;
      bool PjQFWAKAgW = false;
      bool yAwVDmaDPm = false;
      bool IFzIDNmATZ = false;
      bool gPFLdiLScT = false;
      bool ONBWDtmzuf = false;
      bool CuxIgKkHBI = false;
      bool NKgGoitkqU = false;
      bool aIZuXuEcFI = false;
      bool amEmXlRwdT = false;
      bool yEQTFDgtgU = false;
      bool zBHaFtUBjl = false;
      bool FHBsgZGsiD = false;
      bool QyHXWWqGoU = false;
      string oRYlPOfnRt;
      string eusFzudySo;
      string xapQINxTrh;
      string NfUJogIIRg;
      string yJIGtbwPkO;
      string WPXrPOaIdC;
      string QLwjgyajQS;
      string mUfkpnSjVg;
      string QgidLxIbtZ;
      string FzeOPlNYYu;
      string AMySaBilCa;
      string uplwljcRYi;
      string pzopMmpRUE;
      string asLafDhQDJ;
      string OVYSePNicf;
      string JuApEBWIFm;
      string LRQyzCeKPh;
      string BMNOTUZVLx;
      string ZHnotesUWe;
      string fZKPyxEaTb;
      if(oRYlPOfnRt == AMySaBilCa){jCSudwhkVi = true;}
      else if(AMySaBilCa == oRYlPOfnRt){gPFLdiLScT = true;}
      if(eusFzudySo == uplwljcRYi){bAwINEdbDT = true;}
      else if(uplwljcRYi == eusFzudySo){ONBWDtmzuf = true;}
      if(xapQINxTrh == pzopMmpRUE){IKnjBbByPW = true;}
      else if(pzopMmpRUE == xapQINxTrh){CuxIgKkHBI = true;}
      if(NfUJogIIRg == asLafDhQDJ){PyCiMWnsKy = true;}
      else if(asLafDhQDJ == NfUJogIIRg){NKgGoitkqU = true;}
      if(yJIGtbwPkO == OVYSePNicf){xIzmDecBBt = true;}
      else if(OVYSePNicf == yJIGtbwPkO){aIZuXuEcFI = true;}
      if(WPXrPOaIdC == JuApEBWIFm){TcXzTZOhsB = true;}
      else if(JuApEBWIFm == WPXrPOaIdC){amEmXlRwdT = true;}
      if(QLwjgyajQS == LRQyzCeKPh){tiUyTcyMwp = true;}
      else if(LRQyzCeKPh == QLwjgyajQS){yEQTFDgtgU = true;}
      if(mUfkpnSjVg == BMNOTUZVLx){PjQFWAKAgW = true;}
      if(QgidLxIbtZ == ZHnotesUWe){yAwVDmaDPm = true;}
      if(FzeOPlNYYu == fZKPyxEaTb){IFzIDNmATZ = true;}
      while(BMNOTUZVLx == mUfkpnSjVg){zBHaFtUBjl = true;}
      while(ZHnotesUWe == ZHnotesUWe){FHBsgZGsiD = true;}
      while(fZKPyxEaTb == fZKPyxEaTb){QyHXWWqGoU = true;}
      if(jCSudwhkVi == true){jCSudwhkVi = false;}
      if(bAwINEdbDT == true){bAwINEdbDT = false;}
      if(IKnjBbByPW == true){IKnjBbByPW = false;}
      if(PyCiMWnsKy == true){PyCiMWnsKy = false;}
      if(xIzmDecBBt == true){xIzmDecBBt = false;}
      if(TcXzTZOhsB == true){TcXzTZOhsB = false;}
      if(tiUyTcyMwp == true){tiUyTcyMwp = false;}
      if(PjQFWAKAgW == true){PjQFWAKAgW = false;}
      if(yAwVDmaDPm == true){yAwVDmaDPm = false;}
      if(IFzIDNmATZ == true){IFzIDNmATZ = false;}
      if(gPFLdiLScT == true){gPFLdiLScT = false;}
      if(ONBWDtmzuf == true){ONBWDtmzuf = false;}
      if(CuxIgKkHBI == true){CuxIgKkHBI = false;}
      if(NKgGoitkqU == true){NKgGoitkqU = false;}
      if(aIZuXuEcFI == true){aIZuXuEcFI = false;}
      if(amEmXlRwdT == true){amEmXlRwdT = false;}
      if(yEQTFDgtgU == true){yEQTFDgtgU = false;}
      if(zBHaFtUBjl == true){zBHaFtUBjl = false;}
      if(FHBsgZGsiD == true){FHBsgZGsiD = false;}
      if(QyHXWWqGoU == true){QyHXWWqGoU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKBZLAYCWI
{ 
  void fWKZfkgcrU()
  { 
      bool goVOOCCyYO = false;
      bool jTqYRumFiP = false;
      bool nlkVXSFkrE = false;
      bool WhGbFtMVzS = false;
      bool KBQGaHUJxA = false;
      bool UoRDGtDApw = false;
      bool xQFUrCMOTX = false;
      bool hRGQFlUdtQ = false;
      bool xunrjhQCVK = false;
      bool pMfCUsuwOY = false;
      bool tFpZRCiAyT = false;
      bool YZFYyBcMkJ = false;
      bool lJrIgVlDuL = false;
      bool qYOUVrENag = false;
      bool yPEClPGGET = false;
      bool PiKFmkMhru = false;
      bool QfFmcALkDG = false;
      bool wPlELVFpWR = false;
      bool PeybuHOJhk = false;
      bool eWVePSKQYk = false;
      string xqQBmLJeNy;
      string anubnQSZnE;
      string YneqDbSWOK;
      string EKcbQbeOsm;
      string PlCXbRmcTR;
      string TCYGiJMYyK;
      string smPDtQKSKL;
      string kDgAomkGOl;
      string opCxpBkWsG;
      string PFQhtbVzdL;
      string GTRHfQVXRu;
      string YFJMUCjRNr;
      string enYEwemyFM;
      string RkcDeVYuQY;
      string fMFyhJuDNr;
      string qDllgStNLB;
      string dXSEdmcGhz;
      string doBnMRiaWl;
      string iijNUNzpVL;
      string aLiPuHtATt;
      if(xqQBmLJeNy == GTRHfQVXRu){goVOOCCyYO = true;}
      else if(GTRHfQVXRu == xqQBmLJeNy){tFpZRCiAyT = true;}
      if(anubnQSZnE == YFJMUCjRNr){jTqYRumFiP = true;}
      else if(YFJMUCjRNr == anubnQSZnE){YZFYyBcMkJ = true;}
      if(YneqDbSWOK == enYEwemyFM){nlkVXSFkrE = true;}
      else if(enYEwemyFM == YneqDbSWOK){lJrIgVlDuL = true;}
      if(EKcbQbeOsm == RkcDeVYuQY){WhGbFtMVzS = true;}
      else if(RkcDeVYuQY == EKcbQbeOsm){qYOUVrENag = true;}
      if(PlCXbRmcTR == fMFyhJuDNr){KBQGaHUJxA = true;}
      else if(fMFyhJuDNr == PlCXbRmcTR){yPEClPGGET = true;}
      if(TCYGiJMYyK == qDllgStNLB){UoRDGtDApw = true;}
      else if(qDllgStNLB == TCYGiJMYyK){PiKFmkMhru = true;}
      if(smPDtQKSKL == dXSEdmcGhz){xQFUrCMOTX = true;}
      else if(dXSEdmcGhz == smPDtQKSKL){QfFmcALkDG = true;}
      if(kDgAomkGOl == doBnMRiaWl){hRGQFlUdtQ = true;}
      if(opCxpBkWsG == iijNUNzpVL){xunrjhQCVK = true;}
      if(PFQhtbVzdL == aLiPuHtATt){pMfCUsuwOY = true;}
      while(doBnMRiaWl == kDgAomkGOl){wPlELVFpWR = true;}
      while(iijNUNzpVL == iijNUNzpVL){PeybuHOJhk = true;}
      while(aLiPuHtATt == aLiPuHtATt){eWVePSKQYk = true;}
      if(goVOOCCyYO == true){goVOOCCyYO = false;}
      if(jTqYRumFiP == true){jTqYRumFiP = false;}
      if(nlkVXSFkrE == true){nlkVXSFkrE = false;}
      if(WhGbFtMVzS == true){WhGbFtMVzS = false;}
      if(KBQGaHUJxA == true){KBQGaHUJxA = false;}
      if(UoRDGtDApw == true){UoRDGtDApw = false;}
      if(xQFUrCMOTX == true){xQFUrCMOTX = false;}
      if(hRGQFlUdtQ == true){hRGQFlUdtQ = false;}
      if(xunrjhQCVK == true){xunrjhQCVK = false;}
      if(pMfCUsuwOY == true){pMfCUsuwOY = false;}
      if(tFpZRCiAyT == true){tFpZRCiAyT = false;}
      if(YZFYyBcMkJ == true){YZFYyBcMkJ = false;}
      if(lJrIgVlDuL == true){lJrIgVlDuL = false;}
      if(qYOUVrENag == true){qYOUVrENag = false;}
      if(yPEClPGGET == true){yPEClPGGET = false;}
      if(PiKFmkMhru == true){PiKFmkMhru = false;}
      if(QfFmcALkDG == true){QfFmcALkDG = false;}
      if(wPlELVFpWR == true){wPlELVFpWR = false;}
      if(PeybuHOJhk == true){PeybuHOJhk = false;}
      if(eWVePSKQYk == true){eWVePSKQYk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JLIFAIJMIZ
{ 
  void lyWCwSZHCI()
  { 
      bool wQPjYbwACb = false;
      bool ilcIWFaagV = false;
      bool iUXmDnTjAC = false;
      bool VAyxCReWWl = false;
      bool zfPKFPNgbK = false;
      bool AkaIdascfj = false;
      bool HMzAGimfFE = false;
      bool ZEDuWCFMgn = false;
      bool amIpBkZpSa = false;
      bool YCpldmgPEW = false;
      bool chaWjwgelb = false;
      bool VgurJUDJyV = false;
      bool IxMefWNRQi = false;
      bool VoIKKrLkFF = false;
      bool DtDpFrHycJ = false;
      bool iWRiNfUwpM = false;
      bool hOOCGfXkgQ = false;
      bool IRDsROsWZn = false;
      bool PPoGAyXZxe = false;
      bool XPurWnfAiY = false;
      string TeFyyNbpCK;
      string VrBRnGhDlV;
      string bQVZCSCjfX;
      string fwghqgNusX;
      string heZABQJAxJ;
      string WpmiqCIeuf;
      string KrKeeZKSaH;
      string slKOnwqUXl;
      string IClVApIyqn;
      string XhAMMpUtVa;
      string FqYpQkeYtt;
      string LmHIWIFneo;
      string RMaliKkxBy;
      string bwzwgRcwFO;
      string KjDxbjaqpE;
      string jfPgJrPlGG;
      string zhXuRPnKbF;
      string eIiPdhIdJy;
      string itHwNwfSmo;
      string BpozPbLIeM;
      if(TeFyyNbpCK == FqYpQkeYtt){wQPjYbwACb = true;}
      else if(FqYpQkeYtt == TeFyyNbpCK){chaWjwgelb = true;}
      if(VrBRnGhDlV == LmHIWIFneo){ilcIWFaagV = true;}
      else if(LmHIWIFneo == VrBRnGhDlV){VgurJUDJyV = true;}
      if(bQVZCSCjfX == RMaliKkxBy){iUXmDnTjAC = true;}
      else if(RMaliKkxBy == bQVZCSCjfX){IxMefWNRQi = true;}
      if(fwghqgNusX == bwzwgRcwFO){VAyxCReWWl = true;}
      else if(bwzwgRcwFO == fwghqgNusX){VoIKKrLkFF = true;}
      if(heZABQJAxJ == KjDxbjaqpE){zfPKFPNgbK = true;}
      else if(KjDxbjaqpE == heZABQJAxJ){DtDpFrHycJ = true;}
      if(WpmiqCIeuf == jfPgJrPlGG){AkaIdascfj = true;}
      else if(jfPgJrPlGG == WpmiqCIeuf){iWRiNfUwpM = true;}
      if(KrKeeZKSaH == zhXuRPnKbF){HMzAGimfFE = true;}
      else if(zhXuRPnKbF == KrKeeZKSaH){hOOCGfXkgQ = true;}
      if(slKOnwqUXl == eIiPdhIdJy){ZEDuWCFMgn = true;}
      if(IClVApIyqn == itHwNwfSmo){amIpBkZpSa = true;}
      if(XhAMMpUtVa == BpozPbLIeM){YCpldmgPEW = true;}
      while(eIiPdhIdJy == slKOnwqUXl){IRDsROsWZn = true;}
      while(itHwNwfSmo == itHwNwfSmo){PPoGAyXZxe = true;}
      while(BpozPbLIeM == BpozPbLIeM){XPurWnfAiY = true;}
      if(wQPjYbwACb == true){wQPjYbwACb = false;}
      if(ilcIWFaagV == true){ilcIWFaagV = false;}
      if(iUXmDnTjAC == true){iUXmDnTjAC = false;}
      if(VAyxCReWWl == true){VAyxCReWWl = false;}
      if(zfPKFPNgbK == true){zfPKFPNgbK = false;}
      if(AkaIdascfj == true){AkaIdascfj = false;}
      if(HMzAGimfFE == true){HMzAGimfFE = false;}
      if(ZEDuWCFMgn == true){ZEDuWCFMgn = false;}
      if(amIpBkZpSa == true){amIpBkZpSa = false;}
      if(YCpldmgPEW == true){YCpldmgPEW = false;}
      if(chaWjwgelb == true){chaWjwgelb = false;}
      if(VgurJUDJyV == true){VgurJUDJyV = false;}
      if(IxMefWNRQi == true){IxMefWNRQi = false;}
      if(VoIKKrLkFF == true){VoIKKrLkFF = false;}
      if(DtDpFrHycJ == true){DtDpFrHycJ = false;}
      if(iWRiNfUwpM == true){iWRiNfUwpM = false;}
      if(hOOCGfXkgQ == true){hOOCGfXkgQ = false;}
      if(IRDsROsWZn == true){IRDsROsWZn = false;}
      if(PPoGAyXZxe == true){PPoGAyXZxe = false;}
      if(XPurWnfAiY == true){XPurWnfAiY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FKYHVOPAMH
{ 
  void OqgbTuyqjg()
  { 
      bool OexZkliBiQ = false;
      bool manEyCdLoi = false;
      bool HuTDNPlRBl = false;
      bool yqFAWrjzaJ = false;
      bool LJUsjGwPkZ = false;
      bool dljEXTLsMU = false;
      bool AQAxSwVmhG = false;
      bool SejfXxZaSG = false;
      bool TVgaHLHAcC = false;
      bool gplGJtJXZn = false;
      bool kIhdHzBEgZ = false;
      bool skZFBdjYoG = false;
      bool nUKeYbrdVc = false;
      bool nCAeUKnCTI = false;
      bool KDTCIwPgEf = false;
      bool KjhTzQyCFe = false;
      bool GWhDkqjujp = false;
      bool ogFfukBHVc = false;
      bool LLYpSETffE = false;
      bool LkxnBmUPRR = false;
      string KTmPByGYUw;
      string LRIanyVama;
      string niVmCNpmFZ;
      string dBGQlsIoIy;
      string cNSDmramkt;
      string WRKWlbyzMm;
      string HSTtSJLrot;
      string ogRnxaPRAJ;
      string mCBKDLqjeK;
      string tIbVpJtXjd;
      string giypEpzVYL;
      string LfzDzERIqG;
      string RbNeAgFuxn;
      string frgVcDEKGM;
      string MVKSyNIXVk;
      string rkfdMEVTpW;
      string jDXkeTycaw;
      string AGBdtuQtfl;
      string XgZMuuLDJX;
      string hjUicIxZne;
      if(KTmPByGYUw == giypEpzVYL){OexZkliBiQ = true;}
      else if(giypEpzVYL == KTmPByGYUw){kIhdHzBEgZ = true;}
      if(LRIanyVama == LfzDzERIqG){manEyCdLoi = true;}
      else if(LfzDzERIqG == LRIanyVama){skZFBdjYoG = true;}
      if(niVmCNpmFZ == RbNeAgFuxn){HuTDNPlRBl = true;}
      else if(RbNeAgFuxn == niVmCNpmFZ){nUKeYbrdVc = true;}
      if(dBGQlsIoIy == frgVcDEKGM){yqFAWrjzaJ = true;}
      else if(frgVcDEKGM == dBGQlsIoIy){nCAeUKnCTI = true;}
      if(cNSDmramkt == MVKSyNIXVk){LJUsjGwPkZ = true;}
      else if(MVKSyNIXVk == cNSDmramkt){KDTCIwPgEf = true;}
      if(WRKWlbyzMm == rkfdMEVTpW){dljEXTLsMU = true;}
      else if(rkfdMEVTpW == WRKWlbyzMm){KjhTzQyCFe = true;}
      if(HSTtSJLrot == jDXkeTycaw){AQAxSwVmhG = true;}
      else if(jDXkeTycaw == HSTtSJLrot){GWhDkqjujp = true;}
      if(ogRnxaPRAJ == AGBdtuQtfl){SejfXxZaSG = true;}
      if(mCBKDLqjeK == XgZMuuLDJX){TVgaHLHAcC = true;}
      if(tIbVpJtXjd == hjUicIxZne){gplGJtJXZn = true;}
      while(AGBdtuQtfl == ogRnxaPRAJ){ogFfukBHVc = true;}
      while(XgZMuuLDJX == XgZMuuLDJX){LLYpSETffE = true;}
      while(hjUicIxZne == hjUicIxZne){LkxnBmUPRR = true;}
      if(OexZkliBiQ == true){OexZkliBiQ = false;}
      if(manEyCdLoi == true){manEyCdLoi = false;}
      if(HuTDNPlRBl == true){HuTDNPlRBl = false;}
      if(yqFAWrjzaJ == true){yqFAWrjzaJ = false;}
      if(LJUsjGwPkZ == true){LJUsjGwPkZ = false;}
      if(dljEXTLsMU == true){dljEXTLsMU = false;}
      if(AQAxSwVmhG == true){AQAxSwVmhG = false;}
      if(SejfXxZaSG == true){SejfXxZaSG = false;}
      if(TVgaHLHAcC == true){TVgaHLHAcC = false;}
      if(gplGJtJXZn == true){gplGJtJXZn = false;}
      if(kIhdHzBEgZ == true){kIhdHzBEgZ = false;}
      if(skZFBdjYoG == true){skZFBdjYoG = false;}
      if(nUKeYbrdVc == true){nUKeYbrdVc = false;}
      if(nCAeUKnCTI == true){nCAeUKnCTI = false;}
      if(KDTCIwPgEf == true){KDTCIwPgEf = false;}
      if(KjhTzQyCFe == true){KjhTzQyCFe = false;}
      if(GWhDkqjujp == true){GWhDkqjujp = false;}
      if(ogFfukBHVc == true){ogFfukBHVc = false;}
      if(LLYpSETffE == true){LLYpSETffE = false;}
      if(LkxnBmUPRR == true){LkxnBmUPRR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFUNBZONUH
{ 
  void YCAsdCzISU()
  { 
      bool hNnIfhFXyc = false;
      bool xCpShHUGeE = false;
      bool uYzlrKxRuV = false;
      bool kEYJGfLIku = false;
      bool RlqoZUcXAb = false;
      bool BAtSeJNBPU = false;
      bool knccrscfMC = false;
      bool uMUjmJgKMX = false;
      bool hZQSTkJGdx = false;
      bool RJrQJdIOwg = false;
      bool qxKyfoeJfV = false;
      bool bCormKXJIG = false;
      bool iWBPjkTEZI = false;
      bool ARNffkORld = false;
      bool FAaIUOUAcz = false;
      bool FzFpxUuuNu = false;
      bool VaiWVJoJLC = false;
      bool uFWeBiwstU = false;
      bool QSaaDBMXhL = false;
      bool oTDqIeQElL = false;
      string jWNeVKysTx;
      string pUPauhDQDB;
      string kcBaiRzSVC;
      string MoNLHOXBPs;
      string popctuzLZK;
      string GbJUDGUlwE;
      string LfWQkBGESf;
      string JCAJKwmYgn;
      string RmrLujesHA;
      string skFLhKRYqr;
      string oustAEazJH;
      string TwFHlXmLVA;
      string WNwRlYxobA;
      string dNgnyVtyKq;
      string IeiAgxexYJ;
      string WGDqVbyaHb;
      string HlXIcFORJP;
      string dnAerrdwkn;
      string szQRdXKpSW;
      string XSqiiWGZWa;
      if(jWNeVKysTx == oustAEazJH){hNnIfhFXyc = true;}
      else if(oustAEazJH == jWNeVKysTx){qxKyfoeJfV = true;}
      if(pUPauhDQDB == TwFHlXmLVA){xCpShHUGeE = true;}
      else if(TwFHlXmLVA == pUPauhDQDB){bCormKXJIG = true;}
      if(kcBaiRzSVC == WNwRlYxobA){uYzlrKxRuV = true;}
      else if(WNwRlYxobA == kcBaiRzSVC){iWBPjkTEZI = true;}
      if(MoNLHOXBPs == dNgnyVtyKq){kEYJGfLIku = true;}
      else if(dNgnyVtyKq == MoNLHOXBPs){ARNffkORld = true;}
      if(popctuzLZK == IeiAgxexYJ){RlqoZUcXAb = true;}
      else if(IeiAgxexYJ == popctuzLZK){FAaIUOUAcz = true;}
      if(GbJUDGUlwE == WGDqVbyaHb){BAtSeJNBPU = true;}
      else if(WGDqVbyaHb == GbJUDGUlwE){FzFpxUuuNu = true;}
      if(LfWQkBGESf == HlXIcFORJP){knccrscfMC = true;}
      else if(HlXIcFORJP == LfWQkBGESf){VaiWVJoJLC = true;}
      if(JCAJKwmYgn == dnAerrdwkn){uMUjmJgKMX = true;}
      if(RmrLujesHA == szQRdXKpSW){hZQSTkJGdx = true;}
      if(skFLhKRYqr == XSqiiWGZWa){RJrQJdIOwg = true;}
      while(dnAerrdwkn == JCAJKwmYgn){uFWeBiwstU = true;}
      while(szQRdXKpSW == szQRdXKpSW){QSaaDBMXhL = true;}
      while(XSqiiWGZWa == XSqiiWGZWa){oTDqIeQElL = true;}
      if(hNnIfhFXyc == true){hNnIfhFXyc = false;}
      if(xCpShHUGeE == true){xCpShHUGeE = false;}
      if(uYzlrKxRuV == true){uYzlrKxRuV = false;}
      if(kEYJGfLIku == true){kEYJGfLIku = false;}
      if(RlqoZUcXAb == true){RlqoZUcXAb = false;}
      if(BAtSeJNBPU == true){BAtSeJNBPU = false;}
      if(knccrscfMC == true){knccrscfMC = false;}
      if(uMUjmJgKMX == true){uMUjmJgKMX = false;}
      if(hZQSTkJGdx == true){hZQSTkJGdx = false;}
      if(RJrQJdIOwg == true){RJrQJdIOwg = false;}
      if(qxKyfoeJfV == true){qxKyfoeJfV = false;}
      if(bCormKXJIG == true){bCormKXJIG = false;}
      if(iWBPjkTEZI == true){iWBPjkTEZI = false;}
      if(ARNffkORld == true){ARNffkORld = false;}
      if(FAaIUOUAcz == true){FAaIUOUAcz = false;}
      if(FzFpxUuuNu == true){FzFpxUuuNu = false;}
      if(VaiWVJoJLC == true){VaiWVJoJLC = false;}
      if(uFWeBiwstU == true){uFWeBiwstU = false;}
      if(QSaaDBMXhL == true){QSaaDBMXhL = false;}
      if(oTDqIeQElL == true){oTDqIeQElL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGSKXZOHML
{ 
  void SfgrorEsoT()
  { 
      bool EWmtRKXoFN = false;
      bool WogmcSeKmr = false;
      bool yUxrlwRYDH = false;
      bool AOjxJBnZcX = false;
      bool rgLRTJRTlV = false;
      bool hWuUljYuHV = false;
      bool sylxNHFicb = false;
      bool eFgOARIfYc = false;
      bool exmgZdTPLZ = false;
      bool bsSGdsuNEM = false;
      bool DhpJqcofUU = false;
      bool bsVdquLEXj = false;
      bool npWDAllZjG = false;
      bool VtaMZwGcpw = false;
      bool nmtqxiWnPh = false;
      bool hppUXNLmJE = false;
      bool pOuNygRJEt = false;
      bool nhOauBueFR = false;
      bool PyKBYeEGnL = false;
      bool jTTkGZqgrQ = false;
      string VcTQoWAjiG;
      string FIEyWbyYVC;
      string EdAYrXwApe;
      string NlPgZxAlVt;
      string RLOAhNddhA;
      string ECmXbqcuXR;
      string aAtDrSrXYZ;
      string bMDajsPzpe;
      string sSRoaLyqEh;
      string TEODTRRKHP;
      string UGFIYqyMni;
      string bcErXHhFbg;
      string TBSpFXxzGR;
      string bFqaJlNJQi;
      string MlDUGpzVfM;
      string iLhZuTmPCA;
      string tzFVHVlcik;
      string tYnrUgxxiO;
      string XaTtiPWQfp;
      string zyGPoNghNk;
      if(VcTQoWAjiG == UGFIYqyMni){EWmtRKXoFN = true;}
      else if(UGFIYqyMni == VcTQoWAjiG){DhpJqcofUU = true;}
      if(FIEyWbyYVC == bcErXHhFbg){WogmcSeKmr = true;}
      else if(bcErXHhFbg == FIEyWbyYVC){bsVdquLEXj = true;}
      if(EdAYrXwApe == TBSpFXxzGR){yUxrlwRYDH = true;}
      else if(TBSpFXxzGR == EdAYrXwApe){npWDAllZjG = true;}
      if(NlPgZxAlVt == bFqaJlNJQi){AOjxJBnZcX = true;}
      else if(bFqaJlNJQi == NlPgZxAlVt){VtaMZwGcpw = true;}
      if(RLOAhNddhA == MlDUGpzVfM){rgLRTJRTlV = true;}
      else if(MlDUGpzVfM == RLOAhNddhA){nmtqxiWnPh = true;}
      if(ECmXbqcuXR == iLhZuTmPCA){hWuUljYuHV = true;}
      else if(iLhZuTmPCA == ECmXbqcuXR){hppUXNLmJE = true;}
      if(aAtDrSrXYZ == tzFVHVlcik){sylxNHFicb = true;}
      else if(tzFVHVlcik == aAtDrSrXYZ){pOuNygRJEt = true;}
      if(bMDajsPzpe == tYnrUgxxiO){eFgOARIfYc = true;}
      if(sSRoaLyqEh == XaTtiPWQfp){exmgZdTPLZ = true;}
      if(TEODTRRKHP == zyGPoNghNk){bsSGdsuNEM = true;}
      while(tYnrUgxxiO == bMDajsPzpe){nhOauBueFR = true;}
      while(XaTtiPWQfp == XaTtiPWQfp){PyKBYeEGnL = true;}
      while(zyGPoNghNk == zyGPoNghNk){jTTkGZqgrQ = true;}
      if(EWmtRKXoFN == true){EWmtRKXoFN = false;}
      if(WogmcSeKmr == true){WogmcSeKmr = false;}
      if(yUxrlwRYDH == true){yUxrlwRYDH = false;}
      if(AOjxJBnZcX == true){AOjxJBnZcX = false;}
      if(rgLRTJRTlV == true){rgLRTJRTlV = false;}
      if(hWuUljYuHV == true){hWuUljYuHV = false;}
      if(sylxNHFicb == true){sylxNHFicb = false;}
      if(eFgOARIfYc == true){eFgOARIfYc = false;}
      if(exmgZdTPLZ == true){exmgZdTPLZ = false;}
      if(bsSGdsuNEM == true){bsSGdsuNEM = false;}
      if(DhpJqcofUU == true){DhpJqcofUU = false;}
      if(bsVdquLEXj == true){bsVdquLEXj = false;}
      if(npWDAllZjG == true){npWDAllZjG = false;}
      if(VtaMZwGcpw == true){VtaMZwGcpw = false;}
      if(nmtqxiWnPh == true){nmtqxiWnPh = false;}
      if(hppUXNLmJE == true){hppUXNLmJE = false;}
      if(pOuNygRJEt == true){pOuNygRJEt = false;}
      if(nhOauBueFR == true){nhOauBueFR = false;}
      if(PyKBYeEGnL == true){PyKBYeEGnL = false;}
      if(jTTkGZqgrQ == true){jTTkGZqgrQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SOGIPIWPZF
{ 
  void bEQqdxKAfP()
  { 
      bool rEJywJyLZw = false;
      bool TkUdeWHBcB = false;
      bool MdHZKghaiQ = false;
      bool aIWgCcfCGH = false;
      bool lSDkVrHShu = false;
      bool mMfPUOxjmO = false;
      bool aWcIVLNnbC = false;
      bool qEuVPtZVDS = false;
      bool YOrmdObHMn = false;
      bool fuOqfOotPK = false;
      bool dTqfEhQJzZ = false;
      bool nafUoLeoeG = false;
      bool iFamWuoDoB = false;
      bool FfGsnEWLiu = false;
      bool xRIlzEPtBU = false;
      bool izOIbYsEII = false;
      bool sNUyUITmgj = false;
      bool nSGjJQxnmR = false;
      bool euCURFQxRO = false;
      bool LSDZCjxKRq = false;
      string cPInqDjVDO;
      string RatQgJbuYp;
      string ILbmNjxkoR;
      string DgCrXLashk;
      string qicLbeROqX;
      string KGBzgRnVaH;
      string GyfkKjXCsU;
      string hhMnzYiPKh;
      string RitQGweDKG;
      string XFSaesCqAq;
      string GPVWobtNAI;
      string hXKroXDPeO;
      string FUqlwcPlJF;
      string WqPTbBMXad;
      string CQDCXAuZkH;
      string omMlkkYiZM;
      string MHDtkqHpPm;
      string KfnALnRnOu;
      string goACQjddhp;
      string ccxNRtNJQg;
      if(cPInqDjVDO == GPVWobtNAI){rEJywJyLZw = true;}
      else if(GPVWobtNAI == cPInqDjVDO){dTqfEhQJzZ = true;}
      if(RatQgJbuYp == hXKroXDPeO){TkUdeWHBcB = true;}
      else if(hXKroXDPeO == RatQgJbuYp){nafUoLeoeG = true;}
      if(ILbmNjxkoR == FUqlwcPlJF){MdHZKghaiQ = true;}
      else if(FUqlwcPlJF == ILbmNjxkoR){iFamWuoDoB = true;}
      if(DgCrXLashk == WqPTbBMXad){aIWgCcfCGH = true;}
      else if(WqPTbBMXad == DgCrXLashk){FfGsnEWLiu = true;}
      if(qicLbeROqX == CQDCXAuZkH){lSDkVrHShu = true;}
      else if(CQDCXAuZkH == qicLbeROqX){xRIlzEPtBU = true;}
      if(KGBzgRnVaH == omMlkkYiZM){mMfPUOxjmO = true;}
      else if(omMlkkYiZM == KGBzgRnVaH){izOIbYsEII = true;}
      if(GyfkKjXCsU == MHDtkqHpPm){aWcIVLNnbC = true;}
      else if(MHDtkqHpPm == GyfkKjXCsU){sNUyUITmgj = true;}
      if(hhMnzYiPKh == KfnALnRnOu){qEuVPtZVDS = true;}
      if(RitQGweDKG == goACQjddhp){YOrmdObHMn = true;}
      if(XFSaesCqAq == ccxNRtNJQg){fuOqfOotPK = true;}
      while(KfnALnRnOu == hhMnzYiPKh){nSGjJQxnmR = true;}
      while(goACQjddhp == goACQjddhp){euCURFQxRO = true;}
      while(ccxNRtNJQg == ccxNRtNJQg){LSDZCjxKRq = true;}
      if(rEJywJyLZw == true){rEJywJyLZw = false;}
      if(TkUdeWHBcB == true){TkUdeWHBcB = false;}
      if(MdHZKghaiQ == true){MdHZKghaiQ = false;}
      if(aIWgCcfCGH == true){aIWgCcfCGH = false;}
      if(lSDkVrHShu == true){lSDkVrHShu = false;}
      if(mMfPUOxjmO == true){mMfPUOxjmO = false;}
      if(aWcIVLNnbC == true){aWcIVLNnbC = false;}
      if(qEuVPtZVDS == true){qEuVPtZVDS = false;}
      if(YOrmdObHMn == true){YOrmdObHMn = false;}
      if(fuOqfOotPK == true){fuOqfOotPK = false;}
      if(dTqfEhQJzZ == true){dTqfEhQJzZ = false;}
      if(nafUoLeoeG == true){nafUoLeoeG = false;}
      if(iFamWuoDoB == true){iFamWuoDoB = false;}
      if(FfGsnEWLiu == true){FfGsnEWLiu = false;}
      if(xRIlzEPtBU == true){xRIlzEPtBU = false;}
      if(izOIbYsEII == true){izOIbYsEII = false;}
      if(sNUyUITmgj == true){sNUyUITmgj = false;}
      if(nSGjJQxnmR == true){nSGjJQxnmR = false;}
      if(euCURFQxRO == true){euCURFQxRO = false;}
      if(LSDZCjxKRq == true){LSDZCjxKRq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGEAAMBAPQ
{ 
  void HxTNApVNcG()
  { 
      bool RQRgPIQAWg = false;
      bool fKuXeUbgbG = false;
      bool XMETdPCmmk = false;
      bool fkiDMWtHgl = false;
      bool hHohkBRJyB = false;
      bool OXDWrEMxCz = false;
      bool GdMlAubqKI = false;
      bool aUzoXPWVic = false;
      bool xsnkVHgMKH = false;
      bool JwEhfEuChp = false;
      bool ZaypasYNzc = false;
      bool hpOZBMoaPs = false;
      bool NPfCydQRJS = false;
      bool UTnsDWtyKc = false;
      bool iSMhZThdfS = false;
      bool PTmnbKtwrx = false;
      bool bGEfHNBVVd = false;
      bool SqQmKtCxbd = false;
      bool wlkpDAgAQs = false;
      bool byGMAbOgaM = false;
      string PcswaJyqYy;
      string drAtBRttxf;
      string SayZUsxZqL;
      string cIPhiFFdgJ;
      string iskEHqnpSD;
      string MqGFLndSbg;
      string MYzMVVcSKu;
      string LQMmwZptSc;
      string FHGmzlCKVt;
      string alBAxKsXik;
      string OUeWqudSIl;
      string yjAzbFSLNj;
      string TRwPUYOMol;
      string fRLgNjbiuD;
      string HiBiwpkCXr;
      string qgKzRwXOCS;
      string gQdVFfYTkq;
      string ciQJbkQMTe;
      string nLnwtzHMOQ;
      string MMgcWqFedQ;
      if(PcswaJyqYy == OUeWqudSIl){RQRgPIQAWg = true;}
      else if(OUeWqudSIl == PcswaJyqYy){ZaypasYNzc = true;}
      if(drAtBRttxf == yjAzbFSLNj){fKuXeUbgbG = true;}
      else if(yjAzbFSLNj == drAtBRttxf){hpOZBMoaPs = true;}
      if(SayZUsxZqL == TRwPUYOMol){XMETdPCmmk = true;}
      else if(TRwPUYOMol == SayZUsxZqL){NPfCydQRJS = true;}
      if(cIPhiFFdgJ == fRLgNjbiuD){fkiDMWtHgl = true;}
      else if(fRLgNjbiuD == cIPhiFFdgJ){UTnsDWtyKc = true;}
      if(iskEHqnpSD == HiBiwpkCXr){hHohkBRJyB = true;}
      else if(HiBiwpkCXr == iskEHqnpSD){iSMhZThdfS = true;}
      if(MqGFLndSbg == qgKzRwXOCS){OXDWrEMxCz = true;}
      else if(qgKzRwXOCS == MqGFLndSbg){PTmnbKtwrx = true;}
      if(MYzMVVcSKu == gQdVFfYTkq){GdMlAubqKI = true;}
      else if(gQdVFfYTkq == MYzMVVcSKu){bGEfHNBVVd = true;}
      if(LQMmwZptSc == ciQJbkQMTe){aUzoXPWVic = true;}
      if(FHGmzlCKVt == nLnwtzHMOQ){xsnkVHgMKH = true;}
      if(alBAxKsXik == MMgcWqFedQ){JwEhfEuChp = true;}
      while(ciQJbkQMTe == LQMmwZptSc){SqQmKtCxbd = true;}
      while(nLnwtzHMOQ == nLnwtzHMOQ){wlkpDAgAQs = true;}
      while(MMgcWqFedQ == MMgcWqFedQ){byGMAbOgaM = true;}
      if(RQRgPIQAWg == true){RQRgPIQAWg = false;}
      if(fKuXeUbgbG == true){fKuXeUbgbG = false;}
      if(XMETdPCmmk == true){XMETdPCmmk = false;}
      if(fkiDMWtHgl == true){fkiDMWtHgl = false;}
      if(hHohkBRJyB == true){hHohkBRJyB = false;}
      if(OXDWrEMxCz == true){OXDWrEMxCz = false;}
      if(GdMlAubqKI == true){GdMlAubqKI = false;}
      if(aUzoXPWVic == true){aUzoXPWVic = false;}
      if(xsnkVHgMKH == true){xsnkVHgMKH = false;}
      if(JwEhfEuChp == true){JwEhfEuChp = false;}
      if(ZaypasYNzc == true){ZaypasYNzc = false;}
      if(hpOZBMoaPs == true){hpOZBMoaPs = false;}
      if(NPfCydQRJS == true){NPfCydQRJS = false;}
      if(UTnsDWtyKc == true){UTnsDWtyKc = false;}
      if(iSMhZThdfS == true){iSMhZThdfS = false;}
      if(PTmnbKtwrx == true){PTmnbKtwrx = false;}
      if(bGEfHNBVVd == true){bGEfHNBVVd = false;}
      if(SqQmKtCxbd == true){SqQmKtCxbd = false;}
      if(wlkpDAgAQs == true){wlkpDAgAQs = false;}
      if(byGMAbOgaM == true){byGMAbOgaM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFEKUHSYYD
{ 
  void yydRwGdphQ()
  { 
      bool BipInjUDUi = false;
      bool kQbEQFpOgR = false;
      bool wQBhpHNshH = false;
      bool BrqFVYtQuw = false;
      bool BSgVNMfQUH = false;
      bool XzxHDjgHSf = false;
      bool VbVNhsZVhr = false;
      bool LYTkQcjfUc = false;
      bool bwXZiCuiBl = false;
      bool qlyOZZxTmU = false;
      bool mKicwzeLqZ = false;
      bool ABmpEZDudf = false;
      bool ypTuAYZFKp = false;
      bool fPszoQNudj = false;
      bool WiqblpyIJA = false;
      bool WCpGWxpmbW = false;
      bool YZBBtjHnAn = false;
      bool LHRsJOyrJK = false;
      bool aRuKTcYlcr = false;
      bool ZZTGLwhpgB = false;
      string kTSAGsIPfe;
      string MkDFAjMhMu;
      string UYYebxpKwb;
      string gkPxVbmnTN;
      string xIDoBtVrsQ;
      string XhlKWLunYJ;
      string DxTDyaUGjY;
      string wYNyyLVidg;
      string bxReDyzFZJ;
      string fzPKKzozpZ;
      string YOHTUzTmML;
      string pLKqgFfoAA;
      string bPfZrwJDny;
      string WWrDIMpxJD;
      string dMrOTUoYcE;
      string SzzpyIihbX;
      string pQyNnTSGhT;
      string PiewVOWRGX;
      string HjZjfWWCEz;
      string dHUlNNNeZA;
      if(kTSAGsIPfe == YOHTUzTmML){BipInjUDUi = true;}
      else if(YOHTUzTmML == kTSAGsIPfe){mKicwzeLqZ = true;}
      if(MkDFAjMhMu == pLKqgFfoAA){kQbEQFpOgR = true;}
      else if(pLKqgFfoAA == MkDFAjMhMu){ABmpEZDudf = true;}
      if(UYYebxpKwb == bPfZrwJDny){wQBhpHNshH = true;}
      else if(bPfZrwJDny == UYYebxpKwb){ypTuAYZFKp = true;}
      if(gkPxVbmnTN == WWrDIMpxJD){BrqFVYtQuw = true;}
      else if(WWrDIMpxJD == gkPxVbmnTN){fPszoQNudj = true;}
      if(xIDoBtVrsQ == dMrOTUoYcE){BSgVNMfQUH = true;}
      else if(dMrOTUoYcE == xIDoBtVrsQ){WiqblpyIJA = true;}
      if(XhlKWLunYJ == SzzpyIihbX){XzxHDjgHSf = true;}
      else if(SzzpyIihbX == XhlKWLunYJ){WCpGWxpmbW = true;}
      if(DxTDyaUGjY == pQyNnTSGhT){VbVNhsZVhr = true;}
      else if(pQyNnTSGhT == DxTDyaUGjY){YZBBtjHnAn = true;}
      if(wYNyyLVidg == PiewVOWRGX){LYTkQcjfUc = true;}
      if(bxReDyzFZJ == HjZjfWWCEz){bwXZiCuiBl = true;}
      if(fzPKKzozpZ == dHUlNNNeZA){qlyOZZxTmU = true;}
      while(PiewVOWRGX == wYNyyLVidg){LHRsJOyrJK = true;}
      while(HjZjfWWCEz == HjZjfWWCEz){aRuKTcYlcr = true;}
      while(dHUlNNNeZA == dHUlNNNeZA){ZZTGLwhpgB = true;}
      if(BipInjUDUi == true){BipInjUDUi = false;}
      if(kQbEQFpOgR == true){kQbEQFpOgR = false;}
      if(wQBhpHNshH == true){wQBhpHNshH = false;}
      if(BrqFVYtQuw == true){BrqFVYtQuw = false;}
      if(BSgVNMfQUH == true){BSgVNMfQUH = false;}
      if(XzxHDjgHSf == true){XzxHDjgHSf = false;}
      if(VbVNhsZVhr == true){VbVNhsZVhr = false;}
      if(LYTkQcjfUc == true){LYTkQcjfUc = false;}
      if(bwXZiCuiBl == true){bwXZiCuiBl = false;}
      if(qlyOZZxTmU == true){qlyOZZxTmU = false;}
      if(mKicwzeLqZ == true){mKicwzeLqZ = false;}
      if(ABmpEZDudf == true){ABmpEZDudf = false;}
      if(ypTuAYZFKp == true){ypTuAYZFKp = false;}
      if(fPszoQNudj == true){fPszoQNudj = false;}
      if(WiqblpyIJA == true){WiqblpyIJA = false;}
      if(WCpGWxpmbW == true){WCpGWxpmbW = false;}
      if(YZBBtjHnAn == true){YZBBtjHnAn = false;}
      if(LHRsJOyrJK == true){LHRsJOyrJK = false;}
      if(aRuKTcYlcr == true){aRuKTcYlcr = false;}
      if(ZZTGLwhpgB == true){ZZTGLwhpgB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWFBKHWBKE
{ 
  void VmcKWzAIWA()
  { 
      bool WHxaipZfGd = false;
      bool nTnwDfrfFu = false;
      bool eSFbSuTNAO = false;
      bool MtGpYdSRhX = false;
      bool NDVDxlmqGH = false;
      bool crtUBECUIm = false;
      bool VMfrQsMxWY = false;
      bool MayhhbwBef = false;
      bool HbGrlUAknU = false;
      bool axJtCBWdmE = false;
      bool ZpTgtBsLmZ = false;
      bool HBpbetFnFw = false;
      bool raICyPREff = false;
      bool ESOaGRHYxj = false;
      bool boyOMZHgPH = false;
      bool uiXpLygRie = false;
      bool jofHVolOVM = false;
      bool lgpVUDctoX = false;
      bool HjnXjUtXOH = false;
      bool jooRzmIprW = false;
      string jPpbJLStcD;
      string qptRkxJWfK;
      string QTDlcYhpDy;
      string dubygqkpHs;
      string NKWFRMLPBi;
      string ptGbbPLEyj;
      string cbqeZwOujt;
      string MSPmwFwyTQ;
      string NSnUHjozWQ;
      string ffrWQkTrfV;
      string xPeHVWdTeV;
      string TNkgWKnWXo;
      string GOYTOgasWL;
      string lESxTxmgyj;
      string FVTAwRuKAF;
      string xxTpPhqLsn;
      string wkxTjPumNY;
      string WHXniktXXw;
      string kPrQNnjbhk;
      string GbnJnUYzQg;
      if(jPpbJLStcD == xPeHVWdTeV){WHxaipZfGd = true;}
      else if(xPeHVWdTeV == jPpbJLStcD){ZpTgtBsLmZ = true;}
      if(qptRkxJWfK == TNkgWKnWXo){nTnwDfrfFu = true;}
      else if(TNkgWKnWXo == qptRkxJWfK){HBpbetFnFw = true;}
      if(QTDlcYhpDy == GOYTOgasWL){eSFbSuTNAO = true;}
      else if(GOYTOgasWL == QTDlcYhpDy){raICyPREff = true;}
      if(dubygqkpHs == lESxTxmgyj){MtGpYdSRhX = true;}
      else if(lESxTxmgyj == dubygqkpHs){ESOaGRHYxj = true;}
      if(NKWFRMLPBi == FVTAwRuKAF){NDVDxlmqGH = true;}
      else if(FVTAwRuKAF == NKWFRMLPBi){boyOMZHgPH = true;}
      if(ptGbbPLEyj == xxTpPhqLsn){crtUBECUIm = true;}
      else if(xxTpPhqLsn == ptGbbPLEyj){uiXpLygRie = true;}
      if(cbqeZwOujt == wkxTjPumNY){VMfrQsMxWY = true;}
      else if(wkxTjPumNY == cbqeZwOujt){jofHVolOVM = true;}
      if(MSPmwFwyTQ == WHXniktXXw){MayhhbwBef = true;}
      if(NSnUHjozWQ == kPrQNnjbhk){HbGrlUAknU = true;}
      if(ffrWQkTrfV == GbnJnUYzQg){axJtCBWdmE = true;}
      while(WHXniktXXw == MSPmwFwyTQ){lgpVUDctoX = true;}
      while(kPrQNnjbhk == kPrQNnjbhk){HjnXjUtXOH = true;}
      while(GbnJnUYzQg == GbnJnUYzQg){jooRzmIprW = true;}
      if(WHxaipZfGd == true){WHxaipZfGd = false;}
      if(nTnwDfrfFu == true){nTnwDfrfFu = false;}
      if(eSFbSuTNAO == true){eSFbSuTNAO = false;}
      if(MtGpYdSRhX == true){MtGpYdSRhX = false;}
      if(NDVDxlmqGH == true){NDVDxlmqGH = false;}
      if(crtUBECUIm == true){crtUBECUIm = false;}
      if(VMfrQsMxWY == true){VMfrQsMxWY = false;}
      if(MayhhbwBef == true){MayhhbwBef = false;}
      if(HbGrlUAknU == true){HbGrlUAknU = false;}
      if(axJtCBWdmE == true){axJtCBWdmE = false;}
      if(ZpTgtBsLmZ == true){ZpTgtBsLmZ = false;}
      if(HBpbetFnFw == true){HBpbetFnFw = false;}
      if(raICyPREff == true){raICyPREff = false;}
      if(ESOaGRHYxj == true){ESOaGRHYxj = false;}
      if(boyOMZHgPH == true){boyOMZHgPH = false;}
      if(uiXpLygRie == true){uiXpLygRie = false;}
      if(jofHVolOVM == true){jofHVolOVM = false;}
      if(lgpVUDctoX == true){lgpVUDctoX = false;}
      if(HjnXjUtXOH == true){HjnXjUtXOH = false;}
      if(jooRzmIprW == true){jooRzmIprW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVOQRTIUBR
{ 
  void YydWlgZcka()
  { 
      bool ehceuGDfsh = false;
      bool nKswGrRuYi = false;
      bool QrYYlHhNfl = false;
      bool SNbqCtqrzZ = false;
      bool HpCauTUPNF = false;
      bool ggfAElIEsm = false;
      bool YozHPahCtM = false;
      bool AYwzaapxcR = false;
      bool mRAaFkgamP = false;
      bool kmzLARpuLU = false;
      bool kRUAEHjfZd = false;
      bool wKbazGoYBd = false;
      bool sGOebNYkyI = false;
      bool jtlHfUwzWx = false;
      bool ABBJSZKXLs = false;
      bool cRsgbeDpYp = false;
      bool hzhRsBXTtd = false;
      bool KpBEcrFFLB = false;
      bool DAYEfSBFfB = false;
      bool RGagOBSjPR = false;
      string qhJWLqqGHu;
      string ZlBMFVGOIN;
      string QusHtjIjno;
      string dpInUWoOlo;
      string srQSaQYQNH;
      string KiUIQwoCcb;
      string hHSSRidMri;
      string fqbSUXdafc;
      string LrVfdtUzWY;
      string hmkKHlZyBr;
      string lLYebSGCns;
      string RNWzPokmnW;
      string OeoSBsGRLh;
      string yfZmqATpDK;
      string mSLdGTQktR;
      string BmJddHVFdi;
      string MopGtlniIP;
      string VtidjuSLLg;
      string bUXtgLVuJj;
      string dNMUxycFiU;
      if(qhJWLqqGHu == lLYebSGCns){ehceuGDfsh = true;}
      else if(lLYebSGCns == qhJWLqqGHu){kRUAEHjfZd = true;}
      if(ZlBMFVGOIN == RNWzPokmnW){nKswGrRuYi = true;}
      else if(RNWzPokmnW == ZlBMFVGOIN){wKbazGoYBd = true;}
      if(QusHtjIjno == OeoSBsGRLh){QrYYlHhNfl = true;}
      else if(OeoSBsGRLh == QusHtjIjno){sGOebNYkyI = true;}
      if(dpInUWoOlo == yfZmqATpDK){SNbqCtqrzZ = true;}
      else if(yfZmqATpDK == dpInUWoOlo){jtlHfUwzWx = true;}
      if(srQSaQYQNH == mSLdGTQktR){HpCauTUPNF = true;}
      else if(mSLdGTQktR == srQSaQYQNH){ABBJSZKXLs = true;}
      if(KiUIQwoCcb == BmJddHVFdi){ggfAElIEsm = true;}
      else if(BmJddHVFdi == KiUIQwoCcb){cRsgbeDpYp = true;}
      if(hHSSRidMri == MopGtlniIP){YozHPahCtM = true;}
      else if(MopGtlniIP == hHSSRidMri){hzhRsBXTtd = true;}
      if(fqbSUXdafc == VtidjuSLLg){AYwzaapxcR = true;}
      if(LrVfdtUzWY == bUXtgLVuJj){mRAaFkgamP = true;}
      if(hmkKHlZyBr == dNMUxycFiU){kmzLARpuLU = true;}
      while(VtidjuSLLg == fqbSUXdafc){KpBEcrFFLB = true;}
      while(bUXtgLVuJj == bUXtgLVuJj){DAYEfSBFfB = true;}
      while(dNMUxycFiU == dNMUxycFiU){RGagOBSjPR = true;}
      if(ehceuGDfsh == true){ehceuGDfsh = false;}
      if(nKswGrRuYi == true){nKswGrRuYi = false;}
      if(QrYYlHhNfl == true){QrYYlHhNfl = false;}
      if(SNbqCtqrzZ == true){SNbqCtqrzZ = false;}
      if(HpCauTUPNF == true){HpCauTUPNF = false;}
      if(ggfAElIEsm == true){ggfAElIEsm = false;}
      if(YozHPahCtM == true){YozHPahCtM = false;}
      if(AYwzaapxcR == true){AYwzaapxcR = false;}
      if(mRAaFkgamP == true){mRAaFkgamP = false;}
      if(kmzLARpuLU == true){kmzLARpuLU = false;}
      if(kRUAEHjfZd == true){kRUAEHjfZd = false;}
      if(wKbazGoYBd == true){wKbazGoYBd = false;}
      if(sGOebNYkyI == true){sGOebNYkyI = false;}
      if(jtlHfUwzWx == true){jtlHfUwzWx = false;}
      if(ABBJSZKXLs == true){ABBJSZKXLs = false;}
      if(cRsgbeDpYp == true){cRsgbeDpYp = false;}
      if(hzhRsBXTtd == true){hzhRsBXTtd = false;}
      if(KpBEcrFFLB == true){KpBEcrFFLB = false;}
      if(DAYEfSBFfB == true){DAYEfSBFfB = false;}
      if(RGagOBSjPR == true){RGagOBSjPR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITBJDLQUTM
{ 
  void GbVZdJFhez()
  { 
      bool htyteGCOfe = false;
      bool dBdUcfgTCJ = false;
      bool ANTiIPIMWS = false;
      bool wgARnCTPIB = false;
      bool kDalWuAoOG = false;
      bool rMACjTaOkP = false;
      bool xorMiwBMfZ = false;
      bool MQLAXxlgMN = false;
      bool PTyQaigxhT = false;
      bool bEerEwLNDZ = false;
      bool tnInsaAAdl = false;
      bool htBXAdqalz = false;
      bool PDdMyIlTub = false;
      bool lXdmTaKJWz = false;
      bool ifSulhCGrZ = false;
      bool EjbDJpJwpj = false;
      bool ngECAJPODY = false;
      bool ThDmQijhZQ = false;
      bool GeaVXBwZdc = false;
      bool QNTmKBbQub = false;
      string fpSyVHmcwh;
      string wVqCnbdGZz;
      string iKcEfIDEoQ;
      string BUVQiOGydh;
      string ZNzOCJMGoW;
      string ffLQNUNOSN;
      string DhmffaAZTZ;
      string UfbqYVKNCV;
      string wxPSkVIEDN;
      string BreQeraTia;
      string IllOCzDUqr;
      string KzMwQFSUuK;
      string RwWFXcALMg;
      string tqeaMKLAQk;
      string RnMKDCfhAY;
      string YGYXIMOgpY;
      string yrHKySTkjF;
      string tSDJrciMCV;
      string wRKmInSGRA;
      string weJqlZgCMj;
      if(fpSyVHmcwh == IllOCzDUqr){htyteGCOfe = true;}
      else if(IllOCzDUqr == fpSyVHmcwh){tnInsaAAdl = true;}
      if(wVqCnbdGZz == KzMwQFSUuK){dBdUcfgTCJ = true;}
      else if(KzMwQFSUuK == wVqCnbdGZz){htBXAdqalz = true;}
      if(iKcEfIDEoQ == RwWFXcALMg){ANTiIPIMWS = true;}
      else if(RwWFXcALMg == iKcEfIDEoQ){PDdMyIlTub = true;}
      if(BUVQiOGydh == tqeaMKLAQk){wgARnCTPIB = true;}
      else if(tqeaMKLAQk == BUVQiOGydh){lXdmTaKJWz = true;}
      if(ZNzOCJMGoW == RnMKDCfhAY){kDalWuAoOG = true;}
      else if(RnMKDCfhAY == ZNzOCJMGoW){ifSulhCGrZ = true;}
      if(ffLQNUNOSN == YGYXIMOgpY){rMACjTaOkP = true;}
      else if(YGYXIMOgpY == ffLQNUNOSN){EjbDJpJwpj = true;}
      if(DhmffaAZTZ == yrHKySTkjF){xorMiwBMfZ = true;}
      else if(yrHKySTkjF == DhmffaAZTZ){ngECAJPODY = true;}
      if(UfbqYVKNCV == tSDJrciMCV){MQLAXxlgMN = true;}
      if(wxPSkVIEDN == wRKmInSGRA){PTyQaigxhT = true;}
      if(BreQeraTia == weJqlZgCMj){bEerEwLNDZ = true;}
      while(tSDJrciMCV == UfbqYVKNCV){ThDmQijhZQ = true;}
      while(wRKmInSGRA == wRKmInSGRA){GeaVXBwZdc = true;}
      while(weJqlZgCMj == weJqlZgCMj){QNTmKBbQub = true;}
      if(htyteGCOfe == true){htyteGCOfe = false;}
      if(dBdUcfgTCJ == true){dBdUcfgTCJ = false;}
      if(ANTiIPIMWS == true){ANTiIPIMWS = false;}
      if(wgARnCTPIB == true){wgARnCTPIB = false;}
      if(kDalWuAoOG == true){kDalWuAoOG = false;}
      if(rMACjTaOkP == true){rMACjTaOkP = false;}
      if(xorMiwBMfZ == true){xorMiwBMfZ = false;}
      if(MQLAXxlgMN == true){MQLAXxlgMN = false;}
      if(PTyQaigxhT == true){PTyQaigxhT = false;}
      if(bEerEwLNDZ == true){bEerEwLNDZ = false;}
      if(tnInsaAAdl == true){tnInsaAAdl = false;}
      if(htBXAdqalz == true){htBXAdqalz = false;}
      if(PDdMyIlTub == true){PDdMyIlTub = false;}
      if(lXdmTaKJWz == true){lXdmTaKJWz = false;}
      if(ifSulhCGrZ == true){ifSulhCGrZ = false;}
      if(EjbDJpJwpj == true){EjbDJpJwpj = false;}
      if(ngECAJPODY == true){ngECAJPODY = false;}
      if(ThDmQijhZQ == true){ThDmQijhZQ = false;}
      if(GeaVXBwZdc == true){GeaVXBwZdc = false;}
      if(QNTmKBbQub == true){QNTmKBbQub = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LREZRQMSTL
{ 
  void BFqihsqjaS()
  { 
      bool MMfwQUfCVD = false;
      bool IFUgmbLptB = false;
      bool TmAsMRdkml = false;
      bool ThwLmWkYfd = false;
      bool sfnmMnlMAQ = false;
      bool yquOfZMljy = false;
      bool qtPjiZJJtQ = false;
      bool qmJPInzNgX = false;
      bool fQkVmcmgeN = false;
      bool KyohlyPDDl = false;
      bool ecSjZLgeGr = false;
      bool ayELSaJsxG = false;
      bool lbegFrxbcJ = false;
      bool XuKtsDyBua = false;
      bool wIalmLscOL = false;
      bool oWGwACxkdg = false;
      bool OEBwTenJSP = false;
      bool bHxVKdArtt = false;
      bool zUMRUBnNtp = false;
      bool FMXOMqGeRH = false;
      string RmXFNLgSci;
      string fTapwehYtz;
      string PfaOCINMMR;
      string yOrXGyAMbC;
      string NuMqrOYdqp;
      string ZBSWZlLJCE;
      string xUGLjRbCiy;
      string eUwrkTSjWn;
      string jiUVrwuUxU;
      string mpJXEsoBGa;
      string mWusLFFalG;
      string SblOTNzjSn;
      string VGENLnLYmr;
      string eQcuANnbKm;
      string qUiqCLEtDp;
      string sFiSEfSggW;
      string sgmsaCyqNG;
      string ZXYfwBXMLA;
      string jQUxzZhKpU;
      string tHtmsKgoQA;
      if(RmXFNLgSci == mWusLFFalG){MMfwQUfCVD = true;}
      else if(mWusLFFalG == RmXFNLgSci){ecSjZLgeGr = true;}
      if(fTapwehYtz == SblOTNzjSn){IFUgmbLptB = true;}
      else if(SblOTNzjSn == fTapwehYtz){ayELSaJsxG = true;}
      if(PfaOCINMMR == VGENLnLYmr){TmAsMRdkml = true;}
      else if(VGENLnLYmr == PfaOCINMMR){lbegFrxbcJ = true;}
      if(yOrXGyAMbC == eQcuANnbKm){ThwLmWkYfd = true;}
      else if(eQcuANnbKm == yOrXGyAMbC){XuKtsDyBua = true;}
      if(NuMqrOYdqp == qUiqCLEtDp){sfnmMnlMAQ = true;}
      else if(qUiqCLEtDp == NuMqrOYdqp){wIalmLscOL = true;}
      if(ZBSWZlLJCE == sFiSEfSggW){yquOfZMljy = true;}
      else if(sFiSEfSggW == ZBSWZlLJCE){oWGwACxkdg = true;}
      if(xUGLjRbCiy == sgmsaCyqNG){qtPjiZJJtQ = true;}
      else if(sgmsaCyqNG == xUGLjRbCiy){OEBwTenJSP = true;}
      if(eUwrkTSjWn == ZXYfwBXMLA){qmJPInzNgX = true;}
      if(jiUVrwuUxU == jQUxzZhKpU){fQkVmcmgeN = true;}
      if(mpJXEsoBGa == tHtmsKgoQA){KyohlyPDDl = true;}
      while(ZXYfwBXMLA == eUwrkTSjWn){bHxVKdArtt = true;}
      while(jQUxzZhKpU == jQUxzZhKpU){zUMRUBnNtp = true;}
      while(tHtmsKgoQA == tHtmsKgoQA){FMXOMqGeRH = true;}
      if(MMfwQUfCVD == true){MMfwQUfCVD = false;}
      if(IFUgmbLptB == true){IFUgmbLptB = false;}
      if(TmAsMRdkml == true){TmAsMRdkml = false;}
      if(ThwLmWkYfd == true){ThwLmWkYfd = false;}
      if(sfnmMnlMAQ == true){sfnmMnlMAQ = false;}
      if(yquOfZMljy == true){yquOfZMljy = false;}
      if(qtPjiZJJtQ == true){qtPjiZJJtQ = false;}
      if(qmJPInzNgX == true){qmJPInzNgX = false;}
      if(fQkVmcmgeN == true){fQkVmcmgeN = false;}
      if(KyohlyPDDl == true){KyohlyPDDl = false;}
      if(ecSjZLgeGr == true){ecSjZLgeGr = false;}
      if(ayELSaJsxG == true){ayELSaJsxG = false;}
      if(lbegFrxbcJ == true){lbegFrxbcJ = false;}
      if(XuKtsDyBua == true){XuKtsDyBua = false;}
      if(wIalmLscOL == true){wIalmLscOL = false;}
      if(oWGwACxkdg == true){oWGwACxkdg = false;}
      if(OEBwTenJSP == true){OEBwTenJSP = false;}
      if(bHxVKdArtt == true){bHxVKdArtt = false;}
      if(zUMRUBnNtp == true){zUMRUBnNtp = false;}
      if(FMXOMqGeRH == true){FMXOMqGeRH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDQDTMGHYV
{ 
  void cYgGIOYUai()
  { 
      bool NTLEJprius = false;
      bool MsWJsxJlHM = false;
      bool VgXEdtYZuJ = false;
      bool sUUoXuFzRS = false;
      bool CCYxHAJjZB = false;
      bool WAJRsfwHaO = false;
      bool QSnkzrYhky = false;
      bool qKTnJTIawd = false;
      bool koAtlsKCwr = false;
      bool zxXDBjOmxP = false;
      bool aazaJMfUHY = false;
      bool XVLxcbRszG = false;
      bool gVlszslQmZ = false;
      bool FUcfCKoYkZ = false;
      bool MotWTdlaZZ = false;
      bool RUmqiEnGbP = false;
      bool ZPhhTCrftS = false;
      bool lsIZsqbPYV = false;
      bool HLqNHjglwx = false;
      bool ViwUAxGMDQ = false;
      string qWUfQduwKb;
      string nbAofLtWww;
      string rThaxujCta;
      string zintSKEMGO;
      string LHTBIIhZRM;
      string xKIUWXnthV;
      string tsBjbFnGWV;
      string GgQgkjzfRo;
      string MKjgcoZSWu;
      string VJdkURFjZD;
      string UaCuFQsajl;
      string XHbsIiIUGm;
      string eUiaAwCfMS;
      string ePGOTkHobM;
      string uzikWOhkbk;
      string JkdlXzrauI;
      string ONNQGIANYW;
      string aSrtqelyDl;
      string ORDbJtlTpU;
      string sftSyglRdO;
      if(qWUfQduwKb == UaCuFQsajl){NTLEJprius = true;}
      else if(UaCuFQsajl == qWUfQduwKb){aazaJMfUHY = true;}
      if(nbAofLtWww == XHbsIiIUGm){MsWJsxJlHM = true;}
      else if(XHbsIiIUGm == nbAofLtWww){XVLxcbRszG = true;}
      if(rThaxujCta == eUiaAwCfMS){VgXEdtYZuJ = true;}
      else if(eUiaAwCfMS == rThaxujCta){gVlszslQmZ = true;}
      if(zintSKEMGO == ePGOTkHobM){sUUoXuFzRS = true;}
      else if(ePGOTkHobM == zintSKEMGO){FUcfCKoYkZ = true;}
      if(LHTBIIhZRM == uzikWOhkbk){CCYxHAJjZB = true;}
      else if(uzikWOhkbk == LHTBIIhZRM){MotWTdlaZZ = true;}
      if(xKIUWXnthV == JkdlXzrauI){WAJRsfwHaO = true;}
      else if(JkdlXzrauI == xKIUWXnthV){RUmqiEnGbP = true;}
      if(tsBjbFnGWV == ONNQGIANYW){QSnkzrYhky = true;}
      else if(ONNQGIANYW == tsBjbFnGWV){ZPhhTCrftS = true;}
      if(GgQgkjzfRo == aSrtqelyDl){qKTnJTIawd = true;}
      if(MKjgcoZSWu == ORDbJtlTpU){koAtlsKCwr = true;}
      if(VJdkURFjZD == sftSyglRdO){zxXDBjOmxP = true;}
      while(aSrtqelyDl == GgQgkjzfRo){lsIZsqbPYV = true;}
      while(ORDbJtlTpU == ORDbJtlTpU){HLqNHjglwx = true;}
      while(sftSyglRdO == sftSyglRdO){ViwUAxGMDQ = true;}
      if(NTLEJprius == true){NTLEJprius = false;}
      if(MsWJsxJlHM == true){MsWJsxJlHM = false;}
      if(VgXEdtYZuJ == true){VgXEdtYZuJ = false;}
      if(sUUoXuFzRS == true){sUUoXuFzRS = false;}
      if(CCYxHAJjZB == true){CCYxHAJjZB = false;}
      if(WAJRsfwHaO == true){WAJRsfwHaO = false;}
      if(QSnkzrYhky == true){QSnkzrYhky = false;}
      if(qKTnJTIawd == true){qKTnJTIawd = false;}
      if(koAtlsKCwr == true){koAtlsKCwr = false;}
      if(zxXDBjOmxP == true){zxXDBjOmxP = false;}
      if(aazaJMfUHY == true){aazaJMfUHY = false;}
      if(XVLxcbRszG == true){XVLxcbRszG = false;}
      if(gVlszslQmZ == true){gVlszslQmZ = false;}
      if(FUcfCKoYkZ == true){FUcfCKoYkZ = false;}
      if(MotWTdlaZZ == true){MotWTdlaZZ = false;}
      if(RUmqiEnGbP == true){RUmqiEnGbP = false;}
      if(ZPhhTCrftS == true){ZPhhTCrftS = false;}
      if(lsIZsqbPYV == true){lsIZsqbPYV = false;}
      if(HLqNHjglwx == true){HLqNHjglwx = false;}
      if(ViwUAxGMDQ == true){ViwUAxGMDQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFLYVGYZIN
{ 
  void wlDRzQRuQn()
  { 
      bool obMWmYFpAB = false;
      bool VPnsnnMJHn = false;
      bool HjVtjtFmfx = false;
      bool IReMBQmJDK = false;
      bool nFaSDDwfCS = false;
      bool QADjEEFRms = false;
      bool SSJCrEkbqW = false;
      bool BCFxzCIDqf = false;
      bool xZkMfHNuHx = false;
      bool LUWKrVuYZz = false;
      bool RUoeRNuGjC = false;
      bool uBaGusgwVk = false;
      bool ppTtLffuEd = false;
      bool GjcrOcjFuS = false;
      bool MHKFCJtPOy = false;
      bool nzCoIbAtTk = false;
      bool hzBGuKYirS = false;
      bool IbBDXheOqC = false;
      bool lQgGoHhnim = false;
      bool bpkJjNGEJr = false;
      string LXDjVTsXgX;
      string oFUpUTQqlw;
      string LxdlrRnUKj;
      string zorsHLNOTd;
      string QxKzzqDljx;
      string UYSKZOtQrD;
      string fYNxYANbhI;
      string GCXHeNldmB;
      string NBjNOZVhSs;
      string QwWPxrjMay;
      string dbDapSBKeM;
      string cPdqodnAiz;
      string deIoqKeHKm;
      string dYDnWlyIWu;
      string XLCGQBRfZS;
      string DidbTySNif;
      string mtAqhDMpTD;
      string eednaScCYp;
      string rzgqitubTY;
      string TkYpHdKLXM;
      if(LXDjVTsXgX == dbDapSBKeM){obMWmYFpAB = true;}
      else if(dbDapSBKeM == LXDjVTsXgX){RUoeRNuGjC = true;}
      if(oFUpUTQqlw == cPdqodnAiz){VPnsnnMJHn = true;}
      else if(cPdqodnAiz == oFUpUTQqlw){uBaGusgwVk = true;}
      if(LxdlrRnUKj == deIoqKeHKm){HjVtjtFmfx = true;}
      else if(deIoqKeHKm == LxdlrRnUKj){ppTtLffuEd = true;}
      if(zorsHLNOTd == dYDnWlyIWu){IReMBQmJDK = true;}
      else if(dYDnWlyIWu == zorsHLNOTd){GjcrOcjFuS = true;}
      if(QxKzzqDljx == XLCGQBRfZS){nFaSDDwfCS = true;}
      else if(XLCGQBRfZS == QxKzzqDljx){MHKFCJtPOy = true;}
      if(UYSKZOtQrD == DidbTySNif){QADjEEFRms = true;}
      else if(DidbTySNif == UYSKZOtQrD){nzCoIbAtTk = true;}
      if(fYNxYANbhI == mtAqhDMpTD){SSJCrEkbqW = true;}
      else if(mtAqhDMpTD == fYNxYANbhI){hzBGuKYirS = true;}
      if(GCXHeNldmB == eednaScCYp){BCFxzCIDqf = true;}
      if(NBjNOZVhSs == rzgqitubTY){xZkMfHNuHx = true;}
      if(QwWPxrjMay == TkYpHdKLXM){LUWKrVuYZz = true;}
      while(eednaScCYp == GCXHeNldmB){IbBDXheOqC = true;}
      while(rzgqitubTY == rzgqitubTY){lQgGoHhnim = true;}
      while(TkYpHdKLXM == TkYpHdKLXM){bpkJjNGEJr = true;}
      if(obMWmYFpAB == true){obMWmYFpAB = false;}
      if(VPnsnnMJHn == true){VPnsnnMJHn = false;}
      if(HjVtjtFmfx == true){HjVtjtFmfx = false;}
      if(IReMBQmJDK == true){IReMBQmJDK = false;}
      if(nFaSDDwfCS == true){nFaSDDwfCS = false;}
      if(QADjEEFRms == true){QADjEEFRms = false;}
      if(SSJCrEkbqW == true){SSJCrEkbqW = false;}
      if(BCFxzCIDqf == true){BCFxzCIDqf = false;}
      if(xZkMfHNuHx == true){xZkMfHNuHx = false;}
      if(LUWKrVuYZz == true){LUWKrVuYZz = false;}
      if(RUoeRNuGjC == true){RUoeRNuGjC = false;}
      if(uBaGusgwVk == true){uBaGusgwVk = false;}
      if(ppTtLffuEd == true){ppTtLffuEd = false;}
      if(GjcrOcjFuS == true){GjcrOcjFuS = false;}
      if(MHKFCJtPOy == true){MHKFCJtPOy = false;}
      if(nzCoIbAtTk == true){nzCoIbAtTk = false;}
      if(hzBGuKYirS == true){hzBGuKYirS = false;}
      if(IbBDXheOqC == true){IbBDXheOqC = false;}
      if(lQgGoHhnim == true){lQgGoHhnim = false;}
      if(bpkJjNGEJr == true){bpkJjNGEJr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXEORFESFC
{ 
  void RYVVdjRBCJ()
  { 
      bool EjWyTmNQNk = false;
      bool XigdZsXCwd = false;
      bool IeCGhJNwGX = false;
      bool VObuURfgIt = false;
      bool AqfpEhqiJi = false;
      bool WyqOCYhPPJ = false;
      bool ZQKoPIGlJH = false;
      bool MptBcRzLCz = false;
      bool SemWBXWNrw = false;
      bool jPRyUigpau = false;
      bool aEYCVfDpkk = false;
      bool YWNPqudmmr = false;
      bool lssNWxYwgs = false;
      bool jJjGXNFjBV = false;
      bool TfbGWNCBGY = false;
      bool EsCiJhLLeY = false;
      bool HHJqAOlGqd = false;
      bool otkRXFQlpI = false;
      bool tWoHoqGAwp = false;
      bool CsFcOMWkGI = false;
      string leulgzNdUz;
      string BhUJYXYPiR;
      string TDKoEfcCkj;
      string GNUceufYTO;
      string PcqoxHBxhi;
      string FcabqhTFhA;
      string WLsksnNqdc;
      string qAwUBqMVrw;
      string eeUCddlrkx;
      string aaqSrEiFwJ;
      string tJTEqFfGaA;
      string VyMkUqppHP;
      string BUFgBPIcbw;
      string HGZiCVKPKY;
      string xeRkacNFxA;
      string OsyfHZDmCb;
      string wDddrPYdiz;
      string gaehSVCUFY;
      string CDebhOHsbb;
      string RXMibtAnrK;
      if(leulgzNdUz == tJTEqFfGaA){EjWyTmNQNk = true;}
      else if(tJTEqFfGaA == leulgzNdUz){aEYCVfDpkk = true;}
      if(BhUJYXYPiR == VyMkUqppHP){XigdZsXCwd = true;}
      else if(VyMkUqppHP == BhUJYXYPiR){YWNPqudmmr = true;}
      if(TDKoEfcCkj == BUFgBPIcbw){IeCGhJNwGX = true;}
      else if(BUFgBPIcbw == TDKoEfcCkj){lssNWxYwgs = true;}
      if(GNUceufYTO == HGZiCVKPKY){VObuURfgIt = true;}
      else if(HGZiCVKPKY == GNUceufYTO){jJjGXNFjBV = true;}
      if(PcqoxHBxhi == xeRkacNFxA){AqfpEhqiJi = true;}
      else if(xeRkacNFxA == PcqoxHBxhi){TfbGWNCBGY = true;}
      if(FcabqhTFhA == OsyfHZDmCb){WyqOCYhPPJ = true;}
      else if(OsyfHZDmCb == FcabqhTFhA){EsCiJhLLeY = true;}
      if(WLsksnNqdc == wDddrPYdiz){ZQKoPIGlJH = true;}
      else if(wDddrPYdiz == WLsksnNqdc){HHJqAOlGqd = true;}
      if(qAwUBqMVrw == gaehSVCUFY){MptBcRzLCz = true;}
      if(eeUCddlrkx == CDebhOHsbb){SemWBXWNrw = true;}
      if(aaqSrEiFwJ == RXMibtAnrK){jPRyUigpau = true;}
      while(gaehSVCUFY == qAwUBqMVrw){otkRXFQlpI = true;}
      while(CDebhOHsbb == CDebhOHsbb){tWoHoqGAwp = true;}
      while(RXMibtAnrK == RXMibtAnrK){CsFcOMWkGI = true;}
      if(EjWyTmNQNk == true){EjWyTmNQNk = false;}
      if(XigdZsXCwd == true){XigdZsXCwd = false;}
      if(IeCGhJNwGX == true){IeCGhJNwGX = false;}
      if(VObuURfgIt == true){VObuURfgIt = false;}
      if(AqfpEhqiJi == true){AqfpEhqiJi = false;}
      if(WyqOCYhPPJ == true){WyqOCYhPPJ = false;}
      if(ZQKoPIGlJH == true){ZQKoPIGlJH = false;}
      if(MptBcRzLCz == true){MptBcRzLCz = false;}
      if(SemWBXWNrw == true){SemWBXWNrw = false;}
      if(jPRyUigpau == true){jPRyUigpau = false;}
      if(aEYCVfDpkk == true){aEYCVfDpkk = false;}
      if(YWNPqudmmr == true){YWNPqudmmr = false;}
      if(lssNWxYwgs == true){lssNWxYwgs = false;}
      if(jJjGXNFjBV == true){jJjGXNFjBV = false;}
      if(TfbGWNCBGY == true){TfbGWNCBGY = false;}
      if(EsCiJhLLeY == true){EsCiJhLLeY = false;}
      if(HHJqAOlGqd == true){HHJqAOlGqd = false;}
      if(otkRXFQlpI == true){otkRXFQlpI = false;}
      if(tWoHoqGAwp == true){tWoHoqGAwp = false;}
      if(CsFcOMWkGI == true){CsFcOMWkGI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWOXECLZYG
{ 
  void NsYCFsWGsr()
  { 
      bool dQPhIxkYUt = false;
      bool zcBCjaPxlN = false;
      bool DGtHlLWRlu = false;
      bool JkuXOWDAJO = false;
      bool aeMHsIVwTg = false;
      bool kFFFWXVHuw = false;
      bool ZTmYkNhcnM = false;
      bool XOmWlYsmOd = false;
      bool oaxEKEfoBp = false;
      bool BuFNoHqmWe = false;
      bool asHHJVRhSy = false;
      bool eisQHzVhOf = false;
      bool hrbxLcIZhe = false;
      bool gFPiDwSpun = false;
      bool myWDLRCoGo = false;
      bool kJYpxhRKuf = false;
      bool NqzmQYSJMK = false;
      bool fflZsjUYls = false;
      bool aTTrtXfZlU = false;
      bool dItOauyjlm = false;
      string MEKgkFnGSA;
      string NwCgNqyWeS;
      string opHJuNoUBk;
      string SkLJjAUZcR;
      string DMzuOeofTx;
      string CfosWVxBlX;
      string QSEghbjswN;
      string VXsMPcpLuP;
      string XIBEhlwSmO;
      string DTnFBjISNl;
      string twiGaembct;
      string ekFWzIRAyw;
      string fRFhKCjnLe;
      string UXyIVbYucD;
      string zToriRNQFr;
      string SITQGbpBuY;
      string tyQyZHmxBX;
      string jVWuwMcNzs;
      string nShSLMDgCs;
      string kXzEIACqSa;
      if(MEKgkFnGSA == twiGaembct){dQPhIxkYUt = true;}
      else if(twiGaembct == MEKgkFnGSA){asHHJVRhSy = true;}
      if(NwCgNqyWeS == ekFWzIRAyw){zcBCjaPxlN = true;}
      else if(ekFWzIRAyw == NwCgNqyWeS){eisQHzVhOf = true;}
      if(opHJuNoUBk == fRFhKCjnLe){DGtHlLWRlu = true;}
      else if(fRFhKCjnLe == opHJuNoUBk){hrbxLcIZhe = true;}
      if(SkLJjAUZcR == UXyIVbYucD){JkuXOWDAJO = true;}
      else if(UXyIVbYucD == SkLJjAUZcR){gFPiDwSpun = true;}
      if(DMzuOeofTx == zToriRNQFr){aeMHsIVwTg = true;}
      else if(zToriRNQFr == DMzuOeofTx){myWDLRCoGo = true;}
      if(CfosWVxBlX == SITQGbpBuY){kFFFWXVHuw = true;}
      else if(SITQGbpBuY == CfosWVxBlX){kJYpxhRKuf = true;}
      if(QSEghbjswN == tyQyZHmxBX){ZTmYkNhcnM = true;}
      else if(tyQyZHmxBX == QSEghbjswN){NqzmQYSJMK = true;}
      if(VXsMPcpLuP == jVWuwMcNzs){XOmWlYsmOd = true;}
      if(XIBEhlwSmO == nShSLMDgCs){oaxEKEfoBp = true;}
      if(DTnFBjISNl == kXzEIACqSa){BuFNoHqmWe = true;}
      while(jVWuwMcNzs == VXsMPcpLuP){fflZsjUYls = true;}
      while(nShSLMDgCs == nShSLMDgCs){aTTrtXfZlU = true;}
      while(kXzEIACqSa == kXzEIACqSa){dItOauyjlm = true;}
      if(dQPhIxkYUt == true){dQPhIxkYUt = false;}
      if(zcBCjaPxlN == true){zcBCjaPxlN = false;}
      if(DGtHlLWRlu == true){DGtHlLWRlu = false;}
      if(JkuXOWDAJO == true){JkuXOWDAJO = false;}
      if(aeMHsIVwTg == true){aeMHsIVwTg = false;}
      if(kFFFWXVHuw == true){kFFFWXVHuw = false;}
      if(ZTmYkNhcnM == true){ZTmYkNhcnM = false;}
      if(XOmWlYsmOd == true){XOmWlYsmOd = false;}
      if(oaxEKEfoBp == true){oaxEKEfoBp = false;}
      if(BuFNoHqmWe == true){BuFNoHqmWe = false;}
      if(asHHJVRhSy == true){asHHJVRhSy = false;}
      if(eisQHzVhOf == true){eisQHzVhOf = false;}
      if(hrbxLcIZhe == true){hrbxLcIZhe = false;}
      if(gFPiDwSpun == true){gFPiDwSpun = false;}
      if(myWDLRCoGo == true){myWDLRCoGo = false;}
      if(kJYpxhRKuf == true){kJYpxhRKuf = false;}
      if(NqzmQYSJMK == true){NqzmQYSJMK = false;}
      if(fflZsjUYls == true){fflZsjUYls = false;}
      if(aTTrtXfZlU == true){aTTrtXfZlU = false;}
      if(dItOauyjlm == true){dItOauyjlm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASRUZLYDEB
{ 
  void TeYpfsLATh()
  { 
      bool OhGMkpOZyO = false;
      bool NuoPWsLmqt = false;
      bool ODUzQDhhla = false;
      bool yQWCMMKRFV = false;
      bool IIrMNddZZj = false;
      bool XuXXaKMGwh = false;
      bool HfmWQwYlCJ = false;
      bool htgVlGKHll = false;
      bool ZHIBCCszbB = false;
      bool zEVXNbUVwQ = false;
      bool FrXPCdOClT = false;
      bool zFTJIAXkTN = false;
      bool DYKAJcXIHK = false;
      bool koLUggjrzY = false;
      bool nqNHCtjLPN = false;
      bool DiBhNfhWFY = false;
      bool FFtaiKszba = false;
      bool PfluYLLCyP = false;
      bool sMssHBmcHB = false;
      bool zNlZSiwlYq = false;
      string JXSIoKiSlB;
      string oGDthyPKFR;
      string zRfmyUVXRi;
      string NEMLCtcmXW;
      string bqxjZkBFPL;
      string lMNRrqqfJT;
      string nLBCnksrqn;
      string VblhpITwMN;
      string TPHFxBqtTK;
      string DxdDhQpuwo;
      string rJObpJZebj;
      string WtSwAYDuEm;
      string syYfjYyiAY;
      string RYAWUKBfPn;
      string aMSinIdgDI;
      string MupJusjhqR;
      string KqdDRxtwap;
      string XWfQLgforb;
      string tReqLWipaa;
      string ZToxdjhORp;
      if(JXSIoKiSlB == rJObpJZebj){OhGMkpOZyO = true;}
      else if(rJObpJZebj == JXSIoKiSlB){FrXPCdOClT = true;}
      if(oGDthyPKFR == WtSwAYDuEm){NuoPWsLmqt = true;}
      else if(WtSwAYDuEm == oGDthyPKFR){zFTJIAXkTN = true;}
      if(zRfmyUVXRi == syYfjYyiAY){ODUzQDhhla = true;}
      else if(syYfjYyiAY == zRfmyUVXRi){DYKAJcXIHK = true;}
      if(NEMLCtcmXW == RYAWUKBfPn){yQWCMMKRFV = true;}
      else if(RYAWUKBfPn == NEMLCtcmXW){koLUggjrzY = true;}
      if(bqxjZkBFPL == aMSinIdgDI){IIrMNddZZj = true;}
      else if(aMSinIdgDI == bqxjZkBFPL){nqNHCtjLPN = true;}
      if(lMNRrqqfJT == MupJusjhqR){XuXXaKMGwh = true;}
      else if(MupJusjhqR == lMNRrqqfJT){DiBhNfhWFY = true;}
      if(nLBCnksrqn == KqdDRxtwap){HfmWQwYlCJ = true;}
      else if(KqdDRxtwap == nLBCnksrqn){FFtaiKszba = true;}
      if(VblhpITwMN == XWfQLgforb){htgVlGKHll = true;}
      if(TPHFxBqtTK == tReqLWipaa){ZHIBCCszbB = true;}
      if(DxdDhQpuwo == ZToxdjhORp){zEVXNbUVwQ = true;}
      while(XWfQLgforb == VblhpITwMN){PfluYLLCyP = true;}
      while(tReqLWipaa == tReqLWipaa){sMssHBmcHB = true;}
      while(ZToxdjhORp == ZToxdjhORp){zNlZSiwlYq = true;}
      if(OhGMkpOZyO == true){OhGMkpOZyO = false;}
      if(NuoPWsLmqt == true){NuoPWsLmqt = false;}
      if(ODUzQDhhla == true){ODUzQDhhla = false;}
      if(yQWCMMKRFV == true){yQWCMMKRFV = false;}
      if(IIrMNddZZj == true){IIrMNddZZj = false;}
      if(XuXXaKMGwh == true){XuXXaKMGwh = false;}
      if(HfmWQwYlCJ == true){HfmWQwYlCJ = false;}
      if(htgVlGKHll == true){htgVlGKHll = false;}
      if(ZHIBCCszbB == true){ZHIBCCszbB = false;}
      if(zEVXNbUVwQ == true){zEVXNbUVwQ = false;}
      if(FrXPCdOClT == true){FrXPCdOClT = false;}
      if(zFTJIAXkTN == true){zFTJIAXkTN = false;}
      if(DYKAJcXIHK == true){DYKAJcXIHK = false;}
      if(koLUggjrzY == true){koLUggjrzY = false;}
      if(nqNHCtjLPN == true){nqNHCtjLPN = false;}
      if(DiBhNfhWFY == true){DiBhNfhWFY = false;}
      if(FFtaiKszba == true){FFtaiKszba = false;}
      if(PfluYLLCyP == true){PfluYLLCyP = false;}
      if(sMssHBmcHB == true){sMssHBmcHB = false;}
      if(zNlZSiwlYq == true){zNlZSiwlYq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KFUOQWTZES
{ 
  void ZkWQVLpFhF()
  { 
      bool DRLfyrolZb = false;
      bool MwLZDryRiB = false;
      bool RCAdVSwRLO = false;
      bool yOSbbeeran = false;
      bool bAnKPczZXi = false;
      bool BmsZcBQgKe = false;
      bool wXZLdxcixY = false;
      bool NGpuZRNpOr = false;
      bool TVtcNKVsza = false;
      bool OxguqEZcgR = false;
      bool zPcyVtwxzL = false;
      bool naSRLacxyS = false;
      bool bjiWKPYuEV = false;
      bool qkJxrDruHS = false;
      bool NXsnmmePjQ = false;
      bool aceNoPfGnG = false;
      bool VBscTDRUYH = false;
      bool hhpeEEpuiW = false;
      bool jJKnuOFuIb = false;
      bool WkGBxMePTi = false;
      string GaUegHazMZ;
      string ZtstcdYZZS;
      string QIdQYckLxK;
      string xkdpLlPLoW;
      string GIZBSEhmyR;
      string GFwybywDGE;
      string VPCCbnPCip;
      string ONjCMHibxU;
      string tyNfDqoeON;
      string oLEkAqGXYe;
      string neEHDsVslT;
      string OTGlJXCWyj;
      string zjnVBCJyCV;
      string BLDSfPsFcK;
      string VwstyUFRac;
      string ojYneDpiFA;
      string iWqQSDQnGt;
      string dwtmODqtWf;
      string wqXYgQlOmb;
      string YKAbazEcat;
      if(GaUegHazMZ == neEHDsVslT){DRLfyrolZb = true;}
      else if(neEHDsVslT == GaUegHazMZ){zPcyVtwxzL = true;}
      if(ZtstcdYZZS == OTGlJXCWyj){MwLZDryRiB = true;}
      else if(OTGlJXCWyj == ZtstcdYZZS){naSRLacxyS = true;}
      if(QIdQYckLxK == zjnVBCJyCV){RCAdVSwRLO = true;}
      else if(zjnVBCJyCV == QIdQYckLxK){bjiWKPYuEV = true;}
      if(xkdpLlPLoW == BLDSfPsFcK){yOSbbeeran = true;}
      else if(BLDSfPsFcK == xkdpLlPLoW){qkJxrDruHS = true;}
      if(GIZBSEhmyR == VwstyUFRac){bAnKPczZXi = true;}
      else if(VwstyUFRac == GIZBSEhmyR){NXsnmmePjQ = true;}
      if(GFwybywDGE == ojYneDpiFA){BmsZcBQgKe = true;}
      else if(ojYneDpiFA == GFwybywDGE){aceNoPfGnG = true;}
      if(VPCCbnPCip == iWqQSDQnGt){wXZLdxcixY = true;}
      else if(iWqQSDQnGt == VPCCbnPCip){VBscTDRUYH = true;}
      if(ONjCMHibxU == dwtmODqtWf){NGpuZRNpOr = true;}
      if(tyNfDqoeON == wqXYgQlOmb){TVtcNKVsza = true;}
      if(oLEkAqGXYe == YKAbazEcat){OxguqEZcgR = true;}
      while(dwtmODqtWf == ONjCMHibxU){hhpeEEpuiW = true;}
      while(wqXYgQlOmb == wqXYgQlOmb){jJKnuOFuIb = true;}
      while(YKAbazEcat == YKAbazEcat){WkGBxMePTi = true;}
      if(DRLfyrolZb == true){DRLfyrolZb = false;}
      if(MwLZDryRiB == true){MwLZDryRiB = false;}
      if(RCAdVSwRLO == true){RCAdVSwRLO = false;}
      if(yOSbbeeran == true){yOSbbeeran = false;}
      if(bAnKPczZXi == true){bAnKPczZXi = false;}
      if(BmsZcBQgKe == true){BmsZcBQgKe = false;}
      if(wXZLdxcixY == true){wXZLdxcixY = false;}
      if(NGpuZRNpOr == true){NGpuZRNpOr = false;}
      if(TVtcNKVsza == true){TVtcNKVsza = false;}
      if(OxguqEZcgR == true){OxguqEZcgR = false;}
      if(zPcyVtwxzL == true){zPcyVtwxzL = false;}
      if(naSRLacxyS == true){naSRLacxyS = false;}
      if(bjiWKPYuEV == true){bjiWKPYuEV = false;}
      if(qkJxrDruHS == true){qkJxrDruHS = false;}
      if(NXsnmmePjQ == true){NXsnmmePjQ = false;}
      if(aceNoPfGnG == true){aceNoPfGnG = false;}
      if(VBscTDRUYH == true){VBscTDRUYH = false;}
      if(hhpeEEpuiW == true){hhpeEEpuiW = false;}
      if(jJKnuOFuIb == true){jJKnuOFuIb = false;}
      if(WkGBxMePTi == true){WkGBxMePTi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBALBIFJAF
{ 
  void TEDpGrxsYG()
  { 
      bool dedIDiHDZz = false;
      bool wZSoPInDak = false;
      bool omqoetfPyP = false;
      bool ADOFFbCWrK = false;
      bool MSPzLwJfmx = false;
      bool HDZCnpmndJ = false;
      bool DrFJyrLMjn = false;
      bool GQKQXWXrdi = false;
      bool jzbAHwdMQO = false;
      bool nNsiGTMFAS = false;
      bool jxwyqqrJdR = false;
      bool RtKuYDQFBB = false;
      bool NzuUAsXbJE = false;
      bool JSrKymDcJQ = false;
      bool DUhywsCxJD = false;
      bool DHDyFkBayx = false;
      bool SQzZIzCzwl = false;
      bool AmwkxsQwXH = false;
      bool qZSGABOsFN = false;
      bool kbeLymUIpx = false;
      string TyHwyoXmUn;
      string iVBIAfJcfs;
      string GpGkGdiUSb;
      string ksbMGBmVch;
      string joDRKVKcMr;
      string iKRIScrVpT;
      string GDTsDotnCy;
      string smzxJQmoaj;
      string TFHZraaTtd;
      string JQfJbfUJNU;
      string bVaNzwKUyB;
      string oDuFzButBb;
      string OZtYobGpVd;
      string udaFIyetaw;
      string QGUroGUaKZ;
      string jaIlGBbCXW;
      string oTzTFKbpwB;
      string WBSELHEBii;
      string GffusUVoyH;
      string VcVDGwHBmd;
      if(TyHwyoXmUn == bVaNzwKUyB){dedIDiHDZz = true;}
      else if(bVaNzwKUyB == TyHwyoXmUn){jxwyqqrJdR = true;}
      if(iVBIAfJcfs == oDuFzButBb){wZSoPInDak = true;}
      else if(oDuFzButBb == iVBIAfJcfs){RtKuYDQFBB = true;}
      if(GpGkGdiUSb == OZtYobGpVd){omqoetfPyP = true;}
      else if(OZtYobGpVd == GpGkGdiUSb){NzuUAsXbJE = true;}
      if(ksbMGBmVch == udaFIyetaw){ADOFFbCWrK = true;}
      else if(udaFIyetaw == ksbMGBmVch){JSrKymDcJQ = true;}
      if(joDRKVKcMr == QGUroGUaKZ){MSPzLwJfmx = true;}
      else if(QGUroGUaKZ == joDRKVKcMr){DUhywsCxJD = true;}
      if(iKRIScrVpT == jaIlGBbCXW){HDZCnpmndJ = true;}
      else if(jaIlGBbCXW == iKRIScrVpT){DHDyFkBayx = true;}
      if(GDTsDotnCy == oTzTFKbpwB){DrFJyrLMjn = true;}
      else if(oTzTFKbpwB == GDTsDotnCy){SQzZIzCzwl = true;}
      if(smzxJQmoaj == WBSELHEBii){GQKQXWXrdi = true;}
      if(TFHZraaTtd == GffusUVoyH){jzbAHwdMQO = true;}
      if(JQfJbfUJNU == VcVDGwHBmd){nNsiGTMFAS = true;}
      while(WBSELHEBii == smzxJQmoaj){AmwkxsQwXH = true;}
      while(GffusUVoyH == GffusUVoyH){qZSGABOsFN = true;}
      while(VcVDGwHBmd == VcVDGwHBmd){kbeLymUIpx = true;}
      if(dedIDiHDZz == true){dedIDiHDZz = false;}
      if(wZSoPInDak == true){wZSoPInDak = false;}
      if(omqoetfPyP == true){omqoetfPyP = false;}
      if(ADOFFbCWrK == true){ADOFFbCWrK = false;}
      if(MSPzLwJfmx == true){MSPzLwJfmx = false;}
      if(HDZCnpmndJ == true){HDZCnpmndJ = false;}
      if(DrFJyrLMjn == true){DrFJyrLMjn = false;}
      if(GQKQXWXrdi == true){GQKQXWXrdi = false;}
      if(jzbAHwdMQO == true){jzbAHwdMQO = false;}
      if(nNsiGTMFAS == true){nNsiGTMFAS = false;}
      if(jxwyqqrJdR == true){jxwyqqrJdR = false;}
      if(RtKuYDQFBB == true){RtKuYDQFBB = false;}
      if(NzuUAsXbJE == true){NzuUAsXbJE = false;}
      if(JSrKymDcJQ == true){JSrKymDcJQ = false;}
      if(DUhywsCxJD == true){DUhywsCxJD = false;}
      if(DHDyFkBayx == true){DHDyFkBayx = false;}
      if(SQzZIzCzwl == true){SQzZIzCzwl = false;}
      if(AmwkxsQwXH == true){AmwkxsQwXH = false;}
      if(qZSGABOsFN == true){qZSGABOsFN = false;}
      if(kbeLymUIpx == true){kbeLymUIpx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CXOOYPEWVI
{ 
  void pGwoZSJmur()
  { 
      bool WZSMmOrQqC = false;
      bool oZlmzrhbLE = false;
      bool kLHJdZTjeO = false;
      bool pOouoMZsar = false;
      bool LjaKCjHemf = false;
      bool uOEZpKRIhM = false;
      bool tHlcMakqym = false;
      bool SoATrBkxHs = false;
      bool SoxzSbJPEd = false;
      bool tQKOxDyyxa = false;
      bool zPfANFNkgo = false;
      bool ZUAntEKmJk = false;
      bool RVlTrBdlVo = false;
      bool DmzftCJwkN = false;
      bool NXhPEZPVTs = false;
      bool sKnMJcdMHL = false;
      bool bbPqklVUtr = false;
      bool uNBwWsmWPS = false;
      bool lIRcwrylVQ = false;
      bool YxoZllHpeR = false;
      string OftAPZMmQd;
      string zLpqwGjnzu;
      string eDHmsUDgzx;
      string HxqVhEQomA;
      string jzANwASEDH;
      string quIjHLYGGt;
      string VfmSVBTTIr;
      string ptAyLeDsqs;
      string CycqFMoHOW;
      string fJhsdELgru;
      string gyuLRxuJYb;
      string IePNrWDwMJ;
      string LMFlMfMGUH;
      string TVBuLDDQYI;
      string RehlOAsUBG;
      string APUiiTsJzl;
      string jnoRIldTBn;
      string TlWDrfeSWL;
      string lrFNGDARMq;
      string KtRmYcpPdb;
      if(OftAPZMmQd == gyuLRxuJYb){WZSMmOrQqC = true;}
      else if(gyuLRxuJYb == OftAPZMmQd){zPfANFNkgo = true;}
      if(zLpqwGjnzu == IePNrWDwMJ){oZlmzrhbLE = true;}
      else if(IePNrWDwMJ == zLpqwGjnzu){ZUAntEKmJk = true;}
      if(eDHmsUDgzx == LMFlMfMGUH){kLHJdZTjeO = true;}
      else if(LMFlMfMGUH == eDHmsUDgzx){RVlTrBdlVo = true;}
      if(HxqVhEQomA == TVBuLDDQYI){pOouoMZsar = true;}
      else if(TVBuLDDQYI == HxqVhEQomA){DmzftCJwkN = true;}
      if(jzANwASEDH == RehlOAsUBG){LjaKCjHemf = true;}
      else if(RehlOAsUBG == jzANwASEDH){NXhPEZPVTs = true;}
      if(quIjHLYGGt == APUiiTsJzl){uOEZpKRIhM = true;}
      else if(APUiiTsJzl == quIjHLYGGt){sKnMJcdMHL = true;}
      if(VfmSVBTTIr == jnoRIldTBn){tHlcMakqym = true;}
      else if(jnoRIldTBn == VfmSVBTTIr){bbPqklVUtr = true;}
      if(ptAyLeDsqs == TlWDrfeSWL){SoATrBkxHs = true;}
      if(CycqFMoHOW == lrFNGDARMq){SoxzSbJPEd = true;}
      if(fJhsdELgru == KtRmYcpPdb){tQKOxDyyxa = true;}
      while(TlWDrfeSWL == ptAyLeDsqs){uNBwWsmWPS = true;}
      while(lrFNGDARMq == lrFNGDARMq){lIRcwrylVQ = true;}
      while(KtRmYcpPdb == KtRmYcpPdb){YxoZllHpeR = true;}
      if(WZSMmOrQqC == true){WZSMmOrQqC = false;}
      if(oZlmzrhbLE == true){oZlmzrhbLE = false;}
      if(kLHJdZTjeO == true){kLHJdZTjeO = false;}
      if(pOouoMZsar == true){pOouoMZsar = false;}
      if(LjaKCjHemf == true){LjaKCjHemf = false;}
      if(uOEZpKRIhM == true){uOEZpKRIhM = false;}
      if(tHlcMakqym == true){tHlcMakqym = false;}
      if(SoATrBkxHs == true){SoATrBkxHs = false;}
      if(SoxzSbJPEd == true){SoxzSbJPEd = false;}
      if(tQKOxDyyxa == true){tQKOxDyyxa = false;}
      if(zPfANFNkgo == true){zPfANFNkgo = false;}
      if(ZUAntEKmJk == true){ZUAntEKmJk = false;}
      if(RVlTrBdlVo == true){RVlTrBdlVo = false;}
      if(DmzftCJwkN == true){DmzftCJwkN = false;}
      if(NXhPEZPVTs == true){NXhPEZPVTs = false;}
      if(sKnMJcdMHL == true){sKnMJcdMHL = false;}
      if(bbPqklVUtr == true){bbPqklVUtr = false;}
      if(uNBwWsmWPS == true){uNBwWsmWPS = false;}
      if(lIRcwrylVQ == true){lIRcwrylVQ = false;}
      if(YxoZllHpeR == true){YxoZllHpeR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMRGIOLCRF
{ 
  void JKYhmOYkxN()
  { 
      bool PGpayjjtXi = false;
      bool nwLIXHnDIQ = false;
      bool nEjhTsiUnc = false;
      bool ReKwnSFtuK = false;
      bool bBizDIposh = false;
      bool dfOOpLVIGF = false;
      bool BOGuQIlPUF = false;
      bool CtIyomUkeK = false;
      bool DsbGykQuFc = false;
      bool wwmoINumht = false;
      bool WZUnejXPZC = false;
      bool pkdwCIlzxf = false;
      bool rqJqIFGSpb = false;
      bool rhCjncXnaN = false;
      bool MAUDmLSqmA = false;
      bool auoBCfQdeZ = false;
      bool dFZyKIhtIZ = false;
      bool jyYjTqVGEx = false;
      bool mPfoAwrBgI = false;
      bool LtJBjHZWrd = false;
      string QIVIsxgZiU;
      string OyDDRmPOmW;
      string kszAxqAmOE;
      string jPbirXehWY;
      string CgadQrJlkE;
      string wYzjOXIULB;
      string wsKejyWUKs;
      string IhrOUDRUjE;
      string hOBKHKQqUU;
      string OJWUbIVwsR;
      string VnaqwOgjPK;
      string FmkGThqAWY;
      string heAoeyLWmL;
      string hUbRhsmKOs;
      string dgbJOaYPBs;
      string QVYTjqmlMx;
      string DKwDckLSYZ;
      string tglduBDqZD;
      string YuVstLwHhq;
      string FByQoSjXfd;
      if(QIVIsxgZiU == VnaqwOgjPK){PGpayjjtXi = true;}
      else if(VnaqwOgjPK == QIVIsxgZiU){WZUnejXPZC = true;}
      if(OyDDRmPOmW == FmkGThqAWY){nwLIXHnDIQ = true;}
      else if(FmkGThqAWY == OyDDRmPOmW){pkdwCIlzxf = true;}
      if(kszAxqAmOE == heAoeyLWmL){nEjhTsiUnc = true;}
      else if(heAoeyLWmL == kszAxqAmOE){rqJqIFGSpb = true;}
      if(jPbirXehWY == hUbRhsmKOs){ReKwnSFtuK = true;}
      else if(hUbRhsmKOs == jPbirXehWY){rhCjncXnaN = true;}
      if(CgadQrJlkE == dgbJOaYPBs){bBizDIposh = true;}
      else if(dgbJOaYPBs == CgadQrJlkE){MAUDmLSqmA = true;}
      if(wYzjOXIULB == QVYTjqmlMx){dfOOpLVIGF = true;}
      else if(QVYTjqmlMx == wYzjOXIULB){auoBCfQdeZ = true;}
      if(wsKejyWUKs == DKwDckLSYZ){BOGuQIlPUF = true;}
      else if(DKwDckLSYZ == wsKejyWUKs){dFZyKIhtIZ = true;}
      if(IhrOUDRUjE == tglduBDqZD){CtIyomUkeK = true;}
      if(hOBKHKQqUU == YuVstLwHhq){DsbGykQuFc = true;}
      if(OJWUbIVwsR == FByQoSjXfd){wwmoINumht = true;}
      while(tglduBDqZD == IhrOUDRUjE){jyYjTqVGEx = true;}
      while(YuVstLwHhq == YuVstLwHhq){mPfoAwrBgI = true;}
      while(FByQoSjXfd == FByQoSjXfd){LtJBjHZWrd = true;}
      if(PGpayjjtXi == true){PGpayjjtXi = false;}
      if(nwLIXHnDIQ == true){nwLIXHnDIQ = false;}
      if(nEjhTsiUnc == true){nEjhTsiUnc = false;}
      if(ReKwnSFtuK == true){ReKwnSFtuK = false;}
      if(bBizDIposh == true){bBizDIposh = false;}
      if(dfOOpLVIGF == true){dfOOpLVIGF = false;}
      if(BOGuQIlPUF == true){BOGuQIlPUF = false;}
      if(CtIyomUkeK == true){CtIyomUkeK = false;}
      if(DsbGykQuFc == true){DsbGykQuFc = false;}
      if(wwmoINumht == true){wwmoINumht = false;}
      if(WZUnejXPZC == true){WZUnejXPZC = false;}
      if(pkdwCIlzxf == true){pkdwCIlzxf = false;}
      if(rqJqIFGSpb == true){rqJqIFGSpb = false;}
      if(rhCjncXnaN == true){rhCjncXnaN = false;}
      if(MAUDmLSqmA == true){MAUDmLSqmA = false;}
      if(auoBCfQdeZ == true){auoBCfQdeZ = false;}
      if(dFZyKIhtIZ == true){dFZyKIhtIZ = false;}
      if(jyYjTqVGEx == true){jyYjTqVGEx = false;}
      if(mPfoAwrBgI == true){mPfoAwrBgI = false;}
      if(LtJBjHZWrd == true){LtJBjHZWrd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOERIVGAPR
{ 
  void YywJFrbfKw()
  { 
      bool JJKqPNLSuZ = false;
      bool AbLDyYQSSM = false;
      bool ctFIeHQJzV = false;
      bool iKriknsdtp = false;
      bool UWWUgPJaBu = false;
      bool zxibVOEBLH = false;
      bool wCTZpoicSJ = false;
      bool emYbqGXjbP = false;
      bool xpHDVkaPMW = false;
      bool jqRltSDxdq = false;
      bool fgHrPMYHjP = false;
      bool qTZwJFuPDF = false;
      bool NSPuYnUlgY = false;
      bool DaGkiQhOnJ = false;
      bool LTfxfQRVbn = false;
      bool WmsYcMQMSb = false;
      bool qlZLMPNnMs = false;
      bool WfbsstmSPI = false;
      bool WzKsBPggHV = false;
      bool zVwLSZtTjP = false;
      string ygSHXRUrAa;
      string zguuJMCtYs;
      string KaBPghQDlE;
      string NkmDiMeLZl;
      string ygxgepMGMl;
      string YoPeZWeDap;
      string BQFuMNsqMx;
      string hpTludcTjq;
      string UJqAeXVIdL;
      string gakjjhaBUQ;
      string xVtODhVcjw;
      string tLSiVrYFPn;
      string rkNAQGFiBN;
      string CaySszPcww;
      string CrXhRVIBNr;
      string IUlgYMHtyw;
      string clbWsSMzpW;
      string cuJSkzMfht;
      string yEVJEgoRtg;
      string qUdATPQBnz;
      if(ygSHXRUrAa == xVtODhVcjw){JJKqPNLSuZ = true;}
      else if(xVtODhVcjw == ygSHXRUrAa){fgHrPMYHjP = true;}
      if(zguuJMCtYs == tLSiVrYFPn){AbLDyYQSSM = true;}
      else if(tLSiVrYFPn == zguuJMCtYs){qTZwJFuPDF = true;}
      if(KaBPghQDlE == rkNAQGFiBN){ctFIeHQJzV = true;}
      else if(rkNAQGFiBN == KaBPghQDlE){NSPuYnUlgY = true;}
      if(NkmDiMeLZl == CaySszPcww){iKriknsdtp = true;}
      else if(CaySszPcww == NkmDiMeLZl){DaGkiQhOnJ = true;}
      if(ygxgepMGMl == CrXhRVIBNr){UWWUgPJaBu = true;}
      else if(CrXhRVIBNr == ygxgepMGMl){LTfxfQRVbn = true;}
      if(YoPeZWeDap == IUlgYMHtyw){zxibVOEBLH = true;}
      else if(IUlgYMHtyw == YoPeZWeDap){WmsYcMQMSb = true;}
      if(BQFuMNsqMx == clbWsSMzpW){wCTZpoicSJ = true;}
      else if(clbWsSMzpW == BQFuMNsqMx){qlZLMPNnMs = true;}
      if(hpTludcTjq == cuJSkzMfht){emYbqGXjbP = true;}
      if(UJqAeXVIdL == yEVJEgoRtg){xpHDVkaPMW = true;}
      if(gakjjhaBUQ == qUdATPQBnz){jqRltSDxdq = true;}
      while(cuJSkzMfht == hpTludcTjq){WfbsstmSPI = true;}
      while(yEVJEgoRtg == yEVJEgoRtg){WzKsBPggHV = true;}
      while(qUdATPQBnz == qUdATPQBnz){zVwLSZtTjP = true;}
      if(JJKqPNLSuZ == true){JJKqPNLSuZ = false;}
      if(AbLDyYQSSM == true){AbLDyYQSSM = false;}
      if(ctFIeHQJzV == true){ctFIeHQJzV = false;}
      if(iKriknsdtp == true){iKriknsdtp = false;}
      if(UWWUgPJaBu == true){UWWUgPJaBu = false;}
      if(zxibVOEBLH == true){zxibVOEBLH = false;}
      if(wCTZpoicSJ == true){wCTZpoicSJ = false;}
      if(emYbqGXjbP == true){emYbqGXjbP = false;}
      if(xpHDVkaPMW == true){xpHDVkaPMW = false;}
      if(jqRltSDxdq == true){jqRltSDxdq = false;}
      if(fgHrPMYHjP == true){fgHrPMYHjP = false;}
      if(qTZwJFuPDF == true){qTZwJFuPDF = false;}
      if(NSPuYnUlgY == true){NSPuYnUlgY = false;}
      if(DaGkiQhOnJ == true){DaGkiQhOnJ = false;}
      if(LTfxfQRVbn == true){LTfxfQRVbn = false;}
      if(WmsYcMQMSb == true){WmsYcMQMSb = false;}
      if(qlZLMPNnMs == true){qlZLMPNnMs = false;}
      if(WfbsstmSPI == true){WfbsstmSPI = false;}
      if(WzKsBPggHV == true){WzKsBPggHV = false;}
      if(zVwLSZtTjP == true){zVwLSZtTjP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEQIAGXVPK
{ 
  void AIZiUtdVAF()
  { 
      bool SmTRQKqMQy = false;
      bool RBkFrpDFYn = false;
      bool xMTKVkhOam = false;
      bool NRZqRGZYwn = false;
      bool IrYUFXyYyU = false;
      bool xwFLjGSIwe = false;
      bool bclcjAbsmk = false;
      bool PeJjfFnzFx = false;
      bool mJQFoRMNHL = false;
      bool mQcRMfFujF = false;
      bool uEkMESlUfe = false;
      bool STDyqRLfmS = false;
      bool mOlbyyBqWz = false;
      bool zrOzBhYDBV = false;
      bool eqhbrSNdZu = false;
      bool TZHRRgSJOF = false;
      bool RuyffZEEwJ = false;
      bool sHeQmwfKie = false;
      bool kWQbfZjxgU = false;
      bool POouEjsBwS = false;
      string KzGNCQiTht;
      string fEZdZOCLla;
      string WWOEyPjkEZ;
      string KIMndBykwj;
      string BtnaWCaUUV;
      string yOUSNnjCPl;
      string gxPIiXqlzX;
      string PROCYbimgw;
      string oPQhbwmtZp;
      string RwVKDDeerz;
      string KnUwFfzSsl;
      string FwUTwQgggl;
      string kxMJFTwEzV;
      string xDuhkBuUbu;
      string xUBnjUaCNl;
      string WxyFONaKpk;
      string juSXnCBmhu;
      string VMFkoPuYZk;
      string stqMyAEoTX;
      string ZjdpKBBdzh;
      if(KzGNCQiTht == KnUwFfzSsl){SmTRQKqMQy = true;}
      else if(KnUwFfzSsl == KzGNCQiTht){uEkMESlUfe = true;}
      if(fEZdZOCLla == FwUTwQgggl){RBkFrpDFYn = true;}
      else if(FwUTwQgggl == fEZdZOCLla){STDyqRLfmS = true;}
      if(WWOEyPjkEZ == kxMJFTwEzV){xMTKVkhOam = true;}
      else if(kxMJFTwEzV == WWOEyPjkEZ){mOlbyyBqWz = true;}
      if(KIMndBykwj == xDuhkBuUbu){NRZqRGZYwn = true;}
      else if(xDuhkBuUbu == KIMndBykwj){zrOzBhYDBV = true;}
      if(BtnaWCaUUV == xUBnjUaCNl){IrYUFXyYyU = true;}
      else if(xUBnjUaCNl == BtnaWCaUUV){eqhbrSNdZu = true;}
      if(yOUSNnjCPl == WxyFONaKpk){xwFLjGSIwe = true;}
      else if(WxyFONaKpk == yOUSNnjCPl){TZHRRgSJOF = true;}
      if(gxPIiXqlzX == juSXnCBmhu){bclcjAbsmk = true;}
      else if(juSXnCBmhu == gxPIiXqlzX){RuyffZEEwJ = true;}
      if(PROCYbimgw == VMFkoPuYZk){PeJjfFnzFx = true;}
      if(oPQhbwmtZp == stqMyAEoTX){mJQFoRMNHL = true;}
      if(RwVKDDeerz == ZjdpKBBdzh){mQcRMfFujF = true;}
      while(VMFkoPuYZk == PROCYbimgw){sHeQmwfKie = true;}
      while(stqMyAEoTX == stqMyAEoTX){kWQbfZjxgU = true;}
      while(ZjdpKBBdzh == ZjdpKBBdzh){POouEjsBwS = true;}
      if(SmTRQKqMQy == true){SmTRQKqMQy = false;}
      if(RBkFrpDFYn == true){RBkFrpDFYn = false;}
      if(xMTKVkhOam == true){xMTKVkhOam = false;}
      if(NRZqRGZYwn == true){NRZqRGZYwn = false;}
      if(IrYUFXyYyU == true){IrYUFXyYyU = false;}
      if(xwFLjGSIwe == true){xwFLjGSIwe = false;}
      if(bclcjAbsmk == true){bclcjAbsmk = false;}
      if(PeJjfFnzFx == true){PeJjfFnzFx = false;}
      if(mJQFoRMNHL == true){mJQFoRMNHL = false;}
      if(mQcRMfFujF == true){mQcRMfFujF = false;}
      if(uEkMESlUfe == true){uEkMESlUfe = false;}
      if(STDyqRLfmS == true){STDyqRLfmS = false;}
      if(mOlbyyBqWz == true){mOlbyyBqWz = false;}
      if(zrOzBhYDBV == true){zrOzBhYDBV = false;}
      if(eqhbrSNdZu == true){eqhbrSNdZu = false;}
      if(TZHRRgSJOF == true){TZHRRgSJOF = false;}
      if(RuyffZEEwJ == true){RuyffZEEwJ = false;}
      if(sHeQmwfKie == true){sHeQmwfKie = false;}
      if(kWQbfZjxgU == true){kWQbfZjxgU = false;}
      if(POouEjsBwS == true){POouEjsBwS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LNBIZSANBQ
{ 
  void dIhfTMznLq()
  { 
      bool PVNIDhVUqz = false;
      bool zGHILMhOSK = false;
      bool usIXNcWsMr = false;
      bool WHtgXotzfN = false;
      bool ZYsuoPYJQO = false;
      bool uCoRPWMouZ = false;
      bool KbHzbqMZkW = false;
      bool RhhEjVANix = false;
      bool DNcyxTSbRA = false;
      bool bEEFDyQtTy = false;
      bool DzXswMUkhs = false;
      bool VzGxVxyJBH = false;
      bool YjHjtNdbBk = false;
      bool EGtktEojCj = false;
      bool zgtYecxHiF = false;
      bool AHrLYSqmyi = false;
      bool iriwoPFVDR = false;
      bool HOHQHqoiFR = false;
      bool PVrukxOhLa = false;
      bool MCkSBHxyjP = false;
      string UhukINVobj;
      string RWGUyVETNO;
      string tdGhHsAYLn;
      string gDdZiuYYqP;
      string VrgGGxNcfE;
      string lUsZwpaNdO;
      string MwdmCOrgkC;
      string wfcyrCxAaK;
      string fXsHCMJEcs;
      string ULubCZNsDr;
      string EgqdHFrtgt;
      string salTioDVjp;
      string EnErhjjAwS;
      string nDxiFzfOzw;
      string UPWhAtZbrM;
      string WrIMnQczwW;
      string UqyOGodDNj;
      string JoVnVnQVrm;
      string KIIiuwtjto;
      string WfRcadRIbK;
      if(UhukINVobj == EgqdHFrtgt){PVNIDhVUqz = true;}
      else if(EgqdHFrtgt == UhukINVobj){DzXswMUkhs = true;}
      if(RWGUyVETNO == salTioDVjp){zGHILMhOSK = true;}
      else if(salTioDVjp == RWGUyVETNO){VzGxVxyJBH = true;}
      if(tdGhHsAYLn == EnErhjjAwS){usIXNcWsMr = true;}
      else if(EnErhjjAwS == tdGhHsAYLn){YjHjtNdbBk = true;}
      if(gDdZiuYYqP == nDxiFzfOzw){WHtgXotzfN = true;}
      else if(nDxiFzfOzw == gDdZiuYYqP){EGtktEojCj = true;}
      if(VrgGGxNcfE == UPWhAtZbrM){ZYsuoPYJQO = true;}
      else if(UPWhAtZbrM == VrgGGxNcfE){zgtYecxHiF = true;}
      if(lUsZwpaNdO == WrIMnQczwW){uCoRPWMouZ = true;}
      else if(WrIMnQczwW == lUsZwpaNdO){AHrLYSqmyi = true;}
      if(MwdmCOrgkC == UqyOGodDNj){KbHzbqMZkW = true;}
      else if(UqyOGodDNj == MwdmCOrgkC){iriwoPFVDR = true;}
      if(wfcyrCxAaK == JoVnVnQVrm){RhhEjVANix = true;}
      if(fXsHCMJEcs == KIIiuwtjto){DNcyxTSbRA = true;}
      if(ULubCZNsDr == WfRcadRIbK){bEEFDyQtTy = true;}
      while(JoVnVnQVrm == wfcyrCxAaK){HOHQHqoiFR = true;}
      while(KIIiuwtjto == KIIiuwtjto){PVrukxOhLa = true;}
      while(WfRcadRIbK == WfRcadRIbK){MCkSBHxyjP = true;}
      if(PVNIDhVUqz == true){PVNIDhVUqz = false;}
      if(zGHILMhOSK == true){zGHILMhOSK = false;}
      if(usIXNcWsMr == true){usIXNcWsMr = false;}
      if(WHtgXotzfN == true){WHtgXotzfN = false;}
      if(ZYsuoPYJQO == true){ZYsuoPYJQO = false;}
      if(uCoRPWMouZ == true){uCoRPWMouZ = false;}
      if(KbHzbqMZkW == true){KbHzbqMZkW = false;}
      if(RhhEjVANix == true){RhhEjVANix = false;}
      if(DNcyxTSbRA == true){DNcyxTSbRA = false;}
      if(bEEFDyQtTy == true){bEEFDyQtTy = false;}
      if(DzXswMUkhs == true){DzXswMUkhs = false;}
      if(VzGxVxyJBH == true){VzGxVxyJBH = false;}
      if(YjHjtNdbBk == true){YjHjtNdbBk = false;}
      if(EGtktEojCj == true){EGtktEojCj = false;}
      if(zgtYecxHiF == true){zgtYecxHiF = false;}
      if(AHrLYSqmyi == true){AHrLYSqmyi = false;}
      if(iriwoPFVDR == true){iriwoPFVDR = false;}
      if(HOHQHqoiFR == true){HOHQHqoiFR = false;}
      if(PVrukxOhLa == true){PVrukxOhLa = false;}
      if(MCkSBHxyjP == true){MCkSBHxyjP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXYEDXYTOL
{ 
  void KjjDFKDzAc()
  { 
      bool HOySbLMIXg = false;
      bool mVOFgRLazo = false;
      bool rqcwdXyrIG = false;
      bool xdulVHbRzf = false;
      bool SPTjTQtQEV = false;
      bool kTgxcQkBnD = false;
      bool NUARiJZcjY = false;
      bool otaSVcXrcN = false;
      bool dhnmVdxyIF = false;
      bool VacuSyPBBK = false;
      bool pQgegprNaA = false;
      bool rrYaZffMwF = false;
      bool LbUeCOQeAW = false;
      bool NWqRWMAJGe = false;
      bool kiWIMdBCVl = false;
      bool SCEwyOwCbR = false;
      bool ZMNEmVBGEM = false;
      bool eWFRTbEMRY = false;
      bool MOJNEKRuTH = false;
      bool PygnFXVSUp = false;
      string YRapDCuOiw;
      string FFJPyCwqsJ;
      string ZSXnsNpSaH;
      string nghVmleIfj;
      string guHgkFfsNE;
      string IcxsWFslxo;
      string LcmaIXXnbL;
      string WmLJceKqCm;
      string hxFVzLjozh;
      string rrLqXDHgXM;
      string hrQBhURmQr;
      string uCjJGOXRax;
      string nintSebUkY;
      string WdSoFpfDne;
      string twXHlpIBjJ;
      string fpFaYyDWhC;
      string rxCrUQitDQ;
      string hTcwCrKgHc;
      string VakarfYqQH;
      string mJVkmwtflV;
      if(YRapDCuOiw == hrQBhURmQr){HOySbLMIXg = true;}
      else if(hrQBhURmQr == YRapDCuOiw){pQgegprNaA = true;}
      if(FFJPyCwqsJ == uCjJGOXRax){mVOFgRLazo = true;}
      else if(uCjJGOXRax == FFJPyCwqsJ){rrYaZffMwF = true;}
      if(ZSXnsNpSaH == nintSebUkY){rqcwdXyrIG = true;}
      else if(nintSebUkY == ZSXnsNpSaH){LbUeCOQeAW = true;}
      if(nghVmleIfj == WdSoFpfDne){xdulVHbRzf = true;}
      else if(WdSoFpfDne == nghVmleIfj){NWqRWMAJGe = true;}
      if(guHgkFfsNE == twXHlpIBjJ){SPTjTQtQEV = true;}
      else if(twXHlpIBjJ == guHgkFfsNE){kiWIMdBCVl = true;}
      if(IcxsWFslxo == fpFaYyDWhC){kTgxcQkBnD = true;}
      else if(fpFaYyDWhC == IcxsWFslxo){SCEwyOwCbR = true;}
      if(LcmaIXXnbL == rxCrUQitDQ){NUARiJZcjY = true;}
      else if(rxCrUQitDQ == LcmaIXXnbL){ZMNEmVBGEM = true;}
      if(WmLJceKqCm == hTcwCrKgHc){otaSVcXrcN = true;}
      if(hxFVzLjozh == VakarfYqQH){dhnmVdxyIF = true;}
      if(rrLqXDHgXM == mJVkmwtflV){VacuSyPBBK = true;}
      while(hTcwCrKgHc == WmLJceKqCm){eWFRTbEMRY = true;}
      while(VakarfYqQH == VakarfYqQH){MOJNEKRuTH = true;}
      while(mJVkmwtflV == mJVkmwtflV){PygnFXVSUp = true;}
      if(HOySbLMIXg == true){HOySbLMIXg = false;}
      if(mVOFgRLazo == true){mVOFgRLazo = false;}
      if(rqcwdXyrIG == true){rqcwdXyrIG = false;}
      if(xdulVHbRzf == true){xdulVHbRzf = false;}
      if(SPTjTQtQEV == true){SPTjTQtQEV = false;}
      if(kTgxcQkBnD == true){kTgxcQkBnD = false;}
      if(NUARiJZcjY == true){NUARiJZcjY = false;}
      if(otaSVcXrcN == true){otaSVcXrcN = false;}
      if(dhnmVdxyIF == true){dhnmVdxyIF = false;}
      if(VacuSyPBBK == true){VacuSyPBBK = false;}
      if(pQgegprNaA == true){pQgegprNaA = false;}
      if(rrYaZffMwF == true){rrYaZffMwF = false;}
      if(LbUeCOQeAW == true){LbUeCOQeAW = false;}
      if(NWqRWMAJGe == true){NWqRWMAJGe = false;}
      if(kiWIMdBCVl == true){kiWIMdBCVl = false;}
      if(SCEwyOwCbR == true){SCEwyOwCbR = false;}
      if(ZMNEmVBGEM == true){ZMNEmVBGEM = false;}
      if(eWFRTbEMRY == true){eWFRTbEMRY = false;}
      if(MOJNEKRuTH == true){MOJNEKRuTH = false;}
      if(PygnFXVSUp == true){PygnFXVSUp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEEBYTZSXU
{ 
  void ZRPoBWNhFS()
  { 
      bool SXECMjUdhI = false;
      bool kSHxKxtSSa = false;
      bool YSTlrEKDUF = false;
      bool RdWmOCSnTT = false;
      bool khyMgtHDRy = false;
      bool NjOxIAERJH = false;
      bool YRJbqGuUhH = false;
      bool eGzzopUGFy = false;
      bool xHlVqgOZdO = false;
      bool xBdMtTYVVZ = false;
      bool ymUJTHkPHS = false;
      bool fxLKJRenkK = false;
      bool rVpTKcbmEV = false;
      bool RykezKlcCj = false;
      bool uzRLiAoTCc = false;
      bool njkKhcwAzp = false;
      bool eyKlAgMgKy = false;
      bool eClAPrDekJ = false;
      bool nIjbggMZxW = false;
      bool OkcLExnfKB = false;
      string rKdWQGmgYZ;
      string QTdzlnetXb;
      string YMImcwiiDZ;
      string tfejtsuWIR;
      string pXbglBHXWR;
      string ITRFpfBqtU;
      string XDdyfkntEr;
      string rHlFkBkbBa;
      string nLLkQZNYsO;
      string rEbnsmscAB;
      string MNSeYAhLUo;
      string tZpSfMqrgF;
      string WPAoznfxMy;
      string HIazOarfMQ;
      string rCEETRNIHg;
      string uBuudwNcej;
      string UjyVglypEF;
      string TLfQNULuUh;
      string ZWpfDGMfVR;
      string MOAbwHDhXh;
      if(rKdWQGmgYZ == MNSeYAhLUo){SXECMjUdhI = true;}
      else if(MNSeYAhLUo == rKdWQGmgYZ){ymUJTHkPHS = true;}
      if(QTdzlnetXb == tZpSfMqrgF){kSHxKxtSSa = true;}
      else if(tZpSfMqrgF == QTdzlnetXb){fxLKJRenkK = true;}
      if(YMImcwiiDZ == WPAoznfxMy){YSTlrEKDUF = true;}
      else if(WPAoznfxMy == YMImcwiiDZ){rVpTKcbmEV = true;}
      if(tfejtsuWIR == HIazOarfMQ){RdWmOCSnTT = true;}
      else if(HIazOarfMQ == tfejtsuWIR){RykezKlcCj = true;}
      if(pXbglBHXWR == rCEETRNIHg){khyMgtHDRy = true;}
      else if(rCEETRNIHg == pXbglBHXWR){uzRLiAoTCc = true;}
      if(ITRFpfBqtU == uBuudwNcej){NjOxIAERJH = true;}
      else if(uBuudwNcej == ITRFpfBqtU){njkKhcwAzp = true;}
      if(XDdyfkntEr == UjyVglypEF){YRJbqGuUhH = true;}
      else if(UjyVglypEF == XDdyfkntEr){eyKlAgMgKy = true;}
      if(rHlFkBkbBa == TLfQNULuUh){eGzzopUGFy = true;}
      if(nLLkQZNYsO == ZWpfDGMfVR){xHlVqgOZdO = true;}
      if(rEbnsmscAB == MOAbwHDhXh){xBdMtTYVVZ = true;}
      while(TLfQNULuUh == rHlFkBkbBa){eClAPrDekJ = true;}
      while(ZWpfDGMfVR == ZWpfDGMfVR){nIjbggMZxW = true;}
      while(MOAbwHDhXh == MOAbwHDhXh){OkcLExnfKB = true;}
      if(SXECMjUdhI == true){SXECMjUdhI = false;}
      if(kSHxKxtSSa == true){kSHxKxtSSa = false;}
      if(YSTlrEKDUF == true){YSTlrEKDUF = false;}
      if(RdWmOCSnTT == true){RdWmOCSnTT = false;}
      if(khyMgtHDRy == true){khyMgtHDRy = false;}
      if(NjOxIAERJH == true){NjOxIAERJH = false;}
      if(YRJbqGuUhH == true){YRJbqGuUhH = false;}
      if(eGzzopUGFy == true){eGzzopUGFy = false;}
      if(xHlVqgOZdO == true){xHlVqgOZdO = false;}
      if(xBdMtTYVVZ == true){xBdMtTYVVZ = false;}
      if(ymUJTHkPHS == true){ymUJTHkPHS = false;}
      if(fxLKJRenkK == true){fxLKJRenkK = false;}
      if(rVpTKcbmEV == true){rVpTKcbmEV = false;}
      if(RykezKlcCj == true){RykezKlcCj = false;}
      if(uzRLiAoTCc == true){uzRLiAoTCc = false;}
      if(njkKhcwAzp == true){njkKhcwAzp = false;}
      if(eyKlAgMgKy == true){eyKlAgMgKy = false;}
      if(eClAPrDekJ == true){eClAPrDekJ = false;}
      if(nIjbggMZxW == true){nIjbggMZxW = false;}
      if(OkcLExnfKB == true){OkcLExnfKB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDPXETBIPX
{ 
  void jByLzDZfNH()
  { 
      bool LdrQgDaDrU = false;
      bool blNqaDXMzJ = false;
      bool UcDMBhmyfw = false;
      bool hxgNSFEpVQ = false;
      bool AUocfstMlX = false;
      bool btTlhhaePz = false;
      bool PbXuldFAYV = false;
      bool zgqhJAnZfH = false;
      bool naMIUndtej = false;
      bool dYaWAXxsqC = false;
      bool mtmQXuDkcg = false;
      bool tAyHKoPOay = false;
      bool zKUoqZFUhk = false;
      bool DtidTsmujY = false;
      bool jsRxpcaSLK = false;
      bool HhSrCcYxYy = false;
      bool oiDqczRTmQ = false;
      bool CTeBOGrWzN = false;
      bool ylIWdVapbq = false;
      bool UoWkiBoaUp = false;
      string nGpbbTXPBW;
      string VzHLPymztw;
      string olqrMhJNhi;
      string focQZPpxTO;
      string VEKGHROdTi;
      string zPXIjCPxPt;
      string KKhSqfWpkz;
      string IpefZkakkt;
      string SftyjPQTgX;
      string ArgYDLWrPa;
      string tYrTaIkrhz;
      string aeLUaeQiha;
      string OCJNyPIFbO;
      string OhUKAtmZXa;
      string eYlgwUfMxY;
      string tmKnLrOeVK;
      string zeQTksJBUg;
      string qqLGwpQcQd;
      string jwHDTbXgyH;
      string fIEMazHSuD;
      if(nGpbbTXPBW == tYrTaIkrhz){LdrQgDaDrU = true;}
      else if(tYrTaIkrhz == nGpbbTXPBW){mtmQXuDkcg = true;}
      if(VzHLPymztw == aeLUaeQiha){blNqaDXMzJ = true;}
      else if(aeLUaeQiha == VzHLPymztw){tAyHKoPOay = true;}
      if(olqrMhJNhi == OCJNyPIFbO){UcDMBhmyfw = true;}
      else if(OCJNyPIFbO == olqrMhJNhi){zKUoqZFUhk = true;}
      if(focQZPpxTO == OhUKAtmZXa){hxgNSFEpVQ = true;}
      else if(OhUKAtmZXa == focQZPpxTO){DtidTsmujY = true;}
      if(VEKGHROdTi == eYlgwUfMxY){AUocfstMlX = true;}
      else if(eYlgwUfMxY == VEKGHROdTi){jsRxpcaSLK = true;}
      if(zPXIjCPxPt == tmKnLrOeVK){btTlhhaePz = true;}
      else if(tmKnLrOeVK == zPXIjCPxPt){HhSrCcYxYy = true;}
      if(KKhSqfWpkz == zeQTksJBUg){PbXuldFAYV = true;}
      else if(zeQTksJBUg == KKhSqfWpkz){oiDqczRTmQ = true;}
      if(IpefZkakkt == qqLGwpQcQd){zgqhJAnZfH = true;}
      if(SftyjPQTgX == jwHDTbXgyH){naMIUndtej = true;}
      if(ArgYDLWrPa == fIEMazHSuD){dYaWAXxsqC = true;}
      while(qqLGwpQcQd == IpefZkakkt){CTeBOGrWzN = true;}
      while(jwHDTbXgyH == jwHDTbXgyH){ylIWdVapbq = true;}
      while(fIEMazHSuD == fIEMazHSuD){UoWkiBoaUp = true;}
      if(LdrQgDaDrU == true){LdrQgDaDrU = false;}
      if(blNqaDXMzJ == true){blNqaDXMzJ = false;}
      if(UcDMBhmyfw == true){UcDMBhmyfw = false;}
      if(hxgNSFEpVQ == true){hxgNSFEpVQ = false;}
      if(AUocfstMlX == true){AUocfstMlX = false;}
      if(btTlhhaePz == true){btTlhhaePz = false;}
      if(PbXuldFAYV == true){PbXuldFAYV = false;}
      if(zgqhJAnZfH == true){zgqhJAnZfH = false;}
      if(naMIUndtej == true){naMIUndtej = false;}
      if(dYaWAXxsqC == true){dYaWAXxsqC = false;}
      if(mtmQXuDkcg == true){mtmQXuDkcg = false;}
      if(tAyHKoPOay == true){tAyHKoPOay = false;}
      if(zKUoqZFUhk == true){zKUoqZFUhk = false;}
      if(DtidTsmujY == true){DtidTsmujY = false;}
      if(jsRxpcaSLK == true){jsRxpcaSLK = false;}
      if(HhSrCcYxYy == true){HhSrCcYxYy = false;}
      if(oiDqczRTmQ == true){oiDqczRTmQ = false;}
      if(CTeBOGrWzN == true){CTeBOGrWzN = false;}
      if(ylIWdVapbq == true){ylIWdVapbq = false;}
      if(UoWkiBoaUp == true){UoWkiBoaUp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZDKBSDVRE
{ 
  void ncysDHDrUD()
  { 
      bool TkKepIXade = false;
      bool fWZDByGSzU = false;
      bool fdLRVJqhYG = false;
      bool sTtmWXgJnL = false;
      bool GZuKERwDHM = false;
      bool BtBXtpZrIg = false;
      bool RoCWlLclgc = false;
      bool QxemNGhAND = false;
      bool MmaLFzRVsg = false;
      bool yoBGtQXXYr = false;
      bool oJWdwDOOJm = false;
      bool HYeETdOpQl = false;
      bool tGszebwYsw = false;
      bool hJbUODQwOB = false;
      bool jDMFZYJwlP = false;
      bool CgHlyiQXzU = false;
      bool HpUNFxxKoQ = false;
      bool NRaOCptmYF = false;
      bool RzlcsBCoVf = false;
      bool mrxttshyAb = false;
      string tbMGlGkjid;
      string lRQcpnbcaJ;
      string hpfElozXxz;
      string iOFAFlZUxQ;
      string WNgEZGDgMV;
      string CFGkODuITw;
      string GMljtXMPXE;
      string NGfJmUJadf;
      string lSLbxcHUlB;
      string pQBAJJaxJC;
      string smJIHuZxxt;
      string sTdnKnBKlR;
      string QrdVNwFeAc;
      string tMRblyJCTB;
      string DJWqHWmMpV;
      string HPLrlBJmuK;
      string puxUzgCBCL;
      string ezqjOGVlNq;
      string JrndUeBYpj;
      string oVHILHMBrZ;
      if(tbMGlGkjid == smJIHuZxxt){TkKepIXade = true;}
      else if(smJIHuZxxt == tbMGlGkjid){oJWdwDOOJm = true;}
      if(lRQcpnbcaJ == sTdnKnBKlR){fWZDByGSzU = true;}
      else if(sTdnKnBKlR == lRQcpnbcaJ){HYeETdOpQl = true;}
      if(hpfElozXxz == QrdVNwFeAc){fdLRVJqhYG = true;}
      else if(QrdVNwFeAc == hpfElozXxz){tGszebwYsw = true;}
      if(iOFAFlZUxQ == tMRblyJCTB){sTtmWXgJnL = true;}
      else if(tMRblyJCTB == iOFAFlZUxQ){hJbUODQwOB = true;}
      if(WNgEZGDgMV == DJWqHWmMpV){GZuKERwDHM = true;}
      else if(DJWqHWmMpV == WNgEZGDgMV){jDMFZYJwlP = true;}
      if(CFGkODuITw == HPLrlBJmuK){BtBXtpZrIg = true;}
      else if(HPLrlBJmuK == CFGkODuITw){CgHlyiQXzU = true;}
      if(GMljtXMPXE == puxUzgCBCL){RoCWlLclgc = true;}
      else if(puxUzgCBCL == GMljtXMPXE){HpUNFxxKoQ = true;}
      if(NGfJmUJadf == ezqjOGVlNq){QxemNGhAND = true;}
      if(lSLbxcHUlB == JrndUeBYpj){MmaLFzRVsg = true;}
      if(pQBAJJaxJC == oVHILHMBrZ){yoBGtQXXYr = true;}
      while(ezqjOGVlNq == NGfJmUJadf){NRaOCptmYF = true;}
      while(JrndUeBYpj == JrndUeBYpj){RzlcsBCoVf = true;}
      while(oVHILHMBrZ == oVHILHMBrZ){mrxttshyAb = true;}
      if(TkKepIXade == true){TkKepIXade = false;}
      if(fWZDByGSzU == true){fWZDByGSzU = false;}
      if(fdLRVJqhYG == true){fdLRVJqhYG = false;}
      if(sTtmWXgJnL == true){sTtmWXgJnL = false;}
      if(GZuKERwDHM == true){GZuKERwDHM = false;}
      if(BtBXtpZrIg == true){BtBXtpZrIg = false;}
      if(RoCWlLclgc == true){RoCWlLclgc = false;}
      if(QxemNGhAND == true){QxemNGhAND = false;}
      if(MmaLFzRVsg == true){MmaLFzRVsg = false;}
      if(yoBGtQXXYr == true){yoBGtQXXYr = false;}
      if(oJWdwDOOJm == true){oJWdwDOOJm = false;}
      if(HYeETdOpQl == true){HYeETdOpQl = false;}
      if(tGszebwYsw == true){tGszebwYsw = false;}
      if(hJbUODQwOB == true){hJbUODQwOB = false;}
      if(jDMFZYJwlP == true){jDMFZYJwlP = false;}
      if(CgHlyiQXzU == true){CgHlyiQXzU = false;}
      if(HpUNFxxKoQ == true){HpUNFxxKoQ = false;}
      if(NRaOCptmYF == true){NRaOCptmYF = false;}
      if(RzlcsBCoVf == true){RzlcsBCoVf = false;}
      if(mrxttshyAb == true){mrxttshyAb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWIXUSPFXX
{ 
  void UnoDsKPOpW()
  { 
      bool RlMbiihjzr = false;
      bool ekUHorNwDN = false;
      bool RbTiiTHmip = false;
      bool ggLtuozzMD = false;
      bool reggFuCFWL = false;
      bool iVDmapSdsO = false;
      bool atAILxZaMA = false;
      bool sNjzVmtmdn = false;
      bool RCQXHLdXSF = false;
      bool VVGycxdYUH = false;
      bool UbsVRUlDRn = false;
      bool uezEwXdbAA = false;
      bool TCIGeXGkWX = false;
      bool JVRVTpJuFm = false;
      bool ZaFdJqVCBE = false;
      bool TBYUnRSlqt = false;
      bool OAgteYNdjG = false;
      bool OhVNZswdxn = false;
      bool BEjRDHxwhC = false;
      bool WWELXYsLzk = false;
      string FLqwCEYIAj;
      string rPzcrbYXro;
      string LdIJUaeicy;
      string OICGVEadPX;
      string tqWemPtduZ;
      string rSiZRaDhbb;
      string YofCUjMrHn;
      string AuIUtTHcVF;
      string gBnCGwYbnt;
      string ArCmyEKTKD;
      string CBVHYxKOfy;
      string TaLVuXBcwY;
      string KjDNmHrUVp;
      string ImSSCefgcI;
      string kKwpZZffra;
      string DhXlrSyITQ;
      string EorpogIsSP;
      string qUzmmzmMmM;
      string bMbulaOfZj;
      string gXMLDwSGBs;
      if(FLqwCEYIAj == CBVHYxKOfy){RlMbiihjzr = true;}
      else if(CBVHYxKOfy == FLqwCEYIAj){UbsVRUlDRn = true;}
      if(rPzcrbYXro == TaLVuXBcwY){ekUHorNwDN = true;}
      else if(TaLVuXBcwY == rPzcrbYXro){uezEwXdbAA = true;}
      if(LdIJUaeicy == KjDNmHrUVp){RbTiiTHmip = true;}
      else if(KjDNmHrUVp == LdIJUaeicy){TCIGeXGkWX = true;}
      if(OICGVEadPX == ImSSCefgcI){ggLtuozzMD = true;}
      else if(ImSSCefgcI == OICGVEadPX){JVRVTpJuFm = true;}
      if(tqWemPtduZ == kKwpZZffra){reggFuCFWL = true;}
      else if(kKwpZZffra == tqWemPtduZ){ZaFdJqVCBE = true;}
      if(rSiZRaDhbb == DhXlrSyITQ){iVDmapSdsO = true;}
      else if(DhXlrSyITQ == rSiZRaDhbb){TBYUnRSlqt = true;}
      if(YofCUjMrHn == EorpogIsSP){atAILxZaMA = true;}
      else if(EorpogIsSP == YofCUjMrHn){OAgteYNdjG = true;}
      if(AuIUtTHcVF == qUzmmzmMmM){sNjzVmtmdn = true;}
      if(gBnCGwYbnt == bMbulaOfZj){RCQXHLdXSF = true;}
      if(ArCmyEKTKD == gXMLDwSGBs){VVGycxdYUH = true;}
      while(qUzmmzmMmM == AuIUtTHcVF){OhVNZswdxn = true;}
      while(bMbulaOfZj == bMbulaOfZj){BEjRDHxwhC = true;}
      while(gXMLDwSGBs == gXMLDwSGBs){WWELXYsLzk = true;}
      if(RlMbiihjzr == true){RlMbiihjzr = false;}
      if(ekUHorNwDN == true){ekUHorNwDN = false;}
      if(RbTiiTHmip == true){RbTiiTHmip = false;}
      if(ggLtuozzMD == true){ggLtuozzMD = false;}
      if(reggFuCFWL == true){reggFuCFWL = false;}
      if(iVDmapSdsO == true){iVDmapSdsO = false;}
      if(atAILxZaMA == true){atAILxZaMA = false;}
      if(sNjzVmtmdn == true){sNjzVmtmdn = false;}
      if(RCQXHLdXSF == true){RCQXHLdXSF = false;}
      if(VVGycxdYUH == true){VVGycxdYUH = false;}
      if(UbsVRUlDRn == true){UbsVRUlDRn = false;}
      if(uezEwXdbAA == true){uezEwXdbAA = false;}
      if(TCIGeXGkWX == true){TCIGeXGkWX = false;}
      if(JVRVTpJuFm == true){JVRVTpJuFm = false;}
      if(ZaFdJqVCBE == true){ZaFdJqVCBE = false;}
      if(TBYUnRSlqt == true){TBYUnRSlqt = false;}
      if(OAgteYNdjG == true){OAgteYNdjG = false;}
      if(OhVNZswdxn == true){OhVNZswdxn = false;}
      if(BEjRDHxwhC == true){BEjRDHxwhC = false;}
      if(WWELXYsLzk == true){WWELXYsLzk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPLTJTDGRR
{ 
  void CizKUHecqP()
  { 
      bool xlfDKyYYJO = false;
      bool bCpfjAFJjX = false;
      bool QiGAErzqKN = false;
      bool gplPtBSrij = false;
      bool dDsgwAZmAd = false;
      bool MEGbSNfezR = false;
      bool zhOuhkPakh = false;
      bool gNZzsMoZEE = false;
      bool SLqfBbiKxf = false;
      bool VmsQkuoyyK = false;
      bool kyCRwyeHhF = false;
      bool YGatzmphtG = false;
      bool BFcELtUINy = false;
      bool XqatSTJYjC = false;
      bool xbbqHPMyRx = false;
      bool FGDrIeVxGC = false;
      bool dVsjhgegbe = false;
      bool dRyqJZclxu = false;
      bool gWpQrRnhkn = false;
      bool yMSgYaiqJZ = false;
      string HPakEIlcyX;
      string kmtDXHLLNB;
      string RBAqzNXkjz;
      string wqTaRfgwyS;
      string bceROSVCsa;
      string RUKrTFPjlp;
      string jBrzasSTlr;
      string ZONtZoWibf;
      string rVrIgagbGL;
      string QxKHhZjfpV;
      string zBPAADHPRe;
      string ifIFxOJiRA;
      string LqNabcEFMz;
      string EpsFgpFqHd;
      string TQJabjoFKS;
      string QANpJInoXX;
      string zBCSaslCYG;
      string ISanfuglyr;
      string nzusiDcDwX;
      string CQSjdRNqzi;
      if(HPakEIlcyX == zBPAADHPRe){xlfDKyYYJO = true;}
      else if(zBPAADHPRe == HPakEIlcyX){kyCRwyeHhF = true;}
      if(kmtDXHLLNB == ifIFxOJiRA){bCpfjAFJjX = true;}
      else if(ifIFxOJiRA == kmtDXHLLNB){YGatzmphtG = true;}
      if(RBAqzNXkjz == LqNabcEFMz){QiGAErzqKN = true;}
      else if(LqNabcEFMz == RBAqzNXkjz){BFcELtUINy = true;}
      if(wqTaRfgwyS == EpsFgpFqHd){gplPtBSrij = true;}
      else if(EpsFgpFqHd == wqTaRfgwyS){XqatSTJYjC = true;}
      if(bceROSVCsa == TQJabjoFKS){dDsgwAZmAd = true;}
      else if(TQJabjoFKS == bceROSVCsa){xbbqHPMyRx = true;}
      if(RUKrTFPjlp == QANpJInoXX){MEGbSNfezR = true;}
      else if(QANpJInoXX == RUKrTFPjlp){FGDrIeVxGC = true;}
      if(jBrzasSTlr == zBCSaslCYG){zhOuhkPakh = true;}
      else if(zBCSaslCYG == jBrzasSTlr){dVsjhgegbe = true;}
      if(ZONtZoWibf == ISanfuglyr){gNZzsMoZEE = true;}
      if(rVrIgagbGL == nzusiDcDwX){SLqfBbiKxf = true;}
      if(QxKHhZjfpV == CQSjdRNqzi){VmsQkuoyyK = true;}
      while(ISanfuglyr == ZONtZoWibf){dRyqJZclxu = true;}
      while(nzusiDcDwX == nzusiDcDwX){gWpQrRnhkn = true;}
      while(CQSjdRNqzi == CQSjdRNqzi){yMSgYaiqJZ = true;}
      if(xlfDKyYYJO == true){xlfDKyYYJO = false;}
      if(bCpfjAFJjX == true){bCpfjAFJjX = false;}
      if(QiGAErzqKN == true){QiGAErzqKN = false;}
      if(gplPtBSrij == true){gplPtBSrij = false;}
      if(dDsgwAZmAd == true){dDsgwAZmAd = false;}
      if(MEGbSNfezR == true){MEGbSNfezR = false;}
      if(zhOuhkPakh == true){zhOuhkPakh = false;}
      if(gNZzsMoZEE == true){gNZzsMoZEE = false;}
      if(SLqfBbiKxf == true){SLqfBbiKxf = false;}
      if(VmsQkuoyyK == true){VmsQkuoyyK = false;}
      if(kyCRwyeHhF == true){kyCRwyeHhF = false;}
      if(YGatzmphtG == true){YGatzmphtG = false;}
      if(BFcELtUINy == true){BFcELtUINy = false;}
      if(XqatSTJYjC == true){XqatSTJYjC = false;}
      if(xbbqHPMyRx == true){xbbqHPMyRx = false;}
      if(FGDrIeVxGC == true){FGDrIeVxGC = false;}
      if(dVsjhgegbe == true){dVsjhgegbe = false;}
      if(dRyqJZclxu == true){dRyqJZclxu = false;}
      if(gWpQrRnhkn == true){gWpQrRnhkn = false;}
      if(yMSgYaiqJZ == true){yMSgYaiqJZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LHIDAHPBPS
{ 
  void VuMAnIzgwe()
  { 
      bool LrjSedEBRg = false;
      bool bqfiufOSVz = false;
      bool hGxNgIwZLJ = false;
      bool DhntolGfTj = false;
      bool nIClczarqq = false;
      bool jtLAVFuVlW = false;
      bool hepHdtCktJ = false;
      bool YiykLZDKjg = false;
      bool gDhUZIWnYj = false;
      bool pksxCISuIi = false;
      bool xpyhRAwZnw = false;
      bool BjkFpdxUhU = false;
      bool WNLJTnoBiC = false;
      bool GICBipFADY = false;
      bool LwAchFzmGY = false;
      bool LxMmLjdnOc = false;
      bool KtqloshjVz = false;
      bool YxRIJaNibN = false;
      bool oCuKpJuOoz = false;
      bool MQkZNRFNnn = false;
      string PdiqDQOUog;
      string gZhKILcmsF;
      string uQUrAZHxTx;
      string usXDgPhLMD;
      string CsGfhbqzPr;
      string jdBEGyIqpc;
      string IQBqlnBdcs;
      string dQZoCCKnKX;
      string iIhaNQqTxi;
      string GpVjukqOts;
      string ZMWWNSELBD;
      string mUgRsAiZdU;
      string whgsmnuptQ;
      string KutQyVkLNt;
      string MfRsulJDpt;
      string CRkZxredjZ;
      string XNRjsraQTW;
      string PXMiIQPnxA;
      string eqzzOsKTSF;
      string pHbmWyNgzD;
      if(PdiqDQOUog == ZMWWNSELBD){LrjSedEBRg = true;}
      else if(ZMWWNSELBD == PdiqDQOUog){xpyhRAwZnw = true;}
      if(gZhKILcmsF == mUgRsAiZdU){bqfiufOSVz = true;}
      else if(mUgRsAiZdU == gZhKILcmsF){BjkFpdxUhU = true;}
      if(uQUrAZHxTx == whgsmnuptQ){hGxNgIwZLJ = true;}
      else if(whgsmnuptQ == uQUrAZHxTx){WNLJTnoBiC = true;}
      if(usXDgPhLMD == KutQyVkLNt){DhntolGfTj = true;}
      else if(KutQyVkLNt == usXDgPhLMD){GICBipFADY = true;}
      if(CsGfhbqzPr == MfRsulJDpt){nIClczarqq = true;}
      else if(MfRsulJDpt == CsGfhbqzPr){LwAchFzmGY = true;}
      if(jdBEGyIqpc == CRkZxredjZ){jtLAVFuVlW = true;}
      else if(CRkZxredjZ == jdBEGyIqpc){LxMmLjdnOc = true;}
      if(IQBqlnBdcs == XNRjsraQTW){hepHdtCktJ = true;}
      else if(XNRjsraQTW == IQBqlnBdcs){KtqloshjVz = true;}
      if(dQZoCCKnKX == PXMiIQPnxA){YiykLZDKjg = true;}
      if(iIhaNQqTxi == eqzzOsKTSF){gDhUZIWnYj = true;}
      if(GpVjukqOts == pHbmWyNgzD){pksxCISuIi = true;}
      while(PXMiIQPnxA == dQZoCCKnKX){YxRIJaNibN = true;}
      while(eqzzOsKTSF == eqzzOsKTSF){oCuKpJuOoz = true;}
      while(pHbmWyNgzD == pHbmWyNgzD){MQkZNRFNnn = true;}
      if(LrjSedEBRg == true){LrjSedEBRg = false;}
      if(bqfiufOSVz == true){bqfiufOSVz = false;}
      if(hGxNgIwZLJ == true){hGxNgIwZLJ = false;}
      if(DhntolGfTj == true){DhntolGfTj = false;}
      if(nIClczarqq == true){nIClczarqq = false;}
      if(jtLAVFuVlW == true){jtLAVFuVlW = false;}
      if(hepHdtCktJ == true){hepHdtCktJ = false;}
      if(YiykLZDKjg == true){YiykLZDKjg = false;}
      if(gDhUZIWnYj == true){gDhUZIWnYj = false;}
      if(pksxCISuIi == true){pksxCISuIi = false;}
      if(xpyhRAwZnw == true){xpyhRAwZnw = false;}
      if(BjkFpdxUhU == true){BjkFpdxUhU = false;}
      if(WNLJTnoBiC == true){WNLJTnoBiC = false;}
      if(GICBipFADY == true){GICBipFADY = false;}
      if(LwAchFzmGY == true){LwAchFzmGY = false;}
      if(LxMmLjdnOc == true){LxMmLjdnOc = false;}
      if(KtqloshjVz == true){KtqloshjVz = false;}
      if(YxRIJaNibN == true){YxRIJaNibN = false;}
      if(oCuKpJuOoz == true){oCuKpJuOoz = false;}
      if(MQkZNRFNnn == true){MQkZNRFNnn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOXOHPBYGV
{ 
  void XfBQDfJBQc()
  { 
      bool LiegZCxasl = false;
      bool BKTaWpgjQE = false;
      bool NesgcIwglS = false;
      bool HuctepUxuY = false;
      bool cGwqlndsuD = false;
      bool QabhDfoyDR = false;
      bool GPoZdFgZwg = false;
      bool VinqaGiCtn = false;
      bool dClhCgTupy = false;
      bool AWsdSNRVMg = false;
      bool HExOhglkGx = false;
      bool xlDPmEcHWx = false;
      bool llixfyoJYN = false;
      bool oMpNgYFXzU = false;
      bool thnsANSdqN = false;
      bool jKyPtVVzii = false;
      bool qcLsHkwpiO = false;
      bool zFHCDDxpxR = false;
      bool fLSKceNaSK = false;
      bool DFnQcRWtkO = false;
      string hLqBSiRVRm;
      string DfHVfZskEQ;
      string JiFQJlNnMW;
      string DwfHxHjrol;
      string zWUUuPGdNT;
      string suYFnzFZrf;
      string UcJuiGAAXY;
      string pAwRRlOkVs;
      string ejasdIXZTy;
      string BJzIQVNYkn;
      string PGFocryGnC;
      string kUDzAkCQRa;
      string iZgZWfBmBu;
      string XozgdYdlPk;
      string JQkQNfFAIf;
      string TxHKEoZfRx;
      string qLFseuUWUb;
      string GQAfQSnPLp;
      string ZAdUbZhocn;
      string yyUStxKrlR;
      if(hLqBSiRVRm == PGFocryGnC){LiegZCxasl = true;}
      else if(PGFocryGnC == hLqBSiRVRm){HExOhglkGx = true;}
      if(DfHVfZskEQ == kUDzAkCQRa){BKTaWpgjQE = true;}
      else if(kUDzAkCQRa == DfHVfZskEQ){xlDPmEcHWx = true;}
      if(JiFQJlNnMW == iZgZWfBmBu){NesgcIwglS = true;}
      else if(iZgZWfBmBu == JiFQJlNnMW){llixfyoJYN = true;}
      if(DwfHxHjrol == XozgdYdlPk){HuctepUxuY = true;}
      else if(XozgdYdlPk == DwfHxHjrol){oMpNgYFXzU = true;}
      if(zWUUuPGdNT == JQkQNfFAIf){cGwqlndsuD = true;}
      else if(JQkQNfFAIf == zWUUuPGdNT){thnsANSdqN = true;}
      if(suYFnzFZrf == TxHKEoZfRx){QabhDfoyDR = true;}
      else if(TxHKEoZfRx == suYFnzFZrf){jKyPtVVzii = true;}
      if(UcJuiGAAXY == qLFseuUWUb){GPoZdFgZwg = true;}
      else if(qLFseuUWUb == UcJuiGAAXY){qcLsHkwpiO = true;}
      if(pAwRRlOkVs == GQAfQSnPLp){VinqaGiCtn = true;}
      if(ejasdIXZTy == ZAdUbZhocn){dClhCgTupy = true;}
      if(BJzIQVNYkn == yyUStxKrlR){AWsdSNRVMg = true;}
      while(GQAfQSnPLp == pAwRRlOkVs){zFHCDDxpxR = true;}
      while(ZAdUbZhocn == ZAdUbZhocn){fLSKceNaSK = true;}
      while(yyUStxKrlR == yyUStxKrlR){DFnQcRWtkO = true;}
      if(LiegZCxasl == true){LiegZCxasl = false;}
      if(BKTaWpgjQE == true){BKTaWpgjQE = false;}
      if(NesgcIwglS == true){NesgcIwglS = false;}
      if(HuctepUxuY == true){HuctepUxuY = false;}
      if(cGwqlndsuD == true){cGwqlndsuD = false;}
      if(QabhDfoyDR == true){QabhDfoyDR = false;}
      if(GPoZdFgZwg == true){GPoZdFgZwg = false;}
      if(VinqaGiCtn == true){VinqaGiCtn = false;}
      if(dClhCgTupy == true){dClhCgTupy = false;}
      if(AWsdSNRVMg == true){AWsdSNRVMg = false;}
      if(HExOhglkGx == true){HExOhglkGx = false;}
      if(xlDPmEcHWx == true){xlDPmEcHWx = false;}
      if(llixfyoJYN == true){llixfyoJYN = false;}
      if(oMpNgYFXzU == true){oMpNgYFXzU = false;}
      if(thnsANSdqN == true){thnsANSdqN = false;}
      if(jKyPtVVzii == true){jKyPtVVzii = false;}
      if(qcLsHkwpiO == true){qcLsHkwpiO = false;}
      if(zFHCDDxpxR == true){zFHCDDxpxR = false;}
      if(fLSKceNaSK == true){fLSKceNaSK = false;}
      if(DFnQcRWtkO == true){DFnQcRWtkO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNXSMZPKFY
{ 
  void jzjHrIyPqo()
  { 
      bool HoTWmtIOoi = false;
      bool kiRljjJOFV = false;
      bool OXYDJRMZXF = false;
      bool LKxIQLLnfg = false;
      bool xieHFrKqls = false;
      bool kkxRJiPQMV = false;
      bool hhpjWZkJUX = false;
      bool XUiXYerRxR = false;
      bool HUndUZNfyg = false;
      bool wuaJzOsujf = false;
      bool HAVNVPCYrd = false;
      bool pySuOMtLPx = false;
      bool LEKnbctZXK = false;
      bool kxhRKGzZIE = false;
      bool WomTpxbftm = false;
      bool ThflTCphlr = false;
      bool VcAhssQBjI = false;
      bool NUCKZWRpxe = false;
      bool ANekpDRuxI = false;
      bool PQnQhtnFax = false;
      string wJPVqqYCPJ;
      string WVHqztLqNj;
      string asnkDrgbAL;
      string rGwEOYiRlL;
      string KJQWITZqIB;
      string FqmTCDUdSy;
      string JwBDQQYDca;
      string KtFCZRbQci;
      string RoTyGBTcBL;
      string DFymBNHNGq;
      string tWOgqLljsk;
      string aDAifTcDwP;
      string wwBQXFuRBM;
      string JOKkouZmHt;
      string OjiPjzEOHg;
      string jEQpuyUyJk;
      string QTigbMrOtj;
      string spuCAMMlfX;
      string BfKTbFxUpq;
      string abcVduACnX;
      if(wJPVqqYCPJ == tWOgqLljsk){HoTWmtIOoi = true;}
      else if(tWOgqLljsk == wJPVqqYCPJ){HAVNVPCYrd = true;}
      if(WVHqztLqNj == aDAifTcDwP){kiRljjJOFV = true;}
      else if(aDAifTcDwP == WVHqztLqNj){pySuOMtLPx = true;}
      if(asnkDrgbAL == wwBQXFuRBM){OXYDJRMZXF = true;}
      else if(wwBQXFuRBM == asnkDrgbAL){LEKnbctZXK = true;}
      if(rGwEOYiRlL == JOKkouZmHt){LKxIQLLnfg = true;}
      else if(JOKkouZmHt == rGwEOYiRlL){kxhRKGzZIE = true;}
      if(KJQWITZqIB == OjiPjzEOHg){xieHFrKqls = true;}
      else if(OjiPjzEOHg == KJQWITZqIB){WomTpxbftm = true;}
      if(FqmTCDUdSy == jEQpuyUyJk){kkxRJiPQMV = true;}
      else if(jEQpuyUyJk == FqmTCDUdSy){ThflTCphlr = true;}
      if(JwBDQQYDca == QTigbMrOtj){hhpjWZkJUX = true;}
      else if(QTigbMrOtj == JwBDQQYDca){VcAhssQBjI = true;}
      if(KtFCZRbQci == spuCAMMlfX){XUiXYerRxR = true;}
      if(RoTyGBTcBL == BfKTbFxUpq){HUndUZNfyg = true;}
      if(DFymBNHNGq == abcVduACnX){wuaJzOsujf = true;}
      while(spuCAMMlfX == KtFCZRbQci){NUCKZWRpxe = true;}
      while(BfKTbFxUpq == BfKTbFxUpq){ANekpDRuxI = true;}
      while(abcVduACnX == abcVduACnX){PQnQhtnFax = true;}
      if(HoTWmtIOoi == true){HoTWmtIOoi = false;}
      if(kiRljjJOFV == true){kiRljjJOFV = false;}
      if(OXYDJRMZXF == true){OXYDJRMZXF = false;}
      if(LKxIQLLnfg == true){LKxIQLLnfg = false;}
      if(xieHFrKqls == true){xieHFrKqls = false;}
      if(kkxRJiPQMV == true){kkxRJiPQMV = false;}
      if(hhpjWZkJUX == true){hhpjWZkJUX = false;}
      if(XUiXYerRxR == true){XUiXYerRxR = false;}
      if(HUndUZNfyg == true){HUndUZNfyg = false;}
      if(wuaJzOsujf == true){wuaJzOsujf = false;}
      if(HAVNVPCYrd == true){HAVNVPCYrd = false;}
      if(pySuOMtLPx == true){pySuOMtLPx = false;}
      if(LEKnbctZXK == true){LEKnbctZXK = false;}
      if(kxhRKGzZIE == true){kxhRKGzZIE = false;}
      if(WomTpxbftm == true){WomTpxbftm = false;}
      if(ThflTCphlr == true){ThflTCphlr = false;}
      if(VcAhssQBjI == true){VcAhssQBjI = false;}
      if(NUCKZWRpxe == true){NUCKZWRpxe = false;}
      if(ANekpDRuxI == true){ANekpDRuxI = false;}
      if(PQnQhtnFax == true){PQnQhtnFax = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYIMNBAYHI
{ 
  void GKdquFrjbg()
  { 
      bool nwxoIlMYgl = false;
      bool KohbrjmhXN = false;
      bool SDqGQwWLRo = false;
      bool cFeCSThyON = false;
      bool OzKwJFsEdV = false;
      bool LBOBQkEpYM = false;
      bool OAGqJEKfJY = false;
      bool CnSJySsuwL = false;
      bool DRgwdaqckg = false;
      bool OqZByNsSmF = false;
      bool tMuFSWhECy = false;
      bool rJsMJxSKNh = false;
      bool MgtcJKORKk = false;
      bool ZaHqQpWbcG = false;
      bool rlamnFyMrB = false;
      bool tiEErMRRuI = false;
      bool IQsRXRBBuS = false;
      bool ZqgHpZGHnE = false;
      bool MCYJpqVDzD = false;
      bool XEgUxarIOW = false;
      string JxPgBSIYJs;
      string FOKSigPXDT;
      string XiobIBSykc;
      string nImAOAQsqz;
      string TtXpwgqmIL;
      string oxLOmZHmYz;
      string zJmgFxbKDi;
      string PWgDAcLzfb;
      string KfpZmpwYNo;
      string rdTqAJHpkz;
      string FfiZuRQINJ;
      string NIGwoTTMsO;
      string ACxOplCoDp;
      string VVNgVdwPeV;
      string ZnKDbiWXBf;
      string ptwVyCiUiI;
      string PaEXnqtZZL;
      string XDhXnMrslG;
      string PenWAaYqhT;
      string tagWFzilOj;
      if(JxPgBSIYJs == FfiZuRQINJ){nwxoIlMYgl = true;}
      else if(FfiZuRQINJ == JxPgBSIYJs){tMuFSWhECy = true;}
      if(FOKSigPXDT == NIGwoTTMsO){KohbrjmhXN = true;}
      else if(NIGwoTTMsO == FOKSigPXDT){rJsMJxSKNh = true;}
      if(XiobIBSykc == ACxOplCoDp){SDqGQwWLRo = true;}
      else if(ACxOplCoDp == XiobIBSykc){MgtcJKORKk = true;}
      if(nImAOAQsqz == VVNgVdwPeV){cFeCSThyON = true;}
      else if(VVNgVdwPeV == nImAOAQsqz){ZaHqQpWbcG = true;}
      if(TtXpwgqmIL == ZnKDbiWXBf){OzKwJFsEdV = true;}
      else if(ZnKDbiWXBf == TtXpwgqmIL){rlamnFyMrB = true;}
      if(oxLOmZHmYz == ptwVyCiUiI){LBOBQkEpYM = true;}
      else if(ptwVyCiUiI == oxLOmZHmYz){tiEErMRRuI = true;}
      if(zJmgFxbKDi == PaEXnqtZZL){OAGqJEKfJY = true;}
      else if(PaEXnqtZZL == zJmgFxbKDi){IQsRXRBBuS = true;}
      if(PWgDAcLzfb == XDhXnMrslG){CnSJySsuwL = true;}
      if(KfpZmpwYNo == PenWAaYqhT){DRgwdaqckg = true;}
      if(rdTqAJHpkz == tagWFzilOj){OqZByNsSmF = true;}
      while(XDhXnMrslG == PWgDAcLzfb){ZqgHpZGHnE = true;}
      while(PenWAaYqhT == PenWAaYqhT){MCYJpqVDzD = true;}
      while(tagWFzilOj == tagWFzilOj){XEgUxarIOW = true;}
      if(nwxoIlMYgl == true){nwxoIlMYgl = false;}
      if(KohbrjmhXN == true){KohbrjmhXN = false;}
      if(SDqGQwWLRo == true){SDqGQwWLRo = false;}
      if(cFeCSThyON == true){cFeCSThyON = false;}
      if(OzKwJFsEdV == true){OzKwJFsEdV = false;}
      if(LBOBQkEpYM == true){LBOBQkEpYM = false;}
      if(OAGqJEKfJY == true){OAGqJEKfJY = false;}
      if(CnSJySsuwL == true){CnSJySsuwL = false;}
      if(DRgwdaqckg == true){DRgwdaqckg = false;}
      if(OqZByNsSmF == true){OqZByNsSmF = false;}
      if(tMuFSWhECy == true){tMuFSWhECy = false;}
      if(rJsMJxSKNh == true){rJsMJxSKNh = false;}
      if(MgtcJKORKk == true){MgtcJKORKk = false;}
      if(ZaHqQpWbcG == true){ZaHqQpWbcG = false;}
      if(rlamnFyMrB == true){rlamnFyMrB = false;}
      if(tiEErMRRuI == true){tiEErMRRuI = false;}
      if(IQsRXRBBuS == true){IQsRXRBBuS = false;}
      if(ZqgHpZGHnE == true){ZqgHpZGHnE = false;}
      if(MCYJpqVDzD == true){MCYJpqVDzD = false;}
      if(XEgUxarIOW == true){XEgUxarIOW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSMWDWHDRU
{ 
  void XiQLxfyRhF()
  { 
      bool FlqlrKbzJT = false;
      bool mAENBNsVyS = false;
      bool nkGSsgiXjs = false;
      bool TVRWkCWAzA = false;
      bool ILgCiqmLSM = false;
      bool ZLoumTeYrK = false;
      bool aDOQAQhhbz = false;
      bool psVyJbEEiC = false;
      bool sWEXTHgWjR = false;
      bool WyInZFwPCS = false;
      bool IFjTVgpqkK = false;
      bool PaooRDzqxr = false;
      bool jKxKbqjgXE = false;
      bool enBQtnmkBl = false;
      bool RokZBuJTWW = false;
      bool GFSKixHYqe = false;
      bool wISgebZXuc = false;
      bool PNoKZtZXIf = false;
      bool hPJByZVqhw = false;
      bool fNsWpIVEtZ = false;
      string ERfIMEXsMS;
      string wHjUFHCbUm;
      string IuewaDOdkc;
      string RgMLDJTUna;
      string AfFiiBBsXg;
      string DcPZlJlihJ;
      string psHjAPuXRu;
      string ngmslcowMZ;
      string BVGEYnRlZt;
      string XjmekHXUhT;
      string GdabsWoVnI;
      string TpVHHTmDLL;
      string xIxXXDtIIe;
      string FTNsTWudKC;
      string zuyRZgOeWQ;
      string TUIWWxfCEp;
      string bfNJDzbcnk;
      string YJrJMCKfxp;
      string nOlqKkLqWV;
      string qrZUZShnNa;
      if(ERfIMEXsMS == GdabsWoVnI){FlqlrKbzJT = true;}
      else if(GdabsWoVnI == ERfIMEXsMS){IFjTVgpqkK = true;}
      if(wHjUFHCbUm == TpVHHTmDLL){mAENBNsVyS = true;}
      else if(TpVHHTmDLL == wHjUFHCbUm){PaooRDzqxr = true;}
      if(IuewaDOdkc == xIxXXDtIIe){nkGSsgiXjs = true;}
      else if(xIxXXDtIIe == IuewaDOdkc){jKxKbqjgXE = true;}
      if(RgMLDJTUna == FTNsTWudKC){TVRWkCWAzA = true;}
      else if(FTNsTWudKC == RgMLDJTUna){enBQtnmkBl = true;}
      if(AfFiiBBsXg == zuyRZgOeWQ){ILgCiqmLSM = true;}
      else if(zuyRZgOeWQ == AfFiiBBsXg){RokZBuJTWW = true;}
      if(DcPZlJlihJ == TUIWWxfCEp){ZLoumTeYrK = true;}
      else if(TUIWWxfCEp == DcPZlJlihJ){GFSKixHYqe = true;}
      if(psHjAPuXRu == bfNJDzbcnk){aDOQAQhhbz = true;}
      else if(bfNJDzbcnk == psHjAPuXRu){wISgebZXuc = true;}
      if(ngmslcowMZ == YJrJMCKfxp){psVyJbEEiC = true;}
      if(BVGEYnRlZt == nOlqKkLqWV){sWEXTHgWjR = true;}
      if(XjmekHXUhT == qrZUZShnNa){WyInZFwPCS = true;}
      while(YJrJMCKfxp == ngmslcowMZ){PNoKZtZXIf = true;}
      while(nOlqKkLqWV == nOlqKkLqWV){hPJByZVqhw = true;}
      while(qrZUZShnNa == qrZUZShnNa){fNsWpIVEtZ = true;}
      if(FlqlrKbzJT == true){FlqlrKbzJT = false;}
      if(mAENBNsVyS == true){mAENBNsVyS = false;}
      if(nkGSsgiXjs == true){nkGSsgiXjs = false;}
      if(TVRWkCWAzA == true){TVRWkCWAzA = false;}
      if(ILgCiqmLSM == true){ILgCiqmLSM = false;}
      if(ZLoumTeYrK == true){ZLoumTeYrK = false;}
      if(aDOQAQhhbz == true){aDOQAQhhbz = false;}
      if(psVyJbEEiC == true){psVyJbEEiC = false;}
      if(sWEXTHgWjR == true){sWEXTHgWjR = false;}
      if(WyInZFwPCS == true){WyInZFwPCS = false;}
      if(IFjTVgpqkK == true){IFjTVgpqkK = false;}
      if(PaooRDzqxr == true){PaooRDzqxr = false;}
      if(jKxKbqjgXE == true){jKxKbqjgXE = false;}
      if(enBQtnmkBl == true){enBQtnmkBl = false;}
      if(RokZBuJTWW == true){RokZBuJTWW = false;}
      if(GFSKixHYqe == true){GFSKixHYqe = false;}
      if(wISgebZXuc == true){wISgebZXuc = false;}
      if(PNoKZtZXIf == true){PNoKZtZXIf = false;}
      if(hPJByZVqhw == true){hPJByZVqhw = false;}
      if(fNsWpIVEtZ == true){fNsWpIVEtZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZLVFOLYMD
{ 
  void UxqmcgLmuD()
  { 
      bool WtmYHVlCER = false;
      bool AGTOwbcXph = false;
      bool qLxixBoTun = false;
      bool ARtsUMpGJn = false;
      bool CGYjRbgXcJ = false;
      bool QgqJfLwDbG = false;
      bool gSHQQhMati = false;
      bool kWOCejmNRU = false;
      bool TQplWTakMI = false;
      bool PmdDGjzHSi = false;
      bool PGdsXtRodu = false;
      bool XhkGmQbUsx = false;
      bool GaNkTyrLuu = false;
      bool keuhENlxNc = false;
      bool BlHRkhBXPo = false;
      bool IdNUbosrZY = false;
      bool BGshKsmDBZ = false;
      bool ddHQuUTuAl = false;
      bool wUuGmGQZFP = false;
      bool TtXnatrYHq = false;
      string jzHVIVRuuf;
      string SFWIoFtzLc;
      string MsBkEadoxI;
      string uDfOGQnWxn;
      string yusKmGCXiT;
      string twpnIqxVQg;
      string rcxlkOYHBX;
      string RXBXeRzqxy;
      string XGFdNyNqFO;
      string SRGPwVyHZY;
      string guVLCWuRJq;
      string rGXRJlWTXl;
      string BgBmEzRlbI;
      string TrQYQcjtaq;
      string DuhOWMsnGJ;
      string yeimXzsiGC;
      string FIpAWAozBg;
      string BbrgiFzlPq;
      string GcfRKoIdBR;
      string iAmYktFgqW;
      if(jzHVIVRuuf == guVLCWuRJq){WtmYHVlCER = true;}
      else if(guVLCWuRJq == jzHVIVRuuf){PGdsXtRodu = true;}
      if(SFWIoFtzLc == rGXRJlWTXl){AGTOwbcXph = true;}
      else if(rGXRJlWTXl == SFWIoFtzLc){XhkGmQbUsx = true;}
      if(MsBkEadoxI == BgBmEzRlbI){qLxixBoTun = true;}
      else if(BgBmEzRlbI == MsBkEadoxI){GaNkTyrLuu = true;}
      if(uDfOGQnWxn == TrQYQcjtaq){ARtsUMpGJn = true;}
      else if(TrQYQcjtaq == uDfOGQnWxn){keuhENlxNc = true;}
      if(yusKmGCXiT == DuhOWMsnGJ){CGYjRbgXcJ = true;}
      else if(DuhOWMsnGJ == yusKmGCXiT){BlHRkhBXPo = true;}
      if(twpnIqxVQg == yeimXzsiGC){QgqJfLwDbG = true;}
      else if(yeimXzsiGC == twpnIqxVQg){IdNUbosrZY = true;}
      if(rcxlkOYHBX == FIpAWAozBg){gSHQQhMati = true;}
      else if(FIpAWAozBg == rcxlkOYHBX){BGshKsmDBZ = true;}
      if(RXBXeRzqxy == BbrgiFzlPq){kWOCejmNRU = true;}
      if(XGFdNyNqFO == GcfRKoIdBR){TQplWTakMI = true;}
      if(SRGPwVyHZY == iAmYktFgqW){PmdDGjzHSi = true;}
      while(BbrgiFzlPq == RXBXeRzqxy){ddHQuUTuAl = true;}
      while(GcfRKoIdBR == GcfRKoIdBR){wUuGmGQZFP = true;}
      while(iAmYktFgqW == iAmYktFgqW){TtXnatrYHq = true;}
      if(WtmYHVlCER == true){WtmYHVlCER = false;}
      if(AGTOwbcXph == true){AGTOwbcXph = false;}
      if(qLxixBoTun == true){qLxixBoTun = false;}
      if(ARtsUMpGJn == true){ARtsUMpGJn = false;}
      if(CGYjRbgXcJ == true){CGYjRbgXcJ = false;}
      if(QgqJfLwDbG == true){QgqJfLwDbG = false;}
      if(gSHQQhMati == true){gSHQQhMati = false;}
      if(kWOCejmNRU == true){kWOCejmNRU = false;}
      if(TQplWTakMI == true){TQplWTakMI = false;}
      if(PmdDGjzHSi == true){PmdDGjzHSi = false;}
      if(PGdsXtRodu == true){PGdsXtRodu = false;}
      if(XhkGmQbUsx == true){XhkGmQbUsx = false;}
      if(GaNkTyrLuu == true){GaNkTyrLuu = false;}
      if(keuhENlxNc == true){keuhENlxNc = false;}
      if(BlHRkhBXPo == true){BlHRkhBXPo = false;}
      if(IdNUbosrZY == true){IdNUbosrZY = false;}
      if(BGshKsmDBZ == true){BGshKsmDBZ = false;}
      if(ddHQuUTuAl == true){ddHQuUTuAl = false;}
      if(wUuGmGQZFP == true){wUuGmGQZFP = false;}
      if(TtXnatrYHq == true){TtXnatrYHq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGYHASJKWL
{ 
  void eJXoeiVXBJ()
  { 
      bool rtrBFMJCsU = false;
      bool RhqbcVZJZR = false;
      bool VNKBAOLNTF = false;
      bool DxmQgODaKN = false;
      bool ySbKXrKxTG = false;
      bool BtLCgeipBp = false;
      bool BuinQUtZuN = false;
      bool RzyMTClAcI = false;
      bool EOsNDJkkjC = false;
      bool fNYTLCjmtD = false;
      bool xjBGnCwzid = false;
      bool siMsllBUjH = false;
      bool iJpsgEZdAQ = false;
      bool RyGZKTNmYB = false;
      bool NlBFJxAfhZ = false;
      bool APDmTmtHYi = false;
      bool cRySLtcmhS = false;
      bool YOuitxIjjj = false;
      bool EswaQCtTFX = false;
      bool ZFNoYumisO = false;
      string HidTjFfdOU;
      string SGYHZdLkFm;
      string GhVLWnmnWi;
      string UpWfiTBONS;
      string CTVmpHizJI;
      string rfzJmZNSxu;
      string SqHfAbisXG;
      string cwXmjmLiUO;
      string FndOpnpMrI;
      string FhRRALMpmN;
      string XpaCfwIMZz;
      string NexhpdMrpM;
      string kWAOAteFlY;
      string aVuHqPNahs;
      string edmsuajibV;
      string yTzabBoLBl;
      string RDZAYripqZ;
      string QkKwgHiHTY;
      string JucQZHVUeo;
      string ZBZwbbDlTC;
      if(HidTjFfdOU == XpaCfwIMZz){rtrBFMJCsU = true;}
      else if(XpaCfwIMZz == HidTjFfdOU){xjBGnCwzid = true;}
      if(SGYHZdLkFm == NexhpdMrpM){RhqbcVZJZR = true;}
      else if(NexhpdMrpM == SGYHZdLkFm){siMsllBUjH = true;}
      if(GhVLWnmnWi == kWAOAteFlY){VNKBAOLNTF = true;}
      else if(kWAOAteFlY == GhVLWnmnWi){iJpsgEZdAQ = true;}
      if(UpWfiTBONS == aVuHqPNahs){DxmQgODaKN = true;}
      else if(aVuHqPNahs == UpWfiTBONS){RyGZKTNmYB = true;}
      if(CTVmpHizJI == edmsuajibV){ySbKXrKxTG = true;}
      else if(edmsuajibV == CTVmpHizJI){NlBFJxAfhZ = true;}
      if(rfzJmZNSxu == yTzabBoLBl){BtLCgeipBp = true;}
      else if(yTzabBoLBl == rfzJmZNSxu){APDmTmtHYi = true;}
      if(SqHfAbisXG == RDZAYripqZ){BuinQUtZuN = true;}
      else if(RDZAYripqZ == SqHfAbisXG){cRySLtcmhS = true;}
      if(cwXmjmLiUO == QkKwgHiHTY){RzyMTClAcI = true;}
      if(FndOpnpMrI == JucQZHVUeo){EOsNDJkkjC = true;}
      if(FhRRALMpmN == ZBZwbbDlTC){fNYTLCjmtD = true;}
      while(QkKwgHiHTY == cwXmjmLiUO){YOuitxIjjj = true;}
      while(JucQZHVUeo == JucQZHVUeo){EswaQCtTFX = true;}
      while(ZBZwbbDlTC == ZBZwbbDlTC){ZFNoYumisO = true;}
      if(rtrBFMJCsU == true){rtrBFMJCsU = false;}
      if(RhqbcVZJZR == true){RhqbcVZJZR = false;}
      if(VNKBAOLNTF == true){VNKBAOLNTF = false;}
      if(DxmQgODaKN == true){DxmQgODaKN = false;}
      if(ySbKXrKxTG == true){ySbKXrKxTG = false;}
      if(BtLCgeipBp == true){BtLCgeipBp = false;}
      if(BuinQUtZuN == true){BuinQUtZuN = false;}
      if(RzyMTClAcI == true){RzyMTClAcI = false;}
      if(EOsNDJkkjC == true){EOsNDJkkjC = false;}
      if(fNYTLCjmtD == true){fNYTLCjmtD = false;}
      if(xjBGnCwzid == true){xjBGnCwzid = false;}
      if(siMsllBUjH == true){siMsllBUjH = false;}
      if(iJpsgEZdAQ == true){iJpsgEZdAQ = false;}
      if(RyGZKTNmYB == true){RyGZKTNmYB = false;}
      if(NlBFJxAfhZ == true){NlBFJxAfhZ = false;}
      if(APDmTmtHYi == true){APDmTmtHYi = false;}
      if(cRySLtcmhS == true){cRySLtcmhS = false;}
      if(YOuitxIjjj == true){YOuitxIjjj = false;}
      if(EswaQCtTFX == true){EswaQCtTFX = false;}
      if(ZFNoYumisO == true){ZFNoYumisO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DGAQNEVUBN
{ 
  void jVzgQoktXV()
  { 
      bool VcXaYZKLgT = false;
      bool ulLekiBkDf = false;
      bool JLNjwkSEyN = false;
      bool RnjwWZdCZz = false;
      bool UjQDDOZDrO = false;
      bool OnUKGKPmdn = false;
      bool GFMSCHCOIL = false;
      bool EzLDLZuJfh = false;
      bool LOMiycTZoL = false;
      bool JpXkrOWxBw = false;
      bool MKufJPcQyg = false;
      bool PFHwcrscUY = false;
      bool mbYwBOaZLx = false;
      bool CxIjUASfZh = false;
      bool ADbIwDibIA = false;
      bool UtbbJjlzdu = false;
      bool nCEAeRwXab = false;
      bool YMDlYiAPzx = false;
      bool ezRKbIVgZk = false;
      bool NTBdtxyade = false;
      string zrGPdhhtCs;
      string Zmzqcngnsj;
      string exgtsLkUXn;
      string rltjeHrWCX;
      string yOElAOGTQA;
      string GQyPyBLMWR;
      string xMWOBnrOMU;
      string wKkUkPsttd;
      string FRDWgamekc;
      string wfAjakrpkL;
      string VqHwEweddi;
      string HRRrMfJAgZ;
      string ANdiXQKAsA;
      string WDIhHOJHRj;
      string uJBCUeNHXu;
      string brILKINYXn;
      string ldjcLEIjjx;
      string VBhxdqMaNs;
      string CCcyYeuxWz;
      string BkicyQZXqQ;
      if(zrGPdhhtCs == VqHwEweddi){VcXaYZKLgT = true;}
      else if(VqHwEweddi == zrGPdhhtCs){MKufJPcQyg = true;}
      if(Zmzqcngnsj == HRRrMfJAgZ){ulLekiBkDf = true;}
      else if(HRRrMfJAgZ == Zmzqcngnsj){PFHwcrscUY = true;}
      if(exgtsLkUXn == ANdiXQKAsA){JLNjwkSEyN = true;}
      else if(ANdiXQKAsA == exgtsLkUXn){mbYwBOaZLx = true;}
      if(rltjeHrWCX == WDIhHOJHRj){RnjwWZdCZz = true;}
      else if(WDIhHOJHRj == rltjeHrWCX){CxIjUASfZh = true;}
      if(yOElAOGTQA == uJBCUeNHXu){UjQDDOZDrO = true;}
      else if(uJBCUeNHXu == yOElAOGTQA){ADbIwDibIA = true;}
      if(GQyPyBLMWR == brILKINYXn){OnUKGKPmdn = true;}
      else if(brILKINYXn == GQyPyBLMWR){UtbbJjlzdu = true;}
      if(xMWOBnrOMU == ldjcLEIjjx){GFMSCHCOIL = true;}
      else if(ldjcLEIjjx == xMWOBnrOMU){nCEAeRwXab = true;}
      if(wKkUkPsttd == VBhxdqMaNs){EzLDLZuJfh = true;}
      if(FRDWgamekc == CCcyYeuxWz){LOMiycTZoL = true;}
      if(wfAjakrpkL == BkicyQZXqQ){JpXkrOWxBw = true;}
      while(VBhxdqMaNs == wKkUkPsttd){YMDlYiAPzx = true;}
      while(CCcyYeuxWz == CCcyYeuxWz){ezRKbIVgZk = true;}
      while(BkicyQZXqQ == BkicyQZXqQ){NTBdtxyade = true;}
      if(VcXaYZKLgT == true){VcXaYZKLgT = false;}
      if(ulLekiBkDf == true){ulLekiBkDf = false;}
      if(JLNjwkSEyN == true){JLNjwkSEyN = false;}
      if(RnjwWZdCZz == true){RnjwWZdCZz = false;}
      if(UjQDDOZDrO == true){UjQDDOZDrO = false;}
      if(OnUKGKPmdn == true){OnUKGKPmdn = false;}
      if(GFMSCHCOIL == true){GFMSCHCOIL = false;}
      if(EzLDLZuJfh == true){EzLDLZuJfh = false;}
      if(LOMiycTZoL == true){LOMiycTZoL = false;}
      if(JpXkrOWxBw == true){JpXkrOWxBw = false;}
      if(MKufJPcQyg == true){MKufJPcQyg = false;}
      if(PFHwcrscUY == true){PFHwcrscUY = false;}
      if(mbYwBOaZLx == true){mbYwBOaZLx = false;}
      if(CxIjUASfZh == true){CxIjUASfZh = false;}
      if(ADbIwDibIA == true){ADbIwDibIA = false;}
      if(UtbbJjlzdu == true){UtbbJjlzdu = false;}
      if(nCEAeRwXab == true){nCEAeRwXab = false;}
      if(YMDlYiAPzx == true){YMDlYiAPzx = false;}
      if(ezRKbIVgZk == true){ezRKbIVgZk = false;}
      if(NTBdtxyade == true){NTBdtxyade = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJLMGEFSEE
{ 
  void kEKjUOuykk()
  { 
      bool PJwajEbfHk = false;
      bool EIkuxMXEuk = false;
      bool pfSdVxbIVV = false;
      bool mPLXEELaiR = false;
      bool MQwJQYnXDy = false;
      bool DxpmWipSFl = false;
      bool cTJkyoxMqr = false;
      bool AwVcXYiJNw = false;
      bool JDEXRpZXAU = false;
      bool NrUwnsHLKa = false;
      bool bagKxGaMPy = false;
      bool zgFJcYOkSI = false;
      bool PYMVdHbYod = false;
      bool RXylUhWsZK = false;
      bool OMICVgmLSP = false;
      bool dVrCLCOKgp = false;
      bool eBXkfahTnt = false;
      bool BULHsCQJzw = false;
      bool UQGYAufuZS = false;
      bool TMMjfMoWVt = false;
      string HfjOpBTnaN;
      string BhMHSBPgid;
      string SbXmzKkUHI;
      string GPieaCFmpm;
      string cmrKbKIkBu;
      string CyspfeHwPf;
      string PygSHkygfP;
      string wbqwBfiNLn;
      string BzTLFIWsyu;
      string uIWJWdFZDp;
      string LaFkzZHxoA;
      string wtjadQdUMy;
      string OFhjUmEgYW;
      string ZJJVbatiMf;
      string BZDyzAXweG;
      string zkMEaGrUPL;
      string UZXRZlkOzD;
      string VuIgxoBjjT;
      string OICSWowEuV;
      string hYSAKaBkXM;
      if(HfjOpBTnaN == LaFkzZHxoA){PJwajEbfHk = true;}
      else if(LaFkzZHxoA == HfjOpBTnaN){bagKxGaMPy = true;}
      if(BhMHSBPgid == wtjadQdUMy){EIkuxMXEuk = true;}
      else if(wtjadQdUMy == BhMHSBPgid){zgFJcYOkSI = true;}
      if(SbXmzKkUHI == OFhjUmEgYW){pfSdVxbIVV = true;}
      else if(OFhjUmEgYW == SbXmzKkUHI){PYMVdHbYod = true;}
      if(GPieaCFmpm == ZJJVbatiMf){mPLXEELaiR = true;}
      else if(ZJJVbatiMf == GPieaCFmpm){RXylUhWsZK = true;}
      if(cmrKbKIkBu == BZDyzAXweG){MQwJQYnXDy = true;}
      else if(BZDyzAXweG == cmrKbKIkBu){OMICVgmLSP = true;}
      if(CyspfeHwPf == zkMEaGrUPL){DxpmWipSFl = true;}
      else if(zkMEaGrUPL == CyspfeHwPf){dVrCLCOKgp = true;}
      if(PygSHkygfP == UZXRZlkOzD){cTJkyoxMqr = true;}
      else if(UZXRZlkOzD == PygSHkygfP){eBXkfahTnt = true;}
      if(wbqwBfiNLn == VuIgxoBjjT){AwVcXYiJNw = true;}
      if(BzTLFIWsyu == OICSWowEuV){JDEXRpZXAU = true;}
      if(uIWJWdFZDp == hYSAKaBkXM){NrUwnsHLKa = true;}
      while(VuIgxoBjjT == wbqwBfiNLn){BULHsCQJzw = true;}
      while(OICSWowEuV == OICSWowEuV){UQGYAufuZS = true;}
      while(hYSAKaBkXM == hYSAKaBkXM){TMMjfMoWVt = true;}
      if(PJwajEbfHk == true){PJwajEbfHk = false;}
      if(EIkuxMXEuk == true){EIkuxMXEuk = false;}
      if(pfSdVxbIVV == true){pfSdVxbIVV = false;}
      if(mPLXEELaiR == true){mPLXEELaiR = false;}
      if(MQwJQYnXDy == true){MQwJQYnXDy = false;}
      if(DxpmWipSFl == true){DxpmWipSFl = false;}
      if(cTJkyoxMqr == true){cTJkyoxMqr = false;}
      if(AwVcXYiJNw == true){AwVcXYiJNw = false;}
      if(JDEXRpZXAU == true){JDEXRpZXAU = false;}
      if(NrUwnsHLKa == true){NrUwnsHLKa = false;}
      if(bagKxGaMPy == true){bagKxGaMPy = false;}
      if(zgFJcYOkSI == true){zgFJcYOkSI = false;}
      if(PYMVdHbYod == true){PYMVdHbYod = false;}
      if(RXylUhWsZK == true){RXylUhWsZK = false;}
      if(OMICVgmLSP == true){OMICVgmLSP = false;}
      if(dVrCLCOKgp == true){dVrCLCOKgp = false;}
      if(eBXkfahTnt == true){eBXkfahTnt = false;}
      if(BULHsCQJzw == true){BULHsCQJzw = false;}
      if(UQGYAufuZS == true){UQGYAufuZS = false;}
      if(TMMjfMoWVt == true){TMMjfMoWVt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVCCTWNHSZ
{ 
  void TukPcVQkTM()
  { 
      bool DHjMTPXgVx = false;
      bool QEmosLIQuw = false;
      bool IrBDRzSrdJ = false;
      bool sxaYQZDtLL = false;
      bool pySslIndMC = false;
      bool BVCJiKGfuU = false;
      bool wfCMESdNYS = false;
      bool IOFjFKZHQI = false;
      bool KoebHXtQpF = false;
      bool TWzpOJuFoT = false;
      bool eaEssmPSDY = false;
      bool kzOlKGBaFf = false;
      bool XMXTzlOOUw = false;
      bool PTSxdjkkhT = false;
      bool IbNRTUHMfI = false;
      bool ITAIuSCktH = false;
      bool XAxHIQfRIa = false;
      bool VPskXwyGze = false;
      bool dBiMmuTJCL = false;
      bool gzpauHeGID = false;
      string iTxTkJTMCI;
      string buCWjgOxeQ;
      string DInXFaNMsG;
      string XHKrzdlZdz;
      string XSZWLNsbUD;
      string QgCqfZeZNK;
      string uHTukTjKWF;
      string toSesjhRMr;
      string glroopFSMY;
      string zMLTEQzelq;
      string ciEPIbOWyu;
      string rNMVcIOdFu;
      string NQxyFhcyab;
      string jDfUOyhcfN;
      string ahUQglzpqu;
      string BVYpdMkFJa;
      string zQwVKnhrGd;
      string alxrTfwgRT;
      string hmHeaOeoqC;
      string MbSFOKlyFr;
      if(iTxTkJTMCI == ciEPIbOWyu){DHjMTPXgVx = true;}
      else if(ciEPIbOWyu == iTxTkJTMCI){eaEssmPSDY = true;}
      if(buCWjgOxeQ == rNMVcIOdFu){QEmosLIQuw = true;}
      else if(rNMVcIOdFu == buCWjgOxeQ){kzOlKGBaFf = true;}
      if(DInXFaNMsG == NQxyFhcyab){IrBDRzSrdJ = true;}
      else if(NQxyFhcyab == DInXFaNMsG){XMXTzlOOUw = true;}
      if(XHKrzdlZdz == jDfUOyhcfN){sxaYQZDtLL = true;}
      else if(jDfUOyhcfN == XHKrzdlZdz){PTSxdjkkhT = true;}
      if(XSZWLNsbUD == ahUQglzpqu){pySslIndMC = true;}
      else if(ahUQglzpqu == XSZWLNsbUD){IbNRTUHMfI = true;}
      if(QgCqfZeZNK == BVYpdMkFJa){BVCJiKGfuU = true;}
      else if(BVYpdMkFJa == QgCqfZeZNK){ITAIuSCktH = true;}
      if(uHTukTjKWF == zQwVKnhrGd){wfCMESdNYS = true;}
      else if(zQwVKnhrGd == uHTukTjKWF){XAxHIQfRIa = true;}
      if(toSesjhRMr == alxrTfwgRT){IOFjFKZHQI = true;}
      if(glroopFSMY == hmHeaOeoqC){KoebHXtQpF = true;}
      if(zMLTEQzelq == MbSFOKlyFr){TWzpOJuFoT = true;}
      while(alxrTfwgRT == toSesjhRMr){VPskXwyGze = true;}
      while(hmHeaOeoqC == hmHeaOeoqC){dBiMmuTJCL = true;}
      while(MbSFOKlyFr == MbSFOKlyFr){gzpauHeGID = true;}
      if(DHjMTPXgVx == true){DHjMTPXgVx = false;}
      if(QEmosLIQuw == true){QEmosLIQuw = false;}
      if(IrBDRzSrdJ == true){IrBDRzSrdJ = false;}
      if(sxaYQZDtLL == true){sxaYQZDtLL = false;}
      if(pySslIndMC == true){pySslIndMC = false;}
      if(BVCJiKGfuU == true){BVCJiKGfuU = false;}
      if(wfCMESdNYS == true){wfCMESdNYS = false;}
      if(IOFjFKZHQI == true){IOFjFKZHQI = false;}
      if(KoebHXtQpF == true){KoebHXtQpF = false;}
      if(TWzpOJuFoT == true){TWzpOJuFoT = false;}
      if(eaEssmPSDY == true){eaEssmPSDY = false;}
      if(kzOlKGBaFf == true){kzOlKGBaFf = false;}
      if(XMXTzlOOUw == true){XMXTzlOOUw = false;}
      if(PTSxdjkkhT == true){PTSxdjkkhT = false;}
      if(IbNRTUHMfI == true){IbNRTUHMfI = false;}
      if(ITAIuSCktH == true){ITAIuSCktH = false;}
      if(XAxHIQfRIa == true){XAxHIQfRIa = false;}
      if(VPskXwyGze == true){VPskXwyGze = false;}
      if(dBiMmuTJCL == true){dBiMmuTJCL = false;}
      if(gzpauHeGID == true){gzpauHeGID = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWUVIBYVLT
{ 
  void ePICqZmZFd()
  { 
      bool wLPeCLhnEF = false;
      bool uHXzCVcHtN = false;
      bool lGoeFJemgQ = false;
      bool XqoShNfucV = false;
      bool YoDjfrJQJO = false;
      bool UPuEIoVkYs = false;
      bool gtHmhDSEQn = false;
      bool phdXowDFyN = false;
      bool zNcRwHwkKr = false;
      bool quVjodhQBc = false;
      bool ZFzVXllWPM = false;
      bool lQlKsSRoqa = false;
      bool HgtXwtLtiL = false;
      bool NlDVntOHsJ = false;
      bool VYUxGaILpV = false;
      bool MsYaUrLaYc = false;
      bool ZqmEyzMQWz = false;
      bool EJugEhMwRV = false;
      bool lADNyUNcAw = false;
      bool hmiQidlQzG = false;
      string zezgMIicjV;
      string rRryBQbOVj;
      string sqafpTUeIb;
      string qPjFQHiZzq;
      string AmhOiJurOa;
      string mcqAMHDTqs;
      string mETIechlht;
      string gBPdjGIMxf;
      string XcPgnOXirJ;
      string DPiFEuSZjF;
      string bIJUtkMNQG;
      string yqWLUKolTQ;
      string FzsYpRSKZn;
      string mibqEPStmC;
      string BKRlKLrWjt;
      string GgFTAbPkdb;
      string RCmbTPPfHF;
      string qtyRPtgHNe;
      string ZwZfhGdIpb;
      string zgPLjyWoRt;
      if(zezgMIicjV == bIJUtkMNQG){wLPeCLhnEF = true;}
      else if(bIJUtkMNQG == zezgMIicjV){ZFzVXllWPM = true;}
      if(rRryBQbOVj == yqWLUKolTQ){uHXzCVcHtN = true;}
      else if(yqWLUKolTQ == rRryBQbOVj){lQlKsSRoqa = true;}
      if(sqafpTUeIb == FzsYpRSKZn){lGoeFJemgQ = true;}
      else if(FzsYpRSKZn == sqafpTUeIb){HgtXwtLtiL = true;}
      if(qPjFQHiZzq == mibqEPStmC){XqoShNfucV = true;}
      else if(mibqEPStmC == qPjFQHiZzq){NlDVntOHsJ = true;}
      if(AmhOiJurOa == BKRlKLrWjt){YoDjfrJQJO = true;}
      else if(BKRlKLrWjt == AmhOiJurOa){VYUxGaILpV = true;}
      if(mcqAMHDTqs == GgFTAbPkdb){UPuEIoVkYs = true;}
      else if(GgFTAbPkdb == mcqAMHDTqs){MsYaUrLaYc = true;}
      if(mETIechlht == RCmbTPPfHF){gtHmhDSEQn = true;}
      else if(RCmbTPPfHF == mETIechlht){ZqmEyzMQWz = true;}
      if(gBPdjGIMxf == qtyRPtgHNe){phdXowDFyN = true;}
      if(XcPgnOXirJ == ZwZfhGdIpb){zNcRwHwkKr = true;}
      if(DPiFEuSZjF == zgPLjyWoRt){quVjodhQBc = true;}
      while(qtyRPtgHNe == gBPdjGIMxf){EJugEhMwRV = true;}
      while(ZwZfhGdIpb == ZwZfhGdIpb){lADNyUNcAw = true;}
      while(zgPLjyWoRt == zgPLjyWoRt){hmiQidlQzG = true;}
      if(wLPeCLhnEF == true){wLPeCLhnEF = false;}
      if(uHXzCVcHtN == true){uHXzCVcHtN = false;}
      if(lGoeFJemgQ == true){lGoeFJemgQ = false;}
      if(XqoShNfucV == true){XqoShNfucV = false;}
      if(YoDjfrJQJO == true){YoDjfrJQJO = false;}
      if(UPuEIoVkYs == true){UPuEIoVkYs = false;}
      if(gtHmhDSEQn == true){gtHmhDSEQn = false;}
      if(phdXowDFyN == true){phdXowDFyN = false;}
      if(zNcRwHwkKr == true){zNcRwHwkKr = false;}
      if(quVjodhQBc == true){quVjodhQBc = false;}
      if(ZFzVXllWPM == true){ZFzVXllWPM = false;}
      if(lQlKsSRoqa == true){lQlKsSRoqa = false;}
      if(HgtXwtLtiL == true){HgtXwtLtiL = false;}
      if(NlDVntOHsJ == true){NlDVntOHsJ = false;}
      if(VYUxGaILpV == true){VYUxGaILpV = false;}
      if(MsYaUrLaYc == true){MsYaUrLaYc = false;}
      if(ZqmEyzMQWz == true){ZqmEyzMQWz = false;}
      if(EJugEhMwRV == true){EJugEhMwRV = false;}
      if(lADNyUNcAw == true){lADNyUNcAw = false;}
      if(hmiQidlQzG == true){hmiQidlQzG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZPYPLQXJW
{ 
  void WmrTMkpeGL()
  { 
      bool HtgWlQHfKf = false;
      bool JgthTpPmIZ = false;
      bool MBwRhbGgmj = false;
      bool GAKdcLDgfY = false;
      bool nXorqNzjxD = false;
      bool bhcXxGyPoJ = false;
      bool JasZYIWPEH = false;
      bool mhHjlnMDZT = false;
      bool bViiIYXlfW = false;
      bool NmrVOMeOSi = false;
      bool qifoPtZrkI = false;
      bool ttpVhmrJQz = false;
      bool jjjhtAokUZ = false;
      bool JxjqcrptTO = false;
      bool yeAXbSxWmb = false;
      bool UVxTyGzxuP = false;
      bool EoXLzwJzrp = false;
      bool xyoCAEiLFa = false;
      bool CSysFnzQrW = false;
      bool rryEKJHnXe = false;
      string wDnyFRAwbu;
      string OMjuektrHm;
      string YgGASptuSr;
      string YKaPXrBtac;
      string GZzuMDmUye;
      string LoILWPxneO;
      string XFdiVDkUWm;
      string iAQegygKnO;
      string CZwmgiCOrI;
      string tNPLFAwPYI;
      string RRxLuLXdeX;
      string hlzPMyJpCm;
      string AVcOsUjEYf;
      string CRlfxjbjrU;
      string KYjTaIOzzH;
      string pGNlHuohRa;
      string aTEyVQATSb;
      string VYygbblInj;
      string GjERpwEzXB;
      string ttSRtqUkyJ;
      if(wDnyFRAwbu == RRxLuLXdeX){HtgWlQHfKf = true;}
      else if(RRxLuLXdeX == wDnyFRAwbu){qifoPtZrkI = true;}
      if(OMjuektrHm == hlzPMyJpCm){JgthTpPmIZ = true;}
      else if(hlzPMyJpCm == OMjuektrHm){ttpVhmrJQz = true;}
      if(YgGASptuSr == AVcOsUjEYf){MBwRhbGgmj = true;}
      else if(AVcOsUjEYf == YgGASptuSr){jjjhtAokUZ = true;}
      if(YKaPXrBtac == CRlfxjbjrU){GAKdcLDgfY = true;}
      else if(CRlfxjbjrU == YKaPXrBtac){JxjqcrptTO = true;}
      if(GZzuMDmUye == KYjTaIOzzH){nXorqNzjxD = true;}
      else if(KYjTaIOzzH == GZzuMDmUye){yeAXbSxWmb = true;}
      if(LoILWPxneO == pGNlHuohRa){bhcXxGyPoJ = true;}
      else if(pGNlHuohRa == LoILWPxneO){UVxTyGzxuP = true;}
      if(XFdiVDkUWm == aTEyVQATSb){JasZYIWPEH = true;}
      else if(aTEyVQATSb == XFdiVDkUWm){EoXLzwJzrp = true;}
      if(iAQegygKnO == VYygbblInj){mhHjlnMDZT = true;}
      if(CZwmgiCOrI == GjERpwEzXB){bViiIYXlfW = true;}
      if(tNPLFAwPYI == ttSRtqUkyJ){NmrVOMeOSi = true;}
      while(VYygbblInj == iAQegygKnO){xyoCAEiLFa = true;}
      while(GjERpwEzXB == GjERpwEzXB){CSysFnzQrW = true;}
      while(ttSRtqUkyJ == ttSRtqUkyJ){rryEKJHnXe = true;}
      if(HtgWlQHfKf == true){HtgWlQHfKf = false;}
      if(JgthTpPmIZ == true){JgthTpPmIZ = false;}
      if(MBwRhbGgmj == true){MBwRhbGgmj = false;}
      if(GAKdcLDgfY == true){GAKdcLDgfY = false;}
      if(nXorqNzjxD == true){nXorqNzjxD = false;}
      if(bhcXxGyPoJ == true){bhcXxGyPoJ = false;}
      if(JasZYIWPEH == true){JasZYIWPEH = false;}
      if(mhHjlnMDZT == true){mhHjlnMDZT = false;}
      if(bViiIYXlfW == true){bViiIYXlfW = false;}
      if(NmrVOMeOSi == true){NmrVOMeOSi = false;}
      if(qifoPtZrkI == true){qifoPtZrkI = false;}
      if(ttpVhmrJQz == true){ttpVhmrJQz = false;}
      if(jjjhtAokUZ == true){jjjhtAokUZ = false;}
      if(JxjqcrptTO == true){JxjqcrptTO = false;}
      if(yeAXbSxWmb == true){yeAXbSxWmb = false;}
      if(UVxTyGzxuP == true){UVxTyGzxuP = false;}
      if(EoXLzwJzrp == true){EoXLzwJzrp = false;}
      if(xyoCAEiLFa == true){xyoCAEiLFa = false;}
      if(CSysFnzQrW == true){CSysFnzQrW = false;}
      if(rryEKJHnXe == true){rryEKJHnXe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QSBIKUKTLD
{ 
  void TTVCfaThyQ()
  { 
      bool hLLAwiFYcb = false;
      bool dzoIlhgOyp = false;
      bool pgbPRJlMus = false;
      bool jKQwTTpGft = false;
      bool EngBUjThKc = false;
      bool ljyMCAjwim = false;
      bool xrdjqSisnR = false;
      bool rahElBAZuh = false;
      bool pDCRGzMEsT = false;
      bool isWswMKxJB = false;
      bool AZsskLBtZA = false;
      bool AJBBwspLcr = false;
      bool GezUhyDoHY = false;
      bool qCPsgQJIgu = false;
      bool xSdsSZrVwD = false;
      bool VzTRuVZXKl = false;
      bool HMlBIxsHTf = false;
      bool igdhtnBGCI = false;
      bool GgrECriyxL = false;
      bool pkyumkfbjV = false;
      string KEmzjEoDou;
      string fHSEXofYqk;
      string DfxRukwXBZ;
      string UbkRYafdGc;
      string GpAkpqqtjX;
      string PPzumdGUDy;
      string HRCOZDWBex;
      string ICRNdMfMaE;
      string sCndKFcpdt;
      string ULZHUomkKl;
      string TpOmONxkQZ;
      string yttzFFdYEU;
      string agWkbxcJro;
      string YtBnkDmBOw;
      string HqYDwaRaCP;
      string LOgpLlSdKR;
      string knrbADrFOC;
      string ScJHMiISnB;
      string fCGccJNKcy;
      string jIpwLTzxCr;
      if(KEmzjEoDou == TpOmONxkQZ){hLLAwiFYcb = true;}
      else if(TpOmONxkQZ == KEmzjEoDou){AZsskLBtZA = true;}
      if(fHSEXofYqk == yttzFFdYEU){dzoIlhgOyp = true;}
      else if(yttzFFdYEU == fHSEXofYqk){AJBBwspLcr = true;}
      if(DfxRukwXBZ == agWkbxcJro){pgbPRJlMus = true;}
      else if(agWkbxcJro == DfxRukwXBZ){GezUhyDoHY = true;}
      if(UbkRYafdGc == YtBnkDmBOw){jKQwTTpGft = true;}
      else if(YtBnkDmBOw == UbkRYafdGc){qCPsgQJIgu = true;}
      if(GpAkpqqtjX == HqYDwaRaCP){EngBUjThKc = true;}
      else if(HqYDwaRaCP == GpAkpqqtjX){xSdsSZrVwD = true;}
      if(PPzumdGUDy == LOgpLlSdKR){ljyMCAjwim = true;}
      else if(LOgpLlSdKR == PPzumdGUDy){VzTRuVZXKl = true;}
      if(HRCOZDWBex == knrbADrFOC){xrdjqSisnR = true;}
      else if(knrbADrFOC == HRCOZDWBex){HMlBIxsHTf = true;}
      if(ICRNdMfMaE == ScJHMiISnB){rahElBAZuh = true;}
      if(sCndKFcpdt == fCGccJNKcy){pDCRGzMEsT = true;}
      if(ULZHUomkKl == jIpwLTzxCr){isWswMKxJB = true;}
      while(ScJHMiISnB == ICRNdMfMaE){igdhtnBGCI = true;}
      while(fCGccJNKcy == fCGccJNKcy){GgrECriyxL = true;}
      while(jIpwLTzxCr == jIpwLTzxCr){pkyumkfbjV = true;}
      if(hLLAwiFYcb == true){hLLAwiFYcb = false;}
      if(dzoIlhgOyp == true){dzoIlhgOyp = false;}
      if(pgbPRJlMus == true){pgbPRJlMus = false;}
      if(jKQwTTpGft == true){jKQwTTpGft = false;}
      if(EngBUjThKc == true){EngBUjThKc = false;}
      if(ljyMCAjwim == true){ljyMCAjwim = false;}
      if(xrdjqSisnR == true){xrdjqSisnR = false;}
      if(rahElBAZuh == true){rahElBAZuh = false;}
      if(pDCRGzMEsT == true){pDCRGzMEsT = false;}
      if(isWswMKxJB == true){isWswMKxJB = false;}
      if(AZsskLBtZA == true){AZsskLBtZA = false;}
      if(AJBBwspLcr == true){AJBBwspLcr = false;}
      if(GezUhyDoHY == true){GezUhyDoHY = false;}
      if(qCPsgQJIgu == true){qCPsgQJIgu = false;}
      if(xSdsSZrVwD == true){xSdsSZrVwD = false;}
      if(VzTRuVZXKl == true){VzTRuVZXKl = false;}
      if(HMlBIxsHTf == true){HMlBIxsHTf = false;}
      if(igdhtnBGCI == true){igdhtnBGCI = false;}
      if(GgrECriyxL == true){GgrECriyxL = false;}
      if(pkyumkfbjV == true){pkyumkfbjV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ISTNZHBAHH
{ 
  void BRLRoERdXY()
  { 
      bool dbieyrqJBD = false;
      bool IzVUlyNtBZ = false;
      bool QNmVTXbfjm = false;
      bool aPQPBXbZFt = false;
      bool OaBIBYsLSH = false;
      bool psPtkPnNLa = false;
      bool QKYNcriGSO = false;
      bool WmnHLoLeTt = false;
      bool dPMcxgAVdk = false;
      bool iOOddDBneI = false;
      bool omsEkDEIiu = false;
      bool EJsQwAywQw = false;
      bool rNbgfHXKdH = false;
      bool nXAKEqWIrs = false;
      bool brmigZUygc = false;
      bool FFXiQbKLYc = false;
      bool etdaHfJiLF = false;
      bool doDWTAZsAG = false;
      bool mZcAChAQtb = false;
      bool fKjPNgNLaB = false;
      string aPVoaTWoEC;
      string DNOXOVXHmT;
      string gzwrewWXEA;
      string TcpQPckDEW;
      string oqJqsBSONy;
      string CzDGDbSdJe;
      string xzjDiZXxHl;
      string jTCPdopEyd;
      string dIJGyTZiNn;
      string JHtYZpGFIS;
      string dUGbOiwncN;
      string kNefBnodFO;
      string AnjTbbYcon;
      string ijweAIBgrO;
      string WlGzCubOXk;
      string AcAsSpjmAl;
      string JSyoeBRAfr;
      string lIlprOgjQf;
      string zKFEmFjDMJ;
      string YOfFFEnRTB;
      if(aPVoaTWoEC == dUGbOiwncN){dbieyrqJBD = true;}
      else if(dUGbOiwncN == aPVoaTWoEC){omsEkDEIiu = true;}
      if(DNOXOVXHmT == kNefBnodFO){IzVUlyNtBZ = true;}
      else if(kNefBnodFO == DNOXOVXHmT){EJsQwAywQw = true;}
      if(gzwrewWXEA == AnjTbbYcon){QNmVTXbfjm = true;}
      else if(AnjTbbYcon == gzwrewWXEA){rNbgfHXKdH = true;}
      if(TcpQPckDEW == ijweAIBgrO){aPQPBXbZFt = true;}
      else if(ijweAIBgrO == TcpQPckDEW){nXAKEqWIrs = true;}
      if(oqJqsBSONy == WlGzCubOXk){OaBIBYsLSH = true;}
      else if(WlGzCubOXk == oqJqsBSONy){brmigZUygc = true;}
      if(CzDGDbSdJe == AcAsSpjmAl){psPtkPnNLa = true;}
      else if(AcAsSpjmAl == CzDGDbSdJe){FFXiQbKLYc = true;}
      if(xzjDiZXxHl == JSyoeBRAfr){QKYNcriGSO = true;}
      else if(JSyoeBRAfr == xzjDiZXxHl){etdaHfJiLF = true;}
      if(jTCPdopEyd == lIlprOgjQf){WmnHLoLeTt = true;}
      if(dIJGyTZiNn == zKFEmFjDMJ){dPMcxgAVdk = true;}
      if(JHtYZpGFIS == YOfFFEnRTB){iOOddDBneI = true;}
      while(lIlprOgjQf == jTCPdopEyd){doDWTAZsAG = true;}
      while(zKFEmFjDMJ == zKFEmFjDMJ){mZcAChAQtb = true;}
      while(YOfFFEnRTB == YOfFFEnRTB){fKjPNgNLaB = true;}
      if(dbieyrqJBD == true){dbieyrqJBD = false;}
      if(IzVUlyNtBZ == true){IzVUlyNtBZ = false;}
      if(QNmVTXbfjm == true){QNmVTXbfjm = false;}
      if(aPQPBXbZFt == true){aPQPBXbZFt = false;}
      if(OaBIBYsLSH == true){OaBIBYsLSH = false;}
      if(psPtkPnNLa == true){psPtkPnNLa = false;}
      if(QKYNcriGSO == true){QKYNcriGSO = false;}
      if(WmnHLoLeTt == true){WmnHLoLeTt = false;}
      if(dPMcxgAVdk == true){dPMcxgAVdk = false;}
      if(iOOddDBneI == true){iOOddDBneI = false;}
      if(omsEkDEIiu == true){omsEkDEIiu = false;}
      if(EJsQwAywQw == true){EJsQwAywQw = false;}
      if(rNbgfHXKdH == true){rNbgfHXKdH = false;}
      if(nXAKEqWIrs == true){nXAKEqWIrs = false;}
      if(brmigZUygc == true){brmigZUygc = false;}
      if(FFXiQbKLYc == true){FFXiQbKLYc = false;}
      if(etdaHfJiLF == true){etdaHfJiLF = false;}
      if(doDWTAZsAG == true){doDWTAZsAG = false;}
      if(mZcAChAQtb == true){mZcAChAQtb = false;}
      if(fKjPNgNLaB == true){fKjPNgNLaB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQXNRMRAJF
{ 
  void aZPacISKWw()
  { 
      bool MMVtoPgAoH = false;
      bool sJNrwGJXxj = false;
      bool YNSwyhLQDE = false;
      bool sdAPUWWQaE = false;
      bool CDzLSwFDAe = false;
      bool ZgjHNysZwH = false;
      bool EQxjOPIxWY = false;
      bool iswrgUOHdC = false;
      bool bHPXdLssBV = false;
      bool cxTTAlGPwC = false;
      bool mIfawfkqZr = false;
      bool jlutfwAZFC = false;
      bool VPuBwkYcrt = false;
      bool OyKaOTbnay = false;
      bool aBSJlqCZnD = false;
      bool kgJtfXMeeL = false;
      bool HHzfdkaUeM = false;
      bool UMyHaUwlPE = false;
      bool iynoJhoQtp = false;
      bool HwIPpSCmeA = false;
      string uxqbwJReAH;
      string GiifcktxLM;
      string lLmHSZHxwP;
      string eWNXXusOec;
      string UUByikOpEF;
      string EweDOiJjIV;
      string BUikbjVKHh;
      string qfSirQKoYg;
      string KRrqKiqKIo;
      string kJGJazlPWz;
      string PDhWNYdwKx;
      string XULaKjbqZs;
      string rKCSxhYJHr;
      string etRYRGiUck;
      string EtzKQPyeyp;
      string XuocGEBPZf;
      string zUoRSdClJD;
      string BHNonyKrCg;
      string isKQUiEoSM;
      string FTuxkjFgql;
      if(uxqbwJReAH == PDhWNYdwKx){MMVtoPgAoH = true;}
      else if(PDhWNYdwKx == uxqbwJReAH){mIfawfkqZr = true;}
      if(GiifcktxLM == XULaKjbqZs){sJNrwGJXxj = true;}
      else if(XULaKjbqZs == GiifcktxLM){jlutfwAZFC = true;}
      if(lLmHSZHxwP == rKCSxhYJHr){YNSwyhLQDE = true;}
      else if(rKCSxhYJHr == lLmHSZHxwP){VPuBwkYcrt = true;}
      if(eWNXXusOec == etRYRGiUck){sdAPUWWQaE = true;}
      else if(etRYRGiUck == eWNXXusOec){OyKaOTbnay = true;}
      if(UUByikOpEF == EtzKQPyeyp){CDzLSwFDAe = true;}
      else if(EtzKQPyeyp == UUByikOpEF){aBSJlqCZnD = true;}
      if(EweDOiJjIV == XuocGEBPZf){ZgjHNysZwH = true;}
      else if(XuocGEBPZf == EweDOiJjIV){kgJtfXMeeL = true;}
      if(BUikbjVKHh == zUoRSdClJD){EQxjOPIxWY = true;}
      else if(zUoRSdClJD == BUikbjVKHh){HHzfdkaUeM = true;}
      if(qfSirQKoYg == BHNonyKrCg){iswrgUOHdC = true;}
      if(KRrqKiqKIo == isKQUiEoSM){bHPXdLssBV = true;}
      if(kJGJazlPWz == FTuxkjFgql){cxTTAlGPwC = true;}
      while(BHNonyKrCg == qfSirQKoYg){UMyHaUwlPE = true;}
      while(isKQUiEoSM == isKQUiEoSM){iynoJhoQtp = true;}
      while(FTuxkjFgql == FTuxkjFgql){HwIPpSCmeA = true;}
      if(MMVtoPgAoH == true){MMVtoPgAoH = false;}
      if(sJNrwGJXxj == true){sJNrwGJXxj = false;}
      if(YNSwyhLQDE == true){YNSwyhLQDE = false;}
      if(sdAPUWWQaE == true){sdAPUWWQaE = false;}
      if(CDzLSwFDAe == true){CDzLSwFDAe = false;}
      if(ZgjHNysZwH == true){ZgjHNysZwH = false;}
      if(EQxjOPIxWY == true){EQxjOPIxWY = false;}
      if(iswrgUOHdC == true){iswrgUOHdC = false;}
      if(bHPXdLssBV == true){bHPXdLssBV = false;}
      if(cxTTAlGPwC == true){cxTTAlGPwC = false;}
      if(mIfawfkqZr == true){mIfawfkqZr = false;}
      if(jlutfwAZFC == true){jlutfwAZFC = false;}
      if(VPuBwkYcrt == true){VPuBwkYcrt = false;}
      if(OyKaOTbnay == true){OyKaOTbnay = false;}
      if(aBSJlqCZnD == true){aBSJlqCZnD = false;}
      if(kgJtfXMeeL == true){kgJtfXMeeL = false;}
      if(HHzfdkaUeM == true){HHzfdkaUeM = false;}
      if(UMyHaUwlPE == true){UMyHaUwlPE = false;}
      if(iynoJhoQtp == true){iynoJhoQtp = false;}
      if(HwIPpSCmeA == true){HwIPpSCmeA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIZDSLTIZW
{ 
  void fOZQTxxPNT()
  { 
      bool BjTaCppNVQ = false;
      bool KThoIVauHN = false;
      bool iPfcHeEZln = false;
      bool DyGdGQCMQa = false;
      bool JVGbOjItCU = false;
      bool FIOjhlDpTX = false;
      bool kPbhMMMEhr = false;
      bool TNefDMIENW = false;
      bool VJXQhuiWwT = false;
      bool NLrsostYOB = false;
      bool WELKBrcifU = false;
      bool dycxBarKzQ = false;
      bool dpIOdIUkpJ = false;
      bool SioLAQxNPp = false;
      bool RzpapOiuqN = false;
      bool BiZyXfwxfs = false;
      bool WrrWCtIQwj = false;
      bool ceuJzdAhXO = false;
      bool YYtbIiJqnT = false;
      bool UAgWTZHTXw = false;
      string hPIkQTlKCZ;
      string eMQHyIGWtt;
      string kLeFcQwlPW;
      string YifAzpAkXm;
      string zbhGsbDRGa;
      string EnMPzVjCHz;
      string WzteAwfQIH;
      string HUyHuJcYMA;
      string NeenSkWQBc;
      string FycXPzgDFw;
      string ulJyTioFUp;
      string sLoHlqUGMP;
      string YPPeCJqaqw;
      string bZSPFaVfUi;
      string uRuLjtIVlX;
      string dappXeWdwJ;
      string rONYNSrYCK;
      string VnkcTHUDuH;
      string AVnSRAicrZ;
      string DqiKqfDWxQ;
      if(hPIkQTlKCZ == ulJyTioFUp){BjTaCppNVQ = true;}
      else if(ulJyTioFUp == hPIkQTlKCZ){WELKBrcifU = true;}
      if(eMQHyIGWtt == sLoHlqUGMP){KThoIVauHN = true;}
      else if(sLoHlqUGMP == eMQHyIGWtt){dycxBarKzQ = true;}
      if(kLeFcQwlPW == YPPeCJqaqw){iPfcHeEZln = true;}
      else if(YPPeCJqaqw == kLeFcQwlPW){dpIOdIUkpJ = true;}
      if(YifAzpAkXm == bZSPFaVfUi){DyGdGQCMQa = true;}
      else if(bZSPFaVfUi == YifAzpAkXm){SioLAQxNPp = true;}
      if(zbhGsbDRGa == uRuLjtIVlX){JVGbOjItCU = true;}
      else if(uRuLjtIVlX == zbhGsbDRGa){RzpapOiuqN = true;}
      if(EnMPzVjCHz == dappXeWdwJ){FIOjhlDpTX = true;}
      else if(dappXeWdwJ == EnMPzVjCHz){BiZyXfwxfs = true;}
      if(WzteAwfQIH == rONYNSrYCK){kPbhMMMEhr = true;}
      else if(rONYNSrYCK == WzteAwfQIH){WrrWCtIQwj = true;}
      if(HUyHuJcYMA == VnkcTHUDuH){TNefDMIENW = true;}
      if(NeenSkWQBc == AVnSRAicrZ){VJXQhuiWwT = true;}
      if(FycXPzgDFw == DqiKqfDWxQ){NLrsostYOB = true;}
      while(VnkcTHUDuH == HUyHuJcYMA){ceuJzdAhXO = true;}
      while(AVnSRAicrZ == AVnSRAicrZ){YYtbIiJqnT = true;}
      while(DqiKqfDWxQ == DqiKqfDWxQ){UAgWTZHTXw = true;}
      if(BjTaCppNVQ == true){BjTaCppNVQ = false;}
      if(KThoIVauHN == true){KThoIVauHN = false;}
      if(iPfcHeEZln == true){iPfcHeEZln = false;}
      if(DyGdGQCMQa == true){DyGdGQCMQa = false;}
      if(JVGbOjItCU == true){JVGbOjItCU = false;}
      if(FIOjhlDpTX == true){FIOjhlDpTX = false;}
      if(kPbhMMMEhr == true){kPbhMMMEhr = false;}
      if(TNefDMIENW == true){TNefDMIENW = false;}
      if(VJXQhuiWwT == true){VJXQhuiWwT = false;}
      if(NLrsostYOB == true){NLrsostYOB = false;}
      if(WELKBrcifU == true){WELKBrcifU = false;}
      if(dycxBarKzQ == true){dycxBarKzQ = false;}
      if(dpIOdIUkpJ == true){dpIOdIUkpJ = false;}
      if(SioLAQxNPp == true){SioLAQxNPp = false;}
      if(RzpapOiuqN == true){RzpapOiuqN = false;}
      if(BiZyXfwxfs == true){BiZyXfwxfs = false;}
      if(WrrWCtIQwj == true){WrrWCtIQwj = false;}
      if(ceuJzdAhXO == true){ceuJzdAhXO = false;}
      if(YYtbIiJqnT == true){YYtbIiJqnT = false;}
      if(UAgWTZHTXw == true){UAgWTZHTXw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OAZKJCPFAH
{ 
  void HkypJJpBdd()
  { 
      bool OKaqKPTbKp = false;
      bool XeDRPPmfyp = false;
      bool MdCIMbSNQU = false;
      bool uOWWQYYEOD = false;
      bool pJoGnqbzZK = false;
      bool nfwspjHRdh = false;
      bool xFKotJIgAp = false;
      bool qhRtACouUV = false;
      bool zSmGgORcfg = false;
      bool QGafGjzzLe = false;
      bool huyiTFOBrn = false;
      bool tLxHhdRDIe = false;
      bool qeATYjHknQ = false;
      bool CpiomEUEla = false;
      bool AQjqmEJSxb = false;
      bool SuqfnCteKj = false;
      bool ydMbkEbHTd = false;
      bool JNQgeZuIgT = false;
      bool ZnmLyHyCBj = false;
      bool KotCcVDHGh = false;
      string ATJjtSrKFo;
      string YfyokebhbD;
      string nqMoYSrHgU;
      string NhHrLjbVsF;
      string jrlpRbigWx;
      string SuRGbIGTLa;
      string ZjcjaqXGdB;
      string DGoVTwFVWx;
      string jLkjCSPAPD;
      string cHKRfzPBPa;
      string DbDVtLGwmf;
      string CjwNqOzrhI;
      string bWpZXuwWpT;
      string fEGwsHHOop;
      string LSNjArKwaQ;
      string AWSHzgkcxz;
      string PjFSzxdAUi;
      string GjDqwIJGZf;
      string jAwYTJkzxL;
      string VeRoZbMtjC;
      if(ATJjtSrKFo == DbDVtLGwmf){OKaqKPTbKp = true;}
      else if(DbDVtLGwmf == ATJjtSrKFo){huyiTFOBrn = true;}
      if(YfyokebhbD == CjwNqOzrhI){XeDRPPmfyp = true;}
      else if(CjwNqOzrhI == YfyokebhbD){tLxHhdRDIe = true;}
      if(nqMoYSrHgU == bWpZXuwWpT){MdCIMbSNQU = true;}
      else if(bWpZXuwWpT == nqMoYSrHgU){qeATYjHknQ = true;}
      if(NhHrLjbVsF == fEGwsHHOop){uOWWQYYEOD = true;}
      else if(fEGwsHHOop == NhHrLjbVsF){CpiomEUEla = true;}
      if(jrlpRbigWx == LSNjArKwaQ){pJoGnqbzZK = true;}
      else if(LSNjArKwaQ == jrlpRbigWx){AQjqmEJSxb = true;}
      if(SuRGbIGTLa == AWSHzgkcxz){nfwspjHRdh = true;}
      else if(AWSHzgkcxz == SuRGbIGTLa){SuqfnCteKj = true;}
      if(ZjcjaqXGdB == PjFSzxdAUi){xFKotJIgAp = true;}
      else if(PjFSzxdAUi == ZjcjaqXGdB){ydMbkEbHTd = true;}
      if(DGoVTwFVWx == GjDqwIJGZf){qhRtACouUV = true;}
      if(jLkjCSPAPD == jAwYTJkzxL){zSmGgORcfg = true;}
      if(cHKRfzPBPa == VeRoZbMtjC){QGafGjzzLe = true;}
      while(GjDqwIJGZf == DGoVTwFVWx){JNQgeZuIgT = true;}
      while(jAwYTJkzxL == jAwYTJkzxL){ZnmLyHyCBj = true;}
      while(VeRoZbMtjC == VeRoZbMtjC){KotCcVDHGh = true;}
      if(OKaqKPTbKp == true){OKaqKPTbKp = false;}
      if(XeDRPPmfyp == true){XeDRPPmfyp = false;}
      if(MdCIMbSNQU == true){MdCIMbSNQU = false;}
      if(uOWWQYYEOD == true){uOWWQYYEOD = false;}
      if(pJoGnqbzZK == true){pJoGnqbzZK = false;}
      if(nfwspjHRdh == true){nfwspjHRdh = false;}
      if(xFKotJIgAp == true){xFKotJIgAp = false;}
      if(qhRtACouUV == true){qhRtACouUV = false;}
      if(zSmGgORcfg == true){zSmGgORcfg = false;}
      if(QGafGjzzLe == true){QGafGjzzLe = false;}
      if(huyiTFOBrn == true){huyiTFOBrn = false;}
      if(tLxHhdRDIe == true){tLxHhdRDIe = false;}
      if(qeATYjHknQ == true){qeATYjHknQ = false;}
      if(CpiomEUEla == true){CpiomEUEla = false;}
      if(AQjqmEJSxb == true){AQjqmEJSxb = false;}
      if(SuqfnCteKj == true){SuqfnCteKj = false;}
      if(ydMbkEbHTd == true){ydMbkEbHTd = false;}
      if(JNQgeZuIgT == true){JNQgeZuIgT = false;}
      if(ZnmLyHyCBj == true){ZnmLyHyCBj = false;}
      if(KotCcVDHGh == true){KotCcVDHGh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEWPKAXNOD
{ 
  void zNoreQjtEP()
  { 
      bool PFMcprnsDo = false;
      bool pCVPdTUMHd = false;
      bool bTmBUeCrLj = false;
      bool ZGYELfAXqa = false;
      bool BxQGYYjziC = false;
      bool VURJduSLHK = false;
      bool owgSPidRDx = false;
      bool TwVfbdDfbw = false;
      bool uCIJNFoOaP = false;
      bool NoPfkFQxqp = false;
      bool uSuliYykgz = false;
      bool rliLOlnXFK = false;
      bool sOpnjefpuW = false;
      bool NGolBcHWao = false;
      bool GDgbWaGEQz = false;
      bool QrqgwfbHBD = false;
      bool sIpKklxwKl = false;
      bool eQxQDpgORI = false;
      bool YbYuFUOHpU = false;
      bool AAUWuxNWpj = false;
      string dWdHRbBCgl;
      string HtMQyPkOgk;
      string iLZYTBEFCR;
      string pqNbaiWQcX;
      string bZdLxhWDhi;
      string phLLOSxEmQ;
      string XuzOuPgjpO;
      string sTlIJJhNbl;
      string dAXSaIeBNI;
      string lRdLzgZPQh;
      string BlNSpWwDCE;
      string kjcBmXWgmm;
      string jeWhcaoZIb;
      string jSwskqlFbE;
      string MbzJXCocYb;
      string JsbcxVPfpP;
      string gVtZURmiPw;
      string lREiZHfNJa;
      string lMBgSppTwO;
      string aGOMWphYnF;
      if(dWdHRbBCgl == BlNSpWwDCE){PFMcprnsDo = true;}
      else if(BlNSpWwDCE == dWdHRbBCgl){uSuliYykgz = true;}
      if(HtMQyPkOgk == kjcBmXWgmm){pCVPdTUMHd = true;}
      else if(kjcBmXWgmm == HtMQyPkOgk){rliLOlnXFK = true;}
      if(iLZYTBEFCR == jeWhcaoZIb){bTmBUeCrLj = true;}
      else if(jeWhcaoZIb == iLZYTBEFCR){sOpnjefpuW = true;}
      if(pqNbaiWQcX == jSwskqlFbE){ZGYELfAXqa = true;}
      else if(jSwskqlFbE == pqNbaiWQcX){NGolBcHWao = true;}
      if(bZdLxhWDhi == MbzJXCocYb){BxQGYYjziC = true;}
      else if(MbzJXCocYb == bZdLxhWDhi){GDgbWaGEQz = true;}
      if(phLLOSxEmQ == JsbcxVPfpP){VURJduSLHK = true;}
      else if(JsbcxVPfpP == phLLOSxEmQ){QrqgwfbHBD = true;}
      if(XuzOuPgjpO == gVtZURmiPw){owgSPidRDx = true;}
      else if(gVtZURmiPw == XuzOuPgjpO){sIpKklxwKl = true;}
      if(sTlIJJhNbl == lREiZHfNJa){TwVfbdDfbw = true;}
      if(dAXSaIeBNI == lMBgSppTwO){uCIJNFoOaP = true;}
      if(lRdLzgZPQh == aGOMWphYnF){NoPfkFQxqp = true;}
      while(lREiZHfNJa == sTlIJJhNbl){eQxQDpgORI = true;}
      while(lMBgSppTwO == lMBgSppTwO){YbYuFUOHpU = true;}
      while(aGOMWphYnF == aGOMWphYnF){AAUWuxNWpj = true;}
      if(PFMcprnsDo == true){PFMcprnsDo = false;}
      if(pCVPdTUMHd == true){pCVPdTUMHd = false;}
      if(bTmBUeCrLj == true){bTmBUeCrLj = false;}
      if(ZGYELfAXqa == true){ZGYELfAXqa = false;}
      if(BxQGYYjziC == true){BxQGYYjziC = false;}
      if(VURJduSLHK == true){VURJduSLHK = false;}
      if(owgSPidRDx == true){owgSPidRDx = false;}
      if(TwVfbdDfbw == true){TwVfbdDfbw = false;}
      if(uCIJNFoOaP == true){uCIJNFoOaP = false;}
      if(NoPfkFQxqp == true){NoPfkFQxqp = false;}
      if(uSuliYykgz == true){uSuliYykgz = false;}
      if(rliLOlnXFK == true){rliLOlnXFK = false;}
      if(sOpnjefpuW == true){sOpnjefpuW = false;}
      if(NGolBcHWao == true){NGolBcHWao = false;}
      if(GDgbWaGEQz == true){GDgbWaGEQz = false;}
      if(QrqgwfbHBD == true){QrqgwfbHBD = false;}
      if(sIpKklxwKl == true){sIpKklxwKl = false;}
      if(eQxQDpgORI == true){eQxQDpgORI = false;}
      if(YbYuFUOHpU == true){YbYuFUOHpU = false;}
      if(AAUWuxNWpj == true){AAUWuxNWpj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMEJPIWZAI
{ 
  void yHhGxJlsLp()
  { 
      bool qPxOqmmiZC = false;
      bool HByDTezgfP = false;
      bool cpUsnNASsa = false;
      bool lWOECfDqKA = false;
      bool ZpqyupXdki = false;
      bool IuEChAtDZc = false;
      bool lTozQjmtAm = false;
      bool aHWepmzVxx = false;
      bool pWhKSpRLVC = false;
      bool kzRgOFArhK = false;
      bool DdcxHAYZMu = false;
      bool BYGbmOlefZ = false;
      bool SbYyBbppQj = false;
      bool mHnltLtjDS = false;
      bool RryaBMspsz = false;
      bool SVLIraFeuf = false;
      bool JiJcHtjTga = false;
      bool UCbMHacxxo = false;
      bool hAwQQQuftS = false;
      bool GOnXIihVSG = false;
      string lbCSReTWMD;
      string OmqNdeSFYB;
      string cOJCLWfmQt;
      string jOwSDBYQzx;
      string MFIarRiCSC;
      string bNoQXWSzHu;
      string zfFSTAqXJc;
      string GCFboXFiKs;
      string mdTOSVYfuf;
      string iZIDxfApHr;
      string aLrpuYHNbz;
      string RjnOIVLpAx;
      string aLcdsgtBdI;
      string WOaSSakdSs;
      string NLDuNzksub;
      string UJpJROiOxO;
      string eFiScCIVwg;
      string jhWHiOHgPt;
      string uAGBmMYRBD;
      string rWgENHcjSL;
      if(lbCSReTWMD == aLrpuYHNbz){qPxOqmmiZC = true;}
      else if(aLrpuYHNbz == lbCSReTWMD){DdcxHAYZMu = true;}
      if(OmqNdeSFYB == RjnOIVLpAx){HByDTezgfP = true;}
      else if(RjnOIVLpAx == OmqNdeSFYB){BYGbmOlefZ = true;}
      if(cOJCLWfmQt == aLcdsgtBdI){cpUsnNASsa = true;}
      else if(aLcdsgtBdI == cOJCLWfmQt){SbYyBbppQj = true;}
      if(jOwSDBYQzx == WOaSSakdSs){lWOECfDqKA = true;}
      else if(WOaSSakdSs == jOwSDBYQzx){mHnltLtjDS = true;}
      if(MFIarRiCSC == NLDuNzksub){ZpqyupXdki = true;}
      else if(NLDuNzksub == MFIarRiCSC){RryaBMspsz = true;}
      if(bNoQXWSzHu == UJpJROiOxO){IuEChAtDZc = true;}
      else if(UJpJROiOxO == bNoQXWSzHu){SVLIraFeuf = true;}
      if(zfFSTAqXJc == eFiScCIVwg){lTozQjmtAm = true;}
      else if(eFiScCIVwg == zfFSTAqXJc){JiJcHtjTga = true;}
      if(GCFboXFiKs == jhWHiOHgPt){aHWepmzVxx = true;}
      if(mdTOSVYfuf == uAGBmMYRBD){pWhKSpRLVC = true;}
      if(iZIDxfApHr == rWgENHcjSL){kzRgOFArhK = true;}
      while(jhWHiOHgPt == GCFboXFiKs){UCbMHacxxo = true;}
      while(uAGBmMYRBD == uAGBmMYRBD){hAwQQQuftS = true;}
      while(rWgENHcjSL == rWgENHcjSL){GOnXIihVSG = true;}
      if(qPxOqmmiZC == true){qPxOqmmiZC = false;}
      if(HByDTezgfP == true){HByDTezgfP = false;}
      if(cpUsnNASsa == true){cpUsnNASsa = false;}
      if(lWOECfDqKA == true){lWOECfDqKA = false;}
      if(ZpqyupXdki == true){ZpqyupXdki = false;}
      if(IuEChAtDZc == true){IuEChAtDZc = false;}
      if(lTozQjmtAm == true){lTozQjmtAm = false;}
      if(aHWepmzVxx == true){aHWepmzVxx = false;}
      if(pWhKSpRLVC == true){pWhKSpRLVC = false;}
      if(kzRgOFArhK == true){kzRgOFArhK = false;}
      if(DdcxHAYZMu == true){DdcxHAYZMu = false;}
      if(BYGbmOlefZ == true){BYGbmOlefZ = false;}
      if(SbYyBbppQj == true){SbYyBbppQj = false;}
      if(mHnltLtjDS == true){mHnltLtjDS = false;}
      if(RryaBMspsz == true){RryaBMspsz = false;}
      if(SVLIraFeuf == true){SVLIraFeuf = false;}
      if(JiJcHtjTga == true){JiJcHtjTga = false;}
      if(UCbMHacxxo == true){UCbMHacxxo = false;}
      if(hAwQQQuftS == true){hAwQQQuftS = false;}
      if(GOnXIihVSG == true){GOnXIihVSG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APNMTCUGVH
{ 
  void BncOOTwCwL()
  { 
      bool mHxozpsTfU = false;
      bool FbhDqBrsEM = false;
      bool DSbMDICPhR = false;
      bool NjedVRTxJx = false;
      bool sPrcLqjJGm = false;
      bool wKlbbTejlq = false;
      bool mdkOGUxEgY = false;
      bool gtiGTmayBL = false;
      bool XsJuVCyCBC = false;
      bool ljLSKPedWp = false;
      bool tfbgFBbeHn = false;
      bool sghaStTorD = false;
      bool WtCelwiPwD = false;
      bool IwbLQrQcoU = false;
      bool aStNJFCjAP = false;
      bool wolSSAdxuJ = false;
      bool RLiDewEWKa = false;
      bool cqAXcEzoUf = false;
      bool tyOfHTKJrP = false;
      bool OSgfCOjphN = false;
      string RDaHQRWOSF;
      string tXtmqqDyYJ;
      string SLVWyMBCDW;
      string cbwDiStKBb;
      string RrRrcOtXZT;
      string EbicUFhEJD;
      string PTKwcRaqEY;
      string wswwratctj;
      string SdbjRAsShc;
      string jpAxMygUPK;
      string mDSBWKelks;
      string LFJZklqadb;
      string YHIanGrzjt;
      string sYMjwOKaNH;
      string UGhoRegaLZ;
      string GGpnleurMQ;
      string SfCqzlrZdW;
      string aQMWHRZTJJ;
      string YRmJmmiYxQ;
      string TSNxnoDpoe;
      if(RDaHQRWOSF == mDSBWKelks){mHxozpsTfU = true;}
      else if(mDSBWKelks == RDaHQRWOSF){tfbgFBbeHn = true;}
      if(tXtmqqDyYJ == LFJZklqadb){FbhDqBrsEM = true;}
      else if(LFJZklqadb == tXtmqqDyYJ){sghaStTorD = true;}
      if(SLVWyMBCDW == YHIanGrzjt){DSbMDICPhR = true;}
      else if(YHIanGrzjt == SLVWyMBCDW){WtCelwiPwD = true;}
      if(cbwDiStKBb == sYMjwOKaNH){NjedVRTxJx = true;}
      else if(sYMjwOKaNH == cbwDiStKBb){IwbLQrQcoU = true;}
      if(RrRrcOtXZT == UGhoRegaLZ){sPrcLqjJGm = true;}
      else if(UGhoRegaLZ == RrRrcOtXZT){aStNJFCjAP = true;}
      if(EbicUFhEJD == GGpnleurMQ){wKlbbTejlq = true;}
      else if(GGpnleurMQ == EbicUFhEJD){wolSSAdxuJ = true;}
      if(PTKwcRaqEY == SfCqzlrZdW){mdkOGUxEgY = true;}
      else if(SfCqzlrZdW == PTKwcRaqEY){RLiDewEWKa = true;}
      if(wswwratctj == aQMWHRZTJJ){gtiGTmayBL = true;}
      if(SdbjRAsShc == YRmJmmiYxQ){XsJuVCyCBC = true;}
      if(jpAxMygUPK == TSNxnoDpoe){ljLSKPedWp = true;}
      while(aQMWHRZTJJ == wswwratctj){cqAXcEzoUf = true;}
      while(YRmJmmiYxQ == YRmJmmiYxQ){tyOfHTKJrP = true;}
      while(TSNxnoDpoe == TSNxnoDpoe){OSgfCOjphN = true;}
      if(mHxozpsTfU == true){mHxozpsTfU = false;}
      if(FbhDqBrsEM == true){FbhDqBrsEM = false;}
      if(DSbMDICPhR == true){DSbMDICPhR = false;}
      if(NjedVRTxJx == true){NjedVRTxJx = false;}
      if(sPrcLqjJGm == true){sPrcLqjJGm = false;}
      if(wKlbbTejlq == true){wKlbbTejlq = false;}
      if(mdkOGUxEgY == true){mdkOGUxEgY = false;}
      if(gtiGTmayBL == true){gtiGTmayBL = false;}
      if(XsJuVCyCBC == true){XsJuVCyCBC = false;}
      if(ljLSKPedWp == true){ljLSKPedWp = false;}
      if(tfbgFBbeHn == true){tfbgFBbeHn = false;}
      if(sghaStTorD == true){sghaStTorD = false;}
      if(WtCelwiPwD == true){WtCelwiPwD = false;}
      if(IwbLQrQcoU == true){IwbLQrQcoU = false;}
      if(aStNJFCjAP == true){aStNJFCjAP = false;}
      if(wolSSAdxuJ == true){wolSSAdxuJ = false;}
      if(RLiDewEWKa == true){RLiDewEWKa = false;}
      if(cqAXcEzoUf == true){cqAXcEzoUf = false;}
      if(tyOfHTKJrP == true){tyOfHTKJrP = false;}
      if(OSgfCOjphN == true){OSgfCOjphN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSBTLQKHKE
{ 
  void hrjcBIHmnG()
  { 
      bool OqVrXFjgVL = false;
      bool ySqwoBTspF = false;
      bool bftZySOBYe = false;
      bool DUDIYDUFzJ = false;
      bool KSBpztVgRt = false;
      bool DNmrchxwtE = false;
      bool qiIqHcPiXl = false;
      bool fNsgtIeDZD = false;
      bool wgieaohKfq = false;
      bool FYLtSbKKiV = false;
      bool elJeNpUFxT = false;
      bool CtVpIJzcPR = false;
      bool tEDggHBzNS = false;
      bool xTTDYKXEQj = false;
      bool UcMLnLCUlJ = false;
      bool bhtRbZicyG = false;
      bool oUreVhZSRy = false;
      bool kuMewRrqrU = false;
      bool FfNEpPZCby = false;
      bool auGKuAjgoF = false;
      string utXuHsbYTX;
      string YhzOKuJkug;
      string fAeZyNaSQs;
      string XdtJHjFKnT;
      string NAlQyVLIPH;
      string bPRnUtPxws;
      string RIIZztnpHa;
      string pywbSfONbc;
      string CSCIRHMFnM;
      string UHNuBErLQD;
      string gUAoRcSpUo;
      string eBUTqyFzIr;
      string giBuFhkBZO;
      string nDxYwgSNqn;
      string oWjzgSmtDD;
      string yrCYVxTFij;
      string rRPGBbEwXK;
      string frIUCKyBNm;
      string tqyWPuAXCy;
      string MNdHuXGdyE;
      if(utXuHsbYTX == gUAoRcSpUo){OqVrXFjgVL = true;}
      else if(gUAoRcSpUo == utXuHsbYTX){elJeNpUFxT = true;}
      if(YhzOKuJkug == eBUTqyFzIr){ySqwoBTspF = true;}
      else if(eBUTqyFzIr == YhzOKuJkug){CtVpIJzcPR = true;}
      if(fAeZyNaSQs == giBuFhkBZO){bftZySOBYe = true;}
      else if(giBuFhkBZO == fAeZyNaSQs){tEDggHBzNS = true;}
      if(XdtJHjFKnT == nDxYwgSNqn){DUDIYDUFzJ = true;}
      else if(nDxYwgSNqn == XdtJHjFKnT){xTTDYKXEQj = true;}
      if(NAlQyVLIPH == oWjzgSmtDD){KSBpztVgRt = true;}
      else if(oWjzgSmtDD == NAlQyVLIPH){UcMLnLCUlJ = true;}
      if(bPRnUtPxws == yrCYVxTFij){DNmrchxwtE = true;}
      else if(yrCYVxTFij == bPRnUtPxws){bhtRbZicyG = true;}
      if(RIIZztnpHa == rRPGBbEwXK){qiIqHcPiXl = true;}
      else if(rRPGBbEwXK == RIIZztnpHa){oUreVhZSRy = true;}
      if(pywbSfONbc == frIUCKyBNm){fNsgtIeDZD = true;}
      if(CSCIRHMFnM == tqyWPuAXCy){wgieaohKfq = true;}
      if(UHNuBErLQD == MNdHuXGdyE){FYLtSbKKiV = true;}
      while(frIUCKyBNm == pywbSfONbc){kuMewRrqrU = true;}
      while(tqyWPuAXCy == tqyWPuAXCy){FfNEpPZCby = true;}
      while(MNdHuXGdyE == MNdHuXGdyE){auGKuAjgoF = true;}
      if(OqVrXFjgVL == true){OqVrXFjgVL = false;}
      if(ySqwoBTspF == true){ySqwoBTspF = false;}
      if(bftZySOBYe == true){bftZySOBYe = false;}
      if(DUDIYDUFzJ == true){DUDIYDUFzJ = false;}
      if(KSBpztVgRt == true){KSBpztVgRt = false;}
      if(DNmrchxwtE == true){DNmrchxwtE = false;}
      if(qiIqHcPiXl == true){qiIqHcPiXl = false;}
      if(fNsgtIeDZD == true){fNsgtIeDZD = false;}
      if(wgieaohKfq == true){wgieaohKfq = false;}
      if(FYLtSbKKiV == true){FYLtSbKKiV = false;}
      if(elJeNpUFxT == true){elJeNpUFxT = false;}
      if(CtVpIJzcPR == true){CtVpIJzcPR = false;}
      if(tEDggHBzNS == true){tEDggHBzNS = false;}
      if(xTTDYKXEQj == true){xTTDYKXEQj = false;}
      if(UcMLnLCUlJ == true){UcMLnLCUlJ = false;}
      if(bhtRbZicyG == true){bhtRbZicyG = false;}
      if(oUreVhZSRy == true){oUreVhZSRy = false;}
      if(kuMewRrqrU == true){kuMewRrqrU = false;}
      if(FfNEpPZCby == true){FfNEpPZCby = false;}
      if(auGKuAjgoF == true){auGKuAjgoF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVRFBFDWND
{ 
  void ojnqRbjwPT()
  { 
      bool pgKmmJEqFm = false;
      bool GAlXJtdbiu = false;
      bool pBoCAAFWSB = false;
      bool hxYHMiWcFO = false;
      bool GGnxgodgxa = false;
      bool jHBVDorHml = false;
      bool DhYDFJaeLa = false;
      bool WAVToiMqVK = false;
      bool VYZqRauDEW = false;
      bool pPpTLYhkrW = false;
      bool NzVVDikhgT = false;
      bool bAkbPeIgld = false;
      bool OXZnjHKCIQ = false;
      bool AbzyxVCDmh = false;
      bool pNWjtpdNDf = false;
      bool PByNIpZglw = false;
      bool YhYQSABles = false;
      bool bFsEmABpst = false;
      bool dxybAzdkpG = false;
      bool wVQqIHnGQt = false;
      string PnKmxZhTUH;
      string zQJnwylKwC;
      string cFWeakcuaZ;
      string kJxSIMDhNX;
      string ymLPOixCzt;
      string PloErKRfLL;
      string xmruWoTpfj;
      string uEwXEosHPr;
      string naugJyUsax;
      string uWVBaLuQsZ;
      string PGVPyLoQAC;
      string QJPTXWqLlX;
      string UZPhnXiuxs;
      string tcOpcgEfhx;
      string IDrYgkHBdE;
      string TieUFoqmaa;
      string btTHHnuZqp;
      string RKdnPRhpBC;
      string QhQrYLxtkn;
      string pQFHVNikRs;
      if(PnKmxZhTUH == PGVPyLoQAC){pgKmmJEqFm = true;}
      else if(PGVPyLoQAC == PnKmxZhTUH){NzVVDikhgT = true;}
      if(zQJnwylKwC == QJPTXWqLlX){GAlXJtdbiu = true;}
      else if(QJPTXWqLlX == zQJnwylKwC){bAkbPeIgld = true;}
      if(cFWeakcuaZ == UZPhnXiuxs){pBoCAAFWSB = true;}
      else if(UZPhnXiuxs == cFWeakcuaZ){OXZnjHKCIQ = true;}
      if(kJxSIMDhNX == tcOpcgEfhx){hxYHMiWcFO = true;}
      else if(tcOpcgEfhx == kJxSIMDhNX){AbzyxVCDmh = true;}
      if(ymLPOixCzt == IDrYgkHBdE){GGnxgodgxa = true;}
      else if(IDrYgkHBdE == ymLPOixCzt){pNWjtpdNDf = true;}
      if(PloErKRfLL == TieUFoqmaa){jHBVDorHml = true;}
      else if(TieUFoqmaa == PloErKRfLL){PByNIpZglw = true;}
      if(xmruWoTpfj == btTHHnuZqp){DhYDFJaeLa = true;}
      else if(btTHHnuZqp == xmruWoTpfj){YhYQSABles = true;}
      if(uEwXEosHPr == RKdnPRhpBC){WAVToiMqVK = true;}
      if(naugJyUsax == QhQrYLxtkn){VYZqRauDEW = true;}
      if(uWVBaLuQsZ == pQFHVNikRs){pPpTLYhkrW = true;}
      while(RKdnPRhpBC == uEwXEosHPr){bFsEmABpst = true;}
      while(QhQrYLxtkn == QhQrYLxtkn){dxybAzdkpG = true;}
      while(pQFHVNikRs == pQFHVNikRs){wVQqIHnGQt = true;}
      if(pgKmmJEqFm == true){pgKmmJEqFm = false;}
      if(GAlXJtdbiu == true){GAlXJtdbiu = false;}
      if(pBoCAAFWSB == true){pBoCAAFWSB = false;}
      if(hxYHMiWcFO == true){hxYHMiWcFO = false;}
      if(GGnxgodgxa == true){GGnxgodgxa = false;}
      if(jHBVDorHml == true){jHBVDorHml = false;}
      if(DhYDFJaeLa == true){DhYDFJaeLa = false;}
      if(WAVToiMqVK == true){WAVToiMqVK = false;}
      if(VYZqRauDEW == true){VYZqRauDEW = false;}
      if(pPpTLYhkrW == true){pPpTLYhkrW = false;}
      if(NzVVDikhgT == true){NzVVDikhgT = false;}
      if(bAkbPeIgld == true){bAkbPeIgld = false;}
      if(OXZnjHKCIQ == true){OXZnjHKCIQ = false;}
      if(AbzyxVCDmh == true){AbzyxVCDmh = false;}
      if(pNWjtpdNDf == true){pNWjtpdNDf = false;}
      if(PByNIpZglw == true){PByNIpZglw = false;}
      if(YhYQSABles == true){YhYQSABles = false;}
      if(bFsEmABpst == true){bFsEmABpst = false;}
      if(dxybAzdkpG == true){dxybAzdkpG = false;}
      if(wVQqIHnGQt == true){wVQqIHnGQt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSPHQNVSBH
{ 
  void QRKsBWpxWa()
  { 
      bool sHAAqHDmDH = false;
      bool XYqtYlqBsQ = false;
      bool qbHEMgEcHj = false;
      bool NrWHBMGYXx = false;
      bool VQEcHqpcQJ = false;
      bool iBgheQAunJ = false;
      bool DZeSteCjrM = false;
      bool fRcwtaWexU = false;
      bool qaLxALLncj = false;
      bool MKkNtukkhb = false;
      bool oFjDdRXjmD = false;
      bool tUySRbOgRi = false;
      bool TNGHAUfPCy = false;
      bool pkwVekqITi = false;
      bool maBZpqMSwR = false;
      bool gDTzHbzbDJ = false;
      bool kIhnNIYbmf = false;
      bool kFNiwsLgRJ = false;
      bool HNSjRlRxND = false;
      bool lOFJxdsNLh = false;
      string ESjxKXFpJY;
      string SMOgiCetyw;
      string niXOoFmqoq;
      string HeJcccayWH;
      string kWDiukpTRq;
      string QsaxCUtVIE;
      string jNASRmDkDF;
      string agWqLRenSD;
      string PSYyZNDLZH;
      string hFoSWWWjRI;
      string hEQMPjVjlk;
      string pFDFnQnBsD;
      string jqKuWVqETn;
      string ttWJUKCMio;
      string rSYoRbBjdF;
      string iVqOYptUos;
      string sRPypuisjc;
      string ObRELQSVdt;
      string UGZOEYDHke;
      string QgWowaDZyV;
      if(ESjxKXFpJY == hEQMPjVjlk){sHAAqHDmDH = true;}
      else if(hEQMPjVjlk == ESjxKXFpJY){oFjDdRXjmD = true;}
      if(SMOgiCetyw == pFDFnQnBsD){XYqtYlqBsQ = true;}
      else if(pFDFnQnBsD == SMOgiCetyw){tUySRbOgRi = true;}
      if(niXOoFmqoq == jqKuWVqETn){qbHEMgEcHj = true;}
      else if(jqKuWVqETn == niXOoFmqoq){TNGHAUfPCy = true;}
      if(HeJcccayWH == ttWJUKCMio){NrWHBMGYXx = true;}
      else if(ttWJUKCMio == HeJcccayWH){pkwVekqITi = true;}
      if(kWDiukpTRq == rSYoRbBjdF){VQEcHqpcQJ = true;}
      else if(rSYoRbBjdF == kWDiukpTRq){maBZpqMSwR = true;}
      if(QsaxCUtVIE == iVqOYptUos){iBgheQAunJ = true;}
      else if(iVqOYptUos == QsaxCUtVIE){gDTzHbzbDJ = true;}
      if(jNASRmDkDF == sRPypuisjc){DZeSteCjrM = true;}
      else if(sRPypuisjc == jNASRmDkDF){kIhnNIYbmf = true;}
      if(agWqLRenSD == ObRELQSVdt){fRcwtaWexU = true;}
      if(PSYyZNDLZH == UGZOEYDHke){qaLxALLncj = true;}
      if(hFoSWWWjRI == QgWowaDZyV){MKkNtukkhb = true;}
      while(ObRELQSVdt == agWqLRenSD){kFNiwsLgRJ = true;}
      while(UGZOEYDHke == UGZOEYDHke){HNSjRlRxND = true;}
      while(QgWowaDZyV == QgWowaDZyV){lOFJxdsNLh = true;}
      if(sHAAqHDmDH == true){sHAAqHDmDH = false;}
      if(XYqtYlqBsQ == true){XYqtYlqBsQ = false;}
      if(qbHEMgEcHj == true){qbHEMgEcHj = false;}
      if(NrWHBMGYXx == true){NrWHBMGYXx = false;}
      if(VQEcHqpcQJ == true){VQEcHqpcQJ = false;}
      if(iBgheQAunJ == true){iBgheQAunJ = false;}
      if(DZeSteCjrM == true){DZeSteCjrM = false;}
      if(fRcwtaWexU == true){fRcwtaWexU = false;}
      if(qaLxALLncj == true){qaLxALLncj = false;}
      if(MKkNtukkhb == true){MKkNtukkhb = false;}
      if(oFjDdRXjmD == true){oFjDdRXjmD = false;}
      if(tUySRbOgRi == true){tUySRbOgRi = false;}
      if(TNGHAUfPCy == true){TNGHAUfPCy = false;}
      if(pkwVekqITi == true){pkwVekqITi = false;}
      if(maBZpqMSwR == true){maBZpqMSwR = false;}
      if(gDTzHbzbDJ == true){gDTzHbzbDJ = false;}
      if(kIhnNIYbmf == true){kIhnNIYbmf = false;}
      if(kFNiwsLgRJ == true){kFNiwsLgRJ = false;}
      if(HNSjRlRxND == true){HNSjRlRxND = false;}
      if(lOFJxdsNLh == true){lOFJxdsNLh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLWEGMIVRT
{ 
  void nHzBDFyiQA()
  { 
      bool uKlsbhXPDI = false;
      bool mdcgAGOLWQ = false;
      bool dLccfFuCCz = false;
      bool DsNAisDepI = false;
      bool HiiRUncEIj = false;
      bool dAKMUihJMV = false;
      bool mVNDEtQcyG = false;
      bool DjVOJucKHq = false;
      bool bpsSVDhAez = false;
      bool LsRTVkVfNa = false;
      bool XzGCftdwDZ = false;
      bool GWBVtwbuhB = false;
      bool MQyztKRCsX = false;
      bool ZwxgTcjqlb = false;
      bool YkxErnruZY = false;
      bool IaxLOHBGHV = false;
      bool bbDezJZTCQ = false;
      bool MjIGbaSsHG = false;
      bool SWcTOzzkSM = false;
      bool acjPzxhRFh = false;
      string NKctZapLej;
      string ZaXyRrllFR;
      string rYZreNpYzz;
      string etnVEOEsqS;
      string NUXXLXnAnM;
      string CxUXjnkkOM;
      string kQLeEfmCtD;
      string nrumDXBCfH;
      string ZpjmxhYPlQ;
      string dTeehwIrSf;
      string kkGkYJChTL;
      string mhEHmtgYhW;
      string GWQcZTNPEG;
      string PJiAVniyNn;
      string epuZcuPXrm;
      string PiKuYNUcLE;
      string wldNwdzEky;
      string LhKtrQapzd;
      string EoXRpfzmaH;
      string SGlIqrMhcz;
      if(NKctZapLej == kkGkYJChTL){uKlsbhXPDI = true;}
      else if(kkGkYJChTL == NKctZapLej){XzGCftdwDZ = true;}
      if(ZaXyRrllFR == mhEHmtgYhW){mdcgAGOLWQ = true;}
      else if(mhEHmtgYhW == ZaXyRrllFR){GWBVtwbuhB = true;}
      if(rYZreNpYzz == GWQcZTNPEG){dLccfFuCCz = true;}
      else if(GWQcZTNPEG == rYZreNpYzz){MQyztKRCsX = true;}
      if(etnVEOEsqS == PJiAVniyNn){DsNAisDepI = true;}
      else if(PJiAVniyNn == etnVEOEsqS){ZwxgTcjqlb = true;}
      if(NUXXLXnAnM == epuZcuPXrm){HiiRUncEIj = true;}
      else if(epuZcuPXrm == NUXXLXnAnM){YkxErnruZY = true;}
      if(CxUXjnkkOM == PiKuYNUcLE){dAKMUihJMV = true;}
      else if(PiKuYNUcLE == CxUXjnkkOM){IaxLOHBGHV = true;}
      if(kQLeEfmCtD == wldNwdzEky){mVNDEtQcyG = true;}
      else if(wldNwdzEky == kQLeEfmCtD){bbDezJZTCQ = true;}
      if(nrumDXBCfH == LhKtrQapzd){DjVOJucKHq = true;}
      if(ZpjmxhYPlQ == EoXRpfzmaH){bpsSVDhAez = true;}
      if(dTeehwIrSf == SGlIqrMhcz){LsRTVkVfNa = true;}
      while(LhKtrQapzd == nrumDXBCfH){MjIGbaSsHG = true;}
      while(EoXRpfzmaH == EoXRpfzmaH){SWcTOzzkSM = true;}
      while(SGlIqrMhcz == SGlIqrMhcz){acjPzxhRFh = true;}
      if(uKlsbhXPDI == true){uKlsbhXPDI = false;}
      if(mdcgAGOLWQ == true){mdcgAGOLWQ = false;}
      if(dLccfFuCCz == true){dLccfFuCCz = false;}
      if(DsNAisDepI == true){DsNAisDepI = false;}
      if(HiiRUncEIj == true){HiiRUncEIj = false;}
      if(dAKMUihJMV == true){dAKMUihJMV = false;}
      if(mVNDEtQcyG == true){mVNDEtQcyG = false;}
      if(DjVOJucKHq == true){DjVOJucKHq = false;}
      if(bpsSVDhAez == true){bpsSVDhAez = false;}
      if(LsRTVkVfNa == true){LsRTVkVfNa = false;}
      if(XzGCftdwDZ == true){XzGCftdwDZ = false;}
      if(GWBVtwbuhB == true){GWBVtwbuhB = false;}
      if(MQyztKRCsX == true){MQyztKRCsX = false;}
      if(ZwxgTcjqlb == true){ZwxgTcjqlb = false;}
      if(YkxErnruZY == true){YkxErnruZY = false;}
      if(IaxLOHBGHV == true){IaxLOHBGHV = false;}
      if(bbDezJZTCQ == true){bbDezJZTCQ = false;}
      if(MjIGbaSsHG == true){MjIGbaSsHG = false;}
      if(SWcTOzzkSM == true){SWcTOzzkSM = false;}
      if(acjPzxhRFh == true){acjPzxhRFh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDDIYVKPXF
{ 
  void nbOkeNSoJX()
  { 
      bool eEnqdFIjtJ = false;
      bool TpWrZSnaiz = false;
      bool pgEomHlfVm = false;
      bool ruoenlMtSZ = false;
      bool xMMamjMiNF = false;
      bool eeNPGxzyEW = false;
      bool TcNGQYBqEn = false;
      bool GtIICcUcBD = false;
      bool tCRPINhYXp = false;
      bool lNowGUzFKO = false;
      bool hUdZzjWENd = false;
      bool cVwBbQKxyD = false;
      bool qbTOCrFLCg = false;
      bool dPSmUZYrQX = false;
      bool qdKtNPQnTp = false;
      bool JBGHXFBPXG = false;
      bool eKBgAMDJgC = false;
      bool rSfaLNRZBl = false;
      bool bRrMWbILPO = false;
      bool XIUKrfbdtA = false;
      string wqgmihiwYV;
      string ZscRkDtwVd;
      string PpeSjGQtSp;
      string IYLnFdqFRK;
      string JeyRmyMXGN;
      string swCjaFLNCc;
      string RodhNAgoLG;
      string MneLTkqNek;
      string ssnFwLWbMz;
      string ScCnsUBPEl;
      string RXLzAEQqPp;
      string OyiRiXBXlB;
      string dEbMnjlqRz;
      string jaJsTVhnEq;
      string teMWjTtkEU;
      string ScdCIMuyLQ;
      string SZYPGmooxN;
      string pNTtHyrFbT;
      string pAlxfGxHkH;
      string ZibnXTGxPx;
      if(wqgmihiwYV == RXLzAEQqPp){eEnqdFIjtJ = true;}
      else if(RXLzAEQqPp == wqgmihiwYV){hUdZzjWENd = true;}
      if(ZscRkDtwVd == OyiRiXBXlB){TpWrZSnaiz = true;}
      else if(OyiRiXBXlB == ZscRkDtwVd){cVwBbQKxyD = true;}
      if(PpeSjGQtSp == dEbMnjlqRz){pgEomHlfVm = true;}
      else if(dEbMnjlqRz == PpeSjGQtSp){qbTOCrFLCg = true;}
      if(IYLnFdqFRK == jaJsTVhnEq){ruoenlMtSZ = true;}
      else if(jaJsTVhnEq == IYLnFdqFRK){dPSmUZYrQX = true;}
      if(JeyRmyMXGN == teMWjTtkEU){xMMamjMiNF = true;}
      else if(teMWjTtkEU == JeyRmyMXGN){qdKtNPQnTp = true;}
      if(swCjaFLNCc == ScdCIMuyLQ){eeNPGxzyEW = true;}
      else if(ScdCIMuyLQ == swCjaFLNCc){JBGHXFBPXG = true;}
      if(RodhNAgoLG == SZYPGmooxN){TcNGQYBqEn = true;}
      else if(SZYPGmooxN == RodhNAgoLG){eKBgAMDJgC = true;}
      if(MneLTkqNek == pNTtHyrFbT){GtIICcUcBD = true;}
      if(ssnFwLWbMz == pAlxfGxHkH){tCRPINhYXp = true;}
      if(ScCnsUBPEl == ZibnXTGxPx){lNowGUzFKO = true;}
      while(pNTtHyrFbT == MneLTkqNek){rSfaLNRZBl = true;}
      while(pAlxfGxHkH == pAlxfGxHkH){bRrMWbILPO = true;}
      while(ZibnXTGxPx == ZibnXTGxPx){XIUKrfbdtA = true;}
      if(eEnqdFIjtJ == true){eEnqdFIjtJ = false;}
      if(TpWrZSnaiz == true){TpWrZSnaiz = false;}
      if(pgEomHlfVm == true){pgEomHlfVm = false;}
      if(ruoenlMtSZ == true){ruoenlMtSZ = false;}
      if(xMMamjMiNF == true){xMMamjMiNF = false;}
      if(eeNPGxzyEW == true){eeNPGxzyEW = false;}
      if(TcNGQYBqEn == true){TcNGQYBqEn = false;}
      if(GtIICcUcBD == true){GtIICcUcBD = false;}
      if(tCRPINhYXp == true){tCRPINhYXp = false;}
      if(lNowGUzFKO == true){lNowGUzFKO = false;}
      if(hUdZzjWENd == true){hUdZzjWENd = false;}
      if(cVwBbQKxyD == true){cVwBbQKxyD = false;}
      if(qbTOCrFLCg == true){qbTOCrFLCg = false;}
      if(dPSmUZYrQX == true){dPSmUZYrQX = false;}
      if(qdKtNPQnTp == true){qdKtNPQnTp = false;}
      if(JBGHXFBPXG == true){JBGHXFBPXG = false;}
      if(eKBgAMDJgC == true){eKBgAMDJgC = false;}
      if(rSfaLNRZBl == true){rSfaLNRZBl = false;}
      if(bRrMWbILPO == true){bRrMWbILPO = false;}
      if(XIUKrfbdtA == true){XIUKrfbdtA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FQWCDHBAVD
{ 
  void bcmaRQIPqN()
  { 
      bool mnBFfYmoWX = false;
      bool AFAajPIIfd = false;
      bool FqGRTSNCdi = false;
      bool bcJhmCGLgd = false;
      bool wOUBzQoFpt = false;
      bool NTPczwhjkN = false;
      bool KkKnwXwSng = false;
      bool IxbBgqVESD = false;
      bool cILjUHNghq = false;
      bool TWaSTLEgFa = false;
      bool UWRJkQrNwI = false;
      bool ZdQhjBYaSn = false;
      bool JOjxMlWIhU = false;
      bool loyqhGqBzE = false;
      bool PzkZQpFsiR = false;
      bool ldOQRGmTxy = false;
      bool tifaVkeZAd = false;
      bool KXbNYKdJfV = false;
      bool gcZQiIahZb = false;
      bool TWEAKfSJDf = false;
      string GJHDLpKNQA;
      string ywGtuljMRa;
      string IgJoNZeBsP;
      string PXJngYVzSn;
      string HOAMGNZGUE;
      string igBZHYzRpk;
      string LJTBjZlRMV;
      string QjtdTtgwiA;
      string AXfofiVjgI;
      string YDJgbxtycf;
      string aHsynymXFM;
      string rCipkmcdVB;
      string DCkEwMaMBW;
      string zhTCYsehBg;
      string wydTQWUSwo;
      string TPcbcYVoBa;
      string XZViNKifRq;
      string IucnFEXQnZ;
      string qHQMCjErZz;
      string WpgZJVcuGF;
      if(GJHDLpKNQA == aHsynymXFM){mnBFfYmoWX = true;}
      else if(aHsynymXFM == GJHDLpKNQA){UWRJkQrNwI = true;}
      if(ywGtuljMRa == rCipkmcdVB){AFAajPIIfd = true;}
      else if(rCipkmcdVB == ywGtuljMRa){ZdQhjBYaSn = true;}
      if(IgJoNZeBsP == DCkEwMaMBW){FqGRTSNCdi = true;}
      else if(DCkEwMaMBW == IgJoNZeBsP){JOjxMlWIhU = true;}
      if(PXJngYVzSn == zhTCYsehBg){bcJhmCGLgd = true;}
      else if(zhTCYsehBg == PXJngYVzSn){loyqhGqBzE = true;}
      if(HOAMGNZGUE == wydTQWUSwo){wOUBzQoFpt = true;}
      else if(wydTQWUSwo == HOAMGNZGUE){PzkZQpFsiR = true;}
      if(igBZHYzRpk == TPcbcYVoBa){NTPczwhjkN = true;}
      else if(TPcbcYVoBa == igBZHYzRpk){ldOQRGmTxy = true;}
      if(LJTBjZlRMV == XZViNKifRq){KkKnwXwSng = true;}
      else if(XZViNKifRq == LJTBjZlRMV){tifaVkeZAd = true;}
      if(QjtdTtgwiA == IucnFEXQnZ){IxbBgqVESD = true;}
      if(AXfofiVjgI == qHQMCjErZz){cILjUHNghq = true;}
      if(YDJgbxtycf == WpgZJVcuGF){TWaSTLEgFa = true;}
      while(IucnFEXQnZ == QjtdTtgwiA){KXbNYKdJfV = true;}
      while(qHQMCjErZz == qHQMCjErZz){gcZQiIahZb = true;}
      while(WpgZJVcuGF == WpgZJVcuGF){TWEAKfSJDf = true;}
      if(mnBFfYmoWX == true){mnBFfYmoWX = false;}
      if(AFAajPIIfd == true){AFAajPIIfd = false;}
      if(FqGRTSNCdi == true){FqGRTSNCdi = false;}
      if(bcJhmCGLgd == true){bcJhmCGLgd = false;}
      if(wOUBzQoFpt == true){wOUBzQoFpt = false;}
      if(NTPczwhjkN == true){NTPczwhjkN = false;}
      if(KkKnwXwSng == true){KkKnwXwSng = false;}
      if(IxbBgqVESD == true){IxbBgqVESD = false;}
      if(cILjUHNghq == true){cILjUHNghq = false;}
      if(TWaSTLEgFa == true){TWaSTLEgFa = false;}
      if(UWRJkQrNwI == true){UWRJkQrNwI = false;}
      if(ZdQhjBYaSn == true){ZdQhjBYaSn = false;}
      if(JOjxMlWIhU == true){JOjxMlWIhU = false;}
      if(loyqhGqBzE == true){loyqhGqBzE = false;}
      if(PzkZQpFsiR == true){PzkZQpFsiR = false;}
      if(ldOQRGmTxy == true){ldOQRGmTxy = false;}
      if(tifaVkeZAd == true){tifaVkeZAd = false;}
      if(KXbNYKdJfV == true){KXbNYKdJfV = false;}
      if(gcZQiIahZb == true){gcZQiIahZb = false;}
      if(TWEAKfSJDf == true){TWEAKfSJDf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRKLKODHLE
{ 
  void fOEMPdpPIB()
  { 
      bool aHGqNxbNme = false;
      bool brEaowduTn = false;
      bool uWbdBaZOwD = false;
      bool YyofTuSQhD = false;
      bool ZUmLEumzLh = false;
      bool XnRVRDebpl = false;
      bool WNQiGdDYHs = false;
      bool dMMQNZjPYG = false;
      bool mZCNejfSNP = false;
      bool QpaufMDDFa = false;
      bool qOrREKbBIr = false;
      bool TPCjywKCEV = false;
      bool ykKqcnlQjA = false;
      bool VgKyOYhkJT = false;
      bool IeKUuAmpxi = false;
      bool BAzjcGEAoP = false;
      bool YKQHWmFEUZ = false;
      bool OZsjMTZowb = false;
      bool AuTAyUhZVI = false;
      bool TgustyNDyI = false;
      string xLLLkXQYen;
      string JGwVKokfsc;
      string RBuGLunhzn;
      string ffpMpEgWpZ;
      string fZJrBQZOug;
      string ZQlQcuQEzp;
      string iiZpHdPieG;
      string HNoSwrrCEu;
      string VZlRNOtZjt;
      string mbWApwzSjX;
      string BpioYMaSTj;
      string DOAETJxIcs;
      string joykTfqobz;
      string sYRfsepwsA;
      string naFAqYbRfg;
      string yqpqnLqyVs;
      string VlqUpdxTLo;
      string SBObEIiysu;
      string DYIuACiZqg;
      string nraAeBjkJN;
      if(xLLLkXQYen == BpioYMaSTj){aHGqNxbNme = true;}
      else if(BpioYMaSTj == xLLLkXQYen){qOrREKbBIr = true;}
      if(JGwVKokfsc == DOAETJxIcs){brEaowduTn = true;}
      else if(DOAETJxIcs == JGwVKokfsc){TPCjywKCEV = true;}
      if(RBuGLunhzn == joykTfqobz){uWbdBaZOwD = true;}
      else if(joykTfqobz == RBuGLunhzn){ykKqcnlQjA = true;}
      if(ffpMpEgWpZ == sYRfsepwsA){YyofTuSQhD = true;}
      else if(sYRfsepwsA == ffpMpEgWpZ){VgKyOYhkJT = true;}
      if(fZJrBQZOug == naFAqYbRfg){ZUmLEumzLh = true;}
      else if(naFAqYbRfg == fZJrBQZOug){IeKUuAmpxi = true;}
      if(ZQlQcuQEzp == yqpqnLqyVs){XnRVRDebpl = true;}
      else if(yqpqnLqyVs == ZQlQcuQEzp){BAzjcGEAoP = true;}
      if(iiZpHdPieG == VlqUpdxTLo){WNQiGdDYHs = true;}
      else if(VlqUpdxTLo == iiZpHdPieG){YKQHWmFEUZ = true;}
      if(HNoSwrrCEu == SBObEIiysu){dMMQNZjPYG = true;}
      if(VZlRNOtZjt == DYIuACiZqg){mZCNejfSNP = true;}
      if(mbWApwzSjX == nraAeBjkJN){QpaufMDDFa = true;}
      while(SBObEIiysu == HNoSwrrCEu){OZsjMTZowb = true;}
      while(DYIuACiZqg == DYIuACiZqg){AuTAyUhZVI = true;}
      while(nraAeBjkJN == nraAeBjkJN){TgustyNDyI = true;}
      if(aHGqNxbNme == true){aHGqNxbNme = false;}
      if(brEaowduTn == true){brEaowduTn = false;}
      if(uWbdBaZOwD == true){uWbdBaZOwD = false;}
      if(YyofTuSQhD == true){YyofTuSQhD = false;}
      if(ZUmLEumzLh == true){ZUmLEumzLh = false;}
      if(XnRVRDebpl == true){XnRVRDebpl = false;}
      if(WNQiGdDYHs == true){WNQiGdDYHs = false;}
      if(dMMQNZjPYG == true){dMMQNZjPYG = false;}
      if(mZCNejfSNP == true){mZCNejfSNP = false;}
      if(QpaufMDDFa == true){QpaufMDDFa = false;}
      if(qOrREKbBIr == true){qOrREKbBIr = false;}
      if(TPCjywKCEV == true){TPCjywKCEV = false;}
      if(ykKqcnlQjA == true){ykKqcnlQjA = false;}
      if(VgKyOYhkJT == true){VgKyOYhkJT = false;}
      if(IeKUuAmpxi == true){IeKUuAmpxi = false;}
      if(BAzjcGEAoP == true){BAzjcGEAoP = false;}
      if(YKQHWmFEUZ == true){YKQHWmFEUZ = false;}
      if(OZsjMTZowb == true){OZsjMTZowb = false;}
      if(AuTAyUhZVI == true){AuTAyUhZVI = false;}
      if(TgustyNDyI == true){TgustyNDyI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQVNRPPPTN
{ 
  void kaGcTFSgJV()
  { 
      bool bTAGSKMuih = false;
      bool qbOunToqgx = false;
      bool QuCbtacnLR = false;
      bool llfMpbCSNE = false;
      bool AYyOjfxcHL = false;
      bool yGhLLgQXLq = false;
      bool hXjQwFuBEL = false;
      bool QVdcxrwnrO = false;
      bool dAgATeETAJ = false;
      bool LeGVVbogSe = false;
      bool juXutbcFOT = false;
      bool jcfxNhqixQ = false;
      bool BbAuAlPIGU = false;
      bool COUNehbkGr = false;
      bool CyFgYhyJHn = false;
      bool kGjBcHucuH = false;
      bool MTysRUHSRf = false;
      bool FGbFOCWTVR = false;
      bool mGARjueTjW = false;
      bool myozfhzLOD = false;
      string ekDaFeziXT;
      string eVjIAkPdnf;
      string nwSAadAoix;
      string OqbisWldLo;
      string IPHBMzcZQA;
      string PPJttiRDAb;
      string eKAaFntAPd;
      string zkRyXYnRna;
      string BaXhgzhhoJ;
      string FidiKxOguY;
      string FbKlBexLWU;
      string tzOYaDlRsG;
      string GMKFYPHhmZ;
      string JHVPUYQlgC;
      string BVKUPFTEIG;
      string LxmnRsRENk;
      string WOXwKlczEB;
      string mAkqFjBppS;
      string wDZgOMUhxb;
      string HLXwemyOJc;
      if(ekDaFeziXT == FbKlBexLWU){bTAGSKMuih = true;}
      else if(FbKlBexLWU == ekDaFeziXT){juXutbcFOT = true;}
      if(eVjIAkPdnf == tzOYaDlRsG){qbOunToqgx = true;}
      else if(tzOYaDlRsG == eVjIAkPdnf){jcfxNhqixQ = true;}
      if(nwSAadAoix == GMKFYPHhmZ){QuCbtacnLR = true;}
      else if(GMKFYPHhmZ == nwSAadAoix){BbAuAlPIGU = true;}
      if(OqbisWldLo == JHVPUYQlgC){llfMpbCSNE = true;}
      else if(JHVPUYQlgC == OqbisWldLo){COUNehbkGr = true;}
      if(IPHBMzcZQA == BVKUPFTEIG){AYyOjfxcHL = true;}
      else if(BVKUPFTEIG == IPHBMzcZQA){CyFgYhyJHn = true;}
      if(PPJttiRDAb == LxmnRsRENk){yGhLLgQXLq = true;}
      else if(LxmnRsRENk == PPJttiRDAb){kGjBcHucuH = true;}
      if(eKAaFntAPd == WOXwKlczEB){hXjQwFuBEL = true;}
      else if(WOXwKlczEB == eKAaFntAPd){MTysRUHSRf = true;}
      if(zkRyXYnRna == mAkqFjBppS){QVdcxrwnrO = true;}
      if(BaXhgzhhoJ == wDZgOMUhxb){dAgATeETAJ = true;}
      if(FidiKxOguY == HLXwemyOJc){LeGVVbogSe = true;}
      while(mAkqFjBppS == zkRyXYnRna){FGbFOCWTVR = true;}
      while(wDZgOMUhxb == wDZgOMUhxb){mGARjueTjW = true;}
      while(HLXwemyOJc == HLXwemyOJc){myozfhzLOD = true;}
      if(bTAGSKMuih == true){bTAGSKMuih = false;}
      if(qbOunToqgx == true){qbOunToqgx = false;}
      if(QuCbtacnLR == true){QuCbtacnLR = false;}
      if(llfMpbCSNE == true){llfMpbCSNE = false;}
      if(AYyOjfxcHL == true){AYyOjfxcHL = false;}
      if(yGhLLgQXLq == true){yGhLLgQXLq = false;}
      if(hXjQwFuBEL == true){hXjQwFuBEL = false;}
      if(QVdcxrwnrO == true){QVdcxrwnrO = false;}
      if(dAgATeETAJ == true){dAgATeETAJ = false;}
      if(LeGVVbogSe == true){LeGVVbogSe = false;}
      if(juXutbcFOT == true){juXutbcFOT = false;}
      if(jcfxNhqixQ == true){jcfxNhqixQ = false;}
      if(BbAuAlPIGU == true){BbAuAlPIGU = false;}
      if(COUNehbkGr == true){COUNehbkGr = false;}
      if(CyFgYhyJHn == true){CyFgYhyJHn = false;}
      if(kGjBcHucuH == true){kGjBcHucuH = false;}
      if(MTysRUHSRf == true){MTysRUHSRf = false;}
      if(FGbFOCWTVR == true){FGbFOCWTVR = false;}
      if(mGARjueTjW == true){mGARjueTjW = false;}
      if(myozfhzLOD == true){myozfhzLOD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CIXSIRNKDU
{ 
  void MpKgNoubnC()
  { 
      bool GUkfoPXwRw = false;
      bool HnJWSGewSQ = false;
      bool yhcneQNhoY = false;
      bool tEnplGeHjb = false;
      bool VIookAkHfp = false;
      bool JrXZZXrwAX = false;
      bool CpGrCDzTkM = false;
      bool bXMqupsmDe = false;
      bool eFBzPBfOPN = false;
      bool OhGLZeBwmh = false;
      bool ARVTNkfgej = false;
      bool eEsUswoGcA = false;
      bool WkDWxtQBRQ = false;
      bool nwAUeNjhld = false;
      bool VzifiJnkRc = false;
      bool puTlLONzVT = false;
      bool UePOuhEXpf = false;
      bool MGUyeWBXnn = false;
      bool FeinZscNJP = false;
      bool zkMRJqjUjB = false;
      string QoeVndkJjU;
      string GKuAxOwbJJ;
      string luYJyDMGiG;
      string kIFBollSLA;
      string UGSkUDtbMh;
      string hWExoUPVXj;
      string RdadjxEsLK;
      string bdPIoecnot;
      string IktAXOEILT;
      string WQubipfnBX;
      string yBPBGEGuHK;
      string rbfcbgjaFV;
      string rugqmLhnZy;
      string znlRuHUrsS;
      string HJABbujSAB;
      string GFifeCTYOt;
      string WSUJKDoOgT;
      string MqglNiueOr;
      string bPnYqtFGlr;
      string nudzwnnpqY;
      if(QoeVndkJjU == yBPBGEGuHK){GUkfoPXwRw = true;}
      else if(yBPBGEGuHK == QoeVndkJjU){ARVTNkfgej = true;}
      if(GKuAxOwbJJ == rbfcbgjaFV){HnJWSGewSQ = true;}
      else if(rbfcbgjaFV == GKuAxOwbJJ){eEsUswoGcA = true;}
      if(luYJyDMGiG == rugqmLhnZy){yhcneQNhoY = true;}
      else if(rugqmLhnZy == luYJyDMGiG){WkDWxtQBRQ = true;}
      if(kIFBollSLA == znlRuHUrsS){tEnplGeHjb = true;}
      else if(znlRuHUrsS == kIFBollSLA){nwAUeNjhld = true;}
      if(UGSkUDtbMh == HJABbujSAB){VIookAkHfp = true;}
      else if(HJABbujSAB == UGSkUDtbMh){VzifiJnkRc = true;}
      if(hWExoUPVXj == GFifeCTYOt){JrXZZXrwAX = true;}
      else if(GFifeCTYOt == hWExoUPVXj){puTlLONzVT = true;}
      if(RdadjxEsLK == WSUJKDoOgT){CpGrCDzTkM = true;}
      else if(WSUJKDoOgT == RdadjxEsLK){UePOuhEXpf = true;}
      if(bdPIoecnot == MqglNiueOr){bXMqupsmDe = true;}
      if(IktAXOEILT == bPnYqtFGlr){eFBzPBfOPN = true;}
      if(WQubipfnBX == nudzwnnpqY){OhGLZeBwmh = true;}
      while(MqglNiueOr == bdPIoecnot){MGUyeWBXnn = true;}
      while(bPnYqtFGlr == bPnYqtFGlr){FeinZscNJP = true;}
      while(nudzwnnpqY == nudzwnnpqY){zkMRJqjUjB = true;}
      if(GUkfoPXwRw == true){GUkfoPXwRw = false;}
      if(HnJWSGewSQ == true){HnJWSGewSQ = false;}
      if(yhcneQNhoY == true){yhcneQNhoY = false;}
      if(tEnplGeHjb == true){tEnplGeHjb = false;}
      if(VIookAkHfp == true){VIookAkHfp = false;}
      if(JrXZZXrwAX == true){JrXZZXrwAX = false;}
      if(CpGrCDzTkM == true){CpGrCDzTkM = false;}
      if(bXMqupsmDe == true){bXMqupsmDe = false;}
      if(eFBzPBfOPN == true){eFBzPBfOPN = false;}
      if(OhGLZeBwmh == true){OhGLZeBwmh = false;}
      if(ARVTNkfgej == true){ARVTNkfgej = false;}
      if(eEsUswoGcA == true){eEsUswoGcA = false;}
      if(WkDWxtQBRQ == true){WkDWxtQBRQ = false;}
      if(nwAUeNjhld == true){nwAUeNjhld = false;}
      if(VzifiJnkRc == true){VzifiJnkRc = false;}
      if(puTlLONzVT == true){puTlLONzVT = false;}
      if(UePOuhEXpf == true){UePOuhEXpf = false;}
      if(MGUyeWBXnn == true){MGUyeWBXnn = false;}
      if(FeinZscNJP == true){FeinZscNJP = false;}
      if(zkMRJqjUjB == true){zkMRJqjUjB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHGGVDTIMI
{ 
  void IxXJQuGedX()
  { 
      bool SNsVufpUia = false;
      bool NGsHxMajbS = false;
      bool dzNKncrTeZ = false;
      bool cNmPkhwBZw = false;
      bool QEfyptSjqn = false;
      bool xSXyBSAhhR = false;
      bool nVoIyATdVP = false;
      bool QYJeCZSPTt = false;
      bool KHcqcKooNR = false;
      bool hNTHItPXAp = false;
      bool ZoNbWYJsua = false;
      bool AkOmHfsyfn = false;
      bool KePDhDEBVI = false;
      bool KuPdTUtATE = false;
      bool BwsmRxzfAc = false;
      bool AQrLftZJtT = false;
      bool THWlQEVkSm = false;
      bool kseamOlclj = false;
      bool DXBrIsDDxZ = false;
      bool ukGzjsYGVN = false;
      string YmXCUaSMoE;
      string KGaqmoUeDh;
      string OjabiyWeqC;
      string fFnFBGTVia;
      string oOYaAKcGdO;
      string ycmnfoMwSW;
      string DmVmYFRUof;
      string VzucszLzbY;
      string UPBcDDRzYM;
      string tWCMWBskCt;
      string sIQxszgKug;
      string dMUtBmlsjU;
      string mRwclyxiFq;
      string GZxgeMzDjD;
      string VHEqihCHKi;
      string OzAhGaLmLt;
      string CyFEZDOnOo;
      string niJfyeNEtE;
      string woXVbGYPZE;
      string ALqoBXCzRe;
      if(YmXCUaSMoE == sIQxszgKug){SNsVufpUia = true;}
      else if(sIQxszgKug == YmXCUaSMoE){ZoNbWYJsua = true;}
      if(KGaqmoUeDh == dMUtBmlsjU){NGsHxMajbS = true;}
      else if(dMUtBmlsjU == KGaqmoUeDh){AkOmHfsyfn = true;}
      if(OjabiyWeqC == mRwclyxiFq){dzNKncrTeZ = true;}
      else if(mRwclyxiFq == OjabiyWeqC){KePDhDEBVI = true;}
      if(fFnFBGTVia == GZxgeMzDjD){cNmPkhwBZw = true;}
      else if(GZxgeMzDjD == fFnFBGTVia){KuPdTUtATE = true;}
      if(oOYaAKcGdO == VHEqihCHKi){QEfyptSjqn = true;}
      else if(VHEqihCHKi == oOYaAKcGdO){BwsmRxzfAc = true;}
      if(ycmnfoMwSW == OzAhGaLmLt){xSXyBSAhhR = true;}
      else if(OzAhGaLmLt == ycmnfoMwSW){AQrLftZJtT = true;}
      if(DmVmYFRUof == CyFEZDOnOo){nVoIyATdVP = true;}
      else if(CyFEZDOnOo == DmVmYFRUof){THWlQEVkSm = true;}
      if(VzucszLzbY == niJfyeNEtE){QYJeCZSPTt = true;}
      if(UPBcDDRzYM == woXVbGYPZE){KHcqcKooNR = true;}
      if(tWCMWBskCt == ALqoBXCzRe){hNTHItPXAp = true;}
      while(niJfyeNEtE == VzucszLzbY){kseamOlclj = true;}
      while(woXVbGYPZE == woXVbGYPZE){DXBrIsDDxZ = true;}
      while(ALqoBXCzRe == ALqoBXCzRe){ukGzjsYGVN = true;}
      if(SNsVufpUia == true){SNsVufpUia = false;}
      if(NGsHxMajbS == true){NGsHxMajbS = false;}
      if(dzNKncrTeZ == true){dzNKncrTeZ = false;}
      if(cNmPkhwBZw == true){cNmPkhwBZw = false;}
      if(QEfyptSjqn == true){QEfyptSjqn = false;}
      if(xSXyBSAhhR == true){xSXyBSAhhR = false;}
      if(nVoIyATdVP == true){nVoIyATdVP = false;}
      if(QYJeCZSPTt == true){QYJeCZSPTt = false;}
      if(KHcqcKooNR == true){KHcqcKooNR = false;}
      if(hNTHItPXAp == true){hNTHItPXAp = false;}
      if(ZoNbWYJsua == true){ZoNbWYJsua = false;}
      if(AkOmHfsyfn == true){AkOmHfsyfn = false;}
      if(KePDhDEBVI == true){KePDhDEBVI = false;}
      if(KuPdTUtATE == true){KuPdTUtATE = false;}
      if(BwsmRxzfAc == true){BwsmRxzfAc = false;}
      if(AQrLftZJtT == true){AQrLftZJtT = false;}
      if(THWlQEVkSm == true){THWlQEVkSm = false;}
      if(kseamOlclj == true){kseamOlclj = false;}
      if(DXBrIsDDxZ == true){DXBrIsDDxZ = false;}
      if(ukGzjsYGVN == true){ukGzjsYGVN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODCZDOHNRE
{ 
  void FdahYPYXYK()
  { 
      bool htttGEIRhG = false;
      bool clndHcFyUW = false;
      bool ufZzorUuCw = false;
      bool WOofuczwoq = false;
      bool EPGaFxVUNx = false;
      bool fQTjLBTtFN = false;
      bool iMPkjNwHhd = false;
      bool dIJdSeYztq = false;
      bool VAgEQGuEUt = false;
      bool JEpaIqAVqq = false;
      bool BOliTWGpRf = false;
      bool bUANqhfLTc = false;
      bool SqlnUYRhVb = false;
      bool eDIDpHOykt = false;
      bool zFmnRoEciZ = false;
      bool LoBNXJbxOt = false;
      bool EYToBXMwXj = false;
      bool TgZZdNDyWf = false;
      bool UozwQpCteg = false;
      bool eQipoakxms = false;
      string EauIEgHwIN;
      string QsRTxmfOeg;
      string tuQBBUFoWm;
      string MNrOBnchtZ;
      string PQsfpscSwP;
      string sZECAIKsGj;
      string bRYVBDBDRJ;
      string JyUERdBjLI;
      string rlrGslIpNr;
      string cjaKyxqXel;
      string rYAmFtFzjV;
      string HZgyqoYRbO;
      string tKoYfZWJFT;
      string ldFZPSlFBy;
      string gIFrkCCcSJ;
      string XYuPrhibGf;
      string XutQjdUHhY;
      string CTQchkExnc;
      string XtpuuMhogh;
      string iKyVakOoHH;
      if(EauIEgHwIN == rYAmFtFzjV){htttGEIRhG = true;}
      else if(rYAmFtFzjV == EauIEgHwIN){BOliTWGpRf = true;}
      if(QsRTxmfOeg == HZgyqoYRbO){clndHcFyUW = true;}
      else if(HZgyqoYRbO == QsRTxmfOeg){bUANqhfLTc = true;}
      if(tuQBBUFoWm == tKoYfZWJFT){ufZzorUuCw = true;}
      else if(tKoYfZWJFT == tuQBBUFoWm){SqlnUYRhVb = true;}
      if(MNrOBnchtZ == ldFZPSlFBy){WOofuczwoq = true;}
      else if(ldFZPSlFBy == MNrOBnchtZ){eDIDpHOykt = true;}
      if(PQsfpscSwP == gIFrkCCcSJ){EPGaFxVUNx = true;}
      else if(gIFrkCCcSJ == PQsfpscSwP){zFmnRoEciZ = true;}
      if(sZECAIKsGj == XYuPrhibGf){fQTjLBTtFN = true;}
      else if(XYuPrhibGf == sZECAIKsGj){LoBNXJbxOt = true;}
      if(bRYVBDBDRJ == XutQjdUHhY){iMPkjNwHhd = true;}
      else if(XutQjdUHhY == bRYVBDBDRJ){EYToBXMwXj = true;}
      if(JyUERdBjLI == CTQchkExnc){dIJdSeYztq = true;}
      if(rlrGslIpNr == XtpuuMhogh){VAgEQGuEUt = true;}
      if(cjaKyxqXel == iKyVakOoHH){JEpaIqAVqq = true;}
      while(CTQchkExnc == JyUERdBjLI){TgZZdNDyWf = true;}
      while(XtpuuMhogh == XtpuuMhogh){UozwQpCteg = true;}
      while(iKyVakOoHH == iKyVakOoHH){eQipoakxms = true;}
      if(htttGEIRhG == true){htttGEIRhG = false;}
      if(clndHcFyUW == true){clndHcFyUW = false;}
      if(ufZzorUuCw == true){ufZzorUuCw = false;}
      if(WOofuczwoq == true){WOofuczwoq = false;}
      if(EPGaFxVUNx == true){EPGaFxVUNx = false;}
      if(fQTjLBTtFN == true){fQTjLBTtFN = false;}
      if(iMPkjNwHhd == true){iMPkjNwHhd = false;}
      if(dIJdSeYztq == true){dIJdSeYztq = false;}
      if(VAgEQGuEUt == true){VAgEQGuEUt = false;}
      if(JEpaIqAVqq == true){JEpaIqAVqq = false;}
      if(BOliTWGpRf == true){BOliTWGpRf = false;}
      if(bUANqhfLTc == true){bUANqhfLTc = false;}
      if(SqlnUYRhVb == true){SqlnUYRhVb = false;}
      if(eDIDpHOykt == true){eDIDpHOykt = false;}
      if(zFmnRoEciZ == true){zFmnRoEciZ = false;}
      if(LoBNXJbxOt == true){LoBNXJbxOt = false;}
      if(EYToBXMwXj == true){EYToBXMwXj = false;}
      if(TgZZdNDyWf == true){TgZZdNDyWf = false;}
      if(UozwQpCteg == true){UozwQpCteg = false;}
      if(eQipoakxms == true){eQipoakxms = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJKOIAJEKR
{ 
  void xWGrwVVLPS()
  { 
      bool gJelmgGJIj = false;
      bool gpCdpKkNmf = false;
      bool MujucLttlF = false;
      bool VjbHucxFuK = false;
      bool SzUfDoElti = false;
      bool llDzulZiIa = false;
      bool mMXDOwNuhN = false;
      bool MeSbNNZErm = false;
      bool HHACSigcMJ = false;
      bool COxTXFbRQG = false;
      bool bJEfWHTakh = false;
      bool LVpUTeMUje = false;
      bool OkhXKygyEH = false;
      bool kImkLxDTfL = false;
      bool PGqdygXcAr = false;
      bool sGhkqpafVX = false;
      bool ZUWdxDhEIV = false;
      bool broXPIsEZc = false;
      bool aEyLNdaBsV = false;
      bool WWyIltjNgu = false;
      string BElTBuRVZp;
      string PBGblYiCic;
      string FblUtzHZoF;
      string yOOMcLwKip;
      string RNXHZshPOB;
      string yieaKZRQZC;
      string mrgUrBlsza;
      string bXSsKrDdtA;
      string QrKmGPinCC;
      string sfkgCZfDOY;
      string HnQnYZPlQR;
      string WnVZluhsNc;
      string Syqwhwmlpj;
      string LzPVscbWNg;
      string AwWjfFJKtH;
      string rlplFIwTGc;
      string mcwfFWYAfI;
      string TKefcVaGQb;
      string lbqhrZJdPj;
      string fHQktWAqeI;
      if(BElTBuRVZp == HnQnYZPlQR){gJelmgGJIj = true;}
      else if(HnQnYZPlQR == BElTBuRVZp){bJEfWHTakh = true;}
      if(PBGblYiCic == WnVZluhsNc){gpCdpKkNmf = true;}
      else if(WnVZluhsNc == PBGblYiCic){LVpUTeMUje = true;}
      if(FblUtzHZoF == Syqwhwmlpj){MujucLttlF = true;}
      else if(Syqwhwmlpj == FblUtzHZoF){OkhXKygyEH = true;}
      if(yOOMcLwKip == LzPVscbWNg){VjbHucxFuK = true;}
      else if(LzPVscbWNg == yOOMcLwKip){kImkLxDTfL = true;}
      if(RNXHZshPOB == AwWjfFJKtH){SzUfDoElti = true;}
      else if(AwWjfFJKtH == RNXHZshPOB){PGqdygXcAr = true;}
      if(yieaKZRQZC == rlplFIwTGc){llDzulZiIa = true;}
      else if(rlplFIwTGc == yieaKZRQZC){sGhkqpafVX = true;}
      if(mrgUrBlsza == mcwfFWYAfI){mMXDOwNuhN = true;}
      else if(mcwfFWYAfI == mrgUrBlsza){ZUWdxDhEIV = true;}
      if(bXSsKrDdtA == TKefcVaGQb){MeSbNNZErm = true;}
      if(QrKmGPinCC == lbqhrZJdPj){HHACSigcMJ = true;}
      if(sfkgCZfDOY == fHQktWAqeI){COxTXFbRQG = true;}
      while(TKefcVaGQb == bXSsKrDdtA){broXPIsEZc = true;}
      while(lbqhrZJdPj == lbqhrZJdPj){aEyLNdaBsV = true;}
      while(fHQktWAqeI == fHQktWAqeI){WWyIltjNgu = true;}
      if(gJelmgGJIj == true){gJelmgGJIj = false;}
      if(gpCdpKkNmf == true){gpCdpKkNmf = false;}
      if(MujucLttlF == true){MujucLttlF = false;}
      if(VjbHucxFuK == true){VjbHucxFuK = false;}
      if(SzUfDoElti == true){SzUfDoElti = false;}
      if(llDzulZiIa == true){llDzulZiIa = false;}
      if(mMXDOwNuhN == true){mMXDOwNuhN = false;}
      if(MeSbNNZErm == true){MeSbNNZErm = false;}
      if(HHACSigcMJ == true){HHACSigcMJ = false;}
      if(COxTXFbRQG == true){COxTXFbRQG = false;}
      if(bJEfWHTakh == true){bJEfWHTakh = false;}
      if(LVpUTeMUje == true){LVpUTeMUje = false;}
      if(OkhXKygyEH == true){OkhXKygyEH = false;}
      if(kImkLxDTfL == true){kImkLxDTfL = false;}
      if(PGqdygXcAr == true){PGqdygXcAr = false;}
      if(sGhkqpafVX == true){sGhkqpafVX = false;}
      if(ZUWdxDhEIV == true){ZUWdxDhEIV = false;}
      if(broXPIsEZc == true){broXPIsEZc = false;}
      if(aEyLNdaBsV == true){aEyLNdaBsV = false;}
      if(WWyIltjNgu == true){WWyIltjNgu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FUEUGQACGK
{ 
  void OEPzGSSWFs()
  { 
      bool CBsBzXtJFx = false;
      bool XQfpOoSYVu = false;
      bool eXhEkkOTup = false;
      bool RBYJyKsNNB = false;
      bool KABfsCClDK = false;
      bool TkgRydSnPN = false;
      bool JaOPeWqVqE = false;
      bool wFLTjdWCLi = false;
      bool hcQkVgTGLU = false;
      bool qEyzrjlkAV = false;
      bool KgtzNOYNgT = false;
      bool HQcfffKdty = false;
      bool DkJVMqGMaA = false;
      bool qkBoXBhQWH = false;
      bool IFYqNZbRSL = false;
      bool ZIqCSZWXlV = false;
      bool HLlgcVPmIe = false;
      bool ysGlpxLSIm = false;
      bool PosPaitzWx = false;
      bool dJeAzwSrOq = false;
      string ATrfTYKSAB;
      string jUbBinEgEr;
      string eBafqVcGuV;
      string dzieXxmVej;
      string diIDgRyDMB;
      string NFlzgysMoy;
      string uEXeWklxdl;
      string AiBTOwsWyY;
      string WZssHYNiyY;
      string DafgnZKcgw;
      string eBYZAeDRkk;
      string FVNPaVKeXy;
      string XCzFiZCUfo;
      string kPpCtVBTsb;
      string UuyMShNPFS;
      string OfFiYbCSqa;
      string bhluzofLVE;
      string TqlucbElmB;
      string MmOMZEKHcR;
      string SibRzmJDMc;
      if(ATrfTYKSAB == eBYZAeDRkk){CBsBzXtJFx = true;}
      else if(eBYZAeDRkk == ATrfTYKSAB){KgtzNOYNgT = true;}
      if(jUbBinEgEr == FVNPaVKeXy){XQfpOoSYVu = true;}
      else if(FVNPaVKeXy == jUbBinEgEr){HQcfffKdty = true;}
      if(eBafqVcGuV == XCzFiZCUfo){eXhEkkOTup = true;}
      else if(XCzFiZCUfo == eBafqVcGuV){DkJVMqGMaA = true;}
      if(dzieXxmVej == kPpCtVBTsb){RBYJyKsNNB = true;}
      else if(kPpCtVBTsb == dzieXxmVej){qkBoXBhQWH = true;}
      if(diIDgRyDMB == UuyMShNPFS){KABfsCClDK = true;}
      else if(UuyMShNPFS == diIDgRyDMB){IFYqNZbRSL = true;}
      if(NFlzgysMoy == OfFiYbCSqa){TkgRydSnPN = true;}
      else if(OfFiYbCSqa == NFlzgysMoy){ZIqCSZWXlV = true;}
      if(uEXeWklxdl == bhluzofLVE){JaOPeWqVqE = true;}
      else if(bhluzofLVE == uEXeWklxdl){HLlgcVPmIe = true;}
      if(AiBTOwsWyY == TqlucbElmB){wFLTjdWCLi = true;}
      if(WZssHYNiyY == MmOMZEKHcR){hcQkVgTGLU = true;}
      if(DafgnZKcgw == SibRzmJDMc){qEyzrjlkAV = true;}
      while(TqlucbElmB == AiBTOwsWyY){ysGlpxLSIm = true;}
      while(MmOMZEKHcR == MmOMZEKHcR){PosPaitzWx = true;}
      while(SibRzmJDMc == SibRzmJDMc){dJeAzwSrOq = true;}
      if(CBsBzXtJFx == true){CBsBzXtJFx = false;}
      if(XQfpOoSYVu == true){XQfpOoSYVu = false;}
      if(eXhEkkOTup == true){eXhEkkOTup = false;}
      if(RBYJyKsNNB == true){RBYJyKsNNB = false;}
      if(KABfsCClDK == true){KABfsCClDK = false;}
      if(TkgRydSnPN == true){TkgRydSnPN = false;}
      if(JaOPeWqVqE == true){JaOPeWqVqE = false;}
      if(wFLTjdWCLi == true){wFLTjdWCLi = false;}
      if(hcQkVgTGLU == true){hcQkVgTGLU = false;}
      if(qEyzrjlkAV == true){qEyzrjlkAV = false;}
      if(KgtzNOYNgT == true){KgtzNOYNgT = false;}
      if(HQcfffKdty == true){HQcfffKdty = false;}
      if(DkJVMqGMaA == true){DkJVMqGMaA = false;}
      if(qkBoXBhQWH == true){qkBoXBhQWH = false;}
      if(IFYqNZbRSL == true){IFYqNZbRSL = false;}
      if(ZIqCSZWXlV == true){ZIqCSZWXlV = false;}
      if(HLlgcVPmIe == true){HLlgcVPmIe = false;}
      if(ysGlpxLSIm == true){ysGlpxLSIm = false;}
      if(PosPaitzWx == true){PosPaitzWx = false;}
      if(dJeAzwSrOq == true){dJeAzwSrOq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQFJQDPIBC
{ 
  void ygAQcdaszo()
  { 
      bool JPaRSkafsR = false;
      bool coHASpatLp = false;
      bool wWebHbVKNS = false;
      bool pYINiGrWDo = false;
      bool QBAXZJuYNo = false;
      bool QbAqQljyJq = false;
      bool OQRaaDgtRL = false;
      bool yEqVYuWGCy = false;
      bool fxwYBOYRwx = false;
      bool WsMLZAiZxV = false;
      bool cBGCqMkeRV = false;
      bool PdwLLRTsYL = false;
      bool eOxToEqewY = false;
      bool LxJfVeptho = false;
      bool dtzZhrwBAH = false;
      bool fpAkpNDmNl = false;
      bool UFhrKSTQof = false;
      bool bZKjhkPWlw = false;
      bool IpensUwXoH = false;
      bool aDgwUXLGPO = false;
      string WXszaJwWdl;
      string WGJfctpmNq;
      string zVpElVyBsb;
      string jxhsfUOOPb;
      string pJHXEWDFUb;
      string HAXsiAgoME;
      string LudBCZXQAH;
      string faXlBpNSzP;
      string SrgQUjYoJe;
      string nZCKQueGVe;
      string ymFNugblqs;
      string lNowlSOMgR;
      string AiGUSGXMUG;
      string KHxURemSVm;
      string HmxQsZjFYy;
      string fSZDeOfjto;
      string IPQkheQUeG;
      string euqsKMkpbs;
      string WSnWZrhspC;
      string zDYferVLhN;
      if(WXszaJwWdl == ymFNugblqs){JPaRSkafsR = true;}
      else if(ymFNugblqs == WXszaJwWdl){cBGCqMkeRV = true;}
      if(WGJfctpmNq == lNowlSOMgR){coHASpatLp = true;}
      else if(lNowlSOMgR == WGJfctpmNq){PdwLLRTsYL = true;}
      if(zVpElVyBsb == AiGUSGXMUG){wWebHbVKNS = true;}
      else if(AiGUSGXMUG == zVpElVyBsb){eOxToEqewY = true;}
      if(jxhsfUOOPb == KHxURemSVm){pYINiGrWDo = true;}
      else if(KHxURemSVm == jxhsfUOOPb){LxJfVeptho = true;}
      if(pJHXEWDFUb == HmxQsZjFYy){QBAXZJuYNo = true;}
      else if(HmxQsZjFYy == pJHXEWDFUb){dtzZhrwBAH = true;}
      if(HAXsiAgoME == fSZDeOfjto){QbAqQljyJq = true;}
      else if(fSZDeOfjto == HAXsiAgoME){fpAkpNDmNl = true;}
      if(LudBCZXQAH == IPQkheQUeG){OQRaaDgtRL = true;}
      else if(IPQkheQUeG == LudBCZXQAH){UFhrKSTQof = true;}
      if(faXlBpNSzP == euqsKMkpbs){yEqVYuWGCy = true;}
      if(SrgQUjYoJe == WSnWZrhspC){fxwYBOYRwx = true;}
      if(nZCKQueGVe == zDYferVLhN){WsMLZAiZxV = true;}
      while(euqsKMkpbs == faXlBpNSzP){bZKjhkPWlw = true;}
      while(WSnWZrhspC == WSnWZrhspC){IpensUwXoH = true;}
      while(zDYferVLhN == zDYferVLhN){aDgwUXLGPO = true;}
      if(JPaRSkafsR == true){JPaRSkafsR = false;}
      if(coHASpatLp == true){coHASpatLp = false;}
      if(wWebHbVKNS == true){wWebHbVKNS = false;}
      if(pYINiGrWDo == true){pYINiGrWDo = false;}
      if(QBAXZJuYNo == true){QBAXZJuYNo = false;}
      if(QbAqQljyJq == true){QbAqQljyJq = false;}
      if(OQRaaDgtRL == true){OQRaaDgtRL = false;}
      if(yEqVYuWGCy == true){yEqVYuWGCy = false;}
      if(fxwYBOYRwx == true){fxwYBOYRwx = false;}
      if(WsMLZAiZxV == true){WsMLZAiZxV = false;}
      if(cBGCqMkeRV == true){cBGCqMkeRV = false;}
      if(PdwLLRTsYL == true){PdwLLRTsYL = false;}
      if(eOxToEqewY == true){eOxToEqewY = false;}
      if(LxJfVeptho == true){LxJfVeptho = false;}
      if(dtzZhrwBAH == true){dtzZhrwBAH = false;}
      if(fpAkpNDmNl == true){fpAkpNDmNl = false;}
      if(UFhrKSTQof == true){UFhrKSTQof = false;}
      if(bZKjhkPWlw == true){bZKjhkPWlw = false;}
      if(IpensUwXoH == true){IpensUwXoH = false;}
      if(aDgwUXLGPO == true){aDgwUXLGPO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCJQTRBBWH
{ 
  void IKNMUMNgXg()
  { 
      bool BkryyzPHES = false;
      bool sTOpJcVjrP = false;
      bool kzLKtscVPm = false;
      bool lsBqUPoAOj = false;
      bool UrzWrsFWCY = false;
      bool hReILBYgDE = false;
      bool VtrQfARWVs = false;
      bool mUVHurAnSB = false;
      bool mGTpFUOseS = false;
      bool qHxJNaAhqr = false;
      bool ahBJkNuWNS = false;
      bool BjOCQPaBLL = false;
      bool kYrCBeXMsU = false;
      bool rRxaaEFJFr = false;
      bool ZreLQGstry = false;
      bool AyVeGBpyHG = false;
      bool ohcrajmmbL = false;
      bool KQwTlssfku = false;
      bool kcUuUsuRTY = false;
      bool OGCzCqOmkg = false;
      string mBtRPYfQGB;
      string etkuQHxAIY;
      string JCjAFCowsh;
      string pTgbecfsei;
      string qYaWGkCqdY;
      string mswhTkRsMM;
      string jiXYLLMIQn;
      string aEVYgjaMsT;
      string zyRTuwWyIs;
      string KmgRzHBCLu;
      string XsZpyhXWAi;
      string KEArMlRDdP;
      string nNzWcnWDZZ;
      string hYAxuGXaVM;
      string XzxZiFmoEM;
      string pxYwHJsCNK;
      string LTxaAkECwG;
      string OphQqnQZnW;
      string AhyMikAEpk;
      string MUNLBDCWYx;
      if(mBtRPYfQGB == XsZpyhXWAi){BkryyzPHES = true;}
      else if(XsZpyhXWAi == mBtRPYfQGB){ahBJkNuWNS = true;}
      if(etkuQHxAIY == KEArMlRDdP){sTOpJcVjrP = true;}
      else if(KEArMlRDdP == etkuQHxAIY){BjOCQPaBLL = true;}
      if(JCjAFCowsh == nNzWcnWDZZ){kzLKtscVPm = true;}
      else if(nNzWcnWDZZ == JCjAFCowsh){kYrCBeXMsU = true;}
      if(pTgbecfsei == hYAxuGXaVM){lsBqUPoAOj = true;}
      else if(hYAxuGXaVM == pTgbecfsei){rRxaaEFJFr = true;}
      if(qYaWGkCqdY == XzxZiFmoEM){UrzWrsFWCY = true;}
      else if(XzxZiFmoEM == qYaWGkCqdY){ZreLQGstry = true;}
      if(mswhTkRsMM == pxYwHJsCNK){hReILBYgDE = true;}
      else if(pxYwHJsCNK == mswhTkRsMM){AyVeGBpyHG = true;}
      if(jiXYLLMIQn == LTxaAkECwG){VtrQfARWVs = true;}
      else if(LTxaAkECwG == jiXYLLMIQn){ohcrajmmbL = true;}
      if(aEVYgjaMsT == OphQqnQZnW){mUVHurAnSB = true;}
      if(zyRTuwWyIs == AhyMikAEpk){mGTpFUOseS = true;}
      if(KmgRzHBCLu == MUNLBDCWYx){qHxJNaAhqr = true;}
      while(OphQqnQZnW == aEVYgjaMsT){KQwTlssfku = true;}
      while(AhyMikAEpk == AhyMikAEpk){kcUuUsuRTY = true;}
      while(MUNLBDCWYx == MUNLBDCWYx){OGCzCqOmkg = true;}
      if(BkryyzPHES == true){BkryyzPHES = false;}
      if(sTOpJcVjrP == true){sTOpJcVjrP = false;}
      if(kzLKtscVPm == true){kzLKtscVPm = false;}
      if(lsBqUPoAOj == true){lsBqUPoAOj = false;}
      if(UrzWrsFWCY == true){UrzWrsFWCY = false;}
      if(hReILBYgDE == true){hReILBYgDE = false;}
      if(VtrQfARWVs == true){VtrQfARWVs = false;}
      if(mUVHurAnSB == true){mUVHurAnSB = false;}
      if(mGTpFUOseS == true){mGTpFUOseS = false;}
      if(qHxJNaAhqr == true){qHxJNaAhqr = false;}
      if(ahBJkNuWNS == true){ahBJkNuWNS = false;}
      if(BjOCQPaBLL == true){BjOCQPaBLL = false;}
      if(kYrCBeXMsU == true){kYrCBeXMsU = false;}
      if(rRxaaEFJFr == true){rRxaaEFJFr = false;}
      if(ZreLQGstry == true){ZreLQGstry = false;}
      if(AyVeGBpyHG == true){AyVeGBpyHG = false;}
      if(ohcrajmmbL == true){ohcrajmmbL = false;}
      if(KQwTlssfku == true){KQwTlssfku = false;}
      if(kcUuUsuRTY == true){kcUuUsuRTY = false;}
      if(OGCzCqOmkg == true){OGCzCqOmkg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTRMJEHSTU
{ 
  void ugKQCzxDyj()
  { 
      bool icrrkHWjZZ = false;
      bool acKsokWVyO = false;
      bool kGfKLaxgBj = false;
      bool hddrjDmsWD = false;
      bool ZxzAhZDnTi = false;
      bool suIoWcwgfK = false;
      bool KohprxyRJk = false;
      bool xdytomGfbl = false;
      bool XIMRplVnVG = false;
      bool HFMMsjOJIk = false;
      bool bkeikOwNAi = false;
      bool WQEtmBbPAF = false;
      bool bJuCdrQlBE = false;
      bool YwXqJlcdga = false;
      bool oHnmjpASYq = false;
      bool HyJCJRocEs = false;
      bool yKMuKZsNjA = false;
      bool XyiYPTVHRn = false;
      bool qyMJwZmUhr = false;
      bool xAYmcetrcJ = false;
      string NoYMNiZEnE;
      string yZfwLgXOmi;
      string SHEuiMIMPq;
      string DtuymgWekP;
      string YYICYupuYx;
      string zdkTOFjddA;
      string aMoxAEegIe;
      string JrcXKszCVm;
      string WMnSqZIajg;
      string wsBkoLjLBU;
      string QImtmGANJU;
      string GgIpdOYVFa;
      string uDxahQqriy;
      string JmBAWOYsej;
      string ZuROaOjLHZ;
      string mNFaZMKLLV;
      string PIdKKSfHTP;
      string oeqVAzlhAS;
      string gekILwhZaJ;
      string DNhJTQQHEH;
      if(NoYMNiZEnE == QImtmGANJU){icrrkHWjZZ = true;}
      else if(QImtmGANJU == NoYMNiZEnE){bkeikOwNAi = true;}
      if(yZfwLgXOmi == GgIpdOYVFa){acKsokWVyO = true;}
      else if(GgIpdOYVFa == yZfwLgXOmi){WQEtmBbPAF = true;}
      if(SHEuiMIMPq == uDxahQqriy){kGfKLaxgBj = true;}
      else if(uDxahQqriy == SHEuiMIMPq){bJuCdrQlBE = true;}
      if(DtuymgWekP == JmBAWOYsej){hddrjDmsWD = true;}
      else if(JmBAWOYsej == DtuymgWekP){YwXqJlcdga = true;}
      if(YYICYupuYx == ZuROaOjLHZ){ZxzAhZDnTi = true;}
      else if(ZuROaOjLHZ == YYICYupuYx){oHnmjpASYq = true;}
      if(zdkTOFjddA == mNFaZMKLLV){suIoWcwgfK = true;}
      else if(mNFaZMKLLV == zdkTOFjddA){HyJCJRocEs = true;}
      if(aMoxAEegIe == PIdKKSfHTP){KohprxyRJk = true;}
      else if(PIdKKSfHTP == aMoxAEegIe){yKMuKZsNjA = true;}
      if(JrcXKszCVm == oeqVAzlhAS){xdytomGfbl = true;}
      if(WMnSqZIajg == gekILwhZaJ){XIMRplVnVG = true;}
      if(wsBkoLjLBU == DNhJTQQHEH){HFMMsjOJIk = true;}
      while(oeqVAzlhAS == JrcXKszCVm){XyiYPTVHRn = true;}
      while(gekILwhZaJ == gekILwhZaJ){qyMJwZmUhr = true;}
      while(DNhJTQQHEH == DNhJTQQHEH){xAYmcetrcJ = true;}
      if(icrrkHWjZZ == true){icrrkHWjZZ = false;}
      if(acKsokWVyO == true){acKsokWVyO = false;}
      if(kGfKLaxgBj == true){kGfKLaxgBj = false;}
      if(hddrjDmsWD == true){hddrjDmsWD = false;}
      if(ZxzAhZDnTi == true){ZxzAhZDnTi = false;}
      if(suIoWcwgfK == true){suIoWcwgfK = false;}
      if(KohprxyRJk == true){KohprxyRJk = false;}
      if(xdytomGfbl == true){xdytomGfbl = false;}
      if(XIMRplVnVG == true){XIMRplVnVG = false;}
      if(HFMMsjOJIk == true){HFMMsjOJIk = false;}
      if(bkeikOwNAi == true){bkeikOwNAi = false;}
      if(WQEtmBbPAF == true){WQEtmBbPAF = false;}
      if(bJuCdrQlBE == true){bJuCdrQlBE = false;}
      if(YwXqJlcdga == true){YwXqJlcdga = false;}
      if(oHnmjpASYq == true){oHnmjpASYq = false;}
      if(HyJCJRocEs == true){HyJCJRocEs = false;}
      if(yKMuKZsNjA == true){yKMuKZsNjA = false;}
      if(XyiYPTVHRn == true){XyiYPTVHRn = false;}
      if(qyMJwZmUhr == true){qyMJwZmUhr = false;}
      if(xAYmcetrcJ == true){xAYmcetrcJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKQIGAAFCD
{ 
  void uryyogUZUz()
  { 
      bool PDWqNYuToM = false;
      bool tfpYhtjAIc = false;
      bool TnrdolRYbt = false;
      bool rEhcUMmOaE = false;
      bool TgACPlaTYL = false;
      bool CKBbRaLsBa = false;
      bool HWqtToxMEU = false;
      bool HUZDJlnoND = false;
      bool KyAQrgDGLs = false;
      bool BsMzxxoFha = false;
      bool nOODDhjySe = false;
      bool mVexPJVaCl = false;
      bool lpBKSNHZFM = false;
      bool xhHmPwiwMJ = false;
      bool xFnfFfOPjm = false;
      bool aODunxMDko = false;
      bool ZKrGhFNrhS = false;
      bool ZZNrogCUEm = false;
      bool zrpRkheMyR = false;
      bool ieLXjlMhyA = false;
      string zmIxhDopRw;
      string sKdJZCoSTH;
      string jYGWHCcmYp;
      string OrFQGOgFWT;
      string yeXOWXPdxt;
      string HpuJmZgloe;
      string aBQbhBFNCK;
      string UiuzJEArAj;
      string myoehXwudf;
      string guPqswNwgU;
      string RCamYXtuzh;
      string ZokFrbMlsJ;
      string EJiVcZTEGN;
      string pELeRkWCFK;
      string cBwwGrJKyR;
      string ibCWQHSFJy;
      string EpolqUcGmH;
      string EJfigDNmOj;
      string QJFndOBoOJ;
      string RRrHGlLJEk;
      if(zmIxhDopRw == RCamYXtuzh){PDWqNYuToM = true;}
      else if(RCamYXtuzh == zmIxhDopRw){nOODDhjySe = true;}
      if(sKdJZCoSTH == ZokFrbMlsJ){tfpYhtjAIc = true;}
      else if(ZokFrbMlsJ == sKdJZCoSTH){mVexPJVaCl = true;}
      if(jYGWHCcmYp == EJiVcZTEGN){TnrdolRYbt = true;}
      else if(EJiVcZTEGN == jYGWHCcmYp){lpBKSNHZFM = true;}
      if(OrFQGOgFWT == pELeRkWCFK){rEhcUMmOaE = true;}
      else if(pELeRkWCFK == OrFQGOgFWT){xhHmPwiwMJ = true;}
      if(yeXOWXPdxt == cBwwGrJKyR){TgACPlaTYL = true;}
      else if(cBwwGrJKyR == yeXOWXPdxt){xFnfFfOPjm = true;}
      if(HpuJmZgloe == ibCWQHSFJy){CKBbRaLsBa = true;}
      else if(ibCWQHSFJy == HpuJmZgloe){aODunxMDko = true;}
      if(aBQbhBFNCK == EpolqUcGmH){HWqtToxMEU = true;}
      else if(EpolqUcGmH == aBQbhBFNCK){ZKrGhFNrhS = true;}
      if(UiuzJEArAj == EJfigDNmOj){HUZDJlnoND = true;}
      if(myoehXwudf == QJFndOBoOJ){KyAQrgDGLs = true;}
      if(guPqswNwgU == RRrHGlLJEk){BsMzxxoFha = true;}
      while(EJfigDNmOj == UiuzJEArAj){ZZNrogCUEm = true;}
      while(QJFndOBoOJ == QJFndOBoOJ){zrpRkheMyR = true;}
      while(RRrHGlLJEk == RRrHGlLJEk){ieLXjlMhyA = true;}
      if(PDWqNYuToM == true){PDWqNYuToM = false;}
      if(tfpYhtjAIc == true){tfpYhtjAIc = false;}
      if(TnrdolRYbt == true){TnrdolRYbt = false;}
      if(rEhcUMmOaE == true){rEhcUMmOaE = false;}
      if(TgACPlaTYL == true){TgACPlaTYL = false;}
      if(CKBbRaLsBa == true){CKBbRaLsBa = false;}
      if(HWqtToxMEU == true){HWqtToxMEU = false;}
      if(HUZDJlnoND == true){HUZDJlnoND = false;}
      if(KyAQrgDGLs == true){KyAQrgDGLs = false;}
      if(BsMzxxoFha == true){BsMzxxoFha = false;}
      if(nOODDhjySe == true){nOODDhjySe = false;}
      if(mVexPJVaCl == true){mVexPJVaCl = false;}
      if(lpBKSNHZFM == true){lpBKSNHZFM = false;}
      if(xhHmPwiwMJ == true){xhHmPwiwMJ = false;}
      if(xFnfFfOPjm == true){xFnfFfOPjm = false;}
      if(aODunxMDko == true){aODunxMDko = false;}
      if(ZKrGhFNrhS == true){ZKrGhFNrhS = false;}
      if(ZZNrogCUEm == true){ZZNrogCUEm = false;}
      if(zrpRkheMyR == true){zrpRkheMyR = false;}
      if(ieLXjlMhyA == true){ieLXjlMhyA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDGBYRUXRT
{ 
  void yWzEumNpyf()
  { 
      bool YAdLbLWEmG = false;
      bool mhgZqngyHE = false;
      bool NhjnLpUkKC = false;
      bool oYqhNVRUOY = false;
      bool huWNrhstqS = false;
      bool iUFPjpPoAk = false;
      bool pltkRNpzLU = false;
      bool VLiiVSLWuc = false;
      bool wasqSTTbxX = false;
      bool FcUchwAkwe = false;
      bool rthVxWlWsR = false;
      bool dssWnOrCSx = false;
      bool tOBnOrqGAY = false;
      bool RaZQkCrWsu = false;
      bool hwifsMiynS = false;
      bool DySykdrsGE = false;
      bool ffWTACScll = false;
      bool VUIWPxfVtC = false;
      bool JrRgVTIbfH = false;
      bool JyPoOCZOfq = false;
      string yHuPccFsyG;
      string iwKOeUoFew;
      string DMfqRxenuS;
      string wmUneByVHw;
      string mDKNbsEmrK;
      string xhGlFkaExf;
      string xQyeKwaWjc;
      string VSxiIABSPX;
      string rqujVOfihs;
      string ZtXbzWEfCe;
      string RhDPodjXdF;
      string iIoZmFVOJw;
      string QrnpDbtVik;
      string uVPjFKnfuq;
      string dHFcKQFyns;
      string BpWFOZsMLM;
      string jNnrJMrETc;
      string RoSRSImKfl;
      string VwgpjFzJUf;
      string QaThHPTNTx;
      if(yHuPccFsyG == RhDPodjXdF){YAdLbLWEmG = true;}
      else if(RhDPodjXdF == yHuPccFsyG){rthVxWlWsR = true;}
      if(iwKOeUoFew == iIoZmFVOJw){mhgZqngyHE = true;}
      else if(iIoZmFVOJw == iwKOeUoFew){dssWnOrCSx = true;}
      if(DMfqRxenuS == QrnpDbtVik){NhjnLpUkKC = true;}
      else if(QrnpDbtVik == DMfqRxenuS){tOBnOrqGAY = true;}
      if(wmUneByVHw == uVPjFKnfuq){oYqhNVRUOY = true;}
      else if(uVPjFKnfuq == wmUneByVHw){RaZQkCrWsu = true;}
      if(mDKNbsEmrK == dHFcKQFyns){huWNrhstqS = true;}
      else if(dHFcKQFyns == mDKNbsEmrK){hwifsMiynS = true;}
      if(xhGlFkaExf == BpWFOZsMLM){iUFPjpPoAk = true;}
      else if(BpWFOZsMLM == xhGlFkaExf){DySykdrsGE = true;}
      if(xQyeKwaWjc == jNnrJMrETc){pltkRNpzLU = true;}
      else if(jNnrJMrETc == xQyeKwaWjc){ffWTACScll = true;}
      if(VSxiIABSPX == RoSRSImKfl){VLiiVSLWuc = true;}
      if(rqujVOfihs == VwgpjFzJUf){wasqSTTbxX = true;}
      if(ZtXbzWEfCe == QaThHPTNTx){FcUchwAkwe = true;}
      while(RoSRSImKfl == VSxiIABSPX){VUIWPxfVtC = true;}
      while(VwgpjFzJUf == VwgpjFzJUf){JrRgVTIbfH = true;}
      while(QaThHPTNTx == QaThHPTNTx){JyPoOCZOfq = true;}
      if(YAdLbLWEmG == true){YAdLbLWEmG = false;}
      if(mhgZqngyHE == true){mhgZqngyHE = false;}
      if(NhjnLpUkKC == true){NhjnLpUkKC = false;}
      if(oYqhNVRUOY == true){oYqhNVRUOY = false;}
      if(huWNrhstqS == true){huWNrhstqS = false;}
      if(iUFPjpPoAk == true){iUFPjpPoAk = false;}
      if(pltkRNpzLU == true){pltkRNpzLU = false;}
      if(VLiiVSLWuc == true){VLiiVSLWuc = false;}
      if(wasqSTTbxX == true){wasqSTTbxX = false;}
      if(FcUchwAkwe == true){FcUchwAkwe = false;}
      if(rthVxWlWsR == true){rthVxWlWsR = false;}
      if(dssWnOrCSx == true){dssWnOrCSx = false;}
      if(tOBnOrqGAY == true){tOBnOrqGAY = false;}
      if(RaZQkCrWsu == true){RaZQkCrWsu = false;}
      if(hwifsMiynS == true){hwifsMiynS = false;}
      if(DySykdrsGE == true){DySykdrsGE = false;}
      if(ffWTACScll == true){ffWTACScll = false;}
      if(VUIWPxfVtC == true){VUIWPxfVtC = false;}
      if(JrRgVTIbfH == true){JrRgVTIbfH = false;}
      if(JyPoOCZOfq == true){JyPoOCZOfq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMRBBQQEKI
{ 
  void lnmqYbTpKk()
  { 
      bool lWfJPrysHG = false;
      bool ZapXFRjxbX = false;
      bool LWhhiblQUp = false;
      bool TSDPoyEGaq = false;
      bool PHYDyrpcxH = false;
      bool DamAFOoxan = false;
      bool GgYRlGXaiH = false;
      bool NcWjIDxejp = false;
      bool kISNmseCJa = false;
      bool IGflkhiHQq = false;
      bool TPtpsZDCrC = false;
      bool RJNjCxOKes = false;
      bool aVQHyGwjzZ = false;
      bool UpNsWVOcTM = false;
      bool ocJHIysujm = false;
      bool SXbXPyylql = false;
      bool cTDRhawTNf = false;
      bool ilpSDyLJzz = false;
      bool NAzMGwNpcY = false;
      bool XckhiVZrZh = false;
      string gxuhFQioys;
      string mmGbnaRniQ;
      string CeFipSRXAa;
      string KSUqhGbSYj;
      string fFgkXmFdBK;
      string YsCOOBrLqm;
      string zKnWhTSPsh;
      string zzPzkwyULC;
      string NmVpBRPGcg;
      string OPbljUQJCD;
      string UpjTLZdDcR;
      string CWAnZLoyVQ;
      string ELmMSjXcOP;
      string foSIgWDBeb;
      string mMcKeqOmMX;
      string fRmkyJDXAa;
      string CAnMlMErGC;
      string ImTtcribgb;
      string UjQpjNBgJX;
      string TfBDYmXPYR;
      if(gxuhFQioys == UpjTLZdDcR){lWfJPrysHG = true;}
      else if(UpjTLZdDcR == gxuhFQioys){TPtpsZDCrC = true;}
      if(mmGbnaRniQ == CWAnZLoyVQ){ZapXFRjxbX = true;}
      else if(CWAnZLoyVQ == mmGbnaRniQ){RJNjCxOKes = true;}
      if(CeFipSRXAa == ELmMSjXcOP){LWhhiblQUp = true;}
      else if(ELmMSjXcOP == CeFipSRXAa){aVQHyGwjzZ = true;}
      if(KSUqhGbSYj == foSIgWDBeb){TSDPoyEGaq = true;}
      else if(foSIgWDBeb == KSUqhGbSYj){UpNsWVOcTM = true;}
      if(fFgkXmFdBK == mMcKeqOmMX){PHYDyrpcxH = true;}
      else if(mMcKeqOmMX == fFgkXmFdBK){ocJHIysujm = true;}
      if(YsCOOBrLqm == fRmkyJDXAa){DamAFOoxan = true;}
      else if(fRmkyJDXAa == YsCOOBrLqm){SXbXPyylql = true;}
      if(zKnWhTSPsh == CAnMlMErGC){GgYRlGXaiH = true;}
      else if(CAnMlMErGC == zKnWhTSPsh){cTDRhawTNf = true;}
      if(zzPzkwyULC == ImTtcribgb){NcWjIDxejp = true;}
      if(NmVpBRPGcg == UjQpjNBgJX){kISNmseCJa = true;}
      if(OPbljUQJCD == TfBDYmXPYR){IGflkhiHQq = true;}
      while(ImTtcribgb == zzPzkwyULC){ilpSDyLJzz = true;}
      while(UjQpjNBgJX == UjQpjNBgJX){NAzMGwNpcY = true;}
      while(TfBDYmXPYR == TfBDYmXPYR){XckhiVZrZh = true;}
      if(lWfJPrysHG == true){lWfJPrysHG = false;}
      if(ZapXFRjxbX == true){ZapXFRjxbX = false;}
      if(LWhhiblQUp == true){LWhhiblQUp = false;}
      if(TSDPoyEGaq == true){TSDPoyEGaq = false;}
      if(PHYDyrpcxH == true){PHYDyrpcxH = false;}
      if(DamAFOoxan == true){DamAFOoxan = false;}
      if(GgYRlGXaiH == true){GgYRlGXaiH = false;}
      if(NcWjIDxejp == true){NcWjIDxejp = false;}
      if(kISNmseCJa == true){kISNmseCJa = false;}
      if(IGflkhiHQq == true){IGflkhiHQq = false;}
      if(TPtpsZDCrC == true){TPtpsZDCrC = false;}
      if(RJNjCxOKes == true){RJNjCxOKes = false;}
      if(aVQHyGwjzZ == true){aVQHyGwjzZ = false;}
      if(UpNsWVOcTM == true){UpNsWVOcTM = false;}
      if(ocJHIysujm == true){ocJHIysujm = false;}
      if(SXbXPyylql == true){SXbXPyylql = false;}
      if(cTDRhawTNf == true){cTDRhawTNf = false;}
      if(ilpSDyLJzz == true){ilpSDyLJzz = false;}
      if(NAzMGwNpcY == true){NAzMGwNpcY = false;}
      if(XckhiVZrZh == true){XckhiVZrZh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AWIYZYTSKL
{ 
  void DoNrgQBjIg()
  { 
      bool WpbLhbwEkn = false;
      bool UcsFDIFPzO = false;
      bool pXTUpWgwNk = false;
      bool eAaVcFqykh = false;
      bool ILyncyXeZn = false;
      bool gcQfbyVGUL = false;
      bool uzqzJUCXbx = false;
      bool QHdRGdYerq = false;
      bool yBWYDCjute = false;
      bool ikcZmIUzeH = false;
      bool wACbWZyzYx = false;
      bool YqNcMscRwH = false;
      bool kHdxNfdEdy = false;
      bool JZzjuyztCd = false;
      bool DjVwFrWzMt = false;
      bool eCCXWnWFOq = false;
      bool usUanyrchO = false;
      bool tiPRDAkgqV = false;
      bool JdrjSGWaNG = false;
      bool aseLiJPuIH = false;
      string bVzslRBIKE;
      string aqohQRbkco;
      string cRtMajsTyO;
      string WZJxQHKQZe;
      string igrRMLaGsn;
      string BPXToJblSC;
      string XhKuhBgqQJ;
      string GLKxFwZbAO;
      string JmZJNHCoHG;
      string eXyWHBVwiL;
      string dipjgoEZOs;
      string jAkDskHBha;
      string zrjJdhNnpE;
      string ZdrojaxpbX;
      string DbaOWdltdW;
      string sUNILlyfFz;
      string bPiKTFHwSR;
      string nRYJXXQVmz;
      string uSJTKEPjcx;
      string bQjcwmrQtR;
      if(bVzslRBIKE == dipjgoEZOs){WpbLhbwEkn = true;}
      else if(dipjgoEZOs == bVzslRBIKE){wACbWZyzYx = true;}
      if(aqohQRbkco == jAkDskHBha){UcsFDIFPzO = true;}
      else if(jAkDskHBha == aqohQRbkco){YqNcMscRwH = true;}
      if(cRtMajsTyO == zrjJdhNnpE){pXTUpWgwNk = true;}
      else if(zrjJdhNnpE == cRtMajsTyO){kHdxNfdEdy = true;}
      if(WZJxQHKQZe == ZdrojaxpbX){eAaVcFqykh = true;}
      else if(ZdrojaxpbX == WZJxQHKQZe){JZzjuyztCd = true;}
      if(igrRMLaGsn == DbaOWdltdW){ILyncyXeZn = true;}
      else if(DbaOWdltdW == igrRMLaGsn){DjVwFrWzMt = true;}
      if(BPXToJblSC == sUNILlyfFz){gcQfbyVGUL = true;}
      else if(sUNILlyfFz == BPXToJblSC){eCCXWnWFOq = true;}
      if(XhKuhBgqQJ == bPiKTFHwSR){uzqzJUCXbx = true;}
      else if(bPiKTFHwSR == XhKuhBgqQJ){usUanyrchO = true;}
      if(GLKxFwZbAO == nRYJXXQVmz){QHdRGdYerq = true;}
      if(JmZJNHCoHG == uSJTKEPjcx){yBWYDCjute = true;}
      if(eXyWHBVwiL == bQjcwmrQtR){ikcZmIUzeH = true;}
      while(nRYJXXQVmz == GLKxFwZbAO){tiPRDAkgqV = true;}
      while(uSJTKEPjcx == uSJTKEPjcx){JdrjSGWaNG = true;}
      while(bQjcwmrQtR == bQjcwmrQtR){aseLiJPuIH = true;}
      if(WpbLhbwEkn == true){WpbLhbwEkn = false;}
      if(UcsFDIFPzO == true){UcsFDIFPzO = false;}
      if(pXTUpWgwNk == true){pXTUpWgwNk = false;}
      if(eAaVcFqykh == true){eAaVcFqykh = false;}
      if(ILyncyXeZn == true){ILyncyXeZn = false;}
      if(gcQfbyVGUL == true){gcQfbyVGUL = false;}
      if(uzqzJUCXbx == true){uzqzJUCXbx = false;}
      if(QHdRGdYerq == true){QHdRGdYerq = false;}
      if(yBWYDCjute == true){yBWYDCjute = false;}
      if(ikcZmIUzeH == true){ikcZmIUzeH = false;}
      if(wACbWZyzYx == true){wACbWZyzYx = false;}
      if(YqNcMscRwH == true){YqNcMscRwH = false;}
      if(kHdxNfdEdy == true){kHdxNfdEdy = false;}
      if(JZzjuyztCd == true){JZzjuyztCd = false;}
      if(DjVwFrWzMt == true){DjVwFrWzMt = false;}
      if(eCCXWnWFOq == true){eCCXWnWFOq = false;}
      if(usUanyrchO == true){usUanyrchO = false;}
      if(tiPRDAkgqV == true){tiPRDAkgqV = false;}
      if(JdrjSGWaNG == true){JdrjSGWaNG = false;}
      if(aseLiJPuIH == true){aseLiJPuIH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XALZZTZTCY
{ 
  void YyiCzrICKa()
  { 
      bool sGhKBuoKQT = false;
      bool WFbmFWykcO = false;
      bool uNoyedfspR = false;
      bool zMKYErHBcK = false;
      bool adqibSmYYo = false;
      bool nsaHRfRjeW = false;
      bool OuUzUKtCiM = false;
      bool PwHSmQWGVL = false;
      bool pHTBdFkDGX = false;
      bool aXVGufJqOR = false;
      bool XjoLYqlIUA = false;
      bool JLNTfGaSVO = false;
      bool YqwKlraBWH = false;
      bool HeqEnGRIbl = false;
      bool TciFOPJCZn = false;
      bool EpVzrgneZg = false;
      bool QjkMseTIeZ = false;
      bool oSqiuwIpuW = false;
      bool hXbhCRIrMG = false;
      bool RmhtVjrVMj = false;
      string ZtcItjIXpu;
      string heGWoFKbKg;
      string GBwIsxmXfO;
      string QWKNGMNcZQ;
      string MKNziNPMbt;
      string MkjuEYxTPx;
      string xkqbeLTsPc;
      string rgCtUwmxZf;
      string hZwkCelOJh;
      string OsNcTbSlUX;
      string sVwzCeipaI;
      string kztiOXoGYz;
      string ZEihNyTZar;
      string cBcBmLcwhW;
      string uumBwPzdNu;
      string mMMUynmNkE;
      string LJPieiVrwD;
      string trXBDdRgly;
      string zoLeFQnIDy;
      string YPLdLleEWM;
      if(ZtcItjIXpu == sVwzCeipaI){sGhKBuoKQT = true;}
      else if(sVwzCeipaI == ZtcItjIXpu){XjoLYqlIUA = true;}
      if(heGWoFKbKg == kztiOXoGYz){WFbmFWykcO = true;}
      else if(kztiOXoGYz == heGWoFKbKg){JLNTfGaSVO = true;}
      if(GBwIsxmXfO == ZEihNyTZar){uNoyedfspR = true;}
      else if(ZEihNyTZar == GBwIsxmXfO){YqwKlraBWH = true;}
      if(QWKNGMNcZQ == cBcBmLcwhW){zMKYErHBcK = true;}
      else if(cBcBmLcwhW == QWKNGMNcZQ){HeqEnGRIbl = true;}
      if(MKNziNPMbt == uumBwPzdNu){adqibSmYYo = true;}
      else if(uumBwPzdNu == MKNziNPMbt){TciFOPJCZn = true;}
      if(MkjuEYxTPx == mMMUynmNkE){nsaHRfRjeW = true;}
      else if(mMMUynmNkE == MkjuEYxTPx){EpVzrgneZg = true;}
      if(xkqbeLTsPc == LJPieiVrwD){OuUzUKtCiM = true;}
      else if(LJPieiVrwD == xkqbeLTsPc){QjkMseTIeZ = true;}
      if(rgCtUwmxZf == trXBDdRgly){PwHSmQWGVL = true;}
      if(hZwkCelOJh == zoLeFQnIDy){pHTBdFkDGX = true;}
      if(OsNcTbSlUX == YPLdLleEWM){aXVGufJqOR = true;}
      while(trXBDdRgly == rgCtUwmxZf){oSqiuwIpuW = true;}
      while(zoLeFQnIDy == zoLeFQnIDy){hXbhCRIrMG = true;}
      while(YPLdLleEWM == YPLdLleEWM){RmhtVjrVMj = true;}
      if(sGhKBuoKQT == true){sGhKBuoKQT = false;}
      if(WFbmFWykcO == true){WFbmFWykcO = false;}
      if(uNoyedfspR == true){uNoyedfspR = false;}
      if(zMKYErHBcK == true){zMKYErHBcK = false;}
      if(adqibSmYYo == true){adqibSmYYo = false;}
      if(nsaHRfRjeW == true){nsaHRfRjeW = false;}
      if(OuUzUKtCiM == true){OuUzUKtCiM = false;}
      if(PwHSmQWGVL == true){PwHSmQWGVL = false;}
      if(pHTBdFkDGX == true){pHTBdFkDGX = false;}
      if(aXVGufJqOR == true){aXVGufJqOR = false;}
      if(XjoLYqlIUA == true){XjoLYqlIUA = false;}
      if(JLNTfGaSVO == true){JLNTfGaSVO = false;}
      if(YqwKlraBWH == true){YqwKlraBWH = false;}
      if(HeqEnGRIbl == true){HeqEnGRIbl = false;}
      if(TciFOPJCZn == true){TciFOPJCZn = false;}
      if(EpVzrgneZg == true){EpVzrgneZg = false;}
      if(QjkMseTIeZ == true){QjkMseTIeZ = false;}
      if(oSqiuwIpuW == true){oSqiuwIpuW = false;}
      if(hXbhCRIrMG == true){hXbhCRIrMG = false;}
      if(RmhtVjrVMj == true){RmhtVjrVMj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMUUSJPSZP
{ 
  void aRuMUXteTP()
  { 
      bool ZIsXoGpAjo = false;
      bool cpuUwrtclF = false;
      bool DZaFuOtTzY = false;
      bool TBSFDnCKxV = false;
      bool AONLBMQYie = false;
      bool ZwpgVzgmca = false;
      bool MVBLVaXoRH = false;
      bool ojePEnMPDi = false;
      bool yUkTyWLljD = false;
      bool GOgWJdNCpa = false;
      bool naHaopQabh = false;
      bool mRiscrkgMy = false;
      bool PkFOBZCIGZ = false;
      bool ZKYctWMKeI = false;
      bool GjKCPnfmtQ = false;
      bool sgoqKCVsYP = false;
      bool mIUBHcsGyF = false;
      bool eaCEreaDyM = false;
      bool tONogrUgSr = false;
      bool BTkOVyPItl = false;
      string rbMtBDNURJ;
      string DWgKNhVaQY;
      string VxiDCUCPAM;
      string mNSfqoEsBg;
      string ZeIoFikRxD;
      string oHEmTtrIqg;
      string AyTEVpDATX;
      string cbZjzqotxS;
      string ikRxXfIfLw;
      string wuCTfaLDSO;
      string fjxYZNhTmc;
      string EyKXxOfVgp;
      string gXnWagZFEX;
      string flaimzmrWK;
      string xorirykdWQ;
      string toWchIwayr;
      string mcPPwSXbky;
      string bnyVrreFec;
      string wuhmcqPxBe;
      string CMteWTYclY;
      if(rbMtBDNURJ == fjxYZNhTmc){ZIsXoGpAjo = true;}
      else if(fjxYZNhTmc == rbMtBDNURJ){naHaopQabh = true;}
      if(DWgKNhVaQY == EyKXxOfVgp){cpuUwrtclF = true;}
      else if(EyKXxOfVgp == DWgKNhVaQY){mRiscrkgMy = true;}
      if(VxiDCUCPAM == gXnWagZFEX){DZaFuOtTzY = true;}
      else if(gXnWagZFEX == VxiDCUCPAM){PkFOBZCIGZ = true;}
      if(mNSfqoEsBg == flaimzmrWK){TBSFDnCKxV = true;}
      else if(flaimzmrWK == mNSfqoEsBg){ZKYctWMKeI = true;}
      if(ZeIoFikRxD == xorirykdWQ){AONLBMQYie = true;}
      else if(xorirykdWQ == ZeIoFikRxD){GjKCPnfmtQ = true;}
      if(oHEmTtrIqg == toWchIwayr){ZwpgVzgmca = true;}
      else if(toWchIwayr == oHEmTtrIqg){sgoqKCVsYP = true;}
      if(AyTEVpDATX == mcPPwSXbky){MVBLVaXoRH = true;}
      else if(mcPPwSXbky == AyTEVpDATX){mIUBHcsGyF = true;}
      if(cbZjzqotxS == bnyVrreFec){ojePEnMPDi = true;}
      if(ikRxXfIfLw == wuhmcqPxBe){yUkTyWLljD = true;}
      if(wuCTfaLDSO == CMteWTYclY){GOgWJdNCpa = true;}
      while(bnyVrreFec == cbZjzqotxS){eaCEreaDyM = true;}
      while(wuhmcqPxBe == wuhmcqPxBe){tONogrUgSr = true;}
      while(CMteWTYclY == CMteWTYclY){BTkOVyPItl = true;}
      if(ZIsXoGpAjo == true){ZIsXoGpAjo = false;}
      if(cpuUwrtclF == true){cpuUwrtclF = false;}
      if(DZaFuOtTzY == true){DZaFuOtTzY = false;}
      if(TBSFDnCKxV == true){TBSFDnCKxV = false;}
      if(AONLBMQYie == true){AONLBMQYie = false;}
      if(ZwpgVzgmca == true){ZwpgVzgmca = false;}
      if(MVBLVaXoRH == true){MVBLVaXoRH = false;}
      if(ojePEnMPDi == true){ojePEnMPDi = false;}
      if(yUkTyWLljD == true){yUkTyWLljD = false;}
      if(GOgWJdNCpa == true){GOgWJdNCpa = false;}
      if(naHaopQabh == true){naHaopQabh = false;}
      if(mRiscrkgMy == true){mRiscrkgMy = false;}
      if(PkFOBZCIGZ == true){PkFOBZCIGZ = false;}
      if(ZKYctWMKeI == true){ZKYctWMKeI = false;}
      if(GjKCPnfmtQ == true){GjKCPnfmtQ = false;}
      if(sgoqKCVsYP == true){sgoqKCVsYP = false;}
      if(mIUBHcsGyF == true){mIUBHcsGyF = false;}
      if(eaCEreaDyM == true){eaCEreaDyM = false;}
      if(tONogrUgSr == true){tONogrUgSr = false;}
      if(BTkOVyPItl == true){BTkOVyPItl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUJLNXIDTQ
{ 
  void lqdrCSCYKU()
  { 
      bool WfOYSLIacJ = false;
      bool oERCZtbsqs = false;
      bool GOtsXVSfxE = false;
      bool INeOIqBUnB = false;
      bool bcJoBXxLFP = false;
      bool mUFREHkUBx = false;
      bool rccYAaZCsh = false;
      bool rHFoRdFEqA = false;
      bool YGZgQnINJA = false;
      bool FgSpIyzkna = false;
      bool xtRXWeOPza = false;
      bool CgdBYlDuHM = false;
      bool SMsrbLoOgS = false;
      bool eTPQCdoBJk = false;
      bool YrNiyYCRRW = false;
      bool uDdaHkBYuL = false;
      bool pzigwiQNyt = false;
      bool wBkVnazJtD = false;
      bool IWxJWapnIR = false;
      bool cPGyuYJfmO = false;
      string QCCPyuyQfS;
      string HScZyOriqJ;
      string fZbelcFkHJ;
      string isuXJjUDSk;
      string hRemgifHBl;
      string OGRjypZWdU;
      string pMIViNWFQO;
      string soQGaNtnyC;
      string xyjUtbaKZS;
      string JxZxuVIJES;
      string LZpmrZpLJj;
      string wkYaXrcnbG;
      string lMfxEwPTKF;
      string FkjfqWHwbU;
      string lPBoWYYyZD;
      string rUhxfztrhw;
      string KVBEdKBsjA;
      string jgLGUWKpaf;
      string WQsHMkDlzq;
      string bONfJPOxKL;
      if(QCCPyuyQfS == LZpmrZpLJj){WfOYSLIacJ = true;}
      else if(LZpmrZpLJj == QCCPyuyQfS){xtRXWeOPza = true;}
      if(HScZyOriqJ == wkYaXrcnbG){oERCZtbsqs = true;}
      else if(wkYaXrcnbG == HScZyOriqJ){CgdBYlDuHM = true;}
      if(fZbelcFkHJ == lMfxEwPTKF){GOtsXVSfxE = true;}
      else if(lMfxEwPTKF == fZbelcFkHJ){SMsrbLoOgS = true;}
      if(isuXJjUDSk == FkjfqWHwbU){INeOIqBUnB = true;}
      else if(FkjfqWHwbU == isuXJjUDSk){eTPQCdoBJk = true;}
      if(hRemgifHBl == lPBoWYYyZD){bcJoBXxLFP = true;}
      else if(lPBoWYYyZD == hRemgifHBl){YrNiyYCRRW = true;}
      if(OGRjypZWdU == rUhxfztrhw){mUFREHkUBx = true;}
      else if(rUhxfztrhw == OGRjypZWdU){uDdaHkBYuL = true;}
      if(pMIViNWFQO == KVBEdKBsjA){rccYAaZCsh = true;}
      else if(KVBEdKBsjA == pMIViNWFQO){pzigwiQNyt = true;}
      if(soQGaNtnyC == jgLGUWKpaf){rHFoRdFEqA = true;}
      if(xyjUtbaKZS == WQsHMkDlzq){YGZgQnINJA = true;}
      if(JxZxuVIJES == bONfJPOxKL){FgSpIyzkna = true;}
      while(jgLGUWKpaf == soQGaNtnyC){wBkVnazJtD = true;}
      while(WQsHMkDlzq == WQsHMkDlzq){IWxJWapnIR = true;}
      while(bONfJPOxKL == bONfJPOxKL){cPGyuYJfmO = true;}
      if(WfOYSLIacJ == true){WfOYSLIacJ = false;}
      if(oERCZtbsqs == true){oERCZtbsqs = false;}
      if(GOtsXVSfxE == true){GOtsXVSfxE = false;}
      if(INeOIqBUnB == true){INeOIqBUnB = false;}
      if(bcJoBXxLFP == true){bcJoBXxLFP = false;}
      if(mUFREHkUBx == true){mUFREHkUBx = false;}
      if(rccYAaZCsh == true){rccYAaZCsh = false;}
      if(rHFoRdFEqA == true){rHFoRdFEqA = false;}
      if(YGZgQnINJA == true){YGZgQnINJA = false;}
      if(FgSpIyzkna == true){FgSpIyzkna = false;}
      if(xtRXWeOPza == true){xtRXWeOPza = false;}
      if(CgdBYlDuHM == true){CgdBYlDuHM = false;}
      if(SMsrbLoOgS == true){SMsrbLoOgS = false;}
      if(eTPQCdoBJk == true){eTPQCdoBJk = false;}
      if(YrNiyYCRRW == true){YrNiyYCRRW = false;}
      if(uDdaHkBYuL == true){uDdaHkBYuL = false;}
      if(pzigwiQNyt == true){pzigwiQNyt = false;}
      if(wBkVnazJtD == true){wBkVnazJtD = false;}
      if(IWxJWapnIR == true){IWxJWapnIR = false;}
      if(cPGyuYJfmO == true){cPGyuYJfmO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDBVWACNSU
{ 
  void jleXNUNJMx()
  { 
      bool DyGsxafnMS = false;
      bool MlkMDIdYKz = false;
      bool LUYWWYJrzw = false;
      bool nfkUPKwEAb = false;
      bool WjsLJngoGf = false;
      bool hhZwJiZiWY = false;
      bool RnnQdgAPxr = false;
      bool LYXhcaaNNi = false;
      bool rUkTNGFoLf = false;
      bool kMhbKiucgc = false;
      bool mQqOTIJqTh = false;
      bool ILVmfxCUCW = false;
      bool aLDRHyquXs = false;
      bool eyfkwacWzE = false;
      bool xNVcWYqtuN = false;
      bool fZZKBaMZGU = false;
      bool RNTZCKfkqE = false;
      bool TfVyZMpZti = false;
      bool HwAKNFYViU = false;
      bool ODPdmituaM = false;
      string tKNjgSeyeh;
      string boldOlVYiF;
      string WpMjACTYdZ;
      string iMXUtgbaHW;
      string kcWRDINFLi;
      string JfXWhEycid;
      string yFUEzPQQjg;
      string KtRMTtStgq;
      string oOMuPCoBlo;
      string iyqdYeIRSn;
      string rxVeXOOLCn;
      string kDwrnjsYow;
      string ZOdtyLDmmo;
      string lBbrzrshWA;
      string ndyyEeCzoo;
      string licVOcSafM;
      string LbXNCjaDsw;
      string qKCnIuQfpT;
      string JDxyCDYGdV;
      string ZRBKoMGkuU;
      if(tKNjgSeyeh == rxVeXOOLCn){DyGsxafnMS = true;}
      else if(rxVeXOOLCn == tKNjgSeyeh){mQqOTIJqTh = true;}
      if(boldOlVYiF == kDwrnjsYow){MlkMDIdYKz = true;}
      else if(kDwrnjsYow == boldOlVYiF){ILVmfxCUCW = true;}
      if(WpMjACTYdZ == ZOdtyLDmmo){LUYWWYJrzw = true;}
      else if(ZOdtyLDmmo == WpMjACTYdZ){aLDRHyquXs = true;}
      if(iMXUtgbaHW == lBbrzrshWA){nfkUPKwEAb = true;}
      else if(lBbrzrshWA == iMXUtgbaHW){eyfkwacWzE = true;}
      if(kcWRDINFLi == ndyyEeCzoo){WjsLJngoGf = true;}
      else if(ndyyEeCzoo == kcWRDINFLi){xNVcWYqtuN = true;}
      if(JfXWhEycid == licVOcSafM){hhZwJiZiWY = true;}
      else if(licVOcSafM == JfXWhEycid){fZZKBaMZGU = true;}
      if(yFUEzPQQjg == LbXNCjaDsw){RnnQdgAPxr = true;}
      else if(LbXNCjaDsw == yFUEzPQQjg){RNTZCKfkqE = true;}
      if(KtRMTtStgq == qKCnIuQfpT){LYXhcaaNNi = true;}
      if(oOMuPCoBlo == JDxyCDYGdV){rUkTNGFoLf = true;}
      if(iyqdYeIRSn == ZRBKoMGkuU){kMhbKiucgc = true;}
      while(qKCnIuQfpT == KtRMTtStgq){TfVyZMpZti = true;}
      while(JDxyCDYGdV == JDxyCDYGdV){HwAKNFYViU = true;}
      while(ZRBKoMGkuU == ZRBKoMGkuU){ODPdmituaM = true;}
      if(DyGsxafnMS == true){DyGsxafnMS = false;}
      if(MlkMDIdYKz == true){MlkMDIdYKz = false;}
      if(LUYWWYJrzw == true){LUYWWYJrzw = false;}
      if(nfkUPKwEAb == true){nfkUPKwEAb = false;}
      if(WjsLJngoGf == true){WjsLJngoGf = false;}
      if(hhZwJiZiWY == true){hhZwJiZiWY = false;}
      if(RnnQdgAPxr == true){RnnQdgAPxr = false;}
      if(LYXhcaaNNi == true){LYXhcaaNNi = false;}
      if(rUkTNGFoLf == true){rUkTNGFoLf = false;}
      if(kMhbKiucgc == true){kMhbKiucgc = false;}
      if(mQqOTIJqTh == true){mQqOTIJqTh = false;}
      if(ILVmfxCUCW == true){ILVmfxCUCW = false;}
      if(aLDRHyquXs == true){aLDRHyquXs = false;}
      if(eyfkwacWzE == true){eyfkwacWzE = false;}
      if(xNVcWYqtuN == true){xNVcWYqtuN = false;}
      if(fZZKBaMZGU == true){fZZKBaMZGU = false;}
      if(RNTZCKfkqE == true){RNTZCKfkqE = false;}
      if(TfVyZMpZti == true){TfVyZMpZti = false;}
      if(HwAKNFYViU == true){HwAKNFYViU = false;}
      if(ODPdmituaM == true){ODPdmituaM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKHLDKHAHK
{ 
  void PWWSPEbpyQ()
  { 
      bool HnqhwLMkwZ = false;
      bool SreknCghcG = false;
      bool oFdntbGPiC = false;
      bool cVfFAXmGZi = false;
      bool zXDSESLdYe = false;
      bool mnMRzBKDnU = false;
      bool FxCtxxLYkP = false;
      bool PZHsGQCKib = false;
      bool PbpEOoIOFz = false;
      bool NiSFdCVJVH = false;
      bool GmsJOMfTLh = false;
      bool zzUMFcGxeH = false;
      bool nxTkCgHCOE = false;
      bool uroaUbhgoB = false;
      bool IoDWANOGAA = false;
      bool uXdOTJTIHh = false;
      bool FdEGmGKsqc = false;
      bool tZIcyzswkn = false;
      bool RBCOIWOaHK = false;
      bool IZZHwejwit = false;
      string rNfbVBzRDU;
      string jBbdWqpofL;
      string rmlSEHAums;
      string QpLQBNPpNx;
      string SKrkwwFgWA;
      string OaYtDEaNXO;
      string BEdJEspKcI;
      string aAbhrhtAVI;
      string CTXmdpRQNw;
      string mCSzwOfigC;
      string FtEOYOzpCU;
      string JZqOLhfpfN;
      string bZxfUXhbkd;
      string BLTTDHOJNO;
      string qbNrlNLDmO;
      string hoCSaexXsA;
      string gWEXSyGWLE;
      string SWcQWALFsH;
      string MdoWuMJAsX;
      string KqPMhUWpYn;
      if(rNfbVBzRDU == FtEOYOzpCU){HnqhwLMkwZ = true;}
      else if(FtEOYOzpCU == rNfbVBzRDU){GmsJOMfTLh = true;}
      if(jBbdWqpofL == JZqOLhfpfN){SreknCghcG = true;}
      else if(JZqOLhfpfN == jBbdWqpofL){zzUMFcGxeH = true;}
      if(rmlSEHAums == bZxfUXhbkd){oFdntbGPiC = true;}
      else if(bZxfUXhbkd == rmlSEHAums){nxTkCgHCOE = true;}
      if(QpLQBNPpNx == BLTTDHOJNO){cVfFAXmGZi = true;}
      else if(BLTTDHOJNO == QpLQBNPpNx){uroaUbhgoB = true;}
      if(SKrkwwFgWA == qbNrlNLDmO){zXDSESLdYe = true;}
      else if(qbNrlNLDmO == SKrkwwFgWA){IoDWANOGAA = true;}
      if(OaYtDEaNXO == hoCSaexXsA){mnMRzBKDnU = true;}
      else if(hoCSaexXsA == OaYtDEaNXO){uXdOTJTIHh = true;}
      if(BEdJEspKcI == gWEXSyGWLE){FxCtxxLYkP = true;}
      else if(gWEXSyGWLE == BEdJEspKcI){FdEGmGKsqc = true;}
      if(aAbhrhtAVI == SWcQWALFsH){PZHsGQCKib = true;}
      if(CTXmdpRQNw == MdoWuMJAsX){PbpEOoIOFz = true;}
      if(mCSzwOfigC == KqPMhUWpYn){NiSFdCVJVH = true;}
      while(SWcQWALFsH == aAbhrhtAVI){tZIcyzswkn = true;}
      while(MdoWuMJAsX == MdoWuMJAsX){RBCOIWOaHK = true;}
      while(KqPMhUWpYn == KqPMhUWpYn){IZZHwejwit = true;}
      if(HnqhwLMkwZ == true){HnqhwLMkwZ = false;}
      if(SreknCghcG == true){SreknCghcG = false;}
      if(oFdntbGPiC == true){oFdntbGPiC = false;}
      if(cVfFAXmGZi == true){cVfFAXmGZi = false;}
      if(zXDSESLdYe == true){zXDSESLdYe = false;}
      if(mnMRzBKDnU == true){mnMRzBKDnU = false;}
      if(FxCtxxLYkP == true){FxCtxxLYkP = false;}
      if(PZHsGQCKib == true){PZHsGQCKib = false;}
      if(PbpEOoIOFz == true){PbpEOoIOFz = false;}
      if(NiSFdCVJVH == true){NiSFdCVJVH = false;}
      if(GmsJOMfTLh == true){GmsJOMfTLh = false;}
      if(zzUMFcGxeH == true){zzUMFcGxeH = false;}
      if(nxTkCgHCOE == true){nxTkCgHCOE = false;}
      if(uroaUbhgoB == true){uroaUbhgoB = false;}
      if(IoDWANOGAA == true){IoDWANOGAA = false;}
      if(uXdOTJTIHh == true){uXdOTJTIHh = false;}
      if(FdEGmGKsqc == true){FdEGmGKsqc = false;}
      if(tZIcyzswkn == true){tZIcyzswkn = false;}
      if(RBCOIWOaHK == true){RBCOIWOaHK = false;}
      if(IZZHwejwit == true){IZZHwejwit = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZQFKHJAOV
{ 
  void fsWYyOMYSV()
  { 
      bool UrVDTxDyJE = false;
      bool mrsrudNska = false;
      bool eMFjCdeQLR = false;
      bool TLQRnxDAsJ = false;
      bool EBSuTlgHSu = false;
      bool oqcZiImkBo = false;
      bool SmmqkaabEy = false;
      bool aMzbWcsJQP = false;
      bool xWxQcbiqhf = false;
      bool KRzDqQObKr = false;
      bool LFDUTbrADG = false;
      bool OdUkruoVOI = false;
      bool risYnJNukF = false;
      bool OQyXErTcwB = false;
      bool jhnbQfwNLu = false;
      bool arNCAbLegK = false;
      bool NwOxqxfxfz = false;
      bool aMYMYJuRHH = false;
      bool MzjoeVDuXb = false;
      bool gowlmnSpjS = false;
      string TZTqyeKFEs;
      string WSGrsiDZqE;
      string cTGtUadJyU;
      string dqDsJWjtdc;
      string LVihiIZgnY;
      string ACHUhASYWW;
      string ABGjPeONhV;
      string zJuOsHjXLM;
      string BxUZUajhKJ;
      string DLWGbJPzRD;
      string sMySZpGsba;
      string PuNKVDgfOn;
      string ufCYRmloli;
      string qjGISnzBAd;
      string TqGjsIxMkY;
      string cijdHMKYBl;
      string ERGrienFqg;
      string EeekTDZRfI;
      string pZENGIAbAG;
      string dZAOZCjOAO;
      if(TZTqyeKFEs == sMySZpGsba){UrVDTxDyJE = true;}
      else if(sMySZpGsba == TZTqyeKFEs){LFDUTbrADG = true;}
      if(WSGrsiDZqE == PuNKVDgfOn){mrsrudNska = true;}
      else if(PuNKVDgfOn == WSGrsiDZqE){OdUkruoVOI = true;}
      if(cTGtUadJyU == ufCYRmloli){eMFjCdeQLR = true;}
      else if(ufCYRmloli == cTGtUadJyU){risYnJNukF = true;}
      if(dqDsJWjtdc == qjGISnzBAd){TLQRnxDAsJ = true;}
      else if(qjGISnzBAd == dqDsJWjtdc){OQyXErTcwB = true;}
      if(LVihiIZgnY == TqGjsIxMkY){EBSuTlgHSu = true;}
      else if(TqGjsIxMkY == LVihiIZgnY){jhnbQfwNLu = true;}
      if(ACHUhASYWW == cijdHMKYBl){oqcZiImkBo = true;}
      else if(cijdHMKYBl == ACHUhASYWW){arNCAbLegK = true;}
      if(ABGjPeONhV == ERGrienFqg){SmmqkaabEy = true;}
      else if(ERGrienFqg == ABGjPeONhV){NwOxqxfxfz = true;}
      if(zJuOsHjXLM == EeekTDZRfI){aMzbWcsJQP = true;}
      if(BxUZUajhKJ == pZENGIAbAG){xWxQcbiqhf = true;}
      if(DLWGbJPzRD == dZAOZCjOAO){KRzDqQObKr = true;}
      while(EeekTDZRfI == zJuOsHjXLM){aMYMYJuRHH = true;}
      while(pZENGIAbAG == pZENGIAbAG){MzjoeVDuXb = true;}
      while(dZAOZCjOAO == dZAOZCjOAO){gowlmnSpjS = true;}
      if(UrVDTxDyJE == true){UrVDTxDyJE = false;}
      if(mrsrudNska == true){mrsrudNska = false;}
      if(eMFjCdeQLR == true){eMFjCdeQLR = false;}
      if(TLQRnxDAsJ == true){TLQRnxDAsJ = false;}
      if(EBSuTlgHSu == true){EBSuTlgHSu = false;}
      if(oqcZiImkBo == true){oqcZiImkBo = false;}
      if(SmmqkaabEy == true){SmmqkaabEy = false;}
      if(aMzbWcsJQP == true){aMzbWcsJQP = false;}
      if(xWxQcbiqhf == true){xWxQcbiqhf = false;}
      if(KRzDqQObKr == true){KRzDqQObKr = false;}
      if(LFDUTbrADG == true){LFDUTbrADG = false;}
      if(OdUkruoVOI == true){OdUkruoVOI = false;}
      if(risYnJNukF == true){risYnJNukF = false;}
      if(OQyXErTcwB == true){OQyXErTcwB = false;}
      if(jhnbQfwNLu == true){jhnbQfwNLu = false;}
      if(arNCAbLegK == true){arNCAbLegK = false;}
      if(NwOxqxfxfz == true){NwOxqxfxfz = false;}
      if(aMYMYJuRHH == true){aMYMYJuRHH = false;}
      if(MzjoeVDuXb == true){MzjoeVDuXb = false;}
      if(gowlmnSpjS == true){gowlmnSpjS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTYEAFDKSK
{ 
  void MqklqwLrUu()
  { 
      bool YXaLMmHEsA = false;
      bool nfCpSlNaTQ = false;
      bool ENJuhiYtXg = false;
      bool HOJohStfDz = false;
      bool LNesUQTVYg = false;
      bool ASJfMLOedd = false;
      bool OMfMsZVNHA = false;
      bool rgXUEqhPaQ = false;
      bool PCVqfnEdcW = false;
      bool EOBZjygSAu = false;
      bool uFNYnSuoaU = false;
      bool dyEMNMqofE = false;
      bool UrkkwdexjG = false;
      bool JOPfUJnwDN = false;
      bool sPCHsFKoLX = false;
      bool GrmuZCUccK = false;
      bool mxEULOhXqD = false;
      bool XtkSKFpcqp = false;
      bool SpkMzQbUFS = false;
      bool oKTrZwKgue = false;
      string KuFmZkrKOx;
      string bepTBwuRMS;
      string xrhXrBPVsO;
      string ebyYuXGVdZ;
      string oAOTnqqdtQ;
      string gZOutRNhuY;
      string VVQzSAfRYc;
      string pZmmdxdOiA;
      string JkacgFNCdc;
      string KYZFDSiOBn;
      string KZFQaGlaRx;
      string mzytOktnRN;
      string mdmwSQzhiK;
      string NPMupjeJBZ;
      string SlkfoLaepS;
      string XtwnBgmJyJ;
      string GErGjXlCEe;
      string FjmqtBrGGH;
      string pUqQmSSYsI;
      string xVLrSNsdwR;
      if(KuFmZkrKOx == KZFQaGlaRx){YXaLMmHEsA = true;}
      else if(KZFQaGlaRx == KuFmZkrKOx){uFNYnSuoaU = true;}
      if(bepTBwuRMS == mzytOktnRN){nfCpSlNaTQ = true;}
      else if(mzytOktnRN == bepTBwuRMS){dyEMNMqofE = true;}
      if(xrhXrBPVsO == mdmwSQzhiK){ENJuhiYtXg = true;}
      else if(mdmwSQzhiK == xrhXrBPVsO){UrkkwdexjG = true;}
      if(ebyYuXGVdZ == NPMupjeJBZ){HOJohStfDz = true;}
      else if(NPMupjeJBZ == ebyYuXGVdZ){JOPfUJnwDN = true;}
      if(oAOTnqqdtQ == SlkfoLaepS){LNesUQTVYg = true;}
      else if(SlkfoLaepS == oAOTnqqdtQ){sPCHsFKoLX = true;}
      if(gZOutRNhuY == XtwnBgmJyJ){ASJfMLOedd = true;}
      else if(XtwnBgmJyJ == gZOutRNhuY){GrmuZCUccK = true;}
      if(VVQzSAfRYc == GErGjXlCEe){OMfMsZVNHA = true;}
      else if(GErGjXlCEe == VVQzSAfRYc){mxEULOhXqD = true;}
      if(pZmmdxdOiA == FjmqtBrGGH){rgXUEqhPaQ = true;}
      if(JkacgFNCdc == pUqQmSSYsI){PCVqfnEdcW = true;}
      if(KYZFDSiOBn == xVLrSNsdwR){EOBZjygSAu = true;}
      while(FjmqtBrGGH == pZmmdxdOiA){XtkSKFpcqp = true;}
      while(pUqQmSSYsI == pUqQmSSYsI){SpkMzQbUFS = true;}
      while(xVLrSNsdwR == xVLrSNsdwR){oKTrZwKgue = true;}
      if(YXaLMmHEsA == true){YXaLMmHEsA = false;}
      if(nfCpSlNaTQ == true){nfCpSlNaTQ = false;}
      if(ENJuhiYtXg == true){ENJuhiYtXg = false;}
      if(HOJohStfDz == true){HOJohStfDz = false;}
      if(LNesUQTVYg == true){LNesUQTVYg = false;}
      if(ASJfMLOedd == true){ASJfMLOedd = false;}
      if(OMfMsZVNHA == true){OMfMsZVNHA = false;}
      if(rgXUEqhPaQ == true){rgXUEqhPaQ = false;}
      if(PCVqfnEdcW == true){PCVqfnEdcW = false;}
      if(EOBZjygSAu == true){EOBZjygSAu = false;}
      if(uFNYnSuoaU == true){uFNYnSuoaU = false;}
      if(dyEMNMqofE == true){dyEMNMqofE = false;}
      if(UrkkwdexjG == true){UrkkwdexjG = false;}
      if(JOPfUJnwDN == true){JOPfUJnwDN = false;}
      if(sPCHsFKoLX == true){sPCHsFKoLX = false;}
      if(GrmuZCUccK == true){GrmuZCUccK = false;}
      if(mxEULOhXqD == true){mxEULOhXqD = false;}
      if(XtkSKFpcqp == true){XtkSKFpcqp = false;}
      if(SpkMzQbUFS == true){SpkMzQbUFS = false;}
      if(oKTrZwKgue == true){oKTrZwKgue = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLOEHJYAPC
{ 
  void VbwmdhAIbS()
  { 
      bool mExckTKiHo = false;
      bool PqnnWDALHP = false;
      bool AqWBipXjXm = false;
      bool FtuxJYAUPc = false;
      bool ywDDdOhFbx = false;
      bool VVfbGwhwtu = false;
      bool wZKUiVwqey = false;
      bool CewdREmSXT = false;
      bool HRIZQiNTpN = false;
      bool pEaTgXkhUI = false;
      bool RqadupYBJC = false;
      bool IPYZneRjDz = false;
      bool HcBRIyEbxs = false;
      bool SFxPBQqeeZ = false;
      bool KMJmEZfAfC = false;
      bool GBdUAopJVx = false;
      bool lxEPjDSJXW = false;
      bool mlEcotSNMh = false;
      bool SDwumQabOM = false;
      bool ZhJhnMIsDB = false;
      string edwrjPkckM;
      string gwqCbXAmbG;
      string jkcfrtlixL;
      string BrowCVUdgC;
      string lGKFAdbleA;
      string OTkHEtBQzp;
      string cCeYKoGtAG;
      string CVFYTdZWfN;
      string RAExwhGgqH;
      string TEdpZjaktK;
      string WgkXysNLna;
      string TejlYbyhcc;
      string hZDrlxqPyi;
      string CnbUpjPfyD;
      string TurQmoTrRx;
      string lsIQbxdskA;
      string ByMEYfCPun;
      string MRiZJmgmEx;
      string cyxAxIeLrs;
      string FWtyBVhmqH;
      if(edwrjPkckM == WgkXysNLna){mExckTKiHo = true;}
      else if(WgkXysNLna == edwrjPkckM){RqadupYBJC = true;}
      if(gwqCbXAmbG == TejlYbyhcc){PqnnWDALHP = true;}
      else if(TejlYbyhcc == gwqCbXAmbG){IPYZneRjDz = true;}
      if(jkcfrtlixL == hZDrlxqPyi){AqWBipXjXm = true;}
      else if(hZDrlxqPyi == jkcfrtlixL){HcBRIyEbxs = true;}
      if(BrowCVUdgC == CnbUpjPfyD){FtuxJYAUPc = true;}
      else if(CnbUpjPfyD == BrowCVUdgC){SFxPBQqeeZ = true;}
      if(lGKFAdbleA == TurQmoTrRx){ywDDdOhFbx = true;}
      else if(TurQmoTrRx == lGKFAdbleA){KMJmEZfAfC = true;}
      if(OTkHEtBQzp == lsIQbxdskA){VVfbGwhwtu = true;}
      else if(lsIQbxdskA == OTkHEtBQzp){GBdUAopJVx = true;}
      if(cCeYKoGtAG == ByMEYfCPun){wZKUiVwqey = true;}
      else if(ByMEYfCPun == cCeYKoGtAG){lxEPjDSJXW = true;}
      if(CVFYTdZWfN == MRiZJmgmEx){CewdREmSXT = true;}
      if(RAExwhGgqH == cyxAxIeLrs){HRIZQiNTpN = true;}
      if(TEdpZjaktK == FWtyBVhmqH){pEaTgXkhUI = true;}
      while(MRiZJmgmEx == CVFYTdZWfN){mlEcotSNMh = true;}
      while(cyxAxIeLrs == cyxAxIeLrs){SDwumQabOM = true;}
      while(FWtyBVhmqH == FWtyBVhmqH){ZhJhnMIsDB = true;}
      if(mExckTKiHo == true){mExckTKiHo = false;}
      if(PqnnWDALHP == true){PqnnWDALHP = false;}
      if(AqWBipXjXm == true){AqWBipXjXm = false;}
      if(FtuxJYAUPc == true){FtuxJYAUPc = false;}
      if(ywDDdOhFbx == true){ywDDdOhFbx = false;}
      if(VVfbGwhwtu == true){VVfbGwhwtu = false;}
      if(wZKUiVwqey == true){wZKUiVwqey = false;}
      if(CewdREmSXT == true){CewdREmSXT = false;}
      if(HRIZQiNTpN == true){HRIZQiNTpN = false;}
      if(pEaTgXkhUI == true){pEaTgXkhUI = false;}
      if(RqadupYBJC == true){RqadupYBJC = false;}
      if(IPYZneRjDz == true){IPYZneRjDz = false;}
      if(HcBRIyEbxs == true){HcBRIyEbxs = false;}
      if(SFxPBQqeeZ == true){SFxPBQqeeZ = false;}
      if(KMJmEZfAfC == true){KMJmEZfAfC = false;}
      if(GBdUAopJVx == true){GBdUAopJVx = false;}
      if(lxEPjDSJXW == true){lxEPjDSJXW = false;}
      if(mlEcotSNMh == true){mlEcotSNMh = false;}
      if(SDwumQabOM == true){SDwumQabOM = false;}
      if(ZhJhnMIsDB == true){ZhJhnMIsDB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKYCQZFDMC
{ 
  void YxTJbPILmK()
  { 
      bool WWUuVZVUDp = false;
      bool escmEAIbgi = false;
      bool jkoKWHEVsq = false;
      bool GzArYzUxHx = false;
      bool VhHgixqHxO = false;
      bool alEorlgJYO = false;
      bool VzaLifrjOF = false;
      bool eKUiNBcHbZ = false;
      bool PwYeQUtLAm = false;
      bool RLYsbVGuyC = false;
      bool EHsrjPQVbp = false;
      bool IYhyyYauuN = false;
      bool kgjbmSlbGq = false;
      bool ugJYVIDfuB = false;
      bool DYiJdrdZtD = false;
      bool tLAjRWXQEQ = false;
      bool coOjuaOIco = false;
      bool VtztJMyZxt = false;
      bool oMgDxjgZHy = false;
      bool klbeXOJyOD = false;
      string lgjFwcNfbW;
      string XKfethFoqR;
      string jAPLeXoCVk;
      string YoszQWAXFc;
      string PEflgIWrWM;
      string HlrCplQYZY;
      string nKJpxiRgNW;
      string ggiNBeUdeV;
      string AweIdmwpIe;
      string GbxgnEtonx;
      string qpeAfZCdBK;
      string QlsEXreAMK;
      string maXhPEjCYx;
      string keogeJQecE;
      string jSoyNTisJw;
      string ZscdKQSxja;
      string pAEEZlwLYN;
      string azXIZUkYUw;
      string VprcWqCLWO;
      string qTuCOiNkXb;
      if(lgjFwcNfbW == qpeAfZCdBK){WWUuVZVUDp = true;}
      else if(qpeAfZCdBK == lgjFwcNfbW){EHsrjPQVbp = true;}
      if(XKfethFoqR == QlsEXreAMK){escmEAIbgi = true;}
      else if(QlsEXreAMK == XKfethFoqR){IYhyyYauuN = true;}
      if(jAPLeXoCVk == maXhPEjCYx){jkoKWHEVsq = true;}
      else if(maXhPEjCYx == jAPLeXoCVk){kgjbmSlbGq = true;}
      if(YoszQWAXFc == keogeJQecE){GzArYzUxHx = true;}
      else if(keogeJQecE == YoszQWAXFc){ugJYVIDfuB = true;}
      if(PEflgIWrWM == jSoyNTisJw){VhHgixqHxO = true;}
      else if(jSoyNTisJw == PEflgIWrWM){DYiJdrdZtD = true;}
      if(HlrCplQYZY == ZscdKQSxja){alEorlgJYO = true;}
      else if(ZscdKQSxja == HlrCplQYZY){tLAjRWXQEQ = true;}
      if(nKJpxiRgNW == pAEEZlwLYN){VzaLifrjOF = true;}
      else if(pAEEZlwLYN == nKJpxiRgNW){coOjuaOIco = true;}
      if(ggiNBeUdeV == azXIZUkYUw){eKUiNBcHbZ = true;}
      if(AweIdmwpIe == VprcWqCLWO){PwYeQUtLAm = true;}
      if(GbxgnEtonx == qTuCOiNkXb){RLYsbVGuyC = true;}
      while(azXIZUkYUw == ggiNBeUdeV){VtztJMyZxt = true;}
      while(VprcWqCLWO == VprcWqCLWO){oMgDxjgZHy = true;}
      while(qTuCOiNkXb == qTuCOiNkXb){klbeXOJyOD = true;}
      if(WWUuVZVUDp == true){WWUuVZVUDp = false;}
      if(escmEAIbgi == true){escmEAIbgi = false;}
      if(jkoKWHEVsq == true){jkoKWHEVsq = false;}
      if(GzArYzUxHx == true){GzArYzUxHx = false;}
      if(VhHgixqHxO == true){VhHgixqHxO = false;}
      if(alEorlgJYO == true){alEorlgJYO = false;}
      if(VzaLifrjOF == true){VzaLifrjOF = false;}
      if(eKUiNBcHbZ == true){eKUiNBcHbZ = false;}
      if(PwYeQUtLAm == true){PwYeQUtLAm = false;}
      if(RLYsbVGuyC == true){RLYsbVGuyC = false;}
      if(EHsrjPQVbp == true){EHsrjPQVbp = false;}
      if(IYhyyYauuN == true){IYhyyYauuN = false;}
      if(kgjbmSlbGq == true){kgjbmSlbGq = false;}
      if(ugJYVIDfuB == true){ugJYVIDfuB = false;}
      if(DYiJdrdZtD == true){DYiJdrdZtD = false;}
      if(tLAjRWXQEQ == true){tLAjRWXQEQ = false;}
      if(coOjuaOIco == true){coOjuaOIco = false;}
      if(VtztJMyZxt == true){VtztJMyZxt = false;}
      if(oMgDxjgZHy == true){oMgDxjgZHy = false;}
      if(klbeXOJyOD == true){klbeXOJyOD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHPLFKJVVK
{ 
  void wmyYMKHEgu()
  { 
      bool lTxrsOqyGo = false;
      bool jzXOxCiWks = false;
      bool MddfoRQqUI = false;
      bool kIhejjByjW = false;
      bool FrCBoytksm = false;
      bool tysiIHpRDb = false;
      bool yAcyEbRsdM = false;
      bool BkmOnUabqp = false;
      bool XeygOmOyVb = false;
      bool tjuIYFOExM = false;
      bool gAGflILeun = false;
      bool gNZMDSBujQ = false;
      bool NTWBSRpdpi = false;
      bool FVeeJWXSuF = false;
      bool aiCgufJhEF = false;
      bool DSUfzNcEMT = false;
      bool SgoMiKiuCg = false;
      bool thAdodQpGm = false;
      bool HHZjemByew = false;
      bool sSGblttpyk = false;
      string hrCTiKijIl;
      string zJZrJAeOiz;
      string kTNlFrrOWJ;
      string tucQpuLUQX;
      string BNJabtxBui;
      string NsSljNdQOp;
      string SUNyqEgJCN;
      string nJxLyWKmJL;
      string uqSmwAbpfb;
      string RuGaEgALiX;
      string NmzguEwGnM;
      string CqGDubBZCp;
      string bpcZwsCVGQ;
      string WzDlxHqkrq;
      string EVCSYZnDec;
      string eZIsuXJYkB;
      string BZAWpDnUFm;
      string jQhKlGmKAW;
      string EzpckxpJpY;
      string ySAppdUecV;
      if(hrCTiKijIl == NmzguEwGnM){lTxrsOqyGo = true;}
      else if(NmzguEwGnM == hrCTiKijIl){gAGflILeun = true;}
      if(zJZrJAeOiz == CqGDubBZCp){jzXOxCiWks = true;}
      else if(CqGDubBZCp == zJZrJAeOiz){gNZMDSBujQ = true;}
      if(kTNlFrrOWJ == bpcZwsCVGQ){MddfoRQqUI = true;}
      else if(bpcZwsCVGQ == kTNlFrrOWJ){NTWBSRpdpi = true;}
      if(tucQpuLUQX == WzDlxHqkrq){kIhejjByjW = true;}
      else if(WzDlxHqkrq == tucQpuLUQX){FVeeJWXSuF = true;}
      if(BNJabtxBui == EVCSYZnDec){FrCBoytksm = true;}
      else if(EVCSYZnDec == BNJabtxBui){aiCgufJhEF = true;}
      if(NsSljNdQOp == eZIsuXJYkB){tysiIHpRDb = true;}
      else if(eZIsuXJYkB == NsSljNdQOp){DSUfzNcEMT = true;}
      if(SUNyqEgJCN == BZAWpDnUFm){yAcyEbRsdM = true;}
      else if(BZAWpDnUFm == SUNyqEgJCN){SgoMiKiuCg = true;}
      if(nJxLyWKmJL == jQhKlGmKAW){BkmOnUabqp = true;}
      if(uqSmwAbpfb == EzpckxpJpY){XeygOmOyVb = true;}
      if(RuGaEgALiX == ySAppdUecV){tjuIYFOExM = true;}
      while(jQhKlGmKAW == nJxLyWKmJL){thAdodQpGm = true;}
      while(EzpckxpJpY == EzpckxpJpY){HHZjemByew = true;}
      while(ySAppdUecV == ySAppdUecV){sSGblttpyk = true;}
      if(lTxrsOqyGo == true){lTxrsOqyGo = false;}
      if(jzXOxCiWks == true){jzXOxCiWks = false;}
      if(MddfoRQqUI == true){MddfoRQqUI = false;}
      if(kIhejjByjW == true){kIhejjByjW = false;}
      if(FrCBoytksm == true){FrCBoytksm = false;}
      if(tysiIHpRDb == true){tysiIHpRDb = false;}
      if(yAcyEbRsdM == true){yAcyEbRsdM = false;}
      if(BkmOnUabqp == true){BkmOnUabqp = false;}
      if(XeygOmOyVb == true){XeygOmOyVb = false;}
      if(tjuIYFOExM == true){tjuIYFOExM = false;}
      if(gAGflILeun == true){gAGflILeun = false;}
      if(gNZMDSBujQ == true){gNZMDSBujQ = false;}
      if(NTWBSRpdpi == true){NTWBSRpdpi = false;}
      if(FVeeJWXSuF == true){FVeeJWXSuF = false;}
      if(aiCgufJhEF == true){aiCgufJhEF = false;}
      if(DSUfzNcEMT == true){DSUfzNcEMT = false;}
      if(SgoMiKiuCg == true){SgoMiKiuCg = false;}
      if(thAdodQpGm == true){thAdodQpGm = false;}
      if(HHZjemByew == true){HHZjemByew = false;}
      if(sSGblttpyk == true){sSGblttpyk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOTFFMDKKC
{ 
  void NoxVpDcZAy()
  { 
      bool bpWqfdDiVO = false;
      bool wfumCNQBCY = false;
      bool twUyMgHThP = false;
      bool HNXCAzsYup = false;
      bool jRktfYsUqt = false;
      bool hVgZofVYdz = false;
      bool VjAGGhHrmD = false;
      bool TrGLnbLaRn = false;
      bool mmbnglfyMU = false;
      bool cUuuUARdmy = false;
      bool RAgmZpOVkN = false;
      bool TtGoLhHLYU = false;
      bool BIfSZzwKqn = false;
      bool KhmTWlGnNq = false;
      bool WKNzAhOFjl = false;
      bool rFERwIUONa = false;
      bool tDdxDlGlSY = false;
      bool bTxhypufRq = false;
      bool jpaEwEcVXN = false;
      bool RqamwSfQuO = false;
      string rMygJDpmyn;
      string ZRjQeUcGlQ;
      string asqoNqmEAm;
      string DmWVzuKQzM;
      string TDORMrzPHM;
      string GOfgpzUJTR;
      string QkmKkmtNQi;
      string KLHZwWdYcU;
      string rWxngnGpez;
      string aAwhwhQDgZ;
      string ykzYBtHGjT;
      string UugyYsnzdw;
      string fDiQIJOYdN;
      string FarCWHWXlm;
      string gAFLdeTyIC;
      string tQZkttChPr;
      string ehcVNtDdaR;
      string VPNqOexWlc;
      string oQQaTnAGIc;
      string EoHtIzXjyj;
      if(rMygJDpmyn == ykzYBtHGjT){bpWqfdDiVO = true;}
      else if(ykzYBtHGjT == rMygJDpmyn){RAgmZpOVkN = true;}
      if(ZRjQeUcGlQ == UugyYsnzdw){wfumCNQBCY = true;}
      else if(UugyYsnzdw == ZRjQeUcGlQ){TtGoLhHLYU = true;}
      if(asqoNqmEAm == fDiQIJOYdN){twUyMgHThP = true;}
      else if(fDiQIJOYdN == asqoNqmEAm){BIfSZzwKqn = true;}
      if(DmWVzuKQzM == FarCWHWXlm){HNXCAzsYup = true;}
      else if(FarCWHWXlm == DmWVzuKQzM){KhmTWlGnNq = true;}
      if(TDORMrzPHM == gAFLdeTyIC){jRktfYsUqt = true;}
      else if(gAFLdeTyIC == TDORMrzPHM){WKNzAhOFjl = true;}
      if(GOfgpzUJTR == tQZkttChPr){hVgZofVYdz = true;}
      else if(tQZkttChPr == GOfgpzUJTR){rFERwIUONa = true;}
      if(QkmKkmtNQi == ehcVNtDdaR){VjAGGhHrmD = true;}
      else if(ehcVNtDdaR == QkmKkmtNQi){tDdxDlGlSY = true;}
      if(KLHZwWdYcU == VPNqOexWlc){TrGLnbLaRn = true;}
      if(rWxngnGpez == oQQaTnAGIc){mmbnglfyMU = true;}
      if(aAwhwhQDgZ == EoHtIzXjyj){cUuuUARdmy = true;}
      while(VPNqOexWlc == KLHZwWdYcU){bTxhypufRq = true;}
      while(oQQaTnAGIc == oQQaTnAGIc){jpaEwEcVXN = true;}
      while(EoHtIzXjyj == EoHtIzXjyj){RqamwSfQuO = true;}
      if(bpWqfdDiVO == true){bpWqfdDiVO = false;}
      if(wfumCNQBCY == true){wfumCNQBCY = false;}
      if(twUyMgHThP == true){twUyMgHThP = false;}
      if(HNXCAzsYup == true){HNXCAzsYup = false;}
      if(jRktfYsUqt == true){jRktfYsUqt = false;}
      if(hVgZofVYdz == true){hVgZofVYdz = false;}
      if(VjAGGhHrmD == true){VjAGGhHrmD = false;}
      if(TrGLnbLaRn == true){TrGLnbLaRn = false;}
      if(mmbnglfyMU == true){mmbnglfyMU = false;}
      if(cUuuUARdmy == true){cUuuUARdmy = false;}
      if(RAgmZpOVkN == true){RAgmZpOVkN = false;}
      if(TtGoLhHLYU == true){TtGoLhHLYU = false;}
      if(BIfSZzwKqn == true){BIfSZzwKqn = false;}
      if(KhmTWlGnNq == true){KhmTWlGnNq = false;}
      if(WKNzAhOFjl == true){WKNzAhOFjl = false;}
      if(rFERwIUONa == true){rFERwIUONa = false;}
      if(tDdxDlGlSY == true){tDdxDlGlSY = false;}
      if(bTxhypufRq == true){bTxhypufRq = false;}
      if(jpaEwEcVXN == true){jpaEwEcVXN = false;}
      if(RqamwSfQuO == true){RqamwSfQuO = false;}
    } 
}; 
