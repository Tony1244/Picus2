#include "Client.h"
#include <ctime>
#include <Shlobj.h>
#include "../ConfigPop/cfgmsgpop.h"
#include <stdint.h>
#include "../ImGui/imgui.h"
#include "../Cheat/GrenadeHelper/CGrenadeAPI.h"
#include <chrono>


//[enc_string_enable /]
//[junk_enable /]




namespace Client
{
	//[swap_lines
	int	iScreenWidth = 0;
	int	iScreenHeight = 0;

	char* username = getenv("USERPROFILE");

	//string BaseDir = std::string(username) + "\\Documents\\riptide";
	string BaseDir = "C:\\Users\\Aaron\\Documents\\riptide";
	string LogFile = "";
	string GuiFile = "";
	string IniFile = "";

	vector<string> ConfigList;

	Vector2D	g_vCenterScreen = Vector2D(0.f, 0.f);

	CPlayers*	g_pPlayers = nullptr;
	CRender*	g_pRender = nullptr;
	CGui*		g_pGui = nullptr;
	CTriggerbot* g_pTriggerbot = nullptr;
	CAimbot*	g_pAimbot = nullptr;
	CEsp*		g_pEsp = nullptr;
	CSkin*		g_pSkin = nullptr;
	CMisc*		g_pMisc = nullptr;

	bool		bC4Timer = false;
	int			iC4Timer = 40;

	int			iWeaponID = 0;
	int			iWeaponSelectIndex = WEAPON_DEAGLE;
	int			iWeaponSelectSkinIndex = -1;

	float watermarkRainbowSpeed = 0.005f;
	float watermarkScrollSpeed = 2.5f;
	//[/swap_lines]

	void ReadConfigs(LPCTSTR lpszFileName)
	{
		if (!strstr(lpszFileName, "gui.ini"))
		{
			ConfigList.push_back(lpszFileName);
		}
	}

	void RefreshConfigs()
	{
		CHAR my_documents[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents)))
		{
			ConfigList.clear();
			string ConfigDir = string(my_documents) + "\\riptide\\" "\\*.ini";
			SearchFiles(ConfigDir.c_str(), ReadConfigs, FALSE);
		}
	}

	bool Initialize(IDirect3DDevice9* pDevice)
	{
		
		
		

		


		g_pPlayers = new CPlayers();
		g_pRender = new CRender(pDevice);
		g_pGui = new CGui();
		g_pTriggerbot = new CTriggerbot();
		g_pAimbot = new CAimbot();
		g_pEsp = new CEsp();
		g_pSkin = new CSkin();
		g_pMisc = new CMisc();

		CHAR my_documents[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents)))
		{
			GuiFile = (string(my_documents) + "\\riptide\\" + "gui.ini");
			IniFile = (string(my_documents) + "\\riptide\\" + "settings.ini");
		}

		g_pSkin->InitalizeSkins();

		Settings::LoadSettings(IniFile);

		iWeaponSelectSkinIndex = GetWeaponSkinIndexFromPaintKit(g_SkinChangerCfg[iWeaponSelectIndex].nFallbackPaintKit);

		g_pGui->GUI_Init(pDevice);

		RefreshConfigs();

		return true;
	}

	void Shutdown()
	{
		DELETE_MOD(g_pPlayers);
		DELETE_MOD(g_pRender);
		DELETE_MOD(g_pGui);
		DELETE_MOD(g_pTriggerbot);
		DELETE_MOD(g_pAimbot);
		DELETE_MOD(g_pEsp);
		DELETE_MOD(g_pSkin);
		DELETE_MOD(g_pMisc);
	}

	int get_fps()
	{
		using namespace std::chrono;
		static int count = 0;
		static auto last = high_resolution_clock::now();
		auto now = high_resolution_clock::now();
		static int fps = 0;

		count++;

		if (duration_cast<milliseconds>(now - last).count() > 1000)
		{
			fps = count;
			count = 0;
			last = now;
		}
		return fps;
	}


	void OnRender()
	{

		

		// if (g_pRender && !Interfaces::Engine()->IsTakingScreenshot() && Interfaces::Engine()->IsActiveApp()) - screenshot shit
		if (g_pRender && Interfaces::Engine()->IsActiveApp())
		{
			g_pRender->BeginRender();

			if (g_pGui)
				g_pGui->GUI_Draw_Elements();

			Interfaces::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

			g_vCenterScreen.x = iScreenWidth / 2.f;
			g_vCenterScreen.y = iScreenHeight / 2.f;

			if (Settings::Esp::esp_legitAAWarnings)
			{
				static bool left;
				if (GetAsyncKeyState(VK_RIGHT))
					left = true;
				else if (GetAsyncKeyState(0x44))
					left = true;

				else if (GetAsyncKeyState(VK_LEFT))
					left = false;
				else if (GetAsyncKeyState(0x41))
					left = false;

				if (left)
					g_pRender->Text(15, 650, false, true, Color::SkyBlue(), LEGITAALEFT);
				else if (!left)
					g_pRender->Text(15, 650, false, true, Color::SkyBlue(), LEGITAARIGHT);
			}



			if (Settings::Esp::esp_Watermark)
			{
				//bool rainbow; 
				static float rainbow;
				rainbow += watermarkRainbowSpeed;
				if (rainbow > 1.f) rainbow = 0.f;
				static int u = 0;
				if (u <= 100)                g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "<>riptide");
				if (u > 100 && u <= 200)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "e<>riptid");
				if (u > 200 && u <= 300)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "de<>ripti");
				if (u > 300 && u <= 400)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ide<>ript");
				if (u > 400 && u <= 500)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "tide<>rip");
				if (u > 500 && u <= 600)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ptide<>ri");
				if (u > 600 && u <= 700)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "iptide<>r");
				if (u > 700 && u <= 800)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "riptide<>");
				if (u > 800 && u <= 900)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), ">riptide<");
				if (u > 900 && u <= 1000)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "<>riptide");
				if (u > 1000 && u <= 1100)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "e<>riptid");
				if (u > 1100 && u <= 1200)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "de<>ripti");
				if (u > 1200 && u <= 1300)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ide<>ript");
				if (u > 1300 && u <= 1400)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "tide<>rip");
				if (u > 1400 && u <= 1500)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ptide<>ri");
				if (u > 1500 && u <= 1600)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "iptide<>r");
				if (u > 1600 && u <= 1700)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "riptide<>");
				if (u > 1700 && u <= 1800)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), ">riptide<");
				// if (u > 1600 && u <= 1700)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "riptide<>");
				// if (u > 1700 && u <= 1800)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "rip");
				// if (u > 1800 && u <= 1900)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ri");
				// if (u > 1900 && u <= 2000)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "r");
				// if (u > 2000 && u <= 2100)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "");
				u += watermarkScrollSpeed;
				// if (u > 2100) u = 0;
				if (u > 1800) u = 0;
			}

			if (Settings::Esp::esp_Cheatbuild)
				g_pRender->Text(15, 45, false, true, Color::White(), "latest build: %s : %s", __DATE__, __TIME__);

			if (Settings::Misc::misc_RainbowMenu)
			{
				g_pGui->MenuColor();
			}

			{
				if (g_pEsp)
					g_pEsp->OnRender();

				if (g_pMisc)
				{
					g_pMisc->OnRender();
					g_pMisc->OnRenderSpectatorList();
				}
			}

			std::time_t result = std::time(nullptr);

			if (Settings::Esp::esp_Time)
				g_pRender->Text(15, 30, false, true, Color::White(), std::asctime(std::localtime(&result)));

			g_pRender->EndRender();
		}
	}

	void OnLostDevice()
	{
		if (g_pRender)
			g_pRender->OnLostDevice();

		if (g_pGui)
			ImGui_ImplDX9_InvalidateDeviceObjects();
	}

	void OnResetDevice()
	{
		if (g_pRender)
			g_pRender->OnResetDevice();

		if (g_pGui)
			ImGui_ImplDX9_CreateDeviceObjects();
	}

	void OnCreateMove(CUserCmd* pCmd)
	{
		if (g_pPlayers && Interfaces::Engine()->IsInGame())
		{
			g_pPlayers->Update();

			if (g_pEsp)
				g_pEsp->OnCreateMove(pCmd);

			if (IsLocalAlive())
			{
				if (!bIsGuiVisible)
				{
					int iWeaponSettingsSelectID = GetWeaponSettingsSelectID();

					if (iWeaponSettingsSelectID >= 0)
						iWeaponID = iWeaponSettingsSelectID;
				}

				if (g_pAimbot)
					g_pAimbot->OnCreateMove(pCmd, g_pPlayers->GetLocal());

				if (g_pTriggerbot)
					g_pTriggerbot->OnCreateMove(pCmd, g_pPlayers->GetLocal());

				if (g_pMisc)
					g_pMisc->OnCreateMove(pCmd);

				backtracking->legitBackTrack(pCmd);

			}
		}
	}

	void OnFireEventClientSideThink(IGameEvent* pEvent)
	{
		if (!strcmp(pEvent->GetName(), "player_connect_full") ||
			!strcmp(pEvent->GetName(), "round_start") ||
			!strcmp(pEvent->GetName(), "cs_game_disconnected"))
		{
			if (g_pPlayers)
				g_pPlayers->Clear();

			if (g_pEsp)
				g_pEsp->OnReset();
		}


		if (Interfaces::Engine()->IsConnected())
		{
			hitmarker::singleton()->initialize();

			if (g_pEsp)
				g_pEsp->OnEvents(pEvent);

			if (g_pSkin)
				g_pSkin->OnEvents(pEvent);
		}
	}

	void OnFrameStageNotify(ClientFrameStage_t Stage)
	{
		if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
		{

			ConVar* sv_cheats = Interfaces::GetConVar()->FindVar("sv_cheats");
			SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
			sv_cheats_spoofed->SetInt(1);
			

			if (g_pMisc)
				g_pMisc->FrameStageNotify(Stage);

			Skin_OnFrameStageNotify(Stage);
			Gloves_OnFrameStageNotify(Stage);
		}
	}

	void OnDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state,
		const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
	{
		if (Interfaces::Engine()->IsInGame() && ctx && pCustomBoneToWorld)
		{
			if (g_pEsp)
				g_pEsp->OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

			if (g_pMisc)
				g_pMisc->OnDrawModelExecute();
		}
	}

	void OnPlaySound(const Vector* pOrigin, const char* pszSoundName)
	{
		if (!pszSoundName || !Interfaces::Engine()->IsInGame())
			return;

		if (!strstr(pszSoundName, "bulletLtoR") &&
			!strstr(pszSoundName, "rics/ric") &&
			!strstr(pszSoundName, "impact_bullet"))
		{
			if (g_pEsp && IsLocalAlive() && Settings::Esp::esp_Sound && pOrigin)
			{
				if (!GetVisibleOrigin(*pOrigin))
					g_pEsp->SoundEsp.AddSound(*pOrigin);
			}
		}
	}

	void OnPlaySound(const char* pszSoundName)
	{
		if (g_pMisc)
			g_pMisc->OnPlaySound(pszSoundName);
	}

	void OnOverrideView(CViewSetup* pSetup)
	{
		if (g_pMisc)
			g_pMisc->OnOverrideView(pSetup);
	}

	void OnGetViewModelFOV(float& fov)
	{
		if (g_pMisc)
			g_pMisc->OnGetViewModelFOV(fov);
	}

	BOOL DirectoryExists(LPCTSTR szPath)
	{
		DWORD dwAttrib = GetFileAttributes(szPath);

		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
			(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}


	void ImDrawRectRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow)
	{
		ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

		Color colColor(0, 0, 0, 255);

		flRainbow += flSpeed;
		if (flRainbow > 1.f) flRainbow = 0.f;//1 0 

		for (int i = 0; i < width; i = i + 1)
		{
			float hue = (1.f / (float)width) * i;
			hue -= flRainbow;
			if (hue < 0.f) hue += 1.f;

			Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
			windowDrawList->AddRectFilled(ImVec2(x + i, y), ImVec2(width, height), colRainbow.GetU32());
		}
	}

	void OnRenderGUI()
	{





		ImGui::SetNextWindowSize(ImVec2(860, 570)); // format = width height
		g_pGui->NameFont();
		if (ImGui::Begin("riptide", &bIsGuiVisible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
			g_pRender->DrawFillBox(0, 0, iScreenWidth, iScreenHeight, Color(0, 0, 0, 170));
		{





			static float flRainbow;
			// float flSpeed = 0.001f;
			static float flSpeed = 0.003;
			int curWidth = 3;
			ImVec2 curPos = ImGui::GetCursorPos();
			ImVec2 curWindowPos = ImGui::GetWindowPos();
			curPos.x += curWindowPos.x;
			curPos.y += curWindowPos.y;
			int size = 2;
			int y;
			Interfaces::Engine()->GetScreenSize(y, size);
			ImDrawRectRainbow(curPos.x - 10, curPos.y - 1, ImGui::GetWindowSize().x + size, curPos.y + -4, flSpeed, flRainbow);








			ImGui::BeginGroup();

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType > 1)
				Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType = 1;

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit > 1)
				Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit = 1;

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot > 5)
				Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot = 5;

			enum DWRITE_READING_DIRECTION {
				DWRITE_READING_DIRECTION_LEFT_TO_RIGHT,
				DWRITE_READING_DIRECTION_RIGHT_TO_LEFT
			};

			g_pGui->bluefont();
			ImGui::TextColored(ImVec4{ 0.0f, 0.5f, 0.0f, 1.0f }, "FPS:%03d", get_fps());
			ImGui::Separator();
			g_pGui->IconFont();
			const char* tabNames[] = {
				"A" , "I" ,"B" , "G" , "C" };

			static int tabOrder[] = { 0 , 1 , 2 , 3 , 4 };
			static int tabSelected = 4;
			const bool tabChanged = ImGui::TabLabels(tabNames,
				sizeof(tabNames) / sizeof(tabNames[0]),
				tabSelected, tabOrder);

			ImGui::Columns();





			float SpaceLineTitleOne = 120.f;
			float SpaceLineTitleTwo = 230.f;
			float SpaceLineTitleThr = 460.f;
			float SpaceLineTitleFour = 460.f;


			float SpaceLineBoxOne = 135.f;
			float SpaceLineBoxTwo = 275.f;
			float SpaceLineBoxThr = 410.f;
			float SpaceLineBoxFour = 475.f;


			float SpaceLineOne = 120.f;
			float SpaceLineTwo = 240.f;
			float SpaceLineThr = 360.f;
			float SpaceLineFour = 440.f;

			ImGui::EndGroup();
			ImGui::SameLine();




			if (tabSelected == 0) // Aimbot
			{
				g_pGui->bluefont();

				static int otherpages = 0;

				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 530), true);
				{

					if (ImGui::Button("aimbot", ImVec2(180.0f, 30.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine(SpaceLineTitleTwo);

					if (ImGui::Button("triggerbot", ImVec2(180.0f, 30.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}

					if (otherpages == 0)
					{
						ImGui::BeginGroup();

						ImGui::PushItemWidth(500.f);

						ImGui::Combo("weapon", &iWeaponID, pWeaponData, IM_ARRAYSIZE(pWeaponData));
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Columns();
						
					
						ImGui::Checkbox("attack team", &Settings::Aimbot::aim_Deathmatch);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("useful in free for all community servers");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("auto wall", &Settings::Aimbot::aim_WallAttack);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("activates aimbot if player takes damage through penetrable walls");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("check smoke", &Settings::Aimbot::aim_CheckSmoke);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("does not activate aimbot if smoke is between you and the enemy");

						ImGui::Checkbox("anti jump", &Settings::Aimbot::aim_AntiJump);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("disables aimbot if enemy and/or you are jumping");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("draw fov", &Settings::Aimbot::aim_DrawFov);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("renders radius of influence of aimbot");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("draw spot", &Settings::Aimbot::aim_DrawSpot);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("renders point of aimbot attack");

						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Spacing();

						ImGui::Checkbox("backtrack", &Settings::Aimbot::aim_Backtrack);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("you can teleport enemies to an older position and kill them");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("visualise ticks", &Settings::Aimbot::aim_DrawBacktrack);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("renders ticks with potential to be backtracked");
						ImGui::SliderInt("tickrate", &Settings::Aimbot::aim_Backtracktickrate, 1, 12);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("set backtrack tick rate (higher number longer backtrack)");

						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Checkbox("aimbot active", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Active);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("master switch");
						if (iWeaponID <= 9)
						{
							ImGui::SameLine();
							ImGui::Checkbox("autopistol", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("ability to use pistols like an automatic gun, hold down left mouse button");
						}
						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("smoothing", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth, 1, 300);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("lower fov = snapping higher fov = looks real");
						ImGui::SliderInt("fov", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov, 1, 300);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("area that aimbot effects");
						ImGui::PopItemWidth();

						const char* AimFovType[] = { "dynamic" , "static" };
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("fov type", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType, AimFovType, IM_ARRAYSIZE(AimFovType));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("dynamic changes size of FOV depending on distance between you and enemy");
						ImGui::PopItemWidth();

						const char* BestHit[] = { "disable" , "enable" };
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("best hit", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit, BestHit, IM_ARRAYSIZE(BestHit));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("looks more legit, rather than forcing hitting aimspot every time");

						ImGui::PopItemWidth();

						const char* Aimspot[] = { "Head" , "Neck" ,  "Body" , "Thorax" , "Chest" , "Right Thigh" , "Left Thigh" , "Right Hand" , "Left Hand" , "Right Upperarm" , "Right Forearm" , "Left Upperarm" , "Left Forearm" };
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("aimspot", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot, Aimspot, IM_ARRAYSIZE(Aimspot));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("if besthit is disabled, this forces one location for the aimbot to travel to");
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("recoil control system");
						ImGui::Spacing();

						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("shot delay", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Delay, 0, 200);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("amount of time before automated rcs kicks in");
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Spacing();


						if (iWeaponID >= 10 && iWeaponID <= 30)
						{
							ImGui::PushItemWidth(362.f);
							ImGui::SliderInt("rcs", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcs, 0, 100);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("amount of rcs");
							ImGui::SliderInt("rcs fov", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov, 1, 300);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("area of influence of automated recoil control");
							ImGui::SliderInt("rcs smooth", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth, 1, 300);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("humanization of automated recoil");
							ImGui::PopItemWidth();

							const char* ClampType[] = { "all targets" , "shot" , "shot + target" };
							ImGui::PushItemWidth(362.f);
							ImGui::Combo("rcs clamp", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType, ClampType, IM_ARRAYSIZE(ClampType));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("methods of target selection for rcs");
							ImGui::PopItemWidth();
						}


						ImGui::EndGroup();
					}
					if (otherpages == 1)
					{
						ImGui::BeginGroup();


						const char* TriggerEnable[] = { "disable" , "fov" };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("enable", &Settings::Triggerbot::trigger_Enable, TriggerEnable, IM_ARRAYSIZE(TriggerEnable));
						ImGui::PopItemWidth();
						ImGui::SameLine();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("deathmatch", &Settings::Triggerbot::trigger_Deathmatch);
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("wall-attack", &Settings::Triggerbot::trigger_WallAttack);
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("fast-zoom", &Settings::Triggerbot::trigger_FastZoom);

						ImGui::Checkbox("smoke check", &Settings::Triggerbot::trigger_SmokCheck);
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("draw fov", &Settings::Triggerbot::trigger_DrawFov);
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("draw spot", &Settings::Triggerbot::trigger_DrawSpot);
						ImGui::SameLine(SpaceLineThr);
						ImGui::Checkbox("draw fov assist", &Settings::Triggerbot::trigger_DrawFovAssist);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						const char* items1[] = { CVAR_KEY_MOUSE3 , CVAR_KEY_MOUSE4 , CVAR_KEY_MOUSE5 };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("key", &Settings::Triggerbot::trigger_Key, items1, IM_ARRAYSIZE(items1));
						ImGui::PopItemWidth();
						ImGui::SameLine();

						const char* items2[] = { "hold" , "press" };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("key mode", &Settings::Triggerbot::trigger_KeyMode, items2, IM_ARRAYSIZE(items2));
						ImGui::PopItemWidth();
						ImGui::SameLine();

						ImGui::PushItemWidth(110.f);
						ImGui::Combo("weapon", &iWeaponID, pWeaponData, IM_ARRAYSIZE(pWeaponData));
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("minimum distance", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DistanceMin, 0, 5000);
						ImGui::SliderInt("maximum distance", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DistanceMax, 0, 5000);
						ImGui::SliderInt("fov", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Fov, 1, 100);
						ImGui::SliderInt("delay before ", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DelayBefore, 0, 200);
						ImGui::SliderInt("delay after", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DelayAfter, 0, 1000);
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("head only", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly);
						ImGui::SameLine();

						const char* AssistMode[] = { "disable" , "one-shot" , "auto" };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("assist", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist, AssistMode, IM_ARRAYSIZE(AssistMode));
						ImGui::PopItemWidth();
						ImGui::SameLine();


						const char* AssistFovType[] = { "dynamic" , "static" };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("assist fov type", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType, AssistFovType, IM_ARRAYSIZE(AssistFovType));
						ImGui::PopItemWidth();

						const char* HitGroup[] = { "all" , "head + body" , "head" };
						ImGui::Combo("hit group", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HitGroup, HitGroup, IM_ARRAYSIZE(HitGroup));
						//ImGui::PopItemWidth();

						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("assist rcs", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistRcs, 0, 100);
						ImGui::SliderInt("assist fov", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov, 1, 300);
						ImGui::SliderInt("assist smooth", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistSmooth, 1, 300);
						ImGui::PopItemWidth();




						ImGui::EndGroup();
					}
					ImGui::EndChild();
					ImGui::EndGroup();







				}
			}
			else if (tabSelected == 1) // Visuals
			{

				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 530), true);
				{
					const char* iHitSound[] =
					{
						"off",
						"default",
						"metallic",
						"roblox",
						"windows xp",
					};

					const char* material_items[] =
					{
						"glass",
						"crystal",
						"dark gold",
						"dark chrome",
						"plastic glass",
						"velvet",
						"crystal blue",
						"bright gold"
					};

					const char* armtype_items[] =
					{
						"arms only",
						"arms and weapon"
					};

					const char* skybox_items[] =
					{
						"cs_baggage_skybox_",
						"cs_tibet",
						"embassy",
						"italy",
						"jungle",
						"nukeblank",
						"office",
						"sky_cs15_daylight01_hdr",
						"sky_cs15_daylight02_hdr",
						"sky_cs15_daylight03_hdr",
						"sky_cs15_daylight04_hdr",
						"sky_csgo_cloudy01",
						"sky_csgo_night02",
						"sky_csgo_night02b",
						"sky_csgo_night_flat",
						"sky_day02_05_hdr",
						"sky_day02_05",
						"sky_dust",
						"sky_l4d_rural02_ldr",
						"sky_venice",
						"vertigo_hdr",
						"vertigoblue_hdr",
						"vertigo",
						"vietnam",
						"amethyst",
						"bartuc_canyon",
						"bartuc_grey_sky",
						"blue1",
						"blue2",
						"blue3",
						"blue5",
						"blue6",
						"cssdefault",
						"dark1",
						"dark2",
						"dark3",
						"dark4",
						"dark5",
						"extreme_glaciation",
						"green1",
						"green2",
						"green3",
						"green4",
						"green5",
						"greenscreen",
						"greysky",
						"night1",
						"night2",
						"night3",
						"night4",
						"night5",
						"orange1",
						"orange2",
						"orange3",
						"orange4",
						"orange5",
						"orange6",
						"persistent_fog",
						"pink1",
						"pink2",
						"pink3",
						"pink4",
						"pink5",
						"polluted_atm",
						"toxic_atm",
						"water_sunset﻿"
					};

					string style_1 = "box";
					string style_2 = "corners only";

					const char* items1[] = { style_1.c_str() , style_2.c_str() };

					static int otherpages = 0;



					if (ImGui::Button("esp", ImVec2(180.0f, 30.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine(SpaceLineTitleTwo);

					if (ImGui::Button("misc. visuals", ImVec2(180.0f, 30.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}
					ImGui::SameLine(SpaceLineTitleThr);
					



					if (otherpages == 0)
					{
						static int otherpages = 0;



						if (ImGui::Button("visuals", ImVec2(87.0f, 25.0f))) // <---- customize these to your liking.
						{
							otherpages = 0;
						}
						ImGui::SameLine();
						if (ImGui::Button("options", ImVec2(87.0f, 25.0f))) // <---- again, customize to your liking.
						{
							otherpages = 1;
						}

						ImGui::Separator();

						if (otherpages == 0)
						{



							ImGui::PushItemWidth(339.f);
							ImGui::Combo("box type", &Settings::Esp::esp_Style, items1, IM_ARRAYSIZE(items1));
							ImGui::PopItemWidth();


							ImGui::Spacing();

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(150.f); //item width
							ImGui::BeginChild("first child", ImVec2(135, 111), true); //begins the child and the size of the child.
							{
								ImGui::Checkbox("team esp", &Settings::Esp::esp_Team);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("render teammates");
								ImGui::Checkbox("enemy esp", &Settings::Esp::esp_Enemy);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("render enemies");
								ImGui::Checkbox("skeleton", &Settings::Esp::esp_Skeleton);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("innacurate and buggy rendering of bones of enemies");
								ImGui::Checkbox("outline", &Settings::Esp::esp_Outline);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("draws black outline over box");

							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group

							ImGui::SameLine(SpaceLineBoxOne);

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(300.f); //item width
							ImGui::BeginChild("second child", ImVec2(200, 111), true); //begins the child and the size of the child.
							{
								ImGui::Checkbox("name esp", &Settings::Esp::esp_Name);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders name of players");
								ImGui::Checkbox("bomb esp", &Settings::Esp::esp_Bomb);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders position of bomb on players and when planted");
								ImGui::Checkbox("weapon esp", &Settings::Esp::esp_Weapon);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders text of current weapon held by enemies");
								ImGui::Checkbox("PLayer Status", &Settings::Esp::esp_Statusx);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders text of current status for enemies for example (is defusing)");

							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group


							ImGui::SameLine(SpaceLineBoxTwo);

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(300.f); //item width
							ImGui::BeginChild("third child", ImVec2(145, 111), true); //begins the child and the size of the child.
							{
								ImGui::Checkbox("reveal ranks", &Settings::Esp::esp_Rank);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("in scoreboard");
								ImGui::Checkbox("sound esp", &Settings::Esp::esp_Sound);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("draws each hearable footstep");
								ImGui::Checkbox("line esp", &Settings::Esp::esp_Line);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("draws line to enemy");
								ImGui::Checkbox("distance esp", &Settings::Esp::esp_Distance);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders text for distance between you and enemy");
							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group

							ImGui::SameLine(SpaceLineBoxThr);

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(300.f); //item width
							ImGui::BeginChild("fourth child", ImVec2(1200, 111), true); //begins the child and the size of the child.
							{
								ImGui::Checkbox("ammo esp", &Settings::Esp::esp_Ammo);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders text of amount of ammunition enemy has");
								ImGui::Checkbox("last build", &Settings::Esp::esp_Cheatbuild);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders time of last compilation in top left of screen");
								ImGui::Checkbox("watermark", &Settings::Esp::esp_Watermark);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders animated riptide rainbow text in top left of screen");
								ImGui::Checkbox("time", &Settings::Esp::esp_Time);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders current time in top left of screen");
								
							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group

							ImGui::Spacing();

							ImGui::Checkbox("capslock boxtoggle", &Settings::Esp::esp_CapitalToggle);
							ImGui::SameLine(SpaceLineTwo);
							ImGui::Checkbox("fish esp", &Settings::Esp::esp_Fish);
							ImGui::SameLine(SpaceLineFour);
							ImGui::Checkbox("chicken esp", &Settings::Esp::esp_Chicken);

							

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							static bool sh_save_cfg = false;

							if (ImGui::Checkbox("grenade helper", &Settings::Esp::helper))
								sh_save_cfg = true;
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("buy a smoke, hold it in your hand, walk on a red circle, bottom left screen is info, throw as instructed at the green point.");

							ImGui::SameLine();
							if (ImGui::Button("update map"))
								cGrenade.bUpdateGrenadeInfo(Interfaces::Engine()->GetLevelNameShort());
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("does not work on all maps");

							ImGui::Checkbox("grenade trajectory", &Settings::Misc::misc_GrenadeTrajectory);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN, buggy");

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							ImGui::Checkbox("dropped weapon esp", &Settings::Esp::esp_WorldWeapons);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders text of dropped weapons on them");
							ImGui::Checkbox("thrown grenades esp", &Settings::Esp::esp_WorldGrenade);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders text of type of grenade being thrown by enemies and teammates");
							ImGui::Checkbox("grenade boxes", &Settings::Esp::esp_BoxNade);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders 3D box around grenades regardless of type");

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();


							ImGui::Checkbox("asus walls", &Settings::Esp::esp_AsusWalls);
							ImGui::SliderInt("walls opacity	", &Settings::Esp::esp_WallsOpacity, 0, 100);

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							ImGui::ColorEdit3("ambient light", Settings::Esp::esp_Ambient);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::Checkbox("night mode", &Settings::Esp::esp_NightMode);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::SameLine(SpaceLineOne);
							ImGui::Checkbox("chrome", &Settings::Esp::esp_ChromeWorld);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::SameLine(SpaceLineTwo);
							ImGui::Checkbox("minecraft", &Settings::Esp::esp_MinecraftMode);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::SameLine(SpaceLineThr);
							ImGui::Checkbox("lsd", &Settings::Esp::esp_LSDMode);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::Checkbox("fullbright", &Settings::Misc::misc_FullBright);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN, looks best on mirage");
							ImGui::Spacing();




						}

						if (otherpages == 1)
						{

							string visible_1 = "enemy";
							string visible_2 = "team";
							string visible_3 = "all";
							string visible_4 = "only visible";

							string hpbar_1 = "none";
							string hpbar_2 = "number";
							string hpbar_3 = "bottom";
							string hpbar_4 = "left";
							string hpbar_5 = "partition";

							string arbar_1 = "none";
							string arbar_2 = "number";
							string arbar_3 = "bottom";
							string arbar_4 = "right";

							string chams_1 = "None";
							string chams_2 = "flat";
							string chams_3 = "texture";


							const char* items2[] = { visible_1.c_str() , visible_2.c_str() , visible_3.c_str() , visible_4.c_str() };

							ImGui::PushItemWidth(339.f);
							ImGui::Combo("esp visible", &Settings::Esp::esp_Visible, items2, IM_ARRAYSIZE(items2));

							ImGui::Separator();
							ImGui::Spacing();


							ImGui::Text("rendering");
							ImGui::Spacing();
							const char* items3[] = { hpbar_1.c_str() , hpbar_2.c_str() , hpbar_3.c_str() , hpbar_4.c_str() , hpbar_5.c_str() };
							ImGui::Combo("esp health", &Settings::Esp::esp_Health, items3, IM_ARRAYSIZE(items3));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders health of players");

							const char* items4[] = { arbar_1.c_str() , arbar_2.c_str() , arbar_3.c_str() , arbar_4.c_str() };
							ImGui::Combo("esp armor", &Settings::Esp::esp_Armor, items4, IM_ARRAYSIZE(items4));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders armor of players");

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							ImGui::Text("chams options");
							ImGui::Spacing();
							const char* items5[] = { chams_1.c_str() , chams_2.c_str() , chams_3.c_str() };
							ImGui::Combo("chams", &Settings::Esp::esp_Chams, items5, IM_ARRAYSIZE(items5));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("fills player models with colour");
							ImGui::Combo("chams visible", &Settings::Esp::esp_ChamsVisible, items2, IM_ARRAYSIZE(items2));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("selection of when to render coloured playermodels");

							ImGui::Spacing();
							ImGui::Spacing();

							ImGui::Checkbox("chams materials", &Settings::Misc::misc_ChamsMaterials);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("choose prebuilt material types");
							ImGui::PushItemWidth(362.f);
							ImGui::Combo("##CHAMSMATERIALS", &Settings::Misc::misc_ChamsMaterialsList, material_items, ARRAYSIZE(material_items));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("choose prebuilt material types");
							ImGui::Checkbox("health chams", &Settings::Esp::esp_HealthChams);
							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();


							ImGui::Text("esp settings");
							ImGui::Spacing();
							ImGui::SliderInt("esp size", &Settings::Esp::esp_Size, 0, 10);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("size of each box");
							ImGui::SliderInt("bomb timer", &Settings::Esp::esp_BombTimer, 0, 65);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("useful for community servers(?) where bomb timer is different");
							ImGui::SliderInt("bullet tracers", &Settings::Esp::esp_BulletTrace, 0, 3000);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders direction of player viewangle with a line of a certain length");






						}
					}
					if (otherpages == 1)
					{






						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Text("skybox changer");
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("spoofs skybox to other map");
						ImGui::Spacing();
						if (ImGui::Combo("", &Settings::Misc::misc_CurrentSky, skybox_items, IM_ARRAYSIZE(skybox_items)))
						{
							Settings::Misc::misc_SkyName = skybox_items[Settings::Misc::misc_CurrentSky];
						}

						ImGui::Checkbox("snow world", &Settings::Misc::misc_Snow);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("no sky", &Settings::Misc::misc_NoSky);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("disable postprocessing", &Settings::Misc::misc_EPostprocess);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("wire smoke", &Settings::Misc::misc_wireframesmoke);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN, buggy while walking through smoke");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("no smoke", &Settings::Misc::misc_NoSmoke);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN, buggy while walking through smoke");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("no flash", &Settings::Misc::misc_NoFlash);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("disables rendering of flash blinding");

						ImGui::Checkbox("esp warnings", &Settings::Esp::bEspWarnings);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("displays a warning if someone is aiming at you");
				
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("hitmarker", &Settings::Esp::esp_HitMarker);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("visual representation of landing a hit");
						ImGui::Combo("hitmarker sound", &Settings::Esp::esp_HitMarkerSound, iHitSound, ARRAYSIZE(iHitSound));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("audial representation of landing a hit");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Text("arm materials");
						ImGui::Spacing();
						ImGui::Checkbox("arm materials", &Settings::Misc::misc_ArmMaterials);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("spoofs arm/weapon materials to something else");
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("type", &Settings::Misc::misc_ArmMaterialsType, armtype_items, ARRAYSIZE(armtype_items));
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("material", &Settings::Misc::misc_ArmMaterialsList, material_items, ARRAYSIZE(material_items));


					}

					ImGui::EndChild();
					ImGui::EndGroup();
				}
			}
			else if (tabSelected == 2) // Skins
			{
				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 530), true);
				{

					ImGui::Text("clientsided changers");
					ImGui::Spacing();

					ImGui::Checkbox("skin changer", &Settings::Misc::misc_SkinChanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("clientsided - you're the only one who can see it");


					ImGui::Checkbox("knife changer", &Settings::Misc::misc_KnifeChanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("clientsided - you're the only one who can see it");


					ImGui::Checkbox("sticker changer", &Settings::Misc::misc_StickerChanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("clientsided - you're the only one who can see it");

					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Text("filters");
					ImGui::Checkbox("skin ids", &Settings::Misc::skinids);
					ImGui::SameLine(SpaceLineOne);
					ImGui::Checkbox("weapon ids", &Settings::Misc::weaponids);
					ImGui::SameLine(SpaceLineTwo);
					ImGui::Checkbox("sticker ids", &Settings::Misc::stickerids);
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::EndChild();
					ImGui::EndGroup();
				}
			}
			else if (tabSelected == 3) // Misc
			{
				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 530), true);
				{

					ImGui::BeginGroup();


					static int otherpages = 0;



					if (ImGui::Button("part 1", ImVec2(87.0f, 25.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine();
					if (ImGui::Button("part 2", ImVec2(87.0f, 25.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}
					ImGui::SameLine();

					ImGui::Separator();

					if (otherpages == 0)
					{
						ImGui::BeginGroup();

						ImGui::Spacing();

						ImGui::Checkbox("rainbow menu", &Settings::Misc::misc_RainbowMenu);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("does not work anymore on main window");
						ImGui::PushItemWidth(362.f);
						if (ImGui::InputFloat("fade speed", &Settings::Misc::misc_RainbowSpeed, 0.001f, 0.01f))
						{
							if (Settings::Misc::misc_RainbowSpeed < 0.001f)
								Settings::Misc::misc_RainbowSpeed = 0.001f;
							if (Settings::Misc::misc_RainbowSpeed > 0.01f)
								Settings::Misc::misc_RainbowSpeed = 0.01f;
						};

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						


						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("bhop", &Settings::Misc::misc_Bhop);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("perfect bunny hop, lands 100% of the time");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("inventory always on", &Settings::Misc::invalwayson);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("allows you to access inventory in competitive match post-warmup");

						ImGui::Spacing();

						ImGui::Checkbox("punch", &Settings::Misc::misc_Punch);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("shows white crosshair to show where recoil is");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("sniper crosshair", &Settings::Misc::misc_AwpAim);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("shows your crosshair while holding a sniper");

						ImGui::Spacing();

						ImGui::Checkbox("chat spam", &Settings::Misc::misc_spamregular);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("trashtalks chat");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("random chat spam", &Settings::Misc::misc_spamrandom);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("trashtalks chat creatively");

						ImGui::Spacing();

						ImGui::Checkbox("nohands", &Settings::Misc::misc_NoHands);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("stops rendering arms but still renders weapons");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("wirehands", &Settings::Misc::misc_WireHands);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("renders hands with a wireframe");
						ImGui::Spacing();

						ImGui::Checkbox("spectators", &Settings::Misc::misc_Spectators);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("buggy, external window");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("autoaccept", &Settings::Misc::misc_AutoAccept);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("buggy");
						ImGui::Spacing();

						ImGui::Separator();
						ImGui::Checkbox("legit aa", &Settings::Misc::misc_LegitAA);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("WARNING: CHANGES AIMBOT TO SILENT AIM");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("silent aim fix", &Settings::Misc::misc_LegitAAToggle);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("fixes changing aimbot to silent aim when legit aa is enabled");
						ImGui::SameLine(SpaceLineThr);
						ImGui::Checkbox("legit aa indicators", &Settings::Esp::esp_legitAAWarnings);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("text - current side of your real angle");

						ImGui::Separator();
						ImGui::Spacing();

						string clan_1 = "none";
						string clan_2 = "clear";
						string clan_3 = "no-name";
						string clan_4 = "riptide";
						string clan_5 = "riptide no name";
						string clan_6 = "valve";
						string clan_7 = "valve no-name";
						string clan_8 = "karmafreediet";
						string clan_9 = "riptide animated";
						const char* items5[] = { clan_1.c_str() , clan_2.c_str() , clan_3.c_str() , clan_4.c_str() , clan_5.c_str() , clan_6.c_str() , clan_7.c_str(), clan_8.c_str(), clan_9.c_str() };
						ImGui::Combo("clantag changer", &Settings::Misc::misc_Clan, items5, IM_ARRAYSIZE(items5));

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();


						ImGui::Checkbox("field of view changer", &Settings::Misc::misc_FovChanger);
						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("viewposition", &Settings::Misc::misc_FovView, 1, 190);
						ImGui::SliderInt("viewmodel", &Settings::Misc::misc_FovModelView, 1, 190);

						ImGui::EndGroup();
					}
					if (otherpages == 1)
					{

						ImGui::BeginGroup();

						ImGui::Spacing();


						static char buf2[128] = { 0 };
						ImGui::Text("custom name");
						ImGui::InputText("##CustomName", buf2, 16, Settings::Misc::misc_NameChange);
						if (ImGui::Button("apply custom name")) {
							ConVar* Name = Interfaces::GetConVar()->FindVar("name");
							*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = 0;
							Name->SetValue(buf2);
						}

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();



						static char misc_CustomClanTag[128] = { 0 };
						ImGui::Text("custom clantag");
						ImGui::InputText("##CustomClanTag", misc_CustomClanTag, 128);

						if (ImGui::Button("apply custom clantag"))
						{
							Engine::ClanTagApply(misc_CustomClanTag);
						}

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("gravity", &Settings::Misc::misc_ragdoll_gravity);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("changes gravity for corpse, buggy, SMAC BAN");
						ImGui::SliderInt("gravity amount", &Settings::Misc::misc_ragdoll_gravity_amount, -1000, 1000);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("0 = no gravity / 1000 = high gravity / -1000 = negative gravity");

						ImGui::Checkbox("pushscale", &Settings::Misc::misc_pushscale);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("spoofs phys_pushscale, possibly untrusted, SMAC BAN");
						ImGui::SliderInt("pushscale amount", &Settings::Misc::misc_pushscale_amount, 0, 5000);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("buggy");
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						if (ImGui::Button("ayyware crasher"))    //Crashes the Ayyware ESP. Most of ayyware user already fixed it.
						{

							ConVar* Name = Interfaces::GetConVar()->FindVar("name");
							*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = 0;

							Name->SetValue("GETCRASHEDAYY?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????");
						}
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("changes your name to crash ayyware name esp/spectators list");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("fake ping", &Settings::Misc::misc_fakeping);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("extends backtrack");
						ImGui::Spacing();

						ImGui::Text("custom models");

						
						ImGui::Checkbox("enable custom models", &Settings::Misc::custommodelson);
						if (ImGui::IsItemHovered())
						ImGui::SetTooltip("CAUSES CRASH");
						const char* customModelsct[] =
						{
						"off",
						"trump",
						"noire",
						"anime",
						"joe"

						};

						const char* customModelst[] =
						{
						"off",
						"trump",
						"noire",
						"anime",
						"joe"

						};

						if (Settings::Misc::custommodelson) {
						ImGui::Combo(("ct model"), &Settings::Misc::customodelsct, customModelsct, ARRAYSIZE(customModelsct));
						ImGui::Combo(("t model"), &Settings::Misc::customodelst, customModelst, ARRAYSIZE(customModelst));
						}

						if (ImGui::Button("update"))
						{
						ForceFullUpdate();
						}
						
					}

					ImGui::EndChild();
					ImGui::EndGroup();


				}

			}
			else if (tabSelected == 4)
			{
				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 530), true);
				{

					static int otherpages = 0;



					if (ImGui::Button("settings", ImVec2(87.0f, 25.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine();
					if (ImGui::Button("colours", ImVec2(87.0f, 25.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}

					ImGui::Separator();


					if (otherpages == 0)
					{
						g_pGui->bluefont();

						ImGui::BeginGroup();
						static int iConfigSelect = 0;
						static int iMenuSheme = 1;
						static char ConfigName[64] = { 0 };
						static bool sh_save_cfg = false;
						static bool sh_load_cfg = false;

						ImGui::ComboBoxArray("select config", &iConfigSelect, ConfigList);


						CHAR my_documents[MAX_PATH];
						if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents)))
						{

							if (ImGui::Button("load config"))
							{
								sh_load_cfg = true;
								Settings::LoadSettings(string(my_documents) + "\\riptide\\" + ConfigList[iConfigSelect]);
							}
							ImGui::SameLine();
							if (ImGui::Button("save config"))
							{
								Settings::SaveSettings(string(my_documents) + "\\riptide\\" + ConfigList[iConfigSelect]);
								sh_save_cfg = true;
							}
							ImGui::SameLine();
							if (ImGui::Button("refresh config list"))
							{
								RefreshConfigs();
							}
						}
						if (sh_save_cfg)
						{
							//save ur cfg
							bool done = false;
							Anime::Popup("config saved", 2000, &done);
							if (done)
								sh_save_cfg = false;
						}

						if (sh_load_cfg)
						{
							//load ur cfg
							bool done = false;
							Anime::Popup("loaded config", 2000, &done);
							if (done)
								sh_load_cfg = false;
						}





						ImGui::InputText("config name", ConfigName, 64);
						ImGui::Text("if you are making a new config, click 'create & save new config'.");
						ImGui::Text("configs save in documents, riptide");
						if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents)))
						{
							if (ImGui::Button("create & save new config"))
							{
								string ConfigFileName = ConfigName;

								if (ConfigFileName.size() < 1)
								{
									ConfigFileName = "settings";
								}
								string riptide = "\\riptide\\";
								string both = my_documents + riptide;

								if (!DirectoryExists(both.c_str())) // only create dir if doesnt already exist
									CreateDirectoryA(both.c_str(), NULL); //create riptdie dir



								Settings::SaveSettings(string(my_documents) + "\\riptide\\" + ConfigFileName + ".ini");
								RefreshConfigs();
							}
						}


						ImGui::Text(" ");


						const char* ThemesList[] = { "purple" , "white" , "light pink" , "narcisisti.cc" , "midnight" , "night" , "black/red" , "blue"  , "black" , "green" , "yellow" , "light blue" , "light grey" , "phook" };

						ImGui::Combo("menu theme", &iMenuSheme, ThemesList, IM_ARRAYSIZE(ThemesList));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("currently out of operation");


						if (ImGui::Button("apply color"))
						{
							if (iMenuSheme == 0)
							{
								g_pGui->purple();
							}
							else if (iMenuSheme == 1)
							{
								g_pGui->DefaultSheme1();
							}
							else if (iMenuSheme == 2)
							{
								g_pGui->RedSheme();
							}
							else if (iMenuSheme == 3)
							{
								g_pGui->darkblue();
							}
							else if (iMenuSheme == 4)
							{
								g_pGui->MidNightSheme();
							}
							else if (iMenuSheme == 5)
							{
								g_pGui->NightSheme();
							}
							else if (iMenuSheme == 6)
							{
								g_pGui->DunnoSheme();
							}
							else if (iMenuSheme == 7)
							{
								g_pGui->BlueSheme();
							}
							//else if (iMenuSheme == 10)
							//{
							//	g_pGui->MidNight2();
							//}
							else if (iMenuSheme == 8)
							{
								g_pGui->BlackSheme2();
							}
							else if (iMenuSheme == 9)
							{
								g_pGui->green();
							}
							else if (iMenuSheme == 10)
							{
								g_pGui->pink();
							}
							else if (iMenuSheme == 11)
							{
								g_pGui->blue();
							}
							else if (iMenuSheme == 12)
							{
								g_pGui->yellow();
							}
							else if (iMenuSheme == 13)
							{
								g_pGui->BlackSheme();
							}
						}
						ImGui::EndGroup();

					}
					if (otherpages == 1)
					{

						ImGui::BeginGroup();
						ImGui::Text("menu");
						if (ImGui::ColorEdit3("menu colour", Settings::Misc::misc_MenuColor))
							g_pGui->MenuColor();
						if (ImGui::ColorEdit3("menu text colour", Settings::Misc::misc_TextColor))
							g_pGui->MenuColor();
						ImGui::SliderFloat("rainbow bar speed", &flSpeed, 0.000f, 0.005f);
						ImGui::SliderFloat("watermark rainbow speed", &watermarkRainbowSpeed, 0.000f, 0.05f);
						ImGui::SliderFloat("watermark scroll speed", &watermarkScrollSpeed, 1.0f, 10.0f);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("esp");
						ImGui::ColorEdit3("hitmarker", Settings::Esp::esp_HitMarkerColor);
						ImGui::ColorEdit3("esp ct", Settings::Esp::esp_Color_CT);
						ImGui::ColorEdit3("esp tt", Settings::Esp::esp_Color_TT);
						ImGui::ColorEdit3("esp vis. ct", Settings::Esp::esp_Color_VCT);
						ImGui::ColorEdit3("esp vis. t", Settings::Esp::esp_Color_VTT);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("chams");
						ImGui::ColorEdit3("chams ct", Settings::Esp::chams_Color_CT);
						ImGui::ColorEdit3("chams tt", Settings::Esp::chams_Color_TT);
						ImGui::ColorEdit3("chams vis. ct", Settings::Esp::chams_Color_VCT);
						ImGui::ColorEdit3("chams vis. t", Settings::Esp::chams_Color_VTT);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

					}


					ImGui::EndChild();
					ImGui::EndGroup();

				}

			}
			ImGui::EndGroup();
			ImGui::End();
		}


	}
}







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOBNBPEWWZ
{ 
  void YHSYWlGGFd()
  { 
      bool ILflnbDzyF = false;
      bool jYspLFaIJV = false;
      bool molyHlGaPq = false;
      bool VHgPOfywFa = false;
      bool EzxYzsDoNX = false;
      bool iXrmkSZgdC = false;
      bool UbiHjcrcbf = false;
      bool GdDhRmqMzO = false;
      bool iRNrHxOsdu = false;
      bool FRSDFbQpoW = false;
      bool AZNgQEUJVy = false;
      bool bNhOSDOqzm = false;
      bool NzzgZoLzbo = false;
      bool WAWbOIEfaC = false;
      bool cEWfSriDjC = false;
      bool NZqCIAagHb = false;
      bool sUggaapFzK = false;
      bool zhPxJJbSNh = false;
      bool FHOZaxJUTN = false;
      bool hXYyIHWpEq = false;
      string NfDiupuGhp;
      string EIMsNWtPwP;
      string JrhQdPWqaj;
      string tQpKIXUczz;
      string AOzQhjrPTZ;
      string sUOujVxmEe;
      string SEeyunSBkp;
      string CQPwPurQht;
      string XHXBpZBuam;
      string ZhXTgwiAVt;
      string QpedXbFRfo;
      string cfEKHKgdHV;
      string lXaxPTruPS;
      string LquncgcscN;
      string UiOkJscNMV;
      string PEszIsOgND;
      string jJCMckkQhZ;
      string hmBtBCIonW;
      string qdisDHywei;
      string SwfZdKgBIX;
      if(NfDiupuGhp == QpedXbFRfo){ILflnbDzyF = true;}
      else if(QpedXbFRfo == NfDiupuGhp){AZNgQEUJVy = true;}
      if(EIMsNWtPwP == cfEKHKgdHV){jYspLFaIJV = true;}
      else if(cfEKHKgdHV == EIMsNWtPwP){bNhOSDOqzm = true;}
      if(JrhQdPWqaj == lXaxPTruPS){molyHlGaPq = true;}
      else if(lXaxPTruPS == JrhQdPWqaj){NzzgZoLzbo = true;}
      if(tQpKIXUczz == LquncgcscN){VHgPOfywFa = true;}
      else if(LquncgcscN == tQpKIXUczz){WAWbOIEfaC = true;}
      if(AOzQhjrPTZ == UiOkJscNMV){EzxYzsDoNX = true;}
      else if(UiOkJscNMV == AOzQhjrPTZ){cEWfSriDjC = true;}
      if(sUOujVxmEe == PEszIsOgND){iXrmkSZgdC = true;}
      else if(PEszIsOgND == sUOujVxmEe){NZqCIAagHb = true;}
      if(SEeyunSBkp == jJCMckkQhZ){UbiHjcrcbf = true;}
      else if(jJCMckkQhZ == SEeyunSBkp){sUggaapFzK = true;}
      if(CQPwPurQht == hmBtBCIonW){GdDhRmqMzO = true;}
      if(XHXBpZBuam == qdisDHywei){iRNrHxOsdu = true;}
      if(ZhXTgwiAVt == SwfZdKgBIX){FRSDFbQpoW = true;}
      while(hmBtBCIonW == CQPwPurQht){zhPxJJbSNh = true;}
      while(qdisDHywei == qdisDHywei){FHOZaxJUTN = true;}
      while(SwfZdKgBIX == SwfZdKgBIX){hXYyIHWpEq = true;}
      if(ILflnbDzyF == true){ILflnbDzyF = false;}
      if(jYspLFaIJV == true){jYspLFaIJV = false;}
      if(molyHlGaPq == true){molyHlGaPq = false;}
      if(VHgPOfywFa == true){VHgPOfywFa = false;}
      if(EzxYzsDoNX == true){EzxYzsDoNX = false;}
      if(iXrmkSZgdC == true){iXrmkSZgdC = false;}
      if(UbiHjcrcbf == true){UbiHjcrcbf = false;}
      if(GdDhRmqMzO == true){GdDhRmqMzO = false;}
      if(iRNrHxOsdu == true){iRNrHxOsdu = false;}
      if(FRSDFbQpoW == true){FRSDFbQpoW = false;}
      if(AZNgQEUJVy == true){AZNgQEUJVy = false;}
      if(bNhOSDOqzm == true){bNhOSDOqzm = false;}
      if(NzzgZoLzbo == true){NzzgZoLzbo = false;}
      if(WAWbOIEfaC == true){WAWbOIEfaC = false;}
      if(cEWfSriDjC == true){cEWfSriDjC = false;}
      if(NZqCIAagHb == true){NZqCIAagHb = false;}
      if(sUggaapFzK == true){sUggaapFzK = false;}
      if(zhPxJJbSNh == true){zhPxJJbSNh = false;}
      if(FHOZaxJUTN == true){FHOZaxJUTN = false;}
      if(hXYyIHWpEq == true){hXYyIHWpEq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBXHBKLBZL
{ 
  void pUxILfDWnG()
  { 
      bool FNigJVDsJb = false;
      bool tosYycxeUu = false;
      bool nxgCbAxVeT = false;
      bool mSrVlSGcYS = false;
      bool GZjpkYOUiT = false;
      bool XxjcNIggEI = false;
      bool XgNoobwWmf = false;
      bool WUFBoNMpRD = false;
      bool kcmLwohOHd = false;
      bool kYXPuYLuBI = false;
      bool cqgDwDrhnA = false;
      bool uqPBXttCsz = false;
      bool sgOJtxwpGP = false;
      bool BRnIZswjOs = false;
      bool xAaHhtJWrB = false;
      bool eJCBPwbXJz = false;
      bool GBbYycCHbd = false;
      bool yKmACrFHaA = false;
      bool nZyEjrPlrd = false;
      bool RXZPluYCJF = false;
      string zKSrQULhDK;
      string TJYtAwfkGw;
      string XzOGMfNscU;
      string YNzWFchbTH;
      string fewDBMGnco;
      string eGMaRzuMej;
      string HRFhkGJCnW;
      string OEQzPrCLEA;
      string YYQmpSBYFG;
      string hUwizOZNRu;
      string CEzFZaoMKY;
      string wjHeLhBRrS;
      string EkxhotHhzB;
      string SosJxUZKNP;
      string coNfJxMRXR;
      string MHVzqRGRQf;
      string SHMJGHqyhp;
      string IqEbpPWRXr;
      string gpJhnKTsRe;
      string OHshwVbEYC;
      if(zKSrQULhDK == CEzFZaoMKY){FNigJVDsJb = true;}
      else if(CEzFZaoMKY == zKSrQULhDK){cqgDwDrhnA = true;}
      if(TJYtAwfkGw == wjHeLhBRrS){tosYycxeUu = true;}
      else if(wjHeLhBRrS == TJYtAwfkGw){uqPBXttCsz = true;}
      if(XzOGMfNscU == EkxhotHhzB){nxgCbAxVeT = true;}
      else if(EkxhotHhzB == XzOGMfNscU){sgOJtxwpGP = true;}
      if(YNzWFchbTH == SosJxUZKNP){mSrVlSGcYS = true;}
      else if(SosJxUZKNP == YNzWFchbTH){BRnIZswjOs = true;}
      if(fewDBMGnco == coNfJxMRXR){GZjpkYOUiT = true;}
      else if(coNfJxMRXR == fewDBMGnco){xAaHhtJWrB = true;}
      if(eGMaRzuMej == MHVzqRGRQf){XxjcNIggEI = true;}
      else if(MHVzqRGRQf == eGMaRzuMej){eJCBPwbXJz = true;}
      if(HRFhkGJCnW == SHMJGHqyhp){XgNoobwWmf = true;}
      else if(SHMJGHqyhp == HRFhkGJCnW){GBbYycCHbd = true;}
      if(OEQzPrCLEA == IqEbpPWRXr){WUFBoNMpRD = true;}
      if(YYQmpSBYFG == gpJhnKTsRe){kcmLwohOHd = true;}
      if(hUwizOZNRu == OHshwVbEYC){kYXPuYLuBI = true;}
      while(IqEbpPWRXr == OEQzPrCLEA){yKmACrFHaA = true;}
      while(gpJhnKTsRe == gpJhnKTsRe){nZyEjrPlrd = true;}
      while(OHshwVbEYC == OHshwVbEYC){RXZPluYCJF = true;}
      if(FNigJVDsJb == true){FNigJVDsJb = false;}
      if(tosYycxeUu == true){tosYycxeUu = false;}
      if(nxgCbAxVeT == true){nxgCbAxVeT = false;}
      if(mSrVlSGcYS == true){mSrVlSGcYS = false;}
      if(GZjpkYOUiT == true){GZjpkYOUiT = false;}
      if(XxjcNIggEI == true){XxjcNIggEI = false;}
      if(XgNoobwWmf == true){XgNoobwWmf = false;}
      if(WUFBoNMpRD == true){WUFBoNMpRD = false;}
      if(kcmLwohOHd == true){kcmLwohOHd = false;}
      if(kYXPuYLuBI == true){kYXPuYLuBI = false;}
      if(cqgDwDrhnA == true){cqgDwDrhnA = false;}
      if(uqPBXttCsz == true){uqPBXttCsz = false;}
      if(sgOJtxwpGP == true){sgOJtxwpGP = false;}
      if(BRnIZswjOs == true){BRnIZswjOs = false;}
      if(xAaHhtJWrB == true){xAaHhtJWrB = false;}
      if(eJCBPwbXJz == true){eJCBPwbXJz = false;}
      if(GBbYycCHbd == true){GBbYycCHbd = false;}
      if(yKmACrFHaA == true){yKmACrFHaA = false;}
      if(nZyEjrPlrd == true){nZyEjrPlrd = false;}
      if(RXZPluYCJF == true){RXZPluYCJF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FKZPHTHEHY
{ 
  void jbNgLfDgIo()
  { 
      bool LJDgxgCROt = false;
      bool DDyKYeDegI = false;
      bool zCFQBKRjty = false;
      bool mHHyBAjwcx = false;
      bool sCqnZOeMty = false;
      bool xqyGXIDlel = false;
      bool OSXPHwwAJX = false;
      bool uHCjPxKRqm = false;
      bool eEouBuIAZr = false;
      bool xxQqhZdbfd = false;
      bool ReCWDpoNqa = false;
      bool xkurGJccOL = false;
      bool mwaRaxqKCo = false;
      bool SikMUACSrK = false;
      bool GtJytLCXjX = false;
      bool wBMUpVEkwF = false;
      bool zdLBHOAhXG = false;
      bool HKkEFrlbWO = false;
      bool tSadrRVQWy = false;
      bool wQWlKciHqf = false;
      string ClNKGedOYb;
      string jPCNfRXglH;
      string RBoFBkHpSE;
      string ABdoZxiXly;
      string wGfXZIcXnZ;
      string EGGXQBxHJV;
      string XmwUahkNmh;
      string iAumKLVRer;
      string IiBrAsuFXX;
      string AaOPaIJKwq;
      string WOjFpDLSNF;
      string eecQNnlEUg;
      string mfoOhIkeMB;
      string BKVnVszuBw;
      string hcrSrUyyCl;
      string WFpOEqZUXh;
      string SfFLDUJouU;
      string opCXzJmVWM;
      string JmcZduUGid;
      string SdXSdBWfOX;
      if(ClNKGedOYb == WOjFpDLSNF){LJDgxgCROt = true;}
      else if(WOjFpDLSNF == ClNKGedOYb){ReCWDpoNqa = true;}
      if(jPCNfRXglH == eecQNnlEUg){DDyKYeDegI = true;}
      else if(eecQNnlEUg == jPCNfRXglH){xkurGJccOL = true;}
      if(RBoFBkHpSE == mfoOhIkeMB){zCFQBKRjty = true;}
      else if(mfoOhIkeMB == RBoFBkHpSE){mwaRaxqKCo = true;}
      if(ABdoZxiXly == BKVnVszuBw){mHHyBAjwcx = true;}
      else if(BKVnVszuBw == ABdoZxiXly){SikMUACSrK = true;}
      if(wGfXZIcXnZ == hcrSrUyyCl){sCqnZOeMty = true;}
      else if(hcrSrUyyCl == wGfXZIcXnZ){GtJytLCXjX = true;}
      if(EGGXQBxHJV == WFpOEqZUXh){xqyGXIDlel = true;}
      else if(WFpOEqZUXh == EGGXQBxHJV){wBMUpVEkwF = true;}
      if(XmwUahkNmh == SfFLDUJouU){OSXPHwwAJX = true;}
      else if(SfFLDUJouU == XmwUahkNmh){zdLBHOAhXG = true;}
      if(iAumKLVRer == opCXzJmVWM){uHCjPxKRqm = true;}
      if(IiBrAsuFXX == JmcZduUGid){eEouBuIAZr = true;}
      if(AaOPaIJKwq == SdXSdBWfOX){xxQqhZdbfd = true;}
      while(opCXzJmVWM == iAumKLVRer){HKkEFrlbWO = true;}
      while(JmcZduUGid == JmcZduUGid){tSadrRVQWy = true;}
      while(SdXSdBWfOX == SdXSdBWfOX){wQWlKciHqf = true;}
      if(LJDgxgCROt == true){LJDgxgCROt = false;}
      if(DDyKYeDegI == true){DDyKYeDegI = false;}
      if(zCFQBKRjty == true){zCFQBKRjty = false;}
      if(mHHyBAjwcx == true){mHHyBAjwcx = false;}
      if(sCqnZOeMty == true){sCqnZOeMty = false;}
      if(xqyGXIDlel == true){xqyGXIDlel = false;}
      if(OSXPHwwAJX == true){OSXPHwwAJX = false;}
      if(uHCjPxKRqm == true){uHCjPxKRqm = false;}
      if(eEouBuIAZr == true){eEouBuIAZr = false;}
      if(xxQqhZdbfd == true){xxQqhZdbfd = false;}
      if(ReCWDpoNqa == true){ReCWDpoNqa = false;}
      if(xkurGJccOL == true){xkurGJccOL = false;}
      if(mwaRaxqKCo == true){mwaRaxqKCo = false;}
      if(SikMUACSrK == true){SikMUACSrK = false;}
      if(GtJytLCXjX == true){GtJytLCXjX = false;}
      if(wBMUpVEkwF == true){wBMUpVEkwF = false;}
      if(zdLBHOAhXG == true){zdLBHOAhXG = false;}
      if(HKkEFrlbWO == true){HKkEFrlbWO = false;}
      if(tSadrRVQWy == true){tSadrRVQWy = false;}
      if(wQWlKciHqf == true){wQWlKciHqf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTDNOBJHAO
{ 
  void HgZjUMmLbm()
  { 
      bool XukCdfyARl = false;
      bool UVYnWfdtIK = false;
      bool tFapXlhqWF = false;
      bool wsdaBGQbdl = false;
      bool KpzSyKuAfE = false;
      bool qZZRaSTter = false;
      bool xHdMoaqxmQ = false;
      bool PBPWAEFIrN = false;
      bool pgKROVTMAi = false;
      bool lVxlnCMmcX = false;
      bool TxNPnoKCQW = false;
      bool NLBRBPxLyT = false;
      bool GdxEdsEdhx = false;
      bool rReTssTtdY = false;
      bool KQwdUaTfjX = false;
      bool FAoJRoAJlt = false;
      bool kgUTeughXI = false;
      bool wChZIohTiC = false;
      bool YYtJqqcVCE = false;
      bool rKIimdwcyZ = false;
      string MHjtyBgcPC;
      string uuhOEwHeOu;
      string jqYxWupSaq;
      string amDJPJDqXp;
      string tRHVyYFZew;
      string tCTyoVhmWD;
      string LOBXbHqXyu;
      string sQHXBSiCyx;
      string pPmexYSFTt;
      string aPTUeePitq;
      string hgaiCduuwW;
      string lfnZNubWaC;
      string nkEEUdwlsV;
      string CzIHPIoDbS;
      string cXJxHubtHj;
      string DsIqCwcVOY;
      string hICaUlWfJE;
      string FXtHZQbGxZ;
      string BBeIRJqRES;
      string fToDkUUhbV;
      if(MHjtyBgcPC == hgaiCduuwW){XukCdfyARl = true;}
      else if(hgaiCduuwW == MHjtyBgcPC){TxNPnoKCQW = true;}
      if(uuhOEwHeOu == lfnZNubWaC){UVYnWfdtIK = true;}
      else if(lfnZNubWaC == uuhOEwHeOu){NLBRBPxLyT = true;}
      if(jqYxWupSaq == nkEEUdwlsV){tFapXlhqWF = true;}
      else if(nkEEUdwlsV == jqYxWupSaq){GdxEdsEdhx = true;}
      if(amDJPJDqXp == CzIHPIoDbS){wsdaBGQbdl = true;}
      else if(CzIHPIoDbS == amDJPJDqXp){rReTssTtdY = true;}
      if(tRHVyYFZew == cXJxHubtHj){KpzSyKuAfE = true;}
      else if(cXJxHubtHj == tRHVyYFZew){KQwdUaTfjX = true;}
      if(tCTyoVhmWD == DsIqCwcVOY){qZZRaSTter = true;}
      else if(DsIqCwcVOY == tCTyoVhmWD){FAoJRoAJlt = true;}
      if(LOBXbHqXyu == hICaUlWfJE){xHdMoaqxmQ = true;}
      else if(hICaUlWfJE == LOBXbHqXyu){kgUTeughXI = true;}
      if(sQHXBSiCyx == FXtHZQbGxZ){PBPWAEFIrN = true;}
      if(pPmexYSFTt == BBeIRJqRES){pgKROVTMAi = true;}
      if(aPTUeePitq == fToDkUUhbV){lVxlnCMmcX = true;}
      while(FXtHZQbGxZ == sQHXBSiCyx){wChZIohTiC = true;}
      while(BBeIRJqRES == BBeIRJqRES){YYtJqqcVCE = true;}
      while(fToDkUUhbV == fToDkUUhbV){rKIimdwcyZ = true;}
      if(XukCdfyARl == true){XukCdfyARl = false;}
      if(UVYnWfdtIK == true){UVYnWfdtIK = false;}
      if(tFapXlhqWF == true){tFapXlhqWF = false;}
      if(wsdaBGQbdl == true){wsdaBGQbdl = false;}
      if(KpzSyKuAfE == true){KpzSyKuAfE = false;}
      if(qZZRaSTter == true){qZZRaSTter = false;}
      if(xHdMoaqxmQ == true){xHdMoaqxmQ = false;}
      if(PBPWAEFIrN == true){PBPWAEFIrN = false;}
      if(pgKROVTMAi == true){pgKROVTMAi = false;}
      if(lVxlnCMmcX == true){lVxlnCMmcX = false;}
      if(TxNPnoKCQW == true){TxNPnoKCQW = false;}
      if(NLBRBPxLyT == true){NLBRBPxLyT = false;}
      if(GdxEdsEdhx == true){GdxEdsEdhx = false;}
      if(rReTssTtdY == true){rReTssTtdY = false;}
      if(KQwdUaTfjX == true){KQwdUaTfjX = false;}
      if(FAoJRoAJlt == true){FAoJRoAJlt = false;}
      if(kgUTeughXI == true){kgUTeughXI = false;}
      if(wChZIohTiC == true){wChZIohTiC = false;}
      if(YYtJqqcVCE == true){YYtJqqcVCE = false;}
      if(rKIimdwcyZ == true){rKIimdwcyZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKQZUXMUIT
{ 
  void exqiCxzkNM()
  { 
      bool JcsXeGSowN = false;
      bool cOspWyxIWq = false;
      bool BqTgGMxCre = false;
      bool UpNfbwnqGW = false;
      bool VMhYRIBQPu = false;
      bool JxWjlSJLQR = false;
      bool JPxRslANOa = false;
      bool JGCAUoJtPy = false;
      bool LglwUWSdtJ = false;
      bool lbZnNFPPfe = false;
      bool HmBokCtWOw = false;
      bool JOwRGbdAwV = false;
      bool TVTFnggOlO = false;
      bool YsNkqXexKR = false;
      bool buPxAXfIgl = false;
      bool bOTKKkTwAE = false;
      bool VfkAWPBKai = false;
      bool wfpdsXGVFQ = false;
      bool BXgzlKYDZF = false;
      bool DhxGwwKPZj = false;
      string NdgDflOkQy;
      string JnSCcSxHZC;
      string dSsFRBozVx;
      string uMSpSyrpkz;
      string NyEqNObIXf;
      string ozsfHtjald;
      string wOPSCwUcje;
      string aGWZneNCrC;
      string ZgboHwTmhX;
      string NREGCyhkoQ;
      string tyYrFhbSqb;
      string fhhiEPmZKG;
      string bgtLQICPXo;
      string wbMaHaHijZ;
      string TBwFqeiUBl;
      string LIainNDMbw;
      string fMtBeDVGbd;
      string HEpklakoTk;
      string YhOkdnBdmt;
      string WtGmsHGtan;
      if(NdgDflOkQy == tyYrFhbSqb){JcsXeGSowN = true;}
      else if(tyYrFhbSqb == NdgDflOkQy){HmBokCtWOw = true;}
      if(JnSCcSxHZC == fhhiEPmZKG){cOspWyxIWq = true;}
      else if(fhhiEPmZKG == JnSCcSxHZC){JOwRGbdAwV = true;}
      if(dSsFRBozVx == bgtLQICPXo){BqTgGMxCre = true;}
      else if(bgtLQICPXo == dSsFRBozVx){TVTFnggOlO = true;}
      if(uMSpSyrpkz == wbMaHaHijZ){UpNfbwnqGW = true;}
      else if(wbMaHaHijZ == uMSpSyrpkz){YsNkqXexKR = true;}
      if(NyEqNObIXf == TBwFqeiUBl){VMhYRIBQPu = true;}
      else if(TBwFqeiUBl == NyEqNObIXf){buPxAXfIgl = true;}
      if(ozsfHtjald == LIainNDMbw){JxWjlSJLQR = true;}
      else if(LIainNDMbw == ozsfHtjald){bOTKKkTwAE = true;}
      if(wOPSCwUcje == fMtBeDVGbd){JPxRslANOa = true;}
      else if(fMtBeDVGbd == wOPSCwUcje){VfkAWPBKai = true;}
      if(aGWZneNCrC == HEpklakoTk){JGCAUoJtPy = true;}
      if(ZgboHwTmhX == YhOkdnBdmt){LglwUWSdtJ = true;}
      if(NREGCyhkoQ == WtGmsHGtan){lbZnNFPPfe = true;}
      while(HEpklakoTk == aGWZneNCrC){wfpdsXGVFQ = true;}
      while(YhOkdnBdmt == YhOkdnBdmt){BXgzlKYDZF = true;}
      while(WtGmsHGtan == WtGmsHGtan){DhxGwwKPZj = true;}
      if(JcsXeGSowN == true){JcsXeGSowN = false;}
      if(cOspWyxIWq == true){cOspWyxIWq = false;}
      if(BqTgGMxCre == true){BqTgGMxCre = false;}
      if(UpNfbwnqGW == true){UpNfbwnqGW = false;}
      if(VMhYRIBQPu == true){VMhYRIBQPu = false;}
      if(JxWjlSJLQR == true){JxWjlSJLQR = false;}
      if(JPxRslANOa == true){JPxRslANOa = false;}
      if(JGCAUoJtPy == true){JGCAUoJtPy = false;}
      if(LglwUWSdtJ == true){LglwUWSdtJ = false;}
      if(lbZnNFPPfe == true){lbZnNFPPfe = false;}
      if(HmBokCtWOw == true){HmBokCtWOw = false;}
      if(JOwRGbdAwV == true){JOwRGbdAwV = false;}
      if(TVTFnggOlO == true){TVTFnggOlO = false;}
      if(YsNkqXexKR == true){YsNkqXexKR = false;}
      if(buPxAXfIgl == true){buPxAXfIgl = false;}
      if(bOTKKkTwAE == true){bOTKKkTwAE = false;}
      if(VfkAWPBKai == true){VfkAWPBKai = false;}
      if(wfpdsXGVFQ == true){wfpdsXGVFQ = false;}
      if(BXgzlKYDZF == true){BXgzlKYDZF = false;}
      if(DhxGwwKPZj == true){DhxGwwKPZj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FANLMZURZH
{ 
  void NyKcQgHDfa()
  { 
      bool DHeZZNTdEj = false;
      bool LAtdkPrYoq = false;
      bool hpgUIWaRWg = false;
      bool DQsUChKVhb = false;
      bool MDtFIfylQc = false;
      bool cQSoqNZKRC = false;
      bool lBGXftHYaD = false;
      bool EWpMeeuaLb = false;
      bool YoBsEmyEco = false;
      bool HADfoKwWYO = false;
      bool YYLNYFaFJL = false;
      bool RzyodxANSs = false;
      bool wCwlwESKWT = false;
      bool iYBxDzcmUy = false;
      bool LrtQXIBNBr = false;
      bool KhDfRVcZQT = false;
      bool lQhocrxBld = false;
      bool TMsTgDHeOn = false;
      bool CFIeIBUVeg = false;
      bool WDWALuJFne = false;
      string ecfKrzZfVx;
      string jsSOrOfmbK;
      string QJJaPluBIx;
      string dRYtzGZIQq;
      string UJdkMPbnTj;
      string kVPOyUSEtF;
      string EYWXTSUYOl;
      string oXWkpGfXNA;
      string JGgYLICJue;
      string mUOKlwmFRt;
      string uDYhuNzeXq;
      string ouptuxqyMK;
      string QKcjyTJLyt;
      string TZFTFGgzdx;
      string IWlDordTPo;
      string EnsGdjZoia;
      string EngdXPoWoo;
      string PqUPCsYZtF;
      string oouIofgzpU;
      string frPCrUoHfZ;
      if(ecfKrzZfVx == uDYhuNzeXq){DHeZZNTdEj = true;}
      else if(uDYhuNzeXq == ecfKrzZfVx){YYLNYFaFJL = true;}
      if(jsSOrOfmbK == ouptuxqyMK){LAtdkPrYoq = true;}
      else if(ouptuxqyMK == jsSOrOfmbK){RzyodxANSs = true;}
      if(QJJaPluBIx == QKcjyTJLyt){hpgUIWaRWg = true;}
      else if(QKcjyTJLyt == QJJaPluBIx){wCwlwESKWT = true;}
      if(dRYtzGZIQq == TZFTFGgzdx){DQsUChKVhb = true;}
      else if(TZFTFGgzdx == dRYtzGZIQq){iYBxDzcmUy = true;}
      if(UJdkMPbnTj == IWlDordTPo){MDtFIfylQc = true;}
      else if(IWlDordTPo == UJdkMPbnTj){LrtQXIBNBr = true;}
      if(kVPOyUSEtF == EnsGdjZoia){cQSoqNZKRC = true;}
      else if(EnsGdjZoia == kVPOyUSEtF){KhDfRVcZQT = true;}
      if(EYWXTSUYOl == EngdXPoWoo){lBGXftHYaD = true;}
      else if(EngdXPoWoo == EYWXTSUYOl){lQhocrxBld = true;}
      if(oXWkpGfXNA == PqUPCsYZtF){EWpMeeuaLb = true;}
      if(JGgYLICJue == oouIofgzpU){YoBsEmyEco = true;}
      if(mUOKlwmFRt == frPCrUoHfZ){HADfoKwWYO = true;}
      while(PqUPCsYZtF == oXWkpGfXNA){TMsTgDHeOn = true;}
      while(oouIofgzpU == oouIofgzpU){CFIeIBUVeg = true;}
      while(frPCrUoHfZ == frPCrUoHfZ){WDWALuJFne = true;}
      if(DHeZZNTdEj == true){DHeZZNTdEj = false;}
      if(LAtdkPrYoq == true){LAtdkPrYoq = false;}
      if(hpgUIWaRWg == true){hpgUIWaRWg = false;}
      if(DQsUChKVhb == true){DQsUChKVhb = false;}
      if(MDtFIfylQc == true){MDtFIfylQc = false;}
      if(cQSoqNZKRC == true){cQSoqNZKRC = false;}
      if(lBGXftHYaD == true){lBGXftHYaD = false;}
      if(EWpMeeuaLb == true){EWpMeeuaLb = false;}
      if(YoBsEmyEco == true){YoBsEmyEco = false;}
      if(HADfoKwWYO == true){HADfoKwWYO = false;}
      if(YYLNYFaFJL == true){YYLNYFaFJL = false;}
      if(RzyodxANSs == true){RzyodxANSs = false;}
      if(wCwlwESKWT == true){wCwlwESKWT = false;}
      if(iYBxDzcmUy == true){iYBxDzcmUy = false;}
      if(LrtQXIBNBr == true){LrtQXIBNBr = false;}
      if(KhDfRVcZQT == true){KhDfRVcZQT = false;}
      if(lQhocrxBld == true){lQhocrxBld = false;}
      if(TMsTgDHeOn == true){TMsTgDHeOn = false;}
      if(CFIeIBUVeg == true){CFIeIBUVeg = false;}
      if(WDWALuJFne == true){WDWALuJFne = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFKRTESHUO
{ 
  void PyzTwTkLtu()
  { 
      bool zOYMaCklFT = false;
      bool UFHDHBdDJp = false;
      bool EsBNaJgRMV = false;
      bool JQesubaGrJ = false;
      bool fZZVgtYqzH = false;
      bool lXWmyGNLlR = false;
      bool USYiKEaNHe = false;
      bool aXKzJdTeff = false;
      bool jpRFjlsqto = false;
      bool OPTanMAqLb = false;
      bool TLiUgNMWcU = false;
      bool lheGhdATzX = false;
      bool KiSSQKDjKx = false;
      bool ccSEMYHxXV = false;
      bool ZVNZCfkNsK = false;
      bool LgqnQjrPDW = false;
      bool JbLfqJOZsI = false;
      bool WDwcynUsQj = false;
      bool ZpqAkwkemb = false;
      bool fqsBLxKhhr = false;
      string piAdlRAViZ;
      string oUTdSRCOuW;
      string goYXKfpSpA;
      string FuLLHdXqgS;
      string gSaKkZNnHo;
      string AmlAtBJbTF;
      string bgeiTtJIVn;
      string sKhcoNNNmj;
      string SBLBASILQG;
      string UuWaqznrqq;
      string PFRSuoEJKg;
      string muoimZUdhA;
      string kyrOTxmGkp;
      string ZVWwTMisFL;
      string NzBjTYGnmR;
      string dJJqFRNCyy;
      string ByXUGQYrPZ;
      string pbYWlkxHuu;
      string pzTTLQMepB;
      string zftGJPafcC;
      if(piAdlRAViZ == PFRSuoEJKg){zOYMaCklFT = true;}
      else if(PFRSuoEJKg == piAdlRAViZ){TLiUgNMWcU = true;}
      if(oUTdSRCOuW == muoimZUdhA){UFHDHBdDJp = true;}
      else if(muoimZUdhA == oUTdSRCOuW){lheGhdATzX = true;}
      if(goYXKfpSpA == kyrOTxmGkp){EsBNaJgRMV = true;}
      else if(kyrOTxmGkp == goYXKfpSpA){KiSSQKDjKx = true;}
      if(FuLLHdXqgS == ZVWwTMisFL){JQesubaGrJ = true;}
      else if(ZVWwTMisFL == FuLLHdXqgS){ccSEMYHxXV = true;}
      if(gSaKkZNnHo == NzBjTYGnmR){fZZVgtYqzH = true;}
      else if(NzBjTYGnmR == gSaKkZNnHo){ZVNZCfkNsK = true;}
      if(AmlAtBJbTF == dJJqFRNCyy){lXWmyGNLlR = true;}
      else if(dJJqFRNCyy == AmlAtBJbTF){LgqnQjrPDW = true;}
      if(bgeiTtJIVn == ByXUGQYrPZ){USYiKEaNHe = true;}
      else if(ByXUGQYrPZ == bgeiTtJIVn){JbLfqJOZsI = true;}
      if(sKhcoNNNmj == pbYWlkxHuu){aXKzJdTeff = true;}
      if(SBLBASILQG == pzTTLQMepB){jpRFjlsqto = true;}
      if(UuWaqznrqq == zftGJPafcC){OPTanMAqLb = true;}
      while(pbYWlkxHuu == sKhcoNNNmj){WDwcynUsQj = true;}
      while(pzTTLQMepB == pzTTLQMepB){ZpqAkwkemb = true;}
      while(zftGJPafcC == zftGJPafcC){fqsBLxKhhr = true;}
      if(zOYMaCklFT == true){zOYMaCklFT = false;}
      if(UFHDHBdDJp == true){UFHDHBdDJp = false;}
      if(EsBNaJgRMV == true){EsBNaJgRMV = false;}
      if(JQesubaGrJ == true){JQesubaGrJ = false;}
      if(fZZVgtYqzH == true){fZZVgtYqzH = false;}
      if(lXWmyGNLlR == true){lXWmyGNLlR = false;}
      if(USYiKEaNHe == true){USYiKEaNHe = false;}
      if(aXKzJdTeff == true){aXKzJdTeff = false;}
      if(jpRFjlsqto == true){jpRFjlsqto = false;}
      if(OPTanMAqLb == true){OPTanMAqLb = false;}
      if(TLiUgNMWcU == true){TLiUgNMWcU = false;}
      if(lheGhdATzX == true){lheGhdATzX = false;}
      if(KiSSQKDjKx == true){KiSSQKDjKx = false;}
      if(ccSEMYHxXV == true){ccSEMYHxXV = false;}
      if(ZVNZCfkNsK == true){ZVNZCfkNsK = false;}
      if(LgqnQjrPDW == true){LgqnQjrPDW = false;}
      if(JbLfqJOZsI == true){JbLfqJOZsI = false;}
      if(WDwcynUsQj == true){WDwcynUsQj = false;}
      if(ZpqAkwkemb == true){ZpqAkwkemb = false;}
      if(fqsBLxKhhr == true){fqsBLxKhhr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RAIASJAFBV
{ 
  void xmnbQaHXKx()
  { 
      bool JdjJAfoUTz = false;
      bool MylnJcWVno = false;
      bool hnEsDiJYlx = false;
      bool CefrEKzlAl = false;
      bool JIDcWtxZQy = false;
      bool nDTdtUZqGR = false;
      bool VQiVwgRtjz = false;
      bool dkVBfZkaWI = false;
      bool kjHmIzLBxi = false;
      bool kIehPsYgfo = false;
      bool bDoRTDhRyU = false;
      bool jyTxglIuNx = false;
      bool VQwANVFmll = false;
      bool ADugfgtpSF = false;
      bool RsCcylnhBd = false;
      bool kcThTLHoDy = false;
      bool ytfMUfDmQz = false;
      bool rRcHfbNTBb = false;
      bool hWlHBWjMNU = false;
      bool ZElUGWNpHS = false;
      string OnpfeRuKks;
      string pbBHWRtYAw;
      string KpMIhtxENh;
      string KegKkGaXdA;
      string iJpxIxwnBo;
      string hNrobXahxk;
      string UqwDiKtpVP;
      string qWtAMAzOAk;
      string xJCXAwmqiM;
      string frZseqNmOx;
      string CFRlyKTqba;
      string XLhLmLnYDl;
      string WCHJizxBUV;
      string mMACiqrQZo;
      string cuOHnUJNFT;
      string DnicZzyHCy;
      string NRWGnLLfcw;
      string SXzNIamzUN;
      string ojuARycWbi;
      string sjNabLYITc;
      if(OnpfeRuKks == CFRlyKTqba){JdjJAfoUTz = true;}
      else if(CFRlyKTqba == OnpfeRuKks){bDoRTDhRyU = true;}
      if(pbBHWRtYAw == XLhLmLnYDl){MylnJcWVno = true;}
      else if(XLhLmLnYDl == pbBHWRtYAw){jyTxglIuNx = true;}
      if(KpMIhtxENh == WCHJizxBUV){hnEsDiJYlx = true;}
      else if(WCHJizxBUV == KpMIhtxENh){VQwANVFmll = true;}
      if(KegKkGaXdA == mMACiqrQZo){CefrEKzlAl = true;}
      else if(mMACiqrQZo == KegKkGaXdA){ADugfgtpSF = true;}
      if(iJpxIxwnBo == cuOHnUJNFT){JIDcWtxZQy = true;}
      else if(cuOHnUJNFT == iJpxIxwnBo){RsCcylnhBd = true;}
      if(hNrobXahxk == DnicZzyHCy){nDTdtUZqGR = true;}
      else if(DnicZzyHCy == hNrobXahxk){kcThTLHoDy = true;}
      if(UqwDiKtpVP == NRWGnLLfcw){VQiVwgRtjz = true;}
      else if(NRWGnLLfcw == UqwDiKtpVP){ytfMUfDmQz = true;}
      if(qWtAMAzOAk == SXzNIamzUN){dkVBfZkaWI = true;}
      if(xJCXAwmqiM == ojuARycWbi){kjHmIzLBxi = true;}
      if(frZseqNmOx == sjNabLYITc){kIehPsYgfo = true;}
      while(SXzNIamzUN == qWtAMAzOAk){rRcHfbNTBb = true;}
      while(ojuARycWbi == ojuARycWbi){hWlHBWjMNU = true;}
      while(sjNabLYITc == sjNabLYITc){ZElUGWNpHS = true;}
      if(JdjJAfoUTz == true){JdjJAfoUTz = false;}
      if(MylnJcWVno == true){MylnJcWVno = false;}
      if(hnEsDiJYlx == true){hnEsDiJYlx = false;}
      if(CefrEKzlAl == true){CefrEKzlAl = false;}
      if(JIDcWtxZQy == true){JIDcWtxZQy = false;}
      if(nDTdtUZqGR == true){nDTdtUZqGR = false;}
      if(VQiVwgRtjz == true){VQiVwgRtjz = false;}
      if(dkVBfZkaWI == true){dkVBfZkaWI = false;}
      if(kjHmIzLBxi == true){kjHmIzLBxi = false;}
      if(kIehPsYgfo == true){kIehPsYgfo = false;}
      if(bDoRTDhRyU == true){bDoRTDhRyU = false;}
      if(jyTxglIuNx == true){jyTxglIuNx = false;}
      if(VQwANVFmll == true){VQwANVFmll = false;}
      if(ADugfgtpSF == true){ADugfgtpSF = false;}
      if(RsCcylnhBd == true){RsCcylnhBd = false;}
      if(kcThTLHoDy == true){kcThTLHoDy = false;}
      if(ytfMUfDmQz == true){ytfMUfDmQz = false;}
      if(rRcHfbNTBb == true){rRcHfbNTBb = false;}
      if(hWlHBWjMNU == true){hWlHBWjMNU = false;}
      if(ZElUGWNpHS == true){ZElUGWNpHS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVEJABHFQF
{ 
  void ETiLRxpJBz()
  { 
      bool hsLLHQjPJK = false;
      bool FwYNYnMWtJ = false;
      bool cTEgumAoEo = false;
      bool PnDCoVdNZG = false;
      bool NXkCPwuILM = false;
      bool VtbFsNoeQU = false;
      bool QuLUtRrVYC = false;
      bool JzxnwEhBRz = false;
      bool rrcrTULyIa = false;
      bool gywFpRMQHx = false;
      bool DYiJCWxnIo = false;
      bool emNRcXRSBZ = false;
      bool FtMxVKCqyd = false;
      bool qRsTuSITox = false;
      bool XXoTutkebR = false;
      bool AsOhrJMlmr = false;
      bool TFpexNstVJ = false;
      bool PydDBgFrCa = false;
      bool ZWPfdyCLak = false;
      bool GWfxcRgJVh = false;
      string JqzXpSJzxl;
      string optjsPwXYc;
      string PRxailRXLA;
      string OLXUGjGpBn;
      string BxCuYhbnNX;
      string nilFhqtYoE;
      string BlmwWcRZcJ;
      string IFWjaSPBBB;
      string JcJnMfYSlP;
      string ohBwmPJFYw;
      string PCLDOhMCdP;
      string brWmuXbzjq;
      string EznNTaEZxL;
      string IJcFkGRFYd;
      string TWoVnxLNAO;
      string mKVgrQNyjn;
      string dlFRHRPRBn;
      string GVZFWgKRYW;
      string PpZhXxnuNU;
      string rTVkAhRWOW;
      if(JqzXpSJzxl == PCLDOhMCdP){hsLLHQjPJK = true;}
      else if(PCLDOhMCdP == JqzXpSJzxl){DYiJCWxnIo = true;}
      if(optjsPwXYc == brWmuXbzjq){FwYNYnMWtJ = true;}
      else if(brWmuXbzjq == optjsPwXYc){emNRcXRSBZ = true;}
      if(PRxailRXLA == EznNTaEZxL){cTEgumAoEo = true;}
      else if(EznNTaEZxL == PRxailRXLA){FtMxVKCqyd = true;}
      if(OLXUGjGpBn == IJcFkGRFYd){PnDCoVdNZG = true;}
      else if(IJcFkGRFYd == OLXUGjGpBn){qRsTuSITox = true;}
      if(BxCuYhbnNX == TWoVnxLNAO){NXkCPwuILM = true;}
      else if(TWoVnxLNAO == BxCuYhbnNX){XXoTutkebR = true;}
      if(nilFhqtYoE == mKVgrQNyjn){VtbFsNoeQU = true;}
      else if(mKVgrQNyjn == nilFhqtYoE){AsOhrJMlmr = true;}
      if(BlmwWcRZcJ == dlFRHRPRBn){QuLUtRrVYC = true;}
      else if(dlFRHRPRBn == BlmwWcRZcJ){TFpexNstVJ = true;}
      if(IFWjaSPBBB == GVZFWgKRYW){JzxnwEhBRz = true;}
      if(JcJnMfYSlP == PpZhXxnuNU){rrcrTULyIa = true;}
      if(ohBwmPJFYw == rTVkAhRWOW){gywFpRMQHx = true;}
      while(GVZFWgKRYW == IFWjaSPBBB){PydDBgFrCa = true;}
      while(PpZhXxnuNU == PpZhXxnuNU){ZWPfdyCLak = true;}
      while(rTVkAhRWOW == rTVkAhRWOW){GWfxcRgJVh = true;}
      if(hsLLHQjPJK == true){hsLLHQjPJK = false;}
      if(FwYNYnMWtJ == true){FwYNYnMWtJ = false;}
      if(cTEgumAoEo == true){cTEgumAoEo = false;}
      if(PnDCoVdNZG == true){PnDCoVdNZG = false;}
      if(NXkCPwuILM == true){NXkCPwuILM = false;}
      if(VtbFsNoeQU == true){VtbFsNoeQU = false;}
      if(QuLUtRrVYC == true){QuLUtRrVYC = false;}
      if(JzxnwEhBRz == true){JzxnwEhBRz = false;}
      if(rrcrTULyIa == true){rrcrTULyIa = false;}
      if(gywFpRMQHx == true){gywFpRMQHx = false;}
      if(DYiJCWxnIo == true){DYiJCWxnIo = false;}
      if(emNRcXRSBZ == true){emNRcXRSBZ = false;}
      if(FtMxVKCqyd == true){FtMxVKCqyd = false;}
      if(qRsTuSITox == true){qRsTuSITox = false;}
      if(XXoTutkebR == true){XXoTutkebR = false;}
      if(AsOhrJMlmr == true){AsOhrJMlmr = false;}
      if(TFpexNstVJ == true){TFpexNstVJ = false;}
      if(PydDBgFrCa == true){PydDBgFrCa = false;}
      if(ZWPfdyCLak == true){ZWPfdyCLak = false;}
      if(GWfxcRgJVh == true){GWfxcRgJVh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKUXNMLLJN
{ 
  void ffrhpdMemB()
  { 
      bool fKCmFhDMCz = false;
      bool hDPKYxLsWP = false;
      bool BFzOCnZcOd = false;
      bool JqJpBCxefV = false;
      bool nEpKZJgAyI = false;
      bool dOaZMZLmjQ = false;
      bool IZxYppsYIW = false;
      bool AfMAbwPoos = false;
      bool HYeGztQida = false;
      bool pJuONNHRTi = false;
      bool QIqaIxCayP = false;
      bool KWxqJjuqYw = false;
      bool YKuhgpkxlO = false;
      bool oxUFbygDxC = false;
      bool qpjNPTMDFd = false;
      bool RPrXKGNJtS = false;
      bool LEnjaMBqOK = false;
      bool CrtVEiZgRM = false;
      bool chrIwYExuV = false;
      bool kXIdqmCAmD = false;
      string mKxEHCEVpZ;
      string bnKTQSphuj;
      string QLfRmMYIgs;
      string UbCOdSiqdX;
      string EEELVWwzBD;
      string TCfeOaefQu;
      string cwoxEAlwpy;
      string jyDXfLHTwP;
      string PZGdYSuXzC;
      string mDZitIPGHV;
      string kzICSVzIyC;
      string TKiBfDoLYl;
      string ENwnKgYUcX;
      string uAMadPRDKD;
      string SmYxhcTYCq;
      string SEhUQWCUrl;
      string wdeaGTxIWP;
      string kkAVSRozFg;
      string MzRlEqRrJH;
      string MwLXGoHxpO;
      if(mKxEHCEVpZ == kzICSVzIyC){fKCmFhDMCz = true;}
      else if(kzICSVzIyC == mKxEHCEVpZ){QIqaIxCayP = true;}
      if(bnKTQSphuj == TKiBfDoLYl){hDPKYxLsWP = true;}
      else if(TKiBfDoLYl == bnKTQSphuj){KWxqJjuqYw = true;}
      if(QLfRmMYIgs == ENwnKgYUcX){BFzOCnZcOd = true;}
      else if(ENwnKgYUcX == QLfRmMYIgs){YKuhgpkxlO = true;}
      if(UbCOdSiqdX == uAMadPRDKD){JqJpBCxefV = true;}
      else if(uAMadPRDKD == UbCOdSiqdX){oxUFbygDxC = true;}
      if(EEELVWwzBD == SmYxhcTYCq){nEpKZJgAyI = true;}
      else if(SmYxhcTYCq == EEELVWwzBD){qpjNPTMDFd = true;}
      if(TCfeOaefQu == SEhUQWCUrl){dOaZMZLmjQ = true;}
      else if(SEhUQWCUrl == TCfeOaefQu){RPrXKGNJtS = true;}
      if(cwoxEAlwpy == wdeaGTxIWP){IZxYppsYIW = true;}
      else if(wdeaGTxIWP == cwoxEAlwpy){LEnjaMBqOK = true;}
      if(jyDXfLHTwP == kkAVSRozFg){AfMAbwPoos = true;}
      if(PZGdYSuXzC == MzRlEqRrJH){HYeGztQida = true;}
      if(mDZitIPGHV == MwLXGoHxpO){pJuONNHRTi = true;}
      while(kkAVSRozFg == jyDXfLHTwP){CrtVEiZgRM = true;}
      while(MzRlEqRrJH == MzRlEqRrJH){chrIwYExuV = true;}
      while(MwLXGoHxpO == MwLXGoHxpO){kXIdqmCAmD = true;}
      if(fKCmFhDMCz == true){fKCmFhDMCz = false;}
      if(hDPKYxLsWP == true){hDPKYxLsWP = false;}
      if(BFzOCnZcOd == true){BFzOCnZcOd = false;}
      if(JqJpBCxefV == true){JqJpBCxefV = false;}
      if(nEpKZJgAyI == true){nEpKZJgAyI = false;}
      if(dOaZMZLmjQ == true){dOaZMZLmjQ = false;}
      if(IZxYppsYIW == true){IZxYppsYIW = false;}
      if(AfMAbwPoos == true){AfMAbwPoos = false;}
      if(HYeGztQida == true){HYeGztQida = false;}
      if(pJuONNHRTi == true){pJuONNHRTi = false;}
      if(QIqaIxCayP == true){QIqaIxCayP = false;}
      if(KWxqJjuqYw == true){KWxqJjuqYw = false;}
      if(YKuhgpkxlO == true){YKuhgpkxlO = false;}
      if(oxUFbygDxC == true){oxUFbygDxC = false;}
      if(qpjNPTMDFd == true){qpjNPTMDFd = false;}
      if(RPrXKGNJtS == true){RPrXKGNJtS = false;}
      if(LEnjaMBqOK == true){LEnjaMBqOK = false;}
      if(CrtVEiZgRM == true){CrtVEiZgRM = false;}
      if(chrIwYExuV == true){chrIwYExuV = false;}
      if(kXIdqmCAmD == true){kXIdqmCAmD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQPFJBNLJY
{ 
  void eciriXoUNz()
  { 
      bool NPXAMbEojB = false;
      bool AAsCUpTmqQ = false;
      bool cYeLWaGulH = false;
      bool GAVNEkRtoe = false;
      bool WkurVttqqI = false;
      bool xbjHAnkMdk = false;
      bool VIDbtAefxi = false;
      bool XYxLsqdlpc = false;
      bool fPEcKeQNMP = false;
      bool AFQDJOhSxV = false;
      bool OOsHjXdXNJ = false;
      bool KyWAFGEZRP = false;
      bool iRThiSIsCe = false;
      bool IKoUORVxrl = false;
      bool AszCFCiQyC = false;
      bool KIBhlxtLYR = false;
      bool PjUiAzJClm = false;
      bool jHgeOpRQbg = false;
      bool iquAUAJGhQ = false;
      bool WKXaWQXQCF = false;
      string qcRicZOIrs;
      string gdgmJDlbgD;
      string ZzfLVTCcZU;
      string eiSUcKiBkm;
      string bkKcwqUTGf;
      string NULJVrxFMI;
      string XkiWOxLLJz;
      string TkqsaonDPe;
      string ziWtHJWIzk;
      string MdnbPqBnNy;
      string eIJHLcdSig;
      string DtohInOoOE;
      string aCMYlowOcj;
      string nzoQzpYOhe;
      string fEZRgSnGSb;
      string bLYJXcukVV;
      string fOozsDEXhR;
      string OzHjYVbtqS;
      string BpuBHbafsW;
      string unsLyQPaYd;
      if(qcRicZOIrs == eIJHLcdSig){NPXAMbEojB = true;}
      else if(eIJHLcdSig == qcRicZOIrs){OOsHjXdXNJ = true;}
      if(gdgmJDlbgD == DtohInOoOE){AAsCUpTmqQ = true;}
      else if(DtohInOoOE == gdgmJDlbgD){KyWAFGEZRP = true;}
      if(ZzfLVTCcZU == aCMYlowOcj){cYeLWaGulH = true;}
      else if(aCMYlowOcj == ZzfLVTCcZU){iRThiSIsCe = true;}
      if(eiSUcKiBkm == nzoQzpYOhe){GAVNEkRtoe = true;}
      else if(nzoQzpYOhe == eiSUcKiBkm){IKoUORVxrl = true;}
      if(bkKcwqUTGf == fEZRgSnGSb){WkurVttqqI = true;}
      else if(fEZRgSnGSb == bkKcwqUTGf){AszCFCiQyC = true;}
      if(NULJVrxFMI == bLYJXcukVV){xbjHAnkMdk = true;}
      else if(bLYJXcukVV == NULJVrxFMI){KIBhlxtLYR = true;}
      if(XkiWOxLLJz == fOozsDEXhR){VIDbtAefxi = true;}
      else if(fOozsDEXhR == XkiWOxLLJz){PjUiAzJClm = true;}
      if(TkqsaonDPe == OzHjYVbtqS){XYxLsqdlpc = true;}
      if(ziWtHJWIzk == BpuBHbafsW){fPEcKeQNMP = true;}
      if(MdnbPqBnNy == unsLyQPaYd){AFQDJOhSxV = true;}
      while(OzHjYVbtqS == TkqsaonDPe){jHgeOpRQbg = true;}
      while(BpuBHbafsW == BpuBHbafsW){iquAUAJGhQ = true;}
      while(unsLyQPaYd == unsLyQPaYd){WKXaWQXQCF = true;}
      if(NPXAMbEojB == true){NPXAMbEojB = false;}
      if(AAsCUpTmqQ == true){AAsCUpTmqQ = false;}
      if(cYeLWaGulH == true){cYeLWaGulH = false;}
      if(GAVNEkRtoe == true){GAVNEkRtoe = false;}
      if(WkurVttqqI == true){WkurVttqqI = false;}
      if(xbjHAnkMdk == true){xbjHAnkMdk = false;}
      if(VIDbtAefxi == true){VIDbtAefxi = false;}
      if(XYxLsqdlpc == true){XYxLsqdlpc = false;}
      if(fPEcKeQNMP == true){fPEcKeQNMP = false;}
      if(AFQDJOhSxV == true){AFQDJOhSxV = false;}
      if(OOsHjXdXNJ == true){OOsHjXdXNJ = false;}
      if(KyWAFGEZRP == true){KyWAFGEZRP = false;}
      if(iRThiSIsCe == true){iRThiSIsCe = false;}
      if(IKoUORVxrl == true){IKoUORVxrl = false;}
      if(AszCFCiQyC == true){AszCFCiQyC = false;}
      if(KIBhlxtLYR == true){KIBhlxtLYR = false;}
      if(PjUiAzJClm == true){PjUiAzJClm = false;}
      if(jHgeOpRQbg == true){jHgeOpRQbg = false;}
      if(iquAUAJGhQ == true){iquAUAJGhQ = false;}
      if(WKXaWQXQCF == true){WKXaWQXQCF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKWADNPPNJ
{ 
  void OtXUqQzbLS()
  { 
      bool pEQTogWTcY = false;
      bool hVnljDfqXB = false;
      bool EAuPHQxbzq = false;
      bool MKMlueDyAY = false;
      bool ddhYZYHzNx = false;
      bool mKqKkoJBMY = false;
      bool juTlMXJCpF = false;
      bool AhqyXaSVph = false;
      bool IyNCEBSBBG = false;
      bool UCkaoiJwMB = false;
      bool PFIIxETrmK = false;
      bool WnLePlgRhK = false;
      bool FHAjjyxPJo = false;
      bool QVInRDoFFz = false;
      bool haNqigqGLC = false;
      bool CqNCwIEXXy = false;
      bool HDhysAeWML = false;
      bool waMhbdsJAD = false;
      bool HpEGlZHGqJ = false;
      bool zRgGqerPyi = false;
      string mhcTcAjqSZ;
      string CpFrlyDhRo;
      string jyIUkLacgh;
      string swZBEllNfA;
      string NyhutrmZKN;
      string YooclnYHhQ;
      string ZHKkfGPDmA;
      string MpCRblQNas;
      string YARSJEHwPQ;
      string MeeOaFnxOn;
      string bimKBilXBA;
      string WKforYpqab;
      string zTnVmhKnpV;
      string xTymQpMHRZ;
      string RitOsBypVB;
      string PwVmnHtQWT;
      string YygeCDLsYC;
      string MhZBKPZYck;
      string iURoGAyLyI;
      string uukxBSCPMp;
      if(mhcTcAjqSZ == bimKBilXBA){pEQTogWTcY = true;}
      else if(bimKBilXBA == mhcTcAjqSZ){PFIIxETrmK = true;}
      if(CpFrlyDhRo == WKforYpqab){hVnljDfqXB = true;}
      else if(WKforYpqab == CpFrlyDhRo){WnLePlgRhK = true;}
      if(jyIUkLacgh == zTnVmhKnpV){EAuPHQxbzq = true;}
      else if(zTnVmhKnpV == jyIUkLacgh){FHAjjyxPJo = true;}
      if(swZBEllNfA == xTymQpMHRZ){MKMlueDyAY = true;}
      else if(xTymQpMHRZ == swZBEllNfA){QVInRDoFFz = true;}
      if(NyhutrmZKN == RitOsBypVB){ddhYZYHzNx = true;}
      else if(RitOsBypVB == NyhutrmZKN){haNqigqGLC = true;}
      if(YooclnYHhQ == PwVmnHtQWT){mKqKkoJBMY = true;}
      else if(PwVmnHtQWT == YooclnYHhQ){CqNCwIEXXy = true;}
      if(ZHKkfGPDmA == YygeCDLsYC){juTlMXJCpF = true;}
      else if(YygeCDLsYC == ZHKkfGPDmA){HDhysAeWML = true;}
      if(MpCRblQNas == MhZBKPZYck){AhqyXaSVph = true;}
      if(YARSJEHwPQ == iURoGAyLyI){IyNCEBSBBG = true;}
      if(MeeOaFnxOn == uukxBSCPMp){UCkaoiJwMB = true;}
      while(MhZBKPZYck == MpCRblQNas){waMhbdsJAD = true;}
      while(iURoGAyLyI == iURoGAyLyI){HpEGlZHGqJ = true;}
      while(uukxBSCPMp == uukxBSCPMp){zRgGqerPyi = true;}
      if(pEQTogWTcY == true){pEQTogWTcY = false;}
      if(hVnljDfqXB == true){hVnljDfqXB = false;}
      if(EAuPHQxbzq == true){EAuPHQxbzq = false;}
      if(MKMlueDyAY == true){MKMlueDyAY = false;}
      if(ddhYZYHzNx == true){ddhYZYHzNx = false;}
      if(mKqKkoJBMY == true){mKqKkoJBMY = false;}
      if(juTlMXJCpF == true){juTlMXJCpF = false;}
      if(AhqyXaSVph == true){AhqyXaSVph = false;}
      if(IyNCEBSBBG == true){IyNCEBSBBG = false;}
      if(UCkaoiJwMB == true){UCkaoiJwMB = false;}
      if(PFIIxETrmK == true){PFIIxETrmK = false;}
      if(WnLePlgRhK == true){WnLePlgRhK = false;}
      if(FHAjjyxPJo == true){FHAjjyxPJo = false;}
      if(QVInRDoFFz == true){QVInRDoFFz = false;}
      if(haNqigqGLC == true){haNqigqGLC = false;}
      if(CqNCwIEXXy == true){CqNCwIEXXy = false;}
      if(HDhysAeWML == true){HDhysAeWML = false;}
      if(waMhbdsJAD == true){waMhbdsJAD = false;}
      if(HpEGlZHGqJ == true){HpEGlZHGqJ = false;}
      if(zRgGqerPyi == true){zRgGqerPyi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQXZLBIZQN
{ 
  void KIDRXotELM()
  { 
      bool WGQuaWFGSo = false;
      bool SniIOCqCLX = false;
      bool bGbZZVSCiM = false;
      bool ZxWspoQnup = false;
      bool mfUlnSVGCJ = false;
      bool LzEORPeqVE = false;
      bool ECWFOURpRY = false;
      bool kDHVjulokG = false;
      bool zLAZAasHba = false;
      bool JZSpkjJOXT = false;
      bool AfocYHqhdV = false;
      bool dpFOErCwEm = false;
      bool bJOqPKkQkA = false;
      bool kWRRGTWWAs = false;
      bool jKcFwTTDkr = false;
      bool hMJjqqRxNO = false;
      bool WZxdkHYnIk = false;
      bool UeuLDQfJtu = false;
      bool pgfrSXMgZO = false;
      bool CYJlVJNzUo = false;
      string NCLlYGCKYe;
      string UuJzKaFecO;
      string uclDsZLyWV;
      string VwKJuxOJJz;
      string aIulqULUMd;
      string LGZdVjPHry;
      string tDnCJXjAEM;
      string MwUdnlhzLY;
      string OqksKOWfmK;
      string hGQKFWUscS;
      string kKPAQOkwpi;
      string CQwTjCRuqt;
      string BDNteGeKXR;
      string RnVrmDakbw;
      string dZoDHQKxaC;
      string EYBiQgxVVK;
      string jaXYQOtDff;
      string bgTuPbNJlN;
      string whiVMslmbG;
      string GFOQLDBQms;
      if(NCLlYGCKYe == kKPAQOkwpi){WGQuaWFGSo = true;}
      else if(kKPAQOkwpi == NCLlYGCKYe){AfocYHqhdV = true;}
      if(UuJzKaFecO == CQwTjCRuqt){SniIOCqCLX = true;}
      else if(CQwTjCRuqt == UuJzKaFecO){dpFOErCwEm = true;}
      if(uclDsZLyWV == BDNteGeKXR){bGbZZVSCiM = true;}
      else if(BDNteGeKXR == uclDsZLyWV){bJOqPKkQkA = true;}
      if(VwKJuxOJJz == RnVrmDakbw){ZxWspoQnup = true;}
      else if(RnVrmDakbw == VwKJuxOJJz){kWRRGTWWAs = true;}
      if(aIulqULUMd == dZoDHQKxaC){mfUlnSVGCJ = true;}
      else if(dZoDHQKxaC == aIulqULUMd){jKcFwTTDkr = true;}
      if(LGZdVjPHry == EYBiQgxVVK){LzEORPeqVE = true;}
      else if(EYBiQgxVVK == LGZdVjPHry){hMJjqqRxNO = true;}
      if(tDnCJXjAEM == jaXYQOtDff){ECWFOURpRY = true;}
      else if(jaXYQOtDff == tDnCJXjAEM){WZxdkHYnIk = true;}
      if(MwUdnlhzLY == bgTuPbNJlN){kDHVjulokG = true;}
      if(OqksKOWfmK == whiVMslmbG){zLAZAasHba = true;}
      if(hGQKFWUscS == GFOQLDBQms){JZSpkjJOXT = true;}
      while(bgTuPbNJlN == MwUdnlhzLY){UeuLDQfJtu = true;}
      while(whiVMslmbG == whiVMslmbG){pgfrSXMgZO = true;}
      while(GFOQLDBQms == GFOQLDBQms){CYJlVJNzUo = true;}
      if(WGQuaWFGSo == true){WGQuaWFGSo = false;}
      if(SniIOCqCLX == true){SniIOCqCLX = false;}
      if(bGbZZVSCiM == true){bGbZZVSCiM = false;}
      if(ZxWspoQnup == true){ZxWspoQnup = false;}
      if(mfUlnSVGCJ == true){mfUlnSVGCJ = false;}
      if(LzEORPeqVE == true){LzEORPeqVE = false;}
      if(ECWFOURpRY == true){ECWFOURpRY = false;}
      if(kDHVjulokG == true){kDHVjulokG = false;}
      if(zLAZAasHba == true){zLAZAasHba = false;}
      if(JZSpkjJOXT == true){JZSpkjJOXT = false;}
      if(AfocYHqhdV == true){AfocYHqhdV = false;}
      if(dpFOErCwEm == true){dpFOErCwEm = false;}
      if(bJOqPKkQkA == true){bJOqPKkQkA = false;}
      if(kWRRGTWWAs == true){kWRRGTWWAs = false;}
      if(jKcFwTTDkr == true){jKcFwTTDkr = false;}
      if(hMJjqqRxNO == true){hMJjqqRxNO = false;}
      if(WZxdkHYnIk == true){WZxdkHYnIk = false;}
      if(UeuLDQfJtu == true){UeuLDQfJtu = false;}
      if(pgfrSXMgZO == true){pgfrSXMgZO = false;}
      if(CYJlVJNzUo == true){CYJlVJNzUo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDEKVGPLEW
{ 
  void dIFcaaLqSp()
  { 
      bool QLsJcgmawY = false;
      bool SrSfHoJnQK = false;
      bool ZgRGMtCkQt = false;
      bool HHEClsNwiZ = false;
      bool JCpFSsDYDe = false;
      bool oTbQHitmwh = false;
      bool eBKBQLmPtO = false;
      bool bMFpAXpMmT = false;
      bool qchlEnfmtC = false;
      bool zaAAuHqnnH = false;
      bool FmenCcNkQi = false;
      bool rgzcqBTXxc = false;
      bool ezUqOBMFts = false;
      bool fBXeNDysib = false;
      bool atWLKRaXIt = false;
      bool nTqLcGSmZB = false;
      bool PIqXDpJUOn = false;
      bool CaoUBjbJgx = false;
      bool aowzEMKLCH = false;
      bool kLThLSDzHT = false;
      string ZwhKmRDnqD;
      string FpmdVLEFVa;
      string PcZjWdaxRf;
      string BQozbCWYZc;
      string rcYzCidanP;
      string XIAEaxVxmJ;
      string qFWKBoAnBS;
      string nferimDZgn;
      string AzJBIsQkXe;
      string fZlQllFNyN;
      string hoZUbqdHUn;
      string swQyIqwVCI;
      string YPPWlOtNGx;
      string gobTFKZnYQ;
      string OIPiljImHt;
      string ojLooSYDhN;
      string xPAXHDTwsy;
      string RIwksPzgjC;
      string FHGLHxclel;
      string kWFLTzHrbh;
      if(ZwhKmRDnqD == hoZUbqdHUn){QLsJcgmawY = true;}
      else if(hoZUbqdHUn == ZwhKmRDnqD){FmenCcNkQi = true;}
      if(FpmdVLEFVa == swQyIqwVCI){SrSfHoJnQK = true;}
      else if(swQyIqwVCI == FpmdVLEFVa){rgzcqBTXxc = true;}
      if(PcZjWdaxRf == YPPWlOtNGx){ZgRGMtCkQt = true;}
      else if(YPPWlOtNGx == PcZjWdaxRf){ezUqOBMFts = true;}
      if(BQozbCWYZc == gobTFKZnYQ){HHEClsNwiZ = true;}
      else if(gobTFKZnYQ == BQozbCWYZc){fBXeNDysib = true;}
      if(rcYzCidanP == OIPiljImHt){JCpFSsDYDe = true;}
      else if(OIPiljImHt == rcYzCidanP){atWLKRaXIt = true;}
      if(XIAEaxVxmJ == ojLooSYDhN){oTbQHitmwh = true;}
      else if(ojLooSYDhN == XIAEaxVxmJ){nTqLcGSmZB = true;}
      if(qFWKBoAnBS == xPAXHDTwsy){eBKBQLmPtO = true;}
      else if(xPAXHDTwsy == qFWKBoAnBS){PIqXDpJUOn = true;}
      if(nferimDZgn == RIwksPzgjC){bMFpAXpMmT = true;}
      if(AzJBIsQkXe == FHGLHxclel){qchlEnfmtC = true;}
      if(fZlQllFNyN == kWFLTzHrbh){zaAAuHqnnH = true;}
      while(RIwksPzgjC == nferimDZgn){CaoUBjbJgx = true;}
      while(FHGLHxclel == FHGLHxclel){aowzEMKLCH = true;}
      while(kWFLTzHrbh == kWFLTzHrbh){kLThLSDzHT = true;}
      if(QLsJcgmawY == true){QLsJcgmawY = false;}
      if(SrSfHoJnQK == true){SrSfHoJnQK = false;}
      if(ZgRGMtCkQt == true){ZgRGMtCkQt = false;}
      if(HHEClsNwiZ == true){HHEClsNwiZ = false;}
      if(JCpFSsDYDe == true){JCpFSsDYDe = false;}
      if(oTbQHitmwh == true){oTbQHitmwh = false;}
      if(eBKBQLmPtO == true){eBKBQLmPtO = false;}
      if(bMFpAXpMmT == true){bMFpAXpMmT = false;}
      if(qchlEnfmtC == true){qchlEnfmtC = false;}
      if(zaAAuHqnnH == true){zaAAuHqnnH = false;}
      if(FmenCcNkQi == true){FmenCcNkQi = false;}
      if(rgzcqBTXxc == true){rgzcqBTXxc = false;}
      if(ezUqOBMFts == true){ezUqOBMFts = false;}
      if(fBXeNDysib == true){fBXeNDysib = false;}
      if(atWLKRaXIt == true){atWLKRaXIt = false;}
      if(nTqLcGSmZB == true){nTqLcGSmZB = false;}
      if(PIqXDpJUOn == true){PIqXDpJUOn = false;}
      if(CaoUBjbJgx == true){CaoUBjbJgx = false;}
      if(aowzEMKLCH == true){aowzEMKLCH = false;}
      if(kLThLSDzHT == true){kLThLSDzHT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWUMGRFQZY
{ 
  void WqMtuHBwIs()
  { 
      bool JbWQOFxqST = false;
      bool zxUeldGZuC = false;
      bool mmsGVOLpcw = false;
      bool gnkLYwePZu = false;
      bool IbaOqdmkdB = false;
      bool czIfdWhQuA = false;
      bool sHOVmKLJGp = false;
      bool yqzztLLeOr = false;
      bool aaLaSgfEhB = false;
      bool NOUZCBMEbg = false;
      bool SdenCkzIlR = false;
      bool KDCCYSumDF = false;
      bool dGbEbjWZxr = false;
      bool zHChZwwXYh = false;
      bool hXSPqKMRBj = false;
      bool FZBWCLCZLS = false;
      bool NZKtSCBTcb = false;
      bool VXOUXFnLMR = false;
      bool WFYNlYGeeN = false;
      bool tVLFTHNXxn = false;
      string PYtdGrDfcz;
      string kDOSUiVarW;
      string oyFadmIleq;
      string pLdjRgLzZA;
      string DoILuJLBXM;
      string ZjhyURSSzS;
      string jRBlJYYdBm;
      string WWBqTzptfT;
      string aGNRQFdfOz;
      string OrzGQknVCV;
      string kgzkoDhpeV;
      string aYmfqdEiVD;
      string tsOBXdWuah;
      string LTrJitGbbM;
      string WnAsYpFTOl;
      string gEAyarSyML;
      string gmOwJHfcxx;
      string XbGIfGrUch;
      string YCfoBGTsip;
      string aIPQfjYDiR;
      if(PYtdGrDfcz == kgzkoDhpeV){JbWQOFxqST = true;}
      else if(kgzkoDhpeV == PYtdGrDfcz){SdenCkzIlR = true;}
      if(kDOSUiVarW == aYmfqdEiVD){zxUeldGZuC = true;}
      else if(aYmfqdEiVD == kDOSUiVarW){KDCCYSumDF = true;}
      if(oyFadmIleq == tsOBXdWuah){mmsGVOLpcw = true;}
      else if(tsOBXdWuah == oyFadmIleq){dGbEbjWZxr = true;}
      if(pLdjRgLzZA == LTrJitGbbM){gnkLYwePZu = true;}
      else if(LTrJitGbbM == pLdjRgLzZA){zHChZwwXYh = true;}
      if(DoILuJLBXM == WnAsYpFTOl){IbaOqdmkdB = true;}
      else if(WnAsYpFTOl == DoILuJLBXM){hXSPqKMRBj = true;}
      if(ZjhyURSSzS == gEAyarSyML){czIfdWhQuA = true;}
      else if(gEAyarSyML == ZjhyURSSzS){FZBWCLCZLS = true;}
      if(jRBlJYYdBm == gmOwJHfcxx){sHOVmKLJGp = true;}
      else if(gmOwJHfcxx == jRBlJYYdBm){NZKtSCBTcb = true;}
      if(WWBqTzptfT == XbGIfGrUch){yqzztLLeOr = true;}
      if(aGNRQFdfOz == YCfoBGTsip){aaLaSgfEhB = true;}
      if(OrzGQknVCV == aIPQfjYDiR){NOUZCBMEbg = true;}
      while(XbGIfGrUch == WWBqTzptfT){VXOUXFnLMR = true;}
      while(YCfoBGTsip == YCfoBGTsip){WFYNlYGeeN = true;}
      while(aIPQfjYDiR == aIPQfjYDiR){tVLFTHNXxn = true;}
      if(JbWQOFxqST == true){JbWQOFxqST = false;}
      if(zxUeldGZuC == true){zxUeldGZuC = false;}
      if(mmsGVOLpcw == true){mmsGVOLpcw = false;}
      if(gnkLYwePZu == true){gnkLYwePZu = false;}
      if(IbaOqdmkdB == true){IbaOqdmkdB = false;}
      if(czIfdWhQuA == true){czIfdWhQuA = false;}
      if(sHOVmKLJGp == true){sHOVmKLJGp = false;}
      if(yqzztLLeOr == true){yqzztLLeOr = false;}
      if(aaLaSgfEhB == true){aaLaSgfEhB = false;}
      if(NOUZCBMEbg == true){NOUZCBMEbg = false;}
      if(SdenCkzIlR == true){SdenCkzIlR = false;}
      if(KDCCYSumDF == true){KDCCYSumDF = false;}
      if(dGbEbjWZxr == true){dGbEbjWZxr = false;}
      if(zHChZwwXYh == true){zHChZwwXYh = false;}
      if(hXSPqKMRBj == true){hXSPqKMRBj = false;}
      if(FZBWCLCZLS == true){FZBWCLCZLS = false;}
      if(NZKtSCBTcb == true){NZKtSCBTcb = false;}
      if(VXOUXFnLMR == true){VXOUXFnLMR = false;}
      if(WFYNlYGeeN == true){WFYNlYGeeN = false;}
      if(tVLFTHNXxn == true){tVLFTHNXxn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SGMGTNLHHV
{ 
  void eAZhdyEHJY()
  { 
      bool HmttMOmRTu = false;
      bool jrgQnhgkoF = false;
      bool AyQyWgRfJJ = false;
      bool diJcVzePtF = false;
      bool VlhdsGwSBf = false;
      bool VkjxIIVwWf = false;
      bool wGHJRAiEun = false;
      bool DQqjjOQmFQ = false;
      bool jyddnszMUM = false;
      bool chsNIOdXMr = false;
      bool XrXMcEsANt = false;
      bool riqGwycdVY = false;
      bool AViiLUWcaU = false;
      bool jsaMrqaRBi = false;
      bool zzzaUsqmRK = false;
      bool lABmqCInBH = false;
      bool hQYrJyIdNE = false;
      bool WKcmYBWIOS = false;
      bool cjLQijqmUp = false;
      bool hlQsBiaGQV = false;
      string HdorbkQyCO;
      string aMYDbrXgbX;
      string BfZuuIFXFk;
      string xYysoxkMMN;
      string pnBENtQjLy;
      string MllZtbEtwT;
      string essRRCNeNe;
      string GLTNgMdUgB;
      string qULHXLmYzM;
      string rpQshxujlL;
      string glVgqBRXrg;
      string yiMubKgltF;
      string OofBlQtaej;
      string RshVTFzePV;
      string sOgSOIdUQX;
      string QIpgwqFUta;
      string HqrIOEApaW;
      string KCVXMAHNmc;
      string lYJHTIDBZc;
      string zdjoOCVYDJ;
      if(HdorbkQyCO == glVgqBRXrg){HmttMOmRTu = true;}
      else if(glVgqBRXrg == HdorbkQyCO){XrXMcEsANt = true;}
      if(aMYDbrXgbX == yiMubKgltF){jrgQnhgkoF = true;}
      else if(yiMubKgltF == aMYDbrXgbX){riqGwycdVY = true;}
      if(BfZuuIFXFk == OofBlQtaej){AyQyWgRfJJ = true;}
      else if(OofBlQtaej == BfZuuIFXFk){AViiLUWcaU = true;}
      if(xYysoxkMMN == RshVTFzePV){diJcVzePtF = true;}
      else if(RshVTFzePV == xYysoxkMMN){jsaMrqaRBi = true;}
      if(pnBENtQjLy == sOgSOIdUQX){VlhdsGwSBf = true;}
      else if(sOgSOIdUQX == pnBENtQjLy){zzzaUsqmRK = true;}
      if(MllZtbEtwT == QIpgwqFUta){VkjxIIVwWf = true;}
      else if(QIpgwqFUta == MllZtbEtwT){lABmqCInBH = true;}
      if(essRRCNeNe == HqrIOEApaW){wGHJRAiEun = true;}
      else if(HqrIOEApaW == essRRCNeNe){hQYrJyIdNE = true;}
      if(GLTNgMdUgB == KCVXMAHNmc){DQqjjOQmFQ = true;}
      if(qULHXLmYzM == lYJHTIDBZc){jyddnszMUM = true;}
      if(rpQshxujlL == zdjoOCVYDJ){chsNIOdXMr = true;}
      while(KCVXMAHNmc == GLTNgMdUgB){WKcmYBWIOS = true;}
      while(lYJHTIDBZc == lYJHTIDBZc){cjLQijqmUp = true;}
      while(zdjoOCVYDJ == zdjoOCVYDJ){hlQsBiaGQV = true;}
      if(HmttMOmRTu == true){HmttMOmRTu = false;}
      if(jrgQnhgkoF == true){jrgQnhgkoF = false;}
      if(AyQyWgRfJJ == true){AyQyWgRfJJ = false;}
      if(diJcVzePtF == true){diJcVzePtF = false;}
      if(VlhdsGwSBf == true){VlhdsGwSBf = false;}
      if(VkjxIIVwWf == true){VkjxIIVwWf = false;}
      if(wGHJRAiEun == true){wGHJRAiEun = false;}
      if(DQqjjOQmFQ == true){DQqjjOQmFQ = false;}
      if(jyddnszMUM == true){jyddnszMUM = false;}
      if(chsNIOdXMr == true){chsNIOdXMr = false;}
      if(XrXMcEsANt == true){XrXMcEsANt = false;}
      if(riqGwycdVY == true){riqGwycdVY = false;}
      if(AViiLUWcaU == true){AViiLUWcaU = false;}
      if(jsaMrqaRBi == true){jsaMrqaRBi = false;}
      if(zzzaUsqmRK == true){zzzaUsqmRK = false;}
      if(lABmqCInBH == true){lABmqCInBH = false;}
      if(hQYrJyIdNE == true){hQYrJyIdNE = false;}
      if(WKcmYBWIOS == true){WKcmYBWIOS = false;}
      if(cjLQijqmUp == true){cjLQijqmUp = false;}
      if(hlQsBiaGQV == true){hlQsBiaGQV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMUKXXWSBQ
{ 
  void eYXyfZksKt()
  { 
      bool ALCsmdjJgJ = false;
      bool mUqXBWFNxZ = false;
      bool uGokGuDKye = false;
      bool PxbseQqTpV = false;
      bool xkcUcuHNYJ = false;
      bool POYLTsWRlq = false;
      bool aZKCsorysk = false;
      bool flXbbJcTHL = false;
      bool mplnOBYQYk = false;
      bool tYgyuXZabm = false;
      bool CJTmddpxiJ = false;
      bool PCKaDkmVmr = false;
      bool QbZIpGFZgE = false;
      bool jCrTJdVyKk = false;
      bool KbgOUqOGtJ = false;
      bool jEnjWZjLxX = false;
      bool YQQeZNKpRZ = false;
      bool OnLCgouKmy = false;
      bool qyeWTeOHwi = false;
      bool tJBmLsLBnG = false;
      string zpgZrajBrJ;
      string owsIjNmATf;
      string MSMmllURSz;
      string mIVhNHZOoh;
      string OuMtsUzIca;
      string lEnicgcsnG;
      string GSirWfaKtb;
      string nXKlQQFRsQ;
      string lMorNhUlEg;
      string dfaiawMUXM;
      string tnNAmOtBRL;
      string aLAWTscpeo;
      string LnGNxIxbKT;
      string EksfWxynFy;
      string nSUsFSeDPh;
      string TVpiBGhzCe;
      string QRpyHpRTAV;
      string tokfBrTNIe;
      string ctMcAhuKeP;
      string PzkagVbVkP;
      if(zpgZrajBrJ == tnNAmOtBRL){ALCsmdjJgJ = true;}
      else if(tnNAmOtBRL == zpgZrajBrJ){CJTmddpxiJ = true;}
      if(owsIjNmATf == aLAWTscpeo){mUqXBWFNxZ = true;}
      else if(aLAWTscpeo == owsIjNmATf){PCKaDkmVmr = true;}
      if(MSMmllURSz == LnGNxIxbKT){uGokGuDKye = true;}
      else if(LnGNxIxbKT == MSMmllURSz){QbZIpGFZgE = true;}
      if(mIVhNHZOoh == EksfWxynFy){PxbseQqTpV = true;}
      else if(EksfWxynFy == mIVhNHZOoh){jCrTJdVyKk = true;}
      if(OuMtsUzIca == nSUsFSeDPh){xkcUcuHNYJ = true;}
      else if(nSUsFSeDPh == OuMtsUzIca){KbgOUqOGtJ = true;}
      if(lEnicgcsnG == TVpiBGhzCe){POYLTsWRlq = true;}
      else if(TVpiBGhzCe == lEnicgcsnG){jEnjWZjLxX = true;}
      if(GSirWfaKtb == QRpyHpRTAV){aZKCsorysk = true;}
      else if(QRpyHpRTAV == GSirWfaKtb){YQQeZNKpRZ = true;}
      if(nXKlQQFRsQ == tokfBrTNIe){flXbbJcTHL = true;}
      if(lMorNhUlEg == ctMcAhuKeP){mplnOBYQYk = true;}
      if(dfaiawMUXM == PzkagVbVkP){tYgyuXZabm = true;}
      while(tokfBrTNIe == nXKlQQFRsQ){OnLCgouKmy = true;}
      while(ctMcAhuKeP == ctMcAhuKeP){qyeWTeOHwi = true;}
      while(PzkagVbVkP == PzkagVbVkP){tJBmLsLBnG = true;}
      if(ALCsmdjJgJ == true){ALCsmdjJgJ = false;}
      if(mUqXBWFNxZ == true){mUqXBWFNxZ = false;}
      if(uGokGuDKye == true){uGokGuDKye = false;}
      if(PxbseQqTpV == true){PxbseQqTpV = false;}
      if(xkcUcuHNYJ == true){xkcUcuHNYJ = false;}
      if(POYLTsWRlq == true){POYLTsWRlq = false;}
      if(aZKCsorysk == true){aZKCsorysk = false;}
      if(flXbbJcTHL == true){flXbbJcTHL = false;}
      if(mplnOBYQYk == true){mplnOBYQYk = false;}
      if(tYgyuXZabm == true){tYgyuXZabm = false;}
      if(CJTmddpxiJ == true){CJTmddpxiJ = false;}
      if(PCKaDkmVmr == true){PCKaDkmVmr = false;}
      if(QbZIpGFZgE == true){QbZIpGFZgE = false;}
      if(jCrTJdVyKk == true){jCrTJdVyKk = false;}
      if(KbgOUqOGtJ == true){KbgOUqOGtJ = false;}
      if(jEnjWZjLxX == true){jEnjWZjLxX = false;}
      if(YQQeZNKpRZ == true){YQQeZNKpRZ = false;}
      if(OnLCgouKmy == true){OnLCgouKmy = false;}
      if(qyeWTeOHwi == true){qyeWTeOHwi = false;}
      if(tJBmLsLBnG == true){tJBmLsLBnG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSXINIPUAP
{ 
  void EQDgQNsOLc()
  { 
      bool EIljIXauDd = false;
      bool eHpWKQJjdS = false;
      bool DJszwsyktb = false;
      bool TzDBtFVepZ = false;
      bool zqlzbdALsJ = false;
      bool tROlHuOlmO = false;
      bool ZoBbKfDobE = false;
      bool tdsESMXtXS = false;
      bool slqjhCjRsy = false;
      bool pjqaAJpKnw = false;
      bool aKioPPXKSu = false;
      bool XUNUVmyQsI = false;
      bool ukwdOKlRDJ = false;
      bool VNFbqhCCUR = false;
      bool dZzyaVVWFM = false;
      bool LZQfAoOFZE = false;
      bool cFGIYJOkcm = false;
      bool kuubdUkxCs = false;
      bool nPMqxwxYaB = false;
      bool SxbPoXSpYR = false;
      string yZmboesCeF;
      string cjblqmVrhs;
      string SRoGUgnfoj;
      string TJVnbMMmJP;
      string CueaYBJbDs;
      string JmuVHfkgGH;
      string qNNtlTOmKe;
      string ZhiRqXmNgT;
      string XLcuafNzgu;
      string bfgBYohjoE;
      string mVRYSaEcdi;
      string sXzmjejRTG;
      string FOGOCtBgsC;
      string pCXbfBtEcz;
      string akVxCDfsRt;
      string EPPizYPDVY;
      string YXibspzWHh;
      string kfoUeUsIMz;
      string OIOzxZmocH;
      string kqhDZDBsEL;
      if(yZmboesCeF == mVRYSaEcdi){EIljIXauDd = true;}
      else if(mVRYSaEcdi == yZmboesCeF){aKioPPXKSu = true;}
      if(cjblqmVrhs == sXzmjejRTG){eHpWKQJjdS = true;}
      else if(sXzmjejRTG == cjblqmVrhs){XUNUVmyQsI = true;}
      if(SRoGUgnfoj == FOGOCtBgsC){DJszwsyktb = true;}
      else if(FOGOCtBgsC == SRoGUgnfoj){ukwdOKlRDJ = true;}
      if(TJVnbMMmJP == pCXbfBtEcz){TzDBtFVepZ = true;}
      else if(pCXbfBtEcz == TJVnbMMmJP){VNFbqhCCUR = true;}
      if(CueaYBJbDs == akVxCDfsRt){zqlzbdALsJ = true;}
      else if(akVxCDfsRt == CueaYBJbDs){dZzyaVVWFM = true;}
      if(JmuVHfkgGH == EPPizYPDVY){tROlHuOlmO = true;}
      else if(EPPizYPDVY == JmuVHfkgGH){LZQfAoOFZE = true;}
      if(qNNtlTOmKe == YXibspzWHh){ZoBbKfDobE = true;}
      else if(YXibspzWHh == qNNtlTOmKe){cFGIYJOkcm = true;}
      if(ZhiRqXmNgT == kfoUeUsIMz){tdsESMXtXS = true;}
      if(XLcuafNzgu == OIOzxZmocH){slqjhCjRsy = true;}
      if(bfgBYohjoE == kqhDZDBsEL){pjqaAJpKnw = true;}
      while(kfoUeUsIMz == ZhiRqXmNgT){kuubdUkxCs = true;}
      while(OIOzxZmocH == OIOzxZmocH){nPMqxwxYaB = true;}
      while(kqhDZDBsEL == kqhDZDBsEL){SxbPoXSpYR = true;}
      if(EIljIXauDd == true){EIljIXauDd = false;}
      if(eHpWKQJjdS == true){eHpWKQJjdS = false;}
      if(DJszwsyktb == true){DJszwsyktb = false;}
      if(TzDBtFVepZ == true){TzDBtFVepZ = false;}
      if(zqlzbdALsJ == true){zqlzbdALsJ = false;}
      if(tROlHuOlmO == true){tROlHuOlmO = false;}
      if(ZoBbKfDobE == true){ZoBbKfDobE = false;}
      if(tdsESMXtXS == true){tdsESMXtXS = false;}
      if(slqjhCjRsy == true){slqjhCjRsy = false;}
      if(pjqaAJpKnw == true){pjqaAJpKnw = false;}
      if(aKioPPXKSu == true){aKioPPXKSu = false;}
      if(XUNUVmyQsI == true){XUNUVmyQsI = false;}
      if(ukwdOKlRDJ == true){ukwdOKlRDJ = false;}
      if(VNFbqhCCUR == true){VNFbqhCCUR = false;}
      if(dZzyaVVWFM == true){dZzyaVVWFM = false;}
      if(LZQfAoOFZE == true){LZQfAoOFZE = false;}
      if(cFGIYJOkcm == true){cFGIYJOkcm = false;}
      if(kuubdUkxCs == true){kuubdUkxCs = false;}
      if(nPMqxwxYaB == true){nPMqxwxYaB = false;}
      if(SxbPoXSpYR == true){SxbPoXSpYR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNADQILLGI
{ 
  void OxpdteCcQy()
  { 
      bool fNNTqSLdDg = false;
      bool UfEwrMLSFq = false;
      bool rMPybYSqSy = false;
      bool qMLgYqRnyE = false;
      bool hAAZmQIAJZ = false;
      bool hWxjUSyOqS = false;
      bool zTKEoHTXXA = false;
      bool uWUAIrMoLL = false;
      bool QShsQUPbLF = false;
      bool sCxfFOpuke = false;
      bool xkbIeLCwac = false;
      bool GIDfCgkQnU = false;
      bool qqLSHrYout = false;
      bool CQEfOepYNE = false;
      bool RTAiyjzRdX = false;
      bool cYGPnFZJBm = false;
      bool lNAgapEXQW = false;
      bool pLCiDXpcTW = false;
      bool sHLWQcJnqI = false;
      bool EfXaSDSTHI = false;
      string fNgUPfnhic;
      string RDXsBMwmjT;
      string fLsUDsgWzb;
      string mJydpiphDg;
      string PhcqDiLjUK;
      string FEglhTTLRV;
      string yRiHoIFtCR;
      string VOiDDyiCRT;
      string gwCoVibMuV;
      string PePhhyzUBu;
      string cRgDopVdhj;
      string kRsxoCOskF;
      string fsygCpyBUF;
      string zNAWqPOyAe;
      string NydLkxkSse;
      string iFjwOiSABy;
      string rTIbkWRWFY;
      string mQsGrhOmuE;
      string FeIpWtdEHH;
      string wNxBmspCaN;
      if(fNgUPfnhic == cRgDopVdhj){fNNTqSLdDg = true;}
      else if(cRgDopVdhj == fNgUPfnhic){xkbIeLCwac = true;}
      if(RDXsBMwmjT == kRsxoCOskF){UfEwrMLSFq = true;}
      else if(kRsxoCOskF == RDXsBMwmjT){GIDfCgkQnU = true;}
      if(fLsUDsgWzb == fsygCpyBUF){rMPybYSqSy = true;}
      else if(fsygCpyBUF == fLsUDsgWzb){qqLSHrYout = true;}
      if(mJydpiphDg == zNAWqPOyAe){qMLgYqRnyE = true;}
      else if(zNAWqPOyAe == mJydpiphDg){CQEfOepYNE = true;}
      if(PhcqDiLjUK == NydLkxkSse){hAAZmQIAJZ = true;}
      else if(NydLkxkSse == PhcqDiLjUK){RTAiyjzRdX = true;}
      if(FEglhTTLRV == iFjwOiSABy){hWxjUSyOqS = true;}
      else if(iFjwOiSABy == FEglhTTLRV){cYGPnFZJBm = true;}
      if(yRiHoIFtCR == rTIbkWRWFY){zTKEoHTXXA = true;}
      else if(rTIbkWRWFY == yRiHoIFtCR){lNAgapEXQW = true;}
      if(VOiDDyiCRT == mQsGrhOmuE){uWUAIrMoLL = true;}
      if(gwCoVibMuV == FeIpWtdEHH){QShsQUPbLF = true;}
      if(PePhhyzUBu == wNxBmspCaN){sCxfFOpuke = true;}
      while(mQsGrhOmuE == VOiDDyiCRT){pLCiDXpcTW = true;}
      while(FeIpWtdEHH == FeIpWtdEHH){sHLWQcJnqI = true;}
      while(wNxBmspCaN == wNxBmspCaN){EfXaSDSTHI = true;}
      if(fNNTqSLdDg == true){fNNTqSLdDg = false;}
      if(UfEwrMLSFq == true){UfEwrMLSFq = false;}
      if(rMPybYSqSy == true){rMPybYSqSy = false;}
      if(qMLgYqRnyE == true){qMLgYqRnyE = false;}
      if(hAAZmQIAJZ == true){hAAZmQIAJZ = false;}
      if(hWxjUSyOqS == true){hWxjUSyOqS = false;}
      if(zTKEoHTXXA == true){zTKEoHTXXA = false;}
      if(uWUAIrMoLL == true){uWUAIrMoLL = false;}
      if(QShsQUPbLF == true){QShsQUPbLF = false;}
      if(sCxfFOpuke == true){sCxfFOpuke = false;}
      if(xkbIeLCwac == true){xkbIeLCwac = false;}
      if(GIDfCgkQnU == true){GIDfCgkQnU = false;}
      if(qqLSHrYout == true){qqLSHrYout = false;}
      if(CQEfOepYNE == true){CQEfOepYNE = false;}
      if(RTAiyjzRdX == true){RTAiyjzRdX = false;}
      if(cYGPnFZJBm == true){cYGPnFZJBm = false;}
      if(lNAgapEXQW == true){lNAgapEXQW = false;}
      if(pLCiDXpcTW == true){pLCiDXpcTW = false;}
      if(sHLWQcJnqI == true){sHLWQcJnqI = false;}
      if(EfXaSDSTHI == true){EfXaSDSTHI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYGJOFHLIS
{ 
  void alKssPUYNS()
  { 
      bool IFdwtpNIfy = false;
      bool pNIpTEgLgy = false;
      bool dniEVuqFHA = false;
      bool UoMGprjePb = false;
      bool DkOqsNwtqp = false;
      bool aLIEdUWZaz = false;
      bool zHAedABCAb = false;
      bool UBuFusZqKH = false;
      bool yxORYIgIbU = false;
      bool VJEQcujiNr = false;
      bool MtsOUZPCIk = false;
      bool tePSABriFU = false;
      bool TrZeFKxecz = false;
      bool JqdRuEDAwz = false;
      bool rezqaptkPa = false;
      bool DAcrYTTOIK = false;
      bool bkZJbDAxWw = false;
      bool xrlGboshEO = false;
      bool QLPBuINksa = false;
      bool joqlXHEoPW = false;
      string yLSYEVwDnU;
      string dNUQhWyhLj;
      string MoqyhlFnjI;
      string wVSJQfGDOk;
      string crHolkVOhL;
      string tyBrfJUTqS;
      string QHSeXHuLAC;
      string PtSZGUgBMw;
      string PpFYOxUadH;
      string LmMwUUYbQd;
      string pKOfuAeakL;
      string bTHtCaCtQa;
      string lUhrqcgVEk;
      string uEjhGEaZcN;
      string RtoRereStt;
      string SeLpqVcVoR;
      string TIVzPWiZnx;
      string zbQCJrePNy;
      string yObKSQstpj;
      string bEjKtIXoCH;
      if(yLSYEVwDnU == pKOfuAeakL){IFdwtpNIfy = true;}
      else if(pKOfuAeakL == yLSYEVwDnU){MtsOUZPCIk = true;}
      if(dNUQhWyhLj == bTHtCaCtQa){pNIpTEgLgy = true;}
      else if(bTHtCaCtQa == dNUQhWyhLj){tePSABriFU = true;}
      if(MoqyhlFnjI == lUhrqcgVEk){dniEVuqFHA = true;}
      else if(lUhrqcgVEk == MoqyhlFnjI){TrZeFKxecz = true;}
      if(wVSJQfGDOk == uEjhGEaZcN){UoMGprjePb = true;}
      else if(uEjhGEaZcN == wVSJQfGDOk){JqdRuEDAwz = true;}
      if(crHolkVOhL == RtoRereStt){DkOqsNwtqp = true;}
      else if(RtoRereStt == crHolkVOhL){rezqaptkPa = true;}
      if(tyBrfJUTqS == SeLpqVcVoR){aLIEdUWZaz = true;}
      else if(SeLpqVcVoR == tyBrfJUTqS){DAcrYTTOIK = true;}
      if(QHSeXHuLAC == TIVzPWiZnx){zHAedABCAb = true;}
      else if(TIVzPWiZnx == QHSeXHuLAC){bkZJbDAxWw = true;}
      if(PtSZGUgBMw == zbQCJrePNy){UBuFusZqKH = true;}
      if(PpFYOxUadH == yObKSQstpj){yxORYIgIbU = true;}
      if(LmMwUUYbQd == bEjKtIXoCH){VJEQcujiNr = true;}
      while(zbQCJrePNy == PtSZGUgBMw){xrlGboshEO = true;}
      while(yObKSQstpj == yObKSQstpj){QLPBuINksa = true;}
      while(bEjKtIXoCH == bEjKtIXoCH){joqlXHEoPW = true;}
      if(IFdwtpNIfy == true){IFdwtpNIfy = false;}
      if(pNIpTEgLgy == true){pNIpTEgLgy = false;}
      if(dniEVuqFHA == true){dniEVuqFHA = false;}
      if(UoMGprjePb == true){UoMGprjePb = false;}
      if(DkOqsNwtqp == true){DkOqsNwtqp = false;}
      if(aLIEdUWZaz == true){aLIEdUWZaz = false;}
      if(zHAedABCAb == true){zHAedABCAb = false;}
      if(UBuFusZqKH == true){UBuFusZqKH = false;}
      if(yxORYIgIbU == true){yxORYIgIbU = false;}
      if(VJEQcujiNr == true){VJEQcujiNr = false;}
      if(MtsOUZPCIk == true){MtsOUZPCIk = false;}
      if(tePSABriFU == true){tePSABriFU = false;}
      if(TrZeFKxecz == true){TrZeFKxecz = false;}
      if(JqdRuEDAwz == true){JqdRuEDAwz = false;}
      if(rezqaptkPa == true){rezqaptkPa = false;}
      if(DAcrYTTOIK == true){DAcrYTTOIK = false;}
      if(bkZJbDAxWw == true){bkZJbDAxWw = false;}
      if(xrlGboshEO == true){xrlGboshEO = false;}
      if(QLPBuINksa == true){QLPBuINksa = false;}
      if(joqlXHEoPW == true){joqlXHEoPW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RULJQRUMSC
{ 
  void BpbrRqzZLO()
  { 
      bool XJkiwFjBhG = false;
      bool TJyIfToXmD = false;
      bool WixnzcqljL = false;
      bool zLCrflwAUb = false;
      bool jnYEKUwNQG = false;
      bool PmGflnLwjS = false;
      bool OxRVGIHGct = false;
      bool XnCKSiKrdd = false;
      bool fcVcwMEVFq = false;
      bool ZzQCMmWCyC = false;
      bool NpkWiajuMD = false;
      bool cSSFmlanZt = false;
      bool DkAkTYXAyf = false;
      bool LHtaQorytU = false;
      bool bJJBNHfLPa = false;
      bool LicEycozDK = false;
      bool DjxfqUXqnx = false;
      bool tcsERtazXL = false;
      bool rMkWUcepcn = false;
      bool ArtjRqMcJs = false;
      string iVKJVnZnhe;
      string ObxOXLNxDr;
      string MOeTpFAQSZ;
      string lcYpFytxgc;
      string ZxJjOttgDG;
      string GlBnZTppTP;
      string nJVHslDHIZ;
      string RQPaROEuFu;
      string LTMMSzajQk;
      string IDcRoQbBqc;
      string qlXdooWaVK;
      string PtkXDTwIos;
      string LSqXRNmxlB;
      string mCEcDZuiXc;
      string cANFVNRFNU;
      string TTMxQYtAMa;
      string CYoUWMpITd;
      string YNjLPKEkBD;
      string uhjQhToGLe;
      string euWxaEKsiJ;
      if(iVKJVnZnhe == qlXdooWaVK){XJkiwFjBhG = true;}
      else if(qlXdooWaVK == iVKJVnZnhe){NpkWiajuMD = true;}
      if(ObxOXLNxDr == PtkXDTwIos){TJyIfToXmD = true;}
      else if(PtkXDTwIos == ObxOXLNxDr){cSSFmlanZt = true;}
      if(MOeTpFAQSZ == LSqXRNmxlB){WixnzcqljL = true;}
      else if(LSqXRNmxlB == MOeTpFAQSZ){DkAkTYXAyf = true;}
      if(lcYpFytxgc == mCEcDZuiXc){zLCrflwAUb = true;}
      else if(mCEcDZuiXc == lcYpFytxgc){LHtaQorytU = true;}
      if(ZxJjOttgDG == cANFVNRFNU){jnYEKUwNQG = true;}
      else if(cANFVNRFNU == ZxJjOttgDG){bJJBNHfLPa = true;}
      if(GlBnZTppTP == TTMxQYtAMa){PmGflnLwjS = true;}
      else if(TTMxQYtAMa == GlBnZTppTP){LicEycozDK = true;}
      if(nJVHslDHIZ == CYoUWMpITd){OxRVGIHGct = true;}
      else if(CYoUWMpITd == nJVHslDHIZ){DjxfqUXqnx = true;}
      if(RQPaROEuFu == YNjLPKEkBD){XnCKSiKrdd = true;}
      if(LTMMSzajQk == uhjQhToGLe){fcVcwMEVFq = true;}
      if(IDcRoQbBqc == euWxaEKsiJ){ZzQCMmWCyC = true;}
      while(YNjLPKEkBD == RQPaROEuFu){tcsERtazXL = true;}
      while(uhjQhToGLe == uhjQhToGLe){rMkWUcepcn = true;}
      while(euWxaEKsiJ == euWxaEKsiJ){ArtjRqMcJs = true;}
      if(XJkiwFjBhG == true){XJkiwFjBhG = false;}
      if(TJyIfToXmD == true){TJyIfToXmD = false;}
      if(WixnzcqljL == true){WixnzcqljL = false;}
      if(zLCrflwAUb == true){zLCrflwAUb = false;}
      if(jnYEKUwNQG == true){jnYEKUwNQG = false;}
      if(PmGflnLwjS == true){PmGflnLwjS = false;}
      if(OxRVGIHGct == true){OxRVGIHGct = false;}
      if(XnCKSiKrdd == true){XnCKSiKrdd = false;}
      if(fcVcwMEVFq == true){fcVcwMEVFq = false;}
      if(ZzQCMmWCyC == true){ZzQCMmWCyC = false;}
      if(NpkWiajuMD == true){NpkWiajuMD = false;}
      if(cSSFmlanZt == true){cSSFmlanZt = false;}
      if(DkAkTYXAyf == true){DkAkTYXAyf = false;}
      if(LHtaQorytU == true){LHtaQorytU = false;}
      if(bJJBNHfLPa == true){bJJBNHfLPa = false;}
      if(LicEycozDK == true){LicEycozDK = false;}
      if(DjxfqUXqnx == true){DjxfqUXqnx = false;}
      if(tcsERtazXL == true){tcsERtazXL = false;}
      if(rMkWUcepcn == true){rMkWUcepcn = false;}
      if(ArtjRqMcJs == true){ArtjRqMcJs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWJRGEKQYK
{ 
  void VdSrTAHyEb()
  { 
      bool xZHAexUfNM = false;
      bool BnbqltnPBP = false;
      bool knEmodSkfI = false;
      bool lukzzdsExy = false;
      bool aLeupgTYIV = false;
      bool XMjzIJVTLA = false;
      bool dizFaGCbrI = false;
      bool AiSDnZIIxI = false;
      bool KtcJjZKlqp = false;
      bool HYswTrLZTj = false;
      bool dqgzVotgLh = false;
      bool AMWCpjGpUB = false;
      bool wQkBAboViw = false;
      bool NhoNeSNcnu = false;
      bool ecZIptBpFj = false;
      bool kVFSmMGeys = false;
      bool zXyOTRXJXW = false;
      bool WcBYVSpbLF = false;
      bool ZyPzKrcVZR = false;
      bool LietuHeLnX = false;
      string DqUjFUTKXY;
      string aFWMJtOhSb;
      string WyrgBGaIYR;
      string exeKZoVdgo;
      string eFrEmZdXlF;
      string UMDWZEyniz;
      string sKlFtcZLlT;
      string XjAcwQGmsa;
      string cCWTxStIjU;
      string qguhuUTlKK;
      string zRlRgkLZZI;
      string yKuHVpnSIb;
      string iQbQcpoRhb;
      string xUcibKQElL;
      string GUiaWflmLF;
      string fBciaioUnq;
      string utrxLchLfK;
      string ZifwUOgAsx;
      string EBFbuwqsHr;
      string VuPuQMblPt;
      if(DqUjFUTKXY == zRlRgkLZZI){xZHAexUfNM = true;}
      else if(zRlRgkLZZI == DqUjFUTKXY){dqgzVotgLh = true;}
      if(aFWMJtOhSb == yKuHVpnSIb){BnbqltnPBP = true;}
      else if(yKuHVpnSIb == aFWMJtOhSb){AMWCpjGpUB = true;}
      if(WyrgBGaIYR == iQbQcpoRhb){knEmodSkfI = true;}
      else if(iQbQcpoRhb == WyrgBGaIYR){wQkBAboViw = true;}
      if(exeKZoVdgo == xUcibKQElL){lukzzdsExy = true;}
      else if(xUcibKQElL == exeKZoVdgo){NhoNeSNcnu = true;}
      if(eFrEmZdXlF == GUiaWflmLF){aLeupgTYIV = true;}
      else if(GUiaWflmLF == eFrEmZdXlF){ecZIptBpFj = true;}
      if(UMDWZEyniz == fBciaioUnq){XMjzIJVTLA = true;}
      else if(fBciaioUnq == UMDWZEyniz){kVFSmMGeys = true;}
      if(sKlFtcZLlT == utrxLchLfK){dizFaGCbrI = true;}
      else if(utrxLchLfK == sKlFtcZLlT){zXyOTRXJXW = true;}
      if(XjAcwQGmsa == ZifwUOgAsx){AiSDnZIIxI = true;}
      if(cCWTxStIjU == EBFbuwqsHr){KtcJjZKlqp = true;}
      if(qguhuUTlKK == VuPuQMblPt){HYswTrLZTj = true;}
      while(ZifwUOgAsx == XjAcwQGmsa){WcBYVSpbLF = true;}
      while(EBFbuwqsHr == EBFbuwqsHr){ZyPzKrcVZR = true;}
      while(VuPuQMblPt == VuPuQMblPt){LietuHeLnX = true;}
      if(xZHAexUfNM == true){xZHAexUfNM = false;}
      if(BnbqltnPBP == true){BnbqltnPBP = false;}
      if(knEmodSkfI == true){knEmodSkfI = false;}
      if(lukzzdsExy == true){lukzzdsExy = false;}
      if(aLeupgTYIV == true){aLeupgTYIV = false;}
      if(XMjzIJVTLA == true){XMjzIJVTLA = false;}
      if(dizFaGCbrI == true){dizFaGCbrI = false;}
      if(AiSDnZIIxI == true){AiSDnZIIxI = false;}
      if(KtcJjZKlqp == true){KtcJjZKlqp = false;}
      if(HYswTrLZTj == true){HYswTrLZTj = false;}
      if(dqgzVotgLh == true){dqgzVotgLh = false;}
      if(AMWCpjGpUB == true){AMWCpjGpUB = false;}
      if(wQkBAboViw == true){wQkBAboViw = false;}
      if(NhoNeSNcnu == true){NhoNeSNcnu = false;}
      if(ecZIptBpFj == true){ecZIptBpFj = false;}
      if(kVFSmMGeys == true){kVFSmMGeys = false;}
      if(zXyOTRXJXW == true){zXyOTRXJXW = false;}
      if(WcBYVSpbLF == true){WcBYVSpbLF = false;}
      if(ZyPzKrcVZR == true){ZyPzKrcVZR = false;}
      if(LietuHeLnX == true){LietuHeLnX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLYCLRBVBL
{ 
  void zDRLdAjznX()
  { 
      bool lGlxRpjpDU = false;
      bool gdLxGrbXsM = false;
      bool sqwMeUSCUg = false;
      bool XHIrNlqyVn = false;
      bool UkaCbCNxDU = false;
      bool kHOoWtJYSx = false;
      bool WhVWxYVSjT = false;
      bool BdBErIPskc = false;
      bool GVyzwPrTUS = false;
      bool bRfYQlPEFC = false;
      bool ftMiTHFKwO = false;
      bool dQnopBiVag = false;
      bool gCyRqiybmF = false;
      bool rLnhwLIPfn = false;
      bool JhWFnLdpiP = false;
      bool DsdYVdwuqj = false;
      bool IdWpWSbFsd = false;
      bool rTplWyerce = false;
      bool FIsXCyhOMR = false;
      bool PNXuefLgiV = false;
      string GsFyFhcFRg;
      string HWzfpZXLwH;
      string pqhcZfhYFK;
      string mKmeZVRGPy;
      string OUyYOboWab;
      string WYIApPKcYY;
      string zEAGtwiTFT;
      string IQwysVrJNy;
      string qLydnNBmnJ;
      string KogqzKTqeS;
      string rUQGSFcKGT;
      string WBOahnFWRf;
      string twewISjEyi;
      string BBduFVtrKi;
      string kqfUmJZGJL;
      string ExYyXwoUxA;
      string VXLXRVWTUL;
      string sNMitDPKJz;
      string scumeEbeWI;
      string gYtKNNeICQ;
      if(GsFyFhcFRg == rUQGSFcKGT){lGlxRpjpDU = true;}
      else if(rUQGSFcKGT == GsFyFhcFRg){ftMiTHFKwO = true;}
      if(HWzfpZXLwH == WBOahnFWRf){gdLxGrbXsM = true;}
      else if(WBOahnFWRf == HWzfpZXLwH){dQnopBiVag = true;}
      if(pqhcZfhYFK == twewISjEyi){sqwMeUSCUg = true;}
      else if(twewISjEyi == pqhcZfhYFK){gCyRqiybmF = true;}
      if(mKmeZVRGPy == BBduFVtrKi){XHIrNlqyVn = true;}
      else if(BBduFVtrKi == mKmeZVRGPy){rLnhwLIPfn = true;}
      if(OUyYOboWab == kqfUmJZGJL){UkaCbCNxDU = true;}
      else if(kqfUmJZGJL == OUyYOboWab){JhWFnLdpiP = true;}
      if(WYIApPKcYY == ExYyXwoUxA){kHOoWtJYSx = true;}
      else if(ExYyXwoUxA == WYIApPKcYY){DsdYVdwuqj = true;}
      if(zEAGtwiTFT == VXLXRVWTUL){WhVWxYVSjT = true;}
      else if(VXLXRVWTUL == zEAGtwiTFT){IdWpWSbFsd = true;}
      if(IQwysVrJNy == sNMitDPKJz){BdBErIPskc = true;}
      if(qLydnNBmnJ == scumeEbeWI){GVyzwPrTUS = true;}
      if(KogqzKTqeS == gYtKNNeICQ){bRfYQlPEFC = true;}
      while(sNMitDPKJz == IQwysVrJNy){rTplWyerce = true;}
      while(scumeEbeWI == scumeEbeWI){FIsXCyhOMR = true;}
      while(gYtKNNeICQ == gYtKNNeICQ){PNXuefLgiV = true;}
      if(lGlxRpjpDU == true){lGlxRpjpDU = false;}
      if(gdLxGrbXsM == true){gdLxGrbXsM = false;}
      if(sqwMeUSCUg == true){sqwMeUSCUg = false;}
      if(XHIrNlqyVn == true){XHIrNlqyVn = false;}
      if(UkaCbCNxDU == true){UkaCbCNxDU = false;}
      if(kHOoWtJYSx == true){kHOoWtJYSx = false;}
      if(WhVWxYVSjT == true){WhVWxYVSjT = false;}
      if(BdBErIPskc == true){BdBErIPskc = false;}
      if(GVyzwPrTUS == true){GVyzwPrTUS = false;}
      if(bRfYQlPEFC == true){bRfYQlPEFC = false;}
      if(ftMiTHFKwO == true){ftMiTHFKwO = false;}
      if(dQnopBiVag == true){dQnopBiVag = false;}
      if(gCyRqiybmF == true){gCyRqiybmF = false;}
      if(rLnhwLIPfn == true){rLnhwLIPfn = false;}
      if(JhWFnLdpiP == true){JhWFnLdpiP = false;}
      if(DsdYVdwuqj == true){DsdYVdwuqj = false;}
      if(IdWpWSbFsd == true){IdWpWSbFsd = false;}
      if(rTplWyerce == true){rTplWyerce = false;}
      if(FIsXCyhOMR == true){FIsXCyhOMR = false;}
      if(PNXuefLgiV == true){PNXuefLgiV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CIIRLAXKWD
{ 
  void yOEOShFkeI()
  { 
      bool wSQZrugKSI = false;
      bool VGBUVeWkUD = false;
      bool KaSibhDzVK = false;
      bool RCQVokDThW = false;
      bool OPotbUZdmL = false;
      bool UuFWtVzhxJ = false;
      bool qgnHqSpffk = false;
      bool aDCxoukYGH = false;
      bool HYMKpVxsbS = false;
      bool kVVYfgagDI = false;
      bool etxCjRrHhy = false;
      bool jaapBRUdRU = false;
      bool VwENzFgdRH = false;
      bool TDUybNbKaX = false;
      bool doLchKteWN = false;
      bool MxOimipjDd = false;
      bool jNpaegFcNn = false;
      bool pKCtpfkaeo = false;
      bool LBHEuVnlKs = false;
      bool WqGwnQzjxB = false;
      string ZNDzFAylrW;
      string itAaVSnKaO;
      string FRsThjlLnb;
      string QNnViLErcg;
      string rirkPutlgi;
      string PUhYJITiQU;
      string OlyQFUFdqJ;
      string OugtVWZIEm;
      string pzdELuePMZ;
      string rUbIRGjbeu;
      string oPtXUTnnCl;
      string iLeddPIsEJ;
      string opRRRsTXcP;
      string mxcIxZEFjq;
      string HqMZpfoydC;
      string xpWUFzycGa;
      string APLmzkiVgE;
      string KCJMCxcqak;
      string EUsZRwZICx;
      string bbzJpqfZaF;
      if(ZNDzFAylrW == oPtXUTnnCl){wSQZrugKSI = true;}
      else if(oPtXUTnnCl == ZNDzFAylrW){etxCjRrHhy = true;}
      if(itAaVSnKaO == iLeddPIsEJ){VGBUVeWkUD = true;}
      else if(iLeddPIsEJ == itAaVSnKaO){jaapBRUdRU = true;}
      if(FRsThjlLnb == opRRRsTXcP){KaSibhDzVK = true;}
      else if(opRRRsTXcP == FRsThjlLnb){VwENzFgdRH = true;}
      if(QNnViLErcg == mxcIxZEFjq){RCQVokDThW = true;}
      else if(mxcIxZEFjq == QNnViLErcg){TDUybNbKaX = true;}
      if(rirkPutlgi == HqMZpfoydC){OPotbUZdmL = true;}
      else if(HqMZpfoydC == rirkPutlgi){doLchKteWN = true;}
      if(PUhYJITiQU == xpWUFzycGa){UuFWtVzhxJ = true;}
      else if(xpWUFzycGa == PUhYJITiQU){MxOimipjDd = true;}
      if(OlyQFUFdqJ == APLmzkiVgE){qgnHqSpffk = true;}
      else if(APLmzkiVgE == OlyQFUFdqJ){jNpaegFcNn = true;}
      if(OugtVWZIEm == KCJMCxcqak){aDCxoukYGH = true;}
      if(pzdELuePMZ == EUsZRwZICx){HYMKpVxsbS = true;}
      if(rUbIRGjbeu == bbzJpqfZaF){kVVYfgagDI = true;}
      while(KCJMCxcqak == OugtVWZIEm){pKCtpfkaeo = true;}
      while(EUsZRwZICx == EUsZRwZICx){LBHEuVnlKs = true;}
      while(bbzJpqfZaF == bbzJpqfZaF){WqGwnQzjxB = true;}
      if(wSQZrugKSI == true){wSQZrugKSI = false;}
      if(VGBUVeWkUD == true){VGBUVeWkUD = false;}
      if(KaSibhDzVK == true){KaSibhDzVK = false;}
      if(RCQVokDThW == true){RCQVokDThW = false;}
      if(OPotbUZdmL == true){OPotbUZdmL = false;}
      if(UuFWtVzhxJ == true){UuFWtVzhxJ = false;}
      if(qgnHqSpffk == true){qgnHqSpffk = false;}
      if(aDCxoukYGH == true){aDCxoukYGH = false;}
      if(HYMKpVxsbS == true){HYMKpVxsbS = false;}
      if(kVVYfgagDI == true){kVVYfgagDI = false;}
      if(etxCjRrHhy == true){etxCjRrHhy = false;}
      if(jaapBRUdRU == true){jaapBRUdRU = false;}
      if(VwENzFgdRH == true){VwENzFgdRH = false;}
      if(TDUybNbKaX == true){TDUybNbKaX = false;}
      if(doLchKteWN == true){doLchKteWN = false;}
      if(MxOimipjDd == true){MxOimipjDd = false;}
      if(jNpaegFcNn == true){jNpaegFcNn = false;}
      if(pKCtpfkaeo == true){pKCtpfkaeo = false;}
      if(LBHEuVnlKs == true){LBHEuVnlKs = false;}
      if(WqGwnQzjxB == true){WqGwnQzjxB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFUVVOMKDD
{ 
  void MuHceKAaYu()
  { 
      bool gCmtLcFwxS = false;
      bool eBPxsRnIFu = false;
      bool wfnnmXIjKj = false;
      bool zeFAuWiKEM = false;
      bool CnLBXnIKyE = false;
      bool xjzltAOyHm = false;
      bool UUlMTzuOCW = false;
      bool hdEsrIUmPy = false;
      bool OylFmOeSFt = false;
      bool IkCRrhCzgY = false;
      bool stIaWSfGsl = false;
      bool faiJXVhfYE = false;
      bool UcIHOwalAK = false;
      bool GVFqFUpLiT = false;
      bool iYYTOgCstV = false;
      bool zVZbDQkALZ = false;
      bool rsFifKVqDC = false;
      bool fVxFUwDosh = false;
      bool tgrdKjucmo = false;
      bool joAIbpSpnD = false;
      string VmoXGAJPXl;
      string wPoljiLjdV;
      string mrXxrIRIKg;
      string gWskzAtTcT;
      string saKauXQMFt;
      string geHJFdOqey;
      string hAEqEZVDmi;
      string nqHJcMhxBU;
      string qFDQACPieV;
      string lCodkrVTVV;
      string CMYVFpWxgs;
      string wQpKGcxnpC;
      string KlYRxlBcXk;
      string pNbfSdfgLJ;
      string fRCkZVMeXI;
      string thcTLPnHYT;
      string ntYwDhnJqc;
      string xQcfVrjmrb;
      string ZWFPpIkIUD;
      string oYHrVlsFhq;
      if(VmoXGAJPXl == CMYVFpWxgs){gCmtLcFwxS = true;}
      else if(CMYVFpWxgs == VmoXGAJPXl){stIaWSfGsl = true;}
      if(wPoljiLjdV == wQpKGcxnpC){eBPxsRnIFu = true;}
      else if(wQpKGcxnpC == wPoljiLjdV){faiJXVhfYE = true;}
      if(mrXxrIRIKg == KlYRxlBcXk){wfnnmXIjKj = true;}
      else if(KlYRxlBcXk == mrXxrIRIKg){UcIHOwalAK = true;}
      if(gWskzAtTcT == pNbfSdfgLJ){zeFAuWiKEM = true;}
      else if(pNbfSdfgLJ == gWskzAtTcT){GVFqFUpLiT = true;}
      if(saKauXQMFt == fRCkZVMeXI){CnLBXnIKyE = true;}
      else if(fRCkZVMeXI == saKauXQMFt){iYYTOgCstV = true;}
      if(geHJFdOqey == thcTLPnHYT){xjzltAOyHm = true;}
      else if(thcTLPnHYT == geHJFdOqey){zVZbDQkALZ = true;}
      if(hAEqEZVDmi == ntYwDhnJqc){UUlMTzuOCW = true;}
      else if(ntYwDhnJqc == hAEqEZVDmi){rsFifKVqDC = true;}
      if(nqHJcMhxBU == xQcfVrjmrb){hdEsrIUmPy = true;}
      if(qFDQACPieV == ZWFPpIkIUD){OylFmOeSFt = true;}
      if(lCodkrVTVV == oYHrVlsFhq){IkCRrhCzgY = true;}
      while(xQcfVrjmrb == nqHJcMhxBU){fVxFUwDosh = true;}
      while(ZWFPpIkIUD == ZWFPpIkIUD){tgrdKjucmo = true;}
      while(oYHrVlsFhq == oYHrVlsFhq){joAIbpSpnD = true;}
      if(gCmtLcFwxS == true){gCmtLcFwxS = false;}
      if(eBPxsRnIFu == true){eBPxsRnIFu = false;}
      if(wfnnmXIjKj == true){wfnnmXIjKj = false;}
      if(zeFAuWiKEM == true){zeFAuWiKEM = false;}
      if(CnLBXnIKyE == true){CnLBXnIKyE = false;}
      if(xjzltAOyHm == true){xjzltAOyHm = false;}
      if(UUlMTzuOCW == true){UUlMTzuOCW = false;}
      if(hdEsrIUmPy == true){hdEsrIUmPy = false;}
      if(OylFmOeSFt == true){OylFmOeSFt = false;}
      if(IkCRrhCzgY == true){IkCRrhCzgY = false;}
      if(stIaWSfGsl == true){stIaWSfGsl = false;}
      if(faiJXVhfYE == true){faiJXVhfYE = false;}
      if(UcIHOwalAK == true){UcIHOwalAK = false;}
      if(GVFqFUpLiT == true){GVFqFUpLiT = false;}
      if(iYYTOgCstV == true){iYYTOgCstV = false;}
      if(zVZbDQkALZ == true){zVZbDQkALZ = false;}
      if(rsFifKVqDC == true){rsFifKVqDC = false;}
      if(fVxFUwDosh == true){fVxFUwDosh = false;}
      if(tgrdKjucmo == true){tgrdKjucmo = false;}
      if(joAIbpSpnD == true){joAIbpSpnD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLSHZZFBSD
{ 
  void noLjKYZlJW()
  { 
      bool ItdpFOKKSZ = false;
      bool FwkdcduXux = false;
      bool ZFNoKxVsGm = false;
      bool FoaUoHXwwy = false;
      bool zQPEqedfmS = false;
      bool UZOOcCfnfI = false;
      bool rRDfTPUQoU = false;
      bool FyawxJpJxe = false;
      bool SpFnReaMql = false;
      bool biQnFhMjjb = false;
      bool KNqRMWzRRS = false;
      bool LWqAoCLONo = false;
      bool oIYCsWglqO = false;
      bool xGYVUFznbu = false;
      bool fJuYZFrQzC = false;
      bool VyVulBonXo = false;
      bool oMZCVFxUfj = false;
      bool DXmRJeMzcn = false;
      bool eQlnszjdiS = false;
      bool PKPlFSisDU = false;
      string HgXWERxTHj;
      string qjFpHWxQfS;
      string kjFMFETTEA;
      string kterSTxXaD;
      string skBYAdDIKr;
      string YnYslXaKRz;
      string xcOHzwFMWn;
      string ZZpbZAhfLb;
      string BKJMbwUlFt;
      string rlGaFPVsZE;
      string YplWRzxwSl;
      string puzoylTCfC;
      string aSGcunSPVJ;
      string dnGHCLYltb;
      string yXSTExlQcT;
      string wTNWcFiJbd;
      string fhaIHBorml;
      string NgIDDDzmXx;
      string BCmCNKaidx;
      string bPKPwQxJLD;
      if(HgXWERxTHj == YplWRzxwSl){ItdpFOKKSZ = true;}
      else if(YplWRzxwSl == HgXWERxTHj){KNqRMWzRRS = true;}
      if(qjFpHWxQfS == puzoylTCfC){FwkdcduXux = true;}
      else if(puzoylTCfC == qjFpHWxQfS){LWqAoCLONo = true;}
      if(kjFMFETTEA == aSGcunSPVJ){ZFNoKxVsGm = true;}
      else if(aSGcunSPVJ == kjFMFETTEA){oIYCsWglqO = true;}
      if(kterSTxXaD == dnGHCLYltb){FoaUoHXwwy = true;}
      else if(dnGHCLYltb == kterSTxXaD){xGYVUFznbu = true;}
      if(skBYAdDIKr == yXSTExlQcT){zQPEqedfmS = true;}
      else if(yXSTExlQcT == skBYAdDIKr){fJuYZFrQzC = true;}
      if(YnYslXaKRz == wTNWcFiJbd){UZOOcCfnfI = true;}
      else if(wTNWcFiJbd == YnYslXaKRz){VyVulBonXo = true;}
      if(xcOHzwFMWn == fhaIHBorml){rRDfTPUQoU = true;}
      else if(fhaIHBorml == xcOHzwFMWn){oMZCVFxUfj = true;}
      if(ZZpbZAhfLb == NgIDDDzmXx){FyawxJpJxe = true;}
      if(BKJMbwUlFt == BCmCNKaidx){SpFnReaMql = true;}
      if(rlGaFPVsZE == bPKPwQxJLD){biQnFhMjjb = true;}
      while(NgIDDDzmXx == ZZpbZAhfLb){DXmRJeMzcn = true;}
      while(BCmCNKaidx == BCmCNKaidx){eQlnszjdiS = true;}
      while(bPKPwQxJLD == bPKPwQxJLD){PKPlFSisDU = true;}
      if(ItdpFOKKSZ == true){ItdpFOKKSZ = false;}
      if(FwkdcduXux == true){FwkdcduXux = false;}
      if(ZFNoKxVsGm == true){ZFNoKxVsGm = false;}
      if(FoaUoHXwwy == true){FoaUoHXwwy = false;}
      if(zQPEqedfmS == true){zQPEqedfmS = false;}
      if(UZOOcCfnfI == true){UZOOcCfnfI = false;}
      if(rRDfTPUQoU == true){rRDfTPUQoU = false;}
      if(FyawxJpJxe == true){FyawxJpJxe = false;}
      if(SpFnReaMql == true){SpFnReaMql = false;}
      if(biQnFhMjjb == true){biQnFhMjjb = false;}
      if(KNqRMWzRRS == true){KNqRMWzRRS = false;}
      if(LWqAoCLONo == true){LWqAoCLONo = false;}
      if(oIYCsWglqO == true){oIYCsWglqO = false;}
      if(xGYVUFznbu == true){xGYVUFznbu = false;}
      if(fJuYZFrQzC == true){fJuYZFrQzC = false;}
      if(VyVulBonXo == true){VyVulBonXo = false;}
      if(oMZCVFxUfj == true){oMZCVFxUfj = false;}
      if(DXmRJeMzcn == true){DXmRJeMzcn = false;}
      if(eQlnszjdiS == true){eQlnszjdiS = false;}
      if(PKPlFSisDU == true){PKPlFSisDU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDGTAIHWBR
{ 
  void aCkGXsGnSf()
  { 
      bool FVZFAEuGZi = false;
      bool EzlfHUdRKG = false;
      bool UrOZCYPPgQ = false;
      bool OKFZIJXLFZ = false;
      bool VSfDVkfTns = false;
      bool GleGqNHADb = false;
      bool neZJTttMWx = false;
      bool xRLkkBLKDR = false;
      bool swanJceyhu = false;
      bool CXIdkpsWjb = false;
      bool pSwqwoatVo = false;
      bool CwwkirEkzq = false;
      bool OuebuZJgzt = false;
      bool IoabaZzirU = false;
      bool BkbssFbWus = false;
      bool kIWrMtnUwV = false;
      bool estbgNVTKI = false;
      bool sUseocTkio = false;
      bool yllFIARiOf = false;
      bool ldmVoIpAMf = false;
      string jBIrAozMFE;
      string nmooRQgqol;
      string AzZdxjycoz;
      string jtnDQNuBzP;
      string EZnfqhIpSN;
      string YxuVVjbetQ;
      string pWXFUsykYE;
      string UfrYgaLtmO;
      string aIJbalySgf;
      string kQGhZhChKx;
      string jXRNrrFWnu;
      string YgrfphMuei;
      string teEsSEYJyz;
      string XdioeDqujh;
      string gbekHEYarr;
      string UGDbCESXum;
      string TuXoXuyCAm;
      string qQLwCSASlO;
      string fyRGdQZGmZ;
      string jSAwOkDpNL;
      if(jBIrAozMFE == jXRNrrFWnu){FVZFAEuGZi = true;}
      else if(jXRNrrFWnu == jBIrAozMFE){pSwqwoatVo = true;}
      if(nmooRQgqol == YgrfphMuei){EzlfHUdRKG = true;}
      else if(YgrfphMuei == nmooRQgqol){CwwkirEkzq = true;}
      if(AzZdxjycoz == teEsSEYJyz){UrOZCYPPgQ = true;}
      else if(teEsSEYJyz == AzZdxjycoz){OuebuZJgzt = true;}
      if(jtnDQNuBzP == XdioeDqujh){OKFZIJXLFZ = true;}
      else if(XdioeDqujh == jtnDQNuBzP){IoabaZzirU = true;}
      if(EZnfqhIpSN == gbekHEYarr){VSfDVkfTns = true;}
      else if(gbekHEYarr == EZnfqhIpSN){BkbssFbWus = true;}
      if(YxuVVjbetQ == UGDbCESXum){GleGqNHADb = true;}
      else if(UGDbCESXum == YxuVVjbetQ){kIWrMtnUwV = true;}
      if(pWXFUsykYE == TuXoXuyCAm){neZJTttMWx = true;}
      else if(TuXoXuyCAm == pWXFUsykYE){estbgNVTKI = true;}
      if(UfrYgaLtmO == qQLwCSASlO){xRLkkBLKDR = true;}
      if(aIJbalySgf == fyRGdQZGmZ){swanJceyhu = true;}
      if(kQGhZhChKx == jSAwOkDpNL){CXIdkpsWjb = true;}
      while(qQLwCSASlO == UfrYgaLtmO){sUseocTkio = true;}
      while(fyRGdQZGmZ == fyRGdQZGmZ){yllFIARiOf = true;}
      while(jSAwOkDpNL == jSAwOkDpNL){ldmVoIpAMf = true;}
      if(FVZFAEuGZi == true){FVZFAEuGZi = false;}
      if(EzlfHUdRKG == true){EzlfHUdRKG = false;}
      if(UrOZCYPPgQ == true){UrOZCYPPgQ = false;}
      if(OKFZIJXLFZ == true){OKFZIJXLFZ = false;}
      if(VSfDVkfTns == true){VSfDVkfTns = false;}
      if(GleGqNHADb == true){GleGqNHADb = false;}
      if(neZJTttMWx == true){neZJTttMWx = false;}
      if(xRLkkBLKDR == true){xRLkkBLKDR = false;}
      if(swanJceyhu == true){swanJceyhu = false;}
      if(CXIdkpsWjb == true){CXIdkpsWjb = false;}
      if(pSwqwoatVo == true){pSwqwoatVo = false;}
      if(CwwkirEkzq == true){CwwkirEkzq = false;}
      if(OuebuZJgzt == true){OuebuZJgzt = false;}
      if(IoabaZzirU == true){IoabaZzirU = false;}
      if(BkbssFbWus == true){BkbssFbWus = false;}
      if(kIWrMtnUwV == true){kIWrMtnUwV = false;}
      if(estbgNVTKI == true){estbgNVTKI = false;}
      if(sUseocTkio == true){sUseocTkio = false;}
      if(yllFIARiOf == true){yllFIARiOf = false;}
      if(ldmVoIpAMf == true){ldmVoIpAMf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDJADGKGXX
{ 
  void KjVtSLLPYx()
  { 
      bool SWzJiNMkUR = false;
      bool SCesIaBRRx = false;
      bool DaiPOryYaD = false;
      bool dwlZaoySwF = false;
      bool rAdeCGBRbb = false;
      bool cGKPurmitp = false;
      bool PmJQnWQERS = false;
      bool chULFDwDNI = false;
      bool qgxzZWkVei = false;
      bool CPXFpEpNqe = false;
      bool owzIztkyKq = false;
      bool uiUlzhpKpQ = false;
      bool ktZiQNKPVA = false;
      bool MhMhStgoAe = false;
      bool klKmnStkFH = false;
      bool OfWZsuWQrl = false;
      bool jVcKeMWmTF = false;
      bool BBKKfzjlux = false;
      bool SYKNkgLlnX = false;
      bool WQwNuPIAIa = false;
      string trqFcXpsyr;
      string iXEhyaBHqi;
      string EgWiJNKIoJ;
      string HDqpqpJhfh;
      string MpKcYNhHiA;
      string aNuztMVIwP;
      string NgDojffNpI;
      string QTaJVOWtJu;
      string fCZoitHrwd;
      string UBkQUelVrr;
      string gTQajGllce;
      string pbyAiKHOFp;
      string XnQMmOhJoq;
      string bBBROLkyEb;
      string HVOQmsDkgJ;
      string WWPCTrCEmU;
      string YcxlDoZglX;
      string ZJJdhCZAYt;
      string LxbfTFkzxV;
      string IgKjCdYcNy;
      if(trqFcXpsyr == gTQajGllce){SWzJiNMkUR = true;}
      else if(gTQajGllce == trqFcXpsyr){owzIztkyKq = true;}
      if(iXEhyaBHqi == pbyAiKHOFp){SCesIaBRRx = true;}
      else if(pbyAiKHOFp == iXEhyaBHqi){uiUlzhpKpQ = true;}
      if(EgWiJNKIoJ == XnQMmOhJoq){DaiPOryYaD = true;}
      else if(XnQMmOhJoq == EgWiJNKIoJ){ktZiQNKPVA = true;}
      if(HDqpqpJhfh == bBBROLkyEb){dwlZaoySwF = true;}
      else if(bBBROLkyEb == HDqpqpJhfh){MhMhStgoAe = true;}
      if(MpKcYNhHiA == HVOQmsDkgJ){rAdeCGBRbb = true;}
      else if(HVOQmsDkgJ == MpKcYNhHiA){klKmnStkFH = true;}
      if(aNuztMVIwP == WWPCTrCEmU){cGKPurmitp = true;}
      else if(WWPCTrCEmU == aNuztMVIwP){OfWZsuWQrl = true;}
      if(NgDojffNpI == YcxlDoZglX){PmJQnWQERS = true;}
      else if(YcxlDoZglX == NgDojffNpI){jVcKeMWmTF = true;}
      if(QTaJVOWtJu == ZJJdhCZAYt){chULFDwDNI = true;}
      if(fCZoitHrwd == LxbfTFkzxV){qgxzZWkVei = true;}
      if(UBkQUelVrr == IgKjCdYcNy){CPXFpEpNqe = true;}
      while(ZJJdhCZAYt == QTaJVOWtJu){BBKKfzjlux = true;}
      while(LxbfTFkzxV == LxbfTFkzxV){SYKNkgLlnX = true;}
      while(IgKjCdYcNy == IgKjCdYcNy){WQwNuPIAIa = true;}
      if(SWzJiNMkUR == true){SWzJiNMkUR = false;}
      if(SCesIaBRRx == true){SCesIaBRRx = false;}
      if(DaiPOryYaD == true){DaiPOryYaD = false;}
      if(dwlZaoySwF == true){dwlZaoySwF = false;}
      if(rAdeCGBRbb == true){rAdeCGBRbb = false;}
      if(cGKPurmitp == true){cGKPurmitp = false;}
      if(PmJQnWQERS == true){PmJQnWQERS = false;}
      if(chULFDwDNI == true){chULFDwDNI = false;}
      if(qgxzZWkVei == true){qgxzZWkVei = false;}
      if(CPXFpEpNqe == true){CPXFpEpNqe = false;}
      if(owzIztkyKq == true){owzIztkyKq = false;}
      if(uiUlzhpKpQ == true){uiUlzhpKpQ = false;}
      if(ktZiQNKPVA == true){ktZiQNKPVA = false;}
      if(MhMhStgoAe == true){MhMhStgoAe = false;}
      if(klKmnStkFH == true){klKmnStkFH = false;}
      if(OfWZsuWQrl == true){OfWZsuWQrl = false;}
      if(jVcKeMWmTF == true){jVcKeMWmTF = false;}
      if(BBKKfzjlux == true){BBKKfzjlux = false;}
      if(SYKNkgLlnX == true){SYKNkgLlnX = false;}
      if(WQwNuPIAIa == true){WQwNuPIAIa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUZRQRPKLC
{ 
  void OCigTAnHJF()
  { 
      bool ArlXJuIuaW = false;
      bool PKRUpHRnUB = false;
      bool uUaSdNDjmM = false;
      bool skhFgOnIXx = false;
      bool kEwKgXBwQu = false;
      bool UlqWFeQSsu = false;
      bool qXINcdcLma = false;
      bool SIQWPqYQlF = false;
      bool MGTqqGsKAC = false;
      bool xUOcFMwhgC = false;
      bool uoJobLVUGO = false;
      bool FAgmhjEQWW = false;
      bool kRLkcysnQC = false;
      bool tqiiKXxdPe = false;
      bool jYDkwxmbtU = false;
      bool IfLJRccYMd = false;
      bool RhDDTOQycK = false;
      bool mZBqlLNaof = false;
      bool KRswtOfZRg = false;
      bool tYRkNCVzQg = false;
      string IuGPgjYKVG;
      string fucxqgrUzD;
      string ncxuxZmlFB;
      string ZXcpLgrrFM;
      string qzepPCfQnu;
      string IcghefxLSH;
      string wlETgIRmkK;
      string oAOmMoxHet;
      string sWxJsxpuLf;
      string ifYyPEtLJH;
      string ksedGINsUp;
      string hpfYNYntZi;
      string RWbFaIaQXH;
      string tlxXJArTDj;
      string jxZUxsAAjp;
      string PzkZpNRYCx;
      string hxVMwwrIOM;
      string gUqpzTxGHh;
      string HZfgrtAWgw;
      string iSQGClaMYB;
      if(IuGPgjYKVG == ksedGINsUp){ArlXJuIuaW = true;}
      else if(ksedGINsUp == IuGPgjYKVG){uoJobLVUGO = true;}
      if(fucxqgrUzD == hpfYNYntZi){PKRUpHRnUB = true;}
      else if(hpfYNYntZi == fucxqgrUzD){FAgmhjEQWW = true;}
      if(ncxuxZmlFB == RWbFaIaQXH){uUaSdNDjmM = true;}
      else if(RWbFaIaQXH == ncxuxZmlFB){kRLkcysnQC = true;}
      if(ZXcpLgrrFM == tlxXJArTDj){skhFgOnIXx = true;}
      else if(tlxXJArTDj == ZXcpLgrrFM){tqiiKXxdPe = true;}
      if(qzepPCfQnu == jxZUxsAAjp){kEwKgXBwQu = true;}
      else if(jxZUxsAAjp == qzepPCfQnu){jYDkwxmbtU = true;}
      if(IcghefxLSH == PzkZpNRYCx){UlqWFeQSsu = true;}
      else if(PzkZpNRYCx == IcghefxLSH){IfLJRccYMd = true;}
      if(wlETgIRmkK == hxVMwwrIOM){qXINcdcLma = true;}
      else if(hxVMwwrIOM == wlETgIRmkK){RhDDTOQycK = true;}
      if(oAOmMoxHet == gUqpzTxGHh){SIQWPqYQlF = true;}
      if(sWxJsxpuLf == HZfgrtAWgw){MGTqqGsKAC = true;}
      if(ifYyPEtLJH == iSQGClaMYB){xUOcFMwhgC = true;}
      while(gUqpzTxGHh == oAOmMoxHet){mZBqlLNaof = true;}
      while(HZfgrtAWgw == HZfgrtAWgw){KRswtOfZRg = true;}
      while(iSQGClaMYB == iSQGClaMYB){tYRkNCVzQg = true;}
      if(ArlXJuIuaW == true){ArlXJuIuaW = false;}
      if(PKRUpHRnUB == true){PKRUpHRnUB = false;}
      if(uUaSdNDjmM == true){uUaSdNDjmM = false;}
      if(skhFgOnIXx == true){skhFgOnIXx = false;}
      if(kEwKgXBwQu == true){kEwKgXBwQu = false;}
      if(UlqWFeQSsu == true){UlqWFeQSsu = false;}
      if(qXINcdcLma == true){qXINcdcLma = false;}
      if(SIQWPqYQlF == true){SIQWPqYQlF = false;}
      if(MGTqqGsKAC == true){MGTqqGsKAC = false;}
      if(xUOcFMwhgC == true){xUOcFMwhgC = false;}
      if(uoJobLVUGO == true){uoJobLVUGO = false;}
      if(FAgmhjEQWW == true){FAgmhjEQWW = false;}
      if(kRLkcysnQC == true){kRLkcysnQC = false;}
      if(tqiiKXxdPe == true){tqiiKXxdPe = false;}
      if(jYDkwxmbtU == true){jYDkwxmbtU = false;}
      if(IfLJRccYMd == true){IfLJRccYMd = false;}
      if(RhDDTOQycK == true){RhDDTOQycK = false;}
      if(mZBqlLNaof == true){mZBqlLNaof = false;}
      if(KRswtOfZRg == true){KRswtOfZRg = false;}
      if(tYRkNCVzQg == true){tYRkNCVzQg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHCKXVFULK
{ 
  void dSZBsruoSt()
  { 
      bool pnVogSPJBt = false;
      bool aOBjOAocnM = false;
      bool NoGHBwgwBw = false;
      bool tUTQcwsZEH = false;
      bool PMSJqNaosW = false;
      bool eXLnNAgOnk = false;
      bool kTIEAFtjGR = false;
      bool GPYfxBWxQm = false;
      bool UrDdRVJeDc = false;
      bool OelTWwENIk = false;
      bool TphaQOzeqM = false;
      bool dixAPrQdmd = false;
      bool wOgdCbdEJB = false;
      bool wIofTeJbNC = false;
      bool VdnqyfgkEd = false;
      bool faZenEJEXn = false;
      bool kuUoPUtRfj = false;
      bool hnQjHSapeW = false;
      bool urzfVViJqP = false;
      bool UFDYRaIzad = false;
      string DrpcVmQQNf;
      string FIUsDxVzFs;
      string QQAlqTXjOn;
      string hUuPmnIXKO;
      string miTFntGDlX;
      string ZYxSalqDlC;
      string OgCZyjMFFP;
      string nxnqFhxuyw;
      string NUypOIWbnA;
      string wElHzGgsHD;
      string gAyWibjGNs;
      string owFoothLLo;
      string MjQESjLgqy;
      string AEmtPMVbHm;
      string XQOtLzzwRF;
      string YUhSpxjsDz;
      string PDOOsjJKZc;
      string XGEYQwVVrT;
      string kPOlZfVTDR;
      string bbYHWTBABb;
      if(DrpcVmQQNf == gAyWibjGNs){pnVogSPJBt = true;}
      else if(gAyWibjGNs == DrpcVmQQNf){TphaQOzeqM = true;}
      if(FIUsDxVzFs == owFoothLLo){aOBjOAocnM = true;}
      else if(owFoothLLo == FIUsDxVzFs){dixAPrQdmd = true;}
      if(QQAlqTXjOn == MjQESjLgqy){NoGHBwgwBw = true;}
      else if(MjQESjLgqy == QQAlqTXjOn){wOgdCbdEJB = true;}
      if(hUuPmnIXKO == AEmtPMVbHm){tUTQcwsZEH = true;}
      else if(AEmtPMVbHm == hUuPmnIXKO){wIofTeJbNC = true;}
      if(miTFntGDlX == XQOtLzzwRF){PMSJqNaosW = true;}
      else if(XQOtLzzwRF == miTFntGDlX){VdnqyfgkEd = true;}
      if(ZYxSalqDlC == YUhSpxjsDz){eXLnNAgOnk = true;}
      else if(YUhSpxjsDz == ZYxSalqDlC){faZenEJEXn = true;}
      if(OgCZyjMFFP == PDOOsjJKZc){kTIEAFtjGR = true;}
      else if(PDOOsjJKZc == OgCZyjMFFP){kuUoPUtRfj = true;}
      if(nxnqFhxuyw == XGEYQwVVrT){GPYfxBWxQm = true;}
      if(NUypOIWbnA == kPOlZfVTDR){UrDdRVJeDc = true;}
      if(wElHzGgsHD == bbYHWTBABb){OelTWwENIk = true;}
      while(XGEYQwVVrT == nxnqFhxuyw){hnQjHSapeW = true;}
      while(kPOlZfVTDR == kPOlZfVTDR){urzfVViJqP = true;}
      while(bbYHWTBABb == bbYHWTBABb){UFDYRaIzad = true;}
      if(pnVogSPJBt == true){pnVogSPJBt = false;}
      if(aOBjOAocnM == true){aOBjOAocnM = false;}
      if(NoGHBwgwBw == true){NoGHBwgwBw = false;}
      if(tUTQcwsZEH == true){tUTQcwsZEH = false;}
      if(PMSJqNaosW == true){PMSJqNaosW = false;}
      if(eXLnNAgOnk == true){eXLnNAgOnk = false;}
      if(kTIEAFtjGR == true){kTIEAFtjGR = false;}
      if(GPYfxBWxQm == true){GPYfxBWxQm = false;}
      if(UrDdRVJeDc == true){UrDdRVJeDc = false;}
      if(OelTWwENIk == true){OelTWwENIk = false;}
      if(TphaQOzeqM == true){TphaQOzeqM = false;}
      if(dixAPrQdmd == true){dixAPrQdmd = false;}
      if(wOgdCbdEJB == true){wOgdCbdEJB = false;}
      if(wIofTeJbNC == true){wIofTeJbNC = false;}
      if(VdnqyfgkEd == true){VdnqyfgkEd = false;}
      if(faZenEJEXn == true){faZenEJEXn = false;}
      if(kuUoPUtRfj == true){kuUoPUtRfj = false;}
      if(hnQjHSapeW == true){hnQjHSapeW = false;}
      if(urzfVViJqP == true){urzfVViJqP = false;}
      if(UFDYRaIzad == true){UFDYRaIzad = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMWANXJKLX
{ 
  void BwZRfojSxN()
  { 
      bool IrOrNCUJtb = false;
      bool zjXFezKDlr = false;
      bool kRJmeWiEil = false;
      bool pxDSmxYyhJ = false;
      bool lQUmVVHljY = false;
      bool ZzyxRqiaNq = false;
      bool TQaIlBfESg = false;
      bool aMVbFTwVQI = false;
      bool OwTJMpzFAu = false;
      bool OxjqpVoMBU = false;
      bool oCSCyMdVqy = false;
      bool tNJEbWwRuu = false;
      bool BaEWScbdkj = false;
      bool djTwSMcRLz = false;
      bool McNCBAmfPT = false;
      bool ZXQFSOywjU = false;
      bool kzjHTJsNlO = false;
      bool seFwiYMBVR = false;
      bool owORKGTOcD = false;
      bool NghqONrGiq = false;
      string bHoNjUNngy;
      string jpfFKUxXbn;
      string ssocuWmKXD;
      string maAOBVlCJY;
      string AHOjaqcicK;
      string shNbfhRLRN;
      string gCQdLJpQDo;
      string huOCmldECE;
      string tEhMJEMXiS;
      string DajwrxqkXR;
      string ALencyTKns;
      string ENJMSbUDTH;
      string wShklHKSKo;
      string trfkDiZtjL;
      string kCioOpQXcP;
      string cnRQUhctBU;
      string mAzyzLgYIj;
      string CaSHWsisVw;
      string pmpuMGaPPV;
      string FfrOYjDkpC;
      if(bHoNjUNngy == ALencyTKns){IrOrNCUJtb = true;}
      else if(ALencyTKns == bHoNjUNngy){oCSCyMdVqy = true;}
      if(jpfFKUxXbn == ENJMSbUDTH){zjXFezKDlr = true;}
      else if(ENJMSbUDTH == jpfFKUxXbn){tNJEbWwRuu = true;}
      if(ssocuWmKXD == wShklHKSKo){kRJmeWiEil = true;}
      else if(wShklHKSKo == ssocuWmKXD){BaEWScbdkj = true;}
      if(maAOBVlCJY == trfkDiZtjL){pxDSmxYyhJ = true;}
      else if(trfkDiZtjL == maAOBVlCJY){djTwSMcRLz = true;}
      if(AHOjaqcicK == kCioOpQXcP){lQUmVVHljY = true;}
      else if(kCioOpQXcP == AHOjaqcicK){McNCBAmfPT = true;}
      if(shNbfhRLRN == cnRQUhctBU){ZzyxRqiaNq = true;}
      else if(cnRQUhctBU == shNbfhRLRN){ZXQFSOywjU = true;}
      if(gCQdLJpQDo == mAzyzLgYIj){TQaIlBfESg = true;}
      else if(mAzyzLgYIj == gCQdLJpQDo){kzjHTJsNlO = true;}
      if(huOCmldECE == CaSHWsisVw){aMVbFTwVQI = true;}
      if(tEhMJEMXiS == pmpuMGaPPV){OwTJMpzFAu = true;}
      if(DajwrxqkXR == FfrOYjDkpC){OxjqpVoMBU = true;}
      while(CaSHWsisVw == huOCmldECE){seFwiYMBVR = true;}
      while(pmpuMGaPPV == pmpuMGaPPV){owORKGTOcD = true;}
      while(FfrOYjDkpC == FfrOYjDkpC){NghqONrGiq = true;}
      if(IrOrNCUJtb == true){IrOrNCUJtb = false;}
      if(zjXFezKDlr == true){zjXFezKDlr = false;}
      if(kRJmeWiEil == true){kRJmeWiEil = false;}
      if(pxDSmxYyhJ == true){pxDSmxYyhJ = false;}
      if(lQUmVVHljY == true){lQUmVVHljY = false;}
      if(ZzyxRqiaNq == true){ZzyxRqiaNq = false;}
      if(TQaIlBfESg == true){TQaIlBfESg = false;}
      if(aMVbFTwVQI == true){aMVbFTwVQI = false;}
      if(OwTJMpzFAu == true){OwTJMpzFAu = false;}
      if(OxjqpVoMBU == true){OxjqpVoMBU = false;}
      if(oCSCyMdVqy == true){oCSCyMdVqy = false;}
      if(tNJEbWwRuu == true){tNJEbWwRuu = false;}
      if(BaEWScbdkj == true){BaEWScbdkj = false;}
      if(djTwSMcRLz == true){djTwSMcRLz = false;}
      if(McNCBAmfPT == true){McNCBAmfPT = false;}
      if(ZXQFSOywjU == true){ZXQFSOywjU = false;}
      if(kzjHTJsNlO == true){kzjHTJsNlO = false;}
      if(seFwiYMBVR == true){seFwiYMBVR = false;}
      if(owORKGTOcD == true){owORKGTOcD = false;}
      if(NghqONrGiq == true){NghqONrGiq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZSXPCAACJ
{ 
  void BghUVnFXpG()
  { 
      bool mnigpcEObm = false;
      bool hGpjooYupw = false;
      bool PWZHeQMQbT = false;
      bool BsgnQcDSXS = false;
      bool THFkVXnkop = false;
      bool yaWrTQNbBY = false;
      bool QnlHkoZBSM = false;
      bool kFXWbIRnkH = false;
      bool caalVaWoTA = false;
      bool ObRyCfUxzg = false;
      bool ymScEsCzPL = false;
      bool zZptwpMAlJ = false;
      bool RkgSyJnYTw = false;
      bool mTnEIpHygb = false;
      bool YWYIAnkWCM = false;
      bool SUKpONFzet = false;
      bool EceTYeklkG = false;
      bool hOSJkuLYRJ = false;
      bool XQWHcRIypu = false;
      bool jISlXuqFiU = false;
      string pzqXcAUEep;
      string RqeASeXqqC;
      string MkdHfyIfdC;
      string jYtzEUFqnR;
      string sHLQIqkFii;
      string nUjCyEUire;
      string qoabFsxeux;
      string ZfCZJFZNzn;
      string MCwtOPoqBA;
      string AVzJZDgiKP;
      string tFJlJIRJrs;
      string dHiERnrfNp;
      string DFduxDgrAG;
      string YqCjsHsKkG;
      string xfzIWrmtrl;
      string KAUULobOoF;
      string aZJlUlEyLK;
      string uhuGrXGUYE;
      string QlANuXVhYE;
      string edVeeXVMnj;
      if(pzqXcAUEep == tFJlJIRJrs){mnigpcEObm = true;}
      else if(tFJlJIRJrs == pzqXcAUEep){ymScEsCzPL = true;}
      if(RqeASeXqqC == dHiERnrfNp){hGpjooYupw = true;}
      else if(dHiERnrfNp == RqeASeXqqC){zZptwpMAlJ = true;}
      if(MkdHfyIfdC == DFduxDgrAG){PWZHeQMQbT = true;}
      else if(DFduxDgrAG == MkdHfyIfdC){RkgSyJnYTw = true;}
      if(jYtzEUFqnR == YqCjsHsKkG){BsgnQcDSXS = true;}
      else if(YqCjsHsKkG == jYtzEUFqnR){mTnEIpHygb = true;}
      if(sHLQIqkFii == xfzIWrmtrl){THFkVXnkop = true;}
      else if(xfzIWrmtrl == sHLQIqkFii){YWYIAnkWCM = true;}
      if(nUjCyEUire == KAUULobOoF){yaWrTQNbBY = true;}
      else if(KAUULobOoF == nUjCyEUire){SUKpONFzet = true;}
      if(qoabFsxeux == aZJlUlEyLK){QnlHkoZBSM = true;}
      else if(aZJlUlEyLK == qoabFsxeux){EceTYeklkG = true;}
      if(ZfCZJFZNzn == uhuGrXGUYE){kFXWbIRnkH = true;}
      if(MCwtOPoqBA == QlANuXVhYE){caalVaWoTA = true;}
      if(AVzJZDgiKP == edVeeXVMnj){ObRyCfUxzg = true;}
      while(uhuGrXGUYE == ZfCZJFZNzn){hOSJkuLYRJ = true;}
      while(QlANuXVhYE == QlANuXVhYE){XQWHcRIypu = true;}
      while(edVeeXVMnj == edVeeXVMnj){jISlXuqFiU = true;}
      if(mnigpcEObm == true){mnigpcEObm = false;}
      if(hGpjooYupw == true){hGpjooYupw = false;}
      if(PWZHeQMQbT == true){PWZHeQMQbT = false;}
      if(BsgnQcDSXS == true){BsgnQcDSXS = false;}
      if(THFkVXnkop == true){THFkVXnkop = false;}
      if(yaWrTQNbBY == true){yaWrTQNbBY = false;}
      if(QnlHkoZBSM == true){QnlHkoZBSM = false;}
      if(kFXWbIRnkH == true){kFXWbIRnkH = false;}
      if(caalVaWoTA == true){caalVaWoTA = false;}
      if(ObRyCfUxzg == true){ObRyCfUxzg = false;}
      if(ymScEsCzPL == true){ymScEsCzPL = false;}
      if(zZptwpMAlJ == true){zZptwpMAlJ = false;}
      if(RkgSyJnYTw == true){RkgSyJnYTw = false;}
      if(mTnEIpHygb == true){mTnEIpHygb = false;}
      if(YWYIAnkWCM == true){YWYIAnkWCM = false;}
      if(SUKpONFzet == true){SUKpONFzet = false;}
      if(EceTYeklkG == true){EceTYeklkG = false;}
      if(hOSJkuLYRJ == true){hOSJkuLYRJ = false;}
      if(XQWHcRIypu == true){XQWHcRIypu = false;}
      if(jISlXuqFiU == true){jISlXuqFiU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKNDGZFDHN
{ 
  void PxqtysiEGB()
  { 
      bool wdeaBZzLLH = false;
      bool hkIeIwMhon = false;
      bool EqwZdNHgqE = false;
      bool edPYnqLteI = false;
      bool UegtNuiOte = false;
      bool VXyiIFhFxm = false;
      bool SSUHbDUiqQ = false;
      bool kSCfSZJBLh = false;
      bool eslMhHegQh = false;
      bool JGxqpCJZSK = false;
      bool ZzWdtDVSPh = false;
      bool wfsOIYfIYU = false;
      bool XnSIGdVKoP = false;
      bool QiiBHfVHRe = false;
      bool kMRhldMhiR = false;
      bool WBBxllgOWP = false;
      bool gKczRMxqHb = false;
      bool DXpsiLWjWc = false;
      bool RnbXsPhkPV = false;
      bool yHjCxajRQZ = false;
      string NqbdFRzhEb;
      string AITtJnTXMm;
      string ePRhkttyIe;
      string MSfJXiRKNX;
      string oZjUjIzOHz;
      string mCriRxZssK;
      string XBZYPhcJWa;
      string WIKnyEfxyb;
      string tepJrJZxrZ;
      string JXRCzmAKEB;
      string fprgbdqDjM;
      string QbuQPrLQfF;
      string HfRwQyqInL;
      string EUrwuEmJgN;
      string SVMeJgcAlH;
      string bidzsAXuPd;
      string miPYIujyVK;
      string FBjSmlSlmj;
      string VpVgiUpsCu;
      string gqtCaiGnWN;
      if(NqbdFRzhEb == fprgbdqDjM){wdeaBZzLLH = true;}
      else if(fprgbdqDjM == NqbdFRzhEb){ZzWdtDVSPh = true;}
      if(AITtJnTXMm == QbuQPrLQfF){hkIeIwMhon = true;}
      else if(QbuQPrLQfF == AITtJnTXMm){wfsOIYfIYU = true;}
      if(ePRhkttyIe == HfRwQyqInL){EqwZdNHgqE = true;}
      else if(HfRwQyqInL == ePRhkttyIe){XnSIGdVKoP = true;}
      if(MSfJXiRKNX == EUrwuEmJgN){edPYnqLteI = true;}
      else if(EUrwuEmJgN == MSfJXiRKNX){QiiBHfVHRe = true;}
      if(oZjUjIzOHz == SVMeJgcAlH){UegtNuiOte = true;}
      else if(SVMeJgcAlH == oZjUjIzOHz){kMRhldMhiR = true;}
      if(mCriRxZssK == bidzsAXuPd){VXyiIFhFxm = true;}
      else if(bidzsAXuPd == mCriRxZssK){WBBxllgOWP = true;}
      if(XBZYPhcJWa == miPYIujyVK){SSUHbDUiqQ = true;}
      else if(miPYIujyVK == XBZYPhcJWa){gKczRMxqHb = true;}
      if(WIKnyEfxyb == FBjSmlSlmj){kSCfSZJBLh = true;}
      if(tepJrJZxrZ == VpVgiUpsCu){eslMhHegQh = true;}
      if(JXRCzmAKEB == gqtCaiGnWN){JGxqpCJZSK = true;}
      while(FBjSmlSlmj == WIKnyEfxyb){DXpsiLWjWc = true;}
      while(VpVgiUpsCu == VpVgiUpsCu){RnbXsPhkPV = true;}
      while(gqtCaiGnWN == gqtCaiGnWN){yHjCxajRQZ = true;}
      if(wdeaBZzLLH == true){wdeaBZzLLH = false;}
      if(hkIeIwMhon == true){hkIeIwMhon = false;}
      if(EqwZdNHgqE == true){EqwZdNHgqE = false;}
      if(edPYnqLteI == true){edPYnqLteI = false;}
      if(UegtNuiOte == true){UegtNuiOte = false;}
      if(VXyiIFhFxm == true){VXyiIFhFxm = false;}
      if(SSUHbDUiqQ == true){SSUHbDUiqQ = false;}
      if(kSCfSZJBLh == true){kSCfSZJBLh = false;}
      if(eslMhHegQh == true){eslMhHegQh = false;}
      if(JGxqpCJZSK == true){JGxqpCJZSK = false;}
      if(ZzWdtDVSPh == true){ZzWdtDVSPh = false;}
      if(wfsOIYfIYU == true){wfsOIYfIYU = false;}
      if(XnSIGdVKoP == true){XnSIGdVKoP = false;}
      if(QiiBHfVHRe == true){QiiBHfVHRe = false;}
      if(kMRhldMhiR == true){kMRhldMhiR = false;}
      if(WBBxllgOWP == true){WBBxllgOWP = false;}
      if(gKczRMxqHb == true){gKczRMxqHb = false;}
      if(DXpsiLWjWc == true){DXpsiLWjWc = false;}
      if(RnbXsPhkPV == true){RnbXsPhkPV = false;}
      if(yHjCxajRQZ == true){yHjCxajRQZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDPYWBXBVB
{ 
  void rOJiOMGoIb()
  { 
      bool ENJTXgMoFh = false;
      bool PrlnmAreHB = false;
      bool IaqEkrReZe = false;
      bool PHwnRAbHiC = false;
      bool dIJGGhFVAd = false;
      bool aaOpPdWFhf = false;
      bool PhPaRHwyWm = false;
      bool YkuFWzQjxC = false;
      bool muduDosGXn = false;
      bool cVYDlwshny = false;
      bool lHzNFpfJSQ = false;
      bool MmHfrUETWc = false;
      bool OpZhJCLrSa = false;
      bool GiuzQeuPpN = false;
      bool JimHapOsKR = false;
      bool qYLLiuhQDC = false;
      bool emprJdrHON = false;
      bool YncITfDSHT = false;
      bool mRgBihWiPU = false;
      bool xdMmiVrtxw = false;
      string HUbdOJwzOz;
      string JdEFpkUiyL;
      string NECohkyxoZ;
      string yAmfhVHXbw;
      string IABrbdbPxn;
      string DhFneCSmuc;
      string KzKoBJqYXU;
      string cxGCDNDJMD;
      string JizBVPuyBe;
      string DUbzkJoLpS;
      string mDqcKGbDkQ;
      string yIZqSbzJSl;
      string NrWrRIUHQs;
      string XqStQGqWpP;
      string nrNjfttjfJ;
      string JfsEEtfzLB;
      string kTlqsHofaM;
      string kcSDyVdmMW;
      string OkbHjqyOoW;
      string arKndTFWqY;
      if(HUbdOJwzOz == mDqcKGbDkQ){ENJTXgMoFh = true;}
      else if(mDqcKGbDkQ == HUbdOJwzOz){lHzNFpfJSQ = true;}
      if(JdEFpkUiyL == yIZqSbzJSl){PrlnmAreHB = true;}
      else if(yIZqSbzJSl == JdEFpkUiyL){MmHfrUETWc = true;}
      if(NECohkyxoZ == NrWrRIUHQs){IaqEkrReZe = true;}
      else if(NrWrRIUHQs == NECohkyxoZ){OpZhJCLrSa = true;}
      if(yAmfhVHXbw == XqStQGqWpP){PHwnRAbHiC = true;}
      else if(XqStQGqWpP == yAmfhVHXbw){GiuzQeuPpN = true;}
      if(IABrbdbPxn == nrNjfttjfJ){dIJGGhFVAd = true;}
      else if(nrNjfttjfJ == IABrbdbPxn){JimHapOsKR = true;}
      if(DhFneCSmuc == JfsEEtfzLB){aaOpPdWFhf = true;}
      else if(JfsEEtfzLB == DhFneCSmuc){qYLLiuhQDC = true;}
      if(KzKoBJqYXU == kTlqsHofaM){PhPaRHwyWm = true;}
      else if(kTlqsHofaM == KzKoBJqYXU){emprJdrHON = true;}
      if(cxGCDNDJMD == kcSDyVdmMW){YkuFWzQjxC = true;}
      if(JizBVPuyBe == OkbHjqyOoW){muduDosGXn = true;}
      if(DUbzkJoLpS == arKndTFWqY){cVYDlwshny = true;}
      while(kcSDyVdmMW == cxGCDNDJMD){YncITfDSHT = true;}
      while(OkbHjqyOoW == OkbHjqyOoW){mRgBihWiPU = true;}
      while(arKndTFWqY == arKndTFWqY){xdMmiVrtxw = true;}
      if(ENJTXgMoFh == true){ENJTXgMoFh = false;}
      if(PrlnmAreHB == true){PrlnmAreHB = false;}
      if(IaqEkrReZe == true){IaqEkrReZe = false;}
      if(PHwnRAbHiC == true){PHwnRAbHiC = false;}
      if(dIJGGhFVAd == true){dIJGGhFVAd = false;}
      if(aaOpPdWFhf == true){aaOpPdWFhf = false;}
      if(PhPaRHwyWm == true){PhPaRHwyWm = false;}
      if(YkuFWzQjxC == true){YkuFWzQjxC = false;}
      if(muduDosGXn == true){muduDosGXn = false;}
      if(cVYDlwshny == true){cVYDlwshny = false;}
      if(lHzNFpfJSQ == true){lHzNFpfJSQ = false;}
      if(MmHfrUETWc == true){MmHfrUETWc = false;}
      if(OpZhJCLrSa == true){OpZhJCLrSa = false;}
      if(GiuzQeuPpN == true){GiuzQeuPpN = false;}
      if(JimHapOsKR == true){JimHapOsKR = false;}
      if(qYLLiuhQDC == true){qYLLiuhQDC = false;}
      if(emprJdrHON == true){emprJdrHON = false;}
      if(YncITfDSHT == true){YncITfDSHT = false;}
      if(mRgBihWiPU == true){mRgBihWiPU = false;}
      if(xdMmiVrtxw == true){xdMmiVrtxw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFAMKPNJDF
{ 
  void FhiQBFNXQK()
  { 
      bool KdkbEYhAcC = false;
      bool xOehGfMoUH = false;
      bool rGNbpZKOKG = false;
      bool sFwVMPCRKZ = false;
      bool zkbJJMVpzA = false;
      bool BjWBVDPJkd = false;
      bool OSoWIqRIUp = false;
      bool dteuIGeESd = false;
      bool ETOKEJiuAJ = false;
      bool AsgfLfwFAR = false;
      bool uMVJVGEasO = false;
      bool YLqHZtDeRz = false;
      bool HVILpkNyjb = false;
      bool KZDAiryFnx = false;
      bool EICljnCYGQ = false;
      bool bRmBKYEKSk = false;
      bool sGqQDzHpYh = false;
      bool wypTtzTVaB = false;
      bool inrSzslBoJ = false;
      bool mmmDEyQlhk = false;
      string weCuznEFlJ;
      string XrmGRfFisu;
      string iXctFSkLTP;
      string FwuMalUsna;
      string QRHotAzZfL;
      string mpRHoYBIog;
      string DskVEaxafe;
      string LLuSeQPmAF;
      string TKeHcPdnWB;
      string kMEGXWfkkS;
      string DXtAAbuzbY;
      string INHjMrNcsn;
      string xIDdtzHntI;
      string jdCgBuQdHB;
      string UdLxsWETse;
      string IDrxUtUPFB;
      string TGETneLZiR;
      string aiVrTSxFkX;
      string tmtOzglELG;
      string aAYGgNYqIO;
      if(weCuznEFlJ == DXtAAbuzbY){KdkbEYhAcC = true;}
      else if(DXtAAbuzbY == weCuznEFlJ){uMVJVGEasO = true;}
      if(XrmGRfFisu == INHjMrNcsn){xOehGfMoUH = true;}
      else if(INHjMrNcsn == XrmGRfFisu){YLqHZtDeRz = true;}
      if(iXctFSkLTP == xIDdtzHntI){rGNbpZKOKG = true;}
      else if(xIDdtzHntI == iXctFSkLTP){HVILpkNyjb = true;}
      if(FwuMalUsna == jdCgBuQdHB){sFwVMPCRKZ = true;}
      else if(jdCgBuQdHB == FwuMalUsna){KZDAiryFnx = true;}
      if(QRHotAzZfL == UdLxsWETse){zkbJJMVpzA = true;}
      else if(UdLxsWETse == QRHotAzZfL){EICljnCYGQ = true;}
      if(mpRHoYBIog == IDrxUtUPFB){BjWBVDPJkd = true;}
      else if(IDrxUtUPFB == mpRHoYBIog){bRmBKYEKSk = true;}
      if(DskVEaxafe == TGETneLZiR){OSoWIqRIUp = true;}
      else if(TGETneLZiR == DskVEaxafe){sGqQDzHpYh = true;}
      if(LLuSeQPmAF == aiVrTSxFkX){dteuIGeESd = true;}
      if(TKeHcPdnWB == tmtOzglELG){ETOKEJiuAJ = true;}
      if(kMEGXWfkkS == aAYGgNYqIO){AsgfLfwFAR = true;}
      while(aiVrTSxFkX == LLuSeQPmAF){wypTtzTVaB = true;}
      while(tmtOzglELG == tmtOzglELG){inrSzslBoJ = true;}
      while(aAYGgNYqIO == aAYGgNYqIO){mmmDEyQlhk = true;}
      if(KdkbEYhAcC == true){KdkbEYhAcC = false;}
      if(xOehGfMoUH == true){xOehGfMoUH = false;}
      if(rGNbpZKOKG == true){rGNbpZKOKG = false;}
      if(sFwVMPCRKZ == true){sFwVMPCRKZ = false;}
      if(zkbJJMVpzA == true){zkbJJMVpzA = false;}
      if(BjWBVDPJkd == true){BjWBVDPJkd = false;}
      if(OSoWIqRIUp == true){OSoWIqRIUp = false;}
      if(dteuIGeESd == true){dteuIGeESd = false;}
      if(ETOKEJiuAJ == true){ETOKEJiuAJ = false;}
      if(AsgfLfwFAR == true){AsgfLfwFAR = false;}
      if(uMVJVGEasO == true){uMVJVGEasO = false;}
      if(YLqHZtDeRz == true){YLqHZtDeRz = false;}
      if(HVILpkNyjb == true){HVILpkNyjb = false;}
      if(KZDAiryFnx == true){KZDAiryFnx = false;}
      if(EICljnCYGQ == true){EICljnCYGQ = false;}
      if(bRmBKYEKSk == true){bRmBKYEKSk = false;}
      if(sGqQDzHpYh == true){sGqQDzHpYh = false;}
      if(wypTtzTVaB == true){wypTtzTVaB = false;}
      if(inrSzslBoJ == true){inrSzslBoJ = false;}
      if(mmmDEyQlhk == true){mmmDEyQlhk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNXFVRIYEA
{ 
  void hurFeTluTj()
  { 
      bool jiSJjLjNFE = false;
      bool crHWgUGIAU = false;
      bool qWMgPaWpAL = false;
      bool ffufnpSSOR = false;
      bool pXIZfUgOJe = false;
      bool MVpcENWltJ = false;
      bool nsNtXxxbiq = false;
      bool CmthdTOlAt = false;
      bool sHfUyKoSba = false;
      bool SfYEdxKNBi = false;
      bool XFfScYbIyk = false;
      bool yjlzQgMsuN = false;
      bool HdAHXVOoEg = false;
      bool IAjRWmbNrZ = false;
      bool hgTpbhtYnw = false;
      bool jRSnasFXuG = false;
      bool JmDQbyzTcc = false;
      bool EzBVeaKJfo = false;
      bool bpAHxqgwpc = false;
      bool hDSkPucCOd = false;
      string PzlpVGYymE;
      string ZZaJsDSwil;
      string OOFAmTDJQS;
      string amjGExuMRs;
      string abqsxisqlN;
      string IbwlZBtlDC;
      string CPgTdmpTEw;
      string IFdpKlXLCD;
      string ZMXCKyqxgD;
      string CIJPpLuWOK;
      string sZloFCxGbm;
      string dhiAcpqdIe;
      string urmBszuOzy;
      string qAxrJzZhxH;
      string BkUsZUZJlA;
      string UQOiOAljuG;
      string HhGducjppc;
      string PJgAdKWsbY;
      string YlbycalNdJ;
      string NolpASdqyw;
      if(PzlpVGYymE == sZloFCxGbm){jiSJjLjNFE = true;}
      else if(sZloFCxGbm == PzlpVGYymE){XFfScYbIyk = true;}
      if(ZZaJsDSwil == dhiAcpqdIe){crHWgUGIAU = true;}
      else if(dhiAcpqdIe == ZZaJsDSwil){yjlzQgMsuN = true;}
      if(OOFAmTDJQS == urmBszuOzy){qWMgPaWpAL = true;}
      else if(urmBszuOzy == OOFAmTDJQS){HdAHXVOoEg = true;}
      if(amjGExuMRs == qAxrJzZhxH){ffufnpSSOR = true;}
      else if(qAxrJzZhxH == amjGExuMRs){IAjRWmbNrZ = true;}
      if(abqsxisqlN == BkUsZUZJlA){pXIZfUgOJe = true;}
      else if(BkUsZUZJlA == abqsxisqlN){hgTpbhtYnw = true;}
      if(IbwlZBtlDC == UQOiOAljuG){MVpcENWltJ = true;}
      else if(UQOiOAljuG == IbwlZBtlDC){jRSnasFXuG = true;}
      if(CPgTdmpTEw == HhGducjppc){nsNtXxxbiq = true;}
      else if(HhGducjppc == CPgTdmpTEw){JmDQbyzTcc = true;}
      if(IFdpKlXLCD == PJgAdKWsbY){CmthdTOlAt = true;}
      if(ZMXCKyqxgD == YlbycalNdJ){sHfUyKoSba = true;}
      if(CIJPpLuWOK == NolpASdqyw){SfYEdxKNBi = true;}
      while(PJgAdKWsbY == IFdpKlXLCD){EzBVeaKJfo = true;}
      while(YlbycalNdJ == YlbycalNdJ){bpAHxqgwpc = true;}
      while(NolpASdqyw == NolpASdqyw){hDSkPucCOd = true;}
      if(jiSJjLjNFE == true){jiSJjLjNFE = false;}
      if(crHWgUGIAU == true){crHWgUGIAU = false;}
      if(qWMgPaWpAL == true){qWMgPaWpAL = false;}
      if(ffufnpSSOR == true){ffufnpSSOR = false;}
      if(pXIZfUgOJe == true){pXIZfUgOJe = false;}
      if(MVpcENWltJ == true){MVpcENWltJ = false;}
      if(nsNtXxxbiq == true){nsNtXxxbiq = false;}
      if(CmthdTOlAt == true){CmthdTOlAt = false;}
      if(sHfUyKoSba == true){sHfUyKoSba = false;}
      if(SfYEdxKNBi == true){SfYEdxKNBi = false;}
      if(XFfScYbIyk == true){XFfScYbIyk = false;}
      if(yjlzQgMsuN == true){yjlzQgMsuN = false;}
      if(HdAHXVOoEg == true){HdAHXVOoEg = false;}
      if(IAjRWmbNrZ == true){IAjRWmbNrZ = false;}
      if(hgTpbhtYnw == true){hgTpbhtYnw = false;}
      if(jRSnasFXuG == true){jRSnasFXuG = false;}
      if(JmDQbyzTcc == true){JmDQbyzTcc = false;}
      if(EzBVeaKJfo == true){EzBVeaKJfo = false;}
      if(bpAHxqgwpc == true){bpAHxqgwpc = false;}
      if(hDSkPucCOd == true){hDSkPucCOd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEIRYFWFBE
{ 
  void MRylzKKimX()
  { 
      bool BnfOeJtWXc = false;
      bool rMLPVUdjdg = false;
      bool MJFuHUebrV = false;
      bool pxnlzBuTlK = false;
      bool YWBxotoHPY = false;
      bool CzCuaqikHJ = false;
      bool eRdBmtYYQT = false;
      bool YKxSHpIIFN = false;
      bool eWMTTpurLH = false;
      bool SJLcfGrzJu = false;
      bool UQqwzqCjmj = false;
      bool hafteHFJhx = false;
      bool yfMIBOzUlA = false;
      bool xJyKrOfPUb = false;
      bool mLEbYrdRyX = false;
      bool BiRMwnDhuj = false;
      bool rgxlmYbUBP = false;
      bool bpoFJlbkjI = false;
      bool kgWOzOqlOD = false;
      bool LyUjjGORoz = false;
      string UMZpgZXLir;
      string UohSYScQtP;
      string yZIYccVsfh;
      string cDWgwVeCeP;
      string gBllfuWbEK;
      string IKyNauDBNE;
      string EefBOQRAVD;
      string nZldhxmVrg;
      string GtoUYSFJGB;
      string RcoaLBUkWO;
      string dWFBWhXTec;
      string HhIfxKpLbw;
      string LHsTkKkLSg;
      string cBzcDjnnxp;
      string tkdcsjTIcB;
      string LIIZDVclQL;
      string xMByAGifbN;
      string WCNlCZdQZA;
      string pbhQUTsYZg;
      string GBWksgjfbm;
      if(UMZpgZXLir == dWFBWhXTec){BnfOeJtWXc = true;}
      else if(dWFBWhXTec == UMZpgZXLir){UQqwzqCjmj = true;}
      if(UohSYScQtP == HhIfxKpLbw){rMLPVUdjdg = true;}
      else if(HhIfxKpLbw == UohSYScQtP){hafteHFJhx = true;}
      if(yZIYccVsfh == LHsTkKkLSg){MJFuHUebrV = true;}
      else if(LHsTkKkLSg == yZIYccVsfh){yfMIBOzUlA = true;}
      if(cDWgwVeCeP == cBzcDjnnxp){pxnlzBuTlK = true;}
      else if(cBzcDjnnxp == cDWgwVeCeP){xJyKrOfPUb = true;}
      if(gBllfuWbEK == tkdcsjTIcB){YWBxotoHPY = true;}
      else if(tkdcsjTIcB == gBllfuWbEK){mLEbYrdRyX = true;}
      if(IKyNauDBNE == LIIZDVclQL){CzCuaqikHJ = true;}
      else if(LIIZDVclQL == IKyNauDBNE){BiRMwnDhuj = true;}
      if(EefBOQRAVD == xMByAGifbN){eRdBmtYYQT = true;}
      else if(xMByAGifbN == EefBOQRAVD){rgxlmYbUBP = true;}
      if(nZldhxmVrg == WCNlCZdQZA){YKxSHpIIFN = true;}
      if(GtoUYSFJGB == pbhQUTsYZg){eWMTTpurLH = true;}
      if(RcoaLBUkWO == GBWksgjfbm){SJLcfGrzJu = true;}
      while(WCNlCZdQZA == nZldhxmVrg){bpoFJlbkjI = true;}
      while(pbhQUTsYZg == pbhQUTsYZg){kgWOzOqlOD = true;}
      while(GBWksgjfbm == GBWksgjfbm){LyUjjGORoz = true;}
      if(BnfOeJtWXc == true){BnfOeJtWXc = false;}
      if(rMLPVUdjdg == true){rMLPVUdjdg = false;}
      if(MJFuHUebrV == true){MJFuHUebrV = false;}
      if(pxnlzBuTlK == true){pxnlzBuTlK = false;}
      if(YWBxotoHPY == true){YWBxotoHPY = false;}
      if(CzCuaqikHJ == true){CzCuaqikHJ = false;}
      if(eRdBmtYYQT == true){eRdBmtYYQT = false;}
      if(YKxSHpIIFN == true){YKxSHpIIFN = false;}
      if(eWMTTpurLH == true){eWMTTpurLH = false;}
      if(SJLcfGrzJu == true){SJLcfGrzJu = false;}
      if(UQqwzqCjmj == true){UQqwzqCjmj = false;}
      if(hafteHFJhx == true){hafteHFJhx = false;}
      if(yfMIBOzUlA == true){yfMIBOzUlA = false;}
      if(xJyKrOfPUb == true){xJyKrOfPUb = false;}
      if(mLEbYrdRyX == true){mLEbYrdRyX = false;}
      if(BiRMwnDhuj == true){BiRMwnDhuj = false;}
      if(rgxlmYbUBP == true){rgxlmYbUBP = false;}
      if(bpoFJlbkjI == true){bpoFJlbkjI = false;}
      if(kgWOzOqlOD == true){kgWOzOqlOD = false;}
      if(LyUjjGORoz == true){LyUjjGORoz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRJDRNSWCZ
{ 
  void pBchzBgghO()
  { 
      bool ikhXDqoktG = false;
      bool GHdCgugKaK = false;
      bool ENpqmMLiDI = false;
      bool VRMyaaQquR = false;
      bool DYbcSfhaqh = false;
      bool iYpZpUtpkq = false;
      bool eGhljntfbG = false;
      bool eoOIGekMXG = false;
      bool dkqVYwamHF = false;
      bool fZFElxqose = false;
      bool kBzkCsKhSK = false;
      bool jhRdMtOMNm = false;
      bool MHYVZFjKVJ = false;
      bool mwTsUbkGSe = false;
      bool lsTwVyHbqr = false;
      bool heaFRdccKx = false;
      bool JALJXmNYJk = false;
      bool IIshATnbAb = false;
      bool xISdaIUObq = false;
      bool yIwVVlhKYh = false;
      string bWfxLCtBGb;
      string MJKsfJiQOS;
      string mmDCaCkmwm;
      string UezopLIEfC;
      string SboKskOcIP;
      string XxyYFoScWJ;
      string QHFTHgKVDU;
      string AekMzLxsIp;
      string mIdfPXfZiB;
      string regVkKVVDM;
      string ZsYnOrLlYt;
      string qZUgVIdYDj;
      string AjmCbVyPbo;
      string pbouPtioRW;
      string LtBoJSJzAb;
      string fwRSMpFWLs;
      string twKjDOjYRb;
      string YoHfXFiyrJ;
      string LyPzIsKWiZ;
      string nMcYcPjQkt;
      if(bWfxLCtBGb == ZsYnOrLlYt){ikhXDqoktG = true;}
      else if(ZsYnOrLlYt == bWfxLCtBGb){kBzkCsKhSK = true;}
      if(MJKsfJiQOS == qZUgVIdYDj){GHdCgugKaK = true;}
      else if(qZUgVIdYDj == MJKsfJiQOS){jhRdMtOMNm = true;}
      if(mmDCaCkmwm == AjmCbVyPbo){ENpqmMLiDI = true;}
      else if(AjmCbVyPbo == mmDCaCkmwm){MHYVZFjKVJ = true;}
      if(UezopLIEfC == pbouPtioRW){VRMyaaQquR = true;}
      else if(pbouPtioRW == UezopLIEfC){mwTsUbkGSe = true;}
      if(SboKskOcIP == LtBoJSJzAb){DYbcSfhaqh = true;}
      else if(LtBoJSJzAb == SboKskOcIP){lsTwVyHbqr = true;}
      if(XxyYFoScWJ == fwRSMpFWLs){iYpZpUtpkq = true;}
      else if(fwRSMpFWLs == XxyYFoScWJ){heaFRdccKx = true;}
      if(QHFTHgKVDU == twKjDOjYRb){eGhljntfbG = true;}
      else if(twKjDOjYRb == QHFTHgKVDU){JALJXmNYJk = true;}
      if(AekMzLxsIp == YoHfXFiyrJ){eoOIGekMXG = true;}
      if(mIdfPXfZiB == LyPzIsKWiZ){dkqVYwamHF = true;}
      if(regVkKVVDM == nMcYcPjQkt){fZFElxqose = true;}
      while(YoHfXFiyrJ == AekMzLxsIp){IIshATnbAb = true;}
      while(LyPzIsKWiZ == LyPzIsKWiZ){xISdaIUObq = true;}
      while(nMcYcPjQkt == nMcYcPjQkt){yIwVVlhKYh = true;}
      if(ikhXDqoktG == true){ikhXDqoktG = false;}
      if(GHdCgugKaK == true){GHdCgugKaK = false;}
      if(ENpqmMLiDI == true){ENpqmMLiDI = false;}
      if(VRMyaaQquR == true){VRMyaaQquR = false;}
      if(DYbcSfhaqh == true){DYbcSfhaqh = false;}
      if(iYpZpUtpkq == true){iYpZpUtpkq = false;}
      if(eGhljntfbG == true){eGhljntfbG = false;}
      if(eoOIGekMXG == true){eoOIGekMXG = false;}
      if(dkqVYwamHF == true){dkqVYwamHF = false;}
      if(fZFElxqose == true){fZFElxqose = false;}
      if(kBzkCsKhSK == true){kBzkCsKhSK = false;}
      if(jhRdMtOMNm == true){jhRdMtOMNm = false;}
      if(MHYVZFjKVJ == true){MHYVZFjKVJ = false;}
      if(mwTsUbkGSe == true){mwTsUbkGSe = false;}
      if(lsTwVyHbqr == true){lsTwVyHbqr = false;}
      if(heaFRdccKx == true){heaFRdccKx = false;}
      if(JALJXmNYJk == true){JALJXmNYJk = false;}
      if(IIshATnbAb == true){IIshATnbAb = false;}
      if(xISdaIUObq == true){xISdaIUObq = false;}
      if(yIwVVlhKYh == true){yIwVVlhKYh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSPQXVPCCX
{ 
  void uPdtccfFXO()
  { 
      bool cdaEzgceeE = false;
      bool SQKpaSGuAg = false;
      bool qKABwYCRZw = false;
      bool qsRWonZfWa = false;
      bool wCrhYqeNoG = false;
      bool mxbIbRdYHa = false;
      bool dLEiMZznAm = false;
      bool saYYkoRRcE = false;
      bool sobSItQIuX = false;
      bool JAXwxjxJUz = false;
      bool qqMCMMXCXl = false;
      bool zLwChoilZS = false;
      bool IqrccsCcbA = false;
      bool qIxcNBbZGw = false;
      bool VNkIXyDUNH = false;
      bool BLiBpAziYS = false;
      bool JuZWtpNSof = false;
      bool MJedwtFiEd = false;
      bool pgOUzfZumM = false;
      bool CsAmlanNNh = false;
      string MJfSWAPPWu;
      string ioGKVUOdIV;
      string ZppFRaTzhr;
      string uYsQAFFxpC;
      string VkDytpRsBs;
      string HYJDdWTZBu;
      string gQgezJuoKP;
      string PRnGAnlrLa;
      string JZynjWOolc;
      string lfutUFDYyj;
      string ubikdpkDDp;
      string kbOZlGSrtc;
      string uGDhcjVsku;
      string jMsafgqMKt;
      string lKkwqKQUIO;
      string mKeVonYBIt;
      string TqRIGYhmtE;
      string OFhApjUHpR;
      string SAjWIYgXlr;
      string IpDQZtsboS;
      if(MJfSWAPPWu == ubikdpkDDp){cdaEzgceeE = true;}
      else if(ubikdpkDDp == MJfSWAPPWu){qqMCMMXCXl = true;}
      if(ioGKVUOdIV == kbOZlGSrtc){SQKpaSGuAg = true;}
      else if(kbOZlGSrtc == ioGKVUOdIV){zLwChoilZS = true;}
      if(ZppFRaTzhr == uGDhcjVsku){qKABwYCRZw = true;}
      else if(uGDhcjVsku == ZppFRaTzhr){IqrccsCcbA = true;}
      if(uYsQAFFxpC == jMsafgqMKt){qsRWonZfWa = true;}
      else if(jMsafgqMKt == uYsQAFFxpC){qIxcNBbZGw = true;}
      if(VkDytpRsBs == lKkwqKQUIO){wCrhYqeNoG = true;}
      else if(lKkwqKQUIO == VkDytpRsBs){VNkIXyDUNH = true;}
      if(HYJDdWTZBu == mKeVonYBIt){mxbIbRdYHa = true;}
      else if(mKeVonYBIt == HYJDdWTZBu){BLiBpAziYS = true;}
      if(gQgezJuoKP == TqRIGYhmtE){dLEiMZznAm = true;}
      else if(TqRIGYhmtE == gQgezJuoKP){JuZWtpNSof = true;}
      if(PRnGAnlrLa == OFhApjUHpR){saYYkoRRcE = true;}
      if(JZynjWOolc == SAjWIYgXlr){sobSItQIuX = true;}
      if(lfutUFDYyj == IpDQZtsboS){JAXwxjxJUz = true;}
      while(OFhApjUHpR == PRnGAnlrLa){MJedwtFiEd = true;}
      while(SAjWIYgXlr == SAjWIYgXlr){pgOUzfZumM = true;}
      while(IpDQZtsboS == IpDQZtsboS){CsAmlanNNh = true;}
      if(cdaEzgceeE == true){cdaEzgceeE = false;}
      if(SQKpaSGuAg == true){SQKpaSGuAg = false;}
      if(qKABwYCRZw == true){qKABwYCRZw = false;}
      if(qsRWonZfWa == true){qsRWonZfWa = false;}
      if(wCrhYqeNoG == true){wCrhYqeNoG = false;}
      if(mxbIbRdYHa == true){mxbIbRdYHa = false;}
      if(dLEiMZznAm == true){dLEiMZznAm = false;}
      if(saYYkoRRcE == true){saYYkoRRcE = false;}
      if(sobSItQIuX == true){sobSItQIuX = false;}
      if(JAXwxjxJUz == true){JAXwxjxJUz = false;}
      if(qqMCMMXCXl == true){qqMCMMXCXl = false;}
      if(zLwChoilZS == true){zLwChoilZS = false;}
      if(IqrccsCcbA == true){IqrccsCcbA = false;}
      if(qIxcNBbZGw == true){qIxcNBbZGw = false;}
      if(VNkIXyDUNH == true){VNkIXyDUNH = false;}
      if(BLiBpAziYS == true){BLiBpAziYS = false;}
      if(JuZWtpNSof == true){JuZWtpNSof = false;}
      if(MJedwtFiEd == true){MJedwtFiEd = false;}
      if(pgOUzfZumM == true){pgOUzfZumM = false;}
      if(CsAmlanNNh == true){CsAmlanNNh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NAADVZALUN
{ 
  void trLNJcziuc()
  { 
      bool xLgettoKeB = false;
      bool KYJsjBSgLF = false;
      bool MODcDkgkhR = false;
      bool CtEnSSZFZF = false;
      bool RZHTpaeLHq = false;
      bool cZOsgiHDbJ = false;
      bool NDcMyPUVaR = false;
      bool bMGFmlHimc = false;
      bool GUcqoceLHj = false;
      bool KVdQrNxtVZ = false;
      bool GIkpPPSJFu = false;
      bool bYQzDralXV = false;
      bool kIOpHFipMY = false;
      bool oMNMVxjlbY = false;
      bool JVFMIkFeMz = false;
      bool mLVzoxttiJ = false;
      bool gcwgGOKDcG = false;
      bool InJzLODChV = false;
      bool AEcNkcpNXX = false;
      bool CoDRqgYYFs = false;
      string uqWVOCFlkT;
      string bXUztMkCtn;
      string wsZGrQyNSk;
      string iIlKOxGyPd;
      string ZUKoxYzBWj;
      string LLHHNCQPcy;
      string DrSzjTlJjw;
      string GllPObhjJS;
      string RxpiYXAewL;
      string fqUQZhBLEc;
      string moQacYYqrl;
      string UgFKgFBiZM;
      string SHMYQPRUog;
      string ZWeffbfPFz;
      string zIlKqzkKjU;
      string fSkrKfbqKN;
      string HDCLMxBYdE;
      string ZlcZNJUChQ;
      string dGkUAHklVA;
      string AnFrruGays;
      if(uqWVOCFlkT == moQacYYqrl){xLgettoKeB = true;}
      else if(moQacYYqrl == uqWVOCFlkT){GIkpPPSJFu = true;}
      if(bXUztMkCtn == UgFKgFBiZM){KYJsjBSgLF = true;}
      else if(UgFKgFBiZM == bXUztMkCtn){bYQzDralXV = true;}
      if(wsZGrQyNSk == SHMYQPRUog){MODcDkgkhR = true;}
      else if(SHMYQPRUog == wsZGrQyNSk){kIOpHFipMY = true;}
      if(iIlKOxGyPd == ZWeffbfPFz){CtEnSSZFZF = true;}
      else if(ZWeffbfPFz == iIlKOxGyPd){oMNMVxjlbY = true;}
      if(ZUKoxYzBWj == zIlKqzkKjU){RZHTpaeLHq = true;}
      else if(zIlKqzkKjU == ZUKoxYzBWj){JVFMIkFeMz = true;}
      if(LLHHNCQPcy == fSkrKfbqKN){cZOsgiHDbJ = true;}
      else if(fSkrKfbqKN == LLHHNCQPcy){mLVzoxttiJ = true;}
      if(DrSzjTlJjw == HDCLMxBYdE){NDcMyPUVaR = true;}
      else if(HDCLMxBYdE == DrSzjTlJjw){gcwgGOKDcG = true;}
      if(GllPObhjJS == ZlcZNJUChQ){bMGFmlHimc = true;}
      if(RxpiYXAewL == dGkUAHklVA){GUcqoceLHj = true;}
      if(fqUQZhBLEc == AnFrruGays){KVdQrNxtVZ = true;}
      while(ZlcZNJUChQ == GllPObhjJS){InJzLODChV = true;}
      while(dGkUAHklVA == dGkUAHklVA){AEcNkcpNXX = true;}
      while(AnFrruGays == AnFrruGays){CoDRqgYYFs = true;}
      if(xLgettoKeB == true){xLgettoKeB = false;}
      if(KYJsjBSgLF == true){KYJsjBSgLF = false;}
      if(MODcDkgkhR == true){MODcDkgkhR = false;}
      if(CtEnSSZFZF == true){CtEnSSZFZF = false;}
      if(RZHTpaeLHq == true){RZHTpaeLHq = false;}
      if(cZOsgiHDbJ == true){cZOsgiHDbJ = false;}
      if(NDcMyPUVaR == true){NDcMyPUVaR = false;}
      if(bMGFmlHimc == true){bMGFmlHimc = false;}
      if(GUcqoceLHj == true){GUcqoceLHj = false;}
      if(KVdQrNxtVZ == true){KVdQrNxtVZ = false;}
      if(GIkpPPSJFu == true){GIkpPPSJFu = false;}
      if(bYQzDralXV == true){bYQzDralXV = false;}
      if(kIOpHFipMY == true){kIOpHFipMY = false;}
      if(oMNMVxjlbY == true){oMNMVxjlbY = false;}
      if(JVFMIkFeMz == true){JVFMIkFeMz = false;}
      if(mLVzoxttiJ == true){mLVzoxttiJ = false;}
      if(gcwgGOKDcG == true){gcwgGOKDcG = false;}
      if(InJzLODChV == true){InJzLODChV = false;}
      if(AEcNkcpNXX == true){AEcNkcpNXX = false;}
      if(CoDRqgYYFs == true){CoDRqgYYFs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JJTZILHSOX
{ 
  void RgVsAjlMen()
  { 
      bool oKxpRiPdCK = false;
      bool HDakmJzHig = false;
      bool KnRSBPMMzD = false;
      bool fOYnXKbiCA = false;
      bool MDBkDDHFlV = false;
      bool kqnkjBsenB = false;
      bool VCdzerdlMb = false;
      bool gPEiTGmfOx = false;
      bool HHadRoZnEW = false;
      bool RwuBdJZBGL = false;
      bool ZVrJnUlFQc = false;
      bool OMQptObzgp = false;
      bool RohoKjUDEJ = false;
      bool gkZDXlOQow = false;
      bool CUXaIEfFGP = false;
      bool hZUQsjnCzE = false;
      bool AhBGucmMRH = false;
      bool zKKjmxRGgF = false;
      bool DPwnbHPIJm = false;
      bool xLRkwTSQee = false;
      string PjqVlQRPpo;
      string laiotPjWQF;
      string dnTPJKzpIx;
      string msSBwgyXmY;
      string FdunlftYGV;
      string xgFnmaPbMb;
      string RbHsCsIgrM;
      string RMjrzAredc;
      string PZilzFneOV;
      string RWKLHdVCls;
      string XNgtEkxMnm;
      string hjxiLqrUsw;
      string EcSWuuBYkV;
      string dpsjFCsohO;
      string IapamgYbzP;
      string lBIpnttKzJ;
      string iXbSJrqNdJ;
      string yClemdlqiN;
      string VZYUibgDuL;
      string HhpYejyXRu;
      if(PjqVlQRPpo == XNgtEkxMnm){oKxpRiPdCK = true;}
      else if(XNgtEkxMnm == PjqVlQRPpo){ZVrJnUlFQc = true;}
      if(laiotPjWQF == hjxiLqrUsw){HDakmJzHig = true;}
      else if(hjxiLqrUsw == laiotPjWQF){OMQptObzgp = true;}
      if(dnTPJKzpIx == EcSWuuBYkV){KnRSBPMMzD = true;}
      else if(EcSWuuBYkV == dnTPJKzpIx){RohoKjUDEJ = true;}
      if(msSBwgyXmY == dpsjFCsohO){fOYnXKbiCA = true;}
      else if(dpsjFCsohO == msSBwgyXmY){gkZDXlOQow = true;}
      if(FdunlftYGV == IapamgYbzP){MDBkDDHFlV = true;}
      else if(IapamgYbzP == FdunlftYGV){CUXaIEfFGP = true;}
      if(xgFnmaPbMb == lBIpnttKzJ){kqnkjBsenB = true;}
      else if(lBIpnttKzJ == xgFnmaPbMb){hZUQsjnCzE = true;}
      if(RbHsCsIgrM == iXbSJrqNdJ){VCdzerdlMb = true;}
      else if(iXbSJrqNdJ == RbHsCsIgrM){AhBGucmMRH = true;}
      if(RMjrzAredc == yClemdlqiN){gPEiTGmfOx = true;}
      if(PZilzFneOV == VZYUibgDuL){HHadRoZnEW = true;}
      if(RWKLHdVCls == HhpYejyXRu){RwuBdJZBGL = true;}
      while(yClemdlqiN == RMjrzAredc){zKKjmxRGgF = true;}
      while(VZYUibgDuL == VZYUibgDuL){DPwnbHPIJm = true;}
      while(HhpYejyXRu == HhpYejyXRu){xLRkwTSQee = true;}
      if(oKxpRiPdCK == true){oKxpRiPdCK = false;}
      if(HDakmJzHig == true){HDakmJzHig = false;}
      if(KnRSBPMMzD == true){KnRSBPMMzD = false;}
      if(fOYnXKbiCA == true){fOYnXKbiCA = false;}
      if(MDBkDDHFlV == true){MDBkDDHFlV = false;}
      if(kqnkjBsenB == true){kqnkjBsenB = false;}
      if(VCdzerdlMb == true){VCdzerdlMb = false;}
      if(gPEiTGmfOx == true){gPEiTGmfOx = false;}
      if(HHadRoZnEW == true){HHadRoZnEW = false;}
      if(RwuBdJZBGL == true){RwuBdJZBGL = false;}
      if(ZVrJnUlFQc == true){ZVrJnUlFQc = false;}
      if(OMQptObzgp == true){OMQptObzgp = false;}
      if(RohoKjUDEJ == true){RohoKjUDEJ = false;}
      if(gkZDXlOQow == true){gkZDXlOQow = false;}
      if(CUXaIEfFGP == true){CUXaIEfFGP = false;}
      if(hZUQsjnCzE == true){hZUQsjnCzE = false;}
      if(AhBGucmMRH == true){AhBGucmMRH = false;}
      if(zKKjmxRGgF == true){zKKjmxRGgF = false;}
      if(DPwnbHPIJm == true){DPwnbHPIJm = false;}
      if(xLRkwTSQee == true){xLRkwTSQee = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXVABOPZKK
{ 
  void ylfHyYjlyH()
  { 
      bool TlpPTZiIgh = false;
      bool GcXWAfgilO = false;
      bool rkStuqeUHl = false;
      bool tVkMURDCMJ = false;
      bool wFbTXtQCfe = false;
      bool ixxYfiSuUc = false;
      bool uNBtmjqKCi = false;
      bool bdWcRmJyWA = false;
      bool abobDxYMgl = false;
      bool yIgjOiEhfm = false;
      bool CFAxCEaTGs = false;
      bool YTYTCTYYqp = false;
      bool LedQjTwlOi = false;
      bool haSjxUbqYz = false;
      bool VEFmMdiNhu = false;
      bool KeqpaXbjMi = false;
      bool HnFXKyBnVh = false;
      bool qgzqUGZpEF = false;
      bool jiESYDjbIZ = false;
      bool rrdpqgzhbN = false;
      string GwXZOfJGba;
      string OPkkfQBibr;
      string CkTwsmiTQx;
      string twLoubQLEW;
      string JNMdBcEOSP;
      string ZeCTyUbbfb;
      string wpodfSEwpD;
      string AoeFhoYptP;
      string hUABXPtqpZ;
      string AoecZTYhyh;
      string YIYOPkAwkJ;
      string wlgPsaonGP;
      string YMFPDLJBfO;
      string PpqLqZwkkm;
      string OxGgdOHPiy;
      string dkbhJMCILE;
      string azQWsFtVYS;
      string eECTBaFYkn;
      string DtRgjeNICd;
      string XnZgLPgjmX;
      if(GwXZOfJGba == YIYOPkAwkJ){TlpPTZiIgh = true;}
      else if(YIYOPkAwkJ == GwXZOfJGba){CFAxCEaTGs = true;}
      if(OPkkfQBibr == wlgPsaonGP){GcXWAfgilO = true;}
      else if(wlgPsaonGP == OPkkfQBibr){YTYTCTYYqp = true;}
      if(CkTwsmiTQx == YMFPDLJBfO){rkStuqeUHl = true;}
      else if(YMFPDLJBfO == CkTwsmiTQx){LedQjTwlOi = true;}
      if(twLoubQLEW == PpqLqZwkkm){tVkMURDCMJ = true;}
      else if(PpqLqZwkkm == twLoubQLEW){haSjxUbqYz = true;}
      if(JNMdBcEOSP == OxGgdOHPiy){wFbTXtQCfe = true;}
      else if(OxGgdOHPiy == JNMdBcEOSP){VEFmMdiNhu = true;}
      if(ZeCTyUbbfb == dkbhJMCILE){ixxYfiSuUc = true;}
      else if(dkbhJMCILE == ZeCTyUbbfb){KeqpaXbjMi = true;}
      if(wpodfSEwpD == azQWsFtVYS){uNBtmjqKCi = true;}
      else if(azQWsFtVYS == wpodfSEwpD){HnFXKyBnVh = true;}
      if(AoeFhoYptP == eECTBaFYkn){bdWcRmJyWA = true;}
      if(hUABXPtqpZ == DtRgjeNICd){abobDxYMgl = true;}
      if(AoecZTYhyh == XnZgLPgjmX){yIgjOiEhfm = true;}
      while(eECTBaFYkn == AoeFhoYptP){qgzqUGZpEF = true;}
      while(DtRgjeNICd == DtRgjeNICd){jiESYDjbIZ = true;}
      while(XnZgLPgjmX == XnZgLPgjmX){rrdpqgzhbN = true;}
      if(TlpPTZiIgh == true){TlpPTZiIgh = false;}
      if(GcXWAfgilO == true){GcXWAfgilO = false;}
      if(rkStuqeUHl == true){rkStuqeUHl = false;}
      if(tVkMURDCMJ == true){tVkMURDCMJ = false;}
      if(wFbTXtQCfe == true){wFbTXtQCfe = false;}
      if(ixxYfiSuUc == true){ixxYfiSuUc = false;}
      if(uNBtmjqKCi == true){uNBtmjqKCi = false;}
      if(bdWcRmJyWA == true){bdWcRmJyWA = false;}
      if(abobDxYMgl == true){abobDxYMgl = false;}
      if(yIgjOiEhfm == true){yIgjOiEhfm = false;}
      if(CFAxCEaTGs == true){CFAxCEaTGs = false;}
      if(YTYTCTYYqp == true){YTYTCTYYqp = false;}
      if(LedQjTwlOi == true){LedQjTwlOi = false;}
      if(haSjxUbqYz == true){haSjxUbqYz = false;}
      if(VEFmMdiNhu == true){VEFmMdiNhu = false;}
      if(KeqpaXbjMi == true){KeqpaXbjMi = false;}
      if(HnFXKyBnVh == true){HnFXKyBnVh = false;}
      if(qgzqUGZpEF == true){qgzqUGZpEF = false;}
      if(jiESYDjbIZ == true){jiESYDjbIZ = false;}
      if(rrdpqgzhbN == true){rrdpqgzhbN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VAOLWWEZKA
{ 
  void gnIqaUbbLb()
  { 
      bool ccYrzRjlHh = false;
      bool DflBaqjBSW = false;
      bool porMMTmZPY = false;
      bool iMbtLnuwfa = false;
      bool CRdRJERmxV = false;
      bool KSqdpnjMfe = false;
      bool dJWhzqDqol = false;
      bool wnVrUYKZDH = false;
      bool CAbsOQVyEX = false;
      bool EiQAwrtwSS = false;
      bool AZxLZVwzIR = false;
      bool cKIXcdhcTi = false;
      bool UElRgMWVuc = false;
      bool dOHjHbDPTr = false;
      bool TWpmttasWS = false;
      bool JRbjyumeeM = false;
      bool zaDemNCYQA = false;
      bool ZRIbOxOzWm = false;
      bool ldybSLmWlL = false;
      bool oXkGrsSKzg = false;
      string LzFIFlBUnh;
      string PPRQnmVViC;
      string ZOnBlVXhKb;
      string ccDmgCCkOX;
      string QHeQbecwUP;
      string SIsixwKDVi;
      string OSJMFmMdjk;
      string kjHLkSjXZG;
      string rbNuITiTok;
      string ryOeJyxRLo;
      string SyLidhBhyd;
      string LmdOpmFODk;
      string DrozslVcBl;
      string URLkntPdQa;
      string SAVKYEUAnW;
      string siOZkZJMpr;
      string MXgLJsaraw;
      string WaycSCWdZo;
      string RUneslDkAN;
      string jDnYNtTJBf;
      if(LzFIFlBUnh == SyLidhBhyd){ccYrzRjlHh = true;}
      else if(SyLidhBhyd == LzFIFlBUnh){AZxLZVwzIR = true;}
      if(PPRQnmVViC == LmdOpmFODk){DflBaqjBSW = true;}
      else if(LmdOpmFODk == PPRQnmVViC){cKIXcdhcTi = true;}
      if(ZOnBlVXhKb == DrozslVcBl){porMMTmZPY = true;}
      else if(DrozslVcBl == ZOnBlVXhKb){UElRgMWVuc = true;}
      if(ccDmgCCkOX == URLkntPdQa){iMbtLnuwfa = true;}
      else if(URLkntPdQa == ccDmgCCkOX){dOHjHbDPTr = true;}
      if(QHeQbecwUP == SAVKYEUAnW){CRdRJERmxV = true;}
      else if(SAVKYEUAnW == QHeQbecwUP){TWpmttasWS = true;}
      if(SIsixwKDVi == siOZkZJMpr){KSqdpnjMfe = true;}
      else if(siOZkZJMpr == SIsixwKDVi){JRbjyumeeM = true;}
      if(OSJMFmMdjk == MXgLJsaraw){dJWhzqDqol = true;}
      else if(MXgLJsaraw == OSJMFmMdjk){zaDemNCYQA = true;}
      if(kjHLkSjXZG == WaycSCWdZo){wnVrUYKZDH = true;}
      if(rbNuITiTok == RUneslDkAN){CAbsOQVyEX = true;}
      if(ryOeJyxRLo == jDnYNtTJBf){EiQAwrtwSS = true;}
      while(WaycSCWdZo == kjHLkSjXZG){ZRIbOxOzWm = true;}
      while(RUneslDkAN == RUneslDkAN){ldybSLmWlL = true;}
      while(jDnYNtTJBf == jDnYNtTJBf){oXkGrsSKzg = true;}
      if(ccYrzRjlHh == true){ccYrzRjlHh = false;}
      if(DflBaqjBSW == true){DflBaqjBSW = false;}
      if(porMMTmZPY == true){porMMTmZPY = false;}
      if(iMbtLnuwfa == true){iMbtLnuwfa = false;}
      if(CRdRJERmxV == true){CRdRJERmxV = false;}
      if(KSqdpnjMfe == true){KSqdpnjMfe = false;}
      if(dJWhzqDqol == true){dJWhzqDqol = false;}
      if(wnVrUYKZDH == true){wnVrUYKZDH = false;}
      if(CAbsOQVyEX == true){CAbsOQVyEX = false;}
      if(EiQAwrtwSS == true){EiQAwrtwSS = false;}
      if(AZxLZVwzIR == true){AZxLZVwzIR = false;}
      if(cKIXcdhcTi == true){cKIXcdhcTi = false;}
      if(UElRgMWVuc == true){UElRgMWVuc = false;}
      if(dOHjHbDPTr == true){dOHjHbDPTr = false;}
      if(TWpmttasWS == true){TWpmttasWS = false;}
      if(JRbjyumeeM == true){JRbjyumeeM = false;}
      if(zaDemNCYQA == true){zaDemNCYQA = false;}
      if(ZRIbOxOzWm == true){ZRIbOxOzWm = false;}
      if(ldybSLmWlL == true){ldybSLmWlL = false;}
      if(oXkGrsSKzg == true){oXkGrsSKzg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWMQCMOZOI
{ 
  void AcIaeJqwdo()
  { 
      bool EwkTsiWkBE = false;
      bool GMjjdIaycW = false;
      bool xSbwiPfetz = false;
      bool xjjgHUBmnJ = false;
      bool qgigAVedWF = false;
      bool qijFNlTokc = false;
      bool CrpCHWbDbI = false;
      bool GmKTePiuwM = false;
      bool jBHnINzdSV = false;
      bool BMBKGzqgZd = false;
      bool sbBNyDYQay = false;
      bool CYsYsBjBts = false;
      bool WyjGHtkzMf = false;
      bool YCURSHzsoF = false;
      bool oiDUTbTcRF = false;
      bool PomfGuruGE = false;
      bool RYDtYADaFk = false;
      bool BpMoEnuOme = false;
      bool ZIhGQjOoLX = false;
      bool PDmjmPeIuS = false;
      string tWIBZYeHpA;
      string ifDcKxwsMe;
      string aqVYotKqKm;
      string GnYOFTcPpK;
      string YcQeYrnUKq;
      string EdnyzCAiLe;
      string NnwCttHoWp;
      string UfDCGxapAw;
      string GpfTibAaOD;
      string TsEKwkfNkd;
      string kyxTWXalqB;
      string bJiOYXHcTR;
      string tgZTWabrFV;
      string RMEVLHrMwK;
      string AOiMaJJokX;
      string dDtTjEYcxu;
      string whfVjPENDQ;
      string eufJRexMrM;
      string RmHgrNRkkH;
      string hPOBORhNbL;
      if(tWIBZYeHpA == kyxTWXalqB){EwkTsiWkBE = true;}
      else if(kyxTWXalqB == tWIBZYeHpA){sbBNyDYQay = true;}
      if(ifDcKxwsMe == bJiOYXHcTR){GMjjdIaycW = true;}
      else if(bJiOYXHcTR == ifDcKxwsMe){CYsYsBjBts = true;}
      if(aqVYotKqKm == tgZTWabrFV){xSbwiPfetz = true;}
      else if(tgZTWabrFV == aqVYotKqKm){WyjGHtkzMf = true;}
      if(GnYOFTcPpK == RMEVLHrMwK){xjjgHUBmnJ = true;}
      else if(RMEVLHrMwK == GnYOFTcPpK){YCURSHzsoF = true;}
      if(YcQeYrnUKq == AOiMaJJokX){qgigAVedWF = true;}
      else if(AOiMaJJokX == YcQeYrnUKq){oiDUTbTcRF = true;}
      if(EdnyzCAiLe == dDtTjEYcxu){qijFNlTokc = true;}
      else if(dDtTjEYcxu == EdnyzCAiLe){PomfGuruGE = true;}
      if(NnwCttHoWp == whfVjPENDQ){CrpCHWbDbI = true;}
      else if(whfVjPENDQ == NnwCttHoWp){RYDtYADaFk = true;}
      if(UfDCGxapAw == eufJRexMrM){GmKTePiuwM = true;}
      if(GpfTibAaOD == RmHgrNRkkH){jBHnINzdSV = true;}
      if(TsEKwkfNkd == hPOBORhNbL){BMBKGzqgZd = true;}
      while(eufJRexMrM == UfDCGxapAw){BpMoEnuOme = true;}
      while(RmHgrNRkkH == RmHgrNRkkH){ZIhGQjOoLX = true;}
      while(hPOBORhNbL == hPOBORhNbL){PDmjmPeIuS = true;}
      if(EwkTsiWkBE == true){EwkTsiWkBE = false;}
      if(GMjjdIaycW == true){GMjjdIaycW = false;}
      if(xSbwiPfetz == true){xSbwiPfetz = false;}
      if(xjjgHUBmnJ == true){xjjgHUBmnJ = false;}
      if(qgigAVedWF == true){qgigAVedWF = false;}
      if(qijFNlTokc == true){qijFNlTokc = false;}
      if(CrpCHWbDbI == true){CrpCHWbDbI = false;}
      if(GmKTePiuwM == true){GmKTePiuwM = false;}
      if(jBHnINzdSV == true){jBHnINzdSV = false;}
      if(BMBKGzqgZd == true){BMBKGzqgZd = false;}
      if(sbBNyDYQay == true){sbBNyDYQay = false;}
      if(CYsYsBjBts == true){CYsYsBjBts = false;}
      if(WyjGHtkzMf == true){WyjGHtkzMf = false;}
      if(YCURSHzsoF == true){YCURSHzsoF = false;}
      if(oiDUTbTcRF == true){oiDUTbTcRF = false;}
      if(PomfGuruGE == true){PomfGuruGE = false;}
      if(RYDtYADaFk == true){RYDtYADaFk = false;}
      if(BpMoEnuOme == true){BpMoEnuOme = false;}
      if(ZIhGQjOoLX == true){ZIhGQjOoLX = false;}
      if(PDmjmPeIuS == true){PDmjmPeIuS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHFRACWQJD
{ 
  void wHRYMOMHgq()
  { 
      bool awDnJjdxpf = false;
      bool pDXBHgVJmt = false;
      bool ZWLUEDcQrR = false;
      bool KBVZnUhxsg = false;
      bool poqwehZbwC = false;
      bool EdDBIDjhiG = false;
      bool GMEXVogyNl = false;
      bool yXQFEkePpW = false;
      bool dAUpNgyTQj = false;
      bool kzOlZcjTap = false;
      bool AaNJDfMxxW = false;
      bool XUrMcFqOJn = false;
      bool qNgdAzJeea = false;
      bool ALnzVCmLlg = false;
      bool TAWtLQHBJU = false;
      bool kUJlymtjIE = false;
      bool WhRVWMfrqa = false;
      bool SfcbTqpmRj = false;
      bool rIUKoeBBBh = false;
      bool HDCgKlhAWz = false;
      string kUXOiNLWAU;
      string bLKimFmhiu;
      string PwYnqbVGTW;
      string hDRoJuSOkf;
      string wAgxCPUICO;
      string WXcKwnuiXG;
      string qEDdlYtUYr;
      string lXxCzPPaka;
      string HNDFAKZGrU;
      string ziqeoqwDKc;
      string VzjJbyaZLg;
      string YUxwzdAxdb;
      string ymcDsDfRNH;
      string SMPIEHctcB;
      string iAuKuekufK;
      string pyZieiVfQY;
      string RIMEOMEoqq;
      string AGUbsyrSIO;
      string RklCQTmgcV;
      string lxdDiampwh;
      if(kUXOiNLWAU == VzjJbyaZLg){awDnJjdxpf = true;}
      else if(VzjJbyaZLg == kUXOiNLWAU){AaNJDfMxxW = true;}
      if(bLKimFmhiu == YUxwzdAxdb){pDXBHgVJmt = true;}
      else if(YUxwzdAxdb == bLKimFmhiu){XUrMcFqOJn = true;}
      if(PwYnqbVGTW == ymcDsDfRNH){ZWLUEDcQrR = true;}
      else if(ymcDsDfRNH == PwYnqbVGTW){qNgdAzJeea = true;}
      if(hDRoJuSOkf == SMPIEHctcB){KBVZnUhxsg = true;}
      else if(SMPIEHctcB == hDRoJuSOkf){ALnzVCmLlg = true;}
      if(wAgxCPUICO == iAuKuekufK){poqwehZbwC = true;}
      else if(iAuKuekufK == wAgxCPUICO){TAWtLQHBJU = true;}
      if(WXcKwnuiXG == pyZieiVfQY){EdDBIDjhiG = true;}
      else if(pyZieiVfQY == WXcKwnuiXG){kUJlymtjIE = true;}
      if(qEDdlYtUYr == RIMEOMEoqq){GMEXVogyNl = true;}
      else if(RIMEOMEoqq == qEDdlYtUYr){WhRVWMfrqa = true;}
      if(lXxCzPPaka == AGUbsyrSIO){yXQFEkePpW = true;}
      if(HNDFAKZGrU == RklCQTmgcV){dAUpNgyTQj = true;}
      if(ziqeoqwDKc == lxdDiampwh){kzOlZcjTap = true;}
      while(AGUbsyrSIO == lXxCzPPaka){SfcbTqpmRj = true;}
      while(RklCQTmgcV == RklCQTmgcV){rIUKoeBBBh = true;}
      while(lxdDiampwh == lxdDiampwh){HDCgKlhAWz = true;}
      if(awDnJjdxpf == true){awDnJjdxpf = false;}
      if(pDXBHgVJmt == true){pDXBHgVJmt = false;}
      if(ZWLUEDcQrR == true){ZWLUEDcQrR = false;}
      if(KBVZnUhxsg == true){KBVZnUhxsg = false;}
      if(poqwehZbwC == true){poqwehZbwC = false;}
      if(EdDBIDjhiG == true){EdDBIDjhiG = false;}
      if(GMEXVogyNl == true){GMEXVogyNl = false;}
      if(yXQFEkePpW == true){yXQFEkePpW = false;}
      if(dAUpNgyTQj == true){dAUpNgyTQj = false;}
      if(kzOlZcjTap == true){kzOlZcjTap = false;}
      if(AaNJDfMxxW == true){AaNJDfMxxW = false;}
      if(XUrMcFqOJn == true){XUrMcFqOJn = false;}
      if(qNgdAzJeea == true){qNgdAzJeea = false;}
      if(ALnzVCmLlg == true){ALnzVCmLlg = false;}
      if(TAWtLQHBJU == true){TAWtLQHBJU = false;}
      if(kUJlymtjIE == true){kUJlymtjIE = false;}
      if(WhRVWMfrqa == true){WhRVWMfrqa = false;}
      if(SfcbTqpmRj == true){SfcbTqpmRj = false;}
      if(rIUKoeBBBh == true){rIUKoeBBBh = false;}
      if(HDCgKlhAWz == true){HDCgKlhAWz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ERAELFEXUH
{ 
  void XCXQHAUqCV()
  { 
      bool uVxNqaYVjL = false;
      bool zTLWmgUkwd = false;
      bool oaUunRYgzL = false;
      bool lGCjNJRLly = false;
      bool YHLwoqHZCA = false;
      bool xyDhbTABYZ = false;
      bool CqVYYrQbJd = false;
      bool OJyyEgPYGw = false;
      bool JzdzOnDUHs = false;
      bool IPlLuglmWw = false;
      bool afPYkmzEcu = false;
      bool EaucQDNVJk = false;
      bool owUPUzXmCW = false;
      bool tbCKVdiEOa = false;
      bool nyqMnhUIur = false;
      bool TQckGdKzEl = false;
      bool PMBFAbYkHl = false;
      bool UIGhwqFIam = false;
      bool dOrKDdzQDr = false;
      bool SiAcLbwlLL = false;
      string jDhyttQnLt;
      string aKMthSXTtB;
      string oqDatXwcAb;
      string MoWBaCXObr;
      string iRxllUtRos;
      string DVWJsrAGDV;
      string xmnjgknKTe;
      string uIqCRWsQoZ;
      string cenHYqSMIh;
      string CQLFuwcNFA;
      string fjyJxteUqV;
      string yiRcsRzgKp;
      string SaBkcexkGV;
      string tfLossgdJd;
      string LxUmjTyhMc;
      string wwCOgFhMgS;
      string wsNVbSXcjz;
      string kVXgdVFOBJ;
      string fPYcYxcwHn;
      string LTxpgRizLR;
      if(jDhyttQnLt == fjyJxteUqV){uVxNqaYVjL = true;}
      else if(fjyJxteUqV == jDhyttQnLt){afPYkmzEcu = true;}
      if(aKMthSXTtB == yiRcsRzgKp){zTLWmgUkwd = true;}
      else if(yiRcsRzgKp == aKMthSXTtB){EaucQDNVJk = true;}
      if(oqDatXwcAb == SaBkcexkGV){oaUunRYgzL = true;}
      else if(SaBkcexkGV == oqDatXwcAb){owUPUzXmCW = true;}
      if(MoWBaCXObr == tfLossgdJd){lGCjNJRLly = true;}
      else if(tfLossgdJd == MoWBaCXObr){tbCKVdiEOa = true;}
      if(iRxllUtRos == LxUmjTyhMc){YHLwoqHZCA = true;}
      else if(LxUmjTyhMc == iRxllUtRos){nyqMnhUIur = true;}
      if(DVWJsrAGDV == wwCOgFhMgS){xyDhbTABYZ = true;}
      else if(wwCOgFhMgS == DVWJsrAGDV){TQckGdKzEl = true;}
      if(xmnjgknKTe == wsNVbSXcjz){CqVYYrQbJd = true;}
      else if(wsNVbSXcjz == xmnjgknKTe){PMBFAbYkHl = true;}
      if(uIqCRWsQoZ == kVXgdVFOBJ){OJyyEgPYGw = true;}
      if(cenHYqSMIh == fPYcYxcwHn){JzdzOnDUHs = true;}
      if(CQLFuwcNFA == LTxpgRizLR){IPlLuglmWw = true;}
      while(kVXgdVFOBJ == uIqCRWsQoZ){UIGhwqFIam = true;}
      while(fPYcYxcwHn == fPYcYxcwHn){dOrKDdzQDr = true;}
      while(LTxpgRizLR == LTxpgRizLR){SiAcLbwlLL = true;}
      if(uVxNqaYVjL == true){uVxNqaYVjL = false;}
      if(zTLWmgUkwd == true){zTLWmgUkwd = false;}
      if(oaUunRYgzL == true){oaUunRYgzL = false;}
      if(lGCjNJRLly == true){lGCjNJRLly = false;}
      if(YHLwoqHZCA == true){YHLwoqHZCA = false;}
      if(xyDhbTABYZ == true){xyDhbTABYZ = false;}
      if(CqVYYrQbJd == true){CqVYYrQbJd = false;}
      if(OJyyEgPYGw == true){OJyyEgPYGw = false;}
      if(JzdzOnDUHs == true){JzdzOnDUHs = false;}
      if(IPlLuglmWw == true){IPlLuglmWw = false;}
      if(afPYkmzEcu == true){afPYkmzEcu = false;}
      if(EaucQDNVJk == true){EaucQDNVJk = false;}
      if(owUPUzXmCW == true){owUPUzXmCW = false;}
      if(tbCKVdiEOa == true){tbCKVdiEOa = false;}
      if(nyqMnhUIur == true){nyqMnhUIur = false;}
      if(TQckGdKzEl == true){TQckGdKzEl = false;}
      if(PMBFAbYkHl == true){PMBFAbYkHl = false;}
      if(UIGhwqFIam == true){UIGhwqFIam = false;}
      if(dOrKDdzQDr == true){dOrKDdzQDr = false;}
      if(SiAcLbwlLL == true){SiAcLbwlLL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGFLRTGMGF
{ 
  void IpMjGCYnIm()
  { 
      bool LUZagmttPL = false;
      bool lkuGhrzGZP = false;
      bool SVlpqCLyKs = false;
      bool YNNjfcVzRc = false;
      bool mXWQZjSFcc = false;
      bool cbwsKohiie = false;
      bool bujWlXXLZE = false;
      bool VznwcuzUPH = false;
      bool iFUhQxRTYp = false;
      bool tmQlBqnzeC = false;
      bool LGfXGcmzPP = false;
      bool pMTauVaBGn = false;
      bool FDmiKihCul = false;
      bool HzpNwbZxbm = false;
      bool JSDIAgTppe = false;
      bool QlspxHTwNW = false;
      bool tkEdIpWFdT = false;
      bool wdZTdlzdic = false;
      bool PrLPVUGzPn = false;
      bool IdiErYOZAJ = false;
      string eBgladryec;
      string SAXNUpieZO;
      string tnrLATcqsS;
      string TfVGmIOzlo;
      string tHcPByDPWo;
      string wfnnTpIUlH;
      string BBEMJmeQaM;
      string bjrkUmKcKB;
      string QMTEVnqgmw;
      string ztMemrDQFO;
      string TlnKNMmDTg;
      string ffKjqogApV;
      string uxdeMhXNxb;
      string jsWuhdXJqJ;
      string AnNGQTjbmy;
      string KDajSVIJyf;
      string nYFqwlIOCM;
      string QWJfUHjWNr;
      string xuZzQgSlbL;
      string UOLKUbhVJd;
      if(eBgladryec == TlnKNMmDTg){LUZagmttPL = true;}
      else if(TlnKNMmDTg == eBgladryec){LGfXGcmzPP = true;}
      if(SAXNUpieZO == ffKjqogApV){lkuGhrzGZP = true;}
      else if(ffKjqogApV == SAXNUpieZO){pMTauVaBGn = true;}
      if(tnrLATcqsS == uxdeMhXNxb){SVlpqCLyKs = true;}
      else if(uxdeMhXNxb == tnrLATcqsS){FDmiKihCul = true;}
      if(TfVGmIOzlo == jsWuhdXJqJ){YNNjfcVzRc = true;}
      else if(jsWuhdXJqJ == TfVGmIOzlo){HzpNwbZxbm = true;}
      if(tHcPByDPWo == AnNGQTjbmy){mXWQZjSFcc = true;}
      else if(AnNGQTjbmy == tHcPByDPWo){JSDIAgTppe = true;}
      if(wfnnTpIUlH == KDajSVIJyf){cbwsKohiie = true;}
      else if(KDajSVIJyf == wfnnTpIUlH){QlspxHTwNW = true;}
      if(BBEMJmeQaM == nYFqwlIOCM){bujWlXXLZE = true;}
      else if(nYFqwlIOCM == BBEMJmeQaM){tkEdIpWFdT = true;}
      if(bjrkUmKcKB == QWJfUHjWNr){VznwcuzUPH = true;}
      if(QMTEVnqgmw == xuZzQgSlbL){iFUhQxRTYp = true;}
      if(ztMemrDQFO == UOLKUbhVJd){tmQlBqnzeC = true;}
      while(QWJfUHjWNr == bjrkUmKcKB){wdZTdlzdic = true;}
      while(xuZzQgSlbL == xuZzQgSlbL){PrLPVUGzPn = true;}
      while(UOLKUbhVJd == UOLKUbhVJd){IdiErYOZAJ = true;}
      if(LUZagmttPL == true){LUZagmttPL = false;}
      if(lkuGhrzGZP == true){lkuGhrzGZP = false;}
      if(SVlpqCLyKs == true){SVlpqCLyKs = false;}
      if(YNNjfcVzRc == true){YNNjfcVzRc = false;}
      if(mXWQZjSFcc == true){mXWQZjSFcc = false;}
      if(cbwsKohiie == true){cbwsKohiie = false;}
      if(bujWlXXLZE == true){bujWlXXLZE = false;}
      if(VznwcuzUPH == true){VznwcuzUPH = false;}
      if(iFUhQxRTYp == true){iFUhQxRTYp = false;}
      if(tmQlBqnzeC == true){tmQlBqnzeC = false;}
      if(LGfXGcmzPP == true){LGfXGcmzPP = false;}
      if(pMTauVaBGn == true){pMTauVaBGn = false;}
      if(FDmiKihCul == true){FDmiKihCul = false;}
      if(HzpNwbZxbm == true){HzpNwbZxbm = false;}
      if(JSDIAgTppe == true){JSDIAgTppe = false;}
      if(QlspxHTwNW == true){QlspxHTwNW = false;}
      if(tkEdIpWFdT == true){tkEdIpWFdT = false;}
      if(wdZTdlzdic == true){wdZTdlzdic = false;}
      if(PrLPVUGzPn == true){PrLPVUGzPn = false;}
      if(IdiErYOZAJ == true){IdiErYOZAJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CXKWRLCTRH
{ 
  void HxuyHEaNud()
  { 
      bool SGHATCwQyV = false;
      bool dJomKoBCaW = false;
      bool BXaNoPuBDE = false;
      bool BxjMQgyVRB = false;
      bool lZkVXcVADV = false;
      bool OFUWBtetKE = false;
      bool HuMtTgYbVc = false;
      bool pfkZjbmFoL = false;
      bool ttyhowbNLW = false;
      bool BEKMsqMpBq = false;
      bool EsdZeiUumY = false;
      bool GZEyKNweEX = false;
      bool ELQzalUXgs = false;
      bool OxDyHAPXCG = false;
      bool bgalPbALCf = false;
      bool thldmsbeys = false;
      bool NwOsKJWGqJ = false;
      bool xXcywWkeiz = false;
      bool kJUAyfKYKO = false;
      bool XkZJreRgaG = false;
      string ISTwlkuJEj;
      string aAHOUpYKTb;
      string QYcUioQOLC;
      string OCidtZOddE;
      string JkCxKMukZm;
      string VDjlejpzNx;
      string UfyCUYRcUt;
      string bufPRfVeJV;
      string seoXgLRwyJ;
      string jOPgiclAcl;
      string tRPeLZWUUz;
      string NKorDoqaUJ;
      string GVdLJMezfo;
      string sVCWaaOJLG;
      string nwbzuZYXct;
      string kKeTeYnEVy;
      string uXneFrHSQc;
      string ZhOOUJtePi;
      string nGVlDhpiqC;
      string mKmNKQIwtD;
      if(ISTwlkuJEj == tRPeLZWUUz){SGHATCwQyV = true;}
      else if(tRPeLZWUUz == ISTwlkuJEj){EsdZeiUumY = true;}
      if(aAHOUpYKTb == NKorDoqaUJ){dJomKoBCaW = true;}
      else if(NKorDoqaUJ == aAHOUpYKTb){GZEyKNweEX = true;}
      if(QYcUioQOLC == GVdLJMezfo){BXaNoPuBDE = true;}
      else if(GVdLJMezfo == QYcUioQOLC){ELQzalUXgs = true;}
      if(OCidtZOddE == sVCWaaOJLG){BxjMQgyVRB = true;}
      else if(sVCWaaOJLG == OCidtZOddE){OxDyHAPXCG = true;}
      if(JkCxKMukZm == nwbzuZYXct){lZkVXcVADV = true;}
      else if(nwbzuZYXct == JkCxKMukZm){bgalPbALCf = true;}
      if(VDjlejpzNx == kKeTeYnEVy){OFUWBtetKE = true;}
      else if(kKeTeYnEVy == VDjlejpzNx){thldmsbeys = true;}
      if(UfyCUYRcUt == uXneFrHSQc){HuMtTgYbVc = true;}
      else if(uXneFrHSQc == UfyCUYRcUt){NwOsKJWGqJ = true;}
      if(bufPRfVeJV == ZhOOUJtePi){pfkZjbmFoL = true;}
      if(seoXgLRwyJ == nGVlDhpiqC){ttyhowbNLW = true;}
      if(jOPgiclAcl == mKmNKQIwtD){BEKMsqMpBq = true;}
      while(ZhOOUJtePi == bufPRfVeJV){xXcywWkeiz = true;}
      while(nGVlDhpiqC == nGVlDhpiqC){kJUAyfKYKO = true;}
      while(mKmNKQIwtD == mKmNKQIwtD){XkZJreRgaG = true;}
      if(SGHATCwQyV == true){SGHATCwQyV = false;}
      if(dJomKoBCaW == true){dJomKoBCaW = false;}
      if(BXaNoPuBDE == true){BXaNoPuBDE = false;}
      if(BxjMQgyVRB == true){BxjMQgyVRB = false;}
      if(lZkVXcVADV == true){lZkVXcVADV = false;}
      if(OFUWBtetKE == true){OFUWBtetKE = false;}
      if(HuMtTgYbVc == true){HuMtTgYbVc = false;}
      if(pfkZjbmFoL == true){pfkZjbmFoL = false;}
      if(ttyhowbNLW == true){ttyhowbNLW = false;}
      if(BEKMsqMpBq == true){BEKMsqMpBq = false;}
      if(EsdZeiUumY == true){EsdZeiUumY = false;}
      if(GZEyKNweEX == true){GZEyKNweEX = false;}
      if(ELQzalUXgs == true){ELQzalUXgs = false;}
      if(OxDyHAPXCG == true){OxDyHAPXCG = false;}
      if(bgalPbALCf == true){bgalPbALCf = false;}
      if(thldmsbeys == true){thldmsbeys = false;}
      if(NwOsKJWGqJ == true){NwOsKJWGqJ = false;}
      if(xXcywWkeiz == true){xXcywWkeiz = false;}
      if(kJUAyfKYKO == true){kJUAyfKYKO = false;}
      if(XkZJreRgaG == true){XkZJreRgaG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXKVVAYUUL
{ 
  void ubNaUjdgmx()
  { 
      bool dSemspMoWu = false;
      bool TiQXxxdrsc = false;
      bool RjxRkLfowD = false;
      bool LmIAoHJUSt = false;
      bool ScoRbtuYcU = false;
      bool PJfndsVNCg = false;
      bool KWrTifaPip = false;
      bool nIZzJoufpq = false;
      bool QGMbmCGTWu = false;
      bool luSliujUiu = false;
      bool SepmgHjgdn = false;
      bool xpXKPEKQff = false;
      bool YGsmEronPO = false;
      bool FZwtXkPZuf = false;
      bool SZpixuXIVe = false;
      bool kToCVLlDin = false;
      bool RuRPiXscle = false;
      bool nkVANzQKoI = false;
      bool TgRjckktYL = false;
      bool zMpGNWHazZ = false;
      string PuNCfauQyu;
      string OWwEKFOIMR;
      string oNkhjmRFWF;
      string nIOIoNpAuW;
      string amRFiHtDgs;
      string hKVZSCJeSs;
      string JotrHGHnOx;
      string PONopBwfyc;
      string rNXcXcloom;
      string EKhCMksYyc;
      string AGojdSxfjQ;
      string GdfoAwRQTd;
      string TSybsEgKbE;
      string IWgVckXnzE;
      string fFEYfZdrCQ;
      string TcEUIgIMpY;
      string llEeHjwKMO;
      string XcQPxNNYwS;
      string anILkeRMMu;
      string cLxaStBZQu;
      if(PuNCfauQyu == AGojdSxfjQ){dSemspMoWu = true;}
      else if(AGojdSxfjQ == PuNCfauQyu){SepmgHjgdn = true;}
      if(OWwEKFOIMR == GdfoAwRQTd){TiQXxxdrsc = true;}
      else if(GdfoAwRQTd == OWwEKFOIMR){xpXKPEKQff = true;}
      if(oNkhjmRFWF == TSybsEgKbE){RjxRkLfowD = true;}
      else if(TSybsEgKbE == oNkhjmRFWF){YGsmEronPO = true;}
      if(nIOIoNpAuW == IWgVckXnzE){LmIAoHJUSt = true;}
      else if(IWgVckXnzE == nIOIoNpAuW){FZwtXkPZuf = true;}
      if(amRFiHtDgs == fFEYfZdrCQ){ScoRbtuYcU = true;}
      else if(fFEYfZdrCQ == amRFiHtDgs){SZpixuXIVe = true;}
      if(hKVZSCJeSs == TcEUIgIMpY){PJfndsVNCg = true;}
      else if(TcEUIgIMpY == hKVZSCJeSs){kToCVLlDin = true;}
      if(JotrHGHnOx == llEeHjwKMO){KWrTifaPip = true;}
      else if(llEeHjwKMO == JotrHGHnOx){RuRPiXscle = true;}
      if(PONopBwfyc == XcQPxNNYwS){nIZzJoufpq = true;}
      if(rNXcXcloom == anILkeRMMu){QGMbmCGTWu = true;}
      if(EKhCMksYyc == cLxaStBZQu){luSliujUiu = true;}
      while(XcQPxNNYwS == PONopBwfyc){nkVANzQKoI = true;}
      while(anILkeRMMu == anILkeRMMu){TgRjckktYL = true;}
      while(cLxaStBZQu == cLxaStBZQu){zMpGNWHazZ = true;}
      if(dSemspMoWu == true){dSemspMoWu = false;}
      if(TiQXxxdrsc == true){TiQXxxdrsc = false;}
      if(RjxRkLfowD == true){RjxRkLfowD = false;}
      if(LmIAoHJUSt == true){LmIAoHJUSt = false;}
      if(ScoRbtuYcU == true){ScoRbtuYcU = false;}
      if(PJfndsVNCg == true){PJfndsVNCg = false;}
      if(KWrTifaPip == true){KWrTifaPip = false;}
      if(nIZzJoufpq == true){nIZzJoufpq = false;}
      if(QGMbmCGTWu == true){QGMbmCGTWu = false;}
      if(luSliujUiu == true){luSliujUiu = false;}
      if(SepmgHjgdn == true){SepmgHjgdn = false;}
      if(xpXKPEKQff == true){xpXKPEKQff = false;}
      if(YGsmEronPO == true){YGsmEronPO = false;}
      if(FZwtXkPZuf == true){FZwtXkPZuf = false;}
      if(SZpixuXIVe == true){SZpixuXIVe = false;}
      if(kToCVLlDin == true){kToCVLlDin = false;}
      if(RuRPiXscle == true){RuRPiXscle = false;}
      if(nkVANzQKoI == true){nkVANzQKoI = false;}
      if(TgRjckktYL == true){TgRjckktYL = false;}
      if(zMpGNWHazZ == true){zMpGNWHazZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSCAATCQIM
{ 
  void HYRasDmmzF()
  { 
      bool xPmPuLFPau = false;
      bool DlCkPUbHiz = false;
      bool pnUwtGoDWp = false;
      bool gXqlXlIsMg = false;
      bool fFpuSmHZHl = false;
      bool CtTWgJupVo = false;
      bool VBskOetQMc = false;
      bool LitCSjyZdG = false;
      bool zPwjnmETEO = false;
      bool qSWXKdMEgm = false;
      bool rpMdZTzRDx = false;
      bool LUMPpGFIwa = false;
      bool aaMylsLWqn = false;
      bool XsrpNICSKU = false;
      bool mlPHCVFHgE = false;
      bool YDIFMRdNqf = false;
      bool HcZOZScVCg = false;
      bool DmybnnKEwQ = false;
      bool mEolPTjldu = false;
      bool doadMKMBhj = false;
      string adCfUxkYXb;
      string DjtugZAifb;
      string KqNYejiVWh;
      string uEVUsmlZMM;
      string tyiPbwrHZj;
      string rADNNiQcBj;
      string NPCogzNZCt;
      string maVShMIxwh;
      string qawlouAIGJ;
      string VIYcydusib;
      string iSEewRdjeA;
      string aTgSsmSPAl;
      string yESrXeBsUD;
      string QONUzYVRoW;
      string QQdFiCbFjL;
      string LfswcdzMGR;
      string QkPajLFLST;
      string QAacVhaMJV;
      string CuJIrkVQqV;
      string ZJKWGeBCVX;
      if(adCfUxkYXb == iSEewRdjeA){xPmPuLFPau = true;}
      else if(iSEewRdjeA == adCfUxkYXb){rpMdZTzRDx = true;}
      if(DjtugZAifb == aTgSsmSPAl){DlCkPUbHiz = true;}
      else if(aTgSsmSPAl == DjtugZAifb){LUMPpGFIwa = true;}
      if(KqNYejiVWh == yESrXeBsUD){pnUwtGoDWp = true;}
      else if(yESrXeBsUD == KqNYejiVWh){aaMylsLWqn = true;}
      if(uEVUsmlZMM == QONUzYVRoW){gXqlXlIsMg = true;}
      else if(QONUzYVRoW == uEVUsmlZMM){XsrpNICSKU = true;}
      if(tyiPbwrHZj == QQdFiCbFjL){fFpuSmHZHl = true;}
      else if(QQdFiCbFjL == tyiPbwrHZj){mlPHCVFHgE = true;}
      if(rADNNiQcBj == LfswcdzMGR){CtTWgJupVo = true;}
      else if(LfswcdzMGR == rADNNiQcBj){YDIFMRdNqf = true;}
      if(NPCogzNZCt == QkPajLFLST){VBskOetQMc = true;}
      else if(QkPajLFLST == NPCogzNZCt){HcZOZScVCg = true;}
      if(maVShMIxwh == QAacVhaMJV){LitCSjyZdG = true;}
      if(qawlouAIGJ == CuJIrkVQqV){zPwjnmETEO = true;}
      if(VIYcydusib == ZJKWGeBCVX){qSWXKdMEgm = true;}
      while(QAacVhaMJV == maVShMIxwh){DmybnnKEwQ = true;}
      while(CuJIrkVQqV == CuJIrkVQqV){mEolPTjldu = true;}
      while(ZJKWGeBCVX == ZJKWGeBCVX){doadMKMBhj = true;}
      if(xPmPuLFPau == true){xPmPuLFPau = false;}
      if(DlCkPUbHiz == true){DlCkPUbHiz = false;}
      if(pnUwtGoDWp == true){pnUwtGoDWp = false;}
      if(gXqlXlIsMg == true){gXqlXlIsMg = false;}
      if(fFpuSmHZHl == true){fFpuSmHZHl = false;}
      if(CtTWgJupVo == true){CtTWgJupVo = false;}
      if(VBskOetQMc == true){VBskOetQMc = false;}
      if(LitCSjyZdG == true){LitCSjyZdG = false;}
      if(zPwjnmETEO == true){zPwjnmETEO = false;}
      if(qSWXKdMEgm == true){qSWXKdMEgm = false;}
      if(rpMdZTzRDx == true){rpMdZTzRDx = false;}
      if(LUMPpGFIwa == true){LUMPpGFIwa = false;}
      if(aaMylsLWqn == true){aaMylsLWqn = false;}
      if(XsrpNICSKU == true){XsrpNICSKU = false;}
      if(mlPHCVFHgE == true){mlPHCVFHgE = false;}
      if(YDIFMRdNqf == true){YDIFMRdNqf = false;}
      if(HcZOZScVCg == true){HcZOZScVCg = false;}
      if(DmybnnKEwQ == true){DmybnnKEwQ = false;}
      if(mEolPTjldu == true){mEolPTjldu = false;}
      if(doadMKMBhj == true){doadMKMBhj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HUMLERHUQG
{ 
  void fHIYQMAisP()
  { 
      bool xUKmNRqARZ = false;
      bool JXIOVdztgG = false;
      bool JEFlripYKF = false;
      bool ylNruCASqL = false;
      bool riXiTMmQLb = false;
      bool yGrNVsPXtd = false;
      bool aSpMaWKQST = false;
      bool dfDVNafVSf = false;
      bool wZMiGrszVC = false;
      bool mbYMjZrLIw = false;
      bool BWxqxSCWAu = false;
      bool MsEOhBFGFh = false;
      bool cKtPfBHpkm = false;
      bool hUNVdZbUkn = false;
      bool pWzaptWJeh = false;
      bool TkFZTqbhLw = false;
      bool KLlMMqehkI = false;
      bool YjVRrGLTYl = false;
      bool exLCTwOnCl = false;
      bool xtJocdjmOz = false;
      string JwaVeLBewt;
      string gHuIgYoCJw;
      string DkAXqSzMTR;
      string KmyTrujRwM;
      string jpHMRabsfp;
      string xgrmkYuDdL;
      string MoLejsIbQl;
      string nXGxLMdnGQ;
      string qFgcTduLiT;
      string zgmjAuecbX;
      string SzctBYauaX;
      string tHxNUHIhKG;
      string ywswlHjVwQ;
      string gBLhyqbmbt;
      string CzjKYrjZPr;
      string mxRVYVGfHt;
      string nEyKpsuOOc;
      string eUGQDzMhXs;
      string XKFEcjipIc;
      string kwehFxAZUf;
      if(JwaVeLBewt == SzctBYauaX){xUKmNRqARZ = true;}
      else if(SzctBYauaX == JwaVeLBewt){BWxqxSCWAu = true;}
      if(gHuIgYoCJw == tHxNUHIhKG){JXIOVdztgG = true;}
      else if(tHxNUHIhKG == gHuIgYoCJw){MsEOhBFGFh = true;}
      if(DkAXqSzMTR == ywswlHjVwQ){JEFlripYKF = true;}
      else if(ywswlHjVwQ == DkAXqSzMTR){cKtPfBHpkm = true;}
      if(KmyTrujRwM == gBLhyqbmbt){ylNruCASqL = true;}
      else if(gBLhyqbmbt == KmyTrujRwM){hUNVdZbUkn = true;}
      if(jpHMRabsfp == CzjKYrjZPr){riXiTMmQLb = true;}
      else if(CzjKYrjZPr == jpHMRabsfp){pWzaptWJeh = true;}
      if(xgrmkYuDdL == mxRVYVGfHt){yGrNVsPXtd = true;}
      else if(mxRVYVGfHt == xgrmkYuDdL){TkFZTqbhLw = true;}
      if(MoLejsIbQl == nEyKpsuOOc){aSpMaWKQST = true;}
      else if(nEyKpsuOOc == MoLejsIbQl){KLlMMqehkI = true;}
      if(nXGxLMdnGQ == eUGQDzMhXs){dfDVNafVSf = true;}
      if(qFgcTduLiT == XKFEcjipIc){wZMiGrszVC = true;}
      if(zgmjAuecbX == kwehFxAZUf){mbYMjZrLIw = true;}
      while(eUGQDzMhXs == nXGxLMdnGQ){YjVRrGLTYl = true;}
      while(XKFEcjipIc == XKFEcjipIc){exLCTwOnCl = true;}
      while(kwehFxAZUf == kwehFxAZUf){xtJocdjmOz = true;}
      if(xUKmNRqARZ == true){xUKmNRqARZ = false;}
      if(JXIOVdztgG == true){JXIOVdztgG = false;}
      if(JEFlripYKF == true){JEFlripYKF = false;}
      if(ylNruCASqL == true){ylNruCASqL = false;}
      if(riXiTMmQLb == true){riXiTMmQLb = false;}
      if(yGrNVsPXtd == true){yGrNVsPXtd = false;}
      if(aSpMaWKQST == true){aSpMaWKQST = false;}
      if(dfDVNafVSf == true){dfDVNafVSf = false;}
      if(wZMiGrszVC == true){wZMiGrszVC = false;}
      if(mbYMjZrLIw == true){mbYMjZrLIw = false;}
      if(BWxqxSCWAu == true){BWxqxSCWAu = false;}
      if(MsEOhBFGFh == true){MsEOhBFGFh = false;}
      if(cKtPfBHpkm == true){cKtPfBHpkm = false;}
      if(hUNVdZbUkn == true){hUNVdZbUkn = false;}
      if(pWzaptWJeh == true){pWzaptWJeh = false;}
      if(TkFZTqbhLw == true){TkFZTqbhLw = false;}
      if(KLlMMqehkI == true){KLlMMqehkI = false;}
      if(YjVRrGLTYl == true){YjVRrGLTYl = false;}
      if(exLCTwOnCl == true){exLCTwOnCl = false;}
      if(xtJocdjmOz == true){xtJocdjmOz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGTGONCTBY
{ 
  void YSQWnrYsIi()
  { 
      bool OChixBehHQ = false;
      bool seOWYOAncR = false;
      bool GpyNEProqp = false;
      bool OSyPhRdeVu = false;
      bool kdPXrYABdP = false;
      bool EeBwPXDUeh = false;
      bool JopRCZfynG = false;
      bool jVRhgbaZUe = false;
      bool OpLakiQCAJ = false;
      bool OJAnlunxVR = false;
      bool sCMWeiMTOm = false;
      bool xczzTTdPfT = false;
      bool JdyeraVdwl = false;
      bool ndEClMcnwC = false;
      bool VxmMMkKAUR = false;
      bool QXQBIPDhdE = false;
      bool NiXczSXwNG = false;
      bool poSdyLpkRG = false;
      bool QUJdUPMDtW = false;
      bool IuJqomZJNs = false;
      string RpVGmDXgBM;
      string lbOInbDHWR;
      string FjKtLgSZnx;
      string KydlHwuCDF;
      string ZFkSxqfbll;
      string VXThUheauG;
      string jxrEBnybAq;
      string fADQqzyqxU;
      string AqnCamduRZ;
      string QUHxVbMgQI;
      string sDatFUTCpU;
      string jncaFsJocN;
      string JCKaZLsFuP;
      string mQZnbxPsxG;
      string SbFwocqgrb;
      string RWECzprAUt;
      string aOHahSNnyI;
      string dQrVuhxNlx;
      string UMNTxPMWok;
      string EOYDeETeOV;
      if(RpVGmDXgBM == sDatFUTCpU){OChixBehHQ = true;}
      else if(sDatFUTCpU == RpVGmDXgBM){sCMWeiMTOm = true;}
      if(lbOInbDHWR == jncaFsJocN){seOWYOAncR = true;}
      else if(jncaFsJocN == lbOInbDHWR){xczzTTdPfT = true;}
      if(FjKtLgSZnx == JCKaZLsFuP){GpyNEProqp = true;}
      else if(JCKaZLsFuP == FjKtLgSZnx){JdyeraVdwl = true;}
      if(KydlHwuCDF == mQZnbxPsxG){OSyPhRdeVu = true;}
      else if(mQZnbxPsxG == KydlHwuCDF){ndEClMcnwC = true;}
      if(ZFkSxqfbll == SbFwocqgrb){kdPXrYABdP = true;}
      else if(SbFwocqgrb == ZFkSxqfbll){VxmMMkKAUR = true;}
      if(VXThUheauG == RWECzprAUt){EeBwPXDUeh = true;}
      else if(RWECzprAUt == VXThUheauG){QXQBIPDhdE = true;}
      if(jxrEBnybAq == aOHahSNnyI){JopRCZfynG = true;}
      else if(aOHahSNnyI == jxrEBnybAq){NiXczSXwNG = true;}
      if(fADQqzyqxU == dQrVuhxNlx){jVRhgbaZUe = true;}
      if(AqnCamduRZ == UMNTxPMWok){OpLakiQCAJ = true;}
      if(QUHxVbMgQI == EOYDeETeOV){OJAnlunxVR = true;}
      while(dQrVuhxNlx == fADQqzyqxU){poSdyLpkRG = true;}
      while(UMNTxPMWok == UMNTxPMWok){QUJdUPMDtW = true;}
      while(EOYDeETeOV == EOYDeETeOV){IuJqomZJNs = true;}
      if(OChixBehHQ == true){OChixBehHQ = false;}
      if(seOWYOAncR == true){seOWYOAncR = false;}
      if(GpyNEProqp == true){GpyNEProqp = false;}
      if(OSyPhRdeVu == true){OSyPhRdeVu = false;}
      if(kdPXrYABdP == true){kdPXrYABdP = false;}
      if(EeBwPXDUeh == true){EeBwPXDUeh = false;}
      if(JopRCZfynG == true){JopRCZfynG = false;}
      if(jVRhgbaZUe == true){jVRhgbaZUe = false;}
      if(OpLakiQCAJ == true){OpLakiQCAJ = false;}
      if(OJAnlunxVR == true){OJAnlunxVR = false;}
      if(sCMWeiMTOm == true){sCMWeiMTOm = false;}
      if(xczzTTdPfT == true){xczzTTdPfT = false;}
      if(JdyeraVdwl == true){JdyeraVdwl = false;}
      if(ndEClMcnwC == true){ndEClMcnwC = false;}
      if(VxmMMkKAUR == true){VxmMMkKAUR = false;}
      if(QXQBIPDhdE == true){QXQBIPDhdE = false;}
      if(NiXczSXwNG == true){NiXczSXwNG = false;}
      if(poSdyLpkRG == true){poSdyLpkRG = false;}
      if(QUJdUPMDtW == true){QUJdUPMDtW = false;}
      if(IuJqomZJNs == true){IuJqomZJNs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFCZZDIDJM
{ 
  void xyuAdMHTYH()
  { 
      bool YqJxKUgkwn = false;
      bool HWdokNjLUp = false;
      bool mUuSkuVTLn = false;
      bool aJeCOUCJUy = false;
      bool BVzfEqJXIG = false;
      bool OxiYmDuqMP = false;
      bool yMYINxqbaQ = false;
      bool LZqVoRVPNs = false;
      bool kyLEYcZFOK = false;
      bool YLxEAowpRG = false;
      bool zhxqunFMjV = false;
      bool hfcSeAATjk = false;
      bool XkNPrzclVz = false;
      bool VexGtDATJj = false;
      bool WNUrcshdZz = false;
      bool nbGgiNThzu = false;
      bool LTpkAChVYa = false;
      bool AgKzNJPUlz = false;
      bool RyLWLsYPXf = false;
      bool iSUNYDWjra = false;
      string HyTgbcBWFa;
      string cszPoMeZFR;
      string sSMIGMuYID;
      string OccXcYbbrH;
      string KOyWHtcsYB;
      string ecNVgnlKZP;
      string hbNBMzPamQ;
      string jDgyHeUoBM;
      string iCAHXkPHqn;
      string lQCcZhBwKI;
      string dCGIQbuPOC;
      string SwJNffbFdb;
      string jHjydSBEYY;
      string dYeshgwrqw;
      string oAsnUpHnxs;
      string FuSiXVSHdx;
      string aqpoYtRQez;
      string ijOgljOucn;
      string LMHeThGwUM;
      string OnNtUyJEPa;
      if(HyTgbcBWFa == dCGIQbuPOC){YqJxKUgkwn = true;}
      else if(dCGIQbuPOC == HyTgbcBWFa){zhxqunFMjV = true;}
      if(cszPoMeZFR == SwJNffbFdb){HWdokNjLUp = true;}
      else if(SwJNffbFdb == cszPoMeZFR){hfcSeAATjk = true;}
      if(sSMIGMuYID == jHjydSBEYY){mUuSkuVTLn = true;}
      else if(jHjydSBEYY == sSMIGMuYID){XkNPrzclVz = true;}
      if(OccXcYbbrH == dYeshgwrqw){aJeCOUCJUy = true;}
      else if(dYeshgwrqw == OccXcYbbrH){VexGtDATJj = true;}
      if(KOyWHtcsYB == oAsnUpHnxs){BVzfEqJXIG = true;}
      else if(oAsnUpHnxs == KOyWHtcsYB){WNUrcshdZz = true;}
      if(ecNVgnlKZP == FuSiXVSHdx){OxiYmDuqMP = true;}
      else if(FuSiXVSHdx == ecNVgnlKZP){nbGgiNThzu = true;}
      if(hbNBMzPamQ == aqpoYtRQez){yMYINxqbaQ = true;}
      else if(aqpoYtRQez == hbNBMzPamQ){LTpkAChVYa = true;}
      if(jDgyHeUoBM == ijOgljOucn){LZqVoRVPNs = true;}
      if(iCAHXkPHqn == LMHeThGwUM){kyLEYcZFOK = true;}
      if(lQCcZhBwKI == OnNtUyJEPa){YLxEAowpRG = true;}
      while(ijOgljOucn == jDgyHeUoBM){AgKzNJPUlz = true;}
      while(LMHeThGwUM == LMHeThGwUM){RyLWLsYPXf = true;}
      while(OnNtUyJEPa == OnNtUyJEPa){iSUNYDWjra = true;}
      if(YqJxKUgkwn == true){YqJxKUgkwn = false;}
      if(HWdokNjLUp == true){HWdokNjLUp = false;}
      if(mUuSkuVTLn == true){mUuSkuVTLn = false;}
      if(aJeCOUCJUy == true){aJeCOUCJUy = false;}
      if(BVzfEqJXIG == true){BVzfEqJXIG = false;}
      if(OxiYmDuqMP == true){OxiYmDuqMP = false;}
      if(yMYINxqbaQ == true){yMYINxqbaQ = false;}
      if(LZqVoRVPNs == true){LZqVoRVPNs = false;}
      if(kyLEYcZFOK == true){kyLEYcZFOK = false;}
      if(YLxEAowpRG == true){YLxEAowpRG = false;}
      if(zhxqunFMjV == true){zhxqunFMjV = false;}
      if(hfcSeAATjk == true){hfcSeAATjk = false;}
      if(XkNPrzclVz == true){XkNPrzclVz = false;}
      if(VexGtDATJj == true){VexGtDATJj = false;}
      if(WNUrcshdZz == true){WNUrcshdZz = false;}
      if(nbGgiNThzu == true){nbGgiNThzu = false;}
      if(LTpkAChVYa == true){LTpkAChVYa = false;}
      if(AgKzNJPUlz == true){AgKzNJPUlz = false;}
      if(RyLWLsYPXf == true){RyLWLsYPXf = false;}
      if(iSUNYDWjra == true){iSUNYDWjra = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CIWBJWIXSS
{ 
  void bxDoxKZhUj()
  { 
      bool urJBaybZIm = false;
      bool ezwUtjZiFS = false;
      bool LjYZIJdbyl = false;
      bool SsregBbuyn = false;
      bool PUYURnJIlU = false;
      bool NEesWLTjsR = false;
      bool UAaWUlGRnr = false;
      bool HdjRCpKDHU = false;
      bool zUpdYOOzHU = false;
      bool hrCfSPtCAe = false;
      bool gqUsMiTMpf = false;
      bool BPbXSzJxxF = false;
      bool XHKSKPaDym = false;
      bool wHDcmHzxRo = false;
      bool tBIaTRPdNS = false;
      bool FxEuGZgChx = false;
      bool HPNDisMzkK = false;
      bool AMfIKWyizr = false;
      bool zxpfhzDHVM = false;
      bool axOTgdnFqZ = false;
      string joBKJZeXap;
      string CGhuEblcYP;
      string IcUQKxNkRg;
      string bfiqZRuJxj;
      string hSAiRmXiYo;
      string RyMTeGUjzM;
      string LtFsOVWpVl;
      string fbfngpckzW;
      string YeLcPdTPMS;
      string xLJjXnMGTw;
      string QhNlIoSXln;
      string cikcmghbdk;
      string BHcCoUSuPs;
      string cWRDGqRZUa;
      string KudXoNZfxq;
      string GjbitIEKwn;
      string VXHsLGRhWu;
      string PHHCZGdFNb;
      string tlxYmrthIx;
      string mGdfEmmkMi;
      if(joBKJZeXap == QhNlIoSXln){urJBaybZIm = true;}
      else if(QhNlIoSXln == joBKJZeXap){gqUsMiTMpf = true;}
      if(CGhuEblcYP == cikcmghbdk){ezwUtjZiFS = true;}
      else if(cikcmghbdk == CGhuEblcYP){BPbXSzJxxF = true;}
      if(IcUQKxNkRg == BHcCoUSuPs){LjYZIJdbyl = true;}
      else if(BHcCoUSuPs == IcUQKxNkRg){XHKSKPaDym = true;}
      if(bfiqZRuJxj == cWRDGqRZUa){SsregBbuyn = true;}
      else if(cWRDGqRZUa == bfiqZRuJxj){wHDcmHzxRo = true;}
      if(hSAiRmXiYo == KudXoNZfxq){PUYURnJIlU = true;}
      else if(KudXoNZfxq == hSAiRmXiYo){tBIaTRPdNS = true;}
      if(RyMTeGUjzM == GjbitIEKwn){NEesWLTjsR = true;}
      else if(GjbitIEKwn == RyMTeGUjzM){FxEuGZgChx = true;}
      if(LtFsOVWpVl == VXHsLGRhWu){UAaWUlGRnr = true;}
      else if(VXHsLGRhWu == LtFsOVWpVl){HPNDisMzkK = true;}
      if(fbfngpckzW == PHHCZGdFNb){HdjRCpKDHU = true;}
      if(YeLcPdTPMS == tlxYmrthIx){zUpdYOOzHU = true;}
      if(xLJjXnMGTw == mGdfEmmkMi){hrCfSPtCAe = true;}
      while(PHHCZGdFNb == fbfngpckzW){AMfIKWyizr = true;}
      while(tlxYmrthIx == tlxYmrthIx){zxpfhzDHVM = true;}
      while(mGdfEmmkMi == mGdfEmmkMi){axOTgdnFqZ = true;}
      if(urJBaybZIm == true){urJBaybZIm = false;}
      if(ezwUtjZiFS == true){ezwUtjZiFS = false;}
      if(LjYZIJdbyl == true){LjYZIJdbyl = false;}
      if(SsregBbuyn == true){SsregBbuyn = false;}
      if(PUYURnJIlU == true){PUYURnJIlU = false;}
      if(NEesWLTjsR == true){NEesWLTjsR = false;}
      if(UAaWUlGRnr == true){UAaWUlGRnr = false;}
      if(HdjRCpKDHU == true){HdjRCpKDHU = false;}
      if(zUpdYOOzHU == true){zUpdYOOzHU = false;}
      if(hrCfSPtCAe == true){hrCfSPtCAe = false;}
      if(gqUsMiTMpf == true){gqUsMiTMpf = false;}
      if(BPbXSzJxxF == true){BPbXSzJxxF = false;}
      if(XHKSKPaDym == true){XHKSKPaDym = false;}
      if(wHDcmHzxRo == true){wHDcmHzxRo = false;}
      if(tBIaTRPdNS == true){tBIaTRPdNS = false;}
      if(FxEuGZgChx == true){FxEuGZgChx = false;}
      if(HPNDisMzkK == true){HPNDisMzkK = false;}
      if(AMfIKWyizr == true){AMfIKWyizr = false;}
      if(zxpfhzDHVM == true){zxpfhzDHVM = false;}
      if(axOTgdnFqZ == true){axOTgdnFqZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIGZMNTKXL
{ 
  void hdfIOkzdFj()
  { 
      bool HbdaBQwjVZ = false;
      bool bXEiaGijQM = false;
      bool lJHGjnRGhs = false;
      bool iUXJSPJqKN = false;
      bool FLWwzOibJQ = false;
      bool kmEbSxTXqN = false;
      bool ypCbqHztPK = false;
      bool xrYDHZlLGU = false;
      bool FoxRHuPwqU = false;
      bool wkzxOOJuFr = false;
      bool OnMySsNBUr = false;
      bool KIRWHJskUu = false;
      bool qDDuOLrbnr = false;
      bool QqFNGQcyyO = false;
      bool gNayJnTcoF = false;
      bool VYaJAKjQjH = false;
      bool AlMbbTCDPp = false;
      bool ftlFOcbFka = false;
      bool rOmiVqPwMu = false;
      bool gLOqNtBzVp = false;
      string Xfmkiakmmy;
      string UGNquSdeaM;
      string UCAwmJNcYA;
      string UpPleVfmTZ;
      string yxBAlRfiRD;
      string ldkgcVfqyZ;
      string NIOlceqbLZ;
      string lpKANXBzJU;
      string deLUOqEiJI;
      string pnotLphOWG;
      string aEWrQuSkSE;
      string UfhcwiwtXl;
      string ZHSCiyAQoX;
      string olcDtYHTDS;
      string XTQEnJGMyc;
      string smpjfSlTIS;
      string uCwtOhCehW;
      string bcqFOGpNOZ;
      string rnSLdCwsWb;
      string mmLjXUXVoF;
      if(Xfmkiakmmy == aEWrQuSkSE){HbdaBQwjVZ = true;}
      else if(aEWrQuSkSE == Xfmkiakmmy){OnMySsNBUr = true;}
      if(UGNquSdeaM == UfhcwiwtXl){bXEiaGijQM = true;}
      else if(UfhcwiwtXl == UGNquSdeaM){KIRWHJskUu = true;}
      if(UCAwmJNcYA == ZHSCiyAQoX){lJHGjnRGhs = true;}
      else if(ZHSCiyAQoX == UCAwmJNcYA){qDDuOLrbnr = true;}
      if(UpPleVfmTZ == olcDtYHTDS){iUXJSPJqKN = true;}
      else if(olcDtYHTDS == UpPleVfmTZ){QqFNGQcyyO = true;}
      if(yxBAlRfiRD == XTQEnJGMyc){FLWwzOibJQ = true;}
      else if(XTQEnJGMyc == yxBAlRfiRD){gNayJnTcoF = true;}
      if(ldkgcVfqyZ == smpjfSlTIS){kmEbSxTXqN = true;}
      else if(smpjfSlTIS == ldkgcVfqyZ){VYaJAKjQjH = true;}
      if(NIOlceqbLZ == uCwtOhCehW){ypCbqHztPK = true;}
      else if(uCwtOhCehW == NIOlceqbLZ){AlMbbTCDPp = true;}
      if(lpKANXBzJU == bcqFOGpNOZ){xrYDHZlLGU = true;}
      if(deLUOqEiJI == rnSLdCwsWb){FoxRHuPwqU = true;}
      if(pnotLphOWG == mmLjXUXVoF){wkzxOOJuFr = true;}
      while(bcqFOGpNOZ == lpKANXBzJU){ftlFOcbFka = true;}
      while(rnSLdCwsWb == rnSLdCwsWb){rOmiVqPwMu = true;}
      while(mmLjXUXVoF == mmLjXUXVoF){gLOqNtBzVp = true;}
      if(HbdaBQwjVZ == true){HbdaBQwjVZ = false;}
      if(bXEiaGijQM == true){bXEiaGijQM = false;}
      if(lJHGjnRGhs == true){lJHGjnRGhs = false;}
      if(iUXJSPJqKN == true){iUXJSPJqKN = false;}
      if(FLWwzOibJQ == true){FLWwzOibJQ = false;}
      if(kmEbSxTXqN == true){kmEbSxTXqN = false;}
      if(ypCbqHztPK == true){ypCbqHztPK = false;}
      if(xrYDHZlLGU == true){xrYDHZlLGU = false;}
      if(FoxRHuPwqU == true){FoxRHuPwqU = false;}
      if(wkzxOOJuFr == true){wkzxOOJuFr = false;}
      if(OnMySsNBUr == true){OnMySsNBUr = false;}
      if(KIRWHJskUu == true){KIRWHJskUu = false;}
      if(qDDuOLrbnr == true){qDDuOLrbnr = false;}
      if(QqFNGQcyyO == true){QqFNGQcyyO = false;}
      if(gNayJnTcoF == true){gNayJnTcoF = false;}
      if(VYaJAKjQjH == true){VYaJAKjQjH = false;}
      if(AlMbbTCDPp == true){AlMbbTCDPp = false;}
      if(ftlFOcbFka == true){ftlFOcbFka = false;}
      if(rOmiVqPwMu == true){rOmiVqPwMu = false;}
      if(gLOqNtBzVp == true){gLOqNtBzVp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMYWHBBYUR
{ 
  void BnZOENphzo()
  { 
      bool TAFfVzRSrF = false;
      bool HTylIXsoKz = false;
      bool SzTpBIgbUd = false;
      bool VbREVBBJTF = false;
      bool EtLViIBzDT = false;
      bool MoXLRTfPdN = false;
      bool SpyNjfCsQG = false;
      bool WjUFtXmyHs = false;
      bool GgXARfDFmB = false;
      bool VkeGmOwylC = false;
      bool FHixxbURQs = false;
      bool fhIkGkSxuE = false;
      bool cwGOkkEOSf = false;
      bool boMEmzxaCp = false;
      bool LkosUnctzB = false;
      bool uyDgZJAULM = false;
      bool XFzjRqVDyG = false;
      bool mruFsqHMtw = false;
      bool HJPRkcleed = false;
      bool ycOpRFlEbd = false;
      string kEIsXsqAZV;
      string XAbRuSdSsG;
      string GDkhPjSJJs;
      string WDBgWaxGDA;
      string hJuBkbCmHc;
      string wysNxhTZcm;
      string ahqfyUzttT;
      string UWPsXwIixm;
      string heBfwXJnio;
      string HXcPYzSOCQ;
      string cHrnIYizoB;
      string YjbpFugLjZ;
      string KKKEMxtzTY;
      string dsfgJZmNXW;
      string oKzhQWumKd;
      string SGecFSxmaK;
      string eieQWfDuge;
      string ISnMkAKcno;
      string BHopFWNDap;
      string czlMrGeiKj;
      if(kEIsXsqAZV == cHrnIYizoB){TAFfVzRSrF = true;}
      else if(cHrnIYizoB == kEIsXsqAZV){FHixxbURQs = true;}
      if(XAbRuSdSsG == YjbpFugLjZ){HTylIXsoKz = true;}
      else if(YjbpFugLjZ == XAbRuSdSsG){fhIkGkSxuE = true;}
      if(GDkhPjSJJs == KKKEMxtzTY){SzTpBIgbUd = true;}
      else if(KKKEMxtzTY == GDkhPjSJJs){cwGOkkEOSf = true;}
      if(WDBgWaxGDA == dsfgJZmNXW){VbREVBBJTF = true;}
      else if(dsfgJZmNXW == WDBgWaxGDA){boMEmzxaCp = true;}
      if(hJuBkbCmHc == oKzhQWumKd){EtLViIBzDT = true;}
      else if(oKzhQWumKd == hJuBkbCmHc){LkosUnctzB = true;}
      if(wysNxhTZcm == SGecFSxmaK){MoXLRTfPdN = true;}
      else if(SGecFSxmaK == wysNxhTZcm){uyDgZJAULM = true;}
      if(ahqfyUzttT == eieQWfDuge){SpyNjfCsQG = true;}
      else if(eieQWfDuge == ahqfyUzttT){XFzjRqVDyG = true;}
      if(UWPsXwIixm == ISnMkAKcno){WjUFtXmyHs = true;}
      if(heBfwXJnio == BHopFWNDap){GgXARfDFmB = true;}
      if(HXcPYzSOCQ == czlMrGeiKj){VkeGmOwylC = true;}
      while(ISnMkAKcno == UWPsXwIixm){mruFsqHMtw = true;}
      while(BHopFWNDap == BHopFWNDap){HJPRkcleed = true;}
      while(czlMrGeiKj == czlMrGeiKj){ycOpRFlEbd = true;}
      if(TAFfVzRSrF == true){TAFfVzRSrF = false;}
      if(HTylIXsoKz == true){HTylIXsoKz = false;}
      if(SzTpBIgbUd == true){SzTpBIgbUd = false;}
      if(VbREVBBJTF == true){VbREVBBJTF = false;}
      if(EtLViIBzDT == true){EtLViIBzDT = false;}
      if(MoXLRTfPdN == true){MoXLRTfPdN = false;}
      if(SpyNjfCsQG == true){SpyNjfCsQG = false;}
      if(WjUFtXmyHs == true){WjUFtXmyHs = false;}
      if(GgXARfDFmB == true){GgXARfDFmB = false;}
      if(VkeGmOwylC == true){VkeGmOwylC = false;}
      if(FHixxbURQs == true){FHixxbURQs = false;}
      if(fhIkGkSxuE == true){fhIkGkSxuE = false;}
      if(cwGOkkEOSf == true){cwGOkkEOSf = false;}
      if(boMEmzxaCp == true){boMEmzxaCp = false;}
      if(LkosUnctzB == true){LkosUnctzB = false;}
      if(uyDgZJAULM == true){uyDgZJAULM = false;}
      if(XFzjRqVDyG == true){XFzjRqVDyG = false;}
      if(mruFsqHMtw == true){mruFsqHMtw = false;}
      if(HJPRkcleed == true){HJPRkcleed = false;}
      if(ycOpRFlEbd == true){ycOpRFlEbd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMOMGNGWSC
{ 
  void DPIFPMRLZx()
  { 
      bool enhWwVpqjc = false;
      bool DEpNEZRbDP = false;
      bool HpKrsKLNUY = false;
      bool SMryJjjOhL = false;
      bool JaTncZrcCZ = false;
      bool QeHRHndocl = false;
      bool JcVLKqMqEU = false;
      bool pCtqGgWWPT = false;
      bool RiKuHmFZpU = false;
      bool GulwBgEHdl = false;
      bool MAXhjOkPKZ = false;
      bool RGZITZRaEW = false;
      bool klAiNuPxpZ = false;
      bool cOscHRLcKs = false;
      bool BoPQCzUdbb = false;
      bool OdDGAZznTo = false;
      bool ymZkxDNxBC = false;
      bool OnPKUwWjfN = false;
      bool ZlVNKzKlcg = false;
      bool RWJVtNPeTz = false;
      string WCiaySNhQe;
      string XzUDRVgbdA;
      string CKfbtHwGXp;
      string PyyZGmTUSp;
      string aaDzQswDwU;
      string esLOBMWHgq;
      string WGJaOZBuxe;
      string BMImZbHfKA;
      string KrKDLVliXt;
      string QMmbTUQcjp;
      string rBGQSRjYoZ;
      string EpwggewFPs;
      string mRWCOoYgSE;
      string KeuUHIlsks;
      string lMtxoZPGuo;
      string XKMqDadDCd;
      string rDFjPZtbYX;
      string rCUVGZWZNn;
      string YRldgzREQg;
      string dhpHAhHKhP;
      if(WCiaySNhQe == rBGQSRjYoZ){enhWwVpqjc = true;}
      else if(rBGQSRjYoZ == WCiaySNhQe){MAXhjOkPKZ = true;}
      if(XzUDRVgbdA == EpwggewFPs){DEpNEZRbDP = true;}
      else if(EpwggewFPs == XzUDRVgbdA){RGZITZRaEW = true;}
      if(CKfbtHwGXp == mRWCOoYgSE){HpKrsKLNUY = true;}
      else if(mRWCOoYgSE == CKfbtHwGXp){klAiNuPxpZ = true;}
      if(PyyZGmTUSp == KeuUHIlsks){SMryJjjOhL = true;}
      else if(KeuUHIlsks == PyyZGmTUSp){cOscHRLcKs = true;}
      if(aaDzQswDwU == lMtxoZPGuo){JaTncZrcCZ = true;}
      else if(lMtxoZPGuo == aaDzQswDwU){BoPQCzUdbb = true;}
      if(esLOBMWHgq == XKMqDadDCd){QeHRHndocl = true;}
      else if(XKMqDadDCd == esLOBMWHgq){OdDGAZznTo = true;}
      if(WGJaOZBuxe == rDFjPZtbYX){JcVLKqMqEU = true;}
      else if(rDFjPZtbYX == WGJaOZBuxe){ymZkxDNxBC = true;}
      if(BMImZbHfKA == rCUVGZWZNn){pCtqGgWWPT = true;}
      if(KrKDLVliXt == YRldgzREQg){RiKuHmFZpU = true;}
      if(QMmbTUQcjp == dhpHAhHKhP){GulwBgEHdl = true;}
      while(rCUVGZWZNn == BMImZbHfKA){OnPKUwWjfN = true;}
      while(YRldgzREQg == YRldgzREQg){ZlVNKzKlcg = true;}
      while(dhpHAhHKhP == dhpHAhHKhP){RWJVtNPeTz = true;}
      if(enhWwVpqjc == true){enhWwVpqjc = false;}
      if(DEpNEZRbDP == true){DEpNEZRbDP = false;}
      if(HpKrsKLNUY == true){HpKrsKLNUY = false;}
      if(SMryJjjOhL == true){SMryJjjOhL = false;}
      if(JaTncZrcCZ == true){JaTncZrcCZ = false;}
      if(QeHRHndocl == true){QeHRHndocl = false;}
      if(JcVLKqMqEU == true){JcVLKqMqEU = false;}
      if(pCtqGgWWPT == true){pCtqGgWWPT = false;}
      if(RiKuHmFZpU == true){RiKuHmFZpU = false;}
      if(GulwBgEHdl == true){GulwBgEHdl = false;}
      if(MAXhjOkPKZ == true){MAXhjOkPKZ = false;}
      if(RGZITZRaEW == true){RGZITZRaEW = false;}
      if(klAiNuPxpZ == true){klAiNuPxpZ = false;}
      if(cOscHRLcKs == true){cOscHRLcKs = false;}
      if(BoPQCzUdbb == true){BoPQCzUdbb = false;}
      if(OdDGAZznTo == true){OdDGAZznTo = false;}
      if(ymZkxDNxBC == true){ymZkxDNxBC = false;}
      if(OnPKUwWjfN == true){OnPKUwWjfN = false;}
      if(ZlVNKzKlcg == true){ZlVNKzKlcg = false;}
      if(RWJVtNPeTz == true){RWJVtNPeTz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSDLZEOSDV
{ 
  void bXRhblBHLL()
  { 
      bool RTrzPUGRak = false;
      bool DdNyAaQQDX = false;
      bool QOaKacWymy = false;
      bool PIegKFFdzU = false;
      bool CHYsYVTUpT = false;
      bool xxnnOCrhXm = false;
      bool yHecUuzgnt = false;
      bool VlRiVIpgkF = false;
      bool IBITBSUpSI = false;
      bool NWGLWtcwYd = false;
      bool VmguxKfFSF = false;
      bool LKwRewzLaC = false;
      bool aINfgyfFLa = false;
      bool fsIHiUUNVq = false;
      bool lOXMwCanga = false;
      bool uRVWCMYBNz = false;
      bool dZsqZSCohJ = false;
      bool aloiPLkBie = false;
      bool XrYkfNXlEW = false;
      bool uSzVMLVflc = false;
      string qZnVecSbjA;
      string GnusdWYXMG;
      string FCaIdErFgI;
      string bTXbZjCsxc;
      string JxbeaGabcr;
      string jXEruozfra;
      string jMtaXmQSSs;
      string UfaixIZugW;
      string dQcnYEOegk;
      string kWBWswCBHm;
      string oHIiXExUtm;
      string ODyUxSjGCT;
      string XklhIxeDoB;
      string FYnsgVIsQT;
      string HtktVgXfZa;
      string LwzmPEVZZZ;
      string ZsesgpPEma;
      string KpohMdAqMb;
      string YycOoJYAdc;
      string zhTptNOqMe;
      if(qZnVecSbjA == oHIiXExUtm){RTrzPUGRak = true;}
      else if(oHIiXExUtm == qZnVecSbjA){VmguxKfFSF = true;}
      if(GnusdWYXMG == ODyUxSjGCT){DdNyAaQQDX = true;}
      else if(ODyUxSjGCT == GnusdWYXMG){LKwRewzLaC = true;}
      if(FCaIdErFgI == XklhIxeDoB){QOaKacWymy = true;}
      else if(XklhIxeDoB == FCaIdErFgI){aINfgyfFLa = true;}
      if(bTXbZjCsxc == FYnsgVIsQT){PIegKFFdzU = true;}
      else if(FYnsgVIsQT == bTXbZjCsxc){fsIHiUUNVq = true;}
      if(JxbeaGabcr == HtktVgXfZa){CHYsYVTUpT = true;}
      else if(HtktVgXfZa == JxbeaGabcr){lOXMwCanga = true;}
      if(jXEruozfra == LwzmPEVZZZ){xxnnOCrhXm = true;}
      else if(LwzmPEVZZZ == jXEruozfra){uRVWCMYBNz = true;}
      if(jMtaXmQSSs == ZsesgpPEma){yHecUuzgnt = true;}
      else if(ZsesgpPEma == jMtaXmQSSs){dZsqZSCohJ = true;}
      if(UfaixIZugW == KpohMdAqMb){VlRiVIpgkF = true;}
      if(dQcnYEOegk == YycOoJYAdc){IBITBSUpSI = true;}
      if(kWBWswCBHm == zhTptNOqMe){NWGLWtcwYd = true;}
      while(KpohMdAqMb == UfaixIZugW){aloiPLkBie = true;}
      while(YycOoJYAdc == YycOoJYAdc){XrYkfNXlEW = true;}
      while(zhTptNOqMe == zhTptNOqMe){uSzVMLVflc = true;}
      if(RTrzPUGRak == true){RTrzPUGRak = false;}
      if(DdNyAaQQDX == true){DdNyAaQQDX = false;}
      if(QOaKacWymy == true){QOaKacWymy = false;}
      if(PIegKFFdzU == true){PIegKFFdzU = false;}
      if(CHYsYVTUpT == true){CHYsYVTUpT = false;}
      if(xxnnOCrhXm == true){xxnnOCrhXm = false;}
      if(yHecUuzgnt == true){yHecUuzgnt = false;}
      if(VlRiVIpgkF == true){VlRiVIpgkF = false;}
      if(IBITBSUpSI == true){IBITBSUpSI = false;}
      if(NWGLWtcwYd == true){NWGLWtcwYd = false;}
      if(VmguxKfFSF == true){VmguxKfFSF = false;}
      if(LKwRewzLaC == true){LKwRewzLaC = false;}
      if(aINfgyfFLa == true){aINfgyfFLa = false;}
      if(fsIHiUUNVq == true){fsIHiUUNVq = false;}
      if(lOXMwCanga == true){lOXMwCanga = false;}
      if(uRVWCMYBNz == true){uRVWCMYBNz = false;}
      if(dZsqZSCohJ == true){dZsqZSCohJ = false;}
      if(aloiPLkBie == true){aloiPLkBie = false;}
      if(XrYkfNXlEW == true){XrYkfNXlEW = false;}
      if(uSzVMLVflc == true){uSzVMLVflc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWGROOVJEN
{ 
  void UMaAyPKUpd()
  { 
      bool dbJGfeqwGO = false;
      bool UkGennHZXL = false;
      bool TVwPWzZDGA = false;
      bool SFOIrAlBhm = false;
      bool MfgGFSACqJ = false;
      bool NOJrPHesjf = false;
      bool FnpGwOWxlm = false;
      bool CFrkzmopJD = false;
      bool zXLwmEwVsj = false;
      bool UrRBhYpZKp = false;
      bool uDPDHHWYsb = false;
      bool SoifggbsTq = false;
      bool SBDCRJnpCZ = false;
      bool xOeSHwIIne = false;
      bool hWbRQfJkUB = false;
      bool xwGSXtzMly = false;
      bool SfWTdEJPXk = false;
      bool YTEnJwZlll = false;
      bool ACVBcAHMuN = false;
      bool wuWpMBAHmM = false;
      string rGOIjKBLSJ;
      string uowWGqqMfo;
      string zChEUyYVyT;
      string JxCrtkPQDi;
      string HRliEKxyeO;
      string FPiecoXKmk;
      string lfNzAylEbV;
      string bZIwhhPzzK;
      string BapiNsOWPE;
      string MFdRxbEmiG;
      string YsVJmfHlxt;
      string YYKcjLodlG;
      string jOnXIWwqzF;
      string dcPrkIEgug;
      string kbZUemtAhl;
      string mZAbWJEyAQ;
      string iQmqQwJRqa;
      string GHhEUHnSrV;
      string cuINSEbmVa;
      string EGgeyUnhEi;
      if(rGOIjKBLSJ == YsVJmfHlxt){dbJGfeqwGO = true;}
      else if(YsVJmfHlxt == rGOIjKBLSJ){uDPDHHWYsb = true;}
      if(uowWGqqMfo == YYKcjLodlG){UkGennHZXL = true;}
      else if(YYKcjLodlG == uowWGqqMfo){SoifggbsTq = true;}
      if(zChEUyYVyT == jOnXIWwqzF){TVwPWzZDGA = true;}
      else if(jOnXIWwqzF == zChEUyYVyT){SBDCRJnpCZ = true;}
      if(JxCrtkPQDi == dcPrkIEgug){SFOIrAlBhm = true;}
      else if(dcPrkIEgug == JxCrtkPQDi){xOeSHwIIne = true;}
      if(HRliEKxyeO == kbZUemtAhl){MfgGFSACqJ = true;}
      else if(kbZUemtAhl == HRliEKxyeO){hWbRQfJkUB = true;}
      if(FPiecoXKmk == mZAbWJEyAQ){NOJrPHesjf = true;}
      else if(mZAbWJEyAQ == FPiecoXKmk){xwGSXtzMly = true;}
      if(lfNzAylEbV == iQmqQwJRqa){FnpGwOWxlm = true;}
      else if(iQmqQwJRqa == lfNzAylEbV){SfWTdEJPXk = true;}
      if(bZIwhhPzzK == GHhEUHnSrV){CFrkzmopJD = true;}
      if(BapiNsOWPE == cuINSEbmVa){zXLwmEwVsj = true;}
      if(MFdRxbEmiG == EGgeyUnhEi){UrRBhYpZKp = true;}
      while(GHhEUHnSrV == bZIwhhPzzK){YTEnJwZlll = true;}
      while(cuINSEbmVa == cuINSEbmVa){ACVBcAHMuN = true;}
      while(EGgeyUnhEi == EGgeyUnhEi){wuWpMBAHmM = true;}
      if(dbJGfeqwGO == true){dbJGfeqwGO = false;}
      if(UkGennHZXL == true){UkGennHZXL = false;}
      if(TVwPWzZDGA == true){TVwPWzZDGA = false;}
      if(SFOIrAlBhm == true){SFOIrAlBhm = false;}
      if(MfgGFSACqJ == true){MfgGFSACqJ = false;}
      if(NOJrPHesjf == true){NOJrPHesjf = false;}
      if(FnpGwOWxlm == true){FnpGwOWxlm = false;}
      if(CFrkzmopJD == true){CFrkzmopJD = false;}
      if(zXLwmEwVsj == true){zXLwmEwVsj = false;}
      if(UrRBhYpZKp == true){UrRBhYpZKp = false;}
      if(uDPDHHWYsb == true){uDPDHHWYsb = false;}
      if(SoifggbsTq == true){SoifggbsTq = false;}
      if(SBDCRJnpCZ == true){SBDCRJnpCZ = false;}
      if(xOeSHwIIne == true){xOeSHwIIne = false;}
      if(hWbRQfJkUB == true){hWbRQfJkUB = false;}
      if(xwGSXtzMly == true){xwGSXtzMly = false;}
      if(SfWTdEJPXk == true){SfWTdEJPXk = false;}
      if(YTEnJwZlll == true){YTEnJwZlll = false;}
      if(ACVBcAHMuN == true){ACVBcAHMuN = false;}
      if(wuWpMBAHmM == true){wuWpMBAHmM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LLEAMTMJJG
{ 
  void ENkqbMQkaw()
  { 
      bool PVOYdYWdVJ = false;
      bool AOGLAgoPXx = false;
      bool WqLYkIIjny = false;
      bool QoPrtpmwyj = false;
      bool DsGqhhrOSP = false;
      bool CoLfkYKomV = false;
      bool PlpXrKzORJ = false;
      bool tsRmtcjUqD = false;
      bool PsRYwadjGV = false;
      bool fxIcTQDiyW = false;
      bool idwIUIXYkI = false;
      bool noxjGWTQaR = false;
      bool gOHwdwjnSc = false;
      bool YBVUTkxJDm = false;
      bool CEzygpzYVx = false;
      bool wlHgoUWAdY = false;
      bool YiFHilTcPU = false;
      bool YKNnObPIOm = false;
      bool wLSUgltnez = false;
      bool OxeeOSzqPt = false;
      string LZmMRAyoGg;
      string ETQgWeVNzk;
      string jHaKgXTHTB;
      string AcRAqoGOoi;
      string ecljbORBwg;
      string OLXDdEycft;
      string gqVEfaCQph;
      string YHXPFGUqhS;
      string GRKmmoFNWl;
      string pciuBnHgDB;
      string MBKNHGmHyW;
      string iHtMmOfhRq;
      string UnsDruXcOR;
      string znngFEHwef;
      string ByPADiiVHl;
      string HZPLfXHHVM;
      string iKrgWuSMHi;
      string HiCkpWXsAJ;
      string MBUcJZXbAh;
      string xzaSwqFicH;
      if(LZmMRAyoGg == MBKNHGmHyW){PVOYdYWdVJ = true;}
      else if(MBKNHGmHyW == LZmMRAyoGg){idwIUIXYkI = true;}
      if(ETQgWeVNzk == iHtMmOfhRq){AOGLAgoPXx = true;}
      else if(iHtMmOfhRq == ETQgWeVNzk){noxjGWTQaR = true;}
      if(jHaKgXTHTB == UnsDruXcOR){WqLYkIIjny = true;}
      else if(UnsDruXcOR == jHaKgXTHTB){gOHwdwjnSc = true;}
      if(AcRAqoGOoi == znngFEHwef){QoPrtpmwyj = true;}
      else if(znngFEHwef == AcRAqoGOoi){YBVUTkxJDm = true;}
      if(ecljbORBwg == ByPADiiVHl){DsGqhhrOSP = true;}
      else if(ByPADiiVHl == ecljbORBwg){CEzygpzYVx = true;}
      if(OLXDdEycft == HZPLfXHHVM){CoLfkYKomV = true;}
      else if(HZPLfXHHVM == OLXDdEycft){wlHgoUWAdY = true;}
      if(gqVEfaCQph == iKrgWuSMHi){PlpXrKzORJ = true;}
      else if(iKrgWuSMHi == gqVEfaCQph){YiFHilTcPU = true;}
      if(YHXPFGUqhS == HiCkpWXsAJ){tsRmtcjUqD = true;}
      if(GRKmmoFNWl == MBUcJZXbAh){PsRYwadjGV = true;}
      if(pciuBnHgDB == xzaSwqFicH){fxIcTQDiyW = true;}
      while(HiCkpWXsAJ == YHXPFGUqhS){YKNnObPIOm = true;}
      while(MBUcJZXbAh == MBUcJZXbAh){wLSUgltnez = true;}
      while(xzaSwqFicH == xzaSwqFicH){OxeeOSzqPt = true;}
      if(PVOYdYWdVJ == true){PVOYdYWdVJ = false;}
      if(AOGLAgoPXx == true){AOGLAgoPXx = false;}
      if(WqLYkIIjny == true){WqLYkIIjny = false;}
      if(QoPrtpmwyj == true){QoPrtpmwyj = false;}
      if(DsGqhhrOSP == true){DsGqhhrOSP = false;}
      if(CoLfkYKomV == true){CoLfkYKomV = false;}
      if(PlpXrKzORJ == true){PlpXrKzORJ = false;}
      if(tsRmtcjUqD == true){tsRmtcjUqD = false;}
      if(PsRYwadjGV == true){PsRYwadjGV = false;}
      if(fxIcTQDiyW == true){fxIcTQDiyW = false;}
      if(idwIUIXYkI == true){idwIUIXYkI = false;}
      if(noxjGWTQaR == true){noxjGWTQaR = false;}
      if(gOHwdwjnSc == true){gOHwdwjnSc = false;}
      if(YBVUTkxJDm == true){YBVUTkxJDm = false;}
      if(CEzygpzYVx == true){CEzygpzYVx = false;}
      if(wlHgoUWAdY == true){wlHgoUWAdY = false;}
      if(YiFHilTcPU == true){YiFHilTcPU = false;}
      if(YKNnObPIOm == true){YKNnObPIOm = false;}
      if(wLSUgltnez == true){wLSUgltnez = false;}
      if(OxeeOSzqPt == true){OxeeOSzqPt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKKXZEXZLX
{ 
  void QZMTOSLFbD()
  { 
      bool ROZduCWUSH = false;
      bool SnNNILOKIX = false;
      bool tjmprBCXNn = false;
      bool bDhmptLjZE = false;
      bool WArrGkHwmg = false;
      bool mXuZdgaiks = false;
      bool zyGefOGZXN = false;
      bool zdkDBtrtjH = false;
      bool tFkgADHHJI = false;
      bool SbyfEXsNMr = false;
      bool dgXYgJmrYj = false;
      bool ogzczsNYdb = false;
      bool GyQOuXfEyd = false;
      bool AdgrdMhMAq = false;
      bool PPiZSlcUgK = false;
      bool KTjjkfQIcJ = false;
      bool cisuiKzHzl = false;
      bool LBYlMpOqwJ = false;
      bool tKXmSftxGx = false;
      bool wYiqOgWnpH = false;
      string dejBZXZIXN;
      string cywhqzzGhw;
      string AyPPkypLmP;
      string aURegrdUkN;
      string UreQCijYox;
      string CIlMKfOTQa;
      string gOVImIgRAy;
      string UeUTbHTzMB;
      string NRVoMRhETB;
      string cJDJgGWWds;
      string CSXpcXmSkD;
      string MPHONPrfuU;
      string abxzULaKlU;
      string kwUTzusfMo;
      string dPTQnMCowR;
      string OpaJSZVYVQ;
      string xcfPSPunPS;
      string VLTGpKHgLH;
      string IkOUGtVLAY;
      string ZUJurBiEyX;
      if(dejBZXZIXN == CSXpcXmSkD){ROZduCWUSH = true;}
      else if(CSXpcXmSkD == dejBZXZIXN){dgXYgJmrYj = true;}
      if(cywhqzzGhw == MPHONPrfuU){SnNNILOKIX = true;}
      else if(MPHONPrfuU == cywhqzzGhw){ogzczsNYdb = true;}
      if(AyPPkypLmP == abxzULaKlU){tjmprBCXNn = true;}
      else if(abxzULaKlU == AyPPkypLmP){GyQOuXfEyd = true;}
      if(aURegrdUkN == kwUTzusfMo){bDhmptLjZE = true;}
      else if(kwUTzusfMo == aURegrdUkN){AdgrdMhMAq = true;}
      if(UreQCijYox == dPTQnMCowR){WArrGkHwmg = true;}
      else if(dPTQnMCowR == UreQCijYox){PPiZSlcUgK = true;}
      if(CIlMKfOTQa == OpaJSZVYVQ){mXuZdgaiks = true;}
      else if(OpaJSZVYVQ == CIlMKfOTQa){KTjjkfQIcJ = true;}
      if(gOVImIgRAy == xcfPSPunPS){zyGefOGZXN = true;}
      else if(xcfPSPunPS == gOVImIgRAy){cisuiKzHzl = true;}
      if(UeUTbHTzMB == VLTGpKHgLH){zdkDBtrtjH = true;}
      if(NRVoMRhETB == IkOUGtVLAY){tFkgADHHJI = true;}
      if(cJDJgGWWds == ZUJurBiEyX){SbyfEXsNMr = true;}
      while(VLTGpKHgLH == UeUTbHTzMB){LBYlMpOqwJ = true;}
      while(IkOUGtVLAY == IkOUGtVLAY){tKXmSftxGx = true;}
      while(ZUJurBiEyX == ZUJurBiEyX){wYiqOgWnpH = true;}
      if(ROZduCWUSH == true){ROZduCWUSH = false;}
      if(SnNNILOKIX == true){SnNNILOKIX = false;}
      if(tjmprBCXNn == true){tjmprBCXNn = false;}
      if(bDhmptLjZE == true){bDhmptLjZE = false;}
      if(WArrGkHwmg == true){WArrGkHwmg = false;}
      if(mXuZdgaiks == true){mXuZdgaiks = false;}
      if(zyGefOGZXN == true){zyGefOGZXN = false;}
      if(zdkDBtrtjH == true){zdkDBtrtjH = false;}
      if(tFkgADHHJI == true){tFkgADHHJI = false;}
      if(SbyfEXsNMr == true){SbyfEXsNMr = false;}
      if(dgXYgJmrYj == true){dgXYgJmrYj = false;}
      if(ogzczsNYdb == true){ogzczsNYdb = false;}
      if(GyQOuXfEyd == true){GyQOuXfEyd = false;}
      if(AdgrdMhMAq == true){AdgrdMhMAq = false;}
      if(PPiZSlcUgK == true){PPiZSlcUgK = false;}
      if(KTjjkfQIcJ == true){KTjjkfQIcJ = false;}
      if(cisuiKzHzl == true){cisuiKzHzl = false;}
      if(LBYlMpOqwJ == true){LBYlMpOqwJ = false;}
      if(tKXmSftxGx == true){tKXmSftxGx = false;}
      if(wYiqOgWnpH == true){wYiqOgWnpH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBDCSLMRXL
{ 
  void oeJCADtwcG()
  { 
      bool LfDmxoQKeL = false;
      bool RLiiOFmFcN = false;
      bool nIWozilVte = false;
      bool fhMkFuYcNK = false;
      bool ImrfimqZWV = false;
      bool ouTyfDJNnN = false;
      bool DtPAeiyydT = false;
      bool fJrRFAQpGL = false;
      bool rLzYpkOOEC = false;
      bool kKozHNXrAz = false;
      bool oswCoeCBrf = false;
      bool mTHbVrtqJt = false;
      bool UjsaiVTrKq = false;
      bool cXpHWzOxiL = false;
      bool hMVYPRDMcO = false;
      bool TfhGdEzUTS = false;
      bool KJqADOczFW = false;
      bool cxHyLIOULQ = false;
      bool SGPuXwpjcR = false;
      bool ztcPAXUUVA = false;
      string lJuQqVCrAp;
      string aYgBCkJVGw;
      string njiTkNnZSM;
      string QbgYWJUKyL;
      string ThxzppSbEc;
      string BdbroCabfd;
      string hbZnZyrIes;
      string PzXtcFmjct;
      string tLVoKlzniU;
      string isdUcqIJZr;
      string yKxKMCGhOj;
      string PpykiWGjcm;
      string zDYJJVUCQl;
      string xdKkujNKbH;
      string fRYzFrtslG;
      string kXflsukmBp;
      string gDQcmkfNoy;
      string JuHVHgdZER;
      string bbQKAYxXqA;
      string zZJkabAwMT;
      if(lJuQqVCrAp == yKxKMCGhOj){LfDmxoQKeL = true;}
      else if(yKxKMCGhOj == lJuQqVCrAp){oswCoeCBrf = true;}
      if(aYgBCkJVGw == PpykiWGjcm){RLiiOFmFcN = true;}
      else if(PpykiWGjcm == aYgBCkJVGw){mTHbVrtqJt = true;}
      if(njiTkNnZSM == zDYJJVUCQl){nIWozilVte = true;}
      else if(zDYJJVUCQl == njiTkNnZSM){UjsaiVTrKq = true;}
      if(QbgYWJUKyL == xdKkujNKbH){fhMkFuYcNK = true;}
      else if(xdKkujNKbH == QbgYWJUKyL){cXpHWzOxiL = true;}
      if(ThxzppSbEc == fRYzFrtslG){ImrfimqZWV = true;}
      else if(fRYzFrtslG == ThxzppSbEc){hMVYPRDMcO = true;}
      if(BdbroCabfd == kXflsukmBp){ouTyfDJNnN = true;}
      else if(kXflsukmBp == BdbroCabfd){TfhGdEzUTS = true;}
      if(hbZnZyrIes == gDQcmkfNoy){DtPAeiyydT = true;}
      else if(gDQcmkfNoy == hbZnZyrIes){KJqADOczFW = true;}
      if(PzXtcFmjct == JuHVHgdZER){fJrRFAQpGL = true;}
      if(tLVoKlzniU == bbQKAYxXqA){rLzYpkOOEC = true;}
      if(isdUcqIJZr == zZJkabAwMT){kKozHNXrAz = true;}
      while(JuHVHgdZER == PzXtcFmjct){cxHyLIOULQ = true;}
      while(bbQKAYxXqA == bbQKAYxXqA){SGPuXwpjcR = true;}
      while(zZJkabAwMT == zZJkabAwMT){ztcPAXUUVA = true;}
      if(LfDmxoQKeL == true){LfDmxoQKeL = false;}
      if(RLiiOFmFcN == true){RLiiOFmFcN = false;}
      if(nIWozilVte == true){nIWozilVte = false;}
      if(fhMkFuYcNK == true){fhMkFuYcNK = false;}
      if(ImrfimqZWV == true){ImrfimqZWV = false;}
      if(ouTyfDJNnN == true){ouTyfDJNnN = false;}
      if(DtPAeiyydT == true){DtPAeiyydT = false;}
      if(fJrRFAQpGL == true){fJrRFAQpGL = false;}
      if(rLzYpkOOEC == true){rLzYpkOOEC = false;}
      if(kKozHNXrAz == true){kKozHNXrAz = false;}
      if(oswCoeCBrf == true){oswCoeCBrf = false;}
      if(mTHbVrtqJt == true){mTHbVrtqJt = false;}
      if(UjsaiVTrKq == true){UjsaiVTrKq = false;}
      if(cXpHWzOxiL == true){cXpHWzOxiL = false;}
      if(hMVYPRDMcO == true){hMVYPRDMcO = false;}
      if(TfhGdEzUTS == true){TfhGdEzUTS = false;}
      if(KJqADOczFW == true){KJqADOczFW = false;}
      if(cxHyLIOULQ == true){cxHyLIOULQ = false;}
      if(SGPuXwpjcR == true){SGPuXwpjcR = false;}
      if(ztcPAXUUVA == true){ztcPAXUUVA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCJPSKGNOH
{ 
  void oggSEezJXF()
  { 
      bool bMXAxRMwxy = false;
      bool GwiRhQuuke = false;
      bool SCQzwWTxnp = false;
      bool CLgOCDDwNV = false;
      bool gWTIGSycWd = false;
      bool YhnHzYuXDZ = false;
      bool yPIGutOTOd = false;
      bool MygOywiIsd = false;
      bool YpZKRTWZPd = false;
      bool HfrmXROMML = false;
      bool DdOrQZBZJD = false;
      bool omdZBHoyoa = false;
      bool WoEkWgGspg = false;
      bool gWuhZtbhsr = false;
      bool SxPLnTCRlQ = false;
      bool bQXknNZdVj = false;
      bool THicVSrwAH = false;
      bool fHExHZYrwC = false;
      bool enHZEQyKsL = false;
      bool TyLJYLNmoV = false;
      string LIZkZAXmYD;
      string IVjPuRMgiQ;
      string zWOomEqBjI;
      string UqsHhgbzXO;
      string JVSLKFalkl;
      string QJnALotkyU;
      string IWCPhRcbgN;
      string pMJTHcDCdg;
      string dEPyrLDrur;
      string mqBCGmTDds;
      string cyFXwEzTsi;
      string lqHQqDGEXW;
      string OjgnayLHNT;
      string JzXjEfzrCn;
      string LiyMFuijKC;
      string fOfHdrQRwx;
      string rrGYZmTWMK;
      string EOCiKfkUhe;
      string PawLntTQGM;
      string OhuEuTcZmS;
      if(LIZkZAXmYD == cyFXwEzTsi){bMXAxRMwxy = true;}
      else if(cyFXwEzTsi == LIZkZAXmYD){DdOrQZBZJD = true;}
      if(IVjPuRMgiQ == lqHQqDGEXW){GwiRhQuuke = true;}
      else if(lqHQqDGEXW == IVjPuRMgiQ){omdZBHoyoa = true;}
      if(zWOomEqBjI == OjgnayLHNT){SCQzwWTxnp = true;}
      else if(OjgnayLHNT == zWOomEqBjI){WoEkWgGspg = true;}
      if(UqsHhgbzXO == JzXjEfzrCn){CLgOCDDwNV = true;}
      else if(JzXjEfzrCn == UqsHhgbzXO){gWuhZtbhsr = true;}
      if(JVSLKFalkl == LiyMFuijKC){gWTIGSycWd = true;}
      else if(LiyMFuijKC == JVSLKFalkl){SxPLnTCRlQ = true;}
      if(QJnALotkyU == fOfHdrQRwx){YhnHzYuXDZ = true;}
      else if(fOfHdrQRwx == QJnALotkyU){bQXknNZdVj = true;}
      if(IWCPhRcbgN == rrGYZmTWMK){yPIGutOTOd = true;}
      else if(rrGYZmTWMK == IWCPhRcbgN){THicVSrwAH = true;}
      if(pMJTHcDCdg == EOCiKfkUhe){MygOywiIsd = true;}
      if(dEPyrLDrur == PawLntTQGM){YpZKRTWZPd = true;}
      if(mqBCGmTDds == OhuEuTcZmS){HfrmXROMML = true;}
      while(EOCiKfkUhe == pMJTHcDCdg){fHExHZYrwC = true;}
      while(PawLntTQGM == PawLntTQGM){enHZEQyKsL = true;}
      while(OhuEuTcZmS == OhuEuTcZmS){TyLJYLNmoV = true;}
      if(bMXAxRMwxy == true){bMXAxRMwxy = false;}
      if(GwiRhQuuke == true){GwiRhQuuke = false;}
      if(SCQzwWTxnp == true){SCQzwWTxnp = false;}
      if(CLgOCDDwNV == true){CLgOCDDwNV = false;}
      if(gWTIGSycWd == true){gWTIGSycWd = false;}
      if(YhnHzYuXDZ == true){YhnHzYuXDZ = false;}
      if(yPIGutOTOd == true){yPIGutOTOd = false;}
      if(MygOywiIsd == true){MygOywiIsd = false;}
      if(YpZKRTWZPd == true){YpZKRTWZPd = false;}
      if(HfrmXROMML == true){HfrmXROMML = false;}
      if(DdOrQZBZJD == true){DdOrQZBZJD = false;}
      if(omdZBHoyoa == true){omdZBHoyoa = false;}
      if(WoEkWgGspg == true){WoEkWgGspg = false;}
      if(gWuhZtbhsr == true){gWuhZtbhsr = false;}
      if(SxPLnTCRlQ == true){SxPLnTCRlQ = false;}
      if(bQXknNZdVj == true){bQXknNZdVj = false;}
      if(THicVSrwAH == true){THicVSrwAH = false;}
      if(fHExHZYrwC == true){fHExHZYrwC = false;}
      if(enHZEQyKsL == true){enHZEQyKsL = false;}
      if(TyLJYLNmoV == true){TyLJYLNmoV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKLNLVBKWT
{ 
  void NOnjNZWkyi()
  { 
      bool PZmiBWZcSA = false;
      bool LxVFhRzezY = false;
      bool tKsrKuzLYO = false;
      bool tWoTAxLGcI = false;
      bool OuiVSNFrAC = false;
      bool iZQbkFfuYG = false;
      bool XNDEFoHBEj = false;
      bool FsBpJzbXYx = false;
      bool oHKWeUFNhu = false;
      bool QQhWkBrdQc = false;
      bool FEmPwpYaRl = false;
      bool cIVbQQCgYj = false;
      bool jtSIToLdEI = false;
      bool GxHwqkTtZo = false;
      bool wewuSHuGGU = false;
      bool yKEfsLkdwH = false;
      bool etVIfeBZje = false;
      bool xIHimFxWpL = false;
      bool tFXjJwsaCf = false;
      bool zoyRKCImPm = false;
      string ByGOwpCtsn;
      string VLMmpilNYf;
      string ypPkDfDzIC;
      string MgzUYpuTqd;
      string pnrMCsljPE;
      string qFGWhLiUKP;
      string mClpanLrNA;
      string mRVtoKxDiK;
      string tTjEKGaclN;
      string HaJaqnBCkN;
      string gtVPQZiMgW;
      string OekzVTSheU;
      string NhFAsMItCB;
      string IuSVczxUmk;
      string WOuOzboJFX;
      string UTWQzynVVE;
      string QoJeNSMPWV;
      string VxtsxzmpAQ;
      string WzoefoYBVe;
      string LayhUhEPAf;
      if(ByGOwpCtsn == gtVPQZiMgW){PZmiBWZcSA = true;}
      else if(gtVPQZiMgW == ByGOwpCtsn){FEmPwpYaRl = true;}
      if(VLMmpilNYf == OekzVTSheU){LxVFhRzezY = true;}
      else if(OekzVTSheU == VLMmpilNYf){cIVbQQCgYj = true;}
      if(ypPkDfDzIC == NhFAsMItCB){tKsrKuzLYO = true;}
      else if(NhFAsMItCB == ypPkDfDzIC){jtSIToLdEI = true;}
      if(MgzUYpuTqd == IuSVczxUmk){tWoTAxLGcI = true;}
      else if(IuSVczxUmk == MgzUYpuTqd){GxHwqkTtZo = true;}
      if(pnrMCsljPE == WOuOzboJFX){OuiVSNFrAC = true;}
      else if(WOuOzboJFX == pnrMCsljPE){wewuSHuGGU = true;}
      if(qFGWhLiUKP == UTWQzynVVE){iZQbkFfuYG = true;}
      else if(UTWQzynVVE == qFGWhLiUKP){yKEfsLkdwH = true;}
      if(mClpanLrNA == QoJeNSMPWV){XNDEFoHBEj = true;}
      else if(QoJeNSMPWV == mClpanLrNA){etVIfeBZje = true;}
      if(mRVtoKxDiK == VxtsxzmpAQ){FsBpJzbXYx = true;}
      if(tTjEKGaclN == WzoefoYBVe){oHKWeUFNhu = true;}
      if(HaJaqnBCkN == LayhUhEPAf){QQhWkBrdQc = true;}
      while(VxtsxzmpAQ == mRVtoKxDiK){xIHimFxWpL = true;}
      while(WzoefoYBVe == WzoefoYBVe){tFXjJwsaCf = true;}
      while(LayhUhEPAf == LayhUhEPAf){zoyRKCImPm = true;}
      if(PZmiBWZcSA == true){PZmiBWZcSA = false;}
      if(LxVFhRzezY == true){LxVFhRzezY = false;}
      if(tKsrKuzLYO == true){tKsrKuzLYO = false;}
      if(tWoTAxLGcI == true){tWoTAxLGcI = false;}
      if(OuiVSNFrAC == true){OuiVSNFrAC = false;}
      if(iZQbkFfuYG == true){iZQbkFfuYG = false;}
      if(XNDEFoHBEj == true){XNDEFoHBEj = false;}
      if(FsBpJzbXYx == true){FsBpJzbXYx = false;}
      if(oHKWeUFNhu == true){oHKWeUFNhu = false;}
      if(QQhWkBrdQc == true){QQhWkBrdQc = false;}
      if(FEmPwpYaRl == true){FEmPwpYaRl = false;}
      if(cIVbQQCgYj == true){cIVbQQCgYj = false;}
      if(jtSIToLdEI == true){jtSIToLdEI = false;}
      if(GxHwqkTtZo == true){GxHwqkTtZo = false;}
      if(wewuSHuGGU == true){wewuSHuGGU = false;}
      if(yKEfsLkdwH == true){yKEfsLkdwH = false;}
      if(etVIfeBZje == true){etVIfeBZje = false;}
      if(xIHimFxWpL == true){xIHimFxWpL = false;}
      if(tFXjJwsaCf == true){tFXjJwsaCf = false;}
      if(zoyRKCImPm == true){zoyRKCImPm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSWJKZXPFN
{ 
  void gwamfJzCHO()
  { 
      bool mQmQrXDSLB = false;
      bool wpCHmPoYLj = false;
      bool ziKzsKJnhB = false;
      bool CioUCrcctf = false;
      bool sGYHjMXmPx = false;
      bool UxmjhDGnWh = false;
      bool OPkJyNAgEt = false;
      bool lMefpsKDPg = false;
      bool mWYkfFuFly = false;
      bool loFMQdVOIV = false;
      bool LphUKISHso = false;
      bool sCYpurqAcs = false;
      bool RuuFIxGSOM = false;
      bool XutsUwnDZX = false;
      bool mnLxFiQORY = false;
      bool mUkPEQubMN = false;
      bool BArgRxHfVy = false;
      bool DmZFFcjyAY = false;
      bool grAoYCJdoE = false;
      bool BMpMVlwdfH = false;
      string OSsHaHqsim;
      string MSQNbrqyOE;
      string sEEWZLtKNd;
      string wtJdfwKscF;
      string CQKTCkxyZX;
      string QMjyDJNWgO;
      string MfeEpSIlge;
      string hxVICctkTn;
      string OwkoNjKLaW;
      string inMNsWkFcj;
      string cKQtpSpawZ;
      string ObDrAQtppF;
      string IxKKwtkHPf;
      string roHjLDfqzu;
      string siPBHGjTNc;
      string buOXaeAFxw;
      string giLPgZTTfw;
      string jDquLZhJDp;
      string JQslExZjIg;
      string DZtCNKWzTh;
      if(OSsHaHqsim == cKQtpSpawZ){mQmQrXDSLB = true;}
      else if(cKQtpSpawZ == OSsHaHqsim){LphUKISHso = true;}
      if(MSQNbrqyOE == ObDrAQtppF){wpCHmPoYLj = true;}
      else if(ObDrAQtppF == MSQNbrqyOE){sCYpurqAcs = true;}
      if(sEEWZLtKNd == IxKKwtkHPf){ziKzsKJnhB = true;}
      else if(IxKKwtkHPf == sEEWZLtKNd){RuuFIxGSOM = true;}
      if(wtJdfwKscF == roHjLDfqzu){CioUCrcctf = true;}
      else if(roHjLDfqzu == wtJdfwKscF){XutsUwnDZX = true;}
      if(CQKTCkxyZX == siPBHGjTNc){sGYHjMXmPx = true;}
      else if(siPBHGjTNc == CQKTCkxyZX){mnLxFiQORY = true;}
      if(QMjyDJNWgO == buOXaeAFxw){UxmjhDGnWh = true;}
      else if(buOXaeAFxw == QMjyDJNWgO){mUkPEQubMN = true;}
      if(MfeEpSIlge == giLPgZTTfw){OPkJyNAgEt = true;}
      else if(giLPgZTTfw == MfeEpSIlge){BArgRxHfVy = true;}
      if(hxVICctkTn == jDquLZhJDp){lMefpsKDPg = true;}
      if(OwkoNjKLaW == JQslExZjIg){mWYkfFuFly = true;}
      if(inMNsWkFcj == DZtCNKWzTh){loFMQdVOIV = true;}
      while(jDquLZhJDp == hxVICctkTn){DmZFFcjyAY = true;}
      while(JQslExZjIg == JQslExZjIg){grAoYCJdoE = true;}
      while(DZtCNKWzTh == DZtCNKWzTh){BMpMVlwdfH = true;}
      if(mQmQrXDSLB == true){mQmQrXDSLB = false;}
      if(wpCHmPoYLj == true){wpCHmPoYLj = false;}
      if(ziKzsKJnhB == true){ziKzsKJnhB = false;}
      if(CioUCrcctf == true){CioUCrcctf = false;}
      if(sGYHjMXmPx == true){sGYHjMXmPx = false;}
      if(UxmjhDGnWh == true){UxmjhDGnWh = false;}
      if(OPkJyNAgEt == true){OPkJyNAgEt = false;}
      if(lMefpsKDPg == true){lMefpsKDPg = false;}
      if(mWYkfFuFly == true){mWYkfFuFly = false;}
      if(loFMQdVOIV == true){loFMQdVOIV = false;}
      if(LphUKISHso == true){LphUKISHso = false;}
      if(sCYpurqAcs == true){sCYpurqAcs = false;}
      if(RuuFIxGSOM == true){RuuFIxGSOM = false;}
      if(XutsUwnDZX == true){XutsUwnDZX = false;}
      if(mnLxFiQORY == true){mnLxFiQORY = false;}
      if(mUkPEQubMN == true){mUkPEQubMN = false;}
      if(BArgRxHfVy == true){BArgRxHfVy = false;}
      if(DmZFFcjyAY == true){DmZFFcjyAY = false;}
      if(grAoYCJdoE == true){grAoYCJdoE = false;}
      if(BMpMVlwdfH == true){BMpMVlwdfH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFEXZAJFCR
{ 
  void kcVffslBXc()
  { 
      bool LGazhwhcnZ = false;
      bool wwVKsZsWGw = false;
      bool tzxPeZDRzG = false;
      bool cCDrNfNgVa = false;
      bool OUuHbmBNUg = false;
      bool RlyqjMILTI = false;
      bool sPdhwtrdwM = false;
      bool LMBegYEomr = false;
      bool YoxRopDMIB = false;
      bool WCNMgyqMKh = false;
      bool tWRHUFkSJK = false;
      bool HSYbjDSLsF = false;
      bool qfVtpJznxi = false;
      bool gqeExBXoxj = false;
      bool FjCxsEdlcd = false;
      bool efTEqOBWRL = false;
      bool GxUacQnTdh = false;
      bool edOIAGdXAl = false;
      bool fMKTDAWZNi = false;
      bool AAXkdIOaTc = false;
      string ruiCkuJGHm;
      string FjELhrGUlL;
      string MWWgOMfKhq;
      string aklqTrLUYI;
      string HMbWDraduk;
      string DSodEVYBnX;
      string PzXPMTyMro;
      string gkwcEztzdW;
      string lCOxnIwImy;
      string TJgAsInLKj;
      string sNlGDSVLZE;
      string aYXRlNjZbD;
      string XpZsVXEuju;
      string LhoscXPItV;
      string lkihWukPOf;
      string XNjGMDnrjf;
      string OaadssienO;
      string xafGRlGrVZ;
      string lngEXxyigY;
      string iWXNGLJEnd;
      if(ruiCkuJGHm == sNlGDSVLZE){LGazhwhcnZ = true;}
      else if(sNlGDSVLZE == ruiCkuJGHm){tWRHUFkSJK = true;}
      if(FjELhrGUlL == aYXRlNjZbD){wwVKsZsWGw = true;}
      else if(aYXRlNjZbD == FjELhrGUlL){HSYbjDSLsF = true;}
      if(MWWgOMfKhq == XpZsVXEuju){tzxPeZDRzG = true;}
      else if(XpZsVXEuju == MWWgOMfKhq){qfVtpJznxi = true;}
      if(aklqTrLUYI == LhoscXPItV){cCDrNfNgVa = true;}
      else if(LhoscXPItV == aklqTrLUYI){gqeExBXoxj = true;}
      if(HMbWDraduk == lkihWukPOf){OUuHbmBNUg = true;}
      else if(lkihWukPOf == HMbWDraduk){FjCxsEdlcd = true;}
      if(DSodEVYBnX == XNjGMDnrjf){RlyqjMILTI = true;}
      else if(XNjGMDnrjf == DSodEVYBnX){efTEqOBWRL = true;}
      if(PzXPMTyMro == OaadssienO){sPdhwtrdwM = true;}
      else if(OaadssienO == PzXPMTyMro){GxUacQnTdh = true;}
      if(gkwcEztzdW == xafGRlGrVZ){LMBegYEomr = true;}
      if(lCOxnIwImy == lngEXxyigY){YoxRopDMIB = true;}
      if(TJgAsInLKj == iWXNGLJEnd){WCNMgyqMKh = true;}
      while(xafGRlGrVZ == gkwcEztzdW){edOIAGdXAl = true;}
      while(lngEXxyigY == lngEXxyigY){fMKTDAWZNi = true;}
      while(iWXNGLJEnd == iWXNGLJEnd){AAXkdIOaTc = true;}
      if(LGazhwhcnZ == true){LGazhwhcnZ = false;}
      if(wwVKsZsWGw == true){wwVKsZsWGw = false;}
      if(tzxPeZDRzG == true){tzxPeZDRzG = false;}
      if(cCDrNfNgVa == true){cCDrNfNgVa = false;}
      if(OUuHbmBNUg == true){OUuHbmBNUg = false;}
      if(RlyqjMILTI == true){RlyqjMILTI = false;}
      if(sPdhwtrdwM == true){sPdhwtrdwM = false;}
      if(LMBegYEomr == true){LMBegYEomr = false;}
      if(YoxRopDMIB == true){YoxRopDMIB = false;}
      if(WCNMgyqMKh == true){WCNMgyqMKh = false;}
      if(tWRHUFkSJK == true){tWRHUFkSJK = false;}
      if(HSYbjDSLsF == true){HSYbjDSLsF = false;}
      if(qfVtpJznxi == true){qfVtpJznxi = false;}
      if(gqeExBXoxj == true){gqeExBXoxj = false;}
      if(FjCxsEdlcd == true){FjCxsEdlcd = false;}
      if(efTEqOBWRL == true){efTEqOBWRL = false;}
      if(GxUacQnTdh == true){GxUacQnTdh = false;}
      if(edOIAGdXAl == true){edOIAGdXAl = false;}
      if(fMKTDAWZNi == true){fMKTDAWZNi = false;}
      if(AAXkdIOaTc == true){AAXkdIOaTc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QUJDODDXYG
{ 
  void SqGWLMrPZt()
  { 
      bool qzTHpsJZqp = false;
      bool ESAwQOOslk = false;
      bool FsttcLUrjc = false;
      bool CVulaBSQkx = false;
      bool sqysseWggp = false;
      bool YlugcxFYdd = false;
      bool YRpNmiWOUP = false;
      bool uxHnrNuABy = false;
      bool nmKtEPZOId = false;
      bool wsmGYaBkGJ = false;
      bool HIMRtadHnP = false;
      bool CEXepkGwJX = false;
      bool IHFqSCKBPQ = false;
      bool MKtqqfaszc = false;
      bool kSasbqVHQm = false;
      bool TEaiBzCVyr = false;
      bool QcqWCqKfnJ = false;
      bool KNwflogLOb = false;
      bool fDkbwHiLoq = false;
      bool cEtHMIaDpj = false;
      string pXaSehpcOJ;
      string rpJibLyNRm;
      string jxyZpuSCHP;
      string BoCtAeQnVQ;
      string VbIEKLQdDs;
      string JjUdyrYBci;
      string PnVzHDmPhx;
      string uJrAQIotOd;
      string enyOFRUXuI;
      string FPKlAhGIxH;
      string XAuGxzrTMp;
      string DelyEbpGtp;
      string iOTZreyFzi;
      string CfwHGdsqQF;
      string ZALFFZdLhY;
      string rzOHXIgVNS;
      string BlTdnWidra;
      string iypnQhDNUR;
      string BlXaqCRoix;
      string xXcyEmfhRh;
      if(pXaSehpcOJ == XAuGxzrTMp){qzTHpsJZqp = true;}
      else if(XAuGxzrTMp == pXaSehpcOJ){HIMRtadHnP = true;}
      if(rpJibLyNRm == DelyEbpGtp){ESAwQOOslk = true;}
      else if(DelyEbpGtp == rpJibLyNRm){CEXepkGwJX = true;}
      if(jxyZpuSCHP == iOTZreyFzi){FsttcLUrjc = true;}
      else if(iOTZreyFzi == jxyZpuSCHP){IHFqSCKBPQ = true;}
      if(BoCtAeQnVQ == CfwHGdsqQF){CVulaBSQkx = true;}
      else if(CfwHGdsqQF == BoCtAeQnVQ){MKtqqfaszc = true;}
      if(VbIEKLQdDs == ZALFFZdLhY){sqysseWggp = true;}
      else if(ZALFFZdLhY == VbIEKLQdDs){kSasbqVHQm = true;}
      if(JjUdyrYBci == rzOHXIgVNS){YlugcxFYdd = true;}
      else if(rzOHXIgVNS == JjUdyrYBci){TEaiBzCVyr = true;}
      if(PnVzHDmPhx == BlTdnWidra){YRpNmiWOUP = true;}
      else if(BlTdnWidra == PnVzHDmPhx){QcqWCqKfnJ = true;}
      if(uJrAQIotOd == iypnQhDNUR){uxHnrNuABy = true;}
      if(enyOFRUXuI == BlXaqCRoix){nmKtEPZOId = true;}
      if(FPKlAhGIxH == xXcyEmfhRh){wsmGYaBkGJ = true;}
      while(iypnQhDNUR == uJrAQIotOd){KNwflogLOb = true;}
      while(BlXaqCRoix == BlXaqCRoix){fDkbwHiLoq = true;}
      while(xXcyEmfhRh == xXcyEmfhRh){cEtHMIaDpj = true;}
      if(qzTHpsJZqp == true){qzTHpsJZqp = false;}
      if(ESAwQOOslk == true){ESAwQOOslk = false;}
      if(FsttcLUrjc == true){FsttcLUrjc = false;}
      if(CVulaBSQkx == true){CVulaBSQkx = false;}
      if(sqysseWggp == true){sqysseWggp = false;}
      if(YlugcxFYdd == true){YlugcxFYdd = false;}
      if(YRpNmiWOUP == true){YRpNmiWOUP = false;}
      if(uxHnrNuABy == true){uxHnrNuABy = false;}
      if(nmKtEPZOId == true){nmKtEPZOId = false;}
      if(wsmGYaBkGJ == true){wsmGYaBkGJ = false;}
      if(HIMRtadHnP == true){HIMRtadHnP = false;}
      if(CEXepkGwJX == true){CEXepkGwJX = false;}
      if(IHFqSCKBPQ == true){IHFqSCKBPQ = false;}
      if(MKtqqfaszc == true){MKtqqfaszc = false;}
      if(kSasbqVHQm == true){kSasbqVHQm = false;}
      if(TEaiBzCVyr == true){TEaiBzCVyr = false;}
      if(QcqWCqKfnJ == true){QcqWCqKfnJ = false;}
      if(KNwflogLOb == true){KNwflogLOb = false;}
      if(fDkbwHiLoq == true){fDkbwHiLoq = false;}
      if(cEtHMIaDpj == true){cEtHMIaDpj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPAHAWVIYC
{ 
  void qmsueRUBlS()
  { 
      bool zizhNEXXXC = false;
      bool JomMjToadT = false;
      bool haTBMpomyD = false;
      bool crGSDQwpbd = false;
      bool TnATkAVbNk = false;
      bool IIOtSXOyUX = false;
      bool PjYUZRhUJT = false;
      bool XyzAzsazQM = false;
      bool TMZNuUcMAe = false;
      bool ByVEOiOetT = false;
      bool RBSsNJIOtY = false;
      bool xOhHDCKLZE = false;
      bool nVUdRZctlP = false;
      bool duFwuSsfzk = false;
      bool LORahlPNAL = false;
      bool YDFoeufoan = false;
      bool fOcdtBJkMk = false;
      bool JeLnsZEsuf = false;
      bool JOsaqapPRA = false;
      bool lDELFxlmfg = false;
      string NBNWduoeNq;
      string uhxsfWibGF;
      string HoSVBdwlXN;
      string wPCVBguGib;
      string VgAhGUdLQi;
      string kNxPkXirUz;
      string zDGAuefbqz;
      string bcrejaokOg;
      string zjUnbhSljd;
      string xDkjbRZAlb;
      string oBTQHHVSeK;
      string iycnAPhRXM;
      string MsrNBYrICR;
      string AnylqyPEgU;
      string LzGYtzZwjM;
      string iIbZPwIGOi;
      string PNQNKtzqxC;
      string zdkDBMlTSC;
      string zuXoiqMYWu;
      string oJoxExisNA;
      if(NBNWduoeNq == oBTQHHVSeK){zizhNEXXXC = true;}
      else if(oBTQHHVSeK == NBNWduoeNq){RBSsNJIOtY = true;}
      if(uhxsfWibGF == iycnAPhRXM){JomMjToadT = true;}
      else if(iycnAPhRXM == uhxsfWibGF){xOhHDCKLZE = true;}
      if(HoSVBdwlXN == MsrNBYrICR){haTBMpomyD = true;}
      else if(MsrNBYrICR == HoSVBdwlXN){nVUdRZctlP = true;}
      if(wPCVBguGib == AnylqyPEgU){crGSDQwpbd = true;}
      else if(AnylqyPEgU == wPCVBguGib){duFwuSsfzk = true;}
      if(VgAhGUdLQi == LzGYtzZwjM){TnATkAVbNk = true;}
      else if(LzGYtzZwjM == VgAhGUdLQi){LORahlPNAL = true;}
      if(kNxPkXirUz == iIbZPwIGOi){IIOtSXOyUX = true;}
      else if(iIbZPwIGOi == kNxPkXirUz){YDFoeufoan = true;}
      if(zDGAuefbqz == PNQNKtzqxC){PjYUZRhUJT = true;}
      else if(PNQNKtzqxC == zDGAuefbqz){fOcdtBJkMk = true;}
      if(bcrejaokOg == zdkDBMlTSC){XyzAzsazQM = true;}
      if(zjUnbhSljd == zuXoiqMYWu){TMZNuUcMAe = true;}
      if(xDkjbRZAlb == oJoxExisNA){ByVEOiOetT = true;}
      while(zdkDBMlTSC == bcrejaokOg){JeLnsZEsuf = true;}
      while(zuXoiqMYWu == zuXoiqMYWu){JOsaqapPRA = true;}
      while(oJoxExisNA == oJoxExisNA){lDELFxlmfg = true;}
      if(zizhNEXXXC == true){zizhNEXXXC = false;}
      if(JomMjToadT == true){JomMjToadT = false;}
      if(haTBMpomyD == true){haTBMpomyD = false;}
      if(crGSDQwpbd == true){crGSDQwpbd = false;}
      if(TnATkAVbNk == true){TnATkAVbNk = false;}
      if(IIOtSXOyUX == true){IIOtSXOyUX = false;}
      if(PjYUZRhUJT == true){PjYUZRhUJT = false;}
      if(XyzAzsazQM == true){XyzAzsazQM = false;}
      if(TMZNuUcMAe == true){TMZNuUcMAe = false;}
      if(ByVEOiOetT == true){ByVEOiOetT = false;}
      if(RBSsNJIOtY == true){RBSsNJIOtY = false;}
      if(xOhHDCKLZE == true){xOhHDCKLZE = false;}
      if(nVUdRZctlP == true){nVUdRZctlP = false;}
      if(duFwuSsfzk == true){duFwuSsfzk = false;}
      if(LORahlPNAL == true){LORahlPNAL = false;}
      if(YDFoeufoan == true){YDFoeufoan = false;}
      if(fOcdtBJkMk == true){fOcdtBJkMk = false;}
      if(JeLnsZEsuf == true){JeLnsZEsuf = false;}
      if(JOsaqapPRA == true){JOsaqapPRA = false;}
      if(lDELFxlmfg == true){lDELFxlmfg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULLSHYEKXQ
{ 
  void kuRlfkdGTP()
  { 
      bool nLNZBOrxTB = false;
      bool EMjEnZHEcJ = false;
      bool utNBOWJrEm = false;
      bool SGfGHeKwNe = false;
      bool RUrSADwHOo = false;
      bool NFXPnsxMLe = false;
      bool EzsfhyfdwI = false;
      bool OLqxrZCuAK = false;
      bool aCdOZNiQRN = false;
      bool hykiaRbLkC = false;
      bool XRKGaCOZXO = false;
      bool qCLADBVdGU = false;
      bool PPMhZQaHVZ = false;
      bool ypJxlIqXnW = false;
      bool yIrCWfljeZ = false;
      bool uxFQmIFcfK = false;
      bool bGDyPArONt = false;
      bool JyoiVGWJLt = false;
      bool dpcwdAksJd = false;
      bool DOqdurEtmV = false;
      string sqXlwFxBKT;
      string abGLgGHelt;
      string LNYEFeWQZb;
      string FwWuaFtXjA;
      string ytfzRxdzQa;
      string YAbxieSTgQ;
      string igbiNdFLjb;
      string LiuluQgYmI;
      string BWAyCFUZLw;
      string maqTQRSxkn;
      string qSPnPoFoBR;
      string ysgXOLgdfI;
      string IfznojraUd;
      string yjnyQiHLhM;
      string zeXsxssTFF;
      string jnQceLSaze;
      string xdUWTNFhGe;
      string DVuTIdHGpu;
      string qXVPtJSLTF;
      string QgLDOVKAZj;
      if(sqXlwFxBKT == qSPnPoFoBR){nLNZBOrxTB = true;}
      else if(qSPnPoFoBR == sqXlwFxBKT){XRKGaCOZXO = true;}
      if(abGLgGHelt == ysgXOLgdfI){EMjEnZHEcJ = true;}
      else if(ysgXOLgdfI == abGLgGHelt){qCLADBVdGU = true;}
      if(LNYEFeWQZb == IfznojraUd){utNBOWJrEm = true;}
      else if(IfznojraUd == LNYEFeWQZb){PPMhZQaHVZ = true;}
      if(FwWuaFtXjA == yjnyQiHLhM){SGfGHeKwNe = true;}
      else if(yjnyQiHLhM == FwWuaFtXjA){ypJxlIqXnW = true;}
      if(ytfzRxdzQa == zeXsxssTFF){RUrSADwHOo = true;}
      else if(zeXsxssTFF == ytfzRxdzQa){yIrCWfljeZ = true;}
      if(YAbxieSTgQ == jnQceLSaze){NFXPnsxMLe = true;}
      else if(jnQceLSaze == YAbxieSTgQ){uxFQmIFcfK = true;}
      if(igbiNdFLjb == xdUWTNFhGe){EzsfhyfdwI = true;}
      else if(xdUWTNFhGe == igbiNdFLjb){bGDyPArONt = true;}
      if(LiuluQgYmI == DVuTIdHGpu){OLqxrZCuAK = true;}
      if(BWAyCFUZLw == qXVPtJSLTF){aCdOZNiQRN = true;}
      if(maqTQRSxkn == QgLDOVKAZj){hykiaRbLkC = true;}
      while(DVuTIdHGpu == LiuluQgYmI){JyoiVGWJLt = true;}
      while(qXVPtJSLTF == qXVPtJSLTF){dpcwdAksJd = true;}
      while(QgLDOVKAZj == QgLDOVKAZj){DOqdurEtmV = true;}
      if(nLNZBOrxTB == true){nLNZBOrxTB = false;}
      if(EMjEnZHEcJ == true){EMjEnZHEcJ = false;}
      if(utNBOWJrEm == true){utNBOWJrEm = false;}
      if(SGfGHeKwNe == true){SGfGHeKwNe = false;}
      if(RUrSADwHOo == true){RUrSADwHOo = false;}
      if(NFXPnsxMLe == true){NFXPnsxMLe = false;}
      if(EzsfhyfdwI == true){EzsfhyfdwI = false;}
      if(OLqxrZCuAK == true){OLqxrZCuAK = false;}
      if(aCdOZNiQRN == true){aCdOZNiQRN = false;}
      if(hykiaRbLkC == true){hykiaRbLkC = false;}
      if(XRKGaCOZXO == true){XRKGaCOZXO = false;}
      if(qCLADBVdGU == true){qCLADBVdGU = false;}
      if(PPMhZQaHVZ == true){PPMhZQaHVZ = false;}
      if(ypJxlIqXnW == true){ypJxlIqXnW = false;}
      if(yIrCWfljeZ == true){yIrCWfljeZ = false;}
      if(uxFQmIFcfK == true){uxFQmIFcfK = false;}
      if(bGDyPArONt == true){bGDyPArONt = false;}
      if(JyoiVGWJLt == true){JyoiVGWJLt = false;}
      if(dpcwdAksJd == true){dpcwdAksJd = false;}
      if(DOqdurEtmV == true){DOqdurEtmV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUIOVRWGIF
{ 
  void lkOLLeSxSF()
  { 
      bool zPWzIpUnUs = false;
      bool bsGiQSpjly = false;
      bool xBWCBmlZXA = false;
      bool PZGVGXONGH = false;
      bool tidNTYdykd = false;
      bool iKnlQyrUxV = false;
      bool DtQTcCmjcs = false;
      bool EcddEOXJib = false;
      bool JnntRFlTFI = false;
      bool etQkDzRJkQ = false;
      bool lsVrYGfJhC = false;
      bool aikULPGWCW = false;
      bool QSeUNKLsZE = false;
      bool wNYRpQRuUK = false;
      bool YblCguIuYn = false;
      bool suGNASNBdO = false;
      bool umicGMKTeu = false;
      bool xKCrxngbmS = false;
      bool CQTlKAHKQW = false;
      bool CQRGOlrIwU = false;
      string wMkxJCSMOi;
      string OQAKmBgBCS;
      string xfTbMMKKlc;
      string PQDnDnoeiY;
      string JFRVHAlUtw;
      string OCZBQQsIkw;
      string qHZlTxMMHz;
      string LBSdJqNxUM;
      string apQpONqCWm;
      string tftmhBffCK;
      string mYMtjMiwrY;
      string CunXUAqiWF;
      string GKoUFfHewI;
      string LguKYBcWGC;
      string dtJyjzrVRg;
      string KwJwEcjroD;
      string EDzjNUzcyS;
      string XTbUaLAqkF;
      string mkMPxOXyGw;
      string RkhCxZuZkO;
      if(wMkxJCSMOi == mYMtjMiwrY){zPWzIpUnUs = true;}
      else if(mYMtjMiwrY == wMkxJCSMOi){lsVrYGfJhC = true;}
      if(OQAKmBgBCS == CunXUAqiWF){bsGiQSpjly = true;}
      else if(CunXUAqiWF == OQAKmBgBCS){aikULPGWCW = true;}
      if(xfTbMMKKlc == GKoUFfHewI){xBWCBmlZXA = true;}
      else if(GKoUFfHewI == xfTbMMKKlc){QSeUNKLsZE = true;}
      if(PQDnDnoeiY == LguKYBcWGC){PZGVGXONGH = true;}
      else if(LguKYBcWGC == PQDnDnoeiY){wNYRpQRuUK = true;}
      if(JFRVHAlUtw == dtJyjzrVRg){tidNTYdykd = true;}
      else if(dtJyjzrVRg == JFRVHAlUtw){YblCguIuYn = true;}
      if(OCZBQQsIkw == KwJwEcjroD){iKnlQyrUxV = true;}
      else if(KwJwEcjroD == OCZBQQsIkw){suGNASNBdO = true;}
      if(qHZlTxMMHz == EDzjNUzcyS){DtQTcCmjcs = true;}
      else if(EDzjNUzcyS == qHZlTxMMHz){umicGMKTeu = true;}
      if(LBSdJqNxUM == XTbUaLAqkF){EcddEOXJib = true;}
      if(apQpONqCWm == mkMPxOXyGw){JnntRFlTFI = true;}
      if(tftmhBffCK == RkhCxZuZkO){etQkDzRJkQ = true;}
      while(XTbUaLAqkF == LBSdJqNxUM){xKCrxngbmS = true;}
      while(mkMPxOXyGw == mkMPxOXyGw){CQTlKAHKQW = true;}
      while(RkhCxZuZkO == RkhCxZuZkO){CQRGOlrIwU = true;}
      if(zPWzIpUnUs == true){zPWzIpUnUs = false;}
      if(bsGiQSpjly == true){bsGiQSpjly = false;}
      if(xBWCBmlZXA == true){xBWCBmlZXA = false;}
      if(PZGVGXONGH == true){PZGVGXONGH = false;}
      if(tidNTYdykd == true){tidNTYdykd = false;}
      if(iKnlQyrUxV == true){iKnlQyrUxV = false;}
      if(DtQTcCmjcs == true){DtQTcCmjcs = false;}
      if(EcddEOXJib == true){EcddEOXJib = false;}
      if(JnntRFlTFI == true){JnntRFlTFI = false;}
      if(etQkDzRJkQ == true){etQkDzRJkQ = false;}
      if(lsVrYGfJhC == true){lsVrYGfJhC = false;}
      if(aikULPGWCW == true){aikULPGWCW = false;}
      if(QSeUNKLsZE == true){QSeUNKLsZE = false;}
      if(wNYRpQRuUK == true){wNYRpQRuUK = false;}
      if(YblCguIuYn == true){YblCguIuYn = false;}
      if(suGNASNBdO == true){suGNASNBdO = false;}
      if(umicGMKTeu == true){umicGMKTeu = false;}
      if(xKCrxngbmS == true){xKCrxngbmS = false;}
      if(CQTlKAHKQW == true){CQTlKAHKQW = false;}
      if(CQRGOlrIwU == true){CQRGOlrIwU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKETJEFMJZ
{ 
  void LQaclzYuxe()
  { 
      bool SrgVbPpIZl = false;
      bool PNjNAaOffe = false;
      bool MZJcWbmuQX = false;
      bool qdfIILbcPM = false;
      bool ESdjRFIuVH = false;
      bool BGdRVshDyA = false;
      bool buqBtlgaFo = false;
      bool zkPSZtuZLQ = false;
      bool SrYJWkAOmO = false;
      bool cXePkJabof = false;
      bool YgpgIPpKqa = false;
      bool xIqggjVheI = false;
      bool kSnpLaGAhQ = false;
      bool TTjfrkBrAG = false;
      bool upXLRTfxiB = false;
      bool nrxgtGszUg = false;
      bool IpcZHdXLou = false;
      bool hdgXNutcXq = false;
      bool tJQgcbVDkl = false;
      bool rCWTxFMxEn = false;
      string uATepGrxFW;
      string VhanFRdjIG;
      string sLDJhpInBh;
      string zJJbeoAlMi;
      string LszERjpzcx;
      string cwlscjwJwA;
      string yEuXWMXzJQ;
      string RqWYuALzqy;
      string AJKEEDWQzu;
      string sppLkGybgF;
      string LpoMekYMxb;
      string XwRxAntpSS;
      string oHAOXbBKno;
      string CjSllJTxZS;
      string dKSWWwXrLw;
      string LHIOQEpanD;
      string jNXIZndfLp;
      string UwQzndncqa;
      string DIzrcuaDVh;
      string SrIViQlJwi;
      if(uATepGrxFW == LpoMekYMxb){SrgVbPpIZl = true;}
      else if(LpoMekYMxb == uATepGrxFW){YgpgIPpKqa = true;}
      if(VhanFRdjIG == XwRxAntpSS){PNjNAaOffe = true;}
      else if(XwRxAntpSS == VhanFRdjIG){xIqggjVheI = true;}
      if(sLDJhpInBh == oHAOXbBKno){MZJcWbmuQX = true;}
      else if(oHAOXbBKno == sLDJhpInBh){kSnpLaGAhQ = true;}
      if(zJJbeoAlMi == CjSllJTxZS){qdfIILbcPM = true;}
      else if(CjSllJTxZS == zJJbeoAlMi){TTjfrkBrAG = true;}
      if(LszERjpzcx == dKSWWwXrLw){ESdjRFIuVH = true;}
      else if(dKSWWwXrLw == LszERjpzcx){upXLRTfxiB = true;}
      if(cwlscjwJwA == LHIOQEpanD){BGdRVshDyA = true;}
      else if(LHIOQEpanD == cwlscjwJwA){nrxgtGszUg = true;}
      if(yEuXWMXzJQ == jNXIZndfLp){buqBtlgaFo = true;}
      else if(jNXIZndfLp == yEuXWMXzJQ){IpcZHdXLou = true;}
      if(RqWYuALzqy == UwQzndncqa){zkPSZtuZLQ = true;}
      if(AJKEEDWQzu == DIzrcuaDVh){SrYJWkAOmO = true;}
      if(sppLkGybgF == SrIViQlJwi){cXePkJabof = true;}
      while(UwQzndncqa == RqWYuALzqy){hdgXNutcXq = true;}
      while(DIzrcuaDVh == DIzrcuaDVh){tJQgcbVDkl = true;}
      while(SrIViQlJwi == SrIViQlJwi){rCWTxFMxEn = true;}
      if(SrgVbPpIZl == true){SrgVbPpIZl = false;}
      if(PNjNAaOffe == true){PNjNAaOffe = false;}
      if(MZJcWbmuQX == true){MZJcWbmuQX = false;}
      if(qdfIILbcPM == true){qdfIILbcPM = false;}
      if(ESdjRFIuVH == true){ESdjRFIuVH = false;}
      if(BGdRVshDyA == true){BGdRVshDyA = false;}
      if(buqBtlgaFo == true){buqBtlgaFo = false;}
      if(zkPSZtuZLQ == true){zkPSZtuZLQ = false;}
      if(SrYJWkAOmO == true){SrYJWkAOmO = false;}
      if(cXePkJabof == true){cXePkJabof = false;}
      if(YgpgIPpKqa == true){YgpgIPpKqa = false;}
      if(xIqggjVheI == true){xIqggjVheI = false;}
      if(kSnpLaGAhQ == true){kSnpLaGAhQ = false;}
      if(TTjfrkBrAG == true){TTjfrkBrAG = false;}
      if(upXLRTfxiB == true){upXLRTfxiB = false;}
      if(nrxgtGszUg == true){nrxgtGszUg = false;}
      if(IpcZHdXLou == true){IpcZHdXLou = false;}
      if(hdgXNutcXq == true){hdgXNutcXq = false;}
      if(tJQgcbVDkl == true){tJQgcbVDkl = false;}
      if(rCWTxFMxEn == true){rCWTxFMxEn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WKIJWOXEMA
{ 
  void RjGJkfBaQT()
  { 
      bool UWItIIfwLt = false;
      bool jGPHCWlydx = false;
      bool NAnOXYABQh = false;
      bool GgaeleoXkd = false;
      bool CouLijFipI = false;
      bool EAEzgUhsWi = false;
      bool HefcnDfkVX = false;
      bool gNNAtXEcfn = false;
      bool TRKHdGbbyQ = false;
      bool wuABVXJRWf = false;
      bool DUNSaplEEJ = false;
      bool PFNiPpTXyh = false;
      bool aElEakNLdV = false;
      bool NlGzjyDqgn = false;
      bool TXWnBqhQke = false;
      bool ElTnEzhJro = false;
      bool caZiucyNzR = false;
      bool mbpKODhxCi = false;
      bool DwZyRbSRtj = false;
      bool PtyrLrxnsX = false;
      string SdipyyyJTV;
      string OJRLTKFEue;
      string WUneKJWBoI;
      string biqtUNWXhm;
      string tpBuceFBBO;
      string tBAnXxoDfn;
      string bxULsfRXqF;
      string nhVIjgTrCe;
      string DVAZNZiDVW;
      string XSqsKxVpCw;
      string NhJuaMfqDq;
      string cxAAjGwtxS;
      string xOCTgUpbym;
      string KdpFRVLEzB;
      string trzdtaRqJD;
      string AarjzzepNF;
      string VEsQgzGuhO;
      string uquwXEOXZG;
      string CyStlilGGS;
      string pVqsfpyhxt;
      if(SdipyyyJTV == NhJuaMfqDq){UWItIIfwLt = true;}
      else if(NhJuaMfqDq == SdipyyyJTV){DUNSaplEEJ = true;}
      if(OJRLTKFEue == cxAAjGwtxS){jGPHCWlydx = true;}
      else if(cxAAjGwtxS == OJRLTKFEue){PFNiPpTXyh = true;}
      if(WUneKJWBoI == xOCTgUpbym){NAnOXYABQh = true;}
      else if(xOCTgUpbym == WUneKJWBoI){aElEakNLdV = true;}
      if(biqtUNWXhm == KdpFRVLEzB){GgaeleoXkd = true;}
      else if(KdpFRVLEzB == biqtUNWXhm){NlGzjyDqgn = true;}
      if(tpBuceFBBO == trzdtaRqJD){CouLijFipI = true;}
      else if(trzdtaRqJD == tpBuceFBBO){TXWnBqhQke = true;}
      if(tBAnXxoDfn == AarjzzepNF){EAEzgUhsWi = true;}
      else if(AarjzzepNF == tBAnXxoDfn){ElTnEzhJro = true;}
      if(bxULsfRXqF == VEsQgzGuhO){HefcnDfkVX = true;}
      else if(VEsQgzGuhO == bxULsfRXqF){caZiucyNzR = true;}
      if(nhVIjgTrCe == uquwXEOXZG){gNNAtXEcfn = true;}
      if(DVAZNZiDVW == CyStlilGGS){TRKHdGbbyQ = true;}
      if(XSqsKxVpCw == pVqsfpyhxt){wuABVXJRWf = true;}
      while(uquwXEOXZG == nhVIjgTrCe){mbpKODhxCi = true;}
      while(CyStlilGGS == CyStlilGGS){DwZyRbSRtj = true;}
      while(pVqsfpyhxt == pVqsfpyhxt){PtyrLrxnsX = true;}
      if(UWItIIfwLt == true){UWItIIfwLt = false;}
      if(jGPHCWlydx == true){jGPHCWlydx = false;}
      if(NAnOXYABQh == true){NAnOXYABQh = false;}
      if(GgaeleoXkd == true){GgaeleoXkd = false;}
      if(CouLijFipI == true){CouLijFipI = false;}
      if(EAEzgUhsWi == true){EAEzgUhsWi = false;}
      if(HefcnDfkVX == true){HefcnDfkVX = false;}
      if(gNNAtXEcfn == true){gNNAtXEcfn = false;}
      if(TRKHdGbbyQ == true){TRKHdGbbyQ = false;}
      if(wuABVXJRWf == true){wuABVXJRWf = false;}
      if(DUNSaplEEJ == true){DUNSaplEEJ = false;}
      if(PFNiPpTXyh == true){PFNiPpTXyh = false;}
      if(aElEakNLdV == true){aElEakNLdV = false;}
      if(NlGzjyDqgn == true){NlGzjyDqgn = false;}
      if(TXWnBqhQke == true){TXWnBqhQke = false;}
      if(ElTnEzhJro == true){ElTnEzhJro = false;}
      if(caZiucyNzR == true){caZiucyNzR = false;}
      if(mbpKODhxCi == true){mbpKODhxCi = false;}
      if(DwZyRbSRtj == true){DwZyRbSRtj = false;}
      if(PtyrLrxnsX == true){PtyrLrxnsX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCACUKNUNL
{ 
  void CVslEGneVI()
  { 
      bool WALiOOezLy = false;
      bool DGtfUowiXp = false;
      bool yEXboLGFeY = false;
      bool EanjsBLdwn = false;
      bool aipcDIthEQ = false;
      bool UFciQScisC = false;
      bool IZUlscRJmS = false;
      bool dSmjOOOtYg = false;
      bool QXBNEzyFTa = false;
      bool YcjtfBODia = false;
      bool pjukmBRrTB = false;
      bool DhKMkjXHht = false;
      bool eMpMtAisEN = false;
      bool AKLxpfcPZC = false;
      bool gFkRWpSWIu = false;
      bool cHUnwdtiql = false;
      bool SYnGBrWMVE = false;
      bool HIgfNZaXoE = false;
      bool hLjJkspWBM = false;
      bool ltYmiHQdPd = false;
      string TcsEjTORZR;
      string cxPEJqGXfz;
      string mHsnGJKeST;
      string QwCxJYWSzH;
      string ykwUBfWjbu;
      string TgrNOMiFyZ;
      string JizFBgtRtk;
      string UmYYBCKXmZ;
      string mZCWAiDohx;
      string oRTYyPlpTU;
      string lEpqZfITMM;
      string BLRXljfbFR;
      string cFjwuCSzZl;
      string QTESniiLxT;
      string aibVwdzulO;
      string iJkCqgUtwX;
      string MJtawgGzjD;
      string AUekpscNzQ;
      string CXMKCGiBaH;
      string OoOYGRoBYO;
      if(TcsEjTORZR == lEpqZfITMM){WALiOOezLy = true;}
      else if(lEpqZfITMM == TcsEjTORZR){pjukmBRrTB = true;}
      if(cxPEJqGXfz == BLRXljfbFR){DGtfUowiXp = true;}
      else if(BLRXljfbFR == cxPEJqGXfz){DhKMkjXHht = true;}
      if(mHsnGJKeST == cFjwuCSzZl){yEXboLGFeY = true;}
      else if(cFjwuCSzZl == mHsnGJKeST){eMpMtAisEN = true;}
      if(QwCxJYWSzH == QTESniiLxT){EanjsBLdwn = true;}
      else if(QTESniiLxT == QwCxJYWSzH){AKLxpfcPZC = true;}
      if(ykwUBfWjbu == aibVwdzulO){aipcDIthEQ = true;}
      else if(aibVwdzulO == ykwUBfWjbu){gFkRWpSWIu = true;}
      if(TgrNOMiFyZ == iJkCqgUtwX){UFciQScisC = true;}
      else if(iJkCqgUtwX == TgrNOMiFyZ){cHUnwdtiql = true;}
      if(JizFBgtRtk == MJtawgGzjD){IZUlscRJmS = true;}
      else if(MJtawgGzjD == JizFBgtRtk){SYnGBrWMVE = true;}
      if(UmYYBCKXmZ == AUekpscNzQ){dSmjOOOtYg = true;}
      if(mZCWAiDohx == CXMKCGiBaH){QXBNEzyFTa = true;}
      if(oRTYyPlpTU == OoOYGRoBYO){YcjtfBODia = true;}
      while(AUekpscNzQ == UmYYBCKXmZ){HIgfNZaXoE = true;}
      while(CXMKCGiBaH == CXMKCGiBaH){hLjJkspWBM = true;}
      while(OoOYGRoBYO == OoOYGRoBYO){ltYmiHQdPd = true;}
      if(WALiOOezLy == true){WALiOOezLy = false;}
      if(DGtfUowiXp == true){DGtfUowiXp = false;}
      if(yEXboLGFeY == true){yEXboLGFeY = false;}
      if(EanjsBLdwn == true){EanjsBLdwn = false;}
      if(aipcDIthEQ == true){aipcDIthEQ = false;}
      if(UFciQScisC == true){UFciQScisC = false;}
      if(IZUlscRJmS == true){IZUlscRJmS = false;}
      if(dSmjOOOtYg == true){dSmjOOOtYg = false;}
      if(QXBNEzyFTa == true){QXBNEzyFTa = false;}
      if(YcjtfBODia == true){YcjtfBODia = false;}
      if(pjukmBRrTB == true){pjukmBRrTB = false;}
      if(DhKMkjXHht == true){DhKMkjXHht = false;}
      if(eMpMtAisEN == true){eMpMtAisEN = false;}
      if(AKLxpfcPZC == true){AKLxpfcPZC = false;}
      if(gFkRWpSWIu == true){gFkRWpSWIu = false;}
      if(cHUnwdtiql == true){cHUnwdtiql = false;}
      if(SYnGBrWMVE == true){SYnGBrWMVE = false;}
      if(HIgfNZaXoE == true){HIgfNZaXoE = false;}
      if(hLjJkspWBM == true){hLjJkspWBM = false;}
      if(ltYmiHQdPd == true){ltYmiHQdPd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NATXDSFBBP
{ 
  void AjyrDOATjq()
  { 
      bool arUmHpgeKn = false;
      bool AFbixwlVtO = false;
      bool TChCZxXXND = false;
      bool KdZkfsPMKA = false;
      bool bpidYlrpJm = false;
      bool MhonrXKRMK = false;
      bool SJQGdVfpCE = false;
      bool fZKtmcSEdn = false;
      bool FhOZqcnksH = false;
      bool iyzAhSZcAC = false;
      bool FBmFGmXuBO = false;
      bool EFmXEktpPA = false;
      bool htxuUgZJLT = false;
      bool DpDbiEtISE = false;
      bool EsjdCcLbwx = false;
      bool XiMzTKDqjZ = false;
      bool MNigLOCKoA = false;
      bool plWKwnKSsr = false;
      bool VyNOwUdEHX = false;
      bool ACXsqqJDSn = false;
      string wncogBLzel;
      string KrzzCRwJjV;
      string XWZYtaZPTk;
      string WdaYNrUEFJ;
      string tQjQqMMJeM;
      string FuFqCZOEuG;
      string auesPfRZlJ;
      string wqEZbHmIgg;
      string NQjHebXjVm;
      string dQJyiykpBL;
      string umXVPOqfOu;
      string lFWNsKLXNm;
      string HhDyffgFqd;
      string WxHVlasOqQ;
      string jrUaBYswFY;
      string mNbNDNiYpj;
      string glnkXoxAbS;
      string QwfxCOMcxH;
      string lkzSqJUtSY;
      string rTYHiyEiCL;
      if(wncogBLzel == umXVPOqfOu){arUmHpgeKn = true;}
      else if(umXVPOqfOu == wncogBLzel){FBmFGmXuBO = true;}
      if(KrzzCRwJjV == lFWNsKLXNm){AFbixwlVtO = true;}
      else if(lFWNsKLXNm == KrzzCRwJjV){EFmXEktpPA = true;}
      if(XWZYtaZPTk == HhDyffgFqd){TChCZxXXND = true;}
      else if(HhDyffgFqd == XWZYtaZPTk){htxuUgZJLT = true;}
      if(WdaYNrUEFJ == WxHVlasOqQ){KdZkfsPMKA = true;}
      else if(WxHVlasOqQ == WdaYNrUEFJ){DpDbiEtISE = true;}
      if(tQjQqMMJeM == jrUaBYswFY){bpidYlrpJm = true;}
      else if(jrUaBYswFY == tQjQqMMJeM){EsjdCcLbwx = true;}
      if(FuFqCZOEuG == mNbNDNiYpj){MhonrXKRMK = true;}
      else if(mNbNDNiYpj == FuFqCZOEuG){XiMzTKDqjZ = true;}
      if(auesPfRZlJ == glnkXoxAbS){SJQGdVfpCE = true;}
      else if(glnkXoxAbS == auesPfRZlJ){MNigLOCKoA = true;}
      if(wqEZbHmIgg == QwfxCOMcxH){fZKtmcSEdn = true;}
      if(NQjHebXjVm == lkzSqJUtSY){FhOZqcnksH = true;}
      if(dQJyiykpBL == rTYHiyEiCL){iyzAhSZcAC = true;}
      while(QwfxCOMcxH == wqEZbHmIgg){plWKwnKSsr = true;}
      while(lkzSqJUtSY == lkzSqJUtSY){VyNOwUdEHX = true;}
      while(rTYHiyEiCL == rTYHiyEiCL){ACXsqqJDSn = true;}
      if(arUmHpgeKn == true){arUmHpgeKn = false;}
      if(AFbixwlVtO == true){AFbixwlVtO = false;}
      if(TChCZxXXND == true){TChCZxXXND = false;}
      if(KdZkfsPMKA == true){KdZkfsPMKA = false;}
      if(bpidYlrpJm == true){bpidYlrpJm = false;}
      if(MhonrXKRMK == true){MhonrXKRMK = false;}
      if(SJQGdVfpCE == true){SJQGdVfpCE = false;}
      if(fZKtmcSEdn == true){fZKtmcSEdn = false;}
      if(FhOZqcnksH == true){FhOZqcnksH = false;}
      if(iyzAhSZcAC == true){iyzAhSZcAC = false;}
      if(FBmFGmXuBO == true){FBmFGmXuBO = false;}
      if(EFmXEktpPA == true){EFmXEktpPA = false;}
      if(htxuUgZJLT == true){htxuUgZJLT = false;}
      if(DpDbiEtISE == true){DpDbiEtISE = false;}
      if(EsjdCcLbwx == true){EsjdCcLbwx = false;}
      if(XiMzTKDqjZ == true){XiMzTKDqjZ = false;}
      if(MNigLOCKoA == true){MNigLOCKoA = false;}
      if(plWKwnKSsr == true){plWKwnKSsr = false;}
      if(VyNOwUdEHX == true){VyNOwUdEHX = false;}
      if(ACXsqqJDSn == true){ACXsqqJDSn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJGUJJJERY
{ 
  void zcclCxweWV()
  { 
      bool pJCsQcDHVb = false;
      bool ouwAPrmtXM = false;
      bool YnOZdTErhZ = false;
      bool bajnzhcwKy = false;
      bool lrEJDWlGKC = false;
      bool fWDFHCtcPw = false;
      bool XLZuAOLIAh = false;
      bool PpiZafjFVH = false;
      bool hygetEWefx = false;
      bool mAgNZZRIIo = false;
      bool KdFcmpmddb = false;
      bool SoGHOZeuBu = false;
      bool rfbDtPIUzB = false;
      bool NaxgwDrDqD = false;
      bool RrBEeysYzA = false;
      bool uWHMxeBBiX = false;
      bool gRecNqrZLK = false;
      bool gaExdzeXYw = false;
      bool VjVzFqTjjR = false;
      bool CpUSVzNYpm = false;
      string drQMNRZXpt;
      string axoqJINkcN;
      string ExtyBOZcbx;
      string ynZhyFllBM;
      string xUbAoscjqh;
      string CrhgygxSLz;
      string qxwrulWGrD;
      string WbiQQjUtJH;
      string lpltuFFriR;
      string ITZCUAXiEC;
      string WVqmLaJRQO;
      string LDIEMBKBxo;
      string geXauDBfuQ;
      string LloHkQyyiT;
      string wnbUGEKVpT;
      string oVkOVryQqH;
      string YcWzCZNASw;
      string CLScssCCUp;
      string rfpbboAZls;
      string RhHauSQbRg;
      if(drQMNRZXpt == WVqmLaJRQO){pJCsQcDHVb = true;}
      else if(WVqmLaJRQO == drQMNRZXpt){KdFcmpmddb = true;}
      if(axoqJINkcN == LDIEMBKBxo){ouwAPrmtXM = true;}
      else if(LDIEMBKBxo == axoqJINkcN){SoGHOZeuBu = true;}
      if(ExtyBOZcbx == geXauDBfuQ){YnOZdTErhZ = true;}
      else if(geXauDBfuQ == ExtyBOZcbx){rfbDtPIUzB = true;}
      if(ynZhyFllBM == LloHkQyyiT){bajnzhcwKy = true;}
      else if(LloHkQyyiT == ynZhyFllBM){NaxgwDrDqD = true;}
      if(xUbAoscjqh == wnbUGEKVpT){lrEJDWlGKC = true;}
      else if(wnbUGEKVpT == xUbAoscjqh){RrBEeysYzA = true;}
      if(CrhgygxSLz == oVkOVryQqH){fWDFHCtcPw = true;}
      else if(oVkOVryQqH == CrhgygxSLz){uWHMxeBBiX = true;}
      if(qxwrulWGrD == YcWzCZNASw){XLZuAOLIAh = true;}
      else if(YcWzCZNASw == qxwrulWGrD){gRecNqrZLK = true;}
      if(WbiQQjUtJH == CLScssCCUp){PpiZafjFVH = true;}
      if(lpltuFFriR == rfpbboAZls){hygetEWefx = true;}
      if(ITZCUAXiEC == RhHauSQbRg){mAgNZZRIIo = true;}
      while(CLScssCCUp == WbiQQjUtJH){gaExdzeXYw = true;}
      while(rfpbboAZls == rfpbboAZls){VjVzFqTjjR = true;}
      while(RhHauSQbRg == RhHauSQbRg){CpUSVzNYpm = true;}
      if(pJCsQcDHVb == true){pJCsQcDHVb = false;}
      if(ouwAPrmtXM == true){ouwAPrmtXM = false;}
      if(YnOZdTErhZ == true){YnOZdTErhZ = false;}
      if(bajnzhcwKy == true){bajnzhcwKy = false;}
      if(lrEJDWlGKC == true){lrEJDWlGKC = false;}
      if(fWDFHCtcPw == true){fWDFHCtcPw = false;}
      if(XLZuAOLIAh == true){XLZuAOLIAh = false;}
      if(PpiZafjFVH == true){PpiZafjFVH = false;}
      if(hygetEWefx == true){hygetEWefx = false;}
      if(mAgNZZRIIo == true){mAgNZZRIIo = false;}
      if(KdFcmpmddb == true){KdFcmpmddb = false;}
      if(SoGHOZeuBu == true){SoGHOZeuBu = false;}
      if(rfbDtPIUzB == true){rfbDtPIUzB = false;}
      if(NaxgwDrDqD == true){NaxgwDrDqD = false;}
      if(RrBEeysYzA == true){RrBEeysYzA = false;}
      if(uWHMxeBBiX == true){uWHMxeBBiX = false;}
      if(gRecNqrZLK == true){gRecNqrZLK = false;}
      if(gaExdzeXYw == true){gaExdzeXYw = false;}
      if(VjVzFqTjjR == true){VjVzFqTjjR = false;}
      if(CpUSVzNYpm == true){CpUSVzNYpm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJJMBVVOGB
{ 
  void JyepBKRqTK()
  { 
      bool LwZkGlIwbu = false;
      bool oFJRTbqbBh = false;
      bool puxcEIBnfx = false;
      bool DLDtsxLbWt = false;
      bool HJEcdhkpkH = false;
      bool ZmIAOQyxgy = false;
      bool kTQdrcBPXV = false;
      bool QOFGafqUzW = false;
      bool XKCXXPDCec = false;
      bool yNuXJmsakA = false;
      bool fVRPpKhBZi = false;
      bool YdxJaZRrFb = false;
      bool ZzjuWCSgxn = false;
      bool mQjzqCsmhM = false;
      bool hCcwDUQkxi = false;
      bool UBUIafkWrn = false;
      bool rAEluItySY = false;
      bool geJrtWWmrC = false;
      bool lgiNSkubYK = false;
      bool QWttUgxpAt = false;
      string DZlgqeWRiR;
      string OBIrJSnQEi;
      string xydnAYCmMA;
      string NOgqWfbfVw;
      string USHfAteirS;
      string esAbtFuygS;
      string ciFhEzURUc;
      string qHuHOepxnF;
      string sTtsUTNFxR;
      string kdyCTkNYaA;
      string ZNNPaWxsMP;
      string OxJbYJnLNk;
      string lOUDrNIrnd;
      string RRVmefFeSx;
      string VTrgCmTWdK;
      string wBLpNLrKWN;
      string NFFiywaWwr;
      string DJsPORVmAF;
      string tlNcgPGfYT;
      string muHEiQOJiF;
      if(DZlgqeWRiR == ZNNPaWxsMP){LwZkGlIwbu = true;}
      else if(ZNNPaWxsMP == DZlgqeWRiR){fVRPpKhBZi = true;}
      if(OBIrJSnQEi == OxJbYJnLNk){oFJRTbqbBh = true;}
      else if(OxJbYJnLNk == OBIrJSnQEi){YdxJaZRrFb = true;}
      if(xydnAYCmMA == lOUDrNIrnd){puxcEIBnfx = true;}
      else if(lOUDrNIrnd == xydnAYCmMA){ZzjuWCSgxn = true;}
      if(NOgqWfbfVw == RRVmefFeSx){DLDtsxLbWt = true;}
      else if(RRVmefFeSx == NOgqWfbfVw){mQjzqCsmhM = true;}
      if(USHfAteirS == VTrgCmTWdK){HJEcdhkpkH = true;}
      else if(VTrgCmTWdK == USHfAteirS){hCcwDUQkxi = true;}
      if(esAbtFuygS == wBLpNLrKWN){ZmIAOQyxgy = true;}
      else if(wBLpNLrKWN == esAbtFuygS){UBUIafkWrn = true;}
      if(ciFhEzURUc == NFFiywaWwr){kTQdrcBPXV = true;}
      else if(NFFiywaWwr == ciFhEzURUc){rAEluItySY = true;}
      if(qHuHOepxnF == DJsPORVmAF){QOFGafqUzW = true;}
      if(sTtsUTNFxR == tlNcgPGfYT){XKCXXPDCec = true;}
      if(kdyCTkNYaA == muHEiQOJiF){yNuXJmsakA = true;}
      while(DJsPORVmAF == qHuHOepxnF){geJrtWWmrC = true;}
      while(tlNcgPGfYT == tlNcgPGfYT){lgiNSkubYK = true;}
      while(muHEiQOJiF == muHEiQOJiF){QWttUgxpAt = true;}
      if(LwZkGlIwbu == true){LwZkGlIwbu = false;}
      if(oFJRTbqbBh == true){oFJRTbqbBh = false;}
      if(puxcEIBnfx == true){puxcEIBnfx = false;}
      if(DLDtsxLbWt == true){DLDtsxLbWt = false;}
      if(HJEcdhkpkH == true){HJEcdhkpkH = false;}
      if(ZmIAOQyxgy == true){ZmIAOQyxgy = false;}
      if(kTQdrcBPXV == true){kTQdrcBPXV = false;}
      if(QOFGafqUzW == true){QOFGafqUzW = false;}
      if(XKCXXPDCec == true){XKCXXPDCec = false;}
      if(yNuXJmsakA == true){yNuXJmsakA = false;}
      if(fVRPpKhBZi == true){fVRPpKhBZi = false;}
      if(YdxJaZRrFb == true){YdxJaZRrFb = false;}
      if(ZzjuWCSgxn == true){ZzjuWCSgxn = false;}
      if(mQjzqCsmhM == true){mQjzqCsmhM = false;}
      if(hCcwDUQkxi == true){hCcwDUQkxi = false;}
      if(UBUIafkWrn == true){UBUIafkWrn = false;}
      if(rAEluItySY == true){rAEluItySY = false;}
      if(geJrtWWmrC == true){geJrtWWmrC = false;}
      if(lgiNSkubYK == true){lgiNSkubYK = false;}
      if(QWttUgxpAt == true){QWttUgxpAt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IJCNHXREQO
{ 
  void nAUVDuFxBS()
  { 
      bool RRtMKHrerX = false;
      bool mgJPYtncFf = false;
      bool mQCMXEBrFJ = false;
      bool mpRaqLxeaH = false;
      bool ahWLdlHZrx = false;
      bool zKUnWAOhnG = false;
      bool GAYijxPiXN = false;
      bool wJCyEEtqhl = false;
      bool xazIJcUcDp = false;
      bool wPqUAaImag = false;
      bool VXBeApIWjR = false;
      bool GXzBJfAQYH = false;
      bool bmehQgRgxd = false;
      bool uGPBQYYUHT = false;
      bool TyrliYQoLU = false;
      bool ZrNTFisTNT = false;
      bool XaZFVAHykj = false;
      bool GeJFmctryq = false;
      bool PcVbEDruwg = false;
      bool eFGnwsYmPi = false;
      string ferkNBYddI;
      string FdARfQttOV;
      string MBeIzaYXwV;
      string wpiHbkJHSm;
      string EMKStMQcbq;
      string oBHCTezjkm;
      string bAhHLOtrpt;
      string HlabRAqMOm;
      string JwuEgtigmx;
      string lYWfKDeCGe;
      string RXlgjCafjT;
      string nlUyceEcaQ;
      string eNFsIhPtQO;
      string UnFiUlKOTd;
      string TDwTIzEXDe;
      string yBapzDSsYC;
      string lfOVyzglcq;
      string UpJwxbQljJ;
      string drqkPSMPiQ;
      string SQoQqnnaUJ;
      if(ferkNBYddI == RXlgjCafjT){RRtMKHrerX = true;}
      else if(RXlgjCafjT == ferkNBYddI){VXBeApIWjR = true;}
      if(FdARfQttOV == nlUyceEcaQ){mgJPYtncFf = true;}
      else if(nlUyceEcaQ == FdARfQttOV){GXzBJfAQYH = true;}
      if(MBeIzaYXwV == eNFsIhPtQO){mQCMXEBrFJ = true;}
      else if(eNFsIhPtQO == MBeIzaYXwV){bmehQgRgxd = true;}
      if(wpiHbkJHSm == UnFiUlKOTd){mpRaqLxeaH = true;}
      else if(UnFiUlKOTd == wpiHbkJHSm){uGPBQYYUHT = true;}
      if(EMKStMQcbq == TDwTIzEXDe){ahWLdlHZrx = true;}
      else if(TDwTIzEXDe == EMKStMQcbq){TyrliYQoLU = true;}
      if(oBHCTezjkm == yBapzDSsYC){zKUnWAOhnG = true;}
      else if(yBapzDSsYC == oBHCTezjkm){ZrNTFisTNT = true;}
      if(bAhHLOtrpt == lfOVyzglcq){GAYijxPiXN = true;}
      else if(lfOVyzglcq == bAhHLOtrpt){XaZFVAHykj = true;}
      if(HlabRAqMOm == UpJwxbQljJ){wJCyEEtqhl = true;}
      if(JwuEgtigmx == drqkPSMPiQ){xazIJcUcDp = true;}
      if(lYWfKDeCGe == SQoQqnnaUJ){wPqUAaImag = true;}
      while(UpJwxbQljJ == HlabRAqMOm){GeJFmctryq = true;}
      while(drqkPSMPiQ == drqkPSMPiQ){PcVbEDruwg = true;}
      while(SQoQqnnaUJ == SQoQqnnaUJ){eFGnwsYmPi = true;}
      if(RRtMKHrerX == true){RRtMKHrerX = false;}
      if(mgJPYtncFf == true){mgJPYtncFf = false;}
      if(mQCMXEBrFJ == true){mQCMXEBrFJ = false;}
      if(mpRaqLxeaH == true){mpRaqLxeaH = false;}
      if(ahWLdlHZrx == true){ahWLdlHZrx = false;}
      if(zKUnWAOhnG == true){zKUnWAOhnG = false;}
      if(GAYijxPiXN == true){GAYijxPiXN = false;}
      if(wJCyEEtqhl == true){wJCyEEtqhl = false;}
      if(xazIJcUcDp == true){xazIJcUcDp = false;}
      if(wPqUAaImag == true){wPqUAaImag = false;}
      if(VXBeApIWjR == true){VXBeApIWjR = false;}
      if(GXzBJfAQYH == true){GXzBJfAQYH = false;}
      if(bmehQgRgxd == true){bmehQgRgxd = false;}
      if(uGPBQYYUHT == true){uGPBQYYUHT = false;}
      if(TyrliYQoLU == true){TyrliYQoLU = false;}
      if(ZrNTFisTNT == true){ZrNTFisTNT = false;}
      if(XaZFVAHykj == true){XaZFVAHykj = false;}
      if(GeJFmctryq == true){GeJFmctryq = false;}
      if(PcVbEDruwg == true){PcVbEDruwg = false;}
      if(eFGnwsYmPi == true){eFGnwsYmPi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMCEYLGPIQ
{ 
  void LADaUwSApc()
  { 
      bool ldVKijzkjB = false;
      bool pdEOwhVBAi = false;
      bool GRHPgJMSQb = false;
      bool QKJfnhYsaN = false;
      bool TJiIOezDEy = false;
      bool JCBmETWGcY = false;
      bool WgUIkfTYZN = false;
      bool JcZlOxizAC = false;
      bool KJNRROIVbU = false;
      bool LSPBpmoaWh = false;
      bool KZdqogbOYG = false;
      bool jWFaONSCpW = false;
      bool XyxFCpMXua = false;
      bool IIbRqjfVck = false;
      bool lsxUjnMomc = false;
      bool TljAKMcXoy = false;
      bool TDTxybumid = false;
      bool gwYFjdBcUN = false;
      bool dXkSHVXbHe = false;
      bool GHgeQhZzVI = false;
      string zjuRDIjxeU;
      string oPynIfcOrz;
      string fxSKPMtCtw;
      string ZVohsmdWAY;
      string iybAYpetIS;
      string VqmbUBQjCp;
      string NgDiuSZQuU;
      string CGNSPgVRlY;
      string gztaZhiMMq;
      string WtUJLCurFF;
      string POzmQPcTMn;
      string eyydJNlcIM;
      string jMEDyIlDHN;
      string ldMfISAGJK;
      string EPAYMXupAx;
      string PSirVDJwoI;
      string dYLyCBlRUp;
      string NeSyHTMfqZ;
      string MuDKyStTJF;
      string IERAgfDCVK;
      if(zjuRDIjxeU == POzmQPcTMn){ldVKijzkjB = true;}
      else if(POzmQPcTMn == zjuRDIjxeU){KZdqogbOYG = true;}
      if(oPynIfcOrz == eyydJNlcIM){pdEOwhVBAi = true;}
      else if(eyydJNlcIM == oPynIfcOrz){jWFaONSCpW = true;}
      if(fxSKPMtCtw == jMEDyIlDHN){GRHPgJMSQb = true;}
      else if(jMEDyIlDHN == fxSKPMtCtw){XyxFCpMXua = true;}
      if(ZVohsmdWAY == ldMfISAGJK){QKJfnhYsaN = true;}
      else if(ldMfISAGJK == ZVohsmdWAY){IIbRqjfVck = true;}
      if(iybAYpetIS == EPAYMXupAx){TJiIOezDEy = true;}
      else if(EPAYMXupAx == iybAYpetIS){lsxUjnMomc = true;}
      if(VqmbUBQjCp == PSirVDJwoI){JCBmETWGcY = true;}
      else if(PSirVDJwoI == VqmbUBQjCp){TljAKMcXoy = true;}
      if(NgDiuSZQuU == dYLyCBlRUp){WgUIkfTYZN = true;}
      else if(dYLyCBlRUp == NgDiuSZQuU){TDTxybumid = true;}
      if(CGNSPgVRlY == NeSyHTMfqZ){JcZlOxizAC = true;}
      if(gztaZhiMMq == MuDKyStTJF){KJNRROIVbU = true;}
      if(WtUJLCurFF == IERAgfDCVK){LSPBpmoaWh = true;}
      while(NeSyHTMfqZ == CGNSPgVRlY){gwYFjdBcUN = true;}
      while(MuDKyStTJF == MuDKyStTJF){dXkSHVXbHe = true;}
      while(IERAgfDCVK == IERAgfDCVK){GHgeQhZzVI = true;}
      if(ldVKijzkjB == true){ldVKijzkjB = false;}
      if(pdEOwhVBAi == true){pdEOwhVBAi = false;}
      if(GRHPgJMSQb == true){GRHPgJMSQb = false;}
      if(QKJfnhYsaN == true){QKJfnhYsaN = false;}
      if(TJiIOezDEy == true){TJiIOezDEy = false;}
      if(JCBmETWGcY == true){JCBmETWGcY = false;}
      if(WgUIkfTYZN == true){WgUIkfTYZN = false;}
      if(JcZlOxizAC == true){JcZlOxizAC = false;}
      if(KJNRROIVbU == true){KJNRROIVbU = false;}
      if(LSPBpmoaWh == true){LSPBpmoaWh = false;}
      if(KZdqogbOYG == true){KZdqogbOYG = false;}
      if(jWFaONSCpW == true){jWFaONSCpW = false;}
      if(XyxFCpMXua == true){XyxFCpMXua = false;}
      if(IIbRqjfVck == true){IIbRqjfVck = false;}
      if(lsxUjnMomc == true){lsxUjnMomc = false;}
      if(TljAKMcXoy == true){TljAKMcXoy = false;}
      if(TDTxybumid == true){TDTxybumid = false;}
      if(gwYFjdBcUN == true){gwYFjdBcUN = false;}
      if(dXkSHVXbHe == true){dXkSHVXbHe = false;}
      if(GHgeQhZzVI == true){GHgeQhZzVI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIJPKYXNAY
{ 
  void stbGLXuijZ()
  { 
      bool GwXtwiqKoK = false;
      bool qVxitbTnCS = false;
      bool IwRkwBgqwe = false;
      bool DQMxHHzGFk = false;
      bool DLHEAxyhEK = false;
      bool nGjhzJemyt = false;
      bool CzOJHaIzam = false;
      bool bNiQPwoMjy = false;
      bool Dzlkpwfeyx = false;
      bool bMIKiDxxwZ = false;
      bool oyGRhaXTRC = false;
      bool URCzqDNcSK = false;
      bool udAcKPFXhL = false;
      bool yqPKJErTDP = false;
      bool YMMwcJJISe = false;
      bool pUdleKycHR = false;
      bool UzkFDdCrom = false;
      bool KsYCkhREAA = false;
      bool GwECVdMdey = false;
      bool FPMkuYaGrz = false;
      string yYoRlEyxGE;
      string oCbldZXwDa;
      string pXnQEFQMda;
      string cjEtJAHfIY;
      string epsUyHrXmy;
      string PTOUoZkXNf;
      string mkTeaExgbc;
      string RqneuzdSSw;
      string NsYeKJUjEi;
      string PiScksWNts;
      string JKuKgYfjYp;
      string wRFQRsMoUR;
      string jNbsMhYKsC;
      string cQYYmCxOyl;
      string ckKOmydBKr;
      string ghscJuiCxy;
      string zUpWNergcP;
      string wxpinyDNFN;
      string EXABUtWwPr;
      string SuQzlIumAH;
      if(yYoRlEyxGE == JKuKgYfjYp){GwXtwiqKoK = true;}
      else if(JKuKgYfjYp == yYoRlEyxGE){oyGRhaXTRC = true;}
      if(oCbldZXwDa == wRFQRsMoUR){qVxitbTnCS = true;}
      else if(wRFQRsMoUR == oCbldZXwDa){URCzqDNcSK = true;}
      if(pXnQEFQMda == jNbsMhYKsC){IwRkwBgqwe = true;}
      else if(jNbsMhYKsC == pXnQEFQMda){udAcKPFXhL = true;}
      if(cjEtJAHfIY == cQYYmCxOyl){DQMxHHzGFk = true;}
      else if(cQYYmCxOyl == cjEtJAHfIY){yqPKJErTDP = true;}
      if(epsUyHrXmy == ckKOmydBKr){DLHEAxyhEK = true;}
      else if(ckKOmydBKr == epsUyHrXmy){YMMwcJJISe = true;}
      if(PTOUoZkXNf == ghscJuiCxy){nGjhzJemyt = true;}
      else if(ghscJuiCxy == PTOUoZkXNf){pUdleKycHR = true;}
      if(mkTeaExgbc == zUpWNergcP){CzOJHaIzam = true;}
      else if(zUpWNergcP == mkTeaExgbc){UzkFDdCrom = true;}
      if(RqneuzdSSw == wxpinyDNFN){bNiQPwoMjy = true;}
      if(NsYeKJUjEi == EXABUtWwPr){Dzlkpwfeyx = true;}
      if(PiScksWNts == SuQzlIumAH){bMIKiDxxwZ = true;}
      while(wxpinyDNFN == RqneuzdSSw){KsYCkhREAA = true;}
      while(EXABUtWwPr == EXABUtWwPr){GwECVdMdey = true;}
      while(SuQzlIumAH == SuQzlIumAH){FPMkuYaGrz = true;}
      if(GwXtwiqKoK == true){GwXtwiqKoK = false;}
      if(qVxitbTnCS == true){qVxitbTnCS = false;}
      if(IwRkwBgqwe == true){IwRkwBgqwe = false;}
      if(DQMxHHzGFk == true){DQMxHHzGFk = false;}
      if(DLHEAxyhEK == true){DLHEAxyhEK = false;}
      if(nGjhzJemyt == true){nGjhzJemyt = false;}
      if(CzOJHaIzam == true){CzOJHaIzam = false;}
      if(bNiQPwoMjy == true){bNiQPwoMjy = false;}
      if(Dzlkpwfeyx == true){Dzlkpwfeyx = false;}
      if(bMIKiDxxwZ == true){bMIKiDxxwZ = false;}
      if(oyGRhaXTRC == true){oyGRhaXTRC = false;}
      if(URCzqDNcSK == true){URCzqDNcSK = false;}
      if(udAcKPFXhL == true){udAcKPFXhL = false;}
      if(yqPKJErTDP == true){yqPKJErTDP = false;}
      if(YMMwcJJISe == true){YMMwcJJISe = false;}
      if(pUdleKycHR == true){pUdleKycHR = false;}
      if(UzkFDdCrom == true){UzkFDdCrom = false;}
      if(KsYCkhREAA == true){KsYCkhREAA = false;}
      if(GwECVdMdey == true){GwECVdMdey = false;}
      if(FPMkuYaGrz == true){FPMkuYaGrz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDNWGZTZMQ
{ 
  void AOGqQghhsQ()
  { 
      bool rPsjEJWmGP = false;
      bool UcTTuoIPly = false;
      bool ufHnoWlLCL = false;
      bool cDZOXAxaYa = false;
      bool zXJzPWZAzs = false;
      bool JWnWDMHEth = false;
      bool XKkumQCEuu = false;
      bool qgqKzXWIYR = false;
      bool wlLIBGOCKL = false;
      bool rrgpDnlNLy = false;
      bool UVEECcedXe = false;
      bool pzfbllycsg = false;
      bool BzsjCyAAGK = false;
      bool lIwZxagHGY = false;
      bool akefVrMEER = false;
      bool pJUewUcUBD = false;
      bool cdWNshCFdL = false;
      bool EqVUGQUNNK = false;
      bool luwoTcmRcc = false;
      bool yMFDuwORln = false;
      string oNJtjYZPfX;
      string yPNRdCUDuA;
      string GnMTeoCXla;
      string QcSRymtmgj;
      string aSdIwWGWeT;
      string WZExHAAoOu;
      string WCdEHUxwTp;
      string HgVLYnJDWI;
      string herREpYVKx;
      string lFYlMYnZBb;
      string ZKDoMoErXT;
      string qxSGMqJLAQ;
      string wblVECIjyA;
      string zjBuhXbDFP;
      string lfxpGnlRYU;
      string PcYkfyXhjK;
      string fTsWUGwWYo;
      string PFGkdPduOQ;
      string PqLdkVKPPj;
      string zsTtiSlZVz;
      if(oNJtjYZPfX == ZKDoMoErXT){rPsjEJWmGP = true;}
      else if(ZKDoMoErXT == oNJtjYZPfX){UVEECcedXe = true;}
      if(yPNRdCUDuA == qxSGMqJLAQ){UcTTuoIPly = true;}
      else if(qxSGMqJLAQ == yPNRdCUDuA){pzfbllycsg = true;}
      if(GnMTeoCXla == wblVECIjyA){ufHnoWlLCL = true;}
      else if(wblVECIjyA == GnMTeoCXla){BzsjCyAAGK = true;}
      if(QcSRymtmgj == zjBuhXbDFP){cDZOXAxaYa = true;}
      else if(zjBuhXbDFP == QcSRymtmgj){lIwZxagHGY = true;}
      if(aSdIwWGWeT == lfxpGnlRYU){zXJzPWZAzs = true;}
      else if(lfxpGnlRYU == aSdIwWGWeT){akefVrMEER = true;}
      if(WZExHAAoOu == PcYkfyXhjK){JWnWDMHEth = true;}
      else if(PcYkfyXhjK == WZExHAAoOu){pJUewUcUBD = true;}
      if(WCdEHUxwTp == fTsWUGwWYo){XKkumQCEuu = true;}
      else if(fTsWUGwWYo == WCdEHUxwTp){cdWNshCFdL = true;}
      if(HgVLYnJDWI == PFGkdPduOQ){qgqKzXWIYR = true;}
      if(herREpYVKx == PqLdkVKPPj){wlLIBGOCKL = true;}
      if(lFYlMYnZBb == zsTtiSlZVz){rrgpDnlNLy = true;}
      while(PFGkdPduOQ == HgVLYnJDWI){EqVUGQUNNK = true;}
      while(PqLdkVKPPj == PqLdkVKPPj){luwoTcmRcc = true;}
      while(zsTtiSlZVz == zsTtiSlZVz){yMFDuwORln = true;}
      if(rPsjEJWmGP == true){rPsjEJWmGP = false;}
      if(UcTTuoIPly == true){UcTTuoIPly = false;}
      if(ufHnoWlLCL == true){ufHnoWlLCL = false;}
      if(cDZOXAxaYa == true){cDZOXAxaYa = false;}
      if(zXJzPWZAzs == true){zXJzPWZAzs = false;}
      if(JWnWDMHEth == true){JWnWDMHEth = false;}
      if(XKkumQCEuu == true){XKkumQCEuu = false;}
      if(qgqKzXWIYR == true){qgqKzXWIYR = false;}
      if(wlLIBGOCKL == true){wlLIBGOCKL = false;}
      if(rrgpDnlNLy == true){rrgpDnlNLy = false;}
      if(UVEECcedXe == true){UVEECcedXe = false;}
      if(pzfbllycsg == true){pzfbllycsg = false;}
      if(BzsjCyAAGK == true){BzsjCyAAGK = false;}
      if(lIwZxagHGY == true){lIwZxagHGY = false;}
      if(akefVrMEER == true){akefVrMEER = false;}
      if(pJUewUcUBD == true){pJUewUcUBD = false;}
      if(cdWNshCFdL == true){cdWNshCFdL = false;}
      if(EqVUGQUNNK == true){EqVUGQUNNK = false;}
      if(luwoTcmRcc == true){luwoTcmRcc = false;}
      if(yMFDuwORln == true){yMFDuwORln = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGICHXFRGJ
{ 
  void mpkCsdOsgz()
  { 
      bool cmkpXJghlS = false;
      bool qlpMHYIhDn = false;
      bool unYQUKQSGE = false;
      bool IaCFjMOolb = false;
      bool RgEqNOPoUF = false;
      bool nqoAAoNUVM = false;
      bool rNahKPijct = false;
      bool JSubVOigCG = false;
      bool uaxAPQlBFu = false;
      bool ztTZiDFWgy = false;
      bool eeMawVwMdk = false;
      bool GfSORQQZRt = false;
      bool chehuPyUrS = false;
      bool ILADaPOWEt = false;
      bool UZXTnSbEIR = false;
      bool mfFlVxAeeg = false;
      bool WbTLctfOnC = false;
      bool CsVWZDKKsc = false;
      bool msMaecFNhd = false;
      bool OirXWrFLqt = false;
      string DEWyPHYgmK;
      string DVEjXRIrLh;
      string kVmPhnyFlP;
      string EyfqejZInL;
      string sCfgEDLChV;
      string flpsyhQGPb;
      string JTtXFFoNEn;
      string qAEAnipGKd;
      string buWPiSHmrx;
      string STsLCZHHaz;
      string NyytefgpEP;
      string rKwlzNweom;
      string yCUGUXHryO;
      string aheLPdxbjD;
      string kQhcFHWGMn;
      string cbSnAKcqZH;
      string YnronJejVV;
      string QTukBgTqBM;
      string AAfJkzOqKE;
      string AFCbdwYsou;
      if(DEWyPHYgmK == NyytefgpEP){cmkpXJghlS = true;}
      else if(NyytefgpEP == DEWyPHYgmK){eeMawVwMdk = true;}
      if(DVEjXRIrLh == rKwlzNweom){qlpMHYIhDn = true;}
      else if(rKwlzNweom == DVEjXRIrLh){GfSORQQZRt = true;}
      if(kVmPhnyFlP == yCUGUXHryO){unYQUKQSGE = true;}
      else if(yCUGUXHryO == kVmPhnyFlP){chehuPyUrS = true;}
      if(EyfqejZInL == aheLPdxbjD){IaCFjMOolb = true;}
      else if(aheLPdxbjD == EyfqejZInL){ILADaPOWEt = true;}
      if(sCfgEDLChV == kQhcFHWGMn){RgEqNOPoUF = true;}
      else if(kQhcFHWGMn == sCfgEDLChV){UZXTnSbEIR = true;}
      if(flpsyhQGPb == cbSnAKcqZH){nqoAAoNUVM = true;}
      else if(cbSnAKcqZH == flpsyhQGPb){mfFlVxAeeg = true;}
      if(JTtXFFoNEn == YnronJejVV){rNahKPijct = true;}
      else if(YnronJejVV == JTtXFFoNEn){WbTLctfOnC = true;}
      if(qAEAnipGKd == QTukBgTqBM){JSubVOigCG = true;}
      if(buWPiSHmrx == AAfJkzOqKE){uaxAPQlBFu = true;}
      if(STsLCZHHaz == AFCbdwYsou){ztTZiDFWgy = true;}
      while(QTukBgTqBM == qAEAnipGKd){CsVWZDKKsc = true;}
      while(AAfJkzOqKE == AAfJkzOqKE){msMaecFNhd = true;}
      while(AFCbdwYsou == AFCbdwYsou){OirXWrFLqt = true;}
      if(cmkpXJghlS == true){cmkpXJghlS = false;}
      if(qlpMHYIhDn == true){qlpMHYIhDn = false;}
      if(unYQUKQSGE == true){unYQUKQSGE = false;}
      if(IaCFjMOolb == true){IaCFjMOolb = false;}
      if(RgEqNOPoUF == true){RgEqNOPoUF = false;}
      if(nqoAAoNUVM == true){nqoAAoNUVM = false;}
      if(rNahKPijct == true){rNahKPijct = false;}
      if(JSubVOigCG == true){JSubVOigCG = false;}
      if(uaxAPQlBFu == true){uaxAPQlBFu = false;}
      if(ztTZiDFWgy == true){ztTZiDFWgy = false;}
      if(eeMawVwMdk == true){eeMawVwMdk = false;}
      if(GfSORQQZRt == true){GfSORQQZRt = false;}
      if(chehuPyUrS == true){chehuPyUrS = false;}
      if(ILADaPOWEt == true){ILADaPOWEt = false;}
      if(UZXTnSbEIR == true){UZXTnSbEIR = false;}
      if(mfFlVxAeeg == true){mfFlVxAeeg = false;}
      if(WbTLctfOnC == true){WbTLctfOnC = false;}
      if(CsVWZDKKsc == true){CsVWZDKKsc = false;}
      if(msMaecFNhd == true){msMaecFNhd = false;}
      if(OirXWrFLqt == true){OirXWrFLqt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWWCYOCKUD
{ 
  void XKisbfwgdn()
  { 
      bool BVbQIhDYBO = false;
      bool ooNQzPIihN = false;
      bool eQxjhALVKO = false;
      bool xuBGEnKxyU = false;
      bool QbGmjjTnqd = false;
      bool GHXZokYqhH = false;
      bool VhOmQtnGMK = false;
      bool FLkNxCJKzx = false;
      bool fXefHpWaQT = false;
      bool PSOpyhNTWp = false;
      bool wMbfYuWKbm = false;
      bool aNqkbyCheZ = false;
      bool WMprtlwtOO = false;
      bool opnJASuyHM = false;
      bool TLzdrCbdOA = false;
      bool fenwSjWikl = false;
      bool zbuMxjZhkI = false;
      bool CDZSGLMLAr = false;
      bool JSfOiJCrpP = false;
      bool uMNVNqQlfI = false;
      string PwiYjibyxj;
      string tdWMKSRGfJ;
      string zAuyBgqErd;
      string XCIWZoLhln;
      string PkuJSDnDYz;
      string IcfehPAkWD;
      string rXGTLrUzmU;
      string HiUrsOFlfy;
      string rmerUuVcoK;
      string naKiurdaxZ;
      string hnQDqZInlS;
      string KNEYKErNyQ;
      string WrKbggXlxB;
      string kdoFPDWbBu;
      string lhqVAaVkXp;
      string zQcfDpdoWK;
      string BWpjhfYzJH;
      string hQMDdoBoaF;
      string KlNGCTBIBY;
      string ZhEpsPqGmU;
      if(PwiYjibyxj == hnQDqZInlS){BVbQIhDYBO = true;}
      else if(hnQDqZInlS == PwiYjibyxj){wMbfYuWKbm = true;}
      if(tdWMKSRGfJ == KNEYKErNyQ){ooNQzPIihN = true;}
      else if(KNEYKErNyQ == tdWMKSRGfJ){aNqkbyCheZ = true;}
      if(zAuyBgqErd == WrKbggXlxB){eQxjhALVKO = true;}
      else if(WrKbggXlxB == zAuyBgqErd){WMprtlwtOO = true;}
      if(XCIWZoLhln == kdoFPDWbBu){xuBGEnKxyU = true;}
      else if(kdoFPDWbBu == XCIWZoLhln){opnJASuyHM = true;}
      if(PkuJSDnDYz == lhqVAaVkXp){QbGmjjTnqd = true;}
      else if(lhqVAaVkXp == PkuJSDnDYz){TLzdrCbdOA = true;}
      if(IcfehPAkWD == zQcfDpdoWK){GHXZokYqhH = true;}
      else if(zQcfDpdoWK == IcfehPAkWD){fenwSjWikl = true;}
      if(rXGTLrUzmU == BWpjhfYzJH){VhOmQtnGMK = true;}
      else if(BWpjhfYzJH == rXGTLrUzmU){zbuMxjZhkI = true;}
      if(HiUrsOFlfy == hQMDdoBoaF){FLkNxCJKzx = true;}
      if(rmerUuVcoK == KlNGCTBIBY){fXefHpWaQT = true;}
      if(naKiurdaxZ == ZhEpsPqGmU){PSOpyhNTWp = true;}
      while(hQMDdoBoaF == HiUrsOFlfy){CDZSGLMLAr = true;}
      while(KlNGCTBIBY == KlNGCTBIBY){JSfOiJCrpP = true;}
      while(ZhEpsPqGmU == ZhEpsPqGmU){uMNVNqQlfI = true;}
      if(BVbQIhDYBO == true){BVbQIhDYBO = false;}
      if(ooNQzPIihN == true){ooNQzPIihN = false;}
      if(eQxjhALVKO == true){eQxjhALVKO = false;}
      if(xuBGEnKxyU == true){xuBGEnKxyU = false;}
      if(QbGmjjTnqd == true){QbGmjjTnqd = false;}
      if(GHXZokYqhH == true){GHXZokYqhH = false;}
      if(VhOmQtnGMK == true){VhOmQtnGMK = false;}
      if(FLkNxCJKzx == true){FLkNxCJKzx = false;}
      if(fXefHpWaQT == true){fXefHpWaQT = false;}
      if(PSOpyhNTWp == true){PSOpyhNTWp = false;}
      if(wMbfYuWKbm == true){wMbfYuWKbm = false;}
      if(aNqkbyCheZ == true){aNqkbyCheZ = false;}
      if(WMprtlwtOO == true){WMprtlwtOO = false;}
      if(opnJASuyHM == true){opnJASuyHM = false;}
      if(TLzdrCbdOA == true){TLzdrCbdOA = false;}
      if(fenwSjWikl == true){fenwSjWikl = false;}
      if(zbuMxjZhkI == true){zbuMxjZhkI = false;}
      if(CDZSGLMLAr == true){CDZSGLMLAr = false;}
      if(JSfOiJCrpP == true){JSfOiJCrpP = false;}
      if(uMNVNqQlfI == true){uMNVNqQlfI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPQTRODRTJ
{ 
  void FRlWceZBNn()
  { 
      bool XHWbBtMYAl = false;
      bool ajXSopjLAc = false;
      bool lXXNmRjgYm = false;
      bool RTTLlFsZCc = false;
      bool pfbRgaGZny = false;
      bool gVSejzjJoj = false;
      bool KezNTGPMgi = false;
      bool xKIXlFuGfM = false;
      bool LKsZGwAoal = false;
      bool VijSRKfOya = false;
      bool KtsEBWMure = false;
      bool EddbYzkYHX = false;
      bool GaltNOZpFb = false;
      bool YgIECQQnYi = false;
      bool iFwuhrEItR = false;
      bool YGGZTiIyqm = false;
      bool wVoQFWUYZH = false;
      bool ixAXnAdpMU = false;
      bool JRwmCRahkS = false;
      bool ISxllMPfpL = false;
      string RsDMoENKrR;
      string jotDQmrctY;
      string fzUQCaggjX;
      string wXymMcnwHH;
      string FpOdtkfrzB;
      string LhGmuRXmKO;
      string XgaTUMpGpm;
      string zuUmTpkpVQ;
      string ungiLOQKrt;
      string FBlsiXPtJg;
      string tYCLBQMTSF;
      string ggQsTizrIF;
      string weNuhyJaDu;
      string ZpgoWVlVgu;
      string CxqmNXjsZz;
      string XXlEkOLGcD;
      string GkPXepAbVx;
      string xdKNDznahJ;
      string NQBEWCEcDI;
      string KescnQgTHW;
      if(RsDMoENKrR == tYCLBQMTSF){XHWbBtMYAl = true;}
      else if(tYCLBQMTSF == RsDMoENKrR){KtsEBWMure = true;}
      if(jotDQmrctY == ggQsTizrIF){ajXSopjLAc = true;}
      else if(ggQsTizrIF == jotDQmrctY){EddbYzkYHX = true;}
      if(fzUQCaggjX == weNuhyJaDu){lXXNmRjgYm = true;}
      else if(weNuhyJaDu == fzUQCaggjX){GaltNOZpFb = true;}
      if(wXymMcnwHH == ZpgoWVlVgu){RTTLlFsZCc = true;}
      else if(ZpgoWVlVgu == wXymMcnwHH){YgIECQQnYi = true;}
      if(FpOdtkfrzB == CxqmNXjsZz){pfbRgaGZny = true;}
      else if(CxqmNXjsZz == FpOdtkfrzB){iFwuhrEItR = true;}
      if(LhGmuRXmKO == XXlEkOLGcD){gVSejzjJoj = true;}
      else if(XXlEkOLGcD == LhGmuRXmKO){YGGZTiIyqm = true;}
      if(XgaTUMpGpm == GkPXepAbVx){KezNTGPMgi = true;}
      else if(GkPXepAbVx == XgaTUMpGpm){wVoQFWUYZH = true;}
      if(zuUmTpkpVQ == xdKNDznahJ){xKIXlFuGfM = true;}
      if(ungiLOQKrt == NQBEWCEcDI){LKsZGwAoal = true;}
      if(FBlsiXPtJg == KescnQgTHW){VijSRKfOya = true;}
      while(xdKNDznahJ == zuUmTpkpVQ){ixAXnAdpMU = true;}
      while(NQBEWCEcDI == NQBEWCEcDI){JRwmCRahkS = true;}
      while(KescnQgTHW == KescnQgTHW){ISxllMPfpL = true;}
      if(XHWbBtMYAl == true){XHWbBtMYAl = false;}
      if(ajXSopjLAc == true){ajXSopjLAc = false;}
      if(lXXNmRjgYm == true){lXXNmRjgYm = false;}
      if(RTTLlFsZCc == true){RTTLlFsZCc = false;}
      if(pfbRgaGZny == true){pfbRgaGZny = false;}
      if(gVSejzjJoj == true){gVSejzjJoj = false;}
      if(KezNTGPMgi == true){KezNTGPMgi = false;}
      if(xKIXlFuGfM == true){xKIXlFuGfM = false;}
      if(LKsZGwAoal == true){LKsZGwAoal = false;}
      if(VijSRKfOya == true){VijSRKfOya = false;}
      if(KtsEBWMure == true){KtsEBWMure = false;}
      if(EddbYzkYHX == true){EddbYzkYHX = false;}
      if(GaltNOZpFb == true){GaltNOZpFb = false;}
      if(YgIECQQnYi == true){YgIECQQnYi = false;}
      if(iFwuhrEItR == true){iFwuhrEItR = false;}
      if(YGGZTiIyqm == true){YGGZTiIyqm = false;}
      if(wVoQFWUYZH == true){wVoQFWUYZH = false;}
      if(ixAXnAdpMU == true){ixAXnAdpMU = false;}
      if(JRwmCRahkS == true){JRwmCRahkS = false;}
      if(ISxllMPfpL == true){ISxllMPfpL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPGZIVVUFS
{ 
  void SnuQMVkDQA()
  { 
      bool hkoVBNcpHD = false;
      bool UcAaMTwABL = false;
      bool rqHNgxVpYy = false;
      bool zqdFwMIpre = false;
      bool sPSgeNrgPn = false;
      bool BqOOQpcanD = false;
      bool rmQIEdytdA = false;
      bool KFIWSbYaiS = false;
      bool FnZjwHcPoG = false;
      bool jgCnlGyKcA = false;
      bool PxCPdwhqwn = false;
      bool RBrVyDMgLw = false;
      bool AhEXQcDTkM = false;
      bool cNxhDHlKGA = false;
      bool YlTAohofph = false;
      bool sRzgAgrezA = false;
      bool rOGjLDEJSp = false;
      bool RCZKWOOEih = false;
      bool mWdCSKOQhV = false;
      bool OHKFHKejok = false;
      string MCzouJBRyF;
      string OtBOJGACuq;
      string FfSXagXLmB;
      string gTlfNgdGFX;
      string YiZfTCOiNO;
      string KLCxXgibOO;
      string kpexYuHUAc;
      string cswXSWFlDX;
      string RoyYqURoIg;
      string xBrpmiDcHY;
      string ushkkROedA;
      string axXpwwqGGD;
      string dSMTeaAGjj;
      string SceecYGNmY;
      string GlKHFAdCsq;
      string qwWEtcgNFK;
      string RItthxSsNX;
      string ocTgwqHENe;
      string xxMsrVFakz;
      string qrHcHyrPZI;
      if(MCzouJBRyF == ushkkROedA){hkoVBNcpHD = true;}
      else if(ushkkROedA == MCzouJBRyF){PxCPdwhqwn = true;}
      if(OtBOJGACuq == axXpwwqGGD){UcAaMTwABL = true;}
      else if(axXpwwqGGD == OtBOJGACuq){RBrVyDMgLw = true;}
      if(FfSXagXLmB == dSMTeaAGjj){rqHNgxVpYy = true;}
      else if(dSMTeaAGjj == FfSXagXLmB){AhEXQcDTkM = true;}
      if(gTlfNgdGFX == SceecYGNmY){zqdFwMIpre = true;}
      else if(SceecYGNmY == gTlfNgdGFX){cNxhDHlKGA = true;}
      if(YiZfTCOiNO == GlKHFAdCsq){sPSgeNrgPn = true;}
      else if(GlKHFAdCsq == YiZfTCOiNO){YlTAohofph = true;}
      if(KLCxXgibOO == qwWEtcgNFK){BqOOQpcanD = true;}
      else if(qwWEtcgNFK == KLCxXgibOO){sRzgAgrezA = true;}
      if(kpexYuHUAc == RItthxSsNX){rmQIEdytdA = true;}
      else if(RItthxSsNX == kpexYuHUAc){rOGjLDEJSp = true;}
      if(cswXSWFlDX == ocTgwqHENe){KFIWSbYaiS = true;}
      if(RoyYqURoIg == xxMsrVFakz){FnZjwHcPoG = true;}
      if(xBrpmiDcHY == qrHcHyrPZI){jgCnlGyKcA = true;}
      while(ocTgwqHENe == cswXSWFlDX){RCZKWOOEih = true;}
      while(xxMsrVFakz == xxMsrVFakz){mWdCSKOQhV = true;}
      while(qrHcHyrPZI == qrHcHyrPZI){OHKFHKejok = true;}
      if(hkoVBNcpHD == true){hkoVBNcpHD = false;}
      if(UcAaMTwABL == true){UcAaMTwABL = false;}
      if(rqHNgxVpYy == true){rqHNgxVpYy = false;}
      if(zqdFwMIpre == true){zqdFwMIpre = false;}
      if(sPSgeNrgPn == true){sPSgeNrgPn = false;}
      if(BqOOQpcanD == true){BqOOQpcanD = false;}
      if(rmQIEdytdA == true){rmQIEdytdA = false;}
      if(KFIWSbYaiS == true){KFIWSbYaiS = false;}
      if(FnZjwHcPoG == true){FnZjwHcPoG = false;}
      if(jgCnlGyKcA == true){jgCnlGyKcA = false;}
      if(PxCPdwhqwn == true){PxCPdwhqwn = false;}
      if(RBrVyDMgLw == true){RBrVyDMgLw = false;}
      if(AhEXQcDTkM == true){AhEXQcDTkM = false;}
      if(cNxhDHlKGA == true){cNxhDHlKGA = false;}
      if(YlTAohofph == true){YlTAohofph = false;}
      if(sRzgAgrezA == true){sRzgAgrezA = false;}
      if(rOGjLDEJSp == true){rOGjLDEJSp = false;}
      if(RCZKWOOEih == true){RCZKWOOEih = false;}
      if(mWdCSKOQhV == true){mWdCSKOQhV = false;}
      if(OHKFHKejok == true){OHKFHKejok = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIQFLYMZRX
{ 
  void uPlNmQXcYA()
  { 
      bool TWGXuCJQxH = false;
      bool PLZsWgAfAc = false;
      bool fcOzXqKHti = false;
      bool wkcuurDpre = false;
      bool IYixydGPol = false;
      bool apYuXpIHzD = false;
      bool rBVOKdiexd = false;
      bool cJnUUGsQBt = false;
      bool juSIIGMgWE = false;
      bool iwqnmHDUmT = false;
      bool tbRLJQCDaR = false;
      bool xrGFTwiNGE = false;
      bool QCIstfSzhM = false;
      bool DYcgzIdHyq = false;
      bool EJFEHqplUp = false;
      bool YoOhDrSXQc = false;
      bool yCUNOXOZFK = false;
      bool SaPOAHwDlD = false;
      bool pgdrnNKucH = false;
      bool oFpUsBnrpi = false;
      string yBhQGdinIX;
      string ZAbWquBJpN;
      string xhGWjDsieC;
      string UzotgWACGj;
      string EFJKIDQnTm;
      string VRhuiPuLgD;
      string jzJFDZLgpT;
      string uzCGJrYwNf;
      string lEPqgDRsLQ;
      string bnUCzFwDHi;
      string riyzrVOalq;
      string qyyBQeiSYz;
      string IRVYrGdAHE;
      string uUoenDGPyK;
      string opHUZcpTlT;
      string VdeHZZNYHl;
      string qOThuVJSMN;
      string YSTNJSKByO;
      string PKNmhRpgEN;
      string ogILSaVYYD;
      if(yBhQGdinIX == riyzrVOalq){TWGXuCJQxH = true;}
      else if(riyzrVOalq == yBhQGdinIX){tbRLJQCDaR = true;}
      if(ZAbWquBJpN == qyyBQeiSYz){PLZsWgAfAc = true;}
      else if(qyyBQeiSYz == ZAbWquBJpN){xrGFTwiNGE = true;}
      if(xhGWjDsieC == IRVYrGdAHE){fcOzXqKHti = true;}
      else if(IRVYrGdAHE == xhGWjDsieC){QCIstfSzhM = true;}
      if(UzotgWACGj == uUoenDGPyK){wkcuurDpre = true;}
      else if(uUoenDGPyK == UzotgWACGj){DYcgzIdHyq = true;}
      if(EFJKIDQnTm == opHUZcpTlT){IYixydGPol = true;}
      else if(opHUZcpTlT == EFJKIDQnTm){EJFEHqplUp = true;}
      if(VRhuiPuLgD == VdeHZZNYHl){apYuXpIHzD = true;}
      else if(VdeHZZNYHl == VRhuiPuLgD){YoOhDrSXQc = true;}
      if(jzJFDZLgpT == qOThuVJSMN){rBVOKdiexd = true;}
      else if(qOThuVJSMN == jzJFDZLgpT){yCUNOXOZFK = true;}
      if(uzCGJrYwNf == YSTNJSKByO){cJnUUGsQBt = true;}
      if(lEPqgDRsLQ == PKNmhRpgEN){juSIIGMgWE = true;}
      if(bnUCzFwDHi == ogILSaVYYD){iwqnmHDUmT = true;}
      while(YSTNJSKByO == uzCGJrYwNf){SaPOAHwDlD = true;}
      while(PKNmhRpgEN == PKNmhRpgEN){pgdrnNKucH = true;}
      while(ogILSaVYYD == ogILSaVYYD){oFpUsBnrpi = true;}
      if(TWGXuCJQxH == true){TWGXuCJQxH = false;}
      if(PLZsWgAfAc == true){PLZsWgAfAc = false;}
      if(fcOzXqKHti == true){fcOzXqKHti = false;}
      if(wkcuurDpre == true){wkcuurDpre = false;}
      if(IYixydGPol == true){IYixydGPol = false;}
      if(apYuXpIHzD == true){apYuXpIHzD = false;}
      if(rBVOKdiexd == true){rBVOKdiexd = false;}
      if(cJnUUGsQBt == true){cJnUUGsQBt = false;}
      if(juSIIGMgWE == true){juSIIGMgWE = false;}
      if(iwqnmHDUmT == true){iwqnmHDUmT = false;}
      if(tbRLJQCDaR == true){tbRLJQCDaR = false;}
      if(xrGFTwiNGE == true){xrGFTwiNGE = false;}
      if(QCIstfSzhM == true){QCIstfSzhM = false;}
      if(DYcgzIdHyq == true){DYcgzIdHyq = false;}
      if(EJFEHqplUp == true){EJFEHqplUp = false;}
      if(YoOhDrSXQc == true){YoOhDrSXQc = false;}
      if(yCUNOXOZFK == true){yCUNOXOZFK = false;}
      if(SaPOAHwDlD == true){SaPOAHwDlD = false;}
      if(pgdrnNKucH == true){pgdrnNKucH = false;}
      if(oFpUsBnrpi == true){oFpUsBnrpi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEWQZZLDAD
{ 
  void WfYPmmaiLt()
  { 
      bool nbcaVEkwXW = false;
      bool DQhkTgngbf = false;
      bool CRMRtitEIr = false;
      bool AzqxnMoIlV = false;
      bool BCTROttgHi = false;
      bool gMMaMVOKgm = false;
      bool JfmfVEYjwG = false;
      bool rftGezyuDA = false;
      bool oNxZKnlPjS = false;
      bool ydbzLUPmuK = false;
      bool UJjBqARGwN = false;
      bool WTGgyuiNUh = false;
      bool RIAcHNEutK = false;
      bool jKzseedwiJ = false;
      bool VfTWueXtAQ = false;
      bool kBSNrLJGsc = false;
      bool wVLkcMTNBS = false;
      bool QldKLlncgc = false;
      bool pJucYhrlBT = false;
      bool VWDFNATiti = false;
      string dPnBYZeQyr;
      string qpeOErghDU;
      string wZGiVcsSoP;
      string AzbHstopGw;
      string UJsjjlNuzd;
      string UQkrJDIFfu;
      string gLbiqqOXUK;
      string CpbGzlfVyi;
      string PyTLtjNixp;
      string kjKKPJhKss;
      string XoanaeoerW;
      string XmGwehrPnH;
      string ceZeZSfQpp;
      string EVcFLZWfjP;
      string tipaRxcNfg;
      string QRVkQrPuNI;
      string zYoBSCJBkE;
      string LMfYNtnzNb;
      string oRjIZlzqnS;
      string KbRaPUsoHP;
      if(dPnBYZeQyr == XoanaeoerW){nbcaVEkwXW = true;}
      else if(XoanaeoerW == dPnBYZeQyr){UJjBqARGwN = true;}
      if(qpeOErghDU == XmGwehrPnH){DQhkTgngbf = true;}
      else if(XmGwehrPnH == qpeOErghDU){WTGgyuiNUh = true;}
      if(wZGiVcsSoP == ceZeZSfQpp){CRMRtitEIr = true;}
      else if(ceZeZSfQpp == wZGiVcsSoP){RIAcHNEutK = true;}
      if(AzbHstopGw == EVcFLZWfjP){AzqxnMoIlV = true;}
      else if(EVcFLZWfjP == AzbHstopGw){jKzseedwiJ = true;}
      if(UJsjjlNuzd == tipaRxcNfg){BCTROttgHi = true;}
      else if(tipaRxcNfg == UJsjjlNuzd){VfTWueXtAQ = true;}
      if(UQkrJDIFfu == QRVkQrPuNI){gMMaMVOKgm = true;}
      else if(QRVkQrPuNI == UQkrJDIFfu){kBSNrLJGsc = true;}
      if(gLbiqqOXUK == zYoBSCJBkE){JfmfVEYjwG = true;}
      else if(zYoBSCJBkE == gLbiqqOXUK){wVLkcMTNBS = true;}
      if(CpbGzlfVyi == LMfYNtnzNb){rftGezyuDA = true;}
      if(PyTLtjNixp == oRjIZlzqnS){oNxZKnlPjS = true;}
      if(kjKKPJhKss == KbRaPUsoHP){ydbzLUPmuK = true;}
      while(LMfYNtnzNb == CpbGzlfVyi){QldKLlncgc = true;}
      while(oRjIZlzqnS == oRjIZlzqnS){pJucYhrlBT = true;}
      while(KbRaPUsoHP == KbRaPUsoHP){VWDFNATiti = true;}
      if(nbcaVEkwXW == true){nbcaVEkwXW = false;}
      if(DQhkTgngbf == true){DQhkTgngbf = false;}
      if(CRMRtitEIr == true){CRMRtitEIr = false;}
      if(AzqxnMoIlV == true){AzqxnMoIlV = false;}
      if(BCTROttgHi == true){BCTROttgHi = false;}
      if(gMMaMVOKgm == true){gMMaMVOKgm = false;}
      if(JfmfVEYjwG == true){JfmfVEYjwG = false;}
      if(rftGezyuDA == true){rftGezyuDA = false;}
      if(oNxZKnlPjS == true){oNxZKnlPjS = false;}
      if(ydbzLUPmuK == true){ydbzLUPmuK = false;}
      if(UJjBqARGwN == true){UJjBqARGwN = false;}
      if(WTGgyuiNUh == true){WTGgyuiNUh = false;}
      if(RIAcHNEutK == true){RIAcHNEutK = false;}
      if(jKzseedwiJ == true){jKzseedwiJ = false;}
      if(VfTWueXtAQ == true){VfTWueXtAQ = false;}
      if(kBSNrLJGsc == true){kBSNrLJGsc = false;}
      if(wVLkcMTNBS == true){wVLkcMTNBS = false;}
      if(QldKLlncgc == true){QldKLlncgc = false;}
      if(pJucYhrlBT == true){pJucYhrlBT = false;}
      if(VWDFNATiti == true){VWDFNATiti = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLEZXOTPQW
{ 
  void raPlhBfWIl()
  { 
      bool cnGcLcNijW = false;
      bool pxeLFrzDRF = false;
      bool haIOadasQn = false;
      bool CywzliIZiT = false;
      bool yHHbzjaSpL = false;
      bool TPFKICfqBg = false;
      bool BUSwUrAeZV = false;
      bool iZTxHZTfPq = false;
      bool CICETlrlqj = false;
      bool DRXBRdnKHG = false;
      bool jwsTbsuHCh = false;
      bool izbKesROci = false;
      bool zNnoSRCSec = false;
      bool kIYIGGOhbZ = false;
      bool pjjIBDoMWY = false;
      bool LZhYHVHDBK = false;
      bool qccZxZaSEX = false;
      bool dimCrOdfnO = false;
      bool bowGQLazBj = false;
      bool zKgRiMHJKa = false;
      string McSsOfCVKX;
      string cmngVljPPg;
      string iGStUOStjb;
      string glBcqJVpmT;
      string ECVMVCQQAN;
      string dTiWNFJYYz;
      string MHkhqpkKpM;
      string QscucfkGXS;
      string yBtWyNDePk;
      string AwRmGwRnVf;
      string RFamxjqmtg;
      string UDAFBLMOid;
      string mFuFLTboof;
      string OwjrBraGYN;
      string VQkhPwwLlu;
      string iCErsLKUbc;
      string ICxNRYSHEI;
      string jGoVHVUMpP;
      string XPCtwLqrzo;
      string hGewETTWPp;
      if(McSsOfCVKX == RFamxjqmtg){cnGcLcNijW = true;}
      else if(RFamxjqmtg == McSsOfCVKX){jwsTbsuHCh = true;}
      if(cmngVljPPg == UDAFBLMOid){pxeLFrzDRF = true;}
      else if(UDAFBLMOid == cmngVljPPg){izbKesROci = true;}
      if(iGStUOStjb == mFuFLTboof){haIOadasQn = true;}
      else if(mFuFLTboof == iGStUOStjb){zNnoSRCSec = true;}
      if(glBcqJVpmT == OwjrBraGYN){CywzliIZiT = true;}
      else if(OwjrBraGYN == glBcqJVpmT){kIYIGGOhbZ = true;}
      if(ECVMVCQQAN == VQkhPwwLlu){yHHbzjaSpL = true;}
      else if(VQkhPwwLlu == ECVMVCQQAN){pjjIBDoMWY = true;}
      if(dTiWNFJYYz == iCErsLKUbc){TPFKICfqBg = true;}
      else if(iCErsLKUbc == dTiWNFJYYz){LZhYHVHDBK = true;}
      if(MHkhqpkKpM == ICxNRYSHEI){BUSwUrAeZV = true;}
      else if(ICxNRYSHEI == MHkhqpkKpM){qccZxZaSEX = true;}
      if(QscucfkGXS == jGoVHVUMpP){iZTxHZTfPq = true;}
      if(yBtWyNDePk == XPCtwLqrzo){CICETlrlqj = true;}
      if(AwRmGwRnVf == hGewETTWPp){DRXBRdnKHG = true;}
      while(jGoVHVUMpP == QscucfkGXS){dimCrOdfnO = true;}
      while(XPCtwLqrzo == XPCtwLqrzo){bowGQLazBj = true;}
      while(hGewETTWPp == hGewETTWPp){zKgRiMHJKa = true;}
      if(cnGcLcNijW == true){cnGcLcNijW = false;}
      if(pxeLFrzDRF == true){pxeLFrzDRF = false;}
      if(haIOadasQn == true){haIOadasQn = false;}
      if(CywzliIZiT == true){CywzliIZiT = false;}
      if(yHHbzjaSpL == true){yHHbzjaSpL = false;}
      if(TPFKICfqBg == true){TPFKICfqBg = false;}
      if(BUSwUrAeZV == true){BUSwUrAeZV = false;}
      if(iZTxHZTfPq == true){iZTxHZTfPq = false;}
      if(CICETlrlqj == true){CICETlrlqj = false;}
      if(DRXBRdnKHG == true){DRXBRdnKHG = false;}
      if(jwsTbsuHCh == true){jwsTbsuHCh = false;}
      if(izbKesROci == true){izbKesROci = false;}
      if(zNnoSRCSec == true){zNnoSRCSec = false;}
      if(kIYIGGOhbZ == true){kIYIGGOhbZ = false;}
      if(pjjIBDoMWY == true){pjjIBDoMWY = false;}
      if(LZhYHVHDBK == true){LZhYHVHDBK = false;}
      if(qccZxZaSEX == true){qccZxZaSEX = false;}
      if(dimCrOdfnO == true){dimCrOdfnO = false;}
      if(bowGQLazBj == true){bowGQLazBj = false;}
      if(zKgRiMHJKa == true){zKgRiMHJKa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZRALSNJUL
{ 
  void DwrluNJxQY()
  { 
      bool iSCCiwFBkM = false;
      bool ArcJEUTTSp = false;
      bool LdnnhiiyRJ = false;
      bool eNtnDXjILj = false;
      bool TmsHZomhyk = false;
      bool IDqAqEeNUA = false;
      bool MGjbhlxnGg = false;
      bool jKHhWYkgOr = false;
      bool wAAfBaWtxy = false;
      bool sVmKWMCRYn = false;
      bool rybQBxwIcR = false;
      bool TxzbELFDaH = false;
      bool PCpHmOXwLJ = false;
      bool VSHaAyYieD = false;
      bool eNQfeuWLGK = false;
      bool GzqRXoHUdm = false;
      bool ZzxTuApXbF = false;
      bool mWYWbBlKbq = false;
      bool qLoACWboCL = false;
      bool pEFrdeQxje = false;
      string jRiXJQxjeD;
      string kzlYNkeexB;
      string PunFGzfVST;
      string wSEqIfxwFB;
      string NZVWUBRfHD;
      string tgnqmoccRK;
      string jbQKGRuuPg;
      string miYunpZRkE;
      string hANPYOdMDT;
      string DTduRkIKPC;
      string GVPZPLIrCx;
      string PLrMbiOBkr;
      string mhrudTEddD;
      string gOCiyLjmzN;
      string GlJGErbRSh;
      string WHZWOXdUuw;
      string HdOzPBJIOQ;
      string yaBXlBXkql;
      string qmKufZoeTZ;
      string hPqCFbWKpC;
      if(jRiXJQxjeD == GVPZPLIrCx){iSCCiwFBkM = true;}
      else if(GVPZPLIrCx == jRiXJQxjeD){rybQBxwIcR = true;}
      if(kzlYNkeexB == PLrMbiOBkr){ArcJEUTTSp = true;}
      else if(PLrMbiOBkr == kzlYNkeexB){TxzbELFDaH = true;}
      if(PunFGzfVST == mhrudTEddD){LdnnhiiyRJ = true;}
      else if(mhrudTEddD == PunFGzfVST){PCpHmOXwLJ = true;}
      if(wSEqIfxwFB == gOCiyLjmzN){eNtnDXjILj = true;}
      else if(gOCiyLjmzN == wSEqIfxwFB){VSHaAyYieD = true;}
      if(NZVWUBRfHD == GlJGErbRSh){TmsHZomhyk = true;}
      else if(GlJGErbRSh == NZVWUBRfHD){eNQfeuWLGK = true;}
      if(tgnqmoccRK == WHZWOXdUuw){IDqAqEeNUA = true;}
      else if(WHZWOXdUuw == tgnqmoccRK){GzqRXoHUdm = true;}
      if(jbQKGRuuPg == HdOzPBJIOQ){MGjbhlxnGg = true;}
      else if(HdOzPBJIOQ == jbQKGRuuPg){ZzxTuApXbF = true;}
      if(miYunpZRkE == yaBXlBXkql){jKHhWYkgOr = true;}
      if(hANPYOdMDT == qmKufZoeTZ){wAAfBaWtxy = true;}
      if(DTduRkIKPC == hPqCFbWKpC){sVmKWMCRYn = true;}
      while(yaBXlBXkql == miYunpZRkE){mWYWbBlKbq = true;}
      while(qmKufZoeTZ == qmKufZoeTZ){qLoACWboCL = true;}
      while(hPqCFbWKpC == hPqCFbWKpC){pEFrdeQxje = true;}
      if(iSCCiwFBkM == true){iSCCiwFBkM = false;}
      if(ArcJEUTTSp == true){ArcJEUTTSp = false;}
      if(LdnnhiiyRJ == true){LdnnhiiyRJ = false;}
      if(eNtnDXjILj == true){eNtnDXjILj = false;}
      if(TmsHZomhyk == true){TmsHZomhyk = false;}
      if(IDqAqEeNUA == true){IDqAqEeNUA = false;}
      if(MGjbhlxnGg == true){MGjbhlxnGg = false;}
      if(jKHhWYkgOr == true){jKHhWYkgOr = false;}
      if(wAAfBaWtxy == true){wAAfBaWtxy = false;}
      if(sVmKWMCRYn == true){sVmKWMCRYn = false;}
      if(rybQBxwIcR == true){rybQBxwIcR = false;}
      if(TxzbELFDaH == true){TxzbELFDaH = false;}
      if(PCpHmOXwLJ == true){PCpHmOXwLJ = false;}
      if(VSHaAyYieD == true){VSHaAyYieD = false;}
      if(eNQfeuWLGK == true){eNQfeuWLGK = false;}
      if(GzqRXoHUdm == true){GzqRXoHUdm = false;}
      if(ZzxTuApXbF == true){ZzxTuApXbF = false;}
      if(mWYWbBlKbq == true){mWYWbBlKbq = false;}
      if(qLoACWboCL == true){qLoACWboCL = false;}
      if(pEFrdeQxje == true){pEFrdeQxje = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKXWTBLTMF
{ 
  void brALxDlzXW()
  { 
      bool BmbBoFFOsI = false;
      bool ubAwUorkBj = false;
      bool tIWztciJdc = false;
      bool meKiSJemqk = false;
      bool eSErjrpDti = false;
      bool cDuMtrPcHL = false;
      bool WukPVPQQdL = false;
      bool JEtPEaDeOB = false;
      bool lfOuAjixoZ = false;
      bool tCfeOjgoWT = false;
      bool aZYiYYJeIS = false;
      bool ojNFZqfpOl = false;
      bool gTbEQHXOBT = false;
      bool sOHuZMGeVb = false;
      bool ZEnVjJnZFX = false;
      bool DqZkmHyUSQ = false;
      bool AudnZacSeN = false;
      bool jBTmLbeFTG = false;
      bool TxIdQCnWHS = false;
      bool NlMFaeaAwJ = false;
      string fwBqehlbmG;
      string IsMhPbNFpM;
      string AUQeRxUfNn;
      string QIJlCiuMQG;
      string szjhVYjrXG;
      string KbrskLeVYg;
      string MGNypziaff;
      string gBojSAjhJr;
      string NcHGcoPQBq;
      string EYmismkkrV;
      string pJMrZJmIZj;
      string awMgSjyGUA;
      string jSYnbINFpf;
      string PypmCEPPgT;
      string CHpRQHLGPJ;
      string neQqlWjYPR;
      string wgRsUbGYdO;
      string UhZBycbHXT;
      string wGogqjhyBe;
      string UqzPXUoxxn;
      if(fwBqehlbmG == pJMrZJmIZj){BmbBoFFOsI = true;}
      else if(pJMrZJmIZj == fwBqehlbmG){aZYiYYJeIS = true;}
      if(IsMhPbNFpM == awMgSjyGUA){ubAwUorkBj = true;}
      else if(awMgSjyGUA == IsMhPbNFpM){ojNFZqfpOl = true;}
      if(AUQeRxUfNn == jSYnbINFpf){tIWztciJdc = true;}
      else if(jSYnbINFpf == AUQeRxUfNn){gTbEQHXOBT = true;}
      if(QIJlCiuMQG == PypmCEPPgT){meKiSJemqk = true;}
      else if(PypmCEPPgT == QIJlCiuMQG){sOHuZMGeVb = true;}
      if(szjhVYjrXG == CHpRQHLGPJ){eSErjrpDti = true;}
      else if(CHpRQHLGPJ == szjhVYjrXG){ZEnVjJnZFX = true;}
      if(KbrskLeVYg == neQqlWjYPR){cDuMtrPcHL = true;}
      else if(neQqlWjYPR == KbrskLeVYg){DqZkmHyUSQ = true;}
      if(MGNypziaff == wgRsUbGYdO){WukPVPQQdL = true;}
      else if(wgRsUbGYdO == MGNypziaff){AudnZacSeN = true;}
      if(gBojSAjhJr == UhZBycbHXT){JEtPEaDeOB = true;}
      if(NcHGcoPQBq == wGogqjhyBe){lfOuAjixoZ = true;}
      if(EYmismkkrV == UqzPXUoxxn){tCfeOjgoWT = true;}
      while(UhZBycbHXT == gBojSAjhJr){jBTmLbeFTG = true;}
      while(wGogqjhyBe == wGogqjhyBe){TxIdQCnWHS = true;}
      while(UqzPXUoxxn == UqzPXUoxxn){NlMFaeaAwJ = true;}
      if(BmbBoFFOsI == true){BmbBoFFOsI = false;}
      if(ubAwUorkBj == true){ubAwUorkBj = false;}
      if(tIWztciJdc == true){tIWztciJdc = false;}
      if(meKiSJemqk == true){meKiSJemqk = false;}
      if(eSErjrpDti == true){eSErjrpDti = false;}
      if(cDuMtrPcHL == true){cDuMtrPcHL = false;}
      if(WukPVPQQdL == true){WukPVPQQdL = false;}
      if(JEtPEaDeOB == true){JEtPEaDeOB = false;}
      if(lfOuAjixoZ == true){lfOuAjixoZ = false;}
      if(tCfeOjgoWT == true){tCfeOjgoWT = false;}
      if(aZYiYYJeIS == true){aZYiYYJeIS = false;}
      if(ojNFZqfpOl == true){ojNFZqfpOl = false;}
      if(gTbEQHXOBT == true){gTbEQHXOBT = false;}
      if(sOHuZMGeVb == true){sOHuZMGeVb = false;}
      if(ZEnVjJnZFX == true){ZEnVjJnZFX = false;}
      if(DqZkmHyUSQ == true){DqZkmHyUSQ = false;}
      if(AudnZacSeN == true){AudnZacSeN = false;}
      if(jBTmLbeFTG == true){jBTmLbeFTG = false;}
      if(TxIdQCnWHS == true){TxIdQCnWHS = false;}
      if(NlMFaeaAwJ == true){NlMFaeaAwJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZWRLKVNSG
{ 
  void qagKxnLTLB()
  { 
      bool yEVONbANtA = false;
      bool DosLGuYnse = false;
      bool eozbwUIxHG = false;
      bool FiJfdoJFnk = false;
      bool XgcbhIZQnH = false;
      bool GTRPaJFsRr = false;
      bool TCGmtUeNhQ = false;
      bool kSzHHyMWtn = false;
      bool uqJzAlQsFU = false;
      bool jQnwRUaohN = false;
      bool cMiWVmTJIc = false;
      bool xiycxbsGmH = false;
      bool DkHMgUeDpl = false;
      bool XWngLhImcM = false;
      bool SGkcXBRKzo = false;
      bool bTBZJqFVpA = false;
      bool IPTVFZtRRO = false;
      bool SFcaowzdoe = false;
      bool DUEAKDVNWT = false;
      bool bmwcDCmPXy = false;
      string eJTmbXbdGt;
      string jZMqAzGiZx;
      string oDxnDGkgTz;
      string mhRoBmcNOd;
      string IpUAZOTnox;
      string gqpUUbMejV;
      string ltJHHCHXpN;
      string WrUwnyhwNn;
      string lxrVSuqxUY;
      string ZxdrrOgNrX;
      string GwxbanWtfV;
      string sPRujoBmoL;
      string KKDRmZNcEZ;
      string RTEphpzQud;
      string YxQyeKfiIC;
      string MsYgNwsfnA;
      string ZspGDZLaNs;
      string okrKlNsElc;
      string teUBNYuWbk;
      string xTbtDfHKtF;
      if(eJTmbXbdGt == GwxbanWtfV){yEVONbANtA = true;}
      else if(GwxbanWtfV == eJTmbXbdGt){cMiWVmTJIc = true;}
      if(jZMqAzGiZx == sPRujoBmoL){DosLGuYnse = true;}
      else if(sPRujoBmoL == jZMqAzGiZx){xiycxbsGmH = true;}
      if(oDxnDGkgTz == KKDRmZNcEZ){eozbwUIxHG = true;}
      else if(KKDRmZNcEZ == oDxnDGkgTz){DkHMgUeDpl = true;}
      if(mhRoBmcNOd == RTEphpzQud){FiJfdoJFnk = true;}
      else if(RTEphpzQud == mhRoBmcNOd){XWngLhImcM = true;}
      if(IpUAZOTnox == YxQyeKfiIC){XgcbhIZQnH = true;}
      else if(YxQyeKfiIC == IpUAZOTnox){SGkcXBRKzo = true;}
      if(gqpUUbMejV == MsYgNwsfnA){GTRPaJFsRr = true;}
      else if(MsYgNwsfnA == gqpUUbMejV){bTBZJqFVpA = true;}
      if(ltJHHCHXpN == ZspGDZLaNs){TCGmtUeNhQ = true;}
      else if(ZspGDZLaNs == ltJHHCHXpN){IPTVFZtRRO = true;}
      if(WrUwnyhwNn == okrKlNsElc){kSzHHyMWtn = true;}
      if(lxrVSuqxUY == teUBNYuWbk){uqJzAlQsFU = true;}
      if(ZxdrrOgNrX == xTbtDfHKtF){jQnwRUaohN = true;}
      while(okrKlNsElc == WrUwnyhwNn){SFcaowzdoe = true;}
      while(teUBNYuWbk == teUBNYuWbk){DUEAKDVNWT = true;}
      while(xTbtDfHKtF == xTbtDfHKtF){bmwcDCmPXy = true;}
      if(yEVONbANtA == true){yEVONbANtA = false;}
      if(DosLGuYnse == true){DosLGuYnse = false;}
      if(eozbwUIxHG == true){eozbwUIxHG = false;}
      if(FiJfdoJFnk == true){FiJfdoJFnk = false;}
      if(XgcbhIZQnH == true){XgcbhIZQnH = false;}
      if(GTRPaJFsRr == true){GTRPaJFsRr = false;}
      if(TCGmtUeNhQ == true){TCGmtUeNhQ = false;}
      if(kSzHHyMWtn == true){kSzHHyMWtn = false;}
      if(uqJzAlQsFU == true){uqJzAlQsFU = false;}
      if(jQnwRUaohN == true){jQnwRUaohN = false;}
      if(cMiWVmTJIc == true){cMiWVmTJIc = false;}
      if(xiycxbsGmH == true){xiycxbsGmH = false;}
      if(DkHMgUeDpl == true){DkHMgUeDpl = false;}
      if(XWngLhImcM == true){XWngLhImcM = false;}
      if(SGkcXBRKzo == true){SGkcXBRKzo = false;}
      if(bTBZJqFVpA == true){bTBZJqFVpA = false;}
      if(IPTVFZtRRO == true){IPTVFZtRRO = false;}
      if(SFcaowzdoe == true){SFcaowzdoe = false;}
      if(DUEAKDVNWT == true){DUEAKDVNWT = false;}
      if(bmwcDCmPXy == true){bmwcDCmPXy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSPFHPVUUV
{ 
  void oBpfJXAZlu()
  { 
      bool sfwHAVFumN = false;
      bool jnrHHmZgoB = false;
      bool oVdJWffILi = false;
      bool EBIncGHJid = false;
      bool YmmYqRQETP = false;
      bool bEExeXBmjT = false;
      bool pxiDJheEeB = false;
      bool fPyLcChERE = false;
      bool PbnwHzxKIF = false;
      bool ETYPnbDjPJ = false;
      bool mLYSiLGsUb = false;
      bool oxVfENImuJ = false;
      bool kTuYxLphWA = false;
      bool yxoIRDCUMu = false;
      bool sDpfPGysKZ = false;
      bool SQnFYSQAVW = false;
      bool UXVTcqHNOA = false;
      bool LnZAQgcOJp = false;
      bool NxWwhhJijy = false;
      bool mCyoaUhWDX = false;
      string sOXSJcoKwK;
      string sUVsciDwPX;
      string MPSbDsSWIN;
      string tDAzkfypfz;
      string NxCRnhGInM;
      string pIHMRcuuPQ;
      string JRBhPoTVHx;
      string kMQPJPMAnV;
      string lKhwXlumhH;
      string jCaOpwuUCy;
      string NjAqacrrDB;
      string PtGseziFJd;
      string tgnzMhkBZN;
      string UrypIBJqUt;
      string sDjfqpwgjp;
      string NpKXDguAes;
      string qqRogXwPkc;
      string orjOkpwHHW;
      string lDQjzehZlb;
      string FJLbDBltzT;
      if(sOXSJcoKwK == NjAqacrrDB){sfwHAVFumN = true;}
      else if(NjAqacrrDB == sOXSJcoKwK){mLYSiLGsUb = true;}
      if(sUVsciDwPX == PtGseziFJd){jnrHHmZgoB = true;}
      else if(PtGseziFJd == sUVsciDwPX){oxVfENImuJ = true;}
      if(MPSbDsSWIN == tgnzMhkBZN){oVdJWffILi = true;}
      else if(tgnzMhkBZN == MPSbDsSWIN){kTuYxLphWA = true;}
      if(tDAzkfypfz == UrypIBJqUt){EBIncGHJid = true;}
      else if(UrypIBJqUt == tDAzkfypfz){yxoIRDCUMu = true;}
      if(NxCRnhGInM == sDjfqpwgjp){YmmYqRQETP = true;}
      else if(sDjfqpwgjp == NxCRnhGInM){sDpfPGysKZ = true;}
      if(pIHMRcuuPQ == NpKXDguAes){bEExeXBmjT = true;}
      else if(NpKXDguAes == pIHMRcuuPQ){SQnFYSQAVW = true;}
      if(JRBhPoTVHx == qqRogXwPkc){pxiDJheEeB = true;}
      else if(qqRogXwPkc == JRBhPoTVHx){UXVTcqHNOA = true;}
      if(kMQPJPMAnV == orjOkpwHHW){fPyLcChERE = true;}
      if(lKhwXlumhH == lDQjzehZlb){PbnwHzxKIF = true;}
      if(jCaOpwuUCy == FJLbDBltzT){ETYPnbDjPJ = true;}
      while(orjOkpwHHW == kMQPJPMAnV){LnZAQgcOJp = true;}
      while(lDQjzehZlb == lDQjzehZlb){NxWwhhJijy = true;}
      while(FJLbDBltzT == FJLbDBltzT){mCyoaUhWDX = true;}
      if(sfwHAVFumN == true){sfwHAVFumN = false;}
      if(jnrHHmZgoB == true){jnrHHmZgoB = false;}
      if(oVdJWffILi == true){oVdJWffILi = false;}
      if(EBIncGHJid == true){EBIncGHJid = false;}
      if(YmmYqRQETP == true){YmmYqRQETP = false;}
      if(bEExeXBmjT == true){bEExeXBmjT = false;}
      if(pxiDJheEeB == true){pxiDJheEeB = false;}
      if(fPyLcChERE == true){fPyLcChERE = false;}
      if(PbnwHzxKIF == true){PbnwHzxKIF = false;}
      if(ETYPnbDjPJ == true){ETYPnbDjPJ = false;}
      if(mLYSiLGsUb == true){mLYSiLGsUb = false;}
      if(oxVfENImuJ == true){oxVfENImuJ = false;}
      if(kTuYxLphWA == true){kTuYxLphWA = false;}
      if(yxoIRDCUMu == true){yxoIRDCUMu = false;}
      if(sDpfPGysKZ == true){sDpfPGysKZ = false;}
      if(SQnFYSQAVW == true){SQnFYSQAVW = false;}
      if(UXVTcqHNOA == true){UXVTcqHNOA = false;}
      if(LnZAQgcOJp == true){LnZAQgcOJp = false;}
      if(NxWwhhJijy == true){NxWwhhJijy = false;}
      if(mCyoaUhWDX == true){mCyoaUhWDX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQHNVDPTEU
{ 
  void xHiVEJrjHO()
  { 
      bool dabfHhNZLV = false;
      bool wwJEgIEKVQ = false;
      bool KdfFohpHnt = false;
      bool GwnOejwlyb = false;
      bool XzXGdTxNRK = false;
      bool wufBPAuWqY = false;
      bool rGkQPAItYx = false;
      bool MSMtsLFYaV = false;
      bool jbpdxKPmze = false;
      bool nZuYiRNGqd = false;
      bool KDnTydilID = false;
      bool tVuVoPPHTE = false;
      bool jVutIlWmKa = false;
      bool xzhxKgnVfT = false;
      bool bdeujSeZjT = false;
      bool BGmltoHsLL = false;
      bool GubgFtnyKI = false;
      bool btbzcFqAJp = false;
      bool GxDqYqMwCV = false;
      bool YuJTMfCxop = false;
      string GqKhHyZAtP;
      string TTNsOzIyfe;
      string SPTOciByVU;
      string sxWIrTzQin;
      string DwQzmbjyHo;
      string FqJHepXuFX;
      string xbeYWVxFAu;
      string ArPrbWzTbB;
      string yCpgPBmOcB;
      string uELKqbRqcQ;
      string dexMoNbRfH;
      string qETDYtlxJU;
      string hhbzzwfEBz;
      string FHqKWTFdqB;
      string YViUKqjHlw;
      string pThHhwDyMs;
      string gXPfCjNIfF;
      string oHFIwMzGoI;
      string LYSFJkYica;
      string QHRyTBGCSZ;
      if(GqKhHyZAtP == dexMoNbRfH){dabfHhNZLV = true;}
      else if(dexMoNbRfH == GqKhHyZAtP){KDnTydilID = true;}
      if(TTNsOzIyfe == qETDYtlxJU){wwJEgIEKVQ = true;}
      else if(qETDYtlxJU == TTNsOzIyfe){tVuVoPPHTE = true;}
      if(SPTOciByVU == hhbzzwfEBz){KdfFohpHnt = true;}
      else if(hhbzzwfEBz == SPTOciByVU){jVutIlWmKa = true;}
      if(sxWIrTzQin == FHqKWTFdqB){GwnOejwlyb = true;}
      else if(FHqKWTFdqB == sxWIrTzQin){xzhxKgnVfT = true;}
      if(DwQzmbjyHo == YViUKqjHlw){XzXGdTxNRK = true;}
      else if(YViUKqjHlw == DwQzmbjyHo){bdeujSeZjT = true;}
      if(FqJHepXuFX == pThHhwDyMs){wufBPAuWqY = true;}
      else if(pThHhwDyMs == FqJHepXuFX){BGmltoHsLL = true;}
      if(xbeYWVxFAu == gXPfCjNIfF){rGkQPAItYx = true;}
      else if(gXPfCjNIfF == xbeYWVxFAu){GubgFtnyKI = true;}
      if(ArPrbWzTbB == oHFIwMzGoI){MSMtsLFYaV = true;}
      if(yCpgPBmOcB == LYSFJkYica){jbpdxKPmze = true;}
      if(uELKqbRqcQ == QHRyTBGCSZ){nZuYiRNGqd = true;}
      while(oHFIwMzGoI == ArPrbWzTbB){btbzcFqAJp = true;}
      while(LYSFJkYica == LYSFJkYica){GxDqYqMwCV = true;}
      while(QHRyTBGCSZ == QHRyTBGCSZ){YuJTMfCxop = true;}
      if(dabfHhNZLV == true){dabfHhNZLV = false;}
      if(wwJEgIEKVQ == true){wwJEgIEKVQ = false;}
      if(KdfFohpHnt == true){KdfFohpHnt = false;}
      if(GwnOejwlyb == true){GwnOejwlyb = false;}
      if(XzXGdTxNRK == true){XzXGdTxNRK = false;}
      if(wufBPAuWqY == true){wufBPAuWqY = false;}
      if(rGkQPAItYx == true){rGkQPAItYx = false;}
      if(MSMtsLFYaV == true){MSMtsLFYaV = false;}
      if(jbpdxKPmze == true){jbpdxKPmze = false;}
      if(nZuYiRNGqd == true){nZuYiRNGqd = false;}
      if(KDnTydilID == true){KDnTydilID = false;}
      if(tVuVoPPHTE == true){tVuVoPPHTE = false;}
      if(jVutIlWmKa == true){jVutIlWmKa = false;}
      if(xzhxKgnVfT == true){xzhxKgnVfT = false;}
      if(bdeujSeZjT == true){bdeujSeZjT = false;}
      if(BGmltoHsLL == true){BGmltoHsLL = false;}
      if(GubgFtnyKI == true){GubgFtnyKI = false;}
      if(btbzcFqAJp == true){btbzcFqAJp = false;}
      if(GxDqYqMwCV == true){GxDqYqMwCV = false;}
      if(YuJTMfCxop == true){YuJTMfCxop = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTBVJJJGQV
{ 
  void swWllKbXJH()
  { 
      bool UbmjTuiiyX = false;
      bool LrnJcSNmAp = false;
      bool KmJgnytjHM = false;
      bool mNQMUEhIJG = false;
      bool yyWzsoToCa = false;
      bool knjBXgSFuV = false;
      bool BzbkkyabnX = false;
      bool jFdsqMPJny = false;
      bool dFgfbzcOnn = false;
      bool lcMnFzWkOu = false;
      bool NrBeqeKpKL = false;
      bool QIRxquRwJk = false;
      bool VMmAkHronq = false;
      bool oetsjlECow = false;
      bool nlEcWcKPwJ = false;
      bool haadYBFAti = false;
      bool mUCSVlOYMF = false;
      bool qPGNxiHJcH = false;
      bool wbsdJODQTh = false;
      bool fDIFITikHj = false;
      string MEWlmTXeTJ;
      string cUwEryFlzM;
      string fKLVaYUQkS;
      string eIAFqJEkaW;
      string nxVFOPPUAu;
      string CSwSmBsALO;
      string yHtAdTTqNi;
      string tTLbXinFHK;
      string IzPpQMMhSo;
      string PDZMYgCUau;
      string wYHRAhGTtD;
      string MmsAFyqEjR;
      string HlXXSqtzDq;
      string fTeLOiryoh;
      string GrmObcJYGZ;
      string oykJmJBjzJ;
      string nHQCXsIhlW;
      string GsPBLPyIuo;
      string gUscChhUXE;
      string hIyetzbkqi;
      if(MEWlmTXeTJ == wYHRAhGTtD){UbmjTuiiyX = true;}
      else if(wYHRAhGTtD == MEWlmTXeTJ){NrBeqeKpKL = true;}
      if(cUwEryFlzM == MmsAFyqEjR){LrnJcSNmAp = true;}
      else if(MmsAFyqEjR == cUwEryFlzM){QIRxquRwJk = true;}
      if(fKLVaYUQkS == HlXXSqtzDq){KmJgnytjHM = true;}
      else if(HlXXSqtzDq == fKLVaYUQkS){VMmAkHronq = true;}
      if(eIAFqJEkaW == fTeLOiryoh){mNQMUEhIJG = true;}
      else if(fTeLOiryoh == eIAFqJEkaW){oetsjlECow = true;}
      if(nxVFOPPUAu == GrmObcJYGZ){yyWzsoToCa = true;}
      else if(GrmObcJYGZ == nxVFOPPUAu){nlEcWcKPwJ = true;}
      if(CSwSmBsALO == oykJmJBjzJ){knjBXgSFuV = true;}
      else if(oykJmJBjzJ == CSwSmBsALO){haadYBFAti = true;}
      if(yHtAdTTqNi == nHQCXsIhlW){BzbkkyabnX = true;}
      else if(nHQCXsIhlW == yHtAdTTqNi){mUCSVlOYMF = true;}
      if(tTLbXinFHK == GsPBLPyIuo){jFdsqMPJny = true;}
      if(IzPpQMMhSo == gUscChhUXE){dFgfbzcOnn = true;}
      if(PDZMYgCUau == hIyetzbkqi){lcMnFzWkOu = true;}
      while(GsPBLPyIuo == tTLbXinFHK){qPGNxiHJcH = true;}
      while(gUscChhUXE == gUscChhUXE){wbsdJODQTh = true;}
      while(hIyetzbkqi == hIyetzbkqi){fDIFITikHj = true;}
      if(UbmjTuiiyX == true){UbmjTuiiyX = false;}
      if(LrnJcSNmAp == true){LrnJcSNmAp = false;}
      if(KmJgnytjHM == true){KmJgnytjHM = false;}
      if(mNQMUEhIJG == true){mNQMUEhIJG = false;}
      if(yyWzsoToCa == true){yyWzsoToCa = false;}
      if(knjBXgSFuV == true){knjBXgSFuV = false;}
      if(BzbkkyabnX == true){BzbkkyabnX = false;}
      if(jFdsqMPJny == true){jFdsqMPJny = false;}
      if(dFgfbzcOnn == true){dFgfbzcOnn = false;}
      if(lcMnFzWkOu == true){lcMnFzWkOu = false;}
      if(NrBeqeKpKL == true){NrBeqeKpKL = false;}
      if(QIRxquRwJk == true){QIRxquRwJk = false;}
      if(VMmAkHronq == true){VMmAkHronq = false;}
      if(oetsjlECow == true){oetsjlECow = false;}
      if(nlEcWcKPwJ == true){nlEcWcKPwJ = false;}
      if(haadYBFAti == true){haadYBFAti = false;}
      if(mUCSVlOYMF == true){mUCSVlOYMF = false;}
      if(qPGNxiHJcH == true){qPGNxiHJcH = false;}
      if(wbsdJODQTh == true){wbsdJODQTh = false;}
      if(fDIFITikHj == true){fDIFITikHj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVGYFNYGOR
{ 
  void fHjWojjRei()
  { 
      bool hFmNLfNaiI = false;
      bool oLGowgoiXy = false;
      bool idbfJRFNZb = false;
      bool jVUITHwCaL = false;
      bool YkrozYYOsz = false;
      bool TMiPyDcGDs = false;
      bool aAAHYSpyVo = false;
      bool kmHMZylmgj = false;
      bool rpTaHWlFJQ = false;
      bool dpygjYjkQf = false;
      bool iasENgEWoA = false;
      bool QpYSBkfZzC = false;
      bool gjnEKtnZbB = false;
      bool NAWABRwOMa = false;
      bool RPQJznQefz = false;
      bool rKlNzzlosS = false;
      bool retnlPTYRi = false;
      bool nQMXjQTeEW = false;
      bool dItbIDOIAB = false;
      bool fGVshmVbWi = false;
      string thuWraeyBP;
      string ZUTYkcRZsM;
      string saTDSICstq;
      string anxxlEnoSK;
      string hWuGaqzFOr;
      string kjBbJTOrEi;
      string YkEKnlWVmf;
      string ocHheVeMcb;
      string IweBFplVmS;
      string pukilwSkRo;
      string TcShCIcSxn;
      string oBOcZbGCEy;
      string zBiUpsqXwh;
      string CsunHedwzx;
      string NSXzcngIIJ;
      string pQgToStyrJ;
      string QEWPkuGaUt;
      string yJDGjfdiqC;
      string MiPmqlLbyn;
      string kfEpfIwHNh;
      if(thuWraeyBP == TcShCIcSxn){hFmNLfNaiI = true;}
      else if(TcShCIcSxn == thuWraeyBP){iasENgEWoA = true;}
      if(ZUTYkcRZsM == oBOcZbGCEy){oLGowgoiXy = true;}
      else if(oBOcZbGCEy == ZUTYkcRZsM){QpYSBkfZzC = true;}
      if(saTDSICstq == zBiUpsqXwh){idbfJRFNZb = true;}
      else if(zBiUpsqXwh == saTDSICstq){gjnEKtnZbB = true;}
      if(anxxlEnoSK == CsunHedwzx){jVUITHwCaL = true;}
      else if(CsunHedwzx == anxxlEnoSK){NAWABRwOMa = true;}
      if(hWuGaqzFOr == NSXzcngIIJ){YkrozYYOsz = true;}
      else if(NSXzcngIIJ == hWuGaqzFOr){RPQJznQefz = true;}
      if(kjBbJTOrEi == pQgToStyrJ){TMiPyDcGDs = true;}
      else if(pQgToStyrJ == kjBbJTOrEi){rKlNzzlosS = true;}
      if(YkEKnlWVmf == QEWPkuGaUt){aAAHYSpyVo = true;}
      else if(QEWPkuGaUt == YkEKnlWVmf){retnlPTYRi = true;}
      if(ocHheVeMcb == yJDGjfdiqC){kmHMZylmgj = true;}
      if(IweBFplVmS == MiPmqlLbyn){rpTaHWlFJQ = true;}
      if(pukilwSkRo == kfEpfIwHNh){dpygjYjkQf = true;}
      while(yJDGjfdiqC == ocHheVeMcb){nQMXjQTeEW = true;}
      while(MiPmqlLbyn == MiPmqlLbyn){dItbIDOIAB = true;}
      while(kfEpfIwHNh == kfEpfIwHNh){fGVshmVbWi = true;}
      if(hFmNLfNaiI == true){hFmNLfNaiI = false;}
      if(oLGowgoiXy == true){oLGowgoiXy = false;}
      if(idbfJRFNZb == true){idbfJRFNZb = false;}
      if(jVUITHwCaL == true){jVUITHwCaL = false;}
      if(YkrozYYOsz == true){YkrozYYOsz = false;}
      if(TMiPyDcGDs == true){TMiPyDcGDs = false;}
      if(aAAHYSpyVo == true){aAAHYSpyVo = false;}
      if(kmHMZylmgj == true){kmHMZylmgj = false;}
      if(rpTaHWlFJQ == true){rpTaHWlFJQ = false;}
      if(dpygjYjkQf == true){dpygjYjkQf = false;}
      if(iasENgEWoA == true){iasENgEWoA = false;}
      if(QpYSBkfZzC == true){QpYSBkfZzC = false;}
      if(gjnEKtnZbB == true){gjnEKtnZbB = false;}
      if(NAWABRwOMa == true){NAWABRwOMa = false;}
      if(RPQJznQefz == true){RPQJznQefz = false;}
      if(rKlNzzlosS == true){rKlNzzlosS = false;}
      if(retnlPTYRi == true){retnlPTYRi = false;}
      if(nQMXjQTeEW == true){nQMXjQTeEW = false;}
      if(dItbIDOIAB == true){dItbIDOIAB = false;}
      if(fGVshmVbWi == true){fGVshmVbWi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUJCQNAWGT
{ 
  void pzBUQSIcZN()
  { 
      bool czSNwymAFE = false;
      bool zdoYdAWrsk = false;
      bool xifHueSDCd = false;
      bool ChUHTCUfea = false;
      bool xSyNJAMCBo = false;
      bool ZEJidtTKRQ = false;
      bool fiybBRIhEb = false;
      bool eqMRnejRyt = false;
      bool SPCMDyYlcY = false;
      bool iKNNuNUWLr = false;
      bool rdyZJiqquy = false;
      bool KCMXyPgkYD = false;
      bool sWEesUcyWa = false;
      bool KMFFBnRcCT = false;
      bool GgqdOfxoPe = false;
      bool fiyIzVZSgo = false;
      bool GrUTnxwHWK = false;
      bool yEiEwLeZQM = false;
      bool XmiqtaOwGf = false;
      bool OyuNMOMWpQ = false;
      string RJekTGxjwC;
      string NOXWayOdLR;
      string lMcSowXWtd;
      string CGAYaWesjU;
      string MJiVaExwnA;
      string jqQrFFfMwX;
      string iapRzGOywE;
      string TVsqFbcHqj;
      string yahstKpITU;
      string pSwMllTQVU;
      string pzAjgOxZld;
      string cYULYHrwXo;
      string QGebNAYgFT;
      string ILkWtzaxMe;
      string NQVorQykmd;
      string sXsgEjTYVf;
      string oQTSVQmyRZ;
      string gtjrazjoix;
      string CnsbZjSESJ;
      string eCbfpxwCTb;
      if(RJekTGxjwC == pzAjgOxZld){czSNwymAFE = true;}
      else if(pzAjgOxZld == RJekTGxjwC){rdyZJiqquy = true;}
      if(NOXWayOdLR == cYULYHrwXo){zdoYdAWrsk = true;}
      else if(cYULYHrwXo == NOXWayOdLR){KCMXyPgkYD = true;}
      if(lMcSowXWtd == QGebNAYgFT){xifHueSDCd = true;}
      else if(QGebNAYgFT == lMcSowXWtd){sWEesUcyWa = true;}
      if(CGAYaWesjU == ILkWtzaxMe){ChUHTCUfea = true;}
      else if(ILkWtzaxMe == CGAYaWesjU){KMFFBnRcCT = true;}
      if(MJiVaExwnA == NQVorQykmd){xSyNJAMCBo = true;}
      else if(NQVorQykmd == MJiVaExwnA){GgqdOfxoPe = true;}
      if(jqQrFFfMwX == sXsgEjTYVf){ZEJidtTKRQ = true;}
      else if(sXsgEjTYVf == jqQrFFfMwX){fiyIzVZSgo = true;}
      if(iapRzGOywE == oQTSVQmyRZ){fiybBRIhEb = true;}
      else if(oQTSVQmyRZ == iapRzGOywE){GrUTnxwHWK = true;}
      if(TVsqFbcHqj == gtjrazjoix){eqMRnejRyt = true;}
      if(yahstKpITU == CnsbZjSESJ){SPCMDyYlcY = true;}
      if(pSwMllTQVU == eCbfpxwCTb){iKNNuNUWLr = true;}
      while(gtjrazjoix == TVsqFbcHqj){yEiEwLeZQM = true;}
      while(CnsbZjSESJ == CnsbZjSESJ){XmiqtaOwGf = true;}
      while(eCbfpxwCTb == eCbfpxwCTb){OyuNMOMWpQ = true;}
      if(czSNwymAFE == true){czSNwymAFE = false;}
      if(zdoYdAWrsk == true){zdoYdAWrsk = false;}
      if(xifHueSDCd == true){xifHueSDCd = false;}
      if(ChUHTCUfea == true){ChUHTCUfea = false;}
      if(xSyNJAMCBo == true){xSyNJAMCBo = false;}
      if(ZEJidtTKRQ == true){ZEJidtTKRQ = false;}
      if(fiybBRIhEb == true){fiybBRIhEb = false;}
      if(eqMRnejRyt == true){eqMRnejRyt = false;}
      if(SPCMDyYlcY == true){SPCMDyYlcY = false;}
      if(iKNNuNUWLr == true){iKNNuNUWLr = false;}
      if(rdyZJiqquy == true){rdyZJiqquy = false;}
      if(KCMXyPgkYD == true){KCMXyPgkYD = false;}
      if(sWEesUcyWa == true){sWEesUcyWa = false;}
      if(KMFFBnRcCT == true){KMFFBnRcCT = false;}
      if(GgqdOfxoPe == true){GgqdOfxoPe = false;}
      if(fiyIzVZSgo == true){fiyIzVZSgo = false;}
      if(GrUTnxwHWK == true){GrUTnxwHWK = false;}
      if(yEiEwLeZQM == true){yEiEwLeZQM = false;}
      if(XmiqtaOwGf == true){XmiqtaOwGf = false;}
      if(OyuNMOMWpQ == true){OyuNMOMWpQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLAUSDDSZB
{ 
  void yORUkCiCrC()
  { 
      bool YtBuXhZFQP = false;
      bool HPTlZHLsHI = false;
      bool TfBIIwqKWK = false;
      bool nKjzTMOhuA = false;
      bool glExVSjIsK = false;
      bool ChEOKsssma = false;
      bool pOiFbwfURN = false;
      bool sdyHahaDmo = false;
      bool MhQMHFGUna = false;
      bool SUtUJSDyVY = false;
      bool mPqfRYjxnc = false;
      bool SoGxOHyVyV = false;
      bool pKfqtXicxI = false;
      bool dbhNCwqkuh = false;
      bool VJgLIdOwGB = false;
      bool ThAzibiAls = false;
      bool oGzfzpHruR = false;
      bool QNaPAfcUhQ = false;
      bool ImWwnwbhda = false;
      bool NpzBsOJBMS = false;
      string EathYgONdF;
      string LpsXdpWKYG;
      string JnlHdBGbif;
      string QQXjIZFkID;
      string UOYHeUbiCi;
      string NGYdVQolDX;
      string alexnuRIOD;
      string klBUkuPdcJ;
      string ZWYzSKqtNr;
      string kTgkchjaTi;
      string CSTyybFDra;
      string AKJsyDNeed;
      string DXtVSQEPqD;
      string LnKsHGCaBp;
      string EnBmqZJnmY;
      string UEuofdXyeg;
      string XoMoPMAPlq;
      string BldoYPWHds;
      string HQcShHrUNc;
      string iEuTROaLWe;
      if(EathYgONdF == CSTyybFDra){YtBuXhZFQP = true;}
      else if(CSTyybFDra == EathYgONdF){mPqfRYjxnc = true;}
      if(LpsXdpWKYG == AKJsyDNeed){HPTlZHLsHI = true;}
      else if(AKJsyDNeed == LpsXdpWKYG){SoGxOHyVyV = true;}
      if(JnlHdBGbif == DXtVSQEPqD){TfBIIwqKWK = true;}
      else if(DXtVSQEPqD == JnlHdBGbif){pKfqtXicxI = true;}
      if(QQXjIZFkID == LnKsHGCaBp){nKjzTMOhuA = true;}
      else if(LnKsHGCaBp == QQXjIZFkID){dbhNCwqkuh = true;}
      if(UOYHeUbiCi == EnBmqZJnmY){glExVSjIsK = true;}
      else if(EnBmqZJnmY == UOYHeUbiCi){VJgLIdOwGB = true;}
      if(NGYdVQolDX == UEuofdXyeg){ChEOKsssma = true;}
      else if(UEuofdXyeg == NGYdVQolDX){ThAzibiAls = true;}
      if(alexnuRIOD == XoMoPMAPlq){pOiFbwfURN = true;}
      else if(XoMoPMAPlq == alexnuRIOD){oGzfzpHruR = true;}
      if(klBUkuPdcJ == BldoYPWHds){sdyHahaDmo = true;}
      if(ZWYzSKqtNr == HQcShHrUNc){MhQMHFGUna = true;}
      if(kTgkchjaTi == iEuTROaLWe){SUtUJSDyVY = true;}
      while(BldoYPWHds == klBUkuPdcJ){QNaPAfcUhQ = true;}
      while(HQcShHrUNc == HQcShHrUNc){ImWwnwbhda = true;}
      while(iEuTROaLWe == iEuTROaLWe){NpzBsOJBMS = true;}
      if(YtBuXhZFQP == true){YtBuXhZFQP = false;}
      if(HPTlZHLsHI == true){HPTlZHLsHI = false;}
      if(TfBIIwqKWK == true){TfBIIwqKWK = false;}
      if(nKjzTMOhuA == true){nKjzTMOhuA = false;}
      if(glExVSjIsK == true){glExVSjIsK = false;}
      if(ChEOKsssma == true){ChEOKsssma = false;}
      if(pOiFbwfURN == true){pOiFbwfURN = false;}
      if(sdyHahaDmo == true){sdyHahaDmo = false;}
      if(MhQMHFGUna == true){MhQMHFGUna = false;}
      if(SUtUJSDyVY == true){SUtUJSDyVY = false;}
      if(mPqfRYjxnc == true){mPqfRYjxnc = false;}
      if(SoGxOHyVyV == true){SoGxOHyVyV = false;}
      if(pKfqtXicxI == true){pKfqtXicxI = false;}
      if(dbhNCwqkuh == true){dbhNCwqkuh = false;}
      if(VJgLIdOwGB == true){VJgLIdOwGB = false;}
      if(ThAzibiAls == true){ThAzibiAls = false;}
      if(oGzfzpHruR == true){oGzfzpHruR = false;}
      if(QNaPAfcUhQ == true){QNaPAfcUhQ = false;}
      if(ImWwnwbhda == true){ImWwnwbhda = false;}
      if(NpzBsOJBMS == true){NpzBsOJBMS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHFUYZTGEY
{ 
  void COfAuzebQD()
  { 
      bool zbJxtxXRIo = false;
      bool zcDjMXEFbH = false;
      bool OyDkoGwdFY = false;
      bool ecGAlzCRyI = false;
      bool RSgRMgRywV = false;
      bool hSNfxBXXHm = false;
      bool BsLiKVVDxM = false;
      bool VmHSpuQkYI = false;
      bool oxhjqLPZCk = false;
      bool adJKHXGyGp = false;
      bool KOBiztLtoB = false;
      bool jmzyyDLbqz = false;
      bool GwALlqcwKS = false;
      bool nReiyZuyjx = false;
      bool zVkABneLME = false;
      bool MeHHiNNpxH = false;
      bool QPiWNRHPAX = false;
      bool HMrszkLzKx = false;
      bool MRjGFJKWzj = false;
      bool LFAbfjlNmi = false;
      string AfTqGltqsC;
      string DqoBritXTu;
      string XBkretAIJi;
      string AtIbNfYtlU;
      string ycEoarNaHL;
      string CPLQsztbML;
      string kkhJCIiMmL;
      string KAkyxuxwRl;
      string gYAyfjirhO;
      string lwgaiNutlR;
      string IAnwBCdMSx;
      string CyKaeMjjcR;
      string YqdYZNSKOj;
      string ACJzcfkEwd;
      string FVYkLmlGwW;
      string cLQTrRVPVm;
      string jTxixznKxy;
      string bemzLCSsMl;
      string aLOrGokoHL;
      string JUiIslXomM;
      if(AfTqGltqsC == IAnwBCdMSx){zbJxtxXRIo = true;}
      else if(IAnwBCdMSx == AfTqGltqsC){KOBiztLtoB = true;}
      if(DqoBritXTu == CyKaeMjjcR){zcDjMXEFbH = true;}
      else if(CyKaeMjjcR == DqoBritXTu){jmzyyDLbqz = true;}
      if(XBkretAIJi == YqdYZNSKOj){OyDkoGwdFY = true;}
      else if(YqdYZNSKOj == XBkretAIJi){GwALlqcwKS = true;}
      if(AtIbNfYtlU == ACJzcfkEwd){ecGAlzCRyI = true;}
      else if(ACJzcfkEwd == AtIbNfYtlU){nReiyZuyjx = true;}
      if(ycEoarNaHL == FVYkLmlGwW){RSgRMgRywV = true;}
      else if(FVYkLmlGwW == ycEoarNaHL){zVkABneLME = true;}
      if(CPLQsztbML == cLQTrRVPVm){hSNfxBXXHm = true;}
      else if(cLQTrRVPVm == CPLQsztbML){MeHHiNNpxH = true;}
      if(kkhJCIiMmL == jTxixznKxy){BsLiKVVDxM = true;}
      else if(jTxixznKxy == kkhJCIiMmL){QPiWNRHPAX = true;}
      if(KAkyxuxwRl == bemzLCSsMl){VmHSpuQkYI = true;}
      if(gYAyfjirhO == aLOrGokoHL){oxhjqLPZCk = true;}
      if(lwgaiNutlR == JUiIslXomM){adJKHXGyGp = true;}
      while(bemzLCSsMl == KAkyxuxwRl){HMrszkLzKx = true;}
      while(aLOrGokoHL == aLOrGokoHL){MRjGFJKWzj = true;}
      while(JUiIslXomM == JUiIslXomM){LFAbfjlNmi = true;}
      if(zbJxtxXRIo == true){zbJxtxXRIo = false;}
      if(zcDjMXEFbH == true){zcDjMXEFbH = false;}
      if(OyDkoGwdFY == true){OyDkoGwdFY = false;}
      if(ecGAlzCRyI == true){ecGAlzCRyI = false;}
      if(RSgRMgRywV == true){RSgRMgRywV = false;}
      if(hSNfxBXXHm == true){hSNfxBXXHm = false;}
      if(BsLiKVVDxM == true){BsLiKVVDxM = false;}
      if(VmHSpuQkYI == true){VmHSpuQkYI = false;}
      if(oxhjqLPZCk == true){oxhjqLPZCk = false;}
      if(adJKHXGyGp == true){adJKHXGyGp = false;}
      if(KOBiztLtoB == true){KOBiztLtoB = false;}
      if(jmzyyDLbqz == true){jmzyyDLbqz = false;}
      if(GwALlqcwKS == true){GwALlqcwKS = false;}
      if(nReiyZuyjx == true){nReiyZuyjx = false;}
      if(zVkABneLME == true){zVkABneLME = false;}
      if(MeHHiNNpxH == true){MeHHiNNpxH = false;}
      if(QPiWNRHPAX == true){QPiWNRHPAX = false;}
      if(HMrszkLzKx == true){HMrszkLzKx = false;}
      if(MRjGFJKWzj == true){MRjGFJKWzj = false;}
      if(LFAbfjlNmi == true){LFAbfjlNmi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQFVXOWXEK
{ 
  void VoAERYsYPc()
  { 
      bool dFcfVTZyWq = false;
      bool nwoTWcWzao = false;
      bool BUllRumWiy = false;
      bool jSVkDBcaQz = false;
      bool ptHsNNxKwb = false;
      bool iADhPITqNZ = false;
      bool fDPXHUZDQV = false;
      bool AwibzGNrXE = false;
      bool ycZHPiPnVt = false;
      bool glNpSleilr = false;
      bool mstabmRahJ = false;
      bool ubSJbDdIIX = false;
      bool FlhVnOisIM = false;
      bool adFfQEiyfc = false;
      bool RnGLyFSDNO = false;
      bool IVaOlBLXmM = false;
      bool EXSUhRVlrW = false;
      bool UeceFRfVWh = false;
      bool ueesEFCqsP = false;
      bool sKLSYsVkdg = false;
      string AzdWwnlWgC;
      string iFeKMtbYSI;
      string xdRnAJryUL;
      string dyJrJRAOXL;
      string VIiqfEyHGI;
      string SwjkbVgpWm;
      string wnCUXjulBu;
      string tNBGlotaHw;
      string LjqMsgOYQm;
      string jKqkPhGOTw;
      string ILGLNFuczm;
      string aGhabLwobq;
      string VWVOKiVQqE;
      string hfHLmzdeyn;
      string klYcLcbQIE;
      string kRmbaloqBd;
      string ieltFtzWmb;
      string hRqnFixsCg;
      string HFHlSQsekB;
      string JldTEGzeWQ;
      if(AzdWwnlWgC == ILGLNFuczm){dFcfVTZyWq = true;}
      else if(ILGLNFuczm == AzdWwnlWgC){mstabmRahJ = true;}
      if(iFeKMtbYSI == aGhabLwobq){nwoTWcWzao = true;}
      else if(aGhabLwobq == iFeKMtbYSI){ubSJbDdIIX = true;}
      if(xdRnAJryUL == VWVOKiVQqE){BUllRumWiy = true;}
      else if(VWVOKiVQqE == xdRnAJryUL){FlhVnOisIM = true;}
      if(dyJrJRAOXL == hfHLmzdeyn){jSVkDBcaQz = true;}
      else if(hfHLmzdeyn == dyJrJRAOXL){adFfQEiyfc = true;}
      if(VIiqfEyHGI == klYcLcbQIE){ptHsNNxKwb = true;}
      else if(klYcLcbQIE == VIiqfEyHGI){RnGLyFSDNO = true;}
      if(SwjkbVgpWm == kRmbaloqBd){iADhPITqNZ = true;}
      else if(kRmbaloqBd == SwjkbVgpWm){IVaOlBLXmM = true;}
      if(wnCUXjulBu == ieltFtzWmb){fDPXHUZDQV = true;}
      else if(ieltFtzWmb == wnCUXjulBu){EXSUhRVlrW = true;}
      if(tNBGlotaHw == hRqnFixsCg){AwibzGNrXE = true;}
      if(LjqMsgOYQm == HFHlSQsekB){ycZHPiPnVt = true;}
      if(jKqkPhGOTw == JldTEGzeWQ){glNpSleilr = true;}
      while(hRqnFixsCg == tNBGlotaHw){UeceFRfVWh = true;}
      while(HFHlSQsekB == HFHlSQsekB){ueesEFCqsP = true;}
      while(JldTEGzeWQ == JldTEGzeWQ){sKLSYsVkdg = true;}
      if(dFcfVTZyWq == true){dFcfVTZyWq = false;}
      if(nwoTWcWzao == true){nwoTWcWzao = false;}
      if(BUllRumWiy == true){BUllRumWiy = false;}
      if(jSVkDBcaQz == true){jSVkDBcaQz = false;}
      if(ptHsNNxKwb == true){ptHsNNxKwb = false;}
      if(iADhPITqNZ == true){iADhPITqNZ = false;}
      if(fDPXHUZDQV == true){fDPXHUZDQV = false;}
      if(AwibzGNrXE == true){AwibzGNrXE = false;}
      if(ycZHPiPnVt == true){ycZHPiPnVt = false;}
      if(glNpSleilr == true){glNpSleilr = false;}
      if(mstabmRahJ == true){mstabmRahJ = false;}
      if(ubSJbDdIIX == true){ubSJbDdIIX = false;}
      if(FlhVnOisIM == true){FlhVnOisIM = false;}
      if(adFfQEiyfc == true){adFfQEiyfc = false;}
      if(RnGLyFSDNO == true){RnGLyFSDNO = false;}
      if(IVaOlBLXmM == true){IVaOlBLXmM = false;}
      if(EXSUhRVlrW == true){EXSUhRVlrW = false;}
      if(UeceFRfVWh == true){UeceFRfVWh = false;}
      if(ueesEFCqsP == true){ueesEFCqsP = false;}
      if(sKLSYsVkdg == true){sKLSYsVkdg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDLZENVCRT
{ 
  void ZESecdCfOq()
  { 
      bool YJbpOROYhm = false;
      bool kCQckDZdze = false;
      bool slAOhuEjiX = false;
      bool InVWPNXBxo = false;
      bool hxngqKGQYe = false;
      bool zqJMtmJNHS = false;
      bool NdoJexgtNW = false;
      bool eXgKwwySWX = false;
      bool omKEXRdIbb = false;
      bool EKtdaDHdCt = false;
      bool cLDCzaJzPy = false;
      bool oppidaSjkN = false;
      bool SXSkSUdDis = false;
      bool oTQcudiIFw = false;
      bool HesdmNTKzz = false;
      bool kWroaFsRje = false;
      bool xGPWJUZNnA = false;
      bool qKenFnenyE = false;
      bool BTDjIRaaCo = false;
      bool jRYazBOVUR = false;
      string utAMpbKdes;
      string MclIgmOoxk;
      string rMPtFuWAkT;
      string SYWHOUtaDE;
      string lPFtxAYhAF;
      string KgccIidFGt;
      string FKsLamGdsL;
      string rnlrybGUxF;
      string WnAfIlwszf;
      string pnUIzaWsTJ;
      string ttonMWtjdg;
      string bIIBXRKNDn;
      string qMeNVDTcsX;
      string FMBmKbyLSk;
      string qMPSDgfSkg;
      string QIpeShPaRI;
      string DRpGaPHVqu;
      string SytRxewMKn;
      string XAqLGwVVUb;
      string MWtJhZVIqn;
      if(utAMpbKdes == ttonMWtjdg){YJbpOROYhm = true;}
      else if(ttonMWtjdg == utAMpbKdes){cLDCzaJzPy = true;}
      if(MclIgmOoxk == bIIBXRKNDn){kCQckDZdze = true;}
      else if(bIIBXRKNDn == MclIgmOoxk){oppidaSjkN = true;}
      if(rMPtFuWAkT == qMeNVDTcsX){slAOhuEjiX = true;}
      else if(qMeNVDTcsX == rMPtFuWAkT){SXSkSUdDis = true;}
      if(SYWHOUtaDE == FMBmKbyLSk){InVWPNXBxo = true;}
      else if(FMBmKbyLSk == SYWHOUtaDE){oTQcudiIFw = true;}
      if(lPFtxAYhAF == qMPSDgfSkg){hxngqKGQYe = true;}
      else if(qMPSDgfSkg == lPFtxAYhAF){HesdmNTKzz = true;}
      if(KgccIidFGt == QIpeShPaRI){zqJMtmJNHS = true;}
      else if(QIpeShPaRI == KgccIidFGt){kWroaFsRje = true;}
      if(FKsLamGdsL == DRpGaPHVqu){NdoJexgtNW = true;}
      else if(DRpGaPHVqu == FKsLamGdsL){xGPWJUZNnA = true;}
      if(rnlrybGUxF == SytRxewMKn){eXgKwwySWX = true;}
      if(WnAfIlwszf == XAqLGwVVUb){omKEXRdIbb = true;}
      if(pnUIzaWsTJ == MWtJhZVIqn){EKtdaDHdCt = true;}
      while(SytRxewMKn == rnlrybGUxF){qKenFnenyE = true;}
      while(XAqLGwVVUb == XAqLGwVVUb){BTDjIRaaCo = true;}
      while(MWtJhZVIqn == MWtJhZVIqn){jRYazBOVUR = true;}
      if(YJbpOROYhm == true){YJbpOROYhm = false;}
      if(kCQckDZdze == true){kCQckDZdze = false;}
      if(slAOhuEjiX == true){slAOhuEjiX = false;}
      if(InVWPNXBxo == true){InVWPNXBxo = false;}
      if(hxngqKGQYe == true){hxngqKGQYe = false;}
      if(zqJMtmJNHS == true){zqJMtmJNHS = false;}
      if(NdoJexgtNW == true){NdoJexgtNW = false;}
      if(eXgKwwySWX == true){eXgKwwySWX = false;}
      if(omKEXRdIbb == true){omKEXRdIbb = false;}
      if(EKtdaDHdCt == true){EKtdaDHdCt = false;}
      if(cLDCzaJzPy == true){cLDCzaJzPy = false;}
      if(oppidaSjkN == true){oppidaSjkN = false;}
      if(SXSkSUdDis == true){SXSkSUdDis = false;}
      if(oTQcudiIFw == true){oTQcudiIFw = false;}
      if(HesdmNTKzz == true){HesdmNTKzz = false;}
      if(kWroaFsRje == true){kWroaFsRje = false;}
      if(xGPWJUZNnA == true){xGPWJUZNnA = false;}
      if(qKenFnenyE == true){qKenFnenyE = false;}
      if(BTDjIRaaCo == true){BTDjIRaaCo = false;}
      if(jRYazBOVUR == true){jRYazBOVUR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WTKMOVSNSH
{ 
  void iOITOpSfhV()
  { 
      bool aJfjktTUnU = false;
      bool qLzfytSsRF = false;
      bool epaxYIqMrL = false;
      bool xpPNSVXnoc = false;
      bool JgnshZygpc = false;
      bool LJTyQjiiLb = false;
      bool DGcbWBwkMb = false;
      bool WeEouyCgPy = false;
      bool JKVOzmVQxh = false;
      bool mobMYCELVg = false;
      bool dMTNGgFeCR = false;
      bool hCSNSsjNbj = false;
      bool eeneogCqPs = false;
      bool spKiTwqIIS = false;
      bool gqOezkVOtf = false;
      bool SqjlCzYnYZ = false;
      bool dOPIYrqjsV = false;
      bool CbFJCmPJfE = false;
      bool KnwjaCGXgU = false;
      bool XCiinSaFFG = false;
      string eYUUaywqbe;
      string ByPOCjgfpe;
      string jzuNjDiMqL;
      string gRGrdxfFrT;
      string WrnrfQFgQM;
      string hzHTYfcHkX;
      string PjAPxjqXkF;
      string DbmVIqKCgT;
      string xCwdchJmSy;
      string TYUTElrXtw;
      string YhuKJGLlLg;
      string UaZQZMnWmO;
      string ZEEmleHSRV;
      string zmIktPGkTW;
      string WXbkcsyDtq;
      string yVkfWUdIYe;
      string yrTohgRoWJ;
      string GDCPqBcSJs;
      string fEYZXcCbOZ;
      string kxMoXeDlDu;
      if(eYUUaywqbe == YhuKJGLlLg){aJfjktTUnU = true;}
      else if(YhuKJGLlLg == eYUUaywqbe){dMTNGgFeCR = true;}
      if(ByPOCjgfpe == UaZQZMnWmO){qLzfytSsRF = true;}
      else if(UaZQZMnWmO == ByPOCjgfpe){hCSNSsjNbj = true;}
      if(jzuNjDiMqL == ZEEmleHSRV){epaxYIqMrL = true;}
      else if(ZEEmleHSRV == jzuNjDiMqL){eeneogCqPs = true;}
      if(gRGrdxfFrT == zmIktPGkTW){xpPNSVXnoc = true;}
      else if(zmIktPGkTW == gRGrdxfFrT){spKiTwqIIS = true;}
      if(WrnrfQFgQM == WXbkcsyDtq){JgnshZygpc = true;}
      else if(WXbkcsyDtq == WrnrfQFgQM){gqOezkVOtf = true;}
      if(hzHTYfcHkX == yVkfWUdIYe){LJTyQjiiLb = true;}
      else if(yVkfWUdIYe == hzHTYfcHkX){SqjlCzYnYZ = true;}
      if(PjAPxjqXkF == yrTohgRoWJ){DGcbWBwkMb = true;}
      else if(yrTohgRoWJ == PjAPxjqXkF){dOPIYrqjsV = true;}
      if(DbmVIqKCgT == GDCPqBcSJs){WeEouyCgPy = true;}
      if(xCwdchJmSy == fEYZXcCbOZ){JKVOzmVQxh = true;}
      if(TYUTElrXtw == kxMoXeDlDu){mobMYCELVg = true;}
      while(GDCPqBcSJs == DbmVIqKCgT){CbFJCmPJfE = true;}
      while(fEYZXcCbOZ == fEYZXcCbOZ){KnwjaCGXgU = true;}
      while(kxMoXeDlDu == kxMoXeDlDu){XCiinSaFFG = true;}
      if(aJfjktTUnU == true){aJfjktTUnU = false;}
      if(qLzfytSsRF == true){qLzfytSsRF = false;}
      if(epaxYIqMrL == true){epaxYIqMrL = false;}
      if(xpPNSVXnoc == true){xpPNSVXnoc = false;}
      if(JgnshZygpc == true){JgnshZygpc = false;}
      if(LJTyQjiiLb == true){LJTyQjiiLb = false;}
      if(DGcbWBwkMb == true){DGcbWBwkMb = false;}
      if(WeEouyCgPy == true){WeEouyCgPy = false;}
      if(JKVOzmVQxh == true){JKVOzmVQxh = false;}
      if(mobMYCELVg == true){mobMYCELVg = false;}
      if(dMTNGgFeCR == true){dMTNGgFeCR = false;}
      if(hCSNSsjNbj == true){hCSNSsjNbj = false;}
      if(eeneogCqPs == true){eeneogCqPs = false;}
      if(spKiTwqIIS == true){spKiTwqIIS = false;}
      if(gqOezkVOtf == true){gqOezkVOtf = false;}
      if(SqjlCzYnYZ == true){SqjlCzYnYZ = false;}
      if(dOPIYrqjsV == true){dOPIYrqjsV = false;}
      if(CbFJCmPJfE == true){CbFJCmPJfE = false;}
      if(KnwjaCGXgU == true){KnwjaCGXgU = false;}
      if(XCiinSaFFG == true){XCiinSaFFG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHFBXTTRBY
{ 
  void uTQtPcZiTV()
  { 
      bool oWwPaLWQTd = false;
      bool wqokoMnTSo = false;
      bool KqqRnVsdlF = false;
      bool cecJaszPPT = false;
      bool NtJZQOXcHX = false;
      bool gOaInyeeaE = false;
      bool RsdNBROfJw = false;
      bool MYEybQgRBZ = false;
      bool xQVNYNDTUc = false;
      bool NToKCUPwYy = false;
      bool AqSLKIKcgX = false;
      bool QNdBGBWPnm = false;
      bool NuKghriswG = false;
      bool AkrCYGxKDP = false;
      bool DalxLzpmDA = false;
      bool yzHlkEglcS = false;
      bool YQfaWeVbbA = false;
      bool EMMYimJNUi = false;
      bool CupwHBcGRU = false;
      bool YKgkpmuKZf = false;
      string VCQRSWLmLF;
      string WtqgMbrWut;
      string GxVmdBlxTU;
      string kQhFNikdyp;
      string EuuizDGwFd;
      string tiOnVXfcnR;
      string kOTqUFMkTd;
      string pNXFoLCmmZ;
      string uoqpZBCsjp;
      string CHpgFpbEOs;
      string pUcbmgLJyK;
      string UsoOVuWdQS;
      string DTBdahXqzz;
      string iyYtiZMPCs;
      string prtZUJSbLJ;
      string SymuoWTyBF;
      string IUJzaVTueu;
      string iHaWbLZbIQ;
      string PwfpfkKcEM;
      string GNNxjVhtyz;
      if(VCQRSWLmLF == pUcbmgLJyK){oWwPaLWQTd = true;}
      else if(pUcbmgLJyK == VCQRSWLmLF){AqSLKIKcgX = true;}
      if(WtqgMbrWut == UsoOVuWdQS){wqokoMnTSo = true;}
      else if(UsoOVuWdQS == WtqgMbrWut){QNdBGBWPnm = true;}
      if(GxVmdBlxTU == DTBdahXqzz){KqqRnVsdlF = true;}
      else if(DTBdahXqzz == GxVmdBlxTU){NuKghriswG = true;}
      if(kQhFNikdyp == iyYtiZMPCs){cecJaszPPT = true;}
      else if(iyYtiZMPCs == kQhFNikdyp){AkrCYGxKDP = true;}
      if(EuuizDGwFd == prtZUJSbLJ){NtJZQOXcHX = true;}
      else if(prtZUJSbLJ == EuuizDGwFd){DalxLzpmDA = true;}
      if(tiOnVXfcnR == SymuoWTyBF){gOaInyeeaE = true;}
      else if(SymuoWTyBF == tiOnVXfcnR){yzHlkEglcS = true;}
      if(kOTqUFMkTd == IUJzaVTueu){RsdNBROfJw = true;}
      else if(IUJzaVTueu == kOTqUFMkTd){YQfaWeVbbA = true;}
      if(pNXFoLCmmZ == iHaWbLZbIQ){MYEybQgRBZ = true;}
      if(uoqpZBCsjp == PwfpfkKcEM){xQVNYNDTUc = true;}
      if(CHpgFpbEOs == GNNxjVhtyz){NToKCUPwYy = true;}
      while(iHaWbLZbIQ == pNXFoLCmmZ){EMMYimJNUi = true;}
      while(PwfpfkKcEM == PwfpfkKcEM){CupwHBcGRU = true;}
      while(GNNxjVhtyz == GNNxjVhtyz){YKgkpmuKZf = true;}
      if(oWwPaLWQTd == true){oWwPaLWQTd = false;}
      if(wqokoMnTSo == true){wqokoMnTSo = false;}
      if(KqqRnVsdlF == true){KqqRnVsdlF = false;}
      if(cecJaszPPT == true){cecJaszPPT = false;}
      if(NtJZQOXcHX == true){NtJZQOXcHX = false;}
      if(gOaInyeeaE == true){gOaInyeeaE = false;}
      if(RsdNBROfJw == true){RsdNBROfJw = false;}
      if(MYEybQgRBZ == true){MYEybQgRBZ = false;}
      if(xQVNYNDTUc == true){xQVNYNDTUc = false;}
      if(NToKCUPwYy == true){NToKCUPwYy = false;}
      if(AqSLKIKcgX == true){AqSLKIKcgX = false;}
      if(QNdBGBWPnm == true){QNdBGBWPnm = false;}
      if(NuKghriswG == true){NuKghriswG = false;}
      if(AkrCYGxKDP == true){AkrCYGxKDP = false;}
      if(DalxLzpmDA == true){DalxLzpmDA = false;}
      if(yzHlkEglcS == true){yzHlkEglcS = false;}
      if(YQfaWeVbbA == true){YQfaWeVbbA = false;}
      if(EMMYimJNUi == true){EMMYimJNUi = false;}
      if(CupwHBcGRU == true){CupwHBcGRU = false;}
      if(YKgkpmuKZf == true){YKgkpmuKZf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDMFCMQWIP
{ 
  void dxIMTAazJy()
  { 
      bool swhDUlwCle = false;
      bool HdWNyWjVOz = false;
      bool UBVnDUzMuR = false;
      bool bAbEjKiwhh = false;
      bool EodJqwllmP = false;
      bool RNgwTqatAA = false;
      bool ljHTDGCSdn = false;
      bool nmngufXMxH = false;
      bool hNYeAOTfjr = false;
      bool jnwguThJFj = false;
      bool sTHzbdYzBn = false;
      bool TOxsRYKbTn = false;
      bool mWhlDzqGka = false;
      bool xNGMNNGZDV = false;
      bool oUduYVqDOW = false;
      bool JFpQxWkVuc = false;
      bool mSOZqFHjeE = false;
      bool SkYxzRrmNh = false;
      bool ImqOQrWoPq = false;
      bool cjdahWGDES = false;
      string umieUdJapK;
      string TmRwNfiLyd;
      string GfNEGTmsfc;
      string wPsLHYYjos;
      string tdHcOYYAUX;
      string aofZWOYeXA;
      string pPuMNDtGnn;
      string GzVFjcYkph;
      string tlXHCGjTns;
      string ztLnDdhuOK;
      string eSMfQbSaot;
      string pnopFEqnJH;
      string TaRuoMmhBG;
      string tdWeDbZqpa;
      string mIdtCLFVhz;
      string ltkGpEBQqE;
      string nkYizMRJmd;
      string dzxhULwWsc;
      string GRACTArPny;
      string aJAkmCiuuo;
      if(umieUdJapK == eSMfQbSaot){swhDUlwCle = true;}
      else if(eSMfQbSaot == umieUdJapK){sTHzbdYzBn = true;}
      if(TmRwNfiLyd == pnopFEqnJH){HdWNyWjVOz = true;}
      else if(pnopFEqnJH == TmRwNfiLyd){TOxsRYKbTn = true;}
      if(GfNEGTmsfc == TaRuoMmhBG){UBVnDUzMuR = true;}
      else if(TaRuoMmhBG == GfNEGTmsfc){mWhlDzqGka = true;}
      if(wPsLHYYjos == tdWeDbZqpa){bAbEjKiwhh = true;}
      else if(tdWeDbZqpa == wPsLHYYjos){xNGMNNGZDV = true;}
      if(tdHcOYYAUX == mIdtCLFVhz){EodJqwllmP = true;}
      else if(mIdtCLFVhz == tdHcOYYAUX){oUduYVqDOW = true;}
      if(aofZWOYeXA == ltkGpEBQqE){RNgwTqatAA = true;}
      else if(ltkGpEBQqE == aofZWOYeXA){JFpQxWkVuc = true;}
      if(pPuMNDtGnn == nkYizMRJmd){ljHTDGCSdn = true;}
      else if(nkYizMRJmd == pPuMNDtGnn){mSOZqFHjeE = true;}
      if(GzVFjcYkph == dzxhULwWsc){nmngufXMxH = true;}
      if(tlXHCGjTns == GRACTArPny){hNYeAOTfjr = true;}
      if(ztLnDdhuOK == aJAkmCiuuo){jnwguThJFj = true;}
      while(dzxhULwWsc == GzVFjcYkph){SkYxzRrmNh = true;}
      while(GRACTArPny == GRACTArPny){ImqOQrWoPq = true;}
      while(aJAkmCiuuo == aJAkmCiuuo){cjdahWGDES = true;}
      if(swhDUlwCle == true){swhDUlwCle = false;}
      if(HdWNyWjVOz == true){HdWNyWjVOz = false;}
      if(UBVnDUzMuR == true){UBVnDUzMuR = false;}
      if(bAbEjKiwhh == true){bAbEjKiwhh = false;}
      if(EodJqwllmP == true){EodJqwllmP = false;}
      if(RNgwTqatAA == true){RNgwTqatAA = false;}
      if(ljHTDGCSdn == true){ljHTDGCSdn = false;}
      if(nmngufXMxH == true){nmngufXMxH = false;}
      if(hNYeAOTfjr == true){hNYeAOTfjr = false;}
      if(jnwguThJFj == true){jnwguThJFj = false;}
      if(sTHzbdYzBn == true){sTHzbdYzBn = false;}
      if(TOxsRYKbTn == true){TOxsRYKbTn = false;}
      if(mWhlDzqGka == true){mWhlDzqGka = false;}
      if(xNGMNNGZDV == true){xNGMNNGZDV = false;}
      if(oUduYVqDOW == true){oUduYVqDOW = false;}
      if(JFpQxWkVuc == true){JFpQxWkVuc = false;}
      if(mSOZqFHjeE == true){mSOZqFHjeE = false;}
      if(SkYxzRrmNh == true){SkYxzRrmNh = false;}
      if(ImqOQrWoPq == true){ImqOQrWoPq = false;}
      if(cjdahWGDES == true){cjdahWGDES = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDBGXHHUSO
{ 
  void yPGBRwRcgx()
  { 
      bool TFEcQdSYQt = false;
      bool pICwbokdzt = false;
      bool OKZQqqSbnf = false;
      bool zYzhkPkyYM = false;
      bool CMrQhsuzCp = false;
      bool GLcoEJenkY = false;
      bool LpjkuRJUKM = false;
      bool DlFlqBRJiy = false;
      bool uSZyZmuJcb = false;
      bool kxMzBLcGUP = false;
      bool janplTGpxD = false;
      bool qVElcrQlLI = false;
      bool VzriaGYFkf = false;
      bool XLoSOUejLF = false;
      bool fEMYjOraVI = false;
      bool uptMsjhFOf = false;
      bool uBFRefflXI = false;
      bool NgaGbQlSyM = false;
      bool NyibkhQbYd = false;
      bool lZVfKezusE = false;
      string SsmbpiCLgU;
      string DPUElPMRIB;
      string mhPewlRtla;
      string fgEajkedLO;
      string NheDDVTryx;
      string zQIMPjdHeD;
      string QIYGoVKtUB;
      string kiGsnEDLbZ;
      string SZuoaOXqLz;
      string GWyHxEJXOg;
      string KZXxLPKOYL;
      string fRfEkqMjeZ;
      string xTiUtNjyui;
      string uextPrBycK;
      string DISzTnqtVG;
      string rYsniqqDCy;
      string fMSpPATkos;
      string oOGTWnAiAF;
      string VpbopVlJKX;
      string ByueeqobiS;
      if(SsmbpiCLgU == KZXxLPKOYL){TFEcQdSYQt = true;}
      else if(KZXxLPKOYL == SsmbpiCLgU){janplTGpxD = true;}
      if(DPUElPMRIB == fRfEkqMjeZ){pICwbokdzt = true;}
      else if(fRfEkqMjeZ == DPUElPMRIB){qVElcrQlLI = true;}
      if(mhPewlRtla == xTiUtNjyui){OKZQqqSbnf = true;}
      else if(xTiUtNjyui == mhPewlRtla){VzriaGYFkf = true;}
      if(fgEajkedLO == uextPrBycK){zYzhkPkyYM = true;}
      else if(uextPrBycK == fgEajkedLO){XLoSOUejLF = true;}
      if(NheDDVTryx == DISzTnqtVG){CMrQhsuzCp = true;}
      else if(DISzTnqtVG == NheDDVTryx){fEMYjOraVI = true;}
      if(zQIMPjdHeD == rYsniqqDCy){GLcoEJenkY = true;}
      else if(rYsniqqDCy == zQIMPjdHeD){uptMsjhFOf = true;}
      if(QIYGoVKtUB == fMSpPATkos){LpjkuRJUKM = true;}
      else if(fMSpPATkos == QIYGoVKtUB){uBFRefflXI = true;}
      if(kiGsnEDLbZ == oOGTWnAiAF){DlFlqBRJiy = true;}
      if(SZuoaOXqLz == VpbopVlJKX){uSZyZmuJcb = true;}
      if(GWyHxEJXOg == ByueeqobiS){kxMzBLcGUP = true;}
      while(oOGTWnAiAF == kiGsnEDLbZ){NgaGbQlSyM = true;}
      while(VpbopVlJKX == VpbopVlJKX){NyibkhQbYd = true;}
      while(ByueeqobiS == ByueeqobiS){lZVfKezusE = true;}
      if(TFEcQdSYQt == true){TFEcQdSYQt = false;}
      if(pICwbokdzt == true){pICwbokdzt = false;}
      if(OKZQqqSbnf == true){OKZQqqSbnf = false;}
      if(zYzhkPkyYM == true){zYzhkPkyYM = false;}
      if(CMrQhsuzCp == true){CMrQhsuzCp = false;}
      if(GLcoEJenkY == true){GLcoEJenkY = false;}
      if(LpjkuRJUKM == true){LpjkuRJUKM = false;}
      if(DlFlqBRJiy == true){DlFlqBRJiy = false;}
      if(uSZyZmuJcb == true){uSZyZmuJcb = false;}
      if(kxMzBLcGUP == true){kxMzBLcGUP = false;}
      if(janplTGpxD == true){janplTGpxD = false;}
      if(qVElcrQlLI == true){qVElcrQlLI = false;}
      if(VzriaGYFkf == true){VzriaGYFkf = false;}
      if(XLoSOUejLF == true){XLoSOUejLF = false;}
      if(fEMYjOraVI == true){fEMYjOraVI = false;}
      if(uptMsjhFOf == true){uptMsjhFOf = false;}
      if(uBFRefflXI == true){uBFRefflXI = false;}
      if(NgaGbQlSyM == true){NgaGbQlSyM = false;}
      if(NyibkhQbYd == true){NyibkhQbYd = false;}
      if(lZVfKezusE == true){lZVfKezusE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFKHWZUYWG
{ 
  void zKBrMgsekk()
  { 
      bool TTxQszuAZz = false;
      bool wUCSyjleFC = false;
      bool lnCMWOKdGb = false;
      bool omdCVIrNOP = false;
      bool VwaESRAuAJ = false;
      bool iEwDxfQjte = false;
      bool oQtyJIqzxo = false;
      bool rXPogpMytE = false;
      bool OOdxrkqaFo = false;
      bool rHTiaECbtK = false;
      bool aAxKQKnHWH = false;
      bool TRpoQZmxGY = false;
      bool QPtIwkEgOb = false;
      bool njDjdNRSfg = false;
      bool wjEyUZQeSA = false;
      bool RFVUsKGoOf = false;
      bool GHrtTjOGKD = false;
      bool ITQYcgLwmW = false;
      bool TYNNJhNipS = false;
      bool GcEzaoqJek = false;
      string FVONoasAeH;
      string toKwrBleEE;
      string xJbjnZfPtF;
      string PXxMtSnYtP;
      string xfsxopOuiq;
      string zHuQbwsdZO;
      string tcFYqWrxCY;
      string MMkoHQQeuy;
      string LkgDFIbfkx;
      string YJzeUTaTFS;
      string yRsJdlWGIK;
      string eOiaDJwCSh;
      string tMLEADNFTn;
      string pwYbAsqXYS;
      string lVWaRKaXaL;
      string XYAWXkGnJa;
      string YQmUUhpGaK;
      string RYcAwYoklp;
      string coeHPRwBEO;
      string mCNysUiBGi;
      if(FVONoasAeH == yRsJdlWGIK){TTxQszuAZz = true;}
      else if(yRsJdlWGIK == FVONoasAeH){aAxKQKnHWH = true;}
      if(toKwrBleEE == eOiaDJwCSh){wUCSyjleFC = true;}
      else if(eOiaDJwCSh == toKwrBleEE){TRpoQZmxGY = true;}
      if(xJbjnZfPtF == tMLEADNFTn){lnCMWOKdGb = true;}
      else if(tMLEADNFTn == xJbjnZfPtF){QPtIwkEgOb = true;}
      if(PXxMtSnYtP == pwYbAsqXYS){omdCVIrNOP = true;}
      else if(pwYbAsqXYS == PXxMtSnYtP){njDjdNRSfg = true;}
      if(xfsxopOuiq == lVWaRKaXaL){VwaESRAuAJ = true;}
      else if(lVWaRKaXaL == xfsxopOuiq){wjEyUZQeSA = true;}
      if(zHuQbwsdZO == XYAWXkGnJa){iEwDxfQjte = true;}
      else if(XYAWXkGnJa == zHuQbwsdZO){RFVUsKGoOf = true;}
      if(tcFYqWrxCY == YQmUUhpGaK){oQtyJIqzxo = true;}
      else if(YQmUUhpGaK == tcFYqWrxCY){GHrtTjOGKD = true;}
      if(MMkoHQQeuy == RYcAwYoklp){rXPogpMytE = true;}
      if(LkgDFIbfkx == coeHPRwBEO){OOdxrkqaFo = true;}
      if(YJzeUTaTFS == mCNysUiBGi){rHTiaECbtK = true;}
      while(RYcAwYoklp == MMkoHQQeuy){ITQYcgLwmW = true;}
      while(coeHPRwBEO == coeHPRwBEO){TYNNJhNipS = true;}
      while(mCNysUiBGi == mCNysUiBGi){GcEzaoqJek = true;}
      if(TTxQszuAZz == true){TTxQszuAZz = false;}
      if(wUCSyjleFC == true){wUCSyjleFC = false;}
      if(lnCMWOKdGb == true){lnCMWOKdGb = false;}
      if(omdCVIrNOP == true){omdCVIrNOP = false;}
      if(VwaESRAuAJ == true){VwaESRAuAJ = false;}
      if(iEwDxfQjte == true){iEwDxfQjte = false;}
      if(oQtyJIqzxo == true){oQtyJIqzxo = false;}
      if(rXPogpMytE == true){rXPogpMytE = false;}
      if(OOdxrkqaFo == true){OOdxrkqaFo = false;}
      if(rHTiaECbtK == true){rHTiaECbtK = false;}
      if(aAxKQKnHWH == true){aAxKQKnHWH = false;}
      if(TRpoQZmxGY == true){TRpoQZmxGY = false;}
      if(QPtIwkEgOb == true){QPtIwkEgOb = false;}
      if(njDjdNRSfg == true){njDjdNRSfg = false;}
      if(wjEyUZQeSA == true){wjEyUZQeSA = false;}
      if(RFVUsKGoOf == true){RFVUsKGoOf = false;}
      if(GHrtTjOGKD == true){GHrtTjOGKD = false;}
      if(ITQYcgLwmW == true){ITQYcgLwmW = false;}
      if(TYNNJhNipS == true){TYNNJhNipS = false;}
      if(GcEzaoqJek == true){GcEzaoqJek = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGZKYFQSQZ
{ 
  void LXPCguJEXO()
  { 
      bool ELBcfmhFbQ = false;
      bool fdPBANGLEW = false;
      bool BLXlJDgaVu = false;
      bool YuqPfwpFcC = false;
      bool sVTTHPwNZG = false;
      bool TeKyNrnOTb = false;
      bool GGigqjmzUE = false;
      bool XBiCcfqEes = false;
      bool HSBPatjrCn = false;
      bool IakAwmmmbW = false;
      bool cxrViRuIUh = false;
      bool BijaUmESFx = false;
      bool ztxguwQiGp = false;
      bool sDbHPJaffI = false;
      bool ybWTlYpJeI = false;
      bool iTheWiAKZm = false;
      bool BMCenxHcKL = false;
      bool MXmwyXWcuW = false;
      bool FGDxHYVxjg = false;
      bool IPGsHkZrfn = false;
      string AFEMwPQemc;
      string yQawCVdNse;
      string CPZANtPfbW;
      string RjMQdsyeZT;
      string UXeuYSimsH;
      string XtyfmkfDzB;
      string AkDQKNEKRJ;
      string WznYJdkdbt;
      string LblTzWkgcs;
      string MufXTiTNkK;
      string OYUikYGZVI;
      string zBaEpXzjRm;
      string cWgYwbSQEa;
      string KWsRelHChZ;
      string QLLTsLTagw;
      string jiwxgqqumI;
      string FpUuycHIZD;
      string PwBqVQLNfk;
      string HqiIpaawjm;
      string tLPZUaqPVP;
      if(AFEMwPQemc == OYUikYGZVI){ELBcfmhFbQ = true;}
      else if(OYUikYGZVI == AFEMwPQemc){cxrViRuIUh = true;}
      if(yQawCVdNse == zBaEpXzjRm){fdPBANGLEW = true;}
      else if(zBaEpXzjRm == yQawCVdNse){BijaUmESFx = true;}
      if(CPZANtPfbW == cWgYwbSQEa){BLXlJDgaVu = true;}
      else if(cWgYwbSQEa == CPZANtPfbW){ztxguwQiGp = true;}
      if(RjMQdsyeZT == KWsRelHChZ){YuqPfwpFcC = true;}
      else if(KWsRelHChZ == RjMQdsyeZT){sDbHPJaffI = true;}
      if(UXeuYSimsH == QLLTsLTagw){sVTTHPwNZG = true;}
      else if(QLLTsLTagw == UXeuYSimsH){ybWTlYpJeI = true;}
      if(XtyfmkfDzB == jiwxgqqumI){TeKyNrnOTb = true;}
      else if(jiwxgqqumI == XtyfmkfDzB){iTheWiAKZm = true;}
      if(AkDQKNEKRJ == FpUuycHIZD){GGigqjmzUE = true;}
      else if(FpUuycHIZD == AkDQKNEKRJ){BMCenxHcKL = true;}
      if(WznYJdkdbt == PwBqVQLNfk){XBiCcfqEes = true;}
      if(LblTzWkgcs == HqiIpaawjm){HSBPatjrCn = true;}
      if(MufXTiTNkK == tLPZUaqPVP){IakAwmmmbW = true;}
      while(PwBqVQLNfk == WznYJdkdbt){MXmwyXWcuW = true;}
      while(HqiIpaawjm == HqiIpaawjm){FGDxHYVxjg = true;}
      while(tLPZUaqPVP == tLPZUaqPVP){IPGsHkZrfn = true;}
      if(ELBcfmhFbQ == true){ELBcfmhFbQ = false;}
      if(fdPBANGLEW == true){fdPBANGLEW = false;}
      if(BLXlJDgaVu == true){BLXlJDgaVu = false;}
      if(YuqPfwpFcC == true){YuqPfwpFcC = false;}
      if(sVTTHPwNZG == true){sVTTHPwNZG = false;}
      if(TeKyNrnOTb == true){TeKyNrnOTb = false;}
      if(GGigqjmzUE == true){GGigqjmzUE = false;}
      if(XBiCcfqEes == true){XBiCcfqEes = false;}
      if(HSBPatjrCn == true){HSBPatjrCn = false;}
      if(IakAwmmmbW == true){IakAwmmmbW = false;}
      if(cxrViRuIUh == true){cxrViRuIUh = false;}
      if(BijaUmESFx == true){BijaUmESFx = false;}
      if(ztxguwQiGp == true){ztxguwQiGp = false;}
      if(sDbHPJaffI == true){sDbHPJaffI = false;}
      if(ybWTlYpJeI == true){ybWTlYpJeI = false;}
      if(iTheWiAKZm == true){iTheWiAKZm = false;}
      if(BMCenxHcKL == true){BMCenxHcKL = false;}
      if(MXmwyXWcuW == true){MXmwyXWcuW = false;}
      if(FGDxHYVxjg == true){FGDxHYVxjg = false;}
      if(IPGsHkZrfn == true){IPGsHkZrfn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THNJGDOZAR
{ 
  void dIqPUqpxsZ()
  { 
      bool ldYTjubpaO = false;
      bool zePTQsbJjG = false;
      bool KjmxTbDzcp = false;
      bool qApjXbGMap = false;
      bool HTPaoukCCG = false;
      bool XEZeUCpaAI = false;
      bool qbNkWzofwn = false;
      bool lOitzpTMIX = false;
      bool pBxWRmZLOU = false;
      bool lfMSyeGeDo = false;
      bool GFGNTJVffd = false;
      bool hdRbRpdpSj = false;
      bool ZcQaCGBPuT = false;
      bool joJSRkujDH = false;
      bool RsejlHNkAI = false;
      bool BPLTOcneKN = false;
      bool HFjLtsUzJg = false;
      bool ttmLRgyfnt = false;
      bool rQOmSTdoEo = false;
      bool wPYozMISps = false;
      string DBIsfSAAkU;
      string jssHMNcHAg;
      string SHyyEGhVRu;
      string HRrttwEmSG;
      string blJccCKHSr;
      string GtnhzuCJnZ;
      string jehoMSByNQ;
      string IpotEgxVVB;
      string uaDZnNcJty;
      string suyrVxDTPK;
      string BMtCjQEscS;
      string ygnmdJaIBy;
      string oqEOWMqwXH;
      string dcGKzifBpX;
      string IifazMGLOM;
      string VtSQUKIeeW;
      string YIUVoUZcmt;
      string cZScpFKcOK;
      string FfgLkiKppo;
      string aBVSzANKle;
      if(DBIsfSAAkU == BMtCjQEscS){ldYTjubpaO = true;}
      else if(BMtCjQEscS == DBIsfSAAkU){GFGNTJVffd = true;}
      if(jssHMNcHAg == ygnmdJaIBy){zePTQsbJjG = true;}
      else if(ygnmdJaIBy == jssHMNcHAg){hdRbRpdpSj = true;}
      if(SHyyEGhVRu == oqEOWMqwXH){KjmxTbDzcp = true;}
      else if(oqEOWMqwXH == SHyyEGhVRu){ZcQaCGBPuT = true;}
      if(HRrttwEmSG == dcGKzifBpX){qApjXbGMap = true;}
      else if(dcGKzifBpX == HRrttwEmSG){joJSRkujDH = true;}
      if(blJccCKHSr == IifazMGLOM){HTPaoukCCG = true;}
      else if(IifazMGLOM == blJccCKHSr){RsejlHNkAI = true;}
      if(GtnhzuCJnZ == VtSQUKIeeW){XEZeUCpaAI = true;}
      else if(VtSQUKIeeW == GtnhzuCJnZ){BPLTOcneKN = true;}
      if(jehoMSByNQ == YIUVoUZcmt){qbNkWzofwn = true;}
      else if(YIUVoUZcmt == jehoMSByNQ){HFjLtsUzJg = true;}
      if(IpotEgxVVB == cZScpFKcOK){lOitzpTMIX = true;}
      if(uaDZnNcJty == FfgLkiKppo){pBxWRmZLOU = true;}
      if(suyrVxDTPK == aBVSzANKle){lfMSyeGeDo = true;}
      while(cZScpFKcOK == IpotEgxVVB){ttmLRgyfnt = true;}
      while(FfgLkiKppo == FfgLkiKppo){rQOmSTdoEo = true;}
      while(aBVSzANKle == aBVSzANKle){wPYozMISps = true;}
      if(ldYTjubpaO == true){ldYTjubpaO = false;}
      if(zePTQsbJjG == true){zePTQsbJjG = false;}
      if(KjmxTbDzcp == true){KjmxTbDzcp = false;}
      if(qApjXbGMap == true){qApjXbGMap = false;}
      if(HTPaoukCCG == true){HTPaoukCCG = false;}
      if(XEZeUCpaAI == true){XEZeUCpaAI = false;}
      if(qbNkWzofwn == true){qbNkWzofwn = false;}
      if(lOitzpTMIX == true){lOitzpTMIX = false;}
      if(pBxWRmZLOU == true){pBxWRmZLOU = false;}
      if(lfMSyeGeDo == true){lfMSyeGeDo = false;}
      if(GFGNTJVffd == true){GFGNTJVffd = false;}
      if(hdRbRpdpSj == true){hdRbRpdpSj = false;}
      if(ZcQaCGBPuT == true){ZcQaCGBPuT = false;}
      if(joJSRkujDH == true){joJSRkujDH = false;}
      if(RsejlHNkAI == true){RsejlHNkAI = false;}
      if(BPLTOcneKN == true){BPLTOcneKN = false;}
      if(HFjLtsUzJg == true){HFjLtsUzJg = false;}
      if(ttmLRgyfnt == true){ttmLRgyfnt = false;}
      if(rQOmSTdoEo == true){rQOmSTdoEo = false;}
      if(wPYozMISps == true){wPYozMISps = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUJSBLGMMC
{ 
  void FEKKonhbhU()
  { 
      bool bLmkFqGInd = false;
      bool ZBDtQUiOhw = false;
      bool WHrEmsYYQJ = false;
      bool AbdiINMOlt = false;
      bool fpqsuJQLJB = false;
      bool TcQwwUTixM = false;
      bool SgqedxWTlD = false;
      bool HUcmPfPzJc = false;
      bool bMOOoWKgmm = false;
      bool scQYbzyMOx = false;
      bool lwZGtzAdgP = false;
      bool EUZUjFScoG = false;
      bool mpgyKdDDLP = false;
      bool hDjLpfmIUp = false;
      bool WgzWhYDwoV = false;
      bool gVWIKwOawP = false;
      bool uwRQgBkNdD = false;
      bool SJIyjFpKQk = false;
      bool aHNoiMfaBt = false;
      bool QLMEuZPipg = false;
      string iuYOXKQCkX;
      string uBDdaWwEYN;
      string PzpPAiFicg;
      string TsOzlopXFJ;
      string TyeGMiblRV;
      string GPeUtiEJOo;
      string EhYEECmDrk;
      string fXyOtRUjCR;
      string HSRHZDNsEC;
      string kgJQElYZCK;
      string uXtfoiRPab;
      string OUGwhlQReA;
      string otzoAzNhKH;
      string sthrWiYkRq;
      string lxSbmPZNiS;
      string VGuBVBYEep;
      string UiFTiUmOZy;
      string MeAmNqaWBk;
      string YAzqkmyfWU;
      string KTGaWDqzsS;
      if(iuYOXKQCkX == uXtfoiRPab){bLmkFqGInd = true;}
      else if(uXtfoiRPab == iuYOXKQCkX){lwZGtzAdgP = true;}
      if(uBDdaWwEYN == OUGwhlQReA){ZBDtQUiOhw = true;}
      else if(OUGwhlQReA == uBDdaWwEYN){EUZUjFScoG = true;}
      if(PzpPAiFicg == otzoAzNhKH){WHrEmsYYQJ = true;}
      else if(otzoAzNhKH == PzpPAiFicg){mpgyKdDDLP = true;}
      if(TsOzlopXFJ == sthrWiYkRq){AbdiINMOlt = true;}
      else if(sthrWiYkRq == TsOzlopXFJ){hDjLpfmIUp = true;}
      if(TyeGMiblRV == lxSbmPZNiS){fpqsuJQLJB = true;}
      else if(lxSbmPZNiS == TyeGMiblRV){WgzWhYDwoV = true;}
      if(GPeUtiEJOo == VGuBVBYEep){TcQwwUTixM = true;}
      else if(VGuBVBYEep == GPeUtiEJOo){gVWIKwOawP = true;}
      if(EhYEECmDrk == UiFTiUmOZy){SgqedxWTlD = true;}
      else if(UiFTiUmOZy == EhYEECmDrk){uwRQgBkNdD = true;}
      if(fXyOtRUjCR == MeAmNqaWBk){HUcmPfPzJc = true;}
      if(HSRHZDNsEC == YAzqkmyfWU){bMOOoWKgmm = true;}
      if(kgJQElYZCK == KTGaWDqzsS){scQYbzyMOx = true;}
      while(MeAmNqaWBk == fXyOtRUjCR){SJIyjFpKQk = true;}
      while(YAzqkmyfWU == YAzqkmyfWU){aHNoiMfaBt = true;}
      while(KTGaWDqzsS == KTGaWDqzsS){QLMEuZPipg = true;}
      if(bLmkFqGInd == true){bLmkFqGInd = false;}
      if(ZBDtQUiOhw == true){ZBDtQUiOhw = false;}
      if(WHrEmsYYQJ == true){WHrEmsYYQJ = false;}
      if(AbdiINMOlt == true){AbdiINMOlt = false;}
      if(fpqsuJQLJB == true){fpqsuJQLJB = false;}
      if(TcQwwUTixM == true){TcQwwUTixM = false;}
      if(SgqedxWTlD == true){SgqedxWTlD = false;}
      if(HUcmPfPzJc == true){HUcmPfPzJc = false;}
      if(bMOOoWKgmm == true){bMOOoWKgmm = false;}
      if(scQYbzyMOx == true){scQYbzyMOx = false;}
      if(lwZGtzAdgP == true){lwZGtzAdgP = false;}
      if(EUZUjFScoG == true){EUZUjFScoG = false;}
      if(mpgyKdDDLP == true){mpgyKdDDLP = false;}
      if(hDjLpfmIUp == true){hDjLpfmIUp = false;}
      if(WgzWhYDwoV == true){WgzWhYDwoV = false;}
      if(gVWIKwOawP == true){gVWIKwOawP = false;}
      if(uwRQgBkNdD == true){uwRQgBkNdD = false;}
      if(SJIyjFpKQk == true){SJIyjFpKQk = false;}
      if(aHNoiMfaBt == true){aHNoiMfaBt = false;}
      if(QLMEuZPipg == true){QLMEuZPipg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJSRBMWZAU
{ 
  void nBZBjbQBbS()
  { 
      bool wVaoPLmtTK = false;
      bool zzgLJlhJXC = false;
      bool VqPRABEVOe = false;
      bool yZoSRnSACi = false;
      bool jsWUMBXFYS = false;
      bool fJpqpEGJoO = false;
      bool GQeoLZKNtU = false;
      bool TgHnRbUuEy = false;
      bool czxwynixbM = false;
      bool hJLmcTOgJm = false;
      bool pKKDzyCBYO = false;
      bool iLEpkGTipW = false;
      bool pNkgmJVTLy = false;
      bool NmkRHSnswz = false;
      bool lhXNcWFUBV = false;
      bool zeplxcYdQo = false;
      bool chpaAwZliS = false;
      bool SalqkIoXDP = false;
      bool EBRoyhwzUe = false;
      bool sKbHWDqxMg = false;
      string dzaEWRDHno;
      string oyUlCayxap;
      string ZBRVSORgxW;
      string NMyLHwaTkr;
      string RKiUUJtpXw;
      string ISzTEchFlH;
      string zWJRaczJeG;
      string zeLhXPSwAI;
      string UbIANtNdHe;
      string OVgdsuARsr;
      string JkLRxcGQwn;
      string JkEclWNIDg;
      string OVBzqcyhnc;
      string OBDIzjQqDj;
      string mwhSUdREqW;
      string hrNMcmiLZU;
      string eYbSYIhudB;
      string GVFTsSnieN;
      string KspRuWmpeL;
      string BFRiEOTOsL;
      if(dzaEWRDHno == JkLRxcGQwn){wVaoPLmtTK = true;}
      else if(JkLRxcGQwn == dzaEWRDHno){pKKDzyCBYO = true;}
      if(oyUlCayxap == JkEclWNIDg){zzgLJlhJXC = true;}
      else if(JkEclWNIDg == oyUlCayxap){iLEpkGTipW = true;}
      if(ZBRVSORgxW == OVBzqcyhnc){VqPRABEVOe = true;}
      else if(OVBzqcyhnc == ZBRVSORgxW){pNkgmJVTLy = true;}
      if(NMyLHwaTkr == OBDIzjQqDj){yZoSRnSACi = true;}
      else if(OBDIzjQqDj == NMyLHwaTkr){NmkRHSnswz = true;}
      if(RKiUUJtpXw == mwhSUdREqW){jsWUMBXFYS = true;}
      else if(mwhSUdREqW == RKiUUJtpXw){lhXNcWFUBV = true;}
      if(ISzTEchFlH == hrNMcmiLZU){fJpqpEGJoO = true;}
      else if(hrNMcmiLZU == ISzTEchFlH){zeplxcYdQo = true;}
      if(zWJRaczJeG == eYbSYIhudB){GQeoLZKNtU = true;}
      else if(eYbSYIhudB == zWJRaczJeG){chpaAwZliS = true;}
      if(zeLhXPSwAI == GVFTsSnieN){TgHnRbUuEy = true;}
      if(UbIANtNdHe == KspRuWmpeL){czxwynixbM = true;}
      if(OVgdsuARsr == BFRiEOTOsL){hJLmcTOgJm = true;}
      while(GVFTsSnieN == zeLhXPSwAI){SalqkIoXDP = true;}
      while(KspRuWmpeL == KspRuWmpeL){EBRoyhwzUe = true;}
      while(BFRiEOTOsL == BFRiEOTOsL){sKbHWDqxMg = true;}
      if(wVaoPLmtTK == true){wVaoPLmtTK = false;}
      if(zzgLJlhJXC == true){zzgLJlhJXC = false;}
      if(VqPRABEVOe == true){VqPRABEVOe = false;}
      if(yZoSRnSACi == true){yZoSRnSACi = false;}
      if(jsWUMBXFYS == true){jsWUMBXFYS = false;}
      if(fJpqpEGJoO == true){fJpqpEGJoO = false;}
      if(GQeoLZKNtU == true){GQeoLZKNtU = false;}
      if(TgHnRbUuEy == true){TgHnRbUuEy = false;}
      if(czxwynixbM == true){czxwynixbM = false;}
      if(hJLmcTOgJm == true){hJLmcTOgJm = false;}
      if(pKKDzyCBYO == true){pKKDzyCBYO = false;}
      if(iLEpkGTipW == true){iLEpkGTipW = false;}
      if(pNkgmJVTLy == true){pNkgmJVTLy = false;}
      if(NmkRHSnswz == true){NmkRHSnswz = false;}
      if(lhXNcWFUBV == true){lhXNcWFUBV = false;}
      if(zeplxcYdQo == true){zeplxcYdQo = false;}
      if(chpaAwZliS == true){chpaAwZliS = false;}
      if(SalqkIoXDP == true){SalqkIoXDP = false;}
      if(EBRoyhwzUe == true){EBRoyhwzUe = false;}
      if(sKbHWDqxMg == true){sKbHWDqxMg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XAVJKYTKZX
{ 
  void rzwOjytRSd()
  { 
      bool nxTqaWWzja = false;
      bool BgaNtIdMGA = false;
      bool okTVhZATuU = false;
      bool aIpFudpcRW = false;
      bool BYbonlyOEU = false;
      bool GDFKqCcxJA = false;
      bool WCEPAspVRP = false;
      bool RAtjzPIehu = false;
      bool blOaOXCeNr = false;
      bool BsTQAyUMou = false;
      bool ubwoCFIVKa = false;
      bool sxPOYjmcAb = false;
      bool pLHZOYfdjB = false;
      bool twpmzzoZXI = false;
      bool OgTmyDdFrP = false;
      bool KrLMEjTWZd = false;
      bool YelJfxHcOY = false;
      bool uMEqNJqUaL = false;
      bool takTpCjchP = false;
      bool fSAsiitKGB = false;
      string RYlRblQghC;
      string JzOCbxueRy;
      string NMrCWCQUqI;
      string SCFDNSlAVi;
      string zUTMmBeibq;
      string EWHtfFfitZ;
      string UwoZiHtKoI;
      string LuJhysrfPU;
      string WgrAEutKXI;
      string mCFuODetcf;
      string HUtSeIMYwm;
      string MATZCmDoUm;
      string MjlgVJpNTt;
      string NyCiNBmZUw;
      string iUOjulhfra;
      string ApYoSWhNxV;
      string SyFBYOykLB;
      string AcTYEqVBli;
      string aKUrtXYMQp;
      string SZbzcjPMLf;
      if(RYlRblQghC == HUtSeIMYwm){nxTqaWWzja = true;}
      else if(HUtSeIMYwm == RYlRblQghC){ubwoCFIVKa = true;}
      if(JzOCbxueRy == MATZCmDoUm){BgaNtIdMGA = true;}
      else if(MATZCmDoUm == JzOCbxueRy){sxPOYjmcAb = true;}
      if(NMrCWCQUqI == MjlgVJpNTt){okTVhZATuU = true;}
      else if(MjlgVJpNTt == NMrCWCQUqI){pLHZOYfdjB = true;}
      if(SCFDNSlAVi == NyCiNBmZUw){aIpFudpcRW = true;}
      else if(NyCiNBmZUw == SCFDNSlAVi){twpmzzoZXI = true;}
      if(zUTMmBeibq == iUOjulhfra){BYbonlyOEU = true;}
      else if(iUOjulhfra == zUTMmBeibq){OgTmyDdFrP = true;}
      if(EWHtfFfitZ == ApYoSWhNxV){GDFKqCcxJA = true;}
      else if(ApYoSWhNxV == EWHtfFfitZ){KrLMEjTWZd = true;}
      if(UwoZiHtKoI == SyFBYOykLB){WCEPAspVRP = true;}
      else if(SyFBYOykLB == UwoZiHtKoI){YelJfxHcOY = true;}
      if(LuJhysrfPU == AcTYEqVBli){RAtjzPIehu = true;}
      if(WgrAEutKXI == aKUrtXYMQp){blOaOXCeNr = true;}
      if(mCFuODetcf == SZbzcjPMLf){BsTQAyUMou = true;}
      while(AcTYEqVBli == LuJhysrfPU){uMEqNJqUaL = true;}
      while(aKUrtXYMQp == aKUrtXYMQp){takTpCjchP = true;}
      while(SZbzcjPMLf == SZbzcjPMLf){fSAsiitKGB = true;}
      if(nxTqaWWzja == true){nxTqaWWzja = false;}
      if(BgaNtIdMGA == true){BgaNtIdMGA = false;}
      if(okTVhZATuU == true){okTVhZATuU = false;}
      if(aIpFudpcRW == true){aIpFudpcRW = false;}
      if(BYbonlyOEU == true){BYbonlyOEU = false;}
      if(GDFKqCcxJA == true){GDFKqCcxJA = false;}
      if(WCEPAspVRP == true){WCEPAspVRP = false;}
      if(RAtjzPIehu == true){RAtjzPIehu = false;}
      if(blOaOXCeNr == true){blOaOXCeNr = false;}
      if(BsTQAyUMou == true){BsTQAyUMou = false;}
      if(ubwoCFIVKa == true){ubwoCFIVKa = false;}
      if(sxPOYjmcAb == true){sxPOYjmcAb = false;}
      if(pLHZOYfdjB == true){pLHZOYfdjB = false;}
      if(twpmzzoZXI == true){twpmzzoZXI = false;}
      if(OgTmyDdFrP == true){OgTmyDdFrP = false;}
      if(KrLMEjTWZd == true){KrLMEjTWZd = false;}
      if(YelJfxHcOY == true){YelJfxHcOY = false;}
      if(uMEqNJqUaL == true){uMEqNJqUaL = false;}
      if(takTpCjchP == true){takTpCjchP = false;}
      if(fSAsiitKGB == true){fSAsiitKGB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYVUTQEEVU
{ 
  void gbWKdxtaUB()
  { 
      bool znlBlnRwBY = false;
      bool EBJxUDPfNL = false;
      bool hZOfSsdmfw = false;
      bool FsRhUQRryK = false;
      bool gPKAAKJbGi = false;
      bool LmpBdYYGhs = false;
      bool JeQFTKibcD = false;
      bool lWhDeSPNeI = false;
      bool jBfwjRCPDu = false;
      bool qKJFACzEgo = false;
      bool agyDxoEmWL = false;
      bool ILaZIHyTVB = false;
      bool HTYgMaNcCc = false;
      bool TLgogCCcyu = false;
      bool NPsrlfiiwr = false;
      bool DeiegHIRqV = false;
      bool bbjtqxdksG = false;
      bool EVVZmraguf = false;
      bool qdgJYocBHY = false;
      bool tklcTleyAo = false;
      string sTPYcbLzjN;
      string DaBeNqLiSZ;
      string sUdcNdNBdu;
      string jIwiAzYYDy;
      string xQRKAsCjlX;
      string TPVdSXplLz;
      string NJUocudSdO;
      string SmeUcbDSbU;
      string bdOFaUlRPb;
      string IlMEjmucgF;
      string OiGWFgjBBq;
      string UXKpXjuONI;
      string IMDBFfZajp;
      string fakWGrXqAt;
      string kjPXHkbWgz;
      string qgOYxBfERY;
      string GJQLKtlnje;
      string MDOSXXxetT;
      string EDtkyzLLYE;
      string LSZamaSDNM;
      if(sTPYcbLzjN == OiGWFgjBBq){znlBlnRwBY = true;}
      else if(OiGWFgjBBq == sTPYcbLzjN){agyDxoEmWL = true;}
      if(DaBeNqLiSZ == UXKpXjuONI){EBJxUDPfNL = true;}
      else if(UXKpXjuONI == DaBeNqLiSZ){ILaZIHyTVB = true;}
      if(sUdcNdNBdu == IMDBFfZajp){hZOfSsdmfw = true;}
      else if(IMDBFfZajp == sUdcNdNBdu){HTYgMaNcCc = true;}
      if(jIwiAzYYDy == fakWGrXqAt){FsRhUQRryK = true;}
      else if(fakWGrXqAt == jIwiAzYYDy){TLgogCCcyu = true;}
      if(xQRKAsCjlX == kjPXHkbWgz){gPKAAKJbGi = true;}
      else if(kjPXHkbWgz == xQRKAsCjlX){NPsrlfiiwr = true;}
      if(TPVdSXplLz == qgOYxBfERY){LmpBdYYGhs = true;}
      else if(qgOYxBfERY == TPVdSXplLz){DeiegHIRqV = true;}
      if(NJUocudSdO == GJQLKtlnje){JeQFTKibcD = true;}
      else if(GJQLKtlnje == NJUocudSdO){bbjtqxdksG = true;}
      if(SmeUcbDSbU == MDOSXXxetT){lWhDeSPNeI = true;}
      if(bdOFaUlRPb == EDtkyzLLYE){jBfwjRCPDu = true;}
      if(IlMEjmucgF == LSZamaSDNM){qKJFACzEgo = true;}
      while(MDOSXXxetT == SmeUcbDSbU){EVVZmraguf = true;}
      while(EDtkyzLLYE == EDtkyzLLYE){qdgJYocBHY = true;}
      while(LSZamaSDNM == LSZamaSDNM){tklcTleyAo = true;}
      if(znlBlnRwBY == true){znlBlnRwBY = false;}
      if(EBJxUDPfNL == true){EBJxUDPfNL = false;}
      if(hZOfSsdmfw == true){hZOfSsdmfw = false;}
      if(FsRhUQRryK == true){FsRhUQRryK = false;}
      if(gPKAAKJbGi == true){gPKAAKJbGi = false;}
      if(LmpBdYYGhs == true){LmpBdYYGhs = false;}
      if(JeQFTKibcD == true){JeQFTKibcD = false;}
      if(lWhDeSPNeI == true){lWhDeSPNeI = false;}
      if(jBfwjRCPDu == true){jBfwjRCPDu = false;}
      if(qKJFACzEgo == true){qKJFACzEgo = false;}
      if(agyDxoEmWL == true){agyDxoEmWL = false;}
      if(ILaZIHyTVB == true){ILaZIHyTVB = false;}
      if(HTYgMaNcCc == true){HTYgMaNcCc = false;}
      if(TLgogCCcyu == true){TLgogCCcyu = false;}
      if(NPsrlfiiwr == true){NPsrlfiiwr = false;}
      if(DeiegHIRqV == true){DeiegHIRqV = false;}
      if(bbjtqxdksG == true){bbjtqxdksG = false;}
      if(EVVZmraguf == true){EVVZmraguf = false;}
      if(qdgJYocBHY == true){qdgJYocBHY = false;}
      if(tklcTleyAo == true){tklcTleyAo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VMUTFXQQXS
{ 
  void TRIODHVSLP()
  { 
      bool efzNjRsVSa = false;
      bool qaMhzSsVhb = false;
      bool RCNHkYKmxx = false;
      bool jrfMQlaRQd = false;
      bool FUrsZzrLqm = false;
      bool EuSocbRqbK = false;
      bool GFXUqzuzRN = false;
      bool raEDWwJThk = false;
      bool gyuJrnZpjn = false;
      bool UipGXzxXCZ = false;
      bool EstdudpOSf = false;
      bool SxJpdHKObC = false;
      bool ZEPdsIkyfX = false;
      bool zlRIfnEQNO = false;
      bool yKXDVWZzbP = false;
      bool ohuzzAcQkm = false;
      bool sritgffBJp = false;
      bool DsANEOfLIV = false;
      bool ikVQiQqSIf = false;
      bool KnfaVFbdWo = false;
      string jzyCmOwbfq;
      string OptcxTjJzg;
      string kSFBRKMegj;
      string XwqPrarkQS;
      string PEYzkHtLoZ;
      string rWTObRtxkc;
      string CRtwSRzdjV;
      string bzrgQfsGQJ;
      string PAoGrAbbna;
      string guzmQyKcfS;
      string HPbSyrdmxu;
      string XngaMCbmDR;
      string pXpIofzFPS;
      string UPZxBAXWIz;
      string WnerCsOYZO;
      string WWYNcjYScR;
      string sYXdZINiYM;
      string dEdDuBryGu;
      string RaeBwypLUR;
      string aEsqGyQARt;
      if(jzyCmOwbfq == HPbSyrdmxu){efzNjRsVSa = true;}
      else if(HPbSyrdmxu == jzyCmOwbfq){EstdudpOSf = true;}
      if(OptcxTjJzg == XngaMCbmDR){qaMhzSsVhb = true;}
      else if(XngaMCbmDR == OptcxTjJzg){SxJpdHKObC = true;}
      if(kSFBRKMegj == pXpIofzFPS){RCNHkYKmxx = true;}
      else if(pXpIofzFPS == kSFBRKMegj){ZEPdsIkyfX = true;}
      if(XwqPrarkQS == UPZxBAXWIz){jrfMQlaRQd = true;}
      else if(UPZxBAXWIz == XwqPrarkQS){zlRIfnEQNO = true;}
      if(PEYzkHtLoZ == WnerCsOYZO){FUrsZzrLqm = true;}
      else if(WnerCsOYZO == PEYzkHtLoZ){yKXDVWZzbP = true;}
      if(rWTObRtxkc == WWYNcjYScR){EuSocbRqbK = true;}
      else if(WWYNcjYScR == rWTObRtxkc){ohuzzAcQkm = true;}
      if(CRtwSRzdjV == sYXdZINiYM){GFXUqzuzRN = true;}
      else if(sYXdZINiYM == CRtwSRzdjV){sritgffBJp = true;}
      if(bzrgQfsGQJ == dEdDuBryGu){raEDWwJThk = true;}
      if(PAoGrAbbna == RaeBwypLUR){gyuJrnZpjn = true;}
      if(guzmQyKcfS == aEsqGyQARt){UipGXzxXCZ = true;}
      while(dEdDuBryGu == bzrgQfsGQJ){DsANEOfLIV = true;}
      while(RaeBwypLUR == RaeBwypLUR){ikVQiQqSIf = true;}
      while(aEsqGyQARt == aEsqGyQARt){KnfaVFbdWo = true;}
      if(efzNjRsVSa == true){efzNjRsVSa = false;}
      if(qaMhzSsVhb == true){qaMhzSsVhb = false;}
      if(RCNHkYKmxx == true){RCNHkYKmxx = false;}
      if(jrfMQlaRQd == true){jrfMQlaRQd = false;}
      if(FUrsZzrLqm == true){FUrsZzrLqm = false;}
      if(EuSocbRqbK == true){EuSocbRqbK = false;}
      if(GFXUqzuzRN == true){GFXUqzuzRN = false;}
      if(raEDWwJThk == true){raEDWwJThk = false;}
      if(gyuJrnZpjn == true){gyuJrnZpjn = false;}
      if(UipGXzxXCZ == true){UipGXzxXCZ = false;}
      if(EstdudpOSf == true){EstdudpOSf = false;}
      if(SxJpdHKObC == true){SxJpdHKObC = false;}
      if(ZEPdsIkyfX == true){ZEPdsIkyfX = false;}
      if(zlRIfnEQNO == true){zlRIfnEQNO = false;}
      if(yKXDVWZzbP == true){yKXDVWZzbP = false;}
      if(ohuzzAcQkm == true){ohuzzAcQkm = false;}
      if(sritgffBJp == true){sritgffBJp = false;}
      if(DsANEOfLIV == true){DsANEOfLIV = false;}
      if(ikVQiQqSIf == true){ikVQiQqSIf = false;}
      if(KnfaVFbdWo == true){KnfaVFbdWo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTUKSKHANF
{ 
  void hsxZTDEGLD()
  { 
      bool mFYrsLEGEr = false;
      bool pNYWFNbVim = false;
      bool XZxKlIVTzW = false;
      bool zPJSlOePZQ = false;
      bool kDEloSucaN = false;
      bool utdNnNIOFj = false;
      bool okGhraDGkp = false;
      bool hLuSCTUKVS = false;
      bool NsrlaFludX = false;
      bool GQJoazxWsN = false;
      bool OoqkejyKLU = false;
      bool rxslWwsUGm = false;
      bool oIbMjRBGqC = false;
      bool WyRHEYBHHq = false;
      bool HajIfJXXSe = false;
      bool GbQGYGMdAN = false;
      bool hrSIytfkhy = false;
      bool tlNOeOYSga = false;
      bool sdmMwtgKhx = false;
      bool MWGsIPHbKl = false;
      string OcenCSAHwZ;
      string ZWQcekkVdV;
      string GwYxgQTrQt;
      string NWbbkTgLUT;
      string JBDNgOAUDg;
      string MDmhbRDhHl;
      string zHpCLDtnrL;
      string DYAJLErKQS;
      string PzojgJitAS;
      string PzEhUBKBBc;
      string TLbrdmCdVW;
      string YsQoWzSGUB;
      string UAnYuDUSnK;
      string tqJmyDWwGt;
      string HEXdtWiPKV;
      string hEgzISXDwZ;
      string SjoLchicpS;
      string bWzatPcKeY;
      string UEHSboKJee;
      string fTAfaXPMBM;
      if(OcenCSAHwZ == TLbrdmCdVW){mFYrsLEGEr = true;}
      else if(TLbrdmCdVW == OcenCSAHwZ){OoqkejyKLU = true;}
      if(ZWQcekkVdV == YsQoWzSGUB){pNYWFNbVim = true;}
      else if(YsQoWzSGUB == ZWQcekkVdV){rxslWwsUGm = true;}
      if(GwYxgQTrQt == UAnYuDUSnK){XZxKlIVTzW = true;}
      else if(UAnYuDUSnK == GwYxgQTrQt){oIbMjRBGqC = true;}
      if(NWbbkTgLUT == tqJmyDWwGt){zPJSlOePZQ = true;}
      else if(tqJmyDWwGt == NWbbkTgLUT){WyRHEYBHHq = true;}
      if(JBDNgOAUDg == HEXdtWiPKV){kDEloSucaN = true;}
      else if(HEXdtWiPKV == JBDNgOAUDg){HajIfJXXSe = true;}
      if(MDmhbRDhHl == hEgzISXDwZ){utdNnNIOFj = true;}
      else if(hEgzISXDwZ == MDmhbRDhHl){GbQGYGMdAN = true;}
      if(zHpCLDtnrL == SjoLchicpS){okGhraDGkp = true;}
      else if(SjoLchicpS == zHpCLDtnrL){hrSIytfkhy = true;}
      if(DYAJLErKQS == bWzatPcKeY){hLuSCTUKVS = true;}
      if(PzojgJitAS == UEHSboKJee){NsrlaFludX = true;}
      if(PzEhUBKBBc == fTAfaXPMBM){GQJoazxWsN = true;}
      while(bWzatPcKeY == DYAJLErKQS){tlNOeOYSga = true;}
      while(UEHSboKJee == UEHSboKJee){sdmMwtgKhx = true;}
      while(fTAfaXPMBM == fTAfaXPMBM){MWGsIPHbKl = true;}
      if(mFYrsLEGEr == true){mFYrsLEGEr = false;}
      if(pNYWFNbVim == true){pNYWFNbVim = false;}
      if(XZxKlIVTzW == true){XZxKlIVTzW = false;}
      if(zPJSlOePZQ == true){zPJSlOePZQ = false;}
      if(kDEloSucaN == true){kDEloSucaN = false;}
      if(utdNnNIOFj == true){utdNnNIOFj = false;}
      if(okGhraDGkp == true){okGhraDGkp = false;}
      if(hLuSCTUKVS == true){hLuSCTUKVS = false;}
      if(NsrlaFludX == true){NsrlaFludX = false;}
      if(GQJoazxWsN == true){GQJoazxWsN = false;}
      if(OoqkejyKLU == true){OoqkejyKLU = false;}
      if(rxslWwsUGm == true){rxslWwsUGm = false;}
      if(oIbMjRBGqC == true){oIbMjRBGqC = false;}
      if(WyRHEYBHHq == true){WyRHEYBHHq = false;}
      if(HajIfJXXSe == true){HajIfJXXSe = false;}
      if(GbQGYGMdAN == true){GbQGYGMdAN = false;}
      if(hrSIytfkhy == true){hrSIytfkhy = false;}
      if(tlNOeOYSga == true){tlNOeOYSga = false;}
      if(sdmMwtgKhx == true){sdmMwtgKhx = false;}
      if(MWGsIPHbKl == true){MWGsIPHbKl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVKTWJUCMS
{ 
  void YMUnAnTCZT()
  { 
      bool qCCZaOqQhy = false;
      bool TjgydUGFkM = false;
      bool PmfoztkotR = false;
      bool ZoXDKtrJBg = false;
      bool mMrecruZqq = false;
      bool xDTtcDVMaf = false;
      bool cCWPYeLdnj = false;
      bool bwEDYCuBLG = false;
      bool yKxCUVVdaG = false;
      bool XfiUDkobGy = false;
      bool fRlHOAzPUZ = false;
      bool IUAThREUuC = false;
      bool JhCgLwNizn = false;
      bool NStNagYpnT = false;
      bool WFIAxDeOmk = false;
      bool gUgDoyOEwR = false;
      bool mPQgMpZmsA = false;
      bool sOfaeEZCjH = false;
      bool RyuNGrlqYb = false;
      bool STsVgHnanH = false;
      string XuwTnoxEIz;
      string iizujSOfZx;
      string yVGEQjrjMz;
      string JIQugjZqYY;
      string UDPIiLyZGd;
      string WkJdUBnqDE;
      string wMqJoaRENA;
      string rXHBctGxUE;
      string kSdibYzmZf;
      string uimUbHLFTI;
      string stLFkzdHBa;
      string tqVySdiIhQ;
      string aeehFJjlZU;
      string hBdLLqGYxb;
      string tqkzkEMoBx;
      string YDWDhNOdza;
      string PqhgrsMKma;
      string WKLGVitewB;
      string xtjbuedZdx;
      string bcYVLDJEHr;
      if(XuwTnoxEIz == stLFkzdHBa){qCCZaOqQhy = true;}
      else if(stLFkzdHBa == XuwTnoxEIz){fRlHOAzPUZ = true;}
      if(iizujSOfZx == tqVySdiIhQ){TjgydUGFkM = true;}
      else if(tqVySdiIhQ == iizujSOfZx){IUAThREUuC = true;}
      if(yVGEQjrjMz == aeehFJjlZU){PmfoztkotR = true;}
      else if(aeehFJjlZU == yVGEQjrjMz){JhCgLwNizn = true;}
      if(JIQugjZqYY == hBdLLqGYxb){ZoXDKtrJBg = true;}
      else if(hBdLLqGYxb == JIQugjZqYY){NStNagYpnT = true;}
      if(UDPIiLyZGd == tqkzkEMoBx){mMrecruZqq = true;}
      else if(tqkzkEMoBx == UDPIiLyZGd){WFIAxDeOmk = true;}
      if(WkJdUBnqDE == YDWDhNOdza){xDTtcDVMaf = true;}
      else if(YDWDhNOdza == WkJdUBnqDE){gUgDoyOEwR = true;}
      if(wMqJoaRENA == PqhgrsMKma){cCWPYeLdnj = true;}
      else if(PqhgrsMKma == wMqJoaRENA){mPQgMpZmsA = true;}
      if(rXHBctGxUE == WKLGVitewB){bwEDYCuBLG = true;}
      if(kSdibYzmZf == xtjbuedZdx){yKxCUVVdaG = true;}
      if(uimUbHLFTI == bcYVLDJEHr){XfiUDkobGy = true;}
      while(WKLGVitewB == rXHBctGxUE){sOfaeEZCjH = true;}
      while(xtjbuedZdx == xtjbuedZdx){RyuNGrlqYb = true;}
      while(bcYVLDJEHr == bcYVLDJEHr){STsVgHnanH = true;}
      if(qCCZaOqQhy == true){qCCZaOqQhy = false;}
      if(TjgydUGFkM == true){TjgydUGFkM = false;}
      if(PmfoztkotR == true){PmfoztkotR = false;}
      if(ZoXDKtrJBg == true){ZoXDKtrJBg = false;}
      if(mMrecruZqq == true){mMrecruZqq = false;}
      if(xDTtcDVMaf == true){xDTtcDVMaf = false;}
      if(cCWPYeLdnj == true){cCWPYeLdnj = false;}
      if(bwEDYCuBLG == true){bwEDYCuBLG = false;}
      if(yKxCUVVdaG == true){yKxCUVVdaG = false;}
      if(XfiUDkobGy == true){XfiUDkobGy = false;}
      if(fRlHOAzPUZ == true){fRlHOAzPUZ = false;}
      if(IUAThREUuC == true){IUAThREUuC = false;}
      if(JhCgLwNizn == true){JhCgLwNizn = false;}
      if(NStNagYpnT == true){NStNagYpnT = false;}
      if(WFIAxDeOmk == true){WFIAxDeOmk = false;}
      if(gUgDoyOEwR == true){gUgDoyOEwR = false;}
      if(mPQgMpZmsA == true){mPQgMpZmsA = false;}
      if(sOfaeEZCjH == true){sOfaeEZCjH = false;}
      if(RyuNGrlqYb == true){RyuNGrlqYb = false;}
      if(STsVgHnanH == true){STsVgHnanH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZFXLLGTGK
{ 
  void zDHxkhUeVG()
  { 
      bool zaxtpWFsVx = false;
      bool oUyrYXAusc = false;
      bool pwsQKBENKp = false;
      bool faqQcDXpGy = false;
      bool UwPJjhHAuQ = false;
      bool EgkhmDhgjo = false;
      bool SqieQOcgPV = false;
      bool AKotHsgjfb = false;
      bool tESskyoJdZ = false;
      bool VpFRfcNjrV = false;
      bool EZjZQtrqZs = false;
      bool WyAIuOYotR = false;
      bool YTDpAJEWOd = false;
      bool fwqKWTTrcq = false;
      bool GyijCXoxWQ = false;
      bool EYoZwkWtZG = false;
      bool oUbwNZGpka = false;
      bool ufLDLakSmc = false;
      bool UHAxZGGRNl = false;
      bool xYSWBkVlWc = false;
      string QIrXNMCdAq;
      string gcSWjATnuL;
      string AtQcDIPxml;
      string kreQuIEQAy;
      string lmmJbqrWEF;
      string ERiegWqOUE;
      string xEpNFnyBba;
      string uDnwYMHGAL;
      string QrrhhTIziY;
      string RouuBhwYDm;
      string spudJAcmGT;
      string OjNInEMHfl;
      string fySDJFHrtq;
      string PhDNSaxOYg;
      string pVsPJgamHx;
      string UorRHtXrUD;
      string rkrOEfgAoM;
      string GxizuJFCsb;
      string eUjxVapkGY;
      string CFsUnFcdLc;
      if(QIrXNMCdAq == spudJAcmGT){zaxtpWFsVx = true;}
      else if(spudJAcmGT == QIrXNMCdAq){EZjZQtrqZs = true;}
      if(gcSWjATnuL == OjNInEMHfl){oUyrYXAusc = true;}
      else if(OjNInEMHfl == gcSWjATnuL){WyAIuOYotR = true;}
      if(AtQcDIPxml == fySDJFHrtq){pwsQKBENKp = true;}
      else if(fySDJFHrtq == AtQcDIPxml){YTDpAJEWOd = true;}
      if(kreQuIEQAy == PhDNSaxOYg){faqQcDXpGy = true;}
      else if(PhDNSaxOYg == kreQuIEQAy){fwqKWTTrcq = true;}
      if(lmmJbqrWEF == pVsPJgamHx){UwPJjhHAuQ = true;}
      else if(pVsPJgamHx == lmmJbqrWEF){GyijCXoxWQ = true;}
      if(ERiegWqOUE == UorRHtXrUD){EgkhmDhgjo = true;}
      else if(UorRHtXrUD == ERiegWqOUE){EYoZwkWtZG = true;}
      if(xEpNFnyBba == rkrOEfgAoM){SqieQOcgPV = true;}
      else if(rkrOEfgAoM == xEpNFnyBba){oUbwNZGpka = true;}
      if(uDnwYMHGAL == GxizuJFCsb){AKotHsgjfb = true;}
      if(QrrhhTIziY == eUjxVapkGY){tESskyoJdZ = true;}
      if(RouuBhwYDm == CFsUnFcdLc){VpFRfcNjrV = true;}
      while(GxizuJFCsb == uDnwYMHGAL){ufLDLakSmc = true;}
      while(eUjxVapkGY == eUjxVapkGY){UHAxZGGRNl = true;}
      while(CFsUnFcdLc == CFsUnFcdLc){xYSWBkVlWc = true;}
      if(zaxtpWFsVx == true){zaxtpWFsVx = false;}
      if(oUyrYXAusc == true){oUyrYXAusc = false;}
      if(pwsQKBENKp == true){pwsQKBENKp = false;}
      if(faqQcDXpGy == true){faqQcDXpGy = false;}
      if(UwPJjhHAuQ == true){UwPJjhHAuQ = false;}
      if(EgkhmDhgjo == true){EgkhmDhgjo = false;}
      if(SqieQOcgPV == true){SqieQOcgPV = false;}
      if(AKotHsgjfb == true){AKotHsgjfb = false;}
      if(tESskyoJdZ == true){tESskyoJdZ = false;}
      if(VpFRfcNjrV == true){VpFRfcNjrV = false;}
      if(EZjZQtrqZs == true){EZjZQtrqZs = false;}
      if(WyAIuOYotR == true){WyAIuOYotR = false;}
      if(YTDpAJEWOd == true){YTDpAJEWOd = false;}
      if(fwqKWTTrcq == true){fwqKWTTrcq = false;}
      if(GyijCXoxWQ == true){GyijCXoxWQ = false;}
      if(EYoZwkWtZG == true){EYoZwkWtZG = false;}
      if(oUbwNZGpka == true){oUbwNZGpka = false;}
      if(ufLDLakSmc == true){ufLDLakSmc = false;}
      if(UHAxZGGRNl == true){UHAxZGGRNl = false;}
      if(xYSWBkVlWc == true){xYSWBkVlWc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGLDKFPYKS
{ 
  void GEnOaGbDTs()
  { 
      bool EIcNdMmasR = false;
      bool RXwRiJmCDz = false;
      bool cCAQQVThWU = false;
      bool pntSwsHrjR = false;
      bool nZGrWalYZM = false;
      bool LUntnCHLwH = false;
      bool rFEYbccdVp = false;
      bool CtRlKDuIto = false;
      bool iuHJJUAzet = false;
      bool luucYiUhPs = false;
      bool yIDjKQCCjj = false;
      bool GyRHYxytOG = false;
      bool cczaEGzoMa = false;
      bool iNsAqaqWyr = false;
      bool RxPtmndnEa = false;
      bool kZSIQUJbfD = false;
      bool RNoJBsFRPx = false;
      bool FauWoeNEmQ = false;
      bool cKkloItjjV = false;
      bool QPquaEIFst = false;
      string ZhtzVUGihS;
      string fETXxmMCLB;
      string bXkRMNTuwq;
      string mXoHwSxPMH;
      string EEWCqTgoHu;
      string LRTfFBxblH;
      string BKmpeHOLbe;
      string pxoEwXBiZr;
      string genAeUEICu;
      string VUcFGtQfWj;
      string EUNcFNcPjg;
      string zOBtaWVlKK;
      string DFJfIUTjyC;
      string GVLpnLQKtR;
      string qoYUuHTidi;
      string XeULfyLgTk;
      string tsQgadCLGP;
      string FKqsSNfnjB;
      string BjGOdbAzKo;
      string ziqJWyXqsR;
      if(ZhtzVUGihS == EUNcFNcPjg){EIcNdMmasR = true;}
      else if(EUNcFNcPjg == ZhtzVUGihS){yIDjKQCCjj = true;}
      if(fETXxmMCLB == zOBtaWVlKK){RXwRiJmCDz = true;}
      else if(zOBtaWVlKK == fETXxmMCLB){GyRHYxytOG = true;}
      if(bXkRMNTuwq == DFJfIUTjyC){cCAQQVThWU = true;}
      else if(DFJfIUTjyC == bXkRMNTuwq){cczaEGzoMa = true;}
      if(mXoHwSxPMH == GVLpnLQKtR){pntSwsHrjR = true;}
      else if(GVLpnLQKtR == mXoHwSxPMH){iNsAqaqWyr = true;}
      if(EEWCqTgoHu == qoYUuHTidi){nZGrWalYZM = true;}
      else if(qoYUuHTidi == EEWCqTgoHu){RxPtmndnEa = true;}
      if(LRTfFBxblH == XeULfyLgTk){LUntnCHLwH = true;}
      else if(XeULfyLgTk == LRTfFBxblH){kZSIQUJbfD = true;}
      if(BKmpeHOLbe == tsQgadCLGP){rFEYbccdVp = true;}
      else if(tsQgadCLGP == BKmpeHOLbe){RNoJBsFRPx = true;}
      if(pxoEwXBiZr == FKqsSNfnjB){CtRlKDuIto = true;}
      if(genAeUEICu == BjGOdbAzKo){iuHJJUAzet = true;}
      if(VUcFGtQfWj == ziqJWyXqsR){luucYiUhPs = true;}
      while(FKqsSNfnjB == pxoEwXBiZr){FauWoeNEmQ = true;}
      while(BjGOdbAzKo == BjGOdbAzKo){cKkloItjjV = true;}
      while(ziqJWyXqsR == ziqJWyXqsR){QPquaEIFst = true;}
      if(EIcNdMmasR == true){EIcNdMmasR = false;}
      if(RXwRiJmCDz == true){RXwRiJmCDz = false;}
      if(cCAQQVThWU == true){cCAQQVThWU = false;}
      if(pntSwsHrjR == true){pntSwsHrjR = false;}
      if(nZGrWalYZM == true){nZGrWalYZM = false;}
      if(LUntnCHLwH == true){LUntnCHLwH = false;}
      if(rFEYbccdVp == true){rFEYbccdVp = false;}
      if(CtRlKDuIto == true){CtRlKDuIto = false;}
      if(iuHJJUAzet == true){iuHJJUAzet = false;}
      if(luucYiUhPs == true){luucYiUhPs = false;}
      if(yIDjKQCCjj == true){yIDjKQCCjj = false;}
      if(GyRHYxytOG == true){GyRHYxytOG = false;}
      if(cczaEGzoMa == true){cczaEGzoMa = false;}
      if(iNsAqaqWyr == true){iNsAqaqWyr = false;}
      if(RxPtmndnEa == true){RxPtmndnEa = false;}
      if(kZSIQUJbfD == true){kZSIQUJbfD = false;}
      if(RNoJBsFRPx == true){RNoJBsFRPx = false;}
      if(FauWoeNEmQ == true){FauWoeNEmQ = false;}
      if(cKkloItjjV == true){cKkloItjjV = false;}
      if(QPquaEIFst == true){QPquaEIFst = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCHYJHCIOL
{ 
  void JxzlnMoKhi()
  { 
      bool sOLeDRREHP = false;
      bool fmtkHLOJjb = false;
      bool FbuUhKUVwu = false;
      bool YDucnRghyg = false;
      bool zTFAxFeUlb = false;
      bool SVOVAQTqwr = false;
      bool xwIMpcqRxp = false;
      bool egLDclWuWc = false;
      bool eAiTcDoYbW = false;
      bool yokFiCKsJU = false;
      bool NNWwxkJLsO = false;
      bool sYTSNxNoim = false;
      bool mRoZrouGTZ = false;
      bool adkCPRcmWq = false;
      bool scfNdZVRrl = false;
      bool oVJWguYwEH = false;
      bool pDrSmOmQDu = false;
      bool TaRrsKlawS = false;
      bool TcOgkEUNVT = false;
      bool sghOApkMZO = false;
      string qAClXkamEX;
      string oMgyPDmVae;
      string tUqDtfxWId;
      string cDTKAeWOwM;
      string uMpTCMowRc;
      string fVMKZWJyrq;
      string mDeZulsWyj;
      string fYYNigdWBg;
      string qAFfyHpIkd;
      string UXVFZqhQYQ;
      string TSygwGwzas;
      string rmxLzlyzbn;
      string ujlUOHCTnr;
      string zNxkMYCXiq;
      string KphqkhaKFm;
      string shokUigcRn;
      string DcKiseoLya;
      string jaPjcECtig;
      string grNBzQYMQd;
      string rYFtmheyyG;
      if(qAClXkamEX == TSygwGwzas){sOLeDRREHP = true;}
      else if(TSygwGwzas == qAClXkamEX){NNWwxkJLsO = true;}
      if(oMgyPDmVae == rmxLzlyzbn){fmtkHLOJjb = true;}
      else if(rmxLzlyzbn == oMgyPDmVae){sYTSNxNoim = true;}
      if(tUqDtfxWId == ujlUOHCTnr){FbuUhKUVwu = true;}
      else if(ujlUOHCTnr == tUqDtfxWId){mRoZrouGTZ = true;}
      if(cDTKAeWOwM == zNxkMYCXiq){YDucnRghyg = true;}
      else if(zNxkMYCXiq == cDTKAeWOwM){adkCPRcmWq = true;}
      if(uMpTCMowRc == KphqkhaKFm){zTFAxFeUlb = true;}
      else if(KphqkhaKFm == uMpTCMowRc){scfNdZVRrl = true;}
      if(fVMKZWJyrq == shokUigcRn){SVOVAQTqwr = true;}
      else if(shokUigcRn == fVMKZWJyrq){oVJWguYwEH = true;}
      if(mDeZulsWyj == DcKiseoLya){xwIMpcqRxp = true;}
      else if(DcKiseoLya == mDeZulsWyj){pDrSmOmQDu = true;}
      if(fYYNigdWBg == jaPjcECtig){egLDclWuWc = true;}
      if(qAFfyHpIkd == grNBzQYMQd){eAiTcDoYbW = true;}
      if(UXVFZqhQYQ == rYFtmheyyG){yokFiCKsJU = true;}
      while(jaPjcECtig == fYYNigdWBg){TaRrsKlawS = true;}
      while(grNBzQYMQd == grNBzQYMQd){TcOgkEUNVT = true;}
      while(rYFtmheyyG == rYFtmheyyG){sghOApkMZO = true;}
      if(sOLeDRREHP == true){sOLeDRREHP = false;}
      if(fmtkHLOJjb == true){fmtkHLOJjb = false;}
      if(FbuUhKUVwu == true){FbuUhKUVwu = false;}
      if(YDucnRghyg == true){YDucnRghyg = false;}
      if(zTFAxFeUlb == true){zTFAxFeUlb = false;}
      if(SVOVAQTqwr == true){SVOVAQTqwr = false;}
      if(xwIMpcqRxp == true){xwIMpcqRxp = false;}
      if(egLDclWuWc == true){egLDclWuWc = false;}
      if(eAiTcDoYbW == true){eAiTcDoYbW = false;}
      if(yokFiCKsJU == true){yokFiCKsJU = false;}
      if(NNWwxkJLsO == true){NNWwxkJLsO = false;}
      if(sYTSNxNoim == true){sYTSNxNoim = false;}
      if(mRoZrouGTZ == true){mRoZrouGTZ = false;}
      if(adkCPRcmWq == true){adkCPRcmWq = false;}
      if(scfNdZVRrl == true){scfNdZVRrl = false;}
      if(oVJWguYwEH == true){oVJWguYwEH = false;}
      if(pDrSmOmQDu == true){pDrSmOmQDu = false;}
      if(TaRrsKlawS == true){TaRrsKlawS = false;}
      if(TcOgkEUNVT == true){TcOgkEUNVT = false;}
      if(sghOApkMZO == true){sghOApkMZO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYGLVJRCCO
{ 
  void qLRPzZFgzp()
  { 
      bool bZaaZtaDer = false;
      bool GJjNXnsUkk = false;
      bool TyJmlgTska = false;
      bool BExAKbMDSd = false;
      bool boWRdkyfyj = false;
      bool rycccdQmos = false;
      bool ZgREpCLjCu = false;
      bool apCHJdbqIA = false;
      bool hnuBhCaUWg = false;
      bool KYOZDuWRab = false;
      bool YNdCICwVTy = false;
      bool CZenLkkQVn = false;
      bool bqNUkBabDO = false;
      bool HJQgaTKsrf = false;
      bool GEAXdjtZNR = false;
      bool JGwmAhAIQG = false;
      bool aTSEqsIyMq = false;
      bool aqXphWpopA = false;
      bool HBOkEBNdfs = false;
      bool SCclEllwgk = false;
      string WNJysDhnPJ;
      string OsGGNlFDHY;
      string SZLippVPNr;
      string UgqHYZInKD;
      string fZuCxQkTEy;
      string eCBfYxCaHD;
      string hRZWohBygm;
      string cRrErreIkZ;
      string ECKPNSeLib;
      string WhfGUNAXNP;
      string PllRUNJxnf;
      string StohyfGKJV;
      string CpPFQuklie;
      string rGtVJRPsuz;
      string JhXCIcsyHo;
      string GpNrMYWgAZ;
      string bXOInLASXg;
      string PMPJMUSMwm;
      string CmdsXCrCJk;
      string uisVXlTOOw;
      if(WNJysDhnPJ == PllRUNJxnf){bZaaZtaDer = true;}
      else if(PllRUNJxnf == WNJysDhnPJ){YNdCICwVTy = true;}
      if(OsGGNlFDHY == StohyfGKJV){GJjNXnsUkk = true;}
      else if(StohyfGKJV == OsGGNlFDHY){CZenLkkQVn = true;}
      if(SZLippVPNr == CpPFQuklie){TyJmlgTska = true;}
      else if(CpPFQuklie == SZLippVPNr){bqNUkBabDO = true;}
      if(UgqHYZInKD == rGtVJRPsuz){BExAKbMDSd = true;}
      else if(rGtVJRPsuz == UgqHYZInKD){HJQgaTKsrf = true;}
      if(fZuCxQkTEy == JhXCIcsyHo){boWRdkyfyj = true;}
      else if(JhXCIcsyHo == fZuCxQkTEy){GEAXdjtZNR = true;}
      if(eCBfYxCaHD == GpNrMYWgAZ){rycccdQmos = true;}
      else if(GpNrMYWgAZ == eCBfYxCaHD){JGwmAhAIQG = true;}
      if(hRZWohBygm == bXOInLASXg){ZgREpCLjCu = true;}
      else if(bXOInLASXg == hRZWohBygm){aTSEqsIyMq = true;}
      if(cRrErreIkZ == PMPJMUSMwm){apCHJdbqIA = true;}
      if(ECKPNSeLib == CmdsXCrCJk){hnuBhCaUWg = true;}
      if(WhfGUNAXNP == uisVXlTOOw){KYOZDuWRab = true;}
      while(PMPJMUSMwm == cRrErreIkZ){aqXphWpopA = true;}
      while(CmdsXCrCJk == CmdsXCrCJk){HBOkEBNdfs = true;}
      while(uisVXlTOOw == uisVXlTOOw){SCclEllwgk = true;}
      if(bZaaZtaDer == true){bZaaZtaDer = false;}
      if(GJjNXnsUkk == true){GJjNXnsUkk = false;}
      if(TyJmlgTska == true){TyJmlgTska = false;}
      if(BExAKbMDSd == true){BExAKbMDSd = false;}
      if(boWRdkyfyj == true){boWRdkyfyj = false;}
      if(rycccdQmos == true){rycccdQmos = false;}
      if(ZgREpCLjCu == true){ZgREpCLjCu = false;}
      if(apCHJdbqIA == true){apCHJdbqIA = false;}
      if(hnuBhCaUWg == true){hnuBhCaUWg = false;}
      if(KYOZDuWRab == true){KYOZDuWRab = false;}
      if(YNdCICwVTy == true){YNdCICwVTy = false;}
      if(CZenLkkQVn == true){CZenLkkQVn = false;}
      if(bqNUkBabDO == true){bqNUkBabDO = false;}
      if(HJQgaTKsrf == true){HJQgaTKsrf = false;}
      if(GEAXdjtZNR == true){GEAXdjtZNR = false;}
      if(JGwmAhAIQG == true){JGwmAhAIQG = false;}
      if(aTSEqsIyMq == true){aTSEqsIyMq = false;}
      if(aqXphWpopA == true){aqXphWpopA = false;}
      if(HBOkEBNdfs == true){HBOkEBNdfs = false;}
      if(SCclEllwgk == true){SCclEllwgk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQMBJBXISR
{ 
  void ksDmqGsBaS()
  { 
      bool rjZtXstnuZ = false;
      bool lLyhoVVXEK = false;
      bool YXsMeVMBwG = false;
      bool mDCopbsZTp = false;
      bool hfNbyNwbqf = false;
      bool LYKWKUpMPB = false;
      bool fsrolhIIqN = false;
      bool cuDObrJROQ = false;
      bool ZkKPuNsfeV = false;
      bool lfKSJomYoP = false;
      bool EnjcDPVwtR = false;
      bool KXyzauibsY = false;
      bool occVbwjjEm = false;
      bool FkcyLlAgMe = false;
      bool rwlMKNgLqO = false;
      bool FKeQabKOBG = false;
      bool elqHMZuzmo = false;
      bool tCPOfrpQKN = false;
      bool OYrpgtFLXj = false;
      bool blfFzGFdzj = false;
      string skyOtWdjDb;
      string LIemVlMQAU;
      string fNXaJwwhuw;
      string jHsIIMJNXx;
      string IhgkJqXEhU;
      string bDzAsfMXEy;
      string auoHqEPVeI;
      string cysDMyflQR;
      string XrzZTgHrPc;
      string AlJYWMrZsF;
      string bCZYrdKunt;
      string zZGlZhwPmK;
      string wWFCIqoTfz;
      string GGsLoVRZhp;
      string WLDVcZeWyn;
      string PcliJFwXQB;
      string npPnnsguxE;
      string QWhxmjSjYi;
      string LSUrjcUJBj;
      string ZtJfBgwPgi;
      if(skyOtWdjDb == bCZYrdKunt){rjZtXstnuZ = true;}
      else if(bCZYrdKunt == skyOtWdjDb){EnjcDPVwtR = true;}
      if(LIemVlMQAU == zZGlZhwPmK){lLyhoVVXEK = true;}
      else if(zZGlZhwPmK == LIemVlMQAU){KXyzauibsY = true;}
      if(fNXaJwwhuw == wWFCIqoTfz){YXsMeVMBwG = true;}
      else if(wWFCIqoTfz == fNXaJwwhuw){occVbwjjEm = true;}
      if(jHsIIMJNXx == GGsLoVRZhp){mDCopbsZTp = true;}
      else if(GGsLoVRZhp == jHsIIMJNXx){FkcyLlAgMe = true;}
      if(IhgkJqXEhU == WLDVcZeWyn){hfNbyNwbqf = true;}
      else if(WLDVcZeWyn == IhgkJqXEhU){rwlMKNgLqO = true;}
      if(bDzAsfMXEy == PcliJFwXQB){LYKWKUpMPB = true;}
      else if(PcliJFwXQB == bDzAsfMXEy){FKeQabKOBG = true;}
      if(auoHqEPVeI == npPnnsguxE){fsrolhIIqN = true;}
      else if(npPnnsguxE == auoHqEPVeI){elqHMZuzmo = true;}
      if(cysDMyflQR == QWhxmjSjYi){cuDObrJROQ = true;}
      if(XrzZTgHrPc == LSUrjcUJBj){ZkKPuNsfeV = true;}
      if(AlJYWMrZsF == ZtJfBgwPgi){lfKSJomYoP = true;}
      while(QWhxmjSjYi == cysDMyflQR){tCPOfrpQKN = true;}
      while(LSUrjcUJBj == LSUrjcUJBj){OYrpgtFLXj = true;}
      while(ZtJfBgwPgi == ZtJfBgwPgi){blfFzGFdzj = true;}
      if(rjZtXstnuZ == true){rjZtXstnuZ = false;}
      if(lLyhoVVXEK == true){lLyhoVVXEK = false;}
      if(YXsMeVMBwG == true){YXsMeVMBwG = false;}
      if(mDCopbsZTp == true){mDCopbsZTp = false;}
      if(hfNbyNwbqf == true){hfNbyNwbqf = false;}
      if(LYKWKUpMPB == true){LYKWKUpMPB = false;}
      if(fsrolhIIqN == true){fsrolhIIqN = false;}
      if(cuDObrJROQ == true){cuDObrJROQ = false;}
      if(ZkKPuNsfeV == true){ZkKPuNsfeV = false;}
      if(lfKSJomYoP == true){lfKSJomYoP = false;}
      if(EnjcDPVwtR == true){EnjcDPVwtR = false;}
      if(KXyzauibsY == true){KXyzauibsY = false;}
      if(occVbwjjEm == true){occVbwjjEm = false;}
      if(FkcyLlAgMe == true){FkcyLlAgMe = false;}
      if(rwlMKNgLqO == true){rwlMKNgLqO = false;}
      if(FKeQabKOBG == true){FKeQabKOBG = false;}
      if(elqHMZuzmo == true){elqHMZuzmo = false;}
      if(tCPOfrpQKN == true){tCPOfrpQKN = false;}
      if(OYrpgtFLXj == true){OYrpgtFLXj = false;}
      if(blfFzGFdzj == true){blfFzGFdzj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NIMVYGEHES
{ 
  void JquZipPhwQ()
  { 
      bool HhDEwarpxR = false;
      bool JUFBWjkhjn = false;
      bool WNnFNQGTrE = false;
      bool TbWpRzcDqD = false;
      bool hdROQXSatb = false;
      bool EpLjlttyqf = false;
      bool TXysxhyOiX = false;
      bool HhqfFrwZoo = false;
      bool yfYPzdPlDX = false;
      bool FdMKjJfXQi = false;
      bool YDqWUWzeds = false;
      bool yTJBhmzisS = false;
      bool RLLKRcUfww = false;
      bool MXIGPunBuc = false;
      bool ekHKZlUKcw = false;
      bool KxexQNrfFq = false;
      bool BSihfaKDkl = false;
      bool zxmPngEAkf = false;
      bool IKDAkPrKoC = false;
      bool CIwDbLCZdz = false;
      string JjyzMBpZTd;
      string jBDWRBVqcL;
      string GJWFmqCMBc;
      string EKDQKiFhwB;
      string ZMRuUOjSVm;
      string THVoLzMsLV;
      string zdYpZZylMh;
      string wmtaksqbjY;
      string GiqOJwnOEK;
      string VLWaCwnbUu;
      string QxGmpgNtDS;
      string IkJmPQlKgc;
      string kigBLkPTYn;
      string EPHoHIbDXc;
      string isKlCkCiKk;
      string JdtqJhPEbF;
      string QsVONrcTeG;
      string nilEtrXuzZ;
      string hgIneZUPfZ;
      string sXbRLoXwXJ;
      if(JjyzMBpZTd == QxGmpgNtDS){HhDEwarpxR = true;}
      else if(QxGmpgNtDS == JjyzMBpZTd){YDqWUWzeds = true;}
      if(jBDWRBVqcL == IkJmPQlKgc){JUFBWjkhjn = true;}
      else if(IkJmPQlKgc == jBDWRBVqcL){yTJBhmzisS = true;}
      if(GJWFmqCMBc == kigBLkPTYn){WNnFNQGTrE = true;}
      else if(kigBLkPTYn == GJWFmqCMBc){RLLKRcUfww = true;}
      if(EKDQKiFhwB == EPHoHIbDXc){TbWpRzcDqD = true;}
      else if(EPHoHIbDXc == EKDQKiFhwB){MXIGPunBuc = true;}
      if(ZMRuUOjSVm == isKlCkCiKk){hdROQXSatb = true;}
      else if(isKlCkCiKk == ZMRuUOjSVm){ekHKZlUKcw = true;}
      if(THVoLzMsLV == JdtqJhPEbF){EpLjlttyqf = true;}
      else if(JdtqJhPEbF == THVoLzMsLV){KxexQNrfFq = true;}
      if(zdYpZZylMh == QsVONrcTeG){TXysxhyOiX = true;}
      else if(QsVONrcTeG == zdYpZZylMh){BSihfaKDkl = true;}
      if(wmtaksqbjY == nilEtrXuzZ){HhqfFrwZoo = true;}
      if(GiqOJwnOEK == hgIneZUPfZ){yfYPzdPlDX = true;}
      if(VLWaCwnbUu == sXbRLoXwXJ){FdMKjJfXQi = true;}
      while(nilEtrXuzZ == wmtaksqbjY){zxmPngEAkf = true;}
      while(hgIneZUPfZ == hgIneZUPfZ){IKDAkPrKoC = true;}
      while(sXbRLoXwXJ == sXbRLoXwXJ){CIwDbLCZdz = true;}
      if(HhDEwarpxR == true){HhDEwarpxR = false;}
      if(JUFBWjkhjn == true){JUFBWjkhjn = false;}
      if(WNnFNQGTrE == true){WNnFNQGTrE = false;}
      if(TbWpRzcDqD == true){TbWpRzcDqD = false;}
      if(hdROQXSatb == true){hdROQXSatb = false;}
      if(EpLjlttyqf == true){EpLjlttyqf = false;}
      if(TXysxhyOiX == true){TXysxhyOiX = false;}
      if(HhqfFrwZoo == true){HhqfFrwZoo = false;}
      if(yfYPzdPlDX == true){yfYPzdPlDX = false;}
      if(FdMKjJfXQi == true){FdMKjJfXQi = false;}
      if(YDqWUWzeds == true){YDqWUWzeds = false;}
      if(yTJBhmzisS == true){yTJBhmzisS = false;}
      if(RLLKRcUfww == true){RLLKRcUfww = false;}
      if(MXIGPunBuc == true){MXIGPunBuc = false;}
      if(ekHKZlUKcw == true){ekHKZlUKcw = false;}
      if(KxexQNrfFq == true){KxexQNrfFq = false;}
      if(BSihfaKDkl == true){BSihfaKDkl = false;}
      if(zxmPngEAkf == true){zxmPngEAkf = false;}
      if(IKDAkPrKoC == true){IKDAkPrKoC = false;}
      if(CIwDbLCZdz == true){CIwDbLCZdz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSRNXNXFXM
{ 
  void reAZIhhjXf()
  { 
      bool rHOVbSLwEZ = false;
      bool DkQwAqxBIj = false;
      bool uciQUwjILg = false;
      bool pwhiJqYCwD = false;
      bool nNuoMTmMXc = false;
      bool PSDPyOXxBe = false;
      bool iCkWiGDhmI = false;
      bool RtEFuhgsEA = false;
      bool IXkhRXrSjt = false;
      bool SaBRUlcYGG = false;
      bool QFYOKUNyUQ = false;
      bool hdsAWLQCFK = false;
      bool NkxroqsmkI = false;
      bool FImxjCyVXx = false;
      bool JtxTLogAtI = false;
      bool VZTwreIgZT = false;
      bool aaMLKZqwQT = false;
      bool NteIASmdgA = false;
      bool KsrbmeoqFE = false;
      bool tQwDVihlIl = false;
      string gUpIgfpUDp;
      string ELAEcArXYX;
      string LsMEJWMRpN;
      string kcGXhGpEGt;
      string hZyiQSMsqO;
      string BJGCNnHlzJ;
      string SYepFbFbWW;
      string JnRdpludnp;
      string KTaaLaWEKs;
      string zEEwbItHdn;
      string NkWUENqbLa;
      string scxJzyyDdd;
      string EBRcWFiUCg;
      string qmzzbYxFWy;
      string itriAVGuwc;
      string KqczjMTsxz;
      string dVZejFcygZ;
      string ArfftKJhcB;
      string zmYYVzKAOP;
      string FEIXTNTMzt;
      if(gUpIgfpUDp == NkWUENqbLa){rHOVbSLwEZ = true;}
      else if(NkWUENqbLa == gUpIgfpUDp){QFYOKUNyUQ = true;}
      if(ELAEcArXYX == scxJzyyDdd){DkQwAqxBIj = true;}
      else if(scxJzyyDdd == ELAEcArXYX){hdsAWLQCFK = true;}
      if(LsMEJWMRpN == EBRcWFiUCg){uciQUwjILg = true;}
      else if(EBRcWFiUCg == LsMEJWMRpN){NkxroqsmkI = true;}
      if(kcGXhGpEGt == qmzzbYxFWy){pwhiJqYCwD = true;}
      else if(qmzzbYxFWy == kcGXhGpEGt){FImxjCyVXx = true;}
      if(hZyiQSMsqO == itriAVGuwc){nNuoMTmMXc = true;}
      else if(itriAVGuwc == hZyiQSMsqO){JtxTLogAtI = true;}
      if(BJGCNnHlzJ == KqczjMTsxz){PSDPyOXxBe = true;}
      else if(KqczjMTsxz == BJGCNnHlzJ){VZTwreIgZT = true;}
      if(SYepFbFbWW == dVZejFcygZ){iCkWiGDhmI = true;}
      else if(dVZejFcygZ == SYepFbFbWW){aaMLKZqwQT = true;}
      if(JnRdpludnp == ArfftKJhcB){RtEFuhgsEA = true;}
      if(KTaaLaWEKs == zmYYVzKAOP){IXkhRXrSjt = true;}
      if(zEEwbItHdn == FEIXTNTMzt){SaBRUlcYGG = true;}
      while(ArfftKJhcB == JnRdpludnp){NteIASmdgA = true;}
      while(zmYYVzKAOP == zmYYVzKAOP){KsrbmeoqFE = true;}
      while(FEIXTNTMzt == FEIXTNTMzt){tQwDVihlIl = true;}
      if(rHOVbSLwEZ == true){rHOVbSLwEZ = false;}
      if(DkQwAqxBIj == true){DkQwAqxBIj = false;}
      if(uciQUwjILg == true){uciQUwjILg = false;}
      if(pwhiJqYCwD == true){pwhiJqYCwD = false;}
      if(nNuoMTmMXc == true){nNuoMTmMXc = false;}
      if(PSDPyOXxBe == true){PSDPyOXxBe = false;}
      if(iCkWiGDhmI == true){iCkWiGDhmI = false;}
      if(RtEFuhgsEA == true){RtEFuhgsEA = false;}
      if(IXkhRXrSjt == true){IXkhRXrSjt = false;}
      if(SaBRUlcYGG == true){SaBRUlcYGG = false;}
      if(QFYOKUNyUQ == true){QFYOKUNyUQ = false;}
      if(hdsAWLQCFK == true){hdsAWLQCFK = false;}
      if(NkxroqsmkI == true){NkxroqsmkI = false;}
      if(FImxjCyVXx == true){FImxjCyVXx = false;}
      if(JtxTLogAtI == true){JtxTLogAtI = false;}
      if(VZTwreIgZT == true){VZTwreIgZT = false;}
      if(aaMLKZqwQT == true){aaMLKZqwQT = false;}
      if(NteIASmdgA == true){NteIASmdgA = false;}
      if(KsrbmeoqFE == true){KsrbmeoqFE = false;}
      if(tQwDVihlIl == true){tQwDVihlIl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRJEOCBEMK
{ 
  void pMQrKbtyTN()
  { 
      bool pRlaZcFfJU = false;
      bool oIrVjSyTPC = false;
      bool YFiJrPhzRk = false;
      bool KpZorcAmnn = false;
      bool JhcRPuMmxb = false;
      bool eGzsAjibhJ = false;
      bool uGOXKyhCdH = false;
      bool RKfbrpcRsw = false;
      bool DtBpGDqgnH = false;
      bool tXFdrCTEHR = false;
      bool MJJpJTaXAK = false;
      bool HRikGAFYRG = false;
      bool HBNVNtFBio = false;
      bool VXJbjskLfl = false;
      bool cSfdzboTWr = false;
      bool xumBJLwmcP = false;
      bool OYoLniHGBN = false;
      bool PsrecnUjWk = false;
      bool EldqqajIRX = false;
      bool wxhQXEdUoP = false;
      string cLJeIomyoe;
      string WIFCdFgYjO;
      string kUSwQdOCcl;
      string gZomQcRdhB;
      string GBHczRgTVB;
      string tpZZEIrNOd;
      string ajUDxwSRkB;
      string mCpiHiMpxz;
      string xtgaqqAPhI;
      string kEPDZWgEeC;
      string yOiTOrzqSU;
      string uCPOffDsLG;
      string uDibQimlIk;
      string CHKtAiLMMz;
      string qJxNNhnAXt;
      string TmrYHueGDe;
      string ENhgRnqVOw;
      string UpgMOlGVOh;
      string ulONRPOlmF;
      string EEIhtdaPuY;
      if(cLJeIomyoe == yOiTOrzqSU){pRlaZcFfJU = true;}
      else if(yOiTOrzqSU == cLJeIomyoe){MJJpJTaXAK = true;}
      if(WIFCdFgYjO == uCPOffDsLG){oIrVjSyTPC = true;}
      else if(uCPOffDsLG == WIFCdFgYjO){HRikGAFYRG = true;}
      if(kUSwQdOCcl == uDibQimlIk){YFiJrPhzRk = true;}
      else if(uDibQimlIk == kUSwQdOCcl){HBNVNtFBio = true;}
      if(gZomQcRdhB == CHKtAiLMMz){KpZorcAmnn = true;}
      else if(CHKtAiLMMz == gZomQcRdhB){VXJbjskLfl = true;}
      if(GBHczRgTVB == qJxNNhnAXt){JhcRPuMmxb = true;}
      else if(qJxNNhnAXt == GBHczRgTVB){cSfdzboTWr = true;}
      if(tpZZEIrNOd == TmrYHueGDe){eGzsAjibhJ = true;}
      else if(TmrYHueGDe == tpZZEIrNOd){xumBJLwmcP = true;}
      if(ajUDxwSRkB == ENhgRnqVOw){uGOXKyhCdH = true;}
      else if(ENhgRnqVOw == ajUDxwSRkB){OYoLniHGBN = true;}
      if(mCpiHiMpxz == UpgMOlGVOh){RKfbrpcRsw = true;}
      if(xtgaqqAPhI == ulONRPOlmF){DtBpGDqgnH = true;}
      if(kEPDZWgEeC == EEIhtdaPuY){tXFdrCTEHR = true;}
      while(UpgMOlGVOh == mCpiHiMpxz){PsrecnUjWk = true;}
      while(ulONRPOlmF == ulONRPOlmF){EldqqajIRX = true;}
      while(EEIhtdaPuY == EEIhtdaPuY){wxhQXEdUoP = true;}
      if(pRlaZcFfJU == true){pRlaZcFfJU = false;}
      if(oIrVjSyTPC == true){oIrVjSyTPC = false;}
      if(YFiJrPhzRk == true){YFiJrPhzRk = false;}
      if(KpZorcAmnn == true){KpZorcAmnn = false;}
      if(JhcRPuMmxb == true){JhcRPuMmxb = false;}
      if(eGzsAjibhJ == true){eGzsAjibhJ = false;}
      if(uGOXKyhCdH == true){uGOXKyhCdH = false;}
      if(RKfbrpcRsw == true){RKfbrpcRsw = false;}
      if(DtBpGDqgnH == true){DtBpGDqgnH = false;}
      if(tXFdrCTEHR == true){tXFdrCTEHR = false;}
      if(MJJpJTaXAK == true){MJJpJTaXAK = false;}
      if(HRikGAFYRG == true){HRikGAFYRG = false;}
      if(HBNVNtFBio == true){HBNVNtFBio = false;}
      if(VXJbjskLfl == true){VXJbjskLfl = false;}
      if(cSfdzboTWr == true){cSfdzboTWr = false;}
      if(xumBJLwmcP == true){xumBJLwmcP = false;}
      if(OYoLniHGBN == true){OYoLniHGBN = false;}
      if(PsrecnUjWk == true){PsrecnUjWk = false;}
      if(EldqqajIRX == true){EldqqajIRX = false;}
      if(wxhQXEdUoP == true){wxhQXEdUoP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZTYEVOUQG
{ 
  void rZbbaXZqSQ()
  { 
      bool XFFUNyDLPk = false;
      bool HXHOUZmFnc = false;
      bool zPLsOgwXbl = false;
      bool EeHdXDDiAQ = false;
      bool BBZdsVVVNf = false;
      bool QFpHzHtMGf = false;
      bool BficgbQcqQ = false;
      bool VEFWayogzr = false;
      bool LaJwUzoAeP = false;
      bool IpcTPURwwQ = false;
      bool FrewJMzSfB = false;
      bool RMMNUaVmIh = false;
      bool mQyaIfblHG = false;
      bool gsjimSuNlI = false;
      bool zWTcywcOyn = false;
      bool zdnOdotEnc = false;
      bool jNKZTYbdaB = false;
      bool eIAzhQwUbL = false;
      bool CMmTGDEVFy = false;
      bool YqYIXlLtJZ = false;
      string RThkdoURlV;
      string xDieTlKSmO;
      string cfggCedPPm;
      string QUgJNQYsrG;
      string MgMuWdxqlh;
      string IylAtklBiy;
      string KFCzEbWYRD;
      string NRZgCuTlJX;
      string hmdhdSifPc;
      string dXJsuHeNpt;
      string HYZiUpXEyy;
      string RAqKQXbTUk;
      string spJnYpHfku;
      string QFuPQINtNm;
      string udgRKcgzcX;
      string eKsFAQPkJd;
      string hqSDhLFasH;
      string JgGgpOIqcu;
      string JIDNPFMoPA;
      string scjiFEKdjz;
      if(RThkdoURlV == HYZiUpXEyy){XFFUNyDLPk = true;}
      else if(HYZiUpXEyy == RThkdoURlV){FrewJMzSfB = true;}
      if(xDieTlKSmO == RAqKQXbTUk){HXHOUZmFnc = true;}
      else if(RAqKQXbTUk == xDieTlKSmO){RMMNUaVmIh = true;}
      if(cfggCedPPm == spJnYpHfku){zPLsOgwXbl = true;}
      else if(spJnYpHfku == cfggCedPPm){mQyaIfblHG = true;}
      if(QUgJNQYsrG == QFuPQINtNm){EeHdXDDiAQ = true;}
      else if(QFuPQINtNm == QUgJNQYsrG){gsjimSuNlI = true;}
      if(MgMuWdxqlh == udgRKcgzcX){BBZdsVVVNf = true;}
      else if(udgRKcgzcX == MgMuWdxqlh){zWTcywcOyn = true;}
      if(IylAtklBiy == eKsFAQPkJd){QFpHzHtMGf = true;}
      else if(eKsFAQPkJd == IylAtklBiy){zdnOdotEnc = true;}
      if(KFCzEbWYRD == hqSDhLFasH){BficgbQcqQ = true;}
      else if(hqSDhLFasH == KFCzEbWYRD){jNKZTYbdaB = true;}
      if(NRZgCuTlJX == JgGgpOIqcu){VEFWayogzr = true;}
      if(hmdhdSifPc == JIDNPFMoPA){LaJwUzoAeP = true;}
      if(dXJsuHeNpt == scjiFEKdjz){IpcTPURwwQ = true;}
      while(JgGgpOIqcu == NRZgCuTlJX){eIAzhQwUbL = true;}
      while(JIDNPFMoPA == JIDNPFMoPA){CMmTGDEVFy = true;}
      while(scjiFEKdjz == scjiFEKdjz){YqYIXlLtJZ = true;}
      if(XFFUNyDLPk == true){XFFUNyDLPk = false;}
      if(HXHOUZmFnc == true){HXHOUZmFnc = false;}
      if(zPLsOgwXbl == true){zPLsOgwXbl = false;}
      if(EeHdXDDiAQ == true){EeHdXDDiAQ = false;}
      if(BBZdsVVVNf == true){BBZdsVVVNf = false;}
      if(QFpHzHtMGf == true){QFpHzHtMGf = false;}
      if(BficgbQcqQ == true){BficgbQcqQ = false;}
      if(VEFWayogzr == true){VEFWayogzr = false;}
      if(LaJwUzoAeP == true){LaJwUzoAeP = false;}
      if(IpcTPURwwQ == true){IpcTPURwwQ = false;}
      if(FrewJMzSfB == true){FrewJMzSfB = false;}
      if(RMMNUaVmIh == true){RMMNUaVmIh = false;}
      if(mQyaIfblHG == true){mQyaIfblHG = false;}
      if(gsjimSuNlI == true){gsjimSuNlI = false;}
      if(zWTcywcOyn == true){zWTcywcOyn = false;}
      if(zdnOdotEnc == true){zdnOdotEnc = false;}
      if(jNKZTYbdaB == true){jNKZTYbdaB = false;}
      if(eIAzhQwUbL == true){eIAzhQwUbL = false;}
      if(CMmTGDEVFy == true){CMmTGDEVFy = false;}
      if(YqYIXlLtJZ == true){YqYIXlLtJZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PANLMZSRGC
{ 
  void ukSizmiyGu()
  { 
      bool MrrwnNXoUF = false;
      bool zXQcXhgsiL = false;
      bool gDuClPdmVe = false;
      bool NkBWqqKaIn = false;
      bool eqxaomPiSj = false;
      bool WELcaJwpKX = false;
      bool ijSpqOWslg = false;
      bool WGkugoFUMy = false;
      bool AtUlHJYXwg = false;
      bool uUPkEuYHiZ = false;
      bool QVxlMPSPwk = false;
      bool DacLWnPghg = false;
      bool oyxEkCpzpk = false;
      bool QykmgexhZq = false;
      bool pIaKdTqEOP = false;
      bool frYCjSXsAJ = false;
      bool YTYLTFopdr = false;
      bool qgHppfWlZR = false;
      bool KlkaFYYiCO = false;
      bool GDgPRWjPqY = false;
      string XBjGUHlAKD;
      string mnwnBeBGrb;
      string AWntjNMqPn;
      string gZGbunhRYC;
      string iQrTeYcofG;
      string JCMjEBNoVH;
      string tukWWMhTsN;
      string wihosjdUPK;
      string jWLIddMWXs;
      string asuQHmeUxR;
      string pJuSKZUXpT;
      string WrYLXXicrr;
      string ALuAlDnQgF;
      string FJWxTZasyE;
      string InfEVhTjsj;
      string ECcEReOufH;
      string lEpkONVbqx;
      string wpeniLfqeD;
      string iDWxBCfSfo;
      string LfMqRExuoH;
      if(XBjGUHlAKD == pJuSKZUXpT){MrrwnNXoUF = true;}
      else if(pJuSKZUXpT == XBjGUHlAKD){QVxlMPSPwk = true;}
      if(mnwnBeBGrb == WrYLXXicrr){zXQcXhgsiL = true;}
      else if(WrYLXXicrr == mnwnBeBGrb){DacLWnPghg = true;}
      if(AWntjNMqPn == ALuAlDnQgF){gDuClPdmVe = true;}
      else if(ALuAlDnQgF == AWntjNMqPn){oyxEkCpzpk = true;}
      if(gZGbunhRYC == FJWxTZasyE){NkBWqqKaIn = true;}
      else if(FJWxTZasyE == gZGbunhRYC){QykmgexhZq = true;}
      if(iQrTeYcofG == InfEVhTjsj){eqxaomPiSj = true;}
      else if(InfEVhTjsj == iQrTeYcofG){pIaKdTqEOP = true;}
      if(JCMjEBNoVH == ECcEReOufH){WELcaJwpKX = true;}
      else if(ECcEReOufH == JCMjEBNoVH){frYCjSXsAJ = true;}
      if(tukWWMhTsN == lEpkONVbqx){ijSpqOWslg = true;}
      else if(lEpkONVbqx == tukWWMhTsN){YTYLTFopdr = true;}
      if(wihosjdUPK == wpeniLfqeD){WGkugoFUMy = true;}
      if(jWLIddMWXs == iDWxBCfSfo){AtUlHJYXwg = true;}
      if(asuQHmeUxR == LfMqRExuoH){uUPkEuYHiZ = true;}
      while(wpeniLfqeD == wihosjdUPK){qgHppfWlZR = true;}
      while(iDWxBCfSfo == iDWxBCfSfo){KlkaFYYiCO = true;}
      while(LfMqRExuoH == LfMqRExuoH){GDgPRWjPqY = true;}
      if(MrrwnNXoUF == true){MrrwnNXoUF = false;}
      if(zXQcXhgsiL == true){zXQcXhgsiL = false;}
      if(gDuClPdmVe == true){gDuClPdmVe = false;}
      if(NkBWqqKaIn == true){NkBWqqKaIn = false;}
      if(eqxaomPiSj == true){eqxaomPiSj = false;}
      if(WELcaJwpKX == true){WELcaJwpKX = false;}
      if(ijSpqOWslg == true){ijSpqOWslg = false;}
      if(WGkugoFUMy == true){WGkugoFUMy = false;}
      if(AtUlHJYXwg == true){AtUlHJYXwg = false;}
      if(uUPkEuYHiZ == true){uUPkEuYHiZ = false;}
      if(QVxlMPSPwk == true){QVxlMPSPwk = false;}
      if(DacLWnPghg == true){DacLWnPghg = false;}
      if(oyxEkCpzpk == true){oyxEkCpzpk = false;}
      if(QykmgexhZq == true){QykmgexhZq = false;}
      if(pIaKdTqEOP == true){pIaKdTqEOP = false;}
      if(frYCjSXsAJ == true){frYCjSXsAJ = false;}
      if(YTYLTFopdr == true){YTYLTFopdr = false;}
      if(qgHppfWlZR == true){qgHppfWlZR = false;}
      if(KlkaFYYiCO == true){KlkaFYYiCO = false;}
      if(GDgPRWjPqY == true){GDgPRWjPqY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBQAGKKWLO
{ 
  void ftgjSPbwyD()
  { 
      bool wWHotsAFeC = false;
      bool hnfastKeJB = false;
      bool nTHJjMQazw = false;
      bool lVamrCEwXQ = false;
      bool TiRVydCNXI = false;
      bool grkeycPyEg = false;
      bool cZFhPLMsip = false;
      bool oOGsgEBkKF = false;
      bool KDCpOtkunP = false;
      bool mGqqntciGm = false;
      bool QIehTSlrys = false;
      bool adnzVZWPSV = false;
      bool aRESDiWPEl = false;
      bool bSeXnBYUWw = false;
      bool HsxuoISqUN = false;
      bool XNQjLzDLej = false;
      bool uWmMRIzPKU = false;
      bool BCrWNhTJdt = false;
      bool QetpOOBtLn = false;
      bool xMomAkFkcf = false;
      string XiYwBdZqHL;
      string SZwOfTafcR;
      string PcsbQRJofT;
      string XNxCjjSysu;
      string wgJixGyZPx;
      string sLmBRtpwej;
      string UkLmnFbtew;
      string AclhViTKdJ;
      string SjYhZMZujp;
      string sVSIZLVVtr;
      string eEtTxQYFfi;
      string afSUQkLcMb;
      string efJoCdJcHK;
      string MxPleNoFkJ;
      string mUPBPNDxro;
      string zrISMyuFQT;
      string GuxUVcQfpC;
      string uFrDnKQHYo;
      string ZLkRKUowYg;
      string SioRDqXtfl;
      if(XiYwBdZqHL == eEtTxQYFfi){wWHotsAFeC = true;}
      else if(eEtTxQYFfi == XiYwBdZqHL){QIehTSlrys = true;}
      if(SZwOfTafcR == afSUQkLcMb){hnfastKeJB = true;}
      else if(afSUQkLcMb == SZwOfTafcR){adnzVZWPSV = true;}
      if(PcsbQRJofT == efJoCdJcHK){nTHJjMQazw = true;}
      else if(efJoCdJcHK == PcsbQRJofT){aRESDiWPEl = true;}
      if(XNxCjjSysu == MxPleNoFkJ){lVamrCEwXQ = true;}
      else if(MxPleNoFkJ == XNxCjjSysu){bSeXnBYUWw = true;}
      if(wgJixGyZPx == mUPBPNDxro){TiRVydCNXI = true;}
      else if(mUPBPNDxro == wgJixGyZPx){HsxuoISqUN = true;}
      if(sLmBRtpwej == zrISMyuFQT){grkeycPyEg = true;}
      else if(zrISMyuFQT == sLmBRtpwej){XNQjLzDLej = true;}
      if(UkLmnFbtew == GuxUVcQfpC){cZFhPLMsip = true;}
      else if(GuxUVcQfpC == UkLmnFbtew){uWmMRIzPKU = true;}
      if(AclhViTKdJ == uFrDnKQHYo){oOGsgEBkKF = true;}
      if(SjYhZMZujp == ZLkRKUowYg){KDCpOtkunP = true;}
      if(sVSIZLVVtr == SioRDqXtfl){mGqqntciGm = true;}
      while(uFrDnKQHYo == AclhViTKdJ){BCrWNhTJdt = true;}
      while(ZLkRKUowYg == ZLkRKUowYg){QetpOOBtLn = true;}
      while(SioRDqXtfl == SioRDqXtfl){xMomAkFkcf = true;}
      if(wWHotsAFeC == true){wWHotsAFeC = false;}
      if(hnfastKeJB == true){hnfastKeJB = false;}
      if(nTHJjMQazw == true){nTHJjMQazw = false;}
      if(lVamrCEwXQ == true){lVamrCEwXQ = false;}
      if(TiRVydCNXI == true){TiRVydCNXI = false;}
      if(grkeycPyEg == true){grkeycPyEg = false;}
      if(cZFhPLMsip == true){cZFhPLMsip = false;}
      if(oOGsgEBkKF == true){oOGsgEBkKF = false;}
      if(KDCpOtkunP == true){KDCpOtkunP = false;}
      if(mGqqntciGm == true){mGqqntciGm = false;}
      if(QIehTSlrys == true){QIehTSlrys = false;}
      if(adnzVZWPSV == true){adnzVZWPSV = false;}
      if(aRESDiWPEl == true){aRESDiWPEl = false;}
      if(bSeXnBYUWw == true){bSeXnBYUWw = false;}
      if(HsxuoISqUN == true){HsxuoISqUN = false;}
      if(XNQjLzDLej == true){XNQjLzDLej = false;}
      if(uWmMRIzPKU == true){uWmMRIzPKU = false;}
      if(BCrWNhTJdt == true){BCrWNhTJdt = false;}
      if(QetpOOBtLn == true){QetpOOBtLn = false;}
      if(xMomAkFkcf == true){xMomAkFkcf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXGWLYEVWJ
{ 
  void IJQmAFdQKq()
  { 
      bool XPQZKDCCMJ = false;
      bool ypfppVfYmc = false;
      bool OasCpCrBxl = false;
      bool dRimbHGWVZ = false;
      bool tsjWniNchT = false;
      bool uTJJOxWOjI = false;
      bool LAEafgHsOi = false;
      bool OIDMhUpVNG = false;
      bool nPScpJHZXd = false;
      bool jqmNNsnJqH = false;
      bool aUNzFmPwbs = false;
      bool HABcTwhbkV = false;
      bool ZhUjyWVpzn = false;
      bool gfdGfTBSXD = false;
      bool tKydWipJsR = false;
      bool LLYVgszcBh = false;
      bool QZxmMaWuxz = false;
      bool tPEgbPjpMO = false;
      bool gLwgcUHIYm = false;
      bool TXRolTMKRw = false;
      string YCNHwngFkG;
      string MCMCmOFDmY;
      string bjsQbPRSeH;
      string SFFVUAYcXL;
      string xOneFljfXR;
      string AxRiLnJxff;
      string VOacmGxqhl;
      string pbeaaNuOKo;
      string eltNHVnVJf;
      string qbxqoinKqy;
      string osxkaXRpIy;
      string sulpBjTMVR;
      string SbgCuNenkr;
      string YjWLAlnIli;
      string ExMLlwpGpF;
      string OboZeNLupN;
      string sdEPZJXZoP;
      string uKZmMVOUPz;
      string XXxfcwuxgm;
      string ZsSYoarxlc;
      if(YCNHwngFkG == osxkaXRpIy){XPQZKDCCMJ = true;}
      else if(osxkaXRpIy == YCNHwngFkG){aUNzFmPwbs = true;}
      if(MCMCmOFDmY == sulpBjTMVR){ypfppVfYmc = true;}
      else if(sulpBjTMVR == MCMCmOFDmY){HABcTwhbkV = true;}
      if(bjsQbPRSeH == SbgCuNenkr){OasCpCrBxl = true;}
      else if(SbgCuNenkr == bjsQbPRSeH){ZhUjyWVpzn = true;}
      if(SFFVUAYcXL == YjWLAlnIli){dRimbHGWVZ = true;}
      else if(YjWLAlnIli == SFFVUAYcXL){gfdGfTBSXD = true;}
      if(xOneFljfXR == ExMLlwpGpF){tsjWniNchT = true;}
      else if(ExMLlwpGpF == xOneFljfXR){tKydWipJsR = true;}
      if(AxRiLnJxff == OboZeNLupN){uTJJOxWOjI = true;}
      else if(OboZeNLupN == AxRiLnJxff){LLYVgszcBh = true;}
      if(VOacmGxqhl == sdEPZJXZoP){LAEafgHsOi = true;}
      else if(sdEPZJXZoP == VOacmGxqhl){QZxmMaWuxz = true;}
      if(pbeaaNuOKo == uKZmMVOUPz){OIDMhUpVNG = true;}
      if(eltNHVnVJf == XXxfcwuxgm){nPScpJHZXd = true;}
      if(qbxqoinKqy == ZsSYoarxlc){jqmNNsnJqH = true;}
      while(uKZmMVOUPz == pbeaaNuOKo){tPEgbPjpMO = true;}
      while(XXxfcwuxgm == XXxfcwuxgm){gLwgcUHIYm = true;}
      while(ZsSYoarxlc == ZsSYoarxlc){TXRolTMKRw = true;}
      if(XPQZKDCCMJ == true){XPQZKDCCMJ = false;}
      if(ypfppVfYmc == true){ypfppVfYmc = false;}
      if(OasCpCrBxl == true){OasCpCrBxl = false;}
      if(dRimbHGWVZ == true){dRimbHGWVZ = false;}
      if(tsjWniNchT == true){tsjWniNchT = false;}
      if(uTJJOxWOjI == true){uTJJOxWOjI = false;}
      if(LAEafgHsOi == true){LAEafgHsOi = false;}
      if(OIDMhUpVNG == true){OIDMhUpVNG = false;}
      if(nPScpJHZXd == true){nPScpJHZXd = false;}
      if(jqmNNsnJqH == true){jqmNNsnJqH = false;}
      if(aUNzFmPwbs == true){aUNzFmPwbs = false;}
      if(HABcTwhbkV == true){HABcTwhbkV = false;}
      if(ZhUjyWVpzn == true){ZhUjyWVpzn = false;}
      if(gfdGfTBSXD == true){gfdGfTBSXD = false;}
      if(tKydWipJsR == true){tKydWipJsR = false;}
      if(LLYVgszcBh == true){LLYVgszcBh = false;}
      if(QZxmMaWuxz == true){QZxmMaWuxz = false;}
      if(tPEgbPjpMO == true){tPEgbPjpMO = false;}
      if(gLwgcUHIYm == true){gLwgcUHIYm = false;}
      if(TXRolTMKRw == true){TXRolTMKRw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHKLPGUNJZ
{ 
  void ymuQDYMrmX()
  { 
      bool ZTpLNNeHXc = false;
      bool PRsRaosDUS = false;
      bool CJLSMWGBUQ = false;
      bool RHDSJOmJHN = false;
      bool FjBoEWaxTY = false;
      bool JxpnUQHWzq = false;
      bool HclHKHNaHM = false;
      bool CjwGMRIWNo = false;
      bool wJhuHUROxs = false;
      bool GPJQGbysdx = false;
      bool JzoHVYBjaD = false;
      bool IkIKtxuqAp = false;
      bool ozcOFmZezj = false;
      bool TOrQfwTZYh = false;
      bool ThmsjVGzVI = false;
      bool gGsnHJWZBi = false;
      bool zVjpjtsrey = false;
      bool dURRVHLiej = false;
      bool fZJqDMUDIV = false;
      bool ZsYohxxwJp = false;
      string oXMStcACbg;
      string YAaMKGuiSy;
      string RWaPPJlFFD;
      string eDHeMHkVRq;
      string PbfeLCsqwK;
      string xObqFSwwDj;
      string ptxXBUruAD;
      string UYQbhppuEM;
      string QuJuGPaQZs;
      string KoShAVdIdp;
      string JyqsoYyAIO;
      string bBrpTukCRk;
      string taVHrfFiaM;
      string LhROCREPFh;
      string RaHKQJxcNF;
      string jbqrwicjAJ;
      string SOZwDsidmB;
      string qVxiTSSKpi;
      string hcVVbjqZRT;
      string oTOuOCBKHW;
      if(oXMStcACbg == JyqsoYyAIO){ZTpLNNeHXc = true;}
      else if(JyqsoYyAIO == oXMStcACbg){JzoHVYBjaD = true;}
      if(YAaMKGuiSy == bBrpTukCRk){PRsRaosDUS = true;}
      else if(bBrpTukCRk == YAaMKGuiSy){IkIKtxuqAp = true;}
      if(RWaPPJlFFD == taVHrfFiaM){CJLSMWGBUQ = true;}
      else if(taVHrfFiaM == RWaPPJlFFD){ozcOFmZezj = true;}
      if(eDHeMHkVRq == LhROCREPFh){RHDSJOmJHN = true;}
      else if(LhROCREPFh == eDHeMHkVRq){TOrQfwTZYh = true;}
      if(PbfeLCsqwK == RaHKQJxcNF){FjBoEWaxTY = true;}
      else if(RaHKQJxcNF == PbfeLCsqwK){ThmsjVGzVI = true;}
      if(xObqFSwwDj == jbqrwicjAJ){JxpnUQHWzq = true;}
      else if(jbqrwicjAJ == xObqFSwwDj){gGsnHJWZBi = true;}
      if(ptxXBUruAD == SOZwDsidmB){HclHKHNaHM = true;}
      else if(SOZwDsidmB == ptxXBUruAD){zVjpjtsrey = true;}
      if(UYQbhppuEM == qVxiTSSKpi){CjwGMRIWNo = true;}
      if(QuJuGPaQZs == hcVVbjqZRT){wJhuHUROxs = true;}
      if(KoShAVdIdp == oTOuOCBKHW){GPJQGbysdx = true;}
      while(qVxiTSSKpi == UYQbhppuEM){dURRVHLiej = true;}
      while(hcVVbjqZRT == hcVVbjqZRT){fZJqDMUDIV = true;}
      while(oTOuOCBKHW == oTOuOCBKHW){ZsYohxxwJp = true;}
      if(ZTpLNNeHXc == true){ZTpLNNeHXc = false;}
      if(PRsRaosDUS == true){PRsRaosDUS = false;}
      if(CJLSMWGBUQ == true){CJLSMWGBUQ = false;}
      if(RHDSJOmJHN == true){RHDSJOmJHN = false;}
      if(FjBoEWaxTY == true){FjBoEWaxTY = false;}
      if(JxpnUQHWzq == true){JxpnUQHWzq = false;}
      if(HclHKHNaHM == true){HclHKHNaHM = false;}
      if(CjwGMRIWNo == true){CjwGMRIWNo = false;}
      if(wJhuHUROxs == true){wJhuHUROxs = false;}
      if(GPJQGbysdx == true){GPJQGbysdx = false;}
      if(JzoHVYBjaD == true){JzoHVYBjaD = false;}
      if(IkIKtxuqAp == true){IkIKtxuqAp = false;}
      if(ozcOFmZezj == true){ozcOFmZezj = false;}
      if(TOrQfwTZYh == true){TOrQfwTZYh = false;}
      if(ThmsjVGzVI == true){ThmsjVGzVI = false;}
      if(gGsnHJWZBi == true){gGsnHJWZBi = false;}
      if(zVjpjtsrey == true){zVjpjtsrey = false;}
      if(dURRVHLiej == true){dURRVHLiej = false;}
      if(fZJqDMUDIV == true){fZJqDMUDIV = false;}
      if(ZsYohxxwJp == true){ZsYohxxwJp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVADIVYPOZ
{ 
  void eVSzJVXdgo()
  { 
      bool eNSmaDoWXf = false;
      bool VnnILsBfBw = false;
      bool fntqwHhdcm = false;
      bool FVwMYmGNYn = false;
      bool FbGkQrDkWe = false;
      bool GnkdxqTapS = false;
      bool ULtjZAqbjX = false;
      bool mnGMqDgJaD = false;
      bool EwGygRkROg = false;
      bool TfWGSshWKQ = false;
      bool AaByrSgXmt = false;
      bool JKzmOYEuCI = false;
      bool OZMCEHQAtx = false;
      bool VKzKCcuHFO = false;
      bool jNdUXIfjrt = false;
      bool nlTBBaOytk = false;
      bool CgdpYzLojl = false;
      bool cwpnYBureu = false;
      bool afIzIiqxIb = false;
      bool OxNUMDjnwX = false;
      string gcQWzCCCHl;
      string PnuUSirzdJ;
      string JjmZomkxJi;
      string AfCAJEzbxK;
      string UCrNSEumbY;
      string EUYFtxppgM;
      string RErYliktLO;
      string jPBSnGrZHk;
      string rxUjeeHxFM;
      string NItksPJSai;
      string SAbNonTFRn;
      string EQiwUTjHsH;
      string bnoyAaVQZX;
      string wYyXRqUHuq;
      string KBfRIxYxPY;
      string fBZTGeKdMN;
      string RCfsqeRKec;
      string ycLCwaIWoD;
      string BYAAquzdQm;
      string gqthYIUlac;
      if(gcQWzCCCHl == SAbNonTFRn){eNSmaDoWXf = true;}
      else if(SAbNonTFRn == gcQWzCCCHl){AaByrSgXmt = true;}
      if(PnuUSirzdJ == EQiwUTjHsH){VnnILsBfBw = true;}
      else if(EQiwUTjHsH == PnuUSirzdJ){JKzmOYEuCI = true;}
      if(JjmZomkxJi == bnoyAaVQZX){fntqwHhdcm = true;}
      else if(bnoyAaVQZX == JjmZomkxJi){OZMCEHQAtx = true;}
      if(AfCAJEzbxK == wYyXRqUHuq){FVwMYmGNYn = true;}
      else if(wYyXRqUHuq == AfCAJEzbxK){VKzKCcuHFO = true;}
      if(UCrNSEumbY == KBfRIxYxPY){FbGkQrDkWe = true;}
      else if(KBfRIxYxPY == UCrNSEumbY){jNdUXIfjrt = true;}
      if(EUYFtxppgM == fBZTGeKdMN){GnkdxqTapS = true;}
      else if(fBZTGeKdMN == EUYFtxppgM){nlTBBaOytk = true;}
      if(RErYliktLO == RCfsqeRKec){ULtjZAqbjX = true;}
      else if(RCfsqeRKec == RErYliktLO){CgdpYzLojl = true;}
      if(jPBSnGrZHk == ycLCwaIWoD){mnGMqDgJaD = true;}
      if(rxUjeeHxFM == BYAAquzdQm){EwGygRkROg = true;}
      if(NItksPJSai == gqthYIUlac){TfWGSshWKQ = true;}
      while(ycLCwaIWoD == jPBSnGrZHk){cwpnYBureu = true;}
      while(BYAAquzdQm == BYAAquzdQm){afIzIiqxIb = true;}
      while(gqthYIUlac == gqthYIUlac){OxNUMDjnwX = true;}
      if(eNSmaDoWXf == true){eNSmaDoWXf = false;}
      if(VnnILsBfBw == true){VnnILsBfBw = false;}
      if(fntqwHhdcm == true){fntqwHhdcm = false;}
      if(FVwMYmGNYn == true){FVwMYmGNYn = false;}
      if(FbGkQrDkWe == true){FbGkQrDkWe = false;}
      if(GnkdxqTapS == true){GnkdxqTapS = false;}
      if(ULtjZAqbjX == true){ULtjZAqbjX = false;}
      if(mnGMqDgJaD == true){mnGMqDgJaD = false;}
      if(EwGygRkROg == true){EwGygRkROg = false;}
      if(TfWGSshWKQ == true){TfWGSshWKQ = false;}
      if(AaByrSgXmt == true){AaByrSgXmt = false;}
      if(JKzmOYEuCI == true){JKzmOYEuCI = false;}
      if(OZMCEHQAtx == true){OZMCEHQAtx = false;}
      if(VKzKCcuHFO == true){VKzKCcuHFO = false;}
      if(jNdUXIfjrt == true){jNdUXIfjrt = false;}
      if(nlTBBaOytk == true){nlTBBaOytk = false;}
      if(CgdpYzLojl == true){CgdpYzLojl = false;}
      if(cwpnYBureu == true){cwpnYBureu = false;}
      if(afIzIiqxIb == true){afIzIiqxIb = false;}
      if(OxNUMDjnwX == true){OxNUMDjnwX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFNRVGSDKQ
{ 
  void DWpnOkgsIf()
  { 
      bool eXRQbybCNx = false;
      bool WpJxqlKlVp = false;
      bool ESybORIGgA = false;
      bool QwdPqkiLjP = false;
      bool xyLpbhrUml = false;
      bool dtpGxLYpCJ = false;
      bool pUVNfZMtFF = false;
      bool DzBGrGHIAf = false;
      bool ZmTtVWFXSe = false;
      bool LrIaZbbxJB = false;
      bool VyPghdrjNp = false;
      bool DQpVjDBbqJ = false;
      bool UnbZsLpafP = false;
      bool eKyyJbXmLq = false;
      bool dUKbbuCmqV = false;
      bool aAGAggWomW = false;
      bool nQDxLsRqLH = false;
      bool fOPzezdzyy = false;
      bool IDjKoeDyRc = false;
      bool FhznDNQMQh = false;
      string btXtTUOlZg;
      string SwlZyEDPga;
      string NZaxbxmBTN;
      string WAUkZKFODc;
      string AwndpMEDAT;
      string UdMzVBSaSW;
      string hNRLJRaBzm;
      string ynMEaRlxGO;
      string siAAssnUPY;
      string reugumdbTY;
      string kDENUfRIXD;
      string PUTDczNQSQ;
      string dFlatTreIn;
      string mJchdpeleM;
      string afxLIXKrDw;
      string ZNIDteQcTB;
      string mlzjPFrlZm;
      string TakGoxIZSW;
      string JAbMOZAYmy;
      string YCSdYogMwC;
      if(btXtTUOlZg == kDENUfRIXD){eXRQbybCNx = true;}
      else if(kDENUfRIXD == btXtTUOlZg){VyPghdrjNp = true;}
      if(SwlZyEDPga == PUTDczNQSQ){WpJxqlKlVp = true;}
      else if(PUTDczNQSQ == SwlZyEDPga){DQpVjDBbqJ = true;}
      if(NZaxbxmBTN == dFlatTreIn){ESybORIGgA = true;}
      else if(dFlatTreIn == NZaxbxmBTN){UnbZsLpafP = true;}
      if(WAUkZKFODc == mJchdpeleM){QwdPqkiLjP = true;}
      else if(mJchdpeleM == WAUkZKFODc){eKyyJbXmLq = true;}
      if(AwndpMEDAT == afxLIXKrDw){xyLpbhrUml = true;}
      else if(afxLIXKrDw == AwndpMEDAT){dUKbbuCmqV = true;}
      if(UdMzVBSaSW == ZNIDteQcTB){dtpGxLYpCJ = true;}
      else if(ZNIDteQcTB == UdMzVBSaSW){aAGAggWomW = true;}
      if(hNRLJRaBzm == mlzjPFrlZm){pUVNfZMtFF = true;}
      else if(mlzjPFrlZm == hNRLJRaBzm){nQDxLsRqLH = true;}
      if(ynMEaRlxGO == TakGoxIZSW){DzBGrGHIAf = true;}
      if(siAAssnUPY == JAbMOZAYmy){ZmTtVWFXSe = true;}
      if(reugumdbTY == YCSdYogMwC){LrIaZbbxJB = true;}
      while(TakGoxIZSW == ynMEaRlxGO){fOPzezdzyy = true;}
      while(JAbMOZAYmy == JAbMOZAYmy){IDjKoeDyRc = true;}
      while(YCSdYogMwC == YCSdYogMwC){FhznDNQMQh = true;}
      if(eXRQbybCNx == true){eXRQbybCNx = false;}
      if(WpJxqlKlVp == true){WpJxqlKlVp = false;}
      if(ESybORIGgA == true){ESybORIGgA = false;}
      if(QwdPqkiLjP == true){QwdPqkiLjP = false;}
      if(xyLpbhrUml == true){xyLpbhrUml = false;}
      if(dtpGxLYpCJ == true){dtpGxLYpCJ = false;}
      if(pUVNfZMtFF == true){pUVNfZMtFF = false;}
      if(DzBGrGHIAf == true){DzBGrGHIAf = false;}
      if(ZmTtVWFXSe == true){ZmTtVWFXSe = false;}
      if(LrIaZbbxJB == true){LrIaZbbxJB = false;}
      if(VyPghdrjNp == true){VyPghdrjNp = false;}
      if(DQpVjDBbqJ == true){DQpVjDBbqJ = false;}
      if(UnbZsLpafP == true){UnbZsLpafP = false;}
      if(eKyyJbXmLq == true){eKyyJbXmLq = false;}
      if(dUKbbuCmqV == true){dUKbbuCmqV = false;}
      if(aAGAggWomW == true){aAGAggWomW = false;}
      if(nQDxLsRqLH == true){nQDxLsRqLH = false;}
      if(fOPzezdzyy == true){fOPzezdzyy = false;}
      if(IDjKoeDyRc == true){IDjKoeDyRc = false;}
      if(FhznDNQMQh == true){FhznDNQMQh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSOLQXHBKM
{ 
  void nrLsIpUKxr()
  { 
      bool GsgkdxcfFz = false;
      bool iXMhiMgQNS = false;
      bool rhBJJyGXwn = false;
      bool NhWtJThckY = false;
      bool tUwycmjPqF = false;
      bool DJiWxYqWae = false;
      bool qFjRlBASXO = false;
      bool eEeoXXkDgW = false;
      bool OqfqkDyAwj = false;
      bool cKBFgojeLa = false;
      bool mQqcaydtyZ = false;
      bool nnpDPAYsgh = false;
      bool DAWmlTCZHh = false;
      bool mFqFiyADPl = false;
      bool ZEBVwnUxog = false;
      bool PqxdXmsDqH = false;
      bool uElPmhwjUR = false;
      bool AVctIzyAqx = false;
      bool yEjaRuINhw = false;
      bool ExMIqURliN = false;
      string shkhDOjuwy;
      string jdMELOREUi;
      string cDyfhNPeEy;
      string AIZANshzNO;
      string IkChKfoFZh;
      string KFdifpiFzp;
      string zFpxyaDMpS;
      string gRqGarBQUC;
      string YJEWntepTX;
      string JbzXPCtEii;
      string bcPHAsOWIn;
      string oSjxQoATJE;
      string wMrSIERTpX;
      string xwhkauswVt;
      string fHhfiqrCGZ;
      string BZuemOjxzu;
      string bugjprjzVV;
      string uExOYneMjQ;
      string MONPVXACxM;
      string LwxZSjaxop;
      if(shkhDOjuwy == bcPHAsOWIn){GsgkdxcfFz = true;}
      else if(bcPHAsOWIn == shkhDOjuwy){mQqcaydtyZ = true;}
      if(jdMELOREUi == oSjxQoATJE){iXMhiMgQNS = true;}
      else if(oSjxQoATJE == jdMELOREUi){nnpDPAYsgh = true;}
      if(cDyfhNPeEy == wMrSIERTpX){rhBJJyGXwn = true;}
      else if(wMrSIERTpX == cDyfhNPeEy){DAWmlTCZHh = true;}
      if(AIZANshzNO == xwhkauswVt){NhWtJThckY = true;}
      else if(xwhkauswVt == AIZANshzNO){mFqFiyADPl = true;}
      if(IkChKfoFZh == fHhfiqrCGZ){tUwycmjPqF = true;}
      else if(fHhfiqrCGZ == IkChKfoFZh){ZEBVwnUxog = true;}
      if(KFdifpiFzp == BZuemOjxzu){DJiWxYqWae = true;}
      else if(BZuemOjxzu == KFdifpiFzp){PqxdXmsDqH = true;}
      if(zFpxyaDMpS == bugjprjzVV){qFjRlBASXO = true;}
      else if(bugjprjzVV == zFpxyaDMpS){uElPmhwjUR = true;}
      if(gRqGarBQUC == uExOYneMjQ){eEeoXXkDgW = true;}
      if(YJEWntepTX == MONPVXACxM){OqfqkDyAwj = true;}
      if(JbzXPCtEii == LwxZSjaxop){cKBFgojeLa = true;}
      while(uExOYneMjQ == gRqGarBQUC){AVctIzyAqx = true;}
      while(MONPVXACxM == MONPVXACxM){yEjaRuINhw = true;}
      while(LwxZSjaxop == LwxZSjaxop){ExMIqURliN = true;}
      if(GsgkdxcfFz == true){GsgkdxcfFz = false;}
      if(iXMhiMgQNS == true){iXMhiMgQNS = false;}
      if(rhBJJyGXwn == true){rhBJJyGXwn = false;}
      if(NhWtJThckY == true){NhWtJThckY = false;}
      if(tUwycmjPqF == true){tUwycmjPqF = false;}
      if(DJiWxYqWae == true){DJiWxYqWae = false;}
      if(qFjRlBASXO == true){qFjRlBASXO = false;}
      if(eEeoXXkDgW == true){eEeoXXkDgW = false;}
      if(OqfqkDyAwj == true){OqfqkDyAwj = false;}
      if(cKBFgojeLa == true){cKBFgojeLa = false;}
      if(mQqcaydtyZ == true){mQqcaydtyZ = false;}
      if(nnpDPAYsgh == true){nnpDPAYsgh = false;}
      if(DAWmlTCZHh == true){DAWmlTCZHh = false;}
      if(mFqFiyADPl == true){mFqFiyADPl = false;}
      if(ZEBVwnUxog == true){ZEBVwnUxog = false;}
      if(PqxdXmsDqH == true){PqxdXmsDqH = false;}
      if(uElPmhwjUR == true){uElPmhwjUR = false;}
      if(AVctIzyAqx == true){AVctIzyAqx = false;}
      if(yEjaRuINhw == true){yEjaRuINhw = false;}
      if(ExMIqURliN == true){ExMIqURliN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YPXOZAUCIT
{ 
  void ApZSwKtEag()
  { 
      bool EMAkMkikMy = false;
      bool krORIGdXIb = false;
      bool XxpXUBBQNE = false;
      bool XKLABkmUbZ = false;
      bool EWsFFehkfe = false;
      bool wfBKaGWcPL = false;
      bool jRXHaagNPW = false;
      bool SIwhWAEjSp = false;
      bool SPkhHqJBZu = false;
      bool NKEPpmzkde = false;
      bool yTUIMmjSmZ = false;
      bool BlJZsTgoAj = false;
      bool QenUIIDfri = false;
      bool BTGnqyubVT = false;
      bool HpNzsbAeWV = false;
      bool GJktNSfAzE = false;
      bool jDaDYhfVit = false;
      bool XETfcaRoag = false;
      bool HYJVcqhLZY = false;
      bool SubRjDPJZL = false;
      string VOPPqgNJXj;
      string iexVMkYHuh;
      string RlhrBjYVBM;
      string PKkEnoCrpb;
      string NybCsyhXIt;
      string gkfnLjgXOH;
      string IrILUYtrgW;
      string igRSUSJezC;
      string CAMGfdewsE;
      string IechSUpQhU;
      string EoplLzTMTr;
      string ZBXMFHeBfp;
      string sxzcNEEizA;
      string csxexMJauf;
      string KRcBdHGPcK;
      string ookraGpNXG;
      string tjMSPfDsOr;
      string xEFzebUxyF;
      string ynGoKnIFDq;
      string WwDokaEJly;
      if(VOPPqgNJXj == EoplLzTMTr){EMAkMkikMy = true;}
      else if(EoplLzTMTr == VOPPqgNJXj){yTUIMmjSmZ = true;}
      if(iexVMkYHuh == ZBXMFHeBfp){krORIGdXIb = true;}
      else if(ZBXMFHeBfp == iexVMkYHuh){BlJZsTgoAj = true;}
      if(RlhrBjYVBM == sxzcNEEizA){XxpXUBBQNE = true;}
      else if(sxzcNEEizA == RlhrBjYVBM){QenUIIDfri = true;}
      if(PKkEnoCrpb == csxexMJauf){XKLABkmUbZ = true;}
      else if(csxexMJauf == PKkEnoCrpb){BTGnqyubVT = true;}
      if(NybCsyhXIt == KRcBdHGPcK){EWsFFehkfe = true;}
      else if(KRcBdHGPcK == NybCsyhXIt){HpNzsbAeWV = true;}
      if(gkfnLjgXOH == ookraGpNXG){wfBKaGWcPL = true;}
      else if(ookraGpNXG == gkfnLjgXOH){GJktNSfAzE = true;}
      if(IrILUYtrgW == tjMSPfDsOr){jRXHaagNPW = true;}
      else if(tjMSPfDsOr == IrILUYtrgW){jDaDYhfVit = true;}
      if(igRSUSJezC == xEFzebUxyF){SIwhWAEjSp = true;}
      if(CAMGfdewsE == ynGoKnIFDq){SPkhHqJBZu = true;}
      if(IechSUpQhU == WwDokaEJly){NKEPpmzkde = true;}
      while(xEFzebUxyF == igRSUSJezC){XETfcaRoag = true;}
      while(ynGoKnIFDq == ynGoKnIFDq){HYJVcqhLZY = true;}
      while(WwDokaEJly == WwDokaEJly){SubRjDPJZL = true;}
      if(EMAkMkikMy == true){EMAkMkikMy = false;}
      if(krORIGdXIb == true){krORIGdXIb = false;}
      if(XxpXUBBQNE == true){XxpXUBBQNE = false;}
      if(XKLABkmUbZ == true){XKLABkmUbZ = false;}
      if(EWsFFehkfe == true){EWsFFehkfe = false;}
      if(wfBKaGWcPL == true){wfBKaGWcPL = false;}
      if(jRXHaagNPW == true){jRXHaagNPW = false;}
      if(SIwhWAEjSp == true){SIwhWAEjSp = false;}
      if(SPkhHqJBZu == true){SPkhHqJBZu = false;}
      if(NKEPpmzkde == true){NKEPpmzkde = false;}
      if(yTUIMmjSmZ == true){yTUIMmjSmZ = false;}
      if(BlJZsTgoAj == true){BlJZsTgoAj = false;}
      if(QenUIIDfri == true){QenUIIDfri = false;}
      if(BTGnqyubVT == true){BTGnqyubVT = false;}
      if(HpNzsbAeWV == true){HpNzsbAeWV = false;}
      if(GJktNSfAzE == true){GJktNSfAzE = false;}
      if(jDaDYhfVit == true){jDaDYhfVit = false;}
      if(XETfcaRoag == true){XETfcaRoag = false;}
      if(HYJVcqhLZY == true){HYJVcqhLZY = false;}
      if(SubRjDPJZL == true){SubRjDPJZL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAOVQQWQGZ
{ 
  void AVzeFOVkLM()
  { 
      bool FSRmYLooyf = false;
      bool PsQzbdenkK = false;
      bool fNZSojSZMZ = false;
      bool TVKTgNgfsr = false;
      bool orZWuoVmAZ = false;
      bool MSejarryyo = false;
      bool sOcXMtixSN = false;
      bool xytrUnmCWz = false;
      bool NeYlNApZro = false;
      bool UhhEzaOBKB = false;
      bool GYUlcNYlPl = false;
      bool EpayaNppKM = false;
      bool DIEcsOQpst = false;
      bool YkqVsoJlJA = false;
      bool aEKGjeGick = false;
      bool kYqyyyTrsN = false;
      bool wisVMTyFFk = false;
      bool DDgJkzxyrO = false;
      bool IhMHJAssWt = false;
      bool VRswDrKosQ = false;
      string stSDnybTKN;
      string nGAlFoQwcn;
      string lyGYGGdFNI;
      string pPxLRHcizR;
      string TjGtSBfJOt;
      string EYffOtnswg;
      string UVFCXXIoUy;
      string LgwKTBrLFF;
      string ZTpSDQiRxX;
      string TjmRwxeEWu;
      string rqoQiWbVLM;
      string BbnqGAflyG;
      string nqqxdbtdOV;
      string WnoKMieZjg;
      string oNFkVquwKu;
      string RrGPGBArlH;
      string cxGooNlcdX;
      string VFCQRakGal;
      string fySSEegYDL;
      string ilmbEqGPuH;
      if(stSDnybTKN == rqoQiWbVLM){FSRmYLooyf = true;}
      else if(rqoQiWbVLM == stSDnybTKN){GYUlcNYlPl = true;}
      if(nGAlFoQwcn == BbnqGAflyG){PsQzbdenkK = true;}
      else if(BbnqGAflyG == nGAlFoQwcn){EpayaNppKM = true;}
      if(lyGYGGdFNI == nqqxdbtdOV){fNZSojSZMZ = true;}
      else if(nqqxdbtdOV == lyGYGGdFNI){DIEcsOQpst = true;}
      if(pPxLRHcizR == WnoKMieZjg){TVKTgNgfsr = true;}
      else if(WnoKMieZjg == pPxLRHcizR){YkqVsoJlJA = true;}
      if(TjGtSBfJOt == oNFkVquwKu){orZWuoVmAZ = true;}
      else if(oNFkVquwKu == TjGtSBfJOt){aEKGjeGick = true;}
      if(EYffOtnswg == RrGPGBArlH){MSejarryyo = true;}
      else if(RrGPGBArlH == EYffOtnswg){kYqyyyTrsN = true;}
      if(UVFCXXIoUy == cxGooNlcdX){sOcXMtixSN = true;}
      else if(cxGooNlcdX == UVFCXXIoUy){wisVMTyFFk = true;}
      if(LgwKTBrLFF == VFCQRakGal){xytrUnmCWz = true;}
      if(ZTpSDQiRxX == fySSEegYDL){NeYlNApZro = true;}
      if(TjmRwxeEWu == ilmbEqGPuH){UhhEzaOBKB = true;}
      while(VFCQRakGal == LgwKTBrLFF){DDgJkzxyrO = true;}
      while(fySSEegYDL == fySSEegYDL){IhMHJAssWt = true;}
      while(ilmbEqGPuH == ilmbEqGPuH){VRswDrKosQ = true;}
      if(FSRmYLooyf == true){FSRmYLooyf = false;}
      if(PsQzbdenkK == true){PsQzbdenkK = false;}
      if(fNZSojSZMZ == true){fNZSojSZMZ = false;}
      if(TVKTgNgfsr == true){TVKTgNgfsr = false;}
      if(orZWuoVmAZ == true){orZWuoVmAZ = false;}
      if(MSejarryyo == true){MSejarryyo = false;}
      if(sOcXMtixSN == true){sOcXMtixSN = false;}
      if(xytrUnmCWz == true){xytrUnmCWz = false;}
      if(NeYlNApZro == true){NeYlNApZro = false;}
      if(UhhEzaOBKB == true){UhhEzaOBKB = false;}
      if(GYUlcNYlPl == true){GYUlcNYlPl = false;}
      if(EpayaNppKM == true){EpayaNppKM = false;}
      if(DIEcsOQpst == true){DIEcsOQpst = false;}
      if(YkqVsoJlJA == true){YkqVsoJlJA = false;}
      if(aEKGjeGick == true){aEKGjeGick = false;}
      if(kYqyyyTrsN == true){kYqyyyTrsN = false;}
      if(wisVMTyFFk == true){wisVMTyFFk = false;}
      if(DDgJkzxyrO == true){DDgJkzxyrO = false;}
      if(IhMHJAssWt == true){IhMHJAssWt = false;}
      if(VRswDrKosQ == true){VRswDrKosQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJIELHRVHQ
{ 
  void RNkBrronzf()
  { 
      bool ZRWsdGOQzJ = false;
      bool GxSEilcQpp = false;
      bool hpOFmAPVTH = false;
      bool clrzWdARnl = false;
      bool bxehDAErMR = false;
      bool KWgbejDRFc = false;
      bool pswrfTFTgF = false;
      bool kLbDOkKfBl = false;
      bool wXICwGFPTm = false;
      bool ZhLKuiAlBi = false;
      bool ukKHfztcNt = false;
      bool YWPSgSjtwZ = false;
      bool OozseCzRIf = false;
      bool jXdRqKMBVx = false;
      bool MbCZNDRrdb = false;
      bool yGpbUFlQbc = false;
      bool zcThJBrybV = false;
      bool FiXzMmmYfa = false;
      bool jHmfhdgCxl = false;
      bool YuYrxjHUQM = false;
      string mnKHekRQOd;
      string aDdwQdYCmV;
      string sQwCGMQRxu;
      string xQlLZhHgpt;
      string etqAWxlSaV;
      string MptkEVrHBS;
      string UATSfJQRWh;
      string VqMrpyZufI;
      string axpahGWBGD;
      string pAfWYdZXUM;
      string gTwrAUdBuG;
      string wwarrXKsjY;
      string lPLSqULoSM;
      string YBaSbGAxaM;
      string cVFAHtZneB;
      string TgnuaQIdBe;
      string JnhihuUHQk;
      string XMRWwQJKLw;
      string uXKRrqNerK;
      string yWwwDnmWSM;
      if(mnKHekRQOd == gTwrAUdBuG){ZRWsdGOQzJ = true;}
      else if(gTwrAUdBuG == mnKHekRQOd){ukKHfztcNt = true;}
      if(aDdwQdYCmV == wwarrXKsjY){GxSEilcQpp = true;}
      else if(wwarrXKsjY == aDdwQdYCmV){YWPSgSjtwZ = true;}
      if(sQwCGMQRxu == lPLSqULoSM){hpOFmAPVTH = true;}
      else if(lPLSqULoSM == sQwCGMQRxu){OozseCzRIf = true;}
      if(xQlLZhHgpt == YBaSbGAxaM){clrzWdARnl = true;}
      else if(YBaSbGAxaM == xQlLZhHgpt){jXdRqKMBVx = true;}
      if(etqAWxlSaV == cVFAHtZneB){bxehDAErMR = true;}
      else if(cVFAHtZneB == etqAWxlSaV){MbCZNDRrdb = true;}
      if(MptkEVrHBS == TgnuaQIdBe){KWgbejDRFc = true;}
      else if(TgnuaQIdBe == MptkEVrHBS){yGpbUFlQbc = true;}
      if(UATSfJQRWh == JnhihuUHQk){pswrfTFTgF = true;}
      else if(JnhihuUHQk == UATSfJQRWh){zcThJBrybV = true;}
      if(VqMrpyZufI == XMRWwQJKLw){kLbDOkKfBl = true;}
      if(axpahGWBGD == uXKRrqNerK){wXICwGFPTm = true;}
      if(pAfWYdZXUM == yWwwDnmWSM){ZhLKuiAlBi = true;}
      while(XMRWwQJKLw == VqMrpyZufI){FiXzMmmYfa = true;}
      while(uXKRrqNerK == uXKRrqNerK){jHmfhdgCxl = true;}
      while(yWwwDnmWSM == yWwwDnmWSM){YuYrxjHUQM = true;}
      if(ZRWsdGOQzJ == true){ZRWsdGOQzJ = false;}
      if(GxSEilcQpp == true){GxSEilcQpp = false;}
      if(hpOFmAPVTH == true){hpOFmAPVTH = false;}
      if(clrzWdARnl == true){clrzWdARnl = false;}
      if(bxehDAErMR == true){bxehDAErMR = false;}
      if(KWgbejDRFc == true){KWgbejDRFc = false;}
      if(pswrfTFTgF == true){pswrfTFTgF = false;}
      if(kLbDOkKfBl == true){kLbDOkKfBl = false;}
      if(wXICwGFPTm == true){wXICwGFPTm = false;}
      if(ZhLKuiAlBi == true){ZhLKuiAlBi = false;}
      if(ukKHfztcNt == true){ukKHfztcNt = false;}
      if(YWPSgSjtwZ == true){YWPSgSjtwZ = false;}
      if(OozseCzRIf == true){OozseCzRIf = false;}
      if(jXdRqKMBVx == true){jXdRqKMBVx = false;}
      if(MbCZNDRrdb == true){MbCZNDRrdb = false;}
      if(yGpbUFlQbc == true){yGpbUFlQbc = false;}
      if(zcThJBrybV == true){zcThJBrybV = false;}
      if(FiXzMmmYfa == true){FiXzMmmYfa = false;}
      if(jHmfhdgCxl == true){jHmfhdgCxl = false;}
      if(YuYrxjHUQM == true){YuYrxjHUQM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKUFLQFLPA
{ 
  void wWcMHAxUHN()
  { 
      bool NgPCgBXJgJ = false;
      bool IyCYjnnqxS = false;
      bool wnFGeZJEyy = false;
      bool fMRsJWKAnn = false;
      bool nBBVhDKIFU = false;
      bool dAxLIZbIXG = false;
      bool qTLhcufJPM = false;
      bool cmCIetljYa = false;
      bool OAycUeOGjj = false;
      bool uCchwTpSrl = false;
      bool WBssqpxnfO = false;
      bool mrjwrqVhNx = false;
      bool fZZfRaKUML = false;
      bool ETqlENHFle = false;
      bool haZUwCRfpF = false;
      bool yHFtFwaMbQ = false;
      bool ecbUJTAxrd = false;
      bool iQwiPFAEiO = false;
      bool IeeGMwOxfH = false;
      bool ltcUzEyELc = false;
      string XCAPxTmEla;
      string QKaEucjhNT;
      string cTraCXqhoh;
      string NbVAzyoejA;
      string UGylBraQzz;
      string IaRTgEJYNY;
      string cFOENnoZFw;
      string mFxNzVVFZJ;
      string wZhpZmJBTt;
      string nQQLWPqtYM;
      string DALDLCcEUK;
      string hEyDbCWYdZ;
      string dnGKHWnlpi;
      string eagNGwOedW;
      string JFgJMjRNiU;
      string sSPyhPtAwn;
      string OqNleHWkxf;
      string nrtGQYGwyW;
      string EaDVoMKiep;
      string BNhpIRrteF;
      if(XCAPxTmEla == DALDLCcEUK){NgPCgBXJgJ = true;}
      else if(DALDLCcEUK == XCAPxTmEla){WBssqpxnfO = true;}
      if(QKaEucjhNT == hEyDbCWYdZ){IyCYjnnqxS = true;}
      else if(hEyDbCWYdZ == QKaEucjhNT){mrjwrqVhNx = true;}
      if(cTraCXqhoh == dnGKHWnlpi){wnFGeZJEyy = true;}
      else if(dnGKHWnlpi == cTraCXqhoh){fZZfRaKUML = true;}
      if(NbVAzyoejA == eagNGwOedW){fMRsJWKAnn = true;}
      else if(eagNGwOedW == NbVAzyoejA){ETqlENHFle = true;}
      if(UGylBraQzz == JFgJMjRNiU){nBBVhDKIFU = true;}
      else if(JFgJMjRNiU == UGylBraQzz){haZUwCRfpF = true;}
      if(IaRTgEJYNY == sSPyhPtAwn){dAxLIZbIXG = true;}
      else if(sSPyhPtAwn == IaRTgEJYNY){yHFtFwaMbQ = true;}
      if(cFOENnoZFw == OqNleHWkxf){qTLhcufJPM = true;}
      else if(OqNleHWkxf == cFOENnoZFw){ecbUJTAxrd = true;}
      if(mFxNzVVFZJ == nrtGQYGwyW){cmCIetljYa = true;}
      if(wZhpZmJBTt == EaDVoMKiep){OAycUeOGjj = true;}
      if(nQQLWPqtYM == BNhpIRrteF){uCchwTpSrl = true;}
      while(nrtGQYGwyW == mFxNzVVFZJ){iQwiPFAEiO = true;}
      while(EaDVoMKiep == EaDVoMKiep){IeeGMwOxfH = true;}
      while(BNhpIRrteF == BNhpIRrteF){ltcUzEyELc = true;}
      if(NgPCgBXJgJ == true){NgPCgBXJgJ = false;}
      if(IyCYjnnqxS == true){IyCYjnnqxS = false;}
      if(wnFGeZJEyy == true){wnFGeZJEyy = false;}
      if(fMRsJWKAnn == true){fMRsJWKAnn = false;}
      if(nBBVhDKIFU == true){nBBVhDKIFU = false;}
      if(dAxLIZbIXG == true){dAxLIZbIXG = false;}
      if(qTLhcufJPM == true){qTLhcufJPM = false;}
      if(cmCIetljYa == true){cmCIetljYa = false;}
      if(OAycUeOGjj == true){OAycUeOGjj = false;}
      if(uCchwTpSrl == true){uCchwTpSrl = false;}
      if(WBssqpxnfO == true){WBssqpxnfO = false;}
      if(mrjwrqVhNx == true){mrjwrqVhNx = false;}
      if(fZZfRaKUML == true){fZZfRaKUML = false;}
      if(ETqlENHFle == true){ETqlENHFle = false;}
      if(haZUwCRfpF == true){haZUwCRfpF = false;}
      if(yHFtFwaMbQ == true){yHFtFwaMbQ = false;}
      if(ecbUJTAxrd == true){ecbUJTAxrd = false;}
      if(iQwiPFAEiO == true){iQwiPFAEiO = false;}
      if(IeeGMwOxfH == true){IeeGMwOxfH = false;}
      if(ltcUzEyELc == true){ltcUzEyELc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYMKFAYLRC
{ 
  void CqiXwXYdIc()
  { 
      bool fpPoEUuUjW = false;
      bool zltBDGxdgb = false;
      bool MAcsJjPynf = false;
      bool QMqgrSKoXg = false;
      bool EPlMEyDoLw = false;
      bool mRgOEeNVfT = false;
      bool FwfEFluMJj = false;
      bool uHFAXwNPnK = false;
      bool gZmqrzfbcM = false;
      bool FoJEaHihHS = false;
      bool DqfaAeLfqH = false;
      bool QygVleJnMG = false;
      bool GSjweGxBYP = false;
      bool MfIVGptLqM = false;
      bool nzkUwGHnRw = false;
      bool xuVBLkGiut = false;
      bool gJGaukoKPw = false;
      bool kxxzRHhOAX = false;
      bool yJjcRRJHKU = false;
      bool iKPwedrJYK = false;
      string qLsiWDeRrV;
      string AhDRTZoAIP;
      string BJNxUzfpXJ;
      string nQyyrudHFh;
      string msWLglZhYV;
      string DktnthxuNX;
      string XnshgjjEZY;
      string uhuZbIlCPi;
      string YyQCGDVJEK;
      string yisgKyznex;
      string BUHAZVpULk;
      string uueeyYWpbd;
      string NZAOaMnNOc;
      string JxXSgEpQbj;
      string NBySPDDNil;
      string aJMAibTsZN;
      string gbFibxWMyt;
      string hGNqQMbhzX;
      string JaebBzkWjE;
      string kxqODkuOqR;
      if(qLsiWDeRrV == BUHAZVpULk){fpPoEUuUjW = true;}
      else if(BUHAZVpULk == qLsiWDeRrV){DqfaAeLfqH = true;}
      if(AhDRTZoAIP == uueeyYWpbd){zltBDGxdgb = true;}
      else if(uueeyYWpbd == AhDRTZoAIP){QygVleJnMG = true;}
      if(BJNxUzfpXJ == NZAOaMnNOc){MAcsJjPynf = true;}
      else if(NZAOaMnNOc == BJNxUzfpXJ){GSjweGxBYP = true;}
      if(nQyyrudHFh == JxXSgEpQbj){QMqgrSKoXg = true;}
      else if(JxXSgEpQbj == nQyyrudHFh){MfIVGptLqM = true;}
      if(msWLglZhYV == NBySPDDNil){EPlMEyDoLw = true;}
      else if(NBySPDDNil == msWLglZhYV){nzkUwGHnRw = true;}
      if(DktnthxuNX == aJMAibTsZN){mRgOEeNVfT = true;}
      else if(aJMAibTsZN == DktnthxuNX){xuVBLkGiut = true;}
      if(XnshgjjEZY == gbFibxWMyt){FwfEFluMJj = true;}
      else if(gbFibxWMyt == XnshgjjEZY){gJGaukoKPw = true;}
      if(uhuZbIlCPi == hGNqQMbhzX){uHFAXwNPnK = true;}
      if(YyQCGDVJEK == JaebBzkWjE){gZmqrzfbcM = true;}
      if(yisgKyznex == kxqODkuOqR){FoJEaHihHS = true;}
      while(hGNqQMbhzX == uhuZbIlCPi){kxxzRHhOAX = true;}
      while(JaebBzkWjE == JaebBzkWjE){yJjcRRJHKU = true;}
      while(kxqODkuOqR == kxqODkuOqR){iKPwedrJYK = true;}
      if(fpPoEUuUjW == true){fpPoEUuUjW = false;}
      if(zltBDGxdgb == true){zltBDGxdgb = false;}
      if(MAcsJjPynf == true){MAcsJjPynf = false;}
      if(QMqgrSKoXg == true){QMqgrSKoXg = false;}
      if(EPlMEyDoLw == true){EPlMEyDoLw = false;}
      if(mRgOEeNVfT == true){mRgOEeNVfT = false;}
      if(FwfEFluMJj == true){FwfEFluMJj = false;}
      if(uHFAXwNPnK == true){uHFAXwNPnK = false;}
      if(gZmqrzfbcM == true){gZmqrzfbcM = false;}
      if(FoJEaHihHS == true){FoJEaHihHS = false;}
      if(DqfaAeLfqH == true){DqfaAeLfqH = false;}
      if(QygVleJnMG == true){QygVleJnMG = false;}
      if(GSjweGxBYP == true){GSjweGxBYP = false;}
      if(MfIVGptLqM == true){MfIVGptLqM = false;}
      if(nzkUwGHnRw == true){nzkUwGHnRw = false;}
      if(xuVBLkGiut == true){xuVBLkGiut = false;}
      if(gJGaukoKPw == true){gJGaukoKPw = false;}
      if(kxxzRHhOAX == true){kxxzRHhOAX = false;}
      if(yJjcRRJHKU == true){yJjcRRJHKU = false;}
      if(iKPwedrJYK == true){iKPwedrJYK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQODLXRKRD
{ 
  void LVnhcHXbRi()
  { 
      bool EEyLelHLDX = false;
      bool NpqXqZzoqP = false;
      bool PnjMRRQUEc = false;
      bool nwWuDCqDJk = false;
      bool NxEbBEPSOj = false;
      bool wiXZCQTksN = false;
      bool UmGajRTwUo = false;
      bool hueGBSiIKN = false;
      bool ByGTfEYwsm = false;
      bool hFJwPapdqj = false;
      bool jSyZCADQXj = false;
      bool hLZfLWflte = false;
      bool rXDgGbkhqa = false;
      bool bFQadiAfRe = false;
      bool AHXJFWfdjs = false;
      bool tDiMqLPQSZ = false;
      bool PUZxHbtzCc = false;
      bool VATOdjAsbj = false;
      bool wHxxfXVEiR = false;
      bool SjNrPfhZBc = false;
      string fgOCmgCRzd;
      string KpcOLLgIUT;
      string ETBObldErA;
      string jYmXLPIUko;
      string ZmQEhTwKnu;
      string rYBaGLezaB;
      string CxZyskCFCu;
      string DLXetQCwfH;
      string oSQwHLXLQz;
      string jItjmbMRKw;
      string RqHrrgBVgo;
      string IhTSLigdph;
      string NqnDKuQmrR;
      string EjkipyLYDa;
      string JBeapBnaYD;
      string thbciZDEgx;
      string PNdOkYwjcM;
      string XIaPYLMMMI;
      string GpOoWVIIzP;
      string uGqFKuXPpR;
      if(fgOCmgCRzd == RqHrrgBVgo){EEyLelHLDX = true;}
      else if(RqHrrgBVgo == fgOCmgCRzd){jSyZCADQXj = true;}
      if(KpcOLLgIUT == IhTSLigdph){NpqXqZzoqP = true;}
      else if(IhTSLigdph == KpcOLLgIUT){hLZfLWflte = true;}
      if(ETBObldErA == NqnDKuQmrR){PnjMRRQUEc = true;}
      else if(NqnDKuQmrR == ETBObldErA){rXDgGbkhqa = true;}
      if(jYmXLPIUko == EjkipyLYDa){nwWuDCqDJk = true;}
      else if(EjkipyLYDa == jYmXLPIUko){bFQadiAfRe = true;}
      if(ZmQEhTwKnu == JBeapBnaYD){NxEbBEPSOj = true;}
      else if(JBeapBnaYD == ZmQEhTwKnu){AHXJFWfdjs = true;}
      if(rYBaGLezaB == thbciZDEgx){wiXZCQTksN = true;}
      else if(thbciZDEgx == rYBaGLezaB){tDiMqLPQSZ = true;}
      if(CxZyskCFCu == PNdOkYwjcM){UmGajRTwUo = true;}
      else if(PNdOkYwjcM == CxZyskCFCu){PUZxHbtzCc = true;}
      if(DLXetQCwfH == XIaPYLMMMI){hueGBSiIKN = true;}
      if(oSQwHLXLQz == GpOoWVIIzP){ByGTfEYwsm = true;}
      if(jItjmbMRKw == uGqFKuXPpR){hFJwPapdqj = true;}
      while(XIaPYLMMMI == DLXetQCwfH){VATOdjAsbj = true;}
      while(GpOoWVIIzP == GpOoWVIIzP){wHxxfXVEiR = true;}
      while(uGqFKuXPpR == uGqFKuXPpR){SjNrPfhZBc = true;}
      if(EEyLelHLDX == true){EEyLelHLDX = false;}
      if(NpqXqZzoqP == true){NpqXqZzoqP = false;}
      if(PnjMRRQUEc == true){PnjMRRQUEc = false;}
      if(nwWuDCqDJk == true){nwWuDCqDJk = false;}
      if(NxEbBEPSOj == true){NxEbBEPSOj = false;}
      if(wiXZCQTksN == true){wiXZCQTksN = false;}
      if(UmGajRTwUo == true){UmGajRTwUo = false;}
      if(hueGBSiIKN == true){hueGBSiIKN = false;}
      if(ByGTfEYwsm == true){ByGTfEYwsm = false;}
      if(hFJwPapdqj == true){hFJwPapdqj = false;}
      if(jSyZCADQXj == true){jSyZCADQXj = false;}
      if(hLZfLWflte == true){hLZfLWflte = false;}
      if(rXDgGbkhqa == true){rXDgGbkhqa = false;}
      if(bFQadiAfRe == true){bFQadiAfRe = false;}
      if(AHXJFWfdjs == true){AHXJFWfdjs = false;}
      if(tDiMqLPQSZ == true){tDiMqLPQSZ = false;}
      if(PUZxHbtzCc == true){PUZxHbtzCc = false;}
      if(VATOdjAsbj == true){VATOdjAsbj = false;}
      if(wHxxfXVEiR == true){wHxxfXVEiR = false;}
      if(SjNrPfhZBc == true){SjNrPfhZBc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ATONVQQOTS
{ 
  void uYzspsHexL()
  { 
      bool utydQdWNiK = false;
      bool EzJMoUFCmM = false;
      bool JbrBWBJGZy = false;
      bool hXQgXXFqTA = false;
      bool jnaedLIRWh = false;
      bool aLaJRSCwGO = false;
      bool UQnjbgibnR = false;
      bool POhlcUBMXL = false;
      bool sriqXWxGPF = false;
      bool UJjFfSAqCx = false;
      bool bfcFSMcngw = false;
      bool RoYuVbhwLE = false;
      bool jcMiwGdcGK = false;
      bool UKKaiNOcYK = false;
      bool tIZSnekojD = false;
      bool kEeyMyStJL = false;
      bool hAhVbGexLH = false;
      bool NEWBKaDtuQ = false;
      bool VosCYPfLNk = false;
      bool tUTMbsaDqg = false;
      string OYrzZLFrTB;
      string irsVXmNPFS;
      string VYlMIaFQdb;
      string wbbEhekiqu;
      string EslILZIDZF;
      string ofSdupmeqz;
      string GnNqEHQonr;
      string BdYKNclcBh;
      string RBqYmPJxJq;
      string rGqroPetDE;
      string JSPgDKHIQR;
      string DKdJgFxoEo;
      string xSewAulfUx;
      string xrYwYykJVb;
      string IBgqmgbhLj;
      string RppOGpnSfI;
      string YamSTLlgjh;
      string TnSbfwlnJT;
      string SDUkeGBJoh;
      string KRdMCgNNWb;
      if(OYrzZLFrTB == JSPgDKHIQR){utydQdWNiK = true;}
      else if(JSPgDKHIQR == OYrzZLFrTB){bfcFSMcngw = true;}
      if(irsVXmNPFS == DKdJgFxoEo){EzJMoUFCmM = true;}
      else if(DKdJgFxoEo == irsVXmNPFS){RoYuVbhwLE = true;}
      if(VYlMIaFQdb == xSewAulfUx){JbrBWBJGZy = true;}
      else if(xSewAulfUx == VYlMIaFQdb){jcMiwGdcGK = true;}
      if(wbbEhekiqu == xrYwYykJVb){hXQgXXFqTA = true;}
      else if(xrYwYykJVb == wbbEhekiqu){UKKaiNOcYK = true;}
      if(EslILZIDZF == IBgqmgbhLj){jnaedLIRWh = true;}
      else if(IBgqmgbhLj == EslILZIDZF){tIZSnekojD = true;}
      if(ofSdupmeqz == RppOGpnSfI){aLaJRSCwGO = true;}
      else if(RppOGpnSfI == ofSdupmeqz){kEeyMyStJL = true;}
      if(GnNqEHQonr == YamSTLlgjh){UQnjbgibnR = true;}
      else if(YamSTLlgjh == GnNqEHQonr){hAhVbGexLH = true;}
      if(BdYKNclcBh == TnSbfwlnJT){POhlcUBMXL = true;}
      if(RBqYmPJxJq == SDUkeGBJoh){sriqXWxGPF = true;}
      if(rGqroPetDE == KRdMCgNNWb){UJjFfSAqCx = true;}
      while(TnSbfwlnJT == BdYKNclcBh){NEWBKaDtuQ = true;}
      while(SDUkeGBJoh == SDUkeGBJoh){VosCYPfLNk = true;}
      while(KRdMCgNNWb == KRdMCgNNWb){tUTMbsaDqg = true;}
      if(utydQdWNiK == true){utydQdWNiK = false;}
      if(EzJMoUFCmM == true){EzJMoUFCmM = false;}
      if(JbrBWBJGZy == true){JbrBWBJGZy = false;}
      if(hXQgXXFqTA == true){hXQgXXFqTA = false;}
      if(jnaedLIRWh == true){jnaedLIRWh = false;}
      if(aLaJRSCwGO == true){aLaJRSCwGO = false;}
      if(UQnjbgibnR == true){UQnjbgibnR = false;}
      if(POhlcUBMXL == true){POhlcUBMXL = false;}
      if(sriqXWxGPF == true){sriqXWxGPF = false;}
      if(UJjFfSAqCx == true){UJjFfSAqCx = false;}
      if(bfcFSMcngw == true){bfcFSMcngw = false;}
      if(RoYuVbhwLE == true){RoYuVbhwLE = false;}
      if(jcMiwGdcGK == true){jcMiwGdcGK = false;}
      if(UKKaiNOcYK == true){UKKaiNOcYK = false;}
      if(tIZSnekojD == true){tIZSnekojD = false;}
      if(kEeyMyStJL == true){kEeyMyStJL = false;}
      if(hAhVbGexLH == true){hAhVbGexLH = false;}
      if(NEWBKaDtuQ == true){NEWBKaDtuQ = false;}
      if(VosCYPfLNk == true){VosCYPfLNk = false;}
      if(tUTMbsaDqg == true){tUTMbsaDqg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JVBQPQFBKN
{ 
  void hbWLVJYNTV()
  { 
      bool iRkqVIjhit = false;
      bool lGkLDqiqIf = false;
      bool QxCbZJNlcF = false;
      bool FQaoWGiHxe = false;
      bool OrBkFnNXZB = false;
      bool CPzCKlOIRM = false;
      bool txFcnUewox = false;
      bool HbsdRYuRWk = false;
      bool uoMaDpRXek = false;
      bool qaokjRlXwj = false;
      bool JRicsZVVkl = false;
      bool pxkgQFjdYx = false;
      bool CHQDFglIsz = false;
      bool lXUladFjgc = false;
      bool UwmrttoITe = false;
      bool gHyygBAeWM = false;
      bool nNblzSbyFm = false;
      bool zAwucGTXIK = false;
      bool qdnORdYWFZ = false;
      bool dZMUoGTAsb = false;
      string agJbuqHcmc;
      string gOMoUGrjWF;
      string XyxQKKuMzY;
      string IZntRqNrej;
      string CBpErQIITs;
      string kxxsBcjsQj;
      string utdNUGZRXd;
      string rAEmCWHsXt;
      string ClsGnLbusn;
      string HUatnIXcik;
      string ppkoAjrKpe;
      string VqUWhJBWYJ;
      string deYiWXYKzt;
      string zdJlDMBDGD;
      string SREOSQzEMe;
      string GADZGLQBSb;
      string LgLweqghTU;
      string IyQUqMZKQG;
      string XTyTmyajeq;
      string uzjdrkGIia;
      if(agJbuqHcmc == ppkoAjrKpe){iRkqVIjhit = true;}
      else if(ppkoAjrKpe == agJbuqHcmc){JRicsZVVkl = true;}
      if(gOMoUGrjWF == VqUWhJBWYJ){lGkLDqiqIf = true;}
      else if(VqUWhJBWYJ == gOMoUGrjWF){pxkgQFjdYx = true;}
      if(XyxQKKuMzY == deYiWXYKzt){QxCbZJNlcF = true;}
      else if(deYiWXYKzt == XyxQKKuMzY){CHQDFglIsz = true;}
      if(IZntRqNrej == zdJlDMBDGD){FQaoWGiHxe = true;}
      else if(zdJlDMBDGD == IZntRqNrej){lXUladFjgc = true;}
      if(CBpErQIITs == SREOSQzEMe){OrBkFnNXZB = true;}
      else if(SREOSQzEMe == CBpErQIITs){UwmrttoITe = true;}
      if(kxxsBcjsQj == GADZGLQBSb){CPzCKlOIRM = true;}
      else if(GADZGLQBSb == kxxsBcjsQj){gHyygBAeWM = true;}
      if(utdNUGZRXd == LgLweqghTU){txFcnUewox = true;}
      else if(LgLweqghTU == utdNUGZRXd){nNblzSbyFm = true;}
      if(rAEmCWHsXt == IyQUqMZKQG){HbsdRYuRWk = true;}
      if(ClsGnLbusn == XTyTmyajeq){uoMaDpRXek = true;}
      if(HUatnIXcik == uzjdrkGIia){qaokjRlXwj = true;}
      while(IyQUqMZKQG == rAEmCWHsXt){zAwucGTXIK = true;}
      while(XTyTmyajeq == XTyTmyajeq){qdnORdYWFZ = true;}
      while(uzjdrkGIia == uzjdrkGIia){dZMUoGTAsb = true;}
      if(iRkqVIjhit == true){iRkqVIjhit = false;}
      if(lGkLDqiqIf == true){lGkLDqiqIf = false;}
      if(QxCbZJNlcF == true){QxCbZJNlcF = false;}
      if(FQaoWGiHxe == true){FQaoWGiHxe = false;}
      if(OrBkFnNXZB == true){OrBkFnNXZB = false;}
      if(CPzCKlOIRM == true){CPzCKlOIRM = false;}
      if(txFcnUewox == true){txFcnUewox = false;}
      if(HbsdRYuRWk == true){HbsdRYuRWk = false;}
      if(uoMaDpRXek == true){uoMaDpRXek = false;}
      if(qaokjRlXwj == true){qaokjRlXwj = false;}
      if(JRicsZVVkl == true){JRicsZVVkl = false;}
      if(pxkgQFjdYx == true){pxkgQFjdYx = false;}
      if(CHQDFglIsz == true){CHQDFglIsz = false;}
      if(lXUladFjgc == true){lXUladFjgc = false;}
      if(UwmrttoITe == true){UwmrttoITe = false;}
      if(gHyygBAeWM == true){gHyygBAeWM = false;}
      if(nNblzSbyFm == true){nNblzSbyFm = false;}
      if(zAwucGTXIK == true){zAwucGTXIK = false;}
      if(qdnORdYWFZ == true){qdnORdYWFZ = false;}
      if(dZMUoGTAsb == true){dZMUoGTAsb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFZOKEOTXI
{ 
  void TakjfIuuam()
  { 
      bool RcXnEupGaL = false;
      bool oIJXZiTYgF = false;
      bool BXwQcymwgm = false;
      bool qtxdasNiUJ = false;
      bool hXSbfzMTDx = false;
      bool cnwcPsfGLG = false;
      bool HtYmTtLexg = false;
      bool VkEWWcFUjd = false;
      bool kTsjJDxUOh = false;
      bool MGXNBnzeHl = false;
      bool mgWVariZFl = false;
      bool nLWgUnAodQ = false;
      bool wqQPTPMpVi = false;
      bool dZNypExWIQ = false;
      bool TXObtBjprN = false;
      bool mJBppwPGCL = false;
      bool esDWHNyYpQ = false;
      bool qdgNwXboVR = false;
      bool fWxIuUYWHt = false;
      bool npTwkaUrUf = false;
      string IjPPmGZWqY;
      string yWaIzHPUCK;
      string ZxZqJdofSK;
      string WYAEnQYmQk;
      string LUPlGXCRcN;
      string rsPRYLKYGI;
      string RsEgCZWWUi;
      string ibERyFgnkk;
      string bWDERcJheb;
      string GAfHSRPijg;
      string BexteQoxST;
      string eVnVgtpzOY;
      string Pnqrchuxyg;
      string oyEDiwZJZB;
      string nLPLxjMKZY;
      string bQTKQNnEQw;
      string UqyldfRjlk;
      string TfZNjEYeus;
      string VkXZFYdsmV;
      string HVrcfxMdhQ;
      if(IjPPmGZWqY == BexteQoxST){RcXnEupGaL = true;}
      else if(BexteQoxST == IjPPmGZWqY){mgWVariZFl = true;}
      if(yWaIzHPUCK == eVnVgtpzOY){oIJXZiTYgF = true;}
      else if(eVnVgtpzOY == yWaIzHPUCK){nLWgUnAodQ = true;}
      if(ZxZqJdofSK == Pnqrchuxyg){BXwQcymwgm = true;}
      else if(Pnqrchuxyg == ZxZqJdofSK){wqQPTPMpVi = true;}
      if(WYAEnQYmQk == oyEDiwZJZB){qtxdasNiUJ = true;}
      else if(oyEDiwZJZB == WYAEnQYmQk){dZNypExWIQ = true;}
      if(LUPlGXCRcN == nLPLxjMKZY){hXSbfzMTDx = true;}
      else if(nLPLxjMKZY == LUPlGXCRcN){TXObtBjprN = true;}
      if(rsPRYLKYGI == bQTKQNnEQw){cnwcPsfGLG = true;}
      else if(bQTKQNnEQw == rsPRYLKYGI){mJBppwPGCL = true;}
      if(RsEgCZWWUi == UqyldfRjlk){HtYmTtLexg = true;}
      else if(UqyldfRjlk == RsEgCZWWUi){esDWHNyYpQ = true;}
      if(ibERyFgnkk == TfZNjEYeus){VkEWWcFUjd = true;}
      if(bWDERcJheb == VkXZFYdsmV){kTsjJDxUOh = true;}
      if(GAfHSRPijg == HVrcfxMdhQ){MGXNBnzeHl = true;}
      while(TfZNjEYeus == ibERyFgnkk){qdgNwXboVR = true;}
      while(VkXZFYdsmV == VkXZFYdsmV){fWxIuUYWHt = true;}
      while(HVrcfxMdhQ == HVrcfxMdhQ){npTwkaUrUf = true;}
      if(RcXnEupGaL == true){RcXnEupGaL = false;}
      if(oIJXZiTYgF == true){oIJXZiTYgF = false;}
      if(BXwQcymwgm == true){BXwQcymwgm = false;}
      if(qtxdasNiUJ == true){qtxdasNiUJ = false;}
      if(hXSbfzMTDx == true){hXSbfzMTDx = false;}
      if(cnwcPsfGLG == true){cnwcPsfGLG = false;}
      if(HtYmTtLexg == true){HtYmTtLexg = false;}
      if(VkEWWcFUjd == true){VkEWWcFUjd = false;}
      if(kTsjJDxUOh == true){kTsjJDxUOh = false;}
      if(MGXNBnzeHl == true){MGXNBnzeHl = false;}
      if(mgWVariZFl == true){mgWVariZFl = false;}
      if(nLWgUnAodQ == true){nLWgUnAodQ = false;}
      if(wqQPTPMpVi == true){wqQPTPMpVi = false;}
      if(dZNypExWIQ == true){dZNypExWIQ = false;}
      if(TXObtBjprN == true){TXObtBjprN = false;}
      if(mJBppwPGCL == true){mJBppwPGCL = false;}
      if(esDWHNyYpQ == true){esDWHNyYpQ = false;}
      if(qdgNwXboVR == true){qdgNwXboVR = false;}
      if(fWxIuUYWHt == true){fWxIuUYWHt = false;}
      if(npTwkaUrUf == true){npTwkaUrUf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSNWVNZFTD
{ 
  void ieBZNAebLO()
  { 
      bool uccYlxBBIe = false;
      bool tzEWNKLmyk = false;
      bool BLoLoItJWx = false;
      bool MAyxjronFc = false;
      bool lYEuVHolUf = false;
      bool FFOeDimQjc = false;
      bool DrdLSsAGlV = false;
      bool VWhVycHtph = false;
      bool THnpqGlTtA = false;
      bool EXEbYttrbb = false;
      bool HizyKiXrfZ = false;
      bool bsaCJuEmUM = false;
      bool HfMlRxSFwE = false;
      bool iOSOZjHofI = false;
      bool hsnUYLxCSd = false;
      bool pHXPUaWNgN = false;
      bool PRuaqMZLbY = false;
      bool mOHMdNqrMG = false;
      bool zPmSObqCsz = false;
      bool NsHSrQyNcL = false;
      string tPFJtKOVCg;
      string gOfjgAPGKc;
      string RprEbtPpuy;
      string cSbjCCTmkm;
      string mfCeduKXee;
      string cdioqEWAgz;
      string uYaEDOluge;
      string gcUXolmMag;
      string iqKPUzilsx;
      string eSFkrOEybP;
      string IPpAxAIKAF;
      string QKZAPDNKiE;
      string eACjzNWifa;
      string gokKXTAKSU;
      string pYlngUsEVn;
      string AsPWkINGBi;
      string cYeYXbZPbw;
      string CDrONFNOCe;
      string URNqZmZNZP;
      string GsIiqQsNPF;
      if(tPFJtKOVCg == IPpAxAIKAF){uccYlxBBIe = true;}
      else if(IPpAxAIKAF == tPFJtKOVCg){HizyKiXrfZ = true;}
      if(gOfjgAPGKc == QKZAPDNKiE){tzEWNKLmyk = true;}
      else if(QKZAPDNKiE == gOfjgAPGKc){bsaCJuEmUM = true;}
      if(RprEbtPpuy == eACjzNWifa){BLoLoItJWx = true;}
      else if(eACjzNWifa == RprEbtPpuy){HfMlRxSFwE = true;}
      if(cSbjCCTmkm == gokKXTAKSU){MAyxjronFc = true;}
      else if(gokKXTAKSU == cSbjCCTmkm){iOSOZjHofI = true;}
      if(mfCeduKXee == pYlngUsEVn){lYEuVHolUf = true;}
      else if(pYlngUsEVn == mfCeduKXee){hsnUYLxCSd = true;}
      if(cdioqEWAgz == AsPWkINGBi){FFOeDimQjc = true;}
      else if(AsPWkINGBi == cdioqEWAgz){pHXPUaWNgN = true;}
      if(uYaEDOluge == cYeYXbZPbw){DrdLSsAGlV = true;}
      else if(cYeYXbZPbw == uYaEDOluge){PRuaqMZLbY = true;}
      if(gcUXolmMag == CDrONFNOCe){VWhVycHtph = true;}
      if(iqKPUzilsx == URNqZmZNZP){THnpqGlTtA = true;}
      if(eSFkrOEybP == GsIiqQsNPF){EXEbYttrbb = true;}
      while(CDrONFNOCe == gcUXolmMag){mOHMdNqrMG = true;}
      while(URNqZmZNZP == URNqZmZNZP){zPmSObqCsz = true;}
      while(GsIiqQsNPF == GsIiqQsNPF){NsHSrQyNcL = true;}
      if(uccYlxBBIe == true){uccYlxBBIe = false;}
      if(tzEWNKLmyk == true){tzEWNKLmyk = false;}
      if(BLoLoItJWx == true){BLoLoItJWx = false;}
      if(MAyxjronFc == true){MAyxjronFc = false;}
      if(lYEuVHolUf == true){lYEuVHolUf = false;}
      if(FFOeDimQjc == true){FFOeDimQjc = false;}
      if(DrdLSsAGlV == true){DrdLSsAGlV = false;}
      if(VWhVycHtph == true){VWhVycHtph = false;}
      if(THnpqGlTtA == true){THnpqGlTtA = false;}
      if(EXEbYttrbb == true){EXEbYttrbb = false;}
      if(HizyKiXrfZ == true){HizyKiXrfZ = false;}
      if(bsaCJuEmUM == true){bsaCJuEmUM = false;}
      if(HfMlRxSFwE == true){HfMlRxSFwE = false;}
      if(iOSOZjHofI == true){iOSOZjHofI = false;}
      if(hsnUYLxCSd == true){hsnUYLxCSd = false;}
      if(pHXPUaWNgN == true){pHXPUaWNgN = false;}
      if(PRuaqMZLbY == true){PRuaqMZLbY = false;}
      if(mOHMdNqrMG == true){mOHMdNqrMG = false;}
      if(zPmSObqCsz == true){zPmSObqCsz = false;}
      if(NsHSrQyNcL == true){NsHSrQyNcL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HILLWFVDJB
{ 
  void dpICKNUONn()
  { 
      bool GCTISZYJbh = false;
      bool DLFeFIISBz = false;
      bool YBlSELtKBB = false;
      bool SZPbPsnsrF = false;
      bool lncoBrDFTl = false;
      bool dpVJyEPAEG = false;
      bool fOIaOcucPM = false;
      bool TOawNkYxRM = false;
      bool IopPXcEGcK = false;
      bool dnokZWeBaX = false;
      bool wZoHROOZuN = false;
      bool eShqypXsCk = false;
      bool YozFhfZpWp = false;
      bool FWVtPhAixJ = false;
      bool NdLPeLFyli = false;
      bool zlzoyHZiYl = false;
      bool oYCEHIwnbQ = false;
      bool pourWudjaW = false;
      bool aaDnqSXfwI = false;
      bool HQJLUobGIW = false;
      string WuPuPTXJJO;
      string oeLjRRsZdV;
      string LZsOztahJV;
      string xIBTTrETmM;
      string MUEUGkXOKW;
      string qSsbUxBAuU;
      string sozmQfdrQZ;
      string MYlRIpVYIO;
      string VLXmddPYyW;
      string pEYRTXVQDa;
      string HfykKRfbSe;
      string bcrfzgRMJl;
      string PEstiIAUxk;
      string TEVhHpMlbM;
      string ymFTtNMrRm;
      string FJGQKClEBC;
      string QLdgKWGJYJ;
      string TejxncyZzV;
      string wICKfKxEWF;
      string EIkZulJXJX;
      if(WuPuPTXJJO == HfykKRfbSe){GCTISZYJbh = true;}
      else if(HfykKRfbSe == WuPuPTXJJO){wZoHROOZuN = true;}
      if(oeLjRRsZdV == bcrfzgRMJl){DLFeFIISBz = true;}
      else if(bcrfzgRMJl == oeLjRRsZdV){eShqypXsCk = true;}
      if(LZsOztahJV == PEstiIAUxk){YBlSELtKBB = true;}
      else if(PEstiIAUxk == LZsOztahJV){YozFhfZpWp = true;}
      if(xIBTTrETmM == TEVhHpMlbM){SZPbPsnsrF = true;}
      else if(TEVhHpMlbM == xIBTTrETmM){FWVtPhAixJ = true;}
      if(MUEUGkXOKW == ymFTtNMrRm){lncoBrDFTl = true;}
      else if(ymFTtNMrRm == MUEUGkXOKW){NdLPeLFyli = true;}
      if(qSsbUxBAuU == FJGQKClEBC){dpVJyEPAEG = true;}
      else if(FJGQKClEBC == qSsbUxBAuU){zlzoyHZiYl = true;}
      if(sozmQfdrQZ == QLdgKWGJYJ){fOIaOcucPM = true;}
      else if(QLdgKWGJYJ == sozmQfdrQZ){oYCEHIwnbQ = true;}
      if(MYlRIpVYIO == TejxncyZzV){TOawNkYxRM = true;}
      if(VLXmddPYyW == wICKfKxEWF){IopPXcEGcK = true;}
      if(pEYRTXVQDa == EIkZulJXJX){dnokZWeBaX = true;}
      while(TejxncyZzV == MYlRIpVYIO){pourWudjaW = true;}
      while(wICKfKxEWF == wICKfKxEWF){aaDnqSXfwI = true;}
      while(EIkZulJXJX == EIkZulJXJX){HQJLUobGIW = true;}
      if(GCTISZYJbh == true){GCTISZYJbh = false;}
      if(DLFeFIISBz == true){DLFeFIISBz = false;}
      if(YBlSELtKBB == true){YBlSELtKBB = false;}
      if(SZPbPsnsrF == true){SZPbPsnsrF = false;}
      if(lncoBrDFTl == true){lncoBrDFTl = false;}
      if(dpVJyEPAEG == true){dpVJyEPAEG = false;}
      if(fOIaOcucPM == true){fOIaOcucPM = false;}
      if(TOawNkYxRM == true){TOawNkYxRM = false;}
      if(IopPXcEGcK == true){IopPXcEGcK = false;}
      if(dnokZWeBaX == true){dnokZWeBaX = false;}
      if(wZoHROOZuN == true){wZoHROOZuN = false;}
      if(eShqypXsCk == true){eShqypXsCk = false;}
      if(YozFhfZpWp == true){YozFhfZpWp = false;}
      if(FWVtPhAixJ == true){FWVtPhAixJ = false;}
      if(NdLPeLFyli == true){NdLPeLFyli = false;}
      if(zlzoyHZiYl == true){zlzoyHZiYl = false;}
      if(oYCEHIwnbQ == true){oYCEHIwnbQ = false;}
      if(pourWudjaW == true){pourWudjaW = false;}
      if(aaDnqSXfwI == true){aaDnqSXfwI = false;}
      if(HQJLUobGIW == true){HQJLUobGIW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFUKPZDWDE
{ 
  void gfnuowDxBW()
  { 
      bool FnZUynUoyn = false;
      bool jaBXCoSBkD = false;
      bool RJluTmpGao = false;
      bool NwQYBXRzok = false;
      bool wqQzysUnmY = false;
      bool irdWbuCdBK = false;
      bool xOOJZmJbWd = false;
      bool WTLzHZslwa = false;
      bool SBSCGVRtxG = false;
      bool UnydmgcHZL = false;
      bool irRIBOfdPB = false;
      bool BPgZrwwLCD = false;
      bool UPdQJiUhMZ = false;
      bool xlMkqajJBq = false;
      bool omewEEGXlq = false;
      bool kQEVpSNAzR = false;
      bool tyRoDOCuhR = false;
      bool LlJLNgkhLE = false;
      bool cxuUnghquY = false;
      bool MiJjxqVorp = false;
      string loqsxdPVTV;
      string QVkzFqkLds;
      string KAjPbfKObK;
      string iHiAmMwcza;
      string nLYJuSopHi;
      string kcngClEbQQ;
      string TBsJmJmjLs;
      string tILCEzaaTJ;
      string qTGsYGTByB;
      string IULiHmRPVl;
      string fEdOncQkbC;
      string KdHHZztAjg;
      string pklKjZwcuR;
      string hLEhclpqEu;
      string ohZuqdNEIH;
      string rQeouuRTdO;
      string gmoKUyYYdn;
      string JDwoqHLqSG;
      string MrUnZQgOmh;
      string TVMpNBsOZs;
      if(loqsxdPVTV == fEdOncQkbC){FnZUynUoyn = true;}
      else if(fEdOncQkbC == loqsxdPVTV){irRIBOfdPB = true;}
      if(QVkzFqkLds == KdHHZztAjg){jaBXCoSBkD = true;}
      else if(KdHHZztAjg == QVkzFqkLds){BPgZrwwLCD = true;}
      if(KAjPbfKObK == pklKjZwcuR){RJluTmpGao = true;}
      else if(pklKjZwcuR == KAjPbfKObK){UPdQJiUhMZ = true;}
      if(iHiAmMwcza == hLEhclpqEu){NwQYBXRzok = true;}
      else if(hLEhclpqEu == iHiAmMwcza){xlMkqajJBq = true;}
      if(nLYJuSopHi == ohZuqdNEIH){wqQzysUnmY = true;}
      else if(ohZuqdNEIH == nLYJuSopHi){omewEEGXlq = true;}
      if(kcngClEbQQ == rQeouuRTdO){irdWbuCdBK = true;}
      else if(rQeouuRTdO == kcngClEbQQ){kQEVpSNAzR = true;}
      if(TBsJmJmjLs == gmoKUyYYdn){xOOJZmJbWd = true;}
      else if(gmoKUyYYdn == TBsJmJmjLs){tyRoDOCuhR = true;}
      if(tILCEzaaTJ == JDwoqHLqSG){WTLzHZslwa = true;}
      if(qTGsYGTByB == MrUnZQgOmh){SBSCGVRtxG = true;}
      if(IULiHmRPVl == TVMpNBsOZs){UnydmgcHZL = true;}
      while(JDwoqHLqSG == tILCEzaaTJ){LlJLNgkhLE = true;}
      while(MrUnZQgOmh == MrUnZQgOmh){cxuUnghquY = true;}
      while(TVMpNBsOZs == TVMpNBsOZs){MiJjxqVorp = true;}
      if(FnZUynUoyn == true){FnZUynUoyn = false;}
      if(jaBXCoSBkD == true){jaBXCoSBkD = false;}
      if(RJluTmpGao == true){RJluTmpGao = false;}
      if(NwQYBXRzok == true){NwQYBXRzok = false;}
      if(wqQzysUnmY == true){wqQzysUnmY = false;}
      if(irdWbuCdBK == true){irdWbuCdBK = false;}
      if(xOOJZmJbWd == true){xOOJZmJbWd = false;}
      if(WTLzHZslwa == true){WTLzHZslwa = false;}
      if(SBSCGVRtxG == true){SBSCGVRtxG = false;}
      if(UnydmgcHZL == true){UnydmgcHZL = false;}
      if(irRIBOfdPB == true){irRIBOfdPB = false;}
      if(BPgZrwwLCD == true){BPgZrwwLCD = false;}
      if(UPdQJiUhMZ == true){UPdQJiUhMZ = false;}
      if(xlMkqajJBq == true){xlMkqajJBq = false;}
      if(omewEEGXlq == true){omewEEGXlq = false;}
      if(kQEVpSNAzR == true){kQEVpSNAzR = false;}
      if(tyRoDOCuhR == true){tyRoDOCuhR = false;}
      if(LlJLNgkhLE == true){LlJLNgkhLE = false;}
      if(cxuUnghquY == true){cxuUnghquY = false;}
      if(MiJjxqVorp == true){MiJjxqVorp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NBBKUQIFFM
{ 
  void bNNIkGyagT()
  { 
      bool EGMIKOsWrF = false;
      bool qaDowZkfVp = false;
      bool znymDjPBYO = false;
      bool lEQFEhuMab = false;
      bool iRNlrQurXo = false;
      bool VuCpVPIZFZ = false;
      bool zrxcTmKykO = false;
      bool dXEsGgaLul = false;
      bool nXcispBZin = false;
      bool ZVHBcqTjRE = false;
      bool GxGJKxpIin = false;
      bool owdSkbONjd = false;
      bool ljOwoIPDQP = false;
      bool NpspfqQTYu = false;
      bool ArqtzcqoPA = false;
      bool cFznSVhKUC = false;
      bool glrTayCmmt = false;
      bool LuoodssTxL = false;
      bool QanQlHqFXJ = false;
      bool JFyWNNAWTA = false;
      string ooAFKrUpOA;
      string WaKOWacFsm;
      string dECLpMnKlD;
      string TXIDgAoZOI;
      string xuIgYCbwaI;
      string dXgGsjloPy;
      string DKELgyRGhV;
      string lDpjohwVln;
      string kricYuqCKx;
      string OzKQFlpxAa;
      string jUOEWagxQK;
      string mPCaMLablk;
      string HPwjHlrZeC;
      string qzVLEQcdFy;
      string OslzJyxjEs;
      string LOKOTUXdxk;
      string iGRNSntpWu;
      string iwVnWNcxaI;
      string nIVlqcnGri;
      string rygUPHbYfV;
      if(ooAFKrUpOA == jUOEWagxQK){EGMIKOsWrF = true;}
      else if(jUOEWagxQK == ooAFKrUpOA){GxGJKxpIin = true;}
      if(WaKOWacFsm == mPCaMLablk){qaDowZkfVp = true;}
      else if(mPCaMLablk == WaKOWacFsm){owdSkbONjd = true;}
      if(dECLpMnKlD == HPwjHlrZeC){znymDjPBYO = true;}
      else if(HPwjHlrZeC == dECLpMnKlD){ljOwoIPDQP = true;}
      if(TXIDgAoZOI == qzVLEQcdFy){lEQFEhuMab = true;}
      else if(qzVLEQcdFy == TXIDgAoZOI){NpspfqQTYu = true;}
      if(xuIgYCbwaI == OslzJyxjEs){iRNlrQurXo = true;}
      else if(OslzJyxjEs == xuIgYCbwaI){ArqtzcqoPA = true;}
      if(dXgGsjloPy == LOKOTUXdxk){VuCpVPIZFZ = true;}
      else if(LOKOTUXdxk == dXgGsjloPy){cFznSVhKUC = true;}
      if(DKELgyRGhV == iGRNSntpWu){zrxcTmKykO = true;}
      else if(iGRNSntpWu == DKELgyRGhV){glrTayCmmt = true;}
      if(lDpjohwVln == iwVnWNcxaI){dXEsGgaLul = true;}
      if(kricYuqCKx == nIVlqcnGri){nXcispBZin = true;}
      if(OzKQFlpxAa == rygUPHbYfV){ZVHBcqTjRE = true;}
      while(iwVnWNcxaI == lDpjohwVln){LuoodssTxL = true;}
      while(nIVlqcnGri == nIVlqcnGri){QanQlHqFXJ = true;}
      while(rygUPHbYfV == rygUPHbYfV){JFyWNNAWTA = true;}
      if(EGMIKOsWrF == true){EGMIKOsWrF = false;}
      if(qaDowZkfVp == true){qaDowZkfVp = false;}
      if(znymDjPBYO == true){znymDjPBYO = false;}
      if(lEQFEhuMab == true){lEQFEhuMab = false;}
      if(iRNlrQurXo == true){iRNlrQurXo = false;}
      if(VuCpVPIZFZ == true){VuCpVPIZFZ = false;}
      if(zrxcTmKykO == true){zrxcTmKykO = false;}
      if(dXEsGgaLul == true){dXEsGgaLul = false;}
      if(nXcispBZin == true){nXcispBZin = false;}
      if(ZVHBcqTjRE == true){ZVHBcqTjRE = false;}
      if(GxGJKxpIin == true){GxGJKxpIin = false;}
      if(owdSkbONjd == true){owdSkbONjd = false;}
      if(ljOwoIPDQP == true){ljOwoIPDQP = false;}
      if(NpspfqQTYu == true){NpspfqQTYu = false;}
      if(ArqtzcqoPA == true){ArqtzcqoPA = false;}
      if(cFznSVhKUC == true){cFznSVhKUC = false;}
      if(glrTayCmmt == true){glrTayCmmt = false;}
      if(LuoodssTxL == true){LuoodssTxL = false;}
      if(QanQlHqFXJ == true){QanQlHqFXJ = false;}
      if(JFyWNNAWTA == true){JFyWNNAWTA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWKQODVTRM
{ 
  void xcrCZlbnxG()
  { 
      bool MqLHwFLtiQ = false;
      bool BMZSKTheMf = false;
      bool IhchZfEZVU = false;
      bool RVBEDWUYBR = false;
      bool JfUfrXxeOh = false;
      bool PhwRzdOdgP = false;
      bool AlXOyfLUPn = false;
      bool yIctVbNxpB = false;
      bool iZLnFjZjEZ = false;
      bool HqrlRXHGgM = false;
      bool MbOajHEBuX = false;
      bool QRnffZajIO = false;
      bool GbPpgGQqcx = false;
      bool TGPcnGLkDy = false;
      bool eXngIoDLFq = false;
      bool xXxSGkLYtc = false;
      bool pNYxDJBKqZ = false;
      bool OofKihmigq = false;
      bool CEkkAwJxWD = false;
      bool ulqaHRypdz = false;
      string EuCtMjxYMP;
      string qiwMYfiOmf;
      string GmSVOyTiWJ;
      string MCAOmTQVnc;
      string GNxhIkrRDT;
      string imjpdRbfeN;
      string POCCDnhhZF;
      string PMZJYsojNc;
      string GCeDZYRKjU;
      string qjpZMrKueT;
      string DJryEWNaQj;
      string crSCHNjybd;
      string WXyEOeVzxf;
      string hsFsZwKgyD;
      string LqszqyQnSz;
      string IMSBxfLmiY;
      string BOcjCilYbK;
      string DCAYRfdyNP;
      string OggyXVaEwt;
      string kWxZCxNIxI;
      if(EuCtMjxYMP == DJryEWNaQj){MqLHwFLtiQ = true;}
      else if(DJryEWNaQj == EuCtMjxYMP){MbOajHEBuX = true;}
      if(qiwMYfiOmf == crSCHNjybd){BMZSKTheMf = true;}
      else if(crSCHNjybd == qiwMYfiOmf){QRnffZajIO = true;}
      if(GmSVOyTiWJ == WXyEOeVzxf){IhchZfEZVU = true;}
      else if(WXyEOeVzxf == GmSVOyTiWJ){GbPpgGQqcx = true;}
      if(MCAOmTQVnc == hsFsZwKgyD){RVBEDWUYBR = true;}
      else if(hsFsZwKgyD == MCAOmTQVnc){TGPcnGLkDy = true;}
      if(GNxhIkrRDT == LqszqyQnSz){JfUfrXxeOh = true;}
      else if(LqszqyQnSz == GNxhIkrRDT){eXngIoDLFq = true;}
      if(imjpdRbfeN == IMSBxfLmiY){PhwRzdOdgP = true;}
      else if(IMSBxfLmiY == imjpdRbfeN){xXxSGkLYtc = true;}
      if(POCCDnhhZF == BOcjCilYbK){AlXOyfLUPn = true;}
      else if(BOcjCilYbK == POCCDnhhZF){pNYxDJBKqZ = true;}
      if(PMZJYsojNc == DCAYRfdyNP){yIctVbNxpB = true;}
      if(GCeDZYRKjU == OggyXVaEwt){iZLnFjZjEZ = true;}
      if(qjpZMrKueT == kWxZCxNIxI){HqrlRXHGgM = true;}
      while(DCAYRfdyNP == PMZJYsojNc){OofKihmigq = true;}
      while(OggyXVaEwt == OggyXVaEwt){CEkkAwJxWD = true;}
      while(kWxZCxNIxI == kWxZCxNIxI){ulqaHRypdz = true;}
      if(MqLHwFLtiQ == true){MqLHwFLtiQ = false;}
      if(BMZSKTheMf == true){BMZSKTheMf = false;}
      if(IhchZfEZVU == true){IhchZfEZVU = false;}
      if(RVBEDWUYBR == true){RVBEDWUYBR = false;}
      if(JfUfrXxeOh == true){JfUfrXxeOh = false;}
      if(PhwRzdOdgP == true){PhwRzdOdgP = false;}
      if(AlXOyfLUPn == true){AlXOyfLUPn = false;}
      if(yIctVbNxpB == true){yIctVbNxpB = false;}
      if(iZLnFjZjEZ == true){iZLnFjZjEZ = false;}
      if(HqrlRXHGgM == true){HqrlRXHGgM = false;}
      if(MbOajHEBuX == true){MbOajHEBuX = false;}
      if(QRnffZajIO == true){QRnffZajIO = false;}
      if(GbPpgGQqcx == true){GbPpgGQqcx = false;}
      if(TGPcnGLkDy == true){TGPcnGLkDy = false;}
      if(eXngIoDLFq == true){eXngIoDLFq = false;}
      if(xXxSGkLYtc == true){xXxSGkLYtc = false;}
      if(pNYxDJBKqZ == true){pNYxDJBKqZ = false;}
      if(OofKihmigq == true){OofKihmigq = false;}
      if(CEkkAwJxWD == true){CEkkAwJxWD = false;}
      if(ulqaHRypdz == true){ulqaHRypdz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUARZLROVY
{ 
  void NDlKElaXao()
  { 
      bool YcoykGigWV = false;
      bool yiaJFNihgy = false;
      bool BslYZOeUsI = false;
      bool FRmDNRSaxL = false;
      bool CpirisDrwE = false;
      bool AOQmNeqPYV = false;
      bool aOmNPgwWun = false;
      bool tIkUuLKsog = false;
      bool KmXnIpBAoi = false;
      bool aDBaknCVcC = false;
      bool wfxIKqduqC = false;
      bool TxarKnpzEY = false;
      bool fuhMNqHJjH = false;
      bool IoQljeoPdQ = false;
      bool LFIlOcbJPx = false;
      bool yDQDWByjuS = false;
      bool jULjtefnIf = false;
      bool yZUnMZmuxj = false;
      bool OysmIFXNPi = false;
      bool fFUKgqsXri = false;
      string XgcCLByrQs;
      string YCoQoPmgqb;
      string DWoQWjLOpy;
      string dVjwekbgQj;
      string CgMRqwumJN;
      string hAhfyArLeb;
      string piBRPDSrlD;
      string nGPGYWKWZa;
      string nYEbQcnExd;
      string sPBotSetBm;
      string cDBGZajaGb;
      string oUlEmQeYBl;
      string POtHKYFaLG;
      string qQUlxkXxCo;
      string sMyVnXcwBd;
      string nFsPXOIsuA;
      string VJPzjYzAHC;
      string sgWLsCPYSl;
      string uIZhSlWFNh;
      string cdCBSjxykP;
      if(XgcCLByrQs == cDBGZajaGb){YcoykGigWV = true;}
      else if(cDBGZajaGb == XgcCLByrQs){wfxIKqduqC = true;}
      if(YCoQoPmgqb == oUlEmQeYBl){yiaJFNihgy = true;}
      else if(oUlEmQeYBl == YCoQoPmgqb){TxarKnpzEY = true;}
      if(DWoQWjLOpy == POtHKYFaLG){BslYZOeUsI = true;}
      else if(POtHKYFaLG == DWoQWjLOpy){fuhMNqHJjH = true;}
      if(dVjwekbgQj == qQUlxkXxCo){FRmDNRSaxL = true;}
      else if(qQUlxkXxCo == dVjwekbgQj){IoQljeoPdQ = true;}
      if(CgMRqwumJN == sMyVnXcwBd){CpirisDrwE = true;}
      else if(sMyVnXcwBd == CgMRqwumJN){LFIlOcbJPx = true;}
      if(hAhfyArLeb == nFsPXOIsuA){AOQmNeqPYV = true;}
      else if(nFsPXOIsuA == hAhfyArLeb){yDQDWByjuS = true;}
      if(piBRPDSrlD == VJPzjYzAHC){aOmNPgwWun = true;}
      else if(VJPzjYzAHC == piBRPDSrlD){jULjtefnIf = true;}
      if(nGPGYWKWZa == sgWLsCPYSl){tIkUuLKsog = true;}
      if(nYEbQcnExd == uIZhSlWFNh){KmXnIpBAoi = true;}
      if(sPBotSetBm == cdCBSjxykP){aDBaknCVcC = true;}
      while(sgWLsCPYSl == nGPGYWKWZa){yZUnMZmuxj = true;}
      while(uIZhSlWFNh == uIZhSlWFNh){OysmIFXNPi = true;}
      while(cdCBSjxykP == cdCBSjxykP){fFUKgqsXri = true;}
      if(YcoykGigWV == true){YcoykGigWV = false;}
      if(yiaJFNihgy == true){yiaJFNihgy = false;}
      if(BslYZOeUsI == true){BslYZOeUsI = false;}
      if(FRmDNRSaxL == true){FRmDNRSaxL = false;}
      if(CpirisDrwE == true){CpirisDrwE = false;}
      if(AOQmNeqPYV == true){AOQmNeqPYV = false;}
      if(aOmNPgwWun == true){aOmNPgwWun = false;}
      if(tIkUuLKsog == true){tIkUuLKsog = false;}
      if(KmXnIpBAoi == true){KmXnIpBAoi = false;}
      if(aDBaknCVcC == true){aDBaknCVcC = false;}
      if(wfxIKqduqC == true){wfxIKqduqC = false;}
      if(TxarKnpzEY == true){TxarKnpzEY = false;}
      if(fuhMNqHJjH == true){fuhMNqHJjH = false;}
      if(IoQljeoPdQ == true){IoQljeoPdQ = false;}
      if(LFIlOcbJPx == true){LFIlOcbJPx = false;}
      if(yDQDWByjuS == true){yDQDWByjuS = false;}
      if(jULjtefnIf == true){jULjtefnIf = false;}
      if(yZUnMZmuxj == true){yZUnMZmuxj = false;}
      if(OysmIFXNPi == true){OysmIFXNPi = false;}
      if(fFUKgqsXri == true){fFUKgqsXri = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJORBBILTK
{ 
  void hjrkbJWgIM()
  { 
      bool LOEeGMbrZQ = false;
      bool GnZkPICOfh = false;
      bool KcwjAUMjnc = false;
      bool zVXnIiDHGk = false;
      bool hSCIRboLKp = false;
      bool RsLDBiSTek = false;
      bool AqDwRkQkbf = false;
      bool FuIuArZmSX = false;
      bool eAZyLFJTmY = false;
      bool QicUjpOFqg = false;
      bool LDidkWkQDJ = false;
      bool IeBGGzRFkL = false;
      bool bwyDPVRnKJ = false;
      bool cTwkMbQuNn = false;
      bool UrQcPlhWOk = false;
      bool YJUeFOFfOO = false;
      bool EwGsfohPsd = false;
      bool hWqwqifUmd = false;
      bool muZZkTzQfy = false;
      bool VkfyjXkWxa = false;
      string GqOFWIyIhD;
      string JYxNVdAJBl;
      string ERDfGsltYa;
      string MFTpjLnOCk;
      string kVpVSJsmBm;
      string XeszWnmhzd;
      string WEjGpDEHdJ;
      string okHPBhagNx;
      string zyskChMUSu;
      string XFPYNgkjfP;
      string ElJqxmXcyn;
      string NGUBdYKyDH;
      string qjniljVhBT;
      string wqAyrNoBnP;
      string JiVdhRkNuo;
      string VlfXXTxZFN;
      string QoadrVFWIP;
      string iIKmxHNJAU;
      string yImMyJKcZY;
      string POwZzUIrlL;
      if(GqOFWIyIhD == ElJqxmXcyn){LOEeGMbrZQ = true;}
      else if(ElJqxmXcyn == GqOFWIyIhD){LDidkWkQDJ = true;}
      if(JYxNVdAJBl == NGUBdYKyDH){GnZkPICOfh = true;}
      else if(NGUBdYKyDH == JYxNVdAJBl){IeBGGzRFkL = true;}
      if(ERDfGsltYa == qjniljVhBT){KcwjAUMjnc = true;}
      else if(qjniljVhBT == ERDfGsltYa){bwyDPVRnKJ = true;}
      if(MFTpjLnOCk == wqAyrNoBnP){zVXnIiDHGk = true;}
      else if(wqAyrNoBnP == MFTpjLnOCk){cTwkMbQuNn = true;}
      if(kVpVSJsmBm == JiVdhRkNuo){hSCIRboLKp = true;}
      else if(JiVdhRkNuo == kVpVSJsmBm){UrQcPlhWOk = true;}
      if(XeszWnmhzd == VlfXXTxZFN){RsLDBiSTek = true;}
      else if(VlfXXTxZFN == XeszWnmhzd){YJUeFOFfOO = true;}
      if(WEjGpDEHdJ == QoadrVFWIP){AqDwRkQkbf = true;}
      else if(QoadrVFWIP == WEjGpDEHdJ){EwGsfohPsd = true;}
      if(okHPBhagNx == iIKmxHNJAU){FuIuArZmSX = true;}
      if(zyskChMUSu == yImMyJKcZY){eAZyLFJTmY = true;}
      if(XFPYNgkjfP == POwZzUIrlL){QicUjpOFqg = true;}
      while(iIKmxHNJAU == okHPBhagNx){hWqwqifUmd = true;}
      while(yImMyJKcZY == yImMyJKcZY){muZZkTzQfy = true;}
      while(POwZzUIrlL == POwZzUIrlL){VkfyjXkWxa = true;}
      if(LOEeGMbrZQ == true){LOEeGMbrZQ = false;}
      if(GnZkPICOfh == true){GnZkPICOfh = false;}
      if(KcwjAUMjnc == true){KcwjAUMjnc = false;}
      if(zVXnIiDHGk == true){zVXnIiDHGk = false;}
      if(hSCIRboLKp == true){hSCIRboLKp = false;}
      if(RsLDBiSTek == true){RsLDBiSTek = false;}
      if(AqDwRkQkbf == true){AqDwRkQkbf = false;}
      if(FuIuArZmSX == true){FuIuArZmSX = false;}
      if(eAZyLFJTmY == true){eAZyLFJTmY = false;}
      if(QicUjpOFqg == true){QicUjpOFqg = false;}
      if(LDidkWkQDJ == true){LDidkWkQDJ = false;}
      if(IeBGGzRFkL == true){IeBGGzRFkL = false;}
      if(bwyDPVRnKJ == true){bwyDPVRnKJ = false;}
      if(cTwkMbQuNn == true){cTwkMbQuNn = false;}
      if(UrQcPlhWOk == true){UrQcPlhWOk = false;}
      if(YJUeFOFfOO == true){YJUeFOFfOO = false;}
      if(EwGsfohPsd == true){EwGsfohPsd = false;}
      if(hWqwqifUmd == true){hWqwqifUmd = false;}
      if(muZZkTzQfy == true){muZZkTzQfy = false;}
      if(VkfyjXkWxa == true){VkfyjXkWxa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUILVDUDKL
{ 
  void jlFIcjGVjN()
  { 
      bool sIDJWLffCx = false;
      bool axuWBbuglK = false;
      bool TrjggkBKrm = false;
      bool ISUOImIcDM = false;
      bool QDrMBNocLM = false;
      bool sfVzRAYVcl = false;
      bool KUmPoHbgOO = false;
      bool SRcYsPzXeT = false;
      bool uYzftbwUxH = false;
      bool NlARCuQcWs = false;
      bool kINwtaCxGB = false;
      bool BAqIpkVGUN = false;
      bool LHiHAfQLVx = false;
      bool yWAkhmKClT = false;
      bool YzOuGMuqaR = false;
      bool ZJHJhcZGuN = false;
      bool JqaICdAFZD = false;
      bool ZTUBnLrmAm = false;
      bool kYjEXoOqCF = false;
      bool NEGYJhYFrb = false;
      string EusoAwUYRd;
      string cyxinJfpfU;
      string YkcidJcOeU;
      string jonZHMjJWQ;
      string thSXxFxLiW;
      string hprXzSSJLq;
      string TGswsmKXbb;
      string YWTPZpSElY;
      string MQfImtxQZn;
      string tZyewnoVeJ;
      string uYjGxLWbxI;
      string ANWldDajIz;
      string ptxnhzXnTl;
      string BxZccmgYLb;
      string WUSRnfDLAs;
      string NEMeSBbuYy;
      string miHKHDmtIq;
      string VBYgbUaezB;
      string wLmaYwjuJb;
      string KkANnnMHKk;
      if(EusoAwUYRd == uYjGxLWbxI){sIDJWLffCx = true;}
      else if(uYjGxLWbxI == EusoAwUYRd){kINwtaCxGB = true;}
      if(cyxinJfpfU == ANWldDajIz){axuWBbuglK = true;}
      else if(ANWldDajIz == cyxinJfpfU){BAqIpkVGUN = true;}
      if(YkcidJcOeU == ptxnhzXnTl){TrjggkBKrm = true;}
      else if(ptxnhzXnTl == YkcidJcOeU){LHiHAfQLVx = true;}
      if(jonZHMjJWQ == BxZccmgYLb){ISUOImIcDM = true;}
      else if(BxZccmgYLb == jonZHMjJWQ){yWAkhmKClT = true;}
      if(thSXxFxLiW == WUSRnfDLAs){QDrMBNocLM = true;}
      else if(WUSRnfDLAs == thSXxFxLiW){YzOuGMuqaR = true;}
      if(hprXzSSJLq == NEMeSBbuYy){sfVzRAYVcl = true;}
      else if(NEMeSBbuYy == hprXzSSJLq){ZJHJhcZGuN = true;}
      if(TGswsmKXbb == miHKHDmtIq){KUmPoHbgOO = true;}
      else if(miHKHDmtIq == TGswsmKXbb){JqaICdAFZD = true;}
      if(YWTPZpSElY == VBYgbUaezB){SRcYsPzXeT = true;}
      if(MQfImtxQZn == wLmaYwjuJb){uYzftbwUxH = true;}
      if(tZyewnoVeJ == KkANnnMHKk){NlARCuQcWs = true;}
      while(VBYgbUaezB == YWTPZpSElY){ZTUBnLrmAm = true;}
      while(wLmaYwjuJb == wLmaYwjuJb){kYjEXoOqCF = true;}
      while(KkANnnMHKk == KkANnnMHKk){NEGYJhYFrb = true;}
      if(sIDJWLffCx == true){sIDJWLffCx = false;}
      if(axuWBbuglK == true){axuWBbuglK = false;}
      if(TrjggkBKrm == true){TrjggkBKrm = false;}
      if(ISUOImIcDM == true){ISUOImIcDM = false;}
      if(QDrMBNocLM == true){QDrMBNocLM = false;}
      if(sfVzRAYVcl == true){sfVzRAYVcl = false;}
      if(KUmPoHbgOO == true){KUmPoHbgOO = false;}
      if(SRcYsPzXeT == true){SRcYsPzXeT = false;}
      if(uYzftbwUxH == true){uYzftbwUxH = false;}
      if(NlARCuQcWs == true){NlARCuQcWs = false;}
      if(kINwtaCxGB == true){kINwtaCxGB = false;}
      if(BAqIpkVGUN == true){BAqIpkVGUN = false;}
      if(LHiHAfQLVx == true){LHiHAfQLVx = false;}
      if(yWAkhmKClT == true){yWAkhmKClT = false;}
      if(YzOuGMuqaR == true){YzOuGMuqaR = false;}
      if(ZJHJhcZGuN == true){ZJHJhcZGuN = false;}
      if(JqaICdAFZD == true){JqaICdAFZD = false;}
      if(ZTUBnLrmAm == true){ZTUBnLrmAm = false;}
      if(kYjEXoOqCF == true){kYjEXoOqCF = false;}
      if(NEGYJhYFrb == true){NEGYJhYFrb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LOWARXFWQZ
{ 
  void ITGyCboHYe()
  { 
      bool YrfskATZWL = false;
      bool wnnuRdJeUc = false;
      bool EHOgYWeoZP = false;
      bool sjjLMcoMgK = false;
      bool fbEHswwjmI = false;
      bool iMrtORcyUN = false;
      bool VezGSMDbhn = false;
      bool owxJxcCGnb = false;
      bool auBRgfqowu = false;
      bool zprToAbxof = false;
      bool rTByTlPhxl = false;
      bool OWKrmZdhZl = false;
      bool VNemnyEcUx = false;
      bool AFRHjHtCyu = false;
      bool QIrKfcfzgO = false;
      bool WtWCKdnNKU = false;
      bool glNzkJFCHe = false;
      bool fajeUMVUHL = false;
      bool SEwFaGhOwF = false;
      bool SfrcNeurYW = false;
      string yZGddHBxho;
      string nuHSYdbSAm;
      string fakXzAWwiV;
      string xTECsjHpUl;
      string kQykobMxMG;
      string KUVGIXnhec;
      string jEOLrUpEZn;
      string VkyNCPbziW;
      string nZibLcxytU;
      string uZLqCfBmsT;
      string lHWYjYVIDr;
      string unyHoJUlzO;
      string XrKErwYHLW;
      string OoGPjgCKrl;
      string GntBZHaDBr;
      string KOmeutwSfm;
      string zOxgdGhiXI;
      string HJtMHjxIek;
      string VVFSLABaTp;
      string jjeFmrqNXS;
      if(yZGddHBxho == lHWYjYVIDr){YrfskATZWL = true;}
      else if(lHWYjYVIDr == yZGddHBxho){rTByTlPhxl = true;}
      if(nuHSYdbSAm == unyHoJUlzO){wnnuRdJeUc = true;}
      else if(unyHoJUlzO == nuHSYdbSAm){OWKrmZdhZl = true;}
      if(fakXzAWwiV == XrKErwYHLW){EHOgYWeoZP = true;}
      else if(XrKErwYHLW == fakXzAWwiV){VNemnyEcUx = true;}
      if(xTECsjHpUl == OoGPjgCKrl){sjjLMcoMgK = true;}
      else if(OoGPjgCKrl == xTECsjHpUl){AFRHjHtCyu = true;}
      if(kQykobMxMG == GntBZHaDBr){fbEHswwjmI = true;}
      else if(GntBZHaDBr == kQykobMxMG){QIrKfcfzgO = true;}
      if(KUVGIXnhec == KOmeutwSfm){iMrtORcyUN = true;}
      else if(KOmeutwSfm == KUVGIXnhec){WtWCKdnNKU = true;}
      if(jEOLrUpEZn == zOxgdGhiXI){VezGSMDbhn = true;}
      else if(zOxgdGhiXI == jEOLrUpEZn){glNzkJFCHe = true;}
      if(VkyNCPbziW == HJtMHjxIek){owxJxcCGnb = true;}
      if(nZibLcxytU == VVFSLABaTp){auBRgfqowu = true;}
      if(uZLqCfBmsT == jjeFmrqNXS){zprToAbxof = true;}
      while(HJtMHjxIek == VkyNCPbziW){fajeUMVUHL = true;}
      while(VVFSLABaTp == VVFSLABaTp){SEwFaGhOwF = true;}
      while(jjeFmrqNXS == jjeFmrqNXS){SfrcNeurYW = true;}
      if(YrfskATZWL == true){YrfskATZWL = false;}
      if(wnnuRdJeUc == true){wnnuRdJeUc = false;}
      if(EHOgYWeoZP == true){EHOgYWeoZP = false;}
      if(sjjLMcoMgK == true){sjjLMcoMgK = false;}
      if(fbEHswwjmI == true){fbEHswwjmI = false;}
      if(iMrtORcyUN == true){iMrtORcyUN = false;}
      if(VezGSMDbhn == true){VezGSMDbhn = false;}
      if(owxJxcCGnb == true){owxJxcCGnb = false;}
      if(auBRgfqowu == true){auBRgfqowu = false;}
      if(zprToAbxof == true){zprToAbxof = false;}
      if(rTByTlPhxl == true){rTByTlPhxl = false;}
      if(OWKrmZdhZl == true){OWKrmZdhZl = false;}
      if(VNemnyEcUx == true){VNemnyEcUx = false;}
      if(AFRHjHtCyu == true){AFRHjHtCyu = false;}
      if(QIrKfcfzgO == true){QIrKfcfzgO = false;}
      if(WtWCKdnNKU == true){WtWCKdnNKU = false;}
      if(glNzkJFCHe == true){glNzkJFCHe = false;}
      if(fajeUMVUHL == true){fajeUMVUHL = false;}
      if(SEwFaGhOwF == true){SEwFaGhOwF = false;}
      if(SfrcNeurYW == true){SfrcNeurYW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJFAJHKKKK
{ 
  void zGWBSEbWWr()
  { 
      bool RThjfawoiO = false;
      bool uMSRrnRzgl = false;
      bool nXASdyOCgJ = false;
      bool eOsZsYqJDP = false;
      bool XdTqdwXgAH = false;
      bool pNsWssSPFh = false;
      bool MtHZjgSrXT = false;
      bool xHwROKDJog = false;
      bool ZgBZTQVVgA = false;
      bool FbDUDdVtHw = false;
      bool deIgJhRaIi = false;
      bool pJZXHerhFS = false;
      bool LwLXNVEaOk = false;
      bool oIBrDtYUQl = false;
      bool ztNyJwBeNX = false;
      bool kmnnkhTkSm = false;
      bool dpMWtgHhUM = false;
      bool GWRTTQhNNQ = false;
      bool UYNpzBUNGV = false;
      bool anCcHIhqEc = false;
      string qTShUjPKbC;
      string azdsRzrICe;
      string xHBixxoSDQ;
      string XCKaQpgOHW;
      string YWQOWNmAJV;
      string rcSIsiRikW;
      string uxGLeYoCcb;
      string RdBfGaqmMi;
      string KnIhYuiBhg;
      string XycjbbPFjx;
      string YkWgEObmCR;
      string reWCMGnYmj;
      string onTwETAQEd;
      string LkDOJZRacJ;
      string SwyQnsaaWU;
      string mqSAIkQack;
      string NLiXGGaHrm;
      string oMucQsoDHL;
      string rZsipTSDGY;
      string JqyruHNaJg;
      if(qTShUjPKbC == YkWgEObmCR){RThjfawoiO = true;}
      else if(YkWgEObmCR == qTShUjPKbC){deIgJhRaIi = true;}
      if(azdsRzrICe == reWCMGnYmj){uMSRrnRzgl = true;}
      else if(reWCMGnYmj == azdsRzrICe){pJZXHerhFS = true;}
      if(xHBixxoSDQ == onTwETAQEd){nXASdyOCgJ = true;}
      else if(onTwETAQEd == xHBixxoSDQ){LwLXNVEaOk = true;}
      if(XCKaQpgOHW == LkDOJZRacJ){eOsZsYqJDP = true;}
      else if(LkDOJZRacJ == XCKaQpgOHW){oIBrDtYUQl = true;}
      if(YWQOWNmAJV == SwyQnsaaWU){XdTqdwXgAH = true;}
      else if(SwyQnsaaWU == YWQOWNmAJV){ztNyJwBeNX = true;}
      if(rcSIsiRikW == mqSAIkQack){pNsWssSPFh = true;}
      else if(mqSAIkQack == rcSIsiRikW){kmnnkhTkSm = true;}
      if(uxGLeYoCcb == NLiXGGaHrm){MtHZjgSrXT = true;}
      else if(NLiXGGaHrm == uxGLeYoCcb){dpMWtgHhUM = true;}
      if(RdBfGaqmMi == oMucQsoDHL){xHwROKDJog = true;}
      if(KnIhYuiBhg == rZsipTSDGY){ZgBZTQVVgA = true;}
      if(XycjbbPFjx == JqyruHNaJg){FbDUDdVtHw = true;}
      while(oMucQsoDHL == RdBfGaqmMi){GWRTTQhNNQ = true;}
      while(rZsipTSDGY == rZsipTSDGY){UYNpzBUNGV = true;}
      while(JqyruHNaJg == JqyruHNaJg){anCcHIhqEc = true;}
      if(RThjfawoiO == true){RThjfawoiO = false;}
      if(uMSRrnRzgl == true){uMSRrnRzgl = false;}
      if(nXASdyOCgJ == true){nXASdyOCgJ = false;}
      if(eOsZsYqJDP == true){eOsZsYqJDP = false;}
      if(XdTqdwXgAH == true){XdTqdwXgAH = false;}
      if(pNsWssSPFh == true){pNsWssSPFh = false;}
      if(MtHZjgSrXT == true){MtHZjgSrXT = false;}
      if(xHwROKDJog == true){xHwROKDJog = false;}
      if(ZgBZTQVVgA == true){ZgBZTQVVgA = false;}
      if(FbDUDdVtHw == true){FbDUDdVtHw = false;}
      if(deIgJhRaIi == true){deIgJhRaIi = false;}
      if(pJZXHerhFS == true){pJZXHerhFS = false;}
      if(LwLXNVEaOk == true){LwLXNVEaOk = false;}
      if(oIBrDtYUQl == true){oIBrDtYUQl = false;}
      if(ztNyJwBeNX == true){ztNyJwBeNX = false;}
      if(kmnnkhTkSm == true){kmnnkhTkSm = false;}
      if(dpMWtgHhUM == true){dpMWtgHhUM = false;}
      if(GWRTTQhNNQ == true){GWRTTQhNNQ = false;}
      if(UYNpzBUNGV == true){UYNpzBUNGV = false;}
      if(anCcHIhqEc == true){anCcHIhqEc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLYXRNDXUC
{ 
  void qpNwZUJDJQ()
  { 
      bool wAlcdOVYzk = false;
      bool RhphdZngTd = false;
      bool qwRbbXZySi = false;
      bool uKNTCgHtpX = false;
      bool qVilkXRgwF = false;
      bool VaimXAiKBF = false;
      bool nXFQpHTVex = false;
      bool StpwmVMfpD = false;
      bool FsBNMUaawC = false;
      bool yxskjTQSwd = false;
      bool EuCzmbjmAB = false;
      bool mDTxAuWqDU = false;
      bool fsZbyUBFLT = false;
      bool FtjMzJpBZj = false;
      bool jmZtPucujn = false;
      bool wYOaxKVZAR = false;
      bool aeagwrTHyp = false;
      bool EURTkrSeMD = false;
      bool qFUXWffIOn = false;
      bool nQBHJFMsxW = false;
      string cMibHjIKdb;
      string YUfeeXYfYL;
      string KmVSZfhSYA;
      string yVmdsWIhmX;
      string eszlElHsOA;
      string VkgdRppPBa;
      string BokccChCkH;
      string PqrAfQmjOm;
      string YnDXdNoILC;
      string grfLVoHVIB;
      string EEHHjerfxB;
      string CFBNBMkMyP;
      string MYpiZXLgdp;
      string IRaMiTgwmz;
      string VJKKAapRJJ;
      string DuXsofNYgM;
      string TKBHrkeoeg;
      string foYzsDNfiz;
      string hsWUmNthXD;
      string FHOafKHDRO;
      if(cMibHjIKdb == EEHHjerfxB){wAlcdOVYzk = true;}
      else if(EEHHjerfxB == cMibHjIKdb){EuCzmbjmAB = true;}
      if(YUfeeXYfYL == CFBNBMkMyP){RhphdZngTd = true;}
      else if(CFBNBMkMyP == YUfeeXYfYL){mDTxAuWqDU = true;}
      if(KmVSZfhSYA == MYpiZXLgdp){qwRbbXZySi = true;}
      else if(MYpiZXLgdp == KmVSZfhSYA){fsZbyUBFLT = true;}
      if(yVmdsWIhmX == IRaMiTgwmz){uKNTCgHtpX = true;}
      else if(IRaMiTgwmz == yVmdsWIhmX){FtjMzJpBZj = true;}
      if(eszlElHsOA == VJKKAapRJJ){qVilkXRgwF = true;}
      else if(VJKKAapRJJ == eszlElHsOA){jmZtPucujn = true;}
      if(VkgdRppPBa == DuXsofNYgM){VaimXAiKBF = true;}
      else if(DuXsofNYgM == VkgdRppPBa){wYOaxKVZAR = true;}
      if(BokccChCkH == TKBHrkeoeg){nXFQpHTVex = true;}
      else if(TKBHrkeoeg == BokccChCkH){aeagwrTHyp = true;}
      if(PqrAfQmjOm == foYzsDNfiz){StpwmVMfpD = true;}
      if(YnDXdNoILC == hsWUmNthXD){FsBNMUaawC = true;}
      if(grfLVoHVIB == FHOafKHDRO){yxskjTQSwd = true;}
      while(foYzsDNfiz == PqrAfQmjOm){EURTkrSeMD = true;}
      while(hsWUmNthXD == hsWUmNthXD){qFUXWffIOn = true;}
      while(FHOafKHDRO == FHOafKHDRO){nQBHJFMsxW = true;}
      if(wAlcdOVYzk == true){wAlcdOVYzk = false;}
      if(RhphdZngTd == true){RhphdZngTd = false;}
      if(qwRbbXZySi == true){qwRbbXZySi = false;}
      if(uKNTCgHtpX == true){uKNTCgHtpX = false;}
      if(qVilkXRgwF == true){qVilkXRgwF = false;}
      if(VaimXAiKBF == true){VaimXAiKBF = false;}
      if(nXFQpHTVex == true){nXFQpHTVex = false;}
      if(StpwmVMfpD == true){StpwmVMfpD = false;}
      if(FsBNMUaawC == true){FsBNMUaawC = false;}
      if(yxskjTQSwd == true){yxskjTQSwd = false;}
      if(EuCzmbjmAB == true){EuCzmbjmAB = false;}
      if(mDTxAuWqDU == true){mDTxAuWqDU = false;}
      if(fsZbyUBFLT == true){fsZbyUBFLT = false;}
      if(FtjMzJpBZj == true){FtjMzJpBZj = false;}
      if(jmZtPucujn == true){jmZtPucujn = false;}
      if(wYOaxKVZAR == true){wYOaxKVZAR = false;}
      if(aeagwrTHyp == true){aeagwrTHyp = false;}
      if(EURTkrSeMD == true){EURTkrSeMD = false;}
      if(qFUXWffIOn == true){qFUXWffIOn = false;}
      if(nQBHJFMsxW == true){nQBHJFMsxW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULKHQMBTLG
{ 
  void NRVdGCprXl()
  { 
      bool CYFyRLNESF = false;
      bool yxGOVwVCxD = false;
      bool qookQEZcaX = false;
      bool SqGsUbzUIA = false;
      bool xAdkIKugMx = false;
      bool UmmYpMiTgM = false;
      bool ljctlGqMtt = false;
      bool wBsxGpLDbF = false;
      bool IrQdDfEgDI = false;
      bool sfmuNMXjzC = false;
      bool ThmSATspSA = false;
      bool BeqbDsTzpG = false;
      bool CJJkAQNxis = false;
      bool SbEZlaFydi = false;
      bool lNNCGNnKqU = false;
      bool sXsrAJXBRi = false;
      bool FwGYgZZRpc = false;
      bool mUVGUnwGem = false;
      bool cCFOAthMZb = false;
      bool CEgtdoHoVg = false;
      string CGVqjrfEjR;
      string ECrCkKwTAI;
      string TNlupZYsFY;
      string NkjWrWPXsj;
      string ZqyfFOcyLW;
      string bDrldoUaBJ;
      string SmzLESSUJN;
      string uYZQhcPFpb;
      string wZghxJsxsD;
      string CoWjQmqlbl;
      string uIoybCdbDA;
      string YOjYMrFROt;
      string ZVbGLFCozt;
      string kcdDgnkiFt;
      string eRsrdmExWY;
      string hZXgMZfimW;
      string AnbJOwkfrY;
      string GVLTOHbibX;
      string AESZMLEwpG;
      string HCwhspojch;
      if(CGVqjrfEjR == uIoybCdbDA){CYFyRLNESF = true;}
      else if(uIoybCdbDA == CGVqjrfEjR){ThmSATspSA = true;}
      if(ECrCkKwTAI == YOjYMrFROt){yxGOVwVCxD = true;}
      else if(YOjYMrFROt == ECrCkKwTAI){BeqbDsTzpG = true;}
      if(TNlupZYsFY == ZVbGLFCozt){qookQEZcaX = true;}
      else if(ZVbGLFCozt == TNlupZYsFY){CJJkAQNxis = true;}
      if(NkjWrWPXsj == kcdDgnkiFt){SqGsUbzUIA = true;}
      else if(kcdDgnkiFt == NkjWrWPXsj){SbEZlaFydi = true;}
      if(ZqyfFOcyLW == eRsrdmExWY){xAdkIKugMx = true;}
      else if(eRsrdmExWY == ZqyfFOcyLW){lNNCGNnKqU = true;}
      if(bDrldoUaBJ == hZXgMZfimW){UmmYpMiTgM = true;}
      else if(hZXgMZfimW == bDrldoUaBJ){sXsrAJXBRi = true;}
      if(SmzLESSUJN == AnbJOwkfrY){ljctlGqMtt = true;}
      else if(AnbJOwkfrY == SmzLESSUJN){FwGYgZZRpc = true;}
      if(uYZQhcPFpb == GVLTOHbibX){wBsxGpLDbF = true;}
      if(wZghxJsxsD == AESZMLEwpG){IrQdDfEgDI = true;}
      if(CoWjQmqlbl == HCwhspojch){sfmuNMXjzC = true;}
      while(GVLTOHbibX == uYZQhcPFpb){mUVGUnwGem = true;}
      while(AESZMLEwpG == AESZMLEwpG){cCFOAthMZb = true;}
      while(HCwhspojch == HCwhspojch){CEgtdoHoVg = true;}
      if(CYFyRLNESF == true){CYFyRLNESF = false;}
      if(yxGOVwVCxD == true){yxGOVwVCxD = false;}
      if(qookQEZcaX == true){qookQEZcaX = false;}
      if(SqGsUbzUIA == true){SqGsUbzUIA = false;}
      if(xAdkIKugMx == true){xAdkIKugMx = false;}
      if(UmmYpMiTgM == true){UmmYpMiTgM = false;}
      if(ljctlGqMtt == true){ljctlGqMtt = false;}
      if(wBsxGpLDbF == true){wBsxGpLDbF = false;}
      if(IrQdDfEgDI == true){IrQdDfEgDI = false;}
      if(sfmuNMXjzC == true){sfmuNMXjzC = false;}
      if(ThmSATspSA == true){ThmSATspSA = false;}
      if(BeqbDsTzpG == true){BeqbDsTzpG = false;}
      if(CJJkAQNxis == true){CJJkAQNxis = false;}
      if(SbEZlaFydi == true){SbEZlaFydi = false;}
      if(lNNCGNnKqU == true){lNNCGNnKqU = false;}
      if(sXsrAJXBRi == true){sXsrAJXBRi = false;}
      if(FwGYgZZRpc == true){FwGYgZZRpc = false;}
      if(mUVGUnwGem == true){mUVGUnwGem = false;}
      if(cCFOAthMZb == true){cCFOAthMZb = false;}
      if(CEgtdoHoVg == true){CEgtdoHoVg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDCEZVYAZH
{ 
  void nMifJtIOGg()
  { 
      bool AVJqgXSZQq = false;
      bool gCOwLVQpAM = false;
      bool nIACQDiMSs = false;
      bool xbesnkWQKg = false;
      bool YYSCBnmRhP = false;
      bool ULSpbqUGac = false;
      bool oFHWsEWVHZ = false;
      bool yzeSmOoxAb = false;
      bool QQeDYlJoQw = false;
      bool QPphqSRuIw = false;
      bool QQKHQUfzCM = false;
      bool CXGyLYZDyH = false;
      bool uhEKJhJxbU = false;
      bool xsnDLzFXlD = false;
      bool FJmEtrJrVS = false;
      bool rOxBBiMzxh = false;
      bool LiXhPIiCmM = false;
      bool SCRuCluzPQ = false;
      bool YRaIbiwmCb = false;
      bool mGZDrVkFol = false;
      string xYDlJVCeUr;
      string kCNYGyQyEX;
      string WeiPffflJM;
      string LEcBoGhyKI;
      string gOdSFWiUTG;
      string wTIXbSonFd;
      string pPVHgfZMiz;
      string QSmwqIAQJI;
      string wKSCQqwEYV;
      string RsrfRRrVkZ;
      string xWkTpcfMfT;
      string RXdxgewTqp;
      string iUmMhWaHdZ;
      string PdejLZZzMm;
      string KjYFDsPtyl;
      string UYeupciXkS;
      string BYhFDnrtkH;
      string FwGEezugIo;
      string HfIrFqzjsi;
      string pBNskkBTCP;
      if(xYDlJVCeUr == xWkTpcfMfT){AVJqgXSZQq = true;}
      else if(xWkTpcfMfT == xYDlJVCeUr){QQKHQUfzCM = true;}
      if(kCNYGyQyEX == RXdxgewTqp){gCOwLVQpAM = true;}
      else if(RXdxgewTqp == kCNYGyQyEX){CXGyLYZDyH = true;}
      if(WeiPffflJM == iUmMhWaHdZ){nIACQDiMSs = true;}
      else if(iUmMhWaHdZ == WeiPffflJM){uhEKJhJxbU = true;}
      if(LEcBoGhyKI == PdejLZZzMm){xbesnkWQKg = true;}
      else if(PdejLZZzMm == LEcBoGhyKI){xsnDLzFXlD = true;}
      if(gOdSFWiUTG == KjYFDsPtyl){YYSCBnmRhP = true;}
      else if(KjYFDsPtyl == gOdSFWiUTG){FJmEtrJrVS = true;}
      if(wTIXbSonFd == UYeupciXkS){ULSpbqUGac = true;}
      else if(UYeupciXkS == wTIXbSonFd){rOxBBiMzxh = true;}
      if(pPVHgfZMiz == BYhFDnrtkH){oFHWsEWVHZ = true;}
      else if(BYhFDnrtkH == pPVHgfZMiz){LiXhPIiCmM = true;}
      if(QSmwqIAQJI == FwGEezugIo){yzeSmOoxAb = true;}
      if(wKSCQqwEYV == HfIrFqzjsi){QQeDYlJoQw = true;}
      if(RsrfRRrVkZ == pBNskkBTCP){QPphqSRuIw = true;}
      while(FwGEezugIo == QSmwqIAQJI){SCRuCluzPQ = true;}
      while(HfIrFqzjsi == HfIrFqzjsi){YRaIbiwmCb = true;}
      while(pBNskkBTCP == pBNskkBTCP){mGZDrVkFol = true;}
      if(AVJqgXSZQq == true){AVJqgXSZQq = false;}
      if(gCOwLVQpAM == true){gCOwLVQpAM = false;}
      if(nIACQDiMSs == true){nIACQDiMSs = false;}
      if(xbesnkWQKg == true){xbesnkWQKg = false;}
      if(YYSCBnmRhP == true){YYSCBnmRhP = false;}
      if(ULSpbqUGac == true){ULSpbqUGac = false;}
      if(oFHWsEWVHZ == true){oFHWsEWVHZ = false;}
      if(yzeSmOoxAb == true){yzeSmOoxAb = false;}
      if(QQeDYlJoQw == true){QQeDYlJoQw = false;}
      if(QPphqSRuIw == true){QPphqSRuIw = false;}
      if(QQKHQUfzCM == true){QQKHQUfzCM = false;}
      if(CXGyLYZDyH == true){CXGyLYZDyH = false;}
      if(uhEKJhJxbU == true){uhEKJhJxbU = false;}
      if(xsnDLzFXlD == true){xsnDLzFXlD = false;}
      if(FJmEtrJrVS == true){FJmEtrJrVS = false;}
      if(rOxBBiMzxh == true){rOxBBiMzxh = false;}
      if(LiXhPIiCmM == true){LiXhPIiCmM = false;}
      if(SCRuCluzPQ == true){SCRuCluzPQ = false;}
      if(YRaIbiwmCb == true){YRaIbiwmCb = false;}
      if(mGZDrVkFol == true){mGZDrVkFol = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJQGMIPRNC
{ 
  void TLhhMxWGRx()
  { 
      bool XPxWWEsJKH = false;
      bool AnhQpyqcQi = false;
      bool qsKiFSptgm = false;
      bool hXdzRiBsDM = false;
      bool iUTeSiERon = false;
      bool HnMFPdENRD = false;
      bool OzbXYcJiyH = false;
      bool xxZDzVZfQV = false;
      bool OYEsftKXin = false;
      bool dmbzyjswFp = false;
      bool YUShpJNIGs = false;
      bool EXxwootire = false;
      bool SlzKcJVZFO = false;
      bool cdZZwsFVCW = false;
      bool fBRojGpfJI = false;
      bool oKEaWmVIFg = false;
      bool mmDqQaxWzw = false;
      bool jXfUyRTKZW = false;
      bool TpQwZSZzDI = false;
      bool WwQVirxaYJ = false;
      string epDQGwDxkw;
      string cFBYrjJisW;
      string jIapEzRHjB;
      string ZjCafKSkMk;
      string lZRLTSyRZQ;
      string UtLNSVONLG;
      string euMjWrCasg;
      string QYVHkJqPVl;
      string BzhTfeYoIJ;
      string uFZFGpMhnb;
      string PXYrzwYEcI;
      string ezrYFeNsDr;
      string TNRjlLzQBt;
      string wIatVcaoTj;
      string GUMAdwNAza;
      string cTdwHCFnGn;
      string xHDhLVXxDc;
      string EYZTkzBRGp;
      string yyQZRceelT;
      string WlhelyRdnH;
      if(epDQGwDxkw == PXYrzwYEcI){XPxWWEsJKH = true;}
      else if(PXYrzwYEcI == epDQGwDxkw){YUShpJNIGs = true;}
      if(cFBYrjJisW == ezrYFeNsDr){AnhQpyqcQi = true;}
      else if(ezrYFeNsDr == cFBYrjJisW){EXxwootire = true;}
      if(jIapEzRHjB == TNRjlLzQBt){qsKiFSptgm = true;}
      else if(TNRjlLzQBt == jIapEzRHjB){SlzKcJVZFO = true;}
      if(ZjCafKSkMk == wIatVcaoTj){hXdzRiBsDM = true;}
      else if(wIatVcaoTj == ZjCafKSkMk){cdZZwsFVCW = true;}
      if(lZRLTSyRZQ == GUMAdwNAza){iUTeSiERon = true;}
      else if(GUMAdwNAza == lZRLTSyRZQ){fBRojGpfJI = true;}
      if(UtLNSVONLG == cTdwHCFnGn){HnMFPdENRD = true;}
      else if(cTdwHCFnGn == UtLNSVONLG){oKEaWmVIFg = true;}
      if(euMjWrCasg == xHDhLVXxDc){OzbXYcJiyH = true;}
      else if(xHDhLVXxDc == euMjWrCasg){mmDqQaxWzw = true;}
      if(QYVHkJqPVl == EYZTkzBRGp){xxZDzVZfQV = true;}
      if(BzhTfeYoIJ == yyQZRceelT){OYEsftKXin = true;}
      if(uFZFGpMhnb == WlhelyRdnH){dmbzyjswFp = true;}
      while(EYZTkzBRGp == QYVHkJqPVl){jXfUyRTKZW = true;}
      while(yyQZRceelT == yyQZRceelT){TpQwZSZzDI = true;}
      while(WlhelyRdnH == WlhelyRdnH){WwQVirxaYJ = true;}
      if(XPxWWEsJKH == true){XPxWWEsJKH = false;}
      if(AnhQpyqcQi == true){AnhQpyqcQi = false;}
      if(qsKiFSptgm == true){qsKiFSptgm = false;}
      if(hXdzRiBsDM == true){hXdzRiBsDM = false;}
      if(iUTeSiERon == true){iUTeSiERon = false;}
      if(HnMFPdENRD == true){HnMFPdENRD = false;}
      if(OzbXYcJiyH == true){OzbXYcJiyH = false;}
      if(xxZDzVZfQV == true){xxZDzVZfQV = false;}
      if(OYEsftKXin == true){OYEsftKXin = false;}
      if(dmbzyjswFp == true){dmbzyjswFp = false;}
      if(YUShpJNIGs == true){YUShpJNIGs = false;}
      if(EXxwootire == true){EXxwootire = false;}
      if(SlzKcJVZFO == true){SlzKcJVZFO = false;}
      if(cdZZwsFVCW == true){cdZZwsFVCW = false;}
      if(fBRojGpfJI == true){fBRojGpfJI = false;}
      if(oKEaWmVIFg == true){oKEaWmVIFg = false;}
      if(mmDqQaxWzw == true){mmDqQaxWzw = false;}
      if(jXfUyRTKZW == true){jXfUyRTKZW = false;}
      if(TpQwZSZzDI == true){TpQwZSZzDI = false;}
      if(WwQVirxaYJ == true){WwQVirxaYJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABYDMFZSSG
{ 
  void QURxZcfqSs()
  { 
      bool wQhwewVJRu = false;
      bool JiWBmNCHKe = false;
      bool jZdzCcJFET = false;
      bool LzSzQUwTdd = false;
      bool tOetMcROGg = false;
      bool WeABLVmitC = false;
      bool lPFxiJPXjR = false;
      bool QhcfkUujlZ = false;
      bool KtzWwgzRmt = false;
      bool hNZaqdJgKC = false;
      bool NtdnQoBTQp = false;
      bool aDwUrrPhBC = false;
      bool KykpjDICnG = false;
      bool LOYjLQPLGH = false;
      bool feAwTdQFiz = false;
      bool OaeHrOJnDM = false;
      bool fzfKeMdMIa = false;
      bool bEasVeynVG = false;
      bool mCSnqkiQqx = false;
      bool HbHtagzoRG = false;
      string nufzNkczoD;
      string CWoFzanlzj;
      string sWRzYwlwRn;
      string famILYSomV;
      string JUuRVJqMVD;
      string ZsAICQdfaQ;
      string yggAWajgta;
      string IyzcZXbAdP;
      string FZaOOlZdFt;
      string ulOWWcnttt;
      string YKRtubtWhe;
      string ocCLKYGSlj;
      string AFazfVibGx;
      string jgGipuHfSm;
      string qCuaESjDLx;
      string WUIJsTiROY;
      string rSQktIVSUO;
      string RZzyryJAuN;
      string leQJaPYwoV;
      string MoQstYlKgw;
      if(nufzNkczoD == YKRtubtWhe){wQhwewVJRu = true;}
      else if(YKRtubtWhe == nufzNkczoD){NtdnQoBTQp = true;}
      if(CWoFzanlzj == ocCLKYGSlj){JiWBmNCHKe = true;}
      else if(ocCLKYGSlj == CWoFzanlzj){aDwUrrPhBC = true;}
      if(sWRzYwlwRn == AFazfVibGx){jZdzCcJFET = true;}
      else if(AFazfVibGx == sWRzYwlwRn){KykpjDICnG = true;}
      if(famILYSomV == jgGipuHfSm){LzSzQUwTdd = true;}
      else if(jgGipuHfSm == famILYSomV){LOYjLQPLGH = true;}
      if(JUuRVJqMVD == qCuaESjDLx){tOetMcROGg = true;}
      else if(qCuaESjDLx == JUuRVJqMVD){feAwTdQFiz = true;}
      if(ZsAICQdfaQ == WUIJsTiROY){WeABLVmitC = true;}
      else if(WUIJsTiROY == ZsAICQdfaQ){OaeHrOJnDM = true;}
      if(yggAWajgta == rSQktIVSUO){lPFxiJPXjR = true;}
      else if(rSQktIVSUO == yggAWajgta){fzfKeMdMIa = true;}
      if(IyzcZXbAdP == RZzyryJAuN){QhcfkUujlZ = true;}
      if(FZaOOlZdFt == leQJaPYwoV){KtzWwgzRmt = true;}
      if(ulOWWcnttt == MoQstYlKgw){hNZaqdJgKC = true;}
      while(RZzyryJAuN == IyzcZXbAdP){bEasVeynVG = true;}
      while(leQJaPYwoV == leQJaPYwoV){mCSnqkiQqx = true;}
      while(MoQstYlKgw == MoQstYlKgw){HbHtagzoRG = true;}
      if(wQhwewVJRu == true){wQhwewVJRu = false;}
      if(JiWBmNCHKe == true){JiWBmNCHKe = false;}
      if(jZdzCcJFET == true){jZdzCcJFET = false;}
      if(LzSzQUwTdd == true){LzSzQUwTdd = false;}
      if(tOetMcROGg == true){tOetMcROGg = false;}
      if(WeABLVmitC == true){WeABLVmitC = false;}
      if(lPFxiJPXjR == true){lPFxiJPXjR = false;}
      if(QhcfkUujlZ == true){QhcfkUujlZ = false;}
      if(KtzWwgzRmt == true){KtzWwgzRmt = false;}
      if(hNZaqdJgKC == true){hNZaqdJgKC = false;}
      if(NtdnQoBTQp == true){NtdnQoBTQp = false;}
      if(aDwUrrPhBC == true){aDwUrrPhBC = false;}
      if(KykpjDICnG == true){KykpjDICnG = false;}
      if(LOYjLQPLGH == true){LOYjLQPLGH = false;}
      if(feAwTdQFiz == true){feAwTdQFiz = false;}
      if(OaeHrOJnDM == true){OaeHrOJnDM = false;}
      if(fzfKeMdMIa == true){fzfKeMdMIa = false;}
      if(bEasVeynVG == true){bEasVeynVG = false;}
      if(mCSnqkiQqx == true){mCSnqkiQqx = false;}
      if(HbHtagzoRG == true){HbHtagzoRG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBDOOUCNUB
{ 
  void VfJklNJGQR()
  { 
      bool HglrZbmdpI = false;
      bool dHsFuSFmIi = false;
      bool rzKoDYahbg = false;
      bool aLouBeAdMn = false;
      bool JqwALuawQt = false;
      bool DEcQWIVwoA = false;
      bool BFCIgRRyDQ = false;
      bool RaZUYACKdH = false;
      bool ydQhcWiXYs = false;
      bool JDoLlEnmSs = false;
      bool ccrAbbdHqV = false;
      bool FKSgCWoUfK = false;
      bool itZKGNkOhU = false;
      bool LPrjeVlPFA = false;
      bool rafCmykIIO = false;
      bool OTHHKiDgsN = false;
      bool pPZWJpShCf = false;
      bool kYOeRHNWXI = false;
      bool bcFSFrIkZu = false;
      bool SEVrJcBJrx = false;
      string kZpySygolN;
      string BhCKcbfsHw;
      string lUtozyTDgE;
      string CUTltbHMWP;
      string bGHTrygGTp;
      string cSXOrPeByU;
      string ecHhLgNPQA;
      string TSWqTeNawB;
      string QNjqbixFtd;
      string xGOCkyyYIL;
      string jRoSVJwftN;
      string CDEwEQsPGb;
      string jIVlDNETGU;
      string fnSkRyXQUR;
      string lQKgbsBRxT;
      string EhSfbbwDPI;
      string FbZYgNkTeF;
      string sbunpSxoJJ;
      string MmWmQxVlIo;
      string CTBMMJqkzO;
      if(kZpySygolN == jRoSVJwftN){HglrZbmdpI = true;}
      else if(jRoSVJwftN == kZpySygolN){ccrAbbdHqV = true;}
      if(BhCKcbfsHw == CDEwEQsPGb){dHsFuSFmIi = true;}
      else if(CDEwEQsPGb == BhCKcbfsHw){FKSgCWoUfK = true;}
      if(lUtozyTDgE == jIVlDNETGU){rzKoDYahbg = true;}
      else if(jIVlDNETGU == lUtozyTDgE){itZKGNkOhU = true;}
      if(CUTltbHMWP == fnSkRyXQUR){aLouBeAdMn = true;}
      else if(fnSkRyXQUR == CUTltbHMWP){LPrjeVlPFA = true;}
      if(bGHTrygGTp == lQKgbsBRxT){JqwALuawQt = true;}
      else if(lQKgbsBRxT == bGHTrygGTp){rafCmykIIO = true;}
      if(cSXOrPeByU == EhSfbbwDPI){DEcQWIVwoA = true;}
      else if(EhSfbbwDPI == cSXOrPeByU){OTHHKiDgsN = true;}
      if(ecHhLgNPQA == FbZYgNkTeF){BFCIgRRyDQ = true;}
      else if(FbZYgNkTeF == ecHhLgNPQA){pPZWJpShCf = true;}
      if(TSWqTeNawB == sbunpSxoJJ){RaZUYACKdH = true;}
      if(QNjqbixFtd == MmWmQxVlIo){ydQhcWiXYs = true;}
      if(xGOCkyyYIL == CTBMMJqkzO){JDoLlEnmSs = true;}
      while(sbunpSxoJJ == TSWqTeNawB){kYOeRHNWXI = true;}
      while(MmWmQxVlIo == MmWmQxVlIo){bcFSFrIkZu = true;}
      while(CTBMMJqkzO == CTBMMJqkzO){SEVrJcBJrx = true;}
      if(HglrZbmdpI == true){HglrZbmdpI = false;}
      if(dHsFuSFmIi == true){dHsFuSFmIi = false;}
      if(rzKoDYahbg == true){rzKoDYahbg = false;}
      if(aLouBeAdMn == true){aLouBeAdMn = false;}
      if(JqwALuawQt == true){JqwALuawQt = false;}
      if(DEcQWIVwoA == true){DEcQWIVwoA = false;}
      if(BFCIgRRyDQ == true){BFCIgRRyDQ = false;}
      if(RaZUYACKdH == true){RaZUYACKdH = false;}
      if(ydQhcWiXYs == true){ydQhcWiXYs = false;}
      if(JDoLlEnmSs == true){JDoLlEnmSs = false;}
      if(ccrAbbdHqV == true){ccrAbbdHqV = false;}
      if(FKSgCWoUfK == true){FKSgCWoUfK = false;}
      if(itZKGNkOhU == true){itZKGNkOhU = false;}
      if(LPrjeVlPFA == true){LPrjeVlPFA = false;}
      if(rafCmykIIO == true){rafCmykIIO = false;}
      if(OTHHKiDgsN == true){OTHHKiDgsN = false;}
      if(pPZWJpShCf == true){pPZWJpShCf = false;}
      if(kYOeRHNWXI == true){kYOeRHNWXI = false;}
      if(bcFSFrIkZu == true){bcFSFrIkZu = false;}
      if(SEVrJcBJrx == true){SEVrJcBJrx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIPJBAHWLV
{ 
  void dHIFiYVHtZ()
  { 
      bool GeFayemAQs = false;
      bool zDXzhPcQDS = false;
      bool LVbcAPrsMY = false;
      bool jRRaDPHycH = false;
      bool ggWFfHZdzy = false;
      bool aAKoIkCcai = false;
      bool ltnqIgkxwR = false;
      bool HenwkezWxs = false;
      bool oNtNxjGcRS = false;
      bool NeXsUmsewy = false;
      bool VchgpwLOEd = false;
      bool kefhsYzZsY = false;
      bool ZIecEcGuby = false;
      bool kTayWLeMWB = false;
      bool XrYnghypzu = false;
      bool mSkXYNyEbN = false;
      bool oQmFrQEhLg = false;
      bool smDrAgjpwW = false;
      bool dQufKSiCZI = false;
      bool NakJLGFSuP = false;
      string dyjOLdaNfp;
      string LbICoWkVDq;
      string GVwNRYBqoM;
      string iHHVaIxdYV;
      string tXPkLmlFRC;
      string NMPZEIBWxm;
      string biXSGETlbg;
      string ZHxhxhFLBd;
      string mwYmyVqhQR;
      string GZflsKzwdH;
      string SzdkcFOgcV;
      string DpUSzfJkUj;
      string MlVJazaLnl;
      string iJgtLnRnKs;
      string HKFuOPFNlM;
      string AObsufdTKc;
      string dCrpmsJaHK;
      string NVaacCgZuK;
      string tNZblUhmye;
      string KydgOEROHU;
      if(dyjOLdaNfp == SzdkcFOgcV){GeFayemAQs = true;}
      else if(SzdkcFOgcV == dyjOLdaNfp){VchgpwLOEd = true;}
      if(LbICoWkVDq == DpUSzfJkUj){zDXzhPcQDS = true;}
      else if(DpUSzfJkUj == LbICoWkVDq){kefhsYzZsY = true;}
      if(GVwNRYBqoM == MlVJazaLnl){LVbcAPrsMY = true;}
      else if(MlVJazaLnl == GVwNRYBqoM){ZIecEcGuby = true;}
      if(iHHVaIxdYV == iJgtLnRnKs){jRRaDPHycH = true;}
      else if(iJgtLnRnKs == iHHVaIxdYV){kTayWLeMWB = true;}
      if(tXPkLmlFRC == HKFuOPFNlM){ggWFfHZdzy = true;}
      else if(HKFuOPFNlM == tXPkLmlFRC){XrYnghypzu = true;}
      if(NMPZEIBWxm == AObsufdTKc){aAKoIkCcai = true;}
      else if(AObsufdTKc == NMPZEIBWxm){mSkXYNyEbN = true;}
      if(biXSGETlbg == dCrpmsJaHK){ltnqIgkxwR = true;}
      else if(dCrpmsJaHK == biXSGETlbg){oQmFrQEhLg = true;}
      if(ZHxhxhFLBd == NVaacCgZuK){HenwkezWxs = true;}
      if(mwYmyVqhQR == tNZblUhmye){oNtNxjGcRS = true;}
      if(GZflsKzwdH == KydgOEROHU){NeXsUmsewy = true;}
      while(NVaacCgZuK == ZHxhxhFLBd){smDrAgjpwW = true;}
      while(tNZblUhmye == tNZblUhmye){dQufKSiCZI = true;}
      while(KydgOEROHU == KydgOEROHU){NakJLGFSuP = true;}
      if(GeFayemAQs == true){GeFayemAQs = false;}
      if(zDXzhPcQDS == true){zDXzhPcQDS = false;}
      if(LVbcAPrsMY == true){LVbcAPrsMY = false;}
      if(jRRaDPHycH == true){jRRaDPHycH = false;}
      if(ggWFfHZdzy == true){ggWFfHZdzy = false;}
      if(aAKoIkCcai == true){aAKoIkCcai = false;}
      if(ltnqIgkxwR == true){ltnqIgkxwR = false;}
      if(HenwkezWxs == true){HenwkezWxs = false;}
      if(oNtNxjGcRS == true){oNtNxjGcRS = false;}
      if(NeXsUmsewy == true){NeXsUmsewy = false;}
      if(VchgpwLOEd == true){VchgpwLOEd = false;}
      if(kefhsYzZsY == true){kefhsYzZsY = false;}
      if(ZIecEcGuby == true){ZIecEcGuby = false;}
      if(kTayWLeMWB == true){kTayWLeMWB = false;}
      if(XrYnghypzu == true){XrYnghypzu = false;}
      if(mSkXYNyEbN == true){mSkXYNyEbN = false;}
      if(oQmFrQEhLg == true){oQmFrQEhLg = false;}
      if(smDrAgjpwW == true){smDrAgjpwW = false;}
      if(dQufKSiCZI == true){dQufKSiCZI = false;}
      if(NakJLGFSuP == true){NakJLGFSuP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPOJAPACNW
{ 
  void oDOiRbJhyD()
  { 
      bool nUePgluhAs = false;
      bool lujVMZMMry = false;
      bool PbBwkZMqnd = false;
      bool sNAOyCSUwd = false;
      bool XCAxZbnDex = false;
      bool DDeHULTidG = false;
      bool YDtVAXtUWK = false;
      bool HrPOZMbEWJ = false;
      bool lIMpaoirtm = false;
      bool hippETIewB = false;
      bool hSfUpKnPgH = false;
      bool jPMUUPqEuL = false;
      bool nBajbXCZKF = false;
      bool EwHUaScqAP = false;
      bool BTLlCSWVUn = false;
      bool cEikNfrwrR = false;
      bool INEaDmHqsC = false;
      bool mzEeJUpogJ = false;
      bool AgEWcANWGu = false;
      bool ZfzhHmOjiP = false;
      string FRCYbyTPwR;
      string iqzibjREfe;
      string otlDGrIHFi;
      string nKyldbyzoe;
      string CBOhqhpbNH;
      string cUCXBLfyRi;
      string oMKNcYrMEA;
      string kSOAcnfDMY;
      string CgtyFTIajR;
      string uzgFoopAFS;
      string odWMVKFBuN;
      string fclrgISLHI;
      string PRblEklIKm;
      string xeysjYJgbu;
      string NGfVlSNnYg;
      string WeswCXBjHj;
      string XxpIQBdrII;
      string zkiLuIkGAl;
      string XyjdPSkBqL;
      string WYYrXQPWFk;
      if(FRCYbyTPwR == odWMVKFBuN){nUePgluhAs = true;}
      else if(odWMVKFBuN == FRCYbyTPwR){hSfUpKnPgH = true;}
      if(iqzibjREfe == fclrgISLHI){lujVMZMMry = true;}
      else if(fclrgISLHI == iqzibjREfe){jPMUUPqEuL = true;}
      if(otlDGrIHFi == PRblEklIKm){PbBwkZMqnd = true;}
      else if(PRblEklIKm == otlDGrIHFi){nBajbXCZKF = true;}
      if(nKyldbyzoe == xeysjYJgbu){sNAOyCSUwd = true;}
      else if(xeysjYJgbu == nKyldbyzoe){EwHUaScqAP = true;}
      if(CBOhqhpbNH == NGfVlSNnYg){XCAxZbnDex = true;}
      else if(NGfVlSNnYg == CBOhqhpbNH){BTLlCSWVUn = true;}
      if(cUCXBLfyRi == WeswCXBjHj){DDeHULTidG = true;}
      else if(WeswCXBjHj == cUCXBLfyRi){cEikNfrwrR = true;}
      if(oMKNcYrMEA == XxpIQBdrII){YDtVAXtUWK = true;}
      else if(XxpIQBdrII == oMKNcYrMEA){INEaDmHqsC = true;}
      if(kSOAcnfDMY == zkiLuIkGAl){HrPOZMbEWJ = true;}
      if(CgtyFTIajR == XyjdPSkBqL){lIMpaoirtm = true;}
      if(uzgFoopAFS == WYYrXQPWFk){hippETIewB = true;}
      while(zkiLuIkGAl == kSOAcnfDMY){mzEeJUpogJ = true;}
      while(XyjdPSkBqL == XyjdPSkBqL){AgEWcANWGu = true;}
      while(WYYrXQPWFk == WYYrXQPWFk){ZfzhHmOjiP = true;}
      if(nUePgluhAs == true){nUePgluhAs = false;}
      if(lujVMZMMry == true){lujVMZMMry = false;}
      if(PbBwkZMqnd == true){PbBwkZMqnd = false;}
      if(sNAOyCSUwd == true){sNAOyCSUwd = false;}
      if(XCAxZbnDex == true){XCAxZbnDex = false;}
      if(DDeHULTidG == true){DDeHULTidG = false;}
      if(YDtVAXtUWK == true){YDtVAXtUWK = false;}
      if(HrPOZMbEWJ == true){HrPOZMbEWJ = false;}
      if(lIMpaoirtm == true){lIMpaoirtm = false;}
      if(hippETIewB == true){hippETIewB = false;}
      if(hSfUpKnPgH == true){hSfUpKnPgH = false;}
      if(jPMUUPqEuL == true){jPMUUPqEuL = false;}
      if(nBajbXCZKF == true){nBajbXCZKF = false;}
      if(EwHUaScqAP == true){EwHUaScqAP = false;}
      if(BTLlCSWVUn == true){BTLlCSWVUn = false;}
      if(cEikNfrwrR == true){cEikNfrwrR = false;}
      if(INEaDmHqsC == true){INEaDmHqsC = false;}
      if(mzEeJUpogJ == true){mzEeJUpogJ = false;}
      if(AgEWcANWGu == true){AgEWcANWGu = false;}
      if(ZfzhHmOjiP == true){ZfzhHmOjiP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYXNMVAISN
{ 
  void OpqqZwaTfY()
  { 
      bool tNKBXuyTtu = false;
      bool dSmYbxlhVF = false;
      bool CCethhoTcT = false;
      bool MpMjclZfpO = false;
      bool tMKkMulXpx = false;
      bool ItBPtqiQTo = false;
      bool FdqZimFDwo = false;
      bool WFrHKorsgl = false;
      bool wRceLRowok = false;
      bool DJMAJQUjCZ = false;
      bool oibAZCCsFF = false;
      bool zoigsmAMOQ = false;
      bool xINKlNsqyt = false;
      bool THpGwMpcEI = false;
      bool PuqjlOZeHV = false;
      bool PIVlcgUQOM = false;
      bool JKuKkryckf = false;
      bool xXHFBBRdYW = false;
      bool mNjbeLkEdP = false;
      bool rZNryEAgys = false;
      string jrqHBnRNun;
      string RxUUgcUXlL;
      string tHYxuXKYgB;
      string ykEURmyZkK;
      string GynafDEjMh;
      string IkTcXbStLd;
      string crftogszCs;
      string etlbFwTyQr;
      string SaMyrMRawo;
      string UDOHhNRtkz;
      string JEgTDOyqXb;
      string ITcSKBfgBc;
      string ORDNXafetq;
      string dYMQhOssud;
      string NZDUfAZuxf;
      string hkrIjrBTwc;
      string hTxfyiGMju;
      string HmlXOoOhgW;
      string AkhOJsgEgp;
      string NZxSutcXVx;
      if(jrqHBnRNun == JEgTDOyqXb){tNKBXuyTtu = true;}
      else if(JEgTDOyqXb == jrqHBnRNun){oibAZCCsFF = true;}
      if(RxUUgcUXlL == ITcSKBfgBc){dSmYbxlhVF = true;}
      else if(ITcSKBfgBc == RxUUgcUXlL){zoigsmAMOQ = true;}
      if(tHYxuXKYgB == ORDNXafetq){CCethhoTcT = true;}
      else if(ORDNXafetq == tHYxuXKYgB){xINKlNsqyt = true;}
      if(ykEURmyZkK == dYMQhOssud){MpMjclZfpO = true;}
      else if(dYMQhOssud == ykEURmyZkK){THpGwMpcEI = true;}
      if(GynafDEjMh == NZDUfAZuxf){tMKkMulXpx = true;}
      else if(NZDUfAZuxf == GynafDEjMh){PuqjlOZeHV = true;}
      if(IkTcXbStLd == hkrIjrBTwc){ItBPtqiQTo = true;}
      else if(hkrIjrBTwc == IkTcXbStLd){PIVlcgUQOM = true;}
      if(crftogszCs == hTxfyiGMju){FdqZimFDwo = true;}
      else if(hTxfyiGMju == crftogszCs){JKuKkryckf = true;}
      if(etlbFwTyQr == HmlXOoOhgW){WFrHKorsgl = true;}
      if(SaMyrMRawo == AkhOJsgEgp){wRceLRowok = true;}
      if(UDOHhNRtkz == NZxSutcXVx){DJMAJQUjCZ = true;}
      while(HmlXOoOhgW == etlbFwTyQr){xXHFBBRdYW = true;}
      while(AkhOJsgEgp == AkhOJsgEgp){mNjbeLkEdP = true;}
      while(NZxSutcXVx == NZxSutcXVx){rZNryEAgys = true;}
      if(tNKBXuyTtu == true){tNKBXuyTtu = false;}
      if(dSmYbxlhVF == true){dSmYbxlhVF = false;}
      if(CCethhoTcT == true){CCethhoTcT = false;}
      if(MpMjclZfpO == true){MpMjclZfpO = false;}
      if(tMKkMulXpx == true){tMKkMulXpx = false;}
      if(ItBPtqiQTo == true){ItBPtqiQTo = false;}
      if(FdqZimFDwo == true){FdqZimFDwo = false;}
      if(WFrHKorsgl == true){WFrHKorsgl = false;}
      if(wRceLRowok == true){wRceLRowok = false;}
      if(DJMAJQUjCZ == true){DJMAJQUjCZ = false;}
      if(oibAZCCsFF == true){oibAZCCsFF = false;}
      if(zoigsmAMOQ == true){zoigsmAMOQ = false;}
      if(xINKlNsqyt == true){xINKlNsqyt = false;}
      if(THpGwMpcEI == true){THpGwMpcEI = false;}
      if(PuqjlOZeHV == true){PuqjlOZeHV = false;}
      if(PIVlcgUQOM == true){PIVlcgUQOM = false;}
      if(JKuKkryckf == true){JKuKkryckf = false;}
      if(xXHFBBRdYW == true){xXHFBBRdYW = false;}
      if(mNjbeLkEdP == true){mNjbeLkEdP = false;}
      if(rZNryEAgys == true){rZNryEAgys = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZOQAMRCFVM
{ 
  void qNpUkgPCZt()
  { 
      bool GxsDcOkeKn = false;
      bool pnDRuDxQYQ = false;
      bool QknTMFZAeH = false;
      bool EVkhgYfsbu = false;
      bool wpemotLdtZ = false;
      bool JyNfpVIYqW = false;
      bool nkzCjTDUkW = false;
      bool XDodUZFBeS = false;
      bool swFFxFIFrL = false;
      bool QHCEGLqcDV = false;
      bool qqsXCGJiKQ = false;
      bool PHsYdretEd = false;
      bool KxcYGPBjXI = false;
      bool icxJaCDgCq = false;
      bool wYtbuINdaN = false;
      bool fwXYKtOTRm = false;
      bool EYLCgmJjxa = false;
      bool oxrMhkCBdx = false;
      bool BXJJblEXyg = false;
      bool niPPmWNrtH = false;
      string AqRDtDKPBo;
      string aSbeIDsGTW;
      string SmzVSmoDHi;
      string gMluEPHGIo;
      string QiWwaKgDWx;
      string goCkqMrukH;
      string OGIRHOfgas;
      string wmxdGjPCuH;
      string FkgJBrJBDq;
      string WMVBaKaFnM;
      string dAcdBtqYeH;
      string xozcBcZzQP;
      string EedjWiRwCu;
      string JKOidFIDIG;
      string BkVushNrzx;
      string kbnYHyWsGR;
      string ctViylaPzu;
      string UVpJOTIhpn;
      string VYxEJgVobe;
      string iOwpdGOmwH;
      if(AqRDtDKPBo == dAcdBtqYeH){GxsDcOkeKn = true;}
      else if(dAcdBtqYeH == AqRDtDKPBo){qqsXCGJiKQ = true;}
      if(aSbeIDsGTW == xozcBcZzQP){pnDRuDxQYQ = true;}
      else if(xozcBcZzQP == aSbeIDsGTW){PHsYdretEd = true;}
      if(SmzVSmoDHi == EedjWiRwCu){QknTMFZAeH = true;}
      else if(EedjWiRwCu == SmzVSmoDHi){KxcYGPBjXI = true;}
      if(gMluEPHGIo == JKOidFIDIG){EVkhgYfsbu = true;}
      else if(JKOidFIDIG == gMluEPHGIo){icxJaCDgCq = true;}
      if(QiWwaKgDWx == BkVushNrzx){wpemotLdtZ = true;}
      else if(BkVushNrzx == QiWwaKgDWx){wYtbuINdaN = true;}
      if(goCkqMrukH == kbnYHyWsGR){JyNfpVIYqW = true;}
      else if(kbnYHyWsGR == goCkqMrukH){fwXYKtOTRm = true;}
      if(OGIRHOfgas == ctViylaPzu){nkzCjTDUkW = true;}
      else if(ctViylaPzu == OGIRHOfgas){EYLCgmJjxa = true;}
      if(wmxdGjPCuH == UVpJOTIhpn){XDodUZFBeS = true;}
      if(FkgJBrJBDq == VYxEJgVobe){swFFxFIFrL = true;}
      if(WMVBaKaFnM == iOwpdGOmwH){QHCEGLqcDV = true;}
      while(UVpJOTIhpn == wmxdGjPCuH){oxrMhkCBdx = true;}
      while(VYxEJgVobe == VYxEJgVobe){BXJJblEXyg = true;}
      while(iOwpdGOmwH == iOwpdGOmwH){niPPmWNrtH = true;}
      if(GxsDcOkeKn == true){GxsDcOkeKn = false;}
      if(pnDRuDxQYQ == true){pnDRuDxQYQ = false;}
      if(QknTMFZAeH == true){QknTMFZAeH = false;}
      if(EVkhgYfsbu == true){EVkhgYfsbu = false;}
      if(wpemotLdtZ == true){wpemotLdtZ = false;}
      if(JyNfpVIYqW == true){JyNfpVIYqW = false;}
      if(nkzCjTDUkW == true){nkzCjTDUkW = false;}
      if(XDodUZFBeS == true){XDodUZFBeS = false;}
      if(swFFxFIFrL == true){swFFxFIFrL = false;}
      if(QHCEGLqcDV == true){QHCEGLqcDV = false;}
      if(qqsXCGJiKQ == true){qqsXCGJiKQ = false;}
      if(PHsYdretEd == true){PHsYdretEd = false;}
      if(KxcYGPBjXI == true){KxcYGPBjXI = false;}
      if(icxJaCDgCq == true){icxJaCDgCq = false;}
      if(wYtbuINdaN == true){wYtbuINdaN = false;}
      if(fwXYKtOTRm == true){fwXYKtOTRm = false;}
      if(EYLCgmJjxa == true){EYLCgmJjxa = false;}
      if(oxrMhkCBdx == true){oxrMhkCBdx = false;}
      if(BXJJblEXyg == true){BXJJblEXyg = false;}
      if(niPPmWNrtH == true){niPPmWNrtH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTWCTLUSOY
{ 
  void sznDtcVIzE()
  { 
      bool VoyRwOQYyf = false;
      bool zqMnpKHULg = false;
      bool AHYLTzRykt = false;
      bool AXMYxdUACp = false;
      bool rGiNhZXAGa = false;
      bool tcXSHNPlxw = false;
      bool xSmDfbdmqM = false;
      bool pHRVotYKct = false;
      bool aQqKAWztRi = false;
      bool NhCFrZTehG = false;
      bool wkJskmKCdN = false;
      bool nFJDVgabDI = false;
      bool ciUHzHEMcO = false;
      bool ZscWxpGyZM = false;
      bool MwQEtIYzjL = false;
      bool zqbYcMPBtc = false;
      bool iyZOmublFe = false;
      bool ZbCpufSQMp = false;
      bool hFbQPhQDsk = false;
      bool aFEwdOWBQz = false;
      string FMuEPeMqal;
      string PYtcqeDWYJ;
      string nmCmPhXazh;
      string tlcrMkFQqA;
      string KGcJWKHerI;
      string bYWnrRJHng;
      string GlrsrdwBPF;
      string YmeXyhKsQE;
      string asipFUPozt;
      string bybJsYNjRr;
      string OFOljotyoK;
      string GQpjGNDBmW;
      string OHCUdZKUeZ;
      string UabXpUdwGP;
      string aQzonKHrDf;
      string ULwtdHDsHJ;
      string dYTPofoStk;
      string jGuXwxHMgS;
      string SSRyEIegth;
      string QjoxlBxjzH;
      if(FMuEPeMqal == OFOljotyoK){VoyRwOQYyf = true;}
      else if(OFOljotyoK == FMuEPeMqal){wkJskmKCdN = true;}
      if(PYtcqeDWYJ == GQpjGNDBmW){zqMnpKHULg = true;}
      else if(GQpjGNDBmW == PYtcqeDWYJ){nFJDVgabDI = true;}
      if(nmCmPhXazh == OHCUdZKUeZ){AHYLTzRykt = true;}
      else if(OHCUdZKUeZ == nmCmPhXazh){ciUHzHEMcO = true;}
      if(tlcrMkFQqA == UabXpUdwGP){AXMYxdUACp = true;}
      else if(UabXpUdwGP == tlcrMkFQqA){ZscWxpGyZM = true;}
      if(KGcJWKHerI == aQzonKHrDf){rGiNhZXAGa = true;}
      else if(aQzonKHrDf == KGcJWKHerI){MwQEtIYzjL = true;}
      if(bYWnrRJHng == ULwtdHDsHJ){tcXSHNPlxw = true;}
      else if(ULwtdHDsHJ == bYWnrRJHng){zqbYcMPBtc = true;}
      if(GlrsrdwBPF == dYTPofoStk){xSmDfbdmqM = true;}
      else if(dYTPofoStk == GlrsrdwBPF){iyZOmublFe = true;}
      if(YmeXyhKsQE == jGuXwxHMgS){pHRVotYKct = true;}
      if(asipFUPozt == SSRyEIegth){aQqKAWztRi = true;}
      if(bybJsYNjRr == QjoxlBxjzH){NhCFrZTehG = true;}
      while(jGuXwxHMgS == YmeXyhKsQE){ZbCpufSQMp = true;}
      while(SSRyEIegth == SSRyEIegth){hFbQPhQDsk = true;}
      while(QjoxlBxjzH == QjoxlBxjzH){aFEwdOWBQz = true;}
      if(VoyRwOQYyf == true){VoyRwOQYyf = false;}
      if(zqMnpKHULg == true){zqMnpKHULg = false;}
      if(AHYLTzRykt == true){AHYLTzRykt = false;}
      if(AXMYxdUACp == true){AXMYxdUACp = false;}
      if(rGiNhZXAGa == true){rGiNhZXAGa = false;}
      if(tcXSHNPlxw == true){tcXSHNPlxw = false;}
      if(xSmDfbdmqM == true){xSmDfbdmqM = false;}
      if(pHRVotYKct == true){pHRVotYKct = false;}
      if(aQqKAWztRi == true){aQqKAWztRi = false;}
      if(NhCFrZTehG == true){NhCFrZTehG = false;}
      if(wkJskmKCdN == true){wkJskmKCdN = false;}
      if(nFJDVgabDI == true){nFJDVgabDI = false;}
      if(ciUHzHEMcO == true){ciUHzHEMcO = false;}
      if(ZscWxpGyZM == true){ZscWxpGyZM = false;}
      if(MwQEtIYzjL == true){MwQEtIYzjL = false;}
      if(zqbYcMPBtc == true){zqbYcMPBtc = false;}
      if(iyZOmublFe == true){iyZOmublFe = false;}
      if(ZbCpufSQMp == true){ZbCpufSQMp = false;}
      if(hFbQPhQDsk == true){hFbQPhQDsk = false;}
      if(aFEwdOWBQz == true){aFEwdOWBQz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENJGMHEJXQ
{ 
  void GUzTWjntEU()
  { 
      bool FdrSQzOFyE = false;
      bool XEJWSGLGky = false;
      bool GAQUOeolFq = false;
      bool LmkUpTBueQ = false;
      bool jELQNsJDLR = false;
      bool qACaVFMWEl = false;
      bool JczGrjSogz = false;
      bool FQaTNBnAHU = false;
      bool VkZnALkKzk = false;
      bool GdqsHHFEXd = false;
      bool ZUWMLaZiMT = false;
      bool QMPiQXCLFg = false;
      bool zIousbYgLG = false;
      bool wjbctAONbZ = false;
      bool kCxeTsOHci = false;
      bool EsyqdReaSj = false;
      bool BrWGXfjlnP = false;
      bool JojfuxKJbz = false;
      bool NRDcBDkkzc = false;
      bool VmtrXseqHm = false;
      string YmSpbMRCSf;
      string rnpjAYTloC;
      string LkFwyqOnMx;
      string LpCGqLQiom;
      string AjGkDzfpSl;
      string eQQhFnhWqj;
      string ydoUTCkiso;
      string HkxBBadUsz;
      string KXVaSuYUBC;
      string dtqEoWukQA;
      string OxxcdsSOfd;
      string JNdrZZHNCX;
      string cPhpLNssLe;
      string fsDrjNarwY;
      string cJoWsPPzeP;
      string OgisWyPHRQ;
      string AZCBxQKlHM;
      string yPRdtSaKxu;
      string xsNwPzJJUl;
      string yTZeXCHmYb;
      if(YmSpbMRCSf == OxxcdsSOfd){FdrSQzOFyE = true;}
      else if(OxxcdsSOfd == YmSpbMRCSf){ZUWMLaZiMT = true;}
      if(rnpjAYTloC == JNdrZZHNCX){XEJWSGLGky = true;}
      else if(JNdrZZHNCX == rnpjAYTloC){QMPiQXCLFg = true;}
      if(LkFwyqOnMx == cPhpLNssLe){GAQUOeolFq = true;}
      else if(cPhpLNssLe == LkFwyqOnMx){zIousbYgLG = true;}
      if(LpCGqLQiom == fsDrjNarwY){LmkUpTBueQ = true;}
      else if(fsDrjNarwY == LpCGqLQiom){wjbctAONbZ = true;}
      if(AjGkDzfpSl == cJoWsPPzeP){jELQNsJDLR = true;}
      else if(cJoWsPPzeP == AjGkDzfpSl){kCxeTsOHci = true;}
      if(eQQhFnhWqj == OgisWyPHRQ){qACaVFMWEl = true;}
      else if(OgisWyPHRQ == eQQhFnhWqj){EsyqdReaSj = true;}
      if(ydoUTCkiso == AZCBxQKlHM){JczGrjSogz = true;}
      else if(AZCBxQKlHM == ydoUTCkiso){BrWGXfjlnP = true;}
      if(HkxBBadUsz == yPRdtSaKxu){FQaTNBnAHU = true;}
      if(KXVaSuYUBC == xsNwPzJJUl){VkZnALkKzk = true;}
      if(dtqEoWukQA == yTZeXCHmYb){GdqsHHFEXd = true;}
      while(yPRdtSaKxu == HkxBBadUsz){JojfuxKJbz = true;}
      while(xsNwPzJJUl == xsNwPzJJUl){NRDcBDkkzc = true;}
      while(yTZeXCHmYb == yTZeXCHmYb){VmtrXseqHm = true;}
      if(FdrSQzOFyE == true){FdrSQzOFyE = false;}
      if(XEJWSGLGky == true){XEJWSGLGky = false;}
      if(GAQUOeolFq == true){GAQUOeolFq = false;}
      if(LmkUpTBueQ == true){LmkUpTBueQ = false;}
      if(jELQNsJDLR == true){jELQNsJDLR = false;}
      if(qACaVFMWEl == true){qACaVFMWEl = false;}
      if(JczGrjSogz == true){JczGrjSogz = false;}
      if(FQaTNBnAHU == true){FQaTNBnAHU = false;}
      if(VkZnALkKzk == true){VkZnALkKzk = false;}
      if(GdqsHHFEXd == true){GdqsHHFEXd = false;}
      if(ZUWMLaZiMT == true){ZUWMLaZiMT = false;}
      if(QMPiQXCLFg == true){QMPiQXCLFg = false;}
      if(zIousbYgLG == true){zIousbYgLG = false;}
      if(wjbctAONbZ == true){wjbctAONbZ = false;}
      if(kCxeTsOHci == true){kCxeTsOHci = false;}
      if(EsyqdReaSj == true){EsyqdReaSj = false;}
      if(BrWGXfjlnP == true){BrWGXfjlnP = false;}
      if(JojfuxKJbz == true){JojfuxKJbz = false;}
      if(NRDcBDkkzc == true){NRDcBDkkzc = false;}
      if(VmtrXseqHm == true){VmtrXseqHm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXSXPABBPW
{ 
  void VVYPekhujc()
  { 
      bool adQCFnDsyt = false;
      bool nkHFJgdfnW = false;
      bool hJMJxDWMao = false;
      bool jNJQxtNXtW = false;
      bool dDZwayMqbk = false;
      bool FUQEkRQGEB = false;
      bool RqRIJZbpIP = false;
      bool SGlRreiPiz = false;
      bool qekojOxEee = false;
      bool cHSsFmkQmA = false;
      bool WViLSzizMG = false;
      bool hBXFJlFcYt = false;
      bool cWLclLnrLE = false;
      bool sRbhcVwYWj = false;
      bool fyrXwbiNiT = false;
      bool gIrsXAJFZG = false;
      bool LqmHNQYobn = false;
      bool ogFoOddmfK = false;
      bool bZIqXjZiKc = false;
      bool LqzPYnKkKf = false;
      string qHpXoaCibO;
      string GJFLeWhcWD;
      string EkpocMFVIt;
      string xrMTRHJexh;
      string hxrEPbWTiB;
      string jtznxGRBub;
      string UgahRNwktX;
      string NDfoUHskZA;
      string pllHKDrXVL;
      string pIiVMBVJmB;
      string ekZLmfOJSp;
      string NfatlitSXO;
      string UXPhhFTJcS;
      string kixXVELaTd;
      string niFfyJgojc;
      string HDlYgGUqdh;
      string LEgAEdhDYg;
      string XTzsZlSjjX;
      string XeZALhwYqO;
      string iTwlSjBFaT;
      if(qHpXoaCibO == ekZLmfOJSp){adQCFnDsyt = true;}
      else if(ekZLmfOJSp == qHpXoaCibO){WViLSzizMG = true;}
      if(GJFLeWhcWD == NfatlitSXO){nkHFJgdfnW = true;}
      else if(NfatlitSXO == GJFLeWhcWD){hBXFJlFcYt = true;}
      if(EkpocMFVIt == UXPhhFTJcS){hJMJxDWMao = true;}
      else if(UXPhhFTJcS == EkpocMFVIt){cWLclLnrLE = true;}
      if(xrMTRHJexh == kixXVELaTd){jNJQxtNXtW = true;}
      else if(kixXVELaTd == xrMTRHJexh){sRbhcVwYWj = true;}
      if(hxrEPbWTiB == niFfyJgojc){dDZwayMqbk = true;}
      else if(niFfyJgojc == hxrEPbWTiB){fyrXwbiNiT = true;}
      if(jtznxGRBub == HDlYgGUqdh){FUQEkRQGEB = true;}
      else if(HDlYgGUqdh == jtznxGRBub){gIrsXAJFZG = true;}
      if(UgahRNwktX == LEgAEdhDYg){RqRIJZbpIP = true;}
      else if(LEgAEdhDYg == UgahRNwktX){LqmHNQYobn = true;}
      if(NDfoUHskZA == XTzsZlSjjX){SGlRreiPiz = true;}
      if(pllHKDrXVL == XeZALhwYqO){qekojOxEee = true;}
      if(pIiVMBVJmB == iTwlSjBFaT){cHSsFmkQmA = true;}
      while(XTzsZlSjjX == NDfoUHskZA){ogFoOddmfK = true;}
      while(XeZALhwYqO == XeZALhwYqO){bZIqXjZiKc = true;}
      while(iTwlSjBFaT == iTwlSjBFaT){LqzPYnKkKf = true;}
      if(adQCFnDsyt == true){adQCFnDsyt = false;}
      if(nkHFJgdfnW == true){nkHFJgdfnW = false;}
      if(hJMJxDWMao == true){hJMJxDWMao = false;}
      if(jNJQxtNXtW == true){jNJQxtNXtW = false;}
      if(dDZwayMqbk == true){dDZwayMqbk = false;}
      if(FUQEkRQGEB == true){FUQEkRQGEB = false;}
      if(RqRIJZbpIP == true){RqRIJZbpIP = false;}
      if(SGlRreiPiz == true){SGlRreiPiz = false;}
      if(qekojOxEee == true){qekojOxEee = false;}
      if(cHSsFmkQmA == true){cHSsFmkQmA = false;}
      if(WViLSzizMG == true){WViLSzizMG = false;}
      if(hBXFJlFcYt == true){hBXFJlFcYt = false;}
      if(cWLclLnrLE == true){cWLclLnrLE = false;}
      if(sRbhcVwYWj == true){sRbhcVwYWj = false;}
      if(fyrXwbiNiT == true){fyrXwbiNiT = false;}
      if(gIrsXAJFZG == true){gIrsXAJFZG = false;}
      if(LqmHNQYobn == true){LqmHNQYobn = false;}
      if(ogFoOddmfK == true){ogFoOddmfK = false;}
      if(bZIqXjZiKc == true){bZIqXjZiKc = false;}
      if(LqzPYnKkKf == true){LqzPYnKkKf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXNWTHWXJH
{ 
  void JcREGlNxYV()
  { 
      bool KqDPuSjRri = false;
      bool XxcOIUAOCb = false;
      bool UZdStRasXG = false;
      bool TYTkPSXDNx = false;
      bool NCpTsHHcLy = false;
      bool OdpJUkNkUd = false;
      bool qqtkOycqyo = false;
      bool xxAFOSiJZm = false;
      bool KyhZroiKQe = false;
      bool FmhjFWIFFt = false;
      bool dPdWAQdjtB = false;
      bool CDKhSsIUsY = false;
      bool OSaTiKPQzr = false;
      bool KcDeItTKYb = false;
      bool LyPObBbAQM = false;
      bool NnLfeLoJmo = false;
      bool BMjCqYzfYY = false;
      bool YyuRNPCLrh = false;
      bool iOzmdVRXzw = false;
      bool FJXiZyNNWC = false;
      string KAwMpLkZMj;
      string OtJVTCgSim;
      string sublzCSVgd;
      string sglHOzOpLj;
      string AtzJJaXREp;
      string CIgGWPYJNm;
      string sPripgICGU;
      string nqGzlyuRcX;
      string dAQpbkAejz;
      string ZEbYqjBQTc;
      string RVLjCLBgTX;
      string TGgoIrzCHF;
      string fcRGtiOhIB;
      string xdyzFIognP;
      string iSLMfTXmPy;
      string kzJOwoDEoS;
      string wTYSapIgiA;
      string CSOqVNRFaa;
      string KaSJPyUiDQ;
      string FkqUTPsrko;
      if(KAwMpLkZMj == RVLjCLBgTX){KqDPuSjRri = true;}
      else if(RVLjCLBgTX == KAwMpLkZMj){dPdWAQdjtB = true;}
      if(OtJVTCgSim == TGgoIrzCHF){XxcOIUAOCb = true;}
      else if(TGgoIrzCHF == OtJVTCgSim){CDKhSsIUsY = true;}
      if(sublzCSVgd == fcRGtiOhIB){UZdStRasXG = true;}
      else if(fcRGtiOhIB == sublzCSVgd){OSaTiKPQzr = true;}
      if(sglHOzOpLj == xdyzFIognP){TYTkPSXDNx = true;}
      else if(xdyzFIognP == sglHOzOpLj){KcDeItTKYb = true;}
      if(AtzJJaXREp == iSLMfTXmPy){NCpTsHHcLy = true;}
      else if(iSLMfTXmPy == AtzJJaXREp){LyPObBbAQM = true;}
      if(CIgGWPYJNm == kzJOwoDEoS){OdpJUkNkUd = true;}
      else if(kzJOwoDEoS == CIgGWPYJNm){NnLfeLoJmo = true;}
      if(sPripgICGU == wTYSapIgiA){qqtkOycqyo = true;}
      else if(wTYSapIgiA == sPripgICGU){BMjCqYzfYY = true;}
      if(nqGzlyuRcX == CSOqVNRFaa){xxAFOSiJZm = true;}
      if(dAQpbkAejz == KaSJPyUiDQ){KyhZroiKQe = true;}
      if(ZEbYqjBQTc == FkqUTPsrko){FmhjFWIFFt = true;}
      while(CSOqVNRFaa == nqGzlyuRcX){YyuRNPCLrh = true;}
      while(KaSJPyUiDQ == KaSJPyUiDQ){iOzmdVRXzw = true;}
      while(FkqUTPsrko == FkqUTPsrko){FJXiZyNNWC = true;}
      if(KqDPuSjRri == true){KqDPuSjRri = false;}
      if(XxcOIUAOCb == true){XxcOIUAOCb = false;}
      if(UZdStRasXG == true){UZdStRasXG = false;}
      if(TYTkPSXDNx == true){TYTkPSXDNx = false;}
      if(NCpTsHHcLy == true){NCpTsHHcLy = false;}
      if(OdpJUkNkUd == true){OdpJUkNkUd = false;}
      if(qqtkOycqyo == true){qqtkOycqyo = false;}
      if(xxAFOSiJZm == true){xxAFOSiJZm = false;}
      if(KyhZroiKQe == true){KyhZroiKQe = false;}
      if(FmhjFWIFFt == true){FmhjFWIFFt = false;}
      if(dPdWAQdjtB == true){dPdWAQdjtB = false;}
      if(CDKhSsIUsY == true){CDKhSsIUsY = false;}
      if(OSaTiKPQzr == true){OSaTiKPQzr = false;}
      if(KcDeItTKYb == true){KcDeItTKYb = false;}
      if(LyPObBbAQM == true){LyPObBbAQM = false;}
      if(NnLfeLoJmo == true){NnLfeLoJmo = false;}
      if(BMjCqYzfYY == true){BMjCqYzfYY = false;}
      if(YyuRNPCLrh == true){YyuRNPCLrh = false;}
      if(iOzmdVRXzw == true){iOzmdVRXzw = false;}
      if(FJXiZyNNWC == true){FJXiZyNNWC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVPQRDBEBW
{ 
  void BOpwdhEjYm()
  { 
      bool CXbmBhwbat = false;
      bool LneBkCDmLL = false;
      bool uhBCQneSHU = false;
      bool BUSQBlIqPR = false;
      bool rUIgWqGqAG = false;
      bool BspzfUWZWM = false;
      bool CdUFspVNzy = false;
      bool tLWtTZYTeZ = false;
      bool gnRBTHeSjf = false;
      bool PhUCOOACng = false;
      bool VrqCMpWufF = false;
      bool uCtweOLSlk = false;
      bool LCdSiLpUfE = false;
      bool ZVeyEowPod = false;
      bool kildkMnXWz = false;
      bool CgQCUSOYSB = false;
      bool zCPbfZXwrp = false;
      bool RwdIAbQzhW = false;
      bool WRxfCrFbck = false;
      bool aXwndiTKyL = false;
      string VOfDFPEXWV;
      string WtOyZSRTeI;
      string sqLuQGqFue;
      string YYeVhbVDbf;
      string ZPwLtgAzcF;
      string znsATdDjmz;
      string YybqxyOrQy;
      string xOqyhduzBj;
      string FqcpfjeeCD;
      string YkQcHbmEOw;
      string RIieHjxtRp;
      string iDiCsgVlLM;
      string SjpMZMyOqG;
      string ppkFRxHxhu;
      string mjMLUUBNiZ;
      string GBsBchRWFu;
      string lhDLAsRdkw;
      string YXEQZhWdrE;
      string KjeQznxjbi;
      string ekrlIEgBLb;
      if(VOfDFPEXWV == RIieHjxtRp){CXbmBhwbat = true;}
      else if(RIieHjxtRp == VOfDFPEXWV){VrqCMpWufF = true;}
      if(WtOyZSRTeI == iDiCsgVlLM){LneBkCDmLL = true;}
      else if(iDiCsgVlLM == WtOyZSRTeI){uCtweOLSlk = true;}
      if(sqLuQGqFue == SjpMZMyOqG){uhBCQneSHU = true;}
      else if(SjpMZMyOqG == sqLuQGqFue){LCdSiLpUfE = true;}
      if(YYeVhbVDbf == ppkFRxHxhu){BUSQBlIqPR = true;}
      else if(ppkFRxHxhu == YYeVhbVDbf){ZVeyEowPod = true;}
      if(ZPwLtgAzcF == mjMLUUBNiZ){rUIgWqGqAG = true;}
      else if(mjMLUUBNiZ == ZPwLtgAzcF){kildkMnXWz = true;}
      if(znsATdDjmz == GBsBchRWFu){BspzfUWZWM = true;}
      else if(GBsBchRWFu == znsATdDjmz){CgQCUSOYSB = true;}
      if(YybqxyOrQy == lhDLAsRdkw){CdUFspVNzy = true;}
      else if(lhDLAsRdkw == YybqxyOrQy){zCPbfZXwrp = true;}
      if(xOqyhduzBj == YXEQZhWdrE){tLWtTZYTeZ = true;}
      if(FqcpfjeeCD == KjeQznxjbi){gnRBTHeSjf = true;}
      if(YkQcHbmEOw == ekrlIEgBLb){PhUCOOACng = true;}
      while(YXEQZhWdrE == xOqyhduzBj){RwdIAbQzhW = true;}
      while(KjeQznxjbi == KjeQznxjbi){WRxfCrFbck = true;}
      while(ekrlIEgBLb == ekrlIEgBLb){aXwndiTKyL = true;}
      if(CXbmBhwbat == true){CXbmBhwbat = false;}
      if(LneBkCDmLL == true){LneBkCDmLL = false;}
      if(uhBCQneSHU == true){uhBCQneSHU = false;}
      if(BUSQBlIqPR == true){BUSQBlIqPR = false;}
      if(rUIgWqGqAG == true){rUIgWqGqAG = false;}
      if(BspzfUWZWM == true){BspzfUWZWM = false;}
      if(CdUFspVNzy == true){CdUFspVNzy = false;}
      if(tLWtTZYTeZ == true){tLWtTZYTeZ = false;}
      if(gnRBTHeSjf == true){gnRBTHeSjf = false;}
      if(PhUCOOACng == true){PhUCOOACng = false;}
      if(VrqCMpWufF == true){VrqCMpWufF = false;}
      if(uCtweOLSlk == true){uCtweOLSlk = false;}
      if(LCdSiLpUfE == true){LCdSiLpUfE = false;}
      if(ZVeyEowPod == true){ZVeyEowPod = false;}
      if(kildkMnXWz == true){kildkMnXWz = false;}
      if(CgQCUSOYSB == true){CgQCUSOYSB = false;}
      if(zCPbfZXwrp == true){zCPbfZXwrp = false;}
      if(RwdIAbQzhW == true){RwdIAbQzhW = false;}
      if(WRxfCrFbck == true){WRxfCrFbck = false;}
      if(aXwndiTKyL == true){aXwndiTKyL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BGODFTHQIN
{ 
  void cYLNsVdFhi()
  { 
      bool YczdlKjTxu = false;
      bool wUEUXCLXNX = false;
      bool kwoRJMLBJH = false;
      bool rZmbcYhZTz = false;
      bool ZRBIylnRKR = false;
      bool ODzrhbmhUY = false;
      bool yiKpDVgcrz = false;
      bool UlDOxStgSW = false;
      bool XtqqrnattB = false;
      bool kAFuAqHLFb = false;
      bool ELZKxbAkuP = false;
      bool gFOxAErTxO = false;
      bool umhqNUgING = false;
      bool KibqRMTfsQ = false;
      bool nozdTfkHuw = false;
      bool znNpgRciwc = false;
      bool uqWnExcXen = false;
      bool jLZgZFnDWh = false;
      bool iYNRGVUkJA = false;
      bool ikiPVwSKYV = false;
      string zaejEciLnj;
      string JMlEZQmhPY;
      string FYQHBBxTLR;
      string GBJUWGImsX;
      string jMFgxMsSNF;
      string eCTgGZKXhD;
      string ePzWcHCRgT;
      string IznqnsSiJo;
      string HeFGlEhcNw;
      string wjEpsUNiEp;
      string JbktxfNbrN;
      string GaNruAKskY;
      string ZYDkWXtyyT;
      string ejeTfesKIG;
      string pFkzoUWMtr;
      string KUyePjXAWZ;
      string kPdXiWwsMQ;
      string GzjdhTnDuC;
      string BhDFJKlzDu;
      string GsmiUabNQS;
      if(zaejEciLnj == JbktxfNbrN){YczdlKjTxu = true;}
      else if(JbktxfNbrN == zaejEciLnj){ELZKxbAkuP = true;}
      if(JMlEZQmhPY == GaNruAKskY){wUEUXCLXNX = true;}
      else if(GaNruAKskY == JMlEZQmhPY){gFOxAErTxO = true;}
      if(FYQHBBxTLR == ZYDkWXtyyT){kwoRJMLBJH = true;}
      else if(ZYDkWXtyyT == FYQHBBxTLR){umhqNUgING = true;}
      if(GBJUWGImsX == ejeTfesKIG){rZmbcYhZTz = true;}
      else if(ejeTfesKIG == GBJUWGImsX){KibqRMTfsQ = true;}
      if(jMFgxMsSNF == pFkzoUWMtr){ZRBIylnRKR = true;}
      else if(pFkzoUWMtr == jMFgxMsSNF){nozdTfkHuw = true;}
      if(eCTgGZKXhD == KUyePjXAWZ){ODzrhbmhUY = true;}
      else if(KUyePjXAWZ == eCTgGZKXhD){znNpgRciwc = true;}
      if(ePzWcHCRgT == kPdXiWwsMQ){yiKpDVgcrz = true;}
      else if(kPdXiWwsMQ == ePzWcHCRgT){uqWnExcXen = true;}
      if(IznqnsSiJo == GzjdhTnDuC){UlDOxStgSW = true;}
      if(HeFGlEhcNw == BhDFJKlzDu){XtqqrnattB = true;}
      if(wjEpsUNiEp == GsmiUabNQS){kAFuAqHLFb = true;}
      while(GzjdhTnDuC == IznqnsSiJo){jLZgZFnDWh = true;}
      while(BhDFJKlzDu == BhDFJKlzDu){iYNRGVUkJA = true;}
      while(GsmiUabNQS == GsmiUabNQS){ikiPVwSKYV = true;}
      if(YczdlKjTxu == true){YczdlKjTxu = false;}
      if(wUEUXCLXNX == true){wUEUXCLXNX = false;}
      if(kwoRJMLBJH == true){kwoRJMLBJH = false;}
      if(rZmbcYhZTz == true){rZmbcYhZTz = false;}
      if(ZRBIylnRKR == true){ZRBIylnRKR = false;}
      if(ODzrhbmhUY == true){ODzrhbmhUY = false;}
      if(yiKpDVgcrz == true){yiKpDVgcrz = false;}
      if(UlDOxStgSW == true){UlDOxStgSW = false;}
      if(XtqqrnattB == true){XtqqrnattB = false;}
      if(kAFuAqHLFb == true){kAFuAqHLFb = false;}
      if(ELZKxbAkuP == true){ELZKxbAkuP = false;}
      if(gFOxAErTxO == true){gFOxAErTxO = false;}
      if(umhqNUgING == true){umhqNUgING = false;}
      if(KibqRMTfsQ == true){KibqRMTfsQ = false;}
      if(nozdTfkHuw == true){nozdTfkHuw = false;}
      if(znNpgRciwc == true){znNpgRciwc = false;}
      if(uqWnExcXen == true){uqWnExcXen = false;}
      if(jLZgZFnDWh == true){jLZgZFnDWh = false;}
      if(iYNRGVUkJA == true){iYNRGVUkJA = false;}
      if(ikiPVwSKYV == true){ikiPVwSKYV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMQXNORKAG
{ 
  void GSEzPeoBqz()
  { 
      bool sxecafLlLa = false;
      bool TsoryTQJCD = false;
      bool LCAQbJWIMK = false;
      bool fdIQWdWeTl = false;
      bool dpWYLogfir = false;
      bool QsgTPpxOAQ = false;
      bool IDYBtpkXVT = false;
      bool xkpQZUfaFl = false;
      bool cqZUtmwnAg = false;
      bool gHdCcaQVeU = false;
      bool EIKOueCQst = false;
      bool JVJOnRdEHG = false;
      bool twXnmoHnmz = false;
      bool EKujgUgKZO = false;
      bool jftGWKyOOL = false;
      bool wMOYaHjVbG = false;
      bool XOctpzaYhS = false;
      bool kSerWNBRRb = false;
      bool prZbCqwWIY = false;
      bool jKhTpUCAPX = false;
      string pjqYIODtoS;
      string RMjaVMhKMQ;
      string yJSTyHknnB;
      string uMchZVeOIT;
      string SFEbHjZqDg;
      string TVyKdgRWZB;
      string cOFmXFjBBz;
      string gTCrxrEqMO;
      string gtkHgYNRDr;
      string EHnHpEAQDC;
      string AXpDzASGNl;
      string bZKLTicyFy;
      string qRyIuYeuBs;
      string rnnKNIDgHg;
      string FHERPexcmG;
      string aCKEKhZhIZ;
      string VXEUsnlAxK;
      string fupYrjNfrP;
      string bCHtRocizf;
      string iVYgLhDjXb;
      if(pjqYIODtoS == AXpDzASGNl){sxecafLlLa = true;}
      else if(AXpDzASGNl == pjqYIODtoS){EIKOueCQst = true;}
      if(RMjaVMhKMQ == bZKLTicyFy){TsoryTQJCD = true;}
      else if(bZKLTicyFy == RMjaVMhKMQ){JVJOnRdEHG = true;}
      if(yJSTyHknnB == qRyIuYeuBs){LCAQbJWIMK = true;}
      else if(qRyIuYeuBs == yJSTyHknnB){twXnmoHnmz = true;}
      if(uMchZVeOIT == rnnKNIDgHg){fdIQWdWeTl = true;}
      else if(rnnKNIDgHg == uMchZVeOIT){EKujgUgKZO = true;}
      if(SFEbHjZqDg == FHERPexcmG){dpWYLogfir = true;}
      else if(FHERPexcmG == SFEbHjZqDg){jftGWKyOOL = true;}
      if(TVyKdgRWZB == aCKEKhZhIZ){QsgTPpxOAQ = true;}
      else if(aCKEKhZhIZ == TVyKdgRWZB){wMOYaHjVbG = true;}
      if(cOFmXFjBBz == VXEUsnlAxK){IDYBtpkXVT = true;}
      else if(VXEUsnlAxK == cOFmXFjBBz){XOctpzaYhS = true;}
      if(gTCrxrEqMO == fupYrjNfrP){xkpQZUfaFl = true;}
      if(gtkHgYNRDr == bCHtRocizf){cqZUtmwnAg = true;}
      if(EHnHpEAQDC == iVYgLhDjXb){gHdCcaQVeU = true;}
      while(fupYrjNfrP == gTCrxrEqMO){kSerWNBRRb = true;}
      while(bCHtRocizf == bCHtRocizf){prZbCqwWIY = true;}
      while(iVYgLhDjXb == iVYgLhDjXb){jKhTpUCAPX = true;}
      if(sxecafLlLa == true){sxecafLlLa = false;}
      if(TsoryTQJCD == true){TsoryTQJCD = false;}
      if(LCAQbJWIMK == true){LCAQbJWIMK = false;}
      if(fdIQWdWeTl == true){fdIQWdWeTl = false;}
      if(dpWYLogfir == true){dpWYLogfir = false;}
      if(QsgTPpxOAQ == true){QsgTPpxOAQ = false;}
      if(IDYBtpkXVT == true){IDYBtpkXVT = false;}
      if(xkpQZUfaFl == true){xkpQZUfaFl = false;}
      if(cqZUtmwnAg == true){cqZUtmwnAg = false;}
      if(gHdCcaQVeU == true){gHdCcaQVeU = false;}
      if(EIKOueCQst == true){EIKOueCQst = false;}
      if(JVJOnRdEHG == true){JVJOnRdEHG = false;}
      if(twXnmoHnmz == true){twXnmoHnmz = false;}
      if(EKujgUgKZO == true){EKujgUgKZO = false;}
      if(jftGWKyOOL == true){jftGWKyOOL = false;}
      if(wMOYaHjVbG == true){wMOYaHjVbG = false;}
      if(XOctpzaYhS == true){XOctpzaYhS = false;}
      if(kSerWNBRRb == true){kSerWNBRRb = false;}
      if(prZbCqwWIY == true){prZbCqwWIY = false;}
      if(jKhTpUCAPX == true){jKhTpUCAPX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SEKWQQQDSB
{ 
  void zxZCDrOIub()
  { 
      bool yeaNdNnTTm = false;
      bool cbBcNgEUay = false;
      bool ToBXKDVGak = false;
      bool oULwYDwEWb = false;
      bool ZpsiBfeISL = false;
      bool LRikuJdCCZ = false;
      bool rhrhyHPEEK = false;
      bool kAxzYcuRVe = false;
      bool YMmPZWkZAO = false;
      bool ZsBwjrxKjt = false;
      bool PZEIZLUiLS = false;
      bool NLgXBetcIa = false;
      bool VoEojqyAPg = false;
      bool fjgbOzIdpN = false;
      bool CBOgAOMduE = false;
      bool xUCJXaUOYh = false;
      bool MTTemddEIB = false;
      bool WPmuXUaWoV = false;
      bool eUFLiKhXEn = false;
      bool esFHAihitW = false;
      string AwQZufwOoM;
      string MaeRhGczdw;
      string CYMSgDurnW;
      string LhMluWJKWZ;
      string TTWOedImid;
      string VAoGlbjxrr;
      string jDaRBdNsWK;
      string xRcEciBxmD;
      string tIJJBKsGAS;
      string mMRdoQrENA;
      string PPPXgDWkdD;
      string ZlJoxbtQQp;
      string kHrDXjzzOM;
      string pxjlmerlcx;
      string nIbxrACcgN;
      string VbmWPIWMzw;
      string EXVRMcCXCS;
      string iHmTCbeuLW;
      string hWSBpNJNWd;
      string HflgrQmKjP;
      if(AwQZufwOoM == PPPXgDWkdD){yeaNdNnTTm = true;}
      else if(PPPXgDWkdD == AwQZufwOoM){PZEIZLUiLS = true;}
      if(MaeRhGczdw == ZlJoxbtQQp){cbBcNgEUay = true;}
      else if(ZlJoxbtQQp == MaeRhGczdw){NLgXBetcIa = true;}
      if(CYMSgDurnW == kHrDXjzzOM){ToBXKDVGak = true;}
      else if(kHrDXjzzOM == CYMSgDurnW){VoEojqyAPg = true;}
      if(LhMluWJKWZ == pxjlmerlcx){oULwYDwEWb = true;}
      else if(pxjlmerlcx == LhMluWJKWZ){fjgbOzIdpN = true;}
      if(TTWOedImid == nIbxrACcgN){ZpsiBfeISL = true;}
      else if(nIbxrACcgN == TTWOedImid){CBOgAOMduE = true;}
      if(VAoGlbjxrr == VbmWPIWMzw){LRikuJdCCZ = true;}
      else if(VbmWPIWMzw == VAoGlbjxrr){xUCJXaUOYh = true;}
      if(jDaRBdNsWK == EXVRMcCXCS){rhrhyHPEEK = true;}
      else if(EXVRMcCXCS == jDaRBdNsWK){MTTemddEIB = true;}
      if(xRcEciBxmD == iHmTCbeuLW){kAxzYcuRVe = true;}
      if(tIJJBKsGAS == hWSBpNJNWd){YMmPZWkZAO = true;}
      if(mMRdoQrENA == HflgrQmKjP){ZsBwjrxKjt = true;}
      while(iHmTCbeuLW == xRcEciBxmD){WPmuXUaWoV = true;}
      while(hWSBpNJNWd == hWSBpNJNWd){eUFLiKhXEn = true;}
      while(HflgrQmKjP == HflgrQmKjP){esFHAihitW = true;}
      if(yeaNdNnTTm == true){yeaNdNnTTm = false;}
      if(cbBcNgEUay == true){cbBcNgEUay = false;}
      if(ToBXKDVGak == true){ToBXKDVGak = false;}
      if(oULwYDwEWb == true){oULwYDwEWb = false;}
      if(ZpsiBfeISL == true){ZpsiBfeISL = false;}
      if(LRikuJdCCZ == true){LRikuJdCCZ = false;}
      if(rhrhyHPEEK == true){rhrhyHPEEK = false;}
      if(kAxzYcuRVe == true){kAxzYcuRVe = false;}
      if(YMmPZWkZAO == true){YMmPZWkZAO = false;}
      if(ZsBwjrxKjt == true){ZsBwjrxKjt = false;}
      if(PZEIZLUiLS == true){PZEIZLUiLS = false;}
      if(NLgXBetcIa == true){NLgXBetcIa = false;}
      if(VoEojqyAPg == true){VoEojqyAPg = false;}
      if(fjgbOzIdpN == true){fjgbOzIdpN = false;}
      if(CBOgAOMduE == true){CBOgAOMduE = false;}
      if(xUCJXaUOYh == true){xUCJXaUOYh = false;}
      if(MTTemddEIB == true){MTTemddEIB = false;}
      if(WPmuXUaWoV == true){WPmuXUaWoV = false;}
      if(eUFLiKhXEn == true){eUFLiKhXEn = false;}
      if(esFHAihitW == true){esFHAihitW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WBFTVVPBGZ
{ 
  void OxpVZFrdzS()
  { 
      bool qxLrHkVQco = false;
      bool VkADDLphkG = false;
      bool YBbYUqhUQV = false;
      bool VyAeBHBPwa = false;
      bool yPFNhHoGDK = false;
      bool RYRLtoVmXQ = false;
      bool DAAHTXkVBu = false;
      bool KakKHIwOpM = false;
      bool CbRFDxfnkL = false;
      bool lOqfXyPxtJ = false;
      bool WSEHAqmHDk = false;
      bool sGwLObitDV = false;
      bool rwjpIwiFmJ = false;
      bool syUgpiXJEL = false;
      bool KYkzSfRfRu = false;
      bool PUtXRZhNzD = false;
      bool IgUtrtlOUe = false;
      bool EYpqKSLkXc = false;
      bool dCnqtYEwOP = false;
      bool AJKADdDpHX = false;
      string ZwJWyFYRoR;
      string JdsMjFrKzE;
      string BMkxQcVHPl;
      string KLnraNqyht;
      string prpBlPRJlG;
      string RokBDMKMGU;
      string iRBDHxoBlW;
      string NsbFOJWjKB;
      string LMUITUZmnO;
      string CerNLYpmto;
      string ZPWPrYNflt;
      string oaBEIWwril;
      string WCMXTiANso;
      string SjpVbuoEPu;
      string HsAtYbcnFo;
      string cyDHSXDzuJ;
      string XzmxbFjecM;
      string gqbmdcBSyr;
      string FMIEMUfhDE;
      string roJGWIGDST;
      if(ZwJWyFYRoR == ZPWPrYNflt){qxLrHkVQco = true;}
      else if(ZPWPrYNflt == ZwJWyFYRoR){WSEHAqmHDk = true;}
      if(JdsMjFrKzE == oaBEIWwril){VkADDLphkG = true;}
      else if(oaBEIWwril == JdsMjFrKzE){sGwLObitDV = true;}
      if(BMkxQcVHPl == WCMXTiANso){YBbYUqhUQV = true;}
      else if(WCMXTiANso == BMkxQcVHPl){rwjpIwiFmJ = true;}
      if(KLnraNqyht == SjpVbuoEPu){VyAeBHBPwa = true;}
      else if(SjpVbuoEPu == KLnraNqyht){syUgpiXJEL = true;}
      if(prpBlPRJlG == HsAtYbcnFo){yPFNhHoGDK = true;}
      else if(HsAtYbcnFo == prpBlPRJlG){KYkzSfRfRu = true;}
      if(RokBDMKMGU == cyDHSXDzuJ){RYRLtoVmXQ = true;}
      else if(cyDHSXDzuJ == RokBDMKMGU){PUtXRZhNzD = true;}
      if(iRBDHxoBlW == XzmxbFjecM){DAAHTXkVBu = true;}
      else if(XzmxbFjecM == iRBDHxoBlW){IgUtrtlOUe = true;}
      if(NsbFOJWjKB == gqbmdcBSyr){KakKHIwOpM = true;}
      if(LMUITUZmnO == FMIEMUfhDE){CbRFDxfnkL = true;}
      if(CerNLYpmto == roJGWIGDST){lOqfXyPxtJ = true;}
      while(gqbmdcBSyr == NsbFOJWjKB){EYpqKSLkXc = true;}
      while(FMIEMUfhDE == FMIEMUfhDE){dCnqtYEwOP = true;}
      while(roJGWIGDST == roJGWIGDST){AJKADdDpHX = true;}
      if(qxLrHkVQco == true){qxLrHkVQco = false;}
      if(VkADDLphkG == true){VkADDLphkG = false;}
      if(YBbYUqhUQV == true){YBbYUqhUQV = false;}
      if(VyAeBHBPwa == true){VyAeBHBPwa = false;}
      if(yPFNhHoGDK == true){yPFNhHoGDK = false;}
      if(RYRLtoVmXQ == true){RYRLtoVmXQ = false;}
      if(DAAHTXkVBu == true){DAAHTXkVBu = false;}
      if(KakKHIwOpM == true){KakKHIwOpM = false;}
      if(CbRFDxfnkL == true){CbRFDxfnkL = false;}
      if(lOqfXyPxtJ == true){lOqfXyPxtJ = false;}
      if(WSEHAqmHDk == true){WSEHAqmHDk = false;}
      if(sGwLObitDV == true){sGwLObitDV = false;}
      if(rwjpIwiFmJ == true){rwjpIwiFmJ = false;}
      if(syUgpiXJEL == true){syUgpiXJEL = false;}
      if(KYkzSfRfRu == true){KYkzSfRfRu = false;}
      if(PUtXRZhNzD == true){PUtXRZhNzD = false;}
      if(IgUtrtlOUe == true){IgUtrtlOUe = false;}
      if(EYpqKSLkXc == true){EYpqKSLkXc = false;}
      if(dCnqtYEwOP == true){dCnqtYEwOP = false;}
      if(AJKADdDpHX == true){AJKADdDpHX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YAONNMJCRG
{ 
  void oCNVTttCFW()
  { 
      bool wxHoAbNdbo = false;
      bool BPKVXerIUF = false;
      bool hHNODBKbRy = false;
      bool qTYgJrTwiE = false;
      bool TKyVdDyRZd = false;
      bool mKKzUoirky = false;
      bool RkMdyhqcLe = false;
      bool KwZQlWIrjA = false;
      bool DrCmLfIYMU = false;
      bool JbKjmhyUXw = false;
      bool MUGtSpktMx = false;
      bool fpHkuYhYSR = false;
      bool YRQpVikocD = false;
      bool YnUnmhlHUU = false;
      bool uOLOnSTZnO = false;
      bool AYBFWtEPYi = false;
      bool FuQIXqVTxM = false;
      bool laExWKFBBC = false;
      bool PLBODAlOQs = false;
      bool dVikOzxDpw = false;
      string sagPTrNDwU;
      string SWWENliwOd;
      string wjlSWJTVdA;
      string zAyCBhUYEw;
      string gArMmHiJrr;
      string xQDGDInOrJ;
      string XqYuURYUDe;
      string RKqRxwqYeP;
      string aKclDhwqzr;
      string tFftXoaxrU;
      string hOGNZlZkJH;
      string ROiciNOmrl;
      string VgULkLewsH;
      string UtgKgMDPLQ;
      string IKhqaeVCLK;
      string anFFzBsubN;
      string HcrBlWhYuW;
      string JyaadKzdkG;
      string obkiggoaKf;
      string SImyJeSfFD;
      if(sagPTrNDwU == hOGNZlZkJH){wxHoAbNdbo = true;}
      else if(hOGNZlZkJH == sagPTrNDwU){MUGtSpktMx = true;}
      if(SWWENliwOd == ROiciNOmrl){BPKVXerIUF = true;}
      else if(ROiciNOmrl == SWWENliwOd){fpHkuYhYSR = true;}
      if(wjlSWJTVdA == VgULkLewsH){hHNODBKbRy = true;}
      else if(VgULkLewsH == wjlSWJTVdA){YRQpVikocD = true;}
      if(zAyCBhUYEw == UtgKgMDPLQ){qTYgJrTwiE = true;}
      else if(UtgKgMDPLQ == zAyCBhUYEw){YnUnmhlHUU = true;}
      if(gArMmHiJrr == IKhqaeVCLK){TKyVdDyRZd = true;}
      else if(IKhqaeVCLK == gArMmHiJrr){uOLOnSTZnO = true;}
      if(xQDGDInOrJ == anFFzBsubN){mKKzUoirky = true;}
      else if(anFFzBsubN == xQDGDInOrJ){AYBFWtEPYi = true;}
      if(XqYuURYUDe == HcrBlWhYuW){RkMdyhqcLe = true;}
      else if(HcrBlWhYuW == XqYuURYUDe){FuQIXqVTxM = true;}
      if(RKqRxwqYeP == JyaadKzdkG){KwZQlWIrjA = true;}
      if(aKclDhwqzr == obkiggoaKf){DrCmLfIYMU = true;}
      if(tFftXoaxrU == SImyJeSfFD){JbKjmhyUXw = true;}
      while(JyaadKzdkG == RKqRxwqYeP){laExWKFBBC = true;}
      while(obkiggoaKf == obkiggoaKf){PLBODAlOQs = true;}
      while(SImyJeSfFD == SImyJeSfFD){dVikOzxDpw = true;}
      if(wxHoAbNdbo == true){wxHoAbNdbo = false;}
      if(BPKVXerIUF == true){BPKVXerIUF = false;}
      if(hHNODBKbRy == true){hHNODBKbRy = false;}
      if(qTYgJrTwiE == true){qTYgJrTwiE = false;}
      if(TKyVdDyRZd == true){TKyVdDyRZd = false;}
      if(mKKzUoirky == true){mKKzUoirky = false;}
      if(RkMdyhqcLe == true){RkMdyhqcLe = false;}
      if(KwZQlWIrjA == true){KwZQlWIrjA = false;}
      if(DrCmLfIYMU == true){DrCmLfIYMU = false;}
      if(JbKjmhyUXw == true){JbKjmhyUXw = false;}
      if(MUGtSpktMx == true){MUGtSpktMx = false;}
      if(fpHkuYhYSR == true){fpHkuYhYSR = false;}
      if(YRQpVikocD == true){YRQpVikocD = false;}
      if(YnUnmhlHUU == true){YnUnmhlHUU = false;}
      if(uOLOnSTZnO == true){uOLOnSTZnO = false;}
      if(AYBFWtEPYi == true){AYBFWtEPYi = false;}
      if(FuQIXqVTxM == true){FuQIXqVTxM = false;}
      if(laExWKFBBC == true){laExWKFBBC = false;}
      if(PLBODAlOQs == true){PLBODAlOQs = false;}
      if(dVikOzxDpw == true){dVikOzxDpw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXJZCZWKBW
{ 
  void kwEUGuYesT()
  { 
      bool NacNNNmKjG = false;
      bool muYSrErcQz = false;
      bool kipxqpmHIn = false;
      bool NCXJKszKIB = false;
      bool yiEfXHHkUQ = false;
      bool LOXfkdkfVW = false;
      bool aeBurkWPIy = false;
      bool EgUPABdJZj = false;
      bool iCmqbydrXf = false;
      bool HTnkZThInl = false;
      bool jqbVMdtHei = false;
      bool AbGknXrJTt = false;
      bool Heqbqjsiog = false;
      bool TUVmAqZQey = false;
      bool DVMnffNCwC = false;
      bool aXoteEzAec = false;
      bool kLRyPeFSkx = false;
      bool xaeVpkSCwK = false;
      bool VplmFwebIw = false;
      bool rZlBMrENYA = false;
      string TOAnYYRHcg;
      string sPrWBWTINn;
      string FDWOHGxhBx;
      string CygZdRRSWR;
      string bIASFYkckp;
      string xjBLcPrkgR;
      string ajFfeuhRsi;
      string FAlwLxDEJh;
      string VTxKzRxUxN;
      string ZfkEprCUnK;
      string qTjBkwxFAf;
      string MnbzwGmtfM;
      string yMUeJYPgFT;
      string thPzpBjuZC;
      string UrUQAkElIi;
      string FInbMezEqM;
      string gQzfkeXcIt;
      string VqUdqGqDeX;
      string UcYVOltnlL;
      string CfDMUDroeV;
      if(TOAnYYRHcg == qTjBkwxFAf){NacNNNmKjG = true;}
      else if(qTjBkwxFAf == TOAnYYRHcg){jqbVMdtHei = true;}
      if(sPrWBWTINn == MnbzwGmtfM){muYSrErcQz = true;}
      else if(MnbzwGmtfM == sPrWBWTINn){AbGknXrJTt = true;}
      if(FDWOHGxhBx == yMUeJYPgFT){kipxqpmHIn = true;}
      else if(yMUeJYPgFT == FDWOHGxhBx){Heqbqjsiog = true;}
      if(CygZdRRSWR == thPzpBjuZC){NCXJKszKIB = true;}
      else if(thPzpBjuZC == CygZdRRSWR){TUVmAqZQey = true;}
      if(bIASFYkckp == UrUQAkElIi){yiEfXHHkUQ = true;}
      else if(UrUQAkElIi == bIASFYkckp){DVMnffNCwC = true;}
      if(xjBLcPrkgR == FInbMezEqM){LOXfkdkfVW = true;}
      else if(FInbMezEqM == xjBLcPrkgR){aXoteEzAec = true;}
      if(ajFfeuhRsi == gQzfkeXcIt){aeBurkWPIy = true;}
      else if(gQzfkeXcIt == ajFfeuhRsi){kLRyPeFSkx = true;}
      if(FAlwLxDEJh == VqUdqGqDeX){EgUPABdJZj = true;}
      if(VTxKzRxUxN == UcYVOltnlL){iCmqbydrXf = true;}
      if(ZfkEprCUnK == CfDMUDroeV){HTnkZThInl = true;}
      while(VqUdqGqDeX == FAlwLxDEJh){xaeVpkSCwK = true;}
      while(UcYVOltnlL == UcYVOltnlL){VplmFwebIw = true;}
      while(CfDMUDroeV == CfDMUDroeV){rZlBMrENYA = true;}
      if(NacNNNmKjG == true){NacNNNmKjG = false;}
      if(muYSrErcQz == true){muYSrErcQz = false;}
      if(kipxqpmHIn == true){kipxqpmHIn = false;}
      if(NCXJKszKIB == true){NCXJKszKIB = false;}
      if(yiEfXHHkUQ == true){yiEfXHHkUQ = false;}
      if(LOXfkdkfVW == true){LOXfkdkfVW = false;}
      if(aeBurkWPIy == true){aeBurkWPIy = false;}
      if(EgUPABdJZj == true){EgUPABdJZj = false;}
      if(iCmqbydrXf == true){iCmqbydrXf = false;}
      if(HTnkZThInl == true){HTnkZThInl = false;}
      if(jqbVMdtHei == true){jqbVMdtHei = false;}
      if(AbGknXrJTt == true){AbGknXrJTt = false;}
      if(Heqbqjsiog == true){Heqbqjsiog = false;}
      if(TUVmAqZQey == true){TUVmAqZQey = false;}
      if(DVMnffNCwC == true){DVMnffNCwC = false;}
      if(aXoteEzAec == true){aXoteEzAec = false;}
      if(kLRyPeFSkx == true){kLRyPeFSkx = false;}
      if(xaeVpkSCwK == true){xaeVpkSCwK = false;}
      if(VplmFwebIw == true){VplmFwebIw = false;}
      if(rZlBMrENYA == true){rZlBMrENYA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZTVPFKCAC
{ 
  void GjFixXgJUn()
  { 
      bool aEjLgNtWXK = false;
      bool GoAyLyOfJJ = false;
      bool eDMWYwtnJU = false;
      bool toGKjxhqYg = false;
      bool speuGlPMmf = false;
      bool ZjlDHXqNmj = false;
      bool SFMCPRipNO = false;
      bool PWGcPnXQPl = false;
      bool ghBcuJCDDL = false;
      bool FUEoNncbfo = false;
      bool DZyXQDdJnS = false;
      bool AaxADjDjHF = false;
      bool OfmCJuRROb = false;
      bool LukZhHjdLr = false;
      bool fsOjLdWEld = false;
      bool jrUZaXmwOV = false;
      bool kMtLHEoWRu = false;
      bool zZXPYUQCpe = false;
      bool XNekqSZKzK = false;
      bool UnPpGTyDcG = false;
      string XJAujlsQrp;
      string CpIlPIrbGz;
      string etkwRWYtVI;
      string kznAVxTpMi;
      string sbcClgwnUY;
      string HxJWVdYDcM;
      string MzujEDCIQR;
      string nCPWGCQhKk;
      string ZkYwAnoQdq;
      string XPNzVsgsxi;
      string dnWDkFhmQT;
      string NpsqmbaziP;
      string NldZsXnPAM;
      string VWjaGlNULu;
      string GCAKcgWVMt;
      string ShKgVrJxKM;
      string QRlDxqGRkB;
      string NFmnJKlTwL;
      string BSDGtnMCFN;
      string bQKydnQwMl;
      if(XJAujlsQrp == dnWDkFhmQT){aEjLgNtWXK = true;}
      else if(dnWDkFhmQT == XJAujlsQrp){DZyXQDdJnS = true;}
      if(CpIlPIrbGz == NpsqmbaziP){GoAyLyOfJJ = true;}
      else if(NpsqmbaziP == CpIlPIrbGz){AaxADjDjHF = true;}
      if(etkwRWYtVI == NldZsXnPAM){eDMWYwtnJU = true;}
      else if(NldZsXnPAM == etkwRWYtVI){OfmCJuRROb = true;}
      if(kznAVxTpMi == VWjaGlNULu){toGKjxhqYg = true;}
      else if(VWjaGlNULu == kznAVxTpMi){LukZhHjdLr = true;}
      if(sbcClgwnUY == GCAKcgWVMt){speuGlPMmf = true;}
      else if(GCAKcgWVMt == sbcClgwnUY){fsOjLdWEld = true;}
      if(HxJWVdYDcM == ShKgVrJxKM){ZjlDHXqNmj = true;}
      else if(ShKgVrJxKM == HxJWVdYDcM){jrUZaXmwOV = true;}
      if(MzujEDCIQR == QRlDxqGRkB){SFMCPRipNO = true;}
      else if(QRlDxqGRkB == MzujEDCIQR){kMtLHEoWRu = true;}
      if(nCPWGCQhKk == NFmnJKlTwL){PWGcPnXQPl = true;}
      if(ZkYwAnoQdq == BSDGtnMCFN){ghBcuJCDDL = true;}
      if(XPNzVsgsxi == bQKydnQwMl){FUEoNncbfo = true;}
      while(NFmnJKlTwL == nCPWGCQhKk){zZXPYUQCpe = true;}
      while(BSDGtnMCFN == BSDGtnMCFN){XNekqSZKzK = true;}
      while(bQKydnQwMl == bQKydnQwMl){UnPpGTyDcG = true;}
      if(aEjLgNtWXK == true){aEjLgNtWXK = false;}
      if(GoAyLyOfJJ == true){GoAyLyOfJJ = false;}
      if(eDMWYwtnJU == true){eDMWYwtnJU = false;}
      if(toGKjxhqYg == true){toGKjxhqYg = false;}
      if(speuGlPMmf == true){speuGlPMmf = false;}
      if(ZjlDHXqNmj == true){ZjlDHXqNmj = false;}
      if(SFMCPRipNO == true){SFMCPRipNO = false;}
      if(PWGcPnXQPl == true){PWGcPnXQPl = false;}
      if(ghBcuJCDDL == true){ghBcuJCDDL = false;}
      if(FUEoNncbfo == true){FUEoNncbfo = false;}
      if(DZyXQDdJnS == true){DZyXQDdJnS = false;}
      if(AaxADjDjHF == true){AaxADjDjHF = false;}
      if(OfmCJuRROb == true){OfmCJuRROb = false;}
      if(LukZhHjdLr == true){LukZhHjdLr = false;}
      if(fsOjLdWEld == true){fsOjLdWEld = false;}
      if(jrUZaXmwOV == true){jrUZaXmwOV = false;}
      if(kMtLHEoWRu == true){kMtLHEoWRu = false;}
      if(zZXPYUQCpe == true){zZXPYUQCpe = false;}
      if(XNekqSZKzK == true){XNekqSZKzK = false;}
      if(UnPpGTyDcG == true){UnPpGTyDcG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFGDTZBOHC
{ 
  void ApDgypEIVw()
  { 
      bool awjsKmMKzG = false;
      bool XXEXGyhUSe = false;
      bool xKZjooYwZB = false;
      bool kfIFBNxTUB = false;
      bool VFnriHrEbF = false;
      bool JfoYcPWzDU = false;
      bool NPjyUrOzWr = false;
      bool AOARIrWgBh = false;
      bool xUUTrEpjbk = false;
      bool qxPzmFUpWp = false;
      bool rrhiFtfXQk = false;
      bool soyVXsuPFP = false;
      bool BeWkBCzBdC = false;
      bool WfKKoElkOx = false;
      bool YSSqrBzsat = false;
      bool KEkGnMVxgC = false;
      bool udsOOMenfS = false;
      bool GKBHqiMfsA = false;
      bool DFZjrRuDVc = false;
      bool ioDMBtYEce = false;
      string cJCDHcKXAr;
      string RulJHheuVi;
      string qBURHmTxAL;
      string DBnxhwUhTa;
      string isrNuXFfPI;
      string lwXlobokuT;
      string INWnnQGnaL;
      string NwatzyIHVj;
      string hmhrZHdCIG;
      string HimARVWDZe;
      string QQFEtoVclp;
      string SgOKlUfdOf;
      string mEfTDdJacd;
      string bFhpTQhdyj;
      string lAPSnaUbNx;
      string orosrMkkAP;
      string ftAHNNzXqU;
      string lCedslnMfc;
      string JhMeniPnyH;
      string fxchEqAIEa;
      if(cJCDHcKXAr == QQFEtoVclp){awjsKmMKzG = true;}
      else if(QQFEtoVclp == cJCDHcKXAr){rrhiFtfXQk = true;}
      if(RulJHheuVi == SgOKlUfdOf){XXEXGyhUSe = true;}
      else if(SgOKlUfdOf == RulJHheuVi){soyVXsuPFP = true;}
      if(qBURHmTxAL == mEfTDdJacd){xKZjooYwZB = true;}
      else if(mEfTDdJacd == qBURHmTxAL){BeWkBCzBdC = true;}
      if(DBnxhwUhTa == bFhpTQhdyj){kfIFBNxTUB = true;}
      else if(bFhpTQhdyj == DBnxhwUhTa){WfKKoElkOx = true;}
      if(isrNuXFfPI == lAPSnaUbNx){VFnriHrEbF = true;}
      else if(lAPSnaUbNx == isrNuXFfPI){YSSqrBzsat = true;}
      if(lwXlobokuT == orosrMkkAP){JfoYcPWzDU = true;}
      else if(orosrMkkAP == lwXlobokuT){KEkGnMVxgC = true;}
      if(INWnnQGnaL == ftAHNNzXqU){NPjyUrOzWr = true;}
      else if(ftAHNNzXqU == INWnnQGnaL){udsOOMenfS = true;}
      if(NwatzyIHVj == lCedslnMfc){AOARIrWgBh = true;}
      if(hmhrZHdCIG == JhMeniPnyH){xUUTrEpjbk = true;}
      if(HimARVWDZe == fxchEqAIEa){qxPzmFUpWp = true;}
      while(lCedslnMfc == NwatzyIHVj){GKBHqiMfsA = true;}
      while(JhMeniPnyH == JhMeniPnyH){DFZjrRuDVc = true;}
      while(fxchEqAIEa == fxchEqAIEa){ioDMBtYEce = true;}
      if(awjsKmMKzG == true){awjsKmMKzG = false;}
      if(XXEXGyhUSe == true){XXEXGyhUSe = false;}
      if(xKZjooYwZB == true){xKZjooYwZB = false;}
      if(kfIFBNxTUB == true){kfIFBNxTUB = false;}
      if(VFnriHrEbF == true){VFnriHrEbF = false;}
      if(JfoYcPWzDU == true){JfoYcPWzDU = false;}
      if(NPjyUrOzWr == true){NPjyUrOzWr = false;}
      if(AOARIrWgBh == true){AOARIrWgBh = false;}
      if(xUUTrEpjbk == true){xUUTrEpjbk = false;}
      if(qxPzmFUpWp == true){qxPzmFUpWp = false;}
      if(rrhiFtfXQk == true){rrhiFtfXQk = false;}
      if(soyVXsuPFP == true){soyVXsuPFP = false;}
      if(BeWkBCzBdC == true){BeWkBCzBdC = false;}
      if(WfKKoElkOx == true){WfKKoElkOx = false;}
      if(YSSqrBzsat == true){YSSqrBzsat = false;}
      if(KEkGnMVxgC == true){KEkGnMVxgC = false;}
      if(udsOOMenfS == true){udsOOMenfS = false;}
      if(GKBHqiMfsA == true){GKBHqiMfsA = false;}
      if(DFZjrRuDVc == true){DFZjrRuDVc = false;}
      if(ioDMBtYEce == true){ioDMBtYEce = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEBCMMYHVF
{ 
  void yJeFABYKKN()
  { 
      bool bzgZGeaYyq = false;
      bool yUyVzVdJXV = false;
      bool NfLnsfGxBY = false;
      bool oacAjHpYuL = false;
      bool feTOXaaENY = false;
      bool CaJRowmrfa = false;
      bool YdXYBWrxkq = false;
      bool eFOMoiMwQS = false;
      bool FBibWORKLn = false;
      bool TxrUlCGtNA = false;
      bool hcTVtwMwcG = false;
      bool iqbMVXtuCl = false;
      bool EhlxWhMsZm = false;
      bool bSiPkbgMhZ = false;
      bool CUgEFcVezO = false;
      bool HKqauzqWzM = false;
      bool iSVpdQHLbs = false;
      bool pgNcjjBgqs = false;
      bool LhsLeQaHTk = false;
      bool jKNVpiypZo = false;
      string naFwQxzcfJ;
      string JxqTfiDOkY;
      string yRUDSqNeCz;
      string tKfTizHIMb;
      string VolgodpLBF;
      string CskTfWGCcY;
      string iTZfPyRWkf;
      string btCIDIemNo;
      string BCdwwAZMnL;
      string sEemsBOFRp;
      string MTaUcIqbPW;
      string qSnmXgocjO;
      string YFhYmWOOPB;
      string sZUWchaISn;
      string JxwRUZPqPM;
      string LkVDRHlChG;
      string scMOcRyQKp;
      string FgKwFaIQDM;
      string GXyCpHDRFV;
      string wYaMufkhnD;
      if(naFwQxzcfJ == MTaUcIqbPW){bzgZGeaYyq = true;}
      else if(MTaUcIqbPW == naFwQxzcfJ){hcTVtwMwcG = true;}
      if(JxqTfiDOkY == qSnmXgocjO){yUyVzVdJXV = true;}
      else if(qSnmXgocjO == JxqTfiDOkY){iqbMVXtuCl = true;}
      if(yRUDSqNeCz == YFhYmWOOPB){NfLnsfGxBY = true;}
      else if(YFhYmWOOPB == yRUDSqNeCz){EhlxWhMsZm = true;}
      if(tKfTizHIMb == sZUWchaISn){oacAjHpYuL = true;}
      else if(sZUWchaISn == tKfTizHIMb){bSiPkbgMhZ = true;}
      if(VolgodpLBF == JxwRUZPqPM){feTOXaaENY = true;}
      else if(JxwRUZPqPM == VolgodpLBF){CUgEFcVezO = true;}
      if(CskTfWGCcY == LkVDRHlChG){CaJRowmrfa = true;}
      else if(LkVDRHlChG == CskTfWGCcY){HKqauzqWzM = true;}
      if(iTZfPyRWkf == scMOcRyQKp){YdXYBWrxkq = true;}
      else if(scMOcRyQKp == iTZfPyRWkf){iSVpdQHLbs = true;}
      if(btCIDIemNo == FgKwFaIQDM){eFOMoiMwQS = true;}
      if(BCdwwAZMnL == GXyCpHDRFV){FBibWORKLn = true;}
      if(sEemsBOFRp == wYaMufkhnD){TxrUlCGtNA = true;}
      while(FgKwFaIQDM == btCIDIemNo){pgNcjjBgqs = true;}
      while(GXyCpHDRFV == GXyCpHDRFV){LhsLeQaHTk = true;}
      while(wYaMufkhnD == wYaMufkhnD){jKNVpiypZo = true;}
      if(bzgZGeaYyq == true){bzgZGeaYyq = false;}
      if(yUyVzVdJXV == true){yUyVzVdJXV = false;}
      if(NfLnsfGxBY == true){NfLnsfGxBY = false;}
      if(oacAjHpYuL == true){oacAjHpYuL = false;}
      if(feTOXaaENY == true){feTOXaaENY = false;}
      if(CaJRowmrfa == true){CaJRowmrfa = false;}
      if(YdXYBWrxkq == true){YdXYBWrxkq = false;}
      if(eFOMoiMwQS == true){eFOMoiMwQS = false;}
      if(FBibWORKLn == true){FBibWORKLn = false;}
      if(TxrUlCGtNA == true){TxrUlCGtNA = false;}
      if(hcTVtwMwcG == true){hcTVtwMwcG = false;}
      if(iqbMVXtuCl == true){iqbMVXtuCl = false;}
      if(EhlxWhMsZm == true){EhlxWhMsZm = false;}
      if(bSiPkbgMhZ == true){bSiPkbgMhZ = false;}
      if(CUgEFcVezO == true){CUgEFcVezO = false;}
      if(HKqauzqWzM == true){HKqauzqWzM = false;}
      if(iSVpdQHLbs == true){iSVpdQHLbs = false;}
      if(pgNcjjBgqs == true){pgNcjjBgqs = false;}
      if(LhsLeQaHTk == true){LhsLeQaHTk = false;}
      if(jKNVpiypZo == true){jKNVpiypZo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZPUHGIAUTI
{ 
  void FYlfjPPtLT()
  { 
      bool ufByBmjJXq = false;
      bool AAqkEKVVTn = false;
      bool RqZkbiZdLM = false;
      bool lMiGqRtLIe = false;
      bool mKwUcPTNHE = false;
      bool fkFCpEGQVR = false;
      bool MFxKEnRksl = false;
      bool QKNnBGuFHM = false;
      bool OMWHgBGfPm = false;
      bool LdppSgNkPo = false;
      bool yiTUnVXRBi = false;
      bool IAIIDzipdD = false;
      bool gkUGZlTWVT = false;
      bool sJoSOfsCTL = false;
      bool doegdKVhlT = false;
      bool yWHMIMNNtB = false;
      bool BAwgpyLosX = false;
      bool FfWSZqGnbO = false;
      bool QljBVVCbJC = false;
      bool ReHRJcsxqf = false;
      string dAVmXjJAAo;
      string XtoJBHmkPY;
      string qBpcGqpZPQ;
      string aVXyOhrcHB;
      string oPQzRGuJkh;
      string bKyylbJrfg;
      string sikjOCWpuS;
      string PJcNibkqLA;
      string wgngnQWZMl;
      string YzwaIFdfkP;
      string jEOSSShkOJ;
      string qRgfjMtEwy;
      string exdItPMBFc;
      string xEGuQqRVNU;
      string ilKDtGRQqw;
      string LZjmjmaFXC;
      string GfekLlLkOs;
      string tYpaOslZOm;
      string yuJJRXUTLd;
      string QLyLOCGYqH;
      if(dAVmXjJAAo == jEOSSShkOJ){ufByBmjJXq = true;}
      else if(jEOSSShkOJ == dAVmXjJAAo){yiTUnVXRBi = true;}
      if(XtoJBHmkPY == qRgfjMtEwy){AAqkEKVVTn = true;}
      else if(qRgfjMtEwy == XtoJBHmkPY){IAIIDzipdD = true;}
      if(qBpcGqpZPQ == exdItPMBFc){RqZkbiZdLM = true;}
      else if(exdItPMBFc == qBpcGqpZPQ){gkUGZlTWVT = true;}
      if(aVXyOhrcHB == xEGuQqRVNU){lMiGqRtLIe = true;}
      else if(xEGuQqRVNU == aVXyOhrcHB){sJoSOfsCTL = true;}
      if(oPQzRGuJkh == ilKDtGRQqw){mKwUcPTNHE = true;}
      else if(ilKDtGRQqw == oPQzRGuJkh){doegdKVhlT = true;}
      if(bKyylbJrfg == LZjmjmaFXC){fkFCpEGQVR = true;}
      else if(LZjmjmaFXC == bKyylbJrfg){yWHMIMNNtB = true;}
      if(sikjOCWpuS == GfekLlLkOs){MFxKEnRksl = true;}
      else if(GfekLlLkOs == sikjOCWpuS){BAwgpyLosX = true;}
      if(PJcNibkqLA == tYpaOslZOm){QKNnBGuFHM = true;}
      if(wgngnQWZMl == yuJJRXUTLd){OMWHgBGfPm = true;}
      if(YzwaIFdfkP == QLyLOCGYqH){LdppSgNkPo = true;}
      while(tYpaOslZOm == PJcNibkqLA){FfWSZqGnbO = true;}
      while(yuJJRXUTLd == yuJJRXUTLd){QljBVVCbJC = true;}
      while(QLyLOCGYqH == QLyLOCGYqH){ReHRJcsxqf = true;}
      if(ufByBmjJXq == true){ufByBmjJXq = false;}
      if(AAqkEKVVTn == true){AAqkEKVVTn = false;}
      if(RqZkbiZdLM == true){RqZkbiZdLM = false;}
      if(lMiGqRtLIe == true){lMiGqRtLIe = false;}
      if(mKwUcPTNHE == true){mKwUcPTNHE = false;}
      if(fkFCpEGQVR == true){fkFCpEGQVR = false;}
      if(MFxKEnRksl == true){MFxKEnRksl = false;}
      if(QKNnBGuFHM == true){QKNnBGuFHM = false;}
      if(OMWHgBGfPm == true){OMWHgBGfPm = false;}
      if(LdppSgNkPo == true){LdppSgNkPo = false;}
      if(yiTUnVXRBi == true){yiTUnVXRBi = false;}
      if(IAIIDzipdD == true){IAIIDzipdD = false;}
      if(gkUGZlTWVT == true){gkUGZlTWVT = false;}
      if(sJoSOfsCTL == true){sJoSOfsCTL = false;}
      if(doegdKVhlT == true){doegdKVhlT = false;}
      if(yWHMIMNNtB == true){yWHMIMNNtB = false;}
      if(BAwgpyLosX == true){BAwgpyLosX = false;}
      if(FfWSZqGnbO == true){FfWSZqGnbO = false;}
      if(QljBVVCbJC == true){QljBVVCbJC = false;}
      if(ReHRJcsxqf == true){ReHRJcsxqf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYFPCGIVBZ
{ 
  void KRRxjrSjal()
  { 
      bool otAqHFNhIZ = false;
      bool qqGlPJCGhO = false;
      bool IhsSxDBxkR = false;
      bool lCTaYhIPSk = false;
      bool OXcDaJqJHF = false;
      bool AiqIlHAhtE = false;
      bool DQxpmnXfNh = false;
      bool BmnxAkEpqm = false;
      bool LrpeQDLKnR = false;
      bool hZUOhxZlPm = false;
      bool kLwYDNusIA = false;
      bool DJqGrLZRZj = false;
      bool cNqwAaRYPC = false;
      bool KRaECAuQaD = false;
      bool ISBnNXiOVV = false;
      bool WHMfJWUAYc = false;
      bool uVdGokimDr = false;
      bool QJpVbKMChb = false;
      bool rDCseDEute = false;
      bool euqyHlnuyb = false;
      string JrMcplglum;
      string WcOLSSWxPQ;
      string fBibWidMAQ;
      string ofisUCEQes;
      string UDwIsoKxpz;
      string TXoPcIJkGH;
      string HTkeyqtVqQ;
      string NFSVubFZhh;
      string YfWBwQpSPM;
      string rTKWkARQKC;
      string uoGYlNESTB;
      string CiCXhbwjhg;
      string AaFeXsuuku;
      string KnPemjZyPh;
      string LXyOJJQloJ;
      string EhhcCTibBr;
      string SIhYpOTWky;
      string ByUAUbbqUO;
      string bIGapbFlcS;
      string AywWPDpYXt;
      if(JrMcplglum == uoGYlNESTB){otAqHFNhIZ = true;}
      else if(uoGYlNESTB == JrMcplglum){kLwYDNusIA = true;}
      if(WcOLSSWxPQ == CiCXhbwjhg){qqGlPJCGhO = true;}
      else if(CiCXhbwjhg == WcOLSSWxPQ){DJqGrLZRZj = true;}
      if(fBibWidMAQ == AaFeXsuuku){IhsSxDBxkR = true;}
      else if(AaFeXsuuku == fBibWidMAQ){cNqwAaRYPC = true;}
      if(ofisUCEQes == KnPemjZyPh){lCTaYhIPSk = true;}
      else if(KnPemjZyPh == ofisUCEQes){KRaECAuQaD = true;}
      if(UDwIsoKxpz == LXyOJJQloJ){OXcDaJqJHF = true;}
      else if(LXyOJJQloJ == UDwIsoKxpz){ISBnNXiOVV = true;}
      if(TXoPcIJkGH == EhhcCTibBr){AiqIlHAhtE = true;}
      else if(EhhcCTibBr == TXoPcIJkGH){WHMfJWUAYc = true;}
      if(HTkeyqtVqQ == SIhYpOTWky){DQxpmnXfNh = true;}
      else if(SIhYpOTWky == HTkeyqtVqQ){uVdGokimDr = true;}
      if(NFSVubFZhh == ByUAUbbqUO){BmnxAkEpqm = true;}
      if(YfWBwQpSPM == bIGapbFlcS){LrpeQDLKnR = true;}
      if(rTKWkARQKC == AywWPDpYXt){hZUOhxZlPm = true;}
      while(ByUAUbbqUO == NFSVubFZhh){QJpVbKMChb = true;}
      while(bIGapbFlcS == bIGapbFlcS){rDCseDEute = true;}
      while(AywWPDpYXt == AywWPDpYXt){euqyHlnuyb = true;}
      if(otAqHFNhIZ == true){otAqHFNhIZ = false;}
      if(qqGlPJCGhO == true){qqGlPJCGhO = false;}
      if(IhsSxDBxkR == true){IhsSxDBxkR = false;}
      if(lCTaYhIPSk == true){lCTaYhIPSk = false;}
      if(OXcDaJqJHF == true){OXcDaJqJHF = false;}
      if(AiqIlHAhtE == true){AiqIlHAhtE = false;}
      if(DQxpmnXfNh == true){DQxpmnXfNh = false;}
      if(BmnxAkEpqm == true){BmnxAkEpqm = false;}
      if(LrpeQDLKnR == true){LrpeQDLKnR = false;}
      if(hZUOhxZlPm == true){hZUOhxZlPm = false;}
      if(kLwYDNusIA == true){kLwYDNusIA = false;}
      if(DJqGrLZRZj == true){DJqGrLZRZj = false;}
      if(cNqwAaRYPC == true){cNqwAaRYPC = false;}
      if(KRaECAuQaD == true){KRaECAuQaD = false;}
      if(ISBnNXiOVV == true){ISBnNXiOVV = false;}
      if(WHMfJWUAYc == true){WHMfJWUAYc = false;}
      if(uVdGokimDr == true){uVdGokimDr = false;}
      if(QJpVbKMChb == true){QJpVbKMChb = false;}
      if(rDCseDEute == true){rDCseDEute = false;}
      if(euqyHlnuyb == true){euqyHlnuyb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKPVAGXOUY
{ 
  void kxgqdQFmcY()
  { 
      bool NeaZNqiCjT = false;
      bool dfyKfFZqGm = false;
      bool gpodXZXCrt = false;
      bool ttqkJCJBrV = false;
      bool LcYRqSGiKt = false;
      bool iJPEuXpxCm = false;
      bool SfKoZjnNBd = false;
      bool wXzjaEQXlF = false;
      bool ToryLjemok = false;
      bool MLzECeSjrH = false;
      bool dshgxLKedp = false;
      bool GRKxTdnLdo = false;
      bool EBXPRjXthu = false;
      bool lgeeaZHLBA = false;
      bool ZAJzetBCjX = false;
      bool qGGDCcVROM = false;
      bool mPwhEZmfVs = false;
      bool WcKcOErXkX = false;
      bool iVJJEfabby = false;
      bool EownMKDatE = false;
      string sueeUsAnNO;
      string GaesEnSFwM;
      string kDzwAzULgo;
      string PWqoQHQTBL;
      string pjBApjNqQZ;
      string zeeMIowheU;
      string YnGXyijocw;
      string WzEkWBCyGP;
      string lduHpkqefa;
      string LhofmBccBG;
      string AXNTCAatoG;
      string lxbOitszhN;
      string rFICknJYxV;
      string YZxAPNPbFp;
      string KxoZoNGZwr;
      string IctmOtOLhN;
      string pBwThMzazV;
      string eQtrDtPiNX;
      string hjbFMueJlV;
      string yEsqzIAVqb;
      if(sueeUsAnNO == AXNTCAatoG){NeaZNqiCjT = true;}
      else if(AXNTCAatoG == sueeUsAnNO){dshgxLKedp = true;}
      if(GaesEnSFwM == lxbOitszhN){dfyKfFZqGm = true;}
      else if(lxbOitszhN == GaesEnSFwM){GRKxTdnLdo = true;}
      if(kDzwAzULgo == rFICknJYxV){gpodXZXCrt = true;}
      else if(rFICknJYxV == kDzwAzULgo){EBXPRjXthu = true;}
      if(PWqoQHQTBL == YZxAPNPbFp){ttqkJCJBrV = true;}
      else if(YZxAPNPbFp == PWqoQHQTBL){lgeeaZHLBA = true;}
      if(pjBApjNqQZ == KxoZoNGZwr){LcYRqSGiKt = true;}
      else if(KxoZoNGZwr == pjBApjNqQZ){ZAJzetBCjX = true;}
      if(zeeMIowheU == IctmOtOLhN){iJPEuXpxCm = true;}
      else if(IctmOtOLhN == zeeMIowheU){qGGDCcVROM = true;}
      if(YnGXyijocw == pBwThMzazV){SfKoZjnNBd = true;}
      else if(pBwThMzazV == YnGXyijocw){mPwhEZmfVs = true;}
      if(WzEkWBCyGP == eQtrDtPiNX){wXzjaEQXlF = true;}
      if(lduHpkqefa == hjbFMueJlV){ToryLjemok = true;}
      if(LhofmBccBG == yEsqzIAVqb){MLzECeSjrH = true;}
      while(eQtrDtPiNX == WzEkWBCyGP){WcKcOErXkX = true;}
      while(hjbFMueJlV == hjbFMueJlV){iVJJEfabby = true;}
      while(yEsqzIAVqb == yEsqzIAVqb){EownMKDatE = true;}
      if(NeaZNqiCjT == true){NeaZNqiCjT = false;}
      if(dfyKfFZqGm == true){dfyKfFZqGm = false;}
      if(gpodXZXCrt == true){gpodXZXCrt = false;}
      if(ttqkJCJBrV == true){ttqkJCJBrV = false;}
      if(LcYRqSGiKt == true){LcYRqSGiKt = false;}
      if(iJPEuXpxCm == true){iJPEuXpxCm = false;}
      if(SfKoZjnNBd == true){SfKoZjnNBd = false;}
      if(wXzjaEQXlF == true){wXzjaEQXlF = false;}
      if(ToryLjemok == true){ToryLjemok = false;}
      if(MLzECeSjrH == true){MLzECeSjrH = false;}
      if(dshgxLKedp == true){dshgxLKedp = false;}
      if(GRKxTdnLdo == true){GRKxTdnLdo = false;}
      if(EBXPRjXthu == true){EBXPRjXthu = false;}
      if(lgeeaZHLBA == true){lgeeaZHLBA = false;}
      if(ZAJzetBCjX == true){ZAJzetBCjX = false;}
      if(qGGDCcVROM == true){qGGDCcVROM = false;}
      if(mPwhEZmfVs == true){mPwhEZmfVs = false;}
      if(WcKcOErXkX == true){WcKcOErXkX = false;}
      if(iVJJEfabby == true){iVJJEfabby = false;}
      if(EownMKDatE == true){EownMKDatE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUAFIAJHHV
{ 
  void oiocEUkUgU()
  { 
      bool kJRMgiWcEY = false;
      bool AOKRbKbkoU = false;
      bool ZWuUXrDheZ = false;
      bool EMIiWAVteW = false;
      bool mawhjBaryK = false;
      bool NHUmPOOxno = false;
      bool foydTnFbua = false;
      bool ngGSgzZNkW = false;
      bool QLjTLwqUSH = false;
      bool lYGopybSNu = false;
      bool uzwWVfBCFQ = false;
      bool oBMQXTFdRX = false;
      bool wjImoOaQbi = false;
      bool WHzobROMyf = false;
      bool uoOCSjMoRV = false;
      bool syApzKpJhG = false;
      bool FjZWsgBWoG = false;
      bool FrflbHUGTE = false;
      bool CkzFpYHJoQ = false;
      bool bFdqZKOrIk = false;
      string dJupJzMocH;
      string CTyGlNkAkP;
      string thoiboCltd;
      string CIredUBtGF;
      string UyzNBYFFJV;
      string AlzrSwTLNU;
      string wZuzFtaSbR;
      string MqtfuuibhD;
      string ixcXdQIAMh;
      string AoglJtDzIG;
      string xmcrJJqTwX;
      string NqcKkyxWVn;
      string kaGsRWKIWB;
      string qiTbGwUjNU;
      string YoEnUILVAK;
      string wgdTUVfiam;
      string ziwtfeWBEn;
      string dMJAPwVRYI;
      string KnHLFKEAGj;
      string PkJaVorJIp;
      if(dJupJzMocH == xmcrJJqTwX){kJRMgiWcEY = true;}
      else if(xmcrJJqTwX == dJupJzMocH){uzwWVfBCFQ = true;}
      if(CTyGlNkAkP == NqcKkyxWVn){AOKRbKbkoU = true;}
      else if(NqcKkyxWVn == CTyGlNkAkP){oBMQXTFdRX = true;}
      if(thoiboCltd == kaGsRWKIWB){ZWuUXrDheZ = true;}
      else if(kaGsRWKIWB == thoiboCltd){wjImoOaQbi = true;}
      if(CIredUBtGF == qiTbGwUjNU){EMIiWAVteW = true;}
      else if(qiTbGwUjNU == CIredUBtGF){WHzobROMyf = true;}
      if(UyzNBYFFJV == YoEnUILVAK){mawhjBaryK = true;}
      else if(YoEnUILVAK == UyzNBYFFJV){uoOCSjMoRV = true;}
      if(AlzrSwTLNU == wgdTUVfiam){NHUmPOOxno = true;}
      else if(wgdTUVfiam == AlzrSwTLNU){syApzKpJhG = true;}
      if(wZuzFtaSbR == ziwtfeWBEn){foydTnFbua = true;}
      else if(ziwtfeWBEn == wZuzFtaSbR){FjZWsgBWoG = true;}
      if(MqtfuuibhD == dMJAPwVRYI){ngGSgzZNkW = true;}
      if(ixcXdQIAMh == KnHLFKEAGj){QLjTLwqUSH = true;}
      if(AoglJtDzIG == PkJaVorJIp){lYGopybSNu = true;}
      while(dMJAPwVRYI == MqtfuuibhD){FrflbHUGTE = true;}
      while(KnHLFKEAGj == KnHLFKEAGj){CkzFpYHJoQ = true;}
      while(PkJaVorJIp == PkJaVorJIp){bFdqZKOrIk = true;}
      if(kJRMgiWcEY == true){kJRMgiWcEY = false;}
      if(AOKRbKbkoU == true){AOKRbKbkoU = false;}
      if(ZWuUXrDheZ == true){ZWuUXrDheZ = false;}
      if(EMIiWAVteW == true){EMIiWAVteW = false;}
      if(mawhjBaryK == true){mawhjBaryK = false;}
      if(NHUmPOOxno == true){NHUmPOOxno = false;}
      if(foydTnFbua == true){foydTnFbua = false;}
      if(ngGSgzZNkW == true){ngGSgzZNkW = false;}
      if(QLjTLwqUSH == true){QLjTLwqUSH = false;}
      if(lYGopybSNu == true){lYGopybSNu = false;}
      if(uzwWVfBCFQ == true){uzwWVfBCFQ = false;}
      if(oBMQXTFdRX == true){oBMQXTFdRX = false;}
      if(wjImoOaQbi == true){wjImoOaQbi = false;}
      if(WHzobROMyf == true){WHzobROMyf = false;}
      if(uoOCSjMoRV == true){uoOCSjMoRV = false;}
      if(syApzKpJhG == true){syApzKpJhG = false;}
      if(FjZWsgBWoG == true){FjZWsgBWoG = false;}
      if(FrflbHUGTE == true){FrflbHUGTE = false;}
      if(CkzFpYHJoQ == true){CkzFpYHJoQ = false;}
      if(bFdqZKOrIk == true){bFdqZKOrIk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MDELUIUEMJ
{ 
  void IkyHKzOJcl()
  { 
      bool ozUbEMoXel = false;
      bool quDNoTyRJp = false;
      bool jmTRaynMFm = false;
      bool phnBUrwNaD = false;
      bool jywUkiimqM = false;
      bool cRMgUCeCBF = false;
      bool YcRqwIGCsw = false;
      bool WjpFFkpygq = false;
      bool PAUsKYVHfS = false;
      bool MtMUdHgFXc = false;
      bool bgsupraGaj = false;
      bool LgVJpXIXgX = false;
      bool mzVajbXUby = false;
      bool DjZDPiGZDR = false;
      bool xOfwGfYCeF = false;
      bool zJYApbKSKN = false;
      bool UFecfbGRtH = false;
      bool RhTOaXTZUD = false;
      bool DUpVztLZNm = false;
      bool XnOpxqiDPe = false;
      string RLptwKVUCs;
      string UHnnUqnDRa;
      string CneJGLIwBR;
      string jNRdZTCXIY;
      string pHwiYkRmlo;
      string iHMcScffnj;
      string CYSkIGoKNB;
      string oQusjuqwkU;
      string sUKMicAoKw;
      string nViXWQnLZR;
      string wHZkzRLTsW;
      string ljuTqgOFCf;
      string FAzQNSgWVS;
      string HfVTYluYNQ;
      string QgumKDaPgp;
      string ChJtLuHIXg;
      string koxZPGObuE;
      string korkPYELFJ;
      string qRpfQZWbHc;
      string dlBffbiVXE;
      if(RLptwKVUCs == wHZkzRLTsW){ozUbEMoXel = true;}
      else if(wHZkzRLTsW == RLptwKVUCs){bgsupraGaj = true;}
      if(UHnnUqnDRa == ljuTqgOFCf){quDNoTyRJp = true;}
      else if(ljuTqgOFCf == UHnnUqnDRa){LgVJpXIXgX = true;}
      if(CneJGLIwBR == FAzQNSgWVS){jmTRaynMFm = true;}
      else if(FAzQNSgWVS == CneJGLIwBR){mzVajbXUby = true;}
      if(jNRdZTCXIY == HfVTYluYNQ){phnBUrwNaD = true;}
      else if(HfVTYluYNQ == jNRdZTCXIY){DjZDPiGZDR = true;}
      if(pHwiYkRmlo == QgumKDaPgp){jywUkiimqM = true;}
      else if(QgumKDaPgp == pHwiYkRmlo){xOfwGfYCeF = true;}
      if(iHMcScffnj == ChJtLuHIXg){cRMgUCeCBF = true;}
      else if(ChJtLuHIXg == iHMcScffnj){zJYApbKSKN = true;}
      if(CYSkIGoKNB == koxZPGObuE){YcRqwIGCsw = true;}
      else if(koxZPGObuE == CYSkIGoKNB){UFecfbGRtH = true;}
      if(oQusjuqwkU == korkPYELFJ){WjpFFkpygq = true;}
      if(sUKMicAoKw == qRpfQZWbHc){PAUsKYVHfS = true;}
      if(nViXWQnLZR == dlBffbiVXE){MtMUdHgFXc = true;}
      while(korkPYELFJ == oQusjuqwkU){RhTOaXTZUD = true;}
      while(qRpfQZWbHc == qRpfQZWbHc){DUpVztLZNm = true;}
      while(dlBffbiVXE == dlBffbiVXE){XnOpxqiDPe = true;}
      if(ozUbEMoXel == true){ozUbEMoXel = false;}
      if(quDNoTyRJp == true){quDNoTyRJp = false;}
      if(jmTRaynMFm == true){jmTRaynMFm = false;}
      if(phnBUrwNaD == true){phnBUrwNaD = false;}
      if(jywUkiimqM == true){jywUkiimqM = false;}
      if(cRMgUCeCBF == true){cRMgUCeCBF = false;}
      if(YcRqwIGCsw == true){YcRqwIGCsw = false;}
      if(WjpFFkpygq == true){WjpFFkpygq = false;}
      if(PAUsKYVHfS == true){PAUsKYVHfS = false;}
      if(MtMUdHgFXc == true){MtMUdHgFXc = false;}
      if(bgsupraGaj == true){bgsupraGaj = false;}
      if(LgVJpXIXgX == true){LgVJpXIXgX = false;}
      if(mzVajbXUby == true){mzVajbXUby = false;}
      if(DjZDPiGZDR == true){DjZDPiGZDR = false;}
      if(xOfwGfYCeF == true){xOfwGfYCeF = false;}
      if(zJYApbKSKN == true){zJYApbKSKN = false;}
      if(UFecfbGRtH == true){UFecfbGRtH = false;}
      if(RhTOaXTZUD == true){RhTOaXTZUD = false;}
      if(DUpVztLZNm == true){DUpVztLZNm = false;}
      if(XnOpxqiDPe == true){XnOpxqiDPe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWTUQFOGYT
{ 
  void KFlLnKiHjF()
  { 
      bool rrjUrZCyLa = false;
      bool jWAxKXCene = false;
      bool ClwxSgoKsK = false;
      bool QWnPiuugFn = false;
      bool LwSZyGQiep = false;
      bool aSXuBGumCK = false;
      bool kqFBJMhkOP = false;
      bool cVZzTFSWzM = false;
      bool PGeDjxzsOc = false;
      bool zHdtDTqRPk = false;
      bool XfTPMEsXbu = false;
      bool mYnptdLCRL = false;
      bool MoWlPVqeuz = false;
      bool OBGNnjlPpe = false;
      bool EaQSoaSnzZ = false;
      bool HnzDXiJhAq = false;
      bool NNccfkRZBK = false;
      bool rwLlHlXDwo = false;
      bool CCeVraBDpF = false;
      bool aDOzRpynmE = false;
      string izoGQwMCDJ;
      string LtNCuosYHz;
      string KCBhGTkTxM;
      string ecWAgDjyao;
      string QzVAMnhKCg;
      string uWjuVfxHAx;
      string LrFqdhXNVr;
      string FtyRhKgBUR;
      string kaQPRHsadA;
      string GbydcXseVe;
      string PUnKbAYRMK;
      string zwmhLkboYV;
      string owiUkcwToK;
      string RBeoBPlFnR;
      string haNTBJoQRq;
      string wDFzoSlTYy;
      string DFcCsxRxfw;
      string zVBHnOiPSb;
      string mfCxONueAh;
      string cRfpNcyLaD;
      if(izoGQwMCDJ == PUnKbAYRMK){rrjUrZCyLa = true;}
      else if(PUnKbAYRMK == izoGQwMCDJ){XfTPMEsXbu = true;}
      if(LtNCuosYHz == zwmhLkboYV){jWAxKXCene = true;}
      else if(zwmhLkboYV == LtNCuosYHz){mYnptdLCRL = true;}
      if(KCBhGTkTxM == owiUkcwToK){ClwxSgoKsK = true;}
      else if(owiUkcwToK == KCBhGTkTxM){MoWlPVqeuz = true;}
      if(ecWAgDjyao == RBeoBPlFnR){QWnPiuugFn = true;}
      else if(RBeoBPlFnR == ecWAgDjyao){OBGNnjlPpe = true;}
      if(QzVAMnhKCg == haNTBJoQRq){LwSZyGQiep = true;}
      else if(haNTBJoQRq == QzVAMnhKCg){EaQSoaSnzZ = true;}
      if(uWjuVfxHAx == wDFzoSlTYy){aSXuBGumCK = true;}
      else if(wDFzoSlTYy == uWjuVfxHAx){HnzDXiJhAq = true;}
      if(LrFqdhXNVr == DFcCsxRxfw){kqFBJMhkOP = true;}
      else if(DFcCsxRxfw == LrFqdhXNVr){NNccfkRZBK = true;}
      if(FtyRhKgBUR == zVBHnOiPSb){cVZzTFSWzM = true;}
      if(kaQPRHsadA == mfCxONueAh){PGeDjxzsOc = true;}
      if(GbydcXseVe == cRfpNcyLaD){zHdtDTqRPk = true;}
      while(zVBHnOiPSb == FtyRhKgBUR){rwLlHlXDwo = true;}
      while(mfCxONueAh == mfCxONueAh){CCeVraBDpF = true;}
      while(cRfpNcyLaD == cRfpNcyLaD){aDOzRpynmE = true;}
      if(rrjUrZCyLa == true){rrjUrZCyLa = false;}
      if(jWAxKXCene == true){jWAxKXCene = false;}
      if(ClwxSgoKsK == true){ClwxSgoKsK = false;}
      if(QWnPiuugFn == true){QWnPiuugFn = false;}
      if(LwSZyGQiep == true){LwSZyGQiep = false;}
      if(aSXuBGumCK == true){aSXuBGumCK = false;}
      if(kqFBJMhkOP == true){kqFBJMhkOP = false;}
      if(cVZzTFSWzM == true){cVZzTFSWzM = false;}
      if(PGeDjxzsOc == true){PGeDjxzsOc = false;}
      if(zHdtDTqRPk == true){zHdtDTqRPk = false;}
      if(XfTPMEsXbu == true){XfTPMEsXbu = false;}
      if(mYnptdLCRL == true){mYnptdLCRL = false;}
      if(MoWlPVqeuz == true){MoWlPVqeuz = false;}
      if(OBGNnjlPpe == true){OBGNnjlPpe = false;}
      if(EaQSoaSnzZ == true){EaQSoaSnzZ = false;}
      if(HnzDXiJhAq == true){HnzDXiJhAq = false;}
      if(NNccfkRZBK == true){NNccfkRZBK = false;}
      if(rwLlHlXDwo == true){rwLlHlXDwo = false;}
      if(CCeVraBDpF == true){CCeVraBDpF = false;}
      if(aDOzRpynmE == true){aDOzRpynmE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWQOHLNKFP
{ 
  void isdmCMlDFZ()
  { 
      bool kWhHuBfLkZ = false;
      bool NpFHwDEhPG = false;
      bool ZUrAxrqJwo = false;
      bool NUdeRFlbQY = false;
      bool WAAuKrwlNi = false;
      bool yCmkxPdhKC = false;
      bool JWPuMsMaop = false;
      bool QbRqjZUwpF = false;
      bool wFuMqLgrgC = false;
      bool aDRNPzjFiQ = false;
      bool fVxWRVjwBW = false;
      bool ugrEFEaCDA = false;
      bool LTsmONKDbj = false;
      bool oONYYaIXuV = false;
      bool bkqJGsLMHK = false;
      bool YhBiFLbKID = false;
      bool KgUQhfTSee = false;
      bool wCGgYacifU = false;
      bool BxuQLHNeSN = false;
      bool yxPqKtPabZ = false;
      string LWNhDpQfbm;
      string ZEKuMGFFVN;
      string WdaGjyJSLZ;
      string AUoZhHAnTa;
      string ZUmzIUTfKr;
      string QxrrNhuGyF;
      string gxUBlFPjMF;
      string GRlunCpayP;
      string dcISJDbxMA;
      string LspOsbAkMC;
      string EiTEkzLwDL;
      string qUIiaDoBri;
      string dSXLtMbWCM;
      string BFOuKtJDhJ;
      string qetBJqjGmo;
      string lzscYlLHKX;
      string XntpJlFNXf;
      string tkShryYVCD;
      string bUjMZCLkVX;
      string hBsJlCjDrX;
      if(LWNhDpQfbm == EiTEkzLwDL){kWhHuBfLkZ = true;}
      else if(EiTEkzLwDL == LWNhDpQfbm){fVxWRVjwBW = true;}
      if(ZEKuMGFFVN == qUIiaDoBri){NpFHwDEhPG = true;}
      else if(qUIiaDoBri == ZEKuMGFFVN){ugrEFEaCDA = true;}
      if(WdaGjyJSLZ == dSXLtMbWCM){ZUrAxrqJwo = true;}
      else if(dSXLtMbWCM == WdaGjyJSLZ){LTsmONKDbj = true;}
      if(AUoZhHAnTa == BFOuKtJDhJ){NUdeRFlbQY = true;}
      else if(BFOuKtJDhJ == AUoZhHAnTa){oONYYaIXuV = true;}
      if(ZUmzIUTfKr == qetBJqjGmo){WAAuKrwlNi = true;}
      else if(qetBJqjGmo == ZUmzIUTfKr){bkqJGsLMHK = true;}
      if(QxrrNhuGyF == lzscYlLHKX){yCmkxPdhKC = true;}
      else if(lzscYlLHKX == QxrrNhuGyF){YhBiFLbKID = true;}
      if(gxUBlFPjMF == XntpJlFNXf){JWPuMsMaop = true;}
      else if(XntpJlFNXf == gxUBlFPjMF){KgUQhfTSee = true;}
      if(GRlunCpayP == tkShryYVCD){QbRqjZUwpF = true;}
      if(dcISJDbxMA == bUjMZCLkVX){wFuMqLgrgC = true;}
      if(LspOsbAkMC == hBsJlCjDrX){aDRNPzjFiQ = true;}
      while(tkShryYVCD == GRlunCpayP){wCGgYacifU = true;}
      while(bUjMZCLkVX == bUjMZCLkVX){BxuQLHNeSN = true;}
      while(hBsJlCjDrX == hBsJlCjDrX){yxPqKtPabZ = true;}
      if(kWhHuBfLkZ == true){kWhHuBfLkZ = false;}
      if(NpFHwDEhPG == true){NpFHwDEhPG = false;}
      if(ZUrAxrqJwo == true){ZUrAxrqJwo = false;}
      if(NUdeRFlbQY == true){NUdeRFlbQY = false;}
      if(WAAuKrwlNi == true){WAAuKrwlNi = false;}
      if(yCmkxPdhKC == true){yCmkxPdhKC = false;}
      if(JWPuMsMaop == true){JWPuMsMaop = false;}
      if(QbRqjZUwpF == true){QbRqjZUwpF = false;}
      if(wFuMqLgrgC == true){wFuMqLgrgC = false;}
      if(aDRNPzjFiQ == true){aDRNPzjFiQ = false;}
      if(fVxWRVjwBW == true){fVxWRVjwBW = false;}
      if(ugrEFEaCDA == true){ugrEFEaCDA = false;}
      if(LTsmONKDbj == true){LTsmONKDbj = false;}
      if(oONYYaIXuV == true){oONYYaIXuV = false;}
      if(bkqJGsLMHK == true){bkqJGsLMHK = false;}
      if(YhBiFLbKID == true){YhBiFLbKID = false;}
      if(KgUQhfTSee == true){KgUQhfTSee = false;}
      if(wCGgYacifU == true){wCGgYacifU = false;}
      if(BxuQLHNeSN == true){BxuQLHNeSN = false;}
      if(yxPqKtPabZ == true){yxPqKtPabZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGMGEFFNZA
{ 
  void lSSbQZMEwl()
  { 
      bool ZAFuZLdqFV = false;
      bool AMhRFPJQab = false;
      bool qZcbPiFpXn = false;
      bool MIgjoZoTyE = false;
      bool gWkpquDroA = false;
      bool qEPndAWdep = false;
      bool FmSRIqfyce = false;
      bool ZpSVuTomkT = false;
      bool fMBXxHrrGo = false;
      bool DLnHysESgz = false;
      bool PFPKZAlssJ = false;
      bool LirKKsluUB = false;
      bool ynqmaOCKWB = false;
      bool PVGlEaxqyw = false;
      bool UzzxdTTdwF = false;
      bool GIyfAaNbiL = false;
      bool yaVqsocGFj = false;
      bool wuxXfzotJG = false;
      bool tYNRuHWZkd = false;
      bool MUHmytcHDn = false;
      string IykaUQwPPZ;
      string zZzflWMVtw;
      string POBUxCZLfp;
      string enchVoLKci;
      string UMWFIbadhH;
      string hyULQsxQdS;
      string qkjZuLxQJw;
      string KBrLbDruLU;
      string bucXIfSQQc;
      string qtgKqibxJw;
      string eJUlwfGIiN;
      string BBEIpwHMQO;
      string rfzgEQThTr;
      string aukPoRZqab;
      string ZKgDapoYTu;
      string bPfuDyJngf;
      string LXoqmGPoSY;
      string VPknohywFO;
      string auOXQKOpLq;
      string IlKtQBVpPU;
      if(IykaUQwPPZ == eJUlwfGIiN){ZAFuZLdqFV = true;}
      else if(eJUlwfGIiN == IykaUQwPPZ){PFPKZAlssJ = true;}
      if(zZzflWMVtw == BBEIpwHMQO){AMhRFPJQab = true;}
      else if(BBEIpwHMQO == zZzflWMVtw){LirKKsluUB = true;}
      if(POBUxCZLfp == rfzgEQThTr){qZcbPiFpXn = true;}
      else if(rfzgEQThTr == POBUxCZLfp){ynqmaOCKWB = true;}
      if(enchVoLKci == aukPoRZqab){MIgjoZoTyE = true;}
      else if(aukPoRZqab == enchVoLKci){PVGlEaxqyw = true;}
      if(UMWFIbadhH == ZKgDapoYTu){gWkpquDroA = true;}
      else if(ZKgDapoYTu == UMWFIbadhH){UzzxdTTdwF = true;}
      if(hyULQsxQdS == bPfuDyJngf){qEPndAWdep = true;}
      else if(bPfuDyJngf == hyULQsxQdS){GIyfAaNbiL = true;}
      if(qkjZuLxQJw == LXoqmGPoSY){FmSRIqfyce = true;}
      else if(LXoqmGPoSY == qkjZuLxQJw){yaVqsocGFj = true;}
      if(KBrLbDruLU == VPknohywFO){ZpSVuTomkT = true;}
      if(bucXIfSQQc == auOXQKOpLq){fMBXxHrrGo = true;}
      if(qtgKqibxJw == IlKtQBVpPU){DLnHysESgz = true;}
      while(VPknohywFO == KBrLbDruLU){wuxXfzotJG = true;}
      while(auOXQKOpLq == auOXQKOpLq){tYNRuHWZkd = true;}
      while(IlKtQBVpPU == IlKtQBVpPU){MUHmytcHDn = true;}
      if(ZAFuZLdqFV == true){ZAFuZLdqFV = false;}
      if(AMhRFPJQab == true){AMhRFPJQab = false;}
      if(qZcbPiFpXn == true){qZcbPiFpXn = false;}
      if(MIgjoZoTyE == true){MIgjoZoTyE = false;}
      if(gWkpquDroA == true){gWkpquDroA = false;}
      if(qEPndAWdep == true){qEPndAWdep = false;}
      if(FmSRIqfyce == true){FmSRIqfyce = false;}
      if(ZpSVuTomkT == true){ZpSVuTomkT = false;}
      if(fMBXxHrrGo == true){fMBXxHrrGo = false;}
      if(DLnHysESgz == true){DLnHysESgz = false;}
      if(PFPKZAlssJ == true){PFPKZAlssJ = false;}
      if(LirKKsluUB == true){LirKKsluUB = false;}
      if(ynqmaOCKWB == true){ynqmaOCKWB = false;}
      if(PVGlEaxqyw == true){PVGlEaxqyw = false;}
      if(UzzxdTTdwF == true){UzzxdTTdwF = false;}
      if(GIyfAaNbiL == true){GIyfAaNbiL = false;}
      if(yaVqsocGFj == true){yaVqsocGFj = false;}
      if(wuxXfzotJG == true){wuxXfzotJG = false;}
      if(tYNRuHWZkd == true){tYNRuHWZkd = false;}
      if(MUHmytcHDn == true){MUHmytcHDn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJLRPHYUOT
{ 
  void KwiTskoJQk()
  { 
      bool focBgQVUyR = false;
      bool lhrtNTAeXG = false;
      bool UhHmqtOrqO = false;
      bool hJDDtlzqgU = false;
      bool LHXfMXBgqr = false;
      bool IzfiPxgpKm = false;
      bool CddiibdnAb = false;
      bool UIyCuMKaZS = false;
      bool rgBzFicUmw = false;
      bool EIgsSgdoxj = false;
      bool tMgPXAAdmC = false;
      bool mGPqtUbdcA = false;
      bool zIADWLbEiN = false;
      bool iVdoYfAlbF = false;
      bool hzhjJysoyy = false;
      bool EzLwkkLcrL = false;
      bool XutYTRbZSO = false;
      bool TpCWSzaPtY = false;
      bool RlGjIiJhEm = false;
      bool TWsPhlFIQq = false;
      string CwJthYDUZU;
      string exMQJCtRqp;
      string YUIlnVhrUV;
      string CuGWNTBFrY;
      string ELlQwQoFSN;
      string bLuoDgmXGM;
      string pKzDRiqpCo;
      string BoYRlNiqoW;
      string fcYHspAQTf;
      string fdyfisLhyM;
      string YyCcMlmcDo;
      string ywhifNlrJb;
      string iaWWJWqsis;
      string BArbxhZutH;
      string DWNdhiuOzU;
      string HTXWdyafTo;
      string ussJnxDGlx;
      string mpxCYLMsnZ;
      string bbsOlgcVyy;
      string GsbELJdDoj;
      if(CwJthYDUZU == YyCcMlmcDo){focBgQVUyR = true;}
      else if(YyCcMlmcDo == CwJthYDUZU){tMgPXAAdmC = true;}
      if(exMQJCtRqp == ywhifNlrJb){lhrtNTAeXG = true;}
      else if(ywhifNlrJb == exMQJCtRqp){mGPqtUbdcA = true;}
      if(YUIlnVhrUV == iaWWJWqsis){UhHmqtOrqO = true;}
      else if(iaWWJWqsis == YUIlnVhrUV){zIADWLbEiN = true;}
      if(CuGWNTBFrY == BArbxhZutH){hJDDtlzqgU = true;}
      else if(BArbxhZutH == CuGWNTBFrY){iVdoYfAlbF = true;}
      if(ELlQwQoFSN == DWNdhiuOzU){LHXfMXBgqr = true;}
      else if(DWNdhiuOzU == ELlQwQoFSN){hzhjJysoyy = true;}
      if(bLuoDgmXGM == HTXWdyafTo){IzfiPxgpKm = true;}
      else if(HTXWdyafTo == bLuoDgmXGM){EzLwkkLcrL = true;}
      if(pKzDRiqpCo == ussJnxDGlx){CddiibdnAb = true;}
      else if(ussJnxDGlx == pKzDRiqpCo){XutYTRbZSO = true;}
      if(BoYRlNiqoW == mpxCYLMsnZ){UIyCuMKaZS = true;}
      if(fcYHspAQTf == bbsOlgcVyy){rgBzFicUmw = true;}
      if(fdyfisLhyM == GsbELJdDoj){EIgsSgdoxj = true;}
      while(mpxCYLMsnZ == BoYRlNiqoW){TpCWSzaPtY = true;}
      while(bbsOlgcVyy == bbsOlgcVyy){RlGjIiJhEm = true;}
      while(GsbELJdDoj == GsbELJdDoj){TWsPhlFIQq = true;}
      if(focBgQVUyR == true){focBgQVUyR = false;}
      if(lhrtNTAeXG == true){lhrtNTAeXG = false;}
      if(UhHmqtOrqO == true){UhHmqtOrqO = false;}
      if(hJDDtlzqgU == true){hJDDtlzqgU = false;}
      if(LHXfMXBgqr == true){LHXfMXBgqr = false;}
      if(IzfiPxgpKm == true){IzfiPxgpKm = false;}
      if(CddiibdnAb == true){CddiibdnAb = false;}
      if(UIyCuMKaZS == true){UIyCuMKaZS = false;}
      if(rgBzFicUmw == true){rgBzFicUmw = false;}
      if(EIgsSgdoxj == true){EIgsSgdoxj = false;}
      if(tMgPXAAdmC == true){tMgPXAAdmC = false;}
      if(mGPqtUbdcA == true){mGPqtUbdcA = false;}
      if(zIADWLbEiN == true){zIADWLbEiN = false;}
      if(iVdoYfAlbF == true){iVdoYfAlbF = false;}
      if(hzhjJysoyy == true){hzhjJysoyy = false;}
      if(EzLwkkLcrL == true){EzLwkkLcrL = false;}
      if(XutYTRbZSO == true){XutYTRbZSO = false;}
      if(TpCWSzaPtY == true){TpCWSzaPtY = false;}
      if(RlGjIiJhEm == true){RlGjIiJhEm = false;}
      if(TWsPhlFIQq == true){TWsPhlFIQq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSZGWYZTPQ
{ 
  void QkFJVYhzNH()
  { 
      bool BnPKscjidz = false;
      bool dCeauqIrKD = false;
      bool yGFlZUiXcS = false;
      bool mOnDKNoMBD = false;
      bool gBYQYzbYNF = false;
      bool nBZUquicjY = false;
      bool sLGLLONaQh = false;
      bool BuqHWwhnNa = false;
      bool sJKXekoTLO = false;
      bool dLccKUuMEJ = false;
      bool kAIfDrKSyu = false;
      bool NtPJeiBhga = false;
      bool ZtPBDoSNxB = false;
      bool AUjEosBdTm = false;
      bool aWUQAjwSya = false;
      bool TNfdjpjGcO = false;
      bool YxUwtsJLTk = false;
      bool hWOszCZzBS = false;
      bool rAOVhmnGTz = false;
      bool JtBFNcBYVH = false;
      string DPEozSPMEH;
      string sJsUrTRHCb;
      string BIcugPmwIn;
      string ynUpyEihQI;
      string CLotBtZOys;
      string pfzJsumJIi;
      string fTEPJEnDVn;
      string jjqtZoShsm;
      string oXxPyRnLwC;
      string QZZgchGZkw;
      string GWrKIFoFiD;
      string cFQVtHVoRq;
      string QbGTWKJJQr;
      string iswwfRemGr;
      string bibsZKIElV;
      string LRHsfdPYmx;
      string wfnqUiIUob;
      string bihYPgANsM;
      string CFWufQkCPC;
      string CGzJwwtkYp;
      if(DPEozSPMEH == GWrKIFoFiD){BnPKscjidz = true;}
      else if(GWrKIFoFiD == DPEozSPMEH){kAIfDrKSyu = true;}
      if(sJsUrTRHCb == cFQVtHVoRq){dCeauqIrKD = true;}
      else if(cFQVtHVoRq == sJsUrTRHCb){NtPJeiBhga = true;}
      if(BIcugPmwIn == QbGTWKJJQr){yGFlZUiXcS = true;}
      else if(QbGTWKJJQr == BIcugPmwIn){ZtPBDoSNxB = true;}
      if(ynUpyEihQI == iswwfRemGr){mOnDKNoMBD = true;}
      else if(iswwfRemGr == ynUpyEihQI){AUjEosBdTm = true;}
      if(CLotBtZOys == bibsZKIElV){gBYQYzbYNF = true;}
      else if(bibsZKIElV == CLotBtZOys){aWUQAjwSya = true;}
      if(pfzJsumJIi == LRHsfdPYmx){nBZUquicjY = true;}
      else if(LRHsfdPYmx == pfzJsumJIi){TNfdjpjGcO = true;}
      if(fTEPJEnDVn == wfnqUiIUob){sLGLLONaQh = true;}
      else if(wfnqUiIUob == fTEPJEnDVn){YxUwtsJLTk = true;}
      if(jjqtZoShsm == bihYPgANsM){BuqHWwhnNa = true;}
      if(oXxPyRnLwC == CFWufQkCPC){sJKXekoTLO = true;}
      if(QZZgchGZkw == CGzJwwtkYp){dLccKUuMEJ = true;}
      while(bihYPgANsM == jjqtZoShsm){hWOszCZzBS = true;}
      while(CFWufQkCPC == CFWufQkCPC){rAOVhmnGTz = true;}
      while(CGzJwwtkYp == CGzJwwtkYp){JtBFNcBYVH = true;}
      if(BnPKscjidz == true){BnPKscjidz = false;}
      if(dCeauqIrKD == true){dCeauqIrKD = false;}
      if(yGFlZUiXcS == true){yGFlZUiXcS = false;}
      if(mOnDKNoMBD == true){mOnDKNoMBD = false;}
      if(gBYQYzbYNF == true){gBYQYzbYNF = false;}
      if(nBZUquicjY == true){nBZUquicjY = false;}
      if(sLGLLONaQh == true){sLGLLONaQh = false;}
      if(BuqHWwhnNa == true){BuqHWwhnNa = false;}
      if(sJKXekoTLO == true){sJKXekoTLO = false;}
      if(dLccKUuMEJ == true){dLccKUuMEJ = false;}
      if(kAIfDrKSyu == true){kAIfDrKSyu = false;}
      if(NtPJeiBhga == true){NtPJeiBhga = false;}
      if(ZtPBDoSNxB == true){ZtPBDoSNxB = false;}
      if(AUjEosBdTm == true){AUjEosBdTm = false;}
      if(aWUQAjwSya == true){aWUQAjwSya = false;}
      if(TNfdjpjGcO == true){TNfdjpjGcO = false;}
      if(YxUwtsJLTk == true){YxUwtsJLTk = false;}
      if(hWOszCZzBS == true){hWOszCZzBS = false;}
      if(rAOVhmnGTz == true){rAOVhmnGTz = false;}
      if(JtBFNcBYVH == true){JtBFNcBYVH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGJQHTNAKF
{ 
  void MnTEezRnTi()
  { 
      bool mLmAXUnZKO = false;
      bool FCqkPZLDEE = false;
      bool JYRlahsrPW = false;
      bool zGxaDVzZbL = false;
      bool OUyHLRKhni = false;
      bool VEefxNtAYp = false;
      bool awKnPyFPgs = false;
      bool ZkbsonZKaJ = false;
      bool XKDgAubRco = false;
      bool bzAljRKKqN = false;
      bool MtAtIjclpJ = false;
      bool mjZPRPsdmU = false;
      bool VmmqQakoIW = false;
      bool dPSMwdJIXQ = false;
      bool SpaTCrYkTT = false;
      bool YgWWqYGIcg = false;
      bool zmcSeWQMSn = false;
      bool FkFWBfMSoY = false;
      bool BzUoywruVX = false;
      bool WBeqReNIne = false;
      string HHYnzOFCgu;
      string GsXqnBZewe;
      string maoNDjLOWf;
      string zNQJowppLU;
      string dOqfgjWTfp;
      string WZoyUfRLjO;
      string CpeBurcNBr;
      string LiSbAXiJfT;
      string NrigIYYRnI;
      string edGxSnipkn;
      string GIRnenHMxw;
      string xIeQAKGyrV;
      string SKYsMgbVIM;
      string nsYqMEZtCU;
      string RLTrLWzpwI;
      string gkyOVwjYax;
      string LkEjHEimDw;
      string jMwXDGpghp;
      string hlZAfDuJVQ;
      string UBSEIgHjjG;
      if(HHYnzOFCgu == GIRnenHMxw){mLmAXUnZKO = true;}
      else if(GIRnenHMxw == HHYnzOFCgu){MtAtIjclpJ = true;}
      if(GsXqnBZewe == xIeQAKGyrV){FCqkPZLDEE = true;}
      else if(xIeQAKGyrV == GsXqnBZewe){mjZPRPsdmU = true;}
      if(maoNDjLOWf == SKYsMgbVIM){JYRlahsrPW = true;}
      else if(SKYsMgbVIM == maoNDjLOWf){VmmqQakoIW = true;}
      if(zNQJowppLU == nsYqMEZtCU){zGxaDVzZbL = true;}
      else if(nsYqMEZtCU == zNQJowppLU){dPSMwdJIXQ = true;}
      if(dOqfgjWTfp == RLTrLWzpwI){OUyHLRKhni = true;}
      else if(RLTrLWzpwI == dOqfgjWTfp){SpaTCrYkTT = true;}
      if(WZoyUfRLjO == gkyOVwjYax){VEefxNtAYp = true;}
      else if(gkyOVwjYax == WZoyUfRLjO){YgWWqYGIcg = true;}
      if(CpeBurcNBr == LkEjHEimDw){awKnPyFPgs = true;}
      else if(LkEjHEimDw == CpeBurcNBr){zmcSeWQMSn = true;}
      if(LiSbAXiJfT == jMwXDGpghp){ZkbsonZKaJ = true;}
      if(NrigIYYRnI == hlZAfDuJVQ){XKDgAubRco = true;}
      if(edGxSnipkn == UBSEIgHjjG){bzAljRKKqN = true;}
      while(jMwXDGpghp == LiSbAXiJfT){FkFWBfMSoY = true;}
      while(hlZAfDuJVQ == hlZAfDuJVQ){BzUoywruVX = true;}
      while(UBSEIgHjjG == UBSEIgHjjG){WBeqReNIne = true;}
      if(mLmAXUnZKO == true){mLmAXUnZKO = false;}
      if(FCqkPZLDEE == true){FCqkPZLDEE = false;}
      if(JYRlahsrPW == true){JYRlahsrPW = false;}
      if(zGxaDVzZbL == true){zGxaDVzZbL = false;}
      if(OUyHLRKhni == true){OUyHLRKhni = false;}
      if(VEefxNtAYp == true){VEefxNtAYp = false;}
      if(awKnPyFPgs == true){awKnPyFPgs = false;}
      if(ZkbsonZKaJ == true){ZkbsonZKaJ = false;}
      if(XKDgAubRco == true){XKDgAubRco = false;}
      if(bzAljRKKqN == true){bzAljRKKqN = false;}
      if(MtAtIjclpJ == true){MtAtIjclpJ = false;}
      if(mjZPRPsdmU == true){mjZPRPsdmU = false;}
      if(VmmqQakoIW == true){VmmqQakoIW = false;}
      if(dPSMwdJIXQ == true){dPSMwdJIXQ = false;}
      if(SpaTCrYkTT == true){SpaTCrYkTT = false;}
      if(YgWWqYGIcg == true){YgWWqYGIcg = false;}
      if(zmcSeWQMSn == true){zmcSeWQMSn = false;}
      if(FkFWBfMSoY == true){FkFWBfMSoY = false;}
      if(BzUoywruVX == true){BzUoywruVX = false;}
      if(WBeqReNIne == true){WBeqReNIne = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPRIVOJOYJ
{ 
  void tdnqqqtmKo()
  { 
      bool aSqBPtFRfa = false;
      bool SVTwHIrQDO = false;
      bool ecQNZJbyXU = false;
      bool nSCmabpkGx = false;
      bool YZRqdDhCmD = false;
      bool sBEZgxBdbG = false;
      bool RGsLmASgUf = false;
      bool SHJGoEKZjV = false;
      bool bZKUalNbGc = false;
      bool ZMIAfRgGDc = false;
      bool jAgGklqykb = false;
      bool lbsGeqwYjA = false;
      bool mqaqGGyJZX = false;
      bool XEVGkasEjo = false;
      bool uPqdpxSCVo = false;
      bool VIWCpsZoAe = false;
      bool mhXMEhFmUD = false;
      bool yrotFWzwBI = false;
      bool mumkCPgSPr = false;
      bool ADDECMqdZI = false;
      string wXLCtIqNTn;
      string lTXhmoSTUX;
      string AuQlhlETZA;
      string djbuAUJatM;
      string ReKUtRNhTd;
      string TssOqBHZTI;
      string DXnTJCrbgR;
      string frZHGUjuqQ;
      string XWzwfkqMDz;
      string NjGlIsqpKr;
      string YkBCybTlIV;
      string QLhDkgXrnX;
      string KeYhDuknyM;
      string dtjzqlVxxD;
      string RFEghBBDAb;
      string UzClgtMSyC;
      string qfmurWaiLy;
      string LatkGFaqzC;
      string thmWqdqyRx;
      string YCyuMlRInL;
      if(wXLCtIqNTn == YkBCybTlIV){aSqBPtFRfa = true;}
      else if(YkBCybTlIV == wXLCtIqNTn){jAgGklqykb = true;}
      if(lTXhmoSTUX == QLhDkgXrnX){SVTwHIrQDO = true;}
      else if(QLhDkgXrnX == lTXhmoSTUX){lbsGeqwYjA = true;}
      if(AuQlhlETZA == KeYhDuknyM){ecQNZJbyXU = true;}
      else if(KeYhDuknyM == AuQlhlETZA){mqaqGGyJZX = true;}
      if(djbuAUJatM == dtjzqlVxxD){nSCmabpkGx = true;}
      else if(dtjzqlVxxD == djbuAUJatM){XEVGkasEjo = true;}
      if(ReKUtRNhTd == RFEghBBDAb){YZRqdDhCmD = true;}
      else if(RFEghBBDAb == ReKUtRNhTd){uPqdpxSCVo = true;}
      if(TssOqBHZTI == UzClgtMSyC){sBEZgxBdbG = true;}
      else if(UzClgtMSyC == TssOqBHZTI){VIWCpsZoAe = true;}
      if(DXnTJCrbgR == qfmurWaiLy){RGsLmASgUf = true;}
      else if(qfmurWaiLy == DXnTJCrbgR){mhXMEhFmUD = true;}
      if(frZHGUjuqQ == LatkGFaqzC){SHJGoEKZjV = true;}
      if(XWzwfkqMDz == thmWqdqyRx){bZKUalNbGc = true;}
      if(NjGlIsqpKr == YCyuMlRInL){ZMIAfRgGDc = true;}
      while(LatkGFaqzC == frZHGUjuqQ){yrotFWzwBI = true;}
      while(thmWqdqyRx == thmWqdqyRx){mumkCPgSPr = true;}
      while(YCyuMlRInL == YCyuMlRInL){ADDECMqdZI = true;}
      if(aSqBPtFRfa == true){aSqBPtFRfa = false;}
      if(SVTwHIrQDO == true){SVTwHIrQDO = false;}
      if(ecQNZJbyXU == true){ecQNZJbyXU = false;}
      if(nSCmabpkGx == true){nSCmabpkGx = false;}
      if(YZRqdDhCmD == true){YZRqdDhCmD = false;}
      if(sBEZgxBdbG == true){sBEZgxBdbG = false;}
      if(RGsLmASgUf == true){RGsLmASgUf = false;}
      if(SHJGoEKZjV == true){SHJGoEKZjV = false;}
      if(bZKUalNbGc == true){bZKUalNbGc = false;}
      if(ZMIAfRgGDc == true){ZMIAfRgGDc = false;}
      if(jAgGklqykb == true){jAgGklqykb = false;}
      if(lbsGeqwYjA == true){lbsGeqwYjA = false;}
      if(mqaqGGyJZX == true){mqaqGGyJZX = false;}
      if(XEVGkasEjo == true){XEVGkasEjo = false;}
      if(uPqdpxSCVo == true){uPqdpxSCVo = false;}
      if(VIWCpsZoAe == true){VIWCpsZoAe = false;}
      if(mhXMEhFmUD == true){mhXMEhFmUD = false;}
      if(yrotFWzwBI == true){yrotFWzwBI = false;}
      if(mumkCPgSPr == true){mumkCPgSPr = false;}
      if(ADDECMqdZI == true){ADDECMqdZI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HAKRUNTDQX
{ 
  void fUsQuFkOAd()
  { 
      bool RHQtRrQIFB = false;
      bool QHFbgDzirZ = false;
      bool uBcOZtmPhu = false;
      bool MQErycCIzE = false;
      bool OymzKPzjiu = false;
      bool TfmLqQdBTW = false;
      bool FAaKnADNdE = false;
      bool BpinKxNdEK = false;
      bool uCflagcrBg = false;
      bool yAocyNXcKJ = false;
      bool LkGetcxyBs = false;
      bool CAxIbCTniH = false;
      bool WLLwFABGpx = false;
      bool ZkSuyJwBry = false;
      bool jdqHexDfAu = false;
      bool sisDlAYKYs = false;
      bool bpIDTQhCJS = false;
      bool GSukWrTEQI = false;
      bool xVFtDpqOIy = false;
      bool jkbzVsVmmN = false;
      string trYWHnZVDW;
      string NjFnudDlaN;
      string qETNUnGuhf;
      string VWRyeuJoem;
      string bAODMzmNVK;
      string MDXQYoYLBT;
      string gemWBpSHJz;
      string UOGnlpoPBV;
      string BsZXTRzAZo;
      string VxmLFwNrCV;
      string ffDVoyxieh;
      string AIKfSnEPCi;
      string qRgTdWauio;
      string cxNeoUoEhV;
      string UPVqoNmHrQ;
      string rxoTdNyjrR;
      string WCAoFCuepx;
      string zzggNbwpdP;
      string jTCRweHsBa;
      string WEMQySOfll;
      if(trYWHnZVDW == ffDVoyxieh){RHQtRrQIFB = true;}
      else if(ffDVoyxieh == trYWHnZVDW){LkGetcxyBs = true;}
      if(NjFnudDlaN == AIKfSnEPCi){QHFbgDzirZ = true;}
      else if(AIKfSnEPCi == NjFnudDlaN){CAxIbCTniH = true;}
      if(qETNUnGuhf == qRgTdWauio){uBcOZtmPhu = true;}
      else if(qRgTdWauio == qETNUnGuhf){WLLwFABGpx = true;}
      if(VWRyeuJoem == cxNeoUoEhV){MQErycCIzE = true;}
      else if(cxNeoUoEhV == VWRyeuJoem){ZkSuyJwBry = true;}
      if(bAODMzmNVK == UPVqoNmHrQ){OymzKPzjiu = true;}
      else if(UPVqoNmHrQ == bAODMzmNVK){jdqHexDfAu = true;}
      if(MDXQYoYLBT == rxoTdNyjrR){TfmLqQdBTW = true;}
      else if(rxoTdNyjrR == MDXQYoYLBT){sisDlAYKYs = true;}
      if(gemWBpSHJz == WCAoFCuepx){FAaKnADNdE = true;}
      else if(WCAoFCuepx == gemWBpSHJz){bpIDTQhCJS = true;}
      if(UOGnlpoPBV == zzggNbwpdP){BpinKxNdEK = true;}
      if(BsZXTRzAZo == jTCRweHsBa){uCflagcrBg = true;}
      if(VxmLFwNrCV == WEMQySOfll){yAocyNXcKJ = true;}
      while(zzggNbwpdP == UOGnlpoPBV){GSukWrTEQI = true;}
      while(jTCRweHsBa == jTCRweHsBa){xVFtDpqOIy = true;}
      while(WEMQySOfll == WEMQySOfll){jkbzVsVmmN = true;}
      if(RHQtRrQIFB == true){RHQtRrQIFB = false;}
      if(QHFbgDzirZ == true){QHFbgDzirZ = false;}
      if(uBcOZtmPhu == true){uBcOZtmPhu = false;}
      if(MQErycCIzE == true){MQErycCIzE = false;}
      if(OymzKPzjiu == true){OymzKPzjiu = false;}
      if(TfmLqQdBTW == true){TfmLqQdBTW = false;}
      if(FAaKnADNdE == true){FAaKnADNdE = false;}
      if(BpinKxNdEK == true){BpinKxNdEK = false;}
      if(uCflagcrBg == true){uCflagcrBg = false;}
      if(yAocyNXcKJ == true){yAocyNXcKJ = false;}
      if(LkGetcxyBs == true){LkGetcxyBs = false;}
      if(CAxIbCTniH == true){CAxIbCTniH = false;}
      if(WLLwFABGpx == true){WLLwFABGpx = false;}
      if(ZkSuyJwBry == true){ZkSuyJwBry = false;}
      if(jdqHexDfAu == true){jdqHexDfAu = false;}
      if(sisDlAYKYs == true){sisDlAYKYs = false;}
      if(bpIDTQhCJS == true){bpIDTQhCJS = false;}
      if(GSukWrTEQI == true){GSukWrTEQI = false;}
      if(xVFtDpqOIy == true){xVFtDpqOIy = false;}
      if(jkbzVsVmmN == true){jkbzVsVmmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KFLYGBIXPV
{ 
  void IhwAlaLBVL()
  { 
      bool xHpcpnnFpy = false;
      bool RgAJBJVCCs = false;
      bool LTFsShAcoa = false;
      bool gNhdRMewZw = false;
      bool WFJEoledoX = false;
      bool RzIZGdCxJI = false;
      bool mLQPRDyVro = false;
      bool eZbFVFKADf = false;
      bool CWmRIhFHWn = false;
      bool KglRJLosml = false;
      bool mJkAsrWCDB = false;
      bool SBsdGQXyHi = false;
      bool yqyEdxmKwK = false;
      bool PQMRrskmYP = false;
      bool KCDVUInIKr = false;
      bool nplDmwKgVw = false;
      bool FMFskCnbkN = false;
      bool fjZrYumcjU = false;
      bool JeAEWYdJdw = false;
      bool hEQcJyxKkS = false;
      string KJxGtkXfkG;
      string eRADDfByMs;
      string EyacxrjBby;
      string rPtdObgzGw;
      string AtxRDlfXhG;
      string taEshMiUJB;
      string BVDlOPXVoa;
      string yCrPrKAIYL;
      string MLTVDQKAwC;
      string sMoEtepLCm;
      string NJiGIqhoBX;
      string MauyopBhix;
      string FXZlhlMnUN;
      string ToFlxCcNNL;
      string iVyXpSQqOE;
      string cIcFhpiwYV;
      string etTmEXUJAl;
      string NnTWOiYCwO;
      string UVYQkKLADH;
      string TfnqgnCKTR;
      if(KJxGtkXfkG == NJiGIqhoBX){xHpcpnnFpy = true;}
      else if(NJiGIqhoBX == KJxGtkXfkG){mJkAsrWCDB = true;}
      if(eRADDfByMs == MauyopBhix){RgAJBJVCCs = true;}
      else if(MauyopBhix == eRADDfByMs){SBsdGQXyHi = true;}
      if(EyacxrjBby == FXZlhlMnUN){LTFsShAcoa = true;}
      else if(FXZlhlMnUN == EyacxrjBby){yqyEdxmKwK = true;}
      if(rPtdObgzGw == ToFlxCcNNL){gNhdRMewZw = true;}
      else if(ToFlxCcNNL == rPtdObgzGw){PQMRrskmYP = true;}
      if(AtxRDlfXhG == iVyXpSQqOE){WFJEoledoX = true;}
      else if(iVyXpSQqOE == AtxRDlfXhG){KCDVUInIKr = true;}
      if(taEshMiUJB == cIcFhpiwYV){RzIZGdCxJI = true;}
      else if(cIcFhpiwYV == taEshMiUJB){nplDmwKgVw = true;}
      if(BVDlOPXVoa == etTmEXUJAl){mLQPRDyVro = true;}
      else if(etTmEXUJAl == BVDlOPXVoa){FMFskCnbkN = true;}
      if(yCrPrKAIYL == NnTWOiYCwO){eZbFVFKADf = true;}
      if(MLTVDQKAwC == UVYQkKLADH){CWmRIhFHWn = true;}
      if(sMoEtepLCm == TfnqgnCKTR){KglRJLosml = true;}
      while(NnTWOiYCwO == yCrPrKAIYL){fjZrYumcjU = true;}
      while(UVYQkKLADH == UVYQkKLADH){JeAEWYdJdw = true;}
      while(TfnqgnCKTR == TfnqgnCKTR){hEQcJyxKkS = true;}
      if(xHpcpnnFpy == true){xHpcpnnFpy = false;}
      if(RgAJBJVCCs == true){RgAJBJVCCs = false;}
      if(LTFsShAcoa == true){LTFsShAcoa = false;}
      if(gNhdRMewZw == true){gNhdRMewZw = false;}
      if(WFJEoledoX == true){WFJEoledoX = false;}
      if(RzIZGdCxJI == true){RzIZGdCxJI = false;}
      if(mLQPRDyVro == true){mLQPRDyVro = false;}
      if(eZbFVFKADf == true){eZbFVFKADf = false;}
      if(CWmRIhFHWn == true){CWmRIhFHWn = false;}
      if(KglRJLosml == true){KglRJLosml = false;}
      if(mJkAsrWCDB == true){mJkAsrWCDB = false;}
      if(SBsdGQXyHi == true){SBsdGQXyHi = false;}
      if(yqyEdxmKwK == true){yqyEdxmKwK = false;}
      if(PQMRrskmYP == true){PQMRrskmYP = false;}
      if(KCDVUInIKr == true){KCDVUInIKr = false;}
      if(nplDmwKgVw == true){nplDmwKgVw = false;}
      if(FMFskCnbkN == true){FMFskCnbkN = false;}
      if(fjZrYumcjU == true){fjZrYumcjU = false;}
      if(JeAEWYdJdw == true){JeAEWYdJdw = false;}
      if(hEQcJyxKkS == true){hEQcJyxKkS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWELVHTFMN
{ 
  void aThjKBafYc()
  { 
      bool VHeYSPPMRR = false;
      bool XTTLcDdjyX = false;
      bool NFbpFlJcFQ = false;
      bool CYQVsRGsyM = false;
      bool LCyddzwMtb = false;
      bool rbdsBPfoSg = false;
      bool GmGAOyCxSL = false;
      bool wjkkMLGxMG = false;
      bool oxhcYauWTc = false;
      bool kRZRGXuyPe = false;
      bool xztheIprgp = false;
      bool JhcMrIEcbm = false;
      bool DfdoZeJTen = false;
      bool PIhgJpCAxQ = false;
      bool kCocTDoNYx = false;
      bool TRWbbQUEHA = false;
      bool yVNsaAzuDC = false;
      bool FEeKCApAVW = false;
      bool owugUxlGFr = false;
      bool UysxROowCS = false;
      string RwLNtpJgym;
      string DRlMrDNTJs;
      string bFaZodJzaU;
      string CYJewDRNJb;
      string nwjunkIBUs;
      string zWWFWMVlXQ;
      string gKGdkeHHPn;
      string kzJhEfUekE;
      string VHegVeCDHj;
      string hfpstdoGKJ;
      string cAkfHzMnBp;
      string qpAStYfYIF;
      string cDzeGFJQma;
      string qNUbaUWyZV;
      string RNCQsqfWyV;
      string xPyEfYBFZC;
      string pwBazcVXrY;
      string ChzlmOBhlO;
      string YlSRcbOPuB;
      string SQXWfVLbRP;
      if(RwLNtpJgym == cAkfHzMnBp){VHeYSPPMRR = true;}
      else if(cAkfHzMnBp == RwLNtpJgym){xztheIprgp = true;}
      if(DRlMrDNTJs == qpAStYfYIF){XTTLcDdjyX = true;}
      else if(qpAStYfYIF == DRlMrDNTJs){JhcMrIEcbm = true;}
      if(bFaZodJzaU == cDzeGFJQma){NFbpFlJcFQ = true;}
      else if(cDzeGFJQma == bFaZodJzaU){DfdoZeJTen = true;}
      if(CYJewDRNJb == qNUbaUWyZV){CYQVsRGsyM = true;}
      else if(qNUbaUWyZV == CYJewDRNJb){PIhgJpCAxQ = true;}
      if(nwjunkIBUs == RNCQsqfWyV){LCyddzwMtb = true;}
      else if(RNCQsqfWyV == nwjunkIBUs){kCocTDoNYx = true;}
      if(zWWFWMVlXQ == xPyEfYBFZC){rbdsBPfoSg = true;}
      else if(xPyEfYBFZC == zWWFWMVlXQ){TRWbbQUEHA = true;}
      if(gKGdkeHHPn == pwBazcVXrY){GmGAOyCxSL = true;}
      else if(pwBazcVXrY == gKGdkeHHPn){yVNsaAzuDC = true;}
      if(kzJhEfUekE == ChzlmOBhlO){wjkkMLGxMG = true;}
      if(VHegVeCDHj == YlSRcbOPuB){oxhcYauWTc = true;}
      if(hfpstdoGKJ == SQXWfVLbRP){kRZRGXuyPe = true;}
      while(ChzlmOBhlO == kzJhEfUekE){FEeKCApAVW = true;}
      while(YlSRcbOPuB == YlSRcbOPuB){owugUxlGFr = true;}
      while(SQXWfVLbRP == SQXWfVLbRP){UysxROowCS = true;}
      if(VHeYSPPMRR == true){VHeYSPPMRR = false;}
      if(XTTLcDdjyX == true){XTTLcDdjyX = false;}
      if(NFbpFlJcFQ == true){NFbpFlJcFQ = false;}
      if(CYQVsRGsyM == true){CYQVsRGsyM = false;}
      if(LCyddzwMtb == true){LCyddzwMtb = false;}
      if(rbdsBPfoSg == true){rbdsBPfoSg = false;}
      if(GmGAOyCxSL == true){GmGAOyCxSL = false;}
      if(wjkkMLGxMG == true){wjkkMLGxMG = false;}
      if(oxhcYauWTc == true){oxhcYauWTc = false;}
      if(kRZRGXuyPe == true){kRZRGXuyPe = false;}
      if(xztheIprgp == true){xztheIprgp = false;}
      if(JhcMrIEcbm == true){JhcMrIEcbm = false;}
      if(DfdoZeJTen == true){DfdoZeJTen = false;}
      if(PIhgJpCAxQ == true){PIhgJpCAxQ = false;}
      if(kCocTDoNYx == true){kCocTDoNYx = false;}
      if(TRWbbQUEHA == true){TRWbbQUEHA = false;}
      if(yVNsaAzuDC == true){yVNsaAzuDC = false;}
      if(FEeKCApAVW == true){FEeKCApAVW = false;}
      if(owugUxlGFr == true){owugUxlGFr = false;}
      if(UysxROowCS == true){UysxROowCS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PULULUUDAC
{ 
  void yAOQyqqEnB()
  { 
      bool iPHiMuVaAA = false;
      bool LQsLDNetWd = false;
      bool RGiflQONbZ = false;
      bool InhmSPcPMJ = false;
      bool QXQifKxGIa = false;
      bool FRiFIbfaxu = false;
      bool gHyaqXiGsn = false;
      bool kOgMNspAza = false;
      bool SHFBTqEbdq = false;
      bool jBRQcIYprI = false;
      bool bpNUppjVqO = false;
      bool kfbWbZCxGz = false;
      bool SGcCEixQjE = false;
      bool UzIqybsjKd = false;
      bool HhjOFDZunC = false;
      bool GbjroUNLQH = false;
      bool sTlmtlXjXA = false;
      bool fSmbrjVNwA = false;
      bool IBbgyrPPBd = false;
      bool OhSCknwxUT = false;
      string rPraQixiop;
      string VoZughRSLW;
      string ouFqbhTkQh;
      string dbWFtRJADp;
      string AlFuPyVKkW;
      string foifDwKAzi;
      string OMRHMsRUAP;
      string XRPUVDoKbc;
      string LIAtCnsqBx;
      string HIBTanTyiV;
      string fBKUyOZNJA;
      string HAYVWGLWFX;
      string AaSDIOPuth;
      string iqbFxJyewm;
      string OegBpHifwU;
      string bwrKVFhGMi;
      string ydTbQPXTXN;
      string HgaRJUsRMB;
      string fjzYFlyRjr;
      string bqSMojLFjZ;
      if(rPraQixiop == fBKUyOZNJA){iPHiMuVaAA = true;}
      else if(fBKUyOZNJA == rPraQixiop){bpNUppjVqO = true;}
      if(VoZughRSLW == HAYVWGLWFX){LQsLDNetWd = true;}
      else if(HAYVWGLWFX == VoZughRSLW){kfbWbZCxGz = true;}
      if(ouFqbhTkQh == AaSDIOPuth){RGiflQONbZ = true;}
      else if(AaSDIOPuth == ouFqbhTkQh){SGcCEixQjE = true;}
      if(dbWFtRJADp == iqbFxJyewm){InhmSPcPMJ = true;}
      else if(iqbFxJyewm == dbWFtRJADp){UzIqybsjKd = true;}
      if(AlFuPyVKkW == OegBpHifwU){QXQifKxGIa = true;}
      else if(OegBpHifwU == AlFuPyVKkW){HhjOFDZunC = true;}
      if(foifDwKAzi == bwrKVFhGMi){FRiFIbfaxu = true;}
      else if(bwrKVFhGMi == foifDwKAzi){GbjroUNLQH = true;}
      if(OMRHMsRUAP == ydTbQPXTXN){gHyaqXiGsn = true;}
      else if(ydTbQPXTXN == OMRHMsRUAP){sTlmtlXjXA = true;}
      if(XRPUVDoKbc == HgaRJUsRMB){kOgMNspAza = true;}
      if(LIAtCnsqBx == fjzYFlyRjr){SHFBTqEbdq = true;}
      if(HIBTanTyiV == bqSMojLFjZ){jBRQcIYprI = true;}
      while(HgaRJUsRMB == XRPUVDoKbc){fSmbrjVNwA = true;}
      while(fjzYFlyRjr == fjzYFlyRjr){IBbgyrPPBd = true;}
      while(bqSMojLFjZ == bqSMojLFjZ){OhSCknwxUT = true;}
      if(iPHiMuVaAA == true){iPHiMuVaAA = false;}
      if(LQsLDNetWd == true){LQsLDNetWd = false;}
      if(RGiflQONbZ == true){RGiflQONbZ = false;}
      if(InhmSPcPMJ == true){InhmSPcPMJ = false;}
      if(QXQifKxGIa == true){QXQifKxGIa = false;}
      if(FRiFIbfaxu == true){FRiFIbfaxu = false;}
      if(gHyaqXiGsn == true){gHyaqXiGsn = false;}
      if(kOgMNspAza == true){kOgMNspAza = false;}
      if(SHFBTqEbdq == true){SHFBTqEbdq = false;}
      if(jBRQcIYprI == true){jBRQcIYprI = false;}
      if(bpNUppjVqO == true){bpNUppjVqO = false;}
      if(kfbWbZCxGz == true){kfbWbZCxGz = false;}
      if(SGcCEixQjE == true){SGcCEixQjE = false;}
      if(UzIqybsjKd == true){UzIqybsjKd = false;}
      if(HhjOFDZunC == true){HhjOFDZunC = false;}
      if(GbjroUNLQH == true){GbjroUNLQH = false;}
      if(sTlmtlXjXA == true){sTlmtlXjXA = false;}
      if(fSmbrjVNwA == true){fSmbrjVNwA = false;}
      if(IBbgyrPPBd == true){IBbgyrPPBd = false;}
      if(OhSCknwxUT == true){OhSCknwxUT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHUFAFOGVB
{ 
  void iWEZTmSlID()
  { 
      bool LqPVfNfKcR = false;
      bool YyunsItghR = false;
      bool VhxMTdFUlm = false;
      bool RnTHoRCzpQ = false;
      bool lGdplXMoTT = false;
      bool nKCjCcsDCC = false;
      bool HLXpAkenya = false;
      bool GupRfPEHZw = false;
      bool QQASzGkjEM = false;
      bool XyxnIZinpB = false;
      bool sYpsNrTkEm = false;
      bool YldFkqKFqs = false;
      bool zuilCHyCIF = false;
      bool fPRXCrZHEG = false;
      bool mAeQmlUqDR = false;
      bool OcxwCyoDpG = false;
      bool tRbzGIUFCr = false;
      bool RDAkGyPSzQ = false;
      bool lHyppCSUVE = false;
      bool DVQyLUXfKe = false;
      string spwQzaYACs;
      string zUSjYkGVky;
      string egQpGADHbx;
      string YGJKCXresJ;
      string SkxoZehAtC;
      string KaSVJMYFJz;
      string WQXFTsKHhB;
      string rbcaesibQb;
      string RCMZlxmnBo;
      string ylUtlCMrUg;
      string TaSsJhyrpP;
      string dwoggUEySV;
      string FWGrDGGhnc;
      string fpGiIqiTQD;
      string zuykLBxnMR;
      string yOYzbxTapC;
      string aPDNimpFXp;
      string ljhOVJXVfB;
      string JSVWeRQHHL;
      string WHdNcirjBY;
      if(spwQzaYACs == TaSsJhyrpP){LqPVfNfKcR = true;}
      else if(TaSsJhyrpP == spwQzaYACs){sYpsNrTkEm = true;}
      if(zUSjYkGVky == dwoggUEySV){YyunsItghR = true;}
      else if(dwoggUEySV == zUSjYkGVky){YldFkqKFqs = true;}
      if(egQpGADHbx == FWGrDGGhnc){VhxMTdFUlm = true;}
      else if(FWGrDGGhnc == egQpGADHbx){zuilCHyCIF = true;}
      if(YGJKCXresJ == fpGiIqiTQD){RnTHoRCzpQ = true;}
      else if(fpGiIqiTQD == YGJKCXresJ){fPRXCrZHEG = true;}
      if(SkxoZehAtC == zuykLBxnMR){lGdplXMoTT = true;}
      else if(zuykLBxnMR == SkxoZehAtC){mAeQmlUqDR = true;}
      if(KaSVJMYFJz == yOYzbxTapC){nKCjCcsDCC = true;}
      else if(yOYzbxTapC == KaSVJMYFJz){OcxwCyoDpG = true;}
      if(WQXFTsKHhB == aPDNimpFXp){HLXpAkenya = true;}
      else if(aPDNimpFXp == WQXFTsKHhB){tRbzGIUFCr = true;}
      if(rbcaesibQb == ljhOVJXVfB){GupRfPEHZw = true;}
      if(RCMZlxmnBo == JSVWeRQHHL){QQASzGkjEM = true;}
      if(ylUtlCMrUg == WHdNcirjBY){XyxnIZinpB = true;}
      while(ljhOVJXVfB == rbcaesibQb){RDAkGyPSzQ = true;}
      while(JSVWeRQHHL == JSVWeRQHHL){lHyppCSUVE = true;}
      while(WHdNcirjBY == WHdNcirjBY){DVQyLUXfKe = true;}
      if(LqPVfNfKcR == true){LqPVfNfKcR = false;}
      if(YyunsItghR == true){YyunsItghR = false;}
      if(VhxMTdFUlm == true){VhxMTdFUlm = false;}
      if(RnTHoRCzpQ == true){RnTHoRCzpQ = false;}
      if(lGdplXMoTT == true){lGdplXMoTT = false;}
      if(nKCjCcsDCC == true){nKCjCcsDCC = false;}
      if(HLXpAkenya == true){HLXpAkenya = false;}
      if(GupRfPEHZw == true){GupRfPEHZw = false;}
      if(QQASzGkjEM == true){QQASzGkjEM = false;}
      if(XyxnIZinpB == true){XyxnIZinpB = false;}
      if(sYpsNrTkEm == true){sYpsNrTkEm = false;}
      if(YldFkqKFqs == true){YldFkqKFqs = false;}
      if(zuilCHyCIF == true){zuilCHyCIF = false;}
      if(fPRXCrZHEG == true){fPRXCrZHEG = false;}
      if(mAeQmlUqDR == true){mAeQmlUqDR = false;}
      if(OcxwCyoDpG == true){OcxwCyoDpG = false;}
      if(tRbzGIUFCr == true){tRbzGIUFCr = false;}
      if(RDAkGyPSzQ == true){RDAkGyPSzQ = false;}
      if(lHyppCSUVE == true){lHyppCSUVE = false;}
      if(DVQyLUXfKe == true){DVQyLUXfKe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVCZLUOCSD
{ 
  void mYwassucUa()
  { 
      bool iLhfUHcbGO = false;
      bool rAxxIDRMBW = false;
      bool gihEsFlhCz = false;
      bool oxXZBOrVLd = false;
      bool fnoBGCCmzO = false;
      bool bPtyszdcmO = false;
      bool VuYGYubXwt = false;
      bool LuAXqrtgyp = false;
      bool DyhnWYCZfB = false;
      bool kOixHkPhbL = false;
      bool aepFCfPWHB = false;
      bool FxewLWMkjA = false;
      bool rCruIxMDPF = false;
      bool bMFlPXIckp = false;
      bool JfRdwnjllk = false;
      bool YdyaSXmuwF = false;
      bool TMHCYsrrgm = false;
      bool OiAspMkNyU = false;
      bool MZQdgyNdSq = false;
      bool kMgeWxXPED = false;
      string iIxKTXCKWZ;
      string VcBcHwHDum;
      string VucpVkxPRS;
      string IMStVUJRDG;
      string FsSZbWxcRG;
      string fxpijmeHnh;
      string ZlrERJKGGm;
      string moznhbbDNy;
      string nUxLmKWiKi;
      string oCcVfSAOHS;
      string MpVeTpxBBI;
      string KaspsFogRH;
      string mawXxjMdHO;
      string bNwukxyRqw;
      string NVhCXNJmba;
      string dSxAfltxgi;
      string dTslfxexEw;
      string GWpUsRstAj;
      string aZBgkIQuPz;
      string DAkHStbuVa;
      if(iIxKTXCKWZ == MpVeTpxBBI){iLhfUHcbGO = true;}
      else if(MpVeTpxBBI == iIxKTXCKWZ){aepFCfPWHB = true;}
      if(VcBcHwHDum == KaspsFogRH){rAxxIDRMBW = true;}
      else if(KaspsFogRH == VcBcHwHDum){FxewLWMkjA = true;}
      if(VucpVkxPRS == mawXxjMdHO){gihEsFlhCz = true;}
      else if(mawXxjMdHO == VucpVkxPRS){rCruIxMDPF = true;}
      if(IMStVUJRDG == bNwukxyRqw){oxXZBOrVLd = true;}
      else if(bNwukxyRqw == IMStVUJRDG){bMFlPXIckp = true;}
      if(FsSZbWxcRG == NVhCXNJmba){fnoBGCCmzO = true;}
      else if(NVhCXNJmba == FsSZbWxcRG){JfRdwnjllk = true;}
      if(fxpijmeHnh == dSxAfltxgi){bPtyszdcmO = true;}
      else if(dSxAfltxgi == fxpijmeHnh){YdyaSXmuwF = true;}
      if(ZlrERJKGGm == dTslfxexEw){VuYGYubXwt = true;}
      else if(dTslfxexEw == ZlrERJKGGm){TMHCYsrrgm = true;}
      if(moznhbbDNy == GWpUsRstAj){LuAXqrtgyp = true;}
      if(nUxLmKWiKi == aZBgkIQuPz){DyhnWYCZfB = true;}
      if(oCcVfSAOHS == DAkHStbuVa){kOixHkPhbL = true;}
      while(GWpUsRstAj == moznhbbDNy){OiAspMkNyU = true;}
      while(aZBgkIQuPz == aZBgkIQuPz){MZQdgyNdSq = true;}
      while(DAkHStbuVa == DAkHStbuVa){kMgeWxXPED = true;}
      if(iLhfUHcbGO == true){iLhfUHcbGO = false;}
      if(rAxxIDRMBW == true){rAxxIDRMBW = false;}
      if(gihEsFlhCz == true){gihEsFlhCz = false;}
      if(oxXZBOrVLd == true){oxXZBOrVLd = false;}
      if(fnoBGCCmzO == true){fnoBGCCmzO = false;}
      if(bPtyszdcmO == true){bPtyszdcmO = false;}
      if(VuYGYubXwt == true){VuYGYubXwt = false;}
      if(LuAXqrtgyp == true){LuAXqrtgyp = false;}
      if(DyhnWYCZfB == true){DyhnWYCZfB = false;}
      if(kOixHkPhbL == true){kOixHkPhbL = false;}
      if(aepFCfPWHB == true){aepFCfPWHB = false;}
      if(FxewLWMkjA == true){FxewLWMkjA = false;}
      if(rCruIxMDPF == true){rCruIxMDPF = false;}
      if(bMFlPXIckp == true){bMFlPXIckp = false;}
      if(JfRdwnjllk == true){JfRdwnjllk = false;}
      if(YdyaSXmuwF == true){YdyaSXmuwF = false;}
      if(TMHCYsrrgm == true){TMHCYsrrgm = false;}
      if(OiAspMkNyU == true){OiAspMkNyU = false;}
      if(MZQdgyNdSq == true){MZQdgyNdSq = false;}
      if(kMgeWxXPED == true){kMgeWxXPED = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YYJJGBXUBE
{ 
  void jgcCNqhAYC()
  { 
      bool MaHxtQSbDQ = false;
      bool aogNuJetJe = false;
      bool KLOynDmzHl = false;
      bool usjctexGXm = false;
      bool jzpPmuzfKh = false;
      bool ioIlmBMJJp = false;
      bool cSTQUhEDSQ = false;
      bool LXWWtKUzKr = false;
      bool EHoZCFjyos = false;
      bool SmxgJQeZtE = false;
      bool puMtVLRlrc = false;
      bool fNyQkVdtNP = false;
      bool xGNYyYaoMc = false;
      bool euEFCIttDq = false;
      bool nyGMNFogun = false;
      bool mkLeHjhnwx = false;
      bool kbYPxjIrNc = false;
      bool ajpWayzALs = false;
      bool issYptjYyR = false;
      bool ZFyGGLYpPc = false;
      string mOatsIInjL;
      string rjFoZpkiqn;
      string HNIDyZVDml;
      string HMyqAcSdnp;
      string wodGDQGKsB;
      string tCIFeZFXwT;
      string lEAxDfkNnx;
      string WGtArSjBAh;
      string TLJlrFEsMa;
      string WthUEqnfCX;
      string frVudmHHNM;
      string pEXNzZtOEy;
      string arBMabYYwA;
      string dDycBaoOIF;
      string xwfzkSWTVd;
      string wZaEwmqIUB;
      string NiLMilFuMX;
      string jfGzBeMBbH;
      string FEDRDDbtfO;
      string jfsGqOjSQy;
      if(mOatsIInjL == frVudmHHNM){MaHxtQSbDQ = true;}
      else if(frVudmHHNM == mOatsIInjL){puMtVLRlrc = true;}
      if(rjFoZpkiqn == pEXNzZtOEy){aogNuJetJe = true;}
      else if(pEXNzZtOEy == rjFoZpkiqn){fNyQkVdtNP = true;}
      if(HNIDyZVDml == arBMabYYwA){KLOynDmzHl = true;}
      else if(arBMabYYwA == HNIDyZVDml){xGNYyYaoMc = true;}
      if(HMyqAcSdnp == dDycBaoOIF){usjctexGXm = true;}
      else if(dDycBaoOIF == HMyqAcSdnp){euEFCIttDq = true;}
      if(wodGDQGKsB == xwfzkSWTVd){jzpPmuzfKh = true;}
      else if(xwfzkSWTVd == wodGDQGKsB){nyGMNFogun = true;}
      if(tCIFeZFXwT == wZaEwmqIUB){ioIlmBMJJp = true;}
      else if(wZaEwmqIUB == tCIFeZFXwT){mkLeHjhnwx = true;}
      if(lEAxDfkNnx == NiLMilFuMX){cSTQUhEDSQ = true;}
      else if(NiLMilFuMX == lEAxDfkNnx){kbYPxjIrNc = true;}
      if(WGtArSjBAh == jfGzBeMBbH){LXWWtKUzKr = true;}
      if(TLJlrFEsMa == FEDRDDbtfO){EHoZCFjyos = true;}
      if(WthUEqnfCX == jfsGqOjSQy){SmxgJQeZtE = true;}
      while(jfGzBeMBbH == WGtArSjBAh){ajpWayzALs = true;}
      while(FEDRDDbtfO == FEDRDDbtfO){issYptjYyR = true;}
      while(jfsGqOjSQy == jfsGqOjSQy){ZFyGGLYpPc = true;}
      if(MaHxtQSbDQ == true){MaHxtQSbDQ = false;}
      if(aogNuJetJe == true){aogNuJetJe = false;}
      if(KLOynDmzHl == true){KLOynDmzHl = false;}
      if(usjctexGXm == true){usjctexGXm = false;}
      if(jzpPmuzfKh == true){jzpPmuzfKh = false;}
      if(ioIlmBMJJp == true){ioIlmBMJJp = false;}
      if(cSTQUhEDSQ == true){cSTQUhEDSQ = false;}
      if(LXWWtKUzKr == true){LXWWtKUzKr = false;}
      if(EHoZCFjyos == true){EHoZCFjyos = false;}
      if(SmxgJQeZtE == true){SmxgJQeZtE = false;}
      if(puMtVLRlrc == true){puMtVLRlrc = false;}
      if(fNyQkVdtNP == true){fNyQkVdtNP = false;}
      if(xGNYyYaoMc == true){xGNYyYaoMc = false;}
      if(euEFCIttDq == true){euEFCIttDq = false;}
      if(nyGMNFogun == true){nyGMNFogun = false;}
      if(mkLeHjhnwx == true){mkLeHjhnwx = false;}
      if(kbYPxjIrNc == true){kbYPxjIrNc = false;}
      if(ajpWayzALs == true){ajpWayzALs = false;}
      if(issYptjYyR == true){issYptjYyR = false;}
      if(ZFyGGLYpPc == true){ZFyGGLYpPc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDMXSWMNTD
{ 
  void eEHqzpBLkO()
  { 
      bool HNZVxrFyLk = false;
      bool VqlXZUjGMa = false;
      bool YMkSAzSGSB = false;
      bool cxxTDmnAOu = false;
      bool NOffKckCtw = false;
      bool ELKQztcHUx = false;
      bool YzeJHYtRUl = false;
      bool fjqRMJgEIX = false;
      bool OPLWxQlfUJ = false;
      bool KgeQVOiVXk = false;
      bool hShHPTUrEo = false;
      bool MXyxiJmILp = false;
      bool lOxKbzFZwx = false;
      bool aLfWouhEGc = false;
      bool wsaewmhghM = false;
      bool baJgzSVWfQ = false;
      bool OtwGOBqbIm = false;
      bool aiBisrmROo = false;
      bool QYrjVzBzXV = false;
      bool ZLXpNCxTQt = false;
      string ZCBMLRNafE;
      string kRzXSFJQiL;
      string ahXqheHxNa;
      string DRbngnZZrF;
      string BSVofZUXiY;
      string EpegEqeKef;
      string JPNEAToLqe;
      string fiXdJHLhKI;
      string KiNoVNmujo;
      string IPuLulFQoM;
      string kIgErVRBWw;
      string fxzWVZBXil;
      string gsbBVQmLhW;
      string BtsxXBCIwz;
      string ukXmJLPYpV;
      string jghCfqgeib;
      string iGSAukDCyU;
      string XrbjquUorK;
      string BOVMmTMqQf;
      string UXZUQoRXrX;
      if(ZCBMLRNafE == kIgErVRBWw){HNZVxrFyLk = true;}
      else if(kIgErVRBWw == ZCBMLRNafE){hShHPTUrEo = true;}
      if(kRzXSFJQiL == fxzWVZBXil){VqlXZUjGMa = true;}
      else if(fxzWVZBXil == kRzXSFJQiL){MXyxiJmILp = true;}
      if(ahXqheHxNa == gsbBVQmLhW){YMkSAzSGSB = true;}
      else if(gsbBVQmLhW == ahXqheHxNa){lOxKbzFZwx = true;}
      if(DRbngnZZrF == BtsxXBCIwz){cxxTDmnAOu = true;}
      else if(BtsxXBCIwz == DRbngnZZrF){aLfWouhEGc = true;}
      if(BSVofZUXiY == ukXmJLPYpV){NOffKckCtw = true;}
      else if(ukXmJLPYpV == BSVofZUXiY){wsaewmhghM = true;}
      if(EpegEqeKef == jghCfqgeib){ELKQztcHUx = true;}
      else if(jghCfqgeib == EpegEqeKef){baJgzSVWfQ = true;}
      if(JPNEAToLqe == iGSAukDCyU){YzeJHYtRUl = true;}
      else if(iGSAukDCyU == JPNEAToLqe){OtwGOBqbIm = true;}
      if(fiXdJHLhKI == XrbjquUorK){fjqRMJgEIX = true;}
      if(KiNoVNmujo == BOVMmTMqQf){OPLWxQlfUJ = true;}
      if(IPuLulFQoM == UXZUQoRXrX){KgeQVOiVXk = true;}
      while(XrbjquUorK == fiXdJHLhKI){aiBisrmROo = true;}
      while(BOVMmTMqQf == BOVMmTMqQf){QYrjVzBzXV = true;}
      while(UXZUQoRXrX == UXZUQoRXrX){ZLXpNCxTQt = true;}
      if(HNZVxrFyLk == true){HNZVxrFyLk = false;}
      if(VqlXZUjGMa == true){VqlXZUjGMa = false;}
      if(YMkSAzSGSB == true){YMkSAzSGSB = false;}
      if(cxxTDmnAOu == true){cxxTDmnAOu = false;}
      if(NOffKckCtw == true){NOffKckCtw = false;}
      if(ELKQztcHUx == true){ELKQztcHUx = false;}
      if(YzeJHYtRUl == true){YzeJHYtRUl = false;}
      if(fjqRMJgEIX == true){fjqRMJgEIX = false;}
      if(OPLWxQlfUJ == true){OPLWxQlfUJ = false;}
      if(KgeQVOiVXk == true){KgeQVOiVXk = false;}
      if(hShHPTUrEo == true){hShHPTUrEo = false;}
      if(MXyxiJmILp == true){MXyxiJmILp = false;}
      if(lOxKbzFZwx == true){lOxKbzFZwx = false;}
      if(aLfWouhEGc == true){aLfWouhEGc = false;}
      if(wsaewmhghM == true){wsaewmhghM = false;}
      if(baJgzSVWfQ == true){baJgzSVWfQ = false;}
      if(OtwGOBqbIm == true){OtwGOBqbIm = false;}
      if(aiBisrmROo == true){aiBisrmROo = false;}
      if(QYrjVzBzXV == true){QYrjVzBzXV = false;}
      if(ZLXpNCxTQt == true){ZLXpNCxTQt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RJQPRSTSVM
{ 
  void dagHFfpSZN()
  { 
      bool blyLgueBuG = false;
      bool RVANcrLmUo = false;
      bool eFocOEkNYC = false;
      bool AQNmLebWth = false;
      bool CPChuLChoV = false;
      bool VrNVQVxVxb = false;
      bool JQbrFBIMBx = false;
      bool PorlmODHhC = false;
      bool BDYDfICqVp = false;
      bool hGYRYkmJbt = false;
      bool DogqFgzaiC = false;
      bool SomuZGqYMx = false;
      bool yQqLOJPaNB = false;
      bool asfnyMVgxz = false;
      bool IbITWsSdrR = false;
      bool tNxeulyVcw = false;
      bool QYNgaYJzwN = false;
      bool jJbMnWIWnU = false;
      bool pkhuHMwArL = false;
      bool NAEBhiNbsy = false;
      string RnmeySTDGF;
      string uPIdrPaSXP;
      string dDnukpbVVW;
      string czADILMCqZ;
      string DjpTILIeCf;
      string HNbPHOAqsI;
      string pxgibwPEUf;
      string DYayLsMTmZ;
      string hwToPPWjwt;
      string LUIiiGCHqL;
      string uDJVcimdDN;
      string BfETatdrTM;
      string YeIaUhPqPF;
      string qFbaddlxMg;
      string csfhrfPoIo;
      string bKnelQuiBt;
      string SuNyWwDdpw;
      string HgfljfyZin;
      string RaiadgRxnM;
      string hDuRNhehLu;
      if(RnmeySTDGF == uDJVcimdDN){blyLgueBuG = true;}
      else if(uDJVcimdDN == RnmeySTDGF){DogqFgzaiC = true;}
      if(uPIdrPaSXP == BfETatdrTM){RVANcrLmUo = true;}
      else if(BfETatdrTM == uPIdrPaSXP){SomuZGqYMx = true;}
      if(dDnukpbVVW == YeIaUhPqPF){eFocOEkNYC = true;}
      else if(YeIaUhPqPF == dDnukpbVVW){yQqLOJPaNB = true;}
      if(czADILMCqZ == qFbaddlxMg){AQNmLebWth = true;}
      else if(qFbaddlxMg == czADILMCqZ){asfnyMVgxz = true;}
      if(DjpTILIeCf == csfhrfPoIo){CPChuLChoV = true;}
      else if(csfhrfPoIo == DjpTILIeCf){IbITWsSdrR = true;}
      if(HNbPHOAqsI == bKnelQuiBt){VrNVQVxVxb = true;}
      else if(bKnelQuiBt == HNbPHOAqsI){tNxeulyVcw = true;}
      if(pxgibwPEUf == SuNyWwDdpw){JQbrFBIMBx = true;}
      else if(SuNyWwDdpw == pxgibwPEUf){QYNgaYJzwN = true;}
      if(DYayLsMTmZ == HgfljfyZin){PorlmODHhC = true;}
      if(hwToPPWjwt == RaiadgRxnM){BDYDfICqVp = true;}
      if(LUIiiGCHqL == hDuRNhehLu){hGYRYkmJbt = true;}
      while(HgfljfyZin == DYayLsMTmZ){jJbMnWIWnU = true;}
      while(RaiadgRxnM == RaiadgRxnM){pkhuHMwArL = true;}
      while(hDuRNhehLu == hDuRNhehLu){NAEBhiNbsy = true;}
      if(blyLgueBuG == true){blyLgueBuG = false;}
      if(RVANcrLmUo == true){RVANcrLmUo = false;}
      if(eFocOEkNYC == true){eFocOEkNYC = false;}
      if(AQNmLebWth == true){AQNmLebWth = false;}
      if(CPChuLChoV == true){CPChuLChoV = false;}
      if(VrNVQVxVxb == true){VrNVQVxVxb = false;}
      if(JQbrFBIMBx == true){JQbrFBIMBx = false;}
      if(PorlmODHhC == true){PorlmODHhC = false;}
      if(BDYDfICqVp == true){BDYDfICqVp = false;}
      if(hGYRYkmJbt == true){hGYRYkmJbt = false;}
      if(DogqFgzaiC == true){DogqFgzaiC = false;}
      if(SomuZGqYMx == true){SomuZGqYMx = false;}
      if(yQqLOJPaNB == true){yQqLOJPaNB = false;}
      if(asfnyMVgxz == true){asfnyMVgxz = false;}
      if(IbITWsSdrR == true){IbITWsSdrR = false;}
      if(tNxeulyVcw == true){tNxeulyVcw = false;}
      if(QYNgaYJzwN == true){QYNgaYJzwN = false;}
      if(jJbMnWIWnU == true){jJbMnWIWnU = false;}
      if(pkhuHMwArL == true){pkhuHMwArL = false;}
      if(NAEBhiNbsy == true){NAEBhiNbsy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YNROTPCZBQ
{ 
  void yECqZkwAUb()
  { 
      bool TWaYCMHuzL = false;
      bool qHAixDKSGI = false;
      bool VgnSyXCRSq = false;
      bool QrzjunNGUJ = false;
      bool PnyBEmWwsY = false;
      bool OCzobmhIZe = false;
      bool JobHuzHQmJ = false;
      bool oDyxrhimOK = false;
      bool BFXtcNrKII = false;
      bool GFgozZLpGF = false;
      bool fFIjiKDCws = false;
      bool DttOdERheg = false;
      bool HxIeCjVJyR = false;
      bool WrgIeuwmKR = false;
      bool KpNOELLSLu = false;
      bool IcLYyhxdhy = false;
      bool ntDdVLNkih = false;
      bool HdWMWQjsap = false;
      bool YDxCJtgHKx = false;
      bool xSFLcPlisr = false;
      string SHCQLuSMEo;
      string bHJXLeluwh;
      string uCzeAlROIs;
      string DEujBCJKkb;
      string KeSkVmGqWO;
      string zyfQkQIWQY;
      string cEDKlXMZWI;
      string VaJUXPiNJN;
      string farstEXdyk;
      string sltLzGaIyx;
      string ZfUNsYnLsU;
      string gtNDsBLKQh;
      string zialPjfyUQ;
      string naOLmzGdAU;
      string PMjdDzYqSx;
      string tQqQyqEiyI;
      string rppcfFeBPs;
      string uhJuRlzxhP;
      string LofWVXixMw;
      string uWeqbZVGxx;
      if(SHCQLuSMEo == ZfUNsYnLsU){TWaYCMHuzL = true;}
      else if(ZfUNsYnLsU == SHCQLuSMEo){fFIjiKDCws = true;}
      if(bHJXLeluwh == gtNDsBLKQh){qHAixDKSGI = true;}
      else if(gtNDsBLKQh == bHJXLeluwh){DttOdERheg = true;}
      if(uCzeAlROIs == zialPjfyUQ){VgnSyXCRSq = true;}
      else if(zialPjfyUQ == uCzeAlROIs){HxIeCjVJyR = true;}
      if(DEujBCJKkb == naOLmzGdAU){QrzjunNGUJ = true;}
      else if(naOLmzGdAU == DEujBCJKkb){WrgIeuwmKR = true;}
      if(KeSkVmGqWO == PMjdDzYqSx){PnyBEmWwsY = true;}
      else if(PMjdDzYqSx == KeSkVmGqWO){KpNOELLSLu = true;}
      if(zyfQkQIWQY == tQqQyqEiyI){OCzobmhIZe = true;}
      else if(tQqQyqEiyI == zyfQkQIWQY){IcLYyhxdhy = true;}
      if(cEDKlXMZWI == rppcfFeBPs){JobHuzHQmJ = true;}
      else if(rppcfFeBPs == cEDKlXMZWI){ntDdVLNkih = true;}
      if(VaJUXPiNJN == uhJuRlzxhP){oDyxrhimOK = true;}
      if(farstEXdyk == LofWVXixMw){BFXtcNrKII = true;}
      if(sltLzGaIyx == uWeqbZVGxx){GFgozZLpGF = true;}
      while(uhJuRlzxhP == VaJUXPiNJN){HdWMWQjsap = true;}
      while(LofWVXixMw == LofWVXixMw){YDxCJtgHKx = true;}
      while(uWeqbZVGxx == uWeqbZVGxx){xSFLcPlisr = true;}
      if(TWaYCMHuzL == true){TWaYCMHuzL = false;}
      if(qHAixDKSGI == true){qHAixDKSGI = false;}
      if(VgnSyXCRSq == true){VgnSyXCRSq = false;}
      if(QrzjunNGUJ == true){QrzjunNGUJ = false;}
      if(PnyBEmWwsY == true){PnyBEmWwsY = false;}
      if(OCzobmhIZe == true){OCzobmhIZe = false;}
      if(JobHuzHQmJ == true){JobHuzHQmJ = false;}
      if(oDyxrhimOK == true){oDyxrhimOK = false;}
      if(BFXtcNrKII == true){BFXtcNrKII = false;}
      if(GFgozZLpGF == true){GFgozZLpGF = false;}
      if(fFIjiKDCws == true){fFIjiKDCws = false;}
      if(DttOdERheg == true){DttOdERheg = false;}
      if(HxIeCjVJyR == true){HxIeCjVJyR = false;}
      if(WrgIeuwmKR == true){WrgIeuwmKR = false;}
      if(KpNOELLSLu == true){KpNOELLSLu = false;}
      if(IcLYyhxdhy == true){IcLYyhxdhy = false;}
      if(ntDdVLNkih == true){ntDdVLNkih = false;}
      if(HdWMWQjsap == true){HdWMWQjsap = false;}
      if(YDxCJtgHKx == true){YDxCJtgHKx = false;}
      if(xSFLcPlisr == true){xSFLcPlisr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LVYCPXGUPJ
{ 
  void NtPJZBWNiu()
  { 
      bool kDbiQpSusr = false;
      bool tCRykKqiLZ = false;
      bool tVnXAGVuXz = false;
      bool OoawSGathS = false;
      bool eGXIYTJGHT = false;
      bool LVBlhOPDiK = false;
      bool TXXtdEbVed = false;
      bool jxBsunyeyg = false;
      bool wPmDmrnnOE = false;
      bool qWLWyGhcdU = false;
      bool qnacjNUIps = false;
      bool PjFBNDjUGk = false;
      bool QmGZmNkdtn = false;
      bool FUAdoInKTY = false;
      bool XfxUnGRJJt = false;
      bool VNWsDDgBpV = false;
      bool cqNCmtiaLE = false;
      bool PZAgNkolkf = false;
      bool waTzSryHZl = false;
      bool bmTxwfRugt = false;
      string GlPySXgDnF;
      string dCJiEgjMFj;
      string jNEeqOQPnO;
      string CAqbOEgjpG;
      string OxTXxssJeA;
      string kZfPPrgjGD;
      string HROYCcLhUA;
      string AAVyVltghy;
      string VGkndbUaLW;
      string XwcmzxhtUT;
      string gKodzkEgsc;
      string xzCIgAgauZ;
      string HjVybEWiyY;
      string EALNQKRGns;
      string XnhiYXsTFz;
      string QGyuMxopCu;
      string NUiUXwmorV;
      string hZmCBTClYE;
      string KCdzIyCQBT;
      string VbEreCFMLb;
      if(GlPySXgDnF == gKodzkEgsc){kDbiQpSusr = true;}
      else if(gKodzkEgsc == GlPySXgDnF){qnacjNUIps = true;}
      if(dCJiEgjMFj == xzCIgAgauZ){tCRykKqiLZ = true;}
      else if(xzCIgAgauZ == dCJiEgjMFj){PjFBNDjUGk = true;}
      if(jNEeqOQPnO == HjVybEWiyY){tVnXAGVuXz = true;}
      else if(HjVybEWiyY == jNEeqOQPnO){QmGZmNkdtn = true;}
      if(CAqbOEgjpG == EALNQKRGns){OoawSGathS = true;}
      else if(EALNQKRGns == CAqbOEgjpG){FUAdoInKTY = true;}
      if(OxTXxssJeA == XnhiYXsTFz){eGXIYTJGHT = true;}
      else if(XnhiYXsTFz == OxTXxssJeA){XfxUnGRJJt = true;}
      if(kZfPPrgjGD == QGyuMxopCu){LVBlhOPDiK = true;}
      else if(QGyuMxopCu == kZfPPrgjGD){VNWsDDgBpV = true;}
      if(HROYCcLhUA == NUiUXwmorV){TXXtdEbVed = true;}
      else if(NUiUXwmorV == HROYCcLhUA){cqNCmtiaLE = true;}
      if(AAVyVltghy == hZmCBTClYE){jxBsunyeyg = true;}
      if(VGkndbUaLW == KCdzIyCQBT){wPmDmrnnOE = true;}
      if(XwcmzxhtUT == VbEreCFMLb){qWLWyGhcdU = true;}
      while(hZmCBTClYE == AAVyVltghy){PZAgNkolkf = true;}
      while(KCdzIyCQBT == KCdzIyCQBT){waTzSryHZl = true;}
      while(VbEreCFMLb == VbEreCFMLb){bmTxwfRugt = true;}
      if(kDbiQpSusr == true){kDbiQpSusr = false;}
      if(tCRykKqiLZ == true){tCRykKqiLZ = false;}
      if(tVnXAGVuXz == true){tVnXAGVuXz = false;}
      if(OoawSGathS == true){OoawSGathS = false;}
      if(eGXIYTJGHT == true){eGXIYTJGHT = false;}
      if(LVBlhOPDiK == true){LVBlhOPDiK = false;}
      if(TXXtdEbVed == true){TXXtdEbVed = false;}
      if(jxBsunyeyg == true){jxBsunyeyg = false;}
      if(wPmDmrnnOE == true){wPmDmrnnOE = false;}
      if(qWLWyGhcdU == true){qWLWyGhcdU = false;}
      if(qnacjNUIps == true){qnacjNUIps = false;}
      if(PjFBNDjUGk == true){PjFBNDjUGk = false;}
      if(QmGZmNkdtn == true){QmGZmNkdtn = false;}
      if(FUAdoInKTY == true){FUAdoInKTY = false;}
      if(XfxUnGRJJt == true){XfxUnGRJJt = false;}
      if(VNWsDDgBpV == true){VNWsDDgBpV = false;}
      if(cqNCmtiaLE == true){cqNCmtiaLE = false;}
      if(PZAgNkolkf == true){PZAgNkolkf = false;}
      if(waTzSryHZl == true){waTzSryHZl = false;}
      if(bmTxwfRugt == true){bmTxwfRugt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CJKUGTUNGW
{ 
  void obcePHZpRy()
  { 
      bool ntsjudsiFz = false;
      bool uNNFcLXQGZ = false;
      bool ZpzGpWDuPV = false;
      bool ywfyEDQOwt = false;
      bool ooOPBqEeqw = false;
      bool PRQwqxulsX = false;
      bool ZySiAygOAZ = false;
      bool uITLkkaiFz = false;
      bool SYDTGgfjHH = false;
      bool IdUYUpVfPC = false;
      bool JpeRAGxEKG = false;
      bool WLgtFAtzcS = false;
      bool SxHsRQmuqt = false;
      bool OuTDobslSz = false;
      bool iaZAjwxaST = false;
      bool wVCwjMhkAj = false;
      bool TCNPqardFd = false;
      bool HIfciqXGIU = false;
      bool TMcWysrXSb = false;
      bool sHkifgNJJJ = false;
      string duMrLWKONN;
      string TWHlBxtAMa;
      string QJfEddhJdE;
      string iRbsOLZabL;
      string rESMFfLehD;
      string xYnENUPINh;
      string nAkIdBtNXo;
      string WTXBhLpSyx;
      string SCbZGKdXfs;
      string wRMtWqTJiD;
      string lxHrfcAmVB;
      string dwJPPkYKCT;
      string XVhdsFHddq;
      string rfjuLUujtd;
      string JqCeOAIxek;
      string SJHPfPPcyZ;
      string VWIeIyLNDt;
      string poPXJgTCPs;
      string xJzrXiYUOw;
      string ESkUHmhWVQ;
      if(duMrLWKONN == lxHrfcAmVB){ntsjudsiFz = true;}
      else if(lxHrfcAmVB == duMrLWKONN){JpeRAGxEKG = true;}
      if(TWHlBxtAMa == dwJPPkYKCT){uNNFcLXQGZ = true;}
      else if(dwJPPkYKCT == TWHlBxtAMa){WLgtFAtzcS = true;}
      if(QJfEddhJdE == XVhdsFHddq){ZpzGpWDuPV = true;}
      else if(XVhdsFHddq == QJfEddhJdE){SxHsRQmuqt = true;}
      if(iRbsOLZabL == rfjuLUujtd){ywfyEDQOwt = true;}
      else if(rfjuLUujtd == iRbsOLZabL){OuTDobslSz = true;}
      if(rESMFfLehD == JqCeOAIxek){ooOPBqEeqw = true;}
      else if(JqCeOAIxek == rESMFfLehD){iaZAjwxaST = true;}
      if(xYnENUPINh == SJHPfPPcyZ){PRQwqxulsX = true;}
      else if(SJHPfPPcyZ == xYnENUPINh){wVCwjMhkAj = true;}
      if(nAkIdBtNXo == VWIeIyLNDt){ZySiAygOAZ = true;}
      else if(VWIeIyLNDt == nAkIdBtNXo){TCNPqardFd = true;}
      if(WTXBhLpSyx == poPXJgTCPs){uITLkkaiFz = true;}
      if(SCbZGKdXfs == xJzrXiYUOw){SYDTGgfjHH = true;}
      if(wRMtWqTJiD == ESkUHmhWVQ){IdUYUpVfPC = true;}
      while(poPXJgTCPs == WTXBhLpSyx){HIfciqXGIU = true;}
      while(xJzrXiYUOw == xJzrXiYUOw){TMcWysrXSb = true;}
      while(ESkUHmhWVQ == ESkUHmhWVQ){sHkifgNJJJ = true;}
      if(ntsjudsiFz == true){ntsjudsiFz = false;}
      if(uNNFcLXQGZ == true){uNNFcLXQGZ = false;}
      if(ZpzGpWDuPV == true){ZpzGpWDuPV = false;}
      if(ywfyEDQOwt == true){ywfyEDQOwt = false;}
      if(ooOPBqEeqw == true){ooOPBqEeqw = false;}
      if(PRQwqxulsX == true){PRQwqxulsX = false;}
      if(ZySiAygOAZ == true){ZySiAygOAZ = false;}
      if(uITLkkaiFz == true){uITLkkaiFz = false;}
      if(SYDTGgfjHH == true){SYDTGgfjHH = false;}
      if(IdUYUpVfPC == true){IdUYUpVfPC = false;}
      if(JpeRAGxEKG == true){JpeRAGxEKG = false;}
      if(WLgtFAtzcS == true){WLgtFAtzcS = false;}
      if(SxHsRQmuqt == true){SxHsRQmuqt = false;}
      if(OuTDobslSz == true){OuTDobslSz = false;}
      if(iaZAjwxaST == true){iaZAjwxaST = false;}
      if(wVCwjMhkAj == true){wVCwjMhkAj = false;}
      if(TCNPqardFd == true){TCNPqardFd = false;}
      if(HIfciqXGIU == true){HIfciqXGIU = false;}
      if(TMcWysrXSb == true){TMcWysrXSb = false;}
      if(sHkifgNJJJ == true){sHkifgNJJJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMEQFINZCD
{ 
  void qyzQKQLPeQ()
  { 
      bool sgCxddDxhT = false;
      bool QwkrkMmQzN = false;
      bool OPkijaOYHd = false;
      bool ECqkVbZsds = false;
      bool DLeTOBcaiG = false;
      bool lFUUycwTND = false;
      bool PdoEPOFzVJ = false;
      bool mtmFJCkQTh = false;
      bool xnpBqzhWms = false;
      bool eFfZdZVaEA = false;
      bool wdEYSrROKu = false;
      bool qezeFamnMP = false;
      bool fhLcdgNMai = false;
      bool fKLTlTiRhz = false;
      bool gTLrBzFATC = false;
      bool mhNnTNRbul = false;
      bool dEmbOgSfrl = false;
      bool rVGNiMWTbd = false;
      bool aNrXwywXzY = false;
      bool BHWwUbfjcT = false;
      string lUnjfWYkIZ;
      string ANGXCsBCut;
      string okBifOQxGb;
      string LgDEtRREyM;
      string shqIjLyydj;
      string gFjGeBTFDR;
      string FadfOSJBdj;
      string awDhBGsryU;
      string PSTWtGxwZs;
      string yMBgGRDKtQ;
      string BwUsIkBBFX;
      string HaGiBmHHkI;
      string VNajlOuWbi;
      string DiyhTTyZNJ;
      string EuqCkWFReT;
      string KwYktmVjHt;
      string peYWTYcYOh;
      string ogsbDaWYyP;
      string IcqIXGJMmf;
      string xNSTTZVThM;
      if(lUnjfWYkIZ == BwUsIkBBFX){sgCxddDxhT = true;}
      else if(BwUsIkBBFX == lUnjfWYkIZ){wdEYSrROKu = true;}
      if(ANGXCsBCut == HaGiBmHHkI){QwkrkMmQzN = true;}
      else if(HaGiBmHHkI == ANGXCsBCut){qezeFamnMP = true;}
      if(okBifOQxGb == VNajlOuWbi){OPkijaOYHd = true;}
      else if(VNajlOuWbi == okBifOQxGb){fhLcdgNMai = true;}
      if(LgDEtRREyM == DiyhTTyZNJ){ECqkVbZsds = true;}
      else if(DiyhTTyZNJ == LgDEtRREyM){fKLTlTiRhz = true;}
      if(shqIjLyydj == EuqCkWFReT){DLeTOBcaiG = true;}
      else if(EuqCkWFReT == shqIjLyydj){gTLrBzFATC = true;}
      if(gFjGeBTFDR == KwYktmVjHt){lFUUycwTND = true;}
      else if(KwYktmVjHt == gFjGeBTFDR){mhNnTNRbul = true;}
      if(FadfOSJBdj == peYWTYcYOh){PdoEPOFzVJ = true;}
      else if(peYWTYcYOh == FadfOSJBdj){dEmbOgSfrl = true;}
      if(awDhBGsryU == ogsbDaWYyP){mtmFJCkQTh = true;}
      if(PSTWtGxwZs == IcqIXGJMmf){xnpBqzhWms = true;}
      if(yMBgGRDKtQ == xNSTTZVThM){eFfZdZVaEA = true;}
      while(ogsbDaWYyP == awDhBGsryU){rVGNiMWTbd = true;}
      while(IcqIXGJMmf == IcqIXGJMmf){aNrXwywXzY = true;}
      while(xNSTTZVThM == xNSTTZVThM){BHWwUbfjcT = true;}
      if(sgCxddDxhT == true){sgCxddDxhT = false;}
      if(QwkrkMmQzN == true){QwkrkMmQzN = false;}
      if(OPkijaOYHd == true){OPkijaOYHd = false;}
      if(ECqkVbZsds == true){ECqkVbZsds = false;}
      if(DLeTOBcaiG == true){DLeTOBcaiG = false;}
      if(lFUUycwTND == true){lFUUycwTND = false;}
      if(PdoEPOFzVJ == true){PdoEPOFzVJ = false;}
      if(mtmFJCkQTh == true){mtmFJCkQTh = false;}
      if(xnpBqzhWms == true){xnpBqzhWms = false;}
      if(eFfZdZVaEA == true){eFfZdZVaEA = false;}
      if(wdEYSrROKu == true){wdEYSrROKu = false;}
      if(qezeFamnMP == true){qezeFamnMP = false;}
      if(fhLcdgNMai == true){fhLcdgNMai = false;}
      if(fKLTlTiRhz == true){fKLTlTiRhz = false;}
      if(gTLrBzFATC == true){gTLrBzFATC = false;}
      if(mhNnTNRbul == true){mhNnTNRbul = false;}
      if(dEmbOgSfrl == true){dEmbOgSfrl = false;}
      if(rVGNiMWTbd == true){rVGNiMWTbd = false;}
      if(aNrXwywXzY == true){aNrXwywXzY = false;}
      if(BHWwUbfjcT == true){BHWwUbfjcT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHJQLEERPQ
{ 
  void kcpqmCfNgA()
  { 
      bool eIIhNtCNlx = false;
      bool TNwrMjXGoH = false;
      bool hTfZaXVlLO = false;
      bool jCEJGOtgkP = false;
      bool LwNfeVyRDO = false;
      bool yWgReLbiGo = false;
      bool YPBXNRImky = false;
      bool opVYwlFztF = false;
      bool ZDhwPNVldu = false;
      bool lKauqutpSM = false;
      bool MKfFZHBHVs = false;
      bool FcnAPVhEHz = false;
      bool wVJpLdPahA = false;
      bool qPfgrOWcWI = false;
      bool LNQjpJWZfV = false;
      bool NoiSQpBptu = false;
      bool raZUCpwHHA = false;
      bool yFgzniEYzC = false;
      bool HptMmBgMQC = false;
      bool NgibPkmwhA = false;
      string HniMjualUa;
      string UcEOCecksI;
      string JdEgRKHyJP;
      string eAbxIZVsBA;
      string YjaOfmVAri;
      string GcdUOdiCuY;
      string nbbFwUBHFc;
      string JiiriZDpBd;
      string oHFZICVHie;
      string qTybMxHURK;
      string lOtPZWskln;
      string ZrAQjfVCwt;
      string ysXakpjGfl;
      string ShXprZNoAk;
      string IjVtEzShrg;
      string aEYXMrpSej;
      string llFzVqTKYK;
      string SfCKkOXcVl;
      string WCOyKNJAdz;
      string itKQyVdVYM;
      if(HniMjualUa == lOtPZWskln){eIIhNtCNlx = true;}
      else if(lOtPZWskln == HniMjualUa){MKfFZHBHVs = true;}
      if(UcEOCecksI == ZrAQjfVCwt){TNwrMjXGoH = true;}
      else if(ZrAQjfVCwt == UcEOCecksI){FcnAPVhEHz = true;}
      if(JdEgRKHyJP == ysXakpjGfl){hTfZaXVlLO = true;}
      else if(ysXakpjGfl == JdEgRKHyJP){wVJpLdPahA = true;}
      if(eAbxIZVsBA == ShXprZNoAk){jCEJGOtgkP = true;}
      else if(ShXprZNoAk == eAbxIZVsBA){qPfgrOWcWI = true;}
      if(YjaOfmVAri == IjVtEzShrg){LwNfeVyRDO = true;}
      else if(IjVtEzShrg == YjaOfmVAri){LNQjpJWZfV = true;}
      if(GcdUOdiCuY == aEYXMrpSej){yWgReLbiGo = true;}
      else if(aEYXMrpSej == GcdUOdiCuY){NoiSQpBptu = true;}
      if(nbbFwUBHFc == llFzVqTKYK){YPBXNRImky = true;}
      else if(llFzVqTKYK == nbbFwUBHFc){raZUCpwHHA = true;}
      if(JiiriZDpBd == SfCKkOXcVl){opVYwlFztF = true;}
      if(oHFZICVHie == WCOyKNJAdz){ZDhwPNVldu = true;}
      if(qTybMxHURK == itKQyVdVYM){lKauqutpSM = true;}
      while(SfCKkOXcVl == JiiriZDpBd){yFgzniEYzC = true;}
      while(WCOyKNJAdz == WCOyKNJAdz){HptMmBgMQC = true;}
      while(itKQyVdVYM == itKQyVdVYM){NgibPkmwhA = true;}
      if(eIIhNtCNlx == true){eIIhNtCNlx = false;}
      if(TNwrMjXGoH == true){TNwrMjXGoH = false;}
      if(hTfZaXVlLO == true){hTfZaXVlLO = false;}
      if(jCEJGOtgkP == true){jCEJGOtgkP = false;}
      if(LwNfeVyRDO == true){LwNfeVyRDO = false;}
      if(yWgReLbiGo == true){yWgReLbiGo = false;}
      if(YPBXNRImky == true){YPBXNRImky = false;}
      if(opVYwlFztF == true){opVYwlFztF = false;}
      if(ZDhwPNVldu == true){ZDhwPNVldu = false;}
      if(lKauqutpSM == true){lKauqutpSM = false;}
      if(MKfFZHBHVs == true){MKfFZHBHVs = false;}
      if(FcnAPVhEHz == true){FcnAPVhEHz = false;}
      if(wVJpLdPahA == true){wVJpLdPahA = false;}
      if(qPfgrOWcWI == true){qPfgrOWcWI = false;}
      if(LNQjpJWZfV == true){LNQjpJWZfV = false;}
      if(NoiSQpBptu == true){NoiSQpBptu = false;}
      if(raZUCpwHHA == true){raZUCpwHHA = false;}
      if(yFgzniEYzC == true){yFgzniEYzC = false;}
      if(HptMmBgMQC == true){HptMmBgMQC = false;}
      if(NgibPkmwhA == true){NgibPkmwhA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXQNRXJFNC
{ 
  void SuVWBZLVif()
  { 
      bool TzMyCRLGBG = false;
      bool GgdlTtrGRh = false;
      bool iDrYELqOdx = false;
      bool KMHqFoDJZg = false;
      bool htzQoImHrf = false;
      bool aRsxXQHmsp = false;
      bool ZwbDutYmge = false;
      bool pigjznEaiw = false;
      bool YiWyVsTJSo = false;
      bool hPPjHlSuVu = false;
      bool jAaNprkJyi = false;
      bool LfExQpZdgB = false;
      bool ZOTqwZSwbN = false;
      bool VJFnLYHIId = false;
      bool HKLjcCLSSQ = false;
      bool LnNTUUfjQP = false;
      bool ZogkNCaPkr = false;
      bool hQVDtPCjNt = false;
      bool NzcLBhukSp = false;
      bool rXqrEScaVZ = false;
      string yWoaetfZHV;
      string rLEVgMDXDJ;
      string krcQaBIUsa;
      string RCRssnQcap;
      string ISgHWXauDJ;
      string ixEVbGsXzd;
      string lKggEotLcs;
      string waxMBSLVtD;
      string ZMRirTyuQm;
      string urcwExkzCg;
      string cPSKMHAqUJ;
      string uWcuEYsxoj;
      string qyuoyExAID;
      string gLSNaJtGVj;
      string THaHqXPgrf;
      string EmKSpdUcMI;
      string KAiQbjDPUt;
      string dlbEQjWnyZ;
      string oPHbzsAAWw;
      string oRtMZTYKfH;
      if(yWoaetfZHV == cPSKMHAqUJ){TzMyCRLGBG = true;}
      else if(cPSKMHAqUJ == yWoaetfZHV){jAaNprkJyi = true;}
      if(rLEVgMDXDJ == uWcuEYsxoj){GgdlTtrGRh = true;}
      else if(uWcuEYsxoj == rLEVgMDXDJ){LfExQpZdgB = true;}
      if(krcQaBIUsa == qyuoyExAID){iDrYELqOdx = true;}
      else if(qyuoyExAID == krcQaBIUsa){ZOTqwZSwbN = true;}
      if(RCRssnQcap == gLSNaJtGVj){KMHqFoDJZg = true;}
      else if(gLSNaJtGVj == RCRssnQcap){VJFnLYHIId = true;}
      if(ISgHWXauDJ == THaHqXPgrf){htzQoImHrf = true;}
      else if(THaHqXPgrf == ISgHWXauDJ){HKLjcCLSSQ = true;}
      if(ixEVbGsXzd == EmKSpdUcMI){aRsxXQHmsp = true;}
      else if(EmKSpdUcMI == ixEVbGsXzd){LnNTUUfjQP = true;}
      if(lKggEotLcs == KAiQbjDPUt){ZwbDutYmge = true;}
      else if(KAiQbjDPUt == lKggEotLcs){ZogkNCaPkr = true;}
      if(waxMBSLVtD == dlbEQjWnyZ){pigjznEaiw = true;}
      if(ZMRirTyuQm == oPHbzsAAWw){YiWyVsTJSo = true;}
      if(urcwExkzCg == oRtMZTYKfH){hPPjHlSuVu = true;}
      while(dlbEQjWnyZ == waxMBSLVtD){hQVDtPCjNt = true;}
      while(oPHbzsAAWw == oPHbzsAAWw){NzcLBhukSp = true;}
      while(oRtMZTYKfH == oRtMZTYKfH){rXqrEScaVZ = true;}
      if(TzMyCRLGBG == true){TzMyCRLGBG = false;}
      if(GgdlTtrGRh == true){GgdlTtrGRh = false;}
      if(iDrYELqOdx == true){iDrYELqOdx = false;}
      if(KMHqFoDJZg == true){KMHqFoDJZg = false;}
      if(htzQoImHrf == true){htzQoImHrf = false;}
      if(aRsxXQHmsp == true){aRsxXQHmsp = false;}
      if(ZwbDutYmge == true){ZwbDutYmge = false;}
      if(pigjznEaiw == true){pigjznEaiw = false;}
      if(YiWyVsTJSo == true){YiWyVsTJSo = false;}
      if(hPPjHlSuVu == true){hPPjHlSuVu = false;}
      if(jAaNprkJyi == true){jAaNprkJyi = false;}
      if(LfExQpZdgB == true){LfExQpZdgB = false;}
      if(ZOTqwZSwbN == true){ZOTqwZSwbN = false;}
      if(VJFnLYHIId == true){VJFnLYHIId = false;}
      if(HKLjcCLSSQ == true){HKLjcCLSSQ = false;}
      if(LnNTUUfjQP == true){LnNTUUfjQP = false;}
      if(ZogkNCaPkr == true){ZogkNCaPkr = false;}
      if(hQVDtPCjNt == true){hQVDtPCjNt = false;}
      if(NzcLBhukSp == true){NzcLBhukSp = false;}
      if(rXqrEScaVZ == true){rXqrEScaVZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZAOREQWTH
{ 
  void PDSeiHcAYP()
  { 
      bool XqOWDGLrTx = false;
      bool LlmAPpUWnG = false;
      bool JEAxQkFeiD = false;
      bool jNBqukLTnd = false;
      bool OHLwnIBdUt = false;
      bool VBTVxSqRFS = false;
      bool AfJPNykuFd = false;
      bool dBhJqCsEJH = false;
      bool ibJohhsftb = false;
      bool ttNUchyuio = false;
      bool XGXqPTSJdu = false;
      bool YmHxjYVUhe = false;
      bool EEBdijnNgI = false;
      bool EyUUjbDSYN = false;
      bool OjByCHmPkE = false;
      bool LcNDjSFtHf = false;
      bool fFcVqaRmNH = false;
      bool UDuTQUDCab = false;
      bool wXbbwajRjQ = false;
      bool WJLshJGfHa = false;
      string PsUmtUaJUz;
      string gVaIlPXlKA;
      string SAHZoCoAgs;
      string LKjuCYXqBJ;
      string zwIAYVjJHx;
      string lWkBEOltyr;
      string fabbmVkeFN;
      string qgjAAVrHBS;
      string ReriGoYhqn;
      string ldrJdYTfMC;
      string kFDtFFlkAh;
      string VdrfZAhsUy;
      string wCnRaNnaVb;
      string BLtzhMaycB;
      string CngJRHkMjd;
      string paLOFhQlTr;
      string QLPYgKjsxM;
      string ZjPSuIVdzS;
      string caprkZAesA;
      string undkjqYHcH;
      if(PsUmtUaJUz == kFDtFFlkAh){XqOWDGLrTx = true;}
      else if(kFDtFFlkAh == PsUmtUaJUz){XGXqPTSJdu = true;}
      if(gVaIlPXlKA == VdrfZAhsUy){LlmAPpUWnG = true;}
      else if(VdrfZAhsUy == gVaIlPXlKA){YmHxjYVUhe = true;}
      if(SAHZoCoAgs == wCnRaNnaVb){JEAxQkFeiD = true;}
      else if(wCnRaNnaVb == SAHZoCoAgs){EEBdijnNgI = true;}
      if(LKjuCYXqBJ == BLtzhMaycB){jNBqukLTnd = true;}
      else if(BLtzhMaycB == LKjuCYXqBJ){EyUUjbDSYN = true;}
      if(zwIAYVjJHx == CngJRHkMjd){OHLwnIBdUt = true;}
      else if(CngJRHkMjd == zwIAYVjJHx){OjByCHmPkE = true;}
      if(lWkBEOltyr == paLOFhQlTr){VBTVxSqRFS = true;}
      else if(paLOFhQlTr == lWkBEOltyr){LcNDjSFtHf = true;}
      if(fabbmVkeFN == QLPYgKjsxM){AfJPNykuFd = true;}
      else if(QLPYgKjsxM == fabbmVkeFN){fFcVqaRmNH = true;}
      if(qgjAAVrHBS == ZjPSuIVdzS){dBhJqCsEJH = true;}
      if(ReriGoYhqn == caprkZAesA){ibJohhsftb = true;}
      if(ldrJdYTfMC == undkjqYHcH){ttNUchyuio = true;}
      while(ZjPSuIVdzS == qgjAAVrHBS){UDuTQUDCab = true;}
      while(caprkZAesA == caprkZAesA){wXbbwajRjQ = true;}
      while(undkjqYHcH == undkjqYHcH){WJLshJGfHa = true;}
      if(XqOWDGLrTx == true){XqOWDGLrTx = false;}
      if(LlmAPpUWnG == true){LlmAPpUWnG = false;}
      if(JEAxQkFeiD == true){JEAxQkFeiD = false;}
      if(jNBqukLTnd == true){jNBqukLTnd = false;}
      if(OHLwnIBdUt == true){OHLwnIBdUt = false;}
      if(VBTVxSqRFS == true){VBTVxSqRFS = false;}
      if(AfJPNykuFd == true){AfJPNykuFd = false;}
      if(dBhJqCsEJH == true){dBhJqCsEJH = false;}
      if(ibJohhsftb == true){ibJohhsftb = false;}
      if(ttNUchyuio == true){ttNUchyuio = false;}
      if(XGXqPTSJdu == true){XGXqPTSJdu = false;}
      if(YmHxjYVUhe == true){YmHxjYVUhe = false;}
      if(EEBdijnNgI == true){EEBdijnNgI = false;}
      if(EyUUjbDSYN == true){EyUUjbDSYN = false;}
      if(OjByCHmPkE == true){OjByCHmPkE = false;}
      if(LcNDjSFtHf == true){LcNDjSFtHf = false;}
      if(fFcVqaRmNH == true){fFcVqaRmNH = false;}
      if(UDuTQUDCab == true){UDuTQUDCab = false;}
      if(wXbbwajRjQ == true){wXbbwajRjQ = false;}
      if(WJLshJGfHa == true){WJLshJGfHa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQNBTHWFZW
{ 
  void SYCrPqhpKW()
  { 
      bool dzXDGZyiKi = false;
      bool aohGXmLgdq = false;
      bool NLbyxkDqRH = false;
      bool SenQqjEWwV = false;
      bool ThrxKSOXLG = false;
      bool hKHWRSWYFU = false;
      bool WHQDQuAROm = false;
      bool hnkHXeSdnd = false;
      bool WfeLYHXRzY = false;
      bool MfRazLRogP = false;
      bool RxJXYtZzyl = false;
      bool zrkayqbFdI = false;
      bool WiSpZBWJIL = false;
      bool NdxXMYVHme = false;
      bool hXSMYTtpbH = false;
      bool jLKYrieTyW = false;
      bool XPpmYVuNOY = false;
      bool UUSzZzQFQF = false;
      bool HfhAbBTYec = false;
      bool tCIQHSgfmD = false;
      string sdQAcZJWAP;
      string IpMhqLsAGl;
      string YYqbmxFWSU;
      string cSWIXHdjyR;
      string jsugVnYtZe;
      string JZPghUmnNf;
      string UlDeloSDJi;
      string gICoCfcJGy;
      string XLxnKDCpaC;
      string UpWRxxoPuf;
      string UVjpxBWaeB;
      string rchOIIoPUh;
      string lccGNqkjqE;
      string qMOZdBaGpJ;
      string gbLYKrHIJn;
      string IYuMsrsdbG;
      string PljZKeNIkG;
      string hhZLBKQDuV;
      string icaCwSRCfl;
      string IwdistrkOe;
      if(sdQAcZJWAP == UVjpxBWaeB){dzXDGZyiKi = true;}
      else if(UVjpxBWaeB == sdQAcZJWAP){RxJXYtZzyl = true;}
      if(IpMhqLsAGl == rchOIIoPUh){aohGXmLgdq = true;}
      else if(rchOIIoPUh == IpMhqLsAGl){zrkayqbFdI = true;}
      if(YYqbmxFWSU == lccGNqkjqE){NLbyxkDqRH = true;}
      else if(lccGNqkjqE == YYqbmxFWSU){WiSpZBWJIL = true;}
      if(cSWIXHdjyR == qMOZdBaGpJ){SenQqjEWwV = true;}
      else if(qMOZdBaGpJ == cSWIXHdjyR){NdxXMYVHme = true;}
      if(jsugVnYtZe == gbLYKrHIJn){ThrxKSOXLG = true;}
      else if(gbLYKrHIJn == jsugVnYtZe){hXSMYTtpbH = true;}
      if(JZPghUmnNf == IYuMsrsdbG){hKHWRSWYFU = true;}
      else if(IYuMsrsdbG == JZPghUmnNf){jLKYrieTyW = true;}
      if(UlDeloSDJi == PljZKeNIkG){WHQDQuAROm = true;}
      else if(PljZKeNIkG == UlDeloSDJi){XPpmYVuNOY = true;}
      if(gICoCfcJGy == hhZLBKQDuV){hnkHXeSdnd = true;}
      if(XLxnKDCpaC == icaCwSRCfl){WfeLYHXRzY = true;}
      if(UpWRxxoPuf == IwdistrkOe){MfRazLRogP = true;}
      while(hhZLBKQDuV == gICoCfcJGy){UUSzZzQFQF = true;}
      while(icaCwSRCfl == icaCwSRCfl){HfhAbBTYec = true;}
      while(IwdistrkOe == IwdistrkOe){tCIQHSgfmD = true;}
      if(dzXDGZyiKi == true){dzXDGZyiKi = false;}
      if(aohGXmLgdq == true){aohGXmLgdq = false;}
      if(NLbyxkDqRH == true){NLbyxkDqRH = false;}
      if(SenQqjEWwV == true){SenQqjEWwV = false;}
      if(ThrxKSOXLG == true){ThrxKSOXLG = false;}
      if(hKHWRSWYFU == true){hKHWRSWYFU = false;}
      if(WHQDQuAROm == true){WHQDQuAROm = false;}
      if(hnkHXeSdnd == true){hnkHXeSdnd = false;}
      if(WfeLYHXRzY == true){WfeLYHXRzY = false;}
      if(MfRazLRogP == true){MfRazLRogP = false;}
      if(RxJXYtZzyl == true){RxJXYtZzyl = false;}
      if(zrkayqbFdI == true){zrkayqbFdI = false;}
      if(WiSpZBWJIL == true){WiSpZBWJIL = false;}
      if(NdxXMYVHme == true){NdxXMYVHme = false;}
      if(hXSMYTtpbH == true){hXSMYTtpbH = false;}
      if(jLKYrieTyW == true){jLKYrieTyW = false;}
      if(XPpmYVuNOY == true){XPpmYVuNOY = false;}
      if(UUSzZzQFQF == true){UUSzZzQFQF = false;}
      if(HfhAbBTYec == true){HfhAbBTYec = false;}
      if(tCIQHSgfmD == true){tCIQHSgfmD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PPGOMGSTJX
{ 
  void oKxyQTGydt()
  { 
      bool XYAKRJJczM = false;
      bool WrFhsIkltW = false;
      bool tTMiaqgNVH = false;
      bool WkTftxFpOW = false;
      bool kSBcpgOZFf = false;
      bool bGDDNDLRia = false;
      bool cuHqplXZnw = false;
      bool CuWWkbSjrt = false;
      bool bHIofPgPSp = false;
      bool knGntoKKmE = false;
      bool IolJdgjfSk = false;
      bool kaYozVmSLZ = false;
      bool EIGxKOoicu = false;
      bool RHxnklVyLy = false;
      bool fBxhFJPQoY = false;
      bool CrzMzAiozP = false;
      bool rACWTcdjEM = false;
      bool znGMtDKXqA = false;
      bool yXtEsYIkoj = false;
      bool DgzwGeyZOb = false;
      string pimoYPJkzE;
      string GNnzpkkHtC;
      string McbuoZqkiM;
      string hmWZlroQWd;
      string WypNXFntMI;
      string niunxNGrAy;
      string YXBmVTqOMy;
      string uUjQfOmOWi;
      string lxYaXzqhbY;
      string kxPXFywCrE;
      string OZhOMTyeIi;
      string arVRMazZOW;
      string bImmMyELLg;
      string RjWRTMPJNE;
      string AMZrysbyLd;
      string zVnVbGmtBO;
      string OlTbRpUDxA;
      string LoMKVPitnS;
      string VGAgguuBpN;
      string ZUIyoNsxaH;
      if(pimoYPJkzE == OZhOMTyeIi){XYAKRJJczM = true;}
      else if(OZhOMTyeIi == pimoYPJkzE){IolJdgjfSk = true;}
      if(GNnzpkkHtC == arVRMazZOW){WrFhsIkltW = true;}
      else if(arVRMazZOW == GNnzpkkHtC){kaYozVmSLZ = true;}
      if(McbuoZqkiM == bImmMyELLg){tTMiaqgNVH = true;}
      else if(bImmMyELLg == McbuoZqkiM){EIGxKOoicu = true;}
      if(hmWZlroQWd == RjWRTMPJNE){WkTftxFpOW = true;}
      else if(RjWRTMPJNE == hmWZlroQWd){RHxnklVyLy = true;}
      if(WypNXFntMI == AMZrysbyLd){kSBcpgOZFf = true;}
      else if(AMZrysbyLd == WypNXFntMI){fBxhFJPQoY = true;}
      if(niunxNGrAy == zVnVbGmtBO){bGDDNDLRia = true;}
      else if(zVnVbGmtBO == niunxNGrAy){CrzMzAiozP = true;}
      if(YXBmVTqOMy == OlTbRpUDxA){cuHqplXZnw = true;}
      else if(OlTbRpUDxA == YXBmVTqOMy){rACWTcdjEM = true;}
      if(uUjQfOmOWi == LoMKVPitnS){CuWWkbSjrt = true;}
      if(lxYaXzqhbY == VGAgguuBpN){bHIofPgPSp = true;}
      if(kxPXFywCrE == ZUIyoNsxaH){knGntoKKmE = true;}
      while(LoMKVPitnS == uUjQfOmOWi){znGMtDKXqA = true;}
      while(VGAgguuBpN == VGAgguuBpN){yXtEsYIkoj = true;}
      while(ZUIyoNsxaH == ZUIyoNsxaH){DgzwGeyZOb = true;}
      if(XYAKRJJczM == true){XYAKRJJczM = false;}
      if(WrFhsIkltW == true){WrFhsIkltW = false;}
      if(tTMiaqgNVH == true){tTMiaqgNVH = false;}
      if(WkTftxFpOW == true){WkTftxFpOW = false;}
      if(kSBcpgOZFf == true){kSBcpgOZFf = false;}
      if(bGDDNDLRia == true){bGDDNDLRia = false;}
      if(cuHqplXZnw == true){cuHqplXZnw = false;}
      if(CuWWkbSjrt == true){CuWWkbSjrt = false;}
      if(bHIofPgPSp == true){bHIofPgPSp = false;}
      if(knGntoKKmE == true){knGntoKKmE = false;}
      if(IolJdgjfSk == true){IolJdgjfSk = false;}
      if(kaYozVmSLZ == true){kaYozVmSLZ = false;}
      if(EIGxKOoicu == true){EIGxKOoicu = false;}
      if(RHxnklVyLy == true){RHxnklVyLy = false;}
      if(fBxhFJPQoY == true){fBxhFJPQoY = false;}
      if(CrzMzAiozP == true){CrzMzAiozP = false;}
      if(rACWTcdjEM == true){rACWTcdjEM = false;}
      if(znGMtDKXqA == true){znGMtDKXqA = false;}
      if(yXtEsYIkoj == true){yXtEsYIkoj = false;}
      if(DgzwGeyZOb == true){DgzwGeyZOb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYHNWFQMMG
{ 
  void jMmXpznrpO()
  { 
      bool wxkxcWzMur = false;
      bool StMrZSTdFd = false;
      bool fnMsuTPFaf = false;
      bool gWnmojwQgl = false;
      bool VttrAwOSIn = false;
      bool RTVdtIkqCJ = false;
      bool HtlPLuGZDo = false;
      bool VCxTHksUsy = false;
      bool ExwmNMAJsf = false;
      bool zFOWdbIefE = false;
      bool poOSRPWCWI = false;
      bool OQyDFJxyBy = false;
      bool uwfWoQmZof = false;
      bool bOnnIOhcUx = false;
      bool pymjRiGKRU = false;
      bool dJchJsIrdA = false;
      bool bwMqgzbKup = false;
      bool aTdDIwJwEG = false;
      bool KcIUBSkGdO = false;
      bool FozTUsluDR = false;
      string ZXWuAjioiZ;
      string TIZDJdVIfe;
      string uAoTDAgnlD;
      string loFCapCpFZ;
      string JUOmUKUcJL;
      string NkdrjZiDrA;
      string CuDemdCXbS;
      string beDGVakCys;
      string fDeZpBLMRB;
      string HzyEWOQizp;
      string HxBpjhgXWJ;
      string ngEzUyPdol;
      string SoFaLbgyiH;
      string JBCHkhCopH;
      string TmpIMZtzjY;
      string ymtMXRqadH;
      string AhoOAmdwNl;
      string uamgReywNk;
      string hhOKIVHojT;
      string qbKhGlybIZ;
      if(ZXWuAjioiZ == HxBpjhgXWJ){wxkxcWzMur = true;}
      else if(HxBpjhgXWJ == ZXWuAjioiZ){poOSRPWCWI = true;}
      if(TIZDJdVIfe == ngEzUyPdol){StMrZSTdFd = true;}
      else if(ngEzUyPdol == TIZDJdVIfe){OQyDFJxyBy = true;}
      if(uAoTDAgnlD == SoFaLbgyiH){fnMsuTPFaf = true;}
      else if(SoFaLbgyiH == uAoTDAgnlD){uwfWoQmZof = true;}
      if(loFCapCpFZ == JBCHkhCopH){gWnmojwQgl = true;}
      else if(JBCHkhCopH == loFCapCpFZ){bOnnIOhcUx = true;}
      if(JUOmUKUcJL == TmpIMZtzjY){VttrAwOSIn = true;}
      else if(TmpIMZtzjY == JUOmUKUcJL){pymjRiGKRU = true;}
      if(NkdrjZiDrA == ymtMXRqadH){RTVdtIkqCJ = true;}
      else if(ymtMXRqadH == NkdrjZiDrA){dJchJsIrdA = true;}
      if(CuDemdCXbS == AhoOAmdwNl){HtlPLuGZDo = true;}
      else if(AhoOAmdwNl == CuDemdCXbS){bwMqgzbKup = true;}
      if(beDGVakCys == uamgReywNk){VCxTHksUsy = true;}
      if(fDeZpBLMRB == hhOKIVHojT){ExwmNMAJsf = true;}
      if(HzyEWOQizp == qbKhGlybIZ){zFOWdbIefE = true;}
      while(uamgReywNk == beDGVakCys){aTdDIwJwEG = true;}
      while(hhOKIVHojT == hhOKIVHojT){KcIUBSkGdO = true;}
      while(qbKhGlybIZ == qbKhGlybIZ){FozTUsluDR = true;}
      if(wxkxcWzMur == true){wxkxcWzMur = false;}
      if(StMrZSTdFd == true){StMrZSTdFd = false;}
      if(fnMsuTPFaf == true){fnMsuTPFaf = false;}
      if(gWnmojwQgl == true){gWnmojwQgl = false;}
      if(VttrAwOSIn == true){VttrAwOSIn = false;}
      if(RTVdtIkqCJ == true){RTVdtIkqCJ = false;}
      if(HtlPLuGZDo == true){HtlPLuGZDo = false;}
      if(VCxTHksUsy == true){VCxTHksUsy = false;}
      if(ExwmNMAJsf == true){ExwmNMAJsf = false;}
      if(zFOWdbIefE == true){zFOWdbIefE = false;}
      if(poOSRPWCWI == true){poOSRPWCWI = false;}
      if(OQyDFJxyBy == true){OQyDFJxyBy = false;}
      if(uwfWoQmZof == true){uwfWoQmZof = false;}
      if(bOnnIOhcUx == true){bOnnIOhcUx = false;}
      if(pymjRiGKRU == true){pymjRiGKRU = false;}
      if(dJchJsIrdA == true){dJchJsIrdA = false;}
      if(bwMqgzbKup == true){bwMqgzbKup = false;}
      if(aTdDIwJwEG == true){aTdDIwJwEG = false;}
      if(KcIUBSkGdO == true){KcIUBSkGdO = false;}
      if(FozTUsluDR == true){FozTUsluDR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RAQCUWDMQV
{ 
  void NuSLdYQIWZ()
  { 
      bool sPZwFxEzNE = false;
      bool NKhHrWHSqP = false;
      bool LPLqiLWYMD = false;
      bool RnUtlFgkfN = false;
      bool uLdHgORwQe = false;
      bool ONcPKcDiNs = false;
      bool ZflKlZonUl = false;
      bool oWlcUAlDJU = false;
      bool taHgoDLFiI = false;
      bool CxXmnOYTVH = false;
      bool YdaeoraztJ = false;
      bool qAZszzYEUh = false;
      bool NjEMjqyzoG = false;
      bool bShCuQAcrw = false;
      bool bLKZRBXemn = false;
      bool oTymsnZOtx = false;
      bool sbJnhYRWxi = false;
      bool zwMXFBZduh = false;
      bool TTLBQHTtIH = false;
      bool pkhtDABVrs = false;
      string GMEusYfFuX;
      string QRhTPweVVr;
      string cZMRTDKDDR;
      string xkYjVpMsmp;
      string RuoDRwHFsH;
      string kJpNjgzlbo;
      string ObCcaerxyY;
      string ilifZgkJAW;
      string uEKufmuLzo;
      string qZRxbpsLbl;
      string EKHTXzaJmD;
      string wolEsJQGwm;
      string jgxIgJUkEj;
      string mYgOSkxpXg;
      string MlXwsBmMDR;
      string YmOoCWMymO;
      string eoFDPWIXlH;
      string LahPayIBPe;
      string VHglLzKrLu;
      string YzDJCWfUfV;
      if(GMEusYfFuX == EKHTXzaJmD){sPZwFxEzNE = true;}
      else if(EKHTXzaJmD == GMEusYfFuX){YdaeoraztJ = true;}
      if(QRhTPweVVr == wolEsJQGwm){NKhHrWHSqP = true;}
      else if(wolEsJQGwm == QRhTPweVVr){qAZszzYEUh = true;}
      if(cZMRTDKDDR == jgxIgJUkEj){LPLqiLWYMD = true;}
      else if(jgxIgJUkEj == cZMRTDKDDR){NjEMjqyzoG = true;}
      if(xkYjVpMsmp == mYgOSkxpXg){RnUtlFgkfN = true;}
      else if(mYgOSkxpXg == xkYjVpMsmp){bShCuQAcrw = true;}
      if(RuoDRwHFsH == MlXwsBmMDR){uLdHgORwQe = true;}
      else if(MlXwsBmMDR == RuoDRwHFsH){bLKZRBXemn = true;}
      if(kJpNjgzlbo == YmOoCWMymO){ONcPKcDiNs = true;}
      else if(YmOoCWMymO == kJpNjgzlbo){oTymsnZOtx = true;}
      if(ObCcaerxyY == eoFDPWIXlH){ZflKlZonUl = true;}
      else if(eoFDPWIXlH == ObCcaerxyY){sbJnhYRWxi = true;}
      if(ilifZgkJAW == LahPayIBPe){oWlcUAlDJU = true;}
      if(uEKufmuLzo == VHglLzKrLu){taHgoDLFiI = true;}
      if(qZRxbpsLbl == YzDJCWfUfV){CxXmnOYTVH = true;}
      while(LahPayIBPe == ilifZgkJAW){zwMXFBZduh = true;}
      while(VHglLzKrLu == VHglLzKrLu){TTLBQHTtIH = true;}
      while(YzDJCWfUfV == YzDJCWfUfV){pkhtDABVrs = true;}
      if(sPZwFxEzNE == true){sPZwFxEzNE = false;}
      if(NKhHrWHSqP == true){NKhHrWHSqP = false;}
      if(LPLqiLWYMD == true){LPLqiLWYMD = false;}
      if(RnUtlFgkfN == true){RnUtlFgkfN = false;}
      if(uLdHgORwQe == true){uLdHgORwQe = false;}
      if(ONcPKcDiNs == true){ONcPKcDiNs = false;}
      if(ZflKlZonUl == true){ZflKlZonUl = false;}
      if(oWlcUAlDJU == true){oWlcUAlDJU = false;}
      if(taHgoDLFiI == true){taHgoDLFiI = false;}
      if(CxXmnOYTVH == true){CxXmnOYTVH = false;}
      if(YdaeoraztJ == true){YdaeoraztJ = false;}
      if(qAZszzYEUh == true){qAZszzYEUh = false;}
      if(NjEMjqyzoG == true){NjEMjqyzoG = false;}
      if(bShCuQAcrw == true){bShCuQAcrw = false;}
      if(bLKZRBXemn == true){bLKZRBXemn = false;}
      if(oTymsnZOtx == true){oTymsnZOtx = false;}
      if(sbJnhYRWxi == true){sbJnhYRWxi = false;}
      if(zwMXFBZduh == true){zwMXFBZduh = false;}
      if(TTLBQHTtIH == true){TTLBQHTtIH = false;}
      if(pkhtDABVrs == true){pkhtDABVrs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCPGHSKAXI
{ 
  void yFOMwoiYyE()
  { 
      bool kXGEaeauEc = false;
      bool IaAySMftGn = false;
      bool SBIXixxjEm = false;
      bool fmUsLWhczS = false;
      bool MqdFRLZKnL = false;
      bool YNXHbjOhUd = false;
      bool gppQxUFGmu = false;
      bool eDunaaWCGX = false;
      bool XmwsORPMRa = false;
      bool HAHVlVBMIx = false;
      bool FSWrfVSjgA = false;
      bool MMbxGstwCf = false;
      bool FsoLmeuZBF = false;
      bool ZKtIREPDMs = false;
      bool yefQOuYKPr = false;
      bool bEKcrLdLEB = false;
      bool ZsibZCRSeB = false;
      bool dpjJgZNXxr = false;
      bool FkKJcVzQQG = false;
      bool aEzKSEwEpL = false;
      string rzcSlyZnqg;
      string RdIRAskLaR;
      string UpsEmdUqgQ;
      string jcASQsckgP;
      string gkCEWHUcWn;
      string uyFZPCFXfH;
      string dhGZwocpBG;
      string PzeLjjmohe;
      string IqUsVkWZCN;
      string mFFYlzecIh;
      string debPXuTtpf;
      string OQpAzmMMEK;
      string RDmmTJsGYj;
      string FKfzBdOFUa;
      string RcjWzVOFZz;
      string lRYxQaqnwN;
      string BMUFaEjqyV;
      string XHqcrnSQnx;
      string ungZymlihZ;
      string lZJGYEIeut;
      if(rzcSlyZnqg == debPXuTtpf){kXGEaeauEc = true;}
      else if(debPXuTtpf == rzcSlyZnqg){FSWrfVSjgA = true;}
      if(RdIRAskLaR == OQpAzmMMEK){IaAySMftGn = true;}
      else if(OQpAzmMMEK == RdIRAskLaR){MMbxGstwCf = true;}
      if(UpsEmdUqgQ == RDmmTJsGYj){SBIXixxjEm = true;}
      else if(RDmmTJsGYj == UpsEmdUqgQ){FsoLmeuZBF = true;}
      if(jcASQsckgP == FKfzBdOFUa){fmUsLWhczS = true;}
      else if(FKfzBdOFUa == jcASQsckgP){ZKtIREPDMs = true;}
      if(gkCEWHUcWn == RcjWzVOFZz){MqdFRLZKnL = true;}
      else if(RcjWzVOFZz == gkCEWHUcWn){yefQOuYKPr = true;}
      if(uyFZPCFXfH == lRYxQaqnwN){YNXHbjOhUd = true;}
      else if(lRYxQaqnwN == uyFZPCFXfH){bEKcrLdLEB = true;}
      if(dhGZwocpBG == BMUFaEjqyV){gppQxUFGmu = true;}
      else if(BMUFaEjqyV == dhGZwocpBG){ZsibZCRSeB = true;}
      if(PzeLjjmohe == XHqcrnSQnx){eDunaaWCGX = true;}
      if(IqUsVkWZCN == ungZymlihZ){XmwsORPMRa = true;}
      if(mFFYlzecIh == lZJGYEIeut){HAHVlVBMIx = true;}
      while(XHqcrnSQnx == PzeLjjmohe){dpjJgZNXxr = true;}
      while(ungZymlihZ == ungZymlihZ){FkKJcVzQQG = true;}
      while(lZJGYEIeut == lZJGYEIeut){aEzKSEwEpL = true;}
      if(kXGEaeauEc == true){kXGEaeauEc = false;}
      if(IaAySMftGn == true){IaAySMftGn = false;}
      if(SBIXixxjEm == true){SBIXixxjEm = false;}
      if(fmUsLWhczS == true){fmUsLWhczS = false;}
      if(MqdFRLZKnL == true){MqdFRLZKnL = false;}
      if(YNXHbjOhUd == true){YNXHbjOhUd = false;}
      if(gppQxUFGmu == true){gppQxUFGmu = false;}
      if(eDunaaWCGX == true){eDunaaWCGX = false;}
      if(XmwsORPMRa == true){XmwsORPMRa = false;}
      if(HAHVlVBMIx == true){HAHVlVBMIx = false;}
      if(FSWrfVSjgA == true){FSWrfVSjgA = false;}
      if(MMbxGstwCf == true){MMbxGstwCf = false;}
      if(FsoLmeuZBF == true){FsoLmeuZBF = false;}
      if(ZKtIREPDMs == true){ZKtIREPDMs = false;}
      if(yefQOuYKPr == true){yefQOuYKPr = false;}
      if(bEKcrLdLEB == true){bEKcrLdLEB = false;}
      if(ZsibZCRSeB == true){ZsibZCRSeB = false;}
      if(dpjJgZNXxr == true){dpjJgZNXxr = false;}
      if(FkKJcVzQQG == true){FkKJcVzQQG = false;}
      if(aEzKSEwEpL == true){aEzKSEwEpL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPUNJHVKHY
{ 
  void mSDaiGmoVp()
  { 
      bool IdTDOiYowS = false;
      bool fcmoJuRChi = false;
      bool nRVuqoUeES = false;
      bool syHyxxsQgq = false;
      bool ijASbikixn = false;
      bool zuFOaqIYMY = false;
      bool NsjdYgVnrL = false;
      bool CAVqAERDSH = false;
      bool EkhQSysrXG = false;
      bool oTEIcozVsu = false;
      bool NxqkkzZONV = false;
      bool YFGEUbKTKa = false;
      bool ncPkWhwNNK = false;
      bool FuJWtHtweT = false;
      bool YdeChiNznB = false;
      bool deLRHkgGOD = false;
      bool CMBCQduiKM = false;
      bool hOopCJxNCn = false;
      bool TwYLfZirPI = false;
      bool ZmgbRLcbkD = false;
      string aZCQOxROac;
      string fBJMxrkHDu;
      string RsgCOtsJsJ;
      string SYMPaGoCZR;
      string AKdgGnWcPB;
      string ZxHFQgrACU;
      string DIVRKGoskq;
      string ChhltHPAwZ;
      string WQsqjURGyt;
      string NozFOqoMWz;
      string zcqYzqPVKJ;
      string QqDcxlOdho;
      string nhtqcNicWC;
      string RDdwZtYUrr;
      string EwuocWkWHb;
      string cKdgKRhAwk;
      string ImyIqNNGDD;
      string NtlojrlFNG;
      string bMUuZHYwkI;
      string LXYGjRymyP;
      if(aZCQOxROac == zcqYzqPVKJ){IdTDOiYowS = true;}
      else if(zcqYzqPVKJ == aZCQOxROac){NxqkkzZONV = true;}
      if(fBJMxrkHDu == QqDcxlOdho){fcmoJuRChi = true;}
      else if(QqDcxlOdho == fBJMxrkHDu){YFGEUbKTKa = true;}
      if(RsgCOtsJsJ == nhtqcNicWC){nRVuqoUeES = true;}
      else if(nhtqcNicWC == RsgCOtsJsJ){ncPkWhwNNK = true;}
      if(SYMPaGoCZR == RDdwZtYUrr){syHyxxsQgq = true;}
      else if(RDdwZtYUrr == SYMPaGoCZR){FuJWtHtweT = true;}
      if(AKdgGnWcPB == EwuocWkWHb){ijASbikixn = true;}
      else if(EwuocWkWHb == AKdgGnWcPB){YdeChiNznB = true;}
      if(ZxHFQgrACU == cKdgKRhAwk){zuFOaqIYMY = true;}
      else if(cKdgKRhAwk == ZxHFQgrACU){deLRHkgGOD = true;}
      if(DIVRKGoskq == ImyIqNNGDD){NsjdYgVnrL = true;}
      else if(ImyIqNNGDD == DIVRKGoskq){CMBCQduiKM = true;}
      if(ChhltHPAwZ == NtlojrlFNG){CAVqAERDSH = true;}
      if(WQsqjURGyt == bMUuZHYwkI){EkhQSysrXG = true;}
      if(NozFOqoMWz == LXYGjRymyP){oTEIcozVsu = true;}
      while(NtlojrlFNG == ChhltHPAwZ){hOopCJxNCn = true;}
      while(bMUuZHYwkI == bMUuZHYwkI){TwYLfZirPI = true;}
      while(LXYGjRymyP == LXYGjRymyP){ZmgbRLcbkD = true;}
      if(IdTDOiYowS == true){IdTDOiYowS = false;}
      if(fcmoJuRChi == true){fcmoJuRChi = false;}
      if(nRVuqoUeES == true){nRVuqoUeES = false;}
      if(syHyxxsQgq == true){syHyxxsQgq = false;}
      if(ijASbikixn == true){ijASbikixn = false;}
      if(zuFOaqIYMY == true){zuFOaqIYMY = false;}
      if(NsjdYgVnrL == true){NsjdYgVnrL = false;}
      if(CAVqAERDSH == true){CAVqAERDSH = false;}
      if(EkhQSysrXG == true){EkhQSysrXG = false;}
      if(oTEIcozVsu == true){oTEIcozVsu = false;}
      if(NxqkkzZONV == true){NxqkkzZONV = false;}
      if(YFGEUbKTKa == true){YFGEUbKTKa = false;}
      if(ncPkWhwNNK == true){ncPkWhwNNK = false;}
      if(FuJWtHtweT == true){FuJWtHtweT = false;}
      if(YdeChiNznB == true){YdeChiNznB = false;}
      if(deLRHkgGOD == true){deLRHkgGOD = false;}
      if(CMBCQduiKM == true){CMBCQduiKM = false;}
      if(hOopCJxNCn == true){hOopCJxNCn = false;}
      if(TwYLfZirPI == true){TwYLfZirPI = false;}
      if(ZmgbRLcbkD == true){ZmgbRLcbkD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLYZDUEEID
{ 
  void iElxKgNhyS()
  { 
      bool KFWHNxQfEP = false;
      bool dHJQKOeYMa = false;
      bool XmXajMrcft = false;
      bool hEBJFeOPSM = false;
      bool IYdjnPagqP = false;
      bool xrGwZWhwWB = false;
      bool FnzJhYFzKe = false;
      bool AOGASzJmlT = false;
      bool lKkQwoyEjh = false;
      bool wSsRHTZTBO = false;
      bool KaVLOhlGda = false;
      bool NuJCOtCiMs = false;
      bool ZAPchgVnry = false;
      bool YpkWJLnYBO = false;
      bool CraJUBJpDN = false;
      bool RpGInJKsdh = false;
      bool MyNeBWJmsD = false;
      bool FcgyphZGHf = false;
      bool Wfkegiichz = false;
      bool AuuSCEeuHx = false;
      string exjaElWdms;
      string WOpgetIpOx;
      string pehpaGkrxP;
      string XZoAzYMdaL;
      string nBDxkoViiq;
      string hECdHzOtzx;
      string BdgXUwYphG;
      string gePCInakEk;
      string kCIGgTXLrz;
      string JSdcKJUfbn;
      string QfAcJCozUT;
      string XdoNMzVapB;
      string XNyiwOBmry;
      string SuIQUEBewe;
      string dYpYafdPPL;
      string ntpaPCgRgu;
      string ACGWAcUXsI;
      string xpdKWzXZHQ;
      string kkWgKYEhAS;
      string XjyBdbRSXy;
      if(exjaElWdms == QfAcJCozUT){KFWHNxQfEP = true;}
      else if(QfAcJCozUT == exjaElWdms){KaVLOhlGda = true;}
      if(WOpgetIpOx == XdoNMzVapB){dHJQKOeYMa = true;}
      else if(XdoNMzVapB == WOpgetIpOx){NuJCOtCiMs = true;}
      if(pehpaGkrxP == XNyiwOBmry){XmXajMrcft = true;}
      else if(XNyiwOBmry == pehpaGkrxP){ZAPchgVnry = true;}
      if(XZoAzYMdaL == SuIQUEBewe){hEBJFeOPSM = true;}
      else if(SuIQUEBewe == XZoAzYMdaL){YpkWJLnYBO = true;}
      if(nBDxkoViiq == dYpYafdPPL){IYdjnPagqP = true;}
      else if(dYpYafdPPL == nBDxkoViiq){CraJUBJpDN = true;}
      if(hECdHzOtzx == ntpaPCgRgu){xrGwZWhwWB = true;}
      else if(ntpaPCgRgu == hECdHzOtzx){RpGInJKsdh = true;}
      if(BdgXUwYphG == ACGWAcUXsI){FnzJhYFzKe = true;}
      else if(ACGWAcUXsI == BdgXUwYphG){MyNeBWJmsD = true;}
      if(gePCInakEk == xpdKWzXZHQ){AOGASzJmlT = true;}
      if(kCIGgTXLrz == kkWgKYEhAS){lKkQwoyEjh = true;}
      if(JSdcKJUfbn == XjyBdbRSXy){wSsRHTZTBO = true;}
      while(xpdKWzXZHQ == gePCInakEk){FcgyphZGHf = true;}
      while(kkWgKYEhAS == kkWgKYEhAS){Wfkegiichz = true;}
      while(XjyBdbRSXy == XjyBdbRSXy){AuuSCEeuHx = true;}
      if(KFWHNxQfEP == true){KFWHNxQfEP = false;}
      if(dHJQKOeYMa == true){dHJQKOeYMa = false;}
      if(XmXajMrcft == true){XmXajMrcft = false;}
      if(hEBJFeOPSM == true){hEBJFeOPSM = false;}
      if(IYdjnPagqP == true){IYdjnPagqP = false;}
      if(xrGwZWhwWB == true){xrGwZWhwWB = false;}
      if(FnzJhYFzKe == true){FnzJhYFzKe = false;}
      if(AOGASzJmlT == true){AOGASzJmlT = false;}
      if(lKkQwoyEjh == true){lKkQwoyEjh = false;}
      if(wSsRHTZTBO == true){wSsRHTZTBO = false;}
      if(KaVLOhlGda == true){KaVLOhlGda = false;}
      if(NuJCOtCiMs == true){NuJCOtCiMs = false;}
      if(ZAPchgVnry == true){ZAPchgVnry = false;}
      if(YpkWJLnYBO == true){YpkWJLnYBO = false;}
      if(CraJUBJpDN == true){CraJUBJpDN = false;}
      if(RpGInJKsdh == true){RpGInJKsdh = false;}
      if(MyNeBWJmsD == true){MyNeBWJmsD = false;}
      if(FcgyphZGHf == true){FcgyphZGHf = false;}
      if(Wfkegiichz == true){Wfkegiichz = false;}
      if(AuuSCEeuHx == true){AuuSCEeuHx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MXVCHXMBIL
{ 
  void HTsIkBsqQf()
  { 
      bool bQBuDRVhTW = false;
      bool lZuHOsOIJX = false;
      bool NHxblGgcDJ = false;
      bool uLpLXeYYYq = false;
      bool YNDePMuAeH = false;
      bool JAeSOUSZJx = false;
      bool jsdKbZjjij = false;
      bool ToiSzADRMY = false;
      bool LfyuAtgWxD = false;
      bool LzPbGeisDo = false;
      bool cKQtnTRLTN = false;
      bool QANjlDtiKg = false;
      bool sMmeYUYGLT = false;
      bool QKOWwAPDHf = false;
      bool cUDimKlfpD = false;
      bool kAhVuQXkVT = false;
      bool uKzzwFlpnk = false;
      bool npaeEYIDrN = false;
      bool isQIiQcrae = false;
      bool bdhnkRUDlh = false;
      string NCLTJLGruG;
      string ltnWFTzclf;
      string abeiUyCSsZ;
      string jdzfRjSuyi;
      string CSgNhnGQkU;
      string dDTKOlWcyK;
      string JnyUWIuIFU;
      string ADdDcHtRBg;
      string rkgXugKnQe;
      string MpxnYNTLqY;
      string syKQUaZPgG;
      string rFaRSXGaYo;
      string yGqaHKGpdP;
      string nhZbnsaQDU;
      string HtGJlHOeUB;
      string HslBalGjIJ;
      string TikRSJeydY;
      string xpWEhDAgnA;
      string uaUcIuuXBB;
      string mpIsAXInqc;
      if(NCLTJLGruG == syKQUaZPgG){bQBuDRVhTW = true;}
      else if(syKQUaZPgG == NCLTJLGruG){cKQtnTRLTN = true;}
      if(ltnWFTzclf == rFaRSXGaYo){lZuHOsOIJX = true;}
      else if(rFaRSXGaYo == ltnWFTzclf){QANjlDtiKg = true;}
      if(abeiUyCSsZ == yGqaHKGpdP){NHxblGgcDJ = true;}
      else if(yGqaHKGpdP == abeiUyCSsZ){sMmeYUYGLT = true;}
      if(jdzfRjSuyi == nhZbnsaQDU){uLpLXeYYYq = true;}
      else if(nhZbnsaQDU == jdzfRjSuyi){QKOWwAPDHf = true;}
      if(CSgNhnGQkU == HtGJlHOeUB){YNDePMuAeH = true;}
      else if(HtGJlHOeUB == CSgNhnGQkU){cUDimKlfpD = true;}
      if(dDTKOlWcyK == HslBalGjIJ){JAeSOUSZJx = true;}
      else if(HslBalGjIJ == dDTKOlWcyK){kAhVuQXkVT = true;}
      if(JnyUWIuIFU == TikRSJeydY){jsdKbZjjij = true;}
      else if(TikRSJeydY == JnyUWIuIFU){uKzzwFlpnk = true;}
      if(ADdDcHtRBg == xpWEhDAgnA){ToiSzADRMY = true;}
      if(rkgXugKnQe == uaUcIuuXBB){LfyuAtgWxD = true;}
      if(MpxnYNTLqY == mpIsAXInqc){LzPbGeisDo = true;}
      while(xpWEhDAgnA == ADdDcHtRBg){npaeEYIDrN = true;}
      while(uaUcIuuXBB == uaUcIuuXBB){isQIiQcrae = true;}
      while(mpIsAXInqc == mpIsAXInqc){bdhnkRUDlh = true;}
      if(bQBuDRVhTW == true){bQBuDRVhTW = false;}
      if(lZuHOsOIJX == true){lZuHOsOIJX = false;}
      if(NHxblGgcDJ == true){NHxblGgcDJ = false;}
      if(uLpLXeYYYq == true){uLpLXeYYYq = false;}
      if(YNDePMuAeH == true){YNDePMuAeH = false;}
      if(JAeSOUSZJx == true){JAeSOUSZJx = false;}
      if(jsdKbZjjij == true){jsdKbZjjij = false;}
      if(ToiSzADRMY == true){ToiSzADRMY = false;}
      if(LfyuAtgWxD == true){LfyuAtgWxD = false;}
      if(LzPbGeisDo == true){LzPbGeisDo = false;}
      if(cKQtnTRLTN == true){cKQtnTRLTN = false;}
      if(QANjlDtiKg == true){QANjlDtiKg = false;}
      if(sMmeYUYGLT == true){sMmeYUYGLT = false;}
      if(QKOWwAPDHf == true){QKOWwAPDHf = false;}
      if(cUDimKlfpD == true){cUDimKlfpD = false;}
      if(kAhVuQXkVT == true){kAhVuQXkVT = false;}
      if(uKzzwFlpnk == true){uKzzwFlpnk = false;}
      if(npaeEYIDrN == true){npaeEYIDrN = false;}
      if(isQIiQcrae == true){isQIiQcrae = false;}
      if(bdhnkRUDlh == true){bdhnkRUDlh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWGCFDHEEM
{ 
  void WmRTYyiQEO()
  { 
      bool dtoGEKrleR = false;
      bool mJgunOEtCL = false;
      bool mHRNXQQqNT = false;
      bool LXYAiEZsxn = false;
      bool aoLTpUOoTu = false;
      bool ifnNUVbain = false;
      bool sAYLFOjgMj = false;
      bool nKwNjywyXC = false;
      bool BbXRjeiLeM = false;
      bool bzJJtZPzNa = false;
      bool khciGYjZcW = false;
      bool YcCglRcGbZ = false;
      bool eXBzHoBlSK = false;
      bool hwkxRTznLL = false;
      bool uJiInzxcXc = false;
      bool wIXmuMfcbQ = false;
      bool WxGRnbrEOR = false;
      bool RotPeVorLI = false;
      bool rYOpNYYxCF = false;
      bool mVMtnxCQUL = false;
      string GyEHmhVQDg;
      string hsScnUApHN;
      string yzHJBBbiue;
      string amiYbtjFiW;
      string tFsrIQEUqS;
      string SUAegGptFk;
      string GmUXGuJtAs;
      string kuGjSsGPBk;
      string xGqbLGlDqV;
      string DoAxQHjVlM;
      string GKUyhXNPMn;
      string zarUnzusLz;
      string IFCeoutJTL;
      string Jkcodllstn;
      string rWqDVbxfIR;
      string MpJlDBIpIl;
      string dEwBdOyDqB;
      string MByXHlOyIM;
      string yOACySapkc;
      string dwkHJnZpYH;
      if(GyEHmhVQDg == GKUyhXNPMn){dtoGEKrleR = true;}
      else if(GKUyhXNPMn == GyEHmhVQDg){khciGYjZcW = true;}
      if(hsScnUApHN == zarUnzusLz){mJgunOEtCL = true;}
      else if(zarUnzusLz == hsScnUApHN){YcCglRcGbZ = true;}
      if(yzHJBBbiue == IFCeoutJTL){mHRNXQQqNT = true;}
      else if(IFCeoutJTL == yzHJBBbiue){eXBzHoBlSK = true;}
      if(amiYbtjFiW == Jkcodllstn){LXYAiEZsxn = true;}
      else if(Jkcodllstn == amiYbtjFiW){hwkxRTznLL = true;}
      if(tFsrIQEUqS == rWqDVbxfIR){aoLTpUOoTu = true;}
      else if(rWqDVbxfIR == tFsrIQEUqS){uJiInzxcXc = true;}
      if(SUAegGptFk == MpJlDBIpIl){ifnNUVbain = true;}
      else if(MpJlDBIpIl == SUAegGptFk){wIXmuMfcbQ = true;}
      if(GmUXGuJtAs == dEwBdOyDqB){sAYLFOjgMj = true;}
      else if(dEwBdOyDqB == GmUXGuJtAs){WxGRnbrEOR = true;}
      if(kuGjSsGPBk == MByXHlOyIM){nKwNjywyXC = true;}
      if(xGqbLGlDqV == yOACySapkc){BbXRjeiLeM = true;}
      if(DoAxQHjVlM == dwkHJnZpYH){bzJJtZPzNa = true;}
      while(MByXHlOyIM == kuGjSsGPBk){RotPeVorLI = true;}
      while(yOACySapkc == yOACySapkc){rYOpNYYxCF = true;}
      while(dwkHJnZpYH == dwkHJnZpYH){mVMtnxCQUL = true;}
      if(dtoGEKrleR == true){dtoGEKrleR = false;}
      if(mJgunOEtCL == true){mJgunOEtCL = false;}
      if(mHRNXQQqNT == true){mHRNXQQqNT = false;}
      if(LXYAiEZsxn == true){LXYAiEZsxn = false;}
      if(aoLTpUOoTu == true){aoLTpUOoTu = false;}
      if(ifnNUVbain == true){ifnNUVbain = false;}
      if(sAYLFOjgMj == true){sAYLFOjgMj = false;}
      if(nKwNjywyXC == true){nKwNjywyXC = false;}
      if(BbXRjeiLeM == true){BbXRjeiLeM = false;}
      if(bzJJtZPzNa == true){bzJJtZPzNa = false;}
      if(khciGYjZcW == true){khciGYjZcW = false;}
      if(YcCglRcGbZ == true){YcCglRcGbZ = false;}
      if(eXBzHoBlSK == true){eXBzHoBlSK = false;}
      if(hwkxRTznLL == true){hwkxRTznLL = false;}
      if(uJiInzxcXc == true){uJiInzxcXc = false;}
      if(wIXmuMfcbQ == true){wIXmuMfcbQ = false;}
      if(WxGRnbrEOR == true){WxGRnbrEOR = false;}
      if(RotPeVorLI == true){RotPeVorLI = false;}
      if(rYOpNYYxCF == true){rYOpNYYxCF = false;}
      if(mVMtnxCQUL == true){mVMtnxCQUL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTFFWADEKQ
{ 
  void AkTGjCPyFw()
  { 
      bool NAippzTqDp = false;
      bool bhTzsFsTyZ = false;
      bool HewuAoeubG = false;
      bool riqQxnUlMJ = false;
      bool mQDRlMrkoU = false;
      bool gKdmVhDmoB = false;
      bool UXOxxsqDBE = false;
      bool jGHolpbeIm = false;
      bool xsFGZhEEtO = false;
      bool jhwKnPBFTs = false;
      bool VojjkZCnAf = false;
      bool GXdCEbRHXP = false;
      bool nlIlUCJwBV = false;
      bool nVLORHJVVz = false;
      bool ePDOILDtGM = false;
      bool xthEFifxPi = false;
      bool QFmeqjMPjw = false;
      bool SwlXjXitdI = false;
      bool yOpoYtnGJh = false;
      bool bLFmhYcYXY = false;
      string xrGhOpAQZq;
      string nIpRqYEaoy;
      string UtPdiYjYix;
      string lxuOPEEDBZ;
      string AYJPZxKFIt;
      string HIfdhCcbyo;
      string GahcEpNbBm;
      string UBYOxwjAEl;
      string OdQopdRQfM;
      string bbELTZqgKj;
      string jhDVYFiQfl;
      string SbXLabKsma;
      string XwwoKrwNtX;
      string FCpTCfauPj;
      string uAjstzErkq;
      string OxtiMmkOKg;
      string JVWHgPlDJu;
      string BPdCfWLDtL;
      string nDbCIHIGHO;
      string tLjhaZdcMd;
      if(xrGhOpAQZq == jhDVYFiQfl){NAippzTqDp = true;}
      else if(jhDVYFiQfl == xrGhOpAQZq){VojjkZCnAf = true;}
      if(nIpRqYEaoy == SbXLabKsma){bhTzsFsTyZ = true;}
      else if(SbXLabKsma == nIpRqYEaoy){GXdCEbRHXP = true;}
      if(UtPdiYjYix == XwwoKrwNtX){HewuAoeubG = true;}
      else if(XwwoKrwNtX == UtPdiYjYix){nlIlUCJwBV = true;}
      if(lxuOPEEDBZ == FCpTCfauPj){riqQxnUlMJ = true;}
      else if(FCpTCfauPj == lxuOPEEDBZ){nVLORHJVVz = true;}
      if(AYJPZxKFIt == uAjstzErkq){mQDRlMrkoU = true;}
      else if(uAjstzErkq == AYJPZxKFIt){ePDOILDtGM = true;}
      if(HIfdhCcbyo == OxtiMmkOKg){gKdmVhDmoB = true;}
      else if(OxtiMmkOKg == HIfdhCcbyo){xthEFifxPi = true;}
      if(GahcEpNbBm == JVWHgPlDJu){UXOxxsqDBE = true;}
      else if(JVWHgPlDJu == GahcEpNbBm){QFmeqjMPjw = true;}
      if(UBYOxwjAEl == BPdCfWLDtL){jGHolpbeIm = true;}
      if(OdQopdRQfM == nDbCIHIGHO){xsFGZhEEtO = true;}
      if(bbELTZqgKj == tLjhaZdcMd){jhwKnPBFTs = true;}
      while(BPdCfWLDtL == UBYOxwjAEl){SwlXjXitdI = true;}
      while(nDbCIHIGHO == nDbCIHIGHO){yOpoYtnGJh = true;}
      while(tLjhaZdcMd == tLjhaZdcMd){bLFmhYcYXY = true;}
      if(NAippzTqDp == true){NAippzTqDp = false;}
      if(bhTzsFsTyZ == true){bhTzsFsTyZ = false;}
      if(HewuAoeubG == true){HewuAoeubG = false;}
      if(riqQxnUlMJ == true){riqQxnUlMJ = false;}
      if(mQDRlMrkoU == true){mQDRlMrkoU = false;}
      if(gKdmVhDmoB == true){gKdmVhDmoB = false;}
      if(UXOxxsqDBE == true){UXOxxsqDBE = false;}
      if(jGHolpbeIm == true){jGHolpbeIm = false;}
      if(xsFGZhEEtO == true){xsFGZhEEtO = false;}
      if(jhwKnPBFTs == true){jhwKnPBFTs = false;}
      if(VojjkZCnAf == true){VojjkZCnAf = false;}
      if(GXdCEbRHXP == true){GXdCEbRHXP = false;}
      if(nlIlUCJwBV == true){nlIlUCJwBV = false;}
      if(nVLORHJVVz == true){nVLORHJVVz = false;}
      if(ePDOILDtGM == true){ePDOILDtGM = false;}
      if(xthEFifxPi == true){xthEFifxPi = false;}
      if(QFmeqjMPjw == true){QFmeqjMPjw = false;}
      if(SwlXjXitdI == true){SwlXjXitdI = false;}
      if(yOpoYtnGJh == true){yOpoYtnGJh = false;}
      if(bLFmhYcYXY == true){bLFmhYcYXY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJAWURKRBH
{ 
  void OQCjguRXiW()
  { 
      bool PImpJcksPD = false;
      bool MATPMZOTcK = false;
      bool TRfCjtwInX = false;
      bool yTRnphVOEd = false;
      bool psonlVIPtG = false;
      bool MUZVKxckFP = false;
      bool fcFqErheZe = false;
      bool EAPyUacqPO = false;
      bool lgNgLctwcs = false;
      bool FkIoxMmxis = false;
      bool ncpPCMFaAj = false;
      bool TkUqczOXfb = false;
      bool ykCfYSqZAH = false;
      bool nfHVZJpyey = false;
      bool XSwsYTQRMy = false;
      bool yOQHuDaJpi = false;
      bool VearundyQT = false;
      bool IPshEfoJHF = false;
      bool CZNCJYOzaW = false;
      bool igIucrrDxk = false;
      string jawSMkCgoZ;
      string DJztXrLLSZ;
      string reDCHAuFVG;
      string NpUAxBhlkH;
      string fngXPfOomj;
      string IwonSEWtLM;
      string pxLiMMnyxW;
      string KZaLtEyfla;
      string kFSkyQBfgr;
      string dnaYQibyLC;
      string rPqPZhVctO;
      string GqHkbjdaju;
      string LIREsWzBtK;
      string bAUiiUOCKP;
      string uXlSklfoxf;
      string EBNPqiylWD;
      string iThilGWXCG;
      string VbPTAnWySG;
      string pJEOGalErz;
      string VbfHfboCfe;
      if(jawSMkCgoZ == rPqPZhVctO){PImpJcksPD = true;}
      else if(rPqPZhVctO == jawSMkCgoZ){ncpPCMFaAj = true;}
      if(DJztXrLLSZ == GqHkbjdaju){MATPMZOTcK = true;}
      else if(GqHkbjdaju == DJztXrLLSZ){TkUqczOXfb = true;}
      if(reDCHAuFVG == LIREsWzBtK){TRfCjtwInX = true;}
      else if(LIREsWzBtK == reDCHAuFVG){ykCfYSqZAH = true;}
      if(NpUAxBhlkH == bAUiiUOCKP){yTRnphVOEd = true;}
      else if(bAUiiUOCKP == NpUAxBhlkH){nfHVZJpyey = true;}
      if(fngXPfOomj == uXlSklfoxf){psonlVIPtG = true;}
      else if(uXlSklfoxf == fngXPfOomj){XSwsYTQRMy = true;}
      if(IwonSEWtLM == EBNPqiylWD){MUZVKxckFP = true;}
      else if(EBNPqiylWD == IwonSEWtLM){yOQHuDaJpi = true;}
      if(pxLiMMnyxW == iThilGWXCG){fcFqErheZe = true;}
      else if(iThilGWXCG == pxLiMMnyxW){VearundyQT = true;}
      if(KZaLtEyfla == VbPTAnWySG){EAPyUacqPO = true;}
      if(kFSkyQBfgr == pJEOGalErz){lgNgLctwcs = true;}
      if(dnaYQibyLC == VbfHfboCfe){FkIoxMmxis = true;}
      while(VbPTAnWySG == KZaLtEyfla){IPshEfoJHF = true;}
      while(pJEOGalErz == pJEOGalErz){CZNCJYOzaW = true;}
      while(VbfHfboCfe == VbfHfboCfe){igIucrrDxk = true;}
      if(PImpJcksPD == true){PImpJcksPD = false;}
      if(MATPMZOTcK == true){MATPMZOTcK = false;}
      if(TRfCjtwInX == true){TRfCjtwInX = false;}
      if(yTRnphVOEd == true){yTRnphVOEd = false;}
      if(psonlVIPtG == true){psonlVIPtG = false;}
      if(MUZVKxckFP == true){MUZVKxckFP = false;}
      if(fcFqErheZe == true){fcFqErheZe = false;}
      if(EAPyUacqPO == true){EAPyUacqPO = false;}
      if(lgNgLctwcs == true){lgNgLctwcs = false;}
      if(FkIoxMmxis == true){FkIoxMmxis = false;}
      if(ncpPCMFaAj == true){ncpPCMFaAj = false;}
      if(TkUqczOXfb == true){TkUqczOXfb = false;}
      if(ykCfYSqZAH == true){ykCfYSqZAH = false;}
      if(nfHVZJpyey == true){nfHVZJpyey = false;}
      if(XSwsYTQRMy == true){XSwsYTQRMy = false;}
      if(yOQHuDaJpi == true){yOQHuDaJpi = false;}
      if(VearundyQT == true){VearundyQT = false;}
      if(IPshEfoJHF == true){IPshEfoJHF = false;}
      if(CZNCJYOzaW == true){CZNCJYOzaW = false;}
      if(igIucrrDxk == true){igIucrrDxk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRUMKHNFFT
{ 
  void eOYGrgYpsR()
  { 
      bool bQTjnodhOn = false;
      bool EmOUUHGIiQ = false;
      bool uLobbftClq = false;
      bool xJdAhtEfxK = false;
      bool UuPhQbCGCy = false;
      bool wMYZZQbrHH = false;
      bool ubuXqtJNma = false;
      bool CaKYuzuGKA = false;
      bool dmzmtjjDaR = false;
      bool RLXpPszrqW = false;
      bool SnTawVCAeZ = false;
      bool UVhHdHbHcG = false;
      bool JFmUIpCUIB = false;
      bool ACPmhoTXqY = false;
      bool hjYAwwcPMH = false;
      bool RqPjMMBySF = false;
      bool SgqcZSGtZn = false;
      bool mDQDYZglYM = false;
      bool MlIBjIlfaU = false;
      bool nVFkFAruZd = false;
      string uHZJKnrISA;
      string ZcauWhOuyh;
      string WHJTxomyDd;
      string nLhaKwZRLm;
      string hlwpCaikic;
      string TycuCnyGLV;
      string BsEoLOuzka;
      string HwiKAjKSQW;
      string GBPZJphlYV;
      string xSFplohGem;
      string eizIVWPStR;
      string cepnOzcdeU;
      string gJaOcnprXL;
      string CEndqWBHEm;
      string aOqGsScRbl;
      string LDaJGVHjeg;
      string fWtiPXpLxq;
      string xVZrtRRUVK;
      string LYQlAzceWV;
      string PQbXGDUIqU;
      if(uHZJKnrISA == eizIVWPStR){bQTjnodhOn = true;}
      else if(eizIVWPStR == uHZJKnrISA){SnTawVCAeZ = true;}
      if(ZcauWhOuyh == cepnOzcdeU){EmOUUHGIiQ = true;}
      else if(cepnOzcdeU == ZcauWhOuyh){UVhHdHbHcG = true;}
      if(WHJTxomyDd == gJaOcnprXL){uLobbftClq = true;}
      else if(gJaOcnprXL == WHJTxomyDd){JFmUIpCUIB = true;}
      if(nLhaKwZRLm == CEndqWBHEm){xJdAhtEfxK = true;}
      else if(CEndqWBHEm == nLhaKwZRLm){ACPmhoTXqY = true;}
      if(hlwpCaikic == aOqGsScRbl){UuPhQbCGCy = true;}
      else if(aOqGsScRbl == hlwpCaikic){hjYAwwcPMH = true;}
      if(TycuCnyGLV == LDaJGVHjeg){wMYZZQbrHH = true;}
      else if(LDaJGVHjeg == TycuCnyGLV){RqPjMMBySF = true;}
      if(BsEoLOuzka == fWtiPXpLxq){ubuXqtJNma = true;}
      else if(fWtiPXpLxq == BsEoLOuzka){SgqcZSGtZn = true;}
      if(HwiKAjKSQW == xVZrtRRUVK){CaKYuzuGKA = true;}
      if(GBPZJphlYV == LYQlAzceWV){dmzmtjjDaR = true;}
      if(xSFplohGem == PQbXGDUIqU){RLXpPszrqW = true;}
      while(xVZrtRRUVK == HwiKAjKSQW){mDQDYZglYM = true;}
      while(LYQlAzceWV == LYQlAzceWV){MlIBjIlfaU = true;}
      while(PQbXGDUIqU == PQbXGDUIqU){nVFkFAruZd = true;}
      if(bQTjnodhOn == true){bQTjnodhOn = false;}
      if(EmOUUHGIiQ == true){EmOUUHGIiQ = false;}
      if(uLobbftClq == true){uLobbftClq = false;}
      if(xJdAhtEfxK == true){xJdAhtEfxK = false;}
      if(UuPhQbCGCy == true){UuPhQbCGCy = false;}
      if(wMYZZQbrHH == true){wMYZZQbrHH = false;}
      if(ubuXqtJNma == true){ubuXqtJNma = false;}
      if(CaKYuzuGKA == true){CaKYuzuGKA = false;}
      if(dmzmtjjDaR == true){dmzmtjjDaR = false;}
      if(RLXpPszrqW == true){RLXpPszrqW = false;}
      if(SnTawVCAeZ == true){SnTawVCAeZ = false;}
      if(UVhHdHbHcG == true){UVhHdHbHcG = false;}
      if(JFmUIpCUIB == true){JFmUIpCUIB = false;}
      if(ACPmhoTXqY == true){ACPmhoTXqY = false;}
      if(hjYAwwcPMH == true){hjYAwwcPMH = false;}
      if(RqPjMMBySF == true){RqPjMMBySF = false;}
      if(SgqcZSGtZn == true){SgqcZSGtZn = false;}
      if(mDQDYZglYM == true){mDQDYZglYM = false;}
      if(MlIBjIlfaU == true){MlIBjIlfaU = false;}
      if(nVFkFAruZd == true){nVFkFAruZd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HGGSXMEDIB
{ 
  void XLNnSsqqet()
  { 
      bool ZEIXsWHOCI = false;
      bool KPUXhwoISx = false;
      bool iMISjUrnlD = false;
      bool dXgUCkexLQ = false;
      bool BiojjcQthF = false;
      bool WpWlPMuomX = false;
      bool eTbzemiAVx = false;
      bool RqxCuzWYiH = false;
      bool DxFgfmAuEo = false;
      bool ooJmkgHpFx = false;
      bool tQYknesUpQ = false;
      bool oWGeUgOuSq = false;
      bool lmwfHbhJQO = false;
      bool qgTkNmYUrB = false;
      bool tfFmAShdRE = false;
      bool SLXNKGTscL = false;
      bool xiDaZIDURg = false;
      bool IsCQxGhIeo = false;
      bool sDrMueJFaH = false;
      bool SerfEKbdNr = false;
      string fnXBeKBDyD;
      string qVqseACnIH;
      string XQJpSTQrGq;
      string MalSeaSmNZ;
      string WAkunRJCOA;
      string JHzMAOeghK;
      string tIxHqPiXOE;
      string gPZijXfOCB;
      string JNdGgEbYSP;
      string ukECeNCdEY;
      string hknJSthQcb;
      string iPegBfeqal;
      string nJFzIuKWDV;
      string VBKcSXZTml;
      string WLwpffGWBz;
      string hLDRkXfnBW;
      string jKMGGgFBNc;
      string GLDnObNPTc;
      string omVEmJyrru;
      string rkSPBLypiy;
      if(fnXBeKBDyD == hknJSthQcb){ZEIXsWHOCI = true;}
      else if(hknJSthQcb == fnXBeKBDyD){tQYknesUpQ = true;}
      if(qVqseACnIH == iPegBfeqal){KPUXhwoISx = true;}
      else if(iPegBfeqal == qVqseACnIH){oWGeUgOuSq = true;}
      if(XQJpSTQrGq == nJFzIuKWDV){iMISjUrnlD = true;}
      else if(nJFzIuKWDV == XQJpSTQrGq){lmwfHbhJQO = true;}
      if(MalSeaSmNZ == VBKcSXZTml){dXgUCkexLQ = true;}
      else if(VBKcSXZTml == MalSeaSmNZ){qgTkNmYUrB = true;}
      if(WAkunRJCOA == WLwpffGWBz){BiojjcQthF = true;}
      else if(WLwpffGWBz == WAkunRJCOA){tfFmAShdRE = true;}
      if(JHzMAOeghK == hLDRkXfnBW){WpWlPMuomX = true;}
      else if(hLDRkXfnBW == JHzMAOeghK){SLXNKGTscL = true;}
      if(tIxHqPiXOE == jKMGGgFBNc){eTbzemiAVx = true;}
      else if(jKMGGgFBNc == tIxHqPiXOE){xiDaZIDURg = true;}
      if(gPZijXfOCB == GLDnObNPTc){RqxCuzWYiH = true;}
      if(JNdGgEbYSP == omVEmJyrru){DxFgfmAuEo = true;}
      if(ukECeNCdEY == rkSPBLypiy){ooJmkgHpFx = true;}
      while(GLDnObNPTc == gPZijXfOCB){IsCQxGhIeo = true;}
      while(omVEmJyrru == omVEmJyrru){sDrMueJFaH = true;}
      while(rkSPBLypiy == rkSPBLypiy){SerfEKbdNr = true;}
      if(ZEIXsWHOCI == true){ZEIXsWHOCI = false;}
      if(KPUXhwoISx == true){KPUXhwoISx = false;}
      if(iMISjUrnlD == true){iMISjUrnlD = false;}
      if(dXgUCkexLQ == true){dXgUCkexLQ = false;}
      if(BiojjcQthF == true){BiojjcQthF = false;}
      if(WpWlPMuomX == true){WpWlPMuomX = false;}
      if(eTbzemiAVx == true){eTbzemiAVx = false;}
      if(RqxCuzWYiH == true){RqxCuzWYiH = false;}
      if(DxFgfmAuEo == true){DxFgfmAuEo = false;}
      if(ooJmkgHpFx == true){ooJmkgHpFx = false;}
      if(tQYknesUpQ == true){tQYknesUpQ = false;}
      if(oWGeUgOuSq == true){oWGeUgOuSq = false;}
      if(lmwfHbhJQO == true){lmwfHbhJQO = false;}
      if(qgTkNmYUrB == true){qgTkNmYUrB = false;}
      if(tfFmAShdRE == true){tfFmAShdRE = false;}
      if(SLXNKGTscL == true){SLXNKGTscL = false;}
      if(xiDaZIDURg == true){xiDaZIDURg = false;}
      if(IsCQxGhIeo == true){IsCQxGhIeo = false;}
      if(sDrMueJFaH == true){sDrMueJFaH = false;}
      if(SerfEKbdNr == true){SerfEKbdNr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCHEVQVARF
{ 
  void QEegilHKaB()
  { 
      bool UZmJSdDmMA = false;
      bool IdbYIlVYRV = false;
      bool bXrwjrDiRQ = false;
      bool QCIeXdHgMr = false;
      bool XdruFrzWQb = false;
      bool KQcJyxhqYa = false;
      bool ZTUwjGUwAd = false;
      bool enLZxxfwpq = false;
      bool rfRoGzZyga = false;
      bool wPIlREJuLz = false;
      bool XDVlxVFCLA = false;
      bool QkBgisBeok = false;
      bool fWPZhOfZIs = false;
      bool njkpTnJfrj = false;
      bool tXlfJKObCY = false;
      bool CdFaSAnwEi = false;
      bool petSLgAKMt = false;
      bool iVmFqIjiQW = false;
      bool zDWiqKdKWS = false;
      bool ANaJsOdTTc = false;
      string SnrgHsuqGM;
      string pyVcklmEpP;
      string UMcntlzLaN;
      string FWxrDCLQiJ;
      string ZYkJbmMgpH;
      string tpEbfFLEmV;
      string tiQrHTBdYh;
      string ZVUgowbSLH;
      string YRVTSORUMy;
      string qGdNOpIrCI;
      string liIIgYUWlj;
      string csrfwcNwZr;
      string BfQaqTrHRy;
      string mjPDUoJNmt;
      string tuhbUyOxQl;
      string cMSKGGShRN;
      string fMEmwscnKH;
      string TzJfxGxnGr;
      string EtqfVaQEwO;
      string WawZNgptfa;
      if(SnrgHsuqGM == liIIgYUWlj){UZmJSdDmMA = true;}
      else if(liIIgYUWlj == SnrgHsuqGM){XDVlxVFCLA = true;}
      if(pyVcklmEpP == csrfwcNwZr){IdbYIlVYRV = true;}
      else if(csrfwcNwZr == pyVcklmEpP){QkBgisBeok = true;}
      if(UMcntlzLaN == BfQaqTrHRy){bXrwjrDiRQ = true;}
      else if(BfQaqTrHRy == UMcntlzLaN){fWPZhOfZIs = true;}
      if(FWxrDCLQiJ == mjPDUoJNmt){QCIeXdHgMr = true;}
      else if(mjPDUoJNmt == FWxrDCLQiJ){njkpTnJfrj = true;}
      if(ZYkJbmMgpH == tuhbUyOxQl){XdruFrzWQb = true;}
      else if(tuhbUyOxQl == ZYkJbmMgpH){tXlfJKObCY = true;}
      if(tpEbfFLEmV == cMSKGGShRN){KQcJyxhqYa = true;}
      else if(cMSKGGShRN == tpEbfFLEmV){CdFaSAnwEi = true;}
      if(tiQrHTBdYh == fMEmwscnKH){ZTUwjGUwAd = true;}
      else if(fMEmwscnKH == tiQrHTBdYh){petSLgAKMt = true;}
      if(ZVUgowbSLH == TzJfxGxnGr){enLZxxfwpq = true;}
      if(YRVTSORUMy == EtqfVaQEwO){rfRoGzZyga = true;}
      if(qGdNOpIrCI == WawZNgptfa){wPIlREJuLz = true;}
      while(TzJfxGxnGr == ZVUgowbSLH){iVmFqIjiQW = true;}
      while(EtqfVaQEwO == EtqfVaQEwO){zDWiqKdKWS = true;}
      while(WawZNgptfa == WawZNgptfa){ANaJsOdTTc = true;}
      if(UZmJSdDmMA == true){UZmJSdDmMA = false;}
      if(IdbYIlVYRV == true){IdbYIlVYRV = false;}
      if(bXrwjrDiRQ == true){bXrwjrDiRQ = false;}
      if(QCIeXdHgMr == true){QCIeXdHgMr = false;}
      if(XdruFrzWQb == true){XdruFrzWQb = false;}
      if(KQcJyxhqYa == true){KQcJyxhqYa = false;}
      if(ZTUwjGUwAd == true){ZTUwjGUwAd = false;}
      if(enLZxxfwpq == true){enLZxxfwpq = false;}
      if(rfRoGzZyga == true){rfRoGzZyga = false;}
      if(wPIlREJuLz == true){wPIlREJuLz = false;}
      if(XDVlxVFCLA == true){XDVlxVFCLA = false;}
      if(QkBgisBeok == true){QkBgisBeok = false;}
      if(fWPZhOfZIs == true){fWPZhOfZIs = false;}
      if(njkpTnJfrj == true){njkpTnJfrj = false;}
      if(tXlfJKObCY == true){tXlfJKObCY = false;}
      if(CdFaSAnwEi == true){CdFaSAnwEi = false;}
      if(petSLgAKMt == true){petSLgAKMt = false;}
      if(iVmFqIjiQW == true){iVmFqIjiQW = false;}
      if(zDWiqKdKWS == true){zDWiqKdKWS = false;}
      if(ANaJsOdTTc == true){ANaJsOdTTc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOWXTJHKZW
{ 
  void ebHiqthOit()
  { 
      bool ADQgxTKKOA = false;
      bool baAnmIBIeN = false;
      bool ZFFTeOrYhX = false;
      bool wluxdthwbU = false;
      bool WuXwpEswQe = false;
      bool BOzcItywCi = false;
      bool bkcpEpeCKs = false;
      bool aFgKqehIda = false;
      bool UuICWhmSoi = false;
      bool uktrrkRgrA = false;
      bool YplWDugnld = false;
      bool LoSaNgbZSW = false;
      bool CMNaxoKoSF = false;
      bool NBQdBdJlza = false;
      bool ByfLXGSSeK = false;
      bool JqNUxLcKZN = false;
      bool krVfPKYoZi = false;
      bool XparVEgBDq = false;
      bool WqJHwVmufo = false;
      bool ByLkpIbzuM = false;
      string FQhWermnjI;
      string uyKMkpYHxT;
      string SCWACrGNuP;
      string LCcljDKWkb;
      string DuRwmfKDVT;
      string LYhWlDshUl;
      string lYrUwsVYbg;
      string fCVUQXjaMV;
      string gCrbDlTFAg;
      string KbByodDxzt;
      string JlbonIDNGO;
      string SSVyFigQQK;
      string ZPXtVDBWel;
      string TmaSMtaDmu;
      string iFzkOrGCsF;
      string xmgoUsNgSj;
      string HfhTtfqDlL;
      string IccVaTQmfd;
      string xydYogGlxS;
      string ftkDmCXeqh;
      if(FQhWermnjI == JlbonIDNGO){ADQgxTKKOA = true;}
      else if(JlbonIDNGO == FQhWermnjI){YplWDugnld = true;}
      if(uyKMkpYHxT == SSVyFigQQK){baAnmIBIeN = true;}
      else if(SSVyFigQQK == uyKMkpYHxT){LoSaNgbZSW = true;}
      if(SCWACrGNuP == ZPXtVDBWel){ZFFTeOrYhX = true;}
      else if(ZPXtVDBWel == SCWACrGNuP){CMNaxoKoSF = true;}
      if(LCcljDKWkb == TmaSMtaDmu){wluxdthwbU = true;}
      else if(TmaSMtaDmu == LCcljDKWkb){NBQdBdJlza = true;}
      if(DuRwmfKDVT == iFzkOrGCsF){WuXwpEswQe = true;}
      else if(iFzkOrGCsF == DuRwmfKDVT){ByfLXGSSeK = true;}
      if(LYhWlDshUl == xmgoUsNgSj){BOzcItywCi = true;}
      else if(xmgoUsNgSj == LYhWlDshUl){JqNUxLcKZN = true;}
      if(lYrUwsVYbg == HfhTtfqDlL){bkcpEpeCKs = true;}
      else if(HfhTtfqDlL == lYrUwsVYbg){krVfPKYoZi = true;}
      if(fCVUQXjaMV == IccVaTQmfd){aFgKqehIda = true;}
      if(gCrbDlTFAg == xydYogGlxS){UuICWhmSoi = true;}
      if(KbByodDxzt == ftkDmCXeqh){uktrrkRgrA = true;}
      while(IccVaTQmfd == fCVUQXjaMV){XparVEgBDq = true;}
      while(xydYogGlxS == xydYogGlxS){WqJHwVmufo = true;}
      while(ftkDmCXeqh == ftkDmCXeqh){ByLkpIbzuM = true;}
      if(ADQgxTKKOA == true){ADQgxTKKOA = false;}
      if(baAnmIBIeN == true){baAnmIBIeN = false;}
      if(ZFFTeOrYhX == true){ZFFTeOrYhX = false;}
      if(wluxdthwbU == true){wluxdthwbU = false;}
      if(WuXwpEswQe == true){WuXwpEswQe = false;}
      if(BOzcItywCi == true){BOzcItywCi = false;}
      if(bkcpEpeCKs == true){bkcpEpeCKs = false;}
      if(aFgKqehIda == true){aFgKqehIda = false;}
      if(UuICWhmSoi == true){UuICWhmSoi = false;}
      if(uktrrkRgrA == true){uktrrkRgrA = false;}
      if(YplWDugnld == true){YplWDugnld = false;}
      if(LoSaNgbZSW == true){LoSaNgbZSW = false;}
      if(CMNaxoKoSF == true){CMNaxoKoSF = false;}
      if(NBQdBdJlza == true){NBQdBdJlza = false;}
      if(ByfLXGSSeK == true){ByfLXGSSeK = false;}
      if(JqNUxLcKZN == true){JqNUxLcKZN = false;}
      if(krVfPKYoZi == true){krVfPKYoZi = false;}
      if(XparVEgBDq == true){XparVEgBDq = false;}
      if(WqJHwVmufo == true){WqJHwVmufo = false;}
      if(ByLkpIbzuM == true){ByLkpIbzuM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZRWJYOFPZC
{ 
  void NmTKpukjSq()
  { 
      bool hfOcWueAUp = false;
      bool ylrxXmhlAS = false;
      bool hYxnkmLFdG = false;
      bool umCBGhlDUI = false;
      bool ynhFaslVaZ = false;
      bool DTkBsJhZrj = false;
      bool jZWNtLjpqp = false;
      bool BeRrUtprNq = false;
      bool ApeDDbBBHx = false;
      bool zLKjXYQTKP = false;
      bool JudjXXBsfz = false;
      bool SpMAjsuSKS = false;
      bool JhitqpThTu = false;
      bool cVgxhELtfe = false;
      bool ZIUIdIyKze = false;
      bool dxJqFaMjsh = false;
      bool ETYkVxIPRf = false;
      bool hAmesBNZPh = false;
      bool qJhoReMpqG = false;
      bool qbBxaGijlg = false;
      string qZUSaHzZZm;
      string ioYJTrONXa;
      string ETKZRmkZbK;
      string EAzObSzrmg;
      string kVAmKeEhkR;
      string oPDZqXPtAn;
      string WZyOhhpJhB;
      string rVZqpiSWOm;
      string iCoJUowZXE;
      string CEqzJLWkFc;
      string ntAjYToLiH;
      string EseNETjnsr;
      string kPldymeahe;
      string LgQlynCFjB;
      string zjpPzJYdto;
      string airNqYIWll;
      string nOdEwWbsOQ;
      string ReDqrBZVdn;
      string NBfrDcoDuZ;
      string feSyNkFlTb;
      if(qZUSaHzZZm == ntAjYToLiH){hfOcWueAUp = true;}
      else if(ntAjYToLiH == qZUSaHzZZm){JudjXXBsfz = true;}
      if(ioYJTrONXa == EseNETjnsr){ylrxXmhlAS = true;}
      else if(EseNETjnsr == ioYJTrONXa){SpMAjsuSKS = true;}
      if(ETKZRmkZbK == kPldymeahe){hYxnkmLFdG = true;}
      else if(kPldymeahe == ETKZRmkZbK){JhitqpThTu = true;}
      if(EAzObSzrmg == LgQlynCFjB){umCBGhlDUI = true;}
      else if(LgQlynCFjB == EAzObSzrmg){cVgxhELtfe = true;}
      if(kVAmKeEhkR == zjpPzJYdto){ynhFaslVaZ = true;}
      else if(zjpPzJYdto == kVAmKeEhkR){ZIUIdIyKze = true;}
      if(oPDZqXPtAn == airNqYIWll){DTkBsJhZrj = true;}
      else if(airNqYIWll == oPDZqXPtAn){dxJqFaMjsh = true;}
      if(WZyOhhpJhB == nOdEwWbsOQ){jZWNtLjpqp = true;}
      else if(nOdEwWbsOQ == WZyOhhpJhB){ETYkVxIPRf = true;}
      if(rVZqpiSWOm == ReDqrBZVdn){BeRrUtprNq = true;}
      if(iCoJUowZXE == NBfrDcoDuZ){ApeDDbBBHx = true;}
      if(CEqzJLWkFc == feSyNkFlTb){zLKjXYQTKP = true;}
      while(ReDqrBZVdn == rVZqpiSWOm){hAmesBNZPh = true;}
      while(NBfrDcoDuZ == NBfrDcoDuZ){qJhoReMpqG = true;}
      while(feSyNkFlTb == feSyNkFlTb){qbBxaGijlg = true;}
      if(hfOcWueAUp == true){hfOcWueAUp = false;}
      if(ylrxXmhlAS == true){ylrxXmhlAS = false;}
      if(hYxnkmLFdG == true){hYxnkmLFdG = false;}
      if(umCBGhlDUI == true){umCBGhlDUI = false;}
      if(ynhFaslVaZ == true){ynhFaslVaZ = false;}
      if(DTkBsJhZrj == true){DTkBsJhZrj = false;}
      if(jZWNtLjpqp == true){jZWNtLjpqp = false;}
      if(BeRrUtprNq == true){BeRrUtprNq = false;}
      if(ApeDDbBBHx == true){ApeDDbBBHx = false;}
      if(zLKjXYQTKP == true){zLKjXYQTKP = false;}
      if(JudjXXBsfz == true){JudjXXBsfz = false;}
      if(SpMAjsuSKS == true){SpMAjsuSKS = false;}
      if(JhitqpThTu == true){JhitqpThTu = false;}
      if(cVgxhELtfe == true){cVgxhELtfe = false;}
      if(ZIUIdIyKze == true){ZIUIdIyKze = false;}
      if(dxJqFaMjsh == true){dxJqFaMjsh = false;}
      if(ETYkVxIPRf == true){ETYkVxIPRf = false;}
      if(hAmesBNZPh == true){hAmesBNZPh = false;}
      if(qJhoReMpqG == true){qJhoReMpqG = false;}
      if(qbBxaGijlg == true){qbBxaGijlg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVSRYQTTAI
{ 
  void kqGhKuhVfI()
  { 
      bool IdQMXhUoyF = false;
      bool pUgKkuZpjV = false;
      bool COatQloYnL = false;
      bool qMElLAtytM = false;
      bool SEVYAwOAAU = false;
      bool uNnsYsDVwl = false;
      bool rwAlOdQtyk = false;
      bool BauXCysBtT = false;
      bool XnXSQdXKNR = false;
      bool wXBHTWDiKW = false;
      bool fTCPTTRQqa = false;
      bool ABbbOEYhVk = false;
      bool GGgfncYnEe = false;
      bool tKqXnDlHyw = false;
      bool LHSlRuwZsO = false;
      bool yVMYQYlVaq = false;
      bool tcLMgpJEnK = false;
      bool RQiZYynuOs = false;
      bool gzuogXxRHO = false;
      bool QPgHBiuGFa = false;
      string BVPtsscnNN;
      string aSorKeUBft;
      string yHUqEQwHun;
      string dcRsAZtyLb;
      string tkwCEScXaO;
      string sgkHptAXpb;
      string wVsYjyAwqk;
      string kWpDAMKSlk;
      string mXffuwrKDG;
      string YVHjeXrXSG;
      string RggpdWqgGd;
      string ihlEnYpMdm;
      string FprkLOOGYb;
      string TmzfSGqpBY;
      string FLDYWqjCuG;
      string hftfAbnueP;
      string HjIeJuhFlh;
      string hAKFgtlTNT;
      string dLKStnsTeq;
      string RuKlQUDYPb;
      if(BVPtsscnNN == RggpdWqgGd){IdQMXhUoyF = true;}
      else if(RggpdWqgGd == BVPtsscnNN){fTCPTTRQqa = true;}
      if(aSorKeUBft == ihlEnYpMdm){pUgKkuZpjV = true;}
      else if(ihlEnYpMdm == aSorKeUBft){ABbbOEYhVk = true;}
      if(yHUqEQwHun == FprkLOOGYb){COatQloYnL = true;}
      else if(FprkLOOGYb == yHUqEQwHun){GGgfncYnEe = true;}
      if(dcRsAZtyLb == TmzfSGqpBY){qMElLAtytM = true;}
      else if(TmzfSGqpBY == dcRsAZtyLb){tKqXnDlHyw = true;}
      if(tkwCEScXaO == FLDYWqjCuG){SEVYAwOAAU = true;}
      else if(FLDYWqjCuG == tkwCEScXaO){LHSlRuwZsO = true;}
      if(sgkHptAXpb == hftfAbnueP){uNnsYsDVwl = true;}
      else if(hftfAbnueP == sgkHptAXpb){yVMYQYlVaq = true;}
      if(wVsYjyAwqk == HjIeJuhFlh){rwAlOdQtyk = true;}
      else if(HjIeJuhFlh == wVsYjyAwqk){tcLMgpJEnK = true;}
      if(kWpDAMKSlk == hAKFgtlTNT){BauXCysBtT = true;}
      if(mXffuwrKDG == dLKStnsTeq){XnXSQdXKNR = true;}
      if(YVHjeXrXSG == RuKlQUDYPb){wXBHTWDiKW = true;}
      while(hAKFgtlTNT == kWpDAMKSlk){RQiZYynuOs = true;}
      while(dLKStnsTeq == dLKStnsTeq){gzuogXxRHO = true;}
      while(RuKlQUDYPb == RuKlQUDYPb){QPgHBiuGFa = true;}
      if(IdQMXhUoyF == true){IdQMXhUoyF = false;}
      if(pUgKkuZpjV == true){pUgKkuZpjV = false;}
      if(COatQloYnL == true){COatQloYnL = false;}
      if(qMElLAtytM == true){qMElLAtytM = false;}
      if(SEVYAwOAAU == true){SEVYAwOAAU = false;}
      if(uNnsYsDVwl == true){uNnsYsDVwl = false;}
      if(rwAlOdQtyk == true){rwAlOdQtyk = false;}
      if(BauXCysBtT == true){BauXCysBtT = false;}
      if(XnXSQdXKNR == true){XnXSQdXKNR = false;}
      if(wXBHTWDiKW == true){wXBHTWDiKW = false;}
      if(fTCPTTRQqa == true){fTCPTTRQqa = false;}
      if(ABbbOEYhVk == true){ABbbOEYhVk = false;}
      if(GGgfncYnEe == true){GGgfncYnEe = false;}
      if(tKqXnDlHyw == true){tKqXnDlHyw = false;}
      if(LHSlRuwZsO == true){LHSlRuwZsO = false;}
      if(yVMYQYlVaq == true){yVMYQYlVaq = false;}
      if(tcLMgpJEnK == true){tcLMgpJEnK = false;}
      if(RQiZYynuOs == true){RQiZYynuOs = false;}
      if(gzuogXxRHO == true){gzuogXxRHO = false;}
      if(QPgHBiuGFa == true){QPgHBiuGFa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVXADYIFQX
{ 
  void mrOzapbafB()
  { 
      bool wBhReDwYnN = false;
      bool jxRmPSSfor = false;
      bool urfYCYfKDF = false;
      bool MHYqJBPEcp = false;
      bool bATRlMnJDh = false;
      bool jrTlxDVIOG = false;
      bool XlVhBcXacN = false;
      bool CODzQtXNlp = false;
      bool jVGUVTmmtG = false;
      bool fHpWSpekQJ = false;
      bool nNfpfVoUUC = false;
      bool eHWXWBeBMg = false;
      bool pjfWguYffZ = false;
      bool PlwcBVpQnz = false;
      bool eRSqaXjRAR = false;
      bool LdYjSEgJIk = false;
      bool xIotmrKsWA = false;
      bool LNMMCYRouI = false;
      bool KGfNOkNMKw = false;
      bool ofIDCVcXDh = false;
      string MxGSDpxyNL;
      string LBUBUhhpKe;
      string JjlqMUtqQf;
      string brmLPORGlt;
      string FVghPaJkDy;
      string VsXiBbKPGi;
      string wGggiSOIkG;
      string QbDQZmDEak;
      string LImSKhUDJm;
      string DBzCxznzyw;
      string MAAwgspHJO;
      string YGoUXmSOVB;
      string yKyyDOcASZ;
      string yDFdYKIpkR;
      string rNsuNxMdeK;
      string fZcxyBBBsR;
      string QonjQVAKwM;
      string ecdEIkQDjG;
      string CyVItXZIeW;
      string JGwSADYJdr;
      if(MxGSDpxyNL == MAAwgspHJO){wBhReDwYnN = true;}
      else if(MAAwgspHJO == MxGSDpxyNL){nNfpfVoUUC = true;}
      if(LBUBUhhpKe == YGoUXmSOVB){jxRmPSSfor = true;}
      else if(YGoUXmSOVB == LBUBUhhpKe){eHWXWBeBMg = true;}
      if(JjlqMUtqQf == yKyyDOcASZ){urfYCYfKDF = true;}
      else if(yKyyDOcASZ == JjlqMUtqQf){pjfWguYffZ = true;}
      if(brmLPORGlt == yDFdYKIpkR){MHYqJBPEcp = true;}
      else if(yDFdYKIpkR == brmLPORGlt){PlwcBVpQnz = true;}
      if(FVghPaJkDy == rNsuNxMdeK){bATRlMnJDh = true;}
      else if(rNsuNxMdeK == FVghPaJkDy){eRSqaXjRAR = true;}
      if(VsXiBbKPGi == fZcxyBBBsR){jrTlxDVIOG = true;}
      else if(fZcxyBBBsR == VsXiBbKPGi){LdYjSEgJIk = true;}
      if(wGggiSOIkG == QonjQVAKwM){XlVhBcXacN = true;}
      else if(QonjQVAKwM == wGggiSOIkG){xIotmrKsWA = true;}
      if(QbDQZmDEak == ecdEIkQDjG){CODzQtXNlp = true;}
      if(LImSKhUDJm == CyVItXZIeW){jVGUVTmmtG = true;}
      if(DBzCxznzyw == JGwSADYJdr){fHpWSpekQJ = true;}
      while(ecdEIkQDjG == QbDQZmDEak){LNMMCYRouI = true;}
      while(CyVItXZIeW == CyVItXZIeW){KGfNOkNMKw = true;}
      while(JGwSADYJdr == JGwSADYJdr){ofIDCVcXDh = true;}
      if(wBhReDwYnN == true){wBhReDwYnN = false;}
      if(jxRmPSSfor == true){jxRmPSSfor = false;}
      if(urfYCYfKDF == true){urfYCYfKDF = false;}
      if(MHYqJBPEcp == true){MHYqJBPEcp = false;}
      if(bATRlMnJDh == true){bATRlMnJDh = false;}
      if(jrTlxDVIOG == true){jrTlxDVIOG = false;}
      if(XlVhBcXacN == true){XlVhBcXacN = false;}
      if(CODzQtXNlp == true){CODzQtXNlp = false;}
      if(jVGUVTmmtG == true){jVGUVTmmtG = false;}
      if(fHpWSpekQJ == true){fHpWSpekQJ = false;}
      if(nNfpfVoUUC == true){nNfpfVoUUC = false;}
      if(eHWXWBeBMg == true){eHWXWBeBMg = false;}
      if(pjfWguYffZ == true){pjfWguYffZ = false;}
      if(PlwcBVpQnz == true){PlwcBVpQnz = false;}
      if(eRSqaXjRAR == true){eRSqaXjRAR = false;}
      if(LdYjSEgJIk == true){LdYjSEgJIk = false;}
      if(xIotmrKsWA == true){xIotmrKsWA = false;}
      if(LNMMCYRouI == true){LNMMCYRouI = false;}
      if(KGfNOkNMKw == true){KGfNOkNMKw = false;}
      if(ofIDCVcXDh == true){ofIDCVcXDh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AIEJVOGAWI
{ 
  void pWRNURXFbQ()
  { 
      bool QZeWKoSRJY = false;
      bool ahhskichWr = false;
      bool moxEYHDLDa = false;
      bool rSAkQXiiFy = false;
      bool ibdqoWzwiJ = false;
      bool mnVyZabaxC = false;
      bool lGNhgHgxcM = false;
      bool AtbYJKLGOC = false;
      bool HHctnDxBKo = false;
      bool uHkDMcNuJh = false;
      bool oBTVIsMwoP = false;
      bool PVLutdcTtc = false;
      bool JfmmQrIYMf = false;
      bool wQwfMFnHku = false;
      bool qAMuYZupIh = false;
      bool ztBfYJOfEQ = false;
      bool jnjISzYfho = false;
      bool pVhzlISrNq = false;
      bool wRPefCOQHD = false;
      bool qHCTKCQDbZ = false;
      string lLQkjcmrXd;
      string khPHCyfOPh;
      string QoKUJtlLmo;
      string wRgGfNEyyu;
      string TkhbqDMzrP;
      string qFiuZwAwbo;
      string qbFihSBJao;
      string thPTNfHicF;
      string gmSXxpikfi;
      string MHVJEqfzsX;
      string CDXDUIpOgt;
      string oRSWIEIhkr;
      string jPdrblMGPW;
      string zIoECdOPCo;
      string AUDlttnzAz;
      string hyNBnlZfai;
      string wiyKtgcOTd;
      string orewrOLqxh;
      string yNFPnBtmQP;
      string EhoTrQWrqM;
      if(lLQkjcmrXd == CDXDUIpOgt){QZeWKoSRJY = true;}
      else if(CDXDUIpOgt == lLQkjcmrXd){oBTVIsMwoP = true;}
      if(khPHCyfOPh == oRSWIEIhkr){ahhskichWr = true;}
      else if(oRSWIEIhkr == khPHCyfOPh){PVLutdcTtc = true;}
      if(QoKUJtlLmo == jPdrblMGPW){moxEYHDLDa = true;}
      else if(jPdrblMGPW == QoKUJtlLmo){JfmmQrIYMf = true;}
      if(wRgGfNEyyu == zIoECdOPCo){rSAkQXiiFy = true;}
      else if(zIoECdOPCo == wRgGfNEyyu){wQwfMFnHku = true;}
      if(TkhbqDMzrP == AUDlttnzAz){ibdqoWzwiJ = true;}
      else if(AUDlttnzAz == TkhbqDMzrP){qAMuYZupIh = true;}
      if(qFiuZwAwbo == hyNBnlZfai){mnVyZabaxC = true;}
      else if(hyNBnlZfai == qFiuZwAwbo){ztBfYJOfEQ = true;}
      if(qbFihSBJao == wiyKtgcOTd){lGNhgHgxcM = true;}
      else if(wiyKtgcOTd == qbFihSBJao){jnjISzYfho = true;}
      if(thPTNfHicF == orewrOLqxh){AtbYJKLGOC = true;}
      if(gmSXxpikfi == yNFPnBtmQP){HHctnDxBKo = true;}
      if(MHVJEqfzsX == EhoTrQWrqM){uHkDMcNuJh = true;}
      while(orewrOLqxh == thPTNfHicF){pVhzlISrNq = true;}
      while(yNFPnBtmQP == yNFPnBtmQP){wRPefCOQHD = true;}
      while(EhoTrQWrqM == EhoTrQWrqM){qHCTKCQDbZ = true;}
      if(QZeWKoSRJY == true){QZeWKoSRJY = false;}
      if(ahhskichWr == true){ahhskichWr = false;}
      if(moxEYHDLDa == true){moxEYHDLDa = false;}
      if(rSAkQXiiFy == true){rSAkQXiiFy = false;}
      if(ibdqoWzwiJ == true){ibdqoWzwiJ = false;}
      if(mnVyZabaxC == true){mnVyZabaxC = false;}
      if(lGNhgHgxcM == true){lGNhgHgxcM = false;}
      if(AtbYJKLGOC == true){AtbYJKLGOC = false;}
      if(HHctnDxBKo == true){HHctnDxBKo = false;}
      if(uHkDMcNuJh == true){uHkDMcNuJh = false;}
      if(oBTVIsMwoP == true){oBTVIsMwoP = false;}
      if(PVLutdcTtc == true){PVLutdcTtc = false;}
      if(JfmmQrIYMf == true){JfmmQrIYMf = false;}
      if(wQwfMFnHku == true){wQwfMFnHku = false;}
      if(qAMuYZupIh == true){qAMuYZupIh = false;}
      if(ztBfYJOfEQ == true){ztBfYJOfEQ = false;}
      if(jnjISzYfho == true){jnjISzYfho = false;}
      if(pVhzlISrNq == true){pVhzlISrNq = false;}
      if(wRPefCOQHD == true){wRPefCOQHD = false;}
      if(qHCTKCQDbZ == true){qHCTKCQDbZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWAEEABFGI
{ 
  void eDzVrXWeSD()
  { 
      bool bQmPUWApQx = false;
      bool uPnmjxJrJZ = false;
      bool XeIlQyheQg = false;
      bool qelkUhkMAG = false;
      bool hYsLdKtyPP = false;
      bool RZoMWxIAyV = false;
      bool oVYjFPcCSC = false;
      bool LxqCqykwHG = false;
      bool EiOBORoZNW = false;
      bool ZjNeRMAJGO = false;
      bool hqfNDUhmVX = false;
      bool LMrrQFGXVn = false;
      bool ZDnucbiMjd = false;
      bool ybpsXNDBys = false;
      bool iCDpKMqUNL = false;
      bool FcmRndCjkb = false;
      bool lVCqYjWzTD = false;
      bool CFYbEXzyjP = false;
      bool jNzXYVnXFt = false;
      bool KTPWHNzMQa = false;
      string YrNkyFlitK;
      string OTsLDNpnLz;
      string YlkRmUlZSE;
      string DIIFryNHqE;
      string uMVDDAxBEQ;
      string bSrNkmGwyd;
      string TMQoHGLnTF;
      string zhxHELPgNm;
      string XjVBcjQuTF;
      string qRJNkhwgwx;
      string oIhyRsVjIY;
      string WZiKGiqPMW;
      string pPTONhXjWV;
      string PijQyOCWji;
      string OfluhRizHB;
      string qfTZHYnTji;
      string VlNmImoRLq;
      string gTfdIJdYfw;
      string zYbUdiPKJZ;
      string ZhlAMbRylu;
      if(YrNkyFlitK == oIhyRsVjIY){bQmPUWApQx = true;}
      else if(oIhyRsVjIY == YrNkyFlitK){hqfNDUhmVX = true;}
      if(OTsLDNpnLz == WZiKGiqPMW){uPnmjxJrJZ = true;}
      else if(WZiKGiqPMW == OTsLDNpnLz){LMrrQFGXVn = true;}
      if(YlkRmUlZSE == pPTONhXjWV){XeIlQyheQg = true;}
      else if(pPTONhXjWV == YlkRmUlZSE){ZDnucbiMjd = true;}
      if(DIIFryNHqE == PijQyOCWji){qelkUhkMAG = true;}
      else if(PijQyOCWji == DIIFryNHqE){ybpsXNDBys = true;}
      if(uMVDDAxBEQ == OfluhRizHB){hYsLdKtyPP = true;}
      else if(OfluhRizHB == uMVDDAxBEQ){iCDpKMqUNL = true;}
      if(bSrNkmGwyd == qfTZHYnTji){RZoMWxIAyV = true;}
      else if(qfTZHYnTji == bSrNkmGwyd){FcmRndCjkb = true;}
      if(TMQoHGLnTF == VlNmImoRLq){oVYjFPcCSC = true;}
      else if(VlNmImoRLq == TMQoHGLnTF){lVCqYjWzTD = true;}
      if(zhxHELPgNm == gTfdIJdYfw){LxqCqykwHG = true;}
      if(XjVBcjQuTF == zYbUdiPKJZ){EiOBORoZNW = true;}
      if(qRJNkhwgwx == ZhlAMbRylu){ZjNeRMAJGO = true;}
      while(gTfdIJdYfw == zhxHELPgNm){CFYbEXzyjP = true;}
      while(zYbUdiPKJZ == zYbUdiPKJZ){jNzXYVnXFt = true;}
      while(ZhlAMbRylu == ZhlAMbRylu){KTPWHNzMQa = true;}
      if(bQmPUWApQx == true){bQmPUWApQx = false;}
      if(uPnmjxJrJZ == true){uPnmjxJrJZ = false;}
      if(XeIlQyheQg == true){XeIlQyheQg = false;}
      if(qelkUhkMAG == true){qelkUhkMAG = false;}
      if(hYsLdKtyPP == true){hYsLdKtyPP = false;}
      if(RZoMWxIAyV == true){RZoMWxIAyV = false;}
      if(oVYjFPcCSC == true){oVYjFPcCSC = false;}
      if(LxqCqykwHG == true){LxqCqykwHG = false;}
      if(EiOBORoZNW == true){EiOBORoZNW = false;}
      if(ZjNeRMAJGO == true){ZjNeRMAJGO = false;}
      if(hqfNDUhmVX == true){hqfNDUhmVX = false;}
      if(LMrrQFGXVn == true){LMrrQFGXVn = false;}
      if(ZDnucbiMjd == true){ZDnucbiMjd = false;}
      if(ybpsXNDBys == true){ybpsXNDBys = false;}
      if(iCDpKMqUNL == true){iCDpKMqUNL = false;}
      if(FcmRndCjkb == true){FcmRndCjkb = false;}
      if(lVCqYjWzTD == true){lVCqYjWzTD = false;}
      if(CFYbEXzyjP == true){CFYbEXzyjP = false;}
      if(jNzXYVnXFt == true){jNzXYVnXFt = false;}
      if(KTPWHNzMQa == true){KTPWHNzMQa = false;}
    } 
}; 
