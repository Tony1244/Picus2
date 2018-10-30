#include "Misc.h"


using namespace Client;
//[junk_enable /]
//[enc_string_enable /]
void CMisc::OnRender()
{
	int punch_x = (int)g_vCenterScreen.x + (int)g_pPlayers->GetLocal()->vAimPunch.y * 10;
	int punch_y = (int)g_vCenterScreen.y + (int)g_pPlayers->GetLocal()->vAimPunch.x * 10;

	if (Settings::Misc::misc_Punch)
	{
		CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		if (Interfaces::Engine()->IsInGame() && localplayer)
		{
			Vector ViewAngles;
			Interfaces::Engine()->GetViewAngles(ViewAngles);
			ViewAngles += (localplayer->GetAimPunchAngle()) * 2.f;

			Vector fowardVec;
			AngleVectors(ViewAngles, fowardVec);
			fowardVec *= 10000;

			Vector start = localplayer->GetEyePosition();
			Vector end = start + fowardVec, endScreen;

			if (WorldToScreen(end, endScreen) && IsLocalAlive())
			{
				g_pRender->DrawLine(punch_x - 4, punch_y, punch_x + 4, punch_y, Color::White());
				g_pRender->DrawLine(punch_x, punch_y - 4, punch_x, punch_y + 4, Color::White());
			}
		}
	}
}

void CMisc::OnCreateMove(CUserCmd* pCmd)
{

	/*if (Settings::Misc::misc_fakeping) 
	{
		ConVar* sv_cheats = Interfaces::GetConVar()->FindVar("sv_cheats");
		SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
		sv_cheats_spoofed->SetInt(0);

		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakeloss 3");
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakelag 75");
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakejitter 53535353");
	}
	else
	{
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakeloss 0");
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakelag 0");
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakejitter 0");
	}
	*/
	static bool gravityTurnedOn = false;

	if (Settings::Misc::misc_ragdoll_gravity) {
		ConVar* Gravity = Interfaces::GetConVar()->FindVar("cl_ragdoll_gravity");
		Gravity->SetValue(Settings::Misc::misc_ragdoll_gravity_amount);
		gravityTurnedOn = true;
	}
	else {
		if (gravityTurnedOn == true) {
			ConVar* Gravity = Interfaces::GetConVar()->FindVar("cl_ragdoll_gravity");
			Gravity->SetValue(800.f);
			gravityTurnedOn = false;
		}
	}

	static bool pushscaleTurnedOn = false;

	if (Settings::Misc::misc_pushscale) {
		ConVar* Pushscale = Interfaces::GetConVar()->FindVar("phys_pushscale");
		Pushscale->SetValue(Settings::Misc::misc_pushscale_amount);
		pushscaleTurnedOn = true;
	}
	else {
		if (pushscaleTurnedOn == true) {
			ConVar* Pushscale = Interfaces::GetConVar()->FindVar("phys_pushscale");
			Pushscale->SetValue(600.f);
			pushscaleTurnedOn = false;
		}
	}

	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	int flag = *(PINT)((DWORD)pPlayer + 600); // offset for movetype 

	if (Settings::Misc::misc_Bhop)
	{
		if (!(flag & MOVETYPE_LADDER))
		{
			if (pCmd->buttons & IN_JUMP && !(g_pPlayers->GetLocal()->iFlags & FL_ONGROUND))
			{
				pCmd->buttons &= ~IN_JUMP;
			}
		}
	}

	if (Settings::Misc::misc_spamregular)
		ChatSpamRegular();

	if (Settings::Misc::misc_spamrandom)
		ChatSpamRandom();

	if (Settings::Misc::misc_Clan > 0)
		ClanTag();

	ConVar* skybox = Interfaces::GetConVar()->FindVar("sv_skyname");

	if (Settings::Misc::misc_SkyName) { if (skybox) skybox->SetValue(Settings::Misc::misc_SkyName); }
	if (Settings::Misc::misc_NoSky) { if (skybox) skybox->SetValue("sky_l4d_rural02_ldr"); }

	ConVar* snow = Interfaces::GetConVar()->FindVar("mat_drawgray");

	if (Settings::Misc::misc_Snow)
	{
		snow->SetValue(1);
	}
	else
	{
		snow->SetValue(0);
	}

	ConVar* postprocess = Interfaces::GetConVar()->FindVar("mat_postprocess_enable");

	if (Settings::Misc::misc_EPostprocess)
	{
		if (Interfaces::Engine()->IsInGame())
		{
			postprocess->SetValue(0);
		}
	}
	else
	{
		if (Interfaces::Engine()->IsInGame())
		{
			postprocess->SetValue(1);
		}
	}


	static ConVar* grenadetraj = Interfaces::GetConVar()->FindVar("sv_grenade_trajectory");

	if (Settings::Misc::misc_GrenadeTrajectory)
	{
		if (Interfaces::Engine()->IsInGame())
		{
			grenadetraj->SetValue(1);
		}
	}
	else
	{
		if (Interfaces::Engine()->IsInGame())
		{
			grenadetraj->SetValue(0);
		}
	}

	static ConVar* fullbright = Interfaces::GetConVar()->FindVar("mat_fullbright");
	if (Settings::Misc::misc_FullBright)
	{
		if (Interfaces::Engine()->IsInGame())
		{
			fullbright->SetValue(1);
		}
	}
	else {
		if (Interfaces::Engine()->IsInGame())
		{
			fullbright->SetValue(0);
		}
	}

	/*
	if (Settings::Misc::misc_GrenadeTrajectory)
	{
	if (Interfaces::Engine()->IsInGame())
	{
	ConVar* sv_grenade_trajectory = Interfaces::GetConVar()->FindVar("sv_grenade_trajectory");
	SpoofedConvar* sv_grenade_spoofed = new SpoofedConvar(sv_grenade_trajectory);
	sv_grenade_spoofed->SetInt(1);
	}
	}
	else
	{
	if (Interfaces::Engine()->IsInGame())
	{
	ConVar* sv_grenade_trajectory = Interfaces::GetConVar()->FindVar("sv_grenade_trajectory");
	SpoofedConvar* sv_grenade_spoofed = new SpoofedConvar(sv_grenade_trajectory);
	sv_grenade_spoofed->SetInt(0);
	}

	}
	*/

}

void CMisc::FrameStageNotify(ClientFrameStage_t Stage)
{
	CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (Interfaces::Engine()->IsInGame() && localplayer && Stage == ClientFrameStage_t::FRAME_RENDER_START)
	{
		static QAngle vecAngles;
		Interfaces::Engine()->GetViewAngles(vecAngles);

		
	}
}

void CMisc::OnDrawModelExecute()
{
	static bool NoSmoke = false;
	static bool NoFlashReset = false;
	static bool WireFrameSmoke = false;

	if (Settings::Misc::misc_NoFlash && !NoFlashReset)
	{
		IMaterial* flash = Interfaces::MaterialSystem()->FindMaterial(
			"effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* flashWhite = Interfaces::MaterialSystem()->FindMaterial("effects\\flashbang_white",
			TEXTURE_GROUP_CLIENT_EFFECTS);

		if (flash && flashWhite)
		{
			flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			flashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);

			NoFlashReset = true;
		}
	}
	else if (!Settings::Misc::misc_NoFlash && NoFlashReset)
	{
		IMaterial* flash = Interfaces::MaterialSystem()->FindMaterial(
			"effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* flashWhite = Interfaces::MaterialSystem()->FindMaterial("effects\\flashbang_white",
			TEXTURE_GROUP_CLIENT_EFFECTS);

		if (flash && flashWhite)
		{
			flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			flashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

			NoFlashReset = false;
		}
	}

	if (Settings::Misc::misc_NoSmoke)
	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);

			NoSmoke = true;
		}
	}


	else if (!Settings::Misc::misc_NoSmoke)
	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

			NoSmoke = false;

		}
	}


	if (Settings::Misc::misc_wireframesmoke)

	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);

			WireFrameSmoke = true;
		}
	}

	else if (!Settings::Misc::misc_wireframesmoke)

	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);

			WireFrameSmoke = false;
		}
	}

}

void CMisc::OnPlaySound(const char* pszSoundName)
{
	if (Settings::Misc::misc_AutoAccept && !strcmp(pszSoundName, "!UI/competitive_accept_beep.wav"))
	{
		typedef void(*IsReadyCallBackFn)();

		IsReadyCallBackFn IsReadyCallBack = 0;

		if (!IsReadyCallBack)
		{
			IsReadyCallBack = (IsReadyCallBackFn)(
				CSX::Memory::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 83 BE", 0));

#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::IsReadyCallBack = %X", IsReadyCallBack);
#endif
		}

		if (IsReadyCallBack)
		{
			IsReadyCallBack();
		}
	}
}

void CMisc::OnOverrideView(CViewSetup * pSetup)
{
	if (Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot())
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!pPlayer)
			return;

		if (pPlayer->GetIsScoped())
			return;

		if (pPlayer->IsDead())
		{
			if (pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget())
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

			if (!pPlayer)
				return;
		}

		pSetup->fov = (float)Settings::Misc::misc_FovView;
	}
}

void CMisc::OnGetViewModelFOV(float& fov)
{
	if (Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot())
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!pPlayer)
			return;

		if (pPlayer->IsDead())
		{
			if (pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget())
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

			if (!pPlayer)
				return;
		}

		fov = (float)Settings::Misc::misc_FovModelView;
	}
}

vector<int> CMisc::GetObservervators(int playerId)
{
	vector<int> SpectatorList;

	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(playerId);

	if (!pPlayer)
		return SpectatorList;

	if (pPlayer->IsDead())
	{
		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

		if (!pObserverTarget)
			return SpectatorList;

		pPlayer = pObserverTarget;
	}

	for (int PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CBaseEntity* pCheckPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(PlayerIndex);

		if (!pCheckPlayer)
			continue;

		if (pCheckPlayer->IsDormant() || !pCheckPlayer->IsDead())
			continue;

		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pCheckPlayer->GetObserverTarget());

		if (!pObserverTarget)
			continue;

		if (pPlayer != pObserverTarget)
			continue;

		SpectatorList.push_back(PlayerIndex);
	}

	return SpectatorList;
}

// old speclist
/*
void CMisc::OnRenderSpectatorList()
{
	if (Settings::Misc::misc_Spectators)
	{
		int specs = 0;
		int modes = 0;
		std::string spect = "";
		std::string mode = "";
		int DrawIndex = 1;
		for (int playerId : GetObservervators(Interfaces::Engine()->GetLocalPlayer()))
		{
			if (playerId == Interfaces::Engine()->GetLocalPlayer())
				continue;
			CBaseEntity * pPlayer = (CBaseEntity *)Interfaces::EntityList()->GetClientEntity(playerId);
			if (!pPlayer)
				continue;
			PlayerInfo Pinfo;
			Interfaces::Engine()->GetPlayerInfo(playerId, &Pinfo);
			if (Pinfo.m_bIsFakePlayer)
				continue;
			if (g_pRender)
			{
				spect += Pinfo.m_szPlayerName;
				spect += "\n";
				specs++;
				if (spect != "")
				{
					Color PlayerObsColor;
					// [junk_disable /] 
					switch (pPlayer->GetObserverMode())
					{
					case ObserverMode_t::OBS_MODE_IN_EYE:
						mode += ("Perspective");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_CHASE:
						mode += ("3rd Person");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_ROAMING:
						mode += ("Free look");
						PlayerObsColor = Color::Red();
						break;
					case ObserverMode_t::OBS_MODE_DEATHCAM:
						mode += ("Deathcam");
						PlayerObsColor = Color::Yellow();
						break;
					case ObserverMode_t::OBS_MODE_FREEZECAM:
						mode += ("Freezecam");
						PlayerObsColor = Color::LimeGreen();
						break;
					case ObserverMode_t::OBS_MODE_FIXED:
						mode += ("Fixed");
						PlayerObsColor = Color::Orange();
						break;
					default:
						break;
					}
					mode += "\n";
					modes++;
				}
			}
		}
		if (ImGui::Begin("Spectator List", &Settings::Misc::misc_Spectators, ImVec2(200, 100), 0.9f, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders))
		{
			if (specs> 0) spect += "\n";
			if (modes> 0) mode += "\n";
			ImVec2 size = ImGui::CalcTextSize(spect.c_str());
			ImGui::Columns(2);
			ImGui::Text("Name");
			ImGui::NextColumn();
			ImGui::Text("Mode");
			ImGui::NextColumn();
			ImGui::Separator();
			ImGui::Text(spect.c_str());
			ImGui::NextColumn();
			ImGui::Text(mode.c_str());
			ImGui::Columns(1);
			DrawIndex++;
		}
		ImGui::End();
	}
}
*/

// new speclist
void CMisc::OnRenderSpectatorList()
{
	if (Settings::Misc::misc_Spectators)
	{
		int DrawIndex = 1;

		for (int playerId : GetObservervators(Interfaces::Engine()->GetLocalPlayer()))
		{
			if (playerId == Interfaces::Engine()->GetLocalPlayer())
				continue;

			CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(playerId);

			if (!pPlayer)
				continue;

			PlayerInfo Pinfo;
			Interfaces::Engine()->GetPlayerInfo(playerId, &Pinfo);

			if (Pinfo.m_bIsFakePlayer)
				continue;

			if (g_pRender)
			{
				string Name = Pinfo.m_szPlayerName;

				if (Name != "")
				{
					Color PlayerObsColor;
					//[junk_disable /]
					switch (pPlayer->GetObserverMode())
					{
					case ObserverMode_t::OBS_MODE_IN_EYE:
						Name.append(" - Perspective");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_CHASE:
						Name.append(" - 3rd person");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_ROAMING:
						Name.append(" - Free look");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_DEATHCAM:
						Name.append(" - Deathcam");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_FREEZECAM:
						Name.append(" - Freezecam");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_FIXED:
						Name.append(" - Fixed");
						PlayerObsColor = Color::White();
						break;
					default:
						break;
					}
					//[junk_enable /]
					g_pRender->Text(iScreenWidth - 300, 300 + (DrawIndex * 13), false, true, PlayerObsColor, "%s", Name.c_str());
					DrawIndex++;
				}
			}
		}
	}
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZZMIZACGD
{ 
  void qPRYcStBOO()
  { 
      bool FyhUnrmTsx = false;
      bool dmClYHLUlh = false;
      bool oUtMaKLhun = false;
      bool qWjyuHHcPt = false;
      bool MicUKtWDpm = false;
      bool bqJSMjDVsd = false;
      bool fFXEGHCDqQ = false;
      bool AhEqVFrZCg = false;
      bool mIrILzMRlK = false;
      bool DlikNHLXNC = false;
      bool qSLYmslRwG = false;
      bool rcSMpWNPrG = false;
      bool ujQfNOyTdN = false;
      bool tTLzoUxSUS = false;
      bool MtUeSZSWuq = false;
      bool sueGHGBfLY = false;
      bool uSniMYRTXV = false;
      bool ZttZtAOlNm = false;
      bool ubXmTynFqi = false;
      bool SRHwWtFlRt = false;
      string HWrThBVcmr;
      string JqLDneeUdT;
      string XwwJMTQdtn;
      string ioglJIXfET;
      string PKqGGrTqQD;
      string XAHIhKahHN;
      string kqhzJTKZsf;
      string GzQJENFpDT;
      string AZNqQhhXEz;
      string hoXpiXbrxl;
      string htxkwXjyET;
      string FjdmNLdqha;
      string llVtxRaZaf;
      string kMsRkFbctr;
      string yiTjtxKkbW;
      string sjJVzwYCme;
      string xJXXirqMCH;
      string iBxpcCRkAA;
      string GpyDlADWRo;
      string gYoOtnLuAB;
      if(HWrThBVcmr == htxkwXjyET){FyhUnrmTsx = true;}
      else if(htxkwXjyET == HWrThBVcmr){qSLYmslRwG = true;}
      if(JqLDneeUdT == FjdmNLdqha){dmClYHLUlh = true;}
      else if(FjdmNLdqha == JqLDneeUdT){rcSMpWNPrG = true;}
      if(XwwJMTQdtn == llVtxRaZaf){oUtMaKLhun = true;}
      else if(llVtxRaZaf == XwwJMTQdtn){ujQfNOyTdN = true;}
      if(ioglJIXfET == kMsRkFbctr){qWjyuHHcPt = true;}
      else if(kMsRkFbctr == ioglJIXfET){tTLzoUxSUS = true;}
      if(PKqGGrTqQD == yiTjtxKkbW){MicUKtWDpm = true;}
      else if(yiTjtxKkbW == PKqGGrTqQD){MtUeSZSWuq = true;}
      if(XAHIhKahHN == sjJVzwYCme){bqJSMjDVsd = true;}
      else if(sjJVzwYCme == XAHIhKahHN){sueGHGBfLY = true;}
      if(kqhzJTKZsf == xJXXirqMCH){fFXEGHCDqQ = true;}
      else if(xJXXirqMCH == kqhzJTKZsf){uSniMYRTXV = true;}
      if(GzQJENFpDT == iBxpcCRkAA){AhEqVFrZCg = true;}
      if(AZNqQhhXEz == GpyDlADWRo){mIrILzMRlK = true;}
      if(hoXpiXbrxl == gYoOtnLuAB){DlikNHLXNC = true;}
      while(iBxpcCRkAA == GzQJENFpDT){ZttZtAOlNm = true;}
      while(GpyDlADWRo == GpyDlADWRo){ubXmTynFqi = true;}
      while(gYoOtnLuAB == gYoOtnLuAB){SRHwWtFlRt = true;}
      if(FyhUnrmTsx == true){FyhUnrmTsx = false;}
      if(dmClYHLUlh == true){dmClYHLUlh = false;}
      if(oUtMaKLhun == true){oUtMaKLhun = false;}
      if(qWjyuHHcPt == true){qWjyuHHcPt = false;}
      if(MicUKtWDpm == true){MicUKtWDpm = false;}
      if(bqJSMjDVsd == true){bqJSMjDVsd = false;}
      if(fFXEGHCDqQ == true){fFXEGHCDqQ = false;}
      if(AhEqVFrZCg == true){AhEqVFrZCg = false;}
      if(mIrILzMRlK == true){mIrILzMRlK = false;}
      if(DlikNHLXNC == true){DlikNHLXNC = false;}
      if(qSLYmslRwG == true){qSLYmslRwG = false;}
      if(rcSMpWNPrG == true){rcSMpWNPrG = false;}
      if(ujQfNOyTdN == true){ujQfNOyTdN = false;}
      if(tTLzoUxSUS == true){tTLzoUxSUS = false;}
      if(MtUeSZSWuq == true){MtUeSZSWuq = false;}
      if(sueGHGBfLY == true){sueGHGBfLY = false;}
      if(uSniMYRTXV == true){uSniMYRTXV = false;}
      if(ZttZtAOlNm == true){ZttZtAOlNm = false;}
      if(ubXmTynFqi == true){ubXmTynFqi = false;}
      if(SRHwWtFlRt == true){SRHwWtFlRt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQBPKAMLXP
{ 
  void cPVChTbEUx()
  { 
      bool IhooYudHiL = false;
      bool UWKoKdCXDV = false;
      bool ImNGePVHrH = false;
      bool ahBhmkfHCN = false;
      bool lmdmohRhRy = false;
      bool YVwJJUThKJ = false;
      bool ZWOaklUcBY = false;
      bool xtUoiUJaRw = false;
      bool xmpsiFlrXS = false;
      bool RxxsmPXDBC = false;
      bool NofrBeAHZn = false;
      bool LsPOLmfVrf = false;
      bool AbEiHAxbBT = false;
      bool xFYPhIGxrD = false;
      bool FdSjHXgigA = false;
      bool iCKVBlkxkA = false;
      bool hXFFqFTAfC = false;
      bool fhcnaVIUbi = false;
      bool SNuBktuDOw = false;
      bool XJMqVgYMrB = false;
      string qSTSpNodoF;
      string LyLgQAmFno;
      string ZUiGdnOkqo;
      string BQdgRXzaSx;
      string xqXdkSeujs;
      string mHhEzWjMoB;
      string zEmzDtTePs;
      string AMmpriwEUL;
      string JSAxCtiYgt;
      string nlkQxsDYZq;
      string yAeqraUqMQ;
      string ZeqdrfDowI;
      string LuxUFObVrz;
      string eWddMImJFb;
      string ZqMQUIuGYR;
      string oOcRfDDKld;
      string yyyMlCAMQj;
      string rsjUiThgzw;
      string TUwaJQtMyJ;
      string FcXbcaszeR;
      if(qSTSpNodoF == yAeqraUqMQ){IhooYudHiL = true;}
      else if(yAeqraUqMQ == qSTSpNodoF){NofrBeAHZn = true;}
      if(LyLgQAmFno == ZeqdrfDowI){UWKoKdCXDV = true;}
      else if(ZeqdrfDowI == LyLgQAmFno){LsPOLmfVrf = true;}
      if(ZUiGdnOkqo == LuxUFObVrz){ImNGePVHrH = true;}
      else if(LuxUFObVrz == ZUiGdnOkqo){AbEiHAxbBT = true;}
      if(BQdgRXzaSx == eWddMImJFb){ahBhmkfHCN = true;}
      else if(eWddMImJFb == BQdgRXzaSx){xFYPhIGxrD = true;}
      if(xqXdkSeujs == ZqMQUIuGYR){lmdmohRhRy = true;}
      else if(ZqMQUIuGYR == xqXdkSeujs){FdSjHXgigA = true;}
      if(mHhEzWjMoB == oOcRfDDKld){YVwJJUThKJ = true;}
      else if(oOcRfDDKld == mHhEzWjMoB){iCKVBlkxkA = true;}
      if(zEmzDtTePs == yyyMlCAMQj){ZWOaklUcBY = true;}
      else if(yyyMlCAMQj == zEmzDtTePs){hXFFqFTAfC = true;}
      if(AMmpriwEUL == rsjUiThgzw){xtUoiUJaRw = true;}
      if(JSAxCtiYgt == TUwaJQtMyJ){xmpsiFlrXS = true;}
      if(nlkQxsDYZq == FcXbcaszeR){RxxsmPXDBC = true;}
      while(rsjUiThgzw == AMmpriwEUL){fhcnaVIUbi = true;}
      while(TUwaJQtMyJ == TUwaJQtMyJ){SNuBktuDOw = true;}
      while(FcXbcaszeR == FcXbcaszeR){XJMqVgYMrB = true;}
      if(IhooYudHiL == true){IhooYudHiL = false;}
      if(UWKoKdCXDV == true){UWKoKdCXDV = false;}
      if(ImNGePVHrH == true){ImNGePVHrH = false;}
      if(ahBhmkfHCN == true){ahBhmkfHCN = false;}
      if(lmdmohRhRy == true){lmdmohRhRy = false;}
      if(YVwJJUThKJ == true){YVwJJUThKJ = false;}
      if(ZWOaklUcBY == true){ZWOaklUcBY = false;}
      if(xtUoiUJaRw == true){xtUoiUJaRw = false;}
      if(xmpsiFlrXS == true){xmpsiFlrXS = false;}
      if(RxxsmPXDBC == true){RxxsmPXDBC = false;}
      if(NofrBeAHZn == true){NofrBeAHZn = false;}
      if(LsPOLmfVrf == true){LsPOLmfVrf = false;}
      if(AbEiHAxbBT == true){AbEiHAxbBT = false;}
      if(xFYPhIGxrD == true){xFYPhIGxrD = false;}
      if(FdSjHXgigA == true){FdSjHXgigA = false;}
      if(iCKVBlkxkA == true){iCKVBlkxkA = false;}
      if(hXFFqFTAfC == true){hXFFqFTAfC = false;}
      if(fhcnaVIUbi == true){fhcnaVIUbi = false;}
      if(SNuBktuDOw == true){SNuBktuDOw = false;}
      if(XJMqVgYMrB == true){XJMqVgYMrB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKIFWZHXNJ
{ 
  void zuGAnBhVtq()
  { 
      bool TFxSbtmhIP = false;
      bool HJUoVUixhD = false;
      bool EojZquPOpF = false;
      bool BeezeBQaRL = false;
      bool AEySuWeVXJ = false;
      bool diaGSeVWag = false;
      bool dYrDOceVJU = false;
      bool DHfWCAqQeU = false;
      bool QtpfaRDYgA = false;
      bool ftAkgbLuES = false;
      bool qIMDFWDEDS = false;
      bool mFrGQjhLbw = false;
      bool YGnJoJHtoa = false;
      bool nwLLcHgmaE = false;
      bool OyUOMaBtUw = false;
      bool sASItkUCOw = false;
      bool PIObdqsgcJ = false;
      bool CukXgakYwN = false;
      bool HNZsgmcCRr = false;
      bool ldXdoGisjU = false;
      string fTBYHbCsaS;
      string xGpVIDFEoB;
      string tcTUPhVWkG;
      string CMEStuCLVP;
      string ciFAmiMCRH;
      string SxgpnCzfIZ;
      string GfIUPjBWaM;
      string AshZYLXThf;
      string VSEcmFeOeq;
      string wVDwJxajkC;
      string hpaEGZOHQc;
      string eeybEmaehJ;
      string FlqiQdplQb;
      string jnifyfrzVN;
      string pXyCMQXaqW;
      string VwCaxuyrnb;
      string icqnrpwScY;
      string uaITSgnnWz;
      string GOtsGnlHiC;
      string gAKtdNfJJW;
      if(fTBYHbCsaS == hpaEGZOHQc){TFxSbtmhIP = true;}
      else if(hpaEGZOHQc == fTBYHbCsaS){qIMDFWDEDS = true;}
      if(xGpVIDFEoB == eeybEmaehJ){HJUoVUixhD = true;}
      else if(eeybEmaehJ == xGpVIDFEoB){mFrGQjhLbw = true;}
      if(tcTUPhVWkG == FlqiQdplQb){EojZquPOpF = true;}
      else if(FlqiQdplQb == tcTUPhVWkG){YGnJoJHtoa = true;}
      if(CMEStuCLVP == jnifyfrzVN){BeezeBQaRL = true;}
      else if(jnifyfrzVN == CMEStuCLVP){nwLLcHgmaE = true;}
      if(ciFAmiMCRH == pXyCMQXaqW){AEySuWeVXJ = true;}
      else if(pXyCMQXaqW == ciFAmiMCRH){OyUOMaBtUw = true;}
      if(SxgpnCzfIZ == VwCaxuyrnb){diaGSeVWag = true;}
      else if(VwCaxuyrnb == SxgpnCzfIZ){sASItkUCOw = true;}
      if(GfIUPjBWaM == icqnrpwScY){dYrDOceVJU = true;}
      else if(icqnrpwScY == GfIUPjBWaM){PIObdqsgcJ = true;}
      if(AshZYLXThf == uaITSgnnWz){DHfWCAqQeU = true;}
      if(VSEcmFeOeq == GOtsGnlHiC){QtpfaRDYgA = true;}
      if(wVDwJxajkC == gAKtdNfJJW){ftAkgbLuES = true;}
      while(uaITSgnnWz == AshZYLXThf){CukXgakYwN = true;}
      while(GOtsGnlHiC == GOtsGnlHiC){HNZsgmcCRr = true;}
      while(gAKtdNfJJW == gAKtdNfJJW){ldXdoGisjU = true;}
      if(TFxSbtmhIP == true){TFxSbtmhIP = false;}
      if(HJUoVUixhD == true){HJUoVUixhD = false;}
      if(EojZquPOpF == true){EojZquPOpF = false;}
      if(BeezeBQaRL == true){BeezeBQaRL = false;}
      if(AEySuWeVXJ == true){AEySuWeVXJ = false;}
      if(diaGSeVWag == true){diaGSeVWag = false;}
      if(dYrDOceVJU == true){dYrDOceVJU = false;}
      if(DHfWCAqQeU == true){DHfWCAqQeU = false;}
      if(QtpfaRDYgA == true){QtpfaRDYgA = false;}
      if(ftAkgbLuES == true){ftAkgbLuES = false;}
      if(qIMDFWDEDS == true){qIMDFWDEDS = false;}
      if(mFrGQjhLbw == true){mFrGQjhLbw = false;}
      if(YGnJoJHtoa == true){YGnJoJHtoa = false;}
      if(nwLLcHgmaE == true){nwLLcHgmaE = false;}
      if(OyUOMaBtUw == true){OyUOMaBtUw = false;}
      if(sASItkUCOw == true){sASItkUCOw = false;}
      if(PIObdqsgcJ == true){PIObdqsgcJ = false;}
      if(CukXgakYwN == true){CukXgakYwN = false;}
      if(HNZsgmcCRr == true){HNZsgmcCRr = false;}
      if(ldXdoGisjU == true){ldXdoGisjU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTSUFMCHCY
{ 
  void YggMqIQgGt()
  { 
      bool NlCxnxNzyu = false;
      bool LeXzfuHiLo = false;
      bool NbIXXtoXwg = false;
      bool rXAaaSCqdW = false;
      bool dzMViUWIRq = false;
      bool cxgFxlcdZt = false;
      bool HoDQCndxYM = false;
      bool rQEnLOOmoD = false;
      bool WgGEEtqtdo = false;
      bool pXRjOnwwSt = false;
      bool pYjEzLsrth = false;
      bool WooVWaiyMI = false;
      bool xiTjWUzUZW = false;
      bool SRUtMyxBFr = false;
      bool ByAuRAhuMn = false;
      bool FxjKwHFzhd = false;
      bool MYSXPEUuJY = false;
      bool dgrTGyiXSV = false;
      bool lEHkQUhJyF = false;
      bool rxSaecfcfM = false;
      string KhwZHniRAt;
      string fSWgWiQOGT;
      string uafYAkVLaS;
      string NtPLDQthnn;
      string NemrMQKxjp;
      string HdPzZiBXYW;
      string RWpgflCKdF;
      string nhZSFQnmMj;
      string ZXbkLieQlT;
      string PWJRWpoFMa;
      string NzTdBYDxsI;
      string uOLnxsuFVw;
      string GlYJpQYIuO;
      string bhakVZExil;
      string ehWcXBLUTc;
      string ujiPTbaJnk;
      string zuBegMmZSW;
      string oyViQYPwln;
      string EEnSTqzLQt;
      string ztIymjfruK;
      if(KhwZHniRAt == NzTdBYDxsI){NlCxnxNzyu = true;}
      else if(NzTdBYDxsI == KhwZHniRAt){pYjEzLsrth = true;}
      if(fSWgWiQOGT == uOLnxsuFVw){LeXzfuHiLo = true;}
      else if(uOLnxsuFVw == fSWgWiQOGT){WooVWaiyMI = true;}
      if(uafYAkVLaS == GlYJpQYIuO){NbIXXtoXwg = true;}
      else if(GlYJpQYIuO == uafYAkVLaS){xiTjWUzUZW = true;}
      if(NtPLDQthnn == bhakVZExil){rXAaaSCqdW = true;}
      else if(bhakVZExil == NtPLDQthnn){SRUtMyxBFr = true;}
      if(NemrMQKxjp == ehWcXBLUTc){dzMViUWIRq = true;}
      else if(ehWcXBLUTc == NemrMQKxjp){ByAuRAhuMn = true;}
      if(HdPzZiBXYW == ujiPTbaJnk){cxgFxlcdZt = true;}
      else if(ujiPTbaJnk == HdPzZiBXYW){FxjKwHFzhd = true;}
      if(RWpgflCKdF == zuBegMmZSW){HoDQCndxYM = true;}
      else if(zuBegMmZSW == RWpgflCKdF){MYSXPEUuJY = true;}
      if(nhZSFQnmMj == oyViQYPwln){rQEnLOOmoD = true;}
      if(ZXbkLieQlT == EEnSTqzLQt){WgGEEtqtdo = true;}
      if(PWJRWpoFMa == ztIymjfruK){pXRjOnwwSt = true;}
      while(oyViQYPwln == nhZSFQnmMj){dgrTGyiXSV = true;}
      while(EEnSTqzLQt == EEnSTqzLQt){lEHkQUhJyF = true;}
      while(ztIymjfruK == ztIymjfruK){rxSaecfcfM = true;}
      if(NlCxnxNzyu == true){NlCxnxNzyu = false;}
      if(LeXzfuHiLo == true){LeXzfuHiLo = false;}
      if(NbIXXtoXwg == true){NbIXXtoXwg = false;}
      if(rXAaaSCqdW == true){rXAaaSCqdW = false;}
      if(dzMViUWIRq == true){dzMViUWIRq = false;}
      if(cxgFxlcdZt == true){cxgFxlcdZt = false;}
      if(HoDQCndxYM == true){HoDQCndxYM = false;}
      if(rQEnLOOmoD == true){rQEnLOOmoD = false;}
      if(WgGEEtqtdo == true){WgGEEtqtdo = false;}
      if(pXRjOnwwSt == true){pXRjOnwwSt = false;}
      if(pYjEzLsrth == true){pYjEzLsrth = false;}
      if(WooVWaiyMI == true){WooVWaiyMI = false;}
      if(xiTjWUzUZW == true){xiTjWUzUZW = false;}
      if(SRUtMyxBFr == true){SRUtMyxBFr = false;}
      if(ByAuRAhuMn == true){ByAuRAhuMn = false;}
      if(FxjKwHFzhd == true){FxjKwHFzhd = false;}
      if(MYSXPEUuJY == true){MYSXPEUuJY = false;}
      if(dgrTGyiXSV == true){dgrTGyiXSV = false;}
      if(lEHkQUhJyF == true){lEHkQUhJyF = false;}
      if(rxSaecfcfM == true){rxSaecfcfM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEFHZOJEZW
{ 
  void lLhslYzwxy()
  { 
      bool qQhGPQFtcn = false;
      bool oOudlQMuzL = false;
      bool HxCaHruudN = false;
      bool FyjPmcZZcY = false;
      bool ULlZcEbLOT = false;
      bool CnwTDsOHzW = false;
      bool UJPPipefqJ = false;
      bool qlRaqwLbxC = false;
      bool QjfKLQCQLs = false;
      bool ORaGEKwWqm = false;
      bool ZuTFcPVVcH = false;
      bool hlJwGkdEDS = false;
      bool mNTytYKLWf = false;
      bool AnkKcUQZhu = false;
      bool tfnEKcHeAS = false;
      bool gqSXzLbVLD = false;
      bool EKzwHsAzSk = false;
      bool UDWIYHZPmR = false;
      bool QfLDzIVMKQ = false;
      bool stOdpigqxR = false;
      string xsfHMRTzaB;
      string QpLdtNsOfs;
      string PXChqdpuai;
      string zOlBbbqlpR;
      string LGaquWVYHg;
      string PgbQWZqxPh;
      string bXYrBCEKCR;
      string WGXOgJxKlU;
      string IQnsSRmVdB;
      string ksWHpmghos;
      string SKWoKJJNiN;
      string cgKuZKjeYj;
      string OhfAgcjPYs;
      string bOUsCxtyiJ;
      string IYlQYDiahe;
      string DBIFdjdWIg;
      string YsopkNMRrb;
      string PlwObouPad;
      string tIgspZFOOR;
      string TXpBkOjweL;
      if(xsfHMRTzaB == SKWoKJJNiN){qQhGPQFtcn = true;}
      else if(SKWoKJJNiN == xsfHMRTzaB){ZuTFcPVVcH = true;}
      if(QpLdtNsOfs == cgKuZKjeYj){oOudlQMuzL = true;}
      else if(cgKuZKjeYj == QpLdtNsOfs){hlJwGkdEDS = true;}
      if(PXChqdpuai == OhfAgcjPYs){HxCaHruudN = true;}
      else if(OhfAgcjPYs == PXChqdpuai){mNTytYKLWf = true;}
      if(zOlBbbqlpR == bOUsCxtyiJ){FyjPmcZZcY = true;}
      else if(bOUsCxtyiJ == zOlBbbqlpR){AnkKcUQZhu = true;}
      if(LGaquWVYHg == IYlQYDiahe){ULlZcEbLOT = true;}
      else if(IYlQYDiahe == LGaquWVYHg){tfnEKcHeAS = true;}
      if(PgbQWZqxPh == DBIFdjdWIg){CnwTDsOHzW = true;}
      else if(DBIFdjdWIg == PgbQWZqxPh){gqSXzLbVLD = true;}
      if(bXYrBCEKCR == YsopkNMRrb){UJPPipefqJ = true;}
      else if(YsopkNMRrb == bXYrBCEKCR){EKzwHsAzSk = true;}
      if(WGXOgJxKlU == PlwObouPad){qlRaqwLbxC = true;}
      if(IQnsSRmVdB == tIgspZFOOR){QjfKLQCQLs = true;}
      if(ksWHpmghos == TXpBkOjweL){ORaGEKwWqm = true;}
      while(PlwObouPad == WGXOgJxKlU){UDWIYHZPmR = true;}
      while(tIgspZFOOR == tIgspZFOOR){QfLDzIVMKQ = true;}
      while(TXpBkOjweL == TXpBkOjweL){stOdpigqxR = true;}
      if(qQhGPQFtcn == true){qQhGPQFtcn = false;}
      if(oOudlQMuzL == true){oOudlQMuzL = false;}
      if(HxCaHruudN == true){HxCaHruudN = false;}
      if(FyjPmcZZcY == true){FyjPmcZZcY = false;}
      if(ULlZcEbLOT == true){ULlZcEbLOT = false;}
      if(CnwTDsOHzW == true){CnwTDsOHzW = false;}
      if(UJPPipefqJ == true){UJPPipefqJ = false;}
      if(qlRaqwLbxC == true){qlRaqwLbxC = false;}
      if(QjfKLQCQLs == true){QjfKLQCQLs = false;}
      if(ORaGEKwWqm == true){ORaGEKwWqm = false;}
      if(ZuTFcPVVcH == true){ZuTFcPVVcH = false;}
      if(hlJwGkdEDS == true){hlJwGkdEDS = false;}
      if(mNTytYKLWf == true){mNTytYKLWf = false;}
      if(AnkKcUQZhu == true){AnkKcUQZhu = false;}
      if(tfnEKcHeAS == true){tfnEKcHeAS = false;}
      if(gqSXzLbVLD == true){gqSXzLbVLD = false;}
      if(EKzwHsAzSk == true){EKzwHsAzSk = false;}
      if(UDWIYHZPmR == true){UDWIYHZPmR = false;}
      if(QfLDzIVMKQ == true){QfLDzIVMKQ = false;}
      if(stOdpigqxR == true){stOdpigqxR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZISGLPHBX
{ 
  void RhTHXiPXjA()
  { 
      bool QlcIeDXQEF = false;
      bool toSDkwsjUl = false;
      bool zWFJzyZaed = false;
      bool oHnMmrQnMu = false;
      bool RHbptkhjTW = false;
      bool GIiZptfSJf = false;
      bool cxlaQlAGPr = false;
      bool eFXZUquOPN = false;
      bool PpHIWgYNWs = false;
      bool LyefRTVBZH = false;
      bool kbTaqBjJFz = false;
      bool yRDuQmodEj = false;
      bool NmiWfgarHA = false;
      bool UsnHcmVgQU = false;
      bool wOHXtttiPe = false;
      bool erxptxsxtK = false;
      bool ZrBFdFcuRc = false;
      bool RHMimyeKcl = false;
      bool lqccUcwyNe = false;
      bool tYmGuDNCto = false;
      string fytzENMkFU;
      string HSgkzdtLHy;
      string NJIhTUhaeb;
      string mnbhwhkCHh;
      string KLzmIgbZza;
      string FZVWXWpLfi;
      string fkFdhTpyoR;
      string rrEYnBJUZl;
      string sIbDWMRFKZ;
      string qZVYCYGVEo;
      string qckgiMVxhW;
      string MUlsoXIBGU;
      string BjnPZSWfVO;
      string tnQjuPWtUJ;
      string qTXnNVnbie;
      string QEOimGoUHP;
      string ppaSbXEByZ;
      string ANfxdhMACE;
      string etwqypYgwn;
      string ZBmESArEMo;
      if(fytzENMkFU == qckgiMVxhW){QlcIeDXQEF = true;}
      else if(qckgiMVxhW == fytzENMkFU){kbTaqBjJFz = true;}
      if(HSgkzdtLHy == MUlsoXIBGU){toSDkwsjUl = true;}
      else if(MUlsoXIBGU == HSgkzdtLHy){yRDuQmodEj = true;}
      if(NJIhTUhaeb == BjnPZSWfVO){zWFJzyZaed = true;}
      else if(BjnPZSWfVO == NJIhTUhaeb){NmiWfgarHA = true;}
      if(mnbhwhkCHh == tnQjuPWtUJ){oHnMmrQnMu = true;}
      else if(tnQjuPWtUJ == mnbhwhkCHh){UsnHcmVgQU = true;}
      if(KLzmIgbZza == qTXnNVnbie){RHbptkhjTW = true;}
      else if(qTXnNVnbie == KLzmIgbZza){wOHXtttiPe = true;}
      if(FZVWXWpLfi == QEOimGoUHP){GIiZptfSJf = true;}
      else if(QEOimGoUHP == FZVWXWpLfi){erxptxsxtK = true;}
      if(fkFdhTpyoR == ppaSbXEByZ){cxlaQlAGPr = true;}
      else if(ppaSbXEByZ == fkFdhTpyoR){ZrBFdFcuRc = true;}
      if(rrEYnBJUZl == ANfxdhMACE){eFXZUquOPN = true;}
      if(sIbDWMRFKZ == etwqypYgwn){PpHIWgYNWs = true;}
      if(qZVYCYGVEo == ZBmESArEMo){LyefRTVBZH = true;}
      while(ANfxdhMACE == rrEYnBJUZl){RHMimyeKcl = true;}
      while(etwqypYgwn == etwqypYgwn){lqccUcwyNe = true;}
      while(ZBmESArEMo == ZBmESArEMo){tYmGuDNCto = true;}
      if(QlcIeDXQEF == true){QlcIeDXQEF = false;}
      if(toSDkwsjUl == true){toSDkwsjUl = false;}
      if(zWFJzyZaed == true){zWFJzyZaed = false;}
      if(oHnMmrQnMu == true){oHnMmrQnMu = false;}
      if(RHbptkhjTW == true){RHbptkhjTW = false;}
      if(GIiZptfSJf == true){GIiZptfSJf = false;}
      if(cxlaQlAGPr == true){cxlaQlAGPr = false;}
      if(eFXZUquOPN == true){eFXZUquOPN = false;}
      if(PpHIWgYNWs == true){PpHIWgYNWs = false;}
      if(LyefRTVBZH == true){LyefRTVBZH = false;}
      if(kbTaqBjJFz == true){kbTaqBjJFz = false;}
      if(yRDuQmodEj == true){yRDuQmodEj = false;}
      if(NmiWfgarHA == true){NmiWfgarHA = false;}
      if(UsnHcmVgQU == true){UsnHcmVgQU = false;}
      if(wOHXtttiPe == true){wOHXtttiPe = false;}
      if(erxptxsxtK == true){erxptxsxtK = false;}
      if(ZrBFdFcuRc == true){ZrBFdFcuRc = false;}
      if(RHMimyeKcl == true){RHMimyeKcl = false;}
      if(lqccUcwyNe == true){lqccUcwyNe = false;}
      if(tYmGuDNCto == true){tYmGuDNCto = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKNWAURITE
{ 
  void gqVPJErtVw()
  { 
      bool ajuOoiwLmI = false;
      bool PShxOQxseX = false;
      bool SKTWLGrDrh = false;
      bool zqoaDqBiBQ = false;
      bool YrJgmDIEjM = false;
      bool yDLAlQPYCi = false;
      bool prSEIYdHsX = false;
      bool POrOyaBmjI = false;
      bool xnTfjwennm = false;
      bool abfRafZEYO = false;
      bool YAKLxiKxBL = false;
      bool OcotkCYmTL = false;
      bool soSGxmhZmS = false;
      bool BwNVixdHiB = false;
      bool kgmcXxmkgY = false;
      bool GmjMUigDOJ = false;
      bool BkJhKSOSKn = false;
      bool XRDSaLCphz = false;
      bool zwsOLOMBAA = false;
      bool PZrYAAXESF = false;
      string nWWaQYWdxF;
      string yIEPAEpDjY;
      string wCwmuWtdiP;
      string AZVzVgibaS;
      string skZrIpMRKh;
      string tSenWkaiet;
      string ertgEYlEtT;
      string VObQeKcDdE;
      string JcTBVhugbk;
      string GzwgnBqrni;
      string DHXpMepNJM;
      string HWFajBXrLV;
      string dFbINVRtcd;
      string TkOuABFdop;
      string qgWPcitVwl;
      string czgRFyeObp;
      string MujfrWHJZh;
      string wtCVdwhMfe;
      string awyqAUDxpC;
      string WpBzcuwqXF;
      if(nWWaQYWdxF == DHXpMepNJM){ajuOoiwLmI = true;}
      else if(DHXpMepNJM == nWWaQYWdxF){YAKLxiKxBL = true;}
      if(yIEPAEpDjY == HWFajBXrLV){PShxOQxseX = true;}
      else if(HWFajBXrLV == yIEPAEpDjY){OcotkCYmTL = true;}
      if(wCwmuWtdiP == dFbINVRtcd){SKTWLGrDrh = true;}
      else if(dFbINVRtcd == wCwmuWtdiP){soSGxmhZmS = true;}
      if(AZVzVgibaS == TkOuABFdop){zqoaDqBiBQ = true;}
      else if(TkOuABFdop == AZVzVgibaS){BwNVixdHiB = true;}
      if(skZrIpMRKh == qgWPcitVwl){YrJgmDIEjM = true;}
      else if(qgWPcitVwl == skZrIpMRKh){kgmcXxmkgY = true;}
      if(tSenWkaiet == czgRFyeObp){yDLAlQPYCi = true;}
      else if(czgRFyeObp == tSenWkaiet){GmjMUigDOJ = true;}
      if(ertgEYlEtT == MujfrWHJZh){prSEIYdHsX = true;}
      else if(MujfrWHJZh == ertgEYlEtT){BkJhKSOSKn = true;}
      if(VObQeKcDdE == wtCVdwhMfe){POrOyaBmjI = true;}
      if(JcTBVhugbk == awyqAUDxpC){xnTfjwennm = true;}
      if(GzwgnBqrni == WpBzcuwqXF){abfRafZEYO = true;}
      while(wtCVdwhMfe == VObQeKcDdE){XRDSaLCphz = true;}
      while(awyqAUDxpC == awyqAUDxpC){zwsOLOMBAA = true;}
      while(WpBzcuwqXF == WpBzcuwqXF){PZrYAAXESF = true;}
      if(ajuOoiwLmI == true){ajuOoiwLmI = false;}
      if(PShxOQxseX == true){PShxOQxseX = false;}
      if(SKTWLGrDrh == true){SKTWLGrDrh = false;}
      if(zqoaDqBiBQ == true){zqoaDqBiBQ = false;}
      if(YrJgmDIEjM == true){YrJgmDIEjM = false;}
      if(yDLAlQPYCi == true){yDLAlQPYCi = false;}
      if(prSEIYdHsX == true){prSEIYdHsX = false;}
      if(POrOyaBmjI == true){POrOyaBmjI = false;}
      if(xnTfjwennm == true){xnTfjwennm = false;}
      if(abfRafZEYO == true){abfRafZEYO = false;}
      if(YAKLxiKxBL == true){YAKLxiKxBL = false;}
      if(OcotkCYmTL == true){OcotkCYmTL = false;}
      if(soSGxmhZmS == true){soSGxmhZmS = false;}
      if(BwNVixdHiB == true){BwNVixdHiB = false;}
      if(kgmcXxmkgY == true){kgmcXxmkgY = false;}
      if(GmjMUigDOJ == true){GmjMUigDOJ = false;}
      if(BkJhKSOSKn == true){BkJhKSOSKn = false;}
      if(XRDSaLCphz == true){XRDSaLCphz = false;}
      if(zwsOLOMBAA == true){zwsOLOMBAA = false;}
      if(PZrYAAXESF == true){PZrYAAXESF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGZDIWWAYC
{ 
  void GyAaiddZBr()
  { 
      bool wdODKyNqwl = false;
      bool FKzlWxIzUV = false;
      bool biSzMuEqGT = false;
      bool JpftBBXGfg = false;
      bool zaoltARIwq = false;
      bool RbbEwMKOpP = false;
      bool sVkbbOeFkV = false;
      bool ZCTnVBtgEM = false;
      bool cwtOChOaxn = false;
      bool pIPPmdpNJf = false;
      bool VMXaRPHmiu = false;
      bool SdJdmxbWZt = false;
      bool ADIwfQlDBq = false;
      bool LgWYpPYTwl = false;
      bool ZarBVLylco = false;
      bool BSnPeREatA = false;
      bool dElqjlHkmW = false;
      bool YIZmTYLGaT = false;
      bool RzaMprrGsY = false;
      bool KxYuIVoARi = false;
      string UacljqFlqB;
      string lUhssRpyoi;
      string EFWVRcFAeJ;
      string QLIpjRMdjG;
      string fMpPAqWOYH;
      string xSngMPEGUH;
      string lEGhkaMqIb;
      string FLOiDrOHUZ;
      string GpbXLxWacU;
      string NFJcTaGIeZ;
      string eeGxBlEFcU;
      string AxktAwchVn;
      string DkOnNzBlOc;
      string lFbttbjdWZ;
      string sRxIUQUObX;
      string xYmqWsQSiC;
      string jSpAiuUpAY;
      string MzLutknFSx;
      string elJqeNSkXA;
      string LRtToaaxZY;
      if(UacljqFlqB == eeGxBlEFcU){wdODKyNqwl = true;}
      else if(eeGxBlEFcU == UacljqFlqB){VMXaRPHmiu = true;}
      if(lUhssRpyoi == AxktAwchVn){FKzlWxIzUV = true;}
      else if(AxktAwchVn == lUhssRpyoi){SdJdmxbWZt = true;}
      if(EFWVRcFAeJ == DkOnNzBlOc){biSzMuEqGT = true;}
      else if(DkOnNzBlOc == EFWVRcFAeJ){ADIwfQlDBq = true;}
      if(QLIpjRMdjG == lFbttbjdWZ){JpftBBXGfg = true;}
      else if(lFbttbjdWZ == QLIpjRMdjG){LgWYpPYTwl = true;}
      if(fMpPAqWOYH == sRxIUQUObX){zaoltARIwq = true;}
      else if(sRxIUQUObX == fMpPAqWOYH){ZarBVLylco = true;}
      if(xSngMPEGUH == xYmqWsQSiC){RbbEwMKOpP = true;}
      else if(xYmqWsQSiC == xSngMPEGUH){BSnPeREatA = true;}
      if(lEGhkaMqIb == jSpAiuUpAY){sVkbbOeFkV = true;}
      else if(jSpAiuUpAY == lEGhkaMqIb){dElqjlHkmW = true;}
      if(FLOiDrOHUZ == MzLutknFSx){ZCTnVBtgEM = true;}
      if(GpbXLxWacU == elJqeNSkXA){cwtOChOaxn = true;}
      if(NFJcTaGIeZ == LRtToaaxZY){pIPPmdpNJf = true;}
      while(MzLutknFSx == FLOiDrOHUZ){YIZmTYLGaT = true;}
      while(elJqeNSkXA == elJqeNSkXA){RzaMprrGsY = true;}
      while(LRtToaaxZY == LRtToaaxZY){KxYuIVoARi = true;}
      if(wdODKyNqwl == true){wdODKyNqwl = false;}
      if(FKzlWxIzUV == true){FKzlWxIzUV = false;}
      if(biSzMuEqGT == true){biSzMuEqGT = false;}
      if(JpftBBXGfg == true){JpftBBXGfg = false;}
      if(zaoltARIwq == true){zaoltARIwq = false;}
      if(RbbEwMKOpP == true){RbbEwMKOpP = false;}
      if(sVkbbOeFkV == true){sVkbbOeFkV = false;}
      if(ZCTnVBtgEM == true){ZCTnVBtgEM = false;}
      if(cwtOChOaxn == true){cwtOChOaxn = false;}
      if(pIPPmdpNJf == true){pIPPmdpNJf = false;}
      if(VMXaRPHmiu == true){VMXaRPHmiu = false;}
      if(SdJdmxbWZt == true){SdJdmxbWZt = false;}
      if(ADIwfQlDBq == true){ADIwfQlDBq = false;}
      if(LgWYpPYTwl == true){LgWYpPYTwl = false;}
      if(ZarBVLylco == true){ZarBVLylco = false;}
      if(BSnPeREatA == true){BSnPeREatA = false;}
      if(dElqjlHkmW == true){dElqjlHkmW = false;}
      if(YIZmTYLGaT == true){YIZmTYLGaT = false;}
      if(RzaMprrGsY == true){RzaMprrGsY = false;}
      if(KxYuIVoARi == true){KxYuIVoARi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VLBJYJGWRX
{ 
  void UTtDpdTmfx()
  { 
      bool csmNohCUMp = false;
      bool WMIyieLpmb = false;
      bool rPinoRkePX = false;
      bool oaTtlJVKaQ = false;
      bool fyajCmNlpS = false;
      bool wUqXHNKzYX = false;
      bool xWFoBwsOMZ = false;
      bool JBOVusnykC = false;
      bool DyowbTiwmX = false;
      bool zVlDTJsliG = false;
      bool tzYPJtGVbN = false;
      bool YLOVUygIMg = false;
      bool MwboZmPKBl = false;
      bool ABOdIEZYmg = false;
      bool NNTYymHPhU = false;
      bool bjYCtxWjpV = false;
      bool dwTpNXxjMQ = false;
      bool YIVfTzbDpm = false;
      bool fAbgJPbMjL = false;
      bool gpiQCRsdKa = false;
      string tgeuHFDIpt;
      string tHMuPYHmUf;
      string FyuZesNblH;
      string QHcWSDlgmi;
      string BsPuxdBhUg;
      string XMmULukFQN;
      string rbVhcleobM;
      string mZAkdLhzcB;
      string reGFjETHKX;
      string RfQYqZWgRK;
      string zLGIsyLBqz;
      string MkcPVMUQyY;
      string SWeDuGJatE;
      string oBhSBgYyLl;
      string rRQKKfDADd;
      string EGhsqbgCNm;
      string njGlKLDJNo;
      string nVEMfAFTsO;
      string DIXQzhTnaZ;
      string zWkYxIKdzz;
      if(tgeuHFDIpt == zLGIsyLBqz){csmNohCUMp = true;}
      else if(zLGIsyLBqz == tgeuHFDIpt){tzYPJtGVbN = true;}
      if(tHMuPYHmUf == MkcPVMUQyY){WMIyieLpmb = true;}
      else if(MkcPVMUQyY == tHMuPYHmUf){YLOVUygIMg = true;}
      if(FyuZesNblH == SWeDuGJatE){rPinoRkePX = true;}
      else if(SWeDuGJatE == FyuZesNblH){MwboZmPKBl = true;}
      if(QHcWSDlgmi == oBhSBgYyLl){oaTtlJVKaQ = true;}
      else if(oBhSBgYyLl == QHcWSDlgmi){ABOdIEZYmg = true;}
      if(BsPuxdBhUg == rRQKKfDADd){fyajCmNlpS = true;}
      else if(rRQKKfDADd == BsPuxdBhUg){NNTYymHPhU = true;}
      if(XMmULukFQN == EGhsqbgCNm){wUqXHNKzYX = true;}
      else if(EGhsqbgCNm == XMmULukFQN){bjYCtxWjpV = true;}
      if(rbVhcleobM == njGlKLDJNo){xWFoBwsOMZ = true;}
      else if(njGlKLDJNo == rbVhcleobM){dwTpNXxjMQ = true;}
      if(mZAkdLhzcB == nVEMfAFTsO){JBOVusnykC = true;}
      if(reGFjETHKX == DIXQzhTnaZ){DyowbTiwmX = true;}
      if(RfQYqZWgRK == zWkYxIKdzz){zVlDTJsliG = true;}
      while(nVEMfAFTsO == mZAkdLhzcB){YIVfTzbDpm = true;}
      while(DIXQzhTnaZ == DIXQzhTnaZ){fAbgJPbMjL = true;}
      while(zWkYxIKdzz == zWkYxIKdzz){gpiQCRsdKa = true;}
      if(csmNohCUMp == true){csmNohCUMp = false;}
      if(WMIyieLpmb == true){WMIyieLpmb = false;}
      if(rPinoRkePX == true){rPinoRkePX = false;}
      if(oaTtlJVKaQ == true){oaTtlJVKaQ = false;}
      if(fyajCmNlpS == true){fyajCmNlpS = false;}
      if(wUqXHNKzYX == true){wUqXHNKzYX = false;}
      if(xWFoBwsOMZ == true){xWFoBwsOMZ = false;}
      if(JBOVusnykC == true){JBOVusnykC = false;}
      if(DyowbTiwmX == true){DyowbTiwmX = false;}
      if(zVlDTJsliG == true){zVlDTJsliG = false;}
      if(tzYPJtGVbN == true){tzYPJtGVbN = false;}
      if(YLOVUygIMg == true){YLOVUygIMg = false;}
      if(MwboZmPKBl == true){MwboZmPKBl = false;}
      if(ABOdIEZYmg == true){ABOdIEZYmg = false;}
      if(NNTYymHPhU == true){NNTYymHPhU = false;}
      if(bjYCtxWjpV == true){bjYCtxWjpV = false;}
      if(dwTpNXxjMQ == true){dwTpNXxjMQ = false;}
      if(YIVfTzbDpm == true){YIVfTzbDpm = false;}
      if(fAbgJPbMjL == true){fAbgJPbMjL = false;}
      if(gpiQCRsdKa == true){gpiQCRsdKa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROGIKIJSOQ
{ 
  void NdjzbPRHUY()
  { 
      bool HpABiKZsOJ = false;
      bool FDLerxtxZi = false;
      bool IzUSWJBPsI = false;
      bool eoDzDHoqcA = false;
      bool HmKzJbUwyC = false;
      bool WyGzfHVgdY = false;
      bool IJzFdPALbk = false;
      bool IDUYbUoUJu = false;
      bool oFRqlfiDSu = false;
      bool kHMErxmEVs = false;
      bool aITNsSdgXK = false;
      bool SAWijDrITx = false;
      bool gwsgzApQgd = false;
      bool hjzPTgkExS = false;
      bool CBfIckjcTn = false;
      bool FdkXMeOmNr = false;
      bool cNAtchBHPC = false;
      bool SnKAufQkDO = false;
      bool QMwrYDybDo = false;
      bool RxpFpnAket = false;
      string RhHdIgnrKM;
      string UMGXBpHVxN;
      string hbOVEnNsMi;
      string uhXqXoeexP;
      string dArhHCqQtU;
      string lIdUMoTlZU;
      string TteaQmoPzM;
      string LcYhihifOC;
      string xxzqwmDCdi;
      string UrFbwiUQRT;
      string MaQgJJiwkd;
      string FnXWXWunec;
      string ilkQqSWwlz;
      string NRNtoVfRgl;
      string DHRzcgUhEY;
      string nflnkZpzpq;
      string lmKkQnZdhC;
      string pdGsZbUlnK;
      string yorMLgfZIO;
      string ffbpzQwfin;
      if(RhHdIgnrKM == MaQgJJiwkd){HpABiKZsOJ = true;}
      else if(MaQgJJiwkd == RhHdIgnrKM){aITNsSdgXK = true;}
      if(UMGXBpHVxN == FnXWXWunec){FDLerxtxZi = true;}
      else if(FnXWXWunec == UMGXBpHVxN){SAWijDrITx = true;}
      if(hbOVEnNsMi == ilkQqSWwlz){IzUSWJBPsI = true;}
      else if(ilkQqSWwlz == hbOVEnNsMi){gwsgzApQgd = true;}
      if(uhXqXoeexP == NRNtoVfRgl){eoDzDHoqcA = true;}
      else if(NRNtoVfRgl == uhXqXoeexP){hjzPTgkExS = true;}
      if(dArhHCqQtU == DHRzcgUhEY){HmKzJbUwyC = true;}
      else if(DHRzcgUhEY == dArhHCqQtU){CBfIckjcTn = true;}
      if(lIdUMoTlZU == nflnkZpzpq){WyGzfHVgdY = true;}
      else if(nflnkZpzpq == lIdUMoTlZU){FdkXMeOmNr = true;}
      if(TteaQmoPzM == lmKkQnZdhC){IJzFdPALbk = true;}
      else if(lmKkQnZdhC == TteaQmoPzM){cNAtchBHPC = true;}
      if(LcYhihifOC == pdGsZbUlnK){IDUYbUoUJu = true;}
      if(xxzqwmDCdi == yorMLgfZIO){oFRqlfiDSu = true;}
      if(UrFbwiUQRT == ffbpzQwfin){kHMErxmEVs = true;}
      while(pdGsZbUlnK == LcYhihifOC){SnKAufQkDO = true;}
      while(yorMLgfZIO == yorMLgfZIO){QMwrYDybDo = true;}
      while(ffbpzQwfin == ffbpzQwfin){RxpFpnAket = true;}
      if(HpABiKZsOJ == true){HpABiKZsOJ = false;}
      if(FDLerxtxZi == true){FDLerxtxZi = false;}
      if(IzUSWJBPsI == true){IzUSWJBPsI = false;}
      if(eoDzDHoqcA == true){eoDzDHoqcA = false;}
      if(HmKzJbUwyC == true){HmKzJbUwyC = false;}
      if(WyGzfHVgdY == true){WyGzfHVgdY = false;}
      if(IJzFdPALbk == true){IJzFdPALbk = false;}
      if(IDUYbUoUJu == true){IDUYbUoUJu = false;}
      if(oFRqlfiDSu == true){oFRqlfiDSu = false;}
      if(kHMErxmEVs == true){kHMErxmEVs = false;}
      if(aITNsSdgXK == true){aITNsSdgXK = false;}
      if(SAWijDrITx == true){SAWijDrITx = false;}
      if(gwsgzApQgd == true){gwsgzApQgd = false;}
      if(hjzPTgkExS == true){hjzPTgkExS = false;}
      if(CBfIckjcTn == true){CBfIckjcTn = false;}
      if(FdkXMeOmNr == true){FdkXMeOmNr = false;}
      if(cNAtchBHPC == true){cNAtchBHPC = false;}
      if(SnKAufQkDO == true){SnKAufQkDO = false;}
      if(QMwrYDybDo == true){QMwrYDybDo = false;}
      if(RxpFpnAket == true){RxpFpnAket = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBMBOHBWAW
{ 
  void oQMkIINtrB()
  { 
      bool HfOUtCjrkG = false;
      bool CZLjBCoRHb = false;
      bool kIuxNFSdpO = false;
      bool nPizmlQBGx = false;
      bool cbLXlwcqmT = false;
      bool iLxhizkQHo = false;
      bool jFCVSlqLxO = false;
      bool knLKyIwXLQ = false;
      bool baqWecSAQn = false;
      bool BAsQMXZoEz = false;
      bool FRtXhtzliZ = false;
      bool CMEpMINfqp = false;
      bool TpuJNkttya = false;
      bool iGSMLKgSnk = false;
      bool cgQpknuDEE = false;
      bool KtyOfOVjKx = false;
      bool zEnIqwtreB = false;
      bool btqFMmYEXY = false;
      bool oqpsQoHEfw = false;
      bool owIpkYrIzo = false;
      string NzXsoWTYsS;
      string cOBYVMBQzo;
      string uqJCZMQYzM;
      string VGPDacETIH;
      string tCzrKFKXez;
      string uwAzyVpUTb;
      string FuZfxVzyys;
      string HgIqurqQrT;
      string BsszRYGQFE;
      string liAfBycSun;
      string GLYlrNnIDF;
      string dZczZMBZOX;
      string PhstGXfbow;
      string PYUDMpTHHD;
      string kxMzZMFBFn;
      string xCEXYXSeeT;
      string hLTHoFFZlj;
      string stSLmRVsTt;
      string SeWBzNUwdn;
      string WnbnVYdFKU;
      if(NzXsoWTYsS == GLYlrNnIDF){HfOUtCjrkG = true;}
      else if(GLYlrNnIDF == NzXsoWTYsS){FRtXhtzliZ = true;}
      if(cOBYVMBQzo == dZczZMBZOX){CZLjBCoRHb = true;}
      else if(dZczZMBZOX == cOBYVMBQzo){CMEpMINfqp = true;}
      if(uqJCZMQYzM == PhstGXfbow){kIuxNFSdpO = true;}
      else if(PhstGXfbow == uqJCZMQYzM){TpuJNkttya = true;}
      if(VGPDacETIH == PYUDMpTHHD){nPizmlQBGx = true;}
      else if(PYUDMpTHHD == VGPDacETIH){iGSMLKgSnk = true;}
      if(tCzrKFKXez == kxMzZMFBFn){cbLXlwcqmT = true;}
      else if(kxMzZMFBFn == tCzrKFKXez){cgQpknuDEE = true;}
      if(uwAzyVpUTb == xCEXYXSeeT){iLxhizkQHo = true;}
      else if(xCEXYXSeeT == uwAzyVpUTb){KtyOfOVjKx = true;}
      if(FuZfxVzyys == hLTHoFFZlj){jFCVSlqLxO = true;}
      else if(hLTHoFFZlj == FuZfxVzyys){zEnIqwtreB = true;}
      if(HgIqurqQrT == stSLmRVsTt){knLKyIwXLQ = true;}
      if(BsszRYGQFE == SeWBzNUwdn){baqWecSAQn = true;}
      if(liAfBycSun == WnbnVYdFKU){BAsQMXZoEz = true;}
      while(stSLmRVsTt == HgIqurqQrT){btqFMmYEXY = true;}
      while(SeWBzNUwdn == SeWBzNUwdn){oqpsQoHEfw = true;}
      while(WnbnVYdFKU == WnbnVYdFKU){owIpkYrIzo = true;}
      if(HfOUtCjrkG == true){HfOUtCjrkG = false;}
      if(CZLjBCoRHb == true){CZLjBCoRHb = false;}
      if(kIuxNFSdpO == true){kIuxNFSdpO = false;}
      if(nPizmlQBGx == true){nPizmlQBGx = false;}
      if(cbLXlwcqmT == true){cbLXlwcqmT = false;}
      if(iLxhizkQHo == true){iLxhizkQHo = false;}
      if(jFCVSlqLxO == true){jFCVSlqLxO = false;}
      if(knLKyIwXLQ == true){knLKyIwXLQ = false;}
      if(baqWecSAQn == true){baqWecSAQn = false;}
      if(BAsQMXZoEz == true){BAsQMXZoEz = false;}
      if(FRtXhtzliZ == true){FRtXhtzliZ = false;}
      if(CMEpMINfqp == true){CMEpMINfqp = false;}
      if(TpuJNkttya == true){TpuJNkttya = false;}
      if(iGSMLKgSnk == true){iGSMLKgSnk = false;}
      if(cgQpknuDEE == true){cgQpknuDEE = false;}
      if(KtyOfOVjKx == true){KtyOfOVjKx = false;}
      if(zEnIqwtreB == true){zEnIqwtreB = false;}
      if(btqFMmYEXY == true){btqFMmYEXY = false;}
      if(oqpsQoHEfw == true){oqpsQoHEfw = false;}
      if(owIpkYrIzo == true){owIpkYrIzo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFFTFPYOWO
{ 
  void gSLDlwwiAB()
  { 
      bool GNFihMfuLH = false;
      bool pkRKnBYFZp = false;
      bool eUlmcOVxiA = false;
      bool fwXZbBUcmf = false;
      bool Lkqtozgycw = false;
      bool uhRUnkaSFT = false;
      bool qiMKasMrim = false;
      bool fwStetdqxd = false;
      bool hXTmFxeDkp = false;
      bool ZBWSocXfTw = false;
      bool lnOpPyPWpt = false;
      bool HjVblSOZFd = false;
      bool NJGsNeYzEB = false;
      bool VxXArsIdXG = false;
      bool gHNqiofufV = false;
      bool OyaoichVbj = false;
      bool ZPRnYJMUjs = false;
      bool KjCywFwPJY = false;
      bool ydTimWVhRO = false;
      bool KmBmgRoYSY = false;
      string tiqzDfFDhA;
      string YrgsoCQGXZ;
      string IggmhjLOja;
      string WicsQoVRhm;
      string PuomAsjOGy;
      string aTbNgNCEQS;
      string UpSGdpOmcA;
      string gzYjJNrsmn;
      string AwIkACGOLC;
      string mRAOSYbhJK;
      string dwlFRaurDT;
      string VIQbRXghFb;
      string izbZMPyJQj;
      string lJjcJEKCTZ;
      string GOKrfeAXwu;
      string qtbgadTLsC;
      string blaSgMXmSN;
      string MeOfVTnith;
      string OaMUsqgDBe;
      string jyJQxUnrKT;
      if(tiqzDfFDhA == dwlFRaurDT){GNFihMfuLH = true;}
      else if(dwlFRaurDT == tiqzDfFDhA){lnOpPyPWpt = true;}
      if(YrgsoCQGXZ == VIQbRXghFb){pkRKnBYFZp = true;}
      else if(VIQbRXghFb == YrgsoCQGXZ){HjVblSOZFd = true;}
      if(IggmhjLOja == izbZMPyJQj){eUlmcOVxiA = true;}
      else if(izbZMPyJQj == IggmhjLOja){NJGsNeYzEB = true;}
      if(WicsQoVRhm == lJjcJEKCTZ){fwXZbBUcmf = true;}
      else if(lJjcJEKCTZ == WicsQoVRhm){VxXArsIdXG = true;}
      if(PuomAsjOGy == GOKrfeAXwu){Lkqtozgycw = true;}
      else if(GOKrfeAXwu == PuomAsjOGy){gHNqiofufV = true;}
      if(aTbNgNCEQS == qtbgadTLsC){uhRUnkaSFT = true;}
      else if(qtbgadTLsC == aTbNgNCEQS){OyaoichVbj = true;}
      if(UpSGdpOmcA == blaSgMXmSN){qiMKasMrim = true;}
      else if(blaSgMXmSN == UpSGdpOmcA){ZPRnYJMUjs = true;}
      if(gzYjJNrsmn == MeOfVTnith){fwStetdqxd = true;}
      if(AwIkACGOLC == OaMUsqgDBe){hXTmFxeDkp = true;}
      if(mRAOSYbhJK == jyJQxUnrKT){ZBWSocXfTw = true;}
      while(MeOfVTnith == gzYjJNrsmn){KjCywFwPJY = true;}
      while(OaMUsqgDBe == OaMUsqgDBe){ydTimWVhRO = true;}
      while(jyJQxUnrKT == jyJQxUnrKT){KmBmgRoYSY = true;}
      if(GNFihMfuLH == true){GNFihMfuLH = false;}
      if(pkRKnBYFZp == true){pkRKnBYFZp = false;}
      if(eUlmcOVxiA == true){eUlmcOVxiA = false;}
      if(fwXZbBUcmf == true){fwXZbBUcmf = false;}
      if(Lkqtozgycw == true){Lkqtozgycw = false;}
      if(uhRUnkaSFT == true){uhRUnkaSFT = false;}
      if(qiMKasMrim == true){qiMKasMrim = false;}
      if(fwStetdqxd == true){fwStetdqxd = false;}
      if(hXTmFxeDkp == true){hXTmFxeDkp = false;}
      if(ZBWSocXfTw == true){ZBWSocXfTw = false;}
      if(lnOpPyPWpt == true){lnOpPyPWpt = false;}
      if(HjVblSOZFd == true){HjVblSOZFd = false;}
      if(NJGsNeYzEB == true){NJGsNeYzEB = false;}
      if(VxXArsIdXG == true){VxXArsIdXG = false;}
      if(gHNqiofufV == true){gHNqiofufV = false;}
      if(OyaoichVbj == true){OyaoichVbj = false;}
      if(ZPRnYJMUjs == true){ZPRnYJMUjs = false;}
      if(KjCywFwPJY == true){KjCywFwPJY = false;}
      if(ydTimWVhRO == true){ydTimWVhRO = false;}
      if(KmBmgRoYSY == true){KmBmgRoYSY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNYETMHJBV
{ 
  void naDjwUoaUA()
  { 
      bool JVERoskCit = false;
      bool DpWnnjHuqU = false;
      bool xhwVClSWiQ = false;
      bool FVxIFZpMlR = false;
      bool mJwLcrKKNu = false;
      bool RqtzbbZhPD = false;
      bool aOTSnhsNiN = false;
      bool stIZgnljsJ = false;
      bool aHJmzNbxfc = false;
      bool AHxiqYocWu = false;
      bool zxazBWhUSm = false;
      bool pooFbSFfTZ = false;
      bool FugFMlwZiI = false;
      bool yIMxKdgJkb = false;
      bool fHesmKRqGX = false;
      bool TJJxoDPVlP = false;
      bool ZIkJogcquy = false;
      bool lutqtyPnRB = false;
      bool TFTKooyPIG = false;
      bool NKXVBXVUDF = false;
      string xkEVEkedKm;
      string iCBWXXLyet;
      string ZmkfWwURcm;
      string ITpbhrnDme;
      string sUPEBUPLWm;
      string rdEbhKzXyI;
      string PNAWeOLZof;
      string jILzBEWfdC;
      string fJtpudOOsW;
      string rQEdPeUsZm;
      string IoWqDiSFZd;
      string mTswbGTKaA;
      string AxgRmSDgjW;
      string idFqsqmClL;
      string KIoOiXWICI;
      string KKRZlLIEDj;
      string flVDtJNBDk;
      string TRYOprHRhP;
      string wueaLYLfFg;
      string ihyBfYllUZ;
      if(xkEVEkedKm == IoWqDiSFZd){JVERoskCit = true;}
      else if(IoWqDiSFZd == xkEVEkedKm){zxazBWhUSm = true;}
      if(iCBWXXLyet == mTswbGTKaA){DpWnnjHuqU = true;}
      else if(mTswbGTKaA == iCBWXXLyet){pooFbSFfTZ = true;}
      if(ZmkfWwURcm == AxgRmSDgjW){xhwVClSWiQ = true;}
      else if(AxgRmSDgjW == ZmkfWwURcm){FugFMlwZiI = true;}
      if(ITpbhrnDme == idFqsqmClL){FVxIFZpMlR = true;}
      else if(idFqsqmClL == ITpbhrnDme){yIMxKdgJkb = true;}
      if(sUPEBUPLWm == KIoOiXWICI){mJwLcrKKNu = true;}
      else if(KIoOiXWICI == sUPEBUPLWm){fHesmKRqGX = true;}
      if(rdEbhKzXyI == KKRZlLIEDj){RqtzbbZhPD = true;}
      else if(KKRZlLIEDj == rdEbhKzXyI){TJJxoDPVlP = true;}
      if(PNAWeOLZof == flVDtJNBDk){aOTSnhsNiN = true;}
      else if(flVDtJNBDk == PNAWeOLZof){ZIkJogcquy = true;}
      if(jILzBEWfdC == TRYOprHRhP){stIZgnljsJ = true;}
      if(fJtpudOOsW == wueaLYLfFg){aHJmzNbxfc = true;}
      if(rQEdPeUsZm == ihyBfYllUZ){AHxiqYocWu = true;}
      while(TRYOprHRhP == jILzBEWfdC){lutqtyPnRB = true;}
      while(wueaLYLfFg == wueaLYLfFg){TFTKooyPIG = true;}
      while(ihyBfYllUZ == ihyBfYllUZ){NKXVBXVUDF = true;}
      if(JVERoskCit == true){JVERoskCit = false;}
      if(DpWnnjHuqU == true){DpWnnjHuqU = false;}
      if(xhwVClSWiQ == true){xhwVClSWiQ = false;}
      if(FVxIFZpMlR == true){FVxIFZpMlR = false;}
      if(mJwLcrKKNu == true){mJwLcrKKNu = false;}
      if(RqtzbbZhPD == true){RqtzbbZhPD = false;}
      if(aOTSnhsNiN == true){aOTSnhsNiN = false;}
      if(stIZgnljsJ == true){stIZgnljsJ = false;}
      if(aHJmzNbxfc == true){aHJmzNbxfc = false;}
      if(AHxiqYocWu == true){AHxiqYocWu = false;}
      if(zxazBWhUSm == true){zxazBWhUSm = false;}
      if(pooFbSFfTZ == true){pooFbSFfTZ = false;}
      if(FugFMlwZiI == true){FugFMlwZiI = false;}
      if(yIMxKdgJkb == true){yIMxKdgJkb = false;}
      if(fHesmKRqGX == true){fHesmKRqGX = false;}
      if(TJJxoDPVlP == true){TJJxoDPVlP = false;}
      if(ZIkJogcquy == true){ZIkJogcquy = false;}
      if(lutqtyPnRB == true){lutqtyPnRB = false;}
      if(TFTKooyPIG == true){TFTKooyPIG = false;}
      if(NKXVBXVUDF == true){NKXVBXVUDF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCKUTZZOWV
{ 
  void xJpTCnkRzc()
  { 
      bool VPVqugaiuY = false;
      bool VEPkHNzwUS = false;
      bool dARbLFDEib = false;
      bool ZWXnWnpFFA = false;
      bool tAsuunXlcs = false;
      bool ITYxTUytfo = false;
      bool dWATyyfbNS = false;
      bool WtpUXcGWfW = false;
      bool hQboSGyZTC = false;
      bool pwYPWWAZxw = false;
      bool HuYJWOcDYq = false;
      bool NaNIHNuKAq = false;
      bool AFHLcaUZxA = false;
      bool bgZjOmqRSE = false;
      bool dtBcnOhPIJ = false;
      bool bpZFwBnNgu = false;
      bool sCGXOgBdtU = false;
      bool VcquNFEeXN = false;
      bool sFRnYlHTmM = false;
      bool ycjWKancNG = false;
      string leFOxwJEdo;
      string RLOwrXDdLX;
      string hIigLiXuHX;
      string JIHpNRuOzw;
      string ywCxdFKhKt;
      string oRERLduXCN;
      string XNxFeJEYha;
      string cndOZkGlDF;
      string XokMhqEoej;
      string VWLkXjzwRT;
      string BlAiRBnorZ;
      string XJUxpibjWm;
      string FOsyFGbrqo;
      string kJTiEloBug;
      string DOxELLBOuo;
      string HPYeOmsBdL;
      string ZuyDnNolsE;
      string sanpipRnls;
      string EMwBhVjoTQ;
      string rmXjGHPtQy;
      if(leFOxwJEdo == BlAiRBnorZ){VPVqugaiuY = true;}
      else if(BlAiRBnorZ == leFOxwJEdo){HuYJWOcDYq = true;}
      if(RLOwrXDdLX == XJUxpibjWm){VEPkHNzwUS = true;}
      else if(XJUxpibjWm == RLOwrXDdLX){NaNIHNuKAq = true;}
      if(hIigLiXuHX == FOsyFGbrqo){dARbLFDEib = true;}
      else if(FOsyFGbrqo == hIigLiXuHX){AFHLcaUZxA = true;}
      if(JIHpNRuOzw == kJTiEloBug){ZWXnWnpFFA = true;}
      else if(kJTiEloBug == JIHpNRuOzw){bgZjOmqRSE = true;}
      if(ywCxdFKhKt == DOxELLBOuo){tAsuunXlcs = true;}
      else if(DOxELLBOuo == ywCxdFKhKt){dtBcnOhPIJ = true;}
      if(oRERLduXCN == HPYeOmsBdL){ITYxTUytfo = true;}
      else if(HPYeOmsBdL == oRERLduXCN){bpZFwBnNgu = true;}
      if(XNxFeJEYha == ZuyDnNolsE){dWATyyfbNS = true;}
      else if(ZuyDnNolsE == XNxFeJEYha){sCGXOgBdtU = true;}
      if(cndOZkGlDF == sanpipRnls){WtpUXcGWfW = true;}
      if(XokMhqEoej == EMwBhVjoTQ){hQboSGyZTC = true;}
      if(VWLkXjzwRT == rmXjGHPtQy){pwYPWWAZxw = true;}
      while(sanpipRnls == cndOZkGlDF){VcquNFEeXN = true;}
      while(EMwBhVjoTQ == EMwBhVjoTQ){sFRnYlHTmM = true;}
      while(rmXjGHPtQy == rmXjGHPtQy){ycjWKancNG = true;}
      if(VPVqugaiuY == true){VPVqugaiuY = false;}
      if(VEPkHNzwUS == true){VEPkHNzwUS = false;}
      if(dARbLFDEib == true){dARbLFDEib = false;}
      if(ZWXnWnpFFA == true){ZWXnWnpFFA = false;}
      if(tAsuunXlcs == true){tAsuunXlcs = false;}
      if(ITYxTUytfo == true){ITYxTUytfo = false;}
      if(dWATyyfbNS == true){dWATyyfbNS = false;}
      if(WtpUXcGWfW == true){WtpUXcGWfW = false;}
      if(hQboSGyZTC == true){hQboSGyZTC = false;}
      if(pwYPWWAZxw == true){pwYPWWAZxw = false;}
      if(HuYJWOcDYq == true){HuYJWOcDYq = false;}
      if(NaNIHNuKAq == true){NaNIHNuKAq = false;}
      if(AFHLcaUZxA == true){AFHLcaUZxA = false;}
      if(bgZjOmqRSE == true){bgZjOmqRSE = false;}
      if(dtBcnOhPIJ == true){dtBcnOhPIJ = false;}
      if(bpZFwBnNgu == true){bpZFwBnNgu = false;}
      if(sCGXOgBdtU == true){sCGXOgBdtU = false;}
      if(VcquNFEeXN == true){VcquNFEeXN = false;}
      if(sFRnYlHTmM == true){sFRnYlHTmM = false;}
      if(ycjWKancNG == true){ycjWKancNG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RXTICJALUT
{ 
  void YMOCNpkkpa()
  { 
      bool KISlXWjPJJ = false;
      bool JpjOiMbSIp = false;
      bool FEhDggwMnz = false;
      bool drxSaWOxWL = false;
      bool zoEKNJycDf = false;
      bool ipZwBGaOEp = false;
      bool ZWaJeRsRnM = false;
      bool xewxqPzXoX = false;
      bool hTIHQmSART = false;
      bool uArfkbNuew = false;
      bool PgnqhDtcFk = false;
      bool GDYfIFNSsq = false;
      bool zszTQxlQLO = false;
      bool CErsHBfRYM = false;
      bool spufNraLXf = false;
      bool OtCmxWgUaj = false;
      bool QdQqiCKeYG = false;
      bool ZwsfyJyTFX = false;
      bool WZrfAHCFwj = false;
      bool UKqowOYDxL = false;
      string mrEXYBIoNu;
      string PtxRQpQMRO;
      string wLFLsSEUfk;
      string cmhyCTWKhq;
      string dssTlyVNMY;
      string crUVubmreF;
      string xmIcRcMzPw;
      string TGeajDRkZt;
      string xpHGIjRLDZ;
      string gdebspkQBI;
      string lVyQFVNtkq;
      string KCSkIGeBTg;
      string LAuoPpbCgs;
      string SAiQIaqqBm;
      string WWZLPdKtTl;
      string KiwUxkaJAO;
      string tLNqYJSBbh;
      string OnzgKnajYk;
      string egitiiEOTX;
      string AhqmsLJhlG;
      if(mrEXYBIoNu == lVyQFVNtkq){KISlXWjPJJ = true;}
      else if(lVyQFVNtkq == mrEXYBIoNu){PgnqhDtcFk = true;}
      if(PtxRQpQMRO == KCSkIGeBTg){JpjOiMbSIp = true;}
      else if(KCSkIGeBTg == PtxRQpQMRO){GDYfIFNSsq = true;}
      if(wLFLsSEUfk == LAuoPpbCgs){FEhDggwMnz = true;}
      else if(LAuoPpbCgs == wLFLsSEUfk){zszTQxlQLO = true;}
      if(cmhyCTWKhq == SAiQIaqqBm){drxSaWOxWL = true;}
      else if(SAiQIaqqBm == cmhyCTWKhq){CErsHBfRYM = true;}
      if(dssTlyVNMY == WWZLPdKtTl){zoEKNJycDf = true;}
      else if(WWZLPdKtTl == dssTlyVNMY){spufNraLXf = true;}
      if(crUVubmreF == KiwUxkaJAO){ipZwBGaOEp = true;}
      else if(KiwUxkaJAO == crUVubmreF){OtCmxWgUaj = true;}
      if(xmIcRcMzPw == tLNqYJSBbh){ZWaJeRsRnM = true;}
      else if(tLNqYJSBbh == xmIcRcMzPw){QdQqiCKeYG = true;}
      if(TGeajDRkZt == OnzgKnajYk){xewxqPzXoX = true;}
      if(xpHGIjRLDZ == egitiiEOTX){hTIHQmSART = true;}
      if(gdebspkQBI == AhqmsLJhlG){uArfkbNuew = true;}
      while(OnzgKnajYk == TGeajDRkZt){ZwsfyJyTFX = true;}
      while(egitiiEOTX == egitiiEOTX){WZrfAHCFwj = true;}
      while(AhqmsLJhlG == AhqmsLJhlG){UKqowOYDxL = true;}
      if(KISlXWjPJJ == true){KISlXWjPJJ = false;}
      if(JpjOiMbSIp == true){JpjOiMbSIp = false;}
      if(FEhDggwMnz == true){FEhDggwMnz = false;}
      if(drxSaWOxWL == true){drxSaWOxWL = false;}
      if(zoEKNJycDf == true){zoEKNJycDf = false;}
      if(ipZwBGaOEp == true){ipZwBGaOEp = false;}
      if(ZWaJeRsRnM == true){ZWaJeRsRnM = false;}
      if(xewxqPzXoX == true){xewxqPzXoX = false;}
      if(hTIHQmSART == true){hTIHQmSART = false;}
      if(uArfkbNuew == true){uArfkbNuew = false;}
      if(PgnqhDtcFk == true){PgnqhDtcFk = false;}
      if(GDYfIFNSsq == true){GDYfIFNSsq = false;}
      if(zszTQxlQLO == true){zszTQxlQLO = false;}
      if(CErsHBfRYM == true){CErsHBfRYM = false;}
      if(spufNraLXf == true){spufNraLXf = false;}
      if(OtCmxWgUaj == true){OtCmxWgUaj = false;}
      if(QdQqiCKeYG == true){QdQqiCKeYG = false;}
      if(ZwsfyJyTFX == true){ZwsfyJyTFX = false;}
      if(WZrfAHCFwj == true){WZrfAHCFwj = false;}
      if(UKqowOYDxL == true){UKqowOYDxL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJAXEKESJL
{ 
  void ZsCzLZhlgP()
  { 
      bool rJnPRjZKkr = false;
      bool DRwLzPwOzP = false;
      bool WzhBCbGHyQ = false;
      bool YtxhhVNOlY = false;
      bool MabFMAQtxh = false;
      bool cIrPGsalMp = false;
      bool dRLTSJUNdc = false;
      bool BgcZDwXboC = false;
      bool KMKQmPBgbn = false;
      bool ubBuutOHmD = false;
      bool fCPUgufRLK = false;
      bool VzxKeQHugC = false;
      bool HmlphZfgeI = false;
      bool gQnkVIwojq = false;
      bool jiUQSudpQd = false;
      bool mTZkurPZlG = false;
      bool PymDcFKLoV = false;
      bool URLoRXSVWm = false;
      bool upQAVMpDpc = false;
      bool sWDcbkwRmN = false;
      string lEjNsCSWEC;
      string jfNakUXLgU;
      string GdBBHoPFJC;
      string UagAsEqkZE;
      string NbTylZTmwe;
      string MdGTyIChFE;
      string mMNBgIyNgg;
      string dmlbGeJDPg;
      string UbIdoqUMBj;
      string CIeVRBNSQc;
      string aGGPBZqdNS;
      string zySYiKEiLp;
      string nkLxdVIQKF;
      string QqmmGNVrcP;
      string AqzhkDoGlG;
      string weGaoouIlf;
      string RaSHCHLfRV;
      string oMFwpxlcLZ;
      string fCeDIlkMxQ;
      string SMFxxYXqfd;
      if(lEjNsCSWEC == aGGPBZqdNS){rJnPRjZKkr = true;}
      else if(aGGPBZqdNS == lEjNsCSWEC){fCPUgufRLK = true;}
      if(jfNakUXLgU == zySYiKEiLp){DRwLzPwOzP = true;}
      else if(zySYiKEiLp == jfNakUXLgU){VzxKeQHugC = true;}
      if(GdBBHoPFJC == nkLxdVIQKF){WzhBCbGHyQ = true;}
      else if(nkLxdVIQKF == GdBBHoPFJC){HmlphZfgeI = true;}
      if(UagAsEqkZE == QqmmGNVrcP){YtxhhVNOlY = true;}
      else if(QqmmGNVrcP == UagAsEqkZE){gQnkVIwojq = true;}
      if(NbTylZTmwe == AqzhkDoGlG){MabFMAQtxh = true;}
      else if(AqzhkDoGlG == NbTylZTmwe){jiUQSudpQd = true;}
      if(MdGTyIChFE == weGaoouIlf){cIrPGsalMp = true;}
      else if(weGaoouIlf == MdGTyIChFE){mTZkurPZlG = true;}
      if(mMNBgIyNgg == RaSHCHLfRV){dRLTSJUNdc = true;}
      else if(RaSHCHLfRV == mMNBgIyNgg){PymDcFKLoV = true;}
      if(dmlbGeJDPg == oMFwpxlcLZ){BgcZDwXboC = true;}
      if(UbIdoqUMBj == fCeDIlkMxQ){KMKQmPBgbn = true;}
      if(CIeVRBNSQc == SMFxxYXqfd){ubBuutOHmD = true;}
      while(oMFwpxlcLZ == dmlbGeJDPg){URLoRXSVWm = true;}
      while(fCeDIlkMxQ == fCeDIlkMxQ){upQAVMpDpc = true;}
      while(SMFxxYXqfd == SMFxxYXqfd){sWDcbkwRmN = true;}
      if(rJnPRjZKkr == true){rJnPRjZKkr = false;}
      if(DRwLzPwOzP == true){DRwLzPwOzP = false;}
      if(WzhBCbGHyQ == true){WzhBCbGHyQ = false;}
      if(YtxhhVNOlY == true){YtxhhVNOlY = false;}
      if(MabFMAQtxh == true){MabFMAQtxh = false;}
      if(cIrPGsalMp == true){cIrPGsalMp = false;}
      if(dRLTSJUNdc == true){dRLTSJUNdc = false;}
      if(BgcZDwXboC == true){BgcZDwXboC = false;}
      if(KMKQmPBgbn == true){KMKQmPBgbn = false;}
      if(ubBuutOHmD == true){ubBuutOHmD = false;}
      if(fCPUgufRLK == true){fCPUgufRLK = false;}
      if(VzxKeQHugC == true){VzxKeQHugC = false;}
      if(HmlphZfgeI == true){HmlphZfgeI = false;}
      if(gQnkVIwojq == true){gQnkVIwojq = false;}
      if(jiUQSudpQd == true){jiUQSudpQd = false;}
      if(mTZkurPZlG == true){mTZkurPZlG = false;}
      if(PymDcFKLoV == true){PymDcFKLoV = false;}
      if(URLoRXSVWm == true){URLoRXSVWm = false;}
      if(upQAVMpDpc == true){upQAVMpDpc = false;}
      if(sWDcbkwRmN == true){sWDcbkwRmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FUASMAGNMT
{ 
  void gVFMkShuSn()
  { 
      bool PalhRxITdL = false;
      bool ddTJmAnEqL = false;
      bool pUTCfKyLhw = false;
      bool nKBlcEmVuq = false;
      bool LaXNSJazVQ = false;
      bool oLOljuGiBG = false;
      bool yxlgXScgfi = false;
      bool NRIzAPwFjV = false;
      bool jyoQGcwOCh = false;
      bool xDUosNoqpz = false;
      bool gtSmCXCOkT = false;
      bool yBzeWzHUZu = false;
      bool WOdykKxTGl = false;
      bool ZFPjoofCOi = false;
      bool ZgchiwDoSs = false;
      bool GTQtcSQUBq = false;
      bool aiIztskPog = false;
      bool TFGqUokuOo = false;
      bool GHAMfGnVHW = false;
      bool XLAWIqXdno = false;
      string VDqbjqoQOa;
      string wOEZsntwIE;
      string uxUOwWbZWx;
      string LaBPlxgHBT;
      string mVZOWJxtea;
      string WrqqFYhbeM;
      string OOtQOVMomu;
      string GmtoRZXFqm;
      string ZhuwaSjKKN;
      string OFcoEXaIzB;
      string wIGiTjxCYe;
      string AcjqlgTxpw;
      string kBdZfBKFjs;
      string yOFpqRaLbq;
      string VhkeMlUkCW;
      string EdSDPtdfDS;
      string ZqRfglWtzU;
      string FHUzZDQzMs;
      string fYDMoUuBZx;
      string ntIJRdPFyZ;
      if(VDqbjqoQOa == wIGiTjxCYe){PalhRxITdL = true;}
      else if(wIGiTjxCYe == VDqbjqoQOa){gtSmCXCOkT = true;}
      if(wOEZsntwIE == AcjqlgTxpw){ddTJmAnEqL = true;}
      else if(AcjqlgTxpw == wOEZsntwIE){yBzeWzHUZu = true;}
      if(uxUOwWbZWx == kBdZfBKFjs){pUTCfKyLhw = true;}
      else if(kBdZfBKFjs == uxUOwWbZWx){WOdykKxTGl = true;}
      if(LaBPlxgHBT == yOFpqRaLbq){nKBlcEmVuq = true;}
      else if(yOFpqRaLbq == LaBPlxgHBT){ZFPjoofCOi = true;}
      if(mVZOWJxtea == VhkeMlUkCW){LaXNSJazVQ = true;}
      else if(VhkeMlUkCW == mVZOWJxtea){ZgchiwDoSs = true;}
      if(WrqqFYhbeM == EdSDPtdfDS){oLOljuGiBG = true;}
      else if(EdSDPtdfDS == WrqqFYhbeM){GTQtcSQUBq = true;}
      if(OOtQOVMomu == ZqRfglWtzU){yxlgXScgfi = true;}
      else if(ZqRfglWtzU == OOtQOVMomu){aiIztskPog = true;}
      if(GmtoRZXFqm == FHUzZDQzMs){NRIzAPwFjV = true;}
      if(ZhuwaSjKKN == fYDMoUuBZx){jyoQGcwOCh = true;}
      if(OFcoEXaIzB == ntIJRdPFyZ){xDUosNoqpz = true;}
      while(FHUzZDQzMs == GmtoRZXFqm){TFGqUokuOo = true;}
      while(fYDMoUuBZx == fYDMoUuBZx){GHAMfGnVHW = true;}
      while(ntIJRdPFyZ == ntIJRdPFyZ){XLAWIqXdno = true;}
      if(PalhRxITdL == true){PalhRxITdL = false;}
      if(ddTJmAnEqL == true){ddTJmAnEqL = false;}
      if(pUTCfKyLhw == true){pUTCfKyLhw = false;}
      if(nKBlcEmVuq == true){nKBlcEmVuq = false;}
      if(LaXNSJazVQ == true){LaXNSJazVQ = false;}
      if(oLOljuGiBG == true){oLOljuGiBG = false;}
      if(yxlgXScgfi == true){yxlgXScgfi = false;}
      if(NRIzAPwFjV == true){NRIzAPwFjV = false;}
      if(jyoQGcwOCh == true){jyoQGcwOCh = false;}
      if(xDUosNoqpz == true){xDUosNoqpz = false;}
      if(gtSmCXCOkT == true){gtSmCXCOkT = false;}
      if(yBzeWzHUZu == true){yBzeWzHUZu = false;}
      if(WOdykKxTGl == true){WOdykKxTGl = false;}
      if(ZFPjoofCOi == true){ZFPjoofCOi = false;}
      if(ZgchiwDoSs == true){ZgchiwDoSs = false;}
      if(GTQtcSQUBq == true){GTQtcSQUBq = false;}
      if(aiIztskPog == true){aiIztskPog = false;}
      if(TFGqUokuOo == true){TFGqUokuOo = false;}
      if(GHAMfGnVHW == true){GHAMfGnVHW = false;}
      if(XLAWIqXdno == true){XLAWIqXdno = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMTMXHYBQP
{ 
  void HoguUABdDl()
  { 
      bool wDQRawqyJr = false;
      bool SfRsWPlCww = false;
      bool yFSAheBVln = false;
      bool shLTyHKSnp = false;
      bool zRWLGXEBzZ = false;
      bool jhGIPpjPju = false;
      bool uVLVyjUyuO = false;
      bool FTNFwgiHsJ = false;
      bool azVLDLaCEH = false;
      bool WthrudFANW = false;
      bool CGGjTPTBMi = false;
      bool HcVaUwzzRl = false;
      bool ISsmqLkVKS = false;
      bool ahtWGUrkqm = false;
      bool qZpVAtXHXy = false;
      bool dFhaNjMTrI = false;
      bool eypsHYizTz = false;
      bool EOHdticXlx = false;
      bool ndxMoVASJV = false;
      bool IXriIsjwOb = false;
      string fcpVabBhJP;
      string BEoqiFPYwR;
      string OFNSMdYSIK;
      string CLaZEjuDpD;
      string JHglqFUtQf;
      string UuBXUaOXJx;
      string CiZyMocOly;
      string KLirHHXaaG;
      string IeCbpHKDFd;
      string VXtsAagiZB;
      string cGIRVIMIQM;
      string CmwDnXgxIF;
      string eYIIcmRoqg;
      string ZoBZcCVjFg;
      string tBmrahaqEc;
      string siZUVExzni;
      string qXQimNlWZl;
      string BwrbKdlQgt;
      string LakOmpPfDY;
      string EWuWpWjDFN;
      if(fcpVabBhJP == cGIRVIMIQM){wDQRawqyJr = true;}
      else if(cGIRVIMIQM == fcpVabBhJP){CGGjTPTBMi = true;}
      if(BEoqiFPYwR == CmwDnXgxIF){SfRsWPlCww = true;}
      else if(CmwDnXgxIF == BEoqiFPYwR){HcVaUwzzRl = true;}
      if(OFNSMdYSIK == eYIIcmRoqg){yFSAheBVln = true;}
      else if(eYIIcmRoqg == OFNSMdYSIK){ISsmqLkVKS = true;}
      if(CLaZEjuDpD == ZoBZcCVjFg){shLTyHKSnp = true;}
      else if(ZoBZcCVjFg == CLaZEjuDpD){ahtWGUrkqm = true;}
      if(JHglqFUtQf == tBmrahaqEc){zRWLGXEBzZ = true;}
      else if(tBmrahaqEc == JHglqFUtQf){qZpVAtXHXy = true;}
      if(UuBXUaOXJx == siZUVExzni){jhGIPpjPju = true;}
      else if(siZUVExzni == UuBXUaOXJx){dFhaNjMTrI = true;}
      if(CiZyMocOly == qXQimNlWZl){uVLVyjUyuO = true;}
      else if(qXQimNlWZl == CiZyMocOly){eypsHYizTz = true;}
      if(KLirHHXaaG == BwrbKdlQgt){FTNFwgiHsJ = true;}
      if(IeCbpHKDFd == LakOmpPfDY){azVLDLaCEH = true;}
      if(VXtsAagiZB == EWuWpWjDFN){WthrudFANW = true;}
      while(BwrbKdlQgt == KLirHHXaaG){EOHdticXlx = true;}
      while(LakOmpPfDY == LakOmpPfDY){ndxMoVASJV = true;}
      while(EWuWpWjDFN == EWuWpWjDFN){IXriIsjwOb = true;}
      if(wDQRawqyJr == true){wDQRawqyJr = false;}
      if(SfRsWPlCww == true){SfRsWPlCww = false;}
      if(yFSAheBVln == true){yFSAheBVln = false;}
      if(shLTyHKSnp == true){shLTyHKSnp = false;}
      if(zRWLGXEBzZ == true){zRWLGXEBzZ = false;}
      if(jhGIPpjPju == true){jhGIPpjPju = false;}
      if(uVLVyjUyuO == true){uVLVyjUyuO = false;}
      if(FTNFwgiHsJ == true){FTNFwgiHsJ = false;}
      if(azVLDLaCEH == true){azVLDLaCEH = false;}
      if(WthrudFANW == true){WthrudFANW = false;}
      if(CGGjTPTBMi == true){CGGjTPTBMi = false;}
      if(HcVaUwzzRl == true){HcVaUwzzRl = false;}
      if(ISsmqLkVKS == true){ISsmqLkVKS = false;}
      if(ahtWGUrkqm == true){ahtWGUrkqm = false;}
      if(qZpVAtXHXy == true){qZpVAtXHXy = false;}
      if(dFhaNjMTrI == true){dFhaNjMTrI = false;}
      if(eypsHYizTz == true){eypsHYizTz = false;}
      if(EOHdticXlx == true){EOHdticXlx = false;}
      if(ndxMoVASJV == true){ndxMoVASJV = false;}
      if(IXriIsjwOb == true){IXriIsjwOb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WTAVJQQRIU
{ 
  void ORTXolwlRh()
  { 
      bool WeazYOqSuo = false;
      bool fkNemUIGlM = false;
      bool IutTmVWQkz = false;
      bool wzHMDbDPkF = false;
      bool goaCVelZUJ = false;
      bool MdqUSajHMD = false;
      bool ragusfdAbL = false;
      bool RsUgfSTryH = false;
      bool iwubmSHlsb = false;
      bool qwChMFIfIo = false;
      bool BlyJrTIKoA = false;
      bool GqIETweFIa = false;
      bool XqGzTUpmTZ = false;
      bool KmjIGxxkiS = false;
      bool JxwsUAmyNQ = false;
      bool aCXhQJeypW = false;
      bool cVpPoSHAyW = false;
      bool ysVoQauNeS = false;
      bool gqYDyHPBqw = false;
      bool SzuLonGfDB = false;
      string dewCcXUZuz;
      string ihALdWLnNk;
      string YBDefHIEbr;
      string xaNAcUhCUk;
      string tpfiMshTbH;
      string kKAJIbaQVU;
      string OPxCCITzhI;
      string oIScpiUURl;
      string ZocUHlZErA;
      string tQgzVdsdgE;
      string ZhkSSbrXSZ;
      string HFziuZmbuP;
      string hPHhNXbTGL;
      string oqmNMqDKCe;
      string tBkRrnQxDu;
      string qQiQVKaDEt;
      string AXRGjQRlVE;
      string WbZPVgdooZ;
      string GePKUXHWqC;
      string QAFIeVjdhb;
      if(dewCcXUZuz == ZhkSSbrXSZ){WeazYOqSuo = true;}
      else if(ZhkSSbrXSZ == dewCcXUZuz){BlyJrTIKoA = true;}
      if(ihALdWLnNk == HFziuZmbuP){fkNemUIGlM = true;}
      else if(HFziuZmbuP == ihALdWLnNk){GqIETweFIa = true;}
      if(YBDefHIEbr == hPHhNXbTGL){IutTmVWQkz = true;}
      else if(hPHhNXbTGL == YBDefHIEbr){XqGzTUpmTZ = true;}
      if(xaNAcUhCUk == oqmNMqDKCe){wzHMDbDPkF = true;}
      else if(oqmNMqDKCe == xaNAcUhCUk){KmjIGxxkiS = true;}
      if(tpfiMshTbH == tBkRrnQxDu){goaCVelZUJ = true;}
      else if(tBkRrnQxDu == tpfiMshTbH){JxwsUAmyNQ = true;}
      if(kKAJIbaQVU == qQiQVKaDEt){MdqUSajHMD = true;}
      else if(qQiQVKaDEt == kKAJIbaQVU){aCXhQJeypW = true;}
      if(OPxCCITzhI == AXRGjQRlVE){ragusfdAbL = true;}
      else if(AXRGjQRlVE == OPxCCITzhI){cVpPoSHAyW = true;}
      if(oIScpiUURl == WbZPVgdooZ){RsUgfSTryH = true;}
      if(ZocUHlZErA == GePKUXHWqC){iwubmSHlsb = true;}
      if(tQgzVdsdgE == QAFIeVjdhb){qwChMFIfIo = true;}
      while(WbZPVgdooZ == oIScpiUURl){ysVoQauNeS = true;}
      while(GePKUXHWqC == GePKUXHWqC){gqYDyHPBqw = true;}
      while(QAFIeVjdhb == QAFIeVjdhb){SzuLonGfDB = true;}
      if(WeazYOqSuo == true){WeazYOqSuo = false;}
      if(fkNemUIGlM == true){fkNemUIGlM = false;}
      if(IutTmVWQkz == true){IutTmVWQkz = false;}
      if(wzHMDbDPkF == true){wzHMDbDPkF = false;}
      if(goaCVelZUJ == true){goaCVelZUJ = false;}
      if(MdqUSajHMD == true){MdqUSajHMD = false;}
      if(ragusfdAbL == true){ragusfdAbL = false;}
      if(RsUgfSTryH == true){RsUgfSTryH = false;}
      if(iwubmSHlsb == true){iwubmSHlsb = false;}
      if(qwChMFIfIo == true){qwChMFIfIo = false;}
      if(BlyJrTIKoA == true){BlyJrTIKoA = false;}
      if(GqIETweFIa == true){GqIETweFIa = false;}
      if(XqGzTUpmTZ == true){XqGzTUpmTZ = false;}
      if(KmjIGxxkiS == true){KmjIGxxkiS = false;}
      if(JxwsUAmyNQ == true){JxwsUAmyNQ = false;}
      if(aCXhQJeypW == true){aCXhQJeypW = false;}
      if(cVpPoSHAyW == true){cVpPoSHAyW = false;}
      if(ysVoQauNeS == true){ysVoQauNeS = false;}
      if(gqYDyHPBqw == true){gqYDyHPBqw = false;}
      if(SzuLonGfDB == true){SzuLonGfDB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOWFGULROH
{ 
  void mHHjBBFkym()
  { 
      bool LRKIgcRzXO = false;
      bool RSZXMmFXEI = false;
      bool jgmIFTdgMS = false;
      bool oRKKBIRrZI = false;
      bool CoXzBPzaAP = false;
      bool kEwXGddCDN = false;
      bool zkmEYAHOWD = false;
      bool VMxwGtJmGo = false;
      bool UCfwhkVmEW = false;
      bool dPoMIQCSaB = false;
      bool IjEwtXGzRL = false;
      bool UquOrwFpWn = false;
      bool dUKzZGXjmo = false;
      bool rqMFgjyiBJ = false;
      bool eVVrCmTZTL = false;
      bool LLumWmZEWn = false;
      bool zVMbTddpgI = false;
      bool yVnMIIzRxm = false;
      bool lxQacfuZis = false;
      bool KsLNKIJsYY = false;
      string RYjzAwsstk;
      string MCfsFVbeGX;
      string SjGoWWGFUL;
      string eYVOdLLtFH;
      string JegrqZXKgo;
      string MdIwwhSubc;
      string omYhGmgQOt;
      string JgZyOmDNyw;
      string ywXeyAPYRu;
      string rQRbSVGylD;
      string sHumeeEKhJ;
      string eExfesOsiF;
      string WIySBsOxfr;
      string gEbuDqAkzT;
      string wFpIQnTlwY;
      string GMPffjIbkl;
      string PGdpcZcCbn;
      string rdtPIQRpCM;
      string ZcBGkTouOT;
      string hYzNDpbAfq;
      if(RYjzAwsstk == sHumeeEKhJ){LRKIgcRzXO = true;}
      else if(sHumeeEKhJ == RYjzAwsstk){IjEwtXGzRL = true;}
      if(MCfsFVbeGX == eExfesOsiF){RSZXMmFXEI = true;}
      else if(eExfesOsiF == MCfsFVbeGX){UquOrwFpWn = true;}
      if(SjGoWWGFUL == WIySBsOxfr){jgmIFTdgMS = true;}
      else if(WIySBsOxfr == SjGoWWGFUL){dUKzZGXjmo = true;}
      if(eYVOdLLtFH == gEbuDqAkzT){oRKKBIRrZI = true;}
      else if(gEbuDqAkzT == eYVOdLLtFH){rqMFgjyiBJ = true;}
      if(JegrqZXKgo == wFpIQnTlwY){CoXzBPzaAP = true;}
      else if(wFpIQnTlwY == JegrqZXKgo){eVVrCmTZTL = true;}
      if(MdIwwhSubc == GMPffjIbkl){kEwXGddCDN = true;}
      else if(GMPffjIbkl == MdIwwhSubc){LLumWmZEWn = true;}
      if(omYhGmgQOt == PGdpcZcCbn){zkmEYAHOWD = true;}
      else if(PGdpcZcCbn == omYhGmgQOt){zVMbTddpgI = true;}
      if(JgZyOmDNyw == rdtPIQRpCM){VMxwGtJmGo = true;}
      if(ywXeyAPYRu == ZcBGkTouOT){UCfwhkVmEW = true;}
      if(rQRbSVGylD == hYzNDpbAfq){dPoMIQCSaB = true;}
      while(rdtPIQRpCM == JgZyOmDNyw){yVnMIIzRxm = true;}
      while(ZcBGkTouOT == ZcBGkTouOT){lxQacfuZis = true;}
      while(hYzNDpbAfq == hYzNDpbAfq){KsLNKIJsYY = true;}
      if(LRKIgcRzXO == true){LRKIgcRzXO = false;}
      if(RSZXMmFXEI == true){RSZXMmFXEI = false;}
      if(jgmIFTdgMS == true){jgmIFTdgMS = false;}
      if(oRKKBIRrZI == true){oRKKBIRrZI = false;}
      if(CoXzBPzaAP == true){CoXzBPzaAP = false;}
      if(kEwXGddCDN == true){kEwXGddCDN = false;}
      if(zkmEYAHOWD == true){zkmEYAHOWD = false;}
      if(VMxwGtJmGo == true){VMxwGtJmGo = false;}
      if(UCfwhkVmEW == true){UCfwhkVmEW = false;}
      if(dPoMIQCSaB == true){dPoMIQCSaB = false;}
      if(IjEwtXGzRL == true){IjEwtXGzRL = false;}
      if(UquOrwFpWn == true){UquOrwFpWn = false;}
      if(dUKzZGXjmo == true){dUKzZGXjmo = false;}
      if(rqMFgjyiBJ == true){rqMFgjyiBJ = false;}
      if(eVVrCmTZTL == true){eVVrCmTZTL = false;}
      if(LLumWmZEWn == true){LLumWmZEWn = false;}
      if(zVMbTddpgI == true){zVMbTddpgI = false;}
      if(yVnMIIzRxm == true){yVnMIIzRxm = false;}
      if(lxQacfuZis == true){lxQacfuZis = false;}
      if(KsLNKIJsYY == true){KsLNKIJsYY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBWFCAUJHR
{ 
  void VYKapXedCn()
  { 
      bool gegURBUngE = false;
      bool YBUDyWCDBD = false;
      bool mAnEtTmBSz = false;
      bool ITBkSnAUQG = false;
      bool HAoAIuObQT = false;
      bool NcpGigpbZx = false;
      bool OSVguEzijK = false;
      bool WgmtumLnwy = false;
      bool FKjzkfcuCl = false;
      bool xXtTrneHED = false;
      bool weqGwfpuKu = false;
      bool VCfbqDiVwP = false;
      bool bEgyNymSCG = false;
      bool HDirCaTdCE = false;
      bool phjGQuqSbn = false;
      bool FILobqyssy = false;
      bool sWrDmRSnYQ = false;
      bool jESqZtUZhR = false;
      bool HUqOBzrtPL = false;
      bool bakELSofTy = false;
      string pJPlqFsuip;
      string CYLeTRUDhL;
      string YphVQSuzGf;
      string OkWbMUKtlt;
      string OZDuTAwAHP;
      string fLcisAbtVX;
      string JsoDaQBiRy;
      string HaQmxzllBQ;
      string WtrpADIniM;
      string sQYOjUkATC;
      string yMhIIFtols;
      string NorEBPByDX;
      string INAFEqBCDb;
      string NlSyRJLigt;
      string ISBoyEXTMU;
      string TlxwtjMcDR;
      string ErlJebWslq;
      string DRRIPoLKHA;
      string SgphIbnVEh;
      string xiePpPgrJV;
      if(pJPlqFsuip == yMhIIFtols){gegURBUngE = true;}
      else if(yMhIIFtols == pJPlqFsuip){weqGwfpuKu = true;}
      if(CYLeTRUDhL == NorEBPByDX){YBUDyWCDBD = true;}
      else if(NorEBPByDX == CYLeTRUDhL){VCfbqDiVwP = true;}
      if(YphVQSuzGf == INAFEqBCDb){mAnEtTmBSz = true;}
      else if(INAFEqBCDb == YphVQSuzGf){bEgyNymSCG = true;}
      if(OkWbMUKtlt == NlSyRJLigt){ITBkSnAUQG = true;}
      else if(NlSyRJLigt == OkWbMUKtlt){HDirCaTdCE = true;}
      if(OZDuTAwAHP == ISBoyEXTMU){HAoAIuObQT = true;}
      else if(ISBoyEXTMU == OZDuTAwAHP){phjGQuqSbn = true;}
      if(fLcisAbtVX == TlxwtjMcDR){NcpGigpbZx = true;}
      else if(TlxwtjMcDR == fLcisAbtVX){FILobqyssy = true;}
      if(JsoDaQBiRy == ErlJebWslq){OSVguEzijK = true;}
      else if(ErlJebWslq == JsoDaQBiRy){sWrDmRSnYQ = true;}
      if(HaQmxzllBQ == DRRIPoLKHA){WgmtumLnwy = true;}
      if(WtrpADIniM == SgphIbnVEh){FKjzkfcuCl = true;}
      if(sQYOjUkATC == xiePpPgrJV){xXtTrneHED = true;}
      while(DRRIPoLKHA == HaQmxzllBQ){jESqZtUZhR = true;}
      while(SgphIbnVEh == SgphIbnVEh){HUqOBzrtPL = true;}
      while(xiePpPgrJV == xiePpPgrJV){bakELSofTy = true;}
      if(gegURBUngE == true){gegURBUngE = false;}
      if(YBUDyWCDBD == true){YBUDyWCDBD = false;}
      if(mAnEtTmBSz == true){mAnEtTmBSz = false;}
      if(ITBkSnAUQG == true){ITBkSnAUQG = false;}
      if(HAoAIuObQT == true){HAoAIuObQT = false;}
      if(NcpGigpbZx == true){NcpGigpbZx = false;}
      if(OSVguEzijK == true){OSVguEzijK = false;}
      if(WgmtumLnwy == true){WgmtumLnwy = false;}
      if(FKjzkfcuCl == true){FKjzkfcuCl = false;}
      if(xXtTrneHED == true){xXtTrneHED = false;}
      if(weqGwfpuKu == true){weqGwfpuKu = false;}
      if(VCfbqDiVwP == true){VCfbqDiVwP = false;}
      if(bEgyNymSCG == true){bEgyNymSCG = false;}
      if(HDirCaTdCE == true){HDirCaTdCE = false;}
      if(phjGQuqSbn == true){phjGQuqSbn = false;}
      if(FILobqyssy == true){FILobqyssy = false;}
      if(sWrDmRSnYQ == true){sWrDmRSnYQ = false;}
      if(jESqZtUZhR == true){jESqZtUZhR = false;}
      if(HUqOBzrtPL == true){HUqOBzrtPL = false;}
      if(bakELSofTy == true){bakELSofTy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMZEDLFIXH
{ 
  void xoDHVbOhGg()
  { 
      bool KFWMmNEeJf = false;
      bool OruAojqPZA = false;
      bool dTyGZNwjgK = false;
      bool nhPlkTMVSR = false;
      bool WASWLpwERQ = false;
      bool odbirqHPmY = false;
      bool QTxyrgcJOV = false;
      bool XUwHddAauj = false;
      bool RrSQVKGgtt = false;
      bool LxitADCTee = false;
      bool NmousTgTFN = false;
      bool pgUCHYBgcg = false;
      bool awOUJZlCGZ = false;
      bool afuQVdCWWC = false;
      bool clafDecflb = false;
      bool BVqyDRXUlS = false;
      bool heMelKkEgd = false;
      bool VdJaDnUiQe = false;
      bool xGPeXFoxME = false;
      bool FhkDUyZwss = false;
      string begbbsHBdU;
      string qdORlllmfw;
      string SOUfEKDyWr;
      string hFdquuciZk;
      string emDnzpcPsF;
      string LtRTeMJAWR;
      string pJekmlAXWp;
      string ICNuReKgfO;
      string gnERfnmJLh;
      string kbMHuUISBN;
      string oErCwJfWCz;
      string BcTHkBEMFz;
      string yqMnEgoFAw;
      string WreSZbuCVV;
      string HQHMfIHFWs;
      string PuNCOyrDxO;
      string UaWFbJxBhJ;
      string FCqirhizIw;
      string ZjiGfbecDa;
      string irFGBgsBjW;
      if(begbbsHBdU == oErCwJfWCz){KFWMmNEeJf = true;}
      else if(oErCwJfWCz == begbbsHBdU){NmousTgTFN = true;}
      if(qdORlllmfw == BcTHkBEMFz){OruAojqPZA = true;}
      else if(BcTHkBEMFz == qdORlllmfw){pgUCHYBgcg = true;}
      if(SOUfEKDyWr == yqMnEgoFAw){dTyGZNwjgK = true;}
      else if(yqMnEgoFAw == SOUfEKDyWr){awOUJZlCGZ = true;}
      if(hFdquuciZk == WreSZbuCVV){nhPlkTMVSR = true;}
      else if(WreSZbuCVV == hFdquuciZk){afuQVdCWWC = true;}
      if(emDnzpcPsF == HQHMfIHFWs){WASWLpwERQ = true;}
      else if(HQHMfIHFWs == emDnzpcPsF){clafDecflb = true;}
      if(LtRTeMJAWR == PuNCOyrDxO){odbirqHPmY = true;}
      else if(PuNCOyrDxO == LtRTeMJAWR){BVqyDRXUlS = true;}
      if(pJekmlAXWp == UaWFbJxBhJ){QTxyrgcJOV = true;}
      else if(UaWFbJxBhJ == pJekmlAXWp){heMelKkEgd = true;}
      if(ICNuReKgfO == FCqirhizIw){XUwHddAauj = true;}
      if(gnERfnmJLh == ZjiGfbecDa){RrSQVKGgtt = true;}
      if(kbMHuUISBN == irFGBgsBjW){LxitADCTee = true;}
      while(FCqirhizIw == ICNuReKgfO){VdJaDnUiQe = true;}
      while(ZjiGfbecDa == ZjiGfbecDa){xGPeXFoxME = true;}
      while(irFGBgsBjW == irFGBgsBjW){FhkDUyZwss = true;}
      if(KFWMmNEeJf == true){KFWMmNEeJf = false;}
      if(OruAojqPZA == true){OruAojqPZA = false;}
      if(dTyGZNwjgK == true){dTyGZNwjgK = false;}
      if(nhPlkTMVSR == true){nhPlkTMVSR = false;}
      if(WASWLpwERQ == true){WASWLpwERQ = false;}
      if(odbirqHPmY == true){odbirqHPmY = false;}
      if(QTxyrgcJOV == true){QTxyrgcJOV = false;}
      if(XUwHddAauj == true){XUwHddAauj = false;}
      if(RrSQVKGgtt == true){RrSQVKGgtt = false;}
      if(LxitADCTee == true){LxitADCTee = false;}
      if(NmousTgTFN == true){NmousTgTFN = false;}
      if(pgUCHYBgcg == true){pgUCHYBgcg = false;}
      if(awOUJZlCGZ == true){awOUJZlCGZ = false;}
      if(afuQVdCWWC == true){afuQVdCWWC = false;}
      if(clafDecflb == true){clafDecflb = false;}
      if(BVqyDRXUlS == true){BVqyDRXUlS = false;}
      if(heMelKkEgd == true){heMelKkEgd = false;}
      if(VdJaDnUiQe == true){VdJaDnUiQe = false;}
      if(xGPeXFoxME == true){xGPeXFoxME = false;}
      if(FhkDUyZwss == true){FhkDUyZwss = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPMYDLZTFU
{ 
  void LEztsUsrTU()
  { 
      bool ajfTGPXnPA = false;
      bool SUcmXgQeel = false;
      bool VnsRFagwXl = false;
      bool UAArJAJcMe = false;
      bool woSdCZjlOV = false;
      bool YnpYImpONe = false;
      bool iaQcfRUjcX = false;
      bool WmSzogUOPf = false;
      bool qugCNfKbiW = false;
      bool JuOgwUXpyj = false;
      bool FzIpykVqib = false;
      bool RayhnmtOPz = false;
      bool HsAGOaYkDU = false;
      bool IeQfarlpDc = false;
      bool KTrHEhxgsI = false;
      bool aJazcMyBbW = false;
      bool MkmNTmKSHw = false;
      bool ADKmomAsCg = false;
      bool dqqttyDQCO = false;
      bool skOfPYfemQ = false;
      string YbMnKurdZk;
      string wZRlPJHFUW;
      string gbhCZHhlyR;
      string WHVtRmMfwJ;
      string fSVklJcViz;
      string JnZiwwsJND;
      string NGeHNoDXUc;
      string wbJKqOFxQQ;
      string dMDzHhglxU;
      string tCRruZmOWw;
      string FFAGCheOqg;
      string qwsxYADfzf;
      string HQaAhtKQOR;
      string bqZTKYMwwZ;
      string DSuPdxJTTu;
      string WHOqooezXI;
      string XNzZFzWYmz;
      string nGjZbnVKWk;
      string jpxTuTcheU;
      string tMYmCoTUKd;
      if(YbMnKurdZk == FFAGCheOqg){ajfTGPXnPA = true;}
      else if(FFAGCheOqg == YbMnKurdZk){FzIpykVqib = true;}
      if(wZRlPJHFUW == qwsxYADfzf){SUcmXgQeel = true;}
      else if(qwsxYADfzf == wZRlPJHFUW){RayhnmtOPz = true;}
      if(gbhCZHhlyR == HQaAhtKQOR){VnsRFagwXl = true;}
      else if(HQaAhtKQOR == gbhCZHhlyR){HsAGOaYkDU = true;}
      if(WHVtRmMfwJ == bqZTKYMwwZ){UAArJAJcMe = true;}
      else if(bqZTKYMwwZ == WHVtRmMfwJ){IeQfarlpDc = true;}
      if(fSVklJcViz == DSuPdxJTTu){woSdCZjlOV = true;}
      else if(DSuPdxJTTu == fSVklJcViz){KTrHEhxgsI = true;}
      if(JnZiwwsJND == WHOqooezXI){YnpYImpONe = true;}
      else if(WHOqooezXI == JnZiwwsJND){aJazcMyBbW = true;}
      if(NGeHNoDXUc == XNzZFzWYmz){iaQcfRUjcX = true;}
      else if(XNzZFzWYmz == NGeHNoDXUc){MkmNTmKSHw = true;}
      if(wbJKqOFxQQ == nGjZbnVKWk){WmSzogUOPf = true;}
      if(dMDzHhglxU == jpxTuTcheU){qugCNfKbiW = true;}
      if(tCRruZmOWw == tMYmCoTUKd){JuOgwUXpyj = true;}
      while(nGjZbnVKWk == wbJKqOFxQQ){ADKmomAsCg = true;}
      while(jpxTuTcheU == jpxTuTcheU){dqqttyDQCO = true;}
      while(tMYmCoTUKd == tMYmCoTUKd){skOfPYfemQ = true;}
      if(ajfTGPXnPA == true){ajfTGPXnPA = false;}
      if(SUcmXgQeel == true){SUcmXgQeel = false;}
      if(VnsRFagwXl == true){VnsRFagwXl = false;}
      if(UAArJAJcMe == true){UAArJAJcMe = false;}
      if(woSdCZjlOV == true){woSdCZjlOV = false;}
      if(YnpYImpONe == true){YnpYImpONe = false;}
      if(iaQcfRUjcX == true){iaQcfRUjcX = false;}
      if(WmSzogUOPf == true){WmSzogUOPf = false;}
      if(qugCNfKbiW == true){qugCNfKbiW = false;}
      if(JuOgwUXpyj == true){JuOgwUXpyj = false;}
      if(FzIpykVqib == true){FzIpykVqib = false;}
      if(RayhnmtOPz == true){RayhnmtOPz = false;}
      if(HsAGOaYkDU == true){HsAGOaYkDU = false;}
      if(IeQfarlpDc == true){IeQfarlpDc = false;}
      if(KTrHEhxgsI == true){KTrHEhxgsI = false;}
      if(aJazcMyBbW == true){aJazcMyBbW = false;}
      if(MkmNTmKSHw == true){MkmNTmKSHw = false;}
      if(ADKmomAsCg == true){ADKmomAsCg = false;}
      if(dqqttyDQCO == true){dqqttyDQCO = false;}
      if(skOfPYfemQ == true){skOfPYfemQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTYEBYJBYZ
{ 
  void teGlrupMqe()
  { 
      bool rcNzKDxXlY = false;
      bool jPQuFsEsuy = false;
      bool fXIjVyEiAH = false;
      bool kYmakMTpkF = false;
      bool TiYpoZgHue = false;
      bool ejRknTUdcM = false;
      bool zNXdnLboJs = false;
      bool YNHodwyRtw = false;
      bool QxnUbAGClQ = false;
      bool qoMYFGLuBd = false;
      bool xqxBGRcbGr = false;
      bool VCjguBYDBn = false;
      bool FZDrBjAhjX = false;
      bool kCQQyZAmOK = false;
      bool XewtunFfdE = false;
      bool hItNYXnEzW = false;
      bool QtrhHSlShU = false;
      bool BkopPZcIxM = false;
      bool dUDfpbIDra = false;
      bool lumrtdmOmb = false;
      string FIrHCKesrd;
      string KORNUungxx;
      string hqrqgbjohq;
      string eQYjNQcEck;
      string jXTBQNpOiC;
      string OCEkXOPBaa;
      string ZoLAztogAE;
      string RiEMNKXqZT;
      string kVGfccLnLy;
      string AbdBKtMTBW;
      string XINdjexrXN;
      string qYaGoEieWW;
      string hBVCEpECCT;
      string yDoDwcIbuy;
      string eTQyHaAXMG;
      string KgwdnVmLYt;
      string ZtoDPmiXKM;
      string uHjYrOkWtd;
      string ogpwIQHLPZ;
      string pxCAXjdMiT;
      if(FIrHCKesrd == XINdjexrXN){rcNzKDxXlY = true;}
      else if(XINdjexrXN == FIrHCKesrd){xqxBGRcbGr = true;}
      if(KORNUungxx == qYaGoEieWW){jPQuFsEsuy = true;}
      else if(qYaGoEieWW == KORNUungxx){VCjguBYDBn = true;}
      if(hqrqgbjohq == hBVCEpECCT){fXIjVyEiAH = true;}
      else if(hBVCEpECCT == hqrqgbjohq){FZDrBjAhjX = true;}
      if(eQYjNQcEck == yDoDwcIbuy){kYmakMTpkF = true;}
      else if(yDoDwcIbuy == eQYjNQcEck){kCQQyZAmOK = true;}
      if(jXTBQNpOiC == eTQyHaAXMG){TiYpoZgHue = true;}
      else if(eTQyHaAXMG == jXTBQNpOiC){XewtunFfdE = true;}
      if(OCEkXOPBaa == KgwdnVmLYt){ejRknTUdcM = true;}
      else if(KgwdnVmLYt == OCEkXOPBaa){hItNYXnEzW = true;}
      if(ZoLAztogAE == ZtoDPmiXKM){zNXdnLboJs = true;}
      else if(ZtoDPmiXKM == ZoLAztogAE){QtrhHSlShU = true;}
      if(RiEMNKXqZT == uHjYrOkWtd){YNHodwyRtw = true;}
      if(kVGfccLnLy == ogpwIQHLPZ){QxnUbAGClQ = true;}
      if(AbdBKtMTBW == pxCAXjdMiT){qoMYFGLuBd = true;}
      while(uHjYrOkWtd == RiEMNKXqZT){BkopPZcIxM = true;}
      while(ogpwIQHLPZ == ogpwIQHLPZ){dUDfpbIDra = true;}
      while(pxCAXjdMiT == pxCAXjdMiT){lumrtdmOmb = true;}
      if(rcNzKDxXlY == true){rcNzKDxXlY = false;}
      if(jPQuFsEsuy == true){jPQuFsEsuy = false;}
      if(fXIjVyEiAH == true){fXIjVyEiAH = false;}
      if(kYmakMTpkF == true){kYmakMTpkF = false;}
      if(TiYpoZgHue == true){TiYpoZgHue = false;}
      if(ejRknTUdcM == true){ejRknTUdcM = false;}
      if(zNXdnLboJs == true){zNXdnLboJs = false;}
      if(YNHodwyRtw == true){YNHodwyRtw = false;}
      if(QxnUbAGClQ == true){QxnUbAGClQ = false;}
      if(qoMYFGLuBd == true){qoMYFGLuBd = false;}
      if(xqxBGRcbGr == true){xqxBGRcbGr = false;}
      if(VCjguBYDBn == true){VCjguBYDBn = false;}
      if(FZDrBjAhjX == true){FZDrBjAhjX = false;}
      if(kCQQyZAmOK == true){kCQQyZAmOK = false;}
      if(XewtunFfdE == true){XewtunFfdE = false;}
      if(hItNYXnEzW == true){hItNYXnEzW = false;}
      if(QtrhHSlShU == true){QtrhHSlShU = false;}
      if(BkopPZcIxM == true){BkopPZcIxM = false;}
      if(dUDfpbIDra == true){dUDfpbIDra = false;}
      if(lumrtdmOmb == true){lumrtdmOmb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMTTHVGGGL
{ 
  void SPYskkgmng()
  { 
      bool sLXDdfOaeH = false;
      bool olMOhTnfNW = false;
      bool ZoDMMFrptP = false;
      bool OQFIuznEoG = false;
      bool FInZxcAGzq = false;
      bool DdCZcEIKpY = false;
      bool mYfOsXfESh = false;
      bool fiqGQRBcOi = false;
      bool FlpCMkNfeq = false;
      bool qcOPTgbYfZ = false;
      bool xumQLTluIL = false;
      bool CewGTBhcCI = false;
      bool KAZbqDUamj = false;
      bool obwolJyZqr = false;
      bool yRWToLfHwR = false;
      bool yzWXPwVLYH = false;
      bool zLIYWZhHUJ = false;
      bool CIkJKrdFlf = false;
      bool WNeUkoFYYo = false;
      bool nmAislJxxO = false;
      string xeOeJShNkb;
      string ElANTdfhBC;
      string CchnrqiYlh;
      string JBqYFMWRfj;
      string pLhxOOGCDI;
      string blesmUxZlR;
      string jIbDRCuaHH;
      string GNBQMpujZc;
      string jfVcFXWxkk;
      string OxfNAgjefL;
      string TetwCNjOfx;
      string YMzIgDmyxt;
      string fxpWrIhnPf;
      string GPENJEkZaq;
      string mHQnLCxWfw;
      string slgkfVoXEs;
      string fwyAqIIkzc;
      string SNWGGXgCKo;
      string LLHSlTiShm;
      string PNUgLqJQwC;
      if(xeOeJShNkb == TetwCNjOfx){sLXDdfOaeH = true;}
      else if(TetwCNjOfx == xeOeJShNkb){xumQLTluIL = true;}
      if(ElANTdfhBC == YMzIgDmyxt){olMOhTnfNW = true;}
      else if(YMzIgDmyxt == ElANTdfhBC){CewGTBhcCI = true;}
      if(CchnrqiYlh == fxpWrIhnPf){ZoDMMFrptP = true;}
      else if(fxpWrIhnPf == CchnrqiYlh){KAZbqDUamj = true;}
      if(JBqYFMWRfj == GPENJEkZaq){OQFIuznEoG = true;}
      else if(GPENJEkZaq == JBqYFMWRfj){obwolJyZqr = true;}
      if(pLhxOOGCDI == mHQnLCxWfw){FInZxcAGzq = true;}
      else if(mHQnLCxWfw == pLhxOOGCDI){yRWToLfHwR = true;}
      if(blesmUxZlR == slgkfVoXEs){DdCZcEIKpY = true;}
      else if(slgkfVoXEs == blesmUxZlR){yzWXPwVLYH = true;}
      if(jIbDRCuaHH == fwyAqIIkzc){mYfOsXfESh = true;}
      else if(fwyAqIIkzc == jIbDRCuaHH){zLIYWZhHUJ = true;}
      if(GNBQMpujZc == SNWGGXgCKo){fiqGQRBcOi = true;}
      if(jfVcFXWxkk == LLHSlTiShm){FlpCMkNfeq = true;}
      if(OxfNAgjefL == PNUgLqJQwC){qcOPTgbYfZ = true;}
      while(SNWGGXgCKo == GNBQMpujZc){CIkJKrdFlf = true;}
      while(LLHSlTiShm == LLHSlTiShm){WNeUkoFYYo = true;}
      while(PNUgLqJQwC == PNUgLqJQwC){nmAislJxxO = true;}
      if(sLXDdfOaeH == true){sLXDdfOaeH = false;}
      if(olMOhTnfNW == true){olMOhTnfNW = false;}
      if(ZoDMMFrptP == true){ZoDMMFrptP = false;}
      if(OQFIuznEoG == true){OQFIuznEoG = false;}
      if(FInZxcAGzq == true){FInZxcAGzq = false;}
      if(DdCZcEIKpY == true){DdCZcEIKpY = false;}
      if(mYfOsXfESh == true){mYfOsXfESh = false;}
      if(fiqGQRBcOi == true){fiqGQRBcOi = false;}
      if(FlpCMkNfeq == true){FlpCMkNfeq = false;}
      if(qcOPTgbYfZ == true){qcOPTgbYfZ = false;}
      if(xumQLTluIL == true){xumQLTluIL = false;}
      if(CewGTBhcCI == true){CewGTBhcCI = false;}
      if(KAZbqDUamj == true){KAZbqDUamj = false;}
      if(obwolJyZqr == true){obwolJyZqr = false;}
      if(yRWToLfHwR == true){yRWToLfHwR = false;}
      if(yzWXPwVLYH == true){yzWXPwVLYH = false;}
      if(zLIYWZhHUJ == true){zLIYWZhHUJ = false;}
      if(CIkJKrdFlf == true){CIkJKrdFlf = false;}
      if(WNeUkoFYYo == true){WNeUkoFYYo = false;}
      if(nmAislJxxO == true){nmAislJxxO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ETKVUAWJKQ
{ 
  void PGkMOgWkdf()
  { 
      bool cMpcCkYWjT = false;
      bool lbNoHzhMet = false;
      bool LgclnEYltx = false;
      bool SLJsBEDeJW = false;
      bool rVqgjGnoyG = false;
      bool adERMwiEoy = false;
      bool LlcmBaRTmC = false;
      bool uCCHCppwBh = false;
      bool PjnnWoHrgF = false;
      bool UzpLKFsDfJ = false;
      bool nUBuKXawPV = false;
      bool FmCHhbynQM = false;
      bool TZlhhwMqxw = false;
      bool xmPrsuhrcy = false;
      bool NKbLzgwidi = false;
      bool HElSoNhTNO = false;
      bool KjzTYSWKNl = false;
      bool sFKSzIyahA = false;
      bool zcMNorAxCf = false;
      bool NOeOmcLIlg = false;
      string VAXmQWgnRP;
      string LItHbIaCJU;
      string tHLbZibuFc;
      string MYjgNzxXmq;
      string dXPyqXGTMs;
      string oNMbPOnuNh;
      string ulioDlYMtb;
      string LCORpWrNkB;
      string bHiMmyLHRz;
      string LCKFwrnZuE;
      string ytZjhmzuks;
      string VZKLFmCWBE;
      string aRttPIrIVx;
      string hRRfDhgyeA;
      string zQWXckqyAI;
      string oQYpdgzeTY;
      string tpZmLEIeIW;
      string GErBFJtWRe;
      string RtIMIQsaBW;
      string iBeFGIqiMX;
      if(VAXmQWgnRP == ytZjhmzuks){cMpcCkYWjT = true;}
      else if(ytZjhmzuks == VAXmQWgnRP){nUBuKXawPV = true;}
      if(LItHbIaCJU == VZKLFmCWBE){lbNoHzhMet = true;}
      else if(VZKLFmCWBE == LItHbIaCJU){FmCHhbynQM = true;}
      if(tHLbZibuFc == aRttPIrIVx){LgclnEYltx = true;}
      else if(aRttPIrIVx == tHLbZibuFc){TZlhhwMqxw = true;}
      if(MYjgNzxXmq == hRRfDhgyeA){SLJsBEDeJW = true;}
      else if(hRRfDhgyeA == MYjgNzxXmq){xmPrsuhrcy = true;}
      if(dXPyqXGTMs == zQWXckqyAI){rVqgjGnoyG = true;}
      else if(zQWXckqyAI == dXPyqXGTMs){NKbLzgwidi = true;}
      if(oNMbPOnuNh == oQYpdgzeTY){adERMwiEoy = true;}
      else if(oQYpdgzeTY == oNMbPOnuNh){HElSoNhTNO = true;}
      if(ulioDlYMtb == tpZmLEIeIW){LlcmBaRTmC = true;}
      else if(tpZmLEIeIW == ulioDlYMtb){KjzTYSWKNl = true;}
      if(LCORpWrNkB == GErBFJtWRe){uCCHCppwBh = true;}
      if(bHiMmyLHRz == RtIMIQsaBW){PjnnWoHrgF = true;}
      if(LCKFwrnZuE == iBeFGIqiMX){UzpLKFsDfJ = true;}
      while(GErBFJtWRe == LCORpWrNkB){sFKSzIyahA = true;}
      while(RtIMIQsaBW == RtIMIQsaBW){zcMNorAxCf = true;}
      while(iBeFGIqiMX == iBeFGIqiMX){NOeOmcLIlg = true;}
      if(cMpcCkYWjT == true){cMpcCkYWjT = false;}
      if(lbNoHzhMet == true){lbNoHzhMet = false;}
      if(LgclnEYltx == true){LgclnEYltx = false;}
      if(SLJsBEDeJW == true){SLJsBEDeJW = false;}
      if(rVqgjGnoyG == true){rVqgjGnoyG = false;}
      if(adERMwiEoy == true){adERMwiEoy = false;}
      if(LlcmBaRTmC == true){LlcmBaRTmC = false;}
      if(uCCHCppwBh == true){uCCHCppwBh = false;}
      if(PjnnWoHrgF == true){PjnnWoHrgF = false;}
      if(UzpLKFsDfJ == true){UzpLKFsDfJ = false;}
      if(nUBuKXawPV == true){nUBuKXawPV = false;}
      if(FmCHhbynQM == true){FmCHhbynQM = false;}
      if(TZlhhwMqxw == true){TZlhhwMqxw = false;}
      if(xmPrsuhrcy == true){xmPrsuhrcy = false;}
      if(NKbLzgwidi == true){NKbLzgwidi = false;}
      if(HElSoNhTNO == true){HElSoNhTNO = false;}
      if(KjzTYSWKNl == true){KjzTYSWKNl = false;}
      if(sFKSzIyahA == true){sFKSzIyahA = false;}
      if(zcMNorAxCf == true){zcMNorAxCf = false;}
      if(NOeOmcLIlg == true){NOeOmcLIlg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQEGEGBLCX
{ 
  void qriBtBGpmY()
  { 
      bool SfCjDEHQAx = false;
      bool rgoqMILgUK = false;
      bool CSaikOkXYO = false;
      bool sqFPClULfi = false;
      bool ZblpUKQQAO = false;
      bool lbIkeAETyo = false;
      bool TjrlDBbYoa = false;
      bool nAAlkZfkNa = false;
      bool xUWKbRiUjB = false;
      bool gAMqOpjAlT = false;
      bool iqaZalaVzE = false;
      bool TSGXqzMhJl = false;
      bool SGomsmmJXt = false;
      bool pfzsqFsxjo = false;
      bool pMUehOtozO = false;
      bool cBpzBbCngm = false;
      bool zRyENnTMfl = false;
      bool GPyTuGkJEe = false;
      bool rxKIRoozrO = false;
      bool DEQwpYNQQt = false;
      string RllfcwnzTF;
      string nIOMmcpCAn;
      string ctASJWbCmJ;
      string POTSEPRuZG;
      string thYUBKVVcC;
      string AsRmMXkTWG;
      string TkMKoYnwHX;
      string KucsstUfQy;
      string BGYjJWxfGf;
      string dyXSlIUOfc;
      string VZNFqEQXsR;
      string CFDYFNLcAS;
      string bIpasMXJHk;
      string YGAnbbrTrE;
      string FYmndXuzNX;
      string xrNNANilLe;
      string gHPIruFOwd;
      string UrkwMCVBxU;
      string RXuimgsmmN;
      string rGHNXyIdwh;
      if(RllfcwnzTF == VZNFqEQXsR){SfCjDEHQAx = true;}
      else if(VZNFqEQXsR == RllfcwnzTF){iqaZalaVzE = true;}
      if(nIOMmcpCAn == CFDYFNLcAS){rgoqMILgUK = true;}
      else if(CFDYFNLcAS == nIOMmcpCAn){TSGXqzMhJl = true;}
      if(ctASJWbCmJ == bIpasMXJHk){CSaikOkXYO = true;}
      else if(bIpasMXJHk == ctASJWbCmJ){SGomsmmJXt = true;}
      if(POTSEPRuZG == YGAnbbrTrE){sqFPClULfi = true;}
      else if(YGAnbbrTrE == POTSEPRuZG){pfzsqFsxjo = true;}
      if(thYUBKVVcC == FYmndXuzNX){ZblpUKQQAO = true;}
      else if(FYmndXuzNX == thYUBKVVcC){pMUehOtozO = true;}
      if(AsRmMXkTWG == xrNNANilLe){lbIkeAETyo = true;}
      else if(xrNNANilLe == AsRmMXkTWG){cBpzBbCngm = true;}
      if(TkMKoYnwHX == gHPIruFOwd){TjrlDBbYoa = true;}
      else if(gHPIruFOwd == TkMKoYnwHX){zRyENnTMfl = true;}
      if(KucsstUfQy == UrkwMCVBxU){nAAlkZfkNa = true;}
      if(BGYjJWxfGf == RXuimgsmmN){xUWKbRiUjB = true;}
      if(dyXSlIUOfc == rGHNXyIdwh){gAMqOpjAlT = true;}
      while(UrkwMCVBxU == KucsstUfQy){GPyTuGkJEe = true;}
      while(RXuimgsmmN == RXuimgsmmN){rxKIRoozrO = true;}
      while(rGHNXyIdwh == rGHNXyIdwh){DEQwpYNQQt = true;}
      if(SfCjDEHQAx == true){SfCjDEHQAx = false;}
      if(rgoqMILgUK == true){rgoqMILgUK = false;}
      if(CSaikOkXYO == true){CSaikOkXYO = false;}
      if(sqFPClULfi == true){sqFPClULfi = false;}
      if(ZblpUKQQAO == true){ZblpUKQQAO = false;}
      if(lbIkeAETyo == true){lbIkeAETyo = false;}
      if(TjrlDBbYoa == true){TjrlDBbYoa = false;}
      if(nAAlkZfkNa == true){nAAlkZfkNa = false;}
      if(xUWKbRiUjB == true){xUWKbRiUjB = false;}
      if(gAMqOpjAlT == true){gAMqOpjAlT = false;}
      if(iqaZalaVzE == true){iqaZalaVzE = false;}
      if(TSGXqzMhJl == true){TSGXqzMhJl = false;}
      if(SGomsmmJXt == true){SGomsmmJXt = false;}
      if(pfzsqFsxjo == true){pfzsqFsxjo = false;}
      if(pMUehOtozO == true){pMUehOtozO = false;}
      if(cBpzBbCngm == true){cBpzBbCngm = false;}
      if(zRyENnTMfl == true){zRyENnTMfl = false;}
      if(GPyTuGkJEe == true){GPyTuGkJEe = false;}
      if(rxKIRoozrO == true){rxKIRoozrO = false;}
      if(DEQwpYNQQt == true){DEQwpYNQQt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELUHZKNTGV
{ 
  void rLUSfUpZyB()
  { 
      bool QggPhCDmAP = false;
      bool mGzUtbMEFW = false;
      bool dSdeEunlTi = false;
      bool wyYYiWNoVK = false;
      bool DWwpQQNsqc = false;
      bool VylQnxCBKm = false;
      bool NRTQTnhakX = false;
      bool OXiuTGWnOm = false;
      bool guupNxLHkl = false;
      bool ULdhxlDeWb = false;
      bool imHSOyPqxg = false;
      bool ZNmWGSVcDV = false;
      bool cZozDDsAyg = false;
      bool DrQlEsmbbO = false;
      bool hTJDLGXHbd = false;
      bool PabAzIxIPK = false;
      bool FOsPdhwARM = false;
      bool etAnnIQlmx = false;
      bool ekYTRcPQlw = false;
      bool ueLRISatYc = false;
      string NyxTDwAXtS;
      string psRejUzfGY;
      string JORuqtrdOh;
      string lQtJQrbIVH;
      string NrbQzeGBsM;
      string XXCweyfCcI;
      string DVIMfYzIOr;
      string spJzKRmAuM;
      string nqjBJNOxeR;
      string LYfMDqiPkZ;
      string exmBSgODlM;
      string LfGPTMlHCR;
      string KBdwfUKxuS;
      string iXPVgqDiic;
      string zLLRFfRPrq;
      string FbMSPcSpUx;
      string WQISdnPkic;
      string ICXZRzpMqz;
      string DtEDNHKwGD;
      string XNNkFiCrnR;
      if(NyxTDwAXtS == exmBSgODlM){QggPhCDmAP = true;}
      else if(exmBSgODlM == NyxTDwAXtS){imHSOyPqxg = true;}
      if(psRejUzfGY == LfGPTMlHCR){mGzUtbMEFW = true;}
      else if(LfGPTMlHCR == psRejUzfGY){ZNmWGSVcDV = true;}
      if(JORuqtrdOh == KBdwfUKxuS){dSdeEunlTi = true;}
      else if(KBdwfUKxuS == JORuqtrdOh){cZozDDsAyg = true;}
      if(lQtJQrbIVH == iXPVgqDiic){wyYYiWNoVK = true;}
      else if(iXPVgqDiic == lQtJQrbIVH){DrQlEsmbbO = true;}
      if(NrbQzeGBsM == zLLRFfRPrq){DWwpQQNsqc = true;}
      else if(zLLRFfRPrq == NrbQzeGBsM){hTJDLGXHbd = true;}
      if(XXCweyfCcI == FbMSPcSpUx){VylQnxCBKm = true;}
      else if(FbMSPcSpUx == XXCweyfCcI){PabAzIxIPK = true;}
      if(DVIMfYzIOr == WQISdnPkic){NRTQTnhakX = true;}
      else if(WQISdnPkic == DVIMfYzIOr){FOsPdhwARM = true;}
      if(spJzKRmAuM == ICXZRzpMqz){OXiuTGWnOm = true;}
      if(nqjBJNOxeR == DtEDNHKwGD){guupNxLHkl = true;}
      if(LYfMDqiPkZ == XNNkFiCrnR){ULdhxlDeWb = true;}
      while(ICXZRzpMqz == spJzKRmAuM){etAnnIQlmx = true;}
      while(DtEDNHKwGD == DtEDNHKwGD){ekYTRcPQlw = true;}
      while(XNNkFiCrnR == XNNkFiCrnR){ueLRISatYc = true;}
      if(QggPhCDmAP == true){QggPhCDmAP = false;}
      if(mGzUtbMEFW == true){mGzUtbMEFW = false;}
      if(dSdeEunlTi == true){dSdeEunlTi = false;}
      if(wyYYiWNoVK == true){wyYYiWNoVK = false;}
      if(DWwpQQNsqc == true){DWwpQQNsqc = false;}
      if(VylQnxCBKm == true){VylQnxCBKm = false;}
      if(NRTQTnhakX == true){NRTQTnhakX = false;}
      if(OXiuTGWnOm == true){OXiuTGWnOm = false;}
      if(guupNxLHkl == true){guupNxLHkl = false;}
      if(ULdhxlDeWb == true){ULdhxlDeWb = false;}
      if(imHSOyPqxg == true){imHSOyPqxg = false;}
      if(ZNmWGSVcDV == true){ZNmWGSVcDV = false;}
      if(cZozDDsAyg == true){cZozDDsAyg = false;}
      if(DrQlEsmbbO == true){DrQlEsmbbO = false;}
      if(hTJDLGXHbd == true){hTJDLGXHbd = false;}
      if(PabAzIxIPK == true){PabAzIxIPK = false;}
      if(FOsPdhwARM == true){FOsPdhwARM = false;}
      if(etAnnIQlmx == true){etAnnIQlmx = false;}
      if(ekYTRcPQlw == true){ekYTRcPQlw = false;}
      if(ueLRISatYc == true){ueLRISatYc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YROVGAWRTQ
{ 
  void LfMZMuzZzj()
  { 
      bool hTMrpNBCJL = false;
      bool mzLyTCwASM = false;
      bool sCFKUVoTZH = false;
      bool lLJUDYNDtp = false;
      bool omWGVOAfyH = false;
      bool zoRJcfOBXT = false;
      bool YhbCZbopuu = false;
      bool nrGbWGfyoF = false;
      bool VJVSIwsAqX = false;
      bool JLfZRGLTft = false;
      bool ZKjDSGiplW = false;
      bool zPMRxOMJsc = false;
      bool hnzXkcMfJQ = false;
      bool tLSufLYSzC = false;
      bool NDOTXszNcD = false;
      bool tCaCLkLMRp = false;
      bool sCgUcnxRll = false;
      bool psJqPeYezq = false;
      bool cyDGVrkPit = false;
      bool zLAJIKWsqi = false;
      string hXWgWFcQAq;
      string KzZePsmgVH;
      string XmyBnSmoaG;
      string uqdQNSolGo;
      string ErCAHIqTkA;
      string jqXMMuZVrD;
      string RmpswTUIQw;
      string DAafDfjxsf;
      string bSDaWESQER;
      string sTsDXQCIEn;
      string miCnwjPrJf;
      string LbbMbyiPWq;
      string BDDzDjGXIl;
      string dbsErsPPdm;
      string nZHXGQqgaY;
      string hmlMmieDkM;
      string crjWCiiWTi;
      string iTkjDawerl;
      string rZwjEpofRJ;
      string NMeRJuojVW;
      if(hXWgWFcQAq == miCnwjPrJf){hTMrpNBCJL = true;}
      else if(miCnwjPrJf == hXWgWFcQAq){ZKjDSGiplW = true;}
      if(KzZePsmgVH == LbbMbyiPWq){mzLyTCwASM = true;}
      else if(LbbMbyiPWq == KzZePsmgVH){zPMRxOMJsc = true;}
      if(XmyBnSmoaG == BDDzDjGXIl){sCFKUVoTZH = true;}
      else if(BDDzDjGXIl == XmyBnSmoaG){hnzXkcMfJQ = true;}
      if(uqdQNSolGo == dbsErsPPdm){lLJUDYNDtp = true;}
      else if(dbsErsPPdm == uqdQNSolGo){tLSufLYSzC = true;}
      if(ErCAHIqTkA == nZHXGQqgaY){omWGVOAfyH = true;}
      else if(nZHXGQqgaY == ErCAHIqTkA){NDOTXszNcD = true;}
      if(jqXMMuZVrD == hmlMmieDkM){zoRJcfOBXT = true;}
      else if(hmlMmieDkM == jqXMMuZVrD){tCaCLkLMRp = true;}
      if(RmpswTUIQw == crjWCiiWTi){YhbCZbopuu = true;}
      else if(crjWCiiWTi == RmpswTUIQw){sCgUcnxRll = true;}
      if(DAafDfjxsf == iTkjDawerl){nrGbWGfyoF = true;}
      if(bSDaWESQER == rZwjEpofRJ){VJVSIwsAqX = true;}
      if(sTsDXQCIEn == NMeRJuojVW){JLfZRGLTft = true;}
      while(iTkjDawerl == DAafDfjxsf){psJqPeYezq = true;}
      while(rZwjEpofRJ == rZwjEpofRJ){cyDGVrkPit = true;}
      while(NMeRJuojVW == NMeRJuojVW){zLAJIKWsqi = true;}
      if(hTMrpNBCJL == true){hTMrpNBCJL = false;}
      if(mzLyTCwASM == true){mzLyTCwASM = false;}
      if(sCFKUVoTZH == true){sCFKUVoTZH = false;}
      if(lLJUDYNDtp == true){lLJUDYNDtp = false;}
      if(omWGVOAfyH == true){omWGVOAfyH = false;}
      if(zoRJcfOBXT == true){zoRJcfOBXT = false;}
      if(YhbCZbopuu == true){YhbCZbopuu = false;}
      if(nrGbWGfyoF == true){nrGbWGfyoF = false;}
      if(VJVSIwsAqX == true){VJVSIwsAqX = false;}
      if(JLfZRGLTft == true){JLfZRGLTft = false;}
      if(ZKjDSGiplW == true){ZKjDSGiplW = false;}
      if(zPMRxOMJsc == true){zPMRxOMJsc = false;}
      if(hnzXkcMfJQ == true){hnzXkcMfJQ = false;}
      if(tLSufLYSzC == true){tLSufLYSzC = false;}
      if(NDOTXszNcD == true){NDOTXszNcD = false;}
      if(tCaCLkLMRp == true){tCaCLkLMRp = false;}
      if(sCgUcnxRll == true){sCgUcnxRll = false;}
      if(psJqPeYezq == true){psJqPeYezq = false;}
      if(cyDGVrkPit == true){cyDGVrkPit = false;}
      if(zLAJIKWsqi == true){zLAJIKWsqi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODBEEJYSHT
{ 
  void EyFJKHbWBF()
  { 
      bool HQMsazNokz = false;
      bool awSCgXAGYp = false;
      bool sIsMiAYbxJ = false;
      bool qJtLYDpDnB = false;
      bool iVhLxsPqqR = false;
      bool jdBgBzXzKZ = false;
      bool akrbIRBGdc = false;
      bool gwRWHXZgPo = false;
      bool jgkeYNHNKY = false;
      bool fqsNaxcFDe = false;
      bool rJNNknLeYd = false;
      bool YpjUosANDt = false;
      bool KnwExpCDuJ = false;
      bool tUdjxaTWtk = false;
      bool BbnfApGYXh = false;
      bool wPCIUDNJQt = false;
      bool kHjOiEMzWO = false;
      bool YcSRshzPDG = false;
      bool idfMNdRUPt = false;
      bool MKGzzsrZww = false;
      string MfZJouXOqy;
      string xJryWKnZEX;
      string hAtkIUQATq;
      string WRbGBwDTPe;
      string migkncbbYA;
      string xYSfxLkoAU;
      string eWtzbfgkwa;
      string GTKYjzTJwf;
      string snaTtxywJp;
      string KOStAPngJI;
      string wpfyscOsuy;
      string qbrUbqwaEd;
      string gkbGPqBQYU;
      string KmzmjDHcZR;
      string iFAKziVxSJ;
      string SNbfbLNZhC;
      string byUZmEbFkY;
      string iTAmtbjRHf;
      string UDxOBwKTLX;
      string ohtXpkjaWu;
      if(MfZJouXOqy == wpfyscOsuy){HQMsazNokz = true;}
      else if(wpfyscOsuy == MfZJouXOqy){rJNNknLeYd = true;}
      if(xJryWKnZEX == qbrUbqwaEd){awSCgXAGYp = true;}
      else if(qbrUbqwaEd == xJryWKnZEX){YpjUosANDt = true;}
      if(hAtkIUQATq == gkbGPqBQYU){sIsMiAYbxJ = true;}
      else if(gkbGPqBQYU == hAtkIUQATq){KnwExpCDuJ = true;}
      if(WRbGBwDTPe == KmzmjDHcZR){qJtLYDpDnB = true;}
      else if(KmzmjDHcZR == WRbGBwDTPe){tUdjxaTWtk = true;}
      if(migkncbbYA == iFAKziVxSJ){iVhLxsPqqR = true;}
      else if(iFAKziVxSJ == migkncbbYA){BbnfApGYXh = true;}
      if(xYSfxLkoAU == SNbfbLNZhC){jdBgBzXzKZ = true;}
      else if(SNbfbLNZhC == xYSfxLkoAU){wPCIUDNJQt = true;}
      if(eWtzbfgkwa == byUZmEbFkY){akrbIRBGdc = true;}
      else if(byUZmEbFkY == eWtzbfgkwa){kHjOiEMzWO = true;}
      if(GTKYjzTJwf == iTAmtbjRHf){gwRWHXZgPo = true;}
      if(snaTtxywJp == UDxOBwKTLX){jgkeYNHNKY = true;}
      if(KOStAPngJI == ohtXpkjaWu){fqsNaxcFDe = true;}
      while(iTAmtbjRHf == GTKYjzTJwf){YcSRshzPDG = true;}
      while(UDxOBwKTLX == UDxOBwKTLX){idfMNdRUPt = true;}
      while(ohtXpkjaWu == ohtXpkjaWu){MKGzzsrZww = true;}
      if(HQMsazNokz == true){HQMsazNokz = false;}
      if(awSCgXAGYp == true){awSCgXAGYp = false;}
      if(sIsMiAYbxJ == true){sIsMiAYbxJ = false;}
      if(qJtLYDpDnB == true){qJtLYDpDnB = false;}
      if(iVhLxsPqqR == true){iVhLxsPqqR = false;}
      if(jdBgBzXzKZ == true){jdBgBzXzKZ = false;}
      if(akrbIRBGdc == true){akrbIRBGdc = false;}
      if(gwRWHXZgPo == true){gwRWHXZgPo = false;}
      if(jgkeYNHNKY == true){jgkeYNHNKY = false;}
      if(fqsNaxcFDe == true){fqsNaxcFDe = false;}
      if(rJNNknLeYd == true){rJNNknLeYd = false;}
      if(YpjUosANDt == true){YpjUosANDt = false;}
      if(KnwExpCDuJ == true){KnwExpCDuJ = false;}
      if(tUdjxaTWtk == true){tUdjxaTWtk = false;}
      if(BbnfApGYXh == true){BbnfApGYXh = false;}
      if(wPCIUDNJQt == true){wPCIUDNJQt = false;}
      if(kHjOiEMzWO == true){kHjOiEMzWO = false;}
      if(YcSRshzPDG == true){YcSRshzPDG = false;}
      if(idfMNdRUPt == true){idfMNdRUPt = false;}
      if(MKGzzsrZww == true){MKGzzsrZww = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLJUDWVNTR
{ 
  void yYkOIZXRzb()
  { 
      bool ROYobkhdTc = false;
      bool ozbtDDGEWo = false;
      bool uHWSPMAcdu = false;
      bool ftOwDoliQQ = false;
      bool dFEaYSNlEd = false;
      bool qtMrgJqGYO = false;
      bool jFAYwtjeqO = false;
      bool RWmFKoCwtw = false;
      bool zNYzDlhWPs = false;
      bool yfJCfYFfdd = false;
      bool hhuoLTGGgr = false;
      bool GtMbPVgAUK = false;
      bool LMPyPkNkZl = false;
      bool jVSPOQSinj = false;
      bool ebpXlETgmK = false;
      bool qELSSURxZa = false;
      bool GVgtHjawNy = false;
      bool CyMjfiWrLL = false;
      bool RfyOtfKAxs = false;
      bool zVIMdIuwPB = false;
      string eQrSOcHDUV;
      string TuEonYtbnZ;
      string mBdOWXIxkl;
      string wdKDrEEMLs;
      string HleIWmegSU;
      string LrOKjcmdup;
      string UJRhZojAxj;
      string TgQuSAWUri;
      string saeQaEOzTO;
      string QaQUXxTwig;
      string DdjhAdaTri;
      string FSlMxteAHV;
      string ZjghSsPwWU;
      string fZlKfOqwPw;
      string cuGjIyoEWd;
      string SToMHSwBPH;
      string OexXCfgafh;
      string ChkKsddwYU;
      string DKYrBMjYDN;
      string SogHgxyigc;
      if(eQrSOcHDUV == DdjhAdaTri){ROYobkhdTc = true;}
      else if(DdjhAdaTri == eQrSOcHDUV){hhuoLTGGgr = true;}
      if(TuEonYtbnZ == FSlMxteAHV){ozbtDDGEWo = true;}
      else if(FSlMxteAHV == TuEonYtbnZ){GtMbPVgAUK = true;}
      if(mBdOWXIxkl == ZjghSsPwWU){uHWSPMAcdu = true;}
      else if(ZjghSsPwWU == mBdOWXIxkl){LMPyPkNkZl = true;}
      if(wdKDrEEMLs == fZlKfOqwPw){ftOwDoliQQ = true;}
      else if(fZlKfOqwPw == wdKDrEEMLs){jVSPOQSinj = true;}
      if(HleIWmegSU == cuGjIyoEWd){dFEaYSNlEd = true;}
      else if(cuGjIyoEWd == HleIWmegSU){ebpXlETgmK = true;}
      if(LrOKjcmdup == SToMHSwBPH){qtMrgJqGYO = true;}
      else if(SToMHSwBPH == LrOKjcmdup){qELSSURxZa = true;}
      if(UJRhZojAxj == OexXCfgafh){jFAYwtjeqO = true;}
      else if(OexXCfgafh == UJRhZojAxj){GVgtHjawNy = true;}
      if(TgQuSAWUri == ChkKsddwYU){RWmFKoCwtw = true;}
      if(saeQaEOzTO == DKYrBMjYDN){zNYzDlhWPs = true;}
      if(QaQUXxTwig == SogHgxyigc){yfJCfYFfdd = true;}
      while(ChkKsddwYU == TgQuSAWUri){CyMjfiWrLL = true;}
      while(DKYrBMjYDN == DKYrBMjYDN){RfyOtfKAxs = true;}
      while(SogHgxyigc == SogHgxyigc){zVIMdIuwPB = true;}
      if(ROYobkhdTc == true){ROYobkhdTc = false;}
      if(ozbtDDGEWo == true){ozbtDDGEWo = false;}
      if(uHWSPMAcdu == true){uHWSPMAcdu = false;}
      if(ftOwDoliQQ == true){ftOwDoliQQ = false;}
      if(dFEaYSNlEd == true){dFEaYSNlEd = false;}
      if(qtMrgJqGYO == true){qtMrgJqGYO = false;}
      if(jFAYwtjeqO == true){jFAYwtjeqO = false;}
      if(RWmFKoCwtw == true){RWmFKoCwtw = false;}
      if(zNYzDlhWPs == true){zNYzDlhWPs = false;}
      if(yfJCfYFfdd == true){yfJCfYFfdd = false;}
      if(hhuoLTGGgr == true){hhuoLTGGgr = false;}
      if(GtMbPVgAUK == true){GtMbPVgAUK = false;}
      if(LMPyPkNkZl == true){LMPyPkNkZl = false;}
      if(jVSPOQSinj == true){jVSPOQSinj = false;}
      if(ebpXlETgmK == true){ebpXlETgmK = false;}
      if(qELSSURxZa == true){qELSSURxZa = false;}
      if(GVgtHjawNy == true){GVgtHjawNy = false;}
      if(CyMjfiWrLL == true){CyMjfiWrLL = false;}
      if(RfyOtfKAxs == true){RfyOtfKAxs = false;}
      if(zVIMdIuwPB == true){zVIMdIuwPB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LHVQOPQFFE
{ 
  void dxokcibWJf()
  { 
      bool WxwWpzbBhF = false;
      bool GCMItqTzVp = false;
      bool MPqAYXTcXz = false;
      bool xNDrCbZcOI = false;
      bool IFGRqdqMIf = false;
      bool WdCLFGFwxS = false;
      bool fzdhHryUFS = false;
      bool RqjNhGJYJu = false;
      bool fGUqcTLqmw = false;
      bool VdewcIbXKy = false;
      bool eWHoOesndy = false;
      bool xgmClZelEm = false;
      bool fHgIwnMnjY = false;
      bool elNKQJyecx = false;
      bool ZWNnzopbKD = false;
      bool dpSXRWpyrZ = false;
      bool SFEETKSbkc = false;
      bool azIHNIssJH = false;
      bool xjdgtnSprs = false;
      bool SzlDeTSITn = false;
      string SNVpZnqctC;
      string MAGfjHzpeo;
      string xKMIbChMxw;
      string yogYUrryrf;
      string LqbbNBYhZU;
      string fscDaIANOW;
      string GefxEWShKr;
      string PAxycFijtZ;
      string dAlbQFMdyM;
      string qeiUZgLdXq;
      string ipWhFeudaU;
      string ZQSorGrDgz;
      string KoiyAkQbYw;
      string sEMDqmcDWk;
      string JhCdmaLtbT;
      string nIxXgsHXhT;
      string NTEdaUEOyF;
      string cofupblFLZ;
      string YWzFHkHnWx;
      string fEVDXpdXCS;
      if(SNVpZnqctC == ipWhFeudaU){WxwWpzbBhF = true;}
      else if(ipWhFeudaU == SNVpZnqctC){eWHoOesndy = true;}
      if(MAGfjHzpeo == ZQSorGrDgz){GCMItqTzVp = true;}
      else if(ZQSorGrDgz == MAGfjHzpeo){xgmClZelEm = true;}
      if(xKMIbChMxw == KoiyAkQbYw){MPqAYXTcXz = true;}
      else if(KoiyAkQbYw == xKMIbChMxw){fHgIwnMnjY = true;}
      if(yogYUrryrf == sEMDqmcDWk){xNDrCbZcOI = true;}
      else if(sEMDqmcDWk == yogYUrryrf){elNKQJyecx = true;}
      if(LqbbNBYhZU == JhCdmaLtbT){IFGRqdqMIf = true;}
      else if(JhCdmaLtbT == LqbbNBYhZU){ZWNnzopbKD = true;}
      if(fscDaIANOW == nIxXgsHXhT){WdCLFGFwxS = true;}
      else if(nIxXgsHXhT == fscDaIANOW){dpSXRWpyrZ = true;}
      if(GefxEWShKr == NTEdaUEOyF){fzdhHryUFS = true;}
      else if(NTEdaUEOyF == GefxEWShKr){SFEETKSbkc = true;}
      if(PAxycFijtZ == cofupblFLZ){RqjNhGJYJu = true;}
      if(dAlbQFMdyM == YWzFHkHnWx){fGUqcTLqmw = true;}
      if(qeiUZgLdXq == fEVDXpdXCS){VdewcIbXKy = true;}
      while(cofupblFLZ == PAxycFijtZ){azIHNIssJH = true;}
      while(YWzFHkHnWx == YWzFHkHnWx){xjdgtnSprs = true;}
      while(fEVDXpdXCS == fEVDXpdXCS){SzlDeTSITn = true;}
      if(WxwWpzbBhF == true){WxwWpzbBhF = false;}
      if(GCMItqTzVp == true){GCMItqTzVp = false;}
      if(MPqAYXTcXz == true){MPqAYXTcXz = false;}
      if(xNDrCbZcOI == true){xNDrCbZcOI = false;}
      if(IFGRqdqMIf == true){IFGRqdqMIf = false;}
      if(WdCLFGFwxS == true){WdCLFGFwxS = false;}
      if(fzdhHryUFS == true){fzdhHryUFS = false;}
      if(RqjNhGJYJu == true){RqjNhGJYJu = false;}
      if(fGUqcTLqmw == true){fGUqcTLqmw = false;}
      if(VdewcIbXKy == true){VdewcIbXKy = false;}
      if(eWHoOesndy == true){eWHoOesndy = false;}
      if(xgmClZelEm == true){xgmClZelEm = false;}
      if(fHgIwnMnjY == true){fHgIwnMnjY = false;}
      if(elNKQJyecx == true){elNKQJyecx = false;}
      if(ZWNnzopbKD == true){ZWNnzopbKD = false;}
      if(dpSXRWpyrZ == true){dpSXRWpyrZ = false;}
      if(SFEETKSbkc == true){SFEETKSbkc = false;}
      if(azIHNIssJH == true){azIHNIssJH = false;}
      if(xjdgtnSprs == true){xjdgtnSprs = false;}
      if(SzlDeTSITn == true){SzlDeTSITn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOURTKXQKR
{ 
  void iAnrcNFFIg()
  { 
      bool sznlbxCISf = false;
      bool hhVcWaqQwl = false;
      bool jhaHowBshL = false;
      bool fHkKtJkkgl = false;
      bool dgKGPeoYgZ = false;
      bool zdiSjLYgwe = false;
      bool wIZGzawLhN = false;
      bool oFjKICXTqJ = false;
      bool HbMIMCXSZi = false;
      bool jEnBpUHDHo = false;
      bool icqSjttYKh = false;
      bool mEomXTwRtx = false;
      bool CdkzckQiUm = false;
      bool uUMCadksXS = false;
      bool IzIrueOBcV = false;
      bool YoIJlErqpy = false;
      bool cKEWlSrlLt = false;
      bool hDsboDVrDx = false;
      bool VOFyOFLCQV = false;
      bool ksCYoxukFc = false;
      string LfmkGzCGmk;
      string laRrNSLiMh;
      string TurhcspAjd;
      string xDBiRDZZrO;
      string YFkQkrUBVu;
      string GRQYMQmEIN;
      string JBWImhZiaK;
      string rkqyIOJbxj;
      string XnenXfmbVB;
      string QVRdFXhccC;
      string RlaLDUaSQy;
      string GKHXoUWhkH;
      string uxNYtWTMrk;
      string fgytRlMSkC;
      string EULWtFNtoj;
      string BzqVHUYBQf;
      string BOZfSZLNFD;
      string HDxiCalpen;
      string JZWIifocmx;
      string NLBEApueEU;
      if(LfmkGzCGmk == RlaLDUaSQy){sznlbxCISf = true;}
      else if(RlaLDUaSQy == LfmkGzCGmk){icqSjttYKh = true;}
      if(laRrNSLiMh == GKHXoUWhkH){hhVcWaqQwl = true;}
      else if(GKHXoUWhkH == laRrNSLiMh){mEomXTwRtx = true;}
      if(TurhcspAjd == uxNYtWTMrk){jhaHowBshL = true;}
      else if(uxNYtWTMrk == TurhcspAjd){CdkzckQiUm = true;}
      if(xDBiRDZZrO == fgytRlMSkC){fHkKtJkkgl = true;}
      else if(fgytRlMSkC == xDBiRDZZrO){uUMCadksXS = true;}
      if(YFkQkrUBVu == EULWtFNtoj){dgKGPeoYgZ = true;}
      else if(EULWtFNtoj == YFkQkrUBVu){IzIrueOBcV = true;}
      if(GRQYMQmEIN == BzqVHUYBQf){zdiSjLYgwe = true;}
      else if(BzqVHUYBQf == GRQYMQmEIN){YoIJlErqpy = true;}
      if(JBWImhZiaK == BOZfSZLNFD){wIZGzawLhN = true;}
      else if(BOZfSZLNFD == JBWImhZiaK){cKEWlSrlLt = true;}
      if(rkqyIOJbxj == HDxiCalpen){oFjKICXTqJ = true;}
      if(XnenXfmbVB == JZWIifocmx){HbMIMCXSZi = true;}
      if(QVRdFXhccC == NLBEApueEU){jEnBpUHDHo = true;}
      while(HDxiCalpen == rkqyIOJbxj){hDsboDVrDx = true;}
      while(JZWIifocmx == JZWIifocmx){VOFyOFLCQV = true;}
      while(NLBEApueEU == NLBEApueEU){ksCYoxukFc = true;}
      if(sznlbxCISf == true){sznlbxCISf = false;}
      if(hhVcWaqQwl == true){hhVcWaqQwl = false;}
      if(jhaHowBshL == true){jhaHowBshL = false;}
      if(fHkKtJkkgl == true){fHkKtJkkgl = false;}
      if(dgKGPeoYgZ == true){dgKGPeoYgZ = false;}
      if(zdiSjLYgwe == true){zdiSjLYgwe = false;}
      if(wIZGzawLhN == true){wIZGzawLhN = false;}
      if(oFjKICXTqJ == true){oFjKICXTqJ = false;}
      if(HbMIMCXSZi == true){HbMIMCXSZi = false;}
      if(jEnBpUHDHo == true){jEnBpUHDHo = false;}
      if(icqSjttYKh == true){icqSjttYKh = false;}
      if(mEomXTwRtx == true){mEomXTwRtx = false;}
      if(CdkzckQiUm == true){CdkzckQiUm = false;}
      if(uUMCadksXS == true){uUMCadksXS = false;}
      if(IzIrueOBcV == true){IzIrueOBcV = false;}
      if(YoIJlErqpy == true){YoIJlErqpy = false;}
      if(cKEWlSrlLt == true){cKEWlSrlLt = false;}
      if(hDsboDVrDx == true){hDsboDVrDx = false;}
      if(VOFyOFLCQV == true){VOFyOFLCQV = false;}
      if(ksCYoxukFc == true){ksCYoxukFc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJJYVIAYDF
{ 
  void DPYupanMel()
  { 
      bool ISpBsUkBjc = false;
      bool FKLakGGbTy = false;
      bool UYLEqbbhaE = false;
      bool YSpZFiItDH = false;
      bool esBGhySiaj = false;
      bool WIGGyjHkJQ = false;
      bool sDafDmUkUC = false;
      bool yMYMTaWEVs = false;
      bool IrHpgQLiaV = false;
      bool bWjlOaRVCu = false;
      bool dgNXkJjtlW = false;
      bool MCOQIAwkym = false;
      bool akKzaablxs = false;
      bool JABaPadiEW = false;
      bool fRwDIYHTdN = false;
      bool egXOTrWOxJ = false;
      bool hxwsNLAnAg = false;
      bool WNfaHJnHpB = false;
      bool THIjNbclGW = false;
      bool EPktoiUDow = false;
      string BHgkBpWHWs;
      string dsGbsfFeck;
      string rbKixClLIX;
      string xgUKmdgFPs;
      string FWfbDqRVmE;
      string mPDNeZxynz;
      string EKyywwYuoO;
      string zzOjeUuieG;
      string jPXEjhcGeM;
      string ghRQntYgfG;
      string RVgXEnBThK;
      string dNThOomsNO;
      string TRPbhQhyuk;
      string uNDXnOiAzw;
      string fJYUiSOjBz;
      string HeSRmzFEpm;
      string FDXxOPKusA;
      string GltRhKsusO;
      string CywwcPukjn;
      string IdKLqckaFT;
      if(BHgkBpWHWs == RVgXEnBThK){ISpBsUkBjc = true;}
      else if(RVgXEnBThK == BHgkBpWHWs){dgNXkJjtlW = true;}
      if(dsGbsfFeck == dNThOomsNO){FKLakGGbTy = true;}
      else if(dNThOomsNO == dsGbsfFeck){MCOQIAwkym = true;}
      if(rbKixClLIX == TRPbhQhyuk){UYLEqbbhaE = true;}
      else if(TRPbhQhyuk == rbKixClLIX){akKzaablxs = true;}
      if(xgUKmdgFPs == uNDXnOiAzw){YSpZFiItDH = true;}
      else if(uNDXnOiAzw == xgUKmdgFPs){JABaPadiEW = true;}
      if(FWfbDqRVmE == fJYUiSOjBz){esBGhySiaj = true;}
      else if(fJYUiSOjBz == FWfbDqRVmE){fRwDIYHTdN = true;}
      if(mPDNeZxynz == HeSRmzFEpm){WIGGyjHkJQ = true;}
      else if(HeSRmzFEpm == mPDNeZxynz){egXOTrWOxJ = true;}
      if(EKyywwYuoO == FDXxOPKusA){sDafDmUkUC = true;}
      else if(FDXxOPKusA == EKyywwYuoO){hxwsNLAnAg = true;}
      if(zzOjeUuieG == GltRhKsusO){yMYMTaWEVs = true;}
      if(jPXEjhcGeM == CywwcPukjn){IrHpgQLiaV = true;}
      if(ghRQntYgfG == IdKLqckaFT){bWjlOaRVCu = true;}
      while(GltRhKsusO == zzOjeUuieG){WNfaHJnHpB = true;}
      while(CywwcPukjn == CywwcPukjn){THIjNbclGW = true;}
      while(IdKLqckaFT == IdKLqckaFT){EPktoiUDow = true;}
      if(ISpBsUkBjc == true){ISpBsUkBjc = false;}
      if(FKLakGGbTy == true){FKLakGGbTy = false;}
      if(UYLEqbbhaE == true){UYLEqbbhaE = false;}
      if(YSpZFiItDH == true){YSpZFiItDH = false;}
      if(esBGhySiaj == true){esBGhySiaj = false;}
      if(WIGGyjHkJQ == true){WIGGyjHkJQ = false;}
      if(sDafDmUkUC == true){sDafDmUkUC = false;}
      if(yMYMTaWEVs == true){yMYMTaWEVs = false;}
      if(IrHpgQLiaV == true){IrHpgQLiaV = false;}
      if(bWjlOaRVCu == true){bWjlOaRVCu = false;}
      if(dgNXkJjtlW == true){dgNXkJjtlW = false;}
      if(MCOQIAwkym == true){MCOQIAwkym = false;}
      if(akKzaablxs == true){akKzaablxs = false;}
      if(JABaPadiEW == true){JABaPadiEW = false;}
      if(fRwDIYHTdN == true){fRwDIYHTdN = false;}
      if(egXOTrWOxJ == true){egXOTrWOxJ = false;}
      if(hxwsNLAnAg == true){hxwsNLAnAg = false;}
      if(WNfaHJnHpB == true){WNfaHJnHpB = false;}
      if(THIjNbclGW == true){THIjNbclGW = false;}
      if(EPktoiUDow == true){EPktoiUDow = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCIXVCKIQW
{ 
  void khgabZPNci()
  { 
      bool ADmZeALJAP = false;
      bool VIpViIHlzG = false;
      bool fEXbJuYSDX = false;
      bool OPsYMYUcIP = false;
      bool rMslEnQtSF = false;
      bool YgsNgufLQi = false;
      bool asGbAFPQJJ = false;
      bool neciNTLlWU = false;
      bool eeAxzhVfrQ = false;
      bool sJMZozFQkz = false;
      bool YAjIQsDKzM = false;
      bool jsnuEwsIcR = false;
      bool ijYrQeRDtO = false;
      bool NtAXudtqfF = false;
      bool eLfegzUQUr = false;
      bool GxnTPoarrl = false;
      bool bzPkzorPAZ = false;
      bool BBbXmWEsKQ = false;
      bool JBiCIQGgHG = false;
      bool DCztdfwtfq = false;
      string UnVHbIWZwO;
      string CftJAKBJMo;
      string hsoVyRIrJD;
      string chiZrtBGRU;
      string HfTnuuiuAb;
      string InoDxayzJJ;
      string zeQslUxTRG;
      string ItrqhBZBZC;
      string iMrgtnrebQ;
      string uCxHUbPaCa;
      string xOdsSOwxVw;
      string BxYHalmiyx;
      string cSrBKGxjWF;
      string kyyzETiyOf;
      string rtJePycogh;
      string ogbFyeVbhM;
      string QLaPKCyYCG;
      string DoUSEhJNlM;
      string cHDnQEVsBZ;
      string xHPBOgSsTM;
      if(UnVHbIWZwO == xOdsSOwxVw){ADmZeALJAP = true;}
      else if(xOdsSOwxVw == UnVHbIWZwO){YAjIQsDKzM = true;}
      if(CftJAKBJMo == BxYHalmiyx){VIpViIHlzG = true;}
      else if(BxYHalmiyx == CftJAKBJMo){jsnuEwsIcR = true;}
      if(hsoVyRIrJD == cSrBKGxjWF){fEXbJuYSDX = true;}
      else if(cSrBKGxjWF == hsoVyRIrJD){ijYrQeRDtO = true;}
      if(chiZrtBGRU == kyyzETiyOf){OPsYMYUcIP = true;}
      else if(kyyzETiyOf == chiZrtBGRU){NtAXudtqfF = true;}
      if(HfTnuuiuAb == rtJePycogh){rMslEnQtSF = true;}
      else if(rtJePycogh == HfTnuuiuAb){eLfegzUQUr = true;}
      if(InoDxayzJJ == ogbFyeVbhM){YgsNgufLQi = true;}
      else if(ogbFyeVbhM == InoDxayzJJ){GxnTPoarrl = true;}
      if(zeQslUxTRG == QLaPKCyYCG){asGbAFPQJJ = true;}
      else if(QLaPKCyYCG == zeQslUxTRG){bzPkzorPAZ = true;}
      if(ItrqhBZBZC == DoUSEhJNlM){neciNTLlWU = true;}
      if(iMrgtnrebQ == cHDnQEVsBZ){eeAxzhVfrQ = true;}
      if(uCxHUbPaCa == xHPBOgSsTM){sJMZozFQkz = true;}
      while(DoUSEhJNlM == ItrqhBZBZC){BBbXmWEsKQ = true;}
      while(cHDnQEVsBZ == cHDnQEVsBZ){JBiCIQGgHG = true;}
      while(xHPBOgSsTM == xHPBOgSsTM){DCztdfwtfq = true;}
      if(ADmZeALJAP == true){ADmZeALJAP = false;}
      if(VIpViIHlzG == true){VIpViIHlzG = false;}
      if(fEXbJuYSDX == true){fEXbJuYSDX = false;}
      if(OPsYMYUcIP == true){OPsYMYUcIP = false;}
      if(rMslEnQtSF == true){rMslEnQtSF = false;}
      if(YgsNgufLQi == true){YgsNgufLQi = false;}
      if(asGbAFPQJJ == true){asGbAFPQJJ = false;}
      if(neciNTLlWU == true){neciNTLlWU = false;}
      if(eeAxzhVfrQ == true){eeAxzhVfrQ = false;}
      if(sJMZozFQkz == true){sJMZozFQkz = false;}
      if(YAjIQsDKzM == true){YAjIQsDKzM = false;}
      if(jsnuEwsIcR == true){jsnuEwsIcR = false;}
      if(ijYrQeRDtO == true){ijYrQeRDtO = false;}
      if(NtAXudtqfF == true){NtAXudtqfF = false;}
      if(eLfegzUQUr == true){eLfegzUQUr = false;}
      if(GxnTPoarrl == true){GxnTPoarrl = false;}
      if(bzPkzorPAZ == true){bzPkzorPAZ = false;}
      if(BBbXmWEsKQ == true){BBbXmWEsKQ = false;}
      if(JBiCIQGgHG == true){JBiCIQGgHG = false;}
      if(DCztdfwtfq == true){DCztdfwtfq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKWGREFMVM
{ 
  void azFWThFBlJ()
  { 
      bool YGtyyKiTDJ = false;
      bool pGjiuonwhn = false;
      bool SZirZbwgZz = false;
      bool sONqlZYkdq = false;
      bool ayrmNWfAGY = false;
      bool bMLezyXBYW = false;
      bool OCtEParsxV = false;
      bool QCRqMThueC = false;
      bool uuZAXgDhrm = false;
      bool CWMHcXEnWl = false;
      bool emDjHYtUSe = false;
      bool QbWVaScsgi = false;
      bool XJAJTspKNn = false;
      bool PtYsXHrosz = false;
      bool liPNWZzpfJ = false;
      bool uKGnNUmsQO = false;
      bool hjGeOWCdxS = false;
      bool amAgwotmms = false;
      bool tzdErEmkeC = false;
      bool UyYdQCckyz = false;
      string KbFHMMFwyK;
      string nXbmqMUAZe;
      string bIELVnsSKz;
      string LdcgODUYtM;
      string mRQTGgicnl;
      string MPEUlCWtlY;
      string SmlyyJuuXn;
      string ruGNrJrjFn;
      string EPdXmwYHuM;
      string gamUtzfRVw;
      string lnFAtQIqcb;
      string KlnxTDJNKC;
      string jmALGRIkSr;
      string dZOICQKddW;
      string mgeSCuloBq;
      string pSHSMynstb;
      string IXYjyjWeuC;
      string rfinOCIhJK;
      string fSjbCKRwwD;
      string cQiCNPItTR;
      if(KbFHMMFwyK == lnFAtQIqcb){YGtyyKiTDJ = true;}
      else if(lnFAtQIqcb == KbFHMMFwyK){emDjHYtUSe = true;}
      if(nXbmqMUAZe == KlnxTDJNKC){pGjiuonwhn = true;}
      else if(KlnxTDJNKC == nXbmqMUAZe){QbWVaScsgi = true;}
      if(bIELVnsSKz == jmALGRIkSr){SZirZbwgZz = true;}
      else if(jmALGRIkSr == bIELVnsSKz){XJAJTspKNn = true;}
      if(LdcgODUYtM == dZOICQKddW){sONqlZYkdq = true;}
      else if(dZOICQKddW == LdcgODUYtM){PtYsXHrosz = true;}
      if(mRQTGgicnl == mgeSCuloBq){ayrmNWfAGY = true;}
      else if(mgeSCuloBq == mRQTGgicnl){liPNWZzpfJ = true;}
      if(MPEUlCWtlY == pSHSMynstb){bMLezyXBYW = true;}
      else if(pSHSMynstb == MPEUlCWtlY){uKGnNUmsQO = true;}
      if(SmlyyJuuXn == IXYjyjWeuC){OCtEParsxV = true;}
      else if(IXYjyjWeuC == SmlyyJuuXn){hjGeOWCdxS = true;}
      if(ruGNrJrjFn == rfinOCIhJK){QCRqMThueC = true;}
      if(EPdXmwYHuM == fSjbCKRwwD){uuZAXgDhrm = true;}
      if(gamUtzfRVw == cQiCNPItTR){CWMHcXEnWl = true;}
      while(rfinOCIhJK == ruGNrJrjFn){amAgwotmms = true;}
      while(fSjbCKRwwD == fSjbCKRwwD){tzdErEmkeC = true;}
      while(cQiCNPItTR == cQiCNPItTR){UyYdQCckyz = true;}
      if(YGtyyKiTDJ == true){YGtyyKiTDJ = false;}
      if(pGjiuonwhn == true){pGjiuonwhn = false;}
      if(SZirZbwgZz == true){SZirZbwgZz = false;}
      if(sONqlZYkdq == true){sONqlZYkdq = false;}
      if(ayrmNWfAGY == true){ayrmNWfAGY = false;}
      if(bMLezyXBYW == true){bMLezyXBYW = false;}
      if(OCtEParsxV == true){OCtEParsxV = false;}
      if(QCRqMThueC == true){QCRqMThueC = false;}
      if(uuZAXgDhrm == true){uuZAXgDhrm = false;}
      if(CWMHcXEnWl == true){CWMHcXEnWl = false;}
      if(emDjHYtUSe == true){emDjHYtUSe = false;}
      if(QbWVaScsgi == true){QbWVaScsgi = false;}
      if(XJAJTspKNn == true){XJAJTspKNn = false;}
      if(PtYsXHrosz == true){PtYsXHrosz = false;}
      if(liPNWZzpfJ == true){liPNWZzpfJ = false;}
      if(uKGnNUmsQO == true){uKGnNUmsQO = false;}
      if(hjGeOWCdxS == true){hjGeOWCdxS = false;}
      if(amAgwotmms == true){amAgwotmms = false;}
      if(tzdErEmkeC == true){tzdErEmkeC = false;}
      if(UyYdQCckyz == true){UyYdQCckyz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOIXUAVEHK
{ 
  void agENsrENCd()
  { 
      bool LZLIuGEtBc = false;
      bool kWBGYEnszN = false;
      bool LwYeThbecO = false;
      bool xZPNznHFLm = false;
      bool ElZiVVeMOg = false;
      bool hOntLPAgoM = false;
      bool eYRleLGnGk = false;
      bool whhLIYVoIx = false;
      bool DPQwfilUBj = false;
      bool nZQyIfUnDK = false;
      bool OpFdjAfbkl = false;
      bool sKXqIOIVFw = false;
      bool YklVwWQiDc = false;
      bool EhkyiNJlLf = false;
      bool DJiPqcCZps = false;
      bool WzhHkcDigM = false;
      bool ixXIhKYYIu = false;
      bool EWJYsPCWeT = false;
      bool TqsKFEzdNF = false;
      bool JaEzxFlagf = false;
      string GazpuoLDya;
      string lFXuljbHup;
      string FIdaDNxgTi;
      string EzonuTRYCk;
      string MDqThHenge;
      string oraSFywYlg;
      string rejOWlPjzS;
      string SCEJdBQKrw;
      string hIzntMYVhx;
      string WsmUsgTcww;
      string quoOMlmQoD;
      string glgpzifuUK;
      string NsBBwZPjQw;
      string gnNuElTkbH;
      string YHgdQjLxUJ;
      string BXHliytmRm;
      string WCAsWrXlkM;
      string OtTNkFMWkL;
      string NSOGtJgbMG;
      string rfSnkVHmHX;
      if(GazpuoLDya == quoOMlmQoD){LZLIuGEtBc = true;}
      else if(quoOMlmQoD == GazpuoLDya){OpFdjAfbkl = true;}
      if(lFXuljbHup == glgpzifuUK){kWBGYEnszN = true;}
      else if(glgpzifuUK == lFXuljbHup){sKXqIOIVFw = true;}
      if(FIdaDNxgTi == NsBBwZPjQw){LwYeThbecO = true;}
      else if(NsBBwZPjQw == FIdaDNxgTi){YklVwWQiDc = true;}
      if(EzonuTRYCk == gnNuElTkbH){xZPNznHFLm = true;}
      else if(gnNuElTkbH == EzonuTRYCk){EhkyiNJlLf = true;}
      if(MDqThHenge == YHgdQjLxUJ){ElZiVVeMOg = true;}
      else if(YHgdQjLxUJ == MDqThHenge){DJiPqcCZps = true;}
      if(oraSFywYlg == BXHliytmRm){hOntLPAgoM = true;}
      else if(BXHliytmRm == oraSFywYlg){WzhHkcDigM = true;}
      if(rejOWlPjzS == WCAsWrXlkM){eYRleLGnGk = true;}
      else if(WCAsWrXlkM == rejOWlPjzS){ixXIhKYYIu = true;}
      if(SCEJdBQKrw == OtTNkFMWkL){whhLIYVoIx = true;}
      if(hIzntMYVhx == NSOGtJgbMG){DPQwfilUBj = true;}
      if(WsmUsgTcww == rfSnkVHmHX){nZQyIfUnDK = true;}
      while(OtTNkFMWkL == SCEJdBQKrw){EWJYsPCWeT = true;}
      while(NSOGtJgbMG == NSOGtJgbMG){TqsKFEzdNF = true;}
      while(rfSnkVHmHX == rfSnkVHmHX){JaEzxFlagf = true;}
      if(LZLIuGEtBc == true){LZLIuGEtBc = false;}
      if(kWBGYEnszN == true){kWBGYEnszN = false;}
      if(LwYeThbecO == true){LwYeThbecO = false;}
      if(xZPNznHFLm == true){xZPNznHFLm = false;}
      if(ElZiVVeMOg == true){ElZiVVeMOg = false;}
      if(hOntLPAgoM == true){hOntLPAgoM = false;}
      if(eYRleLGnGk == true){eYRleLGnGk = false;}
      if(whhLIYVoIx == true){whhLIYVoIx = false;}
      if(DPQwfilUBj == true){DPQwfilUBj = false;}
      if(nZQyIfUnDK == true){nZQyIfUnDK = false;}
      if(OpFdjAfbkl == true){OpFdjAfbkl = false;}
      if(sKXqIOIVFw == true){sKXqIOIVFw = false;}
      if(YklVwWQiDc == true){YklVwWQiDc = false;}
      if(EhkyiNJlLf == true){EhkyiNJlLf = false;}
      if(DJiPqcCZps == true){DJiPqcCZps = false;}
      if(WzhHkcDigM == true){WzhHkcDigM = false;}
      if(ixXIhKYYIu == true){ixXIhKYYIu = false;}
      if(EWJYsPCWeT == true){EWJYsPCWeT = false;}
      if(TqsKFEzdNF == true){TqsKFEzdNF = false;}
      if(JaEzxFlagf == true){JaEzxFlagf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BNZLLGSQOW
{ 
  void zzqBgtohHB()
  { 
      bool bgMnWoOHbX = false;
      bool ZoSzsuXner = false;
      bool ZzfMeNCzCW = false;
      bool SWpIhEBRek = false;
      bool iCRLdtuTqa = false;
      bool KuVhCbBzJJ = false;
      bool lOEFFDyKRo = false;
      bool tFJsIWhTij = false;
      bool ShIaMXAIFF = false;
      bool DBIVzTxMGZ = false;
      bool ujCCgFlbYf = false;
      bool tgQYpEGcsh = false;
      bool CpFLkrxnto = false;
      bool YVNInhfGtG = false;
      bool lYjZLVjieu = false;
      bool NTTYXFepQo = false;
      bool HygiGXTIjI = false;
      bool XAilwdGfzP = false;
      bool HNIzbFBoki = false;
      bool CooFymqASn = false;
      string FqRdRZCgOV;
      string JQTXNdfwLd;
      string aDsWhpHhCY;
      string DKnlnoUrgN;
      string fdaREERlNX;
      string pDqoiBxtwa;
      string RTeoRybhjX;
      string JnPxxwbbRc;
      string XVTdiATyCl;
      string qZwFuLzlzG;
      string bjCpOCmsqm;
      string ZVbSCwAAFR;
      string ddexfirJBl;
      string xpbLBnTdPg;
      string MaGPMVxcDz;
      string LzfhbxEEJe;
      string KdqFpitQQO;
      string cWjYFDXPkJ;
      string lOGCaxJtjE;
      string iOTjWhjAZc;
      if(FqRdRZCgOV == bjCpOCmsqm){bgMnWoOHbX = true;}
      else if(bjCpOCmsqm == FqRdRZCgOV){ujCCgFlbYf = true;}
      if(JQTXNdfwLd == ZVbSCwAAFR){ZoSzsuXner = true;}
      else if(ZVbSCwAAFR == JQTXNdfwLd){tgQYpEGcsh = true;}
      if(aDsWhpHhCY == ddexfirJBl){ZzfMeNCzCW = true;}
      else if(ddexfirJBl == aDsWhpHhCY){CpFLkrxnto = true;}
      if(DKnlnoUrgN == xpbLBnTdPg){SWpIhEBRek = true;}
      else if(xpbLBnTdPg == DKnlnoUrgN){YVNInhfGtG = true;}
      if(fdaREERlNX == MaGPMVxcDz){iCRLdtuTqa = true;}
      else if(MaGPMVxcDz == fdaREERlNX){lYjZLVjieu = true;}
      if(pDqoiBxtwa == LzfhbxEEJe){KuVhCbBzJJ = true;}
      else if(LzfhbxEEJe == pDqoiBxtwa){NTTYXFepQo = true;}
      if(RTeoRybhjX == KdqFpitQQO){lOEFFDyKRo = true;}
      else if(KdqFpitQQO == RTeoRybhjX){HygiGXTIjI = true;}
      if(JnPxxwbbRc == cWjYFDXPkJ){tFJsIWhTij = true;}
      if(XVTdiATyCl == lOGCaxJtjE){ShIaMXAIFF = true;}
      if(qZwFuLzlzG == iOTjWhjAZc){DBIVzTxMGZ = true;}
      while(cWjYFDXPkJ == JnPxxwbbRc){XAilwdGfzP = true;}
      while(lOGCaxJtjE == lOGCaxJtjE){HNIzbFBoki = true;}
      while(iOTjWhjAZc == iOTjWhjAZc){CooFymqASn = true;}
      if(bgMnWoOHbX == true){bgMnWoOHbX = false;}
      if(ZoSzsuXner == true){ZoSzsuXner = false;}
      if(ZzfMeNCzCW == true){ZzfMeNCzCW = false;}
      if(SWpIhEBRek == true){SWpIhEBRek = false;}
      if(iCRLdtuTqa == true){iCRLdtuTqa = false;}
      if(KuVhCbBzJJ == true){KuVhCbBzJJ = false;}
      if(lOEFFDyKRo == true){lOEFFDyKRo = false;}
      if(tFJsIWhTij == true){tFJsIWhTij = false;}
      if(ShIaMXAIFF == true){ShIaMXAIFF = false;}
      if(DBIVzTxMGZ == true){DBIVzTxMGZ = false;}
      if(ujCCgFlbYf == true){ujCCgFlbYf = false;}
      if(tgQYpEGcsh == true){tgQYpEGcsh = false;}
      if(CpFLkrxnto == true){CpFLkrxnto = false;}
      if(YVNInhfGtG == true){YVNInhfGtG = false;}
      if(lYjZLVjieu == true){lYjZLVjieu = false;}
      if(NTTYXFepQo == true){NTTYXFepQo = false;}
      if(HygiGXTIjI == true){HygiGXTIjI = false;}
      if(XAilwdGfzP == true){XAilwdGfzP = false;}
      if(HNIzbFBoki == true){HNIzbFBoki = false;}
      if(CooFymqASn == true){CooFymqASn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWWXSSRYAX
{ 
  void fKXBbdQgYG()
  { 
      bool JsSHqeMFuE = false;
      bool EbETQzxhYb = false;
      bool atFwSnVAaX = false;
      bool YEEnQSdIBO = false;
      bool tjerPGtefC = false;
      bool TaLOYOmVoD = false;
      bool ILeWfzWPDy = false;
      bool UogKhqPNfM = false;
      bool spTXExspOB = false;
      bool eISyGhEHMQ = false;
      bool iebhgdsBfh = false;
      bool zZobJRqGSh = false;
      bool GfACSMViEz = false;
      bool lHAPcOOlpZ = false;
      bool DqJgBETqon = false;
      bool qyoeKCdZOU = false;
      bool IKxgurZZyt = false;
      bool DFPrdOVSBN = false;
      bool sdtPInSVFa = false;
      bool koWVRstclI = false;
      string NuSuAjDWCe;
      string VyYoPsAPVZ;
      string RrCuIrIAlA;
      string uSlbbCEDYl;
      string RSKnHDrOJZ;
      string ZdiUAUsXmI;
      string aDjBjCMxNM;
      string nwpiHzgOmF;
      string AtpLaQjRaG;
      string IfQQLNhJDE;
      string ptBxkcmzMA;
      string nekgHfNXaS;
      string SuVHDHfZXs;
      string QXKhPGsray;
      string dkEaRduiJe;
      string AJhjluXtsc;
      string wNaSiQUCQB;
      string mUxcohpuoZ;
      string MwPssGoZwU;
      string hzzxBQJkqA;
      if(NuSuAjDWCe == ptBxkcmzMA){JsSHqeMFuE = true;}
      else if(ptBxkcmzMA == NuSuAjDWCe){iebhgdsBfh = true;}
      if(VyYoPsAPVZ == nekgHfNXaS){EbETQzxhYb = true;}
      else if(nekgHfNXaS == VyYoPsAPVZ){zZobJRqGSh = true;}
      if(RrCuIrIAlA == SuVHDHfZXs){atFwSnVAaX = true;}
      else if(SuVHDHfZXs == RrCuIrIAlA){GfACSMViEz = true;}
      if(uSlbbCEDYl == QXKhPGsray){YEEnQSdIBO = true;}
      else if(QXKhPGsray == uSlbbCEDYl){lHAPcOOlpZ = true;}
      if(RSKnHDrOJZ == dkEaRduiJe){tjerPGtefC = true;}
      else if(dkEaRduiJe == RSKnHDrOJZ){DqJgBETqon = true;}
      if(ZdiUAUsXmI == AJhjluXtsc){TaLOYOmVoD = true;}
      else if(AJhjluXtsc == ZdiUAUsXmI){qyoeKCdZOU = true;}
      if(aDjBjCMxNM == wNaSiQUCQB){ILeWfzWPDy = true;}
      else if(wNaSiQUCQB == aDjBjCMxNM){IKxgurZZyt = true;}
      if(nwpiHzgOmF == mUxcohpuoZ){UogKhqPNfM = true;}
      if(AtpLaQjRaG == MwPssGoZwU){spTXExspOB = true;}
      if(IfQQLNhJDE == hzzxBQJkqA){eISyGhEHMQ = true;}
      while(mUxcohpuoZ == nwpiHzgOmF){DFPrdOVSBN = true;}
      while(MwPssGoZwU == MwPssGoZwU){sdtPInSVFa = true;}
      while(hzzxBQJkqA == hzzxBQJkqA){koWVRstclI = true;}
      if(JsSHqeMFuE == true){JsSHqeMFuE = false;}
      if(EbETQzxhYb == true){EbETQzxhYb = false;}
      if(atFwSnVAaX == true){atFwSnVAaX = false;}
      if(YEEnQSdIBO == true){YEEnQSdIBO = false;}
      if(tjerPGtefC == true){tjerPGtefC = false;}
      if(TaLOYOmVoD == true){TaLOYOmVoD = false;}
      if(ILeWfzWPDy == true){ILeWfzWPDy = false;}
      if(UogKhqPNfM == true){UogKhqPNfM = false;}
      if(spTXExspOB == true){spTXExspOB = false;}
      if(eISyGhEHMQ == true){eISyGhEHMQ = false;}
      if(iebhgdsBfh == true){iebhgdsBfh = false;}
      if(zZobJRqGSh == true){zZobJRqGSh = false;}
      if(GfACSMViEz == true){GfACSMViEz = false;}
      if(lHAPcOOlpZ == true){lHAPcOOlpZ = false;}
      if(DqJgBETqon == true){DqJgBETqon = false;}
      if(qyoeKCdZOU == true){qyoeKCdZOU = false;}
      if(IKxgurZZyt == true){IKxgurZZyt = false;}
      if(DFPrdOVSBN == true){DFPrdOVSBN = false;}
      if(sdtPInSVFa == true){sdtPInSVFa = false;}
      if(koWVRstclI == true){koWVRstclI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTHKDATCSD
{ 
  void CPsptTeodY()
  { 
      bool ISpfZZrNcM = false;
      bool TiHiUwZnLI = false;
      bool GxbuLCbSPM = false;
      bool nxAWsMSyzt = false;
      bool uyEPNLAdiX = false;
      bool dqArBKquTX = false;
      bool xYxPYWijoI = false;
      bool cboRNIrMgA = false;
      bool ByjrhxwHVi = false;
      bool UXeawVAnpq = false;
      bool cPoatCBhes = false;
      bool ReNTVzoFha = false;
      bool ZaOGmFxNUq = false;
      bool HEVpWlJIxe = false;
      bool wObcQpJLFx = false;
      bool guGPRBBimo = false;
      bool FmNnkNJXwi = false;
      bool pfHCeKzkow = false;
      bool ulIXJLxFYV = false;
      bool kaUHZIBnqC = false;
      string rdnAwbugny;
      string OJfFjlMRes;
      string RwZYZtjkxV;
      string rlCkyzzfaf;
      string KYbbVleyLp;
      string NMVwpwEPaC;
      string qKiSGcHtGk;
      string mgpyhrTxCn;
      string PlYHHePGuC;
      string ujEYoApJVs;
      string djqaDgVWNx;
      string bGMllElaKa;
      string MBzEpCbQJh;
      string BKbIJetxEZ;
      string JsrxZnWSmj;
      string NOytgcklkA;
      string FENfwReDbG;
      string KnWkRTJBeC;
      string eJdYTmLgbg;
      string tHMDUEeLBH;
      if(rdnAwbugny == djqaDgVWNx){ISpfZZrNcM = true;}
      else if(djqaDgVWNx == rdnAwbugny){cPoatCBhes = true;}
      if(OJfFjlMRes == bGMllElaKa){TiHiUwZnLI = true;}
      else if(bGMllElaKa == OJfFjlMRes){ReNTVzoFha = true;}
      if(RwZYZtjkxV == MBzEpCbQJh){GxbuLCbSPM = true;}
      else if(MBzEpCbQJh == RwZYZtjkxV){ZaOGmFxNUq = true;}
      if(rlCkyzzfaf == BKbIJetxEZ){nxAWsMSyzt = true;}
      else if(BKbIJetxEZ == rlCkyzzfaf){HEVpWlJIxe = true;}
      if(KYbbVleyLp == JsrxZnWSmj){uyEPNLAdiX = true;}
      else if(JsrxZnWSmj == KYbbVleyLp){wObcQpJLFx = true;}
      if(NMVwpwEPaC == NOytgcklkA){dqArBKquTX = true;}
      else if(NOytgcklkA == NMVwpwEPaC){guGPRBBimo = true;}
      if(qKiSGcHtGk == FENfwReDbG){xYxPYWijoI = true;}
      else if(FENfwReDbG == qKiSGcHtGk){FmNnkNJXwi = true;}
      if(mgpyhrTxCn == KnWkRTJBeC){cboRNIrMgA = true;}
      if(PlYHHePGuC == eJdYTmLgbg){ByjrhxwHVi = true;}
      if(ujEYoApJVs == tHMDUEeLBH){UXeawVAnpq = true;}
      while(KnWkRTJBeC == mgpyhrTxCn){pfHCeKzkow = true;}
      while(eJdYTmLgbg == eJdYTmLgbg){ulIXJLxFYV = true;}
      while(tHMDUEeLBH == tHMDUEeLBH){kaUHZIBnqC = true;}
      if(ISpfZZrNcM == true){ISpfZZrNcM = false;}
      if(TiHiUwZnLI == true){TiHiUwZnLI = false;}
      if(GxbuLCbSPM == true){GxbuLCbSPM = false;}
      if(nxAWsMSyzt == true){nxAWsMSyzt = false;}
      if(uyEPNLAdiX == true){uyEPNLAdiX = false;}
      if(dqArBKquTX == true){dqArBKquTX = false;}
      if(xYxPYWijoI == true){xYxPYWijoI = false;}
      if(cboRNIrMgA == true){cboRNIrMgA = false;}
      if(ByjrhxwHVi == true){ByjrhxwHVi = false;}
      if(UXeawVAnpq == true){UXeawVAnpq = false;}
      if(cPoatCBhes == true){cPoatCBhes = false;}
      if(ReNTVzoFha == true){ReNTVzoFha = false;}
      if(ZaOGmFxNUq == true){ZaOGmFxNUq = false;}
      if(HEVpWlJIxe == true){HEVpWlJIxe = false;}
      if(wObcQpJLFx == true){wObcQpJLFx = false;}
      if(guGPRBBimo == true){guGPRBBimo = false;}
      if(FmNnkNJXwi == true){FmNnkNJXwi = false;}
      if(pfHCeKzkow == true){pfHCeKzkow = false;}
      if(ulIXJLxFYV == true){ulIXJLxFYV = false;}
      if(kaUHZIBnqC == true){kaUHZIBnqC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSNHZDBYKX
{ 
  void BDozhfUjqU()
  { 
      bool pcQVuxfdGC = false;
      bool wsMcBqHKhw = false;
      bool ScQrpTjgEr = false;
      bool RatissqTnd = false;
      bool SlJKIGHtdT = false;
      bool WPURNNLXeb = false;
      bool NyYNjUzdiH = false;
      bool AmVDdfTFij = false;
      bool MoCkVCFbVf = false;
      bool hSnLQTNuam = false;
      bool HcKWSjsRng = false;
      bool sFnuPXwnrh = false;
      bool PWHDZgyKmJ = false;
      bool SXeuciefSk = false;
      bool Jmnnlbdswr = false;
      bool WYDrXjVHwk = false;
      bool kiedOVZrRg = false;
      bool sQVGYbiSRx = false;
      bool DENtlsTlXr = false;
      bool MWigAZIJZP = false;
      string keHnVnjGaN;
      string SWDZKPibre;
      string nKYIMHAegS;
      string kbZmkYrTTH;
      string BkdEuOjwQZ;
      string kIxUpaFzbO;
      string nFZIbpxPok;
      string WOHkcDfUMx;
      string WDOHgceFxJ;
      string TsrESwLUbF;
      string RUHeCVALqm;
      string tkldrjqRaz;
      string LqSeRdWCRg;
      string qKrHfBwiEK;
      string bTNJPhHOMi;
      string EstctZBbMY;
      string zxsKuirdxp;
      string mHNPWrdIPi;
      string WHpibyQPNF;
      string zTWfLdZDOf;
      if(keHnVnjGaN == RUHeCVALqm){pcQVuxfdGC = true;}
      else if(RUHeCVALqm == keHnVnjGaN){HcKWSjsRng = true;}
      if(SWDZKPibre == tkldrjqRaz){wsMcBqHKhw = true;}
      else if(tkldrjqRaz == SWDZKPibre){sFnuPXwnrh = true;}
      if(nKYIMHAegS == LqSeRdWCRg){ScQrpTjgEr = true;}
      else if(LqSeRdWCRg == nKYIMHAegS){PWHDZgyKmJ = true;}
      if(kbZmkYrTTH == qKrHfBwiEK){RatissqTnd = true;}
      else if(qKrHfBwiEK == kbZmkYrTTH){SXeuciefSk = true;}
      if(BkdEuOjwQZ == bTNJPhHOMi){SlJKIGHtdT = true;}
      else if(bTNJPhHOMi == BkdEuOjwQZ){Jmnnlbdswr = true;}
      if(kIxUpaFzbO == EstctZBbMY){WPURNNLXeb = true;}
      else if(EstctZBbMY == kIxUpaFzbO){WYDrXjVHwk = true;}
      if(nFZIbpxPok == zxsKuirdxp){NyYNjUzdiH = true;}
      else if(zxsKuirdxp == nFZIbpxPok){kiedOVZrRg = true;}
      if(WOHkcDfUMx == mHNPWrdIPi){AmVDdfTFij = true;}
      if(WDOHgceFxJ == WHpibyQPNF){MoCkVCFbVf = true;}
      if(TsrESwLUbF == zTWfLdZDOf){hSnLQTNuam = true;}
      while(mHNPWrdIPi == WOHkcDfUMx){sQVGYbiSRx = true;}
      while(WHpibyQPNF == WHpibyQPNF){DENtlsTlXr = true;}
      while(zTWfLdZDOf == zTWfLdZDOf){MWigAZIJZP = true;}
      if(pcQVuxfdGC == true){pcQVuxfdGC = false;}
      if(wsMcBqHKhw == true){wsMcBqHKhw = false;}
      if(ScQrpTjgEr == true){ScQrpTjgEr = false;}
      if(RatissqTnd == true){RatissqTnd = false;}
      if(SlJKIGHtdT == true){SlJKIGHtdT = false;}
      if(WPURNNLXeb == true){WPURNNLXeb = false;}
      if(NyYNjUzdiH == true){NyYNjUzdiH = false;}
      if(AmVDdfTFij == true){AmVDdfTFij = false;}
      if(MoCkVCFbVf == true){MoCkVCFbVf = false;}
      if(hSnLQTNuam == true){hSnLQTNuam = false;}
      if(HcKWSjsRng == true){HcKWSjsRng = false;}
      if(sFnuPXwnrh == true){sFnuPXwnrh = false;}
      if(PWHDZgyKmJ == true){PWHDZgyKmJ = false;}
      if(SXeuciefSk == true){SXeuciefSk = false;}
      if(Jmnnlbdswr == true){Jmnnlbdswr = false;}
      if(WYDrXjVHwk == true){WYDrXjVHwk = false;}
      if(kiedOVZrRg == true){kiedOVZrRg = false;}
      if(sQVGYbiSRx == true){sQVGYbiSRx = false;}
      if(DENtlsTlXr == true){DENtlsTlXr = false;}
      if(MWigAZIJZP == true){MWigAZIJZP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXJMIDJDFV
{ 
  void kBCqiRDKqf()
  { 
      bool RbHkQzdSMp = false;
      bool SrWAuxpTpg = false;
      bool xbMLITiUtK = false;
      bool WlnlRAVoWd = false;
      bool JjZkadMMIB = false;
      bool lHCETpOucx = false;
      bool QIYBTgEkiu = false;
      bool bBwLXNCbjd = false;
      bool GVMsYPiiRb = false;
      bool kZLZMAKXRt = false;
      bool ZbcNYjLpgG = false;
      bool nmKyptwecE = false;
      bool yUSHJCpVyW = false;
      bool CdKpEerzTn = false;
      bool DrBLnyOMjS = false;
      bool EfuMwEIVDW = false;
      bool toqKDJcTsL = false;
      bool BxLoAFTGTL = false;
      bool nclfSWixtA = false;
      bool VWuxsOBqId = false;
      string CDankeuScM;
      string gIVxzfsJuD;
      string pqiiLgIAZP;
      string eDNXsBOokE;
      string lutPyguAzh;
      string WeFJGLUqcD;
      string WurNhdtyDx;
      string REXpQtwTke;
      string kHArsAxERg;
      string gXMhhqDggU;
      string mxxBQSGPsL;
      string PAGyROuATg;
      string fofVQsqpHZ;
      string qPlQqnKyaZ;
      string shLGRfROPT;
      string wDMAnxRakW;
      string aQHSUAOoGd;
      string DwYsmxdZDj;
      string bcZncmClbt;
      string VjNDzcarkR;
      if(CDankeuScM == mxxBQSGPsL){RbHkQzdSMp = true;}
      else if(mxxBQSGPsL == CDankeuScM){ZbcNYjLpgG = true;}
      if(gIVxzfsJuD == PAGyROuATg){SrWAuxpTpg = true;}
      else if(PAGyROuATg == gIVxzfsJuD){nmKyptwecE = true;}
      if(pqiiLgIAZP == fofVQsqpHZ){xbMLITiUtK = true;}
      else if(fofVQsqpHZ == pqiiLgIAZP){yUSHJCpVyW = true;}
      if(eDNXsBOokE == qPlQqnKyaZ){WlnlRAVoWd = true;}
      else if(qPlQqnKyaZ == eDNXsBOokE){CdKpEerzTn = true;}
      if(lutPyguAzh == shLGRfROPT){JjZkadMMIB = true;}
      else if(shLGRfROPT == lutPyguAzh){DrBLnyOMjS = true;}
      if(WeFJGLUqcD == wDMAnxRakW){lHCETpOucx = true;}
      else if(wDMAnxRakW == WeFJGLUqcD){EfuMwEIVDW = true;}
      if(WurNhdtyDx == aQHSUAOoGd){QIYBTgEkiu = true;}
      else if(aQHSUAOoGd == WurNhdtyDx){toqKDJcTsL = true;}
      if(REXpQtwTke == DwYsmxdZDj){bBwLXNCbjd = true;}
      if(kHArsAxERg == bcZncmClbt){GVMsYPiiRb = true;}
      if(gXMhhqDggU == VjNDzcarkR){kZLZMAKXRt = true;}
      while(DwYsmxdZDj == REXpQtwTke){BxLoAFTGTL = true;}
      while(bcZncmClbt == bcZncmClbt){nclfSWixtA = true;}
      while(VjNDzcarkR == VjNDzcarkR){VWuxsOBqId = true;}
      if(RbHkQzdSMp == true){RbHkQzdSMp = false;}
      if(SrWAuxpTpg == true){SrWAuxpTpg = false;}
      if(xbMLITiUtK == true){xbMLITiUtK = false;}
      if(WlnlRAVoWd == true){WlnlRAVoWd = false;}
      if(JjZkadMMIB == true){JjZkadMMIB = false;}
      if(lHCETpOucx == true){lHCETpOucx = false;}
      if(QIYBTgEkiu == true){QIYBTgEkiu = false;}
      if(bBwLXNCbjd == true){bBwLXNCbjd = false;}
      if(GVMsYPiiRb == true){GVMsYPiiRb = false;}
      if(kZLZMAKXRt == true){kZLZMAKXRt = false;}
      if(ZbcNYjLpgG == true){ZbcNYjLpgG = false;}
      if(nmKyptwecE == true){nmKyptwecE = false;}
      if(yUSHJCpVyW == true){yUSHJCpVyW = false;}
      if(CdKpEerzTn == true){CdKpEerzTn = false;}
      if(DrBLnyOMjS == true){DrBLnyOMjS = false;}
      if(EfuMwEIVDW == true){EfuMwEIVDW = false;}
      if(toqKDJcTsL == true){toqKDJcTsL = false;}
      if(BxLoAFTGTL == true){BxLoAFTGTL = false;}
      if(nclfSWixtA == true){nclfSWixtA = false;}
      if(VWuxsOBqId == true){VWuxsOBqId = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENSROPFEPG
{ 
  void jGxDmhfjLP()
  { 
      bool RbqejYZCmf = false;
      bool skhTwzJUgK = false;
      bool umUlwymGfy = false;
      bool QgtHGQxfTQ = false;
      bool PDHcGtlBfr = false;
      bool BNsEedHFhl = false;
      bool kTWnPLpZNe = false;
      bool BcBQurfreB = false;
      bool MlZmxCnpbb = false;
      bool JqyheugSMu = false;
      bool EMnApYMbJm = false;
      bool yPZfYztiqM = false;
      bool WAxkVKdTkz = false;
      bool KNejxzxYxY = false;
      bool pLgndtQSIe = false;
      bool BxbAXDODef = false;
      bool trqJckjphY = false;
      bool CVlRVKTIGb = false;
      bool sLLGyMkdLs = false;
      bool kssQdyUWLs = false;
      string UgQrCbzlTw;
      string fNQVeBknlo;
      string idbRCDKwac;
      string miRaAeaDJX;
      string KXUwlzJxQQ;
      string oStZLpFzoy;
      string QDLqJxuoUz;
      string aheOeLJeeD;
      string tNfJmTnqPJ;
      string ZaOLGGLdmo;
      string DTbRpHnfuA;
      string gZTkDDXCDo;
      string IDYLYASSHX;
      string zfrpzakOSf;
      string fIwPbAGcHD;
      string hJZxgAtQrp;
      string nUYWABhdkc;
      string SJiXJAHJiY;
      string soLDopFtJz;
      string fTVcqKiZOa;
      if(UgQrCbzlTw == DTbRpHnfuA){RbqejYZCmf = true;}
      else if(DTbRpHnfuA == UgQrCbzlTw){EMnApYMbJm = true;}
      if(fNQVeBknlo == gZTkDDXCDo){skhTwzJUgK = true;}
      else if(gZTkDDXCDo == fNQVeBknlo){yPZfYztiqM = true;}
      if(idbRCDKwac == IDYLYASSHX){umUlwymGfy = true;}
      else if(IDYLYASSHX == idbRCDKwac){WAxkVKdTkz = true;}
      if(miRaAeaDJX == zfrpzakOSf){QgtHGQxfTQ = true;}
      else if(zfrpzakOSf == miRaAeaDJX){KNejxzxYxY = true;}
      if(KXUwlzJxQQ == fIwPbAGcHD){PDHcGtlBfr = true;}
      else if(fIwPbAGcHD == KXUwlzJxQQ){pLgndtQSIe = true;}
      if(oStZLpFzoy == hJZxgAtQrp){BNsEedHFhl = true;}
      else if(hJZxgAtQrp == oStZLpFzoy){BxbAXDODef = true;}
      if(QDLqJxuoUz == nUYWABhdkc){kTWnPLpZNe = true;}
      else if(nUYWABhdkc == QDLqJxuoUz){trqJckjphY = true;}
      if(aheOeLJeeD == SJiXJAHJiY){BcBQurfreB = true;}
      if(tNfJmTnqPJ == soLDopFtJz){MlZmxCnpbb = true;}
      if(ZaOLGGLdmo == fTVcqKiZOa){JqyheugSMu = true;}
      while(SJiXJAHJiY == aheOeLJeeD){CVlRVKTIGb = true;}
      while(soLDopFtJz == soLDopFtJz){sLLGyMkdLs = true;}
      while(fTVcqKiZOa == fTVcqKiZOa){kssQdyUWLs = true;}
      if(RbqejYZCmf == true){RbqejYZCmf = false;}
      if(skhTwzJUgK == true){skhTwzJUgK = false;}
      if(umUlwymGfy == true){umUlwymGfy = false;}
      if(QgtHGQxfTQ == true){QgtHGQxfTQ = false;}
      if(PDHcGtlBfr == true){PDHcGtlBfr = false;}
      if(BNsEedHFhl == true){BNsEedHFhl = false;}
      if(kTWnPLpZNe == true){kTWnPLpZNe = false;}
      if(BcBQurfreB == true){BcBQurfreB = false;}
      if(MlZmxCnpbb == true){MlZmxCnpbb = false;}
      if(JqyheugSMu == true){JqyheugSMu = false;}
      if(EMnApYMbJm == true){EMnApYMbJm = false;}
      if(yPZfYztiqM == true){yPZfYztiqM = false;}
      if(WAxkVKdTkz == true){WAxkVKdTkz = false;}
      if(KNejxzxYxY == true){KNejxzxYxY = false;}
      if(pLgndtQSIe == true){pLgndtQSIe = false;}
      if(BxbAXDODef == true){BxbAXDODef = false;}
      if(trqJckjphY == true){trqJckjphY = false;}
      if(CVlRVKTIGb == true){CVlRVKTIGb = false;}
      if(sLLGyMkdLs == true){sLLGyMkdLs = false;}
      if(kssQdyUWLs == true){kssQdyUWLs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNGABKYAHX
{ 
  void cwpkLMbHyl()
  { 
      bool cHawxgkAtp = false;
      bool dIhuTWGheC = false;
      bool ljXKQgWZdR = false;
      bool XdEfmTOGxQ = false;
      bool bUYDTOlOyN = false;
      bool KKePxsjPeP = false;
      bool KLWbRAECHA = false;
      bool IzkNaQKTqC = false;
      bool tHaQGNynht = false;
      bool jyagGPywkS = false;
      bool JjGyELYRog = false;
      bool hPXcUCkGVE = false;
      bool CPUNPJXEGK = false;
      bool SOiYrKAbLu = false;
      bool ngzBLTayLD = false;
      bool eqafQsOrht = false;
      bool mUKdNTgzjK = false;
      bool BJtZQUQSCw = false;
      bool iZrCfamCHy = false;
      bool uHsQISWUnr = false;
      string kopBLStcwQ;
      string JCcdrGdcgY;
      string kgEYObWNHB;
      string jdwemPKwMR;
      string wHVTaCkxjs;
      string TMlSlDjRli;
      string wfVtffGyqb;
      string uhQPcdLjxM;
      string pZdNhWrdri;
      string fsJcVQlamu;
      string ulFHykwVoI;
      string rzTZrVCHLJ;
      string mcGHwBYmsL;
      string qjwCQDTVPx;
      string ZVniqfZikz;
      string NdOdHSfyLw;
      string MIcdQHCRIn;
      string CgrOiRnWPQ;
      string boCtyNUSty;
      string XUKSkRsKSj;
      if(kopBLStcwQ == ulFHykwVoI){cHawxgkAtp = true;}
      else if(ulFHykwVoI == kopBLStcwQ){JjGyELYRog = true;}
      if(JCcdrGdcgY == rzTZrVCHLJ){dIhuTWGheC = true;}
      else if(rzTZrVCHLJ == JCcdrGdcgY){hPXcUCkGVE = true;}
      if(kgEYObWNHB == mcGHwBYmsL){ljXKQgWZdR = true;}
      else if(mcGHwBYmsL == kgEYObWNHB){CPUNPJXEGK = true;}
      if(jdwemPKwMR == qjwCQDTVPx){XdEfmTOGxQ = true;}
      else if(qjwCQDTVPx == jdwemPKwMR){SOiYrKAbLu = true;}
      if(wHVTaCkxjs == ZVniqfZikz){bUYDTOlOyN = true;}
      else if(ZVniqfZikz == wHVTaCkxjs){ngzBLTayLD = true;}
      if(TMlSlDjRli == NdOdHSfyLw){KKePxsjPeP = true;}
      else if(NdOdHSfyLw == TMlSlDjRli){eqafQsOrht = true;}
      if(wfVtffGyqb == MIcdQHCRIn){KLWbRAECHA = true;}
      else if(MIcdQHCRIn == wfVtffGyqb){mUKdNTgzjK = true;}
      if(uhQPcdLjxM == CgrOiRnWPQ){IzkNaQKTqC = true;}
      if(pZdNhWrdri == boCtyNUSty){tHaQGNynht = true;}
      if(fsJcVQlamu == XUKSkRsKSj){jyagGPywkS = true;}
      while(CgrOiRnWPQ == uhQPcdLjxM){BJtZQUQSCw = true;}
      while(boCtyNUSty == boCtyNUSty){iZrCfamCHy = true;}
      while(XUKSkRsKSj == XUKSkRsKSj){uHsQISWUnr = true;}
      if(cHawxgkAtp == true){cHawxgkAtp = false;}
      if(dIhuTWGheC == true){dIhuTWGheC = false;}
      if(ljXKQgWZdR == true){ljXKQgWZdR = false;}
      if(XdEfmTOGxQ == true){XdEfmTOGxQ = false;}
      if(bUYDTOlOyN == true){bUYDTOlOyN = false;}
      if(KKePxsjPeP == true){KKePxsjPeP = false;}
      if(KLWbRAECHA == true){KLWbRAECHA = false;}
      if(IzkNaQKTqC == true){IzkNaQKTqC = false;}
      if(tHaQGNynht == true){tHaQGNynht = false;}
      if(jyagGPywkS == true){jyagGPywkS = false;}
      if(JjGyELYRog == true){JjGyELYRog = false;}
      if(hPXcUCkGVE == true){hPXcUCkGVE = false;}
      if(CPUNPJXEGK == true){CPUNPJXEGK = false;}
      if(SOiYrKAbLu == true){SOiYrKAbLu = false;}
      if(ngzBLTayLD == true){ngzBLTayLD = false;}
      if(eqafQsOrht == true){eqafQsOrht = false;}
      if(mUKdNTgzjK == true){mUKdNTgzjK = false;}
      if(BJtZQUQSCw == true){BJtZQUQSCw = false;}
      if(iZrCfamCHy == true){iZrCfamCHy = false;}
      if(uHsQISWUnr == true){uHsQISWUnr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQECVHUKZM
{ 
  void nOUsLpIQEM()
  { 
      bool tQnXlsRbAp = false;
      bool oLyEuixcTx = false;
      bool zUWDmBpRES = false;
      bool yeHuIPPjax = false;
      bool ktrrziSDmF = false;
      bool LqPDiYtjkj = false;
      bool DAWgrJEDwe = false;
      bool SMBWLFcdDD = false;
      bool hldzHHPDLi = false;
      bool VfzptkWKAp = false;
      bool ePHHlyosrd = false;
      bool wPfgCQVXZj = false;
      bool tAqMJmMKca = false;
      bool hRcNXRdVMI = false;
      bool RVLhlFzRnc = false;
      bool OzkQudYtyz = false;
      bool keQQudmSJj = false;
      bool lzKQRXoJZE = false;
      bool muVzMifMRs = false;
      bool siXNWmFtlH = false;
      string fIjMBlCssr;
      string OSYIWUOOdn;
      string XmhJTIRGsZ;
      string TSUpISwLwo;
      string BaHsfMNLXE;
      string akygSrZass;
      string UwzSYwyhzE;
      string YDRnmwfocH;
      string tGhozhTnXQ;
      string rURDUFbnTj;
      string OeLSeXTKsV;
      string MjykyONJTq;
      string bJKiLDkNTh;
      string UqVrsPtPJa;
      string OJtBEIWgFG;
      string qRUcIETcHb;
      string mFpKAVNGrh;
      string TyzrbROIdC;
      string fEHNqDVsio;
      string uRHhnITjBi;
      if(fIjMBlCssr == OeLSeXTKsV){tQnXlsRbAp = true;}
      else if(OeLSeXTKsV == fIjMBlCssr){ePHHlyosrd = true;}
      if(OSYIWUOOdn == MjykyONJTq){oLyEuixcTx = true;}
      else if(MjykyONJTq == OSYIWUOOdn){wPfgCQVXZj = true;}
      if(XmhJTIRGsZ == bJKiLDkNTh){zUWDmBpRES = true;}
      else if(bJKiLDkNTh == XmhJTIRGsZ){tAqMJmMKca = true;}
      if(TSUpISwLwo == UqVrsPtPJa){yeHuIPPjax = true;}
      else if(UqVrsPtPJa == TSUpISwLwo){hRcNXRdVMI = true;}
      if(BaHsfMNLXE == OJtBEIWgFG){ktrrziSDmF = true;}
      else if(OJtBEIWgFG == BaHsfMNLXE){RVLhlFzRnc = true;}
      if(akygSrZass == qRUcIETcHb){LqPDiYtjkj = true;}
      else if(qRUcIETcHb == akygSrZass){OzkQudYtyz = true;}
      if(UwzSYwyhzE == mFpKAVNGrh){DAWgrJEDwe = true;}
      else if(mFpKAVNGrh == UwzSYwyhzE){keQQudmSJj = true;}
      if(YDRnmwfocH == TyzrbROIdC){SMBWLFcdDD = true;}
      if(tGhozhTnXQ == fEHNqDVsio){hldzHHPDLi = true;}
      if(rURDUFbnTj == uRHhnITjBi){VfzptkWKAp = true;}
      while(TyzrbROIdC == YDRnmwfocH){lzKQRXoJZE = true;}
      while(fEHNqDVsio == fEHNqDVsio){muVzMifMRs = true;}
      while(uRHhnITjBi == uRHhnITjBi){siXNWmFtlH = true;}
      if(tQnXlsRbAp == true){tQnXlsRbAp = false;}
      if(oLyEuixcTx == true){oLyEuixcTx = false;}
      if(zUWDmBpRES == true){zUWDmBpRES = false;}
      if(yeHuIPPjax == true){yeHuIPPjax = false;}
      if(ktrrziSDmF == true){ktrrziSDmF = false;}
      if(LqPDiYtjkj == true){LqPDiYtjkj = false;}
      if(DAWgrJEDwe == true){DAWgrJEDwe = false;}
      if(SMBWLFcdDD == true){SMBWLFcdDD = false;}
      if(hldzHHPDLi == true){hldzHHPDLi = false;}
      if(VfzptkWKAp == true){VfzptkWKAp = false;}
      if(ePHHlyosrd == true){ePHHlyosrd = false;}
      if(wPfgCQVXZj == true){wPfgCQVXZj = false;}
      if(tAqMJmMKca == true){tAqMJmMKca = false;}
      if(hRcNXRdVMI == true){hRcNXRdVMI = false;}
      if(RVLhlFzRnc == true){RVLhlFzRnc = false;}
      if(OzkQudYtyz == true){OzkQudYtyz = false;}
      if(keQQudmSJj == true){keQQudmSJj = false;}
      if(lzKQRXoJZE == true){lzKQRXoJZE = false;}
      if(muVzMifMRs == true){muVzMifMRs = false;}
      if(siXNWmFtlH == true){siXNWmFtlH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDVKCTEAAW
{ 
  void mnXmCAYoME()
  { 
      bool HVFMHcPsSF = false;
      bool INAOjiqNWy = false;
      bool InHdQRNYrF = false;
      bool qYuFRhmbwM = false;
      bool kXDHTcZAyV = false;
      bool LCajZSOawp = false;
      bool OqANNjRuxB = false;
      bool wPQJMkkzKm = false;
      bool qMZVtoyLey = false;
      bool TMfGysWptj = false;
      bool LeDxZwkQWo = false;
      bool hOPIzBReTY = false;
      bool lGPygjiKLS = false;
      bool OuFabMJbwx = false;
      bool DgnpQEwWHw = false;
      bool brWUyFOFPp = false;
      bool MaEDalJogl = false;
      bool rohVUERZgb = false;
      bool mLCPqVYjcW = false;
      bool xEMGkbcjOe = false;
      string CeuYbmCBOu;
      string haQkUnkxhu;
      string HrEYoCbiTV;
      string dnUAzBIIgU;
      string IiOlwTSYzO;
      string IFjywJaWiY;
      string LShrRtFPlS;
      string fcQNmYcRbV;
      string jCjENYEWEo;
      string akYIIoAVUC;
      string NClfhfoWKW;
      string gItNnIhcer;
      string oiLxqtDIEx;
      string XHxZHhQEVg;
      string jhLgISpLTA;
      string HWpbMeqonn;
      string bfRNzYKUGG;
      string rdGxIHWdnY;
      string ErnEpBQVNb;
      string paPhFDPyhi;
      if(CeuYbmCBOu == NClfhfoWKW){HVFMHcPsSF = true;}
      else if(NClfhfoWKW == CeuYbmCBOu){LeDxZwkQWo = true;}
      if(haQkUnkxhu == gItNnIhcer){INAOjiqNWy = true;}
      else if(gItNnIhcer == haQkUnkxhu){hOPIzBReTY = true;}
      if(HrEYoCbiTV == oiLxqtDIEx){InHdQRNYrF = true;}
      else if(oiLxqtDIEx == HrEYoCbiTV){lGPygjiKLS = true;}
      if(dnUAzBIIgU == XHxZHhQEVg){qYuFRhmbwM = true;}
      else if(XHxZHhQEVg == dnUAzBIIgU){OuFabMJbwx = true;}
      if(IiOlwTSYzO == jhLgISpLTA){kXDHTcZAyV = true;}
      else if(jhLgISpLTA == IiOlwTSYzO){DgnpQEwWHw = true;}
      if(IFjywJaWiY == HWpbMeqonn){LCajZSOawp = true;}
      else if(HWpbMeqonn == IFjywJaWiY){brWUyFOFPp = true;}
      if(LShrRtFPlS == bfRNzYKUGG){OqANNjRuxB = true;}
      else if(bfRNzYKUGG == LShrRtFPlS){MaEDalJogl = true;}
      if(fcQNmYcRbV == rdGxIHWdnY){wPQJMkkzKm = true;}
      if(jCjENYEWEo == ErnEpBQVNb){qMZVtoyLey = true;}
      if(akYIIoAVUC == paPhFDPyhi){TMfGysWptj = true;}
      while(rdGxIHWdnY == fcQNmYcRbV){rohVUERZgb = true;}
      while(ErnEpBQVNb == ErnEpBQVNb){mLCPqVYjcW = true;}
      while(paPhFDPyhi == paPhFDPyhi){xEMGkbcjOe = true;}
      if(HVFMHcPsSF == true){HVFMHcPsSF = false;}
      if(INAOjiqNWy == true){INAOjiqNWy = false;}
      if(InHdQRNYrF == true){InHdQRNYrF = false;}
      if(qYuFRhmbwM == true){qYuFRhmbwM = false;}
      if(kXDHTcZAyV == true){kXDHTcZAyV = false;}
      if(LCajZSOawp == true){LCajZSOawp = false;}
      if(OqANNjRuxB == true){OqANNjRuxB = false;}
      if(wPQJMkkzKm == true){wPQJMkkzKm = false;}
      if(qMZVtoyLey == true){qMZVtoyLey = false;}
      if(TMfGysWptj == true){TMfGysWptj = false;}
      if(LeDxZwkQWo == true){LeDxZwkQWo = false;}
      if(hOPIzBReTY == true){hOPIzBReTY = false;}
      if(lGPygjiKLS == true){lGPygjiKLS = false;}
      if(OuFabMJbwx == true){OuFabMJbwx = false;}
      if(DgnpQEwWHw == true){DgnpQEwWHw = false;}
      if(brWUyFOFPp == true){brWUyFOFPp = false;}
      if(MaEDalJogl == true){MaEDalJogl = false;}
      if(rohVUERZgb == true){rohVUERZgb = false;}
      if(mLCPqVYjcW == true){mLCPqVYjcW = false;}
      if(xEMGkbcjOe == true){xEMGkbcjOe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKNKDKSKSA
{ 
  void YTHWRsGspC()
  { 
      bool ZarOJaJjJV = false;
      bool HqjdmsNFtE = false;
      bool wbEEGEnXQi = false;
      bool jxJdtgamHr = false;
      bool DICApWysYh = false;
      bool InahiyVnIE = false;
      bool llTalKgGiF = false;
      bool SaxCBmZDNi = false;
      bool GuyhauWbtw = false;
      bool KmdDFQobOf = false;
      bool orKSPgqYgu = false;
      bool YRZYyqnkAp = false;
      bool nFLmtewtwj = false;
      bool yyohsNkeSs = false;
      bool DytzWsMFEN = false;
      bool cDbXqjfXXj = false;
      bool kwbxxacrej = false;
      bool GISGloKMPB = false;
      bool SqphGtVQpJ = false;
      bool gNGhIHVxCw = false;
      string odkJSIntlQ;
      string XGTrwgkNIi;
      string pubShFqCjj;
      string iVArcgUyUe;
      string HwNpygOoxU;
      string PuQwRtCSbN;
      string RlJCgBFaOO;
      string MlscbshkTA;
      string pCEPTnFDai;
      string eBWHNUmLIw;
      string bmZhHdBmUX;
      string MQyaWPhshr;
      string wBzfjLPlPG;
      string GVbWYCbVIp;
      string lRiDVOCujx;
      string mscPAZnsyw;
      string NPXNQpnbCU;
      string mLjrFdSwJU;
      string ITBRTMsMWy;
      string OhWMbWtUlf;
      if(odkJSIntlQ == bmZhHdBmUX){ZarOJaJjJV = true;}
      else if(bmZhHdBmUX == odkJSIntlQ){orKSPgqYgu = true;}
      if(XGTrwgkNIi == MQyaWPhshr){HqjdmsNFtE = true;}
      else if(MQyaWPhshr == XGTrwgkNIi){YRZYyqnkAp = true;}
      if(pubShFqCjj == wBzfjLPlPG){wbEEGEnXQi = true;}
      else if(wBzfjLPlPG == pubShFqCjj){nFLmtewtwj = true;}
      if(iVArcgUyUe == GVbWYCbVIp){jxJdtgamHr = true;}
      else if(GVbWYCbVIp == iVArcgUyUe){yyohsNkeSs = true;}
      if(HwNpygOoxU == lRiDVOCujx){DICApWysYh = true;}
      else if(lRiDVOCujx == HwNpygOoxU){DytzWsMFEN = true;}
      if(PuQwRtCSbN == mscPAZnsyw){InahiyVnIE = true;}
      else if(mscPAZnsyw == PuQwRtCSbN){cDbXqjfXXj = true;}
      if(RlJCgBFaOO == NPXNQpnbCU){llTalKgGiF = true;}
      else if(NPXNQpnbCU == RlJCgBFaOO){kwbxxacrej = true;}
      if(MlscbshkTA == mLjrFdSwJU){SaxCBmZDNi = true;}
      if(pCEPTnFDai == ITBRTMsMWy){GuyhauWbtw = true;}
      if(eBWHNUmLIw == OhWMbWtUlf){KmdDFQobOf = true;}
      while(mLjrFdSwJU == MlscbshkTA){GISGloKMPB = true;}
      while(ITBRTMsMWy == ITBRTMsMWy){SqphGtVQpJ = true;}
      while(OhWMbWtUlf == OhWMbWtUlf){gNGhIHVxCw = true;}
      if(ZarOJaJjJV == true){ZarOJaJjJV = false;}
      if(HqjdmsNFtE == true){HqjdmsNFtE = false;}
      if(wbEEGEnXQi == true){wbEEGEnXQi = false;}
      if(jxJdtgamHr == true){jxJdtgamHr = false;}
      if(DICApWysYh == true){DICApWysYh = false;}
      if(InahiyVnIE == true){InahiyVnIE = false;}
      if(llTalKgGiF == true){llTalKgGiF = false;}
      if(SaxCBmZDNi == true){SaxCBmZDNi = false;}
      if(GuyhauWbtw == true){GuyhauWbtw = false;}
      if(KmdDFQobOf == true){KmdDFQobOf = false;}
      if(orKSPgqYgu == true){orKSPgqYgu = false;}
      if(YRZYyqnkAp == true){YRZYyqnkAp = false;}
      if(nFLmtewtwj == true){nFLmtewtwj = false;}
      if(yyohsNkeSs == true){yyohsNkeSs = false;}
      if(DytzWsMFEN == true){DytzWsMFEN = false;}
      if(cDbXqjfXXj == true){cDbXqjfXXj = false;}
      if(kwbxxacrej == true){kwbxxacrej = false;}
      if(GISGloKMPB == true){GISGloKMPB = false;}
      if(SqphGtVQpJ == true){SqphGtVQpJ = false;}
      if(gNGhIHVxCw == true){gNGhIHVxCw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDEROCWCMH
{ 
  void FajLKyuEuR()
  { 
      bool YxClxpfgmQ = false;
      bool lobBnBTBnd = false;
      bool goOqGLxTqf = false;
      bool BBbOgmlbXn = false;
      bool pMxhbOTyBW = false;
      bool cMPWdjiLfk = false;
      bool sMpGOjNMUA = false;
      bool PrcAnTrfPq = false;
      bool qzRTDokEjw = false;
      bool EaumtcWpSr = false;
      bool BHcBHjiPiJ = false;
      bool rCwntttVCZ = false;
      bool zIcYunwpFL = false;
      bool xBNWpjVQMS = false;
      bool GVVZEBeGsA = false;
      bool hBnssrdEFT = false;
      bool mrJXMqoYyJ = false;
      bool XcIiTcmDTs = false;
      bool IoxEcuNUdx = false;
      bool FRLsfNLyMN = false;
      string XgtZXSkOCr;
      string DtsOCRbcPf;
      string pkgjkRzKHP;
      string KRHytYPJle;
      string TSPGTJtkpX;
      string IkiyjmAJnF;
      string TZGmhkmtUd;
      string CSqkMXUZPb;
      string XOUjGYiJOG;
      string YFUfKsLcYi;
      string VzPMVptxlL;
      string SZtLhFFWfI;
      string BdfNEwyLZS;
      string LqAgGXyHNQ;
      string ekXCmyLIxE;
      string noxQgrTCHY;
      string qhWSAbYNFK;
      string HxIPcPGdZF;
      string koOVdVtjzN;
      string EwAoYwNEBL;
      if(XgtZXSkOCr == VzPMVptxlL){YxClxpfgmQ = true;}
      else if(VzPMVptxlL == XgtZXSkOCr){BHcBHjiPiJ = true;}
      if(DtsOCRbcPf == SZtLhFFWfI){lobBnBTBnd = true;}
      else if(SZtLhFFWfI == DtsOCRbcPf){rCwntttVCZ = true;}
      if(pkgjkRzKHP == BdfNEwyLZS){goOqGLxTqf = true;}
      else if(BdfNEwyLZS == pkgjkRzKHP){zIcYunwpFL = true;}
      if(KRHytYPJle == LqAgGXyHNQ){BBbOgmlbXn = true;}
      else if(LqAgGXyHNQ == KRHytYPJle){xBNWpjVQMS = true;}
      if(TSPGTJtkpX == ekXCmyLIxE){pMxhbOTyBW = true;}
      else if(ekXCmyLIxE == TSPGTJtkpX){GVVZEBeGsA = true;}
      if(IkiyjmAJnF == noxQgrTCHY){cMPWdjiLfk = true;}
      else if(noxQgrTCHY == IkiyjmAJnF){hBnssrdEFT = true;}
      if(TZGmhkmtUd == qhWSAbYNFK){sMpGOjNMUA = true;}
      else if(qhWSAbYNFK == TZGmhkmtUd){mrJXMqoYyJ = true;}
      if(CSqkMXUZPb == HxIPcPGdZF){PrcAnTrfPq = true;}
      if(XOUjGYiJOG == koOVdVtjzN){qzRTDokEjw = true;}
      if(YFUfKsLcYi == EwAoYwNEBL){EaumtcWpSr = true;}
      while(HxIPcPGdZF == CSqkMXUZPb){XcIiTcmDTs = true;}
      while(koOVdVtjzN == koOVdVtjzN){IoxEcuNUdx = true;}
      while(EwAoYwNEBL == EwAoYwNEBL){FRLsfNLyMN = true;}
      if(YxClxpfgmQ == true){YxClxpfgmQ = false;}
      if(lobBnBTBnd == true){lobBnBTBnd = false;}
      if(goOqGLxTqf == true){goOqGLxTqf = false;}
      if(BBbOgmlbXn == true){BBbOgmlbXn = false;}
      if(pMxhbOTyBW == true){pMxhbOTyBW = false;}
      if(cMPWdjiLfk == true){cMPWdjiLfk = false;}
      if(sMpGOjNMUA == true){sMpGOjNMUA = false;}
      if(PrcAnTrfPq == true){PrcAnTrfPq = false;}
      if(qzRTDokEjw == true){qzRTDokEjw = false;}
      if(EaumtcWpSr == true){EaumtcWpSr = false;}
      if(BHcBHjiPiJ == true){BHcBHjiPiJ = false;}
      if(rCwntttVCZ == true){rCwntttVCZ = false;}
      if(zIcYunwpFL == true){zIcYunwpFL = false;}
      if(xBNWpjVQMS == true){xBNWpjVQMS = false;}
      if(GVVZEBeGsA == true){GVVZEBeGsA = false;}
      if(hBnssrdEFT == true){hBnssrdEFT = false;}
      if(mrJXMqoYyJ == true){mrJXMqoYyJ = false;}
      if(XcIiTcmDTs == true){XcIiTcmDTs = false;}
      if(IoxEcuNUdx == true){IoxEcuNUdx = false;}
      if(FRLsfNLyMN == true){FRLsfNLyMN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTGRHVNEPY
{ 
  void uBAIbYumqb()
  { 
      bool yjbpLLQceW = false;
      bool rRUjngDLMZ = false;
      bool gZVbYFPTUI = false;
      bool WOFSWULJMG = false;
      bool JVDoUUUpZB = false;
      bool msxEHXOzQG = false;
      bool wwHVAcMBMS = false;
      bool VszGPLWgGD = false;
      bool kZsTVdRALz = false;
      bool GLrGKMNgor = false;
      bool ISdHettqou = false;
      bool BgsNUVDnAW = false;
      bool LMpNLKArwD = false;
      bool xorOuRwknb = false;
      bool iZLPyYRekn = false;
      bool JZgSgwbPuU = false;
      bool sCukyLodSD = false;
      bool ZRzXmkBaPm = false;
      bool rUGHtWHZhy = false;
      bool ofoThgeZQl = false;
      string TJyirOoqcy;
      string tqGMxYJKBC;
      string PqAXBnfFbr;
      string HUknHnmTGC;
      string ICXOrniJqD;
      string PIOtkcIZhE;
      string ijOjqYGSFI;
      string kpDysMSkfM;
      string EVNYcyGpDd;
      string eMlBTYnnWS;
      string hQEhRYFPAY;
      string JXtUAMVoHr;
      string SPObcXEBeU;
      string YeNMenReHD;
      string sppeTHSQBG;
      string CyfeARBbFs;
      string UDjeAeJhoL;
      string uphDzcZjHU;
      string FmAYSZyiLM;
      string moZNipFKen;
      if(TJyirOoqcy == hQEhRYFPAY){yjbpLLQceW = true;}
      else if(hQEhRYFPAY == TJyirOoqcy){ISdHettqou = true;}
      if(tqGMxYJKBC == JXtUAMVoHr){rRUjngDLMZ = true;}
      else if(JXtUAMVoHr == tqGMxYJKBC){BgsNUVDnAW = true;}
      if(PqAXBnfFbr == SPObcXEBeU){gZVbYFPTUI = true;}
      else if(SPObcXEBeU == PqAXBnfFbr){LMpNLKArwD = true;}
      if(HUknHnmTGC == YeNMenReHD){WOFSWULJMG = true;}
      else if(YeNMenReHD == HUknHnmTGC){xorOuRwknb = true;}
      if(ICXOrniJqD == sppeTHSQBG){JVDoUUUpZB = true;}
      else if(sppeTHSQBG == ICXOrniJqD){iZLPyYRekn = true;}
      if(PIOtkcIZhE == CyfeARBbFs){msxEHXOzQG = true;}
      else if(CyfeARBbFs == PIOtkcIZhE){JZgSgwbPuU = true;}
      if(ijOjqYGSFI == UDjeAeJhoL){wwHVAcMBMS = true;}
      else if(UDjeAeJhoL == ijOjqYGSFI){sCukyLodSD = true;}
      if(kpDysMSkfM == uphDzcZjHU){VszGPLWgGD = true;}
      if(EVNYcyGpDd == FmAYSZyiLM){kZsTVdRALz = true;}
      if(eMlBTYnnWS == moZNipFKen){GLrGKMNgor = true;}
      while(uphDzcZjHU == kpDysMSkfM){ZRzXmkBaPm = true;}
      while(FmAYSZyiLM == FmAYSZyiLM){rUGHtWHZhy = true;}
      while(moZNipFKen == moZNipFKen){ofoThgeZQl = true;}
      if(yjbpLLQceW == true){yjbpLLQceW = false;}
      if(rRUjngDLMZ == true){rRUjngDLMZ = false;}
      if(gZVbYFPTUI == true){gZVbYFPTUI = false;}
      if(WOFSWULJMG == true){WOFSWULJMG = false;}
      if(JVDoUUUpZB == true){JVDoUUUpZB = false;}
      if(msxEHXOzQG == true){msxEHXOzQG = false;}
      if(wwHVAcMBMS == true){wwHVAcMBMS = false;}
      if(VszGPLWgGD == true){VszGPLWgGD = false;}
      if(kZsTVdRALz == true){kZsTVdRALz = false;}
      if(GLrGKMNgor == true){GLrGKMNgor = false;}
      if(ISdHettqou == true){ISdHettqou = false;}
      if(BgsNUVDnAW == true){BgsNUVDnAW = false;}
      if(LMpNLKArwD == true){LMpNLKArwD = false;}
      if(xorOuRwknb == true){xorOuRwknb = false;}
      if(iZLPyYRekn == true){iZLPyYRekn = false;}
      if(JZgSgwbPuU == true){JZgSgwbPuU = false;}
      if(sCukyLodSD == true){sCukyLodSD = false;}
      if(ZRzXmkBaPm == true){ZRzXmkBaPm = false;}
      if(rUGHtWHZhy == true){rUGHtWHZhy = false;}
      if(ofoThgeZQl == true){ofoThgeZQl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEVGCLPLXW
{ 
  void TlOhtXTzxF()
  { 
      bool BaxiqDgkgP = false;
      bool DpAcGXxdXi = false;
      bool dAgDoQuIMX = false;
      bool eaUYqTYlgf = false;
      bool wnqiGZqsQs = false;
      bool FrMWiAtsta = false;
      bool IYXIjcVall = false;
      bool yKxqloIxxO = false;
      bool YBqTRmOxop = false;
      bool ZfrGXXPhyc = false;
      bool EPHeuuuUjt = false;
      bool rwufBGgEqx = false;
      bool OYluMRRpTO = false;
      bool ZZzTKJtMXW = false;
      bool qsNuycjMFR = false;
      bool pLqBOecLRc = false;
      bool cEBVTRxaUq = false;
      bool MUfTFUKqxj = false;
      bool hFkBXOiyFe = false;
      bool fhtuslqraf = false;
      string ThpLqTGTdP;
      string GTzFXRQusD;
      string NgogcNQRky;
      string RfGkuYLiHm;
      string SCkCVhWymI;
      string KRfyPmrIid;
      string DnhexaMNJz;
      string FhnGjLulLt;
      string pRecnAzHVH;
      string fDzcjdTGFt;
      string UInnDcdZOE;
      string rGwnnkIFpx;
      string bErCSBhKWF;
      string qogQZhdqYL;
      string VZsRPZGLoy;
      string VNPIRPQlUB;
      string tSCIMCYfNF;
      string HRfdaCLZlr;
      string uWVXjdYYzK;
      string QqVXRDWkFM;
      if(ThpLqTGTdP == UInnDcdZOE){BaxiqDgkgP = true;}
      else if(UInnDcdZOE == ThpLqTGTdP){EPHeuuuUjt = true;}
      if(GTzFXRQusD == rGwnnkIFpx){DpAcGXxdXi = true;}
      else if(rGwnnkIFpx == GTzFXRQusD){rwufBGgEqx = true;}
      if(NgogcNQRky == bErCSBhKWF){dAgDoQuIMX = true;}
      else if(bErCSBhKWF == NgogcNQRky){OYluMRRpTO = true;}
      if(RfGkuYLiHm == qogQZhdqYL){eaUYqTYlgf = true;}
      else if(qogQZhdqYL == RfGkuYLiHm){ZZzTKJtMXW = true;}
      if(SCkCVhWymI == VZsRPZGLoy){wnqiGZqsQs = true;}
      else if(VZsRPZGLoy == SCkCVhWymI){qsNuycjMFR = true;}
      if(KRfyPmrIid == VNPIRPQlUB){FrMWiAtsta = true;}
      else if(VNPIRPQlUB == KRfyPmrIid){pLqBOecLRc = true;}
      if(DnhexaMNJz == tSCIMCYfNF){IYXIjcVall = true;}
      else if(tSCIMCYfNF == DnhexaMNJz){cEBVTRxaUq = true;}
      if(FhnGjLulLt == HRfdaCLZlr){yKxqloIxxO = true;}
      if(pRecnAzHVH == uWVXjdYYzK){YBqTRmOxop = true;}
      if(fDzcjdTGFt == QqVXRDWkFM){ZfrGXXPhyc = true;}
      while(HRfdaCLZlr == FhnGjLulLt){MUfTFUKqxj = true;}
      while(uWVXjdYYzK == uWVXjdYYzK){hFkBXOiyFe = true;}
      while(QqVXRDWkFM == QqVXRDWkFM){fhtuslqraf = true;}
      if(BaxiqDgkgP == true){BaxiqDgkgP = false;}
      if(DpAcGXxdXi == true){DpAcGXxdXi = false;}
      if(dAgDoQuIMX == true){dAgDoQuIMX = false;}
      if(eaUYqTYlgf == true){eaUYqTYlgf = false;}
      if(wnqiGZqsQs == true){wnqiGZqsQs = false;}
      if(FrMWiAtsta == true){FrMWiAtsta = false;}
      if(IYXIjcVall == true){IYXIjcVall = false;}
      if(yKxqloIxxO == true){yKxqloIxxO = false;}
      if(YBqTRmOxop == true){YBqTRmOxop = false;}
      if(ZfrGXXPhyc == true){ZfrGXXPhyc = false;}
      if(EPHeuuuUjt == true){EPHeuuuUjt = false;}
      if(rwufBGgEqx == true){rwufBGgEqx = false;}
      if(OYluMRRpTO == true){OYluMRRpTO = false;}
      if(ZZzTKJtMXW == true){ZZzTKJtMXW = false;}
      if(qsNuycjMFR == true){qsNuycjMFR = false;}
      if(pLqBOecLRc == true){pLqBOecLRc = false;}
      if(cEBVTRxaUq == true){cEBVTRxaUq = false;}
      if(MUfTFUKqxj == true){MUfTFUKqxj = false;}
      if(hFkBXOiyFe == true){hFkBXOiyFe = false;}
      if(fhtuslqraf == true){fhtuslqraf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QQJXGRZLFK
{ 
  void bezbBVghOQ()
  { 
      bool nDiwrsktBP = false;
      bool mdtrUznKTG = false;
      bool NJAGcKMqcg = false;
      bool aFVyhcdpBk = false;
      bool soCgEAUtKj = false;
      bool qxiUseDbTh = false;
      bool ftRTogHuKq = false;
      bool UxIiNXGSCb = false;
      bool oSfrpdVBFC = false;
      bool ZBVSEzWhrW = false;
      bool sZjTOsnAGU = false;
      bool XjZrsNNZdL = false;
      bool LFpHQTapdO = false;
      bool AYaehOhLcw = false;
      bool oVukepadZq = false;
      bool kwDfLmjbCu = false;
      bool SxVrTzItKd = false;
      bool eBxhVoKEca = false;
      bool sxQmdDUtTu = false;
      bool eFIgdrACQe = false;
      string XqnMfBSGXr;
      string mtDqHIGhwC;
      string lcRFhYlchP;
      string BPLInEduYZ;
      string jlWVQogLoP;
      string PbmnXuZidG;
      string PoXHpWhuCC;
      string dKJVRAGuos;
      string rZnSAYcXjs;
      string euRRJtNOes;
      string GlJlkESQVX;
      string odsjNpBFHR;
      string tKKJXisqMX;
      string mqQwmGPBhu;
      string FLBMDBBgES;
      string sIGMyubAOC;
      string LaEykxMxxH;
      string ZAWMLhIxFV;
      string gMmsddjDxq;
      string ePmfjeHDaG;
      if(XqnMfBSGXr == GlJlkESQVX){nDiwrsktBP = true;}
      else if(GlJlkESQVX == XqnMfBSGXr){sZjTOsnAGU = true;}
      if(mtDqHIGhwC == odsjNpBFHR){mdtrUznKTG = true;}
      else if(odsjNpBFHR == mtDqHIGhwC){XjZrsNNZdL = true;}
      if(lcRFhYlchP == tKKJXisqMX){NJAGcKMqcg = true;}
      else if(tKKJXisqMX == lcRFhYlchP){LFpHQTapdO = true;}
      if(BPLInEduYZ == mqQwmGPBhu){aFVyhcdpBk = true;}
      else if(mqQwmGPBhu == BPLInEduYZ){AYaehOhLcw = true;}
      if(jlWVQogLoP == FLBMDBBgES){soCgEAUtKj = true;}
      else if(FLBMDBBgES == jlWVQogLoP){oVukepadZq = true;}
      if(PbmnXuZidG == sIGMyubAOC){qxiUseDbTh = true;}
      else if(sIGMyubAOC == PbmnXuZidG){kwDfLmjbCu = true;}
      if(PoXHpWhuCC == LaEykxMxxH){ftRTogHuKq = true;}
      else if(LaEykxMxxH == PoXHpWhuCC){SxVrTzItKd = true;}
      if(dKJVRAGuos == ZAWMLhIxFV){UxIiNXGSCb = true;}
      if(rZnSAYcXjs == gMmsddjDxq){oSfrpdVBFC = true;}
      if(euRRJtNOes == ePmfjeHDaG){ZBVSEzWhrW = true;}
      while(ZAWMLhIxFV == dKJVRAGuos){eBxhVoKEca = true;}
      while(gMmsddjDxq == gMmsddjDxq){sxQmdDUtTu = true;}
      while(ePmfjeHDaG == ePmfjeHDaG){eFIgdrACQe = true;}
      if(nDiwrsktBP == true){nDiwrsktBP = false;}
      if(mdtrUznKTG == true){mdtrUznKTG = false;}
      if(NJAGcKMqcg == true){NJAGcKMqcg = false;}
      if(aFVyhcdpBk == true){aFVyhcdpBk = false;}
      if(soCgEAUtKj == true){soCgEAUtKj = false;}
      if(qxiUseDbTh == true){qxiUseDbTh = false;}
      if(ftRTogHuKq == true){ftRTogHuKq = false;}
      if(UxIiNXGSCb == true){UxIiNXGSCb = false;}
      if(oSfrpdVBFC == true){oSfrpdVBFC = false;}
      if(ZBVSEzWhrW == true){ZBVSEzWhrW = false;}
      if(sZjTOsnAGU == true){sZjTOsnAGU = false;}
      if(XjZrsNNZdL == true){XjZrsNNZdL = false;}
      if(LFpHQTapdO == true){LFpHQTapdO = false;}
      if(AYaehOhLcw == true){AYaehOhLcw = false;}
      if(oVukepadZq == true){oVukepadZq = false;}
      if(kwDfLmjbCu == true){kwDfLmjbCu = false;}
      if(SxVrTzItKd == true){SxVrTzItKd = false;}
      if(eBxhVoKEca == true){eBxhVoKEca = false;}
      if(sxQmdDUtTu == true){sxQmdDUtTu = false;}
      if(eFIgdrACQe == true){eFIgdrACQe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOFFJXTGXO
{ 
  void LHbjVdUTZd()
  { 
      bool yKWDMHFoQu = false;
      bool ObbjslRDSa = false;
      bool KSmWOlEaSd = false;
      bool dTHQidtwjM = false;
      bool FAdFUHqMDK = false;
      bool DeSUofXzoa = false;
      bool DeWlQtTLAP = false;
      bool rUSFVKngCG = false;
      bool tqXHazBmaD = false;
      bool FtGJJZcroZ = false;
      bool mfLmShLMze = false;
      bool qpxhfLHPLR = false;
      bool sgjxJxNJuu = false;
      bool gwrbTNfjor = false;
      bool nnmuLOxYcy = false;
      bool RNfXgFwNdU = false;
      bool TBQDxuyUOS = false;
      bool fXZScEtnlt = false;
      bool zogxdTPTuN = false;
      bool RRFTXlXjxP = false;
      string LIIlsgBIus;
      string DhARIlleYR;
      string BARBXxrNGf;
      string wMMEGcCDMY;
      string NgjBrUOVoF;
      string hnOVtKqGOw;
      string nnCOwqVwLe;
      string jiSzDTPQJD;
      string hWXAyIxqJu;
      string lunPjYeUEB;
      string zSJKVyUORa;
      string uZwKNRPBPm;
      string tdlQsntCOe;
      string nuLIEPMNeA;
      string nhYhALzdCS;
      string JcFQHUfsQh;
      string DSAmlANnGy;
      string FBWPzLFDQg;
      string nQAwULouBj;
      string iTwwxVhkwA;
      if(LIIlsgBIus == zSJKVyUORa){yKWDMHFoQu = true;}
      else if(zSJKVyUORa == LIIlsgBIus){mfLmShLMze = true;}
      if(DhARIlleYR == uZwKNRPBPm){ObbjslRDSa = true;}
      else if(uZwKNRPBPm == DhARIlleYR){qpxhfLHPLR = true;}
      if(BARBXxrNGf == tdlQsntCOe){KSmWOlEaSd = true;}
      else if(tdlQsntCOe == BARBXxrNGf){sgjxJxNJuu = true;}
      if(wMMEGcCDMY == nuLIEPMNeA){dTHQidtwjM = true;}
      else if(nuLIEPMNeA == wMMEGcCDMY){gwrbTNfjor = true;}
      if(NgjBrUOVoF == nhYhALzdCS){FAdFUHqMDK = true;}
      else if(nhYhALzdCS == NgjBrUOVoF){nnmuLOxYcy = true;}
      if(hnOVtKqGOw == JcFQHUfsQh){DeSUofXzoa = true;}
      else if(JcFQHUfsQh == hnOVtKqGOw){RNfXgFwNdU = true;}
      if(nnCOwqVwLe == DSAmlANnGy){DeWlQtTLAP = true;}
      else if(DSAmlANnGy == nnCOwqVwLe){TBQDxuyUOS = true;}
      if(jiSzDTPQJD == FBWPzLFDQg){rUSFVKngCG = true;}
      if(hWXAyIxqJu == nQAwULouBj){tqXHazBmaD = true;}
      if(lunPjYeUEB == iTwwxVhkwA){FtGJJZcroZ = true;}
      while(FBWPzLFDQg == jiSzDTPQJD){fXZScEtnlt = true;}
      while(nQAwULouBj == nQAwULouBj){zogxdTPTuN = true;}
      while(iTwwxVhkwA == iTwwxVhkwA){RRFTXlXjxP = true;}
      if(yKWDMHFoQu == true){yKWDMHFoQu = false;}
      if(ObbjslRDSa == true){ObbjslRDSa = false;}
      if(KSmWOlEaSd == true){KSmWOlEaSd = false;}
      if(dTHQidtwjM == true){dTHQidtwjM = false;}
      if(FAdFUHqMDK == true){FAdFUHqMDK = false;}
      if(DeSUofXzoa == true){DeSUofXzoa = false;}
      if(DeWlQtTLAP == true){DeWlQtTLAP = false;}
      if(rUSFVKngCG == true){rUSFVKngCG = false;}
      if(tqXHazBmaD == true){tqXHazBmaD = false;}
      if(FtGJJZcroZ == true){FtGJJZcroZ = false;}
      if(mfLmShLMze == true){mfLmShLMze = false;}
      if(qpxhfLHPLR == true){qpxhfLHPLR = false;}
      if(sgjxJxNJuu == true){sgjxJxNJuu = false;}
      if(gwrbTNfjor == true){gwrbTNfjor = false;}
      if(nnmuLOxYcy == true){nnmuLOxYcy = false;}
      if(RNfXgFwNdU == true){RNfXgFwNdU = false;}
      if(TBQDxuyUOS == true){TBQDxuyUOS = false;}
      if(fXZScEtnlt == true){fXZScEtnlt = false;}
      if(zogxdTPTuN == true){zogxdTPTuN = false;}
      if(RRFTXlXjxP == true){RRFTXlXjxP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPZGNDMRYE
{ 
  void qCxokPOCfV()
  { 
      bool jRsyUMMlzp = false;
      bool nbUXMSrcId = false;
      bool TYeyaVtGjS = false;
      bool fUDdqcTurb = false;
      bool OjruEgicXO = false;
      bool QAUYHLmtXy = false;
      bool RGCgJTXpfj = false;
      bool zwjgPifjss = false;
      bool lQhUBfzdVf = false;
      bool pYXsJIhLlk = false;
      bool JsxnPTPnJY = false;
      bool eDBdMAXgec = false;
      bool TsTAsaYqWG = false;
      bool BTyIjsTtFh = false;
      bool QLUxAmXsgI = false;
      bool jAgIRPYwtn = false;
      bool uYQCWKErsS = false;
      bool gcbxMHYVzF = false;
      bool DfJOVBmoqU = false;
      bool UWzQlquRap = false;
      string EytxZXrtyu;
      string TEJXAGSPue;
      string XYxhnFmSdY;
      string MZNyOltPdl;
      string dELfVAMHpy;
      string gBItDeAMJT;
      string kYQZhtqLIN;
      string LDlJBSNQLn;
      string recfrLRStj;
      string khFJBEnlxb;
      string JAzblcPysk;
      string RjAVaFwjgW;
      string bXRXccxcIw;
      string eaSjdreAsO;
      string uSZJRBhjhu;
      string IDEazliazI;
      string fmpwFpQPqi;
      string ZuqSaJxHGb;
      string uMtNnaWrkr;
      string IEBkhIccDb;
      if(EytxZXrtyu == JAzblcPysk){jRsyUMMlzp = true;}
      else if(JAzblcPysk == EytxZXrtyu){JsxnPTPnJY = true;}
      if(TEJXAGSPue == RjAVaFwjgW){nbUXMSrcId = true;}
      else if(RjAVaFwjgW == TEJXAGSPue){eDBdMAXgec = true;}
      if(XYxhnFmSdY == bXRXccxcIw){TYeyaVtGjS = true;}
      else if(bXRXccxcIw == XYxhnFmSdY){TsTAsaYqWG = true;}
      if(MZNyOltPdl == eaSjdreAsO){fUDdqcTurb = true;}
      else if(eaSjdreAsO == MZNyOltPdl){BTyIjsTtFh = true;}
      if(dELfVAMHpy == uSZJRBhjhu){OjruEgicXO = true;}
      else if(uSZJRBhjhu == dELfVAMHpy){QLUxAmXsgI = true;}
      if(gBItDeAMJT == IDEazliazI){QAUYHLmtXy = true;}
      else if(IDEazliazI == gBItDeAMJT){jAgIRPYwtn = true;}
      if(kYQZhtqLIN == fmpwFpQPqi){RGCgJTXpfj = true;}
      else if(fmpwFpQPqi == kYQZhtqLIN){uYQCWKErsS = true;}
      if(LDlJBSNQLn == ZuqSaJxHGb){zwjgPifjss = true;}
      if(recfrLRStj == uMtNnaWrkr){lQhUBfzdVf = true;}
      if(khFJBEnlxb == IEBkhIccDb){pYXsJIhLlk = true;}
      while(ZuqSaJxHGb == LDlJBSNQLn){gcbxMHYVzF = true;}
      while(uMtNnaWrkr == uMtNnaWrkr){DfJOVBmoqU = true;}
      while(IEBkhIccDb == IEBkhIccDb){UWzQlquRap = true;}
      if(jRsyUMMlzp == true){jRsyUMMlzp = false;}
      if(nbUXMSrcId == true){nbUXMSrcId = false;}
      if(TYeyaVtGjS == true){TYeyaVtGjS = false;}
      if(fUDdqcTurb == true){fUDdqcTurb = false;}
      if(OjruEgicXO == true){OjruEgicXO = false;}
      if(QAUYHLmtXy == true){QAUYHLmtXy = false;}
      if(RGCgJTXpfj == true){RGCgJTXpfj = false;}
      if(zwjgPifjss == true){zwjgPifjss = false;}
      if(lQhUBfzdVf == true){lQhUBfzdVf = false;}
      if(pYXsJIhLlk == true){pYXsJIhLlk = false;}
      if(JsxnPTPnJY == true){JsxnPTPnJY = false;}
      if(eDBdMAXgec == true){eDBdMAXgec = false;}
      if(TsTAsaYqWG == true){TsTAsaYqWG = false;}
      if(BTyIjsTtFh == true){BTyIjsTtFh = false;}
      if(QLUxAmXsgI == true){QLUxAmXsgI = false;}
      if(jAgIRPYwtn == true){jAgIRPYwtn = false;}
      if(uYQCWKErsS == true){uYQCWKErsS = false;}
      if(gcbxMHYVzF == true){gcbxMHYVzF = false;}
      if(DfJOVBmoqU == true){DfJOVBmoqU = false;}
      if(UWzQlquRap == true){UWzQlquRap = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MSMOITBSCY
{ 
  void XgjKUtxYIV()
  { 
      bool ysXPnMElRw = false;
      bool VQUkAUDohW = false;
      bool FZNwZRVhcM = false;
      bool mfIfwHMhpT = false;
      bool LerWtFkUAK = false;
      bool AaVKaXfaoV = false;
      bool pVIFIoIons = false;
      bool IVzOKZgpCT = false;
      bool gAhRMMKxFY = false;
      bool akrTcoVmNE = false;
      bool xugHCebHzA = false;
      bool poYVnonqrw = false;
      bool eLjPRWcekV = false;
      bool EtbyWlTZOh = false;
      bool jDxEhlMWem = false;
      bool AduRYkLQpe = false;
      bool BxVdwwMayC = false;
      bool VObKMbNegf = false;
      bool KGzxUZyKYk = false;
      bool ZCjjflgTIl = false;
      string fQBTwOOWmQ;
      string IcuPjqdIZu;
      string PxnoCbXBIf;
      string dVTbRpomIM;
      string SmwpdUiqDe;
      string SMYNShbMRT;
      string pNOHlmJSxs;
      string CqzNbbAxLh;
      string sfxcNQxFJj;
      string ObUnVFYoDq;
      string KPtKbbMLlp;
      string heBjaJPktU;
      string pEJNeaVLqW;
      string DLsUWdlmBl;
      string EkTTCiZkNM;
      string pntiBGGffA;
      string FBUPlVkgMx;
      string XciIQEjoLu;
      string AjxegPQKTP;
      string WFGAfDQEgf;
      if(fQBTwOOWmQ == KPtKbbMLlp){ysXPnMElRw = true;}
      else if(KPtKbbMLlp == fQBTwOOWmQ){xugHCebHzA = true;}
      if(IcuPjqdIZu == heBjaJPktU){VQUkAUDohW = true;}
      else if(heBjaJPktU == IcuPjqdIZu){poYVnonqrw = true;}
      if(PxnoCbXBIf == pEJNeaVLqW){FZNwZRVhcM = true;}
      else if(pEJNeaVLqW == PxnoCbXBIf){eLjPRWcekV = true;}
      if(dVTbRpomIM == DLsUWdlmBl){mfIfwHMhpT = true;}
      else if(DLsUWdlmBl == dVTbRpomIM){EtbyWlTZOh = true;}
      if(SmwpdUiqDe == EkTTCiZkNM){LerWtFkUAK = true;}
      else if(EkTTCiZkNM == SmwpdUiqDe){jDxEhlMWem = true;}
      if(SMYNShbMRT == pntiBGGffA){AaVKaXfaoV = true;}
      else if(pntiBGGffA == SMYNShbMRT){AduRYkLQpe = true;}
      if(pNOHlmJSxs == FBUPlVkgMx){pVIFIoIons = true;}
      else if(FBUPlVkgMx == pNOHlmJSxs){BxVdwwMayC = true;}
      if(CqzNbbAxLh == XciIQEjoLu){IVzOKZgpCT = true;}
      if(sfxcNQxFJj == AjxegPQKTP){gAhRMMKxFY = true;}
      if(ObUnVFYoDq == WFGAfDQEgf){akrTcoVmNE = true;}
      while(XciIQEjoLu == CqzNbbAxLh){VObKMbNegf = true;}
      while(AjxegPQKTP == AjxegPQKTP){KGzxUZyKYk = true;}
      while(WFGAfDQEgf == WFGAfDQEgf){ZCjjflgTIl = true;}
      if(ysXPnMElRw == true){ysXPnMElRw = false;}
      if(VQUkAUDohW == true){VQUkAUDohW = false;}
      if(FZNwZRVhcM == true){FZNwZRVhcM = false;}
      if(mfIfwHMhpT == true){mfIfwHMhpT = false;}
      if(LerWtFkUAK == true){LerWtFkUAK = false;}
      if(AaVKaXfaoV == true){AaVKaXfaoV = false;}
      if(pVIFIoIons == true){pVIFIoIons = false;}
      if(IVzOKZgpCT == true){IVzOKZgpCT = false;}
      if(gAhRMMKxFY == true){gAhRMMKxFY = false;}
      if(akrTcoVmNE == true){akrTcoVmNE = false;}
      if(xugHCebHzA == true){xugHCebHzA = false;}
      if(poYVnonqrw == true){poYVnonqrw = false;}
      if(eLjPRWcekV == true){eLjPRWcekV = false;}
      if(EtbyWlTZOh == true){EtbyWlTZOh = false;}
      if(jDxEhlMWem == true){jDxEhlMWem = false;}
      if(AduRYkLQpe == true){AduRYkLQpe = false;}
      if(BxVdwwMayC == true){BxVdwwMayC = false;}
      if(VObKMbNegf == true){VObKMbNegf = false;}
      if(KGzxUZyKYk == true){KGzxUZyKYk = false;}
      if(ZCjjflgTIl == true){ZCjjflgTIl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HHLVOIPAFS
{ 
  void JtLMAIKDef()
  { 
      bool ysyAzksieF = false;
      bool IpWsGRfQOC = false;
      bool fkukBOLGGz = false;
      bool gPfSZzCYPg = false;
      bool XzYNzqQgsF = false;
      bool wHcflNxNzj = false;
      bool ZlbfXsKESH = false;
      bool PHAhdgLhkJ = false;
      bool xdNACZmzgM = false;
      bool BnYeGlWsoG = false;
      bool gMOkpoHuCE = false;
      bool CPbolwYbcy = false;
      bool GKWGFahUar = false;
      bool JSreckPbKN = false;
      bool SqxbJlMisK = false;
      bool MuQqAWoHfO = false;
      bool HlTJtjXxMB = false;
      bool gxQOfOMuwT = false;
      bool OybQeOCAdF = false;
      bool uHuwGfXmgZ = false;
      string abfYSlQNdg;
      string WnxxTLqDoG;
      string fizholNJHJ;
      string aNMskRDrmY;
      string LKDWfVboiI;
      string JdNRGqcyjg;
      string XHFUFJaEMC;
      string HzPQuVebCS;
      string KYazAwzums;
      string oFHGAEEiQV;
      string uWbfAJOwWj;
      string LAwQWzgFUJ;
      string JeRTNBqJQp;
      string QwLfXmwtyp;
      string hDXChnJqjB;
      string XzNHLPFISz;
      string RFegTOoPsi;
      string ClGebFGOkY;
      string rAYORQhETI;
      string hnazXbXqiS;
      if(abfYSlQNdg == uWbfAJOwWj){ysyAzksieF = true;}
      else if(uWbfAJOwWj == abfYSlQNdg){gMOkpoHuCE = true;}
      if(WnxxTLqDoG == LAwQWzgFUJ){IpWsGRfQOC = true;}
      else if(LAwQWzgFUJ == WnxxTLqDoG){CPbolwYbcy = true;}
      if(fizholNJHJ == JeRTNBqJQp){fkukBOLGGz = true;}
      else if(JeRTNBqJQp == fizholNJHJ){GKWGFahUar = true;}
      if(aNMskRDrmY == QwLfXmwtyp){gPfSZzCYPg = true;}
      else if(QwLfXmwtyp == aNMskRDrmY){JSreckPbKN = true;}
      if(LKDWfVboiI == hDXChnJqjB){XzYNzqQgsF = true;}
      else if(hDXChnJqjB == LKDWfVboiI){SqxbJlMisK = true;}
      if(JdNRGqcyjg == XzNHLPFISz){wHcflNxNzj = true;}
      else if(XzNHLPFISz == JdNRGqcyjg){MuQqAWoHfO = true;}
      if(XHFUFJaEMC == RFegTOoPsi){ZlbfXsKESH = true;}
      else if(RFegTOoPsi == XHFUFJaEMC){HlTJtjXxMB = true;}
      if(HzPQuVebCS == ClGebFGOkY){PHAhdgLhkJ = true;}
      if(KYazAwzums == rAYORQhETI){xdNACZmzgM = true;}
      if(oFHGAEEiQV == hnazXbXqiS){BnYeGlWsoG = true;}
      while(ClGebFGOkY == HzPQuVebCS){gxQOfOMuwT = true;}
      while(rAYORQhETI == rAYORQhETI){OybQeOCAdF = true;}
      while(hnazXbXqiS == hnazXbXqiS){uHuwGfXmgZ = true;}
      if(ysyAzksieF == true){ysyAzksieF = false;}
      if(IpWsGRfQOC == true){IpWsGRfQOC = false;}
      if(fkukBOLGGz == true){fkukBOLGGz = false;}
      if(gPfSZzCYPg == true){gPfSZzCYPg = false;}
      if(XzYNzqQgsF == true){XzYNzqQgsF = false;}
      if(wHcflNxNzj == true){wHcflNxNzj = false;}
      if(ZlbfXsKESH == true){ZlbfXsKESH = false;}
      if(PHAhdgLhkJ == true){PHAhdgLhkJ = false;}
      if(xdNACZmzgM == true){xdNACZmzgM = false;}
      if(BnYeGlWsoG == true){BnYeGlWsoG = false;}
      if(gMOkpoHuCE == true){gMOkpoHuCE = false;}
      if(CPbolwYbcy == true){CPbolwYbcy = false;}
      if(GKWGFahUar == true){GKWGFahUar = false;}
      if(JSreckPbKN == true){JSreckPbKN = false;}
      if(SqxbJlMisK == true){SqxbJlMisK = false;}
      if(MuQqAWoHfO == true){MuQqAWoHfO = false;}
      if(HlTJtjXxMB == true){HlTJtjXxMB = false;}
      if(gxQOfOMuwT == true){gxQOfOMuwT = false;}
      if(OybQeOCAdF == true){OybQeOCAdF = false;}
      if(uHuwGfXmgZ == true){uHuwGfXmgZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RHTUJQKENH
{ 
  void zAsazDSAqj()
  { 
      bool hfYygKZenQ = false;
      bool PMiDTNEXAD = false;
      bool XfpmliRxeH = false;
      bool SIbMqjCFLx = false;
      bool dxkLMGmQJt = false;
      bool APnBiBpkMy = false;
      bool rczgxGjWMj = false;
      bool LyMDYZudae = false;
      bool wBmjGDTZdo = false;
      bool sQsNEBxEOG = false;
      bool WQDZiCDkcI = false;
      bool GMKgBqpPZs = false;
      bool lKsWpuFyyX = false;
      bool cpOTIexMBE = false;
      bool AixUigGLLM = false;
      bool KhdUTLXgjn = false;
      bool wElEfPxpYW = false;
      bool tdNVsDMXmI = false;
      bool nsllNuMsAw = false;
      bool HQcNHuwsoT = false;
      string wGlXhecpQa;
      string QLJZczRWsi;
      string lzbiQMBHpY;
      string XAFlzxTDru;
      string ApxbzPLCUd;
      string TuwuKxeCHU;
      string cVAqCPGWae;
      string fNeyiuBzjA;
      string BzlLFcDJbB;
      string SRwWReoFZi;
      string JnaoyGPyMO;
      string ueSGSdinlY;
      string MwtYMOQHgD;
      string GuZApNXxNy;
      string MFxNGmyoDm;
      string wBSAWNsBci;
      string oHRIIzFSQF;
      string FlanMGygSY;
      string PaDsHEbYcc;
      string TVTdIEmoFG;
      if(wGlXhecpQa == JnaoyGPyMO){hfYygKZenQ = true;}
      else if(JnaoyGPyMO == wGlXhecpQa){WQDZiCDkcI = true;}
      if(QLJZczRWsi == ueSGSdinlY){PMiDTNEXAD = true;}
      else if(ueSGSdinlY == QLJZczRWsi){GMKgBqpPZs = true;}
      if(lzbiQMBHpY == MwtYMOQHgD){XfpmliRxeH = true;}
      else if(MwtYMOQHgD == lzbiQMBHpY){lKsWpuFyyX = true;}
      if(XAFlzxTDru == GuZApNXxNy){SIbMqjCFLx = true;}
      else if(GuZApNXxNy == XAFlzxTDru){cpOTIexMBE = true;}
      if(ApxbzPLCUd == MFxNGmyoDm){dxkLMGmQJt = true;}
      else if(MFxNGmyoDm == ApxbzPLCUd){AixUigGLLM = true;}
      if(TuwuKxeCHU == wBSAWNsBci){APnBiBpkMy = true;}
      else if(wBSAWNsBci == TuwuKxeCHU){KhdUTLXgjn = true;}
      if(cVAqCPGWae == oHRIIzFSQF){rczgxGjWMj = true;}
      else if(oHRIIzFSQF == cVAqCPGWae){wElEfPxpYW = true;}
      if(fNeyiuBzjA == FlanMGygSY){LyMDYZudae = true;}
      if(BzlLFcDJbB == PaDsHEbYcc){wBmjGDTZdo = true;}
      if(SRwWReoFZi == TVTdIEmoFG){sQsNEBxEOG = true;}
      while(FlanMGygSY == fNeyiuBzjA){tdNVsDMXmI = true;}
      while(PaDsHEbYcc == PaDsHEbYcc){nsllNuMsAw = true;}
      while(TVTdIEmoFG == TVTdIEmoFG){HQcNHuwsoT = true;}
      if(hfYygKZenQ == true){hfYygKZenQ = false;}
      if(PMiDTNEXAD == true){PMiDTNEXAD = false;}
      if(XfpmliRxeH == true){XfpmliRxeH = false;}
      if(SIbMqjCFLx == true){SIbMqjCFLx = false;}
      if(dxkLMGmQJt == true){dxkLMGmQJt = false;}
      if(APnBiBpkMy == true){APnBiBpkMy = false;}
      if(rczgxGjWMj == true){rczgxGjWMj = false;}
      if(LyMDYZudae == true){LyMDYZudae = false;}
      if(wBmjGDTZdo == true){wBmjGDTZdo = false;}
      if(sQsNEBxEOG == true){sQsNEBxEOG = false;}
      if(WQDZiCDkcI == true){WQDZiCDkcI = false;}
      if(GMKgBqpPZs == true){GMKgBqpPZs = false;}
      if(lKsWpuFyyX == true){lKsWpuFyyX = false;}
      if(cpOTIexMBE == true){cpOTIexMBE = false;}
      if(AixUigGLLM == true){AixUigGLLM = false;}
      if(KhdUTLXgjn == true){KhdUTLXgjn = false;}
      if(wElEfPxpYW == true){wElEfPxpYW = false;}
      if(tdNVsDMXmI == true){tdNVsDMXmI = false;}
      if(nsllNuMsAw == true){nsllNuMsAw = false;}
      if(HQcNHuwsoT == true){HQcNHuwsoT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWQRRNZBDW
{ 
  void OejjqCojUe()
  { 
      bool BmVcswfMcL = false;
      bool qcJJWbqwgz = false;
      bool MJrIZjoAsI = false;
      bool eIaOapiTPi = false;
      bool RqQcCoBiUP = false;
      bool mltHLruMCI = false;
      bool GfSUgiCuhf = false;
      bool sXfxgUsPFk = false;
      bool hGecUsNTCh = false;
      bool uVQHclXwwT = false;
      bool mGAoWPGxZp = false;
      bool zfHRZAApzm = false;
      bool ViszjWGYUu = false;
      bool xxSlybFpGF = false;
      bool lQsLiPOzgb = false;
      bool lhwIxDMAEz = false;
      bool JgbesCMUSy = false;
      bool tKitBEohQU = false;
      bool IGrrJOAKnt = false;
      bool PFlGwEnORg = false;
      string liBBciciOY;
      string gRYWPWWybA;
      string KKmMFftTHV;
      string qniQkOFtni;
      string AhAFViFLUP;
      string mQwWtbwnuw;
      string nJasgsiIkB;
      string QbJsAbJhqV;
      string aiyqiZqLVI;
      string SRyqtpGHXb;
      string zxZTzKGDWR;
      string SNwZVFLjJG;
      string BXlchydSyJ;
      string UBKPVcIdrY;
      string TnnEpFUYVo;
      string dWxQZbKxlA;
      string fnFMxQDgDr;
      string whqkmNjhmc;
      string dEwIfxDsot;
      string RLrqrehaGY;
      if(liBBciciOY == zxZTzKGDWR){BmVcswfMcL = true;}
      else if(zxZTzKGDWR == liBBciciOY){mGAoWPGxZp = true;}
      if(gRYWPWWybA == SNwZVFLjJG){qcJJWbqwgz = true;}
      else if(SNwZVFLjJG == gRYWPWWybA){zfHRZAApzm = true;}
      if(KKmMFftTHV == BXlchydSyJ){MJrIZjoAsI = true;}
      else if(BXlchydSyJ == KKmMFftTHV){ViszjWGYUu = true;}
      if(qniQkOFtni == UBKPVcIdrY){eIaOapiTPi = true;}
      else if(UBKPVcIdrY == qniQkOFtni){xxSlybFpGF = true;}
      if(AhAFViFLUP == TnnEpFUYVo){RqQcCoBiUP = true;}
      else if(TnnEpFUYVo == AhAFViFLUP){lQsLiPOzgb = true;}
      if(mQwWtbwnuw == dWxQZbKxlA){mltHLruMCI = true;}
      else if(dWxQZbKxlA == mQwWtbwnuw){lhwIxDMAEz = true;}
      if(nJasgsiIkB == fnFMxQDgDr){GfSUgiCuhf = true;}
      else if(fnFMxQDgDr == nJasgsiIkB){JgbesCMUSy = true;}
      if(QbJsAbJhqV == whqkmNjhmc){sXfxgUsPFk = true;}
      if(aiyqiZqLVI == dEwIfxDsot){hGecUsNTCh = true;}
      if(SRyqtpGHXb == RLrqrehaGY){uVQHclXwwT = true;}
      while(whqkmNjhmc == QbJsAbJhqV){tKitBEohQU = true;}
      while(dEwIfxDsot == dEwIfxDsot){IGrrJOAKnt = true;}
      while(RLrqrehaGY == RLrqrehaGY){PFlGwEnORg = true;}
      if(BmVcswfMcL == true){BmVcswfMcL = false;}
      if(qcJJWbqwgz == true){qcJJWbqwgz = false;}
      if(MJrIZjoAsI == true){MJrIZjoAsI = false;}
      if(eIaOapiTPi == true){eIaOapiTPi = false;}
      if(RqQcCoBiUP == true){RqQcCoBiUP = false;}
      if(mltHLruMCI == true){mltHLruMCI = false;}
      if(GfSUgiCuhf == true){GfSUgiCuhf = false;}
      if(sXfxgUsPFk == true){sXfxgUsPFk = false;}
      if(hGecUsNTCh == true){hGecUsNTCh = false;}
      if(uVQHclXwwT == true){uVQHclXwwT = false;}
      if(mGAoWPGxZp == true){mGAoWPGxZp = false;}
      if(zfHRZAApzm == true){zfHRZAApzm = false;}
      if(ViszjWGYUu == true){ViszjWGYUu = false;}
      if(xxSlybFpGF == true){xxSlybFpGF = false;}
      if(lQsLiPOzgb == true){lQsLiPOzgb = false;}
      if(lhwIxDMAEz == true){lhwIxDMAEz = false;}
      if(JgbesCMUSy == true){JgbesCMUSy = false;}
      if(tKitBEohQU == true){tKitBEohQU = false;}
      if(IGrrJOAKnt == true){IGrrJOAKnt = false;}
      if(PFlGwEnORg == true){PFlGwEnORg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOPJJSVOWN
{ 
  void wVXlrsmGuA()
  { 
      bool RqKDgeSiRc = false;
      bool YiEEoeAsmx = false;
      bool PmuycCpmoS = false;
      bool MxShYobSuH = false;
      bool kFBjXcdSro = false;
      bool ptKAnduLZe = false;
      bool nfszQbPVeA = false;
      bool DhyfLKlLaA = false;
      bool XWtAbSmStu = false;
      bool sQrPSFLCSu = false;
      bool MHnrkIudnc = false;
      bool rjjZGRkrWy = false;
      bool oxbjHmpiMG = false;
      bool yirfmQiCPT = false;
      bool WIdQDIfRJB = false;
      bool TTfUGOfEky = false;
      bool RMRheIrEmp = false;
      bool ihcCafSKgy = false;
      bool GYYKmeDWYX = false;
      bool jdRQCKpwlt = false;
      string LRcCeIxDFI;
      string EoxnXCmdbr;
      string lEQBnBkkdN;
      string nSqoAdZeWB;
      string lihUXkYYGb;
      string RpqMwHAbOd;
      string WLYrUkxImt;
      string cIGZGCWwcD;
      string cLeBuxaers;
      string dxQsdZKozm;
      string mPlLzJjRGs;
      string kEyLBLgWwX;
      string JSPtQeqNuf;
      string rgwpPMZSCl;
      string NJXzHZzFrS;
      string smsbcTAquU;
      string RVVZBDHIun;
      string kNUKJAuQlq;
      string flVcmEnTMw;
      string LiXgUqmxxD;
      if(LRcCeIxDFI == mPlLzJjRGs){RqKDgeSiRc = true;}
      else if(mPlLzJjRGs == LRcCeIxDFI){MHnrkIudnc = true;}
      if(EoxnXCmdbr == kEyLBLgWwX){YiEEoeAsmx = true;}
      else if(kEyLBLgWwX == EoxnXCmdbr){rjjZGRkrWy = true;}
      if(lEQBnBkkdN == JSPtQeqNuf){PmuycCpmoS = true;}
      else if(JSPtQeqNuf == lEQBnBkkdN){oxbjHmpiMG = true;}
      if(nSqoAdZeWB == rgwpPMZSCl){MxShYobSuH = true;}
      else if(rgwpPMZSCl == nSqoAdZeWB){yirfmQiCPT = true;}
      if(lihUXkYYGb == NJXzHZzFrS){kFBjXcdSro = true;}
      else if(NJXzHZzFrS == lihUXkYYGb){WIdQDIfRJB = true;}
      if(RpqMwHAbOd == smsbcTAquU){ptKAnduLZe = true;}
      else if(smsbcTAquU == RpqMwHAbOd){TTfUGOfEky = true;}
      if(WLYrUkxImt == RVVZBDHIun){nfszQbPVeA = true;}
      else if(RVVZBDHIun == WLYrUkxImt){RMRheIrEmp = true;}
      if(cIGZGCWwcD == kNUKJAuQlq){DhyfLKlLaA = true;}
      if(cLeBuxaers == flVcmEnTMw){XWtAbSmStu = true;}
      if(dxQsdZKozm == LiXgUqmxxD){sQrPSFLCSu = true;}
      while(kNUKJAuQlq == cIGZGCWwcD){ihcCafSKgy = true;}
      while(flVcmEnTMw == flVcmEnTMw){GYYKmeDWYX = true;}
      while(LiXgUqmxxD == LiXgUqmxxD){jdRQCKpwlt = true;}
      if(RqKDgeSiRc == true){RqKDgeSiRc = false;}
      if(YiEEoeAsmx == true){YiEEoeAsmx = false;}
      if(PmuycCpmoS == true){PmuycCpmoS = false;}
      if(MxShYobSuH == true){MxShYobSuH = false;}
      if(kFBjXcdSro == true){kFBjXcdSro = false;}
      if(ptKAnduLZe == true){ptKAnduLZe = false;}
      if(nfszQbPVeA == true){nfszQbPVeA = false;}
      if(DhyfLKlLaA == true){DhyfLKlLaA = false;}
      if(XWtAbSmStu == true){XWtAbSmStu = false;}
      if(sQrPSFLCSu == true){sQrPSFLCSu = false;}
      if(MHnrkIudnc == true){MHnrkIudnc = false;}
      if(rjjZGRkrWy == true){rjjZGRkrWy = false;}
      if(oxbjHmpiMG == true){oxbjHmpiMG = false;}
      if(yirfmQiCPT == true){yirfmQiCPT = false;}
      if(WIdQDIfRJB == true){WIdQDIfRJB = false;}
      if(TTfUGOfEky == true){TTfUGOfEky = false;}
      if(RMRheIrEmp == true){RMRheIrEmp = false;}
      if(ihcCafSKgy == true){ihcCafSKgy = false;}
      if(GYYKmeDWYX == true){GYYKmeDWYX = false;}
      if(jdRQCKpwlt == true){jdRQCKpwlt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODEGRGKUER
{ 
  void QYosWRUSEe()
  { 
      bool FobeGbNqXX = false;
      bool XgYECOcYUw = false;
      bool KqgXpbkXmo = false;
      bool KmBhgaWXqt = false;
      bool FfdVOmqFRm = false;
      bool PWpTrNHEnd = false;
      bool ppEiMkeqXb = false;
      bool qEhZqdMLID = false;
      bool kfFzYnwhoS = false;
      bool SSiNEPauId = false;
      bool HAhpwKoPcN = false;
      bool BwukrJjEJY = false;
      bool nxBEJXVTVb = false;
      bool CRCeukyPDN = false;
      bool zgEbRVWxUt = false;
      bool fWkipJycfX = false;
      bool oUtAKjtQoH = false;
      bool LTAwZGsZmm = false;
      bool AXzawffSol = false;
      bool lVjfXemDQh = false;
      string QLLCqCRqik;
      string cepjJgFgEG;
      string KsnlzpcqbN;
      string gSmUsXmKUp;
      string sAFRMQVWNq;
      string wjgyzXXYDA;
      string YZPVEJqUqk;
      string ttLNMKmVZi;
      string UGcjRwkoVU;
      string AOHTRTkjNC;
      string YAfbxBXSko;
      string jByUeSweEH;
      string XCzVkemqws;
      string YCIXJUZBlP;
      string YRDgjyPmoy;
      string WGfGdWAKqR;
      string OfWrPhsaKK;
      string rurnhGySkl;
      string PzCxWSWCsm;
      string UPJUBsuLQC;
      if(QLLCqCRqik == YAfbxBXSko){FobeGbNqXX = true;}
      else if(YAfbxBXSko == QLLCqCRqik){HAhpwKoPcN = true;}
      if(cepjJgFgEG == jByUeSweEH){XgYECOcYUw = true;}
      else if(jByUeSweEH == cepjJgFgEG){BwukrJjEJY = true;}
      if(KsnlzpcqbN == XCzVkemqws){KqgXpbkXmo = true;}
      else if(XCzVkemqws == KsnlzpcqbN){nxBEJXVTVb = true;}
      if(gSmUsXmKUp == YCIXJUZBlP){KmBhgaWXqt = true;}
      else if(YCIXJUZBlP == gSmUsXmKUp){CRCeukyPDN = true;}
      if(sAFRMQVWNq == YRDgjyPmoy){FfdVOmqFRm = true;}
      else if(YRDgjyPmoy == sAFRMQVWNq){zgEbRVWxUt = true;}
      if(wjgyzXXYDA == WGfGdWAKqR){PWpTrNHEnd = true;}
      else if(WGfGdWAKqR == wjgyzXXYDA){fWkipJycfX = true;}
      if(YZPVEJqUqk == OfWrPhsaKK){ppEiMkeqXb = true;}
      else if(OfWrPhsaKK == YZPVEJqUqk){oUtAKjtQoH = true;}
      if(ttLNMKmVZi == rurnhGySkl){qEhZqdMLID = true;}
      if(UGcjRwkoVU == PzCxWSWCsm){kfFzYnwhoS = true;}
      if(AOHTRTkjNC == UPJUBsuLQC){SSiNEPauId = true;}
      while(rurnhGySkl == ttLNMKmVZi){LTAwZGsZmm = true;}
      while(PzCxWSWCsm == PzCxWSWCsm){AXzawffSol = true;}
      while(UPJUBsuLQC == UPJUBsuLQC){lVjfXemDQh = true;}
      if(FobeGbNqXX == true){FobeGbNqXX = false;}
      if(XgYECOcYUw == true){XgYECOcYUw = false;}
      if(KqgXpbkXmo == true){KqgXpbkXmo = false;}
      if(KmBhgaWXqt == true){KmBhgaWXqt = false;}
      if(FfdVOmqFRm == true){FfdVOmqFRm = false;}
      if(PWpTrNHEnd == true){PWpTrNHEnd = false;}
      if(ppEiMkeqXb == true){ppEiMkeqXb = false;}
      if(qEhZqdMLID == true){qEhZqdMLID = false;}
      if(kfFzYnwhoS == true){kfFzYnwhoS = false;}
      if(SSiNEPauId == true){SSiNEPauId = false;}
      if(HAhpwKoPcN == true){HAhpwKoPcN = false;}
      if(BwukrJjEJY == true){BwukrJjEJY = false;}
      if(nxBEJXVTVb == true){nxBEJXVTVb = false;}
      if(CRCeukyPDN == true){CRCeukyPDN = false;}
      if(zgEbRVWxUt == true){zgEbRVWxUt = false;}
      if(fWkipJycfX == true){fWkipJycfX = false;}
      if(oUtAKjtQoH == true){oUtAKjtQoH = false;}
      if(LTAwZGsZmm == true){LTAwZGsZmm = false;}
      if(AXzawffSol == true){AXzawffSol = false;}
      if(lVjfXemDQh == true){lVjfXemDQh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MLRHHEUWRB
{ 
  void eYTasfkQcC()
  { 
      bool plkSqXRWVi = false;
      bool YVgpJUiYtD = false;
      bool oqRFNxjAMU = false;
      bool aSTYJwHkem = false;
      bool IkKFQUhypq = false;
      bool rqowcyTfEt = false;
      bool mRJBIFCHfN = false;
      bool MysGtEfLns = false;
      bool OlKVbidWuK = false;
      bool bbfjzpaJxL = false;
      bool SZRcetyhBX = false;
      bool SIqLfBHnYY = false;
      bool beLVkkRIHD = false;
      bool dWNcZoThph = false;
      bool juVXrTkUEx = false;
      bool iljXjnNwqs = false;
      bool coaytutNlp = false;
      bool hZxqofJncQ = false;
      bool AxDKUrlprk = false;
      bool aWpxEuTXcw = false;
      string NCTwtBVXeY;
      string WSWxmQJrGs;
      string QJAGyuekUS;
      string gkXZWnbpHa;
      string kNIWONfIDI;
      string FACVZDBNxz;
      string WkDMrltwaz;
      string oSjfIDBdqk;
      string OVhLMfiCAS;
      string lOsHEAKwec;
      string TjgDTmPWNW;
      string CXVMjADrzL;
      string CruINaZbaI;
      string sEzOQendrZ;
      string PLocQNrgXD;
      string xRwSZbnYor;
      string NmuFdxXGuE;
      string MYzZwqCSrz;
      string hrEWKaHgoo;
      string pOnzMbQjzS;
      if(NCTwtBVXeY == TjgDTmPWNW){plkSqXRWVi = true;}
      else if(TjgDTmPWNW == NCTwtBVXeY){SZRcetyhBX = true;}
      if(WSWxmQJrGs == CXVMjADrzL){YVgpJUiYtD = true;}
      else if(CXVMjADrzL == WSWxmQJrGs){SIqLfBHnYY = true;}
      if(QJAGyuekUS == CruINaZbaI){oqRFNxjAMU = true;}
      else if(CruINaZbaI == QJAGyuekUS){beLVkkRIHD = true;}
      if(gkXZWnbpHa == sEzOQendrZ){aSTYJwHkem = true;}
      else if(sEzOQendrZ == gkXZWnbpHa){dWNcZoThph = true;}
      if(kNIWONfIDI == PLocQNrgXD){IkKFQUhypq = true;}
      else if(PLocQNrgXD == kNIWONfIDI){juVXrTkUEx = true;}
      if(FACVZDBNxz == xRwSZbnYor){rqowcyTfEt = true;}
      else if(xRwSZbnYor == FACVZDBNxz){iljXjnNwqs = true;}
      if(WkDMrltwaz == NmuFdxXGuE){mRJBIFCHfN = true;}
      else if(NmuFdxXGuE == WkDMrltwaz){coaytutNlp = true;}
      if(oSjfIDBdqk == MYzZwqCSrz){MysGtEfLns = true;}
      if(OVhLMfiCAS == hrEWKaHgoo){OlKVbidWuK = true;}
      if(lOsHEAKwec == pOnzMbQjzS){bbfjzpaJxL = true;}
      while(MYzZwqCSrz == oSjfIDBdqk){hZxqofJncQ = true;}
      while(hrEWKaHgoo == hrEWKaHgoo){AxDKUrlprk = true;}
      while(pOnzMbQjzS == pOnzMbQjzS){aWpxEuTXcw = true;}
      if(plkSqXRWVi == true){plkSqXRWVi = false;}
      if(YVgpJUiYtD == true){YVgpJUiYtD = false;}
      if(oqRFNxjAMU == true){oqRFNxjAMU = false;}
      if(aSTYJwHkem == true){aSTYJwHkem = false;}
      if(IkKFQUhypq == true){IkKFQUhypq = false;}
      if(rqowcyTfEt == true){rqowcyTfEt = false;}
      if(mRJBIFCHfN == true){mRJBIFCHfN = false;}
      if(MysGtEfLns == true){MysGtEfLns = false;}
      if(OlKVbidWuK == true){OlKVbidWuK = false;}
      if(bbfjzpaJxL == true){bbfjzpaJxL = false;}
      if(SZRcetyhBX == true){SZRcetyhBX = false;}
      if(SIqLfBHnYY == true){SIqLfBHnYY = false;}
      if(beLVkkRIHD == true){beLVkkRIHD = false;}
      if(dWNcZoThph == true){dWNcZoThph = false;}
      if(juVXrTkUEx == true){juVXrTkUEx = false;}
      if(iljXjnNwqs == true){iljXjnNwqs = false;}
      if(coaytutNlp == true){coaytutNlp = false;}
      if(hZxqofJncQ == true){hZxqofJncQ = false;}
      if(AxDKUrlprk == true){AxDKUrlprk = false;}
      if(aWpxEuTXcw == true){aWpxEuTXcw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHGSLXNBMV
{ 
  void SLLKtyihmJ()
  { 
      bool TrBTOlRrFQ = false;
      bool oTtdlqjmsW = false;
      bool ElkDXCfOrp = false;
      bool qyZoEhJmXd = false;
      bool XfPxAAQaQD = false;
      bool jXMfugHyuL = false;
      bool GCAOYptFYE = false;
      bool gwPPzXWmDW = false;
      bool lExnGTlstX = false;
      bool ZLrLXUfBYJ = false;
      bool GLCMWmHwgX = false;
      bool KTuXZBFLIF = false;
      bool EAKBdVEEre = false;
      bool qVOsPZCkRS = false;
      bool LoMVMGQTkV = false;
      bool OUrSFGAAhA = false;
      bool iCECfoECHA = false;
      bool yTsptOmonW = false;
      bool FjTVPWcwmJ = false;
      bool ZBCRiIkKoX = false;
      string rTtRDqexrQ;
      string cwPAAyeftY;
      string hjESqlhbUy;
      string XNPYUiDznt;
      string TsMfYtfiSZ;
      string pBnCYHPbZR;
      string ICbtsOfqfR;
      string tfqAFoXXsx;
      string GzJuIVZMzM;
      string SbYWkQQRmJ;
      string NnDBeKKnxj;
      string iricKJsglW;
      string oTrSzSHTOn;
      string XFkiiRuHPy;
      string LlPOcaruMb;
      string XifPUswjCM;
      string CqZJLdGzss;
      string NkRmKDEcoX;
      string ZLGlPoYUOo;
      string ULFDuULFCz;
      if(rTtRDqexrQ == NnDBeKKnxj){TrBTOlRrFQ = true;}
      else if(NnDBeKKnxj == rTtRDqexrQ){GLCMWmHwgX = true;}
      if(cwPAAyeftY == iricKJsglW){oTtdlqjmsW = true;}
      else if(iricKJsglW == cwPAAyeftY){KTuXZBFLIF = true;}
      if(hjESqlhbUy == oTrSzSHTOn){ElkDXCfOrp = true;}
      else if(oTrSzSHTOn == hjESqlhbUy){EAKBdVEEre = true;}
      if(XNPYUiDznt == XFkiiRuHPy){qyZoEhJmXd = true;}
      else if(XFkiiRuHPy == XNPYUiDznt){qVOsPZCkRS = true;}
      if(TsMfYtfiSZ == LlPOcaruMb){XfPxAAQaQD = true;}
      else if(LlPOcaruMb == TsMfYtfiSZ){LoMVMGQTkV = true;}
      if(pBnCYHPbZR == XifPUswjCM){jXMfugHyuL = true;}
      else if(XifPUswjCM == pBnCYHPbZR){OUrSFGAAhA = true;}
      if(ICbtsOfqfR == CqZJLdGzss){GCAOYptFYE = true;}
      else if(CqZJLdGzss == ICbtsOfqfR){iCECfoECHA = true;}
      if(tfqAFoXXsx == NkRmKDEcoX){gwPPzXWmDW = true;}
      if(GzJuIVZMzM == ZLGlPoYUOo){lExnGTlstX = true;}
      if(SbYWkQQRmJ == ULFDuULFCz){ZLrLXUfBYJ = true;}
      while(NkRmKDEcoX == tfqAFoXXsx){yTsptOmonW = true;}
      while(ZLGlPoYUOo == ZLGlPoYUOo){FjTVPWcwmJ = true;}
      while(ULFDuULFCz == ULFDuULFCz){ZBCRiIkKoX = true;}
      if(TrBTOlRrFQ == true){TrBTOlRrFQ = false;}
      if(oTtdlqjmsW == true){oTtdlqjmsW = false;}
      if(ElkDXCfOrp == true){ElkDXCfOrp = false;}
      if(qyZoEhJmXd == true){qyZoEhJmXd = false;}
      if(XfPxAAQaQD == true){XfPxAAQaQD = false;}
      if(jXMfugHyuL == true){jXMfugHyuL = false;}
      if(GCAOYptFYE == true){GCAOYptFYE = false;}
      if(gwPPzXWmDW == true){gwPPzXWmDW = false;}
      if(lExnGTlstX == true){lExnGTlstX = false;}
      if(ZLrLXUfBYJ == true){ZLrLXUfBYJ = false;}
      if(GLCMWmHwgX == true){GLCMWmHwgX = false;}
      if(KTuXZBFLIF == true){KTuXZBFLIF = false;}
      if(EAKBdVEEre == true){EAKBdVEEre = false;}
      if(qVOsPZCkRS == true){qVOsPZCkRS = false;}
      if(LoMVMGQTkV == true){LoMVMGQTkV = false;}
      if(OUrSFGAAhA == true){OUrSFGAAhA = false;}
      if(iCECfoECHA == true){iCECfoECHA = false;}
      if(yTsptOmonW == true){yTsptOmonW = false;}
      if(FjTVPWcwmJ == true){FjTVPWcwmJ = false;}
      if(ZBCRiIkKoX == true){ZBCRiIkKoX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQKOOYTKQC
{ 
  void ZMnAPYXPfj()
  { 
      bool UdVrltwPLX = false;
      bool rawYGdibBa = false;
      bool JCTNDglwoS = false;
      bool SBLeQmSSfR = false;
      bool qQTLYBauah = false;
      bool XcHmMRJIoE = false;
      bool IAarFqOQHT = false;
      bool KQujisiIoC = false;
      bool GpVHuosYSz = false;
      bool cKdbJqpbGg = false;
      bool lJnGWHhXDT = false;
      bool hBSlyReTxP = false;
      bool ypyIqzmTZr = false;
      bool CHCIQwCOjm = false;
      bool HUUzQbrqdr = false;
      bool MWdphuLfPX = false;
      bool UNxLQazKVB = false;
      bool OPiJIcUzqO = false;
      bool HuphefcLZU = false;
      bool kWyMSsWJho = false;
      string MipmgbgaKf;
      string GNeOdYygxz;
      string BVCBeuRTOn;
      string YdcRtkHHRY;
      string zYWVyXPhqm;
      string zsabIpgnHl;
      string JNMWHbjMTr;
      string QpPXzczfDH;
      string ejcboeDAJE;
      string ESAfPlMANV;
      string mDNyVJdCbf;
      string pAkzHZkjhb;
      string YiDPnypjIN;
      string PzRgUbVdFf;
      string BAYdNDhAXp;
      string BbRlxDAyJX;
      string SttOPqiDee;
      string EGeBZYKYBk;
      string QoLRMngfjQ;
      string bWThMGFJNW;
      if(MipmgbgaKf == mDNyVJdCbf){UdVrltwPLX = true;}
      else if(mDNyVJdCbf == MipmgbgaKf){lJnGWHhXDT = true;}
      if(GNeOdYygxz == pAkzHZkjhb){rawYGdibBa = true;}
      else if(pAkzHZkjhb == GNeOdYygxz){hBSlyReTxP = true;}
      if(BVCBeuRTOn == YiDPnypjIN){JCTNDglwoS = true;}
      else if(YiDPnypjIN == BVCBeuRTOn){ypyIqzmTZr = true;}
      if(YdcRtkHHRY == PzRgUbVdFf){SBLeQmSSfR = true;}
      else if(PzRgUbVdFf == YdcRtkHHRY){CHCIQwCOjm = true;}
      if(zYWVyXPhqm == BAYdNDhAXp){qQTLYBauah = true;}
      else if(BAYdNDhAXp == zYWVyXPhqm){HUUzQbrqdr = true;}
      if(zsabIpgnHl == BbRlxDAyJX){XcHmMRJIoE = true;}
      else if(BbRlxDAyJX == zsabIpgnHl){MWdphuLfPX = true;}
      if(JNMWHbjMTr == SttOPqiDee){IAarFqOQHT = true;}
      else if(SttOPqiDee == JNMWHbjMTr){UNxLQazKVB = true;}
      if(QpPXzczfDH == EGeBZYKYBk){KQujisiIoC = true;}
      if(ejcboeDAJE == QoLRMngfjQ){GpVHuosYSz = true;}
      if(ESAfPlMANV == bWThMGFJNW){cKdbJqpbGg = true;}
      while(EGeBZYKYBk == QpPXzczfDH){OPiJIcUzqO = true;}
      while(QoLRMngfjQ == QoLRMngfjQ){HuphefcLZU = true;}
      while(bWThMGFJNW == bWThMGFJNW){kWyMSsWJho = true;}
      if(UdVrltwPLX == true){UdVrltwPLX = false;}
      if(rawYGdibBa == true){rawYGdibBa = false;}
      if(JCTNDglwoS == true){JCTNDglwoS = false;}
      if(SBLeQmSSfR == true){SBLeQmSSfR = false;}
      if(qQTLYBauah == true){qQTLYBauah = false;}
      if(XcHmMRJIoE == true){XcHmMRJIoE = false;}
      if(IAarFqOQHT == true){IAarFqOQHT = false;}
      if(KQujisiIoC == true){KQujisiIoC = false;}
      if(GpVHuosYSz == true){GpVHuosYSz = false;}
      if(cKdbJqpbGg == true){cKdbJqpbGg = false;}
      if(lJnGWHhXDT == true){lJnGWHhXDT = false;}
      if(hBSlyReTxP == true){hBSlyReTxP = false;}
      if(ypyIqzmTZr == true){ypyIqzmTZr = false;}
      if(CHCIQwCOjm == true){CHCIQwCOjm = false;}
      if(HUUzQbrqdr == true){HUUzQbrqdr = false;}
      if(MWdphuLfPX == true){MWdphuLfPX = false;}
      if(UNxLQazKVB == true){UNxLQazKVB = false;}
      if(OPiJIcUzqO == true){OPiJIcUzqO = false;}
      if(HuphefcLZU == true){HuphefcLZU = false;}
      if(kWyMSsWJho == true){kWyMSsWJho = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RAZYBBPCRB
{ 
  void lFdVbRFqgL()
  { 
      bool ZmpQnoapPn = false;
      bool lQUkbEMEYi = false;
      bool QlNsPxnuKY = false;
      bool oXebtIcSXP = false;
      bool TFFxhzkqgx = false;
      bool kdcbjmYxBp = false;
      bool BfepzOksqS = false;
      bool atfIOKgPKQ = false;
      bool MxNMmKtDqG = false;
      bool ifRhOnZOyS = false;
      bool NqzOWqxUNY = false;
      bool GIljcESRDn = false;
      bool UhBjitcysa = false;
      bool kRRrCVxzpw = false;
      bool MZoSAatgEK = false;
      bool VHLJyeoOeb = false;
      bool NzamnoqthH = false;
      bool GSbGausijI = false;
      bool AwtiFcFHsW = false;
      bool fhTNhNyCdK = false;
      string lxDtxywroY;
      string pGZpnwOyGL;
      string kkORyfxFRi;
      string gubwZjYsRB;
      string urwxfxSENd;
      string OJZFzAiluQ;
      string BqZGqtdcPE;
      string WUgEPsoQkB;
      string NsqnTXVWwZ;
      string BmyAAERoGl;
      string TonIGtcUoG;
      string LSAtDIzllS;
      string YHgpDiWfEK;
      string bzJzgXEhgZ;
      string uAgpNimDwr;
      string FfDnMMHyFX;
      string XwQdeMIANf;
      string DQEMXYZqcT;
      string uSiMFuwVlU;
      string PGcJByiCLA;
      if(lxDtxywroY == TonIGtcUoG){ZmpQnoapPn = true;}
      else if(TonIGtcUoG == lxDtxywroY){NqzOWqxUNY = true;}
      if(pGZpnwOyGL == LSAtDIzllS){lQUkbEMEYi = true;}
      else if(LSAtDIzllS == pGZpnwOyGL){GIljcESRDn = true;}
      if(kkORyfxFRi == YHgpDiWfEK){QlNsPxnuKY = true;}
      else if(YHgpDiWfEK == kkORyfxFRi){UhBjitcysa = true;}
      if(gubwZjYsRB == bzJzgXEhgZ){oXebtIcSXP = true;}
      else if(bzJzgXEhgZ == gubwZjYsRB){kRRrCVxzpw = true;}
      if(urwxfxSENd == uAgpNimDwr){TFFxhzkqgx = true;}
      else if(uAgpNimDwr == urwxfxSENd){MZoSAatgEK = true;}
      if(OJZFzAiluQ == FfDnMMHyFX){kdcbjmYxBp = true;}
      else if(FfDnMMHyFX == OJZFzAiluQ){VHLJyeoOeb = true;}
      if(BqZGqtdcPE == XwQdeMIANf){BfepzOksqS = true;}
      else if(XwQdeMIANf == BqZGqtdcPE){NzamnoqthH = true;}
      if(WUgEPsoQkB == DQEMXYZqcT){atfIOKgPKQ = true;}
      if(NsqnTXVWwZ == uSiMFuwVlU){MxNMmKtDqG = true;}
      if(BmyAAERoGl == PGcJByiCLA){ifRhOnZOyS = true;}
      while(DQEMXYZqcT == WUgEPsoQkB){GSbGausijI = true;}
      while(uSiMFuwVlU == uSiMFuwVlU){AwtiFcFHsW = true;}
      while(PGcJByiCLA == PGcJByiCLA){fhTNhNyCdK = true;}
      if(ZmpQnoapPn == true){ZmpQnoapPn = false;}
      if(lQUkbEMEYi == true){lQUkbEMEYi = false;}
      if(QlNsPxnuKY == true){QlNsPxnuKY = false;}
      if(oXebtIcSXP == true){oXebtIcSXP = false;}
      if(TFFxhzkqgx == true){TFFxhzkqgx = false;}
      if(kdcbjmYxBp == true){kdcbjmYxBp = false;}
      if(BfepzOksqS == true){BfepzOksqS = false;}
      if(atfIOKgPKQ == true){atfIOKgPKQ = false;}
      if(MxNMmKtDqG == true){MxNMmKtDqG = false;}
      if(ifRhOnZOyS == true){ifRhOnZOyS = false;}
      if(NqzOWqxUNY == true){NqzOWqxUNY = false;}
      if(GIljcESRDn == true){GIljcESRDn = false;}
      if(UhBjitcysa == true){UhBjitcysa = false;}
      if(kRRrCVxzpw == true){kRRrCVxzpw = false;}
      if(MZoSAatgEK == true){MZoSAatgEK = false;}
      if(VHLJyeoOeb == true){VHLJyeoOeb = false;}
      if(NzamnoqthH == true){NzamnoqthH = false;}
      if(GSbGausijI == true){GSbGausijI = false;}
      if(AwtiFcFHsW == true){AwtiFcFHsW = false;}
      if(fhTNhNyCdK == true){fhTNhNyCdK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEITWGXHKT
{ 
  void rJaMzXyXYo()
  { 
      bool UCNEwUpAym = false;
      bool zNrtuyYaDR = false;
      bool raMfVWlpEI = false;
      bool iigCwZFzjd = false;
      bool DdsFPGtYwa = false;
      bool OpaHxtogiZ = false;
      bool hzupEQfoxU = false;
      bool sYqYNOhHQO = false;
      bool bNtdsrHZFC = false;
      bool kXQKwEiDBz = false;
      bool aFabhpzBsi = false;
      bool MgQTxUERwM = false;
      bool IGiuiUHgcJ = false;
      bool feFQnWlSuD = false;
      bool rFfWpDHxMb = false;
      bool zQGopTVfrM = false;
      bool hRYiDgbzfZ = false;
      bool hlVrTCaMFe = false;
      bool MKTBKOXQaU = false;
      bool AGZiUagwSI = false;
      string PdqFzxBiBM;
      string dgcmESCmDh;
      string bWWFxQDSOr;
      string BjaZmCiqKf;
      string woKWINOpTq;
      string GFRPNsHlIh;
      string siUIKsFCzB;
      string iLbXllLzxj;
      string BNyXluSKLt;
      string uxhblMUBLO;
      string HLpSItdscb;
      string gHoYgfkxWP;
      string atqFGkcAlZ;
      string QJnhbpWeOq;
      string RZgjMnIJuF;
      string aXewnMUjMW;
      string RdHDKWSGwp;
      string JFhexANGrR;
      string bSEfzsersP;
      string UlSqZnRdYp;
      if(PdqFzxBiBM == HLpSItdscb){UCNEwUpAym = true;}
      else if(HLpSItdscb == PdqFzxBiBM){aFabhpzBsi = true;}
      if(dgcmESCmDh == gHoYgfkxWP){zNrtuyYaDR = true;}
      else if(gHoYgfkxWP == dgcmESCmDh){MgQTxUERwM = true;}
      if(bWWFxQDSOr == atqFGkcAlZ){raMfVWlpEI = true;}
      else if(atqFGkcAlZ == bWWFxQDSOr){IGiuiUHgcJ = true;}
      if(BjaZmCiqKf == QJnhbpWeOq){iigCwZFzjd = true;}
      else if(QJnhbpWeOq == BjaZmCiqKf){feFQnWlSuD = true;}
      if(woKWINOpTq == RZgjMnIJuF){DdsFPGtYwa = true;}
      else if(RZgjMnIJuF == woKWINOpTq){rFfWpDHxMb = true;}
      if(GFRPNsHlIh == aXewnMUjMW){OpaHxtogiZ = true;}
      else if(aXewnMUjMW == GFRPNsHlIh){zQGopTVfrM = true;}
      if(siUIKsFCzB == RdHDKWSGwp){hzupEQfoxU = true;}
      else if(RdHDKWSGwp == siUIKsFCzB){hRYiDgbzfZ = true;}
      if(iLbXllLzxj == JFhexANGrR){sYqYNOhHQO = true;}
      if(BNyXluSKLt == bSEfzsersP){bNtdsrHZFC = true;}
      if(uxhblMUBLO == UlSqZnRdYp){kXQKwEiDBz = true;}
      while(JFhexANGrR == iLbXllLzxj){hlVrTCaMFe = true;}
      while(bSEfzsersP == bSEfzsersP){MKTBKOXQaU = true;}
      while(UlSqZnRdYp == UlSqZnRdYp){AGZiUagwSI = true;}
      if(UCNEwUpAym == true){UCNEwUpAym = false;}
      if(zNrtuyYaDR == true){zNrtuyYaDR = false;}
      if(raMfVWlpEI == true){raMfVWlpEI = false;}
      if(iigCwZFzjd == true){iigCwZFzjd = false;}
      if(DdsFPGtYwa == true){DdsFPGtYwa = false;}
      if(OpaHxtogiZ == true){OpaHxtogiZ = false;}
      if(hzupEQfoxU == true){hzupEQfoxU = false;}
      if(sYqYNOhHQO == true){sYqYNOhHQO = false;}
      if(bNtdsrHZFC == true){bNtdsrHZFC = false;}
      if(kXQKwEiDBz == true){kXQKwEiDBz = false;}
      if(aFabhpzBsi == true){aFabhpzBsi = false;}
      if(MgQTxUERwM == true){MgQTxUERwM = false;}
      if(IGiuiUHgcJ == true){IGiuiUHgcJ = false;}
      if(feFQnWlSuD == true){feFQnWlSuD = false;}
      if(rFfWpDHxMb == true){rFfWpDHxMb = false;}
      if(zQGopTVfrM == true){zQGopTVfrM = false;}
      if(hRYiDgbzfZ == true){hRYiDgbzfZ = false;}
      if(hlVrTCaMFe == true){hlVrTCaMFe = false;}
      if(MKTBKOXQaU == true){MKTBKOXQaU = false;}
      if(AGZiUagwSI == true){AGZiUagwSI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANBQUVKGWY
{ 
  void YufrYMcOjw()
  { 
      bool fLrbVhqQiQ = false;
      bool TnPJwQyadj = false;
      bool VsrlLqZwRa = false;
      bool eNKJZlMxEH = false;
      bool jwAlVcpNbI = false;
      bool yyemUmSFPe = false;
      bool IuzIlFcFiJ = false;
      bool EAWWzZrGPi = false;
      bool AMUIcgiXnm = false;
      bool TGhZzowrzP = false;
      bool zjdRDxaHnu = false;
      bool tMogdwZpfF = false;
      bool WFQupxSxXJ = false;
      bool cAGziPhCFe = false;
      bool FajssGQAuD = false;
      bool OGMtstThbF = false;
      bool ddieStFpxN = false;
      bool NXkAAuVXCi = false;
      bool gRBUtWmMGo = false;
      bool wzZzAaqFay = false;
      string oUQQMmAFLm;
      string CGeorwPPCy;
      string ybGZiSFxyl;
      string YAncnuQLPU;
      string QHQOBJqrde;
      string xCcVrNNphs;
      string hCGYOBSCBx;
      string eDAghpLrXY;
      string bNTSnWWRka;
      string gZdVmNBqzz;
      string qnpgztBunB;
      string BVSJQTinjr;
      string eARZQFYdtT;
      string oTrXgnWlSt;
      string UaciYKGUES;
      string eMGHUqWQPt;
      string UXBTMhdubc;
      string xwUpXDWhAG;
      string yEYaobMjCp;
      string QGWXYwYJWq;
      if(oUQQMmAFLm == qnpgztBunB){fLrbVhqQiQ = true;}
      else if(qnpgztBunB == oUQQMmAFLm){zjdRDxaHnu = true;}
      if(CGeorwPPCy == BVSJQTinjr){TnPJwQyadj = true;}
      else if(BVSJQTinjr == CGeorwPPCy){tMogdwZpfF = true;}
      if(ybGZiSFxyl == eARZQFYdtT){VsrlLqZwRa = true;}
      else if(eARZQFYdtT == ybGZiSFxyl){WFQupxSxXJ = true;}
      if(YAncnuQLPU == oTrXgnWlSt){eNKJZlMxEH = true;}
      else if(oTrXgnWlSt == YAncnuQLPU){cAGziPhCFe = true;}
      if(QHQOBJqrde == UaciYKGUES){jwAlVcpNbI = true;}
      else if(UaciYKGUES == QHQOBJqrde){FajssGQAuD = true;}
      if(xCcVrNNphs == eMGHUqWQPt){yyemUmSFPe = true;}
      else if(eMGHUqWQPt == xCcVrNNphs){OGMtstThbF = true;}
      if(hCGYOBSCBx == UXBTMhdubc){IuzIlFcFiJ = true;}
      else if(UXBTMhdubc == hCGYOBSCBx){ddieStFpxN = true;}
      if(eDAghpLrXY == xwUpXDWhAG){EAWWzZrGPi = true;}
      if(bNTSnWWRka == yEYaobMjCp){AMUIcgiXnm = true;}
      if(gZdVmNBqzz == QGWXYwYJWq){TGhZzowrzP = true;}
      while(xwUpXDWhAG == eDAghpLrXY){NXkAAuVXCi = true;}
      while(yEYaobMjCp == yEYaobMjCp){gRBUtWmMGo = true;}
      while(QGWXYwYJWq == QGWXYwYJWq){wzZzAaqFay = true;}
      if(fLrbVhqQiQ == true){fLrbVhqQiQ = false;}
      if(TnPJwQyadj == true){TnPJwQyadj = false;}
      if(VsrlLqZwRa == true){VsrlLqZwRa = false;}
      if(eNKJZlMxEH == true){eNKJZlMxEH = false;}
      if(jwAlVcpNbI == true){jwAlVcpNbI = false;}
      if(yyemUmSFPe == true){yyemUmSFPe = false;}
      if(IuzIlFcFiJ == true){IuzIlFcFiJ = false;}
      if(EAWWzZrGPi == true){EAWWzZrGPi = false;}
      if(AMUIcgiXnm == true){AMUIcgiXnm = false;}
      if(TGhZzowrzP == true){TGhZzowrzP = false;}
      if(zjdRDxaHnu == true){zjdRDxaHnu = false;}
      if(tMogdwZpfF == true){tMogdwZpfF = false;}
      if(WFQupxSxXJ == true){WFQupxSxXJ = false;}
      if(cAGziPhCFe == true){cAGziPhCFe = false;}
      if(FajssGQAuD == true){FajssGQAuD = false;}
      if(OGMtstThbF == true){OGMtstThbF = false;}
      if(ddieStFpxN == true){ddieStFpxN = false;}
      if(NXkAAuVXCi == true){NXkAAuVXCi = false;}
      if(gRBUtWmMGo == true){gRBUtWmMGo = false;}
      if(wzZzAaqFay == true){wzZzAaqFay = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSVTCIPZTQ
{ 
  void NDTOAHIeFa()
  { 
      bool OgCDjnlVlM = false;
      bool AWXIOhjIrs = false;
      bool pTuxfksEjB = false;
      bool chhUsdmlhG = false;
      bool gBQimbOQRc = false;
      bool cNWnaulEWy = false;
      bool tgkkiRoCPj = false;
      bool tyalMnCLKD = false;
      bool VcmGXOLstx = false;
      bool riOiLzPfzU = false;
      bool mMAgielkal = false;
      bool sZsTcRtdMU = false;
      bool GuISrLirZN = false;
      bool YWMoPJcGXr = false;
      bool bZRHERouGt = false;
      bool FlSeOqEhoW = false;
      bool wtKNNWNEDT = false;
      bool nnFUrgdANZ = false;
      bool WnlfImDhaY = false;
      bool EtQBwhOEth = false;
      string plnhtDXlps;
      string yqSZBtHVgq;
      string YACWZsFOfa;
      string ECzIYwmSzc;
      string YTNsFpIdPP;
      string pTEHIpjQHA;
      string yIGPnuqKBF;
      string GnVESEmJRj;
      string jazPjkxqzi;
      string LWKyePNxEJ;
      string yycJJBxAoD;
      string DayWQWIpeD;
      string xALRsjcXZC;
      string poEHllypFi;
      string nxCuekXnhI;
      string HWRBMymKQZ;
      string XZamMNVpke;
      string YSkwPzxPmH;
      string LooRtTXCum;
      string zmYfLNWPhR;
      if(plnhtDXlps == yycJJBxAoD){OgCDjnlVlM = true;}
      else if(yycJJBxAoD == plnhtDXlps){mMAgielkal = true;}
      if(yqSZBtHVgq == DayWQWIpeD){AWXIOhjIrs = true;}
      else if(DayWQWIpeD == yqSZBtHVgq){sZsTcRtdMU = true;}
      if(YACWZsFOfa == xALRsjcXZC){pTuxfksEjB = true;}
      else if(xALRsjcXZC == YACWZsFOfa){GuISrLirZN = true;}
      if(ECzIYwmSzc == poEHllypFi){chhUsdmlhG = true;}
      else if(poEHllypFi == ECzIYwmSzc){YWMoPJcGXr = true;}
      if(YTNsFpIdPP == nxCuekXnhI){gBQimbOQRc = true;}
      else if(nxCuekXnhI == YTNsFpIdPP){bZRHERouGt = true;}
      if(pTEHIpjQHA == HWRBMymKQZ){cNWnaulEWy = true;}
      else if(HWRBMymKQZ == pTEHIpjQHA){FlSeOqEhoW = true;}
      if(yIGPnuqKBF == XZamMNVpke){tgkkiRoCPj = true;}
      else if(XZamMNVpke == yIGPnuqKBF){wtKNNWNEDT = true;}
      if(GnVESEmJRj == YSkwPzxPmH){tyalMnCLKD = true;}
      if(jazPjkxqzi == LooRtTXCum){VcmGXOLstx = true;}
      if(LWKyePNxEJ == zmYfLNWPhR){riOiLzPfzU = true;}
      while(YSkwPzxPmH == GnVESEmJRj){nnFUrgdANZ = true;}
      while(LooRtTXCum == LooRtTXCum){WnlfImDhaY = true;}
      while(zmYfLNWPhR == zmYfLNWPhR){EtQBwhOEth = true;}
      if(OgCDjnlVlM == true){OgCDjnlVlM = false;}
      if(AWXIOhjIrs == true){AWXIOhjIrs = false;}
      if(pTuxfksEjB == true){pTuxfksEjB = false;}
      if(chhUsdmlhG == true){chhUsdmlhG = false;}
      if(gBQimbOQRc == true){gBQimbOQRc = false;}
      if(cNWnaulEWy == true){cNWnaulEWy = false;}
      if(tgkkiRoCPj == true){tgkkiRoCPj = false;}
      if(tyalMnCLKD == true){tyalMnCLKD = false;}
      if(VcmGXOLstx == true){VcmGXOLstx = false;}
      if(riOiLzPfzU == true){riOiLzPfzU = false;}
      if(mMAgielkal == true){mMAgielkal = false;}
      if(sZsTcRtdMU == true){sZsTcRtdMU = false;}
      if(GuISrLirZN == true){GuISrLirZN = false;}
      if(YWMoPJcGXr == true){YWMoPJcGXr = false;}
      if(bZRHERouGt == true){bZRHERouGt = false;}
      if(FlSeOqEhoW == true){FlSeOqEhoW = false;}
      if(wtKNNWNEDT == true){wtKNNWNEDT = false;}
      if(nnFUrgdANZ == true){nnFUrgdANZ = false;}
      if(WnlfImDhaY == true){WnlfImDhaY = false;}
      if(EtQBwhOEth == true){EtQBwhOEth = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBLIMJIHBD
{ 
  void LGlzOUuteu()
  { 
      bool xMUTggCaNg = false;
      bool LlcqtthaVy = false;
      bool uFMmysizCs = false;
      bool OKcMliNkpW = false;
      bool deyCTbODQh = false;
      bool NGjYcqzhUn = false;
      bool xCYURAIQFK = false;
      bool gwkyTPHKTW = false;
      bool dfiTfHZEjt = false;
      bool jePCYbGdjS = false;
      bool SxyFBQUlEM = false;
      bool jnOyJQSEoJ = false;
      bool ZDgKaBgiYq = false;
      bool JcZADfhcSO = false;
      bool mnAWJuQRrH = false;
      bool IBoZrPQmez = false;
      bool jlMNDGNNtc = false;
      bool ipkZWlDKAe = false;
      bool jOpRhHnAIn = false;
      bool PtyTeAblSD = false;
      string DxxeBjJTff;
      string BArHGNEWhd;
      string zkgVXBKPLo;
      string GEiQGLrUsj;
      string EfgwDpObUP;
      string jBkOqRPaGA;
      string ZtHpZwRaAu;
      string UjdyZSDjSg;
      string mhuuFETUZo;
      string uQNsJKYqWG;
      string YmaZtzXmnY;
      string OfIZMrzLkU;
      string cwBLzEWknO;
      string sMNMHAGUBF;
      string gffBZPImfR;
      string LMGBcclOap;
      string clyZeBRwRM;
      string kdKenwQAki;
      string uiEWDgGLie;
      string NrtKcuhGWY;
      if(DxxeBjJTff == YmaZtzXmnY){xMUTggCaNg = true;}
      else if(YmaZtzXmnY == DxxeBjJTff){SxyFBQUlEM = true;}
      if(BArHGNEWhd == OfIZMrzLkU){LlcqtthaVy = true;}
      else if(OfIZMrzLkU == BArHGNEWhd){jnOyJQSEoJ = true;}
      if(zkgVXBKPLo == cwBLzEWknO){uFMmysizCs = true;}
      else if(cwBLzEWknO == zkgVXBKPLo){ZDgKaBgiYq = true;}
      if(GEiQGLrUsj == sMNMHAGUBF){OKcMliNkpW = true;}
      else if(sMNMHAGUBF == GEiQGLrUsj){JcZADfhcSO = true;}
      if(EfgwDpObUP == gffBZPImfR){deyCTbODQh = true;}
      else if(gffBZPImfR == EfgwDpObUP){mnAWJuQRrH = true;}
      if(jBkOqRPaGA == LMGBcclOap){NGjYcqzhUn = true;}
      else if(LMGBcclOap == jBkOqRPaGA){IBoZrPQmez = true;}
      if(ZtHpZwRaAu == clyZeBRwRM){xCYURAIQFK = true;}
      else if(clyZeBRwRM == ZtHpZwRaAu){jlMNDGNNtc = true;}
      if(UjdyZSDjSg == kdKenwQAki){gwkyTPHKTW = true;}
      if(mhuuFETUZo == uiEWDgGLie){dfiTfHZEjt = true;}
      if(uQNsJKYqWG == NrtKcuhGWY){jePCYbGdjS = true;}
      while(kdKenwQAki == UjdyZSDjSg){ipkZWlDKAe = true;}
      while(uiEWDgGLie == uiEWDgGLie){jOpRhHnAIn = true;}
      while(NrtKcuhGWY == NrtKcuhGWY){PtyTeAblSD = true;}
      if(xMUTggCaNg == true){xMUTggCaNg = false;}
      if(LlcqtthaVy == true){LlcqtthaVy = false;}
      if(uFMmysizCs == true){uFMmysizCs = false;}
      if(OKcMliNkpW == true){OKcMliNkpW = false;}
      if(deyCTbODQh == true){deyCTbODQh = false;}
      if(NGjYcqzhUn == true){NGjYcqzhUn = false;}
      if(xCYURAIQFK == true){xCYURAIQFK = false;}
      if(gwkyTPHKTW == true){gwkyTPHKTW = false;}
      if(dfiTfHZEjt == true){dfiTfHZEjt = false;}
      if(jePCYbGdjS == true){jePCYbGdjS = false;}
      if(SxyFBQUlEM == true){SxyFBQUlEM = false;}
      if(jnOyJQSEoJ == true){jnOyJQSEoJ = false;}
      if(ZDgKaBgiYq == true){ZDgKaBgiYq = false;}
      if(JcZADfhcSO == true){JcZADfhcSO = false;}
      if(mnAWJuQRrH == true){mnAWJuQRrH = false;}
      if(IBoZrPQmez == true){IBoZrPQmez = false;}
      if(jlMNDGNNtc == true){jlMNDGNNtc = false;}
      if(ipkZWlDKAe == true){ipkZWlDKAe = false;}
      if(jOpRhHnAIn == true){jOpRhHnAIn = false;}
      if(PtyTeAblSD == true){PtyTeAblSD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKNYLYZWUT
{ 
  void wXQCOisqYe()
  { 
      bool yNckJncFZr = false;
      bool UirEXPBhQc = false;
      bool hDQdFcruQa = false;
      bool SsQJbleaVg = false;
      bool IzPxgkZGWd = false;
      bool gluODtwyef = false;
      bool uhnzZaRibl = false;
      bool kZLiTimSxT = false;
      bool DkYlsfyCGh = false;
      bool ofuokaKQXF = false;
      bool TpdjsHaLtT = false;
      bool HdBKcKICFs = false;
      bool cPctwEdWxs = false;
      bool YVuqAMGnsl = false;
      bool FlHlaLejMa = false;
      bool RHLdcENjnn = false;
      bool cENBukiJKP = false;
      bool DUISnpIpTk = false;
      bool ZsKWbQKQOw = false;
      bool zWAEIBXFpp = false;
      string UdVzlhEgWY;
      string PxaAeNPdLU;
      string YyrVkbSUQi;
      string lRufBzxfHU;
      string VqhbzfFFeH;
      string ZGmxCWlzNJ;
      string OjQmlyBuyf;
      string QiVpygPQWF;
      string WNoIJfdxde;
      string NxRyGlatpA;
      string dJHyqpjxzV;
      string HUcImBtHdF;
      string UDRSSTRWjM;
      string FUaVbMGqRS;
      string ugyHXrTJLE;
      string qTQjfZrneW;
      string YMMlPltGfZ;
      string uDpKJmFJua;
      string zILeVlEppB;
      string TRLtthTLrk;
      if(UdVzlhEgWY == dJHyqpjxzV){yNckJncFZr = true;}
      else if(dJHyqpjxzV == UdVzlhEgWY){TpdjsHaLtT = true;}
      if(PxaAeNPdLU == HUcImBtHdF){UirEXPBhQc = true;}
      else if(HUcImBtHdF == PxaAeNPdLU){HdBKcKICFs = true;}
      if(YyrVkbSUQi == UDRSSTRWjM){hDQdFcruQa = true;}
      else if(UDRSSTRWjM == YyrVkbSUQi){cPctwEdWxs = true;}
      if(lRufBzxfHU == FUaVbMGqRS){SsQJbleaVg = true;}
      else if(FUaVbMGqRS == lRufBzxfHU){YVuqAMGnsl = true;}
      if(VqhbzfFFeH == ugyHXrTJLE){IzPxgkZGWd = true;}
      else if(ugyHXrTJLE == VqhbzfFFeH){FlHlaLejMa = true;}
      if(ZGmxCWlzNJ == qTQjfZrneW){gluODtwyef = true;}
      else if(qTQjfZrneW == ZGmxCWlzNJ){RHLdcENjnn = true;}
      if(OjQmlyBuyf == YMMlPltGfZ){uhnzZaRibl = true;}
      else if(YMMlPltGfZ == OjQmlyBuyf){cENBukiJKP = true;}
      if(QiVpygPQWF == uDpKJmFJua){kZLiTimSxT = true;}
      if(WNoIJfdxde == zILeVlEppB){DkYlsfyCGh = true;}
      if(NxRyGlatpA == TRLtthTLrk){ofuokaKQXF = true;}
      while(uDpKJmFJua == QiVpygPQWF){DUISnpIpTk = true;}
      while(zILeVlEppB == zILeVlEppB){ZsKWbQKQOw = true;}
      while(TRLtthTLrk == TRLtthTLrk){zWAEIBXFpp = true;}
      if(yNckJncFZr == true){yNckJncFZr = false;}
      if(UirEXPBhQc == true){UirEXPBhQc = false;}
      if(hDQdFcruQa == true){hDQdFcruQa = false;}
      if(SsQJbleaVg == true){SsQJbleaVg = false;}
      if(IzPxgkZGWd == true){IzPxgkZGWd = false;}
      if(gluODtwyef == true){gluODtwyef = false;}
      if(uhnzZaRibl == true){uhnzZaRibl = false;}
      if(kZLiTimSxT == true){kZLiTimSxT = false;}
      if(DkYlsfyCGh == true){DkYlsfyCGh = false;}
      if(ofuokaKQXF == true){ofuokaKQXF = false;}
      if(TpdjsHaLtT == true){TpdjsHaLtT = false;}
      if(HdBKcKICFs == true){HdBKcKICFs = false;}
      if(cPctwEdWxs == true){cPctwEdWxs = false;}
      if(YVuqAMGnsl == true){YVuqAMGnsl = false;}
      if(FlHlaLejMa == true){FlHlaLejMa = false;}
      if(RHLdcENjnn == true){RHLdcENjnn = false;}
      if(cENBukiJKP == true){cENBukiJKP = false;}
      if(DUISnpIpTk == true){DUISnpIpTk = false;}
      if(ZsKWbQKQOw == true){ZsKWbQKQOw = false;}
      if(zWAEIBXFpp == true){zWAEIBXFpp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOXSXEAORN
{ 
  void xkESokrtwV()
  { 
      bool zoNVdQZTfz = false;
      bool rcIXBWHYDr = false;
      bool zrDZdGEjxs = false;
      bool uFGTuhUDsD = false;
      bool rHSSxJADiJ = false;
      bool oiedYHlmrW = false;
      bool MpVmEmWnbS = false;
      bool BEeAzrYjbT = false;
      bool GAAnDLZbtn = false;
      bool wgKVqCkeOJ = false;
      bool mLaQHkEedg = false;
      bool hBLXQLohjs = false;
      bool NttnVTsIIx = false;
      bool GtUSguZjfR = false;
      bool GtxNFuVlFf = false;
      bool MCtVusRmtm = false;
      bool ruWgZngrqU = false;
      bool kEBSlTwfia = false;
      bool xGCckDzzWm = false;
      bool dmprZLWQnR = false;
      string wSwOPINEOP;
      string yRgVQMidcd;
      string GNsXYshpJw;
      string YUXQfcbGTr;
      string rTdgpXhgrr;
      string tCAaKhYYoV;
      string ZWtRpdsQon;
      string kcJklljMhB;
      string LBxQCWUxFx;
      string DCQxSUYLpL;
      string dRrDHQrOoX;
      string yMqmKYYdOT;
      string IwKqkhLLRQ;
      string NXVVXtIsJk;
      string dFHgzpKcmt;
      string wuxWCgGASY;
      string FgxXKaqVPQ;
      string PeUcpDncrt;
      string XhYXUSazSp;
      string mIajfxIiWY;
      if(wSwOPINEOP == dRrDHQrOoX){zoNVdQZTfz = true;}
      else if(dRrDHQrOoX == wSwOPINEOP){mLaQHkEedg = true;}
      if(yRgVQMidcd == yMqmKYYdOT){rcIXBWHYDr = true;}
      else if(yMqmKYYdOT == yRgVQMidcd){hBLXQLohjs = true;}
      if(GNsXYshpJw == IwKqkhLLRQ){zrDZdGEjxs = true;}
      else if(IwKqkhLLRQ == GNsXYshpJw){NttnVTsIIx = true;}
      if(YUXQfcbGTr == NXVVXtIsJk){uFGTuhUDsD = true;}
      else if(NXVVXtIsJk == YUXQfcbGTr){GtUSguZjfR = true;}
      if(rTdgpXhgrr == dFHgzpKcmt){rHSSxJADiJ = true;}
      else if(dFHgzpKcmt == rTdgpXhgrr){GtxNFuVlFf = true;}
      if(tCAaKhYYoV == wuxWCgGASY){oiedYHlmrW = true;}
      else if(wuxWCgGASY == tCAaKhYYoV){MCtVusRmtm = true;}
      if(ZWtRpdsQon == FgxXKaqVPQ){MpVmEmWnbS = true;}
      else if(FgxXKaqVPQ == ZWtRpdsQon){ruWgZngrqU = true;}
      if(kcJklljMhB == PeUcpDncrt){BEeAzrYjbT = true;}
      if(LBxQCWUxFx == XhYXUSazSp){GAAnDLZbtn = true;}
      if(DCQxSUYLpL == mIajfxIiWY){wgKVqCkeOJ = true;}
      while(PeUcpDncrt == kcJklljMhB){kEBSlTwfia = true;}
      while(XhYXUSazSp == XhYXUSazSp){xGCckDzzWm = true;}
      while(mIajfxIiWY == mIajfxIiWY){dmprZLWQnR = true;}
      if(zoNVdQZTfz == true){zoNVdQZTfz = false;}
      if(rcIXBWHYDr == true){rcIXBWHYDr = false;}
      if(zrDZdGEjxs == true){zrDZdGEjxs = false;}
      if(uFGTuhUDsD == true){uFGTuhUDsD = false;}
      if(rHSSxJADiJ == true){rHSSxJADiJ = false;}
      if(oiedYHlmrW == true){oiedYHlmrW = false;}
      if(MpVmEmWnbS == true){MpVmEmWnbS = false;}
      if(BEeAzrYjbT == true){BEeAzrYjbT = false;}
      if(GAAnDLZbtn == true){GAAnDLZbtn = false;}
      if(wgKVqCkeOJ == true){wgKVqCkeOJ = false;}
      if(mLaQHkEedg == true){mLaQHkEedg = false;}
      if(hBLXQLohjs == true){hBLXQLohjs = false;}
      if(NttnVTsIIx == true){NttnVTsIIx = false;}
      if(GtUSguZjfR == true){GtUSguZjfR = false;}
      if(GtxNFuVlFf == true){GtxNFuVlFf = false;}
      if(MCtVusRmtm == true){MCtVusRmtm = false;}
      if(ruWgZngrqU == true){ruWgZngrqU = false;}
      if(kEBSlTwfia == true){kEBSlTwfia = false;}
      if(xGCckDzzWm == true){xGCckDzzWm = false;}
      if(dmprZLWQnR == true){dmprZLWQnR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBZVXLKNQI
{ 
  void OdKZBjPIVf()
  { 
      bool UYjgeOZsdI = false;
      bool iyVyVtywkN = false;
      bool iOiBucdCCg = false;
      bool GeGmHkpZyy = false;
      bool oAKTZkRfXq = false;
      bool QMSjhGphlC = false;
      bool kXpwCDqipk = false;
      bool DXxlXiDObJ = false;
      bool KydKQtLWEB = false;
      bool uInwNRJNRV = false;
      bool sholnrOfLz = false;
      bool CaFbqmsffH = false;
      bool qUenptjBYG = false;
      bool YoxGQbIrWX = false;
      bool efKEyTCLEZ = false;
      bool XdhJdYDAus = false;
      bool IMHEaMczLO = false;
      bool dBIHcLJZoV = false;
      bool rYxyiuHnbq = false;
      bool XHwcORXFdl = false;
      string hwATJajnjg;
      string COGBEWwHqt;
      string sZTSFYIsRq;
      string RaqkEQetLr;
      string ZOVKwbEUOR;
      string sUwEtHbhOj;
      string SqVsPbXVwn;
      string qBuyTeDJVd;
      string TmeAywempx;
      string oxfbZirctU;
      string DhYZZqZxjP;
      string DRMkPeLVuT;
      string wkfyztVTXk;
      string laOAZlOEZG;
      string VgCatWjtLu;
      string WWgaXRCaaf;
      string UGYycbCLKd;
      string QHwnxPiEEb;
      string JaHcNPsncI;
      string imdtlPIDxR;
      if(hwATJajnjg == DhYZZqZxjP){UYjgeOZsdI = true;}
      else if(DhYZZqZxjP == hwATJajnjg){sholnrOfLz = true;}
      if(COGBEWwHqt == DRMkPeLVuT){iyVyVtywkN = true;}
      else if(DRMkPeLVuT == COGBEWwHqt){CaFbqmsffH = true;}
      if(sZTSFYIsRq == wkfyztVTXk){iOiBucdCCg = true;}
      else if(wkfyztVTXk == sZTSFYIsRq){qUenptjBYG = true;}
      if(RaqkEQetLr == laOAZlOEZG){GeGmHkpZyy = true;}
      else if(laOAZlOEZG == RaqkEQetLr){YoxGQbIrWX = true;}
      if(ZOVKwbEUOR == VgCatWjtLu){oAKTZkRfXq = true;}
      else if(VgCatWjtLu == ZOVKwbEUOR){efKEyTCLEZ = true;}
      if(sUwEtHbhOj == WWgaXRCaaf){QMSjhGphlC = true;}
      else if(WWgaXRCaaf == sUwEtHbhOj){XdhJdYDAus = true;}
      if(SqVsPbXVwn == UGYycbCLKd){kXpwCDqipk = true;}
      else if(UGYycbCLKd == SqVsPbXVwn){IMHEaMczLO = true;}
      if(qBuyTeDJVd == QHwnxPiEEb){DXxlXiDObJ = true;}
      if(TmeAywempx == JaHcNPsncI){KydKQtLWEB = true;}
      if(oxfbZirctU == imdtlPIDxR){uInwNRJNRV = true;}
      while(QHwnxPiEEb == qBuyTeDJVd){dBIHcLJZoV = true;}
      while(JaHcNPsncI == JaHcNPsncI){rYxyiuHnbq = true;}
      while(imdtlPIDxR == imdtlPIDxR){XHwcORXFdl = true;}
      if(UYjgeOZsdI == true){UYjgeOZsdI = false;}
      if(iyVyVtywkN == true){iyVyVtywkN = false;}
      if(iOiBucdCCg == true){iOiBucdCCg = false;}
      if(GeGmHkpZyy == true){GeGmHkpZyy = false;}
      if(oAKTZkRfXq == true){oAKTZkRfXq = false;}
      if(QMSjhGphlC == true){QMSjhGphlC = false;}
      if(kXpwCDqipk == true){kXpwCDqipk = false;}
      if(DXxlXiDObJ == true){DXxlXiDObJ = false;}
      if(KydKQtLWEB == true){KydKQtLWEB = false;}
      if(uInwNRJNRV == true){uInwNRJNRV = false;}
      if(sholnrOfLz == true){sholnrOfLz = false;}
      if(CaFbqmsffH == true){CaFbqmsffH = false;}
      if(qUenptjBYG == true){qUenptjBYG = false;}
      if(YoxGQbIrWX == true){YoxGQbIrWX = false;}
      if(efKEyTCLEZ == true){efKEyTCLEZ = false;}
      if(XdhJdYDAus == true){XdhJdYDAus = false;}
      if(IMHEaMczLO == true){IMHEaMczLO = false;}
      if(dBIHcLJZoV == true){dBIHcLJZoV = false;}
      if(rYxyiuHnbq == true){rYxyiuHnbq = false;}
      if(XHwcORXFdl == true){XHwcORXFdl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDQWSWFABV
{ 
  void SzaQgOOHlL()
  { 
      bool hRbkQHPXRh = false;
      bool ljnJNCkmCb = false;
      bool xowKOjOaRI = false;
      bool MetgfdybHm = false;
      bool HFiiuQUkCt = false;
      bool xwiHVrUQVf = false;
      bool rnGIUHpHcj = false;
      bool DIfPUqFNPx = false;
      bool OcXWLQumKm = false;
      bool IhFatSzZNn = false;
      bool aNHSqnPTle = false;
      bool lHBXROPjxE = false;
      bool MDwpaVDFVB = false;
      bool qfAbWBVFeW = false;
      bool AaAeAAggJe = false;
      bool DPbIaWQRqV = false;
      bool kKykmGHZAQ = false;
      bool sKEaEkDRpa = false;
      bool nVwpybDqAA = false;
      bool jDOJlocOqt = false;
      string nLgCVXjfGN;
      string xxSCGSPENy;
      string zFcLiwyjFT;
      string ASFqUCGTHb;
      string sxNqytDQKw;
      string UIeNeiiUSZ;
      string ZAZmNdqagD;
      string MwwkEBqkNn;
      string sgYJyqnqMl;
      string TlAhCsWadT;
      string DciGjYLsIc;
      string qxGegrbQnV;
      string pzNtjawOhL;
      string dQHtkQyRZZ;
      string etiitWeUBK;
      string RGlHcDOnWJ;
      string cxKxzaoMsQ;
      string sJqOpuQdAN;
      string uaMXtWdAQh;
      string BJtPwhiljT;
      if(nLgCVXjfGN == DciGjYLsIc){hRbkQHPXRh = true;}
      else if(DciGjYLsIc == nLgCVXjfGN){aNHSqnPTle = true;}
      if(xxSCGSPENy == qxGegrbQnV){ljnJNCkmCb = true;}
      else if(qxGegrbQnV == xxSCGSPENy){lHBXROPjxE = true;}
      if(zFcLiwyjFT == pzNtjawOhL){xowKOjOaRI = true;}
      else if(pzNtjawOhL == zFcLiwyjFT){MDwpaVDFVB = true;}
      if(ASFqUCGTHb == dQHtkQyRZZ){MetgfdybHm = true;}
      else if(dQHtkQyRZZ == ASFqUCGTHb){qfAbWBVFeW = true;}
      if(sxNqytDQKw == etiitWeUBK){HFiiuQUkCt = true;}
      else if(etiitWeUBK == sxNqytDQKw){AaAeAAggJe = true;}
      if(UIeNeiiUSZ == RGlHcDOnWJ){xwiHVrUQVf = true;}
      else if(RGlHcDOnWJ == UIeNeiiUSZ){DPbIaWQRqV = true;}
      if(ZAZmNdqagD == cxKxzaoMsQ){rnGIUHpHcj = true;}
      else if(cxKxzaoMsQ == ZAZmNdqagD){kKykmGHZAQ = true;}
      if(MwwkEBqkNn == sJqOpuQdAN){DIfPUqFNPx = true;}
      if(sgYJyqnqMl == uaMXtWdAQh){OcXWLQumKm = true;}
      if(TlAhCsWadT == BJtPwhiljT){IhFatSzZNn = true;}
      while(sJqOpuQdAN == MwwkEBqkNn){sKEaEkDRpa = true;}
      while(uaMXtWdAQh == uaMXtWdAQh){nVwpybDqAA = true;}
      while(BJtPwhiljT == BJtPwhiljT){jDOJlocOqt = true;}
      if(hRbkQHPXRh == true){hRbkQHPXRh = false;}
      if(ljnJNCkmCb == true){ljnJNCkmCb = false;}
      if(xowKOjOaRI == true){xowKOjOaRI = false;}
      if(MetgfdybHm == true){MetgfdybHm = false;}
      if(HFiiuQUkCt == true){HFiiuQUkCt = false;}
      if(xwiHVrUQVf == true){xwiHVrUQVf = false;}
      if(rnGIUHpHcj == true){rnGIUHpHcj = false;}
      if(DIfPUqFNPx == true){DIfPUqFNPx = false;}
      if(OcXWLQumKm == true){OcXWLQumKm = false;}
      if(IhFatSzZNn == true){IhFatSzZNn = false;}
      if(aNHSqnPTle == true){aNHSqnPTle = false;}
      if(lHBXROPjxE == true){lHBXROPjxE = false;}
      if(MDwpaVDFVB == true){MDwpaVDFVB = false;}
      if(qfAbWBVFeW == true){qfAbWBVFeW = false;}
      if(AaAeAAggJe == true){AaAeAAggJe = false;}
      if(DPbIaWQRqV == true){DPbIaWQRqV = false;}
      if(kKykmGHZAQ == true){kKykmGHZAQ = false;}
      if(sKEaEkDRpa == true){sKEaEkDRpa = false;}
      if(nVwpybDqAA == true){nVwpybDqAA = false;}
      if(jDOJlocOqt == true){jDOJlocOqt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCLGQUYLVQ
{ 
  void zEtBVPGMfs()
  { 
      bool AehftfLeqZ = false;
      bool xUHqmZxRIq = false;
      bool UGNNpOoWzl = false;
      bool MOZZltfNxQ = false;
      bool FyZNjWFwOM = false;
      bool VkKYAtQTpe = false;
      bool pofEMhuhFs = false;
      bool tiUqlWgzcT = false;
      bool JrHlQbEAZr = false;
      bool cLXRZQSUBC = false;
      bool bXqVSlQSmd = false;
      bool MRpWVxgtnk = false;
      bool ctHNPiLCQU = false;
      bool ELyarlBlSd = false;
      bool LlNweLUBwc = false;
      bool jXgPYgPcFj = false;
      bool aNBRYBTPei = false;
      bool wtaKZqgKiE = false;
      bool NKGnkfehCK = false;
      bool WXfiDxjuWc = false;
      string tbwWNJXYcx;
      string prSNpzOUSW;
      string KYQWSBgSIK;
      string UfFTjUjnLq;
      string KlyobWYxKe;
      string FJxWiULZDM;
      string bEPScKmzdU;
      string PaIbLYaatw;
      string bjIcFLhhjO;
      string JKjzOFWeMR;
      string jZSoPdAVKK;
      string tkeHjrwlNQ;
      string bEOPLEpIMF;
      string CuNcMCQSNa;
      string KLWYTYfcOV;
      string JjRwoeKDdL;
      string mrIEIyXBuh;
      string bdYlFPgpum;
      string YNtqwRdQng;
      string qMnBmSDSQU;
      if(tbwWNJXYcx == jZSoPdAVKK){AehftfLeqZ = true;}
      else if(jZSoPdAVKK == tbwWNJXYcx){bXqVSlQSmd = true;}
      if(prSNpzOUSW == tkeHjrwlNQ){xUHqmZxRIq = true;}
      else if(tkeHjrwlNQ == prSNpzOUSW){MRpWVxgtnk = true;}
      if(KYQWSBgSIK == bEOPLEpIMF){UGNNpOoWzl = true;}
      else if(bEOPLEpIMF == KYQWSBgSIK){ctHNPiLCQU = true;}
      if(UfFTjUjnLq == CuNcMCQSNa){MOZZltfNxQ = true;}
      else if(CuNcMCQSNa == UfFTjUjnLq){ELyarlBlSd = true;}
      if(KlyobWYxKe == KLWYTYfcOV){FyZNjWFwOM = true;}
      else if(KLWYTYfcOV == KlyobWYxKe){LlNweLUBwc = true;}
      if(FJxWiULZDM == JjRwoeKDdL){VkKYAtQTpe = true;}
      else if(JjRwoeKDdL == FJxWiULZDM){jXgPYgPcFj = true;}
      if(bEPScKmzdU == mrIEIyXBuh){pofEMhuhFs = true;}
      else if(mrIEIyXBuh == bEPScKmzdU){aNBRYBTPei = true;}
      if(PaIbLYaatw == bdYlFPgpum){tiUqlWgzcT = true;}
      if(bjIcFLhhjO == YNtqwRdQng){JrHlQbEAZr = true;}
      if(JKjzOFWeMR == qMnBmSDSQU){cLXRZQSUBC = true;}
      while(bdYlFPgpum == PaIbLYaatw){wtaKZqgKiE = true;}
      while(YNtqwRdQng == YNtqwRdQng){NKGnkfehCK = true;}
      while(qMnBmSDSQU == qMnBmSDSQU){WXfiDxjuWc = true;}
      if(AehftfLeqZ == true){AehftfLeqZ = false;}
      if(xUHqmZxRIq == true){xUHqmZxRIq = false;}
      if(UGNNpOoWzl == true){UGNNpOoWzl = false;}
      if(MOZZltfNxQ == true){MOZZltfNxQ = false;}
      if(FyZNjWFwOM == true){FyZNjWFwOM = false;}
      if(VkKYAtQTpe == true){VkKYAtQTpe = false;}
      if(pofEMhuhFs == true){pofEMhuhFs = false;}
      if(tiUqlWgzcT == true){tiUqlWgzcT = false;}
      if(JrHlQbEAZr == true){JrHlQbEAZr = false;}
      if(cLXRZQSUBC == true){cLXRZQSUBC = false;}
      if(bXqVSlQSmd == true){bXqVSlQSmd = false;}
      if(MRpWVxgtnk == true){MRpWVxgtnk = false;}
      if(ctHNPiLCQU == true){ctHNPiLCQU = false;}
      if(ELyarlBlSd == true){ELyarlBlSd = false;}
      if(LlNweLUBwc == true){LlNweLUBwc = false;}
      if(jXgPYgPcFj == true){jXgPYgPcFj = false;}
      if(aNBRYBTPei == true){aNBRYBTPei = false;}
      if(wtaKZqgKiE == true){wtaKZqgKiE = false;}
      if(NKGnkfehCK == true){NKGnkfehCK = false;}
      if(WXfiDxjuWc == true){WXfiDxjuWc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQGQEJZNKX
{ 
  void nNJgAWIHuf()
  { 
      bool GPrdJpcPNn = false;
      bool WCGGeKcssB = false;
      bool bfRfYpgWws = false;
      bool hkIZdsVGLY = false;
      bool isnqhXhPZE = false;
      bool oiNYjaxMFS = false;
      bool IGSTFlsfbk = false;
      bool nWgURirZxB = false;
      bool IQxqEzWjpD = false;
      bool uJAsPcZTkw = false;
      bool dBnnPSBsGA = false;
      bool iXOEJrJbPG = false;
      bool PJoYoeVnEo = false;
      bool JXnBWGcIbk = false;
      bool xccpUXtuiX = false;
      bool TyEdfUMOyk = false;
      bool wMoRqKiMhC = false;
      bool OAzdJlfzER = false;
      bool kZEgVKTJUC = false;
      bool tOJqojnLzJ = false;
      string JXyVzEMAAq;
      string MRcrbETTaZ;
      string nhStQTjRay;
      string nuWmrDspSS;
      string FyaWQUzbnW;
      string tdfmUaFEEe;
      string TtYBDQtpAX;
      string LdBIUpHucw;
      string UIdEDJPjSQ;
      string ynlmzKYYTz;
      string ZIbQLQcXSe;
      string TJaHKKQUys;
      string BJWiZWrNJJ;
      string QibdVLfNsm;
      string gqQnwnNdcn;
      string tEZZyQlrqn;
      string XOOJNkhxky;
      string dDaKMKsilk;
      string JNkUPMIBfF;
      string ZnVEOSbHZL;
      if(JXyVzEMAAq == ZIbQLQcXSe){GPrdJpcPNn = true;}
      else if(ZIbQLQcXSe == JXyVzEMAAq){dBnnPSBsGA = true;}
      if(MRcrbETTaZ == TJaHKKQUys){WCGGeKcssB = true;}
      else if(TJaHKKQUys == MRcrbETTaZ){iXOEJrJbPG = true;}
      if(nhStQTjRay == BJWiZWrNJJ){bfRfYpgWws = true;}
      else if(BJWiZWrNJJ == nhStQTjRay){PJoYoeVnEo = true;}
      if(nuWmrDspSS == QibdVLfNsm){hkIZdsVGLY = true;}
      else if(QibdVLfNsm == nuWmrDspSS){JXnBWGcIbk = true;}
      if(FyaWQUzbnW == gqQnwnNdcn){isnqhXhPZE = true;}
      else if(gqQnwnNdcn == FyaWQUzbnW){xccpUXtuiX = true;}
      if(tdfmUaFEEe == tEZZyQlrqn){oiNYjaxMFS = true;}
      else if(tEZZyQlrqn == tdfmUaFEEe){TyEdfUMOyk = true;}
      if(TtYBDQtpAX == XOOJNkhxky){IGSTFlsfbk = true;}
      else if(XOOJNkhxky == TtYBDQtpAX){wMoRqKiMhC = true;}
      if(LdBIUpHucw == dDaKMKsilk){nWgURirZxB = true;}
      if(UIdEDJPjSQ == JNkUPMIBfF){IQxqEzWjpD = true;}
      if(ynlmzKYYTz == ZnVEOSbHZL){uJAsPcZTkw = true;}
      while(dDaKMKsilk == LdBIUpHucw){OAzdJlfzER = true;}
      while(JNkUPMIBfF == JNkUPMIBfF){kZEgVKTJUC = true;}
      while(ZnVEOSbHZL == ZnVEOSbHZL){tOJqojnLzJ = true;}
      if(GPrdJpcPNn == true){GPrdJpcPNn = false;}
      if(WCGGeKcssB == true){WCGGeKcssB = false;}
      if(bfRfYpgWws == true){bfRfYpgWws = false;}
      if(hkIZdsVGLY == true){hkIZdsVGLY = false;}
      if(isnqhXhPZE == true){isnqhXhPZE = false;}
      if(oiNYjaxMFS == true){oiNYjaxMFS = false;}
      if(IGSTFlsfbk == true){IGSTFlsfbk = false;}
      if(nWgURirZxB == true){nWgURirZxB = false;}
      if(IQxqEzWjpD == true){IQxqEzWjpD = false;}
      if(uJAsPcZTkw == true){uJAsPcZTkw = false;}
      if(dBnnPSBsGA == true){dBnnPSBsGA = false;}
      if(iXOEJrJbPG == true){iXOEJrJbPG = false;}
      if(PJoYoeVnEo == true){PJoYoeVnEo = false;}
      if(JXnBWGcIbk == true){JXnBWGcIbk = false;}
      if(xccpUXtuiX == true){xccpUXtuiX = false;}
      if(TyEdfUMOyk == true){TyEdfUMOyk = false;}
      if(wMoRqKiMhC == true){wMoRqKiMhC = false;}
      if(OAzdJlfzER == true){OAzdJlfzER = false;}
      if(kZEgVKTJUC == true){kZEgVKTJUC = false;}
      if(tOJqojnLzJ == true){tOJqojnLzJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNWNQNVQHM
{ 
  void jNouPZXOqj()
  { 
      bool IbGeZDwQna = false;
      bool BmKmrRfzQO = false;
      bool MLEnePdggA = false;
      bool MVILCkXZEi = false;
      bool DdlrymxziE = false;
      bool YRgZNwWRzK = false;
      bool ZPjnNfdzkG = false;
      bool sFthLiZMpq = false;
      bool RdxbatnhxG = false;
      bool OGZtInsyeR = false;
      bool IyObLSXzOe = false;
      bool WKbIsuRIMT = false;
      bool qwBdrmfAYW = false;
      bool oagXhSOVPH = false;
      bool WoTSiEdRAN = false;
      bool WjkLaMwjiY = false;
      bool mWZqoucDZZ = false;
      bool fusEwBcitn = false;
      bool INzLAFoVxU = false;
      bool WdlqUzPbcn = false;
      string eeUQMLAZuq;
      string DlKAgMHCnx;
      string nELSqBKGgl;
      string fWDodWAdMf;
      string RnzAMbFmPf;
      string yPRpSaSCYL;
      string BtrJLfiVWK;
      string LdpIeAEKFO;
      string uWqBmPFMVD;
      string DyEAdXupof;
      string rjQFTUZIKS;
      string VIxKQeCpVu;
      string aWATGNYodH;
      string EOUYVKGlhS;
      string pwCCguAtjz;
      string UETtFVjxyF;
      string wjeDNGmYnF;
      string YQIDFdUxlK;
      string NdEelztaTz;
      string aImbWFRynZ;
      if(eeUQMLAZuq == rjQFTUZIKS){IbGeZDwQna = true;}
      else if(rjQFTUZIKS == eeUQMLAZuq){IyObLSXzOe = true;}
      if(DlKAgMHCnx == VIxKQeCpVu){BmKmrRfzQO = true;}
      else if(VIxKQeCpVu == DlKAgMHCnx){WKbIsuRIMT = true;}
      if(nELSqBKGgl == aWATGNYodH){MLEnePdggA = true;}
      else if(aWATGNYodH == nELSqBKGgl){qwBdrmfAYW = true;}
      if(fWDodWAdMf == EOUYVKGlhS){MVILCkXZEi = true;}
      else if(EOUYVKGlhS == fWDodWAdMf){oagXhSOVPH = true;}
      if(RnzAMbFmPf == pwCCguAtjz){DdlrymxziE = true;}
      else if(pwCCguAtjz == RnzAMbFmPf){WoTSiEdRAN = true;}
      if(yPRpSaSCYL == UETtFVjxyF){YRgZNwWRzK = true;}
      else if(UETtFVjxyF == yPRpSaSCYL){WjkLaMwjiY = true;}
      if(BtrJLfiVWK == wjeDNGmYnF){ZPjnNfdzkG = true;}
      else if(wjeDNGmYnF == BtrJLfiVWK){mWZqoucDZZ = true;}
      if(LdpIeAEKFO == YQIDFdUxlK){sFthLiZMpq = true;}
      if(uWqBmPFMVD == NdEelztaTz){RdxbatnhxG = true;}
      if(DyEAdXupof == aImbWFRynZ){OGZtInsyeR = true;}
      while(YQIDFdUxlK == LdpIeAEKFO){fusEwBcitn = true;}
      while(NdEelztaTz == NdEelztaTz){INzLAFoVxU = true;}
      while(aImbWFRynZ == aImbWFRynZ){WdlqUzPbcn = true;}
      if(IbGeZDwQna == true){IbGeZDwQna = false;}
      if(BmKmrRfzQO == true){BmKmrRfzQO = false;}
      if(MLEnePdggA == true){MLEnePdggA = false;}
      if(MVILCkXZEi == true){MVILCkXZEi = false;}
      if(DdlrymxziE == true){DdlrymxziE = false;}
      if(YRgZNwWRzK == true){YRgZNwWRzK = false;}
      if(ZPjnNfdzkG == true){ZPjnNfdzkG = false;}
      if(sFthLiZMpq == true){sFthLiZMpq = false;}
      if(RdxbatnhxG == true){RdxbatnhxG = false;}
      if(OGZtInsyeR == true){OGZtInsyeR = false;}
      if(IyObLSXzOe == true){IyObLSXzOe = false;}
      if(WKbIsuRIMT == true){WKbIsuRIMT = false;}
      if(qwBdrmfAYW == true){qwBdrmfAYW = false;}
      if(oagXhSOVPH == true){oagXhSOVPH = false;}
      if(WoTSiEdRAN == true){WoTSiEdRAN = false;}
      if(WjkLaMwjiY == true){WjkLaMwjiY = false;}
      if(mWZqoucDZZ == true){mWZqoucDZZ = false;}
      if(fusEwBcitn == true){fusEwBcitn = false;}
      if(INzLAFoVxU == true){INzLAFoVxU = false;}
      if(WdlqUzPbcn == true){WdlqUzPbcn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SMWVWDUXXZ
{ 
  void EFhwcspbWT()
  { 
      bool VpyoZcHFXh = false;
      bool ajBkrfNQKE = false;
      bool tbyuPMAEkw = false;
      bool PLyQDZQVhW = false;
      bool oakThiGINZ = false;
      bool YmoUPtrDZM = false;
      bool bDTaRPkkgS = false;
      bool PrhnPTpeMg = false;
      bool FrpLXcVcAI = false;
      bool hNwUulGJBS = false;
      bool xUauKgEBFw = false;
      bool DNqrHiMICo = false;
      bool tIjYjCuNrd = false;
      bool MgcsijQuBq = false;
      bool YTWEEUWDNL = false;
      bool YxHLXokCLI = false;
      bool kpJbiWjxJW = false;
      bool RRHLQZkfTO = false;
      bool erAgEPYQUt = false;
      bool zOirFhKuVh = false;
      string AuyDenMOKF;
      string doKQFDqtiG;
      string NXftpkKTEB;
      string rgVSQUzScf;
      string NEBOtfAlZV;
      string lYeaZbPEMt;
      string drJJNxTrzj;
      string DXQDrJWQzK;
      string jXshPSCtro;
      string EuFhBVtrBw;
      string MImpRNHahQ;
      string FzECKGyatt;
      string uYAKeIRiCW;
      string PeODxakDQB;
      string KbLajFqDXu;
      string WSyGBnIbKJ;
      string uYXLBajAEi;
      string UtKriSMYZZ;
      string QOKHAwfIBJ;
      string SIsGGlDAZJ;
      if(AuyDenMOKF == MImpRNHahQ){VpyoZcHFXh = true;}
      else if(MImpRNHahQ == AuyDenMOKF){xUauKgEBFw = true;}
      if(doKQFDqtiG == FzECKGyatt){ajBkrfNQKE = true;}
      else if(FzECKGyatt == doKQFDqtiG){DNqrHiMICo = true;}
      if(NXftpkKTEB == uYAKeIRiCW){tbyuPMAEkw = true;}
      else if(uYAKeIRiCW == NXftpkKTEB){tIjYjCuNrd = true;}
      if(rgVSQUzScf == PeODxakDQB){PLyQDZQVhW = true;}
      else if(PeODxakDQB == rgVSQUzScf){MgcsijQuBq = true;}
      if(NEBOtfAlZV == KbLajFqDXu){oakThiGINZ = true;}
      else if(KbLajFqDXu == NEBOtfAlZV){YTWEEUWDNL = true;}
      if(lYeaZbPEMt == WSyGBnIbKJ){YmoUPtrDZM = true;}
      else if(WSyGBnIbKJ == lYeaZbPEMt){YxHLXokCLI = true;}
      if(drJJNxTrzj == uYXLBajAEi){bDTaRPkkgS = true;}
      else if(uYXLBajAEi == drJJNxTrzj){kpJbiWjxJW = true;}
      if(DXQDrJWQzK == UtKriSMYZZ){PrhnPTpeMg = true;}
      if(jXshPSCtro == QOKHAwfIBJ){FrpLXcVcAI = true;}
      if(EuFhBVtrBw == SIsGGlDAZJ){hNwUulGJBS = true;}
      while(UtKriSMYZZ == DXQDrJWQzK){RRHLQZkfTO = true;}
      while(QOKHAwfIBJ == QOKHAwfIBJ){erAgEPYQUt = true;}
      while(SIsGGlDAZJ == SIsGGlDAZJ){zOirFhKuVh = true;}
      if(VpyoZcHFXh == true){VpyoZcHFXh = false;}
      if(ajBkrfNQKE == true){ajBkrfNQKE = false;}
      if(tbyuPMAEkw == true){tbyuPMAEkw = false;}
      if(PLyQDZQVhW == true){PLyQDZQVhW = false;}
      if(oakThiGINZ == true){oakThiGINZ = false;}
      if(YmoUPtrDZM == true){YmoUPtrDZM = false;}
      if(bDTaRPkkgS == true){bDTaRPkkgS = false;}
      if(PrhnPTpeMg == true){PrhnPTpeMg = false;}
      if(FrpLXcVcAI == true){FrpLXcVcAI = false;}
      if(hNwUulGJBS == true){hNwUulGJBS = false;}
      if(xUauKgEBFw == true){xUauKgEBFw = false;}
      if(DNqrHiMICo == true){DNqrHiMICo = false;}
      if(tIjYjCuNrd == true){tIjYjCuNrd = false;}
      if(MgcsijQuBq == true){MgcsijQuBq = false;}
      if(YTWEEUWDNL == true){YTWEEUWDNL = false;}
      if(YxHLXokCLI == true){YxHLXokCLI = false;}
      if(kpJbiWjxJW == true){kpJbiWjxJW = false;}
      if(RRHLQZkfTO == true){RRHLQZkfTO = false;}
      if(erAgEPYQUt == true){erAgEPYQUt = false;}
      if(zOirFhKuVh == true){zOirFhKuVh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQUVLALGKY
{ 
  void fIHNdrkRSD()
  { 
      bool GDeLtpTfuk = false;
      bool SEzBqbUeBJ = false;
      bool lHrnBfHPOW = false;
      bool kOBsphQfar = false;
      bool jODTgSyNHY = false;
      bool ToFoFzKqJO = false;
      bool iDRXAECGKI = false;
      bool KnDIYXDYGi = false;
      bool htIpDuIMmp = false;
      bool XYWMJgxeSc = false;
      bool PqCyNekwQh = false;
      bool ulkafotaUE = false;
      bool upTUklRpzq = false;
      bool aXFcSprJbX = false;
      bool JLuEtknugU = false;
      bool lVKOhZXgNb = false;
      bool NuxYHWfHHp = false;
      bool xkyxtjtOZz = false;
      bool xVJeFENqus = false;
      bool RKwAJOOWwX = false;
      string DbfEYZPdKB;
      string totwniarSq;
      string UHtYkffLsK;
      string xAAWqGBPch;
      string zJiWLsnBpz;
      string yFhZLuhGTr;
      string sDjzEtoXFh;
      string hKOjrLYWNq;
      string reUsLrSaLu;
      string XtuknuYiSR;
      string DQuIQmpxhz;
      string WKsbAOiqmM;
      string aOLJKmPcww;
      string lpEunajMbX;
      string BVsLYMBTkZ;
      string MhuFpnEkyd;
      string XMBkNgGxnY;
      string eVOOKFVAkx;
      string lwrViEtyEz;
      string WyOyAnTHyr;
      if(DbfEYZPdKB == DQuIQmpxhz){GDeLtpTfuk = true;}
      else if(DQuIQmpxhz == DbfEYZPdKB){PqCyNekwQh = true;}
      if(totwniarSq == WKsbAOiqmM){SEzBqbUeBJ = true;}
      else if(WKsbAOiqmM == totwniarSq){ulkafotaUE = true;}
      if(UHtYkffLsK == aOLJKmPcww){lHrnBfHPOW = true;}
      else if(aOLJKmPcww == UHtYkffLsK){upTUklRpzq = true;}
      if(xAAWqGBPch == lpEunajMbX){kOBsphQfar = true;}
      else if(lpEunajMbX == xAAWqGBPch){aXFcSprJbX = true;}
      if(zJiWLsnBpz == BVsLYMBTkZ){jODTgSyNHY = true;}
      else if(BVsLYMBTkZ == zJiWLsnBpz){JLuEtknugU = true;}
      if(yFhZLuhGTr == MhuFpnEkyd){ToFoFzKqJO = true;}
      else if(MhuFpnEkyd == yFhZLuhGTr){lVKOhZXgNb = true;}
      if(sDjzEtoXFh == XMBkNgGxnY){iDRXAECGKI = true;}
      else if(XMBkNgGxnY == sDjzEtoXFh){NuxYHWfHHp = true;}
      if(hKOjrLYWNq == eVOOKFVAkx){KnDIYXDYGi = true;}
      if(reUsLrSaLu == lwrViEtyEz){htIpDuIMmp = true;}
      if(XtuknuYiSR == WyOyAnTHyr){XYWMJgxeSc = true;}
      while(eVOOKFVAkx == hKOjrLYWNq){xkyxtjtOZz = true;}
      while(lwrViEtyEz == lwrViEtyEz){xVJeFENqus = true;}
      while(WyOyAnTHyr == WyOyAnTHyr){RKwAJOOWwX = true;}
      if(GDeLtpTfuk == true){GDeLtpTfuk = false;}
      if(SEzBqbUeBJ == true){SEzBqbUeBJ = false;}
      if(lHrnBfHPOW == true){lHrnBfHPOW = false;}
      if(kOBsphQfar == true){kOBsphQfar = false;}
      if(jODTgSyNHY == true){jODTgSyNHY = false;}
      if(ToFoFzKqJO == true){ToFoFzKqJO = false;}
      if(iDRXAECGKI == true){iDRXAECGKI = false;}
      if(KnDIYXDYGi == true){KnDIYXDYGi = false;}
      if(htIpDuIMmp == true){htIpDuIMmp = false;}
      if(XYWMJgxeSc == true){XYWMJgxeSc = false;}
      if(PqCyNekwQh == true){PqCyNekwQh = false;}
      if(ulkafotaUE == true){ulkafotaUE = false;}
      if(upTUklRpzq == true){upTUklRpzq = false;}
      if(aXFcSprJbX == true){aXFcSprJbX = false;}
      if(JLuEtknugU == true){JLuEtknugU = false;}
      if(lVKOhZXgNb == true){lVKOhZXgNb = false;}
      if(NuxYHWfHHp == true){NuxYHWfHHp = false;}
      if(xkyxtjtOZz == true){xkyxtjtOZz = false;}
      if(xVJeFENqus == true){xVJeFENqus = false;}
      if(RKwAJOOWwX == true){RKwAJOOWwX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PPPHPVNDNO
{ 
  void fZXjEzKmDA()
  { 
      bool lRjoiVGLMl = false;
      bool iNNXltpIcT = false;
      bool DarXhLBdyo = false;
      bool bFQjoNaDQn = false;
      bool JVpyBzkKYF = false;
      bool rDYIpLZLGX = false;
      bool TcMXKcxchY = false;
      bool SlqoJhjsVh = false;
      bool ZqEswXgHsd = false;
      bool mOwsUgISnY = false;
      bool CIbAmGLjyI = false;
      bool agpYxbXTal = false;
      bool woiDkDoyUc = false;
      bool YQExfRPEFp = false;
      bool LxIkDGYXur = false;
      bool JorBbMYYOj = false;
      bool QNOVjJbsrf = false;
      bool MSNjZzgyAd = false;
      bool eRCbSjYDUT = false;
      bool rpoVZyhlAs = false;
      string XCHCUQdEQA;
      string CbsVteKpdy;
      string SkRUzRUoUA;
      string cRjbyTVeHp;
      string LwdzWhfaQA;
      string nwqpSlkmCD;
      string uojPWkrQWZ;
      string JfhnlWHRyR;
      string ktXTMfZsJL;
      string iicDtWLNbl;
      string oPDpqHNDDu;
      string eSnjRBQQDq;
      string KyHLqZDesP;
      string LsoLbVqgbE;
      string SVpNgPtrks;
      string FuKkaqHrzR;
      string EiJmjldcIw;
      string KjnyYnIsea;
      string eKsAJQhDkk;
      string NyhKziMCct;
      if(XCHCUQdEQA == oPDpqHNDDu){lRjoiVGLMl = true;}
      else if(oPDpqHNDDu == XCHCUQdEQA){CIbAmGLjyI = true;}
      if(CbsVteKpdy == eSnjRBQQDq){iNNXltpIcT = true;}
      else if(eSnjRBQQDq == CbsVteKpdy){agpYxbXTal = true;}
      if(SkRUzRUoUA == KyHLqZDesP){DarXhLBdyo = true;}
      else if(KyHLqZDesP == SkRUzRUoUA){woiDkDoyUc = true;}
      if(cRjbyTVeHp == LsoLbVqgbE){bFQjoNaDQn = true;}
      else if(LsoLbVqgbE == cRjbyTVeHp){YQExfRPEFp = true;}
      if(LwdzWhfaQA == SVpNgPtrks){JVpyBzkKYF = true;}
      else if(SVpNgPtrks == LwdzWhfaQA){LxIkDGYXur = true;}
      if(nwqpSlkmCD == FuKkaqHrzR){rDYIpLZLGX = true;}
      else if(FuKkaqHrzR == nwqpSlkmCD){JorBbMYYOj = true;}
      if(uojPWkrQWZ == EiJmjldcIw){TcMXKcxchY = true;}
      else if(EiJmjldcIw == uojPWkrQWZ){QNOVjJbsrf = true;}
      if(JfhnlWHRyR == KjnyYnIsea){SlqoJhjsVh = true;}
      if(ktXTMfZsJL == eKsAJQhDkk){ZqEswXgHsd = true;}
      if(iicDtWLNbl == NyhKziMCct){mOwsUgISnY = true;}
      while(KjnyYnIsea == JfhnlWHRyR){MSNjZzgyAd = true;}
      while(eKsAJQhDkk == eKsAJQhDkk){eRCbSjYDUT = true;}
      while(NyhKziMCct == NyhKziMCct){rpoVZyhlAs = true;}
      if(lRjoiVGLMl == true){lRjoiVGLMl = false;}
      if(iNNXltpIcT == true){iNNXltpIcT = false;}
      if(DarXhLBdyo == true){DarXhLBdyo = false;}
      if(bFQjoNaDQn == true){bFQjoNaDQn = false;}
      if(JVpyBzkKYF == true){JVpyBzkKYF = false;}
      if(rDYIpLZLGX == true){rDYIpLZLGX = false;}
      if(TcMXKcxchY == true){TcMXKcxchY = false;}
      if(SlqoJhjsVh == true){SlqoJhjsVh = false;}
      if(ZqEswXgHsd == true){ZqEswXgHsd = false;}
      if(mOwsUgISnY == true){mOwsUgISnY = false;}
      if(CIbAmGLjyI == true){CIbAmGLjyI = false;}
      if(agpYxbXTal == true){agpYxbXTal = false;}
      if(woiDkDoyUc == true){woiDkDoyUc = false;}
      if(YQExfRPEFp == true){YQExfRPEFp = false;}
      if(LxIkDGYXur == true){LxIkDGYXur = false;}
      if(JorBbMYYOj == true){JorBbMYYOj = false;}
      if(QNOVjJbsrf == true){QNOVjJbsrf = false;}
      if(MSNjZzgyAd == true){MSNjZzgyAd = false;}
      if(eRCbSjYDUT == true){eRCbSjYDUT = false;}
      if(rpoVZyhlAs == true){rpoVZyhlAs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COXJVIYUTV
{ 
  void kMomHBSExq()
  { 
      bool ohjSGLXEaN = false;
      bool NASObrHwWl = false;
      bool SljtIYPXnu = false;
      bool BuPiNiLAtb = false;
      bool xCYzcJIyWP = false;
      bool IIdaOCypKh = false;
      bool wAPfMRjjAr = false;
      bool gGCuoPNjQz = false;
      bool PRAYlrQnTL = false;
      bool kUpLewmsmK = false;
      bool YYxeiCFilz = false;
      bool oNYLReApsT = false;
      bool AuQoHLPpPr = false;
      bool bUwGZpTUpj = false;
      bool lhCTVWwetA = false;
      bool wwzTJdIIXW = false;
      bool lPTsWTRSkb = false;
      bool KeAJgSrwSj = false;
      bool PkwOwfVbww = false;
      bool hLxSxWOIxC = false;
      string WtjLqOrgga;
      string yMbihEAzWC;
      string hnsxzakHil;
      string zjFmWBwWFx;
      string fImQobOSdz;
      string jaeIwhAlMQ;
      string djytaNGnLf;
      string HctZWYAbIX;
      string MRcjCXFxqn;
      string AKKoSuJsoa;
      string UZGyqGgEkW;
      string gYdnDLHOrD;
      string HJxXfxSFHa;
      string PHlgClLeru;
      string qBLTGbfVkG;
      string ntAlTLciSs;
      string nawKHYlxkR;
      string AbWwLFxcQD;
      string RwTAmUGzNq;
      string JbMzHPEBMg;
      if(WtjLqOrgga == UZGyqGgEkW){ohjSGLXEaN = true;}
      else if(UZGyqGgEkW == WtjLqOrgga){YYxeiCFilz = true;}
      if(yMbihEAzWC == gYdnDLHOrD){NASObrHwWl = true;}
      else if(gYdnDLHOrD == yMbihEAzWC){oNYLReApsT = true;}
      if(hnsxzakHil == HJxXfxSFHa){SljtIYPXnu = true;}
      else if(HJxXfxSFHa == hnsxzakHil){AuQoHLPpPr = true;}
      if(zjFmWBwWFx == PHlgClLeru){BuPiNiLAtb = true;}
      else if(PHlgClLeru == zjFmWBwWFx){bUwGZpTUpj = true;}
      if(fImQobOSdz == qBLTGbfVkG){xCYzcJIyWP = true;}
      else if(qBLTGbfVkG == fImQobOSdz){lhCTVWwetA = true;}
      if(jaeIwhAlMQ == ntAlTLciSs){IIdaOCypKh = true;}
      else if(ntAlTLciSs == jaeIwhAlMQ){wwzTJdIIXW = true;}
      if(djytaNGnLf == nawKHYlxkR){wAPfMRjjAr = true;}
      else if(nawKHYlxkR == djytaNGnLf){lPTsWTRSkb = true;}
      if(HctZWYAbIX == AbWwLFxcQD){gGCuoPNjQz = true;}
      if(MRcjCXFxqn == RwTAmUGzNq){PRAYlrQnTL = true;}
      if(AKKoSuJsoa == JbMzHPEBMg){kUpLewmsmK = true;}
      while(AbWwLFxcQD == HctZWYAbIX){KeAJgSrwSj = true;}
      while(RwTAmUGzNq == RwTAmUGzNq){PkwOwfVbww = true;}
      while(JbMzHPEBMg == JbMzHPEBMg){hLxSxWOIxC = true;}
      if(ohjSGLXEaN == true){ohjSGLXEaN = false;}
      if(NASObrHwWl == true){NASObrHwWl = false;}
      if(SljtIYPXnu == true){SljtIYPXnu = false;}
      if(BuPiNiLAtb == true){BuPiNiLAtb = false;}
      if(xCYzcJIyWP == true){xCYzcJIyWP = false;}
      if(IIdaOCypKh == true){IIdaOCypKh = false;}
      if(wAPfMRjjAr == true){wAPfMRjjAr = false;}
      if(gGCuoPNjQz == true){gGCuoPNjQz = false;}
      if(PRAYlrQnTL == true){PRAYlrQnTL = false;}
      if(kUpLewmsmK == true){kUpLewmsmK = false;}
      if(YYxeiCFilz == true){YYxeiCFilz = false;}
      if(oNYLReApsT == true){oNYLReApsT = false;}
      if(AuQoHLPpPr == true){AuQoHLPpPr = false;}
      if(bUwGZpTUpj == true){bUwGZpTUpj = false;}
      if(lhCTVWwetA == true){lhCTVWwetA = false;}
      if(wwzTJdIIXW == true){wwzTJdIIXW = false;}
      if(lPTsWTRSkb == true){lPTsWTRSkb = false;}
      if(KeAJgSrwSj == true){KeAJgSrwSj = false;}
      if(PkwOwfVbww == true){PkwOwfVbww = false;}
      if(hLxSxWOIxC == true){hLxSxWOIxC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPZYMQWZDC
{ 
  void amOSmirOuV()
  { 
      bool kIuZRZGVDg = false;
      bool ssumurZnSC = false;
      bool jyZzxCBIqS = false;
      bool ejjoLremff = false;
      bool dDrxROzDHo = false;
      bool GghWYlhwbP = false;
      bool YydkCIJFbD = false;
      bool NlHmXgGchh = false;
      bool CxABLxCMQY = false;
      bool JhKPHfYGtI = false;
      bool FsbDbUZtzq = false;
      bool eFNtNbxcYF = false;
      bool GwoDtearfr = false;
      bool IAhYbIUxYq = false;
      bool XHNYsDUQCe = false;
      bool hugoCJEYJx = false;
      bool shOGieWoSF = false;
      bool GADhhyhQJp = false;
      bool KKoAKMSsWS = false;
      bool EwmbxprHoO = false;
      string qZcisXIiBo;
      string pTCZqoPrLD;
      string ebKJFofCNe;
      string VYhaKoxgCt;
      string rypoHaCbOD;
      string gWQJWOPScE;
      string qGVWSQkaOC;
      string ripQKflVCe;
      string mDmKyzIYEw;
      string ZdDxClcSWp;
      string paNMKxfAyp;
      string csQyRmTKYS;
      string ILWScOesNY;
      string DSzLnLpazA;
      string TIaNTfNFeP;
      string SRtDhdDtjw;
      string SmlZmJtEJF;
      string xrLYzAkJzw;
      string AZNyGkYudK;
      string IuqDhgVBZJ;
      if(qZcisXIiBo == paNMKxfAyp){kIuZRZGVDg = true;}
      else if(paNMKxfAyp == qZcisXIiBo){FsbDbUZtzq = true;}
      if(pTCZqoPrLD == csQyRmTKYS){ssumurZnSC = true;}
      else if(csQyRmTKYS == pTCZqoPrLD){eFNtNbxcYF = true;}
      if(ebKJFofCNe == ILWScOesNY){jyZzxCBIqS = true;}
      else if(ILWScOesNY == ebKJFofCNe){GwoDtearfr = true;}
      if(VYhaKoxgCt == DSzLnLpazA){ejjoLremff = true;}
      else if(DSzLnLpazA == VYhaKoxgCt){IAhYbIUxYq = true;}
      if(rypoHaCbOD == TIaNTfNFeP){dDrxROzDHo = true;}
      else if(TIaNTfNFeP == rypoHaCbOD){XHNYsDUQCe = true;}
      if(gWQJWOPScE == SRtDhdDtjw){GghWYlhwbP = true;}
      else if(SRtDhdDtjw == gWQJWOPScE){hugoCJEYJx = true;}
      if(qGVWSQkaOC == SmlZmJtEJF){YydkCIJFbD = true;}
      else if(SmlZmJtEJF == qGVWSQkaOC){shOGieWoSF = true;}
      if(ripQKflVCe == xrLYzAkJzw){NlHmXgGchh = true;}
      if(mDmKyzIYEw == AZNyGkYudK){CxABLxCMQY = true;}
      if(ZdDxClcSWp == IuqDhgVBZJ){JhKPHfYGtI = true;}
      while(xrLYzAkJzw == ripQKflVCe){GADhhyhQJp = true;}
      while(AZNyGkYudK == AZNyGkYudK){KKoAKMSsWS = true;}
      while(IuqDhgVBZJ == IuqDhgVBZJ){EwmbxprHoO = true;}
      if(kIuZRZGVDg == true){kIuZRZGVDg = false;}
      if(ssumurZnSC == true){ssumurZnSC = false;}
      if(jyZzxCBIqS == true){jyZzxCBIqS = false;}
      if(ejjoLremff == true){ejjoLremff = false;}
      if(dDrxROzDHo == true){dDrxROzDHo = false;}
      if(GghWYlhwbP == true){GghWYlhwbP = false;}
      if(YydkCIJFbD == true){YydkCIJFbD = false;}
      if(NlHmXgGchh == true){NlHmXgGchh = false;}
      if(CxABLxCMQY == true){CxABLxCMQY = false;}
      if(JhKPHfYGtI == true){JhKPHfYGtI = false;}
      if(FsbDbUZtzq == true){FsbDbUZtzq = false;}
      if(eFNtNbxcYF == true){eFNtNbxcYF = false;}
      if(GwoDtearfr == true){GwoDtearfr = false;}
      if(IAhYbIUxYq == true){IAhYbIUxYq = false;}
      if(XHNYsDUQCe == true){XHNYsDUQCe = false;}
      if(hugoCJEYJx == true){hugoCJEYJx = false;}
      if(shOGieWoSF == true){shOGieWoSF = false;}
      if(GADhhyhQJp == true){GADhhyhQJp = false;}
      if(KKoAKMSsWS == true){KKoAKMSsWS = false;}
      if(EwmbxprHoO == true){EwmbxprHoO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ECRFQFGDXR
{ 
  void WInUrKEPcC()
  { 
      bool bWNURNzMXa = false;
      bool aVbEXjrVbe = false;
      bool lMiIUkAcXY = false;
      bool uqJIKwJeww = false;
      bool oLnAYREfgf = false;
      bool EgzUKPnFzf = false;
      bool MVozeiLSsb = false;
      bool aMYfpZXhiC = false;
      bool fUwqTOroxt = false;
      bool IDePiSWoUp = false;
      bool FllFFqHSdj = false;
      bool rFVwArYxeQ = false;
      bool pWUzTWgJxW = false;
      bool DhMsxthqkc = false;
      bool GZKMBCghPq = false;
      bool sYJEziQmlh = false;
      bool JyVGgKsczF = false;
      bool JhMCJQLHyQ = false;
      bool pysFddXItN = false;
      bool duFCSIEEfq = false;
      string FdEISGbAYg;
      string ZMQUxLIjTy;
      string TilflROIdn;
      string LRWfOaQrDG;
      string ejxZTRrDCm;
      string QBuOXVrXVA;
      string qSWjUHpjGW;
      string tPfNTilLMU;
      string ZKGpXKVIHr;
      string hsWDPLNMEL;
      string bHwesAUhto;
      string jfLBZfMfLK;
      string lgbOnBscxI;
      string VYGBsSOaxX;
      string omNSIBgVci;
      string yhAtYtehpr;
      string HrjlSKYKHH;
      string RkinVyTJGl;
      string TWAOJnXMbz;
      string mfjFQwCbzx;
      if(FdEISGbAYg == bHwesAUhto){bWNURNzMXa = true;}
      else if(bHwesAUhto == FdEISGbAYg){FllFFqHSdj = true;}
      if(ZMQUxLIjTy == jfLBZfMfLK){aVbEXjrVbe = true;}
      else if(jfLBZfMfLK == ZMQUxLIjTy){rFVwArYxeQ = true;}
      if(TilflROIdn == lgbOnBscxI){lMiIUkAcXY = true;}
      else if(lgbOnBscxI == TilflROIdn){pWUzTWgJxW = true;}
      if(LRWfOaQrDG == VYGBsSOaxX){uqJIKwJeww = true;}
      else if(VYGBsSOaxX == LRWfOaQrDG){DhMsxthqkc = true;}
      if(ejxZTRrDCm == omNSIBgVci){oLnAYREfgf = true;}
      else if(omNSIBgVci == ejxZTRrDCm){GZKMBCghPq = true;}
      if(QBuOXVrXVA == yhAtYtehpr){EgzUKPnFzf = true;}
      else if(yhAtYtehpr == QBuOXVrXVA){sYJEziQmlh = true;}
      if(qSWjUHpjGW == HrjlSKYKHH){MVozeiLSsb = true;}
      else if(HrjlSKYKHH == qSWjUHpjGW){JyVGgKsczF = true;}
      if(tPfNTilLMU == RkinVyTJGl){aMYfpZXhiC = true;}
      if(ZKGpXKVIHr == TWAOJnXMbz){fUwqTOroxt = true;}
      if(hsWDPLNMEL == mfjFQwCbzx){IDePiSWoUp = true;}
      while(RkinVyTJGl == tPfNTilLMU){JhMCJQLHyQ = true;}
      while(TWAOJnXMbz == TWAOJnXMbz){pysFddXItN = true;}
      while(mfjFQwCbzx == mfjFQwCbzx){duFCSIEEfq = true;}
      if(bWNURNzMXa == true){bWNURNzMXa = false;}
      if(aVbEXjrVbe == true){aVbEXjrVbe = false;}
      if(lMiIUkAcXY == true){lMiIUkAcXY = false;}
      if(uqJIKwJeww == true){uqJIKwJeww = false;}
      if(oLnAYREfgf == true){oLnAYREfgf = false;}
      if(EgzUKPnFzf == true){EgzUKPnFzf = false;}
      if(MVozeiLSsb == true){MVozeiLSsb = false;}
      if(aMYfpZXhiC == true){aMYfpZXhiC = false;}
      if(fUwqTOroxt == true){fUwqTOroxt = false;}
      if(IDePiSWoUp == true){IDePiSWoUp = false;}
      if(FllFFqHSdj == true){FllFFqHSdj = false;}
      if(rFVwArYxeQ == true){rFVwArYxeQ = false;}
      if(pWUzTWgJxW == true){pWUzTWgJxW = false;}
      if(DhMsxthqkc == true){DhMsxthqkc = false;}
      if(GZKMBCghPq == true){GZKMBCghPq = false;}
      if(sYJEziQmlh == true){sYJEziQmlh = false;}
      if(JyVGgKsczF == true){JyVGgKsczF = false;}
      if(JhMCJQLHyQ == true){JhMCJQLHyQ = false;}
      if(pysFddXItN == true){pysFddXItN = false;}
      if(duFCSIEEfq == true){duFCSIEEfq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DEUZPWMJZI
{ 
  void XNQUgSyiqz()
  { 
      bool nUoQcACBcl = false;
      bool AIbYqhJadB = false;
      bool cAJWYkIggc = false;
      bool CkSkAtwsAa = false;
      bool TZHeDySrnF = false;
      bool WcMWknKSqr = false;
      bool qVUzjPpqXw = false;
      bool lPaChCseSa = false;
      bool RQraGZXuAM = false;
      bool icCIjyFHum = false;
      bool IbUrTHBKoh = false;
      bool tfzPZactsJ = false;
      bool qtpKMINSRj = false;
      bool xkjfSpwAGy = false;
      bool XNFRRDdliI = false;
      bool ULNkuNlJeL = false;
      bool thrFkJuTxj = false;
      bool dbmtldoXrJ = false;
      bool eajJOkXzjF = false;
      bool DlVuEpVzgI = false;
      string DRntPelIiX;
      string QTPLxSmJsU;
      string QDtoGfFbHb;
      string ozrTVDdMSo;
      string nPGcYakkVF;
      string xQxnLzXzmi;
      string YJAHhRawos;
      string oaqDfBxQPf;
      string uTGCdYCEHV;
      string edYjPdOzuH;
      string znubQVZsHK;
      string CGiHmFDycI;
      string PWnSNKCGnC;
      string lxVIfGXdkH;
      string zIwxSYuQwK;
      string ZPVlrbAbNG;
      string TSEFXEjZaf;
      string gZMUJGaqAo;
      string OkJcbWbjQE;
      string GuQenfEpYO;
      if(DRntPelIiX == znubQVZsHK){nUoQcACBcl = true;}
      else if(znubQVZsHK == DRntPelIiX){IbUrTHBKoh = true;}
      if(QTPLxSmJsU == CGiHmFDycI){AIbYqhJadB = true;}
      else if(CGiHmFDycI == QTPLxSmJsU){tfzPZactsJ = true;}
      if(QDtoGfFbHb == PWnSNKCGnC){cAJWYkIggc = true;}
      else if(PWnSNKCGnC == QDtoGfFbHb){qtpKMINSRj = true;}
      if(ozrTVDdMSo == lxVIfGXdkH){CkSkAtwsAa = true;}
      else if(lxVIfGXdkH == ozrTVDdMSo){xkjfSpwAGy = true;}
      if(nPGcYakkVF == zIwxSYuQwK){TZHeDySrnF = true;}
      else if(zIwxSYuQwK == nPGcYakkVF){XNFRRDdliI = true;}
      if(xQxnLzXzmi == ZPVlrbAbNG){WcMWknKSqr = true;}
      else if(ZPVlrbAbNG == xQxnLzXzmi){ULNkuNlJeL = true;}
      if(YJAHhRawos == TSEFXEjZaf){qVUzjPpqXw = true;}
      else if(TSEFXEjZaf == YJAHhRawos){thrFkJuTxj = true;}
      if(oaqDfBxQPf == gZMUJGaqAo){lPaChCseSa = true;}
      if(uTGCdYCEHV == OkJcbWbjQE){RQraGZXuAM = true;}
      if(edYjPdOzuH == GuQenfEpYO){icCIjyFHum = true;}
      while(gZMUJGaqAo == oaqDfBxQPf){dbmtldoXrJ = true;}
      while(OkJcbWbjQE == OkJcbWbjQE){eajJOkXzjF = true;}
      while(GuQenfEpYO == GuQenfEpYO){DlVuEpVzgI = true;}
      if(nUoQcACBcl == true){nUoQcACBcl = false;}
      if(AIbYqhJadB == true){AIbYqhJadB = false;}
      if(cAJWYkIggc == true){cAJWYkIggc = false;}
      if(CkSkAtwsAa == true){CkSkAtwsAa = false;}
      if(TZHeDySrnF == true){TZHeDySrnF = false;}
      if(WcMWknKSqr == true){WcMWknKSqr = false;}
      if(qVUzjPpqXw == true){qVUzjPpqXw = false;}
      if(lPaChCseSa == true){lPaChCseSa = false;}
      if(RQraGZXuAM == true){RQraGZXuAM = false;}
      if(icCIjyFHum == true){icCIjyFHum = false;}
      if(IbUrTHBKoh == true){IbUrTHBKoh = false;}
      if(tfzPZactsJ == true){tfzPZactsJ = false;}
      if(qtpKMINSRj == true){qtpKMINSRj = false;}
      if(xkjfSpwAGy == true){xkjfSpwAGy = false;}
      if(XNFRRDdliI == true){XNFRRDdliI = false;}
      if(ULNkuNlJeL == true){ULNkuNlJeL = false;}
      if(thrFkJuTxj == true){thrFkJuTxj = false;}
      if(dbmtldoXrJ == true){dbmtldoXrJ = false;}
      if(eajJOkXzjF == true){eajJOkXzjF = false;}
      if(DlVuEpVzgI == true){DlVuEpVzgI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LEWYJVDSPN
{ 
  void pDeYIlogqI()
  { 
      bool lKhEERdSjR = false;
      bool UViJHyGoNt = false;
      bool UIcAXInhcO = false;
      bool tLmWCdjoNI = false;
      bool LTccjADfBK = false;
      bool XKeOudhhgu = false;
      bool dwoUXJiMHc = false;
      bool OQbEiBezQW = false;
      bool EHfSqifYbX = false;
      bool wCIRdPeHFZ = false;
      bool RqYYwGhZet = false;
      bool ziRKqWPWdn = false;
      bool cKjigLIJZT = false;
      bool WWspENhGWj = false;
      bool BGsgYMkxaG = false;
      bool zHdRxHGorj = false;
      bool xYALXbpaFd = false;
      bool oIAsmWQDKT = false;
      bool aKiSTOsbsx = false;
      bool GrOlmbFhJw = false;
      string ExTxWFwHSr;
      string QSuTsAZtXC;
      string WsqTZnIuiE;
      string uepPiaNtRA;
      string QrhyyloRMH;
      string DVxyZLFAWi;
      string wBYOxkcfjR;
      string lebWleKsUm;
      string yqiaAYhroX;
      string UNXiEOSSBN;
      string JJhtUYsZLu;
      string AMeijESxNX;
      string CjpLwXGsRX;
      string LrqGdoJnFa;
      string eIfsXHinzz;
      string wVFcLYSVyw;
      string RAHnjHVXFt;
      string udqlstDwmn;
      string oStRaomNuE;
      string WmpJJdArJQ;
      if(ExTxWFwHSr == JJhtUYsZLu){lKhEERdSjR = true;}
      else if(JJhtUYsZLu == ExTxWFwHSr){RqYYwGhZet = true;}
      if(QSuTsAZtXC == AMeijESxNX){UViJHyGoNt = true;}
      else if(AMeijESxNX == QSuTsAZtXC){ziRKqWPWdn = true;}
      if(WsqTZnIuiE == CjpLwXGsRX){UIcAXInhcO = true;}
      else if(CjpLwXGsRX == WsqTZnIuiE){cKjigLIJZT = true;}
      if(uepPiaNtRA == LrqGdoJnFa){tLmWCdjoNI = true;}
      else if(LrqGdoJnFa == uepPiaNtRA){WWspENhGWj = true;}
      if(QrhyyloRMH == eIfsXHinzz){LTccjADfBK = true;}
      else if(eIfsXHinzz == QrhyyloRMH){BGsgYMkxaG = true;}
      if(DVxyZLFAWi == wVFcLYSVyw){XKeOudhhgu = true;}
      else if(wVFcLYSVyw == DVxyZLFAWi){zHdRxHGorj = true;}
      if(wBYOxkcfjR == RAHnjHVXFt){dwoUXJiMHc = true;}
      else if(RAHnjHVXFt == wBYOxkcfjR){xYALXbpaFd = true;}
      if(lebWleKsUm == udqlstDwmn){OQbEiBezQW = true;}
      if(yqiaAYhroX == oStRaomNuE){EHfSqifYbX = true;}
      if(UNXiEOSSBN == WmpJJdArJQ){wCIRdPeHFZ = true;}
      while(udqlstDwmn == lebWleKsUm){oIAsmWQDKT = true;}
      while(oStRaomNuE == oStRaomNuE){aKiSTOsbsx = true;}
      while(WmpJJdArJQ == WmpJJdArJQ){GrOlmbFhJw = true;}
      if(lKhEERdSjR == true){lKhEERdSjR = false;}
      if(UViJHyGoNt == true){UViJHyGoNt = false;}
      if(UIcAXInhcO == true){UIcAXInhcO = false;}
      if(tLmWCdjoNI == true){tLmWCdjoNI = false;}
      if(LTccjADfBK == true){LTccjADfBK = false;}
      if(XKeOudhhgu == true){XKeOudhhgu = false;}
      if(dwoUXJiMHc == true){dwoUXJiMHc = false;}
      if(OQbEiBezQW == true){OQbEiBezQW = false;}
      if(EHfSqifYbX == true){EHfSqifYbX = false;}
      if(wCIRdPeHFZ == true){wCIRdPeHFZ = false;}
      if(RqYYwGhZet == true){RqYYwGhZet = false;}
      if(ziRKqWPWdn == true){ziRKqWPWdn = false;}
      if(cKjigLIJZT == true){cKjigLIJZT = false;}
      if(WWspENhGWj == true){WWspENhGWj = false;}
      if(BGsgYMkxaG == true){BGsgYMkxaG = false;}
      if(zHdRxHGorj == true){zHdRxHGorj = false;}
      if(xYALXbpaFd == true){xYALXbpaFd = false;}
      if(oIAsmWQDKT == true){oIAsmWQDKT = false;}
      if(aKiSTOsbsx == true){aKiSTOsbsx = false;}
      if(GrOlmbFhJw == true){GrOlmbFhJw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YIHOWKTZVK
{ 
  void IDyaUbVWDu()
  { 
      bool XrNgsjFqlJ = false;
      bool LVafmtaBzF = false;
      bool JhiVjiezcB = false;
      bool CnXjLNSyzU = false;
      bool VshlpkUeCg = false;
      bool CIZVQoJqxK = false;
      bool FGNjHXypTZ = false;
      bool abCejPAxfy = false;
      bool NAxwzsOBTW = false;
      bool DaBnOPfxeS = false;
      bool meKbFaGtlB = false;
      bool nMLzxFIRkN = false;
      bool IxWxVAaNPU = false;
      bool jCRMLioVpY = false;
      bool lTPShqPCqI = false;
      bool GNMRJpHNFF = false;
      bool AsdQQltymO = false;
      bool QmaMangDOd = false;
      bool jXWGNVpACV = false;
      bool abPkYspyBw = false;
      string fPYQnrKLlL;
      string GYeSBXnVxS;
      string qbGWUKhyeo;
      string DbRIwZXiXt;
      string zAwnRZBkAX;
      string wIMCtDICwd;
      string JLgxIeHWWa;
      string zEyCSpeSEt;
      string IwyHrtOONr;
      string QVmskmTzfm;
      string SeOYXqKKjD;
      string YpxBUMNYEO;
      string QrJdKdREQe;
      string WelRbchYiA;
      string iDeJTaXlYY;
      string ZutRVZVkOs;
      string ZGsFgsDeYq;
      string eooDeMNzKi;
      string GffrFajUuC;
      string HwKoacJYbZ;
      if(fPYQnrKLlL == SeOYXqKKjD){XrNgsjFqlJ = true;}
      else if(SeOYXqKKjD == fPYQnrKLlL){meKbFaGtlB = true;}
      if(GYeSBXnVxS == YpxBUMNYEO){LVafmtaBzF = true;}
      else if(YpxBUMNYEO == GYeSBXnVxS){nMLzxFIRkN = true;}
      if(qbGWUKhyeo == QrJdKdREQe){JhiVjiezcB = true;}
      else if(QrJdKdREQe == qbGWUKhyeo){IxWxVAaNPU = true;}
      if(DbRIwZXiXt == WelRbchYiA){CnXjLNSyzU = true;}
      else if(WelRbchYiA == DbRIwZXiXt){jCRMLioVpY = true;}
      if(zAwnRZBkAX == iDeJTaXlYY){VshlpkUeCg = true;}
      else if(iDeJTaXlYY == zAwnRZBkAX){lTPShqPCqI = true;}
      if(wIMCtDICwd == ZutRVZVkOs){CIZVQoJqxK = true;}
      else if(ZutRVZVkOs == wIMCtDICwd){GNMRJpHNFF = true;}
      if(JLgxIeHWWa == ZGsFgsDeYq){FGNjHXypTZ = true;}
      else if(ZGsFgsDeYq == JLgxIeHWWa){AsdQQltymO = true;}
      if(zEyCSpeSEt == eooDeMNzKi){abCejPAxfy = true;}
      if(IwyHrtOONr == GffrFajUuC){NAxwzsOBTW = true;}
      if(QVmskmTzfm == HwKoacJYbZ){DaBnOPfxeS = true;}
      while(eooDeMNzKi == zEyCSpeSEt){QmaMangDOd = true;}
      while(GffrFajUuC == GffrFajUuC){jXWGNVpACV = true;}
      while(HwKoacJYbZ == HwKoacJYbZ){abPkYspyBw = true;}
      if(XrNgsjFqlJ == true){XrNgsjFqlJ = false;}
      if(LVafmtaBzF == true){LVafmtaBzF = false;}
      if(JhiVjiezcB == true){JhiVjiezcB = false;}
      if(CnXjLNSyzU == true){CnXjLNSyzU = false;}
      if(VshlpkUeCg == true){VshlpkUeCg = false;}
      if(CIZVQoJqxK == true){CIZVQoJqxK = false;}
      if(FGNjHXypTZ == true){FGNjHXypTZ = false;}
      if(abCejPAxfy == true){abCejPAxfy = false;}
      if(NAxwzsOBTW == true){NAxwzsOBTW = false;}
      if(DaBnOPfxeS == true){DaBnOPfxeS = false;}
      if(meKbFaGtlB == true){meKbFaGtlB = false;}
      if(nMLzxFIRkN == true){nMLzxFIRkN = false;}
      if(IxWxVAaNPU == true){IxWxVAaNPU = false;}
      if(jCRMLioVpY == true){jCRMLioVpY = false;}
      if(lTPShqPCqI == true){lTPShqPCqI = false;}
      if(GNMRJpHNFF == true){GNMRJpHNFF = false;}
      if(AsdQQltymO == true){AsdQQltymO = false;}
      if(QmaMangDOd == true){QmaMangDOd = false;}
      if(jXWGNVpACV == true){jXWGNVpACV = false;}
      if(abPkYspyBw == true){abPkYspyBw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPCIAFGKXV
{ 
  void sVXnRXsJYF()
  { 
      bool PSdmoHKjJD = false;
      bool ZlZTdIlnaK = false;
      bool BpHYWEOTEf = false;
      bool rJPbXBDXYJ = false;
      bool ZrWHZnQRGn = false;
      bool fSHCKYKEQj = false;
      bool spedLQWyub = false;
      bool EOOQjISzzh = false;
      bool nxMPAZBNRz = false;
      bool pzGnQjMswI = false;
      bool RSWejQDpRB = false;
      bool FLFiwucPdl = false;
      bool OJgukFIaAz = false;
      bool wZDpPVahfi = false;
      bool VLuQsesWrU = false;
      bool GxPJtHlatd = false;
      bool IboRFfHOSZ = false;
      bool UuitPDOPCF = false;
      bool LkifszJswI = false;
      bool jAmBZtWcLM = false;
      string AsFgykHmdD;
      string QkiRJuVXUr;
      string dUPAoWpnNY;
      string czdyKfXnBh;
      string TbfAboiwMb;
      string JQnnwfdFrb;
      string uTZEaRGkGd;
      string XgWmXBoPXA;
      string ntblPLKoBe;
      string CRuZmzCaYK;
      string hxoiDbtBPt;
      string pOgrnBrmoP;
      string HQibbFlwzY;
      string zNpNRpErhm;
      string QIZHnmkDkl;
      string HOkICRONHy;
      string pxBqucXSZy;
      string wzEBzyqbmn;
      string UhLNQjbgLA;
      string aqkjxSGhML;
      if(AsFgykHmdD == hxoiDbtBPt){PSdmoHKjJD = true;}
      else if(hxoiDbtBPt == AsFgykHmdD){RSWejQDpRB = true;}
      if(QkiRJuVXUr == pOgrnBrmoP){ZlZTdIlnaK = true;}
      else if(pOgrnBrmoP == QkiRJuVXUr){FLFiwucPdl = true;}
      if(dUPAoWpnNY == HQibbFlwzY){BpHYWEOTEf = true;}
      else if(HQibbFlwzY == dUPAoWpnNY){OJgukFIaAz = true;}
      if(czdyKfXnBh == zNpNRpErhm){rJPbXBDXYJ = true;}
      else if(zNpNRpErhm == czdyKfXnBh){wZDpPVahfi = true;}
      if(TbfAboiwMb == QIZHnmkDkl){ZrWHZnQRGn = true;}
      else if(QIZHnmkDkl == TbfAboiwMb){VLuQsesWrU = true;}
      if(JQnnwfdFrb == HOkICRONHy){fSHCKYKEQj = true;}
      else if(HOkICRONHy == JQnnwfdFrb){GxPJtHlatd = true;}
      if(uTZEaRGkGd == pxBqucXSZy){spedLQWyub = true;}
      else if(pxBqucXSZy == uTZEaRGkGd){IboRFfHOSZ = true;}
      if(XgWmXBoPXA == wzEBzyqbmn){EOOQjISzzh = true;}
      if(ntblPLKoBe == UhLNQjbgLA){nxMPAZBNRz = true;}
      if(CRuZmzCaYK == aqkjxSGhML){pzGnQjMswI = true;}
      while(wzEBzyqbmn == XgWmXBoPXA){UuitPDOPCF = true;}
      while(UhLNQjbgLA == UhLNQjbgLA){LkifszJswI = true;}
      while(aqkjxSGhML == aqkjxSGhML){jAmBZtWcLM = true;}
      if(PSdmoHKjJD == true){PSdmoHKjJD = false;}
      if(ZlZTdIlnaK == true){ZlZTdIlnaK = false;}
      if(BpHYWEOTEf == true){BpHYWEOTEf = false;}
      if(rJPbXBDXYJ == true){rJPbXBDXYJ = false;}
      if(ZrWHZnQRGn == true){ZrWHZnQRGn = false;}
      if(fSHCKYKEQj == true){fSHCKYKEQj = false;}
      if(spedLQWyub == true){spedLQWyub = false;}
      if(EOOQjISzzh == true){EOOQjISzzh = false;}
      if(nxMPAZBNRz == true){nxMPAZBNRz = false;}
      if(pzGnQjMswI == true){pzGnQjMswI = false;}
      if(RSWejQDpRB == true){RSWejQDpRB = false;}
      if(FLFiwucPdl == true){FLFiwucPdl = false;}
      if(OJgukFIaAz == true){OJgukFIaAz = false;}
      if(wZDpPVahfi == true){wZDpPVahfi = false;}
      if(VLuQsesWrU == true){VLuQsesWrU = false;}
      if(GxPJtHlatd == true){GxPJtHlatd = false;}
      if(IboRFfHOSZ == true){IboRFfHOSZ = false;}
      if(UuitPDOPCF == true){UuitPDOPCF = false;}
      if(LkifszJswI == true){LkifszJswI = false;}
      if(jAmBZtWcLM == true){jAmBZtWcLM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYLVCYKCVE
{ 
  void kQYSmQWstg()
  { 
      bool MAEYVKORWM = false;
      bool ywDVsgHEmI = false;
      bool lEhGSwEzAu = false;
      bool KgQrVWhpug = false;
      bool ysEygwtrGF = false;
      bool rKftDISxFZ = false;
      bool GORbBRfLAV = false;
      bool zQIGJsAiYV = false;
      bool BLrtCzAWnN = false;
      bool DjkUaibbxP = false;
      bool QhrkGbBYjK = false;
      bool HjYjYtWWYB = false;
      bool QIXmSOfmfa = false;
      bool QYlJFSSHna = false;
      bool yalcFTLBwf = false;
      bool MECuzHKFRq = false;
      bool uNsJsiyOeF = false;
      bool bOiyDoWtgy = false;
      bool DeqAOMVpKx = false;
      bool HNowejhcjW = false;
      string iZjXamQzlf;
      string XlesSdpCtm;
      string wIWwclRdkn;
      string VWlTYWZDuQ;
      string CruszzTadl;
      string jcglAZDnuo;
      string VlOxKAAKTw;
      string DlGckENcwd;
      string SqAyEsoATz;
      string TlIGuPdxiy;
      string zIGghxWEAu;
      string MZqQVelPsR;
      string LAqUcRdzhU;
      string aPsyeJjSQG;
      string WkzXmstqjQ;
      string cNERmzQlEQ;
      string TWVeUxfslL;
      string tSzmuZAThi;
      string XlORqMKaLf;
      string syOzmzPTCp;
      if(iZjXamQzlf == zIGghxWEAu){MAEYVKORWM = true;}
      else if(zIGghxWEAu == iZjXamQzlf){QhrkGbBYjK = true;}
      if(XlesSdpCtm == MZqQVelPsR){ywDVsgHEmI = true;}
      else if(MZqQVelPsR == XlesSdpCtm){HjYjYtWWYB = true;}
      if(wIWwclRdkn == LAqUcRdzhU){lEhGSwEzAu = true;}
      else if(LAqUcRdzhU == wIWwclRdkn){QIXmSOfmfa = true;}
      if(VWlTYWZDuQ == aPsyeJjSQG){KgQrVWhpug = true;}
      else if(aPsyeJjSQG == VWlTYWZDuQ){QYlJFSSHna = true;}
      if(CruszzTadl == WkzXmstqjQ){ysEygwtrGF = true;}
      else if(WkzXmstqjQ == CruszzTadl){yalcFTLBwf = true;}
      if(jcglAZDnuo == cNERmzQlEQ){rKftDISxFZ = true;}
      else if(cNERmzQlEQ == jcglAZDnuo){MECuzHKFRq = true;}
      if(VlOxKAAKTw == TWVeUxfslL){GORbBRfLAV = true;}
      else if(TWVeUxfslL == VlOxKAAKTw){uNsJsiyOeF = true;}
      if(DlGckENcwd == tSzmuZAThi){zQIGJsAiYV = true;}
      if(SqAyEsoATz == XlORqMKaLf){BLrtCzAWnN = true;}
      if(TlIGuPdxiy == syOzmzPTCp){DjkUaibbxP = true;}
      while(tSzmuZAThi == DlGckENcwd){bOiyDoWtgy = true;}
      while(XlORqMKaLf == XlORqMKaLf){DeqAOMVpKx = true;}
      while(syOzmzPTCp == syOzmzPTCp){HNowejhcjW = true;}
      if(MAEYVKORWM == true){MAEYVKORWM = false;}
      if(ywDVsgHEmI == true){ywDVsgHEmI = false;}
      if(lEhGSwEzAu == true){lEhGSwEzAu = false;}
      if(KgQrVWhpug == true){KgQrVWhpug = false;}
      if(ysEygwtrGF == true){ysEygwtrGF = false;}
      if(rKftDISxFZ == true){rKftDISxFZ = false;}
      if(GORbBRfLAV == true){GORbBRfLAV = false;}
      if(zQIGJsAiYV == true){zQIGJsAiYV = false;}
      if(BLrtCzAWnN == true){BLrtCzAWnN = false;}
      if(DjkUaibbxP == true){DjkUaibbxP = false;}
      if(QhrkGbBYjK == true){QhrkGbBYjK = false;}
      if(HjYjYtWWYB == true){HjYjYtWWYB = false;}
      if(QIXmSOfmfa == true){QIXmSOfmfa = false;}
      if(QYlJFSSHna == true){QYlJFSSHna = false;}
      if(yalcFTLBwf == true){yalcFTLBwf = false;}
      if(MECuzHKFRq == true){MECuzHKFRq = false;}
      if(uNsJsiyOeF == true){uNsJsiyOeF = false;}
      if(bOiyDoWtgy == true){bOiyDoWtgy = false;}
      if(DeqAOMVpKx == true){DeqAOMVpKx = false;}
      if(HNowejhcjW == true){HNowejhcjW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TZKBHJMFWH
{ 
  void SrqwLBkPdY()
  { 
      bool FocedzZYky = false;
      bool TTexrSiICq = false;
      bool VRMlUrGwKu = false;
      bool KFuOajOSFF = false;
      bool HikjQnWBzb = false;
      bool BBFfDnbpJk = false;
      bool rdNpnOXPVI = false;
      bool EQDwjmfbUg = false;
      bool UFwisIzPLm = false;
      bool HXIUMcVuwC = false;
      bool PGeqWjyIuQ = false;
      bool HAVcPmhdwf = false;
      bool OIEiBfHijG = false;
      bool QkfRROaEMJ = false;
      bool JpTueHCfEZ = false;
      bool uqyPnGCupp = false;
      bool cPYozWTDLB = false;
      bool LcRmVXnJDs = false;
      bool dadJKZlQdK = false;
      bool MeOVftRewI = false;
      string bALyNwsEIc;
      string ZqkVwehpdt;
      string PjUPknAePo;
      string aymBKBhCEi;
      string ADIRTLnUza;
      string hWuJhrewNY;
      string uNnSBaEjKu;
      string xfkutLbDuY;
      string AffnHDDcTS;
      string VlnfmlOoPr;
      string HEKDdClzOV;
      string PbAnYPhzLy;
      string XaQqZLqEHI;
      string wlnDRuUbKF;
      string RDNxDslzHX;
      string EOdRTfmSdR;
      string KgrGZdnwWc;
      string tFoFfUMTnf;
      string YqxiEhHWik;
      string HByrtkKHXY;
      if(bALyNwsEIc == HEKDdClzOV){FocedzZYky = true;}
      else if(HEKDdClzOV == bALyNwsEIc){PGeqWjyIuQ = true;}
      if(ZqkVwehpdt == PbAnYPhzLy){TTexrSiICq = true;}
      else if(PbAnYPhzLy == ZqkVwehpdt){HAVcPmhdwf = true;}
      if(PjUPknAePo == XaQqZLqEHI){VRMlUrGwKu = true;}
      else if(XaQqZLqEHI == PjUPknAePo){OIEiBfHijG = true;}
      if(aymBKBhCEi == wlnDRuUbKF){KFuOajOSFF = true;}
      else if(wlnDRuUbKF == aymBKBhCEi){QkfRROaEMJ = true;}
      if(ADIRTLnUza == RDNxDslzHX){HikjQnWBzb = true;}
      else if(RDNxDslzHX == ADIRTLnUza){JpTueHCfEZ = true;}
      if(hWuJhrewNY == EOdRTfmSdR){BBFfDnbpJk = true;}
      else if(EOdRTfmSdR == hWuJhrewNY){uqyPnGCupp = true;}
      if(uNnSBaEjKu == KgrGZdnwWc){rdNpnOXPVI = true;}
      else if(KgrGZdnwWc == uNnSBaEjKu){cPYozWTDLB = true;}
      if(xfkutLbDuY == tFoFfUMTnf){EQDwjmfbUg = true;}
      if(AffnHDDcTS == YqxiEhHWik){UFwisIzPLm = true;}
      if(VlnfmlOoPr == HByrtkKHXY){HXIUMcVuwC = true;}
      while(tFoFfUMTnf == xfkutLbDuY){LcRmVXnJDs = true;}
      while(YqxiEhHWik == YqxiEhHWik){dadJKZlQdK = true;}
      while(HByrtkKHXY == HByrtkKHXY){MeOVftRewI = true;}
      if(FocedzZYky == true){FocedzZYky = false;}
      if(TTexrSiICq == true){TTexrSiICq = false;}
      if(VRMlUrGwKu == true){VRMlUrGwKu = false;}
      if(KFuOajOSFF == true){KFuOajOSFF = false;}
      if(HikjQnWBzb == true){HikjQnWBzb = false;}
      if(BBFfDnbpJk == true){BBFfDnbpJk = false;}
      if(rdNpnOXPVI == true){rdNpnOXPVI = false;}
      if(EQDwjmfbUg == true){EQDwjmfbUg = false;}
      if(UFwisIzPLm == true){UFwisIzPLm = false;}
      if(HXIUMcVuwC == true){HXIUMcVuwC = false;}
      if(PGeqWjyIuQ == true){PGeqWjyIuQ = false;}
      if(HAVcPmhdwf == true){HAVcPmhdwf = false;}
      if(OIEiBfHijG == true){OIEiBfHijG = false;}
      if(QkfRROaEMJ == true){QkfRROaEMJ = false;}
      if(JpTueHCfEZ == true){JpTueHCfEZ = false;}
      if(uqyPnGCupp == true){uqyPnGCupp = false;}
      if(cPYozWTDLB == true){cPYozWTDLB = false;}
      if(LcRmVXnJDs == true){LcRmVXnJDs = false;}
      if(dadJKZlQdK == true){dadJKZlQdK = false;}
      if(MeOVftRewI == true){MeOVftRewI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVHLNLEAKZ
{ 
  void npcklihSVe()
  { 
      bool sLCydLQuxp = false;
      bool XNEXiKaPss = false;
      bool HWDewszLVC = false;
      bool kjutNRtOZt = false;
      bool sBPZQNJxoY = false;
      bool zjaotWHWBk = false;
      bool MEZtFnSKJR = false;
      bool PMoyAFGcOi = false;
      bool iBWwCBIGAq = false;
      bool JWMohnbUUc = false;
      bool uzmXJmtcnn = false;
      bool QdISBKhcrD = false;
      bool eMKSIrzAQL = false;
      bool dkIknjOymO = false;
      bool HfRLaeOtnX = false;
      bool GycQxinUOQ = false;
      bool ntLbJeVWeR = false;
      bool wipcwztyqc = false;
      bool dEMsFeHqnE = false;
      bool usjWaMTpCu = false;
      string ZPmCXHyBCf;
      string cGSSFftjrY;
      string kWrxwCWNYf;
      string FpcBKWgPks;
      string lAWoVdZIyT;
      string JVKXzCXoFU;
      string kkbVZlcRIi;
      string zezzmjzCbS;
      string bOPFWjfEBH;
      string yqJPIAXBPi;
      string AIAPTdWLkP;
      string CVMlsVUWzp;
      string GXQAjHUipl;
      string LylsRTOAks;
      string NUTlFceXWl;
      string fBBZccrzeM;
      string ImUzDDiTUY;
      string HUkGclEduH;
      string cxMEFJwMQo;
      string bOUYjZAUiB;
      if(ZPmCXHyBCf == AIAPTdWLkP){sLCydLQuxp = true;}
      else if(AIAPTdWLkP == ZPmCXHyBCf){uzmXJmtcnn = true;}
      if(cGSSFftjrY == CVMlsVUWzp){XNEXiKaPss = true;}
      else if(CVMlsVUWzp == cGSSFftjrY){QdISBKhcrD = true;}
      if(kWrxwCWNYf == GXQAjHUipl){HWDewszLVC = true;}
      else if(GXQAjHUipl == kWrxwCWNYf){eMKSIrzAQL = true;}
      if(FpcBKWgPks == LylsRTOAks){kjutNRtOZt = true;}
      else if(LylsRTOAks == FpcBKWgPks){dkIknjOymO = true;}
      if(lAWoVdZIyT == NUTlFceXWl){sBPZQNJxoY = true;}
      else if(NUTlFceXWl == lAWoVdZIyT){HfRLaeOtnX = true;}
      if(JVKXzCXoFU == fBBZccrzeM){zjaotWHWBk = true;}
      else if(fBBZccrzeM == JVKXzCXoFU){GycQxinUOQ = true;}
      if(kkbVZlcRIi == ImUzDDiTUY){MEZtFnSKJR = true;}
      else if(ImUzDDiTUY == kkbVZlcRIi){ntLbJeVWeR = true;}
      if(zezzmjzCbS == HUkGclEduH){PMoyAFGcOi = true;}
      if(bOPFWjfEBH == cxMEFJwMQo){iBWwCBIGAq = true;}
      if(yqJPIAXBPi == bOUYjZAUiB){JWMohnbUUc = true;}
      while(HUkGclEduH == zezzmjzCbS){wipcwztyqc = true;}
      while(cxMEFJwMQo == cxMEFJwMQo){dEMsFeHqnE = true;}
      while(bOUYjZAUiB == bOUYjZAUiB){usjWaMTpCu = true;}
      if(sLCydLQuxp == true){sLCydLQuxp = false;}
      if(XNEXiKaPss == true){XNEXiKaPss = false;}
      if(HWDewszLVC == true){HWDewszLVC = false;}
      if(kjutNRtOZt == true){kjutNRtOZt = false;}
      if(sBPZQNJxoY == true){sBPZQNJxoY = false;}
      if(zjaotWHWBk == true){zjaotWHWBk = false;}
      if(MEZtFnSKJR == true){MEZtFnSKJR = false;}
      if(PMoyAFGcOi == true){PMoyAFGcOi = false;}
      if(iBWwCBIGAq == true){iBWwCBIGAq = false;}
      if(JWMohnbUUc == true){JWMohnbUUc = false;}
      if(uzmXJmtcnn == true){uzmXJmtcnn = false;}
      if(QdISBKhcrD == true){QdISBKhcrD = false;}
      if(eMKSIrzAQL == true){eMKSIrzAQL = false;}
      if(dkIknjOymO == true){dkIknjOymO = false;}
      if(HfRLaeOtnX == true){HfRLaeOtnX = false;}
      if(GycQxinUOQ == true){GycQxinUOQ = false;}
      if(ntLbJeVWeR == true){ntLbJeVWeR = false;}
      if(wipcwztyqc == true){wipcwztyqc = false;}
      if(dEMsFeHqnE == true){dEMsFeHqnE = false;}
      if(usjWaMTpCu == true){usjWaMTpCu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZGDFRTVRE
{ 
  void SlwTBfTMuJ()
  { 
      bool eftLDqnWWo = false;
      bool VQxgjXuFLX = false;
      bool BFygJNmmGV = false;
      bool ncIyVGtiRY = false;
      bool PTJcLnsTri = false;
      bool xYzgjYgMBp = false;
      bool EBPAArIyLd = false;
      bool dLmmHguUUV = false;
      bool TTtXXOdaOw = false;
      bool YghbUODIcT = false;
      bool etIOEllMYD = false;
      bool cLqfWjGrbk = false;
      bool OgjOEwdLRs = false;
      bool cmrBpYKfSl = false;
      bool cRCLSNoBFj = false;
      bool ILfqFyKsKI = false;
      bool IatfapSpox = false;
      bool YZYpHweYwp = false;
      bool HbGhjQGAwr = false;
      bool ORVKcCWWkb = false;
      string SnYoFaWwAy;
      string RcrOMHMbDK;
      string JJgZExaRdu;
      string DhndFalAgl;
      string IjTeRanFjZ;
      string UHWaKIGzjH;
      string zERFtjoOJk;
      string VMuQBZpCHd;
      string JUgDZwKNSw;
      string UmPYmDROjg;
      string lZuyEIMFZk;
      string SDqGydXOey;
      string YbuNQhwVdx;
      string HaRZqiZiyR;
      string iFmhcQwIaI;
      string fDjlIJdhhV;
      string LpabcrlQOO;
      string EnPMOSnNjA;
      string lnuVQEqfRh;
      string EqBcGseKFk;
      if(SnYoFaWwAy == lZuyEIMFZk){eftLDqnWWo = true;}
      else if(lZuyEIMFZk == SnYoFaWwAy){etIOEllMYD = true;}
      if(RcrOMHMbDK == SDqGydXOey){VQxgjXuFLX = true;}
      else if(SDqGydXOey == RcrOMHMbDK){cLqfWjGrbk = true;}
      if(JJgZExaRdu == YbuNQhwVdx){BFygJNmmGV = true;}
      else if(YbuNQhwVdx == JJgZExaRdu){OgjOEwdLRs = true;}
      if(DhndFalAgl == HaRZqiZiyR){ncIyVGtiRY = true;}
      else if(HaRZqiZiyR == DhndFalAgl){cmrBpYKfSl = true;}
      if(IjTeRanFjZ == iFmhcQwIaI){PTJcLnsTri = true;}
      else if(iFmhcQwIaI == IjTeRanFjZ){cRCLSNoBFj = true;}
      if(UHWaKIGzjH == fDjlIJdhhV){xYzgjYgMBp = true;}
      else if(fDjlIJdhhV == UHWaKIGzjH){ILfqFyKsKI = true;}
      if(zERFtjoOJk == LpabcrlQOO){EBPAArIyLd = true;}
      else if(LpabcrlQOO == zERFtjoOJk){IatfapSpox = true;}
      if(VMuQBZpCHd == EnPMOSnNjA){dLmmHguUUV = true;}
      if(JUgDZwKNSw == lnuVQEqfRh){TTtXXOdaOw = true;}
      if(UmPYmDROjg == EqBcGseKFk){YghbUODIcT = true;}
      while(EnPMOSnNjA == VMuQBZpCHd){YZYpHweYwp = true;}
      while(lnuVQEqfRh == lnuVQEqfRh){HbGhjQGAwr = true;}
      while(EqBcGseKFk == EqBcGseKFk){ORVKcCWWkb = true;}
      if(eftLDqnWWo == true){eftLDqnWWo = false;}
      if(VQxgjXuFLX == true){VQxgjXuFLX = false;}
      if(BFygJNmmGV == true){BFygJNmmGV = false;}
      if(ncIyVGtiRY == true){ncIyVGtiRY = false;}
      if(PTJcLnsTri == true){PTJcLnsTri = false;}
      if(xYzgjYgMBp == true){xYzgjYgMBp = false;}
      if(EBPAArIyLd == true){EBPAArIyLd = false;}
      if(dLmmHguUUV == true){dLmmHguUUV = false;}
      if(TTtXXOdaOw == true){TTtXXOdaOw = false;}
      if(YghbUODIcT == true){YghbUODIcT = false;}
      if(etIOEllMYD == true){etIOEllMYD = false;}
      if(cLqfWjGrbk == true){cLqfWjGrbk = false;}
      if(OgjOEwdLRs == true){OgjOEwdLRs = false;}
      if(cmrBpYKfSl == true){cmrBpYKfSl = false;}
      if(cRCLSNoBFj == true){cRCLSNoBFj = false;}
      if(ILfqFyKsKI == true){ILfqFyKsKI = false;}
      if(IatfapSpox == true){IatfapSpox = false;}
      if(YZYpHweYwp == true){YZYpHweYwp = false;}
      if(HbGhjQGAwr == true){HbGhjQGAwr = false;}
      if(ORVKcCWWkb == true){ORVKcCWWkb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZCUYTHHSZ
{ 
  void HFORxcBESl()
  { 
      bool FydOlQFesc = false;
      bool gDRXUxTKYO = false;
      bool HurQMEODGM = false;
      bool EuhnFqbCYk = false;
      bool DAHItZsyMB = false;
      bool nMDDsJFMCh = false;
      bool CBXfYkVdRc = false;
      bool UQlmKHnjWm = false;
      bool KQpFYqrdtw = false;
      bool kPApiBbajI = false;
      bool EPfjgXaPsl = false;
      bool VVoPXkLSHh = false;
      bool sqiVqEPuEI = false;
      bool eMAOhtjGXB = false;
      bool PckHZPZkSx = false;
      bool pJTCONfKsb = false;
      bool HeLkHIVagc = false;
      bool BEtFRQFaub = false;
      bool eecGRUrxzU = false;
      bool NZNwskRAAQ = false;
      string BpesWqSQbe;
      string KQLWsDIcRc;
      string mplrEYHaRl;
      string NLGHCRljbT;
      string hShtapxEYu;
      string EKgYsKDmny;
      string jqyoRzJEUb;
      string RYBxtTIrRN;
      string aCCVhDdhOq;
      string NywcjqTrca;
      string gsjxdfJjeY;
      string CLVZXhocHO;
      string VbpcNScXND;
      string APOqggRFrB;
      string stDpnCcVFC;
      string BpjNEFDGiK;
      string DlVaXmwdrp;
      string PjkFUbXzoL;
      string pGRLCJeAlb;
      string dLVgyHXbRB;
      if(BpesWqSQbe == gsjxdfJjeY){FydOlQFesc = true;}
      else if(gsjxdfJjeY == BpesWqSQbe){EPfjgXaPsl = true;}
      if(KQLWsDIcRc == CLVZXhocHO){gDRXUxTKYO = true;}
      else if(CLVZXhocHO == KQLWsDIcRc){VVoPXkLSHh = true;}
      if(mplrEYHaRl == VbpcNScXND){HurQMEODGM = true;}
      else if(VbpcNScXND == mplrEYHaRl){sqiVqEPuEI = true;}
      if(NLGHCRljbT == APOqggRFrB){EuhnFqbCYk = true;}
      else if(APOqggRFrB == NLGHCRljbT){eMAOhtjGXB = true;}
      if(hShtapxEYu == stDpnCcVFC){DAHItZsyMB = true;}
      else if(stDpnCcVFC == hShtapxEYu){PckHZPZkSx = true;}
      if(EKgYsKDmny == BpjNEFDGiK){nMDDsJFMCh = true;}
      else if(BpjNEFDGiK == EKgYsKDmny){pJTCONfKsb = true;}
      if(jqyoRzJEUb == DlVaXmwdrp){CBXfYkVdRc = true;}
      else if(DlVaXmwdrp == jqyoRzJEUb){HeLkHIVagc = true;}
      if(RYBxtTIrRN == PjkFUbXzoL){UQlmKHnjWm = true;}
      if(aCCVhDdhOq == pGRLCJeAlb){KQpFYqrdtw = true;}
      if(NywcjqTrca == dLVgyHXbRB){kPApiBbajI = true;}
      while(PjkFUbXzoL == RYBxtTIrRN){BEtFRQFaub = true;}
      while(pGRLCJeAlb == pGRLCJeAlb){eecGRUrxzU = true;}
      while(dLVgyHXbRB == dLVgyHXbRB){NZNwskRAAQ = true;}
      if(FydOlQFesc == true){FydOlQFesc = false;}
      if(gDRXUxTKYO == true){gDRXUxTKYO = false;}
      if(HurQMEODGM == true){HurQMEODGM = false;}
      if(EuhnFqbCYk == true){EuhnFqbCYk = false;}
      if(DAHItZsyMB == true){DAHItZsyMB = false;}
      if(nMDDsJFMCh == true){nMDDsJFMCh = false;}
      if(CBXfYkVdRc == true){CBXfYkVdRc = false;}
      if(UQlmKHnjWm == true){UQlmKHnjWm = false;}
      if(KQpFYqrdtw == true){KQpFYqrdtw = false;}
      if(kPApiBbajI == true){kPApiBbajI = false;}
      if(EPfjgXaPsl == true){EPfjgXaPsl = false;}
      if(VVoPXkLSHh == true){VVoPXkLSHh = false;}
      if(sqiVqEPuEI == true){sqiVqEPuEI = false;}
      if(eMAOhtjGXB == true){eMAOhtjGXB = false;}
      if(PckHZPZkSx == true){PckHZPZkSx = false;}
      if(pJTCONfKsb == true){pJTCONfKsb = false;}
      if(HeLkHIVagc == true){HeLkHIVagc = false;}
      if(BEtFRQFaub == true){BEtFRQFaub = false;}
      if(eecGRUrxzU == true){eecGRUrxzU = false;}
      if(NZNwskRAAQ == true){NZNwskRAAQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNWDLEWSAA
{ 
  void ccCPztUgQG()
  { 
      bool PKDsggxdjU = false;
      bool EhszQIsRMw = false;
      bool shUTTuPhcn = false;
      bool SugSspCVnh = false;
      bool KHEMKDupUl = false;
      bool djMnIhpiZl = false;
      bool QPBwBIAZFZ = false;
      bool FWceklcHJQ = false;
      bool zYNpJhirKL = false;
      bool ASwCQuGILB = false;
      bool CUjugHGhDW = false;
      bool EhZIlqCKmS = false;
      bool ZHPtYmZaNp = false;
      bool eTwHNdnSJC = false;
      bool bAonGSrmPZ = false;
      bool suVratFpVs = false;
      bool gfUMqklRtH = false;
      bool CiBjqZRbmG = false;
      bool tlKmwjyDgS = false;
      bool YywPUuebwV = false;
      string HqKyJGLUiZ;
      string RIrESodVJz;
      string IMJIlbwBOg;
      string cmFPybnXUQ;
      string EtlkhzjYwf;
      string OYUZtugBLg;
      string KKFBweCcGq;
      string AFBsuOZYal;
      string rWEhSERfUD;
      string tmMmFsnknC;
      string xHSFeIWade;
      string UHZYonFWhr;
      string MWHDwNsNmC;
      string aokXojDzCK;
      string gpBohmMmyR;
      string mRCupZzOIR;
      string OJnbEfWCiE;
      string jGTXLVURUJ;
      string BGPVOIlogP;
      string kopkuXCZjC;
      if(HqKyJGLUiZ == xHSFeIWade){PKDsggxdjU = true;}
      else if(xHSFeIWade == HqKyJGLUiZ){CUjugHGhDW = true;}
      if(RIrESodVJz == UHZYonFWhr){EhszQIsRMw = true;}
      else if(UHZYonFWhr == RIrESodVJz){EhZIlqCKmS = true;}
      if(IMJIlbwBOg == MWHDwNsNmC){shUTTuPhcn = true;}
      else if(MWHDwNsNmC == IMJIlbwBOg){ZHPtYmZaNp = true;}
      if(cmFPybnXUQ == aokXojDzCK){SugSspCVnh = true;}
      else if(aokXojDzCK == cmFPybnXUQ){eTwHNdnSJC = true;}
      if(EtlkhzjYwf == gpBohmMmyR){KHEMKDupUl = true;}
      else if(gpBohmMmyR == EtlkhzjYwf){bAonGSrmPZ = true;}
      if(OYUZtugBLg == mRCupZzOIR){djMnIhpiZl = true;}
      else if(mRCupZzOIR == OYUZtugBLg){suVratFpVs = true;}
      if(KKFBweCcGq == OJnbEfWCiE){QPBwBIAZFZ = true;}
      else if(OJnbEfWCiE == KKFBweCcGq){gfUMqklRtH = true;}
      if(AFBsuOZYal == jGTXLVURUJ){FWceklcHJQ = true;}
      if(rWEhSERfUD == BGPVOIlogP){zYNpJhirKL = true;}
      if(tmMmFsnknC == kopkuXCZjC){ASwCQuGILB = true;}
      while(jGTXLVURUJ == AFBsuOZYal){CiBjqZRbmG = true;}
      while(BGPVOIlogP == BGPVOIlogP){tlKmwjyDgS = true;}
      while(kopkuXCZjC == kopkuXCZjC){YywPUuebwV = true;}
      if(PKDsggxdjU == true){PKDsggxdjU = false;}
      if(EhszQIsRMw == true){EhszQIsRMw = false;}
      if(shUTTuPhcn == true){shUTTuPhcn = false;}
      if(SugSspCVnh == true){SugSspCVnh = false;}
      if(KHEMKDupUl == true){KHEMKDupUl = false;}
      if(djMnIhpiZl == true){djMnIhpiZl = false;}
      if(QPBwBIAZFZ == true){QPBwBIAZFZ = false;}
      if(FWceklcHJQ == true){FWceklcHJQ = false;}
      if(zYNpJhirKL == true){zYNpJhirKL = false;}
      if(ASwCQuGILB == true){ASwCQuGILB = false;}
      if(CUjugHGhDW == true){CUjugHGhDW = false;}
      if(EhZIlqCKmS == true){EhZIlqCKmS = false;}
      if(ZHPtYmZaNp == true){ZHPtYmZaNp = false;}
      if(eTwHNdnSJC == true){eTwHNdnSJC = false;}
      if(bAonGSrmPZ == true){bAonGSrmPZ = false;}
      if(suVratFpVs == true){suVratFpVs = false;}
      if(gfUMqklRtH == true){gfUMqklRtH = false;}
      if(CiBjqZRbmG == true){CiBjqZRbmG = false;}
      if(tlKmwjyDgS == true){tlKmwjyDgS = false;}
      if(YywPUuebwV == true){YywPUuebwV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEJCRPZVPL
{ 
  void XnSsrNccSH()
  { 
      bool bNAMyGnYiA = false;
      bool AWHSnGAutn = false;
      bool pGlRwSzTDo = false;
      bool qtfUwhCkLE = false;
      bool IyyyAnPRhN = false;
      bool BNiddUbhQe = false;
      bool HUUtIGpmVG = false;
      bool EOjpeqHnRI = false;
      bool DhkpmcKCpa = false;
      bool GTUgwncEot = false;
      bool xcuaJmdsyl = false;
      bool MmQHbZieGe = false;
      bool unwuAjsDsq = false;
      bool ODyWLalJfz = false;
      bool zRDENSDNEW = false;
      bool EyxKzIfAaZ = false;
      bool sazGXJotuA = false;
      bool mYyHfckrgg = false;
      bool gfyWmPFnXC = false;
      bool tliGGXSwgE = false;
      string paVZkeBjnX;
      string KyzylQnawS;
      string QmDTdtikzY;
      string MZAgQjlGzw;
      string PNQcCapyfL;
      string NsFKQDWCuq;
      string wPkOKkxShB;
      string ehbACDVZRD;
      string DkFmKSUpQN;
      string NjLIAAbBRR;
      string dXQeffRFHM;
      string gwjrmKJxDr;
      string QGCUnuVTzB;
      string aUIzYfTaHe;
      string APiDfQzTUo;
      string pdxZBXUwpk;
      string JyFFkMnkSH;
      string qipYqBXynX;
      string wCyJLxWhyB;
      string KXjWUCJcST;
      if(paVZkeBjnX == dXQeffRFHM){bNAMyGnYiA = true;}
      else if(dXQeffRFHM == paVZkeBjnX){xcuaJmdsyl = true;}
      if(KyzylQnawS == gwjrmKJxDr){AWHSnGAutn = true;}
      else if(gwjrmKJxDr == KyzylQnawS){MmQHbZieGe = true;}
      if(QmDTdtikzY == QGCUnuVTzB){pGlRwSzTDo = true;}
      else if(QGCUnuVTzB == QmDTdtikzY){unwuAjsDsq = true;}
      if(MZAgQjlGzw == aUIzYfTaHe){qtfUwhCkLE = true;}
      else if(aUIzYfTaHe == MZAgQjlGzw){ODyWLalJfz = true;}
      if(PNQcCapyfL == APiDfQzTUo){IyyyAnPRhN = true;}
      else if(APiDfQzTUo == PNQcCapyfL){zRDENSDNEW = true;}
      if(NsFKQDWCuq == pdxZBXUwpk){BNiddUbhQe = true;}
      else if(pdxZBXUwpk == NsFKQDWCuq){EyxKzIfAaZ = true;}
      if(wPkOKkxShB == JyFFkMnkSH){HUUtIGpmVG = true;}
      else if(JyFFkMnkSH == wPkOKkxShB){sazGXJotuA = true;}
      if(ehbACDVZRD == qipYqBXynX){EOjpeqHnRI = true;}
      if(DkFmKSUpQN == wCyJLxWhyB){DhkpmcKCpa = true;}
      if(NjLIAAbBRR == KXjWUCJcST){GTUgwncEot = true;}
      while(qipYqBXynX == ehbACDVZRD){mYyHfckrgg = true;}
      while(wCyJLxWhyB == wCyJLxWhyB){gfyWmPFnXC = true;}
      while(KXjWUCJcST == KXjWUCJcST){tliGGXSwgE = true;}
      if(bNAMyGnYiA == true){bNAMyGnYiA = false;}
      if(AWHSnGAutn == true){AWHSnGAutn = false;}
      if(pGlRwSzTDo == true){pGlRwSzTDo = false;}
      if(qtfUwhCkLE == true){qtfUwhCkLE = false;}
      if(IyyyAnPRhN == true){IyyyAnPRhN = false;}
      if(BNiddUbhQe == true){BNiddUbhQe = false;}
      if(HUUtIGpmVG == true){HUUtIGpmVG = false;}
      if(EOjpeqHnRI == true){EOjpeqHnRI = false;}
      if(DhkpmcKCpa == true){DhkpmcKCpa = false;}
      if(GTUgwncEot == true){GTUgwncEot = false;}
      if(xcuaJmdsyl == true){xcuaJmdsyl = false;}
      if(MmQHbZieGe == true){MmQHbZieGe = false;}
      if(unwuAjsDsq == true){unwuAjsDsq = false;}
      if(ODyWLalJfz == true){ODyWLalJfz = false;}
      if(zRDENSDNEW == true){zRDENSDNEW = false;}
      if(EyxKzIfAaZ == true){EyxKzIfAaZ = false;}
      if(sazGXJotuA == true){sazGXJotuA = false;}
      if(mYyHfckrgg == true){mYyHfckrgg = false;}
      if(gfyWmPFnXC == true){gfyWmPFnXC = false;}
      if(tliGGXSwgE == true){tliGGXSwgE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNPUZSBDJG
{ 
  void GejleRSVoh()
  { 
      bool wCjkRwcaeZ = false;
      bool tBwqYWNIjp = false;
      bool FdbFlGlAzH = false;
      bool bbEPdUWLmu = false;
      bool NZGjKWEjzj = false;
      bool aHqqoSaezK = false;
      bool KcbXxRwfNE = false;
      bool zCUobeWqtO = false;
      bool CBAOfUkNaL = false;
      bool trLbkkyimr = false;
      bool aXWujYlBOJ = false;
      bool uijjIIbMrb = false;
      bool giFBJHpsDq = false;
      bool fnDCndeFdH = false;
      bool iiyQQKIaTb = false;
      bool IkpLKqSUkc = false;
      bool hrxXcHegwd = false;
      bool dWhjsyknkz = false;
      bool yPZbitxrqx = false;
      bool LJTBZpkZnI = false;
      string AdSVRpliOV;
      string PTAAjxeJtq;
      string PxMoCoAfHD;
      string UbeHuHfYwc;
      string XYlZatjYga;
      string lQHwQCQcSc;
      string oGbKAnosFc;
      string QGMRSpLmOH;
      string EayfREThps;
      string pDFTmRxaYl;
      string FqTEKeDpda;
      string qdOLXOHusw;
      string UHCMlMArdB;
      string sjNbCNHtVl;
      string AcEPBLoswY;
      string JChbRxnGRx;
      string dKMbgHPlJK;
      string HNYGwrDmKZ;
      string XHwEqqBlKE;
      string YAbYHoPbht;
      if(AdSVRpliOV == FqTEKeDpda){wCjkRwcaeZ = true;}
      else if(FqTEKeDpda == AdSVRpliOV){aXWujYlBOJ = true;}
      if(PTAAjxeJtq == qdOLXOHusw){tBwqYWNIjp = true;}
      else if(qdOLXOHusw == PTAAjxeJtq){uijjIIbMrb = true;}
      if(PxMoCoAfHD == UHCMlMArdB){FdbFlGlAzH = true;}
      else if(UHCMlMArdB == PxMoCoAfHD){giFBJHpsDq = true;}
      if(UbeHuHfYwc == sjNbCNHtVl){bbEPdUWLmu = true;}
      else if(sjNbCNHtVl == UbeHuHfYwc){fnDCndeFdH = true;}
      if(XYlZatjYga == AcEPBLoswY){NZGjKWEjzj = true;}
      else if(AcEPBLoswY == XYlZatjYga){iiyQQKIaTb = true;}
      if(lQHwQCQcSc == JChbRxnGRx){aHqqoSaezK = true;}
      else if(JChbRxnGRx == lQHwQCQcSc){IkpLKqSUkc = true;}
      if(oGbKAnosFc == dKMbgHPlJK){KcbXxRwfNE = true;}
      else if(dKMbgHPlJK == oGbKAnosFc){hrxXcHegwd = true;}
      if(QGMRSpLmOH == HNYGwrDmKZ){zCUobeWqtO = true;}
      if(EayfREThps == XHwEqqBlKE){CBAOfUkNaL = true;}
      if(pDFTmRxaYl == YAbYHoPbht){trLbkkyimr = true;}
      while(HNYGwrDmKZ == QGMRSpLmOH){dWhjsyknkz = true;}
      while(XHwEqqBlKE == XHwEqqBlKE){yPZbitxrqx = true;}
      while(YAbYHoPbht == YAbYHoPbht){LJTBZpkZnI = true;}
      if(wCjkRwcaeZ == true){wCjkRwcaeZ = false;}
      if(tBwqYWNIjp == true){tBwqYWNIjp = false;}
      if(FdbFlGlAzH == true){FdbFlGlAzH = false;}
      if(bbEPdUWLmu == true){bbEPdUWLmu = false;}
      if(NZGjKWEjzj == true){NZGjKWEjzj = false;}
      if(aHqqoSaezK == true){aHqqoSaezK = false;}
      if(KcbXxRwfNE == true){KcbXxRwfNE = false;}
      if(zCUobeWqtO == true){zCUobeWqtO = false;}
      if(CBAOfUkNaL == true){CBAOfUkNaL = false;}
      if(trLbkkyimr == true){trLbkkyimr = false;}
      if(aXWujYlBOJ == true){aXWujYlBOJ = false;}
      if(uijjIIbMrb == true){uijjIIbMrb = false;}
      if(giFBJHpsDq == true){giFBJHpsDq = false;}
      if(fnDCndeFdH == true){fnDCndeFdH = false;}
      if(iiyQQKIaTb == true){iiyQQKIaTb = false;}
      if(IkpLKqSUkc == true){IkpLKqSUkc = false;}
      if(hrxXcHegwd == true){hrxXcHegwd = false;}
      if(dWhjsyknkz == true){dWhjsyknkz = false;}
      if(yPZbitxrqx == true){yPZbitxrqx = false;}
      if(LJTBZpkZnI == true){LJTBZpkZnI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTNXDRFXIE
{ 
  void WmAWCbIpDc()
  { 
      bool mqcUIPaZri = false;
      bool xLLDhHoZbn = false;
      bool xmwgDDDyRg = false;
      bool JFMJmhNVox = false;
      bool ZExQTBkuaQ = false;
      bool jxUHcAuuQE = false;
      bool LcIKZqzCPA = false;
      bool tTkdNsoeMC = false;
      bool SHXAxMjEfl = false;
      bool mREjlwwmqc = false;
      bool ChfZWPLqti = false;
      bool LPhOlDFHMM = false;
      bool GtVcNbOAqQ = false;
      bool xCnjzjbxdg = false;
      bool AsJxaXjpyh = false;
      bool qnZdVHMCMt = false;
      bool BLzdlIaxOC = false;
      bool aIcfMNkYBo = false;
      bool rYCIZIbKOr = false;
      bool XYjifotfLR = false;
      string jLZJOrZjEN;
      string PDidWkXwgN;
      string KrrDnRWsXJ;
      string kNIcRzWNhX;
      string gSWptiUusj;
      string YWnBRqSVVx;
      string UgLucBuFMX;
      string OJNJfqUCIF;
      string xbzmjOZGLZ;
      string fArkCAHaNr;
      string mOiVVOIeUZ;
      string WQMQzsgYLN;
      string bntmqNRbGf;
      string jtoQRhrdRV;
      string GukkDPnblI;
      string ShPzQzUueI;
      string xfXoobbwzR;
      string ADHoHgCIja;
      string ZppxNBdoAR;
      string NxzJXZWwwa;
      if(jLZJOrZjEN == mOiVVOIeUZ){mqcUIPaZri = true;}
      else if(mOiVVOIeUZ == jLZJOrZjEN){ChfZWPLqti = true;}
      if(PDidWkXwgN == WQMQzsgYLN){xLLDhHoZbn = true;}
      else if(WQMQzsgYLN == PDidWkXwgN){LPhOlDFHMM = true;}
      if(KrrDnRWsXJ == bntmqNRbGf){xmwgDDDyRg = true;}
      else if(bntmqNRbGf == KrrDnRWsXJ){GtVcNbOAqQ = true;}
      if(kNIcRzWNhX == jtoQRhrdRV){JFMJmhNVox = true;}
      else if(jtoQRhrdRV == kNIcRzWNhX){xCnjzjbxdg = true;}
      if(gSWptiUusj == GukkDPnblI){ZExQTBkuaQ = true;}
      else if(GukkDPnblI == gSWptiUusj){AsJxaXjpyh = true;}
      if(YWnBRqSVVx == ShPzQzUueI){jxUHcAuuQE = true;}
      else if(ShPzQzUueI == YWnBRqSVVx){qnZdVHMCMt = true;}
      if(UgLucBuFMX == xfXoobbwzR){LcIKZqzCPA = true;}
      else if(xfXoobbwzR == UgLucBuFMX){BLzdlIaxOC = true;}
      if(OJNJfqUCIF == ADHoHgCIja){tTkdNsoeMC = true;}
      if(xbzmjOZGLZ == ZppxNBdoAR){SHXAxMjEfl = true;}
      if(fArkCAHaNr == NxzJXZWwwa){mREjlwwmqc = true;}
      while(ADHoHgCIja == OJNJfqUCIF){aIcfMNkYBo = true;}
      while(ZppxNBdoAR == ZppxNBdoAR){rYCIZIbKOr = true;}
      while(NxzJXZWwwa == NxzJXZWwwa){XYjifotfLR = true;}
      if(mqcUIPaZri == true){mqcUIPaZri = false;}
      if(xLLDhHoZbn == true){xLLDhHoZbn = false;}
      if(xmwgDDDyRg == true){xmwgDDDyRg = false;}
      if(JFMJmhNVox == true){JFMJmhNVox = false;}
      if(ZExQTBkuaQ == true){ZExQTBkuaQ = false;}
      if(jxUHcAuuQE == true){jxUHcAuuQE = false;}
      if(LcIKZqzCPA == true){LcIKZqzCPA = false;}
      if(tTkdNsoeMC == true){tTkdNsoeMC = false;}
      if(SHXAxMjEfl == true){SHXAxMjEfl = false;}
      if(mREjlwwmqc == true){mREjlwwmqc = false;}
      if(ChfZWPLqti == true){ChfZWPLqti = false;}
      if(LPhOlDFHMM == true){LPhOlDFHMM = false;}
      if(GtVcNbOAqQ == true){GtVcNbOAqQ = false;}
      if(xCnjzjbxdg == true){xCnjzjbxdg = false;}
      if(AsJxaXjpyh == true){AsJxaXjpyh = false;}
      if(qnZdVHMCMt == true){qnZdVHMCMt = false;}
      if(BLzdlIaxOC == true){BLzdlIaxOC = false;}
      if(aIcfMNkYBo == true){aIcfMNkYBo = false;}
      if(rYCIZIbKOr == true){rYCIZIbKOr = false;}
      if(XYjifotfLR == true){XYjifotfLR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKNRGTDCJW
{ 
  void mdFmqpAnTR()
  { 
      bool yVXrVXOdFF = false;
      bool RmULAuIzdl = false;
      bool zQIwsbcSbM = false;
      bool mZnKxhPYTM = false;
      bool ImaQyikpBx = false;
      bool DWrzSgNbyt = false;
      bool twBrSqyJNR = false;
      bool ejfQdMprxK = false;
      bool plReJPgorP = false;
      bool UmaYSMkhyG = false;
      bool jaciRTqaUF = false;
      bool qVdmDHdViC = false;
      bool KIRxxrIGyR = false;
      bool aIspZPJhNo = false;
      bool YGTmYzJmVK = false;
      bool hPzwwbJekZ = false;
      bool KkbDdhbmMn = false;
      bool yuHsdDoeYy = false;
      bool hUjniLJxty = false;
      bool GexndmdQIp = false;
      string SKHHJtDrMQ;
      string dtjYPajFbS;
      string WexUsptFzi;
      string QOWyASDnZq;
      string nEWrzTVgxh;
      string CeUgkmNlOS;
      string zxrczPXkXx;
      string WwekdSIEVZ;
      string TNIQgltoNM;
      string ERYGqqLtrj;
      string wkJzKFziCR;
      string eIQozlnbuM;
      string UhWLrFWYtm;
      string HOLkciEJGa;
      string mLlwhwBjHE;
      string CjyfONNxHE;
      string iZoPKPxeLP;
      string heUUZJwacw;
      string EmQokXQfVP;
      string VGBBrMVWlR;
      if(SKHHJtDrMQ == wkJzKFziCR){yVXrVXOdFF = true;}
      else if(wkJzKFziCR == SKHHJtDrMQ){jaciRTqaUF = true;}
      if(dtjYPajFbS == eIQozlnbuM){RmULAuIzdl = true;}
      else if(eIQozlnbuM == dtjYPajFbS){qVdmDHdViC = true;}
      if(WexUsptFzi == UhWLrFWYtm){zQIwsbcSbM = true;}
      else if(UhWLrFWYtm == WexUsptFzi){KIRxxrIGyR = true;}
      if(QOWyASDnZq == HOLkciEJGa){mZnKxhPYTM = true;}
      else if(HOLkciEJGa == QOWyASDnZq){aIspZPJhNo = true;}
      if(nEWrzTVgxh == mLlwhwBjHE){ImaQyikpBx = true;}
      else if(mLlwhwBjHE == nEWrzTVgxh){YGTmYzJmVK = true;}
      if(CeUgkmNlOS == CjyfONNxHE){DWrzSgNbyt = true;}
      else if(CjyfONNxHE == CeUgkmNlOS){hPzwwbJekZ = true;}
      if(zxrczPXkXx == iZoPKPxeLP){twBrSqyJNR = true;}
      else if(iZoPKPxeLP == zxrczPXkXx){KkbDdhbmMn = true;}
      if(WwekdSIEVZ == heUUZJwacw){ejfQdMprxK = true;}
      if(TNIQgltoNM == EmQokXQfVP){plReJPgorP = true;}
      if(ERYGqqLtrj == VGBBrMVWlR){UmaYSMkhyG = true;}
      while(heUUZJwacw == WwekdSIEVZ){yuHsdDoeYy = true;}
      while(EmQokXQfVP == EmQokXQfVP){hUjniLJxty = true;}
      while(VGBBrMVWlR == VGBBrMVWlR){GexndmdQIp = true;}
      if(yVXrVXOdFF == true){yVXrVXOdFF = false;}
      if(RmULAuIzdl == true){RmULAuIzdl = false;}
      if(zQIwsbcSbM == true){zQIwsbcSbM = false;}
      if(mZnKxhPYTM == true){mZnKxhPYTM = false;}
      if(ImaQyikpBx == true){ImaQyikpBx = false;}
      if(DWrzSgNbyt == true){DWrzSgNbyt = false;}
      if(twBrSqyJNR == true){twBrSqyJNR = false;}
      if(ejfQdMprxK == true){ejfQdMprxK = false;}
      if(plReJPgorP == true){plReJPgorP = false;}
      if(UmaYSMkhyG == true){UmaYSMkhyG = false;}
      if(jaciRTqaUF == true){jaciRTqaUF = false;}
      if(qVdmDHdViC == true){qVdmDHdViC = false;}
      if(KIRxxrIGyR == true){KIRxxrIGyR = false;}
      if(aIspZPJhNo == true){aIspZPJhNo = false;}
      if(YGTmYzJmVK == true){YGTmYzJmVK = false;}
      if(hPzwwbJekZ == true){hPzwwbJekZ = false;}
      if(KkbDdhbmMn == true){KkbDdhbmMn = false;}
      if(yuHsdDoeYy == true){yuHsdDoeYy = false;}
      if(hUjniLJxty == true){hUjniLJxty = false;}
      if(GexndmdQIp == true){GexndmdQIp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYDYFMCRWU
{ 
  void CWSdZMfELF()
  { 
      bool McArXqtOfV = false;
      bool jYtocepuJB = false;
      bool hsaqoxfRYq = false;
      bool ktMLWSfYbn = false;
      bool FRlOTXsbCp = false;
      bool gKpefTCICa = false;
      bool KbpokpLhSK = false;
      bool yQTVwQGLXR = false;
      bool DEOiKZDgfC = false;
      bool PWWAccaxdc = false;
      bool LLIrqPpTiP = false;
      bool MpkkXGMGeK = false;
      bool ldCPtbtTsT = false;
      bool oJhtFruWrt = false;
      bool jjyPpZllcW = false;
      bool PTSSqhJsyP = false;
      bool UWaPZDIpee = false;
      bool KpOjaCelZT = false;
      bool oIpWDUqODX = false;
      bool iCYcYMIiom = false;
      string obQQXLPIQg;
      string WfEwTlETje;
      string kKGGpKmGxR;
      string IWzALQGAsZ;
      string kCjJEtzIjm;
      string tcPCZeUJZN;
      string XJKzXzfDjD;
      string fDaKthaxBw;
      string LeVKXfGxag;
      string uwZfBaqkkE;
      string NuXfHpCFHr;
      string EXIdBrmAaq;
      string ricDHiduJS;
      string poLxhPHpDg;
      string dBohcXnwdI;
      string nqJsMdSTYX;
      string MHuoBOLLul;
      string jxxtNpttZi;
      string ugQAezfRjD;
      string wmQeUWFAgO;
      if(obQQXLPIQg == NuXfHpCFHr){McArXqtOfV = true;}
      else if(NuXfHpCFHr == obQQXLPIQg){LLIrqPpTiP = true;}
      if(WfEwTlETje == EXIdBrmAaq){jYtocepuJB = true;}
      else if(EXIdBrmAaq == WfEwTlETje){MpkkXGMGeK = true;}
      if(kKGGpKmGxR == ricDHiduJS){hsaqoxfRYq = true;}
      else if(ricDHiduJS == kKGGpKmGxR){ldCPtbtTsT = true;}
      if(IWzALQGAsZ == poLxhPHpDg){ktMLWSfYbn = true;}
      else if(poLxhPHpDg == IWzALQGAsZ){oJhtFruWrt = true;}
      if(kCjJEtzIjm == dBohcXnwdI){FRlOTXsbCp = true;}
      else if(dBohcXnwdI == kCjJEtzIjm){jjyPpZllcW = true;}
      if(tcPCZeUJZN == nqJsMdSTYX){gKpefTCICa = true;}
      else if(nqJsMdSTYX == tcPCZeUJZN){PTSSqhJsyP = true;}
      if(XJKzXzfDjD == MHuoBOLLul){KbpokpLhSK = true;}
      else if(MHuoBOLLul == XJKzXzfDjD){UWaPZDIpee = true;}
      if(fDaKthaxBw == jxxtNpttZi){yQTVwQGLXR = true;}
      if(LeVKXfGxag == ugQAezfRjD){DEOiKZDgfC = true;}
      if(uwZfBaqkkE == wmQeUWFAgO){PWWAccaxdc = true;}
      while(jxxtNpttZi == fDaKthaxBw){KpOjaCelZT = true;}
      while(ugQAezfRjD == ugQAezfRjD){oIpWDUqODX = true;}
      while(wmQeUWFAgO == wmQeUWFAgO){iCYcYMIiom = true;}
      if(McArXqtOfV == true){McArXqtOfV = false;}
      if(jYtocepuJB == true){jYtocepuJB = false;}
      if(hsaqoxfRYq == true){hsaqoxfRYq = false;}
      if(ktMLWSfYbn == true){ktMLWSfYbn = false;}
      if(FRlOTXsbCp == true){FRlOTXsbCp = false;}
      if(gKpefTCICa == true){gKpefTCICa = false;}
      if(KbpokpLhSK == true){KbpokpLhSK = false;}
      if(yQTVwQGLXR == true){yQTVwQGLXR = false;}
      if(DEOiKZDgfC == true){DEOiKZDgfC = false;}
      if(PWWAccaxdc == true){PWWAccaxdc = false;}
      if(LLIrqPpTiP == true){LLIrqPpTiP = false;}
      if(MpkkXGMGeK == true){MpkkXGMGeK = false;}
      if(ldCPtbtTsT == true){ldCPtbtTsT = false;}
      if(oJhtFruWrt == true){oJhtFruWrt = false;}
      if(jjyPpZllcW == true){jjyPpZllcW = false;}
      if(PTSSqhJsyP == true){PTSSqhJsyP = false;}
      if(UWaPZDIpee == true){UWaPZDIpee = false;}
      if(KpOjaCelZT == true){KpOjaCelZT = false;}
      if(oIpWDUqODX == true){oIpWDUqODX = false;}
      if(iCYcYMIiom == true){iCYcYMIiom = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNNETQBLMU
{ 
  void djSchTQnhY()
  { 
      bool fTWfQOJwSz = false;
      bool YggojrwUBq = false;
      bool qmSkrEjWeK = false;
      bool cwBPOWWWFB = false;
      bool JRYbFiKNKs = false;
      bool VufmYsBlnM = false;
      bool emQHWbfRaM = false;
      bool UYOzgYNpfI = false;
      bool tVLkngPOqV = false;
      bool VkisWWBQEc = false;
      bool DsmyXxggFz = false;
      bool eKFfSJaeSp = false;
      bool LQZFpjpUcJ = false;
      bool XwlCEAhNNq = false;
      bool AiIrpLeCaN = false;
      bool uVxOQlShHm = false;
      bool GLDwahYDaR = false;
      bool aNRbocIhOe = false;
      bool FmtPOCyWkR = false;
      bool hAGZjoeMQH = false;
      string IjaUBGIWGk;
      string CgUINAOunf;
      string QDiuIEjDcb;
      string bQSHGdMwZl;
      string iHdCftsQYX;
      string lOehNFAfLx;
      string VFsdIlNMCi;
      string nSVBxIZgON;
      string KTdFpMkjsB;
      string dgkbPdNzss;
      string gfOpiTsckF;
      string fSQxmCbmmw;
      string AdTBFHgskS;
      string tZnUgdFnVW;
      string SHznUKPmoN;
      string CaLwrCMNjb;
      string lArRKFeuPI;
      string wmQPdrdeft;
      string qtDWQTNqbd;
      string QrDtkSPgdP;
      if(IjaUBGIWGk == gfOpiTsckF){fTWfQOJwSz = true;}
      else if(gfOpiTsckF == IjaUBGIWGk){DsmyXxggFz = true;}
      if(CgUINAOunf == fSQxmCbmmw){YggojrwUBq = true;}
      else if(fSQxmCbmmw == CgUINAOunf){eKFfSJaeSp = true;}
      if(QDiuIEjDcb == AdTBFHgskS){qmSkrEjWeK = true;}
      else if(AdTBFHgskS == QDiuIEjDcb){LQZFpjpUcJ = true;}
      if(bQSHGdMwZl == tZnUgdFnVW){cwBPOWWWFB = true;}
      else if(tZnUgdFnVW == bQSHGdMwZl){XwlCEAhNNq = true;}
      if(iHdCftsQYX == SHznUKPmoN){JRYbFiKNKs = true;}
      else if(SHznUKPmoN == iHdCftsQYX){AiIrpLeCaN = true;}
      if(lOehNFAfLx == CaLwrCMNjb){VufmYsBlnM = true;}
      else if(CaLwrCMNjb == lOehNFAfLx){uVxOQlShHm = true;}
      if(VFsdIlNMCi == lArRKFeuPI){emQHWbfRaM = true;}
      else if(lArRKFeuPI == VFsdIlNMCi){GLDwahYDaR = true;}
      if(nSVBxIZgON == wmQPdrdeft){UYOzgYNpfI = true;}
      if(KTdFpMkjsB == qtDWQTNqbd){tVLkngPOqV = true;}
      if(dgkbPdNzss == QrDtkSPgdP){VkisWWBQEc = true;}
      while(wmQPdrdeft == nSVBxIZgON){aNRbocIhOe = true;}
      while(qtDWQTNqbd == qtDWQTNqbd){FmtPOCyWkR = true;}
      while(QrDtkSPgdP == QrDtkSPgdP){hAGZjoeMQH = true;}
      if(fTWfQOJwSz == true){fTWfQOJwSz = false;}
      if(YggojrwUBq == true){YggojrwUBq = false;}
      if(qmSkrEjWeK == true){qmSkrEjWeK = false;}
      if(cwBPOWWWFB == true){cwBPOWWWFB = false;}
      if(JRYbFiKNKs == true){JRYbFiKNKs = false;}
      if(VufmYsBlnM == true){VufmYsBlnM = false;}
      if(emQHWbfRaM == true){emQHWbfRaM = false;}
      if(UYOzgYNpfI == true){UYOzgYNpfI = false;}
      if(tVLkngPOqV == true){tVLkngPOqV = false;}
      if(VkisWWBQEc == true){VkisWWBQEc = false;}
      if(DsmyXxggFz == true){DsmyXxggFz = false;}
      if(eKFfSJaeSp == true){eKFfSJaeSp = false;}
      if(LQZFpjpUcJ == true){LQZFpjpUcJ = false;}
      if(XwlCEAhNNq == true){XwlCEAhNNq = false;}
      if(AiIrpLeCaN == true){AiIrpLeCaN = false;}
      if(uVxOQlShHm == true){uVxOQlShHm = false;}
      if(GLDwahYDaR == true){GLDwahYDaR = false;}
      if(aNRbocIhOe == true){aNRbocIhOe = false;}
      if(FmtPOCyWkR == true){FmtPOCyWkR = false;}
      if(hAGZjoeMQH == true){hAGZjoeMQH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQZKSZVVIL
{ 
  void SlgkoMBkap()
  { 
      bool meWZdYokeF = false;
      bool YoTYHtAzYo = false;
      bool ESzWosHYNg = false;
      bool EBCQyuiWcI = false;
      bool puKbLFVfgJ = false;
      bool lyxVUTezkj = false;
      bool QPXyAXlDZL = false;
      bool LcVQyJIWLi = false;
      bool WbqEtGDgud = false;
      bool PilsqZWMbm = false;
      bool TSFVxJbgWL = false;
      bool LImBNnYTDt = false;
      bool TFHuubpcYY = false;
      bool lwuYPDVVGk = false;
      bool dWJiSHwkeC = false;
      bool BDIgSNKJZV = false;
      bool SzHyYPMOkJ = false;
      bool SCNSQwuYcn = false;
      bool fFxWWimNFB = false;
      bool rMwjSdPLKC = false;
      string SbfyxIULmm;
      string FKmsNjuTKj;
      string jolDcVKhjd;
      string tUIJJjMoTt;
      string BOguzyaxXr;
      string oFpHYcobUb;
      string xmaJsjBdjd;
      string XFzQhVHqEe;
      string tNJqnodBjg;
      string tjUrwOmXCO;
      string xwMtUjFZYD;
      string UxXphjcjUD;
      string GztCimjHTS;
      string hinphxAPWD;
      string jDbfLwMeKM;
      string lCCyHxCKKh;
      string zxGFUkJhHj;
      string iMNRTCXNpl;
      string ZFxGgfgphk;
      string tpEnDlxVKZ;
      if(SbfyxIULmm == xwMtUjFZYD){meWZdYokeF = true;}
      else if(xwMtUjFZYD == SbfyxIULmm){TSFVxJbgWL = true;}
      if(FKmsNjuTKj == UxXphjcjUD){YoTYHtAzYo = true;}
      else if(UxXphjcjUD == FKmsNjuTKj){LImBNnYTDt = true;}
      if(jolDcVKhjd == GztCimjHTS){ESzWosHYNg = true;}
      else if(GztCimjHTS == jolDcVKhjd){TFHuubpcYY = true;}
      if(tUIJJjMoTt == hinphxAPWD){EBCQyuiWcI = true;}
      else if(hinphxAPWD == tUIJJjMoTt){lwuYPDVVGk = true;}
      if(BOguzyaxXr == jDbfLwMeKM){puKbLFVfgJ = true;}
      else if(jDbfLwMeKM == BOguzyaxXr){dWJiSHwkeC = true;}
      if(oFpHYcobUb == lCCyHxCKKh){lyxVUTezkj = true;}
      else if(lCCyHxCKKh == oFpHYcobUb){BDIgSNKJZV = true;}
      if(xmaJsjBdjd == zxGFUkJhHj){QPXyAXlDZL = true;}
      else if(zxGFUkJhHj == xmaJsjBdjd){SzHyYPMOkJ = true;}
      if(XFzQhVHqEe == iMNRTCXNpl){LcVQyJIWLi = true;}
      if(tNJqnodBjg == ZFxGgfgphk){WbqEtGDgud = true;}
      if(tjUrwOmXCO == tpEnDlxVKZ){PilsqZWMbm = true;}
      while(iMNRTCXNpl == XFzQhVHqEe){SCNSQwuYcn = true;}
      while(ZFxGgfgphk == ZFxGgfgphk){fFxWWimNFB = true;}
      while(tpEnDlxVKZ == tpEnDlxVKZ){rMwjSdPLKC = true;}
      if(meWZdYokeF == true){meWZdYokeF = false;}
      if(YoTYHtAzYo == true){YoTYHtAzYo = false;}
      if(ESzWosHYNg == true){ESzWosHYNg = false;}
      if(EBCQyuiWcI == true){EBCQyuiWcI = false;}
      if(puKbLFVfgJ == true){puKbLFVfgJ = false;}
      if(lyxVUTezkj == true){lyxVUTezkj = false;}
      if(QPXyAXlDZL == true){QPXyAXlDZL = false;}
      if(LcVQyJIWLi == true){LcVQyJIWLi = false;}
      if(WbqEtGDgud == true){WbqEtGDgud = false;}
      if(PilsqZWMbm == true){PilsqZWMbm = false;}
      if(TSFVxJbgWL == true){TSFVxJbgWL = false;}
      if(LImBNnYTDt == true){LImBNnYTDt = false;}
      if(TFHuubpcYY == true){TFHuubpcYY = false;}
      if(lwuYPDVVGk == true){lwuYPDVVGk = false;}
      if(dWJiSHwkeC == true){dWJiSHwkeC = false;}
      if(BDIgSNKJZV == true){BDIgSNKJZV = false;}
      if(SzHyYPMOkJ == true){SzHyYPMOkJ = false;}
      if(SCNSQwuYcn == true){SCNSQwuYcn = false;}
      if(fFxWWimNFB == true){fFxWWimNFB = false;}
      if(rMwjSdPLKC == true){rMwjSdPLKC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DOKVUIOGXC
{ 
  void ZwGyrPmFfj()
  { 
      bool YVKVjMByYf = false;
      bool SsxfeuYYYA = false;
      bool hTqEmufAmD = false;
      bool TOUNEgSZJY = false;
      bool tZCfjiScFa = false;
      bool VfCbRFdGin = false;
      bool fBLVMEXiby = false;
      bool czPzFIRLUD = false;
      bool cCtLgnMswz = false;
      bool CMpVsrOfTe = false;
      bool LjAHyWQCVJ = false;
      bool mSlfLcGzoX = false;
      bool qelcuQIsGN = false;
      bool tkqoqsCmNJ = false;
      bool WJXlLiZKJP = false;
      bool kOqungxXLh = false;
      bool OWwIPCawnR = false;
      bool aTleBhGAQM = false;
      bool pyiqbetwBK = false;
      bool webfuAMPWJ = false;
      string WtzscKlzoJ;
      string mjfFPSXkzr;
      string wjKFiONARQ;
      string ZIbHjAqshd;
      string uXmWhpjDXm;
      string zGctDmisKN;
      string wkhXidIYUP;
      string aeCVwYxmWs;
      string eKbdRTfhDx;
      string QxiUgJoOmE;
      string hLiILUDHxe;
      string ouWRilIDGP;
      string yZUWyduhnm;
      string ihASKSaTSw;
      string QYkXHUaRlt;
      string BlIXFHpLKh;
      string ZUSJwHuEGP;
      string KojJyZoxOd;
      string DdwskwYbMC;
      string cPJjWuFabA;
      if(WtzscKlzoJ == hLiILUDHxe){YVKVjMByYf = true;}
      else if(hLiILUDHxe == WtzscKlzoJ){LjAHyWQCVJ = true;}
      if(mjfFPSXkzr == ouWRilIDGP){SsxfeuYYYA = true;}
      else if(ouWRilIDGP == mjfFPSXkzr){mSlfLcGzoX = true;}
      if(wjKFiONARQ == yZUWyduhnm){hTqEmufAmD = true;}
      else if(yZUWyduhnm == wjKFiONARQ){qelcuQIsGN = true;}
      if(ZIbHjAqshd == ihASKSaTSw){TOUNEgSZJY = true;}
      else if(ihASKSaTSw == ZIbHjAqshd){tkqoqsCmNJ = true;}
      if(uXmWhpjDXm == QYkXHUaRlt){tZCfjiScFa = true;}
      else if(QYkXHUaRlt == uXmWhpjDXm){WJXlLiZKJP = true;}
      if(zGctDmisKN == BlIXFHpLKh){VfCbRFdGin = true;}
      else if(BlIXFHpLKh == zGctDmisKN){kOqungxXLh = true;}
      if(wkhXidIYUP == ZUSJwHuEGP){fBLVMEXiby = true;}
      else if(ZUSJwHuEGP == wkhXidIYUP){OWwIPCawnR = true;}
      if(aeCVwYxmWs == KojJyZoxOd){czPzFIRLUD = true;}
      if(eKbdRTfhDx == DdwskwYbMC){cCtLgnMswz = true;}
      if(QxiUgJoOmE == cPJjWuFabA){CMpVsrOfTe = true;}
      while(KojJyZoxOd == aeCVwYxmWs){aTleBhGAQM = true;}
      while(DdwskwYbMC == DdwskwYbMC){pyiqbetwBK = true;}
      while(cPJjWuFabA == cPJjWuFabA){webfuAMPWJ = true;}
      if(YVKVjMByYf == true){YVKVjMByYf = false;}
      if(SsxfeuYYYA == true){SsxfeuYYYA = false;}
      if(hTqEmufAmD == true){hTqEmufAmD = false;}
      if(TOUNEgSZJY == true){TOUNEgSZJY = false;}
      if(tZCfjiScFa == true){tZCfjiScFa = false;}
      if(VfCbRFdGin == true){VfCbRFdGin = false;}
      if(fBLVMEXiby == true){fBLVMEXiby = false;}
      if(czPzFIRLUD == true){czPzFIRLUD = false;}
      if(cCtLgnMswz == true){cCtLgnMswz = false;}
      if(CMpVsrOfTe == true){CMpVsrOfTe = false;}
      if(LjAHyWQCVJ == true){LjAHyWQCVJ = false;}
      if(mSlfLcGzoX == true){mSlfLcGzoX = false;}
      if(qelcuQIsGN == true){qelcuQIsGN = false;}
      if(tkqoqsCmNJ == true){tkqoqsCmNJ = false;}
      if(WJXlLiZKJP == true){WJXlLiZKJP = false;}
      if(kOqungxXLh == true){kOqungxXLh = false;}
      if(OWwIPCawnR == true){OWwIPCawnR = false;}
      if(aTleBhGAQM == true){aTleBhGAQM = false;}
      if(pyiqbetwBK == true){pyiqbetwBK = false;}
      if(webfuAMPWJ == true){webfuAMPWJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYJOAVYWAU
{ 
  void dowXkCMkIR()
  { 
      bool kHFXdgqYgn = false;
      bool GbfxORDtjg = false;
      bool PEIsWsPkfh = false;
      bool edTJJqdEcN = false;
      bool xgWVNOlYej = false;
      bool iMmmyfzMBj = false;
      bool RFryJbIVmX = false;
      bool nzQWjigleH = false;
      bool HqGwzSpfKd = false;
      bool qQDrwqnYMl = false;
      bool GPkGuiuQCP = false;
      bool yNgscazwyq = false;
      bool kcKJfWuYar = false;
      bool uIZsBqFzBP = false;
      bool WZcuedjJOU = false;
      bool qraVAcEaZX = false;
      bool nVpJUpmmrl = false;
      bool UzthTLzPeC = false;
      bool mkJFBDhEsX = false;
      bool ldYdbBiSan = false;
      string kCVuaaUWLj;
      string KiZlPiBFuz;
      string MsqQMBQYmT;
      string gOcXKTgqhf;
      string QsktNUxkcp;
      string NSLdAqLEhZ;
      string KwjrDuFCaw;
      string CKWPiTHxCr;
      string DeuwGOCzXT;
      string HbIIUTJsqS;
      string PuKgnDuuug;
      string jOCpVfAmkn;
      string rGeHnZBOuO;
      string KNGjcHUOID;
      string SGDpjsZSln;
      string TVHCZIQDrO;
      string BfAfVVIRMO;
      string KlehVkCnXt;
      string zicGunGDJT;
      string qRVsBmGXUN;
      if(kCVuaaUWLj == PuKgnDuuug){kHFXdgqYgn = true;}
      else if(PuKgnDuuug == kCVuaaUWLj){GPkGuiuQCP = true;}
      if(KiZlPiBFuz == jOCpVfAmkn){GbfxORDtjg = true;}
      else if(jOCpVfAmkn == KiZlPiBFuz){yNgscazwyq = true;}
      if(MsqQMBQYmT == rGeHnZBOuO){PEIsWsPkfh = true;}
      else if(rGeHnZBOuO == MsqQMBQYmT){kcKJfWuYar = true;}
      if(gOcXKTgqhf == KNGjcHUOID){edTJJqdEcN = true;}
      else if(KNGjcHUOID == gOcXKTgqhf){uIZsBqFzBP = true;}
      if(QsktNUxkcp == SGDpjsZSln){xgWVNOlYej = true;}
      else if(SGDpjsZSln == QsktNUxkcp){WZcuedjJOU = true;}
      if(NSLdAqLEhZ == TVHCZIQDrO){iMmmyfzMBj = true;}
      else if(TVHCZIQDrO == NSLdAqLEhZ){qraVAcEaZX = true;}
      if(KwjrDuFCaw == BfAfVVIRMO){RFryJbIVmX = true;}
      else if(BfAfVVIRMO == KwjrDuFCaw){nVpJUpmmrl = true;}
      if(CKWPiTHxCr == KlehVkCnXt){nzQWjigleH = true;}
      if(DeuwGOCzXT == zicGunGDJT){HqGwzSpfKd = true;}
      if(HbIIUTJsqS == qRVsBmGXUN){qQDrwqnYMl = true;}
      while(KlehVkCnXt == CKWPiTHxCr){UzthTLzPeC = true;}
      while(zicGunGDJT == zicGunGDJT){mkJFBDhEsX = true;}
      while(qRVsBmGXUN == qRVsBmGXUN){ldYdbBiSan = true;}
      if(kHFXdgqYgn == true){kHFXdgqYgn = false;}
      if(GbfxORDtjg == true){GbfxORDtjg = false;}
      if(PEIsWsPkfh == true){PEIsWsPkfh = false;}
      if(edTJJqdEcN == true){edTJJqdEcN = false;}
      if(xgWVNOlYej == true){xgWVNOlYej = false;}
      if(iMmmyfzMBj == true){iMmmyfzMBj = false;}
      if(RFryJbIVmX == true){RFryJbIVmX = false;}
      if(nzQWjigleH == true){nzQWjigleH = false;}
      if(HqGwzSpfKd == true){HqGwzSpfKd = false;}
      if(qQDrwqnYMl == true){qQDrwqnYMl = false;}
      if(GPkGuiuQCP == true){GPkGuiuQCP = false;}
      if(yNgscazwyq == true){yNgscazwyq = false;}
      if(kcKJfWuYar == true){kcKJfWuYar = false;}
      if(uIZsBqFzBP == true){uIZsBqFzBP = false;}
      if(WZcuedjJOU == true){WZcuedjJOU = false;}
      if(qraVAcEaZX == true){qraVAcEaZX = false;}
      if(nVpJUpmmrl == true){nVpJUpmmrl = false;}
      if(UzthTLzPeC == true){UzthTLzPeC = false;}
      if(mkJFBDhEsX == true){mkJFBDhEsX = false;}
      if(ldYdbBiSan == true){ldYdbBiSan = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YIGZFCDIOM
{ 
  void hFlbcoQZqS()
  { 
      bool chdzkWiHws = false;
      bool aDIjyTyFOt = false;
      bool wYpEEULbHZ = false;
      bool qgxOYctGGp = false;
      bool qQATQTQjDb = false;
      bool wBtdZDrYuP = false;
      bool LHzWCtFtKU = false;
      bool ZryYCeYVnj = false;
      bool EaXfcomTnV = false;
      bool jUKpejRdRW = false;
      bool NWZhCDDUau = false;
      bool eVkKLjjTsM = false;
      bool HlFojEgItR = false;
      bool NtERWgBocZ = false;
      bool lRrspOjAet = false;
      bool AykEPbRkyy = false;
      bool VtaIgjQSne = false;
      bool itpSaosLyV = false;
      bool UgdAROJzCt = false;
      bool OQqeDqqiLG = false;
      string WhdyjxqShR;
      string qfIUDrMnWY;
      string tZwVuepNMF;
      string JObutUBhFC;
      string SGiuWwxyUw;
      string XVoxuwkHDE;
      string GdFcIbEMai;
      string peiTFnqBzz;
      string gqrQhmYdzx;
      string iseAuoBGmt;
      string qkXlFrmUrH;
      string FjIEXPlntU;
      string CaMcAwzhXP;
      string mjOEHuTGKo;
      string AEkrqykabf;
      string CMLRqQXtkI;
      string sExbUUVDwb;
      string ufcEUyoUkB;
      string KYFqMaYwMq;
      string XZUBwuHIXW;
      if(WhdyjxqShR == qkXlFrmUrH){chdzkWiHws = true;}
      else if(qkXlFrmUrH == WhdyjxqShR){NWZhCDDUau = true;}
      if(qfIUDrMnWY == FjIEXPlntU){aDIjyTyFOt = true;}
      else if(FjIEXPlntU == qfIUDrMnWY){eVkKLjjTsM = true;}
      if(tZwVuepNMF == CaMcAwzhXP){wYpEEULbHZ = true;}
      else if(CaMcAwzhXP == tZwVuepNMF){HlFojEgItR = true;}
      if(JObutUBhFC == mjOEHuTGKo){qgxOYctGGp = true;}
      else if(mjOEHuTGKo == JObutUBhFC){NtERWgBocZ = true;}
      if(SGiuWwxyUw == AEkrqykabf){qQATQTQjDb = true;}
      else if(AEkrqykabf == SGiuWwxyUw){lRrspOjAet = true;}
      if(XVoxuwkHDE == CMLRqQXtkI){wBtdZDrYuP = true;}
      else if(CMLRqQXtkI == XVoxuwkHDE){AykEPbRkyy = true;}
      if(GdFcIbEMai == sExbUUVDwb){LHzWCtFtKU = true;}
      else if(sExbUUVDwb == GdFcIbEMai){VtaIgjQSne = true;}
      if(peiTFnqBzz == ufcEUyoUkB){ZryYCeYVnj = true;}
      if(gqrQhmYdzx == KYFqMaYwMq){EaXfcomTnV = true;}
      if(iseAuoBGmt == XZUBwuHIXW){jUKpejRdRW = true;}
      while(ufcEUyoUkB == peiTFnqBzz){itpSaosLyV = true;}
      while(KYFqMaYwMq == KYFqMaYwMq){UgdAROJzCt = true;}
      while(XZUBwuHIXW == XZUBwuHIXW){OQqeDqqiLG = true;}
      if(chdzkWiHws == true){chdzkWiHws = false;}
      if(aDIjyTyFOt == true){aDIjyTyFOt = false;}
      if(wYpEEULbHZ == true){wYpEEULbHZ = false;}
      if(qgxOYctGGp == true){qgxOYctGGp = false;}
      if(qQATQTQjDb == true){qQATQTQjDb = false;}
      if(wBtdZDrYuP == true){wBtdZDrYuP = false;}
      if(LHzWCtFtKU == true){LHzWCtFtKU = false;}
      if(ZryYCeYVnj == true){ZryYCeYVnj = false;}
      if(EaXfcomTnV == true){EaXfcomTnV = false;}
      if(jUKpejRdRW == true){jUKpejRdRW = false;}
      if(NWZhCDDUau == true){NWZhCDDUau = false;}
      if(eVkKLjjTsM == true){eVkKLjjTsM = false;}
      if(HlFojEgItR == true){HlFojEgItR = false;}
      if(NtERWgBocZ == true){NtERWgBocZ = false;}
      if(lRrspOjAet == true){lRrspOjAet = false;}
      if(AykEPbRkyy == true){AykEPbRkyy = false;}
      if(VtaIgjQSne == true){VtaIgjQSne = false;}
      if(itpSaosLyV == true){itpSaosLyV = false;}
      if(UgdAROJzCt == true){UgdAROJzCt = false;}
      if(OQqeDqqiLG == true){OQqeDqqiLG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWDGGRRUZH
{ 
  void OKlpGFuraW()
  { 
      bool YGsSDzGDaU = false;
      bool zqQTUtoCLw = false;
      bool xysNALBuYX = false;
      bool KgXCJjhcxX = false;
      bool QsUpbJbHra = false;
      bool nyjJVZNeSq = false;
      bool yLeCKSTOJj = false;
      bool LMEmfDcDkq = false;
      bool itCxiLwNfj = false;
      bool VCJGZFOSeJ = false;
      bool pNxHObswdR = false;
      bool wKsbHEIgSz = false;
      bool WFhZOICyNZ = false;
      bool nKXbAVwuiH = false;
      bool SzjNmKJhyV = false;
      bool xhzfljeXsF = false;
      bool YuiDclmQal = false;
      bool HNyLfWVTlD = false;
      bool zTzqcGKroQ = false;
      bool qXBchXPfkB = false;
      string mlzUrtMiCH;
      string PrOJTACcix;
      string CTwPmSIaMt;
      string ahZZWdpMTf;
      string RSpbcARHtY;
      string WKQNqSoigZ;
      string lkVHggSolp;
      string JpJDeicUml;
      string AAgnWPRLiD;
      string nHessfwhtu;
      string hcUDOgANhH;
      string pUuuYkEhjR;
      string PGGiBCLPJz;
      string luZqEXfcYp;
      string OEdaNTLjUI;
      string bOxcfbWlBL;
      string VkDiUtuEpB;
      string FbIsCKbeUh;
      string qauBXXxwLb;
      string BsaMUdAuGS;
      if(mlzUrtMiCH == hcUDOgANhH){YGsSDzGDaU = true;}
      else if(hcUDOgANhH == mlzUrtMiCH){pNxHObswdR = true;}
      if(PrOJTACcix == pUuuYkEhjR){zqQTUtoCLw = true;}
      else if(pUuuYkEhjR == PrOJTACcix){wKsbHEIgSz = true;}
      if(CTwPmSIaMt == PGGiBCLPJz){xysNALBuYX = true;}
      else if(PGGiBCLPJz == CTwPmSIaMt){WFhZOICyNZ = true;}
      if(ahZZWdpMTf == luZqEXfcYp){KgXCJjhcxX = true;}
      else if(luZqEXfcYp == ahZZWdpMTf){nKXbAVwuiH = true;}
      if(RSpbcARHtY == OEdaNTLjUI){QsUpbJbHra = true;}
      else if(OEdaNTLjUI == RSpbcARHtY){SzjNmKJhyV = true;}
      if(WKQNqSoigZ == bOxcfbWlBL){nyjJVZNeSq = true;}
      else if(bOxcfbWlBL == WKQNqSoigZ){xhzfljeXsF = true;}
      if(lkVHggSolp == VkDiUtuEpB){yLeCKSTOJj = true;}
      else if(VkDiUtuEpB == lkVHggSolp){YuiDclmQal = true;}
      if(JpJDeicUml == FbIsCKbeUh){LMEmfDcDkq = true;}
      if(AAgnWPRLiD == qauBXXxwLb){itCxiLwNfj = true;}
      if(nHessfwhtu == BsaMUdAuGS){VCJGZFOSeJ = true;}
      while(FbIsCKbeUh == JpJDeicUml){HNyLfWVTlD = true;}
      while(qauBXXxwLb == qauBXXxwLb){zTzqcGKroQ = true;}
      while(BsaMUdAuGS == BsaMUdAuGS){qXBchXPfkB = true;}
      if(YGsSDzGDaU == true){YGsSDzGDaU = false;}
      if(zqQTUtoCLw == true){zqQTUtoCLw = false;}
      if(xysNALBuYX == true){xysNALBuYX = false;}
      if(KgXCJjhcxX == true){KgXCJjhcxX = false;}
      if(QsUpbJbHra == true){QsUpbJbHra = false;}
      if(nyjJVZNeSq == true){nyjJVZNeSq = false;}
      if(yLeCKSTOJj == true){yLeCKSTOJj = false;}
      if(LMEmfDcDkq == true){LMEmfDcDkq = false;}
      if(itCxiLwNfj == true){itCxiLwNfj = false;}
      if(VCJGZFOSeJ == true){VCJGZFOSeJ = false;}
      if(pNxHObswdR == true){pNxHObswdR = false;}
      if(wKsbHEIgSz == true){wKsbHEIgSz = false;}
      if(WFhZOICyNZ == true){WFhZOICyNZ = false;}
      if(nKXbAVwuiH == true){nKXbAVwuiH = false;}
      if(SzjNmKJhyV == true){SzjNmKJhyV = false;}
      if(xhzfljeXsF == true){xhzfljeXsF = false;}
      if(YuiDclmQal == true){YuiDclmQal = false;}
      if(HNyLfWVTlD == true){HNyLfWVTlD = false;}
      if(zTzqcGKroQ == true){zTzqcGKroQ = false;}
      if(qXBchXPfkB == true){qXBchXPfkB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBRVIPCGHE
{ 
  void JMOyGMVoBO()
  { 
      bool iCdyhUfMly = false;
      bool MQXLiTlybt = false;
      bool mcAthVWUqe = false;
      bool wYEMfoQfQm = false;
      bool NILqiccTOq = false;
      bool sWesMGCiPM = false;
      bool xKVGCnMLet = false;
      bool DFgogeQILF = false;
      bool rDGzkYsKzZ = false;
      bool lgPEpClFnt = false;
      bool PRoUnmppMh = false;
      bool psXKTtEWUd = false;
      bool tBLFHVpbyd = false;
      bool rLTQoaNlLx = false;
      bool hDxRisJEkw = false;
      bool xPjKAOGjMS = false;
      bool xNqhpeZGVs = false;
      bool fSKWwpEsVO = false;
      bool LkqBgbaJQa = false;
      bool TdYsATLPaE = false;
      string TpTspyiuaY;
      string BSqHBXEcxP;
      string uxYOFfnPVw;
      string AulScwwnQa;
      string BNUbGyAoGm;
      string shYdMWRFmK;
      string JSYdYGgYeE;
      string bPLWNgbxHH;
      string eyIiDRVIGF;
      string eqAGQhopCA;
      string RbKBKdVCPe;
      string uUxfeLKpaG;
      string jXSYZkOFFf;
      string rktGoDnHXY;
      string wSraKJsUaF;
      string XyOwQsIlaZ;
      string OQxjmJappb;
      string XDSBKRfrNP;
      string qtezHsVxpw;
      string tBfxKeVHmA;
      if(TpTspyiuaY == RbKBKdVCPe){iCdyhUfMly = true;}
      else if(RbKBKdVCPe == TpTspyiuaY){PRoUnmppMh = true;}
      if(BSqHBXEcxP == uUxfeLKpaG){MQXLiTlybt = true;}
      else if(uUxfeLKpaG == BSqHBXEcxP){psXKTtEWUd = true;}
      if(uxYOFfnPVw == jXSYZkOFFf){mcAthVWUqe = true;}
      else if(jXSYZkOFFf == uxYOFfnPVw){tBLFHVpbyd = true;}
      if(AulScwwnQa == rktGoDnHXY){wYEMfoQfQm = true;}
      else if(rktGoDnHXY == AulScwwnQa){rLTQoaNlLx = true;}
      if(BNUbGyAoGm == wSraKJsUaF){NILqiccTOq = true;}
      else if(wSraKJsUaF == BNUbGyAoGm){hDxRisJEkw = true;}
      if(shYdMWRFmK == XyOwQsIlaZ){sWesMGCiPM = true;}
      else if(XyOwQsIlaZ == shYdMWRFmK){xPjKAOGjMS = true;}
      if(JSYdYGgYeE == OQxjmJappb){xKVGCnMLet = true;}
      else if(OQxjmJappb == JSYdYGgYeE){xNqhpeZGVs = true;}
      if(bPLWNgbxHH == XDSBKRfrNP){DFgogeQILF = true;}
      if(eyIiDRVIGF == qtezHsVxpw){rDGzkYsKzZ = true;}
      if(eqAGQhopCA == tBfxKeVHmA){lgPEpClFnt = true;}
      while(XDSBKRfrNP == bPLWNgbxHH){fSKWwpEsVO = true;}
      while(qtezHsVxpw == qtezHsVxpw){LkqBgbaJQa = true;}
      while(tBfxKeVHmA == tBfxKeVHmA){TdYsATLPaE = true;}
      if(iCdyhUfMly == true){iCdyhUfMly = false;}
      if(MQXLiTlybt == true){MQXLiTlybt = false;}
      if(mcAthVWUqe == true){mcAthVWUqe = false;}
      if(wYEMfoQfQm == true){wYEMfoQfQm = false;}
      if(NILqiccTOq == true){NILqiccTOq = false;}
      if(sWesMGCiPM == true){sWesMGCiPM = false;}
      if(xKVGCnMLet == true){xKVGCnMLet = false;}
      if(DFgogeQILF == true){DFgogeQILF = false;}
      if(rDGzkYsKzZ == true){rDGzkYsKzZ = false;}
      if(lgPEpClFnt == true){lgPEpClFnt = false;}
      if(PRoUnmppMh == true){PRoUnmppMh = false;}
      if(psXKTtEWUd == true){psXKTtEWUd = false;}
      if(tBLFHVpbyd == true){tBLFHVpbyd = false;}
      if(rLTQoaNlLx == true){rLTQoaNlLx = false;}
      if(hDxRisJEkw == true){hDxRisJEkw = false;}
      if(xPjKAOGjMS == true){xPjKAOGjMS = false;}
      if(xNqhpeZGVs == true){xNqhpeZGVs = false;}
      if(fSKWwpEsVO == true){fSKWwpEsVO = false;}
      if(LkqBgbaJQa == true){LkqBgbaJQa = false;}
      if(TdYsATLPaE == true){TdYsATLPaE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILXTGRBZBM
{ 
  void dyjYfyHuNw()
  { 
      bool LWwzCHtohV = false;
      bool elTmGagaEz = false;
      bool fzCRqOmjhq = false;
      bool xysdqUaiMA = false;
      bool DbOsmuLKun = false;
      bool dGDpJLTdIm = false;
      bool TKGpXgsowl = false;
      bool zyNDuEjIeu = false;
      bool DcotNptCUe = false;
      bool AxaZgsVYVF = false;
      bool CWOInesAtE = false;
      bool aLzMjqVMch = false;
      bool mpTQlCXmWC = false;
      bool iLmYsfNfFh = false;
      bool xtIPDnxOpo = false;
      bool XIunSLCxWk = false;
      bool HFcrVPXaSD = false;
      bool coGujshENx = false;
      bool FIxgdZQzFg = false;
      bool cPJTZrQPsn = false;
      string mSHBteraVM;
      string igbmLayiLt;
      string ehpEtXChKq;
      string iDTprOYZYm;
      string ahdsjbdowf;
      string ZiahZEbCGW;
      string bJPddfNltx;
      string CXKXSxDxUS;
      string tNldRAbkPn;
      string mWTCLQRzOE;
      string OqtzdCXDOc;
      string BehncNXlMd;
      string DcVGJfDIMB;
      string eDhPDCSlAO;
      string bYVmmHnfZx;
      string sfmkAlUmoy;
      string yPpNyxwRjZ;
      string uklyCeGhTC;
      string qXiPIyQxOR;
      string hfxBPLhIoo;
      if(mSHBteraVM == OqtzdCXDOc){LWwzCHtohV = true;}
      else if(OqtzdCXDOc == mSHBteraVM){CWOInesAtE = true;}
      if(igbmLayiLt == BehncNXlMd){elTmGagaEz = true;}
      else if(BehncNXlMd == igbmLayiLt){aLzMjqVMch = true;}
      if(ehpEtXChKq == DcVGJfDIMB){fzCRqOmjhq = true;}
      else if(DcVGJfDIMB == ehpEtXChKq){mpTQlCXmWC = true;}
      if(iDTprOYZYm == eDhPDCSlAO){xysdqUaiMA = true;}
      else if(eDhPDCSlAO == iDTprOYZYm){iLmYsfNfFh = true;}
      if(ahdsjbdowf == bYVmmHnfZx){DbOsmuLKun = true;}
      else if(bYVmmHnfZx == ahdsjbdowf){xtIPDnxOpo = true;}
      if(ZiahZEbCGW == sfmkAlUmoy){dGDpJLTdIm = true;}
      else if(sfmkAlUmoy == ZiahZEbCGW){XIunSLCxWk = true;}
      if(bJPddfNltx == yPpNyxwRjZ){TKGpXgsowl = true;}
      else if(yPpNyxwRjZ == bJPddfNltx){HFcrVPXaSD = true;}
      if(CXKXSxDxUS == uklyCeGhTC){zyNDuEjIeu = true;}
      if(tNldRAbkPn == qXiPIyQxOR){DcotNptCUe = true;}
      if(mWTCLQRzOE == hfxBPLhIoo){AxaZgsVYVF = true;}
      while(uklyCeGhTC == CXKXSxDxUS){coGujshENx = true;}
      while(qXiPIyQxOR == qXiPIyQxOR){FIxgdZQzFg = true;}
      while(hfxBPLhIoo == hfxBPLhIoo){cPJTZrQPsn = true;}
      if(LWwzCHtohV == true){LWwzCHtohV = false;}
      if(elTmGagaEz == true){elTmGagaEz = false;}
      if(fzCRqOmjhq == true){fzCRqOmjhq = false;}
      if(xysdqUaiMA == true){xysdqUaiMA = false;}
      if(DbOsmuLKun == true){DbOsmuLKun = false;}
      if(dGDpJLTdIm == true){dGDpJLTdIm = false;}
      if(TKGpXgsowl == true){TKGpXgsowl = false;}
      if(zyNDuEjIeu == true){zyNDuEjIeu = false;}
      if(DcotNptCUe == true){DcotNptCUe = false;}
      if(AxaZgsVYVF == true){AxaZgsVYVF = false;}
      if(CWOInesAtE == true){CWOInesAtE = false;}
      if(aLzMjqVMch == true){aLzMjqVMch = false;}
      if(mpTQlCXmWC == true){mpTQlCXmWC = false;}
      if(iLmYsfNfFh == true){iLmYsfNfFh = false;}
      if(xtIPDnxOpo == true){xtIPDnxOpo = false;}
      if(XIunSLCxWk == true){XIunSLCxWk = false;}
      if(HFcrVPXaSD == true){HFcrVPXaSD = false;}
      if(coGujshENx == true){coGujshENx = false;}
      if(FIxgdZQzFg == true){FIxgdZQzFg = false;}
      if(cPJTZrQPsn == true){cPJTZrQPsn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOEZZCWUIY
{ 
  void YJBqRDexJQ()
  { 
      bool cCcSLIFogO = false;
      bool ElYTFhfeJa = false;
      bool UoSFhIHZey = false;
      bool juUrJkeejj = false;
      bool YFLDcHhdSt = false;
      bool dzqMrmiWkD = false;
      bool BfJidJQgKU = false;
      bool CAtYCOdOca = false;
      bool ZcHkTjEIzV = false;
      bool BItfirwcYT = false;
      bool qBSxrdERJc = false;
      bool JUtKcXYYOt = false;
      bool EIgoTtFOpK = false;
      bool RAoIiXKJsp = false;
      bool flyVMgNjDL = false;
      bool TXOeOhTddx = false;
      bool YpbzKJekaE = false;
      bool NOeYNSJKcl = false;
      bool fUKdptlKsB = false;
      bool EfeuQpJzLD = false;
      string PPSARdQEQC;
      string QQHbBfGQcd;
      string YrXztQdtCJ;
      string qyEXIWlsLc;
      string wVdALLffjP;
      string bcxrpWqSFA;
      string zVCHLSLjTd;
      string tMEAhCOXmi;
      string jxKlgNBMgk;
      string eSmKcZTWns;
      string zwMFUOYxJn;
      string ISeWPBLPZy;
      string RzChyaYsWH;
      string hrjtinkFRR;
      string oDCscMnQub;
      string ODwpbAtdGs;
      string peZCFPiknb;
      string PFyHINwIEl;
      string mIyusdusRh;
      string sHyXbKdAnM;
      if(PPSARdQEQC == zwMFUOYxJn){cCcSLIFogO = true;}
      else if(zwMFUOYxJn == PPSARdQEQC){qBSxrdERJc = true;}
      if(QQHbBfGQcd == ISeWPBLPZy){ElYTFhfeJa = true;}
      else if(ISeWPBLPZy == QQHbBfGQcd){JUtKcXYYOt = true;}
      if(YrXztQdtCJ == RzChyaYsWH){UoSFhIHZey = true;}
      else if(RzChyaYsWH == YrXztQdtCJ){EIgoTtFOpK = true;}
      if(qyEXIWlsLc == hrjtinkFRR){juUrJkeejj = true;}
      else if(hrjtinkFRR == qyEXIWlsLc){RAoIiXKJsp = true;}
      if(wVdALLffjP == oDCscMnQub){YFLDcHhdSt = true;}
      else if(oDCscMnQub == wVdALLffjP){flyVMgNjDL = true;}
      if(bcxrpWqSFA == ODwpbAtdGs){dzqMrmiWkD = true;}
      else if(ODwpbAtdGs == bcxrpWqSFA){TXOeOhTddx = true;}
      if(zVCHLSLjTd == peZCFPiknb){BfJidJQgKU = true;}
      else if(peZCFPiknb == zVCHLSLjTd){YpbzKJekaE = true;}
      if(tMEAhCOXmi == PFyHINwIEl){CAtYCOdOca = true;}
      if(jxKlgNBMgk == mIyusdusRh){ZcHkTjEIzV = true;}
      if(eSmKcZTWns == sHyXbKdAnM){BItfirwcYT = true;}
      while(PFyHINwIEl == tMEAhCOXmi){NOeYNSJKcl = true;}
      while(mIyusdusRh == mIyusdusRh){fUKdptlKsB = true;}
      while(sHyXbKdAnM == sHyXbKdAnM){EfeuQpJzLD = true;}
      if(cCcSLIFogO == true){cCcSLIFogO = false;}
      if(ElYTFhfeJa == true){ElYTFhfeJa = false;}
      if(UoSFhIHZey == true){UoSFhIHZey = false;}
      if(juUrJkeejj == true){juUrJkeejj = false;}
      if(YFLDcHhdSt == true){YFLDcHhdSt = false;}
      if(dzqMrmiWkD == true){dzqMrmiWkD = false;}
      if(BfJidJQgKU == true){BfJidJQgKU = false;}
      if(CAtYCOdOca == true){CAtYCOdOca = false;}
      if(ZcHkTjEIzV == true){ZcHkTjEIzV = false;}
      if(BItfirwcYT == true){BItfirwcYT = false;}
      if(qBSxrdERJc == true){qBSxrdERJc = false;}
      if(JUtKcXYYOt == true){JUtKcXYYOt = false;}
      if(EIgoTtFOpK == true){EIgoTtFOpK = false;}
      if(RAoIiXKJsp == true){RAoIiXKJsp = false;}
      if(flyVMgNjDL == true){flyVMgNjDL = false;}
      if(TXOeOhTddx == true){TXOeOhTddx = false;}
      if(YpbzKJekaE == true){YpbzKJekaE = false;}
      if(NOeYNSJKcl == true){NOeYNSJKcl = false;}
      if(fUKdptlKsB == true){fUKdptlKsB = false;}
      if(EfeuQpJzLD == true){EfeuQpJzLD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTTCWITDFH
{ 
  void iwdmNBGODg()
  { 
      bool pRrrKIqHBn = false;
      bool CMYNIHdJiH = false;
      bool uMKZXuAYdI = false;
      bool dbGsmQVrNH = false;
      bool FGiTVshdzb = false;
      bool cCiprdHRTP = false;
      bool IScrKaGeaq = false;
      bool lkubBocqEe = false;
      bool NVYCfarQBJ = false;
      bool JDYxymcpJt = false;
      bool mDDHoqGHnC = false;
      bool AQNoBlsaMi = false;
      bool hpcQgiMycO = false;
      bool LmgJrKSQMo = false;
      bool TkbyJspiuM = false;
      bool sCdZLwZlaG = false;
      bool eIeZqMiDwq = false;
      bool TcOXPxNdHn = false;
      bool scCQVJJHyu = false;
      bool jfpFKKFCHw = false;
      string euMcRFUPRd;
      string pdTYwxWIuk;
      string PNoJdPxCaS;
      string ysmeGrpIai;
      string sqniKAPBLR;
      string nEeGzRFCyC;
      string IRnyfxqnSD;
      string GOgLrXYFyd;
      string zuqJesNfeo;
      string mnKYZbCoDN;
      string IaiHKZXTOa;
      string rzDTCNaeTl;
      string jLJdQSDHkP;
      string UiCkVXLizF;
      string VtQEwmjpWM;
      string AXVRdxRFqq;
      string VPhyFIxRyd;
      string BrfNPotFgc;
      string iNkYPxNkHX;
      string FGrHjGLSym;
      if(euMcRFUPRd == IaiHKZXTOa){pRrrKIqHBn = true;}
      else if(IaiHKZXTOa == euMcRFUPRd){mDDHoqGHnC = true;}
      if(pdTYwxWIuk == rzDTCNaeTl){CMYNIHdJiH = true;}
      else if(rzDTCNaeTl == pdTYwxWIuk){AQNoBlsaMi = true;}
      if(PNoJdPxCaS == jLJdQSDHkP){uMKZXuAYdI = true;}
      else if(jLJdQSDHkP == PNoJdPxCaS){hpcQgiMycO = true;}
      if(ysmeGrpIai == UiCkVXLizF){dbGsmQVrNH = true;}
      else if(UiCkVXLizF == ysmeGrpIai){LmgJrKSQMo = true;}
      if(sqniKAPBLR == VtQEwmjpWM){FGiTVshdzb = true;}
      else if(VtQEwmjpWM == sqniKAPBLR){TkbyJspiuM = true;}
      if(nEeGzRFCyC == AXVRdxRFqq){cCiprdHRTP = true;}
      else if(AXVRdxRFqq == nEeGzRFCyC){sCdZLwZlaG = true;}
      if(IRnyfxqnSD == VPhyFIxRyd){IScrKaGeaq = true;}
      else if(VPhyFIxRyd == IRnyfxqnSD){eIeZqMiDwq = true;}
      if(GOgLrXYFyd == BrfNPotFgc){lkubBocqEe = true;}
      if(zuqJesNfeo == iNkYPxNkHX){NVYCfarQBJ = true;}
      if(mnKYZbCoDN == FGrHjGLSym){JDYxymcpJt = true;}
      while(BrfNPotFgc == GOgLrXYFyd){TcOXPxNdHn = true;}
      while(iNkYPxNkHX == iNkYPxNkHX){scCQVJJHyu = true;}
      while(FGrHjGLSym == FGrHjGLSym){jfpFKKFCHw = true;}
      if(pRrrKIqHBn == true){pRrrKIqHBn = false;}
      if(CMYNIHdJiH == true){CMYNIHdJiH = false;}
      if(uMKZXuAYdI == true){uMKZXuAYdI = false;}
      if(dbGsmQVrNH == true){dbGsmQVrNH = false;}
      if(FGiTVshdzb == true){FGiTVshdzb = false;}
      if(cCiprdHRTP == true){cCiprdHRTP = false;}
      if(IScrKaGeaq == true){IScrKaGeaq = false;}
      if(lkubBocqEe == true){lkubBocqEe = false;}
      if(NVYCfarQBJ == true){NVYCfarQBJ = false;}
      if(JDYxymcpJt == true){JDYxymcpJt = false;}
      if(mDDHoqGHnC == true){mDDHoqGHnC = false;}
      if(AQNoBlsaMi == true){AQNoBlsaMi = false;}
      if(hpcQgiMycO == true){hpcQgiMycO = false;}
      if(LmgJrKSQMo == true){LmgJrKSQMo = false;}
      if(TkbyJspiuM == true){TkbyJspiuM = false;}
      if(sCdZLwZlaG == true){sCdZLwZlaG = false;}
      if(eIeZqMiDwq == true){eIeZqMiDwq = false;}
      if(TcOXPxNdHn == true){TcOXPxNdHn = false;}
      if(scCQVJJHyu == true){scCQVJJHyu = false;}
      if(jfpFKKFCHw == true){jfpFKKFCHw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEXBJLMBSW
{ 
  void OZFbxISqrj()
  { 
      bool WBgFgkfVAm = false;
      bool pYUQHMIiUW = false;
      bool gZsZSSkkfZ = false;
      bool WxOAHIkMiM = false;
      bool VhdnsepCeO = false;
      bool RrrIbxIGlN = false;
      bool zupaQrJTIz = false;
      bool auAHAyuEfm = false;
      bool bhFQHdEGXK = false;
      bool zdaUMarDXA = false;
      bool VWsfmWrkHd = false;
      bool BDazlQoYSl = false;
      bool mCuyzwUeuZ = false;
      bool GqgeRFoZdk = false;
      bool kTytIuDaiu = false;
      bool kSkkNSaufp = false;
      bool CNpgWJWugf = false;
      bool bOugATDBoE = false;
      bool ssuznmGuRz = false;
      bool essmiXdRXy = false;
      string JaXRUMYNbj;
      string QOmSxryUZr;
      string BSIRumVmhV;
      string LlmFCdJGDT;
      string uMuarSzyVg;
      string dngCUpRGWh;
      string pleFYeahQS;
      string iqRFxoXhZc;
      string nWRBrXEkjM;
      string MCjVdJhpCM;
      string qQhCxlVbFf;
      string RjgtsSTcMB;
      string apyDGfHubm;
      string HgeMkWoOEF;
      string BbeDtbVpbK;
      string oEcAkBSduR;
      string daARYkETIW;
      string dEYHAyKtJe;
      string JRSQxCEeai;
      string DKTmaZbNeJ;
      if(JaXRUMYNbj == qQhCxlVbFf){WBgFgkfVAm = true;}
      else if(qQhCxlVbFf == JaXRUMYNbj){VWsfmWrkHd = true;}
      if(QOmSxryUZr == RjgtsSTcMB){pYUQHMIiUW = true;}
      else if(RjgtsSTcMB == QOmSxryUZr){BDazlQoYSl = true;}
      if(BSIRumVmhV == apyDGfHubm){gZsZSSkkfZ = true;}
      else if(apyDGfHubm == BSIRumVmhV){mCuyzwUeuZ = true;}
      if(LlmFCdJGDT == HgeMkWoOEF){WxOAHIkMiM = true;}
      else if(HgeMkWoOEF == LlmFCdJGDT){GqgeRFoZdk = true;}
      if(uMuarSzyVg == BbeDtbVpbK){VhdnsepCeO = true;}
      else if(BbeDtbVpbK == uMuarSzyVg){kTytIuDaiu = true;}
      if(dngCUpRGWh == oEcAkBSduR){RrrIbxIGlN = true;}
      else if(oEcAkBSduR == dngCUpRGWh){kSkkNSaufp = true;}
      if(pleFYeahQS == daARYkETIW){zupaQrJTIz = true;}
      else if(daARYkETIW == pleFYeahQS){CNpgWJWugf = true;}
      if(iqRFxoXhZc == dEYHAyKtJe){auAHAyuEfm = true;}
      if(nWRBrXEkjM == JRSQxCEeai){bhFQHdEGXK = true;}
      if(MCjVdJhpCM == DKTmaZbNeJ){zdaUMarDXA = true;}
      while(dEYHAyKtJe == iqRFxoXhZc){bOugATDBoE = true;}
      while(JRSQxCEeai == JRSQxCEeai){ssuznmGuRz = true;}
      while(DKTmaZbNeJ == DKTmaZbNeJ){essmiXdRXy = true;}
      if(WBgFgkfVAm == true){WBgFgkfVAm = false;}
      if(pYUQHMIiUW == true){pYUQHMIiUW = false;}
      if(gZsZSSkkfZ == true){gZsZSSkkfZ = false;}
      if(WxOAHIkMiM == true){WxOAHIkMiM = false;}
      if(VhdnsepCeO == true){VhdnsepCeO = false;}
      if(RrrIbxIGlN == true){RrrIbxIGlN = false;}
      if(zupaQrJTIz == true){zupaQrJTIz = false;}
      if(auAHAyuEfm == true){auAHAyuEfm = false;}
      if(bhFQHdEGXK == true){bhFQHdEGXK = false;}
      if(zdaUMarDXA == true){zdaUMarDXA = false;}
      if(VWsfmWrkHd == true){VWsfmWrkHd = false;}
      if(BDazlQoYSl == true){BDazlQoYSl = false;}
      if(mCuyzwUeuZ == true){mCuyzwUeuZ = false;}
      if(GqgeRFoZdk == true){GqgeRFoZdk = false;}
      if(kTytIuDaiu == true){kTytIuDaiu = false;}
      if(kSkkNSaufp == true){kSkkNSaufp = false;}
      if(CNpgWJWugf == true){CNpgWJWugf = false;}
      if(bOugATDBoE == true){bOugATDBoE = false;}
      if(ssuznmGuRz == true){ssuznmGuRz = false;}
      if(essmiXdRXy == true){essmiXdRXy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FUGQYCHHTR
{ 
  void wLgUOnVdsC()
  { 
      bool PgSGWEwNhj = false;
      bool nuFsbLxRUd = false;
      bool DbyJVMbNgN = false;
      bool HnmhHGIUkW = false;
      bool xaNrefWPnE = false;
      bool PGCAEniIkJ = false;
      bool chgTczHXlU = false;
      bool DcgxfcNGdp = false;
      bool pMZcyAklcS = false;
      bool XziatPtsOf = false;
      bool XzcSBlYFTb = false;
      bool ZbduSPIDVb = false;
      bool OVtTxDsFCQ = false;
      bool hUqySqiGbL = false;
      bool afRBrwUnId = false;
      bool GpXmQBEIVx = false;
      bool sTCDtFjfbb = false;
      bool fBbJAiEsbA = false;
      bool iExYJqxEgQ = false;
      bool lZjdSHcOHl = false;
      string rQOwbTZhGV;
      string DnOqEGLNxp;
      string ykIGyVqJcr;
      string PgWxCaistC;
      string TpZdSxAdGj;
      string dXnmAGIHyF;
      string bPENFWQRod;
      string XSTtWHLdnA;
      string VNDsNqrjww;
      string RatnaDlLXu;
      string ghocMLEsPs;
      string tdTxjOMKzN;
      string efUrLwXeTS;
      string UAGrTmYafC;
      string lyUDBnHwDM;
      string qaLJQAMwQP;
      string mYZwXsXadw;
      string olexafLRpW;
      string nabHbtowbT;
      string abJQPMYXeI;
      if(rQOwbTZhGV == ghocMLEsPs){PgSGWEwNhj = true;}
      else if(ghocMLEsPs == rQOwbTZhGV){XzcSBlYFTb = true;}
      if(DnOqEGLNxp == tdTxjOMKzN){nuFsbLxRUd = true;}
      else if(tdTxjOMKzN == DnOqEGLNxp){ZbduSPIDVb = true;}
      if(ykIGyVqJcr == efUrLwXeTS){DbyJVMbNgN = true;}
      else if(efUrLwXeTS == ykIGyVqJcr){OVtTxDsFCQ = true;}
      if(PgWxCaistC == UAGrTmYafC){HnmhHGIUkW = true;}
      else if(UAGrTmYafC == PgWxCaistC){hUqySqiGbL = true;}
      if(TpZdSxAdGj == lyUDBnHwDM){xaNrefWPnE = true;}
      else if(lyUDBnHwDM == TpZdSxAdGj){afRBrwUnId = true;}
      if(dXnmAGIHyF == qaLJQAMwQP){PGCAEniIkJ = true;}
      else if(qaLJQAMwQP == dXnmAGIHyF){GpXmQBEIVx = true;}
      if(bPENFWQRod == mYZwXsXadw){chgTczHXlU = true;}
      else if(mYZwXsXadw == bPENFWQRod){sTCDtFjfbb = true;}
      if(XSTtWHLdnA == olexafLRpW){DcgxfcNGdp = true;}
      if(VNDsNqrjww == nabHbtowbT){pMZcyAklcS = true;}
      if(RatnaDlLXu == abJQPMYXeI){XziatPtsOf = true;}
      while(olexafLRpW == XSTtWHLdnA){fBbJAiEsbA = true;}
      while(nabHbtowbT == nabHbtowbT){iExYJqxEgQ = true;}
      while(abJQPMYXeI == abJQPMYXeI){lZjdSHcOHl = true;}
      if(PgSGWEwNhj == true){PgSGWEwNhj = false;}
      if(nuFsbLxRUd == true){nuFsbLxRUd = false;}
      if(DbyJVMbNgN == true){DbyJVMbNgN = false;}
      if(HnmhHGIUkW == true){HnmhHGIUkW = false;}
      if(xaNrefWPnE == true){xaNrefWPnE = false;}
      if(PGCAEniIkJ == true){PGCAEniIkJ = false;}
      if(chgTczHXlU == true){chgTczHXlU = false;}
      if(DcgxfcNGdp == true){DcgxfcNGdp = false;}
      if(pMZcyAklcS == true){pMZcyAklcS = false;}
      if(XziatPtsOf == true){XziatPtsOf = false;}
      if(XzcSBlYFTb == true){XzcSBlYFTb = false;}
      if(ZbduSPIDVb == true){ZbduSPIDVb = false;}
      if(OVtTxDsFCQ == true){OVtTxDsFCQ = false;}
      if(hUqySqiGbL == true){hUqySqiGbL = false;}
      if(afRBrwUnId == true){afRBrwUnId = false;}
      if(GpXmQBEIVx == true){GpXmQBEIVx = false;}
      if(sTCDtFjfbb == true){sTCDtFjfbb = false;}
      if(fBbJAiEsbA == true){fBbJAiEsbA = false;}
      if(iExYJqxEgQ == true){iExYJqxEgQ = false;}
      if(lZjdSHcOHl == true){lZjdSHcOHl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYJPEWUQVV
{ 
  void VjQgPZlHby()
  { 
      bool RZYOFoYwIn = false;
      bool ltSxrSKCRC = false;
      bool eggVYNJYuT = false;
      bool whXZYYlFwr = false;
      bool jrzNybsYVr = false;
      bool pLqUkksDpq = false;
      bool ezAoqEVrXT = false;
      bool gFFZRmhSWw = false;
      bool TkDDckpDnn = false;
      bool fhOFMjqKWt = false;
      bool FAACLjFRCx = false;
      bool DZgsWtwxLF = false;
      bool NRDjmypANg = false;
      bool wWwcqTkArr = false;
      bool fYAqkFBVhR = false;
      bool ntzQfmwQOM = false;
      bool tEDUBfcECD = false;
      bool JuESZnRMzh = false;
      bool xUSusCXfwD = false;
      bool WTlfyaVfoE = false;
      string shsmUNxFae;
      string bkMQFFyliJ;
      string esohdmLLGU;
      string nwaUtaDIub;
      string wEEWGmJGQB;
      string KzsPGzsKJh;
      string BkyFqfKqVe;
      string BopHNZoRap;
      string cFuFKoDKOt;
      string gryNZKFyfa;
      string cRjkzUIkBf;
      string KaiTEuosuB;
      string bzcaxIpcgC;
      string UqlANKVJFo;
      string gRIhjGJeIe;
      string ULCdycoJnq;
      string deEzLToiFt;
      string ZfmGUKqupq;
      string zLTBgInHBj;
      string VLVNKBNJWQ;
      if(shsmUNxFae == cRjkzUIkBf){RZYOFoYwIn = true;}
      else if(cRjkzUIkBf == shsmUNxFae){FAACLjFRCx = true;}
      if(bkMQFFyliJ == KaiTEuosuB){ltSxrSKCRC = true;}
      else if(KaiTEuosuB == bkMQFFyliJ){DZgsWtwxLF = true;}
      if(esohdmLLGU == bzcaxIpcgC){eggVYNJYuT = true;}
      else if(bzcaxIpcgC == esohdmLLGU){NRDjmypANg = true;}
      if(nwaUtaDIub == UqlANKVJFo){whXZYYlFwr = true;}
      else if(UqlANKVJFo == nwaUtaDIub){wWwcqTkArr = true;}
      if(wEEWGmJGQB == gRIhjGJeIe){jrzNybsYVr = true;}
      else if(gRIhjGJeIe == wEEWGmJGQB){fYAqkFBVhR = true;}
      if(KzsPGzsKJh == ULCdycoJnq){pLqUkksDpq = true;}
      else if(ULCdycoJnq == KzsPGzsKJh){ntzQfmwQOM = true;}
      if(BkyFqfKqVe == deEzLToiFt){ezAoqEVrXT = true;}
      else if(deEzLToiFt == BkyFqfKqVe){tEDUBfcECD = true;}
      if(BopHNZoRap == ZfmGUKqupq){gFFZRmhSWw = true;}
      if(cFuFKoDKOt == zLTBgInHBj){TkDDckpDnn = true;}
      if(gryNZKFyfa == VLVNKBNJWQ){fhOFMjqKWt = true;}
      while(ZfmGUKqupq == BopHNZoRap){JuESZnRMzh = true;}
      while(zLTBgInHBj == zLTBgInHBj){xUSusCXfwD = true;}
      while(VLVNKBNJWQ == VLVNKBNJWQ){WTlfyaVfoE = true;}
      if(RZYOFoYwIn == true){RZYOFoYwIn = false;}
      if(ltSxrSKCRC == true){ltSxrSKCRC = false;}
      if(eggVYNJYuT == true){eggVYNJYuT = false;}
      if(whXZYYlFwr == true){whXZYYlFwr = false;}
      if(jrzNybsYVr == true){jrzNybsYVr = false;}
      if(pLqUkksDpq == true){pLqUkksDpq = false;}
      if(ezAoqEVrXT == true){ezAoqEVrXT = false;}
      if(gFFZRmhSWw == true){gFFZRmhSWw = false;}
      if(TkDDckpDnn == true){TkDDckpDnn = false;}
      if(fhOFMjqKWt == true){fhOFMjqKWt = false;}
      if(FAACLjFRCx == true){FAACLjFRCx = false;}
      if(DZgsWtwxLF == true){DZgsWtwxLF = false;}
      if(NRDjmypANg == true){NRDjmypANg = false;}
      if(wWwcqTkArr == true){wWwcqTkArr = false;}
      if(fYAqkFBVhR == true){fYAqkFBVhR = false;}
      if(ntzQfmwQOM == true){ntzQfmwQOM = false;}
      if(tEDUBfcECD == true){tEDUBfcECD = false;}
      if(JuESZnRMzh == true){JuESZnRMzh = false;}
      if(xUSusCXfwD == true){xUSusCXfwD = false;}
      if(WTlfyaVfoE == true){WTlfyaVfoE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JACIKLKBGI
{ 
  void tEhOklyGYn()
  { 
      bool TPCbxxDLIp = false;
      bool iHkjPjaApf = false;
      bool ECrDsEYyKl = false;
      bool OyoViYamDW = false;
      bool wQNyTVhOLu = false;
      bool zkcTuRWyhs = false;
      bool XFBVbjRPBq = false;
      bool JnxSimntjX = false;
      bool VKlPmcVVZR = false;
      bool BbEJyqOqWi = false;
      bool DSMUkKnJkI = false;
      bool ccOJXNSlhy = false;
      bool OwojogimUr = false;
      bool XxXBUDxRdc = false;
      bool oLkRoYNtlk = false;
      bool XcIXTGcceE = false;
      bool aAorjeFMoT = false;
      bool PBIFJCLXtQ = false;
      bool ToBiTuoAgO = false;
      bool aTlYBnWrhJ = false;
      string JsOaVReilc;
      string aQcKRfjCpb;
      string bilpRbkCHF;
      string gatQRPjcqA;
      string IMSueSfBil;
      string JNOSZaHYJt;
      string gcbgwAWMsC;
      string wGKpTPPqKz;
      string uiSVwSMbpq;
      string HKTxSeklze;
      string uTIgoCCYyK;
      string KPNJyxJGjc;
      string ntVBtkmNWo;
      string ddrfDaZlft;
      string PmcffqxJyV;
      string UdBVqAxGmD;
      string OoBJffXhGW;
      string XXapMARpVC;
      string ndOBTAbVoC;
      string dTzbeZlSAz;
      if(JsOaVReilc == uTIgoCCYyK){TPCbxxDLIp = true;}
      else if(uTIgoCCYyK == JsOaVReilc){DSMUkKnJkI = true;}
      if(aQcKRfjCpb == KPNJyxJGjc){iHkjPjaApf = true;}
      else if(KPNJyxJGjc == aQcKRfjCpb){ccOJXNSlhy = true;}
      if(bilpRbkCHF == ntVBtkmNWo){ECrDsEYyKl = true;}
      else if(ntVBtkmNWo == bilpRbkCHF){OwojogimUr = true;}
      if(gatQRPjcqA == ddrfDaZlft){OyoViYamDW = true;}
      else if(ddrfDaZlft == gatQRPjcqA){XxXBUDxRdc = true;}
      if(IMSueSfBil == PmcffqxJyV){wQNyTVhOLu = true;}
      else if(PmcffqxJyV == IMSueSfBil){oLkRoYNtlk = true;}
      if(JNOSZaHYJt == UdBVqAxGmD){zkcTuRWyhs = true;}
      else if(UdBVqAxGmD == JNOSZaHYJt){XcIXTGcceE = true;}
      if(gcbgwAWMsC == OoBJffXhGW){XFBVbjRPBq = true;}
      else if(OoBJffXhGW == gcbgwAWMsC){aAorjeFMoT = true;}
      if(wGKpTPPqKz == XXapMARpVC){JnxSimntjX = true;}
      if(uiSVwSMbpq == ndOBTAbVoC){VKlPmcVVZR = true;}
      if(HKTxSeklze == dTzbeZlSAz){BbEJyqOqWi = true;}
      while(XXapMARpVC == wGKpTPPqKz){PBIFJCLXtQ = true;}
      while(ndOBTAbVoC == ndOBTAbVoC){ToBiTuoAgO = true;}
      while(dTzbeZlSAz == dTzbeZlSAz){aTlYBnWrhJ = true;}
      if(TPCbxxDLIp == true){TPCbxxDLIp = false;}
      if(iHkjPjaApf == true){iHkjPjaApf = false;}
      if(ECrDsEYyKl == true){ECrDsEYyKl = false;}
      if(OyoViYamDW == true){OyoViYamDW = false;}
      if(wQNyTVhOLu == true){wQNyTVhOLu = false;}
      if(zkcTuRWyhs == true){zkcTuRWyhs = false;}
      if(XFBVbjRPBq == true){XFBVbjRPBq = false;}
      if(JnxSimntjX == true){JnxSimntjX = false;}
      if(VKlPmcVVZR == true){VKlPmcVVZR = false;}
      if(BbEJyqOqWi == true){BbEJyqOqWi = false;}
      if(DSMUkKnJkI == true){DSMUkKnJkI = false;}
      if(ccOJXNSlhy == true){ccOJXNSlhy = false;}
      if(OwojogimUr == true){OwojogimUr = false;}
      if(XxXBUDxRdc == true){XxXBUDxRdc = false;}
      if(oLkRoYNtlk == true){oLkRoYNtlk = false;}
      if(XcIXTGcceE == true){XcIXTGcceE = false;}
      if(aAorjeFMoT == true){aAorjeFMoT = false;}
      if(PBIFJCLXtQ == true){PBIFJCLXtQ = false;}
      if(ToBiTuoAgO == true){ToBiTuoAgO = false;}
      if(aTlYBnWrhJ == true){aTlYBnWrhJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBDTAPGJOA
{ 
  void dpGRyKpNUq()
  { 
      bool MeFEBoxGTs = false;
      bool pUDRyqLDOs = false;
      bool WzYoiSSCMk = false;
      bool YjLahHcien = false;
      bool IDPQBGfcjb = false;
      bool uTQRaNFPVi = false;
      bool VtthUFJbiq = false;
      bool NbYZkSiInc = false;
      bool moRjoFTszU = false;
      bool BNNwSNJhwu = false;
      bool wDtsNTupgI = false;
      bool dxaswfcJrO = false;
      bool lPbOoAOcHX = false;
      bool IBLsfiuYWV = false;
      bool KcMqpDlTAl = false;
      bool jAogJgbeDM = false;
      bool ESiIAclhMM = false;
      bool kElWEICkXl = false;
      bool OtbVmIMdiz = false;
      bool HPUJQrtEqN = false;
      string TjwdYqQPfb;
      string XFrIugNRVH;
      string hhoQNzlkzR;
      string OtXMuZeeSV;
      string DEYbWZFtZp;
      string dCTbPlteQY;
      string FfPNNdheNV;
      string CiyAEcIMtn;
      string trKInLZuxI;
      string eAOtQXoLOs;
      string rZgDntETXm;
      string dhkceMUGYB;
      string DlhEqCUDjf;
      string nwyAwTLGUs;
      string HGWKewPlPD;
      string ChlNpFrbLl;
      string ZAjrygjjfK;
      string BNkfswPWYt;
      string minfcFKjKq;
      string bitiSHWeLy;
      if(TjwdYqQPfb == rZgDntETXm){MeFEBoxGTs = true;}
      else if(rZgDntETXm == TjwdYqQPfb){wDtsNTupgI = true;}
      if(XFrIugNRVH == dhkceMUGYB){pUDRyqLDOs = true;}
      else if(dhkceMUGYB == XFrIugNRVH){dxaswfcJrO = true;}
      if(hhoQNzlkzR == DlhEqCUDjf){WzYoiSSCMk = true;}
      else if(DlhEqCUDjf == hhoQNzlkzR){lPbOoAOcHX = true;}
      if(OtXMuZeeSV == nwyAwTLGUs){YjLahHcien = true;}
      else if(nwyAwTLGUs == OtXMuZeeSV){IBLsfiuYWV = true;}
      if(DEYbWZFtZp == HGWKewPlPD){IDPQBGfcjb = true;}
      else if(HGWKewPlPD == DEYbWZFtZp){KcMqpDlTAl = true;}
      if(dCTbPlteQY == ChlNpFrbLl){uTQRaNFPVi = true;}
      else if(ChlNpFrbLl == dCTbPlteQY){jAogJgbeDM = true;}
      if(FfPNNdheNV == ZAjrygjjfK){VtthUFJbiq = true;}
      else if(ZAjrygjjfK == FfPNNdheNV){ESiIAclhMM = true;}
      if(CiyAEcIMtn == BNkfswPWYt){NbYZkSiInc = true;}
      if(trKInLZuxI == minfcFKjKq){moRjoFTszU = true;}
      if(eAOtQXoLOs == bitiSHWeLy){BNNwSNJhwu = true;}
      while(BNkfswPWYt == CiyAEcIMtn){kElWEICkXl = true;}
      while(minfcFKjKq == minfcFKjKq){OtbVmIMdiz = true;}
      while(bitiSHWeLy == bitiSHWeLy){HPUJQrtEqN = true;}
      if(MeFEBoxGTs == true){MeFEBoxGTs = false;}
      if(pUDRyqLDOs == true){pUDRyqLDOs = false;}
      if(WzYoiSSCMk == true){WzYoiSSCMk = false;}
      if(YjLahHcien == true){YjLahHcien = false;}
      if(IDPQBGfcjb == true){IDPQBGfcjb = false;}
      if(uTQRaNFPVi == true){uTQRaNFPVi = false;}
      if(VtthUFJbiq == true){VtthUFJbiq = false;}
      if(NbYZkSiInc == true){NbYZkSiInc = false;}
      if(moRjoFTszU == true){moRjoFTszU = false;}
      if(BNNwSNJhwu == true){BNNwSNJhwu = false;}
      if(wDtsNTupgI == true){wDtsNTupgI = false;}
      if(dxaswfcJrO == true){dxaswfcJrO = false;}
      if(lPbOoAOcHX == true){lPbOoAOcHX = false;}
      if(IBLsfiuYWV == true){IBLsfiuYWV = false;}
      if(KcMqpDlTAl == true){KcMqpDlTAl = false;}
      if(jAogJgbeDM == true){jAogJgbeDM = false;}
      if(ESiIAclhMM == true){ESiIAclhMM = false;}
      if(kElWEICkXl == true){kElWEICkXl = false;}
      if(OtbVmIMdiz == true){OtbVmIMdiz = false;}
      if(HPUJQrtEqN == true){HPUJQrtEqN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MHHOJFJQQI
{ 
  void UtFVJsqguz()
  { 
      bool nRWQaIOtGW = false;
      bool gUIHlVNEeN = false;
      bool TKRoWLCBVK = false;
      bool ZaixzErIQC = false;
      bool BUyHODxhxS = false;
      bool pzIXccAgsP = false;
      bool GMYuwGkKIh = false;
      bool cEmbMyLKaS = false;
      bool OTEDTaRLTV = false;
      bool DKOBwnwCKI = false;
      bool RlZPokLgKd = false;
      bool QoGZAlIUbV = false;
      bool nYpldRpkeX = false;
      bool CIzSBctnNh = false;
      bool OkBoEOEnBK = false;
      bool faanTsumkW = false;
      bool uaBmbIonYX = false;
      bool rTGsHCXBhP = false;
      bool NCjUrbhLyI = false;
      bool gHCpmmiNNw = false;
      string meZEHxuTdC;
      string ftuMTrKUoV;
      string mXotsKgtEH;
      string lUWzAiTyQj;
      string fsMpnLVrWS;
      string WZmroPofLx;
      string PBOVQKWuMk;
      string YLDFptLzGg;
      string noXlkLheKk;
      string snmTTddpYc;
      string naelsKVhBu;
      string EpZdIadckE;
      string crkbqkYjkL;
      string QUZcrNJkrZ;
      string pAcPgDOIKr;
      string AAFUzwoDuI;
      string llwpdiPwlt;
      string RrkKOcOUum;
      string WPYrKQPFdw;
      string XFpinDDmkx;
      if(meZEHxuTdC == naelsKVhBu){nRWQaIOtGW = true;}
      else if(naelsKVhBu == meZEHxuTdC){RlZPokLgKd = true;}
      if(ftuMTrKUoV == EpZdIadckE){gUIHlVNEeN = true;}
      else if(EpZdIadckE == ftuMTrKUoV){QoGZAlIUbV = true;}
      if(mXotsKgtEH == crkbqkYjkL){TKRoWLCBVK = true;}
      else if(crkbqkYjkL == mXotsKgtEH){nYpldRpkeX = true;}
      if(lUWzAiTyQj == QUZcrNJkrZ){ZaixzErIQC = true;}
      else if(QUZcrNJkrZ == lUWzAiTyQj){CIzSBctnNh = true;}
      if(fsMpnLVrWS == pAcPgDOIKr){BUyHODxhxS = true;}
      else if(pAcPgDOIKr == fsMpnLVrWS){OkBoEOEnBK = true;}
      if(WZmroPofLx == AAFUzwoDuI){pzIXccAgsP = true;}
      else if(AAFUzwoDuI == WZmroPofLx){faanTsumkW = true;}
      if(PBOVQKWuMk == llwpdiPwlt){GMYuwGkKIh = true;}
      else if(llwpdiPwlt == PBOVQKWuMk){uaBmbIonYX = true;}
      if(YLDFptLzGg == RrkKOcOUum){cEmbMyLKaS = true;}
      if(noXlkLheKk == WPYrKQPFdw){OTEDTaRLTV = true;}
      if(snmTTddpYc == XFpinDDmkx){DKOBwnwCKI = true;}
      while(RrkKOcOUum == YLDFptLzGg){rTGsHCXBhP = true;}
      while(WPYrKQPFdw == WPYrKQPFdw){NCjUrbhLyI = true;}
      while(XFpinDDmkx == XFpinDDmkx){gHCpmmiNNw = true;}
      if(nRWQaIOtGW == true){nRWQaIOtGW = false;}
      if(gUIHlVNEeN == true){gUIHlVNEeN = false;}
      if(TKRoWLCBVK == true){TKRoWLCBVK = false;}
      if(ZaixzErIQC == true){ZaixzErIQC = false;}
      if(BUyHODxhxS == true){BUyHODxhxS = false;}
      if(pzIXccAgsP == true){pzIXccAgsP = false;}
      if(GMYuwGkKIh == true){GMYuwGkKIh = false;}
      if(cEmbMyLKaS == true){cEmbMyLKaS = false;}
      if(OTEDTaRLTV == true){OTEDTaRLTV = false;}
      if(DKOBwnwCKI == true){DKOBwnwCKI = false;}
      if(RlZPokLgKd == true){RlZPokLgKd = false;}
      if(QoGZAlIUbV == true){QoGZAlIUbV = false;}
      if(nYpldRpkeX == true){nYpldRpkeX = false;}
      if(CIzSBctnNh == true){CIzSBctnNh = false;}
      if(OkBoEOEnBK == true){OkBoEOEnBK = false;}
      if(faanTsumkW == true){faanTsumkW = false;}
      if(uaBmbIonYX == true){uaBmbIonYX = false;}
      if(rTGsHCXBhP == true){rTGsHCXBhP = false;}
      if(NCjUrbhLyI == true){NCjUrbhLyI = false;}
      if(gHCpmmiNNw == true){gHCpmmiNNw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFDYQXOUUA
{ 
  void RWUMGLotmG()
  { 
      bool daAFIScZFb = false;
      bool NEkoGNITZY = false;
      bool oUzlaJIrwT = false;
      bool KUfddPdkyX = false;
      bool otIcUzKlbO = false;
      bool KyAwmIbOdy = false;
      bool KkckQsYGLq = false;
      bool jXUCitMVRb = false;
      bool zVPgIMUjqV = false;
      bool mPGANEQWMa = false;
      bool ZDakdmcxMr = false;
      bool wFxBznUubD = false;
      bool YoPoDUQUnd = false;
      bool coJpCuueDV = false;
      bool jWWzZhRFBY = false;
      bool jUuJCjmkhJ = false;
      bool WIJhOGwGzD = false;
      bool sorFTCRQPU = false;
      bool CKSOtItAmR = false;
      bool IJxszaNojS = false;
      string LGPYBeebHc;
      string SOEPTCWwwX;
      string mTKSXiPdaw;
      string ZJYQHyoksV;
      string OJFDikGrmd;
      string feVUqqwwAS;
      string PABLCJpmIV;
      string MkCaIdNGim;
      string cWpwQunDZP;
      string BrjaFNItAZ;
      string uSjRRtbuLM;
      string doNNorJFuH;
      string VlNrTUBbUu;
      string VTGJrJmYeV;
      string TrqMlMeWkN;
      string DDzsEIFqxw;
      string szaQqJiDVf;
      string FkZYnctAGH;
      string peqGqSUNEi;
      string EubhcTRZUb;
      if(LGPYBeebHc == uSjRRtbuLM){daAFIScZFb = true;}
      else if(uSjRRtbuLM == LGPYBeebHc){ZDakdmcxMr = true;}
      if(SOEPTCWwwX == doNNorJFuH){NEkoGNITZY = true;}
      else if(doNNorJFuH == SOEPTCWwwX){wFxBznUubD = true;}
      if(mTKSXiPdaw == VlNrTUBbUu){oUzlaJIrwT = true;}
      else if(VlNrTUBbUu == mTKSXiPdaw){YoPoDUQUnd = true;}
      if(ZJYQHyoksV == VTGJrJmYeV){KUfddPdkyX = true;}
      else if(VTGJrJmYeV == ZJYQHyoksV){coJpCuueDV = true;}
      if(OJFDikGrmd == TrqMlMeWkN){otIcUzKlbO = true;}
      else if(TrqMlMeWkN == OJFDikGrmd){jWWzZhRFBY = true;}
      if(feVUqqwwAS == DDzsEIFqxw){KyAwmIbOdy = true;}
      else if(DDzsEIFqxw == feVUqqwwAS){jUuJCjmkhJ = true;}
      if(PABLCJpmIV == szaQqJiDVf){KkckQsYGLq = true;}
      else if(szaQqJiDVf == PABLCJpmIV){WIJhOGwGzD = true;}
      if(MkCaIdNGim == FkZYnctAGH){jXUCitMVRb = true;}
      if(cWpwQunDZP == peqGqSUNEi){zVPgIMUjqV = true;}
      if(BrjaFNItAZ == EubhcTRZUb){mPGANEQWMa = true;}
      while(FkZYnctAGH == MkCaIdNGim){sorFTCRQPU = true;}
      while(peqGqSUNEi == peqGqSUNEi){CKSOtItAmR = true;}
      while(EubhcTRZUb == EubhcTRZUb){IJxszaNojS = true;}
      if(daAFIScZFb == true){daAFIScZFb = false;}
      if(NEkoGNITZY == true){NEkoGNITZY = false;}
      if(oUzlaJIrwT == true){oUzlaJIrwT = false;}
      if(KUfddPdkyX == true){KUfddPdkyX = false;}
      if(otIcUzKlbO == true){otIcUzKlbO = false;}
      if(KyAwmIbOdy == true){KyAwmIbOdy = false;}
      if(KkckQsYGLq == true){KkckQsYGLq = false;}
      if(jXUCitMVRb == true){jXUCitMVRb = false;}
      if(zVPgIMUjqV == true){zVPgIMUjqV = false;}
      if(mPGANEQWMa == true){mPGANEQWMa = false;}
      if(ZDakdmcxMr == true){ZDakdmcxMr = false;}
      if(wFxBznUubD == true){wFxBznUubD = false;}
      if(YoPoDUQUnd == true){YoPoDUQUnd = false;}
      if(coJpCuueDV == true){coJpCuueDV = false;}
      if(jWWzZhRFBY == true){jWWzZhRFBY = false;}
      if(jUuJCjmkhJ == true){jUuJCjmkhJ = false;}
      if(WIJhOGwGzD == true){WIJhOGwGzD = false;}
      if(sorFTCRQPU == true){sorFTCRQPU = false;}
      if(CKSOtItAmR == true){CKSOtItAmR = false;}
      if(IJxszaNojS == true){IJxszaNojS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHIGVPLWOT
{ 
  void IdaeXrejlj()
  { 
      bool OIbEmthdoF = false;
      bool qMLPRgZpbZ = false;
      bool ylOkAFcOBh = false;
      bool YKqtcPhrxR = false;
      bool GAlpuwFLpz = false;
      bool buOfnbsqDg = false;
      bool RTcGgfURlB = false;
      bool zhrKTyAXoE = false;
      bool zQXBGcwLFA = false;
      bool WqnPAlWfJO = false;
      bool bnYnAsCELp = false;
      bool bUBzgAwazD = false;
      bool jJMkeItcJh = false;
      bool aUOabLrjBN = false;
      bool aqzPYBonhz = false;
      bool pwfFeRamIq = false;
      bool yZtdOHFaWV = false;
      bool ILYlcrJxMd = false;
      bool SFtKqenJwK = false;
      bool jEaKOBxVAQ = false;
      string jbUAuIzDTE;
      string HnFqACUQVe;
      string tIewsWXBBl;
      string ozaHLnQJOe;
      string iazxumaWoT;
      string MiOubbwYHX;
      string kyBgOIMyfM;
      string kLBqwSIhAF;
      string uBLgZGkeei;
      string qrBqtkYShm;
      string ZcpciBgXzJ;
      string SOXCbilUGI;
      string WgSxUrJKwK;
      string spAMeSKiyY;
      string YMfVPcTzOL;
      string yELYPrJsHp;
      string qWaoPcNLWJ;
      string XDVhjKBxgr;
      string YKwkModawl;
      string IRaHgBkqGm;
      if(jbUAuIzDTE == ZcpciBgXzJ){OIbEmthdoF = true;}
      else if(ZcpciBgXzJ == jbUAuIzDTE){bnYnAsCELp = true;}
      if(HnFqACUQVe == SOXCbilUGI){qMLPRgZpbZ = true;}
      else if(SOXCbilUGI == HnFqACUQVe){bUBzgAwazD = true;}
      if(tIewsWXBBl == WgSxUrJKwK){ylOkAFcOBh = true;}
      else if(WgSxUrJKwK == tIewsWXBBl){jJMkeItcJh = true;}
      if(ozaHLnQJOe == spAMeSKiyY){YKqtcPhrxR = true;}
      else if(spAMeSKiyY == ozaHLnQJOe){aUOabLrjBN = true;}
      if(iazxumaWoT == YMfVPcTzOL){GAlpuwFLpz = true;}
      else if(YMfVPcTzOL == iazxumaWoT){aqzPYBonhz = true;}
      if(MiOubbwYHX == yELYPrJsHp){buOfnbsqDg = true;}
      else if(yELYPrJsHp == MiOubbwYHX){pwfFeRamIq = true;}
      if(kyBgOIMyfM == qWaoPcNLWJ){RTcGgfURlB = true;}
      else if(qWaoPcNLWJ == kyBgOIMyfM){yZtdOHFaWV = true;}
      if(kLBqwSIhAF == XDVhjKBxgr){zhrKTyAXoE = true;}
      if(uBLgZGkeei == YKwkModawl){zQXBGcwLFA = true;}
      if(qrBqtkYShm == IRaHgBkqGm){WqnPAlWfJO = true;}
      while(XDVhjKBxgr == kLBqwSIhAF){ILYlcrJxMd = true;}
      while(YKwkModawl == YKwkModawl){SFtKqenJwK = true;}
      while(IRaHgBkqGm == IRaHgBkqGm){jEaKOBxVAQ = true;}
      if(OIbEmthdoF == true){OIbEmthdoF = false;}
      if(qMLPRgZpbZ == true){qMLPRgZpbZ = false;}
      if(ylOkAFcOBh == true){ylOkAFcOBh = false;}
      if(YKqtcPhrxR == true){YKqtcPhrxR = false;}
      if(GAlpuwFLpz == true){GAlpuwFLpz = false;}
      if(buOfnbsqDg == true){buOfnbsqDg = false;}
      if(RTcGgfURlB == true){RTcGgfURlB = false;}
      if(zhrKTyAXoE == true){zhrKTyAXoE = false;}
      if(zQXBGcwLFA == true){zQXBGcwLFA = false;}
      if(WqnPAlWfJO == true){WqnPAlWfJO = false;}
      if(bnYnAsCELp == true){bnYnAsCELp = false;}
      if(bUBzgAwazD == true){bUBzgAwazD = false;}
      if(jJMkeItcJh == true){jJMkeItcJh = false;}
      if(aUOabLrjBN == true){aUOabLrjBN = false;}
      if(aqzPYBonhz == true){aqzPYBonhz = false;}
      if(pwfFeRamIq == true){pwfFeRamIq = false;}
      if(yZtdOHFaWV == true){yZtdOHFaWV = false;}
      if(ILYlcrJxMd == true){ILYlcrJxMd = false;}
      if(SFtKqenJwK == true){SFtKqenJwK = false;}
      if(jEaKOBxVAQ == true){jEaKOBxVAQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALLWHILCAS
{ 
  void VghuqUhung()
  { 
      bool ALpGTLGuFN = false;
      bool txtIdrMNNk = false;
      bool ssiqYWVbOi = false;
      bool XFXmEHYKjh = false;
      bool JAORRWSebz = false;
      bool YxDFRHbyhx = false;
      bool odfWpnYHDV = false;
      bool TCdeareRZC = false;
      bool DqAPJZCRUx = false;
      bool fZcmseUqbd = false;
      bool xLaGeVTXdZ = false;
      bool cKYesxdQMQ = false;
      bool lHlGptZplu = false;
      bool XmowFrQtjm = false;
      bool FemuTUAxtu = false;
      bool BDeKqpYTPk = false;
      bool wdlhBoUcZB = false;
      bool gjfYKGTqlU = false;
      bool tbuptTIeEO = false;
      bool SwdzqasEse = false;
      string odIJhepjrq;
      string BzieYYgcrM;
      string hqPWoOlAET;
      string thJfnjHwon;
      string TEhIfATkUJ;
      string CidPixOlUS;
      string sofXxSoCpn;
      string QkmDsdIGqn;
      string uBfuQLEtxp;
      string VVaWudYJLM;
      string LQtfrRuZVF;
      string oHtgWqJkGk;
      string OtFASuJQHO;
      string EzteceHACz;
      string QdXqBNbtzD;
      string UnCayQKsNx;
      string HdSHBoMPDr;
      string jJhHUjWNyE;
      string TOREtPwTfM;
      string TNmFrlLQpL;
      if(odIJhepjrq == LQtfrRuZVF){ALpGTLGuFN = true;}
      else if(LQtfrRuZVF == odIJhepjrq){xLaGeVTXdZ = true;}
      if(BzieYYgcrM == oHtgWqJkGk){txtIdrMNNk = true;}
      else if(oHtgWqJkGk == BzieYYgcrM){cKYesxdQMQ = true;}
      if(hqPWoOlAET == OtFASuJQHO){ssiqYWVbOi = true;}
      else if(OtFASuJQHO == hqPWoOlAET){lHlGptZplu = true;}
      if(thJfnjHwon == EzteceHACz){XFXmEHYKjh = true;}
      else if(EzteceHACz == thJfnjHwon){XmowFrQtjm = true;}
      if(TEhIfATkUJ == QdXqBNbtzD){JAORRWSebz = true;}
      else if(QdXqBNbtzD == TEhIfATkUJ){FemuTUAxtu = true;}
      if(CidPixOlUS == UnCayQKsNx){YxDFRHbyhx = true;}
      else if(UnCayQKsNx == CidPixOlUS){BDeKqpYTPk = true;}
      if(sofXxSoCpn == HdSHBoMPDr){odfWpnYHDV = true;}
      else if(HdSHBoMPDr == sofXxSoCpn){wdlhBoUcZB = true;}
      if(QkmDsdIGqn == jJhHUjWNyE){TCdeareRZC = true;}
      if(uBfuQLEtxp == TOREtPwTfM){DqAPJZCRUx = true;}
      if(VVaWudYJLM == TNmFrlLQpL){fZcmseUqbd = true;}
      while(jJhHUjWNyE == QkmDsdIGqn){gjfYKGTqlU = true;}
      while(TOREtPwTfM == TOREtPwTfM){tbuptTIeEO = true;}
      while(TNmFrlLQpL == TNmFrlLQpL){SwdzqasEse = true;}
      if(ALpGTLGuFN == true){ALpGTLGuFN = false;}
      if(txtIdrMNNk == true){txtIdrMNNk = false;}
      if(ssiqYWVbOi == true){ssiqYWVbOi = false;}
      if(XFXmEHYKjh == true){XFXmEHYKjh = false;}
      if(JAORRWSebz == true){JAORRWSebz = false;}
      if(YxDFRHbyhx == true){YxDFRHbyhx = false;}
      if(odfWpnYHDV == true){odfWpnYHDV = false;}
      if(TCdeareRZC == true){TCdeareRZC = false;}
      if(DqAPJZCRUx == true){DqAPJZCRUx = false;}
      if(fZcmseUqbd == true){fZcmseUqbd = false;}
      if(xLaGeVTXdZ == true){xLaGeVTXdZ = false;}
      if(cKYesxdQMQ == true){cKYesxdQMQ = false;}
      if(lHlGptZplu == true){lHlGptZplu = false;}
      if(XmowFrQtjm == true){XmowFrQtjm = false;}
      if(FemuTUAxtu == true){FemuTUAxtu = false;}
      if(BDeKqpYTPk == true){BDeKqpYTPk = false;}
      if(wdlhBoUcZB == true){wdlhBoUcZB = false;}
      if(gjfYKGTqlU == true){gjfYKGTqlU = false;}
      if(tbuptTIeEO == true){tbuptTIeEO = false;}
      if(SwdzqasEse == true){SwdzqasEse = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHRSAGEYPV
{ 
  void WoQdfVBAWX()
  { 
      bool DQWoWxMNFc = false;
      bool oEECEhxgAI = false;
      bool TnAbhwlcDj = false;
      bool SYCHVejtat = false;
      bool JMxrgKAMNI = false;
      bool zxFKAPPuHZ = false;
      bool LiKUKQBwfY = false;
      bool xCGFyGpItX = false;
      bool wYPukUTrHG = false;
      bool PnmAiaCcgQ = false;
      bool IDgoKwqzLs = false;
      bool YHBidmTPjp = false;
      bool xInYJIPFWX = false;
      bool ENacOrqZjn = false;
      bool cTgOgHmDWw = false;
      bool GmsqTzOHeC = false;
      bool gkbnoLgYUk = false;
      bool useuMcbZqB = false;
      bool VLiaQQTiIP = false;
      bool ciuhHrqsYV = false;
      string RQZchLRrgi;
      string FDCZBpishC;
      string sWqcxKRkaI;
      string knsYoCCrxD;
      string WoFzzHZIwX;
      string JAdNOuZwfX;
      string tgRXyQJdky;
      string npwefDQrdo;
      string kIoCyjJfJs;
      string cFMYJpXgBh;
      string yuXxiSEzhL;
      string dhSpmlrOYN;
      string HcUqVidWUo;
      string eipwqokqSf;
      string fJyyPumVlX;
      string yIHmaUafbA;
      string oherfuqVyx;
      string AAushxeVbZ;
      string wHjxqWaDVW;
      string OEOSpxeFST;
      if(RQZchLRrgi == yuXxiSEzhL){DQWoWxMNFc = true;}
      else if(yuXxiSEzhL == RQZchLRrgi){IDgoKwqzLs = true;}
      if(FDCZBpishC == dhSpmlrOYN){oEECEhxgAI = true;}
      else if(dhSpmlrOYN == FDCZBpishC){YHBidmTPjp = true;}
      if(sWqcxKRkaI == HcUqVidWUo){TnAbhwlcDj = true;}
      else if(HcUqVidWUo == sWqcxKRkaI){xInYJIPFWX = true;}
      if(knsYoCCrxD == eipwqokqSf){SYCHVejtat = true;}
      else if(eipwqokqSf == knsYoCCrxD){ENacOrqZjn = true;}
      if(WoFzzHZIwX == fJyyPumVlX){JMxrgKAMNI = true;}
      else if(fJyyPumVlX == WoFzzHZIwX){cTgOgHmDWw = true;}
      if(JAdNOuZwfX == yIHmaUafbA){zxFKAPPuHZ = true;}
      else if(yIHmaUafbA == JAdNOuZwfX){GmsqTzOHeC = true;}
      if(tgRXyQJdky == oherfuqVyx){LiKUKQBwfY = true;}
      else if(oherfuqVyx == tgRXyQJdky){gkbnoLgYUk = true;}
      if(npwefDQrdo == AAushxeVbZ){xCGFyGpItX = true;}
      if(kIoCyjJfJs == wHjxqWaDVW){wYPukUTrHG = true;}
      if(cFMYJpXgBh == OEOSpxeFST){PnmAiaCcgQ = true;}
      while(AAushxeVbZ == npwefDQrdo){useuMcbZqB = true;}
      while(wHjxqWaDVW == wHjxqWaDVW){VLiaQQTiIP = true;}
      while(OEOSpxeFST == OEOSpxeFST){ciuhHrqsYV = true;}
      if(DQWoWxMNFc == true){DQWoWxMNFc = false;}
      if(oEECEhxgAI == true){oEECEhxgAI = false;}
      if(TnAbhwlcDj == true){TnAbhwlcDj = false;}
      if(SYCHVejtat == true){SYCHVejtat = false;}
      if(JMxrgKAMNI == true){JMxrgKAMNI = false;}
      if(zxFKAPPuHZ == true){zxFKAPPuHZ = false;}
      if(LiKUKQBwfY == true){LiKUKQBwfY = false;}
      if(xCGFyGpItX == true){xCGFyGpItX = false;}
      if(wYPukUTrHG == true){wYPukUTrHG = false;}
      if(PnmAiaCcgQ == true){PnmAiaCcgQ = false;}
      if(IDgoKwqzLs == true){IDgoKwqzLs = false;}
      if(YHBidmTPjp == true){YHBidmTPjp = false;}
      if(xInYJIPFWX == true){xInYJIPFWX = false;}
      if(ENacOrqZjn == true){ENacOrqZjn = false;}
      if(cTgOgHmDWw == true){cTgOgHmDWw = false;}
      if(GmsqTzOHeC == true){GmsqTzOHeC = false;}
      if(gkbnoLgYUk == true){gkbnoLgYUk = false;}
      if(useuMcbZqB == true){useuMcbZqB = false;}
      if(VLiaQQTiIP == true){VLiaQQTiIP = false;}
      if(ciuhHrqsYV == true){ciuhHrqsYV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMZHPIPRIP
{ 
  void pgwksmLaaM()
  { 
      bool nItBRRuZiX = false;
      bool lmGVtjxgRR = false;
      bool XHsxpTDXZB = false;
      bool UKwkSkXfkU = false;
      bool uSXfUbCqyT = false;
      bool cPxTRfOwLx = false;
      bool NWzhDbpVCI = false;
      bool MQwxWFiNcN = false;
      bool RMZGXENcSl = false;
      bool WbTnHXSpbs = false;
      bool lfnoHMTAwM = false;
      bool xBTyeAwsJy = false;
      bool NNCQlkxIoy = false;
      bool lrkiakYkyL = false;
      bool kNfGoUIUIG = false;
      bool bYgcfXcXCV = false;
      bool PKKyZEQjWs = false;
      bool bLtxMzhwbR = false;
      bool cbziWNLHDD = false;
      bool HBhbwZDhfj = false;
      string sOxRhotUpn;
      string JTFZhPJEsh;
      string joQZTLSLDf;
      string fBfYXkTVSi;
      string XZBCttdPjj;
      string GFpkUDxWyW;
      string VhQKIIngBx;
      string wnkJKKnOfY;
      string gDbTYZLtEU;
      string mwXwMoIptl;
      string FxNlmSTfZK;
      string OiqYoSGxkh;
      string wsbgJzQowV;
      string ByTsTjoofG;
      string FfTtGDFyGt;
      string iLFLoLUgbn;
      string CeiEIQPxEE;
      string cQQebQZhZG;
      string sRhCmpsHEH;
      string OIMrEawOlo;
      if(sOxRhotUpn == FxNlmSTfZK){nItBRRuZiX = true;}
      else if(FxNlmSTfZK == sOxRhotUpn){lfnoHMTAwM = true;}
      if(JTFZhPJEsh == OiqYoSGxkh){lmGVtjxgRR = true;}
      else if(OiqYoSGxkh == JTFZhPJEsh){xBTyeAwsJy = true;}
      if(joQZTLSLDf == wsbgJzQowV){XHsxpTDXZB = true;}
      else if(wsbgJzQowV == joQZTLSLDf){NNCQlkxIoy = true;}
      if(fBfYXkTVSi == ByTsTjoofG){UKwkSkXfkU = true;}
      else if(ByTsTjoofG == fBfYXkTVSi){lrkiakYkyL = true;}
      if(XZBCttdPjj == FfTtGDFyGt){uSXfUbCqyT = true;}
      else if(FfTtGDFyGt == XZBCttdPjj){kNfGoUIUIG = true;}
      if(GFpkUDxWyW == iLFLoLUgbn){cPxTRfOwLx = true;}
      else if(iLFLoLUgbn == GFpkUDxWyW){bYgcfXcXCV = true;}
      if(VhQKIIngBx == CeiEIQPxEE){NWzhDbpVCI = true;}
      else if(CeiEIQPxEE == VhQKIIngBx){PKKyZEQjWs = true;}
      if(wnkJKKnOfY == cQQebQZhZG){MQwxWFiNcN = true;}
      if(gDbTYZLtEU == sRhCmpsHEH){RMZGXENcSl = true;}
      if(mwXwMoIptl == OIMrEawOlo){WbTnHXSpbs = true;}
      while(cQQebQZhZG == wnkJKKnOfY){bLtxMzhwbR = true;}
      while(sRhCmpsHEH == sRhCmpsHEH){cbziWNLHDD = true;}
      while(OIMrEawOlo == OIMrEawOlo){HBhbwZDhfj = true;}
      if(nItBRRuZiX == true){nItBRRuZiX = false;}
      if(lmGVtjxgRR == true){lmGVtjxgRR = false;}
      if(XHsxpTDXZB == true){XHsxpTDXZB = false;}
      if(UKwkSkXfkU == true){UKwkSkXfkU = false;}
      if(uSXfUbCqyT == true){uSXfUbCqyT = false;}
      if(cPxTRfOwLx == true){cPxTRfOwLx = false;}
      if(NWzhDbpVCI == true){NWzhDbpVCI = false;}
      if(MQwxWFiNcN == true){MQwxWFiNcN = false;}
      if(RMZGXENcSl == true){RMZGXENcSl = false;}
      if(WbTnHXSpbs == true){WbTnHXSpbs = false;}
      if(lfnoHMTAwM == true){lfnoHMTAwM = false;}
      if(xBTyeAwsJy == true){xBTyeAwsJy = false;}
      if(NNCQlkxIoy == true){NNCQlkxIoy = false;}
      if(lrkiakYkyL == true){lrkiakYkyL = false;}
      if(kNfGoUIUIG == true){kNfGoUIUIG = false;}
      if(bYgcfXcXCV == true){bYgcfXcXCV = false;}
      if(PKKyZEQjWs == true){PKKyZEQjWs = false;}
      if(bLtxMzhwbR == true){bLtxMzhwbR = false;}
      if(cbziWNLHDD == true){cbziWNLHDD = false;}
      if(HBhbwZDhfj == true){HBhbwZDhfj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGSVYIFVJY
{ 
  void LIfJhDWDUl()
  { 
      bool xxgslyLNJz = false;
      bool hsDuAVCHfZ = false;
      bool nFqXwgwNiG = false;
      bool NYzVyDtzYM = false;
      bool ALHiIoLzGy = false;
      bool tugeKrFIwE = false;
      bool CydDkIshxx = false;
      bool aDhSZbxHPH = false;
      bool UxGkMSrUKF = false;
      bool xkCUKChDyA = false;
      bool udCJWqNNEi = false;
      bool txsojEqrqS = false;
      bool QYXqzpANIX = false;
      bool ssJOMquxNU = false;
      bool EdPaLzqNjF = false;
      bool KoMfiVFLJg = false;
      bool pzFgpAnecr = false;
      bool JteVNlJxeA = false;
      bool ymcCMDgcep = false;
      bool kjmfdFXhkK = false;
      string LxHWzcBtOY;
      string fDExxAQJQH;
      string TbGdYVxghE;
      string TJNszMcUKB;
      string mTxPZBBCpy;
      string QMbObiqdyc;
      string fTLJEVpLxj;
      string XuzOUzepDW;
      string TtqimHhyRQ;
      string UyWgUSInKE;
      string LpFFaVNMsb;
      string EBZaIlccVx;
      string mqsgOYXRtC;
      string qqezLdokIR;
      string sVEoMTXwXi;
      string pfRNQUwYpB;
      string xwSqkNWaOe;
      string xqTEDRlDUu;
      string AbsKLLYQiq;
      string hPtGUxDMEz;
      if(LxHWzcBtOY == LpFFaVNMsb){xxgslyLNJz = true;}
      else if(LpFFaVNMsb == LxHWzcBtOY){udCJWqNNEi = true;}
      if(fDExxAQJQH == EBZaIlccVx){hsDuAVCHfZ = true;}
      else if(EBZaIlccVx == fDExxAQJQH){txsojEqrqS = true;}
      if(TbGdYVxghE == mqsgOYXRtC){nFqXwgwNiG = true;}
      else if(mqsgOYXRtC == TbGdYVxghE){QYXqzpANIX = true;}
      if(TJNszMcUKB == qqezLdokIR){NYzVyDtzYM = true;}
      else if(qqezLdokIR == TJNszMcUKB){ssJOMquxNU = true;}
      if(mTxPZBBCpy == sVEoMTXwXi){ALHiIoLzGy = true;}
      else if(sVEoMTXwXi == mTxPZBBCpy){EdPaLzqNjF = true;}
      if(QMbObiqdyc == pfRNQUwYpB){tugeKrFIwE = true;}
      else if(pfRNQUwYpB == QMbObiqdyc){KoMfiVFLJg = true;}
      if(fTLJEVpLxj == xwSqkNWaOe){CydDkIshxx = true;}
      else if(xwSqkNWaOe == fTLJEVpLxj){pzFgpAnecr = true;}
      if(XuzOUzepDW == xqTEDRlDUu){aDhSZbxHPH = true;}
      if(TtqimHhyRQ == AbsKLLYQiq){UxGkMSrUKF = true;}
      if(UyWgUSInKE == hPtGUxDMEz){xkCUKChDyA = true;}
      while(xqTEDRlDUu == XuzOUzepDW){JteVNlJxeA = true;}
      while(AbsKLLYQiq == AbsKLLYQiq){ymcCMDgcep = true;}
      while(hPtGUxDMEz == hPtGUxDMEz){kjmfdFXhkK = true;}
      if(xxgslyLNJz == true){xxgslyLNJz = false;}
      if(hsDuAVCHfZ == true){hsDuAVCHfZ = false;}
      if(nFqXwgwNiG == true){nFqXwgwNiG = false;}
      if(NYzVyDtzYM == true){NYzVyDtzYM = false;}
      if(ALHiIoLzGy == true){ALHiIoLzGy = false;}
      if(tugeKrFIwE == true){tugeKrFIwE = false;}
      if(CydDkIshxx == true){CydDkIshxx = false;}
      if(aDhSZbxHPH == true){aDhSZbxHPH = false;}
      if(UxGkMSrUKF == true){UxGkMSrUKF = false;}
      if(xkCUKChDyA == true){xkCUKChDyA = false;}
      if(udCJWqNNEi == true){udCJWqNNEi = false;}
      if(txsojEqrqS == true){txsojEqrqS = false;}
      if(QYXqzpANIX == true){QYXqzpANIX = false;}
      if(ssJOMquxNU == true){ssJOMquxNU = false;}
      if(EdPaLzqNjF == true){EdPaLzqNjF = false;}
      if(KoMfiVFLJg == true){KoMfiVFLJg = false;}
      if(pzFgpAnecr == true){pzFgpAnecr = false;}
      if(JteVNlJxeA == true){JteVNlJxeA = false;}
      if(ymcCMDgcep == true){ymcCMDgcep = false;}
      if(kjmfdFXhkK == true){kjmfdFXhkK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDCGKQHABF
{ 
  void rnuBfSEcOM()
  { 
      bool tPuGEUVVUs = false;
      bool bxqgCNpgWS = false;
      bool ATtJfhHgMR = false;
      bool EcwTFFZVXV = false;
      bool YcZaihRPqo = false;
      bool WhcsKaUkaV = false;
      bool NnJDnzAXax = false;
      bool mUJAtWtSZx = false;
      bool QroWuWADJe = false;
      bool jntBIjTWmj = false;
      bool htntBBYbym = false;
      bool fBLcFVylHR = false;
      bool yxNwNzZHrK = false;
      bool DXfpPVDuUs = false;
      bool yYEVzhcRwl = false;
      bool kgOVkkfrgC = false;
      bool aQinjIVUMi = false;
      bool RDRNTZrqxe = false;
      bool WILFYWIKEe = false;
      bool pKOSShpPlp = false;
      string TinoGnyZZW;
      string chfeLxszSp;
      string GNUypgdsqS;
      string RcyRyhSCoc;
      string PYrPHdFpVB;
      string MXWFlFOoyZ;
      string KFiGEziOgd;
      string dqKpahVFqL;
      string bnWoGsGses;
      string TdEPRJpkKH;
      string upIrXVNgeE;
      string iJylxWisAK;
      string spjmKAmtXQ;
      string qjtiQledRk;
      string fYNZJJeRSu;
      string ZxkzNEGVhX;
      string iSJNNzOPVL;
      string qEaOeUcJdA;
      string UUbbqtztUL;
      string eJwtCMPzMK;
      if(TinoGnyZZW == upIrXVNgeE){tPuGEUVVUs = true;}
      else if(upIrXVNgeE == TinoGnyZZW){htntBBYbym = true;}
      if(chfeLxszSp == iJylxWisAK){bxqgCNpgWS = true;}
      else if(iJylxWisAK == chfeLxszSp){fBLcFVylHR = true;}
      if(GNUypgdsqS == spjmKAmtXQ){ATtJfhHgMR = true;}
      else if(spjmKAmtXQ == GNUypgdsqS){yxNwNzZHrK = true;}
      if(RcyRyhSCoc == qjtiQledRk){EcwTFFZVXV = true;}
      else if(qjtiQledRk == RcyRyhSCoc){DXfpPVDuUs = true;}
      if(PYrPHdFpVB == fYNZJJeRSu){YcZaihRPqo = true;}
      else if(fYNZJJeRSu == PYrPHdFpVB){yYEVzhcRwl = true;}
      if(MXWFlFOoyZ == ZxkzNEGVhX){WhcsKaUkaV = true;}
      else if(ZxkzNEGVhX == MXWFlFOoyZ){kgOVkkfrgC = true;}
      if(KFiGEziOgd == iSJNNzOPVL){NnJDnzAXax = true;}
      else if(iSJNNzOPVL == KFiGEziOgd){aQinjIVUMi = true;}
      if(dqKpahVFqL == qEaOeUcJdA){mUJAtWtSZx = true;}
      if(bnWoGsGses == UUbbqtztUL){QroWuWADJe = true;}
      if(TdEPRJpkKH == eJwtCMPzMK){jntBIjTWmj = true;}
      while(qEaOeUcJdA == dqKpahVFqL){RDRNTZrqxe = true;}
      while(UUbbqtztUL == UUbbqtztUL){WILFYWIKEe = true;}
      while(eJwtCMPzMK == eJwtCMPzMK){pKOSShpPlp = true;}
      if(tPuGEUVVUs == true){tPuGEUVVUs = false;}
      if(bxqgCNpgWS == true){bxqgCNpgWS = false;}
      if(ATtJfhHgMR == true){ATtJfhHgMR = false;}
      if(EcwTFFZVXV == true){EcwTFFZVXV = false;}
      if(YcZaihRPqo == true){YcZaihRPqo = false;}
      if(WhcsKaUkaV == true){WhcsKaUkaV = false;}
      if(NnJDnzAXax == true){NnJDnzAXax = false;}
      if(mUJAtWtSZx == true){mUJAtWtSZx = false;}
      if(QroWuWADJe == true){QroWuWADJe = false;}
      if(jntBIjTWmj == true){jntBIjTWmj = false;}
      if(htntBBYbym == true){htntBBYbym = false;}
      if(fBLcFVylHR == true){fBLcFVylHR = false;}
      if(yxNwNzZHrK == true){yxNwNzZHrK = false;}
      if(DXfpPVDuUs == true){DXfpPVDuUs = false;}
      if(yYEVzhcRwl == true){yYEVzhcRwl = false;}
      if(kgOVkkfrgC == true){kgOVkkfrgC = false;}
      if(aQinjIVUMi == true){aQinjIVUMi = false;}
      if(RDRNTZrqxe == true){RDRNTZrqxe = false;}
      if(WILFYWIKEe == true){WILFYWIKEe = false;}
      if(pKOSShpPlp == true){pKOSShpPlp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNTTGTVLIJ
{ 
  void BrFmVJfedo()
  { 
      bool OiokniHzXp = false;
      bool RXVEKUwXqD = false;
      bool PlgqYRlitw = false;
      bool foZfLAdTWy = false;
      bool OLOppEDmeu = false;
      bool HiArjbBxLV = false;
      bool wYEbKbyosK = false;
      bool pbAsnDXqBT = false;
      bool OzEzowngwi = false;
      bool zgIBCpHmfN = false;
      bool GNtUFfiHDf = false;
      bool EKwqHwTFmN = false;
      bool nQsJKJTypx = false;
      bool wkLmNAEjtI = false;
      bool NgdQenjQtF = false;
      bool WBARZoUjJu = false;
      bool MjQFjTzIdG = false;
      bool rjLdAGmbeW = false;
      bool YCEkatjsMY = false;
      bool eUZywcPXgK = false;
      string koJmSRzTYx;
      string UkXucTMuhh;
      string MqSRclSmuF;
      string ubGdRsOGqu;
      string ZPtezZekZh;
      string DxMYbtWqJf;
      string zMXSCrdsdi;
      string FFDmHwxmRC;
      string HhMNCyPgBX;
      string WXwLwNracG;
      string ukHqcxsYRe;
      string xiZHYRAKQE;
      string cwqGMhIrpt;
      string EVKKHWZVkE;
      string EpPWamxome;
      string MgKXdysBdu;
      string nBiXaaYOAC;
      string qdZLzmgUfZ;
      string jTFLgWLlgI;
      string cYqpQDGquz;
      if(koJmSRzTYx == ukHqcxsYRe){OiokniHzXp = true;}
      else if(ukHqcxsYRe == koJmSRzTYx){GNtUFfiHDf = true;}
      if(UkXucTMuhh == xiZHYRAKQE){RXVEKUwXqD = true;}
      else if(xiZHYRAKQE == UkXucTMuhh){EKwqHwTFmN = true;}
      if(MqSRclSmuF == cwqGMhIrpt){PlgqYRlitw = true;}
      else if(cwqGMhIrpt == MqSRclSmuF){nQsJKJTypx = true;}
      if(ubGdRsOGqu == EVKKHWZVkE){foZfLAdTWy = true;}
      else if(EVKKHWZVkE == ubGdRsOGqu){wkLmNAEjtI = true;}
      if(ZPtezZekZh == EpPWamxome){OLOppEDmeu = true;}
      else if(EpPWamxome == ZPtezZekZh){NgdQenjQtF = true;}
      if(DxMYbtWqJf == MgKXdysBdu){HiArjbBxLV = true;}
      else if(MgKXdysBdu == DxMYbtWqJf){WBARZoUjJu = true;}
      if(zMXSCrdsdi == nBiXaaYOAC){wYEbKbyosK = true;}
      else if(nBiXaaYOAC == zMXSCrdsdi){MjQFjTzIdG = true;}
      if(FFDmHwxmRC == qdZLzmgUfZ){pbAsnDXqBT = true;}
      if(HhMNCyPgBX == jTFLgWLlgI){OzEzowngwi = true;}
      if(WXwLwNracG == cYqpQDGquz){zgIBCpHmfN = true;}
      while(qdZLzmgUfZ == FFDmHwxmRC){rjLdAGmbeW = true;}
      while(jTFLgWLlgI == jTFLgWLlgI){YCEkatjsMY = true;}
      while(cYqpQDGquz == cYqpQDGquz){eUZywcPXgK = true;}
      if(OiokniHzXp == true){OiokniHzXp = false;}
      if(RXVEKUwXqD == true){RXVEKUwXqD = false;}
      if(PlgqYRlitw == true){PlgqYRlitw = false;}
      if(foZfLAdTWy == true){foZfLAdTWy = false;}
      if(OLOppEDmeu == true){OLOppEDmeu = false;}
      if(HiArjbBxLV == true){HiArjbBxLV = false;}
      if(wYEbKbyosK == true){wYEbKbyosK = false;}
      if(pbAsnDXqBT == true){pbAsnDXqBT = false;}
      if(OzEzowngwi == true){OzEzowngwi = false;}
      if(zgIBCpHmfN == true){zgIBCpHmfN = false;}
      if(GNtUFfiHDf == true){GNtUFfiHDf = false;}
      if(EKwqHwTFmN == true){EKwqHwTFmN = false;}
      if(nQsJKJTypx == true){nQsJKJTypx = false;}
      if(wkLmNAEjtI == true){wkLmNAEjtI = false;}
      if(NgdQenjQtF == true){NgdQenjQtF = false;}
      if(WBARZoUjJu == true){WBARZoUjJu = false;}
      if(MjQFjTzIdG == true){MjQFjTzIdG = false;}
      if(rjLdAGmbeW == true){rjLdAGmbeW = false;}
      if(YCEkatjsMY == true){YCEkatjsMY = false;}
      if(eUZywcPXgK == true){eUZywcPXgK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBORZWYANB
{ 
  void UFYKphWypP()
  { 
      bool sXqRTCLKyJ = false;
      bool lPAawCrjVe = false;
      bool CHcHCXuFLP = false;
      bool XNlOZfHVau = false;
      bool XFatYVcPKJ = false;
      bool LKpVmltiOu = false;
      bool HGzhkYclAQ = false;
      bool uVJaHxgihg = false;
      bool uetBENWQan = false;
      bool kXGemRFrIz = false;
      bool rqOtOoAOOp = false;
      bool FLBhAbLydX = false;
      bool CMKMeWPdno = false;
      bool qnZhnEPzlP = false;
      bool MIBjiZVXeK = false;
      bool FHOkxffCPq = false;
      bool YVaZzQlStw = false;
      bool MLLNKsLadF = false;
      bool AqzciiZnkI = false;
      bool XNjtppgbjS = false;
      string diSnYoNqyY;
      string HpHwgWuoNP;
      string itwwExEMFq;
      string MpuOJlqkLq;
      string PfbhpNAEjn;
      string TDSHajmVia;
      string kBlHMRtrlt;
      string eKdWACSNGq;
      string xAbQWIWmnZ;
      string zVBjGNtTVX;
      string SHRpJJZwGX;
      string QYPqdjYUkD;
      string tGEMtJIsQm;
      string IyrhXohlHM;
      string iagQIaFKGV;
      string oYiSdMDEuA;
      string AfeTOSghSn;
      string BlMXTTZnET;
      string DymtxjPYEL;
      string lcqHMDuMBp;
      if(diSnYoNqyY == SHRpJJZwGX){sXqRTCLKyJ = true;}
      else if(SHRpJJZwGX == diSnYoNqyY){rqOtOoAOOp = true;}
      if(HpHwgWuoNP == QYPqdjYUkD){lPAawCrjVe = true;}
      else if(QYPqdjYUkD == HpHwgWuoNP){FLBhAbLydX = true;}
      if(itwwExEMFq == tGEMtJIsQm){CHcHCXuFLP = true;}
      else if(tGEMtJIsQm == itwwExEMFq){CMKMeWPdno = true;}
      if(MpuOJlqkLq == IyrhXohlHM){XNlOZfHVau = true;}
      else if(IyrhXohlHM == MpuOJlqkLq){qnZhnEPzlP = true;}
      if(PfbhpNAEjn == iagQIaFKGV){XFatYVcPKJ = true;}
      else if(iagQIaFKGV == PfbhpNAEjn){MIBjiZVXeK = true;}
      if(TDSHajmVia == oYiSdMDEuA){LKpVmltiOu = true;}
      else if(oYiSdMDEuA == TDSHajmVia){FHOkxffCPq = true;}
      if(kBlHMRtrlt == AfeTOSghSn){HGzhkYclAQ = true;}
      else if(AfeTOSghSn == kBlHMRtrlt){YVaZzQlStw = true;}
      if(eKdWACSNGq == BlMXTTZnET){uVJaHxgihg = true;}
      if(xAbQWIWmnZ == DymtxjPYEL){uetBENWQan = true;}
      if(zVBjGNtTVX == lcqHMDuMBp){kXGemRFrIz = true;}
      while(BlMXTTZnET == eKdWACSNGq){MLLNKsLadF = true;}
      while(DymtxjPYEL == DymtxjPYEL){AqzciiZnkI = true;}
      while(lcqHMDuMBp == lcqHMDuMBp){XNjtppgbjS = true;}
      if(sXqRTCLKyJ == true){sXqRTCLKyJ = false;}
      if(lPAawCrjVe == true){lPAawCrjVe = false;}
      if(CHcHCXuFLP == true){CHcHCXuFLP = false;}
      if(XNlOZfHVau == true){XNlOZfHVau = false;}
      if(XFatYVcPKJ == true){XFatYVcPKJ = false;}
      if(LKpVmltiOu == true){LKpVmltiOu = false;}
      if(HGzhkYclAQ == true){HGzhkYclAQ = false;}
      if(uVJaHxgihg == true){uVJaHxgihg = false;}
      if(uetBENWQan == true){uetBENWQan = false;}
      if(kXGemRFrIz == true){kXGemRFrIz = false;}
      if(rqOtOoAOOp == true){rqOtOoAOOp = false;}
      if(FLBhAbLydX == true){FLBhAbLydX = false;}
      if(CMKMeWPdno == true){CMKMeWPdno = false;}
      if(qnZhnEPzlP == true){qnZhnEPzlP = false;}
      if(MIBjiZVXeK == true){MIBjiZVXeK = false;}
      if(FHOkxffCPq == true){FHOkxffCPq = false;}
      if(YVaZzQlStw == true){YVaZzQlStw = false;}
      if(MLLNKsLadF == true){MLLNKsLadF = false;}
      if(AqzciiZnkI == true){AqzciiZnkI = false;}
      if(XNjtppgbjS == true){XNjtppgbjS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZGQRMPJDW
{ 
  void ReBGaoOYcJ()
  { 
      bool GUDcGmNnEY = false;
      bool wgUjoWThBE = false;
      bool reUCJbmZRA = false;
      bool lPulihLqKB = false;
      bool FniGMjaHLn = false;
      bool uSsyPazBSe = false;
      bool AnWElfliAG = false;
      bool LbXAyDwNpZ = false;
      bool BfNcETWxWI = false;
      bool iKXfARQeUf = false;
      bool yrHFcSurzL = false;
      bool ekKsdUZszS = false;
      bool JnLqXAEqzg = false;
      bool mQsJbIYHAl = false;
      bool XdxKcxzdCf = false;
      bool qXfBWJfPgb = false;
      bool ODsSYNrBRU = false;
      bool wSsMueqAOa = false;
      bool AZoToOkrlR = false;
      bool cIaYXTkelO = false;
      string QpauJlGDkJ;
      string kWhIjuFxFc;
      string LPTjzjDGUx;
      string ZztDrVFlzw;
      string LseXnfiDCH;
      string iJDNxAVpuY;
      string izimjkbdPN;
      string oTyIRRkwwT;
      string BzEMNPwgFr;
      string zPpaNLKqnC;
      string DEmnSPLuwe;
      string OZtbWitVZT;
      string ouYXOZdXuF;
      string HtHsQxLQtx;
      string DBkZcYVODd;
      string RnQTNHfPZs;
      string lnzpXUSAKZ;
      string XdacPnKytp;
      string DOTQnScmfI;
      string QuqBLPBtCH;
      if(QpauJlGDkJ == DEmnSPLuwe){GUDcGmNnEY = true;}
      else if(DEmnSPLuwe == QpauJlGDkJ){yrHFcSurzL = true;}
      if(kWhIjuFxFc == OZtbWitVZT){wgUjoWThBE = true;}
      else if(OZtbWitVZT == kWhIjuFxFc){ekKsdUZszS = true;}
      if(LPTjzjDGUx == ouYXOZdXuF){reUCJbmZRA = true;}
      else if(ouYXOZdXuF == LPTjzjDGUx){JnLqXAEqzg = true;}
      if(ZztDrVFlzw == HtHsQxLQtx){lPulihLqKB = true;}
      else if(HtHsQxLQtx == ZztDrVFlzw){mQsJbIYHAl = true;}
      if(LseXnfiDCH == DBkZcYVODd){FniGMjaHLn = true;}
      else if(DBkZcYVODd == LseXnfiDCH){XdxKcxzdCf = true;}
      if(iJDNxAVpuY == RnQTNHfPZs){uSsyPazBSe = true;}
      else if(RnQTNHfPZs == iJDNxAVpuY){qXfBWJfPgb = true;}
      if(izimjkbdPN == lnzpXUSAKZ){AnWElfliAG = true;}
      else if(lnzpXUSAKZ == izimjkbdPN){ODsSYNrBRU = true;}
      if(oTyIRRkwwT == XdacPnKytp){LbXAyDwNpZ = true;}
      if(BzEMNPwgFr == DOTQnScmfI){BfNcETWxWI = true;}
      if(zPpaNLKqnC == QuqBLPBtCH){iKXfARQeUf = true;}
      while(XdacPnKytp == oTyIRRkwwT){wSsMueqAOa = true;}
      while(DOTQnScmfI == DOTQnScmfI){AZoToOkrlR = true;}
      while(QuqBLPBtCH == QuqBLPBtCH){cIaYXTkelO = true;}
      if(GUDcGmNnEY == true){GUDcGmNnEY = false;}
      if(wgUjoWThBE == true){wgUjoWThBE = false;}
      if(reUCJbmZRA == true){reUCJbmZRA = false;}
      if(lPulihLqKB == true){lPulihLqKB = false;}
      if(FniGMjaHLn == true){FniGMjaHLn = false;}
      if(uSsyPazBSe == true){uSsyPazBSe = false;}
      if(AnWElfliAG == true){AnWElfliAG = false;}
      if(LbXAyDwNpZ == true){LbXAyDwNpZ = false;}
      if(BfNcETWxWI == true){BfNcETWxWI = false;}
      if(iKXfARQeUf == true){iKXfARQeUf = false;}
      if(yrHFcSurzL == true){yrHFcSurzL = false;}
      if(ekKsdUZszS == true){ekKsdUZszS = false;}
      if(JnLqXAEqzg == true){JnLqXAEqzg = false;}
      if(mQsJbIYHAl == true){mQsJbIYHAl = false;}
      if(XdxKcxzdCf == true){XdxKcxzdCf = false;}
      if(qXfBWJfPgb == true){qXfBWJfPgb = false;}
      if(ODsSYNrBRU == true){ODsSYNrBRU = false;}
      if(wSsMueqAOa == true){wSsMueqAOa = false;}
      if(AZoToOkrlR == true){AZoToOkrlR = false;}
      if(cIaYXTkelO == true){cIaYXTkelO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLFDZIFXLD
{ 
  void VzPpGdkSMS()
  { 
      bool XnohRmZUyV = false;
      bool onROWGaLWl = false;
      bool LrAyMUAnPc = false;
      bool klParwNWlF = false;
      bool YsOSRcjqxa = false;
      bool YFtkbenpUx = false;
      bool mlFVkDYqVZ = false;
      bool rEZRNSdhgj = false;
      bool jIqnEeqdzN = false;
      bool IXBnRmmsgO = false;
      bool DrUWhTfcWI = false;
      bool AFJkNduQQF = false;
      bool LtqIRUDkza = false;
      bool fkARfrnTGj = false;
      bool zOGpMCOPan = false;
      bool qVbbDJALFN = false;
      bool QtdwcPEqFU = false;
      bool paKgFwmBwO = false;
      bool GmJKiJJYOV = false;
      bool qbOsSEkKNw = false;
      string iccLIBSuFI;
      string VeSRWqpWeV;
      string AmDIZRDLMN;
      string VqLsRAynYq;
      string uAyZmwyJxO;
      string MsxcRwZUkp;
      string yHhqldSYzV;
      string rCymazndUd;
      string SsNyBbsibV;
      string adChsnSHmI;
      string cZKaVJuKCS;
      string HwAGWEsjoK;
      string kjxcuOzPsm;
      string ggpLAsilbr;
      string figJOdcuLn;
      string thScXsbgfH;
      string KfQPkaGnGd;
      string VGIxdCDnOQ;
      string kDEEryONnH;
      string QBGTgARQXn;
      if(iccLIBSuFI == cZKaVJuKCS){XnohRmZUyV = true;}
      else if(cZKaVJuKCS == iccLIBSuFI){DrUWhTfcWI = true;}
      if(VeSRWqpWeV == HwAGWEsjoK){onROWGaLWl = true;}
      else if(HwAGWEsjoK == VeSRWqpWeV){AFJkNduQQF = true;}
      if(AmDIZRDLMN == kjxcuOzPsm){LrAyMUAnPc = true;}
      else if(kjxcuOzPsm == AmDIZRDLMN){LtqIRUDkza = true;}
      if(VqLsRAynYq == ggpLAsilbr){klParwNWlF = true;}
      else if(ggpLAsilbr == VqLsRAynYq){fkARfrnTGj = true;}
      if(uAyZmwyJxO == figJOdcuLn){YsOSRcjqxa = true;}
      else if(figJOdcuLn == uAyZmwyJxO){zOGpMCOPan = true;}
      if(MsxcRwZUkp == thScXsbgfH){YFtkbenpUx = true;}
      else if(thScXsbgfH == MsxcRwZUkp){qVbbDJALFN = true;}
      if(yHhqldSYzV == KfQPkaGnGd){mlFVkDYqVZ = true;}
      else if(KfQPkaGnGd == yHhqldSYzV){QtdwcPEqFU = true;}
      if(rCymazndUd == VGIxdCDnOQ){rEZRNSdhgj = true;}
      if(SsNyBbsibV == kDEEryONnH){jIqnEeqdzN = true;}
      if(adChsnSHmI == QBGTgARQXn){IXBnRmmsgO = true;}
      while(VGIxdCDnOQ == rCymazndUd){paKgFwmBwO = true;}
      while(kDEEryONnH == kDEEryONnH){GmJKiJJYOV = true;}
      while(QBGTgARQXn == QBGTgARQXn){qbOsSEkKNw = true;}
      if(XnohRmZUyV == true){XnohRmZUyV = false;}
      if(onROWGaLWl == true){onROWGaLWl = false;}
      if(LrAyMUAnPc == true){LrAyMUAnPc = false;}
      if(klParwNWlF == true){klParwNWlF = false;}
      if(YsOSRcjqxa == true){YsOSRcjqxa = false;}
      if(YFtkbenpUx == true){YFtkbenpUx = false;}
      if(mlFVkDYqVZ == true){mlFVkDYqVZ = false;}
      if(rEZRNSdhgj == true){rEZRNSdhgj = false;}
      if(jIqnEeqdzN == true){jIqnEeqdzN = false;}
      if(IXBnRmmsgO == true){IXBnRmmsgO = false;}
      if(DrUWhTfcWI == true){DrUWhTfcWI = false;}
      if(AFJkNduQQF == true){AFJkNduQQF = false;}
      if(LtqIRUDkza == true){LtqIRUDkza = false;}
      if(fkARfrnTGj == true){fkARfrnTGj = false;}
      if(zOGpMCOPan == true){zOGpMCOPan = false;}
      if(qVbbDJALFN == true){qVbbDJALFN = false;}
      if(QtdwcPEqFU == true){QtdwcPEqFU = false;}
      if(paKgFwmBwO == true){paKgFwmBwO = false;}
      if(GmJKiJJYOV == true){GmJKiJJYOV = false;}
      if(qbOsSEkKNw == true){qbOsSEkKNw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPXFNPEJOJ
{ 
  void zbhcaGkWMV()
  { 
      bool lBJTAGLzop = false;
      bool WJwomzftid = false;
      bool meWskPWSFQ = false;
      bool ifSpWFZcBw = false;
      bool BqThruinhk = false;
      bool VUtaoGdQhj = false;
      bool issXGpqFSg = false;
      bool YCslbwLoBp = false;
      bool fikUuNkrAP = false;
      bool bJuQMIxubB = false;
      bool EdUALSbIys = false;
      bool uoPrDzHYbr = false;
      bool FyEDFPHbYT = false;
      bool yPMzkCOkIc = false;
      bool lcsHTmtCMN = false;
      bool BYTjuFZRuw = false;
      bool LAieuebPGB = false;
      bool kWPzGcFxiS = false;
      bool UFOLSYwcDf = false;
      bool cwoLQksOMn = false;
      string oMKwYnBqlH;
      string PpwuUpCxBX;
      string qzmlqINKYT;
      string tsEaFFebCN;
      string bXSRWpVdyJ;
      string MeisYpZXEP;
      string apSRMVkUoP;
      string KZtmwSgUOA;
      string mjLOGPJLBP;
      string eGWmmlEAEB;
      string FAoiylkwwF;
      string JEJEcpdEKx;
      string MYTZjEDHzK;
      string OfQNultcPT;
      string eMPwGaxSJw;
      string HApHofgOzt;
      string icxlqcnuIp;
      string uBnpSzJWSJ;
      string HjxCCNpIXO;
      string FfdUjBPdEc;
      if(oMKwYnBqlH == FAoiylkwwF){lBJTAGLzop = true;}
      else if(FAoiylkwwF == oMKwYnBqlH){EdUALSbIys = true;}
      if(PpwuUpCxBX == JEJEcpdEKx){WJwomzftid = true;}
      else if(JEJEcpdEKx == PpwuUpCxBX){uoPrDzHYbr = true;}
      if(qzmlqINKYT == MYTZjEDHzK){meWskPWSFQ = true;}
      else if(MYTZjEDHzK == qzmlqINKYT){FyEDFPHbYT = true;}
      if(tsEaFFebCN == OfQNultcPT){ifSpWFZcBw = true;}
      else if(OfQNultcPT == tsEaFFebCN){yPMzkCOkIc = true;}
      if(bXSRWpVdyJ == eMPwGaxSJw){BqThruinhk = true;}
      else if(eMPwGaxSJw == bXSRWpVdyJ){lcsHTmtCMN = true;}
      if(MeisYpZXEP == HApHofgOzt){VUtaoGdQhj = true;}
      else if(HApHofgOzt == MeisYpZXEP){BYTjuFZRuw = true;}
      if(apSRMVkUoP == icxlqcnuIp){issXGpqFSg = true;}
      else if(icxlqcnuIp == apSRMVkUoP){LAieuebPGB = true;}
      if(KZtmwSgUOA == uBnpSzJWSJ){YCslbwLoBp = true;}
      if(mjLOGPJLBP == HjxCCNpIXO){fikUuNkrAP = true;}
      if(eGWmmlEAEB == FfdUjBPdEc){bJuQMIxubB = true;}
      while(uBnpSzJWSJ == KZtmwSgUOA){kWPzGcFxiS = true;}
      while(HjxCCNpIXO == HjxCCNpIXO){UFOLSYwcDf = true;}
      while(FfdUjBPdEc == FfdUjBPdEc){cwoLQksOMn = true;}
      if(lBJTAGLzop == true){lBJTAGLzop = false;}
      if(WJwomzftid == true){WJwomzftid = false;}
      if(meWskPWSFQ == true){meWskPWSFQ = false;}
      if(ifSpWFZcBw == true){ifSpWFZcBw = false;}
      if(BqThruinhk == true){BqThruinhk = false;}
      if(VUtaoGdQhj == true){VUtaoGdQhj = false;}
      if(issXGpqFSg == true){issXGpqFSg = false;}
      if(YCslbwLoBp == true){YCslbwLoBp = false;}
      if(fikUuNkrAP == true){fikUuNkrAP = false;}
      if(bJuQMIxubB == true){bJuQMIxubB = false;}
      if(EdUALSbIys == true){EdUALSbIys = false;}
      if(uoPrDzHYbr == true){uoPrDzHYbr = false;}
      if(FyEDFPHbYT == true){FyEDFPHbYT = false;}
      if(yPMzkCOkIc == true){yPMzkCOkIc = false;}
      if(lcsHTmtCMN == true){lcsHTmtCMN = false;}
      if(BYTjuFZRuw == true){BYTjuFZRuw = false;}
      if(LAieuebPGB == true){LAieuebPGB = false;}
      if(kWPzGcFxiS == true){kWPzGcFxiS = false;}
      if(UFOLSYwcDf == true){UFOLSYwcDf = false;}
      if(cwoLQksOMn == true){cwoLQksOMn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KATZHPJOSA
{ 
  void lOXpNuiLWI()
  { 
      bool HmdLFdCLrj = false;
      bool jSHoQfGrPx = false;
      bool SQHtZaAUfz = false;
      bool ziXYiSZuKf = false;
      bool MYWECEuJyC = false;
      bool TkuwMpfile = false;
      bool dhfrkBuhGx = false;
      bool GLgjjstDrV = false;
      bool epVcfOnbMr = false;
      bool mpIfCesdSA = false;
      bool JNDAwIDLMS = false;
      bool wbqQzmLDMW = false;
      bool NSVNKQCAgE = false;
      bool AQkqLRmVgX = false;
      bool KbOswLzrgO = false;
      bool TpRwmpqooe = false;
      bool FCdHSepzEg = false;
      bool zoVnLkEbRz = false;
      bool QKTSkKznEV = false;
      bool ayfBRHyHZQ = false;
      string WmmblHKMpE;
      string mbldCkDPIb;
      string phRLFQBkoo;
      string aeCtoWKejg;
      string gfKHigAnrn;
      string WJjGYnVaVV;
      string FYWAcIYrnf;
      string ZXebuKWJcX;
      string PNsARQtuUA;
      string AiJOaIIJda;
      string HIzMOydILO;
      string QLyxFreVhM;
      string NdXmeqOQAl;
      string BMfBQHOflS;
      string mkjFinjLJi;
      string claRMdjLgW;
      string jNIYMEfwgx;
      string dzjOYbsREq;
      string GDHQJPkOnl;
      string WCzOiZcKse;
      if(WmmblHKMpE == HIzMOydILO){HmdLFdCLrj = true;}
      else if(HIzMOydILO == WmmblHKMpE){JNDAwIDLMS = true;}
      if(mbldCkDPIb == QLyxFreVhM){jSHoQfGrPx = true;}
      else if(QLyxFreVhM == mbldCkDPIb){wbqQzmLDMW = true;}
      if(phRLFQBkoo == NdXmeqOQAl){SQHtZaAUfz = true;}
      else if(NdXmeqOQAl == phRLFQBkoo){NSVNKQCAgE = true;}
      if(aeCtoWKejg == BMfBQHOflS){ziXYiSZuKf = true;}
      else if(BMfBQHOflS == aeCtoWKejg){AQkqLRmVgX = true;}
      if(gfKHigAnrn == mkjFinjLJi){MYWECEuJyC = true;}
      else if(mkjFinjLJi == gfKHigAnrn){KbOswLzrgO = true;}
      if(WJjGYnVaVV == claRMdjLgW){TkuwMpfile = true;}
      else if(claRMdjLgW == WJjGYnVaVV){TpRwmpqooe = true;}
      if(FYWAcIYrnf == jNIYMEfwgx){dhfrkBuhGx = true;}
      else if(jNIYMEfwgx == FYWAcIYrnf){FCdHSepzEg = true;}
      if(ZXebuKWJcX == dzjOYbsREq){GLgjjstDrV = true;}
      if(PNsARQtuUA == GDHQJPkOnl){epVcfOnbMr = true;}
      if(AiJOaIIJda == WCzOiZcKse){mpIfCesdSA = true;}
      while(dzjOYbsREq == ZXebuKWJcX){zoVnLkEbRz = true;}
      while(GDHQJPkOnl == GDHQJPkOnl){QKTSkKznEV = true;}
      while(WCzOiZcKse == WCzOiZcKse){ayfBRHyHZQ = true;}
      if(HmdLFdCLrj == true){HmdLFdCLrj = false;}
      if(jSHoQfGrPx == true){jSHoQfGrPx = false;}
      if(SQHtZaAUfz == true){SQHtZaAUfz = false;}
      if(ziXYiSZuKf == true){ziXYiSZuKf = false;}
      if(MYWECEuJyC == true){MYWECEuJyC = false;}
      if(TkuwMpfile == true){TkuwMpfile = false;}
      if(dhfrkBuhGx == true){dhfrkBuhGx = false;}
      if(GLgjjstDrV == true){GLgjjstDrV = false;}
      if(epVcfOnbMr == true){epVcfOnbMr = false;}
      if(mpIfCesdSA == true){mpIfCesdSA = false;}
      if(JNDAwIDLMS == true){JNDAwIDLMS = false;}
      if(wbqQzmLDMW == true){wbqQzmLDMW = false;}
      if(NSVNKQCAgE == true){NSVNKQCAgE = false;}
      if(AQkqLRmVgX == true){AQkqLRmVgX = false;}
      if(KbOswLzrgO == true){KbOswLzrgO = false;}
      if(TpRwmpqooe == true){TpRwmpqooe = false;}
      if(FCdHSepzEg == true){FCdHSepzEg = false;}
      if(zoVnLkEbRz == true){zoVnLkEbRz = false;}
      if(QKTSkKznEV == true){QKTSkKznEV = false;}
      if(ayfBRHyHZQ == true){ayfBRHyHZQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRVVXOSVEQ
{ 
  void NEHNokwPLe()
  { 
      bool ONMWCVCfpW = false;
      bool ZbUyxRcVmF = false;
      bool ezhrQOUHnW = false;
      bool RexkMTPkpw = false;
      bool mJzcMOBlFq = false;
      bool bJSfgOeTFn = false;
      bool AuqTEueikd = false;
      bool BrfpRUzEfC = false;
      bool MiBxtHLREx = false;
      bool oweCurSfYR = false;
      bool jSAbpjdbNL = false;
      bool OZnDbRttYw = false;
      bool jMdmnEMduZ = false;
      bool CTfNSshYGK = false;
      bool diEshOIbZd = false;
      bool yYGbhWoMmk = false;
      bool WzgmJusZjh = false;
      bool jUmOSAIjFZ = false;
      bool wkDRbdMEfu = false;
      bool DUlVmdCQjm = false;
      string bGaDqdlNmt;
      string SykwkSxHNG;
      string ArLkTCWGcV;
      string OgroBAoGeT;
      string VquQANXnql;
      string FAoiIjuojo;
      string HejRfkFwtk;
      string cqcsjJwtkF;
      string dhPqQNqJfR;
      string FAWpMqGdkP;
      string HbtFIOXuyz;
      string mAEdKYPsAR;
      string twQbfcUmfs;
      string DSJVyCnJhC;
      string puLgeEwrem;
      string aMcSUKLRYe;
      string skOEuTphfI;
      string kFKxbykixa;
      string gbHsRpopAm;
      string qWjDIFfGkL;
      if(bGaDqdlNmt == HbtFIOXuyz){ONMWCVCfpW = true;}
      else if(HbtFIOXuyz == bGaDqdlNmt){jSAbpjdbNL = true;}
      if(SykwkSxHNG == mAEdKYPsAR){ZbUyxRcVmF = true;}
      else if(mAEdKYPsAR == SykwkSxHNG){OZnDbRttYw = true;}
      if(ArLkTCWGcV == twQbfcUmfs){ezhrQOUHnW = true;}
      else if(twQbfcUmfs == ArLkTCWGcV){jMdmnEMduZ = true;}
      if(OgroBAoGeT == DSJVyCnJhC){RexkMTPkpw = true;}
      else if(DSJVyCnJhC == OgroBAoGeT){CTfNSshYGK = true;}
      if(VquQANXnql == puLgeEwrem){mJzcMOBlFq = true;}
      else if(puLgeEwrem == VquQANXnql){diEshOIbZd = true;}
      if(FAoiIjuojo == aMcSUKLRYe){bJSfgOeTFn = true;}
      else if(aMcSUKLRYe == FAoiIjuojo){yYGbhWoMmk = true;}
      if(HejRfkFwtk == skOEuTphfI){AuqTEueikd = true;}
      else if(skOEuTphfI == HejRfkFwtk){WzgmJusZjh = true;}
      if(cqcsjJwtkF == kFKxbykixa){BrfpRUzEfC = true;}
      if(dhPqQNqJfR == gbHsRpopAm){MiBxtHLREx = true;}
      if(FAWpMqGdkP == qWjDIFfGkL){oweCurSfYR = true;}
      while(kFKxbykixa == cqcsjJwtkF){jUmOSAIjFZ = true;}
      while(gbHsRpopAm == gbHsRpopAm){wkDRbdMEfu = true;}
      while(qWjDIFfGkL == qWjDIFfGkL){DUlVmdCQjm = true;}
      if(ONMWCVCfpW == true){ONMWCVCfpW = false;}
      if(ZbUyxRcVmF == true){ZbUyxRcVmF = false;}
      if(ezhrQOUHnW == true){ezhrQOUHnW = false;}
      if(RexkMTPkpw == true){RexkMTPkpw = false;}
      if(mJzcMOBlFq == true){mJzcMOBlFq = false;}
      if(bJSfgOeTFn == true){bJSfgOeTFn = false;}
      if(AuqTEueikd == true){AuqTEueikd = false;}
      if(BrfpRUzEfC == true){BrfpRUzEfC = false;}
      if(MiBxtHLREx == true){MiBxtHLREx = false;}
      if(oweCurSfYR == true){oweCurSfYR = false;}
      if(jSAbpjdbNL == true){jSAbpjdbNL = false;}
      if(OZnDbRttYw == true){OZnDbRttYw = false;}
      if(jMdmnEMduZ == true){jMdmnEMduZ = false;}
      if(CTfNSshYGK == true){CTfNSshYGK = false;}
      if(diEshOIbZd == true){diEshOIbZd = false;}
      if(yYGbhWoMmk == true){yYGbhWoMmk = false;}
      if(WzgmJusZjh == true){WzgmJusZjh = false;}
      if(jUmOSAIjFZ == true){jUmOSAIjFZ = false;}
      if(wkDRbdMEfu == true){wkDRbdMEfu = false;}
      if(DUlVmdCQjm == true){DUlVmdCQjm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBVMXTIATI
{ 
  void MJWdUnAjzU()
  { 
      bool eRLmxNxcay = false;
      bool PgBSxNmXQi = false;
      bool yzglNnPtrA = false;
      bool KuojuJLFUC = false;
      bool kQsLqrMUps = false;
      bool zKRqKfkYZJ = false;
      bool yDkanUrQWn = false;
      bool BgCNxgGUuU = false;
      bool atEzAAdxZO = false;
      bool XleKEhfRWW = false;
      bool AuxBqRHDtc = false;
      bool ZQdEhDzkZn = false;
      bool puqHPOCqJO = false;
      bool BnyYUfxCHi = false;
      bool raDwoHHZbA = false;
      bool itrhfEEolb = false;
      bool PPseakRFjC = false;
      bool GxcquPrtSH = false;
      bool HbPIfGwPrP = false;
      bool bHPfScgXUE = false;
      string GuVgJKSqiw;
      string NCclctDjqO;
      string gBqRzTCmXo;
      string YPdtXDGecQ;
      string fsLpHMoEpz;
      string lHiyUFDEgp;
      string HfTsWyYiNY;
      string nYHZhnoBKm;
      string dyxXDRgeZS;
      string ACxmIAZSSI;
      string mGpQKMAIPf;
      string PBssLJiupE;
      string QsIuYkbTRh;
      string NWhCAXHfNq;
      string RYPsCyJEaz;
      string QebNqsxtrZ;
      string jfpgRsTqsm;
      string BDgymrdPsZ;
      string bWsSQitTKG;
      string ZNmmGlhhaJ;
      if(GuVgJKSqiw == mGpQKMAIPf){eRLmxNxcay = true;}
      else if(mGpQKMAIPf == GuVgJKSqiw){AuxBqRHDtc = true;}
      if(NCclctDjqO == PBssLJiupE){PgBSxNmXQi = true;}
      else if(PBssLJiupE == NCclctDjqO){ZQdEhDzkZn = true;}
      if(gBqRzTCmXo == QsIuYkbTRh){yzglNnPtrA = true;}
      else if(QsIuYkbTRh == gBqRzTCmXo){puqHPOCqJO = true;}
      if(YPdtXDGecQ == NWhCAXHfNq){KuojuJLFUC = true;}
      else if(NWhCAXHfNq == YPdtXDGecQ){BnyYUfxCHi = true;}
      if(fsLpHMoEpz == RYPsCyJEaz){kQsLqrMUps = true;}
      else if(RYPsCyJEaz == fsLpHMoEpz){raDwoHHZbA = true;}
      if(lHiyUFDEgp == QebNqsxtrZ){zKRqKfkYZJ = true;}
      else if(QebNqsxtrZ == lHiyUFDEgp){itrhfEEolb = true;}
      if(HfTsWyYiNY == jfpgRsTqsm){yDkanUrQWn = true;}
      else if(jfpgRsTqsm == HfTsWyYiNY){PPseakRFjC = true;}
      if(nYHZhnoBKm == BDgymrdPsZ){BgCNxgGUuU = true;}
      if(dyxXDRgeZS == bWsSQitTKG){atEzAAdxZO = true;}
      if(ACxmIAZSSI == ZNmmGlhhaJ){XleKEhfRWW = true;}
      while(BDgymrdPsZ == nYHZhnoBKm){GxcquPrtSH = true;}
      while(bWsSQitTKG == bWsSQitTKG){HbPIfGwPrP = true;}
      while(ZNmmGlhhaJ == ZNmmGlhhaJ){bHPfScgXUE = true;}
      if(eRLmxNxcay == true){eRLmxNxcay = false;}
      if(PgBSxNmXQi == true){PgBSxNmXQi = false;}
      if(yzglNnPtrA == true){yzglNnPtrA = false;}
      if(KuojuJLFUC == true){KuojuJLFUC = false;}
      if(kQsLqrMUps == true){kQsLqrMUps = false;}
      if(zKRqKfkYZJ == true){zKRqKfkYZJ = false;}
      if(yDkanUrQWn == true){yDkanUrQWn = false;}
      if(BgCNxgGUuU == true){BgCNxgGUuU = false;}
      if(atEzAAdxZO == true){atEzAAdxZO = false;}
      if(XleKEhfRWW == true){XleKEhfRWW = false;}
      if(AuxBqRHDtc == true){AuxBqRHDtc = false;}
      if(ZQdEhDzkZn == true){ZQdEhDzkZn = false;}
      if(puqHPOCqJO == true){puqHPOCqJO = false;}
      if(BnyYUfxCHi == true){BnyYUfxCHi = false;}
      if(raDwoHHZbA == true){raDwoHHZbA = false;}
      if(itrhfEEolb == true){itrhfEEolb = false;}
      if(PPseakRFjC == true){PPseakRFjC = false;}
      if(GxcquPrtSH == true){GxcquPrtSH = false;}
      if(HbPIfGwPrP == true){HbPIfGwPrP = false;}
      if(bHPfScgXUE == true){bHPfScgXUE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTTNXTJJAM
{ 
  void JDUSsXWGmx()
  { 
      bool jNSDaMNtyz = false;
      bool lqehWcuCJg = false;
      bool OLMWtMJHrD = false;
      bool BPVlxQOYgA = false;
      bool PYUffPYoJj = false;
      bool YBYTxYAwJO = false;
      bool DGCuyVUskG = false;
      bool NVUIQpqgpd = false;
      bool nUxHezpCnX = false;
      bool PSOSxJWYgK = false;
      bool ueECWCgPCH = false;
      bool hTGfZiItQz = false;
      bool eSEMpuGBLH = false;
      bool SRAfiIQtkb = false;
      bool SZAgpwMisO = false;
      bool AbIgebaqMb = false;
      bool ueEtnQSZxQ = false;
      bool SNIngESXWs = false;
      bool hXIxHqISBG = false;
      bool hYhJfmVFrY = false;
      string eYYVgZOOQg;
      string cdYuNrfchA;
      string PdbjgsWuYO;
      string SekqBfYoQr;
      string gMeAXkbRtF;
      string qSCzqBwoon;
      string CToBOxsgtg;
      string TpLpTCybLw;
      string QFATXzblzz;
      string jiAcoMXdla;
      string ruXNkAGMeo;
      string DUcrWxTVcP;
      string UGgtxjoiAH;
      string eUokDVgmhX;
      string rPHKuPFHFr;
      string sBAVFkNdPB;
      string KXLXKieroB;
      string QfnFXFzWyh;
      string dhcINcTTfS;
      string HDWgMTEiAM;
      if(eYYVgZOOQg == ruXNkAGMeo){jNSDaMNtyz = true;}
      else if(ruXNkAGMeo == eYYVgZOOQg){ueECWCgPCH = true;}
      if(cdYuNrfchA == DUcrWxTVcP){lqehWcuCJg = true;}
      else if(DUcrWxTVcP == cdYuNrfchA){hTGfZiItQz = true;}
      if(PdbjgsWuYO == UGgtxjoiAH){OLMWtMJHrD = true;}
      else if(UGgtxjoiAH == PdbjgsWuYO){eSEMpuGBLH = true;}
      if(SekqBfYoQr == eUokDVgmhX){BPVlxQOYgA = true;}
      else if(eUokDVgmhX == SekqBfYoQr){SRAfiIQtkb = true;}
      if(gMeAXkbRtF == rPHKuPFHFr){PYUffPYoJj = true;}
      else if(rPHKuPFHFr == gMeAXkbRtF){SZAgpwMisO = true;}
      if(qSCzqBwoon == sBAVFkNdPB){YBYTxYAwJO = true;}
      else if(sBAVFkNdPB == qSCzqBwoon){AbIgebaqMb = true;}
      if(CToBOxsgtg == KXLXKieroB){DGCuyVUskG = true;}
      else if(KXLXKieroB == CToBOxsgtg){ueEtnQSZxQ = true;}
      if(TpLpTCybLw == QfnFXFzWyh){NVUIQpqgpd = true;}
      if(QFATXzblzz == dhcINcTTfS){nUxHezpCnX = true;}
      if(jiAcoMXdla == HDWgMTEiAM){PSOSxJWYgK = true;}
      while(QfnFXFzWyh == TpLpTCybLw){SNIngESXWs = true;}
      while(dhcINcTTfS == dhcINcTTfS){hXIxHqISBG = true;}
      while(HDWgMTEiAM == HDWgMTEiAM){hYhJfmVFrY = true;}
      if(jNSDaMNtyz == true){jNSDaMNtyz = false;}
      if(lqehWcuCJg == true){lqehWcuCJg = false;}
      if(OLMWtMJHrD == true){OLMWtMJHrD = false;}
      if(BPVlxQOYgA == true){BPVlxQOYgA = false;}
      if(PYUffPYoJj == true){PYUffPYoJj = false;}
      if(YBYTxYAwJO == true){YBYTxYAwJO = false;}
      if(DGCuyVUskG == true){DGCuyVUskG = false;}
      if(NVUIQpqgpd == true){NVUIQpqgpd = false;}
      if(nUxHezpCnX == true){nUxHezpCnX = false;}
      if(PSOSxJWYgK == true){PSOSxJWYgK = false;}
      if(ueECWCgPCH == true){ueECWCgPCH = false;}
      if(hTGfZiItQz == true){hTGfZiItQz = false;}
      if(eSEMpuGBLH == true){eSEMpuGBLH = false;}
      if(SRAfiIQtkb == true){SRAfiIQtkb = false;}
      if(SZAgpwMisO == true){SZAgpwMisO = false;}
      if(AbIgebaqMb == true){AbIgebaqMb = false;}
      if(ueEtnQSZxQ == true){ueEtnQSZxQ = false;}
      if(SNIngESXWs == true){SNIngESXWs = false;}
      if(hXIxHqISBG == true){hXIxHqISBG = false;}
      if(hYhJfmVFrY == true){hYhJfmVFrY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GQKGLXXWHX
{ 
  void eAMVuqgKGE()
  { 
      bool MbtQUflCnQ = false;
      bool gRaokzoSJR = false;
      bool dBZyGYoQPG = false;
      bool LULadxRzns = false;
      bool oBsoasctRE = false;
      bool qrrBVKCwKu = false;
      bool pVmgFMGzLn = false;
      bool gpePbbIjXN = false;
      bool wtyKPSbKES = false;
      bool uUorDTOMjO = false;
      bool ldidWANbZt = false;
      bool CRYxzuWcQl = false;
      bool jwtsrLBlMH = false;
      bool NwAIaSLUmO = false;
      bool FAjKPcwrsH = false;
      bool xluxepipkL = false;
      bool zaPRfGQPVg = false;
      bool iBpBgjLicP = false;
      bool PIsFKbADdj = false;
      bool iVjbOdjSeJ = false;
      string upFkfkDMSV;
      string hyShaarfZr;
      string GHigtMheUu;
      string CxonexIKaj;
      string ShbVkVRPwM;
      string GKYnAnGXqT;
      string CXqWSjJeCc;
      string SgFoZYeMwX;
      string tSiInrXAnq;
      string pjTGhtpEDA;
      string MmMSsYEjOb;
      string IsbSYioiia;
      string LIpKmhNyHe;
      string hZJuLHGPOP;
      string mnlLiwIBhy;
      string FGVboDwCfL;
      string LGbjshjfGQ;
      string cYTTnXWebp;
      string ZMQJZbEhGH;
      string KDjDDgLCSA;
      if(upFkfkDMSV == MmMSsYEjOb){MbtQUflCnQ = true;}
      else if(MmMSsYEjOb == upFkfkDMSV){ldidWANbZt = true;}
      if(hyShaarfZr == IsbSYioiia){gRaokzoSJR = true;}
      else if(IsbSYioiia == hyShaarfZr){CRYxzuWcQl = true;}
      if(GHigtMheUu == LIpKmhNyHe){dBZyGYoQPG = true;}
      else if(LIpKmhNyHe == GHigtMheUu){jwtsrLBlMH = true;}
      if(CxonexIKaj == hZJuLHGPOP){LULadxRzns = true;}
      else if(hZJuLHGPOP == CxonexIKaj){NwAIaSLUmO = true;}
      if(ShbVkVRPwM == mnlLiwIBhy){oBsoasctRE = true;}
      else if(mnlLiwIBhy == ShbVkVRPwM){FAjKPcwrsH = true;}
      if(GKYnAnGXqT == FGVboDwCfL){qrrBVKCwKu = true;}
      else if(FGVboDwCfL == GKYnAnGXqT){xluxepipkL = true;}
      if(CXqWSjJeCc == LGbjshjfGQ){pVmgFMGzLn = true;}
      else if(LGbjshjfGQ == CXqWSjJeCc){zaPRfGQPVg = true;}
      if(SgFoZYeMwX == cYTTnXWebp){gpePbbIjXN = true;}
      if(tSiInrXAnq == ZMQJZbEhGH){wtyKPSbKES = true;}
      if(pjTGhtpEDA == KDjDDgLCSA){uUorDTOMjO = true;}
      while(cYTTnXWebp == SgFoZYeMwX){iBpBgjLicP = true;}
      while(ZMQJZbEhGH == ZMQJZbEhGH){PIsFKbADdj = true;}
      while(KDjDDgLCSA == KDjDDgLCSA){iVjbOdjSeJ = true;}
      if(MbtQUflCnQ == true){MbtQUflCnQ = false;}
      if(gRaokzoSJR == true){gRaokzoSJR = false;}
      if(dBZyGYoQPG == true){dBZyGYoQPG = false;}
      if(LULadxRzns == true){LULadxRzns = false;}
      if(oBsoasctRE == true){oBsoasctRE = false;}
      if(qrrBVKCwKu == true){qrrBVKCwKu = false;}
      if(pVmgFMGzLn == true){pVmgFMGzLn = false;}
      if(gpePbbIjXN == true){gpePbbIjXN = false;}
      if(wtyKPSbKES == true){wtyKPSbKES = false;}
      if(uUorDTOMjO == true){uUorDTOMjO = false;}
      if(ldidWANbZt == true){ldidWANbZt = false;}
      if(CRYxzuWcQl == true){CRYxzuWcQl = false;}
      if(jwtsrLBlMH == true){jwtsrLBlMH = false;}
      if(NwAIaSLUmO == true){NwAIaSLUmO = false;}
      if(FAjKPcwrsH == true){FAjKPcwrsH = false;}
      if(xluxepipkL == true){xluxepipkL = false;}
      if(zaPRfGQPVg == true){zaPRfGQPVg = false;}
      if(iBpBgjLicP == true){iBpBgjLicP = false;}
      if(PIsFKbADdj == true){PIsFKbADdj = false;}
      if(iVjbOdjSeJ == true){iVjbOdjSeJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VOUYRLVTIN
{ 
  void FlYzOeMSEQ()
  { 
      bool aVVpYQEXcz = false;
      bool KzchTjcolj = false;
      bool zKkzypCdZl = false;
      bool DrMYzthEzt = false;
      bool WlkmcFtQhg = false;
      bool OVejuPkVrh = false;
      bool NaxquRmEiY = false;
      bool CYprMNYyWs = false;
      bool ulurXgNcdi = false;
      bool JMMQfuntqK = false;
      bool SpgIepfmWg = false;
      bool qlyymafETO = false;
      bool EJZAPoMYLQ = false;
      bool ZeGMaFEmNg = false;
      bool BZGwrWONdE = false;
      bool PiZcFIPgro = false;
      bool dHaFHLflXh = false;
      bool VsqlMeDdIs = false;
      bool ayuHBpEcGR = false;
      bool oXtXDtzAof = false;
      string mOkTFyqHjo;
      string siFalkdbbZ;
      string OMuCQlXtIc;
      string RETpOODJCu;
      string WAWYtLIhFb;
      string UmFdlZShCS;
      string ZwyGXoPPMW;
      string gTYgDOpWHF;
      string dpogHdzpDn;
      string wUGiVZBPAF;
      string urUhuBNYaX;
      string juaxoiHQzs;
      string pZLXaLMoKc;
      string MZVCJkUGlG;
      string PZOeEAtJtl;
      string RjQHPVfxHj;
      string nXNxLJZXnD;
      string NBerdPKgTZ;
      string QDuXKbJOmn;
      string EXyBRqLRTt;
      if(mOkTFyqHjo == urUhuBNYaX){aVVpYQEXcz = true;}
      else if(urUhuBNYaX == mOkTFyqHjo){SpgIepfmWg = true;}
      if(siFalkdbbZ == juaxoiHQzs){KzchTjcolj = true;}
      else if(juaxoiHQzs == siFalkdbbZ){qlyymafETO = true;}
      if(OMuCQlXtIc == pZLXaLMoKc){zKkzypCdZl = true;}
      else if(pZLXaLMoKc == OMuCQlXtIc){EJZAPoMYLQ = true;}
      if(RETpOODJCu == MZVCJkUGlG){DrMYzthEzt = true;}
      else if(MZVCJkUGlG == RETpOODJCu){ZeGMaFEmNg = true;}
      if(WAWYtLIhFb == PZOeEAtJtl){WlkmcFtQhg = true;}
      else if(PZOeEAtJtl == WAWYtLIhFb){BZGwrWONdE = true;}
      if(UmFdlZShCS == RjQHPVfxHj){OVejuPkVrh = true;}
      else if(RjQHPVfxHj == UmFdlZShCS){PiZcFIPgro = true;}
      if(ZwyGXoPPMW == nXNxLJZXnD){NaxquRmEiY = true;}
      else if(nXNxLJZXnD == ZwyGXoPPMW){dHaFHLflXh = true;}
      if(gTYgDOpWHF == NBerdPKgTZ){CYprMNYyWs = true;}
      if(dpogHdzpDn == QDuXKbJOmn){ulurXgNcdi = true;}
      if(wUGiVZBPAF == EXyBRqLRTt){JMMQfuntqK = true;}
      while(NBerdPKgTZ == gTYgDOpWHF){VsqlMeDdIs = true;}
      while(QDuXKbJOmn == QDuXKbJOmn){ayuHBpEcGR = true;}
      while(EXyBRqLRTt == EXyBRqLRTt){oXtXDtzAof = true;}
      if(aVVpYQEXcz == true){aVVpYQEXcz = false;}
      if(KzchTjcolj == true){KzchTjcolj = false;}
      if(zKkzypCdZl == true){zKkzypCdZl = false;}
      if(DrMYzthEzt == true){DrMYzthEzt = false;}
      if(WlkmcFtQhg == true){WlkmcFtQhg = false;}
      if(OVejuPkVrh == true){OVejuPkVrh = false;}
      if(NaxquRmEiY == true){NaxquRmEiY = false;}
      if(CYprMNYyWs == true){CYprMNYyWs = false;}
      if(ulurXgNcdi == true){ulurXgNcdi = false;}
      if(JMMQfuntqK == true){JMMQfuntqK = false;}
      if(SpgIepfmWg == true){SpgIepfmWg = false;}
      if(qlyymafETO == true){qlyymafETO = false;}
      if(EJZAPoMYLQ == true){EJZAPoMYLQ = false;}
      if(ZeGMaFEmNg == true){ZeGMaFEmNg = false;}
      if(BZGwrWONdE == true){BZGwrWONdE = false;}
      if(PiZcFIPgro == true){PiZcFIPgro = false;}
      if(dHaFHLflXh == true){dHaFHLflXh = false;}
      if(VsqlMeDdIs == true){VsqlMeDdIs = false;}
      if(ayuHBpEcGR == true){ayuHBpEcGR = false;}
      if(oXtXDtzAof == true){oXtXDtzAof = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJLNWWYHUY
{ 
  void oPIdJIkYJl()
  { 
      bool YGrdRRUJFO = false;
      bool lJJwiAGbxT = false;
      bool hzMERXeHGi = false;
      bool SmKzbapfcW = false;
      bool gKIDFTYsuW = false;
      bool mhAMzYtnLt = false;
      bool mNCWuyzKUI = false;
      bool KZzalXqIzy = false;
      bool ykMjukmyzC = false;
      bool gCUhiTHkHG = false;
      bool UOYlLNhZZb = false;
      bool hlnMwBARbK = false;
      bool LBLRbIFRqR = false;
      bool PFArcjMZYg = false;
      bool CMXXTuOHlh = false;
      bool SpJxuSDGKD = false;
      bool HPhILckuiL = false;
      bool oastHydmxg = false;
      bool syeJyZwDxK = false;
      bool gFPUZmdPLq = false;
      string tMtplMgVtj;
      string VEgqURpgtA;
      string xFgtWoyAIs;
      string pmjIgeYSxU;
      string cBYOiORQab;
      string ehPlaoezSx;
      string OgMAthUYJo;
      string rWiYXwfSKI;
      string WgYfOHXygr;
      string AZzAFunYUB;
      string srHljHypNe;
      string IMnKagHgkl;
      string JVrQnSXiTb;
      string IGxJOdZmuH;
      string JgjCjnknZY;
      string mGmiqXAqxQ;
      string jPWlVBOeww;
      string GUldcclpgA;
      string giJtnCTORq;
      string dipdWtKyfh;
      if(tMtplMgVtj == srHljHypNe){YGrdRRUJFO = true;}
      else if(srHljHypNe == tMtplMgVtj){UOYlLNhZZb = true;}
      if(VEgqURpgtA == IMnKagHgkl){lJJwiAGbxT = true;}
      else if(IMnKagHgkl == VEgqURpgtA){hlnMwBARbK = true;}
      if(xFgtWoyAIs == JVrQnSXiTb){hzMERXeHGi = true;}
      else if(JVrQnSXiTb == xFgtWoyAIs){LBLRbIFRqR = true;}
      if(pmjIgeYSxU == IGxJOdZmuH){SmKzbapfcW = true;}
      else if(IGxJOdZmuH == pmjIgeYSxU){PFArcjMZYg = true;}
      if(cBYOiORQab == JgjCjnknZY){gKIDFTYsuW = true;}
      else if(JgjCjnknZY == cBYOiORQab){CMXXTuOHlh = true;}
      if(ehPlaoezSx == mGmiqXAqxQ){mhAMzYtnLt = true;}
      else if(mGmiqXAqxQ == ehPlaoezSx){SpJxuSDGKD = true;}
      if(OgMAthUYJo == jPWlVBOeww){mNCWuyzKUI = true;}
      else if(jPWlVBOeww == OgMAthUYJo){HPhILckuiL = true;}
      if(rWiYXwfSKI == GUldcclpgA){KZzalXqIzy = true;}
      if(WgYfOHXygr == giJtnCTORq){ykMjukmyzC = true;}
      if(AZzAFunYUB == dipdWtKyfh){gCUhiTHkHG = true;}
      while(GUldcclpgA == rWiYXwfSKI){oastHydmxg = true;}
      while(giJtnCTORq == giJtnCTORq){syeJyZwDxK = true;}
      while(dipdWtKyfh == dipdWtKyfh){gFPUZmdPLq = true;}
      if(YGrdRRUJFO == true){YGrdRRUJFO = false;}
      if(lJJwiAGbxT == true){lJJwiAGbxT = false;}
      if(hzMERXeHGi == true){hzMERXeHGi = false;}
      if(SmKzbapfcW == true){SmKzbapfcW = false;}
      if(gKIDFTYsuW == true){gKIDFTYsuW = false;}
      if(mhAMzYtnLt == true){mhAMzYtnLt = false;}
      if(mNCWuyzKUI == true){mNCWuyzKUI = false;}
      if(KZzalXqIzy == true){KZzalXqIzy = false;}
      if(ykMjukmyzC == true){ykMjukmyzC = false;}
      if(gCUhiTHkHG == true){gCUhiTHkHG = false;}
      if(UOYlLNhZZb == true){UOYlLNhZZb = false;}
      if(hlnMwBARbK == true){hlnMwBARbK = false;}
      if(LBLRbIFRqR == true){LBLRbIFRqR = false;}
      if(PFArcjMZYg == true){PFArcjMZYg = false;}
      if(CMXXTuOHlh == true){CMXXTuOHlh = false;}
      if(SpJxuSDGKD == true){SpJxuSDGKD = false;}
      if(HPhILckuiL == true){HPhILckuiL = false;}
      if(oastHydmxg == true){oastHydmxg = false;}
      if(syeJyZwDxK == true){syeJyZwDxK = false;}
      if(gFPUZmdPLq == true){gFPUZmdPLq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCUCQLXBQG
{ 
  void LQzhDKbdSq()
  { 
      bool HbUWTguOJy = false;
      bool DiCDWUpDDw = false;
      bool ECZspfyJCi = false;
      bool cYwNCSyluc = false;
      bool UIhKfCoyfO = false;
      bool BbGyKFBagm = false;
      bool hkLaUemoAD = false;
      bool VEIaauTPMm = false;
      bool pAdmgARyCw = false;
      bool RWEHtjxHoB = false;
      bool PAxbsxSfXO = false;
      bool klOswhHXsU = false;
      bool MolElzzBgp = false;
      bool yLZLXpDBti = false;
      bool glZnKfIKKL = false;
      bool cYNTnZOrot = false;
      bool yRzgQZLCVG = false;
      bool eFdJnaOysG = false;
      bool pnpUNYyGXx = false;
      bool aKLAkOlsWk = false;
      string PTGDYBxOhc;
      string SuinSHaEwf;
      string kfMaoAixku;
      string FmOrbgpMKE;
      string uUxcuZPMKp;
      string SDQnAiHeOX;
      string RAdlWegpMk;
      string ROtrjPiifO;
      string kWmtbCWarr;
      string ZKxlltqKFP;
      string rYzYYEIXDk;
      string AXzzmuNiJU;
      string IGyULGQIFp;
      string XXcPWLWNVX;
      string syWHqBLxyq;
      string gIAkHlaeMS;
      string mASMMbtica;
      string XzNlbJiqcJ;
      string uSJOJPXrIj;
      string krBDjrfKtP;
      if(PTGDYBxOhc == rYzYYEIXDk){HbUWTguOJy = true;}
      else if(rYzYYEIXDk == PTGDYBxOhc){PAxbsxSfXO = true;}
      if(SuinSHaEwf == AXzzmuNiJU){DiCDWUpDDw = true;}
      else if(AXzzmuNiJU == SuinSHaEwf){klOswhHXsU = true;}
      if(kfMaoAixku == IGyULGQIFp){ECZspfyJCi = true;}
      else if(IGyULGQIFp == kfMaoAixku){MolElzzBgp = true;}
      if(FmOrbgpMKE == XXcPWLWNVX){cYwNCSyluc = true;}
      else if(XXcPWLWNVX == FmOrbgpMKE){yLZLXpDBti = true;}
      if(uUxcuZPMKp == syWHqBLxyq){UIhKfCoyfO = true;}
      else if(syWHqBLxyq == uUxcuZPMKp){glZnKfIKKL = true;}
      if(SDQnAiHeOX == gIAkHlaeMS){BbGyKFBagm = true;}
      else if(gIAkHlaeMS == SDQnAiHeOX){cYNTnZOrot = true;}
      if(RAdlWegpMk == mASMMbtica){hkLaUemoAD = true;}
      else if(mASMMbtica == RAdlWegpMk){yRzgQZLCVG = true;}
      if(ROtrjPiifO == XzNlbJiqcJ){VEIaauTPMm = true;}
      if(kWmtbCWarr == uSJOJPXrIj){pAdmgARyCw = true;}
      if(ZKxlltqKFP == krBDjrfKtP){RWEHtjxHoB = true;}
      while(XzNlbJiqcJ == ROtrjPiifO){eFdJnaOysG = true;}
      while(uSJOJPXrIj == uSJOJPXrIj){pnpUNYyGXx = true;}
      while(krBDjrfKtP == krBDjrfKtP){aKLAkOlsWk = true;}
      if(HbUWTguOJy == true){HbUWTguOJy = false;}
      if(DiCDWUpDDw == true){DiCDWUpDDw = false;}
      if(ECZspfyJCi == true){ECZspfyJCi = false;}
      if(cYwNCSyluc == true){cYwNCSyluc = false;}
      if(UIhKfCoyfO == true){UIhKfCoyfO = false;}
      if(BbGyKFBagm == true){BbGyKFBagm = false;}
      if(hkLaUemoAD == true){hkLaUemoAD = false;}
      if(VEIaauTPMm == true){VEIaauTPMm = false;}
      if(pAdmgARyCw == true){pAdmgARyCw = false;}
      if(RWEHtjxHoB == true){RWEHtjxHoB = false;}
      if(PAxbsxSfXO == true){PAxbsxSfXO = false;}
      if(klOswhHXsU == true){klOswhHXsU = false;}
      if(MolElzzBgp == true){MolElzzBgp = false;}
      if(yLZLXpDBti == true){yLZLXpDBti = false;}
      if(glZnKfIKKL == true){glZnKfIKKL = false;}
      if(cYNTnZOrot == true){cYNTnZOrot = false;}
      if(yRzgQZLCVG == true){yRzgQZLCVG = false;}
      if(eFdJnaOysG == true){eFdJnaOysG = false;}
      if(pnpUNYyGXx == true){pnpUNYyGXx = false;}
      if(aKLAkOlsWk == true){aKLAkOlsWk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTPCRPCQZK
{ 
  void OPSexTyHYg()
  { 
      bool joSNKhBXXw = false;
      bool EJunNkaHdG = false;
      bool FWSOBMGDwX = false;
      bool VajEtmLFUs = false;
      bool KTQjteNLsl = false;
      bool spnKgNWEMx = false;
      bool axbAZcZpsZ = false;
      bool ZVljukFiTW = false;
      bool ztKJdfmYXg = false;
      bool QGrWSNrQJQ = false;
      bool FWRTMWDDOu = false;
      bool HnkoxfmRVt = false;
      bool pARMIScOQh = false;
      bool snYCRccpwH = false;
      bool ciKcZcVCYl = false;
      bool ZZuPaEEFKt = false;
      bool snlgBSOhXU = false;
      bool DwUNQGoome = false;
      bool wZoeHTsIaM = false;
      bool XXfCNnwcbG = false;
      string fWkxIZeeay;
      string hyfSmxMEbe;
      string fOgYdQErPz;
      string MspPeBuJmS;
      string AkdGIUQyeJ;
      string fhJylQpLSr;
      string VmPbknHQml;
      string BCRJdtkZQJ;
      string AFMGSejqcO;
      string LjptwNVBVT;
      string MzKsIcQzUr;
      string fPuJqPZJJG;
      string EPmYZRMWMP;
      string YiEwwBtSyo;
      string NjWkhungDg;
      string nMrPPxMlSp;
      string QtmFSwLzNp;
      string VGKTrTsCpe;
      string ceSfaMqnfz;
      string nIAHXTxRRl;
      if(fWkxIZeeay == MzKsIcQzUr){joSNKhBXXw = true;}
      else if(MzKsIcQzUr == fWkxIZeeay){FWRTMWDDOu = true;}
      if(hyfSmxMEbe == fPuJqPZJJG){EJunNkaHdG = true;}
      else if(fPuJqPZJJG == hyfSmxMEbe){HnkoxfmRVt = true;}
      if(fOgYdQErPz == EPmYZRMWMP){FWSOBMGDwX = true;}
      else if(EPmYZRMWMP == fOgYdQErPz){pARMIScOQh = true;}
      if(MspPeBuJmS == YiEwwBtSyo){VajEtmLFUs = true;}
      else if(YiEwwBtSyo == MspPeBuJmS){snYCRccpwH = true;}
      if(AkdGIUQyeJ == NjWkhungDg){KTQjteNLsl = true;}
      else if(NjWkhungDg == AkdGIUQyeJ){ciKcZcVCYl = true;}
      if(fhJylQpLSr == nMrPPxMlSp){spnKgNWEMx = true;}
      else if(nMrPPxMlSp == fhJylQpLSr){ZZuPaEEFKt = true;}
      if(VmPbknHQml == QtmFSwLzNp){axbAZcZpsZ = true;}
      else if(QtmFSwLzNp == VmPbknHQml){snlgBSOhXU = true;}
      if(BCRJdtkZQJ == VGKTrTsCpe){ZVljukFiTW = true;}
      if(AFMGSejqcO == ceSfaMqnfz){ztKJdfmYXg = true;}
      if(LjptwNVBVT == nIAHXTxRRl){QGrWSNrQJQ = true;}
      while(VGKTrTsCpe == BCRJdtkZQJ){DwUNQGoome = true;}
      while(ceSfaMqnfz == ceSfaMqnfz){wZoeHTsIaM = true;}
      while(nIAHXTxRRl == nIAHXTxRRl){XXfCNnwcbG = true;}
      if(joSNKhBXXw == true){joSNKhBXXw = false;}
      if(EJunNkaHdG == true){EJunNkaHdG = false;}
      if(FWSOBMGDwX == true){FWSOBMGDwX = false;}
      if(VajEtmLFUs == true){VajEtmLFUs = false;}
      if(KTQjteNLsl == true){KTQjteNLsl = false;}
      if(spnKgNWEMx == true){spnKgNWEMx = false;}
      if(axbAZcZpsZ == true){axbAZcZpsZ = false;}
      if(ZVljukFiTW == true){ZVljukFiTW = false;}
      if(ztKJdfmYXg == true){ztKJdfmYXg = false;}
      if(QGrWSNrQJQ == true){QGrWSNrQJQ = false;}
      if(FWRTMWDDOu == true){FWRTMWDDOu = false;}
      if(HnkoxfmRVt == true){HnkoxfmRVt = false;}
      if(pARMIScOQh == true){pARMIScOQh = false;}
      if(snYCRccpwH == true){snYCRccpwH = false;}
      if(ciKcZcVCYl == true){ciKcZcVCYl = false;}
      if(ZZuPaEEFKt == true){ZZuPaEEFKt = false;}
      if(snlgBSOhXU == true){snlgBSOhXU = false;}
      if(DwUNQGoome == true){DwUNQGoome = false;}
      if(wZoeHTsIaM == true){wZoeHTsIaM = false;}
      if(XXfCNnwcbG == true){XXfCNnwcbG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVZXWZKFNX
{ 
  void nmpKkgzlHq()
  { 
      bool QsnLHQoZnI = false;
      bool ZsNWjfpPpj = false;
      bool NlXcQlhdxc = false;
      bool NzaBzVkJpz = false;
      bool DueDGXATGh = false;
      bool mCeJAeVKuV = false;
      bool iKbLtaSLWO = false;
      bool ugZpfRHTWs = false;
      bool kOXPpLTQBU = false;
      bool zaOTQrSSJe = false;
      bool EnwqmFboch = false;
      bool XCnBkUmMVi = false;
      bool HBKBOTSGYm = false;
      bool ynJqnwRfbj = false;
      bool idmTxxmMiw = false;
      bool FGxaXDducS = false;
      bool mVPoiirwMn = false;
      bool DGklAcOqER = false;
      bool gFWchrqiTk = false;
      bool RWDIxMOxjN = false;
      string zpODyqLZSh;
      string nlKFuPwjdq;
      string jeOXywSGhk;
      string SZzKGRHnLX;
      string uMCHReHmDA;
      string kAZJFTaqEC;
      string XErgPOmzyc;
      string IHYFwXcHFT;
      string nfDgzSApFm;
      string pPiIApTUrD;
      string rInZrdbTMg;
      string qTlkOrBKhx;
      string NxsLmrXPFF;
      string DHOBafqcoU;
      string pgcXwVdytI;
      string oJmuotOcmz;
      string GMNHdiFjJh;
      string AXUMGgUUOQ;
      string OZVxQsUSMg;
      string QOppOdSVtN;
      if(zpODyqLZSh == rInZrdbTMg){QsnLHQoZnI = true;}
      else if(rInZrdbTMg == zpODyqLZSh){EnwqmFboch = true;}
      if(nlKFuPwjdq == qTlkOrBKhx){ZsNWjfpPpj = true;}
      else if(qTlkOrBKhx == nlKFuPwjdq){XCnBkUmMVi = true;}
      if(jeOXywSGhk == NxsLmrXPFF){NlXcQlhdxc = true;}
      else if(NxsLmrXPFF == jeOXywSGhk){HBKBOTSGYm = true;}
      if(SZzKGRHnLX == DHOBafqcoU){NzaBzVkJpz = true;}
      else if(DHOBafqcoU == SZzKGRHnLX){ynJqnwRfbj = true;}
      if(uMCHReHmDA == pgcXwVdytI){DueDGXATGh = true;}
      else if(pgcXwVdytI == uMCHReHmDA){idmTxxmMiw = true;}
      if(kAZJFTaqEC == oJmuotOcmz){mCeJAeVKuV = true;}
      else if(oJmuotOcmz == kAZJFTaqEC){FGxaXDducS = true;}
      if(XErgPOmzyc == GMNHdiFjJh){iKbLtaSLWO = true;}
      else if(GMNHdiFjJh == XErgPOmzyc){mVPoiirwMn = true;}
      if(IHYFwXcHFT == AXUMGgUUOQ){ugZpfRHTWs = true;}
      if(nfDgzSApFm == OZVxQsUSMg){kOXPpLTQBU = true;}
      if(pPiIApTUrD == QOppOdSVtN){zaOTQrSSJe = true;}
      while(AXUMGgUUOQ == IHYFwXcHFT){DGklAcOqER = true;}
      while(OZVxQsUSMg == OZVxQsUSMg){gFWchrqiTk = true;}
      while(QOppOdSVtN == QOppOdSVtN){RWDIxMOxjN = true;}
      if(QsnLHQoZnI == true){QsnLHQoZnI = false;}
      if(ZsNWjfpPpj == true){ZsNWjfpPpj = false;}
      if(NlXcQlhdxc == true){NlXcQlhdxc = false;}
      if(NzaBzVkJpz == true){NzaBzVkJpz = false;}
      if(DueDGXATGh == true){DueDGXATGh = false;}
      if(mCeJAeVKuV == true){mCeJAeVKuV = false;}
      if(iKbLtaSLWO == true){iKbLtaSLWO = false;}
      if(ugZpfRHTWs == true){ugZpfRHTWs = false;}
      if(kOXPpLTQBU == true){kOXPpLTQBU = false;}
      if(zaOTQrSSJe == true){zaOTQrSSJe = false;}
      if(EnwqmFboch == true){EnwqmFboch = false;}
      if(XCnBkUmMVi == true){XCnBkUmMVi = false;}
      if(HBKBOTSGYm == true){HBKBOTSGYm = false;}
      if(ynJqnwRfbj == true){ynJqnwRfbj = false;}
      if(idmTxxmMiw == true){idmTxxmMiw = false;}
      if(FGxaXDducS == true){FGxaXDducS = false;}
      if(mVPoiirwMn == true){mVPoiirwMn = false;}
      if(DGklAcOqER == true){DGklAcOqER = false;}
      if(gFWchrqiTk == true){gFWchrqiTk = false;}
      if(RWDIxMOxjN == true){RWDIxMOxjN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIEHOLMHAP
{ 
  void lIGCcFWLHH()
  { 
      bool RpFnOmhYRP = false;
      bool kpIVXAxuks = false;
      bool EoABLNLVti = false;
      bool qSnUFsyqhu = false;
      bool CbrbkhLwwm = false;
      bool iJmASboEcA = false;
      bool bMdiYRBnPe = false;
      bool CGMpqbxYQc = false;
      bool COYHzgfnBd = false;
      bool DtNgToxJCS = false;
      bool gXfRkcxwIp = false;
      bool eQnAyMmWir = false;
      bool lMmlaHreVB = false;
      bool enVxudiHVW = false;
      bool iieKzmGNiH = false;
      bool BaaKgTkspd = false;
      bool kSaHLptpEU = false;
      bool ceBLIChbmn = false;
      bool AewOzDNLQb = false;
      bool soQrlPIXyI = false;
      string tZBtbUWkKB;
      string FgPKIfNVxF;
      string FmduOUYiTB;
      string iZmyyGjfLy;
      string xGsblEuhkT;
      string UqmbmHuFfG;
      string unQJSftRLB;
      string uhJyIzsCJJ;
      string ZqxzgqlLLq;
      string LdzFCIojJF;
      string KdVjYmgnTn;
      string NswWfEqQba;
      string shFUpRhEuz;
      string JIsDywVMas;
      string JxqXcRhcYy;
      string RYHiLbXAtG;
      string FcrTdFArXj;
      string idpiQwqhrX;
      string iEfxhkAKqV;
      string YUSTngEXsX;
      if(tZBtbUWkKB == KdVjYmgnTn){RpFnOmhYRP = true;}
      else if(KdVjYmgnTn == tZBtbUWkKB){gXfRkcxwIp = true;}
      if(FgPKIfNVxF == NswWfEqQba){kpIVXAxuks = true;}
      else if(NswWfEqQba == FgPKIfNVxF){eQnAyMmWir = true;}
      if(FmduOUYiTB == shFUpRhEuz){EoABLNLVti = true;}
      else if(shFUpRhEuz == FmduOUYiTB){lMmlaHreVB = true;}
      if(iZmyyGjfLy == JIsDywVMas){qSnUFsyqhu = true;}
      else if(JIsDywVMas == iZmyyGjfLy){enVxudiHVW = true;}
      if(xGsblEuhkT == JxqXcRhcYy){CbrbkhLwwm = true;}
      else if(JxqXcRhcYy == xGsblEuhkT){iieKzmGNiH = true;}
      if(UqmbmHuFfG == RYHiLbXAtG){iJmASboEcA = true;}
      else if(RYHiLbXAtG == UqmbmHuFfG){BaaKgTkspd = true;}
      if(unQJSftRLB == FcrTdFArXj){bMdiYRBnPe = true;}
      else if(FcrTdFArXj == unQJSftRLB){kSaHLptpEU = true;}
      if(uhJyIzsCJJ == idpiQwqhrX){CGMpqbxYQc = true;}
      if(ZqxzgqlLLq == iEfxhkAKqV){COYHzgfnBd = true;}
      if(LdzFCIojJF == YUSTngEXsX){DtNgToxJCS = true;}
      while(idpiQwqhrX == uhJyIzsCJJ){ceBLIChbmn = true;}
      while(iEfxhkAKqV == iEfxhkAKqV){AewOzDNLQb = true;}
      while(YUSTngEXsX == YUSTngEXsX){soQrlPIXyI = true;}
      if(RpFnOmhYRP == true){RpFnOmhYRP = false;}
      if(kpIVXAxuks == true){kpIVXAxuks = false;}
      if(EoABLNLVti == true){EoABLNLVti = false;}
      if(qSnUFsyqhu == true){qSnUFsyqhu = false;}
      if(CbrbkhLwwm == true){CbrbkhLwwm = false;}
      if(iJmASboEcA == true){iJmASboEcA = false;}
      if(bMdiYRBnPe == true){bMdiYRBnPe = false;}
      if(CGMpqbxYQc == true){CGMpqbxYQc = false;}
      if(COYHzgfnBd == true){COYHzgfnBd = false;}
      if(DtNgToxJCS == true){DtNgToxJCS = false;}
      if(gXfRkcxwIp == true){gXfRkcxwIp = false;}
      if(eQnAyMmWir == true){eQnAyMmWir = false;}
      if(lMmlaHreVB == true){lMmlaHreVB = false;}
      if(enVxudiHVW == true){enVxudiHVW = false;}
      if(iieKzmGNiH == true){iieKzmGNiH = false;}
      if(BaaKgTkspd == true){BaaKgTkspd = false;}
      if(kSaHLptpEU == true){kSaHLptpEU = false;}
      if(ceBLIChbmn == true){ceBLIChbmn = false;}
      if(AewOzDNLQb == true){AewOzDNLQb = false;}
      if(soQrlPIXyI == true){soQrlPIXyI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYVZFROPUY
{ 
  void XSRiwOyXLR()
  { 
      bool ZFWHolSeUH = false;
      bool rsceczPEbr = false;
      bool QxKeoeSIUt = false;
      bool VkxpjVxbgj = false;
      bool PDKUfyTRhb = false;
      bool gBPPrbuqSK = false;
      bool SJKZkHumtG = false;
      bool BnXqcNmozp = false;
      bool KAZsNTUhxH = false;
      bool ZFIWRFsjiY = false;
      bool CgWaZsdYle = false;
      bool oFrcASjRMR = false;
      bool lNplfueBZX = false;
      bool TDGamcdyST = false;
      bool owuRSUNfWz = false;
      bool UbWRloqkud = false;
      bool NcyOKkyQoW = false;
      bool nkyrboRXSL = false;
      bool hzeaCrfonx = false;
      bool lrDnGMxgGh = false;
      string CDGbhxKmAg;
      string bnbuMAQtuP;
      string cIuEzhgWSt;
      string aUIKPdrzKl;
      string poaFzSESjf;
      string hGXwhsICbA;
      string QnUFGGeQfh;
      string IRiIZngoEf;
      string dNmlMTwMcV;
      string VoWKUBTVys;
      string mmmBWPXOVt;
      string LSxwWDAhsm;
      string JSnJMTuXnX;
      string TLpLrpakOw;
      string wgphJCranR;
      string BlbLiUycoD;
      string UzayZAblDf;
      string bOTxqbcFzJ;
      string aUjVWhiebX;
      string qxwKbwGqIJ;
      if(CDGbhxKmAg == mmmBWPXOVt){ZFWHolSeUH = true;}
      else if(mmmBWPXOVt == CDGbhxKmAg){CgWaZsdYle = true;}
      if(bnbuMAQtuP == LSxwWDAhsm){rsceczPEbr = true;}
      else if(LSxwWDAhsm == bnbuMAQtuP){oFrcASjRMR = true;}
      if(cIuEzhgWSt == JSnJMTuXnX){QxKeoeSIUt = true;}
      else if(JSnJMTuXnX == cIuEzhgWSt){lNplfueBZX = true;}
      if(aUIKPdrzKl == TLpLrpakOw){VkxpjVxbgj = true;}
      else if(TLpLrpakOw == aUIKPdrzKl){TDGamcdyST = true;}
      if(poaFzSESjf == wgphJCranR){PDKUfyTRhb = true;}
      else if(wgphJCranR == poaFzSESjf){owuRSUNfWz = true;}
      if(hGXwhsICbA == BlbLiUycoD){gBPPrbuqSK = true;}
      else if(BlbLiUycoD == hGXwhsICbA){UbWRloqkud = true;}
      if(QnUFGGeQfh == UzayZAblDf){SJKZkHumtG = true;}
      else if(UzayZAblDf == QnUFGGeQfh){NcyOKkyQoW = true;}
      if(IRiIZngoEf == bOTxqbcFzJ){BnXqcNmozp = true;}
      if(dNmlMTwMcV == aUjVWhiebX){KAZsNTUhxH = true;}
      if(VoWKUBTVys == qxwKbwGqIJ){ZFIWRFsjiY = true;}
      while(bOTxqbcFzJ == IRiIZngoEf){nkyrboRXSL = true;}
      while(aUjVWhiebX == aUjVWhiebX){hzeaCrfonx = true;}
      while(qxwKbwGqIJ == qxwKbwGqIJ){lrDnGMxgGh = true;}
      if(ZFWHolSeUH == true){ZFWHolSeUH = false;}
      if(rsceczPEbr == true){rsceczPEbr = false;}
      if(QxKeoeSIUt == true){QxKeoeSIUt = false;}
      if(VkxpjVxbgj == true){VkxpjVxbgj = false;}
      if(PDKUfyTRhb == true){PDKUfyTRhb = false;}
      if(gBPPrbuqSK == true){gBPPrbuqSK = false;}
      if(SJKZkHumtG == true){SJKZkHumtG = false;}
      if(BnXqcNmozp == true){BnXqcNmozp = false;}
      if(KAZsNTUhxH == true){KAZsNTUhxH = false;}
      if(ZFIWRFsjiY == true){ZFIWRFsjiY = false;}
      if(CgWaZsdYle == true){CgWaZsdYle = false;}
      if(oFrcASjRMR == true){oFrcASjRMR = false;}
      if(lNplfueBZX == true){lNplfueBZX = false;}
      if(TDGamcdyST == true){TDGamcdyST = false;}
      if(owuRSUNfWz == true){owuRSUNfWz = false;}
      if(UbWRloqkud == true){UbWRloqkud = false;}
      if(NcyOKkyQoW == true){NcyOKkyQoW = false;}
      if(nkyrboRXSL == true){nkyrboRXSL = false;}
      if(hzeaCrfonx == true){hzeaCrfonx = false;}
      if(lrDnGMxgGh == true){lrDnGMxgGh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BGRDTLDCUF
{ 
  void GpqrQYnZzK()
  { 
      bool eRycaLQjjk = false;
      bool yYkSjqbPjP = false;
      bool MggomOxjmX = false;
      bool pHsgiUFRYg = false;
      bool HudmHBfhbL = false;
      bool eHYXjykIpM = false;
      bool NgxLtqfEjO = false;
      bool kKpCIQDthl = false;
      bool hPHasihUwk = false;
      bool iwaLTZyRrP = false;
      bool VbyMZUQWPT = false;
      bool tqaEeyYVSL = false;
      bool IKHyfoieih = false;
      bool SkBRPFQuAY = false;
      bool RLFcprVWfU = false;
      bool AbzgHKUzfk = false;
      bool klngAJpInZ = false;
      bool gdUtsxEdIn = false;
      bool TLyNgpkUKF = false;
      bool kROPmfXYcf = false;
      string nBfbniuwhJ;
      string aQAMKFZicZ;
      string GUZhYGEJEz;
      string NNwuGYwOPz;
      string dgyWMlPnGp;
      string FaCcxTayDh;
      string dkriwMUEFk;
      string IKSdwZVDVl;
      string pPDOslLSym;
      string xyLhUroPZz;
      string QLiUgtHYgX;
      string yXbQrNhcoK;
      string ACGSmJzkID;
      string jFcWUeghhy;
      string emlZoZWtpH;
      string KLaPyOEPgW;
      string uWPcmrtEuM;
      string fzupfNPfdN;
      string mEtAsXeNXG;
      string ZRBLDHWImx;
      if(nBfbniuwhJ == QLiUgtHYgX){eRycaLQjjk = true;}
      else if(QLiUgtHYgX == nBfbniuwhJ){VbyMZUQWPT = true;}
      if(aQAMKFZicZ == yXbQrNhcoK){yYkSjqbPjP = true;}
      else if(yXbQrNhcoK == aQAMKFZicZ){tqaEeyYVSL = true;}
      if(GUZhYGEJEz == ACGSmJzkID){MggomOxjmX = true;}
      else if(ACGSmJzkID == GUZhYGEJEz){IKHyfoieih = true;}
      if(NNwuGYwOPz == jFcWUeghhy){pHsgiUFRYg = true;}
      else if(jFcWUeghhy == NNwuGYwOPz){SkBRPFQuAY = true;}
      if(dgyWMlPnGp == emlZoZWtpH){HudmHBfhbL = true;}
      else if(emlZoZWtpH == dgyWMlPnGp){RLFcprVWfU = true;}
      if(FaCcxTayDh == KLaPyOEPgW){eHYXjykIpM = true;}
      else if(KLaPyOEPgW == FaCcxTayDh){AbzgHKUzfk = true;}
      if(dkriwMUEFk == uWPcmrtEuM){NgxLtqfEjO = true;}
      else if(uWPcmrtEuM == dkriwMUEFk){klngAJpInZ = true;}
      if(IKSdwZVDVl == fzupfNPfdN){kKpCIQDthl = true;}
      if(pPDOslLSym == mEtAsXeNXG){hPHasihUwk = true;}
      if(xyLhUroPZz == ZRBLDHWImx){iwaLTZyRrP = true;}
      while(fzupfNPfdN == IKSdwZVDVl){gdUtsxEdIn = true;}
      while(mEtAsXeNXG == mEtAsXeNXG){TLyNgpkUKF = true;}
      while(ZRBLDHWImx == ZRBLDHWImx){kROPmfXYcf = true;}
      if(eRycaLQjjk == true){eRycaLQjjk = false;}
      if(yYkSjqbPjP == true){yYkSjqbPjP = false;}
      if(MggomOxjmX == true){MggomOxjmX = false;}
      if(pHsgiUFRYg == true){pHsgiUFRYg = false;}
      if(HudmHBfhbL == true){HudmHBfhbL = false;}
      if(eHYXjykIpM == true){eHYXjykIpM = false;}
      if(NgxLtqfEjO == true){NgxLtqfEjO = false;}
      if(kKpCIQDthl == true){kKpCIQDthl = false;}
      if(hPHasihUwk == true){hPHasihUwk = false;}
      if(iwaLTZyRrP == true){iwaLTZyRrP = false;}
      if(VbyMZUQWPT == true){VbyMZUQWPT = false;}
      if(tqaEeyYVSL == true){tqaEeyYVSL = false;}
      if(IKHyfoieih == true){IKHyfoieih = false;}
      if(SkBRPFQuAY == true){SkBRPFQuAY = false;}
      if(RLFcprVWfU == true){RLFcprVWfU = false;}
      if(AbzgHKUzfk == true){AbzgHKUzfk = false;}
      if(klngAJpInZ == true){klngAJpInZ = false;}
      if(gdUtsxEdIn == true){gdUtsxEdIn = false;}
      if(TLyNgpkUKF == true){TLyNgpkUKF = false;}
      if(kROPmfXYcf == true){kROPmfXYcf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKGKPGPMDA
{ 
  void lnqopSuxCE()
  { 
      bool ItCzFVVkmC = false;
      bool kJPxglkBhi = false;
      bool OTcFReJKYo = false;
      bool QLlMAuFmWB = false;
      bool WAtWWmEPYW = false;
      bool xwobooRwgZ = false;
      bool MKLykZWCxk = false;
      bool fxefMOZFid = false;
      bool ZslBqUVKXL = false;
      bool dIFwoLnukw = false;
      bool QCSmpzQJPa = false;
      bool PLNDzSYJHQ = false;
      bool ELekHXriqA = false;
      bool ZdTmNXayLq = false;
      bool DLtwuRuCwW = false;
      bool mdnTrEWgeS = false;
      bool HhRPAlqZob = false;
      bool qZyPNrRiop = false;
      bool bolUMwoAtJ = false;
      bool AsTsiVseuJ = false;
      string hMalsmptgp;
      string OXruEEfaAc;
      string MWijqbhyRX;
      string fkQJSfeBwM;
      string bEOAlkcdAh;
      string zByUOLcpuQ;
      string FqbJJdGhbX;
      string ZednAHIiyF;
      string zDyjXemwuH;
      string DnFeGkcEpI;
      string etBbITWKTG;
      string DsroRBrqle;
      string qKmUTkYzgP;
      string dDrpaEBVbD;
      string HbbnDKwQMF;
      string rkSKQTHgHW;
      string uXdEczBBNN;
      string zWPhXOiyQJ;
      string oIlbWskgYH;
      string wUNFIiyWLE;
      if(hMalsmptgp == etBbITWKTG){ItCzFVVkmC = true;}
      else if(etBbITWKTG == hMalsmptgp){QCSmpzQJPa = true;}
      if(OXruEEfaAc == DsroRBrqle){kJPxglkBhi = true;}
      else if(DsroRBrqle == OXruEEfaAc){PLNDzSYJHQ = true;}
      if(MWijqbhyRX == qKmUTkYzgP){OTcFReJKYo = true;}
      else if(qKmUTkYzgP == MWijqbhyRX){ELekHXriqA = true;}
      if(fkQJSfeBwM == dDrpaEBVbD){QLlMAuFmWB = true;}
      else if(dDrpaEBVbD == fkQJSfeBwM){ZdTmNXayLq = true;}
      if(bEOAlkcdAh == HbbnDKwQMF){WAtWWmEPYW = true;}
      else if(HbbnDKwQMF == bEOAlkcdAh){DLtwuRuCwW = true;}
      if(zByUOLcpuQ == rkSKQTHgHW){xwobooRwgZ = true;}
      else if(rkSKQTHgHW == zByUOLcpuQ){mdnTrEWgeS = true;}
      if(FqbJJdGhbX == uXdEczBBNN){MKLykZWCxk = true;}
      else if(uXdEczBBNN == FqbJJdGhbX){HhRPAlqZob = true;}
      if(ZednAHIiyF == zWPhXOiyQJ){fxefMOZFid = true;}
      if(zDyjXemwuH == oIlbWskgYH){ZslBqUVKXL = true;}
      if(DnFeGkcEpI == wUNFIiyWLE){dIFwoLnukw = true;}
      while(zWPhXOiyQJ == ZednAHIiyF){qZyPNrRiop = true;}
      while(oIlbWskgYH == oIlbWskgYH){bolUMwoAtJ = true;}
      while(wUNFIiyWLE == wUNFIiyWLE){AsTsiVseuJ = true;}
      if(ItCzFVVkmC == true){ItCzFVVkmC = false;}
      if(kJPxglkBhi == true){kJPxglkBhi = false;}
      if(OTcFReJKYo == true){OTcFReJKYo = false;}
      if(QLlMAuFmWB == true){QLlMAuFmWB = false;}
      if(WAtWWmEPYW == true){WAtWWmEPYW = false;}
      if(xwobooRwgZ == true){xwobooRwgZ = false;}
      if(MKLykZWCxk == true){MKLykZWCxk = false;}
      if(fxefMOZFid == true){fxefMOZFid = false;}
      if(ZslBqUVKXL == true){ZslBqUVKXL = false;}
      if(dIFwoLnukw == true){dIFwoLnukw = false;}
      if(QCSmpzQJPa == true){QCSmpzQJPa = false;}
      if(PLNDzSYJHQ == true){PLNDzSYJHQ = false;}
      if(ELekHXriqA == true){ELekHXriqA = false;}
      if(ZdTmNXayLq == true){ZdTmNXayLq = false;}
      if(DLtwuRuCwW == true){DLtwuRuCwW = false;}
      if(mdnTrEWgeS == true){mdnTrEWgeS = false;}
      if(HhRPAlqZob == true){HhRPAlqZob = false;}
      if(qZyPNrRiop == true){qZyPNrRiop = false;}
      if(bolUMwoAtJ == true){bolUMwoAtJ = false;}
      if(AsTsiVseuJ == true){AsTsiVseuJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VOCJLQBOPI
{ 
  void oCxhjxkVoy()
  { 
      bool iUPQrHCDeg = false;
      bool ToNXwrCeLh = false;
      bool DQqiLbbpmR = false;
      bool yWOsKfkxai = false;
      bool cCGQQhbQZG = false;
      bool LiMEYRcfFQ = false;
      bool fLPMhxZTNP = false;
      bool HEDbFBKaSc = false;
      bool zKQgFPJKTr = false;
      bool CErJDQmshT = false;
      bool IHDJyHfjyX = false;
      bool GCNcRUuiHS = false;
      bool mPAUNCMsYo = false;
      bool ORsyTrHGhy = false;
      bool iYLukzqOri = false;
      bool UDlOfsGhuu = false;
      bool ulLJJoJOIY = false;
      bool MnAJiODEjN = false;
      bool LxBpTKedSa = false;
      bool kZKlDxNBlw = false;
      string BZsAQaswta;
      string PsUMMqGOrp;
      string thKyqLPPns;
      string EybJKymOCM;
      string aDTskEEwLM;
      string WrIgASPtIE;
      string KcHBWQRLBN;
      string EqMeOqNRMm;
      string HTEbWLptJr;
      string irGxByuSVU;
      string lrtxIefcSI;
      string ExhVxqYfdL;
      string ZWBJeLkOdP;
      string uturAOZHSr;
      string eMbAmkKjAJ;
      string YPoKtPpjRx;
      string sQyCNJCoUi;
      string QRMlfMuBWs;
      string AAOTqeFkxk;
      string XooVyOOYlc;
      if(BZsAQaswta == lrtxIefcSI){iUPQrHCDeg = true;}
      else if(lrtxIefcSI == BZsAQaswta){IHDJyHfjyX = true;}
      if(PsUMMqGOrp == ExhVxqYfdL){ToNXwrCeLh = true;}
      else if(ExhVxqYfdL == PsUMMqGOrp){GCNcRUuiHS = true;}
      if(thKyqLPPns == ZWBJeLkOdP){DQqiLbbpmR = true;}
      else if(ZWBJeLkOdP == thKyqLPPns){mPAUNCMsYo = true;}
      if(EybJKymOCM == uturAOZHSr){yWOsKfkxai = true;}
      else if(uturAOZHSr == EybJKymOCM){ORsyTrHGhy = true;}
      if(aDTskEEwLM == eMbAmkKjAJ){cCGQQhbQZG = true;}
      else if(eMbAmkKjAJ == aDTskEEwLM){iYLukzqOri = true;}
      if(WrIgASPtIE == YPoKtPpjRx){LiMEYRcfFQ = true;}
      else if(YPoKtPpjRx == WrIgASPtIE){UDlOfsGhuu = true;}
      if(KcHBWQRLBN == sQyCNJCoUi){fLPMhxZTNP = true;}
      else if(sQyCNJCoUi == KcHBWQRLBN){ulLJJoJOIY = true;}
      if(EqMeOqNRMm == QRMlfMuBWs){HEDbFBKaSc = true;}
      if(HTEbWLptJr == AAOTqeFkxk){zKQgFPJKTr = true;}
      if(irGxByuSVU == XooVyOOYlc){CErJDQmshT = true;}
      while(QRMlfMuBWs == EqMeOqNRMm){MnAJiODEjN = true;}
      while(AAOTqeFkxk == AAOTqeFkxk){LxBpTKedSa = true;}
      while(XooVyOOYlc == XooVyOOYlc){kZKlDxNBlw = true;}
      if(iUPQrHCDeg == true){iUPQrHCDeg = false;}
      if(ToNXwrCeLh == true){ToNXwrCeLh = false;}
      if(DQqiLbbpmR == true){DQqiLbbpmR = false;}
      if(yWOsKfkxai == true){yWOsKfkxai = false;}
      if(cCGQQhbQZG == true){cCGQQhbQZG = false;}
      if(LiMEYRcfFQ == true){LiMEYRcfFQ = false;}
      if(fLPMhxZTNP == true){fLPMhxZTNP = false;}
      if(HEDbFBKaSc == true){HEDbFBKaSc = false;}
      if(zKQgFPJKTr == true){zKQgFPJKTr = false;}
      if(CErJDQmshT == true){CErJDQmshT = false;}
      if(IHDJyHfjyX == true){IHDJyHfjyX = false;}
      if(GCNcRUuiHS == true){GCNcRUuiHS = false;}
      if(mPAUNCMsYo == true){mPAUNCMsYo = false;}
      if(ORsyTrHGhy == true){ORsyTrHGhy = false;}
      if(iYLukzqOri == true){iYLukzqOri = false;}
      if(UDlOfsGhuu == true){UDlOfsGhuu = false;}
      if(ulLJJoJOIY == true){ulLJJoJOIY = false;}
      if(MnAJiODEjN == true){MnAJiODEjN = false;}
      if(LxBpTKedSa == true){LxBpTKedSa = false;}
      if(kZKlDxNBlw == true){kZKlDxNBlw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCIQISYJFS
{ 
  void ppyRdWxTCw()
  { 
      bool TKFccElhLo = false;
      bool WgKVKWyXIS = false;
      bool iJqwdsYQEW = false;
      bool aIIFpqaOng = false;
      bool GdwAyCWsfb = false;
      bool DDrUKJSJyj = false;
      bool fVcnNOXEfT = false;
      bool ujjaMFMqxa = false;
      bool VejcTXPnuf = false;
      bool XRPDBjAIlj = false;
      bool dSNLfTSRHF = false;
      bool waMWNAkzUp = false;
      bool yjJzudUfYb = false;
      bool EEEMwDRYxz = false;
      bool EyfpjwErpA = false;
      bool yAmwltJNQC = false;
      bool zmrfAqWzaJ = false;
      bool iMCUkADSPy = false;
      bool YboYdEQIaC = false;
      bool tDItARFAor = false;
      string bfxQcRxgiR;
      string ZdpitHDgZp;
      string PuasENIpNS;
      string lfCrNCJFgf;
      string iXGgDOYSTE;
      string HWEgqgFDLP;
      string IGTPetaxUr;
      string yyzsHrntpp;
      string noWIKObVAg;
      string wFsRXbEpBJ;
      string mayaFIXLZz;
      string rKNUaSiKFQ;
      string SFxnusFhVe;
      string mxsgDNquDB;
      string qPuAnlqXpE;
      string rtkjqgdJfM;
      string DootMuRgRN;
      string anHDYCJwzJ;
      string BgqQlsLIoV;
      string ihPqyBaBns;
      if(bfxQcRxgiR == mayaFIXLZz){TKFccElhLo = true;}
      else if(mayaFIXLZz == bfxQcRxgiR){dSNLfTSRHF = true;}
      if(ZdpitHDgZp == rKNUaSiKFQ){WgKVKWyXIS = true;}
      else if(rKNUaSiKFQ == ZdpitHDgZp){waMWNAkzUp = true;}
      if(PuasENIpNS == SFxnusFhVe){iJqwdsYQEW = true;}
      else if(SFxnusFhVe == PuasENIpNS){yjJzudUfYb = true;}
      if(lfCrNCJFgf == mxsgDNquDB){aIIFpqaOng = true;}
      else if(mxsgDNquDB == lfCrNCJFgf){EEEMwDRYxz = true;}
      if(iXGgDOYSTE == qPuAnlqXpE){GdwAyCWsfb = true;}
      else if(qPuAnlqXpE == iXGgDOYSTE){EyfpjwErpA = true;}
      if(HWEgqgFDLP == rtkjqgdJfM){DDrUKJSJyj = true;}
      else if(rtkjqgdJfM == HWEgqgFDLP){yAmwltJNQC = true;}
      if(IGTPetaxUr == DootMuRgRN){fVcnNOXEfT = true;}
      else if(DootMuRgRN == IGTPetaxUr){zmrfAqWzaJ = true;}
      if(yyzsHrntpp == anHDYCJwzJ){ujjaMFMqxa = true;}
      if(noWIKObVAg == BgqQlsLIoV){VejcTXPnuf = true;}
      if(wFsRXbEpBJ == ihPqyBaBns){XRPDBjAIlj = true;}
      while(anHDYCJwzJ == yyzsHrntpp){iMCUkADSPy = true;}
      while(BgqQlsLIoV == BgqQlsLIoV){YboYdEQIaC = true;}
      while(ihPqyBaBns == ihPqyBaBns){tDItARFAor = true;}
      if(TKFccElhLo == true){TKFccElhLo = false;}
      if(WgKVKWyXIS == true){WgKVKWyXIS = false;}
      if(iJqwdsYQEW == true){iJqwdsYQEW = false;}
      if(aIIFpqaOng == true){aIIFpqaOng = false;}
      if(GdwAyCWsfb == true){GdwAyCWsfb = false;}
      if(DDrUKJSJyj == true){DDrUKJSJyj = false;}
      if(fVcnNOXEfT == true){fVcnNOXEfT = false;}
      if(ujjaMFMqxa == true){ujjaMFMqxa = false;}
      if(VejcTXPnuf == true){VejcTXPnuf = false;}
      if(XRPDBjAIlj == true){XRPDBjAIlj = false;}
      if(dSNLfTSRHF == true){dSNLfTSRHF = false;}
      if(waMWNAkzUp == true){waMWNAkzUp = false;}
      if(yjJzudUfYb == true){yjJzudUfYb = false;}
      if(EEEMwDRYxz == true){EEEMwDRYxz = false;}
      if(EyfpjwErpA == true){EyfpjwErpA = false;}
      if(yAmwltJNQC == true){yAmwltJNQC = false;}
      if(zmrfAqWzaJ == true){zmrfAqWzaJ = false;}
      if(iMCUkADSPy == true){iMCUkADSPy = false;}
      if(YboYdEQIaC == true){YboYdEQIaC = false;}
      if(tDItARFAor == true){tDItARFAor = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFKHPWOLFJ
{ 
  void IFrycLSbVK()
  { 
      bool TnCZpfUNzk = false;
      bool kAWFnIcJAP = false;
      bool sUqcCqMAbI = false;
      bool WuADrMoxSr = false;
      bool WDnMhSlOyQ = false;
      bool NdwNGzxYWz = false;
      bool SUkpOpASMa = false;
      bool TepHspfeuj = false;
      bool ExBKurylws = false;
      bool PPZTZCRyxr = false;
      bool RTCWxhmnUQ = false;
      bool SRdltUSatV = false;
      bool qNWSLDEWhq = false;
      bool XhgCSkudMN = false;
      bool FKRfaxknYE = false;
      bool iqDbAEwjLt = false;
      bool cQFcrjkaTJ = false;
      bool ZoNgQguqqN = false;
      bool RQxdHgeFCO = false;
      bool nLRSkoEnmq = false;
      string WgoWyklgsz;
      string BAkaRxXALH;
      string PJJAhpbXQy;
      string DOEbMzCjUk;
      string rplhwpACbQ;
      string fxrXiMXnnH;
      string JNQuuluINS;
      string tmeaOZWaEr;
      string oYuzSGWfsz;
      string aOwNadZqmK;
      string trnJVrRRJI;
      string oxjwSkSQbn;
      string OPONqfqRzj;
      string AfmsywjlcZ;
      string oFWkJdezup;
      string LIOyuddaRp;
      string AzRYHJJpxV;
      string AfmBzJrcDM;
      string BrWIXrQnyT;
      string SJTmZpmxcA;
      if(WgoWyklgsz == trnJVrRRJI){TnCZpfUNzk = true;}
      else if(trnJVrRRJI == WgoWyklgsz){RTCWxhmnUQ = true;}
      if(BAkaRxXALH == oxjwSkSQbn){kAWFnIcJAP = true;}
      else if(oxjwSkSQbn == BAkaRxXALH){SRdltUSatV = true;}
      if(PJJAhpbXQy == OPONqfqRzj){sUqcCqMAbI = true;}
      else if(OPONqfqRzj == PJJAhpbXQy){qNWSLDEWhq = true;}
      if(DOEbMzCjUk == AfmsywjlcZ){WuADrMoxSr = true;}
      else if(AfmsywjlcZ == DOEbMzCjUk){XhgCSkudMN = true;}
      if(rplhwpACbQ == oFWkJdezup){WDnMhSlOyQ = true;}
      else if(oFWkJdezup == rplhwpACbQ){FKRfaxknYE = true;}
      if(fxrXiMXnnH == LIOyuddaRp){NdwNGzxYWz = true;}
      else if(LIOyuddaRp == fxrXiMXnnH){iqDbAEwjLt = true;}
      if(JNQuuluINS == AzRYHJJpxV){SUkpOpASMa = true;}
      else if(AzRYHJJpxV == JNQuuluINS){cQFcrjkaTJ = true;}
      if(tmeaOZWaEr == AfmBzJrcDM){TepHspfeuj = true;}
      if(oYuzSGWfsz == BrWIXrQnyT){ExBKurylws = true;}
      if(aOwNadZqmK == SJTmZpmxcA){PPZTZCRyxr = true;}
      while(AfmBzJrcDM == tmeaOZWaEr){ZoNgQguqqN = true;}
      while(BrWIXrQnyT == BrWIXrQnyT){RQxdHgeFCO = true;}
      while(SJTmZpmxcA == SJTmZpmxcA){nLRSkoEnmq = true;}
      if(TnCZpfUNzk == true){TnCZpfUNzk = false;}
      if(kAWFnIcJAP == true){kAWFnIcJAP = false;}
      if(sUqcCqMAbI == true){sUqcCqMAbI = false;}
      if(WuADrMoxSr == true){WuADrMoxSr = false;}
      if(WDnMhSlOyQ == true){WDnMhSlOyQ = false;}
      if(NdwNGzxYWz == true){NdwNGzxYWz = false;}
      if(SUkpOpASMa == true){SUkpOpASMa = false;}
      if(TepHspfeuj == true){TepHspfeuj = false;}
      if(ExBKurylws == true){ExBKurylws = false;}
      if(PPZTZCRyxr == true){PPZTZCRyxr = false;}
      if(RTCWxhmnUQ == true){RTCWxhmnUQ = false;}
      if(SRdltUSatV == true){SRdltUSatV = false;}
      if(qNWSLDEWhq == true){qNWSLDEWhq = false;}
      if(XhgCSkudMN == true){XhgCSkudMN = false;}
      if(FKRfaxknYE == true){FKRfaxknYE = false;}
      if(iqDbAEwjLt == true){iqDbAEwjLt = false;}
      if(cQFcrjkaTJ == true){cQFcrjkaTJ = false;}
      if(ZoNgQguqqN == true){ZoNgQguqqN = false;}
      if(RQxdHgeFCO == true){RQxdHgeFCO = false;}
      if(nLRSkoEnmq == true){nLRSkoEnmq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZUVYTQWRW
{ 
  void FFaILBQQNb()
  { 
      bool cNruDuKSsr = false;
      bool NcQJkyMSnh = false;
      bool FVXHIREzKQ = false;
      bool jnQQoBDukh = false;
      bool SxPyMuilue = false;
      bool ATdqJGojll = false;
      bool pLHcIZLzUj = false;
      bool uQgFOIGYuN = false;
      bool iSEfQPJYHh = false;
      bool LTIyrHolpl = false;
      bool iiRKjilXbB = false;
      bool AQnYDXHbMr = false;
      bool PmrlYaIhNH = false;
      bool STiJezBsug = false;
      bool ckwGhueiuT = false;
      bool AMYxWuqelI = false;
      bool ZEKUhfgetE = false;
      bool WNfePdplEc = false;
      bool wYmsHGtkli = false;
      bool HVHmHYaaXB = false;
      string BDElSaVFtE;
      string qjICaFXRnJ;
      string QRttwPIYPn;
      string YQNSLeLuBy;
      string QsZwHkgCyn;
      string wlFjDiJKoD;
      string RxoFfaWoqw;
      string tcQorXqxmK;
      string hGZbrlKcPb;
      string UAFxfSDUQf;
      string OrLCtSVQqe;
      string rMWdVLXNNs;
      string QsZPasXSJY;
      string TWgHwouWhY;
      string QtkjjIdabU;
      string upGWPVRubB;
      string uDHSLUfPhf;
      string QAfncWHoeR;
      string PwpnddPJqZ;
      string XzufdMlSYO;
      if(BDElSaVFtE == OrLCtSVQqe){cNruDuKSsr = true;}
      else if(OrLCtSVQqe == BDElSaVFtE){iiRKjilXbB = true;}
      if(qjICaFXRnJ == rMWdVLXNNs){NcQJkyMSnh = true;}
      else if(rMWdVLXNNs == qjICaFXRnJ){AQnYDXHbMr = true;}
      if(QRttwPIYPn == QsZPasXSJY){FVXHIREzKQ = true;}
      else if(QsZPasXSJY == QRttwPIYPn){PmrlYaIhNH = true;}
      if(YQNSLeLuBy == TWgHwouWhY){jnQQoBDukh = true;}
      else if(TWgHwouWhY == YQNSLeLuBy){STiJezBsug = true;}
      if(QsZwHkgCyn == QtkjjIdabU){SxPyMuilue = true;}
      else if(QtkjjIdabU == QsZwHkgCyn){ckwGhueiuT = true;}
      if(wlFjDiJKoD == upGWPVRubB){ATdqJGojll = true;}
      else if(upGWPVRubB == wlFjDiJKoD){AMYxWuqelI = true;}
      if(RxoFfaWoqw == uDHSLUfPhf){pLHcIZLzUj = true;}
      else if(uDHSLUfPhf == RxoFfaWoqw){ZEKUhfgetE = true;}
      if(tcQorXqxmK == QAfncWHoeR){uQgFOIGYuN = true;}
      if(hGZbrlKcPb == PwpnddPJqZ){iSEfQPJYHh = true;}
      if(UAFxfSDUQf == XzufdMlSYO){LTIyrHolpl = true;}
      while(QAfncWHoeR == tcQorXqxmK){WNfePdplEc = true;}
      while(PwpnddPJqZ == PwpnddPJqZ){wYmsHGtkli = true;}
      while(XzufdMlSYO == XzufdMlSYO){HVHmHYaaXB = true;}
      if(cNruDuKSsr == true){cNruDuKSsr = false;}
      if(NcQJkyMSnh == true){NcQJkyMSnh = false;}
      if(FVXHIREzKQ == true){FVXHIREzKQ = false;}
      if(jnQQoBDukh == true){jnQQoBDukh = false;}
      if(SxPyMuilue == true){SxPyMuilue = false;}
      if(ATdqJGojll == true){ATdqJGojll = false;}
      if(pLHcIZLzUj == true){pLHcIZLzUj = false;}
      if(uQgFOIGYuN == true){uQgFOIGYuN = false;}
      if(iSEfQPJYHh == true){iSEfQPJYHh = false;}
      if(LTIyrHolpl == true){LTIyrHolpl = false;}
      if(iiRKjilXbB == true){iiRKjilXbB = false;}
      if(AQnYDXHbMr == true){AQnYDXHbMr = false;}
      if(PmrlYaIhNH == true){PmrlYaIhNH = false;}
      if(STiJezBsug == true){STiJezBsug = false;}
      if(ckwGhueiuT == true){ckwGhueiuT = false;}
      if(AMYxWuqelI == true){AMYxWuqelI = false;}
      if(ZEKUhfgetE == true){ZEKUhfgetE = false;}
      if(WNfePdplEc == true){WNfePdplEc = false;}
      if(wYmsHGtkli == true){wYmsHGtkli = false;}
      if(HVHmHYaaXB == true){HVHmHYaaXB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWGYYOYQPH
{ 
  void NCtCgWBnZZ()
  { 
      bool EDAMxTSrTM = false;
      bool TXEqByaWss = false;
      bool SQTewyyndl = false;
      bool knxgyoWNbp = false;
      bool jzelwdzrZs = false;
      bool SHByymiVQz = false;
      bool UdNgafZXrM = false;
      bool aNuCISlhhR = false;
      bool yGOjSclziK = false;
      bool FBxbUGlxKP = false;
      bool EbzMSFMyoe = false;
      bool BBmyBOPcOy = false;
      bool tangHZQShC = false;
      bool gnWSNWGBRM = false;
      bool QmJDJDNyaF = false;
      bool pIiMVdmRFs = false;
      bool osQlyMdUkd = false;
      bool INLBhHQkXD = false;
      bool LRrbLXFKxi = false;
      bool inuYXWWXFx = false;
      string bIHtTkQmTp;
      string DmMrdqGAqk;
      string mAROdAnNWb;
      string dIuKVYJbqG;
      string OiroQasBUq;
      string VuHjmaprQT;
      string wDPrLtqCWE;
      string geIjWEHbyC;
      string GmreFiALXu;
      string hQKXJLSAcW;
      string iqePJqlXNi;
      string SOtOMJKklc;
      string sfdaWPTkZK;
      string kHyaSOHcUO;
      string wcxocTWwKA;
      string BhOAcCMDst;
      string WBxCxLPSuy;
      string CgPWgQioyC;
      string sXZZJDryyQ;
      string BEiartetrR;
      if(bIHtTkQmTp == iqePJqlXNi){EDAMxTSrTM = true;}
      else if(iqePJqlXNi == bIHtTkQmTp){EbzMSFMyoe = true;}
      if(DmMrdqGAqk == SOtOMJKklc){TXEqByaWss = true;}
      else if(SOtOMJKklc == DmMrdqGAqk){BBmyBOPcOy = true;}
      if(mAROdAnNWb == sfdaWPTkZK){SQTewyyndl = true;}
      else if(sfdaWPTkZK == mAROdAnNWb){tangHZQShC = true;}
      if(dIuKVYJbqG == kHyaSOHcUO){knxgyoWNbp = true;}
      else if(kHyaSOHcUO == dIuKVYJbqG){gnWSNWGBRM = true;}
      if(OiroQasBUq == wcxocTWwKA){jzelwdzrZs = true;}
      else if(wcxocTWwKA == OiroQasBUq){QmJDJDNyaF = true;}
      if(VuHjmaprQT == BhOAcCMDst){SHByymiVQz = true;}
      else if(BhOAcCMDst == VuHjmaprQT){pIiMVdmRFs = true;}
      if(wDPrLtqCWE == WBxCxLPSuy){UdNgafZXrM = true;}
      else if(WBxCxLPSuy == wDPrLtqCWE){osQlyMdUkd = true;}
      if(geIjWEHbyC == CgPWgQioyC){aNuCISlhhR = true;}
      if(GmreFiALXu == sXZZJDryyQ){yGOjSclziK = true;}
      if(hQKXJLSAcW == BEiartetrR){FBxbUGlxKP = true;}
      while(CgPWgQioyC == geIjWEHbyC){INLBhHQkXD = true;}
      while(sXZZJDryyQ == sXZZJDryyQ){LRrbLXFKxi = true;}
      while(BEiartetrR == BEiartetrR){inuYXWWXFx = true;}
      if(EDAMxTSrTM == true){EDAMxTSrTM = false;}
      if(TXEqByaWss == true){TXEqByaWss = false;}
      if(SQTewyyndl == true){SQTewyyndl = false;}
      if(knxgyoWNbp == true){knxgyoWNbp = false;}
      if(jzelwdzrZs == true){jzelwdzrZs = false;}
      if(SHByymiVQz == true){SHByymiVQz = false;}
      if(UdNgafZXrM == true){UdNgafZXrM = false;}
      if(aNuCISlhhR == true){aNuCISlhhR = false;}
      if(yGOjSclziK == true){yGOjSclziK = false;}
      if(FBxbUGlxKP == true){FBxbUGlxKP = false;}
      if(EbzMSFMyoe == true){EbzMSFMyoe = false;}
      if(BBmyBOPcOy == true){BBmyBOPcOy = false;}
      if(tangHZQShC == true){tangHZQShC = false;}
      if(gnWSNWGBRM == true){gnWSNWGBRM = false;}
      if(QmJDJDNyaF == true){QmJDJDNyaF = false;}
      if(pIiMVdmRFs == true){pIiMVdmRFs = false;}
      if(osQlyMdUkd == true){osQlyMdUkd = false;}
      if(INLBhHQkXD == true){INLBhHQkXD = false;}
      if(LRrbLXFKxi == true){LRrbLXFKxi = false;}
      if(inuYXWWXFx == true){inuYXWWXFx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYESFZGNAJ
{ 
  void sEUwRoSTtw()
  { 
      bool TtiOYVFryH = false;
      bool fOijjdPqMC = false;
      bool pnsszktoED = false;
      bool cJGNgpezwn = false;
      bool qBVxQnGhPJ = false;
      bool iiWmReBpOn = false;
      bool bPmteVIVCs = false;
      bool zPtYLoSucK = false;
      bool eLZtTsmTwB = false;
      bool ookILaNaSu = false;
      bool fjfVKSoybc = false;
      bool LGMDIPorZk = false;
      bool hoZAEKekMj = false;
      bool arbhetfDjB = false;
      bool EoqSpibgAu = false;
      bool kVAhMqKeRA = false;
      bool nEkrBTdeYN = false;
      bool jlIYfsxGKU = false;
      bool hykQyFqtUn = false;
      bool iAkiNAEzRV = false;
      string miGxwhshCb;
      string FudWVXOaxT;
      string hkCaqTyNDP;
      string KtZQFllqLG;
      string dkxzKuIjwj;
      string DXZEmBfeGc;
      string jfelRKVNQi;
      string kXOqpxnCQu;
      string KNQTMlUUdE;
      string FHjiVxFKgA;
      string ZuSNyfJhOo;
      string MdOLRVPKZf;
      string oAjMcdmeVr;
      string qdVPVOuCUg;
      string clGnqbrYRz;
      string hukBKZLFkU;
      string rdMWyiIyoD;
      string aMosCCtwVA;
      string kONVJwsTFw;
      string DoRAnzZjoH;
      if(miGxwhshCb == ZuSNyfJhOo){TtiOYVFryH = true;}
      else if(ZuSNyfJhOo == miGxwhshCb){fjfVKSoybc = true;}
      if(FudWVXOaxT == MdOLRVPKZf){fOijjdPqMC = true;}
      else if(MdOLRVPKZf == FudWVXOaxT){LGMDIPorZk = true;}
      if(hkCaqTyNDP == oAjMcdmeVr){pnsszktoED = true;}
      else if(oAjMcdmeVr == hkCaqTyNDP){hoZAEKekMj = true;}
      if(KtZQFllqLG == qdVPVOuCUg){cJGNgpezwn = true;}
      else if(qdVPVOuCUg == KtZQFllqLG){arbhetfDjB = true;}
      if(dkxzKuIjwj == clGnqbrYRz){qBVxQnGhPJ = true;}
      else if(clGnqbrYRz == dkxzKuIjwj){EoqSpibgAu = true;}
      if(DXZEmBfeGc == hukBKZLFkU){iiWmReBpOn = true;}
      else if(hukBKZLFkU == DXZEmBfeGc){kVAhMqKeRA = true;}
      if(jfelRKVNQi == rdMWyiIyoD){bPmteVIVCs = true;}
      else if(rdMWyiIyoD == jfelRKVNQi){nEkrBTdeYN = true;}
      if(kXOqpxnCQu == aMosCCtwVA){zPtYLoSucK = true;}
      if(KNQTMlUUdE == kONVJwsTFw){eLZtTsmTwB = true;}
      if(FHjiVxFKgA == DoRAnzZjoH){ookILaNaSu = true;}
      while(aMosCCtwVA == kXOqpxnCQu){jlIYfsxGKU = true;}
      while(kONVJwsTFw == kONVJwsTFw){hykQyFqtUn = true;}
      while(DoRAnzZjoH == DoRAnzZjoH){iAkiNAEzRV = true;}
      if(TtiOYVFryH == true){TtiOYVFryH = false;}
      if(fOijjdPqMC == true){fOijjdPqMC = false;}
      if(pnsszktoED == true){pnsszktoED = false;}
      if(cJGNgpezwn == true){cJGNgpezwn = false;}
      if(qBVxQnGhPJ == true){qBVxQnGhPJ = false;}
      if(iiWmReBpOn == true){iiWmReBpOn = false;}
      if(bPmteVIVCs == true){bPmteVIVCs = false;}
      if(zPtYLoSucK == true){zPtYLoSucK = false;}
      if(eLZtTsmTwB == true){eLZtTsmTwB = false;}
      if(ookILaNaSu == true){ookILaNaSu = false;}
      if(fjfVKSoybc == true){fjfVKSoybc = false;}
      if(LGMDIPorZk == true){LGMDIPorZk = false;}
      if(hoZAEKekMj == true){hoZAEKekMj = false;}
      if(arbhetfDjB == true){arbhetfDjB = false;}
      if(EoqSpibgAu == true){EoqSpibgAu = false;}
      if(kVAhMqKeRA == true){kVAhMqKeRA = false;}
      if(nEkrBTdeYN == true){nEkrBTdeYN = false;}
      if(jlIYfsxGKU == true){jlIYfsxGKU = false;}
      if(hykQyFqtUn == true){hykQyFqtUn = false;}
      if(iAkiNAEzRV == true){iAkiNAEzRV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YNWFHPZBDP
{ 
  void YcsZxrrBMI()
  { 
      bool szxdMMrUKV = false;
      bool NlLctrRTZa = false;
      bool iUbIpHtIBL = false;
      bool zAWEMdMPnP = false;
      bool RHdDoXkMHk = false;
      bool qPVTTYXnnE = false;
      bool RiSyVMPHQQ = false;
      bool eCfKIapXTR = false;
      bool WhBQUieCkm = false;
      bool FYaiyioegb = false;
      bool IdwpFojLLs = false;
      bool hzUWhjgBdm = false;
      bool hMWcKGawMZ = false;
      bool lLqqJrkLLf = false;
      bool zSqrEFEEBN = false;
      bool BmBtsuHSey = false;
      bool NnzkGWIcMo = false;
      bool yVoxnPVeYF = false;
      bool BVuyYyJwxO = false;
      bool kSfMRKTFkg = false;
      string sZqucHYroA;
      string MLHGqmfqaO;
      string uPFpAxayha;
      string GildgBedZU;
      string gwaPUffRhI;
      string XBrKycTAtf;
      string fZJOtcYcZp;
      string HCRGgzopVU;
      string QJQZCEpbeD;
      string geisnGlMVq;
      string GCqrAVjlcy;
      string ndeZOWJiLo;
      string mwyWIcSXRZ;
      string NcUdNORYYf;
      string UDzfODAIdR;
      string xCAfEKEUiX;
      string CLTCkLJALA;
      string FkKeUixRIF;
      string cJsAcKboYD;
      string KxpBdIjwuD;
      if(sZqucHYroA == GCqrAVjlcy){szxdMMrUKV = true;}
      else if(GCqrAVjlcy == sZqucHYroA){IdwpFojLLs = true;}
      if(MLHGqmfqaO == ndeZOWJiLo){NlLctrRTZa = true;}
      else if(ndeZOWJiLo == MLHGqmfqaO){hzUWhjgBdm = true;}
      if(uPFpAxayha == mwyWIcSXRZ){iUbIpHtIBL = true;}
      else if(mwyWIcSXRZ == uPFpAxayha){hMWcKGawMZ = true;}
      if(GildgBedZU == NcUdNORYYf){zAWEMdMPnP = true;}
      else if(NcUdNORYYf == GildgBedZU){lLqqJrkLLf = true;}
      if(gwaPUffRhI == UDzfODAIdR){RHdDoXkMHk = true;}
      else if(UDzfODAIdR == gwaPUffRhI){zSqrEFEEBN = true;}
      if(XBrKycTAtf == xCAfEKEUiX){qPVTTYXnnE = true;}
      else if(xCAfEKEUiX == XBrKycTAtf){BmBtsuHSey = true;}
      if(fZJOtcYcZp == CLTCkLJALA){RiSyVMPHQQ = true;}
      else if(CLTCkLJALA == fZJOtcYcZp){NnzkGWIcMo = true;}
      if(HCRGgzopVU == FkKeUixRIF){eCfKIapXTR = true;}
      if(QJQZCEpbeD == cJsAcKboYD){WhBQUieCkm = true;}
      if(geisnGlMVq == KxpBdIjwuD){FYaiyioegb = true;}
      while(FkKeUixRIF == HCRGgzopVU){yVoxnPVeYF = true;}
      while(cJsAcKboYD == cJsAcKboYD){BVuyYyJwxO = true;}
      while(KxpBdIjwuD == KxpBdIjwuD){kSfMRKTFkg = true;}
      if(szxdMMrUKV == true){szxdMMrUKV = false;}
      if(NlLctrRTZa == true){NlLctrRTZa = false;}
      if(iUbIpHtIBL == true){iUbIpHtIBL = false;}
      if(zAWEMdMPnP == true){zAWEMdMPnP = false;}
      if(RHdDoXkMHk == true){RHdDoXkMHk = false;}
      if(qPVTTYXnnE == true){qPVTTYXnnE = false;}
      if(RiSyVMPHQQ == true){RiSyVMPHQQ = false;}
      if(eCfKIapXTR == true){eCfKIapXTR = false;}
      if(WhBQUieCkm == true){WhBQUieCkm = false;}
      if(FYaiyioegb == true){FYaiyioegb = false;}
      if(IdwpFojLLs == true){IdwpFojLLs = false;}
      if(hzUWhjgBdm == true){hzUWhjgBdm = false;}
      if(hMWcKGawMZ == true){hMWcKGawMZ = false;}
      if(lLqqJrkLLf == true){lLqqJrkLLf = false;}
      if(zSqrEFEEBN == true){zSqrEFEEBN = false;}
      if(BmBtsuHSey == true){BmBtsuHSey = false;}
      if(NnzkGWIcMo == true){NnzkGWIcMo = false;}
      if(yVoxnPVeYF == true){yVoxnPVeYF = false;}
      if(BVuyYyJwxO == true){BVuyYyJwxO = false;}
      if(kSfMRKTFkg == true){kSfMRKTFkg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVGKMZKVIF
{ 
  void tHRpyRTJXc()
  { 
      bool DgqkcIZBCT = false;
      bool mKeRKhIaaR = false;
      bool mGaxMHTxaV = false;
      bool rrWCUCVLFI = false;
      bool ziwaVnTfeU = false;
      bool rGEQjxFtXU = false;
      bool nbZgbumcxI = false;
      bool LwVSREKzbY = false;
      bool nnRGckmGRW = false;
      bool wbmkTXIOza = false;
      bool BqhWIuklze = false;
      bool mFSzfAJSDq = false;
      bool HgKZLjIkyt = false;
      bool uuAAWxGtyh = false;
      bool zAGljpJnET = false;
      bool NoLISUfHLY = false;
      bool lAnEjrFRbi = false;
      bool tOUUqHZXpU = false;
      bool ZUfdgGirhC = false;
      bool QyiYwyMBCr = false;
      string QpAfWnPtbn;
      string jLnquXGToV;
      string FItqfmCxCu;
      string MBLGoeWXFe;
      string yfmZrGcZli;
      string pKkFDHuJzj;
      string lRrfbhAhBP;
      string AiNKXZVUyZ;
      string JbLSEBQFCg;
      string iNXVsgmGyK;
      string FuYWhHwZhd;
      string laKZZJGYaZ;
      string QueTfmLrRp;
      string mOWnTODnkx;
      string EqWYtIDxwi;
      string ZNeXsKPEpt;
      string uEIqpWEVGL;
      string GRndVZXFZX;
      string jNwhQYjytI;
      string yyypCAhfhW;
      if(QpAfWnPtbn == FuYWhHwZhd){DgqkcIZBCT = true;}
      else if(FuYWhHwZhd == QpAfWnPtbn){BqhWIuklze = true;}
      if(jLnquXGToV == laKZZJGYaZ){mKeRKhIaaR = true;}
      else if(laKZZJGYaZ == jLnquXGToV){mFSzfAJSDq = true;}
      if(FItqfmCxCu == QueTfmLrRp){mGaxMHTxaV = true;}
      else if(QueTfmLrRp == FItqfmCxCu){HgKZLjIkyt = true;}
      if(MBLGoeWXFe == mOWnTODnkx){rrWCUCVLFI = true;}
      else if(mOWnTODnkx == MBLGoeWXFe){uuAAWxGtyh = true;}
      if(yfmZrGcZli == EqWYtIDxwi){ziwaVnTfeU = true;}
      else if(EqWYtIDxwi == yfmZrGcZli){zAGljpJnET = true;}
      if(pKkFDHuJzj == ZNeXsKPEpt){rGEQjxFtXU = true;}
      else if(ZNeXsKPEpt == pKkFDHuJzj){NoLISUfHLY = true;}
      if(lRrfbhAhBP == uEIqpWEVGL){nbZgbumcxI = true;}
      else if(uEIqpWEVGL == lRrfbhAhBP){lAnEjrFRbi = true;}
      if(AiNKXZVUyZ == GRndVZXFZX){LwVSREKzbY = true;}
      if(JbLSEBQFCg == jNwhQYjytI){nnRGckmGRW = true;}
      if(iNXVsgmGyK == yyypCAhfhW){wbmkTXIOza = true;}
      while(GRndVZXFZX == AiNKXZVUyZ){tOUUqHZXpU = true;}
      while(jNwhQYjytI == jNwhQYjytI){ZUfdgGirhC = true;}
      while(yyypCAhfhW == yyypCAhfhW){QyiYwyMBCr = true;}
      if(DgqkcIZBCT == true){DgqkcIZBCT = false;}
      if(mKeRKhIaaR == true){mKeRKhIaaR = false;}
      if(mGaxMHTxaV == true){mGaxMHTxaV = false;}
      if(rrWCUCVLFI == true){rrWCUCVLFI = false;}
      if(ziwaVnTfeU == true){ziwaVnTfeU = false;}
      if(rGEQjxFtXU == true){rGEQjxFtXU = false;}
      if(nbZgbumcxI == true){nbZgbumcxI = false;}
      if(LwVSREKzbY == true){LwVSREKzbY = false;}
      if(nnRGckmGRW == true){nnRGckmGRW = false;}
      if(wbmkTXIOza == true){wbmkTXIOza = false;}
      if(BqhWIuklze == true){BqhWIuklze = false;}
      if(mFSzfAJSDq == true){mFSzfAJSDq = false;}
      if(HgKZLjIkyt == true){HgKZLjIkyt = false;}
      if(uuAAWxGtyh == true){uuAAWxGtyh = false;}
      if(zAGljpJnET == true){zAGljpJnET = false;}
      if(NoLISUfHLY == true){NoLISUfHLY = false;}
      if(lAnEjrFRbi == true){lAnEjrFRbi = false;}
      if(tOUUqHZXpU == true){tOUUqHZXpU = false;}
      if(ZUfdgGirhC == true){ZUfdgGirhC = false;}
      if(QyiYwyMBCr == true){QyiYwyMBCr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UWRTFGUNLY
{ 
  void sXKTIVFVNd()
  { 
      bool myRdqnLZdO = false;
      bool QdBcFWnGVT = false;
      bool iCAbgWjXwU = false;
      bool lLRZsOnklA = false;
      bool hPsPPQuQDq = false;
      bool ALbHukxpxU = false;
      bool EncJbFLbip = false;
      bool iDUUkSIkMP = false;
      bool bSTFTajKdI = false;
      bool QymQwtminJ = false;
      bool ESgNIxpGVb = false;
      bool bMdhskTXpA = false;
      bool VAyaYjPEXq = false;
      bool fZxCKIlGxW = false;
      bool jcoBfEUFWL = false;
      bool aOsmnEUFnX = false;
      bool glidwCPaWj = false;
      bool zMZSPrLwuT = false;
      bool OKgMQRfJNG = false;
      bool nfRYoytLFd = false;
      string RkdpXpspnc;
      string FuCeVBXqyB;
      string jFCeeDyCti;
      string MXDdQeEBUa;
      string rwqEHhedtH;
      string guwcnMhyLT;
      string rpuEQhqXNp;
      string xWWXJmNyWw;
      string YUHmCQaaoE;
      string xFoBiBBmmZ;
      string pGQDKKYYSA;
      string zjbOtXiICA;
      string GQiJsqgVnH;
      string lZKxGSDEbq;
      string qCHoEMcaGL;
      string SrjmSZXGJS;
      string cDjKNYZeIb;
      string TdfKIEIsEg;
      string NGPcotpXdg;
      string uxtINnRxae;
      if(RkdpXpspnc == pGQDKKYYSA){myRdqnLZdO = true;}
      else if(pGQDKKYYSA == RkdpXpspnc){ESgNIxpGVb = true;}
      if(FuCeVBXqyB == zjbOtXiICA){QdBcFWnGVT = true;}
      else if(zjbOtXiICA == FuCeVBXqyB){bMdhskTXpA = true;}
      if(jFCeeDyCti == GQiJsqgVnH){iCAbgWjXwU = true;}
      else if(GQiJsqgVnH == jFCeeDyCti){VAyaYjPEXq = true;}
      if(MXDdQeEBUa == lZKxGSDEbq){lLRZsOnklA = true;}
      else if(lZKxGSDEbq == MXDdQeEBUa){fZxCKIlGxW = true;}
      if(rwqEHhedtH == qCHoEMcaGL){hPsPPQuQDq = true;}
      else if(qCHoEMcaGL == rwqEHhedtH){jcoBfEUFWL = true;}
      if(guwcnMhyLT == SrjmSZXGJS){ALbHukxpxU = true;}
      else if(SrjmSZXGJS == guwcnMhyLT){aOsmnEUFnX = true;}
      if(rpuEQhqXNp == cDjKNYZeIb){EncJbFLbip = true;}
      else if(cDjKNYZeIb == rpuEQhqXNp){glidwCPaWj = true;}
      if(xWWXJmNyWw == TdfKIEIsEg){iDUUkSIkMP = true;}
      if(YUHmCQaaoE == NGPcotpXdg){bSTFTajKdI = true;}
      if(xFoBiBBmmZ == uxtINnRxae){QymQwtminJ = true;}
      while(TdfKIEIsEg == xWWXJmNyWw){zMZSPrLwuT = true;}
      while(NGPcotpXdg == NGPcotpXdg){OKgMQRfJNG = true;}
      while(uxtINnRxae == uxtINnRxae){nfRYoytLFd = true;}
      if(myRdqnLZdO == true){myRdqnLZdO = false;}
      if(QdBcFWnGVT == true){QdBcFWnGVT = false;}
      if(iCAbgWjXwU == true){iCAbgWjXwU = false;}
      if(lLRZsOnklA == true){lLRZsOnklA = false;}
      if(hPsPPQuQDq == true){hPsPPQuQDq = false;}
      if(ALbHukxpxU == true){ALbHukxpxU = false;}
      if(EncJbFLbip == true){EncJbFLbip = false;}
      if(iDUUkSIkMP == true){iDUUkSIkMP = false;}
      if(bSTFTajKdI == true){bSTFTajKdI = false;}
      if(QymQwtminJ == true){QymQwtminJ = false;}
      if(ESgNIxpGVb == true){ESgNIxpGVb = false;}
      if(bMdhskTXpA == true){bMdhskTXpA = false;}
      if(VAyaYjPEXq == true){VAyaYjPEXq = false;}
      if(fZxCKIlGxW == true){fZxCKIlGxW = false;}
      if(jcoBfEUFWL == true){jcoBfEUFWL = false;}
      if(aOsmnEUFnX == true){aOsmnEUFnX = false;}
      if(glidwCPaWj == true){glidwCPaWj = false;}
      if(zMZSPrLwuT == true){zMZSPrLwuT = false;}
      if(OKgMQRfJNG == true){OKgMQRfJNG = false;}
      if(nfRYoytLFd == true){nfRYoytLFd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIGTQNZKIN
{ 
  void eHNgDrdCCB()
  { 
      bool iQMYdJOpyJ = false;
      bool yPEEYKFbCo = false;
      bool nwHrdjemnQ = false;
      bool pYfTJuIUoO = false;
      bool BssZiKPTjC = false;
      bool BdkPalJTus = false;
      bool eaBhSZikuc = false;
      bool BkmnmuChIS = false;
      bool TKDlOMmQrW = false;
      bool loZuiZqLGJ = false;
      bool aeYGAQpxbf = false;
      bool ibLbYUXPTF = false;
      bool lSrYqMKqEN = false;
      bool Dqazqolwlx = false;
      bool VonMmJcxWO = false;
      bool BbqBWImzOm = false;
      bool FzrObrBLjj = false;
      bool iadViwdflg = false;
      bool iNUpLazZbi = false;
      bool BlgyqWwZju = false;
      string tiPamVDNPb;
      string radLkRSfed;
      string dfRraqnqRk;
      string YwUxBsKECe;
      string BzRDztYUGO;
      string CyxpJORXzw;
      string hLudDwGfJr;
      string HNcAbdONrg;
      string RTkDiaydnm;
      string bmFGxoDmzD;
      string nrKNHoUxOe;
      string zDeSdOaruc;
      string xcrWQUIVCm;
      string abOosZIWws;
      string FAPImXHlci;
      string NKrVFLznxl;
      string gyuaEXopZE;
      string FEwBXwMjir;
      string MVsSYPjrig;
      string ZUYJMGFnEP;
      if(tiPamVDNPb == nrKNHoUxOe){iQMYdJOpyJ = true;}
      else if(nrKNHoUxOe == tiPamVDNPb){aeYGAQpxbf = true;}
      if(radLkRSfed == zDeSdOaruc){yPEEYKFbCo = true;}
      else if(zDeSdOaruc == radLkRSfed){ibLbYUXPTF = true;}
      if(dfRraqnqRk == xcrWQUIVCm){nwHrdjemnQ = true;}
      else if(xcrWQUIVCm == dfRraqnqRk){lSrYqMKqEN = true;}
      if(YwUxBsKECe == abOosZIWws){pYfTJuIUoO = true;}
      else if(abOosZIWws == YwUxBsKECe){Dqazqolwlx = true;}
      if(BzRDztYUGO == FAPImXHlci){BssZiKPTjC = true;}
      else if(FAPImXHlci == BzRDztYUGO){VonMmJcxWO = true;}
      if(CyxpJORXzw == NKrVFLznxl){BdkPalJTus = true;}
      else if(NKrVFLznxl == CyxpJORXzw){BbqBWImzOm = true;}
      if(hLudDwGfJr == gyuaEXopZE){eaBhSZikuc = true;}
      else if(gyuaEXopZE == hLudDwGfJr){FzrObrBLjj = true;}
      if(HNcAbdONrg == FEwBXwMjir){BkmnmuChIS = true;}
      if(RTkDiaydnm == MVsSYPjrig){TKDlOMmQrW = true;}
      if(bmFGxoDmzD == ZUYJMGFnEP){loZuiZqLGJ = true;}
      while(FEwBXwMjir == HNcAbdONrg){iadViwdflg = true;}
      while(MVsSYPjrig == MVsSYPjrig){iNUpLazZbi = true;}
      while(ZUYJMGFnEP == ZUYJMGFnEP){BlgyqWwZju = true;}
      if(iQMYdJOpyJ == true){iQMYdJOpyJ = false;}
      if(yPEEYKFbCo == true){yPEEYKFbCo = false;}
      if(nwHrdjemnQ == true){nwHrdjemnQ = false;}
      if(pYfTJuIUoO == true){pYfTJuIUoO = false;}
      if(BssZiKPTjC == true){BssZiKPTjC = false;}
      if(BdkPalJTus == true){BdkPalJTus = false;}
      if(eaBhSZikuc == true){eaBhSZikuc = false;}
      if(BkmnmuChIS == true){BkmnmuChIS = false;}
      if(TKDlOMmQrW == true){TKDlOMmQrW = false;}
      if(loZuiZqLGJ == true){loZuiZqLGJ = false;}
      if(aeYGAQpxbf == true){aeYGAQpxbf = false;}
      if(ibLbYUXPTF == true){ibLbYUXPTF = false;}
      if(lSrYqMKqEN == true){lSrYqMKqEN = false;}
      if(Dqazqolwlx == true){Dqazqolwlx = false;}
      if(VonMmJcxWO == true){VonMmJcxWO = false;}
      if(BbqBWImzOm == true){BbqBWImzOm = false;}
      if(FzrObrBLjj == true){FzrObrBLjj = false;}
      if(iadViwdflg == true){iadViwdflg = false;}
      if(iNUpLazZbi == true){iNUpLazZbi = false;}
      if(BlgyqWwZju == true){BlgyqWwZju = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUBRBZSNYA
{ 
  void ZccNFOChwP()
  { 
      bool UnMYzaNytp = false;
      bool SGFBKVOyBT = false;
      bool pwkmxbORoP = false;
      bool yrTbUKgQEg = false;
      bool FAyZPqQEdz = false;
      bool GwiSfXCYaW = false;
      bool LwJerZmdfz = false;
      bool nxsUNpyLXG = false;
      bool LKmpIBJAux = false;
      bool IHphUIqSgo = false;
      bool EmYeKIDOFo = false;
      bool ZqBTLBJSVp = false;
      bool QmhiqfHLzE = false;
      bool zediBXlIfz = false;
      bool xttFWRGVVS = false;
      bool zXwqXREome = false;
      bool ArOBpuMRSm = false;
      bool PBmVsVrbMZ = false;
      bool YlofEahmKj = false;
      bool SwUAzFfsOb = false;
      string xWNDneIQCe;
      string TfWpUmqYzr;
      string kmwoEdVBRe;
      string jbupUxLgmd;
      string WXaiRFZiNX;
      string CzZjnKZXyK;
      string JGyWtrjgUW;
      string aKlVUMLMXz;
      string DmntckBKBK;
      string WnhbTPYDnZ;
      string UrNpwrMEPa;
      string yNzzHWSEtI;
      string pYfKzmbJBF;
      string nIXydKYxyj;
      string XxuZMJnhUx;
      string wUIeiwMDqI;
      string PDCKmpoAVw;
      string xVGKjscGyo;
      string ytoEITzsPh;
      string yVGoUUuklW;
      if(xWNDneIQCe == UrNpwrMEPa){UnMYzaNytp = true;}
      else if(UrNpwrMEPa == xWNDneIQCe){EmYeKIDOFo = true;}
      if(TfWpUmqYzr == yNzzHWSEtI){SGFBKVOyBT = true;}
      else if(yNzzHWSEtI == TfWpUmqYzr){ZqBTLBJSVp = true;}
      if(kmwoEdVBRe == pYfKzmbJBF){pwkmxbORoP = true;}
      else if(pYfKzmbJBF == kmwoEdVBRe){QmhiqfHLzE = true;}
      if(jbupUxLgmd == nIXydKYxyj){yrTbUKgQEg = true;}
      else if(nIXydKYxyj == jbupUxLgmd){zediBXlIfz = true;}
      if(WXaiRFZiNX == XxuZMJnhUx){FAyZPqQEdz = true;}
      else if(XxuZMJnhUx == WXaiRFZiNX){xttFWRGVVS = true;}
      if(CzZjnKZXyK == wUIeiwMDqI){GwiSfXCYaW = true;}
      else if(wUIeiwMDqI == CzZjnKZXyK){zXwqXREome = true;}
      if(JGyWtrjgUW == PDCKmpoAVw){LwJerZmdfz = true;}
      else if(PDCKmpoAVw == JGyWtrjgUW){ArOBpuMRSm = true;}
      if(aKlVUMLMXz == xVGKjscGyo){nxsUNpyLXG = true;}
      if(DmntckBKBK == ytoEITzsPh){LKmpIBJAux = true;}
      if(WnhbTPYDnZ == yVGoUUuklW){IHphUIqSgo = true;}
      while(xVGKjscGyo == aKlVUMLMXz){PBmVsVrbMZ = true;}
      while(ytoEITzsPh == ytoEITzsPh){YlofEahmKj = true;}
      while(yVGoUUuklW == yVGoUUuklW){SwUAzFfsOb = true;}
      if(UnMYzaNytp == true){UnMYzaNytp = false;}
      if(SGFBKVOyBT == true){SGFBKVOyBT = false;}
      if(pwkmxbORoP == true){pwkmxbORoP = false;}
      if(yrTbUKgQEg == true){yrTbUKgQEg = false;}
      if(FAyZPqQEdz == true){FAyZPqQEdz = false;}
      if(GwiSfXCYaW == true){GwiSfXCYaW = false;}
      if(LwJerZmdfz == true){LwJerZmdfz = false;}
      if(nxsUNpyLXG == true){nxsUNpyLXG = false;}
      if(LKmpIBJAux == true){LKmpIBJAux = false;}
      if(IHphUIqSgo == true){IHphUIqSgo = false;}
      if(EmYeKIDOFo == true){EmYeKIDOFo = false;}
      if(ZqBTLBJSVp == true){ZqBTLBJSVp = false;}
      if(QmhiqfHLzE == true){QmhiqfHLzE = false;}
      if(zediBXlIfz == true){zediBXlIfz = false;}
      if(xttFWRGVVS == true){xttFWRGVVS = false;}
      if(zXwqXREome == true){zXwqXREome = false;}
      if(ArOBpuMRSm == true){ArOBpuMRSm = false;}
      if(PBmVsVrbMZ == true){PBmVsVrbMZ = false;}
      if(YlofEahmKj == true){YlofEahmKj = false;}
      if(SwUAzFfsOb == true){SwUAzFfsOb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRCCZFSBFA
{ 
  void VqsaVKmEuk()
  { 
      bool CoiAwujQMn = false;
      bool XBBsfnTGDz = false;
      bool nqBdSctQPe = false;
      bool HjlANRHIzN = false;
      bool latTIssthp = false;
      bool XzjNdLmEhS = false;
      bool ATBhfmOAfO = false;
      bool fLHoMNwhUY = false;
      bool jAhYHIAYWB = false;
      bool eCafNSYLnU = false;
      bool esOTJLrtAQ = false;
      bool OFiIiAkbaW = false;
      bool mpddicjabs = false;
      bool nksztpkNPu = false;
      bool QFXFlZSSxN = false;
      bool hxjQhnOjjf = false;
      bool bRSHbdLjNr = false;
      bool OWMfGgSXqJ = false;
      bool KRdNLqAbQG = false;
      bool bBdiSymQdI = false;
      string FSUeTlMtbg;
      string eWLlGzhybL;
      string NFKPsjtHQB;
      string QaxlizYSFB;
      string ObnqduHpiT;
      string dtwwtAIFlj;
      string rFdZPDZZCH;
      string ZPraxkQSky;
      string bDYwXWeAqi;
      string pTfVJJyNba;
      string VhnatOBUzI;
      string ioUmHnfhCr;
      string XYhSQGiWRm;
      string mCqKctPxCI;
      string VJAizBzsNU;
      string dPKiCwAUJm;
      string edDMVgyJKM;
      string XhfsWOYyTP;
      string HpJwJWrHHf;
      string ttnOdrGnMS;
      if(FSUeTlMtbg == VhnatOBUzI){CoiAwujQMn = true;}
      else if(VhnatOBUzI == FSUeTlMtbg){esOTJLrtAQ = true;}
      if(eWLlGzhybL == ioUmHnfhCr){XBBsfnTGDz = true;}
      else if(ioUmHnfhCr == eWLlGzhybL){OFiIiAkbaW = true;}
      if(NFKPsjtHQB == XYhSQGiWRm){nqBdSctQPe = true;}
      else if(XYhSQGiWRm == NFKPsjtHQB){mpddicjabs = true;}
      if(QaxlizYSFB == mCqKctPxCI){HjlANRHIzN = true;}
      else if(mCqKctPxCI == QaxlizYSFB){nksztpkNPu = true;}
      if(ObnqduHpiT == VJAizBzsNU){latTIssthp = true;}
      else if(VJAizBzsNU == ObnqduHpiT){QFXFlZSSxN = true;}
      if(dtwwtAIFlj == dPKiCwAUJm){XzjNdLmEhS = true;}
      else if(dPKiCwAUJm == dtwwtAIFlj){hxjQhnOjjf = true;}
      if(rFdZPDZZCH == edDMVgyJKM){ATBhfmOAfO = true;}
      else if(edDMVgyJKM == rFdZPDZZCH){bRSHbdLjNr = true;}
      if(ZPraxkQSky == XhfsWOYyTP){fLHoMNwhUY = true;}
      if(bDYwXWeAqi == HpJwJWrHHf){jAhYHIAYWB = true;}
      if(pTfVJJyNba == ttnOdrGnMS){eCafNSYLnU = true;}
      while(XhfsWOYyTP == ZPraxkQSky){OWMfGgSXqJ = true;}
      while(HpJwJWrHHf == HpJwJWrHHf){KRdNLqAbQG = true;}
      while(ttnOdrGnMS == ttnOdrGnMS){bBdiSymQdI = true;}
      if(CoiAwujQMn == true){CoiAwujQMn = false;}
      if(XBBsfnTGDz == true){XBBsfnTGDz = false;}
      if(nqBdSctQPe == true){nqBdSctQPe = false;}
      if(HjlANRHIzN == true){HjlANRHIzN = false;}
      if(latTIssthp == true){latTIssthp = false;}
      if(XzjNdLmEhS == true){XzjNdLmEhS = false;}
      if(ATBhfmOAfO == true){ATBhfmOAfO = false;}
      if(fLHoMNwhUY == true){fLHoMNwhUY = false;}
      if(jAhYHIAYWB == true){jAhYHIAYWB = false;}
      if(eCafNSYLnU == true){eCafNSYLnU = false;}
      if(esOTJLrtAQ == true){esOTJLrtAQ = false;}
      if(OFiIiAkbaW == true){OFiIiAkbaW = false;}
      if(mpddicjabs == true){mpddicjabs = false;}
      if(nksztpkNPu == true){nksztpkNPu = false;}
      if(QFXFlZSSxN == true){QFXFlZSSxN = false;}
      if(hxjQhnOjjf == true){hxjQhnOjjf = false;}
      if(bRSHbdLjNr == true){bRSHbdLjNr = false;}
      if(OWMfGgSXqJ == true){OWMfGgSXqJ = false;}
      if(KRdNLqAbQG == true){KRdNLqAbQG = false;}
      if(bBdiSymQdI == true){bBdiSymQdI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTWLUJQPQR
{ 
  void JszVHNDXTa()
  { 
      bool zaqMALiOPd = false;
      bool eSAQqtwboz = false;
      bool BaBpajaDWb = false;
      bool koHqXCNicg = false;
      bool YDwywRRbdX = false;
      bool lKrSeYZAlQ = false;
      bool kermsoKIso = false;
      bool gNyHZyeCtI = false;
      bool RzZzpZxnLz = false;
      bool cMxMwsLIFG = false;
      bool GJioqYMjsg = false;
      bool sWGczlFsxS = false;
      bool rVxtMUPkLg = false;
      bool lVwnCIPkHR = false;
      bool MNudFFFUMK = false;
      bool nSLlOjLncW = false;
      bool IbXMuXZSap = false;
      bool VUkfFeaSoG = false;
      bool OuXArTKKZR = false;
      bool wbIkIkoiig = false;
      string EPUiirfzuL;
      string wCIpJQnLJX;
      string RcoNUTJzqL;
      string jzpJUmUTce;
      string OeuoQBtTTy;
      string guSRLaZGOP;
      string ifHjbxLzUW;
      string uThdImhAxS;
      string YperdogYyt;
      string MNFNwhWKNS;
      string otyxCNMnIX;
      string rZIupsBOGm;
      string QmAZJhOThZ;
      string QXmedeqgpQ;
      string brPZCmEJXD;
      string gIEaCCsYnU;
      string ysFiHUmdRL;
      string CUYoKXWaXW;
      string cEwdsISLca;
      string kRsURilgSg;
      if(EPUiirfzuL == otyxCNMnIX){zaqMALiOPd = true;}
      else if(otyxCNMnIX == EPUiirfzuL){GJioqYMjsg = true;}
      if(wCIpJQnLJX == rZIupsBOGm){eSAQqtwboz = true;}
      else if(rZIupsBOGm == wCIpJQnLJX){sWGczlFsxS = true;}
      if(RcoNUTJzqL == QmAZJhOThZ){BaBpajaDWb = true;}
      else if(QmAZJhOThZ == RcoNUTJzqL){rVxtMUPkLg = true;}
      if(jzpJUmUTce == QXmedeqgpQ){koHqXCNicg = true;}
      else if(QXmedeqgpQ == jzpJUmUTce){lVwnCIPkHR = true;}
      if(OeuoQBtTTy == brPZCmEJXD){YDwywRRbdX = true;}
      else if(brPZCmEJXD == OeuoQBtTTy){MNudFFFUMK = true;}
      if(guSRLaZGOP == gIEaCCsYnU){lKrSeYZAlQ = true;}
      else if(gIEaCCsYnU == guSRLaZGOP){nSLlOjLncW = true;}
      if(ifHjbxLzUW == ysFiHUmdRL){kermsoKIso = true;}
      else if(ysFiHUmdRL == ifHjbxLzUW){IbXMuXZSap = true;}
      if(uThdImhAxS == CUYoKXWaXW){gNyHZyeCtI = true;}
      if(YperdogYyt == cEwdsISLca){RzZzpZxnLz = true;}
      if(MNFNwhWKNS == kRsURilgSg){cMxMwsLIFG = true;}
      while(CUYoKXWaXW == uThdImhAxS){VUkfFeaSoG = true;}
      while(cEwdsISLca == cEwdsISLca){OuXArTKKZR = true;}
      while(kRsURilgSg == kRsURilgSg){wbIkIkoiig = true;}
      if(zaqMALiOPd == true){zaqMALiOPd = false;}
      if(eSAQqtwboz == true){eSAQqtwboz = false;}
      if(BaBpajaDWb == true){BaBpajaDWb = false;}
      if(koHqXCNicg == true){koHqXCNicg = false;}
      if(YDwywRRbdX == true){YDwywRRbdX = false;}
      if(lKrSeYZAlQ == true){lKrSeYZAlQ = false;}
      if(kermsoKIso == true){kermsoKIso = false;}
      if(gNyHZyeCtI == true){gNyHZyeCtI = false;}
      if(RzZzpZxnLz == true){RzZzpZxnLz = false;}
      if(cMxMwsLIFG == true){cMxMwsLIFG = false;}
      if(GJioqYMjsg == true){GJioqYMjsg = false;}
      if(sWGczlFsxS == true){sWGczlFsxS = false;}
      if(rVxtMUPkLg == true){rVxtMUPkLg = false;}
      if(lVwnCIPkHR == true){lVwnCIPkHR = false;}
      if(MNudFFFUMK == true){MNudFFFUMK = false;}
      if(nSLlOjLncW == true){nSLlOjLncW = false;}
      if(IbXMuXZSap == true){IbXMuXZSap = false;}
      if(VUkfFeaSoG == true){VUkfFeaSoG = false;}
      if(OuXArTKKZR == true){OuXArTKKZR = false;}
      if(wbIkIkoiig == true){wbIkIkoiig = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJGXRQMGSS
{ 
  void YADKpRknlo()
  { 
      bool ZoIQtiqRuW = false;
      bool uPXlTZfQoT = false;
      bool PGJJysYHuS = false;
      bool TzHTQayNqj = false;
      bool VRawOZhPaX = false;
      bool aWkYsTfySA = false;
      bool KiVcCwIEVs = false;
      bool aRYFyxeMtX = false;
      bool LIgXrxNhZw = false;
      bool tAuqYluytS = false;
      bool RdthwIxeau = false;
      bool nTDtoCCyjE = false;
      bool hZdYyaVhgL = false;
      bool BgRbGgOzai = false;
      bool ziGdHZwBCW = false;
      bool ixNojrAUiU = false;
      bool mPyOsHBbnH = false;
      bool mDXBEzSzRY = false;
      bool eUeJbEScqO = false;
      bool gsPFwijrjz = false;
      string JeVelJtSrk;
      string JfjKGPwedQ;
      string pkKWUoMmnW;
      string lmApYpplwx;
      string WGFJyKnVlq;
      string abOeZYUyKw;
      string xHdUzVetkP;
      string ZKifsjeAYK;
      string BpBwuJXVQA;
      string VqbzAPbjJb;
      string etjVRQshlo;
      string sTZzuGFgYo;
      string xJcjshiifc;
      string HtqxfHGeee;
      string QpiaHCRbEt;
      string JtLUdUQAcj;
      string gJCIhycbTn;
      string zaCsYHZBbp;
      string PGdlSNiVSK;
      string pGCtyGmasI;
      if(JeVelJtSrk == etjVRQshlo){ZoIQtiqRuW = true;}
      else if(etjVRQshlo == JeVelJtSrk){RdthwIxeau = true;}
      if(JfjKGPwedQ == sTZzuGFgYo){uPXlTZfQoT = true;}
      else if(sTZzuGFgYo == JfjKGPwedQ){nTDtoCCyjE = true;}
      if(pkKWUoMmnW == xJcjshiifc){PGJJysYHuS = true;}
      else if(xJcjshiifc == pkKWUoMmnW){hZdYyaVhgL = true;}
      if(lmApYpplwx == HtqxfHGeee){TzHTQayNqj = true;}
      else if(HtqxfHGeee == lmApYpplwx){BgRbGgOzai = true;}
      if(WGFJyKnVlq == QpiaHCRbEt){VRawOZhPaX = true;}
      else if(QpiaHCRbEt == WGFJyKnVlq){ziGdHZwBCW = true;}
      if(abOeZYUyKw == JtLUdUQAcj){aWkYsTfySA = true;}
      else if(JtLUdUQAcj == abOeZYUyKw){ixNojrAUiU = true;}
      if(xHdUzVetkP == gJCIhycbTn){KiVcCwIEVs = true;}
      else if(gJCIhycbTn == xHdUzVetkP){mPyOsHBbnH = true;}
      if(ZKifsjeAYK == zaCsYHZBbp){aRYFyxeMtX = true;}
      if(BpBwuJXVQA == PGdlSNiVSK){LIgXrxNhZw = true;}
      if(VqbzAPbjJb == pGCtyGmasI){tAuqYluytS = true;}
      while(zaCsYHZBbp == ZKifsjeAYK){mDXBEzSzRY = true;}
      while(PGdlSNiVSK == PGdlSNiVSK){eUeJbEScqO = true;}
      while(pGCtyGmasI == pGCtyGmasI){gsPFwijrjz = true;}
      if(ZoIQtiqRuW == true){ZoIQtiqRuW = false;}
      if(uPXlTZfQoT == true){uPXlTZfQoT = false;}
      if(PGJJysYHuS == true){PGJJysYHuS = false;}
      if(TzHTQayNqj == true){TzHTQayNqj = false;}
      if(VRawOZhPaX == true){VRawOZhPaX = false;}
      if(aWkYsTfySA == true){aWkYsTfySA = false;}
      if(KiVcCwIEVs == true){KiVcCwIEVs = false;}
      if(aRYFyxeMtX == true){aRYFyxeMtX = false;}
      if(LIgXrxNhZw == true){LIgXrxNhZw = false;}
      if(tAuqYluytS == true){tAuqYluytS = false;}
      if(RdthwIxeau == true){RdthwIxeau = false;}
      if(nTDtoCCyjE == true){nTDtoCCyjE = false;}
      if(hZdYyaVhgL == true){hZdYyaVhgL = false;}
      if(BgRbGgOzai == true){BgRbGgOzai = false;}
      if(ziGdHZwBCW == true){ziGdHZwBCW = false;}
      if(ixNojrAUiU == true){ixNojrAUiU = false;}
      if(mPyOsHBbnH == true){mPyOsHBbnH = false;}
      if(mDXBEzSzRY == true){mDXBEzSzRY = false;}
      if(eUeJbEScqO == true){eUeJbEScqO = false;}
      if(gsPFwijrjz == true){gsPFwijrjz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IEMOXURUXG
{ 
  void dsgXFiKRaw()
  { 
      bool fVgJMnuiNZ = false;
      bool DCnjNPtMJt = false;
      bool rrLMhXBnxD = false;
      bool TnxNoXmMML = false;
      bool tUoQFDOAXz = false;
      bool QcdzBnKUao = false;
      bool mGlJFOFaup = false;
      bool cgAyzWCuHe = false;
      bool IAQylqKxLB = false;
      bool MRlWXnifKp = false;
      bool ynFgVjcfAd = false;
      bool kPNwglpnWO = false;
      bool EIOtcKudZL = false;
      bool nWjQfUuibC = false;
      bool OewhPwEopk = false;
      bool xuIulpZKDL = false;
      bool nyFooOfwPM = false;
      bool qHLUAYLfdf = false;
      bool FFnnNsNnep = false;
      bool ujeQNPYHrA = false;
      string noAmcUCAHE;
      string NnRXTlmyws;
      string eiRdpZJkLq;
      string CAmVqXVHqW;
      string SdZTiCKWuq;
      string lqYJwFXWwD;
      string KQoQBNAugu;
      string QfHYaAIxun;
      string OmoUELbdZk;
      string AzKmLBoISU;
      string BOpAZFjzhu;
      string wZaInXaTLp;
      string lWVuuRVTNZ;
      string LAeZmzxotz;
      string abudoZXCyn;
      string ZUwbiestEI;
      string jPlIjwtBUo;
      string alZMOJaqGU;
      string tTVZzpECpI;
      string GCklPKomts;
      if(noAmcUCAHE == BOpAZFjzhu){fVgJMnuiNZ = true;}
      else if(BOpAZFjzhu == noAmcUCAHE){ynFgVjcfAd = true;}
      if(NnRXTlmyws == wZaInXaTLp){DCnjNPtMJt = true;}
      else if(wZaInXaTLp == NnRXTlmyws){kPNwglpnWO = true;}
      if(eiRdpZJkLq == lWVuuRVTNZ){rrLMhXBnxD = true;}
      else if(lWVuuRVTNZ == eiRdpZJkLq){EIOtcKudZL = true;}
      if(CAmVqXVHqW == LAeZmzxotz){TnxNoXmMML = true;}
      else if(LAeZmzxotz == CAmVqXVHqW){nWjQfUuibC = true;}
      if(SdZTiCKWuq == abudoZXCyn){tUoQFDOAXz = true;}
      else if(abudoZXCyn == SdZTiCKWuq){OewhPwEopk = true;}
      if(lqYJwFXWwD == ZUwbiestEI){QcdzBnKUao = true;}
      else if(ZUwbiestEI == lqYJwFXWwD){xuIulpZKDL = true;}
      if(KQoQBNAugu == jPlIjwtBUo){mGlJFOFaup = true;}
      else if(jPlIjwtBUo == KQoQBNAugu){nyFooOfwPM = true;}
      if(QfHYaAIxun == alZMOJaqGU){cgAyzWCuHe = true;}
      if(OmoUELbdZk == tTVZzpECpI){IAQylqKxLB = true;}
      if(AzKmLBoISU == GCklPKomts){MRlWXnifKp = true;}
      while(alZMOJaqGU == QfHYaAIxun){qHLUAYLfdf = true;}
      while(tTVZzpECpI == tTVZzpECpI){FFnnNsNnep = true;}
      while(GCklPKomts == GCklPKomts){ujeQNPYHrA = true;}
      if(fVgJMnuiNZ == true){fVgJMnuiNZ = false;}
      if(DCnjNPtMJt == true){DCnjNPtMJt = false;}
      if(rrLMhXBnxD == true){rrLMhXBnxD = false;}
      if(TnxNoXmMML == true){TnxNoXmMML = false;}
      if(tUoQFDOAXz == true){tUoQFDOAXz = false;}
      if(QcdzBnKUao == true){QcdzBnKUao = false;}
      if(mGlJFOFaup == true){mGlJFOFaup = false;}
      if(cgAyzWCuHe == true){cgAyzWCuHe = false;}
      if(IAQylqKxLB == true){IAQylqKxLB = false;}
      if(MRlWXnifKp == true){MRlWXnifKp = false;}
      if(ynFgVjcfAd == true){ynFgVjcfAd = false;}
      if(kPNwglpnWO == true){kPNwglpnWO = false;}
      if(EIOtcKudZL == true){EIOtcKudZL = false;}
      if(nWjQfUuibC == true){nWjQfUuibC = false;}
      if(OewhPwEopk == true){OewhPwEopk = false;}
      if(xuIulpZKDL == true){xuIulpZKDL = false;}
      if(nyFooOfwPM == true){nyFooOfwPM = false;}
      if(qHLUAYLfdf == true){qHLUAYLfdf = false;}
      if(FFnnNsNnep == true){FFnnNsNnep = false;}
      if(ujeQNPYHrA == true){ujeQNPYHrA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBTYUOBSJF
{ 
  void JtfjmZceiS()
  { 
      bool nSOEfFIewr = false;
      bool CcOQHiVLQL = false;
      bool GigdjEEBNU = false;
      bool FSYVIGYPMG = false;
      bool BPSEigYiop = false;
      bool RJVYnFlkTa = false;
      bool BGRbmiDrHB = false;
      bool JFyJKpPbtC = false;
      bool fVLXCuxAhD = false;
      bool UnwlFtyqRz = false;
      bool dfanfLKMOx = false;
      bool oKpQtftsYq = false;
      bool lCKEgUIMDP = false;
      bool qYJtYAtXqp = false;
      bool jjljNJxeqZ = false;
      bool zESaNaUWGK = false;
      bool DyIyGQAurt = false;
      bool kWChHBQapW = false;
      bool WdVdPmFigx = false;
      bool eXQgmlbmdx = false;
      string SwtYMFYHGe;
      string TzpSSodtFy;
      string nmVKpShxyj;
      string GTMdqdaWjF;
      string CpYNWQQUlR;
      string xSVwjeZiit;
      string WbIWXAlLan;
      string NGJzwxOInY;
      string CMKgmmxPsM;
      string ErnphZhBoW;
      string eEtxDpJVzl;
      string PRuJqKQbik;
      string CVROjVSSQV;
      string PNSQtxSMdw;
      string caPHxmwdyX;
      string JGRDTImfNg;
      string XpFcVCydPt;
      string rDxmHaFKQx;
      string YnUsMJuOxl;
      string JmzwYmVmku;
      if(SwtYMFYHGe == eEtxDpJVzl){nSOEfFIewr = true;}
      else if(eEtxDpJVzl == SwtYMFYHGe){dfanfLKMOx = true;}
      if(TzpSSodtFy == PRuJqKQbik){CcOQHiVLQL = true;}
      else if(PRuJqKQbik == TzpSSodtFy){oKpQtftsYq = true;}
      if(nmVKpShxyj == CVROjVSSQV){GigdjEEBNU = true;}
      else if(CVROjVSSQV == nmVKpShxyj){lCKEgUIMDP = true;}
      if(GTMdqdaWjF == PNSQtxSMdw){FSYVIGYPMG = true;}
      else if(PNSQtxSMdw == GTMdqdaWjF){qYJtYAtXqp = true;}
      if(CpYNWQQUlR == caPHxmwdyX){BPSEigYiop = true;}
      else if(caPHxmwdyX == CpYNWQQUlR){jjljNJxeqZ = true;}
      if(xSVwjeZiit == JGRDTImfNg){RJVYnFlkTa = true;}
      else if(JGRDTImfNg == xSVwjeZiit){zESaNaUWGK = true;}
      if(WbIWXAlLan == XpFcVCydPt){BGRbmiDrHB = true;}
      else if(XpFcVCydPt == WbIWXAlLan){DyIyGQAurt = true;}
      if(NGJzwxOInY == rDxmHaFKQx){JFyJKpPbtC = true;}
      if(CMKgmmxPsM == YnUsMJuOxl){fVLXCuxAhD = true;}
      if(ErnphZhBoW == JmzwYmVmku){UnwlFtyqRz = true;}
      while(rDxmHaFKQx == NGJzwxOInY){kWChHBQapW = true;}
      while(YnUsMJuOxl == YnUsMJuOxl){WdVdPmFigx = true;}
      while(JmzwYmVmku == JmzwYmVmku){eXQgmlbmdx = true;}
      if(nSOEfFIewr == true){nSOEfFIewr = false;}
      if(CcOQHiVLQL == true){CcOQHiVLQL = false;}
      if(GigdjEEBNU == true){GigdjEEBNU = false;}
      if(FSYVIGYPMG == true){FSYVIGYPMG = false;}
      if(BPSEigYiop == true){BPSEigYiop = false;}
      if(RJVYnFlkTa == true){RJVYnFlkTa = false;}
      if(BGRbmiDrHB == true){BGRbmiDrHB = false;}
      if(JFyJKpPbtC == true){JFyJKpPbtC = false;}
      if(fVLXCuxAhD == true){fVLXCuxAhD = false;}
      if(UnwlFtyqRz == true){UnwlFtyqRz = false;}
      if(dfanfLKMOx == true){dfanfLKMOx = false;}
      if(oKpQtftsYq == true){oKpQtftsYq = false;}
      if(lCKEgUIMDP == true){lCKEgUIMDP = false;}
      if(qYJtYAtXqp == true){qYJtYAtXqp = false;}
      if(jjljNJxeqZ == true){jjljNJxeqZ = false;}
      if(zESaNaUWGK == true){zESaNaUWGK = false;}
      if(DyIyGQAurt == true){DyIyGQAurt = false;}
      if(kWChHBQapW == true){kWChHBQapW = false;}
      if(WdVdPmFigx == true){WdVdPmFigx = false;}
      if(eXQgmlbmdx == true){eXQgmlbmdx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQNARHWFYD
{ 
  void WPwpRGMnBO()
  { 
      bool jfEUCLOxGe = false;
      bool EKGWYejhOI = false;
      bool NHXRbbypLP = false;
      bool gpsNsdTplu = false;
      bool fuiujuglpJ = false;
      bool LzthYcHlsa = false;
      bool NXlpxNQrct = false;
      bool LtuSbRXcgg = false;
      bool tLzBEhuKnQ = false;
      bool VgxKhHJsxW = false;
      bool doIuyQDbGG = false;
      bool EdFMgBXjkP = false;
      bool RFDMYdxjjT = false;
      bool IeeKCEDEDm = false;
      bool dTEhMrbkdg = false;
      bool iYHhEXkwWT = false;
      bool TTqlyYztJb = false;
      bool yTfxlyBVAf = false;
      bool BMGDjiWxGe = false;
      bool TGgjTKcSjm = false;
      string XkHyzsLCiG;
      string ExSIQmgjWh;
      string msDDVskacL;
      string DAnYVTBmok;
      string VxMYTsTnGI;
      string gDPKJdhDbG;
      string IkYWDEJtlw;
      string ltukMofdjc;
      string YxTUezjdOq;
      string lxKickYoVO;
      string jZBKWmIexT;
      string xETzgKQDrD;
      string UfetKniMHb;
      string QpHUrzuJxr;
      string qFfttgdKBS;
      string TUxRtEtHAh;
      string DuWVDGxyGg;
      string PHFALPzjAc;
      string JXKoHusoZn;
      string FnJPnwhJqm;
      if(XkHyzsLCiG == jZBKWmIexT){jfEUCLOxGe = true;}
      else if(jZBKWmIexT == XkHyzsLCiG){doIuyQDbGG = true;}
      if(ExSIQmgjWh == xETzgKQDrD){EKGWYejhOI = true;}
      else if(xETzgKQDrD == ExSIQmgjWh){EdFMgBXjkP = true;}
      if(msDDVskacL == UfetKniMHb){NHXRbbypLP = true;}
      else if(UfetKniMHb == msDDVskacL){RFDMYdxjjT = true;}
      if(DAnYVTBmok == QpHUrzuJxr){gpsNsdTplu = true;}
      else if(QpHUrzuJxr == DAnYVTBmok){IeeKCEDEDm = true;}
      if(VxMYTsTnGI == qFfttgdKBS){fuiujuglpJ = true;}
      else if(qFfttgdKBS == VxMYTsTnGI){dTEhMrbkdg = true;}
      if(gDPKJdhDbG == TUxRtEtHAh){LzthYcHlsa = true;}
      else if(TUxRtEtHAh == gDPKJdhDbG){iYHhEXkwWT = true;}
      if(IkYWDEJtlw == DuWVDGxyGg){NXlpxNQrct = true;}
      else if(DuWVDGxyGg == IkYWDEJtlw){TTqlyYztJb = true;}
      if(ltukMofdjc == PHFALPzjAc){LtuSbRXcgg = true;}
      if(YxTUezjdOq == JXKoHusoZn){tLzBEhuKnQ = true;}
      if(lxKickYoVO == FnJPnwhJqm){VgxKhHJsxW = true;}
      while(PHFALPzjAc == ltukMofdjc){yTfxlyBVAf = true;}
      while(JXKoHusoZn == JXKoHusoZn){BMGDjiWxGe = true;}
      while(FnJPnwhJqm == FnJPnwhJqm){TGgjTKcSjm = true;}
      if(jfEUCLOxGe == true){jfEUCLOxGe = false;}
      if(EKGWYejhOI == true){EKGWYejhOI = false;}
      if(NHXRbbypLP == true){NHXRbbypLP = false;}
      if(gpsNsdTplu == true){gpsNsdTplu = false;}
      if(fuiujuglpJ == true){fuiujuglpJ = false;}
      if(LzthYcHlsa == true){LzthYcHlsa = false;}
      if(NXlpxNQrct == true){NXlpxNQrct = false;}
      if(LtuSbRXcgg == true){LtuSbRXcgg = false;}
      if(tLzBEhuKnQ == true){tLzBEhuKnQ = false;}
      if(VgxKhHJsxW == true){VgxKhHJsxW = false;}
      if(doIuyQDbGG == true){doIuyQDbGG = false;}
      if(EdFMgBXjkP == true){EdFMgBXjkP = false;}
      if(RFDMYdxjjT == true){RFDMYdxjjT = false;}
      if(IeeKCEDEDm == true){IeeKCEDEDm = false;}
      if(dTEhMrbkdg == true){dTEhMrbkdg = false;}
      if(iYHhEXkwWT == true){iYHhEXkwWT = false;}
      if(TTqlyYztJb == true){TTqlyYztJb = false;}
      if(yTfxlyBVAf == true){yTfxlyBVAf = false;}
      if(BMGDjiWxGe == true){BMGDjiWxGe = false;}
      if(TGgjTKcSjm == true){TGgjTKcSjm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GAOYUMJLCI
{ 
  void lnrPhaXHhe()
  { 
      bool ikmEDSxcoZ = false;
      bool XiwpDNNtoJ = false;
      bool hKBDZJECKh = false;
      bool jNLskUYrCC = false;
      bool ZzXZJFnJNZ = false;
      bool LyXENYijes = false;
      bool NuRHpJWDEh = false;
      bool oVrmjhlasT = false;
      bool VtnkVkpGeL = false;
      bool koMInegPjA = false;
      bool hkFfkpGkUf = false;
      bool mIqKXTGglF = false;
      bool TQXswAIjzF = false;
      bool AVqslkoIAf = false;
      bool eEkzYcxCkT = false;
      bool XAdefRMMij = false;
      bool gWlPeRQxYm = false;
      bool eyfGaPeXTT = false;
      bool CGzegArMNT = false;
      bool XcZPyISVUH = false;
      string mZNMpEYBNn;
      string fgjusXeTki;
      string tcqaIzrHYW;
      string jMGtfZhyWW;
      string DpgruZVsHs;
      string tYPgaKhmDp;
      string MQbqDTZpOT;
      string ogxNeEuzfi;
      string dyAfcLwZSU;
      string qutfKmOpna;
      string AfdnDNaCBW;
      string PiHUMNQwNq;
      string WzWtctlQCq;
      string oEKEiyTLbO;
      string jsXwFHmZTx;
      string WRbxDAJjLJ;
      string aKAJgKXClO;
      string sETzHcbZnU;
      string GMxFUXcNAh;
      string njARnZsNOu;
      if(mZNMpEYBNn == AfdnDNaCBW){ikmEDSxcoZ = true;}
      else if(AfdnDNaCBW == mZNMpEYBNn){hkFfkpGkUf = true;}
      if(fgjusXeTki == PiHUMNQwNq){XiwpDNNtoJ = true;}
      else if(PiHUMNQwNq == fgjusXeTki){mIqKXTGglF = true;}
      if(tcqaIzrHYW == WzWtctlQCq){hKBDZJECKh = true;}
      else if(WzWtctlQCq == tcqaIzrHYW){TQXswAIjzF = true;}
      if(jMGtfZhyWW == oEKEiyTLbO){jNLskUYrCC = true;}
      else if(oEKEiyTLbO == jMGtfZhyWW){AVqslkoIAf = true;}
      if(DpgruZVsHs == jsXwFHmZTx){ZzXZJFnJNZ = true;}
      else if(jsXwFHmZTx == DpgruZVsHs){eEkzYcxCkT = true;}
      if(tYPgaKhmDp == WRbxDAJjLJ){LyXENYijes = true;}
      else if(WRbxDAJjLJ == tYPgaKhmDp){XAdefRMMij = true;}
      if(MQbqDTZpOT == aKAJgKXClO){NuRHpJWDEh = true;}
      else if(aKAJgKXClO == MQbqDTZpOT){gWlPeRQxYm = true;}
      if(ogxNeEuzfi == sETzHcbZnU){oVrmjhlasT = true;}
      if(dyAfcLwZSU == GMxFUXcNAh){VtnkVkpGeL = true;}
      if(qutfKmOpna == njARnZsNOu){koMInegPjA = true;}
      while(sETzHcbZnU == ogxNeEuzfi){eyfGaPeXTT = true;}
      while(GMxFUXcNAh == GMxFUXcNAh){CGzegArMNT = true;}
      while(njARnZsNOu == njARnZsNOu){XcZPyISVUH = true;}
      if(ikmEDSxcoZ == true){ikmEDSxcoZ = false;}
      if(XiwpDNNtoJ == true){XiwpDNNtoJ = false;}
      if(hKBDZJECKh == true){hKBDZJECKh = false;}
      if(jNLskUYrCC == true){jNLskUYrCC = false;}
      if(ZzXZJFnJNZ == true){ZzXZJFnJNZ = false;}
      if(LyXENYijes == true){LyXENYijes = false;}
      if(NuRHpJWDEh == true){NuRHpJWDEh = false;}
      if(oVrmjhlasT == true){oVrmjhlasT = false;}
      if(VtnkVkpGeL == true){VtnkVkpGeL = false;}
      if(koMInegPjA == true){koMInegPjA = false;}
      if(hkFfkpGkUf == true){hkFfkpGkUf = false;}
      if(mIqKXTGglF == true){mIqKXTGglF = false;}
      if(TQXswAIjzF == true){TQXswAIjzF = false;}
      if(AVqslkoIAf == true){AVqslkoIAf = false;}
      if(eEkzYcxCkT == true){eEkzYcxCkT = false;}
      if(XAdefRMMij == true){XAdefRMMij = false;}
      if(gWlPeRQxYm == true){gWlPeRQxYm = false;}
      if(eyfGaPeXTT == true){eyfGaPeXTT = false;}
      if(CGzegArMNT == true){CGzegArMNT = false;}
      if(XcZPyISVUH == true){XcZPyISVUH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PISGAZAIUX
{ 
  void hJiYdOEyee()
  { 
      bool htRhptQQlG = false;
      bool iWINPQahRm = false;
      bool HEhlRqMukK = false;
      bool WVamttJVhd = false;
      bool gqtCsJQJUD = false;
      bool WhDFtdMfQz = false;
      bool hUfaiMwUSU = false;
      bool HEAmFQJesI = false;
      bool ZDahnoSVsQ = false;
      bool hcEhwMLSTf = false;
      bool NupzuRgPzc = false;
      bool TgmHYdtxms = false;
      bool tZaCmdzSqs = false;
      bool FpLMueNblW = false;
      bool HDVPxApwIR = false;
      bool RNfZlmUnLR = false;
      bool ROXGXcUZMt = false;
      bool QSLPkqEKFm = false;
      bool mCJYarJlaI = false;
      bool KYPTFsePrT = false;
      string skawDJVXsa;
      string ihGljbmfZH;
      string DiPcGQxVqO;
      string xPcwUDajpE;
      string buRHWeAWTb;
      string CFHYmKVypl;
      string MzgecSFJRf;
      string ACoVfHQHGa;
      string PaCOMrIDJK;
      string hbtDqbNmeD;
      string ZqEnaAPkse;
      string sNrOWkxSRj;
      string KBzGxXHkeD;
      string scbCAXVNmM;
      string bWKeRTjfgF;
      string euVtsYrxqD;
      string reGpkPlpNy;
      string PjeFImpUoc;
      string nbEYYxHgIb;
      string fYWjTxPUsB;
      if(skawDJVXsa == ZqEnaAPkse){htRhptQQlG = true;}
      else if(ZqEnaAPkse == skawDJVXsa){NupzuRgPzc = true;}
      if(ihGljbmfZH == sNrOWkxSRj){iWINPQahRm = true;}
      else if(sNrOWkxSRj == ihGljbmfZH){TgmHYdtxms = true;}
      if(DiPcGQxVqO == KBzGxXHkeD){HEhlRqMukK = true;}
      else if(KBzGxXHkeD == DiPcGQxVqO){tZaCmdzSqs = true;}
      if(xPcwUDajpE == scbCAXVNmM){WVamttJVhd = true;}
      else if(scbCAXVNmM == xPcwUDajpE){FpLMueNblW = true;}
      if(buRHWeAWTb == bWKeRTjfgF){gqtCsJQJUD = true;}
      else if(bWKeRTjfgF == buRHWeAWTb){HDVPxApwIR = true;}
      if(CFHYmKVypl == euVtsYrxqD){WhDFtdMfQz = true;}
      else if(euVtsYrxqD == CFHYmKVypl){RNfZlmUnLR = true;}
      if(MzgecSFJRf == reGpkPlpNy){hUfaiMwUSU = true;}
      else if(reGpkPlpNy == MzgecSFJRf){ROXGXcUZMt = true;}
      if(ACoVfHQHGa == PjeFImpUoc){HEAmFQJesI = true;}
      if(PaCOMrIDJK == nbEYYxHgIb){ZDahnoSVsQ = true;}
      if(hbtDqbNmeD == fYWjTxPUsB){hcEhwMLSTf = true;}
      while(PjeFImpUoc == ACoVfHQHGa){QSLPkqEKFm = true;}
      while(nbEYYxHgIb == nbEYYxHgIb){mCJYarJlaI = true;}
      while(fYWjTxPUsB == fYWjTxPUsB){KYPTFsePrT = true;}
      if(htRhptQQlG == true){htRhptQQlG = false;}
      if(iWINPQahRm == true){iWINPQahRm = false;}
      if(HEhlRqMukK == true){HEhlRqMukK = false;}
      if(WVamttJVhd == true){WVamttJVhd = false;}
      if(gqtCsJQJUD == true){gqtCsJQJUD = false;}
      if(WhDFtdMfQz == true){WhDFtdMfQz = false;}
      if(hUfaiMwUSU == true){hUfaiMwUSU = false;}
      if(HEAmFQJesI == true){HEAmFQJesI = false;}
      if(ZDahnoSVsQ == true){ZDahnoSVsQ = false;}
      if(hcEhwMLSTf == true){hcEhwMLSTf = false;}
      if(NupzuRgPzc == true){NupzuRgPzc = false;}
      if(TgmHYdtxms == true){TgmHYdtxms = false;}
      if(tZaCmdzSqs == true){tZaCmdzSqs = false;}
      if(FpLMueNblW == true){FpLMueNblW = false;}
      if(HDVPxApwIR == true){HDVPxApwIR = false;}
      if(RNfZlmUnLR == true){RNfZlmUnLR = false;}
      if(ROXGXcUZMt == true){ROXGXcUZMt = false;}
      if(QSLPkqEKFm == true){QSLPkqEKFm = false;}
      if(mCJYarJlaI == true){mCJYarJlaI = false;}
      if(KYPTFsePrT == true){KYPTFsePrT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SGKXLFTQFF
{ 
  void MdcGVEVWjF()
  { 
      bool oYdhZkHijB = false;
      bool ynTQhfXgdG = false;
      bool ocfHifgxRR = false;
      bool byuzHRPpCP = false;
      bool khirDEJioC = false;
      bool uEmShLrVys = false;
      bool EJRSZArTJQ = false;
      bool QhdOVHtnEe = false;
      bool VyIOVWKcRu = false;
      bool YtqILbPQSD = false;
      bool LpZXlNZYxa = false;
      bool REQTWFACwC = false;
      bool oPBNrWpUDt = false;
      bool qcVBSfXkbI = false;
      bool wleqdTcWlF = false;
      bool aNUPOwoMeP = false;
      bool XFUDjoiPBq = false;
      bool hPanFCjKiY = false;
      bool sSiySdIFmV = false;
      bool pLFLjqRbHo = false;
      string SeoIocTSAq;
      string okTViNnxfu;
      string lQebjCmPqY;
      string uOaelZsoaE;
      string PVVSxntaGh;
      string GAxdjCzMXl;
      string oDbbuZKojJ;
      string UyVafPuMew;
      string HLJJRtQwtj;
      string ZfQnOMttWW;
      string dFqwNHdVyU;
      string GmhbddtRKB;
      string INuAinhhMS;
      string UAoIRCTMwJ;
      string PuxYcmynJj;
      string ScjVOPJpNY;
      string ZwJezFxYKb;
      string JgUAkNQVWw;
      string psXcArQTsC;
      string rdzXiTkRZW;
      if(SeoIocTSAq == dFqwNHdVyU){oYdhZkHijB = true;}
      else if(dFqwNHdVyU == SeoIocTSAq){LpZXlNZYxa = true;}
      if(okTViNnxfu == GmhbddtRKB){ynTQhfXgdG = true;}
      else if(GmhbddtRKB == okTViNnxfu){REQTWFACwC = true;}
      if(lQebjCmPqY == INuAinhhMS){ocfHifgxRR = true;}
      else if(INuAinhhMS == lQebjCmPqY){oPBNrWpUDt = true;}
      if(uOaelZsoaE == UAoIRCTMwJ){byuzHRPpCP = true;}
      else if(UAoIRCTMwJ == uOaelZsoaE){qcVBSfXkbI = true;}
      if(PVVSxntaGh == PuxYcmynJj){khirDEJioC = true;}
      else if(PuxYcmynJj == PVVSxntaGh){wleqdTcWlF = true;}
      if(GAxdjCzMXl == ScjVOPJpNY){uEmShLrVys = true;}
      else if(ScjVOPJpNY == GAxdjCzMXl){aNUPOwoMeP = true;}
      if(oDbbuZKojJ == ZwJezFxYKb){EJRSZArTJQ = true;}
      else if(ZwJezFxYKb == oDbbuZKojJ){XFUDjoiPBq = true;}
      if(UyVafPuMew == JgUAkNQVWw){QhdOVHtnEe = true;}
      if(HLJJRtQwtj == psXcArQTsC){VyIOVWKcRu = true;}
      if(ZfQnOMttWW == rdzXiTkRZW){YtqILbPQSD = true;}
      while(JgUAkNQVWw == UyVafPuMew){hPanFCjKiY = true;}
      while(psXcArQTsC == psXcArQTsC){sSiySdIFmV = true;}
      while(rdzXiTkRZW == rdzXiTkRZW){pLFLjqRbHo = true;}
      if(oYdhZkHijB == true){oYdhZkHijB = false;}
      if(ynTQhfXgdG == true){ynTQhfXgdG = false;}
      if(ocfHifgxRR == true){ocfHifgxRR = false;}
      if(byuzHRPpCP == true){byuzHRPpCP = false;}
      if(khirDEJioC == true){khirDEJioC = false;}
      if(uEmShLrVys == true){uEmShLrVys = false;}
      if(EJRSZArTJQ == true){EJRSZArTJQ = false;}
      if(QhdOVHtnEe == true){QhdOVHtnEe = false;}
      if(VyIOVWKcRu == true){VyIOVWKcRu = false;}
      if(YtqILbPQSD == true){YtqILbPQSD = false;}
      if(LpZXlNZYxa == true){LpZXlNZYxa = false;}
      if(REQTWFACwC == true){REQTWFACwC = false;}
      if(oPBNrWpUDt == true){oPBNrWpUDt = false;}
      if(qcVBSfXkbI == true){qcVBSfXkbI = false;}
      if(wleqdTcWlF == true){wleqdTcWlF = false;}
      if(aNUPOwoMeP == true){aNUPOwoMeP = false;}
      if(XFUDjoiPBq == true){XFUDjoiPBq = false;}
      if(hPanFCjKiY == true){hPanFCjKiY = false;}
      if(sSiySdIFmV == true){sSiySdIFmV = false;}
      if(pLFLjqRbHo == true){pLFLjqRbHo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SMQCROJWCD
{ 
  void xMSPzNFpMi()
  { 
      bool plMztLSchp = false;
      bool YgaiLnNwys = false;
      bool hAQPmoFwpF = false;
      bool IfWtDAFxlP = false;
      bool xbFtUOePNa = false;
      bool pgbMDpVwLE = false;
      bool FWlbhsKffL = false;
      bool iQJhwFtVuY = false;
      bool KphPObDJpN = false;
      bool dIkhJapdMb = false;
      bool EyjCqZWtQx = false;
      bool uABltPnWMF = false;
      bool oAoRhZebYU = false;
      bool PQISULFfXo = false;
      bool EJssScHyms = false;
      bool lSQGlEISTR = false;
      bool tuVugerhRi = false;
      bool JIzXAeGwzE = false;
      bool RfoeixABfQ = false;
      bool DmLGtJnyMm = false;
      string aQBVqXXuDb;
      string QAFgujBdqF;
      string MBuCXorJDJ;
      string yTbfZUEEZa;
      string NZDwSKdTcF;
      string rsOJBYUzxB;
      string fOrsdxXYGZ;
      string fwDQqmxziM;
      string LYfyREEReB;
      string AEHYuzhKRU;
      string lEMDZuoyRO;
      string aVPjpGhsbZ;
      string rGtFYaoeUr;
      string EmgNZGMcXV;
      string OGzQZenWin;
      string QnhrcfKGdy;
      string GKcZJmnBKi;
      string tEVFKlGdft;
      string mRwgbPFnkt;
      string uFzZPEcZGl;
      if(aQBVqXXuDb == lEMDZuoyRO){plMztLSchp = true;}
      else if(lEMDZuoyRO == aQBVqXXuDb){EyjCqZWtQx = true;}
      if(QAFgujBdqF == aVPjpGhsbZ){YgaiLnNwys = true;}
      else if(aVPjpGhsbZ == QAFgujBdqF){uABltPnWMF = true;}
      if(MBuCXorJDJ == rGtFYaoeUr){hAQPmoFwpF = true;}
      else if(rGtFYaoeUr == MBuCXorJDJ){oAoRhZebYU = true;}
      if(yTbfZUEEZa == EmgNZGMcXV){IfWtDAFxlP = true;}
      else if(EmgNZGMcXV == yTbfZUEEZa){PQISULFfXo = true;}
      if(NZDwSKdTcF == OGzQZenWin){xbFtUOePNa = true;}
      else if(OGzQZenWin == NZDwSKdTcF){EJssScHyms = true;}
      if(rsOJBYUzxB == QnhrcfKGdy){pgbMDpVwLE = true;}
      else if(QnhrcfKGdy == rsOJBYUzxB){lSQGlEISTR = true;}
      if(fOrsdxXYGZ == GKcZJmnBKi){FWlbhsKffL = true;}
      else if(GKcZJmnBKi == fOrsdxXYGZ){tuVugerhRi = true;}
      if(fwDQqmxziM == tEVFKlGdft){iQJhwFtVuY = true;}
      if(LYfyREEReB == mRwgbPFnkt){KphPObDJpN = true;}
      if(AEHYuzhKRU == uFzZPEcZGl){dIkhJapdMb = true;}
      while(tEVFKlGdft == fwDQqmxziM){JIzXAeGwzE = true;}
      while(mRwgbPFnkt == mRwgbPFnkt){RfoeixABfQ = true;}
      while(uFzZPEcZGl == uFzZPEcZGl){DmLGtJnyMm = true;}
      if(plMztLSchp == true){plMztLSchp = false;}
      if(YgaiLnNwys == true){YgaiLnNwys = false;}
      if(hAQPmoFwpF == true){hAQPmoFwpF = false;}
      if(IfWtDAFxlP == true){IfWtDAFxlP = false;}
      if(xbFtUOePNa == true){xbFtUOePNa = false;}
      if(pgbMDpVwLE == true){pgbMDpVwLE = false;}
      if(FWlbhsKffL == true){FWlbhsKffL = false;}
      if(iQJhwFtVuY == true){iQJhwFtVuY = false;}
      if(KphPObDJpN == true){KphPObDJpN = false;}
      if(dIkhJapdMb == true){dIkhJapdMb = false;}
      if(EyjCqZWtQx == true){EyjCqZWtQx = false;}
      if(uABltPnWMF == true){uABltPnWMF = false;}
      if(oAoRhZebYU == true){oAoRhZebYU = false;}
      if(PQISULFfXo == true){PQISULFfXo = false;}
      if(EJssScHyms == true){EJssScHyms = false;}
      if(lSQGlEISTR == true){lSQGlEISTR = false;}
      if(tuVugerhRi == true){tuVugerhRi = false;}
      if(JIzXAeGwzE == true){JIzXAeGwzE = false;}
      if(RfoeixABfQ == true){RfoeixABfQ = false;}
      if(DmLGtJnyMm == true){DmLGtJnyMm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUVFBCZWYU
{ 
  void OxSehiXlVl()
  { 
      bool YUPFDwKmEr = false;
      bool IozgPjLpOE = false;
      bool OtqMLYxqUr = false;
      bool pqOpOCoXcy = false;
      bool mdoVyObpDu = false;
      bool HAYuDedDte = false;
      bool yTSLCRaIRM = false;
      bool tmMPQkEUNw = false;
      bool wHnZkoRTmj = false;
      bool YldxzTLdTg = false;
      bool nTXpAUmJdR = false;
      bool ZIoxhperaM = false;
      bool zHVhnHIPPx = false;
      bool YaBgIcjxYP = false;
      bool BIoUKQxfPJ = false;
      bool nSCHggxpCr = false;
      bool LXsfrzHHnF = false;
      bool GhTKKqRAWW = false;
      bool KcAGJGXsAb = false;
      bool estfEdPIbK = false;
      string ckmfplYygr;
      string ROqQNgElyx;
      string AisnKoCwqO;
      string bDYBbCQRtX;
      string HsYzhDLDhA;
      string PfhJctqyUB;
      string icHRPOpooL;
      string PlqZpGKsGH;
      string dyOpywUPYh;
      string KSxroelGjS;
      string NVOVjdnHTV;
      string jxrNXjNQTT;
      string tZQGAxoykK;
      string TDJmtIjrFT;
      string HMwCyMZiUE;
      string QVlPYmEHUm;
      string ooWICfnFTP;
      string AUKzLgdOIn;
      string XFdgtyQtNG;
      string DbWSeSpmzR;
      if(ckmfplYygr == NVOVjdnHTV){YUPFDwKmEr = true;}
      else if(NVOVjdnHTV == ckmfplYygr){nTXpAUmJdR = true;}
      if(ROqQNgElyx == jxrNXjNQTT){IozgPjLpOE = true;}
      else if(jxrNXjNQTT == ROqQNgElyx){ZIoxhperaM = true;}
      if(AisnKoCwqO == tZQGAxoykK){OtqMLYxqUr = true;}
      else if(tZQGAxoykK == AisnKoCwqO){zHVhnHIPPx = true;}
      if(bDYBbCQRtX == TDJmtIjrFT){pqOpOCoXcy = true;}
      else if(TDJmtIjrFT == bDYBbCQRtX){YaBgIcjxYP = true;}
      if(HsYzhDLDhA == HMwCyMZiUE){mdoVyObpDu = true;}
      else if(HMwCyMZiUE == HsYzhDLDhA){BIoUKQxfPJ = true;}
      if(PfhJctqyUB == QVlPYmEHUm){HAYuDedDte = true;}
      else if(QVlPYmEHUm == PfhJctqyUB){nSCHggxpCr = true;}
      if(icHRPOpooL == ooWICfnFTP){yTSLCRaIRM = true;}
      else if(ooWICfnFTP == icHRPOpooL){LXsfrzHHnF = true;}
      if(PlqZpGKsGH == AUKzLgdOIn){tmMPQkEUNw = true;}
      if(dyOpywUPYh == XFdgtyQtNG){wHnZkoRTmj = true;}
      if(KSxroelGjS == DbWSeSpmzR){YldxzTLdTg = true;}
      while(AUKzLgdOIn == PlqZpGKsGH){GhTKKqRAWW = true;}
      while(XFdgtyQtNG == XFdgtyQtNG){KcAGJGXsAb = true;}
      while(DbWSeSpmzR == DbWSeSpmzR){estfEdPIbK = true;}
      if(YUPFDwKmEr == true){YUPFDwKmEr = false;}
      if(IozgPjLpOE == true){IozgPjLpOE = false;}
      if(OtqMLYxqUr == true){OtqMLYxqUr = false;}
      if(pqOpOCoXcy == true){pqOpOCoXcy = false;}
      if(mdoVyObpDu == true){mdoVyObpDu = false;}
      if(HAYuDedDte == true){HAYuDedDte = false;}
      if(yTSLCRaIRM == true){yTSLCRaIRM = false;}
      if(tmMPQkEUNw == true){tmMPQkEUNw = false;}
      if(wHnZkoRTmj == true){wHnZkoRTmj = false;}
      if(YldxzTLdTg == true){YldxzTLdTg = false;}
      if(nTXpAUmJdR == true){nTXpAUmJdR = false;}
      if(ZIoxhperaM == true){ZIoxhperaM = false;}
      if(zHVhnHIPPx == true){zHVhnHIPPx = false;}
      if(YaBgIcjxYP == true){YaBgIcjxYP = false;}
      if(BIoUKQxfPJ == true){BIoUKQxfPJ = false;}
      if(nSCHggxpCr == true){nSCHggxpCr = false;}
      if(LXsfrzHHnF == true){LXsfrzHHnF = false;}
      if(GhTKKqRAWW == true){GhTKKqRAWW = false;}
      if(KcAGJGXsAb == true){KcAGJGXsAb = false;}
      if(estfEdPIbK == true){estfEdPIbK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDKHYGGRNL
{ 
  void mElndlcgBZ()
  { 
      bool ZqdKCQaKPl = false;
      bool BtcQUkVKdy = false;
      bool bAqiBbYOsc = false;
      bool PYXRzEZjYM = false;
      bool EMAwPQrgdx = false;
      bool tiagGYAtJa = false;
      bool rMQlWbWKQQ = false;
      bool LlkRsPAuSk = false;
      bool irkuigyqLa = false;
      bool EeaxTruNYn = false;
      bool thPNlHxImp = false;
      bool YFaXrAaVDp = false;
      bool cezpLfLmxB = false;
      bool UlVdpBbWJa = false;
      bool ioEUCyDCFT = false;
      bool QYKiKOhZBF = false;
      bool wKKkVliwgq = false;
      bool XEMbHnadnN = false;
      bool bJgdjualSb = false;
      bool SCVDeXdSzP = false;
      string hlAonNuccz;
      string UBNSaUHpnL;
      string aelhWzBsFf;
      string IlXrsfmwgL;
      string yoibTBfmAL;
      string jrqkjDzRSn;
      string MBWwqidUYu;
      string hLJbMluJOU;
      string TNrtwPtlIp;
      string fUcrzwRlkj;
      string XKNFdXhOYy;
      string HpDyUyJcAa;
      string nrMiPMiRcQ;
      string TIYdxIAmPX;
      string geMJhpQeWA;
      string mnlJufxdpQ;
      string oQlHdzQZAM;
      string xVNbsIeDBY;
      string wDtbcfWPhR;
      string KVxyiQsFei;
      if(hlAonNuccz == XKNFdXhOYy){ZqdKCQaKPl = true;}
      else if(XKNFdXhOYy == hlAonNuccz){thPNlHxImp = true;}
      if(UBNSaUHpnL == HpDyUyJcAa){BtcQUkVKdy = true;}
      else if(HpDyUyJcAa == UBNSaUHpnL){YFaXrAaVDp = true;}
      if(aelhWzBsFf == nrMiPMiRcQ){bAqiBbYOsc = true;}
      else if(nrMiPMiRcQ == aelhWzBsFf){cezpLfLmxB = true;}
      if(IlXrsfmwgL == TIYdxIAmPX){PYXRzEZjYM = true;}
      else if(TIYdxIAmPX == IlXrsfmwgL){UlVdpBbWJa = true;}
      if(yoibTBfmAL == geMJhpQeWA){EMAwPQrgdx = true;}
      else if(geMJhpQeWA == yoibTBfmAL){ioEUCyDCFT = true;}
      if(jrqkjDzRSn == mnlJufxdpQ){tiagGYAtJa = true;}
      else if(mnlJufxdpQ == jrqkjDzRSn){QYKiKOhZBF = true;}
      if(MBWwqidUYu == oQlHdzQZAM){rMQlWbWKQQ = true;}
      else if(oQlHdzQZAM == MBWwqidUYu){wKKkVliwgq = true;}
      if(hLJbMluJOU == xVNbsIeDBY){LlkRsPAuSk = true;}
      if(TNrtwPtlIp == wDtbcfWPhR){irkuigyqLa = true;}
      if(fUcrzwRlkj == KVxyiQsFei){EeaxTruNYn = true;}
      while(xVNbsIeDBY == hLJbMluJOU){XEMbHnadnN = true;}
      while(wDtbcfWPhR == wDtbcfWPhR){bJgdjualSb = true;}
      while(KVxyiQsFei == KVxyiQsFei){SCVDeXdSzP = true;}
      if(ZqdKCQaKPl == true){ZqdKCQaKPl = false;}
      if(BtcQUkVKdy == true){BtcQUkVKdy = false;}
      if(bAqiBbYOsc == true){bAqiBbYOsc = false;}
      if(PYXRzEZjYM == true){PYXRzEZjYM = false;}
      if(EMAwPQrgdx == true){EMAwPQrgdx = false;}
      if(tiagGYAtJa == true){tiagGYAtJa = false;}
      if(rMQlWbWKQQ == true){rMQlWbWKQQ = false;}
      if(LlkRsPAuSk == true){LlkRsPAuSk = false;}
      if(irkuigyqLa == true){irkuigyqLa = false;}
      if(EeaxTruNYn == true){EeaxTruNYn = false;}
      if(thPNlHxImp == true){thPNlHxImp = false;}
      if(YFaXrAaVDp == true){YFaXrAaVDp = false;}
      if(cezpLfLmxB == true){cezpLfLmxB = false;}
      if(UlVdpBbWJa == true){UlVdpBbWJa = false;}
      if(ioEUCyDCFT == true){ioEUCyDCFT = false;}
      if(QYKiKOhZBF == true){QYKiKOhZBF = false;}
      if(wKKkVliwgq == true){wKKkVliwgq = false;}
      if(XEMbHnadnN == true){XEMbHnadnN = false;}
      if(bJgdjualSb == true){bJgdjualSb = false;}
      if(SCVDeXdSzP == true){SCVDeXdSzP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URYSTQVYZJ
{ 
  void NZtkJaqycd()
  { 
      bool RhWQKxerhY = false;
      bool GRRFSytLla = false;
      bool ahjUuozzCt = false;
      bool LjAMOEztKe = false;
      bool dkiJxxxKeu = false;
      bool cBgiwiyBUU = false;
      bool xeomNVREpN = false;
      bool zAAHxpzZWy = false;
      bool roUHRKDRQf = false;
      bool GxYogyuwua = false;
      bool frTQwbAZkG = false;
      bool jXeWbHKhUD = false;
      bool SznKGCbKZy = false;
      bool tCeuRzVDLp = false;
      bool JcfJuhRBNY = false;
      bool nNarIfDJJs = false;
      bool AozmLgsiFc = false;
      bool lGVesoSdOY = false;
      bool jZxAJgbmmk = false;
      bool uLtRoUdsyO = false;
      string ZGbjNUSaEx;
      string eiTBAcodWK;
      string miajhgMKcq;
      string gCKyoQplLw;
      string nZPMpUFcVf;
      string oKrZhpfrBf;
      string HIxNQbXVLj;
      string lCSZVMTNsM;
      string bjoxBVKkPy;
      string jykfnfbBuN;
      string xiQlslrRDU;
      string WSynDXSALu;
      string QlFNzmRmko;
      string kSRfPsSCDO;
      string cshtbRAwbP;
      string NboAxKcDmF;
      string UFgOjEASYK;
      string FPxxRXEKkg;
      string mVKUbIcRiE;
      string PPPxtWMTKX;
      if(ZGbjNUSaEx == xiQlslrRDU){RhWQKxerhY = true;}
      else if(xiQlslrRDU == ZGbjNUSaEx){frTQwbAZkG = true;}
      if(eiTBAcodWK == WSynDXSALu){GRRFSytLla = true;}
      else if(WSynDXSALu == eiTBAcodWK){jXeWbHKhUD = true;}
      if(miajhgMKcq == QlFNzmRmko){ahjUuozzCt = true;}
      else if(QlFNzmRmko == miajhgMKcq){SznKGCbKZy = true;}
      if(gCKyoQplLw == kSRfPsSCDO){LjAMOEztKe = true;}
      else if(kSRfPsSCDO == gCKyoQplLw){tCeuRzVDLp = true;}
      if(nZPMpUFcVf == cshtbRAwbP){dkiJxxxKeu = true;}
      else if(cshtbRAwbP == nZPMpUFcVf){JcfJuhRBNY = true;}
      if(oKrZhpfrBf == NboAxKcDmF){cBgiwiyBUU = true;}
      else if(NboAxKcDmF == oKrZhpfrBf){nNarIfDJJs = true;}
      if(HIxNQbXVLj == UFgOjEASYK){xeomNVREpN = true;}
      else if(UFgOjEASYK == HIxNQbXVLj){AozmLgsiFc = true;}
      if(lCSZVMTNsM == FPxxRXEKkg){zAAHxpzZWy = true;}
      if(bjoxBVKkPy == mVKUbIcRiE){roUHRKDRQf = true;}
      if(jykfnfbBuN == PPPxtWMTKX){GxYogyuwua = true;}
      while(FPxxRXEKkg == lCSZVMTNsM){lGVesoSdOY = true;}
      while(mVKUbIcRiE == mVKUbIcRiE){jZxAJgbmmk = true;}
      while(PPPxtWMTKX == PPPxtWMTKX){uLtRoUdsyO = true;}
      if(RhWQKxerhY == true){RhWQKxerhY = false;}
      if(GRRFSytLla == true){GRRFSytLla = false;}
      if(ahjUuozzCt == true){ahjUuozzCt = false;}
      if(LjAMOEztKe == true){LjAMOEztKe = false;}
      if(dkiJxxxKeu == true){dkiJxxxKeu = false;}
      if(cBgiwiyBUU == true){cBgiwiyBUU = false;}
      if(xeomNVREpN == true){xeomNVREpN = false;}
      if(zAAHxpzZWy == true){zAAHxpzZWy = false;}
      if(roUHRKDRQf == true){roUHRKDRQf = false;}
      if(GxYogyuwua == true){GxYogyuwua = false;}
      if(frTQwbAZkG == true){frTQwbAZkG = false;}
      if(jXeWbHKhUD == true){jXeWbHKhUD = false;}
      if(SznKGCbKZy == true){SznKGCbKZy = false;}
      if(tCeuRzVDLp == true){tCeuRzVDLp = false;}
      if(JcfJuhRBNY == true){JcfJuhRBNY = false;}
      if(nNarIfDJJs == true){nNarIfDJJs = false;}
      if(AozmLgsiFc == true){AozmLgsiFc = false;}
      if(lGVesoSdOY == true){lGVesoSdOY = false;}
      if(jZxAJgbmmk == true){jZxAJgbmmk = false;}
      if(uLtRoUdsyO == true){uLtRoUdsyO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKYTAQSDAJ
{ 
  void IhwfuFLOTV()
  { 
      bool JMCPLrJuWQ = false;
      bool HymocgMzte = false;
      bool qjiJcjADyG = false;
      bool mxpehoksUA = false;
      bool ndzBrsDhIk = false;
      bool wOuFzYdsmb = false;
      bool qGxPdJIHHm = false;
      bool wSdtpNjgQj = false;
      bool fRtNKYBjeI = false;
      bool KqFsIhgjXh = false;
      bool juZVockBPl = false;
      bool nwbDuZMjFF = false;
      bool HXczbEMkkI = false;
      bool fAJhzkqXYg = false;
      bool mAUrTOPCxi = false;
      bool UweSZMSasj = false;
      bool PzQHFnmsEK = false;
      bool hnLXRHDjeN = false;
      bool oKnBmjVqHm = false;
      bool RPenQniNmf = false;
      string UWlqiWtiLP;
      string KTwteCLwBR;
      string UVOAWULXUB;
      string YWZRHolohW;
      string PSXXBJqZdK;
      string rddycyHkUN;
      string LVOKpntdmo;
      string PVOeCBxqzM;
      string dlsJIuraoI;
      string gAUULsDNhN;
      string PNlntVPzwa;
      string BQlHjYcECu;
      string uSndHPBsSI;
      string xjJkxPzEPl;
      string esdNHQNNjl;
      string PzKlSwYIgd;
      string UVfmcQHBKT;
      string ZXoPPBnZVq;
      string BnJgryYWSA;
      string qpXkRINpjq;
      if(UWlqiWtiLP == PNlntVPzwa){JMCPLrJuWQ = true;}
      else if(PNlntVPzwa == UWlqiWtiLP){juZVockBPl = true;}
      if(KTwteCLwBR == BQlHjYcECu){HymocgMzte = true;}
      else if(BQlHjYcECu == KTwteCLwBR){nwbDuZMjFF = true;}
      if(UVOAWULXUB == uSndHPBsSI){qjiJcjADyG = true;}
      else if(uSndHPBsSI == UVOAWULXUB){HXczbEMkkI = true;}
      if(YWZRHolohW == xjJkxPzEPl){mxpehoksUA = true;}
      else if(xjJkxPzEPl == YWZRHolohW){fAJhzkqXYg = true;}
      if(PSXXBJqZdK == esdNHQNNjl){ndzBrsDhIk = true;}
      else if(esdNHQNNjl == PSXXBJqZdK){mAUrTOPCxi = true;}
      if(rddycyHkUN == PzKlSwYIgd){wOuFzYdsmb = true;}
      else if(PzKlSwYIgd == rddycyHkUN){UweSZMSasj = true;}
      if(LVOKpntdmo == UVfmcQHBKT){qGxPdJIHHm = true;}
      else if(UVfmcQHBKT == LVOKpntdmo){PzQHFnmsEK = true;}
      if(PVOeCBxqzM == ZXoPPBnZVq){wSdtpNjgQj = true;}
      if(dlsJIuraoI == BnJgryYWSA){fRtNKYBjeI = true;}
      if(gAUULsDNhN == qpXkRINpjq){KqFsIhgjXh = true;}
      while(ZXoPPBnZVq == PVOeCBxqzM){hnLXRHDjeN = true;}
      while(BnJgryYWSA == BnJgryYWSA){oKnBmjVqHm = true;}
      while(qpXkRINpjq == qpXkRINpjq){RPenQniNmf = true;}
      if(JMCPLrJuWQ == true){JMCPLrJuWQ = false;}
      if(HymocgMzte == true){HymocgMzte = false;}
      if(qjiJcjADyG == true){qjiJcjADyG = false;}
      if(mxpehoksUA == true){mxpehoksUA = false;}
      if(ndzBrsDhIk == true){ndzBrsDhIk = false;}
      if(wOuFzYdsmb == true){wOuFzYdsmb = false;}
      if(qGxPdJIHHm == true){qGxPdJIHHm = false;}
      if(wSdtpNjgQj == true){wSdtpNjgQj = false;}
      if(fRtNKYBjeI == true){fRtNKYBjeI = false;}
      if(KqFsIhgjXh == true){KqFsIhgjXh = false;}
      if(juZVockBPl == true){juZVockBPl = false;}
      if(nwbDuZMjFF == true){nwbDuZMjFF = false;}
      if(HXczbEMkkI == true){HXczbEMkkI = false;}
      if(fAJhzkqXYg == true){fAJhzkqXYg = false;}
      if(mAUrTOPCxi == true){mAUrTOPCxi = false;}
      if(UweSZMSasj == true){UweSZMSasj = false;}
      if(PzQHFnmsEK == true){PzQHFnmsEK = false;}
      if(hnLXRHDjeN == true){hnLXRHDjeN = false;}
      if(oKnBmjVqHm == true){oKnBmjVqHm = false;}
      if(RPenQniNmf == true){RPenQniNmf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MRJBNMOMTP
{ 
  void JlIwXpZCDZ()
  { 
      bool LWeDkngaAi = false;
      bool HwVZwceMDj = false;
      bool KNbWNCMZjs = false;
      bool OwFzTFluzn = false;
      bool muyzaJfsCW = false;
      bool RbRjkxtIpi = false;
      bool aGpGTKpWFp = false;
      bool pjMOwPObuE = false;
      bool VSXMaleUOV = false;
      bool LdEQMfEqeP = false;
      bool SJnLfhOCmV = false;
      bool iRMlMIidfg = false;
      bool fVIieMewCQ = false;
      bool KWwekMeLfs = false;
      bool WbgrmsQSDE = false;
      bool xaLyjxBEgT = false;
      bool CSAWKMUgAA = false;
      bool dXxmKEnPwk = false;
      bool wLrxTjKyun = false;
      bool LZdMpEbKhZ = false;
      string ZLWuIIMHQN;
      string oUAAOPMDrh;
      string YlGoiPXYHr;
      string SgaCghtKMA;
      string MzNFnkSLpD;
      string ApSxBnFgLs;
      string kmzXuHtyTg;
      string VCpqVYXBBy;
      string wLhErbOcAs;
      string bMyTPYApKf;
      string pTrJgxAabc;
      string PDfNwYEueS;
      string rRxZEJDVbw;
      string YhqVHbTYWt;
      string bnAXdYgkXp;
      string TELqmYVRFX;
      string tdyfDhMKFT;
      string EfXjqEQZuf;
      string bRykbTWzhi;
      string FCTyAxoUTw;
      if(ZLWuIIMHQN == pTrJgxAabc){LWeDkngaAi = true;}
      else if(pTrJgxAabc == ZLWuIIMHQN){SJnLfhOCmV = true;}
      if(oUAAOPMDrh == PDfNwYEueS){HwVZwceMDj = true;}
      else if(PDfNwYEueS == oUAAOPMDrh){iRMlMIidfg = true;}
      if(YlGoiPXYHr == rRxZEJDVbw){KNbWNCMZjs = true;}
      else if(rRxZEJDVbw == YlGoiPXYHr){fVIieMewCQ = true;}
      if(SgaCghtKMA == YhqVHbTYWt){OwFzTFluzn = true;}
      else if(YhqVHbTYWt == SgaCghtKMA){KWwekMeLfs = true;}
      if(MzNFnkSLpD == bnAXdYgkXp){muyzaJfsCW = true;}
      else if(bnAXdYgkXp == MzNFnkSLpD){WbgrmsQSDE = true;}
      if(ApSxBnFgLs == TELqmYVRFX){RbRjkxtIpi = true;}
      else if(TELqmYVRFX == ApSxBnFgLs){xaLyjxBEgT = true;}
      if(kmzXuHtyTg == tdyfDhMKFT){aGpGTKpWFp = true;}
      else if(tdyfDhMKFT == kmzXuHtyTg){CSAWKMUgAA = true;}
      if(VCpqVYXBBy == EfXjqEQZuf){pjMOwPObuE = true;}
      if(wLhErbOcAs == bRykbTWzhi){VSXMaleUOV = true;}
      if(bMyTPYApKf == FCTyAxoUTw){LdEQMfEqeP = true;}
      while(EfXjqEQZuf == VCpqVYXBBy){dXxmKEnPwk = true;}
      while(bRykbTWzhi == bRykbTWzhi){wLrxTjKyun = true;}
      while(FCTyAxoUTw == FCTyAxoUTw){LZdMpEbKhZ = true;}
      if(LWeDkngaAi == true){LWeDkngaAi = false;}
      if(HwVZwceMDj == true){HwVZwceMDj = false;}
      if(KNbWNCMZjs == true){KNbWNCMZjs = false;}
      if(OwFzTFluzn == true){OwFzTFluzn = false;}
      if(muyzaJfsCW == true){muyzaJfsCW = false;}
      if(RbRjkxtIpi == true){RbRjkxtIpi = false;}
      if(aGpGTKpWFp == true){aGpGTKpWFp = false;}
      if(pjMOwPObuE == true){pjMOwPObuE = false;}
      if(VSXMaleUOV == true){VSXMaleUOV = false;}
      if(LdEQMfEqeP == true){LdEQMfEqeP = false;}
      if(SJnLfhOCmV == true){SJnLfhOCmV = false;}
      if(iRMlMIidfg == true){iRMlMIidfg = false;}
      if(fVIieMewCQ == true){fVIieMewCQ = false;}
      if(KWwekMeLfs == true){KWwekMeLfs = false;}
      if(WbgrmsQSDE == true){WbgrmsQSDE = false;}
      if(xaLyjxBEgT == true){xaLyjxBEgT = false;}
      if(CSAWKMUgAA == true){CSAWKMUgAA = false;}
      if(dXxmKEnPwk == true){dXxmKEnPwk = false;}
      if(wLrxTjKyun == true){wLrxTjKyun = false;}
      if(LZdMpEbKhZ == true){LZdMpEbKhZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CXJLKHAULC
{ 
  void GmXMVImVhS()
  { 
      bool cKnzbwhDMR = false;
      bool EpauHemwLu = false;
      bool AddLeWskYZ = false;
      bool tYYMNeGuTB = false;
      bool bWoXyGdiaU = false;
      bool BlujDyfbTE = false;
      bool DxdlWfROgc = false;
      bool YqcJSdoGNX = false;
      bool sKJEYIcnIO = false;
      bool ydaPyerCAS = false;
      bool oOCyuJJlRY = false;
      bool JZOuKsmZNO = false;
      bool CcFRetQMKm = false;
      bool llFtidHLIO = false;
      bool zqWiFYPfEF = false;
      bool qRnlQMJkSB = false;
      bool swadmXTTMg = false;
      bool kbRzOLFVMG = false;
      bool ekIFuTxTdW = false;
      bool UWrHUDPswg = false;
      string MUIKxlGdaD;
      string UmgWukgDOd;
      string XERPoDdOac;
      string rsynRYdbnk;
      string BGZYcVbsJZ;
      string dSWEjIDsVt;
      string IrCyLbosFW;
      string GEPcbQdrmT;
      string ajEAzZVsDJ;
      string UkGtcIDbNB;
      string finmTYCscS;
      string dLFCSYnBzl;
      string FwowBUyUAS;
      string MCdkmqwQgZ;
      string WbQkeJeDaE;
      string UCbbujtqly;
      string ZhsJFagTPb;
      string bXTYOdeEQq;
      string putwyKZCpD;
      string xEdiAoiGeE;
      if(MUIKxlGdaD == finmTYCscS){cKnzbwhDMR = true;}
      else if(finmTYCscS == MUIKxlGdaD){oOCyuJJlRY = true;}
      if(UmgWukgDOd == dLFCSYnBzl){EpauHemwLu = true;}
      else if(dLFCSYnBzl == UmgWukgDOd){JZOuKsmZNO = true;}
      if(XERPoDdOac == FwowBUyUAS){AddLeWskYZ = true;}
      else if(FwowBUyUAS == XERPoDdOac){CcFRetQMKm = true;}
      if(rsynRYdbnk == MCdkmqwQgZ){tYYMNeGuTB = true;}
      else if(MCdkmqwQgZ == rsynRYdbnk){llFtidHLIO = true;}
      if(BGZYcVbsJZ == WbQkeJeDaE){bWoXyGdiaU = true;}
      else if(WbQkeJeDaE == BGZYcVbsJZ){zqWiFYPfEF = true;}
      if(dSWEjIDsVt == UCbbujtqly){BlujDyfbTE = true;}
      else if(UCbbujtqly == dSWEjIDsVt){qRnlQMJkSB = true;}
      if(IrCyLbosFW == ZhsJFagTPb){DxdlWfROgc = true;}
      else if(ZhsJFagTPb == IrCyLbosFW){swadmXTTMg = true;}
      if(GEPcbQdrmT == bXTYOdeEQq){YqcJSdoGNX = true;}
      if(ajEAzZVsDJ == putwyKZCpD){sKJEYIcnIO = true;}
      if(UkGtcIDbNB == xEdiAoiGeE){ydaPyerCAS = true;}
      while(bXTYOdeEQq == GEPcbQdrmT){kbRzOLFVMG = true;}
      while(putwyKZCpD == putwyKZCpD){ekIFuTxTdW = true;}
      while(xEdiAoiGeE == xEdiAoiGeE){UWrHUDPswg = true;}
      if(cKnzbwhDMR == true){cKnzbwhDMR = false;}
      if(EpauHemwLu == true){EpauHemwLu = false;}
      if(AddLeWskYZ == true){AddLeWskYZ = false;}
      if(tYYMNeGuTB == true){tYYMNeGuTB = false;}
      if(bWoXyGdiaU == true){bWoXyGdiaU = false;}
      if(BlujDyfbTE == true){BlujDyfbTE = false;}
      if(DxdlWfROgc == true){DxdlWfROgc = false;}
      if(YqcJSdoGNX == true){YqcJSdoGNX = false;}
      if(sKJEYIcnIO == true){sKJEYIcnIO = false;}
      if(ydaPyerCAS == true){ydaPyerCAS = false;}
      if(oOCyuJJlRY == true){oOCyuJJlRY = false;}
      if(JZOuKsmZNO == true){JZOuKsmZNO = false;}
      if(CcFRetQMKm == true){CcFRetQMKm = false;}
      if(llFtidHLIO == true){llFtidHLIO = false;}
      if(zqWiFYPfEF == true){zqWiFYPfEF = false;}
      if(qRnlQMJkSB == true){qRnlQMJkSB = false;}
      if(swadmXTTMg == true){swadmXTTMg = false;}
      if(kbRzOLFVMG == true){kbRzOLFVMG = false;}
      if(ekIFuTxTdW == true){ekIFuTxTdW = false;}
      if(UWrHUDPswg == true){UWrHUDPswg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWGPRUJZKS
{ 
  void HkRCnmtxBy()
  { 
      bool qWoBKhAMMN = false;
      bool jiLsPFXZNs = false;
      bool qdJsPqjoFC = false;
      bool yBtoiekeQZ = false;
      bool lyOteKtdFK = false;
      bool VwWTPMMwlS = false;
      bool xKHKPhnVKk = false;
      bool TsImGrPOOF = false;
      bool xGjtgCeZZW = false;
      bool RorybaqDew = false;
      bool VYSTqcmiMW = false;
      bool wxhgVpaNdM = false;
      bool DNumSeAKLf = false;
      bool BMjRiXmPDD = false;
      bool PwMCZTHLck = false;
      bool AcZRsHdfBL = false;
      bool bbXgVjNPyx = false;
      bool CKJZxHAsNy = false;
      bool XohZeXlRYa = false;
      bool tHOqbmYfgp = false;
      string OOWEJkWmpd;
      string xtYJcNkQHN;
      string HUjuTpzmsU;
      string mwfCyRYYWF;
      string ZCYucZNYCw;
      string RqmHhseakT;
      string litVqBOVLK;
      string nMtCnFwnRt;
      string bajwCwIXUF;
      string mxnCSpICEa;
      string KrNrIFwkSb;
      string wpIprKzxTu;
      string rpAFXpXqiy;
      string wtjqijNqmx;
      string zXEsIxnxKH;
      string pKiIhUqHTR;
      string gFBUeCFRHI;
      string xHKVwUkHwa;
      string BagaHlLaIO;
      string sFWUQsVjNG;
      if(OOWEJkWmpd == KrNrIFwkSb){qWoBKhAMMN = true;}
      else if(KrNrIFwkSb == OOWEJkWmpd){VYSTqcmiMW = true;}
      if(xtYJcNkQHN == wpIprKzxTu){jiLsPFXZNs = true;}
      else if(wpIprKzxTu == xtYJcNkQHN){wxhgVpaNdM = true;}
      if(HUjuTpzmsU == rpAFXpXqiy){qdJsPqjoFC = true;}
      else if(rpAFXpXqiy == HUjuTpzmsU){DNumSeAKLf = true;}
      if(mwfCyRYYWF == wtjqijNqmx){yBtoiekeQZ = true;}
      else if(wtjqijNqmx == mwfCyRYYWF){BMjRiXmPDD = true;}
      if(ZCYucZNYCw == zXEsIxnxKH){lyOteKtdFK = true;}
      else if(zXEsIxnxKH == ZCYucZNYCw){PwMCZTHLck = true;}
      if(RqmHhseakT == pKiIhUqHTR){VwWTPMMwlS = true;}
      else if(pKiIhUqHTR == RqmHhseakT){AcZRsHdfBL = true;}
      if(litVqBOVLK == gFBUeCFRHI){xKHKPhnVKk = true;}
      else if(gFBUeCFRHI == litVqBOVLK){bbXgVjNPyx = true;}
      if(nMtCnFwnRt == xHKVwUkHwa){TsImGrPOOF = true;}
      if(bajwCwIXUF == BagaHlLaIO){xGjtgCeZZW = true;}
      if(mxnCSpICEa == sFWUQsVjNG){RorybaqDew = true;}
      while(xHKVwUkHwa == nMtCnFwnRt){CKJZxHAsNy = true;}
      while(BagaHlLaIO == BagaHlLaIO){XohZeXlRYa = true;}
      while(sFWUQsVjNG == sFWUQsVjNG){tHOqbmYfgp = true;}
      if(qWoBKhAMMN == true){qWoBKhAMMN = false;}
      if(jiLsPFXZNs == true){jiLsPFXZNs = false;}
      if(qdJsPqjoFC == true){qdJsPqjoFC = false;}
      if(yBtoiekeQZ == true){yBtoiekeQZ = false;}
      if(lyOteKtdFK == true){lyOteKtdFK = false;}
      if(VwWTPMMwlS == true){VwWTPMMwlS = false;}
      if(xKHKPhnVKk == true){xKHKPhnVKk = false;}
      if(TsImGrPOOF == true){TsImGrPOOF = false;}
      if(xGjtgCeZZW == true){xGjtgCeZZW = false;}
      if(RorybaqDew == true){RorybaqDew = false;}
      if(VYSTqcmiMW == true){VYSTqcmiMW = false;}
      if(wxhgVpaNdM == true){wxhgVpaNdM = false;}
      if(DNumSeAKLf == true){DNumSeAKLf = false;}
      if(BMjRiXmPDD == true){BMjRiXmPDD = false;}
      if(PwMCZTHLck == true){PwMCZTHLck = false;}
      if(AcZRsHdfBL == true){AcZRsHdfBL = false;}
      if(bbXgVjNPyx == true){bbXgVjNPyx = false;}
      if(CKJZxHAsNy == true){CKJZxHAsNy = false;}
      if(XohZeXlRYa == true){XohZeXlRYa = false;}
      if(tHOqbmYfgp == true){tHOqbmYfgp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULRLHSTNBS
{ 
  void LizwBiinyK()
  { 
      bool yCesgSKfXL = false;
      bool uGsBtkyNOr = false;
      bool VsnaGSaYDE = false;
      bool ZePdbVnRyb = false;
      bool PqexMIOwRg = false;
      bool YhOZOEOElN = false;
      bool rkcSkQpOYX = false;
      bool xfPmceNpOy = false;
      bool EdHVfrQpPW = false;
      bool HifkidNMMw = false;
      bool SAWsirRawj = false;
      bool qXonJNdGmr = false;
      bool zAyBQNAeEz = false;
      bool QBdReDHNmm = false;
      bool aosffitqaU = false;
      bool AHYTwRBUcV = false;
      bool rmWxSotXIF = false;
      bool GPTzRKGSVg = false;
      bool TIDiyIbJVM = false;
      bool BljRumSwMq = false;
      string EwgrBzycrr;
      string TkpQNdFwmh;
      string qSoImNwejn;
      string SmGxfAONdB;
      string GHyfYcBiJJ;
      string dCRWXlHYEm;
      string DSsDYfeskN;
      string PqRkajTJjJ;
      string MMVaJQUiYt;
      string soJpynOuGr;
      string yIywtmjfwn;
      string RyotapxRsH;
      string KuTqUZhaml;
      string VYCqLEOYfW;
      string fomkbtAOPH;
      string qwCzhDoHbT;
      string EJsJSrwxiW;
      string aXlVbVHhOZ;
      string YSLeuZWCJH;
      string PHxMSWucSj;
      if(EwgrBzycrr == yIywtmjfwn){yCesgSKfXL = true;}
      else if(yIywtmjfwn == EwgrBzycrr){SAWsirRawj = true;}
      if(TkpQNdFwmh == RyotapxRsH){uGsBtkyNOr = true;}
      else if(RyotapxRsH == TkpQNdFwmh){qXonJNdGmr = true;}
      if(qSoImNwejn == KuTqUZhaml){VsnaGSaYDE = true;}
      else if(KuTqUZhaml == qSoImNwejn){zAyBQNAeEz = true;}
      if(SmGxfAONdB == VYCqLEOYfW){ZePdbVnRyb = true;}
      else if(VYCqLEOYfW == SmGxfAONdB){QBdReDHNmm = true;}
      if(GHyfYcBiJJ == fomkbtAOPH){PqexMIOwRg = true;}
      else if(fomkbtAOPH == GHyfYcBiJJ){aosffitqaU = true;}
      if(dCRWXlHYEm == qwCzhDoHbT){YhOZOEOElN = true;}
      else if(qwCzhDoHbT == dCRWXlHYEm){AHYTwRBUcV = true;}
      if(DSsDYfeskN == EJsJSrwxiW){rkcSkQpOYX = true;}
      else if(EJsJSrwxiW == DSsDYfeskN){rmWxSotXIF = true;}
      if(PqRkajTJjJ == aXlVbVHhOZ){xfPmceNpOy = true;}
      if(MMVaJQUiYt == YSLeuZWCJH){EdHVfrQpPW = true;}
      if(soJpynOuGr == PHxMSWucSj){HifkidNMMw = true;}
      while(aXlVbVHhOZ == PqRkajTJjJ){GPTzRKGSVg = true;}
      while(YSLeuZWCJH == YSLeuZWCJH){TIDiyIbJVM = true;}
      while(PHxMSWucSj == PHxMSWucSj){BljRumSwMq = true;}
      if(yCesgSKfXL == true){yCesgSKfXL = false;}
      if(uGsBtkyNOr == true){uGsBtkyNOr = false;}
      if(VsnaGSaYDE == true){VsnaGSaYDE = false;}
      if(ZePdbVnRyb == true){ZePdbVnRyb = false;}
      if(PqexMIOwRg == true){PqexMIOwRg = false;}
      if(YhOZOEOElN == true){YhOZOEOElN = false;}
      if(rkcSkQpOYX == true){rkcSkQpOYX = false;}
      if(xfPmceNpOy == true){xfPmceNpOy = false;}
      if(EdHVfrQpPW == true){EdHVfrQpPW = false;}
      if(HifkidNMMw == true){HifkidNMMw = false;}
      if(SAWsirRawj == true){SAWsirRawj = false;}
      if(qXonJNdGmr == true){qXonJNdGmr = false;}
      if(zAyBQNAeEz == true){zAyBQNAeEz = false;}
      if(QBdReDHNmm == true){QBdReDHNmm = false;}
      if(aosffitqaU == true){aosffitqaU = false;}
      if(AHYTwRBUcV == true){AHYTwRBUcV = false;}
      if(rmWxSotXIF == true){rmWxSotXIF = false;}
      if(GPTzRKGSVg == true){GPTzRKGSVg = false;}
      if(TIDiyIbJVM == true){TIDiyIbJVM = false;}
      if(BljRumSwMq == true){BljRumSwMq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCNKZBOUED
{ 
  void hsMlRiQUJy()
  { 
      bool RsSeKJBdrF = false;
      bool NhIpdJHwUP = false;
      bool VkOFOifeQB = false;
      bool uejWCKCECl = false;
      bool JhYOoSjhaR = false;
      bool qCbaWfdMPb = false;
      bool dVNqJhxlmT = false;
      bool HCthFnLAPu = false;
      bool zyEyKsDJAV = false;
      bool gooZHnTgFH = false;
      bool VytGKnIsVh = false;
      bool UdwTcfQPgP = false;
      bool enkRlSNTZR = false;
      bool TeuIZADxmV = false;
      bool kJnRBDrUwb = false;
      bool WEAobhMcUq = false;
      bool anSENphmtb = false;
      bool bTbLeUzSPi = false;
      bool ZrXytPdFgr = false;
      bool nacwtxpjEL = false;
      string aYZqeFaAMY;
      string fBLrJRSAmg;
      string sGUyWueFae;
      string aJZaKlGuCH;
      string VjCdaDkxWY;
      string yRpliTDaTi;
      string aUZgxWbjgW;
      string KXxfKJDpXT;
      string KghBgJSnrp;
      string heaTfAKVfD;
      string bAPzNaUJaZ;
      string PMDAYsmXzn;
      string DnrqofwdAK;
      string yhJTqJRimG;
      string oIMRaUbatm;
      string NlWrAnIYKh;
      string epJQahCiIP;
      string bDjrztaaPU;
      string DUiNwLLRTC;
      string ArXEbyywps;
      if(aYZqeFaAMY == bAPzNaUJaZ){RsSeKJBdrF = true;}
      else if(bAPzNaUJaZ == aYZqeFaAMY){VytGKnIsVh = true;}
      if(fBLrJRSAmg == PMDAYsmXzn){NhIpdJHwUP = true;}
      else if(PMDAYsmXzn == fBLrJRSAmg){UdwTcfQPgP = true;}
      if(sGUyWueFae == DnrqofwdAK){VkOFOifeQB = true;}
      else if(DnrqofwdAK == sGUyWueFae){enkRlSNTZR = true;}
      if(aJZaKlGuCH == yhJTqJRimG){uejWCKCECl = true;}
      else if(yhJTqJRimG == aJZaKlGuCH){TeuIZADxmV = true;}
      if(VjCdaDkxWY == oIMRaUbatm){JhYOoSjhaR = true;}
      else if(oIMRaUbatm == VjCdaDkxWY){kJnRBDrUwb = true;}
      if(yRpliTDaTi == NlWrAnIYKh){qCbaWfdMPb = true;}
      else if(NlWrAnIYKh == yRpliTDaTi){WEAobhMcUq = true;}
      if(aUZgxWbjgW == epJQahCiIP){dVNqJhxlmT = true;}
      else if(epJQahCiIP == aUZgxWbjgW){anSENphmtb = true;}
      if(KXxfKJDpXT == bDjrztaaPU){HCthFnLAPu = true;}
      if(KghBgJSnrp == DUiNwLLRTC){zyEyKsDJAV = true;}
      if(heaTfAKVfD == ArXEbyywps){gooZHnTgFH = true;}
      while(bDjrztaaPU == KXxfKJDpXT){bTbLeUzSPi = true;}
      while(DUiNwLLRTC == DUiNwLLRTC){ZrXytPdFgr = true;}
      while(ArXEbyywps == ArXEbyywps){nacwtxpjEL = true;}
      if(RsSeKJBdrF == true){RsSeKJBdrF = false;}
      if(NhIpdJHwUP == true){NhIpdJHwUP = false;}
      if(VkOFOifeQB == true){VkOFOifeQB = false;}
      if(uejWCKCECl == true){uejWCKCECl = false;}
      if(JhYOoSjhaR == true){JhYOoSjhaR = false;}
      if(qCbaWfdMPb == true){qCbaWfdMPb = false;}
      if(dVNqJhxlmT == true){dVNqJhxlmT = false;}
      if(HCthFnLAPu == true){HCthFnLAPu = false;}
      if(zyEyKsDJAV == true){zyEyKsDJAV = false;}
      if(gooZHnTgFH == true){gooZHnTgFH = false;}
      if(VytGKnIsVh == true){VytGKnIsVh = false;}
      if(UdwTcfQPgP == true){UdwTcfQPgP = false;}
      if(enkRlSNTZR == true){enkRlSNTZR = false;}
      if(TeuIZADxmV == true){TeuIZADxmV = false;}
      if(kJnRBDrUwb == true){kJnRBDrUwb = false;}
      if(WEAobhMcUq == true){WEAobhMcUq = false;}
      if(anSENphmtb == true){anSENphmtb = false;}
      if(bTbLeUzSPi == true){bTbLeUzSPi = false;}
      if(ZrXytPdFgr == true){ZrXytPdFgr = false;}
      if(nacwtxpjEL == true){nacwtxpjEL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDMWSVTSKA
{ 
  void yFAhmoIOWw()
  { 
      bool sTYdXXDCUC = false;
      bool tzSVXRUsXI = false;
      bool OVMufghQZq = false;
      bool EEosEunUfD = false;
      bool lBKIfbiPCI = false;
      bool PRKJZXHdxp = false;
      bool plcdxpKYQb = false;
      bool dzMUVMLDOE = false;
      bool xSNQalseTg = false;
      bool nKWoMAXgKo = false;
      bool QJyadQFomM = false;
      bool MDOrrXXLCL = false;
      bool weFinTcWHV = false;
      bool nesZnnTmmK = false;
      bool gDrGUjwdxo = false;
      bool bMdzskEOlK = false;
      bool nhhQXhJoEE = false;
      bool EjYrdrmzOD = false;
      bool WyZSsbAtgC = false;
      bool iEBbVzVahm = false;
      string RzMfQqrJSG;
      string VdutVCBmls;
      string BaSuoPIzwR;
      string UgFWXEGRbe;
      string JOJOdbDNeo;
      string XNQDWpgQqB;
      string isMAlnYYWQ;
      string uiKHimQDRM;
      string MuTGtGQCAg;
      string XpZauQBJbo;
      string DdqNsnDITj;
      string ZczeonYFGe;
      string XVXosFIjLS;
      string kHbbIhEFNF;
      string DHiQGtpukH;
      string quDwRhGBUm;
      string eSxAySBWVH;
      string jSrAbPmGhy;
      string PNyEbpEeKa;
      string aCkaajKiRn;
      if(RzMfQqrJSG == DdqNsnDITj){sTYdXXDCUC = true;}
      else if(DdqNsnDITj == RzMfQqrJSG){QJyadQFomM = true;}
      if(VdutVCBmls == ZczeonYFGe){tzSVXRUsXI = true;}
      else if(ZczeonYFGe == VdutVCBmls){MDOrrXXLCL = true;}
      if(BaSuoPIzwR == XVXosFIjLS){OVMufghQZq = true;}
      else if(XVXosFIjLS == BaSuoPIzwR){weFinTcWHV = true;}
      if(UgFWXEGRbe == kHbbIhEFNF){EEosEunUfD = true;}
      else if(kHbbIhEFNF == UgFWXEGRbe){nesZnnTmmK = true;}
      if(JOJOdbDNeo == DHiQGtpukH){lBKIfbiPCI = true;}
      else if(DHiQGtpukH == JOJOdbDNeo){gDrGUjwdxo = true;}
      if(XNQDWpgQqB == quDwRhGBUm){PRKJZXHdxp = true;}
      else if(quDwRhGBUm == XNQDWpgQqB){bMdzskEOlK = true;}
      if(isMAlnYYWQ == eSxAySBWVH){plcdxpKYQb = true;}
      else if(eSxAySBWVH == isMAlnYYWQ){nhhQXhJoEE = true;}
      if(uiKHimQDRM == jSrAbPmGhy){dzMUVMLDOE = true;}
      if(MuTGtGQCAg == PNyEbpEeKa){xSNQalseTg = true;}
      if(XpZauQBJbo == aCkaajKiRn){nKWoMAXgKo = true;}
      while(jSrAbPmGhy == uiKHimQDRM){EjYrdrmzOD = true;}
      while(PNyEbpEeKa == PNyEbpEeKa){WyZSsbAtgC = true;}
      while(aCkaajKiRn == aCkaajKiRn){iEBbVzVahm = true;}
      if(sTYdXXDCUC == true){sTYdXXDCUC = false;}
      if(tzSVXRUsXI == true){tzSVXRUsXI = false;}
      if(OVMufghQZq == true){OVMufghQZq = false;}
      if(EEosEunUfD == true){EEosEunUfD = false;}
      if(lBKIfbiPCI == true){lBKIfbiPCI = false;}
      if(PRKJZXHdxp == true){PRKJZXHdxp = false;}
      if(plcdxpKYQb == true){plcdxpKYQb = false;}
      if(dzMUVMLDOE == true){dzMUVMLDOE = false;}
      if(xSNQalseTg == true){xSNQalseTg = false;}
      if(nKWoMAXgKo == true){nKWoMAXgKo = false;}
      if(QJyadQFomM == true){QJyadQFomM = false;}
      if(MDOrrXXLCL == true){MDOrrXXLCL = false;}
      if(weFinTcWHV == true){weFinTcWHV = false;}
      if(nesZnnTmmK == true){nesZnnTmmK = false;}
      if(gDrGUjwdxo == true){gDrGUjwdxo = false;}
      if(bMdzskEOlK == true){bMdzskEOlK = false;}
      if(nhhQXhJoEE == true){nhhQXhJoEE = false;}
      if(EjYrdrmzOD == true){EjYrdrmzOD = false;}
      if(WyZSsbAtgC == true){WyZSsbAtgC = false;}
      if(iEBbVzVahm == true){iEBbVzVahm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZAQKFILAB
{ 
  void PIFgCPjycp()
  { 
      bool fHdqrQFbqz = false;
      bool lfhxHXjisx = false;
      bool BsYHbWrkhm = false;
      bool TUJwsoBkuP = false;
      bool xHKohKoBNT = false;
      bool wKroOliVPU = false;
      bool XTtEfRWkDR = false;
      bool VynczthiZQ = false;
      bool hqWNpIcUhG = false;
      bool GfVaqcNGJP = false;
      bool nDxwyxWOoU = false;
      bool EzuylgxfNW = false;
      bool nBDxLpcNlV = false;
      bool fbZJbesaPs = false;
      bool lOeMCHjWnJ = false;
      bool fhrlblzAkI = false;
      bool UJbSobYkVH = false;
      bool nVPUjZWqtE = false;
      bool FFYcpyinhp = false;
      bool espHXcmMXa = false;
      string OVwXtUEJFs;
      string bYRsXEkGTb;
      string oiWhOabBbC;
      string jjnfEkAESr;
      string VcZikswyJc;
      string ToWRcfyNJS;
      string rDgDJrkknm;
      string EfmaFLInxU;
      string edqziuMVDY;
      string lltzASuWZs;
      string HKKWXnBwLQ;
      string WKQonNLhUN;
      string ePhOASknZm;
      string QlODMTSUat;
      string tQJlBbUFLm;
      string HMCLOrbuVF;
      string CMVYAkwNbT;
      string upHZTOFuMY;
      string xecmfDjCoT;
      string qXyVqgtklQ;
      if(OVwXtUEJFs == HKKWXnBwLQ){fHdqrQFbqz = true;}
      else if(HKKWXnBwLQ == OVwXtUEJFs){nDxwyxWOoU = true;}
      if(bYRsXEkGTb == WKQonNLhUN){lfhxHXjisx = true;}
      else if(WKQonNLhUN == bYRsXEkGTb){EzuylgxfNW = true;}
      if(oiWhOabBbC == ePhOASknZm){BsYHbWrkhm = true;}
      else if(ePhOASknZm == oiWhOabBbC){nBDxLpcNlV = true;}
      if(jjnfEkAESr == QlODMTSUat){TUJwsoBkuP = true;}
      else if(QlODMTSUat == jjnfEkAESr){fbZJbesaPs = true;}
      if(VcZikswyJc == tQJlBbUFLm){xHKohKoBNT = true;}
      else if(tQJlBbUFLm == VcZikswyJc){lOeMCHjWnJ = true;}
      if(ToWRcfyNJS == HMCLOrbuVF){wKroOliVPU = true;}
      else if(HMCLOrbuVF == ToWRcfyNJS){fhrlblzAkI = true;}
      if(rDgDJrkknm == CMVYAkwNbT){XTtEfRWkDR = true;}
      else if(CMVYAkwNbT == rDgDJrkknm){UJbSobYkVH = true;}
      if(EfmaFLInxU == upHZTOFuMY){VynczthiZQ = true;}
      if(edqziuMVDY == xecmfDjCoT){hqWNpIcUhG = true;}
      if(lltzASuWZs == qXyVqgtklQ){GfVaqcNGJP = true;}
      while(upHZTOFuMY == EfmaFLInxU){nVPUjZWqtE = true;}
      while(xecmfDjCoT == xecmfDjCoT){FFYcpyinhp = true;}
      while(qXyVqgtklQ == qXyVqgtklQ){espHXcmMXa = true;}
      if(fHdqrQFbqz == true){fHdqrQFbqz = false;}
      if(lfhxHXjisx == true){lfhxHXjisx = false;}
      if(BsYHbWrkhm == true){BsYHbWrkhm = false;}
      if(TUJwsoBkuP == true){TUJwsoBkuP = false;}
      if(xHKohKoBNT == true){xHKohKoBNT = false;}
      if(wKroOliVPU == true){wKroOliVPU = false;}
      if(XTtEfRWkDR == true){XTtEfRWkDR = false;}
      if(VynczthiZQ == true){VynczthiZQ = false;}
      if(hqWNpIcUhG == true){hqWNpIcUhG = false;}
      if(GfVaqcNGJP == true){GfVaqcNGJP = false;}
      if(nDxwyxWOoU == true){nDxwyxWOoU = false;}
      if(EzuylgxfNW == true){EzuylgxfNW = false;}
      if(nBDxLpcNlV == true){nBDxLpcNlV = false;}
      if(fbZJbesaPs == true){fbZJbesaPs = false;}
      if(lOeMCHjWnJ == true){lOeMCHjWnJ = false;}
      if(fhrlblzAkI == true){fhrlblzAkI = false;}
      if(UJbSobYkVH == true){UJbSobYkVH = false;}
      if(nVPUjZWqtE == true){nVPUjZWqtE = false;}
      if(FFYcpyinhp == true){FFYcpyinhp = false;}
      if(espHXcmMXa == true){espHXcmMXa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYMCQBKWHZ
{ 
  void SshWpydOBn()
  { 
      bool WUldHTUGjz = false;
      bool OBGTYEhuOP = false;
      bool apsZwCoDQT = false;
      bool YkaoGGVuOo = false;
      bool AlPKzKeAft = false;
      bool ReyolfbLgF = false;
      bool eRpPadaQNS = false;
      bool imgZPoahal = false;
      bool XoWWBsllDZ = false;
      bool dKNJKiwziU = false;
      bool jNmNLeyYZw = false;
      bool FsjugptSOh = false;
      bool qnNmnXZXOf = false;
      bool razGCJBIKW = false;
      bool uNMGUkZRbU = false;
      bool nckBcuzAZn = false;
      bool FZJsDetdsX = false;
      bool nlIqmdbGRC = false;
      bool xHwtrPoxcG = false;
      bool JBiWRUESDp = false;
      string EDkkmJWFKo;
      string lfqbtjBeyc;
      string xBUUyqlqma;
      string mNAwXsAchB;
      string jIjhRawyni;
      string TOhEXDiPmu;
      string WeRjBYetEA;
      string iYxxroRlCW;
      string unDEGYewYT;
      string KjpldFpAgs;
      string uCsmzuRkLi;
      string lwMPAhaNcb;
      string siUjpzhKSm;
      string yQFJartQFL;
      string HskohNXZlw;
      string dcXEzMgIwA;
      string MGSXkUqCnH;
      string nJIQUzxeCc;
      string aHYWJUsAJN;
      string LkUFzAaMEM;
      if(EDkkmJWFKo == uCsmzuRkLi){WUldHTUGjz = true;}
      else if(uCsmzuRkLi == EDkkmJWFKo){jNmNLeyYZw = true;}
      if(lfqbtjBeyc == lwMPAhaNcb){OBGTYEhuOP = true;}
      else if(lwMPAhaNcb == lfqbtjBeyc){FsjugptSOh = true;}
      if(xBUUyqlqma == siUjpzhKSm){apsZwCoDQT = true;}
      else if(siUjpzhKSm == xBUUyqlqma){qnNmnXZXOf = true;}
      if(mNAwXsAchB == yQFJartQFL){YkaoGGVuOo = true;}
      else if(yQFJartQFL == mNAwXsAchB){razGCJBIKW = true;}
      if(jIjhRawyni == HskohNXZlw){AlPKzKeAft = true;}
      else if(HskohNXZlw == jIjhRawyni){uNMGUkZRbU = true;}
      if(TOhEXDiPmu == dcXEzMgIwA){ReyolfbLgF = true;}
      else if(dcXEzMgIwA == TOhEXDiPmu){nckBcuzAZn = true;}
      if(WeRjBYetEA == MGSXkUqCnH){eRpPadaQNS = true;}
      else if(MGSXkUqCnH == WeRjBYetEA){FZJsDetdsX = true;}
      if(iYxxroRlCW == nJIQUzxeCc){imgZPoahal = true;}
      if(unDEGYewYT == aHYWJUsAJN){XoWWBsllDZ = true;}
      if(KjpldFpAgs == LkUFzAaMEM){dKNJKiwziU = true;}
      while(nJIQUzxeCc == iYxxroRlCW){nlIqmdbGRC = true;}
      while(aHYWJUsAJN == aHYWJUsAJN){xHwtrPoxcG = true;}
      while(LkUFzAaMEM == LkUFzAaMEM){JBiWRUESDp = true;}
      if(WUldHTUGjz == true){WUldHTUGjz = false;}
      if(OBGTYEhuOP == true){OBGTYEhuOP = false;}
      if(apsZwCoDQT == true){apsZwCoDQT = false;}
      if(YkaoGGVuOo == true){YkaoGGVuOo = false;}
      if(AlPKzKeAft == true){AlPKzKeAft = false;}
      if(ReyolfbLgF == true){ReyolfbLgF = false;}
      if(eRpPadaQNS == true){eRpPadaQNS = false;}
      if(imgZPoahal == true){imgZPoahal = false;}
      if(XoWWBsllDZ == true){XoWWBsllDZ = false;}
      if(dKNJKiwziU == true){dKNJKiwziU = false;}
      if(jNmNLeyYZw == true){jNmNLeyYZw = false;}
      if(FsjugptSOh == true){FsjugptSOh = false;}
      if(qnNmnXZXOf == true){qnNmnXZXOf = false;}
      if(razGCJBIKW == true){razGCJBIKW = false;}
      if(uNMGUkZRbU == true){uNMGUkZRbU = false;}
      if(nckBcuzAZn == true){nckBcuzAZn = false;}
      if(FZJsDetdsX == true){FZJsDetdsX = false;}
      if(nlIqmdbGRC == true){nlIqmdbGRC = false;}
      if(xHwtrPoxcG == true){xHwtrPoxcG = false;}
      if(JBiWRUESDp == true){JBiWRUESDp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIRURSAPMP
{ 
  void aZDBUTnmtZ()
  { 
      bool XchVoLisfC = false;
      bool qCgAVbDXDH = false;
      bool rJppeDbDgL = false;
      bool GrBRNyqNoq = false;
      bool dyGCEkefik = false;
      bool XjqwOOmrqk = false;
      bool jfLUwzBOmW = false;
      bool kohMdtDmks = false;
      bool YwUunVAECy = false;
      bool LzVEHyllGF = false;
      bool jQrLAhCdSU = false;
      bool LzHyLnLPfZ = false;
      bool yxLnKkScFf = false;
      bool IRgfJIDIuF = false;
      bool TWkhmLrXrS = false;
      bool mVFfGmEEAO = false;
      bool OYYmMtSboD = false;
      bool jCUaGbLdAz = false;
      bool sujlslLAYV = false;
      bool DzHfptxyUs = false;
      string LFGpDHTuMt;
      string duIfeKSikx;
      string PLaahCiglm;
      string RHadHBUpFM;
      string fKbzNnRtVm;
      string YpKueAeeHA;
      string XlJZcWUdXc;
      string ocdXQFibNt;
      string joLzNaxfzH;
      string WphEntBCVq;
      string TnVrxwMldZ;
      string QCRNPiaJMC;
      string ZoePGztYjW;
      string EgGWawSSBQ;
      string OKBYpUXUoF;
      string TqoTRdIGlx;
      string CmCGUjwulS;
      string QHHumOmFYl;
      string bZjdDMqlFw;
      string nMfENaIuEG;
      if(LFGpDHTuMt == TnVrxwMldZ){XchVoLisfC = true;}
      else if(TnVrxwMldZ == LFGpDHTuMt){jQrLAhCdSU = true;}
      if(duIfeKSikx == QCRNPiaJMC){qCgAVbDXDH = true;}
      else if(QCRNPiaJMC == duIfeKSikx){LzHyLnLPfZ = true;}
      if(PLaahCiglm == ZoePGztYjW){rJppeDbDgL = true;}
      else if(ZoePGztYjW == PLaahCiglm){yxLnKkScFf = true;}
      if(RHadHBUpFM == EgGWawSSBQ){GrBRNyqNoq = true;}
      else if(EgGWawSSBQ == RHadHBUpFM){IRgfJIDIuF = true;}
      if(fKbzNnRtVm == OKBYpUXUoF){dyGCEkefik = true;}
      else if(OKBYpUXUoF == fKbzNnRtVm){TWkhmLrXrS = true;}
      if(YpKueAeeHA == TqoTRdIGlx){XjqwOOmrqk = true;}
      else if(TqoTRdIGlx == YpKueAeeHA){mVFfGmEEAO = true;}
      if(XlJZcWUdXc == CmCGUjwulS){jfLUwzBOmW = true;}
      else if(CmCGUjwulS == XlJZcWUdXc){OYYmMtSboD = true;}
      if(ocdXQFibNt == QHHumOmFYl){kohMdtDmks = true;}
      if(joLzNaxfzH == bZjdDMqlFw){YwUunVAECy = true;}
      if(WphEntBCVq == nMfENaIuEG){LzVEHyllGF = true;}
      while(QHHumOmFYl == ocdXQFibNt){jCUaGbLdAz = true;}
      while(bZjdDMqlFw == bZjdDMqlFw){sujlslLAYV = true;}
      while(nMfENaIuEG == nMfENaIuEG){DzHfptxyUs = true;}
      if(XchVoLisfC == true){XchVoLisfC = false;}
      if(qCgAVbDXDH == true){qCgAVbDXDH = false;}
      if(rJppeDbDgL == true){rJppeDbDgL = false;}
      if(GrBRNyqNoq == true){GrBRNyqNoq = false;}
      if(dyGCEkefik == true){dyGCEkefik = false;}
      if(XjqwOOmrqk == true){XjqwOOmrqk = false;}
      if(jfLUwzBOmW == true){jfLUwzBOmW = false;}
      if(kohMdtDmks == true){kohMdtDmks = false;}
      if(YwUunVAECy == true){YwUunVAECy = false;}
      if(LzVEHyllGF == true){LzVEHyllGF = false;}
      if(jQrLAhCdSU == true){jQrLAhCdSU = false;}
      if(LzHyLnLPfZ == true){LzHyLnLPfZ = false;}
      if(yxLnKkScFf == true){yxLnKkScFf = false;}
      if(IRgfJIDIuF == true){IRgfJIDIuF = false;}
      if(TWkhmLrXrS == true){TWkhmLrXrS = false;}
      if(mVFfGmEEAO == true){mVFfGmEEAO = false;}
      if(OYYmMtSboD == true){OYYmMtSboD = false;}
      if(jCUaGbLdAz == true){jCUaGbLdAz = false;}
      if(sujlslLAYV == true){sujlslLAYV = false;}
      if(DzHfptxyUs == true){DzHfptxyUs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZKYMWDRLMF
{ 
  void eziyJdVMxI()
  { 
      bool ipSdctKWCI = false;
      bool mEGbAmtnds = false;
      bool REwZEiGgZy = false;
      bool uaEGsMTUFY = false;
      bool LJOVaPZeZh = false;
      bool zUdVBdtsZs = false;
      bool mdwEMLzAim = false;
      bool TYhEhIpayn = false;
      bool IaGryaxiFO = false;
      bool SauLkhMJIP = false;
      bool PZumOZlZmr = false;
      bool nStkkLWEGl = false;
      bool NPtTTrcVSA = false;
      bool wfSiXifTdX = false;
      bool nXuNazfKaZ = false;
      bool KIDVBzfbSV = false;
      bool wPGmwIALMC = false;
      bool fDZhxpUfrT = false;
      bool LStsombwgX = false;
      bool CDAIaXQHQS = false;
      string TlGtPkjYGG;
      string sbWVguSYqM;
      string nRSAaeSLiC;
      string udIjPIpwEq;
      string FtLiLeLeLe;
      string nOzezCTGTk;
      string SYpDKOSlFX;
      string FVUAHsFjnw;
      string SmzENgedkN;
      string ojcTXfEHXx;
      string LZYmZStzXF;
      string wiRWReYlpd;
      string joAriVrBba;
      string oxLqjsOLdu;
      string lfFfRGRFCs;
      string HRRtMWYgEE;
      string ZsWxQyWamX;
      string QNHuqEjUZc;
      string DlyiSWfRdN;
      string TgGZUsIIPS;
      if(TlGtPkjYGG == LZYmZStzXF){ipSdctKWCI = true;}
      else if(LZYmZStzXF == TlGtPkjYGG){PZumOZlZmr = true;}
      if(sbWVguSYqM == wiRWReYlpd){mEGbAmtnds = true;}
      else if(wiRWReYlpd == sbWVguSYqM){nStkkLWEGl = true;}
      if(nRSAaeSLiC == joAriVrBba){REwZEiGgZy = true;}
      else if(joAriVrBba == nRSAaeSLiC){NPtTTrcVSA = true;}
      if(udIjPIpwEq == oxLqjsOLdu){uaEGsMTUFY = true;}
      else if(oxLqjsOLdu == udIjPIpwEq){wfSiXifTdX = true;}
      if(FtLiLeLeLe == lfFfRGRFCs){LJOVaPZeZh = true;}
      else if(lfFfRGRFCs == FtLiLeLeLe){nXuNazfKaZ = true;}
      if(nOzezCTGTk == HRRtMWYgEE){zUdVBdtsZs = true;}
      else if(HRRtMWYgEE == nOzezCTGTk){KIDVBzfbSV = true;}
      if(SYpDKOSlFX == ZsWxQyWamX){mdwEMLzAim = true;}
      else if(ZsWxQyWamX == SYpDKOSlFX){wPGmwIALMC = true;}
      if(FVUAHsFjnw == QNHuqEjUZc){TYhEhIpayn = true;}
      if(SmzENgedkN == DlyiSWfRdN){IaGryaxiFO = true;}
      if(ojcTXfEHXx == TgGZUsIIPS){SauLkhMJIP = true;}
      while(QNHuqEjUZc == FVUAHsFjnw){fDZhxpUfrT = true;}
      while(DlyiSWfRdN == DlyiSWfRdN){LStsombwgX = true;}
      while(TgGZUsIIPS == TgGZUsIIPS){CDAIaXQHQS = true;}
      if(ipSdctKWCI == true){ipSdctKWCI = false;}
      if(mEGbAmtnds == true){mEGbAmtnds = false;}
      if(REwZEiGgZy == true){REwZEiGgZy = false;}
      if(uaEGsMTUFY == true){uaEGsMTUFY = false;}
      if(LJOVaPZeZh == true){LJOVaPZeZh = false;}
      if(zUdVBdtsZs == true){zUdVBdtsZs = false;}
      if(mdwEMLzAim == true){mdwEMLzAim = false;}
      if(TYhEhIpayn == true){TYhEhIpayn = false;}
      if(IaGryaxiFO == true){IaGryaxiFO = false;}
      if(SauLkhMJIP == true){SauLkhMJIP = false;}
      if(PZumOZlZmr == true){PZumOZlZmr = false;}
      if(nStkkLWEGl == true){nStkkLWEGl = false;}
      if(NPtTTrcVSA == true){NPtTTrcVSA = false;}
      if(wfSiXifTdX == true){wfSiXifTdX = false;}
      if(nXuNazfKaZ == true){nXuNazfKaZ = false;}
      if(KIDVBzfbSV == true){KIDVBzfbSV = false;}
      if(wPGmwIALMC == true){wPGmwIALMC = false;}
      if(fDZhxpUfrT == true){fDZhxpUfrT = false;}
      if(LStsombwgX == true){LStsombwgX = false;}
      if(CDAIaXQHQS == true){CDAIaXQHQS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGMXWZWDCS
{ 
  void DyiupHKyDu()
  { 
      bool JPUWhDPZPn = false;
      bool kBCDJCqAwT = false;
      bool YHRVXWCutj = false;
      bool HrClTrWBzP = false;
      bool nihSSzaPID = false;
      bool tLPWtCxyzL = false;
      bool AUfffsyPjR = false;
      bool eoAgfoZzDX = false;
      bool ullqpwbfqQ = false;
      bool tYCnOSDBmZ = false;
      bool AKfqXEKiqF = false;
      bool cxuaPOhopi = false;
      bool QSYSWFlMSM = false;
      bool lXMcXkGuSk = false;
      bool ksnlnxdbYA = false;
      bool kNLDIhkMUR = false;
      bool RyQeTEkRCd = false;
      bool HlVEyWemdY = false;
      bool bJnRaXLIUp = false;
      bool zsaASmcJRj = false;
      string unwkpfpUEH;
      string kkzZjbJLmY;
      string QSGUzYsweW;
      string AaXZxlDDeE;
      string nMIOhibrWj;
      string nQgqHcgalQ;
      string ltohGJMZcx;
      string XFghkDJqmQ;
      string xBYthjtgRU;
      string EbRNSsWZIX;
      string VCPYMhiyGD;
      string SonVSkUtzW;
      string PfHHrunSPq;
      string fjiOtukzhA;
      string BuaNCPnuth;
      string YbZkIptHfQ;
      string tPiOXhFYaX;
      string zUMzUUEsFc;
      string HrYhSDJyGE;
      string AcSRFkMLpT;
      if(unwkpfpUEH == VCPYMhiyGD){JPUWhDPZPn = true;}
      else if(VCPYMhiyGD == unwkpfpUEH){AKfqXEKiqF = true;}
      if(kkzZjbJLmY == SonVSkUtzW){kBCDJCqAwT = true;}
      else if(SonVSkUtzW == kkzZjbJLmY){cxuaPOhopi = true;}
      if(QSGUzYsweW == PfHHrunSPq){YHRVXWCutj = true;}
      else if(PfHHrunSPq == QSGUzYsweW){QSYSWFlMSM = true;}
      if(AaXZxlDDeE == fjiOtukzhA){HrClTrWBzP = true;}
      else if(fjiOtukzhA == AaXZxlDDeE){lXMcXkGuSk = true;}
      if(nMIOhibrWj == BuaNCPnuth){nihSSzaPID = true;}
      else if(BuaNCPnuth == nMIOhibrWj){ksnlnxdbYA = true;}
      if(nQgqHcgalQ == YbZkIptHfQ){tLPWtCxyzL = true;}
      else if(YbZkIptHfQ == nQgqHcgalQ){kNLDIhkMUR = true;}
      if(ltohGJMZcx == tPiOXhFYaX){AUfffsyPjR = true;}
      else if(tPiOXhFYaX == ltohGJMZcx){RyQeTEkRCd = true;}
      if(XFghkDJqmQ == zUMzUUEsFc){eoAgfoZzDX = true;}
      if(xBYthjtgRU == HrYhSDJyGE){ullqpwbfqQ = true;}
      if(EbRNSsWZIX == AcSRFkMLpT){tYCnOSDBmZ = true;}
      while(zUMzUUEsFc == XFghkDJqmQ){HlVEyWemdY = true;}
      while(HrYhSDJyGE == HrYhSDJyGE){bJnRaXLIUp = true;}
      while(AcSRFkMLpT == AcSRFkMLpT){zsaASmcJRj = true;}
      if(JPUWhDPZPn == true){JPUWhDPZPn = false;}
      if(kBCDJCqAwT == true){kBCDJCqAwT = false;}
      if(YHRVXWCutj == true){YHRVXWCutj = false;}
      if(HrClTrWBzP == true){HrClTrWBzP = false;}
      if(nihSSzaPID == true){nihSSzaPID = false;}
      if(tLPWtCxyzL == true){tLPWtCxyzL = false;}
      if(AUfffsyPjR == true){AUfffsyPjR = false;}
      if(eoAgfoZzDX == true){eoAgfoZzDX = false;}
      if(ullqpwbfqQ == true){ullqpwbfqQ = false;}
      if(tYCnOSDBmZ == true){tYCnOSDBmZ = false;}
      if(AKfqXEKiqF == true){AKfqXEKiqF = false;}
      if(cxuaPOhopi == true){cxuaPOhopi = false;}
      if(QSYSWFlMSM == true){QSYSWFlMSM = false;}
      if(lXMcXkGuSk == true){lXMcXkGuSk = false;}
      if(ksnlnxdbYA == true){ksnlnxdbYA = false;}
      if(kNLDIhkMUR == true){kNLDIhkMUR = false;}
      if(RyQeTEkRCd == true){RyQeTEkRCd = false;}
      if(HlVEyWemdY == true){HlVEyWemdY = false;}
      if(bJnRaXLIUp == true){bJnRaXLIUp = false;}
      if(zsaASmcJRj == true){zsaASmcJRj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EURMWCVEXH
{ 
  void luwhVmZMAV()
  { 
      bool BPyifHflYV = false;
      bool uUmJwakdlH = false;
      bool mMcATiYMLk = false;
      bool RIojuMViBc = false;
      bool BSkhfKkeDw = false;
      bool rnxbNolxPw = false;
      bool iTanDleCNj = false;
      bool FCbJFTauTI = false;
      bool xsJOrdLNVG = false;
      bool ZXTFthrxdt = false;
      bool fiRSqpLmWt = false;
      bool NqdGyoKMuZ = false;
      bool aRgGJghWPW = false;
      bool bdQZcObpXC = false;
      bool RXpbritMHE = false;
      bool XfBDSNBKIJ = false;
      bool IoXzRiZEdi = false;
      bool MTnsIDaFNa = false;
      bool mUOKzwcMGO = false;
      bool NRhOtczpJJ = false;
      string uWJbqCuoRy;
      string jZuaRheQKp;
      string mcOhcxyPhJ;
      string KHqIgCSRDw;
      string IjebzXeyqM;
      string BTuITRIbys;
      string EfGInbhltP;
      string PMMNgDylhF;
      string SAXVHpMhnO;
      string tpSKrccWmW;
      string orDbxoHgaP;
      string TVssaEIkBy;
      string PAyfVYtCVE;
      string aazLQZwuXS;
      string ieGYtXxZin;
      string UrVoHntXGY;
      string tELWosWhbA;
      string HMMiPksYkx;
      string bTShjhFKEb;
      string fXnzXdSjiB;
      if(uWJbqCuoRy == orDbxoHgaP){BPyifHflYV = true;}
      else if(orDbxoHgaP == uWJbqCuoRy){fiRSqpLmWt = true;}
      if(jZuaRheQKp == TVssaEIkBy){uUmJwakdlH = true;}
      else if(TVssaEIkBy == jZuaRheQKp){NqdGyoKMuZ = true;}
      if(mcOhcxyPhJ == PAyfVYtCVE){mMcATiYMLk = true;}
      else if(PAyfVYtCVE == mcOhcxyPhJ){aRgGJghWPW = true;}
      if(KHqIgCSRDw == aazLQZwuXS){RIojuMViBc = true;}
      else if(aazLQZwuXS == KHqIgCSRDw){bdQZcObpXC = true;}
      if(IjebzXeyqM == ieGYtXxZin){BSkhfKkeDw = true;}
      else if(ieGYtXxZin == IjebzXeyqM){RXpbritMHE = true;}
      if(BTuITRIbys == UrVoHntXGY){rnxbNolxPw = true;}
      else if(UrVoHntXGY == BTuITRIbys){XfBDSNBKIJ = true;}
      if(EfGInbhltP == tELWosWhbA){iTanDleCNj = true;}
      else if(tELWosWhbA == EfGInbhltP){IoXzRiZEdi = true;}
      if(PMMNgDylhF == HMMiPksYkx){FCbJFTauTI = true;}
      if(SAXVHpMhnO == bTShjhFKEb){xsJOrdLNVG = true;}
      if(tpSKrccWmW == fXnzXdSjiB){ZXTFthrxdt = true;}
      while(HMMiPksYkx == PMMNgDylhF){MTnsIDaFNa = true;}
      while(bTShjhFKEb == bTShjhFKEb){mUOKzwcMGO = true;}
      while(fXnzXdSjiB == fXnzXdSjiB){NRhOtczpJJ = true;}
      if(BPyifHflYV == true){BPyifHflYV = false;}
      if(uUmJwakdlH == true){uUmJwakdlH = false;}
      if(mMcATiYMLk == true){mMcATiYMLk = false;}
      if(RIojuMViBc == true){RIojuMViBc = false;}
      if(BSkhfKkeDw == true){BSkhfKkeDw = false;}
      if(rnxbNolxPw == true){rnxbNolxPw = false;}
      if(iTanDleCNj == true){iTanDleCNj = false;}
      if(FCbJFTauTI == true){FCbJFTauTI = false;}
      if(xsJOrdLNVG == true){xsJOrdLNVG = false;}
      if(ZXTFthrxdt == true){ZXTFthrxdt = false;}
      if(fiRSqpLmWt == true){fiRSqpLmWt = false;}
      if(NqdGyoKMuZ == true){NqdGyoKMuZ = false;}
      if(aRgGJghWPW == true){aRgGJghWPW = false;}
      if(bdQZcObpXC == true){bdQZcObpXC = false;}
      if(RXpbritMHE == true){RXpbritMHE = false;}
      if(XfBDSNBKIJ == true){XfBDSNBKIJ = false;}
      if(IoXzRiZEdi == true){IoXzRiZEdi = false;}
      if(MTnsIDaFNa == true){MTnsIDaFNa = false;}
      if(mUOKzwcMGO == true){mUOKzwcMGO = false;}
      if(NRhOtczpJJ == true){NRhOtczpJJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUTSEIPKQM
{ 
  void PfYrmiJTHz()
  { 
      bool MALTAWTBEW = false;
      bool zKMXCzunGW = false;
      bool UmEjWFRJLu = false;
      bool ZaNpXXtntA = false;
      bool ypGLmFoUCg = false;
      bool NbIOyZubxu = false;
      bool EJpIxXxWze = false;
      bool FHtGYdfswQ = false;
      bool PxGegxSyqy = false;
      bool bRpzunAxNP = false;
      bool HSVXaGgBpT = false;
      bool sBefeHDLbz = false;
      bool EzeACmQuKj = false;
      bool diegJwaiDa = false;
      bool QRHXEZmJTn = false;
      bool knVOKImUUn = false;
      bool olpGoJWyWh = false;
      bool fTIAhlrHub = false;
      bool AGbWypNPVB = false;
      bool IFOOkebBhu = false;
      string oiVgVhzDuh;
      string uOlHMoAexL;
      string bhVkgtQgmo;
      string iRFqloHfuF;
      string MtaaigggaU;
      string MCefXGMkza;
      string QSPFzdIuUW;
      string hTjrygHuBA;
      string NjFScgmZSf;
      string bWgUoteVbF;
      string XlLElrSlgq;
      string zRiyNfMwbS;
      string qibouLmODE;
      string BlTwbaYBgk;
      string NArbfKmhGI;
      string hisJNoKVIa;
      string EDicoNxmWm;
      string HKPqEqpzIk;
      string XFItWSrKhl;
      string QCsFfJQOlS;
      if(oiVgVhzDuh == XlLElrSlgq){MALTAWTBEW = true;}
      else if(XlLElrSlgq == oiVgVhzDuh){HSVXaGgBpT = true;}
      if(uOlHMoAexL == zRiyNfMwbS){zKMXCzunGW = true;}
      else if(zRiyNfMwbS == uOlHMoAexL){sBefeHDLbz = true;}
      if(bhVkgtQgmo == qibouLmODE){UmEjWFRJLu = true;}
      else if(qibouLmODE == bhVkgtQgmo){EzeACmQuKj = true;}
      if(iRFqloHfuF == BlTwbaYBgk){ZaNpXXtntA = true;}
      else if(BlTwbaYBgk == iRFqloHfuF){diegJwaiDa = true;}
      if(MtaaigggaU == NArbfKmhGI){ypGLmFoUCg = true;}
      else if(NArbfKmhGI == MtaaigggaU){QRHXEZmJTn = true;}
      if(MCefXGMkza == hisJNoKVIa){NbIOyZubxu = true;}
      else if(hisJNoKVIa == MCefXGMkza){knVOKImUUn = true;}
      if(QSPFzdIuUW == EDicoNxmWm){EJpIxXxWze = true;}
      else if(EDicoNxmWm == QSPFzdIuUW){olpGoJWyWh = true;}
      if(hTjrygHuBA == HKPqEqpzIk){FHtGYdfswQ = true;}
      if(NjFScgmZSf == XFItWSrKhl){PxGegxSyqy = true;}
      if(bWgUoteVbF == QCsFfJQOlS){bRpzunAxNP = true;}
      while(HKPqEqpzIk == hTjrygHuBA){fTIAhlrHub = true;}
      while(XFItWSrKhl == XFItWSrKhl){AGbWypNPVB = true;}
      while(QCsFfJQOlS == QCsFfJQOlS){IFOOkebBhu = true;}
      if(MALTAWTBEW == true){MALTAWTBEW = false;}
      if(zKMXCzunGW == true){zKMXCzunGW = false;}
      if(UmEjWFRJLu == true){UmEjWFRJLu = false;}
      if(ZaNpXXtntA == true){ZaNpXXtntA = false;}
      if(ypGLmFoUCg == true){ypGLmFoUCg = false;}
      if(NbIOyZubxu == true){NbIOyZubxu = false;}
      if(EJpIxXxWze == true){EJpIxXxWze = false;}
      if(FHtGYdfswQ == true){FHtGYdfswQ = false;}
      if(PxGegxSyqy == true){PxGegxSyqy = false;}
      if(bRpzunAxNP == true){bRpzunAxNP = false;}
      if(HSVXaGgBpT == true){HSVXaGgBpT = false;}
      if(sBefeHDLbz == true){sBefeHDLbz = false;}
      if(EzeACmQuKj == true){EzeACmQuKj = false;}
      if(diegJwaiDa == true){diegJwaiDa = false;}
      if(QRHXEZmJTn == true){QRHXEZmJTn = false;}
      if(knVOKImUUn == true){knVOKImUUn = false;}
      if(olpGoJWyWh == true){olpGoJWyWh = false;}
      if(fTIAhlrHub == true){fTIAhlrHub = false;}
      if(AGbWypNPVB == true){AGbWypNPVB = false;}
      if(IFOOkebBhu == true){IFOOkebBhu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMDVESZPMS
{ 
  void LzBcPVwsBS()
  { 
      bool xutkSmRhCD = false;
      bool mmxXSTwLsP = false;
      bool wiqOiVazNy = false;
      bool JFTyKlKxeN = false;
      bool FBxlFbpbZY = false;
      bool YJqHjNEeBw = false;
      bool MRTEthSyNg = false;
      bool JygeJtlEJH = false;
      bool fyZoYzNMOw = false;
      bool heuhBnhrrX = false;
      bool IqOsOZcMxo = false;
      bool bzVtPNrdfu = false;
      bool TGiQzdDzcV = false;
      bool MsMkyoigZy = false;
      bool WBPZUhJBSm = false;
      bool uDMxDCIxsj = false;
      bool Wciabhljua = false;
      bool eKDhXSpIwQ = false;
      bool UBgoZJgPhw = false;
      bool fkmpasRnxl = false;
      string RpVgwQSMwC;
      string xEGNnMYjha;
      string XaUqffJFRX;
      string kWrcGJPhqH;
      string lrnHVLHZBK;
      string XoIAzqUdAP;
      string HNtYQZMcGd;
      string xpsZoemNVU;
      string XiEHzwOqcP;
      string nlhaAXxOpu;
      string ydTWMgwiLT;
      string EGHerYJmZT;
      string LVAqpLHRYQ;
      string gXWZWsPgtS;
      string AfeJLgdDib;
      string OKoWjcdbgB;
      string YdJtlfjhIy;
      string JbsHTfpqeI;
      string hEhxBWiAps;
      string OmAssVVjWf;
      if(RpVgwQSMwC == ydTWMgwiLT){xutkSmRhCD = true;}
      else if(ydTWMgwiLT == RpVgwQSMwC){IqOsOZcMxo = true;}
      if(xEGNnMYjha == EGHerYJmZT){mmxXSTwLsP = true;}
      else if(EGHerYJmZT == xEGNnMYjha){bzVtPNrdfu = true;}
      if(XaUqffJFRX == LVAqpLHRYQ){wiqOiVazNy = true;}
      else if(LVAqpLHRYQ == XaUqffJFRX){TGiQzdDzcV = true;}
      if(kWrcGJPhqH == gXWZWsPgtS){JFTyKlKxeN = true;}
      else if(gXWZWsPgtS == kWrcGJPhqH){MsMkyoigZy = true;}
      if(lrnHVLHZBK == AfeJLgdDib){FBxlFbpbZY = true;}
      else if(AfeJLgdDib == lrnHVLHZBK){WBPZUhJBSm = true;}
      if(XoIAzqUdAP == OKoWjcdbgB){YJqHjNEeBw = true;}
      else if(OKoWjcdbgB == XoIAzqUdAP){uDMxDCIxsj = true;}
      if(HNtYQZMcGd == YdJtlfjhIy){MRTEthSyNg = true;}
      else if(YdJtlfjhIy == HNtYQZMcGd){Wciabhljua = true;}
      if(xpsZoemNVU == JbsHTfpqeI){JygeJtlEJH = true;}
      if(XiEHzwOqcP == hEhxBWiAps){fyZoYzNMOw = true;}
      if(nlhaAXxOpu == OmAssVVjWf){heuhBnhrrX = true;}
      while(JbsHTfpqeI == xpsZoemNVU){eKDhXSpIwQ = true;}
      while(hEhxBWiAps == hEhxBWiAps){UBgoZJgPhw = true;}
      while(OmAssVVjWf == OmAssVVjWf){fkmpasRnxl = true;}
      if(xutkSmRhCD == true){xutkSmRhCD = false;}
      if(mmxXSTwLsP == true){mmxXSTwLsP = false;}
      if(wiqOiVazNy == true){wiqOiVazNy = false;}
      if(JFTyKlKxeN == true){JFTyKlKxeN = false;}
      if(FBxlFbpbZY == true){FBxlFbpbZY = false;}
      if(YJqHjNEeBw == true){YJqHjNEeBw = false;}
      if(MRTEthSyNg == true){MRTEthSyNg = false;}
      if(JygeJtlEJH == true){JygeJtlEJH = false;}
      if(fyZoYzNMOw == true){fyZoYzNMOw = false;}
      if(heuhBnhrrX == true){heuhBnhrrX = false;}
      if(IqOsOZcMxo == true){IqOsOZcMxo = false;}
      if(bzVtPNrdfu == true){bzVtPNrdfu = false;}
      if(TGiQzdDzcV == true){TGiQzdDzcV = false;}
      if(MsMkyoigZy == true){MsMkyoigZy = false;}
      if(WBPZUhJBSm == true){WBPZUhJBSm = false;}
      if(uDMxDCIxsj == true){uDMxDCIxsj = false;}
      if(Wciabhljua == true){Wciabhljua = false;}
      if(eKDhXSpIwQ == true){eKDhXSpIwQ = false;}
      if(UBgoZJgPhw == true){UBgoZJgPhw = false;}
      if(fkmpasRnxl == true){fkmpasRnxl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUIXGHNEZA
{ 
  void MZFSXRTaJN()
  { 
      bool TfpqQgsxNI = false;
      bool kCdWPVrJSM = false;
      bool BMpOMKOeme = false;
      bool WBSclGphbC = false;
      bool KuXRzALpNh = false;
      bool DQRWeGpbdG = false;
      bool SOKikijBkJ = false;
      bool eKhQBGnXPM = false;
      bool yXQEaGjuxe = false;
      bool QODUiwkogP = false;
      bool PJFECshAUY = false;
      bool SRMRHtxFHd = false;
      bool znDGrQGNgF = false;
      bool UzqzwoSMBh = false;
      bool YjZYMyClMo = false;
      bool zehDQaFyMl = false;
      bool lUSPDSaMUS = false;
      bool bkDZEPNest = false;
      bool NTArGpRmhV = false;
      bool iTzPuEQKVs = false;
      string BbcWmudIRZ;
      string dDezynjbeN;
      string NyrQIzQPsh;
      string VKxCIdINRZ;
      string qKZjBCjOVV;
      string yISQbDjMOm;
      string eNPiDSFcpT;
      string fWKFVDYIOF;
      string PBtXiMqgZF;
      string tuzdtdupfh;
      string wHXCoayNtY;
      string daxIXcTrAp;
      string bYCkYkXfKr;
      string HibgIHcqhH;
      string OdlAbSxpGR;
      string JDpoGXEmcD;
      string DRDBQuzQzP;
      string AcJrbxlCJF;
      string mgYsiEslak;
      string CoNdEwZjig;
      if(BbcWmudIRZ == wHXCoayNtY){TfpqQgsxNI = true;}
      else if(wHXCoayNtY == BbcWmudIRZ){PJFECshAUY = true;}
      if(dDezynjbeN == daxIXcTrAp){kCdWPVrJSM = true;}
      else if(daxIXcTrAp == dDezynjbeN){SRMRHtxFHd = true;}
      if(NyrQIzQPsh == bYCkYkXfKr){BMpOMKOeme = true;}
      else if(bYCkYkXfKr == NyrQIzQPsh){znDGrQGNgF = true;}
      if(VKxCIdINRZ == HibgIHcqhH){WBSclGphbC = true;}
      else if(HibgIHcqhH == VKxCIdINRZ){UzqzwoSMBh = true;}
      if(qKZjBCjOVV == OdlAbSxpGR){KuXRzALpNh = true;}
      else if(OdlAbSxpGR == qKZjBCjOVV){YjZYMyClMo = true;}
      if(yISQbDjMOm == JDpoGXEmcD){DQRWeGpbdG = true;}
      else if(JDpoGXEmcD == yISQbDjMOm){zehDQaFyMl = true;}
      if(eNPiDSFcpT == DRDBQuzQzP){SOKikijBkJ = true;}
      else if(DRDBQuzQzP == eNPiDSFcpT){lUSPDSaMUS = true;}
      if(fWKFVDYIOF == AcJrbxlCJF){eKhQBGnXPM = true;}
      if(PBtXiMqgZF == mgYsiEslak){yXQEaGjuxe = true;}
      if(tuzdtdupfh == CoNdEwZjig){QODUiwkogP = true;}
      while(AcJrbxlCJF == fWKFVDYIOF){bkDZEPNest = true;}
      while(mgYsiEslak == mgYsiEslak){NTArGpRmhV = true;}
      while(CoNdEwZjig == CoNdEwZjig){iTzPuEQKVs = true;}
      if(TfpqQgsxNI == true){TfpqQgsxNI = false;}
      if(kCdWPVrJSM == true){kCdWPVrJSM = false;}
      if(BMpOMKOeme == true){BMpOMKOeme = false;}
      if(WBSclGphbC == true){WBSclGphbC = false;}
      if(KuXRzALpNh == true){KuXRzALpNh = false;}
      if(DQRWeGpbdG == true){DQRWeGpbdG = false;}
      if(SOKikijBkJ == true){SOKikijBkJ = false;}
      if(eKhQBGnXPM == true){eKhQBGnXPM = false;}
      if(yXQEaGjuxe == true){yXQEaGjuxe = false;}
      if(QODUiwkogP == true){QODUiwkogP = false;}
      if(PJFECshAUY == true){PJFECshAUY = false;}
      if(SRMRHtxFHd == true){SRMRHtxFHd = false;}
      if(znDGrQGNgF == true){znDGrQGNgF = false;}
      if(UzqzwoSMBh == true){UzqzwoSMBh = false;}
      if(YjZYMyClMo == true){YjZYMyClMo = false;}
      if(zehDQaFyMl == true){zehDQaFyMl = false;}
      if(lUSPDSaMUS == true){lUSPDSaMUS = false;}
      if(bkDZEPNest == true){bkDZEPNest = false;}
      if(NTArGpRmhV == true){NTArGpRmhV = false;}
      if(iTzPuEQKVs == true){iTzPuEQKVs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ERJQJXQATX
{ 
  void wMAMBqwCNT()
  { 
      bool RyUCDFcxOR = false;
      bool untnOZABwa = false;
      bool sTSiNWRRuD = false;
      bool niJZIsWePr = false;
      bool QSLGypsyCF = false;
      bool BIRXFxflof = false;
      bool mKBLdMeUeU = false;
      bool CVlDKZILkX = false;
      bool cTOpBeQkTL = false;
      bool NjoiFFRAbk = false;
      bool KYSgCfVNNe = false;
      bool oTARCTuLJy = false;
      bool wsATHSfDyE = false;
      bool IHjzMDBgmV = false;
      bool ICXnWtiXfl = false;
      bool JFpcoRYyZj = false;
      bool zSPIWgjBFy = false;
      bool ROXnpsVLxN = false;
      bool iIWMuCRGKu = false;
      bool eCGDVomORo = false;
      string jLCFDQBdnl;
      string CAIXwmRSNr;
      string REKmDmstGM;
      string xripkEjOcC;
      string VrVBEQolrr;
      string JAMXzfAOBP;
      string XHWanJRRlq;
      string DCoLVZiIil;
      string xGCODxfKqF;
      string EUNMeOUuMt;
      string zWzBoGLBBY;
      string xqfPSQFIWq;
      string dGagmhobfH;
      string FmwolaGAYw;
      string keISIMoxtN;
      string JLXUQswSOH;
      string QiUtTJuqcq;
      string KEiaFyxIYZ;
      string rqhSxsPaXs;
      string dmlReCKOyz;
      if(jLCFDQBdnl == zWzBoGLBBY){RyUCDFcxOR = true;}
      else if(zWzBoGLBBY == jLCFDQBdnl){KYSgCfVNNe = true;}
      if(CAIXwmRSNr == xqfPSQFIWq){untnOZABwa = true;}
      else if(xqfPSQFIWq == CAIXwmRSNr){oTARCTuLJy = true;}
      if(REKmDmstGM == dGagmhobfH){sTSiNWRRuD = true;}
      else if(dGagmhobfH == REKmDmstGM){wsATHSfDyE = true;}
      if(xripkEjOcC == FmwolaGAYw){niJZIsWePr = true;}
      else if(FmwolaGAYw == xripkEjOcC){IHjzMDBgmV = true;}
      if(VrVBEQolrr == keISIMoxtN){QSLGypsyCF = true;}
      else if(keISIMoxtN == VrVBEQolrr){ICXnWtiXfl = true;}
      if(JAMXzfAOBP == JLXUQswSOH){BIRXFxflof = true;}
      else if(JLXUQswSOH == JAMXzfAOBP){JFpcoRYyZj = true;}
      if(XHWanJRRlq == QiUtTJuqcq){mKBLdMeUeU = true;}
      else if(QiUtTJuqcq == XHWanJRRlq){zSPIWgjBFy = true;}
      if(DCoLVZiIil == KEiaFyxIYZ){CVlDKZILkX = true;}
      if(xGCODxfKqF == rqhSxsPaXs){cTOpBeQkTL = true;}
      if(EUNMeOUuMt == dmlReCKOyz){NjoiFFRAbk = true;}
      while(KEiaFyxIYZ == DCoLVZiIil){ROXnpsVLxN = true;}
      while(rqhSxsPaXs == rqhSxsPaXs){iIWMuCRGKu = true;}
      while(dmlReCKOyz == dmlReCKOyz){eCGDVomORo = true;}
      if(RyUCDFcxOR == true){RyUCDFcxOR = false;}
      if(untnOZABwa == true){untnOZABwa = false;}
      if(sTSiNWRRuD == true){sTSiNWRRuD = false;}
      if(niJZIsWePr == true){niJZIsWePr = false;}
      if(QSLGypsyCF == true){QSLGypsyCF = false;}
      if(BIRXFxflof == true){BIRXFxflof = false;}
      if(mKBLdMeUeU == true){mKBLdMeUeU = false;}
      if(CVlDKZILkX == true){CVlDKZILkX = false;}
      if(cTOpBeQkTL == true){cTOpBeQkTL = false;}
      if(NjoiFFRAbk == true){NjoiFFRAbk = false;}
      if(KYSgCfVNNe == true){KYSgCfVNNe = false;}
      if(oTARCTuLJy == true){oTARCTuLJy = false;}
      if(wsATHSfDyE == true){wsATHSfDyE = false;}
      if(IHjzMDBgmV == true){IHjzMDBgmV = false;}
      if(ICXnWtiXfl == true){ICXnWtiXfl = false;}
      if(JFpcoRYyZj == true){JFpcoRYyZj = false;}
      if(zSPIWgjBFy == true){zSPIWgjBFy = false;}
      if(ROXnpsVLxN == true){ROXnpsVLxN = false;}
      if(iIWMuCRGKu == true){iIWMuCRGKu = false;}
      if(eCGDVomORo == true){eCGDVomORo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVFFKIVBDZ
{ 
  void uggNlgeQSr()
  { 
      bool nIWjRsMSnn = false;
      bool cQYHhGsRgK = false;
      bool FXxyzEXkqX = false;
      bool DcSusUfyVI = false;
      bool ksibdspQOr = false;
      bool LriVFPLXkN = false;
      bool UbbQjAxcON = false;
      bool ZuuYYMnVTF = false;
      bool OHVyLLsxoc = false;
      bool JHMInIRSqd = false;
      bool wMCBSQxKws = false;
      bool boDezMGcFY = false;
      bool GAnkDRhmkP = false;
      bool tUdpIBFTft = false;
      bool OiAwBTEhIa = false;
      bool CnNSXuYQxA = false;
      bool hJZgyGLNVx = false;
      bool GlwKKXAqji = false;
      bool NAdJNFHLSN = false;
      bool cnWfMEITxt = false;
      string ytbKhOwDUp;
      string ZJFrLfgBGW;
      string lfqzfQlPmZ;
      string tCpZlYdque;
      string fEBYDjjXtP;
      string dJHQiSDbeQ;
      string cfQtwXSeFm;
      string CpFbqhdRwu;
      string fNVXwkuZpT;
      string UBLdBAnHce;
      string QFSHNnDfZB;
      string okejkPKryK;
      string csnlRAeaZq;
      string sVoRdauNKH;
      string gPzodjWbsl;
      string ouJRBWQfoM;
      string IbFiISuNFJ;
      string TwhpcNtzHh;
      string dChnByMXPG;
      string KOXxyFJQfL;
      if(ytbKhOwDUp == QFSHNnDfZB){nIWjRsMSnn = true;}
      else if(QFSHNnDfZB == ytbKhOwDUp){wMCBSQxKws = true;}
      if(ZJFrLfgBGW == okejkPKryK){cQYHhGsRgK = true;}
      else if(okejkPKryK == ZJFrLfgBGW){boDezMGcFY = true;}
      if(lfqzfQlPmZ == csnlRAeaZq){FXxyzEXkqX = true;}
      else if(csnlRAeaZq == lfqzfQlPmZ){GAnkDRhmkP = true;}
      if(tCpZlYdque == sVoRdauNKH){DcSusUfyVI = true;}
      else if(sVoRdauNKH == tCpZlYdque){tUdpIBFTft = true;}
      if(fEBYDjjXtP == gPzodjWbsl){ksibdspQOr = true;}
      else if(gPzodjWbsl == fEBYDjjXtP){OiAwBTEhIa = true;}
      if(dJHQiSDbeQ == ouJRBWQfoM){LriVFPLXkN = true;}
      else if(ouJRBWQfoM == dJHQiSDbeQ){CnNSXuYQxA = true;}
      if(cfQtwXSeFm == IbFiISuNFJ){UbbQjAxcON = true;}
      else if(IbFiISuNFJ == cfQtwXSeFm){hJZgyGLNVx = true;}
      if(CpFbqhdRwu == TwhpcNtzHh){ZuuYYMnVTF = true;}
      if(fNVXwkuZpT == dChnByMXPG){OHVyLLsxoc = true;}
      if(UBLdBAnHce == KOXxyFJQfL){JHMInIRSqd = true;}
      while(TwhpcNtzHh == CpFbqhdRwu){GlwKKXAqji = true;}
      while(dChnByMXPG == dChnByMXPG){NAdJNFHLSN = true;}
      while(KOXxyFJQfL == KOXxyFJQfL){cnWfMEITxt = true;}
      if(nIWjRsMSnn == true){nIWjRsMSnn = false;}
      if(cQYHhGsRgK == true){cQYHhGsRgK = false;}
      if(FXxyzEXkqX == true){FXxyzEXkqX = false;}
      if(DcSusUfyVI == true){DcSusUfyVI = false;}
      if(ksibdspQOr == true){ksibdspQOr = false;}
      if(LriVFPLXkN == true){LriVFPLXkN = false;}
      if(UbbQjAxcON == true){UbbQjAxcON = false;}
      if(ZuuYYMnVTF == true){ZuuYYMnVTF = false;}
      if(OHVyLLsxoc == true){OHVyLLsxoc = false;}
      if(JHMInIRSqd == true){JHMInIRSqd = false;}
      if(wMCBSQxKws == true){wMCBSQxKws = false;}
      if(boDezMGcFY == true){boDezMGcFY = false;}
      if(GAnkDRhmkP == true){GAnkDRhmkP = false;}
      if(tUdpIBFTft == true){tUdpIBFTft = false;}
      if(OiAwBTEhIa == true){OiAwBTEhIa = false;}
      if(CnNSXuYQxA == true){CnNSXuYQxA = false;}
      if(hJZgyGLNVx == true){hJZgyGLNVx = false;}
      if(GlwKKXAqji == true){GlwKKXAqji = false;}
      if(NAdJNFHLSN == true){NAdJNFHLSN = false;}
      if(cnWfMEITxt == true){cnWfMEITxt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZYMFPMJKM
{ 
  void bRSTNcsqBA()
  { 
      bool UVyfUbBIqI = false;
      bool mfYDomRVrR = false;
      bool UJSWWrIeDH = false;
      bool WJDCEtSnoO = false;
      bool VDfBiBVRPl = false;
      bool PFUzpKDaJb = false;
      bool TVEjkdcWzt = false;
      bool UdfcwRdQnU = false;
      bool WpORrRoELs = false;
      bool qqdMtzzwPF = false;
      bool YzSVQlYqCY = false;
      bool glmoFdGmqT = false;
      bool oYKGDdzShw = false;
      bool RhBhuWXsAF = false;
      bool rxBmMEDoHQ = false;
      bool rLEwQzoMRm = false;
      bool mFJFGzkEsh = false;
      bool GNllaqXWty = false;
      bool ZJLREFcERw = false;
      bool hLaMSmnufM = false;
      string KhEVAGFjix;
      string ElRgkKkscu;
      string BkCojHGZHj;
      string dyppzUFGQe;
      string OKrIPYAcVZ;
      string rStNnYfPls;
      string AfczSGwagQ;
      string EdbxfprsYK;
      string GdDgrKDcCZ;
      string ooUWeihsoJ;
      string cYuEUNqxgx;
      string flqblWbwHI;
      string DSYHbOJERx;
      string IyEPghiyLd;
      string TFwFsCyrkI;
      string GllgFKzmcG;
      string EleinhhbtE;
      string ndjcoxWTNY;
      string QQTJqWMXJW;
      string huVFZgaMQL;
      if(KhEVAGFjix == cYuEUNqxgx){UVyfUbBIqI = true;}
      else if(cYuEUNqxgx == KhEVAGFjix){YzSVQlYqCY = true;}
      if(ElRgkKkscu == flqblWbwHI){mfYDomRVrR = true;}
      else if(flqblWbwHI == ElRgkKkscu){glmoFdGmqT = true;}
      if(BkCojHGZHj == DSYHbOJERx){UJSWWrIeDH = true;}
      else if(DSYHbOJERx == BkCojHGZHj){oYKGDdzShw = true;}
      if(dyppzUFGQe == IyEPghiyLd){WJDCEtSnoO = true;}
      else if(IyEPghiyLd == dyppzUFGQe){RhBhuWXsAF = true;}
      if(OKrIPYAcVZ == TFwFsCyrkI){VDfBiBVRPl = true;}
      else if(TFwFsCyrkI == OKrIPYAcVZ){rxBmMEDoHQ = true;}
      if(rStNnYfPls == GllgFKzmcG){PFUzpKDaJb = true;}
      else if(GllgFKzmcG == rStNnYfPls){rLEwQzoMRm = true;}
      if(AfczSGwagQ == EleinhhbtE){TVEjkdcWzt = true;}
      else if(EleinhhbtE == AfczSGwagQ){mFJFGzkEsh = true;}
      if(EdbxfprsYK == ndjcoxWTNY){UdfcwRdQnU = true;}
      if(GdDgrKDcCZ == QQTJqWMXJW){WpORrRoELs = true;}
      if(ooUWeihsoJ == huVFZgaMQL){qqdMtzzwPF = true;}
      while(ndjcoxWTNY == EdbxfprsYK){GNllaqXWty = true;}
      while(QQTJqWMXJW == QQTJqWMXJW){ZJLREFcERw = true;}
      while(huVFZgaMQL == huVFZgaMQL){hLaMSmnufM = true;}
      if(UVyfUbBIqI == true){UVyfUbBIqI = false;}
      if(mfYDomRVrR == true){mfYDomRVrR = false;}
      if(UJSWWrIeDH == true){UJSWWrIeDH = false;}
      if(WJDCEtSnoO == true){WJDCEtSnoO = false;}
      if(VDfBiBVRPl == true){VDfBiBVRPl = false;}
      if(PFUzpKDaJb == true){PFUzpKDaJb = false;}
      if(TVEjkdcWzt == true){TVEjkdcWzt = false;}
      if(UdfcwRdQnU == true){UdfcwRdQnU = false;}
      if(WpORrRoELs == true){WpORrRoELs = false;}
      if(qqdMtzzwPF == true){qqdMtzzwPF = false;}
      if(YzSVQlYqCY == true){YzSVQlYqCY = false;}
      if(glmoFdGmqT == true){glmoFdGmqT = false;}
      if(oYKGDdzShw == true){oYKGDdzShw = false;}
      if(RhBhuWXsAF == true){RhBhuWXsAF = false;}
      if(rxBmMEDoHQ == true){rxBmMEDoHQ = false;}
      if(rLEwQzoMRm == true){rLEwQzoMRm = false;}
      if(mFJFGzkEsh == true){mFJFGzkEsh = false;}
      if(GNllaqXWty == true){GNllaqXWty = false;}
      if(ZJLREFcERw == true){ZJLREFcERw = false;}
      if(hLaMSmnufM == true){hLaMSmnufM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJZSENIGVX
{ 
  void RCbktXoWDV()
  { 
      bool WyjWwKJzYh = false;
      bool MdflyYJDdC = false;
      bool JyzrXamMct = false;
      bool mCfCyVenyg = false;
      bool YjjfSooaeg = false;
      bool jGzZhXyqzV = false;
      bool XxWetKxdnb = false;
      bool tVFxdZOSYi = false;
      bool lLguKgDGTZ = false;
      bool WmncIaMFkI = false;
      bool qKmDmOBCwI = false;
      bool JeRQiLPbUN = false;
      bool HqJNEGgbnC = false;
      bool MIhQqaYdHw = false;
      bool fAJKQqUXsx = false;
      bool LkkXBzAYyf = false;
      bool gYOtwAxBYI = false;
      bool mkTXgGgyxN = false;
      bool lIiqpaXJOq = false;
      bool ZzfaOHlPOP = false;
      string TYGajbkjjC;
      string IoTNXOkHDT;
      string ndLRcYimBy;
      string oGkSlSKFWd;
      string gUybldKgKE;
      string qfLLlpMnyL;
      string syikMBEBaE;
      string DfkYlTejez;
      string OBbwGJuYfw;
      string GVHKkhlMOk;
      string YIFGALumZS;
      string KbIywrWldC;
      string FfVeyhXZnD;
      string hRUtZFuVwu;
      string OIzMkdMINs;
      string LziMesmaHS;
      string nUyVksHOYq;
      string wBpimxfItU;
      string UOLuqhiIOf;
      string SUNcGsJdbr;
      if(TYGajbkjjC == YIFGALumZS){WyjWwKJzYh = true;}
      else if(YIFGALumZS == TYGajbkjjC){qKmDmOBCwI = true;}
      if(IoTNXOkHDT == KbIywrWldC){MdflyYJDdC = true;}
      else if(KbIywrWldC == IoTNXOkHDT){JeRQiLPbUN = true;}
      if(ndLRcYimBy == FfVeyhXZnD){JyzrXamMct = true;}
      else if(FfVeyhXZnD == ndLRcYimBy){HqJNEGgbnC = true;}
      if(oGkSlSKFWd == hRUtZFuVwu){mCfCyVenyg = true;}
      else if(hRUtZFuVwu == oGkSlSKFWd){MIhQqaYdHw = true;}
      if(gUybldKgKE == OIzMkdMINs){YjjfSooaeg = true;}
      else if(OIzMkdMINs == gUybldKgKE){fAJKQqUXsx = true;}
      if(qfLLlpMnyL == LziMesmaHS){jGzZhXyqzV = true;}
      else if(LziMesmaHS == qfLLlpMnyL){LkkXBzAYyf = true;}
      if(syikMBEBaE == nUyVksHOYq){XxWetKxdnb = true;}
      else if(nUyVksHOYq == syikMBEBaE){gYOtwAxBYI = true;}
      if(DfkYlTejez == wBpimxfItU){tVFxdZOSYi = true;}
      if(OBbwGJuYfw == UOLuqhiIOf){lLguKgDGTZ = true;}
      if(GVHKkhlMOk == SUNcGsJdbr){WmncIaMFkI = true;}
      while(wBpimxfItU == DfkYlTejez){mkTXgGgyxN = true;}
      while(UOLuqhiIOf == UOLuqhiIOf){lIiqpaXJOq = true;}
      while(SUNcGsJdbr == SUNcGsJdbr){ZzfaOHlPOP = true;}
      if(WyjWwKJzYh == true){WyjWwKJzYh = false;}
      if(MdflyYJDdC == true){MdflyYJDdC = false;}
      if(JyzrXamMct == true){JyzrXamMct = false;}
      if(mCfCyVenyg == true){mCfCyVenyg = false;}
      if(YjjfSooaeg == true){YjjfSooaeg = false;}
      if(jGzZhXyqzV == true){jGzZhXyqzV = false;}
      if(XxWetKxdnb == true){XxWetKxdnb = false;}
      if(tVFxdZOSYi == true){tVFxdZOSYi = false;}
      if(lLguKgDGTZ == true){lLguKgDGTZ = false;}
      if(WmncIaMFkI == true){WmncIaMFkI = false;}
      if(qKmDmOBCwI == true){qKmDmOBCwI = false;}
      if(JeRQiLPbUN == true){JeRQiLPbUN = false;}
      if(HqJNEGgbnC == true){HqJNEGgbnC = false;}
      if(MIhQqaYdHw == true){MIhQqaYdHw = false;}
      if(fAJKQqUXsx == true){fAJKQqUXsx = false;}
      if(LkkXBzAYyf == true){LkkXBzAYyf = false;}
      if(gYOtwAxBYI == true){gYOtwAxBYI = false;}
      if(mkTXgGgyxN == true){mkTXgGgyxN = false;}
      if(lIiqpaXJOq == true){lIiqpaXJOq = false;}
      if(ZzfaOHlPOP == true){ZzfaOHlPOP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJTAFMVGHA
{ 
  void muQLQzbCYC()
  { 
      bool ywRKmkUbCe = false;
      bool VpafRRxPTl = false;
      bool DrAKFittek = false;
      bool MPAISbazAt = false;
      bool bzgpFOaPZl = false;
      bool SgaEPFwHEE = false;
      bool pZxRRGoRNo = false;
      bool qxPYKELJEq = false;
      bool HeTsRfnusM = false;
      bool fSuuDBBPXz = false;
      bool YJBktVQBtK = false;
      bool tlCNwLGEzl = false;
      bool RsXBJXBTVI = false;
      bool CulFRyciyw = false;
      bool OlBhRsQhzr = false;
      bool uxPlgekAbW = false;
      bool TxflHyAxuy = false;
      bool hWFCXeroiP = false;
      bool GTUcMFeAXm = false;
      bool McHacRGPZS = false;
      string WqYOAUKQdb;
      string kUPOoUawLl;
      string rMSkdRywgP;
      string tISiYLihzk;
      string WLTHblfRQR;
      string yjqTUJYmkh;
      string WNiNgbCgod;
      string lrxaOgrLJq;
      string kgfORKRyOP;
      string muxQOIbGZz;
      string jzbmfFmQEn;
      string RMdswohUuW;
      string KDRZppufMG;
      string ElkJHlErhM;
      string WBsaxZRDUY;
      string aHKCnfgCwp;
      string JHDyieaUlK;
      string kplhAJKqbQ;
      string YrKnexbiUb;
      string EBurDPxtqS;
      if(WqYOAUKQdb == jzbmfFmQEn){ywRKmkUbCe = true;}
      else if(jzbmfFmQEn == WqYOAUKQdb){YJBktVQBtK = true;}
      if(kUPOoUawLl == RMdswohUuW){VpafRRxPTl = true;}
      else if(RMdswohUuW == kUPOoUawLl){tlCNwLGEzl = true;}
      if(rMSkdRywgP == KDRZppufMG){DrAKFittek = true;}
      else if(KDRZppufMG == rMSkdRywgP){RsXBJXBTVI = true;}
      if(tISiYLihzk == ElkJHlErhM){MPAISbazAt = true;}
      else if(ElkJHlErhM == tISiYLihzk){CulFRyciyw = true;}
      if(WLTHblfRQR == WBsaxZRDUY){bzgpFOaPZl = true;}
      else if(WBsaxZRDUY == WLTHblfRQR){OlBhRsQhzr = true;}
      if(yjqTUJYmkh == aHKCnfgCwp){SgaEPFwHEE = true;}
      else if(aHKCnfgCwp == yjqTUJYmkh){uxPlgekAbW = true;}
      if(WNiNgbCgod == JHDyieaUlK){pZxRRGoRNo = true;}
      else if(JHDyieaUlK == WNiNgbCgod){TxflHyAxuy = true;}
      if(lrxaOgrLJq == kplhAJKqbQ){qxPYKELJEq = true;}
      if(kgfORKRyOP == YrKnexbiUb){HeTsRfnusM = true;}
      if(muxQOIbGZz == EBurDPxtqS){fSuuDBBPXz = true;}
      while(kplhAJKqbQ == lrxaOgrLJq){hWFCXeroiP = true;}
      while(YrKnexbiUb == YrKnexbiUb){GTUcMFeAXm = true;}
      while(EBurDPxtqS == EBurDPxtqS){McHacRGPZS = true;}
      if(ywRKmkUbCe == true){ywRKmkUbCe = false;}
      if(VpafRRxPTl == true){VpafRRxPTl = false;}
      if(DrAKFittek == true){DrAKFittek = false;}
      if(MPAISbazAt == true){MPAISbazAt = false;}
      if(bzgpFOaPZl == true){bzgpFOaPZl = false;}
      if(SgaEPFwHEE == true){SgaEPFwHEE = false;}
      if(pZxRRGoRNo == true){pZxRRGoRNo = false;}
      if(qxPYKELJEq == true){qxPYKELJEq = false;}
      if(HeTsRfnusM == true){HeTsRfnusM = false;}
      if(fSuuDBBPXz == true){fSuuDBBPXz = false;}
      if(YJBktVQBtK == true){YJBktVQBtK = false;}
      if(tlCNwLGEzl == true){tlCNwLGEzl = false;}
      if(RsXBJXBTVI == true){RsXBJXBTVI = false;}
      if(CulFRyciyw == true){CulFRyciyw = false;}
      if(OlBhRsQhzr == true){OlBhRsQhzr = false;}
      if(uxPlgekAbW == true){uxPlgekAbW = false;}
      if(TxflHyAxuy == true){TxflHyAxuy = false;}
      if(hWFCXeroiP == true){hWFCXeroiP = false;}
      if(GTUcMFeAXm == true){GTUcMFeAXm = false;}
      if(McHacRGPZS == true){McHacRGPZS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUTOTVZFAO
{ 
  void DRBhxxCpTp()
  { 
      bool NpwZafCMVF = false;
      bool xOzKmjGEYH = false;
      bool aOxjMDcRbz = false;
      bool McVOofMYTK = false;
      bool VTNhDUErUq = false;
      bool esdJIzsLMW = false;
      bool CkjWsTsjVH = false;
      bool WgkOlGBOgr = false;
      bool ykwjUSzMGo = false;
      bool mALwHkjpoi = false;
      bool bUVNUxHPXB = false;
      bool ydeUYRnzBZ = false;
      bool UfdfTWVoHA = false;
      bool WKZyQdOhPW = false;
      bool KjnEqJVqXo = false;
      bool wjoPNuqpsx = false;
      bool bSIWdmEgDu = false;
      bool DGjdOkrYoK = false;
      bool AeQRDmVJjU = false;
      bool mYoRuraQaD = false;
      string nWHhyVlQyU;
      string EEEakFzyPW;
      string HyFlPlUrzX;
      string ZWUkmSnNTt;
      string HlNeHKJcwY;
      string UGxiEoQUSM;
      string BtRauhjTnR;
      string QkdVPVjadE;
      string cquZDSYkgx;
      string CSuHrMTmiZ;
      string aoodHibbSh;
      string FppNjJyqXb;
      string IylqPypWcD;
      string BxqEcmCRRT;
      string qxRyrMbgWh;
      string NcPHQcDyNJ;
      string sFzPgIykjx;
      string HgZDkKfnyD;
      string VJztpYgjnA;
      string jEDIakyCRj;
      if(nWHhyVlQyU == aoodHibbSh){NpwZafCMVF = true;}
      else if(aoodHibbSh == nWHhyVlQyU){bUVNUxHPXB = true;}
      if(EEEakFzyPW == FppNjJyqXb){xOzKmjGEYH = true;}
      else if(FppNjJyqXb == EEEakFzyPW){ydeUYRnzBZ = true;}
      if(HyFlPlUrzX == IylqPypWcD){aOxjMDcRbz = true;}
      else if(IylqPypWcD == HyFlPlUrzX){UfdfTWVoHA = true;}
      if(ZWUkmSnNTt == BxqEcmCRRT){McVOofMYTK = true;}
      else if(BxqEcmCRRT == ZWUkmSnNTt){WKZyQdOhPW = true;}
      if(HlNeHKJcwY == qxRyrMbgWh){VTNhDUErUq = true;}
      else if(qxRyrMbgWh == HlNeHKJcwY){KjnEqJVqXo = true;}
      if(UGxiEoQUSM == NcPHQcDyNJ){esdJIzsLMW = true;}
      else if(NcPHQcDyNJ == UGxiEoQUSM){wjoPNuqpsx = true;}
      if(BtRauhjTnR == sFzPgIykjx){CkjWsTsjVH = true;}
      else if(sFzPgIykjx == BtRauhjTnR){bSIWdmEgDu = true;}
      if(QkdVPVjadE == HgZDkKfnyD){WgkOlGBOgr = true;}
      if(cquZDSYkgx == VJztpYgjnA){ykwjUSzMGo = true;}
      if(CSuHrMTmiZ == jEDIakyCRj){mALwHkjpoi = true;}
      while(HgZDkKfnyD == QkdVPVjadE){DGjdOkrYoK = true;}
      while(VJztpYgjnA == VJztpYgjnA){AeQRDmVJjU = true;}
      while(jEDIakyCRj == jEDIakyCRj){mYoRuraQaD = true;}
      if(NpwZafCMVF == true){NpwZafCMVF = false;}
      if(xOzKmjGEYH == true){xOzKmjGEYH = false;}
      if(aOxjMDcRbz == true){aOxjMDcRbz = false;}
      if(McVOofMYTK == true){McVOofMYTK = false;}
      if(VTNhDUErUq == true){VTNhDUErUq = false;}
      if(esdJIzsLMW == true){esdJIzsLMW = false;}
      if(CkjWsTsjVH == true){CkjWsTsjVH = false;}
      if(WgkOlGBOgr == true){WgkOlGBOgr = false;}
      if(ykwjUSzMGo == true){ykwjUSzMGo = false;}
      if(mALwHkjpoi == true){mALwHkjpoi = false;}
      if(bUVNUxHPXB == true){bUVNUxHPXB = false;}
      if(ydeUYRnzBZ == true){ydeUYRnzBZ = false;}
      if(UfdfTWVoHA == true){UfdfTWVoHA = false;}
      if(WKZyQdOhPW == true){WKZyQdOhPW = false;}
      if(KjnEqJVqXo == true){KjnEqJVqXo = false;}
      if(wjoPNuqpsx == true){wjoPNuqpsx = false;}
      if(bSIWdmEgDu == true){bSIWdmEgDu = false;}
      if(DGjdOkrYoK == true){DGjdOkrYoK = false;}
      if(AeQRDmVJjU == true){AeQRDmVJjU = false;}
      if(mYoRuraQaD == true){mYoRuraQaD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZAXIOUIVJ
{ 
  void oNlPbPaYiV()
  { 
      bool xLbFBizjtc = false;
      bool WiddBSDtyk = false;
      bool fkIBMXatMU = false;
      bool EZMsueyrHf = false;
      bool MkzZfrtMTV = false;
      bool UDDNAMCard = false;
      bool IFWYXwVkiV = false;
      bool ULmRYukhUT = false;
      bool cNaqzAVzsi = false;
      bool bXAcXHNZCi = false;
      bool WJdxBJQlnE = false;
      bool aUFXAudfZW = false;
      bool aVrztwKJtQ = false;
      bool hLfkxTidop = false;
      bool ijKnHGSbcb = false;
      bool cgAeIARdCF = false;
      bool yHqWWPoTag = false;
      bool LAqjmpLDrm = false;
      bool cifRnAKAbw = false;
      bool BFaiqbsmRr = false;
      string ephhtLrtTw;
      string VLqkzJtjRP;
      string BlmUcJyGBq;
      string HEXMkpeuok;
      string SjCxBgiKAj;
      string DnqbpsCNEk;
      string MksbnQnezI;
      string ezufxRipSw;
      string ZmFRnTMuVr;
      string nRpEXgpaIj;
      string rDKrEDrLeY;
      string JLtIKYfbmU;
      string EsIHUNIqHQ;
      string aIgiDVbNMj;
      string aBQxhbWhsy;
      string BOmnfztDWq;
      string tBDNxBeLFn;
      string xROCtCcLZr;
      string paxJPMUsDD;
      string aYqUoYyCzf;
      if(ephhtLrtTw == rDKrEDrLeY){xLbFBizjtc = true;}
      else if(rDKrEDrLeY == ephhtLrtTw){WJdxBJQlnE = true;}
      if(VLqkzJtjRP == JLtIKYfbmU){WiddBSDtyk = true;}
      else if(JLtIKYfbmU == VLqkzJtjRP){aUFXAudfZW = true;}
      if(BlmUcJyGBq == EsIHUNIqHQ){fkIBMXatMU = true;}
      else if(EsIHUNIqHQ == BlmUcJyGBq){aVrztwKJtQ = true;}
      if(HEXMkpeuok == aIgiDVbNMj){EZMsueyrHf = true;}
      else if(aIgiDVbNMj == HEXMkpeuok){hLfkxTidop = true;}
      if(SjCxBgiKAj == aBQxhbWhsy){MkzZfrtMTV = true;}
      else if(aBQxhbWhsy == SjCxBgiKAj){ijKnHGSbcb = true;}
      if(DnqbpsCNEk == BOmnfztDWq){UDDNAMCard = true;}
      else if(BOmnfztDWq == DnqbpsCNEk){cgAeIARdCF = true;}
      if(MksbnQnezI == tBDNxBeLFn){IFWYXwVkiV = true;}
      else if(tBDNxBeLFn == MksbnQnezI){yHqWWPoTag = true;}
      if(ezufxRipSw == xROCtCcLZr){ULmRYukhUT = true;}
      if(ZmFRnTMuVr == paxJPMUsDD){cNaqzAVzsi = true;}
      if(nRpEXgpaIj == aYqUoYyCzf){bXAcXHNZCi = true;}
      while(xROCtCcLZr == ezufxRipSw){LAqjmpLDrm = true;}
      while(paxJPMUsDD == paxJPMUsDD){cifRnAKAbw = true;}
      while(aYqUoYyCzf == aYqUoYyCzf){BFaiqbsmRr = true;}
      if(xLbFBizjtc == true){xLbFBizjtc = false;}
      if(WiddBSDtyk == true){WiddBSDtyk = false;}
      if(fkIBMXatMU == true){fkIBMXatMU = false;}
      if(EZMsueyrHf == true){EZMsueyrHf = false;}
      if(MkzZfrtMTV == true){MkzZfrtMTV = false;}
      if(UDDNAMCard == true){UDDNAMCard = false;}
      if(IFWYXwVkiV == true){IFWYXwVkiV = false;}
      if(ULmRYukhUT == true){ULmRYukhUT = false;}
      if(cNaqzAVzsi == true){cNaqzAVzsi = false;}
      if(bXAcXHNZCi == true){bXAcXHNZCi = false;}
      if(WJdxBJQlnE == true){WJdxBJQlnE = false;}
      if(aUFXAudfZW == true){aUFXAudfZW = false;}
      if(aVrztwKJtQ == true){aVrztwKJtQ = false;}
      if(hLfkxTidop == true){hLfkxTidop = false;}
      if(ijKnHGSbcb == true){ijKnHGSbcb = false;}
      if(cgAeIARdCF == true){cgAeIARdCF = false;}
      if(yHqWWPoTag == true){yHqWWPoTag = false;}
      if(LAqjmpLDrm == true){LAqjmpLDrm = false;}
      if(cifRnAKAbw == true){cifRnAKAbw = false;}
      if(BFaiqbsmRr == true){BFaiqbsmRr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RYNIXEPSGY
{ 
  void fIExpipSmX()
  { 
      bool TIABZasins = false;
      bool cTAKYqCRbK = false;
      bool mVogyUdJAC = false;
      bool PLTgMpmRPt = false;
      bool swdZmsDLkS = false;
      bool sFBXGxSSDE = false;
      bool wjikdRzSxi = false;
      bool EjChRpqPtE = false;
      bool RSYhIJKwZO = false;
      bool WTOKxJNswV = false;
      bool tjNBNJDTFP = false;
      bool GDXymdKAcU = false;
      bool GCsiLjVrjI = false;
      bool cyTYJgFWTy = false;
      bool FppJITwPWT = false;
      bool yMPaOrqdpd = false;
      bool nKixmHjznG = false;
      bool YngdOQLiZr = false;
      bool nFUQKPhrKR = false;
      bool pafoKtHsWA = false;
      string ewxpnwUczD;
      string AjuFoZzjng;
      string zUwooEzNEq;
      string QIykNAhgsy;
      string wmBopUPFUg;
      string juieIJzHBj;
      string xGYHlqkKqo;
      string qRqokMSHzT;
      string nssWHVYTbD;
      string AafJBoNsCz;
      string jFOfoRDtsw;
      string qrIguDNBAQ;
      string SQimnQlhmw;
      string yYEziieNhp;
      string ReafMHRyNy;
      string aMslgTVaqX;
      string fVGxxSnIxL;
      string YASKympCaf;
      string znToUleRSP;
      string NDVJKwXdit;
      if(ewxpnwUczD == jFOfoRDtsw){TIABZasins = true;}
      else if(jFOfoRDtsw == ewxpnwUczD){tjNBNJDTFP = true;}
      if(AjuFoZzjng == qrIguDNBAQ){cTAKYqCRbK = true;}
      else if(qrIguDNBAQ == AjuFoZzjng){GDXymdKAcU = true;}
      if(zUwooEzNEq == SQimnQlhmw){mVogyUdJAC = true;}
      else if(SQimnQlhmw == zUwooEzNEq){GCsiLjVrjI = true;}
      if(QIykNAhgsy == yYEziieNhp){PLTgMpmRPt = true;}
      else if(yYEziieNhp == QIykNAhgsy){cyTYJgFWTy = true;}
      if(wmBopUPFUg == ReafMHRyNy){swdZmsDLkS = true;}
      else if(ReafMHRyNy == wmBopUPFUg){FppJITwPWT = true;}
      if(juieIJzHBj == aMslgTVaqX){sFBXGxSSDE = true;}
      else if(aMslgTVaqX == juieIJzHBj){yMPaOrqdpd = true;}
      if(xGYHlqkKqo == fVGxxSnIxL){wjikdRzSxi = true;}
      else if(fVGxxSnIxL == xGYHlqkKqo){nKixmHjznG = true;}
      if(qRqokMSHzT == YASKympCaf){EjChRpqPtE = true;}
      if(nssWHVYTbD == znToUleRSP){RSYhIJKwZO = true;}
      if(AafJBoNsCz == NDVJKwXdit){WTOKxJNswV = true;}
      while(YASKympCaf == qRqokMSHzT){YngdOQLiZr = true;}
      while(znToUleRSP == znToUleRSP){nFUQKPhrKR = true;}
      while(NDVJKwXdit == NDVJKwXdit){pafoKtHsWA = true;}
      if(TIABZasins == true){TIABZasins = false;}
      if(cTAKYqCRbK == true){cTAKYqCRbK = false;}
      if(mVogyUdJAC == true){mVogyUdJAC = false;}
      if(PLTgMpmRPt == true){PLTgMpmRPt = false;}
      if(swdZmsDLkS == true){swdZmsDLkS = false;}
      if(sFBXGxSSDE == true){sFBXGxSSDE = false;}
      if(wjikdRzSxi == true){wjikdRzSxi = false;}
      if(EjChRpqPtE == true){EjChRpqPtE = false;}
      if(RSYhIJKwZO == true){RSYhIJKwZO = false;}
      if(WTOKxJNswV == true){WTOKxJNswV = false;}
      if(tjNBNJDTFP == true){tjNBNJDTFP = false;}
      if(GDXymdKAcU == true){GDXymdKAcU = false;}
      if(GCsiLjVrjI == true){GCsiLjVrjI = false;}
      if(cyTYJgFWTy == true){cyTYJgFWTy = false;}
      if(FppJITwPWT == true){FppJITwPWT = false;}
      if(yMPaOrqdpd == true){yMPaOrqdpd = false;}
      if(nKixmHjznG == true){nKixmHjznG = false;}
      if(YngdOQLiZr == true){YngdOQLiZr = false;}
      if(nFUQKPhrKR == true){nFUQKPhrKR = false;}
      if(pafoKtHsWA == true){pafoKtHsWA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXLVSJLQNA
{ 
  void FswiDsNHUf()
  { 
      bool HOcHqJouTj = false;
      bool alQgYoDNDq = false;
      bool jnDBDggkgI = false;
      bool fpcaOkrNDZ = false;
      bool oNhCBmqenW = false;
      bool VdYXHTLbDK = false;
      bool bDOLDjJoSn = false;
      bool woJcBWFAzQ = false;
      bool oBwJmBRFSt = false;
      bool YQJsxkyWyQ = false;
      bool dCMAafUuVj = false;
      bool OLblUaHFXC = false;
      bool SDVXPfePeP = false;
      bool YhBhmmowiG = false;
      bool gViifNnWYW = false;
      bool dsywyZfnkt = false;
      bool BEQGLfJszh = false;
      bool lKVRUxTmrB = false;
      bool qHqIkfjEjM = false;
      bool GALnFbFcWz = false;
      string eIhtHfSDBh;
      string agMJpFhccy;
      string ciZTxRMYxa;
      string bQJKZbGBGj;
      string DhenqzIbld;
      string RAdTkuhOwo;
      string TtGZGKXCjO;
      string yfWruuDlbx;
      string JklTJaloZd;
      string trEQPJbFgg;
      string bFqXfldkYo;
      string qulyfiHmQe;
      string YibGUGaFcl;
      string TyEuVDsOmW;
      string xAPjlyFFjg;
      string BnoCIsdkCZ;
      string KXImVsppcc;
      string orzshXSqTV;
      string AUUujeICmb;
      string YILNMYqbOr;
      if(eIhtHfSDBh == bFqXfldkYo){HOcHqJouTj = true;}
      else if(bFqXfldkYo == eIhtHfSDBh){dCMAafUuVj = true;}
      if(agMJpFhccy == qulyfiHmQe){alQgYoDNDq = true;}
      else if(qulyfiHmQe == agMJpFhccy){OLblUaHFXC = true;}
      if(ciZTxRMYxa == YibGUGaFcl){jnDBDggkgI = true;}
      else if(YibGUGaFcl == ciZTxRMYxa){SDVXPfePeP = true;}
      if(bQJKZbGBGj == TyEuVDsOmW){fpcaOkrNDZ = true;}
      else if(TyEuVDsOmW == bQJKZbGBGj){YhBhmmowiG = true;}
      if(DhenqzIbld == xAPjlyFFjg){oNhCBmqenW = true;}
      else if(xAPjlyFFjg == DhenqzIbld){gViifNnWYW = true;}
      if(RAdTkuhOwo == BnoCIsdkCZ){VdYXHTLbDK = true;}
      else if(BnoCIsdkCZ == RAdTkuhOwo){dsywyZfnkt = true;}
      if(TtGZGKXCjO == KXImVsppcc){bDOLDjJoSn = true;}
      else if(KXImVsppcc == TtGZGKXCjO){BEQGLfJszh = true;}
      if(yfWruuDlbx == orzshXSqTV){woJcBWFAzQ = true;}
      if(JklTJaloZd == AUUujeICmb){oBwJmBRFSt = true;}
      if(trEQPJbFgg == YILNMYqbOr){YQJsxkyWyQ = true;}
      while(orzshXSqTV == yfWruuDlbx){lKVRUxTmrB = true;}
      while(AUUujeICmb == AUUujeICmb){qHqIkfjEjM = true;}
      while(YILNMYqbOr == YILNMYqbOr){GALnFbFcWz = true;}
      if(HOcHqJouTj == true){HOcHqJouTj = false;}
      if(alQgYoDNDq == true){alQgYoDNDq = false;}
      if(jnDBDggkgI == true){jnDBDggkgI = false;}
      if(fpcaOkrNDZ == true){fpcaOkrNDZ = false;}
      if(oNhCBmqenW == true){oNhCBmqenW = false;}
      if(VdYXHTLbDK == true){VdYXHTLbDK = false;}
      if(bDOLDjJoSn == true){bDOLDjJoSn = false;}
      if(woJcBWFAzQ == true){woJcBWFAzQ = false;}
      if(oBwJmBRFSt == true){oBwJmBRFSt = false;}
      if(YQJsxkyWyQ == true){YQJsxkyWyQ = false;}
      if(dCMAafUuVj == true){dCMAafUuVj = false;}
      if(OLblUaHFXC == true){OLblUaHFXC = false;}
      if(SDVXPfePeP == true){SDVXPfePeP = false;}
      if(YhBhmmowiG == true){YhBhmmowiG = false;}
      if(gViifNnWYW == true){gViifNnWYW = false;}
      if(dsywyZfnkt == true){dsywyZfnkt = false;}
      if(BEQGLfJszh == true){BEQGLfJszh = false;}
      if(lKVRUxTmrB == true){lKVRUxTmrB = false;}
      if(qHqIkfjEjM == true){qHqIkfjEjM = false;}
      if(GALnFbFcWz == true){GALnFbFcWz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BVTOLIBPGC
{ 
  void UBIoGDRYwE()
  { 
      bool ZzWfxZZseJ = false;
      bool mIxyHkbDtO = false;
      bool CisrDVfPql = false;
      bool VnjQhwFFcN = false;
      bool TWaYaRQRgd = false;
      bool ZJrfYqFdca = false;
      bool tKCrmzYgQK = false;
      bool eVZgteHURk = false;
      bool EOhMMMuDqq = false;
      bool pacBTJUhkb = false;
      bool sjAWzEiKlt = false;
      bool jkMqVebofa = false;
      bool DUoZTDsYNk = false;
      bool KYiorUNLNI = false;
      bool ckRxHFOlen = false;
      bool geCKXXtaCu = false;
      bool KKxAiKCWyB = false;
      bool RQbXySDrSN = false;
      bool oGsYDeWXRT = false;
      bool alIRxRmRNw = false;
      string APFgRuEHVX;
      string oZqgtYHrPQ;
      string mQCKJibhso;
      string qnNTOrXlnn;
      string NnQDSWuufa;
      string qPMxgjNtWh;
      string TVNgfAMWSC;
      string AVDbCzzyrm;
      string nfBRxbaPme;
      string ecOFTqZiXR;
      string KXcdaULkth;
      string jPCjtmTuiE;
      string ZwjmWWHxHL;
      string YQZZcPDXqc;
      string PpVEuOadLg;
      string WdzTrNnoGD;
      string NNdiJSobHe;
      string jwDGniaerH;
      string wclZntQGhO;
      string aNQnPBMmub;
      if(APFgRuEHVX == KXcdaULkth){ZzWfxZZseJ = true;}
      else if(KXcdaULkth == APFgRuEHVX){sjAWzEiKlt = true;}
      if(oZqgtYHrPQ == jPCjtmTuiE){mIxyHkbDtO = true;}
      else if(jPCjtmTuiE == oZqgtYHrPQ){jkMqVebofa = true;}
      if(mQCKJibhso == ZwjmWWHxHL){CisrDVfPql = true;}
      else if(ZwjmWWHxHL == mQCKJibhso){DUoZTDsYNk = true;}
      if(qnNTOrXlnn == YQZZcPDXqc){VnjQhwFFcN = true;}
      else if(YQZZcPDXqc == qnNTOrXlnn){KYiorUNLNI = true;}
      if(NnQDSWuufa == PpVEuOadLg){TWaYaRQRgd = true;}
      else if(PpVEuOadLg == NnQDSWuufa){ckRxHFOlen = true;}
      if(qPMxgjNtWh == WdzTrNnoGD){ZJrfYqFdca = true;}
      else if(WdzTrNnoGD == qPMxgjNtWh){geCKXXtaCu = true;}
      if(TVNgfAMWSC == NNdiJSobHe){tKCrmzYgQK = true;}
      else if(NNdiJSobHe == TVNgfAMWSC){KKxAiKCWyB = true;}
      if(AVDbCzzyrm == jwDGniaerH){eVZgteHURk = true;}
      if(nfBRxbaPme == wclZntQGhO){EOhMMMuDqq = true;}
      if(ecOFTqZiXR == aNQnPBMmub){pacBTJUhkb = true;}
      while(jwDGniaerH == AVDbCzzyrm){RQbXySDrSN = true;}
      while(wclZntQGhO == wclZntQGhO){oGsYDeWXRT = true;}
      while(aNQnPBMmub == aNQnPBMmub){alIRxRmRNw = true;}
      if(ZzWfxZZseJ == true){ZzWfxZZseJ = false;}
      if(mIxyHkbDtO == true){mIxyHkbDtO = false;}
      if(CisrDVfPql == true){CisrDVfPql = false;}
      if(VnjQhwFFcN == true){VnjQhwFFcN = false;}
      if(TWaYaRQRgd == true){TWaYaRQRgd = false;}
      if(ZJrfYqFdca == true){ZJrfYqFdca = false;}
      if(tKCrmzYgQK == true){tKCrmzYgQK = false;}
      if(eVZgteHURk == true){eVZgteHURk = false;}
      if(EOhMMMuDqq == true){EOhMMMuDqq = false;}
      if(pacBTJUhkb == true){pacBTJUhkb = false;}
      if(sjAWzEiKlt == true){sjAWzEiKlt = false;}
      if(jkMqVebofa == true){jkMqVebofa = false;}
      if(DUoZTDsYNk == true){DUoZTDsYNk = false;}
      if(KYiorUNLNI == true){KYiorUNLNI = false;}
      if(ckRxHFOlen == true){ckRxHFOlen = false;}
      if(geCKXXtaCu == true){geCKXXtaCu = false;}
      if(KKxAiKCWyB == true){KKxAiKCWyB = false;}
      if(RQbXySDrSN == true){RQbXySDrSN = false;}
      if(oGsYDeWXRT == true){oGsYDeWXRT = false;}
      if(alIRxRmRNw == true){alIRxRmRNw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RBGRPSSGDK
{ 
  void PXiHOZBMcu()
  { 
      bool AJkJTobwIM = false;
      bool DyKkUScPNS = false;
      bool CzxpfyqDxU = false;
      bool eNJnkgcGuE = false;
      bool wPyJOkQakC = false;
      bool ocEZUAMtcV = false;
      bool xXzmhpoWzn = false;
      bool pWUJVmBmbu = false;
      bool gPStfBIiSj = false;
      bool UicYGYPLbX = false;
      bool usbxMSItEg = false;
      bool zYRhohFFGf = false;
      bool hFDOSHsuDx = false;
      bool XpLEAmnVgN = false;
      bool rNelkwQtjY = false;
      bool SJEuoopMdF = false;
      bool YMqHJJMNhB = false;
      bool tiYrmTZRcW = false;
      bool pyLedNkPOK = false;
      bool xaqbofWXcb = false;
      string PenQyyNgHd;
      string oCnHZkaGij;
      string SLccKdJZEt;
      string necPgRNMsG;
      string SryipQJsZE;
      string CuRJcECLFT;
      string nncMpJZXZI;
      string WNNbQaMtlt;
      string UQAAqrNSlc;
      string OCGYReOkrf;
      string qkSQgnhorC;
      string qHYLzXmcVx;
      string wGkxsUHoJk;
      string LbBFCixjSC;
      string KYZjlHctYt;
      string rlPujjAVWM;
      string greHqOGSJP;
      string ZDJSmXfBKl;
      string qNPPsYMGVS;
      string ibMGVRsSrW;
      if(PenQyyNgHd == qkSQgnhorC){AJkJTobwIM = true;}
      else if(qkSQgnhorC == PenQyyNgHd){usbxMSItEg = true;}
      if(oCnHZkaGij == qHYLzXmcVx){DyKkUScPNS = true;}
      else if(qHYLzXmcVx == oCnHZkaGij){zYRhohFFGf = true;}
      if(SLccKdJZEt == wGkxsUHoJk){CzxpfyqDxU = true;}
      else if(wGkxsUHoJk == SLccKdJZEt){hFDOSHsuDx = true;}
      if(necPgRNMsG == LbBFCixjSC){eNJnkgcGuE = true;}
      else if(LbBFCixjSC == necPgRNMsG){XpLEAmnVgN = true;}
      if(SryipQJsZE == KYZjlHctYt){wPyJOkQakC = true;}
      else if(KYZjlHctYt == SryipQJsZE){rNelkwQtjY = true;}
      if(CuRJcECLFT == rlPujjAVWM){ocEZUAMtcV = true;}
      else if(rlPujjAVWM == CuRJcECLFT){SJEuoopMdF = true;}
      if(nncMpJZXZI == greHqOGSJP){xXzmhpoWzn = true;}
      else if(greHqOGSJP == nncMpJZXZI){YMqHJJMNhB = true;}
      if(WNNbQaMtlt == ZDJSmXfBKl){pWUJVmBmbu = true;}
      if(UQAAqrNSlc == qNPPsYMGVS){gPStfBIiSj = true;}
      if(OCGYReOkrf == ibMGVRsSrW){UicYGYPLbX = true;}
      while(ZDJSmXfBKl == WNNbQaMtlt){tiYrmTZRcW = true;}
      while(qNPPsYMGVS == qNPPsYMGVS){pyLedNkPOK = true;}
      while(ibMGVRsSrW == ibMGVRsSrW){xaqbofWXcb = true;}
      if(AJkJTobwIM == true){AJkJTobwIM = false;}
      if(DyKkUScPNS == true){DyKkUScPNS = false;}
      if(CzxpfyqDxU == true){CzxpfyqDxU = false;}
      if(eNJnkgcGuE == true){eNJnkgcGuE = false;}
      if(wPyJOkQakC == true){wPyJOkQakC = false;}
      if(ocEZUAMtcV == true){ocEZUAMtcV = false;}
      if(xXzmhpoWzn == true){xXzmhpoWzn = false;}
      if(pWUJVmBmbu == true){pWUJVmBmbu = false;}
      if(gPStfBIiSj == true){gPStfBIiSj = false;}
      if(UicYGYPLbX == true){UicYGYPLbX = false;}
      if(usbxMSItEg == true){usbxMSItEg = false;}
      if(zYRhohFFGf == true){zYRhohFFGf = false;}
      if(hFDOSHsuDx == true){hFDOSHsuDx = false;}
      if(XpLEAmnVgN == true){XpLEAmnVgN = false;}
      if(rNelkwQtjY == true){rNelkwQtjY = false;}
      if(SJEuoopMdF == true){SJEuoopMdF = false;}
      if(YMqHJJMNhB == true){YMqHJJMNhB = false;}
      if(tiYrmTZRcW == true){tiYrmTZRcW = false;}
      if(pyLedNkPOK == true){pyLedNkPOK = false;}
      if(xaqbofWXcb == true){xaqbofWXcb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BONTZTDGWN
{ 
  void JaFEjbmTQz()
  { 
      bool morPLdIODj = false;
      bool SSpTkJOYWo = false;
      bool KthinXylQU = false;
      bool SeBjGUlwhB = false;
      bool ddNcRgaQNN = false;
      bool gUVWqsGJam = false;
      bool fWxhRnQGNP = false;
      bool WRqVKfgEQH = false;
      bool wgYDmxIerN = false;
      bool NcVtUHgeLd = false;
      bool PUDxpPdALK = false;
      bool MBsSqzxsuT = false;
      bool flNzCtuwAC = false;
      bool zBslqbcaNX = false;
      bool TIShBLiCCV = false;
      bool KmjrycGDuu = false;
      bool TgzILKIGaP = false;
      bool VWeWzWTfyp = false;
      bool KrserLRBnN = false;
      bool UZfSDmJJVp = false;
      string mjdDCexPOx;
      string NzTwVExIOg;
      string npxuQLfFDX;
      string wQiOAgVwQj;
      string oirGRbqQwV;
      string ghqoOwlhlp;
      string zrLpAxPEwn;
      string hBqeqExpdo;
      string TOIgqNYtAE;
      string unJakxXCGU;
      string MlUInfqMxJ;
      string yuExWjidzm;
      string XUEqssqQtt;
      string gujIchtAsL;
      string WLwpFzjMDA;
      string NsCTwqhcOt;
      string naSDcDLuTn;
      string oiknPMXOlt;
      string JeMsfmrQMk;
      string ARkyWussMB;
      if(mjdDCexPOx == MlUInfqMxJ){morPLdIODj = true;}
      else if(MlUInfqMxJ == mjdDCexPOx){PUDxpPdALK = true;}
      if(NzTwVExIOg == yuExWjidzm){SSpTkJOYWo = true;}
      else if(yuExWjidzm == NzTwVExIOg){MBsSqzxsuT = true;}
      if(npxuQLfFDX == XUEqssqQtt){KthinXylQU = true;}
      else if(XUEqssqQtt == npxuQLfFDX){flNzCtuwAC = true;}
      if(wQiOAgVwQj == gujIchtAsL){SeBjGUlwhB = true;}
      else if(gujIchtAsL == wQiOAgVwQj){zBslqbcaNX = true;}
      if(oirGRbqQwV == WLwpFzjMDA){ddNcRgaQNN = true;}
      else if(WLwpFzjMDA == oirGRbqQwV){TIShBLiCCV = true;}
      if(ghqoOwlhlp == NsCTwqhcOt){gUVWqsGJam = true;}
      else if(NsCTwqhcOt == ghqoOwlhlp){KmjrycGDuu = true;}
      if(zrLpAxPEwn == naSDcDLuTn){fWxhRnQGNP = true;}
      else if(naSDcDLuTn == zrLpAxPEwn){TgzILKIGaP = true;}
      if(hBqeqExpdo == oiknPMXOlt){WRqVKfgEQH = true;}
      if(TOIgqNYtAE == JeMsfmrQMk){wgYDmxIerN = true;}
      if(unJakxXCGU == ARkyWussMB){NcVtUHgeLd = true;}
      while(oiknPMXOlt == hBqeqExpdo){VWeWzWTfyp = true;}
      while(JeMsfmrQMk == JeMsfmrQMk){KrserLRBnN = true;}
      while(ARkyWussMB == ARkyWussMB){UZfSDmJJVp = true;}
      if(morPLdIODj == true){morPLdIODj = false;}
      if(SSpTkJOYWo == true){SSpTkJOYWo = false;}
      if(KthinXylQU == true){KthinXylQU = false;}
      if(SeBjGUlwhB == true){SeBjGUlwhB = false;}
      if(ddNcRgaQNN == true){ddNcRgaQNN = false;}
      if(gUVWqsGJam == true){gUVWqsGJam = false;}
      if(fWxhRnQGNP == true){fWxhRnQGNP = false;}
      if(WRqVKfgEQH == true){WRqVKfgEQH = false;}
      if(wgYDmxIerN == true){wgYDmxIerN = false;}
      if(NcVtUHgeLd == true){NcVtUHgeLd = false;}
      if(PUDxpPdALK == true){PUDxpPdALK = false;}
      if(MBsSqzxsuT == true){MBsSqzxsuT = false;}
      if(flNzCtuwAC == true){flNzCtuwAC = false;}
      if(zBslqbcaNX == true){zBslqbcaNX = false;}
      if(TIShBLiCCV == true){TIShBLiCCV = false;}
      if(KmjrycGDuu == true){KmjrycGDuu = false;}
      if(TgzILKIGaP == true){TgzILKIGaP = false;}
      if(VWeWzWTfyp == true){VWeWzWTfyp = false;}
      if(KrserLRBnN == true){KrserLRBnN = false;}
      if(UZfSDmJJVp == true){UZfSDmJJVp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUCLNHYCKN
{ 
  void fBaGhdTMcI()
  { 
      bool REnVCEouGk = false;
      bool HoqTbSWbWt = false;
      bool YZjVqQrQtd = false;
      bool SbcRxbfnCQ = false;
      bool wdCuUiynPZ = false;
      bool WMXZsqTSdk = false;
      bool LXBbSeLYVA = false;
      bool miZGyuXnBI = false;
      bool SDAUHFECYG = false;
      bool HMJQEXbZco = false;
      bool WZSPlnmRby = false;
      bool SeRVSHWgUM = false;
      bool aIzPrZYIBZ = false;
      bool SyLLlrkkhT = false;
      bool Smaambunyx = false;
      bool BuFPNNZDWM = false;
      bool OdQCeUSFia = false;
      bool WlzAtnhYbP = false;
      bool ekKDYWswyX = false;
      bool RgNUFnWYuR = false;
      string PmyzxTVIKq;
      string AFcQFSsgwG;
      string WAxKxgAjmS;
      string nHrToOCtZA;
      string ieqfOBpFra;
      string sjqoGPonBP;
      string SkVqCsMJbq;
      string QzGwXrIRww;
      string purLZEPDNY;
      string YNrKhxIAcV;
      string ngdBKtcuRO;
      string HXrFYXrKRy;
      string cJuCRCGwOZ;
      string iInZHJQqAe;
      string aUlzRBVlkJ;
      string EyhesekaiI;
      string mggqeziRyP;
      string GAJlXHWwjP;
      string fUKEUkZJgb;
      string XoIrrsntTS;
      if(PmyzxTVIKq == ngdBKtcuRO){REnVCEouGk = true;}
      else if(ngdBKtcuRO == PmyzxTVIKq){WZSPlnmRby = true;}
      if(AFcQFSsgwG == HXrFYXrKRy){HoqTbSWbWt = true;}
      else if(HXrFYXrKRy == AFcQFSsgwG){SeRVSHWgUM = true;}
      if(WAxKxgAjmS == cJuCRCGwOZ){YZjVqQrQtd = true;}
      else if(cJuCRCGwOZ == WAxKxgAjmS){aIzPrZYIBZ = true;}
      if(nHrToOCtZA == iInZHJQqAe){SbcRxbfnCQ = true;}
      else if(iInZHJQqAe == nHrToOCtZA){SyLLlrkkhT = true;}
      if(ieqfOBpFra == aUlzRBVlkJ){wdCuUiynPZ = true;}
      else if(aUlzRBVlkJ == ieqfOBpFra){Smaambunyx = true;}
      if(sjqoGPonBP == EyhesekaiI){WMXZsqTSdk = true;}
      else if(EyhesekaiI == sjqoGPonBP){BuFPNNZDWM = true;}
      if(SkVqCsMJbq == mggqeziRyP){LXBbSeLYVA = true;}
      else if(mggqeziRyP == SkVqCsMJbq){OdQCeUSFia = true;}
      if(QzGwXrIRww == GAJlXHWwjP){miZGyuXnBI = true;}
      if(purLZEPDNY == fUKEUkZJgb){SDAUHFECYG = true;}
      if(YNrKhxIAcV == XoIrrsntTS){HMJQEXbZco = true;}
      while(GAJlXHWwjP == QzGwXrIRww){WlzAtnhYbP = true;}
      while(fUKEUkZJgb == fUKEUkZJgb){ekKDYWswyX = true;}
      while(XoIrrsntTS == XoIrrsntTS){RgNUFnWYuR = true;}
      if(REnVCEouGk == true){REnVCEouGk = false;}
      if(HoqTbSWbWt == true){HoqTbSWbWt = false;}
      if(YZjVqQrQtd == true){YZjVqQrQtd = false;}
      if(SbcRxbfnCQ == true){SbcRxbfnCQ = false;}
      if(wdCuUiynPZ == true){wdCuUiynPZ = false;}
      if(WMXZsqTSdk == true){WMXZsqTSdk = false;}
      if(LXBbSeLYVA == true){LXBbSeLYVA = false;}
      if(miZGyuXnBI == true){miZGyuXnBI = false;}
      if(SDAUHFECYG == true){SDAUHFECYG = false;}
      if(HMJQEXbZco == true){HMJQEXbZco = false;}
      if(WZSPlnmRby == true){WZSPlnmRby = false;}
      if(SeRVSHWgUM == true){SeRVSHWgUM = false;}
      if(aIzPrZYIBZ == true){aIzPrZYIBZ = false;}
      if(SyLLlrkkhT == true){SyLLlrkkhT = false;}
      if(Smaambunyx == true){Smaambunyx = false;}
      if(BuFPNNZDWM == true){BuFPNNZDWM = false;}
      if(OdQCeUSFia == true){OdQCeUSFia = false;}
      if(WlzAtnhYbP == true){WlzAtnhYbP = false;}
      if(ekKDYWswyX == true){ekKDYWswyX = false;}
      if(RgNUFnWYuR == true){RgNUFnWYuR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFSTTVEEBC
{ 
  void sgOaxUzGGX()
  { 
      bool IPnANjRYbJ = false;
      bool ulgsrhwgWk = false;
      bool rSBGOXBVRq = false;
      bool WhGBsFtCgh = false;
      bool WGaKqURAkr = false;
      bool uQJfJoOhkp = false;
      bool iuGjlMeeAm = false;
      bool mtAoOkrpOs = false;
      bool FBkZwGXarD = false;
      bool qMQpzaApXd = false;
      bool plAyEBPTQX = false;
      bool wXSqkgKfnf = false;
      bool nDlwuacKom = false;
      bool jBSjDSBlVt = false;
      bool pEKTGTsZES = false;
      bool QUCrplADCd = false;
      bool YFddnuFinR = false;
      bool eYKsojsSob = false;
      bool gDFWWPzZtQ = false;
      bool SxiqVkZffL = false;
      string aVVOmoePyK;
      string oIOkyUnTTW;
      string lHhaiIjhFp;
      string TMLYNDDCmw;
      string KUJeBqQlUo;
      string REeAzSntfe;
      string FwJHqbwpXu;
      string RkgWMRyDYq;
      string ryNQXOhLYt;
      string PIVIqNKBnY;
      string uaNZXfXHng;
      string UkVomGhsjb;
      string tkQcfIPXfy;
      string GxOzwQjmsq;
      string qZWrZdlgVk;
      string eRRLeJKktO;
      string QzbpaXVWsV;
      string WuArjUOXDB;
      string ViCtSofCUl;
      string GzsdZrxgRB;
      if(aVVOmoePyK == uaNZXfXHng){IPnANjRYbJ = true;}
      else if(uaNZXfXHng == aVVOmoePyK){plAyEBPTQX = true;}
      if(oIOkyUnTTW == UkVomGhsjb){ulgsrhwgWk = true;}
      else if(UkVomGhsjb == oIOkyUnTTW){wXSqkgKfnf = true;}
      if(lHhaiIjhFp == tkQcfIPXfy){rSBGOXBVRq = true;}
      else if(tkQcfIPXfy == lHhaiIjhFp){nDlwuacKom = true;}
      if(TMLYNDDCmw == GxOzwQjmsq){WhGBsFtCgh = true;}
      else if(GxOzwQjmsq == TMLYNDDCmw){jBSjDSBlVt = true;}
      if(KUJeBqQlUo == qZWrZdlgVk){WGaKqURAkr = true;}
      else if(qZWrZdlgVk == KUJeBqQlUo){pEKTGTsZES = true;}
      if(REeAzSntfe == eRRLeJKktO){uQJfJoOhkp = true;}
      else if(eRRLeJKktO == REeAzSntfe){QUCrplADCd = true;}
      if(FwJHqbwpXu == QzbpaXVWsV){iuGjlMeeAm = true;}
      else if(QzbpaXVWsV == FwJHqbwpXu){YFddnuFinR = true;}
      if(RkgWMRyDYq == WuArjUOXDB){mtAoOkrpOs = true;}
      if(ryNQXOhLYt == ViCtSofCUl){FBkZwGXarD = true;}
      if(PIVIqNKBnY == GzsdZrxgRB){qMQpzaApXd = true;}
      while(WuArjUOXDB == RkgWMRyDYq){eYKsojsSob = true;}
      while(ViCtSofCUl == ViCtSofCUl){gDFWWPzZtQ = true;}
      while(GzsdZrxgRB == GzsdZrxgRB){SxiqVkZffL = true;}
      if(IPnANjRYbJ == true){IPnANjRYbJ = false;}
      if(ulgsrhwgWk == true){ulgsrhwgWk = false;}
      if(rSBGOXBVRq == true){rSBGOXBVRq = false;}
      if(WhGBsFtCgh == true){WhGBsFtCgh = false;}
      if(WGaKqURAkr == true){WGaKqURAkr = false;}
      if(uQJfJoOhkp == true){uQJfJoOhkp = false;}
      if(iuGjlMeeAm == true){iuGjlMeeAm = false;}
      if(mtAoOkrpOs == true){mtAoOkrpOs = false;}
      if(FBkZwGXarD == true){FBkZwGXarD = false;}
      if(qMQpzaApXd == true){qMQpzaApXd = false;}
      if(plAyEBPTQX == true){plAyEBPTQX = false;}
      if(wXSqkgKfnf == true){wXSqkgKfnf = false;}
      if(nDlwuacKom == true){nDlwuacKom = false;}
      if(jBSjDSBlVt == true){jBSjDSBlVt = false;}
      if(pEKTGTsZES == true){pEKTGTsZES = false;}
      if(QUCrplADCd == true){QUCrplADCd = false;}
      if(YFddnuFinR == true){YFddnuFinR = false;}
      if(eYKsojsSob == true){eYKsojsSob = false;}
      if(gDFWWPzZtQ == true){gDFWWPzZtQ = false;}
      if(SxiqVkZffL == true){SxiqVkZffL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJLYYTIKNG
{ 
  void zictFLJDlw()
  { 
      bool WZmzZYqquk = false;
      bool tFwTqMKfVm = false;
      bool WrIJbaOcGT = false;
      bool HEJfRlKBmd = false;
      bool DNQTsJKZcd = false;
      bool IGphteRcXy = false;
      bool JOjbdpwQCE = false;
      bool CJsriIanPR = false;
      bool QozcLBNakm = false;
      bool UgdnUocopD = false;
      bool NsXYayMyzk = false;
      bool DdNFgUOGPb = false;
      bool cUePjUfEXs = false;
      bool elxMEWQaCM = false;
      bool oOaAjpTXGz = false;
      bool ZVYOZrNInG = false;
      bool SHaFFQgABJ = false;
      bool DnEDmNseet = false;
      bool AHyXSIMilL = false;
      bool JIlusgmVuS = false;
      string afKkmKhcyF;
      string lldoFZKJcV;
      string CRoRZgmqcE;
      string HSnccPhslP;
      string mKhxYMRyOx;
      string KZZrJIpsLF;
      string XpAsySyAMo;
      string qQXMhrjrrN;
      string PncetgsuTT;
      string YohfrwJnyG;
      string NQlYGsCNKQ;
      string YyAxpjNVzQ;
      string ZCgrPBhqUk;
      string iuslzyBDYB;
      string dekCuankpH;
      string inohfLjtIE;
      string KLsYhcENxq;
      string hJwxltQdxn;
      string MxAMCuFLFn;
      string OHtTpSlMUR;
      if(afKkmKhcyF == NQlYGsCNKQ){WZmzZYqquk = true;}
      else if(NQlYGsCNKQ == afKkmKhcyF){NsXYayMyzk = true;}
      if(lldoFZKJcV == YyAxpjNVzQ){tFwTqMKfVm = true;}
      else if(YyAxpjNVzQ == lldoFZKJcV){DdNFgUOGPb = true;}
      if(CRoRZgmqcE == ZCgrPBhqUk){WrIJbaOcGT = true;}
      else if(ZCgrPBhqUk == CRoRZgmqcE){cUePjUfEXs = true;}
      if(HSnccPhslP == iuslzyBDYB){HEJfRlKBmd = true;}
      else if(iuslzyBDYB == HSnccPhslP){elxMEWQaCM = true;}
      if(mKhxYMRyOx == dekCuankpH){DNQTsJKZcd = true;}
      else if(dekCuankpH == mKhxYMRyOx){oOaAjpTXGz = true;}
      if(KZZrJIpsLF == inohfLjtIE){IGphteRcXy = true;}
      else if(inohfLjtIE == KZZrJIpsLF){ZVYOZrNInG = true;}
      if(XpAsySyAMo == KLsYhcENxq){JOjbdpwQCE = true;}
      else if(KLsYhcENxq == XpAsySyAMo){SHaFFQgABJ = true;}
      if(qQXMhrjrrN == hJwxltQdxn){CJsriIanPR = true;}
      if(PncetgsuTT == MxAMCuFLFn){QozcLBNakm = true;}
      if(YohfrwJnyG == OHtTpSlMUR){UgdnUocopD = true;}
      while(hJwxltQdxn == qQXMhrjrrN){DnEDmNseet = true;}
      while(MxAMCuFLFn == MxAMCuFLFn){AHyXSIMilL = true;}
      while(OHtTpSlMUR == OHtTpSlMUR){JIlusgmVuS = true;}
      if(WZmzZYqquk == true){WZmzZYqquk = false;}
      if(tFwTqMKfVm == true){tFwTqMKfVm = false;}
      if(WrIJbaOcGT == true){WrIJbaOcGT = false;}
      if(HEJfRlKBmd == true){HEJfRlKBmd = false;}
      if(DNQTsJKZcd == true){DNQTsJKZcd = false;}
      if(IGphteRcXy == true){IGphteRcXy = false;}
      if(JOjbdpwQCE == true){JOjbdpwQCE = false;}
      if(CJsriIanPR == true){CJsriIanPR = false;}
      if(QozcLBNakm == true){QozcLBNakm = false;}
      if(UgdnUocopD == true){UgdnUocopD = false;}
      if(NsXYayMyzk == true){NsXYayMyzk = false;}
      if(DdNFgUOGPb == true){DdNFgUOGPb = false;}
      if(cUePjUfEXs == true){cUePjUfEXs = false;}
      if(elxMEWQaCM == true){elxMEWQaCM = false;}
      if(oOaAjpTXGz == true){oOaAjpTXGz = false;}
      if(ZVYOZrNInG == true){ZVYOZrNInG = false;}
      if(SHaFFQgABJ == true){SHaFFQgABJ = false;}
      if(DnEDmNseet == true){DnEDmNseet = false;}
      if(AHyXSIMilL == true){AHyXSIMilL = false;}
      if(JIlusgmVuS == true){JIlusgmVuS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPIDXPAUEA
{ 
  void bUKYoKFheK()
  { 
      bool ECBgPFlRid = false;
      bool RaWrSJPFEQ = false;
      bool KRQWJHuZSe = false;
      bool lEQEfpNRni = false;
      bool VBbzGezPNn = false;
      bool PKArzmldXH = false;
      bool JMyErMJRMb = false;
      bool uyQUuJpQQd = false;
      bool IfLeObEYEr = false;
      bool DitfYICXHs = false;
      bool UgClrRsewp = false;
      bool xUNszdBToQ = false;
      bool IkNTXLEjwl = false;
      bool GRJWJacYlw = false;
      bool hYcOuhVAgu = false;
      bool HhhqkjTiNf = false;
      bool NJiJieLqiY = false;
      bool AbgrhjHyXo = false;
      bool pDDAeXjSkZ = false;
      bool GtKGiXoSeQ = false;
      string cCAhfYjghl;
      string hVqdhJRSnU;
      string cePgIruLmp;
      string aWbZNBSPFI;
      string XkLKRbaCcr;
      string kWnmRxlSZm;
      string dXsqKKtQQg;
      string pBMexrTFPf;
      string QrhtFEinIP;
      string OApRezqTAG;
      string gJlwCjJJpZ;
      string cgCsVkpylG;
      string aGIBSpLtzx;
      string AAEIyHGlrV;
      string uZxhmgxwwt;
      string JrhteaBjdL;
      string XOJrYcbtuO;
      string dDGPKBJZNk;
      string sOyEnHSKcX;
      string FVIgxfPEIJ;
      if(cCAhfYjghl == gJlwCjJJpZ){ECBgPFlRid = true;}
      else if(gJlwCjJJpZ == cCAhfYjghl){UgClrRsewp = true;}
      if(hVqdhJRSnU == cgCsVkpylG){RaWrSJPFEQ = true;}
      else if(cgCsVkpylG == hVqdhJRSnU){xUNszdBToQ = true;}
      if(cePgIruLmp == aGIBSpLtzx){KRQWJHuZSe = true;}
      else if(aGIBSpLtzx == cePgIruLmp){IkNTXLEjwl = true;}
      if(aWbZNBSPFI == AAEIyHGlrV){lEQEfpNRni = true;}
      else if(AAEIyHGlrV == aWbZNBSPFI){GRJWJacYlw = true;}
      if(XkLKRbaCcr == uZxhmgxwwt){VBbzGezPNn = true;}
      else if(uZxhmgxwwt == XkLKRbaCcr){hYcOuhVAgu = true;}
      if(kWnmRxlSZm == JrhteaBjdL){PKArzmldXH = true;}
      else if(JrhteaBjdL == kWnmRxlSZm){HhhqkjTiNf = true;}
      if(dXsqKKtQQg == XOJrYcbtuO){JMyErMJRMb = true;}
      else if(XOJrYcbtuO == dXsqKKtQQg){NJiJieLqiY = true;}
      if(pBMexrTFPf == dDGPKBJZNk){uyQUuJpQQd = true;}
      if(QrhtFEinIP == sOyEnHSKcX){IfLeObEYEr = true;}
      if(OApRezqTAG == FVIgxfPEIJ){DitfYICXHs = true;}
      while(dDGPKBJZNk == pBMexrTFPf){AbgrhjHyXo = true;}
      while(sOyEnHSKcX == sOyEnHSKcX){pDDAeXjSkZ = true;}
      while(FVIgxfPEIJ == FVIgxfPEIJ){GtKGiXoSeQ = true;}
      if(ECBgPFlRid == true){ECBgPFlRid = false;}
      if(RaWrSJPFEQ == true){RaWrSJPFEQ = false;}
      if(KRQWJHuZSe == true){KRQWJHuZSe = false;}
      if(lEQEfpNRni == true){lEQEfpNRni = false;}
      if(VBbzGezPNn == true){VBbzGezPNn = false;}
      if(PKArzmldXH == true){PKArzmldXH = false;}
      if(JMyErMJRMb == true){JMyErMJRMb = false;}
      if(uyQUuJpQQd == true){uyQUuJpQQd = false;}
      if(IfLeObEYEr == true){IfLeObEYEr = false;}
      if(DitfYICXHs == true){DitfYICXHs = false;}
      if(UgClrRsewp == true){UgClrRsewp = false;}
      if(xUNszdBToQ == true){xUNszdBToQ = false;}
      if(IkNTXLEjwl == true){IkNTXLEjwl = false;}
      if(GRJWJacYlw == true){GRJWJacYlw = false;}
      if(hYcOuhVAgu == true){hYcOuhVAgu = false;}
      if(HhhqkjTiNf == true){HhhqkjTiNf = false;}
      if(NJiJieLqiY == true){NJiJieLqiY = false;}
      if(AbgrhjHyXo == true){AbgrhjHyXo = false;}
      if(pDDAeXjSkZ == true){pDDAeXjSkZ = false;}
      if(GtKGiXoSeQ == true){GtKGiXoSeQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVKSFTXZHZ
{ 
  void OuLLlOYbRP()
  { 
      bool jdaJUumtVt = false;
      bool biKmHRORfy = false;
      bool qiFrbThzDk = false;
      bool CCQsBUBYCp = false;
      bool fphfcnxTcz = false;
      bool GpNJJBXihA = false;
      bool NnqjqYRQll = false;
      bool QpOpRBBZOn = false;
      bool WOVDdLnGjA = false;
      bool xSqBcrzxnE = false;
      bool VfhqiPbXrH = false;
      bool zxTsczRmFe = false;
      bool kKfkoxzNMZ = false;
      bool CDkKRpfeUN = false;
      bool jPObAzyxXc = false;
      bool ZMqJSKzwBk = false;
      bool QOLRFwMIbm = false;
      bool SmRqtUwEkp = false;
      bool yCoiApLbqG = false;
      bool picjxVEwVD = false;
      string uYODCabcyI;
      string WmVysywmRR;
      string WbVNNhwswJ;
      string ZMXkWtVrIO;
      string nfikWysFgp;
      string ASJTBSDBpU;
      string ehfohKOjbz;
      string bDeCdqsjqO;
      string opMFIHCDjD;
      string pTBnjFztDL;
      string jIdgOxnGpJ;
      string ZTKbenUafa;
      string HKAXIICpSX;
      string ryfedfMfqL;
      string TwNZcWJYIw;
      string kXOcEYIFYF;
      string txnSRbmfxz;
      string aojTGKxZuk;
      string ychWlTjDZF;
      string WHGkQVItIB;
      if(uYODCabcyI == jIdgOxnGpJ){jdaJUumtVt = true;}
      else if(jIdgOxnGpJ == uYODCabcyI){VfhqiPbXrH = true;}
      if(WmVysywmRR == ZTKbenUafa){biKmHRORfy = true;}
      else if(ZTKbenUafa == WmVysywmRR){zxTsczRmFe = true;}
      if(WbVNNhwswJ == HKAXIICpSX){qiFrbThzDk = true;}
      else if(HKAXIICpSX == WbVNNhwswJ){kKfkoxzNMZ = true;}
      if(ZMXkWtVrIO == ryfedfMfqL){CCQsBUBYCp = true;}
      else if(ryfedfMfqL == ZMXkWtVrIO){CDkKRpfeUN = true;}
      if(nfikWysFgp == TwNZcWJYIw){fphfcnxTcz = true;}
      else if(TwNZcWJYIw == nfikWysFgp){jPObAzyxXc = true;}
      if(ASJTBSDBpU == kXOcEYIFYF){GpNJJBXihA = true;}
      else if(kXOcEYIFYF == ASJTBSDBpU){ZMqJSKzwBk = true;}
      if(ehfohKOjbz == txnSRbmfxz){NnqjqYRQll = true;}
      else if(txnSRbmfxz == ehfohKOjbz){QOLRFwMIbm = true;}
      if(bDeCdqsjqO == aojTGKxZuk){QpOpRBBZOn = true;}
      if(opMFIHCDjD == ychWlTjDZF){WOVDdLnGjA = true;}
      if(pTBnjFztDL == WHGkQVItIB){xSqBcrzxnE = true;}
      while(aojTGKxZuk == bDeCdqsjqO){SmRqtUwEkp = true;}
      while(ychWlTjDZF == ychWlTjDZF){yCoiApLbqG = true;}
      while(WHGkQVItIB == WHGkQVItIB){picjxVEwVD = true;}
      if(jdaJUumtVt == true){jdaJUumtVt = false;}
      if(biKmHRORfy == true){biKmHRORfy = false;}
      if(qiFrbThzDk == true){qiFrbThzDk = false;}
      if(CCQsBUBYCp == true){CCQsBUBYCp = false;}
      if(fphfcnxTcz == true){fphfcnxTcz = false;}
      if(GpNJJBXihA == true){GpNJJBXihA = false;}
      if(NnqjqYRQll == true){NnqjqYRQll = false;}
      if(QpOpRBBZOn == true){QpOpRBBZOn = false;}
      if(WOVDdLnGjA == true){WOVDdLnGjA = false;}
      if(xSqBcrzxnE == true){xSqBcrzxnE = false;}
      if(VfhqiPbXrH == true){VfhqiPbXrH = false;}
      if(zxTsczRmFe == true){zxTsczRmFe = false;}
      if(kKfkoxzNMZ == true){kKfkoxzNMZ = false;}
      if(CDkKRpfeUN == true){CDkKRpfeUN = false;}
      if(jPObAzyxXc == true){jPObAzyxXc = false;}
      if(ZMqJSKzwBk == true){ZMqJSKzwBk = false;}
      if(QOLRFwMIbm == true){QOLRFwMIbm = false;}
      if(SmRqtUwEkp == true){SmRqtUwEkp = false;}
      if(yCoiApLbqG == true){yCoiApLbqG = false;}
      if(picjxVEwVD == true){picjxVEwVD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXXRCXFEVR
{ 
  void zwnHdUtPBB()
  { 
      bool CMnwclOgqr = false;
      bool peurafQtiM = false;
      bool FQuZqrhiDd = false;
      bool IMTuKYlKGP = false;
      bool IkyqZIlhFK = false;
      bool ycoiYlROFj = false;
      bool DfdNjdLAhB = false;
      bool tGnTDTRDzh = false;
      bool GAcrefWjVY = false;
      bool GWEVLbHkHw = false;
      bool xlAEQrnVeE = false;
      bool TNPWdDDkhE = false;
      bool HadItWCSHb = false;
      bool MgwCkUAYam = false;
      bool qAERFsHgqI = false;
      bool YVDDoVIqJt = false;
      bool pUODrmRMlJ = false;
      bool DeKtMGWLCB = false;
      bool PUayCpcsNO = false;
      bool MIOgxVkAYS = false;
      string bbaONuyewB;
      string LpELmrYwpP;
      string SrwXUcKzlq;
      string XIEqIYhGZT;
      string ieayJHDEpB;
      string ecnNZjfCtk;
      string kysFdCkNDO;
      string KRWWfnQxON;
      string YFIjLuUpRX;
      string rfLnijlVUG;
      string VpBbqMGRgk;
      string TimgMeoIsi;
      string htueVdFhmw;
      string BubIqhEgsy;
      string nCJfEIreaD;
      string tdblXatWFM;
      string HXdkjYGepe;
      string aIOttfkPaN;
      string laGjBXSpjQ;
      string mhafqPXYwe;
      if(bbaONuyewB == VpBbqMGRgk){CMnwclOgqr = true;}
      else if(VpBbqMGRgk == bbaONuyewB){xlAEQrnVeE = true;}
      if(LpELmrYwpP == TimgMeoIsi){peurafQtiM = true;}
      else if(TimgMeoIsi == LpELmrYwpP){TNPWdDDkhE = true;}
      if(SrwXUcKzlq == htueVdFhmw){FQuZqrhiDd = true;}
      else if(htueVdFhmw == SrwXUcKzlq){HadItWCSHb = true;}
      if(XIEqIYhGZT == BubIqhEgsy){IMTuKYlKGP = true;}
      else if(BubIqhEgsy == XIEqIYhGZT){MgwCkUAYam = true;}
      if(ieayJHDEpB == nCJfEIreaD){IkyqZIlhFK = true;}
      else if(nCJfEIreaD == ieayJHDEpB){qAERFsHgqI = true;}
      if(ecnNZjfCtk == tdblXatWFM){ycoiYlROFj = true;}
      else if(tdblXatWFM == ecnNZjfCtk){YVDDoVIqJt = true;}
      if(kysFdCkNDO == HXdkjYGepe){DfdNjdLAhB = true;}
      else if(HXdkjYGepe == kysFdCkNDO){pUODrmRMlJ = true;}
      if(KRWWfnQxON == aIOttfkPaN){tGnTDTRDzh = true;}
      if(YFIjLuUpRX == laGjBXSpjQ){GAcrefWjVY = true;}
      if(rfLnijlVUG == mhafqPXYwe){GWEVLbHkHw = true;}
      while(aIOttfkPaN == KRWWfnQxON){DeKtMGWLCB = true;}
      while(laGjBXSpjQ == laGjBXSpjQ){PUayCpcsNO = true;}
      while(mhafqPXYwe == mhafqPXYwe){MIOgxVkAYS = true;}
      if(CMnwclOgqr == true){CMnwclOgqr = false;}
      if(peurafQtiM == true){peurafQtiM = false;}
      if(FQuZqrhiDd == true){FQuZqrhiDd = false;}
      if(IMTuKYlKGP == true){IMTuKYlKGP = false;}
      if(IkyqZIlhFK == true){IkyqZIlhFK = false;}
      if(ycoiYlROFj == true){ycoiYlROFj = false;}
      if(DfdNjdLAhB == true){DfdNjdLAhB = false;}
      if(tGnTDTRDzh == true){tGnTDTRDzh = false;}
      if(GAcrefWjVY == true){GAcrefWjVY = false;}
      if(GWEVLbHkHw == true){GWEVLbHkHw = false;}
      if(xlAEQrnVeE == true){xlAEQrnVeE = false;}
      if(TNPWdDDkhE == true){TNPWdDDkhE = false;}
      if(HadItWCSHb == true){HadItWCSHb = false;}
      if(MgwCkUAYam == true){MgwCkUAYam = false;}
      if(qAERFsHgqI == true){qAERFsHgqI = false;}
      if(YVDDoVIqJt == true){YVDDoVIqJt = false;}
      if(pUODrmRMlJ == true){pUODrmRMlJ = false;}
      if(DeKtMGWLCB == true){DeKtMGWLCB = false;}
      if(PUayCpcsNO == true){PUayCpcsNO = false;}
      if(MIOgxVkAYS == true){MIOgxVkAYS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRAJGWLQEE
{ 
  void aSTVgBBCst()
  { 
      bool kIyiNLrDtt = false;
      bool kiLCsJVLpS = false;
      bool fpTbDbBLHP = false;
      bool UBBMZqbAgP = false;
      bool TRXaLMVnRP = false;
      bool riIJbunVek = false;
      bool JfudYihzcC = false;
      bool gUeZyOSsQp = false;
      bool FMtrXlsqke = false;
      bool CGUuFnVsBc = false;
      bool eWLOiWEhLN = false;
      bool buFofwlDGm = false;
      bool oqNxzaAiUK = false;
      bool rZqnLiBeJB = false;
      bool hLeWCGAfPI = false;
      bool BRmOmmIOPH = false;
      bool WUNBUCERdw = false;
      bool uHtFFdMpts = false;
      bool ZUSLIamcAX = false;
      bool ZmPBdMycCA = false;
      string kbQIVbNXpH;
      string RVhywRAQOJ;
      string ZuSjQFcoDG;
      string UVriFAzWIx;
      string bJMHZfxDPI;
      string MfreVoJfqQ;
      string zXUjlwdysw;
      string RcIRhPhLKj;
      string HYYtsocMNP;
      string qTeqyDobUd;
      string CyKTqiWawF;
      string GyVHIZyZqx;
      string SQkcExyRTe;
      string aGpfhJOFDJ;
      string SCPHIsyXhX;
      string EOkXKkMgOs;
      string jFHReAHoYz;
      string KsVgdQAdUL;
      string zaiuaMURUw;
      string whqKYNuycH;
      if(kbQIVbNXpH == CyKTqiWawF){kIyiNLrDtt = true;}
      else if(CyKTqiWawF == kbQIVbNXpH){eWLOiWEhLN = true;}
      if(RVhywRAQOJ == GyVHIZyZqx){kiLCsJVLpS = true;}
      else if(GyVHIZyZqx == RVhywRAQOJ){buFofwlDGm = true;}
      if(ZuSjQFcoDG == SQkcExyRTe){fpTbDbBLHP = true;}
      else if(SQkcExyRTe == ZuSjQFcoDG){oqNxzaAiUK = true;}
      if(UVriFAzWIx == aGpfhJOFDJ){UBBMZqbAgP = true;}
      else if(aGpfhJOFDJ == UVriFAzWIx){rZqnLiBeJB = true;}
      if(bJMHZfxDPI == SCPHIsyXhX){TRXaLMVnRP = true;}
      else if(SCPHIsyXhX == bJMHZfxDPI){hLeWCGAfPI = true;}
      if(MfreVoJfqQ == EOkXKkMgOs){riIJbunVek = true;}
      else if(EOkXKkMgOs == MfreVoJfqQ){BRmOmmIOPH = true;}
      if(zXUjlwdysw == jFHReAHoYz){JfudYihzcC = true;}
      else if(jFHReAHoYz == zXUjlwdysw){WUNBUCERdw = true;}
      if(RcIRhPhLKj == KsVgdQAdUL){gUeZyOSsQp = true;}
      if(HYYtsocMNP == zaiuaMURUw){FMtrXlsqke = true;}
      if(qTeqyDobUd == whqKYNuycH){CGUuFnVsBc = true;}
      while(KsVgdQAdUL == RcIRhPhLKj){uHtFFdMpts = true;}
      while(zaiuaMURUw == zaiuaMURUw){ZUSLIamcAX = true;}
      while(whqKYNuycH == whqKYNuycH){ZmPBdMycCA = true;}
      if(kIyiNLrDtt == true){kIyiNLrDtt = false;}
      if(kiLCsJVLpS == true){kiLCsJVLpS = false;}
      if(fpTbDbBLHP == true){fpTbDbBLHP = false;}
      if(UBBMZqbAgP == true){UBBMZqbAgP = false;}
      if(TRXaLMVnRP == true){TRXaLMVnRP = false;}
      if(riIJbunVek == true){riIJbunVek = false;}
      if(JfudYihzcC == true){JfudYihzcC = false;}
      if(gUeZyOSsQp == true){gUeZyOSsQp = false;}
      if(FMtrXlsqke == true){FMtrXlsqke = false;}
      if(CGUuFnVsBc == true){CGUuFnVsBc = false;}
      if(eWLOiWEhLN == true){eWLOiWEhLN = false;}
      if(buFofwlDGm == true){buFofwlDGm = false;}
      if(oqNxzaAiUK == true){oqNxzaAiUK = false;}
      if(rZqnLiBeJB == true){rZqnLiBeJB = false;}
      if(hLeWCGAfPI == true){hLeWCGAfPI = false;}
      if(BRmOmmIOPH == true){BRmOmmIOPH = false;}
      if(WUNBUCERdw == true){WUNBUCERdw = false;}
      if(uHtFFdMpts == true){uHtFFdMpts = false;}
      if(ZUSLIamcAX == true){ZUSLIamcAX = false;}
      if(ZmPBdMycCA == true){ZmPBdMycCA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PIKMUHYOZO
{ 
  void yDhxoBkwqu()
  { 
      bool SRMosASqFK = false;
      bool CaBstADPWK = false;
      bool HjdEhGwDBc = false;
      bool NVOPJGpHNT = false;
      bool krPLzfhXgW = false;
      bool wbkpuinHHm = false;
      bool DOobxgMkjn = false;
      bool JwBCYPUSFB = false;
      bool XXVdfkkXUZ = false;
      bool RhzaQWCmNR = false;
      bool TwnsMAZhRf = false;
      bool NVCGOerKuM = false;
      bool wnQJVbwalC = false;
      bool NgEmgaicQf = false;
      bool KCGoMwfsMk = false;
      bool dqrBVffeWk = false;
      bool EzwORgQPYm = false;
      bool uOsPBsgbwY = false;
      bool uCOAXWoCQA = false;
      bool uDFfaKFqWe = false;
      string rEGewJUuwu;
      string KtewmJMKqT;
      string jhfzAsXLNx;
      string qPtWwFMkTS;
      string WIPPdJbiDH;
      string zRmVrKYHeD;
      string kIhyDuAIAg;
      string waqYwbRPUp;
      string QoIGyZbXel;
      string gFGQgOZRMi;
      string ITiVKXZNYP;
      string rIlnlwAbAc;
      string ScdNAqUaqh;
      string CADlhxFlua;
      string zNyOtXSSdj;
      string NyQiPfpUUS;
      string CzWqNqFAFo;
      string qNfZdEdOTb;
      string YCwHTDiUWB;
      string HjQbXAqHAD;
      if(rEGewJUuwu == ITiVKXZNYP){SRMosASqFK = true;}
      else if(ITiVKXZNYP == rEGewJUuwu){TwnsMAZhRf = true;}
      if(KtewmJMKqT == rIlnlwAbAc){CaBstADPWK = true;}
      else if(rIlnlwAbAc == KtewmJMKqT){NVCGOerKuM = true;}
      if(jhfzAsXLNx == ScdNAqUaqh){HjdEhGwDBc = true;}
      else if(ScdNAqUaqh == jhfzAsXLNx){wnQJVbwalC = true;}
      if(qPtWwFMkTS == CADlhxFlua){NVOPJGpHNT = true;}
      else if(CADlhxFlua == qPtWwFMkTS){NgEmgaicQf = true;}
      if(WIPPdJbiDH == zNyOtXSSdj){krPLzfhXgW = true;}
      else if(zNyOtXSSdj == WIPPdJbiDH){KCGoMwfsMk = true;}
      if(zRmVrKYHeD == NyQiPfpUUS){wbkpuinHHm = true;}
      else if(NyQiPfpUUS == zRmVrKYHeD){dqrBVffeWk = true;}
      if(kIhyDuAIAg == CzWqNqFAFo){DOobxgMkjn = true;}
      else if(CzWqNqFAFo == kIhyDuAIAg){EzwORgQPYm = true;}
      if(waqYwbRPUp == qNfZdEdOTb){JwBCYPUSFB = true;}
      if(QoIGyZbXel == YCwHTDiUWB){XXVdfkkXUZ = true;}
      if(gFGQgOZRMi == HjQbXAqHAD){RhzaQWCmNR = true;}
      while(qNfZdEdOTb == waqYwbRPUp){uOsPBsgbwY = true;}
      while(YCwHTDiUWB == YCwHTDiUWB){uCOAXWoCQA = true;}
      while(HjQbXAqHAD == HjQbXAqHAD){uDFfaKFqWe = true;}
      if(SRMosASqFK == true){SRMosASqFK = false;}
      if(CaBstADPWK == true){CaBstADPWK = false;}
      if(HjdEhGwDBc == true){HjdEhGwDBc = false;}
      if(NVOPJGpHNT == true){NVOPJGpHNT = false;}
      if(krPLzfhXgW == true){krPLzfhXgW = false;}
      if(wbkpuinHHm == true){wbkpuinHHm = false;}
      if(DOobxgMkjn == true){DOobxgMkjn = false;}
      if(JwBCYPUSFB == true){JwBCYPUSFB = false;}
      if(XXVdfkkXUZ == true){XXVdfkkXUZ = false;}
      if(RhzaQWCmNR == true){RhzaQWCmNR = false;}
      if(TwnsMAZhRf == true){TwnsMAZhRf = false;}
      if(NVCGOerKuM == true){NVCGOerKuM = false;}
      if(wnQJVbwalC == true){wnQJVbwalC = false;}
      if(NgEmgaicQf == true){NgEmgaicQf = false;}
      if(KCGoMwfsMk == true){KCGoMwfsMk = false;}
      if(dqrBVffeWk == true){dqrBVffeWk = false;}
      if(EzwORgQPYm == true){EzwORgQPYm = false;}
      if(uOsPBsgbwY == true){uOsPBsgbwY = false;}
      if(uCOAXWoCQA == true){uCOAXWoCQA = false;}
      if(uDFfaKFqWe == true){uDFfaKFqWe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFXFYPCBOK
{ 
  void oknstuiPkT()
  { 
      bool aJwnnCjgbb = false;
      bool IUVOBMOkiu = false;
      bool QWknAxXrcG = false;
      bool CMfPHzMjyy = false;
      bool bdNoxqDxAz = false;
      bool ZVPkhEYImq = false;
      bool dqEUZunGHB = false;
      bool zeljTmIupJ = false;
      bool tZrdggwthC = false;
      bool aEwHTjZrPB = false;
      bool CwpyztifRt = false;
      bool ucRdxEzZnr = false;
      bool ztYEauiePi = false;
      bool NPeoGxjsel = false;
      bool xQbmHxlRJP = false;
      bool kzEWCHWkXD = false;
      bool LEPigexbWz = false;
      bool TFuBuhSlxd = false;
      bool IQUAxNLImy = false;
      bool ZyVaasBsFb = false;
      string cwWQhEIJHt;
      string CxywgpdXCX;
      string HrNnGzljMh;
      string hOwKVwBUpK;
      string EgRGMQWBFU;
      string etNpXjhhJi;
      string RYxYLnBnak;
      string oJgqSZZHbp;
      string bkeqCnAGlk;
      string NSKHrfjstY;
      string PiZUfUMWWx;
      string JZGTGgtFWW;
      string muBoWVzZym;
      string pgNDZsKJLg;
      string bdinanMpBL;
      string ldVXkUgkxK;
      string VmXjHbMCsM;
      string WjtouILMOi;
      string IJXmALLpRF;
      string LZLBLnGzgy;
      if(cwWQhEIJHt == PiZUfUMWWx){aJwnnCjgbb = true;}
      else if(PiZUfUMWWx == cwWQhEIJHt){CwpyztifRt = true;}
      if(CxywgpdXCX == JZGTGgtFWW){IUVOBMOkiu = true;}
      else if(JZGTGgtFWW == CxywgpdXCX){ucRdxEzZnr = true;}
      if(HrNnGzljMh == muBoWVzZym){QWknAxXrcG = true;}
      else if(muBoWVzZym == HrNnGzljMh){ztYEauiePi = true;}
      if(hOwKVwBUpK == pgNDZsKJLg){CMfPHzMjyy = true;}
      else if(pgNDZsKJLg == hOwKVwBUpK){NPeoGxjsel = true;}
      if(EgRGMQWBFU == bdinanMpBL){bdNoxqDxAz = true;}
      else if(bdinanMpBL == EgRGMQWBFU){xQbmHxlRJP = true;}
      if(etNpXjhhJi == ldVXkUgkxK){ZVPkhEYImq = true;}
      else if(ldVXkUgkxK == etNpXjhhJi){kzEWCHWkXD = true;}
      if(RYxYLnBnak == VmXjHbMCsM){dqEUZunGHB = true;}
      else if(VmXjHbMCsM == RYxYLnBnak){LEPigexbWz = true;}
      if(oJgqSZZHbp == WjtouILMOi){zeljTmIupJ = true;}
      if(bkeqCnAGlk == IJXmALLpRF){tZrdggwthC = true;}
      if(NSKHrfjstY == LZLBLnGzgy){aEwHTjZrPB = true;}
      while(WjtouILMOi == oJgqSZZHbp){TFuBuhSlxd = true;}
      while(IJXmALLpRF == IJXmALLpRF){IQUAxNLImy = true;}
      while(LZLBLnGzgy == LZLBLnGzgy){ZyVaasBsFb = true;}
      if(aJwnnCjgbb == true){aJwnnCjgbb = false;}
      if(IUVOBMOkiu == true){IUVOBMOkiu = false;}
      if(QWknAxXrcG == true){QWknAxXrcG = false;}
      if(CMfPHzMjyy == true){CMfPHzMjyy = false;}
      if(bdNoxqDxAz == true){bdNoxqDxAz = false;}
      if(ZVPkhEYImq == true){ZVPkhEYImq = false;}
      if(dqEUZunGHB == true){dqEUZunGHB = false;}
      if(zeljTmIupJ == true){zeljTmIupJ = false;}
      if(tZrdggwthC == true){tZrdggwthC = false;}
      if(aEwHTjZrPB == true){aEwHTjZrPB = false;}
      if(CwpyztifRt == true){CwpyztifRt = false;}
      if(ucRdxEzZnr == true){ucRdxEzZnr = false;}
      if(ztYEauiePi == true){ztYEauiePi = false;}
      if(NPeoGxjsel == true){NPeoGxjsel = false;}
      if(xQbmHxlRJP == true){xQbmHxlRJP = false;}
      if(kzEWCHWkXD == true){kzEWCHWkXD = false;}
      if(LEPigexbWz == true){LEPigexbWz = false;}
      if(TFuBuhSlxd == true){TFuBuhSlxd = false;}
      if(IQUAxNLImy == true){IQUAxNLImy = false;}
      if(ZyVaasBsFb == true){ZyVaasBsFb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGFLHHHLLC
{ 
  void JPIHujhxQX()
  { 
      bool sZVmhQLuan = false;
      bool JRTQmUYecy = false;
      bool hOfAwrbNSn = false;
      bool iEaiLObTkk = false;
      bool tNeucpnWZD = false;
      bool FOQxjesUqo = false;
      bool nxblEFpkFX = false;
      bool sFsqDTjjXF = false;
      bool DEnOiUndzg = false;
      bool UGbuwwksqX = false;
      bool zDRBKzUZsP = false;
      bool uJxkljJNDj = false;
      bool QMlXClcxtH = false;
      bool hqsAFzllDi = false;
      bool zOjilLIpJM = false;
      bool mXoGGlRtzX = false;
      bool WWekhEQxem = false;
      bool xWJTjCcClq = false;
      bool clnhUJBlsS = false;
      bool grmeMcjyBh = false;
      string oBuYsbZnmj;
      string ZIGDZryuNi;
      string BkLqPkpufn;
      string PJxmzWJACy;
      string nITpDpdhsm;
      string XZPJpDoEII;
      string ldHyTPKSEC;
      string iysOtsQVnZ;
      string HHCrQptnwu;
      string hFqsMJBUWm;
      string eKdqEYfBPw;
      string lTQhBdbOhc;
      string VWVJTcGzCj;
      string ruzAuwcLnq;
      string KsXzIOoIrh;
      string hllsQInUWa;
      string SfyeEqUPmE;
      string AQaqScyWAF;
      string nxHTCFIFjl;
      string IInMYdtsuR;
      if(oBuYsbZnmj == eKdqEYfBPw){sZVmhQLuan = true;}
      else if(eKdqEYfBPw == oBuYsbZnmj){zDRBKzUZsP = true;}
      if(ZIGDZryuNi == lTQhBdbOhc){JRTQmUYecy = true;}
      else if(lTQhBdbOhc == ZIGDZryuNi){uJxkljJNDj = true;}
      if(BkLqPkpufn == VWVJTcGzCj){hOfAwrbNSn = true;}
      else if(VWVJTcGzCj == BkLqPkpufn){QMlXClcxtH = true;}
      if(PJxmzWJACy == ruzAuwcLnq){iEaiLObTkk = true;}
      else if(ruzAuwcLnq == PJxmzWJACy){hqsAFzllDi = true;}
      if(nITpDpdhsm == KsXzIOoIrh){tNeucpnWZD = true;}
      else if(KsXzIOoIrh == nITpDpdhsm){zOjilLIpJM = true;}
      if(XZPJpDoEII == hllsQInUWa){FOQxjesUqo = true;}
      else if(hllsQInUWa == XZPJpDoEII){mXoGGlRtzX = true;}
      if(ldHyTPKSEC == SfyeEqUPmE){nxblEFpkFX = true;}
      else if(SfyeEqUPmE == ldHyTPKSEC){WWekhEQxem = true;}
      if(iysOtsQVnZ == AQaqScyWAF){sFsqDTjjXF = true;}
      if(HHCrQptnwu == nxHTCFIFjl){DEnOiUndzg = true;}
      if(hFqsMJBUWm == IInMYdtsuR){UGbuwwksqX = true;}
      while(AQaqScyWAF == iysOtsQVnZ){xWJTjCcClq = true;}
      while(nxHTCFIFjl == nxHTCFIFjl){clnhUJBlsS = true;}
      while(IInMYdtsuR == IInMYdtsuR){grmeMcjyBh = true;}
      if(sZVmhQLuan == true){sZVmhQLuan = false;}
      if(JRTQmUYecy == true){JRTQmUYecy = false;}
      if(hOfAwrbNSn == true){hOfAwrbNSn = false;}
      if(iEaiLObTkk == true){iEaiLObTkk = false;}
      if(tNeucpnWZD == true){tNeucpnWZD = false;}
      if(FOQxjesUqo == true){FOQxjesUqo = false;}
      if(nxblEFpkFX == true){nxblEFpkFX = false;}
      if(sFsqDTjjXF == true){sFsqDTjjXF = false;}
      if(DEnOiUndzg == true){DEnOiUndzg = false;}
      if(UGbuwwksqX == true){UGbuwwksqX = false;}
      if(zDRBKzUZsP == true){zDRBKzUZsP = false;}
      if(uJxkljJNDj == true){uJxkljJNDj = false;}
      if(QMlXClcxtH == true){QMlXClcxtH = false;}
      if(hqsAFzllDi == true){hqsAFzllDi = false;}
      if(zOjilLIpJM == true){zOjilLIpJM = false;}
      if(mXoGGlRtzX == true){mXoGGlRtzX = false;}
      if(WWekhEQxem == true){WWekhEQxem = false;}
      if(xWJTjCcClq == true){xWJTjCcClq = false;}
      if(clnhUJBlsS == true){clnhUJBlsS = false;}
      if(grmeMcjyBh == true){grmeMcjyBh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKCXZNEKTT
{ 
  void EixHnygnAG()
  { 
      bool sjXbjgdPKA = false;
      bool ZTZIoZehzQ = false;
      bool duxYUCfkRU = false;
      bool CoGjDaFVcG = false;
      bool EwYGjEuZfq = false;
      bool aiBkhxmzHg = false;
      bool BryoyjMoFO = false;
      bool TJEsLhWpnQ = false;
      bool GFFatTnVCF = false;
      bool nFNuEMyiIA = false;
      bool qFTRWRdIYz = false;
      bool awLqZulWue = false;
      bool wqmAaOuInz = false;
      bool jmhnZBlnEb = false;
      bool oewDdqtWUJ = false;
      bool ZamcDzSTpI = false;
      bool WUTZPmOXRY = false;
      bool JyRToQtjWi = false;
      bool TXneYIAEjZ = false;
      bool hRxwETLWnq = false;
      string BehzRMArWC;
      string rGoWmuGTwx;
      string tjKcOqiirF;
      string KlOPUsZCmC;
      string PNUpDoIVTV;
      string tcKDyQUFja;
      string cRzQrFqYBt;
      string UDftggPTYZ;
      string hMOWLgbKRD;
      string YURMYyNExx;
      string xiUZApxPVR;
      string BAfKrQCcEL;
      string dfHyUAlTVi;
      string SLVabzrnVV;
      string jLozBXoHUI;
      string ukzlTRbWFA;
      string EdtmypeEir;
      string XOGibSqHww;
      string KdyMmhLiHK;
      string XViVQGQBBL;
      if(BehzRMArWC == xiUZApxPVR){sjXbjgdPKA = true;}
      else if(xiUZApxPVR == BehzRMArWC){qFTRWRdIYz = true;}
      if(rGoWmuGTwx == BAfKrQCcEL){ZTZIoZehzQ = true;}
      else if(BAfKrQCcEL == rGoWmuGTwx){awLqZulWue = true;}
      if(tjKcOqiirF == dfHyUAlTVi){duxYUCfkRU = true;}
      else if(dfHyUAlTVi == tjKcOqiirF){wqmAaOuInz = true;}
      if(KlOPUsZCmC == SLVabzrnVV){CoGjDaFVcG = true;}
      else if(SLVabzrnVV == KlOPUsZCmC){jmhnZBlnEb = true;}
      if(PNUpDoIVTV == jLozBXoHUI){EwYGjEuZfq = true;}
      else if(jLozBXoHUI == PNUpDoIVTV){oewDdqtWUJ = true;}
      if(tcKDyQUFja == ukzlTRbWFA){aiBkhxmzHg = true;}
      else if(ukzlTRbWFA == tcKDyQUFja){ZamcDzSTpI = true;}
      if(cRzQrFqYBt == EdtmypeEir){BryoyjMoFO = true;}
      else if(EdtmypeEir == cRzQrFqYBt){WUTZPmOXRY = true;}
      if(UDftggPTYZ == XOGibSqHww){TJEsLhWpnQ = true;}
      if(hMOWLgbKRD == KdyMmhLiHK){GFFatTnVCF = true;}
      if(YURMYyNExx == XViVQGQBBL){nFNuEMyiIA = true;}
      while(XOGibSqHww == UDftggPTYZ){JyRToQtjWi = true;}
      while(KdyMmhLiHK == KdyMmhLiHK){TXneYIAEjZ = true;}
      while(XViVQGQBBL == XViVQGQBBL){hRxwETLWnq = true;}
      if(sjXbjgdPKA == true){sjXbjgdPKA = false;}
      if(ZTZIoZehzQ == true){ZTZIoZehzQ = false;}
      if(duxYUCfkRU == true){duxYUCfkRU = false;}
      if(CoGjDaFVcG == true){CoGjDaFVcG = false;}
      if(EwYGjEuZfq == true){EwYGjEuZfq = false;}
      if(aiBkhxmzHg == true){aiBkhxmzHg = false;}
      if(BryoyjMoFO == true){BryoyjMoFO = false;}
      if(TJEsLhWpnQ == true){TJEsLhWpnQ = false;}
      if(GFFatTnVCF == true){GFFatTnVCF = false;}
      if(nFNuEMyiIA == true){nFNuEMyiIA = false;}
      if(qFTRWRdIYz == true){qFTRWRdIYz = false;}
      if(awLqZulWue == true){awLqZulWue = false;}
      if(wqmAaOuInz == true){wqmAaOuInz = false;}
      if(jmhnZBlnEb == true){jmhnZBlnEb = false;}
      if(oewDdqtWUJ == true){oewDdqtWUJ = false;}
      if(ZamcDzSTpI == true){ZamcDzSTpI = false;}
      if(WUTZPmOXRY == true){WUTZPmOXRY = false;}
      if(JyRToQtjWi == true){JyRToQtjWi = false;}
      if(TXneYIAEjZ == true){TXneYIAEjZ = false;}
      if(hRxwETLWnq == true){hRxwETLWnq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRBUTCVAGG
{ 
  void ePJmkffthj()
  { 
      bool ApmQnxlUeo = false;
      bool xcYVQeKrxy = false;
      bool msefMcluzV = false;
      bool rcsfSJFCrd = false;
      bool ZnWYQCmSXC = false;
      bool EzmSwGLGDK = false;
      bool KpUIwTjrCH = false;
      bool YIzSXyVFPK = false;
      bool oSXxRrpZjL = false;
      bool xzyhSiTObx = false;
      bool StPPdwATux = false;
      bool kFqsUrSXqE = false;
      bool cJIpJZKQAn = false;
      bool eHdSquDHSU = false;
      bool rWelaqHENa = false;
      bool QuWXTIlYFD = false;
      bool liTGScbYBZ = false;
      bool oLEVLFdVPR = false;
      bool RFDYXijFyi = false;
      bool IdBPiIDYSx = false;
      string rHoVckGMbY;
      string RnJfISHUiA;
      string FigrsXGONh;
      string xQjEwiPdYB;
      string VLhUbleTdE;
      string cAQCkIZxbE;
      string eqzsaBDFiY;
      string CcwgdsAMPH;
      string slkIFxAgSn;
      string JRCUWeLota;
      string hZjFCzEiXq;
      string HNhTLrGpmd;
      string BWluPjabKz;
      string gLSnZSBeGF;
      string rQIafujhId;
      string XVCPZLnopR;
      string XcYYJwustr;
      string pajgkjNKPT;
      string AsSfaLJCOO;
      string eMoohOrjQi;
      if(rHoVckGMbY == hZjFCzEiXq){ApmQnxlUeo = true;}
      else if(hZjFCzEiXq == rHoVckGMbY){StPPdwATux = true;}
      if(RnJfISHUiA == HNhTLrGpmd){xcYVQeKrxy = true;}
      else if(HNhTLrGpmd == RnJfISHUiA){kFqsUrSXqE = true;}
      if(FigrsXGONh == BWluPjabKz){msefMcluzV = true;}
      else if(BWluPjabKz == FigrsXGONh){cJIpJZKQAn = true;}
      if(xQjEwiPdYB == gLSnZSBeGF){rcsfSJFCrd = true;}
      else if(gLSnZSBeGF == xQjEwiPdYB){eHdSquDHSU = true;}
      if(VLhUbleTdE == rQIafujhId){ZnWYQCmSXC = true;}
      else if(rQIafujhId == VLhUbleTdE){rWelaqHENa = true;}
      if(cAQCkIZxbE == XVCPZLnopR){EzmSwGLGDK = true;}
      else if(XVCPZLnopR == cAQCkIZxbE){QuWXTIlYFD = true;}
      if(eqzsaBDFiY == XcYYJwustr){KpUIwTjrCH = true;}
      else if(XcYYJwustr == eqzsaBDFiY){liTGScbYBZ = true;}
      if(CcwgdsAMPH == pajgkjNKPT){YIzSXyVFPK = true;}
      if(slkIFxAgSn == AsSfaLJCOO){oSXxRrpZjL = true;}
      if(JRCUWeLota == eMoohOrjQi){xzyhSiTObx = true;}
      while(pajgkjNKPT == CcwgdsAMPH){oLEVLFdVPR = true;}
      while(AsSfaLJCOO == AsSfaLJCOO){RFDYXijFyi = true;}
      while(eMoohOrjQi == eMoohOrjQi){IdBPiIDYSx = true;}
      if(ApmQnxlUeo == true){ApmQnxlUeo = false;}
      if(xcYVQeKrxy == true){xcYVQeKrxy = false;}
      if(msefMcluzV == true){msefMcluzV = false;}
      if(rcsfSJFCrd == true){rcsfSJFCrd = false;}
      if(ZnWYQCmSXC == true){ZnWYQCmSXC = false;}
      if(EzmSwGLGDK == true){EzmSwGLGDK = false;}
      if(KpUIwTjrCH == true){KpUIwTjrCH = false;}
      if(YIzSXyVFPK == true){YIzSXyVFPK = false;}
      if(oSXxRrpZjL == true){oSXxRrpZjL = false;}
      if(xzyhSiTObx == true){xzyhSiTObx = false;}
      if(StPPdwATux == true){StPPdwATux = false;}
      if(kFqsUrSXqE == true){kFqsUrSXqE = false;}
      if(cJIpJZKQAn == true){cJIpJZKQAn = false;}
      if(eHdSquDHSU == true){eHdSquDHSU = false;}
      if(rWelaqHENa == true){rWelaqHENa = false;}
      if(QuWXTIlYFD == true){QuWXTIlYFD = false;}
      if(liTGScbYBZ == true){liTGScbYBZ = false;}
      if(oLEVLFdVPR == true){oLEVLFdVPR = false;}
      if(RFDYXijFyi == true){RFDYXijFyi = false;}
      if(IdBPiIDYSx == true){IdBPiIDYSx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAXWLWZJFK
{ 
  void CRKZRWOkJE()
  { 
      bool dhfCRoHGhO = false;
      bool QorVWyzYAJ = false;
      bool OzijsXSprW = false;
      bool iopLsNmGDg = false;
      bool KXybGpufzr = false;
      bool PLzCOeywJt = false;
      bool WROKfazgcI = false;
      bool KrUTzpAHcC = false;
      bool clqAHWpmwO = false;
      bool OqxJJsJnwf = false;
      bool qNDpgWqeDX = false;
      bool dqTGQkaOCI = false;
      bool kLjOtTuKJG = false;
      bool gMLxLPhASj = false;
      bool fKiYjXXpsY = false;
      bool SukmtecowN = false;
      bool bfVxqQeWuB = false;
      bool CZuScZbLdV = false;
      bool uERknlaXCf = false;
      bool lsEFIzolhS = false;
      string TAZzoCQCGz;
      string IjUDdauhPc;
      string kDnRLlHark;
      string UgsYDDPNZF;
      string SdCIJLesBh;
      string FCFPUQLHmC;
      string upKVdaquzZ;
      string LgHKKGBeHA;
      string GOYKfSacDm;
      string qHaWKcTfei;
      string UjsbVXtuFO;
      string PgzmufRApK;
      string ANrMhDGkAh;
      string lUAYeWUwnH;
      string YfXoXKImad;
      string KToTiGrgsR;
      string QJuXbtfZHY;
      string LULilTpCoX;
      string uSJVWSefpX;
      string emCVpOkAMc;
      if(TAZzoCQCGz == UjsbVXtuFO){dhfCRoHGhO = true;}
      else if(UjsbVXtuFO == TAZzoCQCGz){qNDpgWqeDX = true;}
      if(IjUDdauhPc == PgzmufRApK){QorVWyzYAJ = true;}
      else if(PgzmufRApK == IjUDdauhPc){dqTGQkaOCI = true;}
      if(kDnRLlHark == ANrMhDGkAh){OzijsXSprW = true;}
      else if(ANrMhDGkAh == kDnRLlHark){kLjOtTuKJG = true;}
      if(UgsYDDPNZF == lUAYeWUwnH){iopLsNmGDg = true;}
      else if(lUAYeWUwnH == UgsYDDPNZF){gMLxLPhASj = true;}
      if(SdCIJLesBh == YfXoXKImad){KXybGpufzr = true;}
      else if(YfXoXKImad == SdCIJLesBh){fKiYjXXpsY = true;}
      if(FCFPUQLHmC == KToTiGrgsR){PLzCOeywJt = true;}
      else if(KToTiGrgsR == FCFPUQLHmC){SukmtecowN = true;}
      if(upKVdaquzZ == QJuXbtfZHY){WROKfazgcI = true;}
      else if(QJuXbtfZHY == upKVdaquzZ){bfVxqQeWuB = true;}
      if(LgHKKGBeHA == LULilTpCoX){KrUTzpAHcC = true;}
      if(GOYKfSacDm == uSJVWSefpX){clqAHWpmwO = true;}
      if(qHaWKcTfei == emCVpOkAMc){OqxJJsJnwf = true;}
      while(LULilTpCoX == LgHKKGBeHA){CZuScZbLdV = true;}
      while(uSJVWSefpX == uSJVWSefpX){uERknlaXCf = true;}
      while(emCVpOkAMc == emCVpOkAMc){lsEFIzolhS = true;}
      if(dhfCRoHGhO == true){dhfCRoHGhO = false;}
      if(QorVWyzYAJ == true){QorVWyzYAJ = false;}
      if(OzijsXSprW == true){OzijsXSprW = false;}
      if(iopLsNmGDg == true){iopLsNmGDg = false;}
      if(KXybGpufzr == true){KXybGpufzr = false;}
      if(PLzCOeywJt == true){PLzCOeywJt = false;}
      if(WROKfazgcI == true){WROKfazgcI = false;}
      if(KrUTzpAHcC == true){KrUTzpAHcC = false;}
      if(clqAHWpmwO == true){clqAHWpmwO = false;}
      if(OqxJJsJnwf == true){OqxJJsJnwf = false;}
      if(qNDpgWqeDX == true){qNDpgWqeDX = false;}
      if(dqTGQkaOCI == true){dqTGQkaOCI = false;}
      if(kLjOtTuKJG == true){kLjOtTuKJG = false;}
      if(gMLxLPhASj == true){gMLxLPhASj = false;}
      if(fKiYjXXpsY == true){fKiYjXXpsY = false;}
      if(SukmtecowN == true){SukmtecowN = false;}
      if(bfVxqQeWuB == true){bfVxqQeWuB = false;}
      if(CZuScZbLdV == true){CZuScZbLdV = false;}
      if(uERknlaXCf == true){uERknlaXCf = false;}
      if(lsEFIzolhS == true){lsEFIzolhS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSEYDTWNHL
{ 
  void LpfHFdKDVr()
  { 
      bool VuVhOzPpiS = false;
      bool MSyYHLDnih = false;
      bool DFSYGBBane = false;
      bool hgOZikLmqz = false;
      bool UKHNIeJLRt = false;
      bool siGpDPbxbM = false;
      bool xnBEkeDYoV = false;
      bool zPxiMsyFPa = false;
      bool rpJskyaYVT = false;
      bool JOLdBgIDcc = false;
      bool bjVutclWdK = false;
      bool RWgAUHdISm = false;
      bool EeCVMkESge = false;
      bool jtclzHTOzH = false;
      bool LDtLBlgKJt = false;
      bool CAkoYwhAhJ = false;
      bool XTpyaWsuBM = false;
      bool mPIKaBjqTZ = false;
      bool DtIlciJmNC = false;
      bool ZTfoirNwke = false;
      string iadYzpROkj;
      string rQwBLnHoia;
      string BeRUsGfCXy;
      string kYgJFYKtlf;
      string CVQHRLVTms;
      string FidqzEIIer;
      string JPqlzTimul;
      string dNCCXeOKDg;
      string kMOdrCtpKB;
      string PBOtWmddIx;
      string bhYAPrgaST;
      string oyFyHxANtx;
      string YscsWbyHfk;
      string BkBFECmONA;
      string VTWpMRuPmY;
      string lPjKYiEedn;
      string tYuhSEwAtE;
      string JlAtbFVlgE;
      string fhUGzkApgV;
      string xHjYFwXoXH;
      if(iadYzpROkj == bhYAPrgaST){VuVhOzPpiS = true;}
      else if(bhYAPrgaST == iadYzpROkj){bjVutclWdK = true;}
      if(rQwBLnHoia == oyFyHxANtx){MSyYHLDnih = true;}
      else if(oyFyHxANtx == rQwBLnHoia){RWgAUHdISm = true;}
      if(BeRUsGfCXy == YscsWbyHfk){DFSYGBBane = true;}
      else if(YscsWbyHfk == BeRUsGfCXy){EeCVMkESge = true;}
      if(kYgJFYKtlf == BkBFECmONA){hgOZikLmqz = true;}
      else if(BkBFECmONA == kYgJFYKtlf){jtclzHTOzH = true;}
      if(CVQHRLVTms == VTWpMRuPmY){UKHNIeJLRt = true;}
      else if(VTWpMRuPmY == CVQHRLVTms){LDtLBlgKJt = true;}
      if(FidqzEIIer == lPjKYiEedn){siGpDPbxbM = true;}
      else if(lPjKYiEedn == FidqzEIIer){CAkoYwhAhJ = true;}
      if(JPqlzTimul == tYuhSEwAtE){xnBEkeDYoV = true;}
      else if(tYuhSEwAtE == JPqlzTimul){XTpyaWsuBM = true;}
      if(dNCCXeOKDg == JlAtbFVlgE){zPxiMsyFPa = true;}
      if(kMOdrCtpKB == fhUGzkApgV){rpJskyaYVT = true;}
      if(PBOtWmddIx == xHjYFwXoXH){JOLdBgIDcc = true;}
      while(JlAtbFVlgE == dNCCXeOKDg){mPIKaBjqTZ = true;}
      while(fhUGzkApgV == fhUGzkApgV){DtIlciJmNC = true;}
      while(xHjYFwXoXH == xHjYFwXoXH){ZTfoirNwke = true;}
      if(VuVhOzPpiS == true){VuVhOzPpiS = false;}
      if(MSyYHLDnih == true){MSyYHLDnih = false;}
      if(DFSYGBBane == true){DFSYGBBane = false;}
      if(hgOZikLmqz == true){hgOZikLmqz = false;}
      if(UKHNIeJLRt == true){UKHNIeJLRt = false;}
      if(siGpDPbxbM == true){siGpDPbxbM = false;}
      if(xnBEkeDYoV == true){xnBEkeDYoV = false;}
      if(zPxiMsyFPa == true){zPxiMsyFPa = false;}
      if(rpJskyaYVT == true){rpJskyaYVT = false;}
      if(JOLdBgIDcc == true){JOLdBgIDcc = false;}
      if(bjVutclWdK == true){bjVutclWdK = false;}
      if(RWgAUHdISm == true){RWgAUHdISm = false;}
      if(EeCVMkESge == true){EeCVMkESge = false;}
      if(jtclzHTOzH == true){jtclzHTOzH = false;}
      if(LDtLBlgKJt == true){LDtLBlgKJt = false;}
      if(CAkoYwhAhJ == true){CAkoYwhAhJ = false;}
      if(XTpyaWsuBM == true){XTpyaWsuBM = false;}
      if(mPIKaBjqTZ == true){mPIKaBjqTZ = false;}
      if(DtIlciJmNC == true){DtIlciJmNC = false;}
      if(ZTfoirNwke == true){ZTfoirNwke = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ETNCXRXZSE
{ 
  void OGydRrZIEV()
  { 
      bool MnFUpLixdD = false;
      bool cOAVNuMSzM = false;
      bool gxlIKKHpEo = false;
      bool DaqSNkphqM = false;
      bool XSCIxHDwcp = false;
      bool VolKQPBxKe = false;
      bool DrsoACWhHb = false;
      bool FealoNtcLD = false;
      bool HLNNSNngBx = false;
      bool jsXMIfZNIt = false;
      bool jUoBjqNzVC = false;
      bool UXkHWrdeVl = false;
      bool NpgJqMHOdJ = false;
      bool ngUQSlWLdb = false;
      bool zoKzbLHPoQ = false;
      bool BurWgtnfJW = false;
      bool jzVMOnDUoj = false;
      bool VSAslXehgf = false;
      bool FqZMIroxiX = false;
      bool yqBGrATyjn = false;
      string IxqWOOdAnZ;
      string aXEQqZohBd;
      string SucHxBgLIL;
      string fLLTJWyOuX;
      string rTjUxWTjic;
      string EJQTnMUjYN;
      string hRqbtOMkHT;
      string bamckzLIJZ;
      string hxceHVuqew;
      string CNogpabHZh;
      string KibOBdVmho;
      string BLazfjnLUX;
      string TUFLRNkFmK;
      string WDhaPzUOdd;
      string zIIpupmoBF;
      string lQmCOocQwm;
      string rQAXSxczif;
      string PZhpXLLOPa;
      string ZwDgYGPfMa;
      string VERqliHkXx;
      if(IxqWOOdAnZ == KibOBdVmho){MnFUpLixdD = true;}
      else if(KibOBdVmho == IxqWOOdAnZ){jUoBjqNzVC = true;}
      if(aXEQqZohBd == BLazfjnLUX){cOAVNuMSzM = true;}
      else if(BLazfjnLUX == aXEQqZohBd){UXkHWrdeVl = true;}
      if(SucHxBgLIL == TUFLRNkFmK){gxlIKKHpEo = true;}
      else if(TUFLRNkFmK == SucHxBgLIL){NpgJqMHOdJ = true;}
      if(fLLTJWyOuX == WDhaPzUOdd){DaqSNkphqM = true;}
      else if(WDhaPzUOdd == fLLTJWyOuX){ngUQSlWLdb = true;}
      if(rTjUxWTjic == zIIpupmoBF){XSCIxHDwcp = true;}
      else if(zIIpupmoBF == rTjUxWTjic){zoKzbLHPoQ = true;}
      if(EJQTnMUjYN == lQmCOocQwm){VolKQPBxKe = true;}
      else if(lQmCOocQwm == EJQTnMUjYN){BurWgtnfJW = true;}
      if(hRqbtOMkHT == rQAXSxczif){DrsoACWhHb = true;}
      else if(rQAXSxczif == hRqbtOMkHT){jzVMOnDUoj = true;}
      if(bamckzLIJZ == PZhpXLLOPa){FealoNtcLD = true;}
      if(hxceHVuqew == ZwDgYGPfMa){HLNNSNngBx = true;}
      if(CNogpabHZh == VERqliHkXx){jsXMIfZNIt = true;}
      while(PZhpXLLOPa == bamckzLIJZ){VSAslXehgf = true;}
      while(ZwDgYGPfMa == ZwDgYGPfMa){FqZMIroxiX = true;}
      while(VERqliHkXx == VERqliHkXx){yqBGrATyjn = true;}
      if(MnFUpLixdD == true){MnFUpLixdD = false;}
      if(cOAVNuMSzM == true){cOAVNuMSzM = false;}
      if(gxlIKKHpEo == true){gxlIKKHpEo = false;}
      if(DaqSNkphqM == true){DaqSNkphqM = false;}
      if(XSCIxHDwcp == true){XSCIxHDwcp = false;}
      if(VolKQPBxKe == true){VolKQPBxKe = false;}
      if(DrsoACWhHb == true){DrsoACWhHb = false;}
      if(FealoNtcLD == true){FealoNtcLD = false;}
      if(HLNNSNngBx == true){HLNNSNngBx = false;}
      if(jsXMIfZNIt == true){jsXMIfZNIt = false;}
      if(jUoBjqNzVC == true){jUoBjqNzVC = false;}
      if(UXkHWrdeVl == true){UXkHWrdeVl = false;}
      if(NpgJqMHOdJ == true){NpgJqMHOdJ = false;}
      if(ngUQSlWLdb == true){ngUQSlWLdb = false;}
      if(zoKzbLHPoQ == true){zoKzbLHPoQ = false;}
      if(BurWgtnfJW == true){BurWgtnfJW = false;}
      if(jzVMOnDUoj == true){jzVMOnDUoj = false;}
      if(VSAslXehgf == true){VSAslXehgf = false;}
      if(FqZMIroxiX == true){FqZMIroxiX = false;}
      if(yqBGrATyjn == true){yqBGrATyjn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSQEOMCOFA
{ 
  void mpxedCCycY()
  { 
      bool ecjLZCnUgS = false;
      bool VBGpPuICiM = false;
      bool OJrEXmfpCb = false;
      bool yGeZPPzMCw = false;
      bool RCGbzoTFFl = false;
      bool WZdRFVjfml = false;
      bool VxRFUOWfZz = false;
      bool uuzluLDQEi = false;
      bool TZkPEXcMUt = false;
      bool fTYPZTjAHk = false;
      bool RmeFpaZqWs = false;
      bool SSaESuMCAw = false;
      bool kJLeTbWjLa = false;
      bool aCJTQfueZd = false;
      bool xloabMrTwd = false;
      bool HhzKAHaAlO = false;
      bool EpewSPJHnm = false;
      bool AhcWzzUkCG = false;
      bool jCmgSsCyTI = false;
      bool EtrLYGGsIL = false;
      string ROYfIXQrsT;
      string WoYljnlMpr;
      string OVEdgWCUKG;
      string ImYqQLmtZy;
      string fUpTMTBXgR;
      string RRlVSuJtyk;
      string UuglKiQgVY;
      string BqmrMsfkRN;
      string VensnqADXU;
      string BrwocjnDIc;
      string CTCHQaesJY;
      string OYbkPpHnyT;
      string hNIAWIuxOb;
      string FcboKBbfcN;
      string MHtyGbPKYm;
      string czFntoLBkH;
      string fgdgTlxmZN;
      string NaLjHaTJtu;
      string rjXbyGXmtV;
      string pauUhecMeT;
      if(ROYfIXQrsT == CTCHQaesJY){ecjLZCnUgS = true;}
      else if(CTCHQaesJY == ROYfIXQrsT){RmeFpaZqWs = true;}
      if(WoYljnlMpr == OYbkPpHnyT){VBGpPuICiM = true;}
      else if(OYbkPpHnyT == WoYljnlMpr){SSaESuMCAw = true;}
      if(OVEdgWCUKG == hNIAWIuxOb){OJrEXmfpCb = true;}
      else if(hNIAWIuxOb == OVEdgWCUKG){kJLeTbWjLa = true;}
      if(ImYqQLmtZy == FcboKBbfcN){yGeZPPzMCw = true;}
      else if(FcboKBbfcN == ImYqQLmtZy){aCJTQfueZd = true;}
      if(fUpTMTBXgR == MHtyGbPKYm){RCGbzoTFFl = true;}
      else if(MHtyGbPKYm == fUpTMTBXgR){xloabMrTwd = true;}
      if(RRlVSuJtyk == czFntoLBkH){WZdRFVjfml = true;}
      else if(czFntoLBkH == RRlVSuJtyk){HhzKAHaAlO = true;}
      if(UuglKiQgVY == fgdgTlxmZN){VxRFUOWfZz = true;}
      else if(fgdgTlxmZN == UuglKiQgVY){EpewSPJHnm = true;}
      if(BqmrMsfkRN == NaLjHaTJtu){uuzluLDQEi = true;}
      if(VensnqADXU == rjXbyGXmtV){TZkPEXcMUt = true;}
      if(BrwocjnDIc == pauUhecMeT){fTYPZTjAHk = true;}
      while(NaLjHaTJtu == BqmrMsfkRN){AhcWzzUkCG = true;}
      while(rjXbyGXmtV == rjXbyGXmtV){jCmgSsCyTI = true;}
      while(pauUhecMeT == pauUhecMeT){EtrLYGGsIL = true;}
      if(ecjLZCnUgS == true){ecjLZCnUgS = false;}
      if(VBGpPuICiM == true){VBGpPuICiM = false;}
      if(OJrEXmfpCb == true){OJrEXmfpCb = false;}
      if(yGeZPPzMCw == true){yGeZPPzMCw = false;}
      if(RCGbzoTFFl == true){RCGbzoTFFl = false;}
      if(WZdRFVjfml == true){WZdRFVjfml = false;}
      if(VxRFUOWfZz == true){VxRFUOWfZz = false;}
      if(uuzluLDQEi == true){uuzluLDQEi = false;}
      if(TZkPEXcMUt == true){TZkPEXcMUt = false;}
      if(fTYPZTjAHk == true){fTYPZTjAHk = false;}
      if(RmeFpaZqWs == true){RmeFpaZqWs = false;}
      if(SSaESuMCAw == true){SSaESuMCAw = false;}
      if(kJLeTbWjLa == true){kJLeTbWjLa = false;}
      if(aCJTQfueZd == true){aCJTQfueZd = false;}
      if(xloabMrTwd == true){xloabMrTwd = false;}
      if(HhzKAHaAlO == true){HhzKAHaAlO = false;}
      if(EpewSPJHnm == true){EpewSPJHnm = false;}
      if(AhcWzzUkCG == true){AhcWzzUkCG = false;}
      if(jCmgSsCyTI == true){jCmgSsCyTI = false;}
      if(EtrLYGGsIL == true){EtrLYGGsIL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHKLTDSPPX
{ 
  void LNGjWNXmEV()
  { 
      bool OqPZarTDWc = false;
      bool HUElfqbGNK = false;
      bool ZTiKfxalLd = false;
      bool jMoQUspXCt = false;
      bool BDMwxYTZMG = false;
      bool XLeZpuIEsd = false;
      bool RgrrsufnRm = false;
      bool AEDTIVGmNG = false;
      bool dAZFFXgPaY = false;
      bool kleYbULTDB = false;
      bool sfHYFTHLQT = false;
      bool nUqlzRGmmU = false;
      bool NPMrCOYeqm = false;
      bool KljLNxsAzk = false;
      bool QVyHjPusYK = false;
      bool NXghmcSOWq = false;
      bool tcTdICkeYC = false;
      bool YGmBErRFIm = false;
      bool TfFgYlEBXj = false;
      bool eddIqmBUyh = false;
      string VchiqTJRyj;
      string kVdLoLlIjw;
      string DiziPHOiOP;
      string gWEZjiMixg;
      string bsyIwflpcB;
      string liLoKldzSi;
      string EaDhDOQDaG;
      string yCLCUKkpli;
      string VYFMdyKPPx;
      string ENPNbBoQFh;
      string PhOWCiWJUA;
      string BmMjNfVpDE;
      string DBncBklxZS;
      string UTjETmJhKt;
      string aBuPwRAfzw;
      string fzMAeNskVQ;
      string xZiBfgCIQZ;
      string VmfIdBGYgi;
      string kGxcmUHiYF;
      string tYMsxARsjP;
      if(VchiqTJRyj == PhOWCiWJUA){OqPZarTDWc = true;}
      else if(PhOWCiWJUA == VchiqTJRyj){sfHYFTHLQT = true;}
      if(kVdLoLlIjw == BmMjNfVpDE){HUElfqbGNK = true;}
      else if(BmMjNfVpDE == kVdLoLlIjw){nUqlzRGmmU = true;}
      if(DiziPHOiOP == DBncBklxZS){ZTiKfxalLd = true;}
      else if(DBncBklxZS == DiziPHOiOP){NPMrCOYeqm = true;}
      if(gWEZjiMixg == UTjETmJhKt){jMoQUspXCt = true;}
      else if(UTjETmJhKt == gWEZjiMixg){KljLNxsAzk = true;}
      if(bsyIwflpcB == aBuPwRAfzw){BDMwxYTZMG = true;}
      else if(aBuPwRAfzw == bsyIwflpcB){QVyHjPusYK = true;}
      if(liLoKldzSi == fzMAeNskVQ){XLeZpuIEsd = true;}
      else if(fzMAeNskVQ == liLoKldzSi){NXghmcSOWq = true;}
      if(EaDhDOQDaG == xZiBfgCIQZ){RgrrsufnRm = true;}
      else if(xZiBfgCIQZ == EaDhDOQDaG){tcTdICkeYC = true;}
      if(yCLCUKkpli == VmfIdBGYgi){AEDTIVGmNG = true;}
      if(VYFMdyKPPx == kGxcmUHiYF){dAZFFXgPaY = true;}
      if(ENPNbBoQFh == tYMsxARsjP){kleYbULTDB = true;}
      while(VmfIdBGYgi == yCLCUKkpli){YGmBErRFIm = true;}
      while(kGxcmUHiYF == kGxcmUHiYF){TfFgYlEBXj = true;}
      while(tYMsxARsjP == tYMsxARsjP){eddIqmBUyh = true;}
      if(OqPZarTDWc == true){OqPZarTDWc = false;}
      if(HUElfqbGNK == true){HUElfqbGNK = false;}
      if(ZTiKfxalLd == true){ZTiKfxalLd = false;}
      if(jMoQUspXCt == true){jMoQUspXCt = false;}
      if(BDMwxYTZMG == true){BDMwxYTZMG = false;}
      if(XLeZpuIEsd == true){XLeZpuIEsd = false;}
      if(RgrrsufnRm == true){RgrrsufnRm = false;}
      if(AEDTIVGmNG == true){AEDTIVGmNG = false;}
      if(dAZFFXgPaY == true){dAZFFXgPaY = false;}
      if(kleYbULTDB == true){kleYbULTDB = false;}
      if(sfHYFTHLQT == true){sfHYFTHLQT = false;}
      if(nUqlzRGmmU == true){nUqlzRGmmU = false;}
      if(NPMrCOYeqm == true){NPMrCOYeqm = false;}
      if(KljLNxsAzk == true){KljLNxsAzk = false;}
      if(QVyHjPusYK == true){QVyHjPusYK = false;}
      if(NXghmcSOWq == true){NXghmcSOWq = false;}
      if(tcTdICkeYC == true){tcTdICkeYC = false;}
      if(YGmBErRFIm == true){YGmBErRFIm = false;}
      if(TfFgYlEBXj == true){TfFgYlEBXj = false;}
      if(eddIqmBUyh == true){eddIqmBUyh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXKGPTNECY
{ 
  void UstGpQjeni()
  { 
      bool DGkweKmyHR = false;
      bool ThSqzZWeNd = false;
      bool DmDkGPgazx = false;
      bool pCCaqbBdSE = false;
      bool OGMlHiMJjb = false;
      bool CVhyeQCzpO = false;
      bool cMzJbQfqAW = false;
      bool XsLIPwaRcW = false;
      bool DWpXtTUEwa = false;
      bool YBmDaCHCKq = false;
      bool CUINDIJYih = false;
      bool ojWSLFVaPH = false;
      bool ubuZxVGIgN = false;
      bool oYHlThOcUk = false;
      bool JuUOkneTqV = false;
      bool fflCuaZiPg = false;
      bool CBqVrQckyd = false;
      bool qsGdxzGgnJ = false;
      bool plRLgJlEps = false;
      bool HeNmhIEzVT = false;
      string nqfuxwshQg;
      string jwgnRbfUSm;
      string bGLUFOLrIr;
      string WjPBkwusEP;
      string QAmldVhcML;
      string iHFGJgfLoi;
      string kBYXKzffCU;
      string gmPDWbTZpi;
      string ghewJPeIqD;
      string PiDVdOaOad;
      string oBaqeuqBjh;
      string NFUGCDVbOu;
      string UWnzExitYH;
      string BFzMseHnRN;
      string XcYJpKOxTa;
      string ryzeJSNblh;
      string LxccgIGHMW;
      string uhKBXqyeIt;
      string ilZxOCFTDa;
      string QfBjBZAuch;
      if(nqfuxwshQg == oBaqeuqBjh){DGkweKmyHR = true;}
      else if(oBaqeuqBjh == nqfuxwshQg){CUINDIJYih = true;}
      if(jwgnRbfUSm == NFUGCDVbOu){ThSqzZWeNd = true;}
      else if(NFUGCDVbOu == jwgnRbfUSm){ojWSLFVaPH = true;}
      if(bGLUFOLrIr == UWnzExitYH){DmDkGPgazx = true;}
      else if(UWnzExitYH == bGLUFOLrIr){ubuZxVGIgN = true;}
      if(WjPBkwusEP == BFzMseHnRN){pCCaqbBdSE = true;}
      else if(BFzMseHnRN == WjPBkwusEP){oYHlThOcUk = true;}
      if(QAmldVhcML == XcYJpKOxTa){OGMlHiMJjb = true;}
      else if(XcYJpKOxTa == QAmldVhcML){JuUOkneTqV = true;}
      if(iHFGJgfLoi == ryzeJSNblh){CVhyeQCzpO = true;}
      else if(ryzeJSNblh == iHFGJgfLoi){fflCuaZiPg = true;}
      if(kBYXKzffCU == LxccgIGHMW){cMzJbQfqAW = true;}
      else if(LxccgIGHMW == kBYXKzffCU){CBqVrQckyd = true;}
      if(gmPDWbTZpi == uhKBXqyeIt){XsLIPwaRcW = true;}
      if(ghewJPeIqD == ilZxOCFTDa){DWpXtTUEwa = true;}
      if(PiDVdOaOad == QfBjBZAuch){YBmDaCHCKq = true;}
      while(uhKBXqyeIt == gmPDWbTZpi){qsGdxzGgnJ = true;}
      while(ilZxOCFTDa == ilZxOCFTDa){plRLgJlEps = true;}
      while(QfBjBZAuch == QfBjBZAuch){HeNmhIEzVT = true;}
      if(DGkweKmyHR == true){DGkweKmyHR = false;}
      if(ThSqzZWeNd == true){ThSqzZWeNd = false;}
      if(DmDkGPgazx == true){DmDkGPgazx = false;}
      if(pCCaqbBdSE == true){pCCaqbBdSE = false;}
      if(OGMlHiMJjb == true){OGMlHiMJjb = false;}
      if(CVhyeQCzpO == true){CVhyeQCzpO = false;}
      if(cMzJbQfqAW == true){cMzJbQfqAW = false;}
      if(XsLIPwaRcW == true){XsLIPwaRcW = false;}
      if(DWpXtTUEwa == true){DWpXtTUEwa = false;}
      if(YBmDaCHCKq == true){YBmDaCHCKq = false;}
      if(CUINDIJYih == true){CUINDIJYih = false;}
      if(ojWSLFVaPH == true){ojWSLFVaPH = false;}
      if(ubuZxVGIgN == true){ubuZxVGIgN = false;}
      if(oYHlThOcUk == true){oYHlThOcUk = false;}
      if(JuUOkneTqV == true){JuUOkneTqV = false;}
      if(fflCuaZiPg == true){fflCuaZiPg = false;}
      if(CBqVrQckyd == true){CBqVrQckyd = false;}
      if(qsGdxzGgnJ == true){qsGdxzGgnJ = false;}
      if(plRLgJlEps == true){plRLgJlEps = false;}
      if(HeNmhIEzVT == true){HeNmhIEzVT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MRMYDRYNGQ
{ 
  void HXHVXlNboI()
  { 
      bool WJbtPpBzzU = false;
      bool BEwtfouazV = false;
      bool hFiXDknSPH = false;
      bool IgMeZAgsEz = false;
      bool tGFcTMkGLP = false;
      bool ggGKHQaDpd = false;
      bool BijrLUqRUf = false;
      bool IBVAabzGEp = false;
      bool zhGAabaCWJ = false;
      bool YcDZxLWNQy = false;
      bool UTlfGeKFje = false;
      bool QUzzdTbiRj = false;
      bool sotLGfywDO = false;
      bool FlpFUfwatu = false;
      bool QVRrrEcDud = false;
      bool imwfEeZaYZ = false;
      bool gOBUZeesey = false;
      bool XBoVSXXCSC = false;
      bool CtAYfRoJAo = false;
      bool FVCTOCTxRM = false;
      string uJEbBCHqKd;
      string XshTTFHslD;
      string sNoGrLVFVI;
      string lEERbDBFpg;
      string RctVWMGHnu;
      string coDxqhTxip;
      string fBUCqToQrP;
      string DBDElQSSjf;
      string FNRaexBGZs;
      string jDWABPHrdC;
      string WoPXqblyLa;
      string PANCkRitXt;
      string ShqyfAdCDV;
      string JaogJPysiD;
      string KCuydipUOi;
      string fMTijnxQrq;
      string yiuoRnLfsU;
      string TpKUiPmsTx;
      string KImTowGFxU;
      string RhBrEbHFfo;
      if(uJEbBCHqKd == WoPXqblyLa){WJbtPpBzzU = true;}
      else if(WoPXqblyLa == uJEbBCHqKd){UTlfGeKFje = true;}
      if(XshTTFHslD == PANCkRitXt){BEwtfouazV = true;}
      else if(PANCkRitXt == XshTTFHslD){QUzzdTbiRj = true;}
      if(sNoGrLVFVI == ShqyfAdCDV){hFiXDknSPH = true;}
      else if(ShqyfAdCDV == sNoGrLVFVI){sotLGfywDO = true;}
      if(lEERbDBFpg == JaogJPysiD){IgMeZAgsEz = true;}
      else if(JaogJPysiD == lEERbDBFpg){FlpFUfwatu = true;}
      if(RctVWMGHnu == KCuydipUOi){tGFcTMkGLP = true;}
      else if(KCuydipUOi == RctVWMGHnu){QVRrrEcDud = true;}
      if(coDxqhTxip == fMTijnxQrq){ggGKHQaDpd = true;}
      else if(fMTijnxQrq == coDxqhTxip){imwfEeZaYZ = true;}
      if(fBUCqToQrP == yiuoRnLfsU){BijrLUqRUf = true;}
      else if(yiuoRnLfsU == fBUCqToQrP){gOBUZeesey = true;}
      if(DBDElQSSjf == TpKUiPmsTx){IBVAabzGEp = true;}
      if(FNRaexBGZs == KImTowGFxU){zhGAabaCWJ = true;}
      if(jDWABPHrdC == RhBrEbHFfo){YcDZxLWNQy = true;}
      while(TpKUiPmsTx == DBDElQSSjf){XBoVSXXCSC = true;}
      while(KImTowGFxU == KImTowGFxU){CtAYfRoJAo = true;}
      while(RhBrEbHFfo == RhBrEbHFfo){FVCTOCTxRM = true;}
      if(WJbtPpBzzU == true){WJbtPpBzzU = false;}
      if(BEwtfouazV == true){BEwtfouazV = false;}
      if(hFiXDknSPH == true){hFiXDknSPH = false;}
      if(IgMeZAgsEz == true){IgMeZAgsEz = false;}
      if(tGFcTMkGLP == true){tGFcTMkGLP = false;}
      if(ggGKHQaDpd == true){ggGKHQaDpd = false;}
      if(BijrLUqRUf == true){BijrLUqRUf = false;}
      if(IBVAabzGEp == true){IBVAabzGEp = false;}
      if(zhGAabaCWJ == true){zhGAabaCWJ = false;}
      if(YcDZxLWNQy == true){YcDZxLWNQy = false;}
      if(UTlfGeKFje == true){UTlfGeKFje = false;}
      if(QUzzdTbiRj == true){QUzzdTbiRj = false;}
      if(sotLGfywDO == true){sotLGfywDO = false;}
      if(FlpFUfwatu == true){FlpFUfwatu = false;}
      if(QVRrrEcDud == true){QVRrrEcDud = false;}
      if(imwfEeZaYZ == true){imwfEeZaYZ = false;}
      if(gOBUZeesey == true){gOBUZeesey = false;}
      if(XBoVSXXCSC == true){XBoVSXXCSC = false;}
      if(CtAYfRoJAo == true){CtAYfRoJAo = false;}
      if(FVCTOCTxRM == true){FVCTOCTxRM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLTEAZWQRA
{ 
  void lEABGBknal()
  { 
      bool xXhoKwGAwX = false;
      bool oQBQUBzYua = false;
      bool MkdFsfyFbx = false;
      bool nAyrOJZXfq = false;
      bool LpVogyJywu = false;
      bool CQQdtMtcwd = false;
      bool xAYzioSICL = false;
      bool absEOVOnXt = false;
      bool WzIfuXiTxC = false;
      bool OxbBtKQVGq = false;
      bool fAwjTaXMPX = false;
      bool xFEBHxqrEL = false;
      bool GzKAwczqKD = false;
      bool FshgOVDXLT = false;
      bool zWEZEJsZtw = false;
      bool TYRukgpwnp = false;
      bool agCLSDWWmk = false;
      bool tTfjLiukul = false;
      bool jYwNjgbmug = false;
      bool fHjVsSUrGA = false;
      string YhzQMhnlAR;
      string XLgxnqWnWU;
      string tmpqfPMAdm;
      string NVZrNJbtmZ;
      string FdSPowKrSM;
      string EZGwFlrHjx;
      string VnINDBlnjd;
      string ObAxOQTaCi;
      string FTgRhnPcma;
      string RTKpDRUELm;
      string KVInxbYJgn;
      string RRFArBGqeP;
      string kIBILuRKsx;
      string uPOOYiKrTG;
      string PGwyJAOJxB;
      string KdYwCCTAcC;
      string JNQisCCpbI;
      string qOWYzeMDzL;
      string gINqmRpRMW;
      string PKPRxCpMFG;
      if(YhzQMhnlAR == KVInxbYJgn){xXhoKwGAwX = true;}
      else if(KVInxbYJgn == YhzQMhnlAR){fAwjTaXMPX = true;}
      if(XLgxnqWnWU == RRFArBGqeP){oQBQUBzYua = true;}
      else if(RRFArBGqeP == XLgxnqWnWU){xFEBHxqrEL = true;}
      if(tmpqfPMAdm == kIBILuRKsx){MkdFsfyFbx = true;}
      else if(kIBILuRKsx == tmpqfPMAdm){GzKAwczqKD = true;}
      if(NVZrNJbtmZ == uPOOYiKrTG){nAyrOJZXfq = true;}
      else if(uPOOYiKrTG == NVZrNJbtmZ){FshgOVDXLT = true;}
      if(FdSPowKrSM == PGwyJAOJxB){LpVogyJywu = true;}
      else if(PGwyJAOJxB == FdSPowKrSM){zWEZEJsZtw = true;}
      if(EZGwFlrHjx == KdYwCCTAcC){CQQdtMtcwd = true;}
      else if(KdYwCCTAcC == EZGwFlrHjx){TYRukgpwnp = true;}
      if(VnINDBlnjd == JNQisCCpbI){xAYzioSICL = true;}
      else if(JNQisCCpbI == VnINDBlnjd){agCLSDWWmk = true;}
      if(ObAxOQTaCi == qOWYzeMDzL){absEOVOnXt = true;}
      if(FTgRhnPcma == gINqmRpRMW){WzIfuXiTxC = true;}
      if(RTKpDRUELm == PKPRxCpMFG){OxbBtKQVGq = true;}
      while(qOWYzeMDzL == ObAxOQTaCi){tTfjLiukul = true;}
      while(gINqmRpRMW == gINqmRpRMW){jYwNjgbmug = true;}
      while(PKPRxCpMFG == PKPRxCpMFG){fHjVsSUrGA = true;}
      if(xXhoKwGAwX == true){xXhoKwGAwX = false;}
      if(oQBQUBzYua == true){oQBQUBzYua = false;}
      if(MkdFsfyFbx == true){MkdFsfyFbx = false;}
      if(nAyrOJZXfq == true){nAyrOJZXfq = false;}
      if(LpVogyJywu == true){LpVogyJywu = false;}
      if(CQQdtMtcwd == true){CQQdtMtcwd = false;}
      if(xAYzioSICL == true){xAYzioSICL = false;}
      if(absEOVOnXt == true){absEOVOnXt = false;}
      if(WzIfuXiTxC == true){WzIfuXiTxC = false;}
      if(OxbBtKQVGq == true){OxbBtKQVGq = false;}
      if(fAwjTaXMPX == true){fAwjTaXMPX = false;}
      if(xFEBHxqrEL == true){xFEBHxqrEL = false;}
      if(GzKAwczqKD == true){GzKAwczqKD = false;}
      if(FshgOVDXLT == true){FshgOVDXLT = false;}
      if(zWEZEJsZtw == true){zWEZEJsZtw = false;}
      if(TYRukgpwnp == true){TYRukgpwnp = false;}
      if(agCLSDWWmk == true){agCLSDWWmk = false;}
      if(tTfjLiukul == true){tTfjLiukul = false;}
      if(jYwNjgbmug == true){jYwNjgbmug = false;}
      if(fHjVsSUrGA == true){fHjVsSUrGA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHFTMZHHJP
{ 
  void atPnfrqDwC()
  { 
      bool IPjqbDRriX = false;
      bool pNZhWKZcWy = false;
      bool kToodtnMmf = false;
      bool mXbrybmdUI = false;
      bool neLTFZAXbi = false;
      bool tpNuxnauNg = false;
      bool OFFCkSkhju = false;
      bool XwIOKFIUiD = false;
      bool sPkElwJgtJ = false;
      bool BrPmshYIim = false;
      bool nRnfLyhzkq = false;
      bool fFLKmyUBQn = false;
      bool IEmatffUUb = false;
      bool gzluOabEsm = false;
      bool NJuCcufFzt = false;
      bool NXrtdjeMlf = false;
      bool SNdJKgSPuL = false;
      bool VPIcazIjxy = false;
      bool zZVaNIHrRe = false;
      bool wPRMUAelrw = false;
      string FTrjAQdDhM;
      string ZhMokuuwYj;
      string eWtnhiYaLW;
      string BPwIcpFCQk;
      string otsNmMHdNt;
      string THFlXhZEBR;
      string qCqKLJlELt;
      string psemukdfAV;
      string btNRCsKJju;
      string QAAztlChCd;
      string aDSSDabRqm;
      string EsDfpxoYIR;
      string zbTQdorfsI;
      string iwdWtXbtNb;
      string QrSxpWxUJw;
      string xcYjeyjBoO;
      string hwYhDHOgkR;
      string UtLgAGIVaG;
      string rXVwLFWtru;
      string naFysUTksh;
      if(FTrjAQdDhM == aDSSDabRqm){IPjqbDRriX = true;}
      else if(aDSSDabRqm == FTrjAQdDhM){nRnfLyhzkq = true;}
      if(ZhMokuuwYj == EsDfpxoYIR){pNZhWKZcWy = true;}
      else if(EsDfpxoYIR == ZhMokuuwYj){fFLKmyUBQn = true;}
      if(eWtnhiYaLW == zbTQdorfsI){kToodtnMmf = true;}
      else if(zbTQdorfsI == eWtnhiYaLW){IEmatffUUb = true;}
      if(BPwIcpFCQk == iwdWtXbtNb){mXbrybmdUI = true;}
      else if(iwdWtXbtNb == BPwIcpFCQk){gzluOabEsm = true;}
      if(otsNmMHdNt == QrSxpWxUJw){neLTFZAXbi = true;}
      else if(QrSxpWxUJw == otsNmMHdNt){NJuCcufFzt = true;}
      if(THFlXhZEBR == xcYjeyjBoO){tpNuxnauNg = true;}
      else if(xcYjeyjBoO == THFlXhZEBR){NXrtdjeMlf = true;}
      if(qCqKLJlELt == hwYhDHOgkR){OFFCkSkhju = true;}
      else if(hwYhDHOgkR == qCqKLJlELt){SNdJKgSPuL = true;}
      if(psemukdfAV == UtLgAGIVaG){XwIOKFIUiD = true;}
      if(btNRCsKJju == rXVwLFWtru){sPkElwJgtJ = true;}
      if(QAAztlChCd == naFysUTksh){BrPmshYIim = true;}
      while(UtLgAGIVaG == psemukdfAV){VPIcazIjxy = true;}
      while(rXVwLFWtru == rXVwLFWtru){zZVaNIHrRe = true;}
      while(naFysUTksh == naFysUTksh){wPRMUAelrw = true;}
      if(IPjqbDRriX == true){IPjqbDRriX = false;}
      if(pNZhWKZcWy == true){pNZhWKZcWy = false;}
      if(kToodtnMmf == true){kToodtnMmf = false;}
      if(mXbrybmdUI == true){mXbrybmdUI = false;}
      if(neLTFZAXbi == true){neLTFZAXbi = false;}
      if(tpNuxnauNg == true){tpNuxnauNg = false;}
      if(OFFCkSkhju == true){OFFCkSkhju = false;}
      if(XwIOKFIUiD == true){XwIOKFIUiD = false;}
      if(sPkElwJgtJ == true){sPkElwJgtJ = false;}
      if(BrPmshYIim == true){BrPmshYIim = false;}
      if(nRnfLyhzkq == true){nRnfLyhzkq = false;}
      if(fFLKmyUBQn == true){fFLKmyUBQn = false;}
      if(IEmatffUUb == true){IEmatffUUb = false;}
      if(gzluOabEsm == true){gzluOabEsm = false;}
      if(NJuCcufFzt == true){NJuCcufFzt = false;}
      if(NXrtdjeMlf == true){NXrtdjeMlf = false;}
      if(SNdJKgSPuL == true){SNdJKgSPuL = false;}
      if(VPIcazIjxy == true){VPIcazIjxy = false;}
      if(zZVaNIHrRe == true){zZVaNIHrRe = false;}
      if(wPRMUAelrw == true){wPRMUAelrw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTMUWTAJTN
{ 
  void pZscUTMALk()
  { 
      bool JnVWZUqxdD = false;
      bool ldJufVcbOO = false;
      bool DdKHktzLbQ = false;
      bool pFjFrsOttM = false;
      bool mNWzWdAnHW = false;
      bool YGqxrecOkf = false;
      bool VeUNNgtDCl = false;
      bool HihBboGLkH = false;
      bool tKDEqiNmNM = false;
      bool QzINqHrJlo = false;
      bool jwkVPoYpUC = false;
      bool YRddlLaQVe = false;
      bool SGppVHZTKU = false;
      bool wxYuXyYhoB = false;
      bool KXSKnyVebe = false;
      bool fbmGVdFuzH = false;
      bool OEeAFariGm = false;
      bool msbUTumfCW = false;
      bool luqenUKSYs = false;
      bool rchglFrSFM = false;
      string dFhREhpZxR;
      string DURhQiiOLA;
      string FOPabMXKat;
      string cWVuSIDAlL;
      string xrsCNJzisb;
      string NEukbOpHoq;
      string KezDofyVOH;
      string ehbzDNVMNR;
      string NnQyfYbkTD;
      string RwKtARrpNg;
      string LcUkwebuhO;
      string sdtXdWNBWP;
      string ENCKoiXgyk;
      string UeyfGjSfBA;
      string wfCFJnBmQd;
      string DqTxcxaJwN;
      string HtxwsOeNQt;
      string DhzVSYKwAB;
      string gkQUhdLBDJ;
      string IJinsCiFLu;
      if(dFhREhpZxR == LcUkwebuhO){JnVWZUqxdD = true;}
      else if(LcUkwebuhO == dFhREhpZxR){jwkVPoYpUC = true;}
      if(DURhQiiOLA == sdtXdWNBWP){ldJufVcbOO = true;}
      else if(sdtXdWNBWP == DURhQiiOLA){YRddlLaQVe = true;}
      if(FOPabMXKat == ENCKoiXgyk){DdKHktzLbQ = true;}
      else if(ENCKoiXgyk == FOPabMXKat){SGppVHZTKU = true;}
      if(cWVuSIDAlL == UeyfGjSfBA){pFjFrsOttM = true;}
      else if(UeyfGjSfBA == cWVuSIDAlL){wxYuXyYhoB = true;}
      if(xrsCNJzisb == wfCFJnBmQd){mNWzWdAnHW = true;}
      else if(wfCFJnBmQd == xrsCNJzisb){KXSKnyVebe = true;}
      if(NEukbOpHoq == DqTxcxaJwN){YGqxrecOkf = true;}
      else if(DqTxcxaJwN == NEukbOpHoq){fbmGVdFuzH = true;}
      if(KezDofyVOH == HtxwsOeNQt){VeUNNgtDCl = true;}
      else if(HtxwsOeNQt == KezDofyVOH){OEeAFariGm = true;}
      if(ehbzDNVMNR == DhzVSYKwAB){HihBboGLkH = true;}
      if(NnQyfYbkTD == gkQUhdLBDJ){tKDEqiNmNM = true;}
      if(RwKtARrpNg == IJinsCiFLu){QzINqHrJlo = true;}
      while(DhzVSYKwAB == ehbzDNVMNR){msbUTumfCW = true;}
      while(gkQUhdLBDJ == gkQUhdLBDJ){luqenUKSYs = true;}
      while(IJinsCiFLu == IJinsCiFLu){rchglFrSFM = true;}
      if(JnVWZUqxdD == true){JnVWZUqxdD = false;}
      if(ldJufVcbOO == true){ldJufVcbOO = false;}
      if(DdKHktzLbQ == true){DdKHktzLbQ = false;}
      if(pFjFrsOttM == true){pFjFrsOttM = false;}
      if(mNWzWdAnHW == true){mNWzWdAnHW = false;}
      if(YGqxrecOkf == true){YGqxrecOkf = false;}
      if(VeUNNgtDCl == true){VeUNNgtDCl = false;}
      if(HihBboGLkH == true){HihBboGLkH = false;}
      if(tKDEqiNmNM == true){tKDEqiNmNM = false;}
      if(QzINqHrJlo == true){QzINqHrJlo = false;}
      if(jwkVPoYpUC == true){jwkVPoYpUC = false;}
      if(YRddlLaQVe == true){YRddlLaQVe = false;}
      if(SGppVHZTKU == true){SGppVHZTKU = false;}
      if(wxYuXyYhoB == true){wxYuXyYhoB = false;}
      if(KXSKnyVebe == true){KXSKnyVebe = false;}
      if(fbmGVdFuzH == true){fbmGVdFuzH = false;}
      if(OEeAFariGm == true){OEeAFariGm = false;}
      if(msbUTumfCW == true){msbUTumfCW = false;}
      if(luqenUKSYs == true){luqenUKSYs = false;}
      if(rchglFrSFM == true){rchglFrSFM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DXNIPPKZHR
{ 
  void nHSLetrzkL()
  { 
      bool mOdSSARjzW = false;
      bool LsLiwpHJuD = false;
      bool HIqkebNEqH = false;
      bool QbSLloxfTX = false;
      bool USsYqaoEfw = false;
      bool dhozBeWrmq = false;
      bool mMsrFjaAxG = false;
      bool saoWinORtD = false;
      bool lJYuchlSKH = false;
      bool SErcjIZBTH = false;
      bool AoHZCDrRQN = false;
      bool PEyjEdmyOW = false;
      bool xHoonoiLlZ = false;
      bool ONylCwByrZ = false;
      bool pUCxqNGIYG = false;
      bool UamwKsARlN = false;
      bool UfepyCGLgH = false;
      bool boFngbEryZ = false;
      bool hZmfFmaCaJ = false;
      bool wjMeFJoLyn = false;
      string uIPoWbwOzO;
      string QeaVXFlTVn;
      string FFCyMYKfQC;
      string KxRrkhhJzb;
      string OIrjuzLGMe;
      string msbTXoFQbx;
      string RPxxESNhjp;
      string XbTtYwNRCM;
      string NESlPRVyTw;
      string bQhCJyKufb;
      string lcVWHLYgta;
      string bmNOjMxLhm;
      string xPOnNGsRja;
      string kRlaZjiwdE;
      string soDrTnCSSx;
      string BzNseWOgIA;
      string RGxTpKBmoz;
      string dAhdsILVUZ;
      string EazmYlDsuD;
      string UBmcllqjCI;
      if(uIPoWbwOzO == lcVWHLYgta){mOdSSARjzW = true;}
      else if(lcVWHLYgta == uIPoWbwOzO){AoHZCDrRQN = true;}
      if(QeaVXFlTVn == bmNOjMxLhm){LsLiwpHJuD = true;}
      else if(bmNOjMxLhm == QeaVXFlTVn){PEyjEdmyOW = true;}
      if(FFCyMYKfQC == xPOnNGsRja){HIqkebNEqH = true;}
      else if(xPOnNGsRja == FFCyMYKfQC){xHoonoiLlZ = true;}
      if(KxRrkhhJzb == kRlaZjiwdE){QbSLloxfTX = true;}
      else if(kRlaZjiwdE == KxRrkhhJzb){ONylCwByrZ = true;}
      if(OIrjuzLGMe == soDrTnCSSx){USsYqaoEfw = true;}
      else if(soDrTnCSSx == OIrjuzLGMe){pUCxqNGIYG = true;}
      if(msbTXoFQbx == BzNseWOgIA){dhozBeWrmq = true;}
      else if(BzNseWOgIA == msbTXoFQbx){UamwKsARlN = true;}
      if(RPxxESNhjp == RGxTpKBmoz){mMsrFjaAxG = true;}
      else if(RGxTpKBmoz == RPxxESNhjp){UfepyCGLgH = true;}
      if(XbTtYwNRCM == dAhdsILVUZ){saoWinORtD = true;}
      if(NESlPRVyTw == EazmYlDsuD){lJYuchlSKH = true;}
      if(bQhCJyKufb == UBmcllqjCI){SErcjIZBTH = true;}
      while(dAhdsILVUZ == XbTtYwNRCM){boFngbEryZ = true;}
      while(EazmYlDsuD == EazmYlDsuD){hZmfFmaCaJ = true;}
      while(UBmcllqjCI == UBmcllqjCI){wjMeFJoLyn = true;}
      if(mOdSSARjzW == true){mOdSSARjzW = false;}
      if(LsLiwpHJuD == true){LsLiwpHJuD = false;}
      if(HIqkebNEqH == true){HIqkebNEqH = false;}
      if(QbSLloxfTX == true){QbSLloxfTX = false;}
      if(USsYqaoEfw == true){USsYqaoEfw = false;}
      if(dhozBeWrmq == true){dhozBeWrmq = false;}
      if(mMsrFjaAxG == true){mMsrFjaAxG = false;}
      if(saoWinORtD == true){saoWinORtD = false;}
      if(lJYuchlSKH == true){lJYuchlSKH = false;}
      if(SErcjIZBTH == true){SErcjIZBTH = false;}
      if(AoHZCDrRQN == true){AoHZCDrRQN = false;}
      if(PEyjEdmyOW == true){PEyjEdmyOW = false;}
      if(xHoonoiLlZ == true){xHoonoiLlZ = false;}
      if(ONylCwByrZ == true){ONylCwByrZ = false;}
      if(pUCxqNGIYG == true){pUCxqNGIYG = false;}
      if(UamwKsARlN == true){UamwKsARlN = false;}
      if(UfepyCGLgH == true){UfepyCGLgH = false;}
      if(boFngbEryZ == true){boFngbEryZ = false;}
      if(hZmfFmaCaJ == true){hZmfFmaCaJ = false;}
      if(wjMeFJoLyn == true){wjMeFJoLyn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QJFXWBDFUF
{ 
  void upwkKDGiSF()
  { 
      bool uqHkSagbNr = false;
      bool KXQURWVQYu = false;
      bool HHSYWgQFCq = false;
      bool mMViKxlMjX = false;
      bool XALBiUoCfC = false;
      bool qwrBcnYiNl = false;
      bool JbZWFxBgJU = false;
      bool kIfBXHwRoC = false;
      bool rOYzzpUUGW = false;
      bool YCzyNuZouk = false;
      bool THrLRiQqdU = false;
      bool rGsLsuDaWP = false;
      bool bgamwhJgmb = false;
      bool gHVDhjVMgQ = false;
      bool ZdpkeRInFS = false;
      bool rzRfJlfFOj = false;
      bool YiDCmkjpcJ = false;
      bool YpsGpyqpId = false;
      bool YVbUihoptw = false;
      bool DQxxqpZnxs = false;
      string oOJbCEBZEN;
      string kQTdIWICUN;
      string AVrrmGNFHI;
      string YmYPEXXOza;
      string yNStayMyuA;
      string fWYAbSWRnu;
      string qwRunxqEZk;
      string ztCsPlCxQo;
      string tOJHcBNYmk;
      string BFZDiBwWFc;
      string GIYKBkTekp;
      string PYAzBcmKSm;
      string iSQnisTzKN;
      string pfrmhkpyGq;
      string hinxUcEZBG;
      string OkDSsnqjaH;
      string RTUWzjgMRQ;
      string mnEbEAdTTG;
      string otyDyEbYts;
      string sFWyZNNQxk;
      if(oOJbCEBZEN == GIYKBkTekp){uqHkSagbNr = true;}
      else if(GIYKBkTekp == oOJbCEBZEN){THrLRiQqdU = true;}
      if(kQTdIWICUN == PYAzBcmKSm){KXQURWVQYu = true;}
      else if(PYAzBcmKSm == kQTdIWICUN){rGsLsuDaWP = true;}
      if(AVrrmGNFHI == iSQnisTzKN){HHSYWgQFCq = true;}
      else if(iSQnisTzKN == AVrrmGNFHI){bgamwhJgmb = true;}
      if(YmYPEXXOza == pfrmhkpyGq){mMViKxlMjX = true;}
      else if(pfrmhkpyGq == YmYPEXXOza){gHVDhjVMgQ = true;}
      if(yNStayMyuA == hinxUcEZBG){XALBiUoCfC = true;}
      else if(hinxUcEZBG == yNStayMyuA){ZdpkeRInFS = true;}
      if(fWYAbSWRnu == OkDSsnqjaH){qwrBcnYiNl = true;}
      else if(OkDSsnqjaH == fWYAbSWRnu){rzRfJlfFOj = true;}
      if(qwRunxqEZk == RTUWzjgMRQ){JbZWFxBgJU = true;}
      else if(RTUWzjgMRQ == qwRunxqEZk){YiDCmkjpcJ = true;}
      if(ztCsPlCxQo == mnEbEAdTTG){kIfBXHwRoC = true;}
      if(tOJHcBNYmk == otyDyEbYts){rOYzzpUUGW = true;}
      if(BFZDiBwWFc == sFWyZNNQxk){YCzyNuZouk = true;}
      while(mnEbEAdTTG == ztCsPlCxQo){YpsGpyqpId = true;}
      while(otyDyEbYts == otyDyEbYts){YVbUihoptw = true;}
      while(sFWyZNNQxk == sFWyZNNQxk){DQxxqpZnxs = true;}
      if(uqHkSagbNr == true){uqHkSagbNr = false;}
      if(KXQURWVQYu == true){KXQURWVQYu = false;}
      if(HHSYWgQFCq == true){HHSYWgQFCq = false;}
      if(mMViKxlMjX == true){mMViKxlMjX = false;}
      if(XALBiUoCfC == true){XALBiUoCfC = false;}
      if(qwrBcnYiNl == true){qwrBcnYiNl = false;}
      if(JbZWFxBgJU == true){JbZWFxBgJU = false;}
      if(kIfBXHwRoC == true){kIfBXHwRoC = false;}
      if(rOYzzpUUGW == true){rOYzzpUUGW = false;}
      if(YCzyNuZouk == true){YCzyNuZouk = false;}
      if(THrLRiQqdU == true){THrLRiQqdU = false;}
      if(rGsLsuDaWP == true){rGsLsuDaWP = false;}
      if(bgamwhJgmb == true){bgamwhJgmb = false;}
      if(gHVDhjVMgQ == true){gHVDhjVMgQ = false;}
      if(ZdpkeRInFS == true){ZdpkeRInFS = false;}
      if(rzRfJlfFOj == true){rzRfJlfFOj = false;}
      if(YiDCmkjpcJ == true){YiDCmkjpcJ = false;}
      if(YpsGpyqpId == true){YpsGpyqpId = false;}
      if(YVbUihoptw == true){YVbUihoptw = false;}
      if(DQxxqpZnxs == true){DQxxqpZnxs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PAPBDPGNEF
{ 
  void KAEuXSlNrA()
  { 
      bool MmFukwhdpz = false;
      bool RFFdgUhSVT = false;
      bool oJKtfcAZlY = false;
      bool uMgThYcMKI = false;
      bool DeRyiBmOux = false;
      bool WSbiZDcLOI = false;
      bool wHrQDFXkuH = false;
      bool rVHMQKqLLe = false;
      bool okdnCbjyte = false;
      bool wRxCLulBtc = false;
      bool cCSmFALORO = false;
      bool LQzjSLcDNa = false;
      bool UZpQLZXEAV = false;
      bool XpQhBmRpiB = false;
      bool QVgfSeSNiA = false;
      bool RhmTIDLCbe = false;
      bool cGNwqVzQhf = false;
      bool smULKyrKxg = false;
      bool HKUAEpDxYy = false;
      bool bPODYJHknx = false;
      string umwBGVDEwa;
      string FDLwtIxxwh;
      string bBUNmoAWMJ;
      string XDUkxrRnkg;
      string izyxSwJiCq;
      string xtiWCtRhOQ;
      string VgrmDCiayB;
      string pJLPybDWup;
      string fRTULdTyhD;
      string aiYTLCGKtP;
      string NhjBAnhSXZ;
      string pumXkDMWbZ;
      string hkruaHjqEw;
      string UrcecxhSUW;
      string uAZHMeuBiH;
      string pjiUgcpnZr;
      string EpObFyRIum;
      string VsCEdgKjiu;
      string LiIwFkJIyA;
      string HssbSElyCO;
      if(umwBGVDEwa == NhjBAnhSXZ){MmFukwhdpz = true;}
      else if(NhjBAnhSXZ == umwBGVDEwa){cCSmFALORO = true;}
      if(FDLwtIxxwh == pumXkDMWbZ){RFFdgUhSVT = true;}
      else if(pumXkDMWbZ == FDLwtIxxwh){LQzjSLcDNa = true;}
      if(bBUNmoAWMJ == hkruaHjqEw){oJKtfcAZlY = true;}
      else if(hkruaHjqEw == bBUNmoAWMJ){UZpQLZXEAV = true;}
      if(XDUkxrRnkg == UrcecxhSUW){uMgThYcMKI = true;}
      else if(UrcecxhSUW == XDUkxrRnkg){XpQhBmRpiB = true;}
      if(izyxSwJiCq == uAZHMeuBiH){DeRyiBmOux = true;}
      else if(uAZHMeuBiH == izyxSwJiCq){QVgfSeSNiA = true;}
      if(xtiWCtRhOQ == pjiUgcpnZr){WSbiZDcLOI = true;}
      else if(pjiUgcpnZr == xtiWCtRhOQ){RhmTIDLCbe = true;}
      if(VgrmDCiayB == EpObFyRIum){wHrQDFXkuH = true;}
      else if(EpObFyRIum == VgrmDCiayB){cGNwqVzQhf = true;}
      if(pJLPybDWup == VsCEdgKjiu){rVHMQKqLLe = true;}
      if(fRTULdTyhD == LiIwFkJIyA){okdnCbjyte = true;}
      if(aiYTLCGKtP == HssbSElyCO){wRxCLulBtc = true;}
      while(VsCEdgKjiu == pJLPybDWup){smULKyrKxg = true;}
      while(LiIwFkJIyA == LiIwFkJIyA){HKUAEpDxYy = true;}
      while(HssbSElyCO == HssbSElyCO){bPODYJHknx = true;}
      if(MmFukwhdpz == true){MmFukwhdpz = false;}
      if(RFFdgUhSVT == true){RFFdgUhSVT = false;}
      if(oJKtfcAZlY == true){oJKtfcAZlY = false;}
      if(uMgThYcMKI == true){uMgThYcMKI = false;}
      if(DeRyiBmOux == true){DeRyiBmOux = false;}
      if(WSbiZDcLOI == true){WSbiZDcLOI = false;}
      if(wHrQDFXkuH == true){wHrQDFXkuH = false;}
      if(rVHMQKqLLe == true){rVHMQKqLLe = false;}
      if(okdnCbjyte == true){okdnCbjyte = false;}
      if(wRxCLulBtc == true){wRxCLulBtc = false;}
      if(cCSmFALORO == true){cCSmFALORO = false;}
      if(LQzjSLcDNa == true){LQzjSLcDNa = false;}
      if(UZpQLZXEAV == true){UZpQLZXEAV = false;}
      if(XpQhBmRpiB == true){XpQhBmRpiB = false;}
      if(QVgfSeSNiA == true){QVgfSeSNiA = false;}
      if(RhmTIDLCbe == true){RhmTIDLCbe = false;}
      if(cGNwqVzQhf == true){cGNwqVzQhf = false;}
      if(smULKyrKxg == true){smULKyrKxg = false;}
      if(HKUAEpDxYy == true){HKUAEpDxYy = false;}
      if(bPODYJHknx == true){bPODYJHknx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CANAWLXSBA
{ 
  void YDTttAFuGo()
  { 
      bool ZlwlAzSdta = false;
      bool kwUWRSZadd = false;
      bool WIayKrxoNV = false;
      bool RXZgIKKFmU = false;
      bool BooCfntgEM = false;
      bool cpFNaRLyaI = false;
      bool BdPYINWnNG = false;
      bool IUmJbgTYRW = false;
      bool xPjBraSMGq = false;
      bool zMdeSXZPsS = false;
      bool RGTxEIDuks = false;
      bool xmfEKksOgg = false;
      bool tJhWHuqIpE = false;
      bool HEezFqwlwj = false;
      bool XWaMsMgZTg = false;
      bool dLhLXHXxoI = false;
      bool RtEgksHfyS = false;
      bool oHRxJWiUcu = false;
      bool OQnJawVTby = false;
      bool SzwnRdRtbA = false;
      string knhcBsWqrL;
      string bwLJlyDuHf;
      string lmeiMlopHs;
      string GYGOUWeArh;
      string uKWQZVRHXU;
      string utjFZxJzPO;
      string DfiyECowoP;
      string SCDZkaPOJq;
      string TgSmyLoBoW;
      string NfjcdOaXLW;
      string gVSIBrqJTy;
      string htpYtVMwAr;
      string NnHSBmRZuV;
      string zqClJyOKkG;
      string TegpnSpLhH;
      string BeXSJrNzGO;
      string ZRNyyprDOw;
      string HCLtXhHQdi;
      string xGqmTUTicQ;
      string kPEVfCQiqx;
      if(knhcBsWqrL == gVSIBrqJTy){ZlwlAzSdta = true;}
      else if(gVSIBrqJTy == knhcBsWqrL){RGTxEIDuks = true;}
      if(bwLJlyDuHf == htpYtVMwAr){kwUWRSZadd = true;}
      else if(htpYtVMwAr == bwLJlyDuHf){xmfEKksOgg = true;}
      if(lmeiMlopHs == NnHSBmRZuV){WIayKrxoNV = true;}
      else if(NnHSBmRZuV == lmeiMlopHs){tJhWHuqIpE = true;}
      if(GYGOUWeArh == zqClJyOKkG){RXZgIKKFmU = true;}
      else if(zqClJyOKkG == GYGOUWeArh){HEezFqwlwj = true;}
      if(uKWQZVRHXU == TegpnSpLhH){BooCfntgEM = true;}
      else if(TegpnSpLhH == uKWQZVRHXU){XWaMsMgZTg = true;}
      if(utjFZxJzPO == BeXSJrNzGO){cpFNaRLyaI = true;}
      else if(BeXSJrNzGO == utjFZxJzPO){dLhLXHXxoI = true;}
      if(DfiyECowoP == ZRNyyprDOw){BdPYINWnNG = true;}
      else if(ZRNyyprDOw == DfiyECowoP){RtEgksHfyS = true;}
      if(SCDZkaPOJq == HCLtXhHQdi){IUmJbgTYRW = true;}
      if(TgSmyLoBoW == xGqmTUTicQ){xPjBraSMGq = true;}
      if(NfjcdOaXLW == kPEVfCQiqx){zMdeSXZPsS = true;}
      while(HCLtXhHQdi == SCDZkaPOJq){oHRxJWiUcu = true;}
      while(xGqmTUTicQ == xGqmTUTicQ){OQnJawVTby = true;}
      while(kPEVfCQiqx == kPEVfCQiqx){SzwnRdRtbA = true;}
      if(ZlwlAzSdta == true){ZlwlAzSdta = false;}
      if(kwUWRSZadd == true){kwUWRSZadd = false;}
      if(WIayKrxoNV == true){WIayKrxoNV = false;}
      if(RXZgIKKFmU == true){RXZgIKKFmU = false;}
      if(BooCfntgEM == true){BooCfntgEM = false;}
      if(cpFNaRLyaI == true){cpFNaRLyaI = false;}
      if(BdPYINWnNG == true){BdPYINWnNG = false;}
      if(IUmJbgTYRW == true){IUmJbgTYRW = false;}
      if(xPjBraSMGq == true){xPjBraSMGq = false;}
      if(zMdeSXZPsS == true){zMdeSXZPsS = false;}
      if(RGTxEIDuks == true){RGTxEIDuks = false;}
      if(xmfEKksOgg == true){xmfEKksOgg = false;}
      if(tJhWHuqIpE == true){tJhWHuqIpE = false;}
      if(HEezFqwlwj == true){HEezFqwlwj = false;}
      if(XWaMsMgZTg == true){XWaMsMgZTg = false;}
      if(dLhLXHXxoI == true){dLhLXHXxoI = false;}
      if(RtEgksHfyS == true){RtEgksHfyS = false;}
      if(oHRxJWiUcu == true){oHRxJWiUcu = false;}
      if(OQnJawVTby == true){OQnJawVTby = false;}
      if(SzwnRdRtbA == true){SzwnRdRtbA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYSNKVYWST
{ 
  void zlMuJyuuyR()
  { 
      bool EEKSrRWWWI = false;
      bool qsqkOMQKfU = false;
      bool YVlqNpDqVH = false;
      bool BgmIGyRziI = false;
      bool llcHmXaWlK = false;
      bool gUJANhRTFC = false;
      bool NeBOHJGheQ = false;
      bool tRbWhlseEo = false;
      bool OgEKZfWmuX = false;
      bool gytftHkNAc = false;
      bool RrrVQPsmSa = false;
      bool omOPmgZpoa = false;
      bool mTmGjuXuba = false;
      bool BedaXWoitJ = false;
      bool mjUUhsjdrN = false;
      bool gtYZpyFkkU = false;
      bool ryKqYKImrQ = false;
      bool rqwenCzSXp = false;
      bool LsCOsHFEkZ = false;
      bool QDxYRoZcuX = false;
      string uZEljQbCnY;
      string PxWbWjurWr;
      string ooiGsEzatT;
      string AlSKiNMocf;
      string tlqpPPYsoz;
      string GPFJGFpysf;
      string RBITYdeMrI;
      string XGOqxDxsqd;
      string fFkuNjfJDc;
      string XNwxNsdWQl;
      string jLBgaABOLD;
      string IxHOzMPNGn;
      string xVIOkJKQcE;
      string ZZbEsTEETN;
      string iQxzUZGgyB;
      string cQQbnOClwR;
      string pjlHdhVCVe;
      string ILssFfXItK;
      string CcSbaJJzPd;
      string RRHBXyepVl;
      if(uZEljQbCnY == jLBgaABOLD){EEKSrRWWWI = true;}
      else if(jLBgaABOLD == uZEljQbCnY){RrrVQPsmSa = true;}
      if(PxWbWjurWr == IxHOzMPNGn){qsqkOMQKfU = true;}
      else if(IxHOzMPNGn == PxWbWjurWr){omOPmgZpoa = true;}
      if(ooiGsEzatT == xVIOkJKQcE){YVlqNpDqVH = true;}
      else if(xVIOkJKQcE == ooiGsEzatT){mTmGjuXuba = true;}
      if(AlSKiNMocf == ZZbEsTEETN){BgmIGyRziI = true;}
      else if(ZZbEsTEETN == AlSKiNMocf){BedaXWoitJ = true;}
      if(tlqpPPYsoz == iQxzUZGgyB){llcHmXaWlK = true;}
      else if(iQxzUZGgyB == tlqpPPYsoz){mjUUhsjdrN = true;}
      if(GPFJGFpysf == cQQbnOClwR){gUJANhRTFC = true;}
      else if(cQQbnOClwR == GPFJGFpysf){gtYZpyFkkU = true;}
      if(RBITYdeMrI == pjlHdhVCVe){NeBOHJGheQ = true;}
      else if(pjlHdhVCVe == RBITYdeMrI){ryKqYKImrQ = true;}
      if(XGOqxDxsqd == ILssFfXItK){tRbWhlseEo = true;}
      if(fFkuNjfJDc == CcSbaJJzPd){OgEKZfWmuX = true;}
      if(XNwxNsdWQl == RRHBXyepVl){gytftHkNAc = true;}
      while(ILssFfXItK == XGOqxDxsqd){rqwenCzSXp = true;}
      while(CcSbaJJzPd == CcSbaJJzPd){LsCOsHFEkZ = true;}
      while(RRHBXyepVl == RRHBXyepVl){QDxYRoZcuX = true;}
      if(EEKSrRWWWI == true){EEKSrRWWWI = false;}
      if(qsqkOMQKfU == true){qsqkOMQKfU = false;}
      if(YVlqNpDqVH == true){YVlqNpDqVH = false;}
      if(BgmIGyRziI == true){BgmIGyRziI = false;}
      if(llcHmXaWlK == true){llcHmXaWlK = false;}
      if(gUJANhRTFC == true){gUJANhRTFC = false;}
      if(NeBOHJGheQ == true){NeBOHJGheQ = false;}
      if(tRbWhlseEo == true){tRbWhlseEo = false;}
      if(OgEKZfWmuX == true){OgEKZfWmuX = false;}
      if(gytftHkNAc == true){gytftHkNAc = false;}
      if(RrrVQPsmSa == true){RrrVQPsmSa = false;}
      if(omOPmgZpoa == true){omOPmgZpoa = false;}
      if(mTmGjuXuba == true){mTmGjuXuba = false;}
      if(BedaXWoitJ == true){BedaXWoitJ = false;}
      if(mjUUhsjdrN == true){mjUUhsjdrN = false;}
      if(gtYZpyFkkU == true){gtYZpyFkkU = false;}
      if(ryKqYKImrQ == true){ryKqYKImrQ = false;}
      if(rqwenCzSXp == true){rqwenCzSXp = false;}
      if(LsCOsHFEkZ == true){LsCOsHFEkZ = false;}
      if(QDxYRoZcuX == true){QDxYRoZcuX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVLZAIIGTH
{ 
  void gxCPwJnozA()
  { 
      bool JfJMdKDPgj = false;
      bool gAbAubmhpP = false;
      bool IAhlQlJmsc = false;
      bool cbrCmpIfct = false;
      bool EdRLpgJgcY = false;
      bool iKWRSIyXur = false;
      bool BPWEHEHZNE = false;
      bool TGEuLdhVui = false;
      bool cbKTtSFaid = false;
      bool rkkkroHNEk = false;
      bool ZiTYFbFbGo = false;
      bool abbLPZECJn = false;
      bool zgpjMiVTCV = false;
      bool WURJJsIkNR = false;
      bool McUtCQIYUS = false;
      bool jFEPlssiLW = false;
      bool GlYjSGJRCW = false;
      bool QTnqbVLwgw = false;
      bool ZwyjkRPCXQ = false;
      bool zYZqLZEjbw = false;
      string nlEOihmxlp;
      string wBTmkJATRH;
      string sboJtJLiIS;
      string AKrkwnlqto;
      string bFVYwdqFAV;
      string oLchiMwtTZ;
      string VEnTplJiqx;
      string XJZcenFPNP;
      string RGhmcnhKBj;
      string qqWTSXQBiK;
      string UINDxflzCu;
      string GggEIPVBqB;
      string DygHGflFJH;
      string WEgCtJreow;
      string ChIGcJKSLC;
      string BOKgGWaGxQ;
      string tfouXBAdJz;
      string XqLtzVoadw;
      string VSsHFHszwX;
      string hlhXBVrNha;
      if(nlEOihmxlp == UINDxflzCu){JfJMdKDPgj = true;}
      else if(UINDxflzCu == nlEOihmxlp){ZiTYFbFbGo = true;}
      if(wBTmkJATRH == GggEIPVBqB){gAbAubmhpP = true;}
      else if(GggEIPVBqB == wBTmkJATRH){abbLPZECJn = true;}
      if(sboJtJLiIS == DygHGflFJH){IAhlQlJmsc = true;}
      else if(DygHGflFJH == sboJtJLiIS){zgpjMiVTCV = true;}
      if(AKrkwnlqto == WEgCtJreow){cbrCmpIfct = true;}
      else if(WEgCtJreow == AKrkwnlqto){WURJJsIkNR = true;}
      if(bFVYwdqFAV == ChIGcJKSLC){EdRLpgJgcY = true;}
      else if(ChIGcJKSLC == bFVYwdqFAV){McUtCQIYUS = true;}
      if(oLchiMwtTZ == BOKgGWaGxQ){iKWRSIyXur = true;}
      else if(BOKgGWaGxQ == oLchiMwtTZ){jFEPlssiLW = true;}
      if(VEnTplJiqx == tfouXBAdJz){BPWEHEHZNE = true;}
      else if(tfouXBAdJz == VEnTplJiqx){GlYjSGJRCW = true;}
      if(XJZcenFPNP == XqLtzVoadw){TGEuLdhVui = true;}
      if(RGhmcnhKBj == VSsHFHszwX){cbKTtSFaid = true;}
      if(qqWTSXQBiK == hlhXBVrNha){rkkkroHNEk = true;}
      while(XqLtzVoadw == XJZcenFPNP){QTnqbVLwgw = true;}
      while(VSsHFHszwX == VSsHFHszwX){ZwyjkRPCXQ = true;}
      while(hlhXBVrNha == hlhXBVrNha){zYZqLZEjbw = true;}
      if(JfJMdKDPgj == true){JfJMdKDPgj = false;}
      if(gAbAubmhpP == true){gAbAubmhpP = false;}
      if(IAhlQlJmsc == true){IAhlQlJmsc = false;}
      if(cbrCmpIfct == true){cbrCmpIfct = false;}
      if(EdRLpgJgcY == true){EdRLpgJgcY = false;}
      if(iKWRSIyXur == true){iKWRSIyXur = false;}
      if(BPWEHEHZNE == true){BPWEHEHZNE = false;}
      if(TGEuLdhVui == true){TGEuLdhVui = false;}
      if(cbKTtSFaid == true){cbKTtSFaid = false;}
      if(rkkkroHNEk == true){rkkkroHNEk = false;}
      if(ZiTYFbFbGo == true){ZiTYFbFbGo = false;}
      if(abbLPZECJn == true){abbLPZECJn = false;}
      if(zgpjMiVTCV == true){zgpjMiVTCV = false;}
      if(WURJJsIkNR == true){WURJJsIkNR = false;}
      if(McUtCQIYUS == true){McUtCQIYUS = false;}
      if(jFEPlssiLW == true){jFEPlssiLW = false;}
      if(GlYjSGJRCW == true){GlYjSGJRCW = false;}
      if(QTnqbVLwgw == true){QTnqbVLwgw = false;}
      if(ZwyjkRPCXQ == true){ZwyjkRPCXQ = false;}
      if(zYZqLZEjbw == true){zYZqLZEjbw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SXHKQDGMZR
{ 
  void tSHgxHAkuA()
  { 
      bool UiyMhMTJea = false;
      bool BgeeHZERnk = false;
      bool FswZOaRUmJ = false;
      bool SshWJCOiOk = false;
      bool nIrBVRCxna = false;
      bool OWAdrblXxG = false;
      bool uyWUHHzIUE = false;
      bool LVDDwxAuEw = false;
      bool XUgLuwsDdh = false;
      bool QpkHpplWsN = false;
      bool RsbiPrTwhu = false;
      bool bpSAiZQKZL = false;
      bool NwemnUkuNF = false;
      bool LcBqeerxwC = false;
      bool bwViFZWkYP = false;
      bool ZaxhzVOnuu = false;
      bool HXibjynbVE = false;
      bool hSOXiQawgN = false;
      bool xzWyfjfTqI = false;
      bool PDCAuENsyH = false;
      string PDuiLqecBn;
      string mpOxGPOSXf;
      string BhZIcCXjyn;
      string BZKNsKdGcB;
      string jTopFamwWX;
      string DLWoSgdlGI;
      string TteNlMfBDw;
      string kIpVugriCC;
      string PbNajoDUtL;
      string fqzThoobEr;
      string ukraluVBsk;
      string oujEsqgEcw;
      string JKGrQsIVmG;
      string rQeKHdimnn;
      string TCbJWkHuaq;
      string HjyHhjeAKr;
      string mANmsXPYxO;
      string ItQncHixUe;
      string kMuwyHSWbW;
      string zhcuBTnoPy;
      if(PDuiLqecBn == ukraluVBsk){UiyMhMTJea = true;}
      else if(ukraluVBsk == PDuiLqecBn){RsbiPrTwhu = true;}
      if(mpOxGPOSXf == oujEsqgEcw){BgeeHZERnk = true;}
      else if(oujEsqgEcw == mpOxGPOSXf){bpSAiZQKZL = true;}
      if(BhZIcCXjyn == JKGrQsIVmG){FswZOaRUmJ = true;}
      else if(JKGrQsIVmG == BhZIcCXjyn){NwemnUkuNF = true;}
      if(BZKNsKdGcB == rQeKHdimnn){SshWJCOiOk = true;}
      else if(rQeKHdimnn == BZKNsKdGcB){LcBqeerxwC = true;}
      if(jTopFamwWX == TCbJWkHuaq){nIrBVRCxna = true;}
      else if(TCbJWkHuaq == jTopFamwWX){bwViFZWkYP = true;}
      if(DLWoSgdlGI == HjyHhjeAKr){OWAdrblXxG = true;}
      else if(HjyHhjeAKr == DLWoSgdlGI){ZaxhzVOnuu = true;}
      if(TteNlMfBDw == mANmsXPYxO){uyWUHHzIUE = true;}
      else if(mANmsXPYxO == TteNlMfBDw){HXibjynbVE = true;}
      if(kIpVugriCC == ItQncHixUe){LVDDwxAuEw = true;}
      if(PbNajoDUtL == kMuwyHSWbW){XUgLuwsDdh = true;}
      if(fqzThoobEr == zhcuBTnoPy){QpkHpplWsN = true;}
      while(ItQncHixUe == kIpVugriCC){hSOXiQawgN = true;}
      while(kMuwyHSWbW == kMuwyHSWbW){xzWyfjfTqI = true;}
      while(zhcuBTnoPy == zhcuBTnoPy){PDCAuENsyH = true;}
      if(UiyMhMTJea == true){UiyMhMTJea = false;}
      if(BgeeHZERnk == true){BgeeHZERnk = false;}
      if(FswZOaRUmJ == true){FswZOaRUmJ = false;}
      if(SshWJCOiOk == true){SshWJCOiOk = false;}
      if(nIrBVRCxna == true){nIrBVRCxna = false;}
      if(OWAdrblXxG == true){OWAdrblXxG = false;}
      if(uyWUHHzIUE == true){uyWUHHzIUE = false;}
      if(LVDDwxAuEw == true){LVDDwxAuEw = false;}
      if(XUgLuwsDdh == true){XUgLuwsDdh = false;}
      if(QpkHpplWsN == true){QpkHpplWsN = false;}
      if(RsbiPrTwhu == true){RsbiPrTwhu = false;}
      if(bpSAiZQKZL == true){bpSAiZQKZL = false;}
      if(NwemnUkuNF == true){NwemnUkuNF = false;}
      if(LcBqeerxwC == true){LcBqeerxwC = false;}
      if(bwViFZWkYP == true){bwViFZWkYP = false;}
      if(ZaxhzVOnuu == true){ZaxhzVOnuu = false;}
      if(HXibjynbVE == true){HXibjynbVE = false;}
      if(hSOXiQawgN == true){hSOXiQawgN = false;}
      if(xzWyfjfTqI == true){xzWyfjfTqI = false;}
      if(PDCAuENsyH == true){PDCAuENsyH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTXXOLRPOR
{ 
  void iKPBoMxOoD()
  { 
      bool OHGNGENCKL = false;
      bool kAGLHslmLa = false;
      bool iiWsLTAAus = false;
      bool bQXFXZwZZm = false;
      bool uajcSwGiSO = false;
      bool LwYGpfjMBm = false;
      bool EMGRjUcBmg = false;
      bool wLMYeHztZP = false;
      bool MQhfgeqQOq = false;
      bool ojYmhiURry = false;
      bool TEwkRAjAbi = false;
      bool gpllZmeZjF = false;
      bool cMmuqMlZpu = false;
      bool mgCbuHUwOg = false;
      bool uqnfKzxlMu = false;
      bool EthlUHRAsF = false;
      bool NJJfwAnJpR = false;
      bool ShLCKlXGkr = false;
      bool PAMuqryPHn = false;
      bool oTCITkgHjK = false;
      string ggJZSfIhlz;
      string VbebAFGLob;
      string BkumQdzxmR;
      string eRGIdCMDVA;
      string yYjjpxyyah;
      string HYaYJwkVIo;
      string gKuTUEVVxx;
      string rCpndbALxS;
      string eAWEKGphzh;
      string RqtfTmdQPk;
      string acBdpEimtg;
      string wYXpKfnpJN;
      string NnWPeAHJTq;
      string xjwLqCzsOF;
      string WCmRkrSEVm;
      string znGBWmFkyo;
      string wZSDjMcLyI;
      string guaEqLBFdm;
      string hDnfqJctoE;
      string wNtZIxijhY;
      if(ggJZSfIhlz == acBdpEimtg){OHGNGENCKL = true;}
      else if(acBdpEimtg == ggJZSfIhlz){TEwkRAjAbi = true;}
      if(VbebAFGLob == wYXpKfnpJN){kAGLHslmLa = true;}
      else if(wYXpKfnpJN == VbebAFGLob){gpllZmeZjF = true;}
      if(BkumQdzxmR == NnWPeAHJTq){iiWsLTAAus = true;}
      else if(NnWPeAHJTq == BkumQdzxmR){cMmuqMlZpu = true;}
      if(eRGIdCMDVA == xjwLqCzsOF){bQXFXZwZZm = true;}
      else if(xjwLqCzsOF == eRGIdCMDVA){mgCbuHUwOg = true;}
      if(yYjjpxyyah == WCmRkrSEVm){uajcSwGiSO = true;}
      else if(WCmRkrSEVm == yYjjpxyyah){uqnfKzxlMu = true;}
      if(HYaYJwkVIo == znGBWmFkyo){LwYGpfjMBm = true;}
      else if(znGBWmFkyo == HYaYJwkVIo){EthlUHRAsF = true;}
      if(gKuTUEVVxx == wZSDjMcLyI){EMGRjUcBmg = true;}
      else if(wZSDjMcLyI == gKuTUEVVxx){NJJfwAnJpR = true;}
      if(rCpndbALxS == guaEqLBFdm){wLMYeHztZP = true;}
      if(eAWEKGphzh == hDnfqJctoE){MQhfgeqQOq = true;}
      if(RqtfTmdQPk == wNtZIxijhY){ojYmhiURry = true;}
      while(guaEqLBFdm == rCpndbALxS){ShLCKlXGkr = true;}
      while(hDnfqJctoE == hDnfqJctoE){PAMuqryPHn = true;}
      while(wNtZIxijhY == wNtZIxijhY){oTCITkgHjK = true;}
      if(OHGNGENCKL == true){OHGNGENCKL = false;}
      if(kAGLHslmLa == true){kAGLHslmLa = false;}
      if(iiWsLTAAus == true){iiWsLTAAus = false;}
      if(bQXFXZwZZm == true){bQXFXZwZZm = false;}
      if(uajcSwGiSO == true){uajcSwGiSO = false;}
      if(LwYGpfjMBm == true){LwYGpfjMBm = false;}
      if(EMGRjUcBmg == true){EMGRjUcBmg = false;}
      if(wLMYeHztZP == true){wLMYeHztZP = false;}
      if(MQhfgeqQOq == true){MQhfgeqQOq = false;}
      if(ojYmhiURry == true){ojYmhiURry = false;}
      if(TEwkRAjAbi == true){TEwkRAjAbi = false;}
      if(gpllZmeZjF == true){gpllZmeZjF = false;}
      if(cMmuqMlZpu == true){cMmuqMlZpu = false;}
      if(mgCbuHUwOg == true){mgCbuHUwOg = false;}
      if(uqnfKzxlMu == true){uqnfKzxlMu = false;}
      if(EthlUHRAsF == true){EthlUHRAsF = false;}
      if(NJJfwAnJpR == true){NJJfwAnJpR = false;}
      if(ShLCKlXGkr == true){ShLCKlXGkr = false;}
      if(PAMuqryPHn == true){PAMuqryPHn = false;}
      if(oTCITkgHjK == true){oTCITkgHjK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBIUBGHWQR
{ 
  void ZyHoFZWzwG()
  { 
      bool gdlrjJCUWa = false;
      bool iylEHVGUem = false;
      bool ckOWmTbCKZ = false;
      bool ZsGfUcXOuy = false;
      bool eYRMIJSQAb = false;
      bool AURjAuOOEQ = false;
      bool gAKwAoqFje = false;
      bool yrYgIDTBOc = false;
      bool BLBhZFbWfY = false;
      bool NIJeQdOUMS = false;
      bool SMfUdIukaw = false;
      bool bMAbOVybWt = false;
      bool NUYKQphtPe = false;
      bool nyouKnegEQ = false;
      bool JpuixBHhPt = false;
      bool emyRFynVEn = false;
      bool ZAUwHcWEQZ = false;
      bool qRXFkWYoNO = false;
      bool hAdVzBAWpL = false;
      bool AJbQqIUzbT = false;
      string rKZPnDqZCo;
      string jgsnXYMHkd;
      string iIqPVTWgXw;
      string GuYMfrXXpN;
      string nuUpmGhOsB;
      string daNpDiSJsT;
      string fKCFhoHgHf;
      string AnRWpmnAcO;
      string lHmWSeghIw;
      string YNeVhcsPHy;
      string yAHMAoJpzP;
      string uSgdgYWflD;
      string HYXLHlJuoN;
      string tXsdQkAaVd;
      string VqisBGfAnI;
      string FMdEpYcwFN;
      string eNBlUXZCNw;
      string XwJIhPpeJB;
      string GJHfHgtnmq;
      string IEUHyHpwXc;
      if(rKZPnDqZCo == yAHMAoJpzP){gdlrjJCUWa = true;}
      else if(yAHMAoJpzP == rKZPnDqZCo){SMfUdIukaw = true;}
      if(jgsnXYMHkd == uSgdgYWflD){iylEHVGUem = true;}
      else if(uSgdgYWflD == jgsnXYMHkd){bMAbOVybWt = true;}
      if(iIqPVTWgXw == HYXLHlJuoN){ckOWmTbCKZ = true;}
      else if(HYXLHlJuoN == iIqPVTWgXw){NUYKQphtPe = true;}
      if(GuYMfrXXpN == tXsdQkAaVd){ZsGfUcXOuy = true;}
      else if(tXsdQkAaVd == GuYMfrXXpN){nyouKnegEQ = true;}
      if(nuUpmGhOsB == VqisBGfAnI){eYRMIJSQAb = true;}
      else if(VqisBGfAnI == nuUpmGhOsB){JpuixBHhPt = true;}
      if(daNpDiSJsT == FMdEpYcwFN){AURjAuOOEQ = true;}
      else if(FMdEpYcwFN == daNpDiSJsT){emyRFynVEn = true;}
      if(fKCFhoHgHf == eNBlUXZCNw){gAKwAoqFje = true;}
      else if(eNBlUXZCNw == fKCFhoHgHf){ZAUwHcWEQZ = true;}
      if(AnRWpmnAcO == XwJIhPpeJB){yrYgIDTBOc = true;}
      if(lHmWSeghIw == GJHfHgtnmq){BLBhZFbWfY = true;}
      if(YNeVhcsPHy == IEUHyHpwXc){NIJeQdOUMS = true;}
      while(XwJIhPpeJB == AnRWpmnAcO){qRXFkWYoNO = true;}
      while(GJHfHgtnmq == GJHfHgtnmq){hAdVzBAWpL = true;}
      while(IEUHyHpwXc == IEUHyHpwXc){AJbQqIUzbT = true;}
      if(gdlrjJCUWa == true){gdlrjJCUWa = false;}
      if(iylEHVGUem == true){iylEHVGUem = false;}
      if(ckOWmTbCKZ == true){ckOWmTbCKZ = false;}
      if(ZsGfUcXOuy == true){ZsGfUcXOuy = false;}
      if(eYRMIJSQAb == true){eYRMIJSQAb = false;}
      if(AURjAuOOEQ == true){AURjAuOOEQ = false;}
      if(gAKwAoqFje == true){gAKwAoqFje = false;}
      if(yrYgIDTBOc == true){yrYgIDTBOc = false;}
      if(BLBhZFbWfY == true){BLBhZFbWfY = false;}
      if(NIJeQdOUMS == true){NIJeQdOUMS = false;}
      if(SMfUdIukaw == true){SMfUdIukaw = false;}
      if(bMAbOVybWt == true){bMAbOVybWt = false;}
      if(NUYKQphtPe == true){NUYKQphtPe = false;}
      if(nyouKnegEQ == true){nyouKnegEQ = false;}
      if(JpuixBHhPt == true){JpuixBHhPt = false;}
      if(emyRFynVEn == true){emyRFynVEn = false;}
      if(ZAUwHcWEQZ == true){ZAUwHcWEQZ = false;}
      if(qRXFkWYoNO == true){qRXFkWYoNO = false;}
      if(hAdVzBAWpL == true){hAdVzBAWpL = false;}
      if(AJbQqIUzbT == true){AJbQqIUzbT = false;}
    } 
}; 
