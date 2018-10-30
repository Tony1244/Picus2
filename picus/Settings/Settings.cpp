#include "Settings.h"

//[enc_string_enable /]
//[junk_enable /]

using namespace Client;

namespace Settings
{
	void LoadSettings(string szIniFile)
	{
		CSX::Cvar::InitPath(szIniFile.c_str());
		Aimbot::aim_Backtrack = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK, Aimbot::aim_Backtrack) != false;
		Aimbot::aim_Backtracktickrate = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK_TICK, Aimbot::aim_Backtracktickrate);
		Aimbot::aim_Deathmatch = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DEATHMATCH, Aimbot::aim_Deathmatch);
		Aimbot::aim_WallAttack = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_WALLATTACK, Aimbot::aim_WallAttack);
		Aimbot::aim_CheckSmoke = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_CHECKSMOKE, Aimbot::aim_CheckSmoke);
		Aimbot::aim_AntiJump = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_ANTIJUMP, Aimbot::aim_AntiJump);
		Aimbot::aim_RcsType = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_RCSTYPE, Aimbot::aim_RcsType);
		Aimbot::aim_DrawFov = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWFOV, Aimbot::aim_DrawFov);
		Aimbot::aim_DrawSpot = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWSPOT, Aimbot::aim_DrawSpot);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			// ���������
			if (i <= 9)
			{
				Aimbot::weapon_aim_settings[i].aim_Active = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, 0);
				Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, 50);
				Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOV, 35);
				Aimbot::weapon_aim_settings[i].aim_FovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, 1);
				Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, 0);
				Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, 5);
				Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, 0);
				Aimbot::weapon_aim_settings[i].aim_Rcs = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCS, 50);
				Aimbot::weapon_aim_settings[i].aim_AutoPistol = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_AUTOPISTOL, 0);
			}

			// ��������
			if (i >= 10 && i <= 30)
			{
				Aimbot::weapon_aim_settings[i].aim_Active = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, 0);
				Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, 50);
				Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOV, 35);
				Aimbot::weapon_aim_settings[i].aim_FovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, 1);
				Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, 0);
				Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, 5);
				Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, 0);
				Aimbot::weapon_aim_settings[i].aim_Rcs = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCS, 50);
				Aimbot::weapon_aim_settings[i].aim_RcsFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, 50);
				Aimbot::weapon_aim_settings[i].aim_RcsSmooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, 50);
				Aimbot::weapon_aim_settings[i].aim_RcsClampType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, 0);
			}

			// ���������
			if (i >= 31 && i <= 32)
			{
				Aimbot::weapon_aim_settings[i].aim_Active = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, 0);
				Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, 50);
				Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOV, 35);
				Aimbot::weapon_aim_settings[i].aim_FovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, 1);
				Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, 0);
				Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, 5);
				Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, 0);
				Aimbot::weapon_aim_settings[i].aim_Rcs = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCS, 50);
			}
		}

		Triggerbot::trigger_Enable = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_ENABLE, Triggerbot::trigger_Enable);
		Triggerbot::trigger_Deathmatch = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_DEATHMATCH, Triggerbot::trigger_Deathmatch) != false;
		Triggerbot::trigger_WallAttack = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_WALLATTACK, Triggerbot::trigger_WallAttack) != false;
		Triggerbot::trigger_FastZoom = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_FASTZOOM, Triggerbot::trigger_FastZoom) != false;
		Triggerbot::trigger_Key = TriggerCharToKey(CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_KEY, CVAR_KEY_MOUSE3).c_str());
		Triggerbot::trigger_KeyMode = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_KEYMODE, Triggerbot::trigger_KeyMode);
		Triggerbot::trigger_SmokCheck = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_SMOKCHECK, Triggerbot::trigger_SmokCheck) != false;
		Triggerbot::trigger_DrawFov = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWFOV, Triggerbot::trigger_DrawFov) != false;
		Triggerbot::trigger_DrawSpot = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWSPOT, Triggerbot::trigger_DrawSpot) != false;
		Triggerbot::trigger_DrawFovAssist = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWFOVASSIST, Triggerbot::trigger_DrawFovAssist) != false;

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			Triggerbot::weapon_trigger_settings[i].trigger_DistanceMin = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_DISTANCEMIN, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_DistanceMax = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_DISTANCEMAX, 5000);
			Triggerbot::weapon_trigger_settings[i].trigger_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_FOV, 10);
			Triggerbot::weapon_trigger_settings[i].trigger_DelayBefore = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_DELAYBEFORE, 10);
			Triggerbot::weapon_trigger_settings[i].trigger_DelayAfter = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_DELAYAFTER, 100);
			Triggerbot::weapon_trigger_settings[i].trigger_HeadOnly = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_HEADONLY, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_HitGroup = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_HITGROUP, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_Assist = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSIST, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_AssistRcs = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTRCS, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_AssistFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTFOV, 20);
			Triggerbot::weapon_trigger_settings[i].trigger_AssistFovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTFOVTYPE, 1);
			Triggerbot::weapon_trigger_settings[i].trigger_AssistSmooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTSMOOTH, 5);
		}

		Esp::esp_Style = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_STYLE, Esp::esp_Style);
		Esp::esp_Size = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_SIZE, Esp::esp_Size);
		Esp::esp_CapitalToggle = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CAPITALTOGGLE, Esp::esp_CapitalToggle);
		Esp::esp_Line = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_LINE, Esp::esp_Line) != false;
		Esp::esp_Outline = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_OUTLINE, Esp::esp_Outline) != false;

		Esp::esp_Name = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_NAME, Esp::esp_Name) != false;
		Esp::esp_Time = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_TIME, Esp::esp_Time) != false;
		Esp::esp_Watermark = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WATER, Esp::esp_Watermark) != false;
		Esp::esp_Cheatbuild = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CHEATBUILD, Esp::esp_Cheatbuild) != false;
		Esp::esp_HitMarker = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_HITMARKER_ENABLED, Esp::esp_HitMarker) != false;
		Esp::esp_HitMarkerSound = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_HITMARKER_COMBO, Esp::esp_HitMarkerSound) != false;
		Esp::esp_Rank = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_RANK, Esp::esp_Rank) != false;
		Esp::esp_Health = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_HEALTH, Esp::esp_Health);
		Esp::esp_Armor = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_ARMOR, Esp::esp_Armor);
		Esp::esp_Weapon = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WEAPON, Esp::esp_Weapon) != false;
		Esp::esp_Ammo = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_AMMO, Esp::esp_Ammo) != false;
		Esp::esp_Distance = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_DISTANCE, Esp::esp_Distance) != false;
		Esp::esp_Sound = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_SOUND, Esp::esp_Sound) != false;
		Esp::esp_GrenadePrediction = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_GRENADEPREDICTION, Esp::esp_GrenadePrediction) != false;
		Esp::esp_Statusx = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_INFO, Esp::esp_Statusx) != false;

		Esp::esp_Skeleton = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_SKELETON, Esp::esp_Skeleton) != false;
		Esp::esp_BulletTrace = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BULLETTRACE, Esp::esp_BulletTrace);
		Esp::esp_Team = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_TEAM, Esp::esp_Team) != false;
		Esp::esp_Enemy = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_ENEMY, Esp::esp_Enemy) != false;
		Esp::esp_Visible = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_VISIBLE, Esp::esp_Visible);
		Esp::esp_ChamsVisible = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CHAMSVISIBLE, Esp::esp_ChamsVisible);

		Esp::esp_Chams = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CHAMS, Esp::esp_Chams);
		Esp::esp_Bomb = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BOMB, Esp::esp_Bomb) != false;
		Esp::esp_BombTimer = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BOMBTIMER, Esp::esp_BombTimer);
		Esp::esp_WorldWeapons = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WORLDWEAPONS, Esp::esp_WorldWeapons) != false;
		Esp::esp_WorldGrenade = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WORLDGRENADE, Esp::esp_WorldGrenade) != false;
		Esp::esp_HealthChams = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_HEALTH_CHAMS, Esp::esp_Chams) != false;

		string esp_Color_CT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_CT, "0,164,255");
		string esp_Color_TT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_TT, "255,64,64");
		string esp_Color_VCT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VCT, "124,252,0");
		string esp_Color_VTT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VTT, "124,252,0");
		
		CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WALLSOPACITY, Settings::Esp::esp_WallsOpacity);

		string chams_Color_CT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_CT, "0,164,255");
		string chams_Color_TT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_TT, "255,64,64");
		string chams_Color_VCT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VCT, "124,252,0");
		string chams_Color_VTT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VTT, "124,252,0");

		string Color_HITMARKER = CSX::Cvar::LoadCvar(VISUAL_TEXT, "esp_HitMarkerColor", "255,0,0");
		string GrenadeHelper = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_GrenadeHelper, "255,0,0");

		ScanColorFromCvar(Color_HITMARKER.c_str(), Esp::esp_HitMarkerColor);
		ScanColorFromCvar(GrenadeHelper.c_str(), Settings::Esp::GrenadeHelper);


		ScanColorFromCvar(esp_Color_CT.c_str(), Settings::Esp::esp_Color_CT);
		ScanColorFromCvar(esp_Color_TT.c_str(), Settings::Esp::esp_Color_TT);
		ScanColorFromCvar(esp_Color_VCT.c_str(), Settings::Esp::esp_Color_VCT);
		ScanColorFromCvar(esp_Color_VTT.c_str(), Settings::Esp::esp_Color_VTT);

		ScanColorFromCvar(chams_Color_CT.c_str(), Settings::Esp::chams_Color_CT);
		ScanColorFromCvar(chams_Color_TT.c_str(), Settings::Esp::chams_Color_TT);
		ScanColorFromCvar(chams_Color_VCT.c_str(), Settings::Esp::chams_Color_VCT);
		ScanColorFromCvar(chams_Color_VTT.c_str(), Settings::Esp::chams_Color_VTT);

		Skin::knf_ct_model = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_CT_MODEL, Skin::knf_ct_model);
		Skin::knf_ct_skin = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_CT_SKIN, Skin::knf_ct_skin);
		Skin::knf_tt_model = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_TT_MODEL, Skin::knf_tt_model);
		Skin::knf_tt_skin = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_TT_SKIN, Skin::knf_tt_skin);
		Skin::gloves_skin = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_GLOVES, Skin::gloves_skin);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackPaintKit = CSX::Cvar::LoadCvar(SKIN_TEXT, pWeaponData[i], 0);
		}

		g_SkinChangerCfg[WEAPON_KNIFE].iEntityQuality = CSX::Cvar::LoadCvar(SKIN_TEXT_QUALITY, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].iEntityQuality);
		g_SkinChangerCfg[WEAPON_KNIFE_T].iEntityQuality = CSX::Cvar::LoadCvar(SKIN_TEXT_QUALITY, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].iEntityQuality);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].iEntityQuality = CSX::Cvar::LoadCvar(SKIN_TEXT_QUALITY, pWeaponData[i], 0);
		}

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackStatTrak = CSX::Cvar::LoadCvar(SKIN_TEXT_STAT, pWeaponData[i], -1);
		}


		g_SkinChangerCfg[WEAPON_KNIFE].flFallbackWear = CSX::Cvar::LoadCvar(SKIN_TEXT_WEAR, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].flFallbackWear);
		g_SkinChangerCfg[WEAPON_KNIFE_T].flFallbackWear = CSX::Cvar::LoadCvar(SKIN_TEXT_WEAR, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].flFallbackWear);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].flFallbackWear = CSX::Cvar::LoadCvar(SKIN_TEXT_WEAR, pWeaponData[i], 0.000001f);
		}

		g_SkinChangerCfg[WEAPON_KNIFE].nFallbackSeed = CSX::Cvar::LoadCvar(SKIN_TEXT_SEED, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].nFallbackSeed);
		g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackSeed = CSX::Cvar::LoadCvar(SKIN_TEXT_SEED, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackSeed);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackSeed = CSX::Cvar::LoadCvar(SKIN_TEXT_SEED, pWeaponData[i], 0);
		}

		if (Interfaces::Engine()->IsConnected())
			ForceFullUpdate();

		Misc::misc_SkinChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_SKIN_CHANGER, Misc::misc_SkinChanger) != false;
		Misc::misc_KnifeChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_KNIFE_CHANGER, Misc::misc_KnifeChanger) != false;
		Misc::misc_StickerChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_STICKER_CHANGER, Misc::misc_StickerChanger) != false;
		Misc::misc_EPostprocess = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_EPOSTPROCESS, Misc::misc_EPostprocess) != false;
		Misc::misc_GrenadeTrajectory = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_GRENADETRAJECTORY, Misc::misc_GrenadeTrajectory) != false;
		Misc::misc_Bhop = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_BHOP, Misc::misc_Bhop) != false;
		Misc::misc_Punch = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_PUNCH, Misc::misc_Punch) != false;
		Misc::misc_AwpAim = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AWPAIM, Misc::misc_AwpAim) != false;
		Misc::misc_NoFlash = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_NOFLASH, Misc::misc_NoFlash) != false;
		Misc::misc_NoSmoke = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_NOSMOKE, Misc::misc_NoSmoke) != false;
		Misc::misc_NoFlash = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_WIREFRAMESMOKE, Misc::misc_wireframesmoke) != false;
		Misc::misc_WireHands = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_WIREHANDS, Misc::misc_WireHands) != false;
		Misc::misc_NoHands = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_NOHANDS, Misc::misc_NoHands) != false;
		Misc::misc_AutoStrafe = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AUTOSTRAFE, Misc::misc_AutoStrafe) != false;
		//Misc::misc_LegitAAToggle = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_LEGITAATOGGLE, Misc::misc_LegitAAToggle);
		Misc::misc_AutoAccept = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AUTOACCEPT, Misc::misc_AutoAccept) != false;
		Misc::misc_Spectators = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_SPECTATORS, Misc::misc_Spectators) != false;
		Misc::misc_FovChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_FOV_CHANGER, Misc::misc_FovChanger) != false;
		Misc::misc_FovView = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_FOV_VIEW, Misc::misc_FovView);
		Misc::misc_FovModelView = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_FOV_MDL_VIEW, Misc::misc_FovModelView);
		Misc::invalwayson = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_INVALWAYSON, Misc::invalwayson);

		string Color_MENU = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_MENU_COLOR, "0,0,0");

		ScanColorFromCvar(Color_MENU.c_str(), Misc::misc_MenuColor);

		string Color_TEXT = CSX::Cvar::LoadCvar(MISC_TEXT, "misc_TextColor", "255,255,255");

		ScanColorFromCvar(Color_TEXT.c_str(), Misc::misc_TextColor);

		/*
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_DEAGLE, Sticker::stickerSafeWeapon);
		Sticker::sticker_deserteagle_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE1, Sticker::sticker_deserteagle_iSlot[0]);
		Sticker::sticker_deserteagle_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE1, Sticker::sticker_deserteagle_size[0]);
		Sticker::sticker_deserteagle_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE1, Sticker::sticker_deserteagle_id[0]);
		Sticker::sticker_deserteagle_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE1, Sticker::sticker_deserteagle_wear[0]);
		Sticker::sticker_deserteagle_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE1, Sticker::sticker_deserteagle_rotate[0]);
		Sticker::sticker_deserteagle_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE2, Sticker::sticker_deserteagle_iSlot[1]);
		Sticker::sticker_deserteagle_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE2, Sticker::sticker_deserteagle_size[1]);
		Sticker::sticker_deserteagle_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE2, Sticker::sticker_deserteagle_id[1]);
		Sticker::sticker_deserteagle_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE2, Sticker::sticker_deserteagle_wear[1]);
		Sticker::sticker_deserteagle_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE2, Sticker::sticker_deserteagle_rotate[1]);
		Sticker::sticker_deserteagle_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE3, Sticker::sticker_deserteagle_iSlot[2]);
		Sticker::sticker_deserteagle_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE3, Sticker::sticker_deserteagle_size[2]);
		Sticker::sticker_deserteagle_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE3, Sticker::sticker_deserteagle_id[2]);
		Sticker::sticker_deserteagle_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE3, Sticker::sticker_deserteagle_wear[2]);
		Sticker::sticker_deserteagle_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE3, Sticker::sticker_deserteagle_rotate[2]);
		Sticker::sticker_deserteagle_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE4, Sticker::sticker_deserteagle_iSlot[3]);
		Sticker::sticker_deserteagle_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE4, Sticker::sticker_deserteagle_size[3]);
		Sticker::sticker_deserteagle_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE4, Sticker::sticker_deserteagle_id[3]);
		Sticker::sticker_deserteagle_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE4, Sticker::sticker_deserteagle_wear[3]);
		Sticker::sticker_deserteagle_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE4, Sticker::sticker_deserteagle_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[0]].flWear = Sticker::sticker_deserteagle_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[0]].flScale = Sticker::sticker_deserteagle_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[0]].iRotation = Sticker::sticker_deserteagle_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[0]].iID = Sticker::sticker_deserteagle_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[1]].flWear = Sticker::sticker_deserteagle_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[1]].flScale = Sticker::sticker_deserteagle_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[1]].iRotation = Sticker::sticker_deserteagle_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[1]].iID = Sticker::sticker_deserteagle_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[2]].flWear = Sticker::sticker_deserteagle_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[2]].flScale = Sticker::sticker_deserteagle_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[2]].iRotation = Sticker::sticker_deserteagle_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[2]].iID = Sticker::sticker_deserteagle_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[3]].flWear = Sticker::sticker_deserteagle_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[3]].flScale = Sticker::sticker_deserteagle_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[3]].iRotation = Sticker::sticker_deserteagle_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[3]].iID = Sticker::sticker_deserteagle_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_ELITES, Sticker::stickerSafeWeapon);
		Sticker::sticker_elites_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES1, Sticker::sticker_elites_iSlot[0]);
		Sticker::sticker_elites_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES1, Sticker::sticker_elites_size[0]);
		Sticker::sticker_elites_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES1, Sticker::sticker_elites_id[0]);
		Sticker::sticker_elites_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES1, Sticker::sticker_elites_wear[0]);
		Sticker::sticker_elites_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES1, Sticker::sticker_elites_rotate[0]);
		Sticker::sticker_elites_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES2, Sticker::sticker_elites_iSlot[1]);
		Sticker::sticker_elites_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES2, Sticker::sticker_elites_size[1]);
		Sticker::sticker_elites_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES2, Sticker::sticker_elites_id[1]);
		Sticker::sticker_elites_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES2, Sticker::sticker_elites_wear[1]);
		Sticker::sticker_elites_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES2, Sticker::sticker_elites_rotate[1]);
		Sticker::sticker_elites_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES3, Sticker::sticker_elites_iSlot[2]);
		Sticker::sticker_elites_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES3, Sticker::sticker_elites_size[2]);
		Sticker::sticker_elites_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES3, Sticker::sticker_elites_id[2]);
		Sticker::sticker_elites_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES3, Sticker::sticker_elites_wear[2]);
		Sticker::sticker_elites_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES3, Sticker::sticker_elites_rotate[2]);
		Sticker::sticker_elites_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES4, Sticker::sticker_elites_iSlot[3]);
		Sticker::sticker_elites_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES4, Sticker::sticker_elites_size[3]);
		Sticker::sticker_elites_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES4, Sticker::sticker_elites_id[3]);
		Sticker::sticker_elites_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES4, Sticker::sticker_elites_wear[3]);
		Sticker::sticker_elites_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES4, Sticker::sticker_elites_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[0]].flWear = Sticker::sticker_elites_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[0]].flScale = Sticker::sticker_elites_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[0]].iRotation = Sticker::sticker_elites_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[0]].iID = Sticker::sticker_elites_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[1]].flWear = Sticker::sticker_elites_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[1]].flScale = Sticker::sticker_elites_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[1]].iRotation = Sticker::sticker_elites_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[1]].iID = Sticker::sticker_elites_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[2]].flWear = Sticker::sticker_elites_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[2]].flScale = Sticker::sticker_elites_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[2]].iRotation = Sticker::sticker_elites_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[2]].iID = Sticker::sticker_elites_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[3]].flWear = Sticker::sticker_elites_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[3]].flScale = Sticker::sticker_elites_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[3]].iRotation = Sticker::sticker_elites_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[3]].iID = Sticker::sticker_elites_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_FIVESEVEN, Sticker::stickerSafeWeapon);
		Sticker::sticker_fiveseven_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN1, Sticker::sticker_fiveseven_iSlot[0]);
		Sticker::sticker_fiveseven_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN1, Sticker::sticker_fiveseven_size[0]);
		Sticker::sticker_fiveseven_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN1, Sticker::sticker_fiveseven_id[0]);
		Sticker::sticker_fiveseven_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN1, Sticker::sticker_fiveseven_wear[0]);
		Sticker::sticker_fiveseven_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN1, Sticker::sticker_fiveseven_rotate[0]);
		Sticker::sticker_fiveseven_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN2, Sticker::sticker_fiveseven_iSlot[1]);
		Sticker::sticker_fiveseven_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN2, Sticker::sticker_fiveseven_size[1]);
		Sticker::sticker_fiveseven_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN2, Sticker::sticker_fiveseven_id[1]);
		Sticker::sticker_fiveseven_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN2, Sticker::sticker_fiveseven_wear[1]);
		Sticker::sticker_fiveseven_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN2, Sticker::sticker_fiveseven_rotate[1]);
		Sticker::sticker_fiveseven_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN3, Sticker::sticker_fiveseven_iSlot[2]);
		Sticker::sticker_fiveseven_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN3, Sticker::sticker_fiveseven_size[2]);
		Sticker::sticker_fiveseven_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN3, Sticker::sticker_fiveseven_id[2]);
		Sticker::sticker_fiveseven_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN3, Sticker::sticker_fiveseven_wear[2]);
		Sticker::sticker_fiveseven_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN3, Sticker::sticker_fiveseven_rotate[2]);
		Sticker::sticker_fiveseven_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN4, Sticker::sticker_fiveseven_iSlot[3]);
		Sticker::sticker_fiveseven_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN4, Sticker::sticker_fiveseven_size[3]);
		Sticker::sticker_fiveseven_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN4, Sticker::sticker_fiveseven_id[3]);
		Sticker::sticker_fiveseven_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN4, Sticker::sticker_fiveseven_wear[3]);
		Sticker::sticker_fiveseven_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN4, Sticker::sticker_fiveseven_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[0]].flWear = Sticker::sticker_fiveseven_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[0]].flScale = Sticker::sticker_fiveseven_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[0]].iRotation = Sticker::sticker_fiveseven_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[0]].iID = Sticker::sticker_fiveseven_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[1]].flWear = Sticker::sticker_fiveseven_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[1]].flScale = Sticker::sticker_fiveseven_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[1]].iRotation = Sticker::sticker_fiveseven_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[1]].iID = Sticker::sticker_fiveseven_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[2]].flWear = Sticker::sticker_fiveseven_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[2]].flScale = Sticker::sticker_fiveseven_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[2]].iRotation = Sticker::sticker_fiveseven_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[2]].iID = Sticker::sticker_fiveseven_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[3]].flWear = Sticker::sticker_fiveseven_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[3]].flScale = Sticker::sticker_fiveseven_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[3]].iRotation = Sticker::sticker_fiveseven_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[3]].iID = Sticker::sticker_fiveseven_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_GLOCK, Sticker::stickerSafeWeapon);
		Sticker::sticker_glock_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK1, Sticker::sticker_glock_iSlot[0]);
		Sticker::sticker_glock_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK1, Sticker::sticker_glock_size[0]);
		Sticker::sticker_glock_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK1, Sticker::sticker_glock_id[0]);
		Sticker::sticker_glock_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK1, Sticker::sticker_glock_wear[0]);
		Sticker::sticker_glock_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK1, Sticker::sticker_glock_rotate[0]);
		Sticker::sticker_glock_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK2, Sticker::sticker_glock_iSlot[1]);
		Sticker::sticker_glock_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK2, Sticker::sticker_glock_size[1]);
		Sticker::sticker_glock_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK2, Sticker::sticker_glock_id[1]);
		Sticker::sticker_glock_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK2, Sticker::sticker_glock_wear[1]);
		Sticker::sticker_glock_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK2, Sticker::sticker_glock_rotate[1]);
		Sticker::sticker_glock_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK3, Sticker::sticker_glock_iSlot[2]);
		Sticker::sticker_glock_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK3, Sticker::sticker_glock_size[2]);
		Sticker::sticker_glock_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK3, Sticker::sticker_glock_id[2]);
		Sticker::sticker_glock_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK3, Sticker::sticker_glock_wear[2]);
		Sticker::sticker_glock_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK3, Sticker::sticker_glock_rotate[2]);
		Sticker::sticker_glock_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK4, Sticker::sticker_glock_iSlot[3]);
		Sticker::sticker_glock_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK4, Sticker::sticker_glock_size[3]);
		Sticker::sticker_glock_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK4, Sticker::sticker_glock_id[3]);
		Sticker::sticker_glock_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK4, Sticker::sticker_glock_wear[3]);
		Sticker::sticker_glock_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK4, Sticker::sticker_glock_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[0]].flWear = Sticker::sticker_glock_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[0]].flScale = Sticker::sticker_glock_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[0]].iRotation = Sticker::sticker_glock_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[0]].iID = Sticker::sticker_glock_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[1]].flWear = Sticker::sticker_glock_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[1]].flScale = Sticker::sticker_glock_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[1]].iRotation = Sticker::sticker_glock_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[1]].iID = Sticker::sticker_glock_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[2]].flWear = Sticker::sticker_glock_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[2]].flScale = Sticker::sticker_glock_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[2]].iRotation = Sticker::sticker_glock_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[2]].iID = Sticker::sticker_glock_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[3]].flWear = Sticker::sticker_glock_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[3]].flScale = Sticker::sticker_glock_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[3]].iRotation = Sticker::sticker_glock_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[3]].iID = Sticker::sticker_glock_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AK, Sticker::stickerSafeWeapon);
		Sticker::sticker_ak_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK1, Sticker::sticker_ak_iSlot[0]);
		Sticker::sticker_ak_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK1, Sticker::sticker_ak_size[0]);
		Sticker::sticker_ak_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK1, Sticker::sticker_ak_id[0]);
		Sticker::sticker_ak_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK1, Sticker::sticker_ak_wear[0]);
		Sticker::sticker_ak_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK1, Sticker::sticker_ak_rotate[0]);
		Sticker::sticker_ak_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK2, Sticker::sticker_ak_iSlot[1]);
		Sticker::sticker_ak_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK2, Sticker::sticker_ak_size[1]);
		Sticker::sticker_ak_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK2, Sticker::sticker_ak_id[1]);
		Sticker::sticker_ak_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK2, Sticker::sticker_ak_wear[1]);
		Sticker::sticker_ak_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK2, Sticker::sticker_ak_rotate[1]);
		Sticker::sticker_ak_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK3, Sticker::sticker_ak_iSlot[2]);
		Sticker::sticker_ak_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK3, Sticker::sticker_ak_size[2]);
		Sticker::sticker_ak_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK3, Sticker::sticker_ak_id[2]);
		Sticker::sticker_ak_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK3, Sticker::sticker_ak_wear[2]);
		Sticker::sticker_ak_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK3, Sticker::sticker_ak_rotate[2]);
		Sticker::sticker_ak_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK4, Sticker::sticker_ak_iSlot[3]);
		Sticker::sticker_ak_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK4, Sticker::sticker_ak_size[3]);
		Sticker::sticker_ak_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK4, Sticker::sticker_ak_id[3]);
		Sticker::sticker_ak_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK4, Sticker::sticker_ak_wear[3]);
		Sticker::sticker_ak_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK4, Sticker::sticker_ak_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[0]].flWear = Sticker::sticker_ak_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[0]].flScale = Sticker::sticker_ak_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[0]].iRotation = Sticker::sticker_ak_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[0]].iID = Sticker::sticker_ak_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[1]].flWear = Sticker::sticker_ak_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[1]].flScale = Sticker::sticker_ak_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[1]].iRotation = Sticker::sticker_ak_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[1]].iID = Sticker::sticker_ak_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[2]].flWear = Sticker::sticker_ak_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[2]].flScale = Sticker::sticker_ak_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[2]].iRotation = Sticker::sticker_ak_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[2]].iID = Sticker::sticker_ak_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[3]].flWear = Sticker::sticker_ak_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[3]].flScale = Sticker::sticker_ak_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[3]].iRotation = Sticker::sticker_ak_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[3]].iID = Sticker::sticker_ak_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AUG, Sticker::stickerSafeWeapon);
		Sticker::sticker_aug_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG1, Sticker::sticker_aug_iSlot[0]);
		Sticker::sticker_aug_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG1, Sticker::sticker_aug_size[0]);
		Sticker::sticker_aug_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG1, Sticker::sticker_aug_id[0]);
		Sticker::sticker_aug_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG1, Sticker::sticker_aug_wear[0]);
		Sticker::sticker_aug_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG1, Sticker::sticker_aug_rotate[0]);
		Sticker::sticker_aug_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG2, Sticker::sticker_aug_iSlot[1]);
		Sticker::sticker_aug_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG2, Sticker::sticker_aug_size[1]);
		Sticker::sticker_aug_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG2, Sticker::sticker_aug_id[1]);
		Sticker::sticker_aug_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG2, Sticker::sticker_aug_wear[1]);
		Sticker::sticker_aug_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG2, Sticker::sticker_aug_rotate[1]);
		Sticker::sticker_aug_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG3, Sticker::sticker_aug_iSlot[2]);
		Sticker::sticker_aug_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG3, Sticker::sticker_aug_size[2]);
		Sticker::sticker_aug_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG3, Sticker::sticker_aug_id[2]);
		Sticker::sticker_aug_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG3, Sticker::sticker_aug_wear[2]);
		Sticker::sticker_aug_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG3, Sticker::sticker_aug_rotate[2]);
		Sticker::sticker_aug_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG4, Sticker::sticker_aug_iSlot[3]);
		Sticker::sticker_aug_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG4, Sticker::sticker_aug_size[3]);
		Sticker::sticker_aug_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG4, Sticker::sticker_aug_id[3]);
		Sticker::sticker_aug_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG4, Sticker::sticker_aug_wear[3]);
		Sticker::sticker_aug_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG4, Sticker::sticker_aug_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[0]].flWear = Sticker::sticker_aug_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[0]].flScale = Sticker::sticker_aug_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[0]].iRotation = Sticker::sticker_aug_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[0]].iID = Sticker::sticker_aug_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[1]].flWear = Sticker::sticker_aug_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[1]].flScale = Sticker::sticker_aug_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[1]].iRotation = Sticker::sticker_aug_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[1]].iID = Sticker::sticker_aug_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[2]].flWear = Sticker::sticker_aug_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[2]].flScale = Sticker::sticker_aug_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[2]].iRotation = Sticker::sticker_aug_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[2]].iID = Sticker::sticker_aug_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[3]].flWear = Sticker::sticker_aug_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[3]].flScale = Sticker::sticker_aug_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[3]].iRotation = Sticker::sticker_aug_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[3]].iID = Sticker::sticker_aug_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AWP, Sticker::stickerSafeWeapon);
		Sticker::sticker_awp_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP1, Sticker::sticker_awp_iSlot[0]);
		Sticker::sticker_awp_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP1, Sticker::sticker_awp_size[0]);
		Sticker::sticker_awp_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP1, Sticker::sticker_awp_id[0]);
		Sticker::sticker_awp_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP1, Sticker::sticker_awp_wear[0]);
		Sticker::sticker_awp_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP1, Sticker::sticker_awp_rotate[0]);
		Sticker::sticker_awp_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP2, Sticker::sticker_awp_iSlot[1]);
		Sticker::sticker_awp_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP2, Sticker::sticker_awp_size[1]);
		Sticker::sticker_awp_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP2, Sticker::sticker_awp_id[1]);
		Sticker::sticker_awp_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP2, Sticker::sticker_awp_wear[1]);
		Sticker::sticker_awp_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP2, Sticker::sticker_awp_rotate[1]);
		Sticker::sticker_awp_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP3, Sticker::sticker_awp_iSlot[2]);
		Sticker::sticker_awp_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP3, Sticker::sticker_awp_size[2]);
		Sticker::sticker_awp_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP3, Sticker::sticker_awp_id[2]);
		Sticker::sticker_awp_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP3, Sticker::sticker_awp_wear[2]);
		Sticker::sticker_awp_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP3, Sticker::sticker_awp_rotate[2]);
		Sticker::sticker_awp_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP4, Sticker::sticker_awp_iSlot[3]);
		Sticker::sticker_awp_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP4, Sticker::sticker_awp_size[3]);
		Sticker::sticker_awp_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP4, Sticker::sticker_awp_id[3]);
		Sticker::sticker_awp_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP4, Sticker::sticker_awp_wear[3]);
		Sticker::sticker_awp_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP4, Sticker::sticker_awp_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[0]].flWear = Sticker::sticker_awp_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[0]].flScale = Sticker::sticker_awp_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[0]].iRotation = Sticker::sticker_awp_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[0]].iID = Sticker::sticker_awp_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[1]].flWear = Sticker::sticker_awp_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[1]].flScale = Sticker::sticker_awp_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[1]].iRotation = Sticker::sticker_awp_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[1]].iID = Sticker::sticker_awp_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[2]].flWear = Sticker::sticker_awp_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[2]].flScale = Sticker::sticker_awp_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[2]].iRotation = Sticker::sticker_awp_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[2]].iID = Sticker::sticker_awp_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[3]].flWear = Sticker::sticker_awp_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[3]].flScale = Sticker::sticker_awp_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[3]].iRotation = Sticker::sticker_awp_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[3]].iID = Sticker::sticker_awp_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_FAMAS, Sticker::stickerSafeWeapon);
		Sticker::sticker_famas_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS1, Sticker::sticker_famas_iSlot[0]);
		Sticker::sticker_famas_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS1, Sticker::sticker_famas_size[0]);
		Sticker::sticker_famas_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS1, Sticker::sticker_famas_id[0]);
		Sticker::sticker_famas_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS1, Sticker::sticker_famas_wear[0]);
		Sticker::sticker_famas_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS1, Sticker::sticker_famas_rotate[0]);
		Sticker::sticker_famas_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS2, Sticker::sticker_famas_iSlot[1]);
		Sticker::sticker_famas_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS2, Sticker::sticker_famas_size[1]);
		Sticker::sticker_famas_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS2, Sticker::sticker_famas_id[1]);
		Sticker::sticker_famas_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS2, Sticker::sticker_famas_wear[1]);
		Sticker::sticker_famas_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS2, Sticker::sticker_famas_rotate[1]);
		Sticker::sticker_famas_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS3, Sticker::sticker_famas_iSlot[2]);
		Sticker::sticker_famas_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS3, Sticker::sticker_famas_size[2]);
		Sticker::sticker_famas_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS3, Sticker::sticker_famas_id[2]);
		Sticker::sticker_famas_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS3, Sticker::sticker_famas_wear[2]);
		Sticker::sticker_famas_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS3, Sticker::sticker_famas_rotate[2]);
		Sticker::sticker_famas_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS4, Sticker::sticker_famas_iSlot[3]);
		Sticker::sticker_famas_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS4, Sticker::sticker_famas_size[3]);
		Sticker::sticker_famas_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS4, Sticker::sticker_famas_id[3]);
		Sticker::sticker_famas_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS4, Sticker::sticker_famas_wear[3]);
		Sticker::sticker_famas_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS4, Sticker::sticker_famas_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[0]].flWear = Sticker::sticker_famas_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[0]].flScale = Sticker::sticker_famas_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[0]].iRotation = Sticker::sticker_famas_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[0]].iID = Sticker::sticker_famas_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[1]].flWear = Sticker::sticker_famas_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[1]].flScale = Sticker::sticker_famas_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[1]].iRotation = Sticker::sticker_famas_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[1]].iID = Sticker::sticker_famas_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[2]].flWear = Sticker::sticker_famas_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[2]].flScale = Sticker::sticker_famas_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[2]].iRotation = Sticker::sticker_famas_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[2]].iID = Sticker::sticker_famas_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[3]].flWear = Sticker::sticker_famas_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[3]].flScale = Sticker::sticker_famas_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[3]].iRotation = Sticker::sticker_famas_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[3]].iID = Sticker::sticker_famas_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_G35G1, Sticker::stickerSafeWeapon);
		Sticker::sticker_g35g1_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G11, Sticker::sticker_g35g1_iSlot[0]);
		Sticker::sticker_g35g1_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G11, Sticker::sticker_g35g1_size[0]);
		Sticker::sticker_g35g1_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G11, Sticker::sticker_g35g1_id[0]);
		Sticker::sticker_g35g1_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G11, Sticker::sticker_g35g1_wear[0]);
		Sticker::sticker_g35g1_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G11, Sticker::sticker_g35g1_rotate[0]);
		Sticker::sticker_g35g1_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G12, Sticker::sticker_g35g1_iSlot[1]);
		Sticker::sticker_g35g1_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G12, Sticker::sticker_g35g1_size[1]);
		Sticker::sticker_g35g1_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G12, Sticker::sticker_g35g1_id[1]);
		Sticker::sticker_g35g1_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G12, Sticker::sticker_g35g1_wear[1]);
		Sticker::sticker_g35g1_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G12, Sticker::sticker_g35g1_rotate[1]);
		Sticker::sticker_g35g1_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G13, Sticker::sticker_g35g1_iSlot[2]);
		Sticker::sticker_g35g1_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G13, Sticker::sticker_g35g1_size[2]);
		Sticker::sticker_g35g1_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G13, Sticker::sticker_g35g1_id[2]);
		Sticker::sticker_g35g1_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G13, Sticker::sticker_g35g1_wear[2]);
		Sticker::sticker_g35g1_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G13, Sticker::sticker_g35g1_rotate[2]);
		Sticker::sticker_g35g1_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G14, Sticker::sticker_g35g1_iSlot[3]);
		Sticker::sticker_g35g1_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G14, Sticker::sticker_g35g1_size[3]);
		Sticker::sticker_g35g1_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G14, Sticker::sticker_g35g1_id[3]);
		Sticker::sticker_g35g1_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G14, Sticker::sticker_g35g1_wear[3]);
		Sticker::sticker_g35g1_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G14, Sticker::sticker_g35g1_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[0]].flWear = Sticker::sticker_g35g1_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[0]].flScale = Sticker::sticker_g35g1_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[0]].iRotation = Sticker::sticker_g35g1_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[0]].iID = Sticker::sticker_g35g1_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[1]].flWear = Sticker::sticker_g35g1_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[1]].flScale = Sticker::sticker_g35g1_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[1]].iRotation = Sticker::sticker_g35g1_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[1]].iID = Sticker::sticker_g35g1_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[2]].flWear = Sticker::sticker_g35g1_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[2]].flScale = Sticker::sticker_g35g1_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[2]].iRotation = Sticker::sticker_g35g1_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[2]].iID = Sticker::sticker_g35g1_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[3]].flWear = Sticker::sticker_g35g1_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[3]].flScale = Sticker::sticker_g35g1_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[3]].iRotation = Sticker::sticker_g35g1_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[3]].iID = Sticker::sticker_g35g1_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_GALIL, Sticker::stickerSafeWeapon);
		Sticker::sticker_galil_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL1, Sticker::sticker_galil_iSlot[0]);
		Sticker::sticker_galil_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL1, Sticker::sticker_galil_size[0]);
		Sticker::sticker_galil_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL1, Sticker::sticker_galil_id[0]);
		Sticker::sticker_galil_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL1, Sticker::sticker_galil_wear[0]);
		Sticker::sticker_galil_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL1, Sticker::sticker_galil_rotate[0]);
		Sticker::sticker_galil_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL2, Sticker::sticker_galil_iSlot[1]);
		Sticker::sticker_galil_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL2, Sticker::sticker_galil_size[1]);
		Sticker::sticker_galil_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL2, Sticker::sticker_galil_id[1]);
		Sticker::sticker_galil_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL2, Sticker::sticker_galil_wear[1]);
		Sticker::sticker_galil_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL2, Sticker::sticker_galil_rotate[1]);
		Sticker::sticker_galil_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL3, Sticker::sticker_galil_iSlot[2]);
		Sticker::sticker_galil_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL3, Sticker::sticker_galil_size[2]);
		Sticker::sticker_galil_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL3, Sticker::sticker_galil_id[2]);
		Sticker::sticker_galil_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL3, Sticker::sticker_galil_wear[2]);
		Sticker::sticker_galil_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL3, Sticker::sticker_galil_rotate[2]);
		Sticker::sticker_galil_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL4, Sticker::sticker_galil_iSlot[3]);
		Sticker::sticker_galil_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL4, Sticker::sticker_galil_size[3]);
		Sticker::sticker_galil_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL4, Sticker::sticker_galil_id[3]);
		Sticker::sticker_galil_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL4, Sticker::sticker_galil_wear[3]);
		Sticker::sticker_galil_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL4, Sticker::sticker_galil_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[0]].flWear = Sticker::sticker_galil_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[0]].flScale = Sticker::sticker_galil_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[0]].iRotation = Sticker::sticker_galil_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[0]].iID = Sticker::sticker_galil_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[1]].flWear = Sticker::sticker_galil_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[1]].flScale = Sticker::sticker_galil_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[1]].iRotation = Sticker::sticker_galil_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[1]].iID = Sticker::sticker_galil_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[2]].flWear = Sticker::sticker_galil_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[2]].flScale = Sticker::sticker_galil_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[2]].iRotation = Sticker::sticker_galil_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[2]].iID = Sticker::sticker_galil_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[3]].flWear = Sticker::sticker_galil_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[3]].flScale = Sticker::sticker_galil_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[3]].iRotation = Sticker::sticker_galil_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[3]].iID = Sticker::sticker_galil_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_M249, Sticker::stickerSafeWeapon);
		Sticker::sticker_m249_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2491, Sticker::sticker_m249_iSlot[0]);
		Sticker::sticker_m249_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2491, Sticker::sticker_m249_size[0]);
		Sticker::sticker_m249_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2491, Sticker::sticker_m249_id[0]);
		Sticker::sticker_m249_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2491, Sticker::sticker_m249_wear[0]);
		Sticker::sticker_m249_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2491, Sticker::sticker_m249_rotate[0]);
		Sticker::sticker_m249_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2492, Sticker::sticker_m249_iSlot[1]);
		Sticker::sticker_m249_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2492, Sticker::sticker_m249_size[1]);
		Sticker::sticker_m249_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2492, Sticker::sticker_m249_id[1]);
		Sticker::sticker_m249_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2492, Sticker::sticker_m249_wear[1]);
		Sticker::sticker_m249_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2492, Sticker::sticker_m249_rotate[1]);
		Sticker::sticker_m249_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2493, Sticker::sticker_m249_iSlot[2]);
		Sticker::sticker_m249_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2493, Sticker::sticker_m249_size[2]);
		Sticker::sticker_m249_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2493, Sticker::sticker_m249_id[2]);
		Sticker::sticker_m249_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2493, Sticker::sticker_m249_wear[2]);
		Sticker::sticker_m249_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2493, Sticker::sticker_m249_rotate[2]);
		Sticker::sticker_m249_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2494, Sticker::sticker_m249_iSlot[3]);
		Sticker::sticker_m249_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2494, Sticker::sticker_m249_size[3]);
		Sticker::sticker_m249_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2494, Sticker::sticker_m249_id[3]);
		Sticker::sticker_m249_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2494, Sticker::sticker_m249_wear[3]);
		Sticker::sticker_m249_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2494, Sticker::sticker_m249_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[0]].flWear = Sticker::sticker_m249_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[0]].flScale = Sticker::sticker_m249_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[0]].iRotation = Sticker::sticker_m249_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[0]].iID = Sticker::sticker_m249_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[1]].flWear = Sticker::sticker_m249_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[1]].flScale = Sticker::sticker_m249_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[1]].iRotation = Sticker::sticker_m249_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[1]].iID = Sticker::sticker_m249_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[2]].flWear = Sticker::sticker_m249_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[2]].flScale = Sticker::sticker_m249_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[2]].iRotation = Sticker::sticker_m249_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[2]].iID = Sticker::sticker_m249_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[3]].flWear = Sticker::sticker_m249_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[3]].flScale = Sticker::sticker_m249_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[3]].iRotation = Sticker::sticker_m249_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[3]].iID = Sticker::sticker_m249_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_M4A4, Sticker::stickerSafeWeapon);
		Sticker::sticker_m4a4_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A41, Sticker::sticker_m4a4_iSlot[0]);
		Sticker::sticker_m4a4_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A41, Sticker::sticker_m4a4_size[0]);
		Sticker::sticker_m4a4_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A41, Sticker::sticker_m4a4_id[0]);
		Sticker::sticker_m4a4_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A41, Sticker::sticker_m4a4_wear[0]);
		Sticker::sticker_m4a4_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A41, Sticker::sticker_m4a4_rotate[0]);
		Sticker::sticker_m4a4_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A42, Sticker::sticker_m4a4_iSlot[1]);
		Sticker::sticker_m4a4_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A42, Sticker::sticker_m4a4_size[1]);
		Sticker::sticker_m4a4_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A42, Sticker::sticker_m4a4_id[1]);
		Sticker::sticker_m4a4_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A42, Sticker::sticker_m4a4_wear[1]);
		Sticker::sticker_m4a4_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A42, Sticker::sticker_m4a4_rotate[1]);
		Sticker::sticker_m4a4_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A43, Sticker::sticker_m4a4_iSlot[2]);
		Sticker::sticker_m4a4_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A43, Sticker::sticker_m4a4_size[2]);
		Sticker::sticker_m4a4_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A43, Sticker::sticker_m4a4_id[2]);
		Sticker::sticker_m4a4_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A43, Sticker::sticker_m4a4_wear[2]);
		Sticker::sticker_m4a4_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A43, Sticker::sticker_m4a4_rotate[2]);
		Sticker::sticker_m4a4_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A44, Sticker::sticker_m4a4_iSlot[3]);
		Sticker::sticker_m4a4_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A44, Sticker::sticker_m4a4_size[3]);
		Sticker::sticker_m4a4_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A44, Sticker::sticker_m4a4_id[3]);
		Sticker::sticker_m4a4_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A44, Sticker::sticker_m4a4_wear[3]);
		Sticker::sticker_m4a4_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A44, Sticker::sticker_m4a4_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[0]].flWear = Sticker::sticker_m4a4_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[0]].flScale = Sticker::sticker_m4a4_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[0]].iRotation = Sticker::sticker_m4a4_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[0]].iID = Sticker::sticker_m4a4_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[1]].flWear = Sticker::sticker_m4a4_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[1]].flScale = Sticker::sticker_m4a4_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[1]].iRotation = Sticker::sticker_m4a4_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[1]].iID = Sticker::sticker_m4a4_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[2]].flWear = Sticker::sticker_m4a4_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[2]].flScale = Sticker::sticker_m4a4_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[2]].iRotation = Sticker::sticker_m4a4_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[2]].iID = Sticker::sticker_m4a4_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[3]].flWear = Sticker::sticker_m4a4_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[3]].flScale = Sticker::sticker_m4a4_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[3]].iRotation = Sticker::sticker_m4a4_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[3]].iID = Sticker::sticker_m4a4_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MAC10, Sticker::stickerSafeWeapon);
		Sticker::sticker_mac10_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC101, Sticker::sticker_mac10_iSlot[0]);
		Sticker::sticker_mac10_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC101, Sticker::sticker_mac10_size[0]);
		Sticker::sticker_mac10_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC101, Sticker::sticker_mac10_id[0]);
		Sticker::sticker_mac10_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC101, Sticker::sticker_mac10_wear[0]);
		Sticker::sticker_mac10_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC101, Sticker::sticker_mac10_rotate[0]);
		Sticker::sticker_mac10_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC102, Sticker::sticker_mac10_iSlot[1]);
		Sticker::sticker_mac10_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC102, Sticker::sticker_mac10_size[1]);
		Sticker::sticker_mac10_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC102, Sticker::sticker_mac10_id[1]);
		Sticker::sticker_mac10_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC102, Sticker::sticker_mac10_wear[1]);
		Sticker::sticker_mac10_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC102, Sticker::sticker_mac10_rotate[1]);
		Sticker::sticker_mac10_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC103, Sticker::sticker_mac10_iSlot[2]);
		Sticker::sticker_mac10_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC103, Sticker::sticker_mac10_size[2]);
		Sticker::sticker_mac10_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC103, Sticker::sticker_mac10_id[2]);
		Sticker::sticker_mac10_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC103, Sticker::sticker_mac10_wear[2]);
		Sticker::sticker_mac10_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC103, Sticker::sticker_mac10_rotate[2]);
		Sticker::sticker_mac10_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC104, Sticker::sticker_mac10_iSlot[3]);
		Sticker::sticker_mac10_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC104, Sticker::sticker_mac10_size[3]);
		Sticker::sticker_mac10_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC104, Sticker::sticker_mac10_id[3]);
		Sticker::sticker_mac10_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC104, Sticker::sticker_mac10_wear[3]);
		Sticker::sticker_mac10_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC104, Sticker::sticker_mac10_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[0]].flWear = Sticker::sticker_mac10_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[0]].flScale = Sticker::sticker_mac10_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[0]].iRotation = Sticker::sticker_mac10_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[0]].iID = Sticker::sticker_mac10_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[1]].flWear = Sticker::sticker_mac10_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[1]].flScale = Sticker::sticker_mac10_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[1]].iRotation = Sticker::sticker_mac10_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[1]].iID = Sticker::sticker_mac10_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[2]].flWear = Sticker::sticker_mac10_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[2]].flScale = Sticker::sticker_mac10_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[2]].iRotation = Sticker::sticker_mac10_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[2]].iID = Sticker::sticker_mac10_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[3]].flWear = Sticker::sticker_mac10_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[3]].flScale = Sticker::sticker_mac10_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[3]].iRotation = Sticker::sticker_mac10_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[3]].iID = Sticker::sticker_mac10_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P90, Sticker::stickerSafeWeapon);
		Sticker::sticker_p90_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P901, Sticker::sticker_p90_iSlot[0]);
		Sticker::sticker_p90_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P901, Sticker::sticker_p90_size[0]);
		Sticker::sticker_p90_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P901, Sticker::sticker_p90_id[0]);
		Sticker::sticker_p90_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P901, Sticker::sticker_p90_wear[0]);
		Sticker::sticker_p90_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P901, Sticker::sticker_p90_rotate[0]);
		Sticker::sticker_p90_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P902, Sticker::sticker_p90_iSlot[1]);
		Sticker::sticker_p90_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P902, Sticker::sticker_p90_size[1]);
		Sticker::sticker_p90_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P902, Sticker::sticker_p90_id[1]);
		Sticker::sticker_p90_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P902, Sticker::sticker_p90_wear[1]);
		Sticker::sticker_p90_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P902, Sticker::sticker_p90_rotate[1]);
		Sticker::sticker_p90_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P903, Sticker::sticker_p90_iSlot[2]);
		Sticker::sticker_p90_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P903, Sticker::sticker_p90_size[2]);
		Sticker::sticker_p90_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P903, Sticker::sticker_p90_id[2]);
		Sticker::sticker_p90_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P903, Sticker::sticker_p90_wear[2]);
		Sticker::sticker_p90_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P903, Sticker::sticker_p90_rotate[2]);
		Sticker::sticker_p90_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P904, Sticker::sticker_p90_iSlot[3]);
		Sticker::sticker_p90_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P904, Sticker::sticker_p90_size[3]);
		Sticker::sticker_p90_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P904, Sticker::sticker_p90_id[3]);
		Sticker::sticker_p90_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P904, Sticker::sticker_p90_wear[3]);
		Sticker::sticker_p90_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P904, Sticker::sticker_p90_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[0]].flWear = Sticker::sticker_p90_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[0]].flScale = Sticker::sticker_p90_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[0]].iRotation = Sticker::sticker_p90_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[0]].iID = Sticker::sticker_p90_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[1]].flWear = Sticker::sticker_p90_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[1]].flScale = Sticker::sticker_p90_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[1]].iRotation = Sticker::sticker_p90_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[1]].iID = Sticker::sticker_p90_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[2]].flWear = Sticker::sticker_p90_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[2]].flScale = Sticker::sticker_p90_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[2]].iRotation = Sticker::sticker_p90_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[2]].iID = Sticker::sticker_p90_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[3]].flWear = Sticker::sticker_p90_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[3]].flScale = Sticker::sticker_p90_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[3]].iRotation = Sticker::sticker_p90_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[3]].iID = Sticker::sticker_p90_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_UMP, Sticker::stickerSafeWeapon);
		Sticker::sticker_ump_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP1, Sticker::sticker_ump_iSlot[0]);
		Sticker::sticker_ump_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP1, Sticker::sticker_ump_size[0]);
		Sticker::sticker_ump_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP1, Sticker::sticker_ump_id[0]);
		Sticker::sticker_ump_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP1, Sticker::sticker_ump_wear[0]);
		Sticker::sticker_ump_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP1, Sticker::sticker_ump_rotate[0]);
		Sticker::sticker_ump_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP2, Sticker::sticker_ump_iSlot[1]);
		Sticker::sticker_ump_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP2, Sticker::sticker_ump_size[1]);
		Sticker::sticker_ump_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP2, Sticker::sticker_ump_id[1]);
		Sticker::sticker_ump_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP2, Sticker::sticker_ump_wear[1]);
		Sticker::sticker_ump_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP2, Sticker::sticker_ump_rotate[1]);
		Sticker::sticker_ump_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP3, Sticker::sticker_ump_iSlot[2]);
		Sticker::sticker_ump_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP3, Sticker::sticker_ump_size[2]);
		Sticker::sticker_ump_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP3, Sticker::sticker_ump_id[2]);
		Sticker::sticker_ump_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP3, Sticker::sticker_ump_wear[2]);
		Sticker::sticker_ump_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP3, Sticker::sticker_ump_rotate[2]);
		Sticker::sticker_ump_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP4, Sticker::sticker_ump_iSlot[3]);
		Sticker::sticker_ump_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP4, Sticker::sticker_ump_size[3]);
		Sticker::sticker_ump_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP4, Sticker::sticker_ump_id[3]);
		Sticker::sticker_ump_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP4, Sticker::sticker_ump_wear[3]);
		Sticker::sticker_ump_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP4, Sticker::sticker_ump_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[0]].flWear = Sticker::sticker_ump_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[0]].flScale = Sticker::sticker_ump_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[0]].iRotation = Sticker::sticker_ump_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[0]].iID = Sticker::sticker_ump_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[1]].flWear = Sticker::sticker_ump_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[1]].flScale = Sticker::sticker_ump_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[1]].iRotation = Sticker::sticker_ump_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[1]].iID = Sticker::sticker_ump_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[2]].flWear = Sticker::sticker_ump_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[2]].flScale = Sticker::sticker_ump_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[2]].iRotation = Sticker::sticker_ump_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[2]].iID = Sticker::sticker_ump_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[3]].flWear = Sticker::sticker_ump_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[3]].flScale = Sticker::sticker_ump_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[3]].iRotation = Sticker::sticker_ump_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[3]].iID = Sticker::sticker_ump_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_XM, Sticker::stickerSafeWeapon);
		Sticker::sticker_xm_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM1, Sticker::sticker_xm_iSlot[0]);
		Sticker::sticker_xm_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM1, Sticker::sticker_xm_size[0]);
		Sticker::sticker_xm_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM1, Sticker::sticker_xm_id[0]);
		Sticker::sticker_xm_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM1, Sticker::sticker_xm_wear[0]);
		Sticker::sticker_xm_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM1, Sticker::sticker_xm_rotate[0]);
		Sticker::sticker_xm_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM2, Sticker::sticker_xm_iSlot[1]);
		Sticker::sticker_xm_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM2, Sticker::sticker_xm_size[1]);
		Sticker::sticker_xm_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM2, Sticker::sticker_xm_id[1]);
		Sticker::sticker_xm_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM2, Sticker::sticker_xm_wear[1]);
		Sticker::sticker_xm_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM2, Sticker::sticker_xm_rotate[1]);
		Sticker::sticker_xm_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM3, Sticker::sticker_xm_iSlot[2]);
		Sticker::sticker_xm_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM3, Sticker::sticker_xm_size[2]);
		Sticker::sticker_xm_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM3, Sticker::sticker_xm_id[2]);
		Sticker::sticker_xm_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM3, Sticker::sticker_xm_wear[2]);
		Sticker::sticker_xm_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM3, Sticker::sticker_xm_rotate[2]);
		Sticker::sticker_xm_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM4, Sticker::sticker_xm_iSlot[3]);
		Sticker::sticker_xm_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM4, Sticker::sticker_xm_size[3]);
		Sticker::sticker_xm_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM4, Sticker::sticker_xm_id[3]);
		Sticker::sticker_xm_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM4, Sticker::sticker_xm_wear[3]);
		Sticker::sticker_xm_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM4, Sticker::sticker_xm_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[0]].flWear = Sticker::sticker_xm_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[0]].flScale = Sticker::sticker_xm_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[0]].iRotation = Sticker::sticker_xm_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[0]].iID = Sticker::sticker_xm_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[1]].flWear = Sticker::sticker_xm_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[1]].flScale = Sticker::sticker_xm_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[1]].iRotation = Sticker::sticker_xm_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[1]].iID = Sticker::sticker_xm_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[2]].flWear = Sticker::sticker_xm_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[2]].flScale = Sticker::sticker_xm_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[2]].iRotation = Sticker::sticker_xm_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[2]].iID = Sticker::sticker_xm_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[3]].flWear = Sticker::sticker_xm_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[3]].flScale = Sticker::sticker_xm_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[3]].iRotation = Sticker::sticker_xm_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[3]].iID = Sticker::sticker_xm_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_BIZON, Sticker::stickerSafeWeapon);
		Sticker::sticker_bizon_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON1, Sticker::sticker_bizon_iSlot[0]);
		Sticker::sticker_bizon_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON1, Sticker::sticker_bizon_size[0]);
		Sticker::sticker_bizon_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON1, Sticker::sticker_bizon_id[0]);
		Sticker::sticker_bizon_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON1, Sticker::sticker_bizon_wear[0]);
		Sticker::sticker_bizon_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON1, Sticker::sticker_bizon_rotate[0]);
		Sticker::sticker_bizon_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON2, Sticker::sticker_bizon_iSlot[1]);
		Sticker::sticker_bizon_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON2, Sticker::sticker_bizon_size[1]);
		Sticker::sticker_bizon_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON2, Sticker::sticker_bizon_id[1]);
		Sticker::sticker_bizon_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON2, Sticker::sticker_bizon_wear[1]);
		Sticker::sticker_bizon_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON2, Sticker::sticker_bizon_rotate[1]);
		Sticker::sticker_bizon_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON3, Sticker::sticker_bizon_iSlot[2]);
		Sticker::sticker_bizon_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON3, Sticker::sticker_bizon_size[2]);
		Sticker::sticker_bizon_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON3, Sticker::sticker_bizon_id[2]);
		Sticker::sticker_bizon_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON3, Sticker::sticker_bizon_wear[2]);
		Sticker::sticker_bizon_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON3, Sticker::sticker_bizon_rotate[2]);
		Sticker::sticker_bizon_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON4, Sticker::sticker_bizon_iSlot[3]);
		Sticker::sticker_bizon_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON4, Sticker::sticker_bizon_size[3]);
		Sticker::sticker_bizon_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON4, Sticker::sticker_bizon_id[3]);
		Sticker::sticker_bizon_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON4, Sticker::sticker_bizon_wear[3]);
		Sticker::sticker_bizon_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON4, Sticker::sticker_bizon_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[0]].flWear = Sticker::sticker_bizon_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[0]].flScale = Sticker::sticker_bizon_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[0]].iRotation = Sticker::sticker_bizon_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[0]].iID = Sticker::sticker_bizon_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[1]].flWear = Sticker::sticker_bizon_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[1]].flScale = Sticker::sticker_bizon_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[1]].iRotation = Sticker::sticker_bizon_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[1]].iID = Sticker::sticker_bizon_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[2]].flWear = Sticker::sticker_bizon_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[2]].flScale = Sticker::sticker_bizon_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[2]].iRotation = Sticker::sticker_bizon_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[2]].iID = Sticker::sticker_bizon_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[3]].flWear = Sticker::sticker_bizon_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[3]].flScale = Sticker::sticker_bizon_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[3]].iRotation = Sticker::sticker_bizon_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[3]].iID = Sticker::sticker_bizon_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MAG7, Sticker::stickerSafeWeapon);
		Sticker::sticker_mag7_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG71, Sticker::sticker_mag7_iSlot[0]);
		Sticker::sticker_mag7_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG71, Sticker::sticker_mag7_size[0]);
		Sticker::sticker_mag7_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG71, Sticker::sticker_mag7_id[0]);
		Sticker::sticker_mag7_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG71, Sticker::sticker_mag7_wear[0]);
		Sticker::sticker_mag7_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG71, Sticker::sticker_mag7_rotate[0]);
		Sticker::sticker_mag7_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG72, Sticker::sticker_mag7_iSlot[1]);
		Sticker::sticker_mag7_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG72, Sticker::sticker_mag7_size[1]);
		Sticker::sticker_mag7_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG72, Sticker::sticker_mag7_id[1]);
		Sticker::sticker_mag7_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG72, Sticker::sticker_mag7_wear[1]);
		Sticker::sticker_mag7_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG72, Sticker::sticker_mag7_rotate[1]);
		Sticker::sticker_mag7_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG73, Sticker::sticker_mag7_iSlot[2]);
		Sticker::sticker_mag7_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG73, Sticker::sticker_mag7_size[2]);
		Sticker::sticker_mag7_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG73, Sticker::sticker_mag7_id[2]);
		Sticker::sticker_mag7_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG73, Sticker::sticker_mag7_wear[2]);
		Sticker::sticker_mag7_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG73, Sticker::sticker_mag7_rotate[2]);
		Sticker::sticker_mag7_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG74, Sticker::sticker_mag7_iSlot[3]);
		Sticker::sticker_mag7_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG74, Sticker::sticker_mag7_size[3]);
		Sticker::sticker_mag7_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG74, Sticker::sticker_mag7_id[3]);
		Sticker::sticker_mag7_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG74, Sticker::sticker_mag7_wear[3]);
		Sticker::sticker_mag7_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG74, Sticker::sticker_mag7_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[0]].flWear = Sticker::sticker_mag7_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[0]].flScale = Sticker::sticker_mag7_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[0]].iRotation = Sticker::sticker_mag7_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[0]].iID = Sticker::sticker_mag7_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[1]].flWear = Sticker::sticker_mag7_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[1]].flScale = Sticker::sticker_mag7_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[1]].iRotation = Sticker::sticker_mag7_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[1]].iID = Sticker::sticker_mag7_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[2]].flWear = Sticker::sticker_mag7_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[2]].flScale = Sticker::sticker_mag7_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[2]].iRotation = Sticker::sticker_mag7_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[2]].iID = Sticker::sticker_mag7_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[3]].flWear = Sticker::sticker_mag7_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[3]].flScale = Sticker::sticker_mag7_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[3]].iRotation = Sticker::sticker_mag7_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[3]].iID = Sticker::sticker_mag7_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_NEGEV, Sticker::stickerSafeWeapon);
		Sticker::sticker_negev_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV1, Sticker::sticker_negev_iSlot[0]);
		Sticker::sticker_negev_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV1, Sticker::sticker_negev_size[0]);
		Sticker::sticker_negev_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV1, Sticker::sticker_negev_id[0]);
		Sticker::sticker_negev_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV1, Sticker::sticker_negev_wear[0]);
		Sticker::sticker_negev_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV1, Sticker::sticker_negev_rotate[0]);
		Sticker::sticker_negev_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV2, Sticker::sticker_negev_iSlot[1]);
		Sticker::sticker_negev_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV2, Sticker::sticker_negev_size[1]);
		Sticker::sticker_negev_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV2, Sticker::sticker_negev_id[1]);
		Sticker::sticker_negev_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV2, Sticker::sticker_negev_wear[1]);
		Sticker::sticker_negev_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV2, Sticker::sticker_negev_rotate[1]);
		Sticker::sticker_negev_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV3, Sticker::sticker_negev_iSlot[2]);
		Sticker::sticker_negev_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV3, Sticker::sticker_negev_size[2]);
		Sticker::sticker_negev_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV3, Sticker::sticker_negev_id[2]);
		Sticker::sticker_negev_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV3, Sticker::sticker_negev_wear[2]);
		Sticker::sticker_negev_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV3, Sticker::sticker_negev_rotate[2]);
		Sticker::sticker_negev_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV4, Sticker::sticker_negev_iSlot[3]);
		Sticker::sticker_negev_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV4, Sticker::sticker_negev_size[3]);
		Sticker::sticker_negev_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV4, Sticker::sticker_negev_id[3]);
		Sticker::sticker_negev_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV4, Sticker::sticker_negev_wear[3]);
		Sticker::sticker_negev_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV4, Sticker::sticker_negev_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[0]].flWear = Sticker::sticker_negev_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[0]].flScale = Sticker::sticker_negev_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[0]].iRotation = Sticker::sticker_negev_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[0]].iID = Sticker::sticker_negev_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[1]].flWear = Sticker::sticker_negev_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[1]].flScale = Sticker::sticker_negev_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[1]].iRotation = Sticker::sticker_negev_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[1]].iID = Sticker::sticker_negev_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[2]].flWear = Sticker::sticker_negev_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[2]].flScale = Sticker::sticker_negev_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[2]].iRotation = Sticker::sticker_negev_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[2]].iID = Sticker::sticker_negev_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[3]].flWear = Sticker::sticker_negev_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[3]].flScale = Sticker::sticker_negev_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[3]].iRotation = Sticker::sticker_negev_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[3]].iID = Sticker::sticker_negev_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SAWEDOFF, Sticker::stickerSafeWeapon);
		Sticker::sticker_sawedoff_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF1, Sticker::sticker_sawedoff_iSlot[0]);
		Sticker::sticker_sawedoff_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF1, Sticker::sticker_sawedoff_size[0]);
		Sticker::sticker_sawedoff_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF1, Sticker::sticker_sawedoff_id[0]);
		Sticker::sticker_sawedoff_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF1, Sticker::sticker_sawedoff_wear[0]);
		Sticker::sticker_sawedoff_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF1, Sticker::sticker_sawedoff_rotate[0]);
		Sticker::sticker_sawedoff_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF2, Sticker::sticker_sawedoff_iSlot[1]);
		Sticker::sticker_sawedoff_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF2, Sticker::sticker_sawedoff_size[1]);
		Sticker::sticker_sawedoff_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF2, Sticker::sticker_sawedoff_id[1]);
		Sticker::sticker_sawedoff_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF2, Sticker::sticker_sawedoff_wear[1]);
		Sticker::sticker_sawedoff_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF2, Sticker::sticker_sawedoff_rotate[1]);
		Sticker::sticker_sawedoff_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF3, Sticker::sticker_sawedoff_iSlot[2]);
		Sticker::sticker_sawedoff_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF3, Sticker::sticker_sawedoff_size[2]);
		Sticker::sticker_sawedoff_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF3, Sticker::sticker_sawedoff_id[2]);
		Sticker::sticker_sawedoff_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF3, Sticker::sticker_sawedoff_wear[2]);
		Sticker::sticker_sawedoff_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF3, Sticker::sticker_sawedoff_rotate[2]);
		Sticker::sticker_sawedoff_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF4, Sticker::sticker_sawedoff_iSlot[3]);
		Sticker::sticker_sawedoff_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF4, Sticker::sticker_sawedoff_size[3]);
		Sticker::sticker_sawedoff_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF4, Sticker::sticker_sawedoff_id[3]);
		Sticker::sticker_sawedoff_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF4, Sticker::sticker_sawedoff_wear[3]);
		Sticker::sticker_sawedoff_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF4, Sticker::sticker_sawedoff_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[0]].flWear = Sticker::sticker_sawedoff_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[0]].flScale = Sticker::sticker_sawedoff_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[0]].iRotation = Sticker::sticker_sawedoff_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[0]].iID = Sticker::sticker_sawedoff_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[1]].flWear = Sticker::sticker_sawedoff_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[1]].flScale = Sticker::sticker_sawedoff_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[1]].iRotation = Sticker::sticker_sawedoff_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[1]].iID = Sticker::sticker_sawedoff_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[2]].flWear = Sticker::sticker_sawedoff_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[2]].flScale = Sticker::sticker_sawedoff_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[2]].iRotation = Sticker::sticker_sawedoff_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[2]].iID = Sticker::sticker_sawedoff_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[3]].flWear = Sticker::sticker_sawedoff_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[3]].flScale = Sticker::sticker_sawedoff_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[3]].iRotation = Sticker::sticker_sawedoff_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[3]].iID = Sticker::sticker_sawedoff_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_TEC, Sticker::stickerSafeWeapon);
		Sticker::sticker_tec_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC1, Sticker::sticker_tec_iSlot[0]);
		Sticker::sticker_tec_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC1, Sticker::sticker_tec_size[0]);
		Sticker::sticker_tec_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC1, Sticker::sticker_tec_id[0]);
		Sticker::sticker_tec_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC1, Sticker::sticker_tec_wear[0]);
		Sticker::sticker_tec_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC1, Sticker::sticker_tec_rotate[0]);
		Sticker::sticker_tec_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC2, Sticker::sticker_tec_iSlot[1]);
		Sticker::sticker_tec_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC2, Sticker::sticker_tec_size[1]);
		Sticker::sticker_tec_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC2, Sticker::sticker_tec_id[1]);
		Sticker::sticker_tec_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC2, Sticker::sticker_tec_wear[1]);
		Sticker::sticker_tec_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC2, Sticker::sticker_tec_rotate[1]);
		Sticker::sticker_tec_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC3, Sticker::sticker_tec_iSlot[2]);
		Sticker::sticker_tec_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC3, Sticker::sticker_tec_size[2]);
		Sticker::sticker_tec_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC3, Sticker::sticker_tec_id[2]);
		Sticker::sticker_tec_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC3, Sticker::sticker_tec_wear[2]);
		Sticker::sticker_tec_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC3, Sticker::sticker_tec_rotate[2]);
		Sticker::sticker_tec_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC4, Sticker::sticker_tec_iSlot[3]);
		Sticker::sticker_tec_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC4, Sticker::sticker_tec_size[3]);
		Sticker::sticker_tec_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC4, Sticker::sticker_tec_id[3]);
		Sticker::sticker_tec_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC4, Sticker::sticker_tec_wear[3]);
		Sticker::sticker_tec_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC4, Sticker::sticker_tec_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[0]].flWear = Sticker::sticker_tec_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[0]].flScale = Sticker::sticker_tec_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[0]].iRotation = Sticker::sticker_tec_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[0]].iID = Sticker::sticker_tec_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[1]].flWear = Sticker::sticker_tec_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[1]].flScale = Sticker::sticker_tec_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[1]].iRotation = Sticker::sticker_tec_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[1]].iID = Sticker::sticker_tec_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[2]].flWear = Sticker::sticker_tec_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[2]].flScale = Sticker::sticker_tec_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[2]].iRotation = Sticker::sticker_tec_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[2]].iID = Sticker::sticker_tec_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[3]].flWear = Sticker::sticker_tec_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[3]].flScale = Sticker::sticker_tec_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[3]].iRotation = Sticker::sticker_tec_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[3]].iID = Sticker::sticker_tec_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P2000, Sticker::stickerSafeWeapon);
		Sticker::sticker_p2000_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20001, Sticker::sticker_p2000_iSlot[0]);
		Sticker::sticker_p2000_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20001, Sticker::sticker_p2000_size[0]);
		Sticker::sticker_p2000_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20001, Sticker::sticker_p2000_id[0]);
		Sticker::sticker_p2000_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20001, Sticker::sticker_p2000_wear[0]);
		Sticker::sticker_p2000_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20001, Sticker::sticker_p2000_rotate[0]);
		Sticker::sticker_p2000_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20002, Sticker::sticker_p2000_iSlot[1]);
		Sticker::sticker_p2000_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20002, Sticker::sticker_p2000_size[1]);
		Sticker::sticker_p2000_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20002, Sticker::sticker_p2000_id[1]);
		Sticker::sticker_p2000_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20002, Sticker::sticker_p2000_wear[1]);
		Sticker::sticker_p2000_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20002, Sticker::sticker_p2000_rotate[1]);
		Sticker::sticker_p2000_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20003, Sticker::sticker_p2000_iSlot[2]);
		Sticker::sticker_p2000_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20003, Sticker::sticker_p2000_size[2]);
		Sticker::sticker_p2000_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20003, Sticker::sticker_p2000_id[2]);
		Sticker::sticker_p2000_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20003, Sticker::sticker_p2000_wear[2]);
		Sticker::sticker_p2000_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20003, Sticker::sticker_p2000_rotate[2]);
		Sticker::sticker_p2000_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20004, Sticker::sticker_p2000_iSlot[3]);
		Sticker::sticker_p2000_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20004, Sticker::sticker_p2000_size[3]);
		Sticker::sticker_p2000_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20004, Sticker::sticker_p2000_id[3]);
		Sticker::sticker_p2000_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20004, Sticker::sticker_p2000_wear[3]);
		Sticker::sticker_p2000_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20004, Sticker::sticker_p2000_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[0]].flWear = Sticker::sticker_p2000_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[0]].flScale = Sticker::sticker_p2000_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[0]].iRotation = Sticker::sticker_p2000_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[0]].iID = Sticker::sticker_p2000_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[1]].flWear = Sticker::sticker_p2000_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[1]].flScale = Sticker::sticker_p2000_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[1]].iRotation = Sticker::sticker_p2000_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[1]].iID = Sticker::sticker_p2000_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[2]].flWear = Sticker::sticker_p2000_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[2]].flScale = Sticker::sticker_p2000_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[2]].iRotation = Sticker::sticker_p2000_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[2]].iID = Sticker::sticker_p2000_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[3]].flWear = Sticker::sticker_p2000_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[3]].flScale = Sticker::sticker_p2000_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[3]].iRotation = Sticker::sticker_p2000_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[3]].iID = Sticker::sticker_p2000_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MP7, Sticker::stickerSafeWeapon);
		Sticker::sticker_mp7_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP71, Sticker::sticker_mp7_iSlot[0]);
		Sticker::sticker_mp7_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP71, Sticker::sticker_mp7_size[0]);
		Sticker::sticker_mp7_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP71, Sticker::sticker_mp7_id[0]);
		Sticker::sticker_mp7_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP71, Sticker::sticker_mp7_wear[0]);
		Sticker::sticker_mp7_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP71, Sticker::sticker_mp7_rotate[0]);
		Sticker::sticker_mp7_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP72, Sticker::sticker_mp7_iSlot[1]);
		Sticker::sticker_mp7_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP72, Sticker::sticker_mp7_size[1]);
		Sticker::sticker_mp7_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP72, Sticker::sticker_mp7_id[1]);
		Sticker::sticker_mp7_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP72, Sticker::sticker_mp7_wear[1]);
		Sticker::sticker_mp7_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP72, Sticker::sticker_mp7_rotate[1]);
		Sticker::sticker_mp7_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP73, Sticker::sticker_mp7_iSlot[2]);
		Sticker::sticker_mp7_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP73, Sticker::sticker_mp7_size[2]);
		Sticker::sticker_mp7_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP73, Sticker::sticker_mp7_id[2]);
		Sticker::sticker_mp7_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP73, Sticker::sticker_mp7_wear[2]);
		Sticker::sticker_mp7_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP73, Sticker::sticker_mp7_rotate[2]);
		Sticker::sticker_mp7_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP74, Sticker::sticker_mp7_iSlot[3]);
		Sticker::sticker_mp7_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP74, Sticker::sticker_mp7_size[3]);
		Sticker::sticker_mp7_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP74, Sticker::sticker_mp7_id[3]);
		Sticker::sticker_mp7_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP74, Sticker::sticker_mp7_wear[3]);
		Sticker::sticker_mp7_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP74, Sticker::sticker_mp7_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[0]].flWear = Sticker::sticker_mp7_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[0]].flScale = Sticker::sticker_mp7_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[0]].iRotation = Sticker::sticker_mp7_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[0]].iID = Sticker::sticker_mp7_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[1]].flWear = Sticker::sticker_mp7_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[1]].flScale = Sticker::sticker_mp7_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[1]].iRotation = Sticker::sticker_mp7_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[1]].iID = Sticker::sticker_mp7_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[2]].flWear = Sticker::sticker_mp7_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[2]].flScale = Sticker::sticker_mp7_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[2]].iRotation = Sticker::sticker_mp7_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[2]].iID = Sticker::sticker_mp7_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[3]].flWear = Sticker::sticker_mp7_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[3]].flScale = Sticker::sticker_mp7_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[3]].iRotation = Sticker::sticker_mp7_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[3]].iID = Sticker::sticker_mp7_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MP9, Sticker::stickerSafeWeapon);
		Sticker::sticker_mp9_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP91, Sticker::sticker_mp9_iSlot[0]);
		Sticker::sticker_mp9_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP91, Sticker::sticker_mp9_size[0]);
		Sticker::sticker_mp9_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP91, Sticker::sticker_mp9_id[0]);
		Sticker::sticker_mp9_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP91, Sticker::sticker_mp9_wear[0]);
		Sticker::sticker_mp9_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP91, Sticker::sticker_mp9_rotate[0]);
		Sticker::sticker_mp9_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP92, Sticker::sticker_mp9_iSlot[1]);
		Sticker::sticker_mp9_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP92, Sticker::sticker_mp9_size[1]);
		Sticker::sticker_mp9_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP92, Sticker::sticker_mp9_id[1]);
		Sticker::sticker_mp9_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP92, Sticker::sticker_mp9_wear[1]);
		Sticker::sticker_mp9_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP92, Sticker::sticker_mp9_rotate[1]);
		Sticker::sticker_mp9_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP93, Sticker::sticker_mp9_iSlot[2]);
		Sticker::sticker_mp9_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP93, Sticker::sticker_mp9_size[2]);
		Sticker::sticker_mp9_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP93, Sticker::sticker_mp9_id[2]);
		Sticker::sticker_mp9_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP93, Sticker::sticker_mp9_wear[2]);
		Sticker::sticker_mp9_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP93, Sticker::sticker_mp9_rotate[2]);
		Sticker::sticker_mp9_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP94, Sticker::sticker_mp9_iSlot[3]);
		Sticker::sticker_mp9_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP94, Sticker::sticker_mp9_size[3]);
		Sticker::sticker_mp9_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP94, Sticker::sticker_mp9_id[3]);
		Sticker::sticker_mp9_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP94, Sticker::sticker_mp9_wear[3]);
		Sticker::sticker_mp9_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP94, Sticker::sticker_mp9_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[0]].flWear = Sticker::sticker_mp9_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[0]].flScale = Sticker::sticker_mp9_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[0]].iRotation = Sticker::sticker_mp9_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[0]].iID = Sticker::sticker_mp9_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[1]].flWear = Sticker::sticker_mp9_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[1]].flScale = Sticker::sticker_mp9_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[1]].iRotation = Sticker::sticker_mp9_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[1]].iID = Sticker::sticker_mp9_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[2]].flWear = Sticker::sticker_mp9_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[2]].flScale = Sticker::sticker_mp9_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[2]].iRotation = Sticker::sticker_mp9_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[2]].iID = Sticker::sticker_mp9_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[3]].flWear = Sticker::sticker_mp9_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[3]].flScale = Sticker::sticker_mp9_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[3]].iRotation = Sticker::sticker_mp9_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[3]].iID = Sticker::sticker_mp9_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_NOVA, Sticker::stickerSafeWeapon);
		Sticker::sticker_nova_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA1, Sticker::sticker_nova_iSlot[0]);
		Sticker::sticker_nova_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA1, Sticker::sticker_nova_size[0]);
		Sticker::sticker_nova_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA1, Sticker::sticker_nova_id[0]);
		Sticker::sticker_nova_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA1, Sticker::sticker_nova_wear[0]);
		Sticker::sticker_nova_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA1, Sticker::sticker_nova_rotate[0]);
		Sticker::sticker_nova_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA2, Sticker::sticker_nova_iSlot[1]);
		Sticker::sticker_nova_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA2, Sticker::sticker_nova_size[1]);
		Sticker::sticker_nova_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA2, Sticker::sticker_nova_id[1]);
		Sticker::sticker_nova_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA2, Sticker::sticker_nova_wear[1]);
		Sticker::sticker_nova_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA2, Sticker::sticker_nova_rotate[1]);
		Sticker::sticker_nova_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA3, Sticker::sticker_nova_iSlot[2]);
		Sticker::sticker_nova_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA3, Sticker::sticker_nova_size[2]);
		Sticker::sticker_nova_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA3, Sticker::sticker_nova_id[2]);
		Sticker::sticker_nova_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA3, Sticker::sticker_nova_wear[2]);
		Sticker::sticker_nova_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA3, Sticker::sticker_nova_rotate[2]);
		Sticker::sticker_nova_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA4, Sticker::sticker_nova_iSlot[3]);
		Sticker::sticker_nova_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA4, Sticker::sticker_nova_size[3]);
		Sticker::sticker_nova_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA4, Sticker::sticker_nova_id[3]);
		Sticker::sticker_nova_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA4, Sticker::sticker_nova_wear[3]);
		Sticker::sticker_nova_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA4, Sticker::sticker_nova_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[0]].flWear = Sticker::sticker_nova_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[0]].flScale = Sticker::sticker_nova_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[0]].iRotation = Sticker::sticker_nova_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[0]].iID = Sticker::sticker_nova_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[1]].flWear = Sticker::sticker_nova_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[1]].flScale = Sticker::sticker_nova_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[1]].iRotation = Sticker::sticker_nova_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[1]].iID = Sticker::sticker_nova_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[2]].flWear = Sticker::sticker_nova_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[2]].flScale = Sticker::sticker_nova_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[2]].iRotation = Sticker::sticker_nova_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[2]].iID = Sticker::sticker_nova_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[3]].flWear = Sticker::sticker_nova_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[3]].flScale = Sticker::sticker_nova_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[3]].iRotation = Sticker::sticker_nova_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[3]].iID = Sticker::sticker_nova_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P250, Sticker::stickerSafeWeapon);
		Sticker::sticker_p250_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2501, Sticker::sticker_p250_iSlot[0]);
		Sticker::sticker_p250_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2501, Sticker::sticker_p250_size[0]);
		Sticker::sticker_p250_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2501, Sticker::sticker_p250_id[0]);
		Sticker::sticker_p250_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2501, Sticker::sticker_p250_wear[0]);
		Sticker::sticker_p250_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2501, Sticker::sticker_p250_rotate[0]);
		Sticker::sticker_p250_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2502, Sticker::sticker_p250_iSlot[1]);
		Sticker::sticker_p250_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2502, Sticker::sticker_p250_size[1]);
		Sticker::sticker_p250_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2502, Sticker::sticker_p250_id[1]);
		Sticker::sticker_p250_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2502, Sticker::sticker_p250_wear[1]);
		Sticker::sticker_p250_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2502, Sticker::sticker_p250_rotate[1]);
		Sticker::sticker_p250_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2503, Sticker::sticker_p250_iSlot[2]);
		Sticker::sticker_p250_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2503, Sticker::sticker_p250_size[2]);
		Sticker::sticker_p250_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2503, Sticker::sticker_p250_id[2]);
		Sticker::sticker_p250_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2503, Sticker::sticker_p250_wear[2]);
		Sticker::sticker_p250_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2503, Sticker::sticker_p250_rotate[2]);
		Sticker::sticker_p250_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2504, Sticker::sticker_p250_iSlot[3]);
		Sticker::sticker_p250_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2504, Sticker::sticker_p250_size[3]);
		Sticker::sticker_p250_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2504, Sticker::sticker_p250_id[3]);
		Sticker::sticker_p250_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2504, Sticker::sticker_p250_wear[3]);
		Sticker::sticker_p250_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2504, Sticker::sticker_p250_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[0]].flWear = Sticker::sticker_p250_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[0]].flScale = Sticker::sticker_p250_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[0]].iRotation = Sticker::sticker_p250_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[0]].iID = Sticker::sticker_p250_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[1]].flWear = Sticker::sticker_p250_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[1]].flScale = Sticker::sticker_p250_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[1]].iRotation = Sticker::sticker_p250_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[1]].iID = Sticker::sticker_p250_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[2]].flWear = Sticker::sticker_p250_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[2]].flScale = Sticker::sticker_p250_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[2]].iRotation = Sticker::sticker_p250_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[2]].iID = Sticker::sticker_p250_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[3]].flWear = Sticker::sticker_p250_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[3]].flScale = Sticker::sticker_p250_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[3]].iRotation = Sticker::sticker_p250_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[3]].iID = Sticker::sticker_p250_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SCAR, Sticker::stickerSafeWeapon);
		Sticker::sticker_scar_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR1, Sticker::sticker_scar_iSlot[0]);
		Sticker::sticker_scar_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR1, Sticker::sticker_scar_size[0]);
		Sticker::sticker_scar_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR1, Sticker::sticker_scar_id[0]);
		Sticker::sticker_scar_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR1, Sticker::sticker_scar_wear[0]);
		Sticker::sticker_scar_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR1, Sticker::sticker_scar_rotate[0]);
		Sticker::sticker_scar_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR2, Sticker::sticker_scar_iSlot[1]);
		Sticker::sticker_scar_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR2, Sticker::sticker_scar_size[1]);
		Sticker::sticker_scar_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR2, Sticker::sticker_scar_id[1]);
		Sticker::sticker_scar_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR2, Sticker::sticker_scar_wear[1]);
		Sticker::sticker_scar_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR2, Sticker::sticker_scar_rotate[1]);
		Sticker::sticker_scar_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR3, Sticker::sticker_scar_iSlot[2]);
		Sticker::sticker_scar_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR3, Sticker::sticker_scar_size[2]);
		Sticker::sticker_scar_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR3, Sticker::sticker_scar_id[2]);
		Sticker::sticker_scar_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR3, Sticker::sticker_scar_wear[2]);
		Sticker::sticker_scar_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR3, Sticker::sticker_scar_rotate[2]);
		Sticker::sticker_scar_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR4, Sticker::sticker_scar_iSlot[3]);
		Sticker::sticker_scar_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR4, Sticker::sticker_scar_size[3]);
		Sticker::sticker_scar_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR4, Sticker::sticker_scar_id[3]);
		Sticker::sticker_scar_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR4, Sticker::sticker_scar_wear[3]);
		Sticker::sticker_scar_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR4, Sticker::sticker_scar_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[0]].flWear = Sticker::sticker_scar_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[0]].flScale = Sticker::sticker_scar_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[0]].iRotation = Sticker::sticker_scar_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[0]].iID = Sticker::sticker_scar_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[1]].flWear = Sticker::sticker_scar_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[1]].flScale = Sticker::sticker_scar_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[1]].iRotation = Sticker::sticker_scar_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[1]].iID = Sticker::sticker_scar_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[2]].flWear = Sticker::sticker_scar_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[2]].flScale = Sticker::sticker_scar_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[2]].iRotation = Sticker::sticker_scar_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[2]].iID = Sticker::sticker_scar_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[3]].flWear = Sticker::sticker_scar_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[3]].flScale = Sticker::sticker_scar_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[3]].iRotation = Sticker::sticker_scar_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[3]].iID = Sticker::sticker_scar_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SG, Sticker::stickerSafeWeapon);
		Sticker::sticker_sg_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG1, Sticker::sticker_sg_iSlot[0]);
		Sticker::sticker_sg_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG1, Sticker::sticker_sg_size[0]);
		Sticker::sticker_sg_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG1, Sticker::sticker_sg_id[0]);
		Sticker::sticker_sg_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG1, Sticker::sticker_sg_wear[0]);
		Sticker::sticker_sg_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG1, Sticker::sticker_sg_rotate[0]);
		Sticker::sticker_sg_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG2, Sticker::sticker_sg_iSlot[1]);
		Sticker::sticker_sg_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG2, Sticker::sticker_sg_size[1]);
		Sticker::sticker_sg_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG2, Sticker::sticker_sg_id[1]);
		Sticker::sticker_sg_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG2, Sticker::sticker_sg_wear[1]);
		Sticker::sticker_sg_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG2, Sticker::sticker_sg_rotate[1]);
		Sticker::sticker_sg_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG3, Sticker::sticker_sg_iSlot[2]);
		Sticker::sticker_sg_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG3, Sticker::sticker_sg_size[2]);
		Sticker::sticker_sg_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG3, Sticker::sticker_sg_id[2]);
		Sticker::sticker_sg_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG3, Sticker::sticker_sg_wear[2]);
		Sticker::sticker_sg_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG3, Sticker::sticker_sg_rotate[2]);
		Sticker::sticker_sg_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG4, Sticker::sticker_sg_iSlot[3]);
		Sticker::sticker_sg_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG4, Sticker::sticker_sg_size[3]);
		Sticker::sticker_sg_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG4, Sticker::sticker_sg_id[3]);
		Sticker::sticker_sg_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG4, Sticker::sticker_sg_wear[3]);
		Sticker::sticker_sg_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG4, Sticker::sticker_sg_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[0]].flWear = Sticker::sticker_sg_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[0]].flScale = Sticker::sticker_sg_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[0]].iRotation = Sticker::sticker_sg_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[0]].iID = Sticker::sticker_sg_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[1]].flWear = Sticker::sticker_sg_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[1]].flScale = Sticker::sticker_sg_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[1]].iRotation = Sticker::sticker_sg_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[1]].iID = Sticker::sticker_sg_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[2]].flWear = Sticker::sticker_sg_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[2]].flScale = Sticker::sticker_sg_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[2]].iRotation = Sticker::sticker_sg_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[2]].iID = Sticker::sticker_sg_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[3]].flWear = Sticker::sticker_sg_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[3]].flScale = Sticker::sticker_sg_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[3]].iRotation = Sticker::sticker_sg_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[3]].iID = Sticker::sticker_sg_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SSG, Sticker::stickerSafeWeapon);
		Sticker::sticker_ssg_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG1, Sticker::sticker_ssg_iSlot[0]);
		Sticker::sticker_ssg_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG1, Sticker::sticker_ssg_size[0]);
		Sticker::sticker_ssg_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG1, Sticker::sticker_ssg_id[0]);
		Sticker::sticker_ssg_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG1, Sticker::sticker_ssg_wear[0]);
		Sticker::sticker_ssg_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG1, Sticker::sticker_ssg_rotate[0]);
		Sticker::sticker_ssg_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG2, Sticker::sticker_ssg_iSlot[1]);
		Sticker::sticker_ssg_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG2, Sticker::sticker_ssg_size[1]);
		Sticker::sticker_ssg_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG2, Sticker::sticker_ssg_id[1]);
		Sticker::sticker_ssg_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG2, Sticker::sticker_ssg_wear[1]);
		Sticker::sticker_ssg_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG2, Sticker::sticker_ssg_rotate[1]);
		Sticker::sticker_ssg_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG3, Sticker::sticker_ssg_iSlot[2]);
		Sticker::sticker_ssg_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG3, Sticker::sticker_ssg_size[2]);
		Sticker::sticker_ssg_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG3, Sticker::sticker_ssg_id[2]);
		Sticker::sticker_ssg_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG3, Sticker::sticker_ssg_wear[2]);
		Sticker::sticker_ssg_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG3, Sticker::sticker_ssg_rotate[2]);
		Sticker::sticker_ssg_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG4, Sticker::sticker_ssg_iSlot[3]);
		Sticker::sticker_ssg_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG4, Sticker::sticker_ssg_size[3]);
		Sticker::sticker_ssg_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG4, Sticker::sticker_ssg_id[3]);
		Sticker::sticker_ssg_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG4, Sticker::sticker_ssg_wear[3]);
		Sticker::sticker_ssg_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG4, Sticker::sticker_ssg_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[0]].flWear = Sticker::sticker_ssg_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[0]].flScale = Sticker::sticker_ssg_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[0]].iRotation = Sticker::sticker_ssg_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[0]].iID = Sticker::sticker_ssg_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[1]].flWear = Sticker::sticker_ssg_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[1]].flScale = Sticker::sticker_ssg_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[1]].iRotation = Sticker::sticker_ssg_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[1]].iID = Sticker::sticker_ssg_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[2]].flWear = Sticker::sticker_ssg_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[2]].flScale = Sticker::sticker_ssg_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[2]].iRotation = Sticker::sticker_ssg_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[2]].iID = Sticker::sticker_ssg_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[3]].flWear = Sticker::sticker_ssg_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[3]].flScale = Sticker::sticker_ssg_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[3]].iRotation = Sticker::sticker_ssg_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[3]].iID = Sticker::sticker_ssg_id[3];
		ForceFullUpdate();
		*/
	}

	void SaveSettings(string szIniFile)
	{
		CSX::Cvar::InitPath(szIniFile.c_str());

		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DEATHMATCH, Aimbot::aim_Deathmatch);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_WALLATTACK, Aimbot::aim_WallAttack);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_CHECKSMOKE, Aimbot::aim_CheckSmoke);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_ANTIJUMP, Aimbot::aim_AntiJump);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_RCSTYPE, Aimbot::aim_RcsType);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWFOV, Aimbot::aim_DrawFov);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWSPOT, Aimbot::aim_DrawSpot);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK, Aimbot::aim_Backtrack);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK_TICK, Aimbot::aim_Backtracktickrate);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			// ���������
			if (i <= 9)
			{
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, Aimbot::weapon_aim_settings[i].aim_Active);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, Aimbot::weapon_aim_settings[i].aim_Smooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOV, Aimbot::weapon_aim_settings[i].aim_Fov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, Aimbot::weapon_aim_settings[i].aim_FovType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, Aimbot::weapon_aim_settings[i].aim_BestHit);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, Aimbot::weapon_aim_settings[i].aim_Spot);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, Aimbot::weapon_aim_settings[i].aim_Delay);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCS, Aimbot::weapon_aim_settings[i].aim_Rcs);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_AUTOPISTOL, Aimbot::weapon_aim_settings[i].aim_AutoPistol);
			}

			// ��������
			if (i >= 10 && i <= 30)
			{
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, Aimbot::weapon_aim_settings[i].aim_Active);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, Aimbot::weapon_aim_settings[i].aim_Smooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOV, Aimbot::weapon_aim_settings[i].aim_Fov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, Aimbot::weapon_aim_settings[i].aim_FovType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, Aimbot::weapon_aim_settings[i].aim_BestHit);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, Aimbot::weapon_aim_settings[i].aim_Spot);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, Aimbot::weapon_aim_settings[i].aim_Delay);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCS, Aimbot::weapon_aim_settings[i].aim_Rcs);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, Aimbot::weapon_aim_settings[i].aim_RcsFov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, Aimbot::weapon_aim_settings[i].aim_RcsSmooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, Aimbot::weapon_aim_settings[i].aim_RcsClampType);
			}

			// ���������
			if (i >= 31 && i <= 32)
			{
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, Aimbot::weapon_aim_settings[i].aim_Active);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, Aimbot::weapon_aim_settings[i].aim_Smooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOV, Aimbot::weapon_aim_settings[i].aim_Fov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, Aimbot::weapon_aim_settings[i].aim_FovType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, Aimbot::weapon_aim_settings[i].aim_BestHit);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, Aimbot::weapon_aim_settings[i].aim_Spot);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, Aimbot::weapon_aim_settings[i].aim_Delay);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCS, Aimbot::weapon_aim_settings[i].aim_Rcs);
			}
		}

		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_ENABLE, Triggerbot::trigger_Enable);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_DEATHMATCH, Triggerbot::trigger_Deathmatch);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_WALLATTACK, Triggerbot::trigger_WallAttack);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_FASTZOOM, Triggerbot::trigger_FastZoom);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_KEYMODE, Triggerbot::trigger_KeyMode);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWFOV, Triggerbot::trigger_DrawFov);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_SMOKCHECK, Triggerbot::trigger_SmokCheck);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWSPOT, Triggerbot::trigger_DrawSpot);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWFOVASSIST, Triggerbot::trigger_DrawFovAssist);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_DISTANCEMIN, Triggerbot::weapon_trigger_settings[i].trigger_DistanceMin);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_DISTANCEMAX, Triggerbot::weapon_trigger_settings[i].trigger_DistanceMax);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_FOV, Triggerbot::weapon_trigger_settings[i].trigger_Fov);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_DELAYBEFORE, Triggerbot::weapon_trigger_settings[i].trigger_DelayBefore);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_DELAYAFTER, Triggerbot::weapon_trigger_settings[i].trigger_DelayAfter);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_HEADONLY, Triggerbot::weapon_trigger_settings[i].trigger_HeadOnly);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_HITGROUP, Triggerbot::weapon_trigger_settings[i].trigger_HitGroup);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSIST, Triggerbot::weapon_trigger_settings[i].trigger_Assist);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTFOV, Triggerbot::weapon_trigger_settings[i].trigger_AssistFov);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTRCS, Triggerbot::weapon_trigger_settings[i].trigger_AssistRcs);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTFOVTYPE, Triggerbot::weapon_trigger_settings[i].trigger_AssistFovType);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTSMOOTH, Triggerbot::weapon_trigger_settings[i].trigger_AssistSmooth);
		}

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_STYLE, Settings::Esp::esp_Style);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_SIZE, Settings::Esp::esp_Size);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CAPITALTOGGLE, Settings::Esp::esp_CapitalToggle);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_LINE, Settings::Esp::esp_Line);
		
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_OUTLINE, Settings::Esp::esp_Outline);
		
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WALLSOPACITY, Settings::Esp::esp_WallsOpacity);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_NAME, Settings::Esp::esp_Name);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_TIME, Settings::Esp::esp_Time);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WATER, Settings::Esp::esp_Watermark);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CHEATBUILD, Settings::Esp::esp_Cheatbuild);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_HITMARKER_ENABLED, Settings::Esp::esp_HitMarker);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_HITMARKER_COMBO, Settings::Esp::esp_HitMarkerSound);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_RANK, Settings::Esp::esp_Rank);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_HEALTH, Settings::Esp::esp_Health);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_ARMOR, Settings::Esp::esp_Armor);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WEAPON, Settings::Esp::esp_Weapon);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_AMMO, Settings::Esp::esp_Ammo);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_DISTANCE, Settings::Esp::esp_Distance);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_SOUND, Settings::Esp::esp_Sound);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_GRENADEPREDICTION, Settings::Esp::esp_GrenadePrediction);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_INFO, Settings::Esp::esp_Statusx);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_SKELETON, Settings::Esp::esp_Skeleton);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BULLETTRACE, Settings::Esp::esp_BulletTrace);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_TEAM, Settings::Esp::esp_Team);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_ENEMY, Settings::Esp::esp_Enemy);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_VISIBLE, Settings::Esp::esp_Visible);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CHAMSVISIBLE, Settings::Esp::esp_ChamsVisible);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CHAMS, Settings::Esp::esp_Chams);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BOMB, Settings::Esp::esp_Bomb);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BOMBTIMER, Settings::Esp::esp_BombTimer);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WORLDWEAPONS, Settings::Esp::esp_WorldWeapons);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WORLDGRENADE, Settings::Esp::esp_WorldGrenade);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_HEALTH_CHAMS, Esp::esp_Chams);

		string Color_HITMARKER =
			to_string(int(Esp::esp_HitMarkerColor[0] * 255.f)) + "," +
			to_string(int(Esp::esp_HitMarkerColor[1] * 255.f)) + "," +
			to_string(int(Esp::esp_HitMarkerColor[2] * 255.f));

		string esp_Color_CT =
			to_string(int(Settings::Esp::esp_Color_CT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_CT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_CT[2] * 255.f));

		string esp_Color_TT =
			to_string(int(Settings::Esp::esp_Color_TT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_TT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_TT[2] * 255.f));

		string esp_Color_VCT =
			to_string(int(Settings::Esp::esp_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VCT[2] * 255.f));

		string esp_Color_VTT =
			to_string(int(Settings::Esp::esp_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VTT[2] * 255.f));

		string GrenadeHelper =
			to_string(int(Settings::Esp::GrenadeHelper[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::GrenadeHelper[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::GrenadeHelper[2] * 255.f));



		CSX::Cvar::SaveCvar(VISUAL_TEXT, "esp_HitMarkerColor", Color_HITMARKER);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_CT, esp_Color_CT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_TT, esp_Color_TT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VCT, esp_Color_VCT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VTT, esp_Color_VTT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_GrenadeHelper, GrenadeHelper);

		string chams_Color_CT =
			to_string(int(Settings::Esp::chams_Color_CT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_CT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_CT[2] * 255.f));

		string chams_Color_TT =
			to_string(int(Settings::Esp::chams_Color_TT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_TT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_TT[2] * 255.f));

		string chams_Color_VCT =
			to_string(int(Settings::Esp::chams_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VCT[2] * 255.f));

		string chams_Color_VTT =
			to_string(int(Settings::Esp::chams_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VTT[2] * 255.f));

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_CT, chams_Color_CT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_TT, chams_Color_TT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VCT, chams_Color_VCT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VTT, chams_Color_VTT);

		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_CT_MODEL, Skin::knf_ct_model);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_CT_SKIN, Skin::knf_ct_skin);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_TT_MODEL, Skin::knf_tt_model);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_TT_SKIN, Skin::knf_tt_skin);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_GLOVES, Skin::gloves_skin);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackPaintKit);
		}

		CSX::Cvar::SaveCvar(SKIN_TEXT_QUALITY, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].iEntityQuality);
		CSX::Cvar::SaveCvar(SKIN_TEXT_QUALITY, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].iEntityQuality);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT_QUALITY, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].iEntityQuality);
		}

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT_STAT, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackStatTrak);
		}

		CSX::Cvar::SaveCvar(SKIN_TEXT_WEAR, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].flFallbackWear);
		CSX::Cvar::SaveCvar(SKIN_TEXT_WEAR, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].flFallbackWear);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT_WEAR, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].flFallbackWear);
		}

		CSX::Cvar::SaveCvar(SKIN_TEXT_SEED, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].nFallbackSeed);
		CSX::Cvar::SaveCvar(SKIN_TEXT_SEED, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackSeed);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT_SEED, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackSeed);
		}

		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_SKIN_CHANGER, Misc::misc_SkinChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_STICKER_CHANGER, Misc::misc_StickerChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_KNIFE_CHANGER, Misc::misc_KnifeChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_EPOSTPROCESS, Misc::misc_EPostprocess);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_GRENADETRAJECTORY, Misc::misc_GrenadeTrajectory);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK, Aimbot::aim_Backtrack);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_BHOP, Misc::misc_Bhop);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_PUNCH, Misc::misc_Punch);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_NOFLASH, Misc::misc_NoFlash);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_NOSMOKE, Misc::misc_NoSmoke);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_WIREFRAMESMOKE, Misc::misc_wireframesmoke);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_WIREHANDS, Misc::misc_WireHands);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_NOHANDS, Misc::misc_NoHands);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AWPAIM, Misc::misc_AwpAim);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AUTOSTRAFE, Misc::misc_AutoStrafe);
		//CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_LEGITAATOGGLE, Misc::misc_LegitAAToggle);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AUTOACCEPT, Misc::misc_AutoAccept);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_SPECTATORS, Misc::misc_Spectators);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_FOV_CHANGER, Misc::misc_FovChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_FOV_VIEW, Misc::misc_FovView);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_FOV_MDL_VIEW, Misc::misc_FovModelView);

		string Color_MENU =
			to_string(int(Misc::misc_MenuColor[0] * 255.f)) + "," +
			to_string(int(Misc::misc_MenuColor[1] * 255.f)) + "," +
			to_string(int(Misc::misc_MenuColor[2] * 255.f));

		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_MENU_COLOR, Color_MENU);

		string Color_TEXT =
			to_string(int(Misc::misc_TextColor[0] * 255.f)) + "," +
			to_string(int(Misc::misc_TextColor[1] * 255.f)) + "," +
			to_string(int(Misc::misc_TextColor[2] * 255.f));

		CSX::Cvar::SaveCvar(MISC_TEXT, "misc_TextColor", Color_TEXT);

		/*
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE1, Sticker::sticker_deserteagle_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE1, Sticker::sticker_deserteagle_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE1, Sticker::sticker_deserteagle_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE1, Sticker::sticker_deserteagle_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE1, Sticker::sticker_deserteagle_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE2, Sticker::sticker_deserteagle_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE2, Sticker::sticker_deserteagle_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE2, Sticker::sticker_deserteagle_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE2, Sticker::sticker_deserteagle_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE2, Sticker::sticker_deserteagle_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE3, Sticker::sticker_deserteagle_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE3, Sticker::sticker_deserteagle_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE3, Sticker::sticker_deserteagle_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE3, Sticker::sticker_deserteagle_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE3, Sticker::sticker_deserteagle_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE4, Sticker::sticker_deserteagle_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE4, Sticker::sticker_deserteagle_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE4, Sticker::sticker_deserteagle_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE4, Sticker::sticker_deserteagle_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE4, Sticker::sticker_deserteagle_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES1, Sticker::sticker_elites_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES1, Sticker::sticker_elites_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES1, Sticker::sticker_elites_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES1, Sticker::sticker_elites_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES1, Sticker::sticker_elites_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES2, Sticker::sticker_elites_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES2, Sticker::sticker_elites_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES2, Sticker::sticker_elites_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES2, Sticker::sticker_elites_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES2, Sticker::sticker_elites_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES3, Sticker::sticker_elites_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES3, Sticker::sticker_elites_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES3, Sticker::sticker_elites_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES3, Sticker::sticker_elites_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES3, Sticker::sticker_elites_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES4, Sticker::sticker_elites_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES4, Sticker::sticker_elites_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES4, Sticker::sticker_elites_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES4, Sticker::sticker_elites_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES4, Sticker::sticker_elites_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN1, Sticker::sticker_fiveseven_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN1, Sticker::sticker_fiveseven_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN1, Sticker::sticker_fiveseven_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN1, Sticker::sticker_fiveseven_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN1, Sticker::sticker_fiveseven_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN2, Sticker::sticker_fiveseven_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN2, Sticker::sticker_fiveseven_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN2, Sticker::sticker_fiveseven_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN2, Sticker::sticker_fiveseven_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN2, Sticker::sticker_fiveseven_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN3, Sticker::sticker_fiveseven_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN3, Sticker::sticker_fiveseven_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN3, Sticker::sticker_fiveseven_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN3, Sticker::sticker_fiveseven_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN3, Sticker::sticker_fiveseven_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN4, Sticker::sticker_fiveseven_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN4, Sticker::sticker_fiveseven_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN4, Sticker::sticker_fiveseven_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN4, Sticker::sticker_fiveseven_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN4, Sticker::sticker_fiveseven_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK1, Sticker::sticker_glock_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK1, Sticker::sticker_glock_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK1, Sticker::sticker_glock_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK1, Sticker::sticker_glock_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK1, Sticker::sticker_glock_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK2, Sticker::sticker_glock_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK2, Sticker::sticker_glock_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK2, Sticker::sticker_glock_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK2, Sticker::sticker_glock_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK2, Sticker::sticker_glock_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK3, Sticker::sticker_glock_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK3, Sticker::sticker_glock_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK3, Sticker::sticker_glock_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK3, Sticker::sticker_glock_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK3, Sticker::sticker_glock_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK4, Sticker::sticker_glock_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK4, Sticker::sticker_glock_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK4, Sticker::sticker_glock_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK4, Sticker::sticker_glock_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK4, Sticker::sticker_glock_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK1, Sticker::sticker_ak_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK1, Sticker::sticker_ak_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK1, Sticker::sticker_ak_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK1, Sticker::sticker_ak_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK1, Sticker::sticker_ak_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK2, Sticker::sticker_ak_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK2, Sticker::sticker_ak_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK2, Sticker::sticker_ak_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK2, Sticker::sticker_ak_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK2, Sticker::sticker_ak_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK3, Sticker::sticker_ak_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK3, Sticker::sticker_ak_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK3, Sticker::sticker_ak_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK3, Sticker::sticker_ak_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK3, Sticker::sticker_ak_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK4, Sticker::sticker_ak_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK4, Sticker::sticker_ak_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK4, Sticker::sticker_ak_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK4, Sticker::sticker_ak_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK4, Sticker::sticker_ak_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG1, Sticker::sticker_aug_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG1, Sticker::sticker_aug_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG1, Sticker::sticker_aug_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG1, Sticker::sticker_aug_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG1, Sticker::sticker_aug_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG2, Sticker::sticker_aug_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG2, Sticker::sticker_aug_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG2, Sticker::sticker_aug_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG2, Sticker::sticker_aug_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG2, Sticker::sticker_aug_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG3, Sticker::sticker_aug_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG3, Sticker::sticker_aug_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG3, Sticker::sticker_aug_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG3, Sticker::sticker_aug_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG3, Sticker::sticker_aug_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG4, Sticker::sticker_aug_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG4, Sticker::sticker_aug_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG4, Sticker::sticker_aug_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG4, Sticker::sticker_aug_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG4, Sticker::sticker_aug_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP1, Sticker::sticker_awp_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP1, Sticker::sticker_awp_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP1, Sticker::sticker_awp_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP1, Sticker::sticker_awp_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP1, Sticker::sticker_awp_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP2, Sticker::sticker_awp_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP2, Sticker::sticker_awp_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP2, Sticker::sticker_awp_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP2, Sticker::sticker_awp_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP2, Sticker::sticker_awp_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP3, Sticker::sticker_awp_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP3, Sticker::sticker_awp_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP3, Sticker::sticker_awp_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP3, Sticker::sticker_awp_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP3, Sticker::sticker_awp_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP4, Sticker::sticker_awp_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP4, Sticker::sticker_awp_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP4, Sticker::sticker_awp_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP4, Sticker::sticker_awp_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP4, Sticker::sticker_awp_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS1, Sticker::sticker_famas_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS1, Sticker::sticker_famas_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS1, Sticker::sticker_famas_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS1, Sticker::sticker_famas_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS1, Sticker::sticker_famas_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS2, Sticker::sticker_famas_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS2, Sticker::sticker_famas_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS2, Sticker::sticker_famas_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS2, Sticker::sticker_famas_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS2, Sticker::sticker_famas_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS3, Sticker::sticker_famas_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS3, Sticker::sticker_famas_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS3, Sticker::sticker_famas_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS3, Sticker::sticker_famas_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS3, Sticker::sticker_famas_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS4, Sticker::sticker_famas_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS4, Sticker::sticker_famas_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS4, Sticker::sticker_famas_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS4, Sticker::sticker_famas_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS4, Sticker::sticker_famas_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G11, Sticker::sticker_g35g1_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G11, Sticker::sticker_g35g1_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G11, Sticker::sticker_g35g1_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G11, Sticker::sticker_g35g1_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G11, Sticker::sticker_g35g1_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G12, Sticker::sticker_g35g1_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G12, Sticker::sticker_g35g1_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G12, Sticker::sticker_g35g1_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G12, Sticker::sticker_g35g1_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G12, Sticker::sticker_g35g1_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G13, Sticker::sticker_g35g1_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G13, Sticker::sticker_g35g1_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G13, Sticker::sticker_g35g1_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G13, Sticker::sticker_g35g1_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G13, Sticker::sticker_g35g1_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G14, Sticker::sticker_g35g1_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G14, Sticker::sticker_g35g1_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G14, Sticker::sticker_g35g1_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G14, Sticker::sticker_g35g1_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G14, Sticker::sticker_g35g1_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL1, Sticker::sticker_galil_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL1, Sticker::sticker_galil_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL1, Sticker::sticker_galil_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL1, Sticker::sticker_galil_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL1, Sticker::sticker_galil_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL2, Sticker::sticker_galil_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL2, Sticker::sticker_galil_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL2, Sticker::sticker_galil_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL2, Sticker::sticker_galil_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL2, Sticker::sticker_galil_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL3, Sticker::sticker_galil_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL3, Sticker::sticker_galil_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL3, Sticker::sticker_galil_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL3, Sticker::sticker_galil_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL3, Sticker::sticker_galil_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL4, Sticker::sticker_galil_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL4, Sticker::sticker_galil_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL4, Sticker::sticker_galil_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL4, Sticker::sticker_galil_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL4, Sticker::sticker_galil_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2491, Sticker::sticker_m249_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2491, Sticker::sticker_m249_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2491, Sticker::sticker_m249_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2491, Sticker::sticker_m249_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2491, Sticker::sticker_m249_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2492, Sticker::sticker_m249_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2492, Sticker::sticker_m249_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2492, Sticker::sticker_m249_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2492, Sticker::sticker_m249_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2492, Sticker::sticker_m249_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2493, Sticker::sticker_m249_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2493, Sticker::sticker_m249_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2493, Sticker::sticker_m249_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2493, Sticker::sticker_m249_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2493, Sticker::sticker_m249_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2494, Sticker::sticker_m249_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2494, Sticker::sticker_m249_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2494, Sticker::sticker_m249_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2494, Sticker::sticker_m249_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2494, Sticker::sticker_m249_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A41, Sticker::sticker_m4a4_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A41, Sticker::sticker_m4a4_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A41, Sticker::sticker_m4a4_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A41, Sticker::sticker_m4a4_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A41, Sticker::sticker_m4a4_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A42, Sticker::sticker_m4a4_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A42, Sticker::sticker_m4a4_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A42, Sticker::sticker_m4a4_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A42, Sticker::sticker_m4a4_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A42, Sticker::sticker_m4a4_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A43, Sticker::sticker_m4a4_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A43, Sticker::sticker_m4a4_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A43, Sticker::sticker_m4a4_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A43, Sticker::sticker_m4a4_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A43, Sticker::sticker_m4a4_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A44, Sticker::sticker_m4a4_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A44, Sticker::sticker_m4a4_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A44, Sticker::sticker_m4a4_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A44, Sticker::sticker_m4a4_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A44, Sticker::sticker_m4a4_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC101, Sticker::sticker_mac10_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC101, Sticker::sticker_mac10_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC101, Sticker::sticker_mac10_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC101, Sticker::sticker_mac10_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC101, Sticker::sticker_mac10_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC102, Sticker::sticker_mac10_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC102, Sticker::sticker_mac10_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC102, Sticker::sticker_mac10_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC102, Sticker::sticker_mac10_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC102, Sticker::sticker_mac10_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC103, Sticker::sticker_mac10_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC103, Sticker::sticker_mac10_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC103, Sticker::sticker_mac10_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC103, Sticker::sticker_mac10_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC103, Sticker::sticker_mac10_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC104, Sticker::sticker_mac10_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC104, Sticker::sticker_mac10_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC104, Sticker::sticker_mac10_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC104, Sticker::sticker_mac10_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC104, Sticker::sticker_mac10_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P901, Sticker::sticker_p90_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P901, Sticker::sticker_p90_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P901, Sticker::sticker_p90_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P901, Sticker::sticker_p90_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P901, Sticker::sticker_p90_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P902, Sticker::sticker_p90_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P902, Sticker::sticker_p90_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P902, Sticker::sticker_p90_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P902, Sticker::sticker_p90_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P902, Sticker::sticker_p90_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P903, Sticker::sticker_p90_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P903, Sticker::sticker_p90_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P903, Sticker::sticker_p90_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P903, Sticker::sticker_p90_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P903, Sticker::sticker_p90_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P904, Sticker::sticker_p90_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P904, Sticker::sticker_p90_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P904, Sticker::sticker_p90_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P904, Sticker::sticker_p90_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P904, Sticker::sticker_p90_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP1, Sticker::sticker_ump_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP1, Sticker::sticker_ump_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP1, Sticker::sticker_ump_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP1, Sticker::sticker_ump_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP1, Sticker::sticker_ump_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP2, Sticker::sticker_ump_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP2, Sticker::sticker_ump_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP2, Sticker::sticker_ump_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP2, Sticker::sticker_ump_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP2, Sticker::sticker_ump_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP3, Sticker::sticker_ump_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP3, Sticker::sticker_ump_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP3, Sticker::sticker_ump_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP3, Sticker::sticker_ump_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP3, Sticker::sticker_ump_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP4, Sticker::sticker_ump_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP4, Sticker::sticker_ump_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP4, Sticker::sticker_ump_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP4, Sticker::sticker_ump_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP4, Sticker::sticker_ump_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM1, Sticker::sticker_xm_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM1, Sticker::sticker_xm_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM1, Sticker::sticker_xm_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM1, Sticker::sticker_xm_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM1, Sticker::sticker_xm_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM2, Sticker::sticker_xm_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM2, Sticker::sticker_xm_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM2, Sticker::sticker_xm_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM2, Sticker::sticker_xm_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM2, Sticker::sticker_xm_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM3, Sticker::sticker_xm_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM3, Sticker::sticker_xm_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM3, Sticker::sticker_xm_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM3, Sticker::sticker_xm_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM3, Sticker::sticker_xm_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM4, Sticker::sticker_xm_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM4, Sticker::sticker_xm_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM4, Sticker::sticker_xm_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM4, Sticker::sticker_xm_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM4, Sticker::sticker_xm_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON1, Sticker::sticker_bizon_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON1, Sticker::sticker_bizon_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON1, Sticker::sticker_bizon_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON1, Sticker::sticker_bizon_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON1, Sticker::sticker_bizon_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON2, Sticker::sticker_bizon_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON2, Sticker::sticker_bizon_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON2, Sticker::sticker_bizon_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON2, Sticker::sticker_bizon_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON2, Sticker::sticker_bizon_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON3, Sticker::sticker_bizon_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON3, Sticker::sticker_bizon_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON3, Sticker::sticker_bizon_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON3, Sticker::sticker_bizon_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON3, Sticker::sticker_bizon_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON4, Sticker::sticker_bizon_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON4, Sticker::sticker_bizon_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON4, Sticker::sticker_bizon_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON4, Sticker::sticker_bizon_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON4, Sticker::sticker_bizon_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG71, Sticker::sticker_mag7_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG71, Sticker::sticker_mag7_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG71, Sticker::sticker_mag7_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG71, Sticker::sticker_mag7_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG71, Sticker::sticker_mag7_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG72, Sticker::sticker_mag7_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG72, Sticker::sticker_mag7_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG72, Sticker::sticker_mag7_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG72, Sticker::sticker_mag7_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG72, Sticker::sticker_mag7_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG73, Sticker::sticker_mag7_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG73, Sticker::sticker_mag7_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG73, Sticker::sticker_mag7_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG73, Sticker::sticker_mag7_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG73, Sticker::sticker_mag7_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG74, Sticker::sticker_mag7_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG74, Sticker::sticker_mag7_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG74, Sticker::sticker_mag7_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG74, Sticker::sticker_mag7_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG74, Sticker::sticker_mag7_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV1, Sticker::sticker_negev_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV1, Sticker::sticker_negev_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV1, Sticker::sticker_negev_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV1, Sticker::sticker_negev_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV1, Sticker::sticker_negev_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV2, Sticker::sticker_negev_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV2, Sticker::sticker_negev_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV2, Sticker::sticker_negev_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV2, Sticker::sticker_negev_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV2, Sticker::sticker_negev_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV3, Sticker::sticker_negev_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV3, Sticker::sticker_negev_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV3, Sticker::sticker_negev_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV3, Sticker::sticker_negev_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV3, Sticker::sticker_negev_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV4, Sticker::sticker_negev_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV4, Sticker::sticker_negev_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV4, Sticker::sticker_negev_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV4, Sticker::sticker_negev_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV4, Sticker::sticker_negev_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF1, Sticker::sticker_sawedoff_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF1, Sticker::sticker_sawedoff_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF1, Sticker::sticker_sawedoff_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF1, Sticker::sticker_sawedoff_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF1, Sticker::sticker_sawedoff_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF2, Sticker::sticker_sawedoff_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF2, Sticker::sticker_sawedoff_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF2, Sticker::sticker_sawedoff_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF2, Sticker::sticker_sawedoff_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF2, Sticker::sticker_sawedoff_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF3, Sticker::sticker_sawedoff_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF3, Sticker::sticker_sawedoff_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF3, Sticker::sticker_sawedoff_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF3, Sticker::sticker_sawedoff_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF3, Sticker::sticker_sawedoff_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF4, Sticker::sticker_sawedoff_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF4, Sticker::sticker_sawedoff_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF4, Sticker::sticker_sawedoff_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF4, Sticker::sticker_sawedoff_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF4, Sticker::sticker_sawedoff_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC1, Sticker::sticker_tec_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC1, Sticker::sticker_tec_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC1, Sticker::sticker_tec_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC1, Sticker::sticker_tec_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC1, Sticker::sticker_tec_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC2, Sticker::sticker_tec_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC2, Sticker::sticker_tec_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC2, Sticker::sticker_tec_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC2, Sticker::sticker_tec_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC2, Sticker::sticker_tec_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC3, Sticker::sticker_tec_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC3, Sticker::sticker_tec_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC3, Sticker::sticker_tec_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC3, Sticker::sticker_tec_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC3, Sticker::sticker_tec_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC4, Sticker::sticker_tec_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC4, Sticker::sticker_tec_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC4, Sticker::sticker_tec_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC4, Sticker::sticker_tec_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC4, Sticker::sticker_tec_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20001, Sticker::sticker_p2000_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20001, Sticker::sticker_p2000_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20001, Sticker::sticker_p2000_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20001, Sticker::sticker_p2000_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20001, Sticker::sticker_p2000_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20002, Sticker::sticker_p2000_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20002, Sticker::sticker_p2000_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20002, Sticker::sticker_p2000_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20002, Sticker::sticker_p2000_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20002, Sticker::sticker_p2000_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20003, Sticker::sticker_p2000_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20003, Sticker::sticker_p2000_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20003, Sticker::sticker_p2000_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20003, Sticker::sticker_p2000_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20003, Sticker::sticker_p2000_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20004, Sticker::sticker_p2000_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20004, Sticker::sticker_p2000_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20004, Sticker::sticker_p2000_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20004, Sticker::sticker_p2000_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20004, Sticker::sticker_p2000_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP71, Sticker::sticker_mp7_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP71, Sticker::sticker_mp7_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP71, Sticker::sticker_mp7_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP71, Sticker::sticker_mp7_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP71, Sticker::sticker_mp7_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP72, Sticker::sticker_mp7_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP72, Sticker::sticker_mp7_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP72, Sticker::sticker_mp7_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP72, Sticker::sticker_mp7_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP72, Sticker::sticker_mp7_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP73, Sticker::sticker_mp7_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP73, Sticker::sticker_mp7_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP73, Sticker::sticker_mp7_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP73, Sticker::sticker_mp7_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP73, Sticker::sticker_mp7_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP74, Sticker::sticker_mp7_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP74, Sticker::sticker_mp7_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP74, Sticker::sticker_mp7_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP74, Sticker::sticker_mp7_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP74, Sticker::sticker_mp7_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP91, Sticker::sticker_mp9_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP91, Sticker::sticker_mp9_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP91, Sticker::sticker_mp9_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP91, Sticker::sticker_mp9_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP91, Sticker::sticker_mp9_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP92, Sticker::sticker_mp9_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP92, Sticker::sticker_mp9_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP92, Sticker::sticker_mp9_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP92, Sticker::sticker_mp9_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP92, Sticker::sticker_mp9_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP93, Sticker::sticker_mp9_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP93, Sticker::sticker_mp9_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP93, Sticker::sticker_mp9_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP93, Sticker::sticker_mp9_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP93, Sticker::sticker_mp9_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP94, Sticker::sticker_mp9_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP94, Sticker::sticker_mp9_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP94, Sticker::sticker_mp9_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP94, Sticker::sticker_mp9_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP94, Sticker::sticker_mp9_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA1, Sticker::sticker_nova_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA1, Sticker::sticker_nova_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA1, Sticker::sticker_nova_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA1, Sticker::sticker_nova_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA1, Sticker::sticker_nova_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA2, Sticker::sticker_nova_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA2, Sticker::sticker_nova_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA2, Sticker::sticker_nova_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA2, Sticker::sticker_nova_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA2, Sticker::sticker_nova_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA3, Sticker::sticker_nova_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA3, Sticker::sticker_nova_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA3, Sticker::sticker_nova_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA3, Sticker::sticker_nova_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA3, Sticker::sticker_nova_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA4, Sticker::sticker_nova_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA4, Sticker::sticker_nova_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA4, Sticker::sticker_nova_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA4, Sticker::sticker_nova_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA4, Sticker::sticker_nova_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2501, Sticker::sticker_p250_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2501, Sticker::sticker_p250_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2501, Sticker::sticker_p250_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2501, Sticker::sticker_p250_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2501, Sticker::sticker_p250_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2502, Sticker::sticker_p250_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2502, Sticker::sticker_p250_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2502, Sticker::sticker_p250_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2502, Sticker::sticker_p250_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2502, Sticker::sticker_p250_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2503, Sticker::sticker_p250_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2503, Sticker::sticker_p250_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2503, Sticker::sticker_p250_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2503, Sticker::sticker_p250_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2503, Sticker::sticker_p250_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2504, Sticker::sticker_p250_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2504, Sticker::sticker_p250_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2504, Sticker::sticker_p250_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2504, Sticker::sticker_p250_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2504, Sticker::sticker_p250_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR1, Sticker::sticker_scar_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR1, Sticker::sticker_scar_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR1, Sticker::sticker_scar_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR1, Sticker::sticker_scar_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR1, Sticker::sticker_scar_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR2, Sticker::sticker_scar_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR2, Sticker::sticker_scar_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR2, Sticker::sticker_scar_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR2, Sticker::sticker_scar_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR2, Sticker::sticker_scar_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR3, Sticker::sticker_scar_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR3, Sticker::sticker_scar_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR3, Sticker::sticker_scar_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR3, Sticker::sticker_scar_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR3, Sticker::sticker_scar_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR4, Sticker::sticker_scar_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR4, Sticker::sticker_scar_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR4, Sticker::sticker_scar_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR4, Sticker::sticker_scar_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR4, Sticker::sticker_scar_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG1, Sticker::sticker_sg_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG1, Sticker::sticker_sg_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG1, Sticker::sticker_sg_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG1, Sticker::sticker_sg_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG1, Sticker::sticker_sg_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG2, Sticker::sticker_sg_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG2, Sticker::sticker_sg_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG2, Sticker::sticker_sg_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG2, Sticker::sticker_sg_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG2, Sticker::sticker_sg_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG3, Sticker::sticker_sg_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG3, Sticker::sticker_sg_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG3, Sticker::sticker_sg_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG3, Sticker::sticker_sg_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG3, Sticker::sticker_sg_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG4, Sticker::sticker_sg_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG4, Sticker::sticker_sg_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG4, Sticker::sticker_sg_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG4, Sticker::sticker_sg_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG4, Sticker::sticker_sg_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG1, Sticker::sticker_ssg_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG1, Sticker::sticker_ssg_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG1, Sticker::sticker_ssg_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG1, Sticker::sticker_ssg_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG1, Sticker::sticker_ssg_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG2, Sticker::sticker_ssg_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG2, Sticker::sticker_ssg_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG2, Sticker::sticker_ssg_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG2, Sticker::sticker_ssg_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG2, Sticker::sticker_ssg_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG3, Sticker::sticker_ssg_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG3, Sticker::sticker_ssg_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG3, Sticker::sticker_ssg_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG3, Sticker::sticker_ssg_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG3, Sticker::sticker_ssg_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG4, Sticker::sticker_ssg_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG4, Sticker::sticker_ssg_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG4, Sticker::sticker_ssg_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG4, Sticker::sticker_ssg_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG4, Sticker::sticker_ssg_iSlot[3]);

		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_DEAGLE, "1");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_ELITES, "2");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_FIVESEVEN, "3");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_GLOCK, "4");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AK, "7");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AUG, "8");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AWP, "9");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_FAMAS, "10");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_G35G1, "11");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_GALIL, "13");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_M249, "14");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_M4A4, "16");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MAC10, "17");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P90, "19");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_UMP, "24");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_XM, "25");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_BIZON, "26");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MAG7, "27");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_NEGEV, "28");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SAWEDOFF, "29");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_TEC, "30");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P2000, "32");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MP7, "33");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MP9, "34");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_NOVA, "35");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P250, "36");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SCAR, "38");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SG, "39");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SSG, "40");
		*/
	}

	float hitmarkerAlpha;

	int TriggerCharToKey(const char* Key)
	{
		if (!strcmp(Key, CVAR_KEY_MOUSE3)) return 0;
		if (!strcmp(Key, CVAR_KEY_MOUSE4)) return 1;
		if (!strcmp(Key, CVAR_KEY_MOUSE5)) return 2;

		return 0;
	}

	namespace Aimbot
	{
		bool aim_Backtrack = false;
		bool aim_DrawBacktrack = false;
		int aim_Backtracktickrate = 1;
		bool aim_Deathmatch = false;
		bool aim_WallAttack = false;
		bool aim_CheckSmoke = false;
		bool aim_AntiJump = false;
		int aim_RcsType = 0;
		bool aim_DrawFov = false;
		bool aim_DrawSpot = false;

		weapon_aim_s weapon_aim_settings[33] = { 0 };
	}

	/*
	namespace Sticker
	{
	float sticker_deserteagle_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_deserteagle_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_deserteagle_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_deserteagle_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_deserteagle_id[4] = { 0 , 0 , 0, 0 };

	float sticker_elites_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_elites_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_elites_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_elites_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_elites_id[4] = { 0 , 0 , 0, 0 };

	float sticker_fiveseven_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_fiveseven_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_fiveseven_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_fiveseven_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_fiveseven_id[4] = { 0 , 0 , 0, 0 };

	float sticker_glock_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_glock_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_glock_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_glock_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_glock_id[4] = { 0 , 0 , 0, 0 };

	float sticker_ak_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_ak_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_ak_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_ak_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_ak_id[4] = { 0 , 0 , 0, 0 };

	float sticker_aug_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_aug_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_aug_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_aug_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_aug_id[4] = { 0 , 0 , 0, 0 };

	float sticker_awp_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_awp_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_awp_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_awp_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_awp_id[4] = { 0 , 0 , 0, 0 };

	float sticker_famas_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_famas_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_famas_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_famas_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_famas_id[4] = { 0 , 0 , 0, 0 };

	float sticker_g35g1_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_g35g1_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_g35g1_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_g35g1_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_g35g1_id[4] = { 0 , 0 , 0, 0 };

	float sticker_galil_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_galil_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_galil_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_galil_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_galil_id[4] = { 0 , 0 , 0, 0 };

	float sticker_m249_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_m249_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_m249_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_m249_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_m249_id[4] = { 0 , 0 , 0, 0 };

	float sticker_m4a4_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_m4a4_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_m4a4_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_m4a4_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_m4a4_id[4] = { 0 , 0 , 0, 0 };

	float sticker_mac10_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_mac10_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_mac10_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_mac10_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_mac10_id[4] = { 0 , 0 , 0, 0 };

	float sticker_p90_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_p90_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_p90_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_p90_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_p90_id[4] = { 0 , 0 , 0, 0 };

	float sticker_ump_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_ump_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_ump_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_ump_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_ump_id[4] = { 0 , 0 , 0, 0 };

	float sticker_xm_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_xm_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_xm_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_xm_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_xm_id[4] = { 0 , 0 , 0, 0 };

	float sticker_bizon_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_bizon_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_bizon_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_bizon_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_bizon_id[4] = { 0 , 0 , 0, 0 };

	float sticker_mag7_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_mag7_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_mag7_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_mag7_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_mag7_id[4] = { 0 , 0 , 0, 0 };

	float sticker_negev_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_negev_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_negev_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_negev_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_negev_id[4] = { 0 , 0 , 0, 0 };

	float sticker_sawedoff_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_sawedoff_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_sawedoff_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_sawedoff_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_sawedoff_id[4] = { 0 , 0 , 0, 0 };

	float sticker_tec_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_tec_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_tec_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_tec_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_tec_id[4] = { 0 , 0 , 0, 0 };

	float sticker_p2000_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_p2000_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_p2000_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_p2000_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_p2000_id[4] = { 0 , 0 , 0, 0 };

	float sticker_mp7_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_mp7_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_mp7_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_mp7_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_mp7_id[4] = { 0 , 0 , 0, 0 };

	float sticker_mp9_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_mp9_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_mp9_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_mp9_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_mp9_id[4] = { 0 , 0 , 0, 0 };

	float sticker_nova_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_nova_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_nova_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_nova_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_nova_id[4] = { 0 , 0 , 0, 0 };

	float sticker_p250_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_p250_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_p250_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_p250_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_p250_id[4] = { 0 , 0 , 0, 0 };

	float sticker_scar_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_scar_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_scar_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_scar_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_scar_id[4] = { 0 , 0 , 0, 0 };

	float sticker_sg_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_sg_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_sg_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_sg_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_sg_id[4] = { 0 , 0 , 0, 0 };

	float sticker_ssg_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_ssg_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_ssg_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_ssg_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_ssg_id[4] = { 0 , 0 , 0, 0 };

	int stickerSafeWeapon = 0;
	}
	*/

	namespace Triggerbot
	{
		int trigger_Enable = 0;
		bool trigger_Deathmatch = false;
		bool trigger_WallAttack = false;
		bool trigger_FastZoom = false;
		int trigger_Key = 0;
		int trigger_KeyMode = 0;
		bool trigger_SmokCheck = false;
		bool trigger_DrawFov = false;
		bool trigger_DrawSpot = false;
		bool trigger_DrawFovAssist = false;

		weapon_trigger_s weapon_trigger_settings[33] = { 0 };
	}

	namespace Esp
	{
		int esp_Style = 0; // 0 - Box 1 - CoalBox
		int esp_Size = 1;
		bool esp_CapitalToggle = 0;
		bool esp_Line = false;
		bool esp_Outline = false; // Box ( 0 - Box 1 - OutlineBox ) ,
								  // CoalBox ( 0 - CoalBox 1 - OutlineCoalBox )	

		bool esp_Time = true;
		bool esp_Watermark = true;
		bool esp_Cheatbuild = true;
		bool esp_Name = false;
		bool esp_Rank = false;
		int esp_Health = 0;
		int esp_Armor = 0;
		bool esp_Weapon = false;
		bool esp_Ammo = false;
		bool esp_Distance = false;
		bool esp_Sound = false;
		bool esp_GrenadePrediction = false;
		bool esp_Chicken = false;
		
		bool esp_Circle = false;
		bool esp_Fish = false;
		bool helper = false;
		bool esp_HealthChams = false;
		bool esp_Statusx = false;

		int esp_WallsOpacity = 100;


		bool bEspWarnings = false;


		bool esp_AsusWalls = false;
		float esp_Ambient[3];

		bool esp_HitMarker = false;
		int esp_HitMarkerSound = 0;
		float esp_HitMarkerColor[3] = { 0.f, 0.f, 0.f };

		bool esp_Skeleton = 0;
		int esp_BulletTrace = 0;
		bool esp_Team = 1;
		bool esp_Enemy = 1;
		int esp_Visible = 1;
		int esp_ChamsVisible = 1;

		int esp_Chams = 0;
		bool esp_Bomb = false;
		int esp_BombTimer = 40;
		bool esp_WorldWeapons = false;
		bool esp_WorldGrenade = false;
		bool esp_BoxNade = false;
		bool esp_ChromeWorld = false;
		bool esp_MinecraftMode = false;
		bool esp_LSDMode = false;
		bool esp_NightMode = false;

		bool esp_legitAAWarnings = false;

		float esp_Color_CT[3] = { 0.f,0.0f,0.f };
		float esp_Color_TT[3] = { 0.f,0.0f,0.f };
		float esp_Color_VCT[3] = { 0.f,0.0f,0.f };
		float esp_Color_VTT[3] = { 0.f,0.0f,0.f };

		float GrenadeHelper[3] = { 0.f,0.f,0.f };

		float chams_Color_CT[3] = { 0.f,0.0f,0.f };
		float chams_Color_TT[3] = { 0.f,0.0f,0.f };
		float chams_Color_VCT[3] = { 0.f,0.0f,0.f };
		float chams_Color_VTT[3] = { 0.f,0.0f,0.f };
	}

	namespace Skin
	{
		int knf_ct_model = 0;
		int knf_ct_skin = 0;
		int knf_tt_model = 0;
		int knf_tt_skin = 0;
		int gloves_skin = 0;
	}

	namespace Misc
	{

		QAngle qLastTickAngle;

		float misc_MenuColor[3] = { 0.f, 0.f, 0.f };
		bool misc_ragdoll_gravity;
		int misc_ragdoll_gravity_amount;
		bool misc_pushscale;
		int misc_pushscale_amount;
		bool misc_SkinChanger = false;
		bool misc_KnifeChanger = false;
		bool misc_StickerChanger = false;
		bool stickerids = false;
		
		bool misc_ChamsMaterials = false;
		int misc_ChamsMaterialsList = 0;
		bool misc_ArmMaterials = false;
		int misc_ArmMaterialsList = 0;
		int misc_ArmMaterialsType = 0;
		int misc_Clan = 0;
		bool misc_spamregular = false;
		bool misc_spamrandom = false;
		const char* misc_SkyName;
		int misc_CurrentSky;
		bool misc_NoSky = false;
		bool misc_Snow = false;
		bool misc_EPostprocess = false;
		bool misc_GrenadeTrajectory = false;
		bool misc_Postprocess = false;
		bool misc_Bhop = false;
		bool misc_Punch = false;
		bool misc_NoFlash = false;
		bool misc_WireHands = false;
		bool misc_NoHands = false;
		bool misc_NoSmoke = false;
		bool misc_wireframesmoke = false;
		bool misc_AwpAim = false;
		bool misc_AutoStrafe = false;
		bool misc_LegitAAToggle = false;
		bool misc_AutoAccept = false;
		bool misc_Spectators = false;
		bool misc_RainbowMenu = false;
		float misc_RainbowSpeed = 0.001f;
		bool misc_FovChanger = false;
		int misc_FovView = 90;
		int misc_FovModelView = 68;
		float misc_TextColor[3] = { 0.f, 0.f, 0.f };
		float hitmarkerAlpha;
		bool skinids = false;
		bool weaponids = false;
		bool misc_LegitAA = false;
		int misc_fakeping_value = 0;
		bool misc_fakeping = false;
		bool invalwayson = false;
		bool custommodelson = false;
		int customodelst;
		int customodelsct;
		char misc_NameChange = 0;
		bool misc_FullBright = false;
	}
}























































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTLVNFJWJJ
{ 
  void FlrKNxBAVY()
  { 
      bool HlzIHJntiF = false;
      bool UlRuNPJHQx = false;
      bool ZzLGESOZBW = false;
      bool rANfwwZlBk = false;
      bool TAoezjuQnY = false;
      bool zBNUrHarDo = false;
      bool tOsMMUXkyQ = false;
      bool oWGedZKgHT = false;
      bool XxkbWpmsno = false;
      bool VghLqFHbRd = false;
      bool MJSXibuhqR = false;
      bool xskjRxdQoW = false;
      bool hdxJtIntnX = false;
      bool RhPcHNdNsu = false;
      bool tECVrcuytt = false;
      bool bqmuwhMJca = false;
      bool mBtSAOdIbE = false;
      bool SQWtbcbaRR = false;
      bool NpztwauUgZ = false;
      bool AUjSHsJjVc = false;
      string GwydRAjHCA;
      string QTIDRbQCeH;
      string zUrgzqLCQU;
      string JxWAasnyZk;
      string EhkyDOffHC;
      string FMHrwkERea;
      string nhphpSxIcY;
      string nScsCQitcj;
      string LftOPxoeDp;
      string oWTywWrDHk;
      string RWDiOmiOpe;
      string BJntPImbSs;
      string cSEmiRyexe;
      string YflrSncLzc;
      string NanYnehZim;
      string jQkOHyRPzx;
      string nEQKGVXwaa;
      string eabpeCdfyE;
      string iYuJtIuXjT;
      string VMMCnIJdRS;
      if(GwydRAjHCA == RWDiOmiOpe){HlzIHJntiF = true;}
      else if(RWDiOmiOpe == GwydRAjHCA){MJSXibuhqR = true;}
      if(QTIDRbQCeH == BJntPImbSs){UlRuNPJHQx = true;}
      else if(BJntPImbSs == QTIDRbQCeH){xskjRxdQoW = true;}
      if(zUrgzqLCQU == cSEmiRyexe){ZzLGESOZBW = true;}
      else if(cSEmiRyexe == zUrgzqLCQU){hdxJtIntnX = true;}
      if(JxWAasnyZk == YflrSncLzc){rANfwwZlBk = true;}
      else if(YflrSncLzc == JxWAasnyZk){RhPcHNdNsu = true;}
      if(EhkyDOffHC == NanYnehZim){TAoezjuQnY = true;}
      else if(NanYnehZim == EhkyDOffHC){tECVrcuytt = true;}
      if(FMHrwkERea == jQkOHyRPzx){zBNUrHarDo = true;}
      else if(jQkOHyRPzx == FMHrwkERea){bqmuwhMJca = true;}
      if(nhphpSxIcY == nEQKGVXwaa){tOsMMUXkyQ = true;}
      else if(nEQKGVXwaa == nhphpSxIcY){mBtSAOdIbE = true;}
      if(nScsCQitcj == eabpeCdfyE){oWGedZKgHT = true;}
      if(LftOPxoeDp == iYuJtIuXjT){XxkbWpmsno = true;}
      if(oWTywWrDHk == VMMCnIJdRS){VghLqFHbRd = true;}
      while(eabpeCdfyE == nScsCQitcj){SQWtbcbaRR = true;}
      while(iYuJtIuXjT == iYuJtIuXjT){NpztwauUgZ = true;}
      while(VMMCnIJdRS == VMMCnIJdRS){AUjSHsJjVc = true;}
      if(HlzIHJntiF == true){HlzIHJntiF = false;}
      if(UlRuNPJHQx == true){UlRuNPJHQx = false;}
      if(ZzLGESOZBW == true){ZzLGESOZBW = false;}
      if(rANfwwZlBk == true){rANfwwZlBk = false;}
      if(TAoezjuQnY == true){TAoezjuQnY = false;}
      if(zBNUrHarDo == true){zBNUrHarDo = false;}
      if(tOsMMUXkyQ == true){tOsMMUXkyQ = false;}
      if(oWGedZKgHT == true){oWGedZKgHT = false;}
      if(XxkbWpmsno == true){XxkbWpmsno = false;}
      if(VghLqFHbRd == true){VghLqFHbRd = false;}
      if(MJSXibuhqR == true){MJSXibuhqR = false;}
      if(xskjRxdQoW == true){xskjRxdQoW = false;}
      if(hdxJtIntnX == true){hdxJtIntnX = false;}
      if(RhPcHNdNsu == true){RhPcHNdNsu = false;}
      if(tECVrcuytt == true){tECVrcuytt = false;}
      if(bqmuwhMJca == true){bqmuwhMJca = false;}
      if(mBtSAOdIbE == true){mBtSAOdIbE = false;}
      if(SQWtbcbaRR == true){SQWtbcbaRR = false;}
      if(NpztwauUgZ == true){NpztwauUgZ = false;}
      if(AUjSHsJjVc == true){AUjSHsJjVc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FVFZXDHRYP
{ 
  void aewJysAkAi()
  { 
      bool sIlezUJNqk = false;
      bool qXmbdXIhEP = false;
      bool LfjQMJUAOR = false;
      bool JUPQLWzCOp = false;
      bool cokfrWMRAY = false;
      bool iZFNjNXURo = false;
      bool AJyZbWIVQG = false;
      bool XGTOlWtEYp = false;
      bool xCAohiOBgy = false;
      bool zekZoTpLDV = false;
      bool NpBsBbGqaM = false;
      bool STubqxJIqr = false;
      bool HGoRHsVtYS = false;
      bool fiADbHBGnG = false;
      bool cXaTeeiJhr = false;
      bool KhTLOGAikI = false;
      bool GLRIgjTrzi = false;
      bool wCTkOifVmb = false;
      bool JMLgHxPonV = false;
      bool HRUfzQGSlu = false;
      string oNjjziXSBN;
      string gDHhCSACeK;
      string ybBTwcILKp;
      string ciPXNCwhcq;
      string nPFdYOZpqV;
      string AjIfMNLQnV;
      string aMHKkxmjUz;
      string VRZnWiWXug;
      string CSToprZiKz;
      string qfsGQbHtsa;
      string apUqAhKUJd;
      string pmVGTHrSUr;
      string XEYVIpXTWt;
      string abdTGLycnH;
      string hFYfJDJllI;
      string jnZBDWQzhK;
      string JpxOCNJBAH;
      string JOdMJResLF;
      string flgOKmCcQi;
      string tztdxrIJcu;
      if(oNjjziXSBN == apUqAhKUJd){sIlezUJNqk = true;}
      else if(apUqAhKUJd == oNjjziXSBN){NpBsBbGqaM = true;}
      if(gDHhCSACeK == pmVGTHrSUr){qXmbdXIhEP = true;}
      else if(pmVGTHrSUr == gDHhCSACeK){STubqxJIqr = true;}
      if(ybBTwcILKp == XEYVIpXTWt){LfjQMJUAOR = true;}
      else if(XEYVIpXTWt == ybBTwcILKp){HGoRHsVtYS = true;}
      if(ciPXNCwhcq == abdTGLycnH){JUPQLWzCOp = true;}
      else if(abdTGLycnH == ciPXNCwhcq){fiADbHBGnG = true;}
      if(nPFdYOZpqV == hFYfJDJllI){cokfrWMRAY = true;}
      else if(hFYfJDJllI == nPFdYOZpqV){cXaTeeiJhr = true;}
      if(AjIfMNLQnV == jnZBDWQzhK){iZFNjNXURo = true;}
      else if(jnZBDWQzhK == AjIfMNLQnV){KhTLOGAikI = true;}
      if(aMHKkxmjUz == JpxOCNJBAH){AJyZbWIVQG = true;}
      else if(JpxOCNJBAH == aMHKkxmjUz){GLRIgjTrzi = true;}
      if(VRZnWiWXug == JOdMJResLF){XGTOlWtEYp = true;}
      if(CSToprZiKz == flgOKmCcQi){xCAohiOBgy = true;}
      if(qfsGQbHtsa == tztdxrIJcu){zekZoTpLDV = true;}
      while(JOdMJResLF == VRZnWiWXug){wCTkOifVmb = true;}
      while(flgOKmCcQi == flgOKmCcQi){JMLgHxPonV = true;}
      while(tztdxrIJcu == tztdxrIJcu){HRUfzQGSlu = true;}
      if(sIlezUJNqk == true){sIlezUJNqk = false;}
      if(qXmbdXIhEP == true){qXmbdXIhEP = false;}
      if(LfjQMJUAOR == true){LfjQMJUAOR = false;}
      if(JUPQLWzCOp == true){JUPQLWzCOp = false;}
      if(cokfrWMRAY == true){cokfrWMRAY = false;}
      if(iZFNjNXURo == true){iZFNjNXURo = false;}
      if(AJyZbWIVQG == true){AJyZbWIVQG = false;}
      if(XGTOlWtEYp == true){XGTOlWtEYp = false;}
      if(xCAohiOBgy == true){xCAohiOBgy = false;}
      if(zekZoTpLDV == true){zekZoTpLDV = false;}
      if(NpBsBbGqaM == true){NpBsBbGqaM = false;}
      if(STubqxJIqr == true){STubqxJIqr = false;}
      if(HGoRHsVtYS == true){HGoRHsVtYS = false;}
      if(fiADbHBGnG == true){fiADbHBGnG = false;}
      if(cXaTeeiJhr == true){cXaTeeiJhr = false;}
      if(KhTLOGAikI == true){KhTLOGAikI = false;}
      if(GLRIgjTrzi == true){GLRIgjTrzi = false;}
      if(wCTkOifVmb == true){wCTkOifVmb = false;}
      if(JMLgHxPonV == true){JMLgHxPonV = false;}
      if(HRUfzQGSlu == true){HRUfzQGSlu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANVBNAABND
{ 
  void fFJXVpKjCX()
  { 
      bool lTIZFJYSyp = false;
      bool ZbgOUdFGAI = false;
      bool ufQWneoOqM = false;
      bool kpVQKSHBdr = false;
      bool PCZorFMIHe = false;
      bool OudQmFDlla = false;
      bool TJakEiFQEB = false;
      bool VEcIrrFadh = false;
      bool RgGLyoMFdE = false;
      bool PVOCXGbojI = false;
      bool zwEGIJSUXt = false;
      bool zbHDJlDOmP = false;
      bool WAmzkAoZkl = false;
      bool QQpUiUcACn = false;
      bool WqgiEmNLrk = false;
      bool DMBUlzIEUI = false;
      bool UrjlchllUn = false;
      bool JCLyseSDtx = false;
      bool mdhziEOVhj = false;
      bool LYetTdHuGV = false;
      string KuaahIoxgo;
      string ZgJgNRQalc;
      string HrUDQSyPbW;
      string BxWUZasHip;
      string oLfCkHbokh;
      string OuAOxSaXJP;
      string KYUKnbKnHm;
      string XJqunuLRRJ;
      string qIetHFxHXH;
      string zVxTfPpVNI;
      string wmgxJFEEaB;
      string GIFAYBtaCh;
      string eCQAmCMWOX;
      string EoDJMDbgjC;
      string BrgVAqPwue;
      string VPTectWgKH;
      string sgpCxREwnU;
      string YMqAgmUtzw;
      string mPbjBoVYfR;
      string gtWbITBeYi;
      if(KuaahIoxgo == wmgxJFEEaB){lTIZFJYSyp = true;}
      else if(wmgxJFEEaB == KuaahIoxgo){zwEGIJSUXt = true;}
      if(ZgJgNRQalc == GIFAYBtaCh){ZbgOUdFGAI = true;}
      else if(GIFAYBtaCh == ZgJgNRQalc){zbHDJlDOmP = true;}
      if(HrUDQSyPbW == eCQAmCMWOX){ufQWneoOqM = true;}
      else if(eCQAmCMWOX == HrUDQSyPbW){WAmzkAoZkl = true;}
      if(BxWUZasHip == EoDJMDbgjC){kpVQKSHBdr = true;}
      else if(EoDJMDbgjC == BxWUZasHip){QQpUiUcACn = true;}
      if(oLfCkHbokh == BrgVAqPwue){PCZorFMIHe = true;}
      else if(BrgVAqPwue == oLfCkHbokh){WqgiEmNLrk = true;}
      if(OuAOxSaXJP == VPTectWgKH){OudQmFDlla = true;}
      else if(VPTectWgKH == OuAOxSaXJP){DMBUlzIEUI = true;}
      if(KYUKnbKnHm == sgpCxREwnU){TJakEiFQEB = true;}
      else if(sgpCxREwnU == KYUKnbKnHm){UrjlchllUn = true;}
      if(XJqunuLRRJ == YMqAgmUtzw){VEcIrrFadh = true;}
      if(qIetHFxHXH == mPbjBoVYfR){RgGLyoMFdE = true;}
      if(zVxTfPpVNI == gtWbITBeYi){PVOCXGbojI = true;}
      while(YMqAgmUtzw == XJqunuLRRJ){JCLyseSDtx = true;}
      while(mPbjBoVYfR == mPbjBoVYfR){mdhziEOVhj = true;}
      while(gtWbITBeYi == gtWbITBeYi){LYetTdHuGV = true;}
      if(lTIZFJYSyp == true){lTIZFJYSyp = false;}
      if(ZbgOUdFGAI == true){ZbgOUdFGAI = false;}
      if(ufQWneoOqM == true){ufQWneoOqM = false;}
      if(kpVQKSHBdr == true){kpVQKSHBdr = false;}
      if(PCZorFMIHe == true){PCZorFMIHe = false;}
      if(OudQmFDlla == true){OudQmFDlla = false;}
      if(TJakEiFQEB == true){TJakEiFQEB = false;}
      if(VEcIrrFadh == true){VEcIrrFadh = false;}
      if(RgGLyoMFdE == true){RgGLyoMFdE = false;}
      if(PVOCXGbojI == true){PVOCXGbojI = false;}
      if(zwEGIJSUXt == true){zwEGIJSUXt = false;}
      if(zbHDJlDOmP == true){zbHDJlDOmP = false;}
      if(WAmzkAoZkl == true){WAmzkAoZkl = false;}
      if(QQpUiUcACn == true){QQpUiUcACn = false;}
      if(WqgiEmNLrk == true){WqgiEmNLrk = false;}
      if(DMBUlzIEUI == true){DMBUlzIEUI = false;}
      if(UrjlchllUn == true){UrjlchllUn = false;}
      if(JCLyseSDtx == true){JCLyseSDtx = false;}
      if(mdhziEOVhj == true){mdhziEOVhj = false;}
      if(LYetTdHuGV == true){LYetTdHuGV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCYEBSMWWG
{ 
  void eTdDsEUuEI()
  { 
      bool jSVGIHqnuI = false;
      bool lAhbuJSMAb = false;
      bool yIBxPGumre = false;
      bool LSjVDshMoF = false;
      bool rEpTQNOfPl = false;
      bool yizTDbRYpC = false;
      bool MDuQxTQLYC = false;
      bool aGWtisRhfC = false;
      bool rOWFfbTQRa = false;
      bool aJVmsoJYVx = false;
      bool xCHNLqMEjK = false;
      bool JjsnJyfokV = false;
      bool zztxaQjjBt = false;
      bool jsLhEoGJto = false;
      bool POfGQqQgct = false;
      bool ITnzxxHKlt = false;
      bool HbCpZQXKjU = false;
      bool rWuuGjSmfi = false;
      bool ACGGlQFLkG = false;
      bool guWzgmMpgA = false;
      string RptQEABgln;
      string VnyhNrnMaq;
      string xLAyNPUOdr;
      string wcERKrPhyx;
      string bMSgYTBtEs;
      string tDzCWFpwCn;
      string emDtqsigWU;
      string cGNcOjsSYs;
      string OZJjxrcCtF;
      string BTeKRoJYpf;
      string kTWjQnpVnl;
      string LWWIYFcSwy;
      string PfmRSIaDKZ;
      string aUcsIuCZTI;
      string CHNHsewWkM;
      string LpbqQEfFQH;
      string NlKOLqtdAd;
      string DDznuHSfXn;
      string LESyNjrlbD;
      string OwILuQwzuC;
      if(RptQEABgln == kTWjQnpVnl){jSVGIHqnuI = true;}
      else if(kTWjQnpVnl == RptQEABgln){xCHNLqMEjK = true;}
      if(VnyhNrnMaq == LWWIYFcSwy){lAhbuJSMAb = true;}
      else if(LWWIYFcSwy == VnyhNrnMaq){JjsnJyfokV = true;}
      if(xLAyNPUOdr == PfmRSIaDKZ){yIBxPGumre = true;}
      else if(PfmRSIaDKZ == xLAyNPUOdr){zztxaQjjBt = true;}
      if(wcERKrPhyx == aUcsIuCZTI){LSjVDshMoF = true;}
      else if(aUcsIuCZTI == wcERKrPhyx){jsLhEoGJto = true;}
      if(bMSgYTBtEs == CHNHsewWkM){rEpTQNOfPl = true;}
      else if(CHNHsewWkM == bMSgYTBtEs){POfGQqQgct = true;}
      if(tDzCWFpwCn == LpbqQEfFQH){yizTDbRYpC = true;}
      else if(LpbqQEfFQH == tDzCWFpwCn){ITnzxxHKlt = true;}
      if(emDtqsigWU == NlKOLqtdAd){MDuQxTQLYC = true;}
      else if(NlKOLqtdAd == emDtqsigWU){HbCpZQXKjU = true;}
      if(cGNcOjsSYs == DDznuHSfXn){aGWtisRhfC = true;}
      if(OZJjxrcCtF == LESyNjrlbD){rOWFfbTQRa = true;}
      if(BTeKRoJYpf == OwILuQwzuC){aJVmsoJYVx = true;}
      while(DDznuHSfXn == cGNcOjsSYs){rWuuGjSmfi = true;}
      while(LESyNjrlbD == LESyNjrlbD){ACGGlQFLkG = true;}
      while(OwILuQwzuC == OwILuQwzuC){guWzgmMpgA = true;}
      if(jSVGIHqnuI == true){jSVGIHqnuI = false;}
      if(lAhbuJSMAb == true){lAhbuJSMAb = false;}
      if(yIBxPGumre == true){yIBxPGumre = false;}
      if(LSjVDshMoF == true){LSjVDshMoF = false;}
      if(rEpTQNOfPl == true){rEpTQNOfPl = false;}
      if(yizTDbRYpC == true){yizTDbRYpC = false;}
      if(MDuQxTQLYC == true){MDuQxTQLYC = false;}
      if(aGWtisRhfC == true){aGWtisRhfC = false;}
      if(rOWFfbTQRa == true){rOWFfbTQRa = false;}
      if(aJVmsoJYVx == true){aJVmsoJYVx = false;}
      if(xCHNLqMEjK == true){xCHNLqMEjK = false;}
      if(JjsnJyfokV == true){JjsnJyfokV = false;}
      if(zztxaQjjBt == true){zztxaQjjBt = false;}
      if(jsLhEoGJto == true){jsLhEoGJto = false;}
      if(POfGQqQgct == true){POfGQqQgct = false;}
      if(ITnzxxHKlt == true){ITnzxxHKlt = false;}
      if(HbCpZQXKjU == true){HbCpZQXKjU = false;}
      if(rWuuGjSmfi == true){rWuuGjSmfi = false;}
      if(ACGGlQFLkG == true){ACGGlQFLkG = false;}
      if(guWzgmMpgA == true){guWzgmMpgA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJDKAMXEFE
{ 
  void NiAWFqhAbw()
  { 
      bool nKoyqfzNDD = false;
      bool lszKZuwYcY = false;
      bool IoyfgBSIIY = false;
      bool beqgtMwBNh = false;
      bool gKtuZkLQSs = false;
      bool qyhiRzLJQp = false;
      bool MpEebGBSPN = false;
      bool ytLtrytDFu = false;
      bool pCoOhcxIPu = false;
      bool AmjWVpFPTS = false;
      bool irAFtwmmpS = false;
      bool FIDUAKBowy = false;
      bool JsDUMLJnYB = false;
      bool sdjlMxBjTl = false;
      bool oJRworiOWL = false;
      bool oPSUJoofri = false;
      bool lzOnZaXQIC = false;
      bool JQVKJAbGeU = false;
      bool cuQNMcKPcW = false;
      bool HVrkApucWO = false;
      string AEBoyFOfeg;
      string BXZhAqZzhP;
      string YZZyCqqWYs;
      string uMxNxJIxyt;
      string izOyruQFwI;
      string ZGZNMadDlH;
      string NqGklnaMkp;
      string ibAmgZLbFH;
      string ZkaPSomiAV;
      string eEKqfqrcME;
      string TDUFZxFlgm;
      string OCyegcQqSw;
      string BrMOLdRJHo;
      string ghOBmVQVoU;
      string jBCNHbGfJD;
      string aBKQCbqGtw;
      string fwdqFgmwqL;
      string LuBxMzpyHi;
      string WkzEOfXyyL;
      string dKbsnmXKHZ;
      if(AEBoyFOfeg == TDUFZxFlgm){nKoyqfzNDD = true;}
      else if(TDUFZxFlgm == AEBoyFOfeg){irAFtwmmpS = true;}
      if(BXZhAqZzhP == OCyegcQqSw){lszKZuwYcY = true;}
      else if(OCyegcQqSw == BXZhAqZzhP){FIDUAKBowy = true;}
      if(YZZyCqqWYs == BrMOLdRJHo){IoyfgBSIIY = true;}
      else if(BrMOLdRJHo == YZZyCqqWYs){JsDUMLJnYB = true;}
      if(uMxNxJIxyt == ghOBmVQVoU){beqgtMwBNh = true;}
      else if(ghOBmVQVoU == uMxNxJIxyt){sdjlMxBjTl = true;}
      if(izOyruQFwI == jBCNHbGfJD){gKtuZkLQSs = true;}
      else if(jBCNHbGfJD == izOyruQFwI){oJRworiOWL = true;}
      if(ZGZNMadDlH == aBKQCbqGtw){qyhiRzLJQp = true;}
      else if(aBKQCbqGtw == ZGZNMadDlH){oPSUJoofri = true;}
      if(NqGklnaMkp == fwdqFgmwqL){MpEebGBSPN = true;}
      else if(fwdqFgmwqL == NqGklnaMkp){lzOnZaXQIC = true;}
      if(ibAmgZLbFH == LuBxMzpyHi){ytLtrytDFu = true;}
      if(ZkaPSomiAV == WkzEOfXyyL){pCoOhcxIPu = true;}
      if(eEKqfqrcME == dKbsnmXKHZ){AmjWVpFPTS = true;}
      while(LuBxMzpyHi == ibAmgZLbFH){JQVKJAbGeU = true;}
      while(WkzEOfXyyL == WkzEOfXyyL){cuQNMcKPcW = true;}
      while(dKbsnmXKHZ == dKbsnmXKHZ){HVrkApucWO = true;}
      if(nKoyqfzNDD == true){nKoyqfzNDD = false;}
      if(lszKZuwYcY == true){lszKZuwYcY = false;}
      if(IoyfgBSIIY == true){IoyfgBSIIY = false;}
      if(beqgtMwBNh == true){beqgtMwBNh = false;}
      if(gKtuZkLQSs == true){gKtuZkLQSs = false;}
      if(qyhiRzLJQp == true){qyhiRzLJQp = false;}
      if(MpEebGBSPN == true){MpEebGBSPN = false;}
      if(ytLtrytDFu == true){ytLtrytDFu = false;}
      if(pCoOhcxIPu == true){pCoOhcxIPu = false;}
      if(AmjWVpFPTS == true){AmjWVpFPTS = false;}
      if(irAFtwmmpS == true){irAFtwmmpS = false;}
      if(FIDUAKBowy == true){FIDUAKBowy = false;}
      if(JsDUMLJnYB == true){JsDUMLJnYB = false;}
      if(sdjlMxBjTl == true){sdjlMxBjTl = false;}
      if(oJRworiOWL == true){oJRworiOWL = false;}
      if(oPSUJoofri == true){oPSUJoofri = false;}
      if(lzOnZaXQIC == true){lzOnZaXQIC = false;}
      if(JQVKJAbGeU == true){JQVKJAbGeU = false;}
      if(cuQNMcKPcW == true){cuQNMcKPcW = false;}
      if(HVrkApucWO == true){HVrkApucWO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUNIJKGXZO
{ 
  void GMaZOfHCOa()
  { 
      bool xSwdVLhBGE = false;
      bool nfqYrXmrPP = false;
      bool SxeJdKJssc = false;
      bool TGfAAQFYQC = false;
      bool kIyxDVWuar = false;
      bool qtbjLAmmzL = false;
      bool BoIcjhzqXb = false;
      bool ROaNeJyhFI = false;
      bool mORAlYdwnA = false;
      bool cSYFAwAUNV = false;
      bool WeWzZcTOFB = false;
      bool CFgqXmWHqK = false;
      bool DDCXyyoVMh = false;
      bool JcTjlIqSaI = false;
      bool FPpmyWlggN = false;
      bool ZsdCRSbzAb = false;
      bool nxBXqYkxFP = false;
      bool uDghEnMPYa = false;
      bool MHozIQzRRS = false;
      bool frRyUINSuY = false;
      string RCkgFpuJdF;
      string qeyPjKULuQ;
      string puOrQSnJrR;
      string AiFAaLjrrG;
      string yVTzsfawtk;
      string CYCASWmrPl;
      string BkQMFHZyoX;
      string ZbTnRTaOzk;
      string qrOHOagFhD;
      string YrbFFMFHtl;
      string GcHWKZFOiy;
      string wXseuJWJxd;
      string ZUPkzhzNiE;
      string OTUMdOjrwo;
      string VSViHAyxKu;
      string puJPLlMVXb;
      string ZqedicCfBf;
      string YdNIIHygdy;
      string iCDmNTJFBq;
      string BOUTPemrAd;
      if(RCkgFpuJdF == GcHWKZFOiy){xSwdVLhBGE = true;}
      else if(GcHWKZFOiy == RCkgFpuJdF){WeWzZcTOFB = true;}
      if(qeyPjKULuQ == wXseuJWJxd){nfqYrXmrPP = true;}
      else if(wXseuJWJxd == qeyPjKULuQ){CFgqXmWHqK = true;}
      if(puOrQSnJrR == ZUPkzhzNiE){SxeJdKJssc = true;}
      else if(ZUPkzhzNiE == puOrQSnJrR){DDCXyyoVMh = true;}
      if(AiFAaLjrrG == OTUMdOjrwo){TGfAAQFYQC = true;}
      else if(OTUMdOjrwo == AiFAaLjrrG){JcTjlIqSaI = true;}
      if(yVTzsfawtk == VSViHAyxKu){kIyxDVWuar = true;}
      else if(VSViHAyxKu == yVTzsfawtk){FPpmyWlggN = true;}
      if(CYCASWmrPl == puJPLlMVXb){qtbjLAmmzL = true;}
      else if(puJPLlMVXb == CYCASWmrPl){ZsdCRSbzAb = true;}
      if(BkQMFHZyoX == ZqedicCfBf){BoIcjhzqXb = true;}
      else if(ZqedicCfBf == BkQMFHZyoX){nxBXqYkxFP = true;}
      if(ZbTnRTaOzk == YdNIIHygdy){ROaNeJyhFI = true;}
      if(qrOHOagFhD == iCDmNTJFBq){mORAlYdwnA = true;}
      if(YrbFFMFHtl == BOUTPemrAd){cSYFAwAUNV = true;}
      while(YdNIIHygdy == ZbTnRTaOzk){uDghEnMPYa = true;}
      while(iCDmNTJFBq == iCDmNTJFBq){MHozIQzRRS = true;}
      while(BOUTPemrAd == BOUTPemrAd){frRyUINSuY = true;}
      if(xSwdVLhBGE == true){xSwdVLhBGE = false;}
      if(nfqYrXmrPP == true){nfqYrXmrPP = false;}
      if(SxeJdKJssc == true){SxeJdKJssc = false;}
      if(TGfAAQFYQC == true){TGfAAQFYQC = false;}
      if(kIyxDVWuar == true){kIyxDVWuar = false;}
      if(qtbjLAmmzL == true){qtbjLAmmzL = false;}
      if(BoIcjhzqXb == true){BoIcjhzqXb = false;}
      if(ROaNeJyhFI == true){ROaNeJyhFI = false;}
      if(mORAlYdwnA == true){mORAlYdwnA = false;}
      if(cSYFAwAUNV == true){cSYFAwAUNV = false;}
      if(WeWzZcTOFB == true){WeWzZcTOFB = false;}
      if(CFgqXmWHqK == true){CFgqXmWHqK = false;}
      if(DDCXyyoVMh == true){DDCXyyoVMh = false;}
      if(JcTjlIqSaI == true){JcTjlIqSaI = false;}
      if(FPpmyWlggN == true){FPpmyWlggN = false;}
      if(ZsdCRSbzAb == true){ZsdCRSbzAb = false;}
      if(nxBXqYkxFP == true){nxBXqYkxFP = false;}
      if(uDghEnMPYa == true){uDghEnMPYa = false;}
      if(MHozIQzRRS == true){MHozIQzRRS = false;}
      if(frRyUINSuY == true){frRyUINSuY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHWOXECUMF
{ 
  void ZwsLutuzzj()
  { 
      bool ryouUeBWHr = false;
      bool nsxyQgpdAI = false;
      bool hkJRZEXyzq = false;
      bool KTlStaNsTd = false;
      bool GLxRzrwJTn = false;
      bool HWpPwHnXVP = false;
      bool GCXQhTGeDo = false;
      bool TxKWBWnrRh = false;
      bool HOdKindWVm = false;
      bool loWDWEnfje = false;
      bool kRFdUKMSNZ = false;
      bool SwGmIrXMhs = false;
      bool ojIQDdZGzx = false;
      bool hHHlwpIApX = false;
      bool bKIwToijue = false;
      bool fayppAIoZp = false;
      bool kFTQqLnTpR = false;
      bool iXVJRdaMwO = false;
      bool upKUQHIRwu = false;
      bool gTZAmVqrEI = false;
      string DJthkXqFVw;
      string MEpDkhMxpY;
      string uVALtsELnH;
      string bkPrVklawb;
      string RKeiLyBXIe;
      string TZplthJinq;
      string TeRNTanyhz;
      string wkAOHkqQzw;
      string rfDInCudym;
      string bDmFHmrQOj;
      string JDpJihYadI;
      string qrjrznaIZR;
      string fKztWsytHU;
      string rZBOlnotZF;
      string cTzowiTuGS;
      string LjqwEyDulp;
      string jeSJQQpUFK;
      string yfiToLKKym;
      string YDnnIIiEKm;
      string ktIjUyBpXe;
      if(DJthkXqFVw == JDpJihYadI){ryouUeBWHr = true;}
      else if(JDpJihYadI == DJthkXqFVw){kRFdUKMSNZ = true;}
      if(MEpDkhMxpY == qrjrznaIZR){nsxyQgpdAI = true;}
      else if(qrjrznaIZR == MEpDkhMxpY){SwGmIrXMhs = true;}
      if(uVALtsELnH == fKztWsytHU){hkJRZEXyzq = true;}
      else if(fKztWsytHU == uVALtsELnH){ojIQDdZGzx = true;}
      if(bkPrVklawb == rZBOlnotZF){KTlStaNsTd = true;}
      else if(rZBOlnotZF == bkPrVklawb){hHHlwpIApX = true;}
      if(RKeiLyBXIe == cTzowiTuGS){GLxRzrwJTn = true;}
      else if(cTzowiTuGS == RKeiLyBXIe){bKIwToijue = true;}
      if(TZplthJinq == LjqwEyDulp){HWpPwHnXVP = true;}
      else if(LjqwEyDulp == TZplthJinq){fayppAIoZp = true;}
      if(TeRNTanyhz == jeSJQQpUFK){GCXQhTGeDo = true;}
      else if(jeSJQQpUFK == TeRNTanyhz){kFTQqLnTpR = true;}
      if(wkAOHkqQzw == yfiToLKKym){TxKWBWnrRh = true;}
      if(rfDInCudym == YDnnIIiEKm){HOdKindWVm = true;}
      if(bDmFHmrQOj == ktIjUyBpXe){loWDWEnfje = true;}
      while(yfiToLKKym == wkAOHkqQzw){iXVJRdaMwO = true;}
      while(YDnnIIiEKm == YDnnIIiEKm){upKUQHIRwu = true;}
      while(ktIjUyBpXe == ktIjUyBpXe){gTZAmVqrEI = true;}
      if(ryouUeBWHr == true){ryouUeBWHr = false;}
      if(nsxyQgpdAI == true){nsxyQgpdAI = false;}
      if(hkJRZEXyzq == true){hkJRZEXyzq = false;}
      if(KTlStaNsTd == true){KTlStaNsTd = false;}
      if(GLxRzrwJTn == true){GLxRzrwJTn = false;}
      if(HWpPwHnXVP == true){HWpPwHnXVP = false;}
      if(GCXQhTGeDo == true){GCXQhTGeDo = false;}
      if(TxKWBWnrRh == true){TxKWBWnrRh = false;}
      if(HOdKindWVm == true){HOdKindWVm = false;}
      if(loWDWEnfje == true){loWDWEnfje = false;}
      if(kRFdUKMSNZ == true){kRFdUKMSNZ = false;}
      if(SwGmIrXMhs == true){SwGmIrXMhs = false;}
      if(ojIQDdZGzx == true){ojIQDdZGzx = false;}
      if(hHHlwpIApX == true){hHHlwpIApX = false;}
      if(bKIwToijue == true){bKIwToijue = false;}
      if(fayppAIoZp == true){fayppAIoZp = false;}
      if(kFTQqLnTpR == true){kFTQqLnTpR = false;}
      if(iXVJRdaMwO == true){iXVJRdaMwO = false;}
      if(upKUQHIRwu == true){upKUQHIRwu = false;}
      if(gTZAmVqrEI == true){gTZAmVqrEI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGFDXOSXHK
{ 
  void ZZslhPMbyr()
  { 
      bool XkNZfCxSIk = false;
      bool XrTJYpsYHs = false;
      bool UsLfMfPirB = false;
      bool osxIakEEZM = false;
      bool OjpQDjFiuj = false;
      bool qHrLodZhMA = false;
      bool mNZHweuKim = false;
      bool lnytekDtbc = false;
      bool agmIKgBkSw = false;
      bool LVqZZAJhUY = false;
      bool otzIyCJxgD = false;
      bool aeGjYFaRxO = false;
      bool dJrmaPwYUd = false;
      bool bUYDmfgeJH = false;
      bool XDEOUfPHAT = false;
      bool ZrkGteCMgh = false;
      bool FjbCbGFDxs = false;
      bool YwHopZFcSu = false;
      bool AoXAEjiSIH = false;
      bool dUxaBmbBmN = false;
      string nPZOaBjpUs;
      string RtUeikIBNt;
      string CzuEnfjFpm;
      string WALdiUrxaT;
      string zUVMFOzjiJ;
      string HtRrAoUVZu;
      string QeAhWQiqwN;
      string rKatthciyY;
      string gAVgebiTdt;
      string AWWeCTUnoo;
      string fInUQwTWxS;
      string LkXBOQJTCt;
      string hONBNVnurZ;
      string MnsJsXLAPi;
      string ILWKhOzVQk;
      string KBltGQulHu;
      string IXeWFXqNHp;
      string FIDTlVrCSy;
      string WReGPLCyCb;
      string cYrUajgzFK;
      if(nPZOaBjpUs == fInUQwTWxS){XkNZfCxSIk = true;}
      else if(fInUQwTWxS == nPZOaBjpUs){otzIyCJxgD = true;}
      if(RtUeikIBNt == LkXBOQJTCt){XrTJYpsYHs = true;}
      else if(LkXBOQJTCt == RtUeikIBNt){aeGjYFaRxO = true;}
      if(CzuEnfjFpm == hONBNVnurZ){UsLfMfPirB = true;}
      else if(hONBNVnurZ == CzuEnfjFpm){dJrmaPwYUd = true;}
      if(WALdiUrxaT == MnsJsXLAPi){osxIakEEZM = true;}
      else if(MnsJsXLAPi == WALdiUrxaT){bUYDmfgeJH = true;}
      if(zUVMFOzjiJ == ILWKhOzVQk){OjpQDjFiuj = true;}
      else if(ILWKhOzVQk == zUVMFOzjiJ){XDEOUfPHAT = true;}
      if(HtRrAoUVZu == KBltGQulHu){qHrLodZhMA = true;}
      else if(KBltGQulHu == HtRrAoUVZu){ZrkGteCMgh = true;}
      if(QeAhWQiqwN == IXeWFXqNHp){mNZHweuKim = true;}
      else if(IXeWFXqNHp == QeAhWQiqwN){FjbCbGFDxs = true;}
      if(rKatthciyY == FIDTlVrCSy){lnytekDtbc = true;}
      if(gAVgebiTdt == WReGPLCyCb){agmIKgBkSw = true;}
      if(AWWeCTUnoo == cYrUajgzFK){LVqZZAJhUY = true;}
      while(FIDTlVrCSy == rKatthciyY){YwHopZFcSu = true;}
      while(WReGPLCyCb == WReGPLCyCb){AoXAEjiSIH = true;}
      while(cYrUajgzFK == cYrUajgzFK){dUxaBmbBmN = true;}
      if(XkNZfCxSIk == true){XkNZfCxSIk = false;}
      if(XrTJYpsYHs == true){XrTJYpsYHs = false;}
      if(UsLfMfPirB == true){UsLfMfPirB = false;}
      if(osxIakEEZM == true){osxIakEEZM = false;}
      if(OjpQDjFiuj == true){OjpQDjFiuj = false;}
      if(qHrLodZhMA == true){qHrLodZhMA = false;}
      if(mNZHweuKim == true){mNZHweuKim = false;}
      if(lnytekDtbc == true){lnytekDtbc = false;}
      if(agmIKgBkSw == true){agmIKgBkSw = false;}
      if(LVqZZAJhUY == true){LVqZZAJhUY = false;}
      if(otzIyCJxgD == true){otzIyCJxgD = false;}
      if(aeGjYFaRxO == true){aeGjYFaRxO = false;}
      if(dJrmaPwYUd == true){dJrmaPwYUd = false;}
      if(bUYDmfgeJH == true){bUYDmfgeJH = false;}
      if(XDEOUfPHAT == true){XDEOUfPHAT = false;}
      if(ZrkGteCMgh == true){ZrkGteCMgh = false;}
      if(FjbCbGFDxs == true){FjbCbGFDxs = false;}
      if(YwHopZFcSu == true){YwHopZFcSu = false;}
      if(AoXAEjiSIH == true){AoXAEjiSIH = false;}
      if(dUxaBmbBmN == true){dUxaBmbBmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQNKOXFPDU
{ 
  void dHrWbiYfqk()
  { 
      bool YVMVdsJeXF = false;
      bool RtDZwgrFDH = false;
      bool blgMlVxFLs = false;
      bool guttstsubT = false;
      bool PSOWEGBgsF = false;
      bool ssrabmoAjI = false;
      bool uETdXWzJfB = false;
      bool mwdiqIXJHe = false;
      bool UPLFAnCTRG = false;
      bool ErLTXLzjyh = false;
      bool GqAqRwOJiT = false;
      bool OerEmerNdi = false;
      bool TfqZxtjKKf = false;
      bool JnKZXcPUnD = false;
      bool ZsjyqYzHfr = false;
      bool TkFPOZAatW = false;
      bool MDyDJaUSfK = false;
      bool PXZZJZwrhX = false;
      bool uceSLXhuKx = false;
      bool coZQqVufoQ = false;
      string sYFGIrKOGB;
      string aSXSTKiCEc;
      string dPtrxNYwLT;
      string ACbIKqOTMG;
      string PCmcBEcmlD;
      string EYUnkdeNIt;
      string TNDmBYqOIc;
      string wOpyMbbQps;
      string kkJIPbgmXf;
      string LBLRmByAbc;
      string MNdJGphWaJ;
      string CNWPJhEuWY;
      string qDqbQuCYKK;
      string cboNfWGABY;
      string tKMOdxewHE;
      string xDcCkJWCsL;
      string mILQfZYIil;
      string aEtxefqbyS;
      string PGQFMYylbW;
      string AEGolkyuhD;
      if(sYFGIrKOGB == MNdJGphWaJ){YVMVdsJeXF = true;}
      else if(MNdJGphWaJ == sYFGIrKOGB){GqAqRwOJiT = true;}
      if(aSXSTKiCEc == CNWPJhEuWY){RtDZwgrFDH = true;}
      else if(CNWPJhEuWY == aSXSTKiCEc){OerEmerNdi = true;}
      if(dPtrxNYwLT == qDqbQuCYKK){blgMlVxFLs = true;}
      else if(qDqbQuCYKK == dPtrxNYwLT){TfqZxtjKKf = true;}
      if(ACbIKqOTMG == cboNfWGABY){guttstsubT = true;}
      else if(cboNfWGABY == ACbIKqOTMG){JnKZXcPUnD = true;}
      if(PCmcBEcmlD == tKMOdxewHE){PSOWEGBgsF = true;}
      else if(tKMOdxewHE == PCmcBEcmlD){ZsjyqYzHfr = true;}
      if(EYUnkdeNIt == xDcCkJWCsL){ssrabmoAjI = true;}
      else if(xDcCkJWCsL == EYUnkdeNIt){TkFPOZAatW = true;}
      if(TNDmBYqOIc == mILQfZYIil){uETdXWzJfB = true;}
      else if(mILQfZYIil == TNDmBYqOIc){MDyDJaUSfK = true;}
      if(wOpyMbbQps == aEtxefqbyS){mwdiqIXJHe = true;}
      if(kkJIPbgmXf == PGQFMYylbW){UPLFAnCTRG = true;}
      if(LBLRmByAbc == AEGolkyuhD){ErLTXLzjyh = true;}
      while(aEtxefqbyS == wOpyMbbQps){PXZZJZwrhX = true;}
      while(PGQFMYylbW == PGQFMYylbW){uceSLXhuKx = true;}
      while(AEGolkyuhD == AEGolkyuhD){coZQqVufoQ = true;}
      if(YVMVdsJeXF == true){YVMVdsJeXF = false;}
      if(RtDZwgrFDH == true){RtDZwgrFDH = false;}
      if(blgMlVxFLs == true){blgMlVxFLs = false;}
      if(guttstsubT == true){guttstsubT = false;}
      if(PSOWEGBgsF == true){PSOWEGBgsF = false;}
      if(ssrabmoAjI == true){ssrabmoAjI = false;}
      if(uETdXWzJfB == true){uETdXWzJfB = false;}
      if(mwdiqIXJHe == true){mwdiqIXJHe = false;}
      if(UPLFAnCTRG == true){UPLFAnCTRG = false;}
      if(ErLTXLzjyh == true){ErLTXLzjyh = false;}
      if(GqAqRwOJiT == true){GqAqRwOJiT = false;}
      if(OerEmerNdi == true){OerEmerNdi = false;}
      if(TfqZxtjKKf == true){TfqZxtjKKf = false;}
      if(JnKZXcPUnD == true){JnKZXcPUnD = false;}
      if(ZsjyqYzHfr == true){ZsjyqYzHfr = false;}
      if(TkFPOZAatW == true){TkFPOZAatW = false;}
      if(MDyDJaUSfK == true){MDyDJaUSfK = false;}
      if(PXZZJZwrhX == true){PXZZJZwrhX = false;}
      if(uceSLXhuKx == true){uceSLXhuKx = false;}
      if(coZQqVufoQ == true){coZQqVufoQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VAUPGLDGYN
{ 
  void JQGJbmbDlT()
  { 
      bool AoWnZkfItw = false;
      bool ahUSRWijMA = false;
      bool AqXjVlRwSr = false;
      bool bNPEOyQVsB = false;
      bool QkqzEOtKMS = false;
      bool ddywOIRmSm = false;
      bool SjoBUMRQES = false;
      bool GNqLjPAYeG = false;
      bool rHjAOyPToF = false;
      bool gcDFhgwodr = false;
      bool xcGsMQmmMz = false;
      bool IrHLtLAnmW = false;
      bool wxaylcKkcD = false;
      bool TKtlJPApny = false;
      bool LcHpxnVqKW = false;
      bool fHCHuzBIHi = false;
      bool GBJIfyyVBe = false;
      bool KJAoLTpkBx = false;
      bool HSZFWLHmqK = false;
      bool NrhEqJSyKz = false;
      string qQmYLNxDWw;
      string YMbsCGFHrp;
      string mCyELFiDEd;
      string OwAVCNuwXN;
      string iRSwYuJKPP;
      string tudYXnSiMG;
      string etzrgbLFqn;
      string KJidGVjBfQ;
      string uXmnjTSbxN;
      string uMiRinRZOw;
      string jDSaEjLzRC;
      string EQDwKGHKIN;
      string JiIdsyZRuS;
      string EKmifrELjz;
      string HSJuJdJmGb;
      string gGQAmAuohG;
      string JtEyytdTPS;
      string BuaIGpZNTO;
      string nmKTlxsluf;
      string wPddoNOLxP;
      if(qQmYLNxDWw == jDSaEjLzRC){AoWnZkfItw = true;}
      else if(jDSaEjLzRC == qQmYLNxDWw){xcGsMQmmMz = true;}
      if(YMbsCGFHrp == EQDwKGHKIN){ahUSRWijMA = true;}
      else if(EQDwKGHKIN == YMbsCGFHrp){IrHLtLAnmW = true;}
      if(mCyELFiDEd == JiIdsyZRuS){AqXjVlRwSr = true;}
      else if(JiIdsyZRuS == mCyELFiDEd){wxaylcKkcD = true;}
      if(OwAVCNuwXN == EKmifrELjz){bNPEOyQVsB = true;}
      else if(EKmifrELjz == OwAVCNuwXN){TKtlJPApny = true;}
      if(iRSwYuJKPP == HSJuJdJmGb){QkqzEOtKMS = true;}
      else if(HSJuJdJmGb == iRSwYuJKPP){LcHpxnVqKW = true;}
      if(tudYXnSiMG == gGQAmAuohG){ddywOIRmSm = true;}
      else if(gGQAmAuohG == tudYXnSiMG){fHCHuzBIHi = true;}
      if(etzrgbLFqn == JtEyytdTPS){SjoBUMRQES = true;}
      else if(JtEyytdTPS == etzrgbLFqn){GBJIfyyVBe = true;}
      if(KJidGVjBfQ == BuaIGpZNTO){GNqLjPAYeG = true;}
      if(uXmnjTSbxN == nmKTlxsluf){rHjAOyPToF = true;}
      if(uMiRinRZOw == wPddoNOLxP){gcDFhgwodr = true;}
      while(BuaIGpZNTO == KJidGVjBfQ){KJAoLTpkBx = true;}
      while(nmKTlxsluf == nmKTlxsluf){HSZFWLHmqK = true;}
      while(wPddoNOLxP == wPddoNOLxP){NrhEqJSyKz = true;}
      if(AoWnZkfItw == true){AoWnZkfItw = false;}
      if(ahUSRWijMA == true){ahUSRWijMA = false;}
      if(AqXjVlRwSr == true){AqXjVlRwSr = false;}
      if(bNPEOyQVsB == true){bNPEOyQVsB = false;}
      if(QkqzEOtKMS == true){QkqzEOtKMS = false;}
      if(ddywOIRmSm == true){ddywOIRmSm = false;}
      if(SjoBUMRQES == true){SjoBUMRQES = false;}
      if(GNqLjPAYeG == true){GNqLjPAYeG = false;}
      if(rHjAOyPToF == true){rHjAOyPToF = false;}
      if(gcDFhgwodr == true){gcDFhgwodr = false;}
      if(xcGsMQmmMz == true){xcGsMQmmMz = false;}
      if(IrHLtLAnmW == true){IrHLtLAnmW = false;}
      if(wxaylcKkcD == true){wxaylcKkcD = false;}
      if(TKtlJPApny == true){TKtlJPApny = false;}
      if(LcHpxnVqKW == true){LcHpxnVqKW = false;}
      if(fHCHuzBIHi == true){fHCHuzBIHi = false;}
      if(GBJIfyyVBe == true){GBJIfyyVBe = false;}
      if(KJAoLTpkBx == true){KJAoLTpkBx = false;}
      if(HSZFWLHmqK == true){HSZFWLHmqK = false;}
      if(NrhEqJSyKz == true){NrhEqJSyKz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBYKVLUUGS
{ 
  void Mbzmiawybi()
  { 
      bool utNuHRtDSU = false;
      bool agyPbFFaOl = false;
      bool wYrSwRylVx = false;
      bool kPtpAOfWmW = false;
      bool sGRuPBOUrp = false;
      bool KGIOfWBtyo = false;
      bool TIgVjKlIOM = false;
      bool YinrsoGwDu = false;
      bool DctfleGfJd = false;
      bool MkXxCkYwLE = false;
      bool OGGeQbSQVq = false;
      bool PEqDlqNAiF = false;
      bool EGyjAnKpoI = false;
      bool QKkzfxWOPK = false;
      bool LoKSOItUKL = false;
      bool WYNGzIHVec = false;
      bool QbbMaETrWo = false;
      bool UzjXsOwfVr = false;
      bool spfdkqxdzW = false;
      bool oBjmsiNxrJ = false;
      string KkikTwCqpr;
      string ORWnCdaYgu;
      string cNCDqUnKdV;
      string gljJRRybPE;
      string YZBxmKLpzc;
      string MafPSxifsz;
      string HqMUKbhMVk;
      string fyJcWCLFPf;
      string IyLBIGFTpT;
      string iSiQwgMglK;
      string byTOxOQCsP;
      string kcPMpJfLLE;
      string VOVCCMPsgo;
      string oeSFDKexEt;
      string oDaaiFDVal;
      string ABUhnNbRMj;
      string yXVDZGJJIe;
      string eiGROSmuSw;
      string IsRtnnJkQp;
      string hMkTuQgXAc;
      if(KkikTwCqpr == byTOxOQCsP){utNuHRtDSU = true;}
      else if(byTOxOQCsP == KkikTwCqpr){OGGeQbSQVq = true;}
      if(ORWnCdaYgu == kcPMpJfLLE){agyPbFFaOl = true;}
      else if(kcPMpJfLLE == ORWnCdaYgu){PEqDlqNAiF = true;}
      if(cNCDqUnKdV == VOVCCMPsgo){wYrSwRylVx = true;}
      else if(VOVCCMPsgo == cNCDqUnKdV){EGyjAnKpoI = true;}
      if(gljJRRybPE == oeSFDKexEt){kPtpAOfWmW = true;}
      else if(oeSFDKexEt == gljJRRybPE){QKkzfxWOPK = true;}
      if(YZBxmKLpzc == oDaaiFDVal){sGRuPBOUrp = true;}
      else if(oDaaiFDVal == YZBxmKLpzc){LoKSOItUKL = true;}
      if(MafPSxifsz == ABUhnNbRMj){KGIOfWBtyo = true;}
      else if(ABUhnNbRMj == MafPSxifsz){WYNGzIHVec = true;}
      if(HqMUKbhMVk == yXVDZGJJIe){TIgVjKlIOM = true;}
      else if(yXVDZGJJIe == HqMUKbhMVk){QbbMaETrWo = true;}
      if(fyJcWCLFPf == eiGROSmuSw){YinrsoGwDu = true;}
      if(IyLBIGFTpT == IsRtnnJkQp){DctfleGfJd = true;}
      if(iSiQwgMglK == hMkTuQgXAc){MkXxCkYwLE = true;}
      while(eiGROSmuSw == fyJcWCLFPf){UzjXsOwfVr = true;}
      while(IsRtnnJkQp == IsRtnnJkQp){spfdkqxdzW = true;}
      while(hMkTuQgXAc == hMkTuQgXAc){oBjmsiNxrJ = true;}
      if(utNuHRtDSU == true){utNuHRtDSU = false;}
      if(agyPbFFaOl == true){agyPbFFaOl = false;}
      if(wYrSwRylVx == true){wYrSwRylVx = false;}
      if(kPtpAOfWmW == true){kPtpAOfWmW = false;}
      if(sGRuPBOUrp == true){sGRuPBOUrp = false;}
      if(KGIOfWBtyo == true){KGIOfWBtyo = false;}
      if(TIgVjKlIOM == true){TIgVjKlIOM = false;}
      if(YinrsoGwDu == true){YinrsoGwDu = false;}
      if(DctfleGfJd == true){DctfleGfJd = false;}
      if(MkXxCkYwLE == true){MkXxCkYwLE = false;}
      if(OGGeQbSQVq == true){OGGeQbSQVq = false;}
      if(PEqDlqNAiF == true){PEqDlqNAiF = false;}
      if(EGyjAnKpoI == true){EGyjAnKpoI = false;}
      if(QKkzfxWOPK == true){QKkzfxWOPK = false;}
      if(LoKSOItUKL == true){LoKSOItUKL = false;}
      if(WYNGzIHVec == true){WYNGzIHVec = false;}
      if(QbbMaETrWo == true){QbbMaETrWo = false;}
      if(UzjXsOwfVr == true){UzjXsOwfVr = false;}
      if(spfdkqxdzW == true){spfdkqxdzW = false;}
      if(oBjmsiNxrJ == true){oBjmsiNxrJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQBGBXIYOW
{ 
  void icWNyLaDYm()
  { 
      bool XbQCAbYhBd = false;
      bool kRudqpBxlf = false;
      bool LzdfgAgOMm = false;
      bool jBLQRHHEjI = false;
      bool UutgkWNtrW = false;
      bool QWFQpYykVA = false;
      bool tKUOsjFeLj = false;
      bool hxMdKQFxtJ = false;
      bool lmVpVMutas = false;
      bool IWhjNJZemB = false;
      bool QiiHoTJbFZ = false;
      bool SAqLNHoerf = false;
      bool nKDSaLOcPA = false;
      bool pZKssDEOAC = false;
      bool DToBZIfVWG = false;
      bool UtmGNFePfd = false;
      bool EgMEisoxRJ = false;
      bool DaeocTVCrS = false;
      bool esFIfulDfn = false;
      bool XnhWxWHjSf = false;
      string UGciSjnOAb;
      string nzDVeOnqNr;
      string fuTMnRCWQN;
      string jznIrEOUGZ;
      string wfydeyzDCc;
      string bWRksYmPtA;
      string gQymrnLudZ;
      string ATknwAxoho;
      string SyTnkMgDPS;
      string RyZGsehKlp;
      string mEZbbIldnr;
      string bygFhhxJCe;
      string HHeKIBseuR;
      string RlCrCNYqLb;
      string ZDOWqSRUXK;
      string gXIGheZOSa;
      string OHiWZouoDU;
      string JFyZFEsHSo;
      string iYGkjtduKW;
      string nJXjMRUrwB;
      if(UGciSjnOAb == mEZbbIldnr){XbQCAbYhBd = true;}
      else if(mEZbbIldnr == UGciSjnOAb){QiiHoTJbFZ = true;}
      if(nzDVeOnqNr == bygFhhxJCe){kRudqpBxlf = true;}
      else if(bygFhhxJCe == nzDVeOnqNr){SAqLNHoerf = true;}
      if(fuTMnRCWQN == HHeKIBseuR){LzdfgAgOMm = true;}
      else if(HHeKIBseuR == fuTMnRCWQN){nKDSaLOcPA = true;}
      if(jznIrEOUGZ == RlCrCNYqLb){jBLQRHHEjI = true;}
      else if(RlCrCNYqLb == jznIrEOUGZ){pZKssDEOAC = true;}
      if(wfydeyzDCc == ZDOWqSRUXK){UutgkWNtrW = true;}
      else if(ZDOWqSRUXK == wfydeyzDCc){DToBZIfVWG = true;}
      if(bWRksYmPtA == gXIGheZOSa){QWFQpYykVA = true;}
      else if(gXIGheZOSa == bWRksYmPtA){UtmGNFePfd = true;}
      if(gQymrnLudZ == OHiWZouoDU){tKUOsjFeLj = true;}
      else if(OHiWZouoDU == gQymrnLudZ){EgMEisoxRJ = true;}
      if(ATknwAxoho == JFyZFEsHSo){hxMdKQFxtJ = true;}
      if(SyTnkMgDPS == iYGkjtduKW){lmVpVMutas = true;}
      if(RyZGsehKlp == nJXjMRUrwB){IWhjNJZemB = true;}
      while(JFyZFEsHSo == ATknwAxoho){DaeocTVCrS = true;}
      while(iYGkjtduKW == iYGkjtduKW){esFIfulDfn = true;}
      while(nJXjMRUrwB == nJXjMRUrwB){XnhWxWHjSf = true;}
      if(XbQCAbYhBd == true){XbQCAbYhBd = false;}
      if(kRudqpBxlf == true){kRudqpBxlf = false;}
      if(LzdfgAgOMm == true){LzdfgAgOMm = false;}
      if(jBLQRHHEjI == true){jBLQRHHEjI = false;}
      if(UutgkWNtrW == true){UutgkWNtrW = false;}
      if(QWFQpYykVA == true){QWFQpYykVA = false;}
      if(tKUOsjFeLj == true){tKUOsjFeLj = false;}
      if(hxMdKQFxtJ == true){hxMdKQFxtJ = false;}
      if(lmVpVMutas == true){lmVpVMutas = false;}
      if(IWhjNJZemB == true){IWhjNJZemB = false;}
      if(QiiHoTJbFZ == true){QiiHoTJbFZ = false;}
      if(SAqLNHoerf == true){SAqLNHoerf = false;}
      if(nKDSaLOcPA == true){nKDSaLOcPA = false;}
      if(pZKssDEOAC == true){pZKssDEOAC = false;}
      if(DToBZIfVWG == true){DToBZIfVWG = false;}
      if(UtmGNFePfd == true){UtmGNFePfd = false;}
      if(EgMEisoxRJ == true){EgMEisoxRJ = false;}
      if(DaeocTVCrS == true){DaeocTVCrS = false;}
      if(esFIfulDfn == true){esFIfulDfn = false;}
      if(XnhWxWHjSf == true){XnhWxWHjSf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGNSCIKDYG
{ 
  void DLZgMBdPPr()
  { 
      bool DjugJdCrsG = false;
      bool sFObLSnzIl = false;
      bool OsVtRMmDdg = false;
      bool HezyYiMkgu = false;
      bool abASYSbHMb = false;
      bool NpFbZJNAOx = false;
      bool qzNMzOFQDb = false;
      bool GDRMLlsCVy = false;
      bool kepBSQZXYO = false;
      bool ULVjDbNmTJ = false;
      bool NKEkVKXrQm = false;
      bool QKeQMMIMth = false;
      bool ohrnGughJj = false;
      bool XGiLkZZFfI = false;
      bool sgGkyKgFXq = false;
      bool TBslUeSQda = false;
      bool coifOKbTel = false;
      bool lCfknHaGpw = false;
      bool NbKSQWMxpG = false;
      bool GJbFeDyaVm = false;
      string kPTtDOgbyr;
      string epwLcrNnVV;
      string qRLmxPPJPr;
      string ueyyKGmXsI;
      string jWSSeRKLwi;
      string fpGttSDgxm;
      string zXLGxzrxAW;
      string FpuMlTysHe;
      string EDNgLEXDEq;
      string CFaFJLKMVe;
      string ZMKYdpusIZ;
      string UKYRhwKeur;
      string bnsJTzPoDa;
      string JlWcErrnCV;
      string IeueWqfIWM;
      string AeRcDlTBEd;
      string ZGohQimwNp;
      string DWbYiwrNlc;
      string SHRpZdTtZS;
      string YqjYuCoNOn;
      if(kPTtDOgbyr == ZMKYdpusIZ){DjugJdCrsG = true;}
      else if(ZMKYdpusIZ == kPTtDOgbyr){NKEkVKXrQm = true;}
      if(epwLcrNnVV == UKYRhwKeur){sFObLSnzIl = true;}
      else if(UKYRhwKeur == epwLcrNnVV){QKeQMMIMth = true;}
      if(qRLmxPPJPr == bnsJTzPoDa){OsVtRMmDdg = true;}
      else if(bnsJTzPoDa == qRLmxPPJPr){ohrnGughJj = true;}
      if(ueyyKGmXsI == JlWcErrnCV){HezyYiMkgu = true;}
      else if(JlWcErrnCV == ueyyKGmXsI){XGiLkZZFfI = true;}
      if(jWSSeRKLwi == IeueWqfIWM){abASYSbHMb = true;}
      else if(IeueWqfIWM == jWSSeRKLwi){sgGkyKgFXq = true;}
      if(fpGttSDgxm == AeRcDlTBEd){NpFbZJNAOx = true;}
      else if(AeRcDlTBEd == fpGttSDgxm){TBslUeSQda = true;}
      if(zXLGxzrxAW == ZGohQimwNp){qzNMzOFQDb = true;}
      else if(ZGohQimwNp == zXLGxzrxAW){coifOKbTel = true;}
      if(FpuMlTysHe == DWbYiwrNlc){GDRMLlsCVy = true;}
      if(EDNgLEXDEq == SHRpZdTtZS){kepBSQZXYO = true;}
      if(CFaFJLKMVe == YqjYuCoNOn){ULVjDbNmTJ = true;}
      while(DWbYiwrNlc == FpuMlTysHe){lCfknHaGpw = true;}
      while(SHRpZdTtZS == SHRpZdTtZS){NbKSQWMxpG = true;}
      while(YqjYuCoNOn == YqjYuCoNOn){GJbFeDyaVm = true;}
      if(DjugJdCrsG == true){DjugJdCrsG = false;}
      if(sFObLSnzIl == true){sFObLSnzIl = false;}
      if(OsVtRMmDdg == true){OsVtRMmDdg = false;}
      if(HezyYiMkgu == true){HezyYiMkgu = false;}
      if(abASYSbHMb == true){abASYSbHMb = false;}
      if(NpFbZJNAOx == true){NpFbZJNAOx = false;}
      if(qzNMzOFQDb == true){qzNMzOFQDb = false;}
      if(GDRMLlsCVy == true){GDRMLlsCVy = false;}
      if(kepBSQZXYO == true){kepBSQZXYO = false;}
      if(ULVjDbNmTJ == true){ULVjDbNmTJ = false;}
      if(NKEkVKXrQm == true){NKEkVKXrQm = false;}
      if(QKeQMMIMth == true){QKeQMMIMth = false;}
      if(ohrnGughJj == true){ohrnGughJj = false;}
      if(XGiLkZZFfI == true){XGiLkZZFfI = false;}
      if(sgGkyKgFXq == true){sgGkyKgFXq = false;}
      if(TBslUeSQda == true){TBslUeSQda = false;}
      if(coifOKbTel == true){coifOKbTel = false;}
      if(lCfknHaGpw == true){lCfknHaGpw = false;}
      if(NbKSQWMxpG == true){NbKSQWMxpG = false;}
      if(GJbFeDyaVm == true){GJbFeDyaVm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OZFTGJGFJL
{ 
  void TwjMCIMpCj()
  { 
      bool nAoZzENeAI = false;
      bool WpjYMTtCkZ = false;
      bool VgdmZFyATG = false;
      bool YOUhdtCRTk = false;
      bool UYrsdaRZiA = false;
      bool ltfpcHVCzs = false;
      bool FNLsjHUBtS = false;
      bool RbizFwnkJz = false;
      bool nYRSTeheFV = false;
      bool XzRZeHNyJV = false;
      bool FPePhJKfkf = false;
      bool TksAFgurZF = false;
      bool ZpwYtSJJUx = false;
      bool iobmsXtCkK = false;
      bool TBtYCmFRUy = false;
      bool MUYDuPTGUP = false;
      bool zBLmxdIFGg = false;
      bool lrHOkXwWVH = false;
      bool MqnVkNPXrd = false;
      bool EngUKSoGaY = false;
      string pCibeFgePe;
      string cHcKqWiZGV;
      string EfcXCNohqi;
      string OXRmgrDtRy;
      string nzUGYTezVD;
      string VCGCIJZKZR;
      string PzngQFppcy;
      string ToIIhFLVzh;
      string hoMmMLQOdW;
      string SrUAhoLmpS;
      string doWWigtxUD;
      string yELqjalATE;
      string oaMFfbUHar;
      string tXefDsSoDf;
      string RTtZYNfcQH;
      string CKSldDbQqH;
      string LlWbJZZfmp;
      string HxwnlVglgR;
      string uqqTpiErBA;
      string QByuTfwRQy;
      if(pCibeFgePe == doWWigtxUD){nAoZzENeAI = true;}
      else if(doWWigtxUD == pCibeFgePe){FPePhJKfkf = true;}
      if(cHcKqWiZGV == yELqjalATE){WpjYMTtCkZ = true;}
      else if(yELqjalATE == cHcKqWiZGV){TksAFgurZF = true;}
      if(EfcXCNohqi == oaMFfbUHar){VgdmZFyATG = true;}
      else if(oaMFfbUHar == EfcXCNohqi){ZpwYtSJJUx = true;}
      if(OXRmgrDtRy == tXefDsSoDf){YOUhdtCRTk = true;}
      else if(tXefDsSoDf == OXRmgrDtRy){iobmsXtCkK = true;}
      if(nzUGYTezVD == RTtZYNfcQH){UYrsdaRZiA = true;}
      else if(RTtZYNfcQH == nzUGYTezVD){TBtYCmFRUy = true;}
      if(VCGCIJZKZR == CKSldDbQqH){ltfpcHVCzs = true;}
      else if(CKSldDbQqH == VCGCIJZKZR){MUYDuPTGUP = true;}
      if(PzngQFppcy == LlWbJZZfmp){FNLsjHUBtS = true;}
      else if(LlWbJZZfmp == PzngQFppcy){zBLmxdIFGg = true;}
      if(ToIIhFLVzh == HxwnlVglgR){RbizFwnkJz = true;}
      if(hoMmMLQOdW == uqqTpiErBA){nYRSTeheFV = true;}
      if(SrUAhoLmpS == QByuTfwRQy){XzRZeHNyJV = true;}
      while(HxwnlVglgR == ToIIhFLVzh){lrHOkXwWVH = true;}
      while(uqqTpiErBA == uqqTpiErBA){MqnVkNPXrd = true;}
      while(QByuTfwRQy == QByuTfwRQy){EngUKSoGaY = true;}
      if(nAoZzENeAI == true){nAoZzENeAI = false;}
      if(WpjYMTtCkZ == true){WpjYMTtCkZ = false;}
      if(VgdmZFyATG == true){VgdmZFyATG = false;}
      if(YOUhdtCRTk == true){YOUhdtCRTk = false;}
      if(UYrsdaRZiA == true){UYrsdaRZiA = false;}
      if(ltfpcHVCzs == true){ltfpcHVCzs = false;}
      if(FNLsjHUBtS == true){FNLsjHUBtS = false;}
      if(RbizFwnkJz == true){RbizFwnkJz = false;}
      if(nYRSTeheFV == true){nYRSTeheFV = false;}
      if(XzRZeHNyJV == true){XzRZeHNyJV = false;}
      if(FPePhJKfkf == true){FPePhJKfkf = false;}
      if(TksAFgurZF == true){TksAFgurZF = false;}
      if(ZpwYtSJJUx == true){ZpwYtSJJUx = false;}
      if(iobmsXtCkK == true){iobmsXtCkK = false;}
      if(TBtYCmFRUy == true){TBtYCmFRUy = false;}
      if(MUYDuPTGUP == true){MUYDuPTGUP = false;}
      if(zBLmxdIFGg == true){zBLmxdIFGg = false;}
      if(lrHOkXwWVH == true){lrHOkXwWVH = false;}
      if(MqnVkNPXrd == true){MqnVkNPXrd = false;}
      if(EngUKSoGaY == true){EngUKSoGaY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWCFOYPZQO
{ 
  void trskufpqOA()
  { 
      bool TXRZJRfpOz = false;
      bool FiYpLaoHco = false;
      bool UAnGZkKXGD = false;
      bool zagMfsJZRr = false;
      bool nwEVUlBJaa = false;
      bool LUrihSiLzY = false;
      bool GHiLzdBLKR = false;
      bool QPpjAXwRkn = false;
      bool jBwfqeiydM = false;
      bool JyZskfNrWq = false;
      bool jozIJweHhK = false;
      bool WRZLnFLCUU = false;
      bool tChxHSowyT = false;
      bool KDutDuCmWt = false;
      bool AaPTorXNEf = false;
      bool ULXBwgGBAp = false;
      bool HhJNzSVfIs = false;
      bool DXeZUSmNHP = false;
      bool taqSzzftxV = false;
      bool nAlgmRRBTW = false;
      string uXmVwZHqnz;
      string yKoasJhKlL;
      string SEMOdFXlTs;
      string DPWzuHQzQu;
      string xpGKztStRX;
      string LDWnxqKYrq;
      string CUXuuhnpel;
      string shspOcxCPi;
      string lcUuhAshCE;
      string xrHYsbRLOQ;
      string GcOeecJfZT;
      string sIIIEYAbMu;
      string oFmaoAaUwl;
      string KkmybJNpQE;
      string pMIhKoiyUU;
      string bpyTbBonpd;
      string CojmJHUKgt;
      string KJKIEbwFPA;
      string RbzbKTmTVZ;
      string UZzmBBcUXD;
      if(uXmVwZHqnz == GcOeecJfZT){TXRZJRfpOz = true;}
      else if(GcOeecJfZT == uXmVwZHqnz){jozIJweHhK = true;}
      if(yKoasJhKlL == sIIIEYAbMu){FiYpLaoHco = true;}
      else if(sIIIEYAbMu == yKoasJhKlL){WRZLnFLCUU = true;}
      if(SEMOdFXlTs == oFmaoAaUwl){UAnGZkKXGD = true;}
      else if(oFmaoAaUwl == SEMOdFXlTs){tChxHSowyT = true;}
      if(DPWzuHQzQu == KkmybJNpQE){zagMfsJZRr = true;}
      else if(KkmybJNpQE == DPWzuHQzQu){KDutDuCmWt = true;}
      if(xpGKztStRX == pMIhKoiyUU){nwEVUlBJaa = true;}
      else if(pMIhKoiyUU == xpGKztStRX){AaPTorXNEf = true;}
      if(LDWnxqKYrq == bpyTbBonpd){LUrihSiLzY = true;}
      else if(bpyTbBonpd == LDWnxqKYrq){ULXBwgGBAp = true;}
      if(CUXuuhnpel == CojmJHUKgt){GHiLzdBLKR = true;}
      else if(CojmJHUKgt == CUXuuhnpel){HhJNzSVfIs = true;}
      if(shspOcxCPi == KJKIEbwFPA){QPpjAXwRkn = true;}
      if(lcUuhAshCE == RbzbKTmTVZ){jBwfqeiydM = true;}
      if(xrHYsbRLOQ == UZzmBBcUXD){JyZskfNrWq = true;}
      while(KJKIEbwFPA == shspOcxCPi){DXeZUSmNHP = true;}
      while(RbzbKTmTVZ == RbzbKTmTVZ){taqSzzftxV = true;}
      while(UZzmBBcUXD == UZzmBBcUXD){nAlgmRRBTW = true;}
      if(TXRZJRfpOz == true){TXRZJRfpOz = false;}
      if(FiYpLaoHco == true){FiYpLaoHco = false;}
      if(UAnGZkKXGD == true){UAnGZkKXGD = false;}
      if(zagMfsJZRr == true){zagMfsJZRr = false;}
      if(nwEVUlBJaa == true){nwEVUlBJaa = false;}
      if(LUrihSiLzY == true){LUrihSiLzY = false;}
      if(GHiLzdBLKR == true){GHiLzdBLKR = false;}
      if(QPpjAXwRkn == true){QPpjAXwRkn = false;}
      if(jBwfqeiydM == true){jBwfqeiydM = false;}
      if(JyZskfNrWq == true){JyZskfNrWq = false;}
      if(jozIJweHhK == true){jozIJweHhK = false;}
      if(WRZLnFLCUU == true){WRZLnFLCUU = false;}
      if(tChxHSowyT == true){tChxHSowyT = false;}
      if(KDutDuCmWt == true){KDutDuCmWt = false;}
      if(AaPTorXNEf == true){AaPTorXNEf = false;}
      if(ULXBwgGBAp == true){ULXBwgGBAp = false;}
      if(HhJNzSVfIs == true){HhJNzSVfIs = false;}
      if(DXeZUSmNHP == true){DXeZUSmNHP = false;}
      if(taqSzzftxV == true){taqSzzftxV = false;}
      if(nAlgmRRBTW == true){nAlgmRRBTW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCLNQDWXNB
{ 
  void zkIDZUWESg()
  { 
      bool eUnQXXejYc = false;
      bool LzqtgEmhio = false;
      bool wGAoZMMlia = false;
      bool JyWDsrUlMy = false;
      bool KJLZNyhesm = false;
      bool AKaCVXTyqK = false;
      bool LrBxTMcmAn = false;
      bool jAVjdltabb = false;
      bool egrwZzWThU = false;
      bool XVuBmRIOFA = false;
      bool VteFCznqXi = false;
      bool dsVOeezEXU = false;
      bool oIEfQNFTxL = false;
      bool cfUbGjCmsa = false;
      bool KfuypezfVI = false;
      bool SEpkLMpyoo = false;
      bool tUsMGyXtIt = false;
      bool bLLwJIMFok = false;
      bool OYxosYoiPs = false;
      bool tDyEgplirr = false;
      string zzjJWyWZjQ;
      string GoXldickFm;
      string WCiQMbAqmZ;
      string MQLECAgGTd;
      string SNDhkYRZoi;
      string uApHVwPTwt;
      string xelKDpdSid;
      string BVRaUJzBen;
      string KaCDdMaDhF;
      string jNKYfmardu;
      string typKhYiOmM;
      string xOnHjWcifq;
      string OZjdsmLrtg;
      string hGWjsLkqVF;
      string cMQVIVZCoJ;
      string KrLlfUNMRt;
      string NpTFdpqEOX;
      string llNaNCJOVX;
      string NIDkWotkDY;
      string xYZaqmsKqR;
      if(zzjJWyWZjQ == typKhYiOmM){eUnQXXejYc = true;}
      else if(typKhYiOmM == zzjJWyWZjQ){VteFCznqXi = true;}
      if(GoXldickFm == xOnHjWcifq){LzqtgEmhio = true;}
      else if(xOnHjWcifq == GoXldickFm){dsVOeezEXU = true;}
      if(WCiQMbAqmZ == OZjdsmLrtg){wGAoZMMlia = true;}
      else if(OZjdsmLrtg == WCiQMbAqmZ){oIEfQNFTxL = true;}
      if(MQLECAgGTd == hGWjsLkqVF){JyWDsrUlMy = true;}
      else if(hGWjsLkqVF == MQLECAgGTd){cfUbGjCmsa = true;}
      if(SNDhkYRZoi == cMQVIVZCoJ){KJLZNyhesm = true;}
      else if(cMQVIVZCoJ == SNDhkYRZoi){KfuypezfVI = true;}
      if(uApHVwPTwt == KrLlfUNMRt){AKaCVXTyqK = true;}
      else if(KrLlfUNMRt == uApHVwPTwt){SEpkLMpyoo = true;}
      if(xelKDpdSid == NpTFdpqEOX){LrBxTMcmAn = true;}
      else if(NpTFdpqEOX == xelKDpdSid){tUsMGyXtIt = true;}
      if(BVRaUJzBen == llNaNCJOVX){jAVjdltabb = true;}
      if(KaCDdMaDhF == NIDkWotkDY){egrwZzWThU = true;}
      if(jNKYfmardu == xYZaqmsKqR){XVuBmRIOFA = true;}
      while(llNaNCJOVX == BVRaUJzBen){bLLwJIMFok = true;}
      while(NIDkWotkDY == NIDkWotkDY){OYxosYoiPs = true;}
      while(xYZaqmsKqR == xYZaqmsKqR){tDyEgplirr = true;}
      if(eUnQXXejYc == true){eUnQXXejYc = false;}
      if(LzqtgEmhio == true){LzqtgEmhio = false;}
      if(wGAoZMMlia == true){wGAoZMMlia = false;}
      if(JyWDsrUlMy == true){JyWDsrUlMy = false;}
      if(KJLZNyhesm == true){KJLZNyhesm = false;}
      if(AKaCVXTyqK == true){AKaCVXTyqK = false;}
      if(LrBxTMcmAn == true){LrBxTMcmAn = false;}
      if(jAVjdltabb == true){jAVjdltabb = false;}
      if(egrwZzWThU == true){egrwZzWThU = false;}
      if(XVuBmRIOFA == true){XVuBmRIOFA = false;}
      if(VteFCznqXi == true){VteFCznqXi = false;}
      if(dsVOeezEXU == true){dsVOeezEXU = false;}
      if(oIEfQNFTxL == true){oIEfQNFTxL = false;}
      if(cfUbGjCmsa == true){cfUbGjCmsa = false;}
      if(KfuypezfVI == true){KfuypezfVI = false;}
      if(SEpkLMpyoo == true){SEpkLMpyoo = false;}
      if(tUsMGyXtIt == true){tUsMGyXtIt = false;}
      if(bLLwJIMFok == true){bLLwJIMFok = false;}
      if(OYxosYoiPs == true){OYxosYoiPs = false;}
      if(tDyEgplirr == true){tDyEgplirr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUEDBPTAAU
{ 
  void HxUpXByFLG()
  { 
      bool PgOwjRihpU = false;
      bool uUDOOxKtNk = false;
      bool pthcFuVLcy = false;
      bool ZrWayDMApd = false;
      bool FVRmzUucNJ = false;
      bool LuQeDVylqn = false;
      bool wXFqtCxcPK = false;
      bool jKEifTbucj = false;
      bool ArySlearXc = false;
      bool EaJBghQZrw = false;
      bool XSMCYBqgyi = false;
      bool sDIGnEYlEP = false;
      bool aEEmGJBCCx = false;
      bool DBCfMgewtk = false;
      bool ntsniARCNc = false;
      bool IdVcUSNZwO = false;
      bool AneAfqBcsG = false;
      bool YcqTbgLQEF = false;
      bool qyoYoYfZLt = false;
      bool TFAejAPsHq = false;
      string xORFBfKtaY;
      string UZWxADUjVM;
      string hZQdmaGAxp;
      string xJuPejrlKU;
      string XiTlXDrAXQ;
      string VVZYlXynSa;
      string YJwkaLeHRQ;
      string KhYAnzFdFj;
      string hGbgTajWdH;
      string kETjwNliLM;
      string YkiHFmwYjm;
      string RThhrRhOQA;
      string aIdJeGNoEa;
      string MWSsKxXUag;
      string eKlpoQVlrd;
      string eWRLkQHYbz;
      string ZHUIauBoWu;
      string tNnjUQVmUN;
      string jbxZuoEHHt;
      string oyrbGWpdPs;
      if(xORFBfKtaY == YkiHFmwYjm){PgOwjRihpU = true;}
      else if(YkiHFmwYjm == xORFBfKtaY){XSMCYBqgyi = true;}
      if(UZWxADUjVM == RThhrRhOQA){uUDOOxKtNk = true;}
      else if(RThhrRhOQA == UZWxADUjVM){sDIGnEYlEP = true;}
      if(hZQdmaGAxp == aIdJeGNoEa){pthcFuVLcy = true;}
      else if(aIdJeGNoEa == hZQdmaGAxp){aEEmGJBCCx = true;}
      if(xJuPejrlKU == MWSsKxXUag){ZrWayDMApd = true;}
      else if(MWSsKxXUag == xJuPejrlKU){DBCfMgewtk = true;}
      if(XiTlXDrAXQ == eKlpoQVlrd){FVRmzUucNJ = true;}
      else if(eKlpoQVlrd == XiTlXDrAXQ){ntsniARCNc = true;}
      if(VVZYlXynSa == eWRLkQHYbz){LuQeDVylqn = true;}
      else if(eWRLkQHYbz == VVZYlXynSa){IdVcUSNZwO = true;}
      if(YJwkaLeHRQ == ZHUIauBoWu){wXFqtCxcPK = true;}
      else if(ZHUIauBoWu == YJwkaLeHRQ){AneAfqBcsG = true;}
      if(KhYAnzFdFj == tNnjUQVmUN){jKEifTbucj = true;}
      if(hGbgTajWdH == jbxZuoEHHt){ArySlearXc = true;}
      if(kETjwNliLM == oyrbGWpdPs){EaJBghQZrw = true;}
      while(tNnjUQVmUN == KhYAnzFdFj){YcqTbgLQEF = true;}
      while(jbxZuoEHHt == jbxZuoEHHt){qyoYoYfZLt = true;}
      while(oyrbGWpdPs == oyrbGWpdPs){TFAejAPsHq = true;}
      if(PgOwjRihpU == true){PgOwjRihpU = false;}
      if(uUDOOxKtNk == true){uUDOOxKtNk = false;}
      if(pthcFuVLcy == true){pthcFuVLcy = false;}
      if(ZrWayDMApd == true){ZrWayDMApd = false;}
      if(FVRmzUucNJ == true){FVRmzUucNJ = false;}
      if(LuQeDVylqn == true){LuQeDVylqn = false;}
      if(wXFqtCxcPK == true){wXFqtCxcPK = false;}
      if(jKEifTbucj == true){jKEifTbucj = false;}
      if(ArySlearXc == true){ArySlearXc = false;}
      if(EaJBghQZrw == true){EaJBghQZrw = false;}
      if(XSMCYBqgyi == true){XSMCYBqgyi = false;}
      if(sDIGnEYlEP == true){sDIGnEYlEP = false;}
      if(aEEmGJBCCx == true){aEEmGJBCCx = false;}
      if(DBCfMgewtk == true){DBCfMgewtk = false;}
      if(ntsniARCNc == true){ntsniARCNc = false;}
      if(IdVcUSNZwO == true){IdVcUSNZwO = false;}
      if(AneAfqBcsG == true){AneAfqBcsG = false;}
      if(YcqTbgLQEF == true){YcqTbgLQEF = false;}
      if(qyoYoYfZLt == true){qyoYoYfZLt = false;}
      if(TFAejAPsHq == true){TFAejAPsHq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCKROFYBZI
{ 
  void JgqLNVUwDf()
  { 
      bool ZjweKdKpnR = false;
      bool yzupUljlZm = false;
      bool rFJfdrpbGU = false;
      bool hCRGZGXxpp = false;
      bool xaafDysIHP = false;
      bool RGxttTaPBR = false;
      bool niiSiwhoPN = false;
      bool NmwioQeccf = false;
      bool zgTqDbFWLG = false;
      bool fIwXCOrIxH = false;
      bool PEssCdKNFc = false;
      bool nylVRGOrPH = false;
      bool pLcJhFqXfa = false;
      bool YWeUPtnZnY = false;
      bool RqRiRgVZFu = false;
      bool zAspQEbiLx = false;
      bool mlgdERSRGX = false;
      bool SnDppzttqA = false;
      bool iQRkaYdoEK = false;
      bool SEOqleJmeA = false;
      string jplmXYBbie;
      string xDMwsxZCRo;
      string KbWBoXEwAF;
      string ehQogIZlhW;
      string DhtyMAyuUR;
      string rRYStISkxz;
      string TFadAOmWPj;
      string WnTtkcgXnn;
      string YJaiMNJxtY;
      string oooiCyGQyx;
      string NafktEydgR;
      string auxJaKerQm;
      string Fobqthzkrm;
      string WQZpaxconH;
      string PeQcxtqeIq;
      string SOzLrXznpL;
      string FMlsuKUHic;
      string goDJXaYzsA;
      string qTcATHROxC;
      string ynzbCCrWhm;
      if(jplmXYBbie == NafktEydgR){ZjweKdKpnR = true;}
      else if(NafktEydgR == jplmXYBbie){PEssCdKNFc = true;}
      if(xDMwsxZCRo == auxJaKerQm){yzupUljlZm = true;}
      else if(auxJaKerQm == xDMwsxZCRo){nylVRGOrPH = true;}
      if(KbWBoXEwAF == Fobqthzkrm){rFJfdrpbGU = true;}
      else if(Fobqthzkrm == KbWBoXEwAF){pLcJhFqXfa = true;}
      if(ehQogIZlhW == WQZpaxconH){hCRGZGXxpp = true;}
      else if(WQZpaxconH == ehQogIZlhW){YWeUPtnZnY = true;}
      if(DhtyMAyuUR == PeQcxtqeIq){xaafDysIHP = true;}
      else if(PeQcxtqeIq == DhtyMAyuUR){RqRiRgVZFu = true;}
      if(rRYStISkxz == SOzLrXznpL){RGxttTaPBR = true;}
      else if(SOzLrXznpL == rRYStISkxz){zAspQEbiLx = true;}
      if(TFadAOmWPj == FMlsuKUHic){niiSiwhoPN = true;}
      else if(FMlsuKUHic == TFadAOmWPj){mlgdERSRGX = true;}
      if(WnTtkcgXnn == goDJXaYzsA){NmwioQeccf = true;}
      if(YJaiMNJxtY == qTcATHROxC){zgTqDbFWLG = true;}
      if(oooiCyGQyx == ynzbCCrWhm){fIwXCOrIxH = true;}
      while(goDJXaYzsA == WnTtkcgXnn){SnDppzttqA = true;}
      while(qTcATHROxC == qTcATHROxC){iQRkaYdoEK = true;}
      while(ynzbCCrWhm == ynzbCCrWhm){SEOqleJmeA = true;}
      if(ZjweKdKpnR == true){ZjweKdKpnR = false;}
      if(yzupUljlZm == true){yzupUljlZm = false;}
      if(rFJfdrpbGU == true){rFJfdrpbGU = false;}
      if(hCRGZGXxpp == true){hCRGZGXxpp = false;}
      if(xaafDysIHP == true){xaafDysIHP = false;}
      if(RGxttTaPBR == true){RGxttTaPBR = false;}
      if(niiSiwhoPN == true){niiSiwhoPN = false;}
      if(NmwioQeccf == true){NmwioQeccf = false;}
      if(zgTqDbFWLG == true){zgTqDbFWLG = false;}
      if(fIwXCOrIxH == true){fIwXCOrIxH = false;}
      if(PEssCdKNFc == true){PEssCdKNFc = false;}
      if(nylVRGOrPH == true){nylVRGOrPH = false;}
      if(pLcJhFqXfa == true){pLcJhFqXfa = false;}
      if(YWeUPtnZnY == true){YWeUPtnZnY = false;}
      if(RqRiRgVZFu == true){RqRiRgVZFu = false;}
      if(zAspQEbiLx == true){zAspQEbiLx = false;}
      if(mlgdERSRGX == true){mlgdERSRGX = false;}
      if(SnDppzttqA == true){SnDppzttqA = false;}
      if(iQRkaYdoEK == true){iQRkaYdoEK = false;}
      if(SEOqleJmeA == true){SEOqleJmeA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRFJTIKILL
{ 
  void tCpnejsAQb()
  { 
      bool QxiEaiwGow = false;
      bool uhuGlrztNu = false;
      bool wjiwChDymQ = false;
      bool iQRNQGdgwj = false;
      bool LqLzBJUOgk = false;
      bool KJQMpfNlCr = false;
      bool fySYMeQhof = false;
      bool OSydjFXjtr = false;
      bool NoRCGYzEWj = false;
      bool rreDENXmlV = false;
      bool rmYAWqLmck = false;
      bool IdqJepfQRn = false;
      bool fMKFmVnuZW = false;
      bool hkxXzaQQfO = false;
      bool MMalbOAUXN = false;
      bool gGUypfbTNA = false;
      bool DQMGDWfSJE = false;
      bool ZPkDaSkYcY = false;
      bool VTWLoaPzhT = false;
      bool ywDeLwAUhE = false;
      string MrwfJHGgJG;
      string fUDpEqkRcU;
      string NzhMKRCrXd;
      string RktcKPWhmr;
      string DzEbnXVKMq;
      string yAAZoMJiVr;
      string ENIenuaZfo;
      string TDekRNuFYl;
      string wrfgeRkTmy;
      string FmMtmpqYns;
      string xudWWuVOIa;
      string QDKiuMgbAW;
      string JGlhigpjxa;
      string WWRenBNIJi;
      string uVLMgCcczZ;
      string IOYQiqIwnp;
      string FkRgDtkett;
      string zYRRamuZAg;
      string DMkWSIyBux;
      string rQUTdKEdIm;
      if(MrwfJHGgJG == xudWWuVOIa){QxiEaiwGow = true;}
      else if(xudWWuVOIa == MrwfJHGgJG){rmYAWqLmck = true;}
      if(fUDpEqkRcU == QDKiuMgbAW){uhuGlrztNu = true;}
      else if(QDKiuMgbAW == fUDpEqkRcU){IdqJepfQRn = true;}
      if(NzhMKRCrXd == JGlhigpjxa){wjiwChDymQ = true;}
      else if(JGlhigpjxa == NzhMKRCrXd){fMKFmVnuZW = true;}
      if(RktcKPWhmr == WWRenBNIJi){iQRNQGdgwj = true;}
      else if(WWRenBNIJi == RktcKPWhmr){hkxXzaQQfO = true;}
      if(DzEbnXVKMq == uVLMgCcczZ){LqLzBJUOgk = true;}
      else if(uVLMgCcczZ == DzEbnXVKMq){MMalbOAUXN = true;}
      if(yAAZoMJiVr == IOYQiqIwnp){KJQMpfNlCr = true;}
      else if(IOYQiqIwnp == yAAZoMJiVr){gGUypfbTNA = true;}
      if(ENIenuaZfo == FkRgDtkett){fySYMeQhof = true;}
      else if(FkRgDtkett == ENIenuaZfo){DQMGDWfSJE = true;}
      if(TDekRNuFYl == zYRRamuZAg){OSydjFXjtr = true;}
      if(wrfgeRkTmy == DMkWSIyBux){NoRCGYzEWj = true;}
      if(FmMtmpqYns == rQUTdKEdIm){rreDENXmlV = true;}
      while(zYRRamuZAg == TDekRNuFYl){ZPkDaSkYcY = true;}
      while(DMkWSIyBux == DMkWSIyBux){VTWLoaPzhT = true;}
      while(rQUTdKEdIm == rQUTdKEdIm){ywDeLwAUhE = true;}
      if(QxiEaiwGow == true){QxiEaiwGow = false;}
      if(uhuGlrztNu == true){uhuGlrztNu = false;}
      if(wjiwChDymQ == true){wjiwChDymQ = false;}
      if(iQRNQGdgwj == true){iQRNQGdgwj = false;}
      if(LqLzBJUOgk == true){LqLzBJUOgk = false;}
      if(KJQMpfNlCr == true){KJQMpfNlCr = false;}
      if(fySYMeQhof == true){fySYMeQhof = false;}
      if(OSydjFXjtr == true){OSydjFXjtr = false;}
      if(NoRCGYzEWj == true){NoRCGYzEWj = false;}
      if(rreDENXmlV == true){rreDENXmlV = false;}
      if(rmYAWqLmck == true){rmYAWqLmck = false;}
      if(IdqJepfQRn == true){IdqJepfQRn = false;}
      if(fMKFmVnuZW == true){fMKFmVnuZW = false;}
      if(hkxXzaQQfO == true){hkxXzaQQfO = false;}
      if(MMalbOAUXN == true){MMalbOAUXN = false;}
      if(gGUypfbTNA == true){gGUypfbTNA = false;}
      if(DQMGDWfSJE == true){DQMGDWfSJE = false;}
      if(ZPkDaSkYcY == true){ZPkDaSkYcY = false;}
      if(VTWLoaPzhT == true){VTWLoaPzhT = false;}
      if(ywDeLwAUhE == true){ywDeLwAUhE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKFQXEOCIU
{ 
  void UCFDaCPKKp()
  { 
      bool OhsZFfKxOi = false;
      bool SiwOVhuHfL = false;
      bool wOJVwmILJC = false;
      bool QcGWPHlBxo = false;
      bool nHwKNfMmUk = false;
      bool czhSJzYWcS = false;
      bool WzmLRobZzN = false;
      bool wtKpWnSyHQ = false;
      bool aUpYZQunMP = false;
      bool hOXdRoUjsY = false;
      bool DlnGnioquV = false;
      bool fZOMrBINkB = false;
      bool tnNifgVfYh = false;
      bool SiFiMngjjq = false;
      bool bEsqjIALlP = false;
      bool fHyqePYEaH = false;
      bool MJSMCxTeAE = false;
      bool UXctZouWzW = false;
      bool gKtIBLjNEx = false;
      bool ObJcdRkfnl = false;
      string URkzYAKnBG;
      string RbpIkUEqqT;
      string fZcdADcyxX;
      string FowGiEznAE;
      string KFLObtcjqI;
      string EaEVutoHzU;
      string XMqcBcfjYg;
      string UQqlJZNNBF;
      string asGoTekaKn;
      string OroegxOiMz;
      string OrKKmniRMV;
      string faFsteGCIW;
      string rFYkRbaMFL;
      string LeBBphiuBf;
      string uTNnHnlukC;
      string qLZpHJTZsK;
      string MWLAKBZECL;
      string wLBcaYqjcd;
      string oeaDUzFKtg;
      string OICpSXHNdG;
      if(URkzYAKnBG == OrKKmniRMV){OhsZFfKxOi = true;}
      else if(OrKKmniRMV == URkzYAKnBG){DlnGnioquV = true;}
      if(RbpIkUEqqT == faFsteGCIW){SiwOVhuHfL = true;}
      else if(faFsteGCIW == RbpIkUEqqT){fZOMrBINkB = true;}
      if(fZcdADcyxX == rFYkRbaMFL){wOJVwmILJC = true;}
      else if(rFYkRbaMFL == fZcdADcyxX){tnNifgVfYh = true;}
      if(FowGiEznAE == LeBBphiuBf){QcGWPHlBxo = true;}
      else if(LeBBphiuBf == FowGiEznAE){SiFiMngjjq = true;}
      if(KFLObtcjqI == uTNnHnlukC){nHwKNfMmUk = true;}
      else if(uTNnHnlukC == KFLObtcjqI){bEsqjIALlP = true;}
      if(EaEVutoHzU == qLZpHJTZsK){czhSJzYWcS = true;}
      else if(qLZpHJTZsK == EaEVutoHzU){fHyqePYEaH = true;}
      if(XMqcBcfjYg == MWLAKBZECL){WzmLRobZzN = true;}
      else if(MWLAKBZECL == XMqcBcfjYg){MJSMCxTeAE = true;}
      if(UQqlJZNNBF == wLBcaYqjcd){wtKpWnSyHQ = true;}
      if(asGoTekaKn == oeaDUzFKtg){aUpYZQunMP = true;}
      if(OroegxOiMz == OICpSXHNdG){hOXdRoUjsY = true;}
      while(wLBcaYqjcd == UQqlJZNNBF){UXctZouWzW = true;}
      while(oeaDUzFKtg == oeaDUzFKtg){gKtIBLjNEx = true;}
      while(OICpSXHNdG == OICpSXHNdG){ObJcdRkfnl = true;}
      if(OhsZFfKxOi == true){OhsZFfKxOi = false;}
      if(SiwOVhuHfL == true){SiwOVhuHfL = false;}
      if(wOJVwmILJC == true){wOJVwmILJC = false;}
      if(QcGWPHlBxo == true){QcGWPHlBxo = false;}
      if(nHwKNfMmUk == true){nHwKNfMmUk = false;}
      if(czhSJzYWcS == true){czhSJzYWcS = false;}
      if(WzmLRobZzN == true){WzmLRobZzN = false;}
      if(wtKpWnSyHQ == true){wtKpWnSyHQ = false;}
      if(aUpYZQunMP == true){aUpYZQunMP = false;}
      if(hOXdRoUjsY == true){hOXdRoUjsY = false;}
      if(DlnGnioquV == true){DlnGnioquV = false;}
      if(fZOMrBINkB == true){fZOMrBINkB = false;}
      if(tnNifgVfYh == true){tnNifgVfYh = false;}
      if(SiFiMngjjq == true){SiFiMngjjq = false;}
      if(bEsqjIALlP == true){bEsqjIALlP = false;}
      if(fHyqePYEaH == true){fHyqePYEaH = false;}
      if(MJSMCxTeAE == true){MJSMCxTeAE = false;}
      if(UXctZouWzW == true){UXctZouWzW = false;}
      if(gKtIBLjNEx == true){gKtIBLjNEx = false;}
      if(ObJcdRkfnl == true){ObJcdRkfnl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZOMQEYWVA
{ 
  void IARLyfPDui()
  { 
      bool xrYlhxyphD = false;
      bool AJrIYLdTYu = false;
      bool NAAZlIYoKJ = false;
      bool BdEUJancWf = false;
      bool oADjWQfZgq = false;
      bool eKjQWxrzAY = false;
      bool XIfXBVEWyy = false;
      bool WAxrFMxPCV = false;
      bool czITeqtnyM = false;
      bool iocxHgUehA = false;
      bool LIbiTdNqKJ = false;
      bool AbwewYzMsK = false;
      bool bPYkOhXzkY = false;
      bool qRhCJTXZzA = false;
      bool dCdoMGsxBi = false;
      bool hIlXYujpTl = false;
      bool GNGlRhttUb = false;
      bool BYMrgYliYI = false;
      bool nZyCpifJcN = false;
      bool jgGNtPwqWe = false;
      string KomcCURNjU;
      string FMaZggwjcM;
      string yPJmYBzHaH;
      string oaVAlkqhLo;
      string TaXBxcNhCi;
      string WffbnteAEA;
      string VJlbedqZmw;
      string pNYmrWrIow;
      string nREqkJusMr;
      string FpdKTKouVS;
      string kmtGrIHriQ;
      string CWKHMEFupV;
      string ixMupziNTh;
      string hwlWKAWyzc;
      string CCKupifVyO;
      string EtEAimayPs;
      string ZsYBiFkmxL;
      string gHuNSfmQFH;
      string TNPEcnqkmW;
      string ZYhFDIdIMj;
      if(KomcCURNjU == kmtGrIHriQ){xrYlhxyphD = true;}
      else if(kmtGrIHriQ == KomcCURNjU){LIbiTdNqKJ = true;}
      if(FMaZggwjcM == CWKHMEFupV){AJrIYLdTYu = true;}
      else if(CWKHMEFupV == FMaZggwjcM){AbwewYzMsK = true;}
      if(yPJmYBzHaH == ixMupziNTh){NAAZlIYoKJ = true;}
      else if(ixMupziNTh == yPJmYBzHaH){bPYkOhXzkY = true;}
      if(oaVAlkqhLo == hwlWKAWyzc){BdEUJancWf = true;}
      else if(hwlWKAWyzc == oaVAlkqhLo){qRhCJTXZzA = true;}
      if(TaXBxcNhCi == CCKupifVyO){oADjWQfZgq = true;}
      else if(CCKupifVyO == TaXBxcNhCi){dCdoMGsxBi = true;}
      if(WffbnteAEA == EtEAimayPs){eKjQWxrzAY = true;}
      else if(EtEAimayPs == WffbnteAEA){hIlXYujpTl = true;}
      if(VJlbedqZmw == ZsYBiFkmxL){XIfXBVEWyy = true;}
      else if(ZsYBiFkmxL == VJlbedqZmw){GNGlRhttUb = true;}
      if(pNYmrWrIow == gHuNSfmQFH){WAxrFMxPCV = true;}
      if(nREqkJusMr == TNPEcnqkmW){czITeqtnyM = true;}
      if(FpdKTKouVS == ZYhFDIdIMj){iocxHgUehA = true;}
      while(gHuNSfmQFH == pNYmrWrIow){BYMrgYliYI = true;}
      while(TNPEcnqkmW == TNPEcnqkmW){nZyCpifJcN = true;}
      while(ZYhFDIdIMj == ZYhFDIdIMj){jgGNtPwqWe = true;}
      if(xrYlhxyphD == true){xrYlhxyphD = false;}
      if(AJrIYLdTYu == true){AJrIYLdTYu = false;}
      if(NAAZlIYoKJ == true){NAAZlIYoKJ = false;}
      if(BdEUJancWf == true){BdEUJancWf = false;}
      if(oADjWQfZgq == true){oADjWQfZgq = false;}
      if(eKjQWxrzAY == true){eKjQWxrzAY = false;}
      if(XIfXBVEWyy == true){XIfXBVEWyy = false;}
      if(WAxrFMxPCV == true){WAxrFMxPCV = false;}
      if(czITeqtnyM == true){czITeqtnyM = false;}
      if(iocxHgUehA == true){iocxHgUehA = false;}
      if(LIbiTdNqKJ == true){LIbiTdNqKJ = false;}
      if(AbwewYzMsK == true){AbwewYzMsK = false;}
      if(bPYkOhXzkY == true){bPYkOhXzkY = false;}
      if(qRhCJTXZzA == true){qRhCJTXZzA = false;}
      if(dCdoMGsxBi == true){dCdoMGsxBi = false;}
      if(hIlXYujpTl == true){hIlXYujpTl = false;}
      if(GNGlRhttUb == true){GNGlRhttUb = false;}
      if(BYMrgYliYI == true){BYMrgYliYI = false;}
      if(nZyCpifJcN == true){nZyCpifJcN = false;}
      if(jgGNtPwqWe == true){jgGNtPwqWe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKNATNDFPX
{ 
  void aEiiriDVKZ()
  { 
      bool cdPtjzBLKu = false;
      bool dIBdwfkyft = false;
      bool DJWLzjgApz = false;
      bool qflSOyPHHs = false;
      bool RzJxQQkDiQ = false;
      bool yFncxSHEuA = false;
      bool RBVLExWhOx = false;
      bool PdplbDzYuh = false;
      bool ycQYAlqIVw = false;
      bool qKLHbQdysS = false;
      bool tColBUOCAs = false;
      bool ShJMBnjxKS = false;
      bool GNMRFERiJK = false;
      bool ZAfbnwneXf = false;
      bool WoIbdJBzFm = false;
      bool fgnaLfoWfw = false;
      bool CfroSRBgYF = false;
      bool AFYduRFknw = false;
      bool DScWesMFPH = false;
      bool GQzadqwSIL = false;
      string uWrGXjlLDj;
      string wHktQeZERL;
      string hRJahHruVk;
      string uSqoTOLXze;
      string XKMqKmGeWR;
      string ONeSndMQXQ;
      string rqpRodQuZB;
      string SBEmmWESQt;
      string BMYDVgmXBp;
      string CuzilgUtCg;
      string WKFUyNJreQ;
      string ZtAdPeSluH;
      string prsjzXBVAG;
      string CKPjXpHDFI;
      string XurkPHtVTH;
      string NhytpdQUVZ;
      string LmqYOOeQFY;
      string WOfmjuAITr;
      string cfCrrTLUst;
      string YmhfxjDTWB;
      if(uWrGXjlLDj == WKFUyNJreQ){cdPtjzBLKu = true;}
      else if(WKFUyNJreQ == uWrGXjlLDj){tColBUOCAs = true;}
      if(wHktQeZERL == ZtAdPeSluH){dIBdwfkyft = true;}
      else if(ZtAdPeSluH == wHktQeZERL){ShJMBnjxKS = true;}
      if(hRJahHruVk == prsjzXBVAG){DJWLzjgApz = true;}
      else if(prsjzXBVAG == hRJahHruVk){GNMRFERiJK = true;}
      if(uSqoTOLXze == CKPjXpHDFI){qflSOyPHHs = true;}
      else if(CKPjXpHDFI == uSqoTOLXze){ZAfbnwneXf = true;}
      if(XKMqKmGeWR == XurkPHtVTH){RzJxQQkDiQ = true;}
      else if(XurkPHtVTH == XKMqKmGeWR){WoIbdJBzFm = true;}
      if(ONeSndMQXQ == NhytpdQUVZ){yFncxSHEuA = true;}
      else if(NhytpdQUVZ == ONeSndMQXQ){fgnaLfoWfw = true;}
      if(rqpRodQuZB == LmqYOOeQFY){RBVLExWhOx = true;}
      else if(LmqYOOeQFY == rqpRodQuZB){CfroSRBgYF = true;}
      if(SBEmmWESQt == WOfmjuAITr){PdplbDzYuh = true;}
      if(BMYDVgmXBp == cfCrrTLUst){ycQYAlqIVw = true;}
      if(CuzilgUtCg == YmhfxjDTWB){qKLHbQdysS = true;}
      while(WOfmjuAITr == SBEmmWESQt){AFYduRFknw = true;}
      while(cfCrrTLUst == cfCrrTLUst){DScWesMFPH = true;}
      while(YmhfxjDTWB == YmhfxjDTWB){GQzadqwSIL = true;}
      if(cdPtjzBLKu == true){cdPtjzBLKu = false;}
      if(dIBdwfkyft == true){dIBdwfkyft = false;}
      if(DJWLzjgApz == true){DJWLzjgApz = false;}
      if(qflSOyPHHs == true){qflSOyPHHs = false;}
      if(RzJxQQkDiQ == true){RzJxQQkDiQ = false;}
      if(yFncxSHEuA == true){yFncxSHEuA = false;}
      if(RBVLExWhOx == true){RBVLExWhOx = false;}
      if(PdplbDzYuh == true){PdplbDzYuh = false;}
      if(ycQYAlqIVw == true){ycQYAlqIVw = false;}
      if(qKLHbQdysS == true){qKLHbQdysS = false;}
      if(tColBUOCAs == true){tColBUOCAs = false;}
      if(ShJMBnjxKS == true){ShJMBnjxKS = false;}
      if(GNMRFERiJK == true){GNMRFERiJK = false;}
      if(ZAfbnwneXf == true){ZAfbnwneXf = false;}
      if(WoIbdJBzFm == true){WoIbdJBzFm = false;}
      if(fgnaLfoWfw == true){fgnaLfoWfw = false;}
      if(CfroSRBgYF == true){CfroSRBgYF = false;}
      if(AFYduRFknw == true){AFYduRFknw = false;}
      if(DScWesMFPH == true){DScWesMFPH = false;}
      if(GQzadqwSIL == true){GQzadqwSIL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FUIEDVUQCU
{ 
  void MMQgpxytOL()
  { 
      bool ChxLznYqIi = false;
      bool MONlQhOlRG = false;
      bool nLLeGDxMxB = false;
      bool uIQqHdQgDQ = false;
      bool qWwHEqKojn = false;
      bool HbHATqVSFu = false;
      bool qMtHmExVel = false;
      bool RhiBOROEZO = false;
      bool sIcIsSAQXP = false;
      bool IyaIZebnTA = false;
      bool snJxWYsGkC = false;
      bool cRrpBhilNU = false;
      bool DfyPdTGabi = false;
      bool pZjZVEyekT = false;
      bool ZteUmqGkGq = false;
      bool woZzxNptTD = false;
      bool SSeCMCgRUw = false;
      bool jDAstJBccm = false;
      bool MUTjmAzjcI = false;
      bool OELhBGOcIj = false;
      string pTacFBZoHP;
      string yZOlqcQBdr;
      string BnzreWdaws;
      string OKIJnpHCJL;
      string LVNgxqrUat;
      string TOlWGBUiyi;
      string WyrNBnQExA;
      string VNqSffZRtn;
      string eJACZAXlDl;
      string VYEanMczfJ;
      string ZmXaYFWTpZ;
      string bCnKDNypnA;
      string PeBKdwIPdS;
      string DZkkNqkYcT;
      string cEwcKTktXa;
      string OlLftulNwb;
      string wHoWWCQCxL;
      string bZNTWKhXzK;
      string LOrCEQNFqR;
      string FXbAWVOZGI;
      if(pTacFBZoHP == ZmXaYFWTpZ){ChxLznYqIi = true;}
      else if(ZmXaYFWTpZ == pTacFBZoHP){snJxWYsGkC = true;}
      if(yZOlqcQBdr == bCnKDNypnA){MONlQhOlRG = true;}
      else if(bCnKDNypnA == yZOlqcQBdr){cRrpBhilNU = true;}
      if(BnzreWdaws == PeBKdwIPdS){nLLeGDxMxB = true;}
      else if(PeBKdwIPdS == BnzreWdaws){DfyPdTGabi = true;}
      if(OKIJnpHCJL == DZkkNqkYcT){uIQqHdQgDQ = true;}
      else if(DZkkNqkYcT == OKIJnpHCJL){pZjZVEyekT = true;}
      if(LVNgxqrUat == cEwcKTktXa){qWwHEqKojn = true;}
      else if(cEwcKTktXa == LVNgxqrUat){ZteUmqGkGq = true;}
      if(TOlWGBUiyi == OlLftulNwb){HbHATqVSFu = true;}
      else if(OlLftulNwb == TOlWGBUiyi){woZzxNptTD = true;}
      if(WyrNBnQExA == wHoWWCQCxL){qMtHmExVel = true;}
      else if(wHoWWCQCxL == WyrNBnQExA){SSeCMCgRUw = true;}
      if(VNqSffZRtn == bZNTWKhXzK){RhiBOROEZO = true;}
      if(eJACZAXlDl == LOrCEQNFqR){sIcIsSAQXP = true;}
      if(VYEanMczfJ == FXbAWVOZGI){IyaIZebnTA = true;}
      while(bZNTWKhXzK == VNqSffZRtn){jDAstJBccm = true;}
      while(LOrCEQNFqR == LOrCEQNFqR){MUTjmAzjcI = true;}
      while(FXbAWVOZGI == FXbAWVOZGI){OELhBGOcIj = true;}
      if(ChxLznYqIi == true){ChxLznYqIi = false;}
      if(MONlQhOlRG == true){MONlQhOlRG = false;}
      if(nLLeGDxMxB == true){nLLeGDxMxB = false;}
      if(uIQqHdQgDQ == true){uIQqHdQgDQ = false;}
      if(qWwHEqKojn == true){qWwHEqKojn = false;}
      if(HbHATqVSFu == true){HbHATqVSFu = false;}
      if(qMtHmExVel == true){qMtHmExVel = false;}
      if(RhiBOROEZO == true){RhiBOROEZO = false;}
      if(sIcIsSAQXP == true){sIcIsSAQXP = false;}
      if(IyaIZebnTA == true){IyaIZebnTA = false;}
      if(snJxWYsGkC == true){snJxWYsGkC = false;}
      if(cRrpBhilNU == true){cRrpBhilNU = false;}
      if(DfyPdTGabi == true){DfyPdTGabi = false;}
      if(pZjZVEyekT == true){pZjZVEyekT = false;}
      if(ZteUmqGkGq == true){ZteUmqGkGq = false;}
      if(woZzxNptTD == true){woZzxNptTD = false;}
      if(SSeCMCgRUw == true){SSeCMCgRUw = false;}
      if(jDAstJBccm == true){jDAstJBccm = false;}
      if(MUTjmAzjcI == true){MUTjmAzjcI = false;}
      if(OELhBGOcIj == true){OELhBGOcIj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class INTLMCERWE
{ 
  void NJnOwHIhrB()
  { 
      bool xJPMHpXlMj = false;
      bool UbnxWEEhNW = false;
      bool QPfwPCieYa = false;
      bool DcrEHUkJaw = false;
      bool zdwxibGxnF = false;
      bool TfmoLgdSxF = false;
      bool HrNlgqijoB = false;
      bool TuHRWmShMm = false;
      bool ukpSHWpCsZ = false;
      bool qRMUnHQJQr = false;
      bool sWHmlXYVSY = false;
      bool OuFJKVCteK = false;
      bool BgpPJBimcP = false;
      bool WIRUtXcCgi = false;
      bool xTiTLuMCJR = false;
      bool EVeFqLfrck = false;
      bool nlsDCFdkPm = false;
      bool szMuMgxWEN = false;
      bool ngcKKAdLdi = false;
      bool qkYwtLafRG = false;
      string kxzjpJoQgY;
      string eDPWkdpBZq;
      string oMUQzMOruu;
      string wyPTCsFENQ;
      string qlGngRlhTd;
      string HROHhYbikd;
      string uxUlcgnwUr;
      string YkmJACGgjg;
      string ZfXRmdjIkc;
      string RVTjUsQUKz;
      string dpNbEWdEGe;
      string SuyDDPZDzy;
      string xeKqaCQCnG;
      string klVjCjRuMP;
      string zeBGJVXQgF;
      string TNULCyfVBB;
      string FaQAtgYNAT;
      string xdpizRdEgE;
      string eAVhlXQJhD;
      string DutLKXOALc;
      if(kxzjpJoQgY == dpNbEWdEGe){xJPMHpXlMj = true;}
      else if(dpNbEWdEGe == kxzjpJoQgY){sWHmlXYVSY = true;}
      if(eDPWkdpBZq == SuyDDPZDzy){UbnxWEEhNW = true;}
      else if(SuyDDPZDzy == eDPWkdpBZq){OuFJKVCteK = true;}
      if(oMUQzMOruu == xeKqaCQCnG){QPfwPCieYa = true;}
      else if(xeKqaCQCnG == oMUQzMOruu){BgpPJBimcP = true;}
      if(wyPTCsFENQ == klVjCjRuMP){DcrEHUkJaw = true;}
      else if(klVjCjRuMP == wyPTCsFENQ){WIRUtXcCgi = true;}
      if(qlGngRlhTd == zeBGJVXQgF){zdwxibGxnF = true;}
      else if(zeBGJVXQgF == qlGngRlhTd){xTiTLuMCJR = true;}
      if(HROHhYbikd == TNULCyfVBB){TfmoLgdSxF = true;}
      else if(TNULCyfVBB == HROHhYbikd){EVeFqLfrck = true;}
      if(uxUlcgnwUr == FaQAtgYNAT){HrNlgqijoB = true;}
      else if(FaQAtgYNAT == uxUlcgnwUr){nlsDCFdkPm = true;}
      if(YkmJACGgjg == xdpizRdEgE){TuHRWmShMm = true;}
      if(ZfXRmdjIkc == eAVhlXQJhD){ukpSHWpCsZ = true;}
      if(RVTjUsQUKz == DutLKXOALc){qRMUnHQJQr = true;}
      while(xdpizRdEgE == YkmJACGgjg){szMuMgxWEN = true;}
      while(eAVhlXQJhD == eAVhlXQJhD){ngcKKAdLdi = true;}
      while(DutLKXOALc == DutLKXOALc){qkYwtLafRG = true;}
      if(xJPMHpXlMj == true){xJPMHpXlMj = false;}
      if(UbnxWEEhNW == true){UbnxWEEhNW = false;}
      if(QPfwPCieYa == true){QPfwPCieYa = false;}
      if(DcrEHUkJaw == true){DcrEHUkJaw = false;}
      if(zdwxibGxnF == true){zdwxibGxnF = false;}
      if(TfmoLgdSxF == true){TfmoLgdSxF = false;}
      if(HrNlgqijoB == true){HrNlgqijoB = false;}
      if(TuHRWmShMm == true){TuHRWmShMm = false;}
      if(ukpSHWpCsZ == true){ukpSHWpCsZ = false;}
      if(qRMUnHQJQr == true){qRMUnHQJQr = false;}
      if(sWHmlXYVSY == true){sWHmlXYVSY = false;}
      if(OuFJKVCteK == true){OuFJKVCteK = false;}
      if(BgpPJBimcP == true){BgpPJBimcP = false;}
      if(WIRUtXcCgi == true){WIRUtXcCgi = false;}
      if(xTiTLuMCJR == true){xTiTLuMCJR = false;}
      if(EVeFqLfrck == true){EVeFqLfrck = false;}
      if(nlsDCFdkPm == true){nlsDCFdkPm = false;}
      if(szMuMgxWEN == true){szMuMgxWEN = false;}
      if(ngcKKAdLdi == true){ngcKKAdLdi = false;}
      if(qkYwtLafRG == true){qkYwtLafRG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNLXXGFHGU
{ 
  void AwkJcbWrsl()
  { 
      bool HcJoEfbpeP = false;
      bool OJNysrUPyJ = false;
      bool tjlUnHODNY = false;
      bool wRJKwPdbJJ = false;
      bool fTHjxeAOJU = false;
      bool XoCiZWpoBw = false;
      bool RYbFTwADCd = false;
      bool OsFocacBWJ = false;
      bool HAtsAGPakY = false;
      bool ZnaNqHqBQB = false;
      bool dwMfGdiNFy = false;
      bool tnRqnRdiEM = false;
      bool gYScDZSrxU = false;
      bool jbkVeKnOmW = false;
      bool XBUlekWiYY = false;
      bool dHwDTFcibf = false;
      bool LpPkOSCuMd = false;
      bool dPwhoeEgxS = false;
      bool CiTXqbehBZ = false;
      bool gElGLgkjWM = false;
      string ZEbOYgCniA;
      string DtjFkPRWgs;
      string ldVFGZBIGI;
      string BQLDARoXsk;
      string uNNsmXDAFV;
      string EzOjiwhVHz;
      string ftgZzlifFS;
      string atduyYPcRh;
      string WBCjEBCaUD;
      string jSPtFAfntA;
      string oWtltKVTlK;
      string fFDZbdrwVx;
      string jHLBiIdioy;
      string rbhQszHQpt;
      string fioJXePpRa;
      string IiRwQgLrDl;
      string fldnREWlfc;
      string WbGbRBSBdE;
      string rmQNpIJlAL;
      string nOMDNsEArT;
      if(ZEbOYgCniA == oWtltKVTlK){HcJoEfbpeP = true;}
      else if(oWtltKVTlK == ZEbOYgCniA){dwMfGdiNFy = true;}
      if(DtjFkPRWgs == fFDZbdrwVx){OJNysrUPyJ = true;}
      else if(fFDZbdrwVx == DtjFkPRWgs){tnRqnRdiEM = true;}
      if(ldVFGZBIGI == jHLBiIdioy){tjlUnHODNY = true;}
      else if(jHLBiIdioy == ldVFGZBIGI){gYScDZSrxU = true;}
      if(BQLDARoXsk == rbhQszHQpt){wRJKwPdbJJ = true;}
      else if(rbhQszHQpt == BQLDARoXsk){jbkVeKnOmW = true;}
      if(uNNsmXDAFV == fioJXePpRa){fTHjxeAOJU = true;}
      else if(fioJXePpRa == uNNsmXDAFV){XBUlekWiYY = true;}
      if(EzOjiwhVHz == IiRwQgLrDl){XoCiZWpoBw = true;}
      else if(IiRwQgLrDl == EzOjiwhVHz){dHwDTFcibf = true;}
      if(ftgZzlifFS == fldnREWlfc){RYbFTwADCd = true;}
      else if(fldnREWlfc == ftgZzlifFS){LpPkOSCuMd = true;}
      if(atduyYPcRh == WbGbRBSBdE){OsFocacBWJ = true;}
      if(WBCjEBCaUD == rmQNpIJlAL){HAtsAGPakY = true;}
      if(jSPtFAfntA == nOMDNsEArT){ZnaNqHqBQB = true;}
      while(WbGbRBSBdE == atduyYPcRh){dPwhoeEgxS = true;}
      while(rmQNpIJlAL == rmQNpIJlAL){CiTXqbehBZ = true;}
      while(nOMDNsEArT == nOMDNsEArT){gElGLgkjWM = true;}
      if(HcJoEfbpeP == true){HcJoEfbpeP = false;}
      if(OJNysrUPyJ == true){OJNysrUPyJ = false;}
      if(tjlUnHODNY == true){tjlUnHODNY = false;}
      if(wRJKwPdbJJ == true){wRJKwPdbJJ = false;}
      if(fTHjxeAOJU == true){fTHjxeAOJU = false;}
      if(XoCiZWpoBw == true){XoCiZWpoBw = false;}
      if(RYbFTwADCd == true){RYbFTwADCd = false;}
      if(OsFocacBWJ == true){OsFocacBWJ = false;}
      if(HAtsAGPakY == true){HAtsAGPakY = false;}
      if(ZnaNqHqBQB == true){ZnaNqHqBQB = false;}
      if(dwMfGdiNFy == true){dwMfGdiNFy = false;}
      if(tnRqnRdiEM == true){tnRqnRdiEM = false;}
      if(gYScDZSrxU == true){gYScDZSrxU = false;}
      if(jbkVeKnOmW == true){jbkVeKnOmW = false;}
      if(XBUlekWiYY == true){XBUlekWiYY = false;}
      if(dHwDTFcibf == true){dHwDTFcibf = false;}
      if(LpPkOSCuMd == true){LpPkOSCuMd = false;}
      if(dPwhoeEgxS == true){dPwhoeEgxS = false;}
      if(CiTXqbehBZ == true){CiTXqbehBZ = false;}
      if(gElGLgkjWM == true){gElGLgkjWM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCYZQIDHJC
{ 
  void HioYkOzTya()
  { 
      bool CctLkHHQXo = false;
      bool OIBoAapUgM = false;
      bool AXFFZJmBut = false;
      bool eolRYsLejL = false;
      bool hnfdtrelbr = false;
      bool TbbpbdXnka = false;
      bool UGUdKYWiPG = false;
      bool PLjVeMrbKg = false;
      bool eAYCaDNwpt = false;
      bool VWsIqbSCTU = false;
      bool VuWUcIqFKP = false;
      bool kucEwTgSCG = false;
      bool LZsUkrRbeD = false;
      bool tpHpLidDZS = false;
      bool MHkaJZsoMW = false;
      bool tzzNJuCBjj = false;
      bool pOaHUunmrM = false;
      bool pdsjsEnSLK = false;
      bool zbPHJtptfP = false;
      bool gcTobxfdFO = false;
      string AtNGqsxJHB;
      string xRklxcjZNN;
      string jgdlaUWcgy;
      string DIHFoDpajS;
      string wrDXUgZVPj;
      string EBiHVSPbfV;
      string VTbIynJexs;
      string mJptRqdGRt;
      string tBNxtCZAjV;
      string nNuNxcPtYf;
      string WtXVxtKnpd;
      string nJKlaUGeOw;
      string NJubFYOcxo;
      string ajgkWAcqAz;
      string qlKFgeCIlb;
      string VkecRNywPX;
      string fgpACEbYOa;
      string qOdOEbzota;
      string WFpUSoEDTJ;
      string BgbcTKwJDb;
      if(AtNGqsxJHB == WtXVxtKnpd){CctLkHHQXo = true;}
      else if(WtXVxtKnpd == AtNGqsxJHB){VuWUcIqFKP = true;}
      if(xRklxcjZNN == nJKlaUGeOw){OIBoAapUgM = true;}
      else if(nJKlaUGeOw == xRklxcjZNN){kucEwTgSCG = true;}
      if(jgdlaUWcgy == NJubFYOcxo){AXFFZJmBut = true;}
      else if(NJubFYOcxo == jgdlaUWcgy){LZsUkrRbeD = true;}
      if(DIHFoDpajS == ajgkWAcqAz){eolRYsLejL = true;}
      else if(ajgkWAcqAz == DIHFoDpajS){tpHpLidDZS = true;}
      if(wrDXUgZVPj == qlKFgeCIlb){hnfdtrelbr = true;}
      else if(qlKFgeCIlb == wrDXUgZVPj){MHkaJZsoMW = true;}
      if(EBiHVSPbfV == VkecRNywPX){TbbpbdXnka = true;}
      else if(VkecRNywPX == EBiHVSPbfV){tzzNJuCBjj = true;}
      if(VTbIynJexs == fgpACEbYOa){UGUdKYWiPG = true;}
      else if(fgpACEbYOa == VTbIynJexs){pOaHUunmrM = true;}
      if(mJptRqdGRt == qOdOEbzota){PLjVeMrbKg = true;}
      if(tBNxtCZAjV == WFpUSoEDTJ){eAYCaDNwpt = true;}
      if(nNuNxcPtYf == BgbcTKwJDb){VWsIqbSCTU = true;}
      while(qOdOEbzota == mJptRqdGRt){pdsjsEnSLK = true;}
      while(WFpUSoEDTJ == WFpUSoEDTJ){zbPHJtptfP = true;}
      while(BgbcTKwJDb == BgbcTKwJDb){gcTobxfdFO = true;}
      if(CctLkHHQXo == true){CctLkHHQXo = false;}
      if(OIBoAapUgM == true){OIBoAapUgM = false;}
      if(AXFFZJmBut == true){AXFFZJmBut = false;}
      if(eolRYsLejL == true){eolRYsLejL = false;}
      if(hnfdtrelbr == true){hnfdtrelbr = false;}
      if(TbbpbdXnka == true){TbbpbdXnka = false;}
      if(UGUdKYWiPG == true){UGUdKYWiPG = false;}
      if(PLjVeMrbKg == true){PLjVeMrbKg = false;}
      if(eAYCaDNwpt == true){eAYCaDNwpt = false;}
      if(VWsIqbSCTU == true){VWsIqbSCTU = false;}
      if(VuWUcIqFKP == true){VuWUcIqFKP = false;}
      if(kucEwTgSCG == true){kucEwTgSCG = false;}
      if(LZsUkrRbeD == true){LZsUkrRbeD = false;}
      if(tpHpLidDZS == true){tpHpLidDZS = false;}
      if(MHkaJZsoMW == true){MHkaJZsoMW = false;}
      if(tzzNJuCBjj == true){tzzNJuCBjj = false;}
      if(pOaHUunmrM == true){pOaHUunmrM = false;}
      if(pdsjsEnSLK == true){pdsjsEnSLK = false;}
      if(zbPHJtptfP == true){zbPHJtptfP = false;}
      if(gcTobxfdFO == true){gcTobxfdFO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ERFOYLCLOW
{ 
  void bCWjXWKRGt()
  { 
      bool hMyqSLkiiK = false;
      bool snOxMuZxKc = false;
      bool pCOCruqKrD = false;
      bool UhCLiZLTMI = false;
      bool iJcNosNLOL = false;
      bool gppoqfyuzX = false;
      bool TZpfoLlCOm = false;
      bool iGkBsfYANz = false;
      bool gfwgVdqNTD = false;
      bool bQUnoISxYd = false;
      bool HKxbbaFowL = false;
      bool GxhApmdJKK = false;
      bool TXiLKSlwMj = false;
      bool MbbiqViUEt = false;
      bool YCQIwdhTxB = false;
      bool eJlOJibkQI = false;
      bool nIbLydVyIU = false;
      bool EIEPkRGZOf = false;
      bool kRyKEDpMZI = false;
      bool sxDwGPZFKS = false;
      string XwqHWYrmQy;
      string ijMrjMLBpf;
      string nqRZGTJRNp;
      string kqZXHzwinR;
      string MKULmChEPB;
      string ccYfSfdRBD;
      string PaYZMrJnkk;
      string QbNYScVGlD;
      string kECLNIRtEa;
      string VdhjCkkuyt;
      string rsSdkAOAMo;
      string JWexRKYNME;
      string aPjKPltcWg;
      string raHrLqlXaM;
      string sQgOQyzjRq;
      string MXhtTcJIOz;
      string FkcexiPmla;
      string YAlzKJiUsQ;
      string lKLeUUrMXi;
      string hcIaGHnBRh;
      if(XwqHWYrmQy == rsSdkAOAMo){hMyqSLkiiK = true;}
      else if(rsSdkAOAMo == XwqHWYrmQy){HKxbbaFowL = true;}
      if(ijMrjMLBpf == JWexRKYNME){snOxMuZxKc = true;}
      else if(JWexRKYNME == ijMrjMLBpf){GxhApmdJKK = true;}
      if(nqRZGTJRNp == aPjKPltcWg){pCOCruqKrD = true;}
      else if(aPjKPltcWg == nqRZGTJRNp){TXiLKSlwMj = true;}
      if(kqZXHzwinR == raHrLqlXaM){UhCLiZLTMI = true;}
      else if(raHrLqlXaM == kqZXHzwinR){MbbiqViUEt = true;}
      if(MKULmChEPB == sQgOQyzjRq){iJcNosNLOL = true;}
      else if(sQgOQyzjRq == MKULmChEPB){YCQIwdhTxB = true;}
      if(ccYfSfdRBD == MXhtTcJIOz){gppoqfyuzX = true;}
      else if(MXhtTcJIOz == ccYfSfdRBD){eJlOJibkQI = true;}
      if(PaYZMrJnkk == FkcexiPmla){TZpfoLlCOm = true;}
      else if(FkcexiPmla == PaYZMrJnkk){nIbLydVyIU = true;}
      if(QbNYScVGlD == YAlzKJiUsQ){iGkBsfYANz = true;}
      if(kECLNIRtEa == lKLeUUrMXi){gfwgVdqNTD = true;}
      if(VdhjCkkuyt == hcIaGHnBRh){bQUnoISxYd = true;}
      while(YAlzKJiUsQ == QbNYScVGlD){EIEPkRGZOf = true;}
      while(lKLeUUrMXi == lKLeUUrMXi){kRyKEDpMZI = true;}
      while(hcIaGHnBRh == hcIaGHnBRh){sxDwGPZFKS = true;}
      if(hMyqSLkiiK == true){hMyqSLkiiK = false;}
      if(snOxMuZxKc == true){snOxMuZxKc = false;}
      if(pCOCruqKrD == true){pCOCruqKrD = false;}
      if(UhCLiZLTMI == true){UhCLiZLTMI = false;}
      if(iJcNosNLOL == true){iJcNosNLOL = false;}
      if(gppoqfyuzX == true){gppoqfyuzX = false;}
      if(TZpfoLlCOm == true){TZpfoLlCOm = false;}
      if(iGkBsfYANz == true){iGkBsfYANz = false;}
      if(gfwgVdqNTD == true){gfwgVdqNTD = false;}
      if(bQUnoISxYd == true){bQUnoISxYd = false;}
      if(HKxbbaFowL == true){HKxbbaFowL = false;}
      if(GxhApmdJKK == true){GxhApmdJKK = false;}
      if(TXiLKSlwMj == true){TXiLKSlwMj = false;}
      if(MbbiqViUEt == true){MbbiqViUEt = false;}
      if(YCQIwdhTxB == true){YCQIwdhTxB = false;}
      if(eJlOJibkQI == true){eJlOJibkQI = false;}
      if(nIbLydVyIU == true){nIbLydVyIU = false;}
      if(EIEPkRGZOf == true){EIEPkRGZOf = false;}
      if(kRyKEDpMZI == true){kRyKEDpMZI = false;}
      if(sxDwGPZFKS == true){sxDwGPZFKS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSBLBRHGOT
{ 
  void QzyRrJxtnm()
  { 
      bool aeHTBzKRIg = false;
      bool TmfZTetQxC = false;
      bool HkzsFnDOFF = false;
      bool coxEwQWAyP = false;
      bool dUgcnoVCaz = false;
      bool eidSXpfOOM = false;
      bool wuLDEeoadC = false;
      bool HsRgXlDWFP = false;
      bool SAnGZsLegG = false;
      bool kIllThJdXJ = false;
      bool AtYXrkRwtl = false;
      bool lIJztuHEcL = false;
      bool SKtWRzHfMp = false;
      bool bZywOYaPOo = false;
      bool bPktTbzmrX = false;
      bool aEAMppzBGr = false;
      bool dkiDJMJMjU = false;
      bool UrpniDYzDo = false;
      bool ATnnPWYlFY = false;
      bool YYIVKpfgkG = false;
      string HWzCSbzAuq;
      string kntXWeZjiX;
      string QHiuZmewTg;
      string yTmFHrYgxt;
      string pTpzWqWozH;
      string rYupuzmEcf;
      string wDfOsRBnQd;
      string GsmnhwQjYh;
      string QpwLnZXwKH;
      string FUDQxlnbGE;
      string oiYVBzkGIz;
      string iDetPGGTZS;
      string tEdIYloVpu;
      string IocUshQaKo;
      string nQnLYBoJBq;
      string fTCmKkEPxP;
      string KOQMpsaJBh;
      string ofJkecQRjW;
      string weUzPnlpKH;
      string cBcteYAaUe;
      if(HWzCSbzAuq == oiYVBzkGIz){aeHTBzKRIg = true;}
      else if(oiYVBzkGIz == HWzCSbzAuq){AtYXrkRwtl = true;}
      if(kntXWeZjiX == iDetPGGTZS){TmfZTetQxC = true;}
      else if(iDetPGGTZS == kntXWeZjiX){lIJztuHEcL = true;}
      if(QHiuZmewTg == tEdIYloVpu){HkzsFnDOFF = true;}
      else if(tEdIYloVpu == QHiuZmewTg){SKtWRzHfMp = true;}
      if(yTmFHrYgxt == IocUshQaKo){coxEwQWAyP = true;}
      else if(IocUshQaKo == yTmFHrYgxt){bZywOYaPOo = true;}
      if(pTpzWqWozH == nQnLYBoJBq){dUgcnoVCaz = true;}
      else if(nQnLYBoJBq == pTpzWqWozH){bPktTbzmrX = true;}
      if(rYupuzmEcf == fTCmKkEPxP){eidSXpfOOM = true;}
      else if(fTCmKkEPxP == rYupuzmEcf){aEAMppzBGr = true;}
      if(wDfOsRBnQd == KOQMpsaJBh){wuLDEeoadC = true;}
      else if(KOQMpsaJBh == wDfOsRBnQd){dkiDJMJMjU = true;}
      if(GsmnhwQjYh == ofJkecQRjW){HsRgXlDWFP = true;}
      if(QpwLnZXwKH == weUzPnlpKH){SAnGZsLegG = true;}
      if(FUDQxlnbGE == cBcteYAaUe){kIllThJdXJ = true;}
      while(ofJkecQRjW == GsmnhwQjYh){UrpniDYzDo = true;}
      while(weUzPnlpKH == weUzPnlpKH){ATnnPWYlFY = true;}
      while(cBcteYAaUe == cBcteYAaUe){YYIVKpfgkG = true;}
      if(aeHTBzKRIg == true){aeHTBzKRIg = false;}
      if(TmfZTetQxC == true){TmfZTetQxC = false;}
      if(HkzsFnDOFF == true){HkzsFnDOFF = false;}
      if(coxEwQWAyP == true){coxEwQWAyP = false;}
      if(dUgcnoVCaz == true){dUgcnoVCaz = false;}
      if(eidSXpfOOM == true){eidSXpfOOM = false;}
      if(wuLDEeoadC == true){wuLDEeoadC = false;}
      if(HsRgXlDWFP == true){HsRgXlDWFP = false;}
      if(SAnGZsLegG == true){SAnGZsLegG = false;}
      if(kIllThJdXJ == true){kIllThJdXJ = false;}
      if(AtYXrkRwtl == true){AtYXrkRwtl = false;}
      if(lIJztuHEcL == true){lIJztuHEcL = false;}
      if(SKtWRzHfMp == true){SKtWRzHfMp = false;}
      if(bZywOYaPOo == true){bZywOYaPOo = false;}
      if(bPktTbzmrX == true){bPktTbzmrX = false;}
      if(aEAMppzBGr == true){aEAMppzBGr = false;}
      if(dkiDJMJMjU == true){dkiDJMJMjU = false;}
      if(UrpniDYzDo == true){UrpniDYzDo = false;}
      if(ATnnPWYlFY == true){ATnnPWYlFY = false;}
      if(YYIVKpfgkG == true){YYIVKpfgkG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILZCISIYBW
{ 
  void fxqFqZLSJh()
  { 
      bool JsCPZMPlOr = false;
      bool GLXwfhAGNK = false;
      bool HRpsrHwBFp = false;
      bool ePfiyYGTDF = false;
      bool zbPIHoaHiD = false;
      bool ADyeLrCIXS = false;
      bool QNfYMpenxH = false;
      bool bgDHLeBhkC = false;
      bool foRCpbRAXG = false;
      bool VxwjokwqwQ = false;
      bool JmJbaSAqTg = false;
      bool pUWUlbucij = false;
      bool YeQqkejSSZ = false;
      bool hKkUssepbW = false;
      bool bZfqPBZayM = false;
      bool oSILreWSpw = false;
      bool igXtyeiCbs = false;
      bool wEBLIyyYaj = false;
      bool EIUFjPCZbN = false;
      bool WMAenuClsk = false;
      string JwUyKcpSpK;
      string hycGyzJjJH;
      string JBssnkEEag;
      string TIUILrlaIk;
      string GDIZqikMaN;
      string sETNZHCbKZ;
      string XlrIqZcTuF;
      string MibYBFrTBE;
      string zqcNmOoGiD;
      string pKPiNUKzhR;
      string GRRUAJcuMT;
      string OhZFZfIdVb;
      string jWkqPCSrKf;
      string uskiygZINc;
      string ktsOoHjKIg;
      string MfdGhigZEx;
      string qjjgYVxqHr;
      string GzQrqpcVCI;
      string RIjcSOOeAO;
      string AzDPlAKMpS;
      if(JwUyKcpSpK == GRRUAJcuMT){JsCPZMPlOr = true;}
      else if(GRRUAJcuMT == JwUyKcpSpK){JmJbaSAqTg = true;}
      if(hycGyzJjJH == OhZFZfIdVb){GLXwfhAGNK = true;}
      else if(OhZFZfIdVb == hycGyzJjJH){pUWUlbucij = true;}
      if(JBssnkEEag == jWkqPCSrKf){HRpsrHwBFp = true;}
      else if(jWkqPCSrKf == JBssnkEEag){YeQqkejSSZ = true;}
      if(TIUILrlaIk == uskiygZINc){ePfiyYGTDF = true;}
      else if(uskiygZINc == TIUILrlaIk){hKkUssepbW = true;}
      if(GDIZqikMaN == ktsOoHjKIg){zbPIHoaHiD = true;}
      else if(ktsOoHjKIg == GDIZqikMaN){bZfqPBZayM = true;}
      if(sETNZHCbKZ == MfdGhigZEx){ADyeLrCIXS = true;}
      else if(MfdGhigZEx == sETNZHCbKZ){oSILreWSpw = true;}
      if(XlrIqZcTuF == qjjgYVxqHr){QNfYMpenxH = true;}
      else if(qjjgYVxqHr == XlrIqZcTuF){igXtyeiCbs = true;}
      if(MibYBFrTBE == GzQrqpcVCI){bgDHLeBhkC = true;}
      if(zqcNmOoGiD == RIjcSOOeAO){foRCpbRAXG = true;}
      if(pKPiNUKzhR == AzDPlAKMpS){VxwjokwqwQ = true;}
      while(GzQrqpcVCI == MibYBFrTBE){wEBLIyyYaj = true;}
      while(RIjcSOOeAO == RIjcSOOeAO){EIUFjPCZbN = true;}
      while(AzDPlAKMpS == AzDPlAKMpS){WMAenuClsk = true;}
      if(JsCPZMPlOr == true){JsCPZMPlOr = false;}
      if(GLXwfhAGNK == true){GLXwfhAGNK = false;}
      if(HRpsrHwBFp == true){HRpsrHwBFp = false;}
      if(ePfiyYGTDF == true){ePfiyYGTDF = false;}
      if(zbPIHoaHiD == true){zbPIHoaHiD = false;}
      if(ADyeLrCIXS == true){ADyeLrCIXS = false;}
      if(QNfYMpenxH == true){QNfYMpenxH = false;}
      if(bgDHLeBhkC == true){bgDHLeBhkC = false;}
      if(foRCpbRAXG == true){foRCpbRAXG = false;}
      if(VxwjokwqwQ == true){VxwjokwqwQ = false;}
      if(JmJbaSAqTg == true){JmJbaSAqTg = false;}
      if(pUWUlbucij == true){pUWUlbucij = false;}
      if(YeQqkejSSZ == true){YeQqkejSSZ = false;}
      if(hKkUssepbW == true){hKkUssepbW = false;}
      if(bZfqPBZayM == true){bZfqPBZayM = false;}
      if(oSILreWSpw == true){oSILreWSpw = false;}
      if(igXtyeiCbs == true){igXtyeiCbs = false;}
      if(wEBLIyyYaj == true){wEBLIyyYaj = false;}
      if(EIUFjPCZbN == true){EIUFjPCZbN = false;}
      if(WMAenuClsk == true){WMAenuClsk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGTDSJVECH
{ 
  void bbQnPlygwP()
  { 
      bool EONRACJlBf = false;
      bool KDREBgqmso = false;
      bool UurzHmdxPM = false;
      bool caChtAnRAt = false;
      bool HKjxFFAjlk = false;
      bool rapEUJWNKM = false;
      bool XLVnDjAiJB = false;
      bool rYmygKLutB = false;
      bool ltKeTBkyNk = false;
      bool caHmWwnutU = false;
      bool FQZkrTmqWJ = false;
      bool xbTIacBqTB = false;
      bool zCVXYRQAbk = false;
      bool VPBYwVUZlA = false;
      bool OsaDmBGzMs = false;
      bool txbrVDtBLa = false;
      bool ClPlnhZtME = false;
      bool IbFSmFaSkW = false;
      bool KQnhpYnIDr = false;
      bool aSNKybdnOF = false;
      string jGUDrGqOEp;
      string AAzQlImPaN;
      string CeEcLNSCyz;
      string cKikuBAYmF;
      string SCJRIUJpXa;
      string eWOCREBqrd;
      string nnPEMpQOVj;
      string INbVuzVmTp;
      string EbeXTFugSp;
      string zIfIQdmEES;
      string EuUmRRtrHS;
      string iOWCZLJrjH;
      string tiuejAgSEQ;
      string MQhBkIHqFC;
      string KCZzHkkdiE;
      string UuTxXUzoDR;
      string janpGRfVQQ;
      string ERlhwrJwXz;
      string PCjAwQwkcQ;
      string JRnnSiOiso;
      if(jGUDrGqOEp == EuUmRRtrHS){EONRACJlBf = true;}
      else if(EuUmRRtrHS == jGUDrGqOEp){FQZkrTmqWJ = true;}
      if(AAzQlImPaN == iOWCZLJrjH){KDREBgqmso = true;}
      else if(iOWCZLJrjH == AAzQlImPaN){xbTIacBqTB = true;}
      if(CeEcLNSCyz == tiuejAgSEQ){UurzHmdxPM = true;}
      else if(tiuejAgSEQ == CeEcLNSCyz){zCVXYRQAbk = true;}
      if(cKikuBAYmF == MQhBkIHqFC){caChtAnRAt = true;}
      else if(MQhBkIHqFC == cKikuBAYmF){VPBYwVUZlA = true;}
      if(SCJRIUJpXa == KCZzHkkdiE){HKjxFFAjlk = true;}
      else if(KCZzHkkdiE == SCJRIUJpXa){OsaDmBGzMs = true;}
      if(eWOCREBqrd == UuTxXUzoDR){rapEUJWNKM = true;}
      else if(UuTxXUzoDR == eWOCREBqrd){txbrVDtBLa = true;}
      if(nnPEMpQOVj == janpGRfVQQ){XLVnDjAiJB = true;}
      else if(janpGRfVQQ == nnPEMpQOVj){ClPlnhZtME = true;}
      if(INbVuzVmTp == ERlhwrJwXz){rYmygKLutB = true;}
      if(EbeXTFugSp == PCjAwQwkcQ){ltKeTBkyNk = true;}
      if(zIfIQdmEES == JRnnSiOiso){caHmWwnutU = true;}
      while(ERlhwrJwXz == INbVuzVmTp){IbFSmFaSkW = true;}
      while(PCjAwQwkcQ == PCjAwQwkcQ){KQnhpYnIDr = true;}
      while(JRnnSiOiso == JRnnSiOiso){aSNKybdnOF = true;}
      if(EONRACJlBf == true){EONRACJlBf = false;}
      if(KDREBgqmso == true){KDREBgqmso = false;}
      if(UurzHmdxPM == true){UurzHmdxPM = false;}
      if(caChtAnRAt == true){caChtAnRAt = false;}
      if(HKjxFFAjlk == true){HKjxFFAjlk = false;}
      if(rapEUJWNKM == true){rapEUJWNKM = false;}
      if(XLVnDjAiJB == true){XLVnDjAiJB = false;}
      if(rYmygKLutB == true){rYmygKLutB = false;}
      if(ltKeTBkyNk == true){ltKeTBkyNk = false;}
      if(caHmWwnutU == true){caHmWwnutU = false;}
      if(FQZkrTmqWJ == true){FQZkrTmqWJ = false;}
      if(xbTIacBqTB == true){xbTIacBqTB = false;}
      if(zCVXYRQAbk == true){zCVXYRQAbk = false;}
      if(VPBYwVUZlA == true){VPBYwVUZlA = false;}
      if(OsaDmBGzMs == true){OsaDmBGzMs = false;}
      if(txbrVDtBLa == true){txbrVDtBLa = false;}
      if(ClPlnhZtME == true){ClPlnhZtME = false;}
      if(IbFSmFaSkW == true){IbFSmFaSkW = false;}
      if(KQnhpYnIDr == true){KQnhpYnIDr = false;}
      if(aSNKybdnOF == true){aSNKybdnOF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELGIFNOKAJ
{ 
  void suxwiKaRUZ()
  { 
      bool fWxnlfhaWb = false;
      bool MbpMLhrQjR = false;
      bool wXqoJFgCkk = false;
      bool dqiFhQsXEj = false;
      bool NmRKKyMNZW = false;
      bool DcniiHeHef = false;
      bool zeplyVrjeu = false;
      bool oTMzDIGfeL = false;
      bool sTcOhBDAVZ = false;
      bool kksYkhxfMn = false;
      bool FbhehiQneZ = false;
      bool AycSleCaEx = false;
      bool RqNEJDZnOU = false;
      bool LZTpFRkygy = false;
      bool jOVuYlIalF = false;
      bool fVbOWONcUd = false;
      bool JcZJOadlMU = false;
      bool sEsFMDVSfX = false;
      bool uzBIooyFTq = false;
      bool DIcCnHnLgy = false;
      string dUgdHJNVWi;
      string XwcuoHblUl;
      string LWlCzspWVB;
      string LFfmmiyDHB;
      string lwGIpgyJnx;
      string yULDtHideO;
      string TqzVXRQpHG;
      string IYdSzPQcLR;
      string tfhYCqsbrf;
      string zTXshuxjjY;
      string QIChnZprEe;
      string pFRNUmIZSg;
      string YnxaGoBkkD;
      string RfrmAkdAkc;
      string AAXNpsBKXu;
      string mWRDAcLaaz;
      string XFHAMKNeMi;
      string IHopfXPjkN;
      string mpMpQuOomX;
      string ZCZlEusXAe;
      if(dUgdHJNVWi == QIChnZprEe){fWxnlfhaWb = true;}
      else if(QIChnZprEe == dUgdHJNVWi){FbhehiQneZ = true;}
      if(XwcuoHblUl == pFRNUmIZSg){MbpMLhrQjR = true;}
      else if(pFRNUmIZSg == XwcuoHblUl){AycSleCaEx = true;}
      if(LWlCzspWVB == YnxaGoBkkD){wXqoJFgCkk = true;}
      else if(YnxaGoBkkD == LWlCzspWVB){RqNEJDZnOU = true;}
      if(LFfmmiyDHB == RfrmAkdAkc){dqiFhQsXEj = true;}
      else if(RfrmAkdAkc == LFfmmiyDHB){LZTpFRkygy = true;}
      if(lwGIpgyJnx == AAXNpsBKXu){NmRKKyMNZW = true;}
      else if(AAXNpsBKXu == lwGIpgyJnx){jOVuYlIalF = true;}
      if(yULDtHideO == mWRDAcLaaz){DcniiHeHef = true;}
      else if(mWRDAcLaaz == yULDtHideO){fVbOWONcUd = true;}
      if(TqzVXRQpHG == XFHAMKNeMi){zeplyVrjeu = true;}
      else if(XFHAMKNeMi == TqzVXRQpHG){JcZJOadlMU = true;}
      if(IYdSzPQcLR == IHopfXPjkN){oTMzDIGfeL = true;}
      if(tfhYCqsbrf == mpMpQuOomX){sTcOhBDAVZ = true;}
      if(zTXshuxjjY == ZCZlEusXAe){kksYkhxfMn = true;}
      while(IHopfXPjkN == IYdSzPQcLR){sEsFMDVSfX = true;}
      while(mpMpQuOomX == mpMpQuOomX){uzBIooyFTq = true;}
      while(ZCZlEusXAe == ZCZlEusXAe){DIcCnHnLgy = true;}
      if(fWxnlfhaWb == true){fWxnlfhaWb = false;}
      if(MbpMLhrQjR == true){MbpMLhrQjR = false;}
      if(wXqoJFgCkk == true){wXqoJFgCkk = false;}
      if(dqiFhQsXEj == true){dqiFhQsXEj = false;}
      if(NmRKKyMNZW == true){NmRKKyMNZW = false;}
      if(DcniiHeHef == true){DcniiHeHef = false;}
      if(zeplyVrjeu == true){zeplyVrjeu = false;}
      if(oTMzDIGfeL == true){oTMzDIGfeL = false;}
      if(sTcOhBDAVZ == true){sTcOhBDAVZ = false;}
      if(kksYkhxfMn == true){kksYkhxfMn = false;}
      if(FbhehiQneZ == true){FbhehiQneZ = false;}
      if(AycSleCaEx == true){AycSleCaEx = false;}
      if(RqNEJDZnOU == true){RqNEJDZnOU = false;}
      if(LZTpFRkygy == true){LZTpFRkygy = false;}
      if(jOVuYlIalF == true){jOVuYlIalF = false;}
      if(fVbOWONcUd == true){fVbOWONcUd = false;}
      if(JcZJOadlMU == true){JcZJOadlMU = false;}
      if(sEsFMDVSfX == true){sEsFMDVSfX = false;}
      if(uzBIooyFTq == true){uzBIooyFTq = false;}
      if(DIcCnHnLgy == true){DIcCnHnLgy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRXVQMSHKG
{ 
  void QSUCskrPpr()
  { 
      bool OMyXZkJseE = false;
      bool CMVMTaTtmy = false;
      bool qZhaqAOQZa = false;
      bool EfcBliXHDF = false;
      bool jYylsgOUcp = false;
      bool QSjQPoeWfY = false;
      bool VsTDzWiTaj = false;
      bool DMqgOSauhJ = false;
      bool ktmjKlwMkw = false;
      bool EAadjpFtlV = false;
      bool yutrlDbCBx = false;
      bool NioVnbFisN = false;
      bool aVhdfCkMxX = false;
      bool NgJLLpAtxG = false;
      bool KsKniVLEpH = false;
      bool kVBYtbMPMj = false;
      bool SOEdjgZcKy = false;
      bool bLklChKtuJ = false;
      bool pgWomqejQj = false;
      bool cjhMnungDB = false;
      string zdmUVHpxrA;
      string JUOsZtXOfy;
      string FsCOhfjTJi;
      string lHKulQsihh;
      string xmzybUZNpy;
      string eRKEbGaXmo;
      string WVmJNBKTGI;
      string BnfyARsEmM;
      string FWcKEUxFSe;
      string oUwrKaApjZ;
      string KGGgxplLDK;
      string NWkZjAsbFs;
      string DEBbSfrmnZ;
      string RDTMCzPwNN;
      string hkBIRRjVIK;
      string hXkpWFFeNQ;
      string xyXdrJDXXk;
      string jxNqLRCsJB;
      string wVecqsSdpw;
      string sjhxQjNWPH;
      if(zdmUVHpxrA == KGGgxplLDK){OMyXZkJseE = true;}
      else if(KGGgxplLDK == zdmUVHpxrA){yutrlDbCBx = true;}
      if(JUOsZtXOfy == NWkZjAsbFs){CMVMTaTtmy = true;}
      else if(NWkZjAsbFs == JUOsZtXOfy){NioVnbFisN = true;}
      if(FsCOhfjTJi == DEBbSfrmnZ){qZhaqAOQZa = true;}
      else if(DEBbSfrmnZ == FsCOhfjTJi){aVhdfCkMxX = true;}
      if(lHKulQsihh == RDTMCzPwNN){EfcBliXHDF = true;}
      else if(RDTMCzPwNN == lHKulQsihh){NgJLLpAtxG = true;}
      if(xmzybUZNpy == hkBIRRjVIK){jYylsgOUcp = true;}
      else if(hkBIRRjVIK == xmzybUZNpy){KsKniVLEpH = true;}
      if(eRKEbGaXmo == hXkpWFFeNQ){QSjQPoeWfY = true;}
      else if(hXkpWFFeNQ == eRKEbGaXmo){kVBYtbMPMj = true;}
      if(WVmJNBKTGI == xyXdrJDXXk){VsTDzWiTaj = true;}
      else if(xyXdrJDXXk == WVmJNBKTGI){SOEdjgZcKy = true;}
      if(BnfyARsEmM == jxNqLRCsJB){DMqgOSauhJ = true;}
      if(FWcKEUxFSe == wVecqsSdpw){ktmjKlwMkw = true;}
      if(oUwrKaApjZ == sjhxQjNWPH){EAadjpFtlV = true;}
      while(jxNqLRCsJB == BnfyARsEmM){bLklChKtuJ = true;}
      while(wVecqsSdpw == wVecqsSdpw){pgWomqejQj = true;}
      while(sjhxQjNWPH == sjhxQjNWPH){cjhMnungDB = true;}
      if(OMyXZkJseE == true){OMyXZkJseE = false;}
      if(CMVMTaTtmy == true){CMVMTaTtmy = false;}
      if(qZhaqAOQZa == true){qZhaqAOQZa = false;}
      if(EfcBliXHDF == true){EfcBliXHDF = false;}
      if(jYylsgOUcp == true){jYylsgOUcp = false;}
      if(QSjQPoeWfY == true){QSjQPoeWfY = false;}
      if(VsTDzWiTaj == true){VsTDzWiTaj = false;}
      if(DMqgOSauhJ == true){DMqgOSauhJ = false;}
      if(ktmjKlwMkw == true){ktmjKlwMkw = false;}
      if(EAadjpFtlV == true){EAadjpFtlV = false;}
      if(yutrlDbCBx == true){yutrlDbCBx = false;}
      if(NioVnbFisN == true){NioVnbFisN = false;}
      if(aVhdfCkMxX == true){aVhdfCkMxX = false;}
      if(NgJLLpAtxG == true){NgJLLpAtxG = false;}
      if(KsKniVLEpH == true){KsKniVLEpH = false;}
      if(kVBYtbMPMj == true){kVBYtbMPMj = false;}
      if(SOEdjgZcKy == true){SOEdjgZcKy = false;}
      if(bLklChKtuJ == true){bLklChKtuJ = false;}
      if(pgWomqejQj == true){pgWomqejQj = false;}
      if(cjhMnungDB == true){cjhMnungDB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SRFHXWECCE
{ 
  void TMfBcnUhpB()
  { 
      bool eYscpnCsjM = false;
      bool emVVJkugWA = false;
      bool RMAfBrLyHX = false;
      bool DkiXbgYHxJ = false;
      bool wXsVJGEoEW = false;
      bool piiibSYNbx = false;
      bool cDlLItDytb = false;
      bool LmjNEtSdVt = false;
      bool nVtjhUBAuI = false;
      bool ILfzgrkhMP = false;
      bool DGubKDzVdh = false;
      bool AtqgJGJBdn = false;
      bool rCDkTAHjgL = false;
      bool IjRGqgaSYd = false;
      bool VeVMINTzpZ = false;
      bool ijEYWADJHK = false;
      bool uOoSZPckob = false;
      bool epbzSMgpcG = false;
      bool gHsGbYfsjq = false;
      bool dRKOiGpDms = false;
      string HOwuTqQxlN;
      string StYuGWwBLI;
      string SgEwQPMLBJ;
      string bKSZNtEWXW;
      string bAQItQGPRu;
      string KTHLeZJzeE;
      string eEwckIayhM;
      string SYcogRPuBA;
      string IwsGyIDHum;
      string jFrTrWEnXl;
      string oIhFckpReM;
      string KOxeuhLpdc;
      string FTCtcNgJxJ;
      string NbXPKAOncN;
      string SkbicVHNYJ;
      string LOKtgVGmcP;
      string EfUVziphTu;
      string TWMQKTqSRG;
      string FSkmyyQdhn;
      string saLNIlQGit;
      if(HOwuTqQxlN == oIhFckpReM){eYscpnCsjM = true;}
      else if(oIhFckpReM == HOwuTqQxlN){DGubKDzVdh = true;}
      if(StYuGWwBLI == KOxeuhLpdc){emVVJkugWA = true;}
      else if(KOxeuhLpdc == StYuGWwBLI){AtqgJGJBdn = true;}
      if(SgEwQPMLBJ == FTCtcNgJxJ){RMAfBrLyHX = true;}
      else if(FTCtcNgJxJ == SgEwQPMLBJ){rCDkTAHjgL = true;}
      if(bKSZNtEWXW == NbXPKAOncN){DkiXbgYHxJ = true;}
      else if(NbXPKAOncN == bKSZNtEWXW){IjRGqgaSYd = true;}
      if(bAQItQGPRu == SkbicVHNYJ){wXsVJGEoEW = true;}
      else if(SkbicVHNYJ == bAQItQGPRu){VeVMINTzpZ = true;}
      if(KTHLeZJzeE == LOKtgVGmcP){piiibSYNbx = true;}
      else if(LOKtgVGmcP == KTHLeZJzeE){ijEYWADJHK = true;}
      if(eEwckIayhM == EfUVziphTu){cDlLItDytb = true;}
      else if(EfUVziphTu == eEwckIayhM){uOoSZPckob = true;}
      if(SYcogRPuBA == TWMQKTqSRG){LmjNEtSdVt = true;}
      if(IwsGyIDHum == FSkmyyQdhn){nVtjhUBAuI = true;}
      if(jFrTrWEnXl == saLNIlQGit){ILfzgrkhMP = true;}
      while(TWMQKTqSRG == SYcogRPuBA){epbzSMgpcG = true;}
      while(FSkmyyQdhn == FSkmyyQdhn){gHsGbYfsjq = true;}
      while(saLNIlQGit == saLNIlQGit){dRKOiGpDms = true;}
      if(eYscpnCsjM == true){eYscpnCsjM = false;}
      if(emVVJkugWA == true){emVVJkugWA = false;}
      if(RMAfBrLyHX == true){RMAfBrLyHX = false;}
      if(DkiXbgYHxJ == true){DkiXbgYHxJ = false;}
      if(wXsVJGEoEW == true){wXsVJGEoEW = false;}
      if(piiibSYNbx == true){piiibSYNbx = false;}
      if(cDlLItDytb == true){cDlLItDytb = false;}
      if(LmjNEtSdVt == true){LmjNEtSdVt = false;}
      if(nVtjhUBAuI == true){nVtjhUBAuI = false;}
      if(ILfzgrkhMP == true){ILfzgrkhMP = false;}
      if(DGubKDzVdh == true){DGubKDzVdh = false;}
      if(AtqgJGJBdn == true){AtqgJGJBdn = false;}
      if(rCDkTAHjgL == true){rCDkTAHjgL = false;}
      if(IjRGqgaSYd == true){IjRGqgaSYd = false;}
      if(VeVMINTzpZ == true){VeVMINTzpZ = false;}
      if(ijEYWADJHK == true){ijEYWADJHK = false;}
      if(uOoSZPckob == true){uOoSZPckob = false;}
      if(epbzSMgpcG == true){epbzSMgpcG = false;}
      if(gHsGbYfsjq == true){gHsGbYfsjq = false;}
      if(dRKOiGpDms == true){dRKOiGpDms = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSYKJZBOLY
{ 
  void wcZVSnKjfK()
  { 
      bool mzxfZlwPmy = false;
      bool tYWqaRTMYS = false;
      bool WIHWBgbCrr = false;
      bool etweFuXNyB = false;
      bool kiWhspwrXJ = false;
      bool WnAUedradr = false;
      bool JtXuSAcrkf = false;
      bool tGNWhmlYcL = false;
      bool jieiUpsazb = false;
      bool DwiGqpLaOs = false;
      bool MEHqOQacmr = false;
      bool rSxSIZPnac = false;
      bool GBrIcxWHeq = false;
      bool bKKjyebmTD = false;
      bool OQmHjjzQyR = false;
      bool aWAklKMyOQ = false;
      bool sTxwPgINTc = false;
      bool ybTXNpOjYs = false;
      bool yFJNPFKYxm = false;
      bool ScXDJuSprC = false;
      string wwyOYeerVg;
      string BhuPLFMEKa;
      string TnBtdeWwuE;
      string jKtCiDnJdI;
      string MSkHmGZorV;
      string VcmLhHtEks;
      string HixRwqmrfI;
      string RDZBOBCsGW;
      string EgDZhHXhUb;
      string IjXjBcVTLw;
      string TgIjESCkxf;
      string EBxOnZeWin;
      string SEXEzheoAk;
      string fihJDXYTVP;
      string ElknWGlJwa;
      string xyjWdOIEjW;
      string nNkLAVTmLQ;
      string BLBTifTjgs;
      string uVsYmhzKfn;
      string OTizbqBYnB;
      if(wwyOYeerVg == TgIjESCkxf){mzxfZlwPmy = true;}
      else if(TgIjESCkxf == wwyOYeerVg){MEHqOQacmr = true;}
      if(BhuPLFMEKa == EBxOnZeWin){tYWqaRTMYS = true;}
      else if(EBxOnZeWin == BhuPLFMEKa){rSxSIZPnac = true;}
      if(TnBtdeWwuE == SEXEzheoAk){WIHWBgbCrr = true;}
      else if(SEXEzheoAk == TnBtdeWwuE){GBrIcxWHeq = true;}
      if(jKtCiDnJdI == fihJDXYTVP){etweFuXNyB = true;}
      else if(fihJDXYTVP == jKtCiDnJdI){bKKjyebmTD = true;}
      if(MSkHmGZorV == ElknWGlJwa){kiWhspwrXJ = true;}
      else if(ElknWGlJwa == MSkHmGZorV){OQmHjjzQyR = true;}
      if(VcmLhHtEks == xyjWdOIEjW){WnAUedradr = true;}
      else if(xyjWdOIEjW == VcmLhHtEks){aWAklKMyOQ = true;}
      if(HixRwqmrfI == nNkLAVTmLQ){JtXuSAcrkf = true;}
      else if(nNkLAVTmLQ == HixRwqmrfI){sTxwPgINTc = true;}
      if(RDZBOBCsGW == BLBTifTjgs){tGNWhmlYcL = true;}
      if(EgDZhHXhUb == uVsYmhzKfn){jieiUpsazb = true;}
      if(IjXjBcVTLw == OTizbqBYnB){DwiGqpLaOs = true;}
      while(BLBTifTjgs == RDZBOBCsGW){ybTXNpOjYs = true;}
      while(uVsYmhzKfn == uVsYmhzKfn){yFJNPFKYxm = true;}
      while(OTizbqBYnB == OTizbqBYnB){ScXDJuSprC = true;}
      if(mzxfZlwPmy == true){mzxfZlwPmy = false;}
      if(tYWqaRTMYS == true){tYWqaRTMYS = false;}
      if(WIHWBgbCrr == true){WIHWBgbCrr = false;}
      if(etweFuXNyB == true){etweFuXNyB = false;}
      if(kiWhspwrXJ == true){kiWhspwrXJ = false;}
      if(WnAUedradr == true){WnAUedradr = false;}
      if(JtXuSAcrkf == true){JtXuSAcrkf = false;}
      if(tGNWhmlYcL == true){tGNWhmlYcL = false;}
      if(jieiUpsazb == true){jieiUpsazb = false;}
      if(DwiGqpLaOs == true){DwiGqpLaOs = false;}
      if(MEHqOQacmr == true){MEHqOQacmr = false;}
      if(rSxSIZPnac == true){rSxSIZPnac = false;}
      if(GBrIcxWHeq == true){GBrIcxWHeq = false;}
      if(bKKjyebmTD == true){bKKjyebmTD = false;}
      if(OQmHjjzQyR == true){OQmHjjzQyR = false;}
      if(aWAklKMyOQ == true){aWAklKMyOQ = false;}
      if(sTxwPgINTc == true){sTxwPgINTc = false;}
      if(ybTXNpOjYs == true){ybTXNpOjYs = false;}
      if(yFJNPFKYxm == true){yFJNPFKYxm = false;}
      if(ScXDJuSprC == true){ScXDJuSprC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VMPHSPWMXO
{ 
  void oVUAjsPMRI()
  { 
      bool mpVdZwlHjd = false;
      bool lwyjaoimwu = false;
      bool qkVinUwbOa = false;
      bool TbjkWpMQsD = false;
      bool tYpCJKxEAF = false;
      bool iHtxDBUmpE = false;
      bool AKrIJJMMNk = false;
      bool bSssAStSYc = false;
      bool XqbIqLhmgU = false;
      bool UZaoCjfgrz = false;
      bool yjqOcQOAwj = false;
      bool GBNMfJiiRx = false;
      bool bZerQCrDqP = false;
      bool lNZZemAMfa = false;
      bool xgpwNSLNIs = false;
      bool BwPuXYEyya = false;
      bool XKJfysbmhs = false;
      bool IVDpztiidx = false;
      bool pduxOoxeCF = false;
      bool hBOFCmWJyU = false;
      string xUewZKQsBt;
      string GEtkYTuwRq;
      string ileWAuRKoz;
      string JYfYyDaddZ;
      string HgwFpkrOYY;
      string YPHNCLoHwd;
      string sFDCkgYUlV;
      string rRSqiBpZgO;
      string DClQZtRRWm;
      string NShzgBdsUI;
      string MWcCgHxQdA;
      string UPagapTmbq;
      string PGyyHYiSJh;
      string XxEYCfZiiS;
      string xBmVSyrAYp;
      string gpQdrFYdtH;
      string XdGwcXLBet;
      string QkDJtOScfJ;
      string fhtSAgfZfw;
      string GuobuStqru;
      if(xUewZKQsBt == MWcCgHxQdA){mpVdZwlHjd = true;}
      else if(MWcCgHxQdA == xUewZKQsBt){yjqOcQOAwj = true;}
      if(GEtkYTuwRq == UPagapTmbq){lwyjaoimwu = true;}
      else if(UPagapTmbq == GEtkYTuwRq){GBNMfJiiRx = true;}
      if(ileWAuRKoz == PGyyHYiSJh){qkVinUwbOa = true;}
      else if(PGyyHYiSJh == ileWAuRKoz){bZerQCrDqP = true;}
      if(JYfYyDaddZ == XxEYCfZiiS){TbjkWpMQsD = true;}
      else if(XxEYCfZiiS == JYfYyDaddZ){lNZZemAMfa = true;}
      if(HgwFpkrOYY == xBmVSyrAYp){tYpCJKxEAF = true;}
      else if(xBmVSyrAYp == HgwFpkrOYY){xgpwNSLNIs = true;}
      if(YPHNCLoHwd == gpQdrFYdtH){iHtxDBUmpE = true;}
      else if(gpQdrFYdtH == YPHNCLoHwd){BwPuXYEyya = true;}
      if(sFDCkgYUlV == XdGwcXLBet){AKrIJJMMNk = true;}
      else if(XdGwcXLBet == sFDCkgYUlV){XKJfysbmhs = true;}
      if(rRSqiBpZgO == QkDJtOScfJ){bSssAStSYc = true;}
      if(DClQZtRRWm == fhtSAgfZfw){XqbIqLhmgU = true;}
      if(NShzgBdsUI == GuobuStqru){UZaoCjfgrz = true;}
      while(QkDJtOScfJ == rRSqiBpZgO){IVDpztiidx = true;}
      while(fhtSAgfZfw == fhtSAgfZfw){pduxOoxeCF = true;}
      while(GuobuStqru == GuobuStqru){hBOFCmWJyU = true;}
      if(mpVdZwlHjd == true){mpVdZwlHjd = false;}
      if(lwyjaoimwu == true){lwyjaoimwu = false;}
      if(qkVinUwbOa == true){qkVinUwbOa = false;}
      if(TbjkWpMQsD == true){TbjkWpMQsD = false;}
      if(tYpCJKxEAF == true){tYpCJKxEAF = false;}
      if(iHtxDBUmpE == true){iHtxDBUmpE = false;}
      if(AKrIJJMMNk == true){AKrIJJMMNk = false;}
      if(bSssAStSYc == true){bSssAStSYc = false;}
      if(XqbIqLhmgU == true){XqbIqLhmgU = false;}
      if(UZaoCjfgrz == true){UZaoCjfgrz = false;}
      if(yjqOcQOAwj == true){yjqOcQOAwj = false;}
      if(GBNMfJiiRx == true){GBNMfJiiRx = false;}
      if(bZerQCrDqP == true){bZerQCrDqP = false;}
      if(lNZZemAMfa == true){lNZZemAMfa = false;}
      if(xgpwNSLNIs == true){xgpwNSLNIs = false;}
      if(BwPuXYEyya == true){BwPuXYEyya = false;}
      if(XKJfysbmhs == true){XKJfysbmhs = false;}
      if(IVDpztiidx == true){IVDpztiidx = false;}
      if(pduxOoxeCF == true){pduxOoxeCF = false;}
      if(hBOFCmWJyU == true){hBOFCmWJyU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBEWXDIEBN
{ 
  void kXWYoDfnow()
  { 
      bool KLkDiXUiJn = false;
      bool yYUrkoFsRA = false;
      bool crNQRYgkrR = false;
      bool yOYnrhIpHr = false;
      bool XEKDggKeSF = false;
      bool jpqYiRyUkJ = false;
      bool piqrojzfzC = false;
      bool gPlYcYgJik = false;
      bool OBRlgHWzFZ = false;
      bool jmExCnNSNw = false;
      bool gdfPYUESwJ = false;
      bool knkAtnQEKh = false;
      bool MzaYSsKnVo = false;
      bool KNulDkVBML = false;
      bool DEDuouCEDN = false;
      bool WIIfjhDHxf = false;
      bool KQwHzWrywJ = false;
      bool SPrydIwfjX = false;
      bool pGjIRCFPCV = false;
      bool gNEgBmHuwR = false;
      string PSdfLiNEMX;
      string nNhITcSrRA;
      string TqReyqeEHF;
      string ULiAaWiMww;
      string IgtQxNXfRi;
      string QOgSjXAzhU;
      string EJwGDcehgw;
      string tGwUrmxAgj;
      string TzlXoGdQPD;
      string WiebrzjmNU;
      string ipyUoKSLaw;
      string ZzRxBEWYRw;
      string zNRdZKaTcr;
      string DJmMBcARid;
      string nRpScWQgam;
      string bKVRUVXUtd;
      string iyihsQMFwX;
      string EEpmHgWzAC;
      string stspQrmUqe;
      string FeWEupiIZM;
      if(PSdfLiNEMX == ipyUoKSLaw){KLkDiXUiJn = true;}
      else if(ipyUoKSLaw == PSdfLiNEMX){gdfPYUESwJ = true;}
      if(nNhITcSrRA == ZzRxBEWYRw){yYUrkoFsRA = true;}
      else if(ZzRxBEWYRw == nNhITcSrRA){knkAtnQEKh = true;}
      if(TqReyqeEHF == zNRdZKaTcr){crNQRYgkrR = true;}
      else if(zNRdZKaTcr == TqReyqeEHF){MzaYSsKnVo = true;}
      if(ULiAaWiMww == DJmMBcARid){yOYnrhIpHr = true;}
      else if(DJmMBcARid == ULiAaWiMww){KNulDkVBML = true;}
      if(IgtQxNXfRi == nRpScWQgam){XEKDggKeSF = true;}
      else if(nRpScWQgam == IgtQxNXfRi){DEDuouCEDN = true;}
      if(QOgSjXAzhU == bKVRUVXUtd){jpqYiRyUkJ = true;}
      else if(bKVRUVXUtd == QOgSjXAzhU){WIIfjhDHxf = true;}
      if(EJwGDcehgw == iyihsQMFwX){piqrojzfzC = true;}
      else if(iyihsQMFwX == EJwGDcehgw){KQwHzWrywJ = true;}
      if(tGwUrmxAgj == EEpmHgWzAC){gPlYcYgJik = true;}
      if(TzlXoGdQPD == stspQrmUqe){OBRlgHWzFZ = true;}
      if(WiebrzjmNU == FeWEupiIZM){jmExCnNSNw = true;}
      while(EEpmHgWzAC == tGwUrmxAgj){SPrydIwfjX = true;}
      while(stspQrmUqe == stspQrmUqe){pGjIRCFPCV = true;}
      while(FeWEupiIZM == FeWEupiIZM){gNEgBmHuwR = true;}
      if(KLkDiXUiJn == true){KLkDiXUiJn = false;}
      if(yYUrkoFsRA == true){yYUrkoFsRA = false;}
      if(crNQRYgkrR == true){crNQRYgkrR = false;}
      if(yOYnrhIpHr == true){yOYnrhIpHr = false;}
      if(XEKDggKeSF == true){XEKDggKeSF = false;}
      if(jpqYiRyUkJ == true){jpqYiRyUkJ = false;}
      if(piqrojzfzC == true){piqrojzfzC = false;}
      if(gPlYcYgJik == true){gPlYcYgJik = false;}
      if(OBRlgHWzFZ == true){OBRlgHWzFZ = false;}
      if(jmExCnNSNw == true){jmExCnNSNw = false;}
      if(gdfPYUESwJ == true){gdfPYUESwJ = false;}
      if(knkAtnQEKh == true){knkAtnQEKh = false;}
      if(MzaYSsKnVo == true){MzaYSsKnVo = false;}
      if(KNulDkVBML == true){KNulDkVBML = false;}
      if(DEDuouCEDN == true){DEDuouCEDN = false;}
      if(WIIfjhDHxf == true){WIIfjhDHxf = false;}
      if(KQwHzWrywJ == true){KQwHzWrywJ = false;}
      if(SPrydIwfjX == true){SPrydIwfjX = false;}
      if(pGjIRCFPCV == true){pGjIRCFPCV = false;}
      if(gNEgBmHuwR == true){gNEgBmHuwR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKTRXVLNML
{ 
  void IoWGtSkIuD()
  { 
      bool kLQmaNxNWc = false;
      bool FFyEFkVEls = false;
      bool HncrDXzaar = false;
      bool opmpitshlz = false;
      bool SbFqleRhAd = false;
      bool CjHaOwiXjD = false;
      bool OVldmOSIUK = false;
      bool rnRlZeilGY = false;
      bool FQZxpEhLam = false;
      bool LUxikxoaDW = false;
      bool LJNpkORVAi = false;
      bool NxRLxxuoni = false;
      bool fHghzWpiAc = false;
      bool pHiiMuDjLb = false;
      bool mMKrZODlkn = false;
      bool BAmTqEcepN = false;
      bool XhUWsGOhyB = false;
      bool sKcMuTwnIj = false;
      bool SExLbpTOrI = false;
      bool SXsyDEqnzS = false;
      string GKoYDbLzSk;
      string yJmpHJUIRK;
      string zRqAESwHHC;
      string BIaQzCSoyJ;
      string BXUFhCUfAQ;
      string lxEVgoTnUj;
      string eEqQjpiVpF;
      string qfKHJbxlSB;
      string xPGqQDEFjK;
      string idUNdxfDUr;
      string TzpuYGmwLF;
      string qgVSlOxAAg;
      string kdlfVNKwdM;
      string usQZhyZLRJ;
      string PHsdTBHBaP;
      string zeDnGpNJYL;
      string uqSzJxQwkn;
      string nlhpRdjHLU;
      string FJUNNQpbTr;
      string kQmGOYosUV;
      if(GKoYDbLzSk == TzpuYGmwLF){kLQmaNxNWc = true;}
      else if(TzpuYGmwLF == GKoYDbLzSk){LJNpkORVAi = true;}
      if(yJmpHJUIRK == qgVSlOxAAg){FFyEFkVEls = true;}
      else if(qgVSlOxAAg == yJmpHJUIRK){NxRLxxuoni = true;}
      if(zRqAESwHHC == kdlfVNKwdM){HncrDXzaar = true;}
      else if(kdlfVNKwdM == zRqAESwHHC){fHghzWpiAc = true;}
      if(BIaQzCSoyJ == usQZhyZLRJ){opmpitshlz = true;}
      else if(usQZhyZLRJ == BIaQzCSoyJ){pHiiMuDjLb = true;}
      if(BXUFhCUfAQ == PHsdTBHBaP){SbFqleRhAd = true;}
      else if(PHsdTBHBaP == BXUFhCUfAQ){mMKrZODlkn = true;}
      if(lxEVgoTnUj == zeDnGpNJYL){CjHaOwiXjD = true;}
      else if(zeDnGpNJYL == lxEVgoTnUj){BAmTqEcepN = true;}
      if(eEqQjpiVpF == uqSzJxQwkn){OVldmOSIUK = true;}
      else if(uqSzJxQwkn == eEqQjpiVpF){XhUWsGOhyB = true;}
      if(qfKHJbxlSB == nlhpRdjHLU){rnRlZeilGY = true;}
      if(xPGqQDEFjK == FJUNNQpbTr){FQZxpEhLam = true;}
      if(idUNdxfDUr == kQmGOYosUV){LUxikxoaDW = true;}
      while(nlhpRdjHLU == qfKHJbxlSB){sKcMuTwnIj = true;}
      while(FJUNNQpbTr == FJUNNQpbTr){SExLbpTOrI = true;}
      while(kQmGOYosUV == kQmGOYosUV){SXsyDEqnzS = true;}
      if(kLQmaNxNWc == true){kLQmaNxNWc = false;}
      if(FFyEFkVEls == true){FFyEFkVEls = false;}
      if(HncrDXzaar == true){HncrDXzaar = false;}
      if(opmpitshlz == true){opmpitshlz = false;}
      if(SbFqleRhAd == true){SbFqleRhAd = false;}
      if(CjHaOwiXjD == true){CjHaOwiXjD = false;}
      if(OVldmOSIUK == true){OVldmOSIUK = false;}
      if(rnRlZeilGY == true){rnRlZeilGY = false;}
      if(FQZxpEhLam == true){FQZxpEhLam = false;}
      if(LUxikxoaDW == true){LUxikxoaDW = false;}
      if(LJNpkORVAi == true){LJNpkORVAi = false;}
      if(NxRLxxuoni == true){NxRLxxuoni = false;}
      if(fHghzWpiAc == true){fHghzWpiAc = false;}
      if(pHiiMuDjLb == true){pHiiMuDjLb = false;}
      if(mMKrZODlkn == true){mMKrZODlkn = false;}
      if(BAmTqEcepN == true){BAmTqEcepN = false;}
      if(XhUWsGOhyB == true){XhUWsGOhyB = false;}
      if(sKcMuTwnIj == true){sKcMuTwnIj = false;}
      if(SExLbpTOrI == true){SExLbpTOrI = false;}
      if(SXsyDEqnzS == true){SXsyDEqnzS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKRIKADUFC
{ 
  void pywCmZINEC()
  { 
      bool XTTVMKJCku = false;
      bool NStGbMAmfx = false;
      bool HuoUfycpky = false;
      bool sqUboPnOEA = false;
      bool pNSKNlPIei = false;
      bool LONRJbezpN = false;
      bool gSRmCVySQL = false;
      bool YkhfHsceHs = false;
      bool hTLBlddDRM = false;
      bool koXpSWweIq = false;
      bool nxrSKZfgJP = false;
      bool zzrxfNHPBX = false;
      bool ruAEajNqMj = false;
      bool wyWPEkbrpL = false;
      bool xxsCNkwaKF = false;
      bool Pfdjzswmra = false;
      bool MoUYSBcbrt = false;
      bool kOYoZtCyqo = false;
      bool mmfGUQTlQL = false;
      bool onAPyIcTiM = false;
      string yuzEezOkhj;
      string sEVVhhUCGn;
      string BkqXiadzpT;
      string AwpFaafIHt;
      string tTymlkQOLM;
      string GYBzlMDaUE;
      string UOtNiwNPuH;
      string CMuLsgmEkx;
      string JPmcMauqSN;
      string WEmCZeYkEp;
      string WASEKtdpFF;
      string ZzpWtEbRAH;
      string AWxgjyYrkN;
      string HBAuaIwiSS;
      string xFkMnWOQHU;
      string DHjwozDlTL;
      string VkEqxXztwk;
      string IryhKtkjrM;
      string jIkQKzQDFa;
      string FJPHwMBtPQ;
      if(yuzEezOkhj == WASEKtdpFF){XTTVMKJCku = true;}
      else if(WASEKtdpFF == yuzEezOkhj){nxrSKZfgJP = true;}
      if(sEVVhhUCGn == ZzpWtEbRAH){NStGbMAmfx = true;}
      else if(ZzpWtEbRAH == sEVVhhUCGn){zzrxfNHPBX = true;}
      if(BkqXiadzpT == AWxgjyYrkN){HuoUfycpky = true;}
      else if(AWxgjyYrkN == BkqXiadzpT){ruAEajNqMj = true;}
      if(AwpFaafIHt == HBAuaIwiSS){sqUboPnOEA = true;}
      else if(HBAuaIwiSS == AwpFaafIHt){wyWPEkbrpL = true;}
      if(tTymlkQOLM == xFkMnWOQHU){pNSKNlPIei = true;}
      else if(xFkMnWOQHU == tTymlkQOLM){xxsCNkwaKF = true;}
      if(GYBzlMDaUE == DHjwozDlTL){LONRJbezpN = true;}
      else if(DHjwozDlTL == GYBzlMDaUE){Pfdjzswmra = true;}
      if(UOtNiwNPuH == VkEqxXztwk){gSRmCVySQL = true;}
      else if(VkEqxXztwk == UOtNiwNPuH){MoUYSBcbrt = true;}
      if(CMuLsgmEkx == IryhKtkjrM){YkhfHsceHs = true;}
      if(JPmcMauqSN == jIkQKzQDFa){hTLBlddDRM = true;}
      if(WEmCZeYkEp == FJPHwMBtPQ){koXpSWweIq = true;}
      while(IryhKtkjrM == CMuLsgmEkx){kOYoZtCyqo = true;}
      while(jIkQKzQDFa == jIkQKzQDFa){mmfGUQTlQL = true;}
      while(FJPHwMBtPQ == FJPHwMBtPQ){onAPyIcTiM = true;}
      if(XTTVMKJCku == true){XTTVMKJCku = false;}
      if(NStGbMAmfx == true){NStGbMAmfx = false;}
      if(HuoUfycpky == true){HuoUfycpky = false;}
      if(sqUboPnOEA == true){sqUboPnOEA = false;}
      if(pNSKNlPIei == true){pNSKNlPIei = false;}
      if(LONRJbezpN == true){LONRJbezpN = false;}
      if(gSRmCVySQL == true){gSRmCVySQL = false;}
      if(YkhfHsceHs == true){YkhfHsceHs = false;}
      if(hTLBlddDRM == true){hTLBlddDRM = false;}
      if(koXpSWweIq == true){koXpSWweIq = false;}
      if(nxrSKZfgJP == true){nxrSKZfgJP = false;}
      if(zzrxfNHPBX == true){zzrxfNHPBX = false;}
      if(ruAEajNqMj == true){ruAEajNqMj = false;}
      if(wyWPEkbrpL == true){wyWPEkbrpL = false;}
      if(xxsCNkwaKF == true){xxsCNkwaKF = false;}
      if(Pfdjzswmra == true){Pfdjzswmra = false;}
      if(MoUYSBcbrt == true){MoUYSBcbrt = false;}
      if(kOYoZtCyqo == true){kOYoZtCyqo = false;}
      if(mmfGUQTlQL == true){mmfGUQTlQL = false;}
      if(onAPyIcTiM == true){onAPyIcTiM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDAFBCCCRT
{ 
  void DGVjBfcjeo()
  { 
      bool qXoVyaJxFg = false;
      bool oewdHNKUio = false;
      bool NdSlyRmjmR = false;
      bool VRKoFTBKTZ = false;
      bool bsLNeNsLLi = false;
      bool KcJLAMFCXf = false;
      bool mYJnKWUHYn = false;
      bool LABINTSEHj = false;
      bool YaYEGrIznr = false;
      bool NzlmmCiXCH = false;
      bool sklWWKaAyf = false;
      bool tAunHMAFgS = false;
      bool NUSgZMOOVK = false;
      bool jtBzpmnBgw = false;
      bool RHAHxMDyeZ = false;
      bool CcpjsXRFxK = false;
      bool uMemwzzwxT = false;
      bool XyYkAGULiM = false;
      bool IPiuIGDQFS = false;
      bool ViEWAEcNLx = false;
      string yRXXcumJXV;
      string jKmSmeLTiW;
      string YiDLrioRut;
      string UhHAGIGCjI;
      string TuuxJnSfoA;
      string BVkqAONLfs;
      string FVOdBCCmLe;
      string XJjaCdnGCE;
      string QIbtszwQzr;
      string tuWpCxfQuG;
      string kfTKbqkKoW;
      string aHJacxtUkB;
      string FlnTjcmtXE;
      string xWLuTkoQRB;
      string NkbbRmkuNF;
      string DLfsAzqzaz;
      string EqmjZDuNGq;
      string HcCinTJLCw;
      string qqfRBkpRtU;
      string sppSwVyrBN;
      if(yRXXcumJXV == kfTKbqkKoW){qXoVyaJxFg = true;}
      else if(kfTKbqkKoW == yRXXcumJXV){sklWWKaAyf = true;}
      if(jKmSmeLTiW == aHJacxtUkB){oewdHNKUio = true;}
      else if(aHJacxtUkB == jKmSmeLTiW){tAunHMAFgS = true;}
      if(YiDLrioRut == FlnTjcmtXE){NdSlyRmjmR = true;}
      else if(FlnTjcmtXE == YiDLrioRut){NUSgZMOOVK = true;}
      if(UhHAGIGCjI == xWLuTkoQRB){VRKoFTBKTZ = true;}
      else if(xWLuTkoQRB == UhHAGIGCjI){jtBzpmnBgw = true;}
      if(TuuxJnSfoA == NkbbRmkuNF){bsLNeNsLLi = true;}
      else if(NkbbRmkuNF == TuuxJnSfoA){RHAHxMDyeZ = true;}
      if(BVkqAONLfs == DLfsAzqzaz){KcJLAMFCXf = true;}
      else if(DLfsAzqzaz == BVkqAONLfs){CcpjsXRFxK = true;}
      if(FVOdBCCmLe == EqmjZDuNGq){mYJnKWUHYn = true;}
      else if(EqmjZDuNGq == FVOdBCCmLe){uMemwzzwxT = true;}
      if(XJjaCdnGCE == HcCinTJLCw){LABINTSEHj = true;}
      if(QIbtszwQzr == qqfRBkpRtU){YaYEGrIznr = true;}
      if(tuWpCxfQuG == sppSwVyrBN){NzlmmCiXCH = true;}
      while(HcCinTJLCw == XJjaCdnGCE){XyYkAGULiM = true;}
      while(qqfRBkpRtU == qqfRBkpRtU){IPiuIGDQFS = true;}
      while(sppSwVyrBN == sppSwVyrBN){ViEWAEcNLx = true;}
      if(qXoVyaJxFg == true){qXoVyaJxFg = false;}
      if(oewdHNKUio == true){oewdHNKUio = false;}
      if(NdSlyRmjmR == true){NdSlyRmjmR = false;}
      if(VRKoFTBKTZ == true){VRKoFTBKTZ = false;}
      if(bsLNeNsLLi == true){bsLNeNsLLi = false;}
      if(KcJLAMFCXf == true){KcJLAMFCXf = false;}
      if(mYJnKWUHYn == true){mYJnKWUHYn = false;}
      if(LABINTSEHj == true){LABINTSEHj = false;}
      if(YaYEGrIznr == true){YaYEGrIznr = false;}
      if(NzlmmCiXCH == true){NzlmmCiXCH = false;}
      if(sklWWKaAyf == true){sklWWKaAyf = false;}
      if(tAunHMAFgS == true){tAunHMAFgS = false;}
      if(NUSgZMOOVK == true){NUSgZMOOVK = false;}
      if(jtBzpmnBgw == true){jtBzpmnBgw = false;}
      if(RHAHxMDyeZ == true){RHAHxMDyeZ = false;}
      if(CcpjsXRFxK == true){CcpjsXRFxK = false;}
      if(uMemwzzwxT == true){uMemwzzwxT = false;}
      if(XyYkAGULiM == true){XyYkAGULiM = false;}
      if(IPiuIGDQFS == true){IPiuIGDQFS = false;}
      if(ViEWAEcNLx == true){ViEWAEcNLx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHMNBXRBMH
{ 
  void jmuczhhfaN()
  { 
      bool OOnXTjnJJr = false;
      bool HEUwMDQcJU = false;
      bool TmqZrdoUrg = false;
      bool XsTIwbjkCo = false;
      bool WabREVBGQi = false;
      bool RgNWYbWOeo = false;
      bool tTRbUNjLAj = false;
      bool SfaTxrKZVW = false;
      bool biDIPpfxiT = false;
      bool EVFNuDJzwp = false;
      bool loFgQlGsZf = false;
      bool RwrIMKPJMd = false;
      bool gmcffxZMYs = false;
      bool iKcekmcWrc = false;
      bool jmXDCHcxAj = false;
      bool mzmSJzMYAS = false;
      bool LsUfxGSNXZ = false;
      bool gsRittOZdX = false;
      bool TcLoFiXKVk = false;
      bool ZEVYRpSqGw = false;
      string dLAgSWSYIS;
      string mTaAnstxYm;
      string zlRNgVOwFT;
      string KtIrVRmwxU;
      string DkZHLDgAcP;
      string ZasTqrtlzx;
      string HWToIsKidV;
      string GxADiOLJCc;
      string nOSosiAoAd;
      string WAxAMgQkyS;
      string syVGIcZpjc;
      string fjjVIsEeuY;
      string rUizyGAApB;
      string xaLijprLfP;
      string IKEWymPaqT;
      string cloZZXPVIC;
      string cZzhfFYBlS;
      string AsyePhQLBL;
      string pYIVYLkkJL;
      string ZVDdmiKWqs;
      if(dLAgSWSYIS == syVGIcZpjc){OOnXTjnJJr = true;}
      else if(syVGIcZpjc == dLAgSWSYIS){loFgQlGsZf = true;}
      if(mTaAnstxYm == fjjVIsEeuY){HEUwMDQcJU = true;}
      else if(fjjVIsEeuY == mTaAnstxYm){RwrIMKPJMd = true;}
      if(zlRNgVOwFT == rUizyGAApB){TmqZrdoUrg = true;}
      else if(rUizyGAApB == zlRNgVOwFT){gmcffxZMYs = true;}
      if(KtIrVRmwxU == xaLijprLfP){XsTIwbjkCo = true;}
      else if(xaLijprLfP == KtIrVRmwxU){iKcekmcWrc = true;}
      if(DkZHLDgAcP == IKEWymPaqT){WabREVBGQi = true;}
      else if(IKEWymPaqT == DkZHLDgAcP){jmXDCHcxAj = true;}
      if(ZasTqrtlzx == cloZZXPVIC){RgNWYbWOeo = true;}
      else if(cloZZXPVIC == ZasTqrtlzx){mzmSJzMYAS = true;}
      if(HWToIsKidV == cZzhfFYBlS){tTRbUNjLAj = true;}
      else if(cZzhfFYBlS == HWToIsKidV){LsUfxGSNXZ = true;}
      if(GxADiOLJCc == AsyePhQLBL){SfaTxrKZVW = true;}
      if(nOSosiAoAd == pYIVYLkkJL){biDIPpfxiT = true;}
      if(WAxAMgQkyS == ZVDdmiKWqs){EVFNuDJzwp = true;}
      while(AsyePhQLBL == GxADiOLJCc){gsRittOZdX = true;}
      while(pYIVYLkkJL == pYIVYLkkJL){TcLoFiXKVk = true;}
      while(ZVDdmiKWqs == ZVDdmiKWqs){ZEVYRpSqGw = true;}
      if(OOnXTjnJJr == true){OOnXTjnJJr = false;}
      if(HEUwMDQcJU == true){HEUwMDQcJU = false;}
      if(TmqZrdoUrg == true){TmqZrdoUrg = false;}
      if(XsTIwbjkCo == true){XsTIwbjkCo = false;}
      if(WabREVBGQi == true){WabREVBGQi = false;}
      if(RgNWYbWOeo == true){RgNWYbWOeo = false;}
      if(tTRbUNjLAj == true){tTRbUNjLAj = false;}
      if(SfaTxrKZVW == true){SfaTxrKZVW = false;}
      if(biDIPpfxiT == true){biDIPpfxiT = false;}
      if(EVFNuDJzwp == true){EVFNuDJzwp = false;}
      if(loFgQlGsZf == true){loFgQlGsZf = false;}
      if(RwrIMKPJMd == true){RwrIMKPJMd = false;}
      if(gmcffxZMYs == true){gmcffxZMYs = false;}
      if(iKcekmcWrc == true){iKcekmcWrc = false;}
      if(jmXDCHcxAj == true){jmXDCHcxAj = false;}
      if(mzmSJzMYAS == true){mzmSJzMYAS = false;}
      if(LsUfxGSNXZ == true){LsUfxGSNXZ = false;}
      if(gsRittOZdX == true){gsRittOZdX = false;}
      if(TcLoFiXKVk == true){TcLoFiXKVk = false;}
      if(ZEVYRpSqGw == true){ZEVYRpSqGw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBRMZATOCA
{ 
  void pXJqyDBZEV()
  { 
      bool SfVNHRQsgV = false;
      bool gdFoTywsHS = false;
      bool CenKQlfoJz = false;
      bool BGVHxboaoW = false;
      bool DKDQcCpNhP = false;
      bool ManqJmrKwV = false;
      bool kbigUZIyqq = false;
      bool JVDjPrbXgO = false;
      bool uSGtmZRexK = false;
      bool jedTkbaVuD = false;
      bool tqVpFpXEaQ = false;
      bool KTchZRUntu = false;
      bool HdAfHdqiyn = false;
      bool QFbdUDxPnw = false;
      bool BNDgAPButT = false;
      bool GmbzuPqpib = false;
      bool zoFlAErzNV = false;
      bool UFzytsZTfr = false;
      bool cunegddbiE = false;
      bool MHgMxLIRgu = false;
      string rtATZCkinu;
      string JSSjBwFXBW;
      string agmrdFUkqG;
      string PqtdFeUwVY;
      string qVwWpDapZU;
      string VlEQSLGHpU;
      string gArheSYneW;
      string bIBcfEjQCZ;
      string eeKVkdlcKs;
      string XMGBqpcOqX;
      string emKDrMjbkO;
      string bpFPpCpVxB;
      string fuckyPCzlo;
      string aUZdtqUHdY;
      string sKrwRhHqLo;
      string AHRoqjKYEb;
      string KjpwmGPaUy;
      string giqXIVCfSP;
      string ILnxnTDjlK;
      string guCCNIUwJL;
      if(rtATZCkinu == emKDrMjbkO){SfVNHRQsgV = true;}
      else if(emKDrMjbkO == rtATZCkinu){tqVpFpXEaQ = true;}
      if(JSSjBwFXBW == bpFPpCpVxB){gdFoTywsHS = true;}
      else if(bpFPpCpVxB == JSSjBwFXBW){KTchZRUntu = true;}
      if(agmrdFUkqG == fuckyPCzlo){CenKQlfoJz = true;}
      else if(fuckyPCzlo == agmrdFUkqG){HdAfHdqiyn = true;}
      if(PqtdFeUwVY == aUZdtqUHdY){BGVHxboaoW = true;}
      else if(aUZdtqUHdY == PqtdFeUwVY){QFbdUDxPnw = true;}
      if(qVwWpDapZU == sKrwRhHqLo){DKDQcCpNhP = true;}
      else if(sKrwRhHqLo == qVwWpDapZU){BNDgAPButT = true;}
      if(VlEQSLGHpU == AHRoqjKYEb){ManqJmrKwV = true;}
      else if(AHRoqjKYEb == VlEQSLGHpU){GmbzuPqpib = true;}
      if(gArheSYneW == KjpwmGPaUy){kbigUZIyqq = true;}
      else if(KjpwmGPaUy == gArheSYneW){zoFlAErzNV = true;}
      if(bIBcfEjQCZ == giqXIVCfSP){JVDjPrbXgO = true;}
      if(eeKVkdlcKs == ILnxnTDjlK){uSGtmZRexK = true;}
      if(XMGBqpcOqX == guCCNIUwJL){jedTkbaVuD = true;}
      while(giqXIVCfSP == bIBcfEjQCZ){UFzytsZTfr = true;}
      while(ILnxnTDjlK == ILnxnTDjlK){cunegddbiE = true;}
      while(guCCNIUwJL == guCCNIUwJL){MHgMxLIRgu = true;}
      if(SfVNHRQsgV == true){SfVNHRQsgV = false;}
      if(gdFoTywsHS == true){gdFoTywsHS = false;}
      if(CenKQlfoJz == true){CenKQlfoJz = false;}
      if(BGVHxboaoW == true){BGVHxboaoW = false;}
      if(DKDQcCpNhP == true){DKDQcCpNhP = false;}
      if(ManqJmrKwV == true){ManqJmrKwV = false;}
      if(kbigUZIyqq == true){kbigUZIyqq = false;}
      if(JVDjPrbXgO == true){JVDjPrbXgO = false;}
      if(uSGtmZRexK == true){uSGtmZRexK = false;}
      if(jedTkbaVuD == true){jedTkbaVuD = false;}
      if(tqVpFpXEaQ == true){tqVpFpXEaQ = false;}
      if(KTchZRUntu == true){KTchZRUntu = false;}
      if(HdAfHdqiyn == true){HdAfHdqiyn = false;}
      if(QFbdUDxPnw == true){QFbdUDxPnw = false;}
      if(BNDgAPButT == true){BNDgAPButT = false;}
      if(GmbzuPqpib == true){GmbzuPqpib = false;}
      if(zoFlAErzNV == true){zoFlAErzNV = false;}
      if(UFzytsZTfr == true){UFzytsZTfr = false;}
      if(cunegddbiE == true){cunegddbiE = false;}
      if(MHgMxLIRgu == true){MHgMxLIRgu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHTORYMBAJ
{ 
  void BPRyYWBRhf()
  { 
      bool EghXNSjRFi = false;
      bool kPbmELHVej = false;
      bool ysjCrNQfEg = false;
      bool hbytWMblXd = false;
      bool qERQJaENDW = false;
      bool bNldSKweez = false;
      bool CENYBJQgPq = false;
      bool iVxArsaTrR = false;
      bool ICbgETpUbL = false;
      bool QwGYblqsOA = false;
      bool KXyLmGQkkY = false;
      bool iblNpzcfTh = false;
      bool SuFEalOYXG = false;
      bool ChFrGkEPsy = false;
      bool CEiDbnKshc = false;
      bool JLZfgORskB = false;
      bool rqMeWBWtGE = false;
      bool tMlVeNMCbm = false;
      bool bUpuwqIYKr = false;
      bool TLerFKqDfa = false;
      string jYbRFBZtbt;
      string WLobINOOTb;
      string uUcdBVaRkV;
      string qRSQwcATpz;
      string abAsQJnSpV;
      string FGWNePuyPi;
      string ZIJFDErYfe;
      string MtXTBSUjMq;
      string hIaOPjtFlg;
      string gCEHZSStoL;
      string RPmLILhCLL;
      string uLkXBQgtpS;
      string KmmyxKpQti;
      string AZtBZSVPGD;
      string CrsZlVQfGI;
      string kXDWBebnOy;
      string VRHcLURjyh;
      string uRnlQRsMLa;
      string sJJlxbVXzu;
      string pgAIhjjQNR;
      if(jYbRFBZtbt == RPmLILhCLL){EghXNSjRFi = true;}
      else if(RPmLILhCLL == jYbRFBZtbt){KXyLmGQkkY = true;}
      if(WLobINOOTb == uLkXBQgtpS){kPbmELHVej = true;}
      else if(uLkXBQgtpS == WLobINOOTb){iblNpzcfTh = true;}
      if(uUcdBVaRkV == KmmyxKpQti){ysjCrNQfEg = true;}
      else if(KmmyxKpQti == uUcdBVaRkV){SuFEalOYXG = true;}
      if(qRSQwcATpz == AZtBZSVPGD){hbytWMblXd = true;}
      else if(AZtBZSVPGD == qRSQwcATpz){ChFrGkEPsy = true;}
      if(abAsQJnSpV == CrsZlVQfGI){qERQJaENDW = true;}
      else if(CrsZlVQfGI == abAsQJnSpV){CEiDbnKshc = true;}
      if(FGWNePuyPi == kXDWBebnOy){bNldSKweez = true;}
      else if(kXDWBebnOy == FGWNePuyPi){JLZfgORskB = true;}
      if(ZIJFDErYfe == VRHcLURjyh){CENYBJQgPq = true;}
      else if(VRHcLURjyh == ZIJFDErYfe){rqMeWBWtGE = true;}
      if(MtXTBSUjMq == uRnlQRsMLa){iVxArsaTrR = true;}
      if(hIaOPjtFlg == sJJlxbVXzu){ICbgETpUbL = true;}
      if(gCEHZSStoL == pgAIhjjQNR){QwGYblqsOA = true;}
      while(uRnlQRsMLa == MtXTBSUjMq){tMlVeNMCbm = true;}
      while(sJJlxbVXzu == sJJlxbVXzu){bUpuwqIYKr = true;}
      while(pgAIhjjQNR == pgAIhjjQNR){TLerFKqDfa = true;}
      if(EghXNSjRFi == true){EghXNSjRFi = false;}
      if(kPbmELHVej == true){kPbmELHVej = false;}
      if(ysjCrNQfEg == true){ysjCrNQfEg = false;}
      if(hbytWMblXd == true){hbytWMblXd = false;}
      if(qERQJaENDW == true){qERQJaENDW = false;}
      if(bNldSKweez == true){bNldSKweez = false;}
      if(CENYBJQgPq == true){CENYBJQgPq = false;}
      if(iVxArsaTrR == true){iVxArsaTrR = false;}
      if(ICbgETpUbL == true){ICbgETpUbL = false;}
      if(QwGYblqsOA == true){QwGYblqsOA = false;}
      if(KXyLmGQkkY == true){KXyLmGQkkY = false;}
      if(iblNpzcfTh == true){iblNpzcfTh = false;}
      if(SuFEalOYXG == true){SuFEalOYXG = false;}
      if(ChFrGkEPsy == true){ChFrGkEPsy = false;}
      if(CEiDbnKshc == true){CEiDbnKshc = false;}
      if(JLZfgORskB == true){JLZfgORskB = false;}
      if(rqMeWBWtGE == true){rqMeWBWtGE = false;}
      if(tMlVeNMCbm == true){tMlVeNMCbm = false;}
      if(bUpuwqIYKr == true){bUpuwqIYKr = false;}
      if(TLerFKqDfa == true){TLerFKqDfa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKSHPUSHHX
{ 
  void pYBlVBoTiF()
  { 
      bool gDRRYNNQOg = false;
      bool wEicPCWLIE = false;
      bool fiZEesrPSI = false;
      bool XZbujkgUJe = false;
      bool OqTUbJrCbJ = false;
      bool dmFOhxcNme = false;
      bool UxxFIVbmre = false;
      bool UBBcpoPFbU = false;
      bool ApnJejUMNl = false;
      bool HTgdJRsNLF = false;
      bool gEJwnbkbYr = false;
      bool hWkSeeJnaX = false;
      bool BPZGXAUXSY = false;
      bool wBsVnufqUD = false;
      bool yrnUEkiOze = false;
      bool HEmmDReDYm = false;
      bool GNIAwfcOdj = false;
      bool zSTWYJaFBm = false;
      bool RFYnQqOFRW = false;
      bool QbSgwkinXX = false;
      string EuhmBnBrmc;
      string erNTUwFtHX;
      string UabbwkaXUl;
      string oyojSmRZfw;
      string LxmeBtaDpB;
      string bWhrCcSGpP;
      string MdXBmgCdAh;
      string deOLMWnxZC;
      string KWgTJSPxgp;
      string TLjQihZlqU;
      string qwCIWwIWfe;
      string oVgnFowEqT;
      string QFxKOSuxbd;
      string xBFFKNUYwN;
      string KsQBBxeuKs;
      string kUtXDlzrsE;
      string BKtBgmQbdr;
      string UXHdJWouJQ;
      string nzmhscHhBY;
      string NberLAzOTN;
      if(EuhmBnBrmc == qwCIWwIWfe){gDRRYNNQOg = true;}
      else if(qwCIWwIWfe == EuhmBnBrmc){gEJwnbkbYr = true;}
      if(erNTUwFtHX == oVgnFowEqT){wEicPCWLIE = true;}
      else if(oVgnFowEqT == erNTUwFtHX){hWkSeeJnaX = true;}
      if(UabbwkaXUl == QFxKOSuxbd){fiZEesrPSI = true;}
      else if(QFxKOSuxbd == UabbwkaXUl){BPZGXAUXSY = true;}
      if(oyojSmRZfw == xBFFKNUYwN){XZbujkgUJe = true;}
      else if(xBFFKNUYwN == oyojSmRZfw){wBsVnufqUD = true;}
      if(LxmeBtaDpB == KsQBBxeuKs){OqTUbJrCbJ = true;}
      else if(KsQBBxeuKs == LxmeBtaDpB){yrnUEkiOze = true;}
      if(bWhrCcSGpP == kUtXDlzrsE){dmFOhxcNme = true;}
      else if(kUtXDlzrsE == bWhrCcSGpP){HEmmDReDYm = true;}
      if(MdXBmgCdAh == BKtBgmQbdr){UxxFIVbmre = true;}
      else if(BKtBgmQbdr == MdXBmgCdAh){GNIAwfcOdj = true;}
      if(deOLMWnxZC == UXHdJWouJQ){UBBcpoPFbU = true;}
      if(KWgTJSPxgp == nzmhscHhBY){ApnJejUMNl = true;}
      if(TLjQihZlqU == NberLAzOTN){HTgdJRsNLF = true;}
      while(UXHdJWouJQ == deOLMWnxZC){zSTWYJaFBm = true;}
      while(nzmhscHhBY == nzmhscHhBY){RFYnQqOFRW = true;}
      while(NberLAzOTN == NberLAzOTN){QbSgwkinXX = true;}
      if(gDRRYNNQOg == true){gDRRYNNQOg = false;}
      if(wEicPCWLIE == true){wEicPCWLIE = false;}
      if(fiZEesrPSI == true){fiZEesrPSI = false;}
      if(XZbujkgUJe == true){XZbujkgUJe = false;}
      if(OqTUbJrCbJ == true){OqTUbJrCbJ = false;}
      if(dmFOhxcNme == true){dmFOhxcNme = false;}
      if(UxxFIVbmre == true){UxxFIVbmre = false;}
      if(UBBcpoPFbU == true){UBBcpoPFbU = false;}
      if(ApnJejUMNl == true){ApnJejUMNl = false;}
      if(HTgdJRsNLF == true){HTgdJRsNLF = false;}
      if(gEJwnbkbYr == true){gEJwnbkbYr = false;}
      if(hWkSeeJnaX == true){hWkSeeJnaX = false;}
      if(BPZGXAUXSY == true){BPZGXAUXSY = false;}
      if(wBsVnufqUD == true){wBsVnufqUD = false;}
      if(yrnUEkiOze == true){yrnUEkiOze = false;}
      if(HEmmDReDYm == true){HEmmDReDYm = false;}
      if(GNIAwfcOdj == true){GNIAwfcOdj = false;}
      if(zSTWYJaFBm == true){zSTWYJaFBm = false;}
      if(RFYnQqOFRW == true){RFYnQqOFRW = false;}
      if(QbSgwkinXX == true){QbSgwkinXX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNCFNOQKMZ
{ 
  void aVwlHiDRzH()
  { 
      bool VRbDQdbFYg = false;
      bool IEdhZPBRFQ = false;
      bool hfHAhsoJsF = false;
      bool ywKZEhLHky = false;
      bool CVZfehKZWW = false;
      bool bwjREpJaUX = false;
      bool oSLThMsDdq = false;
      bool EtfGNMFbVz = false;
      bool hOlVcCLrVO = false;
      bool YjlNJjKGyR = false;
      bool nGwfShPcEq = false;
      bool jhFVoZfppf = false;
      bool BBhPRUHSxd = false;
      bool CzcDKbSFDu = false;
      bool lhneeqdQYi = false;
      bool DTPSQmYgNx = false;
      bool ZxfZojECKM = false;
      bool HZlutSMDka = false;
      bool pqtOZhiKlW = false;
      bool ClrFUnBOot = false;
      string yPXfBHeQNH;
      string sVftpxnFWH;
      string CCktTnMLBr;
      string upxVPVtzqI;
      string KbettegeGQ;
      string uJkjiuecLN;
      string uTOULCXKdT;
      string DoNOwZXpzo;
      string HgEkwlFMlU;
      string qQmdMqMJhq;
      string GVAlMFuVnI;
      string XndWFNPdXZ;
      string xLXJcmCiBF;
      string MNIHikfRXq;
      string piYdwCmPXz;
      string bilItuyqJZ;
      string DMUiuJfVnU;
      string hxGgiNlsMa;
      string AmKCcdazNm;
      string moIxmdOpil;
      if(yPXfBHeQNH == GVAlMFuVnI){VRbDQdbFYg = true;}
      else if(GVAlMFuVnI == yPXfBHeQNH){nGwfShPcEq = true;}
      if(sVftpxnFWH == XndWFNPdXZ){IEdhZPBRFQ = true;}
      else if(XndWFNPdXZ == sVftpxnFWH){jhFVoZfppf = true;}
      if(CCktTnMLBr == xLXJcmCiBF){hfHAhsoJsF = true;}
      else if(xLXJcmCiBF == CCktTnMLBr){BBhPRUHSxd = true;}
      if(upxVPVtzqI == MNIHikfRXq){ywKZEhLHky = true;}
      else if(MNIHikfRXq == upxVPVtzqI){CzcDKbSFDu = true;}
      if(KbettegeGQ == piYdwCmPXz){CVZfehKZWW = true;}
      else if(piYdwCmPXz == KbettegeGQ){lhneeqdQYi = true;}
      if(uJkjiuecLN == bilItuyqJZ){bwjREpJaUX = true;}
      else if(bilItuyqJZ == uJkjiuecLN){DTPSQmYgNx = true;}
      if(uTOULCXKdT == DMUiuJfVnU){oSLThMsDdq = true;}
      else if(DMUiuJfVnU == uTOULCXKdT){ZxfZojECKM = true;}
      if(DoNOwZXpzo == hxGgiNlsMa){EtfGNMFbVz = true;}
      if(HgEkwlFMlU == AmKCcdazNm){hOlVcCLrVO = true;}
      if(qQmdMqMJhq == moIxmdOpil){YjlNJjKGyR = true;}
      while(hxGgiNlsMa == DoNOwZXpzo){HZlutSMDka = true;}
      while(AmKCcdazNm == AmKCcdazNm){pqtOZhiKlW = true;}
      while(moIxmdOpil == moIxmdOpil){ClrFUnBOot = true;}
      if(VRbDQdbFYg == true){VRbDQdbFYg = false;}
      if(IEdhZPBRFQ == true){IEdhZPBRFQ = false;}
      if(hfHAhsoJsF == true){hfHAhsoJsF = false;}
      if(ywKZEhLHky == true){ywKZEhLHky = false;}
      if(CVZfehKZWW == true){CVZfehKZWW = false;}
      if(bwjREpJaUX == true){bwjREpJaUX = false;}
      if(oSLThMsDdq == true){oSLThMsDdq = false;}
      if(EtfGNMFbVz == true){EtfGNMFbVz = false;}
      if(hOlVcCLrVO == true){hOlVcCLrVO = false;}
      if(YjlNJjKGyR == true){YjlNJjKGyR = false;}
      if(nGwfShPcEq == true){nGwfShPcEq = false;}
      if(jhFVoZfppf == true){jhFVoZfppf = false;}
      if(BBhPRUHSxd == true){BBhPRUHSxd = false;}
      if(CzcDKbSFDu == true){CzcDKbSFDu = false;}
      if(lhneeqdQYi == true){lhneeqdQYi = false;}
      if(DTPSQmYgNx == true){DTPSQmYgNx = false;}
      if(ZxfZojECKM == true){ZxfZojECKM = false;}
      if(HZlutSMDka == true){HZlutSMDka = false;}
      if(pqtOZhiKlW == true){pqtOZhiKlW = false;}
      if(ClrFUnBOot == true){ClrFUnBOot = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BVQXKWHAFO
{ 
  void gGTTWdLuPX()
  { 
      bool gNFsVTjKOn = false;
      bool KlDGMkMpwA = false;
      bool LCyaTGsQAA = false;
      bool sMgFWwcqSe = false;
      bool QNExfLlYgg = false;
      bool INoMzePeZO = false;
      bool aTKNuyEyiP = false;
      bool HUXQiyxAtH = false;
      bool UTiSqeWUFr = false;
      bool gyQDEwCpCg = false;
      bool HnoRZmpXcB = false;
      bool gOjRtGjqWP = false;
      bool airphIETMl = false;
      bool uGyMAgdQsD = false;
      bool ozrDLSNzJx = false;
      bool LLTlGXuziR = false;
      bool iVKpGZQWRN = false;
      bool bSxTabqneP = false;
      bool tFKPaimLGc = false;
      bool kehbTSnCxk = false;
      string IyldnKeJDJ;
      string gytxJEscCb;
      string PkyuXYNIkk;
      string JjBbEbswXV;
      string duAWKjGXAo;
      string XyRiRWApGP;
      string wWXRzwwSrh;
      string KxEfxTkajn;
      string SoIuMLSRKg;
      string bDpIZGXhXO;
      string mnfReasklx;
      string lYFSxGObEn;
      string ddHLGHGwGq;
      string wCDVAeJpQl;
      string RgfNuCxXLS;
      string rudjjIfTKW;
      string TxduBjVjRR;
      string wXKSVwytQE;
      string KijnyAXSkq;
      string ypetRUDkMK;
      if(IyldnKeJDJ == mnfReasklx){gNFsVTjKOn = true;}
      else if(mnfReasklx == IyldnKeJDJ){HnoRZmpXcB = true;}
      if(gytxJEscCb == lYFSxGObEn){KlDGMkMpwA = true;}
      else if(lYFSxGObEn == gytxJEscCb){gOjRtGjqWP = true;}
      if(PkyuXYNIkk == ddHLGHGwGq){LCyaTGsQAA = true;}
      else if(ddHLGHGwGq == PkyuXYNIkk){airphIETMl = true;}
      if(JjBbEbswXV == wCDVAeJpQl){sMgFWwcqSe = true;}
      else if(wCDVAeJpQl == JjBbEbswXV){uGyMAgdQsD = true;}
      if(duAWKjGXAo == RgfNuCxXLS){QNExfLlYgg = true;}
      else if(RgfNuCxXLS == duAWKjGXAo){ozrDLSNzJx = true;}
      if(XyRiRWApGP == rudjjIfTKW){INoMzePeZO = true;}
      else if(rudjjIfTKW == XyRiRWApGP){LLTlGXuziR = true;}
      if(wWXRzwwSrh == TxduBjVjRR){aTKNuyEyiP = true;}
      else if(TxduBjVjRR == wWXRzwwSrh){iVKpGZQWRN = true;}
      if(KxEfxTkajn == wXKSVwytQE){HUXQiyxAtH = true;}
      if(SoIuMLSRKg == KijnyAXSkq){UTiSqeWUFr = true;}
      if(bDpIZGXhXO == ypetRUDkMK){gyQDEwCpCg = true;}
      while(wXKSVwytQE == KxEfxTkajn){bSxTabqneP = true;}
      while(KijnyAXSkq == KijnyAXSkq){tFKPaimLGc = true;}
      while(ypetRUDkMK == ypetRUDkMK){kehbTSnCxk = true;}
      if(gNFsVTjKOn == true){gNFsVTjKOn = false;}
      if(KlDGMkMpwA == true){KlDGMkMpwA = false;}
      if(LCyaTGsQAA == true){LCyaTGsQAA = false;}
      if(sMgFWwcqSe == true){sMgFWwcqSe = false;}
      if(QNExfLlYgg == true){QNExfLlYgg = false;}
      if(INoMzePeZO == true){INoMzePeZO = false;}
      if(aTKNuyEyiP == true){aTKNuyEyiP = false;}
      if(HUXQiyxAtH == true){HUXQiyxAtH = false;}
      if(UTiSqeWUFr == true){UTiSqeWUFr = false;}
      if(gyQDEwCpCg == true){gyQDEwCpCg = false;}
      if(HnoRZmpXcB == true){HnoRZmpXcB = false;}
      if(gOjRtGjqWP == true){gOjRtGjqWP = false;}
      if(airphIETMl == true){airphIETMl = false;}
      if(uGyMAgdQsD == true){uGyMAgdQsD = false;}
      if(ozrDLSNzJx == true){ozrDLSNzJx = false;}
      if(LLTlGXuziR == true){LLTlGXuziR = false;}
      if(iVKpGZQWRN == true){iVKpGZQWRN = false;}
      if(bSxTabqneP == true){bSxTabqneP = false;}
      if(tFKPaimLGc == true){tFKPaimLGc = false;}
      if(kehbTSnCxk == true){kehbTSnCxk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLKBITVUHY
{ 
  void pJlexzLiob()
  { 
      bool idVmJAbSpR = false;
      bool XxWOsdwkuA = false;
      bool PJOFLnReik = false;
      bool oQHJdjOchW = false;
      bool enEBDmLxAQ = false;
      bool GfBREYPQbV = false;
      bool iwiFcHoMkJ = false;
      bool PSDXUaFMBX = false;
      bool bTdSeIPoEE = false;
      bool UxBLniFyXu = false;
      bool xyMqAmbcwd = false;
      bool SCPDsORPaU = false;
      bool rAHfoSRqjl = false;
      bool VHoFadHmRr = false;
      bool flsalRhxRY = false;
      bool QoXDDxpfCh = false;
      bool UksKHLMJcP = false;
      bool HexinGHgtW = false;
      bool jUYKUfjkCc = false;
      bool nakjXurhTZ = false;
      string pBfgNapzGA;
      string FYgPVuJwKZ;
      string ebQnJkNJkE;
      string VIIreCfWNz;
      string brmKVfJHty;
      string quMUCOjrXc;
      string MfOCdxQnkS;
      string OmiKylnGRc;
      string aGOlNawmoQ;
      string RmyjmudkgY;
      string PUVbiDLBWP;
      string ZdauBGQbnC;
      string AdyUAanzXC;
      string IDYrNGjmCJ;
      string PtQYpnMDhf;
      string eBwdYkVBaI;
      string OMcTHVFhgu;
      string VdZdmGNYdM;
      string OkQrXGGuTb;
      string jhLttCQwRT;
      if(pBfgNapzGA == PUVbiDLBWP){idVmJAbSpR = true;}
      else if(PUVbiDLBWP == pBfgNapzGA){xyMqAmbcwd = true;}
      if(FYgPVuJwKZ == ZdauBGQbnC){XxWOsdwkuA = true;}
      else if(ZdauBGQbnC == FYgPVuJwKZ){SCPDsORPaU = true;}
      if(ebQnJkNJkE == AdyUAanzXC){PJOFLnReik = true;}
      else if(AdyUAanzXC == ebQnJkNJkE){rAHfoSRqjl = true;}
      if(VIIreCfWNz == IDYrNGjmCJ){oQHJdjOchW = true;}
      else if(IDYrNGjmCJ == VIIreCfWNz){VHoFadHmRr = true;}
      if(brmKVfJHty == PtQYpnMDhf){enEBDmLxAQ = true;}
      else if(PtQYpnMDhf == brmKVfJHty){flsalRhxRY = true;}
      if(quMUCOjrXc == eBwdYkVBaI){GfBREYPQbV = true;}
      else if(eBwdYkVBaI == quMUCOjrXc){QoXDDxpfCh = true;}
      if(MfOCdxQnkS == OMcTHVFhgu){iwiFcHoMkJ = true;}
      else if(OMcTHVFhgu == MfOCdxQnkS){UksKHLMJcP = true;}
      if(OmiKylnGRc == VdZdmGNYdM){PSDXUaFMBX = true;}
      if(aGOlNawmoQ == OkQrXGGuTb){bTdSeIPoEE = true;}
      if(RmyjmudkgY == jhLttCQwRT){UxBLniFyXu = true;}
      while(VdZdmGNYdM == OmiKylnGRc){HexinGHgtW = true;}
      while(OkQrXGGuTb == OkQrXGGuTb){jUYKUfjkCc = true;}
      while(jhLttCQwRT == jhLttCQwRT){nakjXurhTZ = true;}
      if(idVmJAbSpR == true){idVmJAbSpR = false;}
      if(XxWOsdwkuA == true){XxWOsdwkuA = false;}
      if(PJOFLnReik == true){PJOFLnReik = false;}
      if(oQHJdjOchW == true){oQHJdjOchW = false;}
      if(enEBDmLxAQ == true){enEBDmLxAQ = false;}
      if(GfBREYPQbV == true){GfBREYPQbV = false;}
      if(iwiFcHoMkJ == true){iwiFcHoMkJ = false;}
      if(PSDXUaFMBX == true){PSDXUaFMBX = false;}
      if(bTdSeIPoEE == true){bTdSeIPoEE = false;}
      if(UxBLniFyXu == true){UxBLniFyXu = false;}
      if(xyMqAmbcwd == true){xyMqAmbcwd = false;}
      if(SCPDsORPaU == true){SCPDsORPaU = false;}
      if(rAHfoSRqjl == true){rAHfoSRqjl = false;}
      if(VHoFadHmRr == true){VHoFadHmRr = false;}
      if(flsalRhxRY == true){flsalRhxRY = false;}
      if(QoXDDxpfCh == true){QoXDDxpfCh = false;}
      if(UksKHLMJcP == true){UksKHLMJcP = false;}
      if(HexinGHgtW == true){HexinGHgtW = false;}
      if(jUYKUfjkCc == true){jUYKUfjkCc = false;}
      if(nakjXurhTZ == true){nakjXurhTZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJYLJVPLWS
{ 
  void dzwUILzIMw()
  { 
      bool xAwtpukbtY = false;
      bool McrnalzVJH = false;
      bool jPoXonunaa = false;
      bool fDiDuJILqb = false;
      bool YqQyYPEWrQ = false;
      bool olAjxhKYFC = false;
      bool AxBSrJsosR = false;
      bool dndghsyqzY = false;
      bool jXuKlsCyGM = false;
      bool yiGobapyFO = false;
      bool VPdalAHSCE = false;
      bool iTZfSbCqfz = false;
      bool HthfSthoFH = false;
      bool DAkjCTtUXk = false;
      bool kiwBdeJZVA = false;
      bool YyRGHbgyHr = false;
      bool SSNtBihody = false;
      bool ghTuNXxgBm = false;
      bool jHSFhEhdba = false;
      bool mwMeRSVCAt = false;
      string ZAjsSUUYLK;
      string OrdhBqiXkR;
      string lwJmexZeBq;
      string PnkLsMIsek;
      string pcuQnlIsnp;
      string tfNjedpxOV;
      string tpXTtZGRnn;
      string hprAaJAryr;
      string ogqLxiZBfP;
      string WLdJpAFbWN;
      string fpEzHDnNIV;
      string cxyWgNyLWL;
      string AFkYRWMhJa;
      string DYVkMybrEs;
      string uLrJlYNHcb;
      string CsFKNZEegj;
      string qFDhREaNKh;
      string kGHcQnMbls;
      string JFFhXKTLXl;
      string sxKTCoIJrh;
      if(ZAjsSUUYLK == fpEzHDnNIV){xAwtpukbtY = true;}
      else if(fpEzHDnNIV == ZAjsSUUYLK){VPdalAHSCE = true;}
      if(OrdhBqiXkR == cxyWgNyLWL){McrnalzVJH = true;}
      else if(cxyWgNyLWL == OrdhBqiXkR){iTZfSbCqfz = true;}
      if(lwJmexZeBq == AFkYRWMhJa){jPoXonunaa = true;}
      else if(AFkYRWMhJa == lwJmexZeBq){HthfSthoFH = true;}
      if(PnkLsMIsek == DYVkMybrEs){fDiDuJILqb = true;}
      else if(DYVkMybrEs == PnkLsMIsek){DAkjCTtUXk = true;}
      if(pcuQnlIsnp == uLrJlYNHcb){YqQyYPEWrQ = true;}
      else if(uLrJlYNHcb == pcuQnlIsnp){kiwBdeJZVA = true;}
      if(tfNjedpxOV == CsFKNZEegj){olAjxhKYFC = true;}
      else if(CsFKNZEegj == tfNjedpxOV){YyRGHbgyHr = true;}
      if(tpXTtZGRnn == qFDhREaNKh){AxBSrJsosR = true;}
      else if(qFDhREaNKh == tpXTtZGRnn){SSNtBihody = true;}
      if(hprAaJAryr == kGHcQnMbls){dndghsyqzY = true;}
      if(ogqLxiZBfP == JFFhXKTLXl){jXuKlsCyGM = true;}
      if(WLdJpAFbWN == sxKTCoIJrh){yiGobapyFO = true;}
      while(kGHcQnMbls == hprAaJAryr){ghTuNXxgBm = true;}
      while(JFFhXKTLXl == JFFhXKTLXl){jHSFhEhdba = true;}
      while(sxKTCoIJrh == sxKTCoIJrh){mwMeRSVCAt = true;}
      if(xAwtpukbtY == true){xAwtpukbtY = false;}
      if(McrnalzVJH == true){McrnalzVJH = false;}
      if(jPoXonunaa == true){jPoXonunaa = false;}
      if(fDiDuJILqb == true){fDiDuJILqb = false;}
      if(YqQyYPEWrQ == true){YqQyYPEWrQ = false;}
      if(olAjxhKYFC == true){olAjxhKYFC = false;}
      if(AxBSrJsosR == true){AxBSrJsosR = false;}
      if(dndghsyqzY == true){dndghsyqzY = false;}
      if(jXuKlsCyGM == true){jXuKlsCyGM = false;}
      if(yiGobapyFO == true){yiGobapyFO = false;}
      if(VPdalAHSCE == true){VPdalAHSCE = false;}
      if(iTZfSbCqfz == true){iTZfSbCqfz = false;}
      if(HthfSthoFH == true){HthfSthoFH = false;}
      if(DAkjCTtUXk == true){DAkjCTtUXk = false;}
      if(kiwBdeJZVA == true){kiwBdeJZVA = false;}
      if(YyRGHbgyHr == true){YyRGHbgyHr = false;}
      if(SSNtBihody == true){SSNtBihody = false;}
      if(ghTuNXxgBm == true){ghTuNXxgBm = false;}
      if(jHSFhEhdba == true){jHSFhEhdba = false;}
      if(mwMeRSVCAt == true){mwMeRSVCAt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGPUKYOXRR
{ 
  void mIVPBQEUDr()
  { 
      bool fOgpMGmSwy = false;
      bool DqBrHJUZQl = false;
      bool msjTimSdku = false;
      bool bTYIsgznaz = false;
      bool zGZVKBeRwY = false;
      bool lNYRlldMGY = false;
      bool mIhAWiSsyZ = false;
      bool JfzRlfSOIg = false;
      bool HBgLJOtGVG = false;
      bool DlhBLqXZza = false;
      bool ilSVOFOHfF = false;
      bool TPEZRlbVqH = false;
      bool oLWrWXyxFu = false;
      bool HsPhxUhKxD = false;
      bool AmaQmnhHjZ = false;
      bool OChqlXPazq = false;
      bool HQBjxZAVcw = false;
      bool DQYmHBjGEi = false;
      bool opMfgFKXwY = false;
      bool FHLFwikqSM = false;
      string eNwXKxSgMO;
      string AObuAeOpFf;
      string xSxszftCOL;
      string DBPKTxJwlT;
      string DddTekrcon;
      string CASoALPCXd;
      string CQRALzyQaC;
      string VSEkbTodOO;
      string nRNaIChZKI;
      string hGXHRmLdHe;
      string laBlSjwgMg;
      string WlnJojDpqI;
      string QXGSUOtwTo;
      string HKVibNPaIX;
      string GBNckuSNRg;
      string iUlzONTiQD;
      string pzNWYLPEgb;
      string TchSCPKcgY;
      string ufemFlYWUN;
      string sgJEhGmpEY;
      if(eNwXKxSgMO == laBlSjwgMg){fOgpMGmSwy = true;}
      else if(laBlSjwgMg == eNwXKxSgMO){ilSVOFOHfF = true;}
      if(AObuAeOpFf == WlnJojDpqI){DqBrHJUZQl = true;}
      else if(WlnJojDpqI == AObuAeOpFf){TPEZRlbVqH = true;}
      if(xSxszftCOL == QXGSUOtwTo){msjTimSdku = true;}
      else if(QXGSUOtwTo == xSxszftCOL){oLWrWXyxFu = true;}
      if(DBPKTxJwlT == HKVibNPaIX){bTYIsgznaz = true;}
      else if(HKVibNPaIX == DBPKTxJwlT){HsPhxUhKxD = true;}
      if(DddTekrcon == GBNckuSNRg){zGZVKBeRwY = true;}
      else if(GBNckuSNRg == DddTekrcon){AmaQmnhHjZ = true;}
      if(CASoALPCXd == iUlzONTiQD){lNYRlldMGY = true;}
      else if(iUlzONTiQD == CASoALPCXd){OChqlXPazq = true;}
      if(CQRALzyQaC == pzNWYLPEgb){mIhAWiSsyZ = true;}
      else if(pzNWYLPEgb == CQRALzyQaC){HQBjxZAVcw = true;}
      if(VSEkbTodOO == TchSCPKcgY){JfzRlfSOIg = true;}
      if(nRNaIChZKI == ufemFlYWUN){HBgLJOtGVG = true;}
      if(hGXHRmLdHe == sgJEhGmpEY){DlhBLqXZza = true;}
      while(TchSCPKcgY == VSEkbTodOO){DQYmHBjGEi = true;}
      while(ufemFlYWUN == ufemFlYWUN){opMfgFKXwY = true;}
      while(sgJEhGmpEY == sgJEhGmpEY){FHLFwikqSM = true;}
      if(fOgpMGmSwy == true){fOgpMGmSwy = false;}
      if(DqBrHJUZQl == true){DqBrHJUZQl = false;}
      if(msjTimSdku == true){msjTimSdku = false;}
      if(bTYIsgznaz == true){bTYIsgznaz = false;}
      if(zGZVKBeRwY == true){zGZVKBeRwY = false;}
      if(lNYRlldMGY == true){lNYRlldMGY = false;}
      if(mIhAWiSsyZ == true){mIhAWiSsyZ = false;}
      if(JfzRlfSOIg == true){JfzRlfSOIg = false;}
      if(HBgLJOtGVG == true){HBgLJOtGVG = false;}
      if(DlhBLqXZza == true){DlhBLqXZza = false;}
      if(ilSVOFOHfF == true){ilSVOFOHfF = false;}
      if(TPEZRlbVqH == true){TPEZRlbVqH = false;}
      if(oLWrWXyxFu == true){oLWrWXyxFu = false;}
      if(HsPhxUhKxD == true){HsPhxUhKxD = false;}
      if(AmaQmnhHjZ == true){AmaQmnhHjZ = false;}
      if(OChqlXPazq == true){OChqlXPazq = false;}
      if(HQBjxZAVcw == true){HQBjxZAVcw = false;}
      if(DQYmHBjGEi == true){DQYmHBjGEi = false;}
      if(opMfgFKXwY == true){opMfgFKXwY = false;}
      if(FHLFwikqSM == true){FHLFwikqSM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNSYXLUJGY
{ 
  void lnStqUDthp()
  { 
      bool NddwlAbLIK = false;
      bool WBmtJjOlTu = false;
      bool LqeGUmLazJ = false;
      bool WRweODyHNp = false;
      bool PcPqgakXFW = false;
      bool iaZLYVyXby = false;
      bool oBMymEEIeF = false;
      bool kHYdehanYs = false;
      bool CnUbZuqkGs = false;
      bool FaePBOQRDc = false;
      bool VcsAkbCwfp = false;
      bool tKyhwAfjYr = false;
      bool MTClAKbJbQ = false;
      bool QJkwWYtUqy = false;
      bool rtEPyubwSA = false;
      bool hgrLPBaGAZ = false;
      bool AsUPZjZCKW = false;
      bool FLrZzRPlmF = false;
      bool hepahiQYfV = false;
      bool ynURyzZnpN = false;
      string UxYzeCSnQW;
      string UEEoCVqDxC;
      string YQRVGUehDp;
      string SDtPwNpigL;
      string hzSpuNoxRN;
      string olUEXEfDrJ;
      string WjkaDRJnso;
      string eIVlUYxaZr;
      string fhQoAfhprq;
      string hmpXnyOqmd;
      string EAEcifQiiy;
      string GEcAcoSwZW;
      string iTwBGrSyxW;
      string KGnwnfcnFT;
      string PzGtkdKpty;
      string eSRPtjDDVq;
      string NSkLmAQgLx;
      string MdpFHjMCPb;
      string gcDzqroYBE;
      string bYROGxNtGj;
      if(UxYzeCSnQW == EAEcifQiiy){NddwlAbLIK = true;}
      else if(EAEcifQiiy == UxYzeCSnQW){VcsAkbCwfp = true;}
      if(UEEoCVqDxC == GEcAcoSwZW){WBmtJjOlTu = true;}
      else if(GEcAcoSwZW == UEEoCVqDxC){tKyhwAfjYr = true;}
      if(YQRVGUehDp == iTwBGrSyxW){LqeGUmLazJ = true;}
      else if(iTwBGrSyxW == YQRVGUehDp){MTClAKbJbQ = true;}
      if(SDtPwNpigL == KGnwnfcnFT){WRweODyHNp = true;}
      else if(KGnwnfcnFT == SDtPwNpigL){QJkwWYtUqy = true;}
      if(hzSpuNoxRN == PzGtkdKpty){PcPqgakXFW = true;}
      else if(PzGtkdKpty == hzSpuNoxRN){rtEPyubwSA = true;}
      if(olUEXEfDrJ == eSRPtjDDVq){iaZLYVyXby = true;}
      else if(eSRPtjDDVq == olUEXEfDrJ){hgrLPBaGAZ = true;}
      if(WjkaDRJnso == NSkLmAQgLx){oBMymEEIeF = true;}
      else if(NSkLmAQgLx == WjkaDRJnso){AsUPZjZCKW = true;}
      if(eIVlUYxaZr == MdpFHjMCPb){kHYdehanYs = true;}
      if(fhQoAfhprq == gcDzqroYBE){CnUbZuqkGs = true;}
      if(hmpXnyOqmd == bYROGxNtGj){FaePBOQRDc = true;}
      while(MdpFHjMCPb == eIVlUYxaZr){FLrZzRPlmF = true;}
      while(gcDzqroYBE == gcDzqroYBE){hepahiQYfV = true;}
      while(bYROGxNtGj == bYROGxNtGj){ynURyzZnpN = true;}
      if(NddwlAbLIK == true){NddwlAbLIK = false;}
      if(WBmtJjOlTu == true){WBmtJjOlTu = false;}
      if(LqeGUmLazJ == true){LqeGUmLazJ = false;}
      if(WRweODyHNp == true){WRweODyHNp = false;}
      if(PcPqgakXFW == true){PcPqgakXFW = false;}
      if(iaZLYVyXby == true){iaZLYVyXby = false;}
      if(oBMymEEIeF == true){oBMymEEIeF = false;}
      if(kHYdehanYs == true){kHYdehanYs = false;}
      if(CnUbZuqkGs == true){CnUbZuqkGs = false;}
      if(FaePBOQRDc == true){FaePBOQRDc = false;}
      if(VcsAkbCwfp == true){VcsAkbCwfp = false;}
      if(tKyhwAfjYr == true){tKyhwAfjYr = false;}
      if(MTClAKbJbQ == true){MTClAKbJbQ = false;}
      if(QJkwWYtUqy == true){QJkwWYtUqy = false;}
      if(rtEPyubwSA == true){rtEPyubwSA = false;}
      if(hgrLPBaGAZ == true){hgrLPBaGAZ = false;}
      if(AsUPZjZCKW == true){AsUPZjZCKW = false;}
      if(FLrZzRPlmF == true){FLrZzRPlmF = false;}
      if(hepahiQYfV == true){hepahiQYfV = false;}
      if(ynURyzZnpN == true){ynURyzZnpN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HJVYFOHUJO
{ 
  void hWalDXxnpo()
  { 
      bool huTyRKVWrL = false;
      bool wOSIEHdJCn = false;
      bool OGaauXnKaU = false;
      bool oMhZXzKNrp = false;
      bool FuJUsuGRVD = false;
      bool sfOZZaTsDs = false;
      bool VKwXWjgrjE = false;
      bool wQRMhTxGgA = false;
      bool RVoWaJxHzx = false;
      bool fRKyUuylxI = false;
      bool ONgQGcNCqG = false;
      bool dMLCbzVZxN = false;
      bool mYrmYeGTqm = false;
      bool ULJYlDoYPx = false;
      bool utQsSSGHVU = false;
      bool ZYnjVpVtqb = false;
      bool WtKDkRDmQY = false;
      bool KwJzRrHyTF = false;
      bool XyxWNwWYCu = false;
      bool gtgmZBiMHB = false;
      string eTFybsJgTs;
      string bknZytXAqp;
      string EAtXXxMCyi;
      string TkihIMOrHz;
      string lBeQVdrkyb;
      string hzihCdZgae;
      string fHhkZpBGQk;
      string efsqECVdCs;
      string FbDWATBAee;
      string mgRcSdStpe;
      string bkTNwBGrdA;
      string IwegYEELkG;
      string nBalyxOPXZ;
      string ibmWQTHpZy;
      string NJVeVqCjDO;
      string YHJjqaKhPz;
      string mpTDQgIHPE;
      string xOklreewPG;
      string teMJBbRCfo;
      string JYaaLXoROo;
      if(eTFybsJgTs == bkTNwBGrdA){huTyRKVWrL = true;}
      else if(bkTNwBGrdA == eTFybsJgTs){ONgQGcNCqG = true;}
      if(bknZytXAqp == IwegYEELkG){wOSIEHdJCn = true;}
      else if(IwegYEELkG == bknZytXAqp){dMLCbzVZxN = true;}
      if(EAtXXxMCyi == nBalyxOPXZ){OGaauXnKaU = true;}
      else if(nBalyxOPXZ == EAtXXxMCyi){mYrmYeGTqm = true;}
      if(TkihIMOrHz == ibmWQTHpZy){oMhZXzKNrp = true;}
      else if(ibmWQTHpZy == TkihIMOrHz){ULJYlDoYPx = true;}
      if(lBeQVdrkyb == NJVeVqCjDO){FuJUsuGRVD = true;}
      else if(NJVeVqCjDO == lBeQVdrkyb){utQsSSGHVU = true;}
      if(hzihCdZgae == YHJjqaKhPz){sfOZZaTsDs = true;}
      else if(YHJjqaKhPz == hzihCdZgae){ZYnjVpVtqb = true;}
      if(fHhkZpBGQk == mpTDQgIHPE){VKwXWjgrjE = true;}
      else if(mpTDQgIHPE == fHhkZpBGQk){WtKDkRDmQY = true;}
      if(efsqECVdCs == xOklreewPG){wQRMhTxGgA = true;}
      if(FbDWATBAee == teMJBbRCfo){RVoWaJxHzx = true;}
      if(mgRcSdStpe == JYaaLXoROo){fRKyUuylxI = true;}
      while(xOklreewPG == efsqECVdCs){KwJzRrHyTF = true;}
      while(teMJBbRCfo == teMJBbRCfo){XyxWNwWYCu = true;}
      while(JYaaLXoROo == JYaaLXoROo){gtgmZBiMHB = true;}
      if(huTyRKVWrL == true){huTyRKVWrL = false;}
      if(wOSIEHdJCn == true){wOSIEHdJCn = false;}
      if(OGaauXnKaU == true){OGaauXnKaU = false;}
      if(oMhZXzKNrp == true){oMhZXzKNrp = false;}
      if(FuJUsuGRVD == true){FuJUsuGRVD = false;}
      if(sfOZZaTsDs == true){sfOZZaTsDs = false;}
      if(VKwXWjgrjE == true){VKwXWjgrjE = false;}
      if(wQRMhTxGgA == true){wQRMhTxGgA = false;}
      if(RVoWaJxHzx == true){RVoWaJxHzx = false;}
      if(fRKyUuylxI == true){fRKyUuylxI = false;}
      if(ONgQGcNCqG == true){ONgQGcNCqG = false;}
      if(dMLCbzVZxN == true){dMLCbzVZxN = false;}
      if(mYrmYeGTqm == true){mYrmYeGTqm = false;}
      if(ULJYlDoYPx == true){ULJYlDoYPx = false;}
      if(utQsSSGHVU == true){utQsSSGHVU = false;}
      if(ZYnjVpVtqb == true){ZYnjVpVtqb = false;}
      if(WtKDkRDmQY == true){WtKDkRDmQY = false;}
      if(KwJzRrHyTF == true){KwJzRrHyTF = false;}
      if(XyxWNwWYCu == true){XyxWNwWYCu = false;}
      if(gtgmZBiMHB == true){gtgmZBiMHB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYBCUEEJLJ
{ 
  void pmXguLXecb()
  { 
      bool YcpiCoTSof = false;
      bool KdweYmkxrB = false;
      bool RZGwdTxbeV = false;
      bool pGnmUlKOPe = false;
      bool qtCfsSGRrW = false;
      bool oyLUGzWsFi = false;
      bool qrnTpEpJKl = false;
      bool cVhMKWXaDK = false;
      bool MfiIfruSfV = false;
      bool PQJgnyGhpo = false;
      bool cxHGsTPyKi = false;
      bool bwptVLIfmy = false;
      bool IXcoWLLBXL = false;
      bool QojNhPXcOL = false;
      bool bwHwsTZPKb = false;
      bool oZurfFTSig = false;
      bool HOaySmLbLF = false;
      bool mfRbVMPfuC = false;
      bool lwpuVptrhb = false;
      bool wFsgDNVJdG = false;
      string HkiNMeMbrh;
      string BIItazUsSD;
      string HlTlTZSOSW;
      string aeCraDrKLS;
      string yVRynACmhJ;
      string qZJVWVQwsl;
      string LxIUGVGQSX;
      string HJhAFkTUyT;
      string XegIfBVfVF;
      string luRYHAMxqS;
      string tkUKBgqJQk;
      string BuyZOgQAnF;
      string zZuNkMrIrE;
      string XWdeYmJVGz;
      string JMPjDqwqKZ;
      string jMIlSUoGYo;
      string niQMMeRSAa;
      string WtsowlJLKt;
      string PAySUKNqME;
      string xDxRKawDWX;
      if(HkiNMeMbrh == tkUKBgqJQk){YcpiCoTSof = true;}
      else if(tkUKBgqJQk == HkiNMeMbrh){cxHGsTPyKi = true;}
      if(BIItazUsSD == BuyZOgQAnF){KdweYmkxrB = true;}
      else if(BuyZOgQAnF == BIItazUsSD){bwptVLIfmy = true;}
      if(HlTlTZSOSW == zZuNkMrIrE){RZGwdTxbeV = true;}
      else if(zZuNkMrIrE == HlTlTZSOSW){IXcoWLLBXL = true;}
      if(aeCraDrKLS == XWdeYmJVGz){pGnmUlKOPe = true;}
      else if(XWdeYmJVGz == aeCraDrKLS){QojNhPXcOL = true;}
      if(yVRynACmhJ == JMPjDqwqKZ){qtCfsSGRrW = true;}
      else if(JMPjDqwqKZ == yVRynACmhJ){bwHwsTZPKb = true;}
      if(qZJVWVQwsl == jMIlSUoGYo){oyLUGzWsFi = true;}
      else if(jMIlSUoGYo == qZJVWVQwsl){oZurfFTSig = true;}
      if(LxIUGVGQSX == niQMMeRSAa){qrnTpEpJKl = true;}
      else if(niQMMeRSAa == LxIUGVGQSX){HOaySmLbLF = true;}
      if(HJhAFkTUyT == WtsowlJLKt){cVhMKWXaDK = true;}
      if(XegIfBVfVF == PAySUKNqME){MfiIfruSfV = true;}
      if(luRYHAMxqS == xDxRKawDWX){PQJgnyGhpo = true;}
      while(WtsowlJLKt == HJhAFkTUyT){mfRbVMPfuC = true;}
      while(PAySUKNqME == PAySUKNqME){lwpuVptrhb = true;}
      while(xDxRKawDWX == xDxRKawDWX){wFsgDNVJdG = true;}
      if(YcpiCoTSof == true){YcpiCoTSof = false;}
      if(KdweYmkxrB == true){KdweYmkxrB = false;}
      if(RZGwdTxbeV == true){RZGwdTxbeV = false;}
      if(pGnmUlKOPe == true){pGnmUlKOPe = false;}
      if(qtCfsSGRrW == true){qtCfsSGRrW = false;}
      if(oyLUGzWsFi == true){oyLUGzWsFi = false;}
      if(qrnTpEpJKl == true){qrnTpEpJKl = false;}
      if(cVhMKWXaDK == true){cVhMKWXaDK = false;}
      if(MfiIfruSfV == true){MfiIfruSfV = false;}
      if(PQJgnyGhpo == true){PQJgnyGhpo = false;}
      if(cxHGsTPyKi == true){cxHGsTPyKi = false;}
      if(bwptVLIfmy == true){bwptVLIfmy = false;}
      if(IXcoWLLBXL == true){IXcoWLLBXL = false;}
      if(QojNhPXcOL == true){QojNhPXcOL = false;}
      if(bwHwsTZPKb == true){bwHwsTZPKb = false;}
      if(oZurfFTSig == true){oZurfFTSig = false;}
      if(HOaySmLbLF == true){HOaySmLbLF = false;}
      if(mfRbVMPfuC == true){mfRbVMPfuC = false;}
      if(lwpuVptrhb == true){lwpuVptrhb = false;}
      if(wFsgDNVJdG == true){wFsgDNVJdG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBFAFBUQHC
{ 
  void IhyqquMxuj()
  { 
      bool jkZbMrPbBR = false;
      bool YhiPlzymUV = false;
      bool PZXchDwDdK = false;
      bool KhlGpQgpyh = false;
      bool VUUjqyckRx = false;
      bool nrmpTKNwsI = false;
      bool wLyqHpwcYV = false;
      bool RIomAtEnlj = false;
      bool aKlgWSuwme = false;
      bool DkwokKWdbA = false;
      bool BAMwefCApY = false;
      bool FYJJglYQTo = false;
      bool uzpsRgLzBo = false;
      bool XZLkhZypBq = false;
      bool PtGNYdamHz = false;
      bool kFJmFCKSdy = false;
      bool TDzABfNXbH = false;
      bool niPcYAsbTm = false;
      bool GYqBERPXff = false;
      bool PeLDWLuGLs = false;
      string UxDfFuPFoJ;
      string solxyTThry;
      string EaFlRQypHc;
      string dOZiCqLEHa;
      string DWsgDaDDDL;
      string tABHytqQOo;
      string wZxMfeODtG;
      string IOaQthgXhq;
      string NtlwhdMSjI;
      string AtpRdcYgBY;
      string LzJwDeYjNQ;
      string MSiXbBmBdC;
      string RwSkGNYImQ;
      string IAWIeNkpsC;
      string EbFTugLRpc;
      string pXDzHPgYoo;
      string GQxwHMwZrO;
      string QxHaxoqyoZ;
      string CGRKakxWBP;
      string fMBEwmeIMi;
      if(UxDfFuPFoJ == LzJwDeYjNQ){jkZbMrPbBR = true;}
      else if(LzJwDeYjNQ == UxDfFuPFoJ){BAMwefCApY = true;}
      if(solxyTThry == MSiXbBmBdC){YhiPlzymUV = true;}
      else if(MSiXbBmBdC == solxyTThry){FYJJglYQTo = true;}
      if(EaFlRQypHc == RwSkGNYImQ){PZXchDwDdK = true;}
      else if(RwSkGNYImQ == EaFlRQypHc){uzpsRgLzBo = true;}
      if(dOZiCqLEHa == IAWIeNkpsC){KhlGpQgpyh = true;}
      else if(IAWIeNkpsC == dOZiCqLEHa){XZLkhZypBq = true;}
      if(DWsgDaDDDL == EbFTugLRpc){VUUjqyckRx = true;}
      else if(EbFTugLRpc == DWsgDaDDDL){PtGNYdamHz = true;}
      if(tABHytqQOo == pXDzHPgYoo){nrmpTKNwsI = true;}
      else if(pXDzHPgYoo == tABHytqQOo){kFJmFCKSdy = true;}
      if(wZxMfeODtG == GQxwHMwZrO){wLyqHpwcYV = true;}
      else if(GQxwHMwZrO == wZxMfeODtG){TDzABfNXbH = true;}
      if(IOaQthgXhq == QxHaxoqyoZ){RIomAtEnlj = true;}
      if(NtlwhdMSjI == CGRKakxWBP){aKlgWSuwme = true;}
      if(AtpRdcYgBY == fMBEwmeIMi){DkwokKWdbA = true;}
      while(QxHaxoqyoZ == IOaQthgXhq){niPcYAsbTm = true;}
      while(CGRKakxWBP == CGRKakxWBP){GYqBERPXff = true;}
      while(fMBEwmeIMi == fMBEwmeIMi){PeLDWLuGLs = true;}
      if(jkZbMrPbBR == true){jkZbMrPbBR = false;}
      if(YhiPlzymUV == true){YhiPlzymUV = false;}
      if(PZXchDwDdK == true){PZXchDwDdK = false;}
      if(KhlGpQgpyh == true){KhlGpQgpyh = false;}
      if(VUUjqyckRx == true){VUUjqyckRx = false;}
      if(nrmpTKNwsI == true){nrmpTKNwsI = false;}
      if(wLyqHpwcYV == true){wLyqHpwcYV = false;}
      if(RIomAtEnlj == true){RIomAtEnlj = false;}
      if(aKlgWSuwme == true){aKlgWSuwme = false;}
      if(DkwokKWdbA == true){DkwokKWdbA = false;}
      if(BAMwefCApY == true){BAMwefCApY = false;}
      if(FYJJglYQTo == true){FYJJglYQTo = false;}
      if(uzpsRgLzBo == true){uzpsRgLzBo = false;}
      if(XZLkhZypBq == true){XZLkhZypBq = false;}
      if(PtGNYdamHz == true){PtGNYdamHz = false;}
      if(kFJmFCKSdy == true){kFJmFCKSdy = false;}
      if(TDzABfNXbH == true){TDzABfNXbH = false;}
      if(niPcYAsbTm == true){niPcYAsbTm = false;}
      if(GYqBERPXff == true){GYqBERPXff = false;}
      if(PeLDWLuGLs == true){PeLDWLuGLs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFSEDPODFW
{ 
  void XFIPOKKWLO()
  { 
      bool XbRFpSsOCh = false;
      bool lhXOYiCewy = false;
      bool zoEwSlkhay = false;
      bool ULgFHpNcKW = false;
      bool sqEABJeHdZ = false;
      bool nukhMiWUmD = false;
      bool hKmENZBRHi = false;
      bool VYUZEHjEuJ = false;
      bool HcEBKZaysY = false;
      bool SrpGnhDAmb = false;
      bool INAtDPaKcE = false;
      bool ySZcwEGltm = false;
      bool zCXiPdiNlW = false;
      bool DiQSBsbJxt = false;
      bool yPUnZARMKi = false;
      bool bRGzcFoReZ = false;
      bool gMYGAPBGbC = false;
      bool cwnzoigjIP = false;
      bool LVCCtlcRpu = false;
      bool EKeWNlpOmK = false;
      string TwoSpqzhfk;
      string ofwFiJNcBx;
      string ewrtyitRmE;
      string IVrxxTLZSI;
      string gEjkAiXfIV;
      string juDTcWDuTG;
      string wgubcTnyIP;
      string ynKrPaMHtP;
      string KOJQTMRXTa;
      string PQGLMzIHIf;
      string uYWsXwkLDC;
      string JwBEugXdIQ;
      string CPdhzggzfQ;
      string RFzNTkrQsX;
      string bGURQTPCPe;
      string aezqdftosp;
      string OkelkEwnjJ;
      string oHkjoutMRe;
      string ReiAomFHim;
      string qCWCJpahfL;
      if(TwoSpqzhfk == uYWsXwkLDC){XbRFpSsOCh = true;}
      else if(uYWsXwkLDC == TwoSpqzhfk){INAtDPaKcE = true;}
      if(ofwFiJNcBx == JwBEugXdIQ){lhXOYiCewy = true;}
      else if(JwBEugXdIQ == ofwFiJNcBx){ySZcwEGltm = true;}
      if(ewrtyitRmE == CPdhzggzfQ){zoEwSlkhay = true;}
      else if(CPdhzggzfQ == ewrtyitRmE){zCXiPdiNlW = true;}
      if(IVrxxTLZSI == RFzNTkrQsX){ULgFHpNcKW = true;}
      else if(RFzNTkrQsX == IVrxxTLZSI){DiQSBsbJxt = true;}
      if(gEjkAiXfIV == bGURQTPCPe){sqEABJeHdZ = true;}
      else if(bGURQTPCPe == gEjkAiXfIV){yPUnZARMKi = true;}
      if(juDTcWDuTG == aezqdftosp){nukhMiWUmD = true;}
      else if(aezqdftosp == juDTcWDuTG){bRGzcFoReZ = true;}
      if(wgubcTnyIP == OkelkEwnjJ){hKmENZBRHi = true;}
      else if(OkelkEwnjJ == wgubcTnyIP){gMYGAPBGbC = true;}
      if(ynKrPaMHtP == oHkjoutMRe){VYUZEHjEuJ = true;}
      if(KOJQTMRXTa == ReiAomFHim){HcEBKZaysY = true;}
      if(PQGLMzIHIf == qCWCJpahfL){SrpGnhDAmb = true;}
      while(oHkjoutMRe == ynKrPaMHtP){cwnzoigjIP = true;}
      while(ReiAomFHim == ReiAomFHim){LVCCtlcRpu = true;}
      while(qCWCJpahfL == qCWCJpahfL){EKeWNlpOmK = true;}
      if(XbRFpSsOCh == true){XbRFpSsOCh = false;}
      if(lhXOYiCewy == true){lhXOYiCewy = false;}
      if(zoEwSlkhay == true){zoEwSlkhay = false;}
      if(ULgFHpNcKW == true){ULgFHpNcKW = false;}
      if(sqEABJeHdZ == true){sqEABJeHdZ = false;}
      if(nukhMiWUmD == true){nukhMiWUmD = false;}
      if(hKmENZBRHi == true){hKmENZBRHi = false;}
      if(VYUZEHjEuJ == true){VYUZEHjEuJ = false;}
      if(HcEBKZaysY == true){HcEBKZaysY = false;}
      if(SrpGnhDAmb == true){SrpGnhDAmb = false;}
      if(INAtDPaKcE == true){INAtDPaKcE = false;}
      if(ySZcwEGltm == true){ySZcwEGltm = false;}
      if(zCXiPdiNlW == true){zCXiPdiNlW = false;}
      if(DiQSBsbJxt == true){DiQSBsbJxt = false;}
      if(yPUnZARMKi == true){yPUnZARMKi = false;}
      if(bRGzcFoReZ == true){bRGzcFoReZ = false;}
      if(gMYGAPBGbC == true){gMYGAPBGbC = false;}
      if(cwnzoigjIP == true){cwnzoigjIP = false;}
      if(LVCCtlcRpu == true){LVCCtlcRpu = false;}
      if(EKeWNlpOmK == true){EKeWNlpOmK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHOKKQVWRN
{ 
  void yhphlOJlin()
  { 
      bool wjucjYipNC = false;
      bool rmAUKjomMx = false;
      bool DHePfAkJrR = false;
      bool pCyuhEtpZp = false;
      bool xTVUGncZrm = false;
      bool jiWdZoEfwi = false;
      bool mZxwMpoFlF = false;
      bool pzMVAjlKJq = false;
      bool XKQEhGfTUs = false;
      bool AOsqCWVYIP = false;
      bool zWmmxjVAdo = false;
      bool CtVELcJsOF = false;
      bool JVjsFbFVTd = false;
      bool OMCsrAXcHx = false;
      bool jepfpFroeZ = false;
      bool MbKDFdmshV = false;
      bool eAfzaorcLK = false;
      bool EflQUdeEDz = false;
      bool iPptQlCymO = false;
      bool NdulSjzpFA = false;
      string CDjfGkuAnI;
      string OrCMAEDGnE;
      string qpIKhXNNHB;
      string rmrIeOBARS;
      string KDGrZbnWCd;
      string czsnuLuZyh;
      string XhrmPbAthl;
      string DCnUtmiPkF;
      string jpKdXrsENS;
      string SbCjubKTbx;
      string atnQaZLXsH;
      string beorygXOOX;
      string hwfOSbzDZR;
      string cOnmdoCsCy;
      string gUKGpnlJkO;
      string DwFEPeNYyz;
      string ZHyadMqCOI;
      string deMPpMlZYd;
      string ooSKOgJiWz;
      string bctDXYWibd;
      if(CDjfGkuAnI == atnQaZLXsH){wjucjYipNC = true;}
      else if(atnQaZLXsH == CDjfGkuAnI){zWmmxjVAdo = true;}
      if(OrCMAEDGnE == beorygXOOX){rmAUKjomMx = true;}
      else if(beorygXOOX == OrCMAEDGnE){CtVELcJsOF = true;}
      if(qpIKhXNNHB == hwfOSbzDZR){DHePfAkJrR = true;}
      else if(hwfOSbzDZR == qpIKhXNNHB){JVjsFbFVTd = true;}
      if(rmrIeOBARS == cOnmdoCsCy){pCyuhEtpZp = true;}
      else if(cOnmdoCsCy == rmrIeOBARS){OMCsrAXcHx = true;}
      if(KDGrZbnWCd == gUKGpnlJkO){xTVUGncZrm = true;}
      else if(gUKGpnlJkO == KDGrZbnWCd){jepfpFroeZ = true;}
      if(czsnuLuZyh == DwFEPeNYyz){jiWdZoEfwi = true;}
      else if(DwFEPeNYyz == czsnuLuZyh){MbKDFdmshV = true;}
      if(XhrmPbAthl == ZHyadMqCOI){mZxwMpoFlF = true;}
      else if(ZHyadMqCOI == XhrmPbAthl){eAfzaorcLK = true;}
      if(DCnUtmiPkF == deMPpMlZYd){pzMVAjlKJq = true;}
      if(jpKdXrsENS == ooSKOgJiWz){XKQEhGfTUs = true;}
      if(SbCjubKTbx == bctDXYWibd){AOsqCWVYIP = true;}
      while(deMPpMlZYd == DCnUtmiPkF){EflQUdeEDz = true;}
      while(ooSKOgJiWz == ooSKOgJiWz){iPptQlCymO = true;}
      while(bctDXYWibd == bctDXYWibd){NdulSjzpFA = true;}
      if(wjucjYipNC == true){wjucjYipNC = false;}
      if(rmAUKjomMx == true){rmAUKjomMx = false;}
      if(DHePfAkJrR == true){DHePfAkJrR = false;}
      if(pCyuhEtpZp == true){pCyuhEtpZp = false;}
      if(xTVUGncZrm == true){xTVUGncZrm = false;}
      if(jiWdZoEfwi == true){jiWdZoEfwi = false;}
      if(mZxwMpoFlF == true){mZxwMpoFlF = false;}
      if(pzMVAjlKJq == true){pzMVAjlKJq = false;}
      if(XKQEhGfTUs == true){XKQEhGfTUs = false;}
      if(AOsqCWVYIP == true){AOsqCWVYIP = false;}
      if(zWmmxjVAdo == true){zWmmxjVAdo = false;}
      if(CtVELcJsOF == true){CtVELcJsOF = false;}
      if(JVjsFbFVTd == true){JVjsFbFVTd = false;}
      if(OMCsrAXcHx == true){OMCsrAXcHx = false;}
      if(jepfpFroeZ == true){jepfpFroeZ = false;}
      if(MbKDFdmshV == true){MbKDFdmshV = false;}
      if(eAfzaorcLK == true){eAfzaorcLK = false;}
      if(EflQUdeEDz == true){EflQUdeEDz = false;}
      if(iPptQlCymO == true){iPptQlCymO = false;}
      if(NdulSjzpFA == true){NdulSjzpFA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFKKEYJUXX
{ 
  void BPcSVezNDm()
  { 
      bool YQPZasDaBn = false;
      bool BlgcqlgrFu = false;
      bool GPSAaSWskP = false;
      bool PjJpUJSDuZ = false;
      bool uRSkHjMfum = false;
      bool KcYHVJxOzI = false;
      bool WKplXQcpHg = false;
      bool Tcwezowgrp = false;
      bool GpyxElKCTL = false;
      bool LDEmDkagMq = false;
      bool HVYNTggtHg = false;
      bool MQWJBfMsgk = false;
      bool FaVwUPYJbO = false;
      bool NPTAhkRjcW = false;
      bool FQtlyugukX = false;
      bool XhzakgzbrE = false;
      bool IWSsTxwVaQ = false;
      bool NbPJfofjyZ = false;
      bool idXEpfQrPA = false;
      bool kprYOhyASA = false;
      string rzDUQYYjsA;
      string NNoDzZMgmp;
      string KrqReTgEtP;
      string XjXFEbmxnj;
      string IIVuXXqsxn;
      string qHaBezHkpw;
      string rUpdbdojzW;
      string lOsChBWwsH;
      string cmGGXQIWaE;
      string TBHqrnSrTt;
      string hHtZCcNYSd;
      string cLrhSENiFK;
      string USItCjHCJt;
      string idczYVsgDu;
      string DjDxaIJYXm;
      string ZilIYPyzWR;
      string ULOYtyisJx;
      string LgeKHkOLSt;
      string ahdWTzrTZJ;
      string WsJlZrUeCc;
      if(rzDUQYYjsA == hHtZCcNYSd){YQPZasDaBn = true;}
      else if(hHtZCcNYSd == rzDUQYYjsA){HVYNTggtHg = true;}
      if(NNoDzZMgmp == cLrhSENiFK){BlgcqlgrFu = true;}
      else if(cLrhSENiFK == NNoDzZMgmp){MQWJBfMsgk = true;}
      if(KrqReTgEtP == USItCjHCJt){GPSAaSWskP = true;}
      else if(USItCjHCJt == KrqReTgEtP){FaVwUPYJbO = true;}
      if(XjXFEbmxnj == idczYVsgDu){PjJpUJSDuZ = true;}
      else if(idczYVsgDu == XjXFEbmxnj){NPTAhkRjcW = true;}
      if(IIVuXXqsxn == DjDxaIJYXm){uRSkHjMfum = true;}
      else if(DjDxaIJYXm == IIVuXXqsxn){FQtlyugukX = true;}
      if(qHaBezHkpw == ZilIYPyzWR){KcYHVJxOzI = true;}
      else if(ZilIYPyzWR == qHaBezHkpw){XhzakgzbrE = true;}
      if(rUpdbdojzW == ULOYtyisJx){WKplXQcpHg = true;}
      else if(ULOYtyisJx == rUpdbdojzW){IWSsTxwVaQ = true;}
      if(lOsChBWwsH == LgeKHkOLSt){Tcwezowgrp = true;}
      if(cmGGXQIWaE == ahdWTzrTZJ){GpyxElKCTL = true;}
      if(TBHqrnSrTt == WsJlZrUeCc){LDEmDkagMq = true;}
      while(LgeKHkOLSt == lOsChBWwsH){NbPJfofjyZ = true;}
      while(ahdWTzrTZJ == ahdWTzrTZJ){idXEpfQrPA = true;}
      while(WsJlZrUeCc == WsJlZrUeCc){kprYOhyASA = true;}
      if(YQPZasDaBn == true){YQPZasDaBn = false;}
      if(BlgcqlgrFu == true){BlgcqlgrFu = false;}
      if(GPSAaSWskP == true){GPSAaSWskP = false;}
      if(PjJpUJSDuZ == true){PjJpUJSDuZ = false;}
      if(uRSkHjMfum == true){uRSkHjMfum = false;}
      if(KcYHVJxOzI == true){KcYHVJxOzI = false;}
      if(WKplXQcpHg == true){WKplXQcpHg = false;}
      if(Tcwezowgrp == true){Tcwezowgrp = false;}
      if(GpyxElKCTL == true){GpyxElKCTL = false;}
      if(LDEmDkagMq == true){LDEmDkagMq = false;}
      if(HVYNTggtHg == true){HVYNTggtHg = false;}
      if(MQWJBfMsgk == true){MQWJBfMsgk = false;}
      if(FaVwUPYJbO == true){FaVwUPYJbO = false;}
      if(NPTAhkRjcW == true){NPTAhkRjcW = false;}
      if(FQtlyugukX == true){FQtlyugukX = false;}
      if(XhzakgzbrE == true){XhzakgzbrE = false;}
      if(IWSsTxwVaQ == true){IWSsTxwVaQ = false;}
      if(NbPJfofjyZ == true){NbPJfofjyZ = false;}
      if(idXEpfQrPA == true){idXEpfQrPA = false;}
      if(kprYOhyASA == true){kprYOhyASA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHYDNKVCBK
{ 
  void tEpcWIiZMT()
  { 
      bool GeGjBCKJoT = false;
      bool WuUZeFVhzb = false;
      bool ScrnrMQLPe = false;
      bool wBuztxZAcP = false;
      bool EYjYyBPONS = false;
      bool pZaRKclSqn = false;
      bool lztJWVAUeh = false;
      bool eUFjXsrTop = false;
      bool wBxwoWZdnR = false;
      bool KHJndFeaBc = false;
      bool BtjfnVUqsQ = false;
      bool jScAqjByUA = false;
      bool uVfNWXKQFS = false;
      bool ORRMnBRRIT = false;
      bool CijWgqeIwt = false;
      bool EgFAgfNWIQ = false;
      bool KDkaCSAPLo = false;
      bool RipByMkJfe = false;
      bool sCTLNhLReI = false;
      bool nuJqIyxJUN = false;
      string chojGyjOEB;
      string exKByezbJI;
      string dPdgSmZNHN;
      string JBncbWXKSC;
      string BclgXdrhMG;
      string VZtAWMEIRT;
      string XWHprdJgYb;
      string GnJGGAcwIn;
      string tqABqiGmGP;
      string ROryeeVwot;
      string ULIkzgQntV;
      string iIzcYfVGyI;
      string WVZJJquKbb;
      string egGOTiiPBK;
      string RSskfIPPZy;
      string IPyfWykyaH;
      string kGLSqCCjIp;
      string xFEnqDbodB;
      string bfkdSOiZrU;
      string xjosYLHasd;
      if(chojGyjOEB == ULIkzgQntV){GeGjBCKJoT = true;}
      else if(ULIkzgQntV == chojGyjOEB){BtjfnVUqsQ = true;}
      if(exKByezbJI == iIzcYfVGyI){WuUZeFVhzb = true;}
      else if(iIzcYfVGyI == exKByezbJI){jScAqjByUA = true;}
      if(dPdgSmZNHN == WVZJJquKbb){ScrnrMQLPe = true;}
      else if(WVZJJquKbb == dPdgSmZNHN){uVfNWXKQFS = true;}
      if(JBncbWXKSC == egGOTiiPBK){wBuztxZAcP = true;}
      else if(egGOTiiPBK == JBncbWXKSC){ORRMnBRRIT = true;}
      if(BclgXdrhMG == RSskfIPPZy){EYjYyBPONS = true;}
      else if(RSskfIPPZy == BclgXdrhMG){CijWgqeIwt = true;}
      if(VZtAWMEIRT == IPyfWykyaH){pZaRKclSqn = true;}
      else if(IPyfWykyaH == VZtAWMEIRT){EgFAgfNWIQ = true;}
      if(XWHprdJgYb == kGLSqCCjIp){lztJWVAUeh = true;}
      else if(kGLSqCCjIp == XWHprdJgYb){KDkaCSAPLo = true;}
      if(GnJGGAcwIn == xFEnqDbodB){eUFjXsrTop = true;}
      if(tqABqiGmGP == bfkdSOiZrU){wBxwoWZdnR = true;}
      if(ROryeeVwot == xjosYLHasd){KHJndFeaBc = true;}
      while(xFEnqDbodB == GnJGGAcwIn){RipByMkJfe = true;}
      while(bfkdSOiZrU == bfkdSOiZrU){sCTLNhLReI = true;}
      while(xjosYLHasd == xjosYLHasd){nuJqIyxJUN = true;}
      if(GeGjBCKJoT == true){GeGjBCKJoT = false;}
      if(WuUZeFVhzb == true){WuUZeFVhzb = false;}
      if(ScrnrMQLPe == true){ScrnrMQLPe = false;}
      if(wBuztxZAcP == true){wBuztxZAcP = false;}
      if(EYjYyBPONS == true){EYjYyBPONS = false;}
      if(pZaRKclSqn == true){pZaRKclSqn = false;}
      if(lztJWVAUeh == true){lztJWVAUeh = false;}
      if(eUFjXsrTop == true){eUFjXsrTop = false;}
      if(wBxwoWZdnR == true){wBxwoWZdnR = false;}
      if(KHJndFeaBc == true){KHJndFeaBc = false;}
      if(BtjfnVUqsQ == true){BtjfnVUqsQ = false;}
      if(jScAqjByUA == true){jScAqjByUA = false;}
      if(uVfNWXKQFS == true){uVfNWXKQFS = false;}
      if(ORRMnBRRIT == true){ORRMnBRRIT = false;}
      if(CijWgqeIwt == true){CijWgqeIwt = false;}
      if(EgFAgfNWIQ == true){EgFAgfNWIQ = false;}
      if(KDkaCSAPLo == true){KDkaCSAPLo = false;}
      if(RipByMkJfe == true){RipByMkJfe = false;}
      if(sCTLNhLReI == true){sCTLNhLReI = false;}
      if(nuJqIyxJUN == true){nuJqIyxJUN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDVDSUVBXH
{ 
  void oVkmhoulax()
  { 
      bool YzoaqFsfuH = false;
      bool WwyyzCpkLX = false;
      bool LNkZOZqlQc = false;
      bool ZoySETOJtC = false;
      bool UcZXGGkLNt = false;
      bool wMeeDLNOLR = false;
      bool NGPRhhyfte = false;
      bool ngpJDinMTI = false;
      bool oeYWfNJSPr = false;
      bool FzxcnNNHpX = false;
      bool HFRhFPVVaT = false;
      bool WBtDbhhskT = false;
      bool XePBZnjNUp = false;
      bool VfWuAiMpQQ = false;
      bool rnquVEEsAG = false;
      bool fTWVAboQIR = false;
      bool fIAkyqdyCs = false;
      bool UqbTbjmTfU = false;
      bool ipMOJBIAuX = false;
      bool swhykjmGwd = false;
      string pnkWEhHZMx;
      string YWRXOiQBip;
      string GBEZKypUOm;
      string DDkwwGFpPT;
      string gflirhJZUg;
      string enZqQnjKMG;
      string qlLZsUlVaH;
      string dakPIZPUhb;
      string nQzhHPdteI;
      string WtcJbtULoW;
      string unzNCECJhp;
      string YOcjRamcRd;
      string qrpRkjxbmO;
      string EDfLgAQleD;
      string NTLojHQsrB;
      string GqtLeDxgbS;
      string GZWTkUhRDQ;
      string JByNQWgBhd;
      string TEjlHNJUfc;
      string CjJMxmxqDO;
      if(pnkWEhHZMx == unzNCECJhp){YzoaqFsfuH = true;}
      else if(unzNCECJhp == pnkWEhHZMx){HFRhFPVVaT = true;}
      if(YWRXOiQBip == YOcjRamcRd){WwyyzCpkLX = true;}
      else if(YOcjRamcRd == YWRXOiQBip){WBtDbhhskT = true;}
      if(GBEZKypUOm == qrpRkjxbmO){LNkZOZqlQc = true;}
      else if(qrpRkjxbmO == GBEZKypUOm){XePBZnjNUp = true;}
      if(DDkwwGFpPT == EDfLgAQleD){ZoySETOJtC = true;}
      else if(EDfLgAQleD == DDkwwGFpPT){VfWuAiMpQQ = true;}
      if(gflirhJZUg == NTLojHQsrB){UcZXGGkLNt = true;}
      else if(NTLojHQsrB == gflirhJZUg){rnquVEEsAG = true;}
      if(enZqQnjKMG == GqtLeDxgbS){wMeeDLNOLR = true;}
      else if(GqtLeDxgbS == enZqQnjKMG){fTWVAboQIR = true;}
      if(qlLZsUlVaH == GZWTkUhRDQ){NGPRhhyfte = true;}
      else if(GZWTkUhRDQ == qlLZsUlVaH){fIAkyqdyCs = true;}
      if(dakPIZPUhb == JByNQWgBhd){ngpJDinMTI = true;}
      if(nQzhHPdteI == TEjlHNJUfc){oeYWfNJSPr = true;}
      if(WtcJbtULoW == CjJMxmxqDO){FzxcnNNHpX = true;}
      while(JByNQWgBhd == dakPIZPUhb){UqbTbjmTfU = true;}
      while(TEjlHNJUfc == TEjlHNJUfc){ipMOJBIAuX = true;}
      while(CjJMxmxqDO == CjJMxmxqDO){swhykjmGwd = true;}
      if(YzoaqFsfuH == true){YzoaqFsfuH = false;}
      if(WwyyzCpkLX == true){WwyyzCpkLX = false;}
      if(LNkZOZqlQc == true){LNkZOZqlQc = false;}
      if(ZoySETOJtC == true){ZoySETOJtC = false;}
      if(UcZXGGkLNt == true){UcZXGGkLNt = false;}
      if(wMeeDLNOLR == true){wMeeDLNOLR = false;}
      if(NGPRhhyfte == true){NGPRhhyfte = false;}
      if(ngpJDinMTI == true){ngpJDinMTI = false;}
      if(oeYWfNJSPr == true){oeYWfNJSPr = false;}
      if(FzxcnNNHpX == true){FzxcnNNHpX = false;}
      if(HFRhFPVVaT == true){HFRhFPVVaT = false;}
      if(WBtDbhhskT == true){WBtDbhhskT = false;}
      if(XePBZnjNUp == true){XePBZnjNUp = false;}
      if(VfWuAiMpQQ == true){VfWuAiMpQQ = false;}
      if(rnquVEEsAG == true){rnquVEEsAG = false;}
      if(fTWVAboQIR == true){fTWVAboQIR = false;}
      if(fIAkyqdyCs == true){fIAkyqdyCs = false;}
      if(UqbTbjmTfU == true){UqbTbjmTfU = false;}
      if(ipMOJBIAuX == true){ipMOJBIAuX = false;}
      if(swhykjmGwd == true){swhykjmGwd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFUITBDFHX
{ 
  void fktcOtmMkK()
  { 
      bool gWusarDOwX = false;
      bool uhNCOpDVax = false;
      bool ttAJHgGJky = false;
      bool MijJtrrbDT = false;
      bool oDNzdzAAAq = false;
      bool hbNJslWkls = false;
      bool kscxLMxDIV = false;
      bool xbSHIqgBfH = false;
      bool fGIsPkUZQI = false;
      bool VHpJhuZQnQ = false;
      bool BxretGIGBC = false;
      bool FVFdNekjgZ = false;
      bool rWlAAplIYN = false;
      bool QQMOGiOdzJ = false;
      bool bNYNCABLwD = false;
      bool KpiNYdKqdD = false;
      bool UAhnkoIqXd = false;
      bool QGjXydyYxA = false;
      bool nZMUCagzob = false;
      bool YWAwnbekbN = false;
      string knVNBMgDTc;
      string rcgyqfZehW;
      string KLauUiIODf;
      string wltiluyzws;
      string MtAIyEMXnV;
      string WJnNaYNZrR;
      string ESzmgGixMu;
      string hZhnJPLRxP;
      string VjZgIlxgIN;
      string hXHdotuMaq;
      string VOKrnwbzDK;
      string MuccwTrSet;
      string IBozNJSDzP;
      string UzpFsHYhsL;
      string KydxAltdhU;
      string CbgfhTZLed;
      string dXAnpMEXio;
      string tJYSjKXqyb;
      string PnUdMrRJWZ;
      string gNDPhlxoHn;
      if(knVNBMgDTc == VOKrnwbzDK){gWusarDOwX = true;}
      else if(VOKrnwbzDK == knVNBMgDTc){BxretGIGBC = true;}
      if(rcgyqfZehW == MuccwTrSet){uhNCOpDVax = true;}
      else if(MuccwTrSet == rcgyqfZehW){FVFdNekjgZ = true;}
      if(KLauUiIODf == IBozNJSDzP){ttAJHgGJky = true;}
      else if(IBozNJSDzP == KLauUiIODf){rWlAAplIYN = true;}
      if(wltiluyzws == UzpFsHYhsL){MijJtrrbDT = true;}
      else if(UzpFsHYhsL == wltiluyzws){QQMOGiOdzJ = true;}
      if(MtAIyEMXnV == KydxAltdhU){oDNzdzAAAq = true;}
      else if(KydxAltdhU == MtAIyEMXnV){bNYNCABLwD = true;}
      if(WJnNaYNZrR == CbgfhTZLed){hbNJslWkls = true;}
      else if(CbgfhTZLed == WJnNaYNZrR){KpiNYdKqdD = true;}
      if(ESzmgGixMu == dXAnpMEXio){kscxLMxDIV = true;}
      else if(dXAnpMEXio == ESzmgGixMu){UAhnkoIqXd = true;}
      if(hZhnJPLRxP == tJYSjKXqyb){xbSHIqgBfH = true;}
      if(VjZgIlxgIN == PnUdMrRJWZ){fGIsPkUZQI = true;}
      if(hXHdotuMaq == gNDPhlxoHn){VHpJhuZQnQ = true;}
      while(tJYSjKXqyb == hZhnJPLRxP){QGjXydyYxA = true;}
      while(PnUdMrRJWZ == PnUdMrRJWZ){nZMUCagzob = true;}
      while(gNDPhlxoHn == gNDPhlxoHn){YWAwnbekbN = true;}
      if(gWusarDOwX == true){gWusarDOwX = false;}
      if(uhNCOpDVax == true){uhNCOpDVax = false;}
      if(ttAJHgGJky == true){ttAJHgGJky = false;}
      if(MijJtrrbDT == true){MijJtrrbDT = false;}
      if(oDNzdzAAAq == true){oDNzdzAAAq = false;}
      if(hbNJslWkls == true){hbNJslWkls = false;}
      if(kscxLMxDIV == true){kscxLMxDIV = false;}
      if(xbSHIqgBfH == true){xbSHIqgBfH = false;}
      if(fGIsPkUZQI == true){fGIsPkUZQI = false;}
      if(VHpJhuZQnQ == true){VHpJhuZQnQ = false;}
      if(BxretGIGBC == true){BxretGIGBC = false;}
      if(FVFdNekjgZ == true){FVFdNekjgZ = false;}
      if(rWlAAplIYN == true){rWlAAplIYN = false;}
      if(QQMOGiOdzJ == true){QQMOGiOdzJ = false;}
      if(bNYNCABLwD == true){bNYNCABLwD = false;}
      if(KpiNYdKqdD == true){KpiNYdKqdD = false;}
      if(UAhnkoIqXd == true){UAhnkoIqXd = false;}
      if(QGjXydyYxA == true){QGjXydyYxA = false;}
      if(nZMUCagzob == true){nZMUCagzob = false;}
      if(YWAwnbekbN == true){YWAwnbekbN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWNPPPABWS
{ 
  void KPCYWtfGpc()
  { 
      bool rwWtNRlxXT = false;
      bool VflpuAmdIT = false;
      bool pqbxWFMsyD = false;
      bool CTGoCNUwLe = false;
      bool UgmsmYFPfp = false;
      bool SgUntBUYXH = false;
      bool EryURBZwnh = false;
      bool fpRczIDhKy = false;
      bool AwMIjVyRuA = false;
      bool ruYDabiRbk = false;
      bool yIbyJcOrok = false;
      bool ylNYHHepku = false;
      bool DIBmojQOCX = false;
      bool ZkFZzqUOyH = false;
      bool HFcJCFhzuS = false;
      bool wrgghpHnIY = false;
      bool LzpRKMfnZQ = false;
      bool lQqdnxfqkj = false;
      bool CRTjahEYrJ = false;
      bool igFYuHPLyo = false;
      string OmRkeGNtGD;
      string yrFXtczgyI;
      string VDUfcIKgGm;
      string gaoiBKITUF;
      string dycydBOOLW;
      string qEcSMLSlIV;
      string wgmSWXCVVi;
      string TeMreXZVBa;
      string swUjubxWWp;
      string rWKyJxKJbG;
      string zsrcCMrkmn;
      string kwjhbALDXt;
      string ZfyfqwTNhh;
      string NQstbADrhi;
      string jMiiFulcWJ;
      string kHlhgSuMlF;
      string rdCFZUCoGb;
      string wTVoJMxOZu;
      string JqqYxGdLNI;
      string EqGbpGKdIk;
      if(OmRkeGNtGD == zsrcCMrkmn){rwWtNRlxXT = true;}
      else if(zsrcCMrkmn == OmRkeGNtGD){yIbyJcOrok = true;}
      if(yrFXtczgyI == kwjhbALDXt){VflpuAmdIT = true;}
      else if(kwjhbALDXt == yrFXtczgyI){ylNYHHepku = true;}
      if(VDUfcIKgGm == ZfyfqwTNhh){pqbxWFMsyD = true;}
      else if(ZfyfqwTNhh == VDUfcIKgGm){DIBmojQOCX = true;}
      if(gaoiBKITUF == NQstbADrhi){CTGoCNUwLe = true;}
      else if(NQstbADrhi == gaoiBKITUF){ZkFZzqUOyH = true;}
      if(dycydBOOLW == jMiiFulcWJ){UgmsmYFPfp = true;}
      else if(jMiiFulcWJ == dycydBOOLW){HFcJCFhzuS = true;}
      if(qEcSMLSlIV == kHlhgSuMlF){SgUntBUYXH = true;}
      else if(kHlhgSuMlF == qEcSMLSlIV){wrgghpHnIY = true;}
      if(wgmSWXCVVi == rdCFZUCoGb){EryURBZwnh = true;}
      else if(rdCFZUCoGb == wgmSWXCVVi){LzpRKMfnZQ = true;}
      if(TeMreXZVBa == wTVoJMxOZu){fpRczIDhKy = true;}
      if(swUjubxWWp == JqqYxGdLNI){AwMIjVyRuA = true;}
      if(rWKyJxKJbG == EqGbpGKdIk){ruYDabiRbk = true;}
      while(wTVoJMxOZu == TeMreXZVBa){lQqdnxfqkj = true;}
      while(JqqYxGdLNI == JqqYxGdLNI){CRTjahEYrJ = true;}
      while(EqGbpGKdIk == EqGbpGKdIk){igFYuHPLyo = true;}
      if(rwWtNRlxXT == true){rwWtNRlxXT = false;}
      if(VflpuAmdIT == true){VflpuAmdIT = false;}
      if(pqbxWFMsyD == true){pqbxWFMsyD = false;}
      if(CTGoCNUwLe == true){CTGoCNUwLe = false;}
      if(UgmsmYFPfp == true){UgmsmYFPfp = false;}
      if(SgUntBUYXH == true){SgUntBUYXH = false;}
      if(EryURBZwnh == true){EryURBZwnh = false;}
      if(fpRczIDhKy == true){fpRczIDhKy = false;}
      if(AwMIjVyRuA == true){AwMIjVyRuA = false;}
      if(ruYDabiRbk == true){ruYDabiRbk = false;}
      if(yIbyJcOrok == true){yIbyJcOrok = false;}
      if(ylNYHHepku == true){ylNYHHepku = false;}
      if(DIBmojQOCX == true){DIBmojQOCX = false;}
      if(ZkFZzqUOyH == true){ZkFZzqUOyH = false;}
      if(HFcJCFhzuS == true){HFcJCFhzuS = false;}
      if(wrgghpHnIY == true){wrgghpHnIY = false;}
      if(LzpRKMfnZQ == true){LzpRKMfnZQ = false;}
      if(lQqdnxfqkj == true){lQqdnxfqkj = false;}
      if(CRTjahEYrJ == true){CRTjahEYrJ = false;}
      if(igFYuHPLyo == true){igFYuHPLyo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JASABVPKSW
{ 
  void TaxUNkcyCT()
  { 
      bool KhSIVKzpse = false;
      bool DbVViMWghu = false;
      bool odILmwtKHe = false;
      bool HtMPGzkDAL = false;
      bool DrhBcJFBPb = false;
      bool gaEfnfYGUZ = false;
      bool QoiOWIPGPj = false;
      bool bSfWqxwHid = false;
      bool pruexgpfbZ = false;
      bool ZeiatOISeT = false;
      bool tzlfANtgnq = false;
      bool jRWpiYsEQp = false;
      bool RidoJxjEbc = false;
      bool nccPjqFPej = false;
      bool lIrkpIHrrV = false;
      bool UECnBKUwVC = false;
      bool coEKDGnHGq = false;
      bool SdZfDJqszB = false;
      bool orMGIianNY = false;
      bool WIsbGwDghi = false;
      string ztkYMWKRji;
      string eQwwkqdOAR;
      string AqkYtHEDDw;
      string wYAxEgzxMa;
      string NAdjbXcCXP;
      string LesHLHILeE;
      string RHOnmGQzrE;
      string rfBZEzMAwW;
      string eCemkQeslw;
      string XmSHJFkpxV;
      string GdKTWecTCL;
      string uIPHZPcaCV;
      string aWNugFNtQy;
      string NWCaPBqKQG;
      string mLpZBPXKgs;
      string cKmbtjPPmR;
      string QiDEyYForY;
      string XRKwhPgnsQ;
      string hDMWVDiaff;
      string kbXzoDHlac;
      if(ztkYMWKRji == GdKTWecTCL){KhSIVKzpse = true;}
      else if(GdKTWecTCL == ztkYMWKRji){tzlfANtgnq = true;}
      if(eQwwkqdOAR == uIPHZPcaCV){DbVViMWghu = true;}
      else if(uIPHZPcaCV == eQwwkqdOAR){jRWpiYsEQp = true;}
      if(AqkYtHEDDw == aWNugFNtQy){odILmwtKHe = true;}
      else if(aWNugFNtQy == AqkYtHEDDw){RidoJxjEbc = true;}
      if(wYAxEgzxMa == NWCaPBqKQG){HtMPGzkDAL = true;}
      else if(NWCaPBqKQG == wYAxEgzxMa){nccPjqFPej = true;}
      if(NAdjbXcCXP == mLpZBPXKgs){DrhBcJFBPb = true;}
      else if(mLpZBPXKgs == NAdjbXcCXP){lIrkpIHrrV = true;}
      if(LesHLHILeE == cKmbtjPPmR){gaEfnfYGUZ = true;}
      else if(cKmbtjPPmR == LesHLHILeE){UECnBKUwVC = true;}
      if(RHOnmGQzrE == QiDEyYForY){QoiOWIPGPj = true;}
      else if(QiDEyYForY == RHOnmGQzrE){coEKDGnHGq = true;}
      if(rfBZEzMAwW == XRKwhPgnsQ){bSfWqxwHid = true;}
      if(eCemkQeslw == hDMWVDiaff){pruexgpfbZ = true;}
      if(XmSHJFkpxV == kbXzoDHlac){ZeiatOISeT = true;}
      while(XRKwhPgnsQ == rfBZEzMAwW){SdZfDJqszB = true;}
      while(hDMWVDiaff == hDMWVDiaff){orMGIianNY = true;}
      while(kbXzoDHlac == kbXzoDHlac){WIsbGwDghi = true;}
      if(KhSIVKzpse == true){KhSIVKzpse = false;}
      if(DbVViMWghu == true){DbVViMWghu = false;}
      if(odILmwtKHe == true){odILmwtKHe = false;}
      if(HtMPGzkDAL == true){HtMPGzkDAL = false;}
      if(DrhBcJFBPb == true){DrhBcJFBPb = false;}
      if(gaEfnfYGUZ == true){gaEfnfYGUZ = false;}
      if(QoiOWIPGPj == true){QoiOWIPGPj = false;}
      if(bSfWqxwHid == true){bSfWqxwHid = false;}
      if(pruexgpfbZ == true){pruexgpfbZ = false;}
      if(ZeiatOISeT == true){ZeiatOISeT = false;}
      if(tzlfANtgnq == true){tzlfANtgnq = false;}
      if(jRWpiYsEQp == true){jRWpiYsEQp = false;}
      if(RidoJxjEbc == true){RidoJxjEbc = false;}
      if(nccPjqFPej == true){nccPjqFPej = false;}
      if(lIrkpIHrrV == true){lIrkpIHrrV = false;}
      if(UECnBKUwVC == true){UECnBKUwVC = false;}
      if(coEKDGnHGq == true){coEKDGnHGq = false;}
      if(SdZfDJqszB == true){SdZfDJqszB = false;}
      if(orMGIianNY == true){orMGIianNY = false;}
      if(WIsbGwDghi == true){WIsbGwDghi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGLTVPFJBQ
{ 
  void YQUhYHKfZH()
  { 
      bool XiAJbwPcnf = false;
      bool xUEXTNIVYa = false;
      bool oSumOWuybr = false;
      bool kTpZRfNepn = false;
      bool XJinOyJWGH = false;
      bool VkxoCFnMuE = false;
      bool ARAutceeFn = false;
      bool zdfjDejGYQ = false;
      bool NYqUVAVAXM = false;
      bool qBikmGImtk = false;
      bool SeQRHrFNlW = false;
      bool VgneqbZeYs = false;
      bool GdHsxyttww = false;
      bool VwLmxiIYNd = false;
      bool uINBqJMEtL = false;
      bool fdNAdoXWUJ = false;
      bool xKQpAYUAhI = false;
      bool TBRuyyQGCm = false;
      bool kpAkQrhKIH = false;
      bool LkEDgjqXAR = false;
      string AnbOiuFTVn;
      string ChoODoUJOM;
      string VfQPFsiiao;
      string hAzYZLSIJx;
      string FRATMtgsJS;
      string CbklxTWLJo;
      string LWrfGBiPnr;
      string VMzRGDfxDK;
      string MoYImFOMaF;
      string nHyTkiZTNK;
      string KQERxpcTft;
      string mZIycWxjsA;
      string mWniDNNefW;
      string dMjrzujHKw;
      string ctfgRNzzqO;
      string loZMXnbVNi;
      string bxnJPapPzg;
      string loZxXrpHQo;
      string OOnRknlWUL;
      string SOtaUeGWQq;
      if(AnbOiuFTVn == KQERxpcTft){XiAJbwPcnf = true;}
      else if(KQERxpcTft == AnbOiuFTVn){SeQRHrFNlW = true;}
      if(ChoODoUJOM == mZIycWxjsA){xUEXTNIVYa = true;}
      else if(mZIycWxjsA == ChoODoUJOM){VgneqbZeYs = true;}
      if(VfQPFsiiao == mWniDNNefW){oSumOWuybr = true;}
      else if(mWniDNNefW == VfQPFsiiao){GdHsxyttww = true;}
      if(hAzYZLSIJx == dMjrzujHKw){kTpZRfNepn = true;}
      else if(dMjrzujHKw == hAzYZLSIJx){VwLmxiIYNd = true;}
      if(FRATMtgsJS == ctfgRNzzqO){XJinOyJWGH = true;}
      else if(ctfgRNzzqO == FRATMtgsJS){uINBqJMEtL = true;}
      if(CbklxTWLJo == loZMXnbVNi){VkxoCFnMuE = true;}
      else if(loZMXnbVNi == CbklxTWLJo){fdNAdoXWUJ = true;}
      if(LWrfGBiPnr == bxnJPapPzg){ARAutceeFn = true;}
      else if(bxnJPapPzg == LWrfGBiPnr){xKQpAYUAhI = true;}
      if(VMzRGDfxDK == loZxXrpHQo){zdfjDejGYQ = true;}
      if(MoYImFOMaF == OOnRknlWUL){NYqUVAVAXM = true;}
      if(nHyTkiZTNK == SOtaUeGWQq){qBikmGImtk = true;}
      while(loZxXrpHQo == VMzRGDfxDK){TBRuyyQGCm = true;}
      while(OOnRknlWUL == OOnRknlWUL){kpAkQrhKIH = true;}
      while(SOtaUeGWQq == SOtaUeGWQq){LkEDgjqXAR = true;}
      if(XiAJbwPcnf == true){XiAJbwPcnf = false;}
      if(xUEXTNIVYa == true){xUEXTNIVYa = false;}
      if(oSumOWuybr == true){oSumOWuybr = false;}
      if(kTpZRfNepn == true){kTpZRfNepn = false;}
      if(XJinOyJWGH == true){XJinOyJWGH = false;}
      if(VkxoCFnMuE == true){VkxoCFnMuE = false;}
      if(ARAutceeFn == true){ARAutceeFn = false;}
      if(zdfjDejGYQ == true){zdfjDejGYQ = false;}
      if(NYqUVAVAXM == true){NYqUVAVAXM = false;}
      if(qBikmGImtk == true){qBikmGImtk = false;}
      if(SeQRHrFNlW == true){SeQRHrFNlW = false;}
      if(VgneqbZeYs == true){VgneqbZeYs = false;}
      if(GdHsxyttww == true){GdHsxyttww = false;}
      if(VwLmxiIYNd == true){VwLmxiIYNd = false;}
      if(uINBqJMEtL == true){uINBqJMEtL = false;}
      if(fdNAdoXWUJ == true){fdNAdoXWUJ = false;}
      if(xKQpAYUAhI == true){xKQpAYUAhI = false;}
      if(TBRuyyQGCm == true){TBRuyyQGCm = false;}
      if(kpAkQrhKIH == true){kpAkQrhKIH = false;}
      if(LkEDgjqXAR == true){LkEDgjqXAR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HATLCFVZCQ
{ 
  void uWIIKMBDqn()
  { 
      bool dxYrUYQFJt = false;
      bool TyIpbGDsoQ = false;
      bool jEImFPUQRF = false;
      bool MLUKsAuyqM = false;
      bool zyyGbWMOpm = false;
      bool CzIRdZnlmF = false;
      bool DAnDgIcxxa = false;
      bool KFCcRlGCLh = false;
      bool DGadDNDCgS = false;
      bool LJKlIzKtZS = false;
      bool tOQOcxxfAr = false;
      bool TlZFBxZJAS = false;
      bool EZQdPAtPTR = false;
      bool bLbrnnoLAG = false;
      bool QXBozYiFjL = false;
      bool ZAtGOTymzb = false;
      bool CgLiPHKhRN = false;
      bool HNItCgYbdp = false;
      bool QofHraRVcT = false;
      bool oCMYDjLSYr = false;
      string yEDCHRMUaC;
      string jiqebIDuJN;
      string LVFlJJOVYV;
      string mIUFofjKRx;
      string jUCwfYLAYC;
      string xhkmoczQsx;
      string CquEPaNlou;
      string XsdMcpSJFj;
      string yNwVXEWgPM;
      string gSQTtsZxfE;
      string KYKceDEXJy;
      string JoLIzntZgL;
      string EgVcOFcKSj;
      string QUcBZYDTqU;
      string zyWRDqHHTG;
      string zzQUAdChOY;
      string atFZhnMJia;
      string kZhLLFJEZX;
      string xUpMkQDHBw;
      string VUFRtFrxiO;
      if(yEDCHRMUaC == KYKceDEXJy){dxYrUYQFJt = true;}
      else if(KYKceDEXJy == yEDCHRMUaC){tOQOcxxfAr = true;}
      if(jiqebIDuJN == JoLIzntZgL){TyIpbGDsoQ = true;}
      else if(JoLIzntZgL == jiqebIDuJN){TlZFBxZJAS = true;}
      if(LVFlJJOVYV == EgVcOFcKSj){jEImFPUQRF = true;}
      else if(EgVcOFcKSj == LVFlJJOVYV){EZQdPAtPTR = true;}
      if(mIUFofjKRx == QUcBZYDTqU){MLUKsAuyqM = true;}
      else if(QUcBZYDTqU == mIUFofjKRx){bLbrnnoLAG = true;}
      if(jUCwfYLAYC == zyWRDqHHTG){zyyGbWMOpm = true;}
      else if(zyWRDqHHTG == jUCwfYLAYC){QXBozYiFjL = true;}
      if(xhkmoczQsx == zzQUAdChOY){CzIRdZnlmF = true;}
      else if(zzQUAdChOY == xhkmoczQsx){ZAtGOTymzb = true;}
      if(CquEPaNlou == atFZhnMJia){DAnDgIcxxa = true;}
      else if(atFZhnMJia == CquEPaNlou){CgLiPHKhRN = true;}
      if(XsdMcpSJFj == kZhLLFJEZX){KFCcRlGCLh = true;}
      if(yNwVXEWgPM == xUpMkQDHBw){DGadDNDCgS = true;}
      if(gSQTtsZxfE == VUFRtFrxiO){LJKlIzKtZS = true;}
      while(kZhLLFJEZX == XsdMcpSJFj){HNItCgYbdp = true;}
      while(xUpMkQDHBw == xUpMkQDHBw){QofHraRVcT = true;}
      while(VUFRtFrxiO == VUFRtFrxiO){oCMYDjLSYr = true;}
      if(dxYrUYQFJt == true){dxYrUYQFJt = false;}
      if(TyIpbGDsoQ == true){TyIpbGDsoQ = false;}
      if(jEImFPUQRF == true){jEImFPUQRF = false;}
      if(MLUKsAuyqM == true){MLUKsAuyqM = false;}
      if(zyyGbWMOpm == true){zyyGbWMOpm = false;}
      if(CzIRdZnlmF == true){CzIRdZnlmF = false;}
      if(DAnDgIcxxa == true){DAnDgIcxxa = false;}
      if(KFCcRlGCLh == true){KFCcRlGCLh = false;}
      if(DGadDNDCgS == true){DGadDNDCgS = false;}
      if(LJKlIzKtZS == true){LJKlIzKtZS = false;}
      if(tOQOcxxfAr == true){tOQOcxxfAr = false;}
      if(TlZFBxZJAS == true){TlZFBxZJAS = false;}
      if(EZQdPAtPTR == true){EZQdPAtPTR = false;}
      if(bLbrnnoLAG == true){bLbrnnoLAG = false;}
      if(QXBozYiFjL == true){QXBozYiFjL = false;}
      if(ZAtGOTymzb == true){ZAtGOTymzb = false;}
      if(CgLiPHKhRN == true){CgLiPHKhRN = false;}
      if(HNItCgYbdp == true){HNItCgYbdp = false;}
      if(QofHraRVcT == true){QofHraRVcT = false;}
      if(oCMYDjLSYr == true){oCMYDjLSYr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZPRAYVNLL
{ 
  void hhNXUtHNlE()
  { 
      bool gFRrKezwZU = false;
      bool GLacBoJpQC = false;
      bool GaqAIcaItz = false;
      bool WJfZiXGPwr = false;
      bool zEsQAjMmUS = false;
      bool wQjbaGNRih = false;
      bool EqCaxweAsd = false;
      bool htsXDBgazY = false;
      bool QmmaDGZDzb = false;
      bool JofNmHCSTE = false;
      bool FLsqkBWLYZ = false;
      bool YmSKRQEaWp = false;
      bool WaBRUsNeju = false;
      bool yOGuSEtwpC = false;
      bool jNeYDWWVwW = false;
      bool DbwdgdKbVq = false;
      bool mqacaKfWqN = false;
      bool WHkUGJubOy = false;
      bool WriNqWScNo = false;
      bool tRZzOrlCxr = false;
      string AwoApPnOSN;
      string cjhgobjpsb;
      string eOrNcpctnG;
      string oKPfjZVdSy;
      string OnmiylMbAu;
      string TtatVkDbXz;
      string lsaMYRUBwO;
      string FFXtNqbJPp;
      string dBtrltjUKz;
      string VtGSMUMaJf;
      string RLfkpNWffe;
      string JtLgVkzhad;
      string hzpxrKzEhs;
      string dBziYRUICX;
      string XDnfobhZwa;
      string VezfyRVhse;
      string ORxmBHtcHE;
      string PpfDFdKKHQ;
      string cYHHWyBTkH;
      string umPWIGGAdg;
      if(AwoApPnOSN == RLfkpNWffe){gFRrKezwZU = true;}
      else if(RLfkpNWffe == AwoApPnOSN){FLsqkBWLYZ = true;}
      if(cjhgobjpsb == JtLgVkzhad){GLacBoJpQC = true;}
      else if(JtLgVkzhad == cjhgobjpsb){YmSKRQEaWp = true;}
      if(eOrNcpctnG == hzpxrKzEhs){GaqAIcaItz = true;}
      else if(hzpxrKzEhs == eOrNcpctnG){WaBRUsNeju = true;}
      if(oKPfjZVdSy == dBziYRUICX){WJfZiXGPwr = true;}
      else if(dBziYRUICX == oKPfjZVdSy){yOGuSEtwpC = true;}
      if(OnmiylMbAu == XDnfobhZwa){zEsQAjMmUS = true;}
      else if(XDnfobhZwa == OnmiylMbAu){jNeYDWWVwW = true;}
      if(TtatVkDbXz == VezfyRVhse){wQjbaGNRih = true;}
      else if(VezfyRVhse == TtatVkDbXz){DbwdgdKbVq = true;}
      if(lsaMYRUBwO == ORxmBHtcHE){EqCaxweAsd = true;}
      else if(ORxmBHtcHE == lsaMYRUBwO){mqacaKfWqN = true;}
      if(FFXtNqbJPp == PpfDFdKKHQ){htsXDBgazY = true;}
      if(dBtrltjUKz == cYHHWyBTkH){QmmaDGZDzb = true;}
      if(VtGSMUMaJf == umPWIGGAdg){JofNmHCSTE = true;}
      while(PpfDFdKKHQ == FFXtNqbJPp){WHkUGJubOy = true;}
      while(cYHHWyBTkH == cYHHWyBTkH){WriNqWScNo = true;}
      while(umPWIGGAdg == umPWIGGAdg){tRZzOrlCxr = true;}
      if(gFRrKezwZU == true){gFRrKezwZU = false;}
      if(GLacBoJpQC == true){GLacBoJpQC = false;}
      if(GaqAIcaItz == true){GaqAIcaItz = false;}
      if(WJfZiXGPwr == true){WJfZiXGPwr = false;}
      if(zEsQAjMmUS == true){zEsQAjMmUS = false;}
      if(wQjbaGNRih == true){wQjbaGNRih = false;}
      if(EqCaxweAsd == true){EqCaxweAsd = false;}
      if(htsXDBgazY == true){htsXDBgazY = false;}
      if(QmmaDGZDzb == true){QmmaDGZDzb = false;}
      if(JofNmHCSTE == true){JofNmHCSTE = false;}
      if(FLsqkBWLYZ == true){FLsqkBWLYZ = false;}
      if(YmSKRQEaWp == true){YmSKRQEaWp = false;}
      if(WaBRUsNeju == true){WaBRUsNeju = false;}
      if(yOGuSEtwpC == true){yOGuSEtwpC = false;}
      if(jNeYDWWVwW == true){jNeYDWWVwW = false;}
      if(DbwdgdKbVq == true){DbwdgdKbVq = false;}
      if(mqacaKfWqN == true){mqacaKfWqN = false;}
      if(WHkUGJubOy == true){WHkUGJubOy = false;}
      if(WriNqWScNo == true){WriNqWScNo = false;}
      if(tRZzOrlCxr == true){tRZzOrlCxr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKEZMQXFXB
{ 
  void ZqcqfTZnPL()
  { 
      bool nrgEHTbuHt = false;
      bool teJAADyxiA = false;
      bool KQLIJXPUMo = false;
      bool HOpSMsubxg = false;
      bool BicinzaGdu = false;
      bool bYKsLXfYui = false;
      bool EGiRleopmG = false;
      bool IVACzbncTK = false;
      bool wIpRNhDwHo = false;
      bool MWfNbtzKwJ = false;
      bool JjTWmFYIti = false;
      bool iDFkmwPRDE = false;
      bool ariytlplZE = false;
      bool cdgJALoTeI = false;
      bool IuBYGJRtZf = false;
      bool dhGqiQBUcA = false;
      bool OlhpGFWuka = false;
      bool HwluueqKrk = false;
      bool UuMtatWoai = false;
      bool KTqdsVNLRA = false;
      string qXSQwLVono;
      string tnnqtYFWSV;
      string NfRBLyelIn;
      string LwuczElFWo;
      string GVwTZihsip;
      string eDApYLGQEx;
      string figzcyrLqo;
      string mzzdOrixbb;
      string QlCRJIuFDn;
      string yVAZJWoxqa;
      string pWBsCeEWaf;
      string bIocgsfOpT;
      string CmHCqRzYUq;
      string DlGAlsjJPd;
      string EYdWMpfXrP;
      string paHWXDPzBk;
      string eeBjcpBnqm;
      string IWyLPdJjpB;
      string kbgEAcejch;
      string dkHdyZWttW;
      if(qXSQwLVono == pWBsCeEWaf){nrgEHTbuHt = true;}
      else if(pWBsCeEWaf == qXSQwLVono){JjTWmFYIti = true;}
      if(tnnqtYFWSV == bIocgsfOpT){teJAADyxiA = true;}
      else if(bIocgsfOpT == tnnqtYFWSV){iDFkmwPRDE = true;}
      if(NfRBLyelIn == CmHCqRzYUq){KQLIJXPUMo = true;}
      else if(CmHCqRzYUq == NfRBLyelIn){ariytlplZE = true;}
      if(LwuczElFWo == DlGAlsjJPd){HOpSMsubxg = true;}
      else if(DlGAlsjJPd == LwuczElFWo){cdgJALoTeI = true;}
      if(GVwTZihsip == EYdWMpfXrP){BicinzaGdu = true;}
      else if(EYdWMpfXrP == GVwTZihsip){IuBYGJRtZf = true;}
      if(eDApYLGQEx == paHWXDPzBk){bYKsLXfYui = true;}
      else if(paHWXDPzBk == eDApYLGQEx){dhGqiQBUcA = true;}
      if(figzcyrLqo == eeBjcpBnqm){EGiRleopmG = true;}
      else if(eeBjcpBnqm == figzcyrLqo){OlhpGFWuka = true;}
      if(mzzdOrixbb == IWyLPdJjpB){IVACzbncTK = true;}
      if(QlCRJIuFDn == kbgEAcejch){wIpRNhDwHo = true;}
      if(yVAZJWoxqa == dkHdyZWttW){MWfNbtzKwJ = true;}
      while(IWyLPdJjpB == mzzdOrixbb){HwluueqKrk = true;}
      while(kbgEAcejch == kbgEAcejch){UuMtatWoai = true;}
      while(dkHdyZWttW == dkHdyZWttW){KTqdsVNLRA = true;}
      if(nrgEHTbuHt == true){nrgEHTbuHt = false;}
      if(teJAADyxiA == true){teJAADyxiA = false;}
      if(KQLIJXPUMo == true){KQLIJXPUMo = false;}
      if(HOpSMsubxg == true){HOpSMsubxg = false;}
      if(BicinzaGdu == true){BicinzaGdu = false;}
      if(bYKsLXfYui == true){bYKsLXfYui = false;}
      if(EGiRleopmG == true){EGiRleopmG = false;}
      if(IVACzbncTK == true){IVACzbncTK = false;}
      if(wIpRNhDwHo == true){wIpRNhDwHo = false;}
      if(MWfNbtzKwJ == true){MWfNbtzKwJ = false;}
      if(JjTWmFYIti == true){JjTWmFYIti = false;}
      if(iDFkmwPRDE == true){iDFkmwPRDE = false;}
      if(ariytlplZE == true){ariytlplZE = false;}
      if(cdgJALoTeI == true){cdgJALoTeI = false;}
      if(IuBYGJRtZf == true){IuBYGJRtZf = false;}
      if(dhGqiQBUcA == true){dhGqiQBUcA = false;}
      if(OlhpGFWuka == true){OlhpGFWuka = false;}
      if(HwluueqKrk == true){HwluueqKrk = false;}
      if(UuMtatWoai == true){UuMtatWoai = false;}
      if(KTqdsVNLRA == true){KTqdsVNLRA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JAUYWUBUSV
{ 
  void ynQOdSpfMk()
  { 
      bool chsojeXHcB = false;
      bool dSoGkeeEhZ = false;
      bool czkLJFlJMe = false;
      bool wUHlhjmWrq = false;
      bool ArFVgHGNlw = false;
      bool rScTadxhee = false;
      bool sOtxFJKDYA = false;
      bool qHLpZksOdB = false;
      bool yXXQmdqnKD = false;
      bool mEqNykyHQX = false;
      bool wDnkEjGmtp = false;
      bool khEdfUqdKb = false;
      bool SWrUNmPyrn = false;
      bool mkxFEujlLC = false;
      bool WEtUSEzNgd = false;
      bool tUxoFZKSXR = false;
      bool UHtFDzkyYj = false;
      bool kERHENbWCI = false;
      bool mBROsRnIAd = false;
      bool jQOshOJnRT = false;
      string CLAgQfOAmO;
      string GyyalorfMk;
      string CMIIJeSsEP;
      string IfZmwJkipe;
      string zKtAUeXjRQ;
      string SSdxTpDqXl;
      string NUwXFZYLec;
      string DJoglrRHnd;
      string HhbnwpBbSF;
      string GtLERdNWtt;
      string GMFoMJcxLb;
      string XuDteesIaP;
      string YwrYWJykPH;
      string duNtWtcmam;
      string NEPqhKqQYl;
      string kFueVKTgSD;
      string LqgEychIWj;
      string CGgnBTfBqL;
      string RgMcVXzhXL;
      string awUXaWWLsE;
      if(CLAgQfOAmO == GMFoMJcxLb){chsojeXHcB = true;}
      else if(GMFoMJcxLb == CLAgQfOAmO){wDnkEjGmtp = true;}
      if(GyyalorfMk == XuDteesIaP){dSoGkeeEhZ = true;}
      else if(XuDteesIaP == GyyalorfMk){khEdfUqdKb = true;}
      if(CMIIJeSsEP == YwrYWJykPH){czkLJFlJMe = true;}
      else if(YwrYWJykPH == CMIIJeSsEP){SWrUNmPyrn = true;}
      if(IfZmwJkipe == duNtWtcmam){wUHlhjmWrq = true;}
      else if(duNtWtcmam == IfZmwJkipe){mkxFEujlLC = true;}
      if(zKtAUeXjRQ == NEPqhKqQYl){ArFVgHGNlw = true;}
      else if(NEPqhKqQYl == zKtAUeXjRQ){WEtUSEzNgd = true;}
      if(SSdxTpDqXl == kFueVKTgSD){rScTadxhee = true;}
      else if(kFueVKTgSD == SSdxTpDqXl){tUxoFZKSXR = true;}
      if(NUwXFZYLec == LqgEychIWj){sOtxFJKDYA = true;}
      else if(LqgEychIWj == NUwXFZYLec){UHtFDzkyYj = true;}
      if(DJoglrRHnd == CGgnBTfBqL){qHLpZksOdB = true;}
      if(HhbnwpBbSF == RgMcVXzhXL){yXXQmdqnKD = true;}
      if(GtLERdNWtt == awUXaWWLsE){mEqNykyHQX = true;}
      while(CGgnBTfBqL == DJoglrRHnd){kERHENbWCI = true;}
      while(RgMcVXzhXL == RgMcVXzhXL){mBROsRnIAd = true;}
      while(awUXaWWLsE == awUXaWWLsE){jQOshOJnRT = true;}
      if(chsojeXHcB == true){chsojeXHcB = false;}
      if(dSoGkeeEhZ == true){dSoGkeeEhZ = false;}
      if(czkLJFlJMe == true){czkLJFlJMe = false;}
      if(wUHlhjmWrq == true){wUHlhjmWrq = false;}
      if(ArFVgHGNlw == true){ArFVgHGNlw = false;}
      if(rScTadxhee == true){rScTadxhee = false;}
      if(sOtxFJKDYA == true){sOtxFJKDYA = false;}
      if(qHLpZksOdB == true){qHLpZksOdB = false;}
      if(yXXQmdqnKD == true){yXXQmdqnKD = false;}
      if(mEqNykyHQX == true){mEqNykyHQX = false;}
      if(wDnkEjGmtp == true){wDnkEjGmtp = false;}
      if(khEdfUqdKb == true){khEdfUqdKb = false;}
      if(SWrUNmPyrn == true){SWrUNmPyrn = false;}
      if(mkxFEujlLC == true){mkxFEujlLC = false;}
      if(WEtUSEzNgd == true){WEtUSEzNgd = false;}
      if(tUxoFZKSXR == true){tUxoFZKSXR = false;}
      if(UHtFDzkyYj == true){UHtFDzkyYj = false;}
      if(kERHENbWCI == true){kERHENbWCI = false;}
      if(mBROsRnIAd == true){mBROsRnIAd = false;}
      if(jQOshOJnRT == true){jQOshOJnRT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JRCYLMMGNI
{ 
  void zOCqbpTLyP()
  { 
      bool kSOoVAAtpZ = false;
      bool nIbZZtFzPy = false;
      bool FJuwCOwjGW = false;
      bool ODlbspIuXU = false;
      bool xORNkblbcV = false;
      bool FfdTMaWSlG = false;
      bool DQmTLkWzfi = false;
      bool kJbtBqrgKa = false;
      bool cUGkQhYSPR = false;
      bool SpIQQfbyCA = false;
      bool FlutjwEjRU = false;
      bool ioILdiJBCc = false;
      bool LDiNPuBLcU = false;
      bool PseJUpYMBU = false;
      bool doAtidhxlh = false;
      bool VZuZnCDgdo = false;
      bool tsGxFoKyqn = false;
      bool KxAhyWDnel = false;
      bool MEYuyoyEVR = false;
      bool lqiMZkhDos = false;
      string VNJKxMNxfa;
      string WdwyPzEOzd;
      string VkeQBdVNoP;
      string msQeEhobjz;
      string EVnsSbypTG;
      string EhjfhjhrIS;
      string pzIQmcNQth;
      string JceAZzwkyZ;
      string fesiKEJkxT;
      string zxTQIENWGo;
      string NgwlwbDjFh;
      string mxshmLFZGi;
      string TbTZhMJNqU;
      string lZeJLyiGli;
      string AYeOfCDkdx;
      string znQXUlNVEi;
      string SoskwNRjVn;
      string bymWhuxEte;
      string JXjsVyIHnZ;
      string kNCDPLftRR;
      if(VNJKxMNxfa == NgwlwbDjFh){kSOoVAAtpZ = true;}
      else if(NgwlwbDjFh == VNJKxMNxfa){FlutjwEjRU = true;}
      if(WdwyPzEOzd == mxshmLFZGi){nIbZZtFzPy = true;}
      else if(mxshmLFZGi == WdwyPzEOzd){ioILdiJBCc = true;}
      if(VkeQBdVNoP == TbTZhMJNqU){FJuwCOwjGW = true;}
      else if(TbTZhMJNqU == VkeQBdVNoP){LDiNPuBLcU = true;}
      if(msQeEhobjz == lZeJLyiGli){ODlbspIuXU = true;}
      else if(lZeJLyiGli == msQeEhobjz){PseJUpYMBU = true;}
      if(EVnsSbypTG == AYeOfCDkdx){xORNkblbcV = true;}
      else if(AYeOfCDkdx == EVnsSbypTG){doAtidhxlh = true;}
      if(EhjfhjhrIS == znQXUlNVEi){FfdTMaWSlG = true;}
      else if(znQXUlNVEi == EhjfhjhrIS){VZuZnCDgdo = true;}
      if(pzIQmcNQth == SoskwNRjVn){DQmTLkWzfi = true;}
      else if(SoskwNRjVn == pzIQmcNQth){tsGxFoKyqn = true;}
      if(JceAZzwkyZ == bymWhuxEte){kJbtBqrgKa = true;}
      if(fesiKEJkxT == JXjsVyIHnZ){cUGkQhYSPR = true;}
      if(zxTQIENWGo == kNCDPLftRR){SpIQQfbyCA = true;}
      while(bymWhuxEte == JceAZzwkyZ){KxAhyWDnel = true;}
      while(JXjsVyIHnZ == JXjsVyIHnZ){MEYuyoyEVR = true;}
      while(kNCDPLftRR == kNCDPLftRR){lqiMZkhDos = true;}
      if(kSOoVAAtpZ == true){kSOoVAAtpZ = false;}
      if(nIbZZtFzPy == true){nIbZZtFzPy = false;}
      if(FJuwCOwjGW == true){FJuwCOwjGW = false;}
      if(ODlbspIuXU == true){ODlbspIuXU = false;}
      if(xORNkblbcV == true){xORNkblbcV = false;}
      if(FfdTMaWSlG == true){FfdTMaWSlG = false;}
      if(DQmTLkWzfi == true){DQmTLkWzfi = false;}
      if(kJbtBqrgKa == true){kJbtBqrgKa = false;}
      if(cUGkQhYSPR == true){cUGkQhYSPR = false;}
      if(SpIQQfbyCA == true){SpIQQfbyCA = false;}
      if(FlutjwEjRU == true){FlutjwEjRU = false;}
      if(ioILdiJBCc == true){ioILdiJBCc = false;}
      if(LDiNPuBLcU == true){LDiNPuBLcU = false;}
      if(PseJUpYMBU == true){PseJUpYMBU = false;}
      if(doAtidhxlh == true){doAtidhxlh = false;}
      if(VZuZnCDgdo == true){VZuZnCDgdo = false;}
      if(tsGxFoKyqn == true){tsGxFoKyqn = false;}
      if(KxAhyWDnel == true){KxAhyWDnel = false;}
      if(MEYuyoyEVR == true){MEYuyoyEVR = false;}
      if(lqiMZkhDos == true){lqiMZkhDos = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQFOSFYGGS
{ 
  void ApqmqnsWIZ()
  { 
      bool NyJELLLoHo = false;
      bool FEEmMeNpUE = false;
      bool jNcpFAjWRH = false;
      bool VQdAxdZCZY = false;
      bool wWVlzwearQ = false;
      bool ymjRkAUSzL = false;
      bool anWzSnZDoi = false;
      bool FKPwHNqqpJ = false;
      bool VJeBJifMPx = false;
      bool IGDOxHzWSL = false;
      bool WakJLnWnJX = false;
      bool IdcppRJVpi = false;
      bool IMnqZyGByz = false;
      bool NUXeltXVoU = false;
      bool MqCqoddNYf = false;
      bool ycgiCJmtiM = false;
      bool gVoKKnGxDu = false;
      bool tmfUWQJwCu = false;
      bool UrbSBjmncc = false;
      bool HdmcnqBrgA = false;
      string KTqQJXtMZV;
      string RTjwzsXOjV;
      string BGlRwFEHdl;
      string yyZJfhtBZK;
      string GsPCKENefQ;
      string YbiORDgZTD;
      string TlimXStZQQ;
      string yVnYOHqjGq;
      string rYaMNVOLrc;
      string BUgVqUKbdr;
      string KmOOSCmKzJ;
      string LwScLtKVYC;
      string DihmPdnSht;
      string xPFOgFKMtK;
      string hELhREBEKw;
      string JnDbnbEayo;
      string OUbFMwqDuG;
      string jybNUzWAVL;
      string biHljILdaE;
      string AjNFwMcFVU;
      if(KTqQJXtMZV == KmOOSCmKzJ){NyJELLLoHo = true;}
      else if(KmOOSCmKzJ == KTqQJXtMZV){WakJLnWnJX = true;}
      if(RTjwzsXOjV == LwScLtKVYC){FEEmMeNpUE = true;}
      else if(LwScLtKVYC == RTjwzsXOjV){IdcppRJVpi = true;}
      if(BGlRwFEHdl == DihmPdnSht){jNcpFAjWRH = true;}
      else if(DihmPdnSht == BGlRwFEHdl){IMnqZyGByz = true;}
      if(yyZJfhtBZK == xPFOgFKMtK){VQdAxdZCZY = true;}
      else if(xPFOgFKMtK == yyZJfhtBZK){NUXeltXVoU = true;}
      if(GsPCKENefQ == hELhREBEKw){wWVlzwearQ = true;}
      else if(hELhREBEKw == GsPCKENefQ){MqCqoddNYf = true;}
      if(YbiORDgZTD == JnDbnbEayo){ymjRkAUSzL = true;}
      else if(JnDbnbEayo == YbiORDgZTD){ycgiCJmtiM = true;}
      if(TlimXStZQQ == OUbFMwqDuG){anWzSnZDoi = true;}
      else if(OUbFMwqDuG == TlimXStZQQ){gVoKKnGxDu = true;}
      if(yVnYOHqjGq == jybNUzWAVL){FKPwHNqqpJ = true;}
      if(rYaMNVOLrc == biHljILdaE){VJeBJifMPx = true;}
      if(BUgVqUKbdr == AjNFwMcFVU){IGDOxHzWSL = true;}
      while(jybNUzWAVL == yVnYOHqjGq){tmfUWQJwCu = true;}
      while(biHljILdaE == biHljILdaE){UrbSBjmncc = true;}
      while(AjNFwMcFVU == AjNFwMcFVU){HdmcnqBrgA = true;}
      if(NyJELLLoHo == true){NyJELLLoHo = false;}
      if(FEEmMeNpUE == true){FEEmMeNpUE = false;}
      if(jNcpFAjWRH == true){jNcpFAjWRH = false;}
      if(VQdAxdZCZY == true){VQdAxdZCZY = false;}
      if(wWVlzwearQ == true){wWVlzwearQ = false;}
      if(ymjRkAUSzL == true){ymjRkAUSzL = false;}
      if(anWzSnZDoi == true){anWzSnZDoi = false;}
      if(FKPwHNqqpJ == true){FKPwHNqqpJ = false;}
      if(VJeBJifMPx == true){VJeBJifMPx = false;}
      if(IGDOxHzWSL == true){IGDOxHzWSL = false;}
      if(WakJLnWnJX == true){WakJLnWnJX = false;}
      if(IdcppRJVpi == true){IdcppRJVpi = false;}
      if(IMnqZyGByz == true){IMnqZyGByz = false;}
      if(NUXeltXVoU == true){NUXeltXVoU = false;}
      if(MqCqoddNYf == true){MqCqoddNYf = false;}
      if(ycgiCJmtiM == true){ycgiCJmtiM = false;}
      if(gVoKKnGxDu == true){gVoKKnGxDu = false;}
      if(tmfUWQJwCu == true){tmfUWQJwCu = false;}
      if(UrbSBjmncc == true){UrbSBjmncc = false;}
      if(HdmcnqBrgA == true){HdmcnqBrgA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NEKRGFUSRQ
{ 
  void AFRJsOwpJz()
  { 
      bool QnFqCSHfTg = false;
      bool hHLWyEYXSs = false;
      bool odJEkjiBSw = false;
      bool pTiKcbNPOf = false;
      bool pURUtPVDXX = false;
      bool qkRlDleAFR = false;
      bool iFMWpNYBtV = false;
      bool qIImCULnJU = false;
      bool NfduFECwHp = false;
      bool xMKwwjHudf = false;
      bool qUIBficdji = false;
      bool ZppjDDbQQk = false;
      bool LbsDYdxMpR = false;
      bool MQKddsWcOW = false;
      bool bXMYPGVars = false;
      bool IpdrUOaFbB = false;
      bool kPnRVJfMFJ = false;
      bool fyBtJmOUmS = false;
      bool IWTxIVlRIO = false;
      bool SRANkLjtCG = false;
      string DdNBlyrgLZ;
      string kqMwsEVSSO;
      string lonJzijKFo;
      string hQqjMEwjGy;
      string KRrgxrikdn;
      string NztwqNoECC;
      string OgaVqTAcjn;
      string HlLUEUxHLG;
      string zyfRaiWtry;
      string OqhDjcpVod;
      string rFBpfbmYrV;
      string QhruDPAJuI;
      string xFjkZQEHka;
      string eaShOsxpkz;
      string uxBWhfzlAT;
      string cfafflVPPP;
      string WfnRqoPKgJ;
      string RJXuMzENDs;
      string QSHQyyAlBb;
      string XhZVbPJjer;
      if(DdNBlyrgLZ == rFBpfbmYrV){QnFqCSHfTg = true;}
      else if(rFBpfbmYrV == DdNBlyrgLZ){qUIBficdji = true;}
      if(kqMwsEVSSO == QhruDPAJuI){hHLWyEYXSs = true;}
      else if(QhruDPAJuI == kqMwsEVSSO){ZppjDDbQQk = true;}
      if(lonJzijKFo == xFjkZQEHka){odJEkjiBSw = true;}
      else if(xFjkZQEHka == lonJzijKFo){LbsDYdxMpR = true;}
      if(hQqjMEwjGy == eaShOsxpkz){pTiKcbNPOf = true;}
      else if(eaShOsxpkz == hQqjMEwjGy){MQKddsWcOW = true;}
      if(KRrgxrikdn == uxBWhfzlAT){pURUtPVDXX = true;}
      else if(uxBWhfzlAT == KRrgxrikdn){bXMYPGVars = true;}
      if(NztwqNoECC == cfafflVPPP){qkRlDleAFR = true;}
      else if(cfafflVPPP == NztwqNoECC){IpdrUOaFbB = true;}
      if(OgaVqTAcjn == WfnRqoPKgJ){iFMWpNYBtV = true;}
      else if(WfnRqoPKgJ == OgaVqTAcjn){kPnRVJfMFJ = true;}
      if(HlLUEUxHLG == RJXuMzENDs){qIImCULnJU = true;}
      if(zyfRaiWtry == QSHQyyAlBb){NfduFECwHp = true;}
      if(OqhDjcpVod == XhZVbPJjer){xMKwwjHudf = true;}
      while(RJXuMzENDs == HlLUEUxHLG){fyBtJmOUmS = true;}
      while(QSHQyyAlBb == QSHQyyAlBb){IWTxIVlRIO = true;}
      while(XhZVbPJjer == XhZVbPJjer){SRANkLjtCG = true;}
      if(QnFqCSHfTg == true){QnFqCSHfTg = false;}
      if(hHLWyEYXSs == true){hHLWyEYXSs = false;}
      if(odJEkjiBSw == true){odJEkjiBSw = false;}
      if(pTiKcbNPOf == true){pTiKcbNPOf = false;}
      if(pURUtPVDXX == true){pURUtPVDXX = false;}
      if(qkRlDleAFR == true){qkRlDleAFR = false;}
      if(iFMWpNYBtV == true){iFMWpNYBtV = false;}
      if(qIImCULnJU == true){qIImCULnJU = false;}
      if(NfduFECwHp == true){NfduFECwHp = false;}
      if(xMKwwjHudf == true){xMKwwjHudf = false;}
      if(qUIBficdji == true){qUIBficdji = false;}
      if(ZppjDDbQQk == true){ZppjDDbQQk = false;}
      if(LbsDYdxMpR == true){LbsDYdxMpR = false;}
      if(MQKddsWcOW == true){MQKddsWcOW = false;}
      if(bXMYPGVars == true){bXMYPGVars = false;}
      if(IpdrUOaFbB == true){IpdrUOaFbB = false;}
      if(kPnRVJfMFJ == true){kPnRVJfMFJ = false;}
      if(fyBtJmOUmS == true){fyBtJmOUmS = false;}
      if(IWTxIVlRIO == true){IWTxIVlRIO = false;}
      if(SRANkLjtCG == true){SRANkLjtCG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZCZLEPYLV
{ 
  void oUcFnwgoOH()
  { 
      bool KmZhGOkbhL = false;
      bool IPNjetZnXk = false;
      bool kSMPeNaPui = false;
      bool mQReFhkSso = false;
      bool pmzNylWCDb = false;
      bool cTCzxrZJCr = false;
      bool nVgzYryhex = false;
      bool IGuiuyTyQs = false;
      bool pYMTFSNRhM = false;
      bool HbQAAUFzoG = false;
      bool mnWFSVXTEz = false;
      bool YbsIBPJNsF = false;
      bool dfARpgpuhZ = false;
      bool rTJJFCBGAj = false;
      bool tsNhnfhHyk = false;
      bool LrFibHnFPl = false;
      bool ecldHERiDz = false;
      bool NCNILjRScJ = false;
      bool yiwwOzNagy = false;
      bool NupNFQHjZj = false;
      string NoJdARuKMc;
      string imftkYifqC;
      string sJDLAQNeDh;
      string sCfNzxnCAU;
      string rUPTfAgXPc;
      string sXOSuEkycj;
      string DPGejfGRum;
      string jgfVJYsjfA;
      string ipPanUnMSu;
      string LpYPRcOjiz;
      string sPcbsMqrJW;
      string KBRcAMAfqP;
      string rtyzbsHPEg;
      string JIBfGTNmha;
      string dwDwkKYwPF;
      string cisTHzRcAz;
      string FanbMBAlWg;
      string yNxQkuqBOQ;
      string ULAzEaPgYG;
      string BklhVCIaji;
      if(NoJdARuKMc == sPcbsMqrJW){KmZhGOkbhL = true;}
      else if(sPcbsMqrJW == NoJdARuKMc){mnWFSVXTEz = true;}
      if(imftkYifqC == KBRcAMAfqP){IPNjetZnXk = true;}
      else if(KBRcAMAfqP == imftkYifqC){YbsIBPJNsF = true;}
      if(sJDLAQNeDh == rtyzbsHPEg){kSMPeNaPui = true;}
      else if(rtyzbsHPEg == sJDLAQNeDh){dfARpgpuhZ = true;}
      if(sCfNzxnCAU == JIBfGTNmha){mQReFhkSso = true;}
      else if(JIBfGTNmha == sCfNzxnCAU){rTJJFCBGAj = true;}
      if(rUPTfAgXPc == dwDwkKYwPF){pmzNylWCDb = true;}
      else if(dwDwkKYwPF == rUPTfAgXPc){tsNhnfhHyk = true;}
      if(sXOSuEkycj == cisTHzRcAz){cTCzxrZJCr = true;}
      else if(cisTHzRcAz == sXOSuEkycj){LrFibHnFPl = true;}
      if(DPGejfGRum == FanbMBAlWg){nVgzYryhex = true;}
      else if(FanbMBAlWg == DPGejfGRum){ecldHERiDz = true;}
      if(jgfVJYsjfA == yNxQkuqBOQ){IGuiuyTyQs = true;}
      if(ipPanUnMSu == ULAzEaPgYG){pYMTFSNRhM = true;}
      if(LpYPRcOjiz == BklhVCIaji){HbQAAUFzoG = true;}
      while(yNxQkuqBOQ == jgfVJYsjfA){NCNILjRScJ = true;}
      while(ULAzEaPgYG == ULAzEaPgYG){yiwwOzNagy = true;}
      while(BklhVCIaji == BklhVCIaji){NupNFQHjZj = true;}
      if(KmZhGOkbhL == true){KmZhGOkbhL = false;}
      if(IPNjetZnXk == true){IPNjetZnXk = false;}
      if(kSMPeNaPui == true){kSMPeNaPui = false;}
      if(mQReFhkSso == true){mQReFhkSso = false;}
      if(pmzNylWCDb == true){pmzNylWCDb = false;}
      if(cTCzxrZJCr == true){cTCzxrZJCr = false;}
      if(nVgzYryhex == true){nVgzYryhex = false;}
      if(IGuiuyTyQs == true){IGuiuyTyQs = false;}
      if(pYMTFSNRhM == true){pYMTFSNRhM = false;}
      if(HbQAAUFzoG == true){HbQAAUFzoG = false;}
      if(mnWFSVXTEz == true){mnWFSVXTEz = false;}
      if(YbsIBPJNsF == true){YbsIBPJNsF = false;}
      if(dfARpgpuhZ == true){dfARpgpuhZ = false;}
      if(rTJJFCBGAj == true){rTJJFCBGAj = false;}
      if(tsNhnfhHyk == true){tsNhnfhHyk = false;}
      if(LrFibHnFPl == true){LrFibHnFPl = false;}
      if(ecldHERiDz == true){ecldHERiDz = false;}
      if(NCNILjRScJ == true){NCNILjRScJ = false;}
      if(yiwwOzNagy == true){yiwwOzNagy = false;}
      if(NupNFQHjZj == true){NupNFQHjZj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKAKRFBBQD
{ 
  void zgMjbwjwuK()
  { 
      bool aadhAEtbZY = false;
      bool EooNKRpkHW = false;
      bool VyVmFZnqmh = false;
      bool MgfLzPhLIs = false;
      bool IpiArMQxbE = false;
      bool VmgLDbFqca = false;
      bool QDoqLXIcNu = false;
      bool jecOOePVtr = false;
      bool JpOiMZzUHW = false;
      bool KpihbFBqoU = false;
      bool EmigUqKSxX = false;
      bool MixjRZnGel = false;
      bool XnUpkswulJ = false;
      bool dXfZnVGhNV = false;
      bool PgWjKasyPC = false;
      bool QuMDwQRsua = false;
      bool tPfmtnCXwu = false;
      bool SGrJVpQkfK = false;
      bool zyejriKccW = false;
      bool DNmlazBjoW = false;
      string QoCApsUJcf;
      string TjRIXzwjeG;
      string mTNWatfXkL;
      string WNQhDtixyC;
      string ARPWWKLcaf;
      string EFLNWxafYu;
      string MwYRJGTiFc;
      string QzlcFUDpAP;
      string hDxEGQBCKG;
      string SCXCoDsyNP;
      string qbXxPFThHC;
      string skfIMJzTLr;
      string FQXyJNainC;
      string bFcjYFezoB;
      string xStINhWOoe;
      string EYlUKaEZnB;
      string djtFZnHujH;
      string ezeKulVPka;
      string pMsIyCSIYx;
      string BFLmWMYoiY;
      if(QoCApsUJcf == qbXxPFThHC){aadhAEtbZY = true;}
      else if(qbXxPFThHC == QoCApsUJcf){EmigUqKSxX = true;}
      if(TjRIXzwjeG == skfIMJzTLr){EooNKRpkHW = true;}
      else if(skfIMJzTLr == TjRIXzwjeG){MixjRZnGel = true;}
      if(mTNWatfXkL == FQXyJNainC){VyVmFZnqmh = true;}
      else if(FQXyJNainC == mTNWatfXkL){XnUpkswulJ = true;}
      if(WNQhDtixyC == bFcjYFezoB){MgfLzPhLIs = true;}
      else if(bFcjYFezoB == WNQhDtixyC){dXfZnVGhNV = true;}
      if(ARPWWKLcaf == xStINhWOoe){IpiArMQxbE = true;}
      else if(xStINhWOoe == ARPWWKLcaf){PgWjKasyPC = true;}
      if(EFLNWxafYu == EYlUKaEZnB){VmgLDbFqca = true;}
      else if(EYlUKaEZnB == EFLNWxafYu){QuMDwQRsua = true;}
      if(MwYRJGTiFc == djtFZnHujH){QDoqLXIcNu = true;}
      else if(djtFZnHujH == MwYRJGTiFc){tPfmtnCXwu = true;}
      if(QzlcFUDpAP == ezeKulVPka){jecOOePVtr = true;}
      if(hDxEGQBCKG == pMsIyCSIYx){JpOiMZzUHW = true;}
      if(SCXCoDsyNP == BFLmWMYoiY){KpihbFBqoU = true;}
      while(ezeKulVPka == QzlcFUDpAP){SGrJVpQkfK = true;}
      while(pMsIyCSIYx == pMsIyCSIYx){zyejriKccW = true;}
      while(BFLmWMYoiY == BFLmWMYoiY){DNmlazBjoW = true;}
      if(aadhAEtbZY == true){aadhAEtbZY = false;}
      if(EooNKRpkHW == true){EooNKRpkHW = false;}
      if(VyVmFZnqmh == true){VyVmFZnqmh = false;}
      if(MgfLzPhLIs == true){MgfLzPhLIs = false;}
      if(IpiArMQxbE == true){IpiArMQxbE = false;}
      if(VmgLDbFqca == true){VmgLDbFqca = false;}
      if(QDoqLXIcNu == true){QDoqLXIcNu = false;}
      if(jecOOePVtr == true){jecOOePVtr = false;}
      if(JpOiMZzUHW == true){JpOiMZzUHW = false;}
      if(KpihbFBqoU == true){KpihbFBqoU = false;}
      if(EmigUqKSxX == true){EmigUqKSxX = false;}
      if(MixjRZnGel == true){MixjRZnGel = false;}
      if(XnUpkswulJ == true){XnUpkswulJ = false;}
      if(dXfZnVGhNV == true){dXfZnVGhNV = false;}
      if(PgWjKasyPC == true){PgWjKasyPC = false;}
      if(QuMDwQRsua == true){QuMDwQRsua = false;}
      if(tPfmtnCXwu == true){tPfmtnCXwu = false;}
      if(SGrJVpQkfK == true){SGrJVpQkfK = false;}
      if(zyejriKccW == true){zyejriKccW = false;}
      if(DNmlazBjoW == true){DNmlazBjoW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLVCJURUBM
{ 
  void eEcHiRtLPd()
  { 
      bool pezuUfNLeq = false;
      bool qlEZTWhded = false;
      bool bPlFgWJyEx = false;
      bool TpIRiNMdWy = false;
      bool wlNyHrgwQB = false;
      bool FxgwOZrsOx = false;
      bool VOGhXBclpF = false;
      bool JDGfgpCnyo = false;
      bool oNhCqWIMCJ = false;
      bool VSPZbgefZF = false;
      bool OtFKqCpBPY = false;
      bool WDtYHIgDpB = false;
      bool sQjgjpmgEz = false;
      bool KWOsZtHWLo = false;
      bool fHxdlRYqRS = false;
      bool zboXLyKXZA = false;
      bool OJwPNAoBzM = false;
      bool AKrBUlTFuS = false;
      bool RwOkzigpga = false;
      bool jjwKZWKgQk = false;
      string xoUbgRzcOk;
      string OPCyehawlH;
      string FaRLUBXGkW;
      string VkWrxoVJye;
      string FUPLGKfmNZ;
      string QlyBgVWJHf;
      string ssqqPcsKAp;
      string MRyHCkKFEJ;
      string UkrKGimULa;
      string RLBRlLcYwc;
      string RUlXNznpzw;
      string KRExKHAfjf;
      string pXzYYAPfVp;
      string HkIbrzyUxH;
      string uwVPQzHEGd;
      string LwnPlsVMzM;
      string iHUJnYIbEL;
      string IeicktCjIY;
      string sLZqdKxrpy;
      string dlVjYmaMaq;
      if(xoUbgRzcOk == RUlXNznpzw){pezuUfNLeq = true;}
      else if(RUlXNznpzw == xoUbgRzcOk){OtFKqCpBPY = true;}
      if(OPCyehawlH == KRExKHAfjf){qlEZTWhded = true;}
      else if(KRExKHAfjf == OPCyehawlH){WDtYHIgDpB = true;}
      if(FaRLUBXGkW == pXzYYAPfVp){bPlFgWJyEx = true;}
      else if(pXzYYAPfVp == FaRLUBXGkW){sQjgjpmgEz = true;}
      if(VkWrxoVJye == HkIbrzyUxH){TpIRiNMdWy = true;}
      else if(HkIbrzyUxH == VkWrxoVJye){KWOsZtHWLo = true;}
      if(FUPLGKfmNZ == uwVPQzHEGd){wlNyHrgwQB = true;}
      else if(uwVPQzHEGd == FUPLGKfmNZ){fHxdlRYqRS = true;}
      if(QlyBgVWJHf == LwnPlsVMzM){FxgwOZrsOx = true;}
      else if(LwnPlsVMzM == QlyBgVWJHf){zboXLyKXZA = true;}
      if(ssqqPcsKAp == iHUJnYIbEL){VOGhXBclpF = true;}
      else if(iHUJnYIbEL == ssqqPcsKAp){OJwPNAoBzM = true;}
      if(MRyHCkKFEJ == IeicktCjIY){JDGfgpCnyo = true;}
      if(UkrKGimULa == sLZqdKxrpy){oNhCqWIMCJ = true;}
      if(RLBRlLcYwc == dlVjYmaMaq){VSPZbgefZF = true;}
      while(IeicktCjIY == MRyHCkKFEJ){AKrBUlTFuS = true;}
      while(sLZqdKxrpy == sLZqdKxrpy){RwOkzigpga = true;}
      while(dlVjYmaMaq == dlVjYmaMaq){jjwKZWKgQk = true;}
      if(pezuUfNLeq == true){pezuUfNLeq = false;}
      if(qlEZTWhded == true){qlEZTWhded = false;}
      if(bPlFgWJyEx == true){bPlFgWJyEx = false;}
      if(TpIRiNMdWy == true){TpIRiNMdWy = false;}
      if(wlNyHrgwQB == true){wlNyHrgwQB = false;}
      if(FxgwOZrsOx == true){FxgwOZrsOx = false;}
      if(VOGhXBclpF == true){VOGhXBclpF = false;}
      if(JDGfgpCnyo == true){JDGfgpCnyo = false;}
      if(oNhCqWIMCJ == true){oNhCqWIMCJ = false;}
      if(VSPZbgefZF == true){VSPZbgefZF = false;}
      if(OtFKqCpBPY == true){OtFKqCpBPY = false;}
      if(WDtYHIgDpB == true){WDtYHIgDpB = false;}
      if(sQjgjpmgEz == true){sQjgjpmgEz = false;}
      if(KWOsZtHWLo == true){KWOsZtHWLo = false;}
      if(fHxdlRYqRS == true){fHxdlRYqRS = false;}
      if(zboXLyKXZA == true){zboXLyKXZA = false;}
      if(OJwPNAoBzM == true){OJwPNAoBzM = false;}
      if(AKrBUlTFuS == true){AKrBUlTFuS = false;}
      if(RwOkzigpga == true){RwOkzigpga = false;}
      if(jjwKZWKgQk == true){jjwKZWKgQk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEEDMNFPIG
{ 
  void GbXXnhTbaj()
  { 
      bool pkkcyKXGTO = false;
      bool TmIqYldhfn = false;
      bool BgMnKoaNPH = false;
      bool WKLsJYpQeS = false;
      bool WYqtQbUnbT = false;
      bool QEFLPJYxSI = false;
      bool iJqLrIaOgz = false;
      bool uNCMQboRWh = false;
      bool UmluqREAdA = false;
      bool AsxVjMheBH = false;
      bool AGGbYCBstm = false;
      bool TGZjnuXwUZ = false;
      bool DajgzBQgcE = false;
      bool tJQPgOgJVn = false;
      bool QLGpftTMgn = false;
      bool okKaDZVZcW = false;
      bool lTPpsJoKDZ = false;
      bool OOZfJrTsBE = false;
      bool hDznOIzoLG = false;
      bool sHfzCwuQxV = false;
      string YiGqjgCrBI;
      string rjVBJulZsR;
      string lHftIpuXJo;
      string yjseFNURlS;
      string aTeDkziXXZ;
      string UJgtgRDLit;
      string leiLKIqpwu;
      string ZUnaqRbbJJ;
      string GWAjUnCzxn;
      string KIiqfwkTsc;
      string IrabzzUFDO;
      string oaCYnOeyqV;
      string FqsIjQkxtt;
      string gIigANwXjU;
      string SxuhyiGJDR;
      string RlcWWQySri;
      string OXKJhgrVXZ;
      string SGOVCIwLKA;
      string JbscctfLJj;
      string PceAGullzQ;
      if(YiGqjgCrBI == IrabzzUFDO){pkkcyKXGTO = true;}
      else if(IrabzzUFDO == YiGqjgCrBI){AGGbYCBstm = true;}
      if(rjVBJulZsR == oaCYnOeyqV){TmIqYldhfn = true;}
      else if(oaCYnOeyqV == rjVBJulZsR){TGZjnuXwUZ = true;}
      if(lHftIpuXJo == FqsIjQkxtt){BgMnKoaNPH = true;}
      else if(FqsIjQkxtt == lHftIpuXJo){DajgzBQgcE = true;}
      if(yjseFNURlS == gIigANwXjU){WKLsJYpQeS = true;}
      else if(gIigANwXjU == yjseFNURlS){tJQPgOgJVn = true;}
      if(aTeDkziXXZ == SxuhyiGJDR){WYqtQbUnbT = true;}
      else if(SxuhyiGJDR == aTeDkziXXZ){QLGpftTMgn = true;}
      if(UJgtgRDLit == RlcWWQySri){QEFLPJYxSI = true;}
      else if(RlcWWQySri == UJgtgRDLit){okKaDZVZcW = true;}
      if(leiLKIqpwu == OXKJhgrVXZ){iJqLrIaOgz = true;}
      else if(OXKJhgrVXZ == leiLKIqpwu){lTPpsJoKDZ = true;}
      if(ZUnaqRbbJJ == SGOVCIwLKA){uNCMQboRWh = true;}
      if(GWAjUnCzxn == JbscctfLJj){UmluqREAdA = true;}
      if(KIiqfwkTsc == PceAGullzQ){AsxVjMheBH = true;}
      while(SGOVCIwLKA == ZUnaqRbbJJ){OOZfJrTsBE = true;}
      while(JbscctfLJj == JbscctfLJj){hDznOIzoLG = true;}
      while(PceAGullzQ == PceAGullzQ){sHfzCwuQxV = true;}
      if(pkkcyKXGTO == true){pkkcyKXGTO = false;}
      if(TmIqYldhfn == true){TmIqYldhfn = false;}
      if(BgMnKoaNPH == true){BgMnKoaNPH = false;}
      if(WKLsJYpQeS == true){WKLsJYpQeS = false;}
      if(WYqtQbUnbT == true){WYqtQbUnbT = false;}
      if(QEFLPJYxSI == true){QEFLPJYxSI = false;}
      if(iJqLrIaOgz == true){iJqLrIaOgz = false;}
      if(uNCMQboRWh == true){uNCMQboRWh = false;}
      if(UmluqREAdA == true){UmluqREAdA = false;}
      if(AsxVjMheBH == true){AsxVjMheBH = false;}
      if(AGGbYCBstm == true){AGGbYCBstm = false;}
      if(TGZjnuXwUZ == true){TGZjnuXwUZ = false;}
      if(DajgzBQgcE == true){DajgzBQgcE = false;}
      if(tJQPgOgJVn == true){tJQPgOgJVn = false;}
      if(QLGpftTMgn == true){QLGpftTMgn = false;}
      if(okKaDZVZcW == true){okKaDZVZcW = false;}
      if(lTPpsJoKDZ == true){lTPpsJoKDZ = false;}
      if(OOZfJrTsBE == true){OOZfJrTsBE = false;}
      if(hDznOIzoLG == true){hDznOIzoLG = false;}
      if(sHfzCwuQxV == true){sHfzCwuQxV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NITXAYSHVE
{ 
  void kgSJxqCtpe()
  { 
      bool ADDZGDYiNp = false;
      bool jhugdgSpwl = false;
      bool zXwBHlENcz = false;
      bool IoTHgwbOdo = false;
      bool bNfrbBSnqL = false;
      bool gLbLHbHBSU = false;
      bool zKGOguNmzg = false;
      bool EELHKkqEZF = false;
      bool TQVQRxNIzE = false;
      bool nZuJpQGRKf = false;
      bool menKHbzUBW = false;
      bool kDaMBhopwi = false;
      bool hEmtsdJCQs = false;
      bool dZstSnbLJo = false;
      bool yrHcTkzhHH = false;
      bool bQVbyhqtRc = false;
      bool SwDHrKJgtM = false;
      bool GdfGkoxKaH = false;
      bool ebtJRNERuj = false;
      bool whtfWBozkI = false;
      string qkPPtXKuEH;
      string ExQJpDhySD;
      string jHfiJfADAM;
      string daudmxauDz;
      string skXAPZqzGo;
      string xHiVuiFfGN;
      string WGtqddBlWr;
      string cmuSJzieTi;
      string nAxLPVrZhD;
      string rtopbmpgWl;
      string YEcNMKMQLw;
      string zZMXZWJhaI;
      string kaESzhxFpW;
      string ICIhJiXizF;
      string IaNlDRhRQF;
      string dHFNAxAJOd;
      string MHZomwRdNp;
      string zZiVAJNSOg;
      string AfnjsAxthL;
      string iNUVsABXyH;
      if(qkPPtXKuEH == YEcNMKMQLw){ADDZGDYiNp = true;}
      else if(YEcNMKMQLw == qkPPtXKuEH){menKHbzUBW = true;}
      if(ExQJpDhySD == zZMXZWJhaI){jhugdgSpwl = true;}
      else if(zZMXZWJhaI == ExQJpDhySD){kDaMBhopwi = true;}
      if(jHfiJfADAM == kaESzhxFpW){zXwBHlENcz = true;}
      else if(kaESzhxFpW == jHfiJfADAM){hEmtsdJCQs = true;}
      if(daudmxauDz == ICIhJiXizF){IoTHgwbOdo = true;}
      else if(ICIhJiXizF == daudmxauDz){dZstSnbLJo = true;}
      if(skXAPZqzGo == IaNlDRhRQF){bNfrbBSnqL = true;}
      else if(IaNlDRhRQF == skXAPZqzGo){yrHcTkzhHH = true;}
      if(xHiVuiFfGN == dHFNAxAJOd){gLbLHbHBSU = true;}
      else if(dHFNAxAJOd == xHiVuiFfGN){bQVbyhqtRc = true;}
      if(WGtqddBlWr == MHZomwRdNp){zKGOguNmzg = true;}
      else if(MHZomwRdNp == WGtqddBlWr){SwDHrKJgtM = true;}
      if(cmuSJzieTi == zZiVAJNSOg){EELHKkqEZF = true;}
      if(nAxLPVrZhD == AfnjsAxthL){TQVQRxNIzE = true;}
      if(rtopbmpgWl == iNUVsABXyH){nZuJpQGRKf = true;}
      while(zZiVAJNSOg == cmuSJzieTi){GdfGkoxKaH = true;}
      while(AfnjsAxthL == AfnjsAxthL){ebtJRNERuj = true;}
      while(iNUVsABXyH == iNUVsABXyH){whtfWBozkI = true;}
      if(ADDZGDYiNp == true){ADDZGDYiNp = false;}
      if(jhugdgSpwl == true){jhugdgSpwl = false;}
      if(zXwBHlENcz == true){zXwBHlENcz = false;}
      if(IoTHgwbOdo == true){IoTHgwbOdo = false;}
      if(bNfrbBSnqL == true){bNfrbBSnqL = false;}
      if(gLbLHbHBSU == true){gLbLHbHBSU = false;}
      if(zKGOguNmzg == true){zKGOguNmzg = false;}
      if(EELHKkqEZF == true){EELHKkqEZF = false;}
      if(TQVQRxNIzE == true){TQVQRxNIzE = false;}
      if(nZuJpQGRKf == true){nZuJpQGRKf = false;}
      if(menKHbzUBW == true){menKHbzUBW = false;}
      if(kDaMBhopwi == true){kDaMBhopwi = false;}
      if(hEmtsdJCQs == true){hEmtsdJCQs = false;}
      if(dZstSnbLJo == true){dZstSnbLJo = false;}
      if(yrHcTkzhHH == true){yrHcTkzhHH = false;}
      if(bQVbyhqtRc == true){bQVbyhqtRc = false;}
      if(SwDHrKJgtM == true){SwDHrKJgtM = false;}
      if(GdfGkoxKaH == true){GdfGkoxKaH = false;}
      if(ebtJRNERuj == true){ebtJRNERuj = false;}
      if(whtfWBozkI == true){whtfWBozkI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHFAULLMDP
{ 
  void EmmnsJUomx()
  { 
      bool VChLtrdbqC = false;
      bool TluWnIpZjO = false;
      bool WPMsKoFmhz = false;
      bool bOVStlbdNd = false;
      bool IjAJtcYquP = false;
      bool cRMzLFpoAE = false;
      bool mptqaFPbbC = false;
      bool fMLGFlPCyh = false;
      bool QNrSWKCWHo = false;
      bool wmcJpSpIio = false;
      bool MwOriQFFsZ = false;
      bool pmpSnZxaUQ = false;
      bool DsUmGsiCQm = false;
      bool uGSIUTyAiF = false;
      bool EwdgyIwKUQ = false;
      bool UOnSlTablp = false;
      bool hCoFdjTgyT = false;
      bool axrPLGPmnx = false;
      bool wYgzSfSAWA = false;
      bool rVNsXCHXDO = false;
      string fqXmGWHxmh;
      string OHVVSohChG;
      string CWwTsjNBEb;
      string BEzRFjnmXo;
      string odsNXDafQw;
      string PolGNItDsW;
      string JGrLgKHEPi;
      string BtdrRYdiup;
      string JgjHMLSrEx;
      string ojsAfikhfN;
      string uWPhuUKsoo;
      string eLHDNbVjyU;
      string rOzStRBcLh;
      string muDhulRCMr;
      string BYDPRdbpmE;
      string MAiKVfWwmc;
      string TggGBiIZIa;
      string KTWGTSLjBQ;
      string oKpHVlMrMO;
      string PUOiXTqxNh;
      if(fqXmGWHxmh == uWPhuUKsoo){VChLtrdbqC = true;}
      else if(uWPhuUKsoo == fqXmGWHxmh){MwOriQFFsZ = true;}
      if(OHVVSohChG == eLHDNbVjyU){TluWnIpZjO = true;}
      else if(eLHDNbVjyU == OHVVSohChG){pmpSnZxaUQ = true;}
      if(CWwTsjNBEb == rOzStRBcLh){WPMsKoFmhz = true;}
      else if(rOzStRBcLh == CWwTsjNBEb){DsUmGsiCQm = true;}
      if(BEzRFjnmXo == muDhulRCMr){bOVStlbdNd = true;}
      else if(muDhulRCMr == BEzRFjnmXo){uGSIUTyAiF = true;}
      if(odsNXDafQw == BYDPRdbpmE){IjAJtcYquP = true;}
      else if(BYDPRdbpmE == odsNXDafQw){EwdgyIwKUQ = true;}
      if(PolGNItDsW == MAiKVfWwmc){cRMzLFpoAE = true;}
      else if(MAiKVfWwmc == PolGNItDsW){UOnSlTablp = true;}
      if(JGrLgKHEPi == TggGBiIZIa){mptqaFPbbC = true;}
      else if(TggGBiIZIa == JGrLgKHEPi){hCoFdjTgyT = true;}
      if(BtdrRYdiup == KTWGTSLjBQ){fMLGFlPCyh = true;}
      if(JgjHMLSrEx == oKpHVlMrMO){QNrSWKCWHo = true;}
      if(ojsAfikhfN == PUOiXTqxNh){wmcJpSpIio = true;}
      while(KTWGTSLjBQ == BtdrRYdiup){axrPLGPmnx = true;}
      while(oKpHVlMrMO == oKpHVlMrMO){wYgzSfSAWA = true;}
      while(PUOiXTqxNh == PUOiXTqxNh){rVNsXCHXDO = true;}
      if(VChLtrdbqC == true){VChLtrdbqC = false;}
      if(TluWnIpZjO == true){TluWnIpZjO = false;}
      if(WPMsKoFmhz == true){WPMsKoFmhz = false;}
      if(bOVStlbdNd == true){bOVStlbdNd = false;}
      if(IjAJtcYquP == true){IjAJtcYquP = false;}
      if(cRMzLFpoAE == true){cRMzLFpoAE = false;}
      if(mptqaFPbbC == true){mptqaFPbbC = false;}
      if(fMLGFlPCyh == true){fMLGFlPCyh = false;}
      if(QNrSWKCWHo == true){QNrSWKCWHo = false;}
      if(wmcJpSpIio == true){wmcJpSpIio = false;}
      if(MwOriQFFsZ == true){MwOriQFFsZ = false;}
      if(pmpSnZxaUQ == true){pmpSnZxaUQ = false;}
      if(DsUmGsiCQm == true){DsUmGsiCQm = false;}
      if(uGSIUTyAiF == true){uGSIUTyAiF = false;}
      if(EwdgyIwKUQ == true){EwdgyIwKUQ = false;}
      if(UOnSlTablp == true){UOnSlTablp = false;}
      if(hCoFdjTgyT == true){hCoFdjTgyT = false;}
      if(axrPLGPmnx == true){axrPLGPmnx = false;}
      if(wYgzSfSAWA == true){wYgzSfSAWA = false;}
      if(rVNsXCHXDO == true){rVNsXCHXDO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFMWUCYXDY
{ 
  void JrSJToUwUm()
  { 
      bool tYyqxilMwi = false;
      bool ZRldGxoIce = false;
      bool nzPHzteBWQ = false;
      bool jyNdYEhAJl = false;
      bool dDBVMAmtse = false;
      bool brsSztJpqC = false;
      bool EjoezbEHFB = false;
      bool OnzqAjxsuz = false;
      bool HjHroqFued = false;
      bool tqIGgtNWWk = false;
      bool wenqQmsBRO = false;
      bool xPurtTbwoH = false;
      bool VIbaGWfrJG = false;
      bool VaWKCbuPbC = false;
      bool yDdQgewPMN = false;
      bool RRgOOnDNks = false;
      bool GArKrWrkpR = false;
      bool XMUmISdKtb = false;
      bool ZQfuoEsHwO = false;
      bool YhehwxLTYK = false;
      string wQNPIQRqZE;
      string oRSYFqNAlh;
      string dYFYTMfONK;
      string shBUtcdRWz;
      string OCfTdBgqkV;
      string AMbZbXLouu;
      string kDcOLHQyec;
      string MwclTbrktS;
      string fodrJfFasV;
      string RnVaNLYQIV;
      string jiLIIEioGz;
      string eZtcPwYkEe;
      string BoEIKXZCYH;
      string DbbYhxcVjF;
      string xQUsqqtsKR;
      string lmLdTudDxj;
      string dfPyuDxUtS;
      string TDBzhjULRS;
      string dgqHUQPyFm;
      string SYYzbQAVxm;
      if(wQNPIQRqZE == jiLIIEioGz){tYyqxilMwi = true;}
      else if(jiLIIEioGz == wQNPIQRqZE){wenqQmsBRO = true;}
      if(oRSYFqNAlh == eZtcPwYkEe){ZRldGxoIce = true;}
      else if(eZtcPwYkEe == oRSYFqNAlh){xPurtTbwoH = true;}
      if(dYFYTMfONK == BoEIKXZCYH){nzPHzteBWQ = true;}
      else if(BoEIKXZCYH == dYFYTMfONK){VIbaGWfrJG = true;}
      if(shBUtcdRWz == DbbYhxcVjF){jyNdYEhAJl = true;}
      else if(DbbYhxcVjF == shBUtcdRWz){VaWKCbuPbC = true;}
      if(OCfTdBgqkV == xQUsqqtsKR){dDBVMAmtse = true;}
      else if(xQUsqqtsKR == OCfTdBgqkV){yDdQgewPMN = true;}
      if(AMbZbXLouu == lmLdTudDxj){brsSztJpqC = true;}
      else if(lmLdTudDxj == AMbZbXLouu){RRgOOnDNks = true;}
      if(kDcOLHQyec == dfPyuDxUtS){EjoezbEHFB = true;}
      else if(dfPyuDxUtS == kDcOLHQyec){GArKrWrkpR = true;}
      if(MwclTbrktS == TDBzhjULRS){OnzqAjxsuz = true;}
      if(fodrJfFasV == dgqHUQPyFm){HjHroqFued = true;}
      if(RnVaNLYQIV == SYYzbQAVxm){tqIGgtNWWk = true;}
      while(TDBzhjULRS == MwclTbrktS){XMUmISdKtb = true;}
      while(dgqHUQPyFm == dgqHUQPyFm){ZQfuoEsHwO = true;}
      while(SYYzbQAVxm == SYYzbQAVxm){YhehwxLTYK = true;}
      if(tYyqxilMwi == true){tYyqxilMwi = false;}
      if(ZRldGxoIce == true){ZRldGxoIce = false;}
      if(nzPHzteBWQ == true){nzPHzteBWQ = false;}
      if(jyNdYEhAJl == true){jyNdYEhAJl = false;}
      if(dDBVMAmtse == true){dDBVMAmtse = false;}
      if(brsSztJpqC == true){brsSztJpqC = false;}
      if(EjoezbEHFB == true){EjoezbEHFB = false;}
      if(OnzqAjxsuz == true){OnzqAjxsuz = false;}
      if(HjHroqFued == true){HjHroqFued = false;}
      if(tqIGgtNWWk == true){tqIGgtNWWk = false;}
      if(wenqQmsBRO == true){wenqQmsBRO = false;}
      if(xPurtTbwoH == true){xPurtTbwoH = false;}
      if(VIbaGWfrJG == true){VIbaGWfrJG = false;}
      if(VaWKCbuPbC == true){VaWKCbuPbC = false;}
      if(yDdQgewPMN == true){yDdQgewPMN = false;}
      if(RRgOOnDNks == true){RRgOOnDNks = false;}
      if(GArKrWrkpR == true){GArKrWrkpR = false;}
      if(XMUmISdKtb == true){XMUmISdKtb = false;}
      if(ZQfuoEsHwO == true){ZQfuoEsHwO = false;}
      if(YhehwxLTYK == true){YhehwxLTYK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNNDNMGCEZ
{ 
  void nesrSZzDJQ()
  { 
      bool ozUtQaKOWf = false;
      bool zJkndkPzTZ = false;
      bool rLYTpmVsOY = false;
      bool pUhfBNrHbq = false;
      bool fxuizeAANF = false;
      bool gNMmycaBDc = false;
      bool FRzxoebEmP = false;
      bool rIXbttPoTK = false;
      bool lVfJqcHtgX = false;
      bool mpDykOxxsU = false;
      bool CwMxNYojrE = false;
      bool MkhrpjlpFM = false;
      bool WhWOcBEYqf = false;
      bool xSuzIpIhwS = false;
      bool mXBcKBIKHB = false;
      bool cHqgxUYxTL = false;
      bool TQsMGtohjz = false;
      bool aDtmYyfsDb = false;
      bool rtQoDpaOBn = false;
      bool RKNjzWenWQ = false;
      string lfBKGyqupR;
      string gwwWroIXuS;
      string OBGUUIFGzD;
      string auSoTeJyxD;
      string zLDTczkgAX;
      string LTRJHkZgpx;
      string sjulqkcGDN;
      string eKarTDylqV;
      string XYGbqGdJhi;
      string FcHzJPPQbq;
      string VdcmrBrYpE;
      string lmoTZTdTuj;
      string HTYTIBCahD;
      string mgJAAtuTio;
      string OESdwRnnZp;
      string kwUrjBEIeq;
      string zRqlQEcoSe;
      string YKkFVDBtXp;
      string NNBrSqMRPz;
      string olnqpxMfMq;
      if(lfBKGyqupR == VdcmrBrYpE){ozUtQaKOWf = true;}
      else if(VdcmrBrYpE == lfBKGyqupR){CwMxNYojrE = true;}
      if(gwwWroIXuS == lmoTZTdTuj){zJkndkPzTZ = true;}
      else if(lmoTZTdTuj == gwwWroIXuS){MkhrpjlpFM = true;}
      if(OBGUUIFGzD == HTYTIBCahD){rLYTpmVsOY = true;}
      else if(HTYTIBCahD == OBGUUIFGzD){WhWOcBEYqf = true;}
      if(auSoTeJyxD == mgJAAtuTio){pUhfBNrHbq = true;}
      else if(mgJAAtuTio == auSoTeJyxD){xSuzIpIhwS = true;}
      if(zLDTczkgAX == OESdwRnnZp){fxuizeAANF = true;}
      else if(OESdwRnnZp == zLDTczkgAX){mXBcKBIKHB = true;}
      if(LTRJHkZgpx == kwUrjBEIeq){gNMmycaBDc = true;}
      else if(kwUrjBEIeq == LTRJHkZgpx){cHqgxUYxTL = true;}
      if(sjulqkcGDN == zRqlQEcoSe){FRzxoebEmP = true;}
      else if(zRqlQEcoSe == sjulqkcGDN){TQsMGtohjz = true;}
      if(eKarTDylqV == YKkFVDBtXp){rIXbttPoTK = true;}
      if(XYGbqGdJhi == NNBrSqMRPz){lVfJqcHtgX = true;}
      if(FcHzJPPQbq == olnqpxMfMq){mpDykOxxsU = true;}
      while(YKkFVDBtXp == eKarTDylqV){aDtmYyfsDb = true;}
      while(NNBrSqMRPz == NNBrSqMRPz){rtQoDpaOBn = true;}
      while(olnqpxMfMq == olnqpxMfMq){RKNjzWenWQ = true;}
      if(ozUtQaKOWf == true){ozUtQaKOWf = false;}
      if(zJkndkPzTZ == true){zJkndkPzTZ = false;}
      if(rLYTpmVsOY == true){rLYTpmVsOY = false;}
      if(pUhfBNrHbq == true){pUhfBNrHbq = false;}
      if(fxuizeAANF == true){fxuizeAANF = false;}
      if(gNMmycaBDc == true){gNMmycaBDc = false;}
      if(FRzxoebEmP == true){FRzxoebEmP = false;}
      if(rIXbttPoTK == true){rIXbttPoTK = false;}
      if(lVfJqcHtgX == true){lVfJqcHtgX = false;}
      if(mpDykOxxsU == true){mpDykOxxsU = false;}
      if(CwMxNYojrE == true){CwMxNYojrE = false;}
      if(MkhrpjlpFM == true){MkhrpjlpFM = false;}
      if(WhWOcBEYqf == true){WhWOcBEYqf = false;}
      if(xSuzIpIhwS == true){xSuzIpIhwS = false;}
      if(mXBcKBIKHB == true){mXBcKBIKHB = false;}
      if(cHqgxUYxTL == true){cHqgxUYxTL = false;}
      if(TQsMGtohjz == true){TQsMGtohjz = false;}
      if(aDtmYyfsDb == true){aDtmYyfsDb = false;}
      if(rtQoDpaOBn == true){rtQoDpaOBn = false;}
      if(RKNjzWenWQ == true){RKNjzWenWQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHMZRENNQQ
{ 
  void aCdspqbSdM()
  { 
      bool hVpQkEmUNG = false;
      bool szRiKeMBOh = false;
      bool qsgmQepQfm = false;
      bool OglkhXkWoV = false;
      bool hrgjiCLfyW = false;
      bool itazeooDAF = false;
      bool NWoZrMNgBm = false;
      bool spLsAzMwDO = false;
      bool SKRJETFmFr = false;
      bool ihWjILDGqW = false;
      bool neeLcsihzf = false;
      bool crzklCEeVX = false;
      bool GaaIEKSbjn = false;
      bool uFEgZneGfL = false;
      bool kXmZPphkxF = false;
      bool GYkTPNDWHS = false;
      bool ZGxKjWmSLy = false;
      bool XyyJmhmArN = false;
      bool chddgWUkQL = false;
      bool kIzNldacps = false;
      string OzOxqTBDNm;
      string yBkExkUDDO;
      string dkxUgGweLc;
      string mrtCZFVbIc;
      string AscbIXJldH;
      string gSWoZdBtPj;
      string WVrkzFGidq;
      string PsuZOkIUMI;
      string wKBEuTVFbw;
      string EbLXFdBrcC;
      string RaHmqnXwZo;
      string UghGnMTmoe;
      string jBHhmmgWTj;
      string jQrJqVDOMH;
      string wYemaWtFis;
      string JNCxSPTYzD;
      string GAboEEnXOS;
      string IFZgiLWTHQ;
      string sbnaZVNuqb;
      string BdOJBuwphV;
      if(OzOxqTBDNm == RaHmqnXwZo){hVpQkEmUNG = true;}
      else if(RaHmqnXwZo == OzOxqTBDNm){neeLcsihzf = true;}
      if(yBkExkUDDO == UghGnMTmoe){szRiKeMBOh = true;}
      else if(UghGnMTmoe == yBkExkUDDO){crzklCEeVX = true;}
      if(dkxUgGweLc == jBHhmmgWTj){qsgmQepQfm = true;}
      else if(jBHhmmgWTj == dkxUgGweLc){GaaIEKSbjn = true;}
      if(mrtCZFVbIc == jQrJqVDOMH){OglkhXkWoV = true;}
      else if(jQrJqVDOMH == mrtCZFVbIc){uFEgZneGfL = true;}
      if(AscbIXJldH == wYemaWtFis){hrgjiCLfyW = true;}
      else if(wYemaWtFis == AscbIXJldH){kXmZPphkxF = true;}
      if(gSWoZdBtPj == JNCxSPTYzD){itazeooDAF = true;}
      else if(JNCxSPTYzD == gSWoZdBtPj){GYkTPNDWHS = true;}
      if(WVrkzFGidq == GAboEEnXOS){NWoZrMNgBm = true;}
      else if(GAboEEnXOS == WVrkzFGidq){ZGxKjWmSLy = true;}
      if(PsuZOkIUMI == IFZgiLWTHQ){spLsAzMwDO = true;}
      if(wKBEuTVFbw == sbnaZVNuqb){SKRJETFmFr = true;}
      if(EbLXFdBrcC == BdOJBuwphV){ihWjILDGqW = true;}
      while(IFZgiLWTHQ == PsuZOkIUMI){XyyJmhmArN = true;}
      while(sbnaZVNuqb == sbnaZVNuqb){chddgWUkQL = true;}
      while(BdOJBuwphV == BdOJBuwphV){kIzNldacps = true;}
      if(hVpQkEmUNG == true){hVpQkEmUNG = false;}
      if(szRiKeMBOh == true){szRiKeMBOh = false;}
      if(qsgmQepQfm == true){qsgmQepQfm = false;}
      if(OglkhXkWoV == true){OglkhXkWoV = false;}
      if(hrgjiCLfyW == true){hrgjiCLfyW = false;}
      if(itazeooDAF == true){itazeooDAF = false;}
      if(NWoZrMNgBm == true){NWoZrMNgBm = false;}
      if(spLsAzMwDO == true){spLsAzMwDO = false;}
      if(SKRJETFmFr == true){SKRJETFmFr = false;}
      if(ihWjILDGqW == true){ihWjILDGqW = false;}
      if(neeLcsihzf == true){neeLcsihzf = false;}
      if(crzklCEeVX == true){crzklCEeVX = false;}
      if(GaaIEKSbjn == true){GaaIEKSbjn = false;}
      if(uFEgZneGfL == true){uFEgZneGfL = false;}
      if(kXmZPphkxF == true){kXmZPphkxF = false;}
      if(GYkTPNDWHS == true){GYkTPNDWHS = false;}
      if(ZGxKjWmSLy == true){ZGxKjWmSLy = false;}
      if(XyyJmhmArN == true){XyyJmhmArN = false;}
      if(chddgWUkQL == true){chddgWUkQL = false;}
      if(kIzNldacps == true){kIzNldacps = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WITYBXLHNG
{ 
  void kqQUMqZALo()
  { 
      bool ysJVNCfFNc = false;
      bool GDcNUZIUWf = false;
      bool DkyNUUmyes = false;
      bool oDxSpSNNnw = false;
      bool WHVfAwuugc = false;
      bool TxDkGMtuBr = false;
      bool PhZTmCGKWB = false;
      bool LtfZJwOSMX = false;
      bool YqRCZqzLMc = false;
      bool YRMugogBsx = false;
      bool pkYeQYRdbK = false;
      bool xbhcSYPXtw = false;
      bool DtyscthjsU = false;
      bool OMYPhnRmkA = false;
      bool ZVjCewiicI = false;
      bool YIHxtumeBW = false;
      bool qgkHukCSue = false;
      bool GcmsVhKwNf = false;
      bool KzHjuGFbUm = false;
      bool BmkNJrkcGt = false;
      string dSxcBOVFlj;
      string NlamurIPno;
      string gjpXKQzrpA;
      string HurpnhbLMw;
      string jfJAyGRJWL;
      string yUYZUscZSk;
      string PcOlbSskyM;
      string PxCqEBZpYE;
      string ypVeClVRUt;
      string FCsbgGQXXf;
      string MgKJuBSgUT;
      string TlANlZHjio;
      string wbPEHNDZKy;
      string jCRsrReLiA;
      string ToxBaSBfpH;
      string ygnijkRGCh;
      string xrWWjQUHVT;
      string twAiUHdOco;
      string MXjCzDNiIH;
      string zYJBDbRaRJ;
      if(dSxcBOVFlj == MgKJuBSgUT){ysJVNCfFNc = true;}
      else if(MgKJuBSgUT == dSxcBOVFlj){pkYeQYRdbK = true;}
      if(NlamurIPno == TlANlZHjio){GDcNUZIUWf = true;}
      else if(TlANlZHjio == NlamurIPno){xbhcSYPXtw = true;}
      if(gjpXKQzrpA == wbPEHNDZKy){DkyNUUmyes = true;}
      else if(wbPEHNDZKy == gjpXKQzrpA){DtyscthjsU = true;}
      if(HurpnhbLMw == jCRsrReLiA){oDxSpSNNnw = true;}
      else if(jCRsrReLiA == HurpnhbLMw){OMYPhnRmkA = true;}
      if(jfJAyGRJWL == ToxBaSBfpH){WHVfAwuugc = true;}
      else if(ToxBaSBfpH == jfJAyGRJWL){ZVjCewiicI = true;}
      if(yUYZUscZSk == ygnijkRGCh){TxDkGMtuBr = true;}
      else if(ygnijkRGCh == yUYZUscZSk){YIHxtumeBW = true;}
      if(PcOlbSskyM == xrWWjQUHVT){PhZTmCGKWB = true;}
      else if(xrWWjQUHVT == PcOlbSskyM){qgkHukCSue = true;}
      if(PxCqEBZpYE == twAiUHdOco){LtfZJwOSMX = true;}
      if(ypVeClVRUt == MXjCzDNiIH){YqRCZqzLMc = true;}
      if(FCsbgGQXXf == zYJBDbRaRJ){YRMugogBsx = true;}
      while(twAiUHdOco == PxCqEBZpYE){GcmsVhKwNf = true;}
      while(MXjCzDNiIH == MXjCzDNiIH){KzHjuGFbUm = true;}
      while(zYJBDbRaRJ == zYJBDbRaRJ){BmkNJrkcGt = true;}
      if(ysJVNCfFNc == true){ysJVNCfFNc = false;}
      if(GDcNUZIUWf == true){GDcNUZIUWf = false;}
      if(DkyNUUmyes == true){DkyNUUmyes = false;}
      if(oDxSpSNNnw == true){oDxSpSNNnw = false;}
      if(WHVfAwuugc == true){WHVfAwuugc = false;}
      if(TxDkGMtuBr == true){TxDkGMtuBr = false;}
      if(PhZTmCGKWB == true){PhZTmCGKWB = false;}
      if(LtfZJwOSMX == true){LtfZJwOSMX = false;}
      if(YqRCZqzLMc == true){YqRCZqzLMc = false;}
      if(YRMugogBsx == true){YRMugogBsx = false;}
      if(pkYeQYRdbK == true){pkYeQYRdbK = false;}
      if(xbhcSYPXtw == true){xbhcSYPXtw = false;}
      if(DtyscthjsU == true){DtyscthjsU = false;}
      if(OMYPhnRmkA == true){OMYPhnRmkA = false;}
      if(ZVjCewiicI == true){ZVjCewiicI = false;}
      if(YIHxtumeBW == true){YIHxtumeBW = false;}
      if(qgkHukCSue == true){qgkHukCSue = false;}
      if(GcmsVhKwNf == true){GcmsVhKwNf = false;}
      if(KzHjuGFbUm == true){KzHjuGFbUm = false;}
      if(BmkNJrkcGt == true){BmkNJrkcGt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJRYMHAVEW
{ 
  void zSWqlMVUaB()
  { 
      bool YxzkApSSqt = false;
      bool TUECIlajMl = false;
      bool ilGiJimQeK = false;
      bool TRFkrllcCU = false;
      bool AEdhGctOmI = false;
      bool siZJCmpPaQ = false;
      bool DBmfaCOSJW = false;
      bool zxgqkdHYbg = false;
      bool oXdWRjqwiF = false;
      bool uVClRzRxGE = false;
      bool NaFQJuBhYX = false;
      bool fRnsaeXPOp = false;
      bool KSjEbcuuZl = false;
      bool LJRXTNSMNW = false;
      bool hJXLZdhIKl = false;
      bool aCiQstqBof = false;
      bool zGIlLVzPZN = false;
      bool MKBqHAuXdx = false;
      bool tmjmLJZBdY = false;
      bool VRXgWbBkzD = false;
      string fbSnBRGinh;
      string GjJOYsbQzi;
      string KKTmpfoHnN;
      string igXxjqEPnV;
      string lbKMABlVBt;
      string dZCdnVIfyU;
      string cyuazYLMdg;
      string nLbdwhzGlo;
      string sSGtiIetIO;
      string hYRTrngjNb;
      string pZqTGRyXhG;
      string VBsIaJrBqp;
      string tQDPzOtHkI;
      string APsKzTalmR;
      string KGMCrgfIsi;
      string wfrWhYVbUq;
      string WpmYGGHiJH;
      string iFNZemEBWR;
      string ikOCLTWVba;
      string xzRwtUTmwk;
      if(fbSnBRGinh == pZqTGRyXhG){YxzkApSSqt = true;}
      else if(pZqTGRyXhG == fbSnBRGinh){NaFQJuBhYX = true;}
      if(GjJOYsbQzi == VBsIaJrBqp){TUECIlajMl = true;}
      else if(VBsIaJrBqp == GjJOYsbQzi){fRnsaeXPOp = true;}
      if(KKTmpfoHnN == tQDPzOtHkI){ilGiJimQeK = true;}
      else if(tQDPzOtHkI == KKTmpfoHnN){KSjEbcuuZl = true;}
      if(igXxjqEPnV == APsKzTalmR){TRFkrllcCU = true;}
      else if(APsKzTalmR == igXxjqEPnV){LJRXTNSMNW = true;}
      if(lbKMABlVBt == KGMCrgfIsi){AEdhGctOmI = true;}
      else if(KGMCrgfIsi == lbKMABlVBt){hJXLZdhIKl = true;}
      if(dZCdnVIfyU == wfrWhYVbUq){siZJCmpPaQ = true;}
      else if(wfrWhYVbUq == dZCdnVIfyU){aCiQstqBof = true;}
      if(cyuazYLMdg == WpmYGGHiJH){DBmfaCOSJW = true;}
      else if(WpmYGGHiJH == cyuazYLMdg){zGIlLVzPZN = true;}
      if(nLbdwhzGlo == iFNZemEBWR){zxgqkdHYbg = true;}
      if(sSGtiIetIO == ikOCLTWVba){oXdWRjqwiF = true;}
      if(hYRTrngjNb == xzRwtUTmwk){uVClRzRxGE = true;}
      while(iFNZemEBWR == nLbdwhzGlo){MKBqHAuXdx = true;}
      while(ikOCLTWVba == ikOCLTWVba){tmjmLJZBdY = true;}
      while(xzRwtUTmwk == xzRwtUTmwk){VRXgWbBkzD = true;}
      if(YxzkApSSqt == true){YxzkApSSqt = false;}
      if(TUECIlajMl == true){TUECIlajMl = false;}
      if(ilGiJimQeK == true){ilGiJimQeK = false;}
      if(TRFkrllcCU == true){TRFkrllcCU = false;}
      if(AEdhGctOmI == true){AEdhGctOmI = false;}
      if(siZJCmpPaQ == true){siZJCmpPaQ = false;}
      if(DBmfaCOSJW == true){DBmfaCOSJW = false;}
      if(zxgqkdHYbg == true){zxgqkdHYbg = false;}
      if(oXdWRjqwiF == true){oXdWRjqwiF = false;}
      if(uVClRzRxGE == true){uVClRzRxGE = false;}
      if(NaFQJuBhYX == true){NaFQJuBhYX = false;}
      if(fRnsaeXPOp == true){fRnsaeXPOp = false;}
      if(KSjEbcuuZl == true){KSjEbcuuZl = false;}
      if(LJRXTNSMNW == true){LJRXTNSMNW = false;}
      if(hJXLZdhIKl == true){hJXLZdhIKl = false;}
      if(aCiQstqBof == true){aCiQstqBof = false;}
      if(zGIlLVzPZN == true){zGIlLVzPZN = false;}
      if(MKBqHAuXdx == true){MKBqHAuXdx = false;}
      if(tmjmLJZBdY == true){tmjmLJZBdY = false;}
      if(VRXgWbBkzD == true){VRXgWbBkzD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBEVFKIKQZ
{ 
  void WjCcEOgncz()
  { 
      bool fRXsQooMZb = false;
      bool UxhslEyHJQ = false;
      bool CQndGwwAyZ = false;
      bool wqJtSxuWqb = false;
      bool ryHhsCqZKl = false;
      bool WdEqHPctlU = false;
      bool soNAecmnZn = false;
      bool JbPgYDIGkE = false;
      bool EVoLCSmRmD = false;
      bool TBjWiCkHCP = false;
      bool ODzVcuNXSD = false;
      bool GWJhQWzBxM = false;
      bool pVBWUIqsxV = false;
      bool SBDUoBWSiH = false;
      bool EPzjwwqBGL = false;
      bool CiKoZsCcBU = false;
      bool EUZwjFSnsO = false;
      bool AgSoIZVRZX = false;
      bool QomkTjqOuw = false;
      bool zsRNDipCzq = false;
      string NDUsKdmzpX;
      string cXjdzYKcwE;
      string EMysGmTXZL;
      string dkqnAmKfrf;
      string yFotiAjrku;
      string mOZEPAFblX;
      string KPYetrgwcM;
      string OdjPFzXDJG;
      string CbleYOKmXA;
      string ghtUVifJAq;
      string TnOYgIeJyQ;
      string bBReUictGe;
      string hsYbefiPtW;
      string SODSmOMNxP;
      string jAnGXeQPzl;
      string FlCUJZOlsA;
      string YOOayNyyqG;
      string VPwpugEREz;
      string OTPHRgLhJN;
      string zZTwqUkNIJ;
      if(NDUsKdmzpX == TnOYgIeJyQ){fRXsQooMZb = true;}
      else if(TnOYgIeJyQ == NDUsKdmzpX){ODzVcuNXSD = true;}
      if(cXjdzYKcwE == bBReUictGe){UxhslEyHJQ = true;}
      else if(bBReUictGe == cXjdzYKcwE){GWJhQWzBxM = true;}
      if(EMysGmTXZL == hsYbefiPtW){CQndGwwAyZ = true;}
      else if(hsYbefiPtW == EMysGmTXZL){pVBWUIqsxV = true;}
      if(dkqnAmKfrf == SODSmOMNxP){wqJtSxuWqb = true;}
      else if(SODSmOMNxP == dkqnAmKfrf){SBDUoBWSiH = true;}
      if(yFotiAjrku == jAnGXeQPzl){ryHhsCqZKl = true;}
      else if(jAnGXeQPzl == yFotiAjrku){EPzjwwqBGL = true;}
      if(mOZEPAFblX == FlCUJZOlsA){WdEqHPctlU = true;}
      else if(FlCUJZOlsA == mOZEPAFblX){CiKoZsCcBU = true;}
      if(KPYetrgwcM == YOOayNyyqG){soNAecmnZn = true;}
      else if(YOOayNyyqG == KPYetrgwcM){EUZwjFSnsO = true;}
      if(OdjPFzXDJG == VPwpugEREz){JbPgYDIGkE = true;}
      if(CbleYOKmXA == OTPHRgLhJN){EVoLCSmRmD = true;}
      if(ghtUVifJAq == zZTwqUkNIJ){TBjWiCkHCP = true;}
      while(VPwpugEREz == OdjPFzXDJG){AgSoIZVRZX = true;}
      while(OTPHRgLhJN == OTPHRgLhJN){QomkTjqOuw = true;}
      while(zZTwqUkNIJ == zZTwqUkNIJ){zsRNDipCzq = true;}
      if(fRXsQooMZb == true){fRXsQooMZb = false;}
      if(UxhslEyHJQ == true){UxhslEyHJQ = false;}
      if(CQndGwwAyZ == true){CQndGwwAyZ = false;}
      if(wqJtSxuWqb == true){wqJtSxuWqb = false;}
      if(ryHhsCqZKl == true){ryHhsCqZKl = false;}
      if(WdEqHPctlU == true){WdEqHPctlU = false;}
      if(soNAecmnZn == true){soNAecmnZn = false;}
      if(JbPgYDIGkE == true){JbPgYDIGkE = false;}
      if(EVoLCSmRmD == true){EVoLCSmRmD = false;}
      if(TBjWiCkHCP == true){TBjWiCkHCP = false;}
      if(ODzVcuNXSD == true){ODzVcuNXSD = false;}
      if(GWJhQWzBxM == true){GWJhQWzBxM = false;}
      if(pVBWUIqsxV == true){pVBWUIqsxV = false;}
      if(SBDUoBWSiH == true){SBDUoBWSiH = false;}
      if(EPzjwwqBGL == true){EPzjwwqBGL = false;}
      if(CiKoZsCcBU == true){CiKoZsCcBU = false;}
      if(EUZwjFSnsO == true){EUZwjFSnsO = false;}
      if(AgSoIZVRZX == true){AgSoIZVRZX = false;}
      if(QomkTjqOuw == true){QomkTjqOuw = false;}
      if(zsRNDipCzq == true){zsRNDipCzq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPKQWDSZNK
{ 
  void ntVFQOdaGh()
  { 
      bool ddssElQnwG = false;
      bool DawCSqIAAX = false;
      bool PTXlUCeEqP = false;
      bool bjxVkSwbGD = false;
      bool yrrdsgnYew = false;
      bool gjfGNJFGXB = false;
      bool HMwgeSdaQA = false;
      bool ugtxZWbsrn = false;
      bool OGZthqEqIa = false;
      bool MoEEuluLza = false;
      bool DNHeBAphgp = false;
      bool hMOjmAlBym = false;
      bool OmSomFcoBm = false;
      bool aPsRjBytsh = false;
      bool BVJRsAaURu = false;
      bool ztNMLQtRru = false;
      bool WAgsPSSwzk = false;
      bool BrIPkrcAwl = false;
      bool eIWGmgCgFT = false;
      bool GfCxKAoPCa = false;
      string ZiifDdtVfl;
      string KWYhAjuXmh;
      string fIOkIAMdtM;
      string UnqknIzAQa;
      string HLmtBknNOi;
      string scaxsRTyXD;
      string QPbTRWentr;
      string jtGMZUUTiW;
      string MyPLSqMsqV;
      string nBcNJrjTcd;
      string GATVyyWOXY;
      string wAOApRzPAZ;
      string KlwXDiRrCh;
      string jAqFQMesMU;
      string UxVSYmmbWq;
      string rTTCTTDuSO;
      string gdMonwJJid;
      string mGCfFMQcyP;
      string woULoPgokx;
      string Ijaynpkfec;
      if(ZiifDdtVfl == GATVyyWOXY){ddssElQnwG = true;}
      else if(GATVyyWOXY == ZiifDdtVfl){DNHeBAphgp = true;}
      if(KWYhAjuXmh == wAOApRzPAZ){DawCSqIAAX = true;}
      else if(wAOApRzPAZ == KWYhAjuXmh){hMOjmAlBym = true;}
      if(fIOkIAMdtM == KlwXDiRrCh){PTXlUCeEqP = true;}
      else if(KlwXDiRrCh == fIOkIAMdtM){OmSomFcoBm = true;}
      if(UnqknIzAQa == jAqFQMesMU){bjxVkSwbGD = true;}
      else if(jAqFQMesMU == UnqknIzAQa){aPsRjBytsh = true;}
      if(HLmtBknNOi == UxVSYmmbWq){yrrdsgnYew = true;}
      else if(UxVSYmmbWq == HLmtBknNOi){BVJRsAaURu = true;}
      if(scaxsRTyXD == rTTCTTDuSO){gjfGNJFGXB = true;}
      else if(rTTCTTDuSO == scaxsRTyXD){ztNMLQtRru = true;}
      if(QPbTRWentr == gdMonwJJid){HMwgeSdaQA = true;}
      else if(gdMonwJJid == QPbTRWentr){WAgsPSSwzk = true;}
      if(jtGMZUUTiW == mGCfFMQcyP){ugtxZWbsrn = true;}
      if(MyPLSqMsqV == woULoPgokx){OGZthqEqIa = true;}
      if(nBcNJrjTcd == Ijaynpkfec){MoEEuluLza = true;}
      while(mGCfFMQcyP == jtGMZUUTiW){BrIPkrcAwl = true;}
      while(woULoPgokx == woULoPgokx){eIWGmgCgFT = true;}
      while(Ijaynpkfec == Ijaynpkfec){GfCxKAoPCa = true;}
      if(ddssElQnwG == true){ddssElQnwG = false;}
      if(DawCSqIAAX == true){DawCSqIAAX = false;}
      if(PTXlUCeEqP == true){PTXlUCeEqP = false;}
      if(bjxVkSwbGD == true){bjxVkSwbGD = false;}
      if(yrrdsgnYew == true){yrrdsgnYew = false;}
      if(gjfGNJFGXB == true){gjfGNJFGXB = false;}
      if(HMwgeSdaQA == true){HMwgeSdaQA = false;}
      if(ugtxZWbsrn == true){ugtxZWbsrn = false;}
      if(OGZthqEqIa == true){OGZthqEqIa = false;}
      if(MoEEuluLza == true){MoEEuluLza = false;}
      if(DNHeBAphgp == true){DNHeBAphgp = false;}
      if(hMOjmAlBym == true){hMOjmAlBym = false;}
      if(OmSomFcoBm == true){OmSomFcoBm = false;}
      if(aPsRjBytsh == true){aPsRjBytsh = false;}
      if(BVJRsAaURu == true){BVJRsAaURu = false;}
      if(ztNMLQtRru == true){ztNMLQtRru = false;}
      if(WAgsPSSwzk == true){WAgsPSSwzk = false;}
      if(BrIPkrcAwl == true){BrIPkrcAwl = false;}
      if(eIWGmgCgFT == true){eIWGmgCgFT = false;}
      if(GfCxKAoPCa == true){GfCxKAoPCa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGPKZESYZQ
{ 
  void CgCQEqZNTb()
  { 
      bool YUQFSJKVZs = false;
      bool qEqWZkNnph = false;
      bool gqQhrPxTaF = false;
      bool GIUQyeVKDK = false;
      bool qNrRXBYJcI = false;
      bool bpllHhEhMC = false;
      bool MpuTlhjaYt = false;
      bool PCkfpTzyKq = false;
      bool pmpRdQViIQ = false;
      bool amxAxBSYfo = false;
      bool RykirYFGwn = false;
      bool hFXVLZAcoV = false;
      bool LBSHTbEjhn = false;
      bool AaSUZrBHYE = false;
      bool KPmThUPbnX = false;
      bool BoiJdQecPQ = false;
      bool TUXHmHmCwT = false;
      bool XrDkKwNyZz = false;
      bool McuKmLrIqJ = false;
      bool MXrIjorefZ = false;
      string zzDEPWzjpT;
      string JLXIfmjEhh;
      string yEirYiAPjP;
      string mPeIttahhR;
      string dgCOygzYlj;
      string ZUwXktPLff;
      string WjAafsfONk;
      string MCVQDQCUtq;
      string iacAoRTHWz;
      string dOBButgbhE;
      string AjLBWXzeTT;
      string ruRnxuGzkN;
      string ZYqNGxAUVI;
      string jaloqyObcQ;
      string SnmDHixNEz;
      string ngpTdbrxtZ;
      string XdJKjRJbxy;
      string gdWTtkknGX;
      string AlQVUCjRLO;
      string FQgCsodcTo;
      if(zzDEPWzjpT == AjLBWXzeTT){YUQFSJKVZs = true;}
      else if(AjLBWXzeTT == zzDEPWzjpT){RykirYFGwn = true;}
      if(JLXIfmjEhh == ruRnxuGzkN){qEqWZkNnph = true;}
      else if(ruRnxuGzkN == JLXIfmjEhh){hFXVLZAcoV = true;}
      if(yEirYiAPjP == ZYqNGxAUVI){gqQhrPxTaF = true;}
      else if(ZYqNGxAUVI == yEirYiAPjP){LBSHTbEjhn = true;}
      if(mPeIttahhR == jaloqyObcQ){GIUQyeVKDK = true;}
      else if(jaloqyObcQ == mPeIttahhR){AaSUZrBHYE = true;}
      if(dgCOygzYlj == SnmDHixNEz){qNrRXBYJcI = true;}
      else if(SnmDHixNEz == dgCOygzYlj){KPmThUPbnX = true;}
      if(ZUwXktPLff == ngpTdbrxtZ){bpllHhEhMC = true;}
      else if(ngpTdbrxtZ == ZUwXktPLff){BoiJdQecPQ = true;}
      if(WjAafsfONk == XdJKjRJbxy){MpuTlhjaYt = true;}
      else if(XdJKjRJbxy == WjAafsfONk){TUXHmHmCwT = true;}
      if(MCVQDQCUtq == gdWTtkknGX){PCkfpTzyKq = true;}
      if(iacAoRTHWz == AlQVUCjRLO){pmpRdQViIQ = true;}
      if(dOBButgbhE == FQgCsodcTo){amxAxBSYfo = true;}
      while(gdWTtkknGX == MCVQDQCUtq){XrDkKwNyZz = true;}
      while(AlQVUCjRLO == AlQVUCjRLO){McuKmLrIqJ = true;}
      while(FQgCsodcTo == FQgCsodcTo){MXrIjorefZ = true;}
      if(YUQFSJKVZs == true){YUQFSJKVZs = false;}
      if(qEqWZkNnph == true){qEqWZkNnph = false;}
      if(gqQhrPxTaF == true){gqQhrPxTaF = false;}
      if(GIUQyeVKDK == true){GIUQyeVKDK = false;}
      if(qNrRXBYJcI == true){qNrRXBYJcI = false;}
      if(bpllHhEhMC == true){bpllHhEhMC = false;}
      if(MpuTlhjaYt == true){MpuTlhjaYt = false;}
      if(PCkfpTzyKq == true){PCkfpTzyKq = false;}
      if(pmpRdQViIQ == true){pmpRdQViIQ = false;}
      if(amxAxBSYfo == true){amxAxBSYfo = false;}
      if(RykirYFGwn == true){RykirYFGwn = false;}
      if(hFXVLZAcoV == true){hFXVLZAcoV = false;}
      if(LBSHTbEjhn == true){LBSHTbEjhn = false;}
      if(AaSUZrBHYE == true){AaSUZrBHYE = false;}
      if(KPmThUPbnX == true){KPmThUPbnX = false;}
      if(BoiJdQecPQ == true){BoiJdQecPQ = false;}
      if(TUXHmHmCwT == true){TUXHmHmCwT = false;}
      if(XrDkKwNyZz == true){XrDkKwNyZz = false;}
      if(McuKmLrIqJ == true){McuKmLrIqJ = false;}
      if(MXrIjorefZ == true){MXrIjorefZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QSJFEJMLRW
{ 
  void mhVnmKccls()
  { 
      bool gUsHbqmKbw = false;
      bool MJOuYbLPEC = false;
      bool dVEgDNYTrN = false;
      bool mGpnNyPNMg = false;
      bool LMEjkptFRf = false;
      bool UkECSKQMEN = false;
      bool STSNIFSZga = false;
      bool MyDXqRRTuN = false;
      bool TSBLrCBmVC = false;
      bool gDIyOqtpbf = false;
      bool WTXqTWhgLA = false;
      bool swQptzRGUG = false;
      bool DfDesJoEJz = false;
      bool WarPqzuKrV = false;
      bool TUbUIklSEO = false;
      bool ZmVVbpPsxK = false;
      bool gcXLcSEBzt = false;
      bool EGOzliDhWI = false;
      bool WWAtZjFWnA = false;
      bool iBNhnpxPqo = false;
      string YaNBoWTtDS;
      string pFtbnnzhPa;
      string YBqPrWytAu;
      string kAwoHWGmjA;
      string FkNLTnMEkz;
      string gKFokXjxJR;
      string XYtIhoJFTR;
      string hMyOVmmeuE;
      string KsJAOZuGDi;
      string mIdRcfqFcd;
      string dGkTRTMpTx;
      string jECEGePstH;
      string sCBkdZhflo;
      string whBQZEIpit;
      string NFmGziGYKx;
      string QxKVjbEAor;
      string lgEdBBCkeC;
      string VYKAtnPukt;
      string SJUnYyXffx;
      string zIAqIfBJFx;
      if(YaNBoWTtDS == dGkTRTMpTx){gUsHbqmKbw = true;}
      else if(dGkTRTMpTx == YaNBoWTtDS){WTXqTWhgLA = true;}
      if(pFtbnnzhPa == jECEGePstH){MJOuYbLPEC = true;}
      else if(jECEGePstH == pFtbnnzhPa){swQptzRGUG = true;}
      if(YBqPrWytAu == sCBkdZhflo){dVEgDNYTrN = true;}
      else if(sCBkdZhflo == YBqPrWytAu){DfDesJoEJz = true;}
      if(kAwoHWGmjA == whBQZEIpit){mGpnNyPNMg = true;}
      else if(whBQZEIpit == kAwoHWGmjA){WarPqzuKrV = true;}
      if(FkNLTnMEkz == NFmGziGYKx){LMEjkptFRf = true;}
      else if(NFmGziGYKx == FkNLTnMEkz){TUbUIklSEO = true;}
      if(gKFokXjxJR == QxKVjbEAor){UkECSKQMEN = true;}
      else if(QxKVjbEAor == gKFokXjxJR){ZmVVbpPsxK = true;}
      if(XYtIhoJFTR == lgEdBBCkeC){STSNIFSZga = true;}
      else if(lgEdBBCkeC == XYtIhoJFTR){gcXLcSEBzt = true;}
      if(hMyOVmmeuE == VYKAtnPukt){MyDXqRRTuN = true;}
      if(KsJAOZuGDi == SJUnYyXffx){TSBLrCBmVC = true;}
      if(mIdRcfqFcd == zIAqIfBJFx){gDIyOqtpbf = true;}
      while(VYKAtnPukt == hMyOVmmeuE){EGOzliDhWI = true;}
      while(SJUnYyXffx == SJUnYyXffx){WWAtZjFWnA = true;}
      while(zIAqIfBJFx == zIAqIfBJFx){iBNhnpxPqo = true;}
      if(gUsHbqmKbw == true){gUsHbqmKbw = false;}
      if(MJOuYbLPEC == true){MJOuYbLPEC = false;}
      if(dVEgDNYTrN == true){dVEgDNYTrN = false;}
      if(mGpnNyPNMg == true){mGpnNyPNMg = false;}
      if(LMEjkptFRf == true){LMEjkptFRf = false;}
      if(UkECSKQMEN == true){UkECSKQMEN = false;}
      if(STSNIFSZga == true){STSNIFSZga = false;}
      if(MyDXqRRTuN == true){MyDXqRRTuN = false;}
      if(TSBLrCBmVC == true){TSBLrCBmVC = false;}
      if(gDIyOqtpbf == true){gDIyOqtpbf = false;}
      if(WTXqTWhgLA == true){WTXqTWhgLA = false;}
      if(swQptzRGUG == true){swQptzRGUG = false;}
      if(DfDesJoEJz == true){DfDesJoEJz = false;}
      if(WarPqzuKrV == true){WarPqzuKrV = false;}
      if(TUbUIklSEO == true){TUbUIklSEO = false;}
      if(ZmVVbpPsxK == true){ZmVVbpPsxK = false;}
      if(gcXLcSEBzt == true){gcXLcSEBzt = false;}
      if(EGOzliDhWI == true){EGOzliDhWI = false;}
      if(WWAtZjFWnA == true){WWAtZjFWnA = false;}
      if(iBNhnpxPqo == true){iBNhnpxPqo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVHJUKOYSU
{ 
  void siQftdAalr()
  { 
      bool EXsJXCEUiC = false;
      bool VOBuMqbbXx = false;
      bool LqVjNZCRJP = false;
      bool VhWNVwLgjz = false;
      bool gsiHJcjXeK = false;
      bool SVTwKNBJux = false;
      bool AlLSfmrnZP = false;
      bool euqXQSHNak = false;
      bool pemzwANZCH = false;
      bool uCklzuhQaV = false;
      bool kuyOeXdwfr = false;
      bool GmhKHVyLVf = false;
      bool ZSkRUcJEYU = false;
      bool kqlFzufXTY = false;
      bool VRsKBHTaec = false;
      bool wVtuuSJgtC = false;
      bool NZWKHPAcKL = false;
      bool oarxJHYaPN = false;
      bool IiYuYOwqJg = false;
      bool kzdQLwuhDl = false;
      string MRCdyeCpKY;
      string HxwYOcbOHN;
      string HCOjUZFncn;
      string KyjqankKQt;
      string zKOhfCdPly;
      string cWoPfJDRJX;
      string ZNNVNJNFxa;
      string rQyMNwngDR;
      string uoBeLnJTLR;
      string kSBrUlxrTW;
      string oYRLGMYbBi;
      string VVNrcjMiKZ;
      string AssfoYPFrb;
      string zuMgbWXpYz;
      string OgScwOEJPj;
      string YOgtVwelVg;
      string xSjZiZJgPF;
      string MVJLLTaQja;
      string UFpICkOSKe;
      string qlTqBuxrtV;
      if(MRCdyeCpKY == oYRLGMYbBi){EXsJXCEUiC = true;}
      else if(oYRLGMYbBi == MRCdyeCpKY){kuyOeXdwfr = true;}
      if(HxwYOcbOHN == VVNrcjMiKZ){VOBuMqbbXx = true;}
      else if(VVNrcjMiKZ == HxwYOcbOHN){GmhKHVyLVf = true;}
      if(HCOjUZFncn == AssfoYPFrb){LqVjNZCRJP = true;}
      else if(AssfoYPFrb == HCOjUZFncn){ZSkRUcJEYU = true;}
      if(KyjqankKQt == zuMgbWXpYz){VhWNVwLgjz = true;}
      else if(zuMgbWXpYz == KyjqankKQt){kqlFzufXTY = true;}
      if(zKOhfCdPly == OgScwOEJPj){gsiHJcjXeK = true;}
      else if(OgScwOEJPj == zKOhfCdPly){VRsKBHTaec = true;}
      if(cWoPfJDRJX == YOgtVwelVg){SVTwKNBJux = true;}
      else if(YOgtVwelVg == cWoPfJDRJX){wVtuuSJgtC = true;}
      if(ZNNVNJNFxa == xSjZiZJgPF){AlLSfmrnZP = true;}
      else if(xSjZiZJgPF == ZNNVNJNFxa){NZWKHPAcKL = true;}
      if(rQyMNwngDR == MVJLLTaQja){euqXQSHNak = true;}
      if(uoBeLnJTLR == UFpICkOSKe){pemzwANZCH = true;}
      if(kSBrUlxrTW == qlTqBuxrtV){uCklzuhQaV = true;}
      while(MVJLLTaQja == rQyMNwngDR){oarxJHYaPN = true;}
      while(UFpICkOSKe == UFpICkOSKe){IiYuYOwqJg = true;}
      while(qlTqBuxrtV == qlTqBuxrtV){kzdQLwuhDl = true;}
      if(EXsJXCEUiC == true){EXsJXCEUiC = false;}
      if(VOBuMqbbXx == true){VOBuMqbbXx = false;}
      if(LqVjNZCRJP == true){LqVjNZCRJP = false;}
      if(VhWNVwLgjz == true){VhWNVwLgjz = false;}
      if(gsiHJcjXeK == true){gsiHJcjXeK = false;}
      if(SVTwKNBJux == true){SVTwKNBJux = false;}
      if(AlLSfmrnZP == true){AlLSfmrnZP = false;}
      if(euqXQSHNak == true){euqXQSHNak = false;}
      if(pemzwANZCH == true){pemzwANZCH = false;}
      if(uCklzuhQaV == true){uCklzuhQaV = false;}
      if(kuyOeXdwfr == true){kuyOeXdwfr = false;}
      if(GmhKHVyLVf == true){GmhKHVyLVf = false;}
      if(ZSkRUcJEYU == true){ZSkRUcJEYU = false;}
      if(kqlFzufXTY == true){kqlFzufXTY = false;}
      if(VRsKBHTaec == true){VRsKBHTaec = false;}
      if(wVtuuSJgtC == true){wVtuuSJgtC = false;}
      if(NZWKHPAcKL == true){NZWKHPAcKL = false;}
      if(oarxJHYaPN == true){oarxJHYaPN = false;}
      if(IiYuYOwqJg == true){IiYuYOwqJg = false;}
      if(kzdQLwuhDl == true){kzdQLwuhDl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JAYRRKFCWF
{ 
  void aRpAVATXkZ()
  { 
      bool TKoXBnznoQ = false;
      bool jwNtlaVjVq = false;
      bool RgtQEsOsaQ = false;
      bool xzeGJLJSrz = false;
      bool NadZRkfSis = false;
      bool NostmmPYTI = false;
      bool YFMYTjRHjZ = false;
      bool RDrWdqCUyS = false;
      bool NwKgCHGjSV = false;
      bool ujziZHNEGh = false;
      bool TYhIbKwVPw = false;
      bool juZAtcteVL = false;
      bool dgnOdhEIxV = false;
      bool cyNQynOCFr = false;
      bool LkUVkAJyow = false;
      bool MiitEmjSdt = false;
      bool GmXsTlgJBF = false;
      bool OrYdArLScd = false;
      bool XFTAIsPTML = false;
      bool EuXLlXMaCz = false;
      string grMLJdfzKQ;
      string FEMtMyWbYf;
      string eXmDCNgJFq;
      string LLehbjVmls;
      string zyuqIMyoAC;
      string PDssLIFJJu;
      string xVsSEsZdRc;
      string cjpeffbuto;
      string OqICbISkWS;
      string dLcpucEclP;
      string mUXWZfMNMf;
      string gJPUfGNqqw;
      string anHyyRGAiD;
      string azJeBtSkcu;
      string wEYqlUuIJo;
      string PNkpnzMZYH;
      string ZMeJEgAkSl;
      string mbOwAWOQLd;
      string VyptmMOTqC;
      string gsMUUiZPlF;
      if(grMLJdfzKQ == mUXWZfMNMf){TKoXBnznoQ = true;}
      else if(mUXWZfMNMf == grMLJdfzKQ){TYhIbKwVPw = true;}
      if(FEMtMyWbYf == gJPUfGNqqw){jwNtlaVjVq = true;}
      else if(gJPUfGNqqw == FEMtMyWbYf){juZAtcteVL = true;}
      if(eXmDCNgJFq == anHyyRGAiD){RgtQEsOsaQ = true;}
      else if(anHyyRGAiD == eXmDCNgJFq){dgnOdhEIxV = true;}
      if(LLehbjVmls == azJeBtSkcu){xzeGJLJSrz = true;}
      else if(azJeBtSkcu == LLehbjVmls){cyNQynOCFr = true;}
      if(zyuqIMyoAC == wEYqlUuIJo){NadZRkfSis = true;}
      else if(wEYqlUuIJo == zyuqIMyoAC){LkUVkAJyow = true;}
      if(PDssLIFJJu == PNkpnzMZYH){NostmmPYTI = true;}
      else if(PNkpnzMZYH == PDssLIFJJu){MiitEmjSdt = true;}
      if(xVsSEsZdRc == ZMeJEgAkSl){YFMYTjRHjZ = true;}
      else if(ZMeJEgAkSl == xVsSEsZdRc){GmXsTlgJBF = true;}
      if(cjpeffbuto == mbOwAWOQLd){RDrWdqCUyS = true;}
      if(OqICbISkWS == VyptmMOTqC){NwKgCHGjSV = true;}
      if(dLcpucEclP == gsMUUiZPlF){ujziZHNEGh = true;}
      while(mbOwAWOQLd == cjpeffbuto){OrYdArLScd = true;}
      while(VyptmMOTqC == VyptmMOTqC){XFTAIsPTML = true;}
      while(gsMUUiZPlF == gsMUUiZPlF){EuXLlXMaCz = true;}
      if(TKoXBnznoQ == true){TKoXBnznoQ = false;}
      if(jwNtlaVjVq == true){jwNtlaVjVq = false;}
      if(RgtQEsOsaQ == true){RgtQEsOsaQ = false;}
      if(xzeGJLJSrz == true){xzeGJLJSrz = false;}
      if(NadZRkfSis == true){NadZRkfSis = false;}
      if(NostmmPYTI == true){NostmmPYTI = false;}
      if(YFMYTjRHjZ == true){YFMYTjRHjZ = false;}
      if(RDrWdqCUyS == true){RDrWdqCUyS = false;}
      if(NwKgCHGjSV == true){NwKgCHGjSV = false;}
      if(ujziZHNEGh == true){ujziZHNEGh = false;}
      if(TYhIbKwVPw == true){TYhIbKwVPw = false;}
      if(juZAtcteVL == true){juZAtcteVL = false;}
      if(dgnOdhEIxV == true){dgnOdhEIxV = false;}
      if(cyNQynOCFr == true){cyNQynOCFr = false;}
      if(LkUVkAJyow == true){LkUVkAJyow = false;}
      if(MiitEmjSdt == true){MiitEmjSdt = false;}
      if(GmXsTlgJBF == true){GmXsTlgJBF = false;}
      if(OrYdArLScd == true){OrYdArLScd = false;}
      if(XFTAIsPTML == true){XFTAIsPTML = false;}
      if(EuXLlXMaCz == true){EuXLlXMaCz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WBNKLUEMFA
{ 
  void bZxfoaaqwx()
  { 
      bool oHUnWFItwM = false;
      bool IzrDoLzDXs = false;
      bool tjhwrrsYep = false;
      bool jFrTGUfShe = false;
      bool OrKIzWTMDo = false;
      bool fizHtEYYwd = false;
      bool MiPFcDHYwU = false;
      bool fgVseBZZwV = false;
      bool YfUoKAFjYB = false;
      bool uGWDSfcFew = false;
      bool OtQiIzNGcs = false;
      bool ezbaFfNZuc = false;
      bool xWAuZYJRay = false;
      bool YUuAGdPlfK = false;
      bool lzHfWweuxl = false;
      bool RCJCyqtVJi = false;
      bool ouedTKDaTb = false;
      bool QbsjpyPTXc = false;
      bool tOUngVKsBO = false;
      bool itcxVpTdLL = false;
      string hLRVTaLdch;
      string imrsosEXTw;
      string DCtCjUStgh;
      string QmnyxPjIfy;
      string GARsxuzaCP;
      string gKGyRfROlz;
      string HRwuQwzswZ;
      string IuqUoCkBFo;
      string VqrRAGfogR;
      string xUVgpoEWbA;
      string uFebGlSlIO;
      string uQIxdPZduJ;
      string QJLecnYKdA;
      string xOYFsPMPLN;
      string ntgSVgLYCZ;
      string PaaRjksAzR;
      string MHHIQgqDDO;
      string DJSgVWcsIu;
      string cAHEjWmGVH;
      string VLQsBflXBo;
      if(hLRVTaLdch == uFebGlSlIO){oHUnWFItwM = true;}
      else if(uFebGlSlIO == hLRVTaLdch){OtQiIzNGcs = true;}
      if(imrsosEXTw == uQIxdPZduJ){IzrDoLzDXs = true;}
      else if(uQIxdPZduJ == imrsosEXTw){ezbaFfNZuc = true;}
      if(DCtCjUStgh == QJLecnYKdA){tjhwrrsYep = true;}
      else if(QJLecnYKdA == DCtCjUStgh){xWAuZYJRay = true;}
      if(QmnyxPjIfy == xOYFsPMPLN){jFrTGUfShe = true;}
      else if(xOYFsPMPLN == QmnyxPjIfy){YUuAGdPlfK = true;}
      if(GARsxuzaCP == ntgSVgLYCZ){OrKIzWTMDo = true;}
      else if(ntgSVgLYCZ == GARsxuzaCP){lzHfWweuxl = true;}
      if(gKGyRfROlz == PaaRjksAzR){fizHtEYYwd = true;}
      else if(PaaRjksAzR == gKGyRfROlz){RCJCyqtVJi = true;}
      if(HRwuQwzswZ == MHHIQgqDDO){MiPFcDHYwU = true;}
      else if(MHHIQgqDDO == HRwuQwzswZ){ouedTKDaTb = true;}
      if(IuqUoCkBFo == DJSgVWcsIu){fgVseBZZwV = true;}
      if(VqrRAGfogR == cAHEjWmGVH){YfUoKAFjYB = true;}
      if(xUVgpoEWbA == VLQsBflXBo){uGWDSfcFew = true;}
      while(DJSgVWcsIu == IuqUoCkBFo){QbsjpyPTXc = true;}
      while(cAHEjWmGVH == cAHEjWmGVH){tOUngVKsBO = true;}
      while(VLQsBflXBo == VLQsBflXBo){itcxVpTdLL = true;}
      if(oHUnWFItwM == true){oHUnWFItwM = false;}
      if(IzrDoLzDXs == true){IzrDoLzDXs = false;}
      if(tjhwrrsYep == true){tjhwrrsYep = false;}
      if(jFrTGUfShe == true){jFrTGUfShe = false;}
      if(OrKIzWTMDo == true){OrKIzWTMDo = false;}
      if(fizHtEYYwd == true){fizHtEYYwd = false;}
      if(MiPFcDHYwU == true){MiPFcDHYwU = false;}
      if(fgVseBZZwV == true){fgVseBZZwV = false;}
      if(YfUoKAFjYB == true){YfUoKAFjYB = false;}
      if(uGWDSfcFew == true){uGWDSfcFew = false;}
      if(OtQiIzNGcs == true){OtQiIzNGcs = false;}
      if(ezbaFfNZuc == true){ezbaFfNZuc = false;}
      if(xWAuZYJRay == true){xWAuZYJRay = false;}
      if(YUuAGdPlfK == true){YUuAGdPlfK = false;}
      if(lzHfWweuxl == true){lzHfWweuxl = false;}
      if(RCJCyqtVJi == true){RCJCyqtVJi = false;}
      if(ouedTKDaTb == true){ouedTKDaTb = false;}
      if(QbsjpyPTXc == true){QbsjpyPTXc = false;}
      if(tOUngVKsBO == true){tOUngVKsBO = false;}
      if(itcxVpTdLL == true){itcxVpTdLL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVJPDIBBGP
{ 
  void pUmbIEhPUS()
  { 
      bool FsFlcbyQIT = false;
      bool EKbZVsjuOD = false;
      bool dsJAulmmhL = false;
      bool wWnZZlUHKH = false;
      bool reuOmfELKa = false;
      bool PounBLiEqq = false;
      bool nLhwWhVBAi = false;
      bool YbjHKzyuNP = false;
      bool habHuGaAYN = false;
      bool CPQTSgwyqE = false;
      bool JCLaBmFncB = false;
      bool NnpaJNiZBQ = false;
      bool GUblgILQnc = false;
      bool CAEJFeOBGH = false;
      bool BmXXAOYoJF = false;
      bool yWxaynZYtr = false;
      bool bozzyNjgVe = false;
      bool zhTsOTxElS = false;
      bool jWGiefCcKR = false;
      bool FoGNfMmXYm = false;
      string NGwzJrQGos;
      string PGfFdKsChH;
      string ACFgUDDXCS;
      string cYXXDXczuS;
      string IWfYtMPusA;
      string lDifhKAOeF;
      string osDWPqhHCF;
      string gtHOycWgmH;
      string nHdCfZoqpr;
      string WOUodPTIJD;
      string dHrmTruUhE;
      string mTbWRhOBpo;
      string BqRKhSYRki;
      string JNWidfOphm;
      string dUJlEDlyXw;
      string ARSTBlphEB;
      string TdjytYxrrk;
      string SYTCLgheFe;
      string fZtniquDhq;
      string pgkfTAkKqe;
      if(NGwzJrQGos == dHrmTruUhE){FsFlcbyQIT = true;}
      else if(dHrmTruUhE == NGwzJrQGos){JCLaBmFncB = true;}
      if(PGfFdKsChH == mTbWRhOBpo){EKbZVsjuOD = true;}
      else if(mTbWRhOBpo == PGfFdKsChH){NnpaJNiZBQ = true;}
      if(ACFgUDDXCS == BqRKhSYRki){dsJAulmmhL = true;}
      else if(BqRKhSYRki == ACFgUDDXCS){GUblgILQnc = true;}
      if(cYXXDXczuS == JNWidfOphm){wWnZZlUHKH = true;}
      else if(JNWidfOphm == cYXXDXczuS){CAEJFeOBGH = true;}
      if(IWfYtMPusA == dUJlEDlyXw){reuOmfELKa = true;}
      else if(dUJlEDlyXw == IWfYtMPusA){BmXXAOYoJF = true;}
      if(lDifhKAOeF == ARSTBlphEB){PounBLiEqq = true;}
      else if(ARSTBlphEB == lDifhKAOeF){yWxaynZYtr = true;}
      if(osDWPqhHCF == TdjytYxrrk){nLhwWhVBAi = true;}
      else if(TdjytYxrrk == osDWPqhHCF){bozzyNjgVe = true;}
      if(gtHOycWgmH == SYTCLgheFe){YbjHKzyuNP = true;}
      if(nHdCfZoqpr == fZtniquDhq){habHuGaAYN = true;}
      if(WOUodPTIJD == pgkfTAkKqe){CPQTSgwyqE = true;}
      while(SYTCLgheFe == gtHOycWgmH){zhTsOTxElS = true;}
      while(fZtniquDhq == fZtniquDhq){jWGiefCcKR = true;}
      while(pgkfTAkKqe == pgkfTAkKqe){FoGNfMmXYm = true;}
      if(FsFlcbyQIT == true){FsFlcbyQIT = false;}
      if(EKbZVsjuOD == true){EKbZVsjuOD = false;}
      if(dsJAulmmhL == true){dsJAulmmhL = false;}
      if(wWnZZlUHKH == true){wWnZZlUHKH = false;}
      if(reuOmfELKa == true){reuOmfELKa = false;}
      if(PounBLiEqq == true){PounBLiEqq = false;}
      if(nLhwWhVBAi == true){nLhwWhVBAi = false;}
      if(YbjHKzyuNP == true){YbjHKzyuNP = false;}
      if(habHuGaAYN == true){habHuGaAYN = false;}
      if(CPQTSgwyqE == true){CPQTSgwyqE = false;}
      if(JCLaBmFncB == true){JCLaBmFncB = false;}
      if(NnpaJNiZBQ == true){NnpaJNiZBQ = false;}
      if(GUblgILQnc == true){GUblgILQnc = false;}
      if(CAEJFeOBGH == true){CAEJFeOBGH = false;}
      if(BmXXAOYoJF == true){BmXXAOYoJF = false;}
      if(yWxaynZYtr == true){yWxaynZYtr = false;}
      if(bozzyNjgVe == true){bozzyNjgVe = false;}
      if(zhTsOTxElS == true){zhTsOTxElS = false;}
      if(jWGiefCcKR == true){jWGiefCcKR = false;}
      if(FoGNfMmXYm == true){FoGNfMmXYm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABHVPHVKTZ
{ 
  void CqLmzaZiRl()
  { 
      bool BhmYKXMUVE = false;
      bool MrukcSzfaU = false;
      bool LnUoiWuiXE = false;
      bool EUUALxIrxw = false;
      bool CAGrSuaYJZ = false;
      bool nmUBBNMyon = false;
      bool bcwRArWuZe = false;
      bool JGheRKgcVn = false;
      bool wVZyPRzTyx = false;
      bool jKCJTYEora = false;
      bool YezdPhEpiq = false;
      bool fjbBrFDxBi = false;
      bool rDxbuzDXKs = false;
      bool FqkuOQWwhh = false;
      bool MIjGQAiBRN = false;
      bool UGnJhVgWhP = false;
      bool dffokoyfla = false;
      bool iHOSVjSpKu = false;
      bool QCGwXyDbNs = false;
      bool iANSEfctVb = false;
      string kBkDMbigkj;
      string gQuhyZDjko;
      string kdpScQGdlk;
      string IwWMpnGMjx;
      string xqKmpgOJoF;
      string JbokZHLRau;
      string UEuAbktiqJ;
      string TqAnqsSCcw;
      string CxofafHkli;
      string colnbswKKE;
      string lfRflSbAsf;
      string nJodsXPOYw;
      string dIwIgeELMy;
      string xHqXJWeJsH;
      string DGqFtTzIuD;
      string dhlOadiJyH;
      string OPnuigRRUW;
      string rFUQrWQqNN;
      string ewQITOVcwf;
      string mVKlrnSwVN;
      if(kBkDMbigkj == lfRflSbAsf){BhmYKXMUVE = true;}
      else if(lfRflSbAsf == kBkDMbigkj){YezdPhEpiq = true;}
      if(gQuhyZDjko == nJodsXPOYw){MrukcSzfaU = true;}
      else if(nJodsXPOYw == gQuhyZDjko){fjbBrFDxBi = true;}
      if(kdpScQGdlk == dIwIgeELMy){LnUoiWuiXE = true;}
      else if(dIwIgeELMy == kdpScQGdlk){rDxbuzDXKs = true;}
      if(IwWMpnGMjx == xHqXJWeJsH){EUUALxIrxw = true;}
      else if(xHqXJWeJsH == IwWMpnGMjx){FqkuOQWwhh = true;}
      if(xqKmpgOJoF == DGqFtTzIuD){CAGrSuaYJZ = true;}
      else if(DGqFtTzIuD == xqKmpgOJoF){MIjGQAiBRN = true;}
      if(JbokZHLRau == dhlOadiJyH){nmUBBNMyon = true;}
      else if(dhlOadiJyH == JbokZHLRau){UGnJhVgWhP = true;}
      if(UEuAbktiqJ == OPnuigRRUW){bcwRArWuZe = true;}
      else if(OPnuigRRUW == UEuAbktiqJ){dffokoyfla = true;}
      if(TqAnqsSCcw == rFUQrWQqNN){JGheRKgcVn = true;}
      if(CxofafHkli == ewQITOVcwf){wVZyPRzTyx = true;}
      if(colnbswKKE == mVKlrnSwVN){jKCJTYEora = true;}
      while(rFUQrWQqNN == TqAnqsSCcw){iHOSVjSpKu = true;}
      while(ewQITOVcwf == ewQITOVcwf){QCGwXyDbNs = true;}
      while(mVKlrnSwVN == mVKlrnSwVN){iANSEfctVb = true;}
      if(BhmYKXMUVE == true){BhmYKXMUVE = false;}
      if(MrukcSzfaU == true){MrukcSzfaU = false;}
      if(LnUoiWuiXE == true){LnUoiWuiXE = false;}
      if(EUUALxIrxw == true){EUUALxIrxw = false;}
      if(CAGrSuaYJZ == true){CAGrSuaYJZ = false;}
      if(nmUBBNMyon == true){nmUBBNMyon = false;}
      if(bcwRArWuZe == true){bcwRArWuZe = false;}
      if(JGheRKgcVn == true){JGheRKgcVn = false;}
      if(wVZyPRzTyx == true){wVZyPRzTyx = false;}
      if(jKCJTYEora == true){jKCJTYEora = false;}
      if(YezdPhEpiq == true){YezdPhEpiq = false;}
      if(fjbBrFDxBi == true){fjbBrFDxBi = false;}
      if(rDxbuzDXKs == true){rDxbuzDXKs = false;}
      if(FqkuOQWwhh == true){FqkuOQWwhh = false;}
      if(MIjGQAiBRN == true){MIjGQAiBRN = false;}
      if(UGnJhVgWhP == true){UGnJhVgWhP = false;}
      if(dffokoyfla == true){dffokoyfla = false;}
      if(iHOSVjSpKu == true){iHOSVjSpKu = false;}
      if(QCGwXyDbNs == true){QCGwXyDbNs = false;}
      if(iANSEfctVb == true){iANSEfctVb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUFGABDSCQ
{ 
  void axbPbGzIiy()
  { 
      bool bMWnLNXLUc = false;
      bool FZlSKyppSD = false;
      bool BFXzobkqXK = false;
      bool RXtxXDxeOa = false;
      bool VqOEfFrkOJ = false;
      bool LlQNuVnWyj = false;
      bool cgnJKgfntH = false;
      bool BLaqgKqSTi = false;
      bool jzcNzfHgCB = false;
      bool OZfeyoDFty = false;
      bool ZDpHIAKYgj = false;
      bool dVDPzcDaJe = false;
      bool Zzlrraeurq = false;
      bool HlYUJfJVEz = false;
      bool UhzRWsWQeU = false;
      bool kbuPYZQxOg = false;
      bool UPfocrxhGS = false;
      bool ThVKJrzTVz = false;
      bool EOPXFeqJwi = false;
      bool OMGWdFBKne = false;
      string JdbtbRBuJk;
      string WknsnDyqKm;
      string TRBHFKOhXh;
      string NjwStzufPk;
      string gdYduygbZP;
      string NOhFWrcUoR;
      string DTXaXmoVyn;
      string HSbZForWLG;
      string cmHHUyBquC;
      string WapygNFxGI;
      string JLckHtmIzg;
      string AFIhnPLQGY;
      string lxZwRgbcrr;
      string itQDxRKWzZ;
      string LrqOCRRIJR;
      string CoqgVLkfSZ;
      string RJQHxFoFkV;
      string FnQfMsGKtA;
      string PTSaotDigk;
      string fdDYIBbiQw;
      if(JdbtbRBuJk == JLckHtmIzg){bMWnLNXLUc = true;}
      else if(JLckHtmIzg == JdbtbRBuJk){ZDpHIAKYgj = true;}
      if(WknsnDyqKm == AFIhnPLQGY){FZlSKyppSD = true;}
      else if(AFIhnPLQGY == WknsnDyqKm){dVDPzcDaJe = true;}
      if(TRBHFKOhXh == lxZwRgbcrr){BFXzobkqXK = true;}
      else if(lxZwRgbcrr == TRBHFKOhXh){Zzlrraeurq = true;}
      if(NjwStzufPk == itQDxRKWzZ){RXtxXDxeOa = true;}
      else if(itQDxRKWzZ == NjwStzufPk){HlYUJfJVEz = true;}
      if(gdYduygbZP == LrqOCRRIJR){VqOEfFrkOJ = true;}
      else if(LrqOCRRIJR == gdYduygbZP){UhzRWsWQeU = true;}
      if(NOhFWrcUoR == CoqgVLkfSZ){LlQNuVnWyj = true;}
      else if(CoqgVLkfSZ == NOhFWrcUoR){kbuPYZQxOg = true;}
      if(DTXaXmoVyn == RJQHxFoFkV){cgnJKgfntH = true;}
      else if(RJQHxFoFkV == DTXaXmoVyn){UPfocrxhGS = true;}
      if(HSbZForWLG == FnQfMsGKtA){BLaqgKqSTi = true;}
      if(cmHHUyBquC == PTSaotDigk){jzcNzfHgCB = true;}
      if(WapygNFxGI == fdDYIBbiQw){OZfeyoDFty = true;}
      while(FnQfMsGKtA == HSbZForWLG){ThVKJrzTVz = true;}
      while(PTSaotDigk == PTSaotDigk){EOPXFeqJwi = true;}
      while(fdDYIBbiQw == fdDYIBbiQw){OMGWdFBKne = true;}
      if(bMWnLNXLUc == true){bMWnLNXLUc = false;}
      if(FZlSKyppSD == true){FZlSKyppSD = false;}
      if(BFXzobkqXK == true){BFXzobkqXK = false;}
      if(RXtxXDxeOa == true){RXtxXDxeOa = false;}
      if(VqOEfFrkOJ == true){VqOEfFrkOJ = false;}
      if(LlQNuVnWyj == true){LlQNuVnWyj = false;}
      if(cgnJKgfntH == true){cgnJKgfntH = false;}
      if(BLaqgKqSTi == true){BLaqgKqSTi = false;}
      if(jzcNzfHgCB == true){jzcNzfHgCB = false;}
      if(OZfeyoDFty == true){OZfeyoDFty = false;}
      if(ZDpHIAKYgj == true){ZDpHIAKYgj = false;}
      if(dVDPzcDaJe == true){dVDPzcDaJe = false;}
      if(Zzlrraeurq == true){Zzlrraeurq = false;}
      if(HlYUJfJVEz == true){HlYUJfJVEz = false;}
      if(UhzRWsWQeU == true){UhzRWsWQeU = false;}
      if(kbuPYZQxOg == true){kbuPYZQxOg = false;}
      if(UPfocrxhGS == true){UPfocrxhGS = false;}
      if(ThVKJrzTVz == true){ThVKJrzTVz = false;}
      if(EOPXFeqJwi == true){EOPXFeqJwi = false;}
      if(OMGWdFBKne == true){OMGWdFBKne = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKDKXLDVFV
{ 
  void KPoemGIKJb()
  { 
      bool fbClmfoWSn = false;
      bool ppqXSNrIPf = false;
      bool PnzmZtJEcn = false;
      bool nXZGzhJRbc = false;
      bool XAaKGdYSLy = false;
      bool jZdNVqcPMr = false;
      bool VktdzSQkYk = false;
      bool DaglIPNngw = false;
      bool VqsdEOsLjH = false;
      bool EtEiHmFxLm = false;
      bool NnsZuJsqFG = false;
      bool doiQWeqQZk = false;
      bool YEARfJVyeV = false;
      bool JPbshgxSht = false;
      bool UCGcdPKnLc = false;
      bool uoWaOInbtl = false;
      bool nuMjwNMphp = false;
      bool gXhePWyXmP = false;
      bool yglCZUsBdZ = false;
      bool rUYwGZpWfQ = false;
      string mqXmygxYEV;
      string YdXBNRqJwi;
      string huZNChSJJQ;
      string aBOzmsuNUX;
      string QfZVMGnQRl;
      string DUJggqRKkQ;
      string NmPnuWPXNU;
      string VcnXSCUEAu;
      string sCqXMFrgRu;
      string bjcDKcQlZp;
      string pPCxPagkOe;
      string VMJoXLwqap;
      string diGSslAjNp;
      string lidKEcAtIl;
      string YGRmZOamfy;
      string gYLjLHJjDd;
      string ZwXYsmiyjt;
      string LBinQXQTre;
      string KMDOIMWtzx;
      string TQqdLcissl;
      if(mqXmygxYEV == pPCxPagkOe){fbClmfoWSn = true;}
      else if(pPCxPagkOe == mqXmygxYEV){NnsZuJsqFG = true;}
      if(YdXBNRqJwi == VMJoXLwqap){ppqXSNrIPf = true;}
      else if(VMJoXLwqap == YdXBNRqJwi){doiQWeqQZk = true;}
      if(huZNChSJJQ == diGSslAjNp){PnzmZtJEcn = true;}
      else if(diGSslAjNp == huZNChSJJQ){YEARfJVyeV = true;}
      if(aBOzmsuNUX == lidKEcAtIl){nXZGzhJRbc = true;}
      else if(lidKEcAtIl == aBOzmsuNUX){JPbshgxSht = true;}
      if(QfZVMGnQRl == YGRmZOamfy){XAaKGdYSLy = true;}
      else if(YGRmZOamfy == QfZVMGnQRl){UCGcdPKnLc = true;}
      if(DUJggqRKkQ == gYLjLHJjDd){jZdNVqcPMr = true;}
      else if(gYLjLHJjDd == DUJggqRKkQ){uoWaOInbtl = true;}
      if(NmPnuWPXNU == ZwXYsmiyjt){VktdzSQkYk = true;}
      else if(ZwXYsmiyjt == NmPnuWPXNU){nuMjwNMphp = true;}
      if(VcnXSCUEAu == LBinQXQTre){DaglIPNngw = true;}
      if(sCqXMFrgRu == KMDOIMWtzx){VqsdEOsLjH = true;}
      if(bjcDKcQlZp == TQqdLcissl){EtEiHmFxLm = true;}
      while(LBinQXQTre == VcnXSCUEAu){gXhePWyXmP = true;}
      while(KMDOIMWtzx == KMDOIMWtzx){yglCZUsBdZ = true;}
      while(TQqdLcissl == TQqdLcissl){rUYwGZpWfQ = true;}
      if(fbClmfoWSn == true){fbClmfoWSn = false;}
      if(ppqXSNrIPf == true){ppqXSNrIPf = false;}
      if(PnzmZtJEcn == true){PnzmZtJEcn = false;}
      if(nXZGzhJRbc == true){nXZGzhJRbc = false;}
      if(XAaKGdYSLy == true){XAaKGdYSLy = false;}
      if(jZdNVqcPMr == true){jZdNVqcPMr = false;}
      if(VktdzSQkYk == true){VktdzSQkYk = false;}
      if(DaglIPNngw == true){DaglIPNngw = false;}
      if(VqsdEOsLjH == true){VqsdEOsLjH = false;}
      if(EtEiHmFxLm == true){EtEiHmFxLm = false;}
      if(NnsZuJsqFG == true){NnsZuJsqFG = false;}
      if(doiQWeqQZk == true){doiQWeqQZk = false;}
      if(YEARfJVyeV == true){YEARfJVyeV = false;}
      if(JPbshgxSht == true){JPbshgxSht = false;}
      if(UCGcdPKnLc == true){UCGcdPKnLc = false;}
      if(uoWaOInbtl == true){uoWaOInbtl = false;}
      if(nuMjwNMphp == true){nuMjwNMphp = false;}
      if(gXhePWyXmP == true){gXhePWyXmP = false;}
      if(yglCZUsBdZ == true){yglCZUsBdZ = false;}
      if(rUYwGZpWfQ == true){rUYwGZpWfQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGGTIPECPL
{ 
  void YEfsUdlHSQ()
  { 
      bool ToyTgCeXSm = false;
      bool pmzhgMqDqK = false;
      bool kaQEsXRcHk = false;
      bool QGKxZokZTX = false;
      bool oDyDVlGchl = false;
      bool rywUrsXtZI = false;
      bool jBQhVibBIr = false;
      bool bQiSUgbMhH = false;
      bool QouVsSKoEg = false;
      bool QqAKmmmQhm = false;
      bool JETpKbPcAK = false;
      bool QLLSruGtoD = false;
      bool YlxbajPXfg = false;
      bool sKeuxLUELQ = false;
      bool CgosPFehSq = false;
      bool gsbeOWHrOZ = false;
      bool LqwSRGgQUf = false;
      bool aBiXAqxDMV = false;
      bool FhFnAAhzfa = false;
      bool EbpkELkVbI = false;
      string QVjeseSIKL;
      string MbOqPNuqlr;
      string BMlCmrtccP;
      string lRChOujTGF;
      string nUaDZILUEP;
      string XBwaBEihqA;
      string jpftZtZgbT;
      string cakgDflice;
      string fZYMrkVbfJ;
      string MCbFUxofce;
      string hdsjlwQPWV;
      string SzFMTKRSCo;
      string YyBSHazeLF;
      string pFGxwCgnaw;
      string TFEKqNwOkK;
      string fWdnGjcacL;
      string xkEQeMsHQR;
      string dcrGUStpat;
      string djtAZTbRqM;
      string YFLOyiBmfd;
      if(QVjeseSIKL == hdsjlwQPWV){ToyTgCeXSm = true;}
      else if(hdsjlwQPWV == QVjeseSIKL){JETpKbPcAK = true;}
      if(MbOqPNuqlr == SzFMTKRSCo){pmzhgMqDqK = true;}
      else if(SzFMTKRSCo == MbOqPNuqlr){QLLSruGtoD = true;}
      if(BMlCmrtccP == YyBSHazeLF){kaQEsXRcHk = true;}
      else if(YyBSHazeLF == BMlCmrtccP){YlxbajPXfg = true;}
      if(lRChOujTGF == pFGxwCgnaw){QGKxZokZTX = true;}
      else if(pFGxwCgnaw == lRChOujTGF){sKeuxLUELQ = true;}
      if(nUaDZILUEP == TFEKqNwOkK){oDyDVlGchl = true;}
      else if(TFEKqNwOkK == nUaDZILUEP){CgosPFehSq = true;}
      if(XBwaBEihqA == fWdnGjcacL){rywUrsXtZI = true;}
      else if(fWdnGjcacL == XBwaBEihqA){gsbeOWHrOZ = true;}
      if(jpftZtZgbT == xkEQeMsHQR){jBQhVibBIr = true;}
      else if(xkEQeMsHQR == jpftZtZgbT){LqwSRGgQUf = true;}
      if(cakgDflice == dcrGUStpat){bQiSUgbMhH = true;}
      if(fZYMrkVbfJ == djtAZTbRqM){QouVsSKoEg = true;}
      if(MCbFUxofce == YFLOyiBmfd){QqAKmmmQhm = true;}
      while(dcrGUStpat == cakgDflice){aBiXAqxDMV = true;}
      while(djtAZTbRqM == djtAZTbRqM){FhFnAAhzfa = true;}
      while(YFLOyiBmfd == YFLOyiBmfd){EbpkELkVbI = true;}
      if(ToyTgCeXSm == true){ToyTgCeXSm = false;}
      if(pmzhgMqDqK == true){pmzhgMqDqK = false;}
      if(kaQEsXRcHk == true){kaQEsXRcHk = false;}
      if(QGKxZokZTX == true){QGKxZokZTX = false;}
      if(oDyDVlGchl == true){oDyDVlGchl = false;}
      if(rywUrsXtZI == true){rywUrsXtZI = false;}
      if(jBQhVibBIr == true){jBQhVibBIr = false;}
      if(bQiSUgbMhH == true){bQiSUgbMhH = false;}
      if(QouVsSKoEg == true){QouVsSKoEg = false;}
      if(QqAKmmmQhm == true){QqAKmmmQhm = false;}
      if(JETpKbPcAK == true){JETpKbPcAK = false;}
      if(QLLSruGtoD == true){QLLSruGtoD = false;}
      if(YlxbajPXfg == true){YlxbajPXfg = false;}
      if(sKeuxLUELQ == true){sKeuxLUELQ = false;}
      if(CgosPFehSq == true){CgosPFehSq = false;}
      if(gsbeOWHrOZ == true){gsbeOWHrOZ = false;}
      if(LqwSRGgQUf == true){LqwSRGgQUf = false;}
      if(aBiXAqxDMV == true){aBiXAqxDMV = false;}
      if(FhFnAAhzfa == true){FhFnAAhzfa = false;}
      if(EbpkELkVbI == true){EbpkELkVbI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZUSHGHVZE
{ 
  void VpPOIZaRsK()
  { 
      bool IiHaNCfHhH = false;
      bool syRkPgVmoS = false;
      bool OkXIRbhthO = false;
      bool IKSSLwEhEB = false;
      bool PqtxemKAzt = false;
      bool toWIMWKyIk = false;
      bool TlZSyifzYT = false;
      bool cmhmDWqade = false;
      bool RhunTTmKGn = false;
      bool kFYSgdRbyw = false;
      bool HLbfRGHiFo = false;
      bool fjUdTlplye = false;
      bool uUsjiWNOGY = false;
      bool FPchWFFPVM = false;
      bool LEFQIAkuyu = false;
      bool mfcSAlSqxt = false;
      bool srcfjQHmGO = false;
      bool faPkTqPbbh = false;
      bool lSQKlZlKgk = false;
      bool mOSbTTaYfq = false;
      string CuIKtECfOZ;
      string JkPSaFSAjj;
      string aHLUMGdDNT;
      string iPpoPJaHzl;
      string ecrfIjBwOQ;
      string FToVzuimym;
      string ayRtqttZCR;
      string dKAxExPeMc;
      string FgnxOPZUpU;
      string ZmJMLfLxoN;
      string obsxltSqQB;
      string fDaUhsKUeb;
      string TZihqqAnkY;
      string lRpymdnqKU;
      string whDonWLoeS;
      string VpRNsPrLFu;
      string seFrONNcgD;
      string ETJJfkVssU;
      string eLJSDwzbEX;
      string kckPbQcLaa;
      if(CuIKtECfOZ == obsxltSqQB){IiHaNCfHhH = true;}
      else if(obsxltSqQB == CuIKtECfOZ){HLbfRGHiFo = true;}
      if(JkPSaFSAjj == fDaUhsKUeb){syRkPgVmoS = true;}
      else if(fDaUhsKUeb == JkPSaFSAjj){fjUdTlplye = true;}
      if(aHLUMGdDNT == TZihqqAnkY){OkXIRbhthO = true;}
      else if(TZihqqAnkY == aHLUMGdDNT){uUsjiWNOGY = true;}
      if(iPpoPJaHzl == lRpymdnqKU){IKSSLwEhEB = true;}
      else if(lRpymdnqKU == iPpoPJaHzl){FPchWFFPVM = true;}
      if(ecrfIjBwOQ == whDonWLoeS){PqtxemKAzt = true;}
      else if(whDonWLoeS == ecrfIjBwOQ){LEFQIAkuyu = true;}
      if(FToVzuimym == VpRNsPrLFu){toWIMWKyIk = true;}
      else if(VpRNsPrLFu == FToVzuimym){mfcSAlSqxt = true;}
      if(ayRtqttZCR == seFrONNcgD){TlZSyifzYT = true;}
      else if(seFrONNcgD == ayRtqttZCR){srcfjQHmGO = true;}
      if(dKAxExPeMc == ETJJfkVssU){cmhmDWqade = true;}
      if(FgnxOPZUpU == eLJSDwzbEX){RhunTTmKGn = true;}
      if(ZmJMLfLxoN == kckPbQcLaa){kFYSgdRbyw = true;}
      while(ETJJfkVssU == dKAxExPeMc){faPkTqPbbh = true;}
      while(eLJSDwzbEX == eLJSDwzbEX){lSQKlZlKgk = true;}
      while(kckPbQcLaa == kckPbQcLaa){mOSbTTaYfq = true;}
      if(IiHaNCfHhH == true){IiHaNCfHhH = false;}
      if(syRkPgVmoS == true){syRkPgVmoS = false;}
      if(OkXIRbhthO == true){OkXIRbhthO = false;}
      if(IKSSLwEhEB == true){IKSSLwEhEB = false;}
      if(PqtxemKAzt == true){PqtxemKAzt = false;}
      if(toWIMWKyIk == true){toWIMWKyIk = false;}
      if(TlZSyifzYT == true){TlZSyifzYT = false;}
      if(cmhmDWqade == true){cmhmDWqade = false;}
      if(RhunTTmKGn == true){RhunTTmKGn = false;}
      if(kFYSgdRbyw == true){kFYSgdRbyw = false;}
      if(HLbfRGHiFo == true){HLbfRGHiFo = false;}
      if(fjUdTlplye == true){fjUdTlplye = false;}
      if(uUsjiWNOGY == true){uUsjiWNOGY = false;}
      if(FPchWFFPVM == true){FPchWFFPVM = false;}
      if(LEFQIAkuyu == true){LEFQIAkuyu = false;}
      if(mfcSAlSqxt == true){mfcSAlSqxt = false;}
      if(srcfjQHmGO == true){srcfjQHmGO = false;}
      if(faPkTqPbbh == true){faPkTqPbbh = false;}
      if(lSQKlZlKgk == true){lSQKlZlKgk = false;}
      if(mOSbTTaYfq == true){mOSbTTaYfq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCSLRGVIGZ
{ 
  void tmMimnzFZl()
  { 
      bool boeDAyzxwJ = false;
      bool RIgeVBQQhQ = false;
      bool xNppMsojpG = false;
      bool uDHgrxiljH = false;
      bool HuoylpRZUt = false;
      bool NphThNzoqH = false;
      bool JOGoONAzmY = false;
      bool SefZIBYqEV = false;
      bool aOPwsFVnze = false;
      bool xttcxsozjX = false;
      bool pSmuahJHKf = false;
      bool oHjUfuzJwI = false;
      bool rMzIaYjDcP = false;
      bool MYHgfHaTVK = false;
      bool uNcSopJZwC = false;
      bool seDaedTeTC = false;
      bool yGeuTPADoY = false;
      bool TfnlNeifSk = false;
      bool PKGZVgVgBB = false;
      bool muzSLohgzZ = false;
      string pbhMaVmHlC;
      string cjQoPBwNnq;
      string sKpUZPRjxV;
      string jbVCTcUwjg;
      string xKzUZYPxhP;
      string EnlfnelNlK;
      string ECJPRBOOVl;
      string gzdGsiLUtB;
      string ATBhRuopNn;
      string qGKYctBiDY;
      string KBauhEKflF;
      string SQTkKjBayV;
      string LXAhuZnEdz;
      string gcRUpzrGzM;
      string kJDIUamZOr;
      string sZjgMlAsAI;
      string QGBmXpyytL;
      string rualkCUrMU;
      string lOokFHskID;
      string yyFqudHQje;
      if(pbhMaVmHlC == KBauhEKflF){boeDAyzxwJ = true;}
      else if(KBauhEKflF == pbhMaVmHlC){pSmuahJHKf = true;}
      if(cjQoPBwNnq == SQTkKjBayV){RIgeVBQQhQ = true;}
      else if(SQTkKjBayV == cjQoPBwNnq){oHjUfuzJwI = true;}
      if(sKpUZPRjxV == LXAhuZnEdz){xNppMsojpG = true;}
      else if(LXAhuZnEdz == sKpUZPRjxV){rMzIaYjDcP = true;}
      if(jbVCTcUwjg == gcRUpzrGzM){uDHgrxiljH = true;}
      else if(gcRUpzrGzM == jbVCTcUwjg){MYHgfHaTVK = true;}
      if(xKzUZYPxhP == kJDIUamZOr){HuoylpRZUt = true;}
      else if(kJDIUamZOr == xKzUZYPxhP){uNcSopJZwC = true;}
      if(EnlfnelNlK == sZjgMlAsAI){NphThNzoqH = true;}
      else if(sZjgMlAsAI == EnlfnelNlK){seDaedTeTC = true;}
      if(ECJPRBOOVl == QGBmXpyytL){JOGoONAzmY = true;}
      else if(QGBmXpyytL == ECJPRBOOVl){yGeuTPADoY = true;}
      if(gzdGsiLUtB == rualkCUrMU){SefZIBYqEV = true;}
      if(ATBhRuopNn == lOokFHskID){aOPwsFVnze = true;}
      if(qGKYctBiDY == yyFqudHQje){xttcxsozjX = true;}
      while(rualkCUrMU == gzdGsiLUtB){TfnlNeifSk = true;}
      while(lOokFHskID == lOokFHskID){PKGZVgVgBB = true;}
      while(yyFqudHQje == yyFqudHQje){muzSLohgzZ = true;}
      if(boeDAyzxwJ == true){boeDAyzxwJ = false;}
      if(RIgeVBQQhQ == true){RIgeVBQQhQ = false;}
      if(xNppMsojpG == true){xNppMsojpG = false;}
      if(uDHgrxiljH == true){uDHgrxiljH = false;}
      if(HuoylpRZUt == true){HuoylpRZUt = false;}
      if(NphThNzoqH == true){NphThNzoqH = false;}
      if(JOGoONAzmY == true){JOGoONAzmY = false;}
      if(SefZIBYqEV == true){SefZIBYqEV = false;}
      if(aOPwsFVnze == true){aOPwsFVnze = false;}
      if(xttcxsozjX == true){xttcxsozjX = false;}
      if(pSmuahJHKf == true){pSmuahJHKf = false;}
      if(oHjUfuzJwI == true){oHjUfuzJwI = false;}
      if(rMzIaYjDcP == true){rMzIaYjDcP = false;}
      if(MYHgfHaTVK == true){MYHgfHaTVK = false;}
      if(uNcSopJZwC == true){uNcSopJZwC = false;}
      if(seDaedTeTC == true){seDaedTeTC = false;}
      if(yGeuTPADoY == true){yGeuTPADoY = false;}
      if(TfnlNeifSk == true){TfnlNeifSk = false;}
      if(PKGZVgVgBB == true){PKGZVgVgBB = false;}
      if(muzSLohgzZ == true){muzSLohgzZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQXLSIWFZO
{ 
  void FPVBHNQANd()
  { 
      bool eWQJJfiUGV = false;
      bool LHuATpWzsV = false;
      bool JQsjiDNUCP = false;
      bool EwYZLQqGOX = false;
      bool RMNzirnDeF = false;
      bool xmFpINdfZF = false;
      bool SOSqQPiVnC = false;
      bool zPkVDxDtAp = false;
      bool OKowRRpiQy = false;
      bool mKgIEDtWhT = false;
      bool JSOcGhCjlL = false;
      bool KjeiqHZVYz = false;
      bool YAEpPoibQA = false;
      bool DfLgguuMpj = false;
      bool PGwFmDexRw = false;
      bool cYyiuJOYNR = false;
      bool yZTkIdXyCu = false;
      bool MNeniRDyCM = false;
      bool JkJTWdhclX = false;
      bool gWyYlomLxI = false;
      string WcNVhtbsQm;
      string fyCVhksoOg;
      string YOhSnyRTec;
      string mZKVMKcLGk;
      string TqAjUmrBXp;
      string hgWNJIuthi;
      string cIOmzFnfIX;
      string IghdNgOxxA;
      string FQuntGDwLE;
      string OhcXIKcMkP;
      string yMrAhBysAb;
      string sywgdLMZrs;
      string CqTDIZDKUC;
      string EBMhCsXuGs;
      string IKwiKQkwtw;
      string yCTqNGrnqH;
      string xmXxXrlOej;
      string mRTyjqujsq;
      string nHQXEBhUUu;
      string AjDywUlyLS;
      if(WcNVhtbsQm == yMrAhBysAb){eWQJJfiUGV = true;}
      else if(yMrAhBysAb == WcNVhtbsQm){JSOcGhCjlL = true;}
      if(fyCVhksoOg == sywgdLMZrs){LHuATpWzsV = true;}
      else if(sywgdLMZrs == fyCVhksoOg){KjeiqHZVYz = true;}
      if(YOhSnyRTec == CqTDIZDKUC){JQsjiDNUCP = true;}
      else if(CqTDIZDKUC == YOhSnyRTec){YAEpPoibQA = true;}
      if(mZKVMKcLGk == EBMhCsXuGs){EwYZLQqGOX = true;}
      else if(EBMhCsXuGs == mZKVMKcLGk){DfLgguuMpj = true;}
      if(TqAjUmrBXp == IKwiKQkwtw){RMNzirnDeF = true;}
      else if(IKwiKQkwtw == TqAjUmrBXp){PGwFmDexRw = true;}
      if(hgWNJIuthi == yCTqNGrnqH){xmFpINdfZF = true;}
      else if(yCTqNGrnqH == hgWNJIuthi){cYyiuJOYNR = true;}
      if(cIOmzFnfIX == xmXxXrlOej){SOSqQPiVnC = true;}
      else if(xmXxXrlOej == cIOmzFnfIX){yZTkIdXyCu = true;}
      if(IghdNgOxxA == mRTyjqujsq){zPkVDxDtAp = true;}
      if(FQuntGDwLE == nHQXEBhUUu){OKowRRpiQy = true;}
      if(OhcXIKcMkP == AjDywUlyLS){mKgIEDtWhT = true;}
      while(mRTyjqujsq == IghdNgOxxA){MNeniRDyCM = true;}
      while(nHQXEBhUUu == nHQXEBhUUu){JkJTWdhclX = true;}
      while(AjDywUlyLS == AjDywUlyLS){gWyYlomLxI = true;}
      if(eWQJJfiUGV == true){eWQJJfiUGV = false;}
      if(LHuATpWzsV == true){LHuATpWzsV = false;}
      if(JQsjiDNUCP == true){JQsjiDNUCP = false;}
      if(EwYZLQqGOX == true){EwYZLQqGOX = false;}
      if(RMNzirnDeF == true){RMNzirnDeF = false;}
      if(xmFpINdfZF == true){xmFpINdfZF = false;}
      if(SOSqQPiVnC == true){SOSqQPiVnC = false;}
      if(zPkVDxDtAp == true){zPkVDxDtAp = false;}
      if(OKowRRpiQy == true){OKowRRpiQy = false;}
      if(mKgIEDtWhT == true){mKgIEDtWhT = false;}
      if(JSOcGhCjlL == true){JSOcGhCjlL = false;}
      if(KjeiqHZVYz == true){KjeiqHZVYz = false;}
      if(YAEpPoibQA == true){YAEpPoibQA = false;}
      if(DfLgguuMpj == true){DfLgguuMpj = false;}
      if(PGwFmDexRw == true){PGwFmDexRw = false;}
      if(cYyiuJOYNR == true){cYyiuJOYNR = false;}
      if(yZTkIdXyCu == true){yZTkIdXyCu = false;}
      if(MNeniRDyCM == true){MNeniRDyCM = false;}
      if(JkJTWdhclX == true){JkJTWdhclX = false;}
      if(gWyYlomLxI == true){gWyYlomLxI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KMFJQYYQTU
{ 
  void rOxtLQIozo()
  { 
      bool pKwnCzzbFV = false;
      bool KkiZGZjECh = false;
      bool wSnpthwKBF = false;
      bool ysLsWFsWxr = false;
      bool QBObWjOXHd = false;
      bool CsfEBWWGsT = false;
      bool DoZAXRYoCB = false;
      bool fNGKQuEMSK = false;
      bool SXCXCFMGqz = false;
      bool hmdcobaOEF = false;
      bool KZVGxolVnF = false;
      bool SKmiBemCxR = false;
      bool ESyCSsicUn = false;
      bool UoHMzsCuZN = false;
      bool SqSkgXztbJ = false;
      bool oYQlBraSnE = false;
      bool FJAzkdCaiI = false;
      bool cqbjyMzMVt = false;
      bool snBKzwXVLG = false;
      bool RiGUHJqTAD = false;
      string KdLNzEQETJ;
      string bOuxJsjKbe;
      string rBgdMDiVUw;
      string qrAlTggMVH;
      string TSfqyDdTGx;
      string zyFqMIwhAw;
      string UtiWSiNJcb;
      string MXoUKYVpeJ;
      string ZPPWwrlJYL;
      string jzLZlYjJXO;
      string pUqekbJkfm;
      string mGCqVEeLaZ;
      string wEjQqNLOhl;
      string oMSPTFYklU;
      string hAckYdxUDh;
      string tYhxRkjZmW;
      string QuDtyanlXP;
      string ftYFrwayqN;
      string QpKzrQdUyh;
      string VyxODmxhmy;
      if(KdLNzEQETJ == pUqekbJkfm){pKwnCzzbFV = true;}
      else if(pUqekbJkfm == KdLNzEQETJ){KZVGxolVnF = true;}
      if(bOuxJsjKbe == mGCqVEeLaZ){KkiZGZjECh = true;}
      else if(mGCqVEeLaZ == bOuxJsjKbe){SKmiBemCxR = true;}
      if(rBgdMDiVUw == wEjQqNLOhl){wSnpthwKBF = true;}
      else if(wEjQqNLOhl == rBgdMDiVUw){ESyCSsicUn = true;}
      if(qrAlTggMVH == oMSPTFYklU){ysLsWFsWxr = true;}
      else if(oMSPTFYklU == qrAlTggMVH){UoHMzsCuZN = true;}
      if(TSfqyDdTGx == hAckYdxUDh){QBObWjOXHd = true;}
      else if(hAckYdxUDh == TSfqyDdTGx){SqSkgXztbJ = true;}
      if(zyFqMIwhAw == tYhxRkjZmW){CsfEBWWGsT = true;}
      else if(tYhxRkjZmW == zyFqMIwhAw){oYQlBraSnE = true;}
      if(UtiWSiNJcb == QuDtyanlXP){DoZAXRYoCB = true;}
      else if(QuDtyanlXP == UtiWSiNJcb){FJAzkdCaiI = true;}
      if(MXoUKYVpeJ == ftYFrwayqN){fNGKQuEMSK = true;}
      if(ZPPWwrlJYL == QpKzrQdUyh){SXCXCFMGqz = true;}
      if(jzLZlYjJXO == VyxODmxhmy){hmdcobaOEF = true;}
      while(ftYFrwayqN == MXoUKYVpeJ){cqbjyMzMVt = true;}
      while(QpKzrQdUyh == QpKzrQdUyh){snBKzwXVLG = true;}
      while(VyxODmxhmy == VyxODmxhmy){RiGUHJqTAD = true;}
      if(pKwnCzzbFV == true){pKwnCzzbFV = false;}
      if(KkiZGZjECh == true){KkiZGZjECh = false;}
      if(wSnpthwKBF == true){wSnpthwKBF = false;}
      if(ysLsWFsWxr == true){ysLsWFsWxr = false;}
      if(QBObWjOXHd == true){QBObWjOXHd = false;}
      if(CsfEBWWGsT == true){CsfEBWWGsT = false;}
      if(DoZAXRYoCB == true){DoZAXRYoCB = false;}
      if(fNGKQuEMSK == true){fNGKQuEMSK = false;}
      if(SXCXCFMGqz == true){SXCXCFMGqz = false;}
      if(hmdcobaOEF == true){hmdcobaOEF = false;}
      if(KZVGxolVnF == true){KZVGxolVnF = false;}
      if(SKmiBemCxR == true){SKmiBemCxR = false;}
      if(ESyCSsicUn == true){ESyCSsicUn = false;}
      if(UoHMzsCuZN == true){UoHMzsCuZN = false;}
      if(SqSkgXztbJ == true){SqSkgXztbJ = false;}
      if(oYQlBraSnE == true){oYQlBraSnE = false;}
      if(FJAzkdCaiI == true){FJAzkdCaiI = false;}
      if(cqbjyMzMVt == true){cqbjyMzMVt = false;}
      if(snBKzwXVLG == true){snBKzwXVLG = false;}
      if(RiGUHJqTAD == true){RiGUHJqTAD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MBEEUHORUO
{ 
  void cXROTxFXcQ()
  { 
      bool tOngRMHFYj = false;
      bool gHuedYBUed = false;
      bool stteuaTXqg = false;
      bool yjLZMqoEVb = false;
      bool drptLRXidU = false;
      bool symidATJlp = false;
      bool riOqkxwUSl = false;
      bool iwyDzBDASc = false;
      bool DksVnAxcwL = false;
      bool WfReitcyIO = false;
      bool VCQqkwziib = false;
      bool xTpIlHprDj = false;
      bool zTYGPDdTTF = false;
      bool XEqEHBTBkr = false;
      bool BNsTOCoJsb = false;
      bool EkuXOCcJbg = false;
      bool RfPdDrclBj = false;
      bool mnHLhkZFqN = false;
      bool NUZqAmJSoE = false;
      bool YKZDZVyPPW = false;
      string qpULzuWfEQ;
      string XpHoMMUKBg;
      string nCtoHkZlmj;
      string ABKpiXYRrl;
      string QDrXPEyKlR;
      string usVTYoueEO;
      string UjrUPWeRFn;
      string nDSPPjKWZC;
      string mPzUnHfpQt;
      string ctNdQfKWHs;
      string YgEydraFEn;
      string eYFBaFjXgH;
      string qoALLtonyj;
      string YmOfcFKBqw;
      string gZlbOEnLCL;
      string umpABjfrmi;
      string ClHTPqJYXU;
      string tifjaRCXxH;
      string FckmnkxOes;
      string ZSOHstSRMX;
      if(qpULzuWfEQ == YgEydraFEn){tOngRMHFYj = true;}
      else if(YgEydraFEn == qpULzuWfEQ){VCQqkwziib = true;}
      if(XpHoMMUKBg == eYFBaFjXgH){gHuedYBUed = true;}
      else if(eYFBaFjXgH == XpHoMMUKBg){xTpIlHprDj = true;}
      if(nCtoHkZlmj == qoALLtonyj){stteuaTXqg = true;}
      else if(qoALLtonyj == nCtoHkZlmj){zTYGPDdTTF = true;}
      if(ABKpiXYRrl == YmOfcFKBqw){yjLZMqoEVb = true;}
      else if(YmOfcFKBqw == ABKpiXYRrl){XEqEHBTBkr = true;}
      if(QDrXPEyKlR == gZlbOEnLCL){drptLRXidU = true;}
      else if(gZlbOEnLCL == QDrXPEyKlR){BNsTOCoJsb = true;}
      if(usVTYoueEO == umpABjfrmi){symidATJlp = true;}
      else if(umpABjfrmi == usVTYoueEO){EkuXOCcJbg = true;}
      if(UjrUPWeRFn == ClHTPqJYXU){riOqkxwUSl = true;}
      else if(ClHTPqJYXU == UjrUPWeRFn){RfPdDrclBj = true;}
      if(nDSPPjKWZC == tifjaRCXxH){iwyDzBDASc = true;}
      if(mPzUnHfpQt == FckmnkxOes){DksVnAxcwL = true;}
      if(ctNdQfKWHs == ZSOHstSRMX){WfReitcyIO = true;}
      while(tifjaRCXxH == nDSPPjKWZC){mnHLhkZFqN = true;}
      while(FckmnkxOes == FckmnkxOes){NUZqAmJSoE = true;}
      while(ZSOHstSRMX == ZSOHstSRMX){YKZDZVyPPW = true;}
      if(tOngRMHFYj == true){tOngRMHFYj = false;}
      if(gHuedYBUed == true){gHuedYBUed = false;}
      if(stteuaTXqg == true){stteuaTXqg = false;}
      if(yjLZMqoEVb == true){yjLZMqoEVb = false;}
      if(drptLRXidU == true){drptLRXidU = false;}
      if(symidATJlp == true){symidATJlp = false;}
      if(riOqkxwUSl == true){riOqkxwUSl = false;}
      if(iwyDzBDASc == true){iwyDzBDASc = false;}
      if(DksVnAxcwL == true){DksVnAxcwL = false;}
      if(WfReitcyIO == true){WfReitcyIO = false;}
      if(VCQqkwziib == true){VCQqkwziib = false;}
      if(xTpIlHprDj == true){xTpIlHprDj = false;}
      if(zTYGPDdTTF == true){zTYGPDdTTF = false;}
      if(XEqEHBTBkr == true){XEqEHBTBkr = false;}
      if(BNsTOCoJsb == true){BNsTOCoJsb = false;}
      if(EkuXOCcJbg == true){EkuXOCcJbg = false;}
      if(RfPdDrclBj == true){RfPdDrclBj = false;}
      if(mnHLhkZFqN == true){mnHLhkZFqN = false;}
      if(NUZqAmJSoE == true){NUZqAmJSoE = false;}
      if(YKZDZVyPPW == true){YKZDZVyPPW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDTOYZMETP
{ 
  void QUngtZZjMD()
  { 
      bool IjKtgGFDEx = false;
      bool ALUfdrbXuI = false;
      bool doRWKKgLBK = false;
      bool YDGujaNzfK = false;
      bool aKWRNyxhip = false;
      bool ifJdbTRnjW = false;
      bool ZsCtXxFZwD = false;
      bool ebqjhTRAIM = false;
      bool MzcKassbSP = false;
      bool IYPJkgIbsQ = false;
      bool rXleLGoYwI = false;
      bool BReXKZQqTe = false;
      bool DcGftFMgzA = false;
      bool KpGrTnMxzT = false;
      bool ETeKNqtqzK = false;
      bool QQIONOQFkF = false;
      bool tHZwxLKmEV = false;
      bool MSrzaixwRD = false;
      bool LUhoisgrdE = false;
      bool WGMtZwtiMC = false;
      string rizmuRpIad;
      string WLtMCREnLB;
      string YWhrTSjdJD;
      string JHkuPryacK;
      string wGwAIKaUAm;
      string QrJlSVAHTc;
      string hLzXUPZywK;
      string TcKBFSZhiI;
      string rOcWmQxzct;
      string rpHAckHXes;
      string jbYpSmhIgA;
      string uSXKkShbjE;
      string RaVBRcVKXT;
      string KCCpYPplDA;
      string inRbzYRxPJ;
      string CemaaJFWYp;
      string QWkMosQhlU;
      string cuYjVcIsBr;
      string LYtNRfOaPO;
      string KSNNiLDFmG;
      if(rizmuRpIad == jbYpSmhIgA){IjKtgGFDEx = true;}
      else if(jbYpSmhIgA == rizmuRpIad){rXleLGoYwI = true;}
      if(WLtMCREnLB == uSXKkShbjE){ALUfdrbXuI = true;}
      else if(uSXKkShbjE == WLtMCREnLB){BReXKZQqTe = true;}
      if(YWhrTSjdJD == RaVBRcVKXT){doRWKKgLBK = true;}
      else if(RaVBRcVKXT == YWhrTSjdJD){DcGftFMgzA = true;}
      if(JHkuPryacK == KCCpYPplDA){YDGujaNzfK = true;}
      else if(KCCpYPplDA == JHkuPryacK){KpGrTnMxzT = true;}
      if(wGwAIKaUAm == inRbzYRxPJ){aKWRNyxhip = true;}
      else if(inRbzYRxPJ == wGwAIKaUAm){ETeKNqtqzK = true;}
      if(QrJlSVAHTc == CemaaJFWYp){ifJdbTRnjW = true;}
      else if(CemaaJFWYp == QrJlSVAHTc){QQIONOQFkF = true;}
      if(hLzXUPZywK == QWkMosQhlU){ZsCtXxFZwD = true;}
      else if(QWkMosQhlU == hLzXUPZywK){tHZwxLKmEV = true;}
      if(TcKBFSZhiI == cuYjVcIsBr){ebqjhTRAIM = true;}
      if(rOcWmQxzct == LYtNRfOaPO){MzcKassbSP = true;}
      if(rpHAckHXes == KSNNiLDFmG){IYPJkgIbsQ = true;}
      while(cuYjVcIsBr == TcKBFSZhiI){MSrzaixwRD = true;}
      while(LYtNRfOaPO == LYtNRfOaPO){LUhoisgrdE = true;}
      while(KSNNiLDFmG == KSNNiLDFmG){WGMtZwtiMC = true;}
      if(IjKtgGFDEx == true){IjKtgGFDEx = false;}
      if(ALUfdrbXuI == true){ALUfdrbXuI = false;}
      if(doRWKKgLBK == true){doRWKKgLBK = false;}
      if(YDGujaNzfK == true){YDGujaNzfK = false;}
      if(aKWRNyxhip == true){aKWRNyxhip = false;}
      if(ifJdbTRnjW == true){ifJdbTRnjW = false;}
      if(ZsCtXxFZwD == true){ZsCtXxFZwD = false;}
      if(ebqjhTRAIM == true){ebqjhTRAIM = false;}
      if(MzcKassbSP == true){MzcKassbSP = false;}
      if(IYPJkgIbsQ == true){IYPJkgIbsQ = false;}
      if(rXleLGoYwI == true){rXleLGoYwI = false;}
      if(BReXKZQqTe == true){BReXKZQqTe = false;}
      if(DcGftFMgzA == true){DcGftFMgzA = false;}
      if(KpGrTnMxzT == true){KpGrTnMxzT = false;}
      if(ETeKNqtqzK == true){ETeKNqtqzK = false;}
      if(QQIONOQFkF == true){QQIONOQFkF = false;}
      if(tHZwxLKmEV == true){tHZwxLKmEV = false;}
      if(MSrzaixwRD == true){MSrzaixwRD = false;}
      if(LUhoisgrdE == true){LUhoisgrdE = false;}
      if(WGMtZwtiMC == true){WGMtZwtiMC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTAYNTSUOI
{ 
  void gXWHXStIZX()
  { 
      bool IWDnsMxSnA = false;
      bool XVlzNZbnpx = false;
      bool clOqLstktc = false;
      bool DDiYRaDsZL = false;
      bool gtqpgtEMzK = false;
      bool iWyqzWILcA = false;
      bool RMYLxUlNhl = false;
      bool VhNeQhuYJQ = false;
      bool ngkisfEqYt = false;
      bool RrPZtTVfrM = false;
      bool HqeNoAJTaQ = false;
      bool bjBLMjboRR = false;
      bool PunmTdSnjw = false;
      bool MOfxIwCWts = false;
      bool VkPIShpDNJ = false;
      bool rfNZwMDqsL = false;
      bool hVidEMDEDP = false;
      bool hEuYweefUl = false;
      bool mOaaEfBGAw = false;
      bool sKdiKABkDG = false;
      string GZfAKiDxQS;
      string mfXLPVoeqh;
      string uAJOAhfrOP;
      string ibYPYOFQex;
      string aBuSJSptcC;
      string LHAOwFPQzc;
      string CKiBiKGIlA;
      string PXAsHsFqFh;
      string qlPLEbbKTS;
      string znRBtPStjy;
      string MhHbmmHHGC;
      string AYLRkPuWwH;
      string iwnTBaGyyr;
      string aKHGUJemYR;
      string TTDQRaczQd;
      string TuxbPPsnaL;
      string gJIObpRFwb;
      string kHyemOrXBa;
      string yGhTXeMeqF;
      string PqMMjKLoob;
      if(GZfAKiDxQS == MhHbmmHHGC){IWDnsMxSnA = true;}
      else if(MhHbmmHHGC == GZfAKiDxQS){HqeNoAJTaQ = true;}
      if(mfXLPVoeqh == AYLRkPuWwH){XVlzNZbnpx = true;}
      else if(AYLRkPuWwH == mfXLPVoeqh){bjBLMjboRR = true;}
      if(uAJOAhfrOP == iwnTBaGyyr){clOqLstktc = true;}
      else if(iwnTBaGyyr == uAJOAhfrOP){PunmTdSnjw = true;}
      if(ibYPYOFQex == aKHGUJemYR){DDiYRaDsZL = true;}
      else if(aKHGUJemYR == ibYPYOFQex){MOfxIwCWts = true;}
      if(aBuSJSptcC == TTDQRaczQd){gtqpgtEMzK = true;}
      else if(TTDQRaczQd == aBuSJSptcC){VkPIShpDNJ = true;}
      if(LHAOwFPQzc == TuxbPPsnaL){iWyqzWILcA = true;}
      else if(TuxbPPsnaL == LHAOwFPQzc){rfNZwMDqsL = true;}
      if(CKiBiKGIlA == gJIObpRFwb){RMYLxUlNhl = true;}
      else if(gJIObpRFwb == CKiBiKGIlA){hVidEMDEDP = true;}
      if(PXAsHsFqFh == kHyemOrXBa){VhNeQhuYJQ = true;}
      if(qlPLEbbKTS == yGhTXeMeqF){ngkisfEqYt = true;}
      if(znRBtPStjy == PqMMjKLoob){RrPZtTVfrM = true;}
      while(kHyemOrXBa == PXAsHsFqFh){hEuYweefUl = true;}
      while(yGhTXeMeqF == yGhTXeMeqF){mOaaEfBGAw = true;}
      while(PqMMjKLoob == PqMMjKLoob){sKdiKABkDG = true;}
      if(IWDnsMxSnA == true){IWDnsMxSnA = false;}
      if(XVlzNZbnpx == true){XVlzNZbnpx = false;}
      if(clOqLstktc == true){clOqLstktc = false;}
      if(DDiYRaDsZL == true){DDiYRaDsZL = false;}
      if(gtqpgtEMzK == true){gtqpgtEMzK = false;}
      if(iWyqzWILcA == true){iWyqzWILcA = false;}
      if(RMYLxUlNhl == true){RMYLxUlNhl = false;}
      if(VhNeQhuYJQ == true){VhNeQhuYJQ = false;}
      if(ngkisfEqYt == true){ngkisfEqYt = false;}
      if(RrPZtTVfrM == true){RrPZtTVfrM = false;}
      if(HqeNoAJTaQ == true){HqeNoAJTaQ = false;}
      if(bjBLMjboRR == true){bjBLMjboRR = false;}
      if(PunmTdSnjw == true){PunmTdSnjw = false;}
      if(MOfxIwCWts == true){MOfxIwCWts = false;}
      if(VkPIShpDNJ == true){VkPIShpDNJ = false;}
      if(rfNZwMDqsL == true){rfNZwMDqsL = false;}
      if(hVidEMDEDP == true){hVidEMDEDP = false;}
      if(hEuYweefUl == true){hEuYweefUl = false;}
      if(mOaaEfBGAw == true){mOaaEfBGAw = false;}
      if(sKdiKABkDG == true){sKdiKABkDG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PULOGWMSAP
{ 
  void nULmOFZdpp()
  { 
      bool BathVlVjFd = false;
      bool VxTtZsMsOH = false;
      bool EErDPbjupz = false;
      bool iShKMISJVd = false;
      bool VHQZSXNYaL = false;
      bool QqrSLxipSs = false;
      bool BatFtCPIgQ = false;
      bool ZDXjkxmSkq = false;
      bool OKUdhraOzO = false;
      bool ZcqbcuMKfP = false;
      bool IErJlNTHhO = false;
      bool JQEaeqGQWC = false;
      bool bAJSpxLuHp = false;
      bool jclViJSKrU = false;
      bool YSgjFJXPxk = false;
      bool nwmdmItYTn = false;
      bool BXArdgdirU = false;
      bool XuXCdJTZMf = false;
      bool ZwyVBnoIhZ = false;
      bool PsqDSARoFX = false;
      string xuuNHTZQJd;
      string sXygjxBJED;
      string sTOCpbTUel;
      string OYldKmQlOQ;
      string aKJMKuJGtA;
      string TMuNscgrXf;
      string zFkXPUlTVw;
      string gOumbiJBrt;
      string RNZeRBdYkg;
      string GXOhRVYlwo;
      string JojyTFRHkK;
      string TezcNlfGGN;
      string qNiooIzMVG;
      string KWECkbcbKL;
      string jVmaMbXlUe;
      string oReiywGuIK;
      string GFkezwZxrl;
      string JDuudUaIbN;
      string jMrqQrrVEn;
      string VgTAFdkHaQ;
      if(xuuNHTZQJd == JojyTFRHkK){BathVlVjFd = true;}
      else if(JojyTFRHkK == xuuNHTZQJd){IErJlNTHhO = true;}
      if(sXygjxBJED == TezcNlfGGN){VxTtZsMsOH = true;}
      else if(TezcNlfGGN == sXygjxBJED){JQEaeqGQWC = true;}
      if(sTOCpbTUel == qNiooIzMVG){EErDPbjupz = true;}
      else if(qNiooIzMVG == sTOCpbTUel){bAJSpxLuHp = true;}
      if(OYldKmQlOQ == KWECkbcbKL){iShKMISJVd = true;}
      else if(KWECkbcbKL == OYldKmQlOQ){jclViJSKrU = true;}
      if(aKJMKuJGtA == jVmaMbXlUe){VHQZSXNYaL = true;}
      else if(jVmaMbXlUe == aKJMKuJGtA){YSgjFJXPxk = true;}
      if(TMuNscgrXf == oReiywGuIK){QqrSLxipSs = true;}
      else if(oReiywGuIK == TMuNscgrXf){nwmdmItYTn = true;}
      if(zFkXPUlTVw == GFkezwZxrl){BatFtCPIgQ = true;}
      else if(GFkezwZxrl == zFkXPUlTVw){BXArdgdirU = true;}
      if(gOumbiJBrt == JDuudUaIbN){ZDXjkxmSkq = true;}
      if(RNZeRBdYkg == jMrqQrrVEn){OKUdhraOzO = true;}
      if(GXOhRVYlwo == VgTAFdkHaQ){ZcqbcuMKfP = true;}
      while(JDuudUaIbN == gOumbiJBrt){XuXCdJTZMf = true;}
      while(jMrqQrrVEn == jMrqQrrVEn){ZwyVBnoIhZ = true;}
      while(VgTAFdkHaQ == VgTAFdkHaQ){PsqDSARoFX = true;}
      if(BathVlVjFd == true){BathVlVjFd = false;}
      if(VxTtZsMsOH == true){VxTtZsMsOH = false;}
      if(EErDPbjupz == true){EErDPbjupz = false;}
      if(iShKMISJVd == true){iShKMISJVd = false;}
      if(VHQZSXNYaL == true){VHQZSXNYaL = false;}
      if(QqrSLxipSs == true){QqrSLxipSs = false;}
      if(BatFtCPIgQ == true){BatFtCPIgQ = false;}
      if(ZDXjkxmSkq == true){ZDXjkxmSkq = false;}
      if(OKUdhraOzO == true){OKUdhraOzO = false;}
      if(ZcqbcuMKfP == true){ZcqbcuMKfP = false;}
      if(IErJlNTHhO == true){IErJlNTHhO = false;}
      if(JQEaeqGQWC == true){JQEaeqGQWC = false;}
      if(bAJSpxLuHp == true){bAJSpxLuHp = false;}
      if(jclViJSKrU == true){jclViJSKrU = false;}
      if(YSgjFJXPxk == true){YSgjFJXPxk = false;}
      if(nwmdmItYTn == true){nwmdmItYTn = false;}
      if(BXArdgdirU == true){BXArdgdirU = false;}
      if(XuXCdJTZMf == true){XuXCdJTZMf = false;}
      if(ZwyVBnoIhZ == true){ZwyVBnoIhZ = false;}
      if(PsqDSARoFX == true){PsqDSARoFX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDJWAHIGRE
{ 
  void uagcPadVtj()
  { 
      bool lQhneGDEOm = false;
      bool zryZEHdAFR = false;
      bool pINmqCQnot = false;
      bool jNJLOCYIPO = false;
      bool fbKSgCVnxR = false;
      bool KRkfgdDuwc = false;
      bool oOPUClimLC = false;
      bool hVjqlOxuFo = false;
      bool gcqXiSbddk = false;
      bool ydMmYQMoPu = false;
      bool ThctjngssS = false;
      bool fIpHwMXqkj = false;
      bool JEJZDDJxRV = false;
      bool BIeJUyzwnt = false;
      bool khkLFpnEqM = false;
      bool rUDfkOYCqf = false;
      bool ejbXQWcglx = false;
      bool MbDqybTxUN = false;
      bool PEGFcfFyXF = false;
      bool ZxFHOBGMth = false;
      string GDDRWNbwPJ;
      string HJPPnRkbrW;
      string HJelDlZWeA;
      string ufpkQwPUtQ;
      string KXlLiskKld;
      string ngVrKwYQOj;
      string nEQPOaTeyq;
      string CPhaLiXTCK;
      string BOjBMOJxZT;
      string XyGJcFHWxH;
      string YFLubXytfb;
      string YENEiZUOCz;
      string RVFdTDJXyF;
      string aAWukuCoZn;
      string PORyuSjBaC;
      string krTxpDAhaX;
      string OawZAXgSTm;
      string WeoOiCEHiA;
      string THwuUigYFg;
      string uUOBYoSqxX;
      if(GDDRWNbwPJ == YFLubXytfb){lQhneGDEOm = true;}
      else if(YFLubXytfb == GDDRWNbwPJ){ThctjngssS = true;}
      if(HJPPnRkbrW == YENEiZUOCz){zryZEHdAFR = true;}
      else if(YENEiZUOCz == HJPPnRkbrW){fIpHwMXqkj = true;}
      if(HJelDlZWeA == RVFdTDJXyF){pINmqCQnot = true;}
      else if(RVFdTDJXyF == HJelDlZWeA){JEJZDDJxRV = true;}
      if(ufpkQwPUtQ == aAWukuCoZn){jNJLOCYIPO = true;}
      else if(aAWukuCoZn == ufpkQwPUtQ){BIeJUyzwnt = true;}
      if(KXlLiskKld == PORyuSjBaC){fbKSgCVnxR = true;}
      else if(PORyuSjBaC == KXlLiskKld){khkLFpnEqM = true;}
      if(ngVrKwYQOj == krTxpDAhaX){KRkfgdDuwc = true;}
      else if(krTxpDAhaX == ngVrKwYQOj){rUDfkOYCqf = true;}
      if(nEQPOaTeyq == OawZAXgSTm){oOPUClimLC = true;}
      else if(OawZAXgSTm == nEQPOaTeyq){ejbXQWcglx = true;}
      if(CPhaLiXTCK == WeoOiCEHiA){hVjqlOxuFo = true;}
      if(BOjBMOJxZT == THwuUigYFg){gcqXiSbddk = true;}
      if(XyGJcFHWxH == uUOBYoSqxX){ydMmYQMoPu = true;}
      while(WeoOiCEHiA == CPhaLiXTCK){MbDqybTxUN = true;}
      while(THwuUigYFg == THwuUigYFg){PEGFcfFyXF = true;}
      while(uUOBYoSqxX == uUOBYoSqxX){ZxFHOBGMth = true;}
      if(lQhneGDEOm == true){lQhneGDEOm = false;}
      if(zryZEHdAFR == true){zryZEHdAFR = false;}
      if(pINmqCQnot == true){pINmqCQnot = false;}
      if(jNJLOCYIPO == true){jNJLOCYIPO = false;}
      if(fbKSgCVnxR == true){fbKSgCVnxR = false;}
      if(KRkfgdDuwc == true){KRkfgdDuwc = false;}
      if(oOPUClimLC == true){oOPUClimLC = false;}
      if(hVjqlOxuFo == true){hVjqlOxuFo = false;}
      if(gcqXiSbddk == true){gcqXiSbddk = false;}
      if(ydMmYQMoPu == true){ydMmYQMoPu = false;}
      if(ThctjngssS == true){ThctjngssS = false;}
      if(fIpHwMXqkj == true){fIpHwMXqkj = false;}
      if(JEJZDDJxRV == true){JEJZDDJxRV = false;}
      if(BIeJUyzwnt == true){BIeJUyzwnt = false;}
      if(khkLFpnEqM == true){khkLFpnEqM = false;}
      if(rUDfkOYCqf == true){rUDfkOYCqf = false;}
      if(ejbXQWcglx == true){ejbXQWcglx = false;}
      if(MbDqybTxUN == true){MbDqybTxUN = false;}
      if(PEGFcfFyXF == true){PEGFcfFyXF = false;}
      if(ZxFHOBGMth == true){ZxFHOBGMth = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VMRCVQOWKI
{ 
  void FKQUIRVpgX()
  { 
      bool BAiUhnlzNc = false;
      bool sTiHxTHjci = false;
      bool EhOhlTsZsC = false;
      bool xcFaMYNjyh = false;
      bool yDOlZgRUhl = false;
      bool EmkudSkBhN = false;
      bool uLFLfPOHuX = false;
      bool GWltjATbIF = false;
      bool CXrHxJrJxs = false;
      bool nLBjmlyDFJ = false;
      bool RKZKehBpKc = false;
      bool zJscLWTyNW = false;
      bool WFJBjtUCHy = false;
      bool CPWymqygbP = false;
      bool ICyTteSYYP = false;
      bool SzpilMAYZk = false;
      bool MzhMailtoT = false;
      bool YlWxOUHoHF = false;
      bool bucqeCZmLa = false;
      bool qZHqCIUksK = false;
      string OKnXpWLTiX;
      string ibzdZLJCOB;
      string WhWZaFYyfq;
      string mlgWeTklmO;
      string qpLAEiNoDB;
      string VozobfnOwk;
      string xNnqjwubyG;
      string ZXPzJfWVVq;
      string qjtdVxmqtz;
      string eWoCQdCUPH;
      string nlqwayZzew;
      string JRrEsNTJVm;
      string JDhzaDhNif;
      string cBGNDFrxDW;
      string XnMxoNdkIC;
      string JrycyjDrUW;
      string QLPySHLdBn;
      string UVGzOUqjJN;
      string ZxEfVjDcPS;
      string BAbfFLXNeh;
      if(OKnXpWLTiX == nlqwayZzew){BAiUhnlzNc = true;}
      else if(nlqwayZzew == OKnXpWLTiX){RKZKehBpKc = true;}
      if(ibzdZLJCOB == JRrEsNTJVm){sTiHxTHjci = true;}
      else if(JRrEsNTJVm == ibzdZLJCOB){zJscLWTyNW = true;}
      if(WhWZaFYyfq == JDhzaDhNif){EhOhlTsZsC = true;}
      else if(JDhzaDhNif == WhWZaFYyfq){WFJBjtUCHy = true;}
      if(mlgWeTklmO == cBGNDFrxDW){xcFaMYNjyh = true;}
      else if(cBGNDFrxDW == mlgWeTklmO){CPWymqygbP = true;}
      if(qpLAEiNoDB == XnMxoNdkIC){yDOlZgRUhl = true;}
      else if(XnMxoNdkIC == qpLAEiNoDB){ICyTteSYYP = true;}
      if(VozobfnOwk == JrycyjDrUW){EmkudSkBhN = true;}
      else if(JrycyjDrUW == VozobfnOwk){SzpilMAYZk = true;}
      if(xNnqjwubyG == QLPySHLdBn){uLFLfPOHuX = true;}
      else if(QLPySHLdBn == xNnqjwubyG){MzhMailtoT = true;}
      if(ZXPzJfWVVq == UVGzOUqjJN){GWltjATbIF = true;}
      if(qjtdVxmqtz == ZxEfVjDcPS){CXrHxJrJxs = true;}
      if(eWoCQdCUPH == BAbfFLXNeh){nLBjmlyDFJ = true;}
      while(UVGzOUqjJN == ZXPzJfWVVq){YlWxOUHoHF = true;}
      while(ZxEfVjDcPS == ZxEfVjDcPS){bucqeCZmLa = true;}
      while(BAbfFLXNeh == BAbfFLXNeh){qZHqCIUksK = true;}
      if(BAiUhnlzNc == true){BAiUhnlzNc = false;}
      if(sTiHxTHjci == true){sTiHxTHjci = false;}
      if(EhOhlTsZsC == true){EhOhlTsZsC = false;}
      if(xcFaMYNjyh == true){xcFaMYNjyh = false;}
      if(yDOlZgRUhl == true){yDOlZgRUhl = false;}
      if(EmkudSkBhN == true){EmkudSkBhN = false;}
      if(uLFLfPOHuX == true){uLFLfPOHuX = false;}
      if(GWltjATbIF == true){GWltjATbIF = false;}
      if(CXrHxJrJxs == true){CXrHxJrJxs = false;}
      if(nLBjmlyDFJ == true){nLBjmlyDFJ = false;}
      if(RKZKehBpKc == true){RKZKehBpKc = false;}
      if(zJscLWTyNW == true){zJscLWTyNW = false;}
      if(WFJBjtUCHy == true){WFJBjtUCHy = false;}
      if(CPWymqygbP == true){CPWymqygbP = false;}
      if(ICyTteSYYP == true){ICyTteSYYP = false;}
      if(SzpilMAYZk == true){SzpilMAYZk = false;}
      if(MzhMailtoT == true){MzhMailtoT = false;}
      if(YlWxOUHoHF == true){YlWxOUHoHF = false;}
      if(bucqeCZmLa == true){bucqeCZmLa = false;}
      if(qZHqCIUksK == true){qZHqCIUksK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBOXISTMTD
{ 
  void CCiALatrtA()
  { 
      bool hudBpZSssV = false;
      bool hHQWKDoCwU = false;
      bool ATYabctsYc = false;
      bool xRMJYlFmfH = false;
      bool MNOrxCwIOW = false;
      bool tlVCxOWCZM = false;
      bool eYTQYPtGxX = false;
      bool yCWnIlEfdY = false;
      bool fleCiKuKMJ = false;
      bool PCNSbmsyTg = false;
      bool HpKqYrPhtK = false;
      bool JpYAgstRhN = false;
      bool TjtnHuoDLV = false;
      bool sGMxRpamcp = false;
      bool uNPBAYdMli = false;
      bool rbQFMWuWic = false;
      bool DLVXRDdbip = false;
      bool SHnqSGTrni = false;
      bool RbQcdQpHjt = false;
      bool tDEzmjrrjw = false;
      string IVSmDcLLVo;
      string QYAyLyChRq;
      string bugbkIeVym;
      string obkAZqlrZG;
      string ZloiwmCJQW;
      string RRmcJNopCu;
      string xoNiAnnAYU;
      string MJILRpGxex;
      string FVFbUXoHqM;
      string CuodIjXGiH;
      string zCjwJHIbLS;
      string GqLEpbjkNb;
      string zfJMRRUdCh;
      string RzOXyDkJRN;
      string ONwXFKikng;
      string AlsGISsXdr;
      string meYdAHbnGl;
      string pZTzMljkHH;
      string hioVgeGIOe;
      string KNeZajnSXx;
      if(IVSmDcLLVo == zCjwJHIbLS){hudBpZSssV = true;}
      else if(zCjwJHIbLS == IVSmDcLLVo){HpKqYrPhtK = true;}
      if(QYAyLyChRq == GqLEpbjkNb){hHQWKDoCwU = true;}
      else if(GqLEpbjkNb == QYAyLyChRq){JpYAgstRhN = true;}
      if(bugbkIeVym == zfJMRRUdCh){ATYabctsYc = true;}
      else if(zfJMRRUdCh == bugbkIeVym){TjtnHuoDLV = true;}
      if(obkAZqlrZG == RzOXyDkJRN){xRMJYlFmfH = true;}
      else if(RzOXyDkJRN == obkAZqlrZG){sGMxRpamcp = true;}
      if(ZloiwmCJQW == ONwXFKikng){MNOrxCwIOW = true;}
      else if(ONwXFKikng == ZloiwmCJQW){uNPBAYdMli = true;}
      if(RRmcJNopCu == AlsGISsXdr){tlVCxOWCZM = true;}
      else if(AlsGISsXdr == RRmcJNopCu){rbQFMWuWic = true;}
      if(xoNiAnnAYU == meYdAHbnGl){eYTQYPtGxX = true;}
      else if(meYdAHbnGl == xoNiAnnAYU){DLVXRDdbip = true;}
      if(MJILRpGxex == pZTzMljkHH){yCWnIlEfdY = true;}
      if(FVFbUXoHqM == hioVgeGIOe){fleCiKuKMJ = true;}
      if(CuodIjXGiH == KNeZajnSXx){PCNSbmsyTg = true;}
      while(pZTzMljkHH == MJILRpGxex){SHnqSGTrni = true;}
      while(hioVgeGIOe == hioVgeGIOe){RbQcdQpHjt = true;}
      while(KNeZajnSXx == KNeZajnSXx){tDEzmjrrjw = true;}
      if(hudBpZSssV == true){hudBpZSssV = false;}
      if(hHQWKDoCwU == true){hHQWKDoCwU = false;}
      if(ATYabctsYc == true){ATYabctsYc = false;}
      if(xRMJYlFmfH == true){xRMJYlFmfH = false;}
      if(MNOrxCwIOW == true){MNOrxCwIOW = false;}
      if(tlVCxOWCZM == true){tlVCxOWCZM = false;}
      if(eYTQYPtGxX == true){eYTQYPtGxX = false;}
      if(yCWnIlEfdY == true){yCWnIlEfdY = false;}
      if(fleCiKuKMJ == true){fleCiKuKMJ = false;}
      if(PCNSbmsyTg == true){PCNSbmsyTg = false;}
      if(HpKqYrPhtK == true){HpKqYrPhtK = false;}
      if(JpYAgstRhN == true){JpYAgstRhN = false;}
      if(TjtnHuoDLV == true){TjtnHuoDLV = false;}
      if(sGMxRpamcp == true){sGMxRpamcp = false;}
      if(uNPBAYdMli == true){uNPBAYdMli = false;}
      if(rbQFMWuWic == true){rbQFMWuWic = false;}
      if(DLVXRDdbip == true){DLVXRDdbip = false;}
      if(SHnqSGTrni == true){SHnqSGTrni = false;}
      if(RbQcdQpHjt == true){RbQcdQpHjt = false;}
      if(tDEzmjrrjw == true){tDEzmjrrjw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKTPQNYIGX
{ 
  void PBufcBmHcr()
  { 
      bool IXWONZNTqM = false;
      bool FuPpNZdQTX = false;
      bool pudJsrOfGB = false;
      bool sPChBPFqkh = false;
      bool OVORREZZuf = false;
      bool dpUGMMtMVV = false;
      bool LhNpSpsgoy = false;
      bool UlfkITgMrn = false;
      bool RnkZWDtwVo = false;
      bool VrVOWgIXya = false;
      bool KskxLrKjxr = false;
      bool egUgEWxmSP = false;
      bool uwKzccPQOb = false;
      bool KINRdYDnOe = false;
      bool sKzdJnXoKA = false;
      bool jVFifNhkTh = false;
      bool bsVVgWTDCe = false;
      bool TJXnWkxgpn = false;
      bool FaGOroDdkP = false;
      bool pRTfCzodwl = false;
      string ddlCGUagqV;
      string IssbdDxDRB;
      string RwIMXVlsBb;
      string cFPYToExMC;
      string jiTwmJGbIU;
      string imYIOgVYdj;
      string igfPrDdUHn;
      string zApOQhcLZO;
      string OKkfrpgHJm;
      string TeTcTCCEEi;
      string flTTVixKqf;
      string EJzPUXwzWC;
      string WVKTTTfNtO;
      string fXHphbpQKJ;
      string rVQdiKfEHu;
      string FDgBMKbAAB;
      string CjPbAfBIgs;
      string heoNJAEfkJ;
      string mbFyIcpGdW;
      string AoQIGIGndC;
      if(ddlCGUagqV == flTTVixKqf){IXWONZNTqM = true;}
      else if(flTTVixKqf == ddlCGUagqV){KskxLrKjxr = true;}
      if(IssbdDxDRB == EJzPUXwzWC){FuPpNZdQTX = true;}
      else if(EJzPUXwzWC == IssbdDxDRB){egUgEWxmSP = true;}
      if(RwIMXVlsBb == WVKTTTfNtO){pudJsrOfGB = true;}
      else if(WVKTTTfNtO == RwIMXVlsBb){uwKzccPQOb = true;}
      if(cFPYToExMC == fXHphbpQKJ){sPChBPFqkh = true;}
      else if(fXHphbpQKJ == cFPYToExMC){KINRdYDnOe = true;}
      if(jiTwmJGbIU == rVQdiKfEHu){OVORREZZuf = true;}
      else if(rVQdiKfEHu == jiTwmJGbIU){sKzdJnXoKA = true;}
      if(imYIOgVYdj == FDgBMKbAAB){dpUGMMtMVV = true;}
      else if(FDgBMKbAAB == imYIOgVYdj){jVFifNhkTh = true;}
      if(igfPrDdUHn == CjPbAfBIgs){LhNpSpsgoy = true;}
      else if(CjPbAfBIgs == igfPrDdUHn){bsVVgWTDCe = true;}
      if(zApOQhcLZO == heoNJAEfkJ){UlfkITgMrn = true;}
      if(OKkfrpgHJm == mbFyIcpGdW){RnkZWDtwVo = true;}
      if(TeTcTCCEEi == AoQIGIGndC){VrVOWgIXya = true;}
      while(heoNJAEfkJ == zApOQhcLZO){TJXnWkxgpn = true;}
      while(mbFyIcpGdW == mbFyIcpGdW){FaGOroDdkP = true;}
      while(AoQIGIGndC == AoQIGIGndC){pRTfCzodwl = true;}
      if(IXWONZNTqM == true){IXWONZNTqM = false;}
      if(FuPpNZdQTX == true){FuPpNZdQTX = false;}
      if(pudJsrOfGB == true){pudJsrOfGB = false;}
      if(sPChBPFqkh == true){sPChBPFqkh = false;}
      if(OVORREZZuf == true){OVORREZZuf = false;}
      if(dpUGMMtMVV == true){dpUGMMtMVV = false;}
      if(LhNpSpsgoy == true){LhNpSpsgoy = false;}
      if(UlfkITgMrn == true){UlfkITgMrn = false;}
      if(RnkZWDtwVo == true){RnkZWDtwVo = false;}
      if(VrVOWgIXya == true){VrVOWgIXya = false;}
      if(KskxLrKjxr == true){KskxLrKjxr = false;}
      if(egUgEWxmSP == true){egUgEWxmSP = false;}
      if(uwKzccPQOb == true){uwKzccPQOb = false;}
      if(KINRdYDnOe == true){KINRdYDnOe = false;}
      if(sKzdJnXoKA == true){sKzdJnXoKA = false;}
      if(jVFifNhkTh == true){jVFifNhkTh = false;}
      if(bsVVgWTDCe == true){bsVVgWTDCe = false;}
      if(TJXnWkxgpn == true){TJXnWkxgpn = false;}
      if(FaGOroDdkP == true){FaGOroDdkP = false;}
      if(pRTfCzodwl == true){pRTfCzodwl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRFZZPOOTY
{ 
  void qdfRiOhusA()
  { 
      bool IyiWZqOjfA = false;
      bool gBjFUeQuYn = false;
      bool bGiOYXYckM = false;
      bool LwxIuXbLLD = false;
      bool jySspIAuGV = false;
      bool TnmaYCPUxC = false;
      bool RlzSojDbJw = false;
      bool DEjUEdmpYQ = false;
      bool WcVPsWJWjs = false;
      bool IGNJkyzzEF = false;
      bool EYkJROERWt = false;
      bool PYugeoPjZR = false;
      bool ZgrQnxpaiF = false;
      bool dnlTLyrMxd = false;
      bool SrzociLgew = false;
      bool hOYleXfTVU = false;
      bool YchQPambUf = false;
      bool xDlwzhgCmE = false;
      bool lJumXPOznn = false;
      bool RXpcFoKiYC = false;
      string aquPGuMUgd;
      string wFkCorNWCr;
      string cBQiXyKknn;
      string SPEPDYDMUI;
      string dWtYnfxPue;
      string YrwsKYaLqH;
      string jbfsKfAUzQ;
      string oBCsNGHrur;
      string BupJOaTLFd;
      string xqUMYCpBNH;
      string ecPdoWoCeD;
      string RiQzGolWdi;
      string MoOVSxgoUL;
      string QGdnMXeLTr;
      string kQfBMOaVFi;
      string QSWdupNtKr;
      string pAgTlLFbli;
      string JZDlyuIMJE;
      string WKiktyizsW;
      string JkBaBkjLOA;
      if(aquPGuMUgd == ecPdoWoCeD){IyiWZqOjfA = true;}
      else if(ecPdoWoCeD == aquPGuMUgd){EYkJROERWt = true;}
      if(wFkCorNWCr == RiQzGolWdi){gBjFUeQuYn = true;}
      else if(RiQzGolWdi == wFkCorNWCr){PYugeoPjZR = true;}
      if(cBQiXyKknn == MoOVSxgoUL){bGiOYXYckM = true;}
      else if(MoOVSxgoUL == cBQiXyKknn){ZgrQnxpaiF = true;}
      if(SPEPDYDMUI == QGdnMXeLTr){LwxIuXbLLD = true;}
      else if(QGdnMXeLTr == SPEPDYDMUI){dnlTLyrMxd = true;}
      if(dWtYnfxPue == kQfBMOaVFi){jySspIAuGV = true;}
      else if(kQfBMOaVFi == dWtYnfxPue){SrzociLgew = true;}
      if(YrwsKYaLqH == QSWdupNtKr){TnmaYCPUxC = true;}
      else if(QSWdupNtKr == YrwsKYaLqH){hOYleXfTVU = true;}
      if(jbfsKfAUzQ == pAgTlLFbli){RlzSojDbJw = true;}
      else if(pAgTlLFbli == jbfsKfAUzQ){YchQPambUf = true;}
      if(oBCsNGHrur == JZDlyuIMJE){DEjUEdmpYQ = true;}
      if(BupJOaTLFd == WKiktyizsW){WcVPsWJWjs = true;}
      if(xqUMYCpBNH == JkBaBkjLOA){IGNJkyzzEF = true;}
      while(JZDlyuIMJE == oBCsNGHrur){xDlwzhgCmE = true;}
      while(WKiktyizsW == WKiktyizsW){lJumXPOznn = true;}
      while(JkBaBkjLOA == JkBaBkjLOA){RXpcFoKiYC = true;}
      if(IyiWZqOjfA == true){IyiWZqOjfA = false;}
      if(gBjFUeQuYn == true){gBjFUeQuYn = false;}
      if(bGiOYXYckM == true){bGiOYXYckM = false;}
      if(LwxIuXbLLD == true){LwxIuXbLLD = false;}
      if(jySspIAuGV == true){jySspIAuGV = false;}
      if(TnmaYCPUxC == true){TnmaYCPUxC = false;}
      if(RlzSojDbJw == true){RlzSojDbJw = false;}
      if(DEjUEdmpYQ == true){DEjUEdmpYQ = false;}
      if(WcVPsWJWjs == true){WcVPsWJWjs = false;}
      if(IGNJkyzzEF == true){IGNJkyzzEF = false;}
      if(EYkJROERWt == true){EYkJROERWt = false;}
      if(PYugeoPjZR == true){PYugeoPjZR = false;}
      if(ZgrQnxpaiF == true){ZgrQnxpaiF = false;}
      if(dnlTLyrMxd == true){dnlTLyrMxd = false;}
      if(SrzociLgew == true){SrzociLgew = false;}
      if(hOYleXfTVU == true){hOYleXfTVU = false;}
      if(YchQPambUf == true){YchQPambUf = false;}
      if(xDlwzhgCmE == true){xDlwzhgCmE = false;}
      if(lJumXPOznn == true){lJumXPOznn = false;}
      if(RXpcFoKiYC == true){RXpcFoKiYC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNZNXOMXIW
{ 
  void dpiYPxjuFt()
  { 
      bool XxgCGlobpM = false;
      bool RpFrMBdpaZ = false;
      bool iGBVaxiCkU = false;
      bool cJEWsVypiV = false;
      bool uyQHPGBdaO = false;
      bool btIbDRwLaJ = false;
      bool DlqVjHlhzq = false;
      bool CmHFdkpsGT = false;
      bool uEaVshBbSa = false;
      bool ZmOZRIGtXH = false;
      bool UTejMnmCyS = false;
      bool aCFHNyLVcB = false;
      bool GJOXQOYgmU = false;
      bool euUyzbZpJE = false;
      bool uydAzWhHLS = false;
      bool xjRWAKEHSx = false;
      bool OFPcnfgGIk = false;
      bool YULXFHfNXt = false;
      bool gRVTXtcyxo = false;
      bool XSXMppiALT = false;
      string sHmaRxNTqm;
      string kfdSaSBjlk;
      string oAeZJlehYw;
      string SLPUCzwAYC;
      string IjVmcoZmnn;
      string zBPMgrcNRe;
      string ReutTYPIQa;
      string VALjcFeqxT;
      string MrskwRwCnJ;
      string WiisjcoaTD;
      string ZRVNRzofia;
      string NkPxSZkJyC;
      string cNTGDlRSzz;
      string QDXttuVfTx;
      string bQTMwlTkZK;
      string qecQZLxPJe;
      string gWfiKJNVDX;
      string DFpAZMtGJR;
      string SfroIkaGUh;
      string xGVnPFjjCm;
      if(sHmaRxNTqm == ZRVNRzofia){XxgCGlobpM = true;}
      else if(ZRVNRzofia == sHmaRxNTqm){UTejMnmCyS = true;}
      if(kfdSaSBjlk == NkPxSZkJyC){RpFrMBdpaZ = true;}
      else if(NkPxSZkJyC == kfdSaSBjlk){aCFHNyLVcB = true;}
      if(oAeZJlehYw == cNTGDlRSzz){iGBVaxiCkU = true;}
      else if(cNTGDlRSzz == oAeZJlehYw){GJOXQOYgmU = true;}
      if(SLPUCzwAYC == QDXttuVfTx){cJEWsVypiV = true;}
      else if(QDXttuVfTx == SLPUCzwAYC){euUyzbZpJE = true;}
      if(IjVmcoZmnn == bQTMwlTkZK){uyQHPGBdaO = true;}
      else if(bQTMwlTkZK == IjVmcoZmnn){uydAzWhHLS = true;}
      if(zBPMgrcNRe == qecQZLxPJe){btIbDRwLaJ = true;}
      else if(qecQZLxPJe == zBPMgrcNRe){xjRWAKEHSx = true;}
      if(ReutTYPIQa == gWfiKJNVDX){DlqVjHlhzq = true;}
      else if(gWfiKJNVDX == ReutTYPIQa){OFPcnfgGIk = true;}
      if(VALjcFeqxT == DFpAZMtGJR){CmHFdkpsGT = true;}
      if(MrskwRwCnJ == SfroIkaGUh){uEaVshBbSa = true;}
      if(WiisjcoaTD == xGVnPFjjCm){ZmOZRIGtXH = true;}
      while(DFpAZMtGJR == VALjcFeqxT){YULXFHfNXt = true;}
      while(SfroIkaGUh == SfroIkaGUh){gRVTXtcyxo = true;}
      while(xGVnPFjjCm == xGVnPFjjCm){XSXMppiALT = true;}
      if(XxgCGlobpM == true){XxgCGlobpM = false;}
      if(RpFrMBdpaZ == true){RpFrMBdpaZ = false;}
      if(iGBVaxiCkU == true){iGBVaxiCkU = false;}
      if(cJEWsVypiV == true){cJEWsVypiV = false;}
      if(uyQHPGBdaO == true){uyQHPGBdaO = false;}
      if(btIbDRwLaJ == true){btIbDRwLaJ = false;}
      if(DlqVjHlhzq == true){DlqVjHlhzq = false;}
      if(CmHFdkpsGT == true){CmHFdkpsGT = false;}
      if(uEaVshBbSa == true){uEaVshBbSa = false;}
      if(ZmOZRIGtXH == true){ZmOZRIGtXH = false;}
      if(UTejMnmCyS == true){UTejMnmCyS = false;}
      if(aCFHNyLVcB == true){aCFHNyLVcB = false;}
      if(GJOXQOYgmU == true){GJOXQOYgmU = false;}
      if(euUyzbZpJE == true){euUyzbZpJE = false;}
      if(uydAzWhHLS == true){uydAzWhHLS = false;}
      if(xjRWAKEHSx == true){xjRWAKEHSx = false;}
      if(OFPcnfgGIk == true){OFPcnfgGIk = false;}
      if(YULXFHfNXt == true){YULXFHfNXt = false;}
      if(gRVTXtcyxo == true){gRVTXtcyxo = false;}
      if(XSXMppiALT == true){XSXMppiALT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFXLKGMETI
{ 
  void iTXzjWImdl()
  { 
      bool iwNuAMCRLM = false;
      bool IepowmBTOV = false;
      bool dKsfbngcST = false;
      bool NAyXgukJQF = false;
      bool KfbqTfyMbD = false;
      bool xZxbXXDhSM = false;
      bool eZzryHgSHA = false;
      bool CqCJKyhCLw = false;
      bool pUBOVmCWzI = false;
      bool qCpEakfjrL = false;
      bool yeEaBFWnQZ = false;
      bool pBVWVKYjVK = false;
      bool FKSzIzByhZ = false;
      bool RyJAyKPZMQ = false;
      bool QOFZRpgThP = false;
      bool MwOgGnMFRC = false;
      bool EYFqHrqVYK = false;
      bool tzWFtpEsgS = false;
      bool RhQSMVibsJ = false;
      bool yKHKMqJORZ = false;
      string XXfgWxsMUO;
      string yZnIUNMQjc;
      string EfpgyIjyMt;
      string qBeZXcNMUa;
      string fSpYDWSHrZ;
      string IppqnqgziN;
      string MuAZXwtOkr;
      string AAuJxkpRda;
      string ocGllAKmkf;
      string uOdHNjSPAG;
      string cEWAZIuftD;
      string BOUHXjoNnW;
      string lGdFwkVnuM;
      string SZQXykGFMd;
      string FdshdgsWid;
      string uEbcTVaREn;
      string lGkgjbywIm;
      string ciBKRHMuaP;
      string rzFRRNxmDc;
      string KoBXqysMxC;
      if(XXfgWxsMUO == cEWAZIuftD){iwNuAMCRLM = true;}
      else if(cEWAZIuftD == XXfgWxsMUO){yeEaBFWnQZ = true;}
      if(yZnIUNMQjc == BOUHXjoNnW){IepowmBTOV = true;}
      else if(BOUHXjoNnW == yZnIUNMQjc){pBVWVKYjVK = true;}
      if(EfpgyIjyMt == lGdFwkVnuM){dKsfbngcST = true;}
      else if(lGdFwkVnuM == EfpgyIjyMt){FKSzIzByhZ = true;}
      if(qBeZXcNMUa == SZQXykGFMd){NAyXgukJQF = true;}
      else if(SZQXykGFMd == qBeZXcNMUa){RyJAyKPZMQ = true;}
      if(fSpYDWSHrZ == FdshdgsWid){KfbqTfyMbD = true;}
      else if(FdshdgsWid == fSpYDWSHrZ){QOFZRpgThP = true;}
      if(IppqnqgziN == uEbcTVaREn){xZxbXXDhSM = true;}
      else if(uEbcTVaREn == IppqnqgziN){MwOgGnMFRC = true;}
      if(MuAZXwtOkr == lGkgjbywIm){eZzryHgSHA = true;}
      else if(lGkgjbywIm == MuAZXwtOkr){EYFqHrqVYK = true;}
      if(AAuJxkpRda == ciBKRHMuaP){CqCJKyhCLw = true;}
      if(ocGllAKmkf == rzFRRNxmDc){pUBOVmCWzI = true;}
      if(uOdHNjSPAG == KoBXqysMxC){qCpEakfjrL = true;}
      while(ciBKRHMuaP == AAuJxkpRda){tzWFtpEsgS = true;}
      while(rzFRRNxmDc == rzFRRNxmDc){RhQSMVibsJ = true;}
      while(KoBXqysMxC == KoBXqysMxC){yKHKMqJORZ = true;}
      if(iwNuAMCRLM == true){iwNuAMCRLM = false;}
      if(IepowmBTOV == true){IepowmBTOV = false;}
      if(dKsfbngcST == true){dKsfbngcST = false;}
      if(NAyXgukJQF == true){NAyXgukJQF = false;}
      if(KfbqTfyMbD == true){KfbqTfyMbD = false;}
      if(xZxbXXDhSM == true){xZxbXXDhSM = false;}
      if(eZzryHgSHA == true){eZzryHgSHA = false;}
      if(CqCJKyhCLw == true){CqCJKyhCLw = false;}
      if(pUBOVmCWzI == true){pUBOVmCWzI = false;}
      if(qCpEakfjrL == true){qCpEakfjrL = false;}
      if(yeEaBFWnQZ == true){yeEaBFWnQZ = false;}
      if(pBVWVKYjVK == true){pBVWVKYjVK = false;}
      if(FKSzIzByhZ == true){FKSzIzByhZ = false;}
      if(RyJAyKPZMQ == true){RyJAyKPZMQ = false;}
      if(QOFZRpgThP == true){QOFZRpgThP = false;}
      if(MwOgGnMFRC == true){MwOgGnMFRC = false;}
      if(EYFqHrqVYK == true){EYFqHrqVYK = false;}
      if(tzWFtpEsgS == true){tzWFtpEsgS = false;}
      if(RhQSMVibsJ == true){RhQSMVibsJ = false;}
      if(yKHKMqJORZ == true){yKHKMqJORZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SBYKLDXQOC
{ 
  void TXwdQPYoZF()
  { 
      bool tDDVkroGns = false;
      bool OLInGRMCIH = false;
      bool rzrzPmRPnQ = false;
      bool tIIuClsJbl = false;
      bool VWmyWzxSZp = false;
      bool xVzhXuLDFx = false;
      bool aZSWyGDNkT = false;
      bool YCaWlULscQ = false;
      bool pyoxTXJZXH = false;
      bool apEdLuEPzP = false;
      bool uigGRuucwC = false;
      bool iRZnHbkUDZ = false;
      bool wcpdrhxwLp = false;
      bool QwsMUGQhfY = false;
      bool cgdUXJPQWi = false;
      bool JiMYTSsCNi = false;
      bool xzQGlmXNSA = false;
      bool KCnexPzUGi = false;
      bool SgZbfgjTsC = false;
      bool NNUxadPXhk = false;
      string beFwVKYLtO;
      string refmxrdAzd;
      string ATcsllyJhB;
      string NpqzzpmBdK;
      string zpPsVeyGLd;
      string cqwNaICMKj;
      string LPdrABnfnH;
      string EbVoeJEjXH;
      string mrxDYWtcYp;
      string naqsyiMWrT;
      string pRREZAUGiQ;
      string ERnCwTRZTc;
      string HKHxSckcqu;
      string xgqEQVZsdX;
      string CntIlVmnwd;
      string RlDPMfKTkw;
      string PrPmSWajka;
      string sYwwaSQyKx;
      string pxfMdLdbqk;
      string KGHgIJYHpP;
      if(beFwVKYLtO == pRREZAUGiQ){tDDVkroGns = true;}
      else if(pRREZAUGiQ == beFwVKYLtO){uigGRuucwC = true;}
      if(refmxrdAzd == ERnCwTRZTc){OLInGRMCIH = true;}
      else if(ERnCwTRZTc == refmxrdAzd){iRZnHbkUDZ = true;}
      if(ATcsllyJhB == HKHxSckcqu){rzrzPmRPnQ = true;}
      else if(HKHxSckcqu == ATcsllyJhB){wcpdrhxwLp = true;}
      if(NpqzzpmBdK == xgqEQVZsdX){tIIuClsJbl = true;}
      else if(xgqEQVZsdX == NpqzzpmBdK){QwsMUGQhfY = true;}
      if(zpPsVeyGLd == CntIlVmnwd){VWmyWzxSZp = true;}
      else if(CntIlVmnwd == zpPsVeyGLd){cgdUXJPQWi = true;}
      if(cqwNaICMKj == RlDPMfKTkw){xVzhXuLDFx = true;}
      else if(RlDPMfKTkw == cqwNaICMKj){JiMYTSsCNi = true;}
      if(LPdrABnfnH == PrPmSWajka){aZSWyGDNkT = true;}
      else if(PrPmSWajka == LPdrABnfnH){xzQGlmXNSA = true;}
      if(EbVoeJEjXH == sYwwaSQyKx){YCaWlULscQ = true;}
      if(mrxDYWtcYp == pxfMdLdbqk){pyoxTXJZXH = true;}
      if(naqsyiMWrT == KGHgIJYHpP){apEdLuEPzP = true;}
      while(sYwwaSQyKx == EbVoeJEjXH){KCnexPzUGi = true;}
      while(pxfMdLdbqk == pxfMdLdbqk){SgZbfgjTsC = true;}
      while(KGHgIJYHpP == KGHgIJYHpP){NNUxadPXhk = true;}
      if(tDDVkroGns == true){tDDVkroGns = false;}
      if(OLInGRMCIH == true){OLInGRMCIH = false;}
      if(rzrzPmRPnQ == true){rzrzPmRPnQ = false;}
      if(tIIuClsJbl == true){tIIuClsJbl = false;}
      if(VWmyWzxSZp == true){VWmyWzxSZp = false;}
      if(xVzhXuLDFx == true){xVzhXuLDFx = false;}
      if(aZSWyGDNkT == true){aZSWyGDNkT = false;}
      if(YCaWlULscQ == true){YCaWlULscQ = false;}
      if(pyoxTXJZXH == true){pyoxTXJZXH = false;}
      if(apEdLuEPzP == true){apEdLuEPzP = false;}
      if(uigGRuucwC == true){uigGRuucwC = false;}
      if(iRZnHbkUDZ == true){iRZnHbkUDZ = false;}
      if(wcpdrhxwLp == true){wcpdrhxwLp = false;}
      if(QwsMUGQhfY == true){QwsMUGQhfY = false;}
      if(cgdUXJPQWi == true){cgdUXJPQWi = false;}
      if(JiMYTSsCNi == true){JiMYTSsCNi = false;}
      if(xzQGlmXNSA == true){xzQGlmXNSA = false;}
      if(KCnexPzUGi == true){KCnexPzUGi = false;}
      if(SgZbfgjTsC == true){SgZbfgjTsC = false;}
      if(NNUxadPXhk == true){NNUxadPXhk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELWSIDSXGJ
{ 
  void lmWCefPgkQ()
  { 
      bool YSAdzbXoce = false;
      bool fcVCPhyjNk = false;
      bool GwsyzXsORA = false;
      bool ZKcEAwnnMz = false;
      bool VqZYHowRAH = false;
      bool CYemWcZBea = false;
      bool hIXbEVAQCT = false;
      bool sKXOPPWTqK = false;
      bool bbOJyBepgX = false;
      bool WmJlQMSxUl = false;
      bool nePgOrBQWG = false;
      bool GFKTyGtOdD = false;
      bool pKiexGAlxC = false;
      bool xYyFWwMhuF = false;
      bool zNSaQQcomK = false;
      bool SETRudukiH = false;
      bool qOTUJhGExB = false;
      bool tMSYDcrINf = false;
      bool cKymjrFgJr = false;
      bool BbymNktxQi = false;
      string NQBxzqkMPV;
      string pkZeZdWflx;
      string rzAOsEICch;
      string DzJmxVRAGj;
      string gOBSsyWjeV;
      string VFyVGOPlEu;
      string ihihSpamhE;
      string LWZBPcxhVt;
      string gXXGMxBngh;
      string FfwKAzfTzD;
      string WjCaKyfwFc;
      string RgPJOLJbVU;
      string nmFzyeaOAQ;
      string xdhSXwUwwN;
      string RFiEQXPlwo;
      string oDxeOjeDce;
      string WQuoemzxlR;
      string pNfHCiEBhZ;
      string OoSLasfCEm;
      string RRTQpBJsYd;
      if(NQBxzqkMPV == WjCaKyfwFc){YSAdzbXoce = true;}
      else if(WjCaKyfwFc == NQBxzqkMPV){nePgOrBQWG = true;}
      if(pkZeZdWflx == RgPJOLJbVU){fcVCPhyjNk = true;}
      else if(RgPJOLJbVU == pkZeZdWflx){GFKTyGtOdD = true;}
      if(rzAOsEICch == nmFzyeaOAQ){GwsyzXsORA = true;}
      else if(nmFzyeaOAQ == rzAOsEICch){pKiexGAlxC = true;}
      if(DzJmxVRAGj == xdhSXwUwwN){ZKcEAwnnMz = true;}
      else if(xdhSXwUwwN == DzJmxVRAGj){xYyFWwMhuF = true;}
      if(gOBSsyWjeV == RFiEQXPlwo){VqZYHowRAH = true;}
      else if(RFiEQXPlwo == gOBSsyWjeV){zNSaQQcomK = true;}
      if(VFyVGOPlEu == oDxeOjeDce){CYemWcZBea = true;}
      else if(oDxeOjeDce == VFyVGOPlEu){SETRudukiH = true;}
      if(ihihSpamhE == WQuoemzxlR){hIXbEVAQCT = true;}
      else if(WQuoemzxlR == ihihSpamhE){qOTUJhGExB = true;}
      if(LWZBPcxhVt == pNfHCiEBhZ){sKXOPPWTqK = true;}
      if(gXXGMxBngh == OoSLasfCEm){bbOJyBepgX = true;}
      if(FfwKAzfTzD == RRTQpBJsYd){WmJlQMSxUl = true;}
      while(pNfHCiEBhZ == LWZBPcxhVt){tMSYDcrINf = true;}
      while(OoSLasfCEm == OoSLasfCEm){cKymjrFgJr = true;}
      while(RRTQpBJsYd == RRTQpBJsYd){BbymNktxQi = true;}
      if(YSAdzbXoce == true){YSAdzbXoce = false;}
      if(fcVCPhyjNk == true){fcVCPhyjNk = false;}
      if(GwsyzXsORA == true){GwsyzXsORA = false;}
      if(ZKcEAwnnMz == true){ZKcEAwnnMz = false;}
      if(VqZYHowRAH == true){VqZYHowRAH = false;}
      if(CYemWcZBea == true){CYemWcZBea = false;}
      if(hIXbEVAQCT == true){hIXbEVAQCT = false;}
      if(sKXOPPWTqK == true){sKXOPPWTqK = false;}
      if(bbOJyBepgX == true){bbOJyBepgX = false;}
      if(WmJlQMSxUl == true){WmJlQMSxUl = false;}
      if(nePgOrBQWG == true){nePgOrBQWG = false;}
      if(GFKTyGtOdD == true){GFKTyGtOdD = false;}
      if(pKiexGAlxC == true){pKiexGAlxC = false;}
      if(xYyFWwMhuF == true){xYyFWwMhuF = false;}
      if(zNSaQQcomK == true){zNSaQQcomK = false;}
      if(SETRudukiH == true){SETRudukiH = false;}
      if(qOTUJhGExB == true){qOTUJhGExB = false;}
      if(tMSYDcrINf == true){tMSYDcrINf = false;}
      if(cKymjrFgJr == true){cKymjrFgJr = false;}
      if(BbymNktxQi == true){BbymNktxQi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIGWYWXDAA
{ 
  void JHIqqCqRCi()
  { 
      bool BcAnzZkUgU = false;
      bool JMyaTmRUNC = false;
      bool gPZstIcyhm = false;
      bool rQgdMJFwas = false;
      bool ONHYxcaADI = false;
      bool mcIbdkDHtq = false;
      bool xlmtbsfUOJ = false;
      bool hUsUmTHAuQ = false;
      bool hbtYzOHEAa = false;
      bool GxBjwbZNwE = false;
      bool xGltaRjnnJ = false;
      bool cCLdIUqNtN = false;
      bool lbTmDjTJYL = false;
      bool ssEqTbpAxg = false;
      bool eTPpxDkXaa = false;
      bool kMTiSVlyqp = false;
      bool yZPcQjxUKg = false;
      bool dqQMhRLdpz = false;
      bool zwixagZVYy = false;
      bool prJGiEDmZN = false;
      string WpuQAUdfPe;
      string TynHhrYjdy;
      string pagYPXHhLG;
      string MnTJTlpIBq;
      string ybarZTsqGr;
      string QtqgVwJVBc;
      string MwUISfddmw;
      string CPhmANzoyu;
      string dQaTpSwlmX;
      string bTHYdBHRYt;
      string pODJoALDgH;
      string xUXGzuVASz;
      string irqPUiHJIz;
      string GgPEFONQdo;
      string GsEfaGwBYh;
      string eGyZKxXmoG;
      string sBuhBPFSAj;
      string hEVdrpmKoN;
      string mFjaTzhosH;
      string pZbXwFxWdK;
      if(WpuQAUdfPe == pODJoALDgH){BcAnzZkUgU = true;}
      else if(pODJoALDgH == WpuQAUdfPe){xGltaRjnnJ = true;}
      if(TynHhrYjdy == xUXGzuVASz){JMyaTmRUNC = true;}
      else if(xUXGzuVASz == TynHhrYjdy){cCLdIUqNtN = true;}
      if(pagYPXHhLG == irqPUiHJIz){gPZstIcyhm = true;}
      else if(irqPUiHJIz == pagYPXHhLG){lbTmDjTJYL = true;}
      if(MnTJTlpIBq == GgPEFONQdo){rQgdMJFwas = true;}
      else if(GgPEFONQdo == MnTJTlpIBq){ssEqTbpAxg = true;}
      if(ybarZTsqGr == GsEfaGwBYh){ONHYxcaADI = true;}
      else if(GsEfaGwBYh == ybarZTsqGr){eTPpxDkXaa = true;}
      if(QtqgVwJVBc == eGyZKxXmoG){mcIbdkDHtq = true;}
      else if(eGyZKxXmoG == QtqgVwJVBc){kMTiSVlyqp = true;}
      if(MwUISfddmw == sBuhBPFSAj){xlmtbsfUOJ = true;}
      else if(sBuhBPFSAj == MwUISfddmw){yZPcQjxUKg = true;}
      if(CPhmANzoyu == hEVdrpmKoN){hUsUmTHAuQ = true;}
      if(dQaTpSwlmX == mFjaTzhosH){hbtYzOHEAa = true;}
      if(bTHYdBHRYt == pZbXwFxWdK){GxBjwbZNwE = true;}
      while(hEVdrpmKoN == CPhmANzoyu){dqQMhRLdpz = true;}
      while(mFjaTzhosH == mFjaTzhosH){zwixagZVYy = true;}
      while(pZbXwFxWdK == pZbXwFxWdK){prJGiEDmZN = true;}
      if(BcAnzZkUgU == true){BcAnzZkUgU = false;}
      if(JMyaTmRUNC == true){JMyaTmRUNC = false;}
      if(gPZstIcyhm == true){gPZstIcyhm = false;}
      if(rQgdMJFwas == true){rQgdMJFwas = false;}
      if(ONHYxcaADI == true){ONHYxcaADI = false;}
      if(mcIbdkDHtq == true){mcIbdkDHtq = false;}
      if(xlmtbsfUOJ == true){xlmtbsfUOJ = false;}
      if(hUsUmTHAuQ == true){hUsUmTHAuQ = false;}
      if(hbtYzOHEAa == true){hbtYzOHEAa = false;}
      if(GxBjwbZNwE == true){GxBjwbZNwE = false;}
      if(xGltaRjnnJ == true){xGltaRjnnJ = false;}
      if(cCLdIUqNtN == true){cCLdIUqNtN = false;}
      if(lbTmDjTJYL == true){lbTmDjTJYL = false;}
      if(ssEqTbpAxg == true){ssEqTbpAxg = false;}
      if(eTPpxDkXaa == true){eTPpxDkXaa = false;}
      if(kMTiSVlyqp == true){kMTiSVlyqp = false;}
      if(yZPcQjxUKg == true){yZPcQjxUKg = false;}
      if(dqQMhRLdpz == true){dqQMhRLdpz = false;}
      if(zwixagZVYy == true){zwixagZVYy = false;}
      if(prJGiEDmZN == true){prJGiEDmZN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDXXNPWBEK
{ 
  void WycYHwURNj()
  { 
      bool EFKDektsMn = false;
      bool csXfByCQXF = false;
      bool BsFUmpcOkR = false;
      bool cGPKaRMfSZ = false;
      bool ieZNphwqjO = false;
      bool bbfWQLApPo = false;
      bool HfHuKWdMFj = false;
      bool kWyyWVSqdF = false;
      bool sldVoBartP = false;
      bool RVPcRDWeCT = false;
      bool DilAcFdgzt = false;
      bool rIMKuVBlFJ = false;
      bool wlSpSPGUfT = false;
      bool ymnJBJzdsi = false;
      bool XsrzWIJEgw = false;
      bool BkZsXQQwhN = false;
      bool yIBfwFTCJl = false;
      bool VXrVkCtSSJ = false;
      bool FCmiSMNtlj = false;
      bool sDufkOrMDQ = false;
      string pttnIUQOwz;
      string IdjEmMHbql;
      string MQAbwYETmn;
      string kUOIFHynej;
      string SheibBSRHV;
      string MiJxmZtSqi;
      string QwbHNnPaye;
      string OTxHSekQzt;
      string GlMQbCKRVe;
      string NewuTVFWUn;
      string lrScHslCeI;
      string ncSxcdjKfL;
      string dxFSQiWBnw;
      string YOwLIOTiJi;
      string PHmMqkMzSo;
      string lupIJnlzLX;
      string VkOhiZfGnO;
      string JAAxwVKrbf;
      string WXiyKcXmBT;
      string bTXlMdrEcR;
      if(pttnIUQOwz == lrScHslCeI){EFKDektsMn = true;}
      else if(lrScHslCeI == pttnIUQOwz){DilAcFdgzt = true;}
      if(IdjEmMHbql == ncSxcdjKfL){csXfByCQXF = true;}
      else if(ncSxcdjKfL == IdjEmMHbql){rIMKuVBlFJ = true;}
      if(MQAbwYETmn == dxFSQiWBnw){BsFUmpcOkR = true;}
      else if(dxFSQiWBnw == MQAbwYETmn){wlSpSPGUfT = true;}
      if(kUOIFHynej == YOwLIOTiJi){cGPKaRMfSZ = true;}
      else if(YOwLIOTiJi == kUOIFHynej){ymnJBJzdsi = true;}
      if(SheibBSRHV == PHmMqkMzSo){ieZNphwqjO = true;}
      else if(PHmMqkMzSo == SheibBSRHV){XsrzWIJEgw = true;}
      if(MiJxmZtSqi == lupIJnlzLX){bbfWQLApPo = true;}
      else if(lupIJnlzLX == MiJxmZtSqi){BkZsXQQwhN = true;}
      if(QwbHNnPaye == VkOhiZfGnO){HfHuKWdMFj = true;}
      else if(VkOhiZfGnO == QwbHNnPaye){yIBfwFTCJl = true;}
      if(OTxHSekQzt == JAAxwVKrbf){kWyyWVSqdF = true;}
      if(GlMQbCKRVe == WXiyKcXmBT){sldVoBartP = true;}
      if(NewuTVFWUn == bTXlMdrEcR){RVPcRDWeCT = true;}
      while(JAAxwVKrbf == OTxHSekQzt){VXrVkCtSSJ = true;}
      while(WXiyKcXmBT == WXiyKcXmBT){FCmiSMNtlj = true;}
      while(bTXlMdrEcR == bTXlMdrEcR){sDufkOrMDQ = true;}
      if(EFKDektsMn == true){EFKDektsMn = false;}
      if(csXfByCQXF == true){csXfByCQXF = false;}
      if(BsFUmpcOkR == true){BsFUmpcOkR = false;}
      if(cGPKaRMfSZ == true){cGPKaRMfSZ = false;}
      if(ieZNphwqjO == true){ieZNphwqjO = false;}
      if(bbfWQLApPo == true){bbfWQLApPo = false;}
      if(HfHuKWdMFj == true){HfHuKWdMFj = false;}
      if(kWyyWVSqdF == true){kWyyWVSqdF = false;}
      if(sldVoBartP == true){sldVoBartP = false;}
      if(RVPcRDWeCT == true){RVPcRDWeCT = false;}
      if(DilAcFdgzt == true){DilAcFdgzt = false;}
      if(rIMKuVBlFJ == true){rIMKuVBlFJ = false;}
      if(wlSpSPGUfT == true){wlSpSPGUfT = false;}
      if(ymnJBJzdsi == true){ymnJBJzdsi = false;}
      if(XsrzWIJEgw == true){XsrzWIJEgw = false;}
      if(BkZsXQQwhN == true){BkZsXQQwhN = false;}
      if(yIBfwFTCJl == true){yIBfwFTCJl = false;}
      if(VXrVkCtSSJ == true){VXrVkCtSSJ = false;}
      if(FCmiSMNtlj == true){FCmiSMNtlj = false;}
      if(sDufkOrMDQ == true){sDufkOrMDQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQIWZJHHYY
{ 
  void PelLxcqnJF()
  { 
      bool tDVBPCmiaH = false;
      bool WraXZLSeTI = false;
      bool bYJbqChryY = false;
      bool aNWOrUCFFp = false;
      bool aJTTHBycBY = false;
      bool uuZSxUssJM = false;
      bool TtkCfIVMfE = false;
      bool IMZdhSFoUo = false;
      bool DEpZdfmDQW = false;
      bool aIwrVfYQny = false;
      bool fkxwPhVwke = false;
      bool PEYUIPDKYA = false;
      bool VRwIcAQgHB = false;
      bool snAVJSGtKu = false;
      bool KpSlGViajG = false;
      bool bNrmcOonSO = false;
      bool RnoikbDDLp = false;
      bool IJAdoeyKCH = false;
      bool QoxAZfwNsu = false;
      bool cSaucVBjAe = false;
      string NrXYsJppjJ;
      string zJgzHZDGsL;
      string oCSdGyBXPf;
      string ceywmQDKDT;
      string AXXUGEYLBf;
      string cVnBHLZsRu;
      string ISaEgTKkLp;
      string VsCYLQexXC;
      string YoWiCGpwnb;
      string pJrILgxTnl;
      string snzKJjTOpp;
      string gcVPVSuqBZ;
      string cOwjALAsNd;
      string TKIkJkpLYS;
      string mbGyuNnclr;
      string lFRNJeqPKx;
      string iZBLWVTkGk;
      string cjShlBHynl;
      string XXHVrNsubd;
      string tZBajNatbZ;
      if(NrXYsJppjJ == snzKJjTOpp){tDVBPCmiaH = true;}
      else if(snzKJjTOpp == NrXYsJppjJ){fkxwPhVwke = true;}
      if(zJgzHZDGsL == gcVPVSuqBZ){WraXZLSeTI = true;}
      else if(gcVPVSuqBZ == zJgzHZDGsL){PEYUIPDKYA = true;}
      if(oCSdGyBXPf == cOwjALAsNd){bYJbqChryY = true;}
      else if(cOwjALAsNd == oCSdGyBXPf){VRwIcAQgHB = true;}
      if(ceywmQDKDT == TKIkJkpLYS){aNWOrUCFFp = true;}
      else if(TKIkJkpLYS == ceywmQDKDT){snAVJSGtKu = true;}
      if(AXXUGEYLBf == mbGyuNnclr){aJTTHBycBY = true;}
      else if(mbGyuNnclr == AXXUGEYLBf){KpSlGViajG = true;}
      if(cVnBHLZsRu == lFRNJeqPKx){uuZSxUssJM = true;}
      else if(lFRNJeqPKx == cVnBHLZsRu){bNrmcOonSO = true;}
      if(ISaEgTKkLp == iZBLWVTkGk){TtkCfIVMfE = true;}
      else if(iZBLWVTkGk == ISaEgTKkLp){RnoikbDDLp = true;}
      if(VsCYLQexXC == cjShlBHynl){IMZdhSFoUo = true;}
      if(YoWiCGpwnb == XXHVrNsubd){DEpZdfmDQW = true;}
      if(pJrILgxTnl == tZBajNatbZ){aIwrVfYQny = true;}
      while(cjShlBHynl == VsCYLQexXC){IJAdoeyKCH = true;}
      while(XXHVrNsubd == XXHVrNsubd){QoxAZfwNsu = true;}
      while(tZBajNatbZ == tZBajNatbZ){cSaucVBjAe = true;}
      if(tDVBPCmiaH == true){tDVBPCmiaH = false;}
      if(WraXZLSeTI == true){WraXZLSeTI = false;}
      if(bYJbqChryY == true){bYJbqChryY = false;}
      if(aNWOrUCFFp == true){aNWOrUCFFp = false;}
      if(aJTTHBycBY == true){aJTTHBycBY = false;}
      if(uuZSxUssJM == true){uuZSxUssJM = false;}
      if(TtkCfIVMfE == true){TtkCfIVMfE = false;}
      if(IMZdhSFoUo == true){IMZdhSFoUo = false;}
      if(DEpZdfmDQW == true){DEpZdfmDQW = false;}
      if(aIwrVfYQny == true){aIwrVfYQny = false;}
      if(fkxwPhVwke == true){fkxwPhVwke = false;}
      if(PEYUIPDKYA == true){PEYUIPDKYA = false;}
      if(VRwIcAQgHB == true){VRwIcAQgHB = false;}
      if(snAVJSGtKu == true){snAVJSGtKu = false;}
      if(KpSlGViajG == true){KpSlGViajG = false;}
      if(bNrmcOonSO == true){bNrmcOonSO = false;}
      if(RnoikbDDLp == true){RnoikbDDLp = false;}
      if(IJAdoeyKCH == true){IJAdoeyKCH = false;}
      if(QoxAZfwNsu == true){QoxAZfwNsu = false;}
      if(cSaucVBjAe == true){cSaucVBjAe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPNOHHTHHN
{ 
  void xZqZamWpIo()
  { 
      bool RuOSEWhRLZ = false;
      bool FxpKhahsYK = false;
      bool znjYEZGISx = false;
      bool yQtwwfipnQ = false;
      bool rlrzyXkKwm = false;
      bool RBcQgcLpNd = false;
      bool PYyObnDtNB = false;
      bool rrFHSMujag = false;
      bool owMfewncOS = false;
      bool UsbJBTmcXJ = false;
      bool TqwtuYuVyT = false;
      bool hbPgoSLRje = false;
      bool AafugyQwGy = false;
      bool ZSLRMxASkF = false;
      bool BRdtkrctTh = false;
      bool HUssIsKANw = false;
      bool IzOztOQyUq = false;
      bool SsgddhwkJn = false;
      bool VVbXqEZRIS = false;
      bool lzEnwBDdAV = false;
      string yHHdRarQgO;
      string tQiUbjYVZm;
      string rTmUoNFeKG;
      string nDTLTlulMY;
      string gBuZiEYfnf;
      string CClFUdUmoE;
      string VMFZZpxXAp;
      string omJBGpYNkj;
      string oZqeEkQOpo;
      string RHwHCTuVzr;
      string HAexqPsjze;
      string FGCEOwVaVo;
      string ZhgLYgpByl;
      string tDOrcntsnn;
      string rgOLiKFqsG;
      string yUzJSYSSYJ;
      string ZqlMjCrJbZ;
      string BbmhxsSVcN;
      string byIrnZDEZD;
      string VbUdOAtCbf;
      if(yHHdRarQgO == HAexqPsjze){RuOSEWhRLZ = true;}
      else if(HAexqPsjze == yHHdRarQgO){TqwtuYuVyT = true;}
      if(tQiUbjYVZm == FGCEOwVaVo){FxpKhahsYK = true;}
      else if(FGCEOwVaVo == tQiUbjYVZm){hbPgoSLRje = true;}
      if(rTmUoNFeKG == ZhgLYgpByl){znjYEZGISx = true;}
      else if(ZhgLYgpByl == rTmUoNFeKG){AafugyQwGy = true;}
      if(nDTLTlulMY == tDOrcntsnn){yQtwwfipnQ = true;}
      else if(tDOrcntsnn == nDTLTlulMY){ZSLRMxASkF = true;}
      if(gBuZiEYfnf == rgOLiKFqsG){rlrzyXkKwm = true;}
      else if(rgOLiKFqsG == gBuZiEYfnf){BRdtkrctTh = true;}
      if(CClFUdUmoE == yUzJSYSSYJ){RBcQgcLpNd = true;}
      else if(yUzJSYSSYJ == CClFUdUmoE){HUssIsKANw = true;}
      if(VMFZZpxXAp == ZqlMjCrJbZ){PYyObnDtNB = true;}
      else if(ZqlMjCrJbZ == VMFZZpxXAp){IzOztOQyUq = true;}
      if(omJBGpYNkj == BbmhxsSVcN){rrFHSMujag = true;}
      if(oZqeEkQOpo == byIrnZDEZD){owMfewncOS = true;}
      if(RHwHCTuVzr == VbUdOAtCbf){UsbJBTmcXJ = true;}
      while(BbmhxsSVcN == omJBGpYNkj){SsgddhwkJn = true;}
      while(byIrnZDEZD == byIrnZDEZD){VVbXqEZRIS = true;}
      while(VbUdOAtCbf == VbUdOAtCbf){lzEnwBDdAV = true;}
      if(RuOSEWhRLZ == true){RuOSEWhRLZ = false;}
      if(FxpKhahsYK == true){FxpKhahsYK = false;}
      if(znjYEZGISx == true){znjYEZGISx = false;}
      if(yQtwwfipnQ == true){yQtwwfipnQ = false;}
      if(rlrzyXkKwm == true){rlrzyXkKwm = false;}
      if(RBcQgcLpNd == true){RBcQgcLpNd = false;}
      if(PYyObnDtNB == true){PYyObnDtNB = false;}
      if(rrFHSMujag == true){rrFHSMujag = false;}
      if(owMfewncOS == true){owMfewncOS = false;}
      if(UsbJBTmcXJ == true){UsbJBTmcXJ = false;}
      if(TqwtuYuVyT == true){TqwtuYuVyT = false;}
      if(hbPgoSLRje == true){hbPgoSLRje = false;}
      if(AafugyQwGy == true){AafugyQwGy = false;}
      if(ZSLRMxASkF == true){ZSLRMxASkF = false;}
      if(BRdtkrctTh == true){BRdtkrctTh = false;}
      if(HUssIsKANw == true){HUssIsKANw = false;}
      if(IzOztOQyUq == true){IzOztOQyUq = false;}
      if(SsgddhwkJn == true){SsgddhwkJn = false;}
      if(VVbXqEZRIS == true){VVbXqEZRIS = false;}
      if(lzEnwBDdAV == true){lzEnwBDdAV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFCJAPHRJS
{ 
  void uYhkukpjaL()
  { 
      bool TBYHxyxffD = false;
      bool prTJoyPAUo = false;
      bool oCrZzPeEWp = false;
      bool SuSVmbsHzA = false;
      bool RUqkBNgnWA = false;
      bool dqWeXRIyHh = false;
      bool SrIpkuZyVN = false;
      bool FHBTXULHYl = false;
      bool hphWLaYmxV = false;
      bool StzRhZLAAG = false;
      bool niSIuWpCHD = false;
      bool GBZVzbJldJ = false;
      bool VlBAuKHily = false;
      bool IKGRyzXYao = false;
      bool kVfsPRUdSF = false;
      bool PZWqkBgRNk = false;
      bool OGQJtutIXz = false;
      bool EkLnXAGHjc = false;
      bool pdQfhhmOgw = false;
      bool SFKoZeEVyT = false;
      string JwkTOoddzQ;
      string BxCXhFQLso;
      string KUYgerXEVQ;
      string aBtglcYWbz;
      string tTZOOfNcXL;
      string WsDoYnWEoV;
      string QZHhpzDUkF;
      string gsitupuKSy;
      string dugKthyFHx;
      string FUhFiUMqXO;
      string brqRecJIth;
      string sLkpqUrxnI;
      string AyMnALLdKa;
      string dDmDWlEPeQ;
      string YpKYEsirNN;
      string bOCPOdfDQS;
      string RexTEpYhSF;
      string QcRWiKmmiH;
      string cSPxyOAWor;
      string FAyMzsrqUN;
      if(JwkTOoddzQ == brqRecJIth){TBYHxyxffD = true;}
      else if(brqRecJIth == JwkTOoddzQ){niSIuWpCHD = true;}
      if(BxCXhFQLso == sLkpqUrxnI){prTJoyPAUo = true;}
      else if(sLkpqUrxnI == BxCXhFQLso){GBZVzbJldJ = true;}
      if(KUYgerXEVQ == AyMnALLdKa){oCrZzPeEWp = true;}
      else if(AyMnALLdKa == KUYgerXEVQ){VlBAuKHily = true;}
      if(aBtglcYWbz == dDmDWlEPeQ){SuSVmbsHzA = true;}
      else if(dDmDWlEPeQ == aBtglcYWbz){IKGRyzXYao = true;}
      if(tTZOOfNcXL == YpKYEsirNN){RUqkBNgnWA = true;}
      else if(YpKYEsirNN == tTZOOfNcXL){kVfsPRUdSF = true;}
      if(WsDoYnWEoV == bOCPOdfDQS){dqWeXRIyHh = true;}
      else if(bOCPOdfDQS == WsDoYnWEoV){PZWqkBgRNk = true;}
      if(QZHhpzDUkF == RexTEpYhSF){SrIpkuZyVN = true;}
      else if(RexTEpYhSF == QZHhpzDUkF){OGQJtutIXz = true;}
      if(gsitupuKSy == QcRWiKmmiH){FHBTXULHYl = true;}
      if(dugKthyFHx == cSPxyOAWor){hphWLaYmxV = true;}
      if(FUhFiUMqXO == FAyMzsrqUN){StzRhZLAAG = true;}
      while(QcRWiKmmiH == gsitupuKSy){EkLnXAGHjc = true;}
      while(cSPxyOAWor == cSPxyOAWor){pdQfhhmOgw = true;}
      while(FAyMzsrqUN == FAyMzsrqUN){SFKoZeEVyT = true;}
      if(TBYHxyxffD == true){TBYHxyxffD = false;}
      if(prTJoyPAUo == true){prTJoyPAUo = false;}
      if(oCrZzPeEWp == true){oCrZzPeEWp = false;}
      if(SuSVmbsHzA == true){SuSVmbsHzA = false;}
      if(RUqkBNgnWA == true){RUqkBNgnWA = false;}
      if(dqWeXRIyHh == true){dqWeXRIyHh = false;}
      if(SrIpkuZyVN == true){SrIpkuZyVN = false;}
      if(FHBTXULHYl == true){FHBTXULHYl = false;}
      if(hphWLaYmxV == true){hphWLaYmxV = false;}
      if(StzRhZLAAG == true){StzRhZLAAG = false;}
      if(niSIuWpCHD == true){niSIuWpCHD = false;}
      if(GBZVzbJldJ == true){GBZVzbJldJ = false;}
      if(VlBAuKHily == true){VlBAuKHily = false;}
      if(IKGRyzXYao == true){IKGRyzXYao = false;}
      if(kVfsPRUdSF == true){kVfsPRUdSF = false;}
      if(PZWqkBgRNk == true){PZWqkBgRNk = false;}
      if(OGQJtutIXz == true){OGQJtutIXz = false;}
      if(EkLnXAGHjc == true){EkLnXAGHjc = false;}
      if(pdQfhhmOgw == true){pdQfhhmOgw = false;}
      if(SFKoZeEVyT == true){SFKoZeEVyT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPVQOUKXEM
{ 
  void qLfnkShJdc()
  { 
      bool wsZhUBbnqQ = false;
      bool LYgeepyrjV = false;
      bool PqsChJxYGh = false;
      bool xfuGdrRqLA = false;
      bool xKMLOHzmoI = false;
      bool leTjxEAXzL = false;
      bool EDhITfdZBl = false;
      bool YHgiXFdgna = false;
      bool JJjxwRMKJY = false;
      bool rtqzutbDrh = false;
      bool dYlCjeyjLq = false;
      bool ZSjYBuSjMB = false;
      bool SSPbsdPgmd = false;
      bool caoFxjXgNQ = false;
      bool TbzRyYJSyA = false;
      bool arqqPKJJIF = false;
      bool OQwgNzdeaQ = false;
      bool WlWugqTxdU = false;
      bool TwimDkiypm = false;
      bool aNXHBCfRDz = false;
      string ydEcuKJKnS;
      string XyEAgKkKEB;
      string WNSzlsJfbl;
      string nuZRUNGpUh;
      string ffkQftNdnX;
      string YkkcdjLFpB;
      string BchBebXmfS;
      string DupWVpcBTr;
      string ferEMDKxmj;
      string CBASfCxilD;
      string VZxVTdtOGm;
      string HKkxVVkcob;
      string RaAwQCuWpT;
      string ssOPVGgVki;
      string IwpzbqPCxJ;
      string QTtKluZBEQ;
      string iXXmtOuVbP;
      string oOrFSUjAUZ;
      string lrYfCYyEcZ;
      string gfRTzkXDFN;
      if(ydEcuKJKnS == VZxVTdtOGm){wsZhUBbnqQ = true;}
      else if(VZxVTdtOGm == ydEcuKJKnS){dYlCjeyjLq = true;}
      if(XyEAgKkKEB == HKkxVVkcob){LYgeepyrjV = true;}
      else if(HKkxVVkcob == XyEAgKkKEB){ZSjYBuSjMB = true;}
      if(WNSzlsJfbl == RaAwQCuWpT){PqsChJxYGh = true;}
      else if(RaAwQCuWpT == WNSzlsJfbl){SSPbsdPgmd = true;}
      if(nuZRUNGpUh == ssOPVGgVki){xfuGdrRqLA = true;}
      else if(ssOPVGgVki == nuZRUNGpUh){caoFxjXgNQ = true;}
      if(ffkQftNdnX == IwpzbqPCxJ){xKMLOHzmoI = true;}
      else if(IwpzbqPCxJ == ffkQftNdnX){TbzRyYJSyA = true;}
      if(YkkcdjLFpB == QTtKluZBEQ){leTjxEAXzL = true;}
      else if(QTtKluZBEQ == YkkcdjLFpB){arqqPKJJIF = true;}
      if(BchBebXmfS == iXXmtOuVbP){EDhITfdZBl = true;}
      else if(iXXmtOuVbP == BchBebXmfS){OQwgNzdeaQ = true;}
      if(DupWVpcBTr == oOrFSUjAUZ){YHgiXFdgna = true;}
      if(ferEMDKxmj == lrYfCYyEcZ){JJjxwRMKJY = true;}
      if(CBASfCxilD == gfRTzkXDFN){rtqzutbDrh = true;}
      while(oOrFSUjAUZ == DupWVpcBTr){WlWugqTxdU = true;}
      while(lrYfCYyEcZ == lrYfCYyEcZ){TwimDkiypm = true;}
      while(gfRTzkXDFN == gfRTzkXDFN){aNXHBCfRDz = true;}
      if(wsZhUBbnqQ == true){wsZhUBbnqQ = false;}
      if(LYgeepyrjV == true){LYgeepyrjV = false;}
      if(PqsChJxYGh == true){PqsChJxYGh = false;}
      if(xfuGdrRqLA == true){xfuGdrRqLA = false;}
      if(xKMLOHzmoI == true){xKMLOHzmoI = false;}
      if(leTjxEAXzL == true){leTjxEAXzL = false;}
      if(EDhITfdZBl == true){EDhITfdZBl = false;}
      if(YHgiXFdgna == true){YHgiXFdgna = false;}
      if(JJjxwRMKJY == true){JJjxwRMKJY = false;}
      if(rtqzutbDrh == true){rtqzutbDrh = false;}
      if(dYlCjeyjLq == true){dYlCjeyjLq = false;}
      if(ZSjYBuSjMB == true){ZSjYBuSjMB = false;}
      if(SSPbsdPgmd == true){SSPbsdPgmd = false;}
      if(caoFxjXgNQ == true){caoFxjXgNQ = false;}
      if(TbzRyYJSyA == true){TbzRyYJSyA = false;}
      if(arqqPKJJIF == true){arqqPKJJIF = false;}
      if(OQwgNzdeaQ == true){OQwgNzdeaQ = false;}
      if(WlWugqTxdU == true){WlWugqTxdU = false;}
      if(TwimDkiypm == true){TwimDkiypm = false;}
      if(aNXHBCfRDz == true){aNXHBCfRDz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGJDRRBRIT
{ 
  void XCkFBZUIFq()
  { 
      bool OVNXBAHirf = false;
      bool KDboUcXWgY = false;
      bool tUbTTmgxpA = false;
      bool fDAjYxfPcV = false;
      bool zoguNyWxaT = false;
      bool uDTxmsssEN = false;
      bool TJsqAGDrQX = false;
      bool xHsKYFngGU = false;
      bool QiWWFbiCwe = false;
      bool DlLPCowotG = false;
      bool udgCWnJIYh = false;
      bool ELmixkmVlX = false;
      bool WAukUKudIj = false;
      bool IzlAYlCTzQ = false;
      bool RadOarzcRQ = false;
      bool BZDVitiuhM = false;
      bool rfznZFYmJK = false;
      bool hTWUFwWgKb = false;
      bool KSLqhiuPRd = false;
      bool CGkmYlaonU = false;
      string EHaTWBSbwV;
      string ZtmxwYAAuX;
      string TKfbisLtgu;
      string xynWLNpSWJ;
      string bcgjuaPBGP;
      string EXEpfsayjc;
      string pXuAYaFQlh;
      string igckupcwgH;
      string cJnQqZtyqR;
      string mqhtTEggLT;
      string VzPXfWtSto;
      string PeRczfjeIz;
      string gHYTurzhRq;
      string JwkNlctPjU;
      string eaDCBIZFtm;
      string UCXLlNaucn;
      string WLBDfTsDqV;
      string lTtnTFDWSm;
      string StndWHYYaX;
      string CzmwxSZAVh;
      if(EHaTWBSbwV == VzPXfWtSto){OVNXBAHirf = true;}
      else if(VzPXfWtSto == EHaTWBSbwV){udgCWnJIYh = true;}
      if(ZtmxwYAAuX == PeRczfjeIz){KDboUcXWgY = true;}
      else if(PeRczfjeIz == ZtmxwYAAuX){ELmixkmVlX = true;}
      if(TKfbisLtgu == gHYTurzhRq){tUbTTmgxpA = true;}
      else if(gHYTurzhRq == TKfbisLtgu){WAukUKudIj = true;}
      if(xynWLNpSWJ == JwkNlctPjU){fDAjYxfPcV = true;}
      else if(JwkNlctPjU == xynWLNpSWJ){IzlAYlCTzQ = true;}
      if(bcgjuaPBGP == eaDCBIZFtm){zoguNyWxaT = true;}
      else if(eaDCBIZFtm == bcgjuaPBGP){RadOarzcRQ = true;}
      if(EXEpfsayjc == UCXLlNaucn){uDTxmsssEN = true;}
      else if(UCXLlNaucn == EXEpfsayjc){BZDVitiuhM = true;}
      if(pXuAYaFQlh == WLBDfTsDqV){TJsqAGDrQX = true;}
      else if(WLBDfTsDqV == pXuAYaFQlh){rfznZFYmJK = true;}
      if(igckupcwgH == lTtnTFDWSm){xHsKYFngGU = true;}
      if(cJnQqZtyqR == StndWHYYaX){QiWWFbiCwe = true;}
      if(mqhtTEggLT == CzmwxSZAVh){DlLPCowotG = true;}
      while(lTtnTFDWSm == igckupcwgH){hTWUFwWgKb = true;}
      while(StndWHYYaX == StndWHYYaX){KSLqhiuPRd = true;}
      while(CzmwxSZAVh == CzmwxSZAVh){CGkmYlaonU = true;}
      if(OVNXBAHirf == true){OVNXBAHirf = false;}
      if(KDboUcXWgY == true){KDboUcXWgY = false;}
      if(tUbTTmgxpA == true){tUbTTmgxpA = false;}
      if(fDAjYxfPcV == true){fDAjYxfPcV = false;}
      if(zoguNyWxaT == true){zoguNyWxaT = false;}
      if(uDTxmsssEN == true){uDTxmsssEN = false;}
      if(TJsqAGDrQX == true){TJsqAGDrQX = false;}
      if(xHsKYFngGU == true){xHsKYFngGU = false;}
      if(QiWWFbiCwe == true){QiWWFbiCwe = false;}
      if(DlLPCowotG == true){DlLPCowotG = false;}
      if(udgCWnJIYh == true){udgCWnJIYh = false;}
      if(ELmixkmVlX == true){ELmixkmVlX = false;}
      if(WAukUKudIj == true){WAukUKudIj = false;}
      if(IzlAYlCTzQ == true){IzlAYlCTzQ = false;}
      if(RadOarzcRQ == true){RadOarzcRQ = false;}
      if(BZDVitiuhM == true){BZDVitiuhM = false;}
      if(rfznZFYmJK == true){rfznZFYmJK = false;}
      if(hTWUFwWgKb == true){hTWUFwWgKb = false;}
      if(KSLqhiuPRd == true){KSLqhiuPRd = false;}
      if(CGkmYlaonU == true){CGkmYlaonU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXOBSSLAIA
{ 
  void EZDsNzcSXh()
  { 
      bool UmUHpNsctk = false;
      bool WfMqhnzgNU = false;
      bool shliQwXNzC = false;
      bool HhwsMqTdBN = false;
      bool MUDHmosaRU = false;
      bool NoqfdmAlqt = false;
      bool pfdqcnjTeq = false;
      bool UUfzHYddua = false;
      bool DwwdnSpPPZ = false;
      bool pgmHXgqLey = false;
      bool EYwaAsIrYF = false;
      bool IWqPqsizCK = false;
      bool yUEEAnhXbZ = false;
      bool gSzwWdzVdu = false;
      bool JypJRToWQd = false;
      bool yqITAiUqZL = false;
      bool KkQzXoWtsM = false;
      bool sNUHBAdtmg = false;
      bool yLHxaoJfwm = false;
      bool JIuSkXhqlb = false;
      string KKiTsxIYpX;
      string xtDFdibeRm;
      string bPoEwDUadb;
      string rWAIkIiyUF;
      string UdxGMkzcbI;
      string IbUlotVeXp;
      string chuOfZttUU;
      string AcKMSxShrK;
      string EqyUSQCNTp;
      string mEaecmihZl;
      string qEIGIfQHTq;
      string bmlMkkiawP;
      string XgaegwCeie;
      string OjHGTzirMm;
      string ztscOzRNsr;
      string EHlKNJdcYM;
      string ckYnbqeerl;
      string BpNJQcmxQg;
      string dnlqaGyxsJ;
      string VFSAJNVFBW;
      if(KKiTsxIYpX == qEIGIfQHTq){UmUHpNsctk = true;}
      else if(qEIGIfQHTq == KKiTsxIYpX){EYwaAsIrYF = true;}
      if(xtDFdibeRm == bmlMkkiawP){WfMqhnzgNU = true;}
      else if(bmlMkkiawP == xtDFdibeRm){IWqPqsizCK = true;}
      if(bPoEwDUadb == XgaegwCeie){shliQwXNzC = true;}
      else if(XgaegwCeie == bPoEwDUadb){yUEEAnhXbZ = true;}
      if(rWAIkIiyUF == OjHGTzirMm){HhwsMqTdBN = true;}
      else if(OjHGTzirMm == rWAIkIiyUF){gSzwWdzVdu = true;}
      if(UdxGMkzcbI == ztscOzRNsr){MUDHmosaRU = true;}
      else if(ztscOzRNsr == UdxGMkzcbI){JypJRToWQd = true;}
      if(IbUlotVeXp == EHlKNJdcYM){NoqfdmAlqt = true;}
      else if(EHlKNJdcYM == IbUlotVeXp){yqITAiUqZL = true;}
      if(chuOfZttUU == ckYnbqeerl){pfdqcnjTeq = true;}
      else if(ckYnbqeerl == chuOfZttUU){KkQzXoWtsM = true;}
      if(AcKMSxShrK == BpNJQcmxQg){UUfzHYddua = true;}
      if(EqyUSQCNTp == dnlqaGyxsJ){DwwdnSpPPZ = true;}
      if(mEaecmihZl == VFSAJNVFBW){pgmHXgqLey = true;}
      while(BpNJQcmxQg == AcKMSxShrK){sNUHBAdtmg = true;}
      while(dnlqaGyxsJ == dnlqaGyxsJ){yLHxaoJfwm = true;}
      while(VFSAJNVFBW == VFSAJNVFBW){JIuSkXhqlb = true;}
      if(UmUHpNsctk == true){UmUHpNsctk = false;}
      if(WfMqhnzgNU == true){WfMqhnzgNU = false;}
      if(shliQwXNzC == true){shliQwXNzC = false;}
      if(HhwsMqTdBN == true){HhwsMqTdBN = false;}
      if(MUDHmosaRU == true){MUDHmosaRU = false;}
      if(NoqfdmAlqt == true){NoqfdmAlqt = false;}
      if(pfdqcnjTeq == true){pfdqcnjTeq = false;}
      if(UUfzHYddua == true){UUfzHYddua = false;}
      if(DwwdnSpPPZ == true){DwwdnSpPPZ = false;}
      if(pgmHXgqLey == true){pgmHXgqLey = false;}
      if(EYwaAsIrYF == true){EYwaAsIrYF = false;}
      if(IWqPqsizCK == true){IWqPqsizCK = false;}
      if(yUEEAnhXbZ == true){yUEEAnhXbZ = false;}
      if(gSzwWdzVdu == true){gSzwWdzVdu = false;}
      if(JypJRToWQd == true){JypJRToWQd = false;}
      if(yqITAiUqZL == true){yqITAiUqZL = false;}
      if(KkQzXoWtsM == true){KkQzXoWtsM = false;}
      if(sNUHBAdtmg == true){sNUHBAdtmg = false;}
      if(yLHxaoJfwm == true){yLHxaoJfwm = false;}
      if(JIuSkXhqlb == true){JIuSkXhqlb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTGAWJOCMJ
{ 
  void EXtBgxuRyq()
  { 
      bool kBNFDdMjEt = false;
      bool QUFjxXLZnF = false;
      bool SfLwNmXZaV = false;
      bool wyLyNXNsOV = false;
      bool SLrshauAwX = false;
      bool EGGdOEoRrQ = false;
      bool GmJiyRIGWY = false;
      bool JSKRmHmSNm = false;
      bool qWcDQorgjI = false;
      bool hwAyPfBJuP = false;
      bool RocXNkwnqH = false;
      bool QWDEZiJGRI = false;
      bool ZbWNqMRMBH = false;
      bool FdXxVCsFoe = false;
      bool sDpcrLruXg = false;
      bool VurmppRPgB = false;
      bool SjliBmzFiW = false;
      bool oDRlOVktVe = false;
      bool TVnUkKkjHf = false;
      bool jdYnLJQGaF = false;
      string cNoxDiozCg;
      string rIRtbyyjVy;
      string pnHrFwHABI;
      string TLbmDkJDos;
      string AOPQGOHGll;
      string eTgVWoGwrH;
      string aoytMgfdqq;
      string nuucxbXpkp;
      string nBNOdzdGPN;
      string dMKhRLPVDZ;
      string idOuyjXEYu;
      string QPKCSZajPN;
      string CZOcMajNKk;
      string LBmLHKlSQt;
      string aZgTwNBIOq;
      string kfFpXIOkhW;
      string zKsmjOcztI;
      string mHTVlcrtfy;
      string ZbySzewwmy;
      string uAjsuQftih;
      if(cNoxDiozCg == idOuyjXEYu){kBNFDdMjEt = true;}
      else if(idOuyjXEYu == cNoxDiozCg){RocXNkwnqH = true;}
      if(rIRtbyyjVy == QPKCSZajPN){QUFjxXLZnF = true;}
      else if(QPKCSZajPN == rIRtbyyjVy){QWDEZiJGRI = true;}
      if(pnHrFwHABI == CZOcMajNKk){SfLwNmXZaV = true;}
      else if(CZOcMajNKk == pnHrFwHABI){ZbWNqMRMBH = true;}
      if(TLbmDkJDos == LBmLHKlSQt){wyLyNXNsOV = true;}
      else if(LBmLHKlSQt == TLbmDkJDos){FdXxVCsFoe = true;}
      if(AOPQGOHGll == aZgTwNBIOq){SLrshauAwX = true;}
      else if(aZgTwNBIOq == AOPQGOHGll){sDpcrLruXg = true;}
      if(eTgVWoGwrH == kfFpXIOkhW){EGGdOEoRrQ = true;}
      else if(kfFpXIOkhW == eTgVWoGwrH){VurmppRPgB = true;}
      if(aoytMgfdqq == zKsmjOcztI){GmJiyRIGWY = true;}
      else if(zKsmjOcztI == aoytMgfdqq){SjliBmzFiW = true;}
      if(nuucxbXpkp == mHTVlcrtfy){JSKRmHmSNm = true;}
      if(nBNOdzdGPN == ZbySzewwmy){qWcDQorgjI = true;}
      if(dMKhRLPVDZ == uAjsuQftih){hwAyPfBJuP = true;}
      while(mHTVlcrtfy == nuucxbXpkp){oDRlOVktVe = true;}
      while(ZbySzewwmy == ZbySzewwmy){TVnUkKkjHf = true;}
      while(uAjsuQftih == uAjsuQftih){jdYnLJQGaF = true;}
      if(kBNFDdMjEt == true){kBNFDdMjEt = false;}
      if(QUFjxXLZnF == true){QUFjxXLZnF = false;}
      if(SfLwNmXZaV == true){SfLwNmXZaV = false;}
      if(wyLyNXNsOV == true){wyLyNXNsOV = false;}
      if(SLrshauAwX == true){SLrshauAwX = false;}
      if(EGGdOEoRrQ == true){EGGdOEoRrQ = false;}
      if(GmJiyRIGWY == true){GmJiyRIGWY = false;}
      if(JSKRmHmSNm == true){JSKRmHmSNm = false;}
      if(qWcDQorgjI == true){qWcDQorgjI = false;}
      if(hwAyPfBJuP == true){hwAyPfBJuP = false;}
      if(RocXNkwnqH == true){RocXNkwnqH = false;}
      if(QWDEZiJGRI == true){QWDEZiJGRI = false;}
      if(ZbWNqMRMBH == true){ZbWNqMRMBH = false;}
      if(FdXxVCsFoe == true){FdXxVCsFoe = false;}
      if(sDpcrLruXg == true){sDpcrLruXg = false;}
      if(VurmppRPgB == true){VurmppRPgB = false;}
      if(SjliBmzFiW == true){SjliBmzFiW = false;}
      if(oDRlOVktVe == true){oDRlOVktVe = false;}
      if(TVnUkKkjHf == true){TVnUkKkjHf = false;}
      if(jdYnLJQGaF == true){jdYnLJQGaF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSASHJLJJK
{ 
  void xiJkDCyzfz()
  { 
      bool uXfPNQwDkG = false;
      bool yrjZbSNSXb = false;
      bool VVrEoUAYxX = false;
      bool yRGdsWzNhr = false;
      bool QFjaHLIpnT = false;
      bool lRSVbZebZs = false;
      bool QXGNHgkGgE = false;
      bool SAkfLPkRwd = false;
      bool LJjdkgyjCS = false;
      bool qXmobsyWSa = false;
      bool ZCIiAkglKL = false;
      bool oNeugGmcbZ = false;
      bool hAEONuMuES = false;
      bool QOzVEJAAdA = false;
      bool AMZpdcsqIU = false;
      bool FVtrrYxtVE = false;
      bool XkhrtZOIqW = false;
      bool FlzbZVaNkj = false;
      bool BVmiMuTGdf = false;
      bool LGeYbPdgwD = false;
      string iipAmjPeFQ;
      string UcwAPbkaFV;
      string CyKuXBuwCY;
      string hwxbqfoumk;
      string yppGyUKZZB;
      string OPIxAkYtck;
      string oTcfhXfUJi;
      string mpmUXLHDxC;
      string qUVBKSnzbF;
      string HtRCueNKYZ;
      string npPpOXbnZn;
      string cUxZtTxbVO;
      string jgrEarXkYr;
      string yxeXOAFfll;
      string qAYmclxrIb;
      string hknJpHxLOV;
      string zqPhoepZLs;
      string OQojXiIFao;
      string tfcwJMJUgG;
      string DsQPmAkqyx;
      if(iipAmjPeFQ == npPpOXbnZn){uXfPNQwDkG = true;}
      else if(npPpOXbnZn == iipAmjPeFQ){ZCIiAkglKL = true;}
      if(UcwAPbkaFV == cUxZtTxbVO){yrjZbSNSXb = true;}
      else if(cUxZtTxbVO == UcwAPbkaFV){oNeugGmcbZ = true;}
      if(CyKuXBuwCY == jgrEarXkYr){VVrEoUAYxX = true;}
      else if(jgrEarXkYr == CyKuXBuwCY){hAEONuMuES = true;}
      if(hwxbqfoumk == yxeXOAFfll){yRGdsWzNhr = true;}
      else if(yxeXOAFfll == hwxbqfoumk){QOzVEJAAdA = true;}
      if(yppGyUKZZB == qAYmclxrIb){QFjaHLIpnT = true;}
      else if(qAYmclxrIb == yppGyUKZZB){AMZpdcsqIU = true;}
      if(OPIxAkYtck == hknJpHxLOV){lRSVbZebZs = true;}
      else if(hknJpHxLOV == OPIxAkYtck){FVtrrYxtVE = true;}
      if(oTcfhXfUJi == zqPhoepZLs){QXGNHgkGgE = true;}
      else if(zqPhoepZLs == oTcfhXfUJi){XkhrtZOIqW = true;}
      if(mpmUXLHDxC == OQojXiIFao){SAkfLPkRwd = true;}
      if(qUVBKSnzbF == tfcwJMJUgG){LJjdkgyjCS = true;}
      if(HtRCueNKYZ == DsQPmAkqyx){qXmobsyWSa = true;}
      while(OQojXiIFao == mpmUXLHDxC){FlzbZVaNkj = true;}
      while(tfcwJMJUgG == tfcwJMJUgG){BVmiMuTGdf = true;}
      while(DsQPmAkqyx == DsQPmAkqyx){LGeYbPdgwD = true;}
      if(uXfPNQwDkG == true){uXfPNQwDkG = false;}
      if(yrjZbSNSXb == true){yrjZbSNSXb = false;}
      if(VVrEoUAYxX == true){VVrEoUAYxX = false;}
      if(yRGdsWzNhr == true){yRGdsWzNhr = false;}
      if(QFjaHLIpnT == true){QFjaHLIpnT = false;}
      if(lRSVbZebZs == true){lRSVbZebZs = false;}
      if(QXGNHgkGgE == true){QXGNHgkGgE = false;}
      if(SAkfLPkRwd == true){SAkfLPkRwd = false;}
      if(LJjdkgyjCS == true){LJjdkgyjCS = false;}
      if(qXmobsyWSa == true){qXmobsyWSa = false;}
      if(ZCIiAkglKL == true){ZCIiAkglKL = false;}
      if(oNeugGmcbZ == true){oNeugGmcbZ = false;}
      if(hAEONuMuES == true){hAEONuMuES = false;}
      if(QOzVEJAAdA == true){QOzVEJAAdA = false;}
      if(AMZpdcsqIU == true){AMZpdcsqIU = false;}
      if(FVtrrYxtVE == true){FVtrrYxtVE = false;}
      if(XkhrtZOIqW == true){XkhrtZOIqW = false;}
      if(FlzbZVaNkj == true){FlzbZVaNkj = false;}
      if(BVmiMuTGdf == true){BVmiMuTGdf = false;}
      if(LGeYbPdgwD == true){LGeYbPdgwD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNZBUDAYNH
{ 
  void YgrhNFKThT()
  { 
      bool jEVKVeHKbM = false;
      bool FaMtGTVFLG = false;
      bool VMSaETRKsR = false;
      bool pOfQfdOKUG = false;
      bool wEbXeaDxaX = false;
      bool CwwdzXluFB = false;
      bool NxQKWquwOb = false;
      bool FLjEJRjuud = false;
      bool PTiVOsRBQI = false;
      bool rSESsynRAn = false;
      bool eHiySqLrTh = false;
      bool mpzbltNtud = false;
      bool YteGjlGRLK = false;
      bool cSuHyHjkDX = false;
      bool hZhiVCTcgz = false;
      bool ksVWOkccOf = false;
      bool jtfIETtrcd = false;
      bool JcqXuzMwkg = false;
      bool SdjMZjxYrN = false;
      bool eHVWmmsYdB = false;
      string PAyMRDELYS;
      string TgQncfTRNW;
      string LbQRXUwLlT;
      string VkcuqWjtOM;
      string tpkVeHXoge;
      string xetAknignw;
      string HrYFxiEVwF;
      string uYCBcVqumQ;
      string wHeHVqqbKD;
      string nDGRECQfYw;
      string DCrbiYbrXO;
      string wmtXAzNQiF;
      string qbLsQrSkwa;
      string ELWpMsPDYx;
      string OyEuGAIhQF;
      string oAwSFbqzKp;
      string FpwwKkQDLG;
      string jJrlprWPlP;
      string ikUpkEODkj;
      string CQrhrYCHjV;
      if(PAyMRDELYS == DCrbiYbrXO){jEVKVeHKbM = true;}
      else if(DCrbiYbrXO == PAyMRDELYS){eHiySqLrTh = true;}
      if(TgQncfTRNW == wmtXAzNQiF){FaMtGTVFLG = true;}
      else if(wmtXAzNQiF == TgQncfTRNW){mpzbltNtud = true;}
      if(LbQRXUwLlT == qbLsQrSkwa){VMSaETRKsR = true;}
      else if(qbLsQrSkwa == LbQRXUwLlT){YteGjlGRLK = true;}
      if(VkcuqWjtOM == ELWpMsPDYx){pOfQfdOKUG = true;}
      else if(ELWpMsPDYx == VkcuqWjtOM){cSuHyHjkDX = true;}
      if(tpkVeHXoge == OyEuGAIhQF){wEbXeaDxaX = true;}
      else if(OyEuGAIhQF == tpkVeHXoge){hZhiVCTcgz = true;}
      if(xetAknignw == oAwSFbqzKp){CwwdzXluFB = true;}
      else if(oAwSFbqzKp == xetAknignw){ksVWOkccOf = true;}
      if(HrYFxiEVwF == FpwwKkQDLG){NxQKWquwOb = true;}
      else if(FpwwKkQDLG == HrYFxiEVwF){jtfIETtrcd = true;}
      if(uYCBcVqumQ == jJrlprWPlP){FLjEJRjuud = true;}
      if(wHeHVqqbKD == ikUpkEODkj){PTiVOsRBQI = true;}
      if(nDGRECQfYw == CQrhrYCHjV){rSESsynRAn = true;}
      while(jJrlprWPlP == uYCBcVqumQ){JcqXuzMwkg = true;}
      while(ikUpkEODkj == ikUpkEODkj){SdjMZjxYrN = true;}
      while(CQrhrYCHjV == CQrhrYCHjV){eHVWmmsYdB = true;}
      if(jEVKVeHKbM == true){jEVKVeHKbM = false;}
      if(FaMtGTVFLG == true){FaMtGTVFLG = false;}
      if(VMSaETRKsR == true){VMSaETRKsR = false;}
      if(pOfQfdOKUG == true){pOfQfdOKUG = false;}
      if(wEbXeaDxaX == true){wEbXeaDxaX = false;}
      if(CwwdzXluFB == true){CwwdzXluFB = false;}
      if(NxQKWquwOb == true){NxQKWquwOb = false;}
      if(FLjEJRjuud == true){FLjEJRjuud = false;}
      if(PTiVOsRBQI == true){PTiVOsRBQI = false;}
      if(rSESsynRAn == true){rSESsynRAn = false;}
      if(eHiySqLrTh == true){eHiySqLrTh = false;}
      if(mpzbltNtud == true){mpzbltNtud = false;}
      if(YteGjlGRLK == true){YteGjlGRLK = false;}
      if(cSuHyHjkDX == true){cSuHyHjkDX = false;}
      if(hZhiVCTcgz == true){hZhiVCTcgz = false;}
      if(ksVWOkccOf == true){ksVWOkccOf = false;}
      if(jtfIETtrcd == true){jtfIETtrcd = false;}
      if(JcqXuzMwkg == true){JcqXuzMwkg = false;}
      if(SdjMZjxYrN == true){SdjMZjxYrN = false;}
      if(eHVWmmsYdB == true){eHVWmmsYdB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VQQCWZLNHE
{ 
  void qOhOBUCqsM()
  { 
      bool hzMKIjjSUb = false;
      bool ylagmSlqLB = false;
      bool CTyizzZLpe = false;
      bool acqZnxrNGd = false;
      bool eYmAlLrTwR = false;
      bool BYiuHNAcKJ = false;
      bool JYboAUuAsp = false;
      bool aXkgVcgywm = false;
      bool GGPYdBtwSZ = false;
      bool xODwTGxxAR = false;
      bool QqaFqcmBYe = false;
      bool fCfWCDIDLz = false;
      bool ZyhSsLUoNO = false;
      bool fjyeWOfKgA = false;
      bool NrWmsuhgsQ = false;
      bool ytkAqSJHMe = false;
      bool IynJywDBAn = false;
      bool XyVLkhatYy = false;
      bool cnuxQlyxmE = false;
      bool FXxBqPEMox = false;
      string mszAaUBpNH;
      string UAEzTTxQLb;
      string YrTxCDwhBO;
      string xilccGzFDw;
      string KicQTeDTub;
      string yFNRCtZByX;
      string YSnzKkObVM;
      string UqMPRoPCdX;
      string AbmZPrVUZi;
      string gyHfXqtdGh;
      string PbyhGHryzM;
      string eXWaWwfOiS;
      string OsBmeWjgqZ;
      string ukuuHYdESH;
      string zXUNDJafIb;
      string LetnSWZKDj;
      string WKGZQsbbTy;
      string SaubSqYnjV;
      string wEYPNPqHcj;
      string ySBiknQuwJ;
      if(mszAaUBpNH == PbyhGHryzM){hzMKIjjSUb = true;}
      else if(PbyhGHryzM == mszAaUBpNH){QqaFqcmBYe = true;}
      if(UAEzTTxQLb == eXWaWwfOiS){ylagmSlqLB = true;}
      else if(eXWaWwfOiS == UAEzTTxQLb){fCfWCDIDLz = true;}
      if(YrTxCDwhBO == OsBmeWjgqZ){CTyizzZLpe = true;}
      else if(OsBmeWjgqZ == YrTxCDwhBO){ZyhSsLUoNO = true;}
      if(xilccGzFDw == ukuuHYdESH){acqZnxrNGd = true;}
      else if(ukuuHYdESH == xilccGzFDw){fjyeWOfKgA = true;}
      if(KicQTeDTub == zXUNDJafIb){eYmAlLrTwR = true;}
      else if(zXUNDJafIb == KicQTeDTub){NrWmsuhgsQ = true;}
      if(yFNRCtZByX == LetnSWZKDj){BYiuHNAcKJ = true;}
      else if(LetnSWZKDj == yFNRCtZByX){ytkAqSJHMe = true;}
      if(YSnzKkObVM == WKGZQsbbTy){JYboAUuAsp = true;}
      else if(WKGZQsbbTy == YSnzKkObVM){IynJywDBAn = true;}
      if(UqMPRoPCdX == SaubSqYnjV){aXkgVcgywm = true;}
      if(AbmZPrVUZi == wEYPNPqHcj){GGPYdBtwSZ = true;}
      if(gyHfXqtdGh == ySBiknQuwJ){xODwTGxxAR = true;}
      while(SaubSqYnjV == UqMPRoPCdX){XyVLkhatYy = true;}
      while(wEYPNPqHcj == wEYPNPqHcj){cnuxQlyxmE = true;}
      while(ySBiknQuwJ == ySBiknQuwJ){FXxBqPEMox = true;}
      if(hzMKIjjSUb == true){hzMKIjjSUb = false;}
      if(ylagmSlqLB == true){ylagmSlqLB = false;}
      if(CTyizzZLpe == true){CTyizzZLpe = false;}
      if(acqZnxrNGd == true){acqZnxrNGd = false;}
      if(eYmAlLrTwR == true){eYmAlLrTwR = false;}
      if(BYiuHNAcKJ == true){BYiuHNAcKJ = false;}
      if(JYboAUuAsp == true){JYboAUuAsp = false;}
      if(aXkgVcgywm == true){aXkgVcgywm = false;}
      if(GGPYdBtwSZ == true){GGPYdBtwSZ = false;}
      if(xODwTGxxAR == true){xODwTGxxAR = false;}
      if(QqaFqcmBYe == true){QqaFqcmBYe = false;}
      if(fCfWCDIDLz == true){fCfWCDIDLz = false;}
      if(ZyhSsLUoNO == true){ZyhSsLUoNO = false;}
      if(fjyeWOfKgA == true){fjyeWOfKgA = false;}
      if(NrWmsuhgsQ == true){NrWmsuhgsQ = false;}
      if(ytkAqSJHMe == true){ytkAqSJHMe = false;}
      if(IynJywDBAn == true){IynJywDBAn = false;}
      if(XyVLkhatYy == true){XyVLkhatYy = false;}
      if(cnuxQlyxmE == true){cnuxQlyxmE = false;}
      if(FXxBqPEMox == true){FXxBqPEMox = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCWSOSQATC
{ 
  void CFiwwXQWSa()
  { 
      bool KOQBSpxzEG = false;
      bool gCiGKpOcYx = false;
      bool TZnkSszrDX = false;
      bool fTIhKKdadq = false;
      bool uUbqmUNiTS = false;
      bool wrucOjZfiZ = false;
      bool qEugZNsAwz = false;
      bool LnyhBzyxxy = false;
      bool fPYkamXfTZ = false;
      bool jyrEAqYtQZ = false;
      bool aMmTGItNbO = false;
      bool kbiksafKGl = false;
      bool oNfVPMwthJ = false;
      bool aDfWXScEdR = false;
      bool sKEFnHPGKY = false;
      bool LNnejMgQEs = false;
      bool MAeRmhuLNa = false;
      bool xafnreJahH = false;
      bool xoiIyMPBmK = false;
      bool lMAjFselRG = false;
      string rzusidLKrm;
      string jUErzNeoUV;
      string gXZrUrFZBm;
      string kJLmMSurfS;
      string WOXdfsAUtc;
      string oVhRUUYCYp;
      string XkJECZIQff;
      string SlJByRzwLa;
      string rkeYxObtSr;
      string trToukFTaG;
      string jjnNKDLfSC;
      string UbqxylGkGm;
      string yOynlZRTGM;
      string MfUFqIwQNt;
      string DuaPWRAWqI;
      string eTMnIVkAbj;
      string kqZGpnGlGo;
      string poWMiCniQU;
      string ZucxgsTgxU;
      string WwodILVUZi;
      if(rzusidLKrm == jjnNKDLfSC){KOQBSpxzEG = true;}
      else if(jjnNKDLfSC == rzusidLKrm){aMmTGItNbO = true;}
      if(jUErzNeoUV == UbqxylGkGm){gCiGKpOcYx = true;}
      else if(UbqxylGkGm == jUErzNeoUV){kbiksafKGl = true;}
      if(gXZrUrFZBm == yOynlZRTGM){TZnkSszrDX = true;}
      else if(yOynlZRTGM == gXZrUrFZBm){oNfVPMwthJ = true;}
      if(kJLmMSurfS == MfUFqIwQNt){fTIhKKdadq = true;}
      else if(MfUFqIwQNt == kJLmMSurfS){aDfWXScEdR = true;}
      if(WOXdfsAUtc == DuaPWRAWqI){uUbqmUNiTS = true;}
      else if(DuaPWRAWqI == WOXdfsAUtc){sKEFnHPGKY = true;}
      if(oVhRUUYCYp == eTMnIVkAbj){wrucOjZfiZ = true;}
      else if(eTMnIVkAbj == oVhRUUYCYp){LNnejMgQEs = true;}
      if(XkJECZIQff == kqZGpnGlGo){qEugZNsAwz = true;}
      else if(kqZGpnGlGo == XkJECZIQff){MAeRmhuLNa = true;}
      if(SlJByRzwLa == poWMiCniQU){LnyhBzyxxy = true;}
      if(rkeYxObtSr == ZucxgsTgxU){fPYkamXfTZ = true;}
      if(trToukFTaG == WwodILVUZi){jyrEAqYtQZ = true;}
      while(poWMiCniQU == SlJByRzwLa){xafnreJahH = true;}
      while(ZucxgsTgxU == ZucxgsTgxU){xoiIyMPBmK = true;}
      while(WwodILVUZi == WwodILVUZi){lMAjFselRG = true;}
      if(KOQBSpxzEG == true){KOQBSpxzEG = false;}
      if(gCiGKpOcYx == true){gCiGKpOcYx = false;}
      if(TZnkSszrDX == true){TZnkSszrDX = false;}
      if(fTIhKKdadq == true){fTIhKKdadq = false;}
      if(uUbqmUNiTS == true){uUbqmUNiTS = false;}
      if(wrucOjZfiZ == true){wrucOjZfiZ = false;}
      if(qEugZNsAwz == true){qEugZNsAwz = false;}
      if(LnyhBzyxxy == true){LnyhBzyxxy = false;}
      if(fPYkamXfTZ == true){fPYkamXfTZ = false;}
      if(jyrEAqYtQZ == true){jyrEAqYtQZ = false;}
      if(aMmTGItNbO == true){aMmTGItNbO = false;}
      if(kbiksafKGl == true){kbiksafKGl = false;}
      if(oNfVPMwthJ == true){oNfVPMwthJ = false;}
      if(aDfWXScEdR == true){aDfWXScEdR = false;}
      if(sKEFnHPGKY == true){sKEFnHPGKY = false;}
      if(LNnejMgQEs == true){LNnejMgQEs = false;}
      if(MAeRmhuLNa == true){MAeRmhuLNa = false;}
      if(xafnreJahH == true){xafnreJahH = false;}
      if(xoiIyMPBmK == true){xoiIyMPBmK = false;}
      if(lMAjFselRG == true){lMAjFselRG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYHHFBAQWK
{ 
  void uFGztrwyeC()
  { 
      bool OUWowsONXe = false;
      bool sIOWttkiJw = false;
      bool RjmHFGGtZX = false;
      bool eYBGTxNywz = false;
      bool tZhpDNJYcE = false;
      bool CfANkdgPjo = false;
      bool mTnzzUHHCw = false;
      bool fllKBrBxEq = false;
      bool wgQVVyXnVo = false;
      bool PyOHLZlhpi = false;
      bool GCVgXQspLs = false;
      bool cjLrsFDRdA = false;
      bool xTlNfhWeyb = false;
      bool FSGUktKjyF = false;
      bool FgbbMfmVNG = false;
      bool WTEokmPIAo = false;
      bool sNqjnJcpGy = false;
      bool tSTXuPqKBA = false;
      bool uBRrEkNRjy = false;
      bool dCjIMqprnC = false;
      string WBLxQSGWJd;
      string pgQrnWCYEi;
      string AcWyVOwKcj;
      string NNheiPtijc;
      string ubOYpXeDQk;
      string MUXdTsdMbB;
      string WwsZQbzkJY;
      string cToamXOxIx;
      string irsrWroDKo;
      string kgGiGzhnHN;
      string XttrHsfxpu;
      string efDdRdDBCX;
      string muZTmuNGUn;
      string pZpuZoyAjd;
      string MrMPJEcbRb;
      string wfliZbTZEM;
      string fZbCFFpIEb;
      string fCRXLuiKKh;
      string SknsrJmGUx;
      string VYwWymPKJD;
      if(WBLxQSGWJd == XttrHsfxpu){OUWowsONXe = true;}
      else if(XttrHsfxpu == WBLxQSGWJd){GCVgXQspLs = true;}
      if(pgQrnWCYEi == efDdRdDBCX){sIOWttkiJw = true;}
      else if(efDdRdDBCX == pgQrnWCYEi){cjLrsFDRdA = true;}
      if(AcWyVOwKcj == muZTmuNGUn){RjmHFGGtZX = true;}
      else if(muZTmuNGUn == AcWyVOwKcj){xTlNfhWeyb = true;}
      if(NNheiPtijc == pZpuZoyAjd){eYBGTxNywz = true;}
      else if(pZpuZoyAjd == NNheiPtijc){FSGUktKjyF = true;}
      if(ubOYpXeDQk == MrMPJEcbRb){tZhpDNJYcE = true;}
      else if(MrMPJEcbRb == ubOYpXeDQk){FgbbMfmVNG = true;}
      if(MUXdTsdMbB == wfliZbTZEM){CfANkdgPjo = true;}
      else if(wfliZbTZEM == MUXdTsdMbB){WTEokmPIAo = true;}
      if(WwsZQbzkJY == fZbCFFpIEb){mTnzzUHHCw = true;}
      else if(fZbCFFpIEb == WwsZQbzkJY){sNqjnJcpGy = true;}
      if(cToamXOxIx == fCRXLuiKKh){fllKBrBxEq = true;}
      if(irsrWroDKo == SknsrJmGUx){wgQVVyXnVo = true;}
      if(kgGiGzhnHN == VYwWymPKJD){PyOHLZlhpi = true;}
      while(fCRXLuiKKh == cToamXOxIx){tSTXuPqKBA = true;}
      while(SknsrJmGUx == SknsrJmGUx){uBRrEkNRjy = true;}
      while(VYwWymPKJD == VYwWymPKJD){dCjIMqprnC = true;}
      if(OUWowsONXe == true){OUWowsONXe = false;}
      if(sIOWttkiJw == true){sIOWttkiJw = false;}
      if(RjmHFGGtZX == true){RjmHFGGtZX = false;}
      if(eYBGTxNywz == true){eYBGTxNywz = false;}
      if(tZhpDNJYcE == true){tZhpDNJYcE = false;}
      if(CfANkdgPjo == true){CfANkdgPjo = false;}
      if(mTnzzUHHCw == true){mTnzzUHHCw = false;}
      if(fllKBrBxEq == true){fllKBrBxEq = false;}
      if(wgQVVyXnVo == true){wgQVVyXnVo = false;}
      if(PyOHLZlhpi == true){PyOHLZlhpi = false;}
      if(GCVgXQspLs == true){GCVgXQspLs = false;}
      if(cjLrsFDRdA == true){cjLrsFDRdA = false;}
      if(xTlNfhWeyb == true){xTlNfhWeyb = false;}
      if(FSGUktKjyF == true){FSGUktKjyF = false;}
      if(FgbbMfmVNG == true){FgbbMfmVNG = false;}
      if(WTEokmPIAo == true){WTEokmPIAo = false;}
      if(sNqjnJcpGy == true){sNqjnJcpGy = false;}
      if(tSTXuPqKBA == true){tSTXuPqKBA = false;}
      if(uBRrEkNRjy == true){uBRrEkNRjy = false;}
      if(dCjIMqprnC == true){dCjIMqprnC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYVJIXFUSK
{ 
  void ixuMzSerqm()
  { 
      bool ijPOCqtbUx = false;
      bool SoltfDyers = false;
      bool mIxFZbhwGI = false;
      bool mAZBHnxGNS = false;
      bool KtPjNxUoNa = false;
      bool CnDTdZmKna = false;
      bool IyULJSOjlr = false;
      bool GrRYhrsMqc = false;
      bool GrifGzwFXh = false;
      bool AlSmJMZDat = false;
      bool hkDUTKVekk = false;
      bool gZSLUQPnFJ = false;
      bool VJMEqTZePV = false;
      bool RolxtVnNMu = false;
      bool cRTlAZTHRr = false;
      bool xlyQYYXzcz = false;
      bool kqOPSqnVQz = false;
      bool bBbJfDoZDQ = false;
      bool ARMWYfqUXV = false;
      bool xojMKlCETJ = false;
      string onFTrWpiGa;
      string hKEzXeYdTS;
      string UVFadVSfDC;
      string HwzElTLZaj;
      string FEudMWcJHM;
      string dThgDSiepV;
      string DKfDSkLAMD;
      string TyCiNPZaNH;
      string sJXqYmORAS;
      string kfjFfuYqKa;
      string KcxDreRyTn;
      string rIQictlnef;
      string WtzsSmOxCS;
      string piPlwPLUyt;
      string VPxLabPBbl;
      string IjMeEPcEkE;
      string PTwByJselN;
      string iRpkKHwmSp;
      string XMVQJFVjhg;
      string mHjsdBTwNQ;
      if(onFTrWpiGa == KcxDreRyTn){ijPOCqtbUx = true;}
      else if(KcxDreRyTn == onFTrWpiGa){hkDUTKVekk = true;}
      if(hKEzXeYdTS == rIQictlnef){SoltfDyers = true;}
      else if(rIQictlnef == hKEzXeYdTS){gZSLUQPnFJ = true;}
      if(UVFadVSfDC == WtzsSmOxCS){mIxFZbhwGI = true;}
      else if(WtzsSmOxCS == UVFadVSfDC){VJMEqTZePV = true;}
      if(HwzElTLZaj == piPlwPLUyt){mAZBHnxGNS = true;}
      else if(piPlwPLUyt == HwzElTLZaj){RolxtVnNMu = true;}
      if(FEudMWcJHM == VPxLabPBbl){KtPjNxUoNa = true;}
      else if(VPxLabPBbl == FEudMWcJHM){cRTlAZTHRr = true;}
      if(dThgDSiepV == IjMeEPcEkE){CnDTdZmKna = true;}
      else if(IjMeEPcEkE == dThgDSiepV){xlyQYYXzcz = true;}
      if(DKfDSkLAMD == PTwByJselN){IyULJSOjlr = true;}
      else if(PTwByJselN == DKfDSkLAMD){kqOPSqnVQz = true;}
      if(TyCiNPZaNH == iRpkKHwmSp){GrRYhrsMqc = true;}
      if(sJXqYmORAS == XMVQJFVjhg){GrifGzwFXh = true;}
      if(kfjFfuYqKa == mHjsdBTwNQ){AlSmJMZDat = true;}
      while(iRpkKHwmSp == TyCiNPZaNH){bBbJfDoZDQ = true;}
      while(XMVQJFVjhg == XMVQJFVjhg){ARMWYfqUXV = true;}
      while(mHjsdBTwNQ == mHjsdBTwNQ){xojMKlCETJ = true;}
      if(ijPOCqtbUx == true){ijPOCqtbUx = false;}
      if(SoltfDyers == true){SoltfDyers = false;}
      if(mIxFZbhwGI == true){mIxFZbhwGI = false;}
      if(mAZBHnxGNS == true){mAZBHnxGNS = false;}
      if(KtPjNxUoNa == true){KtPjNxUoNa = false;}
      if(CnDTdZmKna == true){CnDTdZmKna = false;}
      if(IyULJSOjlr == true){IyULJSOjlr = false;}
      if(GrRYhrsMqc == true){GrRYhrsMqc = false;}
      if(GrifGzwFXh == true){GrifGzwFXh = false;}
      if(AlSmJMZDat == true){AlSmJMZDat = false;}
      if(hkDUTKVekk == true){hkDUTKVekk = false;}
      if(gZSLUQPnFJ == true){gZSLUQPnFJ = false;}
      if(VJMEqTZePV == true){VJMEqTZePV = false;}
      if(RolxtVnNMu == true){RolxtVnNMu = false;}
      if(cRTlAZTHRr == true){cRTlAZTHRr = false;}
      if(xlyQYYXzcz == true){xlyQYYXzcz = false;}
      if(kqOPSqnVQz == true){kqOPSqnVQz = false;}
      if(bBbJfDoZDQ == true){bBbJfDoZDQ = false;}
      if(ARMWYfqUXV == true){ARMWYfqUXV = false;}
      if(xojMKlCETJ == true){xojMKlCETJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVIBZHIPAE
{ 
  void HBZrBMReWi()
  { 
      bool XQZlqIqMdw = false;
      bool ykTOtRZhHU = false;
      bool ESiCnPJTVV = false;
      bool ZuLjkKSVdf = false;
      bool nfJyEzsLLn = false;
      bool SdLjqEgXya = false;
      bool yXpIVDYicj = false;
      bool zEEafXIjxn = false;
      bool VyHgCwibrg = false;
      bool ctWCgQpBcA = false;
      bool aJhboNYkDS = false;
      bool wxaJFAQIFY = false;
      bool UwqwHEgBsP = false;
      bool hGHwNLQfrn = false;
      bool WyYZkfTNwg = false;
      bool zguDfeSkTk = false;
      bool gXqmjoodws = false;
      bool ikQRCWWQLb = false;
      bool jTFLQALDQi = false;
      bool seLGHzGlou = false;
      string DZZziZWJMs;
      string wFAUczEoYh;
      string MEUDVLDclN;
      string YphYXWZewd;
      string WsjEpOzTRQ;
      string KtknTzEVcX;
      string WtXyUFWbwF;
      string YZrtKTTQNH;
      string LiKUCdEsFY;
      string SDBYGcVkij;
      string qXWLqjCpdz;
      string enIVMniDup;
      string BdWXmVYTmh;
      string yhgdQmLycS;
      string bOPFsdueLS;
      string sRosiMByXV;
      string LhCwBxGdFZ;
      string bjZcOlOQeJ;
      string asHUnfrnuD;
      string kMaGGsLTEu;
      if(DZZziZWJMs == qXWLqjCpdz){XQZlqIqMdw = true;}
      else if(qXWLqjCpdz == DZZziZWJMs){aJhboNYkDS = true;}
      if(wFAUczEoYh == enIVMniDup){ykTOtRZhHU = true;}
      else if(enIVMniDup == wFAUczEoYh){wxaJFAQIFY = true;}
      if(MEUDVLDclN == BdWXmVYTmh){ESiCnPJTVV = true;}
      else if(BdWXmVYTmh == MEUDVLDclN){UwqwHEgBsP = true;}
      if(YphYXWZewd == yhgdQmLycS){ZuLjkKSVdf = true;}
      else if(yhgdQmLycS == YphYXWZewd){hGHwNLQfrn = true;}
      if(WsjEpOzTRQ == bOPFsdueLS){nfJyEzsLLn = true;}
      else if(bOPFsdueLS == WsjEpOzTRQ){WyYZkfTNwg = true;}
      if(KtknTzEVcX == sRosiMByXV){SdLjqEgXya = true;}
      else if(sRosiMByXV == KtknTzEVcX){zguDfeSkTk = true;}
      if(WtXyUFWbwF == LhCwBxGdFZ){yXpIVDYicj = true;}
      else if(LhCwBxGdFZ == WtXyUFWbwF){gXqmjoodws = true;}
      if(YZrtKTTQNH == bjZcOlOQeJ){zEEafXIjxn = true;}
      if(LiKUCdEsFY == asHUnfrnuD){VyHgCwibrg = true;}
      if(SDBYGcVkij == kMaGGsLTEu){ctWCgQpBcA = true;}
      while(bjZcOlOQeJ == YZrtKTTQNH){ikQRCWWQLb = true;}
      while(asHUnfrnuD == asHUnfrnuD){jTFLQALDQi = true;}
      while(kMaGGsLTEu == kMaGGsLTEu){seLGHzGlou = true;}
      if(XQZlqIqMdw == true){XQZlqIqMdw = false;}
      if(ykTOtRZhHU == true){ykTOtRZhHU = false;}
      if(ESiCnPJTVV == true){ESiCnPJTVV = false;}
      if(ZuLjkKSVdf == true){ZuLjkKSVdf = false;}
      if(nfJyEzsLLn == true){nfJyEzsLLn = false;}
      if(SdLjqEgXya == true){SdLjqEgXya = false;}
      if(yXpIVDYicj == true){yXpIVDYicj = false;}
      if(zEEafXIjxn == true){zEEafXIjxn = false;}
      if(VyHgCwibrg == true){VyHgCwibrg = false;}
      if(ctWCgQpBcA == true){ctWCgQpBcA = false;}
      if(aJhboNYkDS == true){aJhboNYkDS = false;}
      if(wxaJFAQIFY == true){wxaJFAQIFY = false;}
      if(UwqwHEgBsP == true){UwqwHEgBsP = false;}
      if(hGHwNLQfrn == true){hGHwNLQfrn = false;}
      if(WyYZkfTNwg == true){WyYZkfTNwg = false;}
      if(zguDfeSkTk == true){zguDfeSkTk = false;}
      if(gXqmjoodws == true){gXqmjoodws = false;}
      if(ikQRCWWQLb == true){ikQRCWWQLb = false;}
      if(jTFLQALDQi == true){jTFLQALDQi = false;}
      if(seLGHzGlou == true){seLGHzGlou = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKQFRIFFPH
{ 
  void XXugkLoMAG()
  { 
      bool WGnJtaPJbt = false;
      bool fpSViRnJNF = false;
      bool JgfCADFDsi = false;
      bool epuVUwPcKn = false;
      bool nMVhhFupIW = false;
      bool xMjlxoalIq = false;
      bool UMPsOpuwBl = false;
      bool BLyYRwKyTu = false;
      bool HPtVkSFIXe = false;
      bool VdUTSbxcSr = false;
      bool JyoVUlNLUB = false;
      bool dbRMiFRsIw = false;
      bool kmYWQXqeGo = false;
      bool yheblJaYBz = false;
      bool EtnWAsLHkN = false;
      bool KDTVGWZRFx = false;
      bool uiFeCwxpaY = false;
      bool esrJrqyBWX = false;
      bool LitreuNIUP = false;
      bool jISDDVoIUD = false;
      string FYmxuKrBMj;
      string BTQRIumOYG;
      string kOVydeURwf;
      string UwrzWiiYsY;
      string MnQtoKkDiP;
      string roefWqDnSP;
      string paEgOFaRtZ;
      string LNVztxxaIS;
      string sQhgnfRMbf;
      string etFcikijej;
      string iTJIDdSekY;
      string sbfAWYrXrh;
      string nOoOuRIrPI;
      string ONwXiZHZcJ;
      string MlaClDOEGK;
      string sKqxwUdtNl;
      string UaOcKffHQw;
      string QRthUBnmbq;
      string CDlFOEVybO;
      string wNMqnlWyrG;
      if(FYmxuKrBMj == iTJIDdSekY){WGnJtaPJbt = true;}
      else if(iTJIDdSekY == FYmxuKrBMj){JyoVUlNLUB = true;}
      if(BTQRIumOYG == sbfAWYrXrh){fpSViRnJNF = true;}
      else if(sbfAWYrXrh == BTQRIumOYG){dbRMiFRsIw = true;}
      if(kOVydeURwf == nOoOuRIrPI){JgfCADFDsi = true;}
      else if(nOoOuRIrPI == kOVydeURwf){kmYWQXqeGo = true;}
      if(UwrzWiiYsY == ONwXiZHZcJ){epuVUwPcKn = true;}
      else if(ONwXiZHZcJ == UwrzWiiYsY){yheblJaYBz = true;}
      if(MnQtoKkDiP == MlaClDOEGK){nMVhhFupIW = true;}
      else if(MlaClDOEGK == MnQtoKkDiP){EtnWAsLHkN = true;}
      if(roefWqDnSP == sKqxwUdtNl){xMjlxoalIq = true;}
      else if(sKqxwUdtNl == roefWqDnSP){KDTVGWZRFx = true;}
      if(paEgOFaRtZ == UaOcKffHQw){UMPsOpuwBl = true;}
      else if(UaOcKffHQw == paEgOFaRtZ){uiFeCwxpaY = true;}
      if(LNVztxxaIS == QRthUBnmbq){BLyYRwKyTu = true;}
      if(sQhgnfRMbf == CDlFOEVybO){HPtVkSFIXe = true;}
      if(etFcikijej == wNMqnlWyrG){VdUTSbxcSr = true;}
      while(QRthUBnmbq == LNVztxxaIS){esrJrqyBWX = true;}
      while(CDlFOEVybO == CDlFOEVybO){LitreuNIUP = true;}
      while(wNMqnlWyrG == wNMqnlWyrG){jISDDVoIUD = true;}
      if(WGnJtaPJbt == true){WGnJtaPJbt = false;}
      if(fpSViRnJNF == true){fpSViRnJNF = false;}
      if(JgfCADFDsi == true){JgfCADFDsi = false;}
      if(epuVUwPcKn == true){epuVUwPcKn = false;}
      if(nMVhhFupIW == true){nMVhhFupIW = false;}
      if(xMjlxoalIq == true){xMjlxoalIq = false;}
      if(UMPsOpuwBl == true){UMPsOpuwBl = false;}
      if(BLyYRwKyTu == true){BLyYRwKyTu = false;}
      if(HPtVkSFIXe == true){HPtVkSFIXe = false;}
      if(VdUTSbxcSr == true){VdUTSbxcSr = false;}
      if(JyoVUlNLUB == true){JyoVUlNLUB = false;}
      if(dbRMiFRsIw == true){dbRMiFRsIw = false;}
      if(kmYWQXqeGo == true){kmYWQXqeGo = false;}
      if(yheblJaYBz == true){yheblJaYBz = false;}
      if(EtnWAsLHkN == true){EtnWAsLHkN = false;}
      if(KDTVGWZRFx == true){KDTVGWZRFx = false;}
      if(uiFeCwxpaY == true){uiFeCwxpaY = false;}
      if(esrJrqyBWX == true){esrJrqyBWX = false;}
      if(LitreuNIUP == true){LitreuNIUP = false;}
      if(jISDDVoIUD == true){jISDDVoIUD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMDRAVEZXB
{ 
  void HOxLBGJjeu()
  { 
      bool YTZEoFgsXd = false;
      bool drabklEkFh = false;
      bool gGsFePcmOU = false;
      bool bXhWTMWCrG = false;
      bool hSnVCGjQYG = false;
      bool XXMrwSaUYY = false;
      bool cseCCGJDHX = false;
      bool OBrzANRWCY = false;
      bool fMOHwDLpZB = false;
      bool lCdTdnmkTu = false;
      bool xfIBqWfNrh = false;
      bool ADRzrQeXGy = false;
      bool uTdGlMWYUL = false;
      bool afCGbADMQZ = false;
      bool XyxqBhjdaM = false;
      bool JOeUAcBCPd = false;
      bool zGrgGTBKXr = false;
      bool MRHfaxVlED = false;
      bool brxHBLBgGy = false;
      bool zAxlaQFQjg = false;
      string yQUzURDYiW;
      string gNxeNlwZoJ;
      string LsZUNJZCNa;
      string tduCgiVlXR;
      string LOsjdOcsia;
      string DElEnFpzlK;
      string qBLHbDSuxd;
      string PJCWxxzopy;
      string gfSlWpqqOb;
      string sVAMZJDlHa;
      string wguFKtBPGq;
      string FAIndKiYjl;
      string MafVksJpxn;
      string sNhPBzjMac;
      string nakXVrMLhP;
      string adBVOUAZUQ;
      string jLSSxrSsld;
      string ZVxHxkpIzs;
      string fxHgMOLMAg;
      string yKrJscISZc;
      if(yQUzURDYiW == wguFKtBPGq){YTZEoFgsXd = true;}
      else if(wguFKtBPGq == yQUzURDYiW){xfIBqWfNrh = true;}
      if(gNxeNlwZoJ == FAIndKiYjl){drabklEkFh = true;}
      else if(FAIndKiYjl == gNxeNlwZoJ){ADRzrQeXGy = true;}
      if(LsZUNJZCNa == MafVksJpxn){gGsFePcmOU = true;}
      else if(MafVksJpxn == LsZUNJZCNa){uTdGlMWYUL = true;}
      if(tduCgiVlXR == sNhPBzjMac){bXhWTMWCrG = true;}
      else if(sNhPBzjMac == tduCgiVlXR){afCGbADMQZ = true;}
      if(LOsjdOcsia == nakXVrMLhP){hSnVCGjQYG = true;}
      else if(nakXVrMLhP == LOsjdOcsia){XyxqBhjdaM = true;}
      if(DElEnFpzlK == adBVOUAZUQ){XXMrwSaUYY = true;}
      else if(adBVOUAZUQ == DElEnFpzlK){JOeUAcBCPd = true;}
      if(qBLHbDSuxd == jLSSxrSsld){cseCCGJDHX = true;}
      else if(jLSSxrSsld == qBLHbDSuxd){zGrgGTBKXr = true;}
      if(PJCWxxzopy == ZVxHxkpIzs){OBrzANRWCY = true;}
      if(gfSlWpqqOb == fxHgMOLMAg){fMOHwDLpZB = true;}
      if(sVAMZJDlHa == yKrJscISZc){lCdTdnmkTu = true;}
      while(ZVxHxkpIzs == PJCWxxzopy){MRHfaxVlED = true;}
      while(fxHgMOLMAg == fxHgMOLMAg){brxHBLBgGy = true;}
      while(yKrJscISZc == yKrJscISZc){zAxlaQFQjg = true;}
      if(YTZEoFgsXd == true){YTZEoFgsXd = false;}
      if(drabklEkFh == true){drabklEkFh = false;}
      if(gGsFePcmOU == true){gGsFePcmOU = false;}
      if(bXhWTMWCrG == true){bXhWTMWCrG = false;}
      if(hSnVCGjQYG == true){hSnVCGjQYG = false;}
      if(XXMrwSaUYY == true){XXMrwSaUYY = false;}
      if(cseCCGJDHX == true){cseCCGJDHX = false;}
      if(OBrzANRWCY == true){OBrzANRWCY = false;}
      if(fMOHwDLpZB == true){fMOHwDLpZB = false;}
      if(lCdTdnmkTu == true){lCdTdnmkTu = false;}
      if(xfIBqWfNrh == true){xfIBqWfNrh = false;}
      if(ADRzrQeXGy == true){ADRzrQeXGy = false;}
      if(uTdGlMWYUL == true){uTdGlMWYUL = false;}
      if(afCGbADMQZ == true){afCGbADMQZ = false;}
      if(XyxqBhjdaM == true){XyxqBhjdaM = false;}
      if(JOeUAcBCPd == true){JOeUAcBCPd = false;}
      if(zGrgGTBKXr == true){zGrgGTBKXr = false;}
      if(MRHfaxVlED == true){MRHfaxVlED = false;}
      if(brxHBLBgGy == true){brxHBLBgGy = false;}
      if(zAxlaQFQjg == true){zAxlaQFQjg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKHANALZSA
{ 
  void cscTrVfqDZ()
  { 
      bool wUJJOaMpMN = false;
      bool TpmXFboZVM = false;
      bool xaCagQkpqa = false;
      bool HHuaQPzAVI = false;
      bool aJlsrkIsGX = false;
      bool yQWllVRhby = false;
      bool pVylGMtLGo = false;
      bool bnEMlmnIiu = false;
      bool HqjTbpjIou = false;
      bool xQXXSEKzmf = false;
      bool qxmQwJMKzz = false;
      bool gJzgpyleJP = false;
      bool ckWLrKPgsg = false;
      bool boVDEKETWS = false;
      bool cZJpNnQqgU = false;
      bool SeoWCFZaXk = false;
      bool tfQSWrnwbe = false;
      bool sSIqlCbgxE = false;
      bool sXzYOwzyAy = false;
      bool jdukYxIpSV = false;
      string fAhKjImrIZ;
      string LGekitUPHT;
      string wIwVmXWFiB;
      string IkneiaVrzQ;
      string TaQsnlfpec;
      string WsMUZWDMWM;
      string khIGQZRACH;
      string YcQpAUqChB;
      string qgaFePYSFL;
      string XIUmekRJbN;
      string TfnWEscVUE;
      string eAdVUEHCbB;
      string ByupjPIcKO;
      string DhZTgLrDAk;
      string mCyAfWeySa;
      string dOgaMUjxlo;
      string kzKFBxZJnI;
      string LDCqNyAtKN;
      string jJKjjnAzHM;
      string buRLzmqrzi;
      if(fAhKjImrIZ == TfnWEscVUE){wUJJOaMpMN = true;}
      else if(TfnWEscVUE == fAhKjImrIZ){qxmQwJMKzz = true;}
      if(LGekitUPHT == eAdVUEHCbB){TpmXFboZVM = true;}
      else if(eAdVUEHCbB == LGekitUPHT){gJzgpyleJP = true;}
      if(wIwVmXWFiB == ByupjPIcKO){xaCagQkpqa = true;}
      else if(ByupjPIcKO == wIwVmXWFiB){ckWLrKPgsg = true;}
      if(IkneiaVrzQ == DhZTgLrDAk){HHuaQPzAVI = true;}
      else if(DhZTgLrDAk == IkneiaVrzQ){boVDEKETWS = true;}
      if(TaQsnlfpec == mCyAfWeySa){aJlsrkIsGX = true;}
      else if(mCyAfWeySa == TaQsnlfpec){cZJpNnQqgU = true;}
      if(WsMUZWDMWM == dOgaMUjxlo){yQWllVRhby = true;}
      else if(dOgaMUjxlo == WsMUZWDMWM){SeoWCFZaXk = true;}
      if(khIGQZRACH == kzKFBxZJnI){pVylGMtLGo = true;}
      else if(kzKFBxZJnI == khIGQZRACH){tfQSWrnwbe = true;}
      if(YcQpAUqChB == LDCqNyAtKN){bnEMlmnIiu = true;}
      if(qgaFePYSFL == jJKjjnAzHM){HqjTbpjIou = true;}
      if(XIUmekRJbN == buRLzmqrzi){xQXXSEKzmf = true;}
      while(LDCqNyAtKN == YcQpAUqChB){sSIqlCbgxE = true;}
      while(jJKjjnAzHM == jJKjjnAzHM){sXzYOwzyAy = true;}
      while(buRLzmqrzi == buRLzmqrzi){jdukYxIpSV = true;}
      if(wUJJOaMpMN == true){wUJJOaMpMN = false;}
      if(TpmXFboZVM == true){TpmXFboZVM = false;}
      if(xaCagQkpqa == true){xaCagQkpqa = false;}
      if(HHuaQPzAVI == true){HHuaQPzAVI = false;}
      if(aJlsrkIsGX == true){aJlsrkIsGX = false;}
      if(yQWllVRhby == true){yQWllVRhby = false;}
      if(pVylGMtLGo == true){pVylGMtLGo = false;}
      if(bnEMlmnIiu == true){bnEMlmnIiu = false;}
      if(HqjTbpjIou == true){HqjTbpjIou = false;}
      if(xQXXSEKzmf == true){xQXXSEKzmf = false;}
      if(qxmQwJMKzz == true){qxmQwJMKzz = false;}
      if(gJzgpyleJP == true){gJzgpyleJP = false;}
      if(ckWLrKPgsg == true){ckWLrKPgsg = false;}
      if(boVDEKETWS == true){boVDEKETWS = false;}
      if(cZJpNnQqgU == true){cZJpNnQqgU = false;}
      if(SeoWCFZaXk == true){SeoWCFZaXk = false;}
      if(tfQSWrnwbe == true){tfQSWrnwbe = false;}
      if(sSIqlCbgxE == true){sSIqlCbgxE = false;}
      if(sXzYOwzyAy == true){sXzYOwzyAy = false;}
      if(jdukYxIpSV == true){jdukYxIpSV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEJLTTCCIB
{ 
  void lcTTUhDEQo()
  { 
      bool mJVWghhJNw = false;
      bool gOfFYkgZtI = false;
      bool zPaiLgDQPB = false;
      bool xEueURxzzy = false;
      bool wsrUnAfeQx = false;
      bool JgqblWhmKz = false;
      bool dRtLybSAjG = false;
      bool mgawLGXFtK = false;
      bool AYASqQNTsx = false;
      bool iKozTeyfWM = false;
      bool geuJJcGtPf = false;
      bool zcrAzFRaUh = false;
      bool OzHlXcrabf = false;
      bool HqihdUdpJN = false;
      bool JSDMyFSnAO = false;
      bool NWLnxhXIlf = false;
      bool keRjYItJWd = false;
      bool baRGXuwtnR = false;
      bool KDaNSjetju = false;
      bool xUEccdATno = false;
      string ddLHaafrar;
      string PdYUfEMYRl;
      string xOuJokPPgF;
      string pTiqPYPqXl;
      string ZtMsSVeGmQ;
      string TYsqLOiCRp;
      string KPKUCwuhFH;
      string oUBfMDCBpT;
      string FJcPkQaqeA;
      string pMZgaJiqpW;
      string awBebzWMdH;
      string MgLyjBmtjk;
      string UDCERbuTFD;
      string TKKTsJIynl;
      string sOMXnJBaxY;
      string WnHFCWtwNz;
      string EDGamCVrFa;
      string rnFxqFpeQI;
      string aTWffeCFRV;
      string PLjohpHljk;
      if(ddLHaafrar == awBebzWMdH){mJVWghhJNw = true;}
      else if(awBebzWMdH == ddLHaafrar){geuJJcGtPf = true;}
      if(PdYUfEMYRl == MgLyjBmtjk){gOfFYkgZtI = true;}
      else if(MgLyjBmtjk == PdYUfEMYRl){zcrAzFRaUh = true;}
      if(xOuJokPPgF == UDCERbuTFD){zPaiLgDQPB = true;}
      else if(UDCERbuTFD == xOuJokPPgF){OzHlXcrabf = true;}
      if(pTiqPYPqXl == TKKTsJIynl){xEueURxzzy = true;}
      else if(TKKTsJIynl == pTiqPYPqXl){HqihdUdpJN = true;}
      if(ZtMsSVeGmQ == sOMXnJBaxY){wsrUnAfeQx = true;}
      else if(sOMXnJBaxY == ZtMsSVeGmQ){JSDMyFSnAO = true;}
      if(TYsqLOiCRp == WnHFCWtwNz){JgqblWhmKz = true;}
      else if(WnHFCWtwNz == TYsqLOiCRp){NWLnxhXIlf = true;}
      if(KPKUCwuhFH == EDGamCVrFa){dRtLybSAjG = true;}
      else if(EDGamCVrFa == KPKUCwuhFH){keRjYItJWd = true;}
      if(oUBfMDCBpT == rnFxqFpeQI){mgawLGXFtK = true;}
      if(FJcPkQaqeA == aTWffeCFRV){AYASqQNTsx = true;}
      if(pMZgaJiqpW == PLjohpHljk){iKozTeyfWM = true;}
      while(rnFxqFpeQI == oUBfMDCBpT){baRGXuwtnR = true;}
      while(aTWffeCFRV == aTWffeCFRV){KDaNSjetju = true;}
      while(PLjohpHljk == PLjohpHljk){xUEccdATno = true;}
      if(mJVWghhJNw == true){mJVWghhJNw = false;}
      if(gOfFYkgZtI == true){gOfFYkgZtI = false;}
      if(zPaiLgDQPB == true){zPaiLgDQPB = false;}
      if(xEueURxzzy == true){xEueURxzzy = false;}
      if(wsrUnAfeQx == true){wsrUnAfeQx = false;}
      if(JgqblWhmKz == true){JgqblWhmKz = false;}
      if(dRtLybSAjG == true){dRtLybSAjG = false;}
      if(mgawLGXFtK == true){mgawLGXFtK = false;}
      if(AYASqQNTsx == true){AYASqQNTsx = false;}
      if(iKozTeyfWM == true){iKozTeyfWM = false;}
      if(geuJJcGtPf == true){geuJJcGtPf = false;}
      if(zcrAzFRaUh == true){zcrAzFRaUh = false;}
      if(OzHlXcrabf == true){OzHlXcrabf = false;}
      if(HqihdUdpJN == true){HqihdUdpJN = false;}
      if(JSDMyFSnAO == true){JSDMyFSnAO = false;}
      if(NWLnxhXIlf == true){NWLnxhXIlf = false;}
      if(keRjYItJWd == true){keRjYItJWd = false;}
      if(baRGXuwtnR == true){baRGXuwtnR = false;}
      if(KDaNSjetju == true){KDaNSjetju = false;}
      if(xUEccdATno == true){xUEccdATno = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYYSQJRNHP
{ 
  void KgbmIpChxB()
  { 
      bool PIIjklThcr = false;
      bool LPLNDjOFgi = false;
      bool OCAPuVGkuJ = false;
      bool VZlNtVbMlh = false;
      bool JdqGHDEmHU = false;
      bool XokxnMHsnO = false;
      bool filSWldxSg = false;
      bool IBTzYjKsHr = false;
      bool RTcalfnnYg = false;
      bool NhXWCarYjV = false;
      bool YHTZMWVlXE = false;
      bool COkwxLFLfp = false;
      bool xoXkSZdwxy = false;
      bool rkJkSKADNP = false;
      bool KCPUezwaYq = false;
      bool UgrtYjihGl = false;
      bool sZnZMQEAdm = false;
      bool KBxQftYCGS = false;
      bool cCWGcKsOMh = false;
      bool aSwbWkNpIO = false;
      string lIFOLcpyuR;
      string ouPUepfjlt;
      string JLenNziOsx;
      string THtEZfjCZs;
      string DKHRfUESTc;
      string aPNHFZcRBL;
      string tbFxxhAKty;
      string GcJrpzENHr;
      string uQtPWDslzz;
      string CSAOzbFJTy;
      string TsXUWxFVQG;
      string VPJIPdgoat;
      string oOLuwncusO;
      string susJYBrYsZ;
      string xXUsdlIryV;
      string tPiYJFhcYh;
      string UKbCMaWAiO;
      string kHuBwQsSRK;
      string ejwWUdLTzT;
      string SPAKFluSfD;
      if(lIFOLcpyuR == TsXUWxFVQG){PIIjklThcr = true;}
      else if(TsXUWxFVQG == lIFOLcpyuR){YHTZMWVlXE = true;}
      if(ouPUepfjlt == VPJIPdgoat){LPLNDjOFgi = true;}
      else if(VPJIPdgoat == ouPUepfjlt){COkwxLFLfp = true;}
      if(JLenNziOsx == oOLuwncusO){OCAPuVGkuJ = true;}
      else if(oOLuwncusO == JLenNziOsx){xoXkSZdwxy = true;}
      if(THtEZfjCZs == susJYBrYsZ){VZlNtVbMlh = true;}
      else if(susJYBrYsZ == THtEZfjCZs){rkJkSKADNP = true;}
      if(DKHRfUESTc == xXUsdlIryV){JdqGHDEmHU = true;}
      else if(xXUsdlIryV == DKHRfUESTc){KCPUezwaYq = true;}
      if(aPNHFZcRBL == tPiYJFhcYh){XokxnMHsnO = true;}
      else if(tPiYJFhcYh == aPNHFZcRBL){UgrtYjihGl = true;}
      if(tbFxxhAKty == UKbCMaWAiO){filSWldxSg = true;}
      else if(UKbCMaWAiO == tbFxxhAKty){sZnZMQEAdm = true;}
      if(GcJrpzENHr == kHuBwQsSRK){IBTzYjKsHr = true;}
      if(uQtPWDslzz == ejwWUdLTzT){RTcalfnnYg = true;}
      if(CSAOzbFJTy == SPAKFluSfD){NhXWCarYjV = true;}
      while(kHuBwQsSRK == GcJrpzENHr){KBxQftYCGS = true;}
      while(ejwWUdLTzT == ejwWUdLTzT){cCWGcKsOMh = true;}
      while(SPAKFluSfD == SPAKFluSfD){aSwbWkNpIO = true;}
      if(PIIjklThcr == true){PIIjklThcr = false;}
      if(LPLNDjOFgi == true){LPLNDjOFgi = false;}
      if(OCAPuVGkuJ == true){OCAPuVGkuJ = false;}
      if(VZlNtVbMlh == true){VZlNtVbMlh = false;}
      if(JdqGHDEmHU == true){JdqGHDEmHU = false;}
      if(XokxnMHsnO == true){XokxnMHsnO = false;}
      if(filSWldxSg == true){filSWldxSg = false;}
      if(IBTzYjKsHr == true){IBTzYjKsHr = false;}
      if(RTcalfnnYg == true){RTcalfnnYg = false;}
      if(NhXWCarYjV == true){NhXWCarYjV = false;}
      if(YHTZMWVlXE == true){YHTZMWVlXE = false;}
      if(COkwxLFLfp == true){COkwxLFLfp = false;}
      if(xoXkSZdwxy == true){xoXkSZdwxy = false;}
      if(rkJkSKADNP == true){rkJkSKADNP = false;}
      if(KCPUezwaYq == true){KCPUezwaYq = false;}
      if(UgrtYjihGl == true){UgrtYjihGl = false;}
      if(sZnZMQEAdm == true){sZnZMQEAdm = false;}
      if(KBxQftYCGS == true){KBxQftYCGS = false;}
      if(cCWGcKsOMh == true){cCWGcKsOMh = false;}
      if(aSwbWkNpIO == true){aSwbWkNpIO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRLQKOPKNY
{ 
  void FGcJRjpAiW()
  { 
      bool HBOQRrVUAV = false;
      bool tRkuUxxoma = false;
      bool mLHJopZsRh = false;
      bool HbbCqVpXrm = false;
      bool CYJIwgVySX = false;
      bool ophbJwsFbb = false;
      bool RbDSNRphEy = false;
      bool GZwAXOBzNH = false;
      bool TaZsrRtzsu = false;
      bool ckwPUaVque = false;
      bool qmtTRPsgDu = false;
      bool ttrUHpBJZu = false;
      bool WpoIVVdfex = false;
      bool rKEhQfgFbc = false;
      bool XMuxAhsaId = false;
      bool YMRzHAykyu = false;
      bool lNBGCipJDb = false;
      bool JugwXJurHn = false;
      bool cCXBXfsEaP = false;
      bool huHgpKLntR = false;
      string HIyJPYwIsZ;
      string dwEYcaKehr;
      string FyMKRIZgLl;
      string XIPuaYCpuE;
      string hNZRwIkPYc;
      string qQESSJunrG;
      string zOxGBVgIxE;
      string YTidJrXuNJ;
      string XJHiuGEwcR;
      string cNynESQTPa;
      string abRUDXgZJa;
      string lAZhioGNKt;
      string RjffaLUtZq;
      string aDemhurmfX;
      string ZemBfcnPFO;
      string LDIUIqwksr;
      string CmzRzhUlAn;
      string xTgmUmxdAy;
      string WFoKeXtJep;
      string zGsnUmeUCx;
      if(HIyJPYwIsZ == abRUDXgZJa){HBOQRrVUAV = true;}
      else if(abRUDXgZJa == HIyJPYwIsZ){qmtTRPsgDu = true;}
      if(dwEYcaKehr == lAZhioGNKt){tRkuUxxoma = true;}
      else if(lAZhioGNKt == dwEYcaKehr){ttrUHpBJZu = true;}
      if(FyMKRIZgLl == RjffaLUtZq){mLHJopZsRh = true;}
      else if(RjffaLUtZq == FyMKRIZgLl){WpoIVVdfex = true;}
      if(XIPuaYCpuE == aDemhurmfX){HbbCqVpXrm = true;}
      else if(aDemhurmfX == XIPuaYCpuE){rKEhQfgFbc = true;}
      if(hNZRwIkPYc == ZemBfcnPFO){CYJIwgVySX = true;}
      else if(ZemBfcnPFO == hNZRwIkPYc){XMuxAhsaId = true;}
      if(qQESSJunrG == LDIUIqwksr){ophbJwsFbb = true;}
      else if(LDIUIqwksr == qQESSJunrG){YMRzHAykyu = true;}
      if(zOxGBVgIxE == CmzRzhUlAn){RbDSNRphEy = true;}
      else if(CmzRzhUlAn == zOxGBVgIxE){lNBGCipJDb = true;}
      if(YTidJrXuNJ == xTgmUmxdAy){GZwAXOBzNH = true;}
      if(XJHiuGEwcR == WFoKeXtJep){TaZsrRtzsu = true;}
      if(cNynESQTPa == zGsnUmeUCx){ckwPUaVque = true;}
      while(xTgmUmxdAy == YTidJrXuNJ){JugwXJurHn = true;}
      while(WFoKeXtJep == WFoKeXtJep){cCXBXfsEaP = true;}
      while(zGsnUmeUCx == zGsnUmeUCx){huHgpKLntR = true;}
      if(HBOQRrVUAV == true){HBOQRrVUAV = false;}
      if(tRkuUxxoma == true){tRkuUxxoma = false;}
      if(mLHJopZsRh == true){mLHJopZsRh = false;}
      if(HbbCqVpXrm == true){HbbCqVpXrm = false;}
      if(CYJIwgVySX == true){CYJIwgVySX = false;}
      if(ophbJwsFbb == true){ophbJwsFbb = false;}
      if(RbDSNRphEy == true){RbDSNRphEy = false;}
      if(GZwAXOBzNH == true){GZwAXOBzNH = false;}
      if(TaZsrRtzsu == true){TaZsrRtzsu = false;}
      if(ckwPUaVque == true){ckwPUaVque = false;}
      if(qmtTRPsgDu == true){qmtTRPsgDu = false;}
      if(ttrUHpBJZu == true){ttrUHpBJZu = false;}
      if(WpoIVVdfex == true){WpoIVVdfex = false;}
      if(rKEhQfgFbc == true){rKEhQfgFbc = false;}
      if(XMuxAhsaId == true){XMuxAhsaId = false;}
      if(YMRzHAykyu == true){YMRzHAykyu = false;}
      if(lNBGCipJDb == true){lNBGCipJDb = false;}
      if(JugwXJurHn == true){JugwXJurHn = false;}
      if(cCXBXfsEaP == true){cCXBXfsEaP = false;}
      if(huHgpKLntR == true){huHgpKLntR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXOCRNJMSA
{ 
  void PNRSFOFOSt()
  { 
      bool gPitZFNTxo = false;
      bool rOTGJoBSCF = false;
      bool nKweBlhBLX = false;
      bool WkluKYIeZu = false;
      bool HQwPMbJxwX = false;
      bool jjBjIWSDsn = false;
      bool WMHYRGcYuk = false;
      bool gVrHyXNgSZ = false;
      bool bkFnmmiCln = false;
      bool FEllXuIWxG = false;
      bool zkBKpOrtkk = false;
      bool IkkSLlHTld = false;
      bool WZlHfbiGiD = false;
      bool PpiLaqiuxY = false;
      bool uoQBeTTTZl = false;
      bool mnkTiYytdO = false;
      bool ekLhUSCYqU = false;
      bool CMVMihIkcL = false;
      bool IPfxPaEPbB = false;
      bool roQitJchfL = false;
      string BeNwRBARrw;
      string FaABGaoeIV;
      string WJoOEadgzk;
      string TeXYPhjkDU;
      string yyTHkiKMBs;
      string xQyTproyrp;
      string XSRHbaCalX;
      string pEanXXphdU;
      string QQeGnDfEiX;
      string slrNwegMfJ;
      string giacCsoKwR;
      string BGUXZGnLTX;
      string uyrOeELNqr;
      string qcCTmgpCDt;
      string NVIQVlQTmp;
      string qVsHOhpMyx;
      string gbSDaYEBkr;
      string PlHYKZpbrr;
      string nrZABVjtEF;
      string pdDFMlCEox;
      if(BeNwRBARrw == giacCsoKwR){gPitZFNTxo = true;}
      else if(giacCsoKwR == BeNwRBARrw){zkBKpOrtkk = true;}
      if(FaABGaoeIV == BGUXZGnLTX){rOTGJoBSCF = true;}
      else if(BGUXZGnLTX == FaABGaoeIV){IkkSLlHTld = true;}
      if(WJoOEadgzk == uyrOeELNqr){nKweBlhBLX = true;}
      else if(uyrOeELNqr == WJoOEadgzk){WZlHfbiGiD = true;}
      if(TeXYPhjkDU == qcCTmgpCDt){WkluKYIeZu = true;}
      else if(qcCTmgpCDt == TeXYPhjkDU){PpiLaqiuxY = true;}
      if(yyTHkiKMBs == NVIQVlQTmp){HQwPMbJxwX = true;}
      else if(NVIQVlQTmp == yyTHkiKMBs){uoQBeTTTZl = true;}
      if(xQyTproyrp == qVsHOhpMyx){jjBjIWSDsn = true;}
      else if(qVsHOhpMyx == xQyTproyrp){mnkTiYytdO = true;}
      if(XSRHbaCalX == gbSDaYEBkr){WMHYRGcYuk = true;}
      else if(gbSDaYEBkr == XSRHbaCalX){ekLhUSCYqU = true;}
      if(pEanXXphdU == PlHYKZpbrr){gVrHyXNgSZ = true;}
      if(QQeGnDfEiX == nrZABVjtEF){bkFnmmiCln = true;}
      if(slrNwegMfJ == pdDFMlCEox){FEllXuIWxG = true;}
      while(PlHYKZpbrr == pEanXXphdU){CMVMihIkcL = true;}
      while(nrZABVjtEF == nrZABVjtEF){IPfxPaEPbB = true;}
      while(pdDFMlCEox == pdDFMlCEox){roQitJchfL = true;}
      if(gPitZFNTxo == true){gPitZFNTxo = false;}
      if(rOTGJoBSCF == true){rOTGJoBSCF = false;}
      if(nKweBlhBLX == true){nKweBlhBLX = false;}
      if(WkluKYIeZu == true){WkluKYIeZu = false;}
      if(HQwPMbJxwX == true){HQwPMbJxwX = false;}
      if(jjBjIWSDsn == true){jjBjIWSDsn = false;}
      if(WMHYRGcYuk == true){WMHYRGcYuk = false;}
      if(gVrHyXNgSZ == true){gVrHyXNgSZ = false;}
      if(bkFnmmiCln == true){bkFnmmiCln = false;}
      if(FEllXuIWxG == true){FEllXuIWxG = false;}
      if(zkBKpOrtkk == true){zkBKpOrtkk = false;}
      if(IkkSLlHTld == true){IkkSLlHTld = false;}
      if(WZlHfbiGiD == true){WZlHfbiGiD = false;}
      if(PpiLaqiuxY == true){PpiLaqiuxY = false;}
      if(uoQBeTTTZl == true){uoQBeTTTZl = false;}
      if(mnkTiYytdO == true){mnkTiYytdO = false;}
      if(ekLhUSCYqU == true){ekLhUSCYqU = false;}
      if(CMVMihIkcL == true){CMVMihIkcL = false;}
      if(IPfxPaEPbB == true){IPfxPaEPbB = false;}
      if(roQitJchfL == true){roQitJchfL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VIWFKEOSIM
{ 
  void FUSXnOcNkQ()
  { 
      bool EuWsIXJCtP = false;
      bool VPEkhHpXmZ = false;
      bool nfAboBgKWb = false;
      bool yMrDCiVKeu = false;
      bool tejToLnHRc = false;
      bool PkqyhYuuEG = false;
      bool qzeRQJXBhz = false;
      bool kfsqfJuglc = false;
      bool NZssMNUsUd = false;
      bool naFXEuzSCf = false;
      bool nlZSriqzSY = false;
      bool cNIasRGlFD = false;
      bool ndgDKKZVmk = false;
      bool KcdGoazZBc = false;
      bool VUawAaRedm = false;
      bool nNNzqJFVIg = false;
      bool JUMhNAiBlS = false;
      bool RfjbgSDkDj = false;
      bool rurzwxOeOf = false;
      bool UdRUTAHshz = false;
      string rDAFRnfCAO;
      string uxBrSwRTgB;
      string YhUFihwTqR;
      string UtMbRPQrTQ;
      string XFlDAXZYSE;
      string cKUCWKiuVi;
      string qMLhsBkZZD;
      string fYAQdSwQEK;
      string IWAloKYJFH;
      string gVVkYKtDKz;
      string mAyOXDKEYD;
      string NRpLZTLYsh;
      string baTSWKDPrS;
      string YrGFXIYkNk;
      string AUjCsOfKKE;
      string yUKbWMgerN;
      string AtLGdVKjmQ;
      string uZKHhHpQZH;
      string erEmTEgeiL;
      string bssAkFIdYW;
      if(rDAFRnfCAO == mAyOXDKEYD){EuWsIXJCtP = true;}
      else if(mAyOXDKEYD == rDAFRnfCAO){nlZSriqzSY = true;}
      if(uxBrSwRTgB == NRpLZTLYsh){VPEkhHpXmZ = true;}
      else if(NRpLZTLYsh == uxBrSwRTgB){cNIasRGlFD = true;}
      if(YhUFihwTqR == baTSWKDPrS){nfAboBgKWb = true;}
      else if(baTSWKDPrS == YhUFihwTqR){ndgDKKZVmk = true;}
      if(UtMbRPQrTQ == YrGFXIYkNk){yMrDCiVKeu = true;}
      else if(YrGFXIYkNk == UtMbRPQrTQ){KcdGoazZBc = true;}
      if(XFlDAXZYSE == AUjCsOfKKE){tejToLnHRc = true;}
      else if(AUjCsOfKKE == XFlDAXZYSE){VUawAaRedm = true;}
      if(cKUCWKiuVi == yUKbWMgerN){PkqyhYuuEG = true;}
      else if(yUKbWMgerN == cKUCWKiuVi){nNNzqJFVIg = true;}
      if(qMLhsBkZZD == AtLGdVKjmQ){qzeRQJXBhz = true;}
      else if(AtLGdVKjmQ == qMLhsBkZZD){JUMhNAiBlS = true;}
      if(fYAQdSwQEK == uZKHhHpQZH){kfsqfJuglc = true;}
      if(IWAloKYJFH == erEmTEgeiL){NZssMNUsUd = true;}
      if(gVVkYKtDKz == bssAkFIdYW){naFXEuzSCf = true;}
      while(uZKHhHpQZH == fYAQdSwQEK){RfjbgSDkDj = true;}
      while(erEmTEgeiL == erEmTEgeiL){rurzwxOeOf = true;}
      while(bssAkFIdYW == bssAkFIdYW){UdRUTAHshz = true;}
      if(EuWsIXJCtP == true){EuWsIXJCtP = false;}
      if(VPEkhHpXmZ == true){VPEkhHpXmZ = false;}
      if(nfAboBgKWb == true){nfAboBgKWb = false;}
      if(yMrDCiVKeu == true){yMrDCiVKeu = false;}
      if(tejToLnHRc == true){tejToLnHRc = false;}
      if(PkqyhYuuEG == true){PkqyhYuuEG = false;}
      if(qzeRQJXBhz == true){qzeRQJXBhz = false;}
      if(kfsqfJuglc == true){kfsqfJuglc = false;}
      if(NZssMNUsUd == true){NZssMNUsUd = false;}
      if(naFXEuzSCf == true){naFXEuzSCf = false;}
      if(nlZSriqzSY == true){nlZSriqzSY = false;}
      if(cNIasRGlFD == true){cNIasRGlFD = false;}
      if(ndgDKKZVmk == true){ndgDKKZVmk = false;}
      if(KcdGoazZBc == true){KcdGoazZBc = false;}
      if(VUawAaRedm == true){VUawAaRedm = false;}
      if(nNNzqJFVIg == true){nNNzqJFVIg = false;}
      if(JUMhNAiBlS == true){JUMhNAiBlS = false;}
      if(RfjbgSDkDj == true){RfjbgSDkDj = false;}
      if(rurzwxOeOf == true){rurzwxOeOf = false;}
      if(UdRUTAHshz == true){UdRUTAHshz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSQKPRVGTT
{ 
  void DUFEpCtHPo()
  { 
      bool YjlUoyTzQN = false;
      bool KOPirgLZOO = false;
      bool lgTjBINkoZ = false;
      bool hcCCdqkKzN = false;
      bool IbisHjFFVF = false;
      bool gyBcqrQCSg = false;
      bool kiJpehLMFA = false;
      bool wAaAGKyZbR = false;
      bool DHPisjaZLl = false;
      bool ahqRcZSrOZ = false;
      bool XrAUJfWBWg = false;
      bool sqZBdcSZwt = false;
      bool GlBSZNJIWg = false;
      bool qFKCsKHuZN = false;
      bool NZDdriIonA = false;
      bool GruUTlqguu = false;
      bool WOdpomgXHS = false;
      bool UWAigfiWap = false;
      bool FTTWZzKohH = false;
      bool SaAdqywNoE = false;
      string hRssnPBSeV;
      string DgFDlDWKMZ;
      string RTgDMikzxC;
      string sBPFWGCugr;
      string gVWMPDmAbH;
      string sTqiiNjpgE;
      string eBVbbCQzgf;
      string AacUswxUnI;
      string wjXoIZJgVI;
      string VMNcNeAtkM;
      string mmTwHRqWom;
      string QPBYItdgSB;
      string sjdXJmMAHN;
      string uCiaVIQagq;
      string ilqirGLoUS;
      string BTaiTCJulT;
      string EpOaqNgaCz;
      string dCzbSGrtfD;
      string bXenMbbzHS;
      string yUoNmrXPqd;
      if(hRssnPBSeV == mmTwHRqWom){YjlUoyTzQN = true;}
      else if(mmTwHRqWom == hRssnPBSeV){XrAUJfWBWg = true;}
      if(DgFDlDWKMZ == QPBYItdgSB){KOPirgLZOO = true;}
      else if(QPBYItdgSB == DgFDlDWKMZ){sqZBdcSZwt = true;}
      if(RTgDMikzxC == sjdXJmMAHN){lgTjBINkoZ = true;}
      else if(sjdXJmMAHN == RTgDMikzxC){GlBSZNJIWg = true;}
      if(sBPFWGCugr == uCiaVIQagq){hcCCdqkKzN = true;}
      else if(uCiaVIQagq == sBPFWGCugr){qFKCsKHuZN = true;}
      if(gVWMPDmAbH == ilqirGLoUS){IbisHjFFVF = true;}
      else if(ilqirGLoUS == gVWMPDmAbH){NZDdriIonA = true;}
      if(sTqiiNjpgE == BTaiTCJulT){gyBcqrQCSg = true;}
      else if(BTaiTCJulT == sTqiiNjpgE){GruUTlqguu = true;}
      if(eBVbbCQzgf == EpOaqNgaCz){kiJpehLMFA = true;}
      else if(EpOaqNgaCz == eBVbbCQzgf){WOdpomgXHS = true;}
      if(AacUswxUnI == dCzbSGrtfD){wAaAGKyZbR = true;}
      if(wjXoIZJgVI == bXenMbbzHS){DHPisjaZLl = true;}
      if(VMNcNeAtkM == yUoNmrXPqd){ahqRcZSrOZ = true;}
      while(dCzbSGrtfD == AacUswxUnI){UWAigfiWap = true;}
      while(bXenMbbzHS == bXenMbbzHS){FTTWZzKohH = true;}
      while(yUoNmrXPqd == yUoNmrXPqd){SaAdqywNoE = true;}
      if(YjlUoyTzQN == true){YjlUoyTzQN = false;}
      if(KOPirgLZOO == true){KOPirgLZOO = false;}
      if(lgTjBINkoZ == true){lgTjBINkoZ = false;}
      if(hcCCdqkKzN == true){hcCCdqkKzN = false;}
      if(IbisHjFFVF == true){IbisHjFFVF = false;}
      if(gyBcqrQCSg == true){gyBcqrQCSg = false;}
      if(kiJpehLMFA == true){kiJpehLMFA = false;}
      if(wAaAGKyZbR == true){wAaAGKyZbR = false;}
      if(DHPisjaZLl == true){DHPisjaZLl = false;}
      if(ahqRcZSrOZ == true){ahqRcZSrOZ = false;}
      if(XrAUJfWBWg == true){XrAUJfWBWg = false;}
      if(sqZBdcSZwt == true){sqZBdcSZwt = false;}
      if(GlBSZNJIWg == true){GlBSZNJIWg = false;}
      if(qFKCsKHuZN == true){qFKCsKHuZN = false;}
      if(NZDdriIonA == true){NZDdriIonA = false;}
      if(GruUTlqguu == true){GruUTlqguu = false;}
      if(WOdpomgXHS == true){WOdpomgXHS = false;}
      if(UWAigfiWap == true){UWAigfiWap = false;}
      if(FTTWZzKohH == true){FTTWZzKohH = false;}
      if(SaAdqywNoE == true){SaAdqywNoE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFTBKEBOFV
{ 
  void satFYgVgQV()
  { 
      bool ZbFxHBThQT = false;
      bool CEbGjAXWii = false;
      bool dJoMyYIyym = false;
      bool FSMUdoJLIB = false;
      bool gnUwjqINZR = false;
      bool VGHpcPlsyi = false;
      bool sVicNiqGbt = false;
      bool qMNhCoorcH = false;
      bool PuXfRzLWqN = false;
      bool CPMZHKFqhA = false;
      bool zBkeaJrYmn = false;
      bool asQpSyxDLO = false;
      bool XUOOqaznar = false;
      bool jxKbIOKsEH = false;
      bool GmiDlJzVGJ = false;
      bool MBfTcelVmA = false;
      bool KEyuEdinhE = false;
      bool nEyDHkkLbh = false;
      bool adhQehQqzd = false;
      bool bnFExCnnzI = false;
      string deGmgyhrui;
      string rXWdiGaDjU;
      string smMLnbZPPb;
      string RFkFSOBCdm;
      string CWSXonDyDF;
      string IISlipRuyE;
      string YScTRlmRLU;
      string FXZwRWUoVA;
      string XaMKTJlyVb;
      string xGDYOjtzGC;
      string BlmhzjhVUM;
      string VcYyfxGRAI;
      string znuiXyUBhg;
      string cVhSzlndKi;
      string aQdJGTgErQ;
      string dbzxCMpDKB;
      string PgmmjAtFzt;
      string IbHQgiKlbD;
      string QPJQDAVkQl;
      string ujTJStcqYG;
      if(deGmgyhrui == BlmhzjhVUM){ZbFxHBThQT = true;}
      else if(BlmhzjhVUM == deGmgyhrui){zBkeaJrYmn = true;}
      if(rXWdiGaDjU == VcYyfxGRAI){CEbGjAXWii = true;}
      else if(VcYyfxGRAI == rXWdiGaDjU){asQpSyxDLO = true;}
      if(smMLnbZPPb == znuiXyUBhg){dJoMyYIyym = true;}
      else if(znuiXyUBhg == smMLnbZPPb){XUOOqaznar = true;}
      if(RFkFSOBCdm == cVhSzlndKi){FSMUdoJLIB = true;}
      else if(cVhSzlndKi == RFkFSOBCdm){jxKbIOKsEH = true;}
      if(CWSXonDyDF == aQdJGTgErQ){gnUwjqINZR = true;}
      else if(aQdJGTgErQ == CWSXonDyDF){GmiDlJzVGJ = true;}
      if(IISlipRuyE == dbzxCMpDKB){VGHpcPlsyi = true;}
      else if(dbzxCMpDKB == IISlipRuyE){MBfTcelVmA = true;}
      if(YScTRlmRLU == PgmmjAtFzt){sVicNiqGbt = true;}
      else if(PgmmjAtFzt == YScTRlmRLU){KEyuEdinhE = true;}
      if(FXZwRWUoVA == IbHQgiKlbD){qMNhCoorcH = true;}
      if(XaMKTJlyVb == QPJQDAVkQl){PuXfRzLWqN = true;}
      if(xGDYOjtzGC == ujTJStcqYG){CPMZHKFqhA = true;}
      while(IbHQgiKlbD == FXZwRWUoVA){nEyDHkkLbh = true;}
      while(QPJQDAVkQl == QPJQDAVkQl){adhQehQqzd = true;}
      while(ujTJStcqYG == ujTJStcqYG){bnFExCnnzI = true;}
      if(ZbFxHBThQT == true){ZbFxHBThQT = false;}
      if(CEbGjAXWii == true){CEbGjAXWii = false;}
      if(dJoMyYIyym == true){dJoMyYIyym = false;}
      if(FSMUdoJLIB == true){FSMUdoJLIB = false;}
      if(gnUwjqINZR == true){gnUwjqINZR = false;}
      if(VGHpcPlsyi == true){VGHpcPlsyi = false;}
      if(sVicNiqGbt == true){sVicNiqGbt = false;}
      if(qMNhCoorcH == true){qMNhCoorcH = false;}
      if(PuXfRzLWqN == true){PuXfRzLWqN = false;}
      if(CPMZHKFqhA == true){CPMZHKFqhA = false;}
      if(zBkeaJrYmn == true){zBkeaJrYmn = false;}
      if(asQpSyxDLO == true){asQpSyxDLO = false;}
      if(XUOOqaznar == true){XUOOqaznar = false;}
      if(jxKbIOKsEH == true){jxKbIOKsEH = false;}
      if(GmiDlJzVGJ == true){GmiDlJzVGJ = false;}
      if(MBfTcelVmA == true){MBfTcelVmA = false;}
      if(KEyuEdinhE == true){KEyuEdinhE = false;}
      if(nEyDHkkLbh == true){nEyDHkkLbh = false;}
      if(adhQehQqzd == true){adhQehQqzd = false;}
      if(bnFExCnnzI == true){bnFExCnnzI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZRHIGWAJB
{ 
  void oIcoMHZZRp()
  { 
      bool zRmNTaXrdj = false;
      bool jynZhGKVDQ = false;
      bool umhGyiApST = false;
      bool KZrmguhksS = false;
      bool kRkorpTFKt = false;
      bool XCfyzLjfOj = false;
      bool ZgZJYJFAsm = false;
      bool YZbjfdCsOI = false;
      bool OufYwIttmV = false;
      bool LBVIsDrbPh = false;
      bool jSLXUxZuRV = false;
      bool IqRFVeAAMP = false;
      bool PLNXaWDTqb = false;
      bool kZcgXwiIDy = false;
      bool izbQMUjQmN = false;
      bool DqOzSYFnwy = false;
      bool tGDpjhNjhY = false;
      bool wqxOgPiwLG = false;
      bool lmfdXtLcOz = false;
      bool qtMEDbukfd = false;
      string zBTTGPrLpk;
      string dXoDyiIApt;
      string WojSJZIyPr;
      string rYDOnQYmPm;
      string TbIQPEcWWr;
      string qrJXkJQBKf;
      string HtuyrFUZPh;
      string JVjDZugSCF;
      string xlaWAzOede;
      string zXbjfZfJYK;
      string iCHohVIGyo;
      string cxyFiVSYxs;
      string qpwjhlszXA;
      string PWtrVuelod;
      string qHfnBCYWBK;
      string GHMfSsGWGw;
      string cIixYGCGim;
      string pfiTBiJHif;
      string NVyMsIKOYb;
      string nHfrBhXiOu;
      if(zBTTGPrLpk == iCHohVIGyo){zRmNTaXrdj = true;}
      else if(iCHohVIGyo == zBTTGPrLpk){jSLXUxZuRV = true;}
      if(dXoDyiIApt == cxyFiVSYxs){jynZhGKVDQ = true;}
      else if(cxyFiVSYxs == dXoDyiIApt){IqRFVeAAMP = true;}
      if(WojSJZIyPr == qpwjhlszXA){umhGyiApST = true;}
      else if(qpwjhlszXA == WojSJZIyPr){PLNXaWDTqb = true;}
      if(rYDOnQYmPm == PWtrVuelod){KZrmguhksS = true;}
      else if(PWtrVuelod == rYDOnQYmPm){kZcgXwiIDy = true;}
      if(TbIQPEcWWr == qHfnBCYWBK){kRkorpTFKt = true;}
      else if(qHfnBCYWBK == TbIQPEcWWr){izbQMUjQmN = true;}
      if(qrJXkJQBKf == GHMfSsGWGw){XCfyzLjfOj = true;}
      else if(GHMfSsGWGw == qrJXkJQBKf){DqOzSYFnwy = true;}
      if(HtuyrFUZPh == cIixYGCGim){ZgZJYJFAsm = true;}
      else if(cIixYGCGim == HtuyrFUZPh){tGDpjhNjhY = true;}
      if(JVjDZugSCF == pfiTBiJHif){YZbjfdCsOI = true;}
      if(xlaWAzOede == NVyMsIKOYb){OufYwIttmV = true;}
      if(zXbjfZfJYK == nHfrBhXiOu){LBVIsDrbPh = true;}
      while(pfiTBiJHif == JVjDZugSCF){wqxOgPiwLG = true;}
      while(NVyMsIKOYb == NVyMsIKOYb){lmfdXtLcOz = true;}
      while(nHfrBhXiOu == nHfrBhXiOu){qtMEDbukfd = true;}
      if(zRmNTaXrdj == true){zRmNTaXrdj = false;}
      if(jynZhGKVDQ == true){jynZhGKVDQ = false;}
      if(umhGyiApST == true){umhGyiApST = false;}
      if(KZrmguhksS == true){KZrmguhksS = false;}
      if(kRkorpTFKt == true){kRkorpTFKt = false;}
      if(XCfyzLjfOj == true){XCfyzLjfOj = false;}
      if(ZgZJYJFAsm == true){ZgZJYJFAsm = false;}
      if(YZbjfdCsOI == true){YZbjfdCsOI = false;}
      if(OufYwIttmV == true){OufYwIttmV = false;}
      if(LBVIsDrbPh == true){LBVIsDrbPh = false;}
      if(jSLXUxZuRV == true){jSLXUxZuRV = false;}
      if(IqRFVeAAMP == true){IqRFVeAAMP = false;}
      if(PLNXaWDTqb == true){PLNXaWDTqb = false;}
      if(kZcgXwiIDy == true){kZcgXwiIDy = false;}
      if(izbQMUjQmN == true){izbQMUjQmN = false;}
      if(DqOzSYFnwy == true){DqOzSYFnwy = false;}
      if(tGDpjhNjhY == true){tGDpjhNjhY = false;}
      if(wqxOgPiwLG == true){wqxOgPiwLG = false;}
      if(lmfdXtLcOz == true){lmfdXtLcOz = false;}
      if(qtMEDbukfd == true){qtMEDbukfd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWDNYLKSMA
{ 
  void SXfkPUkAyC()
  { 
      bool RjLUVdDRCa = false;
      bool sbUgXEoXMh = false;
      bool EyPDBCnSYL = false;
      bool PugSpqTlbH = false;
      bool tPUeDfOYAs = false;
      bool YelCUSTHTS = false;
      bool pjsqKyuBpg = false;
      bool jDwEmodjAV = false;
      bool nORflkIdyX = false;
      bool WLSIRJWcUE = false;
      bool kMiTIVhhOe = false;
      bool ojHyeaSMEY = false;
      bool oQDSKYjmld = false;
      bool SAPukbfyXQ = false;
      bool CaOShlEUdq = false;
      bool qJYuOTIQJj = false;
      bool kuukLnULNC = false;
      bool tUnnVOBjjX = false;
      bool TPJulIbTgQ = false;
      bool TPoneHedHs = false;
      string oCICeCrHpm;
      string MttTCftLiN;
      string jROGzkFVnc;
      string FWsUsxaCjl;
      string leExXgEroj;
      string TKXkdWnCDs;
      string wWTMgoAZZE;
      string EqbwaENQhR;
      string gNfDJtzIpV;
      string JYyppPLqPi;
      string gdRjecibKY;
      string JWTlLhpQDl;
      string prjEufrkGL;
      string sWAykCwuYg;
      string LXyQMmEMdI;
      string YundsntMoz;
      string jxVyfmVUAJ;
      string luqVaStSrH;
      string afHxlxhWFw;
      string HiGYxOCzkZ;
      if(oCICeCrHpm == gdRjecibKY){RjLUVdDRCa = true;}
      else if(gdRjecibKY == oCICeCrHpm){kMiTIVhhOe = true;}
      if(MttTCftLiN == JWTlLhpQDl){sbUgXEoXMh = true;}
      else if(JWTlLhpQDl == MttTCftLiN){ojHyeaSMEY = true;}
      if(jROGzkFVnc == prjEufrkGL){EyPDBCnSYL = true;}
      else if(prjEufrkGL == jROGzkFVnc){oQDSKYjmld = true;}
      if(FWsUsxaCjl == sWAykCwuYg){PugSpqTlbH = true;}
      else if(sWAykCwuYg == FWsUsxaCjl){SAPukbfyXQ = true;}
      if(leExXgEroj == LXyQMmEMdI){tPUeDfOYAs = true;}
      else if(LXyQMmEMdI == leExXgEroj){CaOShlEUdq = true;}
      if(TKXkdWnCDs == YundsntMoz){YelCUSTHTS = true;}
      else if(YundsntMoz == TKXkdWnCDs){qJYuOTIQJj = true;}
      if(wWTMgoAZZE == jxVyfmVUAJ){pjsqKyuBpg = true;}
      else if(jxVyfmVUAJ == wWTMgoAZZE){kuukLnULNC = true;}
      if(EqbwaENQhR == luqVaStSrH){jDwEmodjAV = true;}
      if(gNfDJtzIpV == afHxlxhWFw){nORflkIdyX = true;}
      if(JYyppPLqPi == HiGYxOCzkZ){WLSIRJWcUE = true;}
      while(luqVaStSrH == EqbwaENQhR){tUnnVOBjjX = true;}
      while(afHxlxhWFw == afHxlxhWFw){TPJulIbTgQ = true;}
      while(HiGYxOCzkZ == HiGYxOCzkZ){TPoneHedHs = true;}
      if(RjLUVdDRCa == true){RjLUVdDRCa = false;}
      if(sbUgXEoXMh == true){sbUgXEoXMh = false;}
      if(EyPDBCnSYL == true){EyPDBCnSYL = false;}
      if(PugSpqTlbH == true){PugSpqTlbH = false;}
      if(tPUeDfOYAs == true){tPUeDfOYAs = false;}
      if(YelCUSTHTS == true){YelCUSTHTS = false;}
      if(pjsqKyuBpg == true){pjsqKyuBpg = false;}
      if(jDwEmodjAV == true){jDwEmodjAV = false;}
      if(nORflkIdyX == true){nORflkIdyX = false;}
      if(WLSIRJWcUE == true){WLSIRJWcUE = false;}
      if(kMiTIVhhOe == true){kMiTIVhhOe = false;}
      if(ojHyeaSMEY == true){ojHyeaSMEY = false;}
      if(oQDSKYjmld == true){oQDSKYjmld = false;}
      if(SAPukbfyXQ == true){SAPukbfyXQ = false;}
      if(CaOShlEUdq == true){CaOShlEUdq = false;}
      if(qJYuOTIQJj == true){qJYuOTIQJj = false;}
      if(kuukLnULNC == true){kuukLnULNC = false;}
      if(tUnnVOBjjX == true){tUnnVOBjjX = false;}
      if(TPJulIbTgQ == true){TPJulIbTgQ = false;}
      if(TPoneHedHs == true){TPoneHedHs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBAGCJSSTL
{ 
  void JBsKqjiTAJ()
  { 
      bool IofdDLczCg = false;
      bool XeguYaBBTP = false;
      bool FWCcFIFGQf = false;
      bool aPopigyeXU = false;
      bool XiimgDKgZs = false;
      bool zkIJgkmCYt = false;
      bool GViVFHoqMq = false;
      bool cVdzqVnOuC = false;
      bool xYfWgpHfIy = false;
      bool tuGcNCAMhZ = false;
      bool NTThQdGJSK = false;
      bool wXHWxgpLoP = false;
      bool AJhNxgOBko = false;
      bool VbgVndExGC = false;
      bool jyNyBWnjfg = false;
      bool LoXRZEkGki = false;
      bool OEXdoUplhS = false;
      bool brEleCujMa = false;
      bool reVEcfDOwi = false;
      bool syLWmeZjIf = false;
      string fthwDBQPXn;
      string QcAHXEzfRS;
      string cDSJdPdInl;
      string uQAHPVWlVe;
      string AKjUXRpJxN;
      string LwstScaXRn;
      string XIblrzcsrC;
      string hNJlSSSylL;
      string YTKaZyWFol;
      string tyTgHriycX;
      string oxQueymHbz;
      string JclFPDxAMs;
      string cXDFHisbea;
      string iUUOWbDPua;
      string LPdobQMORD;
      string thkjtRsKmu;
      string FKcAQoIWim;
      string AhFlgNsOcq;
      string WdJafBikTF;
      string hrbzUAlcYm;
      if(fthwDBQPXn == oxQueymHbz){IofdDLczCg = true;}
      else if(oxQueymHbz == fthwDBQPXn){NTThQdGJSK = true;}
      if(QcAHXEzfRS == JclFPDxAMs){XeguYaBBTP = true;}
      else if(JclFPDxAMs == QcAHXEzfRS){wXHWxgpLoP = true;}
      if(cDSJdPdInl == cXDFHisbea){FWCcFIFGQf = true;}
      else if(cXDFHisbea == cDSJdPdInl){AJhNxgOBko = true;}
      if(uQAHPVWlVe == iUUOWbDPua){aPopigyeXU = true;}
      else if(iUUOWbDPua == uQAHPVWlVe){VbgVndExGC = true;}
      if(AKjUXRpJxN == LPdobQMORD){XiimgDKgZs = true;}
      else if(LPdobQMORD == AKjUXRpJxN){jyNyBWnjfg = true;}
      if(LwstScaXRn == thkjtRsKmu){zkIJgkmCYt = true;}
      else if(thkjtRsKmu == LwstScaXRn){LoXRZEkGki = true;}
      if(XIblrzcsrC == FKcAQoIWim){GViVFHoqMq = true;}
      else if(FKcAQoIWim == XIblrzcsrC){OEXdoUplhS = true;}
      if(hNJlSSSylL == AhFlgNsOcq){cVdzqVnOuC = true;}
      if(YTKaZyWFol == WdJafBikTF){xYfWgpHfIy = true;}
      if(tyTgHriycX == hrbzUAlcYm){tuGcNCAMhZ = true;}
      while(AhFlgNsOcq == hNJlSSSylL){brEleCujMa = true;}
      while(WdJafBikTF == WdJafBikTF){reVEcfDOwi = true;}
      while(hrbzUAlcYm == hrbzUAlcYm){syLWmeZjIf = true;}
      if(IofdDLczCg == true){IofdDLczCg = false;}
      if(XeguYaBBTP == true){XeguYaBBTP = false;}
      if(FWCcFIFGQf == true){FWCcFIFGQf = false;}
      if(aPopigyeXU == true){aPopigyeXU = false;}
      if(XiimgDKgZs == true){XiimgDKgZs = false;}
      if(zkIJgkmCYt == true){zkIJgkmCYt = false;}
      if(GViVFHoqMq == true){GViVFHoqMq = false;}
      if(cVdzqVnOuC == true){cVdzqVnOuC = false;}
      if(xYfWgpHfIy == true){xYfWgpHfIy = false;}
      if(tuGcNCAMhZ == true){tuGcNCAMhZ = false;}
      if(NTThQdGJSK == true){NTThQdGJSK = false;}
      if(wXHWxgpLoP == true){wXHWxgpLoP = false;}
      if(AJhNxgOBko == true){AJhNxgOBko = false;}
      if(VbgVndExGC == true){VbgVndExGC = false;}
      if(jyNyBWnjfg == true){jyNyBWnjfg = false;}
      if(LoXRZEkGki == true){LoXRZEkGki = false;}
      if(OEXdoUplhS == true){OEXdoUplhS = false;}
      if(brEleCujMa == true){brEleCujMa = false;}
      if(reVEcfDOwi == true){reVEcfDOwi = false;}
      if(syLWmeZjIf == true){syLWmeZjIf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGLHYLPTGS
{ 
  void BfjpWbeRGV()
  { 
      bool cfQKMZPBOb = false;
      bool OeViPpQaHL = false;
      bool iMyJcFmyGe = false;
      bool inHLpmeWoy = false;
      bool DRxxMoUlnu = false;
      bool jLtapPgHgG = false;
      bool lRtjrZWJrb = false;
      bool LtkIHRPBxm = false;
      bool kBJLtXtgVa = false;
      bool FXohLlWNEl = false;
      bool SKsLjpZkSX = false;
      bool zfKsVkHioU = false;
      bool eonRWmEDxV = false;
      bool uCxKUZHyaE = false;
      bool xINxaZNuLZ = false;
      bool emXjHcWanw = false;
      bool kWnxcwizYw = false;
      bool dIIjWWbpqx = false;
      bool ZIqWqHeMDq = false;
      bool DfKdTaUQUd = false;
      string NUSLaEjEsU;
      string yaZnjOJGkH;
      string bVNWkFqMVO;
      string HKeiilssTS;
      string lmskUZbYTc;
      string CXGJDrGuaU;
      string NXheMnuqEy;
      string VQlRVobcCK;
      string dSrsLiDVeq;
      string exRyFNFOXg;
      string dkTVGlkomO;
      string PdsQquenSd;
      string jYLMTXynMH;
      string jNFVfsyWlZ;
      string yOhQbBEBHJ;
      string hQutwFYHBi;
      string mxcfdCXXjx;
      string xIBseUqtkS;
      string TwgCYSSLYa;
      string TqUDlAlClY;
      if(NUSLaEjEsU == dkTVGlkomO){cfQKMZPBOb = true;}
      else if(dkTVGlkomO == NUSLaEjEsU){SKsLjpZkSX = true;}
      if(yaZnjOJGkH == PdsQquenSd){OeViPpQaHL = true;}
      else if(PdsQquenSd == yaZnjOJGkH){zfKsVkHioU = true;}
      if(bVNWkFqMVO == jYLMTXynMH){iMyJcFmyGe = true;}
      else if(jYLMTXynMH == bVNWkFqMVO){eonRWmEDxV = true;}
      if(HKeiilssTS == jNFVfsyWlZ){inHLpmeWoy = true;}
      else if(jNFVfsyWlZ == HKeiilssTS){uCxKUZHyaE = true;}
      if(lmskUZbYTc == yOhQbBEBHJ){DRxxMoUlnu = true;}
      else if(yOhQbBEBHJ == lmskUZbYTc){xINxaZNuLZ = true;}
      if(CXGJDrGuaU == hQutwFYHBi){jLtapPgHgG = true;}
      else if(hQutwFYHBi == CXGJDrGuaU){emXjHcWanw = true;}
      if(NXheMnuqEy == mxcfdCXXjx){lRtjrZWJrb = true;}
      else if(mxcfdCXXjx == NXheMnuqEy){kWnxcwizYw = true;}
      if(VQlRVobcCK == xIBseUqtkS){LtkIHRPBxm = true;}
      if(dSrsLiDVeq == TwgCYSSLYa){kBJLtXtgVa = true;}
      if(exRyFNFOXg == TqUDlAlClY){FXohLlWNEl = true;}
      while(xIBseUqtkS == VQlRVobcCK){dIIjWWbpqx = true;}
      while(TwgCYSSLYa == TwgCYSSLYa){ZIqWqHeMDq = true;}
      while(TqUDlAlClY == TqUDlAlClY){DfKdTaUQUd = true;}
      if(cfQKMZPBOb == true){cfQKMZPBOb = false;}
      if(OeViPpQaHL == true){OeViPpQaHL = false;}
      if(iMyJcFmyGe == true){iMyJcFmyGe = false;}
      if(inHLpmeWoy == true){inHLpmeWoy = false;}
      if(DRxxMoUlnu == true){DRxxMoUlnu = false;}
      if(jLtapPgHgG == true){jLtapPgHgG = false;}
      if(lRtjrZWJrb == true){lRtjrZWJrb = false;}
      if(LtkIHRPBxm == true){LtkIHRPBxm = false;}
      if(kBJLtXtgVa == true){kBJLtXtgVa = false;}
      if(FXohLlWNEl == true){FXohLlWNEl = false;}
      if(SKsLjpZkSX == true){SKsLjpZkSX = false;}
      if(zfKsVkHioU == true){zfKsVkHioU = false;}
      if(eonRWmEDxV == true){eonRWmEDxV = false;}
      if(uCxKUZHyaE == true){uCxKUZHyaE = false;}
      if(xINxaZNuLZ == true){xINxaZNuLZ = false;}
      if(emXjHcWanw == true){emXjHcWanw = false;}
      if(kWnxcwizYw == true){kWnxcwizYw = false;}
      if(dIIjWWbpqx == true){dIIjWWbpqx = false;}
      if(ZIqWqHeMDq == true){ZIqWqHeMDq = false;}
      if(DfKdTaUQUd == true){DfKdTaUQUd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VUFMQYFTXO
{ 
  void oXJDwACSml()
  { 
      bool KpWGsGrbkz = false;
      bool fcRCufCFBZ = false;
      bool JazlOwZlAS = false;
      bool gxytArZluK = false;
      bool hUAkGSkbhx = false;
      bool IXqhrjpjqw = false;
      bool gFaRShdWCC = false;
      bool GQJpqnZNfu = false;
      bool LxEDKJGQCQ = false;
      bool BpuycbtiSY = false;
      bool oNZfqrNApD = false;
      bool JcEukjBXHJ = false;
      bool aMUlAPVLNO = false;
      bool tquGGxWYLS = false;
      bool uGayGYkzMs = false;
      bool aVaIxbsnea = false;
      bool WBmaJRgxom = false;
      bool McLoNUlVeb = false;
      bool eVzTnXPlJe = false;
      bool EiskusSzno = false;
      string qHYaGelIbd;
      string rwDoOjOsBd;
      string LquHMlcBrR;
      string gNntRwWrbL;
      string swzuUfHqNz;
      string qVQgAAMROU;
      string CjPKwdIIWR;
      string NVQpkPqzlf;
      string dlnsaLxGsR;
      string jEdHJIfozq;
      string XyTulUEZuk;
      string IMehpQwWjj;
      string gBPFhIrJgc;
      string jCAuIeRrGF;
      string GWKIIWZuQr;
      string LIFOKViONd;
      string cusSBGMjYK;
      string zEPddKpGwK;
      string hwrnRaxkkl;
      string wCeccKcrHB;
      if(qHYaGelIbd == XyTulUEZuk){KpWGsGrbkz = true;}
      else if(XyTulUEZuk == qHYaGelIbd){oNZfqrNApD = true;}
      if(rwDoOjOsBd == IMehpQwWjj){fcRCufCFBZ = true;}
      else if(IMehpQwWjj == rwDoOjOsBd){JcEukjBXHJ = true;}
      if(LquHMlcBrR == gBPFhIrJgc){JazlOwZlAS = true;}
      else if(gBPFhIrJgc == LquHMlcBrR){aMUlAPVLNO = true;}
      if(gNntRwWrbL == jCAuIeRrGF){gxytArZluK = true;}
      else if(jCAuIeRrGF == gNntRwWrbL){tquGGxWYLS = true;}
      if(swzuUfHqNz == GWKIIWZuQr){hUAkGSkbhx = true;}
      else if(GWKIIWZuQr == swzuUfHqNz){uGayGYkzMs = true;}
      if(qVQgAAMROU == LIFOKViONd){IXqhrjpjqw = true;}
      else if(LIFOKViONd == qVQgAAMROU){aVaIxbsnea = true;}
      if(CjPKwdIIWR == cusSBGMjYK){gFaRShdWCC = true;}
      else if(cusSBGMjYK == CjPKwdIIWR){WBmaJRgxom = true;}
      if(NVQpkPqzlf == zEPddKpGwK){GQJpqnZNfu = true;}
      if(dlnsaLxGsR == hwrnRaxkkl){LxEDKJGQCQ = true;}
      if(jEdHJIfozq == wCeccKcrHB){BpuycbtiSY = true;}
      while(zEPddKpGwK == NVQpkPqzlf){McLoNUlVeb = true;}
      while(hwrnRaxkkl == hwrnRaxkkl){eVzTnXPlJe = true;}
      while(wCeccKcrHB == wCeccKcrHB){EiskusSzno = true;}
      if(KpWGsGrbkz == true){KpWGsGrbkz = false;}
      if(fcRCufCFBZ == true){fcRCufCFBZ = false;}
      if(JazlOwZlAS == true){JazlOwZlAS = false;}
      if(gxytArZluK == true){gxytArZluK = false;}
      if(hUAkGSkbhx == true){hUAkGSkbhx = false;}
      if(IXqhrjpjqw == true){IXqhrjpjqw = false;}
      if(gFaRShdWCC == true){gFaRShdWCC = false;}
      if(GQJpqnZNfu == true){GQJpqnZNfu = false;}
      if(LxEDKJGQCQ == true){LxEDKJGQCQ = false;}
      if(BpuycbtiSY == true){BpuycbtiSY = false;}
      if(oNZfqrNApD == true){oNZfqrNApD = false;}
      if(JcEukjBXHJ == true){JcEukjBXHJ = false;}
      if(aMUlAPVLNO == true){aMUlAPVLNO = false;}
      if(tquGGxWYLS == true){tquGGxWYLS = false;}
      if(uGayGYkzMs == true){uGayGYkzMs = false;}
      if(aVaIxbsnea == true){aVaIxbsnea = false;}
      if(WBmaJRgxom == true){WBmaJRgxom = false;}
      if(McLoNUlVeb == true){McLoNUlVeb = false;}
      if(eVzTnXPlJe == true){eVzTnXPlJe = false;}
      if(EiskusSzno == true){EiskusSzno = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NMNUREFFAP
{ 
  void mbAracjWcr()
  { 
      bool FOVgzBAnLO = false;
      bool UInQmcltOP = false;
      bool qTJKjNQEGl = false;
      bool fMutVUBjFS = false;
      bool yjzjVIXshF = false;
      bool tqawnkFLxl = false;
      bool jwhYhHMstS = false;
      bool aCowRHUYoa = false;
      bool pXWAqolyGk = false;
      bool OplThCCZBN = false;
      bool udyPdrCdeg = false;
      bool QfWVuMZghs = false;
      bool UNmJDkPUOO = false;
      bool EuWafLYGVz = false;
      bool lITYUiTQXV = false;
      bool cUrIrgpoMs = false;
      bool bgPPbUIupi = false;
      bool mSKhGMtOoT = false;
      bool RzxrljCOhy = false;
      bool VjtcWFsExz = false;
      string erWWzoJBBC;
      string NNdVNisxmk;
      string xHzRsjdaPB;
      string JwhblxQOgj;
      string kdCbCfCTVu;
      string YUgdJXrEcP;
      string KhlAsRfCjQ;
      string SeQDzSEXPN;
      string gKFUbnODSN;
      string ELkQYDrCij;
      string zAjEcsDdep;
      string STnOhAbRXE;
      string DbjVMGszdu;
      string aCofNgZBqi;
      string kkYbujWWhY;
      string badegXPOrV;
      string ADziPPeIAB;
      string ZZZoSRCHZb;
      string iWRETzYKzp;
      string QLJUigkpMe;
      if(erWWzoJBBC == zAjEcsDdep){FOVgzBAnLO = true;}
      else if(zAjEcsDdep == erWWzoJBBC){udyPdrCdeg = true;}
      if(NNdVNisxmk == STnOhAbRXE){UInQmcltOP = true;}
      else if(STnOhAbRXE == NNdVNisxmk){QfWVuMZghs = true;}
      if(xHzRsjdaPB == DbjVMGszdu){qTJKjNQEGl = true;}
      else if(DbjVMGszdu == xHzRsjdaPB){UNmJDkPUOO = true;}
      if(JwhblxQOgj == aCofNgZBqi){fMutVUBjFS = true;}
      else if(aCofNgZBqi == JwhblxQOgj){EuWafLYGVz = true;}
      if(kdCbCfCTVu == kkYbujWWhY){yjzjVIXshF = true;}
      else if(kkYbujWWhY == kdCbCfCTVu){lITYUiTQXV = true;}
      if(YUgdJXrEcP == badegXPOrV){tqawnkFLxl = true;}
      else if(badegXPOrV == YUgdJXrEcP){cUrIrgpoMs = true;}
      if(KhlAsRfCjQ == ADziPPeIAB){jwhYhHMstS = true;}
      else if(ADziPPeIAB == KhlAsRfCjQ){bgPPbUIupi = true;}
      if(SeQDzSEXPN == ZZZoSRCHZb){aCowRHUYoa = true;}
      if(gKFUbnODSN == iWRETzYKzp){pXWAqolyGk = true;}
      if(ELkQYDrCij == QLJUigkpMe){OplThCCZBN = true;}
      while(ZZZoSRCHZb == SeQDzSEXPN){mSKhGMtOoT = true;}
      while(iWRETzYKzp == iWRETzYKzp){RzxrljCOhy = true;}
      while(QLJUigkpMe == QLJUigkpMe){VjtcWFsExz = true;}
      if(FOVgzBAnLO == true){FOVgzBAnLO = false;}
      if(UInQmcltOP == true){UInQmcltOP = false;}
      if(qTJKjNQEGl == true){qTJKjNQEGl = false;}
      if(fMutVUBjFS == true){fMutVUBjFS = false;}
      if(yjzjVIXshF == true){yjzjVIXshF = false;}
      if(tqawnkFLxl == true){tqawnkFLxl = false;}
      if(jwhYhHMstS == true){jwhYhHMstS = false;}
      if(aCowRHUYoa == true){aCowRHUYoa = false;}
      if(pXWAqolyGk == true){pXWAqolyGk = false;}
      if(OplThCCZBN == true){OplThCCZBN = false;}
      if(udyPdrCdeg == true){udyPdrCdeg = false;}
      if(QfWVuMZghs == true){QfWVuMZghs = false;}
      if(UNmJDkPUOO == true){UNmJDkPUOO = false;}
      if(EuWafLYGVz == true){EuWafLYGVz = false;}
      if(lITYUiTQXV == true){lITYUiTQXV = false;}
      if(cUrIrgpoMs == true){cUrIrgpoMs = false;}
      if(bgPPbUIupi == true){bgPPbUIupi = false;}
      if(mSKhGMtOoT == true){mSKhGMtOoT = false;}
      if(RzxrljCOhy == true){RzxrljCOhy = false;}
      if(VjtcWFsExz == true){VjtcWFsExz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YWSWYAZXWG
{ 
  void PPswhCtxfY()
  { 
      bool ZAxLmoYeaX = false;
      bool IUaGnBVeSW = false;
      bool FQYhKBqUrn = false;
      bool zOMJBLNtsK = false;
      bool JIMIrlpmhc = false;
      bool YHZYZJaOAk = false;
      bool xEmmYsHRFb = false;
      bool nalHNwEQpY = false;
      bool KElOOromjq = false;
      bool jytHMEVYjy = false;
      bool dYhFoyVSKd = false;
      bool EKYbZsRXXf = false;
      bool EUhNqpgdtI = false;
      bool aefqulWfZQ = false;
      bool VVbFmZZRgT = false;
      bool mxBDtIqTNy = false;
      bool RqXCCZdggn = false;
      bool WkyGKhsbaR = false;
      bool QOxaVdccxl = false;
      bool tCSazeyZDN = false;
      string jbqGEZTXds;
      string TgzbfDyQRb;
      string CnNJHdMqXS;
      string FnJhEsicEV;
      string PbdCYHFAak;
      string XXsEcuNgyZ;
      string NczKmeXQWl;
      string TUMuMZKLkz;
      string YLQmuhuEFJ;
      string fCedIlbSOt;
      string indnQCKxrD;
      string kBwyBBMMPF;
      string jTLNGRpimZ;
      string xqxpPjhbVr;
      string WxLCYeFfcG;
      string ZPDJJPcPhz;
      string MbKSFsEFhQ;
      string TkqXilHIob;
      string LKGfAhnmfA;
      string GRsVetlswe;
      if(jbqGEZTXds == indnQCKxrD){ZAxLmoYeaX = true;}
      else if(indnQCKxrD == jbqGEZTXds){dYhFoyVSKd = true;}
      if(TgzbfDyQRb == kBwyBBMMPF){IUaGnBVeSW = true;}
      else if(kBwyBBMMPF == TgzbfDyQRb){EKYbZsRXXf = true;}
      if(CnNJHdMqXS == jTLNGRpimZ){FQYhKBqUrn = true;}
      else if(jTLNGRpimZ == CnNJHdMqXS){EUhNqpgdtI = true;}
      if(FnJhEsicEV == xqxpPjhbVr){zOMJBLNtsK = true;}
      else if(xqxpPjhbVr == FnJhEsicEV){aefqulWfZQ = true;}
      if(PbdCYHFAak == WxLCYeFfcG){JIMIrlpmhc = true;}
      else if(WxLCYeFfcG == PbdCYHFAak){VVbFmZZRgT = true;}
      if(XXsEcuNgyZ == ZPDJJPcPhz){YHZYZJaOAk = true;}
      else if(ZPDJJPcPhz == XXsEcuNgyZ){mxBDtIqTNy = true;}
      if(NczKmeXQWl == MbKSFsEFhQ){xEmmYsHRFb = true;}
      else if(MbKSFsEFhQ == NczKmeXQWl){RqXCCZdggn = true;}
      if(TUMuMZKLkz == TkqXilHIob){nalHNwEQpY = true;}
      if(YLQmuhuEFJ == LKGfAhnmfA){KElOOromjq = true;}
      if(fCedIlbSOt == GRsVetlswe){jytHMEVYjy = true;}
      while(TkqXilHIob == TUMuMZKLkz){WkyGKhsbaR = true;}
      while(LKGfAhnmfA == LKGfAhnmfA){QOxaVdccxl = true;}
      while(GRsVetlswe == GRsVetlswe){tCSazeyZDN = true;}
      if(ZAxLmoYeaX == true){ZAxLmoYeaX = false;}
      if(IUaGnBVeSW == true){IUaGnBVeSW = false;}
      if(FQYhKBqUrn == true){FQYhKBqUrn = false;}
      if(zOMJBLNtsK == true){zOMJBLNtsK = false;}
      if(JIMIrlpmhc == true){JIMIrlpmhc = false;}
      if(YHZYZJaOAk == true){YHZYZJaOAk = false;}
      if(xEmmYsHRFb == true){xEmmYsHRFb = false;}
      if(nalHNwEQpY == true){nalHNwEQpY = false;}
      if(KElOOromjq == true){KElOOromjq = false;}
      if(jytHMEVYjy == true){jytHMEVYjy = false;}
      if(dYhFoyVSKd == true){dYhFoyVSKd = false;}
      if(EKYbZsRXXf == true){EKYbZsRXXf = false;}
      if(EUhNqpgdtI == true){EUhNqpgdtI = false;}
      if(aefqulWfZQ == true){aefqulWfZQ = false;}
      if(VVbFmZZRgT == true){VVbFmZZRgT = false;}
      if(mxBDtIqTNy == true){mxBDtIqTNy = false;}
      if(RqXCCZdggn == true){RqXCCZdggn = false;}
      if(WkyGKhsbaR == true){WkyGKhsbaR = false;}
      if(QOxaVdccxl == true){QOxaVdccxl = false;}
      if(tCSazeyZDN == true){tCSazeyZDN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBEEPOGFAO
{ 
  void HXOlHikGsi()
  { 
      bool iucUpToVsG = false;
      bool HRPNpiCiNY = false;
      bool wiIGfswHmi = false;
      bool rVCPBsZfuD = false;
      bool RSDcCqUOPt = false;
      bool WZjAEzlWnw = false;
      bool WhhJOlPAMw = false;
      bool JWmKGdffDo = false;
      bool YgrrLRlBKB = false;
      bool GDrzfjjsOQ = false;
      bool bTCSkAmYsa = false;
      bool TGTyXpooxw = false;
      bool ANpKpGendW = false;
      bool slQlNEdYHL = false;
      bool eMHigzjsap = false;
      bool tuwRQNdrce = false;
      bool UyuWghpgkS = false;
      bool LQhlRmGGcp = false;
      bool WlMncyoyUz = false;
      bool ZlwcpfRkBz = false;
      string KgSBEuyuJz;
      string lpZQKtIlml;
      string CzLCihuUEb;
      string TBBwLPpOYQ;
      string YqCVWSEqsL;
      string baxPBKUQSV;
      string AcpgfjocFt;
      string DsMWMKxpeP;
      string dDaszrEluA;
      string tZwCQuAUpm;
      string dalzIiNaCp;
      string NekCrwCxhm;
      string eCgEAdwKFQ;
      string KbzrlCRbjQ;
      string ddiFmOotJT;
      string sCmCHasgye;
      string lDUkfkfsQo;
      string dZNRJBTbRk;
      string oCAkXHnwjK;
      string IkcFdZJxZB;
      if(KgSBEuyuJz == dalzIiNaCp){iucUpToVsG = true;}
      else if(dalzIiNaCp == KgSBEuyuJz){bTCSkAmYsa = true;}
      if(lpZQKtIlml == NekCrwCxhm){HRPNpiCiNY = true;}
      else if(NekCrwCxhm == lpZQKtIlml){TGTyXpooxw = true;}
      if(CzLCihuUEb == eCgEAdwKFQ){wiIGfswHmi = true;}
      else if(eCgEAdwKFQ == CzLCihuUEb){ANpKpGendW = true;}
      if(TBBwLPpOYQ == KbzrlCRbjQ){rVCPBsZfuD = true;}
      else if(KbzrlCRbjQ == TBBwLPpOYQ){slQlNEdYHL = true;}
      if(YqCVWSEqsL == ddiFmOotJT){RSDcCqUOPt = true;}
      else if(ddiFmOotJT == YqCVWSEqsL){eMHigzjsap = true;}
      if(baxPBKUQSV == sCmCHasgye){WZjAEzlWnw = true;}
      else if(sCmCHasgye == baxPBKUQSV){tuwRQNdrce = true;}
      if(AcpgfjocFt == lDUkfkfsQo){WhhJOlPAMw = true;}
      else if(lDUkfkfsQo == AcpgfjocFt){UyuWghpgkS = true;}
      if(DsMWMKxpeP == dZNRJBTbRk){JWmKGdffDo = true;}
      if(dDaszrEluA == oCAkXHnwjK){YgrrLRlBKB = true;}
      if(tZwCQuAUpm == IkcFdZJxZB){GDrzfjjsOQ = true;}
      while(dZNRJBTbRk == DsMWMKxpeP){LQhlRmGGcp = true;}
      while(oCAkXHnwjK == oCAkXHnwjK){WlMncyoyUz = true;}
      while(IkcFdZJxZB == IkcFdZJxZB){ZlwcpfRkBz = true;}
      if(iucUpToVsG == true){iucUpToVsG = false;}
      if(HRPNpiCiNY == true){HRPNpiCiNY = false;}
      if(wiIGfswHmi == true){wiIGfswHmi = false;}
      if(rVCPBsZfuD == true){rVCPBsZfuD = false;}
      if(RSDcCqUOPt == true){RSDcCqUOPt = false;}
      if(WZjAEzlWnw == true){WZjAEzlWnw = false;}
      if(WhhJOlPAMw == true){WhhJOlPAMw = false;}
      if(JWmKGdffDo == true){JWmKGdffDo = false;}
      if(YgrrLRlBKB == true){YgrrLRlBKB = false;}
      if(GDrzfjjsOQ == true){GDrzfjjsOQ = false;}
      if(bTCSkAmYsa == true){bTCSkAmYsa = false;}
      if(TGTyXpooxw == true){TGTyXpooxw = false;}
      if(ANpKpGendW == true){ANpKpGendW = false;}
      if(slQlNEdYHL == true){slQlNEdYHL = false;}
      if(eMHigzjsap == true){eMHigzjsap = false;}
      if(tuwRQNdrce == true){tuwRQNdrce = false;}
      if(UyuWghpgkS == true){UyuWghpgkS = false;}
      if(LQhlRmGGcp == true){LQhlRmGGcp = false;}
      if(WlMncyoyUz == true){WlMncyoyUz = false;}
      if(ZlwcpfRkBz == true){ZlwcpfRkBz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZAEPQSTNHU
{ 
  void CcStQTsMoJ()
  { 
      bool mySePDzJce = false;
      bool rnRBczLjIU = false;
      bool FyApzCsWMw = false;
      bool PYFmVOsXNX = false;
      bool QTOxnZuSfI = false;
      bool SNNXtoxbfM = false;
      bool JcwgPShdeN = false;
      bool FnWjDkiDCY = false;
      bool HZpEdBLgrg = false;
      bool QQqANnWhgU = false;
      bool rQnRCdpcTI = false;
      bool FtYHFjmrCN = false;
      bool HBkyxoxVWP = false;
      bool OBVggplXBz = false;
      bool KhMjaWqjtd = false;
      bool BdeSNqeoUN = false;
      bool gUGEtEXqaP = false;
      bool xOqDDYnBWZ = false;
      bool xNbsOjVCTp = false;
      bool KwCnRpbIoW = false;
      string boycCeJexq;
      string fzpfmXMmDp;
      string aMaMeWIjVc;
      string QYQAmgKdki;
      string kTmBZXGRFq;
      string uMphnONkye;
      string WYJUaHiprG;
      string NhBUFGZYmH;
      string QpedgEhhLX;
      string SYfGLLKRaR;
      string nQYydNKVcg;
      string onypNgtenV;
      string YAdUnnBuIs;
      string wHxUTAQfzS;
      string tLFehdapre;
      string RedFrmlEKp;
      string LONikhqcWM;
      string POfUbNuymJ;
      string MLCcaQcrbf;
      string NMUJHeyVsz;
      if(boycCeJexq == nQYydNKVcg){mySePDzJce = true;}
      else if(nQYydNKVcg == boycCeJexq){rQnRCdpcTI = true;}
      if(fzpfmXMmDp == onypNgtenV){rnRBczLjIU = true;}
      else if(onypNgtenV == fzpfmXMmDp){FtYHFjmrCN = true;}
      if(aMaMeWIjVc == YAdUnnBuIs){FyApzCsWMw = true;}
      else if(YAdUnnBuIs == aMaMeWIjVc){HBkyxoxVWP = true;}
      if(QYQAmgKdki == wHxUTAQfzS){PYFmVOsXNX = true;}
      else if(wHxUTAQfzS == QYQAmgKdki){OBVggplXBz = true;}
      if(kTmBZXGRFq == tLFehdapre){QTOxnZuSfI = true;}
      else if(tLFehdapre == kTmBZXGRFq){KhMjaWqjtd = true;}
      if(uMphnONkye == RedFrmlEKp){SNNXtoxbfM = true;}
      else if(RedFrmlEKp == uMphnONkye){BdeSNqeoUN = true;}
      if(WYJUaHiprG == LONikhqcWM){JcwgPShdeN = true;}
      else if(LONikhqcWM == WYJUaHiprG){gUGEtEXqaP = true;}
      if(NhBUFGZYmH == POfUbNuymJ){FnWjDkiDCY = true;}
      if(QpedgEhhLX == MLCcaQcrbf){HZpEdBLgrg = true;}
      if(SYfGLLKRaR == NMUJHeyVsz){QQqANnWhgU = true;}
      while(POfUbNuymJ == NhBUFGZYmH){xOqDDYnBWZ = true;}
      while(MLCcaQcrbf == MLCcaQcrbf){xNbsOjVCTp = true;}
      while(NMUJHeyVsz == NMUJHeyVsz){KwCnRpbIoW = true;}
      if(mySePDzJce == true){mySePDzJce = false;}
      if(rnRBczLjIU == true){rnRBczLjIU = false;}
      if(FyApzCsWMw == true){FyApzCsWMw = false;}
      if(PYFmVOsXNX == true){PYFmVOsXNX = false;}
      if(QTOxnZuSfI == true){QTOxnZuSfI = false;}
      if(SNNXtoxbfM == true){SNNXtoxbfM = false;}
      if(JcwgPShdeN == true){JcwgPShdeN = false;}
      if(FnWjDkiDCY == true){FnWjDkiDCY = false;}
      if(HZpEdBLgrg == true){HZpEdBLgrg = false;}
      if(QQqANnWhgU == true){QQqANnWhgU = false;}
      if(rQnRCdpcTI == true){rQnRCdpcTI = false;}
      if(FtYHFjmrCN == true){FtYHFjmrCN = false;}
      if(HBkyxoxVWP == true){HBkyxoxVWP = false;}
      if(OBVggplXBz == true){OBVggplXBz = false;}
      if(KhMjaWqjtd == true){KhMjaWqjtd = false;}
      if(BdeSNqeoUN == true){BdeSNqeoUN = false;}
      if(gUGEtEXqaP == true){gUGEtEXqaP = false;}
      if(xOqDDYnBWZ == true){xOqDDYnBWZ = false;}
      if(xNbsOjVCTp == true){xNbsOjVCTp = false;}
      if(KwCnRpbIoW == true){KwCnRpbIoW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJMKVCZWOW
{ 
  void oiWagUuRmN()
  { 
      bool pbXFwwjLdI = false;
      bool iZQAOnUIDx = false;
      bool dNugymEkLC = false;
      bool SYkACBamFE = false;
      bool sNunJTWzco = false;
      bool DLOEBbgqHI = false;
      bool qzAapKoQxM = false;
      bool NgDyDPSGWd = false;
      bool PFIVzGKfyZ = false;
      bool UifwMtMTyz = false;
      bool dGBPaVIPBk = false;
      bool JZTdslpdbj = false;
      bool AJRXreBHlI = false;
      bool CyIXzJDruc = false;
      bool ytdMQuOCDZ = false;
      bool DhqOyUndXw = false;
      bool TAcrhKQwdi = false;
      bool iyiykFeEHx = false;
      bool PzELFTGtZe = false;
      bool VZUzIxRleF = false;
      string MmxjQouCmy;
      string fWwDZDeapC;
      string bzYDjeioRc;
      string pzghaIzpkl;
      string DKQaudrnfs;
      string ZwlEkMOszl;
      string FGkJHfpOcQ;
      string DnpEyRhxIG;
      string luIYDsNcxN;
      string tFqyfxZHSO;
      string mdLPokGhFT;
      string eQkrAJxLGN;
      string SNQOVxxrXB;
      string radsSHjsiR;
      string meWdicTyyW;
      string ANAEwZNwsr;
      string nOKEbDmrZr;
      string ZDcoampmfs;
      string czsBAdZYxs;
      string tmzqdXURCe;
      if(MmxjQouCmy == mdLPokGhFT){pbXFwwjLdI = true;}
      else if(mdLPokGhFT == MmxjQouCmy){dGBPaVIPBk = true;}
      if(fWwDZDeapC == eQkrAJxLGN){iZQAOnUIDx = true;}
      else if(eQkrAJxLGN == fWwDZDeapC){JZTdslpdbj = true;}
      if(bzYDjeioRc == SNQOVxxrXB){dNugymEkLC = true;}
      else if(SNQOVxxrXB == bzYDjeioRc){AJRXreBHlI = true;}
      if(pzghaIzpkl == radsSHjsiR){SYkACBamFE = true;}
      else if(radsSHjsiR == pzghaIzpkl){CyIXzJDruc = true;}
      if(DKQaudrnfs == meWdicTyyW){sNunJTWzco = true;}
      else if(meWdicTyyW == DKQaudrnfs){ytdMQuOCDZ = true;}
      if(ZwlEkMOszl == ANAEwZNwsr){DLOEBbgqHI = true;}
      else if(ANAEwZNwsr == ZwlEkMOszl){DhqOyUndXw = true;}
      if(FGkJHfpOcQ == nOKEbDmrZr){qzAapKoQxM = true;}
      else if(nOKEbDmrZr == FGkJHfpOcQ){TAcrhKQwdi = true;}
      if(DnpEyRhxIG == ZDcoampmfs){NgDyDPSGWd = true;}
      if(luIYDsNcxN == czsBAdZYxs){PFIVzGKfyZ = true;}
      if(tFqyfxZHSO == tmzqdXURCe){UifwMtMTyz = true;}
      while(ZDcoampmfs == DnpEyRhxIG){iyiykFeEHx = true;}
      while(czsBAdZYxs == czsBAdZYxs){PzELFTGtZe = true;}
      while(tmzqdXURCe == tmzqdXURCe){VZUzIxRleF = true;}
      if(pbXFwwjLdI == true){pbXFwwjLdI = false;}
      if(iZQAOnUIDx == true){iZQAOnUIDx = false;}
      if(dNugymEkLC == true){dNugymEkLC = false;}
      if(SYkACBamFE == true){SYkACBamFE = false;}
      if(sNunJTWzco == true){sNunJTWzco = false;}
      if(DLOEBbgqHI == true){DLOEBbgqHI = false;}
      if(qzAapKoQxM == true){qzAapKoQxM = false;}
      if(NgDyDPSGWd == true){NgDyDPSGWd = false;}
      if(PFIVzGKfyZ == true){PFIVzGKfyZ = false;}
      if(UifwMtMTyz == true){UifwMtMTyz = false;}
      if(dGBPaVIPBk == true){dGBPaVIPBk = false;}
      if(JZTdslpdbj == true){JZTdslpdbj = false;}
      if(AJRXreBHlI == true){AJRXreBHlI = false;}
      if(CyIXzJDruc == true){CyIXzJDruc = false;}
      if(ytdMQuOCDZ == true){ytdMQuOCDZ = false;}
      if(DhqOyUndXw == true){DhqOyUndXw = false;}
      if(TAcrhKQwdi == true){TAcrhKQwdi = false;}
      if(iyiykFeEHx == true){iyiykFeEHx = false;}
      if(PzELFTGtZe == true){PzELFTGtZe = false;}
      if(VZUzIxRleF == true){VZUzIxRleF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWLONIZOKA
{ 
  void GIicIULwdb()
  { 
      bool DXjjLPhuHa = false;
      bool AnaIELLQiH = false;
      bool JRyDiSeGOY = false;
      bool dFpKHMxYIs = false;
      bool nGkfEmsaBe = false;
      bool SDTTGkZfAr = false;
      bool jbfhwtyPBr = false;
      bool NmHoSCgSzw = false;
      bool ZEFiGalVEW = false;
      bool mRXQJMZDiJ = false;
      bool ocZIRewdAD = false;
      bool EGgERfWwaV = false;
      bool IbKdFwOqfG = false;
      bool cdioHxdwRb = false;
      bool dHVBRfkTyd = false;
      bool pdbMBMRuCU = false;
      bool QEytaaXqwU = false;
      bool BZdzrBGJMZ = false;
      bool LurCPzBWmt = false;
      bool ehsxKYJaZq = false;
      string zoAMXyDtNU;
      string wZtpIyznMA;
      string fnIBRRRnlP;
      string rjuSzHRKtm;
      string NKqqoqFsrk;
      string JScSQKfzuF;
      string fOIycLeapA;
      string gosYmUwRLZ;
      string MXwAFYHbCn;
      string bROoGyCsOd;
      string MeDrEUZDfw;
      string NNmVsHSHrD;
      string DDXBYOaESn;
      string RDDhNhUDuk;
      string zEuGaNdruy;
      string etBKZIGBTo;
      string tUjreKKFIL;
      string mPMGDyIRaK;
      string jhITIWBrHE;
      string bTjFqdTCbP;
      if(zoAMXyDtNU == MeDrEUZDfw){DXjjLPhuHa = true;}
      else if(MeDrEUZDfw == zoAMXyDtNU){ocZIRewdAD = true;}
      if(wZtpIyznMA == NNmVsHSHrD){AnaIELLQiH = true;}
      else if(NNmVsHSHrD == wZtpIyznMA){EGgERfWwaV = true;}
      if(fnIBRRRnlP == DDXBYOaESn){JRyDiSeGOY = true;}
      else if(DDXBYOaESn == fnIBRRRnlP){IbKdFwOqfG = true;}
      if(rjuSzHRKtm == RDDhNhUDuk){dFpKHMxYIs = true;}
      else if(RDDhNhUDuk == rjuSzHRKtm){cdioHxdwRb = true;}
      if(NKqqoqFsrk == zEuGaNdruy){nGkfEmsaBe = true;}
      else if(zEuGaNdruy == NKqqoqFsrk){dHVBRfkTyd = true;}
      if(JScSQKfzuF == etBKZIGBTo){SDTTGkZfAr = true;}
      else if(etBKZIGBTo == JScSQKfzuF){pdbMBMRuCU = true;}
      if(fOIycLeapA == tUjreKKFIL){jbfhwtyPBr = true;}
      else if(tUjreKKFIL == fOIycLeapA){QEytaaXqwU = true;}
      if(gosYmUwRLZ == mPMGDyIRaK){NmHoSCgSzw = true;}
      if(MXwAFYHbCn == jhITIWBrHE){ZEFiGalVEW = true;}
      if(bROoGyCsOd == bTjFqdTCbP){mRXQJMZDiJ = true;}
      while(mPMGDyIRaK == gosYmUwRLZ){BZdzrBGJMZ = true;}
      while(jhITIWBrHE == jhITIWBrHE){LurCPzBWmt = true;}
      while(bTjFqdTCbP == bTjFqdTCbP){ehsxKYJaZq = true;}
      if(DXjjLPhuHa == true){DXjjLPhuHa = false;}
      if(AnaIELLQiH == true){AnaIELLQiH = false;}
      if(JRyDiSeGOY == true){JRyDiSeGOY = false;}
      if(dFpKHMxYIs == true){dFpKHMxYIs = false;}
      if(nGkfEmsaBe == true){nGkfEmsaBe = false;}
      if(SDTTGkZfAr == true){SDTTGkZfAr = false;}
      if(jbfhwtyPBr == true){jbfhwtyPBr = false;}
      if(NmHoSCgSzw == true){NmHoSCgSzw = false;}
      if(ZEFiGalVEW == true){ZEFiGalVEW = false;}
      if(mRXQJMZDiJ == true){mRXQJMZDiJ = false;}
      if(ocZIRewdAD == true){ocZIRewdAD = false;}
      if(EGgERfWwaV == true){EGgERfWwaV = false;}
      if(IbKdFwOqfG == true){IbKdFwOqfG = false;}
      if(cdioHxdwRb == true){cdioHxdwRb = false;}
      if(dHVBRfkTyd == true){dHVBRfkTyd = false;}
      if(pdbMBMRuCU == true){pdbMBMRuCU = false;}
      if(QEytaaXqwU == true){QEytaaXqwU = false;}
      if(BZdzrBGJMZ == true){BZdzrBGJMZ = false;}
      if(LurCPzBWmt == true){LurCPzBWmt = false;}
      if(ehsxKYJaZq == true){ehsxKYJaZq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZEIGIXQPZZ
{ 
  void DZNcwaJSJV()
  { 
      bool DoVtMWmxPd = false;
      bool KEHNcsQCMO = false;
      bool RhLqoOTHEd = false;
      bool IKZSDMWRVr = false;
      bool FapHlulWBM = false;
      bool wAJjxUdeFx = false;
      bool CfslUAdoKQ = false;
      bool WyfTIprDEs = false;
      bool bxFqgHAoVh = false;
      bool hqMYpZhEll = false;
      bool RxMkpxUoaG = false;
      bool caaLUEZBEN = false;
      bool znTbhelHdi = false;
      bool ImRSbekUBi = false;
      bool lKNPFHQBDk = false;
      bool AgAYlcdkDK = false;
      bool LNLryoIHip = false;
      bool TEzUanZEWZ = false;
      bool NkDribmsgy = false;
      bool AARqXYzVQP = false;
      string FJeDKNeexo;
      string YHJHAxDBtE;
      string rpzoVHGrAK;
      string mrNxqEzQEY;
      string ZCysXOUrQT;
      string bVMxQOJogD;
      string HldlBgtMPu;
      string ylwVdprGRH;
      string lNagiReQfb;
      string uJjAQmXLrq;
      string TIcUUoZpSZ;
      string WDWZRtLxDj;
      string BdfmzoCuFq;
      string SfOamcjGLs;
      string qoxGFrlJiV;
      string bZHIppcpUf;
      string mdkbHpnwmn;
      string JElKrLfYhH;
      string CsMiPrYGkw;
      string ztkeGNDVzO;
      if(FJeDKNeexo == TIcUUoZpSZ){DoVtMWmxPd = true;}
      else if(TIcUUoZpSZ == FJeDKNeexo){RxMkpxUoaG = true;}
      if(YHJHAxDBtE == WDWZRtLxDj){KEHNcsQCMO = true;}
      else if(WDWZRtLxDj == YHJHAxDBtE){caaLUEZBEN = true;}
      if(rpzoVHGrAK == BdfmzoCuFq){RhLqoOTHEd = true;}
      else if(BdfmzoCuFq == rpzoVHGrAK){znTbhelHdi = true;}
      if(mrNxqEzQEY == SfOamcjGLs){IKZSDMWRVr = true;}
      else if(SfOamcjGLs == mrNxqEzQEY){ImRSbekUBi = true;}
      if(ZCysXOUrQT == qoxGFrlJiV){FapHlulWBM = true;}
      else if(qoxGFrlJiV == ZCysXOUrQT){lKNPFHQBDk = true;}
      if(bVMxQOJogD == bZHIppcpUf){wAJjxUdeFx = true;}
      else if(bZHIppcpUf == bVMxQOJogD){AgAYlcdkDK = true;}
      if(HldlBgtMPu == mdkbHpnwmn){CfslUAdoKQ = true;}
      else if(mdkbHpnwmn == HldlBgtMPu){LNLryoIHip = true;}
      if(ylwVdprGRH == JElKrLfYhH){WyfTIprDEs = true;}
      if(lNagiReQfb == CsMiPrYGkw){bxFqgHAoVh = true;}
      if(uJjAQmXLrq == ztkeGNDVzO){hqMYpZhEll = true;}
      while(JElKrLfYhH == ylwVdprGRH){TEzUanZEWZ = true;}
      while(CsMiPrYGkw == CsMiPrYGkw){NkDribmsgy = true;}
      while(ztkeGNDVzO == ztkeGNDVzO){AARqXYzVQP = true;}
      if(DoVtMWmxPd == true){DoVtMWmxPd = false;}
      if(KEHNcsQCMO == true){KEHNcsQCMO = false;}
      if(RhLqoOTHEd == true){RhLqoOTHEd = false;}
      if(IKZSDMWRVr == true){IKZSDMWRVr = false;}
      if(FapHlulWBM == true){FapHlulWBM = false;}
      if(wAJjxUdeFx == true){wAJjxUdeFx = false;}
      if(CfslUAdoKQ == true){CfslUAdoKQ = false;}
      if(WyfTIprDEs == true){WyfTIprDEs = false;}
      if(bxFqgHAoVh == true){bxFqgHAoVh = false;}
      if(hqMYpZhEll == true){hqMYpZhEll = false;}
      if(RxMkpxUoaG == true){RxMkpxUoaG = false;}
      if(caaLUEZBEN == true){caaLUEZBEN = false;}
      if(znTbhelHdi == true){znTbhelHdi = false;}
      if(ImRSbekUBi == true){ImRSbekUBi = false;}
      if(lKNPFHQBDk == true){lKNPFHQBDk = false;}
      if(AgAYlcdkDK == true){AgAYlcdkDK = false;}
      if(LNLryoIHip == true){LNLryoIHip = false;}
      if(TEzUanZEWZ == true){TEzUanZEWZ = false;}
      if(NkDribmsgy == true){NkDribmsgy = false;}
      if(AARqXYzVQP == true){AARqXYzVQP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBNQVDMIXP
{ 
  void rZFRFdShKB()
  { 
      bool LhIIHBfmsh = false;
      bool THAJVwAwfg = false;
      bool hnEoBDelsc = false;
      bool fpcLhOCwBJ = false;
      bool lgExxwprEL = false;
      bool UwTYIXdSGD = false;
      bool VstPBcdoaH = false;
      bool sDtWtBiHqF = false;
      bool NmhgIjVEDK = false;
      bool jioymslouT = false;
      bool RAQxSQCweG = false;
      bool nWbBoiKNHR = false;
      bool HZkQWJNuiA = false;
      bool OtLWmMVjOq = false;
      bool hYZwVNHnIE = false;
      bool hYgcMrOAaI = false;
      bool DGNdrtKENb = false;
      bool MazQihzotI = false;
      bool CYmeSpMhJu = false;
      bool yVJGmbLwEa = false;
      string FPRbcfGsPf;
      string WqkhQcYUde;
      string pfmfYEwPLC;
      string IjfhfAZAma;
      string NfRkPEfCMk;
      string FIUCTZblDX;
      string iqgNXlLCCP;
      string CXhDQJNCPU;
      string YtCawAPcOF;
      string XnxOqWyENd;
      string rdzwhgZRkJ;
      string LZVhzonGQX;
      string WhmwrOZTLt;
      string KInlbttGsP;
      string ZxqEsxROOC;
      string irnpGKpDES;
      string HFFqzCliGF;
      string tgMBxYpiCt;
      string xKFJKRUxeR;
      string DqCZIUrAFp;
      if(FPRbcfGsPf == rdzwhgZRkJ){LhIIHBfmsh = true;}
      else if(rdzwhgZRkJ == FPRbcfGsPf){RAQxSQCweG = true;}
      if(WqkhQcYUde == LZVhzonGQX){THAJVwAwfg = true;}
      else if(LZVhzonGQX == WqkhQcYUde){nWbBoiKNHR = true;}
      if(pfmfYEwPLC == WhmwrOZTLt){hnEoBDelsc = true;}
      else if(WhmwrOZTLt == pfmfYEwPLC){HZkQWJNuiA = true;}
      if(IjfhfAZAma == KInlbttGsP){fpcLhOCwBJ = true;}
      else if(KInlbttGsP == IjfhfAZAma){OtLWmMVjOq = true;}
      if(NfRkPEfCMk == ZxqEsxROOC){lgExxwprEL = true;}
      else if(ZxqEsxROOC == NfRkPEfCMk){hYZwVNHnIE = true;}
      if(FIUCTZblDX == irnpGKpDES){UwTYIXdSGD = true;}
      else if(irnpGKpDES == FIUCTZblDX){hYgcMrOAaI = true;}
      if(iqgNXlLCCP == HFFqzCliGF){VstPBcdoaH = true;}
      else if(HFFqzCliGF == iqgNXlLCCP){DGNdrtKENb = true;}
      if(CXhDQJNCPU == tgMBxYpiCt){sDtWtBiHqF = true;}
      if(YtCawAPcOF == xKFJKRUxeR){NmhgIjVEDK = true;}
      if(XnxOqWyENd == DqCZIUrAFp){jioymslouT = true;}
      while(tgMBxYpiCt == CXhDQJNCPU){MazQihzotI = true;}
      while(xKFJKRUxeR == xKFJKRUxeR){CYmeSpMhJu = true;}
      while(DqCZIUrAFp == DqCZIUrAFp){yVJGmbLwEa = true;}
      if(LhIIHBfmsh == true){LhIIHBfmsh = false;}
      if(THAJVwAwfg == true){THAJVwAwfg = false;}
      if(hnEoBDelsc == true){hnEoBDelsc = false;}
      if(fpcLhOCwBJ == true){fpcLhOCwBJ = false;}
      if(lgExxwprEL == true){lgExxwprEL = false;}
      if(UwTYIXdSGD == true){UwTYIXdSGD = false;}
      if(VstPBcdoaH == true){VstPBcdoaH = false;}
      if(sDtWtBiHqF == true){sDtWtBiHqF = false;}
      if(NmhgIjVEDK == true){NmhgIjVEDK = false;}
      if(jioymslouT == true){jioymslouT = false;}
      if(RAQxSQCweG == true){RAQxSQCweG = false;}
      if(nWbBoiKNHR == true){nWbBoiKNHR = false;}
      if(HZkQWJNuiA == true){HZkQWJNuiA = false;}
      if(OtLWmMVjOq == true){OtLWmMVjOq = false;}
      if(hYZwVNHnIE == true){hYZwVNHnIE = false;}
      if(hYgcMrOAaI == true){hYgcMrOAaI = false;}
      if(DGNdrtKENb == true){DGNdrtKENb = false;}
      if(MazQihzotI == true){MazQihzotI = false;}
      if(CYmeSpMhJu == true){CYmeSpMhJu = false;}
      if(yVJGmbLwEa == true){yVJGmbLwEa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAUCIYRPUP
{ 
  void KoMQAQwfsV()
  { 
      bool Wyazadiebt = false;
      bool YHOUidewKm = false;
      bool anoLVUpfQr = false;
      bool TGiTWzlUlF = false;
      bool PCoDXwEXVs = false;
      bool XbQWPiIPcG = false;
      bool mDNjZRYuxj = false;
      bool rKKFXYyknZ = false;
      bool PRJXTroLDn = false;
      bool pVqfRLnFdF = false;
      bool XJalANRLyp = false;
      bool jXbDpVsoQh = false;
      bool bMqIsWSemL = false;
      bool jsHhCFpXXF = false;
      bool ZdMMDSsnou = false;
      bool RznwcKSRrc = false;
      bool ulXmGqPsAk = false;
      bool eVQKHyzdFa = false;
      bool cdpqskELFq = false;
      bool mXetKnFZGM = false;
      string hebGnfPhog;
      string UKwEWaJWap;
      string RBZFiRYcLi;
      string lbyJnbgSZD;
      string qKdPHVayhJ;
      string epInKfEWXV;
      string HlVGtsLmQu;
      string tqxXzGXKyM;
      string qauBDwSJzH;
      string WKtDwEnWVN;
      string JmhmPnskoD;
      string ItXLdgqUDy;
      string aCmIXjwsbu;
      string RAokDDrIkO;
      string ChUuycliZO;
      string MTTWmGzYPf;
      string qzJskHFmHZ;
      string nijnurhrKt;
      string xNTMiygRxw;
      string DTsEWDYaJp;
      if(hebGnfPhog == JmhmPnskoD){Wyazadiebt = true;}
      else if(JmhmPnskoD == hebGnfPhog){XJalANRLyp = true;}
      if(UKwEWaJWap == ItXLdgqUDy){YHOUidewKm = true;}
      else if(ItXLdgqUDy == UKwEWaJWap){jXbDpVsoQh = true;}
      if(RBZFiRYcLi == aCmIXjwsbu){anoLVUpfQr = true;}
      else if(aCmIXjwsbu == RBZFiRYcLi){bMqIsWSemL = true;}
      if(lbyJnbgSZD == RAokDDrIkO){TGiTWzlUlF = true;}
      else if(RAokDDrIkO == lbyJnbgSZD){jsHhCFpXXF = true;}
      if(qKdPHVayhJ == ChUuycliZO){PCoDXwEXVs = true;}
      else if(ChUuycliZO == qKdPHVayhJ){ZdMMDSsnou = true;}
      if(epInKfEWXV == MTTWmGzYPf){XbQWPiIPcG = true;}
      else if(MTTWmGzYPf == epInKfEWXV){RznwcKSRrc = true;}
      if(HlVGtsLmQu == qzJskHFmHZ){mDNjZRYuxj = true;}
      else if(qzJskHFmHZ == HlVGtsLmQu){ulXmGqPsAk = true;}
      if(tqxXzGXKyM == nijnurhrKt){rKKFXYyknZ = true;}
      if(qauBDwSJzH == xNTMiygRxw){PRJXTroLDn = true;}
      if(WKtDwEnWVN == DTsEWDYaJp){pVqfRLnFdF = true;}
      while(nijnurhrKt == tqxXzGXKyM){eVQKHyzdFa = true;}
      while(xNTMiygRxw == xNTMiygRxw){cdpqskELFq = true;}
      while(DTsEWDYaJp == DTsEWDYaJp){mXetKnFZGM = true;}
      if(Wyazadiebt == true){Wyazadiebt = false;}
      if(YHOUidewKm == true){YHOUidewKm = false;}
      if(anoLVUpfQr == true){anoLVUpfQr = false;}
      if(TGiTWzlUlF == true){TGiTWzlUlF = false;}
      if(PCoDXwEXVs == true){PCoDXwEXVs = false;}
      if(XbQWPiIPcG == true){XbQWPiIPcG = false;}
      if(mDNjZRYuxj == true){mDNjZRYuxj = false;}
      if(rKKFXYyknZ == true){rKKFXYyknZ = false;}
      if(PRJXTroLDn == true){PRJXTroLDn = false;}
      if(pVqfRLnFdF == true){pVqfRLnFdF = false;}
      if(XJalANRLyp == true){XJalANRLyp = false;}
      if(jXbDpVsoQh == true){jXbDpVsoQh = false;}
      if(bMqIsWSemL == true){bMqIsWSemL = false;}
      if(jsHhCFpXXF == true){jsHhCFpXXF = false;}
      if(ZdMMDSsnou == true){ZdMMDSsnou = false;}
      if(RznwcKSRrc == true){RznwcKSRrc = false;}
      if(ulXmGqPsAk == true){ulXmGqPsAk = false;}
      if(eVQKHyzdFa == true){eVQKHyzdFa = false;}
      if(cdpqskELFq == true){cdpqskELFq = false;}
      if(mXetKnFZGM == true){mXetKnFZGM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSQTIBJVTC
{ 
  void wwrDBLhikB()
  { 
      bool etpZoIsTqQ = false;
      bool IqtnVLGgCO = false;
      bool XZRWMsfwTz = false;
      bool tbmaqnyiFB = false;
      bool GlPXNmtWuJ = false;
      bool EilanFbTNw = false;
      bool cwzrVgDSxg = false;
      bool MWbAHkJtIY = false;
      bool yIAJtLpMlk = false;
      bool MeVJXJlXCg = false;
      bool jaZOxhGkSD = false;
      bool uhKoxUwpxK = false;
      bool ppgLUhBSbx = false;
      bool ykqbnXhkMM = false;
      bool EFsipdTgMD = false;
      bool NwarpstNtO = false;
      bool fnIUEJqiAY = false;
      bool lKcjFkwxVp = false;
      bool NUGYjCKzkt = false;
      bool dTqxfQwYef = false;
      string hiksImjHes;
      string HKDQnFEhAW;
      string iIqQQPCDMX;
      string pSVsGytDAJ;
      string wlarTeMVkA;
      string aXhySYrTbs;
      string jguHDnnJKp;
      string KAhpaxhzwl;
      string CgRLwRkXag;
      string GZaHYPpTne;
      string pDKuoZprXV;
      string qrXppDOjKl;
      string DQicjkZaQK;
      string GOKQwzVWVV;
      string arAEoNBjQV;
      string AGICbYUhKE;
      string APbMOchHtq;
      string gqNoKLPdmW;
      string ioJtKzFHoW;
      string enLRUKQnpM;
      if(hiksImjHes == pDKuoZprXV){etpZoIsTqQ = true;}
      else if(pDKuoZprXV == hiksImjHes){jaZOxhGkSD = true;}
      if(HKDQnFEhAW == qrXppDOjKl){IqtnVLGgCO = true;}
      else if(qrXppDOjKl == HKDQnFEhAW){uhKoxUwpxK = true;}
      if(iIqQQPCDMX == DQicjkZaQK){XZRWMsfwTz = true;}
      else if(DQicjkZaQK == iIqQQPCDMX){ppgLUhBSbx = true;}
      if(pSVsGytDAJ == GOKQwzVWVV){tbmaqnyiFB = true;}
      else if(GOKQwzVWVV == pSVsGytDAJ){ykqbnXhkMM = true;}
      if(wlarTeMVkA == arAEoNBjQV){GlPXNmtWuJ = true;}
      else if(arAEoNBjQV == wlarTeMVkA){EFsipdTgMD = true;}
      if(aXhySYrTbs == AGICbYUhKE){EilanFbTNw = true;}
      else if(AGICbYUhKE == aXhySYrTbs){NwarpstNtO = true;}
      if(jguHDnnJKp == APbMOchHtq){cwzrVgDSxg = true;}
      else if(APbMOchHtq == jguHDnnJKp){fnIUEJqiAY = true;}
      if(KAhpaxhzwl == gqNoKLPdmW){MWbAHkJtIY = true;}
      if(CgRLwRkXag == ioJtKzFHoW){yIAJtLpMlk = true;}
      if(GZaHYPpTne == enLRUKQnpM){MeVJXJlXCg = true;}
      while(gqNoKLPdmW == KAhpaxhzwl){lKcjFkwxVp = true;}
      while(ioJtKzFHoW == ioJtKzFHoW){NUGYjCKzkt = true;}
      while(enLRUKQnpM == enLRUKQnpM){dTqxfQwYef = true;}
      if(etpZoIsTqQ == true){etpZoIsTqQ = false;}
      if(IqtnVLGgCO == true){IqtnVLGgCO = false;}
      if(XZRWMsfwTz == true){XZRWMsfwTz = false;}
      if(tbmaqnyiFB == true){tbmaqnyiFB = false;}
      if(GlPXNmtWuJ == true){GlPXNmtWuJ = false;}
      if(EilanFbTNw == true){EilanFbTNw = false;}
      if(cwzrVgDSxg == true){cwzrVgDSxg = false;}
      if(MWbAHkJtIY == true){MWbAHkJtIY = false;}
      if(yIAJtLpMlk == true){yIAJtLpMlk = false;}
      if(MeVJXJlXCg == true){MeVJXJlXCg = false;}
      if(jaZOxhGkSD == true){jaZOxhGkSD = false;}
      if(uhKoxUwpxK == true){uhKoxUwpxK = false;}
      if(ppgLUhBSbx == true){ppgLUhBSbx = false;}
      if(ykqbnXhkMM == true){ykqbnXhkMM = false;}
      if(EFsipdTgMD == true){EFsipdTgMD = false;}
      if(NwarpstNtO == true){NwarpstNtO = false;}
      if(fnIUEJqiAY == true){fnIUEJqiAY = false;}
      if(lKcjFkwxVp == true){lKcjFkwxVp = false;}
      if(NUGYjCKzkt == true){NUGYjCKzkt = false;}
      if(dTqxfQwYef == true){dTqxfQwYef = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYQYGCILMF
{ 
  void XqaaBzNZkU()
  { 
      bool AspzZVpcxt = false;
      bool KZGbeFazFE = false;
      bool AhTCqlungl = false;
      bool pCSVkTkJZh = false;
      bool FdFAXJoefW = false;
      bool UQdRTRYmIn = false;
      bool aCwKDIHjpL = false;
      bool TQYWzVbTeh = false;
      bool xPIJRZXBCT = false;
      bool tyBlHDhuxP = false;
      bool BEoTDDqGRy = false;
      bool oEIaqKslsc = false;
      bool jGhVRVPmOu = false;
      bool mgWPfranGO = false;
      bool hQiDdppaux = false;
      bool JwBTeuVSCg = false;
      bool nErWLIgsty = false;
      bool iFeetSWdrb = false;
      bool fnqRkpeDjj = false;
      bool WIlYZdYLrV = false;
      string fhBPQzqhnS;
      string DrEidbLbAl;
      string xZlaqUSQNZ;
      string DNihlCpQtN;
      string ROVJKkxLMx;
      string fCsEWGwZXw;
      string gZTOPoJWxb;
      string kuhmThDcQG;
      string XGEPtATdLe;
      string FQrygruHtV;
      string aZOjMjUFkn;
      string DTJQXZUDTO;
      string UeLRWTDiGa;
      string muitexrTDJ;
      string fOsWbkHbZG;
      string WqmeAwOwNr;
      string gkyJAHkOkZ;
      string gBAKhGknpk;
      string MaJzEwHDti;
      string iuGLcuPiVT;
      if(fhBPQzqhnS == aZOjMjUFkn){AspzZVpcxt = true;}
      else if(aZOjMjUFkn == fhBPQzqhnS){BEoTDDqGRy = true;}
      if(DrEidbLbAl == DTJQXZUDTO){KZGbeFazFE = true;}
      else if(DTJQXZUDTO == DrEidbLbAl){oEIaqKslsc = true;}
      if(xZlaqUSQNZ == UeLRWTDiGa){AhTCqlungl = true;}
      else if(UeLRWTDiGa == xZlaqUSQNZ){jGhVRVPmOu = true;}
      if(DNihlCpQtN == muitexrTDJ){pCSVkTkJZh = true;}
      else if(muitexrTDJ == DNihlCpQtN){mgWPfranGO = true;}
      if(ROVJKkxLMx == fOsWbkHbZG){FdFAXJoefW = true;}
      else if(fOsWbkHbZG == ROVJKkxLMx){hQiDdppaux = true;}
      if(fCsEWGwZXw == WqmeAwOwNr){UQdRTRYmIn = true;}
      else if(WqmeAwOwNr == fCsEWGwZXw){JwBTeuVSCg = true;}
      if(gZTOPoJWxb == gkyJAHkOkZ){aCwKDIHjpL = true;}
      else if(gkyJAHkOkZ == gZTOPoJWxb){nErWLIgsty = true;}
      if(kuhmThDcQG == gBAKhGknpk){TQYWzVbTeh = true;}
      if(XGEPtATdLe == MaJzEwHDti){xPIJRZXBCT = true;}
      if(FQrygruHtV == iuGLcuPiVT){tyBlHDhuxP = true;}
      while(gBAKhGknpk == kuhmThDcQG){iFeetSWdrb = true;}
      while(MaJzEwHDti == MaJzEwHDti){fnqRkpeDjj = true;}
      while(iuGLcuPiVT == iuGLcuPiVT){WIlYZdYLrV = true;}
      if(AspzZVpcxt == true){AspzZVpcxt = false;}
      if(KZGbeFazFE == true){KZGbeFazFE = false;}
      if(AhTCqlungl == true){AhTCqlungl = false;}
      if(pCSVkTkJZh == true){pCSVkTkJZh = false;}
      if(FdFAXJoefW == true){FdFAXJoefW = false;}
      if(UQdRTRYmIn == true){UQdRTRYmIn = false;}
      if(aCwKDIHjpL == true){aCwKDIHjpL = false;}
      if(TQYWzVbTeh == true){TQYWzVbTeh = false;}
      if(xPIJRZXBCT == true){xPIJRZXBCT = false;}
      if(tyBlHDhuxP == true){tyBlHDhuxP = false;}
      if(BEoTDDqGRy == true){BEoTDDqGRy = false;}
      if(oEIaqKslsc == true){oEIaqKslsc = false;}
      if(jGhVRVPmOu == true){jGhVRVPmOu = false;}
      if(mgWPfranGO == true){mgWPfranGO = false;}
      if(hQiDdppaux == true){hQiDdppaux = false;}
      if(JwBTeuVSCg == true){JwBTeuVSCg = false;}
      if(nErWLIgsty == true){nErWLIgsty = false;}
      if(iFeetSWdrb == true){iFeetSWdrb = false;}
      if(fnqRkpeDjj == true){fnqRkpeDjj = false;}
      if(WIlYZdYLrV == true){WIlYZdYLrV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class INMOKLVFMK
{ 
  void bWMWQnJWez()
  { 
      bool jZRICcQIdX = false;
      bool unMzBQScUI = false;
      bool KMrqgMMEqE = false;
      bool EwOjhCmqWK = false;
      bool WFSiBcJMfE = false;
      bool sShBcWhaap = false;
      bool QMQZSzYcRy = false;
      bool daFJlFtIoE = false;
      bool CAXmLlNMGK = false;
      bool ULPgtJnsPC = false;
      bool DfthaRMXPX = false;
      bool cYlWmPodNg = false;
      bool kMWHdRLYPc = false;
      bool QBslBVGpMs = false;
      bool YpxigwZstd = false;
      bool UJehQqJlEI = false;
      bool GnIlGafzUQ = false;
      bool JyRUIuOmZg = false;
      bool rRdkHHWKVK = false;
      bool LTlDmjhKbF = false;
      string UQoszIEaha;
      string nWCeqFOckM;
      string iGdARxrtjG;
      string XWEZehuOlt;
      string QqAtrVXRlq;
      string gRGudNlobC;
      string QKqbCRSczI;
      string JzqpwqGjHu;
      string ZZHsYGPJuR;
      string wGmidFAXqa;
      string DuSdghaPym;
      string GCgfbqDxDw;
      string BJghLCLHMp;
      string phrgqdHdLq;
      string eAKHKtZGGl;
      string CCUuZtNjRd;
      string VTDIwXJzny;
      string jYlMQByZWR;
      string cFAZnmNxHx;
      string QWLhULwCKm;
      if(UQoszIEaha == DuSdghaPym){jZRICcQIdX = true;}
      else if(DuSdghaPym == UQoszIEaha){DfthaRMXPX = true;}
      if(nWCeqFOckM == GCgfbqDxDw){unMzBQScUI = true;}
      else if(GCgfbqDxDw == nWCeqFOckM){cYlWmPodNg = true;}
      if(iGdARxrtjG == BJghLCLHMp){KMrqgMMEqE = true;}
      else if(BJghLCLHMp == iGdARxrtjG){kMWHdRLYPc = true;}
      if(XWEZehuOlt == phrgqdHdLq){EwOjhCmqWK = true;}
      else if(phrgqdHdLq == XWEZehuOlt){QBslBVGpMs = true;}
      if(QqAtrVXRlq == eAKHKtZGGl){WFSiBcJMfE = true;}
      else if(eAKHKtZGGl == QqAtrVXRlq){YpxigwZstd = true;}
      if(gRGudNlobC == CCUuZtNjRd){sShBcWhaap = true;}
      else if(CCUuZtNjRd == gRGudNlobC){UJehQqJlEI = true;}
      if(QKqbCRSczI == VTDIwXJzny){QMQZSzYcRy = true;}
      else if(VTDIwXJzny == QKqbCRSczI){GnIlGafzUQ = true;}
      if(JzqpwqGjHu == jYlMQByZWR){daFJlFtIoE = true;}
      if(ZZHsYGPJuR == cFAZnmNxHx){CAXmLlNMGK = true;}
      if(wGmidFAXqa == QWLhULwCKm){ULPgtJnsPC = true;}
      while(jYlMQByZWR == JzqpwqGjHu){JyRUIuOmZg = true;}
      while(cFAZnmNxHx == cFAZnmNxHx){rRdkHHWKVK = true;}
      while(QWLhULwCKm == QWLhULwCKm){LTlDmjhKbF = true;}
      if(jZRICcQIdX == true){jZRICcQIdX = false;}
      if(unMzBQScUI == true){unMzBQScUI = false;}
      if(KMrqgMMEqE == true){KMrqgMMEqE = false;}
      if(EwOjhCmqWK == true){EwOjhCmqWK = false;}
      if(WFSiBcJMfE == true){WFSiBcJMfE = false;}
      if(sShBcWhaap == true){sShBcWhaap = false;}
      if(QMQZSzYcRy == true){QMQZSzYcRy = false;}
      if(daFJlFtIoE == true){daFJlFtIoE = false;}
      if(CAXmLlNMGK == true){CAXmLlNMGK = false;}
      if(ULPgtJnsPC == true){ULPgtJnsPC = false;}
      if(DfthaRMXPX == true){DfthaRMXPX = false;}
      if(cYlWmPodNg == true){cYlWmPodNg = false;}
      if(kMWHdRLYPc == true){kMWHdRLYPc = false;}
      if(QBslBVGpMs == true){QBslBVGpMs = false;}
      if(YpxigwZstd == true){YpxigwZstd = false;}
      if(UJehQqJlEI == true){UJehQqJlEI = false;}
      if(GnIlGafzUQ == true){GnIlGafzUQ = false;}
      if(JyRUIuOmZg == true){JyRUIuOmZg = false;}
      if(rRdkHHWKVK == true){rRdkHHWKVK = false;}
      if(LTlDmjhKbF == true){LTlDmjhKbF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRGARNECXR
{ 
  void eSMEByknVV()
  { 
      bool jSMUDWapuE = false;
      bool szgktBJJXS = false;
      bool PPZtWCgZMO = false;
      bool VmwEEppkIy = false;
      bool NtMlKyWSdz = false;
      bool gnLBBTsSyB = false;
      bool oAdgiGCbgD = false;
      bool KXAYEVDmiX = false;
      bool fNwNghauCj = false;
      bool xXmHJMQfCE = false;
      bool wtlZnImlxf = false;
      bool QFiZVaEPzB = false;
      bool eHYwGmksPq = false;
      bool FXkebkbVYX = false;
      bool toyWSrnMlh = false;
      bool IAfBYoUpTA = false;
      bool XsWFZsUEyj = false;
      bool zhpaGpJCcO = false;
      bool zYHhiEqiFm = false;
      bool PlCYABRswZ = false;
      string SXlCkyecXl;
      string nYbAjXZEVs;
      string QUShzbmNbh;
      string EqZjEuRhhf;
      string pBLuIOCnLC;
      string KjgZkxFEDI;
      string KRBphxzrun;
      string FrVpCOJWZj;
      string YzBZXUKAyG;
      string pNdYUYAVNK;
      string PKrWwSNqWV;
      string nheSiLPaRM;
      string mztoxrNwUd;
      string OmJOUOGdcE;
      string HTcbSIiKpI;
      string IZDBXPQDZE;
      string EQVsHAXPyU;
      string FkyMFTWRWn;
      string JCGLVojIpE;
      string xDEYAqxiUR;
      if(SXlCkyecXl == PKrWwSNqWV){jSMUDWapuE = true;}
      else if(PKrWwSNqWV == SXlCkyecXl){wtlZnImlxf = true;}
      if(nYbAjXZEVs == nheSiLPaRM){szgktBJJXS = true;}
      else if(nheSiLPaRM == nYbAjXZEVs){QFiZVaEPzB = true;}
      if(QUShzbmNbh == mztoxrNwUd){PPZtWCgZMO = true;}
      else if(mztoxrNwUd == QUShzbmNbh){eHYwGmksPq = true;}
      if(EqZjEuRhhf == OmJOUOGdcE){VmwEEppkIy = true;}
      else if(OmJOUOGdcE == EqZjEuRhhf){FXkebkbVYX = true;}
      if(pBLuIOCnLC == HTcbSIiKpI){NtMlKyWSdz = true;}
      else if(HTcbSIiKpI == pBLuIOCnLC){toyWSrnMlh = true;}
      if(KjgZkxFEDI == IZDBXPQDZE){gnLBBTsSyB = true;}
      else if(IZDBXPQDZE == KjgZkxFEDI){IAfBYoUpTA = true;}
      if(KRBphxzrun == EQVsHAXPyU){oAdgiGCbgD = true;}
      else if(EQVsHAXPyU == KRBphxzrun){XsWFZsUEyj = true;}
      if(FrVpCOJWZj == FkyMFTWRWn){KXAYEVDmiX = true;}
      if(YzBZXUKAyG == JCGLVojIpE){fNwNghauCj = true;}
      if(pNdYUYAVNK == xDEYAqxiUR){xXmHJMQfCE = true;}
      while(FkyMFTWRWn == FrVpCOJWZj){zhpaGpJCcO = true;}
      while(JCGLVojIpE == JCGLVojIpE){zYHhiEqiFm = true;}
      while(xDEYAqxiUR == xDEYAqxiUR){PlCYABRswZ = true;}
      if(jSMUDWapuE == true){jSMUDWapuE = false;}
      if(szgktBJJXS == true){szgktBJJXS = false;}
      if(PPZtWCgZMO == true){PPZtWCgZMO = false;}
      if(VmwEEppkIy == true){VmwEEppkIy = false;}
      if(NtMlKyWSdz == true){NtMlKyWSdz = false;}
      if(gnLBBTsSyB == true){gnLBBTsSyB = false;}
      if(oAdgiGCbgD == true){oAdgiGCbgD = false;}
      if(KXAYEVDmiX == true){KXAYEVDmiX = false;}
      if(fNwNghauCj == true){fNwNghauCj = false;}
      if(xXmHJMQfCE == true){xXmHJMQfCE = false;}
      if(wtlZnImlxf == true){wtlZnImlxf = false;}
      if(QFiZVaEPzB == true){QFiZVaEPzB = false;}
      if(eHYwGmksPq == true){eHYwGmksPq = false;}
      if(FXkebkbVYX == true){FXkebkbVYX = false;}
      if(toyWSrnMlh == true){toyWSrnMlh = false;}
      if(IAfBYoUpTA == true){IAfBYoUpTA = false;}
      if(XsWFZsUEyj == true){XsWFZsUEyj = false;}
      if(zhpaGpJCcO == true){zhpaGpJCcO = false;}
      if(zYHhiEqiFm == true){zYHhiEqiFm = false;}
      if(PlCYABRswZ == true){PlCYABRswZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSGACKMHBJ
{ 
  void mTcOgkJfUw()
  { 
      bool LAyyReokPh = false;
      bool oPENsYZyaJ = false;
      bool OpeyXwBebV = false;
      bool HdmuqfDxVK = false;
      bool lUozSNozKF = false;
      bool VFFtgUVAaU = false;
      bool cJJtZKcIWM = false;
      bool VccPWtBfeJ = false;
      bool HCUVACYsOV = false;
      bool KDVAhbLuYH = false;
      bool kfcxjrboWm = false;
      bool ToUQNaomtX = false;
      bool ljtABSGcht = false;
      bool hFGWYbYWlH = false;
      bool ZjVbBUhFlG = false;
      bool mYBBVBlbuR = false;
      bool lzGbENhyrl = false;
      bool BRAmxCNRzg = false;
      bool jBpaHIEFBX = false;
      bool oxaUUZcsWm = false;
      string pRwAgbUctC;
      string PRCOUGTgCw;
      string fNinXVAaRs;
      string jqOuQWKuyQ;
      string dwHhSJuEXR;
      string GATRUbhIbL;
      string bsLASYDHyy;
      string wYhkSiGBUO;
      string ZuCzmiXwZn;
      string nBSlojjGPt;
      string GnGZVgRhzk;
      string VgnNlfqMNi;
      string AHgJJuGwwi;
      string zzkaHkocdF;
      string RowoRHNEAI;
      string sXsgszHwPZ;
      string aVlQkVuMGB;
      string pOhHQLKqqC;
      string gBwmobGEgI;
      string dsMDeuDfEw;
      if(pRwAgbUctC == GnGZVgRhzk){LAyyReokPh = true;}
      else if(GnGZVgRhzk == pRwAgbUctC){kfcxjrboWm = true;}
      if(PRCOUGTgCw == VgnNlfqMNi){oPENsYZyaJ = true;}
      else if(VgnNlfqMNi == PRCOUGTgCw){ToUQNaomtX = true;}
      if(fNinXVAaRs == AHgJJuGwwi){OpeyXwBebV = true;}
      else if(AHgJJuGwwi == fNinXVAaRs){ljtABSGcht = true;}
      if(jqOuQWKuyQ == zzkaHkocdF){HdmuqfDxVK = true;}
      else if(zzkaHkocdF == jqOuQWKuyQ){hFGWYbYWlH = true;}
      if(dwHhSJuEXR == RowoRHNEAI){lUozSNozKF = true;}
      else if(RowoRHNEAI == dwHhSJuEXR){ZjVbBUhFlG = true;}
      if(GATRUbhIbL == sXsgszHwPZ){VFFtgUVAaU = true;}
      else if(sXsgszHwPZ == GATRUbhIbL){mYBBVBlbuR = true;}
      if(bsLASYDHyy == aVlQkVuMGB){cJJtZKcIWM = true;}
      else if(aVlQkVuMGB == bsLASYDHyy){lzGbENhyrl = true;}
      if(wYhkSiGBUO == pOhHQLKqqC){VccPWtBfeJ = true;}
      if(ZuCzmiXwZn == gBwmobGEgI){HCUVACYsOV = true;}
      if(nBSlojjGPt == dsMDeuDfEw){KDVAhbLuYH = true;}
      while(pOhHQLKqqC == wYhkSiGBUO){BRAmxCNRzg = true;}
      while(gBwmobGEgI == gBwmobGEgI){jBpaHIEFBX = true;}
      while(dsMDeuDfEw == dsMDeuDfEw){oxaUUZcsWm = true;}
      if(LAyyReokPh == true){LAyyReokPh = false;}
      if(oPENsYZyaJ == true){oPENsYZyaJ = false;}
      if(OpeyXwBebV == true){OpeyXwBebV = false;}
      if(HdmuqfDxVK == true){HdmuqfDxVK = false;}
      if(lUozSNozKF == true){lUozSNozKF = false;}
      if(VFFtgUVAaU == true){VFFtgUVAaU = false;}
      if(cJJtZKcIWM == true){cJJtZKcIWM = false;}
      if(VccPWtBfeJ == true){VccPWtBfeJ = false;}
      if(HCUVACYsOV == true){HCUVACYsOV = false;}
      if(KDVAhbLuYH == true){KDVAhbLuYH = false;}
      if(kfcxjrboWm == true){kfcxjrboWm = false;}
      if(ToUQNaomtX == true){ToUQNaomtX = false;}
      if(ljtABSGcht == true){ljtABSGcht = false;}
      if(hFGWYbYWlH == true){hFGWYbYWlH = false;}
      if(ZjVbBUhFlG == true){ZjVbBUhFlG = false;}
      if(mYBBVBlbuR == true){mYBBVBlbuR = false;}
      if(lzGbENhyrl == true){lzGbENhyrl = false;}
      if(BRAmxCNRzg == true){BRAmxCNRzg = false;}
      if(jBpaHIEFBX == true){jBpaHIEFBX = false;}
      if(oxaUUZcsWm == true){oxaUUZcsWm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEVINSARXI
{ 
  void LKccCasLLq()
  { 
      bool wBqwldQEig = false;
      bool IkysXEZehc = false;
      bool jDIdTIsOph = false;
      bool PajwylPiMd = false;
      bool WCOgwewFcr = false;
      bool SMqfnssNbc = false;
      bool kBNAQgACul = false;
      bool npSDFhnbgo = false;
      bool LmlxPCjDIE = false;
      bool rCGisVnOPO = false;
      bool dtJpDbtmaF = false;
      bool ERfmRyPPjN = false;
      bool xxsptljiKj = false;
      bool sYLSKQcusn = false;
      bool HxcCzaWSRu = false;
      bool FXdBQfBTwR = false;
      bool qLbpMfFMbA = false;
      bool UTWwGATppS = false;
      bool OQRPeUtJBe = false;
      bool PJzbwwUlpT = false;
      string EGqApIEaug;
      string RsCbFuJxAk;
      string yaIzQUSDNx;
      string wDpXjFnGdB;
      string DVmSfccxhd;
      string uiQDNdyqjV;
      string pBMykODdqA;
      string HCSzgcnoTm;
      string rVVjBMllKG;
      string GwVIKCIohQ;
      string ZyFhWrPRVj;
      string pIXwcUfcwX;
      string cQTksKgKne;
      string TyHCNtPnMI;
      string xUPZPyXZep;
      string VfrJnIdTnL;
      string LFcqQqBVhi;
      string ErPmaHAsUu;
      string mGeyImGyNE;
      string PuzBxrrYJY;
      if(EGqApIEaug == ZyFhWrPRVj){wBqwldQEig = true;}
      else if(ZyFhWrPRVj == EGqApIEaug){dtJpDbtmaF = true;}
      if(RsCbFuJxAk == pIXwcUfcwX){IkysXEZehc = true;}
      else if(pIXwcUfcwX == RsCbFuJxAk){ERfmRyPPjN = true;}
      if(yaIzQUSDNx == cQTksKgKne){jDIdTIsOph = true;}
      else if(cQTksKgKne == yaIzQUSDNx){xxsptljiKj = true;}
      if(wDpXjFnGdB == TyHCNtPnMI){PajwylPiMd = true;}
      else if(TyHCNtPnMI == wDpXjFnGdB){sYLSKQcusn = true;}
      if(DVmSfccxhd == xUPZPyXZep){WCOgwewFcr = true;}
      else if(xUPZPyXZep == DVmSfccxhd){HxcCzaWSRu = true;}
      if(uiQDNdyqjV == VfrJnIdTnL){SMqfnssNbc = true;}
      else if(VfrJnIdTnL == uiQDNdyqjV){FXdBQfBTwR = true;}
      if(pBMykODdqA == LFcqQqBVhi){kBNAQgACul = true;}
      else if(LFcqQqBVhi == pBMykODdqA){qLbpMfFMbA = true;}
      if(HCSzgcnoTm == ErPmaHAsUu){npSDFhnbgo = true;}
      if(rVVjBMllKG == mGeyImGyNE){LmlxPCjDIE = true;}
      if(GwVIKCIohQ == PuzBxrrYJY){rCGisVnOPO = true;}
      while(ErPmaHAsUu == HCSzgcnoTm){UTWwGATppS = true;}
      while(mGeyImGyNE == mGeyImGyNE){OQRPeUtJBe = true;}
      while(PuzBxrrYJY == PuzBxrrYJY){PJzbwwUlpT = true;}
      if(wBqwldQEig == true){wBqwldQEig = false;}
      if(IkysXEZehc == true){IkysXEZehc = false;}
      if(jDIdTIsOph == true){jDIdTIsOph = false;}
      if(PajwylPiMd == true){PajwylPiMd = false;}
      if(WCOgwewFcr == true){WCOgwewFcr = false;}
      if(SMqfnssNbc == true){SMqfnssNbc = false;}
      if(kBNAQgACul == true){kBNAQgACul = false;}
      if(npSDFhnbgo == true){npSDFhnbgo = false;}
      if(LmlxPCjDIE == true){LmlxPCjDIE = false;}
      if(rCGisVnOPO == true){rCGisVnOPO = false;}
      if(dtJpDbtmaF == true){dtJpDbtmaF = false;}
      if(ERfmRyPPjN == true){ERfmRyPPjN = false;}
      if(xxsptljiKj == true){xxsptljiKj = false;}
      if(sYLSKQcusn == true){sYLSKQcusn = false;}
      if(HxcCzaWSRu == true){HxcCzaWSRu = false;}
      if(FXdBQfBTwR == true){FXdBQfBTwR = false;}
      if(qLbpMfFMbA == true){qLbpMfFMbA = false;}
      if(UTWwGATppS == true){UTWwGATppS = false;}
      if(OQRPeUtJBe == true){OQRPeUtJBe = false;}
      if(PJzbwwUlpT == true){PJzbwwUlpT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQQKIBWVYL
{ 
  void wAVypwofkY()
  { 
      bool cTYlnasRXY = false;
      bool kGhJOBNLyC = false;
      bool bWyFRWunYF = false;
      bool kUMhSmOtor = false;
      bool fnYfnZJQbT = false;
      bool DmIOlGUTTQ = false;
      bool eErSmQsApa = false;
      bool mSWFWmySQq = false;
      bool MeMFByLxwM = false;
      bool RuZXNawFsX = false;
      bool gJZAgjQDry = false;
      bool HBDbDArmQo = false;
      bool EuDdJqryru = false;
      bool qrZrKDELXR = false;
      bool gIFyEPryUN = false;
      bool iIoDSlFwqo = false;
      bool qSKxHPbKRA = false;
      bool wfPyHwpFZs = false;
      bool ztceLhCVZY = false;
      bool xIUhZOxHqn = false;
      string uRaHclNexu;
      string mTMXhSNJuz;
      string hIqNijEebu;
      string uDIPigBxsX;
      string iSVaRcIKzQ;
      string zaszrmaNYr;
      string giCCAiLxnA;
      string RQQXQPlQwF;
      string btfLuTKIWw;
      string GnXApAQTZh;
      string QKWyziJVib;
      string AJQTPmDqHf;
      string YCZrsdrQgQ;
      string zSpNnRWgLM;
      string KnZuuwWEjD;
      string xYMtJOkeFU;
      string psoRchTDey;
      string PWeuVkceww;
      string GnfcTZFwEZ;
      string frapVQzHRN;
      if(uRaHclNexu == QKWyziJVib){cTYlnasRXY = true;}
      else if(QKWyziJVib == uRaHclNexu){gJZAgjQDry = true;}
      if(mTMXhSNJuz == AJQTPmDqHf){kGhJOBNLyC = true;}
      else if(AJQTPmDqHf == mTMXhSNJuz){HBDbDArmQo = true;}
      if(hIqNijEebu == YCZrsdrQgQ){bWyFRWunYF = true;}
      else if(YCZrsdrQgQ == hIqNijEebu){EuDdJqryru = true;}
      if(uDIPigBxsX == zSpNnRWgLM){kUMhSmOtor = true;}
      else if(zSpNnRWgLM == uDIPigBxsX){qrZrKDELXR = true;}
      if(iSVaRcIKzQ == KnZuuwWEjD){fnYfnZJQbT = true;}
      else if(KnZuuwWEjD == iSVaRcIKzQ){gIFyEPryUN = true;}
      if(zaszrmaNYr == xYMtJOkeFU){DmIOlGUTTQ = true;}
      else if(xYMtJOkeFU == zaszrmaNYr){iIoDSlFwqo = true;}
      if(giCCAiLxnA == psoRchTDey){eErSmQsApa = true;}
      else if(psoRchTDey == giCCAiLxnA){qSKxHPbKRA = true;}
      if(RQQXQPlQwF == PWeuVkceww){mSWFWmySQq = true;}
      if(btfLuTKIWw == GnfcTZFwEZ){MeMFByLxwM = true;}
      if(GnXApAQTZh == frapVQzHRN){RuZXNawFsX = true;}
      while(PWeuVkceww == RQQXQPlQwF){wfPyHwpFZs = true;}
      while(GnfcTZFwEZ == GnfcTZFwEZ){ztceLhCVZY = true;}
      while(frapVQzHRN == frapVQzHRN){xIUhZOxHqn = true;}
      if(cTYlnasRXY == true){cTYlnasRXY = false;}
      if(kGhJOBNLyC == true){kGhJOBNLyC = false;}
      if(bWyFRWunYF == true){bWyFRWunYF = false;}
      if(kUMhSmOtor == true){kUMhSmOtor = false;}
      if(fnYfnZJQbT == true){fnYfnZJQbT = false;}
      if(DmIOlGUTTQ == true){DmIOlGUTTQ = false;}
      if(eErSmQsApa == true){eErSmQsApa = false;}
      if(mSWFWmySQq == true){mSWFWmySQq = false;}
      if(MeMFByLxwM == true){MeMFByLxwM = false;}
      if(RuZXNawFsX == true){RuZXNawFsX = false;}
      if(gJZAgjQDry == true){gJZAgjQDry = false;}
      if(HBDbDArmQo == true){HBDbDArmQo = false;}
      if(EuDdJqryru == true){EuDdJqryru = false;}
      if(qrZrKDELXR == true){qrZrKDELXR = false;}
      if(gIFyEPryUN == true){gIFyEPryUN = false;}
      if(iIoDSlFwqo == true){iIoDSlFwqo = false;}
      if(qSKxHPbKRA == true){qSKxHPbKRA = false;}
      if(wfPyHwpFZs == true){wfPyHwpFZs = false;}
      if(ztceLhCVZY == true){ztceLhCVZY = false;}
      if(xIUhZOxHqn == true){xIUhZOxHqn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDSGDVVAFO
{ 
  void wQXEkIULUZ()
  { 
      bool GjHuQyDwOT = false;
      bool KoUNSreero = false;
      bool PJbAIVcBAy = false;
      bool pWhEznxXNh = false;
      bool lbHbPokCFY = false;
      bool qdyfSxHHlu = false;
      bool VBuPdnGQOe = false;
      bool uHRJCnCAkT = false;
      bool jZubHLXBkC = false;
      bool fpkRMjfqxa = false;
      bool hTnaciMoce = false;
      bool tGWSKuGTHR = false;
      bool QFeLyFWzxS = false;
      bool IKDJlPlTyY = false;
      bool yiYGHZSSHQ = false;
      bool cLieKcobcX = false;
      bool MMrKViDMgt = false;
      bool JlViTgfXEX = false;
      bool lDrfowaXyI = false;
      bool aJqaLlqOjX = false;
      string eXFdhkHMSP;
      string NDZVDPkHSy;
      string cSINzIKdkj;
      string IrJbLlnmPK;
      string BsgeJwrcez;
      string hppufMOqdY;
      string ZdaiHVsyJQ;
      string bxqIwjkcDD;
      string QhzlBSBOuy;
      string XwJpjWRxXn;
      string DtSNWkyhyw;
      string bknaIqeohn;
      string TdCKsfmAXY;
      string RmFPzVOkOP;
      string TTQzWlIihs;
      string rcOiTYrIUp;
      string xxJYdnfXal;
      string bsZSUANDmG;
      string XESegoXVua;
      string dGQYRVJqUi;
      if(eXFdhkHMSP == DtSNWkyhyw){GjHuQyDwOT = true;}
      else if(DtSNWkyhyw == eXFdhkHMSP){hTnaciMoce = true;}
      if(NDZVDPkHSy == bknaIqeohn){KoUNSreero = true;}
      else if(bknaIqeohn == NDZVDPkHSy){tGWSKuGTHR = true;}
      if(cSINzIKdkj == TdCKsfmAXY){PJbAIVcBAy = true;}
      else if(TdCKsfmAXY == cSINzIKdkj){QFeLyFWzxS = true;}
      if(IrJbLlnmPK == RmFPzVOkOP){pWhEznxXNh = true;}
      else if(RmFPzVOkOP == IrJbLlnmPK){IKDJlPlTyY = true;}
      if(BsgeJwrcez == TTQzWlIihs){lbHbPokCFY = true;}
      else if(TTQzWlIihs == BsgeJwrcez){yiYGHZSSHQ = true;}
      if(hppufMOqdY == rcOiTYrIUp){qdyfSxHHlu = true;}
      else if(rcOiTYrIUp == hppufMOqdY){cLieKcobcX = true;}
      if(ZdaiHVsyJQ == xxJYdnfXal){VBuPdnGQOe = true;}
      else if(xxJYdnfXal == ZdaiHVsyJQ){MMrKViDMgt = true;}
      if(bxqIwjkcDD == bsZSUANDmG){uHRJCnCAkT = true;}
      if(QhzlBSBOuy == XESegoXVua){jZubHLXBkC = true;}
      if(XwJpjWRxXn == dGQYRVJqUi){fpkRMjfqxa = true;}
      while(bsZSUANDmG == bxqIwjkcDD){JlViTgfXEX = true;}
      while(XESegoXVua == XESegoXVua){lDrfowaXyI = true;}
      while(dGQYRVJqUi == dGQYRVJqUi){aJqaLlqOjX = true;}
      if(GjHuQyDwOT == true){GjHuQyDwOT = false;}
      if(KoUNSreero == true){KoUNSreero = false;}
      if(PJbAIVcBAy == true){PJbAIVcBAy = false;}
      if(pWhEznxXNh == true){pWhEznxXNh = false;}
      if(lbHbPokCFY == true){lbHbPokCFY = false;}
      if(qdyfSxHHlu == true){qdyfSxHHlu = false;}
      if(VBuPdnGQOe == true){VBuPdnGQOe = false;}
      if(uHRJCnCAkT == true){uHRJCnCAkT = false;}
      if(jZubHLXBkC == true){jZubHLXBkC = false;}
      if(fpkRMjfqxa == true){fpkRMjfqxa = false;}
      if(hTnaciMoce == true){hTnaciMoce = false;}
      if(tGWSKuGTHR == true){tGWSKuGTHR = false;}
      if(QFeLyFWzxS == true){QFeLyFWzxS = false;}
      if(IKDJlPlTyY == true){IKDJlPlTyY = false;}
      if(yiYGHZSSHQ == true){yiYGHZSSHQ = false;}
      if(cLieKcobcX == true){cLieKcobcX = false;}
      if(MMrKViDMgt == true){MMrKViDMgt = false;}
      if(JlViTgfXEX == true){JlViTgfXEX = false;}
      if(lDrfowaXyI == true){lDrfowaXyI = false;}
      if(aJqaLlqOjX == true){aJqaLlqOjX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDSZUMRYTI
{ 
  void nTUWLrngaf()
  { 
      bool VqrrdFyumE = false;
      bool TGEfhStbey = false;
      bool BzcAiRNtOB = false;
      bool zBBziyuwVL = false;
      bool QuCpGjxuzV = false;
      bool lYDrrWNrJM = false;
      bool qDglEREEwj = false;
      bool XyGTgFxmsy = false;
      bool TStsPayJHM = false;
      bool jClJTMOPko = false;
      bool erzPymRjKl = false;
      bool YazKrYJmWd = false;
      bool TtxiAULxzT = false;
      bool qhBDTaSeub = false;
      bool IOyUmIDbQu = false;
      bool DarHVjuPOc = false;
      bool bUjquqYuqR = false;
      bool FeruVFwbuq = false;
      bool RifDQPoshi = false;
      bool eCPRAmdHZu = false;
      string fZxXcSPZPc;
      string UJNGTiHNjZ;
      string dDwsUfRwGE;
      string cpGKBpqbbT;
      string QdLSMWxkfV;
      string tYnSDcdEDx;
      string BSTKAeDCFc;
      string rfkPJArcgy;
      string igPjKDBmHX;
      string LmYeSxKARh;
      string StfCdOnYID;
      string kAWFNUCiAw;
      string cPugRFHFxL;
      string pqLzeoAMGw;
      string OceDmLPSQx;
      string uazUEDyykX;
      string GibwNsoXaY;
      string TocEgAjrsF;
      string onnzQPqpta;
      string pCahofAipt;
      if(fZxXcSPZPc == StfCdOnYID){VqrrdFyumE = true;}
      else if(StfCdOnYID == fZxXcSPZPc){erzPymRjKl = true;}
      if(UJNGTiHNjZ == kAWFNUCiAw){TGEfhStbey = true;}
      else if(kAWFNUCiAw == UJNGTiHNjZ){YazKrYJmWd = true;}
      if(dDwsUfRwGE == cPugRFHFxL){BzcAiRNtOB = true;}
      else if(cPugRFHFxL == dDwsUfRwGE){TtxiAULxzT = true;}
      if(cpGKBpqbbT == pqLzeoAMGw){zBBziyuwVL = true;}
      else if(pqLzeoAMGw == cpGKBpqbbT){qhBDTaSeub = true;}
      if(QdLSMWxkfV == OceDmLPSQx){QuCpGjxuzV = true;}
      else if(OceDmLPSQx == QdLSMWxkfV){IOyUmIDbQu = true;}
      if(tYnSDcdEDx == uazUEDyykX){lYDrrWNrJM = true;}
      else if(uazUEDyykX == tYnSDcdEDx){DarHVjuPOc = true;}
      if(BSTKAeDCFc == GibwNsoXaY){qDglEREEwj = true;}
      else if(GibwNsoXaY == BSTKAeDCFc){bUjquqYuqR = true;}
      if(rfkPJArcgy == TocEgAjrsF){XyGTgFxmsy = true;}
      if(igPjKDBmHX == onnzQPqpta){TStsPayJHM = true;}
      if(LmYeSxKARh == pCahofAipt){jClJTMOPko = true;}
      while(TocEgAjrsF == rfkPJArcgy){FeruVFwbuq = true;}
      while(onnzQPqpta == onnzQPqpta){RifDQPoshi = true;}
      while(pCahofAipt == pCahofAipt){eCPRAmdHZu = true;}
      if(VqrrdFyumE == true){VqrrdFyumE = false;}
      if(TGEfhStbey == true){TGEfhStbey = false;}
      if(BzcAiRNtOB == true){BzcAiRNtOB = false;}
      if(zBBziyuwVL == true){zBBziyuwVL = false;}
      if(QuCpGjxuzV == true){QuCpGjxuzV = false;}
      if(lYDrrWNrJM == true){lYDrrWNrJM = false;}
      if(qDglEREEwj == true){qDglEREEwj = false;}
      if(XyGTgFxmsy == true){XyGTgFxmsy = false;}
      if(TStsPayJHM == true){TStsPayJHM = false;}
      if(jClJTMOPko == true){jClJTMOPko = false;}
      if(erzPymRjKl == true){erzPymRjKl = false;}
      if(YazKrYJmWd == true){YazKrYJmWd = false;}
      if(TtxiAULxzT == true){TtxiAULxzT = false;}
      if(qhBDTaSeub == true){qhBDTaSeub = false;}
      if(IOyUmIDbQu == true){IOyUmIDbQu = false;}
      if(DarHVjuPOc == true){DarHVjuPOc = false;}
      if(bUjquqYuqR == true){bUjquqYuqR = false;}
      if(FeruVFwbuq == true){FeruVFwbuq = false;}
      if(RifDQPoshi == true){RifDQPoshi = false;}
      if(eCPRAmdHZu == true){eCPRAmdHZu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCRLXLEFWJ
{ 
  void TdszycasHH()
  { 
      bool PPRVCCnSVb = false;
      bool xKNPfZopdO = false;
      bool UzjaOnjctJ = false;
      bool cWaXtbBKlF = false;
      bool SNTtgUgHNi = false;
      bool TXtRbQfpHO = false;
      bool SKYMyajpVE = false;
      bool XeDYuHepts = false;
      bool GbPKoFcIuc = false;
      bool wKDXmInGuG = false;
      bool kqlJLoUUWU = false;
      bool kowOHpuOXs = false;
      bool xbtrINaelm = false;
      bool SYtmHPoGzz = false;
      bool jHlaqGNoPw = false;
      bool MZiCIJwtAx = false;
      bool OpiiBMuIGr = false;
      bool AoPXJpoSAB = false;
      bool zkOoasorey = false;
      bool SuFBjtXDZe = false;
      string mxgmpACZIe;
      string NXBNuCpsSo;
      string KBKlnPGLfO;
      string cdCxoJQyks;
      string GsVpoSjZZZ;
      string bbemFkmuyZ;
      string tqtsBjUEXk;
      string lqIZiQfTwV;
      string ffkFmAyPrE;
      string WVAKzPzcoF;
      string yfCnnjTFEn;
      string FSyctNFnFA;
      string kFMTOPqxZS;
      string RDdqWzdxRC;
      string gsKDyEXXQk;
      string KKWoTrTiZX;
      string sWelVBnHFt;
      string iHWDSruIUJ;
      string rTgoHHgoWd;
      string fuXsJJOXgx;
      if(mxgmpACZIe == yfCnnjTFEn){PPRVCCnSVb = true;}
      else if(yfCnnjTFEn == mxgmpACZIe){kqlJLoUUWU = true;}
      if(NXBNuCpsSo == FSyctNFnFA){xKNPfZopdO = true;}
      else if(FSyctNFnFA == NXBNuCpsSo){kowOHpuOXs = true;}
      if(KBKlnPGLfO == kFMTOPqxZS){UzjaOnjctJ = true;}
      else if(kFMTOPqxZS == KBKlnPGLfO){xbtrINaelm = true;}
      if(cdCxoJQyks == RDdqWzdxRC){cWaXtbBKlF = true;}
      else if(RDdqWzdxRC == cdCxoJQyks){SYtmHPoGzz = true;}
      if(GsVpoSjZZZ == gsKDyEXXQk){SNTtgUgHNi = true;}
      else if(gsKDyEXXQk == GsVpoSjZZZ){jHlaqGNoPw = true;}
      if(bbemFkmuyZ == KKWoTrTiZX){TXtRbQfpHO = true;}
      else if(KKWoTrTiZX == bbemFkmuyZ){MZiCIJwtAx = true;}
      if(tqtsBjUEXk == sWelVBnHFt){SKYMyajpVE = true;}
      else if(sWelVBnHFt == tqtsBjUEXk){OpiiBMuIGr = true;}
      if(lqIZiQfTwV == iHWDSruIUJ){XeDYuHepts = true;}
      if(ffkFmAyPrE == rTgoHHgoWd){GbPKoFcIuc = true;}
      if(WVAKzPzcoF == fuXsJJOXgx){wKDXmInGuG = true;}
      while(iHWDSruIUJ == lqIZiQfTwV){AoPXJpoSAB = true;}
      while(rTgoHHgoWd == rTgoHHgoWd){zkOoasorey = true;}
      while(fuXsJJOXgx == fuXsJJOXgx){SuFBjtXDZe = true;}
      if(PPRVCCnSVb == true){PPRVCCnSVb = false;}
      if(xKNPfZopdO == true){xKNPfZopdO = false;}
      if(UzjaOnjctJ == true){UzjaOnjctJ = false;}
      if(cWaXtbBKlF == true){cWaXtbBKlF = false;}
      if(SNTtgUgHNi == true){SNTtgUgHNi = false;}
      if(TXtRbQfpHO == true){TXtRbQfpHO = false;}
      if(SKYMyajpVE == true){SKYMyajpVE = false;}
      if(XeDYuHepts == true){XeDYuHepts = false;}
      if(GbPKoFcIuc == true){GbPKoFcIuc = false;}
      if(wKDXmInGuG == true){wKDXmInGuG = false;}
      if(kqlJLoUUWU == true){kqlJLoUUWU = false;}
      if(kowOHpuOXs == true){kowOHpuOXs = false;}
      if(xbtrINaelm == true){xbtrINaelm = false;}
      if(SYtmHPoGzz == true){SYtmHPoGzz = false;}
      if(jHlaqGNoPw == true){jHlaqGNoPw = false;}
      if(MZiCIJwtAx == true){MZiCIJwtAx = false;}
      if(OpiiBMuIGr == true){OpiiBMuIGr = false;}
      if(AoPXJpoSAB == true){AoPXJpoSAB = false;}
      if(zkOoasorey == true){zkOoasorey = false;}
      if(SuFBjtXDZe == true){SuFBjtXDZe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JJGSTPSZXH
{ 
  void dUpMniVSRX()
  { 
      bool xGifIFkkYz = false;
      bool VTSYyfLBWZ = false;
      bool pxuCWsisCw = false;
      bool rUgtuscndQ = false;
      bool oFGusamyrg = false;
      bool VIjRdALgIP = false;
      bool VqibGBlYdF = false;
      bool DWXFjkqzJw = false;
      bool FjAUZjjPPu = false;
      bool gweNuyVdnq = false;
      bool nOUmdzjdgs = false;
      bool IMXMJkpNCW = false;
      bool QWIhXGqJKl = false;
      bool ONKRHpONqa = false;
      bool zFhWlUXSEJ = false;
      bool HHaRZRGmPW = false;
      bool HaTueuBFFT = false;
      bool VcVbXLnlwC = false;
      bool hYFAdGlsqo = false;
      bool jbxUSXllrp = false;
      string PIJmNDsLxm;
      string hDYKXurgKd;
      string nYXaUJcSFN;
      string iDxVSUQyIU;
      string kzIxefMqpX;
      string zWXUjpjhSE;
      string ZaFjDdFCrD;
      string dsXosnQawn;
      string xlcgNMeclb;
      string jhfEuKsXsA;
      string aJylsGzhbu;
      string ZJleGmxXWq;
      string zcQQTuNSti;
      string urgwNnnpnG;
      string NxAqBZwAyH;
      string MUBCByshSx;
      string sfmszgbpRS;
      string zHjPdBbYOs;
      string zMUlVZqeuO;
      string uGXpNgJHqU;
      if(PIJmNDsLxm == aJylsGzhbu){xGifIFkkYz = true;}
      else if(aJylsGzhbu == PIJmNDsLxm){nOUmdzjdgs = true;}
      if(hDYKXurgKd == ZJleGmxXWq){VTSYyfLBWZ = true;}
      else if(ZJleGmxXWq == hDYKXurgKd){IMXMJkpNCW = true;}
      if(nYXaUJcSFN == zcQQTuNSti){pxuCWsisCw = true;}
      else if(zcQQTuNSti == nYXaUJcSFN){QWIhXGqJKl = true;}
      if(iDxVSUQyIU == urgwNnnpnG){rUgtuscndQ = true;}
      else if(urgwNnnpnG == iDxVSUQyIU){ONKRHpONqa = true;}
      if(kzIxefMqpX == NxAqBZwAyH){oFGusamyrg = true;}
      else if(NxAqBZwAyH == kzIxefMqpX){zFhWlUXSEJ = true;}
      if(zWXUjpjhSE == MUBCByshSx){VIjRdALgIP = true;}
      else if(MUBCByshSx == zWXUjpjhSE){HHaRZRGmPW = true;}
      if(ZaFjDdFCrD == sfmszgbpRS){VqibGBlYdF = true;}
      else if(sfmszgbpRS == ZaFjDdFCrD){HaTueuBFFT = true;}
      if(dsXosnQawn == zHjPdBbYOs){DWXFjkqzJw = true;}
      if(xlcgNMeclb == zMUlVZqeuO){FjAUZjjPPu = true;}
      if(jhfEuKsXsA == uGXpNgJHqU){gweNuyVdnq = true;}
      while(zHjPdBbYOs == dsXosnQawn){VcVbXLnlwC = true;}
      while(zMUlVZqeuO == zMUlVZqeuO){hYFAdGlsqo = true;}
      while(uGXpNgJHqU == uGXpNgJHqU){jbxUSXllrp = true;}
      if(xGifIFkkYz == true){xGifIFkkYz = false;}
      if(VTSYyfLBWZ == true){VTSYyfLBWZ = false;}
      if(pxuCWsisCw == true){pxuCWsisCw = false;}
      if(rUgtuscndQ == true){rUgtuscndQ = false;}
      if(oFGusamyrg == true){oFGusamyrg = false;}
      if(VIjRdALgIP == true){VIjRdALgIP = false;}
      if(VqibGBlYdF == true){VqibGBlYdF = false;}
      if(DWXFjkqzJw == true){DWXFjkqzJw = false;}
      if(FjAUZjjPPu == true){FjAUZjjPPu = false;}
      if(gweNuyVdnq == true){gweNuyVdnq = false;}
      if(nOUmdzjdgs == true){nOUmdzjdgs = false;}
      if(IMXMJkpNCW == true){IMXMJkpNCW = false;}
      if(QWIhXGqJKl == true){QWIhXGqJKl = false;}
      if(ONKRHpONqa == true){ONKRHpONqa = false;}
      if(zFhWlUXSEJ == true){zFhWlUXSEJ = false;}
      if(HHaRZRGmPW == true){HHaRZRGmPW = false;}
      if(HaTueuBFFT == true){HaTueuBFFT = false;}
      if(VcVbXLnlwC == true){VcVbXLnlwC = false;}
      if(hYFAdGlsqo == true){hYFAdGlsqo = false;}
      if(jbxUSXllrp == true){jbxUSXllrp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEFTMHAHQF
{ 
  void TFQotUBGLu()
  { 
      bool nnstfEbQhI = false;
      bool HigxRzOuQJ = false;
      bool HfzHfutKQK = false;
      bool gmohyHyItz = false;
      bool AldZSkwufI = false;
      bool VPtcpHnlOj = false;
      bool JRAWbUsyyK = false;
      bool AFBRJUCYot = false;
      bool yzdHnRsLqp = false;
      bool SMtJphlGyy = false;
      bool qxwUHQNcTU = false;
      bool FOxTlJmrhK = false;
      bool ahHIrnKraa = false;
      bool iuaqDACIzX = false;
      bool DPrWkDOaXf = false;
      bool tsXmWJpncT = false;
      bool FVBrkJnGQk = false;
      bool HerJHLojWn = false;
      bool YjUufpXmTs = false;
      bool KNefShNzka = false;
      string XbRNwyIBXl;
      string hkRXAekWVA;
      string nLXneZrOlk;
      string OcKrXSTZwY;
      string zUCCeLjBjr;
      string XrwPTLDciV;
      string FsOmWFZYzh;
      string KLZwATIVJS;
      string pqetMWfuYL;
      string OqqaSFFPeZ;
      string kKBChMRzOz;
      string DhSPfOOUZA;
      string YeAnSTTzdt;
      string NrpjgepbMA;
      string EgfYIfXbuE;
      string qkpdAGKMiN;
      string rSVUlKrihA;
      string YmIYwrybfl;
      string wrDZDcCLia;
      string TcryIkKLlx;
      if(XbRNwyIBXl == kKBChMRzOz){nnstfEbQhI = true;}
      else if(kKBChMRzOz == XbRNwyIBXl){qxwUHQNcTU = true;}
      if(hkRXAekWVA == DhSPfOOUZA){HigxRzOuQJ = true;}
      else if(DhSPfOOUZA == hkRXAekWVA){FOxTlJmrhK = true;}
      if(nLXneZrOlk == YeAnSTTzdt){HfzHfutKQK = true;}
      else if(YeAnSTTzdt == nLXneZrOlk){ahHIrnKraa = true;}
      if(OcKrXSTZwY == NrpjgepbMA){gmohyHyItz = true;}
      else if(NrpjgepbMA == OcKrXSTZwY){iuaqDACIzX = true;}
      if(zUCCeLjBjr == EgfYIfXbuE){AldZSkwufI = true;}
      else if(EgfYIfXbuE == zUCCeLjBjr){DPrWkDOaXf = true;}
      if(XrwPTLDciV == qkpdAGKMiN){VPtcpHnlOj = true;}
      else if(qkpdAGKMiN == XrwPTLDciV){tsXmWJpncT = true;}
      if(FsOmWFZYzh == rSVUlKrihA){JRAWbUsyyK = true;}
      else if(rSVUlKrihA == FsOmWFZYzh){FVBrkJnGQk = true;}
      if(KLZwATIVJS == YmIYwrybfl){AFBRJUCYot = true;}
      if(pqetMWfuYL == wrDZDcCLia){yzdHnRsLqp = true;}
      if(OqqaSFFPeZ == TcryIkKLlx){SMtJphlGyy = true;}
      while(YmIYwrybfl == KLZwATIVJS){HerJHLojWn = true;}
      while(wrDZDcCLia == wrDZDcCLia){YjUufpXmTs = true;}
      while(TcryIkKLlx == TcryIkKLlx){KNefShNzka = true;}
      if(nnstfEbQhI == true){nnstfEbQhI = false;}
      if(HigxRzOuQJ == true){HigxRzOuQJ = false;}
      if(HfzHfutKQK == true){HfzHfutKQK = false;}
      if(gmohyHyItz == true){gmohyHyItz = false;}
      if(AldZSkwufI == true){AldZSkwufI = false;}
      if(VPtcpHnlOj == true){VPtcpHnlOj = false;}
      if(JRAWbUsyyK == true){JRAWbUsyyK = false;}
      if(AFBRJUCYot == true){AFBRJUCYot = false;}
      if(yzdHnRsLqp == true){yzdHnRsLqp = false;}
      if(SMtJphlGyy == true){SMtJphlGyy = false;}
      if(qxwUHQNcTU == true){qxwUHQNcTU = false;}
      if(FOxTlJmrhK == true){FOxTlJmrhK = false;}
      if(ahHIrnKraa == true){ahHIrnKraa = false;}
      if(iuaqDACIzX == true){iuaqDACIzX = false;}
      if(DPrWkDOaXf == true){DPrWkDOaXf = false;}
      if(tsXmWJpncT == true){tsXmWJpncT = false;}
      if(FVBrkJnGQk == true){FVBrkJnGQk = false;}
      if(HerJHLojWn == true){HerJHLojWn = false;}
      if(YjUufpXmTs == true){YjUufpXmTs = false;}
      if(KNefShNzka == true){KNefShNzka = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PPGDCCAYFD
{ 
  void GtrIUUOfmG()
  { 
      bool JlgbOKawGW = false;
      bool tjPCsDWCAN = false;
      bool ITmFAhtShp = false;
      bool RDYWsLyjVB = false;
      bool zEANlookoc = false;
      bool QedjJpybag = false;
      bool QIOQEqKrJg = false;
      bool FlgzOESZTL = false;
      bool rJdEZlZoNC = false;
      bool MWJnkqojIu = false;
      bool dwaHXeyeUF = false;
      bool WYIPnHdKqS = false;
      bool QVeHTibrNX = false;
      bool OiRXguhVft = false;
      bool ntTHfnOtzd = false;
      bool MesodIRTno = false;
      bool CGQxpmHjhs = false;
      bool YIdwdVBWaf = false;
      bool UhrjKjpbtY = false;
      bool dOgqrhdVQr = false;
      string zkWSBKhKeI;
      string fyEnsAqgeL;
      string zZmAHyZTNz;
      string mPJTXCHaKm;
      string ixWHFsBohp;
      string zSSwqYyWKD;
      string jNweUQnkQp;
      string rPVqbCDetO;
      string wjkWzTwMby;
      string DkPHCVAqlo;
      string EQYryixbTo;
      string VTbwGzbYeB;
      string TaJRlGzNnG;
      string BMrFJfLsYQ;
      string WUrlbjITBD;
      string saLkVcHGFq;
      string iimNnJaWlZ;
      string nhAOdyiWpC;
      string yfMkMZAHjg;
      string YFnhgmgeyS;
      if(zkWSBKhKeI == EQYryixbTo){JlgbOKawGW = true;}
      else if(EQYryixbTo == zkWSBKhKeI){dwaHXeyeUF = true;}
      if(fyEnsAqgeL == VTbwGzbYeB){tjPCsDWCAN = true;}
      else if(VTbwGzbYeB == fyEnsAqgeL){WYIPnHdKqS = true;}
      if(zZmAHyZTNz == TaJRlGzNnG){ITmFAhtShp = true;}
      else if(TaJRlGzNnG == zZmAHyZTNz){QVeHTibrNX = true;}
      if(mPJTXCHaKm == BMrFJfLsYQ){RDYWsLyjVB = true;}
      else if(BMrFJfLsYQ == mPJTXCHaKm){OiRXguhVft = true;}
      if(ixWHFsBohp == WUrlbjITBD){zEANlookoc = true;}
      else if(WUrlbjITBD == ixWHFsBohp){ntTHfnOtzd = true;}
      if(zSSwqYyWKD == saLkVcHGFq){QedjJpybag = true;}
      else if(saLkVcHGFq == zSSwqYyWKD){MesodIRTno = true;}
      if(jNweUQnkQp == iimNnJaWlZ){QIOQEqKrJg = true;}
      else if(iimNnJaWlZ == jNweUQnkQp){CGQxpmHjhs = true;}
      if(rPVqbCDetO == nhAOdyiWpC){FlgzOESZTL = true;}
      if(wjkWzTwMby == yfMkMZAHjg){rJdEZlZoNC = true;}
      if(DkPHCVAqlo == YFnhgmgeyS){MWJnkqojIu = true;}
      while(nhAOdyiWpC == rPVqbCDetO){YIdwdVBWaf = true;}
      while(yfMkMZAHjg == yfMkMZAHjg){UhrjKjpbtY = true;}
      while(YFnhgmgeyS == YFnhgmgeyS){dOgqrhdVQr = true;}
      if(JlgbOKawGW == true){JlgbOKawGW = false;}
      if(tjPCsDWCAN == true){tjPCsDWCAN = false;}
      if(ITmFAhtShp == true){ITmFAhtShp = false;}
      if(RDYWsLyjVB == true){RDYWsLyjVB = false;}
      if(zEANlookoc == true){zEANlookoc = false;}
      if(QedjJpybag == true){QedjJpybag = false;}
      if(QIOQEqKrJg == true){QIOQEqKrJg = false;}
      if(FlgzOESZTL == true){FlgzOESZTL = false;}
      if(rJdEZlZoNC == true){rJdEZlZoNC = false;}
      if(MWJnkqojIu == true){MWJnkqojIu = false;}
      if(dwaHXeyeUF == true){dwaHXeyeUF = false;}
      if(WYIPnHdKqS == true){WYIPnHdKqS = false;}
      if(QVeHTibrNX == true){QVeHTibrNX = false;}
      if(OiRXguhVft == true){OiRXguhVft = false;}
      if(ntTHfnOtzd == true){ntTHfnOtzd = false;}
      if(MesodIRTno == true){MesodIRTno = false;}
      if(CGQxpmHjhs == true){CGQxpmHjhs = false;}
      if(YIdwdVBWaf == true){YIdwdVBWaf = false;}
      if(UhrjKjpbtY == true){UhrjKjpbtY = false;}
      if(dOgqrhdVQr == true){dOgqrhdVQr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPLFYVYXXY
{ 
  void rYaaGGIcRD()
  { 
      bool qcOAkSrRbZ = false;
      bool LZsSSWREIC = false;
      bool XNBkHIxZcN = false;
      bool jjRBDdEfVo = false;
      bool JqpKenyxUH = false;
      bool huteJcadsc = false;
      bool URoNpaIqOo = false;
      bool SlhSrfXqFS = false;
      bool KAFVenpmra = false;
      bool CZlsUrCbUD = false;
      bool fGifouMalc = false;
      bool FjXaSUMShB = false;
      bool kUynlrAoyA = false;
      bool duVBlDQYgi = false;
      bool bPBPUSCLaz = false;
      bool eisTSLIttw = false;
      bool uXblyJOVnP = false;
      bool DmlzYVTiST = false;
      bool poOyUuBBia = false;
      bool uWejnDmOQL = false;
      string lWVpxFkMqw;
      string sYfCmMmWUE;
      string ElYgdorbcq;
      string jauycIoUnU;
      string mPBOairyMT;
      string UjHWAAxoLH;
      string NJjzMRdhZe;
      string WSiARnkJFt;
      string xsOJWzTXxc;
      string LAIfGcfCCJ;
      string EJYhwBBGFM;
      string OmjRJUuacM;
      string yFjwTWKCto;
      string HhHwonTfMU;
      string yNSkNXPqWl;
      string gFYoKzYbOY;
      string qyMPEgfmbV;
      string AONHNkmziu;
      string GTfHHCIRkp;
      string OqQmdAACgg;
      if(lWVpxFkMqw == EJYhwBBGFM){qcOAkSrRbZ = true;}
      else if(EJYhwBBGFM == lWVpxFkMqw){fGifouMalc = true;}
      if(sYfCmMmWUE == OmjRJUuacM){LZsSSWREIC = true;}
      else if(OmjRJUuacM == sYfCmMmWUE){FjXaSUMShB = true;}
      if(ElYgdorbcq == yFjwTWKCto){XNBkHIxZcN = true;}
      else if(yFjwTWKCto == ElYgdorbcq){kUynlrAoyA = true;}
      if(jauycIoUnU == HhHwonTfMU){jjRBDdEfVo = true;}
      else if(HhHwonTfMU == jauycIoUnU){duVBlDQYgi = true;}
      if(mPBOairyMT == yNSkNXPqWl){JqpKenyxUH = true;}
      else if(yNSkNXPqWl == mPBOairyMT){bPBPUSCLaz = true;}
      if(UjHWAAxoLH == gFYoKzYbOY){huteJcadsc = true;}
      else if(gFYoKzYbOY == UjHWAAxoLH){eisTSLIttw = true;}
      if(NJjzMRdhZe == qyMPEgfmbV){URoNpaIqOo = true;}
      else if(qyMPEgfmbV == NJjzMRdhZe){uXblyJOVnP = true;}
      if(WSiARnkJFt == AONHNkmziu){SlhSrfXqFS = true;}
      if(xsOJWzTXxc == GTfHHCIRkp){KAFVenpmra = true;}
      if(LAIfGcfCCJ == OqQmdAACgg){CZlsUrCbUD = true;}
      while(AONHNkmziu == WSiARnkJFt){DmlzYVTiST = true;}
      while(GTfHHCIRkp == GTfHHCIRkp){poOyUuBBia = true;}
      while(OqQmdAACgg == OqQmdAACgg){uWejnDmOQL = true;}
      if(qcOAkSrRbZ == true){qcOAkSrRbZ = false;}
      if(LZsSSWREIC == true){LZsSSWREIC = false;}
      if(XNBkHIxZcN == true){XNBkHIxZcN = false;}
      if(jjRBDdEfVo == true){jjRBDdEfVo = false;}
      if(JqpKenyxUH == true){JqpKenyxUH = false;}
      if(huteJcadsc == true){huteJcadsc = false;}
      if(URoNpaIqOo == true){URoNpaIqOo = false;}
      if(SlhSrfXqFS == true){SlhSrfXqFS = false;}
      if(KAFVenpmra == true){KAFVenpmra = false;}
      if(CZlsUrCbUD == true){CZlsUrCbUD = false;}
      if(fGifouMalc == true){fGifouMalc = false;}
      if(FjXaSUMShB == true){FjXaSUMShB = false;}
      if(kUynlrAoyA == true){kUynlrAoyA = false;}
      if(duVBlDQYgi == true){duVBlDQYgi = false;}
      if(bPBPUSCLaz == true){bPBPUSCLaz = false;}
      if(eisTSLIttw == true){eisTSLIttw = false;}
      if(uXblyJOVnP == true){uXblyJOVnP = false;}
      if(DmlzYVTiST == true){DmlzYVTiST = false;}
      if(poOyUuBBia == true){poOyUuBBia = false;}
      if(uWejnDmOQL == true){uWejnDmOQL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDKDJGDRSE
{ 
  void FUgxJPmVeX()
  { 
      bool PJKasiKhDm = false;
      bool YqTIKolZnS = false;
      bool hRQzwFMtUr = false;
      bool xhpmuoRbPx = false;
      bool GBgPeokpNx = false;
      bool aCWcpxsKen = false;
      bool WQNLpqBgNV = false;
      bool WJJqMgkBUH = false;
      bool UVgXRtLMwx = false;
      bool wGwbZpnVZn = false;
      bool mDcrZQreQJ = false;
      bool MrpXSAiosu = false;
      bool fokPYQMgRV = false;
      bool rObfTQsoyA = false;
      bool CfwlkEQYJZ = false;
      bool GzbdIySMSJ = false;
      bool DLNtQxPJDB = false;
      bool HtqsszryeU = false;
      bool znXqOsmxWV = false;
      bool yfVnwqRBUm = false;
      string MkKFfIJYUz;
      string OcFrRDPlZZ;
      string iteKMksLAA;
      string tSZXDWMimO;
      string XGUUuwdYsd;
      string owJxJSGzru;
      string PxYUFuCgot;
      string pgzLBcZJPQ;
      string HUSWKyJcNk;
      string PNpryZgzPz;
      string swjymHwxwg;
      string rxjbmueCJG;
      string lZSDdcqHNa;
      string wZsPWKjTiC;
      string BMfgrScOED;
      string udoIMSdfTK;
      string QojUkSDTEc;
      string KLSGFZslLL;
      string zbDJfRjkCE;
      string gEzYlMcLwY;
      if(MkKFfIJYUz == swjymHwxwg){PJKasiKhDm = true;}
      else if(swjymHwxwg == MkKFfIJYUz){mDcrZQreQJ = true;}
      if(OcFrRDPlZZ == rxjbmueCJG){YqTIKolZnS = true;}
      else if(rxjbmueCJG == OcFrRDPlZZ){MrpXSAiosu = true;}
      if(iteKMksLAA == lZSDdcqHNa){hRQzwFMtUr = true;}
      else if(lZSDdcqHNa == iteKMksLAA){fokPYQMgRV = true;}
      if(tSZXDWMimO == wZsPWKjTiC){xhpmuoRbPx = true;}
      else if(wZsPWKjTiC == tSZXDWMimO){rObfTQsoyA = true;}
      if(XGUUuwdYsd == BMfgrScOED){GBgPeokpNx = true;}
      else if(BMfgrScOED == XGUUuwdYsd){CfwlkEQYJZ = true;}
      if(owJxJSGzru == udoIMSdfTK){aCWcpxsKen = true;}
      else if(udoIMSdfTK == owJxJSGzru){GzbdIySMSJ = true;}
      if(PxYUFuCgot == QojUkSDTEc){WQNLpqBgNV = true;}
      else if(QojUkSDTEc == PxYUFuCgot){DLNtQxPJDB = true;}
      if(pgzLBcZJPQ == KLSGFZslLL){WJJqMgkBUH = true;}
      if(HUSWKyJcNk == zbDJfRjkCE){UVgXRtLMwx = true;}
      if(PNpryZgzPz == gEzYlMcLwY){wGwbZpnVZn = true;}
      while(KLSGFZslLL == pgzLBcZJPQ){HtqsszryeU = true;}
      while(zbDJfRjkCE == zbDJfRjkCE){znXqOsmxWV = true;}
      while(gEzYlMcLwY == gEzYlMcLwY){yfVnwqRBUm = true;}
      if(PJKasiKhDm == true){PJKasiKhDm = false;}
      if(YqTIKolZnS == true){YqTIKolZnS = false;}
      if(hRQzwFMtUr == true){hRQzwFMtUr = false;}
      if(xhpmuoRbPx == true){xhpmuoRbPx = false;}
      if(GBgPeokpNx == true){GBgPeokpNx = false;}
      if(aCWcpxsKen == true){aCWcpxsKen = false;}
      if(WQNLpqBgNV == true){WQNLpqBgNV = false;}
      if(WJJqMgkBUH == true){WJJqMgkBUH = false;}
      if(UVgXRtLMwx == true){UVgXRtLMwx = false;}
      if(wGwbZpnVZn == true){wGwbZpnVZn = false;}
      if(mDcrZQreQJ == true){mDcrZQreQJ = false;}
      if(MrpXSAiosu == true){MrpXSAiosu = false;}
      if(fokPYQMgRV == true){fokPYQMgRV = false;}
      if(rObfTQsoyA == true){rObfTQsoyA = false;}
      if(CfwlkEQYJZ == true){CfwlkEQYJZ = false;}
      if(GzbdIySMSJ == true){GzbdIySMSJ = false;}
      if(DLNtQxPJDB == true){DLNtQxPJDB = false;}
      if(HtqsszryeU == true){HtqsszryeU = false;}
      if(znXqOsmxWV == true){znXqOsmxWV = false;}
      if(yfVnwqRBUm == true){yfVnwqRBUm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCFECONMSR
{ 
  void HJnyeNLLll()
  { 
      bool YhaUOQfSZn = false;
      bool kbNFiAgnFg = false;
      bool egOeFgLiDN = false;
      bool iStGBPcOSl = false;
      bool bxdCjndOUC = false;
      bool UtfsAqSwPg = false;
      bool EwOLERhHES = false;
      bool WSVTEhCLtQ = false;
      bool DxOBsomBGJ = false;
      bool wgykgehRxR = false;
      bool GWJBfBYLnR = false;
      bool nGBydHhNSP = false;
      bool efAuWoTjmY = false;
      bool zkObKfmMUr = false;
      bool QaNnUoeAHY = false;
      bool xTzhmaVOep = false;
      bool gnYOSDrYnx = false;
      bool UUrayDSLZg = false;
      bool KTbNbflfoj = false;
      bool KYheKbCyVQ = false;
      string dhCBIEAWBu;
      string hjXmLuQABz;
      string jTjYphiEwu;
      string COiLSmTyAZ;
      string YRrRxoqfns;
      string CrRhhJxdLZ;
      string UwaFsTALTY;
      string aRAaaRaSaA;
      string qDPCrKwBdI;
      string oplZFbqlXd;
      string oeLPRjqqGP;
      string ieCLiRfXNh;
      string WzhLikfaUy;
      string antxLMrAjH;
      string SEtNZJmaqn;
      string wSYpGpwAfg;
      string EQVIntkFAV;
      string YfmGPSETlZ;
      string xEigCHPEpU;
      string QrUDCBilZe;
      if(dhCBIEAWBu == oeLPRjqqGP){YhaUOQfSZn = true;}
      else if(oeLPRjqqGP == dhCBIEAWBu){GWJBfBYLnR = true;}
      if(hjXmLuQABz == ieCLiRfXNh){kbNFiAgnFg = true;}
      else if(ieCLiRfXNh == hjXmLuQABz){nGBydHhNSP = true;}
      if(jTjYphiEwu == WzhLikfaUy){egOeFgLiDN = true;}
      else if(WzhLikfaUy == jTjYphiEwu){efAuWoTjmY = true;}
      if(COiLSmTyAZ == antxLMrAjH){iStGBPcOSl = true;}
      else if(antxLMrAjH == COiLSmTyAZ){zkObKfmMUr = true;}
      if(YRrRxoqfns == SEtNZJmaqn){bxdCjndOUC = true;}
      else if(SEtNZJmaqn == YRrRxoqfns){QaNnUoeAHY = true;}
      if(CrRhhJxdLZ == wSYpGpwAfg){UtfsAqSwPg = true;}
      else if(wSYpGpwAfg == CrRhhJxdLZ){xTzhmaVOep = true;}
      if(UwaFsTALTY == EQVIntkFAV){EwOLERhHES = true;}
      else if(EQVIntkFAV == UwaFsTALTY){gnYOSDrYnx = true;}
      if(aRAaaRaSaA == YfmGPSETlZ){WSVTEhCLtQ = true;}
      if(qDPCrKwBdI == xEigCHPEpU){DxOBsomBGJ = true;}
      if(oplZFbqlXd == QrUDCBilZe){wgykgehRxR = true;}
      while(YfmGPSETlZ == aRAaaRaSaA){UUrayDSLZg = true;}
      while(xEigCHPEpU == xEigCHPEpU){KTbNbflfoj = true;}
      while(QrUDCBilZe == QrUDCBilZe){KYheKbCyVQ = true;}
      if(YhaUOQfSZn == true){YhaUOQfSZn = false;}
      if(kbNFiAgnFg == true){kbNFiAgnFg = false;}
      if(egOeFgLiDN == true){egOeFgLiDN = false;}
      if(iStGBPcOSl == true){iStGBPcOSl = false;}
      if(bxdCjndOUC == true){bxdCjndOUC = false;}
      if(UtfsAqSwPg == true){UtfsAqSwPg = false;}
      if(EwOLERhHES == true){EwOLERhHES = false;}
      if(WSVTEhCLtQ == true){WSVTEhCLtQ = false;}
      if(DxOBsomBGJ == true){DxOBsomBGJ = false;}
      if(wgykgehRxR == true){wgykgehRxR = false;}
      if(GWJBfBYLnR == true){GWJBfBYLnR = false;}
      if(nGBydHhNSP == true){nGBydHhNSP = false;}
      if(efAuWoTjmY == true){efAuWoTjmY = false;}
      if(zkObKfmMUr == true){zkObKfmMUr = false;}
      if(QaNnUoeAHY == true){QaNnUoeAHY = false;}
      if(xTzhmaVOep == true){xTzhmaVOep = false;}
      if(gnYOSDrYnx == true){gnYOSDrYnx = false;}
      if(UUrayDSLZg == true){UUrayDSLZg = false;}
      if(KTbNbflfoj == true){KTbNbflfoj = false;}
      if(KYheKbCyVQ == true){KYheKbCyVQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFZYPVTKTH
{ 
  void yJqpEPddtx()
  { 
      bool YhpIIZeDsL = false;
      bool YbOYroqMNJ = false;
      bool jNbKxJjziw = false;
      bool BeFeOWxOHx = false;
      bool fHrUrZsCEo = false;
      bool YCMOlLGfKy = false;
      bool pfTxKtVjKU = false;
      bool qcFQcbVGRX = false;
      bool PgutWyRqrD = false;
      bool QRDIHAntJy = false;
      bool DJrixwxwkJ = false;
      bool oANliIjYZM = false;
      bool beqGEYYwIc = false;
      bool nbwTUFoLxa = false;
      bool BUFhNPERZz = false;
      bool PPUxVXRkeY = false;
      bool WAmIVNDsRc = false;
      bool SYbyLHZIsn = false;
      bool THWJNXHzxw = false;
      bool mEgXEAgxMA = false;
      string BwZhfNibjg;
      string OWkqhiBFft;
      string GOKIRlKTtW;
      string OqwNeDbGJW;
      string zAzRKYAyFD;
      string fodnNmkQQs;
      string DOhMRXaWMe;
      string HuuJtFOrys;
      string kLOpqZMHAq;
      string RKoPSkSlzm;
      string xclZujtTtH;
      string XrSWHrzqVr;
      string KSWUMxGeqI;
      string mbsKuIZnuH;
      string esMrSYqRIa;
      string kbQGcdGQMy;
      string cOclUwzIbz;
      string RLwNNQFdBn;
      string FnWPXLLlgQ;
      string BIawdQPaXW;
      if(BwZhfNibjg == xclZujtTtH){YhpIIZeDsL = true;}
      else if(xclZujtTtH == BwZhfNibjg){DJrixwxwkJ = true;}
      if(OWkqhiBFft == XrSWHrzqVr){YbOYroqMNJ = true;}
      else if(XrSWHrzqVr == OWkqhiBFft){oANliIjYZM = true;}
      if(GOKIRlKTtW == KSWUMxGeqI){jNbKxJjziw = true;}
      else if(KSWUMxGeqI == GOKIRlKTtW){beqGEYYwIc = true;}
      if(OqwNeDbGJW == mbsKuIZnuH){BeFeOWxOHx = true;}
      else if(mbsKuIZnuH == OqwNeDbGJW){nbwTUFoLxa = true;}
      if(zAzRKYAyFD == esMrSYqRIa){fHrUrZsCEo = true;}
      else if(esMrSYqRIa == zAzRKYAyFD){BUFhNPERZz = true;}
      if(fodnNmkQQs == kbQGcdGQMy){YCMOlLGfKy = true;}
      else if(kbQGcdGQMy == fodnNmkQQs){PPUxVXRkeY = true;}
      if(DOhMRXaWMe == cOclUwzIbz){pfTxKtVjKU = true;}
      else if(cOclUwzIbz == DOhMRXaWMe){WAmIVNDsRc = true;}
      if(HuuJtFOrys == RLwNNQFdBn){qcFQcbVGRX = true;}
      if(kLOpqZMHAq == FnWPXLLlgQ){PgutWyRqrD = true;}
      if(RKoPSkSlzm == BIawdQPaXW){QRDIHAntJy = true;}
      while(RLwNNQFdBn == HuuJtFOrys){SYbyLHZIsn = true;}
      while(FnWPXLLlgQ == FnWPXLLlgQ){THWJNXHzxw = true;}
      while(BIawdQPaXW == BIawdQPaXW){mEgXEAgxMA = true;}
      if(YhpIIZeDsL == true){YhpIIZeDsL = false;}
      if(YbOYroqMNJ == true){YbOYroqMNJ = false;}
      if(jNbKxJjziw == true){jNbKxJjziw = false;}
      if(BeFeOWxOHx == true){BeFeOWxOHx = false;}
      if(fHrUrZsCEo == true){fHrUrZsCEo = false;}
      if(YCMOlLGfKy == true){YCMOlLGfKy = false;}
      if(pfTxKtVjKU == true){pfTxKtVjKU = false;}
      if(qcFQcbVGRX == true){qcFQcbVGRX = false;}
      if(PgutWyRqrD == true){PgutWyRqrD = false;}
      if(QRDIHAntJy == true){QRDIHAntJy = false;}
      if(DJrixwxwkJ == true){DJrixwxwkJ = false;}
      if(oANliIjYZM == true){oANliIjYZM = false;}
      if(beqGEYYwIc == true){beqGEYYwIc = false;}
      if(nbwTUFoLxa == true){nbwTUFoLxa = false;}
      if(BUFhNPERZz == true){BUFhNPERZz = false;}
      if(PPUxVXRkeY == true){PPUxVXRkeY = false;}
      if(WAmIVNDsRc == true){WAmIVNDsRc = false;}
      if(SYbyLHZIsn == true){SYbyLHZIsn = false;}
      if(THWJNXHzxw == true){THWJNXHzxw = false;}
      if(mEgXEAgxMA == true){mEgXEAgxMA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HHUEGITWLG
{ 
  void zePZtBucqG()
  { 
      bool wcyrTRbadE = false;
      bool gPwMUEQqHq = false;
      bool XfSTWDRAQI = false;
      bool AxUOlyHedx = false;
      bool BKPPYWRbgj = false;
      bool FYbxXPKdVP = false;
      bool AaKVDjthaW = false;
      bool wlNJpNQCtz = false;
      bool loSgCaUXpW = false;
      bool ncJNwZAtMo = false;
      bool biBKmTLRGK = false;
      bool zHiVdLIdSb = false;
      bool PWrEhSczMQ = false;
      bool MVpFXCnIti = false;
      bool PCQeXftnjk = false;
      bool RWbjZFqwbT = false;
      bool pLFpxcQdya = false;
      bool WzjiMMFMgB = false;
      bool YoPbyptGfS = false;
      bool LqfZrDxahu = false;
      string NKoosGaqVC;
      string TlWUwjkCUB;
      string KfYeYNWwFd;
      string lPiLSnBkEJ;
      string uTcSwDFbJU;
      string oMjQVglKQe;
      string idlrQDDKCI;
      string hzyKFqDGhU;
      string IulknYfRok;
      string CqUYaQgjBs;
      string AuYBloNZLe;
      string debuWnrBDq;
      string XlURFpeYjn;
      string JSEoUMVkyy;
      string LGFKGWPYCl;
      string YffKVNZHuu;
      string KnoWVKalaJ;
      string RGDFfRfJKh;
      string aFWxPdltTG;
      string mOoCnWQiow;
      if(NKoosGaqVC == AuYBloNZLe){wcyrTRbadE = true;}
      else if(AuYBloNZLe == NKoosGaqVC){biBKmTLRGK = true;}
      if(TlWUwjkCUB == debuWnrBDq){gPwMUEQqHq = true;}
      else if(debuWnrBDq == TlWUwjkCUB){zHiVdLIdSb = true;}
      if(KfYeYNWwFd == XlURFpeYjn){XfSTWDRAQI = true;}
      else if(XlURFpeYjn == KfYeYNWwFd){PWrEhSczMQ = true;}
      if(lPiLSnBkEJ == JSEoUMVkyy){AxUOlyHedx = true;}
      else if(JSEoUMVkyy == lPiLSnBkEJ){MVpFXCnIti = true;}
      if(uTcSwDFbJU == LGFKGWPYCl){BKPPYWRbgj = true;}
      else if(LGFKGWPYCl == uTcSwDFbJU){PCQeXftnjk = true;}
      if(oMjQVglKQe == YffKVNZHuu){FYbxXPKdVP = true;}
      else if(YffKVNZHuu == oMjQVglKQe){RWbjZFqwbT = true;}
      if(idlrQDDKCI == KnoWVKalaJ){AaKVDjthaW = true;}
      else if(KnoWVKalaJ == idlrQDDKCI){pLFpxcQdya = true;}
      if(hzyKFqDGhU == RGDFfRfJKh){wlNJpNQCtz = true;}
      if(IulknYfRok == aFWxPdltTG){loSgCaUXpW = true;}
      if(CqUYaQgjBs == mOoCnWQiow){ncJNwZAtMo = true;}
      while(RGDFfRfJKh == hzyKFqDGhU){WzjiMMFMgB = true;}
      while(aFWxPdltTG == aFWxPdltTG){YoPbyptGfS = true;}
      while(mOoCnWQiow == mOoCnWQiow){LqfZrDxahu = true;}
      if(wcyrTRbadE == true){wcyrTRbadE = false;}
      if(gPwMUEQqHq == true){gPwMUEQqHq = false;}
      if(XfSTWDRAQI == true){XfSTWDRAQI = false;}
      if(AxUOlyHedx == true){AxUOlyHedx = false;}
      if(BKPPYWRbgj == true){BKPPYWRbgj = false;}
      if(FYbxXPKdVP == true){FYbxXPKdVP = false;}
      if(AaKVDjthaW == true){AaKVDjthaW = false;}
      if(wlNJpNQCtz == true){wlNJpNQCtz = false;}
      if(loSgCaUXpW == true){loSgCaUXpW = false;}
      if(ncJNwZAtMo == true){ncJNwZAtMo = false;}
      if(biBKmTLRGK == true){biBKmTLRGK = false;}
      if(zHiVdLIdSb == true){zHiVdLIdSb = false;}
      if(PWrEhSczMQ == true){PWrEhSczMQ = false;}
      if(MVpFXCnIti == true){MVpFXCnIti = false;}
      if(PCQeXftnjk == true){PCQeXftnjk = false;}
      if(RWbjZFqwbT == true){RWbjZFqwbT = false;}
      if(pLFpxcQdya == true){pLFpxcQdya = false;}
      if(WzjiMMFMgB == true){WzjiMMFMgB = false;}
      if(YoPbyptGfS == true){YoPbyptGfS = false;}
      if(LqfZrDxahu == true){LqfZrDxahu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGWMELBKMQ
{ 
  void IokfMqpESw()
  { 
      bool IeHRoSYKxV = false;
      bool ihlHtCbzPT = false;
      bool NWAXRrhojq = false;
      bool qMWBBTlyby = false;
      bool TXOfoFfjxD = false;
      bool TEzHUkdjzx = false;
      bool jiaGdVLkFa = false;
      bool QdWQAoHUhM = false;
      bool LyrgWmNOgP = false;
      bool oCyeNjxHBT = false;
      bool tudWmoghHe = false;
      bool dIBlklqsiq = false;
      bool IwEpkNerDQ = false;
      bool rATNSQTUsg = false;
      bool FeHClgBMsb = false;
      bool rDXJLxqnkY = false;
      bool KneplcomTT = false;
      bool SVACkdoBDE = false;
      bool MSyaXobJCU = false;
      bool YejUWRzQPI = false;
      string ODNQIpZnPe;
      string YbOdkAQEmU;
      string UJOuQqVQNY;
      string kGPeKMSiQU;
      string jyiFywDApE;
      string bSCbgEoRzQ;
      string UIZpsSMjSX;
      string ggmSkVaIxT;
      string nVaIxSDmyG;
      string WBiAAaXsLe;
      string jSgRXteiqK;
      string cfTfbzhRra;
      string OYlMBexmSJ;
      string yhxRjVnIjC;
      string nTwmcqgDXB;
      string rFAkQLgUQr;
      string wqQgLuiCwG;
      string LZgpmtbyiJ;
      string ytPRRrhMBX;
      string nSqrFwDPbh;
      if(ODNQIpZnPe == jSgRXteiqK){IeHRoSYKxV = true;}
      else if(jSgRXteiqK == ODNQIpZnPe){tudWmoghHe = true;}
      if(YbOdkAQEmU == cfTfbzhRra){ihlHtCbzPT = true;}
      else if(cfTfbzhRra == YbOdkAQEmU){dIBlklqsiq = true;}
      if(UJOuQqVQNY == OYlMBexmSJ){NWAXRrhojq = true;}
      else if(OYlMBexmSJ == UJOuQqVQNY){IwEpkNerDQ = true;}
      if(kGPeKMSiQU == yhxRjVnIjC){qMWBBTlyby = true;}
      else if(yhxRjVnIjC == kGPeKMSiQU){rATNSQTUsg = true;}
      if(jyiFywDApE == nTwmcqgDXB){TXOfoFfjxD = true;}
      else if(nTwmcqgDXB == jyiFywDApE){FeHClgBMsb = true;}
      if(bSCbgEoRzQ == rFAkQLgUQr){TEzHUkdjzx = true;}
      else if(rFAkQLgUQr == bSCbgEoRzQ){rDXJLxqnkY = true;}
      if(UIZpsSMjSX == wqQgLuiCwG){jiaGdVLkFa = true;}
      else if(wqQgLuiCwG == UIZpsSMjSX){KneplcomTT = true;}
      if(ggmSkVaIxT == LZgpmtbyiJ){QdWQAoHUhM = true;}
      if(nVaIxSDmyG == ytPRRrhMBX){LyrgWmNOgP = true;}
      if(WBiAAaXsLe == nSqrFwDPbh){oCyeNjxHBT = true;}
      while(LZgpmtbyiJ == ggmSkVaIxT){SVACkdoBDE = true;}
      while(ytPRRrhMBX == ytPRRrhMBX){MSyaXobJCU = true;}
      while(nSqrFwDPbh == nSqrFwDPbh){YejUWRzQPI = true;}
      if(IeHRoSYKxV == true){IeHRoSYKxV = false;}
      if(ihlHtCbzPT == true){ihlHtCbzPT = false;}
      if(NWAXRrhojq == true){NWAXRrhojq = false;}
      if(qMWBBTlyby == true){qMWBBTlyby = false;}
      if(TXOfoFfjxD == true){TXOfoFfjxD = false;}
      if(TEzHUkdjzx == true){TEzHUkdjzx = false;}
      if(jiaGdVLkFa == true){jiaGdVLkFa = false;}
      if(QdWQAoHUhM == true){QdWQAoHUhM = false;}
      if(LyrgWmNOgP == true){LyrgWmNOgP = false;}
      if(oCyeNjxHBT == true){oCyeNjxHBT = false;}
      if(tudWmoghHe == true){tudWmoghHe = false;}
      if(dIBlklqsiq == true){dIBlklqsiq = false;}
      if(IwEpkNerDQ == true){IwEpkNerDQ = false;}
      if(rATNSQTUsg == true){rATNSQTUsg = false;}
      if(FeHClgBMsb == true){FeHClgBMsb = false;}
      if(rDXJLxqnkY == true){rDXJLxqnkY = false;}
      if(KneplcomTT == true){KneplcomTT = false;}
      if(SVACkdoBDE == true){SVACkdoBDE = false;}
      if(MSyaXobJCU == true){MSyaXobJCU = false;}
      if(YejUWRzQPI == true){YejUWRzQPI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JRYFVAZCIY
{ 
  void yAVKLgJKXc()
  { 
      bool fkwCEMAubn = false;
      bool pLDRIKeuCX = false;
      bool jFOUDmTiAc = false;
      bool SDRdrGWghn = false;
      bool CiyxoLOMOj = false;
      bool guBatZVayR = false;
      bool sQtzVlsZZB = false;
      bool nxNNVAGRfr = false;
      bool XHUPwWBqjR = false;
      bool juhPuknzaC = false;
      bool RolMwihmEs = false;
      bool SEuGtlweDz = false;
      bool jCoHQrOxSk = false;
      bool MHqcZiUITM = false;
      bool oOlqyfAbVI = false;
      bool nJubSOzeuD = false;
      bool TkUTfKNRfL = false;
      bool QnKpJVQyIk = false;
      bool qlaJwDLOKK = false;
      bool ioMPsDsRKn = false;
      string AQrExBAWAI;
      string ZLwNBdiYSd;
      string OkTplxZnnI;
      string tjZrogarGX;
      string oTDuXxZjti;
      string mscDfPxCRA;
      string aLiqOpkEYT;
      string DqSuougYRo;
      string WptEVAHVLZ;
      string jXZGwckMfg;
      string MVKZfuagOk;
      string hYkcckRdVO;
      string iOrzjeQMyL;
      string JUrjcBeTXZ;
      string ZZHaqLlxdL;
      string KGpRyxdLpB;
      string eNiDaNfBAa;
      string GxGuoJHRHX;
      string rTimBCdale;
      string XSdWuLqDzd;
      if(AQrExBAWAI == MVKZfuagOk){fkwCEMAubn = true;}
      else if(MVKZfuagOk == AQrExBAWAI){RolMwihmEs = true;}
      if(ZLwNBdiYSd == hYkcckRdVO){pLDRIKeuCX = true;}
      else if(hYkcckRdVO == ZLwNBdiYSd){SEuGtlweDz = true;}
      if(OkTplxZnnI == iOrzjeQMyL){jFOUDmTiAc = true;}
      else if(iOrzjeQMyL == OkTplxZnnI){jCoHQrOxSk = true;}
      if(tjZrogarGX == JUrjcBeTXZ){SDRdrGWghn = true;}
      else if(JUrjcBeTXZ == tjZrogarGX){MHqcZiUITM = true;}
      if(oTDuXxZjti == ZZHaqLlxdL){CiyxoLOMOj = true;}
      else if(ZZHaqLlxdL == oTDuXxZjti){oOlqyfAbVI = true;}
      if(mscDfPxCRA == KGpRyxdLpB){guBatZVayR = true;}
      else if(KGpRyxdLpB == mscDfPxCRA){nJubSOzeuD = true;}
      if(aLiqOpkEYT == eNiDaNfBAa){sQtzVlsZZB = true;}
      else if(eNiDaNfBAa == aLiqOpkEYT){TkUTfKNRfL = true;}
      if(DqSuougYRo == GxGuoJHRHX){nxNNVAGRfr = true;}
      if(WptEVAHVLZ == rTimBCdale){XHUPwWBqjR = true;}
      if(jXZGwckMfg == XSdWuLqDzd){juhPuknzaC = true;}
      while(GxGuoJHRHX == DqSuougYRo){QnKpJVQyIk = true;}
      while(rTimBCdale == rTimBCdale){qlaJwDLOKK = true;}
      while(XSdWuLqDzd == XSdWuLqDzd){ioMPsDsRKn = true;}
      if(fkwCEMAubn == true){fkwCEMAubn = false;}
      if(pLDRIKeuCX == true){pLDRIKeuCX = false;}
      if(jFOUDmTiAc == true){jFOUDmTiAc = false;}
      if(SDRdrGWghn == true){SDRdrGWghn = false;}
      if(CiyxoLOMOj == true){CiyxoLOMOj = false;}
      if(guBatZVayR == true){guBatZVayR = false;}
      if(sQtzVlsZZB == true){sQtzVlsZZB = false;}
      if(nxNNVAGRfr == true){nxNNVAGRfr = false;}
      if(XHUPwWBqjR == true){XHUPwWBqjR = false;}
      if(juhPuknzaC == true){juhPuknzaC = false;}
      if(RolMwihmEs == true){RolMwihmEs = false;}
      if(SEuGtlweDz == true){SEuGtlweDz = false;}
      if(jCoHQrOxSk == true){jCoHQrOxSk = false;}
      if(MHqcZiUITM == true){MHqcZiUITM = false;}
      if(oOlqyfAbVI == true){oOlqyfAbVI = false;}
      if(nJubSOzeuD == true){nJubSOzeuD = false;}
      if(TkUTfKNRfL == true){TkUTfKNRfL = false;}
      if(QnKpJVQyIk == true){QnKpJVQyIk = false;}
      if(qlaJwDLOKK == true){qlaJwDLOKK = false;}
      if(ioMPsDsRKn == true){ioMPsDsRKn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDWXWYKEMW
{ 
  void taDzxGYoHW()
  { 
      bool ciimfMUtgJ = false;
      bool XOppndGBFP = false;
      bool JWoPjtzGzS = false;
      bool TiyszbZfEQ = false;
      bool ZZntkLHTee = false;
      bool dMdbOFsTDl = false;
      bool MNuOpnPwpL = false;
      bool DZxoojiudX = false;
      bool lfbUnGEWes = false;
      bool iGcSDLdZDw = false;
      bool wLcSaDPome = false;
      bool WxpfzflaZj = false;
      bool jrRxcxxekc = false;
      bool FJrgbaDIsj = false;
      bool pPjzVkQxSW = false;
      bool ZDzSMDsepd = false;
      bool GjDJZNFIDY = false;
      bool ccgpsTISaq = false;
      bool gALOCCKZTY = false;
      bool gXSPdGLZZI = false;
      string agynjYIxPT;
      string KVgKuojDrr;
      string PtbimUndzI;
      string zcljkahiAJ;
      string lkOUKKsDkt;
      string GuemfgFPBP;
      string kdxHThiwYT;
      string GACiGdeGYb;
      string aksFCExzEE;
      string UShkYHmHAb;
      string awdQmFrwgB;
      string BzpZnzkrEP;
      string jjrUynRQJy;
      string qXGwAdGbRw;
      string LBRCCVcIxY;
      string VuCkrpEISz;
      string malhKdssYJ;
      string rJZIDhSpSb;
      string LJTjcuUVEJ;
      string ZyJSIkOiqY;
      if(agynjYIxPT == awdQmFrwgB){ciimfMUtgJ = true;}
      else if(awdQmFrwgB == agynjYIxPT){wLcSaDPome = true;}
      if(KVgKuojDrr == BzpZnzkrEP){XOppndGBFP = true;}
      else if(BzpZnzkrEP == KVgKuojDrr){WxpfzflaZj = true;}
      if(PtbimUndzI == jjrUynRQJy){JWoPjtzGzS = true;}
      else if(jjrUynRQJy == PtbimUndzI){jrRxcxxekc = true;}
      if(zcljkahiAJ == qXGwAdGbRw){TiyszbZfEQ = true;}
      else if(qXGwAdGbRw == zcljkahiAJ){FJrgbaDIsj = true;}
      if(lkOUKKsDkt == LBRCCVcIxY){ZZntkLHTee = true;}
      else if(LBRCCVcIxY == lkOUKKsDkt){pPjzVkQxSW = true;}
      if(GuemfgFPBP == VuCkrpEISz){dMdbOFsTDl = true;}
      else if(VuCkrpEISz == GuemfgFPBP){ZDzSMDsepd = true;}
      if(kdxHThiwYT == malhKdssYJ){MNuOpnPwpL = true;}
      else if(malhKdssYJ == kdxHThiwYT){GjDJZNFIDY = true;}
      if(GACiGdeGYb == rJZIDhSpSb){DZxoojiudX = true;}
      if(aksFCExzEE == LJTjcuUVEJ){lfbUnGEWes = true;}
      if(UShkYHmHAb == ZyJSIkOiqY){iGcSDLdZDw = true;}
      while(rJZIDhSpSb == GACiGdeGYb){ccgpsTISaq = true;}
      while(LJTjcuUVEJ == LJTjcuUVEJ){gALOCCKZTY = true;}
      while(ZyJSIkOiqY == ZyJSIkOiqY){gXSPdGLZZI = true;}
      if(ciimfMUtgJ == true){ciimfMUtgJ = false;}
      if(XOppndGBFP == true){XOppndGBFP = false;}
      if(JWoPjtzGzS == true){JWoPjtzGzS = false;}
      if(TiyszbZfEQ == true){TiyszbZfEQ = false;}
      if(ZZntkLHTee == true){ZZntkLHTee = false;}
      if(dMdbOFsTDl == true){dMdbOFsTDl = false;}
      if(MNuOpnPwpL == true){MNuOpnPwpL = false;}
      if(DZxoojiudX == true){DZxoojiudX = false;}
      if(lfbUnGEWes == true){lfbUnGEWes = false;}
      if(iGcSDLdZDw == true){iGcSDLdZDw = false;}
      if(wLcSaDPome == true){wLcSaDPome = false;}
      if(WxpfzflaZj == true){WxpfzflaZj = false;}
      if(jrRxcxxekc == true){jrRxcxxekc = false;}
      if(FJrgbaDIsj == true){FJrgbaDIsj = false;}
      if(pPjzVkQxSW == true){pPjzVkQxSW = false;}
      if(ZDzSMDsepd == true){ZDzSMDsepd = false;}
      if(GjDJZNFIDY == true){GjDJZNFIDY = false;}
      if(ccgpsTISaq == true){ccgpsTISaq = false;}
      if(gALOCCKZTY == true){gALOCCKZTY = false;}
      if(gXSPdGLZZI == true){gXSPdGLZZI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHIMPYDPIT
{ 
  void ykYVlqTbrM()
  { 
      bool QmokeJcIYN = false;
      bool uEAMHgAArM = false;
      bool KyVaGnccLa = false;
      bool LMcKlKjhbL = false;
      bool mSbljGVlRn = false;
      bool MFQxxSRNdp = false;
      bool fAwyBiapZx = false;
      bool xSYfZqVipA = false;
      bool RqKXOFwfNT = false;
      bool sVDkflWdjB = false;
      bool efMUqtgkWF = false;
      bool whXdYooYiw = false;
      bool mubFEaOmzn = false;
      bool UryoUkdpgU = false;
      bool XKIIXKyZMp = false;
      bool wytnNjEHPP = false;
      bool ftkijEjiJm = false;
      bool KyqOXblSht = false;
      bool cnaIqWxJaj = false;
      bool gWaRodZZYT = false;
      string tikIXtbuGx;
      string BhjgqReLGF;
      string xYWtyeSjVw;
      string GGywTqAKQS;
      string TmIZErHtkd;
      string ujqGiULpKr;
      string aqZKqtinMA;
      string QUtnkJQxoG;
      string WYzrBVPqMz;
      string eJAXrcNyhK;
      string IThkMZoCVZ;
      string EOAEVCqhIU;
      string eqaNUGUVwH;
      string wROexDqOea;
      string gMVmtQIuCo;
      string lfpNeQrTPF;
      string FTGNclzVGR;
      string KbCgnRUmSD;
      string yYSGVQbBzf;
      string LWyZUMGIJH;
      if(tikIXtbuGx == IThkMZoCVZ){QmokeJcIYN = true;}
      else if(IThkMZoCVZ == tikIXtbuGx){efMUqtgkWF = true;}
      if(BhjgqReLGF == EOAEVCqhIU){uEAMHgAArM = true;}
      else if(EOAEVCqhIU == BhjgqReLGF){whXdYooYiw = true;}
      if(xYWtyeSjVw == eqaNUGUVwH){KyVaGnccLa = true;}
      else if(eqaNUGUVwH == xYWtyeSjVw){mubFEaOmzn = true;}
      if(GGywTqAKQS == wROexDqOea){LMcKlKjhbL = true;}
      else if(wROexDqOea == GGywTqAKQS){UryoUkdpgU = true;}
      if(TmIZErHtkd == gMVmtQIuCo){mSbljGVlRn = true;}
      else if(gMVmtQIuCo == TmIZErHtkd){XKIIXKyZMp = true;}
      if(ujqGiULpKr == lfpNeQrTPF){MFQxxSRNdp = true;}
      else if(lfpNeQrTPF == ujqGiULpKr){wytnNjEHPP = true;}
      if(aqZKqtinMA == FTGNclzVGR){fAwyBiapZx = true;}
      else if(FTGNclzVGR == aqZKqtinMA){ftkijEjiJm = true;}
      if(QUtnkJQxoG == KbCgnRUmSD){xSYfZqVipA = true;}
      if(WYzrBVPqMz == yYSGVQbBzf){RqKXOFwfNT = true;}
      if(eJAXrcNyhK == LWyZUMGIJH){sVDkflWdjB = true;}
      while(KbCgnRUmSD == QUtnkJQxoG){KyqOXblSht = true;}
      while(yYSGVQbBzf == yYSGVQbBzf){cnaIqWxJaj = true;}
      while(LWyZUMGIJH == LWyZUMGIJH){gWaRodZZYT = true;}
      if(QmokeJcIYN == true){QmokeJcIYN = false;}
      if(uEAMHgAArM == true){uEAMHgAArM = false;}
      if(KyVaGnccLa == true){KyVaGnccLa = false;}
      if(LMcKlKjhbL == true){LMcKlKjhbL = false;}
      if(mSbljGVlRn == true){mSbljGVlRn = false;}
      if(MFQxxSRNdp == true){MFQxxSRNdp = false;}
      if(fAwyBiapZx == true){fAwyBiapZx = false;}
      if(xSYfZqVipA == true){xSYfZqVipA = false;}
      if(RqKXOFwfNT == true){RqKXOFwfNT = false;}
      if(sVDkflWdjB == true){sVDkflWdjB = false;}
      if(efMUqtgkWF == true){efMUqtgkWF = false;}
      if(whXdYooYiw == true){whXdYooYiw = false;}
      if(mubFEaOmzn == true){mubFEaOmzn = false;}
      if(UryoUkdpgU == true){UryoUkdpgU = false;}
      if(XKIIXKyZMp == true){XKIIXKyZMp = false;}
      if(wytnNjEHPP == true){wytnNjEHPP = false;}
      if(ftkijEjiJm == true){ftkijEjiJm = false;}
      if(KyqOXblSht == true){KyqOXblSht = false;}
      if(cnaIqWxJaj == true){cnaIqWxJaj = false;}
      if(gWaRodZZYT == true){gWaRodZZYT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMWXRXVYXB
{ 
  void hNZzDHKxdi()
  { 
      bool pkPLlJYDXi = false;
      bool slMuDFefOB = false;
      bool ypyiXakFQx = false;
      bool WxkLVLQkRY = false;
      bool KLdzkMQZqz = false;
      bool XmgfrzmfmL = false;
      bool YTlaLwAAZq = false;
      bool otOpplLzxL = false;
      bool JKORZjQESV = false;
      bool YjyFAqYDmo = false;
      bool MPzzKcXqpF = false;
      bool mmibCNFUBb = false;
      bool fwhESEwIpz = false;
      bool NILHzsKOHw = false;
      bool LYONhkBVDl = false;
      bool lEBLJPhugG = false;
      bool gPBqrdabcI = false;
      bool CpNFQGhUVg = false;
      bool CZEDMJHAxi = false;
      bool LOhBOuXWUE = false;
      string BJhLxExEDN;
      string ZGdFFqySbM;
      string zSIUoewhzC;
      string qwfgpFUebt;
      string OXobuyljCn;
      string OAMrUhBNWS;
      string IPFBWcZxOz;
      string WSpgxadfYp;
      string rMfLmpjnLI;
      string EGIJlzSnFS;
      string YoUCQwJfus;
      string DUnfZuitNf;
      string slkGuPJguy;
      string IpaGRDqctq;
      string fDrSEiScip;
      string PYZYYmEOHA;
      string lckwkNsgNW;
      string DGzVApsSBL;
      string xfxEhjPChe;
      string ycVtFDSugp;
      if(BJhLxExEDN == YoUCQwJfus){pkPLlJYDXi = true;}
      else if(YoUCQwJfus == BJhLxExEDN){MPzzKcXqpF = true;}
      if(ZGdFFqySbM == DUnfZuitNf){slMuDFefOB = true;}
      else if(DUnfZuitNf == ZGdFFqySbM){mmibCNFUBb = true;}
      if(zSIUoewhzC == slkGuPJguy){ypyiXakFQx = true;}
      else if(slkGuPJguy == zSIUoewhzC){fwhESEwIpz = true;}
      if(qwfgpFUebt == IpaGRDqctq){WxkLVLQkRY = true;}
      else if(IpaGRDqctq == qwfgpFUebt){NILHzsKOHw = true;}
      if(OXobuyljCn == fDrSEiScip){KLdzkMQZqz = true;}
      else if(fDrSEiScip == OXobuyljCn){LYONhkBVDl = true;}
      if(OAMrUhBNWS == PYZYYmEOHA){XmgfrzmfmL = true;}
      else if(PYZYYmEOHA == OAMrUhBNWS){lEBLJPhugG = true;}
      if(IPFBWcZxOz == lckwkNsgNW){YTlaLwAAZq = true;}
      else if(lckwkNsgNW == IPFBWcZxOz){gPBqrdabcI = true;}
      if(WSpgxadfYp == DGzVApsSBL){otOpplLzxL = true;}
      if(rMfLmpjnLI == xfxEhjPChe){JKORZjQESV = true;}
      if(EGIJlzSnFS == ycVtFDSugp){YjyFAqYDmo = true;}
      while(DGzVApsSBL == WSpgxadfYp){CpNFQGhUVg = true;}
      while(xfxEhjPChe == xfxEhjPChe){CZEDMJHAxi = true;}
      while(ycVtFDSugp == ycVtFDSugp){LOhBOuXWUE = true;}
      if(pkPLlJYDXi == true){pkPLlJYDXi = false;}
      if(slMuDFefOB == true){slMuDFefOB = false;}
      if(ypyiXakFQx == true){ypyiXakFQx = false;}
      if(WxkLVLQkRY == true){WxkLVLQkRY = false;}
      if(KLdzkMQZqz == true){KLdzkMQZqz = false;}
      if(XmgfrzmfmL == true){XmgfrzmfmL = false;}
      if(YTlaLwAAZq == true){YTlaLwAAZq = false;}
      if(otOpplLzxL == true){otOpplLzxL = false;}
      if(JKORZjQESV == true){JKORZjQESV = false;}
      if(YjyFAqYDmo == true){YjyFAqYDmo = false;}
      if(MPzzKcXqpF == true){MPzzKcXqpF = false;}
      if(mmibCNFUBb == true){mmibCNFUBb = false;}
      if(fwhESEwIpz == true){fwhESEwIpz = false;}
      if(NILHzsKOHw == true){NILHzsKOHw = false;}
      if(LYONhkBVDl == true){LYONhkBVDl = false;}
      if(lEBLJPhugG == true){lEBLJPhugG = false;}
      if(gPBqrdabcI == true){gPBqrdabcI = false;}
      if(CpNFQGhUVg == true){CpNFQGhUVg = false;}
      if(CZEDMJHAxi == true){CZEDMJHAxi = false;}
      if(LOhBOuXWUE == true){LOhBOuXWUE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMWDRSUSSQ
{ 
  void BmgEKwEmFU()
  { 
      bool pOUiiZxiiQ = false;
      bool ulejQjBIQA = false;
      bool yfJoFQsyXz = false;
      bool woSJBUOQAo = false;
      bool JtXpGFCGeP = false;
      bool RknYhJEecS = false;
      bool fyLjUFTVhu = false;
      bool UkIbpDHSiz = false;
      bool OmTHhKBtar = false;
      bool PimgILinVA = false;
      bool lfXjtgcLhd = false;
      bool ClwcEseDBJ = false;
      bool EYtpekxaTe = false;
      bool USxhMhOjNA = false;
      bool hoMwpdmJcO = false;
      bool femLuNkhEI = false;
      bool iCrDJioNQW = false;
      bool eupAbOLyAA = false;
      bool ymxEyofklz = false;
      bool wgeEQfxImG = false;
      string loikgVkyHL;
      string fqgUhMafDP;
      string KxlGslAQyj;
      string TGaWGgmlxD;
      string ffSiIjMfzn;
      string DQJmkoCcru;
      string UTzWqYQJNA;
      string YoizjeeDxJ;
      string ZURKgCwmlR;
      string dKtChLfuqi;
      string SCRyOOhJDF;
      string JzehUACopn;
      string bdXwWOugRX;
      string yiLOqWCSuS;
      string UljfHdeLgg;
      string JqFDGodUbA;
      string SBreHanQqy;
      string yjtWTpsror;
      string jizjOHcHHB;
      string rgpuzTsEYf;
      if(loikgVkyHL == SCRyOOhJDF){pOUiiZxiiQ = true;}
      else if(SCRyOOhJDF == loikgVkyHL){lfXjtgcLhd = true;}
      if(fqgUhMafDP == JzehUACopn){ulejQjBIQA = true;}
      else if(JzehUACopn == fqgUhMafDP){ClwcEseDBJ = true;}
      if(KxlGslAQyj == bdXwWOugRX){yfJoFQsyXz = true;}
      else if(bdXwWOugRX == KxlGslAQyj){EYtpekxaTe = true;}
      if(TGaWGgmlxD == yiLOqWCSuS){woSJBUOQAo = true;}
      else if(yiLOqWCSuS == TGaWGgmlxD){USxhMhOjNA = true;}
      if(ffSiIjMfzn == UljfHdeLgg){JtXpGFCGeP = true;}
      else if(UljfHdeLgg == ffSiIjMfzn){hoMwpdmJcO = true;}
      if(DQJmkoCcru == JqFDGodUbA){RknYhJEecS = true;}
      else if(JqFDGodUbA == DQJmkoCcru){femLuNkhEI = true;}
      if(UTzWqYQJNA == SBreHanQqy){fyLjUFTVhu = true;}
      else if(SBreHanQqy == UTzWqYQJNA){iCrDJioNQW = true;}
      if(YoizjeeDxJ == yjtWTpsror){UkIbpDHSiz = true;}
      if(ZURKgCwmlR == jizjOHcHHB){OmTHhKBtar = true;}
      if(dKtChLfuqi == rgpuzTsEYf){PimgILinVA = true;}
      while(yjtWTpsror == YoizjeeDxJ){eupAbOLyAA = true;}
      while(jizjOHcHHB == jizjOHcHHB){ymxEyofklz = true;}
      while(rgpuzTsEYf == rgpuzTsEYf){wgeEQfxImG = true;}
      if(pOUiiZxiiQ == true){pOUiiZxiiQ = false;}
      if(ulejQjBIQA == true){ulejQjBIQA = false;}
      if(yfJoFQsyXz == true){yfJoFQsyXz = false;}
      if(woSJBUOQAo == true){woSJBUOQAo = false;}
      if(JtXpGFCGeP == true){JtXpGFCGeP = false;}
      if(RknYhJEecS == true){RknYhJEecS = false;}
      if(fyLjUFTVhu == true){fyLjUFTVhu = false;}
      if(UkIbpDHSiz == true){UkIbpDHSiz = false;}
      if(OmTHhKBtar == true){OmTHhKBtar = false;}
      if(PimgILinVA == true){PimgILinVA = false;}
      if(lfXjtgcLhd == true){lfXjtgcLhd = false;}
      if(ClwcEseDBJ == true){ClwcEseDBJ = false;}
      if(EYtpekxaTe == true){EYtpekxaTe = false;}
      if(USxhMhOjNA == true){USxhMhOjNA = false;}
      if(hoMwpdmJcO == true){hoMwpdmJcO = false;}
      if(femLuNkhEI == true){femLuNkhEI = false;}
      if(iCrDJioNQW == true){iCrDJioNQW = false;}
      if(eupAbOLyAA == true){eupAbOLyAA = false;}
      if(ymxEyofklz == true){ymxEyofklz = false;}
      if(wgeEQfxImG == true){wgeEQfxImG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AIGXVFQZXV
{ 
  void LqtNnOieYX()
  { 
      bool PQBPapyKfh = false;
      bool tSwwNtPiTY = false;
      bool ZLlUCLhrxP = false;
      bool qycNJflFEf = false;
      bool PZEKImImLO = false;
      bool QMqyOEegNO = false;
      bool HGMQpuphmh = false;
      bool HKdnIAGaMO = false;
      bool CtfizeHdyF = false;
      bool AFroXIMnTM = false;
      bool waAdHFhCpO = false;
      bool xDUyLMZdQK = false;
      bool mMiggCSnQz = false;
      bool mSHzSbtBas = false;
      bool wFmjIxksdK = false;
      bool iiWIZjqSxF = false;
      bool mskpbdwUfi = false;
      bool SYCXOhYzYj = false;
      bool QYKGQDuyZh = false;
      bool kaEVFDTxHd = false;
      string ETHTzFPWnh;
      string DbkKqoUfYa;
      string TXGkSRbdaA;
      string XNwytjIDjp;
      string RREBGuQUPj;
      string MaTbUfNVAg;
      string clumKpfmQH;
      string fQwiJCTEdW;
      string BHNpnwtTcN;
      string VmCDMfVQqQ;
      string PcDHEwejSS;
      string MJqdfUXEzO;
      string wLKDksNsWc;
      string fCNNGXEGlr;
      string RJBKALuYWq;
      string HRRbUESzVL;
      string hkNomKwdWH;
      string QRSHwmKADZ;
      string xnVeVOjkrC;
      string FEjZJfuLXo;
      if(ETHTzFPWnh == PcDHEwejSS){PQBPapyKfh = true;}
      else if(PcDHEwejSS == ETHTzFPWnh){waAdHFhCpO = true;}
      if(DbkKqoUfYa == MJqdfUXEzO){tSwwNtPiTY = true;}
      else if(MJqdfUXEzO == DbkKqoUfYa){xDUyLMZdQK = true;}
      if(TXGkSRbdaA == wLKDksNsWc){ZLlUCLhrxP = true;}
      else if(wLKDksNsWc == TXGkSRbdaA){mMiggCSnQz = true;}
      if(XNwytjIDjp == fCNNGXEGlr){qycNJflFEf = true;}
      else if(fCNNGXEGlr == XNwytjIDjp){mSHzSbtBas = true;}
      if(RREBGuQUPj == RJBKALuYWq){PZEKImImLO = true;}
      else if(RJBKALuYWq == RREBGuQUPj){wFmjIxksdK = true;}
      if(MaTbUfNVAg == HRRbUESzVL){QMqyOEegNO = true;}
      else if(HRRbUESzVL == MaTbUfNVAg){iiWIZjqSxF = true;}
      if(clumKpfmQH == hkNomKwdWH){HGMQpuphmh = true;}
      else if(hkNomKwdWH == clumKpfmQH){mskpbdwUfi = true;}
      if(fQwiJCTEdW == QRSHwmKADZ){HKdnIAGaMO = true;}
      if(BHNpnwtTcN == xnVeVOjkrC){CtfizeHdyF = true;}
      if(VmCDMfVQqQ == FEjZJfuLXo){AFroXIMnTM = true;}
      while(QRSHwmKADZ == fQwiJCTEdW){SYCXOhYzYj = true;}
      while(xnVeVOjkrC == xnVeVOjkrC){QYKGQDuyZh = true;}
      while(FEjZJfuLXo == FEjZJfuLXo){kaEVFDTxHd = true;}
      if(PQBPapyKfh == true){PQBPapyKfh = false;}
      if(tSwwNtPiTY == true){tSwwNtPiTY = false;}
      if(ZLlUCLhrxP == true){ZLlUCLhrxP = false;}
      if(qycNJflFEf == true){qycNJflFEf = false;}
      if(PZEKImImLO == true){PZEKImImLO = false;}
      if(QMqyOEegNO == true){QMqyOEegNO = false;}
      if(HGMQpuphmh == true){HGMQpuphmh = false;}
      if(HKdnIAGaMO == true){HKdnIAGaMO = false;}
      if(CtfizeHdyF == true){CtfizeHdyF = false;}
      if(AFroXIMnTM == true){AFroXIMnTM = false;}
      if(waAdHFhCpO == true){waAdHFhCpO = false;}
      if(xDUyLMZdQK == true){xDUyLMZdQK = false;}
      if(mMiggCSnQz == true){mMiggCSnQz = false;}
      if(mSHzSbtBas == true){mSHzSbtBas = false;}
      if(wFmjIxksdK == true){wFmjIxksdK = false;}
      if(iiWIZjqSxF == true){iiWIZjqSxF = false;}
      if(mskpbdwUfi == true){mskpbdwUfi = false;}
      if(SYCXOhYzYj == true){SYCXOhYzYj = false;}
      if(QYKGQDuyZh == true){QYKGQDuyZh = false;}
      if(kaEVFDTxHd == true){kaEVFDTxHd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQBMSKRKZC
{ 
  void GVcXsrssIi()
  { 
      bool tPBWGrmEnE = false;
      bool dRKqmfYVeq = false;
      bool NbLXMQHfzt = false;
      bool aHrdrEiBPN = false;
      bool kDthohakrM = false;
      bool LhbJoRDdJo = false;
      bool kGFtdWYfzh = false;
      bool wWFRGKhdie = false;
      bool pWmlhsehoZ = false;
      bool BFrZcdxAER = false;
      bool ItkJPobJDd = false;
      bool jYteyNTSLk = false;
      bool qpqYgpeeoc = false;
      bool MhZQVwkdWs = false;
      bool QVeKpbKMaO = false;
      bool JenTZRCMcY = false;
      bool KxTaQBzcJC = false;
      bool cpwSTVLgiF = false;
      bool fSDaSgsGqD = false;
      bool sXAxiTBDsn = false;
      string UCkoUYOQZT;
      string BnSXMHkmIa;
      string wwMiZNVAnX;
      string RIYIUFmKRp;
      string daygCOfyaJ;
      string UbpOGXpCOH;
      string CNcCBrPKCG;
      string TZUSwUyffK;
      string gXZdCoSJBx;
      string PkwKmPyueJ;
      string zUuTptHWRk;
      string YKVDZdnzzM;
      string ZGJFqidJeg;
      string WDAWLLbFmI;
      string hurPYEOskI;
      string ayuSirLpcH;
      string QxqkOVKzqN;
      string CiLqdeOsfl;
      string TkYVFXHhmS;
      string AkbfrjDGAC;
      if(UCkoUYOQZT == zUuTptHWRk){tPBWGrmEnE = true;}
      else if(zUuTptHWRk == UCkoUYOQZT){ItkJPobJDd = true;}
      if(BnSXMHkmIa == YKVDZdnzzM){dRKqmfYVeq = true;}
      else if(YKVDZdnzzM == BnSXMHkmIa){jYteyNTSLk = true;}
      if(wwMiZNVAnX == ZGJFqidJeg){NbLXMQHfzt = true;}
      else if(ZGJFqidJeg == wwMiZNVAnX){qpqYgpeeoc = true;}
      if(RIYIUFmKRp == WDAWLLbFmI){aHrdrEiBPN = true;}
      else if(WDAWLLbFmI == RIYIUFmKRp){MhZQVwkdWs = true;}
      if(daygCOfyaJ == hurPYEOskI){kDthohakrM = true;}
      else if(hurPYEOskI == daygCOfyaJ){QVeKpbKMaO = true;}
      if(UbpOGXpCOH == ayuSirLpcH){LhbJoRDdJo = true;}
      else if(ayuSirLpcH == UbpOGXpCOH){JenTZRCMcY = true;}
      if(CNcCBrPKCG == QxqkOVKzqN){kGFtdWYfzh = true;}
      else if(QxqkOVKzqN == CNcCBrPKCG){KxTaQBzcJC = true;}
      if(TZUSwUyffK == CiLqdeOsfl){wWFRGKhdie = true;}
      if(gXZdCoSJBx == TkYVFXHhmS){pWmlhsehoZ = true;}
      if(PkwKmPyueJ == AkbfrjDGAC){BFrZcdxAER = true;}
      while(CiLqdeOsfl == TZUSwUyffK){cpwSTVLgiF = true;}
      while(TkYVFXHhmS == TkYVFXHhmS){fSDaSgsGqD = true;}
      while(AkbfrjDGAC == AkbfrjDGAC){sXAxiTBDsn = true;}
      if(tPBWGrmEnE == true){tPBWGrmEnE = false;}
      if(dRKqmfYVeq == true){dRKqmfYVeq = false;}
      if(NbLXMQHfzt == true){NbLXMQHfzt = false;}
      if(aHrdrEiBPN == true){aHrdrEiBPN = false;}
      if(kDthohakrM == true){kDthohakrM = false;}
      if(LhbJoRDdJo == true){LhbJoRDdJo = false;}
      if(kGFtdWYfzh == true){kGFtdWYfzh = false;}
      if(wWFRGKhdie == true){wWFRGKhdie = false;}
      if(pWmlhsehoZ == true){pWmlhsehoZ = false;}
      if(BFrZcdxAER == true){BFrZcdxAER = false;}
      if(ItkJPobJDd == true){ItkJPobJDd = false;}
      if(jYteyNTSLk == true){jYteyNTSLk = false;}
      if(qpqYgpeeoc == true){qpqYgpeeoc = false;}
      if(MhZQVwkdWs == true){MhZQVwkdWs = false;}
      if(QVeKpbKMaO == true){QVeKpbKMaO = false;}
      if(JenTZRCMcY == true){JenTZRCMcY = false;}
      if(KxTaQBzcJC == true){KxTaQBzcJC = false;}
      if(cpwSTVLgiF == true){cpwSTVLgiF = false;}
      if(fSDaSgsGqD == true){fSDaSgsGqD = false;}
      if(sXAxiTBDsn == true){sXAxiTBDsn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEYXUGSDKS
{ 
  void juHtOPnuGF()
  { 
      bool aKqyHJKczc = false;
      bool zzzKqwHVoZ = false;
      bool SYEeCCXgZf = false;
      bool BsMeUrhSwS = false;
      bool RtOwwTpUdX = false;
      bool hfzpACGLwE = false;
      bool lcDTbFmTpy = false;
      bool OoZVIXJIih = false;
      bool MDDCxUtVeS = false;
      bool lVWqgnquTp = false;
      bool fWdeIsGchb = false;
      bool rycNriZAVG = false;
      bool LRoXMsShoU = false;
      bool gOnsBoYXtE = false;
      bool ORnCZnrIyx = false;
      bool OqYNeOhFSO = false;
      bool ZXmMucKjLD = false;
      bool JCFRqtdlxY = false;
      bool AJjrGppZOm = false;
      bool HTEedqdaGw = false;
      string zWXdBZTjVc;
      string RVosCsmKqr;
      string eGIVZJBYKf;
      string QbQeoCbYhF;
      string yGARCakJSG;
      string boSBRsOCDr;
      string XuYpMpEKEz;
      string RNclsXGpSz;
      string XrFEEaJPNw;
      string nYVpgDhJFM;
      string WaFSnNMfIs;
      string mXjDTfpTkk;
      string foxHLsqmFp;
      string pwjFcxmlQp;
      string OcGTJPoRVA;
      string MNXUfgcxHu;
      string VYaRCpndaW;
      string rDDtVDhcyw;
      string DYREcbXOYu;
      string ToeVUpCnQS;
      if(zWXdBZTjVc == WaFSnNMfIs){aKqyHJKczc = true;}
      else if(WaFSnNMfIs == zWXdBZTjVc){fWdeIsGchb = true;}
      if(RVosCsmKqr == mXjDTfpTkk){zzzKqwHVoZ = true;}
      else if(mXjDTfpTkk == RVosCsmKqr){rycNriZAVG = true;}
      if(eGIVZJBYKf == foxHLsqmFp){SYEeCCXgZf = true;}
      else if(foxHLsqmFp == eGIVZJBYKf){LRoXMsShoU = true;}
      if(QbQeoCbYhF == pwjFcxmlQp){BsMeUrhSwS = true;}
      else if(pwjFcxmlQp == QbQeoCbYhF){gOnsBoYXtE = true;}
      if(yGARCakJSG == OcGTJPoRVA){RtOwwTpUdX = true;}
      else if(OcGTJPoRVA == yGARCakJSG){ORnCZnrIyx = true;}
      if(boSBRsOCDr == MNXUfgcxHu){hfzpACGLwE = true;}
      else if(MNXUfgcxHu == boSBRsOCDr){OqYNeOhFSO = true;}
      if(XuYpMpEKEz == VYaRCpndaW){lcDTbFmTpy = true;}
      else if(VYaRCpndaW == XuYpMpEKEz){ZXmMucKjLD = true;}
      if(RNclsXGpSz == rDDtVDhcyw){OoZVIXJIih = true;}
      if(XrFEEaJPNw == DYREcbXOYu){MDDCxUtVeS = true;}
      if(nYVpgDhJFM == ToeVUpCnQS){lVWqgnquTp = true;}
      while(rDDtVDhcyw == RNclsXGpSz){JCFRqtdlxY = true;}
      while(DYREcbXOYu == DYREcbXOYu){AJjrGppZOm = true;}
      while(ToeVUpCnQS == ToeVUpCnQS){HTEedqdaGw = true;}
      if(aKqyHJKczc == true){aKqyHJKczc = false;}
      if(zzzKqwHVoZ == true){zzzKqwHVoZ = false;}
      if(SYEeCCXgZf == true){SYEeCCXgZf = false;}
      if(BsMeUrhSwS == true){BsMeUrhSwS = false;}
      if(RtOwwTpUdX == true){RtOwwTpUdX = false;}
      if(hfzpACGLwE == true){hfzpACGLwE = false;}
      if(lcDTbFmTpy == true){lcDTbFmTpy = false;}
      if(OoZVIXJIih == true){OoZVIXJIih = false;}
      if(MDDCxUtVeS == true){MDDCxUtVeS = false;}
      if(lVWqgnquTp == true){lVWqgnquTp = false;}
      if(fWdeIsGchb == true){fWdeIsGchb = false;}
      if(rycNriZAVG == true){rycNriZAVG = false;}
      if(LRoXMsShoU == true){LRoXMsShoU = false;}
      if(gOnsBoYXtE == true){gOnsBoYXtE = false;}
      if(ORnCZnrIyx == true){ORnCZnrIyx = false;}
      if(OqYNeOhFSO == true){OqYNeOhFSO = false;}
      if(ZXmMucKjLD == true){ZXmMucKjLD = false;}
      if(JCFRqtdlxY == true){JCFRqtdlxY = false;}
      if(AJjrGppZOm == true){AJjrGppZOm = false;}
      if(HTEedqdaGw == true){HTEedqdaGw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVMRDFEXOG
{ 
  void UsuJsGSymw()
  { 
      bool cPqwOMDTby = false;
      bool bijuCorbGl = false;
      bool hLQLEdBYZD = false;
      bool dhsHDaRplx = false;
      bool KrVkDKbmbZ = false;
      bool QURGQRyerk = false;
      bool LesYTsobqb = false;
      bool XCoJapofIs = false;
      bool BNwzlJQlql = false;
      bool blyBkfywRJ = false;
      bool VzwABOeHfZ = false;
      bool bSWyjyitmJ = false;
      bool bDkFzlDnYu = false;
      bool qrNyXBQwxX = false;
      bool eIFQJIPAQm = false;
      bool xEJHgRNqAP = false;
      bool KpikiiEXZh = false;
      bool gmwOeTxUuq = false;
      bool VDWkxmiGRG = false;
      bool mZuhMnZUgZ = false;
      string tFBnrbEuYP;
      string DAmORoPblq;
      string hxcNnOqEyT;
      string JumpFNLmkh;
      string qeQygsyyzb;
      string REmXZwcnzc;
      string kAwEGIMxID;
      string ccpDzDgefu;
      string QrFVCEIOQI;
      string jXmHxqhLqY;
      string gBpuynOiYV;
      string PxHEMrtaCC;
      string zxfzTFphGH;
      string VUmHNOCKXN;
      string oYptsmPhuE;
      string xGIoYiUpbr;
      string yfcRAtJApy;
      string pjDoMaHlGf;
      string pImBKOLyie;
      string sMiePJwYsy;
      if(tFBnrbEuYP == gBpuynOiYV){cPqwOMDTby = true;}
      else if(gBpuynOiYV == tFBnrbEuYP){VzwABOeHfZ = true;}
      if(DAmORoPblq == PxHEMrtaCC){bijuCorbGl = true;}
      else if(PxHEMrtaCC == DAmORoPblq){bSWyjyitmJ = true;}
      if(hxcNnOqEyT == zxfzTFphGH){hLQLEdBYZD = true;}
      else if(zxfzTFphGH == hxcNnOqEyT){bDkFzlDnYu = true;}
      if(JumpFNLmkh == VUmHNOCKXN){dhsHDaRplx = true;}
      else if(VUmHNOCKXN == JumpFNLmkh){qrNyXBQwxX = true;}
      if(qeQygsyyzb == oYptsmPhuE){KrVkDKbmbZ = true;}
      else if(oYptsmPhuE == qeQygsyyzb){eIFQJIPAQm = true;}
      if(REmXZwcnzc == xGIoYiUpbr){QURGQRyerk = true;}
      else if(xGIoYiUpbr == REmXZwcnzc){xEJHgRNqAP = true;}
      if(kAwEGIMxID == yfcRAtJApy){LesYTsobqb = true;}
      else if(yfcRAtJApy == kAwEGIMxID){KpikiiEXZh = true;}
      if(ccpDzDgefu == pjDoMaHlGf){XCoJapofIs = true;}
      if(QrFVCEIOQI == pImBKOLyie){BNwzlJQlql = true;}
      if(jXmHxqhLqY == sMiePJwYsy){blyBkfywRJ = true;}
      while(pjDoMaHlGf == ccpDzDgefu){gmwOeTxUuq = true;}
      while(pImBKOLyie == pImBKOLyie){VDWkxmiGRG = true;}
      while(sMiePJwYsy == sMiePJwYsy){mZuhMnZUgZ = true;}
      if(cPqwOMDTby == true){cPqwOMDTby = false;}
      if(bijuCorbGl == true){bijuCorbGl = false;}
      if(hLQLEdBYZD == true){hLQLEdBYZD = false;}
      if(dhsHDaRplx == true){dhsHDaRplx = false;}
      if(KrVkDKbmbZ == true){KrVkDKbmbZ = false;}
      if(QURGQRyerk == true){QURGQRyerk = false;}
      if(LesYTsobqb == true){LesYTsobqb = false;}
      if(XCoJapofIs == true){XCoJapofIs = false;}
      if(BNwzlJQlql == true){BNwzlJQlql = false;}
      if(blyBkfywRJ == true){blyBkfywRJ = false;}
      if(VzwABOeHfZ == true){VzwABOeHfZ = false;}
      if(bSWyjyitmJ == true){bSWyjyitmJ = false;}
      if(bDkFzlDnYu == true){bDkFzlDnYu = false;}
      if(qrNyXBQwxX == true){qrNyXBQwxX = false;}
      if(eIFQJIPAQm == true){eIFQJIPAQm = false;}
      if(xEJHgRNqAP == true){xEJHgRNqAP = false;}
      if(KpikiiEXZh == true){KpikiiEXZh = false;}
      if(gmwOeTxUuq == true){gmwOeTxUuq = false;}
      if(VDWkxmiGRG == true){VDWkxmiGRG = false;}
      if(mZuhMnZUgZ == true){mZuhMnZUgZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFTDYFIVMG
{ 
  void XyHebTwuob()
  { 
      bool RclXFDdwxP = false;
      bool DUfNCrGfex = false;
      bool MUNqqUCWzY = false;
      bool SGCKWySiGf = false;
      bool iOUDLYfHrt = false;
      bool nEHeMxOtfk = false;
      bool AHwXwwSVqD = false;
      bool YWZyOyzJeS = false;
      bool nteEkNzXyY = false;
      bool iXDVeaRwHP = false;
      bool GKPoVQeIQO = false;
      bool xEONwFcrmi = false;
      bool wuXRTBTDSm = false;
      bool fDCPLddoiT = false;
      bool iqGibdJoYY = false;
      bool yZJYSLlyUU = false;
      bool xaochtCyBR = false;
      bool amITAFnnpo = false;
      bool rddtnGsdxA = false;
      bool qfUOVHBdBg = false;
      string KgoheCzEYi;
      string HJnXmAkccb;
      string NxjjOsShYb;
      string THmSbVidZg;
      string pRAIzMkrNh;
      string zgmLNNwETl;
      string jRfxOAVUuR;
      string RGDwkuwbkB;
      string IZUpblTbEO;
      string YeJmxYlDsz;
      string pPxuQsdqaS;
      string QUTRdJxpUb;
      string ftQgsmwPzL;
      string IshlLscYYi;
      string IcBlxEKrIm;
      string buhQSwzPCd;
      string wNrOJXlgGk;
      string gXRlTDsdjn;
      string bEHLjMKRSO;
      string sMVtltklbY;
      if(KgoheCzEYi == pPxuQsdqaS){RclXFDdwxP = true;}
      else if(pPxuQsdqaS == KgoheCzEYi){GKPoVQeIQO = true;}
      if(HJnXmAkccb == QUTRdJxpUb){DUfNCrGfex = true;}
      else if(QUTRdJxpUb == HJnXmAkccb){xEONwFcrmi = true;}
      if(NxjjOsShYb == ftQgsmwPzL){MUNqqUCWzY = true;}
      else if(ftQgsmwPzL == NxjjOsShYb){wuXRTBTDSm = true;}
      if(THmSbVidZg == IshlLscYYi){SGCKWySiGf = true;}
      else if(IshlLscYYi == THmSbVidZg){fDCPLddoiT = true;}
      if(pRAIzMkrNh == IcBlxEKrIm){iOUDLYfHrt = true;}
      else if(IcBlxEKrIm == pRAIzMkrNh){iqGibdJoYY = true;}
      if(zgmLNNwETl == buhQSwzPCd){nEHeMxOtfk = true;}
      else if(buhQSwzPCd == zgmLNNwETl){yZJYSLlyUU = true;}
      if(jRfxOAVUuR == wNrOJXlgGk){AHwXwwSVqD = true;}
      else if(wNrOJXlgGk == jRfxOAVUuR){xaochtCyBR = true;}
      if(RGDwkuwbkB == gXRlTDsdjn){YWZyOyzJeS = true;}
      if(IZUpblTbEO == bEHLjMKRSO){nteEkNzXyY = true;}
      if(YeJmxYlDsz == sMVtltklbY){iXDVeaRwHP = true;}
      while(gXRlTDsdjn == RGDwkuwbkB){amITAFnnpo = true;}
      while(bEHLjMKRSO == bEHLjMKRSO){rddtnGsdxA = true;}
      while(sMVtltklbY == sMVtltklbY){qfUOVHBdBg = true;}
      if(RclXFDdwxP == true){RclXFDdwxP = false;}
      if(DUfNCrGfex == true){DUfNCrGfex = false;}
      if(MUNqqUCWzY == true){MUNqqUCWzY = false;}
      if(SGCKWySiGf == true){SGCKWySiGf = false;}
      if(iOUDLYfHrt == true){iOUDLYfHrt = false;}
      if(nEHeMxOtfk == true){nEHeMxOtfk = false;}
      if(AHwXwwSVqD == true){AHwXwwSVqD = false;}
      if(YWZyOyzJeS == true){YWZyOyzJeS = false;}
      if(nteEkNzXyY == true){nteEkNzXyY = false;}
      if(iXDVeaRwHP == true){iXDVeaRwHP = false;}
      if(GKPoVQeIQO == true){GKPoVQeIQO = false;}
      if(xEONwFcrmi == true){xEONwFcrmi = false;}
      if(wuXRTBTDSm == true){wuXRTBTDSm = false;}
      if(fDCPLddoiT == true){fDCPLddoiT = false;}
      if(iqGibdJoYY == true){iqGibdJoYY = false;}
      if(yZJYSLlyUU == true){yZJYSLlyUU = false;}
      if(xaochtCyBR == true){xaochtCyBR = false;}
      if(amITAFnnpo == true){amITAFnnpo = false;}
      if(rddtnGsdxA == true){rddtnGsdxA = false;}
      if(qfUOVHBdBg == true){qfUOVHBdBg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XFLZWNELGX
{ 
  void xJIIpYssfK()
  { 
      bool BMccFxbNmz = false;
      bool GkGkrDMtyV = false;
      bool QZuBtPspcm = false;
      bool assssPTuHy = false;
      bool jVLhkMkqzf = false;
      bool qPHmdaQbip = false;
      bool DlkAYNrMqc = false;
      bool jRlzkuONPh = false;
      bool dBpwuKkFPS = false;
      bool yqLRuykKIX = false;
      bool TXzWwZdICi = false;
      bool LDMBMBunEO = false;
      bool bmxYdrFUEl = false;
      bool KDErNFCTAV = false;
      bool gcDgGueKFs = false;
      bool DwGtugaarD = false;
      bool TIDPXHzTmG = false;
      bool zbnigziQSi = false;
      bool NuPKiNxJxg = false;
      bool eaawBXYmIy = false;
      string DjDGnKpkKo;
      string clRsJrpnKw;
      string cJxAMqtDoH;
      string oXdbANoHwZ;
      string iAaKtLWYup;
      string CVUVfsmCsx;
      string QluCzFHoru;
      string DhrkMbimGB;
      string TUIzETCIwH;
      string alOyJxFXKn;
      string DhgAlUdjJE;
      string KAwqduduxf;
      string DyskURTsbO;
      string VKbSxlnIMj;
      string oSzqwZoWUN;
      string SJadkFnufU;
      string AkIthAYcsr;
      string HVhMqkyCot;
      string bwXNwMiyhr;
      string xrbrjEKFJu;
      if(DjDGnKpkKo == DhgAlUdjJE){BMccFxbNmz = true;}
      else if(DhgAlUdjJE == DjDGnKpkKo){TXzWwZdICi = true;}
      if(clRsJrpnKw == KAwqduduxf){GkGkrDMtyV = true;}
      else if(KAwqduduxf == clRsJrpnKw){LDMBMBunEO = true;}
      if(cJxAMqtDoH == DyskURTsbO){QZuBtPspcm = true;}
      else if(DyskURTsbO == cJxAMqtDoH){bmxYdrFUEl = true;}
      if(oXdbANoHwZ == VKbSxlnIMj){assssPTuHy = true;}
      else if(VKbSxlnIMj == oXdbANoHwZ){KDErNFCTAV = true;}
      if(iAaKtLWYup == oSzqwZoWUN){jVLhkMkqzf = true;}
      else if(oSzqwZoWUN == iAaKtLWYup){gcDgGueKFs = true;}
      if(CVUVfsmCsx == SJadkFnufU){qPHmdaQbip = true;}
      else if(SJadkFnufU == CVUVfsmCsx){DwGtugaarD = true;}
      if(QluCzFHoru == AkIthAYcsr){DlkAYNrMqc = true;}
      else if(AkIthAYcsr == QluCzFHoru){TIDPXHzTmG = true;}
      if(DhrkMbimGB == HVhMqkyCot){jRlzkuONPh = true;}
      if(TUIzETCIwH == bwXNwMiyhr){dBpwuKkFPS = true;}
      if(alOyJxFXKn == xrbrjEKFJu){yqLRuykKIX = true;}
      while(HVhMqkyCot == DhrkMbimGB){zbnigziQSi = true;}
      while(bwXNwMiyhr == bwXNwMiyhr){NuPKiNxJxg = true;}
      while(xrbrjEKFJu == xrbrjEKFJu){eaawBXYmIy = true;}
      if(BMccFxbNmz == true){BMccFxbNmz = false;}
      if(GkGkrDMtyV == true){GkGkrDMtyV = false;}
      if(QZuBtPspcm == true){QZuBtPspcm = false;}
      if(assssPTuHy == true){assssPTuHy = false;}
      if(jVLhkMkqzf == true){jVLhkMkqzf = false;}
      if(qPHmdaQbip == true){qPHmdaQbip = false;}
      if(DlkAYNrMqc == true){DlkAYNrMqc = false;}
      if(jRlzkuONPh == true){jRlzkuONPh = false;}
      if(dBpwuKkFPS == true){dBpwuKkFPS = false;}
      if(yqLRuykKIX == true){yqLRuykKIX = false;}
      if(TXzWwZdICi == true){TXzWwZdICi = false;}
      if(LDMBMBunEO == true){LDMBMBunEO = false;}
      if(bmxYdrFUEl == true){bmxYdrFUEl = false;}
      if(KDErNFCTAV == true){KDErNFCTAV = false;}
      if(gcDgGueKFs == true){gcDgGueKFs = false;}
      if(DwGtugaarD == true){DwGtugaarD = false;}
      if(TIDPXHzTmG == true){TIDPXHzTmG = false;}
      if(zbnigziQSi == true){zbnigziQSi = false;}
      if(NuPKiNxJxg == true){NuPKiNxJxg = false;}
      if(eaawBXYmIy == true){eaawBXYmIy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLNRMAFONU
{ 
  void qqTPIsJmcF()
  { 
      bool lyCECJQmUB = false;
      bool XdpgCwOdTM = false;
      bool gNRojnkfOP = false;
      bool iDXiFZEHUs = false;
      bool gJIQVhEVyD = false;
      bool RyOfdXgMUO = false;
      bool XjXFSUFHbb = false;
      bool rGJaeXFASB = false;
      bool iPgLyjnqEg = false;
      bool sqmGUwkDxA = false;
      bool bxsWLKomAG = false;
      bool RftSeIDMGi = false;
      bool gNCtiASDFh = false;
      bool lCDSZlVKzm = false;
      bool uAqyOMxUaM = false;
      bool sXwOTOuymK = false;
      bool rkgRTOcasr = false;
      bool msMTnfWDeW = false;
      bool CybsoOGnyK = false;
      bool qWXouJTYdA = false;
      string RzXZexpSpE;
      string zhtZKBpnjO;
      string hQsXdJdDxT;
      string CQNSUXxWXW;
      string AdsZmWoagm;
      string REYkJBGzuV;
      string TlUVChTbEm;
      string ETPMODWSjH;
      string TDVKCxqbIT;
      string RxaCDNIWWE;
      string CNVthxoLWF;
      string dmPnBQQKTF;
      string qqTjVGsNJA;
      string uzufEFgbcE;
      string IeFCodhlAl;
      string xyCRNKtkYa;
      string EbCWKdqiiu;
      string ingPwLlQtq;
      string YHMXCxxcRt;
      string LuDBAgcirL;
      if(RzXZexpSpE == CNVthxoLWF){lyCECJQmUB = true;}
      else if(CNVthxoLWF == RzXZexpSpE){bxsWLKomAG = true;}
      if(zhtZKBpnjO == dmPnBQQKTF){XdpgCwOdTM = true;}
      else if(dmPnBQQKTF == zhtZKBpnjO){RftSeIDMGi = true;}
      if(hQsXdJdDxT == qqTjVGsNJA){gNRojnkfOP = true;}
      else if(qqTjVGsNJA == hQsXdJdDxT){gNCtiASDFh = true;}
      if(CQNSUXxWXW == uzufEFgbcE){iDXiFZEHUs = true;}
      else if(uzufEFgbcE == CQNSUXxWXW){lCDSZlVKzm = true;}
      if(AdsZmWoagm == IeFCodhlAl){gJIQVhEVyD = true;}
      else if(IeFCodhlAl == AdsZmWoagm){uAqyOMxUaM = true;}
      if(REYkJBGzuV == xyCRNKtkYa){RyOfdXgMUO = true;}
      else if(xyCRNKtkYa == REYkJBGzuV){sXwOTOuymK = true;}
      if(TlUVChTbEm == EbCWKdqiiu){XjXFSUFHbb = true;}
      else if(EbCWKdqiiu == TlUVChTbEm){rkgRTOcasr = true;}
      if(ETPMODWSjH == ingPwLlQtq){rGJaeXFASB = true;}
      if(TDVKCxqbIT == YHMXCxxcRt){iPgLyjnqEg = true;}
      if(RxaCDNIWWE == LuDBAgcirL){sqmGUwkDxA = true;}
      while(ingPwLlQtq == ETPMODWSjH){msMTnfWDeW = true;}
      while(YHMXCxxcRt == YHMXCxxcRt){CybsoOGnyK = true;}
      while(LuDBAgcirL == LuDBAgcirL){qWXouJTYdA = true;}
      if(lyCECJQmUB == true){lyCECJQmUB = false;}
      if(XdpgCwOdTM == true){XdpgCwOdTM = false;}
      if(gNRojnkfOP == true){gNRojnkfOP = false;}
      if(iDXiFZEHUs == true){iDXiFZEHUs = false;}
      if(gJIQVhEVyD == true){gJIQVhEVyD = false;}
      if(RyOfdXgMUO == true){RyOfdXgMUO = false;}
      if(XjXFSUFHbb == true){XjXFSUFHbb = false;}
      if(rGJaeXFASB == true){rGJaeXFASB = false;}
      if(iPgLyjnqEg == true){iPgLyjnqEg = false;}
      if(sqmGUwkDxA == true){sqmGUwkDxA = false;}
      if(bxsWLKomAG == true){bxsWLKomAG = false;}
      if(RftSeIDMGi == true){RftSeIDMGi = false;}
      if(gNCtiASDFh == true){gNCtiASDFh = false;}
      if(lCDSZlVKzm == true){lCDSZlVKzm = false;}
      if(uAqyOMxUaM == true){uAqyOMxUaM = false;}
      if(sXwOTOuymK == true){sXwOTOuymK = false;}
      if(rkgRTOcasr == true){rkgRTOcasr = false;}
      if(msMTnfWDeW == true){msMTnfWDeW = false;}
      if(CybsoOGnyK == true){CybsoOGnyK = false;}
      if(qWXouJTYdA == true){qWXouJTYdA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCXLGAIWEF
{ 
  void NLhbrPdrwm()
  { 
      bool DbiJjsUWPA = false;
      bool eBwQhVtnXj = false;
      bool glVhwIpuey = false;
      bool WGgubMEZTq = false;
      bool rguPpNkuTz = false;
      bool QNcTaQFBMb = false;
      bool DYqRdXUBoV = false;
      bool RUTfrzpGqi = false;
      bool WubfgIcMTK = false;
      bool GCMrnSpdlS = false;
      bool riFygwtxab = false;
      bool ZzKdEIxLkV = false;
      bool tHhdOPHbrZ = false;
      bool JMTXpnodyj = false;
      bool OfkrjHqine = false;
      bool UesQYjBbiR = false;
      bool oREBRNemmQ = false;
      bool STMAGNWosG = false;
      bool YYnMEeTDzF = false;
      bool lNtguwajZW = false;
      string eEdHQjXhUe;
      string IukHtysYfm;
      string UiLQiVgcPX;
      string DVcUCdEVgC;
      string AECAgWqCsS;
      string IcCcqusMXt;
      string DtRxamRQEQ;
      string tXrdmQgKjM;
      string eejwPaSAcH;
      string jqxlyFlFZs;
      string EaxbYjjXpa;
      string NicKPXJUgA;
      string TRmxfCZGeg;
      string dbkpHDhHXf;
      string puJBsBOlVa;
      string uRXZYlmAwV;
      string JdrIxkxmDM;
      string pCxBJYHlDe;
      string nmjEkMELQV;
      string PhLBVLCBEI;
      if(eEdHQjXhUe == EaxbYjjXpa){DbiJjsUWPA = true;}
      else if(EaxbYjjXpa == eEdHQjXhUe){riFygwtxab = true;}
      if(IukHtysYfm == NicKPXJUgA){eBwQhVtnXj = true;}
      else if(NicKPXJUgA == IukHtysYfm){ZzKdEIxLkV = true;}
      if(UiLQiVgcPX == TRmxfCZGeg){glVhwIpuey = true;}
      else if(TRmxfCZGeg == UiLQiVgcPX){tHhdOPHbrZ = true;}
      if(DVcUCdEVgC == dbkpHDhHXf){WGgubMEZTq = true;}
      else if(dbkpHDhHXf == DVcUCdEVgC){JMTXpnodyj = true;}
      if(AECAgWqCsS == puJBsBOlVa){rguPpNkuTz = true;}
      else if(puJBsBOlVa == AECAgWqCsS){OfkrjHqine = true;}
      if(IcCcqusMXt == uRXZYlmAwV){QNcTaQFBMb = true;}
      else if(uRXZYlmAwV == IcCcqusMXt){UesQYjBbiR = true;}
      if(DtRxamRQEQ == JdrIxkxmDM){DYqRdXUBoV = true;}
      else if(JdrIxkxmDM == DtRxamRQEQ){oREBRNemmQ = true;}
      if(tXrdmQgKjM == pCxBJYHlDe){RUTfrzpGqi = true;}
      if(eejwPaSAcH == nmjEkMELQV){WubfgIcMTK = true;}
      if(jqxlyFlFZs == PhLBVLCBEI){GCMrnSpdlS = true;}
      while(pCxBJYHlDe == tXrdmQgKjM){STMAGNWosG = true;}
      while(nmjEkMELQV == nmjEkMELQV){YYnMEeTDzF = true;}
      while(PhLBVLCBEI == PhLBVLCBEI){lNtguwajZW = true;}
      if(DbiJjsUWPA == true){DbiJjsUWPA = false;}
      if(eBwQhVtnXj == true){eBwQhVtnXj = false;}
      if(glVhwIpuey == true){glVhwIpuey = false;}
      if(WGgubMEZTq == true){WGgubMEZTq = false;}
      if(rguPpNkuTz == true){rguPpNkuTz = false;}
      if(QNcTaQFBMb == true){QNcTaQFBMb = false;}
      if(DYqRdXUBoV == true){DYqRdXUBoV = false;}
      if(RUTfrzpGqi == true){RUTfrzpGqi = false;}
      if(WubfgIcMTK == true){WubfgIcMTK = false;}
      if(GCMrnSpdlS == true){GCMrnSpdlS = false;}
      if(riFygwtxab == true){riFygwtxab = false;}
      if(ZzKdEIxLkV == true){ZzKdEIxLkV = false;}
      if(tHhdOPHbrZ == true){tHhdOPHbrZ = false;}
      if(JMTXpnodyj == true){JMTXpnodyj = false;}
      if(OfkrjHqine == true){OfkrjHqine = false;}
      if(UesQYjBbiR == true){UesQYjBbiR = false;}
      if(oREBRNemmQ == true){oREBRNemmQ = false;}
      if(STMAGNWosG == true){STMAGNWosG = false;}
      if(YYnMEeTDzF == true){YYnMEeTDzF = false;}
      if(lNtguwajZW == true){lNtguwajZW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZWUXSOKBL
{ 
  void BhzXZKtFyO()
  { 
      bool YQPJMUBxJY = false;
      bool RDIPEIgdKG = false;
      bool EZtBDObfhc = false;
      bool BtsGTlIaPr = false;
      bool BtwDyuTyRF = false;
      bool RmcZpyWOGx = false;
      bool sUPgXWKBwS = false;
      bool AGOSFJdpCH = false;
      bool ucOcKNRSQU = false;
      bool OsURygeOfa = false;
      bool kSCyELYJUf = false;
      bool UgLzCPFmWJ = false;
      bool FqjaEGkxTY = false;
      bool ePJbVcaQXz = false;
      bool oHykzhhVPi = false;
      bool arrWUshaty = false;
      bool ZbpwBFWjcZ = false;
      bool ooPWTyrzbV = false;
      bool YPgjxlWlGb = false;
      bool uzVYYNQCjt = false;
      string nahlTduFUN;
      string MCYyzwVZMJ;
      string iiemzXLHws;
      string lKCIeYZBlz;
      string MsMHjrGWfU;
      string IDAtEEutmu;
      string SnIbbBAQTa;
      string VUnNxpVXDG;
      string RoabjhKHDZ;
      string ceNpgYjkeh;
      string qpDFynPlwO;
      string hXqfdcMfqs;
      string qrNsxpGxfY;
      string FkrUOblVdu;
      string RXKnqEngLD;
      string LDslqzbJHH;
      string hSGXIxfWQC;
      string qpCubSgYBr;
      string CYkbMCrFcP;
      string zbNVNzRmft;
      if(nahlTduFUN == qpDFynPlwO){YQPJMUBxJY = true;}
      else if(qpDFynPlwO == nahlTduFUN){kSCyELYJUf = true;}
      if(MCYyzwVZMJ == hXqfdcMfqs){RDIPEIgdKG = true;}
      else if(hXqfdcMfqs == MCYyzwVZMJ){UgLzCPFmWJ = true;}
      if(iiemzXLHws == qrNsxpGxfY){EZtBDObfhc = true;}
      else if(qrNsxpGxfY == iiemzXLHws){FqjaEGkxTY = true;}
      if(lKCIeYZBlz == FkrUOblVdu){BtsGTlIaPr = true;}
      else if(FkrUOblVdu == lKCIeYZBlz){ePJbVcaQXz = true;}
      if(MsMHjrGWfU == RXKnqEngLD){BtwDyuTyRF = true;}
      else if(RXKnqEngLD == MsMHjrGWfU){oHykzhhVPi = true;}
      if(IDAtEEutmu == LDslqzbJHH){RmcZpyWOGx = true;}
      else if(LDslqzbJHH == IDAtEEutmu){arrWUshaty = true;}
      if(SnIbbBAQTa == hSGXIxfWQC){sUPgXWKBwS = true;}
      else if(hSGXIxfWQC == SnIbbBAQTa){ZbpwBFWjcZ = true;}
      if(VUnNxpVXDG == qpCubSgYBr){AGOSFJdpCH = true;}
      if(RoabjhKHDZ == CYkbMCrFcP){ucOcKNRSQU = true;}
      if(ceNpgYjkeh == zbNVNzRmft){OsURygeOfa = true;}
      while(qpCubSgYBr == VUnNxpVXDG){ooPWTyrzbV = true;}
      while(CYkbMCrFcP == CYkbMCrFcP){YPgjxlWlGb = true;}
      while(zbNVNzRmft == zbNVNzRmft){uzVYYNQCjt = true;}
      if(YQPJMUBxJY == true){YQPJMUBxJY = false;}
      if(RDIPEIgdKG == true){RDIPEIgdKG = false;}
      if(EZtBDObfhc == true){EZtBDObfhc = false;}
      if(BtsGTlIaPr == true){BtsGTlIaPr = false;}
      if(BtwDyuTyRF == true){BtwDyuTyRF = false;}
      if(RmcZpyWOGx == true){RmcZpyWOGx = false;}
      if(sUPgXWKBwS == true){sUPgXWKBwS = false;}
      if(AGOSFJdpCH == true){AGOSFJdpCH = false;}
      if(ucOcKNRSQU == true){ucOcKNRSQU = false;}
      if(OsURygeOfa == true){OsURygeOfa = false;}
      if(kSCyELYJUf == true){kSCyELYJUf = false;}
      if(UgLzCPFmWJ == true){UgLzCPFmWJ = false;}
      if(FqjaEGkxTY == true){FqjaEGkxTY = false;}
      if(ePJbVcaQXz == true){ePJbVcaQXz = false;}
      if(oHykzhhVPi == true){oHykzhhVPi = false;}
      if(arrWUshaty == true){arrWUshaty = false;}
      if(ZbpwBFWjcZ == true){ZbpwBFWjcZ = false;}
      if(ooPWTyrzbV == true){ooPWTyrzbV = false;}
      if(YPgjxlWlGb == true){YPgjxlWlGb = false;}
      if(uzVYYNQCjt == true){uzVYYNQCjt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTXDYSCFAH
{ 
  void WipEeOTZBf()
  { 
      bool FJMaoAkMaL = false;
      bool zYuPVLQMqJ = false;
      bool TrewmQuDqo = false;
      bool dbrOVwrFCp = false;
      bool QoIffjabFF = false;
      bool euHJrNdPmX = false;
      bool EgUlgWfgtY = false;
      bool TKJBrdiyQC = false;
      bool oSylKiThWI = false;
      bool RbRdkjUWyI = false;
      bool EthgkTkGRN = false;
      bool deykilihby = false;
      bool DyJkHqsfPI = false;
      bool JMAIyujRAp = false;
      bool xNQIdlcguz = false;
      bool BluAFFjxYs = false;
      bool aEpIDReplm = false;
      bool BRhkAphBGU = false;
      bool OLkQGXQzDs = false;
      bool LmrGPsWHEM = false;
      string AOFzKjYHtm;
      string NFGhkRGqmV;
      string OZDJczhKIN;
      string NgBFASmrZK;
      string cxqPZncLVr;
      string XSzGuaLuVL;
      string COzfYfEBgR;
      string dORbsQhmio;
      string VWoQpthuJZ;
      string GrVNINyLqt;
      string ibdDNIBWNd;
      string rYLgpfZhpd;
      string xIqHKlrDTe;
      string SWwoFsrkCg;
      string sLhfghfnXb;
      string nQUMxZjVra;
      string PxDhLVbWbw;
      string mneIklaLZb;
      string FEfqpCBjqe;
      string JWraQuHzTL;
      if(AOFzKjYHtm == ibdDNIBWNd){FJMaoAkMaL = true;}
      else if(ibdDNIBWNd == AOFzKjYHtm){EthgkTkGRN = true;}
      if(NFGhkRGqmV == rYLgpfZhpd){zYuPVLQMqJ = true;}
      else if(rYLgpfZhpd == NFGhkRGqmV){deykilihby = true;}
      if(OZDJczhKIN == xIqHKlrDTe){TrewmQuDqo = true;}
      else if(xIqHKlrDTe == OZDJczhKIN){DyJkHqsfPI = true;}
      if(NgBFASmrZK == SWwoFsrkCg){dbrOVwrFCp = true;}
      else if(SWwoFsrkCg == NgBFASmrZK){JMAIyujRAp = true;}
      if(cxqPZncLVr == sLhfghfnXb){QoIffjabFF = true;}
      else if(sLhfghfnXb == cxqPZncLVr){xNQIdlcguz = true;}
      if(XSzGuaLuVL == nQUMxZjVra){euHJrNdPmX = true;}
      else if(nQUMxZjVra == XSzGuaLuVL){BluAFFjxYs = true;}
      if(COzfYfEBgR == PxDhLVbWbw){EgUlgWfgtY = true;}
      else if(PxDhLVbWbw == COzfYfEBgR){aEpIDReplm = true;}
      if(dORbsQhmio == mneIklaLZb){TKJBrdiyQC = true;}
      if(VWoQpthuJZ == FEfqpCBjqe){oSylKiThWI = true;}
      if(GrVNINyLqt == JWraQuHzTL){RbRdkjUWyI = true;}
      while(mneIklaLZb == dORbsQhmio){BRhkAphBGU = true;}
      while(FEfqpCBjqe == FEfqpCBjqe){OLkQGXQzDs = true;}
      while(JWraQuHzTL == JWraQuHzTL){LmrGPsWHEM = true;}
      if(FJMaoAkMaL == true){FJMaoAkMaL = false;}
      if(zYuPVLQMqJ == true){zYuPVLQMqJ = false;}
      if(TrewmQuDqo == true){TrewmQuDqo = false;}
      if(dbrOVwrFCp == true){dbrOVwrFCp = false;}
      if(QoIffjabFF == true){QoIffjabFF = false;}
      if(euHJrNdPmX == true){euHJrNdPmX = false;}
      if(EgUlgWfgtY == true){EgUlgWfgtY = false;}
      if(TKJBrdiyQC == true){TKJBrdiyQC = false;}
      if(oSylKiThWI == true){oSylKiThWI = false;}
      if(RbRdkjUWyI == true){RbRdkjUWyI = false;}
      if(EthgkTkGRN == true){EthgkTkGRN = false;}
      if(deykilihby == true){deykilihby = false;}
      if(DyJkHqsfPI == true){DyJkHqsfPI = false;}
      if(JMAIyujRAp == true){JMAIyujRAp = false;}
      if(xNQIdlcguz == true){xNQIdlcguz = false;}
      if(BluAFFjxYs == true){BluAFFjxYs = false;}
      if(aEpIDReplm == true){aEpIDReplm = false;}
      if(BRhkAphBGU == true){BRhkAphBGU = false;}
      if(OLkQGXQzDs == true){OLkQGXQzDs = false;}
      if(LmrGPsWHEM == true){LmrGPsWHEM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKBEHASQIN
{ 
  void ZScdHFdpFL()
  { 
      bool fSMNeYCzTZ = false;
      bool HRQqZiGyXd = false;
      bool bUQAjFIGOA = false;
      bool ylZepMnANA = false;
      bool OJVGNDiDbn = false;
      bool xXOKDLBMcY = false;
      bool PwjTaVqlAN = false;
      bool uFkWOSyKlg = false;
      bool WEeZDZWOae = false;
      bool KbXnjSYCer = false;
      bool LxDOsqlqwk = false;
      bool NqZuCLRKQB = false;
      bool ybKVCTgxmw = false;
      bool suesUZBQgL = false;
      bool mfSpRTBckY = false;
      bool BNldsilgLZ = false;
      bool JoEAqRLfZc = false;
      bool JAdENSJTEh = false;
      bool RELNteJAzl = false;
      bool mTEHByaSzA = false;
      string lMsqGDlJIl;
      string SYmYkMOTQh;
      string qeVJaSxoql;
      string iyefDHaXNW;
      string nqDEAilVEk;
      string JIOtXHpjPm;
      string GxSWDTsGVd;
      string lpGssAbQJq;
      string gajFbZikHu;
      string QqHZQpXgBf;
      string oeAazTBUAX;
      string fZaYGfNNtc;
      string jIzZMuigcC;
      string btOcCBZIFI;
      string YOjjPpPiSj;
      string cKlYwffaNE;
      string jUqxukKxVF;
      string FEHlEVYOJV;
      string eANrZRIpgV;
      string UzuBXDWloe;
      if(lMsqGDlJIl == oeAazTBUAX){fSMNeYCzTZ = true;}
      else if(oeAazTBUAX == lMsqGDlJIl){LxDOsqlqwk = true;}
      if(SYmYkMOTQh == fZaYGfNNtc){HRQqZiGyXd = true;}
      else if(fZaYGfNNtc == SYmYkMOTQh){NqZuCLRKQB = true;}
      if(qeVJaSxoql == jIzZMuigcC){bUQAjFIGOA = true;}
      else if(jIzZMuigcC == qeVJaSxoql){ybKVCTgxmw = true;}
      if(iyefDHaXNW == btOcCBZIFI){ylZepMnANA = true;}
      else if(btOcCBZIFI == iyefDHaXNW){suesUZBQgL = true;}
      if(nqDEAilVEk == YOjjPpPiSj){OJVGNDiDbn = true;}
      else if(YOjjPpPiSj == nqDEAilVEk){mfSpRTBckY = true;}
      if(JIOtXHpjPm == cKlYwffaNE){xXOKDLBMcY = true;}
      else if(cKlYwffaNE == JIOtXHpjPm){BNldsilgLZ = true;}
      if(GxSWDTsGVd == jUqxukKxVF){PwjTaVqlAN = true;}
      else if(jUqxukKxVF == GxSWDTsGVd){JoEAqRLfZc = true;}
      if(lpGssAbQJq == FEHlEVYOJV){uFkWOSyKlg = true;}
      if(gajFbZikHu == eANrZRIpgV){WEeZDZWOae = true;}
      if(QqHZQpXgBf == UzuBXDWloe){KbXnjSYCer = true;}
      while(FEHlEVYOJV == lpGssAbQJq){JAdENSJTEh = true;}
      while(eANrZRIpgV == eANrZRIpgV){RELNteJAzl = true;}
      while(UzuBXDWloe == UzuBXDWloe){mTEHByaSzA = true;}
      if(fSMNeYCzTZ == true){fSMNeYCzTZ = false;}
      if(HRQqZiGyXd == true){HRQqZiGyXd = false;}
      if(bUQAjFIGOA == true){bUQAjFIGOA = false;}
      if(ylZepMnANA == true){ylZepMnANA = false;}
      if(OJVGNDiDbn == true){OJVGNDiDbn = false;}
      if(xXOKDLBMcY == true){xXOKDLBMcY = false;}
      if(PwjTaVqlAN == true){PwjTaVqlAN = false;}
      if(uFkWOSyKlg == true){uFkWOSyKlg = false;}
      if(WEeZDZWOae == true){WEeZDZWOae = false;}
      if(KbXnjSYCer == true){KbXnjSYCer = false;}
      if(LxDOsqlqwk == true){LxDOsqlqwk = false;}
      if(NqZuCLRKQB == true){NqZuCLRKQB = false;}
      if(ybKVCTgxmw == true){ybKVCTgxmw = false;}
      if(suesUZBQgL == true){suesUZBQgL = false;}
      if(mfSpRTBckY == true){mfSpRTBckY = false;}
      if(BNldsilgLZ == true){BNldsilgLZ = false;}
      if(JoEAqRLfZc == true){JoEAqRLfZc = false;}
      if(JAdENSJTEh == true){JAdENSJTEh = false;}
      if(RELNteJAzl == true){RELNteJAzl = false;}
      if(mTEHByaSzA == true){mTEHByaSzA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFSVSMTVUN
{ 
  void mFyxDHWHUX()
  { 
      bool HPAFxFkoou = false;
      bool UeUpXIAnXu = false;
      bool elhCYiWgfN = false;
      bool oDilPLEYxp = false;
      bool dOaesdmzZm = false;
      bool qIorOUhyfN = false;
      bool hDIbGRuiaL = false;
      bool EapgRPLDJu = false;
      bool wXGsVgOpWt = false;
      bool dGsiIZGzYa = false;
      bool hEYNiQRHay = false;
      bool IdnkRKwPGY = false;
      bool DELfhyhGYq = false;
      bool IMehMqzsKF = false;
      bool OGPXkzRHRx = false;
      bool cqrzXcrrej = false;
      bool hLijpwyGXZ = false;
      bool LDFAJwomth = false;
      bool gZoaORTfJj = false;
      bool zGNZWDXfho = false;
      string pyzYoZNLKR;
      string IFwEYIiOZw;
      string gJCZaKLyne;
      string UqtqOTQeMB;
      string yNiUQsbxzq;
      string mzqfGfwZyd;
      string NPXexQLEpE;
      string qDCXxTahIh;
      string iOywrUzOjh;
      string XqginipEWz;
      string hWHtAixThm;
      string FNRPtzQalb;
      string RwUHgAVSjO;
      string cWKIzLHDwJ;
      string WffxbJYQno;
      string SORthkCzNz;
      string NeiTJiCIQi;
      string qMdcFlPWeW;
      string bEduwOEPaN;
      string JHpxwrwMms;
      if(pyzYoZNLKR == hWHtAixThm){HPAFxFkoou = true;}
      else if(hWHtAixThm == pyzYoZNLKR){hEYNiQRHay = true;}
      if(IFwEYIiOZw == FNRPtzQalb){UeUpXIAnXu = true;}
      else if(FNRPtzQalb == IFwEYIiOZw){IdnkRKwPGY = true;}
      if(gJCZaKLyne == RwUHgAVSjO){elhCYiWgfN = true;}
      else if(RwUHgAVSjO == gJCZaKLyne){DELfhyhGYq = true;}
      if(UqtqOTQeMB == cWKIzLHDwJ){oDilPLEYxp = true;}
      else if(cWKIzLHDwJ == UqtqOTQeMB){IMehMqzsKF = true;}
      if(yNiUQsbxzq == WffxbJYQno){dOaesdmzZm = true;}
      else if(WffxbJYQno == yNiUQsbxzq){OGPXkzRHRx = true;}
      if(mzqfGfwZyd == SORthkCzNz){qIorOUhyfN = true;}
      else if(SORthkCzNz == mzqfGfwZyd){cqrzXcrrej = true;}
      if(NPXexQLEpE == NeiTJiCIQi){hDIbGRuiaL = true;}
      else if(NeiTJiCIQi == NPXexQLEpE){hLijpwyGXZ = true;}
      if(qDCXxTahIh == qMdcFlPWeW){EapgRPLDJu = true;}
      if(iOywrUzOjh == bEduwOEPaN){wXGsVgOpWt = true;}
      if(XqginipEWz == JHpxwrwMms){dGsiIZGzYa = true;}
      while(qMdcFlPWeW == qDCXxTahIh){LDFAJwomth = true;}
      while(bEduwOEPaN == bEduwOEPaN){gZoaORTfJj = true;}
      while(JHpxwrwMms == JHpxwrwMms){zGNZWDXfho = true;}
      if(HPAFxFkoou == true){HPAFxFkoou = false;}
      if(UeUpXIAnXu == true){UeUpXIAnXu = false;}
      if(elhCYiWgfN == true){elhCYiWgfN = false;}
      if(oDilPLEYxp == true){oDilPLEYxp = false;}
      if(dOaesdmzZm == true){dOaesdmzZm = false;}
      if(qIorOUhyfN == true){qIorOUhyfN = false;}
      if(hDIbGRuiaL == true){hDIbGRuiaL = false;}
      if(EapgRPLDJu == true){EapgRPLDJu = false;}
      if(wXGsVgOpWt == true){wXGsVgOpWt = false;}
      if(dGsiIZGzYa == true){dGsiIZGzYa = false;}
      if(hEYNiQRHay == true){hEYNiQRHay = false;}
      if(IdnkRKwPGY == true){IdnkRKwPGY = false;}
      if(DELfhyhGYq == true){DELfhyhGYq = false;}
      if(IMehMqzsKF == true){IMehMqzsKF = false;}
      if(OGPXkzRHRx == true){OGPXkzRHRx = false;}
      if(cqrzXcrrej == true){cqrzXcrrej = false;}
      if(hLijpwyGXZ == true){hLijpwyGXZ = false;}
      if(LDFAJwomth == true){LDFAJwomth = false;}
      if(gZoaORTfJj == true){gZoaORTfJj = false;}
      if(zGNZWDXfho == true){zGNZWDXfho = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZDFRZXHDK
{ 
  void fGNxwRSLAC()
  { 
      bool qWhSByuGwB = false;
      bool AmxSFoyikT = false;
      bool tasGLMhWrl = false;
      bool oUnVNmWWJs = false;
      bool KEdjXGkEsE = false;
      bool FuqNaQcaHn = false;
      bool PYNJMezaFS = false;
      bool RbZrIpxJhE = false;
      bool addnfsdZtx = false;
      bool JuPUclpTWs = false;
      bool HJzZldVzEk = false;
      bool STsCNluYcT = false;
      bool BYfHJVMFPW = false;
      bool zcloxRdDBB = false;
      bool WdVJdoCMHp = false;
      bool pRpCqicqQP = false;
      bool RQjgkogDFu = false;
      bool HqWawWCWcT = false;
      bool TzyYfhmjxO = false;
      bool nmmkjGtoYo = false;
      string xzEutxRngf;
      string ExFUPthQgj;
      string ySxxQBxuPD;
      string woLZPKuwWN;
      string eZwJboPPbZ;
      string AxSeVeCGer;
      string AWYdjOkfEF;
      string zksSFXVmUb;
      string khSoCyWfEj;
      string HnReNIASZN;
      string DjKWaOEzZx;
      string IOlDGRDjal;
      string qEbUxLTOFw;
      string WDNHXBXwOn;
      string tXGGbrBNXu;
      string FQrnVyHpYP;
      string toscZFBefE;
      string tGVlqTyUrF;
      string JFpKqGKZkY;
      string shXysEecgV;
      if(xzEutxRngf == DjKWaOEzZx){qWhSByuGwB = true;}
      else if(DjKWaOEzZx == xzEutxRngf){HJzZldVzEk = true;}
      if(ExFUPthQgj == IOlDGRDjal){AmxSFoyikT = true;}
      else if(IOlDGRDjal == ExFUPthQgj){STsCNluYcT = true;}
      if(ySxxQBxuPD == qEbUxLTOFw){tasGLMhWrl = true;}
      else if(qEbUxLTOFw == ySxxQBxuPD){BYfHJVMFPW = true;}
      if(woLZPKuwWN == WDNHXBXwOn){oUnVNmWWJs = true;}
      else if(WDNHXBXwOn == woLZPKuwWN){zcloxRdDBB = true;}
      if(eZwJboPPbZ == tXGGbrBNXu){KEdjXGkEsE = true;}
      else if(tXGGbrBNXu == eZwJboPPbZ){WdVJdoCMHp = true;}
      if(AxSeVeCGer == FQrnVyHpYP){FuqNaQcaHn = true;}
      else if(FQrnVyHpYP == AxSeVeCGer){pRpCqicqQP = true;}
      if(AWYdjOkfEF == toscZFBefE){PYNJMezaFS = true;}
      else if(toscZFBefE == AWYdjOkfEF){RQjgkogDFu = true;}
      if(zksSFXVmUb == tGVlqTyUrF){RbZrIpxJhE = true;}
      if(khSoCyWfEj == JFpKqGKZkY){addnfsdZtx = true;}
      if(HnReNIASZN == shXysEecgV){JuPUclpTWs = true;}
      while(tGVlqTyUrF == zksSFXVmUb){HqWawWCWcT = true;}
      while(JFpKqGKZkY == JFpKqGKZkY){TzyYfhmjxO = true;}
      while(shXysEecgV == shXysEecgV){nmmkjGtoYo = true;}
      if(qWhSByuGwB == true){qWhSByuGwB = false;}
      if(AmxSFoyikT == true){AmxSFoyikT = false;}
      if(tasGLMhWrl == true){tasGLMhWrl = false;}
      if(oUnVNmWWJs == true){oUnVNmWWJs = false;}
      if(KEdjXGkEsE == true){KEdjXGkEsE = false;}
      if(FuqNaQcaHn == true){FuqNaQcaHn = false;}
      if(PYNJMezaFS == true){PYNJMezaFS = false;}
      if(RbZrIpxJhE == true){RbZrIpxJhE = false;}
      if(addnfsdZtx == true){addnfsdZtx = false;}
      if(JuPUclpTWs == true){JuPUclpTWs = false;}
      if(HJzZldVzEk == true){HJzZldVzEk = false;}
      if(STsCNluYcT == true){STsCNluYcT = false;}
      if(BYfHJVMFPW == true){BYfHJVMFPW = false;}
      if(zcloxRdDBB == true){zcloxRdDBB = false;}
      if(WdVJdoCMHp == true){WdVJdoCMHp = false;}
      if(pRpCqicqQP == true){pRpCqicqQP = false;}
      if(RQjgkogDFu == true){RQjgkogDFu = false;}
      if(HqWawWCWcT == true){HqWawWCWcT = false;}
      if(TzyYfhmjxO == true){TzyYfhmjxO = false;}
      if(nmmkjGtoYo == true){nmmkjGtoYo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVPCZYUAXA
{ 
  void NZgIXqFyyt()
  { 
      bool HabRwYhwTg = false;
      bool bXhRUgjIPJ = false;
      bool eRQGrMekEX = false;
      bool ATgUuTTcnX = false;
      bool iLhtkkhmaS = false;
      bool RGpFAoKVYi = false;
      bool txqugHpMWB = false;
      bool NGUqaTjVVG = false;
      bool eqKlFtdaUF = false;
      bool IxEEdlTlNc = false;
      bool uUPYFKkydg = false;
      bool FnAREClFpm = false;
      bool dPrRrPCPNo = false;
      bool zxIrLJakgt = false;
      bool IfxnzUxlAa = false;
      bool zNwZzecyfo = false;
      bool HUkngHeHGu = false;
      bool aBYudyRDRX = false;
      bool RQPmplBhsf = false;
      bool fcEqlmtIHr = false;
      string eAPUiCdGPR;
      string KNXXYzrWpi;
      string ewlCdVasVm;
      string haiotEyVKd;
      string GqImGWncSe;
      string qFOxsiNNpM;
      string akjbjjdhcU;
      string AWLMcmnyuH;
      string hyZqwbLlwL;
      string pkexCUHfCV;
      string sFzyeTsCTF;
      string tPRidcLsfI;
      string YqlQdOrOJH;
      string eHuYOczaLb;
      string hIRpQaTwSZ;
      string JOAtxBThUP;
      string besMalTrTB;
      string djgDaPYwzC;
      string uuujxQHBbN;
      string JQFuzCPFPe;
      if(eAPUiCdGPR == sFzyeTsCTF){HabRwYhwTg = true;}
      else if(sFzyeTsCTF == eAPUiCdGPR){uUPYFKkydg = true;}
      if(KNXXYzrWpi == tPRidcLsfI){bXhRUgjIPJ = true;}
      else if(tPRidcLsfI == KNXXYzrWpi){FnAREClFpm = true;}
      if(ewlCdVasVm == YqlQdOrOJH){eRQGrMekEX = true;}
      else if(YqlQdOrOJH == ewlCdVasVm){dPrRrPCPNo = true;}
      if(haiotEyVKd == eHuYOczaLb){ATgUuTTcnX = true;}
      else if(eHuYOczaLb == haiotEyVKd){zxIrLJakgt = true;}
      if(GqImGWncSe == hIRpQaTwSZ){iLhtkkhmaS = true;}
      else if(hIRpQaTwSZ == GqImGWncSe){IfxnzUxlAa = true;}
      if(qFOxsiNNpM == JOAtxBThUP){RGpFAoKVYi = true;}
      else if(JOAtxBThUP == qFOxsiNNpM){zNwZzecyfo = true;}
      if(akjbjjdhcU == besMalTrTB){txqugHpMWB = true;}
      else if(besMalTrTB == akjbjjdhcU){HUkngHeHGu = true;}
      if(AWLMcmnyuH == djgDaPYwzC){NGUqaTjVVG = true;}
      if(hyZqwbLlwL == uuujxQHBbN){eqKlFtdaUF = true;}
      if(pkexCUHfCV == JQFuzCPFPe){IxEEdlTlNc = true;}
      while(djgDaPYwzC == AWLMcmnyuH){aBYudyRDRX = true;}
      while(uuujxQHBbN == uuujxQHBbN){RQPmplBhsf = true;}
      while(JQFuzCPFPe == JQFuzCPFPe){fcEqlmtIHr = true;}
      if(HabRwYhwTg == true){HabRwYhwTg = false;}
      if(bXhRUgjIPJ == true){bXhRUgjIPJ = false;}
      if(eRQGrMekEX == true){eRQGrMekEX = false;}
      if(ATgUuTTcnX == true){ATgUuTTcnX = false;}
      if(iLhtkkhmaS == true){iLhtkkhmaS = false;}
      if(RGpFAoKVYi == true){RGpFAoKVYi = false;}
      if(txqugHpMWB == true){txqugHpMWB = false;}
      if(NGUqaTjVVG == true){NGUqaTjVVG = false;}
      if(eqKlFtdaUF == true){eqKlFtdaUF = false;}
      if(IxEEdlTlNc == true){IxEEdlTlNc = false;}
      if(uUPYFKkydg == true){uUPYFKkydg = false;}
      if(FnAREClFpm == true){FnAREClFpm = false;}
      if(dPrRrPCPNo == true){dPrRrPCPNo = false;}
      if(zxIrLJakgt == true){zxIrLJakgt = false;}
      if(IfxnzUxlAa == true){IfxnzUxlAa = false;}
      if(zNwZzecyfo == true){zNwZzecyfo = false;}
      if(HUkngHeHGu == true){HUkngHeHGu = false;}
      if(aBYudyRDRX == true){aBYudyRDRX = false;}
      if(RQPmplBhsf == true){RQPmplBhsf = false;}
      if(fcEqlmtIHr == true){fcEqlmtIHr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APXODBIWZZ
{ 
  void OTxBbqObom()
  { 
      bool NojNwPTxeA = false;
      bool qMdiCQmKAR = false;
      bool GuMNrfkZbJ = false;
      bool XgFAHqXgnC = false;
      bool CUrrtcJXAE = false;
      bool fBPfxSbVUP = false;
      bool dtUVbJHdbL = false;
      bool rGVxPlCTTP = false;
      bool WMYXdWRYCo = false;
      bool OBLYYIzWQj = false;
      bool VewoLZeRQL = false;
      bool PICFsRUxqE = false;
      bool rhalxqtxYH = false;
      bool meDitqPjLE = false;
      bool rzIqYFyGeH = false;
      bool mBeLqmDKrU = false;
      bool egsIYjETLC = false;
      bool BkkmMsYjMq = false;
      bool rnRQTkArqG = false;
      bool mFqqYKFzSn = false;
      string EjNjQXcRWf;
      string GSWgiQXRuX;
      string EaOaTLsFGX;
      string ZKKjoBOXpl;
      string jXgsWbuHmL;
      string PAGhodUlQF;
      string dWKyFuImrh;
      string CzaJngtUEr;
      string PlRuIZEcuL;
      string fbHkHNMina;
      string SIOFIPYwsI;
      string izhXoqEPoe;
      string qeqfBZqpBa;
      string TLgcYGWLls;
      string BHimbftiuQ;
      string IxsIjmRiEh;
      string XhuSnXSFzh;
      string UrcwcjwEEU;
      string fHtkSVRXrk;
      string onHDUTLPyD;
      if(EjNjQXcRWf == SIOFIPYwsI){NojNwPTxeA = true;}
      else if(SIOFIPYwsI == EjNjQXcRWf){VewoLZeRQL = true;}
      if(GSWgiQXRuX == izhXoqEPoe){qMdiCQmKAR = true;}
      else if(izhXoqEPoe == GSWgiQXRuX){PICFsRUxqE = true;}
      if(EaOaTLsFGX == qeqfBZqpBa){GuMNrfkZbJ = true;}
      else if(qeqfBZqpBa == EaOaTLsFGX){rhalxqtxYH = true;}
      if(ZKKjoBOXpl == TLgcYGWLls){XgFAHqXgnC = true;}
      else if(TLgcYGWLls == ZKKjoBOXpl){meDitqPjLE = true;}
      if(jXgsWbuHmL == BHimbftiuQ){CUrrtcJXAE = true;}
      else if(BHimbftiuQ == jXgsWbuHmL){rzIqYFyGeH = true;}
      if(PAGhodUlQF == IxsIjmRiEh){fBPfxSbVUP = true;}
      else if(IxsIjmRiEh == PAGhodUlQF){mBeLqmDKrU = true;}
      if(dWKyFuImrh == XhuSnXSFzh){dtUVbJHdbL = true;}
      else if(XhuSnXSFzh == dWKyFuImrh){egsIYjETLC = true;}
      if(CzaJngtUEr == UrcwcjwEEU){rGVxPlCTTP = true;}
      if(PlRuIZEcuL == fHtkSVRXrk){WMYXdWRYCo = true;}
      if(fbHkHNMina == onHDUTLPyD){OBLYYIzWQj = true;}
      while(UrcwcjwEEU == CzaJngtUEr){BkkmMsYjMq = true;}
      while(fHtkSVRXrk == fHtkSVRXrk){rnRQTkArqG = true;}
      while(onHDUTLPyD == onHDUTLPyD){mFqqYKFzSn = true;}
      if(NojNwPTxeA == true){NojNwPTxeA = false;}
      if(qMdiCQmKAR == true){qMdiCQmKAR = false;}
      if(GuMNrfkZbJ == true){GuMNrfkZbJ = false;}
      if(XgFAHqXgnC == true){XgFAHqXgnC = false;}
      if(CUrrtcJXAE == true){CUrrtcJXAE = false;}
      if(fBPfxSbVUP == true){fBPfxSbVUP = false;}
      if(dtUVbJHdbL == true){dtUVbJHdbL = false;}
      if(rGVxPlCTTP == true){rGVxPlCTTP = false;}
      if(WMYXdWRYCo == true){WMYXdWRYCo = false;}
      if(OBLYYIzWQj == true){OBLYYIzWQj = false;}
      if(VewoLZeRQL == true){VewoLZeRQL = false;}
      if(PICFsRUxqE == true){PICFsRUxqE = false;}
      if(rhalxqtxYH == true){rhalxqtxYH = false;}
      if(meDitqPjLE == true){meDitqPjLE = false;}
      if(rzIqYFyGeH == true){rzIqYFyGeH = false;}
      if(mBeLqmDKrU == true){mBeLqmDKrU = false;}
      if(egsIYjETLC == true){egsIYjETLC = false;}
      if(BkkmMsYjMq == true){BkkmMsYjMq = false;}
      if(rnRQTkArqG == true){rnRQTkArqG = false;}
      if(mFqqYKFzSn == true){mFqqYKFzSn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUOTSMPBVC
{ 
  void lVdckxLrDj()
  { 
      bool dVbQTzWnLL = false;
      bool nSLyPYhEzi = false;
      bool pyTlWpbjUH = false;
      bool DcKiKmhFyR = false;
      bool yLKOMRswxs = false;
      bool lEyereBosd = false;
      bool WmTDHKIcnc = false;
      bool qcGhkemFZE = false;
      bool wflaVzeepe = false;
      bool lsLTtKqGGB = false;
      bool IPHUCIxPtM = false;
      bool quOogpBshI = false;
      bool edlIqxQlmZ = false;
      bool mfzYugYQYM = false;
      bool BOjdnpeWmD = false;
      bool IyYyVedydE = false;
      bool rKbTZKwpsA = false;
      bool RkTVGPsIUA = false;
      bool StzjQoHBCQ = false;
      bool CZlTTpmPEc = false;
      string baOJslDxKp;
      string mpJpPxjGsx;
      string eNCHjyGsWK;
      string VKhFGBOrEV;
      string jhSGsNmEmi;
      string zAaQrNYGZu;
      string eJaAUbHEiO;
      string hqCWMxtuOV;
      string LCFnKViRMr;
      string bISIqZHSlQ;
      string FhUYAHxDDt;
      string SdrDjbDlpz;
      string rpqqlZYsfm;
      string pbIxQchgnC;
      string XfOSYyQOXO;
      string VUbmXPqclZ;
      string iDWQEpUtmH;
      string tWxmaMaYRn;
      string JJVRQUAVZA;
      string kEtNSTIyNi;
      if(baOJslDxKp == FhUYAHxDDt){dVbQTzWnLL = true;}
      else if(FhUYAHxDDt == baOJslDxKp){IPHUCIxPtM = true;}
      if(mpJpPxjGsx == SdrDjbDlpz){nSLyPYhEzi = true;}
      else if(SdrDjbDlpz == mpJpPxjGsx){quOogpBshI = true;}
      if(eNCHjyGsWK == rpqqlZYsfm){pyTlWpbjUH = true;}
      else if(rpqqlZYsfm == eNCHjyGsWK){edlIqxQlmZ = true;}
      if(VKhFGBOrEV == pbIxQchgnC){DcKiKmhFyR = true;}
      else if(pbIxQchgnC == VKhFGBOrEV){mfzYugYQYM = true;}
      if(jhSGsNmEmi == XfOSYyQOXO){yLKOMRswxs = true;}
      else if(XfOSYyQOXO == jhSGsNmEmi){BOjdnpeWmD = true;}
      if(zAaQrNYGZu == VUbmXPqclZ){lEyereBosd = true;}
      else if(VUbmXPqclZ == zAaQrNYGZu){IyYyVedydE = true;}
      if(eJaAUbHEiO == iDWQEpUtmH){WmTDHKIcnc = true;}
      else if(iDWQEpUtmH == eJaAUbHEiO){rKbTZKwpsA = true;}
      if(hqCWMxtuOV == tWxmaMaYRn){qcGhkemFZE = true;}
      if(LCFnKViRMr == JJVRQUAVZA){wflaVzeepe = true;}
      if(bISIqZHSlQ == kEtNSTIyNi){lsLTtKqGGB = true;}
      while(tWxmaMaYRn == hqCWMxtuOV){RkTVGPsIUA = true;}
      while(JJVRQUAVZA == JJVRQUAVZA){StzjQoHBCQ = true;}
      while(kEtNSTIyNi == kEtNSTIyNi){CZlTTpmPEc = true;}
      if(dVbQTzWnLL == true){dVbQTzWnLL = false;}
      if(nSLyPYhEzi == true){nSLyPYhEzi = false;}
      if(pyTlWpbjUH == true){pyTlWpbjUH = false;}
      if(DcKiKmhFyR == true){DcKiKmhFyR = false;}
      if(yLKOMRswxs == true){yLKOMRswxs = false;}
      if(lEyereBosd == true){lEyereBosd = false;}
      if(WmTDHKIcnc == true){WmTDHKIcnc = false;}
      if(qcGhkemFZE == true){qcGhkemFZE = false;}
      if(wflaVzeepe == true){wflaVzeepe = false;}
      if(lsLTtKqGGB == true){lsLTtKqGGB = false;}
      if(IPHUCIxPtM == true){IPHUCIxPtM = false;}
      if(quOogpBshI == true){quOogpBshI = false;}
      if(edlIqxQlmZ == true){edlIqxQlmZ = false;}
      if(mfzYugYQYM == true){mfzYugYQYM = false;}
      if(BOjdnpeWmD == true){BOjdnpeWmD = false;}
      if(IyYyVedydE == true){IyYyVedydE = false;}
      if(rKbTZKwpsA == true){rKbTZKwpsA = false;}
      if(RkTVGPsIUA == true){RkTVGPsIUA = false;}
      if(StzjQoHBCQ == true){StzjQoHBCQ = false;}
      if(CZlTTpmPEc == true){CZlTTpmPEc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRJABWFPBS
{ 
  void BDexBnMOKI()
  { 
      bool jAWhbFtFwn = false;
      bool ZlleSaPFTO = false;
      bool EeKSpzpCIR = false;
      bool XNUyxjqzLh = false;
      bool QKTcDWQyWd = false;
      bool qknuXFpErc = false;
      bool OqxePMQmhh = false;
      bool iPslytKgPS = false;
      bool hrfdamYZaq = false;
      bool tmGiTYMoNp = false;
      bool GcPntarCwc = false;
      bool tInZtVLSEc = false;
      bool nqLqnwJJSY = false;
      bool gVTYMFbqiz = false;
      bool uVcywkygox = false;
      bool NtkjCOQYAy = false;
      bool RhjWuYoONo = false;
      bool sTiEgRNNtD = false;
      bool xcUULmkiWx = false;
      bool nDqkgNlFCX = false;
      string uysutmrAry;
      string OVVDHcsQaH;
      string jYeYOLSRIO;
      string DSzzZgrVqO;
      string KPIsAFDPBA;
      string ulWPrVTUfi;
      string TardtwVWca;
      string jWYMwUPkYJ;
      string HCQHTRuiHD;
      string NXoIujWezD;
      string igmZPXNKTW;
      string FhwWaRKjKc;
      string AlPYNMhPRM;
      string xklUZaPpru;
      string EkPjxfbShc;
      string YlUVDwRNMD;
      string pxsHZUuawz;
      string BTrOYPVeag;
      string jOhnmKPQQc;
      string JCcoFGqIJc;
      if(uysutmrAry == igmZPXNKTW){jAWhbFtFwn = true;}
      else if(igmZPXNKTW == uysutmrAry){GcPntarCwc = true;}
      if(OVVDHcsQaH == FhwWaRKjKc){ZlleSaPFTO = true;}
      else if(FhwWaRKjKc == OVVDHcsQaH){tInZtVLSEc = true;}
      if(jYeYOLSRIO == AlPYNMhPRM){EeKSpzpCIR = true;}
      else if(AlPYNMhPRM == jYeYOLSRIO){nqLqnwJJSY = true;}
      if(DSzzZgrVqO == xklUZaPpru){XNUyxjqzLh = true;}
      else if(xklUZaPpru == DSzzZgrVqO){gVTYMFbqiz = true;}
      if(KPIsAFDPBA == EkPjxfbShc){QKTcDWQyWd = true;}
      else if(EkPjxfbShc == KPIsAFDPBA){uVcywkygox = true;}
      if(ulWPrVTUfi == YlUVDwRNMD){qknuXFpErc = true;}
      else if(YlUVDwRNMD == ulWPrVTUfi){NtkjCOQYAy = true;}
      if(TardtwVWca == pxsHZUuawz){OqxePMQmhh = true;}
      else if(pxsHZUuawz == TardtwVWca){RhjWuYoONo = true;}
      if(jWYMwUPkYJ == BTrOYPVeag){iPslytKgPS = true;}
      if(HCQHTRuiHD == jOhnmKPQQc){hrfdamYZaq = true;}
      if(NXoIujWezD == JCcoFGqIJc){tmGiTYMoNp = true;}
      while(BTrOYPVeag == jWYMwUPkYJ){sTiEgRNNtD = true;}
      while(jOhnmKPQQc == jOhnmKPQQc){xcUULmkiWx = true;}
      while(JCcoFGqIJc == JCcoFGqIJc){nDqkgNlFCX = true;}
      if(jAWhbFtFwn == true){jAWhbFtFwn = false;}
      if(ZlleSaPFTO == true){ZlleSaPFTO = false;}
      if(EeKSpzpCIR == true){EeKSpzpCIR = false;}
      if(XNUyxjqzLh == true){XNUyxjqzLh = false;}
      if(QKTcDWQyWd == true){QKTcDWQyWd = false;}
      if(qknuXFpErc == true){qknuXFpErc = false;}
      if(OqxePMQmhh == true){OqxePMQmhh = false;}
      if(iPslytKgPS == true){iPslytKgPS = false;}
      if(hrfdamYZaq == true){hrfdamYZaq = false;}
      if(tmGiTYMoNp == true){tmGiTYMoNp = false;}
      if(GcPntarCwc == true){GcPntarCwc = false;}
      if(tInZtVLSEc == true){tInZtVLSEc = false;}
      if(nqLqnwJJSY == true){nqLqnwJJSY = false;}
      if(gVTYMFbqiz == true){gVTYMFbqiz = false;}
      if(uVcywkygox == true){uVcywkygox = false;}
      if(NtkjCOQYAy == true){NtkjCOQYAy = false;}
      if(RhjWuYoONo == true){RhjWuYoONo = false;}
      if(sTiEgRNNtD == true){sTiEgRNNtD = false;}
      if(xcUULmkiWx == true){xcUULmkiWx = false;}
      if(nDqkgNlFCX == true){nDqkgNlFCX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DGEBWYQYYU
{ 
  void JEVzyanJsj()
  { 
      bool TGbEoXJwsr = false;
      bool ZsTxtesyYN = false;
      bool JJaJrPfwxX = false;
      bool EfGGmmXzEn = false;
      bool CMcOUeJsRi = false;
      bool uBfjVJeRMZ = false;
      bool qMyVntlMJH = false;
      bool HttkKxgMoM = false;
      bool GmeOcCzWkc = false;
      bool HFmewpNGZZ = false;
      bool swiKbBHtYY = false;
      bool bSczSDgjrk = false;
      bool tPbgzCGPoU = false;
      bool iZlOTJEUma = false;
      bool tExLBnbmLr = false;
      bool IdNnecUBKY = false;
      bool trFEoBgOeJ = false;
      bool zMxRppSPfK = false;
      bool ZTDwLFLxiq = false;
      bool oCJNgCyrVz = false;
      string SuwxHfBdyd;
      string aBpNUXWdsy;
      string NDBHrXffyn;
      string TQqmwEPxsI;
      string fGXQGybGbd;
      string jIDJKPtnFi;
      string AUeJKKKDQQ;
      string IYjjRGfjAt;
      string uYEUEKMhbg;
      string KarJILbNGw;
      string mYpKULXTqE;
      string jJmLnaQJFz;
      string ybbjGgfaaG;
      string eRcEGVitAs;
      string lspWxAngVg;
      string tSIGxLxFDm;
      string exrkZRfhER;
      string rWJMMFkElG;
      string szEsLLIWHu;
      string YcpMOoAFxe;
      if(SuwxHfBdyd == mYpKULXTqE){TGbEoXJwsr = true;}
      else if(mYpKULXTqE == SuwxHfBdyd){swiKbBHtYY = true;}
      if(aBpNUXWdsy == jJmLnaQJFz){ZsTxtesyYN = true;}
      else if(jJmLnaQJFz == aBpNUXWdsy){bSczSDgjrk = true;}
      if(NDBHrXffyn == ybbjGgfaaG){JJaJrPfwxX = true;}
      else if(ybbjGgfaaG == NDBHrXffyn){tPbgzCGPoU = true;}
      if(TQqmwEPxsI == eRcEGVitAs){EfGGmmXzEn = true;}
      else if(eRcEGVitAs == TQqmwEPxsI){iZlOTJEUma = true;}
      if(fGXQGybGbd == lspWxAngVg){CMcOUeJsRi = true;}
      else if(lspWxAngVg == fGXQGybGbd){tExLBnbmLr = true;}
      if(jIDJKPtnFi == tSIGxLxFDm){uBfjVJeRMZ = true;}
      else if(tSIGxLxFDm == jIDJKPtnFi){IdNnecUBKY = true;}
      if(AUeJKKKDQQ == exrkZRfhER){qMyVntlMJH = true;}
      else if(exrkZRfhER == AUeJKKKDQQ){trFEoBgOeJ = true;}
      if(IYjjRGfjAt == rWJMMFkElG){HttkKxgMoM = true;}
      if(uYEUEKMhbg == szEsLLIWHu){GmeOcCzWkc = true;}
      if(KarJILbNGw == YcpMOoAFxe){HFmewpNGZZ = true;}
      while(rWJMMFkElG == IYjjRGfjAt){zMxRppSPfK = true;}
      while(szEsLLIWHu == szEsLLIWHu){ZTDwLFLxiq = true;}
      while(YcpMOoAFxe == YcpMOoAFxe){oCJNgCyrVz = true;}
      if(TGbEoXJwsr == true){TGbEoXJwsr = false;}
      if(ZsTxtesyYN == true){ZsTxtesyYN = false;}
      if(JJaJrPfwxX == true){JJaJrPfwxX = false;}
      if(EfGGmmXzEn == true){EfGGmmXzEn = false;}
      if(CMcOUeJsRi == true){CMcOUeJsRi = false;}
      if(uBfjVJeRMZ == true){uBfjVJeRMZ = false;}
      if(qMyVntlMJH == true){qMyVntlMJH = false;}
      if(HttkKxgMoM == true){HttkKxgMoM = false;}
      if(GmeOcCzWkc == true){GmeOcCzWkc = false;}
      if(HFmewpNGZZ == true){HFmewpNGZZ = false;}
      if(swiKbBHtYY == true){swiKbBHtYY = false;}
      if(bSczSDgjrk == true){bSczSDgjrk = false;}
      if(tPbgzCGPoU == true){tPbgzCGPoU = false;}
      if(iZlOTJEUma == true){iZlOTJEUma = false;}
      if(tExLBnbmLr == true){tExLBnbmLr = false;}
      if(IdNnecUBKY == true){IdNnecUBKY = false;}
      if(trFEoBgOeJ == true){trFEoBgOeJ = false;}
      if(zMxRppSPfK == true){zMxRppSPfK = false;}
      if(ZTDwLFLxiq == true){ZTDwLFLxiq = false;}
      if(oCJNgCyrVz == true){oCJNgCyrVz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GLJRHRKXAZ
{ 
  void mXaiGsCFGQ()
  { 
      bool uQkPcazSMF = false;
      bool AoysfEHSGg = false;
      bool hFDOKRMNLe = false;
      bool GnKJdYCWAW = false;
      bool odburZTSWT = false;
      bool PwCSbpMVEL = false;
      bool NlHhyMdoPG = false;
      bool CjRjqEdHVj = false;
      bool ytprPKlrgn = false;
      bool LfSoJDWswf = false;
      bool udDQQeeRbX = false;
      bool MEzTMSwORn = false;
      bool alHbtVRban = false;
      bool gjLpoTqYak = false;
      bool fTQIbHgybp = false;
      bool GHbIFJWaVu = false;
      bool MCpnpbsJes = false;
      bool bWmfHGVzAm = false;
      bool oTAkgZHCje = false;
      bool wPCfXdcbRz = false;
      string XQnjxEaqRY;
      string pwUfgcMasg;
      string OpdXjKUEwf;
      string RLVnCbRpSS;
      string cBnpmjNGnq;
      string sdNFoglQzm;
      string jVukGeafdF;
      string KWHZEMCmjA;
      string xNPElmyPzU;
      string oAqfiGGCiI;
      string JgcifWVmBc;
      string eyfypVGpzT;
      string gLgJPKebqx;
      string GAEbqPkfYP;
      string QKNVopUroN;
      string AQCPayASTV;
      string qtwEWetEHZ;
      string jZQjCVxKTZ;
      string omldxoxoAs;
      string PSMDXWOJzK;
      if(XQnjxEaqRY == JgcifWVmBc){uQkPcazSMF = true;}
      else if(JgcifWVmBc == XQnjxEaqRY){udDQQeeRbX = true;}
      if(pwUfgcMasg == eyfypVGpzT){AoysfEHSGg = true;}
      else if(eyfypVGpzT == pwUfgcMasg){MEzTMSwORn = true;}
      if(OpdXjKUEwf == gLgJPKebqx){hFDOKRMNLe = true;}
      else if(gLgJPKebqx == OpdXjKUEwf){alHbtVRban = true;}
      if(RLVnCbRpSS == GAEbqPkfYP){GnKJdYCWAW = true;}
      else if(GAEbqPkfYP == RLVnCbRpSS){gjLpoTqYak = true;}
      if(cBnpmjNGnq == QKNVopUroN){odburZTSWT = true;}
      else if(QKNVopUroN == cBnpmjNGnq){fTQIbHgybp = true;}
      if(sdNFoglQzm == AQCPayASTV){PwCSbpMVEL = true;}
      else if(AQCPayASTV == sdNFoglQzm){GHbIFJWaVu = true;}
      if(jVukGeafdF == qtwEWetEHZ){NlHhyMdoPG = true;}
      else if(qtwEWetEHZ == jVukGeafdF){MCpnpbsJes = true;}
      if(KWHZEMCmjA == jZQjCVxKTZ){CjRjqEdHVj = true;}
      if(xNPElmyPzU == omldxoxoAs){ytprPKlrgn = true;}
      if(oAqfiGGCiI == PSMDXWOJzK){LfSoJDWswf = true;}
      while(jZQjCVxKTZ == KWHZEMCmjA){bWmfHGVzAm = true;}
      while(omldxoxoAs == omldxoxoAs){oTAkgZHCje = true;}
      while(PSMDXWOJzK == PSMDXWOJzK){wPCfXdcbRz = true;}
      if(uQkPcazSMF == true){uQkPcazSMF = false;}
      if(AoysfEHSGg == true){AoysfEHSGg = false;}
      if(hFDOKRMNLe == true){hFDOKRMNLe = false;}
      if(GnKJdYCWAW == true){GnKJdYCWAW = false;}
      if(odburZTSWT == true){odburZTSWT = false;}
      if(PwCSbpMVEL == true){PwCSbpMVEL = false;}
      if(NlHhyMdoPG == true){NlHhyMdoPG = false;}
      if(CjRjqEdHVj == true){CjRjqEdHVj = false;}
      if(ytprPKlrgn == true){ytprPKlrgn = false;}
      if(LfSoJDWswf == true){LfSoJDWswf = false;}
      if(udDQQeeRbX == true){udDQQeeRbX = false;}
      if(MEzTMSwORn == true){MEzTMSwORn = false;}
      if(alHbtVRban == true){alHbtVRban = false;}
      if(gjLpoTqYak == true){gjLpoTqYak = false;}
      if(fTQIbHgybp == true){fTQIbHgybp = false;}
      if(GHbIFJWaVu == true){GHbIFJWaVu = false;}
      if(MCpnpbsJes == true){MCpnpbsJes = false;}
      if(bWmfHGVzAm == true){bWmfHGVzAm = false;}
      if(oTAkgZHCje == true){oTAkgZHCje = false;}
      if(wPCfXdcbRz == true){wPCfXdcbRz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVDTKSNUOL
{ 
  void QAoussxLTi()
  { 
      bool kocyYdHdDV = false;
      bool OptezIiWIb = false;
      bool OsfZNZHrIJ = false;
      bool KdaXPFVrgZ = false;
      bool pSHTtUxTgX = false;
      bool nuhGLrJDkz = false;
      bool WPUsLkOWOs = false;
      bool lpphlulLer = false;
      bool bmKjVPuULX = false;
      bool wSHgDayNIJ = false;
      bool GaFnlxEAUQ = false;
      bool FxXrXiFjXu = false;
      bool ptKqwTiIeL = false;
      bool xYDVlAhVyX = false;
      bool KtzuRztOJU = false;
      bool UNoMSLPNrR = false;
      bool OwVJSgsCGW = false;
      bool AikAkuuPYw = false;
      bool YUyJpjipCZ = false;
      bool kUdfIOYpbk = false;
      string uAuKyPtkSJ;
      string fpBIiYSCGT;
      string PCnYheuGJd;
      string wmPWHBsRdO;
      string JHmcNhyfEf;
      string ULSLLrLVbT;
      string TmbnNradAg;
      string eBXrKIPKKz;
      string gPCcIjUDLP;
      string pWoKtVeyOV;
      string GTeWBTmZAC;
      string cALclDkzed;
      string WWSkqHLNxn;
      string cQwosMkeao;
      string wtCIlpLMXq;
      string jfTkyiBsft;
      string HYcMZLEWiY;
      string RGXpgcTKyB;
      string uzpGDxxKpJ;
      string LryfgWRpia;
      if(uAuKyPtkSJ == GTeWBTmZAC){kocyYdHdDV = true;}
      else if(GTeWBTmZAC == uAuKyPtkSJ){GaFnlxEAUQ = true;}
      if(fpBIiYSCGT == cALclDkzed){OptezIiWIb = true;}
      else if(cALclDkzed == fpBIiYSCGT){FxXrXiFjXu = true;}
      if(PCnYheuGJd == WWSkqHLNxn){OsfZNZHrIJ = true;}
      else if(WWSkqHLNxn == PCnYheuGJd){ptKqwTiIeL = true;}
      if(wmPWHBsRdO == cQwosMkeao){KdaXPFVrgZ = true;}
      else if(cQwosMkeao == wmPWHBsRdO){xYDVlAhVyX = true;}
      if(JHmcNhyfEf == wtCIlpLMXq){pSHTtUxTgX = true;}
      else if(wtCIlpLMXq == JHmcNhyfEf){KtzuRztOJU = true;}
      if(ULSLLrLVbT == jfTkyiBsft){nuhGLrJDkz = true;}
      else if(jfTkyiBsft == ULSLLrLVbT){UNoMSLPNrR = true;}
      if(TmbnNradAg == HYcMZLEWiY){WPUsLkOWOs = true;}
      else if(HYcMZLEWiY == TmbnNradAg){OwVJSgsCGW = true;}
      if(eBXrKIPKKz == RGXpgcTKyB){lpphlulLer = true;}
      if(gPCcIjUDLP == uzpGDxxKpJ){bmKjVPuULX = true;}
      if(pWoKtVeyOV == LryfgWRpia){wSHgDayNIJ = true;}
      while(RGXpgcTKyB == eBXrKIPKKz){AikAkuuPYw = true;}
      while(uzpGDxxKpJ == uzpGDxxKpJ){YUyJpjipCZ = true;}
      while(LryfgWRpia == LryfgWRpia){kUdfIOYpbk = true;}
      if(kocyYdHdDV == true){kocyYdHdDV = false;}
      if(OptezIiWIb == true){OptezIiWIb = false;}
      if(OsfZNZHrIJ == true){OsfZNZHrIJ = false;}
      if(KdaXPFVrgZ == true){KdaXPFVrgZ = false;}
      if(pSHTtUxTgX == true){pSHTtUxTgX = false;}
      if(nuhGLrJDkz == true){nuhGLrJDkz = false;}
      if(WPUsLkOWOs == true){WPUsLkOWOs = false;}
      if(lpphlulLer == true){lpphlulLer = false;}
      if(bmKjVPuULX == true){bmKjVPuULX = false;}
      if(wSHgDayNIJ == true){wSHgDayNIJ = false;}
      if(GaFnlxEAUQ == true){GaFnlxEAUQ = false;}
      if(FxXrXiFjXu == true){FxXrXiFjXu = false;}
      if(ptKqwTiIeL == true){ptKqwTiIeL = false;}
      if(xYDVlAhVyX == true){xYDVlAhVyX = false;}
      if(KtzuRztOJU == true){KtzuRztOJU = false;}
      if(UNoMSLPNrR == true){UNoMSLPNrR = false;}
      if(OwVJSgsCGW == true){OwVJSgsCGW = false;}
      if(AikAkuuPYw == true){AikAkuuPYw = false;}
      if(YUyJpjipCZ == true){YUyJpjipCZ = false;}
      if(kUdfIOYpbk == true){kUdfIOYpbk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTCHKISUCX
{ 
  void ndnWYMyHhr()
  { 
      bool CkYhoRuSnx = false;
      bool YhrQkUHzDl = false;
      bool WXZwigpEId = false;
      bool koXEwbNISc = false;
      bool pXoIqEdrrK = false;
      bool AOJzMdLczH = false;
      bool apJKMiKmUI = false;
      bool GygauziRFd = false;
      bool DxLycWeXqR = false;
      bool QkJLBANdwH = false;
      bool tpXjDChiEN = false;
      bool usXUDceLho = false;
      bool EluCrVoUZu = false;
      bool kEUxjMZbta = false;
      bool owTdVWMnHX = false;
      bool UCwGCHuUqh = false;
      bool MMJIbqXZkq = false;
      bool DDQGAISRgU = false;
      bool JANBZiHOtc = false;
      bool RFjMNclKBe = false;
      string GKctyGpdLc;
      string ZLxxBeqkSI;
      string DMgcHLgYOP;
      string lediCnzcoV;
      string HCeJKYXMfI;
      string unDJmsczmm;
      string ZRPwpuhOtN;
      string eOwwBBgWRh;
      string mUrFTybTuI;
      string KzoCwpmiSP;
      string pJRSdgrGIl;
      string LGhEzEYJbr;
      string TOSlCeYtzK;
      string OyEBrdCYbm;
      string GUKJxERkDq;
      string QcHawbqfPy;
      string HyHxXNBfLU;
      string CzhnlyDJny;
      string NmpHtkpdFP;
      string lVJdeINNlj;
      if(GKctyGpdLc == pJRSdgrGIl){CkYhoRuSnx = true;}
      else if(pJRSdgrGIl == GKctyGpdLc){tpXjDChiEN = true;}
      if(ZLxxBeqkSI == LGhEzEYJbr){YhrQkUHzDl = true;}
      else if(LGhEzEYJbr == ZLxxBeqkSI){usXUDceLho = true;}
      if(DMgcHLgYOP == TOSlCeYtzK){WXZwigpEId = true;}
      else if(TOSlCeYtzK == DMgcHLgYOP){EluCrVoUZu = true;}
      if(lediCnzcoV == OyEBrdCYbm){koXEwbNISc = true;}
      else if(OyEBrdCYbm == lediCnzcoV){kEUxjMZbta = true;}
      if(HCeJKYXMfI == GUKJxERkDq){pXoIqEdrrK = true;}
      else if(GUKJxERkDq == HCeJKYXMfI){owTdVWMnHX = true;}
      if(unDJmsczmm == QcHawbqfPy){AOJzMdLczH = true;}
      else if(QcHawbqfPy == unDJmsczmm){UCwGCHuUqh = true;}
      if(ZRPwpuhOtN == HyHxXNBfLU){apJKMiKmUI = true;}
      else if(HyHxXNBfLU == ZRPwpuhOtN){MMJIbqXZkq = true;}
      if(eOwwBBgWRh == CzhnlyDJny){GygauziRFd = true;}
      if(mUrFTybTuI == NmpHtkpdFP){DxLycWeXqR = true;}
      if(KzoCwpmiSP == lVJdeINNlj){QkJLBANdwH = true;}
      while(CzhnlyDJny == eOwwBBgWRh){DDQGAISRgU = true;}
      while(NmpHtkpdFP == NmpHtkpdFP){JANBZiHOtc = true;}
      while(lVJdeINNlj == lVJdeINNlj){RFjMNclKBe = true;}
      if(CkYhoRuSnx == true){CkYhoRuSnx = false;}
      if(YhrQkUHzDl == true){YhrQkUHzDl = false;}
      if(WXZwigpEId == true){WXZwigpEId = false;}
      if(koXEwbNISc == true){koXEwbNISc = false;}
      if(pXoIqEdrrK == true){pXoIqEdrrK = false;}
      if(AOJzMdLczH == true){AOJzMdLczH = false;}
      if(apJKMiKmUI == true){apJKMiKmUI = false;}
      if(GygauziRFd == true){GygauziRFd = false;}
      if(DxLycWeXqR == true){DxLycWeXqR = false;}
      if(QkJLBANdwH == true){QkJLBANdwH = false;}
      if(tpXjDChiEN == true){tpXjDChiEN = false;}
      if(usXUDceLho == true){usXUDceLho = false;}
      if(EluCrVoUZu == true){EluCrVoUZu = false;}
      if(kEUxjMZbta == true){kEUxjMZbta = false;}
      if(owTdVWMnHX == true){owTdVWMnHX = false;}
      if(UCwGCHuUqh == true){UCwGCHuUqh = false;}
      if(MMJIbqXZkq == true){MMJIbqXZkq = false;}
      if(DDQGAISRgU == true){DDQGAISRgU = false;}
      if(JANBZiHOtc == true){JANBZiHOtc = false;}
      if(RFjMNclKBe == true){RFjMNclKBe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVREZOQIFE
{ 
  void yEgbxQNRno()
  { 
      bool oKxRSrciBc = false;
      bool WrCyHVWCcc = false;
      bool rTgIgseYra = false;
      bool SmkAhPwJrh = false;
      bool fWQLyfjMBd = false;
      bool PIlclVdojZ = false;
      bool NEqaKiHBPr = false;
      bool YNKtwUCVJA = false;
      bool IRWNKJBHOL = false;
      bool lHYRUbepAP = false;
      bool YhwJECyqgR = false;
      bool SHfiQugcPA = false;
      bool hAmEFRnrZT = false;
      bool oMUtbZVNIH = false;
      bool LJZwrdbpAY = false;
      bool uCZzhXurDm = false;
      bool OFRMbGlkGq = false;
      bool ZSUIoXZpLb = false;
      bool pxrAYmmVMD = false;
      bool ecKVsGqMUl = false;
      string LzYoOcmdYw;
      string cDtZwRhNVr;
      string yNmGdZROXN;
      string PeEMHEOLbL;
      string dqusEqzHMq;
      string JhiaNyLSLo;
      string KYGLfxygRq;
      string CWlKNGRtCm;
      string ZKBfDgwdzJ;
      string rwAmAEkjNH;
      string rRpUnmwXMG;
      string gRPXOAWZIy;
      string BThIyGWyKI;
      string UhgttIUgqQ;
      string kXRrcafbXz;
      string hLaOGYihVh;
      string QxNDlykVdG;
      string fohrNcBpeX;
      string ZtaLaJGRnV;
      string YmKJzmKOFd;
      if(LzYoOcmdYw == rRpUnmwXMG){oKxRSrciBc = true;}
      else if(rRpUnmwXMG == LzYoOcmdYw){YhwJECyqgR = true;}
      if(cDtZwRhNVr == gRPXOAWZIy){WrCyHVWCcc = true;}
      else if(gRPXOAWZIy == cDtZwRhNVr){SHfiQugcPA = true;}
      if(yNmGdZROXN == BThIyGWyKI){rTgIgseYra = true;}
      else if(BThIyGWyKI == yNmGdZROXN){hAmEFRnrZT = true;}
      if(PeEMHEOLbL == UhgttIUgqQ){SmkAhPwJrh = true;}
      else if(UhgttIUgqQ == PeEMHEOLbL){oMUtbZVNIH = true;}
      if(dqusEqzHMq == kXRrcafbXz){fWQLyfjMBd = true;}
      else if(kXRrcafbXz == dqusEqzHMq){LJZwrdbpAY = true;}
      if(JhiaNyLSLo == hLaOGYihVh){PIlclVdojZ = true;}
      else if(hLaOGYihVh == JhiaNyLSLo){uCZzhXurDm = true;}
      if(KYGLfxygRq == QxNDlykVdG){NEqaKiHBPr = true;}
      else if(QxNDlykVdG == KYGLfxygRq){OFRMbGlkGq = true;}
      if(CWlKNGRtCm == fohrNcBpeX){YNKtwUCVJA = true;}
      if(ZKBfDgwdzJ == ZtaLaJGRnV){IRWNKJBHOL = true;}
      if(rwAmAEkjNH == YmKJzmKOFd){lHYRUbepAP = true;}
      while(fohrNcBpeX == CWlKNGRtCm){ZSUIoXZpLb = true;}
      while(ZtaLaJGRnV == ZtaLaJGRnV){pxrAYmmVMD = true;}
      while(YmKJzmKOFd == YmKJzmKOFd){ecKVsGqMUl = true;}
      if(oKxRSrciBc == true){oKxRSrciBc = false;}
      if(WrCyHVWCcc == true){WrCyHVWCcc = false;}
      if(rTgIgseYra == true){rTgIgseYra = false;}
      if(SmkAhPwJrh == true){SmkAhPwJrh = false;}
      if(fWQLyfjMBd == true){fWQLyfjMBd = false;}
      if(PIlclVdojZ == true){PIlclVdojZ = false;}
      if(NEqaKiHBPr == true){NEqaKiHBPr = false;}
      if(YNKtwUCVJA == true){YNKtwUCVJA = false;}
      if(IRWNKJBHOL == true){IRWNKJBHOL = false;}
      if(lHYRUbepAP == true){lHYRUbepAP = false;}
      if(YhwJECyqgR == true){YhwJECyqgR = false;}
      if(SHfiQugcPA == true){SHfiQugcPA = false;}
      if(hAmEFRnrZT == true){hAmEFRnrZT = false;}
      if(oMUtbZVNIH == true){oMUtbZVNIH = false;}
      if(LJZwrdbpAY == true){LJZwrdbpAY = false;}
      if(uCZzhXurDm == true){uCZzhXurDm = false;}
      if(OFRMbGlkGq == true){OFRMbGlkGq = false;}
      if(ZSUIoXZpLb == true){ZSUIoXZpLb = false;}
      if(pxrAYmmVMD == true){pxrAYmmVMD = false;}
      if(ecKVsGqMUl == true){ecKVsGqMUl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEHHDAINKZ
{ 
  void kWGPOLVUpG()
  { 
      bool TIkcNaWPmM = false;
      bool SwrCyxZGuY = false;
      bool ncyaljiPPf = false;
      bool OQbeFFbChp = false;
      bool bzshEXZOxM = false;
      bool buNOXpJKqc = false;
      bool rHAHyCTNxr = false;
      bool UXXFxnjQVO = false;
      bool JURDDSDMGO = false;
      bool wRKEyTzkjC = false;
      bool DMQFqEWHRi = false;
      bool GsncTWowEe = false;
      bool zGGiwDNSGc = false;
      bool oyfTKxDMLy = false;
      bool uuuWHDchka = false;
      bool eCgECwGhIn = false;
      bool qEAntIMTRW = false;
      bool TckFjELias = false;
      bool ZehfymQaRN = false;
      bool pVDWHqtGcz = false;
      string BXFiWPKDID;
      string IQHBIyNSGx;
      string rBwNPLPszi;
      string iRsKWQMRgW;
      string kHKgoLmUVO;
      string EFyRqzaqSK;
      string AQEYTpWwdr;
      string lwkiMkqOXE;
      string XtWjdcTaSX;
      string oUyVWTCkMz;
      string npqdbIUOFG;
      string ILSOmGsTuq;
      string VudGCQxOMr;
      string hFCYPgDsIU;
      string IEVMOcCjiQ;
      string aipVdrMjbL;
      string KFCMXCJtyF;
      string CALZhQZQqY;
      string NNewQzOguX;
      string TSQwJCCInL;
      if(BXFiWPKDID == npqdbIUOFG){TIkcNaWPmM = true;}
      else if(npqdbIUOFG == BXFiWPKDID){DMQFqEWHRi = true;}
      if(IQHBIyNSGx == ILSOmGsTuq){SwrCyxZGuY = true;}
      else if(ILSOmGsTuq == IQHBIyNSGx){GsncTWowEe = true;}
      if(rBwNPLPszi == VudGCQxOMr){ncyaljiPPf = true;}
      else if(VudGCQxOMr == rBwNPLPszi){zGGiwDNSGc = true;}
      if(iRsKWQMRgW == hFCYPgDsIU){OQbeFFbChp = true;}
      else if(hFCYPgDsIU == iRsKWQMRgW){oyfTKxDMLy = true;}
      if(kHKgoLmUVO == IEVMOcCjiQ){bzshEXZOxM = true;}
      else if(IEVMOcCjiQ == kHKgoLmUVO){uuuWHDchka = true;}
      if(EFyRqzaqSK == aipVdrMjbL){buNOXpJKqc = true;}
      else if(aipVdrMjbL == EFyRqzaqSK){eCgECwGhIn = true;}
      if(AQEYTpWwdr == KFCMXCJtyF){rHAHyCTNxr = true;}
      else if(KFCMXCJtyF == AQEYTpWwdr){qEAntIMTRW = true;}
      if(lwkiMkqOXE == CALZhQZQqY){UXXFxnjQVO = true;}
      if(XtWjdcTaSX == NNewQzOguX){JURDDSDMGO = true;}
      if(oUyVWTCkMz == TSQwJCCInL){wRKEyTzkjC = true;}
      while(CALZhQZQqY == lwkiMkqOXE){TckFjELias = true;}
      while(NNewQzOguX == NNewQzOguX){ZehfymQaRN = true;}
      while(TSQwJCCInL == TSQwJCCInL){pVDWHqtGcz = true;}
      if(TIkcNaWPmM == true){TIkcNaWPmM = false;}
      if(SwrCyxZGuY == true){SwrCyxZGuY = false;}
      if(ncyaljiPPf == true){ncyaljiPPf = false;}
      if(OQbeFFbChp == true){OQbeFFbChp = false;}
      if(bzshEXZOxM == true){bzshEXZOxM = false;}
      if(buNOXpJKqc == true){buNOXpJKqc = false;}
      if(rHAHyCTNxr == true){rHAHyCTNxr = false;}
      if(UXXFxnjQVO == true){UXXFxnjQVO = false;}
      if(JURDDSDMGO == true){JURDDSDMGO = false;}
      if(wRKEyTzkjC == true){wRKEyTzkjC = false;}
      if(DMQFqEWHRi == true){DMQFqEWHRi = false;}
      if(GsncTWowEe == true){GsncTWowEe = false;}
      if(zGGiwDNSGc == true){zGGiwDNSGc = false;}
      if(oyfTKxDMLy == true){oyfTKxDMLy = false;}
      if(uuuWHDchka == true){uuuWHDchka = false;}
      if(eCgECwGhIn == true){eCgECwGhIn = false;}
      if(qEAntIMTRW == true){qEAntIMTRW = false;}
      if(TckFjELias == true){TckFjELias = false;}
      if(ZehfymQaRN == true){ZehfymQaRN = false;}
      if(pVDWHqtGcz == true){pVDWHqtGcz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGKPOKMOIC
{ 
  void dHDTjypuSm()
  { 
      bool TFdHZHWBWG = false;
      bool kFHFZQrrxb = false;
      bool csMblLMUAW = false;
      bool IDKHxOWlDJ = false;
      bool KhShqPDKBZ = false;
      bool PwKYCasCUO = false;
      bool tBBzyguAHK = false;
      bool tFnnRtadjW = false;
      bool HCSZGMskEW = false;
      bool VUQoOJgSjJ = false;
      bool UDCqfJHWHI = false;
      bool AORyHrhasl = false;
      bool nJwkoZozYI = false;
      bool NItaBDzbtw = false;
      bool EWcuWGDShW = false;
      bool aFYxVKHRBG = false;
      bool UIxzurTpwD = false;
      bool sFgwgQfAOh = false;
      bool VWRCgHiwEq = false;
      bool wganbwYdAd = false;
      string jwglmhLFCS;
      string aXQOOcfFkt;
      string mVFhFOXRsw;
      string FICVySzojj;
      string szzndBkqmz;
      string oPzPyNpygY;
      string JtMGNRUuQu;
      string cpUBAmWREE;
      string cgdsGoJlWj;
      string bAILZzlsaL;
      string fpaqWyuyPK;
      string qYtbucPSzY;
      string IiXfTbgJaA;
      string AdqrYmGmWI;
      string sLWLsCGgPx;
      string jTsBDxRtWt;
      string RlWOJNhBDI;
      string WcwqexLLmR;
      string UAsdQgjoob;
      string VLPbqHnIBf;
      if(jwglmhLFCS == fpaqWyuyPK){TFdHZHWBWG = true;}
      else if(fpaqWyuyPK == jwglmhLFCS){UDCqfJHWHI = true;}
      if(aXQOOcfFkt == qYtbucPSzY){kFHFZQrrxb = true;}
      else if(qYtbucPSzY == aXQOOcfFkt){AORyHrhasl = true;}
      if(mVFhFOXRsw == IiXfTbgJaA){csMblLMUAW = true;}
      else if(IiXfTbgJaA == mVFhFOXRsw){nJwkoZozYI = true;}
      if(FICVySzojj == AdqrYmGmWI){IDKHxOWlDJ = true;}
      else if(AdqrYmGmWI == FICVySzojj){NItaBDzbtw = true;}
      if(szzndBkqmz == sLWLsCGgPx){KhShqPDKBZ = true;}
      else if(sLWLsCGgPx == szzndBkqmz){EWcuWGDShW = true;}
      if(oPzPyNpygY == jTsBDxRtWt){PwKYCasCUO = true;}
      else if(jTsBDxRtWt == oPzPyNpygY){aFYxVKHRBG = true;}
      if(JtMGNRUuQu == RlWOJNhBDI){tBBzyguAHK = true;}
      else if(RlWOJNhBDI == JtMGNRUuQu){UIxzurTpwD = true;}
      if(cpUBAmWREE == WcwqexLLmR){tFnnRtadjW = true;}
      if(cgdsGoJlWj == UAsdQgjoob){HCSZGMskEW = true;}
      if(bAILZzlsaL == VLPbqHnIBf){VUQoOJgSjJ = true;}
      while(WcwqexLLmR == cpUBAmWREE){sFgwgQfAOh = true;}
      while(UAsdQgjoob == UAsdQgjoob){VWRCgHiwEq = true;}
      while(VLPbqHnIBf == VLPbqHnIBf){wganbwYdAd = true;}
      if(TFdHZHWBWG == true){TFdHZHWBWG = false;}
      if(kFHFZQrrxb == true){kFHFZQrrxb = false;}
      if(csMblLMUAW == true){csMblLMUAW = false;}
      if(IDKHxOWlDJ == true){IDKHxOWlDJ = false;}
      if(KhShqPDKBZ == true){KhShqPDKBZ = false;}
      if(PwKYCasCUO == true){PwKYCasCUO = false;}
      if(tBBzyguAHK == true){tBBzyguAHK = false;}
      if(tFnnRtadjW == true){tFnnRtadjW = false;}
      if(HCSZGMskEW == true){HCSZGMskEW = false;}
      if(VUQoOJgSjJ == true){VUQoOJgSjJ = false;}
      if(UDCqfJHWHI == true){UDCqfJHWHI = false;}
      if(AORyHrhasl == true){AORyHrhasl = false;}
      if(nJwkoZozYI == true){nJwkoZozYI = false;}
      if(NItaBDzbtw == true){NItaBDzbtw = false;}
      if(EWcuWGDShW == true){EWcuWGDShW = false;}
      if(aFYxVKHRBG == true){aFYxVKHRBG = false;}
      if(UIxzurTpwD == true){UIxzurTpwD = false;}
      if(sFgwgQfAOh == true){sFgwgQfAOh = false;}
      if(VWRCgHiwEq == true){VWRCgHiwEq = false;}
      if(wganbwYdAd == true){wganbwYdAd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMSKIDDPJW
{ 
  void NQKbJTnhoH()
  { 
      bool iFXJNWYlVx = false;
      bool PiDxwthcZK = false;
      bool kWCHFNPgpf = false;
      bool YsnaGBJgll = false;
      bool yqEKJkhxbA = false;
      bool YVqpOMDPEA = false;
      bool GqwoXWubqt = false;
      bool kApmMtRqyT = false;
      bool eSFoGDBxLs = false;
      bool ysblfHtOll = false;
      bool pFGgPYeDdT = false;
      bool tLQkUmlGiU = false;
      bool VxQxwqXEHF = false;
      bool ADFMdZLXZh = false;
      bool XxSrzmcqQr = false;
      bool UmfQQroIkX = false;
      bool AawYTqFEGu = false;
      bool aNgAxXdXyI = false;
      bool OgmOjMXnuk = false;
      bool jDlBhwAtYH = false;
      string zVWQtONhMF;
      string ExHsdOarGc;
      string IDhiAiTdzV;
      string HoOPZypCOU;
      string KuWYjQplmy;
      string kcZpwunmQL;
      string ujiqxOhrSe;
      string YXckRNfJzi;
      string rhpBjePXSd;
      string KDlCZaMeaU;
      string iySIYMznYi;
      string PengTNshHS;
      string zJYoUVlaLp;
      string BAhdzsOhbW;
      string faziOeOFiL;
      string hdXIVZYdmD;
      string aYbhhOwJgZ;
      string yLFkmXJpZo;
      string GgqzIWcZHZ;
      string UkuYuGyQBz;
      if(zVWQtONhMF == iySIYMznYi){iFXJNWYlVx = true;}
      else if(iySIYMznYi == zVWQtONhMF){pFGgPYeDdT = true;}
      if(ExHsdOarGc == PengTNshHS){PiDxwthcZK = true;}
      else if(PengTNshHS == ExHsdOarGc){tLQkUmlGiU = true;}
      if(IDhiAiTdzV == zJYoUVlaLp){kWCHFNPgpf = true;}
      else if(zJYoUVlaLp == IDhiAiTdzV){VxQxwqXEHF = true;}
      if(HoOPZypCOU == BAhdzsOhbW){YsnaGBJgll = true;}
      else if(BAhdzsOhbW == HoOPZypCOU){ADFMdZLXZh = true;}
      if(KuWYjQplmy == faziOeOFiL){yqEKJkhxbA = true;}
      else if(faziOeOFiL == KuWYjQplmy){XxSrzmcqQr = true;}
      if(kcZpwunmQL == hdXIVZYdmD){YVqpOMDPEA = true;}
      else if(hdXIVZYdmD == kcZpwunmQL){UmfQQroIkX = true;}
      if(ujiqxOhrSe == aYbhhOwJgZ){GqwoXWubqt = true;}
      else if(aYbhhOwJgZ == ujiqxOhrSe){AawYTqFEGu = true;}
      if(YXckRNfJzi == yLFkmXJpZo){kApmMtRqyT = true;}
      if(rhpBjePXSd == GgqzIWcZHZ){eSFoGDBxLs = true;}
      if(KDlCZaMeaU == UkuYuGyQBz){ysblfHtOll = true;}
      while(yLFkmXJpZo == YXckRNfJzi){aNgAxXdXyI = true;}
      while(GgqzIWcZHZ == GgqzIWcZHZ){OgmOjMXnuk = true;}
      while(UkuYuGyQBz == UkuYuGyQBz){jDlBhwAtYH = true;}
      if(iFXJNWYlVx == true){iFXJNWYlVx = false;}
      if(PiDxwthcZK == true){PiDxwthcZK = false;}
      if(kWCHFNPgpf == true){kWCHFNPgpf = false;}
      if(YsnaGBJgll == true){YsnaGBJgll = false;}
      if(yqEKJkhxbA == true){yqEKJkhxbA = false;}
      if(YVqpOMDPEA == true){YVqpOMDPEA = false;}
      if(GqwoXWubqt == true){GqwoXWubqt = false;}
      if(kApmMtRqyT == true){kApmMtRqyT = false;}
      if(eSFoGDBxLs == true){eSFoGDBxLs = false;}
      if(ysblfHtOll == true){ysblfHtOll = false;}
      if(pFGgPYeDdT == true){pFGgPYeDdT = false;}
      if(tLQkUmlGiU == true){tLQkUmlGiU = false;}
      if(VxQxwqXEHF == true){VxQxwqXEHF = false;}
      if(ADFMdZLXZh == true){ADFMdZLXZh = false;}
      if(XxSrzmcqQr == true){XxSrzmcqQr = false;}
      if(UmfQQroIkX == true){UmfQQroIkX = false;}
      if(AawYTqFEGu == true){AawYTqFEGu = false;}
      if(aNgAxXdXyI == true){aNgAxXdXyI = false;}
      if(OgmOjMXnuk == true){OgmOjMXnuk = false;}
      if(jDlBhwAtYH == true){jDlBhwAtYH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICZLEWWKDW
{ 
  void ZMGaYtgRiX()
  { 
      bool FnynRtLTJs = false;
      bool QxSwnrYMnA = false;
      bool YyRKphRxWE = false;
      bool KeAnSoRiDM = false;
      bool eMVXQbblxF = false;
      bool xbuHnHWmyi = false;
      bool cNwFhkxddy = false;
      bool ZpIbVLcssO = false;
      bool FeARHijrAL = false;
      bool RejUiRQQoe = false;
      bool dxIyeGSSlc = false;
      bool dcsjcyMexz = false;
      bool BEdRfuGnsD = false;
      bool uMENjIVBlA = false;
      bool QQFXhokzqk = false;
      bool EkSpdYTqRi = false;
      bool AdZhgRYfAU = false;
      bool bKsxijzGjq = false;
      bool KGxHzJsOjL = false;
      bool oejCAlqXpQ = false;
      string ZCAjbwwQre;
      string SHyZIDxOky;
      string GINhonCEIr;
      string rZhRMTjsng;
      string soSRHztBTl;
      string UzDDrRoSun;
      string sqIAmsYgNn;
      string SEaDFQouZo;
      string sBkVWrWdZt;
      string eRxzmCfSeO;
      string aNmeSPYzya;
      string btsGurGlct;
      string VtHSJBGbQC;
      string jWPKNfOFCH;
      string TWfySjXpEu;
      string utojrfGTVR;
      string IxhupFdirP;
      string cAiVazOIAY;
      string dPXVHpgeRh;
      string YuikyWnjIM;
      if(ZCAjbwwQre == aNmeSPYzya){FnynRtLTJs = true;}
      else if(aNmeSPYzya == ZCAjbwwQre){dxIyeGSSlc = true;}
      if(SHyZIDxOky == btsGurGlct){QxSwnrYMnA = true;}
      else if(btsGurGlct == SHyZIDxOky){dcsjcyMexz = true;}
      if(GINhonCEIr == VtHSJBGbQC){YyRKphRxWE = true;}
      else if(VtHSJBGbQC == GINhonCEIr){BEdRfuGnsD = true;}
      if(rZhRMTjsng == jWPKNfOFCH){KeAnSoRiDM = true;}
      else if(jWPKNfOFCH == rZhRMTjsng){uMENjIVBlA = true;}
      if(soSRHztBTl == TWfySjXpEu){eMVXQbblxF = true;}
      else if(TWfySjXpEu == soSRHztBTl){QQFXhokzqk = true;}
      if(UzDDrRoSun == utojrfGTVR){xbuHnHWmyi = true;}
      else if(utojrfGTVR == UzDDrRoSun){EkSpdYTqRi = true;}
      if(sqIAmsYgNn == IxhupFdirP){cNwFhkxddy = true;}
      else if(IxhupFdirP == sqIAmsYgNn){AdZhgRYfAU = true;}
      if(SEaDFQouZo == cAiVazOIAY){ZpIbVLcssO = true;}
      if(sBkVWrWdZt == dPXVHpgeRh){FeARHijrAL = true;}
      if(eRxzmCfSeO == YuikyWnjIM){RejUiRQQoe = true;}
      while(cAiVazOIAY == SEaDFQouZo){bKsxijzGjq = true;}
      while(dPXVHpgeRh == dPXVHpgeRh){KGxHzJsOjL = true;}
      while(YuikyWnjIM == YuikyWnjIM){oejCAlqXpQ = true;}
      if(FnynRtLTJs == true){FnynRtLTJs = false;}
      if(QxSwnrYMnA == true){QxSwnrYMnA = false;}
      if(YyRKphRxWE == true){YyRKphRxWE = false;}
      if(KeAnSoRiDM == true){KeAnSoRiDM = false;}
      if(eMVXQbblxF == true){eMVXQbblxF = false;}
      if(xbuHnHWmyi == true){xbuHnHWmyi = false;}
      if(cNwFhkxddy == true){cNwFhkxddy = false;}
      if(ZpIbVLcssO == true){ZpIbVLcssO = false;}
      if(FeARHijrAL == true){FeARHijrAL = false;}
      if(RejUiRQQoe == true){RejUiRQQoe = false;}
      if(dxIyeGSSlc == true){dxIyeGSSlc = false;}
      if(dcsjcyMexz == true){dcsjcyMexz = false;}
      if(BEdRfuGnsD == true){BEdRfuGnsD = false;}
      if(uMENjIVBlA == true){uMENjIVBlA = false;}
      if(QQFXhokzqk == true){QQFXhokzqk = false;}
      if(EkSpdYTqRi == true){EkSpdYTqRi = false;}
      if(AdZhgRYfAU == true){AdZhgRYfAU = false;}
      if(bKsxijzGjq == true){bKsxijzGjq = false;}
      if(KGxHzJsOjL == true){KGxHzJsOjL = false;}
      if(oejCAlqXpQ == true){oejCAlqXpQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBTCIAEBRZ
{ 
  void sjhRGMmETY()
  { 
      bool LYLlOCPAgg = false;
      bool gEBXmuWuzT = false;
      bool LiqKqAWAFl = false;
      bool rgzdhniqRE = false;
      bool cGEhbMlmVJ = false;
      bool aJRkHchAtN = false;
      bool fOuuoAEWoz = false;
      bool LecupFdIhd = false;
      bool NiduKhPNWE = false;
      bool FhwEXNKJsb = false;
      bool HOxWxwgVtB = false;
      bool zZSQzwjzjG = false;
      bool kqAjschYWb = false;
      bool tUOGWzlHxO = false;
      bool BsSUFfPfEb = false;
      bool dLYmqQOMdT = false;
      bool OHzRHdKLtA = false;
      bool KcCVErXeeM = false;
      bool NBTuyiuaPF = false;
      bool jYccztsANa = false;
      string jfeeqOdzJz;
      string pAHxLIzQyO;
      string gQFchDNxZq;
      string uUHnpehkPg;
      string bThDbsypZU;
      string eYckrSZBxm;
      string AgZREUrSHf;
      string ZOAQlMhCBo;
      string FWWELWrWwW;
      string FfncgttQzH;
      string AeistQXLye;
      string kXAIhcKUFh;
      string cVVjasaXjq;
      string SRDsnZncKu;
      string yfXRlgfftD;
      string jZKQdeIzRA;
      string pAbGMSUGTI;
      string ogKKjwxExt;
      string NudfHrGlPJ;
      string QnKJExEQFS;
      if(jfeeqOdzJz == AeistQXLye){LYLlOCPAgg = true;}
      else if(AeistQXLye == jfeeqOdzJz){HOxWxwgVtB = true;}
      if(pAHxLIzQyO == kXAIhcKUFh){gEBXmuWuzT = true;}
      else if(kXAIhcKUFh == pAHxLIzQyO){zZSQzwjzjG = true;}
      if(gQFchDNxZq == cVVjasaXjq){LiqKqAWAFl = true;}
      else if(cVVjasaXjq == gQFchDNxZq){kqAjschYWb = true;}
      if(uUHnpehkPg == SRDsnZncKu){rgzdhniqRE = true;}
      else if(SRDsnZncKu == uUHnpehkPg){tUOGWzlHxO = true;}
      if(bThDbsypZU == yfXRlgfftD){cGEhbMlmVJ = true;}
      else if(yfXRlgfftD == bThDbsypZU){BsSUFfPfEb = true;}
      if(eYckrSZBxm == jZKQdeIzRA){aJRkHchAtN = true;}
      else if(jZKQdeIzRA == eYckrSZBxm){dLYmqQOMdT = true;}
      if(AgZREUrSHf == pAbGMSUGTI){fOuuoAEWoz = true;}
      else if(pAbGMSUGTI == AgZREUrSHf){OHzRHdKLtA = true;}
      if(ZOAQlMhCBo == ogKKjwxExt){LecupFdIhd = true;}
      if(FWWELWrWwW == NudfHrGlPJ){NiduKhPNWE = true;}
      if(FfncgttQzH == QnKJExEQFS){FhwEXNKJsb = true;}
      while(ogKKjwxExt == ZOAQlMhCBo){KcCVErXeeM = true;}
      while(NudfHrGlPJ == NudfHrGlPJ){NBTuyiuaPF = true;}
      while(QnKJExEQFS == QnKJExEQFS){jYccztsANa = true;}
      if(LYLlOCPAgg == true){LYLlOCPAgg = false;}
      if(gEBXmuWuzT == true){gEBXmuWuzT = false;}
      if(LiqKqAWAFl == true){LiqKqAWAFl = false;}
      if(rgzdhniqRE == true){rgzdhniqRE = false;}
      if(cGEhbMlmVJ == true){cGEhbMlmVJ = false;}
      if(aJRkHchAtN == true){aJRkHchAtN = false;}
      if(fOuuoAEWoz == true){fOuuoAEWoz = false;}
      if(LecupFdIhd == true){LecupFdIhd = false;}
      if(NiduKhPNWE == true){NiduKhPNWE = false;}
      if(FhwEXNKJsb == true){FhwEXNKJsb = false;}
      if(HOxWxwgVtB == true){HOxWxwgVtB = false;}
      if(zZSQzwjzjG == true){zZSQzwjzjG = false;}
      if(kqAjschYWb == true){kqAjschYWb = false;}
      if(tUOGWzlHxO == true){tUOGWzlHxO = false;}
      if(BsSUFfPfEb == true){BsSUFfPfEb = false;}
      if(dLYmqQOMdT == true){dLYmqQOMdT = false;}
      if(OHzRHdKLtA == true){OHzRHdKLtA = false;}
      if(KcCVErXeeM == true){KcCVErXeeM = false;}
      if(NBTuyiuaPF == true){NBTuyiuaPF = false;}
      if(jYccztsANa == true){jYccztsANa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSRHYDKXIQ
{ 
  void cMOXoldGyc()
  { 
      bool TUsJFmFMrm = false;
      bool uXNdFxtFcH = false;
      bool oNSPfRqbIG = false;
      bool NKzyNmVIwb = false;
      bool ijhZHauIXN = false;
      bool iuaZKFBddm = false;
      bool ucEkYjYOPR = false;
      bool blIAXEfsHE = false;
      bool VhEtXRjZnI = false;
      bool lrdIgGfwAX = false;
      bool CfrFlwmZBF = false;
      bool YIVYRMYJNG = false;
      bool AyaHfiHzTR = false;
      bool YjsjCopyIa = false;
      bool eJXhjcVEqT = false;
      bool gVhsWDFkZC = false;
      bool nmGjfnOkWc = false;
      bool WaBlbqarWC = false;
      bool NCIzkDBAMz = false;
      bool jEXFlrCnBu = false;
      string PcYNmSRslo;
      string VIUNamhMHA;
      string TrklueCmlb;
      string HAXfaoiMgt;
      string YNkiwIGjmZ;
      string LyCBDXrlSH;
      string QdHJhVjnml;
      string EVeMbGGCpl;
      string XSALPIyWbC;
      string xwsYduGbAZ;
      string XSwBVpSoZx;
      string QowgjxcutY;
      string XMMjoIbGhg;
      string AeBPNFVypZ;
      string oIxelHAMng;
      string RKgbCKFMLM;
      string NMGrxlnfSe;
      string adFUiPPgyh;
      string HPRBPoxZMC;
      string zJmcLcBEhz;
      if(PcYNmSRslo == XSwBVpSoZx){TUsJFmFMrm = true;}
      else if(XSwBVpSoZx == PcYNmSRslo){CfrFlwmZBF = true;}
      if(VIUNamhMHA == QowgjxcutY){uXNdFxtFcH = true;}
      else if(QowgjxcutY == VIUNamhMHA){YIVYRMYJNG = true;}
      if(TrklueCmlb == XMMjoIbGhg){oNSPfRqbIG = true;}
      else if(XMMjoIbGhg == TrklueCmlb){AyaHfiHzTR = true;}
      if(HAXfaoiMgt == AeBPNFVypZ){NKzyNmVIwb = true;}
      else if(AeBPNFVypZ == HAXfaoiMgt){YjsjCopyIa = true;}
      if(YNkiwIGjmZ == oIxelHAMng){ijhZHauIXN = true;}
      else if(oIxelHAMng == YNkiwIGjmZ){eJXhjcVEqT = true;}
      if(LyCBDXrlSH == RKgbCKFMLM){iuaZKFBddm = true;}
      else if(RKgbCKFMLM == LyCBDXrlSH){gVhsWDFkZC = true;}
      if(QdHJhVjnml == NMGrxlnfSe){ucEkYjYOPR = true;}
      else if(NMGrxlnfSe == QdHJhVjnml){nmGjfnOkWc = true;}
      if(EVeMbGGCpl == adFUiPPgyh){blIAXEfsHE = true;}
      if(XSALPIyWbC == HPRBPoxZMC){VhEtXRjZnI = true;}
      if(xwsYduGbAZ == zJmcLcBEhz){lrdIgGfwAX = true;}
      while(adFUiPPgyh == EVeMbGGCpl){WaBlbqarWC = true;}
      while(HPRBPoxZMC == HPRBPoxZMC){NCIzkDBAMz = true;}
      while(zJmcLcBEhz == zJmcLcBEhz){jEXFlrCnBu = true;}
      if(TUsJFmFMrm == true){TUsJFmFMrm = false;}
      if(uXNdFxtFcH == true){uXNdFxtFcH = false;}
      if(oNSPfRqbIG == true){oNSPfRqbIG = false;}
      if(NKzyNmVIwb == true){NKzyNmVIwb = false;}
      if(ijhZHauIXN == true){ijhZHauIXN = false;}
      if(iuaZKFBddm == true){iuaZKFBddm = false;}
      if(ucEkYjYOPR == true){ucEkYjYOPR = false;}
      if(blIAXEfsHE == true){blIAXEfsHE = false;}
      if(VhEtXRjZnI == true){VhEtXRjZnI = false;}
      if(lrdIgGfwAX == true){lrdIgGfwAX = false;}
      if(CfrFlwmZBF == true){CfrFlwmZBF = false;}
      if(YIVYRMYJNG == true){YIVYRMYJNG = false;}
      if(AyaHfiHzTR == true){AyaHfiHzTR = false;}
      if(YjsjCopyIa == true){YjsjCopyIa = false;}
      if(eJXhjcVEqT == true){eJXhjcVEqT = false;}
      if(gVhsWDFkZC == true){gVhsWDFkZC = false;}
      if(nmGjfnOkWc == true){nmGjfnOkWc = false;}
      if(WaBlbqarWC == true){WaBlbqarWC = false;}
      if(NCIzkDBAMz == true){NCIzkDBAMz = false;}
      if(jEXFlrCnBu == true){jEXFlrCnBu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPHSCHMQQG
{ 
  void XzABGTqDDq()
  { 
      bool lScaRstxqJ = false;
      bool DZaxUwrhDU = false;
      bool VkFOuikepy = false;
      bool YEiSfwzlTC = false;
      bool QMLLRojmrI = false;
      bool mPfmfBNOei = false;
      bool HPHsjypIRY = false;
      bool xFOBDJYsxF = false;
      bool yylgLIYwle = false;
      bool ijHjtBESaS = false;
      bool zbVSLgAejW = false;
      bool bTRYjJcZha = false;
      bool ZtVlpMydGC = false;
      bool EGSdGVbSUd = false;
      bool IsMPDOShzk = false;
      bool YdkzrFFjcz = false;
      bool iVYgRVBmSN = false;
      bool gJEDSfgGia = false;
      bool sPdUdZVSkA = false;
      bool QrpVtlUexg = false;
      string HKOTDcosab;
      string fRYknxbgZY;
      string kFqPAeWEMH;
      string YHDYRGTcDR;
      string YJkksbyRrV;
      string OiYKFCSyTY;
      string FkgSCXOASg;
      string czdIzaTGWY;
      string fFMpsoisSP;
      string mUIeLncRhV;
      string MyyKrOFQKd;
      string hMburAXpZN;
      string oVgDsIpzwL;
      string yCXBLgGBxd;
      string jRhnhasNlL;
      string PlrUfpRuQj;
      string YFTzffnZjK;
      string sWrucWmrUS;
      string OcNkuLJDUU;
      string PKkNFeyiIC;
      if(HKOTDcosab == MyyKrOFQKd){lScaRstxqJ = true;}
      else if(MyyKrOFQKd == HKOTDcosab){zbVSLgAejW = true;}
      if(fRYknxbgZY == hMburAXpZN){DZaxUwrhDU = true;}
      else if(hMburAXpZN == fRYknxbgZY){bTRYjJcZha = true;}
      if(kFqPAeWEMH == oVgDsIpzwL){VkFOuikepy = true;}
      else if(oVgDsIpzwL == kFqPAeWEMH){ZtVlpMydGC = true;}
      if(YHDYRGTcDR == yCXBLgGBxd){YEiSfwzlTC = true;}
      else if(yCXBLgGBxd == YHDYRGTcDR){EGSdGVbSUd = true;}
      if(YJkksbyRrV == jRhnhasNlL){QMLLRojmrI = true;}
      else if(jRhnhasNlL == YJkksbyRrV){IsMPDOShzk = true;}
      if(OiYKFCSyTY == PlrUfpRuQj){mPfmfBNOei = true;}
      else if(PlrUfpRuQj == OiYKFCSyTY){YdkzrFFjcz = true;}
      if(FkgSCXOASg == YFTzffnZjK){HPHsjypIRY = true;}
      else if(YFTzffnZjK == FkgSCXOASg){iVYgRVBmSN = true;}
      if(czdIzaTGWY == sWrucWmrUS){xFOBDJYsxF = true;}
      if(fFMpsoisSP == OcNkuLJDUU){yylgLIYwle = true;}
      if(mUIeLncRhV == PKkNFeyiIC){ijHjtBESaS = true;}
      while(sWrucWmrUS == czdIzaTGWY){gJEDSfgGia = true;}
      while(OcNkuLJDUU == OcNkuLJDUU){sPdUdZVSkA = true;}
      while(PKkNFeyiIC == PKkNFeyiIC){QrpVtlUexg = true;}
      if(lScaRstxqJ == true){lScaRstxqJ = false;}
      if(DZaxUwrhDU == true){DZaxUwrhDU = false;}
      if(VkFOuikepy == true){VkFOuikepy = false;}
      if(YEiSfwzlTC == true){YEiSfwzlTC = false;}
      if(QMLLRojmrI == true){QMLLRojmrI = false;}
      if(mPfmfBNOei == true){mPfmfBNOei = false;}
      if(HPHsjypIRY == true){HPHsjypIRY = false;}
      if(xFOBDJYsxF == true){xFOBDJYsxF = false;}
      if(yylgLIYwle == true){yylgLIYwle = false;}
      if(ijHjtBESaS == true){ijHjtBESaS = false;}
      if(zbVSLgAejW == true){zbVSLgAejW = false;}
      if(bTRYjJcZha == true){bTRYjJcZha = false;}
      if(ZtVlpMydGC == true){ZtVlpMydGC = false;}
      if(EGSdGVbSUd == true){EGSdGVbSUd = false;}
      if(IsMPDOShzk == true){IsMPDOShzk = false;}
      if(YdkzrFFjcz == true){YdkzrFFjcz = false;}
      if(iVYgRVBmSN == true){iVYgRVBmSN = false;}
      if(gJEDSfgGia == true){gJEDSfgGia = false;}
      if(sPdUdZVSkA == true){sPdUdZVSkA = false;}
      if(QrpVtlUexg == true){QrpVtlUexg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLQEBDWTUO
{ 
  void hsYUIMQYmL()
  { 
      bool BRHPTxibmL = false;
      bool nRBMYLlwqi = false;
      bool oAiRLesJfC = false;
      bool gaTbUOFURN = false;
      bool gUJOHBBFWJ = false;
      bool JcyIWBioEn = false;
      bool DYukdNyYrJ = false;
      bool GRddBTpTKJ = false;
      bool dmlWrEbLFS = false;
      bool fPQcJHYYjs = false;
      bool DbNMDrzUGC = false;
      bool KOetKQmYrZ = false;
      bool lmSYdpAATt = false;
      bool uRjQGBZZSz = false;
      bool EHEDIQkVSs = false;
      bool UzfJHQIohN = false;
      bool qyAMHreNnI = false;
      bool pMFrUdhPPN = false;
      bool EehaYukZIp = false;
      bool skqFHGGrwP = false;
      string eBWYTnQaSa;
      string ukwXtpkqgT;
      string KRhttKtCIZ;
      string jGRxYwFQiT;
      string hLRtUfeZzw;
      string aMfGCNSbeI;
      string sNRspnSyyx;
      string jUHMlyzmZO;
      string eTCMzXaLuL;
      string dclZZTtYEf;
      string MgbCLFETTD;
      string NfCPdZLFtR;
      string NHDlTGhglS;
      string EaisByrAAs;
      string TGqqyyaVwA;
      string HndlSEdohE;
      string XWgBzlwJOf;
      string gKFByGQLnV;
      string fMkkKPxwaw;
      string TCRuUwYorL;
      if(eBWYTnQaSa == MgbCLFETTD){BRHPTxibmL = true;}
      else if(MgbCLFETTD == eBWYTnQaSa){DbNMDrzUGC = true;}
      if(ukwXtpkqgT == NfCPdZLFtR){nRBMYLlwqi = true;}
      else if(NfCPdZLFtR == ukwXtpkqgT){KOetKQmYrZ = true;}
      if(KRhttKtCIZ == NHDlTGhglS){oAiRLesJfC = true;}
      else if(NHDlTGhglS == KRhttKtCIZ){lmSYdpAATt = true;}
      if(jGRxYwFQiT == EaisByrAAs){gaTbUOFURN = true;}
      else if(EaisByrAAs == jGRxYwFQiT){uRjQGBZZSz = true;}
      if(hLRtUfeZzw == TGqqyyaVwA){gUJOHBBFWJ = true;}
      else if(TGqqyyaVwA == hLRtUfeZzw){EHEDIQkVSs = true;}
      if(aMfGCNSbeI == HndlSEdohE){JcyIWBioEn = true;}
      else if(HndlSEdohE == aMfGCNSbeI){UzfJHQIohN = true;}
      if(sNRspnSyyx == XWgBzlwJOf){DYukdNyYrJ = true;}
      else if(XWgBzlwJOf == sNRspnSyyx){qyAMHreNnI = true;}
      if(jUHMlyzmZO == gKFByGQLnV){GRddBTpTKJ = true;}
      if(eTCMzXaLuL == fMkkKPxwaw){dmlWrEbLFS = true;}
      if(dclZZTtYEf == TCRuUwYorL){fPQcJHYYjs = true;}
      while(gKFByGQLnV == jUHMlyzmZO){pMFrUdhPPN = true;}
      while(fMkkKPxwaw == fMkkKPxwaw){EehaYukZIp = true;}
      while(TCRuUwYorL == TCRuUwYorL){skqFHGGrwP = true;}
      if(BRHPTxibmL == true){BRHPTxibmL = false;}
      if(nRBMYLlwqi == true){nRBMYLlwqi = false;}
      if(oAiRLesJfC == true){oAiRLesJfC = false;}
      if(gaTbUOFURN == true){gaTbUOFURN = false;}
      if(gUJOHBBFWJ == true){gUJOHBBFWJ = false;}
      if(JcyIWBioEn == true){JcyIWBioEn = false;}
      if(DYukdNyYrJ == true){DYukdNyYrJ = false;}
      if(GRddBTpTKJ == true){GRddBTpTKJ = false;}
      if(dmlWrEbLFS == true){dmlWrEbLFS = false;}
      if(fPQcJHYYjs == true){fPQcJHYYjs = false;}
      if(DbNMDrzUGC == true){DbNMDrzUGC = false;}
      if(KOetKQmYrZ == true){KOetKQmYrZ = false;}
      if(lmSYdpAATt == true){lmSYdpAATt = false;}
      if(uRjQGBZZSz == true){uRjQGBZZSz = false;}
      if(EHEDIQkVSs == true){EHEDIQkVSs = false;}
      if(UzfJHQIohN == true){UzfJHQIohN = false;}
      if(qyAMHreNnI == true){qyAMHreNnI = false;}
      if(pMFrUdhPPN == true){pMFrUdhPPN = false;}
      if(EehaYukZIp == true){EehaYukZIp = false;}
      if(skqFHGGrwP == true){skqFHGGrwP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVVZIQJUDX
{ 
  void tuTnxyloUg()
  { 
      bool zFPmkNDhuU = false;
      bool zJfttqZhHk = false;
      bool XKKtIFxljP = false;
      bool biFxPdyGFo = false;
      bool znpakBqyyG = false;
      bool sMpNgouUde = false;
      bool QRxesPDhdQ = false;
      bool sScSljTiIH = false;
      bool OyndVPrrQa = false;
      bool icbZXgpKhU = false;
      bool yIUgMaiXaw = false;
      bool ULMWQScTIc = false;
      bool XKQDhQpCtE = false;
      bool sJBmJFcGQu = false;
      bool fURTFWQFJF = false;
      bool DWCExmrQzw = false;
      bool jfcVDLJYNK = false;
      bool oWDMxCswxK = false;
      bool zksnAVHwpV = false;
      bool NLHTLzquQt = false;
      string VTnCPffSmL;
      string JERkxKYbTW;
      string IzseTqIMTg;
      string gYrMCfLZYS;
      string RjJdOhLSmX;
      string OYcUyWZIhX;
      string XTyFejMFhR;
      string yzCAEXpOQl;
      string eoZwSIuXNf;
      string GDqAuykDze;
      string UGjVYOVcPa;
      string gKrwshtCmV;
      string norCLuIBEG;
      string llOlQYFDWE;
      string mSHmzuLtHN;
      string DiQdpfNhKd;
      string FTYJntuFeT;
      string cpeiiVgECP;
      string iNtpCCVkuk;
      string KWssyStxyE;
      if(VTnCPffSmL == UGjVYOVcPa){zFPmkNDhuU = true;}
      else if(UGjVYOVcPa == VTnCPffSmL){yIUgMaiXaw = true;}
      if(JERkxKYbTW == gKrwshtCmV){zJfttqZhHk = true;}
      else if(gKrwshtCmV == JERkxKYbTW){ULMWQScTIc = true;}
      if(IzseTqIMTg == norCLuIBEG){XKKtIFxljP = true;}
      else if(norCLuIBEG == IzseTqIMTg){XKQDhQpCtE = true;}
      if(gYrMCfLZYS == llOlQYFDWE){biFxPdyGFo = true;}
      else if(llOlQYFDWE == gYrMCfLZYS){sJBmJFcGQu = true;}
      if(RjJdOhLSmX == mSHmzuLtHN){znpakBqyyG = true;}
      else if(mSHmzuLtHN == RjJdOhLSmX){fURTFWQFJF = true;}
      if(OYcUyWZIhX == DiQdpfNhKd){sMpNgouUde = true;}
      else if(DiQdpfNhKd == OYcUyWZIhX){DWCExmrQzw = true;}
      if(XTyFejMFhR == FTYJntuFeT){QRxesPDhdQ = true;}
      else if(FTYJntuFeT == XTyFejMFhR){jfcVDLJYNK = true;}
      if(yzCAEXpOQl == cpeiiVgECP){sScSljTiIH = true;}
      if(eoZwSIuXNf == iNtpCCVkuk){OyndVPrrQa = true;}
      if(GDqAuykDze == KWssyStxyE){icbZXgpKhU = true;}
      while(cpeiiVgECP == yzCAEXpOQl){oWDMxCswxK = true;}
      while(iNtpCCVkuk == iNtpCCVkuk){zksnAVHwpV = true;}
      while(KWssyStxyE == KWssyStxyE){NLHTLzquQt = true;}
      if(zFPmkNDhuU == true){zFPmkNDhuU = false;}
      if(zJfttqZhHk == true){zJfttqZhHk = false;}
      if(XKKtIFxljP == true){XKKtIFxljP = false;}
      if(biFxPdyGFo == true){biFxPdyGFo = false;}
      if(znpakBqyyG == true){znpakBqyyG = false;}
      if(sMpNgouUde == true){sMpNgouUde = false;}
      if(QRxesPDhdQ == true){QRxesPDhdQ = false;}
      if(sScSljTiIH == true){sScSljTiIH = false;}
      if(OyndVPrrQa == true){OyndVPrrQa = false;}
      if(icbZXgpKhU == true){icbZXgpKhU = false;}
      if(yIUgMaiXaw == true){yIUgMaiXaw = false;}
      if(ULMWQScTIc == true){ULMWQScTIc = false;}
      if(XKQDhQpCtE == true){XKQDhQpCtE = false;}
      if(sJBmJFcGQu == true){sJBmJFcGQu = false;}
      if(fURTFWQFJF == true){fURTFWQFJF = false;}
      if(DWCExmrQzw == true){DWCExmrQzw = false;}
      if(jfcVDLJYNK == true){jfcVDLJYNK = false;}
      if(oWDMxCswxK == true){oWDMxCswxK = false;}
      if(zksnAVHwpV == true){zksnAVHwpV = false;}
      if(NLHTLzquQt == true){NLHTLzquQt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class POUWJWXBBE
{ 
  void FONDwnVSyC()
  { 
      bool VrsLVCcGWn = false;
      bool VQlYmcXxpk = false;
      bool dejRcBZyrV = false;
      bool buziloZcbl = false;
      bool mSPnLyiMNd = false;
      bool qNSKSqHahT = false;
      bool bdNBLZQCly = false;
      bool DuVExKPwFe = false;
      bool SMkOdOcoQu = false;
      bool gzuHJIFObl = false;
      bool gfZOawrNMH = false;
      bool aKUCAOrzWx = false;
      bool wblpQEAOuo = false;
      bool FBTTymmWnh = false;
      bool VPbIUVdrGt = false;
      bool PGqepFsiyV = false;
      bool wdSXCZqBEN = false;
      bool bVKoagzdVt = false;
      bool ZHHAYzJods = false;
      bool tDXRlrwEFt = false;
      string nIgiRuxszt;
      string MGHWWZyktR;
      string mPgmBSzUtj;
      string zYwZHbQjWA;
      string VwZPKblNYQ;
      string WTfcjYbshz;
      string wbyPtmKhOu;
      string JOOtwpoQbZ;
      string flwcMfrSpi;
      string zWBWDsyJVW;
      string QEycHIElfs;
      string iLRITKeVDN;
      string uqrfulMrpC;
      string rftEIamTVD;
      string bGlwzmFsDs;
      string OcGIbZMSgU;
      string wMudADRMAr;
      string WLzzknEufI;
      string gSnxnPYlbh;
      string OUlAHPLIuw;
      if(nIgiRuxszt == QEycHIElfs){VrsLVCcGWn = true;}
      else if(QEycHIElfs == nIgiRuxszt){gfZOawrNMH = true;}
      if(MGHWWZyktR == iLRITKeVDN){VQlYmcXxpk = true;}
      else if(iLRITKeVDN == MGHWWZyktR){aKUCAOrzWx = true;}
      if(mPgmBSzUtj == uqrfulMrpC){dejRcBZyrV = true;}
      else if(uqrfulMrpC == mPgmBSzUtj){wblpQEAOuo = true;}
      if(zYwZHbQjWA == rftEIamTVD){buziloZcbl = true;}
      else if(rftEIamTVD == zYwZHbQjWA){FBTTymmWnh = true;}
      if(VwZPKblNYQ == bGlwzmFsDs){mSPnLyiMNd = true;}
      else if(bGlwzmFsDs == VwZPKblNYQ){VPbIUVdrGt = true;}
      if(WTfcjYbshz == OcGIbZMSgU){qNSKSqHahT = true;}
      else if(OcGIbZMSgU == WTfcjYbshz){PGqepFsiyV = true;}
      if(wbyPtmKhOu == wMudADRMAr){bdNBLZQCly = true;}
      else if(wMudADRMAr == wbyPtmKhOu){wdSXCZqBEN = true;}
      if(JOOtwpoQbZ == WLzzknEufI){DuVExKPwFe = true;}
      if(flwcMfrSpi == gSnxnPYlbh){SMkOdOcoQu = true;}
      if(zWBWDsyJVW == OUlAHPLIuw){gzuHJIFObl = true;}
      while(WLzzknEufI == JOOtwpoQbZ){bVKoagzdVt = true;}
      while(gSnxnPYlbh == gSnxnPYlbh){ZHHAYzJods = true;}
      while(OUlAHPLIuw == OUlAHPLIuw){tDXRlrwEFt = true;}
      if(VrsLVCcGWn == true){VrsLVCcGWn = false;}
      if(VQlYmcXxpk == true){VQlYmcXxpk = false;}
      if(dejRcBZyrV == true){dejRcBZyrV = false;}
      if(buziloZcbl == true){buziloZcbl = false;}
      if(mSPnLyiMNd == true){mSPnLyiMNd = false;}
      if(qNSKSqHahT == true){qNSKSqHahT = false;}
      if(bdNBLZQCly == true){bdNBLZQCly = false;}
      if(DuVExKPwFe == true){DuVExKPwFe = false;}
      if(SMkOdOcoQu == true){SMkOdOcoQu = false;}
      if(gzuHJIFObl == true){gzuHJIFObl = false;}
      if(gfZOawrNMH == true){gfZOawrNMH = false;}
      if(aKUCAOrzWx == true){aKUCAOrzWx = false;}
      if(wblpQEAOuo == true){wblpQEAOuo = false;}
      if(FBTTymmWnh == true){FBTTymmWnh = false;}
      if(VPbIUVdrGt == true){VPbIUVdrGt = false;}
      if(PGqepFsiyV == true){PGqepFsiyV = false;}
      if(wdSXCZqBEN == true){wdSXCZqBEN = false;}
      if(bVKoagzdVt == true){bVKoagzdVt = false;}
      if(ZHHAYzJods == true){ZHHAYzJods = false;}
      if(tDXRlrwEFt == true){tDXRlrwEFt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMAFEMNYQA
{ 
  void aAWJzOEHgx()
  { 
      bool JIjXYGncUk = false;
      bool MzLGWdspsY = false;
      bool EDWzSOnWUz = false;
      bool crbuaAbSPo = false;
      bool ZcNFdIuSxy = false;
      bool tDzyCFkkEK = false;
      bool SQHVHUXQeV = false;
      bool CaZDzboRVK = false;
      bool SUZWFZrcrU = false;
      bool OqNFWIUryI = false;
      bool kemauTcwya = false;
      bool QTPtqxqkQg = false;
      bool btXKGLMTgq = false;
      bool GxTMZnhyak = false;
      bool wweREuaTOY = false;
      bool RjbQfpGcUi = false;
      bool GJOHTSACTD = false;
      bool PrJejfOFGL = false;
      bool jrFHZVVCfi = false;
      bool gEdqdmhXxk = false;
      string hnoNnTekYO;
      string CSpAVBgMIg;
      string lVxfcjUNiO;
      string BVLlVQooml;
      string QXAigXPOaW;
      string TAjWuMqJjD;
      string yQCKNfHDdE;
      string LqYVQOUNyF;
      string TGlLuAlnqJ;
      string YfFimzVoVB;
      string QLjVLbaNGf;
      string qdKeirdpPM;
      string tSLUeelpiQ;
      string sfqxnIWQzS;
      string YXhLSuVZzt;
      string UeZIHxAOpf;
      string pkeomKlMpa;
      string VNpxnWkACj;
      string JLqnwNFipq;
      string HHZTbnsrXH;
      if(hnoNnTekYO == QLjVLbaNGf){JIjXYGncUk = true;}
      else if(QLjVLbaNGf == hnoNnTekYO){kemauTcwya = true;}
      if(CSpAVBgMIg == qdKeirdpPM){MzLGWdspsY = true;}
      else if(qdKeirdpPM == CSpAVBgMIg){QTPtqxqkQg = true;}
      if(lVxfcjUNiO == tSLUeelpiQ){EDWzSOnWUz = true;}
      else if(tSLUeelpiQ == lVxfcjUNiO){btXKGLMTgq = true;}
      if(BVLlVQooml == sfqxnIWQzS){crbuaAbSPo = true;}
      else if(sfqxnIWQzS == BVLlVQooml){GxTMZnhyak = true;}
      if(QXAigXPOaW == YXhLSuVZzt){ZcNFdIuSxy = true;}
      else if(YXhLSuVZzt == QXAigXPOaW){wweREuaTOY = true;}
      if(TAjWuMqJjD == UeZIHxAOpf){tDzyCFkkEK = true;}
      else if(UeZIHxAOpf == TAjWuMqJjD){RjbQfpGcUi = true;}
      if(yQCKNfHDdE == pkeomKlMpa){SQHVHUXQeV = true;}
      else if(pkeomKlMpa == yQCKNfHDdE){GJOHTSACTD = true;}
      if(LqYVQOUNyF == VNpxnWkACj){CaZDzboRVK = true;}
      if(TGlLuAlnqJ == JLqnwNFipq){SUZWFZrcrU = true;}
      if(YfFimzVoVB == HHZTbnsrXH){OqNFWIUryI = true;}
      while(VNpxnWkACj == LqYVQOUNyF){PrJejfOFGL = true;}
      while(JLqnwNFipq == JLqnwNFipq){jrFHZVVCfi = true;}
      while(HHZTbnsrXH == HHZTbnsrXH){gEdqdmhXxk = true;}
      if(JIjXYGncUk == true){JIjXYGncUk = false;}
      if(MzLGWdspsY == true){MzLGWdspsY = false;}
      if(EDWzSOnWUz == true){EDWzSOnWUz = false;}
      if(crbuaAbSPo == true){crbuaAbSPo = false;}
      if(ZcNFdIuSxy == true){ZcNFdIuSxy = false;}
      if(tDzyCFkkEK == true){tDzyCFkkEK = false;}
      if(SQHVHUXQeV == true){SQHVHUXQeV = false;}
      if(CaZDzboRVK == true){CaZDzboRVK = false;}
      if(SUZWFZrcrU == true){SUZWFZrcrU = false;}
      if(OqNFWIUryI == true){OqNFWIUryI = false;}
      if(kemauTcwya == true){kemauTcwya = false;}
      if(QTPtqxqkQg == true){QTPtqxqkQg = false;}
      if(btXKGLMTgq == true){btXKGLMTgq = false;}
      if(GxTMZnhyak == true){GxTMZnhyak = false;}
      if(wweREuaTOY == true){wweREuaTOY = false;}
      if(RjbQfpGcUi == true){RjbQfpGcUi = false;}
      if(GJOHTSACTD == true){GJOHTSACTD = false;}
      if(PrJejfOFGL == true){PrJejfOFGL = false;}
      if(jrFHZVVCfi == true){jrFHZVVCfi = false;}
      if(gEdqdmhXxk == true){gEdqdmhXxk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KAGZPNRXPE
{ 
  void USHudDDVVb()
  { 
      bool yxumVMujqc = false;
      bool jDNAxUuqtc = false;
      bool ylYUdBYyoq = false;
      bool NYHzzmtxsd = false;
      bool UnTVwjAnCD = false;
      bool ywxalLXaJU = false;
      bool nxtAOLwOAJ = false;
      bool ayxPHKRDXs = false;
      bool AjwkrRafMm = false;
      bool OSnXpXsTGj = false;
      bool nknrcAzhSb = false;
      bool sUCPUDAJIx = false;
      bool jPBMuHKZYj = false;
      bool RywmFOwEIq = false;
      bool SsMktsQXDm = false;
      bool WiKJAXjaxU = false;
      bool pZIiJuYOKF = false;
      bool HwBQeqDQSB = false;
      bool qlVlMhmmmh = false;
      bool eVHmBrjday = false;
      string ExlWASonbt;
      string UMwDeJPfGJ;
      string ItfdGHmEmw;
      string iWilKBfxRr;
      string NZbAYahjWR;
      string PkVAlKRHPs;
      string ejAeKxdJrd;
      string dSNNwhReFf;
      string ZDgVgyBhAA;
      string iXgXMdYwpa;
      string xXqsnwWHED;
      string rmCjSbCeyM;
      string wuIrtGlpAS;
      string JVodiCMngj;
      string atdxHwVwEk;
      string asyceBOyyh;
      string KgGlsWyXBQ;
      string OOxOkBQLjy;
      string jokPqQXLzg;
      string mNozYtmrEk;
      if(ExlWASonbt == xXqsnwWHED){yxumVMujqc = true;}
      else if(xXqsnwWHED == ExlWASonbt){nknrcAzhSb = true;}
      if(UMwDeJPfGJ == rmCjSbCeyM){jDNAxUuqtc = true;}
      else if(rmCjSbCeyM == UMwDeJPfGJ){sUCPUDAJIx = true;}
      if(ItfdGHmEmw == wuIrtGlpAS){ylYUdBYyoq = true;}
      else if(wuIrtGlpAS == ItfdGHmEmw){jPBMuHKZYj = true;}
      if(iWilKBfxRr == JVodiCMngj){NYHzzmtxsd = true;}
      else if(JVodiCMngj == iWilKBfxRr){RywmFOwEIq = true;}
      if(NZbAYahjWR == atdxHwVwEk){UnTVwjAnCD = true;}
      else if(atdxHwVwEk == NZbAYahjWR){SsMktsQXDm = true;}
      if(PkVAlKRHPs == asyceBOyyh){ywxalLXaJU = true;}
      else if(asyceBOyyh == PkVAlKRHPs){WiKJAXjaxU = true;}
      if(ejAeKxdJrd == KgGlsWyXBQ){nxtAOLwOAJ = true;}
      else if(KgGlsWyXBQ == ejAeKxdJrd){pZIiJuYOKF = true;}
      if(dSNNwhReFf == OOxOkBQLjy){ayxPHKRDXs = true;}
      if(ZDgVgyBhAA == jokPqQXLzg){AjwkrRafMm = true;}
      if(iXgXMdYwpa == mNozYtmrEk){OSnXpXsTGj = true;}
      while(OOxOkBQLjy == dSNNwhReFf){HwBQeqDQSB = true;}
      while(jokPqQXLzg == jokPqQXLzg){qlVlMhmmmh = true;}
      while(mNozYtmrEk == mNozYtmrEk){eVHmBrjday = true;}
      if(yxumVMujqc == true){yxumVMujqc = false;}
      if(jDNAxUuqtc == true){jDNAxUuqtc = false;}
      if(ylYUdBYyoq == true){ylYUdBYyoq = false;}
      if(NYHzzmtxsd == true){NYHzzmtxsd = false;}
      if(UnTVwjAnCD == true){UnTVwjAnCD = false;}
      if(ywxalLXaJU == true){ywxalLXaJU = false;}
      if(nxtAOLwOAJ == true){nxtAOLwOAJ = false;}
      if(ayxPHKRDXs == true){ayxPHKRDXs = false;}
      if(AjwkrRafMm == true){AjwkrRafMm = false;}
      if(OSnXpXsTGj == true){OSnXpXsTGj = false;}
      if(nknrcAzhSb == true){nknrcAzhSb = false;}
      if(sUCPUDAJIx == true){sUCPUDAJIx = false;}
      if(jPBMuHKZYj == true){jPBMuHKZYj = false;}
      if(RywmFOwEIq == true){RywmFOwEIq = false;}
      if(SsMktsQXDm == true){SsMktsQXDm = false;}
      if(WiKJAXjaxU == true){WiKJAXjaxU = false;}
      if(pZIiJuYOKF == true){pZIiJuYOKF = false;}
      if(HwBQeqDQSB == true){HwBQeqDQSB = false;}
      if(qlVlMhmmmh == true){qlVlMhmmmh = false;}
      if(eVHmBrjday == true){eVHmBrjday = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXPVBHKXUX
{ 
  void WVDoTkzrTS()
  { 
      bool QMVJbHmxYH = false;
      bool MyslrbgkoK = false;
      bool STIiyzpHCk = false;
      bool UXGhwXKCzw = false;
      bool okwRysVBGA = false;
      bool FpLilwEmLc = false;
      bool RetnmnqKpT = false;
      bool QdksVhXpkE = false;
      bool dnABeeLWuz = false;
      bool SXqWeJpIdJ = false;
      bool BKKljaESNE = false;
      bool YNCHzcdsIH = false;
      bool cUPqBsmOOL = false;
      bool qPMaCSdORE = false;
      bool ZrJqZFVjXB = false;
      bool exzVfgtTkq = false;
      bool npEBMJBaEf = false;
      bool zPaEhkKYQw = false;
      bool XCqMgtPptU = false;
      bool XJcaQjnIdQ = false;
      string ZocsbDdxEi;
      string JuUGUTwbBP;
      string rGOBCZTGex;
      string oKzxonhuhj;
      string YtBukADuAt;
      string GAtXGSZbpC;
      string jWSHsyuXRg;
      string lBsRpxFSPB;
      string VYGjpnPbpV;
      string NGEfACbsBl;
      string FfcSIFHcgI;
      string NGLofKQhQF;
      string iTgwTfwMQn;
      string VLRdwpwmbk;
      string gmtgHGtPAp;
      string kscwDkygzc;
      string ItLsmCohsp;
      string NdGeXuYAnM;
      string kgMaDbiUZK;
      string rOnycmaBtF;
      if(ZocsbDdxEi == FfcSIFHcgI){QMVJbHmxYH = true;}
      else if(FfcSIFHcgI == ZocsbDdxEi){BKKljaESNE = true;}
      if(JuUGUTwbBP == NGLofKQhQF){MyslrbgkoK = true;}
      else if(NGLofKQhQF == JuUGUTwbBP){YNCHzcdsIH = true;}
      if(rGOBCZTGex == iTgwTfwMQn){STIiyzpHCk = true;}
      else if(iTgwTfwMQn == rGOBCZTGex){cUPqBsmOOL = true;}
      if(oKzxonhuhj == VLRdwpwmbk){UXGhwXKCzw = true;}
      else if(VLRdwpwmbk == oKzxonhuhj){qPMaCSdORE = true;}
      if(YtBukADuAt == gmtgHGtPAp){okwRysVBGA = true;}
      else if(gmtgHGtPAp == YtBukADuAt){ZrJqZFVjXB = true;}
      if(GAtXGSZbpC == kscwDkygzc){FpLilwEmLc = true;}
      else if(kscwDkygzc == GAtXGSZbpC){exzVfgtTkq = true;}
      if(jWSHsyuXRg == ItLsmCohsp){RetnmnqKpT = true;}
      else if(ItLsmCohsp == jWSHsyuXRg){npEBMJBaEf = true;}
      if(lBsRpxFSPB == NdGeXuYAnM){QdksVhXpkE = true;}
      if(VYGjpnPbpV == kgMaDbiUZK){dnABeeLWuz = true;}
      if(NGEfACbsBl == rOnycmaBtF){SXqWeJpIdJ = true;}
      while(NdGeXuYAnM == lBsRpxFSPB){zPaEhkKYQw = true;}
      while(kgMaDbiUZK == kgMaDbiUZK){XCqMgtPptU = true;}
      while(rOnycmaBtF == rOnycmaBtF){XJcaQjnIdQ = true;}
      if(QMVJbHmxYH == true){QMVJbHmxYH = false;}
      if(MyslrbgkoK == true){MyslrbgkoK = false;}
      if(STIiyzpHCk == true){STIiyzpHCk = false;}
      if(UXGhwXKCzw == true){UXGhwXKCzw = false;}
      if(okwRysVBGA == true){okwRysVBGA = false;}
      if(FpLilwEmLc == true){FpLilwEmLc = false;}
      if(RetnmnqKpT == true){RetnmnqKpT = false;}
      if(QdksVhXpkE == true){QdksVhXpkE = false;}
      if(dnABeeLWuz == true){dnABeeLWuz = false;}
      if(SXqWeJpIdJ == true){SXqWeJpIdJ = false;}
      if(BKKljaESNE == true){BKKljaESNE = false;}
      if(YNCHzcdsIH == true){YNCHzcdsIH = false;}
      if(cUPqBsmOOL == true){cUPqBsmOOL = false;}
      if(qPMaCSdORE == true){qPMaCSdORE = false;}
      if(ZrJqZFVjXB == true){ZrJqZFVjXB = false;}
      if(exzVfgtTkq == true){exzVfgtTkq = false;}
      if(npEBMJBaEf == true){npEBMJBaEf = false;}
      if(zPaEhkKYQw == true){zPaEhkKYQw = false;}
      if(XCqMgtPptU == true){XCqMgtPptU = false;}
      if(XJcaQjnIdQ == true){XJcaQjnIdQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPEJVHTMMW
{ 
  void BKgiUVMziN()
  { 
      bool iDzOrRJlbV = false;
      bool StZeFWCtSx = false;
      bool qRcSQFMcoA = false;
      bool OfoyzdKDYL = false;
      bool uFsuGnwTzn = false;
      bool YpMxxRagxl = false;
      bool EfxaGmFbeb = false;
      bool LzVHBlXgLc = false;
      bool IsdAbXSqBh = false;
      bool CdFlGOHSnT = false;
      bool iUnXbYUEwK = false;
      bool tsUUcKCwyi = false;
      bool TOZxYhtiBl = false;
      bool dFrqtnFFYD = false;
      bool CNupmJIkIw = false;
      bool MLTFzTtpyt = false;
      bool elDJgnAcao = false;
      bool FxXufGSjJP = false;
      bool YJZEZSkmrZ = false;
      bool sOGeXPJlIy = false;
      string bQsdRIqbUf;
      string wHGFhWyebO;
      string dGCIJailmA;
      string JHnWHuNIUH;
      string GJyAFlxXGa;
      string YLPJWVNjTq;
      string YEnTWnSixl;
      string IpKTHUICDX;
      string cLfLaxrdAl;
      string gdnchBVdcQ;
      string SNZTSiBwCB;
      string NLfwONXbrY;
      string uniLFeBgkF;
      string ydYlEOkMsr;
      string wwbyXVxqOU;
      string cslEVeeNOm;
      string gUKwDilsrA;
      string cLizczLjmi;
      string hKRQcFqUQZ;
      string iWyFKbkfuo;
      if(bQsdRIqbUf == SNZTSiBwCB){iDzOrRJlbV = true;}
      else if(SNZTSiBwCB == bQsdRIqbUf){iUnXbYUEwK = true;}
      if(wHGFhWyebO == NLfwONXbrY){StZeFWCtSx = true;}
      else if(NLfwONXbrY == wHGFhWyebO){tsUUcKCwyi = true;}
      if(dGCIJailmA == uniLFeBgkF){qRcSQFMcoA = true;}
      else if(uniLFeBgkF == dGCIJailmA){TOZxYhtiBl = true;}
      if(JHnWHuNIUH == ydYlEOkMsr){OfoyzdKDYL = true;}
      else if(ydYlEOkMsr == JHnWHuNIUH){dFrqtnFFYD = true;}
      if(GJyAFlxXGa == wwbyXVxqOU){uFsuGnwTzn = true;}
      else if(wwbyXVxqOU == GJyAFlxXGa){CNupmJIkIw = true;}
      if(YLPJWVNjTq == cslEVeeNOm){YpMxxRagxl = true;}
      else if(cslEVeeNOm == YLPJWVNjTq){MLTFzTtpyt = true;}
      if(YEnTWnSixl == gUKwDilsrA){EfxaGmFbeb = true;}
      else if(gUKwDilsrA == YEnTWnSixl){elDJgnAcao = true;}
      if(IpKTHUICDX == cLizczLjmi){LzVHBlXgLc = true;}
      if(cLfLaxrdAl == hKRQcFqUQZ){IsdAbXSqBh = true;}
      if(gdnchBVdcQ == iWyFKbkfuo){CdFlGOHSnT = true;}
      while(cLizczLjmi == IpKTHUICDX){FxXufGSjJP = true;}
      while(hKRQcFqUQZ == hKRQcFqUQZ){YJZEZSkmrZ = true;}
      while(iWyFKbkfuo == iWyFKbkfuo){sOGeXPJlIy = true;}
      if(iDzOrRJlbV == true){iDzOrRJlbV = false;}
      if(StZeFWCtSx == true){StZeFWCtSx = false;}
      if(qRcSQFMcoA == true){qRcSQFMcoA = false;}
      if(OfoyzdKDYL == true){OfoyzdKDYL = false;}
      if(uFsuGnwTzn == true){uFsuGnwTzn = false;}
      if(YpMxxRagxl == true){YpMxxRagxl = false;}
      if(EfxaGmFbeb == true){EfxaGmFbeb = false;}
      if(LzVHBlXgLc == true){LzVHBlXgLc = false;}
      if(IsdAbXSqBh == true){IsdAbXSqBh = false;}
      if(CdFlGOHSnT == true){CdFlGOHSnT = false;}
      if(iUnXbYUEwK == true){iUnXbYUEwK = false;}
      if(tsUUcKCwyi == true){tsUUcKCwyi = false;}
      if(TOZxYhtiBl == true){TOZxYhtiBl = false;}
      if(dFrqtnFFYD == true){dFrqtnFFYD = false;}
      if(CNupmJIkIw == true){CNupmJIkIw = false;}
      if(MLTFzTtpyt == true){MLTFzTtpyt = false;}
      if(elDJgnAcao == true){elDJgnAcao = false;}
      if(FxXufGSjJP == true){FxXufGSjJP = false;}
      if(YJZEZSkmrZ == true){YJZEZSkmrZ = false;}
      if(sOGeXPJlIy == true){sOGeXPJlIy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGJBVPIZWI
{ 
  void ejpHKTdRLF()
  { 
      bool LruOjQspyY = false;
      bool ColaZGwCRl = false;
      bool iQfZiaSMCw = false;
      bool UgUApfuBgK = false;
      bool OfnQEcqeeR = false;
      bool SyHfmuMVfJ = false;
      bool xgnBDUUkks = false;
      bool KuVGWCcPVG = false;
      bool jngkdWZoMu = false;
      bool TZVWMgrlMi = false;
      bool IFskGWcAIk = false;
      bool SxzZYIzCXg = false;
      bool ueYpZkZyso = false;
      bool KpClxetudH = false;
      bool tYgbbVZuyE = false;
      bool hoOfndgDLV = false;
      bool xdGSZbtNbt = false;
      bool NDXPlVywND = false;
      bool KdAoHUaWyT = false;
      bool yqjIJPRNBA = false;
      string jHRSmzrAZd;
      string mxKeyCHfuw;
      string yrJqaTRGls;
      string QCymMPuPiL;
      string hxsMUexYdt;
      string HsJXOryarT;
      string gkOgMjzWSi;
      string HqxjNBzxVu;
      string VrcrkXsaYT;
      string QTXOdxhLzk;
      string faGtmQuYJM;
      string rBFwxoHWun;
      string pXyyRmShFQ;
      string TmxjPukiEU;
      string cTRLbPNbRn;
      string oLQKuIbIcz;
      string xNTrsFDUgC;
      string DYRZLVGmWB;
      string YqQQaHWmoG;
      string ScFFXOAYRV;
      if(jHRSmzrAZd == faGtmQuYJM){LruOjQspyY = true;}
      else if(faGtmQuYJM == jHRSmzrAZd){IFskGWcAIk = true;}
      if(mxKeyCHfuw == rBFwxoHWun){ColaZGwCRl = true;}
      else if(rBFwxoHWun == mxKeyCHfuw){SxzZYIzCXg = true;}
      if(yrJqaTRGls == pXyyRmShFQ){iQfZiaSMCw = true;}
      else if(pXyyRmShFQ == yrJqaTRGls){ueYpZkZyso = true;}
      if(QCymMPuPiL == TmxjPukiEU){UgUApfuBgK = true;}
      else if(TmxjPukiEU == QCymMPuPiL){KpClxetudH = true;}
      if(hxsMUexYdt == cTRLbPNbRn){OfnQEcqeeR = true;}
      else if(cTRLbPNbRn == hxsMUexYdt){tYgbbVZuyE = true;}
      if(HsJXOryarT == oLQKuIbIcz){SyHfmuMVfJ = true;}
      else if(oLQKuIbIcz == HsJXOryarT){hoOfndgDLV = true;}
      if(gkOgMjzWSi == xNTrsFDUgC){xgnBDUUkks = true;}
      else if(xNTrsFDUgC == gkOgMjzWSi){xdGSZbtNbt = true;}
      if(HqxjNBzxVu == DYRZLVGmWB){KuVGWCcPVG = true;}
      if(VrcrkXsaYT == YqQQaHWmoG){jngkdWZoMu = true;}
      if(QTXOdxhLzk == ScFFXOAYRV){TZVWMgrlMi = true;}
      while(DYRZLVGmWB == HqxjNBzxVu){NDXPlVywND = true;}
      while(YqQQaHWmoG == YqQQaHWmoG){KdAoHUaWyT = true;}
      while(ScFFXOAYRV == ScFFXOAYRV){yqjIJPRNBA = true;}
      if(LruOjQspyY == true){LruOjQspyY = false;}
      if(ColaZGwCRl == true){ColaZGwCRl = false;}
      if(iQfZiaSMCw == true){iQfZiaSMCw = false;}
      if(UgUApfuBgK == true){UgUApfuBgK = false;}
      if(OfnQEcqeeR == true){OfnQEcqeeR = false;}
      if(SyHfmuMVfJ == true){SyHfmuMVfJ = false;}
      if(xgnBDUUkks == true){xgnBDUUkks = false;}
      if(KuVGWCcPVG == true){KuVGWCcPVG = false;}
      if(jngkdWZoMu == true){jngkdWZoMu = false;}
      if(TZVWMgrlMi == true){TZVWMgrlMi = false;}
      if(IFskGWcAIk == true){IFskGWcAIk = false;}
      if(SxzZYIzCXg == true){SxzZYIzCXg = false;}
      if(ueYpZkZyso == true){ueYpZkZyso = false;}
      if(KpClxetudH == true){KpClxetudH = false;}
      if(tYgbbVZuyE == true){tYgbbVZuyE = false;}
      if(hoOfndgDLV == true){hoOfndgDLV = false;}
      if(xdGSZbtNbt == true){xdGSZbtNbt = false;}
      if(NDXPlVywND == true){NDXPlVywND = false;}
      if(KdAoHUaWyT == true){KdAoHUaWyT = false;}
      if(yqjIJPRNBA == true){yqjIJPRNBA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGMQQHRISR
{ 
  void ARPwcLyAOM()
  { 
      bool FRHOlCPalE = false;
      bool mlHBgtilBi = false;
      bool bUZPNsKHzB = false;
      bool hNqAOqNuCQ = false;
      bool EgPwLZgTfz = false;
      bool IGgxJjrqBs = false;
      bool rIakWYuHlo = false;
      bool gnijeuFcEm = false;
      bool Lqazsafspd = false;
      bool zVsJYuFdYl = false;
      bool eYgqSUWxSO = false;
      bool eOmOgAhbrw = false;
      bool rBRIoLtZKi = false;
      bool paDRImJigX = false;
      bool DiZbzjhebX = false;
      bool NdlcscHYBG = false;
      bool axljXDLVFt = false;
      bool pytTrJboIF = false;
      bool dOylULoaYf = false;
      bool ekhZxGwoDw = false;
      string ATyloXmQuS;
      string raPbPTkAnm;
      string qpSiZGVIuc;
      string HqAOpjPdRo;
      string hdqXbISlzx;
      string MbjaVKAOMh;
      string BeVSLBZBlf;
      string DHhyEMzuHQ;
      string miJxPeGZrf;
      string iAQinDIXMa;
      string iRASsFslVI;
      string KFHutRVXDf;
      string uzIGxCpzKB;
      string EbhggVipDJ;
      string lTDjUcsVnV;
      string hjTfeiJsVp;
      string PtaUDiWaNY;
      string ieTssawXkT;
      string JUKoTUHCBy;
      string LoUMtrshgk;
      if(ATyloXmQuS == iRASsFslVI){FRHOlCPalE = true;}
      else if(iRASsFslVI == ATyloXmQuS){eYgqSUWxSO = true;}
      if(raPbPTkAnm == KFHutRVXDf){mlHBgtilBi = true;}
      else if(KFHutRVXDf == raPbPTkAnm){eOmOgAhbrw = true;}
      if(qpSiZGVIuc == uzIGxCpzKB){bUZPNsKHzB = true;}
      else if(uzIGxCpzKB == qpSiZGVIuc){rBRIoLtZKi = true;}
      if(HqAOpjPdRo == EbhggVipDJ){hNqAOqNuCQ = true;}
      else if(EbhggVipDJ == HqAOpjPdRo){paDRImJigX = true;}
      if(hdqXbISlzx == lTDjUcsVnV){EgPwLZgTfz = true;}
      else if(lTDjUcsVnV == hdqXbISlzx){DiZbzjhebX = true;}
      if(MbjaVKAOMh == hjTfeiJsVp){IGgxJjrqBs = true;}
      else if(hjTfeiJsVp == MbjaVKAOMh){NdlcscHYBG = true;}
      if(BeVSLBZBlf == PtaUDiWaNY){rIakWYuHlo = true;}
      else if(PtaUDiWaNY == BeVSLBZBlf){axljXDLVFt = true;}
      if(DHhyEMzuHQ == ieTssawXkT){gnijeuFcEm = true;}
      if(miJxPeGZrf == JUKoTUHCBy){Lqazsafspd = true;}
      if(iAQinDIXMa == LoUMtrshgk){zVsJYuFdYl = true;}
      while(ieTssawXkT == DHhyEMzuHQ){pytTrJboIF = true;}
      while(JUKoTUHCBy == JUKoTUHCBy){dOylULoaYf = true;}
      while(LoUMtrshgk == LoUMtrshgk){ekhZxGwoDw = true;}
      if(FRHOlCPalE == true){FRHOlCPalE = false;}
      if(mlHBgtilBi == true){mlHBgtilBi = false;}
      if(bUZPNsKHzB == true){bUZPNsKHzB = false;}
      if(hNqAOqNuCQ == true){hNqAOqNuCQ = false;}
      if(EgPwLZgTfz == true){EgPwLZgTfz = false;}
      if(IGgxJjrqBs == true){IGgxJjrqBs = false;}
      if(rIakWYuHlo == true){rIakWYuHlo = false;}
      if(gnijeuFcEm == true){gnijeuFcEm = false;}
      if(Lqazsafspd == true){Lqazsafspd = false;}
      if(zVsJYuFdYl == true){zVsJYuFdYl = false;}
      if(eYgqSUWxSO == true){eYgqSUWxSO = false;}
      if(eOmOgAhbrw == true){eOmOgAhbrw = false;}
      if(rBRIoLtZKi == true){rBRIoLtZKi = false;}
      if(paDRImJigX == true){paDRImJigX = false;}
      if(DiZbzjhebX == true){DiZbzjhebX = false;}
      if(NdlcscHYBG == true){NdlcscHYBG = false;}
      if(axljXDLVFt == true){axljXDLVFt = false;}
      if(pytTrJboIF == true){pytTrJboIF = false;}
      if(dOylULoaYf == true){dOylULoaYf = false;}
      if(ekhZxGwoDw == true){ekhZxGwoDw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHDDKOZPNT
{ 
  void DImjDcPUZr()
  { 
      bool BUAPedLtff = false;
      bool ABnxRmKXQg = false;
      bool iYNDWdLfNw = false;
      bool plTtqTKaCe = false;
      bool lOGIgJSYnV = false;
      bool MNYcubGxsB = false;
      bool SfgipOgsGx = false;
      bool biUltUSEVM = false;
      bool LlqqjbMqzO = false;
      bool NNhAMGgWSR = false;
      bool bYRqtcrmia = false;
      bool JBafpfnozN = false;
      bool CptriOBTYm = false;
      bool mulEklTAxG = false;
      bool jZIYEMlCKf = false;
      bool RrWFPldZHf = false;
      bool bYNumOPWtD = false;
      bool LnrscbhVmW = false;
      bool byIrUuXgnz = false;
      bool ItrQdLLMkp = false;
      string uCQjWOVDKZ;
      string ZqNVyUloZo;
      string KDbzIOcRcb;
      string RPlfiimIdG;
      string LUezgbcxJz;
      string YBWYQrZQbI;
      string kDahHJFgmO;
      string hcKTcpXcSf;
      string keIcDPsMPq;
      string JVfVVHtwqW;
      string VwKuRuqDwa;
      string TwyuWFuxer;
      string QsRwELxoxV;
      string uakuKoUMLH;
      string YpQnWMWkyP;
      string MxRzGcdNpF;
      string yBFZerLCjh;
      string khkWTabcYr;
      string nLqhJyJlog;
      string KGWFJWkpJe;
      if(uCQjWOVDKZ == VwKuRuqDwa){BUAPedLtff = true;}
      else if(VwKuRuqDwa == uCQjWOVDKZ){bYRqtcrmia = true;}
      if(ZqNVyUloZo == TwyuWFuxer){ABnxRmKXQg = true;}
      else if(TwyuWFuxer == ZqNVyUloZo){JBafpfnozN = true;}
      if(KDbzIOcRcb == QsRwELxoxV){iYNDWdLfNw = true;}
      else if(QsRwELxoxV == KDbzIOcRcb){CptriOBTYm = true;}
      if(RPlfiimIdG == uakuKoUMLH){plTtqTKaCe = true;}
      else if(uakuKoUMLH == RPlfiimIdG){mulEklTAxG = true;}
      if(LUezgbcxJz == YpQnWMWkyP){lOGIgJSYnV = true;}
      else if(YpQnWMWkyP == LUezgbcxJz){jZIYEMlCKf = true;}
      if(YBWYQrZQbI == MxRzGcdNpF){MNYcubGxsB = true;}
      else if(MxRzGcdNpF == YBWYQrZQbI){RrWFPldZHf = true;}
      if(kDahHJFgmO == yBFZerLCjh){SfgipOgsGx = true;}
      else if(yBFZerLCjh == kDahHJFgmO){bYNumOPWtD = true;}
      if(hcKTcpXcSf == khkWTabcYr){biUltUSEVM = true;}
      if(keIcDPsMPq == nLqhJyJlog){LlqqjbMqzO = true;}
      if(JVfVVHtwqW == KGWFJWkpJe){NNhAMGgWSR = true;}
      while(khkWTabcYr == hcKTcpXcSf){LnrscbhVmW = true;}
      while(nLqhJyJlog == nLqhJyJlog){byIrUuXgnz = true;}
      while(KGWFJWkpJe == KGWFJWkpJe){ItrQdLLMkp = true;}
      if(BUAPedLtff == true){BUAPedLtff = false;}
      if(ABnxRmKXQg == true){ABnxRmKXQg = false;}
      if(iYNDWdLfNw == true){iYNDWdLfNw = false;}
      if(plTtqTKaCe == true){plTtqTKaCe = false;}
      if(lOGIgJSYnV == true){lOGIgJSYnV = false;}
      if(MNYcubGxsB == true){MNYcubGxsB = false;}
      if(SfgipOgsGx == true){SfgipOgsGx = false;}
      if(biUltUSEVM == true){biUltUSEVM = false;}
      if(LlqqjbMqzO == true){LlqqjbMqzO = false;}
      if(NNhAMGgWSR == true){NNhAMGgWSR = false;}
      if(bYRqtcrmia == true){bYRqtcrmia = false;}
      if(JBafpfnozN == true){JBafpfnozN = false;}
      if(CptriOBTYm == true){CptriOBTYm = false;}
      if(mulEklTAxG == true){mulEklTAxG = false;}
      if(jZIYEMlCKf == true){jZIYEMlCKf = false;}
      if(RrWFPldZHf == true){RrWFPldZHf = false;}
      if(bYNumOPWtD == true){bYNumOPWtD = false;}
      if(LnrscbhVmW == true){LnrscbhVmW = false;}
      if(byIrUuXgnz == true){byIrUuXgnz = false;}
      if(ItrQdLLMkp == true){ItrQdLLMkp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWFSGJOALB
{ 
  void fiXwUHufXr()
  { 
      bool oxIhSxrntd = false;
      bool llJeSTqOxP = false;
      bool KJGaZoUJkJ = false;
      bool jbgbfAQPqE = false;
      bool yUDxdPFqGL = false;
      bool NSfHleqgHd = false;
      bool ciCksJFgyR = false;
      bool DbXsRoGIwJ = false;
      bool icCYwQwYpA = false;
      bool IjHNaPRSET = false;
      bool KXrnIkumpx = false;
      bool Yijytzfcnb = false;
      bool NfqyJTTJRB = false;
      bool WmEbzLjOQK = false;
      bool VJhraZzJTb = false;
      bool jodbGdgteo = false;
      bool RkUoZkdHyi = false;
      bool OQMcFExyWi = false;
      bool TKpoQhJbVU = false;
      bool doibsknsSo = false;
      string bhBlaHiCVi;
      string JpkbdwLPyo;
      string dlsDDjjirm;
      string gVsxmAijYu;
      string zKcTJVONuH;
      string toIcrooyhq;
      string XzJiBmwnnd;
      string NbpDoSIZsg;
      string UWmjrrMPEx;
      string LjBgWAAtRV;
      string YaYRtSyFnZ;
      string gOEBWBMYpI;
      string ZgjpRcZIfo;
      string SNHWIsxVpY;
      string tHbeQweAKV;
      string maEJwqqizQ;
      string soYyGTHgrc;
      string DpiQOSFEZU;
      string yYxJBqIyaQ;
      string COVYfEhcXx;
      if(bhBlaHiCVi == YaYRtSyFnZ){oxIhSxrntd = true;}
      else if(YaYRtSyFnZ == bhBlaHiCVi){KXrnIkumpx = true;}
      if(JpkbdwLPyo == gOEBWBMYpI){llJeSTqOxP = true;}
      else if(gOEBWBMYpI == JpkbdwLPyo){Yijytzfcnb = true;}
      if(dlsDDjjirm == ZgjpRcZIfo){KJGaZoUJkJ = true;}
      else if(ZgjpRcZIfo == dlsDDjjirm){NfqyJTTJRB = true;}
      if(gVsxmAijYu == SNHWIsxVpY){jbgbfAQPqE = true;}
      else if(SNHWIsxVpY == gVsxmAijYu){WmEbzLjOQK = true;}
      if(zKcTJVONuH == tHbeQweAKV){yUDxdPFqGL = true;}
      else if(tHbeQweAKV == zKcTJVONuH){VJhraZzJTb = true;}
      if(toIcrooyhq == maEJwqqizQ){NSfHleqgHd = true;}
      else if(maEJwqqizQ == toIcrooyhq){jodbGdgteo = true;}
      if(XzJiBmwnnd == soYyGTHgrc){ciCksJFgyR = true;}
      else if(soYyGTHgrc == XzJiBmwnnd){RkUoZkdHyi = true;}
      if(NbpDoSIZsg == DpiQOSFEZU){DbXsRoGIwJ = true;}
      if(UWmjrrMPEx == yYxJBqIyaQ){icCYwQwYpA = true;}
      if(LjBgWAAtRV == COVYfEhcXx){IjHNaPRSET = true;}
      while(DpiQOSFEZU == NbpDoSIZsg){OQMcFExyWi = true;}
      while(yYxJBqIyaQ == yYxJBqIyaQ){TKpoQhJbVU = true;}
      while(COVYfEhcXx == COVYfEhcXx){doibsknsSo = true;}
      if(oxIhSxrntd == true){oxIhSxrntd = false;}
      if(llJeSTqOxP == true){llJeSTqOxP = false;}
      if(KJGaZoUJkJ == true){KJGaZoUJkJ = false;}
      if(jbgbfAQPqE == true){jbgbfAQPqE = false;}
      if(yUDxdPFqGL == true){yUDxdPFqGL = false;}
      if(NSfHleqgHd == true){NSfHleqgHd = false;}
      if(ciCksJFgyR == true){ciCksJFgyR = false;}
      if(DbXsRoGIwJ == true){DbXsRoGIwJ = false;}
      if(icCYwQwYpA == true){icCYwQwYpA = false;}
      if(IjHNaPRSET == true){IjHNaPRSET = false;}
      if(KXrnIkumpx == true){KXrnIkumpx = false;}
      if(Yijytzfcnb == true){Yijytzfcnb = false;}
      if(NfqyJTTJRB == true){NfqyJTTJRB = false;}
      if(WmEbzLjOQK == true){WmEbzLjOQK = false;}
      if(VJhraZzJTb == true){VJhraZzJTb = false;}
      if(jodbGdgteo == true){jodbGdgteo = false;}
      if(RkUoZkdHyi == true){RkUoZkdHyi = false;}
      if(OQMcFExyWi == true){OQMcFExyWi = false;}
      if(TKpoQhJbVU == true){TKpoQhJbVU = false;}
      if(doibsknsSo == true){doibsknsSo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDWRMXEMLV
{ 
  void ENxhPHrWjW()
  { 
      bool RMjcPakNSK = false;
      bool mKHiBLzFNA = false;
      bool DNEkGQWiIk = false;
      bool TxmIXuZxCR = false;
      bool oUAyEUEOlP = false;
      bool XdVFmEHzWz = false;
      bool DBEgpoXzKF = false;
      bool lCCwKiMGgk = false;
      bool LHwsNpbhVT = false;
      bool maaDNnPTHP = false;
      bool xEDfcVaYtE = false;
      bool qBRkmwELTA = false;
      bool NpdqSKbziW = false;
      bool SsyQnGEQPq = false;
      bool OCmQblIoPQ = false;
      bool iEAHCHaMNR = false;
      bool tboXkyCBxg = false;
      bool qnubkKCMOf = false;
      bool CliRnOrqOg = false;
      bool frCxxmNPed = false;
      string AexspOmmmZ;
      string hHiCtfVyuk;
      string CSaUAHNMbM;
      string GeBQddmtUr;
      string LoGzZxuJck;
      string UsmRYgDcrh;
      string BZLZSCGRYP;
      string racCYNMbtD;
      string MEjprNrirw;
      string aJClpkdfgX;
      string qcjNrtQjsK;
      string TbioVxpUhF;
      string KWZbniXpLm;
      string igtVLiTVxx;
      string wHpgcyZNPs;
      string uIyaNTDHYJ;
      string VZXGblgNcm;
      string cTWjIDgrzo;
      string IKZSraiTIq;
      string fMxnaWijFp;
      if(AexspOmmmZ == qcjNrtQjsK){RMjcPakNSK = true;}
      else if(qcjNrtQjsK == AexspOmmmZ){xEDfcVaYtE = true;}
      if(hHiCtfVyuk == TbioVxpUhF){mKHiBLzFNA = true;}
      else if(TbioVxpUhF == hHiCtfVyuk){qBRkmwELTA = true;}
      if(CSaUAHNMbM == KWZbniXpLm){DNEkGQWiIk = true;}
      else if(KWZbniXpLm == CSaUAHNMbM){NpdqSKbziW = true;}
      if(GeBQddmtUr == igtVLiTVxx){TxmIXuZxCR = true;}
      else if(igtVLiTVxx == GeBQddmtUr){SsyQnGEQPq = true;}
      if(LoGzZxuJck == wHpgcyZNPs){oUAyEUEOlP = true;}
      else if(wHpgcyZNPs == LoGzZxuJck){OCmQblIoPQ = true;}
      if(UsmRYgDcrh == uIyaNTDHYJ){XdVFmEHzWz = true;}
      else if(uIyaNTDHYJ == UsmRYgDcrh){iEAHCHaMNR = true;}
      if(BZLZSCGRYP == VZXGblgNcm){DBEgpoXzKF = true;}
      else if(VZXGblgNcm == BZLZSCGRYP){tboXkyCBxg = true;}
      if(racCYNMbtD == cTWjIDgrzo){lCCwKiMGgk = true;}
      if(MEjprNrirw == IKZSraiTIq){LHwsNpbhVT = true;}
      if(aJClpkdfgX == fMxnaWijFp){maaDNnPTHP = true;}
      while(cTWjIDgrzo == racCYNMbtD){qnubkKCMOf = true;}
      while(IKZSraiTIq == IKZSraiTIq){CliRnOrqOg = true;}
      while(fMxnaWijFp == fMxnaWijFp){frCxxmNPed = true;}
      if(RMjcPakNSK == true){RMjcPakNSK = false;}
      if(mKHiBLzFNA == true){mKHiBLzFNA = false;}
      if(DNEkGQWiIk == true){DNEkGQWiIk = false;}
      if(TxmIXuZxCR == true){TxmIXuZxCR = false;}
      if(oUAyEUEOlP == true){oUAyEUEOlP = false;}
      if(XdVFmEHzWz == true){XdVFmEHzWz = false;}
      if(DBEgpoXzKF == true){DBEgpoXzKF = false;}
      if(lCCwKiMGgk == true){lCCwKiMGgk = false;}
      if(LHwsNpbhVT == true){LHwsNpbhVT = false;}
      if(maaDNnPTHP == true){maaDNnPTHP = false;}
      if(xEDfcVaYtE == true){xEDfcVaYtE = false;}
      if(qBRkmwELTA == true){qBRkmwELTA = false;}
      if(NpdqSKbziW == true){NpdqSKbziW = false;}
      if(SsyQnGEQPq == true){SsyQnGEQPq = false;}
      if(OCmQblIoPQ == true){OCmQblIoPQ = false;}
      if(iEAHCHaMNR == true){iEAHCHaMNR = false;}
      if(tboXkyCBxg == true){tboXkyCBxg = false;}
      if(qnubkKCMOf == true){qnubkKCMOf = false;}
      if(CliRnOrqOg == true){CliRnOrqOg = false;}
      if(frCxxmNPed == true){frCxxmNPed = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGEFCUQKWS
{ 
  void ZQVrBSVEuX()
  { 
      bool OYyGJHclLy = false;
      bool rTGIRJckyM = false;
      bool VZkDYrEMWL = false;
      bool ibEheUCYGM = false;
      bool KFpUhBykOa = false;
      bool NQRlTnnugR = false;
      bool CPOAPPPXcx = false;
      bool HDekCQjPVX = false;
      bool sTxwxSKRNq = false;
      bool fHqnJtpoFR = false;
      bool lZHRSKlfjC = false;
      bool DXYJYiSSDw = false;
      bool FxJlQzLpaH = false;
      bool auKEkSMfcm = false;
      bool gdhLmIhgPa = false;
      bool bWlIMoPUAS = false;
      bool yuFbbINUYF = false;
      bool WlpPPaOyzI = false;
      bool ReZAfDJBrw = false;
      bool CqeJokYGie = false;
      string nHGGKgRnKt;
      string fAzBYjeUNC;
      string wMkUqDPnXX;
      string DNunbFYhxD;
      string cbgFqRjdFt;
      string mNjSebWlOH;
      string RcQmpSEKZS;
      string KxXKZUeecY;
      string SlicjocbIz;
      string imSplzKtOY;
      string NZDljopZsK;
      string xrIonetmCB;
      string obCZjXdhXZ;
      string KjPDLshwsu;
      string zDiyCpdcBG;
      string FWrNjkXcCL;
      string KIBSzMbEdu;
      string xytGBksDWs;
      string sBfQUmqBTZ;
      string VEsgjpBQyo;
      if(nHGGKgRnKt == NZDljopZsK){OYyGJHclLy = true;}
      else if(NZDljopZsK == nHGGKgRnKt){lZHRSKlfjC = true;}
      if(fAzBYjeUNC == xrIonetmCB){rTGIRJckyM = true;}
      else if(xrIonetmCB == fAzBYjeUNC){DXYJYiSSDw = true;}
      if(wMkUqDPnXX == obCZjXdhXZ){VZkDYrEMWL = true;}
      else if(obCZjXdhXZ == wMkUqDPnXX){FxJlQzLpaH = true;}
      if(DNunbFYhxD == KjPDLshwsu){ibEheUCYGM = true;}
      else if(KjPDLshwsu == DNunbFYhxD){auKEkSMfcm = true;}
      if(cbgFqRjdFt == zDiyCpdcBG){KFpUhBykOa = true;}
      else if(zDiyCpdcBG == cbgFqRjdFt){gdhLmIhgPa = true;}
      if(mNjSebWlOH == FWrNjkXcCL){NQRlTnnugR = true;}
      else if(FWrNjkXcCL == mNjSebWlOH){bWlIMoPUAS = true;}
      if(RcQmpSEKZS == KIBSzMbEdu){CPOAPPPXcx = true;}
      else if(KIBSzMbEdu == RcQmpSEKZS){yuFbbINUYF = true;}
      if(KxXKZUeecY == xytGBksDWs){HDekCQjPVX = true;}
      if(SlicjocbIz == sBfQUmqBTZ){sTxwxSKRNq = true;}
      if(imSplzKtOY == VEsgjpBQyo){fHqnJtpoFR = true;}
      while(xytGBksDWs == KxXKZUeecY){WlpPPaOyzI = true;}
      while(sBfQUmqBTZ == sBfQUmqBTZ){ReZAfDJBrw = true;}
      while(VEsgjpBQyo == VEsgjpBQyo){CqeJokYGie = true;}
      if(OYyGJHclLy == true){OYyGJHclLy = false;}
      if(rTGIRJckyM == true){rTGIRJckyM = false;}
      if(VZkDYrEMWL == true){VZkDYrEMWL = false;}
      if(ibEheUCYGM == true){ibEheUCYGM = false;}
      if(KFpUhBykOa == true){KFpUhBykOa = false;}
      if(NQRlTnnugR == true){NQRlTnnugR = false;}
      if(CPOAPPPXcx == true){CPOAPPPXcx = false;}
      if(HDekCQjPVX == true){HDekCQjPVX = false;}
      if(sTxwxSKRNq == true){sTxwxSKRNq = false;}
      if(fHqnJtpoFR == true){fHqnJtpoFR = false;}
      if(lZHRSKlfjC == true){lZHRSKlfjC = false;}
      if(DXYJYiSSDw == true){DXYJYiSSDw = false;}
      if(FxJlQzLpaH == true){FxJlQzLpaH = false;}
      if(auKEkSMfcm == true){auKEkSMfcm = false;}
      if(gdhLmIhgPa == true){gdhLmIhgPa = false;}
      if(bWlIMoPUAS == true){bWlIMoPUAS = false;}
      if(yuFbbINUYF == true){yuFbbINUYF = false;}
      if(WlpPPaOyzI == true){WlpPPaOyzI = false;}
      if(ReZAfDJBrw == true){ReZAfDJBrw = false;}
      if(CqeJokYGie == true){CqeJokYGie = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YPGQIMUZDP
{ 
  void LuPckhVGZn()
  { 
      bool arYtlbxQWJ = false;
      bool ZjfGrbKrSG = false;
      bool CfapUxpMzn = false;
      bool eiXAdJlJDw = false;
      bool sYTrElteis = false;
      bool XhTrJuQiYo = false;
      bool ljQhdpLebi = false;
      bool oBoWMdLiki = false;
      bool DKcFQxPepi = false;
      bool rDjOKIIlON = false;
      bool ZOCzDVswff = false;
      bool ihxpkaHKQf = false;
      bool agnsplQZMD = false;
      bool UZUWJoIdCt = false;
      bool ETzKzKFtci = false;
      bool ByUhmsZJIR = false;
      bool ESjbKIMZfw = false;
      bool SdIWaHgdsf = false;
      bool fWwcCWFljQ = false;
      bool OzUkoliXzp = false;
      string unRrmBTlRV;
      string eXKaPoHUUW;
      string TkidVQghom;
      string zYYVjIDMaU;
      string PttkiwODUC;
      string mxhZzKFnVV;
      string UlxdVFyoqG;
      string kutAGZqytY;
      string CdMmABqyVY;
      string DOpEAdwPOd;
      string xZLOQqDhTZ;
      string TGtwTpZKdU;
      string OASSCWEozb;
      string cajQbcSxVI;
      string xIdwFxUskJ;
      string ElksOwGsLt;
      string mOhqxrVcUq;
      string XbnUWFVWMF;
      string BKDpXqopBe;
      string VZlbViZmyM;
      if(unRrmBTlRV == xZLOQqDhTZ){arYtlbxQWJ = true;}
      else if(xZLOQqDhTZ == unRrmBTlRV){ZOCzDVswff = true;}
      if(eXKaPoHUUW == TGtwTpZKdU){ZjfGrbKrSG = true;}
      else if(TGtwTpZKdU == eXKaPoHUUW){ihxpkaHKQf = true;}
      if(TkidVQghom == OASSCWEozb){CfapUxpMzn = true;}
      else if(OASSCWEozb == TkidVQghom){agnsplQZMD = true;}
      if(zYYVjIDMaU == cajQbcSxVI){eiXAdJlJDw = true;}
      else if(cajQbcSxVI == zYYVjIDMaU){UZUWJoIdCt = true;}
      if(PttkiwODUC == xIdwFxUskJ){sYTrElteis = true;}
      else if(xIdwFxUskJ == PttkiwODUC){ETzKzKFtci = true;}
      if(mxhZzKFnVV == ElksOwGsLt){XhTrJuQiYo = true;}
      else if(ElksOwGsLt == mxhZzKFnVV){ByUhmsZJIR = true;}
      if(UlxdVFyoqG == mOhqxrVcUq){ljQhdpLebi = true;}
      else if(mOhqxrVcUq == UlxdVFyoqG){ESjbKIMZfw = true;}
      if(kutAGZqytY == XbnUWFVWMF){oBoWMdLiki = true;}
      if(CdMmABqyVY == BKDpXqopBe){DKcFQxPepi = true;}
      if(DOpEAdwPOd == VZlbViZmyM){rDjOKIIlON = true;}
      while(XbnUWFVWMF == kutAGZqytY){SdIWaHgdsf = true;}
      while(BKDpXqopBe == BKDpXqopBe){fWwcCWFljQ = true;}
      while(VZlbViZmyM == VZlbViZmyM){OzUkoliXzp = true;}
      if(arYtlbxQWJ == true){arYtlbxQWJ = false;}
      if(ZjfGrbKrSG == true){ZjfGrbKrSG = false;}
      if(CfapUxpMzn == true){CfapUxpMzn = false;}
      if(eiXAdJlJDw == true){eiXAdJlJDw = false;}
      if(sYTrElteis == true){sYTrElteis = false;}
      if(XhTrJuQiYo == true){XhTrJuQiYo = false;}
      if(ljQhdpLebi == true){ljQhdpLebi = false;}
      if(oBoWMdLiki == true){oBoWMdLiki = false;}
      if(DKcFQxPepi == true){DKcFQxPepi = false;}
      if(rDjOKIIlON == true){rDjOKIIlON = false;}
      if(ZOCzDVswff == true){ZOCzDVswff = false;}
      if(ihxpkaHKQf == true){ihxpkaHKQf = false;}
      if(agnsplQZMD == true){agnsplQZMD = false;}
      if(UZUWJoIdCt == true){UZUWJoIdCt = false;}
      if(ETzKzKFtci == true){ETzKzKFtci = false;}
      if(ByUhmsZJIR == true){ByUhmsZJIR = false;}
      if(ESjbKIMZfw == true){ESjbKIMZfw = false;}
      if(SdIWaHgdsf == true){SdIWaHgdsf = false;}
      if(fWwcCWFljQ == true){fWwcCWFljQ = false;}
      if(OzUkoliXzp == true){OzUkoliXzp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHDYZTYJJF
{ 
  void JLKfpaqpUy()
  { 
      bool bgOGTHqyqt = false;
      bool SAsgFhQcTT = false;
      bool UxrRabqiNc = false;
      bool qLXgMcdUof = false;
      bool PtQnhsbThW = false;
      bool wFGTldoxfr = false;
      bool QIjNDGbMUc = false;
      bool EwmnEZfDjg = false;
      bool AWAqfkFEth = false;
      bool ngnxOHKDka = false;
      bool QPzFSARROL = false;
      bool ykNyrsHshR = false;
      bool BXSlnXHpYx = false;
      bool PcSIPjXuXf = false;
      bool SmohjDSpFV = false;
      bool zRVSYswMQu = false;
      bool sbsRwVREhH = false;
      bool VLUByOikCk = false;
      bool ERjDxyGAjW = false;
      bool nKdcmpsWkN = false;
      string gPJHnloprG;
      string YkNBrohfIG;
      string UdzMFTqHaK;
      string GsjZwsjFXN;
      string zGAdtaawqn;
      string cDJEMCQwBU;
      string ugOhzeBnEy;
      string FcHtGOdUSe;
      string stQmgCjfNt;
      string cmDDSRqSeO;
      string ZlqriAwOxy;
      string YudWaAQbAx;
      string uUaJVSYDbo;
      string WKpDFGDXEg;
      string GUiOVgIfbR;
      string APRhTELhVP;
      string armIaNFaRU;
      string xsXTpZlLnn;
      string KrbJnHrIiA;
      string tVBnFNhZmH;
      if(gPJHnloprG == ZlqriAwOxy){bgOGTHqyqt = true;}
      else if(ZlqriAwOxy == gPJHnloprG){QPzFSARROL = true;}
      if(YkNBrohfIG == YudWaAQbAx){SAsgFhQcTT = true;}
      else if(YudWaAQbAx == YkNBrohfIG){ykNyrsHshR = true;}
      if(UdzMFTqHaK == uUaJVSYDbo){UxrRabqiNc = true;}
      else if(uUaJVSYDbo == UdzMFTqHaK){BXSlnXHpYx = true;}
      if(GsjZwsjFXN == WKpDFGDXEg){qLXgMcdUof = true;}
      else if(WKpDFGDXEg == GsjZwsjFXN){PcSIPjXuXf = true;}
      if(zGAdtaawqn == GUiOVgIfbR){PtQnhsbThW = true;}
      else if(GUiOVgIfbR == zGAdtaawqn){SmohjDSpFV = true;}
      if(cDJEMCQwBU == APRhTELhVP){wFGTldoxfr = true;}
      else if(APRhTELhVP == cDJEMCQwBU){zRVSYswMQu = true;}
      if(ugOhzeBnEy == armIaNFaRU){QIjNDGbMUc = true;}
      else if(armIaNFaRU == ugOhzeBnEy){sbsRwVREhH = true;}
      if(FcHtGOdUSe == xsXTpZlLnn){EwmnEZfDjg = true;}
      if(stQmgCjfNt == KrbJnHrIiA){AWAqfkFEth = true;}
      if(cmDDSRqSeO == tVBnFNhZmH){ngnxOHKDka = true;}
      while(xsXTpZlLnn == FcHtGOdUSe){VLUByOikCk = true;}
      while(KrbJnHrIiA == KrbJnHrIiA){ERjDxyGAjW = true;}
      while(tVBnFNhZmH == tVBnFNhZmH){nKdcmpsWkN = true;}
      if(bgOGTHqyqt == true){bgOGTHqyqt = false;}
      if(SAsgFhQcTT == true){SAsgFhQcTT = false;}
      if(UxrRabqiNc == true){UxrRabqiNc = false;}
      if(qLXgMcdUof == true){qLXgMcdUof = false;}
      if(PtQnhsbThW == true){PtQnhsbThW = false;}
      if(wFGTldoxfr == true){wFGTldoxfr = false;}
      if(QIjNDGbMUc == true){QIjNDGbMUc = false;}
      if(EwmnEZfDjg == true){EwmnEZfDjg = false;}
      if(AWAqfkFEth == true){AWAqfkFEth = false;}
      if(ngnxOHKDka == true){ngnxOHKDka = false;}
      if(QPzFSARROL == true){QPzFSARROL = false;}
      if(ykNyrsHshR == true){ykNyrsHshR = false;}
      if(BXSlnXHpYx == true){BXSlnXHpYx = false;}
      if(PcSIPjXuXf == true){PcSIPjXuXf = false;}
      if(SmohjDSpFV == true){SmohjDSpFV = false;}
      if(zRVSYswMQu == true){zRVSYswMQu = false;}
      if(sbsRwVREhH == true){sbsRwVREhH = false;}
      if(VLUByOikCk == true){VLUByOikCk = false;}
      if(ERjDxyGAjW == true){ERjDxyGAjW = false;}
      if(nKdcmpsWkN == true){nKdcmpsWkN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROKNQIGKBC
{ 
  void ebKWLEfZFM()
  { 
      bool daMBEqBQOY = false;
      bool CgmzjAJOLV = false;
      bool iiEpUyZSFe = false;
      bool DYWOjDNeXd = false;
      bool JTaxeWMVhH = false;
      bool fWzJstVVfG = false;
      bool RhKiUcKXOf = false;
      bool lepgMPHHKy = false;
      bool lDkyzgZMVo = false;
      bool hqyRMaIqcC = false;
      bool LnGBUBfRxd = false;
      bool lOLhTNwMjm = false;
      bool CyCZytgYUk = false;
      bool GPdIlxwjdx = false;
      bool BIOqCSfPxy = false;
      bool ewHozNlgCZ = false;
      bool UHwMWVjDuW = false;
      bool RMilltiKWf = false;
      bool OQaWGKIoIX = false;
      bool KPgDctMCUf = false;
      string IlnluytXJG;
      string zCeYXotkKb;
      string GhcLItcEZs;
      string ZhsXFHqGnA;
      string FDqSwYGisu;
      string ZthLgZIbcA;
      string UoxPgQJGSP;
      string xnwKWCpKPj;
      string mtLeTezgqf;
      string zPcnePFake;
      string PzQcxkyXod;
      string ixMsMacSwB;
      string QbPmPhKHfH;
      string xPYjUnchgh;
      string fbrMwCDjaD;
      string llejNmjdNO;
      string apqggTXbXY;
      string ytkNUojCqN;
      string eZgcVKkoWh;
      string DzURHpkKfb;
      if(IlnluytXJG == PzQcxkyXod){daMBEqBQOY = true;}
      else if(PzQcxkyXod == IlnluytXJG){LnGBUBfRxd = true;}
      if(zCeYXotkKb == ixMsMacSwB){CgmzjAJOLV = true;}
      else if(ixMsMacSwB == zCeYXotkKb){lOLhTNwMjm = true;}
      if(GhcLItcEZs == QbPmPhKHfH){iiEpUyZSFe = true;}
      else if(QbPmPhKHfH == GhcLItcEZs){CyCZytgYUk = true;}
      if(ZhsXFHqGnA == xPYjUnchgh){DYWOjDNeXd = true;}
      else if(xPYjUnchgh == ZhsXFHqGnA){GPdIlxwjdx = true;}
      if(FDqSwYGisu == fbrMwCDjaD){JTaxeWMVhH = true;}
      else if(fbrMwCDjaD == FDqSwYGisu){BIOqCSfPxy = true;}
      if(ZthLgZIbcA == llejNmjdNO){fWzJstVVfG = true;}
      else if(llejNmjdNO == ZthLgZIbcA){ewHozNlgCZ = true;}
      if(UoxPgQJGSP == apqggTXbXY){RhKiUcKXOf = true;}
      else if(apqggTXbXY == UoxPgQJGSP){UHwMWVjDuW = true;}
      if(xnwKWCpKPj == ytkNUojCqN){lepgMPHHKy = true;}
      if(mtLeTezgqf == eZgcVKkoWh){lDkyzgZMVo = true;}
      if(zPcnePFake == DzURHpkKfb){hqyRMaIqcC = true;}
      while(ytkNUojCqN == xnwKWCpKPj){RMilltiKWf = true;}
      while(eZgcVKkoWh == eZgcVKkoWh){OQaWGKIoIX = true;}
      while(DzURHpkKfb == DzURHpkKfb){KPgDctMCUf = true;}
      if(daMBEqBQOY == true){daMBEqBQOY = false;}
      if(CgmzjAJOLV == true){CgmzjAJOLV = false;}
      if(iiEpUyZSFe == true){iiEpUyZSFe = false;}
      if(DYWOjDNeXd == true){DYWOjDNeXd = false;}
      if(JTaxeWMVhH == true){JTaxeWMVhH = false;}
      if(fWzJstVVfG == true){fWzJstVVfG = false;}
      if(RhKiUcKXOf == true){RhKiUcKXOf = false;}
      if(lepgMPHHKy == true){lepgMPHHKy = false;}
      if(lDkyzgZMVo == true){lDkyzgZMVo = false;}
      if(hqyRMaIqcC == true){hqyRMaIqcC = false;}
      if(LnGBUBfRxd == true){LnGBUBfRxd = false;}
      if(lOLhTNwMjm == true){lOLhTNwMjm = false;}
      if(CyCZytgYUk == true){CyCZytgYUk = false;}
      if(GPdIlxwjdx == true){GPdIlxwjdx = false;}
      if(BIOqCSfPxy == true){BIOqCSfPxy = false;}
      if(ewHozNlgCZ == true){ewHozNlgCZ = false;}
      if(UHwMWVjDuW == true){UHwMWVjDuW = false;}
      if(RMilltiKWf == true){RMilltiKWf = false;}
      if(OQaWGKIoIX == true){OQaWGKIoIX = false;}
      if(KPgDctMCUf == true){KPgDctMCUf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNGAMCEGKP
{ 
  void DxXcVeYgpP()
  { 
      bool uffMpYQZQD = false;
      bool RtpXNqASFy = false;
      bool sYYrJlUqbW = false;
      bool SgJguxaWPq = false;
      bool oIWBmcfynm = false;
      bool fuooxVHnDD = false;
      bool DYxskkjJbP = false;
      bool QcCNJkCWFf = false;
      bool GWDnqWqUjZ = false;
      bool omTLmQLcQB = false;
      bool sWVYWCraeM = false;
      bool SkhWxgVJCN = false;
      bool sPYCZcJqZr = false;
      bool YZFDmiAdQo = false;
      bool eQoXGEEwOG = false;
      bool uCaDHdyTyt = false;
      bool rBAmmseejN = false;
      bool gqrNhcZAwV = false;
      bool XNcTxWzCuJ = false;
      bool kgfWwdPCkN = false;
      string ghmUZrRbNB;
      string iUzsJCTzlB;
      string TEXcmgEnRL;
      string HyEuojlHgj;
      string XGUflBkLnt;
      string weghhcKJgr;
      string ncJBtjPDEZ;
      string PLSCcMiqqk;
      string wrAWPbRWNM;
      string ZcZoutwTkC;
      string lgGOdkMeFU;
      string sSSwuucllR;
      string SrprzmkcGh;
      string PPGnyOlkre;
      string PlRrTHJdsA;
      string QKgSisqOOp;
      string ziYWEcMdxg;
      string JqsHCfaxXq;
      string cHiGQFimFF;
      string WWWCefNtnq;
      if(ghmUZrRbNB == lgGOdkMeFU){uffMpYQZQD = true;}
      else if(lgGOdkMeFU == ghmUZrRbNB){sWVYWCraeM = true;}
      if(iUzsJCTzlB == sSSwuucllR){RtpXNqASFy = true;}
      else if(sSSwuucllR == iUzsJCTzlB){SkhWxgVJCN = true;}
      if(TEXcmgEnRL == SrprzmkcGh){sYYrJlUqbW = true;}
      else if(SrprzmkcGh == TEXcmgEnRL){sPYCZcJqZr = true;}
      if(HyEuojlHgj == PPGnyOlkre){SgJguxaWPq = true;}
      else if(PPGnyOlkre == HyEuojlHgj){YZFDmiAdQo = true;}
      if(XGUflBkLnt == PlRrTHJdsA){oIWBmcfynm = true;}
      else if(PlRrTHJdsA == XGUflBkLnt){eQoXGEEwOG = true;}
      if(weghhcKJgr == QKgSisqOOp){fuooxVHnDD = true;}
      else if(QKgSisqOOp == weghhcKJgr){uCaDHdyTyt = true;}
      if(ncJBtjPDEZ == ziYWEcMdxg){DYxskkjJbP = true;}
      else if(ziYWEcMdxg == ncJBtjPDEZ){rBAmmseejN = true;}
      if(PLSCcMiqqk == JqsHCfaxXq){QcCNJkCWFf = true;}
      if(wrAWPbRWNM == cHiGQFimFF){GWDnqWqUjZ = true;}
      if(ZcZoutwTkC == WWWCefNtnq){omTLmQLcQB = true;}
      while(JqsHCfaxXq == PLSCcMiqqk){gqrNhcZAwV = true;}
      while(cHiGQFimFF == cHiGQFimFF){XNcTxWzCuJ = true;}
      while(WWWCefNtnq == WWWCefNtnq){kgfWwdPCkN = true;}
      if(uffMpYQZQD == true){uffMpYQZQD = false;}
      if(RtpXNqASFy == true){RtpXNqASFy = false;}
      if(sYYrJlUqbW == true){sYYrJlUqbW = false;}
      if(SgJguxaWPq == true){SgJguxaWPq = false;}
      if(oIWBmcfynm == true){oIWBmcfynm = false;}
      if(fuooxVHnDD == true){fuooxVHnDD = false;}
      if(DYxskkjJbP == true){DYxskkjJbP = false;}
      if(QcCNJkCWFf == true){QcCNJkCWFf = false;}
      if(GWDnqWqUjZ == true){GWDnqWqUjZ = false;}
      if(omTLmQLcQB == true){omTLmQLcQB = false;}
      if(sWVYWCraeM == true){sWVYWCraeM = false;}
      if(SkhWxgVJCN == true){SkhWxgVJCN = false;}
      if(sPYCZcJqZr == true){sPYCZcJqZr = false;}
      if(YZFDmiAdQo == true){YZFDmiAdQo = false;}
      if(eQoXGEEwOG == true){eQoXGEEwOG = false;}
      if(uCaDHdyTyt == true){uCaDHdyTyt = false;}
      if(rBAmmseejN == true){rBAmmseejN = false;}
      if(gqrNhcZAwV == true){gqrNhcZAwV = false;}
      if(XNcTxWzCuJ == true){XNcTxWzCuJ = false;}
      if(kgfWwdPCkN == true){kgfWwdPCkN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAIFEJPVUT
{ 
  void FEQISofZKC()
  { 
      bool TELBtjUVCw = false;
      bool jlUFHcBxSw = false;
      bool WMlBaUNVDW = false;
      bool DmBNMZBxou = false;
      bool DzASGefbhn = false;
      bool KqDreHRJZY = false;
      bool WzRerxjGsh = false;
      bool bDIWsXLTuw = false;
      bool nlmPMLiJiF = false;
      bool HqXQYDgVZJ = false;
      bool tYhALGifyG = false;
      bool uyOdjjLCRg = false;
      bool NZXnZkfrxp = false;
      bool qpslBPDmDG = false;
      bool cDKbJJctfo = false;
      bool qdDswUBtZa = false;
      bool aqiIPFFcbU = false;
      bool gXzLDJPwdQ = false;
      bool HkLIyMlzog = false;
      bool NINbekUCME = false;
      string WbBRxaHGJQ;
      string bBUrUbKJhd;
      string fnBjjnlaTS;
      string RHsihPdNmL;
      string ZGJfZePFGU;
      string ENDNyiaQgJ;
      string ngmpzTIkJE;
      string xxVWDYdVKF;
      string XgTzODDejz;
      string oMfdWrTSgF;
      string VduBWHrgKZ;
      string EEGbkHNmbu;
      string QcBKPkQqzL;
      string ELoEiskSbH;
      string LWUKtjGErP;
      string efpkorcjkl;
      string pAgyUrPBrq;
      string VtLUisIqPf;
      string dMyifXUDOp;
      string QAgpQLoVoC;
      if(WbBRxaHGJQ == VduBWHrgKZ){TELBtjUVCw = true;}
      else if(VduBWHrgKZ == WbBRxaHGJQ){tYhALGifyG = true;}
      if(bBUrUbKJhd == EEGbkHNmbu){jlUFHcBxSw = true;}
      else if(EEGbkHNmbu == bBUrUbKJhd){uyOdjjLCRg = true;}
      if(fnBjjnlaTS == QcBKPkQqzL){WMlBaUNVDW = true;}
      else if(QcBKPkQqzL == fnBjjnlaTS){NZXnZkfrxp = true;}
      if(RHsihPdNmL == ELoEiskSbH){DmBNMZBxou = true;}
      else if(ELoEiskSbH == RHsihPdNmL){qpslBPDmDG = true;}
      if(ZGJfZePFGU == LWUKtjGErP){DzASGefbhn = true;}
      else if(LWUKtjGErP == ZGJfZePFGU){cDKbJJctfo = true;}
      if(ENDNyiaQgJ == efpkorcjkl){KqDreHRJZY = true;}
      else if(efpkorcjkl == ENDNyiaQgJ){qdDswUBtZa = true;}
      if(ngmpzTIkJE == pAgyUrPBrq){WzRerxjGsh = true;}
      else if(pAgyUrPBrq == ngmpzTIkJE){aqiIPFFcbU = true;}
      if(xxVWDYdVKF == VtLUisIqPf){bDIWsXLTuw = true;}
      if(XgTzODDejz == dMyifXUDOp){nlmPMLiJiF = true;}
      if(oMfdWrTSgF == QAgpQLoVoC){HqXQYDgVZJ = true;}
      while(VtLUisIqPf == xxVWDYdVKF){gXzLDJPwdQ = true;}
      while(dMyifXUDOp == dMyifXUDOp){HkLIyMlzog = true;}
      while(QAgpQLoVoC == QAgpQLoVoC){NINbekUCME = true;}
      if(TELBtjUVCw == true){TELBtjUVCw = false;}
      if(jlUFHcBxSw == true){jlUFHcBxSw = false;}
      if(WMlBaUNVDW == true){WMlBaUNVDW = false;}
      if(DmBNMZBxou == true){DmBNMZBxou = false;}
      if(DzASGefbhn == true){DzASGefbhn = false;}
      if(KqDreHRJZY == true){KqDreHRJZY = false;}
      if(WzRerxjGsh == true){WzRerxjGsh = false;}
      if(bDIWsXLTuw == true){bDIWsXLTuw = false;}
      if(nlmPMLiJiF == true){nlmPMLiJiF = false;}
      if(HqXQYDgVZJ == true){HqXQYDgVZJ = false;}
      if(tYhALGifyG == true){tYhALGifyG = false;}
      if(uyOdjjLCRg == true){uyOdjjLCRg = false;}
      if(NZXnZkfrxp == true){NZXnZkfrxp = false;}
      if(qpslBPDmDG == true){qpslBPDmDG = false;}
      if(cDKbJJctfo == true){cDKbJJctfo = false;}
      if(qdDswUBtZa == true){qdDswUBtZa = false;}
      if(aqiIPFFcbU == true){aqiIPFFcbU = false;}
      if(gXzLDJPwdQ == true){gXzLDJPwdQ = false;}
      if(HkLIyMlzog == true){HkLIyMlzog = false;}
      if(NINbekUCME == true){NINbekUCME = false;}
    } 
}; 
