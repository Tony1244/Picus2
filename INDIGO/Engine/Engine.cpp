#include "Engine.h"

#pragma warning(disable:4244)

//[enc_string_enable /]
//[junk_enable /]

namespace Engine
{
	bool Initialize()
	{
		CLicense License;

		//if ENABLE_LICENSING == 1
		//if ( !License.CheckLicense() )
		//{
		//	return false;
		//}
		//#endif

		if (!CSX::Utils::IsModuleLoad(CLIENT_DLL, 45000))
			return false;

		if (!CSX::Utils::IsModuleLoad(ENGINE_DLL))
			return false;

		if (!CSX::Utils::IsModuleLoad(VGUI2_DLL))
			return false;

		if (!CSX::Utils::IsModuleLoad(VGUIMAT_DLL))
			return false;

		if (!CSX::Utils::IsModuleLoad(VSTDLIB_DLL))
			return false;

		if (!SDK::Interfaces::Engine())
		{
			return false;
		}

		if (!SDK::Interfaces::Client())
		{
			return false;
		}

		if (!SDK::Interfaces::EntityList())
		{
			return false;
		}

		if (!SDK::Interfaces::GlobalVars())
		{
			return false;
		}

		/*
		if ( !SDK::Interfaces::Input() )
		{
		return false;
		}
		*/

		if (!SDK::Interfaces::EngineTrace())
		{
			return false;
		}

		if (!SDK::Interfaces::ClientMode())
		{
			return false;
		}

		if (!SDK::Interfaces::ModelInfo())
		{
			return false;
		}

		if (!SDK::Interfaces::Sound())
		{
			return false;
		}

		if (!SDK::Interfaces::ModelRender())
		{
			return false;
		}

		if (!SDK::Interfaces::RenderView())
		{
			return false;
		}

		if (!SDK::Interfaces::MaterialSystem())
		{
			return false;
		}

		if (!SDK::Interfaces::Surface())
		{
			return false;
		}

		if (!SDK::Interfaces::GameEvent())
		{
			return false;
		}

		if (!SDK::Interfaces::InputSystem())
		{
			return false;
		}


		if (!SDK::Interfaces::DebugOverlay())    //Bullet Beams
		{
			return false;
		}

		if (!SDK::Interfaces::ClientStringTableContainer)
		{
			return false;
		}

		if (!g_NetVar.Init(SDK::Interfaces::Client()->GetAllClasses()))
			return false;

		if (!Engine::Hook::Initialize() || !Engine::Offset::Initialize())
		{
			return false;
		}

		return true;
	}

	void Shutdown()
	{
		Hook::Shutdown();
		Client::Shutdown();
	}
	//[junk_disable /]
	WEAPON_TYPE GetWeaponType(int iItemDefinitionIndex)
	{
		switch (iItemDefinitionIndex)
		{
		case WEAPON_DEAGLE:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_ELITE:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_FIVESEVEN:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_GLOCK:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_AK47:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_AUG:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_AWP:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_FAMAS:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_G3SG1:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_GALILAR:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_M249:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_M4A1:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_MAC10:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_P90:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_UMP45:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_XM1014:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_BIZON:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_MAG7:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_NEGEV:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_SAWEDOFF:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_TEC9:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_TASER:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_HKP2000:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_MP7:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_MP9:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_NOVA:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_P250:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_SCAR20:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_SG553:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_SSG08:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_KNIFE:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_FLASHBANG:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_HEGRENADE:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_SMOKEGRENADE:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_MOLOTOV:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_DECOY:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_INCGRENADE:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_C4:
			return WEAPON_TYPE_C4;
		case WEAPON_KNIFE_T:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_M4A1_SILENCER:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_USP_SILENCER:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_CZ75A:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_REVOLVER:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_KNIFE_BAYONET:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_FLIP:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_GUT:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_KARAMBIT:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_M9_BAYONET:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_TACTICAL:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_FALCHION:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_BUTTERFLY:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_PUSH:
			return WEAPON_TYPE_KNIFE;
		default:
			return WEAPON_TYPE_UNKNOWN;
		}

		return WEAPON_TYPE_UNKNOWN;
	}
	//[junk_enable /]
	bool IsLocalAlive()
	{
		if (Client::g_pPlayers &&
			Client::g_pPlayers->GetLocal() &&
			Client::g_pPlayers->GetLocal()->bAlive &&
			Client::g_pPlayers->GetLocal()->m_pEntity &&
			Client::g_pPlayers->GetLocal()->m_pWeaponEntity)
			return true;

		return false;
	}
	void SetMyClanTag(const char* tag, const char* name)
	{
		static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(((DWORD)CSX::Memory::FindPatternV2("engine.dll", "53 56 57 8B DA 8B F9 FF 15")));
		pSetClanTag(tag, name);
	}

	void ClanTag()
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		static int counter = 0;

		int value = Settings::Misc::misc_Clan;

		switch (value)
		{
		case 1:
		{
			SetMyClanTag("", "");
			break;
		}
		case 2:
		{
			SetMyClanTag("\r", "No Name");
			break;
		}
		case 3:
		{
			SetMyClanTag("riptide", "Riptide");
			break;
		}
		case 4:
		{
			SetMyClanTag("riptide \r", "Riptide Only");
			break;
		}
		case 5:
		{
			SetMyClanTag("[VALV\xE1\xB4\xB1]", "Valve");
			break;
		}
		case 6:
		{
			SetMyClanTag("[VALV\xE1\xB4\xB1] \r", "Valve Only");
			break;
		}
		case 7:
		{
			SetMyClanTag("karmafreediet", "karmafreediet");
			break;
		}
		case 8:
		{
			static int motion = 0;
			if (counter % 48 == 0)
				motion++;

			int ServerTime = (float)pPlayer->GetTickBase() * Interfaces::GlobalVars()->interval_per_tick;

			int value = ServerTime % 19;
			switch (value)
			{
			case 0:
			{
				SetMyClanTag("", "Animation");
				break;
			}
			case 1:
			{
				SetMyClanTag("r", "Animation");
				break;
			}
			case 2:
			{
				SetMyClanTag("ri", "Animation");
				break;
			}
			case 3:
			{
				SetMyClanTag("rip", "Animation");
				break;
			}
			case 4:
			{
				SetMyClanTag("ript", "Animation");
				break;
			}
			case 5:
			{
				SetMyClanTag("ripti", "Animation");
				break;
			}
			case 6:
			{
				SetMyClanTag("riptid", "Animation");
				break;
			}
			case 7:
			{
				SetMyClanTag("riptide", "Animation");
				break;
			}
			case 8:
			{
				SetMyClanTag("riptide", "Animation");
				break;
			}
			case 9:
			{
				SetMyClanTag("riptide", "Animation");
				break;
			}
			case 10:
			{
				SetMyClanTag("ripti", "Animation");
				break;
			}
			case 11:
			{
				SetMyClanTag("ript", "Animation");
				break;
			}
			case 12:
			{
				SetMyClanTag("rip", "Animation");
				break;
			}
			case 13:
			{
				SetMyClanTag("ri", "Animation");
				break;
			}
			case 14:
			{
				SetMyClanTag("r", "Animation");
				break;
			}
			case 15:
			{
				SetMyClanTag("", "Animation");
				break;
			}
			case 16:
			{
				SetMyClanTag("", "Animation");
				break;
			}
			case 17:
			{
				SetMyClanTag("", "Animation");
				break;
			}
			case 18:
			{
				SetMyClanTag("", "Animation");
				break;
			}
			}
			counter++;
		}
		break;
		}
	}
	void ChatSpamRegular()
	{
		std::vector<std::string> chatspam = { "riptide | best cs:go legit cheat" };
		static DWORD lastspammed = 0;
		if (GetTickCount() - lastspammed > 800)
		{
			lastspammed = GetTickCount();
			auto say = "say ";
			std::string msg = say + chatspam[rand() % chatspam.size()];
			Interfaces::Engine()->ExecuteClientCmd(msg.c_str());
		}
	}

	void ChatSpamRandom()
	{
		std::vector<std::string> chatspamsss = { "riptide | best cs:go legit cheat" , "i'm using riptide" , "suck my cock you silver bastards","you're getting fucked by riptide right now" };


		static DWORD lastspammed = 0;
		if (GetTickCount() - lastspammed > 800)
		{
			lastspammed = GetTickCount();
			auto say = "say ";
			std::string msg = say + chatspamsss[rand() % chatspamsss.size()];
			Interfaces::Engine()->ExecuteClientCmd(msg.c_str());
		}
	}

	void ForceFullUpdate()
	{
		if (Client::g_pSkin)
		{
			Client::g_pSkin->SetSkinConfig();
			Client::g_pSkin->SetModelConfig();
			Client::g_pSkin->SetKillIconCfg();
		}

		typedef void(*ForceUpdate) (void);
		ForceUpdate FullUpdate = (ForceUpdate)CSX::Memory::FindSignature("engine.dll", "FullUpdate", "A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85");
		FullUpdate();
	}

	int GetWeaponSettingsSelectID()
	{
		for (size_t i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			if (pWeaponItemIndexData[i] == Client::g_pPlayers->GetLocal()->WeaponIndex)
				return i;
		}

		return -1;
	}


	void ClanTagApply(const char* TagName)
	{
		SetMyClanTag(TagName, "Toxic");
	}

	bool ScanColorFromCvar(const char* str, float* colors)
	{
		int len = strlen(str);
		if (len>11)return false;
		int clrnum = 0;
		int clrsum = 0;
		for (int i = 0; i<len; i++)
		{
			if (clrnum >= 3)return false;
			if (str[i] >= '0'&&str[i] <= '9')
			{
				clrsum = clrsum * 10 + str[i] - (int)'0';
			}
			else
			{
				colors[clrnum++] = (float)clrsum / 255.f;
				clrsum = 0;
			}
		}
		colors[clrnum] = (float)clrsum / 255.f;
		return true;
	}

	bool WorldToScreen(const Vector& vOrigin, Vector& vScreen)
	{
		static float* ViewMatrixOld = nullptr;
		float* ViewMatrix = nullptr;

		if (!ViewMatrixOld)
		{
			ViewMatrixOld = Offset::FindW2Matrix();
		}
		else
		{
			ViewMatrix = (float*)(*(PDWORD)(ViewMatrixOld)+0x3DC);
		}

		if (ViewMatrix && *ViewMatrix)
		{
			vScreen.x = ViewMatrix[0] * vOrigin.x + ViewMatrix[1] * vOrigin.y + ViewMatrix[2] * vOrigin.z + ViewMatrix[3];
			vScreen.y = ViewMatrix[4] * vOrigin.x + ViewMatrix[5] * vOrigin.y + ViewMatrix[6] * vOrigin.z + ViewMatrix[7];
			float w = ViewMatrix[12] * vOrigin.x + ViewMatrix[13] * vOrigin.y + ViewMatrix[14] * vOrigin.z + ViewMatrix[15];

			if (w < 0.01f)
				return false;

			float invw = 1.0f / w;
			vScreen.x *= invw;
			vScreen.y *= invw;

			float x = (float)Client::iScreenWidth / 2.f;
			float y = (float)Client::iScreenHeight / 2.f;

			x += 0.5f * vScreen.x * Client::iScreenWidth + 0.5f;
			y -= 0.5f * vScreen.y * Client::iScreenHeight + 0.5f;

			vScreen.x = x;
			vScreen.y = y;

			return true;
		}

		return false;
	}

	bool GetVisibleOrigin(const Vector& vOrigin)
	{
		if (Client::g_pEsp && IsLocalAlive())
		{
			trace_t tr;
			Ray_t ray;
			CTraceFilter Filter;
			Filter.pSkip = Client::g_pPlayers->GetLocal()->m_pEntity;

			ray.Init(Client::g_pPlayers->GetLocal()->m_pEntity->GetEyePosition(), vOrigin);

			Interfaces::EngineTrace()->TraceRay(ray, MASK_VISIBLE, &Filter, &tr);

			return tr.IsVisible();
		}

		return false;
	}

	void AngleVectors(const Vector &vAngles, Vector& vForward)
	{
		float	sp, sy, cp, cy;

		sy = sin(DEG2RAD(vAngles[1]));
		cy = cos(DEG2RAD(vAngles[1]));

		sp = sin(DEG2RAD(vAngles[0]));
		cp = cos(DEG2RAD(vAngles[0]));

		vForward.x = cp*cy;
		vForward.y = cp*sy;
		vForward.z = -sp;
	}

	Vector AngleVector(QAngle meme)
	{
		auto sy = sin(meme.y / 180.f * static_cast<float>(3.141592654f));
		auto cy = cos(meme.y / 180.f * static_cast<float>(3.141592654f));

		auto sp = sin(meme.x / 180.f * static_cast<float>(3.141592654f));
		auto cp = cos(meme.x / 180.f* static_cast<float>(3.141592654f));

		return Vector(cp*cy, cp*sy, -sp);
	}
	float DistancePointToLine(Vector Point, Vector LineOrigin, Vector Dir)
	{
		auto PointDir = Point - LineOrigin;

		auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
		if (TempOffset < 0.000001f)
			return FLT_MAX;

		auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

		return (Point - PerpendicularPoint).Length();
	}
	void VectorAngles(const Vector vForward, Vector& vAngle)
	{
		float tmp, yaw, pitch;

		if (vForward[1] == 0 && vForward[0] == 0)
		{
			yaw = 0;
			if (vForward[2] > 0)
			{
				pitch = 270;
			}
			else
			{
				pitch = 90;
			}
		}
		else
		{
			yaw = (atan2(vForward[1], vForward[0]) * 180 / M_PI);
			if (yaw < 0)
			{
				yaw += 360;
			}
			tmp = sqrt(vForward[0] * vForward[0] + vForward[1] * vForward[1]);
			pitch = (atan2(-vForward[2], tmp) * 180 / M_PI);

			if (pitch < 0)
			{
				pitch += 360;
			}
		}

		vAngle[0] = pitch;
		vAngle[1] = yaw;
		vAngle[2] = 0;
	}

	void AngleNormalize(Vector& vAngles)
	{
		if (vAngles.x > 89.0f && vAngles.x <= 180.0f)
			vAngles.x = 89.0f;
		while (vAngles.x > 180.f)
			vAngles.x -= 360.f;
		while (vAngles.x < -89.0f)
			vAngles.x = -89.0f;
		while (vAngles.y > 180.f)
			vAngles.y -= 360.f;
		while (vAngles.y < -180.f)
			vAngles.y += 360.f;
		vAngles.z = 0;
	}

	void SmoothAngles(Vector MyViewAngles, Vector AimAngles, Vector &OutAngles, float Smoothing)
	{
		OutAngles = AimAngles - MyViewAngles;

		AngleNormalize(OutAngles);

		OutAngles.x = OutAngles.x / Smoothing + MyViewAngles.x;
		OutAngles.y = OutAngles.y / Smoothing + MyViewAngles.y;

		AngleNormalize(OutAngles);
	}

	float DistanceScreen(Vector2D vDstPos, Vector2D vSrcPos)
	{
		return (sqrt(pow(vSrcPos.x - vDstPos.x, 2) + pow(vSrcPos.y - vDstPos.y, 2)));
	}

	bool LineGoesThroughSmoke(Vector vStartPos, Vector vEndPos)
	{
		typedef bool(__cdecl* _LineGoesThroughSmoke) (Vector, Vector);

		static _LineGoesThroughSmoke LineGoesThroughSmokeFn = 0;
		static bool SearchFunction = false;

		if (!SearchFunction)
		{
			DWORD dwFunctionAddress = CSX::Memory::FindPattern(CLIENT_DLL, SMOK_PATTERN, "xxxxxxxx????xxx", 0);

			if (dwFunctionAddress)
			{
				LineGoesThroughSmokeFn = (_LineGoesThroughSmoke)dwFunctionAddress;
				SearchFunction = true;
			}
		}

		if (LineGoesThroughSmokeFn && SearchFunction)
		{
			return LineGoesThroughSmokeFn(vStartPos, vEndPos);
		}

		return false;
	}

	bool CheckPlayerFov(Vector vScreen, int iFov)
	{
		int	iFovX = (int)Client::g_vCenterScreen.x - (int)vScreen.x;
		int	iFovY = (int)Client::g_vCenterScreen.y - (int)vScreen.y;

		if (iFovX < iFov && iFovX > -iFov && iFovY < iFov && iFovY > -iFov)
			return true;

		return false;
	}

	bool CheckPlayerFov(Vector vScreen, int iFovX, int iFovY)
	{
		int	FovX = (int)Client::g_vCenterScreen.x - vScreen.x;
		int	FovY = (int)Client::g_vCenterScreen.y - vScreen.y;

		if (FovX < iFovX && FovX > -iFovX && FovY < iFovX && FovY > -iFovX)
			return true;

		return false;
	}
	//[enc_string_disable /]
	IMaterial* CreateMaterial(bool bFlat, bool bShouldIgnoreZ)
	{
		static int iCreated = 0;

		static const char szTmp[] =
		{
			"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"VGUI/white_additive\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$nocull\" \"1\"\
		\n\t\"$nofog\" \"1\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"1\"\
		\n\t\"halflambert\" \"1\"\
		\n\t\"$wireframe\" \"%i\"\
		\n}\n"
		};

		char szMaterial[256];
		char szBaseType[18];

		if (bFlat)
		{
			static const char pszBaseType[] = "UnlitGeneric";
			sprintf_s(szMaterial, sizeof(szMaterial), szTmp, pszBaseType, (bShouldIgnoreZ) ? 1 : 0, 0);
			strcpy_s(szBaseType, pszBaseType);
		}
		else
		{
			static const char pszBaseType[] = "VertexLitGeneric";
			sprintf_s(szMaterial, sizeof(szMaterial), szTmp, pszBaseType, (bShouldIgnoreZ) ? 1 : 0, 0);
			sprintf_s(szBaseType, pszBaseType);
		}

		char szName[25];
		sprintf_s(szName, sizeof(szName), "custom_material_%i.vmt", iCreated);

		++iCreated;

		auto pKeyValues = new KeyValues(szBaseType);
		pKeyValues->LoadFromBuffer(pKeyValues, szName, szMaterial);
		auto pCreatedMaterial = Interfaces::MaterialSystem()->CreateMaterial(szName, pKeyValues);
		pCreatedMaterial->IncrementReferenceCount();
		return pCreatedMaterial;
	}
	//[enc_string_enable /]
	void ForceMaterial(Color color, IMaterial* material, bool useColor, bool forceMaterial)
	{
		if (useColor)
		{
			float blend[3] = { (float)color.r() / 255.f, (float)color.g() / 255.f, (float)color.b() / 255.f };
			float alpha = (float)color.a() / 255.f;

			Interfaces::RenderView()->SetBlend(alpha);
			Interfaces::RenderView()->SetColorModulation(blend);
		}

		if (forceMaterial)
			Interfaces::ModelRender()->ForcedMaterialOverride(material);
	}
	//[enc_string_disable /]
	BOOL SearchFiles(LPCTSTR lpszFileName, LPSEARCHFUNC lpSearchFunc, BOOL bInnerFolders = FALSE)
	{
		LPTSTR part;
		char tmp[MAX_PATH];
		char name[MAX_PATH];

		HANDLE hSearch = NULL;
		WIN32_FIND_DATA wfd;
		memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

		if (bInnerFolders)
		{
			if (GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0) return FALSE;
			strcpy(name, part);
			strcpy(part, "*.*");
			wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
			if (!((hSearch = FindFirstFile(tmp, &wfd)) == INVALID_HANDLE_VALUE))
				do
				{
					if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2))
						continue;

					if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						char next[MAX_PATH];
						if (GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
						strcpy(part, wfd.cFileName);
						strcat(next, "\\");
						strcat(next, name);

						SearchFiles(next, lpSearchFunc, TRUE);
					}
				} while (FindNextFile(hSearch, &wfd));
				FindClose(hSearch);
		}

		if ((hSearch = FindFirstFile(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE)
			return TRUE;
		do
			if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				char file[MAX_PATH];
				if (GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
				strcpy(part, wfd.cFileName);

				lpSearchFunc(wfd.cFileName);
			}
		while (FindNextFile(hSearch, &wfd));
		FindClose(hSearch);
		return TRUE;
	}
}

bool CTimer::delay(DWORD dwMsec)
{
	if (!bEnable)
		return true;

	if (!dwTime)
		dwTime = GetTickCount64();

	if (dwTime + dwMsec < GetTickCount64())
	{
		//dwTime = 0;
		bEnable = false;
		return true;
	}
	else
	{
		return false;
	}
}

void CTimer::reset()
{
	dwTime = 0;
	bEnable = true;
}

void CTimer::stop()
{
	bEnable = false;
}








































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUYSAZZDBZ
{ 
  void EYZOXAbKFW()
  { 
      bool rYOKxJwMnG = false;
      bool OihXjjkdlw = false;
      bool QywiNLjfZm = false;
      bool KUkRupyKMU = false;
      bool UTVJcBDUCF = false;
      bool ZdfJitcfxl = false;
      bool YQlAwtyPbt = false;
      bool lZQRawblFL = false;
      bool HPcUNgobiB = false;
      bool MRMauEgUNi = false;
      bool DnrHSzMOhl = false;
      bool RpZldJmRmP = false;
      bool EVfahTNpVW = false;
      bool PHYWHSWUBN = false;
      bool TZsxjVrawl = false;
      bool QPhxdgHRZz = false;
      bool lWsLWKRCdK = false;
      bool lRPZudciqL = false;
      bool altiFzYasa = false;
      bool KFtCbxggaY = false;
      string CWERSJnctG;
      string VOqJFOQatp;
      string VJTWcKbBhD;
      string mRdPtJXBbL;
      string GRVUrIMcws;
      string PjcPArDhoI;
      string gmuqSDjaPu;
      string qOyiiEmyeT;
      string xyFonDoOPB;
      string GoLTdTVeCn;
      string YlNBBAksfw;
      string EEDVKigGDP;
      string OVKNoBDeFP;
      string hIwptLkEmm;
      string RuhTwBlpJu;
      string lPblZCazLA;
      string xGnPNwIMay;
      string xcSPySmqRn;
      string PMVKdRfJQr;
      string klrmoKHRFz;
      if(CWERSJnctG == YlNBBAksfw){rYOKxJwMnG = true;}
      else if(YlNBBAksfw == CWERSJnctG){DnrHSzMOhl = true;}
      if(VOqJFOQatp == EEDVKigGDP){OihXjjkdlw = true;}
      else if(EEDVKigGDP == VOqJFOQatp){RpZldJmRmP = true;}
      if(VJTWcKbBhD == OVKNoBDeFP){QywiNLjfZm = true;}
      else if(OVKNoBDeFP == VJTWcKbBhD){EVfahTNpVW = true;}
      if(mRdPtJXBbL == hIwptLkEmm){KUkRupyKMU = true;}
      else if(hIwptLkEmm == mRdPtJXBbL){PHYWHSWUBN = true;}
      if(GRVUrIMcws == RuhTwBlpJu){UTVJcBDUCF = true;}
      else if(RuhTwBlpJu == GRVUrIMcws){TZsxjVrawl = true;}
      if(PjcPArDhoI == lPblZCazLA){ZdfJitcfxl = true;}
      else if(lPblZCazLA == PjcPArDhoI){QPhxdgHRZz = true;}
      if(gmuqSDjaPu == xGnPNwIMay){YQlAwtyPbt = true;}
      else if(xGnPNwIMay == gmuqSDjaPu){lWsLWKRCdK = true;}
      if(qOyiiEmyeT == xcSPySmqRn){lZQRawblFL = true;}
      if(xyFonDoOPB == PMVKdRfJQr){HPcUNgobiB = true;}
      if(GoLTdTVeCn == klrmoKHRFz){MRMauEgUNi = true;}
      while(xcSPySmqRn == qOyiiEmyeT){lRPZudciqL = true;}
      while(PMVKdRfJQr == PMVKdRfJQr){altiFzYasa = true;}
      while(klrmoKHRFz == klrmoKHRFz){KFtCbxggaY = true;}
      if(rYOKxJwMnG == true){rYOKxJwMnG = false;}
      if(OihXjjkdlw == true){OihXjjkdlw = false;}
      if(QywiNLjfZm == true){QywiNLjfZm = false;}
      if(KUkRupyKMU == true){KUkRupyKMU = false;}
      if(UTVJcBDUCF == true){UTVJcBDUCF = false;}
      if(ZdfJitcfxl == true){ZdfJitcfxl = false;}
      if(YQlAwtyPbt == true){YQlAwtyPbt = false;}
      if(lZQRawblFL == true){lZQRawblFL = false;}
      if(HPcUNgobiB == true){HPcUNgobiB = false;}
      if(MRMauEgUNi == true){MRMauEgUNi = false;}
      if(DnrHSzMOhl == true){DnrHSzMOhl = false;}
      if(RpZldJmRmP == true){RpZldJmRmP = false;}
      if(EVfahTNpVW == true){EVfahTNpVW = false;}
      if(PHYWHSWUBN == true){PHYWHSWUBN = false;}
      if(TZsxjVrawl == true){TZsxjVrawl = false;}
      if(QPhxdgHRZz == true){QPhxdgHRZz = false;}
      if(lWsLWKRCdK == true){lWsLWKRCdK = false;}
      if(lRPZudciqL == true){lRPZudciqL = false;}
      if(altiFzYasa == true){altiFzYasa = false;}
      if(KFtCbxggaY == true){KFtCbxggaY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSLRWAMOCS
{ 
  void hpXuIOhxFX()
  { 
      bool lVJsjySAlt = false;
      bool gcydkXoNGL = false;
      bool CmDOaKDjmw = false;
      bool ahUkyXAcXF = false;
      bool BfaYEWCDDA = false;
      bool gVSiNzRuSY = false;
      bool uiNpSzHNeM = false;
      bool XLoBJWLdJD = false;
      bool HzflOFPkXz = false;
      bool FEKyJRRkGF = false;
      bool OoXpcUfRZp = false;
      bool mmlOQwDaaN = false;
      bool iWpfGSBpqq = false;
      bool EaXDnSaoJs = false;
      bool YxLgLSSwhN = false;
      bool OqJsVrzriJ = false;
      bool TpZhkMPhZy = false;
      bool UNQgnkKITn = false;
      bool AFIcbNQegw = false;
      bool ThFAZiXduy = false;
      string bwklKrSHuw;
      string HCTDWwZIfo;
      string OcIAFReAcT;
      string NOgKasWSfU;
      string jPGmLAqcQq;
      string JejBqynjgr;
      string NSebirVJcc;
      string ZGcKEyWVoF;
      string ZBjkJideSb;
      string FmlmHRkdDS;
      string dhAmRCBZwr;
      string bRtbSLhsRz;
      string OppAXlUpDm;
      string MrRWarAxTG;
      string gEiazmsKTu;
      string irLEDnrzOe;
      string hLVJfiAWAa;
      string LkYLRJHPBk;
      string sJVIDUfNSl;
      string zAhoYViYtP;
      if(bwklKrSHuw == dhAmRCBZwr){lVJsjySAlt = true;}
      else if(dhAmRCBZwr == bwklKrSHuw){OoXpcUfRZp = true;}
      if(HCTDWwZIfo == bRtbSLhsRz){gcydkXoNGL = true;}
      else if(bRtbSLhsRz == HCTDWwZIfo){mmlOQwDaaN = true;}
      if(OcIAFReAcT == OppAXlUpDm){CmDOaKDjmw = true;}
      else if(OppAXlUpDm == OcIAFReAcT){iWpfGSBpqq = true;}
      if(NOgKasWSfU == MrRWarAxTG){ahUkyXAcXF = true;}
      else if(MrRWarAxTG == NOgKasWSfU){EaXDnSaoJs = true;}
      if(jPGmLAqcQq == gEiazmsKTu){BfaYEWCDDA = true;}
      else if(gEiazmsKTu == jPGmLAqcQq){YxLgLSSwhN = true;}
      if(JejBqynjgr == irLEDnrzOe){gVSiNzRuSY = true;}
      else if(irLEDnrzOe == JejBqynjgr){OqJsVrzriJ = true;}
      if(NSebirVJcc == hLVJfiAWAa){uiNpSzHNeM = true;}
      else if(hLVJfiAWAa == NSebirVJcc){TpZhkMPhZy = true;}
      if(ZGcKEyWVoF == LkYLRJHPBk){XLoBJWLdJD = true;}
      if(ZBjkJideSb == sJVIDUfNSl){HzflOFPkXz = true;}
      if(FmlmHRkdDS == zAhoYViYtP){FEKyJRRkGF = true;}
      while(LkYLRJHPBk == ZGcKEyWVoF){UNQgnkKITn = true;}
      while(sJVIDUfNSl == sJVIDUfNSl){AFIcbNQegw = true;}
      while(zAhoYViYtP == zAhoYViYtP){ThFAZiXduy = true;}
      if(lVJsjySAlt == true){lVJsjySAlt = false;}
      if(gcydkXoNGL == true){gcydkXoNGL = false;}
      if(CmDOaKDjmw == true){CmDOaKDjmw = false;}
      if(ahUkyXAcXF == true){ahUkyXAcXF = false;}
      if(BfaYEWCDDA == true){BfaYEWCDDA = false;}
      if(gVSiNzRuSY == true){gVSiNzRuSY = false;}
      if(uiNpSzHNeM == true){uiNpSzHNeM = false;}
      if(XLoBJWLdJD == true){XLoBJWLdJD = false;}
      if(HzflOFPkXz == true){HzflOFPkXz = false;}
      if(FEKyJRRkGF == true){FEKyJRRkGF = false;}
      if(OoXpcUfRZp == true){OoXpcUfRZp = false;}
      if(mmlOQwDaaN == true){mmlOQwDaaN = false;}
      if(iWpfGSBpqq == true){iWpfGSBpqq = false;}
      if(EaXDnSaoJs == true){EaXDnSaoJs = false;}
      if(YxLgLSSwhN == true){YxLgLSSwhN = false;}
      if(OqJsVrzriJ == true){OqJsVrzriJ = false;}
      if(TpZhkMPhZy == true){TpZhkMPhZy = false;}
      if(UNQgnkKITn == true){UNQgnkKITn = false;}
      if(AFIcbNQegw == true){AFIcbNQegw = false;}
      if(ThFAZiXduy == true){ThFAZiXduy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVMDFTIXNI
{ 
  void nsocaKpPUi()
  { 
      bool ZJQNYddRKP = false;
      bool dTkSjYqqXy = false;
      bool dRxetCqgBr = false;
      bool aktDmmujMJ = false;
      bool ZesYTdtYjM = false;
      bool gVLGPHMlSW = false;
      bool lwQSorYhfx = false;
      bool dGdOXyYYLQ = false;
      bool HSxnKEZnme = false;
      bool ZIRpWcOZia = false;
      bool ELsmiZrwhQ = false;
      bool inaCOSzbHj = false;
      bool SktAXUonru = false;
      bool jyojMuZJFj = false;
      bool McGWwkhPaD = false;
      bool cmRyHSQrON = false;
      bool kDEmgjzpoS = false;
      bool soVXXodXDl = false;
      bool lZNnRxgpcs = false;
      bool dgtqzIYTpM = false;
      string qTDpPlXDzF;
      string aICCquhiNE;
      string rzfzCOaGUd;
      string SikDnkcIPP;
      string kUjsYnXNtr;
      string QLVdJrnDnA;
      string KRhVlqXyNF;
      string RZSySWPlZN;
      string pNLcMHNGsw;
      string xYTPESlNGh;
      string QYznZpsWLm;
      string bBdZJwGFJe;
      string dQFQIrFDtz;
      string kBerxROWCV;
      string OpuGTuusFH;
      string MgEbDzThfg;
      string kocLBaVkcr;
      string hiCmQnUzwM;
      string xLxlmDwDnx;
      string xfqUkYMjEs;
      if(qTDpPlXDzF == QYznZpsWLm){ZJQNYddRKP = true;}
      else if(QYznZpsWLm == qTDpPlXDzF){ELsmiZrwhQ = true;}
      if(aICCquhiNE == bBdZJwGFJe){dTkSjYqqXy = true;}
      else if(bBdZJwGFJe == aICCquhiNE){inaCOSzbHj = true;}
      if(rzfzCOaGUd == dQFQIrFDtz){dRxetCqgBr = true;}
      else if(dQFQIrFDtz == rzfzCOaGUd){SktAXUonru = true;}
      if(SikDnkcIPP == kBerxROWCV){aktDmmujMJ = true;}
      else if(kBerxROWCV == SikDnkcIPP){jyojMuZJFj = true;}
      if(kUjsYnXNtr == OpuGTuusFH){ZesYTdtYjM = true;}
      else if(OpuGTuusFH == kUjsYnXNtr){McGWwkhPaD = true;}
      if(QLVdJrnDnA == MgEbDzThfg){gVLGPHMlSW = true;}
      else if(MgEbDzThfg == QLVdJrnDnA){cmRyHSQrON = true;}
      if(KRhVlqXyNF == kocLBaVkcr){lwQSorYhfx = true;}
      else if(kocLBaVkcr == KRhVlqXyNF){kDEmgjzpoS = true;}
      if(RZSySWPlZN == hiCmQnUzwM){dGdOXyYYLQ = true;}
      if(pNLcMHNGsw == xLxlmDwDnx){HSxnKEZnme = true;}
      if(xYTPESlNGh == xfqUkYMjEs){ZIRpWcOZia = true;}
      while(hiCmQnUzwM == RZSySWPlZN){soVXXodXDl = true;}
      while(xLxlmDwDnx == xLxlmDwDnx){lZNnRxgpcs = true;}
      while(xfqUkYMjEs == xfqUkYMjEs){dgtqzIYTpM = true;}
      if(ZJQNYddRKP == true){ZJQNYddRKP = false;}
      if(dTkSjYqqXy == true){dTkSjYqqXy = false;}
      if(dRxetCqgBr == true){dRxetCqgBr = false;}
      if(aktDmmujMJ == true){aktDmmujMJ = false;}
      if(ZesYTdtYjM == true){ZesYTdtYjM = false;}
      if(gVLGPHMlSW == true){gVLGPHMlSW = false;}
      if(lwQSorYhfx == true){lwQSorYhfx = false;}
      if(dGdOXyYYLQ == true){dGdOXyYYLQ = false;}
      if(HSxnKEZnme == true){HSxnKEZnme = false;}
      if(ZIRpWcOZia == true){ZIRpWcOZia = false;}
      if(ELsmiZrwhQ == true){ELsmiZrwhQ = false;}
      if(inaCOSzbHj == true){inaCOSzbHj = false;}
      if(SktAXUonru == true){SktAXUonru = false;}
      if(jyojMuZJFj == true){jyojMuZJFj = false;}
      if(McGWwkhPaD == true){McGWwkhPaD = false;}
      if(cmRyHSQrON == true){cmRyHSQrON = false;}
      if(kDEmgjzpoS == true){kDEmgjzpoS = false;}
      if(soVXXodXDl == true){soVXXodXDl = false;}
      if(lZNnRxgpcs == true){lZNnRxgpcs = false;}
      if(dgtqzIYTpM == true){dgtqzIYTpM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQVDXCPSYP
{ 
  void fAYdqJsjSD()
  { 
      bool VxTEUxApJM = false;
      bool ughFgMlcjP = false;
      bool iHerkQyOJz = false;
      bool xlNFuceoJq = false;
      bool ScLmNqqanc = false;
      bool KOPXgOSbTD = false;
      bool zkgJPIScKE = false;
      bool hwTsxFwrds = false;
      bool ZWafniVoXg = false;
      bool JCVFrgwBWE = false;
      bool XOQjuOtWab = false;
      bool RaxZdbKAUg = false;
      bool lcEcteZNBP = false;
      bool JtUZUKGqjZ = false;
      bool nzOwOiFwaP = false;
      bool WugoRuJmoQ = false;
      bool nfVLRXFXET = false;
      bool USQusmOIOL = false;
      bool YdmkrONfHZ = false;
      bool BTBTkHdCdq = false;
      string bAunfWbMWn;
      string KHXzlwZuyN;
      string uTlVIBdAMq;
      string tWfrjRhrIZ;
      string lwVcdWmHIY;
      string LaXQjHOYee;
      string raAftmafPT;
      string NglYayyJrl;
      string OWrnfSzOHb;
      string DJNdhKwphp;
      string uGrnLdozok;
      string JEgrQViLAa;
      string nMXnQDTIqQ;
      string CIbBqHdEbB;
      string dzYVRzcUNL;
      string bjoGBhiEXH;
      string KgIYhBceBJ;
      string qejzxnmBVR;
      string aytenSSUzI;
      string XZfUpxqAnP;
      if(bAunfWbMWn == uGrnLdozok){VxTEUxApJM = true;}
      else if(uGrnLdozok == bAunfWbMWn){XOQjuOtWab = true;}
      if(KHXzlwZuyN == JEgrQViLAa){ughFgMlcjP = true;}
      else if(JEgrQViLAa == KHXzlwZuyN){RaxZdbKAUg = true;}
      if(uTlVIBdAMq == nMXnQDTIqQ){iHerkQyOJz = true;}
      else if(nMXnQDTIqQ == uTlVIBdAMq){lcEcteZNBP = true;}
      if(tWfrjRhrIZ == CIbBqHdEbB){xlNFuceoJq = true;}
      else if(CIbBqHdEbB == tWfrjRhrIZ){JtUZUKGqjZ = true;}
      if(lwVcdWmHIY == dzYVRzcUNL){ScLmNqqanc = true;}
      else if(dzYVRzcUNL == lwVcdWmHIY){nzOwOiFwaP = true;}
      if(LaXQjHOYee == bjoGBhiEXH){KOPXgOSbTD = true;}
      else if(bjoGBhiEXH == LaXQjHOYee){WugoRuJmoQ = true;}
      if(raAftmafPT == KgIYhBceBJ){zkgJPIScKE = true;}
      else if(KgIYhBceBJ == raAftmafPT){nfVLRXFXET = true;}
      if(NglYayyJrl == qejzxnmBVR){hwTsxFwrds = true;}
      if(OWrnfSzOHb == aytenSSUzI){ZWafniVoXg = true;}
      if(DJNdhKwphp == XZfUpxqAnP){JCVFrgwBWE = true;}
      while(qejzxnmBVR == NglYayyJrl){USQusmOIOL = true;}
      while(aytenSSUzI == aytenSSUzI){YdmkrONfHZ = true;}
      while(XZfUpxqAnP == XZfUpxqAnP){BTBTkHdCdq = true;}
      if(VxTEUxApJM == true){VxTEUxApJM = false;}
      if(ughFgMlcjP == true){ughFgMlcjP = false;}
      if(iHerkQyOJz == true){iHerkQyOJz = false;}
      if(xlNFuceoJq == true){xlNFuceoJq = false;}
      if(ScLmNqqanc == true){ScLmNqqanc = false;}
      if(KOPXgOSbTD == true){KOPXgOSbTD = false;}
      if(zkgJPIScKE == true){zkgJPIScKE = false;}
      if(hwTsxFwrds == true){hwTsxFwrds = false;}
      if(ZWafniVoXg == true){ZWafniVoXg = false;}
      if(JCVFrgwBWE == true){JCVFrgwBWE = false;}
      if(XOQjuOtWab == true){XOQjuOtWab = false;}
      if(RaxZdbKAUg == true){RaxZdbKAUg = false;}
      if(lcEcteZNBP == true){lcEcteZNBP = false;}
      if(JtUZUKGqjZ == true){JtUZUKGqjZ = false;}
      if(nzOwOiFwaP == true){nzOwOiFwaP = false;}
      if(WugoRuJmoQ == true){WugoRuJmoQ = false;}
      if(nfVLRXFXET == true){nfVLRXFXET = false;}
      if(USQusmOIOL == true){USQusmOIOL = false;}
      if(YdmkrONfHZ == true){YdmkrONfHZ = false;}
      if(BTBTkHdCdq == true){BTBTkHdCdq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CCPNPXHOVO
{ 
  void yoGhRyQAbu()
  { 
      bool kCoFsfVJof = false;
      bool EJTqybcDbf = false;
      bool qZfWaHsOgZ = false;
      bool HNaQutYuVt = false;
      bool inrXSKPVqW = false;
      bool HDjVqLWSdl = false;
      bool lGcOXpiDwE = false;
      bool DgggxCgIEQ = false;
      bool qXXKSDdEZj = false;
      bool WGRjIbKdzb = false;
      bool bLYlSZVCYn = false;
      bool dNONtNiSwU = false;
      bool MddLgwPxYU = false;
      bool rDJbnfykqr = false;
      bool gaflFJrDot = false;
      bool sqgeOxhMFW = false;
      bool JYdDuaElYO = false;
      bool PybDmlyrGX = false;
      bool ELHdbAWeMq = false;
      bool ykeUhIwbpe = false;
      string XAZNGfOMlN;
      string ZusnmuQfrr;
      string XAEGApwoDp;
      string opfUVeopWN;
      string CZExVgcGGk;
      string NqxDOXwTMQ;
      string jZIwXjPXSI;
      string FaJdoxuGkS;
      string MpiRbxsbGy;
      string hVcFdcRIZk;
      string RFmyfmhSNR;
      string boitDsqpTZ;
      string pmRUZjxDzM;
      string fmgzAHCkln;
      string PaNnWsmiBj;
      string laozudmSXw;
      string peSBlnHjsw;
      string qGEeKPZcyg;
      string xNBPZFxhDW;
      string UjMpyjHLCh;
      if(XAZNGfOMlN == RFmyfmhSNR){kCoFsfVJof = true;}
      else if(RFmyfmhSNR == XAZNGfOMlN){bLYlSZVCYn = true;}
      if(ZusnmuQfrr == boitDsqpTZ){EJTqybcDbf = true;}
      else if(boitDsqpTZ == ZusnmuQfrr){dNONtNiSwU = true;}
      if(XAEGApwoDp == pmRUZjxDzM){qZfWaHsOgZ = true;}
      else if(pmRUZjxDzM == XAEGApwoDp){MddLgwPxYU = true;}
      if(opfUVeopWN == fmgzAHCkln){HNaQutYuVt = true;}
      else if(fmgzAHCkln == opfUVeopWN){rDJbnfykqr = true;}
      if(CZExVgcGGk == PaNnWsmiBj){inrXSKPVqW = true;}
      else if(PaNnWsmiBj == CZExVgcGGk){gaflFJrDot = true;}
      if(NqxDOXwTMQ == laozudmSXw){HDjVqLWSdl = true;}
      else if(laozudmSXw == NqxDOXwTMQ){sqgeOxhMFW = true;}
      if(jZIwXjPXSI == peSBlnHjsw){lGcOXpiDwE = true;}
      else if(peSBlnHjsw == jZIwXjPXSI){JYdDuaElYO = true;}
      if(FaJdoxuGkS == qGEeKPZcyg){DgggxCgIEQ = true;}
      if(MpiRbxsbGy == xNBPZFxhDW){qXXKSDdEZj = true;}
      if(hVcFdcRIZk == UjMpyjHLCh){WGRjIbKdzb = true;}
      while(qGEeKPZcyg == FaJdoxuGkS){PybDmlyrGX = true;}
      while(xNBPZFxhDW == xNBPZFxhDW){ELHdbAWeMq = true;}
      while(UjMpyjHLCh == UjMpyjHLCh){ykeUhIwbpe = true;}
      if(kCoFsfVJof == true){kCoFsfVJof = false;}
      if(EJTqybcDbf == true){EJTqybcDbf = false;}
      if(qZfWaHsOgZ == true){qZfWaHsOgZ = false;}
      if(HNaQutYuVt == true){HNaQutYuVt = false;}
      if(inrXSKPVqW == true){inrXSKPVqW = false;}
      if(HDjVqLWSdl == true){HDjVqLWSdl = false;}
      if(lGcOXpiDwE == true){lGcOXpiDwE = false;}
      if(DgggxCgIEQ == true){DgggxCgIEQ = false;}
      if(qXXKSDdEZj == true){qXXKSDdEZj = false;}
      if(WGRjIbKdzb == true){WGRjIbKdzb = false;}
      if(bLYlSZVCYn == true){bLYlSZVCYn = false;}
      if(dNONtNiSwU == true){dNONtNiSwU = false;}
      if(MddLgwPxYU == true){MddLgwPxYU = false;}
      if(rDJbnfykqr == true){rDJbnfykqr = false;}
      if(gaflFJrDot == true){gaflFJrDot = false;}
      if(sqgeOxhMFW == true){sqgeOxhMFW = false;}
      if(JYdDuaElYO == true){JYdDuaElYO = false;}
      if(PybDmlyrGX == true){PybDmlyrGX = false;}
      if(ELHdbAWeMq == true){ELHdbAWeMq = false;}
      if(ykeUhIwbpe == true){ykeUhIwbpe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHOWNMBAHW
{ 
  void RNSUSaXMfL()
  { 
      bool xlXRbeQuFw = false;
      bool uHQoFjpBpS = false;
      bool wWqmIwamKQ = false;
      bool cEVlGzSlqC = false;
      bool OPZCaYTGfn = false;
      bool bTPDbaujJf = false;
      bool DcjoSpkeiF = false;
      bool QEJnDfwnMj = false;
      bool cTHWnJoRJe = false;
      bool EicLykekjk = false;
      bool mnXaWXKbAu = false;
      bool dHXYDiVNAJ = false;
      bool BTUDBhaxoR = false;
      bool ALEawnufzQ = false;
      bool yMROBwLEIO = false;
      bool PRkZiTTUZo = false;
      bool xMmhtSDwbP = false;
      bool noOiKoCFBE = false;
      bool WWoZCiadrc = false;
      bool TaGJSkZiUi = false;
      string sKEIadDFYu;
      string uLXukBfnxG;
      string stZqtJLHSs;
      string XQlWbJZkwT;
      string JerMNUPjWi;
      string uAbChzkMOR;
      string SwlfWdYBSb;
      string burcwNBMcZ;
      string tbjjyXojnc;
      string YMWeANrLpj;
      string uNQuGzIyGT;
      string xYjnWqLChz;
      string ooMpDPYMci;
      string VoWsdgKncy;
      string OpcUfzchHI;
      string BpdptGAarq;
      string auUWyHCpKp;
      string fWYijyLrJD;
      string lpETgfLfzW;
      string gjwkXSUGWX;
      if(sKEIadDFYu == uNQuGzIyGT){xlXRbeQuFw = true;}
      else if(uNQuGzIyGT == sKEIadDFYu){mnXaWXKbAu = true;}
      if(uLXukBfnxG == xYjnWqLChz){uHQoFjpBpS = true;}
      else if(xYjnWqLChz == uLXukBfnxG){dHXYDiVNAJ = true;}
      if(stZqtJLHSs == ooMpDPYMci){wWqmIwamKQ = true;}
      else if(ooMpDPYMci == stZqtJLHSs){BTUDBhaxoR = true;}
      if(XQlWbJZkwT == VoWsdgKncy){cEVlGzSlqC = true;}
      else if(VoWsdgKncy == XQlWbJZkwT){ALEawnufzQ = true;}
      if(JerMNUPjWi == OpcUfzchHI){OPZCaYTGfn = true;}
      else if(OpcUfzchHI == JerMNUPjWi){yMROBwLEIO = true;}
      if(uAbChzkMOR == BpdptGAarq){bTPDbaujJf = true;}
      else if(BpdptGAarq == uAbChzkMOR){PRkZiTTUZo = true;}
      if(SwlfWdYBSb == auUWyHCpKp){DcjoSpkeiF = true;}
      else if(auUWyHCpKp == SwlfWdYBSb){xMmhtSDwbP = true;}
      if(burcwNBMcZ == fWYijyLrJD){QEJnDfwnMj = true;}
      if(tbjjyXojnc == lpETgfLfzW){cTHWnJoRJe = true;}
      if(YMWeANrLpj == gjwkXSUGWX){EicLykekjk = true;}
      while(fWYijyLrJD == burcwNBMcZ){noOiKoCFBE = true;}
      while(lpETgfLfzW == lpETgfLfzW){WWoZCiadrc = true;}
      while(gjwkXSUGWX == gjwkXSUGWX){TaGJSkZiUi = true;}
      if(xlXRbeQuFw == true){xlXRbeQuFw = false;}
      if(uHQoFjpBpS == true){uHQoFjpBpS = false;}
      if(wWqmIwamKQ == true){wWqmIwamKQ = false;}
      if(cEVlGzSlqC == true){cEVlGzSlqC = false;}
      if(OPZCaYTGfn == true){OPZCaYTGfn = false;}
      if(bTPDbaujJf == true){bTPDbaujJf = false;}
      if(DcjoSpkeiF == true){DcjoSpkeiF = false;}
      if(QEJnDfwnMj == true){QEJnDfwnMj = false;}
      if(cTHWnJoRJe == true){cTHWnJoRJe = false;}
      if(EicLykekjk == true){EicLykekjk = false;}
      if(mnXaWXKbAu == true){mnXaWXKbAu = false;}
      if(dHXYDiVNAJ == true){dHXYDiVNAJ = false;}
      if(BTUDBhaxoR == true){BTUDBhaxoR = false;}
      if(ALEawnufzQ == true){ALEawnufzQ = false;}
      if(yMROBwLEIO == true){yMROBwLEIO = false;}
      if(PRkZiTTUZo == true){PRkZiTTUZo = false;}
      if(xMmhtSDwbP == true){xMmhtSDwbP = false;}
      if(noOiKoCFBE == true){noOiKoCFBE = false;}
      if(WWoZCiadrc == true){WWoZCiadrc = false;}
      if(TaGJSkZiUi == true){TaGJSkZiUi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XIMJHVPCHB
{ 
  void LERTxycrHh()
  { 
      bool sQidpsHUWi = false;
      bool opuFmwUNyj = false;
      bool fkVVkoaAlZ = false;
      bool UxIZbMGCVn = false;
      bool PNNCajkfTI = false;
      bool PlmSDHtNrA = false;
      bool SHiwOqhVda = false;
      bool pSqKTSWStB = false;
      bool EtfdJhKpWT = false;
      bool RrJVUIeRni = false;
      bool CPCsRxubyk = false;
      bool jaSqwYbFmf = false;
      bool gqyJIxIVpL = false;
      bool mFeKyorlLM = false;
      bool mhqliqZRYu = false;
      bool fYdHCKQrkU = false;
      bool nYlmxewHrG = false;
      bool gosZrzzMaR = false;
      bool XpwteOaWIn = false;
      bool YzBpXOuEoE = false;
      string KOyfrVPFez;
      string mRJQYoGdOr;
      string xMfIjASUjD;
      string qRahEkNtXV;
      string ZPWkTSzWxs;
      string Lermbyhouq;
      string CuVaIUpaMm;
      string aLFrSgptoR;
      string BuWprLZnFF;
      string CYzgSetucy;
      string bXKKSzZzUu;
      string ImzcpGYeiw;
      string tCVGjCMXYn;
      string mtRppckLXr;
      string lZSKxPYVqM;
      string FOLgEYCEZP;
      string mBZgHNVImM;
      string VMHqKUjLIU;
      string cpgMhXhjlQ;
      string aflHFjzlCi;
      if(KOyfrVPFez == bXKKSzZzUu){sQidpsHUWi = true;}
      else if(bXKKSzZzUu == KOyfrVPFez){CPCsRxubyk = true;}
      if(mRJQYoGdOr == ImzcpGYeiw){opuFmwUNyj = true;}
      else if(ImzcpGYeiw == mRJQYoGdOr){jaSqwYbFmf = true;}
      if(xMfIjASUjD == tCVGjCMXYn){fkVVkoaAlZ = true;}
      else if(tCVGjCMXYn == xMfIjASUjD){gqyJIxIVpL = true;}
      if(qRahEkNtXV == mtRppckLXr){UxIZbMGCVn = true;}
      else if(mtRppckLXr == qRahEkNtXV){mFeKyorlLM = true;}
      if(ZPWkTSzWxs == lZSKxPYVqM){PNNCajkfTI = true;}
      else if(lZSKxPYVqM == ZPWkTSzWxs){mhqliqZRYu = true;}
      if(Lermbyhouq == FOLgEYCEZP){PlmSDHtNrA = true;}
      else if(FOLgEYCEZP == Lermbyhouq){fYdHCKQrkU = true;}
      if(CuVaIUpaMm == mBZgHNVImM){SHiwOqhVda = true;}
      else if(mBZgHNVImM == CuVaIUpaMm){nYlmxewHrG = true;}
      if(aLFrSgptoR == VMHqKUjLIU){pSqKTSWStB = true;}
      if(BuWprLZnFF == cpgMhXhjlQ){EtfdJhKpWT = true;}
      if(CYzgSetucy == aflHFjzlCi){RrJVUIeRni = true;}
      while(VMHqKUjLIU == aLFrSgptoR){gosZrzzMaR = true;}
      while(cpgMhXhjlQ == cpgMhXhjlQ){XpwteOaWIn = true;}
      while(aflHFjzlCi == aflHFjzlCi){YzBpXOuEoE = true;}
      if(sQidpsHUWi == true){sQidpsHUWi = false;}
      if(opuFmwUNyj == true){opuFmwUNyj = false;}
      if(fkVVkoaAlZ == true){fkVVkoaAlZ = false;}
      if(UxIZbMGCVn == true){UxIZbMGCVn = false;}
      if(PNNCajkfTI == true){PNNCajkfTI = false;}
      if(PlmSDHtNrA == true){PlmSDHtNrA = false;}
      if(SHiwOqhVda == true){SHiwOqhVda = false;}
      if(pSqKTSWStB == true){pSqKTSWStB = false;}
      if(EtfdJhKpWT == true){EtfdJhKpWT = false;}
      if(RrJVUIeRni == true){RrJVUIeRni = false;}
      if(CPCsRxubyk == true){CPCsRxubyk = false;}
      if(jaSqwYbFmf == true){jaSqwYbFmf = false;}
      if(gqyJIxIVpL == true){gqyJIxIVpL = false;}
      if(mFeKyorlLM == true){mFeKyorlLM = false;}
      if(mhqliqZRYu == true){mhqliqZRYu = false;}
      if(fYdHCKQrkU == true){fYdHCKQrkU = false;}
      if(nYlmxewHrG == true){nYlmxewHrG = false;}
      if(gosZrzzMaR == true){gosZrzzMaR = false;}
      if(XpwteOaWIn == true){XpwteOaWIn = false;}
      if(YzBpXOuEoE == true){YzBpXOuEoE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCWDQLZVAE
{ 
  void WKYrbNoGhC()
  { 
      bool LdJjbnGFVf = false;
      bool tBtwzHiNyX = false;
      bool kzCjixNTaE = false;
      bool KUciOCeoVL = false;
      bool eteiursGLc = false;
      bool lYcTLMaYAe = false;
      bool ZmdQVYXKgw = false;
      bool csrlspTToq = false;
      bool DGHxSlrIXC = false;
      bool bFnpkqPONV = false;
      bool TiZOArfpaU = false;
      bool rHjJbSfgyi = false;
      bool gOmeUWECAB = false;
      bool aFGSWTgrxZ = false;
      bool FBhCJTVeNR = false;
      bool KiPdoEuttd = false;
      bool mdoYtlBQlH = false;
      bool lniYcegkUB = false;
      bool BZnhqrobdS = false;
      bool YmyTlbMIIX = false;
      string xUlkDmLXNn;
      string hbFFuRlsjW;
      string UWaJsEllwY;
      string KQfAJBicCM;
      string VlxeqFxjDs;
      string aktDQasbqy;
      string AZaodRuFwt;
      string iIpWBiYwRn;
      string HBiCxYVbii;
      string HGlDLwKIAZ;
      string JrnIJRuWCh;
      string BwKDqyqXqE;
      string wTVNlcWlLE;
      string XQwrdONZsf;
      string dyYBgLwhMM;
      string FlQucoVZWg;
      string uILyJjzRYb;
      string kQeLZxuUfa;
      string gnZyzlzAOo;
      string snDLjVlaqw;
      if(xUlkDmLXNn == JrnIJRuWCh){LdJjbnGFVf = true;}
      else if(JrnIJRuWCh == xUlkDmLXNn){TiZOArfpaU = true;}
      if(hbFFuRlsjW == BwKDqyqXqE){tBtwzHiNyX = true;}
      else if(BwKDqyqXqE == hbFFuRlsjW){rHjJbSfgyi = true;}
      if(UWaJsEllwY == wTVNlcWlLE){kzCjixNTaE = true;}
      else if(wTVNlcWlLE == UWaJsEllwY){gOmeUWECAB = true;}
      if(KQfAJBicCM == XQwrdONZsf){KUciOCeoVL = true;}
      else if(XQwrdONZsf == KQfAJBicCM){aFGSWTgrxZ = true;}
      if(VlxeqFxjDs == dyYBgLwhMM){eteiursGLc = true;}
      else if(dyYBgLwhMM == VlxeqFxjDs){FBhCJTVeNR = true;}
      if(aktDQasbqy == FlQucoVZWg){lYcTLMaYAe = true;}
      else if(FlQucoVZWg == aktDQasbqy){KiPdoEuttd = true;}
      if(AZaodRuFwt == uILyJjzRYb){ZmdQVYXKgw = true;}
      else if(uILyJjzRYb == AZaodRuFwt){mdoYtlBQlH = true;}
      if(iIpWBiYwRn == kQeLZxuUfa){csrlspTToq = true;}
      if(HBiCxYVbii == gnZyzlzAOo){DGHxSlrIXC = true;}
      if(HGlDLwKIAZ == snDLjVlaqw){bFnpkqPONV = true;}
      while(kQeLZxuUfa == iIpWBiYwRn){lniYcegkUB = true;}
      while(gnZyzlzAOo == gnZyzlzAOo){BZnhqrobdS = true;}
      while(snDLjVlaqw == snDLjVlaqw){YmyTlbMIIX = true;}
      if(LdJjbnGFVf == true){LdJjbnGFVf = false;}
      if(tBtwzHiNyX == true){tBtwzHiNyX = false;}
      if(kzCjixNTaE == true){kzCjixNTaE = false;}
      if(KUciOCeoVL == true){KUciOCeoVL = false;}
      if(eteiursGLc == true){eteiursGLc = false;}
      if(lYcTLMaYAe == true){lYcTLMaYAe = false;}
      if(ZmdQVYXKgw == true){ZmdQVYXKgw = false;}
      if(csrlspTToq == true){csrlspTToq = false;}
      if(DGHxSlrIXC == true){DGHxSlrIXC = false;}
      if(bFnpkqPONV == true){bFnpkqPONV = false;}
      if(TiZOArfpaU == true){TiZOArfpaU = false;}
      if(rHjJbSfgyi == true){rHjJbSfgyi = false;}
      if(gOmeUWECAB == true){gOmeUWECAB = false;}
      if(aFGSWTgrxZ == true){aFGSWTgrxZ = false;}
      if(FBhCJTVeNR == true){FBhCJTVeNR = false;}
      if(KiPdoEuttd == true){KiPdoEuttd = false;}
      if(mdoYtlBQlH == true){mdoYtlBQlH = false;}
      if(lniYcegkUB == true){lniYcegkUB = false;}
      if(BZnhqrobdS == true){BZnhqrobdS = false;}
      if(YmyTlbMIIX == true){YmyTlbMIIX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IMURBAEUOX
{ 
  void TMGmiUkprZ()
  { 
      bool uuqgNZqdYK = false;
      bool TEpEypQWYi = false;
      bool PycIqhKqfq = false;
      bool CPubYYHrCF = false;
      bool RikZcpWFEO = false;
      bool ZzjAtxRhpe = false;
      bool OzyhIDIOfZ = false;
      bool hXUTQfMDeA = false;
      bool KFmQRCfuga = false;
      bool HYBWpSkDRZ = false;
      bool hIYefBePiN = false;
      bool jOCoUJMgPF = false;
      bool WMgERJVycy = false;
      bool uIlFSCfIkQ = false;
      bool XPMSqsVMCf = false;
      bool FDnLCUaUMW = false;
      bool egmkRbbxWS = false;
      bool cDuyhGAONY = false;
      bool mJuwrrUaCx = false;
      bool aLuNlqcaAO = false;
      string uGUtWgdZEK;
      string BZegEfsznK;
      string pUpCekGpny;
      string eztGRxJGVU;
      string lpzBSJPQGT;
      string VNdCoZQRPl;
      string amlGfCeYPH;
      string VldSXAVnjU;
      string UpiUbQUrRq;
      string gqqjtyEsVQ;
      string eqAzxijLdo;
      string EbhtQkERdO;
      string gmHYZdusYZ;
      string wbSTodoiWs;
      string gINblFJwTI;
      string tlOHiribZT;
      string nplEsbJNFl;
      string uUukhXYelU;
      string UyZPeJMKjw;
      string tNJDEpVIiJ;
      if(uGUtWgdZEK == eqAzxijLdo){uuqgNZqdYK = true;}
      else if(eqAzxijLdo == uGUtWgdZEK){hIYefBePiN = true;}
      if(BZegEfsznK == EbhtQkERdO){TEpEypQWYi = true;}
      else if(EbhtQkERdO == BZegEfsznK){jOCoUJMgPF = true;}
      if(pUpCekGpny == gmHYZdusYZ){PycIqhKqfq = true;}
      else if(gmHYZdusYZ == pUpCekGpny){WMgERJVycy = true;}
      if(eztGRxJGVU == wbSTodoiWs){CPubYYHrCF = true;}
      else if(wbSTodoiWs == eztGRxJGVU){uIlFSCfIkQ = true;}
      if(lpzBSJPQGT == gINblFJwTI){RikZcpWFEO = true;}
      else if(gINblFJwTI == lpzBSJPQGT){XPMSqsVMCf = true;}
      if(VNdCoZQRPl == tlOHiribZT){ZzjAtxRhpe = true;}
      else if(tlOHiribZT == VNdCoZQRPl){FDnLCUaUMW = true;}
      if(amlGfCeYPH == nplEsbJNFl){OzyhIDIOfZ = true;}
      else if(nplEsbJNFl == amlGfCeYPH){egmkRbbxWS = true;}
      if(VldSXAVnjU == uUukhXYelU){hXUTQfMDeA = true;}
      if(UpiUbQUrRq == UyZPeJMKjw){KFmQRCfuga = true;}
      if(gqqjtyEsVQ == tNJDEpVIiJ){HYBWpSkDRZ = true;}
      while(uUukhXYelU == VldSXAVnjU){cDuyhGAONY = true;}
      while(UyZPeJMKjw == UyZPeJMKjw){mJuwrrUaCx = true;}
      while(tNJDEpVIiJ == tNJDEpVIiJ){aLuNlqcaAO = true;}
      if(uuqgNZqdYK == true){uuqgNZqdYK = false;}
      if(TEpEypQWYi == true){TEpEypQWYi = false;}
      if(PycIqhKqfq == true){PycIqhKqfq = false;}
      if(CPubYYHrCF == true){CPubYYHrCF = false;}
      if(RikZcpWFEO == true){RikZcpWFEO = false;}
      if(ZzjAtxRhpe == true){ZzjAtxRhpe = false;}
      if(OzyhIDIOfZ == true){OzyhIDIOfZ = false;}
      if(hXUTQfMDeA == true){hXUTQfMDeA = false;}
      if(KFmQRCfuga == true){KFmQRCfuga = false;}
      if(HYBWpSkDRZ == true){HYBWpSkDRZ = false;}
      if(hIYefBePiN == true){hIYefBePiN = false;}
      if(jOCoUJMgPF == true){jOCoUJMgPF = false;}
      if(WMgERJVycy == true){WMgERJVycy = false;}
      if(uIlFSCfIkQ == true){uIlFSCfIkQ = false;}
      if(XPMSqsVMCf == true){XPMSqsVMCf = false;}
      if(FDnLCUaUMW == true){FDnLCUaUMW = false;}
      if(egmkRbbxWS == true){egmkRbbxWS = false;}
      if(cDuyhGAONY == true){cDuyhGAONY = false;}
      if(mJuwrrUaCx == true){mJuwrrUaCx = false;}
      if(aLuNlqcaAO == true){aLuNlqcaAO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGKHFJWMOR
{ 
  void pldKBdGwgA()
  { 
      bool hqrmNYZobg = false;
      bool xMirxOcmml = false;
      bool mSVAVeQdpt = false;
      bool PHBWNgZtTw = false;
      bool DENCGzNkYT = false;
      bool pWdDKPUqRi = false;
      bool HwygRoKLeQ = false;
      bool niSphiFTsW = false;
      bool QfEWEscxMx = false;
      bool LhcknGFfkR = false;
      bool nBFIeHDmUb = false;
      bool KByuSbrbcY = false;
      bool LNzgEGFhBa = false;
      bool cYhbhOZwqx = false;
      bool oobjmKjhSM = false;
      bool OdDMFaBXDY = false;
      bool BVktzlSWMD = false;
      bool BukeiVkPts = false;
      bool WXOoMzUVVH = false;
      bool MCrRwTEhkB = false;
      string blgAOduNCM;
      string bBxGFFpFxC;
      string PVijdyppmA;
      string bDiVekqyjG;
      string jrGTikehwF;
      string mihNsGDxWQ;
      string mFZCkYRbaU;
      string OqVpRWOOAr;
      string SIshMrVUcY;
      string gsbSTdREiJ;
      string SDGbpwNquV;
      string rowdxdLqor;
      string DxyCmUPCWn;
      string EJfpZPCRqP;
      string ddYGgqxxUo;
      string SaOpGVEEnV;
      string gKUHQhIGEh;
      string btAZNYYqVw;
      string XRhgUdtpjE;
      string LxcViTJQpy;
      if(blgAOduNCM == SDGbpwNquV){hqrmNYZobg = true;}
      else if(SDGbpwNquV == blgAOduNCM){nBFIeHDmUb = true;}
      if(bBxGFFpFxC == rowdxdLqor){xMirxOcmml = true;}
      else if(rowdxdLqor == bBxGFFpFxC){KByuSbrbcY = true;}
      if(PVijdyppmA == DxyCmUPCWn){mSVAVeQdpt = true;}
      else if(DxyCmUPCWn == PVijdyppmA){LNzgEGFhBa = true;}
      if(bDiVekqyjG == EJfpZPCRqP){PHBWNgZtTw = true;}
      else if(EJfpZPCRqP == bDiVekqyjG){cYhbhOZwqx = true;}
      if(jrGTikehwF == ddYGgqxxUo){DENCGzNkYT = true;}
      else if(ddYGgqxxUo == jrGTikehwF){oobjmKjhSM = true;}
      if(mihNsGDxWQ == SaOpGVEEnV){pWdDKPUqRi = true;}
      else if(SaOpGVEEnV == mihNsGDxWQ){OdDMFaBXDY = true;}
      if(mFZCkYRbaU == gKUHQhIGEh){HwygRoKLeQ = true;}
      else if(gKUHQhIGEh == mFZCkYRbaU){BVktzlSWMD = true;}
      if(OqVpRWOOAr == btAZNYYqVw){niSphiFTsW = true;}
      if(SIshMrVUcY == XRhgUdtpjE){QfEWEscxMx = true;}
      if(gsbSTdREiJ == LxcViTJQpy){LhcknGFfkR = true;}
      while(btAZNYYqVw == OqVpRWOOAr){BukeiVkPts = true;}
      while(XRhgUdtpjE == XRhgUdtpjE){WXOoMzUVVH = true;}
      while(LxcViTJQpy == LxcViTJQpy){MCrRwTEhkB = true;}
      if(hqrmNYZobg == true){hqrmNYZobg = false;}
      if(xMirxOcmml == true){xMirxOcmml = false;}
      if(mSVAVeQdpt == true){mSVAVeQdpt = false;}
      if(PHBWNgZtTw == true){PHBWNgZtTw = false;}
      if(DENCGzNkYT == true){DENCGzNkYT = false;}
      if(pWdDKPUqRi == true){pWdDKPUqRi = false;}
      if(HwygRoKLeQ == true){HwygRoKLeQ = false;}
      if(niSphiFTsW == true){niSphiFTsW = false;}
      if(QfEWEscxMx == true){QfEWEscxMx = false;}
      if(LhcknGFfkR == true){LhcknGFfkR = false;}
      if(nBFIeHDmUb == true){nBFIeHDmUb = false;}
      if(KByuSbrbcY == true){KByuSbrbcY = false;}
      if(LNzgEGFhBa == true){LNzgEGFhBa = false;}
      if(cYhbhOZwqx == true){cYhbhOZwqx = false;}
      if(oobjmKjhSM == true){oobjmKjhSM = false;}
      if(OdDMFaBXDY == true){OdDMFaBXDY = false;}
      if(BVktzlSWMD == true){BVktzlSWMD = false;}
      if(BukeiVkPts == true){BukeiVkPts = false;}
      if(WXOoMzUVVH == true){WXOoMzUVVH = false;}
      if(MCrRwTEhkB == true){MCrRwTEhkB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFYHFPRZPM
{ 
  void HPwzOpFPaz()
  { 
      bool OqzYttiwCp = false;
      bool yOMVyWOpZV = false;
      bool DdONjxntfd = false;
      bool HmUYbshmgQ = false;
      bool rVESqRCMuF = false;
      bool zdorSkbkow = false;
      bool FnPXiKsnsF = false;
      bool obJJdgZuWR = false;
      bool uayZdcycFq = false;
      bool RwxjKDFfif = false;
      bool YNTpQXUfNl = false;
      bool KfNWBdpotG = false;
      bool MPiBnrdYyZ = false;
      bool asMpsgHIJG = false;
      bool ISOTfkhaig = false;
      bool NPlcTIeRCY = false;
      bool twgnKRTWdT = false;
      bool WhfnytAPUC = false;
      bool JDpRMLHiWk = false;
      bool CpFkMLkaIO = false;
      string XXHEqoFsph;
      string YLCNknMuZS;
      string QPFxRWkkMi;
      string iTryqFZhGx;
      string EYAamXyRjy;
      string QQdboHRKmU;
      string ETgGzESEVe;
      string OdnbNqPdJt;
      string YSANSRoPJi;
      string mOulrkqsbh;
      string EsuEilcBOx;
      string rmAswkSTng;
      string PDumqziCic;
      string zWCboeXwdf;
      string omBLqAOCpH;
      string RXEuSAyIMi;
      string DaSlxUkXDQ;
      string MWoIrbCiuq;
      string kgLbLaRHJo;
      string gPitbOUONV;
      if(XXHEqoFsph == EsuEilcBOx){OqzYttiwCp = true;}
      else if(EsuEilcBOx == XXHEqoFsph){YNTpQXUfNl = true;}
      if(YLCNknMuZS == rmAswkSTng){yOMVyWOpZV = true;}
      else if(rmAswkSTng == YLCNknMuZS){KfNWBdpotG = true;}
      if(QPFxRWkkMi == PDumqziCic){DdONjxntfd = true;}
      else if(PDumqziCic == QPFxRWkkMi){MPiBnrdYyZ = true;}
      if(iTryqFZhGx == zWCboeXwdf){HmUYbshmgQ = true;}
      else if(zWCboeXwdf == iTryqFZhGx){asMpsgHIJG = true;}
      if(EYAamXyRjy == omBLqAOCpH){rVESqRCMuF = true;}
      else if(omBLqAOCpH == EYAamXyRjy){ISOTfkhaig = true;}
      if(QQdboHRKmU == RXEuSAyIMi){zdorSkbkow = true;}
      else if(RXEuSAyIMi == QQdboHRKmU){NPlcTIeRCY = true;}
      if(ETgGzESEVe == DaSlxUkXDQ){FnPXiKsnsF = true;}
      else if(DaSlxUkXDQ == ETgGzESEVe){twgnKRTWdT = true;}
      if(OdnbNqPdJt == MWoIrbCiuq){obJJdgZuWR = true;}
      if(YSANSRoPJi == kgLbLaRHJo){uayZdcycFq = true;}
      if(mOulrkqsbh == gPitbOUONV){RwxjKDFfif = true;}
      while(MWoIrbCiuq == OdnbNqPdJt){WhfnytAPUC = true;}
      while(kgLbLaRHJo == kgLbLaRHJo){JDpRMLHiWk = true;}
      while(gPitbOUONV == gPitbOUONV){CpFkMLkaIO = true;}
      if(OqzYttiwCp == true){OqzYttiwCp = false;}
      if(yOMVyWOpZV == true){yOMVyWOpZV = false;}
      if(DdONjxntfd == true){DdONjxntfd = false;}
      if(HmUYbshmgQ == true){HmUYbshmgQ = false;}
      if(rVESqRCMuF == true){rVESqRCMuF = false;}
      if(zdorSkbkow == true){zdorSkbkow = false;}
      if(FnPXiKsnsF == true){FnPXiKsnsF = false;}
      if(obJJdgZuWR == true){obJJdgZuWR = false;}
      if(uayZdcycFq == true){uayZdcycFq = false;}
      if(RwxjKDFfif == true){RwxjKDFfif = false;}
      if(YNTpQXUfNl == true){YNTpQXUfNl = false;}
      if(KfNWBdpotG == true){KfNWBdpotG = false;}
      if(MPiBnrdYyZ == true){MPiBnrdYyZ = false;}
      if(asMpsgHIJG == true){asMpsgHIJG = false;}
      if(ISOTfkhaig == true){ISOTfkhaig = false;}
      if(NPlcTIeRCY == true){NPlcTIeRCY = false;}
      if(twgnKRTWdT == true){twgnKRTWdT = false;}
      if(WhfnytAPUC == true){WhfnytAPUC = false;}
      if(JDpRMLHiWk == true){JDpRMLHiWk = false;}
      if(CpFkMLkaIO == true){CpFkMLkaIO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEOBPJZJHL
{ 
  void KOVBWIroLQ()
  { 
      bool ufdUxItOTT = false;
      bool ZamDfDQIbl = false;
      bool bnKVCNcQUI = false;
      bool UuryowzsRx = false;
      bool rcLJoajrro = false;
      bool oZYJXGUISj = false;
      bool fdtKzdhoNi = false;
      bool EXqdtycAfb = false;
      bool cjXeTuWhZh = false;
      bool bpahQNiAKK = false;
      bool rudIkRhtPZ = false;
      bool dTbpGuFOqE = false;
      bool HAPfHNwINf = false;
      bool ObpVjhGOtB = false;
      bool MbSzDHOjbU = false;
      bool ITJFDqeyBW = false;
      bool UYgiLCdGGX = false;
      bool opUpqegPbz = false;
      bool zMgrXtSjRr = false;
      bool CHNXfmujnB = false;
      string dPbUrBmJyx;
      string NkCPZqTeOx;
      string kziDQisHBG;
      string waCendipBm;
      string UMKkUgtejN;
      string EuyyRdfYEI;
      string IeIqBmhWbw;
      string HddbcYoyii;
      string nNWmBBcENJ;
      string xKkrdoDSig;
      string zXDmGaQVVs;
      string ohpUTuHVoA;
      string JdIRzxslym;
      string UVOBjQJjga;
      string kGhUTOUPXi;
      string ghciWUOlnI;
      string gdXhXTTnkD;
      string kXnOPDunyj;
      string cdNOGlredO;
      string BXuXsGhAwz;
      if(dPbUrBmJyx == zXDmGaQVVs){ufdUxItOTT = true;}
      else if(zXDmGaQVVs == dPbUrBmJyx){rudIkRhtPZ = true;}
      if(NkCPZqTeOx == ohpUTuHVoA){ZamDfDQIbl = true;}
      else if(ohpUTuHVoA == NkCPZqTeOx){dTbpGuFOqE = true;}
      if(kziDQisHBG == JdIRzxslym){bnKVCNcQUI = true;}
      else if(JdIRzxslym == kziDQisHBG){HAPfHNwINf = true;}
      if(waCendipBm == UVOBjQJjga){UuryowzsRx = true;}
      else if(UVOBjQJjga == waCendipBm){ObpVjhGOtB = true;}
      if(UMKkUgtejN == kGhUTOUPXi){rcLJoajrro = true;}
      else if(kGhUTOUPXi == UMKkUgtejN){MbSzDHOjbU = true;}
      if(EuyyRdfYEI == ghciWUOlnI){oZYJXGUISj = true;}
      else if(ghciWUOlnI == EuyyRdfYEI){ITJFDqeyBW = true;}
      if(IeIqBmhWbw == gdXhXTTnkD){fdtKzdhoNi = true;}
      else if(gdXhXTTnkD == IeIqBmhWbw){UYgiLCdGGX = true;}
      if(HddbcYoyii == kXnOPDunyj){EXqdtycAfb = true;}
      if(nNWmBBcENJ == cdNOGlredO){cjXeTuWhZh = true;}
      if(xKkrdoDSig == BXuXsGhAwz){bpahQNiAKK = true;}
      while(kXnOPDunyj == HddbcYoyii){opUpqegPbz = true;}
      while(cdNOGlredO == cdNOGlredO){zMgrXtSjRr = true;}
      while(BXuXsGhAwz == BXuXsGhAwz){CHNXfmujnB = true;}
      if(ufdUxItOTT == true){ufdUxItOTT = false;}
      if(ZamDfDQIbl == true){ZamDfDQIbl = false;}
      if(bnKVCNcQUI == true){bnKVCNcQUI = false;}
      if(UuryowzsRx == true){UuryowzsRx = false;}
      if(rcLJoajrro == true){rcLJoajrro = false;}
      if(oZYJXGUISj == true){oZYJXGUISj = false;}
      if(fdtKzdhoNi == true){fdtKzdhoNi = false;}
      if(EXqdtycAfb == true){EXqdtycAfb = false;}
      if(cjXeTuWhZh == true){cjXeTuWhZh = false;}
      if(bpahQNiAKK == true){bpahQNiAKK = false;}
      if(rudIkRhtPZ == true){rudIkRhtPZ = false;}
      if(dTbpGuFOqE == true){dTbpGuFOqE = false;}
      if(HAPfHNwINf == true){HAPfHNwINf = false;}
      if(ObpVjhGOtB == true){ObpVjhGOtB = false;}
      if(MbSzDHOjbU == true){MbSzDHOjbU = false;}
      if(ITJFDqeyBW == true){ITJFDqeyBW = false;}
      if(UYgiLCdGGX == true){UYgiLCdGGX = false;}
      if(opUpqegPbz == true){opUpqegPbz = false;}
      if(zMgrXtSjRr == true){zMgrXtSjRr = false;}
      if(CHNXfmujnB == true){CHNXfmujnB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KHSLZBQFLF
{ 
  void TxHBcMXxxX()
  { 
      bool sBJtPsJGju = false;
      bool lFjutilLWU = false;
      bool UAiaOIKjLe = false;
      bool ohWChHLKAZ = false;
      bool iSwKHoeRma = false;
      bool KAHGXrRieG = false;
      bool iZuEGEhhNl = false;
      bool WbKxkCDXTY = false;
      bool drxjUoZQdo = false;
      bool ocesqJXrED = false;
      bool HwEAEhoJUV = false;
      bool otOFbpbKjQ = false;
      bool eRDXxtxQGb = false;
      bool eLTQRhnxfl = false;
      bool AQuIzuNYRA = false;
      bool gMImYorfDJ = false;
      bool kXCrpcZynt = false;
      bool BdexQNVuXB = false;
      bool gXzFuSDgrb = false;
      bool oItVBcNCRV = false;
      string wrGawTuNeU;
      string HGPUuwksor;
      string TizaktshXZ;
      string QDcFzsOlSg;
      string kTSfmKCjZk;
      string EbmhhNsepC;
      string aNoFEDcKUC;
      string hyZIHzPTma;
      string qIHmUoQuWl;
      string AiwPFWdNaj;
      string gqOXCGBdZh;
      string xZrPKRGCjP;
      string mhmiBzBJDj;
      string UCrDsAtijO;
      string nlUnnapfFm;
      string QbcLwzEeVD;
      string EqapNugoVK;
      string XXRVbAMyua;
      string IVEPSsZgGt;
      string uOMgJwLeas;
      if(wrGawTuNeU == gqOXCGBdZh){sBJtPsJGju = true;}
      else if(gqOXCGBdZh == wrGawTuNeU){HwEAEhoJUV = true;}
      if(HGPUuwksor == xZrPKRGCjP){lFjutilLWU = true;}
      else if(xZrPKRGCjP == HGPUuwksor){otOFbpbKjQ = true;}
      if(TizaktshXZ == mhmiBzBJDj){UAiaOIKjLe = true;}
      else if(mhmiBzBJDj == TizaktshXZ){eRDXxtxQGb = true;}
      if(QDcFzsOlSg == UCrDsAtijO){ohWChHLKAZ = true;}
      else if(UCrDsAtijO == QDcFzsOlSg){eLTQRhnxfl = true;}
      if(kTSfmKCjZk == nlUnnapfFm){iSwKHoeRma = true;}
      else if(nlUnnapfFm == kTSfmKCjZk){AQuIzuNYRA = true;}
      if(EbmhhNsepC == QbcLwzEeVD){KAHGXrRieG = true;}
      else if(QbcLwzEeVD == EbmhhNsepC){gMImYorfDJ = true;}
      if(aNoFEDcKUC == EqapNugoVK){iZuEGEhhNl = true;}
      else if(EqapNugoVK == aNoFEDcKUC){kXCrpcZynt = true;}
      if(hyZIHzPTma == XXRVbAMyua){WbKxkCDXTY = true;}
      if(qIHmUoQuWl == IVEPSsZgGt){drxjUoZQdo = true;}
      if(AiwPFWdNaj == uOMgJwLeas){ocesqJXrED = true;}
      while(XXRVbAMyua == hyZIHzPTma){BdexQNVuXB = true;}
      while(IVEPSsZgGt == IVEPSsZgGt){gXzFuSDgrb = true;}
      while(uOMgJwLeas == uOMgJwLeas){oItVBcNCRV = true;}
      if(sBJtPsJGju == true){sBJtPsJGju = false;}
      if(lFjutilLWU == true){lFjutilLWU = false;}
      if(UAiaOIKjLe == true){UAiaOIKjLe = false;}
      if(ohWChHLKAZ == true){ohWChHLKAZ = false;}
      if(iSwKHoeRma == true){iSwKHoeRma = false;}
      if(KAHGXrRieG == true){KAHGXrRieG = false;}
      if(iZuEGEhhNl == true){iZuEGEhhNl = false;}
      if(WbKxkCDXTY == true){WbKxkCDXTY = false;}
      if(drxjUoZQdo == true){drxjUoZQdo = false;}
      if(ocesqJXrED == true){ocesqJXrED = false;}
      if(HwEAEhoJUV == true){HwEAEhoJUV = false;}
      if(otOFbpbKjQ == true){otOFbpbKjQ = false;}
      if(eRDXxtxQGb == true){eRDXxtxQGb = false;}
      if(eLTQRhnxfl == true){eLTQRhnxfl = false;}
      if(AQuIzuNYRA == true){AQuIzuNYRA = false;}
      if(gMImYorfDJ == true){gMImYorfDJ = false;}
      if(kXCrpcZynt == true){kXCrpcZynt = false;}
      if(BdexQNVuXB == true){BdexQNVuXB = false;}
      if(gXzFuSDgrb == true){gXzFuSDgrb = false;}
      if(oItVBcNCRV == true){oItVBcNCRV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCIWHOSFTN
{ 
  void XQMzdVhunH()
  { 
      bool XKqKkErZnD = false;
      bool HYuHIrhMhR = false;
      bool UVAQyNGwTR = false;
      bool IUEnUOyNGN = false;
      bool QbaPZTycxg = false;
      bool FGdarBKaLW = false;
      bool xuFWtmTGmt = false;
      bool tTGUBstjpe = false;
      bool PczmMCqcuS = false;
      bool EWBiPVVEUl = false;
      bool AqpCmkAIZz = false;
      bool GZkgHTuSKr = false;
      bool wpLUpWRWEf = false;
      bool XpOEdYmxAa = false;
      bool BhDwLdlUbw = false;
      bool ZDscpKfVLP = false;
      bool TcDtbQKgCi = false;
      bool fxRjpNlOIM = false;
      bool kxuIFTwlNT = false;
      bool sRlkHXdJTu = false;
      string gOfmhHRWIW;
      string sDpiIxeLtk;
      string qsSeLSfyHf;
      string wdgVQAymYS;
      string tBzRxELCKi;
      string HUQFVmuBbO;
      string aSObZOVTRH;
      string zrlbppsAhG;
      string HcnXYbNbAd;
      string ExLKqalXqh;
      string iqkCjPhoOe;
      string suSVHydqDy;
      string BtTmCCfbjO;
      string EVIzWPqlnI;
      string sYMUkJdpCr;
      string xuTsfoWxAh;
      string iGEAaWlTyq;
      string HrCtEcgyCr;
      string YpYqRIBPTh;
      string rskGZmTMsN;
      if(gOfmhHRWIW == iqkCjPhoOe){XKqKkErZnD = true;}
      else if(iqkCjPhoOe == gOfmhHRWIW){AqpCmkAIZz = true;}
      if(sDpiIxeLtk == suSVHydqDy){HYuHIrhMhR = true;}
      else if(suSVHydqDy == sDpiIxeLtk){GZkgHTuSKr = true;}
      if(qsSeLSfyHf == BtTmCCfbjO){UVAQyNGwTR = true;}
      else if(BtTmCCfbjO == qsSeLSfyHf){wpLUpWRWEf = true;}
      if(wdgVQAymYS == EVIzWPqlnI){IUEnUOyNGN = true;}
      else if(EVIzWPqlnI == wdgVQAymYS){XpOEdYmxAa = true;}
      if(tBzRxELCKi == sYMUkJdpCr){QbaPZTycxg = true;}
      else if(sYMUkJdpCr == tBzRxELCKi){BhDwLdlUbw = true;}
      if(HUQFVmuBbO == xuTsfoWxAh){FGdarBKaLW = true;}
      else if(xuTsfoWxAh == HUQFVmuBbO){ZDscpKfVLP = true;}
      if(aSObZOVTRH == iGEAaWlTyq){xuFWtmTGmt = true;}
      else if(iGEAaWlTyq == aSObZOVTRH){TcDtbQKgCi = true;}
      if(zrlbppsAhG == HrCtEcgyCr){tTGUBstjpe = true;}
      if(HcnXYbNbAd == YpYqRIBPTh){PczmMCqcuS = true;}
      if(ExLKqalXqh == rskGZmTMsN){EWBiPVVEUl = true;}
      while(HrCtEcgyCr == zrlbppsAhG){fxRjpNlOIM = true;}
      while(YpYqRIBPTh == YpYqRIBPTh){kxuIFTwlNT = true;}
      while(rskGZmTMsN == rskGZmTMsN){sRlkHXdJTu = true;}
      if(XKqKkErZnD == true){XKqKkErZnD = false;}
      if(HYuHIrhMhR == true){HYuHIrhMhR = false;}
      if(UVAQyNGwTR == true){UVAQyNGwTR = false;}
      if(IUEnUOyNGN == true){IUEnUOyNGN = false;}
      if(QbaPZTycxg == true){QbaPZTycxg = false;}
      if(FGdarBKaLW == true){FGdarBKaLW = false;}
      if(xuFWtmTGmt == true){xuFWtmTGmt = false;}
      if(tTGUBstjpe == true){tTGUBstjpe = false;}
      if(PczmMCqcuS == true){PczmMCqcuS = false;}
      if(EWBiPVVEUl == true){EWBiPVVEUl = false;}
      if(AqpCmkAIZz == true){AqpCmkAIZz = false;}
      if(GZkgHTuSKr == true){GZkgHTuSKr = false;}
      if(wpLUpWRWEf == true){wpLUpWRWEf = false;}
      if(XpOEdYmxAa == true){XpOEdYmxAa = false;}
      if(BhDwLdlUbw == true){BhDwLdlUbw = false;}
      if(ZDscpKfVLP == true){ZDscpKfVLP = false;}
      if(TcDtbQKgCi == true){TcDtbQKgCi = false;}
      if(fxRjpNlOIM == true){fxRjpNlOIM = false;}
      if(kxuIFTwlNT == true){kxuIFTwlNT = false;}
      if(sRlkHXdJTu == true){sRlkHXdJTu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACQWNOSHHO
{ 
  void hikHEuRaow()
  { 
      bool ssHImgOlaU = false;
      bool ZUAXrKLeJH = false;
      bool wmDSLYyDiG = false;
      bool hXhygXTSRg = false;
      bool ssXzaqCXDj = false;
      bool qiWooGpoxN = false;
      bool hKDTlCmCqT = false;
      bool psMcNDOErU = false;
      bool WazyPzBrIa = false;
      bool heVEyipEMY = false;
      bool EAgjsxVtal = false;
      bool qlwcqHKEDm = false;
      bool BttPlLWIde = false;
      bool NKqTPVsPFS = false;
      bool cGRWjuhsNp = false;
      bool XkBYWKGQxh = false;
      bool ZMPwYftcMU = false;
      bool OuzkJtcWfp = false;
      bool ddunHbJRwF = false;
      bool PbRWrQqUxD = false;
      string XpRpNmLKZC;
      string KNKXCwZbaX;
      string PcyJZcwREs;
      string MLoXjsjrBX;
      string MZGbKJbXPF;
      string WXIXauqIQj;
      string psFgpyXmnJ;
      string LgZCKpVVyQ;
      string AYCzWoDQwn;
      string CbbQhTTZlM;
      string kojGspxFNk;
      string YVJziRqFJB;
      string uGpzHiEJUp;
      string VwileLnuGf;
      string qyDLOfRbgP;
      string cNPkRdzkzJ;
      string lnjWOclXUX;
      string cuzcJwDdja;
      string RbbENHfyUB;
      string LDwwtDNfwl;
      if(XpRpNmLKZC == kojGspxFNk){ssHImgOlaU = true;}
      else if(kojGspxFNk == XpRpNmLKZC){EAgjsxVtal = true;}
      if(KNKXCwZbaX == YVJziRqFJB){ZUAXrKLeJH = true;}
      else if(YVJziRqFJB == KNKXCwZbaX){qlwcqHKEDm = true;}
      if(PcyJZcwREs == uGpzHiEJUp){wmDSLYyDiG = true;}
      else if(uGpzHiEJUp == PcyJZcwREs){BttPlLWIde = true;}
      if(MLoXjsjrBX == VwileLnuGf){hXhygXTSRg = true;}
      else if(VwileLnuGf == MLoXjsjrBX){NKqTPVsPFS = true;}
      if(MZGbKJbXPF == qyDLOfRbgP){ssXzaqCXDj = true;}
      else if(qyDLOfRbgP == MZGbKJbXPF){cGRWjuhsNp = true;}
      if(WXIXauqIQj == cNPkRdzkzJ){qiWooGpoxN = true;}
      else if(cNPkRdzkzJ == WXIXauqIQj){XkBYWKGQxh = true;}
      if(psFgpyXmnJ == lnjWOclXUX){hKDTlCmCqT = true;}
      else if(lnjWOclXUX == psFgpyXmnJ){ZMPwYftcMU = true;}
      if(LgZCKpVVyQ == cuzcJwDdja){psMcNDOErU = true;}
      if(AYCzWoDQwn == RbbENHfyUB){WazyPzBrIa = true;}
      if(CbbQhTTZlM == LDwwtDNfwl){heVEyipEMY = true;}
      while(cuzcJwDdja == LgZCKpVVyQ){OuzkJtcWfp = true;}
      while(RbbENHfyUB == RbbENHfyUB){ddunHbJRwF = true;}
      while(LDwwtDNfwl == LDwwtDNfwl){PbRWrQqUxD = true;}
      if(ssHImgOlaU == true){ssHImgOlaU = false;}
      if(ZUAXrKLeJH == true){ZUAXrKLeJH = false;}
      if(wmDSLYyDiG == true){wmDSLYyDiG = false;}
      if(hXhygXTSRg == true){hXhygXTSRg = false;}
      if(ssXzaqCXDj == true){ssXzaqCXDj = false;}
      if(qiWooGpoxN == true){qiWooGpoxN = false;}
      if(hKDTlCmCqT == true){hKDTlCmCqT = false;}
      if(psMcNDOErU == true){psMcNDOErU = false;}
      if(WazyPzBrIa == true){WazyPzBrIa = false;}
      if(heVEyipEMY == true){heVEyipEMY = false;}
      if(EAgjsxVtal == true){EAgjsxVtal = false;}
      if(qlwcqHKEDm == true){qlwcqHKEDm = false;}
      if(BttPlLWIde == true){BttPlLWIde = false;}
      if(NKqTPVsPFS == true){NKqTPVsPFS = false;}
      if(cGRWjuhsNp == true){cGRWjuhsNp = false;}
      if(XkBYWKGQxh == true){XkBYWKGQxh = false;}
      if(ZMPwYftcMU == true){ZMPwYftcMU = false;}
      if(OuzkJtcWfp == true){OuzkJtcWfp = false;}
      if(ddunHbJRwF == true){ddunHbJRwF = false;}
      if(PbRWrQqUxD == true){PbRWrQqUxD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZRTRLAPVR
{ 
  void wnSKLyjyNi()
  { 
      bool btbaMsHIlA = false;
      bool cyxKJcwNff = false;
      bool yqpeToZbyD = false;
      bool flPuxNVRPL = false;
      bool EfWhEBgnQa = false;
      bool uSStKkDwGX = false;
      bool TfKiUqhCNw = false;
      bool GexUbSTHaS = false;
      bool HkKXIMSVjL = false;
      bool JZKqqXVnNM = false;
      bool SeaUTPUySr = false;
      bool QwUnQiUlZH = false;
      bool YMRBlgTFdD = false;
      bool wetOzbKoDr = false;
      bool qUDruNFWaH = false;
      bool CiNGmFNYim = false;
      bool wPTOukCFnn = false;
      bool YfihPEJYGX = false;
      bool bxeVAMRmas = false;
      bool OkGQwbAnwJ = false;
      string igCYXOHfNN;
      string WRPChNarMD;
      string TEprhbbdwp;
      string dQBYPLxoAU;
      string EpOrBAoqIJ;
      string yUsHrdpKqw;
      string ldiXjGPpmW;
      string Pkrrycpypg;
      string mkUmqIXsgk;
      string UmyEhaGpHu;
      string kyDltNcAIO;
      string mqTJIBIwfa;
      string iVJBCblnKX;
      string Wzquwogisd;
      string fWkSxcToug;
      string SKKgMOoCjR;
      string aopkrnAYNT;
      string TYCBtLkpEY;
      string IxrcELoJhh;
      string zezaDqfzaJ;
      if(igCYXOHfNN == kyDltNcAIO){btbaMsHIlA = true;}
      else if(kyDltNcAIO == igCYXOHfNN){SeaUTPUySr = true;}
      if(WRPChNarMD == mqTJIBIwfa){cyxKJcwNff = true;}
      else if(mqTJIBIwfa == WRPChNarMD){QwUnQiUlZH = true;}
      if(TEprhbbdwp == iVJBCblnKX){yqpeToZbyD = true;}
      else if(iVJBCblnKX == TEprhbbdwp){YMRBlgTFdD = true;}
      if(dQBYPLxoAU == Wzquwogisd){flPuxNVRPL = true;}
      else if(Wzquwogisd == dQBYPLxoAU){wetOzbKoDr = true;}
      if(EpOrBAoqIJ == fWkSxcToug){EfWhEBgnQa = true;}
      else if(fWkSxcToug == EpOrBAoqIJ){qUDruNFWaH = true;}
      if(yUsHrdpKqw == SKKgMOoCjR){uSStKkDwGX = true;}
      else if(SKKgMOoCjR == yUsHrdpKqw){CiNGmFNYim = true;}
      if(ldiXjGPpmW == aopkrnAYNT){TfKiUqhCNw = true;}
      else if(aopkrnAYNT == ldiXjGPpmW){wPTOukCFnn = true;}
      if(Pkrrycpypg == TYCBtLkpEY){GexUbSTHaS = true;}
      if(mkUmqIXsgk == IxrcELoJhh){HkKXIMSVjL = true;}
      if(UmyEhaGpHu == zezaDqfzaJ){JZKqqXVnNM = true;}
      while(TYCBtLkpEY == Pkrrycpypg){YfihPEJYGX = true;}
      while(IxrcELoJhh == IxrcELoJhh){bxeVAMRmas = true;}
      while(zezaDqfzaJ == zezaDqfzaJ){OkGQwbAnwJ = true;}
      if(btbaMsHIlA == true){btbaMsHIlA = false;}
      if(cyxKJcwNff == true){cyxKJcwNff = false;}
      if(yqpeToZbyD == true){yqpeToZbyD = false;}
      if(flPuxNVRPL == true){flPuxNVRPL = false;}
      if(EfWhEBgnQa == true){EfWhEBgnQa = false;}
      if(uSStKkDwGX == true){uSStKkDwGX = false;}
      if(TfKiUqhCNw == true){TfKiUqhCNw = false;}
      if(GexUbSTHaS == true){GexUbSTHaS = false;}
      if(HkKXIMSVjL == true){HkKXIMSVjL = false;}
      if(JZKqqXVnNM == true){JZKqqXVnNM = false;}
      if(SeaUTPUySr == true){SeaUTPUySr = false;}
      if(QwUnQiUlZH == true){QwUnQiUlZH = false;}
      if(YMRBlgTFdD == true){YMRBlgTFdD = false;}
      if(wetOzbKoDr == true){wetOzbKoDr = false;}
      if(qUDruNFWaH == true){qUDruNFWaH = false;}
      if(CiNGmFNYim == true){CiNGmFNYim = false;}
      if(wPTOukCFnn == true){wPTOukCFnn = false;}
      if(YfihPEJYGX == true){YfihPEJYGX = false;}
      if(bxeVAMRmas == true){bxeVAMRmas = false;}
      if(OkGQwbAnwJ == true){OkGQwbAnwJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWIGAGSZZB
{ 
  void YSVTRnfsij()
  { 
      bool iWzEiHexDq = false;
      bool RlkiNWzsFn = false;
      bool khEIfPqKNI = false;
      bool FAVTAndNFM = false;
      bool hMAOAwMrEO = false;
      bool TByXGARqXT = false;
      bool QUitlQQRiZ = false;
      bool rlmrFYgpHj = false;
      bool DyGynDCxNz = false;
      bool WmolwNcFbj = false;
      bool fuJdWhNFSh = false;
      bool TainQRNkGi = false;
      bool OSEjCExBwq = false;
      bool uaNXEHobbG = false;
      bool oweffuEAVe = false;
      bool zrzsVMqZbR = false;
      bool kMJalrMLjI = false;
      bool clIAsRnXDH = false;
      bool AwfQqCbUCq = false;
      bool QOAJUclDsm = false;
      string EbGECiGtaT;
      string tgkekKCtAo;
      string HIbZpPgfOt;
      string POxFmpYGXI;
      string LIQyDrwnQD;
      string CaOyUwzgOl;
      string BaefDejfqt;
      string kwWrdyrdWx;
      string TrPKroAzjq;
      string prqkGjcjtX;
      string HQxVSFDVTW;
      string DVKQRJLUmO;
      string ekuzDsEkls;
      string VHiyoDusrm;
      string leeNnUhaTx;
      string YHxfrWUxRY;
      string ARiZBwlLaO;
      string NRcAcAFhLi;
      string KdRoTNKDGS;
      string hyaSlTuELr;
      if(EbGECiGtaT == HQxVSFDVTW){iWzEiHexDq = true;}
      else if(HQxVSFDVTW == EbGECiGtaT){fuJdWhNFSh = true;}
      if(tgkekKCtAo == DVKQRJLUmO){RlkiNWzsFn = true;}
      else if(DVKQRJLUmO == tgkekKCtAo){TainQRNkGi = true;}
      if(HIbZpPgfOt == ekuzDsEkls){khEIfPqKNI = true;}
      else if(ekuzDsEkls == HIbZpPgfOt){OSEjCExBwq = true;}
      if(POxFmpYGXI == VHiyoDusrm){FAVTAndNFM = true;}
      else if(VHiyoDusrm == POxFmpYGXI){uaNXEHobbG = true;}
      if(LIQyDrwnQD == leeNnUhaTx){hMAOAwMrEO = true;}
      else if(leeNnUhaTx == LIQyDrwnQD){oweffuEAVe = true;}
      if(CaOyUwzgOl == YHxfrWUxRY){TByXGARqXT = true;}
      else if(YHxfrWUxRY == CaOyUwzgOl){zrzsVMqZbR = true;}
      if(BaefDejfqt == ARiZBwlLaO){QUitlQQRiZ = true;}
      else if(ARiZBwlLaO == BaefDejfqt){kMJalrMLjI = true;}
      if(kwWrdyrdWx == NRcAcAFhLi){rlmrFYgpHj = true;}
      if(TrPKroAzjq == KdRoTNKDGS){DyGynDCxNz = true;}
      if(prqkGjcjtX == hyaSlTuELr){WmolwNcFbj = true;}
      while(NRcAcAFhLi == kwWrdyrdWx){clIAsRnXDH = true;}
      while(KdRoTNKDGS == KdRoTNKDGS){AwfQqCbUCq = true;}
      while(hyaSlTuELr == hyaSlTuELr){QOAJUclDsm = true;}
      if(iWzEiHexDq == true){iWzEiHexDq = false;}
      if(RlkiNWzsFn == true){RlkiNWzsFn = false;}
      if(khEIfPqKNI == true){khEIfPqKNI = false;}
      if(FAVTAndNFM == true){FAVTAndNFM = false;}
      if(hMAOAwMrEO == true){hMAOAwMrEO = false;}
      if(TByXGARqXT == true){TByXGARqXT = false;}
      if(QUitlQQRiZ == true){QUitlQQRiZ = false;}
      if(rlmrFYgpHj == true){rlmrFYgpHj = false;}
      if(DyGynDCxNz == true){DyGynDCxNz = false;}
      if(WmolwNcFbj == true){WmolwNcFbj = false;}
      if(fuJdWhNFSh == true){fuJdWhNFSh = false;}
      if(TainQRNkGi == true){TainQRNkGi = false;}
      if(OSEjCExBwq == true){OSEjCExBwq = false;}
      if(uaNXEHobbG == true){uaNXEHobbG = false;}
      if(oweffuEAVe == true){oweffuEAVe = false;}
      if(zrzsVMqZbR == true){zrzsVMqZbR = false;}
      if(kMJalrMLjI == true){kMJalrMLjI = false;}
      if(clIAsRnXDH == true){clIAsRnXDH = false;}
      if(AwfQqCbUCq == true){AwfQqCbUCq = false;}
      if(QOAJUclDsm == true){QOAJUclDsm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZWBSTBZQJ
{ 
  void irBNqcsZIX()
  { 
      bool IPHAPJYaDb = false;
      bool RYSCOcrDVl = false;
      bool sQTiWqRAdK = false;
      bool NdeasywUYp = false;
      bool VasSqmExtA = false;
      bool RQsgHruXcY = false;
      bool qXwsNnsrJP = false;
      bool gXdeQRWBqi = false;
      bool mUFdsxjySA = false;
      bool DXqAyxdzED = false;
      bool sMmeSslNQo = false;
      bool VtftkWSSAQ = false;
      bool DuYIMJgdgS = false;
      bool nWwnoagaLz = false;
      bool KWgdeIqwOa = false;
      bool dKzmzxmeRI = false;
      bool MIfxByxrEK = false;
      bool prHAGgOudD = false;
      bool RjOFncXJnq = false;
      bool mCIClBpicg = false;
      string UGCUUNAQJu;
      string kMgrHKupHe;
      string iBjcCqytOw;
      string ORCXtbWeha;
      string FdOxVwhPJI;
      string BZsVOSVZSd;
      string PGBNgSJJye;
      string nQHfYFllHG;
      string JijGunYgJa;
      string GwMDLycBQD;
      string mXQeUjRMwI;
      string fiSMUfWuSr;
      string sczWYrDEUa;
      string bkVETkRFkK;
      string WLjAuWdAie;
      string ahiYJJYtFb;
      string gMrVguNOri;
      string ORJHUgrzaC;
      string NDUoztBxtJ;
      string MWzJdJTOTA;
      if(UGCUUNAQJu == mXQeUjRMwI){IPHAPJYaDb = true;}
      else if(mXQeUjRMwI == UGCUUNAQJu){sMmeSslNQo = true;}
      if(kMgrHKupHe == fiSMUfWuSr){RYSCOcrDVl = true;}
      else if(fiSMUfWuSr == kMgrHKupHe){VtftkWSSAQ = true;}
      if(iBjcCqytOw == sczWYrDEUa){sQTiWqRAdK = true;}
      else if(sczWYrDEUa == iBjcCqytOw){DuYIMJgdgS = true;}
      if(ORCXtbWeha == bkVETkRFkK){NdeasywUYp = true;}
      else if(bkVETkRFkK == ORCXtbWeha){nWwnoagaLz = true;}
      if(FdOxVwhPJI == WLjAuWdAie){VasSqmExtA = true;}
      else if(WLjAuWdAie == FdOxVwhPJI){KWgdeIqwOa = true;}
      if(BZsVOSVZSd == ahiYJJYtFb){RQsgHruXcY = true;}
      else if(ahiYJJYtFb == BZsVOSVZSd){dKzmzxmeRI = true;}
      if(PGBNgSJJye == gMrVguNOri){qXwsNnsrJP = true;}
      else if(gMrVguNOri == PGBNgSJJye){MIfxByxrEK = true;}
      if(nQHfYFllHG == ORJHUgrzaC){gXdeQRWBqi = true;}
      if(JijGunYgJa == NDUoztBxtJ){mUFdsxjySA = true;}
      if(GwMDLycBQD == MWzJdJTOTA){DXqAyxdzED = true;}
      while(ORJHUgrzaC == nQHfYFllHG){prHAGgOudD = true;}
      while(NDUoztBxtJ == NDUoztBxtJ){RjOFncXJnq = true;}
      while(MWzJdJTOTA == MWzJdJTOTA){mCIClBpicg = true;}
      if(IPHAPJYaDb == true){IPHAPJYaDb = false;}
      if(RYSCOcrDVl == true){RYSCOcrDVl = false;}
      if(sQTiWqRAdK == true){sQTiWqRAdK = false;}
      if(NdeasywUYp == true){NdeasywUYp = false;}
      if(VasSqmExtA == true){VasSqmExtA = false;}
      if(RQsgHruXcY == true){RQsgHruXcY = false;}
      if(qXwsNnsrJP == true){qXwsNnsrJP = false;}
      if(gXdeQRWBqi == true){gXdeQRWBqi = false;}
      if(mUFdsxjySA == true){mUFdsxjySA = false;}
      if(DXqAyxdzED == true){DXqAyxdzED = false;}
      if(sMmeSslNQo == true){sMmeSslNQo = false;}
      if(VtftkWSSAQ == true){VtftkWSSAQ = false;}
      if(DuYIMJgdgS == true){DuYIMJgdgS = false;}
      if(nWwnoagaLz == true){nWwnoagaLz = false;}
      if(KWgdeIqwOa == true){KWgdeIqwOa = false;}
      if(dKzmzxmeRI == true){dKzmzxmeRI = false;}
      if(MIfxByxrEK == true){MIfxByxrEK = false;}
      if(prHAGgOudD == true){prHAGgOudD = false;}
      if(RjOFncXJnq == true){RjOFncXJnq = false;}
      if(mCIClBpicg == true){mCIClBpicg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCFOSQCCJT
{ 
  void VsBmKPdOhS()
  { 
      bool qlJIPiVAJA = false;
      bool UGwVgtpyYX = false;
      bool xrCojgYUVX = false;
      bool kYRIlpRpHN = false;
      bool iAtwenCmZL = false;
      bool mgIJQyjUXi = false;
      bool KBekPwoniq = false;
      bool czpKowyFKw = false;
      bool dktJkDPHqn = false;
      bool FxRYDhVIfh = false;
      bool yOEiinqyUT = false;
      bool AdJbEYGVAM = false;
      bool ggwukfgQGH = false;
      bool aoYbxOfLax = false;
      bool LQmWmbmpTd = false;
      bool aAITBQSJxD = false;
      bool GaqNsLFgep = false;
      bool rtuDBPtYHJ = false;
      bool rqwcfZfFaf = false;
      bool wWOWpjZYdb = false;
      string DfAUbDMEoi;
      string DrOxIVgUUr;
      string UReosenyWM;
      string XtuPZwJpPH;
      string VZInrhOWai;
      string mfCHakAKaw;
      string ONhcKJxyWL;
      string LpFMWuJqxL;
      string QRXnYrqnon;
      string wyPSsHrfci;
      string jPAOWxaoje;
      string bJNPfxpsDS;
      string RJJhPNalTO;
      string CdNOaBQIQb;
      string RBDJMlkzmw;
      string RybKQaGRzJ;
      string VnVVbyuzoe;
      string fhbaBQFzVc;
      string bbyXxEBDxz;
      string tzJHFcfghN;
      if(DfAUbDMEoi == jPAOWxaoje){qlJIPiVAJA = true;}
      else if(jPAOWxaoje == DfAUbDMEoi){yOEiinqyUT = true;}
      if(DrOxIVgUUr == bJNPfxpsDS){UGwVgtpyYX = true;}
      else if(bJNPfxpsDS == DrOxIVgUUr){AdJbEYGVAM = true;}
      if(UReosenyWM == RJJhPNalTO){xrCojgYUVX = true;}
      else if(RJJhPNalTO == UReosenyWM){ggwukfgQGH = true;}
      if(XtuPZwJpPH == CdNOaBQIQb){kYRIlpRpHN = true;}
      else if(CdNOaBQIQb == XtuPZwJpPH){aoYbxOfLax = true;}
      if(VZInrhOWai == RBDJMlkzmw){iAtwenCmZL = true;}
      else if(RBDJMlkzmw == VZInrhOWai){LQmWmbmpTd = true;}
      if(mfCHakAKaw == RybKQaGRzJ){mgIJQyjUXi = true;}
      else if(RybKQaGRzJ == mfCHakAKaw){aAITBQSJxD = true;}
      if(ONhcKJxyWL == VnVVbyuzoe){KBekPwoniq = true;}
      else if(VnVVbyuzoe == ONhcKJxyWL){GaqNsLFgep = true;}
      if(LpFMWuJqxL == fhbaBQFzVc){czpKowyFKw = true;}
      if(QRXnYrqnon == bbyXxEBDxz){dktJkDPHqn = true;}
      if(wyPSsHrfci == tzJHFcfghN){FxRYDhVIfh = true;}
      while(fhbaBQFzVc == LpFMWuJqxL){rtuDBPtYHJ = true;}
      while(bbyXxEBDxz == bbyXxEBDxz){rqwcfZfFaf = true;}
      while(tzJHFcfghN == tzJHFcfghN){wWOWpjZYdb = true;}
      if(qlJIPiVAJA == true){qlJIPiVAJA = false;}
      if(UGwVgtpyYX == true){UGwVgtpyYX = false;}
      if(xrCojgYUVX == true){xrCojgYUVX = false;}
      if(kYRIlpRpHN == true){kYRIlpRpHN = false;}
      if(iAtwenCmZL == true){iAtwenCmZL = false;}
      if(mgIJQyjUXi == true){mgIJQyjUXi = false;}
      if(KBekPwoniq == true){KBekPwoniq = false;}
      if(czpKowyFKw == true){czpKowyFKw = false;}
      if(dktJkDPHqn == true){dktJkDPHqn = false;}
      if(FxRYDhVIfh == true){FxRYDhVIfh = false;}
      if(yOEiinqyUT == true){yOEiinqyUT = false;}
      if(AdJbEYGVAM == true){AdJbEYGVAM = false;}
      if(ggwukfgQGH == true){ggwukfgQGH = false;}
      if(aoYbxOfLax == true){aoYbxOfLax = false;}
      if(LQmWmbmpTd == true){LQmWmbmpTd = false;}
      if(aAITBQSJxD == true){aAITBQSJxD = false;}
      if(GaqNsLFgep == true){GaqNsLFgep = false;}
      if(rtuDBPtYHJ == true){rtuDBPtYHJ = false;}
      if(rqwcfZfFaf == true){rqwcfZfFaf = false;}
      if(wWOWpjZYdb == true){wWOWpjZYdb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZKEBXEDIKJ
{ 
  void kEUJztjPyU()
  { 
      bool uapNSNRWXO = false;
      bool SEedZGjrrE = false;
      bool NMFEhHrzeD = false;
      bool ZRkGqJNmnl = false;
      bool VMTNzOMzSd = false;
      bool abJcCiVkeL = false;
      bool USqTnATXmP = false;
      bool rxDFiBrqFS = false;
      bool usfBcyIHEI = false;
      bool nbHcQCUAZy = false;
      bool unLCkdXDtB = false;
      bool pdfLQbloqo = false;
      bool rLTebQoZnf = false;
      bool frRGXGhdQy = false;
      bool ZENDRKuwMo = false;
      bool QeIjGiUgaU = false;
      bool nxONUyLZnJ = false;
      bool sIYrPmyQMQ = false;
      bool UsNzPAigzo = false;
      bool lACwKboAhT = false;
      string hIRNjFiygl;
      string HTcmYdUkLu;
      string burojiiWoB;
      string azjSUBGPKd;
      string LSbLfhaEad;
      string fbGMAmQccB;
      string VLJfLHjKRX;
      string XEZgjISfJC;
      string HewLVysWRg;
      string kcmJIzJwAX;
      string yPlDGaBYcq;
      string TjTZsqPyJM;
      string OMrjltQQYj;
      string zWfkDqrsEt;
      string xTsZNAJMPR;
      string jLlmIkWBQL;
      string KkArrxEhWC;
      string yVsPPtSSWl;
      string kDAHAnjrcR;
      string TqcsjLTBhP;
      if(hIRNjFiygl == yPlDGaBYcq){uapNSNRWXO = true;}
      else if(yPlDGaBYcq == hIRNjFiygl){unLCkdXDtB = true;}
      if(HTcmYdUkLu == TjTZsqPyJM){SEedZGjrrE = true;}
      else if(TjTZsqPyJM == HTcmYdUkLu){pdfLQbloqo = true;}
      if(burojiiWoB == OMrjltQQYj){NMFEhHrzeD = true;}
      else if(OMrjltQQYj == burojiiWoB){rLTebQoZnf = true;}
      if(azjSUBGPKd == zWfkDqrsEt){ZRkGqJNmnl = true;}
      else if(zWfkDqrsEt == azjSUBGPKd){frRGXGhdQy = true;}
      if(LSbLfhaEad == xTsZNAJMPR){VMTNzOMzSd = true;}
      else if(xTsZNAJMPR == LSbLfhaEad){ZENDRKuwMo = true;}
      if(fbGMAmQccB == jLlmIkWBQL){abJcCiVkeL = true;}
      else if(jLlmIkWBQL == fbGMAmQccB){QeIjGiUgaU = true;}
      if(VLJfLHjKRX == KkArrxEhWC){USqTnATXmP = true;}
      else if(KkArrxEhWC == VLJfLHjKRX){nxONUyLZnJ = true;}
      if(XEZgjISfJC == yVsPPtSSWl){rxDFiBrqFS = true;}
      if(HewLVysWRg == kDAHAnjrcR){usfBcyIHEI = true;}
      if(kcmJIzJwAX == TqcsjLTBhP){nbHcQCUAZy = true;}
      while(yVsPPtSSWl == XEZgjISfJC){sIYrPmyQMQ = true;}
      while(kDAHAnjrcR == kDAHAnjrcR){UsNzPAigzo = true;}
      while(TqcsjLTBhP == TqcsjLTBhP){lACwKboAhT = true;}
      if(uapNSNRWXO == true){uapNSNRWXO = false;}
      if(SEedZGjrrE == true){SEedZGjrrE = false;}
      if(NMFEhHrzeD == true){NMFEhHrzeD = false;}
      if(ZRkGqJNmnl == true){ZRkGqJNmnl = false;}
      if(VMTNzOMzSd == true){VMTNzOMzSd = false;}
      if(abJcCiVkeL == true){abJcCiVkeL = false;}
      if(USqTnATXmP == true){USqTnATXmP = false;}
      if(rxDFiBrqFS == true){rxDFiBrqFS = false;}
      if(usfBcyIHEI == true){usfBcyIHEI = false;}
      if(nbHcQCUAZy == true){nbHcQCUAZy = false;}
      if(unLCkdXDtB == true){unLCkdXDtB = false;}
      if(pdfLQbloqo == true){pdfLQbloqo = false;}
      if(rLTebQoZnf == true){rLTebQoZnf = false;}
      if(frRGXGhdQy == true){frRGXGhdQy = false;}
      if(ZENDRKuwMo == true){ZENDRKuwMo = false;}
      if(QeIjGiUgaU == true){QeIjGiUgaU = false;}
      if(nxONUyLZnJ == true){nxONUyLZnJ = false;}
      if(sIYrPmyQMQ == true){sIYrPmyQMQ = false;}
      if(UsNzPAigzo == true){UsNzPAigzo = false;}
      if(lACwKboAhT == true){lACwKboAhT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJWMEFVLWU
{ 
  void BNZgGfQVKY()
  { 
      bool uxgNuwSzeu = false;
      bool SazaqcZTbE = false;
      bool BHngrmEBtM = false;
      bool uYmaUjExDu = false;
      bool qAUuSbLslz = false;
      bool oBmVCmIAVH = false;
      bool rQFRAsnXFG = false;
      bool XcPfNBmrNP = false;
      bool bKPtWtlQYh = false;
      bool bEawDauDuZ = false;
      bool mmnebMkGIB = false;
      bool APmFehAKuF = false;
      bool HXzXeTBScl = false;
      bool FixnbnWjSJ = false;
      bool IeIXhLRVQU = false;
      bool ZjHpRPnPAH = false;
      bool LSdVuQSycq = false;
      bool LPrkxbOapT = false;
      bool BeBHLVbHVM = false;
      bool zGjKypBlcQ = false;
      string hWrYLceWFS;
      string qOkUNqrlGm;
      string rDOnqohVzu;
      string gmXWHaRsTd;
      string QEuWTUFcyK;
      string AYnFLeHEhW;
      string tJWJkDpONl;
      string ZySbVnHrUW;
      string iFXntHzSLc;
      string SNLxiHgkkQ;
      string dqPLkCGLiW;
      string WPjLmokiPd;
      string EXCkTLlUsO;
      string HVHDrrpMDr;
      string BmioFDdAJt;
      string VyVHMGneqZ;
      string PkSUOBHfSu;
      string zYeWbQnNeQ;
      string hlLzrJzAql;
      string DLUccPUOaD;
      if(hWrYLceWFS == dqPLkCGLiW){uxgNuwSzeu = true;}
      else if(dqPLkCGLiW == hWrYLceWFS){mmnebMkGIB = true;}
      if(qOkUNqrlGm == WPjLmokiPd){SazaqcZTbE = true;}
      else if(WPjLmokiPd == qOkUNqrlGm){APmFehAKuF = true;}
      if(rDOnqohVzu == EXCkTLlUsO){BHngrmEBtM = true;}
      else if(EXCkTLlUsO == rDOnqohVzu){HXzXeTBScl = true;}
      if(gmXWHaRsTd == HVHDrrpMDr){uYmaUjExDu = true;}
      else if(HVHDrrpMDr == gmXWHaRsTd){FixnbnWjSJ = true;}
      if(QEuWTUFcyK == BmioFDdAJt){qAUuSbLslz = true;}
      else if(BmioFDdAJt == QEuWTUFcyK){IeIXhLRVQU = true;}
      if(AYnFLeHEhW == VyVHMGneqZ){oBmVCmIAVH = true;}
      else if(VyVHMGneqZ == AYnFLeHEhW){ZjHpRPnPAH = true;}
      if(tJWJkDpONl == PkSUOBHfSu){rQFRAsnXFG = true;}
      else if(PkSUOBHfSu == tJWJkDpONl){LSdVuQSycq = true;}
      if(ZySbVnHrUW == zYeWbQnNeQ){XcPfNBmrNP = true;}
      if(iFXntHzSLc == hlLzrJzAql){bKPtWtlQYh = true;}
      if(SNLxiHgkkQ == DLUccPUOaD){bEawDauDuZ = true;}
      while(zYeWbQnNeQ == ZySbVnHrUW){LPrkxbOapT = true;}
      while(hlLzrJzAql == hlLzrJzAql){BeBHLVbHVM = true;}
      while(DLUccPUOaD == DLUccPUOaD){zGjKypBlcQ = true;}
      if(uxgNuwSzeu == true){uxgNuwSzeu = false;}
      if(SazaqcZTbE == true){SazaqcZTbE = false;}
      if(BHngrmEBtM == true){BHngrmEBtM = false;}
      if(uYmaUjExDu == true){uYmaUjExDu = false;}
      if(qAUuSbLslz == true){qAUuSbLslz = false;}
      if(oBmVCmIAVH == true){oBmVCmIAVH = false;}
      if(rQFRAsnXFG == true){rQFRAsnXFG = false;}
      if(XcPfNBmrNP == true){XcPfNBmrNP = false;}
      if(bKPtWtlQYh == true){bKPtWtlQYh = false;}
      if(bEawDauDuZ == true){bEawDauDuZ = false;}
      if(mmnebMkGIB == true){mmnebMkGIB = false;}
      if(APmFehAKuF == true){APmFehAKuF = false;}
      if(HXzXeTBScl == true){HXzXeTBScl = false;}
      if(FixnbnWjSJ == true){FixnbnWjSJ = false;}
      if(IeIXhLRVQU == true){IeIXhLRVQU = false;}
      if(ZjHpRPnPAH == true){ZjHpRPnPAH = false;}
      if(LSdVuQSycq == true){LSdVuQSycq = false;}
      if(LPrkxbOapT == true){LPrkxbOapT = false;}
      if(BeBHLVbHVM == true){BeBHLVbHVM = false;}
      if(zGjKypBlcQ == true){zGjKypBlcQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFXTAAHKHC
{ 
  void qQwyiQuiAi()
  { 
      bool AuBAClWTPa = false;
      bool qgydocGrtB = false;
      bool MqGiQPOmEW = false;
      bool oErwlCjMWf = false;
      bool XseMOmFmRK = false;
      bool WhtiYJoSil = false;
      bool WiPsklnBrl = false;
      bool rsVNdSMsTc = false;
      bool KbUszHKJXc = false;
      bool NRcjIndkbc = false;
      bool yDufRcLfFF = false;
      bool wwyGbtOVsd = false;
      bool becPYaQlFo = false;
      bool oaQqdHgobW = false;
      bool ueDSfRSWHN = false;
      bool ZIrxBSaeGq = false;
      bool LYaPQVeHbU = false;
      bool NYsWiwbKiH = false;
      bool HtdqPgiTpL = false;
      bool fBhkKVDmCJ = false;
      string CMIpsmYDir;
      string JzRfVZbaEq;
      string farAnYchuq;
      string iqKQgHWZXi;
      string YNxUTSWVGb;
      string uUjOaaUHBT;
      string JqHqJRoByN;
      string CBCVSRdWgU;
      string CGaTwNHwpG;
      string mPXDYhFFLB;
      string dVXrZsROwI;
      string wyZgRCPnuu;
      string JsKqamdywj;
      string LXLfqfiitD;
      string wszgJnoqlW;
      string SRKPqjKfQl;
      string PSRLwYmtol;
      string TgtqzQsdhm;
      string xlMYRtMunG;
      string UDRHmcankk;
      if(CMIpsmYDir == dVXrZsROwI){AuBAClWTPa = true;}
      else if(dVXrZsROwI == CMIpsmYDir){yDufRcLfFF = true;}
      if(JzRfVZbaEq == wyZgRCPnuu){qgydocGrtB = true;}
      else if(wyZgRCPnuu == JzRfVZbaEq){wwyGbtOVsd = true;}
      if(farAnYchuq == JsKqamdywj){MqGiQPOmEW = true;}
      else if(JsKqamdywj == farAnYchuq){becPYaQlFo = true;}
      if(iqKQgHWZXi == LXLfqfiitD){oErwlCjMWf = true;}
      else if(LXLfqfiitD == iqKQgHWZXi){oaQqdHgobW = true;}
      if(YNxUTSWVGb == wszgJnoqlW){XseMOmFmRK = true;}
      else if(wszgJnoqlW == YNxUTSWVGb){ueDSfRSWHN = true;}
      if(uUjOaaUHBT == SRKPqjKfQl){WhtiYJoSil = true;}
      else if(SRKPqjKfQl == uUjOaaUHBT){ZIrxBSaeGq = true;}
      if(JqHqJRoByN == PSRLwYmtol){WiPsklnBrl = true;}
      else if(PSRLwYmtol == JqHqJRoByN){LYaPQVeHbU = true;}
      if(CBCVSRdWgU == TgtqzQsdhm){rsVNdSMsTc = true;}
      if(CGaTwNHwpG == xlMYRtMunG){KbUszHKJXc = true;}
      if(mPXDYhFFLB == UDRHmcankk){NRcjIndkbc = true;}
      while(TgtqzQsdhm == CBCVSRdWgU){NYsWiwbKiH = true;}
      while(xlMYRtMunG == xlMYRtMunG){HtdqPgiTpL = true;}
      while(UDRHmcankk == UDRHmcankk){fBhkKVDmCJ = true;}
      if(AuBAClWTPa == true){AuBAClWTPa = false;}
      if(qgydocGrtB == true){qgydocGrtB = false;}
      if(MqGiQPOmEW == true){MqGiQPOmEW = false;}
      if(oErwlCjMWf == true){oErwlCjMWf = false;}
      if(XseMOmFmRK == true){XseMOmFmRK = false;}
      if(WhtiYJoSil == true){WhtiYJoSil = false;}
      if(WiPsklnBrl == true){WiPsklnBrl = false;}
      if(rsVNdSMsTc == true){rsVNdSMsTc = false;}
      if(KbUszHKJXc == true){KbUszHKJXc = false;}
      if(NRcjIndkbc == true){NRcjIndkbc = false;}
      if(yDufRcLfFF == true){yDufRcLfFF = false;}
      if(wwyGbtOVsd == true){wwyGbtOVsd = false;}
      if(becPYaQlFo == true){becPYaQlFo = false;}
      if(oaQqdHgobW == true){oaQqdHgobW = false;}
      if(ueDSfRSWHN == true){ueDSfRSWHN = false;}
      if(ZIrxBSaeGq == true){ZIrxBSaeGq = false;}
      if(LYaPQVeHbU == true){LYaPQVeHbU = false;}
      if(NYsWiwbKiH == true){NYsWiwbKiH = false;}
      if(HtdqPgiTpL == true){HtdqPgiTpL = false;}
      if(fBhkKVDmCJ == true){fBhkKVDmCJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RJYJDMXHEO
{ 
  void BGFhrDyrac()
  { 
      bool UuWOCuryIQ = false;
      bool VaRxTeECPo = false;
      bool lEodAjeSoi = false;
      bool pDhFUsRQSr = false;
      bool uLNWSgPBgs = false;
      bool DzSkDQFsNR = false;
      bool QZIZZRrLca = false;
      bool NnjXtZpSKT = false;
      bool TdlweqkwBE = false;
      bool nXDAbVDnwA = false;
      bool nDXGfPOupd = false;
      bool ZmhsymmLth = false;
      bool gwKYlojiuY = false;
      bool VCVKfPFeQP = false;
      bool bpFXdApJCo = false;
      bool hqtNTrszTq = false;
      bool eezRHXQWMh = false;
      bool gIueFppmtl = false;
      bool yagGqeHHqn = false;
      bool VGLYkxqnPG = false;
      string CFGqYVElMJ;
      string bDCueLmmBY;
      string CxDHtiUXVT;
      string sVYGKxyDMg;
      string VIJyiNtfJl;
      string fNhUXFCzxo;
      string AfPrPGdwkh;
      string NiaUDsmEYg;
      string ooOjmfmEhE;
      string tzFXfpsQib;
      string ixtbYwmMQd;
      string SxZQALQfEi;
      string SZNgmOcCoM;
      string AVVwxqtmLq;
      string rZmElxYoWT;
      string YMLzJIjMnJ;
      string SjXEcwbcSI;
      string RdUNqrmIup;
      string onfUnmKWmo;
      string HgyBXICiap;
      if(CFGqYVElMJ == ixtbYwmMQd){UuWOCuryIQ = true;}
      else if(ixtbYwmMQd == CFGqYVElMJ){nDXGfPOupd = true;}
      if(bDCueLmmBY == SxZQALQfEi){VaRxTeECPo = true;}
      else if(SxZQALQfEi == bDCueLmmBY){ZmhsymmLth = true;}
      if(CxDHtiUXVT == SZNgmOcCoM){lEodAjeSoi = true;}
      else if(SZNgmOcCoM == CxDHtiUXVT){gwKYlojiuY = true;}
      if(sVYGKxyDMg == AVVwxqtmLq){pDhFUsRQSr = true;}
      else if(AVVwxqtmLq == sVYGKxyDMg){VCVKfPFeQP = true;}
      if(VIJyiNtfJl == rZmElxYoWT){uLNWSgPBgs = true;}
      else if(rZmElxYoWT == VIJyiNtfJl){bpFXdApJCo = true;}
      if(fNhUXFCzxo == YMLzJIjMnJ){DzSkDQFsNR = true;}
      else if(YMLzJIjMnJ == fNhUXFCzxo){hqtNTrszTq = true;}
      if(AfPrPGdwkh == SjXEcwbcSI){QZIZZRrLca = true;}
      else if(SjXEcwbcSI == AfPrPGdwkh){eezRHXQWMh = true;}
      if(NiaUDsmEYg == RdUNqrmIup){NnjXtZpSKT = true;}
      if(ooOjmfmEhE == onfUnmKWmo){TdlweqkwBE = true;}
      if(tzFXfpsQib == HgyBXICiap){nXDAbVDnwA = true;}
      while(RdUNqrmIup == NiaUDsmEYg){gIueFppmtl = true;}
      while(onfUnmKWmo == onfUnmKWmo){yagGqeHHqn = true;}
      while(HgyBXICiap == HgyBXICiap){VGLYkxqnPG = true;}
      if(UuWOCuryIQ == true){UuWOCuryIQ = false;}
      if(VaRxTeECPo == true){VaRxTeECPo = false;}
      if(lEodAjeSoi == true){lEodAjeSoi = false;}
      if(pDhFUsRQSr == true){pDhFUsRQSr = false;}
      if(uLNWSgPBgs == true){uLNWSgPBgs = false;}
      if(DzSkDQFsNR == true){DzSkDQFsNR = false;}
      if(QZIZZRrLca == true){QZIZZRrLca = false;}
      if(NnjXtZpSKT == true){NnjXtZpSKT = false;}
      if(TdlweqkwBE == true){TdlweqkwBE = false;}
      if(nXDAbVDnwA == true){nXDAbVDnwA = false;}
      if(nDXGfPOupd == true){nDXGfPOupd = false;}
      if(ZmhsymmLth == true){ZmhsymmLth = false;}
      if(gwKYlojiuY == true){gwKYlojiuY = false;}
      if(VCVKfPFeQP == true){VCVKfPFeQP = false;}
      if(bpFXdApJCo == true){bpFXdApJCo = false;}
      if(hqtNTrszTq == true){hqtNTrszTq = false;}
      if(eezRHXQWMh == true){eezRHXQWMh = false;}
      if(gIueFppmtl == true){gIueFppmtl = false;}
      if(yagGqeHHqn == true){yagGqeHHqn = false;}
      if(VGLYkxqnPG == true){VGLYkxqnPG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KTQRIEYSTA
{ 
  void DbqzPQYTyt()
  { 
      bool srISjEfPXw = false;
      bool sFWNWDnYJO = false;
      bool QHYXiKQonF = false;
      bool YZTBPstmHp = false;
      bool ykzdkxMbdI = false;
      bool HCRCCkSjjZ = false;
      bool npbRXTlUxc = false;
      bool JBQTQeHumk = false;
      bool xoLexVHRzd = false;
      bool aKDhCIJhGQ = false;
      bool LqdAzGkykW = false;
      bool dXwybyewTB = false;
      bool LTVTCyxiQI = false;
      bool UZoVZGKKfq = false;
      bool jIfbADNFFD = false;
      bool dNNEEqVKyA = false;
      bool JCgcCDhZXV = false;
      bool mTQcQDmsSz = false;
      bool krdMeHLjQh = false;
      bool jALehhaDZw = false;
      string TXRniogUJz;
      string WPTZbpPBTq;
      string mldgJTuAZE;
      string GumTAtyQBu;
      string IQmMSGmVkd;
      string SHMtPhsjeO;
      string tguEsbbAYg;
      string rzzXhVzRND;
      string gYOulzhsES;
      string ANlmAbVhTq;
      string dmxDlTHoLs;
      string hbWagVRzSt;
      string tiuFgdMMWF;
      string AQxWYtbLJS;
      string qsgKkXqKFe;
      string KVPZxuqqVI;
      string GuRFsRezCm;
      string tFpACABkUI;
      string lCGrudBWZd;
      string DjoAMwbbQS;
      if(TXRniogUJz == dmxDlTHoLs){srISjEfPXw = true;}
      else if(dmxDlTHoLs == TXRniogUJz){LqdAzGkykW = true;}
      if(WPTZbpPBTq == hbWagVRzSt){sFWNWDnYJO = true;}
      else if(hbWagVRzSt == WPTZbpPBTq){dXwybyewTB = true;}
      if(mldgJTuAZE == tiuFgdMMWF){QHYXiKQonF = true;}
      else if(tiuFgdMMWF == mldgJTuAZE){LTVTCyxiQI = true;}
      if(GumTAtyQBu == AQxWYtbLJS){YZTBPstmHp = true;}
      else if(AQxWYtbLJS == GumTAtyQBu){UZoVZGKKfq = true;}
      if(IQmMSGmVkd == qsgKkXqKFe){ykzdkxMbdI = true;}
      else if(qsgKkXqKFe == IQmMSGmVkd){jIfbADNFFD = true;}
      if(SHMtPhsjeO == KVPZxuqqVI){HCRCCkSjjZ = true;}
      else if(KVPZxuqqVI == SHMtPhsjeO){dNNEEqVKyA = true;}
      if(tguEsbbAYg == GuRFsRezCm){npbRXTlUxc = true;}
      else if(GuRFsRezCm == tguEsbbAYg){JCgcCDhZXV = true;}
      if(rzzXhVzRND == tFpACABkUI){JBQTQeHumk = true;}
      if(gYOulzhsES == lCGrudBWZd){xoLexVHRzd = true;}
      if(ANlmAbVhTq == DjoAMwbbQS){aKDhCIJhGQ = true;}
      while(tFpACABkUI == rzzXhVzRND){mTQcQDmsSz = true;}
      while(lCGrudBWZd == lCGrudBWZd){krdMeHLjQh = true;}
      while(DjoAMwbbQS == DjoAMwbbQS){jALehhaDZw = true;}
      if(srISjEfPXw == true){srISjEfPXw = false;}
      if(sFWNWDnYJO == true){sFWNWDnYJO = false;}
      if(QHYXiKQonF == true){QHYXiKQonF = false;}
      if(YZTBPstmHp == true){YZTBPstmHp = false;}
      if(ykzdkxMbdI == true){ykzdkxMbdI = false;}
      if(HCRCCkSjjZ == true){HCRCCkSjjZ = false;}
      if(npbRXTlUxc == true){npbRXTlUxc = false;}
      if(JBQTQeHumk == true){JBQTQeHumk = false;}
      if(xoLexVHRzd == true){xoLexVHRzd = false;}
      if(aKDhCIJhGQ == true){aKDhCIJhGQ = false;}
      if(LqdAzGkykW == true){LqdAzGkykW = false;}
      if(dXwybyewTB == true){dXwybyewTB = false;}
      if(LTVTCyxiQI == true){LTVTCyxiQI = false;}
      if(UZoVZGKKfq == true){UZoVZGKKfq = false;}
      if(jIfbADNFFD == true){jIfbADNFFD = false;}
      if(dNNEEqVKyA == true){dNNEEqVKyA = false;}
      if(JCgcCDhZXV == true){JCgcCDhZXV = false;}
      if(mTQcQDmsSz == true){mTQcQDmsSz = false;}
      if(krdMeHLjQh == true){krdMeHLjQh = false;}
      if(jALehhaDZw == true){jALehhaDZw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KGAPTBHCBY
{ 
  void lJszuotzjx()
  { 
      bool CgqWYogfie = false;
      bool OPyIaDnFxQ = false;
      bool KqhMuhxCrT = false;
      bool jUDidGalQh = false;
      bool qJYIanSWHi = false;
      bool iQrARKydaq = false;
      bool rdnOttLOeT = false;
      bool cBoPYBSZkH = false;
      bool OZuJjTcDRS = false;
      bool HwKZoNVJNg = false;
      bool bErnFgbcaQ = false;
      bool rYsTbRheda = false;
      bool RIxMLgqPZL = false;
      bool eILEeJhGDD = false;
      bool qAbAZiCpxW = false;
      bool eqelPSGfbY = false;
      bool pMCPkiMooR = false;
      bool jbaajRgxlc = false;
      bool dARCfndYoL = false;
      bool CBedNexMOq = false;
      string YJtZcOarWc;
      string JidEwfMzaT;
      string jYLHxiFhDt;
      string TEqNgfmoGK;
      string KpZtSmeZnz;
      string EVaUZAylcs;
      string IrnbIErQXP;
      string rXsQIsyRoK;
      string DfsEoxdWnf;
      string hALMBRCxkN;
      string tNCXGgcKLf;
      string BfxSoczjmL;
      string aUcqhqLfOp;
      string qAgaPocVxI;
      string USKHdBDsWY;
      string SSKZmYkLoO;
      string VxuUoBzVCz;
      string zcleqHKVMf;
      string nRIpXXpHnp;
      string ERfilWWoRc;
      if(YJtZcOarWc == tNCXGgcKLf){CgqWYogfie = true;}
      else if(tNCXGgcKLf == YJtZcOarWc){bErnFgbcaQ = true;}
      if(JidEwfMzaT == BfxSoczjmL){OPyIaDnFxQ = true;}
      else if(BfxSoczjmL == JidEwfMzaT){rYsTbRheda = true;}
      if(jYLHxiFhDt == aUcqhqLfOp){KqhMuhxCrT = true;}
      else if(aUcqhqLfOp == jYLHxiFhDt){RIxMLgqPZL = true;}
      if(TEqNgfmoGK == qAgaPocVxI){jUDidGalQh = true;}
      else if(qAgaPocVxI == TEqNgfmoGK){eILEeJhGDD = true;}
      if(KpZtSmeZnz == USKHdBDsWY){qJYIanSWHi = true;}
      else if(USKHdBDsWY == KpZtSmeZnz){qAbAZiCpxW = true;}
      if(EVaUZAylcs == SSKZmYkLoO){iQrARKydaq = true;}
      else if(SSKZmYkLoO == EVaUZAylcs){eqelPSGfbY = true;}
      if(IrnbIErQXP == VxuUoBzVCz){rdnOttLOeT = true;}
      else if(VxuUoBzVCz == IrnbIErQXP){pMCPkiMooR = true;}
      if(rXsQIsyRoK == zcleqHKVMf){cBoPYBSZkH = true;}
      if(DfsEoxdWnf == nRIpXXpHnp){OZuJjTcDRS = true;}
      if(hALMBRCxkN == ERfilWWoRc){HwKZoNVJNg = true;}
      while(zcleqHKVMf == rXsQIsyRoK){jbaajRgxlc = true;}
      while(nRIpXXpHnp == nRIpXXpHnp){dARCfndYoL = true;}
      while(ERfilWWoRc == ERfilWWoRc){CBedNexMOq = true;}
      if(CgqWYogfie == true){CgqWYogfie = false;}
      if(OPyIaDnFxQ == true){OPyIaDnFxQ = false;}
      if(KqhMuhxCrT == true){KqhMuhxCrT = false;}
      if(jUDidGalQh == true){jUDidGalQh = false;}
      if(qJYIanSWHi == true){qJYIanSWHi = false;}
      if(iQrARKydaq == true){iQrARKydaq = false;}
      if(rdnOttLOeT == true){rdnOttLOeT = false;}
      if(cBoPYBSZkH == true){cBoPYBSZkH = false;}
      if(OZuJjTcDRS == true){OZuJjTcDRS = false;}
      if(HwKZoNVJNg == true){HwKZoNVJNg = false;}
      if(bErnFgbcaQ == true){bErnFgbcaQ = false;}
      if(rYsTbRheda == true){rYsTbRheda = false;}
      if(RIxMLgqPZL == true){RIxMLgqPZL = false;}
      if(eILEeJhGDD == true){eILEeJhGDD = false;}
      if(qAbAZiCpxW == true){qAbAZiCpxW = false;}
      if(eqelPSGfbY == true){eqelPSGfbY = false;}
      if(pMCPkiMooR == true){pMCPkiMooR = false;}
      if(jbaajRgxlc == true){jbaajRgxlc = false;}
      if(dARCfndYoL == true){dARCfndYoL = false;}
      if(CBedNexMOq == true){CBedNexMOq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFDVHKESLR
{ 
  void XImqTWCqar()
  { 
      bool VcuqJhlNry = false;
      bool wUYPFXNbzs = false;
      bool aUhlicouFH = false;
      bool wHqyjVwJcO = false;
      bool cjFtOOmRaZ = false;
      bool WBEkJBuJIg = false;
      bool sqHkBodafj = false;
      bool aEyjPqPmWT = false;
      bool pWUfjtCFni = false;
      bool alAwVkcTrZ = false;
      bool jLlqyRDUUS = false;
      bool kHlnqVWaAG = false;
      bool lYlxIoDCOd = false;
      bool OutxidkdhR = false;
      bool qhjVxSzLEz = false;
      bool OCTlmLYnhJ = false;
      bool OAFpEpNoFN = false;
      bool ksrhPEnQAp = false;
      bool oqxOPLaIKW = false;
      bool EwuYDqbtRG = false;
      string mHbPcjXNjg;
      string FlCOnHBqeK;
      string oFxVOIGZFF;
      string RpcSbAFIZk;
      string ciKoIchlEK;
      string rruesgJGBU;
      string cxHdPOJimm;
      string CrQsgFuIMl;
      string ZTVtNZtxZu;
      string qyHFHfbgZs;
      string TzzRIAaBxm;
      string lBtPtIaNQp;
      string TLIquDjLlB;
      string dNhSSaTEkM;
      string ysAmIoErKy;
      string EOQjZHpHVF;
      string POPwIXTawS;
      string oWbDqaLViF;
      string zrBmwPxysK;
      string jLhfxjdEdj;
      if(mHbPcjXNjg == TzzRIAaBxm){VcuqJhlNry = true;}
      else if(TzzRIAaBxm == mHbPcjXNjg){jLlqyRDUUS = true;}
      if(FlCOnHBqeK == lBtPtIaNQp){wUYPFXNbzs = true;}
      else if(lBtPtIaNQp == FlCOnHBqeK){kHlnqVWaAG = true;}
      if(oFxVOIGZFF == TLIquDjLlB){aUhlicouFH = true;}
      else if(TLIquDjLlB == oFxVOIGZFF){lYlxIoDCOd = true;}
      if(RpcSbAFIZk == dNhSSaTEkM){wHqyjVwJcO = true;}
      else if(dNhSSaTEkM == RpcSbAFIZk){OutxidkdhR = true;}
      if(ciKoIchlEK == ysAmIoErKy){cjFtOOmRaZ = true;}
      else if(ysAmIoErKy == ciKoIchlEK){qhjVxSzLEz = true;}
      if(rruesgJGBU == EOQjZHpHVF){WBEkJBuJIg = true;}
      else if(EOQjZHpHVF == rruesgJGBU){OCTlmLYnhJ = true;}
      if(cxHdPOJimm == POPwIXTawS){sqHkBodafj = true;}
      else if(POPwIXTawS == cxHdPOJimm){OAFpEpNoFN = true;}
      if(CrQsgFuIMl == oWbDqaLViF){aEyjPqPmWT = true;}
      if(ZTVtNZtxZu == zrBmwPxysK){pWUfjtCFni = true;}
      if(qyHFHfbgZs == jLhfxjdEdj){alAwVkcTrZ = true;}
      while(oWbDqaLViF == CrQsgFuIMl){ksrhPEnQAp = true;}
      while(zrBmwPxysK == zrBmwPxysK){oqxOPLaIKW = true;}
      while(jLhfxjdEdj == jLhfxjdEdj){EwuYDqbtRG = true;}
      if(VcuqJhlNry == true){VcuqJhlNry = false;}
      if(wUYPFXNbzs == true){wUYPFXNbzs = false;}
      if(aUhlicouFH == true){aUhlicouFH = false;}
      if(wHqyjVwJcO == true){wHqyjVwJcO = false;}
      if(cjFtOOmRaZ == true){cjFtOOmRaZ = false;}
      if(WBEkJBuJIg == true){WBEkJBuJIg = false;}
      if(sqHkBodafj == true){sqHkBodafj = false;}
      if(aEyjPqPmWT == true){aEyjPqPmWT = false;}
      if(pWUfjtCFni == true){pWUfjtCFni = false;}
      if(alAwVkcTrZ == true){alAwVkcTrZ = false;}
      if(jLlqyRDUUS == true){jLlqyRDUUS = false;}
      if(kHlnqVWaAG == true){kHlnqVWaAG = false;}
      if(lYlxIoDCOd == true){lYlxIoDCOd = false;}
      if(OutxidkdhR == true){OutxidkdhR = false;}
      if(qhjVxSzLEz == true){qhjVxSzLEz = false;}
      if(OCTlmLYnhJ == true){OCTlmLYnhJ = false;}
      if(OAFpEpNoFN == true){OAFpEpNoFN = false;}
      if(ksrhPEnQAp == true){ksrhPEnQAp = false;}
      if(oqxOPLaIKW == true){oqxOPLaIKW = false;}
      if(EwuYDqbtRG == true){EwuYDqbtRG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XAGIJZYQCF
{ 
  void gyBxDWdVRf()
  { 
      bool hHWScSLHlp = false;
      bool YlwPNSYDYG = false;
      bool eKLMyAiOFK = false;
      bool AxAljOLpAN = false;
      bool EtZOkZProE = false;
      bool HKNWIWuJUc = false;
      bool jwBbpakJez = false;
      bool HiCLCjjxaX = false;
      bool jpZBDojcdM = false;
      bool SBVXcHryYK = false;
      bool oFNoxXHCUX = false;
      bool myhwrsWAXA = false;
      bool qIfSfGNeht = false;
      bool rlXQiecjEe = false;
      bool hhIFZUSYej = false;
      bool krZXSgYtJq = false;
      bool KcTafAZRMN = false;
      bool PlwsSIzarL = false;
      bool mnzyIzLAxC = false;
      bool FiaMTENhZY = false;
      string LWoFgmYKss;
      string OoIOrrsknI;
      string eRnqJSstop;
      string HHWKhBxgff;
      string XDqSTDtwxY;
      string oZJhrtiywN;
      string seUDlGRxgq;
      string tMFHkbaVWF;
      string YxwQBhxoRm;
      string SzjRlshmfN;
      string lwPGdcUCxQ;
      string TMaqnuhECD;
      string IbfsXtbmUq;
      string smoJTchplY;
      string NurBTFYsdp;
      string KckcEJQVhi;
      string AggFWfXRWK;
      string MqRdpNjdZS;
      string VhIdgPBMFK;
      string MMICXfNldm;
      if(LWoFgmYKss == lwPGdcUCxQ){hHWScSLHlp = true;}
      else if(lwPGdcUCxQ == LWoFgmYKss){oFNoxXHCUX = true;}
      if(OoIOrrsknI == TMaqnuhECD){YlwPNSYDYG = true;}
      else if(TMaqnuhECD == OoIOrrsknI){myhwrsWAXA = true;}
      if(eRnqJSstop == IbfsXtbmUq){eKLMyAiOFK = true;}
      else if(IbfsXtbmUq == eRnqJSstop){qIfSfGNeht = true;}
      if(HHWKhBxgff == smoJTchplY){AxAljOLpAN = true;}
      else if(smoJTchplY == HHWKhBxgff){rlXQiecjEe = true;}
      if(XDqSTDtwxY == NurBTFYsdp){EtZOkZProE = true;}
      else if(NurBTFYsdp == XDqSTDtwxY){hhIFZUSYej = true;}
      if(oZJhrtiywN == KckcEJQVhi){HKNWIWuJUc = true;}
      else if(KckcEJQVhi == oZJhrtiywN){krZXSgYtJq = true;}
      if(seUDlGRxgq == AggFWfXRWK){jwBbpakJez = true;}
      else if(AggFWfXRWK == seUDlGRxgq){KcTafAZRMN = true;}
      if(tMFHkbaVWF == MqRdpNjdZS){HiCLCjjxaX = true;}
      if(YxwQBhxoRm == VhIdgPBMFK){jpZBDojcdM = true;}
      if(SzjRlshmfN == MMICXfNldm){SBVXcHryYK = true;}
      while(MqRdpNjdZS == tMFHkbaVWF){PlwsSIzarL = true;}
      while(VhIdgPBMFK == VhIdgPBMFK){mnzyIzLAxC = true;}
      while(MMICXfNldm == MMICXfNldm){FiaMTENhZY = true;}
      if(hHWScSLHlp == true){hHWScSLHlp = false;}
      if(YlwPNSYDYG == true){YlwPNSYDYG = false;}
      if(eKLMyAiOFK == true){eKLMyAiOFK = false;}
      if(AxAljOLpAN == true){AxAljOLpAN = false;}
      if(EtZOkZProE == true){EtZOkZProE = false;}
      if(HKNWIWuJUc == true){HKNWIWuJUc = false;}
      if(jwBbpakJez == true){jwBbpakJez = false;}
      if(HiCLCjjxaX == true){HiCLCjjxaX = false;}
      if(jpZBDojcdM == true){jpZBDojcdM = false;}
      if(SBVXcHryYK == true){SBVXcHryYK = false;}
      if(oFNoxXHCUX == true){oFNoxXHCUX = false;}
      if(myhwrsWAXA == true){myhwrsWAXA = false;}
      if(qIfSfGNeht == true){qIfSfGNeht = false;}
      if(rlXQiecjEe == true){rlXQiecjEe = false;}
      if(hhIFZUSYej == true){hhIFZUSYej = false;}
      if(krZXSgYtJq == true){krZXSgYtJq = false;}
      if(KcTafAZRMN == true){KcTafAZRMN = false;}
      if(PlwsSIzarL == true){PlwsSIzarL = false;}
      if(mnzyIzLAxC == true){mnzyIzLAxC = false;}
      if(FiaMTENhZY == true){FiaMTENhZY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RCBDJHRZEP
{ 
  void baERCsOLYK()
  { 
      bool MZToleYJFJ = false;
      bool oAmxEFtAPu = false;
      bool elXXPkXlDg = false;
      bool WoXbDHAJrd = false;
      bool aOHTgnMBoI = false;
      bool rsoFmaBuYB = false;
      bool GmFXlzbKtx = false;
      bool FjIlTPeEqa = false;
      bool XWxuodzSoc = false;
      bool FEjpWnJigg = false;
      bool MBGqDHjDkW = false;
      bool uxEycjoJiI = false;
      bool zIVRqAARPf = false;
      bool GuXJOWPFrg = false;
      bool swgRgIzlNm = false;
      bool zAzXgDeoAC = false;
      bool HSnFQAYuiG = false;
      bool UiQBPDaEki = false;
      bool ANEbgFuzbL = false;
      bool qZFpZZIbBg = false;
      string GqGPuUQFLL;
      string cZtCYtZlfZ;
      string jVthCVWaOG;
      string zfpaLwEbjn;
      string cKmjNpNpUk;
      string HkYebkxYMZ;
      string yppFLwiTqc;
      string oyBrwZhKTM;
      string HfFcyNGLyZ;
      string zfOKolThXQ;
      string GtyrwJighC;
      string DlEARSkNGy;
      string pXUQcIiqCK;
      string GzmDFNgNgn;
      string dYcwWMaOsW;
      string BFaYaiYhOm;
      string areXuDzBtE;
      string kWfRTQtYtQ;
      string hUyeIAXNcV;
      string nzztNlsFAS;
      if(GqGPuUQFLL == GtyrwJighC){MZToleYJFJ = true;}
      else if(GtyrwJighC == GqGPuUQFLL){MBGqDHjDkW = true;}
      if(cZtCYtZlfZ == DlEARSkNGy){oAmxEFtAPu = true;}
      else if(DlEARSkNGy == cZtCYtZlfZ){uxEycjoJiI = true;}
      if(jVthCVWaOG == pXUQcIiqCK){elXXPkXlDg = true;}
      else if(pXUQcIiqCK == jVthCVWaOG){zIVRqAARPf = true;}
      if(zfpaLwEbjn == GzmDFNgNgn){WoXbDHAJrd = true;}
      else if(GzmDFNgNgn == zfpaLwEbjn){GuXJOWPFrg = true;}
      if(cKmjNpNpUk == dYcwWMaOsW){aOHTgnMBoI = true;}
      else if(dYcwWMaOsW == cKmjNpNpUk){swgRgIzlNm = true;}
      if(HkYebkxYMZ == BFaYaiYhOm){rsoFmaBuYB = true;}
      else if(BFaYaiYhOm == HkYebkxYMZ){zAzXgDeoAC = true;}
      if(yppFLwiTqc == areXuDzBtE){GmFXlzbKtx = true;}
      else if(areXuDzBtE == yppFLwiTqc){HSnFQAYuiG = true;}
      if(oyBrwZhKTM == kWfRTQtYtQ){FjIlTPeEqa = true;}
      if(HfFcyNGLyZ == hUyeIAXNcV){XWxuodzSoc = true;}
      if(zfOKolThXQ == nzztNlsFAS){FEjpWnJigg = true;}
      while(kWfRTQtYtQ == oyBrwZhKTM){UiQBPDaEki = true;}
      while(hUyeIAXNcV == hUyeIAXNcV){ANEbgFuzbL = true;}
      while(nzztNlsFAS == nzztNlsFAS){qZFpZZIbBg = true;}
      if(MZToleYJFJ == true){MZToleYJFJ = false;}
      if(oAmxEFtAPu == true){oAmxEFtAPu = false;}
      if(elXXPkXlDg == true){elXXPkXlDg = false;}
      if(WoXbDHAJrd == true){WoXbDHAJrd = false;}
      if(aOHTgnMBoI == true){aOHTgnMBoI = false;}
      if(rsoFmaBuYB == true){rsoFmaBuYB = false;}
      if(GmFXlzbKtx == true){GmFXlzbKtx = false;}
      if(FjIlTPeEqa == true){FjIlTPeEqa = false;}
      if(XWxuodzSoc == true){XWxuodzSoc = false;}
      if(FEjpWnJigg == true){FEjpWnJigg = false;}
      if(MBGqDHjDkW == true){MBGqDHjDkW = false;}
      if(uxEycjoJiI == true){uxEycjoJiI = false;}
      if(zIVRqAARPf == true){zIVRqAARPf = false;}
      if(GuXJOWPFrg == true){GuXJOWPFrg = false;}
      if(swgRgIzlNm == true){swgRgIzlNm = false;}
      if(zAzXgDeoAC == true){zAzXgDeoAC = false;}
      if(HSnFQAYuiG == true){HSnFQAYuiG = false;}
      if(UiQBPDaEki == true){UiQBPDaEki = false;}
      if(ANEbgFuzbL == true){ANEbgFuzbL = false;}
      if(qZFpZZIbBg == true){qZFpZZIbBg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTQLBCFYFR
{ 
  void dOFyDKiZjJ()
  { 
      bool gntYBfeQMg = false;
      bool NBHcUHNeNL = false;
      bool jNVyzfxCdS = false;
      bool keeFMHiYch = false;
      bool ajuMJKVWbS = false;
      bool QfZxrSSuYV = false;
      bool hclsuhWBQM = false;
      bool YoCfkASIoo = false;
      bool JZZKCFFgNs = false;
      bool omzGzyxCQb = false;
      bool nUGPtadtMq = false;
      bool AJGjLICapp = false;
      bool bonWXkpufl = false;
      bool CPrNBnSKPb = false;
      bool bLTVrefPuq = false;
      bool wWLZzygjqI = false;
      bool kiNaojQsiX = false;
      bool orKOOQURdr = false;
      bool FaAnpfERNC = false;
      bool HiTGprxsgI = false;
      string JBDwowKUJt;
      string fNIyqlUKFz;
      string IxsxCPLzfD;
      string SwtLgAwjZZ;
      string JfpaeiEEJE;
      string OfdKfMHGsZ;
      string kKoFbjSwQp;
      string ojjepbGSST;
      string KHpbomSjfT;
      string sppAoyqkzu;
      string PHmTOdwyTD;
      string GomZOdUMPo;
      string QiQwxysior;
      string kVSXDCTWMK;
      string qTPbNDDQkL;
      string deUKdgppWP;
      string jMJbRkVPVL;
      string JxzExwSois;
      string ucydNGAIsW;
      string LdAxaeKmJc;
      if(JBDwowKUJt == PHmTOdwyTD){gntYBfeQMg = true;}
      else if(PHmTOdwyTD == JBDwowKUJt){nUGPtadtMq = true;}
      if(fNIyqlUKFz == GomZOdUMPo){NBHcUHNeNL = true;}
      else if(GomZOdUMPo == fNIyqlUKFz){AJGjLICapp = true;}
      if(IxsxCPLzfD == QiQwxysior){jNVyzfxCdS = true;}
      else if(QiQwxysior == IxsxCPLzfD){bonWXkpufl = true;}
      if(SwtLgAwjZZ == kVSXDCTWMK){keeFMHiYch = true;}
      else if(kVSXDCTWMK == SwtLgAwjZZ){CPrNBnSKPb = true;}
      if(JfpaeiEEJE == qTPbNDDQkL){ajuMJKVWbS = true;}
      else if(qTPbNDDQkL == JfpaeiEEJE){bLTVrefPuq = true;}
      if(OfdKfMHGsZ == deUKdgppWP){QfZxrSSuYV = true;}
      else if(deUKdgppWP == OfdKfMHGsZ){wWLZzygjqI = true;}
      if(kKoFbjSwQp == jMJbRkVPVL){hclsuhWBQM = true;}
      else if(jMJbRkVPVL == kKoFbjSwQp){kiNaojQsiX = true;}
      if(ojjepbGSST == JxzExwSois){YoCfkASIoo = true;}
      if(KHpbomSjfT == ucydNGAIsW){JZZKCFFgNs = true;}
      if(sppAoyqkzu == LdAxaeKmJc){omzGzyxCQb = true;}
      while(JxzExwSois == ojjepbGSST){orKOOQURdr = true;}
      while(ucydNGAIsW == ucydNGAIsW){FaAnpfERNC = true;}
      while(LdAxaeKmJc == LdAxaeKmJc){HiTGprxsgI = true;}
      if(gntYBfeQMg == true){gntYBfeQMg = false;}
      if(NBHcUHNeNL == true){NBHcUHNeNL = false;}
      if(jNVyzfxCdS == true){jNVyzfxCdS = false;}
      if(keeFMHiYch == true){keeFMHiYch = false;}
      if(ajuMJKVWbS == true){ajuMJKVWbS = false;}
      if(QfZxrSSuYV == true){QfZxrSSuYV = false;}
      if(hclsuhWBQM == true){hclsuhWBQM = false;}
      if(YoCfkASIoo == true){YoCfkASIoo = false;}
      if(JZZKCFFgNs == true){JZZKCFFgNs = false;}
      if(omzGzyxCQb == true){omzGzyxCQb = false;}
      if(nUGPtadtMq == true){nUGPtadtMq = false;}
      if(AJGjLICapp == true){AJGjLICapp = false;}
      if(bonWXkpufl == true){bonWXkpufl = false;}
      if(CPrNBnSKPb == true){CPrNBnSKPb = false;}
      if(bLTVrefPuq == true){bLTVrefPuq = false;}
      if(wWLZzygjqI == true){wWLZzygjqI = false;}
      if(kiNaojQsiX == true){kiNaojQsiX = false;}
      if(orKOOQURdr == true){orKOOQURdr = false;}
      if(FaAnpfERNC == true){FaAnpfERNC = false;}
      if(HiTGprxsgI == true){HiTGprxsgI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELKKOAJQTA
{ 
  void GGHDcJVYPe()
  { 
      bool AQwyxsehUp = false;
      bool MgxMsEtGVP = false;
      bool OZMJkedoQW = false;
      bool XuYYVGcJlU = false;
      bool uVJWKEtHUS = false;
      bool IFzdVaElNR = false;
      bool OoRyRQIYql = false;
      bool akUAUsPozg = false;
      bool kWUxNRwuDu = false;
      bool CqwTGFDKFs = false;
      bool uVPirXkzIb = false;
      bool KOmfgrUUjz = false;
      bool UNUwijoBtO = false;
      bool pFjFkPGlFp = false;
      bool gxlaknEPmO = false;
      bool kiaFYhATzI = false;
      bool ijEslFdguQ = false;
      bool liPsSXasLu = false;
      bool eYNfdGdefD = false;
      bool PllwHxrroe = false;
      string DMXGRuuEzk;
      string jFhqRnHgiK;
      string fWkHWVDfLb;
      string WulAeIUtZk;
      string KIjmEUihRA;
      string sltpTgaQju;
      string rPsXOoThLI;
      string TMHyAWmxCC;
      string mUNLhjAwfy;
      string hEKdrtPLYP;
      string BBVJffewpx;
      string tcNhIWChod;
      string nWBNaOCcFF;
      string HaYmAkzDeB;
      string EDFiEEqcUV;
      string qhWtadzHiQ;
      string dCqjoSEZgW;
      string XyCnZkRRJV;
      string XZHjNZEdMW;
      string lrUNXCMVsk;
      if(DMXGRuuEzk == BBVJffewpx){AQwyxsehUp = true;}
      else if(BBVJffewpx == DMXGRuuEzk){uVPirXkzIb = true;}
      if(jFhqRnHgiK == tcNhIWChod){MgxMsEtGVP = true;}
      else if(tcNhIWChod == jFhqRnHgiK){KOmfgrUUjz = true;}
      if(fWkHWVDfLb == nWBNaOCcFF){OZMJkedoQW = true;}
      else if(nWBNaOCcFF == fWkHWVDfLb){UNUwijoBtO = true;}
      if(WulAeIUtZk == HaYmAkzDeB){XuYYVGcJlU = true;}
      else if(HaYmAkzDeB == WulAeIUtZk){pFjFkPGlFp = true;}
      if(KIjmEUihRA == EDFiEEqcUV){uVJWKEtHUS = true;}
      else if(EDFiEEqcUV == KIjmEUihRA){gxlaknEPmO = true;}
      if(sltpTgaQju == qhWtadzHiQ){IFzdVaElNR = true;}
      else if(qhWtadzHiQ == sltpTgaQju){kiaFYhATzI = true;}
      if(rPsXOoThLI == dCqjoSEZgW){OoRyRQIYql = true;}
      else if(dCqjoSEZgW == rPsXOoThLI){ijEslFdguQ = true;}
      if(TMHyAWmxCC == XyCnZkRRJV){akUAUsPozg = true;}
      if(mUNLhjAwfy == XZHjNZEdMW){kWUxNRwuDu = true;}
      if(hEKdrtPLYP == lrUNXCMVsk){CqwTGFDKFs = true;}
      while(XyCnZkRRJV == TMHyAWmxCC){liPsSXasLu = true;}
      while(XZHjNZEdMW == XZHjNZEdMW){eYNfdGdefD = true;}
      while(lrUNXCMVsk == lrUNXCMVsk){PllwHxrroe = true;}
      if(AQwyxsehUp == true){AQwyxsehUp = false;}
      if(MgxMsEtGVP == true){MgxMsEtGVP = false;}
      if(OZMJkedoQW == true){OZMJkedoQW = false;}
      if(XuYYVGcJlU == true){XuYYVGcJlU = false;}
      if(uVJWKEtHUS == true){uVJWKEtHUS = false;}
      if(IFzdVaElNR == true){IFzdVaElNR = false;}
      if(OoRyRQIYql == true){OoRyRQIYql = false;}
      if(akUAUsPozg == true){akUAUsPozg = false;}
      if(kWUxNRwuDu == true){kWUxNRwuDu = false;}
      if(CqwTGFDKFs == true){CqwTGFDKFs = false;}
      if(uVPirXkzIb == true){uVPirXkzIb = false;}
      if(KOmfgrUUjz == true){KOmfgrUUjz = false;}
      if(UNUwijoBtO == true){UNUwijoBtO = false;}
      if(pFjFkPGlFp == true){pFjFkPGlFp = false;}
      if(gxlaknEPmO == true){gxlaknEPmO = false;}
      if(kiaFYhATzI == true){kiaFYhATzI = false;}
      if(ijEslFdguQ == true){ijEslFdguQ = false;}
      if(liPsSXasLu == true){liPsSXasLu = false;}
      if(eYNfdGdefD == true){eYNfdGdefD = false;}
      if(PllwHxrroe == true){PllwHxrroe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMHOPEVATP
{ 
  void esKIySuPTs()
  { 
      bool UpKRIArGOB = false;
      bool aNLKGJRsML = false;
      bool SLPiutmrqP = false;
      bool lPBDRBpqdM = false;
      bool pLgXZoMmcf = false;
      bool AeaAcIaaVO = false;
      bool MAOyOLLHrF = false;
      bool TZPzVHerIF = false;
      bool gzOLOHnBZJ = false;
      bool aOUOAowhIO = false;
      bool dEuXLZObeV = false;
      bool chRQgMkDjH = false;
      bool XKhhdFFAzg = false;
      bool KxitbcEqzn = false;
      bool rMVEgswEhm = false;
      bool DsxBqSWMsG = false;
      bool UNbxKeyXnE = false;
      bool HtDuOKndBk = false;
      bool IBSMcRAhDI = false;
      bool GrxsTdjYsB = false;
      string BUCHNszdDf;
      string IZNoedCXwZ;
      string gjGMTFSJLP;
      string MoZlmoxxDE;
      string IyJqwtasBD;
      string JTnogQOpnI;
      string aoSnTSAbCo;
      string fETrRiaOPY;
      string dZHHFrBjFW;
      string aGJtcSfVXd;
      string typLXFzuXx;
      string pzaOdBgKha;
      string QPVfOYuYOy;
      string DFqlefiuiA;
      string sFMHfbftQb;
      string kUmwMdbKxz;
      string KZgYtjHojy;
      string SkbghLDOzm;
      string rAImMhRuYA;
      string DXyjpSYnMw;
      if(BUCHNszdDf == typLXFzuXx){UpKRIArGOB = true;}
      else if(typLXFzuXx == BUCHNszdDf){dEuXLZObeV = true;}
      if(IZNoedCXwZ == pzaOdBgKha){aNLKGJRsML = true;}
      else if(pzaOdBgKha == IZNoedCXwZ){chRQgMkDjH = true;}
      if(gjGMTFSJLP == QPVfOYuYOy){SLPiutmrqP = true;}
      else if(QPVfOYuYOy == gjGMTFSJLP){XKhhdFFAzg = true;}
      if(MoZlmoxxDE == DFqlefiuiA){lPBDRBpqdM = true;}
      else if(DFqlefiuiA == MoZlmoxxDE){KxitbcEqzn = true;}
      if(IyJqwtasBD == sFMHfbftQb){pLgXZoMmcf = true;}
      else if(sFMHfbftQb == IyJqwtasBD){rMVEgswEhm = true;}
      if(JTnogQOpnI == kUmwMdbKxz){AeaAcIaaVO = true;}
      else if(kUmwMdbKxz == JTnogQOpnI){DsxBqSWMsG = true;}
      if(aoSnTSAbCo == KZgYtjHojy){MAOyOLLHrF = true;}
      else if(KZgYtjHojy == aoSnTSAbCo){UNbxKeyXnE = true;}
      if(fETrRiaOPY == SkbghLDOzm){TZPzVHerIF = true;}
      if(dZHHFrBjFW == rAImMhRuYA){gzOLOHnBZJ = true;}
      if(aGJtcSfVXd == DXyjpSYnMw){aOUOAowhIO = true;}
      while(SkbghLDOzm == fETrRiaOPY){HtDuOKndBk = true;}
      while(rAImMhRuYA == rAImMhRuYA){IBSMcRAhDI = true;}
      while(DXyjpSYnMw == DXyjpSYnMw){GrxsTdjYsB = true;}
      if(UpKRIArGOB == true){UpKRIArGOB = false;}
      if(aNLKGJRsML == true){aNLKGJRsML = false;}
      if(SLPiutmrqP == true){SLPiutmrqP = false;}
      if(lPBDRBpqdM == true){lPBDRBpqdM = false;}
      if(pLgXZoMmcf == true){pLgXZoMmcf = false;}
      if(AeaAcIaaVO == true){AeaAcIaaVO = false;}
      if(MAOyOLLHrF == true){MAOyOLLHrF = false;}
      if(TZPzVHerIF == true){TZPzVHerIF = false;}
      if(gzOLOHnBZJ == true){gzOLOHnBZJ = false;}
      if(aOUOAowhIO == true){aOUOAowhIO = false;}
      if(dEuXLZObeV == true){dEuXLZObeV = false;}
      if(chRQgMkDjH == true){chRQgMkDjH = false;}
      if(XKhhdFFAzg == true){XKhhdFFAzg = false;}
      if(KxitbcEqzn == true){KxitbcEqzn = false;}
      if(rMVEgswEhm == true){rMVEgswEhm = false;}
      if(DsxBqSWMsG == true){DsxBqSWMsG = false;}
      if(UNbxKeyXnE == true){UNbxKeyXnE = false;}
      if(HtDuOKndBk == true){HtDuOKndBk = false;}
      if(IBSMcRAhDI == true){IBSMcRAhDI = false;}
      if(GrxsTdjYsB == true){GrxsTdjYsB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AWCDRBXYDO
{ 
  void xONsJGOntp()
  { 
      bool zGjhlooxJr = false;
      bool BrCRPGYZey = false;
      bool gNBDfTnjYj = false;
      bool ZZwqBwNuMS = false;
      bool FwlNPsrcnk = false;
      bool ZKKjOlFgBR = false;
      bool BFYZSbwKQS = false;
      bool rdNLsjamml = false;
      bool aKunKOOLcP = false;
      bool qgstRzXMun = false;
      bool xgMVrwxzqd = false;
      bool KRtOqpKkPD = false;
      bool MjhBaKjSss = false;
      bool MOrynsyYuO = false;
      bool RPTyEZmeDb = false;
      bool olxraNzKtg = false;
      bool LdFyQwZuZx = false;
      bool qkpAkxPjwB = false;
      bool XFPRDaRAXa = false;
      bool tmdNCnJVgI = false;
      string kXolQGbLkZ;
      string CRNsrXQkyR;
      string UTHtpGOlqW;
      string LFaRYYZEiu;
      string MImpQzWXui;
      string TgZbbQQtuJ;
      string roTOOxquUS;
      string xLCCFLgQcq;
      string jpqIDeezpI;
      string IfIZDWnYbT;
      string IbDckHdWVP;
      string jzQDZBxLLi;
      string RqFMJRDczh;
      string WHoIiHlNWu;
      string AHcaXJOEzB;
      string YcNrCQWqSS;
      string EBXmrbJHUR;
      string PjnPiJOdnA;
      string DycyIttwGR;
      string kuuEqyjohw;
      if(kXolQGbLkZ == IbDckHdWVP){zGjhlooxJr = true;}
      else if(IbDckHdWVP == kXolQGbLkZ){xgMVrwxzqd = true;}
      if(CRNsrXQkyR == jzQDZBxLLi){BrCRPGYZey = true;}
      else if(jzQDZBxLLi == CRNsrXQkyR){KRtOqpKkPD = true;}
      if(UTHtpGOlqW == RqFMJRDczh){gNBDfTnjYj = true;}
      else if(RqFMJRDczh == UTHtpGOlqW){MjhBaKjSss = true;}
      if(LFaRYYZEiu == WHoIiHlNWu){ZZwqBwNuMS = true;}
      else if(WHoIiHlNWu == LFaRYYZEiu){MOrynsyYuO = true;}
      if(MImpQzWXui == AHcaXJOEzB){FwlNPsrcnk = true;}
      else if(AHcaXJOEzB == MImpQzWXui){RPTyEZmeDb = true;}
      if(TgZbbQQtuJ == YcNrCQWqSS){ZKKjOlFgBR = true;}
      else if(YcNrCQWqSS == TgZbbQQtuJ){olxraNzKtg = true;}
      if(roTOOxquUS == EBXmrbJHUR){BFYZSbwKQS = true;}
      else if(EBXmrbJHUR == roTOOxquUS){LdFyQwZuZx = true;}
      if(xLCCFLgQcq == PjnPiJOdnA){rdNLsjamml = true;}
      if(jpqIDeezpI == DycyIttwGR){aKunKOOLcP = true;}
      if(IfIZDWnYbT == kuuEqyjohw){qgstRzXMun = true;}
      while(PjnPiJOdnA == xLCCFLgQcq){qkpAkxPjwB = true;}
      while(DycyIttwGR == DycyIttwGR){XFPRDaRAXa = true;}
      while(kuuEqyjohw == kuuEqyjohw){tmdNCnJVgI = true;}
      if(zGjhlooxJr == true){zGjhlooxJr = false;}
      if(BrCRPGYZey == true){BrCRPGYZey = false;}
      if(gNBDfTnjYj == true){gNBDfTnjYj = false;}
      if(ZZwqBwNuMS == true){ZZwqBwNuMS = false;}
      if(FwlNPsrcnk == true){FwlNPsrcnk = false;}
      if(ZKKjOlFgBR == true){ZKKjOlFgBR = false;}
      if(BFYZSbwKQS == true){BFYZSbwKQS = false;}
      if(rdNLsjamml == true){rdNLsjamml = false;}
      if(aKunKOOLcP == true){aKunKOOLcP = false;}
      if(qgstRzXMun == true){qgstRzXMun = false;}
      if(xgMVrwxzqd == true){xgMVrwxzqd = false;}
      if(KRtOqpKkPD == true){KRtOqpKkPD = false;}
      if(MjhBaKjSss == true){MjhBaKjSss = false;}
      if(MOrynsyYuO == true){MOrynsyYuO = false;}
      if(RPTyEZmeDb == true){RPTyEZmeDb = false;}
      if(olxraNzKtg == true){olxraNzKtg = false;}
      if(LdFyQwZuZx == true){LdFyQwZuZx = false;}
      if(qkpAkxPjwB == true){qkpAkxPjwB = false;}
      if(XFPRDaRAXa == true){XFPRDaRAXa = false;}
      if(tmdNCnJVgI == true){tmdNCnJVgI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZEIMCSAJO
{ 
  void ckRFFIPdqR()
  { 
      bool EPOqnqghaf = false;
      bool cTEBtHQXnQ = false;
      bool ebJbIogWYX = false;
      bool yGaABQLlMB = false;
      bool sZqEnZrlOU = false;
      bool gLaEncGlhz = false;
      bool JJJDgWrDzd = false;
      bool wdKlWEkFni = false;
      bool xuIDplfWMY = false;
      bool JYEMrjQmWR = false;
      bool goljYCAnhi = false;
      bool qAyyCNBFMt = false;
      bool pVpaTWZxtm = false;
      bool nxiVCHJXem = false;
      bool lqncgJaFKd = false;
      bool iKZbaKyKPC = false;
      bool cCtuutRbwt = false;
      bool EcaYIyhMsK = false;
      bool wUmQEcXGtq = false;
      bool JyHbKixshm = false;
      string jrtzHCIjbc;
      string MJzOFmReLk;
      string XRICELciOq;
      string FOHwDrtOBE;
      string CCehBUcKaL;
      string SuGWCRjruu;
      string YYVjXyCCLN;
      string sCcGiVmZAi;
      string iSIDYJHjsk;
      string IBTFfcftKD;
      string RZyMSPRzmg;
      string eJqLLFQRKN;
      string pSJZFqhWaG;
      string orPxRJUukJ;
      string rIwMGyKIsZ;
      string MOjxNzQXHa;
      string gtYgqmtttC;
      string kUgBVhVwTG;
      string gZdBsaISjR;
      string swmJbxiOUS;
      if(jrtzHCIjbc == RZyMSPRzmg){EPOqnqghaf = true;}
      else if(RZyMSPRzmg == jrtzHCIjbc){goljYCAnhi = true;}
      if(MJzOFmReLk == eJqLLFQRKN){cTEBtHQXnQ = true;}
      else if(eJqLLFQRKN == MJzOFmReLk){qAyyCNBFMt = true;}
      if(XRICELciOq == pSJZFqhWaG){ebJbIogWYX = true;}
      else if(pSJZFqhWaG == XRICELciOq){pVpaTWZxtm = true;}
      if(FOHwDrtOBE == orPxRJUukJ){yGaABQLlMB = true;}
      else if(orPxRJUukJ == FOHwDrtOBE){nxiVCHJXem = true;}
      if(CCehBUcKaL == rIwMGyKIsZ){sZqEnZrlOU = true;}
      else if(rIwMGyKIsZ == CCehBUcKaL){lqncgJaFKd = true;}
      if(SuGWCRjruu == MOjxNzQXHa){gLaEncGlhz = true;}
      else if(MOjxNzQXHa == SuGWCRjruu){iKZbaKyKPC = true;}
      if(YYVjXyCCLN == gtYgqmtttC){JJJDgWrDzd = true;}
      else if(gtYgqmtttC == YYVjXyCCLN){cCtuutRbwt = true;}
      if(sCcGiVmZAi == kUgBVhVwTG){wdKlWEkFni = true;}
      if(iSIDYJHjsk == gZdBsaISjR){xuIDplfWMY = true;}
      if(IBTFfcftKD == swmJbxiOUS){JYEMrjQmWR = true;}
      while(kUgBVhVwTG == sCcGiVmZAi){EcaYIyhMsK = true;}
      while(gZdBsaISjR == gZdBsaISjR){wUmQEcXGtq = true;}
      while(swmJbxiOUS == swmJbxiOUS){JyHbKixshm = true;}
      if(EPOqnqghaf == true){EPOqnqghaf = false;}
      if(cTEBtHQXnQ == true){cTEBtHQXnQ = false;}
      if(ebJbIogWYX == true){ebJbIogWYX = false;}
      if(yGaABQLlMB == true){yGaABQLlMB = false;}
      if(sZqEnZrlOU == true){sZqEnZrlOU = false;}
      if(gLaEncGlhz == true){gLaEncGlhz = false;}
      if(JJJDgWrDzd == true){JJJDgWrDzd = false;}
      if(wdKlWEkFni == true){wdKlWEkFni = false;}
      if(xuIDplfWMY == true){xuIDplfWMY = false;}
      if(JYEMrjQmWR == true){JYEMrjQmWR = false;}
      if(goljYCAnhi == true){goljYCAnhi = false;}
      if(qAyyCNBFMt == true){qAyyCNBFMt = false;}
      if(pVpaTWZxtm == true){pVpaTWZxtm = false;}
      if(nxiVCHJXem == true){nxiVCHJXem = false;}
      if(lqncgJaFKd == true){lqncgJaFKd = false;}
      if(iKZbaKyKPC == true){iKZbaKyKPC = false;}
      if(cCtuutRbwt == true){cCtuutRbwt = false;}
      if(EcaYIyhMsK == true){EcaYIyhMsK = false;}
      if(wUmQEcXGtq == true){wUmQEcXGtq = false;}
      if(JyHbKixshm == true){JyHbKixshm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJXLQJROKI
{ 
  void NWgmRPzMSm()
  { 
      bool FiqgJVrzWi = false;
      bool RhSzEAbajK = false;
      bool EKbNeMVyCb = false;
      bool eIGeTPIDTZ = false;
      bool TQlbZqVVnx = false;
      bool tKRCptHdBw = false;
      bool AtxuEIaneo = false;
      bool rXHJqnYzmm = false;
      bool qzKFgUqDoY = false;
      bool IdBWZZSqWQ = false;
      bool QhpyEVCHLC = false;
      bool VHpOFAirNj = false;
      bool RWzGfNWkjR = false;
      bool UgcWVJILAL = false;
      bool RirlCBnlRZ = false;
      bool padmysijSq = false;
      bool zRWsgoeTru = false;
      bool qWqBRheMDe = false;
      bool ZjSKasCoXc = false;
      bool ZYsIMALyFN = false;
      string yCemInRzBh;
      string wizkWczRcH;
      string GBaNZunOmI;
      string lHSqwzlhdu;
      string BkowukNXwQ;
      string OUZunwbQMN;
      string ADLrwnQHoX;
      string pRmhGUMdSn;
      string gQSWtQhWDz;
      string XUUQtxYxAG;
      string UGhYZwhqoS;
      string jxyYfikoxf;
      string GsEozVwVmI;
      string wPdLTahtxx;
      string hphjPZVwkK;
      string MjzTAbBsYE;
      string AMEfWUTmEE;
      string BpqzxQKTZZ;
      string zzjcwLPJLq;
      string ZoUsxVlBNt;
      if(yCemInRzBh == UGhYZwhqoS){FiqgJVrzWi = true;}
      else if(UGhYZwhqoS == yCemInRzBh){QhpyEVCHLC = true;}
      if(wizkWczRcH == jxyYfikoxf){RhSzEAbajK = true;}
      else if(jxyYfikoxf == wizkWczRcH){VHpOFAirNj = true;}
      if(GBaNZunOmI == GsEozVwVmI){EKbNeMVyCb = true;}
      else if(GsEozVwVmI == GBaNZunOmI){RWzGfNWkjR = true;}
      if(lHSqwzlhdu == wPdLTahtxx){eIGeTPIDTZ = true;}
      else if(wPdLTahtxx == lHSqwzlhdu){UgcWVJILAL = true;}
      if(BkowukNXwQ == hphjPZVwkK){TQlbZqVVnx = true;}
      else if(hphjPZVwkK == BkowukNXwQ){RirlCBnlRZ = true;}
      if(OUZunwbQMN == MjzTAbBsYE){tKRCptHdBw = true;}
      else if(MjzTAbBsYE == OUZunwbQMN){padmysijSq = true;}
      if(ADLrwnQHoX == AMEfWUTmEE){AtxuEIaneo = true;}
      else if(AMEfWUTmEE == ADLrwnQHoX){zRWsgoeTru = true;}
      if(pRmhGUMdSn == BpqzxQKTZZ){rXHJqnYzmm = true;}
      if(gQSWtQhWDz == zzjcwLPJLq){qzKFgUqDoY = true;}
      if(XUUQtxYxAG == ZoUsxVlBNt){IdBWZZSqWQ = true;}
      while(BpqzxQKTZZ == pRmhGUMdSn){qWqBRheMDe = true;}
      while(zzjcwLPJLq == zzjcwLPJLq){ZjSKasCoXc = true;}
      while(ZoUsxVlBNt == ZoUsxVlBNt){ZYsIMALyFN = true;}
      if(FiqgJVrzWi == true){FiqgJVrzWi = false;}
      if(RhSzEAbajK == true){RhSzEAbajK = false;}
      if(EKbNeMVyCb == true){EKbNeMVyCb = false;}
      if(eIGeTPIDTZ == true){eIGeTPIDTZ = false;}
      if(TQlbZqVVnx == true){TQlbZqVVnx = false;}
      if(tKRCptHdBw == true){tKRCptHdBw = false;}
      if(AtxuEIaneo == true){AtxuEIaneo = false;}
      if(rXHJqnYzmm == true){rXHJqnYzmm = false;}
      if(qzKFgUqDoY == true){qzKFgUqDoY = false;}
      if(IdBWZZSqWQ == true){IdBWZZSqWQ = false;}
      if(QhpyEVCHLC == true){QhpyEVCHLC = false;}
      if(VHpOFAirNj == true){VHpOFAirNj = false;}
      if(RWzGfNWkjR == true){RWzGfNWkjR = false;}
      if(UgcWVJILAL == true){UgcWVJILAL = false;}
      if(RirlCBnlRZ == true){RirlCBnlRZ = false;}
      if(padmysijSq == true){padmysijSq = false;}
      if(zRWsgoeTru == true){zRWsgoeTru = false;}
      if(qWqBRheMDe == true){qWqBRheMDe = false;}
      if(ZjSKasCoXc == true){ZjSKasCoXc = false;}
      if(ZYsIMALyFN == true){ZYsIMALyFN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWQFALMOOC
{ 
  void HYEFsYKuCw()
  { 
      bool goLrNozxWC = false;
      bool shjfBobqNo = false;
      bool tXSdoMoTTZ = false;
      bool HcAidCfTcq = false;
      bool NwPKkTODaO = false;
      bool gUxXJJWgDA = false;
      bool zfcxuPgACz = false;
      bool JHNWbyIIrU = false;
      bool ylrFrlebZU = false;
      bool eyQbqhSRPU = false;
      bool lNAbEYGawL = false;
      bool AOnhBNmWEI = false;
      bool jFahTKqlet = false;
      bool epsWhkkPBT = false;
      bool fEfNTQJhad = false;
      bool tuNGkglSIs = false;
      bool hUwCfKURAP = false;
      bool bXVkcfYNNC = false;
      bool AJKBzjcllA = false;
      bool zRHHkKIdhI = false;
      string KOnRIdbaFx;
      string NdKcaTxCuj;
      string dKeFHxPJgT;
      string jKnHxdUyiW;
      string dHPzlRblpE;
      string qDUtgziiJK;
      string NRtkMCoDex;
      string yzTYFWtfSo;
      string VdTbcgotZx;
      string tknXJLNeli;
      string cYGsGqiwnK;
      string EDPUnjyRIf;
      string MtchCNKuPs;
      string IPsjMxXZVk;
      string xsFPsqVTiY;
      string NuVGWhuYqs;
      string gngtCnKfIq;
      string LXwXiToNnK;
      string qqLpfMtlNd;
      string CyicDILLNE;
      if(KOnRIdbaFx == cYGsGqiwnK){goLrNozxWC = true;}
      else if(cYGsGqiwnK == KOnRIdbaFx){lNAbEYGawL = true;}
      if(NdKcaTxCuj == EDPUnjyRIf){shjfBobqNo = true;}
      else if(EDPUnjyRIf == NdKcaTxCuj){AOnhBNmWEI = true;}
      if(dKeFHxPJgT == MtchCNKuPs){tXSdoMoTTZ = true;}
      else if(MtchCNKuPs == dKeFHxPJgT){jFahTKqlet = true;}
      if(jKnHxdUyiW == IPsjMxXZVk){HcAidCfTcq = true;}
      else if(IPsjMxXZVk == jKnHxdUyiW){epsWhkkPBT = true;}
      if(dHPzlRblpE == xsFPsqVTiY){NwPKkTODaO = true;}
      else if(xsFPsqVTiY == dHPzlRblpE){fEfNTQJhad = true;}
      if(qDUtgziiJK == NuVGWhuYqs){gUxXJJWgDA = true;}
      else if(NuVGWhuYqs == qDUtgziiJK){tuNGkglSIs = true;}
      if(NRtkMCoDex == gngtCnKfIq){zfcxuPgACz = true;}
      else if(gngtCnKfIq == NRtkMCoDex){hUwCfKURAP = true;}
      if(yzTYFWtfSo == LXwXiToNnK){JHNWbyIIrU = true;}
      if(VdTbcgotZx == qqLpfMtlNd){ylrFrlebZU = true;}
      if(tknXJLNeli == CyicDILLNE){eyQbqhSRPU = true;}
      while(LXwXiToNnK == yzTYFWtfSo){bXVkcfYNNC = true;}
      while(qqLpfMtlNd == qqLpfMtlNd){AJKBzjcllA = true;}
      while(CyicDILLNE == CyicDILLNE){zRHHkKIdhI = true;}
      if(goLrNozxWC == true){goLrNozxWC = false;}
      if(shjfBobqNo == true){shjfBobqNo = false;}
      if(tXSdoMoTTZ == true){tXSdoMoTTZ = false;}
      if(HcAidCfTcq == true){HcAidCfTcq = false;}
      if(NwPKkTODaO == true){NwPKkTODaO = false;}
      if(gUxXJJWgDA == true){gUxXJJWgDA = false;}
      if(zfcxuPgACz == true){zfcxuPgACz = false;}
      if(JHNWbyIIrU == true){JHNWbyIIrU = false;}
      if(ylrFrlebZU == true){ylrFrlebZU = false;}
      if(eyQbqhSRPU == true){eyQbqhSRPU = false;}
      if(lNAbEYGawL == true){lNAbEYGawL = false;}
      if(AOnhBNmWEI == true){AOnhBNmWEI = false;}
      if(jFahTKqlet == true){jFahTKqlet = false;}
      if(epsWhkkPBT == true){epsWhkkPBT = false;}
      if(fEfNTQJhad == true){fEfNTQJhad = false;}
      if(tuNGkglSIs == true){tuNGkglSIs = false;}
      if(hUwCfKURAP == true){hUwCfKURAP = false;}
      if(bXVkcfYNNC == true){bXVkcfYNNC = false;}
      if(AJKBzjcllA == true){AJKBzjcllA = false;}
      if(zRHHkKIdhI == true){zRHHkKIdhI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDHAXJTCQX
{ 
  void GLLIczuNdy()
  { 
      bool VjKrJFoYoF = false;
      bool zTjehSlkGB = false;
      bool CbFxClYKnT = false;
      bool GpAcSzHeuN = false;
      bool dNZDcrXPVZ = false;
      bool gJRnDsdNpX = false;
      bool fejUyJSHMh = false;
      bool LGorWoCCTK = false;
      bool NJnOmxXLZY = false;
      bool VsoWhzcEFS = false;
      bool YQDmOZTYRN = false;
      bool paseJWpUgA = false;
      bool kGhmMRRSKX = false;
      bool LywBkxGAAN = false;
      bool dytLitzJNK = false;
      bool IHWEgShPaw = false;
      bool HANsBrertL = false;
      bool PpUSWmMVER = false;
      bool SIFzPDarTS = false;
      bool OpZDGckAJq = false;
      string uUBCNMUhkD;
      string hSGWIYhdxf;
      string BEEQVuVBdI;
      string YOnDRLNfIP;
      string cqtVKFOzRK;
      string pIfWBpQkfR;
      string pSDcdSeDEw;
      string LCVgCKJhGQ;
      string gVjTRPhRCa;
      string uczqYJmRqq;
      string aLuUznmyTq;
      string ghdPjUiiLO;
      string kMBcBhCdIs;
      string WrqPpVaOUd;
      string bjyKtMyjGD;
      string ZDGbGNKSTQ;
      string kJoZUnqOYO;
      string tUOgmAOphn;
      string iRWETSlOIb;
      string LHuDrStYpF;
      if(uUBCNMUhkD == aLuUznmyTq){VjKrJFoYoF = true;}
      else if(aLuUznmyTq == uUBCNMUhkD){YQDmOZTYRN = true;}
      if(hSGWIYhdxf == ghdPjUiiLO){zTjehSlkGB = true;}
      else if(ghdPjUiiLO == hSGWIYhdxf){paseJWpUgA = true;}
      if(BEEQVuVBdI == kMBcBhCdIs){CbFxClYKnT = true;}
      else if(kMBcBhCdIs == BEEQVuVBdI){kGhmMRRSKX = true;}
      if(YOnDRLNfIP == WrqPpVaOUd){GpAcSzHeuN = true;}
      else if(WrqPpVaOUd == YOnDRLNfIP){LywBkxGAAN = true;}
      if(cqtVKFOzRK == bjyKtMyjGD){dNZDcrXPVZ = true;}
      else if(bjyKtMyjGD == cqtVKFOzRK){dytLitzJNK = true;}
      if(pIfWBpQkfR == ZDGbGNKSTQ){gJRnDsdNpX = true;}
      else if(ZDGbGNKSTQ == pIfWBpQkfR){IHWEgShPaw = true;}
      if(pSDcdSeDEw == kJoZUnqOYO){fejUyJSHMh = true;}
      else if(kJoZUnqOYO == pSDcdSeDEw){HANsBrertL = true;}
      if(LCVgCKJhGQ == tUOgmAOphn){LGorWoCCTK = true;}
      if(gVjTRPhRCa == iRWETSlOIb){NJnOmxXLZY = true;}
      if(uczqYJmRqq == LHuDrStYpF){VsoWhzcEFS = true;}
      while(tUOgmAOphn == LCVgCKJhGQ){PpUSWmMVER = true;}
      while(iRWETSlOIb == iRWETSlOIb){SIFzPDarTS = true;}
      while(LHuDrStYpF == LHuDrStYpF){OpZDGckAJq = true;}
      if(VjKrJFoYoF == true){VjKrJFoYoF = false;}
      if(zTjehSlkGB == true){zTjehSlkGB = false;}
      if(CbFxClYKnT == true){CbFxClYKnT = false;}
      if(GpAcSzHeuN == true){GpAcSzHeuN = false;}
      if(dNZDcrXPVZ == true){dNZDcrXPVZ = false;}
      if(gJRnDsdNpX == true){gJRnDsdNpX = false;}
      if(fejUyJSHMh == true){fejUyJSHMh = false;}
      if(LGorWoCCTK == true){LGorWoCCTK = false;}
      if(NJnOmxXLZY == true){NJnOmxXLZY = false;}
      if(VsoWhzcEFS == true){VsoWhzcEFS = false;}
      if(YQDmOZTYRN == true){YQDmOZTYRN = false;}
      if(paseJWpUgA == true){paseJWpUgA = false;}
      if(kGhmMRRSKX == true){kGhmMRRSKX = false;}
      if(LywBkxGAAN == true){LywBkxGAAN = false;}
      if(dytLitzJNK == true){dytLitzJNK = false;}
      if(IHWEgShPaw == true){IHWEgShPaw = false;}
      if(HANsBrertL == true){HANsBrertL = false;}
      if(PpUSWmMVER == true){PpUSWmMVER = false;}
      if(SIFzPDarTS == true){SIFzPDarTS = false;}
      if(OpZDGckAJq == true){OpZDGckAJq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVIAYINHQO
{ 
  void zAkrICVdUJ()
  { 
      bool xVTucfcjRb = false;
      bool TJIzyLDOSh = false;
      bool mSLIPslFDx = false;
      bool iXDehDgesA = false;
      bool bDZcHTYMbs = false;
      bool FWhQPeKKej = false;
      bool sXgTruGcRu = false;
      bool eXUSFisiAu = false;
      bool TZdKrMplOD = false;
      bool sVAIGEWFjM = false;
      bool NuufNgBOLg = false;
      bool lbJiPTsVaf = false;
      bool FUONCIXMLA = false;
      bool LmynhYdywL = false;
      bool KaahRRLRrl = false;
      bool LAdDGsghcF = false;
      bool JoDKUycVAq = false;
      bool puZPVdsfwk = false;
      bool wGTYoKItgo = false;
      bool rwUqCUXPNS = false;
      string daQuJrLyVn;
      string oHboIlVwtT;
      string BXVEzdWElO;
      string PQQtrlSGFU;
      string gzYoMKjypD;
      string fijBEGFLue;
      string UHMGYXpgxV;
      string TPpZmByfqo;
      string tXNhhfgPpl;
      string gGKZAZmRQo;
      string TDBUjQsKNC;
      string HYTGkwsdYr;
      string qapLnMEPZN;
      string OgOCUqWsyQ;
      string lVBmdHmEoD;
      string fIrXxsMpfX;
      string LdkAnaJQkt;
      string ZzfIGUYCgf;
      string YAZVgFnqFb;
      string dgMZEIkAzC;
      if(daQuJrLyVn == TDBUjQsKNC){xVTucfcjRb = true;}
      else if(TDBUjQsKNC == daQuJrLyVn){NuufNgBOLg = true;}
      if(oHboIlVwtT == HYTGkwsdYr){TJIzyLDOSh = true;}
      else if(HYTGkwsdYr == oHboIlVwtT){lbJiPTsVaf = true;}
      if(BXVEzdWElO == qapLnMEPZN){mSLIPslFDx = true;}
      else if(qapLnMEPZN == BXVEzdWElO){FUONCIXMLA = true;}
      if(PQQtrlSGFU == OgOCUqWsyQ){iXDehDgesA = true;}
      else if(OgOCUqWsyQ == PQQtrlSGFU){LmynhYdywL = true;}
      if(gzYoMKjypD == lVBmdHmEoD){bDZcHTYMbs = true;}
      else if(lVBmdHmEoD == gzYoMKjypD){KaahRRLRrl = true;}
      if(fijBEGFLue == fIrXxsMpfX){FWhQPeKKej = true;}
      else if(fIrXxsMpfX == fijBEGFLue){LAdDGsghcF = true;}
      if(UHMGYXpgxV == LdkAnaJQkt){sXgTruGcRu = true;}
      else if(LdkAnaJQkt == UHMGYXpgxV){JoDKUycVAq = true;}
      if(TPpZmByfqo == ZzfIGUYCgf){eXUSFisiAu = true;}
      if(tXNhhfgPpl == YAZVgFnqFb){TZdKrMplOD = true;}
      if(gGKZAZmRQo == dgMZEIkAzC){sVAIGEWFjM = true;}
      while(ZzfIGUYCgf == TPpZmByfqo){puZPVdsfwk = true;}
      while(YAZVgFnqFb == YAZVgFnqFb){wGTYoKItgo = true;}
      while(dgMZEIkAzC == dgMZEIkAzC){rwUqCUXPNS = true;}
      if(xVTucfcjRb == true){xVTucfcjRb = false;}
      if(TJIzyLDOSh == true){TJIzyLDOSh = false;}
      if(mSLIPslFDx == true){mSLIPslFDx = false;}
      if(iXDehDgesA == true){iXDehDgesA = false;}
      if(bDZcHTYMbs == true){bDZcHTYMbs = false;}
      if(FWhQPeKKej == true){FWhQPeKKej = false;}
      if(sXgTruGcRu == true){sXgTruGcRu = false;}
      if(eXUSFisiAu == true){eXUSFisiAu = false;}
      if(TZdKrMplOD == true){TZdKrMplOD = false;}
      if(sVAIGEWFjM == true){sVAIGEWFjM = false;}
      if(NuufNgBOLg == true){NuufNgBOLg = false;}
      if(lbJiPTsVaf == true){lbJiPTsVaf = false;}
      if(FUONCIXMLA == true){FUONCIXMLA = false;}
      if(LmynhYdywL == true){LmynhYdywL = false;}
      if(KaahRRLRrl == true){KaahRRLRrl = false;}
      if(LAdDGsghcF == true){LAdDGsghcF = false;}
      if(JoDKUycVAq == true){JoDKUycVAq = false;}
      if(puZPVdsfwk == true){puZPVdsfwk = false;}
      if(wGTYoKItgo == true){wGTYoKItgo = false;}
      if(rwUqCUXPNS == true){rwUqCUXPNS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYXFSFVJCF
{ 
  void YgUEcTYHlj()
  { 
      bool GnOcJmjAQs = false;
      bool ZTLrXGEHKN = false;
      bool MiuWkfIsMF = false;
      bool pYrXWQqwyb = false;
      bool dZlQIbVLUF = false;
      bool OJAwVXrrrc = false;
      bool eqnLCAamVH = false;
      bool PIJiimweOI = false;
      bool JwXHpgXwCz = false;
      bool XyEUwlkaOI = false;
      bool AhpMoGARMh = false;
      bool bNdiShTgVU = false;
      bool bejWiQDnlw = false;
      bool BVPFIbFKRi = false;
      bool gGiTWKUUBO = false;
      bool SEEsfUyTdY = false;
      bool DLePgGxXaq = false;
      bool cIOmnVwQzY = false;
      bool uilXdwQVZm = false;
      bool clgsfUaSmQ = false;
      string PqVcKbXiJF;
      string tPQDHkogzE;
      string tFEDDgXMfy;
      string UfSbSKbsnm;
      string AfiyDcBepj;
      string jHFsaJlRYd;
      string ELCLjNwokw;
      string IusMENWGAZ;
      string erVwNMZZAI;
      string YKTJhocWNo;
      string gMstanOsnN;
      string meQzzLoGxX;
      string nVobWyajdO;
      string kzsLsSybUY;
      string yfkmVssUJW;
      string AVYpBKWRWb;
      string MdPZbmlFFg;
      string MMkYYHkCGd;
      string EGZHOOZDJh;
      string ugErLTQLKh;
      if(PqVcKbXiJF == gMstanOsnN){GnOcJmjAQs = true;}
      else if(gMstanOsnN == PqVcKbXiJF){AhpMoGARMh = true;}
      if(tPQDHkogzE == meQzzLoGxX){ZTLrXGEHKN = true;}
      else if(meQzzLoGxX == tPQDHkogzE){bNdiShTgVU = true;}
      if(tFEDDgXMfy == nVobWyajdO){MiuWkfIsMF = true;}
      else if(nVobWyajdO == tFEDDgXMfy){bejWiQDnlw = true;}
      if(UfSbSKbsnm == kzsLsSybUY){pYrXWQqwyb = true;}
      else if(kzsLsSybUY == UfSbSKbsnm){BVPFIbFKRi = true;}
      if(AfiyDcBepj == yfkmVssUJW){dZlQIbVLUF = true;}
      else if(yfkmVssUJW == AfiyDcBepj){gGiTWKUUBO = true;}
      if(jHFsaJlRYd == AVYpBKWRWb){OJAwVXrrrc = true;}
      else if(AVYpBKWRWb == jHFsaJlRYd){SEEsfUyTdY = true;}
      if(ELCLjNwokw == MdPZbmlFFg){eqnLCAamVH = true;}
      else if(MdPZbmlFFg == ELCLjNwokw){DLePgGxXaq = true;}
      if(IusMENWGAZ == MMkYYHkCGd){PIJiimweOI = true;}
      if(erVwNMZZAI == EGZHOOZDJh){JwXHpgXwCz = true;}
      if(YKTJhocWNo == ugErLTQLKh){XyEUwlkaOI = true;}
      while(MMkYYHkCGd == IusMENWGAZ){cIOmnVwQzY = true;}
      while(EGZHOOZDJh == EGZHOOZDJh){uilXdwQVZm = true;}
      while(ugErLTQLKh == ugErLTQLKh){clgsfUaSmQ = true;}
      if(GnOcJmjAQs == true){GnOcJmjAQs = false;}
      if(ZTLrXGEHKN == true){ZTLrXGEHKN = false;}
      if(MiuWkfIsMF == true){MiuWkfIsMF = false;}
      if(pYrXWQqwyb == true){pYrXWQqwyb = false;}
      if(dZlQIbVLUF == true){dZlQIbVLUF = false;}
      if(OJAwVXrrrc == true){OJAwVXrrrc = false;}
      if(eqnLCAamVH == true){eqnLCAamVH = false;}
      if(PIJiimweOI == true){PIJiimweOI = false;}
      if(JwXHpgXwCz == true){JwXHpgXwCz = false;}
      if(XyEUwlkaOI == true){XyEUwlkaOI = false;}
      if(AhpMoGARMh == true){AhpMoGARMh = false;}
      if(bNdiShTgVU == true){bNdiShTgVU = false;}
      if(bejWiQDnlw == true){bejWiQDnlw = false;}
      if(BVPFIbFKRi == true){BVPFIbFKRi = false;}
      if(gGiTWKUUBO == true){gGiTWKUUBO = false;}
      if(SEEsfUyTdY == true){SEEsfUyTdY = false;}
      if(DLePgGxXaq == true){DLePgGxXaq = false;}
      if(cIOmnVwQzY == true){cIOmnVwQzY = false;}
      if(uilXdwQVZm == true){uilXdwQVZm = false;}
      if(clgsfUaSmQ == true){clgsfUaSmQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FAUQQIWSUV
{ 
  void oyHNlAGlkI()
  { 
      bool qrrOIfFRsd = false;
      bool oSgyPxBClr = false;
      bool nxUVVDgBQE = false;
      bool fZlLkkxEdX = false;
      bool JIhQCHcAcP = false;
      bool jmaEgsWVsF = false;
      bool zEBoxPgVNd = false;
      bool AwYOifPDTN = false;
      bool ZgXBTsyhdq = false;
      bool NaLYYEGsSm = false;
      bool aGlzOmNMUB = false;
      bool dTCeeSfAUE = false;
      bool QzrVPZjApd = false;
      bool YVjgmStXlg = false;
      bool ekMcNtXgsF = false;
      bool YGYOVbOPin = false;
      bool DNWpbHiVrL = false;
      bool YHNmZelPIV = false;
      bool CDHjFSwVKK = false;
      bool EdoxcROVAF = false;
      string WnDwSVHrSY;
      string jNItPmzzZA;
      string VnRoVYbHxD;
      string XAFsFWhPgF;
      string RapdndEVNh;
      string TRUqRiWNZt;
      string tztOAiHOns;
      string EjRUiuxmBq;
      string TGtOjFfNaV;
      string ATolKRfacE;
      string WpgTciAzIW;
      string kiMianFfeu;
      string DsmRskueJQ;
      string OWJwUdYZkA;
      string FfFEkQHGLW;
      string MAwhBcCOar;
      string mUoqHOYPNx;
      string OftdoWnigb;
      string coTlEOZauq;
      string aKysNkpNwV;
      if(WnDwSVHrSY == WpgTciAzIW){qrrOIfFRsd = true;}
      else if(WpgTciAzIW == WnDwSVHrSY){aGlzOmNMUB = true;}
      if(jNItPmzzZA == kiMianFfeu){oSgyPxBClr = true;}
      else if(kiMianFfeu == jNItPmzzZA){dTCeeSfAUE = true;}
      if(VnRoVYbHxD == DsmRskueJQ){nxUVVDgBQE = true;}
      else if(DsmRskueJQ == VnRoVYbHxD){QzrVPZjApd = true;}
      if(XAFsFWhPgF == OWJwUdYZkA){fZlLkkxEdX = true;}
      else if(OWJwUdYZkA == XAFsFWhPgF){YVjgmStXlg = true;}
      if(RapdndEVNh == FfFEkQHGLW){JIhQCHcAcP = true;}
      else if(FfFEkQHGLW == RapdndEVNh){ekMcNtXgsF = true;}
      if(TRUqRiWNZt == MAwhBcCOar){jmaEgsWVsF = true;}
      else if(MAwhBcCOar == TRUqRiWNZt){YGYOVbOPin = true;}
      if(tztOAiHOns == mUoqHOYPNx){zEBoxPgVNd = true;}
      else if(mUoqHOYPNx == tztOAiHOns){DNWpbHiVrL = true;}
      if(EjRUiuxmBq == OftdoWnigb){AwYOifPDTN = true;}
      if(TGtOjFfNaV == coTlEOZauq){ZgXBTsyhdq = true;}
      if(ATolKRfacE == aKysNkpNwV){NaLYYEGsSm = true;}
      while(OftdoWnigb == EjRUiuxmBq){YHNmZelPIV = true;}
      while(coTlEOZauq == coTlEOZauq){CDHjFSwVKK = true;}
      while(aKysNkpNwV == aKysNkpNwV){EdoxcROVAF = true;}
      if(qrrOIfFRsd == true){qrrOIfFRsd = false;}
      if(oSgyPxBClr == true){oSgyPxBClr = false;}
      if(nxUVVDgBQE == true){nxUVVDgBQE = false;}
      if(fZlLkkxEdX == true){fZlLkkxEdX = false;}
      if(JIhQCHcAcP == true){JIhQCHcAcP = false;}
      if(jmaEgsWVsF == true){jmaEgsWVsF = false;}
      if(zEBoxPgVNd == true){zEBoxPgVNd = false;}
      if(AwYOifPDTN == true){AwYOifPDTN = false;}
      if(ZgXBTsyhdq == true){ZgXBTsyhdq = false;}
      if(NaLYYEGsSm == true){NaLYYEGsSm = false;}
      if(aGlzOmNMUB == true){aGlzOmNMUB = false;}
      if(dTCeeSfAUE == true){dTCeeSfAUE = false;}
      if(QzrVPZjApd == true){QzrVPZjApd = false;}
      if(YVjgmStXlg == true){YVjgmStXlg = false;}
      if(ekMcNtXgsF == true){ekMcNtXgsF = false;}
      if(YGYOVbOPin == true){YGYOVbOPin = false;}
      if(DNWpbHiVrL == true){DNWpbHiVrL = false;}
      if(YHNmZelPIV == true){YHNmZelPIV = false;}
      if(CDHjFSwVKK == true){CDHjFSwVKK = false;}
      if(EdoxcROVAF == true){EdoxcROVAF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMEXJLNKMA
{ 
  void dXzCghKQUA()
  { 
      bool bqjHOTNGdO = false;
      bool ckTSBIWwsG = false;
      bool SlJraStUag = false;
      bool SwPpcUminn = false;
      bool BjGnlTwSyp = false;
      bool Ujiglphqgw = false;
      bool YrfxwgUcpg = false;
      bool UnIEFhfUFG = false;
      bool WbWjMiMhEm = false;
      bool muBqPIDJrF = false;
      bool zScQUfbdbD = false;
      bool JMlZZxVwjN = false;
      bool TmXDtYlQow = false;
      bool eWcAHDzFPg = false;
      bool GiFBcZJaQR = false;
      bool lHYekLuZWw = false;
      bool sKnfXljlSW = false;
      bool yPfDGkhWZT = false;
      bool OKzXKXyyOu = false;
      bool IZiSmwtZcq = false;
      string FRtRxoCrgD;
      string tjsjMPuSfE;
      string EShHUebdSD;
      string blqGguSNdW;
      string KpMJzylasa;
      string cfIDfljlwR;
      string NYZdaHrlDQ;
      string xgoJsNGXIW;
      string sBkqZwdnat;
      string LgRLJlQiiq;
      string FzWbdwpzJR;
      string fLcYYLmhDe;
      string dDLIEPPcAH;
      string xWoQRsdINd;
      string FeeINzDrmx;
      string yhfDNBnOXN;
      string fNyCUJWMHf;
      string heUYZyYDuE;
      string LXpCIOqkDP;
      string FPkzyrfcmE;
      if(FRtRxoCrgD == FzWbdwpzJR){bqjHOTNGdO = true;}
      else if(FzWbdwpzJR == FRtRxoCrgD){zScQUfbdbD = true;}
      if(tjsjMPuSfE == fLcYYLmhDe){ckTSBIWwsG = true;}
      else if(fLcYYLmhDe == tjsjMPuSfE){JMlZZxVwjN = true;}
      if(EShHUebdSD == dDLIEPPcAH){SlJraStUag = true;}
      else if(dDLIEPPcAH == EShHUebdSD){TmXDtYlQow = true;}
      if(blqGguSNdW == xWoQRsdINd){SwPpcUminn = true;}
      else if(xWoQRsdINd == blqGguSNdW){eWcAHDzFPg = true;}
      if(KpMJzylasa == FeeINzDrmx){BjGnlTwSyp = true;}
      else if(FeeINzDrmx == KpMJzylasa){GiFBcZJaQR = true;}
      if(cfIDfljlwR == yhfDNBnOXN){Ujiglphqgw = true;}
      else if(yhfDNBnOXN == cfIDfljlwR){lHYekLuZWw = true;}
      if(NYZdaHrlDQ == fNyCUJWMHf){YrfxwgUcpg = true;}
      else if(fNyCUJWMHf == NYZdaHrlDQ){sKnfXljlSW = true;}
      if(xgoJsNGXIW == heUYZyYDuE){UnIEFhfUFG = true;}
      if(sBkqZwdnat == LXpCIOqkDP){WbWjMiMhEm = true;}
      if(LgRLJlQiiq == FPkzyrfcmE){muBqPIDJrF = true;}
      while(heUYZyYDuE == xgoJsNGXIW){yPfDGkhWZT = true;}
      while(LXpCIOqkDP == LXpCIOqkDP){OKzXKXyyOu = true;}
      while(FPkzyrfcmE == FPkzyrfcmE){IZiSmwtZcq = true;}
      if(bqjHOTNGdO == true){bqjHOTNGdO = false;}
      if(ckTSBIWwsG == true){ckTSBIWwsG = false;}
      if(SlJraStUag == true){SlJraStUag = false;}
      if(SwPpcUminn == true){SwPpcUminn = false;}
      if(BjGnlTwSyp == true){BjGnlTwSyp = false;}
      if(Ujiglphqgw == true){Ujiglphqgw = false;}
      if(YrfxwgUcpg == true){YrfxwgUcpg = false;}
      if(UnIEFhfUFG == true){UnIEFhfUFG = false;}
      if(WbWjMiMhEm == true){WbWjMiMhEm = false;}
      if(muBqPIDJrF == true){muBqPIDJrF = false;}
      if(zScQUfbdbD == true){zScQUfbdbD = false;}
      if(JMlZZxVwjN == true){JMlZZxVwjN = false;}
      if(TmXDtYlQow == true){TmXDtYlQow = false;}
      if(eWcAHDzFPg == true){eWcAHDzFPg = false;}
      if(GiFBcZJaQR == true){GiFBcZJaQR = false;}
      if(lHYekLuZWw == true){lHYekLuZWw = false;}
      if(sKnfXljlSW == true){sKnfXljlSW = false;}
      if(yPfDGkhWZT == true){yPfDGkhWZT = false;}
      if(OKzXKXyyOu == true){OKzXKXyyOu = false;}
      if(IZiSmwtZcq == true){IZiSmwtZcq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBZTVYWPJT
{ 
  void spLUXYfzuK()
  { 
      bool nABaVApqrA = false;
      bool lDKDJINUXR = false;
      bool zcYdRQopge = false;
      bool SoxKqwfGrW = false;
      bool LffXyWxUYU = false;
      bool QjKPALbWIE = false;
      bool KAJMhwFAMM = false;
      bool bHbBGSwAet = false;
      bool TUQLOidgJf = false;
      bool UJxmLKVTpB = false;
      bool RxHLrIHJJh = false;
      bool OaqNkpiyxy = false;
      bool RXqgrSJnou = false;
      bool xcKccWMESF = false;
      bool aUXbQsRjCU = false;
      bool bXVqjsFaTZ = false;
      bool zSTOjlPOkO = false;
      bool ddeqXwAPPy = false;
      bool BZlTTYGTsi = false;
      bool QkksGIBIqe = false;
      string prZDrOfpKq;
      string TeybozNUhl;
      string ljEDkPhzgU;
      string ldPaaENqyc;
      string QnZqYcoDnn;
      string KRxCkGnWRc;
      string fgIpEpPXBk;
      string lWVFVyJMdI;
      string aeLsJUfMoT;
      string QpYVwjeilh;
      string NQCDCnurgm;
      string xarJCBVPgj;
      string KDhgTuxAIk;
      string SZZutJcHpU;
      string ZmeCWoxPTt;
      string NPCCXKiUiH;
      string puiuUWAxOr;
      string YNYLKWXeKe;
      string xhgOXCWXXj;
      string aHYideEihA;
      if(prZDrOfpKq == NQCDCnurgm){nABaVApqrA = true;}
      else if(NQCDCnurgm == prZDrOfpKq){RxHLrIHJJh = true;}
      if(TeybozNUhl == xarJCBVPgj){lDKDJINUXR = true;}
      else if(xarJCBVPgj == TeybozNUhl){OaqNkpiyxy = true;}
      if(ljEDkPhzgU == KDhgTuxAIk){zcYdRQopge = true;}
      else if(KDhgTuxAIk == ljEDkPhzgU){RXqgrSJnou = true;}
      if(ldPaaENqyc == SZZutJcHpU){SoxKqwfGrW = true;}
      else if(SZZutJcHpU == ldPaaENqyc){xcKccWMESF = true;}
      if(QnZqYcoDnn == ZmeCWoxPTt){LffXyWxUYU = true;}
      else if(ZmeCWoxPTt == QnZqYcoDnn){aUXbQsRjCU = true;}
      if(KRxCkGnWRc == NPCCXKiUiH){QjKPALbWIE = true;}
      else if(NPCCXKiUiH == KRxCkGnWRc){bXVqjsFaTZ = true;}
      if(fgIpEpPXBk == puiuUWAxOr){KAJMhwFAMM = true;}
      else if(puiuUWAxOr == fgIpEpPXBk){zSTOjlPOkO = true;}
      if(lWVFVyJMdI == YNYLKWXeKe){bHbBGSwAet = true;}
      if(aeLsJUfMoT == xhgOXCWXXj){TUQLOidgJf = true;}
      if(QpYVwjeilh == aHYideEihA){UJxmLKVTpB = true;}
      while(YNYLKWXeKe == lWVFVyJMdI){ddeqXwAPPy = true;}
      while(xhgOXCWXXj == xhgOXCWXXj){BZlTTYGTsi = true;}
      while(aHYideEihA == aHYideEihA){QkksGIBIqe = true;}
      if(nABaVApqrA == true){nABaVApqrA = false;}
      if(lDKDJINUXR == true){lDKDJINUXR = false;}
      if(zcYdRQopge == true){zcYdRQopge = false;}
      if(SoxKqwfGrW == true){SoxKqwfGrW = false;}
      if(LffXyWxUYU == true){LffXyWxUYU = false;}
      if(QjKPALbWIE == true){QjKPALbWIE = false;}
      if(KAJMhwFAMM == true){KAJMhwFAMM = false;}
      if(bHbBGSwAet == true){bHbBGSwAet = false;}
      if(TUQLOidgJf == true){TUQLOidgJf = false;}
      if(UJxmLKVTpB == true){UJxmLKVTpB = false;}
      if(RxHLrIHJJh == true){RxHLrIHJJh = false;}
      if(OaqNkpiyxy == true){OaqNkpiyxy = false;}
      if(RXqgrSJnou == true){RXqgrSJnou = false;}
      if(xcKccWMESF == true){xcKccWMESF = false;}
      if(aUXbQsRjCU == true){aUXbQsRjCU = false;}
      if(bXVqjsFaTZ == true){bXVqjsFaTZ = false;}
      if(zSTOjlPOkO == true){zSTOjlPOkO = false;}
      if(ddeqXwAPPy == true){ddeqXwAPPy = false;}
      if(BZlTTYGTsi == true){BZlTTYGTsi = false;}
      if(QkksGIBIqe == true){QkksGIBIqe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HALPNJZATS
{ 
  void OScYLezViK()
  { 
      bool zjXlpVtmkQ = false;
      bool MzQpTOOitI = false;
      bool lNwDzFPYHO = false;
      bool uMeqEYXlud = false;
      bool qFKOTSNQHI = false;
      bool QWIZGknTmj = false;
      bool GUeVVAUZlu = false;
      bool pbmQRfDhjg = false;
      bool qyRzyXDEjS = false;
      bool kDzLWVanrS = false;
      bool xneMRoirHZ = false;
      bool hGjGrHDeXx = false;
      bool wPoSJmbbsu = false;
      bool FOoQiDTEhI = false;
      bool nKwJkeTsTP = false;
      bool SuQuVgyLDe = false;
      bool NHzMUTQSWn = false;
      bool nzxOIlSehd = false;
      bool ShHdcJxttB = false;
      bool EIADugLjoR = false;
      string FOxdFhuXVV;
      string jfHQFLwGGD;
      string CaJcmbYRKN;
      string ZxhOszFrdB;
      string tQlninthLF;
      string RrmwLeFTqd;
      string IdMHumyrWF;
      string GEbFJkoUty;
      string gqGEuhJkCO;
      string skAArQDdsw;
      string pCKFyNPhma;
      string pkZrwRXHMN;
      string cNoILUDbMs;
      string gKayIegAGg;
      string SbxbYILHDa;
      string swRfSbMBsd;
      string KmUtseJbjR;
      string kWBetBPMjD;
      string JuYlAkruef;
      string ReHbWeGDhs;
      if(FOxdFhuXVV == pCKFyNPhma){zjXlpVtmkQ = true;}
      else if(pCKFyNPhma == FOxdFhuXVV){xneMRoirHZ = true;}
      if(jfHQFLwGGD == pkZrwRXHMN){MzQpTOOitI = true;}
      else if(pkZrwRXHMN == jfHQFLwGGD){hGjGrHDeXx = true;}
      if(CaJcmbYRKN == cNoILUDbMs){lNwDzFPYHO = true;}
      else if(cNoILUDbMs == CaJcmbYRKN){wPoSJmbbsu = true;}
      if(ZxhOszFrdB == gKayIegAGg){uMeqEYXlud = true;}
      else if(gKayIegAGg == ZxhOszFrdB){FOoQiDTEhI = true;}
      if(tQlninthLF == SbxbYILHDa){qFKOTSNQHI = true;}
      else if(SbxbYILHDa == tQlninthLF){nKwJkeTsTP = true;}
      if(RrmwLeFTqd == swRfSbMBsd){QWIZGknTmj = true;}
      else if(swRfSbMBsd == RrmwLeFTqd){SuQuVgyLDe = true;}
      if(IdMHumyrWF == KmUtseJbjR){GUeVVAUZlu = true;}
      else if(KmUtseJbjR == IdMHumyrWF){NHzMUTQSWn = true;}
      if(GEbFJkoUty == kWBetBPMjD){pbmQRfDhjg = true;}
      if(gqGEuhJkCO == JuYlAkruef){qyRzyXDEjS = true;}
      if(skAArQDdsw == ReHbWeGDhs){kDzLWVanrS = true;}
      while(kWBetBPMjD == GEbFJkoUty){nzxOIlSehd = true;}
      while(JuYlAkruef == JuYlAkruef){ShHdcJxttB = true;}
      while(ReHbWeGDhs == ReHbWeGDhs){EIADugLjoR = true;}
      if(zjXlpVtmkQ == true){zjXlpVtmkQ = false;}
      if(MzQpTOOitI == true){MzQpTOOitI = false;}
      if(lNwDzFPYHO == true){lNwDzFPYHO = false;}
      if(uMeqEYXlud == true){uMeqEYXlud = false;}
      if(qFKOTSNQHI == true){qFKOTSNQHI = false;}
      if(QWIZGknTmj == true){QWIZGknTmj = false;}
      if(GUeVVAUZlu == true){GUeVVAUZlu = false;}
      if(pbmQRfDhjg == true){pbmQRfDhjg = false;}
      if(qyRzyXDEjS == true){qyRzyXDEjS = false;}
      if(kDzLWVanrS == true){kDzLWVanrS = false;}
      if(xneMRoirHZ == true){xneMRoirHZ = false;}
      if(hGjGrHDeXx == true){hGjGrHDeXx = false;}
      if(wPoSJmbbsu == true){wPoSJmbbsu = false;}
      if(FOoQiDTEhI == true){FOoQiDTEhI = false;}
      if(nKwJkeTsTP == true){nKwJkeTsTP = false;}
      if(SuQuVgyLDe == true){SuQuVgyLDe = false;}
      if(NHzMUTQSWn == true){NHzMUTQSWn = false;}
      if(nzxOIlSehd == true){nzxOIlSehd = false;}
      if(ShHdcJxttB == true){ShHdcJxttB = false;}
      if(EIADugLjoR == true){EIADugLjoR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZJJVJKMSC
{ 
  void aHBMTXFIPO()
  { 
      bool oHpHYTZMqf = false;
      bool YALnqDjDMh = false;
      bool pyJFLXLaNg = false;
      bool qzPqHSuuiZ = false;
      bool NKdYVonTlJ = false;
      bool OchsUpyjwA = false;
      bool IzzKoYjTfY = false;
      bool HnUlTfTkjW = false;
      bool jrnDRNRWWQ = false;
      bool ULziRNKTiw = false;
      bool ETmNBaIuYo = false;
      bool WMzYPPKusa = false;
      bool HNxPDwnkTG = false;
      bool UABmRPEaBq = false;
      bool FWxhsHLZSB = false;
      bool COaIoqWXJF = false;
      bool lWaSTWLLHz = false;
      bool LjsBVkPPVw = false;
      bool kORRDFZsya = false;
      bool sgRwFhudNW = false;
      string iQReERrcIo;
      string kxrZsgliSU;
      string mhWTiMXzQP;
      string mNJUzQqCgd;
      string ppHpqDCRSF;
      string zBFTkAtyur;
      string srLrCXmXab;
      string oiBoexagbe;
      string KFgLQkIpjy;
      string WrHojxePnT;
      string QdqpPPzPnm;
      string ZNWPgmKAaQ;
      string PwmbFxbLEg;
      string RLsIOfOqwA;
      string lrBwYJVqIx;
      string mdnWDTqOjS;
      string nmLHVNTNBA;
      string YSEaeXtqCw;
      string akDHtnXVEu;
      string oAHdMygtaL;
      if(iQReERrcIo == QdqpPPzPnm){oHpHYTZMqf = true;}
      else if(QdqpPPzPnm == iQReERrcIo){ETmNBaIuYo = true;}
      if(kxrZsgliSU == ZNWPgmKAaQ){YALnqDjDMh = true;}
      else if(ZNWPgmKAaQ == kxrZsgliSU){WMzYPPKusa = true;}
      if(mhWTiMXzQP == PwmbFxbLEg){pyJFLXLaNg = true;}
      else if(PwmbFxbLEg == mhWTiMXzQP){HNxPDwnkTG = true;}
      if(mNJUzQqCgd == RLsIOfOqwA){qzPqHSuuiZ = true;}
      else if(RLsIOfOqwA == mNJUzQqCgd){UABmRPEaBq = true;}
      if(ppHpqDCRSF == lrBwYJVqIx){NKdYVonTlJ = true;}
      else if(lrBwYJVqIx == ppHpqDCRSF){FWxhsHLZSB = true;}
      if(zBFTkAtyur == mdnWDTqOjS){OchsUpyjwA = true;}
      else if(mdnWDTqOjS == zBFTkAtyur){COaIoqWXJF = true;}
      if(srLrCXmXab == nmLHVNTNBA){IzzKoYjTfY = true;}
      else if(nmLHVNTNBA == srLrCXmXab){lWaSTWLLHz = true;}
      if(oiBoexagbe == YSEaeXtqCw){HnUlTfTkjW = true;}
      if(KFgLQkIpjy == akDHtnXVEu){jrnDRNRWWQ = true;}
      if(WrHojxePnT == oAHdMygtaL){ULziRNKTiw = true;}
      while(YSEaeXtqCw == oiBoexagbe){LjsBVkPPVw = true;}
      while(akDHtnXVEu == akDHtnXVEu){kORRDFZsya = true;}
      while(oAHdMygtaL == oAHdMygtaL){sgRwFhudNW = true;}
      if(oHpHYTZMqf == true){oHpHYTZMqf = false;}
      if(YALnqDjDMh == true){YALnqDjDMh = false;}
      if(pyJFLXLaNg == true){pyJFLXLaNg = false;}
      if(qzPqHSuuiZ == true){qzPqHSuuiZ = false;}
      if(NKdYVonTlJ == true){NKdYVonTlJ = false;}
      if(OchsUpyjwA == true){OchsUpyjwA = false;}
      if(IzzKoYjTfY == true){IzzKoYjTfY = false;}
      if(HnUlTfTkjW == true){HnUlTfTkjW = false;}
      if(jrnDRNRWWQ == true){jrnDRNRWWQ = false;}
      if(ULziRNKTiw == true){ULziRNKTiw = false;}
      if(ETmNBaIuYo == true){ETmNBaIuYo = false;}
      if(WMzYPPKusa == true){WMzYPPKusa = false;}
      if(HNxPDwnkTG == true){HNxPDwnkTG = false;}
      if(UABmRPEaBq == true){UABmRPEaBq = false;}
      if(FWxhsHLZSB == true){FWxhsHLZSB = false;}
      if(COaIoqWXJF == true){COaIoqWXJF = false;}
      if(lWaSTWLLHz == true){lWaSTWLLHz = false;}
      if(LjsBVkPPVw == true){LjsBVkPPVw = false;}
      if(kORRDFZsya == true){kORRDFZsya = false;}
      if(sgRwFhudNW == true){sgRwFhudNW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJXNRNIFGU
{ 
  void lWEleVwdHp()
  { 
      bool MYtlyrWFHY = false;
      bool OmKzCxUtdO = false;
      bool PVcoXyZaPU = false;
      bool srFWXLcpVj = false;
      bool pACMiCsNyU = false;
      bool SDMOwqwENA = false;
      bool RwolfWgnaq = false;
      bool UdYsYPSQFV = false;
      bool EMbuCpepZf = false;
      bool OXcUStLQgM = false;
      bool UFlHAndSpg = false;
      bool XfyqwETtio = false;
      bool qqNubxBDad = false;
      bool DCisByaUtO = false;
      bool LLzsIiYkYN = false;
      bool ZQgqUcrqeD = false;
      bool laqMcUwFox = false;
      bool dzzUdfqUmr = false;
      bool XPeNEmVrYX = false;
      bool GjoqbjTmPm = false;
      string PmcVKHrLwk;
      string MxnmPRISrf;
      string KuxqGOszqN;
      string hKBGTmoiSR;
      string IirNVcrfoo;
      string AXLmOTokOu;
      string OsTiDCwgSb;
      string cZzZWaDjUd;
      string WMJCNJyNrA;
      string yDTXDOPJJT;
      string fKNNMZYlPm;
      string QFPkYBiQVs;
      string DhoScYFaWI;
      string LtZBxLzwom;
      string kMyFirnizB;
      string eynPPyVtjn;
      string UxOHbWeOnN;
      string CmbhIqiiik;
      string kWbUcMGJky;
      string oEMBSmxqdM;
      if(PmcVKHrLwk == fKNNMZYlPm){MYtlyrWFHY = true;}
      else if(fKNNMZYlPm == PmcVKHrLwk){UFlHAndSpg = true;}
      if(MxnmPRISrf == QFPkYBiQVs){OmKzCxUtdO = true;}
      else if(QFPkYBiQVs == MxnmPRISrf){XfyqwETtio = true;}
      if(KuxqGOszqN == DhoScYFaWI){PVcoXyZaPU = true;}
      else if(DhoScYFaWI == KuxqGOszqN){qqNubxBDad = true;}
      if(hKBGTmoiSR == LtZBxLzwom){srFWXLcpVj = true;}
      else if(LtZBxLzwom == hKBGTmoiSR){DCisByaUtO = true;}
      if(IirNVcrfoo == kMyFirnizB){pACMiCsNyU = true;}
      else if(kMyFirnizB == IirNVcrfoo){LLzsIiYkYN = true;}
      if(AXLmOTokOu == eynPPyVtjn){SDMOwqwENA = true;}
      else if(eynPPyVtjn == AXLmOTokOu){ZQgqUcrqeD = true;}
      if(OsTiDCwgSb == UxOHbWeOnN){RwolfWgnaq = true;}
      else if(UxOHbWeOnN == OsTiDCwgSb){laqMcUwFox = true;}
      if(cZzZWaDjUd == CmbhIqiiik){UdYsYPSQFV = true;}
      if(WMJCNJyNrA == kWbUcMGJky){EMbuCpepZf = true;}
      if(yDTXDOPJJT == oEMBSmxqdM){OXcUStLQgM = true;}
      while(CmbhIqiiik == cZzZWaDjUd){dzzUdfqUmr = true;}
      while(kWbUcMGJky == kWbUcMGJky){XPeNEmVrYX = true;}
      while(oEMBSmxqdM == oEMBSmxqdM){GjoqbjTmPm = true;}
      if(MYtlyrWFHY == true){MYtlyrWFHY = false;}
      if(OmKzCxUtdO == true){OmKzCxUtdO = false;}
      if(PVcoXyZaPU == true){PVcoXyZaPU = false;}
      if(srFWXLcpVj == true){srFWXLcpVj = false;}
      if(pACMiCsNyU == true){pACMiCsNyU = false;}
      if(SDMOwqwENA == true){SDMOwqwENA = false;}
      if(RwolfWgnaq == true){RwolfWgnaq = false;}
      if(UdYsYPSQFV == true){UdYsYPSQFV = false;}
      if(EMbuCpepZf == true){EMbuCpepZf = false;}
      if(OXcUStLQgM == true){OXcUStLQgM = false;}
      if(UFlHAndSpg == true){UFlHAndSpg = false;}
      if(XfyqwETtio == true){XfyqwETtio = false;}
      if(qqNubxBDad == true){qqNubxBDad = false;}
      if(DCisByaUtO == true){DCisByaUtO = false;}
      if(LLzsIiYkYN == true){LLzsIiYkYN = false;}
      if(ZQgqUcrqeD == true){ZQgqUcrqeD = false;}
      if(laqMcUwFox == true){laqMcUwFox = false;}
      if(dzzUdfqUmr == true){dzzUdfqUmr = false;}
      if(XPeNEmVrYX == true){XPeNEmVrYX = false;}
      if(GjoqbjTmPm == true){GjoqbjTmPm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZFXXIYYVJ
{ 
  void oQgLaqHIVR()
  { 
      bool AepSlFAhaw = false;
      bool kFCCpOIauN = false;
      bool mewefVhMZL = false;
      bool OfCcTxxpps = false;
      bool QPCePQwcRI = false;
      bool DeTSDViKlQ = false;
      bool XmIPgFCYhs = false;
      bool QRjBxWbQOO = false;
      bool ZEuQIiLiZy = false;
      bool NmDZVdHmxK = false;
      bool OWtXrktRVg = false;
      bool tRwWqSqqGy = false;
      bool sSziedNKfS = false;
      bool PnTEACKWYW = false;
      bool otNrEwpghD = false;
      bool lPfzRuXLsN = false;
      bool XjlCQFyqWn = false;
      bool IURjIzFGdh = false;
      bool mgbcgzHTmF = false;
      bool eycLzFHKay = false;
      string yOENUXsgKQ;
      string qzVfgNOMFr;
      string ezBEeIucQx;
      string oQZuqHQSwY;
      string weQZTKLHZs;
      string JOTGRyMzhL;
      string cQQMaaYZnY;
      string wuQfuAiajT;
      string xnCWnaxTdr;
      string uRkkweOEys;
      string lkSBxNxmKR;
      string PkOOOoNtXA;
      string cFwwdeKfjP;
      string lecqhLUBZa;
      string cJJMbJCWVG;
      string RUfyPgoWWR;
      string CRDtekIXfC;
      string TMTxWTujTU;
      string bnJcyRydaB;
      string WyeHXLFPgp;
      if(yOENUXsgKQ == lkSBxNxmKR){AepSlFAhaw = true;}
      else if(lkSBxNxmKR == yOENUXsgKQ){OWtXrktRVg = true;}
      if(qzVfgNOMFr == PkOOOoNtXA){kFCCpOIauN = true;}
      else if(PkOOOoNtXA == qzVfgNOMFr){tRwWqSqqGy = true;}
      if(ezBEeIucQx == cFwwdeKfjP){mewefVhMZL = true;}
      else if(cFwwdeKfjP == ezBEeIucQx){sSziedNKfS = true;}
      if(oQZuqHQSwY == lecqhLUBZa){OfCcTxxpps = true;}
      else if(lecqhLUBZa == oQZuqHQSwY){PnTEACKWYW = true;}
      if(weQZTKLHZs == cJJMbJCWVG){QPCePQwcRI = true;}
      else if(cJJMbJCWVG == weQZTKLHZs){otNrEwpghD = true;}
      if(JOTGRyMzhL == RUfyPgoWWR){DeTSDViKlQ = true;}
      else if(RUfyPgoWWR == JOTGRyMzhL){lPfzRuXLsN = true;}
      if(cQQMaaYZnY == CRDtekIXfC){XmIPgFCYhs = true;}
      else if(CRDtekIXfC == cQQMaaYZnY){XjlCQFyqWn = true;}
      if(wuQfuAiajT == TMTxWTujTU){QRjBxWbQOO = true;}
      if(xnCWnaxTdr == bnJcyRydaB){ZEuQIiLiZy = true;}
      if(uRkkweOEys == WyeHXLFPgp){NmDZVdHmxK = true;}
      while(TMTxWTujTU == wuQfuAiajT){IURjIzFGdh = true;}
      while(bnJcyRydaB == bnJcyRydaB){mgbcgzHTmF = true;}
      while(WyeHXLFPgp == WyeHXLFPgp){eycLzFHKay = true;}
      if(AepSlFAhaw == true){AepSlFAhaw = false;}
      if(kFCCpOIauN == true){kFCCpOIauN = false;}
      if(mewefVhMZL == true){mewefVhMZL = false;}
      if(OfCcTxxpps == true){OfCcTxxpps = false;}
      if(QPCePQwcRI == true){QPCePQwcRI = false;}
      if(DeTSDViKlQ == true){DeTSDViKlQ = false;}
      if(XmIPgFCYhs == true){XmIPgFCYhs = false;}
      if(QRjBxWbQOO == true){QRjBxWbQOO = false;}
      if(ZEuQIiLiZy == true){ZEuQIiLiZy = false;}
      if(NmDZVdHmxK == true){NmDZVdHmxK = false;}
      if(OWtXrktRVg == true){OWtXrktRVg = false;}
      if(tRwWqSqqGy == true){tRwWqSqqGy = false;}
      if(sSziedNKfS == true){sSziedNKfS = false;}
      if(PnTEACKWYW == true){PnTEACKWYW = false;}
      if(otNrEwpghD == true){otNrEwpghD = false;}
      if(lPfzRuXLsN == true){lPfzRuXLsN = false;}
      if(XjlCQFyqWn == true){XjlCQFyqWn = false;}
      if(IURjIzFGdh == true){IURjIzFGdh = false;}
      if(mgbcgzHTmF == true){mgbcgzHTmF = false;}
      if(eycLzFHKay == true){eycLzFHKay = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCJOSOXXMM
{ 
  void PLWhLLhRug()
  { 
      bool rnzQPFguji = false;
      bool dMonCQjUxx = false;
      bool dODQwfQynG = false;
      bool espOGIfCQO = false;
      bool KljDQibjgF = false;
      bool NcApsdjhUi = false;
      bool nhGcDjWZgt = false;
      bool kgEhmrdAAM = false;
      bool EfRhrBszUc = false;
      bool XyhgZceGzf = false;
      bool MBDlUgYRDB = false;
      bool AigHdIPYkB = false;
      bool qWEEVmyWIJ = false;
      bool NWAUADbfNK = false;
      bool cawTcnQaDQ = false;
      bool MGVxnowyPg = false;
      bool iBJsnchMGZ = false;
      bool fjKZXPZkbh = false;
      bool VXTqxHBDfK = false;
      bool GdPfbbRDfz = false;
      string tkNYecOywb;
      string BgwyHicXjm;
      string sdooKPsjZQ;
      string kijNuNpBEm;
      string aFLlFVfBIR;
      string NApplPuXOP;
      string idYepSxiCs;
      string rbSxLnSDjn;
      string jrbHDjrsaf;
      string SRloDxggul;
      string YxyOYkhsex;
      string xqnaeqCQbG;
      string aEHVaZpdsO;
      string HlIxOlsMhR;
      string CyNdiadKJM;
      string tPEnLUpbny;
      string uDAQpKipLr;
      string xohJEcpcmz;
      string weTfTrgTlt;
      string wQYiVyxxmX;
      if(tkNYecOywb == YxyOYkhsex){rnzQPFguji = true;}
      else if(YxyOYkhsex == tkNYecOywb){MBDlUgYRDB = true;}
      if(BgwyHicXjm == xqnaeqCQbG){dMonCQjUxx = true;}
      else if(xqnaeqCQbG == BgwyHicXjm){AigHdIPYkB = true;}
      if(sdooKPsjZQ == aEHVaZpdsO){dODQwfQynG = true;}
      else if(aEHVaZpdsO == sdooKPsjZQ){qWEEVmyWIJ = true;}
      if(kijNuNpBEm == HlIxOlsMhR){espOGIfCQO = true;}
      else if(HlIxOlsMhR == kijNuNpBEm){NWAUADbfNK = true;}
      if(aFLlFVfBIR == CyNdiadKJM){KljDQibjgF = true;}
      else if(CyNdiadKJM == aFLlFVfBIR){cawTcnQaDQ = true;}
      if(NApplPuXOP == tPEnLUpbny){NcApsdjhUi = true;}
      else if(tPEnLUpbny == NApplPuXOP){MGVxnowyPg = true;}
      if(idYepSxiCs == uDAQpKipLr){nhGcDjWZgt = true;}
      else if(uDAQpKipLr == idYepSxiCs){iBJsnchMGZ = true;}
      if(rbSxLnSDjn == xohJEcpcmz){kgEhmrdAAM = true;}
      if(jrbHDjrsaf == weTfTrgTlt){EfRhrBszUc = true;}
      if(SRloDxggul == wQYiVyxxmX){XyhgZceGzf = true;}
      while(xohJEcpcmz == rbSxLnSDjn){fjKZXPZkbh = true;}
      while(weTfTrgTlt == weTfTrgTlt){VXTqxHBDfK = true;}
      while(wQYiVyxxmX == wQYiVyxxmX){GdPfbbRDfz = true;}
      if(rnzQPFguji == true){rnzQPFguji = false;}
      if(dMonCQjUxx == true){dMonCQjUxx = false;}
      if(dODQwfQynG == true){dODQwfQynG = false;}
      if(espOGIfCQO == true){espOGIfCQO = false;}
      if(KljDQibjgF == true){KljDQibjgF = false;}
      if(NcApsdjhUi == true){NcApsdjhUi = false;}
      if(nhGcDjWZgt == true){nhGcDjWZgt = false;}
      if(kgEhmrdAAM == true){kgEhmrdAAM = false;}
      if(EfRhrBszUc == true){EfRhrBszUc = false;}
      if(XyhgZceGzf == true){XyhgZceGzf = false;}
      if(MBDlUgYRDB == true){MBDlUgYRDB = false;}
      if(AigHdIPYkB == true){AigHdIPYkB = false;}
      if(qWEEVmyWIJ == true){qWEEVmyWIJ = false;}
      if(NWAUADbfNK == true){NWAUADbfNK = false;}
      if(cawTcnQaDQ == true){cawTcnQaDQ = false;}
      if(MGVxnowyPg == true){MGVxnowyPg = false;}
      if(iBJsnchMGZ == true){iBJsnchMGZ = false;}
      if(fjKZXPZkbh == true){fjKZXPZkbh = false;}
      if(VXTqxHBDfK == true){VXTqxHBDfK = false;}
      if(GdPfbbRDfz == true){GdPfbbRDfz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSQPLSETCU
{ 
  void aYFfgVwYNH()
  { 
      bool wbjgnyrtHN = false;
      bool DohCPPusXE = false;
      bool MhwYoatTAQ = false;
      bool jfPKTzDrzh = false;
      bool ZZuDThHRKz = false;
      bool JPmOWNfLqM = false;
      bool EXspdWZWiQ = false;
      bool MCtpemlrEH = false;
      bool ScIBGUsAnF = false;
      bool SqBldBfFYx = false;
      bool IkhtlHUwji = false;
      bool amGjtaPriJ = false;
      bool cYhcxUBIMd = false;
      bool HgTHzhuNOz = false;
      bool zxQFefjRqC = false;
      bool kmVOTiCExR = false;
      bool FMiFbsTzkM = false;
      bool fBdiKfIcyR = false;
      bool kjQKrTKEnP = false;
      bool epQxsmNLck = false;
      string USBcsNYdzn;
      string LwwrYXmkCf;
      string FnsAumbSjZ;
      string cOYEGacaLY;
      string VwRklZqWOF;
      string jNBJkgZAhG;
      string lFsYKwWrky;
      string tMYcKIWHOU;
      string uEDdpONPSZ;
      string AbsFlPCsZp;
      string CylQKWnXzb;
      string KSlNKhCPiw;
      string iHZKxRTTqt;
      string FdgYRxRmTS;
      string ZpPpPhpftE;
      string NmJdGuYbSr;
      string DUgEWgkNuN;
      string QOuPWsqitP;
      string bmYmgRTDRW;
      string XoTaPFIKTi;
      if(USBcsNYdzn == CylQKWnXzb){wbjgnyrtHN = true;}
      else if(CylQKWnXzb == USBcsNYdzn){IkhtlHUwji = true;}
      if(LwwrYXmkCf == KSlNKhCPiw){DohCPPusXE = true;}
      else if(KSlNKhCPiw == LwwrYXmkCf){amGjtaPriJ = true;}
      if(FnsAumbSjZ == iHZKxRTTqt){MhwYoatTAQ = true;}
      else if(iHZKxRTTqt == FnsAumbSjZ){cYhcxUBIMd = true;}
      if(cOYEGacaLY == FdgYRxRmTS){jfPKTzDrzh = true;}
      else if(FdgYRxRmTS == cOYEGacaLY){HgTHzhuNOz = true;}
      if(VwRklZqWOF == ZpPpPhpftE){ZZuDThHRKz = true;}
      else if(ZpPpPhpftE == VwRklZqWOF){zxQFefjRqC = true;}
      if(jNBJkgZAhG == NmJdGuYbSr){JPmOWNfLqM = true;}
      else if(NmJdGuYbSr == jNBJkgZAhG){kmVOTiCExR = true;}
      if(lFsYKwWrky == DUgEWgkNuN){EXspdWZWiQ = true;}
      else if(DUgEWgkNuN == lFsYKwWrky){FMiFbsTzkM = true;}
      if(tMYcKIWHOU == QOuPWsqitP){MCtpemlrEH = true;}
      if(uEDdpONPSZ == bmYmgRTDRW){ScIBGUsAnF = true;}
      if(AbsFlPCsZp == XoTaPFIKTi){SqBldBfFYx = true;}
      while(QOuPWsqitP == tMYcKIWHOU){fBdiKfIcyR = true;}
      while(bmYmgRTDRW == bmYmgRTDRW){kjQKrTKEnP = true;}
      while(XoTaPFIKTi == XoTaPFIKTi){epQxsmNLck = true;}
      if(wbjgnyrtHN == true){wbjgnyrtHN = false;}
      if(DohCPPusXE == true){DohCPPusXE = false;}
      if(MhwYoatTAQ == true){MhwYoatTAQ = false;}
      if(jfPKTzDrzh == true){jfPKTzDrzh = false;}
      if(ZZuDThHRKz == true){ZZuDThHRKz = false;}
      if(JPmOWNfLqM == true){JPmOWNfLqM = false;}
      if(EXspdWZWiQ == true){EXspdWZWiQ = false;}
      if(MCtpemlrEH == true){MCtpemlrEH = false;}
      if(ScIBGUsAnF == true){ScIBGUsAnF = false;}
      if(SqBldBfFYx == true){SqBldBfFYx = false;}
      if(IkhtlHUwji == true){IkhtlHUwji = false;}
      if(amGjtaPriJ == true){amGjtaPriJ = false;}
      if(cYhcxUBIMd == true){cYhcxUBIMd = false;}
      if(HgTHzhuNOz == true){HgTHzhuNOz = false;}
      if(zxQFefjRqC == true){zxQFefjRqC = false;}
      if(kmVOTiCExR == true){kmVOTiCExR = false;}
      if(FMiFbsTzkM == true){FMiFbsTzkM = false;}
      if(fBdiKfIcyR == true){fBdiKfIcyR = false;}
      if(kjQKrTKEnP == true){kjQKrTKEnP = false;}
      if(epQxsmNLck == true){epQxsmNLck = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFWXVCKUXG
{ 
  void GmdzQdXTzN()
  { 
      bool QOZGImCLom = false;
      bool fADRJgXgKC = false;
      bool HrmumTjNzT = false;
      bool ccGwFtOfrL = false;
      bool WiZlBkLTNy = false;
      bool eIcldXadSn = false;
      bool CoLVKDsGLO = false;
      bool RqnzfYSBsC = false;
      bool HPzAnTzURh = false;
      bool SjNEIgWEby = false;
      bool qFHygmTdFF = false;
      bool EZkPfloLgp = false;
      bool DYodugdjpz = false;
      bool BOYuLCHBTA = false;
      bool zVOLdszyXV = false;
      bool qLWkuRQdCz = false;
      bool JjnGDoAoEc = false;
      bool emqgqgKczC = false;
      bool hfLTHprmAs = false;
      bool ldzUpPgHHn = false;
      string eFawNQxKbC;
      string hlkcKkSnse;
      string CfzJsQUqtf;
      string YsCSbLiPiX;
      string NcUaiyZKhD;
      string QgwjNyFQDx;
      string uGQwcniRBz;
      string BDEVQYKXZu;
      string pKIqOqxSFc;
      string FRLlcHMYxu;
      string OIJhBNcZTn;
      string nhqIGjxZgl;
      string pQMXtiqRrJ;
      string MlaefgBaoB;
      string OXyQoXaCer;
      string JmqLFywlnR;
      string VKhKbCHMcY;
      string iWjeWSRuiV;
      string InlAzYtOYh;
      string kPlWfDonol;
      if(eFawNQxKbC == OIJhBNcZTn){QOZGImCLom = true;}
      else if(OIJhBNcZTn == eFawNQxKbC){qFHygmTdFF = true;}
      if(hlkcKkSnse == nhqIGjxZgl){fADRJgXgKC = true;}
      else if(nhqIGjxZgl == hlkcKkSnse){EZkPfloLgp = true;}
      if(CfzJsQUqtf == pQMXtiqRrJ){HrmumTjNzT = true;}
      else if(pQMXtiqRrJ == CfzJsQUqtf){DYodugdjpz = true;}
      if(YsCSbLiPiX == MlaefgBaoB){ccGwFtOfrL = true;}
      else if(MlaefgBaoB == YsCSbLiPiX){BOYuLCHBTA = true;}
      if(NcUaiyZKhD == OXyQoXaCer){WiZlBkLTNy = true;}
      else if(OXyQoXaCer == NcUaiyZKhD){zVOLdszyXV = true;}
      if(QgwjNyFQDx == JmqLFywlnR){eIcldXadSn = true;}
      else if(JmqLFywlnR == QgwjNyFQDx){qLWkuRQdCz = true;}
      if(uGQwcniRBz == VKhKbCHMcY){CoLVKDsGLO = true;}
      else if(VKhKbCHMcY == uGQwcniRBz){JjnGDoAoEc = true;}
      if(BDEVQYKXZu == iWjeWSRuiV){RqnzfYSBsC = true;}
      if(pKIqOqxSFc == InlAzYtOYh){HPzAnTzURh = true;}
      if(FRLlcHMYxu == kPlWfDonol){SjNEIgWEby = true;}
      while(iWjeWSRuiV == BDEVQYKXZu){emqgqgKczC = true;}
      while(InlAzYtOYh == InlAzYtOYh){hfLTHprmAs = true;}
      while(kPlWfDonol == kPlWfDonol){ldzUpPgHHn = true;}
      if(QOZGImCLom == true){QOZGImCLom = false;}
      if(fADRJgXgKC == true){fADRJgXgKC = false;}
      if(HrmumTjNzT == true){HrmumTjNzT = false;}
      if(ccGwFtOfrL == true){ccGwFtOfrL = false;}
      if(WiZlBkLTNy == true){WiZlBkLTNy = false;}
      if(eIcldXadSn == true){eIcldXadSn = false;}
      if(CoLVKDsGLO == true){CoLVKDsGLO = false;}
      if(RqnzfYSBsC == true){RqnzfYSBsC = false;}
      if(HPzAnTzURh == true){HPzAnTzURh = false;}
      if(SjNEIgWEby == true){SjNEIgWEby = false;}
      if(qFHygmTdFF == true){qFHygmTdFF = false;}
      if(EZkPfloLgp == true){EZkPfloLgp = false;}
      if(DYodugdjpz == true){DYodugdjpz = false;}
      if(BOYuLCHBTA == true){BOYuLCHBTA = false;}
      if(zVOLdszyXV == true){zVOLdszyXV = false;}
      if(qLWkuRQdCz == true){qLWkuRQdCz = false;}
      if(JjnGDoAoEc == true){JjnGDoAoEc = false;}
      if(emqgqgKczC == true){emqgqgKczC = false;}
      if(hfLTHprmAs == true){hfLTHprmAs = false;}
      if(ldzUpPgHHn == true){ldzUpPgHHn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYFFKFBLAY
{ 
  void cwLNqIyAsk()
  { 
      bool SCcdpMDkjl = false;
      bool NWdXRZiSVx = false;
      bool wJoPaWxVsR = false;
      bool tLGRtNOcaA = false;
      bool ShLYsNVBSL = false;
      bool kTXKOIMNCT = false;
      bool PhrSqCPLdD = false;
      bool KFqUeNyQVN = false;
      bool AuChfamwDk = false;
      bool ABaHkjpshq = false;
      bool yKWPAfbDeA = false;
      bool KwqoTTfJlP = false;
      bool OSIsDJeiju = false;
      bool XEhdOpXmgA = false;
      bool yiQDZDJlnQ = false;
      bool EfHRbeBdMq = false;
      bool BsTjcFNNZd = false;
      bool usckQfCFSz = false;
      bool zruSqqxQCj = false;
      bool ntZpzFPfZT = false;
      string zbpDXKOGCE;
      string NGLjEINWNE;
      string oUKMbsLuPJ;
      string GXLrERJYCq;
      string lYoTLyuqLy;
      string xHlzPeRdbe;
      string zSprxouSem;
      string yoTWRPfpAd;
      string xTjRLzlLbZ;
      string AfxWrTiwWW;
      string CbLXzImPhA;
      string zadxgeiYgy;
      string DipEmRqxey;
      string giTdaVHLRC;
      string LWdbaZCzoM;
      string jKPXSSkHkg;
      string RpjiTPGAWL;
      string WWGdmgFOcN;
      string PqHRNVTwKH;
      string jAZkkUltHK;
      if(zbpDXKOGCE == CbLXzImPhA){SCcdpMDkjl = true;}
      else if(CbLXzImPhA == zbpDXKOGCE){yKWPAfbDeA = true;}
      if(NGLjEINWNE == zadxgeiYgy){NWdXRZiSVx = true;}
      else if(zadxgeiYgy == NGLjEINWNE){KwqoTTfJlP = true;}
      if(oUKMbsLuPJ == DipEmRqxey){wJoPaWxVsR = true;}
      else if(DipEmRqxey == oUKMbsLuPJ){OSIsDJeiju = true;}
      if(GXLrERJYCq == giTdaVHLRC){tLGRtNOcaA = true;}
      else if(giTdaVHLRC == GXLrERJYCq){XEhdOpXmgA = true;}
      if(lYoTLyuqLy == LWdbaZCzoM){ShLYsNVBSL = true;}
      else if(LWdbaZCzoM == lYoTLyuqLy){yiQDZDJlnQ = true;}
      if(xHlzPeRdbe == jKPXSSkHkg){kTXKOIMNCT = true;}
      else if(jKPXSSkHkg == xHlzPeRdbe){EfHRbeBdMq = true;}
      if(zSprxouSem == RpjiTPGAWL){PhrSqCPLdD = true;}
      else if(RpjiTPGAWL == zSprxouSem){BsTjcFNNZd = true;}
      if(yoTWRPfpAd == WWGdmgFOcN){KFqUeNyQVN = true;}
      if(xTjRLzlLbZ == PqHRNVTwKH){AuChfamwDk = true;}
      if(AfxWrTiwWW == jAZkkUltHK){ABaHkjpshq = true;}
      while(WWGdmgFOcN == yoTWRPfpAd){usckQfCFSz = true;}
      while(PqHRNVTwKH == PqHRNVTwKH){zruSqqxQCj = true;}
      while(jAZkkUltHK == jAZkkUltHK){ntZpzFPfZT = true;}
      if(SCcdpMDkjl == true){SCcdpMDkjl = false;}
      if(NWdXRZiSVx == true){NWdXRZiSVx = false;}
      if(wJoPaWxVsR == true){wJoPaWxVsR = false;}
      if(tLGRtNOcaA == true){tLGRtNOcaA = false;}
      if(ShLYsNVBSL == true){ShLYsNVBSL = false;}
      if(kTXKOIMNCT == true){kTXKOIMNCT = false;}
      if(PhrSqCPLdD == true){PhrSqCPLdD = false;}
      if(KFqUeNyQVN == true){KFqUeNyQVN = false;}
      if(AuChfamwDk == true){AuChfamwDk = false;}
      if(ABaHkjpshq == true){ABaHkjpshq = false;}
      if(yKWPAfbDeA == true){yKWPAfbDeA = false;}
      if(KwqoTTfJlP == true){KwqoTTfJlP = false;}
      if(OSIsDJeiju == true){OSIsDJeiju = false;}
      if(XEhdOpXmgA == true){XEhdOpXmgA = false;}
      if(yiQDZDJlnQ == true){yiQDZDJlnQ = false;}
      if(EfHRbeBdMq == true){EfHRbeBdMq = false;}
      if(BsTjcFNNZd == true){BsTjcFNNZd = false;}
      if(usckQfCFSz == true){usckQfCFSz = false;}
      if(zruSqqxQCj == true){zruSqqxQCj = false;}
      if(ntZpzFPfZT == true){ntZpzFPfZT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDZLMFCVYP
{ 
  void eVOLIWESNk()
  { 
      bool CQEIOXZndx = false;
      bool WZMWrddcGF = false;
      bool LTheLYHGDS = false;
      bool wbaYzbJNgd = false;
      bool LnnBdOAmgo = false;
      bool ViFOOhiYwo = false;
      bool QTkLBuznXQ = false;
      bool UQwbsWefBw = false;
      bool YTYNwMWLJQ = false;
      bool rjQqNqDcAi = false;
      bool PLPQTFmcUq = false;
      bool DCXzQwtWOn = false;
      bool XmdHXkzENC = false;
      bool TBfSgMEItq = false;
      bool ZsqSNpLQaQ = false;
      bool wgOLKbgIsi = false;
      bool FhOSXBVFSD = false;
      bool rlcWOewLtg = false;
      bool ZidwFlmUIF = false;
      bool euPLlqdXuL = false;
      string YVylArtIyF;
      string ggJLCxONbd;
      string GMpHTGhsiN;
      string IfFMEVYqOV;
      string sUdLBrWhty;
      string MdakTLfqRt;
      string KAZjwAaxHf;
      string XWzGklhdFb;
      string izyjBdFTrr;
      string phZTKrttOB;
      string QZaOZoeTAh;
      string cBkpKKCoiR;
      string tGEOpoxeur;
      string qnPEKJYjJL;
      string zkTKPnxjJA;
      string pFLwGJULYk;
      string rzYIqolfeB;
      string lSeWSImtzB;
      string rNVuBkcSyA;
      string oMKYTzMLTa;
      if(YVylArtIyF == QZaOZoeTAh){CQEIOXZndx = true;}
      else if(QZaOZoeTAh == YVylArtIyF){PLPQTFmcUq = true;}
      if(ggJLCxONbd == cBkpKKCoiR){WZMWrddcGF = true;}
      else if(cBkpKKCoiR == ggJLCxONbd){DCXzQwtWOn = true;}
      if(GMpHTGhsiN == tGEOpoxeur){LTheLYHGDS = true;}
      else if(tGEOpoxeur == GMpHTGhsiN){XmdHXkzENC = true;}
      if(IfFMEVYqOV == qnPEKJYjJL){wbaYzbJNgd = true;}
      else if(qnPEKJYjJL == IfFMEVYqOV){TBfSgMEItq = true;}
      if(sUdLBrWhty == zkTKPnxjJA){LnnBdOAmgo = true;}
      else if(zkTKPnxjJA == sUdLBrWhty){ZsqSNpLQaQ = true;}
      if(MdakTLfqRt == pFLwGJULYk){ViFOOhiYwo = true;}
      else if(pFLwGJULYk == MdakTLfqRt){wgOLKbgIsi = true;}
      if(KAZjwAaxHf == rzYIqolfeB){QTkLBuznXQ = true;}
      else if(rzYIqolfeB == KAZjwAaxHf){FhOSXBVFSD = true;}
      if(XWzGklhdFb == lSeWSImtzB){UQwbsWefBw = true;}
      if(izyjBdFTrr == rNVuBkcSyA){YTYNwMWLJQ = true;}
      if(phZTKrttOB == oMKYTzMLTa){rjQqNqDcAi = true;}
      while(lSeWSImtzB == XWzGklhdFb){rlcWOewLtg = true;}
      while(rNVuBkcSyA == rNVuBkcSyA){ZidwFlmUIF = true;}
      while(oMKYTzMLTa == oMKYTzMLTa){euPLlqdXuL = true;}
      if(CQEIOXZndx == true){CQEIOXZndx = false;}
      if(WZMWrddcGF == true){WZMWrddcGF = false;}
      if(LTheLYHGDS == true){LTheLYHGDS = false;}
      if(wbaYzbJNgd == true){wbaYzbJNgd = false;}
      if(LnnBdOAmgo == true){LnnBdOAmgo = false;}
      if(ViFOOhiYwo == true){ViFOOhiYwo = false;}
      if(QTkLBuznXQ == true){QTkLBuznXQ = false;}
      if(UQwbsWefBw == true){UQwbsWefBw = false;}
      if(YTYNwMWLJQ == true){YTYNwMWLJQ = false;}
      if(rjQqNqDcAi == true){rjQqNqDcAi = false;}
      if(PLPQTFmcUq == true){PLPQTFmcUq = false;}
      if(DCXzQwtWOn == true){DCXzQwtWOn = false;}
      if(XmdHXkzENC == true){XmdHXkzENC = false;}
      if(TBfSgMEItq == true){TBfSgMEItq = false;}
      if(ZsqSNpLQaQ == true){ZsqSNpLQaQ = false;}
      if(wgOLKbgIsi == true){wgOLKbgIsi = false;}
      if(FhOSXBVFSD == true){FhOSXBVFSD = false;}
      if(rlcWOewLtg == true){rlcWOewLtg = false;}
      if(ZidwFlmUIF == true){ZidwFlmUIF = false;}
      if(euPLlqdXuL == true){euPLlqdXuL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWAFTWZLGO
{ 
  void NGNEIcmDKZ()
  { 
      bool kHYiHohDYE = false;
      bool aKtYeCLmmm = false;
      bool gNqRNmGZGS = false;
      bool HtYBTSiRtO = false;
      bool HzcZAuHYfY = false;
      bool VjjUaXPHUU = false;
      bool iIxGwfksEM = false;
      bool StsXfgjRQR = false;
      bool egshwXKEZw = false;
      bool CbxYfyCVcU = false;
      bool KOUTFbqLnt = false;
      bool mypCoCPPJY = false;
      bool UfTIJqwTrg = false;
      bool dOnwHQLYbU = false;
      bool gzPeJElujc = false;
      bool imMEzduMJN = false;
      bool eWSHQXJstY = false;
      bool ppmoqVPnyF = false;
      bool FBiPxqBixd = false;
      bool UzONpJfHNk = false;
      string QMWIYnkZKJ;
      string IBYIeBrTgn;
      string cuXzCAjsyR;
      string CVQlnfjktt;
      string QxzbMJtZhY;
      string rpYMQVnWFX;
      string EqbsGljlTy;
      string QGZmWeuwms;
      string FKLYYLwDVS;
      string rNfVpYVGUZ;
      string YHFjIlQkol;
      string ZqjMStfCUu;
      string pgQBFDaDxx;
      string JobNTxFbQl;
      string tKOjrAcSDw;
      string sTlZirqDdE;
      string KMnqcjPVsU;
      string nEkhAeRgJE;
      string ZIABEoDCda;
      string GByLahWWHH;
      if(QMWIYnkZKJ == YHFjIlQkol){kHYiHohDYE = true;}
      else if(YHFjIlQkol == QMWIYnkZKJ){KOUTFbqLnt = true;}
      if(IBYIeBrTgn == ZqjMStfCUu){aKtYeCLmmm = true;}
      else if(ZqjMStfCUu == IBYIeBrTgn){mypCoCPPJY = true;}
      if(cuXzCAjsyR == pgQBFDaDxx){gNqRNmGZGS = true;}
      else if(pgQBFDaDxx == cuXzCAjsyR){UfTIJqwTrg = true;}
      if(CVQlnfjktt == JobNTxFbQl){HtYBTSiRtO = true;}
      else if(JobNTxFbQl == CVQlnfjktt){dOnwHQLYbU = true;}
      if(QxzbMJtZhY == tKOjrAcSDw){HzcZAuHYfY = true;}
      else if(tKOjrAcSDw == QxzbMJtZhY){gzPeJElujc = true;}
      if(rpYMQVnWFX == sTlZirqDdE){VjjUaXPHUU = true;}
      else if(sTlZirqDdE == rpYMQVnWFX){imMEzduMJN = true;}
      if(EqbsGljlTy == KMnqcjPVsU){iIxGwfksEM = true;}
      else if(KMnqcjPVsU == EqbsGljlTy){eWSHQXJstY = true;}
      if(QGZmWeuwms == nEkhAeRgJE){StsXfgjRQR = true;}
      if(FKLYYLwDVS == ZIABEoDCda){egshwXKEZw = true;}
      if(rNfVpYVGUZ == GByLahWWHH){CbxYfyCVcU = true;}
      while(nEkhAeRgJE == QGZmWeuwms){ppmoqVPnyF = true;}
      while(ZIABEoDCda == ZIABEoDCda){FBiPxqBixd = true;}
      while(GByLahWWHH == GByLahWWHH){UzONpJfHNk = true;}
      if(kHYiHohDYE == true){kHYiHohDYE = false;}
      if(aKtYeCLmmm == true){aKtYeCLmmm = false;}
      if(gNqRNmGZGS == true){gNqRNmGZGS = false;}
      if(HtYBTSiRtO == true){HtYBTSiRtO = false;}
      if(HzcZAuHYfY == true){HzcZAuHYfY = false;}
      if(VjjUaXPHUU == true){VjjUaXPHUU = false;}
      if(iIxGwfksEM == true){iIxGwfksEM = false;}
      if(StsXfgjRQR == true){StsXfgjRQR = false;}
      if(egshwXKEZw == true){egshwXKEZw = false;}
      if(CbxYfyCVcU == true){CbxYfyCVcU = false;}
      if(KOUTFbqLnt == true){KOUTFbqLnt = false;}
      if(mypCoCPPJY == true){mypCoCPPJY = false;}
      if(UfTIJqwTrg == true){UfTIJqwTrg = false;}
      if(dOnwHQLYbU == true){dOnwHQLYbU = false;}
      if(gzPeJElujc == true){gzPeJElujc = false;}
      if(imMEzduMJN == true){imMEzduMJN = false;}
      if(eWSHQXJstY == true){eWSHQXJstY = false;}
      if(ppmoqVPnyF == true){ppmoqVPnyF = false;}
      if(FBiPxqBixd == true){FBiPxqBixd = false;}
      if(UzONpJfHNk == true){UzONpJfHNk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TETZGWNAXG
{ 
  void uMZHpDsuib()
  { 
      bool bJnifWehML = false;
      bool niJanpuTaC = false;
      bool mofTDkIOLo = false;
      bool yjnYMabuWa = false;
      bool xuQbfeUCcm = false;
      bool QiPfdmdTft = false;
      bool NPWXNEtjNM = false;
      bool NAxAEqXEnX = false;
      bool QFkXXPTItZ = false;
      bool xIPbMgYsOb = false;
      bool kjoQZQlPam = false;
      bool PZfHdIeyzy = false;
      bool jlpmPFjUmW = false;
      bool SdpLmfPUyG = false;
      bool cEhHKXbHxE = false;
      bool CZtPrztCAT = false;
      bool fQcDUkjTTy = false;
      bool rKAsUfDhbr = false;
      bool ccWhUrjZTn = false;
      bool kNTdZMadmZ = false;
      string kTHFOyxftt;
      string fKhxnPMIbE;
      string HPTzoQBacg;
      string QIWTWCERmm;
      string JkNcLwFyjy;
      string uZLZnVzHQy;
      string wVCNcXnOZk;
      string KtUotVCpnr;
      string LCqelpwweB;
      string CwBopmizzn;
      string HpYymAFWfR;
      string TITYmteXal;
      string arjYiNsfzG;
      string mCpAjUdsqk;
      string kZQMhtccBw;
      string IKXNMPGzPY;
      string HYWYeQRSnR;
      string PlfpBBbWpo;
      string kQdDxbdcmT;
      string OdcRdMCqhR;
      if(kTHFOyxftt == HpYymAFWfR){bJnifWehML = true;}
      else if(HpYymAFWfR == kTHFOyxftt){kjoQZQlPam = true;}
      if(fKhxnPMIbE == TITYmteXal){niJanpuTaC = true;}
      else if(TITYmteXal == fKhxnPMIbE){PZfHdIeyzy = true;}
      if(HPTzoQBacg == arjYiNsfzG){mofTDkIOLo = true;}
      else if(arjYiNsfzG == HPTzoQBacg){jlpmPFjUmW = true;}
      if(QIWTWCERmm == mCpAjUdsqk){yjnYMabuWa = true;}
      else if(mCpAjUdsqk == QIWTWCERmm){SdpLmfPUyG = true;}
      if(JkNcLwFyjy == kZQMhtccBw){xuQbfeUCcm = true;}
      else if(kZQMhtccBw == JkNcLwFyjy){cEhHKXbHxE = true;}
      if(uZLZnVzHQy == IKXNMPGzPY){QiPfdmdTft = true;}
      else if(IKXNMPGzPY == uZLZnVzHQy){CZtPrztCAT = true;}
      if(wVCNcXnOZk == HYWYeQRSnR){NPWXNEtjNM = true;}
      else if(HYWYeQRSnR == wVCNcXnOZk){fQcDUkjTTy = true;}
      if(KtUotVCpnr == PlfpBBbWpo){NAxAEqXEnX = true;}
      if(LCqelpwweB == kQdDxbdcmT){QFkXXPTItZ = true;}
      if(CwBopmizzn == OdcRdMCqhR){xIPbMgYsOb = true;}
      while(PlfpBBbWpo == KtUotVCpnr){rKAsUfDhbr = true;}
      while(kQdDxbdcmT == kQdDxbdcmT){ccWhUrjZTn = true;}
      while(OdcRdMCqhR == OdcRdMCqhR){kNTdZMadmZ = true;}
      if(bJnifWehML == true){bJnifWehML = false;}
      if(niJanpuTaC == true){niJanpuTaC = false;}
      if(mofTDkIOLo == true){mofTDkIOLo = false;}
      if(yjnYMabuWa == true){yjnYMabuWa = false;}
      if(xuQbfeUCcm == true){xuQbfeUCcm = false;}
      if(QiPfdmdTft == true){QiPfdmdTft = false;}
      if(NPWXNEtjNM == true){NPWXNEtjNM = false;}
      if(NAxAEqXEnX == true){NAxAEqXEnX = false;}
      if(QFkXXPTItZ == true){QFkXXPTItZ = false;}
      if(xIPbMgYsOb == true){xIPbMgYsOb = false;}
      if(kjoQZQlPam == true){kjoQZQlPam = false;}
      if(PZfHdIeyzy == true){PZfHdIeyzy = false;}
      if(jlpmPFjUmW == true){jlpmPFjUmW = false;}
      if(SdpLmfPUyG == true){SdpLmfPUyG = false;}
      if(cEhHKXbHxE == true){cEhHKXbHxE = false;}
      if(CZtPrztCAT == true){CZtPrztCAT = false;}
      if(fQcDUkjTTy == true){fQcDUkjTTy = false;}
      if(rKAsUfDhbr == true){rKAsUfDhbr = false;}
      if(ccWhUrjZTn == true){ccWhUrjZTn = false;}
      if(kNTdZMadmZ == true){kNTdZMadmZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HUJSMXCJAC
{ 
  void RRBcEHzQsK()
  { 
      bool zLmRkTqnCi = false;
      bool bigDahdzmS = false;
      bool IqYwAUAeaP = false;
      bool lUtLGTtZkW = false;
      bool xbVDgMIjQl = false;
      bool WiIwkImqQQ = false;
      bool SLNmwGnVwG = false;
      bool nENQVfUVOm = false;
      bool MPOnrDMyZy = false;
      bool gDIUDkOiGZ = false;
      bool YmmKySUrZF = false;
      bool mQbcEDxZus = false;
      bool touyYkusNj = false;
      bool RlPoOYbEoY = false;
      bool hUXUKQbfQz = false;
      bool monMeiqokN = false;
      bool WbdpmBBlNe = false;
      bool asjVLZRZmH = false;
      bool IPbNwbxCJe = false;
      bool hmSaCFphgJ = false;
      string aFmwAfWexT;
      string BCgtfZRIEx;
      string wluRFzIHAp;
      string ghOVfiuqCE;
      string HMVtxVjXdo;
      string PhnPqnJVqB;
      string WPeGlSnKOw;
      string dZGAoiPATi;
      string OkdKZysyeq;
      string ZZABgrhPHd;
      string hYJgLpanZI;
      string YJBHllkUfn;
      string ZofXWEZFSx;
      string BArpBoaxyj;
      string WEYVSQXrOu;
      string HMjTErslJH;
      string PVVcHYQLFx;
      string KnVuQUQJEG;
      string fgqWpnQYlI;
      string womqUBhuOs;
      if(aFmwAfWexT == hYJgLpanZI){zLmRkTqnCi = true;}
      else if(hYJgLpanZI == aFmwAfWexT){YmmKySUrZF = true;}
      if(BCgtfZRIEx == YJBHllkUfn){bigDahdzmS = true;}
      else if(YJBHllkUfn == BCgtfZRIEx){mQbcEDxZus = true;}
      if(wluRFzIHAp == ZofXWEZFSx){IqYwAUAeaP = true;}
      else if(ZofXWEZFSx == wluRFzIHAp){touyYkusNj = true;}
      if(ghOVfiuqCE == BArpBoaxyj){lUtLGTtZkW = true;}
      else if(BArpBoaxyj == ghOVfiuqCE){RlPoOYbEoY = true;}
      if(HMVtxVjXdo == WEYVSQXrOu){xbVDgMIjQl = true;}
      else if(WEYVSQXrOu == HMVtxVjXdo){hUXUKQbfQz = true;}
      if(PhnPqnJVqB == HMjTErslJH){WiIwkImqQQ = true;}
      else if(HMjTErslJH == PhnPqnJVqB){monMeiqokN = true;}
      if(WPeGlSnKOw == PVVcHYQLFx){SLNmwGnVwG = true;}
      else if(PVVcHYQLFx == WPeGlSnKOw){WbdpmBBlNe = true;}
      if(dZGAoiPATi == KnVuQUQJEG){nENQVfUVOm = true;}
      if(OkdKZysyeq == fgqWpnQYlI){MPOnrDMyZy = true;}
      if(ZZABgrhPHd == womqUBhuOs){gDIUDkOiGZ = true;}
      while(KnVuQUQJEG == dZGAoiPATi){asjVLZRZmH = true;}
      while(fgqWpnQYlI == fgqWpnQYlI){IPbNwbxCJe = true;}
      while(womqUBhuOs == womqUBhuOs){hmSaCFphgJ = true;}
      if(zLmRkTqnCi == true){zLmRkTqnCi = false;}
      if(bigDahdzmS == true){bigDahdzmS = false;}
      if(IqYwAUAeaP == true){IqYwAUAeaP = false;}
      if(lUtLGTtZkW == true){lUtLGTtZkW = false;}
      if(xbVDgMIjQl == true){xbVDgMIjQl = false;}
      if(WiIwkImqQQ == true){WiIwkImqQQ = false;}
      if(SLNmwGnVwG == true){SLNmwGnVwG = false;}
      if(nENQVfUVOm == true){nENQVfUVOm = false;}
      if(MPOnrDMyZy == true){MPOnrDMyZy = false;}
      if(gDIUDkOiGZ == true){gDIUDkOiGZ = false;}
      if(YmmKySUrZF == true){YmmKySUrZF = false;}
      if(mQbcEDxZus == true){mQbcEDxZus = false;}
      if(touyYkusNj == true){touyYkusNj = false;}
      if(RlPoOYbEoY == true){RlPoOYbEoY = false;}
      if(hUXUKQbfQz == true){hUXUKQbfQz = false;}
      if(monMeiqokN == true){monMeiqokN = false;}
      if(WbdpmBBlNe == true){WbdpmBBlNe = false;}
      if(asjVLZRZmH == true){asjVLZRZmH = false;}
      if(IPbNwbxCJe == true){IPbNwbxCJe = false;}
      if(hmSaCFphgJ == true){hmSaCFphgJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MLLCEZBSIR
{ 
  void LPxHTNwZNp()
  { 
      bool UcwkNPNNfW = false;
      bool SyXjNPncYw = false;
      bool JcTTLorYjK = false;
      bool MdxREOBggC = false;
      bool jpeUyFIuxq = false;
      bool dCbXyrJbZX = false;
      bool WndVJnBGez = false;
      bool NGwWLTyzVG = false;
      bool fwarfKCYTM = false;
      bool FZHIeuLJLK = false;
      bool DBQydXGFLd = false;
      bool tJGTqaMkpz = false;
      bool lcmSsnzmqP = false;
      bool HnnKCefcOH = false;
      bool DwNoSuSnQE = false;
      bool iaTLXaOxFo = false;
      bool YSNuWFVuQM = false;
      bool ujWhuoPyAy = false;
      bool VKWmggUbma = false;
      bool QhWYikiRRN = false;
      string MdSRtNRjyi;
      string TGcSCgoqOx;
      string FRrgbtsXdW;
      string gSqsjCsZkC;
      string rHrNNmeYqZ;
      string IgNBntllpz;
      string TsGaCBOjiz;
      string nPFMExZdSn;
      string PTgDOAEpEo;
      string QHikizBRKL;
      string XuprlsaBwp;
      string UHSBjzMCMC;
      string wYesiffTdF;
      string wITGQTdnRU;
      string YDsNTInhBi;
      string myEIPyPxJF;
      string NGXqtMnLkP;
      string VXkqcsfQYZ;
      string rxStRxDKqR;
      string EgeLHSfBTH;
      if(MdSRtNRjyi == XuprlsaBwp){UcwkNPNNfW = true;}
      else if(XuprlsaBwp == MdSRtNRjyi){DBQydXGFLd = true;}
      if(TGcSCgoqOx == UHSBjzMCMC){SyXjNPncYw = true;}
      else if(UHSBjzMCMC == TGcSCgoqOx){tJGTqaMkpz = true;}
      if(FRrgbtsXdW == wYesiffTdF){JcTTLorYjK = true;}
      else if(wYesiffTdF == FRrgbtsXdW){lcmSsnzmqP = true;}
      if(gSqsjCsZkC == wITGQTdnRU){MdxREOBggC = true;}
      else if(wITGQTdnRU == gSqsjCsZkC){HnnKCefcOH = true;}
      if(rHrNNmeYqZ == YDsNTInhBi){jpeUyFIuxq = true;}
      else if(YDsNTInhBi == rHrNNmeYqZ){DwNoSuSnQE = true;}
      if(IgNBntllpz == myEIPyPxJF){dCbXyrJbZX = true;}
      else if(myEIPyPxJF == IgNBntllpz){iaTLXaOxFo = true;}
      if(TsGaCBOjiz == NGXqtMnLkP){WndVJnBGez = true;}
      else if(NGXqtMnLkP == TsGaCBOjiz){YSNuWFVuQM = true;}
      if(nPFMExZdSn == VXkqcsfQYZ){NGwWLTyzVG = true;}
      if(PTgDOAEpEo == rxStRxDKqR){fwarfKCYTM = true;}
      if(QHikizBRKL == EgeLHSfBTH){FZHIeuLJLK = true;}
      while(VXkqcsfQYZ == nPFMExZdSn){ujWhuoPyAy = true;}
      while(rxStRxDKqR == rxStRxDKqR){VKWmggUbma = true;}
      while(EgeLHSfBTH == EgeLHSfBTH){QhWYikiRRN = true;}
      if(UcwkNPNNfW == true){UcwkNPNNfW = false;}
      if(SyXjNPncYw == true){SyXjNPncYw = false;}
      if(JcTTLorYjK == true){JcTTLorYjK = false;}
      if(MdxREOBggC == true){MdxREOBggC = false;}
      if(jpeUyFIuxq == true){jpeUyFIuxq = false;}
      if(dCbXyrJbZX == true){dCbXyrJbZX = false;}
      if(WndVJnBGez == true){WndVJnBGez = false;}
      if(NGwWLTyzVG == true){NGwWLTyzVG = false;}
      if(fwarfKCYTM == true){fwarfKCYTM = false;}
      if(FZHIeuLJLK == true){FZHIeuLJLK = false;}
      if(DBQydXGFLd == true){DBQydXGFLd = false;}
      if(tJGTqaMkpz == true){tJGTqaMkpz = false;}
      if(lcmSsnzmqP == true){lcmSsnzmqP = false;}
      if(HnnKCefcOH == true){HnnKCefcOH = false;}
      if(DwNoSuSnQE == true){DwNoSuSnQE = false;}
      if(iaTLXaOxFo == true){iaTLXaOxFo = false;}
      if(YSNuWFVuQM == true){YSNuWFVuQM = false;}
      if(ujWhuoPyAy == true){ujWhuoPyAy = false;}
      if(VKWmggUbma == true){VKWmggUbma = false;}
      if(QhWYikiRRN == true){QhWYikiRRN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFVHLHWHYB
{ 
  void QJUrCAWGQj()
  { 
      bool oIhwwTpoZQ = false;
      bool lMgIpyKfDw = false;
      bool fmUTnaHrkT = false;
      bool BAkrztFOmS = false;
      bool VQpcLxhKJP = false;
      bool pVIhZBnOIU = false;
      bool MxEGOlbnJw = false;
      bool swrjZOwqHp = false;
      bool sxhUdfqCSx = false;
      bool GpFSGYMjNY = false;
      bool UsBNWscXIK = false;
      bool FwGRaPOibi = false;
      bool tYVLoCpYdA = false;
      bool CMdhVzuUyj = false;
      bool CTtHrJjmqq = false;
      bool JdHdeuXoXU = false;
      bool DEtHIrRXwb = false;
      bool TtjrgadNTf = false;
      bool RDgmpXEADZ = false;
      bool bGwdgyYmzz = false;
      string AqfysQwzSE;
      string IQIFLprVcq;
      string nmcHVpJMzx;
      string NlXOmWUpif;
      string WVGdIJYpSm;
      string ZOitWNOYbD;
      string GjzUqVssRo;
      string UBmwUSfzyM;
      string RTsMXzCcqZ;
      string IwOfZlWlml;
      string PeXdRXblZE;
      string gPZOkmqmxq;
      string SQCrgYmGWh;
      string utLMxmuPtz;
      string WQDmsrVzum;
      string uinuSzbfws;
      string kVPqImDNRy;
      string qasyUCMOyn;
      string CmKimMGQsy;
      string KPSANABMdG;
      if(AqfysQwzSE == PeXdRXblZE){oIhwwTpoZQ = true;}
      else if(PeXdRXblZE == AqfysQwzSE){UsBNWscXIK = true;}
      if(IQIFLprVcq == gPZOkmqmxq){lMgIpyKfDw = true;}
      else if(gPZOkmqmxq == IQIFLprVcq){FwGRaPOibi = true;}
      if(nmcHVpJMzx == SQCrgYmGWh){fmUTnaHrkT = true;}
      else if(SQCrgYmGWh == nmcHVpJMzx){tYVLoCpYdA = true;}
      if(NlXOmWUpif == utLMxmuPtz){BAkrztFOmS = true;}
      else if(utLMxmuPtz == NlXOmWUpif){CMdhVzuUyj = true;}
      if(WVGdIJYpSm == WQDmsrVzum){VQpcLxhKJP = true;}
      else if(WQDmsrVzum == WVGdIJYpSm){CTtHrJjmqq = true;}
      if(ZOitWNOYbD == uinuSzbfws){pVIhZBnOIU = true;}
      else if(uinuSzbfws == ZOitWNOYbD){JdHdeuXoXU = true;}
      if(GjzUqVssRo == kVPqImDNRy){MxEGOlbnJw = true;}
      else if(kVPqImDNRy == GjzUqVssRo){DEtHIrRXwb = true;}
      if(UBmwUSfzyM == qasyUCMOyn){swrjZOwqHp = true;}
      if(RTsMXzCcqZ == CmKimMGQsy){sxhUdfqCSx = true;}
      if(IwOfZlWlml == KPSANABMdG){GpFSGYMjNY = true;}
      while(qasyUCMOyn == UBmwUSfzyM){TtjrgadNTf = true;}
      while(CmKimMGQsy == CmKimMGQsy){RDgmpXEADZ = true;}
      while(KPSANABMdG == KPSANABMdG){bGwdgyYmzz = true;}
      if(oIhwwTpoZQ == true){oIhwwTpoZQ = false;}
      if(lMgIpyKfDw == true){lMgIpyKfDw = false;}
      if(fmUTnaHrkT == true){fmUTnaHrkT = false;}
      if(BAkrztFOmS == true){BAkrztFOmS = false;}
      if(VQpcLxhKJP == true){VQpcLxhKJP = false;}
      if(pVIhZBnOIU == true){pVIhZBnOIU = false;}
      if(MxEGOlbnJw == true){MxEGOlbnJw = false;}
      if(swrjZOwqHp == true){swrjZOwqHp = false;}
      if(sxhUdfqCSx == true){sxhUdfqCSx = false;}
      if(GpFSGYMjNY == true){GpFSGYMjNY = false;}
      if(UsBNWscXIK == true){UsBNWscXIK = false;}
      if(FwGRaPOibi == true){FwGRaPOibi = false;}
      if(tYVLoCpYdA == true){tYVLoCpYdA = false;}
      if(CMdhVzuUyj == true){CMdhVzuUyj = false;}
      if(CTtHrJjmqq == true){CTtHrJjmqq = false;}
      if(JdHdeuXoXU == true){JdHdeuXoXU = false;}
      if(DEtHIrRXwb == true){DEtHIrRXwb = false;}
      if(TtjrgadNTf == true){TtjrgadNTf = false;}
      if(RDgmpXEADZ == true){RDgmpXEADZ = false;}
      if(bGwdgyYmzz == true){bGwdgyYmzz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGBEXMNTRD
{ 
  void gArCMxtRZy()
  { 
      bool MxSUPPkUzR = false;
      bool JQHUgsEepw = false;
      bool jWlpDFjyoN = false;
      bool PAxXdOjMdt = false;
      bool HiiQGXKCiL = false;
      bool SFEFspKbQK = false;
      bool elfkCJSjpR = false;
      bool JqBuoBnVjf = false;
      bool uhOduKurdn = false;
      bool DHwTPUDxOw = false;
      bool EaLRBaDIPr = false;
      bool BoqjOwWBor = false;
      bool NZFCOCugeT = false;
      bool xpHnaTWxbU = false;
      bool GlbklNPMET = false;
      bool xBHVheUICz = false;
      bool fWdwtLhDJt = false;
      bool YYZUlaxUQA = false;
      bool libLVwhkGw = false;
      bool zOtcoiIfpa = false;
      string zsgOgXPmuM;
      string RUgDPQSPHz;
      string uMTfYbVXfZ;
      string ZqDTLPrpNn;
      string FegTCKSTUx;
      string AiaawmYBoF;
      string BrGUlaRMqz;
      string XcCTsPeAdN;
      string JCCiYpQbWY;
      string pqAIlMXLgb;
      string sFbUYXgGhg;
      string HYXauyoXwu;
      string JooSIfbtgg;
      string rTTBUDahJB;
      string JJtpRRTYMm;
      string WzPkREPILs;
      string wlYAnnFVGr;
      string XHOtkztzBq;
      string MChtKrDhiP;
      string nRWPFXjtBd;
      if(zsgOgXPmuM == sFbUYXgGhg){MxSUPPkUzR = true;}
      else if(sFbUYXgGhg == zsgOgXPmuM){EaLRBaDIPr = true;}
      if(RUgDPQSPHz == HYXauyoXwu){JQHUgsEepw = true;}
      else if(HYXauyoXwu == RUgDPQSPHz){BoqjOwWBor = true;}
      if(uMTfYbVXfZ == JooSIfbtgg){jWlpDFjyoN = true;}
      else if(JooSIfbtgg == uMTfYbVXfZ){NZFCOCugeT = true;}
      if(ZqDTLPrpNn == rTTBUDahJB){PAxXdOjMdt = true;}
      else if(rTTBUDahJB == ZqDTLPrpNn){xpHnaTWxbU = true;}
      if(FegTCKSTUx == JJtpRRTYMm){HiiQGXKCiL = true;}
      else if(JJtpRRTYMm == FegTCKSTUx){GlbklNPMET = true;}
      if(AiaawmYBoF == WzPkREPILs){SFEFspKbQK = true;}
      else if(WzPkREPILs == AiaawmYBoF){xBHVheUICz = true;}
      if(BrGUlaRMqz == wlYAnnFVGr){elfkCJSjpR = true;}
      else if(wlYAnnFVGr == BrGUlaRMqz){fWdwtLhDJt = true;}
      if(XcCTsPeAdN == XHOtkztzBq){JqBuoBnVjf = true;}
      if(JCCiYpQbWY == MChtKrDhiP){uhOduKurdn = true;}
      if(pqAIlMXLgb == nRWPFXjtBd){DHwTPUDxOw = true;}
      while(XHOtkztzBq == XcCTsPeAdN){YYZUlaxUQA = true;}
      while(MChtKrDhiP == MChtKrDhiP){libLVwhkGw = true;}
      while(nRWPFXjtBd == nRWPFXjtBd){zOtcoiIfpa = true;}
      if(MxSUPPkUzR == true){MxSUPPkUzR = false;}
      if(JQHUgsEepw == true){JQHUgsEepw = false;}
      if(jWlpDFjyoN == true){jWlpDFjyoN = false;}
      if(PAxXdOjMdt == true){PAxXdOjMdt = false;}
      if(HiiQGXKCiL == true){HiiQGXKCiL = false;}
      if(SFEFspKbQK == true){SFEFspKbQK = false;}
      if(elfkCJSjpR == true){elfkCJSjpR = false;}
      if(JqBuoBnVjf == true){JqBuoBnVjf = false;}
      if(uhOduKurdn == true){uhOduKurdn = false;}
      if(DHwTPUDxOw == true){DHwTPUDxOw = false;}
      if(EaLRBaDIPr == true){EaLRBaDIPr = false;}
      if(BoqjOwWBor == true){BoqjOwWBor = false;}
      if(NZFCOCugeT == true){NZFCOCugeT = false;}
      if(xpHnaTWxbU == true){xpHnaTWxbU = false;}
      if(GlbklNPMET == true){GlbklNPMET = false;}
      if(xBHVheUICz == true){xBHVheUICz = false;}
      if(fWdwtLhDJt == true){fWdwtLhDJt = false;}
      if(YYZUlaxUQA == true){YYZUlaxUQA = false;}
      if(libLVwhkGw == true){libLVwhkGw = false;}
      if(zOtcoiIfpa == true){zOtcoiIfpa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGLRHOTAKW
{ 
  void kYgmPQBxgF()
  { 
      bool fyHhuyWzPq = false;
      bool dyWyNCxdXk = false;
      bool lqnPwAxcYa = false;
      bool yMZbtQVRyH = false;
      bool rATJlmfwpk = false;
      bool oJXaWnJqku = false;
      bool BtZorRXuEx = false;
      bool gefPskWddJ = false;
      bool TAmnkonzFF = false;
      bool GdgDGyaeQT = false;
      bool PkrsDJdIgk = false;
      bool ReMbbAHlDD = false;
      bool cXpzpCybIu = false;
      bool KqNJthIsjb = false;
      bool LfSTmaQEbG = false;
      bool pobMqqusCB = false;
      bool KBzlaaRDhs = false;
      bool qNBarxFVLP = false;
      bool ktABEUPASC = false;
      bool mPqiQJgfrM = false;
      string HomllAiWAA;
      string oKRhwpQRzf;
      string WANMeZcBzB;
      string BJZjDVfdgn;
      string hnsZGGSWen;
      string jAdYCGbZHL;
      string WgXzyejgea;
      string JmkLxiGnGY;
      string HFWKQAfBgw;
      string tGVUQAPtab;
      string VkrEexPSaT;
      string zmTiERKMhy;
      string yiAifCQQtw;
      string SMMdCVNSfT;
      string kMZNwGmmPz;
      string pDMccmkJXb;
      string fyYdAmaofh;
      string ErfNNlImlZ;
      string OcAtGOAjAP;
      string kDtDnlnwMJ;
      if(HomllAiWAA == VkrEexPSaT){fyHhuyWzPq = true;}
      else if(VkrEexPSaT == HomllAiWAA){PkrsDJdIgk = true;}
      if(oKRhwpQRzf == zmTiERKMhy){dyWyNCxdXk = true;}
      else if(zmTiERKMhy == oKRhwpQRzf){ReMbbAHlDD = true;}
      if(WANMeZcBzB == yiAifCQQtw){lqnPwAxcYa = true;}
      else if(yiAifCQQtw == WANMeZcBzB){cXpzpCybIu = true;}
      if(BJZjDVfdgn == SMMdCVNSfT){yMZbtQVRyH = true;}
      else if(SMMdCVNSfT == BJZjDVfdgn){KqNJthIsjb = true;}
      if(hnsZGGSWen == kMZNwGmmPz){rATJlmfwpk = true;}
      else if(kMZNwGmmPz == hnsZGGSWen){LfSTmaQEbG = true;}
      if(jAdYCGbZHL == pDMccmkJXb){oJXaWnJqku = true;}
      else if(pDMccmkJXb == jAdYCGbZHL){pobMqqusCB = true;}
      if(WgXzyejgea == fyYdAmaofh){BtZorRXuEx = true;}
      else if(fyYdAmaofh == WgXzyejgea){KBzlaaRDhs = true;}
      if(JmkLxiGnGY == ErfNNlImlZ){gefPskWddJ = true;}
      if(HFWKQAfBgw == OcAtGOAjAP){TAmnkonzFF = true;}
      if(tGVUQAPtab == kDtDnlnwMJ){GdgDGyaeQT = true;}
      while(ErfNNlImlZ == JmkLxiGnGY){qNBarxFVLP = true;}
      while(OcAtGOAjAP == OcAtGOAjAP){ktABEUPASC = true;}
      while(kDtDnlnwMJ == kDtDnlnwMJ){mPqiQJgfrM = true;}
      if(fyHhuyWzPq == true){fyHhuyWzPq = false;}
      if(dyWyNCxdXk == true){dyWyNCxdXk = false;}
      if(lqnPwAxcYa == true){lqnPwAxcYa = false;}
      if(yMZbtQVRyH == true){yMZbtQVRyH = false;}
      if(rATJlmfwpk == true){rATJlmfwpk = false;}
      if(oJXaWnJqku == true){oJXaWnJqku = false;}
      if(BtZorRXuEx == true){BtZorRXuEx = false;}
      if(gefPskWddJ == true){gefPskWddJ = false;}
      if(TAmnkonzFF == true){TAmnkonzFF = false;}
      if(GdgDGyaeQT == true){GdgDGyaeQT = false;}
      if(PkrsDJdIgk == true){PkrsDJdIgk = false;}
      if(ReMbbAHlDD == true){ReMbbAHlDD = false;}
      if(cXpzpCybIu == true){cXpzpCybIu = false;}
      if(KqNJthIsjb == true){KqNJthIsjb = false;}
      if(LfSTmaQEbG == true){LfSTmaQEbG = false;}
      if(pobMqqusCB == true){pobMqqusCB = false;}
      if(KBzlaaRDhs == true){KBzlaaRDhs = false;}
      if(qNBarxFVLP == true){qNBarxFVLP = false;}
      if(ktABEUPASC == true){ktABEUPASC = false;}
      if(mPqiQJgfrM == true){mPqiQJgfrM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KTVQZGBBHO
{ 
  void mMXFquTFcA()
  { 
      bool gRHezCMGXA = false;
      bool ZmiHVsnqtA = false;
      bool BwoMZUJzcs = false;
      bool DXAZqseSXb = false;
      bool lZyalfSlDw = false;
      bool bZWLgkctFe = false;
      bool rMcewCmJPb = false;
      bool NUTRNaxNas = false;
      bool CXwgQcAnrG = false;
      bool QjNrjYxTdj = false;
      bool sIVahHFFyF = false;
      bool mOTLbTQwNT = false;
      bool ByQILcGagn = false;
      bool cdjpAsCUyJ = false;
      bool WuplTBPCQP = false;
      bool IBGKiuqMPE = false;
      bool AeXJcIedKi = false;
      bool RwxDwFHdoK = false;
      bool NEKRfbXYHF = false;
      bool BoEsJrXgJK = false;
      string qiaKuXqITB;
      string SHrmrZtFoK;
      string UkNnrmziyN;
      string ebcYKtixuJ;
      string qXSPQXrqDR;
      string tTmdeGVlSI;
      string XHKGWqeSby;
      string qwKeTwSxXT;
      string tHegSLnztE;
      string YxdmliNMsY;
      string sZOFaxJHJh;
      string nXOyNPcdmL;
      string CeYXYtRWsk;
      string iFEyaUsYFU;
      string CgpLQAhfYV;
      string FjYhWOAqfg;
      string elOYzhTQXs;
      string WDXSJVoNHY;
      string LlyWeygWbL;
      string TBsYoPRQMh;
      if(qiaKuXqITB == sZOFaxJHJh){gRHezCMGXA = true;}
      else if(sZOFaxJHJh == qiaKuXqITB){sIVahHFFyF = true;}
      if(SHrmrZtFoK == nXOyNPcdmL){ZmiHVsnqtA = true;}
      else if(nXOyNPcdmL == SHrmrZtFoK){mOTLbTQwNT = true;}
      if(UkNnrmziyN == CeYXYtRWsk){BwoMZUJzcs = true;}
      else if(CeYXYtRWsk == UkNnrmziyN){ByQILcGagn = true;}
      if(ebcYKtixuJ == iFEyaUsYFU){DXAZqseSXb = true;}
      else if(iFEyaUsYFU == ebcYKtixuJ){cdjpAsCUyJ = true;}
      if(qXSPQXrqDR == CgpLQAhfYV){lZyalfSlDw = true;}
      else if(CgpLQAhfYV == qXSPQXrqDR){WuplTBPCQP = true;}
      if(tTmdeGVlSI == FjYhWOAqfg){bZWLgkctFe = true;}
      else if(FjYhWOAqfg == tTmdeGVlSI){IBGKiuqMPE = true;}
      if(XHKGWqeSby == elOYzhTQXs){rMcewCmJPb = true;}
      else if(elOYzhTQXs == XHKGWqeSby){AeXJcIedKi = true;}
      if(qwKeTwSxXT == WDXSJVoNHY){NUTRNaxNas = true;}
      if(tHegSLnztE == LlyWeygWbL){CXwgQcAnrG = true;}
      if(YxdmliNMsY == TBsYoPRQMh){QjNrjYxTdj = true;}
      while(WDXSJVoNHY == qwKeTwSxXT){RwxDwFHdoK = true;}
      while(LlyWeygWbL == LlyWeygWbL){NEKRfbXYHF = true;}
      while(TBsYoPRQMh == TBsYoPRQMh){BoEsJrXgJK = true;}
      if(gRHezCMGXA == true){gRHezCMGXA = false;}
      if(ZmiHVsnqtA == true){ZmiHVsnqtA = false;}
      if(BwoMZUJzcs == true){BwoMZUJzcs = false;}
      if(DXAZqseSXb == true){DXAZqseSXb = false;}
      if(lZyalfSlDw == true){lZyalfSlDw = false;}
      if(bZWLgkctFe == true){bZWLgkctFe = false;}
      if(rMcewCmJPb == true){rMcewCmJPb = false;}
      if(NUTRNaxNas == true){NUTRNaxNas = false;}
      if(CXwgQcAnrG == true){CXwgQcAnrG = false;}
      if(QjNrjYxTdj == true){QjNrjYxTdj = false;}
      if(sIVahHFFyF == true){sIVahHFFyF = false;}
      if(mOTLbTQwNT == true){mOTLbTQwNT = false;}
      if(ByQILcGagn == true){ByQILcGagn = false;}
      if(cdjpAsCUyJ == true){cdjpAsCUyJ = false;}
      if(WuplTBPCQP == true){WuplTBPCQP = false;}
      if(IBGKiuqMPE == true){IBGKiuqMPE = false;}
      if(AeXJcIedKi == true){AeXJcIedKi = false;}
      if(RwxDwFHdoK == true){RwxDwFHdoK = false;}
      if(NEKRfbXYHF == true){NEKRfbXYHF = false;}
      if(BoEsJrXgJK == true){BoEsJrXgJK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVHRCXQIAT
{ 
  void IMcOOazmFR()
  { 
      bool WoqXJCOZFz = false;
      bool rDPLfkMpsf = false;
      bool TOlrVrZECz = false;
      bool KDUHUJbmee = false;
      bool wWRQocVbnx = false;
      bool BjDpaHDyCQ = false;
      bool cJXFnniIqV = false;
      bool IYLOiwwVDr = false;
      bool WxPFxZAdfM = false;
      bool GdkNClzMbA = false;
      bool tNkSncYnGd = false;
      bool LgtJtetRHN = false;
      bool mEbdOdnxMw = false;
      bool wjsCyJMxQU = false;
      bool ALXCBZiaTW = false;
      bool rgEONplGDK = false;
      bool nbbJgamrLj = false;
      bool RxBmMagYco = false;
      bool uMcoEPeeoH = false;
      bool WGsGgYjNUZ = false;
      string oJgScRYaKy;
      string MFzAFIDDYe;
      string MXYDcZGdfM;
      string BKkuCVWEJd;
      string OFfPblAalI;
      string mEAouRkcoD;
      string KuuxxBUDxj;
      string kzstQHqIap;
      string YerWZxKwAk;
      string jsPGSSKiSa;
      string QxcBWnKFXn;
      string ZbCzefDXWz;
      string pYDMzqimax;
      string xIpAZaBpzl;
      string lEXMLIqQbm;
      string PlLSjrtQCf;
      string EXdapQlBYD;
      string dNXkNkApBq;
      string zSLngKxWPg;
      string gkmThNawVt;
      if(oJgScRYaKy == QxcBWnKFXn){WoqXJCOZFz = true;}
      else if(QxcBWnKFXn == oJgScRYaKy){tNkSncYnGd = true;}
      if(MFzAFIDDYe == ZbCzefDXWz){rDPLfkMpsf = true;}
      else if(ZbCzefDXWz == MFzAFIDDYe){LgtJtetRHN = true;}
      if(MXYDcZGdfM == pYDMzqimax){TOlrVrZECz = true;}
      else if(pYDMzqimax == MXYDcZGdfM){mEbdOdnxMw = true;}
      if(BKkuCVWEJd == xIpAZaBpzl){KDUHUJbmee = true;}
      else if(xIpAZaBpzl == BKkuCVWEJd){wjsCyJMxQU = true;}
      if(OFfPblAalI == lEXMLIqQbm){wWRQocVbnx = true;}
      else if(lEXMLIqQbm == OFfPblAalI){ALXCBZiaTW = true;}
      if(mEAouRkcoD == PlLSjrtQCf){BjDpaHDyCQ = true;}
      else if(PlLSjrtQCf == mEAouRkcoD){rgEONplGDK = true;}
      if(KuuxxBUDxj == EXdapQlBYD){cJXFnniIqV = true;}
      else if(EXdapQlBYD == KuuxxBUDxj){nbbJgamrLj = true;}
      if(kzstQHqIap == dNXkNkApBq){IYLOiwwVDr = true;}
      if(YerWZxKwAk == zSLngKxWPg){WxPFxZAdfM = true;}
      if(jsPGSSKiSa == gkmThNawVt){GdkNClzMbA = true;}
      while(dNXkNkApBq == kzstQHqIap){RxBmMagYco = true;}
      while(zSLngKxWPg == zSLngKxWPg){uMcoEPeeoH = true;}
      while(gkmThNawVt == gkmThNawVt){WGsGgYjNUZ = true;}
      if(WoqXJCOZFz == true){WoqXJCOZFz = false;}
      if(rDPLfkMpsf == true){rDPLfkMpsf = false;}
      if(TOlrVrZECz == true){TOlrVrZECz = false;}
      if(KDUHUJbmee == true){KDUHUJbmee = false;}
      if(wWRQocVbnx == true){wWRQocVbnx = false;}
      if(BjDpaHDyCQ == true){BjDpaHDyCQ = false;}
      if(cJXFnniIqV == true){cJXFnniIqV = false;}
      if(IYLOiwwVDr == true){IYLOiwwVDr = false;}
      if(WxPFxZAdfM == true){WxPFxZAdfM = false;}
      if(GdkNClzMbA == true){GdkNClzMbA = false;}
      if(tNkSncYnGd == true){tNkSncYnGd = false;}
      if(LgtJtetRHN == true){LgtJtetRHN = false;}
      if(mEbdOdnxMw == true){mEbdOdnxMw = false;}
      if(wjsCyJMxQU == true){wjsCyJMxQU = false;}
      if(ALXCBZiaTW == true){ALXCBZiaTW = false;}
      if(rgEONplGDK == true){rgEONplGDK = false;}
      if(nbbJgamrLj == true){nbbJgamrLj = false;}
      if(RxBmMagYco == true){RxBmMagYco = false;}
      if(uMcoEPeeoH == true){uMcoEPeeoH = false;}
      if(WGsGgYjNUZ == true){WGsGgYjNUZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YBLAOLPVWX
{ 
  void qJUkyBVTuu()
  { 
      bool GslEsrbZFj = false;
      bool AbMhJFsRYM = false;
      bool hxdGDVfwkz = false;
      bool kleVyMFyTk = false;
      bool HgSBLUAlUK = false;
      bool MdfhhJOfBX = false;
      bool MfoGzNxpjw = false;
      bool ztxmEAdbuh = false;
      bool UsaalGGxnn = false;
      bool xZxwYbrLCx = false;
      bool WJCXKRfrch = false;
      bool emkSCSEOUr = false;
      bool HACuyZxBOc = false;
      bool HSYyKLqDPT = false;
      bool aNTFJKodsF = false;
      bool XdqKoWGHYj = false;
      bool UddAZMNmHq = false;
      bool bAyARtfwln = false;
      bool kSIJFdaOIn = false;
      bool EjdfzwjSfw = false;
      string nHpYcYEmGl;
      string ixIzOINSsJ;
      string cqtyJSVRse;
      string UgWTbwSoKc;
      string mRRmYQFPnT;
      string UMlstxMqOK;
      string ClsaRCaoXR;
      string oXHQVKYGYs;
      string NFdYKHucZe;
      string jaaAZAXpVW;
      string oQrVdwEUWi;
      string XGRVwwIUPJ;
      string GxPrhOxHpU;
      string mhkCDxNHtO;
      string DZGpGcIEDc;
      string rCaLQqAzmP;
      string yxeBwoVPRz;
      string iAaAFfqYlF;
      string FrDNcjHYlL;
      string wNUdPGuEtQ;
      if(nHpYcYEmGl == oQrVdwEUWi){GslEsrbZFj = true;}
      else if(oQrVdwEUWi == nHpYcYEmGl){WJCXKRfrch = true;}
      if(ixIzOINSsJ == XGRVwwIUPJ){AbMhJFsRYM = true;}
      else if(XGRVwwIUPJ == ixIzOINSsJ){emkSCSEOUr = true;}
      if(cqtyJSVRse == GxPrhOxHpU){hxdGDVfwkz = true;}
      else if(GxPrhOxHpU == cqtyJSVRse){HACuyZxBOc = true;}
      if(UgWTbwSoKc == mhkCDxNHtO){kleVyMFyTk = true;}
      else if(mhkCDxNHtO == UgWTbwSoKc){HSYyKLqDPT = true;}
      if(mRRmYQFPnT == DZGpGcIEDc){HgSBLUAlUK = true;}
      else if(DZGpGcIEDc == mRRmYQFPnT){aNTFJKodsF = true;}
      if(UMlstxMqOK == rCaLQqAzmP){MdfhhJOfBX = true;}
      else if(rCaLQqAzmP == UMlstxMqOK){XdqKoWGHYj = true;}
      if(ClsaRCaoXR == yxeBwoVPRz){MfoGzNxpjw = true;}
      else if(yxeBwoVPRz == ClsaRCaoXR){UddAZMNmHq = true;}
      if(oXHQVKYGYs == iAaAFfqYlF){ztxmEAdbuh = true;}
      if(NFdYKHucZe == FrDNcjHYlL){UsaalGGxnn = true;}
      if(jaaAZAXpVW == wNUdPGuEtQ){xZxwYbrLCx = true;}
      while(iAaAFfqYlF == oXHQVKYGYs){bAyARtfwln = true;}
      while(FrDNcjHYlL == FrDNcjHYlL){kSIJFdaOIn = true;}
      while(wNUdPGuEtQ == wNUdPGuEtQ){EjdfzwjSfw = true;}
      if(GslEsrbZFj == true){GslEsrbZFj = false;}
      if(AbMhJFsRYM == true){AbMhJFsRYM = false;}
      if(hxdGDVfwkz == true){hxdGDVfwkz = false;}
      if(kleVyMFyTk == true){kleVyMFyTk = false;}
      if(HgSBLUAlUK == true){HgSBLUAlUK = false;}
      if(MdfhhJOfBX == true){MdfhhJOfBX = false;}
      if(MfoGzNxpjw == true){MfoGzNxpjw = false;}
      if(ztxmEAdbuh == true){ztxmEAdbuh = false;}
      if(UsaalGGxnn == true){UsaalGGxnn = false;}
      if(xZxwYbrLCx == true){xZxwYbrLCx = false;}
      if(WJCXKRfrch == true){WJCXKRfrch = false;}
      if(emkSCSEOUr == true){emkSCSEOUr = false;}
      if(HACuyZxBOc == true){HACuyZxBOc = false;}
      if(HSYyKLqDPT == true){HSYyKLqDPT = false;}
      if(aNTFJKodsF == true){aNTFJKodsF = false;}
      if(XdqKoWGHYj == true){XdqKoWGHYj = false;}
      if(UddAZMNmHq == true){UddAZMNmHq = false;}
      if(bAyARtfwln == true){bAyARtfwln = false;}
      if(kSIJFdaOIn == true){kSIJFdaOIn = false;}
      if(EjdfzwjSfw == true){EjdfzwjSfw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKPQKSZAAK
{ 
  void aPJmZRmlaj()
  { 
      bool XCeaCwpYWd = false;
      bool EHGqgXVmhT = false;
      bool GHyKokBflI = false;
      bool kGwFHjkgOA = false;
      bool tLOgiGKIel = false;
      bool uISCnPEUkQ = false;
      bool tJmOsxLAjx = false;
      bool mnYgYurRbi = false;
      bool arAzMcnsRr = false;
      bool ePwxFjYAnk = false;
      bool uJYhyHilcs = false;
      bool WmsCpBJmCP = false;
      bool JRirSXrban = false;
      bool WrcpmQTSAF = false;
      bool sCPYUqWtGD = false;
      bool akxXbcZfOa = false;
      bool PHKnVdJCOZ = false;
      bool hplxWHBKWa = false;
      bool AxUXNluFOK = false;
      bool pmEZpkqbCq = false;
      string zZTyprWmUV;
      string KDLkUiAwfP;
      string UZwVxhsFLo;
      string pBHMKaqche;
      string rmzuDwVWNK;
      string GeazIYdyAH;
      string yRbfeIwzZs;
      string qWNBWgaARB;
      string MWqAiLZHDk;
      string wrcafZLTQt;
      string AWwTSiQZba;
      string ydfyubaaxT;
      string hnunxytmUx;
      string VGiWApZXgz;
      string tAfbmRMdeE;
      string zjWwLMaIWT;
      string ncEeFqtJyE;
      string CCsxYhHSBe;
      string lPHQxkjlKm;
      string OQAMKQwAWu;
      if(zZTyprWmUV == AWwTSiQZba){XCeaCwpYWd = true;}
      else if(AWwTSiQZba == zZTyprWmUV){uJYhyHilcs = true;}
      if(KDLkUiAwfP == ydfyubaaxT){EHGqgXVmhT = true;}
      else if(ydfyubaaxT == KDLkUiAwfP){WmsCpBJmCP = true;}
      if(UZwVxhsFLo == hnunxytmUx){GHyKokBflI = true;}
      else if(hnunxytmUx == UZwVxhsFLo){JRirSXrban = true;}
      if(pBHMKaqche == VGiWApZXgz){kGwFHjkgOA = true;}
      else if(VGiWApZXgz == pBHMKaqche){WrcpmQTSAF = true;}
      if(rmzuDwVWNK == tAfbmRMdeE){tLOgiGKIel = true;}
      else if(tAfbmRMdeE == rmzuDwVWNK){sCPYUqWtGD = true;}
      if(GeazIYdyAH == zjWwLMaIWT){uISCnPEUkQ = true;}
      else if(zjWwLMaIWT == GeazIYdyAH){akxXbcZfOa = true;}
      if(yRbfeIwzZs == ncEeFqtJyE){tJmOsxLAjx = true;}
      else if(ncEeFqtJyE == yRbfeIwzZs){PHKnVdJCOZ = true;}
      if(qWNBWgaARB == CCsxYhHSBe){mnYgYurRbi = true;}
      if(MWqAiLZHDk == lPHQxkjlKm){arAzMcnsRr = true;}
      if(wrcafZLTQt == OQAMKQwAWu){ePwxFjYAnk = true;}
      while(CCsxYhHSBe == qWNBWgaARB){hplxWHBKWa = true;}
      while(lPHQxkjlKm == lPHQxkjlKm){AxUXNluFOK = true;}
      while(OQAMKQwAWu == OQAMKQwAWu){pmEZpkqbCq = true;}
      if(XCeaCwpYWd == true){XCeaCwpYWd = false;}
      if(EHGqgXVmhT == true){EHGqgXVmhT = false;}
      if(GHyKokBflI == true){GHyKokBflI = false;}
      if(kGwFHjkgOA == true){kGwFHjkgOA = false;}
      if(tLOgiGKIel == true){tLOgiGKIel = false;}
      if(uISCnPEUkQ == true){uISCnPEUkQ = false;}
      if(tJmOsxLAjx == true){tJmOsxLAjx = false;}
      if(mnYgYurRbi == true){mnYgYurRbi = false;}
      if(arAzMcnsRr == true){arAzMcnsRr = false;}
      if(ePwxFjYAnk == true){ePwxFjYAnk = false;}
      if(uJYhyHilcs == true){uJYhyHilcs = false;}
      if(WmsCpBJmCP == true){WmsCpBJmCP = false;}
      if(JRirSXrban == true){JRirSXrban = false;}
      if(WrcpmQTSAF == true){WrcpmQTSAF = false;}
      if(sCPYUqWtGD == true){sCPYUqWtGD = false;}
      if(akxXbcZfOa == true){akxXbcZfOa = false;}
      if(PHKnVdJCOZ == true){PHKnVdJCOZ = false;}
      if(hplxWHBKWa == true){hplxWHBKWa = false;}
      if(AxUXNluFOK == true){AxUXNluFOK = false;}
      if(pmEZpkqbCq == true){pmEZpkqbCq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBWIWQVJRG
{ 
  void KJNiaEbimK()
  { 
      bool wZwuIAGFrz = false;
      bool GiAthMsIyY = false;
      bool RSVenKWzpt = false;
      bool BExeVkspfs = false;
      bool dchXuHRBeh = false;
      bool oTLtscDQGy = false;
      bool dHOxxCkUYw = false;
      bool SDcFtnkyif = false;
      bool rVTHFgrDkr = false;
      bool hbigPWNjZs = false;
      bool VxbiOkqGzF = false;
      bool rFgZFImHrQ = false;
      bool JhjgOqUuoX = false;
      bool ZAXpKuskrT = false;
      bool olEfAbtIbH = false;
      bool iGrJjnNuUX = false;
      bool QwQaeqgqPK = false;
      bool OCOXaXcDgl = false;
      bool xLThnTIOFV = false;
      bool hyPUDsUcAI = false;
      string uzFuANbnzi;
      string dxSqCkIsHy;
      string UYGacBbbrx;
      string qXUnGTsDqI;
      string sgaBoQVbBO;
      string cpXLAWreSy;
      string kAuCqFbekh;
      string rFCyFnxFkM;
      string fzZcTBAJmj;
      string bNkrXrkYKj;
      string npqSWWnYFL;
      string YmtFSkZShp;
      string FSqBGdUJaM;
      string DYtBXoIHFx;
      string MaDaKoSeYl;
      string SSpUdVypLs;
      string CdxsIzrshd;
      string cRMkceOPpR;
      string LpkotjhZWC;
      string pRuMthcKSK;
      if(uzFuANbnzi == npqSWWnYFL){wZwuIAGFrz = true;}
      else if(npqSWWnYFL == uzFuANbnzi){VxbiOkqGzF = true;}
      if(dxSqCkIsHy == YmtFSkZShp){GiAthMsIyY = true;}
      else if(YmtFSkZShp == dxSqCkIsHy){rFgZFImHrQ = true;}
      if(UYGacBbbrx == FSqBGdUJaM){RSVenKWzpt = true;}
      else if(FSqBGdUJaM == UYGacBbbrx){JhjgOqUuoX = true;}
      if(qXUnGTsDqI == DYtBXoIHFx){BExeVkspfs = true;}
      else if(DYtBXoIHFx == qXUnGTsDqI){ZAXpKuskrT = true;}
      if(sgaBoQVbBO == MaDaKoSeYl){dchXuHRBeh = true;}
      else if(MaDaKoSeYl == sgaBoQVbBO){olEfAbtIbH = true;}
      if(cpXLAWreSy == SSpUdVypLs){oTLtscDQGy = true;}
      else if(SSpUdVypLs == cpXLAWreSy){iGrJjnNuUX = true;}
      if(kAuCqFbekh == CdxsIzrshd){dHOxxCkUYw = true;}
      else if(CdxsIzrshd == kAuCqFbekh){QwQaeqgqPK = true;}
      if(rFCyFnxFkM == cRMkceOPpR){SDcFtnkyif = true;}
      if(fzZcTBAJmj == LpkotjhZWC){rVTHFgrDkr = true;}
      if(bNkrXrkYKj == pRuMthcKSK){hbigPWNjZs = true;}
      while(cRMkceOPpR == rFCyFnxFkM){OCOXaXcDgl = true;}
      while(LpkotjhZWC == LpkotjhZWC){xLThnTIOFV = true;}
      while(pRuMthcKSK == pRuMthcKSK){hyPUDsUcAI = true;}
      if(wZwuIAGFrz == true){wZwuIAGFrz = false;}
      if(GiAthMsIyY == true){GiAthMsIyY = false;}
      if(RSVenKWzpt == true){RSVenKWzpt = false;}
      if(BExeVkspfs == true){BExeVkspfs = false;}
      if(dchXuHRBeh == true){dchXuHRBeh = false;}
      if(oTLtscDQGy == true){oTLtscDQGy = false;}
      if(dHOxxCkUYw == true){dHOxxCkUYw = false;}
      if(SDcFtnkyif == true){SDcFtnkyif = false;}
      if(rVTHFgrDkr == true){rVTHFgrDkr = false;}
      if(hbigPWNjZs == true){hbigPWNjZs = false;}
      if(VxbiOkqGzF == true){VxbiOkqGzF = false;}
      if(rFgZFImHrQ == true){rFgZFImHrQ = false;}
      if(JhjgOqUuoX == true){JhjgOqUuoX = false;}
      if(ZAXpKuskrT == true){ZAXpKuskrT = false;}
      if(olEfAbtIbH == true){olEfAbtIbH = false;}
      if(iGrJjnNuUX == true){iGrJjnNuUX = false;}
      if(QwQaeqgqPK == true){QwQaeqgqPK = false;}
      if(OCOXaXcDgl == true){OCOXaXcDgl = false;}
      if(xLThnTIOFV == true){xLThnTIOFV = false;}
      if(hyPUDsUcAI == true){hyPUDsUcAI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TAYDBVWCUV
{ 
  void GBshxhYBhR()
  { 
      bool kGUqwORmXQ = false;
      bool SCNwoQscSF = false;
      bool ktQDJJPmsw = false;
      bool xaGLqgBhMS = false;
      bool NcCLNdSEOL = false;
      bool QtfKApoQgm = false;
      bool zdtbSqwBEI = false;
      bool OLQzqHqFof = false;
      bool pLXgeDuuKA = false;
      bool rjAZTjiasV = false;
      bool gQzGwFcgSs = false;
      bool yiaBwnFMxO = false;
      bool wBqDQdLqeH = false;
      bool YQMTyZLRjY = false;
      bool ZNbRBIJzde = false;
      bool dVddYfZupS = false;
      bool tlBLThVHCV = false;
      bool bmbXnhYYCH = false;
      bool UMNAcCmitS = false;
      bool zPbRemMPxT = false;
      string PZAEuxZewC;
      string GrVGwhMJyR;
      string dWcQzxeEGj;
      string MkEWHepUZk;
      string mGEFlFutXI;
      string GItrwsxjEx;
      string RUXMoVmyzQ;
      string rriNeXRWds;
      string CkfycDpMaO;
      string gFQcSSirQQ;
      string SwuHPOZgMY;
      string aaGKufnZik;
      string eZXjimbGuM;
      string nYFNZFpYhO;
      string dJzBmGzFgl;
      string dJIelsYKYc;
      string mSlAkBUrjp;
      string pPrUHVZWxc;
      string mVYIheQabg;
      string ffAEbKXyQk;
      if(PZAEuxZewC == SwuHPOZgMY){kGUqwORmXQ = true;}
      else if(SwuHPOZgMY == PZAEuxZewC){gQzGwFcgSs = true;}
      if(GrVGwhMJyR == aaGKufnZik){SCNwoQscSF = true;}
      else if(aaGKufnZik == GrVGwhMJyR){yiaBwnFMxO = true;}
      if(dWcQzxeEGj == eZXjimbGuM){ktQDJJPmsw = true;}
      else if(eZXjimbGuM == dWcQzxeEGj){wBqDQdLqeH = true;}
      if(MkEWHepUZk == nYFNZFpYhO){xaGLqgBhMS = true;}
      else if(nYFNZFpYhO == MkEWHepUZk){YQMTyZLRjY = true;}
      if(mGEFlFutXI == dJzBmGzFgl){NcCLNdSEOL = true;}
      else if(dJzBmGzFgl == mGEFlFutXI){ZNbRBIJzde = true;}
      if(GItrwsxjEx == dJIelsYKYc){QtfKApoQgm = true;}
      else if(dJIelsYKYc == GItrwsxjEx){dVddYfZupS = true;}
      if(RUXMoVmyzQ == mSlAkBUrjp){zdtbSqwBEI = true;}
      else if(mSlAkBUrjp == RUXMoVmyzQ){tlBLThVHCV = true;}
      if(rriNeXRWds == pPrUHVZWxc){OLQzqHqFof = true;}
      if(CkfycDpMaO == mVYIheQabg){pLXgeDuuKA = true;}
      if(gFQcSSirQQ == ffAEbKXyQk){rjAZTjiasV = true;}
      while(pPrUHVZWxc == rriNeXRWds){bmbXnhYYCH = true;}
      while(mVYIheQabg == mVYIheQabg){UMNAcCmitS = true;}
      while(ffAEbKXyQk == ffAEbKXyQk){zPbRemMPxT = true;}
      if(kGUqwORmXQ == true){kGUqwORmXQ = false;}
      if(SCNwoQscSF == true){SCNwoQscSF = false;}
      if(ktQDJJPmsw == true){ktQDJJPmsw = false;}
      if(xaGLqgBhMS == true){xaGLqgBhMS = false;}
      if(NcCLNdSEOL == true){NcCLNdSEOL = false;}
      if(QtfKApoQgm == true){QtfKApoQgm = false;}
      if(zdtbSqwBEI == true){zdtbSqwBEI = false;}
      if(OLQzqHqFof == true){OLQzqHqFof = false;}
      if(pLXgeDuuKA == true){pLXgeDuuKA = false;}
      if(rjAZTjiasV == true){rjAZTjiasV = false;}
      if(gQzGwFcgSs == true){gQzGwFcgSs = false;}
      if(yiaBwnFMxO == true){yiaBwnFMxO = false;}
      if(wBqDQdLqeH == true){wBqDQdLqeH = false;}
      if(YQMTyZLRjY == true){YQMTyZLRjY = false;}
      if(ZNbRBIJzde == true){ZNbRBIJzde = false;}
      if(dVddYfZupS == true){dVddYfZupS = false;}
      if(tlBLThVHCV == true){tlBLThVHCV = false;}
      if(bmbXnhYYCH == true){bmbXnhYYCH = false;}
      if(UMNAcCmitS == true){UMNAcCmitS = false;}
      if(zPbRemMPxT == true){zPbRemMPxT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHQTHCRZYJ
{ 
  void yEJhcpeqLP()
  { 
      bool maQTtTsSzj = false;
      bool ASNWuzVMhs = false;
      bool klWFPbLjqW = false;
      bool dMSbLCqhEu = false;
      bool DblbMJINeZ = false;
      bool OoBBwAEKES = false;
      bool HJacFmzkLs = false;
      bool HmHmoIztsG = false;
      bool TyERHoLRfK = false;
      bool xfdlmtBJWZ = false;
      bool JWClRagOLm = false;
      bool BKRxyJEIUQ = false;
      bool bhFAuaIUAu = false;
      bool HpXSxxuSzg = false;
      bool HxFrImNgnc = false;
      bool prnFxaQBpp = false;
      bool RMOQeLlyAB = false;
      bool OkJnIecMrI = false;
      bool MbgWEPBRVV = false;
      bool fsbIOuhoMx = false;
      string ikwSrHmxRb;
      string PZXfyRmhwD;
      string FQCDBBaAan;
      string OClrmLLeER;
      string ElIkUPLmQQ;
      string HRjbMRisQp;
      string glVcNMnerl;
      string FHcdySIQil;
      string onjKgxSKfV;
      string cSONkSQeXI;
      string aftdKAnFcs;
      string IRJdBrCKwQ;
      string sdzWJlsPsf;
      string CcsaKItFzf;
      string INglMKJjMs;
      string QFiHOxgXUY;
      string HYMxqfXhTr;
      string ywLPHewNJy;
      string cICzOxtlLN;
      string bVjaYjBjug;
      if(ikwSrHmxRb == aftdKAnFcs){maQTtTsSzj = true;}
      else if(aftdKAnFcs == ikwSrHmxRb){JWClRagOLm = true;}
      if(PZXfyRmhwD == IRJdBrCKwQ){ASNWuzVMhs = true;}
      else if(IRJdBrCKwQ == PZXfyRmhwD){BKRxyJEIUQ = true;}
      if(FQCDBBaAan == sdzWJlsPsf){klWFPbLjqW = true;}
      else if(sdzWJlsPsf == FQCDBBaAan){bhFAuaIUAu = true;}
      if(OClrmLLeER == CcsaKItFzf){dMSbLCqhEu = true;}
      else if(CcsaKItFzf == OClrmLLeER){HpXSxxuSzg = true;}
      if(ElIkUPLmQQ == INglMKJjMs){DblbMJINeZ = true;}
      else if(INglMKJjMs == ElIkUPLmQQ){HxFrImNgnc = true;}
      if(HRjbMRisQp == QFiHOxgXUY){OoBBwAEKES = true;}
      else if(QFiHOxgXUY == HRjbMRisQp){prnFxaQBpp = true;}
      if(glVcNMnerl == HYMxqfXhTr){HJacFmzkLs = true;}
      else if(HYMxqfXhTr == glVcNMnerl){RMOQeLlyAB = true;}
      if(FHcdySIQil == ywLPHewNJy){HmHmoIztsG = true;}
      if(onjKgxSKfV == cICzOxtlLN){TyERHoLRfK = true;}
      if(cSONkSQeXI == bVjaYjBjug){xfdlmtBJWZ = true;}
      while(ywLPHewNJy == FHcdySIQil){OkJnIecMrI = true;}
      while(cICzOxtlLN == cICzOxtlLN){MbgWEPBRVV = true;}
      while(bVjaYjBjug == bVjaYjBjug){fsbIOuhoMx = true;}
      if(maQTtTsSzj == true){maQTtTsSzj = false;}
      if(ASNWuzVMhs == true){ASNWuzVMhs = false;}
      if(klWFPbLjqW == true){klWFPbLjqW = false;}
      if(dMSbLCqhEu == true){dMSbLCqhEu = false;}
      if(DblbMJINeZ == true){DblbMJINeZ = false;}
      if(OoBBwAEKES == true){OoBBwAEKES = false;}
      if(HJacFmzkLs == true){HJacFmzkLs = false;}
      if(HmHmoIztsG == true){HmHmoIztsG = false;}
      if(TyERHoLRfK == true){TyERHoLRfK = false;}
      if(xfdlmtBJWZ == true){xfdlmtBJWZ = false;}
      if(JWClRagOLm == true){JWClRagOLm = false;}
      if(BKRxyJEIUQ == true){BKRxyJEIUQ = false;}
      if(bhFAuaIUAu == true){bhFAuaIUAu = false;}
      if(HpXSxxuSzg == true){HpXSxxuSzg = false;}
      if(HxFrImNgnc == true){HxFrImNgnc = false;}
      if(prnFxaQBpp == true){prnFxaQBpp = false;}
      if(RMOQeLlyAB == true){RMOQeLlyAB = false;}
      if(OkJnIecMrI == true){OkJnIecMrI = false;}
      if(MbgWEPBRVV == true){MbgWEPBRVV = false;}
      if(fsbIOuhoMx == true){fsbIOuhoMx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VAFNGGHSGE
{ 
  void KdsWRhNAUt()
  { 
      bool gmksXbMEwk = false;
      bool tpUEDlFHnk = false;
      bool oGLXEJmEwO = false;
      bool QFDfdiBUuB = false;
      bool BNierxLQzm = false;
      bool gRrqJaaMoN = false;
      bool nHHhTnmnaT = false;
      bool jkLmibXgeG = false;
      bool xWEJgyMLWD = false;
      bool HnegNtFAKE = false;
      bool JWofCwFEIg = false;
      bool DtghQQCyAU = false;
      bool aaRXLuFdZo = false;
      bool WWWaxZgYGk = false;
      bool rIDoANHwQw = false;
      bool qGApchFRUG = false;
      bool pbeSKfXFkp = false;
      bool idqPbSXbXx = false;
      bool nINdyPWfyO = false;
      bool UPEAtQdjeT = false;
      string FQLeYyLtuO;
      string nVxxoetQyB;
      string SNUgRiFjUU;
      string glFfBdLlde;
      string GeWlVgujEe;
      string OHbaVrwdNp;
      string saZagCPQwK;
      string THmStnphLj;
      string nVeoFZJeJJ;
      string ghYmlfFwET;
      string RdnsLHTIfh;
      string BOScBXukUH;
      string rkHmdlhzgN;
      string itcqSJgkcy;
      string GBybHSOukN;
      string kTaxbfVAPZ;
      string YTaRzHkaKr;
      string pJHWBqlffK;
      string WlOTcOSePl;
      string mgVCZlZgbz;
      if(FQLeYyLtuO == RdnsLHTIfh){gmksXbMEwk = true;}
      else if(RdnsLHTIfh == FQLeYyLtuO){JWofCwFEIg = true;}
      if(nVxxoetQyB == BOScBXukUH){tpUEDlFHnk = true;}
      else if(BOScBXukUH == nVxxoetQyB){DtghQQCyAU = true;}
      if(SNUgRiFjUU == rkHmdlhzgN){oGLXEJmEwO = true;}
      else if(rkHmdlhzgN == SNUgRiFjUU){aaRXLuFdZo = true;}
      if(glFfBdLlde == itcqSJgkcy){QFDfdiBUuB = true;}
      else if(itcqSJgkcy == glFfBdLlde){WWWaxZgYGk = true;}
      if(GeWlVgujEe == GBybHSOukN){BNierxLQzm = true;}
      else if(GBybHSOukN == GeWlVgujEe){rIDoANHwQw = true;}
      if(OHbaVrwdNp == kTaxbfVAPZ){gRrqJaaMoN = true;}
      else if(kTaxbfVAPZ == OHbaVrwdNp){qGApchFRUG = true;}
      if(saZagCPQwK == YTaRzHkaKr){nHHhTnmnaT = true;}
      else if(YTaRzHkaKr == saZagCPQwK){pbeSKfXFkp = true;}
      if(THmStnphLj == pJHWBqlffK){jkLmibXgeG = true;}
      if(nVeoFZJeJJ == WlOTcOSePl){xWEJgyMLWD = true;}
      if(ghYmlfFwET == mgVCZlZgbz){HnegNtFAKE = true;}
      while(pJHWBqlffK == THmStnphLj){idqPbSXbXx = true;}
      while(WlOTcOSePl == WlOTcOSePl){nINdyPWfyO = true;}
      while(mgVCZlZgbz == mgVCZlZgbz){UPEAtQdjeT = true;}
      if(gmksXbMEwk == true){gmksXbMEwk = false;}
      if(tpUEDlFHnk == true){tpUEDlFHnk = false;}
      if(oGLXEJmEwO == true){oGLXEJmEwO = false;}
      if(QFDfdiBUuB == true){QFDfdiBUuB = false;}
      if(BNierxLQzm == true){BNierxLQzm = false;}
      if(gRrqJaaMoN == true){gRrqJaaMoN = false;}
      if(nHHhTnmnaT == true){nHHhTnmnaT = false;}
      if(jkLmibXgeG == true){jkLmibXgeG = false;}
      if(xWEJgyMLWD == true){xWEJgyMLWD = false;}
      if(HnegNtFAKE == true){HnegNtFAKE = false;}
      if(JWofCwFEIg == true){JWofCwFEIg = false;}
      if(DtghQQCyAU == true){DtghQQCyAU = false;}
      if(aaRXLuFdZo == true){aaRXLuFdZo = false;}
      if(WWWaxZgYGk == true){WWWaxZgYGk = false;}
      if(rIDoANHwQw == true){rIDoANHwQw = false;}
      if(qGApchFRUG == true){qGApchFRUG = false;}
      if(pbeSKfXFkp == true){pbeSKfXFkp = false;}
      if(idqPbSXbXx == true){idqPbSXbXx = false;}
      if(nINdyPWfyO == true){nINdyPWfyO = false;}
      if(UPEAtQdjeT == true){UPEAtQdjeT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTRTHGWNNO
{ 
  void KmxQuETeUo()
  { 
      bool GTKqLTOgtE = false;
      bool YIdweXAIVg = false;
      bool NcosVDqHPi = false;
      bool AjkujYtoVu = false;
      bool MVumsHbIbN = false;
      bool lWtnQdeRUH = false;
      bool cHQLDoXiLF = false;
      bool cLmZTrhCzN = false;
      bool bhfCwcpwdG = false;
      bool tcTNSFEiiE = false;
      bool jsxVjajTUY = false;
      bool ubRGetaOOa = false;
      bool yaEFLAqYGO = false;
      bool myTtdikKRV = false;
      bool sVbEKSKMiX = false;
      bool dpTHGJnqJj = false;
      bool iKNFlwHWcw = false;
      bool JQxshbyAts = false;
      bool odphkxeLnT = false;
      bool usAgmhIWRN = false;
      string xFrbIkHRIK;
      string JiNGxlxCee;
      string yMUTGJhSXa;
      string IsRkjihuup;
      string tSeIEpcxTX;
      string HxfBsjkXUz;
      string DnthBQQcWO;
      string ECGnkehMPQ;
      string fjyzSLNQrz;
      string xJawmFYwGm;
      string YAaFTEqqPO;
      string CXIDSSptOp;
      string CAjWQtbJBe;
      string FkFbqfJsfN;
      string TVAdwZBWdU;
      string PdhQkYPEnY;
      string cgpkIRSgLl;
      string IwOAVfzGZq;
      string sFfgPbDoqS;
      string QFFGkmfPVe;
      if(xFrbIkHRIK == YAaFTEqqPO){GTKqLTOgtE = true;}
      else if(YAaFTEqqPO == xFrbIkHRIK){jsxVjajTUY = true;}
      if(JiNGxlxCee == CXIDSSptOp){YIdweXAIVg = true;}
      else if(CXIDSSptOp == JiNGxlxCee){ubRGetaOOa = true;}
      if(yMUTGJhSXa == CAjWQtbJBe){NcosVDqHPi = true;}
      else if(CAjWQtbJBe == yMUTGJhSXa){yaEFLAqYGO = true;}
      if(IsRkjihuup == FkFbqfJsfN){AjkujYtoVu = true;}
      else if(FkFbqfJsfN == IsRkjihuup){myTtdikKRV = true;}
      if(tSeIEpcxTX == TVAdwZBWdU){MVumsHbIbN = true;}
      else if(TVAdwZBWdU == tSeIEpcxTX){sVbEKSKMiX = true;}
      if(HxfBsjkXUz == PdhQkYPEnY){lWtnQdeRUH = true;}
      else if(PdhQkYPEnY == HxfBsjkXUz){dpTHGJnqJj = true;}
      if(DnthBQQcWO == cgpkIRSgLl){cHQLDoXiLF = true;}
      else if(cgpkIRSgLl == DnthBQQcWO){iKNFlwHWcw = true;}
      if(ECGnkehMPQ == IwOAVfzGZq){cLmZTrhCzN = true;}
      if(fjyzSLNQrz == sFfgPbDoqS){bhfCwcpwdG = true;}
      if(xJawmFYwGm == QFFGkmfPVe){tcTNSFEiiE = true;}
      while(IwOAVfzGZq == ECGnkehMPQ){JQxshbyAts = true;}
      while(sFfgPbDoqS == sFfgPbDoqS){odphkxeLnT = true;}
      while(QFFGkmfPVe == QFFGkmfPVe){usAgmhIWRN = true;}
      if(GTKqLTOgtE == true){GTKqLTOgtE = false;}
      if(YIdweXAIVg == true){YIdweXAIVg = false;}
      if(NcosVDqHPi == true){NcosVDqHPi = false;}
      if(AjkujYtoVu == true){AjkujYtoVu = false;}
      if(MVumsHbIbN == true){MVumsHbIbN = false;}
      if(lWtnQdeRUH == true){lWtnQdeRUH = false;}
      if(cHQLDoXiLF == true){cHQLDoXiLF = false;}
      if(cLmZTrhCzN == true){cLmZTrhCzN = false;}
      if(bhfCwcpwdG == true){bhfCwcpwdG = false;}
      if(tcTNSFEiiE == true){tcTNSFEiiE = false;}
      if(jsxVjajTUY == true){jsxVjajTUY = false;}
      if(ubRGetaOOa == true){ubRGetaOOa = false;}
      if(yaEFLAqYGO == true){yaEFLAqYGO = false;}
      if(myTtdikKRV == true){myTtdikKRV = false;}
      if(sVbEKSKMiX == true){sVbEKSKMiX = false;}
      if(dpTHGJnqJj == true){dpTHGJnqJj = false;}
      if(iKNFlwHWcw == true){iKNFlwHWcw = false;}
      if(JQxshbyAts == true){JQxshbyAts = false;}
      if(odphkxeLnT == true){odphkxeLnT = false;}
      if(usAgmhIWRN == true){usAgmhIWRN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPTVYCYXMB
{ 
  void WQVcwrifdr()
  { 
      bool MBewUkQBnP = false;
      bool UrnfqgzRqU = false;
      bool ariAJUAWWn = false;
      bool yiRMPxZfFI = false;
      bool WAljXwarkk = false;
      bool sElzxURelz = false;
      bool ktdzRlabPs = false;
      bool HTLhyaFybN = false;
      bool tHllttxSOu = false;
      bool ftsGXcWlSl = false;
      bool VzcrcZrEAW = false;
      bool OTCYEcIqFW = false;
      bool nHNTNMaFJV = false;
      bool ESforuesIU = false;
      bool BsRqgLrTBu = false;
      bool TeguxNlIeQ = false;
      bool ymteRwmNgJ = false;
      bool yOhkVupVmB = false;
      bool UGDOBYlkqd = false;
      bool IVOrVOylZj = false;
      string TDOklzUJQV;
      string mqoeiMaVNj;
      string YWRqcIYRBF;
      string ySLkTfaCnE;
      string RnuwmpwXTL;
      string legHwwkWHc;
      string ZDHLWUfDKD;
      string lXgJSjbVDl;
      string LBxpSTlDoW;
      string uDtLdOgiYS;
      string KsMQYOxXoL;
      string UPTVQYFQsD;
      string ibOmIicVeD;
      string DrwjbSngRD;
      string VNOcCejYtE;
      string JPpVjhdYIp;
      string kbrkIcSisy;
      string jXyohUMlkc;
      string yEbZtmBaAs;
      string nOXbRsVcTY;
      if(TDOklzUJQV == KsMQYOxXoL){MBewUkQBnP = true;}
      else if(KsMQYOxXoL == TDOklzUJQV){VzcrcZrEAW = true;}
      if(mqoeiMaVNj == UPTVQYFQsD){UrnfqgzRqU = true;}
      else if(UPTVQYFQsD == mqoeiMaVNj){OTCYEcIqFW = true;}
      if(YWRqcIYRBF == ibOmIicVeD){ariAJUAWWn = true;}
      else if(ibOmIicVeD == YWRqcIYRBF){nHNTNMaFJV = true;}
      if(ySLkTfaCnE == DrwjbSngRD){yiRMPxZfFI = true;}
      else if(DrwjbSngRD == ySLkTfaCnE){ESforuesIU = true;}
      if(RnuwmpwXTL == VNOcCejYtE){WAljXwarkk = true;}
      else if(VNOcCejYtE == RnuwmpwXTL){BsRqgLrTBu = true;}
      if(legHwwkWHc == JPpVjhdYIp){sElzxURelz = true;}
      else if(JPpVjhdYIp == legHwwkWHc){TeguxNlIeQ = true;}
      if(ZDHLWUfDKD == kbrkIcSisy){ktdzRlabPs = true;}
      else if(kbrkIcSisy == ZDHLWUfDKD){ymteRwmNgJ = true;}
      if(lXgJSjbVDl == jXyohUMlkc){HTLhyaFybN = true;}
      if(LBxpSTlDoW == yEbZtmBaAs){tHllttxSOu = true;}
      if(uDtLdOgiYS == nOXbRsVcTY){ftsGXcWlSl = true;}
      while(jXyohUMlkc == lXgJSjbVDl){yOhkVupVmB = true;}
      while(yEbZtmBaAs == yEbZtmBaAs){UGDOBYlkqd = true;}
      while(nOXbRsVcTY == nOXbRsVcTY){IVOrVOylZj = true;}
      if(MBewUkQBnP == true){MBewUkQBnP = false;}
      if(UrnfqgzRqU == true){UrnfqgzRqU = false;}
      if(ariAJUAWWn == true){ariAJUAWWn = false;}
      if(yiRMPxZfFI == true){yiRMPxZfFI = false;}
      if(WAljXwarkk == true){WAljXwarkk = false;}
      if(sElzxURelz == true){sElzxURelz = false;}
      if(ktdzRlabPs == true){ktdzRlabPs = false;}
      if(HTLhyaFybN == true){HTLhyaFybN = false;}
      if(tHllttxSOu == true){tHllttxSOu = false;}
      if(ftsGXcWlSl == true){ftsGXcWlSl = false;}
      if(VzcrcZrEAW == true){VzcrcZrEAW = false;}
      if(OTCYEcIqFW == true){OTCYEcIqFW = false;}
      if(nHNTNMaFJV == true){nHNTNMaFJV = false;}
      if(ESforuesIU == true){ESforuesIU = false;}
      if(BsRqgLrTBu == true){BsRqgLrTBu = false;}
      if(TeguxNlIeQ == true){TeguxNlIeQ = false;}
      if(ymteRwmNgJ == true){ymteRwmNgJ = false;}
      if(yOhkVupVmB == true){yOhkVupVmB = false;}
      if(UGDOBYlkqd == true){UGDOBYlkqd = false;}
      if(IVOrVOylZj == true){IVOrVOylZj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZOAZXTZSB
{ 
  void yNMOWUBuAf()
  { 
      bool xAPSVzgqzh = false;
      bool OicaroNRiE = false;
      bool IOoKbYxLxk = false;
      bool XxYpWIYAob = false;
      bool oIdrBxnFmM = false;
      bool nTznwiLFpx = false;
      bool BVsOJQKlDi = false;
      bool QMbHPAjxJd = false;
      bool jrYkwExjsn = false;
      bool xSJrZSOPhj = false;
      bool mBBDwbqrXw = false;
      bool yNwMMJxISE = false;
      bool SZrPlxCjgx = false;
      bool kUOYqipUnT = false;
      bool NFLxoiVxeQ = false;
      bool VGxcRNIlRy = false;
      bool ZGLaKczXUd = false;
      bool SbTyqNOuZC = false;
      bool aEEPaeXkHc = false;
      bool ZEDotGtjlM = false;
      string QqzDzjpjYm;
      string MsfzjkzsEM;
      string NEMjkngAGE;
      string EZKBabMser;
      string YYqpCERHQz;
      string PrLCKMdORL;
      string DpdUhlidYI;
      string XGOLmoNWhg;
      string VYjHoMOIqN;
      string xxaSoitWHP;
      string VniHaIczOV;
      string zHgkpdFWeV;
      string XamKLZewVE;
      string tqPRKgobff;
      string iOsUOpQpbK;
      string cXqlquAYwB;
      string dgcKaIrPZI;
      string odpzlJgRwU;
      string JoTLaVzcZP;
      string gQfeBBkisF;
      if(QqzDzjpjYm == VniHaIczOV){xAPSVzgqzh = true;}
      else if(VniHaIczOV == QqzDzjpjYm){mBBDwbqrXw = true;}
      if(MsfzjkzsEM == zHgkpdFWeV){OicaroNRiE = true;}
      else if(zHgkpdFWeV == MsfzjkzsEM){yNwMMJxISE = true;}
      if(NEMjkngAGE == XamKLZewVE){IOoKbYxLxk = true;}
      else if(XamKLZewVE == NEMjkngAGE){SZrPlxCjgx = true;}
      if(EZKBabMser == tqPRKgobff){XxYpWIYAob = true;}
      else if(tqPRKgobff == EZKBabMser){kUOYqipUnT = true;}
      if(YYqpCERHQz == iOsUOpQpbK){oIdrBxnFmM = true;}
      else if(iOsUOpQpbK == YYqpCERHQz){NFLxoiVxeQ = true;}
      if(PrLCKMdORL == cXqlquAYwB){nTznwiLFpx = true;}
      else if(cXqlquAYwB == PrLCKMdORL){VGxcRNIlRy = true;}
      if(DpdUhlidYI == dgcKaIrPZI){BVsOJQKlDi = true;}
      else if(dgcKaIrPZI == DpdUhlidYI){ZGLaKczXUd = true;}
      if(XGOLmoNWhg == odpzlJgRwU){QMbHPAjxJd = true;}
      if(VYjHoMOIqN == JoTLaVzcZP){jrYkwExjsn = true;}
      if(xxaSoitWHP == gQfeBBkisF){xSJrZSOPhj = true;}
      while(odpzlJgRwU == XGOLmoNWhg){SbTyqNOuZC = true;}
      while(JoTLaVzcZP == JoTLaVzcZP){aEEPaeXkHc = true;}
      while(gQfeBBkisF == gQfeBBkisF){ZEDotGtjlM = true;}
      if(xAPSVzgqzh == true){xAPSVzgqzh = false;}
      if(OicaroNRiE == true){OicaroNRiE = false;}
      if(IOoKbYxLxk == true){IOoKbYxLxk = false;}
      if(XxYpWIYAob == true){XxYpWIYAob = false;}
      if(oIdrBxnFmM == true){oIdrBxnFmM = false;}
      if(nTznwiLFpx == true){nTznwiLFpx = false;}
      if(BVsOJQKlDi == true){BVsOJQKlDi = false;}
      if(QMbHPAjxJd == true){QMbHPAjxJd = false;}
      if(jrYkwExjsn == true){jrYkwExjsn = false;}
      if(xSJrZSOPhj == true){xSJrZSOPhj = false;}
      if(mBBDwbqrXw == true){mBBDwbqrXw = false;}
      if(yNwMMJxISE == true){yNwMMJxISE = false;}
      if(SZrPlxCjgx == true){SZrPlxCjgx = false;}
      if(kUOYqipUnT == true){kUOYqipUnT = false;}
      if(NFLxoiVxeQ == true){NFLxoiVxeQ = false;}
      if(VGxcRNIlRy == true){VGxcRNIlRy = false;}
      if(ZGLaKczXUd == true){ZGLaKczXUd = false;}
      if(SbTyqNOuZC == true){SbTyqNOuZC = false;}
      if(aEEPaeXkHc == true){aEEPaeXkHc = false;}
      if(ZEDotGtjlM == true){ZEDotGtjlM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GAXNGDEJBT
{ 
  void WSTMlIlAKJ()
  { 
      bool EqIBQaJSXW = false;
      bool TelgjyTjua = false;
      bool ldjmCLDIXp = false;
      bool nXpezYFWNO = false;
      bool KDZTNgCTjF = false;
      bool HaJHJaHVzF = false;
      bool XAtgiwoGhL = false;
      bool rwWfQhEPZV = false;
      bool IjYRhNNiUX = false;
      bool RjXHqJIrkR = false;
      bool qwkXNKEcpb = false;
      bool WqucwnbcyV = false;
      bool hGkJsHYOoG = false;
      bool YLdIdMyAEX = false;
      bool IkrsBaotLC = false;
      bool hfsPikKbeF = false;
      bool lomiCKMmzj = false;
      bool oaXaMwNrIS = false;
      bool SdDlYsSOYs = false;
      bool BVVzkTxIqp = false;
      string nORBNBJcNN;
      string ZzPQEthenL;
      string fKjSNMAKaw;
      string WOoeHYFOuV;
      string UmFTIXqDBX;
      string YScuwddzmA;
      string AzBQqLKjJe;
      string oSjRpsEPKp;
      string VxIDWDkshc;
      string tGatVVkncw;
      string MGtViFiLED;
      string YOnxdDpysm;
      string ZQCfjhrowU;
      string HQmNcPClUR;
      string UZodEfRcQR;
      string emtoWuDNkA;
      string NsOjuIaaUO;
      string AEcbRzbYbE;
      string POYeoUVxqg;
      string LoATEbLEhw;
      if(nORBNBJcNN == MGtViFiLED){EqIBQaJSXW = true;}
      else if(MGtViFiLED == nORBNBJcNN){qwkXNKEcpb = true;}
      if(ZzPQEthenL == YOnxdDpysm){TelgjyTjua = true;}
      else if(YOnxdDpysm == ZzPQEthenL){WqucwnbcyV = true;}
      if(fKjSNMAKaw == ZQCfjhrowU){ldjmCLDIXp = true;}
      else if(ZQCfjhrowU == fKjSNMAKaw){hGkJsHYOoG = true;}
      if(WOoeHYFOuV == HQmNcPClUR){nXpezYFWNO = true;}
      else if(HQmNcPClUR == WOoeHYFOuV){YLdIdMyAEX = true;}
      if(UmFTIXqDBX == UZodEfRcQR){KDZTNgCTjF = true;}
      else if(UZodEfRcQR == UmFTIXqDBX){IkrsBaotLC = true;}
      if(YScuwddzmA == emtoWuDNkA){HaJHJaHVzF = true;}
      else if(emtoWuDNkA == YScuwddzmA){hfsPikKbeF = true;}
      if(AzBQqLKjJe == NsOjuIaaUO){XAtgiwoGhL = true;}
      else if(NsOjuIaaUO == AzBQqLKjJe){lomiCKMmzj = true;}
      if(oSjRpsEPKp == AEcbRzbYbE){rwWfQhEPZV = true;}
      if(VxIDWDkshc == POYeoUVxqg){IjYRhNNiUX = true;}
      if(tGatVVkncw == LoATEbLEhw){RjXHqJIrkR = true;}
      while(AEcbRzbYbE == oSjRpsEPKp){oaXaMwNrIS = true;}
      while(POYeoUVxqg == POYeoUVxqg){SdDlYsSOYs = true;}
      while(LoATEbLEhw == LoATEbLEhw){BVVzkTxIqp = true;}
      if(EqIBQaJSXW == true){EqIBQaJSXW = false;}
      if(TelgjyTjua == true){TelgjyTjua = false;}
      if(ldjmCLDIXp == true){ldjmCLDIXp = false;}
      if(nXpezYFWNO == true){nXpezYFWNO = false;}
      if(KDZTNgCTjF == true){KDZTNgCTjF = false;}
      if(HaJHJaHVzF == true){HaJHJaHVzF = false;}
      if(XAtgiwoGhL == true){XAtgiwoGhL = false;}
      if(rwWfQhEPZV == true){rwWfQhEPZV = false;}
      if(IjYRhNNiUX == true){IjYRhNNiUX = false;}
      if(RjXHqJIrkR == true){RjXHqJIrkR = false;}
      if(qwkXNKEcpb == true){qwkXNKEcpb = false;}
      if(WqucwnbcyV == true){WqucwnbcyV = false;}
      if(hGkJsHYOoG == true){hGkJsHYOoG = false;}
      if(YLdIdMyAEX == true){YLdIdMyAEX = false;}
      if(IkrsBaotLC == true){IkrsBaotLC = false;}
      if(hfsPikKbeF == true){hfsPikKbeF = false;}
      if(lomiCKMmzj == true){lomiCKMmzj = false;}
      if(oaXaMwNrIS == true){oaXaMwNrIS = false;}
      if(SdDlYsSOYs == true){SdDlYsSOYs = false;}
      if(BVVzkTxIqp == true){BVVzkTxIqp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHIOLBLMXR
{ 
  void nEVGrFsmtb()
  { 
      bool SZDeNjjXRB = false;
      bool bkBBKbdKqe = false;
      bool PFmiVZeTxS = false;
      bool nxopUppTca = false;
      bool nKIPMIRCRj = false;
      bool AGzLCMlTJn = false;
      bool EPZyNduKfT = false;
      bool lJhQqFxXWN = false;
      bool HbCMSgxdnI = false;
      bool EVJnVXjJBi = false;
      bool MGWxyqYiUw = false;
      bool OOxwfbNNfg = false;
      bool gQWWPPzstS = false;
      bool VnVnAAFFNa = false;
      bool IOIqtoYNIs = false;
      bool KVcTCwjzgi = false;
      bool qenBaarJwf = false;
      bool WHzEYRHeca = false;
      bool plkBHzKBlE = false;
      bool QGXejcZHPS = false;
      string soIqKVycUr;
      string YgngFuRKfN;
      string AoKYJfpCAy;
      string LkaGgzroxH;
      string pKxATEbghZ;
      string ViVCzEeihd;
      string fwbVgnGhzG;
      string DcMXXoqJFE;
      string EJTabcPXGb;
      string TIGTbtibTf;
      string ysgaWsVxeK;
      string MVddZVbBsE;
      string XhbWluWswc;
      string GPoYFKcsEi;
      string GSsuOydbtG;
      string SghPHQRJob;
      string WcABExfEYO;
      string sixKxFogHm;
      string QtypKYhZRo;
      string sTDcMdRqqR;
      if(soIqKVycUr == ysgaWsVxeK){SZDeNjjXRB = true;}
      else if(ysgaWsVxeK == soIqKVycUr){MGWxyqYiUw = true;}
      if(YgngFuRKfN == MVddZVbBsE){bkBBKbdKqe = true;}
      else if(MVddZVbBsE == YgngFuRKfN){OOxwfbNNfg = true;}
      if(AoKYJfpCAy == XhbWluWswc){PFmiVZeTxS = true;}
      else if(XhbWluWswc == AoKYJfpCAy){gQWWPPzstS = true;}
      if(LkaGgzroxH == GPoYFKcsEi){nxopUppTca = true;}
      else if(GPoYFKcsEi == LkaGgzroxH){VnVnAAFFNa = true;}
      if(pKxATEbghZ == GSsuOydbtG){nKIPMIRCRj = true;}
      else if(GSsuOydbtG == pKxATEbghZ){IOIqtoYNIs = true;}
      if(ViVCzEeihd == SghPHQRJob){AGzLCMlTJn = true;}
      else if(SghPHQRJob == ViVCzEeihd){KVcTCwjzgi = true;}
      if(fwbVgnGhzG == WcABExfEYO){EPZyNduKfT = true;}
      else if(WcABExfEYO == fwbVgnGhzG){qenBaarJwf = true;}
      if(DcMXXoqJFE == sixKxFogHm){lJhQqFxXWN = true;}
      if(EJTabcPXGb == QtypKYhZRo){HbCMSgxdnI = true;}
      if(TIGTbtibTf == sTDcMdRqqR){EVJnVXjJBi = true;}
      while(sixKxFogHm == DcMXXoqJFE){WHzEYRHeca = true;}
      while(QtypKYhZRo == QtypKYhZRo){plkBHzKBlE = true;}
      while(sTDcMdRqqR == sTDcMdRqqR){QGXejcZHPS = true;}
      if(SZDeNjjXRB == true){SZDeNjjXRB = false;}
      if(bkBBKbdKqe == true){bkBBKbdKqe = false;}
      if(PFmiVZeTxS == true){PFmiVZeTxS = false;}
      if(nxopUppTca == true){nxopUppTca = false;}
      if(nKIPMIRCRj == true){nKIPMIRCRj = false;}
      if(AGzLCMlTJn == true){AGzLCMlTJn = false;}
      if(EPZyNduKfT == true){EPZyNduKfT = false;}
      if(lJhQqFxXWN == true){lJhQqFxXWN = false;}
      if(HbCMSgxdnI == true){HbCMSgxdnI = false;}
      if(EVJnVXjJBi == true){EVJnVXjJBi = false;}
      if(MGWxyqYiUw == true){MGWxyqYiUw = false;}
      if(OOxwfbNNfg == true){OOxwfbNNfg = false;}
      if(gQWWPPzstS == true){gQWWPPzstS = false;}
      if(VnVnAAFFNa == true){VnVnAAFFNa = false;}
      if(IOIqtoYNIs == true){IOIqtoYNIs = false;}
      if(KVcTCwjzgi == true){KVcTCwjzgi = false;}
      if(qenBaarJwf == true){qenBaarJwf = false;}
      if(WHzEYRHeca == true){WHzEYRHeca = false;}
      if(plkBHzKBlE == true){plkBHzKBlE = false;}
      if(QGXejcZHPS == true){QGXejcZHPS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLEMYFZYGG
{ 
  void cknQTLgxRA()
  { 
      bool CEqHDZDdaQ = false;
      bool dkKHuSjYtP = false;
      bool JBCBjxrgfW = false;
      bool VhwSlwPRYO = false;
      bool fmkxGIRfZx = false;
      bool cCIJHBCoXF = false;
      bool gVxDuwoqVy = false;
      bool DSAejVPFua = false;
      bool fMHhtSYmKk = false;
      bool tZtShJphBK = false;
      bool TZJbtKCdYl = false;
      bool kxtwZTOOJb = false;
      bool WCgkEcXgwa = false;
      bool fhDjHFCfni = false;
      bool PuNYAxfyrN = false;
      bool taXYmRsYWQ = false;
      bool lVgyFCsJnT = false;
      bool RiaZManHjG = false;
      bool xZnifFKdxp = false;
      bool MdIWxtOPSx = false;
      string hwWnECBuxI;
      string XFjalIqoxw;
      string BISMNSJxnJ;
      string CQQZleYqHS;
      string ciBZuaNNJD;
      string JGjzJZcKZl;
      string sEGmFGnKoG;
      string jAheTSGrQm;
      string EwmkzwgRPL;
      string BNQUZXbOUn;
      string lCYCSJXFep;
      string SksmgxRUmJ;
      string ZWucFVjNEw;
      string prXcACWkRp;
      string XblYrQUcmc;
      string GGaLOPHuxw;
      string YKAizaNQle;
      string ZfDxkxkVjo;
      string BGZbojRLNk;
      string tbnVQNbCYR;
      if(hwWnECBuxI == lCYCSJXFep){CEqHDZDdaQ = true;}
      else if(lCYCSJXFep == hwWnECBuxI){TZJbtKCdYl = true;}
      if(XFjalIqoxw == SksmgxRUmJ){dkKHuSjYtP = true;}
      else if(SksmgxRUmJ == XFjalIqoxw){kxtwZTOOJb = true;}
      if(BISMNSJxnJ == ZWucFVjNEw){JBCBjxrgfW = true;}
      else if(ZWucFVjNEw == BISMNSJxnJ){WCgkEcXgwa = true;}
      if(CQQZleYqHS == prXcACWkRp){VhwSlwPRYO = true;}
      else if(prXcACWkRp == CQQZleYqHS){fhDjHFCfni = true;}
      if(ciBZuaNNJD == XblYrQUcmc){fmkxGIRfZx = true;}
      else if(XblYrQUcmc == ciBZuaNNJD){PuNYAxfyrN = true;}
      if(JGjzJZcKZl == GGaLOPHuxw){cCIJHBCoXF = true;}
      else if(GGaLOPHuxw == JGjzJZcKZl){taXYmRsYWQ = true;}
      if(sEGmFGnKoG == YKAizaNQle){gVxDuwoqVy = true;}
      else if(YKAizaNQle == sEGmFGnKoG){lVgyFCsJnT = true;}
      if(jAheTSGrQm == ZfDxkxkVjo){DSAejVPFua = true;}
      if(EwmkzwgRPL == BGZbojRLNk){fMHhtSYmKk = true;}
      if(BNQUZXbOUn == tbnVQNbCYR){tZtShJphBK = true;}
      while(ZfDxkxkVjo == jAheTSGrQm){RiaZManHjG = true;}
      while(BGZbojRLNk == BGZbojRLNk){xZnifFKdxp = true;}
      while(tbnVQNbCYR == tbnVQNbCYR){MdIWxtOPSx = true;}
      if(CEqHDZDdaQ == true){CEqHDZDdaQ = false;}
      if(dkKHuSjYtP == true){dkKHuSjYtP = false;}
      if(JBCBjxrgfW == true){JBCBjxrgfW = false;}
      if(VhwSlwPRYO == true){VhwSlwPRYO = false;}
      if(fmkxGIRfZx == true){fmkxGIRfZx = false;}
      if(cCIJHBCoXF == true){cCIJHBCoXF = false;}
      if(gVxDuwoqVy == true){gVxDuwoqVy = false;}
      if(DSAejVPFua == true){DSAejVPFua = false;}
      if(fMHhtSYmKk == true){fMHhtSYmKk = false;}
      if(tZtShJphBK == true){tZtShJphBK = false;}
      if(TZJbtKCdYl == true){TZJbtKCdYl = false;}
      if(kxtwZTOOJb == true){kxtwZTOOJb = false;}
      if(WCgkEcXgwa == true){WCgkEcXgwa = false;}
      if(fhDjHFCfni == true){fhDjHFCfni = false;}
      if(PuNYAxfyrN == true){PuNYAxfyrN = false;}
      if(taXYmRsYWQ == true){taXYmRsYWQ = false;}
      if(lVgyFCsJnT == true){lVgyFCsJnT = false;}
      if(RiaZManHjG == true){RiaZManHjG = false;}
      if(xZnifFKdxp == true){xZnifFKdxp = false;}
      if(MdIWxtOPSx == true){MdIWxtOPSx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUTWKJSTHV
{ 
  void FpblgQCfWi()
  { 
      bool jMdgFYbICl = false;
      bool kKNdPMUosL = false;
      bool TabgiUAaPE = false;
      bool lNCGOTwwMC = false;
      bool PaugUFghSS = false;
      bool MAYIIJkxyk = false;
      bool XAryAWHGOw = false;
      bool QXbqwrfuLc = false;
      bool mSIwqkotxF = false;
      bool hyybdPhxfy = false;
      bool yZSVCnYgMP = false;
      bool dokUyEqwGO = false;
      bool hMIJNRZAMg = false;
      bool JhONeMAltD = false;
      bool MIghbsMcdY = false;
      bool XlpRPkRJHk = false;
      bool NYTfGuaXok = false;
      bool EEBDCYfagU = false;
      bool ExVmIWrxxt = false;
      bool upeIomnBbg = false;
      string SQaAesVpuu;
      string VqwwBMOlsV;
      string sYLbfGopgo;
      string lDDtNYkuAe;
      string TlVRGXepON;
      string uuJinsFyTX;
      string EeJGJSmBhb;
      string bSlNBGDtVI;
      string aybSspsUFU;
      string TlbbZocPHn;
      string jdIllbJugg;
      string pKcKwFCpMS;
      string YSuMIopJnM;
      string dmlhXxppfQ;
      string gxmXeIIQfU;
      string llDnORhudx;
      string lzHUDCYumy;
      string OMKulbfXhz;
      string gZdSaqixSG;
      string PtLiehoRUb;
      if(SQaAesVpuu == jdIllbJugg){jMdgFYbICl = true;}
      else if(jdIllbJugg == SQaAesVpuu){yZSVCnYgMP = true;}
      if(VqwwBMOlsV == pKcKwFCpMS){kKNdPMUosL = true;}
      else if(pKcKwFCpMS == VqwwBMOlsV){dokUyEqwGO = true;}
      if(sYLbfGopgo == YSuMIopJnM){TabgiUAaPE = true;}
      else if(YSuMIopJnM == sYLbfGopgo){hMIJNRZAMg = true;}
      if(lDDtNYkuAe == dmlhXxppfQ){lNCGOTwwMC = true;}
      else if(dmlhXxppfQ == lDDtNYkuAe){JhONeMAltD = true;}
      if(TlVRGXepON == gxmXeIIQfU){PaugUFghSS = true;}
      else if(gxmXeIIQfU == TlVRGXepON){MIghbsMcdY = true;}
      if(uuJinsFyTX == llDnORhudx){MAYIIJkxyk = true;}
      else if(llDnORhudx == uuJinsFyTX){XlpRPkRJHk = true;}
      if(EeJGJSmBhb == lzHUDCYumy){XAryAWHGOw = true;}
      else if(lzHUDCYumy == EeJGJSmBhb){NYTfGuaXok = true;}
      if(bSlNBGDtVI == OMKulbfXhz){QXbqwrfuLc = true;}
      if(aybSspsUFU == gZdSaqixSG){mSIwqkotxF = true;}
      if(TlbbZocPHn == PtLiehoRUb){hyybdPhxfy = true;}
      while(OMKulbfXhz == bSlNBGDtVI){EEBDCYfagU = true;}
      while(gZdSaqixSG == gZdSaqixSG){ExVmIWrxxt = true;}
      while(PtLiehoRUb == PtLiehoRUb){upeIomnBbg = true;}
      if(jMdgFYbICl == true){jMdgFYbICl = false;}
      if(kKNdPMUosL == true){kKNdPMUosL = false;}
      if(TabgiUAaPE == true){TabgiUAaPE = false;}
      if(lNCGOTwwMC == true){lNCGOTwwMC = false;}
      if(PaugUFghSS == true){PaugUFghSS = false;}
      if(MAYIIJkxyk == true){MAYIIJkxyk = false;}
      if(XAryAWHGOw == true){XAryAWHGOw = false;}
      if(QXbqwrfuLc == true){QXbqwrfuLc = false;}
      if(mSIwqkotxF == true){mSIwqkotxF = false;}
      if(hyybdPhxfy == true){hyybdPhxfy = false;}
      if(yZSVCnYgMP == true){yZSVCnYgMP = false;}
      if(dokUyEqwGO == true){dokUyEqwGO = false;}
      if(hMIJNRZAMg == true){hMIJNRZAMg = false;}
      if(JhONeMAltD == true){JhONeMAltD = false;}
      if(MIghbsMcdY == true){MIghbsMcdY = false;}
      if(XlpRPkRJHk == true){XlpRPkRJHk = false;}
      if(NYTfGuaXok == true){NYTfGuaXok = false;}
      if(EEBDCYfagU == true){EEBDCYfagU = false;}
      if(ExVmIWrxxt == true){ExVmIWrxxt = false;}
      if(upeIomnBbg == true){upeIomnBbg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRYGQWBUMH
{ 
  void xVAdqDKihJ()
  { 
      bool bokyMUjnmy = false;
      bool KftmGbYFuM = false;
      bool NqAWjpDtjl = false;
      bool druXyAamLP = false;
      bool tIKMIitiSL = false;
      bool EDZiukoOOW = false;
      bool QoEAURjVnG = false;
      bool BktfRFfmNA = false;
      bool wUbXhaSLbN = false;
      bool KLYnyEDKrp = false;
      bool zXtLKSItQp = false;
      bool EBANZwNfRs = false;
      bool zXtauoMFgM = false;
      bool BVuXBXZPNO = false;
      bool SYulIJLKNC = false;
      bool qWrzpadSQU = false;
      bool FCMEniFcMC = false;
      bool VxSDaacHSl = false;
      bool dCqdVddwgZ = false;
      bool tGzrIPLqyZ = false;
      string jtCyKcCEdf;
      string ihMQzmKeOy;
      string aqygoixxDY;
      string taITeBiQKP;
      string LwTrVLtKEs;
      string UMsxFruVJa;
      string eEAFkIYrly;
      string EsTzleXGLc;
      string nmrKDggLNm;
      string FMGjjHuNGM;
      string lBYGnastKa;
      string ToKflrLpBD;
      string aNdyrrmiPe;
      string iJAyqmNkVc;
      string mmAmSQCaxq;
      string uEMClXWZOw;
      string nKdeqKnMoz;
      string daUXPmNqfa;
      string oLkXjewxLS;
      string PnWZncJUuI;
      if(jtCyKcCEdf == lBYGnastKa){bokyMUjnmy = true;}
      else if(lBYGnastKa == jtCyKcCEdf){zXtLKSItQp = true;}
      if(ihMQzmKeOy == ToKflrLpBD){KftmGbYFuM = true;}
      else if(ToKflrLpBD == ihMQzmKeOy){EBANZwNfRs = true;}
      if(aqygoixxDY == aNdyrrmiPe){NqAWjpDtjl = true;}
      else if(aNdyrrmiPe == aqygoixxDY){zXtauoMFgM = true;}
      if(taITeBiQKP == iJAyqmNkVc){druXyAamLP = true;}
      else if(iJAyqmNkVc == taITeBiQKP){BVuXBXZPNO = true;}
      if(LwTrVLtKEs == mmAmSQCaxq){tIKMIitiSL = true;}
      else if(mmAmSQCaxq == LwTrVLtKEs){SYulIJLKNC = true;}
      if(UMsxFruVJa == uEMClXWZOw){EDZiukoOOW = true;}
      else if(uEMClXWZOw == UMsxFruVJa){qWrzpadSQU = true;}
      if(eEAFkIYrly == nKdeqKnMoz){QoEAURjVnG = true;}
      else if(nKdeqKnMoz == eEAFkIYrly){FCMEniFcMC = true;}
      if(EsTzleXGLc == daUXPmNqfa){BktfRFfmNA = true;}
      if(nmrKDggLNm == oLkXjewxLS){wUbXhaSLbN = true;}
      if(FMGjjHuNGM == PnWZncJUuI){KLYnyEDKrp = true;}
      while(daUXPmNqfa == EsTzleXGLc){VxSDaacHSl = true;}
      while(oLkXjewxLS == oLkXjewxLS){dCqdVddwgZ = true;}
      while(PnWZncJUuI == PnWZncJUuI){tGzrIPLqyZ = true;}
      if(bokyMUjnmy == true){bokyMUjnmy = false;}
      if(KftmGbYFuM == true){KftmGbYFuM = false;}
      if(NqAWjpDtjl == true){NqAWjpDtjl = false;}
      if(druXyAamLP == true){druXyAamLP = false;}
      if(tIKMIitiSL == true){tIKMIitiSL = false;}
      if(EDZiukoOOW == true){EDZiukoOOW = false;}
      if(QoEAURjVnG == true){QoEAURjVnG = false;}
      if(BktfRFfmNA == true){BktfRFfmNA = false;}
      if(wUbXhaSLbN == true){wUbXhaSLbN = false;}
      if(KLYnyEDKrp == true){KLYnyEDKrp = false;}
      if(zXtLKSItQp == true){zXtLKSItQp = false;}
      if(EBANZwNfRs == true){EBANZwNfRs = false;}
      if(zXtauoMFgM == true){zXtauoMFgM = false;}
      if(BVuXBXZPNO == true){BVuXBXZPNO = false;}
      if(SYulIJLKNC == true){SYulIJLKNC = false;}
      if(qWrzpadSQU == true){qWrzpadSQU = false;}
      if(FCMEniFcMC == true){FCMEniFcMC = false;}
      if(VxSDaacHSl == true){VxSDaacHSl = false;}
      if(dCqdVddwgZ == true){dCqdVddwgZ = false;}
      if(tGzrIPLqyZ == true){tGzrIPLqyZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LNGDWTJGUD
{ 
  void PzUmFtVXMl()
  { 
      bool xpPWjfBYuc = false;
      bool kMgnDDGXHN = false;
      bool DuPqtJrzpH = false;
      bool FNXTOTqtch = false;
      bool quViXFxgHp = false;
      bool TKpQGCaYcZ = false;
      bool nChmWWnMYj = false;
      bool LMuZVIZfSo = false;
      bool MLqAmuWHNM = false;
      bool rSRCtoMhMA = false;
      bool QjIXdHPQty = false;
      bool buFnMcKhAa = false;
      bool AgzLqsuref = false;
      bool uqTSXcDTVf = false;
      bool fFMOjxNcpR = false;
      bool eehkAjjwgk = false;
      bool LXlOCkamPi = false;
      bool YqLUutTjas = false;
      bool fRBNBQJiRn = false;
      bool sGmkTITyMz = false;
      string rknmHgpHra;
      string FFFQUfChnC;
      string DKWexdlJGN;
      string VEWQSefKGy;
      string MzeQaMrWNp;
      string ZzMVRhNIpd;
      string tgBdEAhnxo;
      string zrbpoDeGEj;
      string kPuQnWqBzk;
      string RWUbDfxALa;
      string dEYYphXWfN;
      string CHEFsekkph;
      string IgnMWbWzlJ;
      string GdtdFgpWZF;
      string zTUlhKRPiY;
      string tMJdRxPLBN;
      string LXkWHXMazL;
      string nNKkinMCeM;
      string KHQNOsTQLI;
      string RdVLtaiyeK;
      if(rknmHgpHra == dEYYphXWfN){xpPWjfBYuc = true;}
      else if(dEYYphXWfN == rknmHgpHra){QjIXdHPQty = true;}
      if(FFFQUfChnC == CHEFsekkph){kMgnDDGXHN = true;}
      else if(CHEFsekkph == FFFQUfChnC){buFnMcKhAa = true;}
      if(DKWexdlJGN == IgnMWbWzlJ){DuPqtJrzpH = true;}
      else if(IgnMWbWzlJ == DKWexdlJGN){AgzLqsuref = true;}
      if(VEWQSefKGy == GdtdFgpWZF){FNXTOTqtch = true;}
      else if(GdtdFgpWZF == VEWQSefKGy){uqTSXcDTVf = true;}
      if(MzeQaMrWNp == zTUlhKRPiY){quViXFxgHp = true;}
      else if(zTUlhKRPiY == MzeQaMrWNp){fFMOjxNcpR = true;}
      if(ZzMVRhNIpd == tMJdRxPLBN){TKpQGCaYcZ = true;}
      else if(tMJdRxPLBN == ZzMVRhNIpd){eehkAjjwgk = true;}
      if(tgBdEAhnxo == LXkWHXMazL){nChmWWnMYj = true;}
      else if(LXkWHXMazL == tgBdEAhnxo){LXlOCkamPi = true;}
      if(zrbpoDeGEj == nNKkinMCeM){LMuZVIZfSo = true;}
      if(kPuQnWqBzk == KHQNOsTQLI){MLqAmuWHNM = true;}
      if(RWUbDfxALa == RdVLtaiyeK){rSRCtoMhMA = true;}
      while(nNKkinMCeM == zrbpoDeGEj){YqLUutTjas = true;}
      while(KHQNOsTQLI == KHQNOsTQLI){fRBNBQJiRn = true;}
      while(RdVLtaiyeK == RdVLtaiyeK){sGmkTITyMz = true;}
      if(xpPWjfBYuc == true){xpPWjfBYuc = false;}
      if(kMgnDDGXHN == true){kMgnDDGXHN = false;}
      if(DuPqtJrzpH == true){DuPqtJrzpH = false;}
      if(FNXTOTqtch == true){FNXTOTqtch = false;}
      if(quViXFxgHp == true){quViXFxgHp = false;}
      if(TKpQGCaYcZ == true){TKpQGCaYcZ = false;}
      if(nChmWWnMYj == true){nChmWWnMYj = false;}
      if(LMuZVIZfSo == true){LMuZVIZfSo = false;}
      if(MLqAmuWHNM == true){MLqAmuWHNM = false;}
      if(rSRCtoMhMA == true){rSRCtoMhMA = false;}
      if(QjIXdHPQty == true){QjIXdHPQty = false;}
      if(buFnMcKhAa == true){buFnMcKhAa = false;}
      if(AgzLqsuref == true){AgzLqsuref = false;}
      if(uqTSXcDTVf == true){uqTSXcDTVf = false;}
      if(fFMOjxNcpR == true){fFMOjxNcpR = false;}
      if(eehkAjjwgk == true){eehkAjjwgk = false;}
      if(LXlOCkamPi == true){LXlOCkamPi = false;}
      if(YqLUutTjas == true){YqLUutTjas = false;}
      if(fRBNBQJiRn == true){fRBNBQJiRn = false;}
      if(sGmkTITyMz == true){sGmkTITyMz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZYLQTMPDS
{ 
  void MxzOUjVFaT()
  { 
      bool PTwwPzzzOt = false;
      bool WkrHXNlbWT = false;
      bool CALEXOshGq = false;
      bool NClJcMBBWl = false;
      bool dkOFPlfZmc = false;
      bool tmDgHOIrYA = false;
      bool FRsWfUyidL = false;
      bool LjEjoQkFok = false;
      bool iTtcxazECN = false;
      bool EJcVfMrrYu = false;
      bool nxubQKhSqp = false;
      bool cCCnRlWPZF = false;
      bool VtfPHBHhDc = false;
      bool YsgtxkXSMl = false;
      bool rfMMjBGnDt = false;
      bool pbRTZsQeUP = false;
      bool DzPOQjVIqg = false;
      bool NDDmMogTfF = false;
      bool tSdJmwaMTD = false;
      bool TsywirQyuA = false;
      string LoxtbxLDIV;
      string BZaiGOCFfB;
      string RTBQScNjPI;
      string oLNSGdrugL;
      string IqsISVUDPk;
      string HyaMwrnfby;
      string ibnAfpLIcc;
      string WHXUraZryw;
      string HKTdBqjBVO;
      string oLThcgDsbb;
      string JLZmOzZGTV;
      string SugeqXHJyo;
      string FKmOmKmpqL;
      string XfQVlwjgPC;
      string QchzwteoqE;
      string ZsumWzYLAD;
      string LjOIyleKrt;
      string nZswXbbmSr;
      string fyymldjdzm;
      string WYgLpfOZBJ;
      if(LoxtbxLDIV == JLZmOzZGTV){PTwwPzzzOt = true;}
      else if(JLZmOzZGTV == LoxtbxLDIV){nxubQKhSqp = true;}
      if(BZaiGOCFfB == SugeqXHJyo){WkrHXNlbWT = true;}
      else if(SugeqXHJyo == BZaiGOCFfB){cCCnRlWPZF = true;}
      if(RTBQScNjPI == FKmOmKmpqL){CALEXOshGq = true;}
      else if(FKmOmKmpqL == RTBQScNjPI){VtfPHBHhDc = true;}
      if(oLNSGdrugL == XfQVlwjgPC){NClJcMBBWl = true;}
      else if(XfQVlwjgPC == oLNSGdrugL){YsgtxkXSMl = true;}
      if(IqsISVUDPk == QchzwteoqE){dkOFPlfZmc = true;}
      else if(QchzwteoqE == IqsISVUDPk){rfMMjBGnDt = true;}
      if(HyaMwrnfby == ZsumWzYLAD){tmDgHOIrYA = true;}
      else if(ZsumWzYLAD == HyaMwrnfby){pbRTZsQeUP = true;}
      if(ibnAfpLIcc == LjOIyleKrt){FRsWfUyidL = true;}
      else if(LjOIyleKrt == ibnAfpLIcc){DzPOQjVIqg = true;}
      if(WHXUraZryw == nZswXbbmSr){LjEjoQkFok = true;}
      if(HKTdBqjBVO == fyymldjdzm){iTtcxazECN = true;}
      if(oLThcgDsbb == WYgLpfOZBJ){EJcVfMrrYu = true;}
      while(nZswXbbmSr == WHXUraZryw){NDDmMogTfF = true;}
      while(fyymldjdzm == fyymldjdzm){tSdJmwaMTD = true;}
      while(WYgLpfOZBJ == WYgLpfOZBJ){TsywirQyuA = true;}
      if(PTwwPzzzOt == true){PTwwPzzzOt = false;}
      if(WkrHXNlbWT == true){WkrHXNlbWT = false;}
      if(CALEXOshGq == true){CALEXOshGq = false;}
      if(NClJcMBBWl == true){NClJcMBBWl = false;}
      if(dkOFPlfZmc == true){dkOFPlfZmc = false;}
      if(tmDgHOIrYA == true){tmDgHOIrYA = false;}
      if(FRsWfUyidL == true){FRsWfUyidL = false;}
      if(LjEjoQkFok == true){LjEjoQkFok = false;}
      if(iTtcxazECN == true){iTtcxazECN = false;}
      if(EJcVfMrrYu == true){EJcVfMrrYu = false;}
      if(nxubQKhSqp == true){nxubQKhSqp = false;}
      if(cCCnRlWPZF == true){cCCnRlWPZF = false;}
      if(VtfPHBHhDc == true){VtfPHBHhDc = false;}
      if(YsgtxkXSMl == true){YsgtxkXSMl = false;}
      if(rfMMjBGnDt == true){rfMMjBGnDt = false;}
      if(pbRTZsQeUP == true){pbRTZsQeUP = false;}
      if(DzPOQjVIqg == true){DzPOQjVIqg = false;}
      if(NDDmMogTfF == true){NDDmMogTfF = false;}
      if(tSdJmwaMTD == true){tSdJmwaMTD = false;}
      if(TsywirQyuA == true){TsywirQyuA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXDAPXCADS
{ 
  void AbsqDwIrZU()
  { 
      bool rpmTIPiESO = false;
      bool kgzrzKlJCO = false;
      bool qByQYuHjQS = false;
      bool ICkLzpVdVi = false;
      bool UtksjOaYKQ = false;
      bool ztsTdpqWtN = false;
      bool HzmzGhumsJ = false;
      bool oHnStwQFfJ = false;
      bool ThYATNIQhI = false;
      bool yzjHaVGklC = false;
      bool SmfBbqGaZg = false;
      bool ZlpjsZZmfs = false;
      bool YdFjKpXfrX = false;
      bool peSdqgCXYb = false;
      bool HhqAiMIzOB = false;
      bool wSFscngupk = false;
      bool TZhCqtSMsM = false;
      bool WBODkqmFBy = false;
      bool hXRpbWZZBC = false;
      bool zHhmHgznJn = false;
      string mtpMPqfIkf;
      string fDXPFLiuPW;
      string qNojoXoaZx;
      string LpYxYjtlAE;
      string UxbQUHzNxZ;
      string ySEouZEGXr;
      string BFinTodZpV;
      string QwuKCtkXPh;
      string XbdzysliCz;
      string enOIDPNnxe;
      string cZWaIBWtmA;
      string nfqpTZajoZ;
      string DtWqpchmGl;
      string gxajEyFCpw;
      string VqwCLyxYoc;
      string ncyWbiCekf;
      string TjmASpFGkU;
      string UYtsEMyUfr;
      string fIydyEzDIU;
      string wZRKbkDuiU;
      if(mtpMPqfIkf == cZWaIBWtmA){rpmTIPiESO = true;}
      else if(cZWaIBWtmA == mtpMPqfIkf){SmfBbqGaZg = true;}
      if(fDXPFLiuPW == nfqpTZajoZ){kgzrzKlJCO = true;}
      else if(nfqpTZajoZ == fDXPFLiuPW){ZlpjsZZmfs = true;}
      if(qNojoXoaZx == DtWqpchmGl){qByQYuHjQS = true;}
      else if(DtWqpchmGl == qNojoXoaZx){YdFjKpXfrX = true;}
      if(LpYxYjtlAE == gxajEyFCpw){ICkLzpVdVi = true;}
      else if(gxajEyFCpw == LpYxYjtlAE){peSdqgCXYb = true;}
      if(UxbQUHzNxZ == VqwCLyxYoc){UtksjOaYKQ = true;}
      else if(VqwCLyxYoc == UxbQUHzNxZ){HhqAiMIzOB = true;}
      if(ySEouZEGXr == ncyWbiCekf){ztsTdpqWtN = true;}
      else if(ncyWbiCekf == ySEouZEGXr){wSFscngupk = true;}
      if(BFinTodZpV == TjmASpFGkU){HzmzGhumsJ = true;}
      else if(TjmASpFGkU == BFinTodZpV){TZhCqtSMsM = true;}
      if(QwuKCtkXPh == UYtsEMyUfr){oHnStwQFfJ = true;}
      if(XbdzysliCz == fIydyEzDIU){ThYATNIQhI = true;}
      if(enOIDPNnxe == wZRKbkDuiU){yzjHaVGklC = true;}
      while(UYtsEMyUfr == QwuKCtkXPh){WBODkqmFBy = true;}
      while(fIydyEzDIU == fIydyEzDIU){hXRpbWZZBC = true;}
      while(wZRKbkDuiU == wZRKbkDuiU){zHhmHgznJn = true;}
      if(rpmTIPiESO == true){rpmTIPiESO = false;}
      if(kgzrzKlJCO == true){kgzrzKlJCO = false;}
      if(qByQYuHjQS == true){qByQYuHjQS = false;}
      if(ICkLzpVdVi == true){ICkLzpVdVi = false;}
      if(UtksjOaYKQ == true){UtksjOaYKQ = false;}
      if(ztsTdpqWtN == true){ztsTdpqWtN = false;}
      if(HzmzGhumsJ == true){HzmzGhumsJ = false;}
      if(oHnStwQFfJ == true){oHnStwQFfJ = false;}
      if(ThYATNIQhI == true){ThYATNIQhI = false;}
      if(yzjHaVGklC == true){yzjHaVGklC = false;}
      if(SmfBbqGaZg == true){SmfBbqGaZg = false;}
      if(ZlpjsZZmfs == true){ZlpjsZZmfs = false;}
      if(YdFjKpXfrX == true){YdFjKpXfrX = false;}
      if(peSdqgCXYb == true){peSdqgCXYb = false;}
      if(HhqAiMIzOB == true){HhqAiMIzOB = false;}
      if(wSFscngupk == true){wSFscngupk = false;}
      if(TZhCqtSMsM == true){TZhCqtSMsM = false;}
      if(WBODkqmFBy == true){WBODkqmFBy = false;}
      if(hXRpbWZZBC == true){hXRpbWZZBC = false;}
      if(zHhmHgznJn == true){zHhmHgznJn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXJOYBGDDR
{ 
  void HVCocyblEQ()
  { 
      bool cmwhOayelC = false;
      bool NxueBtchst = false;
      bool RhcjqBLlat = false;
      bool dLVqRYRDHV = false;
      bool wpuoKCmgzf = false;
      bool qTUUntJMqM = false;
      bool OLDrXBaEMc = false;
      bool bZaWyamnYn = false;
      bool OemtCKqBDW = false;
      bool PFLtGjmCQJ = false;
      bool bhTWEQsxVM = false;
      bool HVmCyjYIpN = false;
      bool JZBpNWNgQO = false;
      bool mjWPMfKPpk = false;
      bool QtepOsSJuW = false;
      bool LeMDzBgdJg = false;
      bool CMfHYWzWoR = false;
      bool YIREwPtKaT = false;
      bool EEktCIXSQK = false;
      bool zgGIiENXQq = false;
      string oWuBYkAxgw;
      string MsXNIdQnNT;
      string AgnwFrPsBj;
      string ppcKpaEVeg;
      string PhNFuekFtG;
      string XhHolIhyuf;
      string VHuwGWPNXg;
      string ZuIgDRSiAa;
      string GJytLHhnXh;
      string sFayLIlQzY;
      string OXhNgcYakT;
      string ozxUZLIBky;
      string oboonTUKVu;
      string eBibLhakNi;
      string iHCDrsIFYz;
      string zkfBjmirYM;
      string IOEonmPVIq;
      string jXmBOgYkwt;
      string LOkVwtVhrY;
      string ziLAZUCNOF;
      if(oWuBYkAxgw == OXhNgcYakT){cmwhOayelC = true;}
      else if(OXhNgcYakT == oWuBYkAxgw){bhTWEQsxVM = true;}
      if(MsXNIdQnNT == ozxUZLIBky){NxueBtchst = true;}
      else if(ozxUZLIBky == MsXNIdQnNT){HVmCyjYIpN = true;}
      if(AgnwFrPsBj == oboonTUKVu){RhcjqBLlat = true;}
      else if(oboonTUKVu == AgnwFrPsBj){JZBpNWNgQO = true;}
      if(ppcKpaEVeg == eBibLhakNi){dLVqRYRDHV = true;}
      else if(eBibLhakNi == ppcKpaEVeg){mjWPMfKPpk = true;}
      if(PhNFuekFtG == iHCDrsIFYz){wpuoKCmgzf = true;}
      else if(iHCDrsIFYz == PhNFuekFtG){QtepOsSJuW = true;}
      if(XhHolIhyuf == zkfBjmirYM){qTUUntJMqM = true;}
      else if(zkfBjmirYM == XhHolIhyuf){LeMDzBgdJg = true;}
      if(VHuwGWPNXg == IOEonmPVIq){OLDrXBaEMc = true;}
      else if(IOEonmPVIq == VHuwGWPNXg){CMfHYWzWoR = true;}
      if(ZuIgDRSiAa == jXmBOgYkwt){bZaWyamnYn = true;}
      if(GJytLHhnXh == LOkVwtVhrY){OemtCKqBDW = true;}
      if(sFayLIlQzY == ziLAZUCNOF){PFLtGjmCQJ = true;}
      while(jXmBOgYkwt == ZuIgDRSiAa){YIREwPtKaT = true;}
      while(LOkVwtVhrY == LOkVwtVhrY){EEktCIXSQK = true;}
      while(ziLAZUCNOF == ziLAZUCNOF){zgGIiENXQq = true;}
      if(cmwhOayelC == true){cmwhOayelC = false;}
      if(NxueBtchst == true){NxueBtchst = false;}
      if(RhcjqBLlat == true){RhcjqBLlat = false;}
      if(dLVqRYRDHV == true){dLVqRYRDHV = false;}
      if(wpuoKCmgzf == true){wpuoKCmgzf = false;}
      if(qTUUntJMqM == true){qTUUntJMqM = false;}
      if(OLDrXBaEMc == true){OLDrXBaEMc = false;}
      if(bZaWyamnYn == true){bZaWyamnYn = false;}
      if(OemtCKqBDW == true){OemtCKqBDW = false;}
      if(PFLtGjmCQJ == true){PFLtGjmCQJ = false;}
      if(bhTWEQsxVM == true){bhTWEQsxVM = false;}
      if(HVmCyjYIpN == true){HVmCyjYIpN = false;}
      if(JZBpNWNgQO == true){JZBpNWNgQO = false;}
      if(mjWPMfKPpk == true){mjWPMfKPpk = false;}
      if(QtepOsSJuW == true){QtepOsSJuW = false;}
      if(LeMDzBgdJg == true){LeMDzBgdJg = false;}
      if(CMfHYWzWoR == true){CMfHYWzWoR = false;}
      if(YIREwPtKaT == true){YIREwPtKaT = false;}
      if(EEktCIXSQK == true){EEktCIXSQK = false;}
      if(zgGIiENXQq == true){zgGIiENXQq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGXSAAGFID
{ 
  void IeQKzBJVLR()
  { 
      bool XaSdqAIElh = false;
      bool nqeVCzOOEs = false;
      bool wUCRlJaWJB = false;
      bool apaIHPxzXf = false;
      bool xDThgnWzyj = false;
      bool RDTalDYBrh = false;
      bool YktjHyQVOl = false;
      bool COpXurAUjy = false;
      bool laYZiWWzWD = false;
      bool quHpGLJiai = false;
      bool WBkLhDNufs = false;
      bool CDRtuxMUBj = false;
      bool bQzKtGHzRj = false;
      bool iRsBakpMre = false;
      bool JaTcBmdNuI = false;
      bool zogpGFBZRb = false;
      bool uNduKjKQSK = false;
      bool HzbVZAxWJG = false;
      bool btDIjskCtU = false;
      bool iPuQjuxXRQ = false;
      string bURdAJgpAD;
      string VZzgXNWlwk;
      string YUVBSuBJyS;
      string HpfcEwVeis;
      string ooXVuTZcGX;
      string eSyJVGzQLE;
      string HXqgufsWba;
      string qqCDujwzGz;
      string UYCZnoqWGx;
      string xFTdkRxqaO;
      string ZDAefnPuNl;
      string KzKMiiURsG;
      string nWPedlXXRc;
      string lFYqYRXXtz;
      string YuIUmytGuC;
      string xfxTaCmVBs;
      string QrdjzEZSmQ;
      string LxWshrOuqe;
      string qQcPfGIFQV;
      string eBVAigRXUi;
      if(bURdAJgpAD == ZDAefnPuNl){XaSdqAIElh = true;}
      else if(ZDAefnPuNl == bURdAJgpAD){WBkLhDNufs = true;}
      if(VZzgXNWlwk == KzKMiiURsG){nqeVCzOOEs = true;}
      else if(KzKMiiURsG == VZzgXNWlwk){CDRtuxMUBj = true;}
      if(YUVBSuBJyS == nWPedlXXRc){wUCRlJaWJB = true;}
      else if(nWPedlXXRc == YUVBSuBJyS){bQzKtGHzRj = true;}
      if(HpfcEwVeis == lFYqYRXXtz){apaIHPxzXf = true;}
      else if(lFYqYRXXtz == HpfcEwVeis){iRsBakpMre = true;}
      if(ooXVuTZcGX == YuIUmytGuC){xDThgnWzyj = true;}
      else if(YuIUmytGuC == ooXVuTZcGX){JaTcBmdNuI = true;}
      if(eSyJVGzQLE == xfxTaCmVBs){RDTalDYBrh = true;}
      else if(xfxTaCmVBs == eSyJVGzQLE){zogpGFBZRb = true;}
      if(HXqgufsWba == QrdjzEZSmQ){YktjHyQVOl = true;}
      else if(QrdjzEZSmQ == HXqgufsWba){uNduKjKQSK = true;}
      if(qqCDujwzGz == LxWshrOuqe){COpXurAUjy = true;}
      if(UYCZnoqWGx == qQcPfGIFQV){laYZiWWzWD = true;}
      if(xFTdkRxqaO == eBVAigRXUi){quHpGLJiai = true;}
      while(LxWshrOuqe == qqCDujwzGz){HzbVZAxWJG = true;}
      while(qQcPfGIFQV == qQcPfGIFQV){btDIjskCtU = true;}
      while(eBVAigRXUi == eBVAigRXUi){iPuQjuxXRQ = true;}
      if(XaSdqAIElh == true){XaSdqAIElh = false;}
      if(nqeVCzOOEs == true){nqeVCzOOEs = false;}
      if(wUCRlJaWJB == true){wUCRlJaWJB = false;}
      if(apaIHPxzXf == true){apaIHPxzXf = false;}
      if(xDThgnWzyj == true){xDThgnWzyj = false;}
      if(RDTalDYBrh == true){RDTalDYBrh = false;}
      if(YktjHyQVOl == true){YktjHyQVOl = false;}
      if(COpXurAUjy == true){COpXurAUjy = false;}
      if(laYZiWWzWD == true){laYZiWWzWD = false;}
      if(quHpGLJiai == true){quHpGLJiai = false;}
      if(WBkLhDNufs == true){WBkLhDNufs = false;}
      if(CDRtuxMUBj == true){CDRtuxMUBj = false;}
      if(bQzKtGHzRj == true){bQzKtGHzRj = false;}
      if(iRsBakpMre == true){iRsBakpMre = false;}
      if(JaTcBmdNuI == true){JaTcBmdNuI = false;}
      if(zogpGFBZRb == true){zogpGFBZRb = false;}
      if(uNduKjKQSK == true){uNduKjKQSK = false;}
      if(HzbVZAxWJG == true){HzbVZAxWJG = false;}
      if(btDIjskCtU == true){btDIjskCtU = false;}
      if(iPuQjuxXRQ == true){iPuQjuxXRQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class REBAALILPU
{ 
  void ZhxDTLwABa()
  { 
      bool NSlVCfCgOP = false;
      bool jRChSacTDQ = false;
      bool ZWQfrFtwbh = false;
      bool DkiZMgGFNI = false;
      bool BzxmTTQOwR = false;
      bool zVUQNqCFcx = false;
      bool kGFgMzhcVk = false;
      bool TWFtPZYcMX = false;
      bool ofzKhgPSMV = false;
      bool eBbQXutQZT = false;
      bool lnsLxcQZAm = false;
      bool RYrFIEGtzf = false;
      bool jOPzGStnWT = false;
      bool fICslAmnME = false;
      bool PoRYEFIWIS = false;
      bool ozRtjWXsEd = false;
      bool ibDfHIWzTH = false;
      bool RRhtPtxpuB = false;
      bool KWfDefqIJO = false;
      bool btihVnlkRu = false;
      string hsDeEyxmaa;
      string hDJkgpYykq;
      string RaVkfgdLCz;
      string VLIBqpjEWG;
      string IrKUyOKSXM;
      string DIHmLGWSzW;
      string UljbEWtIsq;
      string FUbeiZQBmR;
      string WKmpuNDUoj;
      string SREzlVHhPb;
      string TCZgHifcEl;
      string oVehzJytfq;
      string SZSIXmPbsM;
      string RilLxUkGiL;
      string gZQCtxmWAb;
      string XNBYIsiQIT;
      string TEjrUGiTjd;
      string YrLUJrJQNa;
      string AsbQnDgMCD;
      string lTxOrboXgm;
      if(hsDeEyxmaa == TCZgHifcEl){NSlVCfCgOP = true;}
      else if(TCZgHifcEl == hsDeEyxmaa){lnsLxcQZAm = true;}
      if(hDJkgpYykq == oVehzJytfq){jRChSacTDQ = true;}
      else if(oVehzJytfq == hDJkgpYykq){RYrFIEGtzf = true;}
      if(RaVkfgdLCz == SZSIXmPbsM){ZWQfrFtwbh = true;}
      else if(SZSIXmPbsM == RaVkfgdLCz){jOPzGStnWT = true;}
      if(VLIBqpjEWG == RilLxUkGiL){DkiZMgGFNI = true;}
      else if(RilLxUkGiL == VLIBqpjEWG){fICslAmnME = true;}
      if(IrKUyOKSXM == gZQCtxmWAb){BzxmTTQOwR = true;}
      else if(gZQCtxmWAb == IrKUyOKSXM){PoRYEFIWIS = true;}
      if(DIHmLGWSzW == XNBYIsiQIT){zVUQNqCFcx = true;}
      else if(XNBYIsiQIT == DIHmLGWSzW){ozRtjWXsEd = true;}
      if(UljbEWtIsq == TEjrUGiTjd){kGFgMzhcVk = true;}
      else if(TEjrUGiTjd == UljbEWtIsq){ibDfHIWzTH = true;}
      if(FUbeiZQBmR == YrLUJrJQNa){TWFtPZYcMX = true;}
      if(WKmpuNDUoj == AsbQnDgMCD){ofzKhgPSMV = true;}
      if(SREzlVHhPb == lTxOrboXgm){eBbQXutQZT = true;}
      while(YrLUJrJQNa == FUbeiZQBmR){RRhtPtxpuB = true;}
      while(AsbQnDgMCD == AsbQnDgMCD){KWfDefqIJO = true;}
      while(lTxOrboXgm == lTxOrboXgm){btihVnlkRu = true;}
      if(NSlVCfCgOP == true){NSlVCfCgOP = false;}
      if(jRChSacTDQ == true){jRChSacTDQ = false;}
      if(ZWQfrFtwbh == true){ZWQfrFtwbh = false;}
      if(DkiZMgGFNI == true){DkiZMgGFNI = false;}
      if(BzxmTTQOwR == true){BzxmTTQOwR = false;}
      if(zVUQNqCFcx == true){zVUQNqCFcx = false;}
      if(kGFgMzhcVk == true){kGFgMzhcVk = false;}
      if(TWFtPZYcMX == true){TWFtPZYcMX = false;}
      if(ofzKhgPSMV == true){ofzKhgPSMV = false;}
      if(eBbQXutQZT == true){eBbQXutQZT = false;}
      if(lnsLxcQZAm == true){lnsLxcQZAm = false;}
      if(RYrFIEGtzf == true){RYrFIEGtzf = false;}
      if(jOPzGStnWT == true){jOPzGStnWT = false;}
      if(fICslAmnME == true){fICslAmnME = false;}
      if(PoRYEFIWIS == true){PoRYEFIWIS = false;}
      if(ozRtjWXsEd == true){ozRtjWXsEd = false;}
      if(ibDfHIWzTH == true){ibDfHIWzTH = false;}
      if(RRhtPtxpuB == true){RRhtPtxpuB = false;}
      if(KWfDefqIJO == true){KWfDefqIJO = false;}
      if(btihVnlkRu == true){btihVnlkRu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXZUJWDIDU
{ 
  void bDexROZmwT()
  { 
      bool DbDboFprUb = false;
      bool hsnzZuuBqe = false;
      bool hDGHMYMXhE = false;
      bool wPPccTFEVB = false;
      bool PxFbcTQQKZ = false;
      bool lMfEMAVuOQ = false;
      bool rSJPeRdLWF = false;
      bool opfpPkxder = false;
      bool HwMHSijLPb = false;
      bool yJpEIxmowK = false;
      bool pFsFjugoob = false;
      bool CqQVIwFBxw = false;
      bool hSutHfAagR = false;
      bool xIhTBBCHXW = false;
      bool CtVnZGrTwM = false;
      bool qlrAbXKzxE = false;
      bool uFHWetJwTG = false;
      bool sydZsnwGUA = false;
      bool mfeUaKQgqd = false;
      bool qDJSbxlzJf = false;
      string flCCRBMtUH;
      string FCBJlPUAVZ;
      string wPuoxPmsZk;
      string tBoTrgyXjc;
      string bfGOaouTAS;
      string dajiGQpNFB;
      string OTTiNDNhRE;
      string RwQsxQIgNH;
      string USrGGSRGMa;
      string pkShOILXAX;
      string bNCuBhJqlp;
      string IJzxguaNbt;
      string kHUpOgdhdn;
      string EjfpeGQxFY;
      string IaUVSgkUBT;
      string hyuGlUrLgU;
      string DbMxlXcJRZ;
      string dcHDkKmzXg;
      string uIfKGGoZDK;
      string NFQjUgOWju;
      if(flCCRBMtUH == bNCuBhJqlp){DbDboFprUb = true;}
      else if(bNCuBhJqlp == flCCRBMtUH){pFsFjugoob = true;}
      if(FCBJlPUAVZ == IJzxguaNbt){hsnzZuuBqe = true;}
      else if(IJzxguaNbt == FCBJlPUAVZ){CqQVIwFBxw = true;}
      if(wPuoxPmsZk == kHUpOgdhdn){hDGHMYMXhE = true;}
      else if(kHUpOgdhdn == wPuoxPmsZk){hSutHfAagR = true;}
      if(tBoTrgyXjc == EjfpeGQxFY){wPPccTFEVB = true;}
      else if(EjfpeGQxFY == tBoTrgyXjc){xIhTBBCHXW = true;}
      if(bfGOaouTAS == IaUVSgkUBT){PxFbcTQQKZ = true;}
      else if(IaUVSgkUBT == bfGOaouTAS){CtVnZGrTwM = true;}
      if(dajiGQpNFB == hyuGlUrLgU){lMfEMAVuOQ = true;}
      else if(hyuGlUrLgU == dajiGQpNFB){qlrAbXKzxE = true;}
      if(OTTiNDNhRE == DbMxlXcJRZ){rSJPeRdLWF = true;}
      else if(DbMxlXcJRZ == OTTiNDNhRE){uFHWetJwTG = true;}
      if(RwQsxQIgNH == dcHDkKmzXg){opfpPkxder = true;}
      if(USrGGSRGMa == uIfKGGoZDK){HwMHSijLPb = true;}
      if(pkShOILXAX == NFQjUgOWju){yJpEIxmowK = true;}
      while(dcHDkKmzXg == RwQsxQIgNH){sydZsnwGUA = true;}
      while(uIfKGGoZDK == uIfKGGoZDK){mfeUaKQgqd = true;}
      while(NFQjUgOWju == NFQjUgOWju){qDJSbxlzJf = true;}
      if(DbDboFprUb == true){DbDboFprUb = false;}
      if(hsnzZuuBqe == true){hsnzZuuBqe = false;}
      if(hDGHMYMXhE == true){hDGHMYMXhE = false;}
      if(wPPccTFEVB == true){wPPccTFEVB = false;}
      if(PxFbcTQQKZ == true){PxFbcTQQKZ = false;}
      if(lMfEMAVuOQ == true){lMfEMAVuOQ = false;}
      if(rSJPeRdLWF == true){rSJPeRdLWF = false;}
      if(opfpPkxder == true){opfpPkxder = false;}
      if(HwMHSijLPb == true){HwMHSijLPb = false;}
      if(yJpEIxmowK == true){yJpEIxmowK = false;}
      if(pFsFjugoob == true){pFsFjugoob = false;}
      if(CqQVIwFBxw == true){CqQVIwFBxw = false;}
      if(hSutHfAagR == true){hSutHfAagR = false;}
      if(xIhTBBCHXW == true){xIhTBBCHXW = false;}
      if(CtVnZGrTwM == true){CtVnZGrTwM = false;}
      if(qlrAbXKzxE == true){qlrAbXKzxE = false;}
      if(uFHWetJwTG == true){uFHWetJwTG = false;}
      if(sydZsnwGUA == true){sydZsnwGUA = false;}
      if(mfeUaKQgqd == true){mfeUaKQgqd = false;}
      if(qDJSbxlzJf == true){qDJSbxlzJf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOZNWBUJZU
{ 
  void OoSaYLiGPA()
  { 
      bool FhhFMdadcP = false;
      bool dJLGNmTgJg = false;
      bool BpEWhTFKeJ = false;
      bool mFGtDQMDBM = false;
      bool JLpUKjRewx = false;
      bool ptcAAPdKWr = false;
      bool XQyScYCRDw = false;
      bool aQfxWoAjLy = false;
      bool BaNhTrbFtm = false;
      bool mBfIosMWql = false;
      bool gAaAVZNfdK = false;
      bool PszYqxCQyk = false;
      bool wxWPJZjXIc = false;
      bool ccrZQAzNLt = false;
      bool dubiWsCGQq = false;
      bool quXGojcLqw = false;
      bool opXBhmAZHp = false;
      bool ynFEGAUnrP = false;
      bool XcHQkgFljg = false;
      bool WnWOFnXZAj = false;
      string CQCsBKastT;
      string xWFOmOQnfb;
      string HPbSDDpptU;
      string KXnSGbNJyO;
      string AmCKnlYFzl;
      string eHjnTmojpy;
      string UkzYIYhmIK;
      string BHpRbUMQeQ;
      string djpHpDnAyS;
      string mcSAtPmcBO;
      string ElxnkWRRMz;
      string aXFYTjtqiF;
      string jgnoXXooWL;
      string gjPPMrlCWS;
      string lVnzrOXtgJ;
      string VwtwdWyIPM;
      string hbtARqIoLb;
      string xqUPTOsnwJ;
      string ztINpkoSko;
      string sdlJkJbmgB;
      if(CQCsBKastT == ElxnkWRRMz){FhhFMdadcP = true;}
      else if(ElxnkWRRMz == CQCsBKastT){gAaAVZNfdK = true;}
      if(xWFOmOQnfb == aXFYTjtqiF){dJLGNmTgJg = true;}
      else if(aXFYTjtqiF == xWFOmOQnfb){PszYqxCQyk = true;}
      if(HPbSDDpptU == jgnoXXooWL){BpEWhTFKeJ = true;}
      else if(jgnoXXooWL == HPbSDDpptU){wxWPJZjXIc = true;}
      if(KXnSGbNJyO == gjPPMrlCWS){mFGtDQMDBM = true;}
      else if(gjPPMrlCWS == KXnSGbNJyO){ccrZQAzNLt = true;}
      if(AmCKnlYFzl == lVnzrOXtgJ){JLpUKjRewx = true;}
      else if(lVnzrOXtgJ == AmCKnlYFzl){dubiWsCGQq = true;}
      if(eHjnTmojpy == VwtwdWyIPM){ptcAAPdKWr = true;}
      else if(VwtwdWyIPM == eHjnTmojpy){quXGojcLqw = true;}
      if(UkzYIYhmIK == hbtARqIoLb){XQyScYCRDw = true;}
      else if(hbtARqIoLb == UkzYIYhmIK){opXBhmAZHp = true;}
      if(BHpRbUMQeQ == xqUPTOsnwJ){aQfxWoAjLy = true;}
      if(djpHpDnAyS == ztINpkoSko){BaNhTrbFtm = true;}
      if(mcSAtPmcBO == sdlJkJbmgB){mBfIosMWql = true;}
      while(xqUPTOsnwJ == BHpRbUMQeQ){ynFEGAUnrP = true;}
      while(ztINpkoSko == ztINpkoSko){XcHQkgFljg = true;}
      while(sdlJkJbmgB == sdlJkJbmgB){WnWOFnXZAj = true;}
      if(FhhFMdadcP == true){FhhFMdadcP = false;}
      if(dJLGNmTgJg == true){dJLGNmTgJg = false;}
      if(BpEWhTFKeJ == true){BpEWhTFKeJ = false;}
      if(mFGtDQMDBM == true){mFGtDQMDBM = false;}
      if(JLpUKjRewx == true){JLpUKjRewx = false;}
      if(ptcAAPdKWr == true){ptcAAPdKWr = false;}
      if(XQyScYCRDw == true){XQyScYCRDw = false;}
      if(aQfxWoAjLy == true){aQfxWoAjLy = false;}
      if(BaNhTrbFtm == true){BaNhTrbFtm = false;}
      if(mBfIosMWql == true){mBfIosMWql = false;}
      if(gAaAVZNfdK == true){gAaAVZNfdK = false;}
      if(PszYqxCQyk == true){PszYqxCQyk = false;}
      if(wxWPJZjXIc == true){wxWPJZjXIc = false;}
      if(ccrZQAzNLt == true){ccrZQAzNLt = false;}
      if(dubiWsCGQq == true){dubiWsCGQq = false;}
      if(quXGojcLqw == true){quXGojcLqw = false;}
      if(opXBhmAZHp == true){opXBhmAZHp = false;}
      if(ynFEGAUnrP == true){ynFEGAUnrP = false;}
      if(XcHQkgFljg == true){XcHQkgFljg = false;}
      if(WnWOFnXZAj == true){WnWOFnXZAj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKLYKZLJZB
{ 
  void xTZwOZobnp()
  { 
      bool pjbMXCgEiF = false;
      bool YfEgrBZxLx = false;
      bool YjkGAuloZl = false;
      bool xjJuCyQxuu = false;
      bool jcjgKDcefH = false;
      bool QAohqFzVMc = false;
      bool PrdwIoWIet = false;
      bool jcBPMuzEux = false;
      bool SGISVwubEw = false;
      bool yukSfrynXV = false;
      bool gTAkWnyYUu = false;
      bool FuZOJIiLaL = false;
      bool tuEhwoqijU = false;
      bool wLfYQyGXuh = false;
      bool yVGIpDUVIW = false;
      bool JmMMbkPRoh = false;
      bool wPozzsOAyL = false;
      bool BKQsMXnwqr = false;
      bool TVZMLJzSxe = false;
      bool iohMligGJw = false;
      string yzgDOoVcnV;
      string xcdATpIasS;
      string PZZVRRVfum;
      string CkPXVDephw;
      string dqchWSJadc;
      string ZjixAYZKkw;
      string TogBTLNFdQ;
      string KRswnXxqzz;
      string HtBSMRBSWx;
      string cTEkboKbNK;
      string FDwNRHqlIc;
      string ahLlnZmOnC;
      string KtigmqMHUz;
      string NUdntExmAE;
      string ZOJtVtISxB;
      string BunKAKUPaa;
      string ujRIOGDXqj;
      string czOibuknLs;
      string hsKTxRgTmj;
      string igMYJpxAeP;
      if(yzgDOoVcnV == FDwNRHqlIc){pjbMXCgEiF = true;}
      else if(FDwNRHqlIc == yzgDOoVcnV){gTAkWnyYUu = true;}
      if(xcdATpIasS == ahLlnZmOnC){YfEgrBZxLx = true;}
      else if(ahLlnZmOnC == xcdATpIasS){FuZOJIiLaL = true;}
      if(PZZVRRVfum == KtigmqMHUz){YjkGAuloZl = true;}
      else if(KtigmqMHUz == PZZVRRVfum){tuEhwoqijU = true;}
      if(CkPXVDephw == NUdntExmAE){xjJuCyQxuu = true;}
      else if(NUdntExmAE == CkPXVDephw){wLfYQyGXuh = true;}
      if(dqchWSJadc == ZOJtVtISxB){jcjgKDcefH = true;}
      else if(ZOJtVtISxB == dqchWSJadc){yVGIpDUVIW = true;}
      if(ZjixAYZKkw == BunKAKUPaa){QAohqFzVMc = true;}
      else if(BunKAKUPaa == ZjixAYZKkw){JmMMbkPRoh = true;}
      if(TogBTLNFdQ == ujRIOGDXqj){PrdwIoWIet = true;}
      else if(ujRIOGDXqj == TogBTLNFdQ){wPozzsOAyL = true;}
      if(KRswnXxqzz == czOibuknLs){jcBPMuzEux = true;}
      if(HtBSMRBSWx == hsKTxRgTmj){SGISVwubEw = true;}
      if(cTEkboKbNK == igMYJpxAeP){yukSfrynXV = true;}
      while(czOibuknLs == KRswnXxqzz){BKQsMXnwqr = true;}
      while(hsKTxRgTmj == hsKTxRgTmj){TVZMLJzSxe = true;}
      while(igMYJpxAeP == igMYJpxAeP){iohMligGJw = true;}
      if(pjbMXCgEiF == true){pjbMXCgEiF = false;}
      if(YfEgrBZxLx == true){YfEgrBZxLx = false;}
      if(YjkGAuloZl == true){YjkGAuloZl = false;}
      if(xjJuCyQxuu == true){xjJuCyQxuu = false;}
      if(jcjgKDcefH == true){jcjgKDcefH = false;}
      if(QAohqFzVMc == true){QAohqFzVMc = false;}
      if(PrdwIoWIet == true){PrdwIoWIet = false;}
      if(jcBPMuzEux == true){jcBPMuzEux = false;}
      if(SGISVwubEw == true){SGISVwubEw = false;}
      if(yukSfrynXV == true){yukSfrynXV = false;}
      if(gTAkWnyYUu == true){gTAkWnyYUu = false;}
      if(FuZOJIiLaL == true){FuZOJIiLaL = false;}
      if(tuEhwoqijU == true){tuEhwoqijU = false;}
      if(wLfYQyGXuh == true){wLfYQyGXuh = false;}
      if(yVGIpDUVIW == true){yVGIpDUVIW = false;}
      if(JmMMbkPRoh == true){JmMMbkPRoh = false;}
      if(wPozzsOAyL == true){wPozzsOAyL = false;}
      if(BKQsMXnwqr == true){BKQsMXnwqr = false;}
      if(TVZMLJzSxe == true){TVZMLJzSxe = false;}
      if(iohMligGJw == true){iohMligGJw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SCSQTFSCSI
{ 
  void mSwFitTUNm()
  { 
      bool CSakQuUaJd = false;
      bool bPHuqzhzNk = false;
      bool ITGKQKkDgC = false;
      bool ZXIOHnrLoJ = false;
      bool ZRUxfedVfM = false;
      bool TVgNQhLQUG = false;
      bool KRtGDDHrmC = false;
      bool HVJEKpyIdk = false;
      bool gOWTiDqtyZ = false;
      bool caqizIXOtb = false;
      bool XkhdFxLbDa = false;
      bool iDliYutaXA = false;
      bool MNtNYfeaFB = false;
      bool SjOBNwfrNk = false;
      bool qOpWpZoHJD = false;
      bool NxptPKpUEZ = false;
      bool SkWBIznjVc = false;
      bool PCMlIxWXXz = false;
      bool pXQBnUsUlD = false;
      bool GLmmSGroOp = false;
      string GHEFioeBFf;
      string RnFPfMjugN;
      string DkaVLdNObT;
      string rqbNJZSIdT;
      string nSekXkCSXz;
      string HontJUghtE;
      string aQYkmZMqFF;
      string saRNZkGpyZ;
      string bupbMDCgEo;
      string skNYsXssxx;
      string YKMSGfXaUY;
      string OqjTceZwYj;
      string XemPMINsUC;
      string rMrBBRhXVf;
      string fbMfaBAswN;
      string xwTNZsWxGy;
      string SdGSfBzhSK;
      string wCasDuRHoK;
      string HTwGEurebH;
      string tkRXMBVtzZ;
      if(GHEFioeBFf == YKMSGfXaUY){CSakQuUaJd = true;}
      else if(YKMSGfXaUY == GHEFioeBFf){XkhdFxLbDa = true;}
      if(RnFPfMjugN == OqjTceZwYj){bPHuqzhzNk = true;}
      else if(OqjTceZwYj == RnFPfMjugN){iDliYutaXA = true;}
      if(DkaVLdNObT == XemPMINsUC){ITGKQKkDgC = true;}
      else if(XemPMINsUC == DkaVLdNObT){MNtNYfeaFB = true;}
      if(rqbNJZSIdT == rMrBBRhXVf){ZXIOHnrLoJ = true;}
      else if(rMrBBRhXVf == rqbNJZSIdT){SjOBNwfrNk = true;}
      if(nSekXkCSXz == fbMfaBAswN){ZRUxfedVfM = true;}
      else if(fbMfaBAswN == nSekXkCSXz){qOpWpZoHJD = true;}
      if(HontJUghtE == xwTNZsWxGy){TVgNQhLQUG = true;}
      else if(xwTNZsWxGy == HontJUghtE){NxptPKpUEZ = true;}
      if(aQYkmZMqFF == SdGSfBzhSK){KRtGDDHrmC = true;}
      else if(SdGSfBzhSK == aQYkmZMqFF){SkWBIznjVc = true;}
      if(saRNZkGpyZ == wCasDuRHoK){HVJEKpyIdk = true;}
      if(bupbMDCgEo == HTwGEurebH){gOWTiDqtyZ = true;}
      if(skNYsXssxx == tkRXMBVtzZ){caqizIXOtb = true;}
      while(wCasDuRHoK == saRNZkGpyZ){PCMlIxWXXz = true;}
      while(HTwGEurebH == HTwGEurebH){pXQBnUsUlD = true;}
      while(tkRXMBVtzZ == tkRXMBVtzZ){GLmmSGroOp = true;}
      if(CSakQuUaJd == true){CSakQuUaJd = false;}
      if(bPHuqzhzNk == true){bPHuqzhzNk = false;}
      if(ITGKQKkDgC == true){ITGKQKkDgC = false;}
      if(ZXIOHnrLoJ == true){ZXIOHnrLoJ = false;}
      if(ZRUxfedVfM == true){ZRUxfedVfM = false;}
      if(TVgNQhLQUG == true){TVgNQhLQUG = false;}
      if(KRtGDDHrmC == true){KRtGDDHrmC = false;}
      if(HVJEKpyIdk == true){HVJEKpyIdk = false;}
      if(gOWTiDqtyZ == true){gOWTiDqtyZ = false;}
      if(caqizIXOtb == true){caqizIXOtb = false;}
      if(XkhdFxLbDa == true){XkhdFxLbDa = false;}
      if(iDliYutaXA == true){iDliYutaXA = false;}
      if(MNtNYfeaFB == true){MNtNYfeaFB = false;}
      if(SjOBNwfrNk == true){SjOBNwfrNk = false;}
      if(qOpWpZoHJD == true){qOpWpZoHJD = false;}
      if(NxptPKpUEZ == true){NxptPKpUEZ = false;}
      if(SkWBIznjVc == true){SkWBIznjVc = false;}
      if(PCMlIxWXXz == true){PCMlIxWXXz = false;}
      if(pXQBnUsUlD == true){pXQBnUsUlD = false;}
      if(GLmmSGroOp == true){GLmmSGroOp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSTBAUYPKT
{ 
  void PNFAcchdzV()
  { 
      bool xMJBXxOPLG = false;
      bool eqEpidQjfD = false;
      bool UdGRiAaGHa = false;
      bool dGpseRLNtO = false;
      bool VEOEsHiKWs = false;
      bool ptEjVSFrRX = false;
      bool VIHkcYBLLR = false;
      bool SDoQhQOBYb = false;
      bool RQiOkiBFXL = false;
      bool LTuVrMwdbT = false;
      bool FXyFalEmCF = false;
      bool DEToGFZszs = false;
      bool XwnAFzHTXU = false;
      bool TkYEWsRcmz = false;
      bool eNCRHGAGPm = false;
      bool mDeiwIiyzb = false;
      bool ekOglSePSM = false;
      bool mxFANJsVry = false;
      bool zBDkhPGpHN = false;
      bool KTcLTsyVfo = false;
      string kCUXFbfXba;
      string ILcysoVYko;
      string yQprzFeTAb;
      string lEnuCmELlb;
      string ieAFJNJyCI;
      string gSpiSTLcXz;
      string xMXzoDXhwG;
      string kKlJGSQkhk;
      string wfQquTNEbh;
      string banmdVHAPF;
      string pbCwXWfgbz;
      string DZumDRwfEV;
      string pSFNdKWzek;
      string LPUbuUcTTX;
      string mgbbdCfAjM;
      string YawtPWVnSN;
      string AfCqnnESqh;
      string nbMfhIqdjb;
      string dVPRLjTaLY;
      string ynBGXGejnp;
      if(kCUXFbfXba == pbCwXWfgbz){xMJBXxOPLG = true;}
      else if(pbCwXWfgbz == kCUXFbfXba){FXyFalEmCF = true;}
      if(ILcysoVYko == DZumDRwfEV){eqEpidQjfD = true;}
      else if(DZumDRwfEV == ILcysoVYko){DEToGFZszs = true;}
      if(yQprzFeTAb == pSFNdKWzek){UdGRiAaGHa = true;}
      else if(pSFNdKWzek == yQprzFeTAb){XwnAFzHTXU = true;}
      if(lEnuCmELlb == LPUbuUcTTX){dGpseRLNtO = true;}
      else if(LPUbuUcTTX == lEnuCmELlb){TkYEWsRcmz = true;}
      if(ieAFJNJyCI == mgbbdCfAjM){VEOEsHiKWs = true;}
      else if(mgbbdCfAjM == ieAFJNJyCI){eNCRHGAGPm = true;}
      if(gSpiSTLcXz == YawtPWVnSN){ptEjVSFrRX = true;}
      else if(YawtPWVnSN == gSpiSTLcXz){mDeiwIiyzb = true;}
      if(xMXzoDXhwG == AfCqnnESqh){VIHkcYBLLR = true;}
      else if(AfCqnnESqh == xMXzoDXhwG){ekOglSePSM = true;}
      if(kKlJGSQkhk == nbMfhIqdjb){SDoQhQOBYb = true;}
      if(wfQquTNEbh == dVPRLjTaLY){RQiOkiBFXL = true;}
      if(banmdVHAPF == ynBGXGejnp){LTuVrMwdbT = true;}
      while(nbMfhIqdjb == kKlJGSQkhk){mxFANJsVry = true;}
      while(dVPRLjTaLY == dVPRLjTaLY){zBDkhPGpHN = true;}
      while(ynBGXGejnp == ynBGXGejnp){KTcLTsyVfo = true;}
      if(xMJBXxOPLG == true){xMJBXxOPLG = false;}
      if(eqEpidQjfD == true){eqEpidQjfD = false;}
      if(UdGRiAaGHa == true){UdGRiAaGHa = false;}
      if(dGpseRLNtO == true){dGpseRLNtO = false;}
      if(VEOEsHiKWs == true){VEOEsHiKWs = false;}
      if(ptEjVSFrRX == true){ptEjVSFrRX = false;}
      if(VIHkcYBLLR == true){VIHkcYBLLR = false;}
      if(SDoQhQOBYb == true){SDoQhQOBYb = false;}
      if(RQiOkiBFXL == true){RQiOkiBFXL = false;}
      if(LTuVrMwdbT == true){LTuVrMwdbT = false;}
      if(FXyFalEmCF == true){FXyFalEmCF = false;}
      if(DEToGFZszs == true){DEToGFZszs = false;}
      if(XwnAFzHTXU == true){XwnAFzHTXU = false;}
      if(TkYEWsRcmz == true){TkYEWsRcmz = false;}
      if(eNCRHGAGPm == true){eNCRHGAGPm = false;}
      if(mDeiwIiyzb == true){mDeiwIiyzb = false;}
      if(ekOglSePSM == true){ekOglSePSM = false;}
      if(mxFANJsVry == true){mxFANJsVry = false;}
      if(zBDkhPGpHN == true){zBDkhPGpHN = false;}
      if(KTcLTsyVfo == true){KTcLTsyVfo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOOAZYSKEZ
{ 
  void nWoxhXzVxp()
  { 
      bool yZwRIsbIsB = false;
      bool lAMNqFIbun = false;
      bool ArnDWLkNdP = false;
      bool wVwOPyKZMK = false;
      bool OcfGuVnyow = false;
      bool ZWlIJFkrtw = false;
      bool HNedFQEyyr = false;
      bool thPjYWMhIB = false;
      bool XmYgoZjmFJ = false;
      bool NSeQDAyBBe = false;
      bool RoAwBqGBil = false;
      bool rDirYUoxoe = false;
      bool gQrnebDzgY = false;
      bool YLfdjhlbfx = false;
      bool ShDSQKilqh = false;
      bool LBMVyAwMRZ = false;
      bool nHUKNgWFIp = false;
      bool iNRqMyMZWT = false;
      bool rQHyNWzKfi = false;
      bool kZKFIKNsFj = false;
      string WDBacdPfFW;
      string JEjJFgSdaj;
      string mBdHZnihhu;
      string HhtqeZPoIQ;
      string LLrnPgImla;
      string eWyTUVYsAn;
      string uhyKPaJref;
      string QcVKYaIors;
      string fuuGPjjaVJ;
      string AWnTUcNhXn;
      string WPHGKBBmts;
      string MiAGIAlqtf;
      string qiWVetoBpu;
      string NZREVPmnwO;
      string hwfcwQVgKU;
      string qWnrwnslbP;
      string MzxzflRwks;
      string MxtfyuCsYO;
      string XHqUEqlYHg;
      string VBMgBiygxJ;
      if(WDBacdPfFW == WPHGKBBmts){yZwRIsbIsB = true;}
      else if(WPHGKBBmts == WDBacdPfFW){RoAwBqGBil = true;}
      if(JEjJFgSdaj == MiAGIAlqtf){lAMNqFIbun = true;}
      else if(MiAGIAlqtf == JEjJFgSdaj){rDirYUoxoe = true;}
      if(mBdHZnihhu == qiWVetoBpu){ArnDWLkNdP = true;}
      else if(qiWVetoBpu == mBdHZnihhu){gQrnebDzgY = true;}
      if(HhtqeZPoIQ == NZREVPmnwO){wVwOPyKZMK = true;}
      else if(NZREVPmnwO == HhtqeZPoIQ){YLfdjhlbfx = true;}
      if(LLrnPgImla == hwfcwQVgKU){OcfGuVnyow = true;}
      else if(hwfcwQVgKU == LLrnPgImla){ShDSQKilqh = true;}
      if(eWyTUVYsAn == qWnrwnslbP){ZWlIJFkrtw = true;}
      else if(qWnrwnslbP == eWyTUVYsAn){LBMVyAwMRZ = true;}
      if(uhyKPaJref == MzxzflRwks){HNedFQEyyr = true;}
      else if(MzxzflRwks == uhyKPaJref){nHUKNgWFIp = true;}
      if(QcVKYaIors == MxtfyuCsYO){thPjYWMhIB = true;}
      if(fuuGPjjaVJ == XHqUEqlYHg){XmYgoZjmFJ = true;}
      if(AWnTUcNhXn == VBMgBiygxJ){NSeQDAyBBe = true;}
      while(MxtfyuCsYO == QcVKYaIors){iNRqMyMZWT = true;}
      while(XHqUEqlYHg == XHqUEqlYHg){rQHyNWzKfi = true;}
      while(VBMgBiygxJ == VBMgBiygxJ){kZKFIKNsFj = true;}
      if(yZwRIsbIsB == true){yZwRIsbIsB = false;}
      if(lAMNqFIbun == true){lAMNqFIbun = false;}
      if(ArnDWLkNdP == true){ArnDWLkNdP = false;}
      if(wVwOPyKZMK == true){wVwOPyKZMK = false;}
      if(OcfGuVnyow == true){OcfGuVnyow = false;}
      if(ZWlIJFkrtw == true){ZWlIJFkrtw = false;}
      if(HNedFQEyyr == true){HNedFQEyyr = false;}
      if(thPjYWMhIB == true){thPjYWMhIB = false;}
      if(XmYgoZjmFJ == true){XmYgoZjmFJ = false;}
      if(NSeQDAyBBe == true){NSeQDAyBBe = false;}
      if(RoAwBqGBil == true){RoAwBqGBil = false;}
      if(rDirYUoxoe == true){rDirYUoxoe = false;}
      if(gQrnebDzgY == true){gQrnebDzgY = false;}
      if(YLfdjhlbfx == true){YLfdjhlbfx = false;}
      if(ShDSQKilqh == true){ShDSQKilqh = false;}
      if(LBMVyAwMRZ == true){LBMVyAwMRZ = false;}
      if(nHUKNgWFIp == true){nHUKNgWFIp = false;}
      if(iNRqMyMZWT == true){iNRqMyMZWT = false;}
      if(rQHyNWzKfi == true){rQHyNWzKfi = false;}
      if(kZKFIKNsFj == true){kZKFIKNsFj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSMBNLPMQB
{ 
  void ZcdIjSUiaf()
  { 
      bool FlaKdlDjsT = false;
      bool CabfMfBkAN = false;
      bool ANEYFUhPXV = false;
      bool BgTTyeAhCw = false;
      bool YAnPMEyWDV = false;
      bool teMNZqgCEJ = false;
      bool EnLWRUHIgg = false;
      bool fSiDnAZnLB = false;
      bool WKMBbWUFsG = false;
      bool yycrrknQxr = false;
      bool wopVpauIZZ = false;
      bool RspDlsbKuu = false;
      bool ABPaigppLD = false;
      bool LJqTEhUpLA = false;
      bool aLfSnEIYGy = false;
      bool IdUBquZPmI = false;
      bool kFxVNIBVzE = false;
      bool YlyuUoUwld = false;
      bool YRjNuhnobI = false;
      bool HFDCPVOKEf = false;
      string NFIKeZEyFE;
      string KDaWbTPdKx;
      string QlHuMFGFJK;
      string ZEbrVkuLHl;
      string twrwpNSeet;
      string BDxqWayMyZ;
      string TyntdGaiBq;
      string YDVYCTsKEy;
      string laaPIWGkUt;
      string mhNhRwHxSj;
      string mjdmVxgYoC;
      string hmIzmrXYlH;
      string zpNHDqpmGG;
      string LwrULCxmtK;
      string ohuRMAZOuZ;
      string XiLKkwWWjd;
      string HsRipktnmk;
      string ukeaRRtutD;
      string RarghckgiO;
      string eZDPCuPMaa;
      if(NFIKeZEyFE == mjdmVxgYoC){FlaKdlDjsT = true;}
      else if(mjdmVxgYoC == NFIKeZEyFE){wopVpauIZZ = true;}
      if(KDaWbTPdKx == hmIzmrXYlH){CabfMfBkAN = true;}
      else if(hmIzmrXYlH == KDaWbTPdKx){RspDlsbKuu = true;}
      if(QlHuMFGFJK == zpNHDqpmGG){ANEYFUhPXV = true;}
      else if(zpNHDqpmGG == QlHuMFGFJK){ABPaigppLD = true;}
      if(ZEbrVkuLHl == LwrULCxmtK){BgTTyeAhCw = true;}
      else if(LwrULCxmtK == ZEbrVkuLHl){LJqTEhUpLA = true;}
      if(twrwpNSeet == ohuRMAZOuZ){YAnPMEyWDV = true;}
      else if(ohuRMAZOuZ == twrwpNSeet){aLfSnEIYGy = true;}
      if(BDxqWayMyZ == XiLKkwWWjd){teMNZqgCEJ = true;}
      else if(XiLKkwWWjd == BDxqWayMyZ){IdUBquZPmI = true;}
      if(TyntdGaiBq == HsRipktnmk){EnLWRUHIgg = true;}
      else if(HsRipktnmk == TyntdGaiBq){kFxVNIBVzE = true;}
      if(YDVYCTsKEy == ukeaRRtutD){fSiDnAZnLB = true;}
      if(laaPIWGkUt == RarghckgiO){WKMBbWUFsG = true;}
      if(mhNhRwHxSj == eZDPCuPMaa){yycrrknQxr = true;}
      while(ukeaRRtutD == YDVYCTsKEy){YlyuUoUwld = true;}
      while(RarghckgiO == RarghckgiO){YRjNuhnobI = true;}
      while(eZDPCuPMaa == eZDPCuPMaa){HFDCPVOKEf = true;}
      if(FlaKdlDjsT == true){FlaKdlDjsT = false;}
      if(CabfMfBkAN == true){CabfMfBkAN = false;}
      if(ANEYFUhPXV == true){ANEYFUhPXV = false;}
      if(BgTTyeAhCw == true){BgTTyeAhCw = false;}
      if(YAnPMEyWDV == true){YAnPMEyWDV = false;}
      if(teMNZqgCEJ == true){teMNZqgCEJ = false;}
      if(EnLWRUHIgg == true){EnLWRUHIgg = false;}
      if(fSiDnAZnLB == true){fSiDnAZnLB = false;}
      if(WKMBbWUFsG == true){WKMBbWUFsG = false;}
      if(yycrrknQxr == true){yycrrknQxr = false;}
      if(wopVpauIZZ == true){wopVpauIZZ = false;}
      if(RspDlsbKuu == true){RspDlsbKuu = false;}
      if(ABPaigppLD == true){ABPaigppLD = false;}
      if(LJqTEhUpLA == true){LJqTEhUpLA = false;}
      if(aLfSnEIYGy == true){aLfSnEIYGy = false;}
      if(IdUBquZPmI == true){IdUBquZPmI = false;}
      if(kFxVNIBVzE == true){kFxVNIBVzE = false;}
      if(YlyuUoUwld == true){YlyuUoUwld = false;}
      if(YRjNuhnobI == true){YRjNuhnobI = false;}
      if(HFDCPVOKEf == true){HFDCPVOKEf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCHCZFYMGX
{ 
  void nWlHePuoQx()
  { 
      bool UAWWoQbjot = false;
      bool VrLyaOrWqi = false;
      bool ripOgCPcdI = false;
      bool dWDXXtkgrj = false;
      bool rCiPMIsmmm = false;
      bool mskOqkKIol = false;
      bool ByGfPznmZg = false;
      bool cLeHpoAZBY = false;
      bool JbopUklogl = false;
      bool icqGitwCzN = false;
      bool TGMGJbOcXC = false;
      bool kkGQbZJPKe = false;
      bool NyGnyATXYw = false;
      bool rxZnEDOigr = false;
      bool VIReByWadJ = false;
      bool kfqUAVzYHJ = false;
      bool IpEbJmKRLY = false;
      bool KZiRIFgblA = false;
      bool drtPLLFFni = false;
      bool DobXjfDoUN = false;
      string bkinzDbuHL;
      string JHRUtBZiVf;
      string LVgdnhOHPc;
      string RpGVDnFXwQ;
      string QaylYrrFRN;
      string DnmZbGDEzR;
      string oUedsSBwRF;
      string wClFPjXuFw;
      string pJoCZdCfsx;
      string kAYebwwTsF;
      string qwmLRAChKr;
      string iIzDaeecEP;
      string PUCUUudHdS;
      string nDBzFsWckY;
      string aUUBObAUDw;
      string RTPdoVsRqV;
      string WuErDeHAyg;
      string HBrenuzBGr;
      string tIDgAUmXJi;
      string AElOBfQcxi;
      if(bkinzDbuHL == qwmLRAChKr){UAWWoQbjot = true;}
      else if(qwmLRAChKr == bkinzDbuHL){TGMGJbOcXC = true;}
      if(JHRUtBZiVf == iIzDaeecEP){VrLyaOrWqi = true;}
      else if(iIzDaeecEP == JHRUtBZiVf){kkGQbZJPKe = true;}
      if(LVgdnhOHPc == PUCUUudHdS){ripOgCPcdI = true;}
      else if(PUCUUudHdS == LVgdnhOHPc){NyGnyATXYw = true;}
      if(RpGVDnFXwQ == nDBzFsWckY){dWDXXtkgrj = true;}
      else if(nDBzFsWckY == RpGVDnFXwQ){rxZnEDOigr = true;}
      if(QaylYrrFRN == aUUBObAUDw){rCiPMIsmmm = true;}
      else if(aUUBObAUDw == QaylYrrFRN){VIReByWadJ = true;}
      if(DnmZbGDEzR == RTPdoVsRqV){mskOqkKIol = true;}
      else if(RTPdoVsRqV == DnmZbGDEzR){kfqUAVzYHJ = true;}
      if(oUedsSBwRF == WuErDeHAyg){ByGfPznmZg = true;}
      else if(WuErDeHAyg == oUedsSBwRF){IpEbJmKRLY = true;}
      if(wClFPjXuFw == HBrenuzBGr){cLeHpoAZBY = true;}
      if(pJoCZdCfsx == tIDgAUmXJi){JbopUklogl = true;}
      if(kAYebwwTsF == AElOBfQcxi){icqGitwCzN = true;}
      while(HBrenuzBGr == wClFPjXuFw){KZiRIFgblA = true;}
      while(tIDgAUmXJi == tIDgAUmXJi){drtPLLFFni = true;}
      while(AElOBfQcxi == AElOBfQcxi){DobXjfDoUN = true;}
      if(UAWWoQbjot == true){UAWWoQbjot = false;}
      if(VrLyaOrWqi == true){VrLyaOrWqi = false;}
      if(ripOgCPcdI == true){ripOgCPcdI = false;}
      if(dWDXXtkgrj == true){dWDXXtkgrj = false;}
      if(rCiPMIsmmm == true){rCiPMIsmmm = false;}
      if(mskOqkKIol == true){mskOqkKIol = false;}
      if(ByGfPznmZg == true){ByGfPznmZg = false;}
      if(cLeHpoAZBY == true){cLeHpoAZBY = false;}
      if(JbopUklogl == true){JbopUklogl = false;}
      if(icqGitwCzN == true){icqGitwCzN = false;}
      if(TGMGJbOcXC == true){TGMGJbOcXC = false;}
      if(kkGQbZJPKe == true){kkGQbZJPKe = false;}
      if(NyGnyATXYw == true){NyGnyATXYw = false;}
      if(rxZnEDOigr == true){rxZnEDOigr = false;}
      if(VIReByWadJ == true){VIReByWadJ = false;}
      if(kfqUAVzYHJ == true){kfqUAVzYHJ = false;}
      if(IpEbJmKRLY == true){IpEbJmKRLY = false;}
      if(KZiRIFgblA == true){KZiRIFgblA = false;}
      if(drtPLLFFni == true){drtPLLFFni = false;}
      if(DobXjfDoUN == true){DobXjfDoUN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPRYONLEND
{ 
  void EZcnQCpOEQ()
  { 
      bool LMGRplndDt = false;
      bool FQCfsjMQPL = false;
      bool aGfIbccwcI = false;
      bool HKtPNlUIzF = false;
      bool ChTcqOwaYa = false;
      bool nGKVAFgxpM = false;
      bool IrBtmtWlSH = false;
      bool PDQKIrmCQN = false;
      bool gCXBUAAXPI = false;
      bool FWSmwJgYox = false;
      bool qKHQLjpANI = false;
      bool SdfbfGUzZm = false;
      bool tyVKCrkcNy = false;
      bool LNMTVVtGpk = false;
      bool KzKHoaqpHp = false;
      bool ogyCCsnxOS = false;
      bool yMlOwEQLGJ = false;
      bool MOIobtnOUa = false;
      bool BuVXJePJRc = false;
      bool gwqXlxNwKk = false;
      string wOnUlCEqrj;
      string EapCPYnVyi;
      string lTOKdbmVCL;
      string PDExLAswPC;
      string CQKZgfxrll;
      string pqKBRczcqK;
      string PhofTAVrpP;
      string erFugUJocx;
      string dtjQUYrCfi;
      string AQFFmTadGg;
      string KFBVGylOUw;
      string TKAsfUyXKu;
      string HTLHPOmzIM;
      string tfhwmYrNJW;
      string ldhjPoPLYS;
      string VCSLYpstGr;
      string LlGHCncDFH;
      string bjOnIdkbrZ;
      string yaZpqqMWXw;
      string fyHRLAWahb;
      if(wOnUlCEqrj == KFBVGylOUw){LMGRplndDt = true;}
      else if(KFBVGylOUw == wOnUlCEqrj){qKHQLjpANI = true;}
      if(EapCPYnVyi == TKAsfUyXKu){FQCfsjMQPL = true;}
      else if(TKAsfUyXKu == EapCPYnVyi){SdfbfGUzZm = true;}
      if(lTOKdbmVCL == HTLHPOmzIM){aGfIbccwcI = true;}
      else if(HTLHPOmzIM == lTOKdbmVCL){tyVKCrkcNy = true;}
      if(PDExLAswPC == tfhwmYrNJW){HKtPNlUIzF = true;}
      else if(tfhwmYrNJW == PDExLAswPC){LNMTVVtGpk = true;}
      if(CQKZgfxrll == ldhjPoPLYS){ChTcqOwaYa = true;}
      else if(ldhjPoPLYS == CQKZgfxrll){KzKHoaqpHp = true;}
      if(pqKBRczcqK == VCSLYpstGr){nGKVAFgxpM = true;}
      else if(VCSLYpstGr == pqKBRczcqK){ogyCCsnxOS = true;}
      if(PhofTAVrpP == LlGHCncDFH){IrBtmtWlSH = true;}
      else if(LlGHCncDFH == PhofTAVrpP){yMlOwEQLGJ = true;}
      if(erFugUJocx == bjOnIdkbrZ){PDQKIrmCQN = true;}
      if(dtjQUYrCfi == yaZpqqMWXw){gCXBUAAXPI = true;}
      if(AQFFmTadGg == fyHRLAWahb){FWSmwJgYox = true;}
      while(bjOnIdkbrZ == erFugUJocx){MOIobtnOUa = true;}
      while(yaZpqqMWXw == yaZpqqMWXw){BuVXJePJRc = true;}
      while(fyHRLAWahb == fyHRLAWahb){gwqXlxNwKk = true;}
      if(LMGRplndDt == true){LMGRplndDt = false;}
      if(FQCfsjMQPL == true){FQCfsjMQPL = false;}
      if(aGfIbccwcI == true){aGfIbccwcI = false;}
      if(HKtPNlUIzF == true){HKtPNlUIzF = false;}
      if(ChTcqOwaYa == true){ChTcqOwaYa = false;}
      if(nGKVAFgxpM == true){nGKVAFgxpM = false;}
      if(IrBtmtWlSH == true){IrBtmtWlSH = false;}
      if(PDQKIrmCQN == true){PDQKIrmCQN = false;}
      if(gCXBUAAXPI == true){gCXBUAAXPI = false;}
      if(FWSmwJgYox == true){FWSmwJgYox = false;}
      if(qKHQLjpANI == true){qKHQLjpANI = false;}
      if(SdfbfGUzZm == true){SdfbfGUzZm = false;}
      if(tyVKCrkcNy == true){tyVKCrkcNy = false;}
      if(LNMTVVtGpk == true){LNMTVVtGpk = false;}
      if(KzKHoaqpHp == true){KzKHoaqpHp = false;}
      if(ogyCCsnxOS == true){ogyCCsnxOS = false;}
      if(yMlOwEQLGJ == true){yMlOwEQLGJ = false;}
      if(MOIobtnOUa == true){MOIobtnOUa = false;}
      if(BuVXJePJRc == true){BuVXJePJRc = false;}
      if(gwqXlxNwKk == true){gwqXlxNwKk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRMYOGNRDZ
{ 
  void ecwdAOzEXG()
  { 
      bool HzouXfZzEa = false;
      bool BYVQrBYJmu = false;
      bool pTdSUQyaPC = false;
      bool SwLYTIlsHo = false;
      bool tXBlLdwPzN = false;
      bool mpVLdnUWaG = false;
      bool gzjCHFMxwj = false;
      bool OeBxASRrGq = false;
      bool UibBPcaAuf = false;
      bool mPRAIunzdG = false;
      bool QySOyHnXLK = false;
      bool WcPjlxXhle = false;
      bool eMCPxzNBoF = false;
      bool eROzZVPNDH = false;
      bool nCojIKzhNK = false;
      bool XFNybDwDQz = false;
      bool tmiFfFOQJQ = false;
      bool hJedqcXSGm = false;
      bool zemegYDPXW = false;
      bool ZMwENBSiDD = false;
      string QOxDRhHiHw;
      string hKypQqsigk;
      string YxcmCPpbgP;
      string LIjBQVBXnS;
      string rGtsbDhQzo;
      string uPqfxSkKAB;
      string reCrjZZwYu;
      string pUtOrSDjKy;
      string hYbqTuREDx;
      string jqXlaMEBIC;
      string clqDzaVcme;
      string PBzBTSCKXo;
      string HVraKyxHme;
      string OBaHUwhYrs;
      string ZoQYhhqVSH;
      string JsdTtHsPsA;
      string dNoHQNaqfX;
      string jdSeOSFTsb;
      string HboeUUWGNN;
      string CSfqPLzIHU;
      if(QOxDRhHiHw == clqDzaVcme){HzouXfZzEa = true;}
      else if(clqDzaVcme == QOxDRhHiHw){QySOyHnXLK = true;}
      if(hKypQqsigk == PBzBTSCKXo){BYVQrBYJmu = true;}
      else if(PBzBTSCKXo == hKypQqsigk){WcPjlxXhle = true;}
      if(YxcmCPpbgP == HVraKyxHme){pTdSUQyaPC = true;}
      else if(HVraKyxHme == YxcmCPpbgP){eMCPxzNBoF = true;}
      if(LIjBQVBXnS == OBaHUwhYrs){SwLYTIlsHo = true;}
      else if(OBaHUwhYrs == LIjBQVBXnS){eROzZVPNDH = true;}
      if(rGtsbDhQzo == ZoQYhhqVSH){tXBlLdwPzN = true;}
      else if(ZoQYhhqVSH == rGtsbDhQzo){nCojIKzhNK = true;}
      if(uPqfxSkKAB == JsdTtHsPsA){mpVLdnUWaG = true;}
      else if(JsdTtHsPsA == uPqfxSkKAB){XFNybDwDQz = true;}
      if(reCrjZZwYu == dNoHQNaqfX){gzjCHFMxwj = true;}
      else if(dNoHQNaqfX == reCrjZZwYu){tmiFfFOQJQ = true;}
      if(pUtOrSDjKy == jdSeOSFTsb){OeBxASRrGq = true;}
      if(hYbqTuREDx == HboeUUWGNN){UibBPcaAuf = true;}
      if(jqXlaMEBIC == CSfqPLzIHU){mPRAIunzdG = true;}
      while(jdSeOSFTsb == pUtOrSDjKy){hJedqcXSGm = true;}
      while(HboeUUWGNN == HboeUUWGNN){zemegYDPXW = true;}
      while(CSfqPLzIHU == CSfqPLzIHU){ZMwENBSiDD = true;}
      if(HzouXfZzEa == true){HzouXfZzEa = false;}
      if(BYVQrBYJmu == true){BYVQrBYJmu = false;}
      if(pTdSUQyaPC == true){pTdSUQyaPC = false;}
      if(SwLYTIlsHo == true){SwLYTIlsHo = false;}
      if(tXBlLdwPzN == true){tXBlLdwPzN = false;}
      if(mpVLdnUWaG == true){mpVLdnUWaG = false;}
      if(gzjCHFMxwj == true){gzjCHFMxwj = false;}
      if(OeBxASRrGq == true){OeBxASRrGq = false;}
      if(UibBPcaAuf == true){UibBPcaAuf = false;}
      if(mPRAIunzdG == true){mPRAIunzdG = false;}
      if(QySOyHnXLK == true){QySOyHnXLK = false;}
      if(WcPjlxXhle == true){WcPjlxXhle = false;}
      if(eMCPxzNBoF == true){eMCPxzNBoF = false;}
      if(eROzZVPNDH == true){eROzZVPNDH = false;}
      if(nCojIKzhNK == true){nCojIKzhNK = false;}
      if(XFNybDwDQz == true){XFNybDwDQz = false;}
      if(tmiFfFOQJQ == true){tmiFfFOQJQ = false;}
      if(hJedqcXSGm == true){hJedqcXSGm = false;}
      if(zemegYDPXW == true){zemegYDPXW = false;}
      if(ZMwENBSiDD == true){ZMwENBSiDD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOVXTTIFJV
{ 
  void lSIpGNrdgz()
  { 
      bool bAjGjDWOWI = false;
      bool jXqXSeMnzw = false;
      bool XxnjfUuCkS = false;
      bool YLdjXBKSbL = false;
      bool HVAnPJNJhL = false;
      bool TzGphdLzZP = false;
      bool IUdEjYtGzR = false;
      bool TsLnoCxATW = false;
      bool GlTYzYEmBs = false;
      bool oLrMDlrwDq = false;
      bool OGJQqZmSBf = false;
      bool gLfDIWAEFK = false;
      bool THEGbIAzjC = false;
      bool JBwcHAcChY = false;
      bool llkVMdfnDg = false;
      bool knqrXHCCni = false;
      bool ZmhyVfOCwI = false;
      bool sxWgYgVity = false;
      bool bLuDQVKEFz = false;
      bool xZOyyyEmzf = false;
      string SWzXKxRYCy;
      string cWEkMFwjxh;
      string OefLxiMISI;
      string hVCfjCcdhF;
      string XHYBaIrnfl;
      string FiMVlmqmZb;
      string jJGsPHTXBJ;
      string cRBqJGFdko;
      string pYbfDzIgsw;
      string LoDGUNBfkS;
      string nTlWJmgVLf;
      string hNCjkLhZpQ;
      string ymeEynNuVw;
      string FZrRAWlFWP;
      string RmVNOxlTUJ;
      string faoUUBogXU;
      string YlzPaIUkjO;
      string YbDayLQQpA;
      string CtZLPdjWwz;
      string hEgBpfmFmG;
      if(SWzXKxRYCy == nTlWJmgVLf){bAjGjDWOWI = true;}
      else if(nTlWJmgVLf == SWzXKxRYCy){OGJQqZmSBf = true;}
      if(cWEkMFwjxh == hNCjkLhZpQ){jXqXSeMnzw = true;}
      else if(hNCjkLhZpQ == cWEkMFwjxh){gLfDIWAEFK = true;}
      if(OefLxiMISI == ymeEynNuVw){XxnjfUuCkS = true;}
      else if(ymeEynNuVw == OefLxiMISI){THEGbIAzjC = true;}
      if(hVCfjCcdhF == FZrRAWlFWP){YLdjXBKSbL = true;}
      else if(FZrRAWlFWP == hVCfjCcdhF){JBwcHAcChY = true;}
      if(XHYBaIrnfl == RmVNOxlTUJ){HVAnPJNJhL = true;}
      else if(RmVNOxlTUJ == XHYBaIrnfl){llkVMdfnDg = true;}
      if(FiMVlmqmZb == faoUUBogXU){TzGphdLzZP = true;}
      else if(faoUUBogXU == FiMVlmqmZb){knqrXHCCni = true;}
      if(jJGsPHTXBJ == YlzPaIUkjO){IUdEjYtGzR = true;}
      else if(YlzPaIUkjO == jJGsPHTXBJ){ZmhyVfOCwI = true;}
      if(cRBqJGFdko == YbDayLQQpA){TsLnoCxATW = true;}
      if(pYbfDzIgsw == CtZLPdjWwz){GlTYzYEmBs = true;}
      if(LoDGUNBfkS == hEgBpfmFmG){oLrMDlrwDq = true;}
      while(YbDayLQQpA == cRBqJGFdko){sxWgYgVity = true;}
      while(CtZLPdjWwz == CtZLPdjWwz){bLuDQVKEFz = true;}
      while(hEgBpfmFmG == hEgBpfmFmG){xZOyyyEmzf = true;}
      if(bAjGjDWOWI == true){bAjGjDWOWI = false;}
      if(jXqXSeMnzw == true){jXqXSeMnzw = false;}
      if(XxnjfUuCkS == true){XxnjfUuCkS = false;}
      if(YLdjXBKSbL == true){YLdjXBKSbL = false;}
      if(HVAnPJNJhL == true){HVAnPJNJhL = false;}
      if(TzGphdLzZP == true){TzGphdLzZP = false;}
      if(IUdEjYtGzR == true){IUdEjYtGzR = false;}
      if(TsLnoCxATW == true){TsLnoCxATW = false;}
      if(GlTYzYEmBs == true){GlTYzYEmBs = false;}
      if(oLrMDlrwDq == true){oLrMDlrwDq = false;}
      if(OGJQqZmSBf == true){OGJQqZmSBf = false;}
      if(gLfDIWAEFK == true){gLfDIWAEFK = false;}
      if(THEGbIAzjC == true){THEGbIAzjC = false;}
      if(JBwcHAcChY == true){JBwcHAcChY = false;}
      if(llkVMdfnDg == true){llkVMdfnDg = false;}
      if(knqrXHCCni == true){knqrXHCCni = false;}
      if(ZmhyVfOCwI == true){ZmhyVfOCwI = false;}
      if(sxWgYgVity == true){sxWgYgVity = false;}
      if(bLuDQVKEFz == true){bLuDQVKEFz = false;}
      if(xZOyyyEmzf == true){xZOyyyEmzf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGCFSWOLWH
{ 
  void cPbhOfInTi()
  { 
      bool gRsJGwAONz = false;
      bool ehCJITLwCF = false;
      bool xIymRBanml = false;
      bool ViuAPKWyVq = false;
      bool kupHAaNrfZ = false;
      bool DDoLzYTFrE = false;
      bool ULaadulCsx = false;
      bool wNaKUCRpmp = false;
      bool niINhRsjBp = false;
      bool qQGQWYTPcE = false;
      bool nLyhcpcdqw = false;
      bool GcSBQkDNrM = false;
      bool BCADGfHKnw = false;
      bool iCMhBbkZjr = false;
      bool oOsFjNxEAk = false;
      bool UFWQClKtax = false;
      bool iSptMDPkAn = false;
      bool AccAXlJuSs = false;
      bool hCJCadfwfO = false;
      bool RpzmIWYyrf = false;
      string jRkDZuJPoD;
      string XyBHArHZSP;
      string oNMGCXqVCq;
      string SdGQngkPRL;
      string wsDnLEBWQr;
      string CUfWBWFdBB;
      string DnMyksqjTS;
      string GqIHTuJXux;
      string VTEKnxyjOR;
      string bGOPHHfEDR;
      string MRDxkLMYCG;
      string MgiDeiiCJm;
      string uHVCqAbrAM;
      string OEUcjEQHYc;
      string jYgIEtXLjX;
      string XduQVFuAGk;
      string iTYpqHMFSa;
      string RbcgCVZNxx;
      string bPHbnkJEHe;
      string JQBnsPAqRx;
      if(jRkDZuJPoD == MRDxkLMYCG){gRsJGwAONz = true;}
      else if(MRDxkLMYCG == jRkDZuJPoD){nLyhcpcdqw = true;}
      if(XyBHArHZSP == MgiDeiiCJm){ehCJITLwCF = true;}
      else if(MgiDeiiCJm == XyBHArHZSP){GcSBQkDNrM = true;}
      if(oNMGCXqVCq == uHVCqAbrAM){xIymRBanml = true;}
      else if(uHVCqAbrAM == oNMGCXqVCq){BCADGfHKnw = true;}
      if(SdGQngkPRL == OEUcjEQHYc){ViuAPKWyVq = true;}
      else if(OEUcjEQHYc == SdGQngkPRL){iCMhBbkZjr = true;}
      if(wsDnLEBWQr == jYgIEtXLjX){kupHAaNrfZ = true;}
      else if(jYgIEtXLjX == wsDnLEBWQr){oOsFjNxEAk = true;}
      if(CUfWBWFdBB == XduQVFuAGk){DDoLzYTFrE = true;}
      else if(XduQVFuAGk == CUfWBWFdBB){UFWQClKtax = true;}
      if(DnMyksqjTS == iTYpqHMFSa){ULaadulCsx = true;}
      else if(iTYpqHMFSa == DnMyksqjTS){iSptMDPkAn = true;}
      if(GqIHTuJXux == RbcgCVZNxx){wNaKUCRpmp = true;}
      if(VTEKnxyjOR == bPHbnkJEHe){niINhRsjBp = true;}
      if(bGOPHHfEDR == JQBnsPAqRx){qQGQWYTPcE = true;}
      while(RbcgCVZNxx == GqIHTuJXux){AccAXlJuSs = true;}
      while(bPHbnkJEHe == bPHbnkJEHe){hCJCadfwfO = true;}
      while(JQBnsPAqRx == JQBnsPAqRx){RpzmIWYyrf = true;}
      if(gRsJGwAONz == true){gRsJGwAONz = false;}
      if(ehCJITLwCF == true){ehCJITLwCF = false;}
      if(xIymRBanml == true){xIymRBanml = false;}
      if(ViuAPKWyVq == true){ViuAPKWyVq = false;}
      if(kupHAaNrfZ == true){kupHAaNrfZ = false;}
      if(DDoLzYTFrE == true){DDoLzYTFrE = false;}
      if(ULaadulCsx == true){ULaadulCsx = false;}
      if(wNaKUCRpmp == true){wNaKUCRpmp = false;}
      if(niINhRsjBp == true){niINhRsjBp = false;}
      if(qQGQWYTPcE == true){qQGQWYTPcE = false;}
      if(nLyhcpcdqw == true){nLyhcpcdqw = false;}
      if(GcSBQkDNrM == true){GcSBQkDNrM = false;}
      if(BCADGfHKnw == true){BCADGfHKnw = false;}
      if(iCMhBbkZjr == true){iCMhBbkZjr = false;}
      if(oOsFjNxEAk == true){oOsFjNxEAk = false;}
      if(UFWQClKtax == true){UFWQClKtax = false;}
      if(iSptMDPkAn == true){iSptMDPkAn = false;}
      if(AccAXlJuSs == true){AccAXlJuSs = false;}
      if(hCJCadfwfO == true){hCJCadfwfO = false;}
      if(RpzmIWYyrf == true){RpzmIWYyrf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFFYSZRLRP
{ 
  void sOJmxEZLbt()
  { 
      bool EEGiLzrxEo = false;
      bool hEhbdKsqtR = false;
      bool QdNNHpRVQw = false;
      bool zrMCAeCXFr = false;
      bool CDxDKZAJAg = false;
      bool QIJbQaqraU = false;
      bool gVgHppqfbz = false;
      bool HUlBOMfJCh = false;
      bool pHVifqhklZ = false;
      bool nJxjKfVoNU = false;
      bool hUhBZuWHMD = false;
      bool ugpseZAyby = false;
      bool HGtBKxXBqh = false;
      bool qpwhzVZTJk = false;
      bool TZXheHTEFk = false;
      bool fXNOMbagpb = false;
      bool XVQeMEjHsI = false;
      bool zgopeghLWD = false;
      bool dSuFCSbhUX = false;
      bool uscgMyIsVZ = false;
      string fDUrwiyrTt;
      string MxCjgKXQzQ;
      string IZTBXFHhzA;
      string qmiidNSLom;
      string rgseVhqGqz;
      string BEVHcGiTUq;
      string bPsSDYOSFT;
      string rMaMYbgoep;
      string NBqzzmQaGX;
      string dyqyLbmZbx;
      string SXAWGncJiA;
      string YsndcZXsTQ;
      string HnMhosVcBw;
      string nHNhXpATrK;
      string JHqFyjKMVk;
      string DsGLoeLRgN;
      string SAHmMRfGGl;
      string ZEBIGzwGiF;
      string iIHQruBCrs;
      string eilerJAEsg;
      if(fDUrwiyrTt == SXAWGncJiA){EEGiLzrxEo = true;}
      else if(SXAWGncJiA == fDUrwiyrTt){hUhBZuWHMD = true;}
      if(MxCjgKXQzQ == YsndcZXsTQ){hEhbdKsqtR = true;}
      else if(YsndcZXsTQ == MxCjgKXQzQ){ugpseZAyby = true;}
      if(IZTBXFHhzA == HnMhosVcBw){QdNNHpRVQw = true;}
      else if(HnMhosVcBw == IZTBXFHhzA){HGtBKxXBqh = true;}
      if(qmiidNSLom == nHNhXpATrK){zrMCAeCXFr = true;}
      else if(nHNhXpATrK == qmiidNSLom){qpwhzVZTJk = true;}
      if(rgseVhqGqz == JHqFyjKMVk){CDxDKZAJAg = true;}
      else if(JHqFyjKMVk == rgseVhqGqz){TZXheHTEFk = true;}
      if(BEVHcGiTUq == DsGLoeLRgN){QIJbQaqraU = true;}
      else if(DsGLoeLRgN == BEVHcGiTUq){fXNOMbagpb = true;}
      if(bPsSDYOSFT == SAHmMRfGGl){gVgHppqfbz = true;}
      else if(SAHmMRfGGl == bPsSDYOSFT){XVQeMEjHsI = true;}
      if(rMaMYbgoep == ZEBIGzwGiF){HUlBOMfJCh = true;}
      if(NBqzzmQaGX == iIHQruBCrs){pHVifqhklZ = true;}
      if(dyqyLbmZbx == eilerJAEsg){nJxjKfVoNU = true;}
      while(ZEBIGzwGiF == rMaMYbgoep){zgopeghLWD = true;}
      while(iIHQruBCrs == iIHQruBCrs){dSuFCSbhUX = true;}
      while(eilerJAEsg == eilerJAEsg){uscgMyIsVZ = true;}
      if(EEGiLzrxEo == true){EEGiLzrxEo = false;}
      if(hEhbdKsqtR == true){hEhbdKsqtR = false;}
      if(QdNNHpRVQw == true){QdNNHpRVQw = false;}
      if(zrMCAeCXFr == true){zrMCAeCXFr = false;}
      if(CDxDKZAJAg == true){CDxDKZAJAg = false;}
      if(QIJbQaqraU == true){QIJbQaqraU = false;}
      if(gVgHppqfbz == true){gVgHppqfbz = false;}
      if(HUlBOMfJCh == true){HUlBOMfJCh = false;}
      if(pHVifqhklZ == true){pHVifqhklZ = false;}
      if(nJxjKfVoNU == true){nJxjKfVoNU = false;}
      if(hUhBZuWHMD == true){hUhBZuWHMD = false;}
      if(ugpseZAyby == true){ugpseZAyby = false;}
      if(HGtBKxXBqh == true){HGtBKxXBqh = false;}
      if(qpwhzVZTJk == true){qpwhzVZTJk = false;}
      if(TZXheHTEFk == true){TZXheHTEFk = false;}
      if(fXNOMbagpb == true){fXNOMbagpb = false;}
      if(XVQeMEjHsI == true){XVQeMEjHsI = false;}
      if(zgopeghLWD == true){zgopeghLWD = false;}
      if(dSuFCSbhUX == true){dSuFCSbhUX = false;}
      if(uscgMyIsVZ == true){uscgMyIsVZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQFQDIBCBG
{ 
  void MHMlkybYfw()
  { 
      bool MXuEUQcXKR = false;
      bool haptEosRQh = false;
      bool qatCaDVPBX = false;
      bool AOaVmUDwnf = false;
      bool wXSddUjCel = false;
      bool EnwSzkdscQ = false;
      bool tNVlRSATGi = false;
      bool kwcjlSIPXG = false;
      bool TTjOSMRHVC = false;
      bool pJTXkiCfMK = false;
      bool UPuuAILMgg = false;
      bool cOUWxacGTF = false;
      bool BryErbcEyD = false;
      bool PcCNkDXnOK = false;
      bool AFanZbnwaK = false;
      bool FuMHJcQqDY = false;
      bool eGNdQzLHks = false;
      bool DnrIEwQJeQ = false;
      bool mfdnxUPuDI = false;
      bool lfkoftrxXZ = false;
      string JqkcuuctPm;
      string PQlmrCJmyl;
      string flZsOiRNcK;
      string KNshjuSHLi;
      string JYxWMiswIp;
      string yxyWPXQrOM;
      string cPREbCXDDw;
      string jBaObHnDff;
      string oVEmMNPVRM;
      string daszGtGrtK;
      string KosMGwViuI;
      string iNLiWHKerN;
      string lBlpRIIbIg;
      string AwJUUzcqgP;
      string rfaJdQOJbz;
      string jaAfXIDCux;
      string nsaNHmEqNX;
      string dSycVGabMA;
      string szAJxYucwL;
      string wZwiayFMBq;
      if(JqkcuuctPm == KosMGwViuI){MXuEUQcXKR = true;}
      else if(KosMGwViuI == JqkcuuctPm){UPuuAILMgg = true;}
      if(PQlmrCJmyl == iNLiWHKerN){haptEosRQh = true;}
      else if(iNLiWHKerN == PQlmrCJmyl){cOUWxacGTF = true;}
      if(flZsOiRNcK == lBlpRIIbIg){qatCaDVPBX = true;}
      else if(lBlpRIIbIg == flZsOiRNcK){BryErbcEyD = true;}
      if(KNshjuSHLi == AwJUUzcqgP){AOaVmUDwnf = true;}
      else if(AwJUUzcqgP == KNshjuSHLi){PcCNkDXnOK = true;}
      if(JYxWMiswIp == rfaJdQOJbz){wXSddUjCel = true;}
      else if(rfaJdQOJbz == JYxWMiswIp){AFanZbnwaK = true;}
      if(yxyWPXQrOM == jaAfXIDCux){EnwSzkdscQ = true;}
      else if(jaAfXIDCux == yxyWPXQrOM){FuMHJcQqDY = true;}
      if(cPREbCXDDw == nsaNHmEqNX){tNVlRSATGi = true;}
      else if(nsaNHmEqNX == cPREbCXDDw){eGNdQzLHks = true;}
      if(jBaObHnDff == dSycVGabMA){kwcjlSIPXG = true;}
      if(oVEmMNPVRM == szAJxYucwL){TTjOSMRHVC = true;}
      if(daszGtGrtK == wZwiayFMBq){pJTXkiCfMK = true;}
      while(dSycVGabMA == jBaObHnDff){DnrIEwQJeQ = true;}
      while(szAJxYucwL == szAJxYucwL){mfdnxUPuDI = true;}
      while(wZwiayFMBq == wZwiayFMBq){lfkoftrxXZ = true;}
      if(MXuEUQcXKR == true){MXuEUQcXKR = false;}
      if(haptEosRQh == true){haptEosRQh = false;}
      if(qatCaDVPBX == true){qatCaDVPBX = false;}
      if(AOaVmUDwnf == true){AOaVmUDwnf = false;}
      if(wXSddUjCel == true){wXSddUjCel = false;}
      if(EnwSzkdscQ == true){EnwSzkdscQ = false;}
      if(tNVlRSATGi == true){tNVlRSATGi = false;}
      if(kwcjlSIPXG == true){kwcjlSIPXG = false;}
      if(TTjOSMRHVC == true){TTjOSMRHVC = false;}
      if(pJTXkiCfMK == true){pJTXkiCfMK = false;}
      if(UPuuAILMgg == true){UPuuAILMgg = false;}
      if(cOUWxacGTF == true){cOUWxacGTF = false;}
      if(BryErbcEyD == true){BryErbcEyD = false;}
      if(PcCNkDXnOK == true){PcCNkDXnOK = false;}
      if(AFanZbnwaK == true){AFanZbnwaK = false;}
      if(FuMHJcQqDY == true){FuMHJcQqDY = false;}
      if(eGNdQzLHks == true){eGNdQzLHks = false;}
      if(DnrIEwQJeQ == true){DnrIEwQJeQ = false;}
      if(mfdnxUPuDI == true){mfdnxUPuDI = false;}
      if(lfkoftrxXZ == true){lfkoftrxXZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TTKNRYSLBJ
{ 
  void uzcjESddXE()
  { 
      bool CBarzHRjPV = false;
      bool SUtVYTYPqM = false;
      bool xsiudxRnQs = false;
      bool SVbiXZVgPK = false;
      bool ZTKLHAWBCT = false;
      bool YNjkFIReNB = false;
      bool pcSWDxrKxz = false;
      bool yrzfmciXnd = false;
      bool aQlxTEkpdO = false;
      bool IpSNUwBnHJ = false;
      bool HLEDVgNDyb = false;
      bool ZsqjaZqVCy = false;
      bool LCghqIYkKp = false;
      bool btQdVOLhal = false;
      bool qhrBoOzimu = false;
      bool FelJxFeVMN = false;
      bool IcsHAecMNM = false;
      bool NItPHdJesb = false;
      bool IpyOjwIGfQ = false;
      bool joVNdNojAJ = false;
      string TUEdPIuJMI;
      string HBRjfwQeJu;
      string sajRdPeasi;
      string EiIJsJULGE;
      string ZreDupdMPV;
      string RoPwerjlAA;
      string dTPcEYsHpW;
      string bFXFVBwgVm;
      string lRLWROTLeA;
      string ZhKGZFbByW;
      string xWVrtLQKac;
      string wCPMOLIsLp;
      string FgbpwstReP;
      string ZtizpPwScF;
      string xIkBEWRxrO;
      string xhpIRPtfuA;
      string QzfKDBTQWz;
      string OoQFrwwZkZ;
      string awZPSqEaga;
      string UQWbnycayC;
      if(TUEdPIuJMI == xWVrtLQKac){CBarzHRjPV = true;}
      else if(xWVrtLQKac == TUEdPIuJMI){HLEDVgNDyb = true;}
      if(HBRjfwQeJu == wCPMOLIsLp){SUtVYTYPqM = true;}
      else if(wCPMOLIsLp == HBRjfwQeJu){ZsqjaZqVCy = true;}
      if(sajRdPeasi == FgbpwstReP){xsiudxRnQs = true;}
      else if(FgbpwstReP == sajRdPeasi){LCghqIYkKp = true;}
      if(EiIJsJULGE == ZtizpPwScF){SVbiXZVgPK = true;}
      else if(ZtizpPwScF == EiIJsJULGE){btQdVOLhal = true;}
      if(ZreDupdMPV == xIkBEWRxrO){ZTKLHAWBCT = true;}
      else if(xIkBEWRxrO == ZreDupdMPV){qhrBoOzimu = true;}
      if(RoPwerjlAA == xhpIRPtfuA){YNjkFIReNB = true;}
      else if(xhpIRPtfuA == RoPwerjlAA){FelJxFeVMN = true;}
      if(dTPcEYsHpW == QzfKDBTQWz){pcSWDxrKxz = true;}
      else if(QzfKDBTQWz == dTPcEYsHpW){IcsHAecMNM = true;}
      if(bFXFVBwgVm == OoQFrwwZkZ){yrzfmciXnd = true;}
      if(lRLWROTLeA == awZPSqEaga){aQlxTEkpdO = true;}
      if(ZhKGZFbByW == UQWbnycayC){IpSNUwBnHJ = true;}
      while(OoQFrwwZkZ == bFXFVBwgVm){NItPHdJesb = true;}
      while(awZPSqEaga == awZPSqEaga){IpyOjwIGfQ = true;}
      while(UQWbnycayC == UQWbnycayC){joVNdNojAJ = true;}
      if(CBarzHRjPV == true){CBarzHRjPV = false;}
      if(SUtVYTYPqM == true){SUtVYTYPqM = false;}
      if(xsiudxRnQs == true){xsiudxRnQs = false;}
      if(SVbiXZVgPK == true){SVbiXZVgPK = false;}
      if(ZTKLHAWBCT == true){ZTKLHAWBCT = false;}
      if(YNjkFIReNB == true){YNjkFIReNB = false;}
      if(pcSWDxrKxz == true){pcSWDxrKxz = false;}
      if(yrzfmciXnd == true){yrzfmciXnd = false;}
      if(aQlxTEkpdO == true){aQlxTEkpdO = false;}
      if(IpSNUwBnHJ == true){IpSNUwBnHJ = false;}
      if(HLEDVgNDyb == true){HLEDVgNDyb = false;}
      if(ZsqjaZqVCy == true){ZsqjaZqVCy = false;}
      if(LCghqIYkKp == true){LCghqIYkKp = false;}
      if(btQdVOLhal == true){btQdVOLhal = false;}
      if(qhrBoOzimu == true){qhrBoOzimu = false;}
      if(FelJxFeVMN == true){FelJxFeVMN = false;}
      if(IcsHAecMNM == true){IcsHAecMNM = false;}
      if(NItPHdJesb == true){NItPHdJesb = false;}
      if(IpyOjwIGfQ == true){IpyOjwIGfQ = false;}
      if(joVNdNojAJ == true){joVNdNojAJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFHTYZMQVS
{ 
  void oEWRHrxAdr()
  { 
      bool NMLwaqWbJD = false;
      bool ohFzAPeVeN = false;
      bool NHrrdFNxmc = false;
      bool hHALObnPoF = false;
      bool ueVaVqZYWU = false;
      bool YajSoGUSRV = false;
      bool cZnfUghsjY = false;
      bool aPgZShkQWl = false;
      bool enZSEHXgWI = false;
      bool HVxTbVqoGn = false;
      bool JfoxsJtJAG = false;
      bool UDwepozVaN = false;
      bool JAVbRFRMyw = false;
      bool quKhcyzbYu = false;
      bool MNfQmDYRcm = false;
      bool WUNreIJMfn = false;
      bool qgLDOYsOCq = false;
      bool oWwfAuTFoO = false;
      bool fziLZVgRCT = false;
      bool nlwkDfCbBN = false;
      string XbQFAFqmcg;
      string DocGoDcnVB;
      string SLgWdJJxdX;
      string FoidODMTjt;
      string KiesLfJAqD;
      string pHpqZLutaq;
      string wsIFaNFzqk;
      string pJEapigmKy;
      string zJGagyzqDD;
      string ISrryQZYRx;
      string ZKIFMgDPBp;
      string dHibrlmhXb;
      string ONuncXQLcZ;
      string JIUMXnAANA;
      string ujpNYAiPzM;
      string cqApiMPUbo;
      string PqlafVlVED;
      string klUXgeWgOc;
      string nALQwRHedL;
      string YfYXjDxOgC;
      if(XbQFAFqmcg == ZKIFMgDPBp){NMLwaqWbJD = true;}
      else if(ZKIFMgDPBp == XbQFAFqmcg){JfoxsJtJAG = true;}
      if(DocGoDcnVB == dHibrlmhXb){ohFzAPeVeN = true;}
      else if(dHibrlmhXb == DocGoDcnVB){UDwepozVaN = true;}
      if(SLgWdJJxdX == ONuncXQLcZ){NHrrdFNxmc = true;}
      else if(ONuncXQLcZ == SLgWdJJxdX){JAVbRFRMyw = true;}
      if(FoidODMTjt == JIUMXnAANA){hHALObnPoF = true;}
      else if(JIUMXnAANA == FoidODMTjt){quKhcyzbYu = true;}
      if(KiesLfJAqD == ujpNYAiPzM){ueVaVqZYWU = true;}
      else if(ujpNYAiPzM == KiesLfJAqD){MNfQmDYRcm = true;}
      if(pHpqZLutaq == cqApiMPUbo){YajSoGUSRV = true;}
      else if(cqApiMPUbo == pHpqZLutaq){WUNreIJMfn = true;}
      if(wsIFaNFzqk == PqlafVlVED){cZnfUghsjY = true;}
      else if(PqlafVlVED == wsIFaNFzqk){qgLDOYsOCq = true;}
      if(pJEapigmKy == klUXgeWgOc){aPgZShkQWl = true;}
      if(zJGagyzqDD == nALQwRHedL){enZSEHXgWI = true;}
      if(ISrryQZYRx == YfYXjDxOgC){HVxTbVqoGn = true;}
      while(klUXgeWgOc == pJEapigmKy){oWwfAuTFoO = true;}
      while(nALQwRHedL == nALQwRHedL){fziLZVgRCT = true;}
      while(YfYXjDxOgC == YfYXjDxOgC){nlwkDfCbBN = true;}
      if(NMLwaqWbJD == true){NMLwaqWbJD = false;}
      if(ohFzAPeVeN == true){ohFzAPeVeN = false;}
      if(NHrrdFNxmc == true){NHrrdFNxmc = false;}
      if(hHALObnPoF == true){hHALObnPoF = false;}
      if(ueVaVqZYWU == true){ueVaVqZYWU = false;}
      if(YajSoGUSRV == true){YajSoGUSRV = false;}
      if(cZnfUghsjY == true){cZnfUghsjY = false;}
      if(aPgZShkQWl == true){aPgZShkQWl = false;}
      if(enZSEHXgWI == true){enZSEHXgWI = false;}
      if(HVxTbVqoGn == true){HVxTbVqoGn = false;}
      if(JfoxsJtJAG == true){JfoxsJtJAG = false;}
      if(UDwepozVaN == true){UDwepozVaN = false;}
      if(JAVbRFRMyw == true){JAVbRFRMyw = false;}
      if(quKhcyzbYu == true){quKhcyzbYu = false;}
      if(MNfQmDYRcm == true){MNfQmDYRcm = false;}
      if(WUNreIJMfn == true){WUNreIJMfn = false;}
      if(qgLDOYsOCq == true){qgLDOYsOCq = false;}
      if(oWwfAuTFoO == true){oWwfAuTFoO = false;}
      if(fziLZVgRCT == true){fziLZVgRCT = false;}
      if(nlwkDfCbBN == true){nlwkDfCbBN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTSVJRFNOQ
{ 
  void gGPAQXUKxM()
  { 
      bool PKAuSXkZbr = false;
      bool PNnzmPzJle = false;
      bool hHsXopNLIW = false;
      bool oMAXPODnDc = false;
      bool CGGMNrdBMu = false;
      bool LYeZfIRcFb = false;
      bool JZREDCMPiX = false;
      bool MKFJcbBfJx = false;
      bool LMyNLPhZrH = false;
      bool xZibScnBJK = false;
      bool eORnhASVxE = false;
      bool GkSIQxaEsn = false;
      bool UmXaalbdpA = false;
      bool mzWzRxtJeL = false;
      bool wLbmAMHaKV = false;
      bool BjIUorqpNu = false;
      bool YoewQHNTpS = false;
      bool CRYgqIKjaN = false;
      bool eBTTzDpCJZ = false;
      bool GDuimHgfWs = false;
      string WJPIVoqQGZ;
      string iorHixVmky;
      string QOuRmcFwcE;
      string wzbkaFesCL;
      string cKuPooFWwP;
      string BsEwJIOyUr;
      string iumCdiNGgd;
      string RcjZVGTeby;
      string XhzMDCuebR;
      string pgXKbhWrlF;
      string byoSyXIeaC;
      string ojVWTAuZyb;
      string nhePmkEZxm;
      string jasWVYrgOe;
      string sPEYcGKApa;
      string lwtKQsTZfN;
      string TigmSOpzAu;
      string IOLThXdGlf;
      string ZDiWAmfiFc;
      string FRAAKKiQFO;
      if(WJPIVoqQGZ == byoSyXIeaC){PKAuSXkZbr = true;}
      else if(byoSyXIeaC == WJPIVoqQGZ){eORnhASVxE = true;}
      if(iorHixVmky == ojVWTAuZyb){PNnzmPzJle = true;}
      else if(ojVWTAuZyb == iorHixVmky){GkSIQxaEsn = true;}
      if(QOuRmcFwcE == nhePmkEZxm){hHsXopNLIW = true;}
      else if(nhePmkEZxm == QOuRmcFwcE){UmXaalbdpA = true;}
      if(wzbkaFesCL == jasWVYrgOe){oMAXPODnDc = true;}
      else if(jasWVYrgOe == wzbkaFesCL){mzWzRxtJeL = true;}
      if(cKuPooFWwP == sPEYcGKApa){CGGMNrdBMu = true;}
      else if(sPEYcGKApa == cKuPooFWwP){wLbmAMHaKV = true;}
      if(BsEwJIOyUr == lwtKQsTZfN){LYeZfIRcFb = true;}
      else if(lwtKQsTZfN == BsEwJIOyUr){BjIUorqpNu = true;}
      if(iumCdiNGgd == TigmSOpzAu){JZREDCMPiX = true;}
      else if(TigmSOpzAu == iumCdiNGgd){YoewQHNTpS = true;}
      if(RcjZVGTeby == IOLThXdGlf){MKFJcbBfJx = true;}
      if(XhzMDCuebR == ZDiWAmfiFc){LMyNLPhZrH = true;}
      if(pgXKbhWrlF == FRAAKKiQFO){xZibScnBJK = true;}
      while(IOLThXdGlf == RcjZVGTeby){CRYgqIKjaN = true;}
      while(ZDiWAmfiFc == ZDiWAmfiFc){eBTTzDpCJZ = true;}
      while(FRAAKKiQFO == FRAAKKiQFO){GDuimHgfWs = true;}
      if(PKAuSXkZbr == true){PKAuSXkZbr = false;}
      if(PNnzmPzJle == true){PNnzmPzJle = false;}
      if(hHsXopNLIW == true){hHsXopNLIW = false;}
      if(oMAXPODnDc == true){oMAXPODnDc = false;}
      if(CGGMNrdBMu == true){CGGMNrdBMu = false;}
      if(LYeZfIRcFb == true){LYeZfIRcFb = false;}
      if(JZREDCMPiX == true){JZREDCMPiX = false;}
      if(MKFJcbBfJx == true){MKFJcbBfJx = false;}
      if(LMyNLPhZrH == true){LMyNLPhZrH = false;}
      if(xZibScnBJK == true){xZibScnBJK = false;}
      if(eORnhASVxE == true){eORnhASVxE = false;}
      if(GkSIQxaEsn == true){GkSIQxaEsn = false;}
      if(UmXaalbdpA == true){UmXaalbdpA = false;}
      if(mzWzRxtJeL == true){mzWzRxtJeL = false;}
      if(wLbmAMHaKV == true){wLbmAMHaKV = false;}
      if(BjIUorqpNu == true){BjIUorqpNu = false;}
      if(YoewQHNTpS == true){YoewQHNTpS = false;}
      if(CRYgqIKjaN == true){CRYgqIKjaN = false;}
      if(eBTTzDpCJZ == true){eBTTzDpCJZ = false;}
      if(GDuimHgfWs == true){GDuimHgfWs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMXIAUYMBI
{ 
  void fUTUerqNFx()
  { 
      bool eOkOttAOrQ = false;
      bool oJLdZGrFnB = false;
      bool ZRcbqwPlKM = false;
      bool YZzjSxcIVu = false;
      bool elGTehTqwX = false;
      bool CzwxcNkJWy = false;
      bool dODfqOJbLc = false;
      bool cijrWnKJwJ = false;
      bool bYpmJYcBHE = false;
      bool LSkXQPiabP = false;
      bool XqeTtSOEan = false;
      bool DbNNVFYPWR = false;
      bool lIUGQKyMaG = false;
      bool FjgflksWsq = false;
      bool KYZSBiFWCL = false;
      bool qSDJdOWYCj = false;
      bool TCcUiTtgbj = false;
      bool LCVeHMhCFg = false;
      bool EbKPOlfWCW = false;
      bool NUTJWIwFih = false;
      string IUjMgfwPYl;
      string lkVDBByCmz;
      string iknOEKguRW;
      string cAxlesqFCa;
      string OVqYjLWmcj;
      string IjSjiXfVIV;
      string zAxBJlmiXH;
      string JrAMjMsPdr;
      string nsShOsgNDH;
      string NUxfaOXpPy;
      string YnOVZPiGzV;
      string dQrPhFhPmP;
      string EYfQtnuUkV;
      string oDzeTzdwHy;
      string JaOgcwcgxV;
      string fIDztzIybk;
      string UOVdgaRNui;
      string akHnGdKymx;
      string LOWPpfAzjT;
      string qeUVdtFjzC;
      if(IUjMgfwPYl == YnOVZPiGzV){eOkOttAOrQ = true;}
      else if(YnOVZPiGzV == IUjMgfwPYl){XqeTtSOEan = true;}
      if(lkVDBByCmz == dQrPhFhPmP){oJLdZGrFnB = true;}
      else if(dQrPhFhPmP == lkVDBByCmz){DbNNVFYPWR = true;}
      if(iknOEKguRW == EYfQtnuUkV){ZRcbqwPlKM = true;}
      else if(EYfQtnuUkV == iknOEKguRW){lIUGQKyMaG = true;}
      if(cAxlesqFCa == oDzeTzdwHy){YZzjSxcIVu = true;}
      else if(oDzeTzdwHy == cAxlesqFCa){FjgflksWsq = true;}
      if(OVqYjLWmcj == JaOgcwcgxV){elGTehTqwX = true;}
      else if(JaOgcwcgxV == OVqYjLWmcj){KYZSBiFWCL = true;}
      if(IjSjiXfVIV == fIDztzIybk){CzwxcNkJWy = true;}
      else if(fIDztzIybk == IjSjiXfVIV){qSDJdOWYCj = true;}
      if(zAxBJlmiXH == UOVdgaRNui){dODfqOJbLc = true;}
      else if(UOVdgaRNui == zAxBJlmiXH){TCcUiTtgbj = true;}
      if(JrAMjMsPdr == akHnGdKymx){cijrWnKJwJ = true;}
      if(nsShOsgNDH == LOWPpfAzjT){bYpmJYcBHE = true;}
      if(NUxfaOXpPy == qeUVdtFjzC){LSkXQPiabP = true;}
      while(akHnGdKymx == JrAMjMsPdr){LCVeHMhCFg = true;}
      while(LOWPpfAzjT == LOWPpfAzjT){EbKPOlfWCW = true;}
      while(qeUVdtFjzC == qeUVdtFjzC){NUTJWIwFih = true;}
      if(eOkOttAOrQ == true){eOkOttAOrQ = false;}
      if(oJLdZGrFnB == true){oJLdZGrFnB = false;}
      if(ZRcbqwPlKM == true){ZRcbqwPlKM = false;}
      if(YZzjSxcIVu == true){YZzjSxcIVu = false;}
      if(elGTehTqwX == true){elGTehTqwX = false;}
      if(CzwxcNkJWy == true){CzwxcNkJWy = false;}
      if(dODfqOJbLc == true){dODfqOJbLc = false;}
      if(cijrWnKJwJ == true){cijrWnKJwJ = false;}
      if(bYpmJYcBHE == true){bYpmJYcBHE = false;}
      if(LSkXQPiabP == true){LSkXQPiabP = false;}
      if(XqeTtSOEan == true){XqeTtSOEan = false;}
      if(DbNNVFYPWR == true){DbNNVFYPWR = false;}
      if(lIUGQKyMaG == true){lIUGQKyMaG = false;}
      if(FjgflksWsq == true){FjgflksWsq = false;}
      if(KYZSBiFWCL == true){KYZSBiFWCL = false;}
      if(qSDJdOWYCj == true){qSDJdOWYCj = false;}
      if(TCcUiTtgbj == true){TCcUiTtgbj = false;}
      if(LCVeHMhCFg == true){LCVeHMhCFg = false;}
      if(EbKPOlfWCW == true){EbKPOlfWCW = false;}
      if(NUTJWIwFih == true){NUTJWIwFih = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRRQFJQGKV
{ 
  void EkuizMOBqo()
  { 
      bool iFVWTnUASz = false;
      bool pLdCnSwFZn = false;
      bool oPihYVdHnJ = false;
      bool DuKSafRMGl = false;
      bool kAVHpoabbM = false;
      bool jowRZSVnxx = false;
      bool KNMJuuALaI = false;
      bool BjznDntbrj = false;
      bool uBfaYNysrH = false;
      bool JdPIaWnLLt = false;
      bool oPASLApHOl = false;
      bool YtuNCIhkkh = false;
      bool wHSTzWUpMf = false;
      bool AhPxteAMPX = false;
      bool XpdGhOhBFS = false;
      bool oCZdyhxgTn = false;
      bool fzuhlqeySX = false;
      bool HUVMJGcMkj = false;
      bool oSktqxHkzM = false;
      bool gTsarYuwTq = false;
      string uYiNCeGocC;
      string AeEYzqoJLV;
      string YpHJXbUDdG;
      string WursUIRcbA;
      string ASwtekEDBg;
      string puPuzFQZpa;
      string KCLWfFmKDp;
      string YLhLVGtNdm;
      string WQCxQaexsP;
      string qrmAoxGZOY;
      string yszKHeNDYs;
      string KDuDDsANFE;
      string apQmygXgWX;
      string zUyFncRqpl;
      string NbXAFnwjxw;
      string xsTJyIbLMZ;
      string GffBtpEpOZ;
      string bIXTpyRQhK;
      string kmjaaGAoHf;
      string AFePeguWFP;
      if(uYiNCeGocC == yszKHeNDYs){iFVWTnUASz = true;}
      else if(yszKHeNDYs == uYiNCeGocC){oPASLApHOl = true;}
      if(AeEYzqoJLV == KDuDDsANFE){pLdCnSwFZn = true;}
      else if(KDuDDsANFE == AeEYzqoJLV){YtuNCIhkkh = true;}
      if(YpHJXbUDdG == apQmygXgWX){oPihYVdHnJ = true;}
      else if(apQmygXgWX == YpHJXbUDdG){wHSTzWUpMf = true;}
      if(WursUIRcbA == zUyFncRqpl){DuKSafRMGl = true;}
      else if(zUyFncRqpl == WursUIRcbA){AhPxteAMPX = true;}
      if(ASwtekEDBg == NbXAFnwjxw){kAVHpoabbM = true;}
      else if(NbXAFnwjxw == ASwtekEDBg){XpdGhOhBFS = true;}
      if(puPuzFQZpa == xsTJyIbLMZ){jowRZSVnxx = true;}
      else if(xsTJyIbLMZ == puPuzFQZpa){oCZdyhxgTn = true;}
      if(KCLWfFmKDp == GffBtpEpOZ){KNMJuuALaI = true;}
      else if(GffBtpEpOZ == KCLWfFmKDp){fzuhlqeySX = true;}
      if(YLhLVGtNdm == bIXTpyRQhK){BjznDntbrj = true;}
      if(WQCxQaexsP == kmjaaGAoHf){uBfaYNysrH = true;}
      if(qrmAoxGZOY == AFePeguWFP){JdPIaWnLLt = true;}
      while(bIXTpyRQhK == YLhLVGtNdm){HUVMJGcMkj = true;}
      while(kmjaaGAoHf == kmjaaGAoHf){oSktqxHkzM = true;}
      while(AFePeguWFP == AFePeguWFP){gTsarYuwTq = true;}
      if(iFVWTnUASz == true){iFVWTnUASz = false;}
      if(pLdCnSwFZn == true){pLdCnSwFZn = false;}
      if(oPihYVdHnJ == true){oPihYVdHnJ = false;}
      if(DuKSafRMGl == true){DuKSafRMGl = false;}
      if(kAVHpoabbM == true){kAVHpoabbM = false;}
      if(jowRZSVnxx == true){jowRZSVnxx = false;}
      if(KNMJuuALaI == true){KNMJuuALaI = false;}
      if(BjznDntbrj == true){BjznDntbrj = false;}
      if(uBfaYNysrH == true){uBfaYNysrH = false;}
      if(JdPIaWnLLt == true){JdPIaWnLLt = false;}
      if(oPASLApHOl == true){oPASLApHOl = false;}
      if(YtuNCIhkkh == true){YtuNCIhkkh = false;}
      if(wHSTzWUpMf == true){wHSTzWUpMf = false;}
      if(AhPxteAMPX == true){AhPxteAMPX = false;}
      if(XpdGhOhBFS == true){XpdGhOhBFS = false;}
      if(oCZdyhxgTn == true){oCZdyhxgTn = false;}
      if(fzuhlqeySX == true){fzuhlqeySX = false;}
      if(HUVMJGcMkj == true){HUVMJGcMkj = false;}
      if(oSktqxHkzM == true){oSktqxHkzM = false;}
      if(gTsarYuwTq == true){gTsarYuwTq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SWUVPEQWEB
{ 
  void lsAeQaqhyV()
  { 
      bool DxhhBRzCAj = false;
      bool ntWHThZUFw = false;
      bool tJaQVJKWFi = false;
      bool pPgjDxAyWF = false;
      bool cxDEtMeXTF = false;
      bool wIDZGsWRMq = false;
      bool GbwRsYMmEV = false;
      bool gaxzSwGVVJ = false;
      bool dmDzlgLGdJ = false;
      bool ZileyAAlKV = false;
      bool zrSxYUKEHJ = false;
      bool mAuCMTYxeM = false;
      bool MGJtwyoSAR = false;
      bool uTLAJlTFaR = false;
      bool WGzTWZmiRe = false;
      bool bDHyIsiYBa = false;
      bool frDoNSotsa = false;
      bool ASVNoFGoXV = false;
      bool KFAVprMMrP = false;
      bool CuEAkdDKFD = false;
      string CKbFjXqHoa;
      string EfdjSuXPfc;
      string QUretBCcWF;
      string QIZZSGRicG;
      string GHdxpcAExz;
      string UmFeTgSxKi;
      string UOkiKuFEQL;
      string cnmYWJqunR;
      string AyeXkcDtFk;
      string nUYtlqWtlu;
      string WwmlVfAfIK;
      string pWIrhWiMyg;
      string qKyfXHOsme;
      string lwIstEKsBE;
      string cWltuQMfLO;
      string HJwEEMxHNO;
      string QGscXtNPyc;
      string MpKsETYDkG;
      string tigYXbADnh;
      string GCemnVdJWA;
      if(CKbFjXqHoa == WwmlVfAfIK){DxhhBRzCAj = true;}
      else if(WwmlVfAfIK == CKbFjXqHoa){zrSxYUKEHJ = true;}
      if(EfdjSuXPfc == pWIrhWiMyg){ntWHThZUFw = true;}
      else if(pWIrhWiMyg == EfdjSuXPfc){mAuCMTYxeM = true;}
      if(QUretBCcWF == qKyfXHOsme){tJaQVJKWFi = true;}
      else if(qKyfXHOsme == QUretBCcWF){MGJtwyoSAR = true;}
      if(QIZZSGRicG == lwIstEKsBE){pPgjDxAyWF = true;}
      else if(lwIstEKsBE == QIZZSGRicG){uTLAJlTFaR = true;}
      if(GHdxpcAExz == cWltuQMfLO){cxDEtMeXTF = true;}
      else if(cWltuQMfLO == GHdxpcAExz){WGzTWZmiRe = true;}
      if(UmFeTgSxKi == HJwEEMxHNO){wIDZGsWRMq = true;}
      else if(HJwEEMxHNO == UmFeTgSxKi){bDHyIsiYBa = true;}
      if(UOkiKuFEQL == QGscXtNPyc){GbwRsYMmEV = true;}
      else if(QGscXtNPyc == UOkiKuFEQL){frDoNSotsa = true;}
      if(cnmYWJqunR == MpKsETYDkG){gaxzSwGVVJ = true;}
      if(AyeXkcDtFk == tigYXbADnh){dmDzlgLGdJ = true;}
      if(nUYtlqWtlu == GCemnVdJWA){ZileyAAlKV = true;}
      while(MpKsETYDkG == cnmYWJqunR){ASVNoFGoXV = true;}
      while(tigYXbADnh == tigYXbADnh){KFAVprMMrP = true;}
      while(GCemnVdJWA == GCemnVdJWA){CuEAkdDKFD = true;}
      if(DxhhBRzCAj == true){DxhhBRzCAj = false;}
      if(ntWHThZUFw == true){ntWHThZUFw = false;}
      if(tJaQVJKWFi == true){tJaQVJKWFi = false;}
      if(pPgjDxAyWF == true){pPgjDxAyWF = false;}
      if(cxDEtMeXTF == true){cxDEtMeXTF = false;}
      if(wIDZGsWRMq == true){wIDZGsWRMq = false;}
      if(GbwRsYMmEV == true){GbwRsYMmEV = false;}
      if(gaxzSwGVVJ == true){gaxzSwGVVJ = false;}
      if(dmDzlgLGdJ == true){dmDzlgLGdJ = false;}
      if(ZileyAAlKV == true){ZileyAAlKV = false;}
      if(zrSxYUKEHJ == true){zrSxYUKEHJ = false;}
      if(mAuCMTYxeM == true){mAuCMTYxeM = false;}
      if(MGJtwyoSAR == true){MGJtwyoSAR = false;}
      if(uTLAJlTFaR == true){uTLAJlTFaR = false;}
      if(WGzTWZmiRe == true){WGzTWZmiRe = false;}
      if(bDHyIsiYBa == true){bDHyIsiYBa = false;}
      if(frDoNSotsa == true){frDoNSotsa = false;}
      if(ASVNoFGoXV == true){ASVNoFGoXV = false;}
      if(KFAVprMMrP == true){KFAVprMMrP = false;}
      if(CuEAkdDKFD == true){CuEAkdDKFD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VIHUNNSPCA
{ 
  void ZHaAFTpGuC()
  { 
      bool EMxFdcPVZX = false;
      bool cUykgmpCUJ = false;
      bool TMEjMNudyj = false;
      bool xAHOZEGVnL = false;
      bool BFPThGTJUh = false;
      bool ikpGDrINsQ = false;
      bool glWpZbMjLc = false;
      bool gUOJIOwkBF = false;
      bool tlJQALKBKg = false;
      bool urcXdOhZsG = false;
      bool siyqBOWgxn = false;
      bool wXLmWucGpO = false;
      bool QLYdgnrpes = false;
      bool gVquMKmROk = false;
      bool odDWkXgoBi = false;
      bool kbjeogJTJM = false;
      bool VfBDHZfQZL = false;
      bool HLqEYmHCsJ = false;
      bool HCouIElMGe = false;
      bool ATHBOIbzPK = false;
      string zVHXWrwWDT;
      string ZtDSyciLmG;
      string PwfIIjRjUU;
      string mYcHhaBBoS;
      string fcGSFmFZYy;
      string UIRrbCpyPm;
      string aLBhfBRwjW;
      string bhWUampMDU;
      string drLWAdGkfe;
      string kClCrTaXlD;
      string VJoBWmlxQn;
      string McutIhAehC;
      string tfPElYuUbH;
      string MRZzzUCJzM;
      string rJUqSHHrsJ;
      string SupjIosjPy;
      string qRUJauCutn;
      string fpeUKkLXle;
      string QDaRnRapqK;
      string aRtBVZnKQX;
      if(zVHXWrwWDT == VJoBWmlxQn){EMxFdcPVZX = true;}
      else if(VJoBWmlxQn == zVHXWrwWDT){siyqBOWgxn = true;}
      if(ZtDSyciLmG == McutIhAehC){cUykgmpCUJ = true;}
      else if(McutIhAehC == ZtDSyciLmG){wXLmWucGpO = true;}
      if(PwfIIjRjUU == tfPElYuUbH){TMEjMNudyj = true;}
      else if(tfPElYuUbH == PwfIIjRjUU){QLYdgnrpes = true;}
      if(mYcHhaBBoS == MRZzzUCJzM){xAHOZEGVnL = true;}
      else if(MRZzzUCJzM == mYcHhaBBoS){gVquMKmROk = true;}
      if(fcGSFmFZYy == rJUqSHHrsJ){BFPThGTJUh = true;}
      else if(rJUqSHHrsJ == fcGSFmFZYy){odDWkXgoBi = true;}
      if(UIRrbCpyPm == SupjIosjPy){ikpGDrINsQ = true;}
      else if(SupjIosjPy == UIRrbCpyPm){kbjeogJTJM = true;}
      if(aLBhfBRwjW == qRUJauCutn){glWpZbMjLc = true;}
      else if(qRUJauCutn == aLBhfBRwjW){VfBDHZfQZL = true;}
      if(bhWUampMDU == fpeUKkLXle){gUOJIOwkBF = true;}
      if(drLWAdGkfe == QDaRnRapqK){tlJQALKBKg = true;}
      if(kClCrTaXlD == aRtBVZnKQX){urcXdOhZsG = true;}
      while(fpeUKkLXle == bhWUampMDU){HLqEYmHCsJ = true;}
      while(QDaRnRapqK == QDaRnRapqK){HCouIElMGe = true;}
      while(aRtBVZnKQX == aRtBVZnKQX){ATHBOIbzPK = true;}
      if(EMxFdcPVZX == true){EMxFdcPVZX = false;}
      if(cUykgmpCUJ == true){cUykgmpCUJ = false;}
      if(TMEjMNudyj == true){TMEjMNudyj = false;}
      if(xAHOZEGVnL == true){xAHOZEGVnL = false;}
      if(BFPThGTJUh == true){BFPThGTJUh = false;}
      if(ikpGDrINsQ == true){ikpGDrINsQ = false;}
      if(glWpZbMjLc == true){glWpZbMjLc = false;}
      if(gUOJIOwkBF == true){gUOJIOwkBF = false;}
      if(tlJQALKBKg == true){tlJQALKBKg = false;}
      if(urcXdOhZsG == true){urcXdOhZsG = false;}
      if(siyqBOWgxn == true){siyqBOWgxn = false;}
      if(wXLmWucGpO == true){wXLmWucGpO = false;}
      if(QLYdgnrpes == true){QLYdgnrpes = false;}
      if(gVquMKmROk == true){gVquMKmROk = false;}
      if(odDWkXgoBi == true){odDWkXgoBi = false;}
      if(kbjeogJTJM == true){kbjeogJTJM = false;}
      if(VfBDHZfQZL == true){VfBDHZfQZL = false;}
      if(HLqEYmHCsJ == true){HLqEYmHCsJ = false;}
      if(HCouIElMGe == true){HCouIElMGe = false;}
      if(ATHBOIbzPK == true){ATHBOIbzPK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STLGZVUWQU
{ 
  void eJkRqCXPHB()
  { 
      bool UVgZVluOrL = false;
      bool fJqpziKoGu = false;
      bool nXbEjrUsNk = false;
      bool lxddRjzxeA = false;
      bool tDTGTkEiLV = false;
      bool GrHAHwscod = false;
      bool QBAGZheMXP = false;
      bool iMKFBjEVkz = false;
      bool mkhrdtpcVV = false;
      bool pWHAjrCMgk = false;
      bool FrKwlthBzW = false;
      bool qXqpqeTIbf = false;
      bool rCpCYMEJUI = false;
      bool gqoztuZkFj = false;
      bool MndydSeRJE = false;
      bool YskBsDBIXZ = false;
      bool oXfqpAiruw = false;
      bool EhDqTDYqXF = false;
      bool hlAQinGmFq = false;
      bool tRNeunHlId = false;
      string SNRwtqHOhV;
      string MQFeizmclB;
      string BlQFxSkjzq;
      string JwetrtUinP;
      string CmNKluAfKG;
      string mzWKngxLza;
      string FXPqMPlLmo;
      string eEoVyNXFTB;
      string SFYsDJYTGL;
      string wIjMKeXWyV;
      string JorVbiKBMZ;
      string IqrxIAyWnC;
      string qRFbrVTbLT;
      string pBHxrdMDQU;
      string zXGfCFPmEJ;
      string gAhueqiQdF;
      string PhpsjGjtFe;
      string ntFSDTLZZm;
      string FgXBmoSLSA;
      string tuZLERgNuu;
      if(SNRwtqHOhV == JorVbiKBMZ){UVgZVluOrL = true;}
      else if(JorVbiKBMZ == SNRwtqHOhV){FrKwlthBzW = true;}
      if(MQFeizmclB == IqrxIAyWnC){fJqpziKoGu = true;}
      else if(IqrxIAyWnC == MQFeizmclB){qXqpqeTIbf = true;}
      if(BlQFxSkjzq == qRFbrVTbLT){nXbEjrUsNk = true;}
      else if(qRFbrVTbLT == BlQFxSkjzq){rCpCYMEJUI = true;}
      if(JwetrtUinP == pBHxrdMDQU){lxddRjzxeA = true;}
      else if(pBHxrdMDQU == JwetrtUinP){gqoztuZkFj = true;}
      if(CmNKluAfKG == zXGfCFPmEJ){tDTGTkEiLV = true;}
      else if(zXGfCFPmEJ == CmNKluAfKG){MndydSeRJE = true;}
      if(mzWKngxLza == gAhueqiQdF){GrHAHwscod = true;}
      else if(gAhueqiQdF == mzWKngxLza){YskBsDBIXZ = true;}
      if(FXPqMPlLmo == PhpsjGjtFe){QBAGZheMXP = true;}
      else if(PhpsjGjtFe == FXPqMPlLmo){oXfqpAiruw = true;}
      if(eEoVyNXFTB == ntFSDTLZZm){iMKFBjEVkz = true;}
      if(SFYsDJYTGL == FgXBmoSLSA){mkhrdtpcVV = true;}
      if(wIjMKeXWyV == tuZLERgNuu){pWHAjrCMgk = true;}
      while(ntFSDTLZZm == eEoVyNXFTB){EhDqTDYqXF = true;}
      while(FgXBmoSLSA == FgXBmoSLSA){hlAQinGmFq = true;}
      while(tuZLERgNuu == tuZLERgNuu){tRNeunHlId = true;}
      if(UVgZVluOrL == true){UVgZVluOrL = false;}
      if(fJqpziKoGu == true){fJqpziKoGu = false;}
      if(nXbEjrUsNk == true){nXbEjrUsNk = false;}
      if(lxddRjzxeA == true){lxddRjzxeA = false;}
      if(tDTGTkEiLV == true){tDTGTkEiLV = false;}
      if(GrHAHwscod == true){GrHAHwscod = false;}
      if(QBAGZheMXP == true){QBAGZheMXP = false;}
      if(iMKFBjEVkz == true){iMKFBjEVkz = false;}
      if(mkhrdtpcVV == true){mkhrdtpcVV = false;}
      if(pWHAjrCMgk == true){pWHAjrCMgk = false;}
      if(FrKwlthBzW == true){FrKwlthBzW = false;}
      if(qXqpqeTIbf == true){qXqpqeTIbf = false;}
      if(rCpCYMEJUI == true){rCpCYMEJUI = false;}
      if(gqoztuZkFj == true){gqoztuZkFj = false;}
      if(MndydSeRJE == true){MndydSeRJE = false;}
      if(YskBsDBIXZ == true){YskBsDBIXZ = false;}
      if(oXfqpAiruw == true){oXfqpAiruw = false;}
      if(EhDqTDYqXF == true){EhDqTDYqXF = false;}
      if(hlAQinGmFq == true){hlAQinGmFq = false;}
      if(tRNeunHlId == true){tRNeunHlId = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LNBYJXQOTI
{ 
  void fCJhWiaZSu()
  { 
      bool bsdXUTaUqo = false;
      bool JrLLoazJor = false;
      bool qhmLgnRFkR = false;
      bool WFJpuyqkMz = false;
      bool fwLwNjbXua = false;
      bool frJlTsGSpg = false;
      bool BVjYSEhVPq = false;
      bool jNwoMuVpyx = false;
      bool MsKJkeuXVB = false;
      bool rXtfxKMmdI = false;
      bool BFHDpSuTYY = false;
      bool XQTsUIKZnm = false;
      bool JKAOyLSPrC = false;
      bool hiLpuGkGTS = false;
      bool jazxdbEBLo = false;
      bool zmyqzqFsFd = false;
      bool AebVpnEdyN = false;
      bool WDGVDhLDjW = false;
      bool HQECDujUpD = false;
      bool ArBoREycGo = false;
      string dIFyCMdXqA;
      string gxzeIDnOzP;
      string rbOyMdwbFb;
      string bxcbEiAVXq;
      string osJyQwVKqu;
      string xofXYBtHlY;
      string PCSPXjTWZZ;
      string DSpHazSQgP;
      string HljJdmRFDD;
      string orizbmZsZg;
      string czjRrezXwY;
      string hcZVRdSIlk;
      string RNSWjKipfn;
      string YYqAlIBRRy;
      string nsIeUMSNgx;
      string URHnOPfNhg;
      string wIrIAIkYiJ;
      string bApmxYFnBW;
      string rUJhTHQDlW;
      string bnijCeBzeL;
      if(dIFyCMdXqA == czjRrezXwY){bsdXUTaUqo = true;}
      else if(czjRrezXwY == dIFyCMdXqA){BFHDpSuTYY = true;}
      if(gxzeIDnOzP == hcZVRdSIlk){JrLLoazJor = true;}
      else if(hcZVRdSIlk == gxzeIDnOzP){XQTsUIKZnm = true;}
      if(rbOyMdwbFb == RNSWjKipfn){qhmLgnRFkR = true;}
      else if(RNSWjKipfn == rbOyMdwbFb){JKAOyLSPrC = true;}
      if(bxcbEiAVXq == YYqAlIBRRy){WFJpuyqkMz = true;}
      else if(YYqAlIBRRy == bxcbEiAVXq){hiLpuGkGTS = true;}
      if(osJyQwVKqu == nsIeUMSNgx){fwLwNjbXua = true;}
      else if(nsIeUMSNgx == osJyQwVKqu){jazxdbEBLo = true;}
      if(xofXYBtHlY == URHnOPfNhg){frJlTsGSpg = true;}
      else if(URHnOPfNhg == xofXYBtHlY){zmyqzqFsFd = true;}
      if(PCSPXjTWZZ == wIrIAIkYiJ){BVjYSEhVPq = true;}
      else if(wIrIAIkYiJ == PCSPXjTWZZ){AebVpnEdyN = true;}
      if(DSpHazSQgP == bApmxYFnBW){jNwoMuVpyx = true;}
      if(HljJdmRFDD == rUJhTHQDlW){MsKJkeuXVB = true;}
      if(orizbmZsZg == bnijCeBzeL){rXtfxKMmdI = true;}
      while(bApmxYFnBW == DSpHazSQgP){WDGVDhLDjW = true;}
      while(rUJhTHQDlW == rUJhTHQDlW){HQECDujUpD = true;}
      while(bnijCeBzeL == bnijCeBzeL){ArBoREycGo = true;}
      if(bsdXUTaUqo == true){bsdXUTaUqo = false;}
      if(JrLLoazJor == true){JrLLoazJor = false;}
      if(qhmLgnRFkR == true){qhmLgnRFkR = false;}
      if(WFJpuyqkMz == true){WFJpuyqkMz = false;}
      if(fwLwNjbXua == true){fwLwNjbXua = false;}
      if(frJlTsGSpg == true){frJlTsGSpg = false;}
      if(BVjYSEhVPq == true){BVjYSEhVPq = false;}
      if(jNwoMuVpyx == true){jNwoMuVpyx = false;}
      if(MsKJkeuXVB == true){MsKJkeuXVB = false;}
      if(rXtfxKMmdI == true){rXtfxKMmdI = false;}
      if(BFHDpSuTYY == true){BFHDpSuTYY = false;}
      if(XQTsUIKZnm == true){XQTsUIKZnm = false;}
      if(JKAOyLSPrC == true){JKAOyLSPrC = false;}
      if(hiLpuGkGTS == true){hiLpuGkGTS = false;}
      if(jazxdbEBLo == true){jazxdbEBLo = false;}
      if(zmyqzqFsFd == true){zmyqzqFsFd = false;}
      if(AebVpnEdyN == true){AebVpnEdyN = false;}
      if(WDGVDhLDjW == true){WDGVDhLDjW = false;}
      if(HQECDujUpD == true){HQECDujUpD = false;}
      if(ArBoREycGo == true){ArBoREycGo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JHSEMQXQTF
{ 
  void iCcphzadyY()
  { 
      bool aAlqYlliJS = false;
      bool ForcNCqmUq = false;
      bool yOzhAQhqzF = false;
      bool VbGGnpAKQq = false;
      bool wbxqaieKfu = false;
      bool MmkQoLADqH = false;
      bool EuiEwchloX = false;
      bool CgWdtWQIHQ = false;
      bool lWKEriqpQb = false;
      bool owTIlAsrty = false;
      bool AsVIsfQHVR = false;
      bool trwZVgkeLM = false;
      bool krUMhFMNqs = false;
      bool dXNJQsBBKL = false;
      bool SjTygxAslF = false;
      bool PNfhMIXIam = false;
      bool SCPcnVdlJc = false;
      bool fiTAtBYVej = false;
      bool ETakdPqfxH = false;
      bool UraWsPTqKK = false;
      string yNwXgrZpcm;
      string uucBFDjoDl;
      string NlIcwyHqAW;
      string OSTNKzLLCs;
      string rxaCpCRUJw;
      string CBmexMETbi;
      string jioGXcbOpG;
      string rXmJtPLGlt;
      string fmhETNeoQy;
      string tqiTIIITdN;
      string ZCdCEeOcjg;
      string ByhhCwAkmJ;
      string ymyqLAnTBl;
      string GqbYTcJezo;
      string zBEixwJBQL;
      string HXgUOmElqE;
      string ptbyZJVJOY;
      string mVkyKwhPtO;
      string pmCodiKHJf;
      string YWmtyEZFIn;
      if(yNwXgrZpcm == ZCdCEeOcjg){aAlqYlliJS = true;}
      else if(ZCdCEeOcjg == yNwXgrZpcm){AsVIsfQHVR = true;}
      if(uucBFDjoDl == ByhhCwAkmJ){ForcNCqmUq = true;}
      else if(ByhhCwAkmJ == uucBFDjoDl){trwZVgkeLM = true;}
      if(NlIcwyHqAW == ymyqLAnTBl){yOzhAQhqzF = true;}
      else if(ymyqLAnTBl == NlIcwyHqAW){krUMhFMNqs = true;}
      if(OSTNKzLLCs == GqbYTcJezo){VbGGnpAKQq = true;}
      else if(GqbYTcJezo == OSTNKzLLCs){dXNJQsBBKL = true;}
      if(rxaCpCRUJw == zBEixwJBQL){wbxqaieKfu = true;}
      else if(zBEixwJBQL == rxaCpCRUJw){SjTygxAslF = true;}
      if(CBmexMETbi == HXgUOmElqE){MmkQoLADqH = true;}
      else if(HXgUOmElqE == CBmexMETbi){PNfhMIXIam = true;}
      if(jioGXcbOpG == ptbyZJVJOY){EuiEwchloX = true;}
      else if(ptbyZJVJOY == jioGXcbOpG){SCPcnVdlJc = true;}
      if(rXmJtPLGlt == mVkyKwhPtO){CgWdtWQIHQ = true;}
      if(fmhETNeoQy == pmCodiKHJf){lWKEriqpQb = true;}
      if(tqiTIIITdN == YWmtyEZFIn){owTIlAsrty = true;}
      while(mVkyKwhPtO == rXmJtPLGlt){fiTAtBYVej = true;}
      while(pmCodiKHJf == pmCodiKHJf){ETakdPqfxH = true;}
      while(YWmtyEZFIn == YWmtyEZFIn){UraWsPTqKK = true;}
      if(aAlqYlliJS == true){aAlqYlliJS = false;}
      if(ForcNCqmUq == true){ForcNCqmUq = false;}
      if(yOzhAQhqzF == true){yOzhAQhqzF = false;}
      if(VbGGnpAKQq == true){VbGGnpAKQq = false;}
      if(wbxqaieKfu == true){wbxqaieKfu = false;}
      if(MmkQoLADqH == true){MmkQoLADqH = false;}
      if(EuiEwchloX == true){EuiEwchloX = false;}
      if(CgWdtWQIHQ == true){CgWdtWQIHQ = false;}
      if(lWKEriqpQb == true){lWKEriqpQb = false;}
      if(owTIlAsrty == true){owTIlAsrty = false;}
      if(AsVIsfQHVR == true){AsVIsfQHVR = false;}
      if(trwZVgkeLM == true){trwZVgkeLM = false;}
      if(krUMhFMNqs == true){krUMhFMNqs = false;}
      if(dXNJQsBBKL == true){dXNJQsBBKL = false;}
      if(SjTygxAslF == true){SjTygxAslF = false;}
      if(PNfhMIXIam == true){PNfhMIXIam = false;}
      if(SCPcnVdlJc == true){SCPcnVdlJc = false;}
      if(fiTAtBYVej == true){fiTAtBYVej = false;}
      if(ETakdPqfxH == true){ETakdPqfxH = false;}
      if(UraWsPTqKK == true){UraWsPTqKK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZHNJPGJKIJ
{ 
  void zbiKyOZQYC()
  { 
      bool NpnCatBSLJ = false;
      bool DRDVHfkDXE = false;
      bool bakGxlTxCz = false;
      bool gREbqnVhxN = false;
      bool MUgPDLzzzq = false;
      bool HQjgVlEhFn = false;
      bool ZEQLckNadT = false;
      bool KCFJqHsUCk = false;
      bool lUxKrPhWGF = false;
      bool incInIDVmR = false;
      bool yYUfgELZpN = false;
      bool rieTBEGGTM = false;
      bool DpUYkVZwVi = false;
      bool EXhklNARcm = false;
      bool EHgrMzJIGi = false;
      bool BwBZOIEuuL = false;
      bool eODGJUAthn = false;
      bool EodfIuJbMk = false;
      bool MQomgHVIVd = false;
      bool JEVRHoEZir = false;
      string FJISjVRHaw;
      string UfyOTPdubm;
      string lwfRuhFRAY;
      string nHDJSdnVqB;
      string WLiUWTrLEq;
      string JnsoPJcqXB;
      string PAGCIMcowo;
      string bIDaPaNKua;
      string otMIOzONsJ;
      string AxxokWEfMJ;
      string qDOPPAjRYo;
      string wSwwMUmymI;
      string yOulneKNor;
      string VgxkilexsN;
      string PwnEMhABcQ;
      string jGsELcIcbk;
      string pVbgSPUKMa;
      string ooEZsBZpZF;
      string dJkYIOmsZG;
      string dCVHXsTHlx;
      if(FJISjVRHaw == qDOPPAjRYo){NpnCatBSLJ = true;}
      else if(qDOPPAjRYo == FJISjVRHaw){yYUfgELZpN = true;}
      if(UfyOTPdubm == wSwwMUmymI){DRDVHfkDXE = true;}
      else if(wSwwMUmymI == UfyOTPdubm){rieTBEGGTM = true;}
      if(lwfRuhFRAY == yOulneKNor){bakGxlTxCz = true;}
      else if(yOulneKNor == lwfRuhFRAY){DpUYkVZwVi = true;}
      if(nHDJSdnVqB == VgxkilexsN){gREbqnVhxN = true;}
      else if(VgxkilexsN == nHDJSdnVqB){EXhklNARcm = true;}
      if(WLiUWTrLEq == PwnEMhABcQ){MUgPDLzzzq = true;}
      else if(PwnEMhABcQ == WLiUWTrLEq){EHgrMzJIGi = true;}
      if(JnsoPJcqXB == jGsELcIcbk){HQjgVlEhFn = true;}
      else if(jGsELcIcbk == JnsoPJcqXB){BwBZOIEuuL = true;}
      if(PAGCIMcowo == pVbgSPUKMa){ZEQLckNadT = true;}
      else if(pVbgSPUKMa == PAGCIMcowo){eODGJUAthn = true;}
      if(bIDaPaNKua == ooEZsBZpZF){KCFJqHsUCk = true;}
      if(otMIOzONsJ == dJkYIOmsZG){lUxKrPhWGF = true;}
      if(AxxokWEfMJ == dCVHXsTHlx){incInIDVmR = true;}
      while(ooEZsBZpZF == bIDaPaNKua){EodfIuJbMk = true;}
      while(dJkYIOmsZG == dJkYIOmsZG){MQomgHVIVd = true;}
      while(dCVHXsTHlx == dCVHXsTHlx){JEVRHoEZir = true;}
      if(NpnCatBSLJ == true){NpnCatBSLJ = false;}
      if(DRDVHfkDXE == true){DRDVHfkDXE = false;}
      if(bakGxlTxCz == true){bakGxlTxCz = false;}
      if(gREbqnVhxN == true){gREbqnVhxN = false;}
      if(MUgPDLzzzq == true){MUgPDLzzzq = false;}
      if(HQjgVlEhFn == true){HQjgVlEhFn = false;}
      if(ZEQLckNadT == true){ZEQLckNadT = false;}
      if(KCFJqHsUCk == true){KCFJqHsUCk = false;}
      if(lUxKrPhWGF == true){lUxKrPhWGF = false;}
      if(incInIDVmR == true){incInIDVmR = false;}
      if(yYUfgELZpN == true){yYUfgELZpN = false;}
      if(rieTBEGGTM == true){rieTBEGGTM = false;}
      if(DpUYkVZwVi == true){DpUYkVZwVi = false;}
      if(EXhklNARcm == true){EXhklNARcm = false;}
      if(EHgrMzJIGi == true){EHgrMzJIGi = false;}
      if(BwBZOIEuuL == true){BwBZOIEuuL = false;}
      if(eODGJUAthn == true){eODGJUAthn = false;}
      if(EodfIuJbMk == true){EodfIuJbMk = false;}
      if(MQomgHVIVd == true){MQomgHVIVd = false;}
      if(JEVRHoEZir == true){JEVRHoEZir = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMMSBMVAUS
{ 
  void UYiRRXHXUa()
  { 
      bool VzimWRIbUq = false;
      bool lSgoKORzgz = false;
      bool sxpKjczDfQ = false;
      bool IGzLqyJQsy = false;
      bool dWoaGOtjcx = false;
      bool UqhncXJXDt = false;
      bool SEuDifTVxL = false;
      bool FAGhVWIODU = false;
      bool hPahwQXKhS = false;
      bool okNyfYakra = false;
      bool tXlRqTjzSF = false;
      bool PtUhLDdNGR = false;
      bool HIndWUmHCw = false;
      bool wWWcaKcIqb = false;
      bool fYrbDtPemc = false;
      bool uNeaSkjItW = false;
      bool fbxVJrXrGB = false;
      bool aUWdkiQLZc = false;
      bool EHUYBiruJo = false;
      bool aTNTwDbWSL = false;
      string HFHajWwCgh;
      string HSyyhjHkeI;
      string JyzefabaFO;
      string jjSrfXClSQ;
      string LjzhVoWbEu;
      string IxUBwIFbtI;
      string uVxSyWAGRJ;
      string gVSNwYzQJp;
      string DAVJGmORuW;
      string RaqJVpmfjz;
      string oQJtNldHEW;
      string JnSEEtzmML;
      string HhKtqFeIqG;
      string lSgJAmpbuT;
      string IHMYNdHlEa;
      string pzTXqHFOCI;
      string HVPykqHIDR;
      string EXqrDAUlgN;
      string yrDPQlyJSs;
      string hbYmMlqOmV;
      if(HFHajWwCgh == oQJtNldHEW){VzimWRIbUq = true;}
      else if(oQJtNldHEW == HFHajWwCgh){tXlRqTjzSF = true;}
      if(HSyyhjHkeI == JnSEEtzmML){lSgoKORzgz = true;}
      else if(JnSEEtzmML == HSyyhjHkeI){PtUhLDdNGR = true;}
      if(JyzefabaFO == HhKtqFeIqG){sxpKjczDfQ = true;}
      else if(HhKtqFeIqG == JyzefabaFO){HIndWUmHCw = true;}
      if(jjSrfXClSQ == lSgJAmpbuT){IGzLqyJQsy = true;}
      else if(lSgJAmpbuT == jjSrfXClSQ){wWWcaKcIqb = true;}
      if(LjzhVoWbEu == IHMYNdHlEa){dWoaGOtjcx = true;}
      else if(IHMYNdHlEa == LjzhVoWbEu){fYrbDtPemc = true;}
      if(IxUBwIFbtI == pzTXqHFOCI){UqhncXJXDt = true;}
      else if(pzTXqHFOCI == IxUBwIFbtI){uNeaSkjItW = true;}
      if(uVxSyWAGRJ == HVPykqHIDR){SEuDifTVxL = true;}
      else if(HVPykqHIDR == uVxSyWAGRJ){fbxVJrXrGB = true;}
      if(gVSNwYzQJp == EXqrDAUlgN){FAGhVWIODU = true;}
      if(DAVJGmORuW == yrDPQlyJSs){hPahwQXKhS = true;}
      if(RaqJVpmfjz == hbYmMlqOmV){okNyfYakra = true;}
      while(EXqrDAUlgN == gVSNwYzQJp){aUWdkiQLZc = true;}
      while(yrDPQlyJSs == yrDPQlyJSs){EHUYBiruJo = true;}
      while(hbYmMlqOmV == hbYmMlqOmV){aTNTwDbWSL = true;}
      if(VzimWRIbUq == true){VzimWRIbUq = false;}
      if(lSgoKORzgz == true){lSgoKORzgz = false;}
      if(sxpKjczDfQ == true){sxpKjczDfQ = false;}
      if(IGzLqyJQsy == true){IGzLqyJQsy = false;}
      if(dWoaGOtjcx == true){dWoaGOtjcx = false;}
      if(UqhncXJXDt == true){UqhncXJXDt = false;}
      if(SEuDifTVxL == true){SEuDifTVxL = false;}
      if(FAGhVWIODU == true){FAGhVWIODU = false;}
      if(hPahwQXKhS == true){hPahwQXKhS = false;}
      if(okNyfYakra == true){okNyfYakra = false;}
      if(tXlRqTjzSF == true){tXlRqTjzSF = false;}
      if(PtUhLDdNGR == true){PtUhLDdNGR = false;}
      if(HIndWUmHCw == true){HIndWUmHCw = false;}
      if(wWWcaKcIqb == true){wWWcaKcIqb = false;}
      if(fYrbDtPemc == true){fYrbDtPemc = false;}
      if(uNeaSkjItW == true){uNeaSkjItW = false;}
      if(fbxVJrXrGB == true){fbxVJrXrGB = false;}
      if(aUWdkiQLZc == true){aUWdkiQLZc = false;}
      if(EHUYBiruJo == true){EHUYBiruJo = false;}
      if(aTNTwDbWSL == true){aTNTwDbWSL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSEHRYQCTK
{ 
  void whjTpeGWsV()
  { 
      bool FmdhKMmAQR = false;
      bool oNNxLeRDtI = false;
      bool TFMiXdbmsk = false;
      bool eScRqMZsDS = false;
      bool QjTnHBUqIe = false;
      bool oIBshzZtKf = false;
      bool jzGelVkwGz = false;
      bool EYzbrjlXbV = false;
      bool JkeOwWRiiq = false;
      bool lfiXiQcoCl = false;
      bool QYkJZQIZBy = false;
      bool NBSoWzUrhP = false;
      bool EBNOMYpbsb = false;
      bool GxVpEjzVnf = false;
      bool OrhjcjNtBi = false;
      bool ujGmhPLVwB = false;
      bool agfYrQfbjl = false;
      bool zzDCALSclc = false;
      bool LuaJfVpiIn = false;
      bool YcYmFhLIrL = false;
      string CQuzHEAufi;
      string SYwBiOVdnm;
      string CXkTaLDeKs;
      string xTeYcKRPOB;
      string zTknaiMeJN;
      string DGnXwefbYu;
      string AUjlkysXXX;
      string wFPlmimwrq;
      string yXUwpqeHby;
      string epqSAdizCc;
      string poHlRxpCjM;
      string riigxcAmus;
      string TluZrGOxkJ;
      string zmsPAJPier;
      string AcWPGuGKVX;
      string duDJIEsgtK;
      string isQaMEpTfm;
      string MQHCsqOfTw;
      string zEaNfEjjGw;
      string PinTJHLwCC;
      if(CQuzHEAufi == poHlRxpCjM){FmdhKMmAQR = true;}
      else if(poHlRxpCjM == CQuzHEAufi){QYkJZQIZBy = true;}
      if(SYwBiOVdnm == riigxcAmus){oNNxLeRDtI = true;}
      else if(riigxcAmus == SYwBiOVdnm){NBSoWzUrhP = true;}
      if(CXkTaLDeKs == TluZrGOxkJ){TFMiXdbmsk = true;}
      else if(TluZrGOxkJ == CXkTaLDeKs){EBNOMYpbsb = true;}
      if(xTeYcKRPOB == zmsPAJPier){eScRqMZsDS = true;}
      else if(zmsPAJPier == xTeYcKRPOB){GxVpEjzVnf = true;}
      if(zTknaiMeJN == AcWPGuGKVX){QjTnHBUqIe = true;}
      else if(AcWPGuGKVX == zTknaiMeJN){OrhjcjNtBi = true;}
      if(DGnXwefbYu == duDJIEsgtK){oIBshzZtKf = true;}
      else if(duDJIEsgtK == DGnXwefbYu){ujGmhPLVwB = true;}
      if(AUjlkysXXX == isQaMEpTfm){jzGelVkwGz = true;}
      else if(isQaMEpTfm == AUjlkysXXX){agfYrQfbjl = true;}
      if(wFPlmimwrq == MQHCsqOfTw){EYzbrjlXbV = true;}
      if(yXUwpqeHby == zEaNfEjjGw){JkeOwWRiiq = true;}
      if(epqSAdizCc == PinTJHLwCC){lfiXiQcoCl = true;}
      while(MQHCsqOfTw == wFPlmimwrq){zzDCALSclc = true;}
      while(zEaNfEjjGw == zEaNfEjjGw){LuaJfVpiIn = true;}
      while(PinTJHLwCC == PinTJHLwCC){YcYmFhLIrL = true;}
      if(FmdhKMmAQR == true){FmdhKMmAQR = false;}
      if(oNNxLeRDtI == true){oNNxLeRDtI = false;}
      if(TFMiXdbmsk == true){TFMiXdbmsk = false;}
      if(eScRqMZsDS == true){eScRqMZsDS = false;}
      if(QjTnHBUqIe == true){QjTnHBUqIe = false;}
      if(oIBshzZtKf == true){oIBshzZtKf = false;}
      if(jzGelVkwGz == true){jzGelVkwGz = false;}
      if(EYzbrjlXbV == true){EYzbrjlXbV = false;}
      if(JkeOwWRiiq == true){JkeOwWRiiq = false;}
      if(lfiXiQcoCl == true){lfiXiQcoCl = false;}
      if(QYkJZQIZBy == true){QYkJZQIZBy = false;}
      if(NBSoWzUrhP == true){NBSoWzUrhP = false;}
      if(EBNOMYpbsb == true){EBNOMYpbsb = false;}
      if(GxVpEjzVnf == true){GxVpEjzVnf = false;}
      if(OrhjcjNtBi == true){OrhjcjNtBi = false;}
      if(ujGmhPLVwB == true){ujGmhPLVwB = false;}
      if(agfYrQfbjl == true){agfYrQfbjl = false;}
      if(zzDCALSclc == true){zzDCALSclc = false;}
      if(LuaJfVpiIn == true){LuaJfVpiIn = false;}
      if(YcYmFhLIrL == true){YcYmFhLIrL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMLBZHPAKB
{ 
  void QuRnCuZXpj()
  { 
      bool QAWFelGyTM = false;
      bool izqzrHQRjG = false;
      bool iFeRYrATuw = false;
      bool ZIlrERHOJn = false;
      bool OewZkwTUrT = false;
      bool FtGyoLVFfl = false;
      bool kmCWlaMytZ = false;
      bool zCIwqDJFfc = false;
      bool YfbaqfBmDs = false;
      bool uCiWDbcYmK = false;
      bool iUaRUClKGl = false;
      bool BQYCMELbfG = false;
      bool YZuAdxTkrP = false;
      bool akRVtEFJGn = false;
      bool tqgQrecfKy = false;
      bool PArgkJZZmX = false;
      bool iARpKPyDII = false;
      bool zBVrLhrdIz = false;
      bool UnaszZrkjj = false;
      bool eeViEsYpGb = false;
      string zkwzfuxidJ;
      string IgCMTVQMku;
      string qjuBVZrSrD;
      string tEkoMAPclI;
      string wAfdJgaMyB;
      string OGGpzPotdF;
      string CepZPDwMAT;
      string FmacyqEQqn;
      string zfTqonxtox;
      string KUyfFRKFOF;
      string kNLduaedrI;
      string LXDoGWKzkb;
      string GBXDIkntWg;
      string fyClDkTouN;
      string ITCgklRJZh;
      string GKUmzipIVK;
      string lkGKbMVQlU;
      string DUEWTmzqRV;
      string SeTnZVdPlU;
      string uKTjbWMqEY;
      if(zkwzfuxidJ == kNLduaedrI){QAWFelGyTM = true;}
      else if(kNLduaedrI == zkwzfuxidJ){iUaRUClKGl = true;}
      if(IgCMTVQMku == LXDoGWKzkb){izqzrHQRjG = true;}
      else if(LXDoGWKzkb == IgCMTVQMku){BQYCMELbfG = true;}
      if(qjuBVZrSrD == GBXDIkntWg){iFeRYrATuw = true;}
      else if(GBXDIkntWg == qjuBVZrSrD){YZuAdxTkrP = true;}
      if(tEkoMAPclI == fyClDkTouN){ZIlrERHOJn = true;}
      else if(fyClDkTouN == tEkoMAPclI){akRVtEFJGn = true;}
      if(wAfdJgaMyB == ITCgklRJZh){OewZkwTUrT = true;}
      else if(ITCgklRJZh == wAfdJgaMyB){tqgQrecfKy = true;}
      if(OGGpzPotdF == GKUmzipIVK){FtGyoLVFfl = true;}
      else if(GKUmzipIVK == OGGpzPotdF){PArgkJZZmX = true;}
      if(CepZPDwMAT == lkGKbMVQlU){kmCWlaMytZ = true;}
      else if(lkGKbMVQlU == CepZPDwMAT){iARpKPyDII = true;}
      if(FmacyqEQqn == DUEWTmzqRV){zCIwqDJFfc = true;}
      if(zfTqonxtox == SeTnZVdPlU){YfbaqfBmDs = true;}
      if(KUyfFRKFOF == uKTjbWMqEY){uCiWDbcYmK = true;}
      while(DUEWTmzqRV == FmacyqEQqn){zBVrLhrdIz = true;}
      while(SeTnZVdPlU == SeTnZVdPlU){UnaszZrkjj = true;}
      while(uKTjbWMqEY == uKTjbWMqEY){eeViEsYpGb = true;}
      if(QAWFelGyTM == true){QAWFelGyTM = false;}
      if(izqzrHQRjG == true){izqzrHQRjG = false;}
      if(iFeRYrATuw == true){iFeRYrATuw = false;}
      if(ZIlrERHOJn == true){ZIlrERHOJn = false;}
      if(OewZkwTUrT == true){OewZkwTUrT = false;}
      if(FtGyoLVFfl == true){FtGyoLVFfl = false;}
      if(kmCWlaMytZ == true){kmCWlaMytZ = false;}
      if(zCIwqDJFfc == true){zCIwqDJFfc = false;}
      if(YfbaqfBmDs == true){YfbaqfBmDs = false;}
      if(uCiWDbcYmK == true){uCiWDbcYmK = false;}
      if(iUaRUClKGl == true){iUaRUClKGl = false;}
      if(BQYCMELbfG == true){BQYCMELbfG = false;}
      if(YZuAdxTkrP == true){YZuAdxTkrP = false;}
      if(akRVtEFJGn == true){akRVtEFJGn = false;}
      if(tqgQrecfKy == true){tqgQrecfKy = false;}
      if(PArgkJZZmX == true){PArgkJZZmX = false;}
      if(iARpKPyDII == true){iARpKPyDII = false;}
      if(zBVrLhrdIz == true){zBVrLhrdIz = false;}
      if(UnaszZrkjj == true){UnaszZrkjj = false;}
      if(eeViEsYpGb == true){eeViEsYpGb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMHJLTYBHF
{ 
  void YkCFqpRYDt()
  { 
      bool bXhUpwnnVn = false;
      bool LuslGlJINJ = false;
      bool AxUVipPhSI = false;
      bool LwFwqKkXcC = false;
      bool QGCoOwTgna = false;
      bool rBpPsdCLlz = false;
      bool fGUNcOpwtu = false;
      bool AleKrsueHl = false;
      bool VisrPKGpCN = false;
      bool IZkcVKloMz = false;
      bool GWlsZGVeWA = false;
      bool iWEAdxMcxS = false;
      bool IAtglaABoh = false;
      bool HFSHeywARJ = false;
      bool nbSCdkUkzX = false;
      bool xIqtpGcFGy = false;
      bool FTonscEwUf = false;
      bool BLKmdfgqCB = false;
      bool GOCQjyNYQY = false;
      bool UqtTDTldIA = false;
      string QgJXuQdnBb;
      string GCyYAcWYMW;
      string UWELXrFTug;
      string SWZItFKMtG;
      string AVmECGhsUP;
      string LWwPjtcxAD;
      string LJrUJibpeu;
      string SJeGWziAIR;
      string JLzfUuaKXA;
      string bMMptpcStS;
      string dqOYwCqosj;
      string KcoisAJMzN;
      string IRReSGwoMf;
      string VPFomSxZjS;
      string DlQmozXdws;
      string gQTfKMZiGo;
      string FCbMOuWzwa;
      string DjbfJVAdpT;
      string iSrSzFuYdZ;
      string rNTtMBKDYs;
      if(QgJXuQdnBb == dqOYwCqosj){bXhUpwnnVn = true;}
      else if(dqOYwCqosj == QgJXuQdnBb){GWlsZGVeWA = true;}
      if(GCyYAcWYMW == KcoisAJMzN){LuslGlJINJ = true;}
      else if(KcoisAJMzN == GCyYAcWYMW){iWEAdxMcxS = true;}
      if(UWELXrFTug == IRReSGwoMf){AxUVipPhSI = true;}
      else if(IRReSGwoMf == UWELXrFTug){IAtglaABoh = true;}
      if(SWZItFKMtG == VPFomSxZjS){LwFwqKkXcC = true;}
      else if(VPFomSxZjS == SWZItFKMtG){HFSHeywARJ = true;}
      if(AVmECGhsUP == DlQmozXdws){QGCoOwTgna = true;}
      else if(DlQmozXdws == AVmECGhsUP){nbSCdkUkzX = true;}
      if(LWwPjtcxAD == gQTfKMZiGo){rBpPsdCLlz = true;}
      else if(gQTfKMZiGo == LWwPjtcxAD){xIqtpGcFGy = true;}
      if(LJrUJibpeu == FCbMOuWzwa){fGUNcOpwtu = true;}
      else if(FCbMOuWzwa == LJrUJibpeu){FTonscEwUf = true;}
      if(SJeGWziAIR == DjbfJVAdpT){AleKrsueHl = true;}
      if(JLzfUuaKXA == iSrSzFuYdZ){VisrPKGpCN = true;}
      if(bMMptpcStS == rNTtMBKDYs){IZkcVKloMz = true;}
      while(DjbfJVAdpT == SJeGWziAIR){BLKmdfgqCB = true;}
      while(iSrSzFuYdZ == iSrSzFuYdZ){GOCQjyNYQY = true;}
      while(rNTtMBKDYs == rNTtMBKDYs){UqtTDTldIA = true;}
      if(bXhUpwnnVn == true){bXhUpwnnVn = false;}
      if(LuslGlJINJ == true){LuslGlJINJ = false;}
      if(AxUVipPhSI == true){AxUVipPhSI = false;}
      if(LwFwqKkXcC == true){LwFwqKkXcC = false;}
      if(QGCoOwTgna == true){QGCoOwTgna = false;}
      if(rBpPsdCLlz == true){rBpPsdCLlz = false;}
      if(fGUNcOpwtu == true){fGUNcOpwtu = false;}
      if(AleKrsueHl == true){AleKrsueHl = false;}
      if(VisrPKGpCN == true){VisrPKGpCN = false;}
      if(IZkcVKloMz == true){IZkcVKloMz = false;}
      if(GWlsZGVeWA == true){GWlsZGVeWA = false;}
      if(iWEAdxMcxS == true){iWEAdxMcxS = false;}
      if(IAtglaABoh == true){IAtglaABoh = false;}
      if(HFSHeywARJ == true){HFSHeywARJ = false;}
      if(nbSCdkUkzX == true){nbSCdkUkzX = false;}
      if(xIqtpGcFGy == true){xIqtpGcFGy = false;}
      if(FTonscEwUf == true){FTonscEwUf = false;}
      if(BLKmdfgqCB == true){BLKmdfgqCB = false;}
      if(GOCQjyNYQY == true){GOCQjyNYQY = false;}
      if(UqtTDTldIA == true){UqtTDTldIA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZXOMXOSSF
{ 
  void JVaJiuMDaA()
  { 
      bool TrVZgWtfYI = false;
      bool JCgkaMAVYT = false;
      bool rXCLtotgKg = false;
      bool BTlxOAPmqp = false;
      bool VHCWCNKKOL = false;
      bool MMDpQwoJeq = false;
      bool bNUqHpQiVZ = false;
      bool xNdhxjUeIg = false;
      bool djRyToQugS = false;
      bool KFHzOIlKPM = false;
      bool xbonOzhUrf = false;
      bool aKAyMruWXR = false;
      bool YUCCPrGdTo = false;
      bool xKPwjCtdiU = false;
      bool GwCAqAEJmV = false;
      bool MPmxmbYlYW = false;
      bool rDBDhQuENJ = false;
      bool xRmCLcRCLO = false;
      bool mxqxbhWRIH = false;
      bool dIEMcCuzRa = false;
      string GiiIafXDAT;
      string ZSLpYNYuOF;
      string xBuAjxHees;
      string HFhHaEOJmz;
      string LTcFXBswrj;
      string sTwGuFmhYc;
      string XrYHLUkDOU;
      string yPHOscXpbh;
      string ELmtAnIaMU;
      string QfjJaSuVsD;
      string PogWkcLgMR;
      string gxGpYMFeGX;
      string LKqtDSexma;
      string gCxXSOePIW;
      string bbNtnTZskO;
      string MQOUrFymTS;
      string yNtljezhXK;
      string hpViuiwwFi;
      string rkMYNQmbfM;
      string PruoYNhbKI;
      if(GiiIafXDAT == PogWkcLgMR){TrVZgWtfYI = true;}
      else if(PogWkcLgMR == GiiIafXDAT){xbonOzhUrf = true;}
      if(ZSLpYNYuOF == gxGpYMFeGX){JCgkaMAVYT = true;}
      else if(gxGpYMFeGX == ZSLpYNYuOF){aKAyMruWXR = true;}
      if(xBuAjxHees == LKqtDSexma){rXCLtotgKg = true;}
      else if(LKqtDSexma == xBuAjxHees){YUCCPrGdTo = true;}
      if(HFhHaEOJmz == gCxXSOePIW){BTlxOAPmqp = true;}
      else if(gCxXSOePIW == HFhHaEOJmz){xKPwjCtdiU = true;}
      if(LTcFXBswrj == bbNtnTZskO){VHCWCNKKOL = true;}
      else if(bbNtnTZskO == LTcFXBswrj){GwCAqAEJmV = true;}
      if(sTwGuFmhYc == MQOUrFymTS){MMDpQwoJeq = true;}
      else if(MQOUrFymTS == sTwGuFmhYc){MPmxmbYlYW = true;}
      if(XrYHLUkDOU == yNtljezhXK){bNUqHpQiVZ = true;}
      else if(yNtljezhXK == XrYHLUkDOU){rDBDhQuENJ = true;}
      if(yPHOscXpbh == hpViuiwwFi){xNdhxjUeIg = true;}
      if(ELmtAnIaMU == rkMYNQmbfM){djRyToQugS = true;}
      if(QfjJaSuVsD == PruoYNhbKI){KFHzOIlKPM = true;}
      while(hpViuiwwFi == yPHOscXpbh){xRmCLcRCLO = true;}
      while(rkMYNQmbfM == rkMYNQmbfM){mxqxbhWRIH = true;}
      while(PruoYNhbKI == PruoYNhbKI){dIEMcCuzRa = true;}
      if(TrVZgWtfYI == true){TrVZgWtfYI = false;}
      if(JCgkaMAVYT == true){JCgkaMAVYT = false;}
      if(rXCLtotgKg == true){rXCLtotgKg = false;}
      if(BTlxOAPmqp == true){BTlxOAPmqp = false;}
      if(VHCWCNKKOL == true){VHCWCNKKOL = false;}
      if(MMDpQwoJeq == true){MMDpQwoJeq = false;}
      if(bNUqHpQiVZ == true){bNUqHpQiVZ = false;}
      if(xNdhxjUeIg == true){xNdhxjUeIg = false;}
      if(djRyToQugS == true){djRyToQugS = false;}
      if(KFHzOIlKPM == true){KFHzOIlKPM = false;}
      if(xbonOzhUrf == true){xbonOzhUrf = false;}
      if(aKAyMruWXR == true){aKAyMruWXR = false;}
      if(YUCCPrGdTo == true){YUCCPrGdTo = false;}
      if(xKPwjCtdiU == true){xKPwjCtdiU = false;}
      if(GwCAqAEJmV == true){GwCAqAEJmV = false;}
      if(MPmxmbYlYW == true){MPmxmbYlYW = false;}
      if(rDBDhQuENJ == true){rDBDhQuENJ = false;}
      if(xRmCLcRCLO == true){xRmCLcRCLO = false;}
      if(mxqxbhWRIH == true){mxqxbhWRIH = false;}
      if(dIEMcCuzRa == true){dIEMcCuzRa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRFFYJCJJQ
{ 
  void NbsyUqVfpx()
  { 
      bool DHSCReHzjL = false;
      bool eeaVBTmFZZ = false;
      bool PmDTuTkqpx = false;
      bool TmoxaqdERi = false;
      bool WsoVmMmOkS = false;
      bool VrHnxQEyHx = false;
      bool sPJmqroctJ = false;
      bool ohmpDWxggh = false;
      bool gVFXbaeBAK = false;
      bool mexToHiCdt = false;
      bool XJUacnFQka = false;
      bool SWRYPWJlLQ = false;
      bool NmcjWKjTBw = false;
      bool muClKXBetm = false;
      bool VNQYrPMYDR = false;
      bool xxqNgjfjES = false;
      bool DlPnnWUeNr = false;
      bool VeqXtzWEqG = false;
      bool xLPiypEnFa = false;
      bool rQZbjjybkU = false;
      string lRbNxRUGyt;
      string PFsjmIfGBZ;
      string dgUnDAQbFz;
      string pAugDsbTCi;
      string CGFEwxRyrY;
      string dupZsEwnJx;
      string ArAzEOJLft;
      string fLDRXWaQrF;
      string hSjgUuKVnz;
      string xnJFhJGGzg;
      string nGSyrSrXBV;
      string ceuEOhITdI;
      string EnWfxqCxiO;
      string QUQKRaAlnC;
      string ClTSVRrFpA;
      string BlbqczilAB;
      string PtnmEINklm;
      string hVebGRTEKe;
      string zwHiNdsZhS;
      string rNkmlIxgOM;
      if(lRbNxRUGyt == nGSyrSrXBV){DHSCReHzjL = true;}
      else if(nGSyrSrXBV == lRbNxRUGyt){XJUacnFQka = true;}
      if(PFsjmIfGBZ == ceuEOhITdI){eeaVBTmFZZ = true;}
      else if(ceuEOhITdI == PFsjmIfGBZ){SWRYPWJlLQ = true;}
      if(dgUnDAQbFz == EnWfxqCxiO){PmDTuTkqpx = true;}
      else if(EnWfxqCxiO == dgUnDAQbFz){NmcjWKjTBw = true;}
      if(pAugDsbTCi == QUQKRaAlnC){TmoxaqdERi = true;}
      else if(QUQKRaAlnC == pAugDsbTCi){muClKXBetm = true;}
      if(CGFEwxRyrY == ClTSVRrFpA){WsoVmMmOkS = true;}
      else if(ClTSVRrFpA == CGFEwxRyrY){VNQYrPMYDR = true;}
      if(dupZsEwnJx == BlbqczilAB){VrHnxQEyHx = true;}
      else if(BlbqczilAB == dupZsEwnJx){xxqNgjfjES = true;}
      if(ArAzEOJLft == PtnmEINklm){sPJmqroctJ = true;}
      else if(PtnmEINklm == ArAzEOJLft){DlPnnWUeNr = true;}
      if(fLDRXWaQrF == hVebGRTEKe){ohmpDWxggh = true;}
      if(hSjgUuKVnz == zwHiNdsZhS){gVFXbaeBAK = true;}
      if(xnJFhJGGzg == rNkmlIxgOM){mexToHiCdt = true;}
      while(hVebGRTEKe == fLDRXWaQrF){VeqXtzWEqG = true;}
      while(zwHiNdsZhS == zwHiNdsZhS){xLPiypEnFa = true;}
      while(rNkmlIxgOM == rNkmlIxgOM){rQZbjjybkU = true;}
      if(DHSCReHzjL == true){DHSCReHzjL = false;}
      if(eeaVBTmFZZ == true){eeaVBTmFZZ = false;}
      if(PmDTuTkqpx == true){PmDTuTkqpx = false;}
      if(TmoxaqdERi == true){TmoxaqdERi = false;}
      if(WsoVmMmOkS == true){WsoVmMmOkS = false;}
      if(VrHnxQEyHx == true){VrHnxQEyHx = false;}
      if(sPJmqroctJ == true){sPJmqroctJ = false;}
      if(ohmpDWxggh == true){ohmpDWxggh = false;}
      if(gVFXbaeBAK == true){gVFXbaeBAK = false;}
      if(mexToHiCdt == true){mexToHiCdt = false;}
      if(XJUacnFQka == true){XJUacnFQka = false;}
      if(SWRYPWJlLQ == true){SWRYPWJlLQ = false;}
      if(NmcjWKjTBw == true){NmcjWKjTBw = false;}
      if(muClKXBetm == true){muClKXBetm = false;}
      if(VNQYrPMYDR == true){VNQYrPMYDR = false;}
      if(xxqNgjfjES == true){xxqNgjfjES = false;}
      if(DlPnnWUeNr == true){DlPnnWUeNr = false;}
      if(VeqXtzWEqG == true){VeqXtzWEqG = false;}
      if(xLPiypEnFa == true){xLPiypEnFa = false;}
      if(rQZbjjybkU == true){rQZbjjybkU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYDGSVHRGZ
{ 
  void woxOtccyio()
  { 
      bool MLhYxUUbVK = false;
      bool AjsdUfqCfk = false;
      bool XUbRzFPLjj = false;
      bool sjSYnwOGAp = false;
      bool RqiAxXyfBq = false;
      bool hsmNnqiPYr = false;
      bool FIrlQPQToX = false;
      bool QjBpTfkaUb = false;
      bool GiJrCAxFkx = false;
      bool NzhIjIyxjg = false;
      bool GdpdaxrwtH = false;
      bool FHtxkVyAiQ = false;
      bool RLirKRCrFK = false;
      bool hnqmUbsfRE = false;
      bool IBLcqFEjWO = false;
      bool JxNTOuuyTI = false;
      bool uzpiZQQHcJ = false;
      bool cSidHQzFAE = false;
      bool NSVqAjZWXZ = false;
      bool gtMIJJKcDZ = false;
      string JfFrgEgrmU;
      string ZisWRyLkmq;
      string dTxKGMsKaG;
      string gxOWlgsBVb;
      string dDYZOmLDDp;
      string hzFInoitkU;
      string LVRgmcUVjk;
      string FKOKMauXwT;
      string ApHjYgqGiw;
      string xyPBQIkrlk;
      string SoSSjXktuM;
      string tLyRTUOhIG;
      string lOmnmHtNtE;
      string pDkKBKWozA;
      string wwKVClzxhu;
      string tDjfzECeec;
      string cWAqWqZnPI;
      string xYhHJoDRkA;
      string IxfyKlSFLx;
      string IrJWXYuSyL;
      if(JfFrgEgrmU == SoSSjXktuM){MLhYxUUbVK = true;}
      else if(SoSSjXktuM == JfFrgEgrmU){GdpdaxrwtH = true;}
      if(ZisWRyLkmq == tLyRTUOhIG){AjsdUfqCfk = true;}
      else if(tLyRTUOhIG == ZisWRyLkmq){FHtxkVyAiQ = true;}
      if(dTxKGMsKaG == lOmnmHtNtE){XUbRzFPLjj = true;}
      else if(lOmnmHtNtE == dTxKGMsKaG){RLirKRCrFK = true;}
      if(gxOWlgsBVb == pDkKBKWozA){sjSYnwOGAp = true;}
      else if(pDkKBKWozA == gxOWlgsBVb){hnqmUbsfRE = true;}
      if(dDYZOmLDDp == wwKVClzxhu){RqiAxXyfBq = true;}
      else if(wwKVClzxhu == dDYZOmLDDp){IBLcqFEjWO = true;}
      if(hzFInoitkU == tDjfzECeec){hsmNnqiPYr = true;}
      else if(tDjfzECeec == hzFInoitkU){JxNTOuuyTI = true;}
      if(LVRgmcUVjk == cWAqWqZnPI){FIrlQPQToX = true;}
      else if(cWAqWqZnPI == LVRgmcUVjk){uzpiZQQHcJ = true;}
      if(FKOKMauXwT == xYhHJoDRkA){QjBpTfkaUb = true;}
      if(ApHjYgqGiw == IxfyKlSFLx){GiJrCAxFkx = true;}
      if(xyPBQIkrlk == IrJWXYuSyL){NzhIjIyxjg = true;}
      while(xYhHJoDRkA == FKOKMauXwT){cSidHQzFAE = true;}
      while(IxfyKlSFLx == IxfyKlSFLx){NSVqAjZWXZ = true;}
      while(IrJWXYuSyL == IrJWXYuSyL){gtMIJJKcDZ = true;}
      if(MLhYxUUbVK == true){MLhYxUUbVK = false;}
      if(AjsdUfqCfk == true){AjsdUfqCfk = false;}
      if(XUbRzFPLjj == true){XUbRzFPLjj = false;}
      if(sjSYnwOGAp == true){sjSYnwOGAp = false;}
      if(RqiAxXyfBq == true){RqiAxXyfBq = false;}
      if(hsmNnqiPYr == true){hsmNnqiPYr = false;}
      if(FIrlQPQToX == true){FIrlQPQToX = false;}
      if(QjBpTfkaUb == true){QjBpTfkaUb = false;}
      if(GiJrCAxFkx == true){GiJrCAxFkx = false;}
      if(NzhIjIyxjg == true){NzhIjIyxjg = false;}
      if(GdpdaxrwtH == true){GdpdaxrwtH = false;}
      if(FHtxkVyAiQ == true){FHtxkVyAiQ = false;}
      if(RLirKRCrFK == true){RLirKRCrFK = false;}
      if(hnqmUbsfRE == true){hnqmUbsfRE = false;}
      if(IBLcqFEjWO == true){IBLcqFEjWO = false;}
      if(JxNTOuuyTI == true){JxNTOuuyTI = false;}
      if(uzpiZQQHcJ == true){uzpiZQQHcJ = false;}
      if(cSidHQzFAE == true){cSidHQzFAE = false;}
      if(NSVqAjZWXZ == true){NSVqAjZWXZ = false;}
      if(gtMIJJKcDZ == true){gtMIJJKcDZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFKHBMXUSE
{ 
  void eVnMNxVQAp()
  { 
      bool CybaePOqzc = false;
      bool wUTyijpwYc = false;
      bool ywEfBsUSor = false;
      bool VmhlZDSRLq = false;
      bool FpTtfdZiGs = false;
      bool pWjcGGsuYk = false;
      bool uwCGHJlgYe = false;
      bool RXkhXIbKAW = false;
      bool SkLwCzDFeS = false;
      bool KWrZwImMlV = false;
      bool rsKaaRkCFy = false;
      bool dhuBRJjGEI = false;
      bool GgBFUteLkO = false;
      bool UPXeeZajUk = false;
      bool NBzgobbqHl = false;
      bool YgIdOLqEFg = false;
      bool lZQpdNKQWq = false;
      bool izkTtFgUQs = false;
      bool SnDzpmHsPT = false;
      bool iVenynjJDa = false;
      string RxkdNALrQi;
      string PlOCLkeBOc;
      string YNgODxRUVU;
      string YSHdPpPmzt;
      string WbhYKGmZpi;
      string CFPMlEPWZQ;
      string iqVuJxekmU;
      string VrBTFxeHDw;
      string JqemSTCtrK;
      string ZsMhKfFmPN;
      string bCmUMJDwGn;
      string YIScHrMibp;
      string ujrbtbeTJZ;
      string qrrpUHEJZI;
      string QFnDkRajaS;
      string SWKYSrJKaj;
      string ejmfxfPcIz;
      string mDISZouoqb;
      string BtspHThTXb;
      string ythodgSIGE;
      if(RxkdNALrQi == bCmUMJDwGn){CybaePOqzc = true;}
      else if(bCmUMJDwGn == RxkdNALrQi){rsKaaRkCFy = true;}
      if(PlOCLkeBOc == YIScHrMibp){wUTyijpwYc = true;}
      else if(YIScHrMibp == PlOCLkeBOc){dhuBRJjGEI = true;}
      if(YNgODxRUVU == ujrbtbeTJZ){ywEfBsUSor = true;}
      else if(ujrbtbeTJZ == YNgODxRUVU){GgBFUteLkO = true;}
      if(YSHdPpPmzt == qrrpUHEJZI){VmhlZDSRLq = true;}
      else if(qrrpUHEJZI == YSHdPpPmzt){UPXeeZajUk = true;}
      if(WbhYKGmZpi == QFnDkRajaS){FpTtfdZiGs = true;}
      else if(QFnDkRajaS == WbhYKGmZpi){NBzgobbqHl = true;}
      if(CFPMlEPWZQ == SWKYSrJKaj){pWjcGGsuYk = true;}
      else if(SWKYSrJKaj == CFPMlEPWZQ){YgIdOLqEFg = true;}
      if(iqVuJxekmU == ejmfxfPcIz){uwCGHJlgYe = true;}
      else if(ejmfxfPcIz == iqVuJxekmU){lZQpdNKQWq = true;}
      if(VrBTFxeHDw == mDISZouoqb){RXkhXIbKAW = true;}
      if(JqemSTCtrK == BtspHThTXb){SkLwCzDFeS = true;}
      if(ZsMhKfFmPN == ythodgSIGE){KWrZwImMlV = true;}
      while(mDISZouoqb == VrBTFxeHDw){izkTtFgUQs = true;}
      while(BtspHThTXb == BtspHThTXb){SnDzpmHsPT = true;}
      while(ythodgSIGE == ythodgSIGE){iVenynjJDa = true;}
      if(CybaePOqzc == true){CybaePOqzc = false;}
      if(wUTyijpwYc == true){wUTyijpwYc = false;}
      if(ywEfBsUSor == true){ywEfBsUSor = false;}
      if(VmhlZDSRLq == true){VmhlZDSRLq = false;}
      if(FpTtfdZiGs == true){FpTtfdZiGs = false;}
      if(pWjcGGsuYk == true){pWjcGGsuYk = false;}
      if(uwCGHJlgYe == true){uwCGHJlgYe = false;}
      if(RXkhXIbKAW == true){RXkhXIbKAW = false;}
      if(SkLwCzDFeS == true){SkLwCzDFeS = false;}
      if(KWrZwImMlV == true){KWrZwImMlV = false;}
      if(rsKaaRkCFy == true){rsKaaRkCFy = false;}
      if(dhuBRJjGEI == true){dhuBRJjGEI = false;}
      if(GgBFUteLkO == true){GgBFUteLkO = false;}
      if(UPXeeZajUk == true){UPXeeZajUk = false;}
      if(NBzgobbqHl == true){NBzgobbqHl = false;}
      if(YgIdOLqEFg == true){YgIdOLqEFg = false;}
      if(lZQpdNKQWq == true){lZQpdNKQWq = false;}
      if(izkTtFgUQs == true){izkTtFgUQs = false;}
      if(SnDzpmHsPT == true){SnDzpmHsPT = false;}
      if(iVenynjJDa == true){iVenynjJDa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDJCHBZXVP
{ 
  void SdmPARwcAO()
  { 
      bool ZiAUmOpEqd = false;
      bool yyTHfiGhBE = false;
      bool qowggKpldT = false;
      bool uHZwSyUJVg = false;
      bool uexlxzwBFa = false;
      bool wLwYOkmTmb = false;
      bool YDaXhpXWog = false;
      bool OwLTIMrJih = false;
      bool NnfCWjLBhh = false;
      bool LAVtIqDZDH = false;
      bool aZMYLAAbPB = false;
      bool rckFNjXXAy = false;
      bool eWnHVNZRLR = false;
      bool JRFbGnaHpW = false;
      bool jikgohPQfX = false;
      bool TfZFbEkFDy = false;
      bool ahQyraWIyZ = false;
      bool JQgdOwkHRm = false;
      bool yIlnxcrAzC = false;
      bool DVDruBRmoN = false;
      string ddboleLUIu;
      string pxUjjpsslZ;
      string mzSAJhVsFh;
      string ePtlPyTlik;
      string qBYoVGHbjN;
      string MaPqbeLbfE;
      string ISPaPaChUk;
      string VGKAilaceD;
      string ZtIqVEACKk;
      string mrGecXlyZt;
      string DZGyqFQOIp;
      string DhwceOJXEK;
      string azXjydzeXK;
      string zcDjzzmJzP;
      string nktTgFudAO;
      string ONsOTDCWAN;
      string FkqxpaeMce;
      string azXnWoFDCs;
      string hVeJwkioQw;
      string xQJlKCtxdG;
      if(ddboleLUIu == DZGyqFQOIp){ZiAUmOpEqd = true;}
      else if(DZGyqFQOIp == ddboleLUIu){aZMYLAAbPB = true;}
      if(pxUjjpsslZ == DhwceOJXEK){yyTHfiGhBE = true;}
      else if(DhwceOJXEK == pxUjjpsslZ){rckFNjXXAy = true;}
      if(mzSAJhVsFh == azXjydzeXK){qowggKpldT = true;}
      else if(azXjydzeXK == mzSAJhVsFh){eWnHVNZRLR = true;}
      if(ePtlPyTlik == zcDjzzmJzP){uHZwSyUJVg = true;}
      else if(zcDjzzmJzP == ePtlPyTlik){JRFbGnaHpW = true;}
      if(qBYoVGHbjN == nktTgFudAO){uexlxzwBFa = true;}
      else if(nktTgFudAO == qBYoVGHbjN){jikgohPQfX = true;}
      if(MaPqbeLbfE == ONsOTDCWAN){wLwYOkmTmb = true;}
      else if(ONsOTDCWAN == MaPqbeLbfE){TfZFbEkFDy = true;}
      if(ISPaPaChUk == FkqxpaeMce){YDaXhpXWog = true;}
      else if(FkqxpaeMce == ISPaPaChUk){ahQyraWIyZ = true;}
      if(VGKAilaceD == azXnWoFDCs){OwLTIMrJih = true;}
      if(ZtIqVEACKk == hVeJwkioQw){NnfCWjLBhh = true;}
      if(mrGecXlyZt == xQJlKCtxdG){LAVtIqDZDH = true;}
      while(azXnWoFDCs == VGKAilaceD){JQgdOwkHRm = true;}
      while(hVeJwkioQw == hVeJwkioQw){yIlnxcrAzC = true;}
      while(xQJlKCtxdG == xQJlKCtxdG){DVDruBRmoN = true;}
      if(ZiAUmOpEqd == true){ZiAUmOpEqd = false;}
      if(yyTHfiGhBE == true){yyTHfiGhBE = false;}
      if(qowggKpldT == true){qowggKpldT = false;}
      if(uHZwSyUJVg == true){uHZwSyUJVg = false;}
      if(uexlxzwBFa == true){uexlxzwBFa = false;}
      if(wLwYOkmTmb == true){wLwYOkmTmb = false;}
      if(YDaXhpXWog == true){YDaXhpXWog = false;}
      if(OwLTIMrJih == true){OwLTIMrJih = false;}
      if(NnfCWjLBhh == true){NnfCWjLBhh = false;}
      if(LAVtIqDZDH == true){LAVtIqDZDH = false;}
      if(aZMYLAAbPB == true){aZMYLAAbPB = false;}
      if(rckFNjXXAy == true){rckFNjXXAy = false;}
      if(eWnHVNZRLR == true){eWnHVNZRLR = false;}
      if(JRFbGnaHpW == true){JRFbGnaHpW = false;}
      if(jikgohPQfX == true){jikgohPQfX = false;}
      if(TfZFbEkFDy == true){TfZFbEkFDy = false;}
      if(ahQyraWIyZ == true){ahQyraWIyZ = false;}
      if(JQgdOwkHRm == true){JQgdOwkHRm = false;}
      if(yIlnxcrAzC == true){yIlnxcrAzC = false;}
      if(DVDruBRmoN == true){DVDruBRmoN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROYOBSJESI
{ 
  void SqVnNeLZqb()
  { 
      bool SPYYHhAFJg = false;
      bool bjgHuzGpJj = false;
      bool PGrlyTAmob = false;
      bool nOixTljUmB = false;
      bool gSDndKwXux = false;
      bool oksKkLXmam = false;
      bool gNPhsNBinJ = false;
      bool PkCHCxDDHm = false;
      bool WbrrlDVXLH = false;
      bool NxtzUTCUuQ = false;
      bool JNjkgEhkIm = false;
      bool ITemPEUXwo = false;
      bool qcWfuSpCmh = false;
      bool uhIqdJrGKg = false;
      bool VjPYytRHjP = false;
      bool zeYFYfpDpO = false;
      bool NexaraLnJG = false;
      bool MOMOTGNygB = false;
      bool AiSXiPJCRx = false;
      bool TnQwTpmofX = false;
      string PsUQURCNpl;
      string XwLbxbyWIx;
      string hNetOCgxhJ;
      string HwxdtSkMnw;
      string baPgBGmCAS;
      string UwxLlBOaBS;
      string kFfgeazhhe;
      string pliLUHyxsI;
      string OdwOoKylqs;
      string EKKVLWtiCZ;
      string HFUVbiNkpe;
      string DQgsDGIQqU;
      string cMqoaeaMAx;
      string MOuSAJJamF;
      string wMuMondRSE;
      string OdqhxtOfuw;
      string IAkrRnUNrs;
      string xgclXPRdzm;
      string BItuihXNVG;
      string ucfpwwaCtB;
      if(PsUQURCNpl == HFUVbiNkpe){SPYYHhAFJg = true;}
      else if(HFUVbiNkpe == PsUQURCNpl){JNjkgEhkIm = true;}
      if(XwLbxbyWIx == DQgsDGIQqU){bjgHuzGpJj = true;}
      else if(DQgsDGIQqU == XwLbxbyWIx){ITemPEUXwo = true;}
      if(hNetOCgxhJ == cMqoaeaMAx){PGrlyTAmob = true;}
      else if(cMqoaeaMAx == hNetOCgxhJ){qcWfuSpCmh = true;}
      if(HwxdtSkMnw == MOuSAJJamF){nOixTljUmB = true;}
      else if(MOuSAJJamF == HwxdtSkMnw){uhIqdJrGKg = true;}
      if(baPgBGmCAS == wMuMondRSE){gSDndKwXux = true;}
      else if(wMuMondRSE == baPgBGmCAS){VjPYytRHjP = true;}
      if(UwxLlBOaBS == OdqhxtOfuw){oksKkLXmam = true;}
      else if(OdqhxtOfuw == UwxLlBOaBS){zeYFYfpDpO = true;}
      if(kFfgeazhhe == IAkrRnUNrs){gNPhsNBinJ = true;}
      else if(IAkrRnUNrs == kFfgeazhhe){NexaraLnJG = true;}
      if(pliLUHyxsI == xgclXPRdzm){PkCHCxDDHm = true;}
      if(OdwOoKylqs == BItuihXNVG){WbrrlDVXLH = true;}
      if(EKKVLWtiCZ == ucfpwwaCtB){NxtzUTCUuQ = true;}
      while(xgclXPRdzm == pliLUHyxsI){MOMOTGNygB = true;}
      while(BItuihXNVG == BItuihXNVG){AiSXiPJCRx = true;}
      while(ucfpwwaCtB == ucfpwwaCtB){TnQwTpmofX = true;}
      if(SPYYHhAFJg == true){SPYYHhAFJg = false;}
      if(bjgHuzGpJj == true){bjgHuzGpJj = false;}
      if(PGrlyTAmob == true){PGrlyTAmob = false;}
      if(nOixTljUmB == true){nOixTljUmB = false;}
      if(gSDndKwXux == true){gSDndKwXux = false;}
      if(oksKkLXmam == true){oksKkLXmam = false;}
      if(gNPhsNBinJ == true){gNPhsNBinJ = false;}
      if(PkCHCxDDHm == true){PkCHCxDDHm = false;}
      if(WbrrlDVXLH == true){WbrrlDVXLH = false;}
      if(NxtzUTCUuQ == true){NxtzUTCUuQ = false;}
      if(JNjkgEhkIm == true){JNjkgEhkIm = false;}
      if(ITemPEUXwo == true){ITemPEUXwo = false;}
      if(qcWfuSpCmh == true){qcWfuSpCmh = false;}
      if(uhIqdJrGKg == true){uhIqdJrGKg = false;}
      if(VjPYytRHjP == true){VjPYytRHjP = false;}
      if(zeYFYfpDpO == true){zeYFYfpDpO = false;}
      if(NexaraLnJG == true){NexaraLnJG = false;}
      if(MOMOTGNygB == true){MOMOTGNygB = false;}
      if(AiSXiPJCRx == true){AiSXiPJCRx = false;}
      if(TnQwTpmofX == true){TnQwTpmofX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNLTINNPHC
{ 
  void IqJCQGVmPe()
  { 
      bool kSiGeTOsuW = false;
      bool HTjsAlIJoc = false;
      bool hMfZniPsrG = false;
      bool tIBIfMjiFz = false;
      bool SXipBKNUmf = false;
      bool UhdQgXlISw = false;
      bool DUBocyRaNn = false;
      bool CYDoKJdpXc = false;
      bool UtGMlLejbH = false;
      bool ZaQIuxWtND = false;
      bool rlHzdudoGW = false;
      bool twkobIOoCQ = false;
      bool TgzFNaIttM = false;
      bool micUkhmGhp = false;
      bool hpdENdpbgl = false;
      bool igqxiLmBlC = false;
      bool mitsjLTPEs = false;
      bool VHGMhdDuri = false;
      bool kfNHdFqflY = false;
      bool ukUfCyujTB = false;
      string QQoxdAuOoG;
      string RDrlSuxAZG;
      string OnFdhLQLXr;
      string CPwCNqhMCf;
      string lngzfxDRgi;
      string cLlsMcKKOS;
      string ijpwEBHoXa;
      string MjytTZGGyj;
      string HyeoPpdCpk;
      string gWxiwCxktd;
      string pOtFVrNrZl;
      string VDMdKkEBgN;
      string WFzltpmOxR;
      string cVLTtsEZTW;
      string clbDOcKSYL;
      string ywDgHkOHKf;
      string FyuIJArrjR;
      string fdgJkkcuXQ;
      string eTpkSgReMJ;
      string dxOnRdqTtO;
      if(QQoxdAuOoG == pOtFVrNrZl){kSiGeTOsuW = true;}
      else if(pOtFVrNrZl == QQoxdAuOoG){rlHzdudoGW = true;}
      if(RDrlSuxAZG == VDMdKkEBgN){HTjsAlIJoc = true;}
      else if(VDMdKkEBgN == RDrlSuxAZG){twkobIOoCQ = true;}
      if(OnFdhLQLXr == WFzltpmOxR){hMfZniPsrG = true;}
      else if(WFzltpmOxR == OnFdhLQLXr){TgzFNaIttM = true;}
      if(CPwCNqhMCf == cVLTtsEZTW){tIBIfMjiFz = true;}
      else if(cVLTtsEZTW == CPwCNqhMCf){micUkhmGhp = true;}
      if(lngzfxDRgi == clbDOcKSYL){SXipBKNUmf = true;}
      else if(clbDOcKSYL == lngzfxDRgi){hpdENdpbgl = true;}
      if(cLlsMcKKOS == ywDgHkOHKf){UhdQgXlISw = true;}
      else if(ywDgHkOHKf == cLlsMcKKOS){igqxiLmBlC = true;}
      if(ijpwEBHoXa == FyuIJArrjR){DUBocyRaNn = true;}
      else if(FyuIJArrjR == ijpwEBHoXa){mitsjLTPEs = true;}
      if(MjytTZGGyj == fdgJkkcuXQ){CYDoKJdpXc = true;}
      if(HyeoPpdCpk == eTpkSgReMJ){UtGMlLejbH = true;}
      if(gWxiwCxktd == dxOnRdqTtO){ZaQIuxWtND = true;}
      while(fdgJkkcuXQ == MjytTZGGyj){VHGMhdDuri = true;}
      while(eTpkSgReMJ == eTpkSgReMJ){kfNHdFqflY = true;}
      while(dxOnRdqTtO == dxOnRdqTtO){ukUfCyujTB = true;}
      if(kSiGeTOsuW == true){kSiGeTOsuW = false;}
      if(HTjsAlIJoc == true){HTjsAlIJoc = false;}
      if(hMfZniPsrG == true){hMfZniPsrG = false;}
      if(tIBIfMjiFz == true){tIBIfMjiFz = false;}
      if(SXipBKNUmf == true){SXipBKNUmf = false;}
      if(UhdQgXlISw == true){UhdQgXlISw = false;}
      if(DUBocyRaNn == true){DUBocyRaNn = false;}
      if(CYDoKJdpXc == true){CYDoKJdpXc = false;}
      if(UtGMlLejbH == true){UtGMlLejbH = false;}
      if(ZaQIuxWtND == true){ZaQIuxWtND = false;}
      if(rlHzdudoGW == true){rlHzdudoGW = false;}
      if(twkobIOoCQ == true){twkobIOoCQ = false;}
      if(TgzFNaIttM == true){TgzFNaIttM = false;}
      if(micUkhmGhp == true){micUkhmGhp = false;}
      if(hpdENdpbgl == true){hpdENdpbgl = false;}
      if(igqxiLmBlC == true){igqxiLmBlC = false;}
      if(mitsjLTPEs == true){mitsjLTPEs = false;}
      if(VHGMhdDuri == true){VHGMhdDuri = false;}
      if(kfNHdFqflY == true){kfNHdFqflY = false;}
      if(ukUfCyujTB == true){ukUfCyujTB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZAONGRYYJ
{ 
  void yEkqmnutIo()
  { 
      bool AGfxLFQAcs = false;
      bool ogkGBfQJeC = false;
      bool QqYZqfymXn = false;
      bool ePNTcRzqNC = false;
      bool MpGsgRNgpS = false;
      bool hxcJyIgGGe = false;
      bool GdcoOZTQci = false;
      bool gYubpZjfrZ = false;
      bool RQxEGhlDVU = false;
      bool jrkhuiNRdH = false;
      bool xxEGlJBBTX = false;
      bool XBOfMpfXig = false;
      bool mQuHznmNfG = false;
      bool MSBjbUMpRw = false;
      bool fkixxhcFUF = false;
      bool CoixUfCwHy = false;
      bool VnUMLFAeEr = false;
      bool doFlABhxKQ = false;
      bool KhraEWiDOw = false;
      bool SQiTZrQVlr = false;
      string SkqiyXrMWJ;
      string KSlhGgRWxd;
      string lexqoWZSiM;
      string euUVgtuBLo;
      string bUNmUbpcDC;
      string jsHnWmnzsb;
      string xZcJdOyQAM;
      string lQLIBRRJWN;
      string fxOgclnfys;
      string GuIiqCrDIF;
      string dZbpPShzlF;
      string VdcfwAKufq;
      string aRSHGpHbQz;
      string ZNBRiGUYQJ;
      string EotrWbRcmq;
      string qwWQeMHUjZ;
      string KFilfHbLwp;
      string fleWmkWZjd;
      string XeoYHdqjlW;
      string yznqyyGHMP;
      if(SkqiyXrMWJ == dZbpPShzlF){AGfxLFQAcs = true;}
      else if(dZbpPShzlF == SkqiyXrMWJ){xxEGlJBBTX = true;}
      if(KSlhGgRWxd == VdcfwAKufq){ogkGBfQJeC = true;}
      else if(VdcfwAKufq == KSlhGgRWxd){XBOfMpfXig = true;}
      if(lexqoWZSiM == aRSHGpHbQz){QqYZqfymXn = true;}
      else if(aRSHGpHbQz == lexqoWZSiM){mQuHznmNfG = true;}
      if(euUVgtuBLo == ZNBRiGUYQJ){ePNTcRzqNC = true;}
      else if(ZNBRiGUYQJ == euUVgtuBLo){MSBjbUMpRw = true;}
      if(bUNmUbpcDC == EotrWbRcmq){MpGsgRNgpS = true;}
      else if(EotrWbRcmq == bUNmUbpcDC){fkixxhcFUF = true;}
      if(jsHnWmnzsb == qwWQeMHUjZ){hxcJyIgGGe = true;}
      else if(qwWQeMHUjZ == jsHnWmnzsb){CoixUfCwHy = true;}
      if(xZcJdOyQAM == KFilfHbLwp){GdcoOZTQci = true;}
      else if(KFilfHbLwp == xZcJdOyQAM){VnUMLFAeEr = true;}
      if(lQLIBRRJWN == fleWmkWZjd){gYubpZjfrZ = true;}
      if(fxOgclnfys == XeoYHdqjlW){RQxEGhlDVU = true;}
      if(GuIiqCrDIF == yznqyyGHMP){jrkhuiNRdH = true;}
      while(fleWmkWZjd == lQLIBRRJWN){doFlABhxKQ = true;}
      while(XeoYHdqjlW == XeoYHdqjlW){KhraEWiDOw = true;}
      while(yznqyyGHMP == yznqyyGHMP){SQiTZrQVlr = true;}
      if(AGfxLFQAcs == true){AGfxLFQAcs = false;}
      if(ogkGBfQJeC == true){ogkGBfQJeC = false;}
      if(QqYZqfymXn == true){QqYZqfymXn = false;}
      if(ePNTcRzqNC == true){ePNTcRzqNC = false;}
      if(MpGsgRNgpS == true){MpGsgRNgpS = false;}
      if(hxcJyIgGGe == true){hxcJyIgGGe = false;}
      if(GdcoOZTQci == true){GdcoOZTQci = false;}
      if(gYubpZjfrZ == true){gYubpZjfrZ = false;}
      if(RQxEGhlDVU == true){RQxEGhlDVU = false;}
      if(jrkhuiNRdH == true){jrkhuiNRdH = false;}
      if(xxEGlJBBTX == true){xxEGlJBBTX = false;}
      if(XBOfMpfXig == true){XBOfMpfXig = false;}
      if(mQuHznmNfG == true){mQuHznmNfG = false;}
      if(MSBjbUMpRw == true){MSBjbUMpRw = false;}
      if(fkixxhcFUF == true){fkixxhcFUF = false;}
      if(CoixUfCwHy == true){CoixUfCwHy = false;}
      if(VnUMLFAeEr == true){VnUMLFAeEr = false;}
      if(doFlABhxKQ == true){doFlABhxKQ = false;}
      if(KhraEWiDOw == true){KhraEWiDOw = false;}
      if(SQiTZrQVlr == true){SQiTZrQVlr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVUWLZSISE
{ 
  void QjospmzAzX()
  { 
      bool hTFgmnGQfw = false;
      bool EoMpIxGUZi = false;
      bool hIwYcueMct = false;
      bool kdZVLycxGJ = false;
      bool iGfdJXQUAb = false;
      bool mIsKlZXgEr = false;
      bool JsnkKZOqeK = false;
      bool TJNPAabSOE = false;
      bool eJLBHcjPjk = false;
      bool awrOApRuSj = false;
      bool IZopHcudJK = false;
      bool xERzNzgmdg = false;
      bool pzHsiXRyOJ = false;
      bool IgzewETVsd = false;
      bool hGFYmVdrBB = false;
      bool JeQksJSuGj = false;
      bool LwOABQElDI = false;
      bool eKsAzjshGN = false;
      bool sYxNAdPOll = false;
      bool lXOJRkqFWW = false;
      string QNAjssYuLU;
      string bPEMcQbxnV;
      string VGqobNsKPs;
      string kHiGeaIENQ;
      string dQqWlVtyis;
      string fUsrwKVKIe;
      string zNeSiUfxhB;
      string HXiXrEOUDF;
      string SubWMPNqKT;
      string FyuiQPkYmR;
      string pwPgkHkVAq;
      string uBHCLEkIFS;
      string GnmNwJbAGb;
      string SpgkPWeukE;
      string erqSYDpsWM;
      string dcSTKBJBjb;
      string fkOXYFUWmo;
      string YpWBnOxTos;
      string SidtyoXMZN;
      string MdLJYtcTsT;
      if(QNAjssYuLU == pwPgkHkVAq){hTFgmnGQfw = true;}
      else if(pwPgkHkVAq == QNAjssYuLU){IZopHcudJK = true;}
      if(bPEMcQbxnV == uBHCLEkIFS){EoMpIxGUZi = true;}
      else if(uBHCLEkIFS == bPEMcQbxnV){xERzNzgmdg = true;}
      if(VGqobNsKPs == GnmNwJbAGb){hIwYcueMct = true;}
      else if(GnmNwJbAGb == VGqobNsKPs){pzHsiXRyOJ = true;}
      if(kHiGeaIENQ == SpgkPWeukE){kdZVLycxGJ = true;}
      else if(SpgkPWeukE == kHiGeaIENQ){IgzewETVsd = true;}
      if(dQqWlVtyis == erqSYDpsWM){iGfdJXQUAb = true;}
      else if(erqSYDpsWM == dQqWlVtyis){hGFYmVdrBB = true;}
      if(fUsrwKVKIe == dcSTKBJBjb){mIsKlZXgEr = true;}
      else if(dcSTKBJBjb == fUsrwKVKIe){JeQksJSuGj = true;}
      if(zNeSiUfxhB == fkOXYFUWmo){JsnkKZOqeK = true;}
      else if(fkOXYFUWmo == zNeSiUfxhB){LwOABQElDI = true;}
      if(HXiXrEOUDF == YpWBnOxTos){TJNPAabSOE = true;}
      if(SubWMPNqKT == SidtyoXMZN){eJLBHcjPjk = true;}
      if(FyuiQPkYmR == MdLJYtcTsT){awrOApRuSj = true;}
      while(YpWBnOxTos == HXiXrEOUDF){eKsAzjshGN = true;}
      while(SidtyoXMZN == SidtyoXMZN){sYxNAdPOll = true;}
      while(MdLJYtcTsT == MdLJYtcTsT){lXOJRkqFWW = true;}
      if(hTFgmnGQfw == true){hTFgmnGQfw = false;}
      if(EoMpIxGUZi == true){EoMpIxGUZi = false;}
      if(hIwYcueMct == true){hIwYcueMct = false;}
      if(kdZVLycxGJ == true){kdZVLycxGJ = false;}
      if(iGfdJXQUAb == true){iGfdJXQUAb = false;}
      if(mIsKlZXgEr == true){mIsKlZXgEr = false;}
      if(JsnkKZOqeK == true){JsnkKZOqeK = false;}
      if(TJNPAabSOE == true){TJNPAabSOE = false;}
      if(eJLBHcjPjk == true){eJLBHcjPjk = false;}
      if(awrOApRuSj == true){awrOApRuSj = false;}
      if(IZopHcudJK == true){IZopHcudJK = false;}
      if(xERzNzgmdg == true){xERzNzgmdg = false;}
      if(pzHsiXRyOJ == true){pzHsiXRyOJ = false;}
      if(IgzewETVsd == true){IgzewETVsd = false;}
      if(hGFYmVdrBB == true){hGFYmVdrBB = false;}
      if(JeQksJSuGj == true){JeQksJSuGj = false;}
      if(LwOABQElDI == true){LwOABQElDI = false;}
      if(eKsAzjshGN == true){eKsAzjshGN = false;}
      if(sYxNAdPOll == true){sYxNAdPOll = false;}
      if(lXOJRkqFWW == true){lXOJRkqFWW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOKEOWGNTS
{ 
  void GJXRgtRTiS()
  { 
      bool srHfIXfrnn = false;
      bool fRtuOlPfVr = false;
      bool GIqLcEFdeG = false;
      bool xjhBILtMid = false;
      bool GTtyPmSnyM = false;
      bool kgJEFkAwCD = false;
      bool RCNgqwirlC = false;
      bool rCwqllNrwo = false;
      bool lReSVQZduX = false;
      bool LyJfMEGMHT = false;
      bool EaBwTijRRT = false;
      bool XHzNRAWuLa = false;
      bool VEwOqsrQeh = false;
      bool fAkckKPiyl = false;
      bool fILbzDzwOM = false;
      bool gKBgxzdmFa = false;
      bool pTljmXWVbG = false;
      bool jnxZtMrUOm = false;
      bool tuBSAUzEel = false;
      bool gcdWwMVbnb = false;
      string yLrgkLpguk;
      string ckygQwuxMV;
      string EYwwdrzAhh;
      string tEaUGVhQqc;
      string XwBERYibgH;
      string lVbjAYOuDs;
      string MozNpXJcZu;
      string NeFjxIWreF;
      string IXTZuYcpUg;
      string HmMyQhxnNs;
      string OGBlsHPqmq;
      string CVQxjoVYRR;
      string uSIsnaRHTO;
      string LiekpCVggn;
      string JkDcekWPNa;
      string MYVwyuxIyS;
      string oIXXfSqeHh;
      string SordHJPfNC;
      string ECsrCmMimu;
      string ENiNyAMexL;
      if(yLrgkLpguk == OGBlsHPqmq){srHfIXfrnn = true;}
      else if(OGBlsHPqmq == yLrgkLpguk){EaBwTijRRT = true;}
      if(ckygQwuxMV == CVQxjoVYRR){fRtuOlPfVr = true;}
      else if(CVQxjoVYRR == ckygQwuxMV){XHzNRAWuLa = true;}
      if(EYwwdrzAhh == uSIsnaRHTO){GIqLcEFdeG = true;}
      else if(uSIsnaRHTO == EYwwdrzAhh){VEwOqsrQeh = true;}
      if(tEaUGVhQqc == LiekpCVggn){xjhBILtMid = true;}
      else if(LiekpCVggn == tEaUGVhQqc){fAkckKPiyl = true;}
      if(XwBERYibgH == JkDcekWPNa){GTtyPmSnyM = true;}
      else if(JkDcekWPNa == XwBERYibgH){fILbzDzwOM = true;}
      if(lVbjAYOuDs == MYVwyuxIyS){kgJEFkAwCD = true;}
      else if(MYVwyuxIyS == lVbjAYOuDs){gKBgxzdmFa = true;}
      if(MozNpXJcZu == oIXXfSqeHh){RCNgqwirlC = true;}
      else if(oIXXfSqeHh == MozNpXJcZu){pTljmXWVbG = true;}
      if(NeFjxIWreF == SordHJPfNC){rCwqllNrwo = true;}
      if(IXTZuYcpUg == ECsrCmMimu){lReSVQZduX = true;}
      if(HmMyQhxnNs == ENiNyAMexL){LyJfMEGMHT = true;}
      while(SordHJPfNC == NeFjxIWreF){jnxZtMrUOm = true;}
      while(ECsrCmMimu == ECsrCmMimu){tuBSAUzEel = true;}
      while(ENiNyAMexL == ENiNyAMexL){gcdWwMVbnb = true;}
      if(srHfIXfrnn == true){srHfIXfrnn = false;}
      if(fRtuOlPfVr == true){fRtuOlPfVr = false;}
      if(GIqLcEFdeG == true){GIqLcEFdeG = false;}
      if(xjhBILtMid == true){xjhBILtMid = false;}
      if(GTtyPmSnyM == true){GTtyPmSnyM = false;}
      if(kgJEFkAwCD == true){kgJEFkAwCD = false;}
      if(RCNgqwirlC == true){RCNgqwirlC = false;}
      if(rCwqllNrwo == true){rCwqllNrwo = false;}
      if(lReSVQZduX == true){lReSVQZduX = false;}
      if(LyJfMEGMHT == true){LyJfMEGMHT = false;}
      if(EaBwTijRRT == true){EaBwTijRRT = false;}
      if(XHzNRAWuLa == true){XHzNRAWuLa = false;}
      if(VEwOqsrQeh == true){VEwOqsrQeh = false;}
      if(fAkckKPiyl == true){fAkckKPiyl = false;}
      if(fILbzDzwOM == true){fILbzDzwOM = false;}
      if(gKBgxzdmFa == true){gKBgxzdmFa = false;}
      if(pTljmXWVbG == true){pTljmXWVbG = false;}
      if(jnxZtMrUOm == true){jnxZtMrUOm = false;}
      if(tuBSAUzEel == true){tuBSAUzEel = false;}
      if(gcdWwMVbnb == true){gcdWwMVbnb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PAHVLXMEWW
{ 
  void giPHdieWPz()
  { 
      bool kygLCRYOEo = false;
      bool kHaVaMSJPe = false;
      bool YfCUYTSPDE = false;
      bool LGXdqBCUsp = false;
      bool RsZeOzbmqn = false;
      bool tntLrFwLmi = false;
      bool zJLAcdjxdZ = false;
      bool JyQZMfGXFY = false;
      bool reYOKXMLll = false;
      bool FqhKpIgYBk = false;
      bool PeJQduWUzL = false;
      bool yYFOpUkwoE = false;
      bool RXKqUSPGiD = false;
      bool ygVUJNUHjO = false;
      bool BqMZmgkTTV = false;
      bool XkiwSqTSwL = false;
      bool eQkuNRCjFb = false;
      bool zcMaDZKjDn = false;
      bool gwlNfNxYCR = false;
      bool tBLYijGQMV = false;
      string MfGELlrYTu;
      string tQuKADcGyS;
      string gGRlUdCfJh;
      string gAIlLUbMhG;
      string oyHPGMFNBV;
      string AwTBEGNTih;
      string jMPkOtIIye;
      string bPXqchyCeI;
      string YndmhjfHhF;
      string HIcAVbiWAM;
      string EwOVtjXbYV;
      string HLnZIwibDd;
      string NAasXSmXVA;
      string zaBSEcYHsy;
      string MDiMxuTDqZ;
      string sHTWyDVVya;
      string wzGXVgKVVf;
      string WbhERJRNuc;
      string zjgwHqHeTA;
      string HCJSBMxKpQ;
      if(MfGELlrYTu == EwOVtjXbYV){kygLCRYOEo = true;}
      else if(EwOVtjXbYV == MfGELlrYTu){PeJQduWUzL = true;}
      if(tQuKADcGyS == HLnZIwibDd){kHaVaMSJPe = true;}
      else if(HLnZIwibDd == tQuKADcGyS){yYFOpUkwoE = true;}
      if(gGRlUdCfJh == NAasXSmXVA){YfCUYTSPDE = true;}
      else if(NAasXSmXVA == gGRlUdCfJh){RXKqUSPGiD = true;}
      if(gAIlLUbMhG == zaBSEcYHsy){LGXdqBCUsp = true;}
      else if(zaBSEcYHsy == gAIlLUbMhG){ygVUJNUHjO = true;}
      if(oyHPGMFNBV == MDiMxuTDqZ){RsZeOzbmqn = true;}
      else if(MDiMxuTDqZ == oyHPGMFNBV){BqMZmgkTTV = true;}
      if(AwTBEGNTih == sHTWyDVVya){tntLrFwLmi = true;}
      else if(sHTWyDVVya == AwTBEGNTih){XkiwSqTSwL = true;}
      if(jMPkOtIIye == wzGXVgKVVf){zJLAcdjxdZ = true;}
      else if(wzGXVgKVVf == jMPkOtIIye){eQkuNRCjFb = true;}
      if(bPXqchyCeI == WbhERJRNuc){JyQZMfGXFY = true;}
      if(YndmhjfHhF == zjgwHqHeTA){reYOKXMLll = true;}
      if(HIcAVbiWAM == HCJSBMxKpQ){FqhKpIgYBk = true;}
      while(WbhERJRNuc == bPXqchyCeI){zcMaDZKjDn = true;}
      while(zjgwHqHeTA == zjgwHqHeTA){gwlNfNxYCR = true;}
      while(HCJSBMxKpQ == HCJSBMxKpQ){tBLYijGQMV = true;}
      if(kygLCRYOEo == true){kygLCRYOEo = false;}
      if(kHaVaMSJPe == true){kHaVaMSJPe = false;}
      if(YfCUYTSPDE == true){YfCUYTSPDE = false;}
      if(LGXdqBCUsp == true){LGXdqBCUsp = false;}
      if(RsZeOzbmqn == true){RsZeOzbmqn = false;}
      if(tntLrFwLmi == true){tntLrFwLmi = false;}
      if(zJLAcdjxdZ == true){zJLAcdjxdZ = false;}
      if(JyQZMfGXFY == true){JyQZMfGXFY = false;}
      if(reYOKXMLll == true){reYOKXMLll = false;}
      if(FqhKpIgYBk == true){FqhKpIgYBk = false;}
      if(PeJQduWUzL == true){PeJQduWUzL = false;}
      if(yYFOpUkwoE == true){yYFOpUkwoE = false;}
      if(RXKqUSPGiD == true){RXKqUSPGiD = false;}
      if(ygVUJNUHjO == true){ygVUJNUHjO = false;}
      if(BqMZmgkTTV == true){BqMZmgkTTV = false;}
      if(XkiwSqTSwL == true){XkiwSqTSwL = false;}
      if(eQkuNRCjFb == true){eQkuNRCjFb = false;}
      if(zcMaDZKjDn == true){zcMaDZKjDn = false;}
      if(gwlNfNxYCR == true){gwlNfNxYCR = false;}
      if(tBLYijGQMV == true){tBLYijGQMV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BEYRLGYQPV
{ 
  void WZpcwhOXng()
  { 
      bool gsbDrQsBlZ = false;
      bool BqcbXMwkCc = false;
      bool nrnXHeNZaP = false;
      bool OdPnMpRxgp = false;
      bool yWezXcxpjq = false;
      bool swcNinEDuM = false;
      bool DSaWKXaoPh = false;
      bool tzDMdQNnAd = false;
      bool hWpiVSACEX = false;
      bool kNBTmewHoA = false;
      bool CIaCxtrQiS = false;
      bool aQCQefcrBr = false;
      bool WYjqwfyiZy = false;
      bool UFzAbYwnkb = false;
      bool ZjSlxUKjoG = false;
      bool CDGwccXiFR = false;
      bool wJqkyUQCnF = false;
      bool ioGYRmGysb = false;
      bool UNtSwQyCXz = false;
      bool BNhTfQrhmb = false;
      string KQmmmzAcGP;
      string GoqrXjGJWo;
      string aSyZKKgqRh;
      string DtkbtcchCi;
      string XjsAVPdhzE;
      string ykUferRMbb;
      string SJKXMMEOxt;
      string GYGmRqZxEu;
      string gyqNjRYExC;
      string KPFaQNYUmI;
      string KOjEyZdgNm;
      string RUIgtTRxnt;
      string mAQujpSfWD;
      string SFKujROmPJ;
      string nqpKjpHYfx;
      string wafsVKxnUH;
      string GxKKTMJNxb;
      string EehdGuJGLs;
      string itAZHqYRZY;
      string UZRHDpgfpW;
      if(KQmmmzAcGP == KOjEyZdgNm){gsbDrQsBlZ = true;}
      else if(KOjEyZdgNm == KQmmmzAcGP){CIaCxtrQiS = true;}
      if(GoqrXjGJWo == RUIgtTRxnt){BqcbXMwkCc = true;}
      else if(RUIgtTRxnt == GoqrXjGJWo){aQCQefcrBr = true;}
      if(aSyZKKgqRh == mAQujpSfWD){nrnXHeNZaP = true;}
      else if(mAQujpSfWD == aSyZKKgqRh){WYjqwfyiZy = true;}
      if(DtkbtcchCi == SFKujROmPJ){OdPnMpRxgp = true;}
      else if(SFKujROmPJ == DtkbtcchCi){UFzAbYwnkb = true;}
      if(XjsAVPdhzE == nqpKjpHYfx){yWezXcxpjq = true;}
      else if(nqpKjpHYfx == XjsAVPdhzE){ZjSlxUKjoG = true;}
      if(ykUferRMbb == wafsVKxnUH){swcNinEDuM = true;}
      else if(wafsVKxnUH == ykUferRMbb){CDGwccXiFR = true;}
      if(SJKXMMEOxt == GxKKTMJNxb){DSaWKXaoPh = true;}
      else if(GxKKTMJNxb == SJKXMMEOxt){wJqkyUQCnF = true;}
      if(GYGmRqZxEu == EehdGuJGLs){tzDMdQNnAd = true;}
      if(gyqNjRYExC == itAZHqYRZY){hWpiVSACEX = true;}
      if(KPFaQNYUmI == UZRHDpgfpW){kNBTmewHoA = true;}
      while(EehdGuJGLs == GYGmRqZxEu){ioGYRmGysb = true;}
      while(itAZHqYRZY == itAZHqYRZY){UNtSwQyCXz = true;}
      while(UZRHDpgfpW == UZRHDpgfpW){BNhTfQrhmb = true;}
      if(gsbDrQsBlZ == true){gsbDrQsBlZ = false;}
      if(BqcbXMwkCc == true){BqcbXMwkCc = false;}
      if(nrnXHeNZaP == true){nrnXHeNZaP = false;}
      if(OdPnMpRxgp == true){OdPnMpRxgp = false;}
      if(yWezXcxpjq == true){yWezXcxpjq = false;}
      if(swcNinEDuM == true){swcNinEDuM = false;}
      if(DSaWKXaoPh == true){DSaWKXaoPh = false;}
      if(tzDMdQNnAd == true){tzDMdQNnAd = false;}
      if(hWpiVSACEX == true){hWpiVSACEX = false;}
      if(kNBTmewHoA == true){kNBTmewHoA = false;}
      if(CIaCxtrQiS == true){CIaCxtrQiS = false;}
      if(aQCQefcrBr == true){aQCQefcrBr = false;}
      if(WYjqwfyiZy == true){WYjqwfyiZy = false;}
      if(UFzAbYwnkb == true){UFzAbYwnkb = false;}
      if(ZjSlxUKjoG == true){ZjSlxUKjoG = false;}
      if(CDGwccXiFR == true){CDGwccXiFR = false;}
      if(wJqkyUQCnF == true){wJqkyUQCnF = false;}
      if(ioGYRmGysb == true){ioGYRmGysb = false;}
      if(UNtSwQyCXz == true){UNtSwQyCXz = false;}
      if(BNhTfQrhmb == true){BNhTfQrhmb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZEBSTPLWJ
{ 
  void WSqfBNXgVc()
  { 
      bool BgdHVEKZBt = false;
      bool YoSZHPKzyV = false;
      bool hRtVGUnfpu = false;
      bool dITwINJdlL = false;
      bool TqBrDbdpTK = false;
      bool tMZagjlIAA = false;
      bool QeiGQQUVQs = false;
      bool GgNmBpPCRe = false;
      bool qyLfAQhsPX = false;
      bool aAcluoHuam = false;
      bool GHYaDNymYp = false;
      bool TjpVJRTDFz = false;
      bool hbGrSFDbqM = false;
      bool iUaeXiZkcm = false;
      bool RuTYDqKGcc = false;
      bool VEoaFeAfHx = false;
      bool JWuMHzILyZ = false;
      bool riZRhlHhob = false;
      bool uwyOpdfAZs = false;
      bool hsceduzHRE = false;
      string eBSdEzXrld;
      string kFDQwQZufQ;
      string WcXwlUbFVq;
      string ODFrWWpAHD;
      string eXgRcbexoj;
      string sBebwCdWqi;
      string WSVtOhzKsZ;
      string aYnblyuFSK;
      string pdPlyNXdwU;
      string sSIXfLBmCu;
      string bTDPJTMDoy;
      string GXEgssDjuB;
      string KVOYfHPPuZ;
      string wHDXiVazce;
      string BTnyNVNbem;
      string IRqBkGFdjB;
      string DwHPByTgyW;
      string RDHQzpgQLK;
      string tmkHQeQClb;
      string QwPaaEMYwO;
      if(eBSdEzXrld == bTDPJTMDoy){BgdHVEKZBt = true;}
      else if(bTDPJTMDoy == eBSdEzXrld){GHYaDNymYp = true;}
      if(kFDQwQZufQ == GXEgssDjuB){YoSZHPKzyV = true;}
      else if(GXEgssDjuB == kFDQwQZufQ){TjpVJRTDFz = true;}
      if(WcXwlUbFVq == KVOYfHPPuZ){hRtVGUnfpu = true;}
      else if(KVOYfHPPuZ == WcXwlUbFVq){hbGrSFDbqM = true;}
      if(ODFrWWpAHD == wHDXiVazce){dITwINJdlL = true;}
      else if(wHDXiVazce == ODFrWWpAHD){iUaeXiZkcm = true;}
      if(eXgRcbexoj == BTnyNVNbem){TqBrDbdpTK = true;}
      else if(BTnyNVNbem == eXgRcbexoj){RuTYDqKGcc = true;}
      if(sBebwCdWqi == IRqBkGFdjB){tMZagjlIAA = true;}
      else if(IRqBkGFdjB == sBebwCdWqi){VEoaFeAfHx = true;}
      if(WSVtOhzKsZ == DwHPByTgyW){QeiGQQUVQs = true;}
      else if(DwHPByTgyW == WSVtOhzKsZ){JWuMHzILyZ = true;}
      if(aYnblyuFSK == RDHQzpgQLK){GgNmBpPCRe = true;}
      if(pdPlyNXdwU == tmkHQeQClb){qyLfAQhsPX = true;}
      if(sSIXfLBmCu == QwPaaEMYwO){aAcluoHuam = true;}
      while(RDHQzpgQLK == aYnblyuFSK){riZRhlHhob = true;}
      while(tmkHQeQClb == tmkHQeQClb){uwyOpdfAZs = true;}
      while(QwPaaEMYwO == QwPaaEMYwO){hsceduzHRE = true;}
      if(BgdHVEKZBt == true){BgdHVEKZBt = false;}
      if(YoSZHPKzyV == true){YoSZHPKzyV = false;}
      if(hRtVGUnfpu == true){hRtVGUnfpu = false;}
      if(dITwINJdlL == true){dITwINJdlL = false;}
      if(TqBrDbdpTK == true){TqBrDbdpTK = false;}
      if(tMZagjlIAA == true){tMZagjlIAA = false;}
      if(QeiGQQUVQs == true){QeiGQQUVQs = false;}
      if(GgNmBpPCRe == true){GgNmBpPCRe = false;}
      if(qyLfAQhsPX == true){qyLfAQhsPX = false;}
      if(aAcluoHuam == true){aAcluoHuam = false;}
      if(GHYaDNymYp == true){GHYaDNymYp = false;}
      if(TjpVJRTDFz == true){TjpVJRTDFz = false;}
      if(hbGrSFDbqM == true){hbGrSFDbqM = false;}
      if(iUaeXiZkcm == true){iUaeXiZkcm = false;}
      if(RuTYDqKGcc == true){RuTYDqKGcc = false;}
      if(VEoaFeAfHx == true){VEoaFeAfHx = false;}
      if(JWuMHzILyZ == true){JWuMHzILyZ = false;}
      if(riZRhlHhob == true){riZRhlHhob = false;}
      if(uwyOpdfAZs == true){uwyOpdfAZs = false;}
      if(hsceduzHRE == true){hsceduzHRE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDFRHJEVMO
{ 
  void RKaWGOUunt()
  { 
      bool ZsMuwsaqAP = false;
      bool mozqXAauCz = false;
      bool usugQWMfZA = false;
      bool zFzRGtylsh = false;
      bool UwJoGGIzJP = false;
      bool cfRYMfxfeY = false;
      bool ftRzPhphjd = false;
      bool CnCTdyjGZJ = false;
      bool NMVJXTnZEa = false;
      bool wSHTBZdKYY = false;
      bool QaOfNncxuN = false;
      bool uqGULSXIau = false;
      bool sPcJgjfhRE = false;
      bool UZgAslypui = false;
      bool qpepeELmIi = false;
      bool BUidfBxFyd = false;
      bool HteqsVJFbY = false;
      bool UhNqECjmdb = false;
      bool XsZiCzqDUq = false;
      bool nsqQawLnwJ = false;
      string UrTXCJAsqW;
      string QHMnzZYtaV;
      string epoAwOZiyd;
      string pRmTawGzUW;
      string hsPEbEyDkL;
      string laFoReCSbn;
      string iRuMgzUsMD;
      string TYZDnkZkXr;
      string PWxlqOMxBw;
      string smXgmQyDWc;
      string jFphrNBBAg;
      string FQtiXLTIUR;
      string lWrQJfArQX;
      string lVNuHKgPtd;
      string NLxTqcroJa;
      string wphEpNNYYL;
      string MJjcuiCzbN;
      string eDOqEaZXZg;
      string mLhoawnJEt;
      string wIqhQDaTXI;
      if(UrTXCJAsqW == jFphrNBBAg){ZsMuwsaqAP = true;}
      else if(jFphrNBBAg == UrTXCJAsqW){QaOfNncxuN = true;}
      if(QHMnzZYtaV == FQtiXLTIUR){mozqXAauCz = true;}
      else if(FQtiXLTIUR == QHMnzZYtaV){uqGULSXIau = true;}
      if(epoAwOZiyd == lWrQJfArQX){usugQWMfZA = true;}
      else if(lWrQJfArQX == epoAwOZiyd){sPcJgjfhRE = true;}
      if(pRmTawGzUW == lVNuHKgPtd){zFzRGtylsh = true;}
      else if(lVNuHKgPtd == pRmTawGzUW){UZgAslypui = true;}
      if(hsPEbEyDkL == NLxTqcroJa){UwJoGGIzJP = true;}
      else if(NLxTqcroJa == hsPEbEyDkL){qpepeELmIi = true;}
      if(laFoReCSbn == wphEpNNYYL){cfRYMfxfeY = true;}
      else if(wphEpNNYYL == laFoReCSbn){BUidfBxFyd = true;}
      if(iRuMgzUsMD == MJjcuiCzbN){ftRzPhphjd = true;}
      else if(MJjcuiCzbN == iRuMgzUsMD){HteqsVJFbY = true;}
      if(TYZDnkZkXr == eDOqEaZXZg){CnCTdyjGZJ = true;}
      if(PWxlqOMxBw == mLhoawnJEt){NMVJXTnZEa = true;}
      if(smXgmQyDWc == wIqhQDaTXI){wSHTBZdKYY = true;}
      while(eDOqEaZXZg == TYZDnkZkXr){UhNqECjmdb = true;}
      while(mLhoawnJEt == mLhoawnJEt){XsZiCzqDUq = true;}
      while(wIqhQDaTXI == wIqhQDaTXI){nsqQawLnwJ = true;}
      if(ZsMuwsaqAP == true){ZsMuwsaqAP = false;}
      if(mozqXAauCz == true){mozqXAauCz = false;}
      if(usugQWMfZA == true){usugQWMfZA = false;}
      if(zFzRGtylsh == true){zFzRGtylsh = false;}
      if(UwJoGGIzJP == true){UwJoGGIzJP = false;}
      if(cfRYMfxfeY == true){cfRYMfxfeY = false;}
      if(ftRzPhphjd == true){ftRzPhphjd = false;}
      if(CnCTdyjGZJ == true){CnCTdyjGZJ = false;}
      if(NMVJXTnZEa == true){NMVJXTnZEa = false;}
      if(wSHTBZdKYY == true){wSHTBZdKYY = false;}
      if(QaOfNncxuN == true){QaOfNncxuN = false;}
      if(uqGULSXIau == true){uqGULSXIau = false;}
      if(sPcJgjfhRE == true){sPcJgjfhRE = false;}
      if(UZgAslypui == true){UZgAslypui = false;}
      if(qpepeELmIi == true){qpepeELmIi = false;}
      if(BUidfBxFyd == true){BUidfBxFyd = false;}
      if(HteqsVJFbY == true){HteqsVJFbY = false;}
      if(UhNqECjmdb == true){UhNqECjmdb = false;}
      if(XsZiCzqDUq == true){XsZiCzqDUq = false;}
      if(nsqQawLnwJ == true){nsqQawLnwJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBOLDBSQDR
{ 
  void DUZmWBYuXo()
  { 
      bool EYZMrdUkjA = false;
      bool gREcMZLlYz = false;
      bool UyacbQYDLF = false;
      bool fspunoEOHE = false;
      bool iOHPuwQKQb = false;
      bool MqzAcGyxka = false;
      bool FQZdUnbIoW = false;
      bool UxdTQFqKge = false;
      bool zNmjrntpRh = false;
      bool qHdgyRocuG = false;
      bool UHVsGPNejX = false;
      bool OmPFardplg = false;
      bool slpHeNSxVz = false;
      bool QOPaJrrscc = false;
      bool ZOFtSEqXFG = false;
      bool mzqONiRNNs = false;
      bool wQJjGzWowi = false;
      bool AkMIGefwna = false;
      bool VuqOMRXBMZ = false;
      bool adejfJFVmS = false;
      string yoaZWjFOgJ;
      string VjKaePgDnu;
      string SOhBXgwMWx;
      string pOdGXyGMGX;
      string HczWqBGPqO;
      string fNgTwjHZCo;
      string msriSHGECf;
      string JTwPmoOKJV;
      string agVIRcgKKn;
      string qfKRkOkPEj;
      string uCMKEMRQfH;
      string UwQfOGXjRp;
      string ZwtNndIdeY;
      string EyGZaXTKDE;
      string LPeDTuPeDd;
      string qAyOJyIyVa;
      string DmlGCVppEp;
      string lMfMdJRpts;
      string OdaAhDAqPb;
      string OVncBYdXAy;
      if(yoaZWjFOgJ == uCMKEMRQfH){EYZMrdUkjA = true;}
      else if(uCMKEMRQfH == yoaZWjFOgJ){UHVsGPNejX = true;}
      if(VjKaePgDnu == UwQfOGXjRp){gREcMZLlYz = true;}
      else if(UwQfOGXjRp == VjKaePgDnu){OmPFardplg = true;}
      if(SOhBXgwMWx == ZwtNndIdeY){UyacbQYDLF = true;}
      else if(ZwtNndIdeY == SOhBXgwMWx){slpHeNSxVz = true;}
      if(pOdGXyGMGX == EyGZaXTKDE){fspunoEOHE = true;}
      else if(EyGZaXTKDE == pOdGXyGMGX){QOPaJrrscc = true;}
      if(HczWqBGPqO == LPeDTuPeDd){iOHPuwQKQb = true;}
      else if(LPeDTuPeDd == HczWqBGPqO){ZOFtSEqXFG = true;}
      if(fNgTwjHZCo == qAyOJyIyVa){MqzAcGyxka = true;}
      else if(qAyOJyIyVa == fNgTwjHZCo){mzqONiRNNs = true;}
      if(msriSHGECf == DmlGCVppEp){FQZdUnbIoW = true;}
      else if(DmlGCVppEp == msriSHGECf){wQJjGzWowi = true;}
      if(JTwPmoOKJV == lMfMdJRpts){UxdTQFqKge = true;}
      if(agVIRcgKKn == OdaAhDAqPb){zNmjrntpRh = true;}
      if(qfKRkOkPEj == OVncBYdXAy){qHdgyRocuG = true;}
      while(lMfMdJRpts == JTwPmoOKJV){AkMIGefwna = true;}
      while(OdaAhDAqPb == OdaAhDAqPb){VuqOMRXBMZ = true;}
      while(OVncBYdXAy == OVncBYdXAy){adejfJFVmS = true;}
      if(EYZMrdUkjA == true){EYZMrdUkjA = false;}
      if(gREcMZLlYz == true){gREcMZLlYz = false;}
      if(UyacbQYDLF == true){UyacbQYDLF = false;}
      if(fspunoEOHE == true){fspunoEOHE = false;}
      if(iOHPuwQKQb == true){iOHPuwQKQb = false;}
      if(MqzAcGyxka == true){MqzAcGyxka = false;}
      if(FQZdUnbIoW == true){FQZdUnbIoW = false;}
      if(UxdTQFqKge == true){UxdTQFqKge = false;}
      if(zNmjrntpRh == true){zNmjrntpRh = false;}
      if(qHdgyRocuG == true){qHdgyRocuG = false;}
      if(UHVsGPNejX == true){UHVsGPNejX = false;}
      if(OmPFardplg == true){OmPFardplg = false;}
      if(slpHeNSxVz == true){slpHeNSxVz = false;}
      if(QOPaJrrscc == true){QOPaJrrscc = false;}
      if(ZOFtSEqXFG == true){ZOFtSEqXFG = false;}
      if(mzqONiRNNs == true){mzqONiRNNs = false;}
      if(wQJjGzWowi == true){wQJjGzWowi = false;}
      if(AkMIGefwna == true){AkMIGefwna = false;}
      if(VuqOMRXBMZ == true){VuqOMRXBMZ = false;}
      if(adejfJFVmS == true){adejfJFVmS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBZWOHXLQS
{ 
  void nWrBnUZeOd()
  { 
      bool jTQBDDCQqY = false;
      bool whFUpObItb = false;
      bool foyCZJRJMG = false;
      bool dSRxaMVimW = false;
      bool dYVLPMZHxY = false;
      bool oMTgHuVOas = false;
      bool krEjucPHsc = false;
      bool srUXxGTmlN = false;
      bool jJLnRQzkpf = false;
      bool pHHtkkTkQl = false;
      bool wROTfwquiA = false;
      bool aibNJbfQRd = false;
      bool ceRNmkjamM = false;
      bool mhVzRSuqIV = false;
      bool YEBoEHetjJ = false;
      bool EDTlJQzAgt = false;
      bool LQIWNsMbwp = false;
      bool foIwFYcbIe = false;
      bool FppcHjOjpA = false;
      bool StKNJIuebL = false;
      string INQLdxbcTL;
      string HtgKsVRYQY;
      string VRxVYBbhDW;
      string QfzidepTWa;
      string xgDIToxSsm;
      string PUZVdqQtlc;
      string UtYwuatxgN;
      string fyBpboOnCi;
      string EIoQGuFdFl;
      string OugtFCHGNs;
      string tAleGRSjto;
      string cbrCXMEHoz;
      string UQqtyjQGjY;
      string gHZIoDWJJo;
      string bViQJlDdVs;
      string yARNXcIqgW;
      string BLzUIVBiNU;
      string otxAWzgakL;
      string gljqZfpMjL;
      string tecmmQVOIm;
      if(INQLdxbcTL == tAleGRSjto){jTQBDDCQqY = true;}
      else if(tAleGRSjto == INQLdxbcTL){wROTfwquiA = true;}
      if(HtgKsVRYQY == cbrCXMEHoz){whFUpObItb = true;}
      else if(cbrCXMEHoz == HtgKsVRYQY){aibNJbfQRd = true;}
      if(VRxVYBbhDW == UQqtyjQGjY){foyCZJRJMG = true;}
      else if(UQqtyjQGjY == VRxVYBbhDW){ceRNmkjamM = true;}
      if(QfzidepTWa == gHZIoDWJJo){dSRxaMVimW = true;}
      else if(gHZIoDWJJo == QfzidepTWa){mhVzRSuqIV = true;}
      if(xgDIToxSsm == bViQJlDdVs){dYVLPMZHxY = true;}
      else if(bViQJlDdVs == xgDIToxSsm){YEBoEHetjJ = true;}
      if(PUZVdqQtlc == yARNXcIqgW){oMTgHuVOas = true;}
      else if(yARNXcIqgW == PUZVdqQtlc){EDTlJQzAgt = true;}
      if(UtYwuatxgN == BLzUIVBiNU){krEjucPHsc = true;}
      else if(BLzUIVBiNU == UtYwuatxgN){LQIWNsMbwp = true;}
      if(fyBpboOnCi == otxAWzgakL){srUXxGTmlN = true;}
      if(EIoQGuFdFl == gljqZfpMjL){jJLnRQzkpf = true;}
      if(OugtFCHGNs == tecmmQVOIm){pHHtkkTkQl = true;}
      while(otxAWzgakL == fyBpboOnCi){foIwFYcbIe = true;}
      while(gljqZfpMjL == gljqZfpMjL){FppcHjOjpA = true;}
      while(tecmmQVOIm == tecmmQVOIm){StKNJIuebL = true;}
      if(jTQBDDCQqY == true){jTQBDDCQqY = false;}
      if(whFUpObItb == true){whFUpObItb = false;}
      if(foyCZJRJMG == true){foyCZJRJMG = false;}
      if(dSRxaMVimW == true){dSRxaMVimW = false;}
      if(dYVLPMZHxY == true){dYVLPMZHxY = false;}
      if(oMTgHuVOas == true){oMTgHuVOas = false;}
      if(krEjucPHsc == true){krEjucPHsc = false;}
      if(srUXxGTmlN == true){srUXxGTmlN = false;}
      if(jJLnRQzkpf == true){jJLnRQzkpf = false;}
      if(pHHtkkTkQl == true){pHHtkkTkQl = false;}
      if(wROTfwquiA == true){wROTfwquiA = false;}
      if(aibNJbfQRd == true){aibNJbfQRd = false;}
      if(ceRNmkjamM == true){ceRNmkjamM = false;}
      if(mhVzRSuqIV == true){mhVzRSuqIV = false;}
      if(YEBoEHetjJ == true){YEBoEHetjJ = false;}
      if(EDTlJQzAgt == true){EDTlJQzAgt = false;}
      if(LQIWNsMbwp == true){LQIWNsMbwp = false;}
      if(foIwFYcbIe == true){foIwFYcbIe = false;}
      if(FppcHjOjpA == true){FppcHjOjpA = false;}
      if(StKNJIuebL == true){StKNJIuebL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFBGJUQUUU
{ 
  void iobTAKmIXS()
  { 
      bool QSpLypUzaL = false;
      bool bkenTiOYQE = false;
      bool SjIECioWMS = false;
      bool TPrGucSYtJ = false;
      bool JUnQeYcAIT = false;
      bool RwOIJgJlJP = false;
      bool AymIrMrXrq = false;
      bool QpeHtxurYd = false;
      bool GoOrBWAixO = false;
      bool SfPeILheYS = false;
      bool fFHQDaRHOL = false;
      bool kRNeILjtHU = false;
      bool LIadYkazyi = false;
      bool PQSFxBhxoZ = false;
      bool FsUkcASjVx = false;
      bool amWDHWecrR = false;
      bool ARJewUyHhH = false;
      bool dlFhORnoAX = false;
      bool RpdAHcsOxZ = false;
      bool WEFWYmionI = false;
      string uyEidiLcZF;
      string oyJRUqsjnZ;
      string QHPprWlbgM;
      string naXZcndlqB;
      string UGqVnscBKb;
      string LAmosniNqG;
      string xiuNRNajng;
      string NHsmEJPtBy;
      string tjRFAmmhgo;
      string EPujDkKdEZ;
      string RsNcNEHAji;
      string YoMrMNRpMd;
      string asDzbyLIiT;
      string zkobfAVnqw;
      string elxxPPDCXp;
      string TTQZzYpOAO;
      string rzRQjmzjLL;
      string qcyQynwFiM;
      string uIjszeUPbH;
      string JHnbDfUfNb;
      if(uyEidiLcZF == RsNcNEHAji){QSpLypUzaL = true;}
      else if(RsNcNEHAji == uyEidiLcZF){fFHQDaRHOL = true;}
      if(oyJRUqsjnZ == YoMrMNRpMd){bkenTiOYQE = true;}
      else if(YoMrMNRpMd == oyJRUqsjnZ){kRNeILjtHU = true;}
      if(QHPprWlbgM == asDzbyLIiT){SjIECioWMS = true;}
      else if(asDzbyLIiT == QHPprWlbgM){LIadYkazyi = true;}
      if(naXZcndlqB == zkobfAVnqw){TPrGucSYtJ = true;}
      else if(zkobfAVnqw == naXZcndlqB){PQSFxBhxoZ = true;}
      if(UGqVnscBKb == elxxPPDCXp){JUnQeYcAIT = true;}
      else if(elxxPPDCXp == UGqVnscBKb){FsUkcASjVx = true;}
      if(LAmosniNqG == TTQZzYpOAO){RwOIJgJlJP = true;}
      else if(TTQZzYpOAO == LAmosniNqG){amWDHWecrR = true;}
      if(xiuNRNajng == rzRQjmzjLL){AymIrMrXrq = true;}
      else if(rzRQjmzjLL == xiuNRNajng){ARJewUyHhH = true;}
      if(NHsmEJPtBy == qcyQynwFiM){QpeHtxurYd = true;}
      if(tjRFAmmhgo == uIjszeUPbH){GoOrBWAixO = true;}
      if(EPujDkKdEZ == JHnbDfUfNb){SfPeILheYS = true;}
      while(qcyQynwFiM == NHsmEJPtBy){dlFhORnoAX = true;}
      while(uIjszeUPbH == uIjszeUPbH){RpdAHcsOxZ = true;}
      while(JHnbDfUfNb == JHnbDfUfNb){WEFWYmionI = true;}
      if(QSpLypUzaL == true){QSpLypUzaL = false;}
      if(bkenTiOYQE == true){bkenTiOYQE = false;}
      if(SjIECioWMS == true){SjIECioWMS = false;}
      if(TPrGucSYtJ == true){TPrGucSYtJ = false;}
      if(JUnQeYcAIT == true){JUnQeYcAIT = false;}
      if(RwOIJgJlJP == true){RwOIJgJlJP = false;}
      if(AymIrMrXrq == true){AymIrMrXrq = false;}
      if(QpeHtxurYd == true){QpeHtxurYd = false;}
      if(GoOrBWAixO == true){GoOrBWAixO = false;}
      if(SfPeILheYS == true){SfPeILheYS = false;}
      if(fFHQDaRHOL == true){fFHQDaRHOL = false;}
      if(kRNeILjtHU == true){kRNeILjtHU = false;}
      if(LIadYkazyi == true){LIadYkazyi = false;}
      if(PQSFxBhxoZ == true){PQSFxBhxoZ = false;}
      if(FsUkcASjVx == true){FsUkcASjVx = false;}
      if(amWDHWecrR == true){amWDHWecrR = false;}
      if(ARJewUyHhH == true){ARJewUyHhH = false;}
      if(dlFhORnoAX == true){dlFhORnoAX = false;}
      if(RpdAHcsOxZ == true){RpdAHcsOxZ = false;}
      if(WEFWYmionI == true){WEFWYmionI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWCZXDMZOO
{ 
  void qcyhYuCuoH()
  { 
      bool gYUNRbUwXu = false;
      bool VeSsLAhBqw = false;
      bool VTuLQGUeDi = false;
      bool fBUPEkWiaT = false;
      bool HYPSCYrBlP = false;
      bool meKAMNdIxK = false;
      bool GornOUJCnZ = false;
      bool czaWnxDcJq = false;
      bool OTrnwBqTDq = false;
      bool HOlPMRfaDh = false;
      bool OoMLlnDnMO = false;
      bool JAyFumwErM = false;
      bool dozxSOMKJW = false;
      bool RcYbcZHgCI = false;
      bool xCHngGPgTZ = false;
      bool VbiqEYoOsX = false;
      bool asepxgaWbV = false;
      bool fPCiOahLPL = false;
      bool yfpiApshXD = false;
      bool jrmdgEXRpA = false;
      string BScfjuossR;
      string AQtlVKSstR;
      string FtwlkciWIU;
      string CUJnKiEhKo;
      string yhPxYWqRrW;
      string YrZtUHWquH;
      string LSkXPfGGbm;
      string GjhFSWdyNN;
      string lRdlwKtPSD;
      string MMmDcfxrhr;
      string PjoFQoJUay;
      string cXdhVtnyaF;
      string kqmXZswebm;
      string ZlQUxBbYUH;
      string AYnUZniFhi;
      string qyQcHYxQeW;
      string resmXqHJjT;
      string ROdTEMCRyl;
      string KqwrwbUmNX;
      string DKtyPUfBxh;
      if(BScfjuossR == PjoFQoJUay){gYUNRbUwXu = true;}
      else if(PjoFQoJUay == BScfjuossR){OoMLlnDnMO = true;}
      if(AQtlVKSstR == cXdhVtnyaF){VeSsLAhBqw = true;}
      else if(cXdhVtnyaF == AQtlVKSstR){JAyFumwErM = true;}
      if(FtwlkciWIU == kqmXZswebm){VTuLQGUeDi = true;}
      else if(kqmXZswebm == FtwlkciWIU){dozxSOMKJW = true;}
      if(CUJnKiEhKo == ZlQUxBbYUH){fBUPEkWiaT = true;}
      else if(ZlQUxBbYUH == CUJnKiEhKo){RcYbcZHgCI = true;}
      if(yhPxYWqRrW == AYnUZniFhi){HYPSCYrBlP = true;}
      else if(AYnUZniFhi == yhPxYWqRrW){xCHngGPgTZ = true;}
      if(YrZtUHWquH == qyQcHYxQeW){meKAMNdIxK = true;}
      else if(qyQcHYxQeW == YrZtUHWquH){VbiqEYoOsX = true;}
      if(LSkXPfGGbm == resmXqHJjT){GornOUJCnZ = true;}
      else if(resmXqHJjT == LSkXPfGGbm){asepxgaWbV = true;}
      if(GjhFSWdyNN == ROdTEMCRyl){czaWnxDcJq = true;}
      if(lRdlwKtPSD == KqwrwbUmNX){OTrnwBqTDq = true;}
      if(MMmDcfxrhr == DKtyPUfBxh){HOlPMRfaDh = true;}
      while(ROdTEMCRyl == GjhFSWdyNN){fPCiOahLPL = true;}
      while(KqwrwbUmNX == KqwrwbUmNX){yfpiApshXD = true;}
      while(DKtyPUfBxh == DKtyPUfBxh){jrmdgEXRpA = true;}
      if(gYUNRbUwXu == true){gYUNRbUwXu = false;}
      if(VeSsLAhBqw == true){VeSsLAhBqw = false;}
      if(VTuLQGUeDi == true){VTuLQGUeDi = false;}
      if(fBUPEkWiaT == true){fBUPEkWiaT = false;}
      if(HYPSCYrBlP == true){HYPSCYrBlP = false;}
      if(meKAMNdIxK == true){meKAMNdIxK = false;}
      if(GornOUJCnZ == true){GornOUJCnZ = false;}
      if(czaWnxDcJq == true){czaWnxDcJq = false;}
      if(OTrnwBqTDq == true){OTrnwBqTDq = false;}
      if(HOlPMRfaDh == true){HOlPMRfaDh = false;}
      if(OoMLlnDnMO == true){OoMLlnDnMO = false;}
      if(JAyFumwErM == true){JAyFumwErM = false;}
      if(dozxSOMKJW == true){dozxSOMKJW = false;}
      if(RcYbcZHgCI == true){RcYbcZHgCI = false;}
      if(xCHngGPgTZ == true){xCHngGPgTZ = false;}
      if(VbiqEYoOsX == true){VbiqEYoOsX = false;}
      if(asepxgaWbV == true){asepxgaWbV = false;}
      if(fPCiOahLPL == true){fPCiOahLPL = false;}
      if(yfpiApshXD == true){yfpiApshXD = false;}
      if(jrmdgEXRpA == true){jrmdgEXRpA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSKBSGZONG
{ 
  void ioQXSFNpRL()
  { 
      bool jXQRjznIdF = false;
      bool wLJaQRedAV = false;
      bool dgUlNVIIua = false;
      bool rsKtaKuKYQ = false;
      bool JRGyieoUwJ = false;
      bool RdUiMCCdDO = false;
      bool qeMDNCAPzF = false;
      bool WUEiMMaWDh = false;
      bool gmLkJNYagY = false;
      bool HRGKZdEDjg = false;
      bool dYUqmxYlWz = false;
      bool afaUhDSbsz = false;
      bool cZiaxFOtJh = false;
      bool IWmVEHSUxM = false;
      bool omDhxbpkcW = false;
      bool KbJkDEptsh = false;
      bool iecoqEsEQZ = false;
      bool jydgKpVBcV = false;
      bool OcRlWfMCRz = false;
      bool RYaPdJKOps = false;
      string EUGGzJYPzy;
      string hqSMMquumQ;
      string WfqKrqbFmq;
      string JmRccncHCC;
      string HVQVxmGIYt;
      string MymtcYdwOI;
      string hSbInuZoiY;
      string NnrjIBOVME;
      string jSgseKzXAE;
      string KgrtUosIgC;
      string NRYzfYFDka;
      string JHiJXOkicd;
      string wBoeNguyPT;
      string HFoKqSsgMF;
      string EulYtCxiWF;
      string DKfDGLbtlz;
      string dHnQTESYSE;
      string UDVWYAPPjK;
      string iLbJQxZkDf;
      string qzuMbxHVFp;
      if(EUGGzJYPzy == NRYzfYFDka){jXQRjznIdF = true;}
      else if(NRYzfYFDka == EUGGzJYPzy){dYUqmxYlWz = true;}
      if(hqSMMquumQ == JHiJXOkicd){wLJaQRedAV = true;}
      else if(JHiJXOkicd == hqSMMquumQ){afaUhDSbsz = true;}
      if(WfqKrqbFmq == wBoeNguyPT){dgUlNVIIua = true;}
      else if(wBoeNguyPT == WfqKrqbFmq){cZiaxFOtJh = true;}
      if(JmRccncHCC == HFoKqSsgMF){rsKtaKuKYQ = true;}
      else if(HFoKqSsgMF == JmRccncHCC){IWmVEHSUxM = true;}
      if(HVQVxmGIYt == EulYtCxiWF){JRGyieoUwJ = true;}
      else if(EulYtCxiWF == HVQVxmGIYt){omDhxbpkcW = true;}
      if(MymtcYdwOI == DKfDGLbtlz){RdUiMCCdDO = true;}
      else if(DKfDGLbtlz == MymtcYdwOI){KbJkDEptsh = true;}
      if(hSbInuZoiY == dHnQTESYSE){qeMDNCAPzF = true;}
      else if(dHnQTESYSE == hSbInuZoiY){iecoqEsEQZ = true;}
      if(NnrjIBOVME == UDVWYAPPjK){WUEiMMaWDh = true;}
      if(jSgseKzXAE == iLbJQxZkDf){gmLkJNYagY = true;}
      if(KgrtUosIgC == qzuMbxHVFp){HRGKZdEDjg = true;}
      while(UDVWYAPPjK == NnrjIBOVME){jydgKpVBcV = true;}
      while(iLbJQxZkDf == iLbJQxZkDf){OcRlWfMCRz = true;}
      while(qzuMbxHVFp == qzuMbxHVFp){RYaPdJKOps = true;}
      if(jXQRjznIdF == true){jXQRjznIdF = false;}
      if(wLJaQRedAV == true){wLJaQRedAV = false;}
      if(dgUlNVIIua == true){dgUlNVIIua = false;}
      if(rsKtaKuKYQ == true){rsKtaKuKYQ = false;}
      if(JRGyieoUwJ == true){JRGyieoUwJ = false;}
      if(RdUiMCCdDO == true){RdUiMCCdDO = false;}
      if(qeMDNCAPzF == true){qeMDNCAPzF = false;}
      if(WUEiMMaWDh == true){WUEiMMaWDh = false;}
      if(gmLkJNYagY == true){gmLkJNYagY = false;}
      if(HRGKZdEDjg == true){HRGKZdEDjg = false;}
      if(dYUqmxYlWz == true){dYUqmxYlWz = false;}
      if(afaUhDSbsz == true){afaUhDSbsz = false;}
      if(cZiaxFOtJh == true){cZiaxFOtJh = false;}
      if(IWmVEHSUxM == true){IWmVEHSUxM = false;}
      if(omDhxbpkcW == true){omDhxbpkcW = false;}
      if(KbJkDEptsh == true){KbJkDEptsh = false;}
      if(iecoqEsEQZ == true){iecoqEsEQZ = false;}
      if(jydgKpVBcV == true){jydgKpVBcV = false;}
      if(OcRlWfMCRz == true){OcRlWfMCRz = false;}
      if(RYaPdJKOps == true){RYaPdJKOps = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKKAPGGEPF
{ 
  void sCXujPxRNx()
  { 
      bool bmujeebhgX = false;
      bool FsILWEpwCB = false;
      bool woZZKWMaKO = false;
      bool ianYxCBOxK = false;
      bool cELdGBFtBB = false;
      bool rUUipmMUZI = false;
      bool SBXRoeEiNU = false;
      bool CbzrYqcwTJ = false;
      bool RSYIWNGFhJ = false;
      bool ofonqagsob = false;
      bool xVfgyPVbKz = false;
      bool JQBPqzcOua = false;
      bool XzBEeWmKAx = false;
      bool JjHrMumqJG = false;
      bool rduiAYeYxq = false;
      bool yRxNDxUbBb = false;
      bool cKaMoYIJDu = false;
      bool MkEnhsERDG = false;
      bool qNNIyrlsnO = false;
      bool aKohdhChta = false;
      string fSEKwQpVAz;
      string HlHFleuUKQ;
      string oxrLUfOZkm;
      string cEXKcoKcXj;
      string WwkVThhdQk;
      string yataeiaspP;
      string BQkMWDNxbx;
      string URwasrLVql;
      string xjIAnBKxet;
      string OQmHhFLXzQ;
      string UkCSPgdSgm;
      string WECERRHjYU;
      string rPRhiDensn;
      string fmWZRMhokH;
      string XqQrWJOhoP;
      string xazdYESTjL;
      string BoZsGjhbmF;
      string jRzQxAzZLY;
      string oxzcpEmrBM;
      string tNFYGhRXkl;
      if(fSEKwQpVAz == UkCSPgdSgm){bmujeebhgX = true;}
      else if(UkCSPgdSgm == fSEKwQpVAz){xVfgyPVbKz = true;}
      if(HlHFleuUKQ == WECERRHjYU){FsILWEpwCB = true;}
      else if(WECERRHjYU == HlHFleuUKQ){JQBPqzcOua = true;}
      if(oxrLUfOZkm == rPRhiDensn){woZZKWMaKO = true;}
      else if(rPRhiDensn == oxrLUfOZkm){XzBEeWmKAx = true;}
      if(cEXKcoKcXj == fmWZRMhokH){ianYxCBOxK = true;}
      else if(fmWZRMhokH == cEXKcoKcXj){JjHrMumqJG = true;}
      if(WwkVThhdQk == XqQrWJOhoP){cELdGBFtBB = true;}
      else if(XqQrWJOhoP == WwkVThhdQk){rduiAYeYxq = true;}
      if(yataeiaspP == xazdYESTjL){rUUipmMUZI = true;}
      else if(xazdYESTjL == yataeiaspP){yRxNDxUbBb = true;}
      if(BQkMWDNxbx == BoZsGjhbmF){SBXRoeEiNU = true;}
      else if(BoZsGjhbmF == BQkMWDNxbx){cKaMoYIJDu = true;}
      if(URwasrLVql == jRzQxAzZLY){CbzrYqcwTJ = true;}
      if(xjIAnBKxet == oxzcpEmrBM){RSYIWNGFhJ = true;}
      if(OQmHhFLXzQ == tNFYGhRXkl){ofonqagsob = true;}
      while(jRzQxAzZLY == URwasrLVql){MkEnhsERDG = true;}
      while(oxzcpEmrBM == oxzcpEmrBM){qNNIyrlsnO = true;}
      while(tNFYGhRXkl == tNFYGhRXkl){aKohdhChta = true;}
      if(bmujeebhgX == true){bmujeebhgX = false;}
      if(FsILWEpwCB == true){FsILWEpwCB = false;}
      if(woZZKWMaKO == true){woZZKWMaKO = false;}
      if(ianYxCBOxK == true){ianYxCBOxK = false;}
      if(cELdGBFtBB == true){cELdGBFtBB = false;}
      if(rUUipmMUZI == true){rUUipmMUZI = false;}
      if(SBXRoeEiNU == true){SBXRoeEiNU = false;}
      if(CbzrYqcwTJ == true){CbzrYqcwTJ = false;}
      if(RSYIWNGFhJ == true){RSYIWNGFhJ = false;}
      if(ofonqagsob == true){ofonqagsob = false;}
      if(xVfgyPVbKz == true){xVfgyPVbKz = false;}
      if(JQBPqzcOua == true){JQBPqzcOua = false;}
      if(XzBEeWmKAx == true){XzBEeWmKAx = false;}
      if(JjHrMumqJG == true){JjHrMumqJG = false;}
      if(rduiAYeYxq == true){rduiAYeYxq = false;}
      if(yRxNDxUbBb == true){yRxNDxUbBb = false;}
      if(cKaMoYIJDu == true){cKaMoYIJDu = false;}
      if(MkEnhsERDG == true){MkEnhsERDG = false;}
      if(qNNIyrlsnO == true){qNNIyrlsnO = false;}
      if(aKohdhChta == true){aKohdhChta = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THRLRLPSJT
{ 
  void OVqVxKsOoH()
  { 
      bool JqmAiJQWgY = false;
      bool ijfhaBTmRG = false;
      bool JsAOPrtqbM = false;
      bool AifhPxbztd = false;
      bool TYPoicUmUD = false;
      bool TYxUwQqXjp = false;
      bool PYuUXzExSd = false;
      bool ZTrnmjcKfm = false;
      bool XGWXralKky = false;
      bool GEPENtduQj = false;
      bool YWUpczfJhM = false;
      bool mfrxRICWbw = false;
      bool NsMTWVDmZr = false;
      bool GhsuNBlfur = false;
      bool tccYKZLSmF = false;
      bool rHSTWeJASH = false;
      bool wsioGFlwiP = false;
      bool WVbiCjPmIx = false;
      bool JkzUzzOYYi = false;
      bool rlMmwBsnSF = false;
      string tCdhibcMaN;
      string EnBrqXOVmx;
      string NiSoDWYcsD;
      string zPjYbBJfar;
      string SVdBOEwkUX;
      string hsQxYKjoeL;
      string CATXNnEbQo;
      string OitueqFQZy;
      string anHUUGylAQ;
      string RTAPoRCFna;
      string zTTeJzzVRg;
      string FSOfkNryCH;
      string oSbzXtieFM;
      string ozczzGUcKV;
      string HcTTLzFTeb;
      string ZEDfkgrTGP;
      string QTQFrFoOgd;
      string sPmgzMyHnY;
      string nOAcmkwwOR;
      string NAVuFmLObG;
      if(tCdhibcMaN == zTTeJzzVRg){JqmAiJQWgY = true;}
      else if(zTTeJzzVRg == tCdhibcMaN){YWUpczfJhM = true;}
      if(EnBrqXOVmx == FSOfkNryCH){ijfhaBTmRG = true;}
      else if(FSOfkNryCH == EnBrqXOVmx){mfrxRICWbw = true;}
      if(NiSoDWYcsD == oSbzXtieFM){JsAOPrtqbM = true;}
      else if(oSbzXtieFM == NiSoDWYcsD){NsMTWVDmZr = true;}
      if(zPjYbBJfar == ozczzGUcKV){AifhPxbztd = true;}
      else if(ozczzGUcKV == zPjYbBJfar){GhsuNBlfur = true;}
      if(SVdBOEwkUX == HcTTLzFTeb){TYPoicUmUD = true;}
      else if(HcTTLzFTeb == SVdBOEwkUX){tccYKZLSmF = true;}
      if(hsQxYKjoeL == ZEDfkgrTGP){TYxUwQqXjp = true;}
      else if(ZEDfkgrTGP == hsQxYKjoeL){rHSTWeJASH = true;}
      if(CATXNnEbQo == QTQFrFoOgd){PYuUXzExSd = true;}
      else if(QTQFrFoOgd == CATXNnEbQo){wsioGFlwiP = true;}
      if(OitueqFQZy == sPmgzMyHnY){ZTrnmjcKfm = true;}
      if(anHUUGylAQ == nOAcmkwwOR){XGWXralKky = true;}
      if(RTAPoRCFna == NAVuFmLObG){GEPENtduQj = true;}
      while(sPmgzMyHnY == OitueqFQZy){WVbiCjPmIx = true;}
      while(nOAcmkwwOR == nOAcmkwwOR){JkzUzzOYYi = true;}
      while(NAVuFmLObG == NAVuFmLObG){rlMmwBsnSF = true;}
      if(JqmAiJQWgY == true){JqmAiJQWgY = false;}
      if(ijfhaBTmRG == true){ijfhaBTmRG = false;}
      if(JsAOPrtqbM == true){JsAOPrtqbM = false;}
      if(AifhPxbztd == true){AifhPxbztd = false;}
      if(TYPoicUmUD == true){TYPoicUmUD = false;}
      if(TYxUwQqXjp == true){TYxUwQqXjp = false;}
      if(PYuUXzExSd == true){PYuUXzExSd = false;}
      if(ZTrnmjcKfm == true){ZTrnmjcKfm = false;}
      if(XGWXralKky == true){XGWXralKky = false;}
      if(GEPENtduQj == true){GEPENtduQj = false;}
      if(YWUpczfJhM == true){YWUpczfJhM = false;}
      if(mfrxRICWbw == true){mfrxRICWbw = false;}
      if(NsMTWVDmZr == true){NsMTWVDmZr = false;}
      if(GhsuNBlfur == true){GhsuNBlfur = false;}
      if(tccYKZLSmF == true){tccYKZLSmF = false;}
      if(rHSTWeJASH == true){rHSTWeJASH = false;}
      if(wsioGFlwiP == true){wsioGFlwiP = false;}
      if(WVbiCjPmIx == true){WVbiCjPmIx = false;}
      if(JkzUzzOYYi == true){JkzUzzOYYi = false;}
      if(rlMmwBsnSF == true){rlMmwBsnSF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSTHQACZGY
{ 
  void YRHaCcyiKB()
  { 
      bool NGGmlbxKXn = false;
      bool maZIjqTlQN = false;
      bool eqaHLTGubO = false;
      bool CahPwkgJqD = false;
      bool AzljuRyjsW = false;
      bool pEaGUWezaR = false;
      bool VChJkLrKLz = false;
      bool KJtNNeFqMs = false;
      bool VVBFYyzbuZ = false;
      bool GhhZhxRbzi = false;
      bool YnXtMfKNso = false;
      bool RnlgwzBckm = false;
      bool LQOlsbbUfP = false;
      bool NcqcTgyGsr = false;
      bool nlhGIRuAdh = false;
      bool wnqLXIZlBj = false;
      bool EogdanwJMO = false;
      bool BtirzZiHda = false;
      bool gaqyTYkeFL = false;
      bool HMEJnyEDfT = false;
      string UhyCMUymcc;
      string fpSfXXUxGo;
      string sYZCUxBmXj;
      string yBnVldKIkI;
      string xTcYMQLpko;
      string aRVuHwIwhO;
      string TLPseeBxtt;
      string NLLxrZuAoD;
      string lKBhJferNo;
      string VOaVnkEjth;
      string PNupbPGYDg;
      string AHHdcIJgiy;
      string AIiEXzjpIG;
      string VKGGnXPKGs;
      string ZGofoOGwse;
      string aXAwhGdpSc;
      string eQPwLoAAoF;
      string szZpXsTDPJ;
      string rnwceyKJYh;
      string sYrdNJprUz;
      if(UhyCMUymcc == PNupbPGYDg){NGGmlbxKXn = true;}
      else if(PNupbPGYDg == UhyCMUymcc){YnXtMfKNso = true;}
      if(fpSfXXUxGo == AHHdcIJgiy){maZIjqTlQN = true;}
      else if(AHHdcIJgiy == fpSfXXUxGo){RnlgwzBckm = true;}
      if(sYZCUxBmXj == AIiEXzjpIG){eqaHLTGubO = true;}
      else if(AIiEXzjpIG == sYZCUxBmXj){LQOlsbbUfP = true;}
      if(yBnVldKIkI == VKGGnXPKGs){CahPwkgJqD = true;}
      else if(VKGGnXPKGs == yBnVldKIkI){NcqcTgyGsr = true;}
      if(xTcYMQLpko == ZGofoOGwse){AzljuRyjsW = true;}
      else if(ZGofoOGwse == xTcYMQLpko){nlhGIRuAdh = true;}
      if(aRVuHwIwhO == aXAwhGdpSc){pEaGUWezaR = true;}
      else if(aXAwhGdpSc == aRVuHwIwhO){wnqLXIZlBj = true;}
      if(TLPseeBxtt == eQPwLoAAoF){VChJkLrKLz = true;}
      else if(eQPwLoAAoF == TLPseeBxtt){EogdanwJMO = true;}
      if(NLLxrZuAoD == szZpXsTDPJ){KJtNNeFqMs = true;}
      if(lKBhJferNo == rnwceyKJYh){VVBFYyzbuZ = true;}
      if(VOaVnkEjth == sYrdNJprUz){GhhZhxRbzi = true;}
      while(szZpXsTDPJ == NLLxrZuAoD){BtirzZiHda = true;}
      while(rnwceyKJYh == rnwceyKJYh){gaqyTYkeFL = true;}
      while(sYrdNJprUz == sYrdNJprUz){HMEJnyEDfT = true;}
      if(NGGmlbxKXn == true){NGGmlbxKXn = false;}
      if(maZIjqTlQN == true){maZIjqTlQN = false;}
      if(eqaHLTGubO == true){eqaHLTGubO = false;}
      if(CahPwkgJqD == true){CahPwkgJqD = false;}
      if(AzljuRyjsW == true){AzljuRyjsW = false;}
      if(pEaGUWezaR == true){pEaGUWezaR = false;}
      if(VChJkLrKLz == true){VChJkLrKLz = false;}
      if(KJtNNeFqMs == true){KJtNNeFqMs = false;}
      if(VVBFYyzbuZ == true){VVBFYyzbuZ = false;}
      if(GhhZhxRbzi == true){GhhZhxRbzi = false;}
      if(YnXtMfKNso == true){YnXtMfKNso = false;}
      if(RnlgwzBckm == true){RnlgwzBckm = false;}
      if(LQOlsbbUfP == true){LQOlsbbUfP = false;}
      if(NcqcTgyGsr == true){NcqcTgyGsr = false;}
      if(nlhGIRuAdh == true){nlhGIRuAdh = false;}
      if(wnqLXIZlBj == true){wnqLXIZlBj = false;}
      if(EogdanwJMO == true){EogdanwJMO = false;}
      if(BtirzZiHda == true){BtirzZiHda = false;}
      if(gaqyTYkeFL == true){gaqyTYkeFL = false;}
      if(HMEJnyEDfT == true){HMEJnyEDfT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVIVYSRNOP
{ 
  void eoJCXkBlGg()
  { 
      bool uoLTgNuWRX = false;
      bool JyxwreiTHm = false;
      bool LlZkiIndRX = false;
      bool gSYaGWosMf = false;
      bool izUwelkdbY = false;
      bool RMOcrJOakY = false;
      bool YQEspqYWoU = false;
      bool poHbDLRdGx = false;
      bool WJCsFUDwhx = false;
      bool INImGRtaFn = false;
      bool NOnGicEmZf = false;
      bool qkUmCONLnV = false;
      bool mcnrMbfTVk = false;
      bool QqXRjIVwJc = false;
      bool PQWCFWsUkq = false;
      bool EimjBkawsG = false;
      bool wkQnOAMCDt = false;
      bool sRBLFVFklp = false;
      bool iKidghDnQy = false;
      bool gYCCfeAhmF = false;
      string jPSqPppDUs;
      string bKznJIEmSh;
      string JYWVZonIEJ;
      string ZwBErPeRFb;
      string xRKfYWFmOd;
      string GeWGgKswRa;
      string CgzKSfItws;
      string dmgqkqOqxC;
      string iBtZDuYtWg;
      string WhAeYPSzNr;
      string OKqUASyeVo;
      string wCzOqBmYGW;
      string GOWOWumBRU;
      string YOcFnXKYZj;
      string xsXgkUilmX;
      string btsqkznbyF;
      string fwNBQgYtZT;
      string pOzVYNpodC;
      string MBNssdVlTn;
      string jhZUEBfWQD;
      if(jPSqPppDUs == OKqUASyeVo){uoLTgNuWRX = true;}
      else if(OKqUASyeVo == jPSqPppDUs){NOnGicEmZf = true;}
      if(bKznJIEmSh == wCzOqBmYGW){JyxwreiTHm = true;}
      else if(wCzOqBmYGW == bKznJIEmSh){qkUmCONLnV = true;}
      if(JYWVZonIEJ == GOWOWumBRU){LlZkiIndRX = true;}
      else if(GOWOWumBRU == JYWVZonIEJ){mcnrMbfTVk = true;}
      if(ZwBErPeRFb == YOcFnXKYZj){gSYaGWosMf = true;}
      else if(YOcFnXKYZj == ZwBErPeRFb){QqXRjIVwJc = true;}
      if(xRKfYWFmOd == xsXgkUilmX){izUwelkdbY = true;}
      else if(xsXgkUilmX == xRKfYWFmOd){PQWCFWsUkq = true;}
      if(GeWGgKswRa == btsqkznbyF){RMOcrJOakY = true;}
      else if(btsqkznbyF == GeWGgKswRa){EimjBkawsG = true;}
      if(CgzKSfItws == fwNBQgYtZT){YQEspqYWoU = true;}
      else if(fwNBQgYtZT == CgzKSfItws){wkQnOAMCDt = true;}
      if(dmgqkqOqxC == pOzVYNpodC){poHbDLRdGx = true;}
      if(iBtZDuYtWg == MBNssdVlTn){WJCsFUDwhx = true;}
      if(WhAeYPSzNr == jhZUEBfWQD){INImGRtaFn = true;}
      while(pOzVYNpodC == dmgqkqOqxC){sRBLFVFklp = true;}
      while(MBNssdVlTn == MBNssdVlTn){iKidghDnQy = true;}
      while(jhZUEBfWQD == jhZUEBfWQD){gYCCfeAhmF = true;}
      if(uoLTgNuWRX == true){uoLTgNuWRX = false;}
      if(JyxwreiTHm == true){JyxwreiTHm = false;}
      if(LlZkiIndRX == true){LlZkiIndRX = false;}
      if(gSYaGWosMf == true){gSYaGWosMf = false;}
      if(izUwelkdbY == true){izUwelkdbY = false;}
      if(RMOcrJOakY == true){RMOcrJOakY = false;}
      if(YQEspqYWoU == true){YQEspqYWoU = false;}
      if(poHbDLRdGx == true){poHbDLRdGx = false;}
      if(WJCsFUDwhx == true){WJCsFUDwhx = false;}
      if(INImGRtaFn == true){INImGRtaFn = false;}
      if(NOnGicEmZf == true){NOnGicEmZf = false;}
      if(qkUmCONLnV == true){qkUmCONLnV = false;}
      if(mcnrMbfTVk == true){mcnrMbfTVk = false;}
      if(QqXRjIVwJc == true){QqXRjIVwJc = false;}
      if(PQWCFWsUkq == true){PQWCFWsUkq = false;}
      if(EimjBkawsG == true){EimjBkawsG = false;}
      if(wkQnOAMCDt == true){wkQnOAMCDt = false;}
      if(sRBLFVFklp == true){sRBLFVFklp = false;}
      if(iKidghDnQy == true){iKidghDnQy = false;}
      if(gYCCfeAhmF == true){gYCCfeAhmF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEGADGJFUH
{ 
  void FrtaijMaRA()
  { 
      bool ALFJUrVQEn = false;
      bool OGcgeoJaDJ = false;
      bool hVKBWamRDZ = false;
      bool DmdMoFuxyW = false;
      bool uQoMCRBnmp = false;
      bool TBaHqeADlt = false;
      bool FDMejacPqY = false;
      bool sLbgORgyzF = false;
      bool YyeMFBLWVK = false;
      bool ErLERqDJca = false;
      bool nkwNxHZtrY = false;
      bool yCDgVGXAYh = false;
      bool OGtgTBAXOW = false;
      bool NWUYQmBRPy = false;
      bool bRdwMBndiK = false;
      bool TDktLhqPsw = false;
      bool HCeVLaheQh = false;
      bool EFjaFxcyUS = false;
      bool MWoDDKlaNh = false;
      bool wlYTqZlIkk = false;
      string XzLxgNIfOF;
      string mduclbODar;
      string endjlpfkgT;
      string lVhPSAgzQG;
      string ZDBYorXyOg;
      string fOJBYiUbKp;
      string gXztTQweJk;
      string tOlTSamFtt;
      string ShVAnWMfpj;
      string eFoaZCEGEY;
      string wrnclQboix;
      string uPgQWzByGx;
      string EPoZFoZLtP;
      string WgAVxasrOW;
      string tXxsnPXYEa;
      string AFAHUgCOWw;
      string qQtSaOOLSu;
      string FIjiCgRwlp;
      string RBGTOQgsAQ;
      string YeVRfcceRY;
      if(XzLxgNIfOF == wrnclQboix){ALFJUrVQEn = true;}
      else if(wrnclQboix == XzLxgNIfOF){nkwNxHZtrY = true;}
      if(mduclbODar == uPgQWzByGx){OGcgeoJaDJ = true;}
      else if(uPgQWzByGx == mduclbODar){yCDgVGXAYh = true;}
      if(endjlpfkgT == EPoZFoZLtP){hVKBWamRDZ = true;}
      else if(EPoZFoZLtP == endjlpfkgT){OGtgTBAXOW = true;}
      if(lVhPSAgzQG == WgAVxasrOW){DmdMoFuxyW = true;}
      else if(WgAVxasrOW == lVhPSAgzQG){NWUYQmBRPy = true;}
      if(ZDBYorXyOg == tXxsnPXYEa){uQoMCRBnmp = true;}
      else if(tXxsnPXYEa == ZDBYorXyOg){bRdwMBndiK = true;}
      if(fOJBYiUbKp == AFAHUgCOWw){TBaHqeADlt = true;}
      else if(AFAHUgCOWw == fOJBYiUbKp){TDktLhqPsw = true;}
      if(gXztTQweJk == qQtSaOOLSu){FDMejacPqY = true;}
      else if(qQtSaOOLSu == gXztTQweJk){HCeVLaheQh = true;}
      if(tOlTSamFtt == FIjiCgRwlp){sLbgORgyzF = true;}
      if(ShVAnWMfpj == RBGTOQgsAQ){YyeMFBLWVK = true;}
      if(eFoaZCEGEY == YeVRfcceRY){ErLERqDJca = true;}
      while(FIjiCgRwlp == tOlTSamFtt){EFjaFxcyUS = true;}
      while(RBGTOQgsAQ == RBGTOQgsAQ){MWoDDKlaNh = true;}
      while(YeVRfcceRY == YeVRfcceRY){wlYTqZlIkk = true;}
      if(ALFJUrVQEn == true){ALFJUrVQEn = false;}
      if(OGcgeoJaDJ == true){OGcgeoJaDJ = false;}
      if(hVKBWamRDZ == true){hVKBWamRDZ = false;}
      if(DmdMoFuxyW == true){DmdMoFuxyW = false;}
      if(uQoMCRBnmp == true){uQoMCRBnmp = false;}
      if(TBaHqeADlt == true){TBaHqeADlt = false;}
      if(FDMejacPqY == true){FDMejacPqY = false;}
      if(sLbgORgyzF == true){sLbgORgyzF = false;}
      if(YyeMFBLWVK == true){YyeMFBLWVK = false;}
      if(ErLERqDJca == true){ErLERqDJca = false;}
      if(nkwNxHZtrY == true){nkwNxHZtrY = false;}
      if(yCDgVGXAYh == true){yCDgVGXAYh = false;}
      if(OGtgTBAXOW == true){OGtgTBAXOW = false;}
      if(NWUYQmBRPy == true){NWUYQmBRPy = false;}
      if(bRdwMBndiK == true){bRdwMBndiK = false;}
      if(TDktLhqPsw == true){TDktLhqPsw = false;}
      if(HCeVLaheQh == true){HCeVLaheQh = false;}
      if(EFjaFxcyUS == true){EFjaFxcyUS = false;}
      if(MWoDDKlaNh == true){MWoDDKlaNh = false;}
      if(wlYTqZlIkk == true){wlYTqZlIkk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXNPKLBQMM
{ 
  void LECHQdcnlr()
  { 
      bool LTINxgDJFX = false;
      bool AOJUBNypSM = false;
      bool JEnuxUNjIy = false;
      bool ADqzcAXeWU = false;
      bool WGzeSRHTap = false;
      bool bNCATHfNQc = false;
      bool SSAHXxWJqB = false;
      bool oSSyoDEIbe = false;
      bool NtJRVlApfV = false;
      bool UKOtBEFrHV = false;
      bool tybYAJuELQ = false;
      bool CWklOYJikl = false;
      bool wgdVgeEYwj = false;
      bool xMBGjORjQM = false;
      bool qudOSxZcec = false;
      bool uVGUYNTFrV = false;
      bool FVIbTpVdBA = false;
      bool GYSYuACODj = false;
      bool EasToaFfgV = false;
      bool uLrtGUmCub = false;
      string xUalgERcyX;
      string WhGqpAQhUN;
      string GQSYpdnEQl;
      string iXUYuRldZp;
      string tnuLuEFPpQ;
      string mmtYugCCuC;
      string PMLLnyMguY;
      string OmIeSSUHdl;
      string XYNAzwdwcO;
      string PjhWahbiWx;
      string qXTRBzdOFc;
      string LtXJdqyLMq;
      string TQEgIeElEk;
      string plkgtAEwyz;
      string SPqzDULXrj;
      string iPWecaTmIV;
      string trKUlYJqPd;
      string lCMMYEZEdn;
      string TgsUBZPFDT;
      string gQncEaEVMd;
      if(xUalgERcyX == qXTRBzdOFc){LTINxgDJFX = true;}
      else if(qXTRBzdOFc == xUalgERcyX){tybYAJuELQ = true;}
      if(WhGqpAQhUN == LtXJdqyLMq){AOJUBNypSM = true;}
      else if(LtXJdqyLMq == WhGqpAQhUN){CWklOYJikl = true;}
      if(GQSYpdnEQl == TQEgIeElEk){JEnuxUNjIy = true;}
      else if(TQEgIeElEk == GQSYpdnEQl){wgdVgeEYwj = true;}
      if(iXUYuRldZp == plkgtAEwyz){ADqzcAXeWU = true;}
      else if(plkgtAEwyz == iXUYuRldZp){xMBGjORjQM = true;}
      if(tnuLuEFPpQ == SPqzDULXrj){WGzeSRHTap = true;}
      else if(SPqzDULXrj == tnuLuEFPpQ){qudOSxZcec = true;}
      if(mmtYugCCuC == iPWecaTmIV){bNCATHfNQc = true;}
      else if(iPWecaTmIV == mmtYugCCuC){uVGUYNTFrV = true;}
      if(PMLLnyMguY == trKUlYJqPd){SSAHXxWJqB = true;}
      else if(trKUlYJqPd == PMLLnyMguY){FVIbTpVdBA = true;}
      if(OmIeSSUHdl == lCMMYEZEdn){oSSyoDEIbe = true;}
      if(XYNAzwdwcO == TgsUBZPFDT){NtJRVlApfV = true;}
      if(PjhWahbiWx == gQncEaEVMd){UKOtBEFrHV = true;}
      while(lCMMYEZEdn == OmIeSSUHdl){GYSYuACODj = true;}
      while(TgsUBZPFDT == TgsUBZPFDT){EasToaFfgV = true;}
      while(gQncEaEVMd == gQncEaEVMd){uLrtGUmCub = true;}
      if(LTINxgDJFX == true){LTINxgDJFX = false;}
      if(AOJUBNypSM == true){AOJUBNypSM = false;}
      if(JEnuxUNjIy == true){JEnuxUNjIy = false;}
      if(ADqzcAXeWU == true){ADqzcAXeWU = false;}
      if(WGzeSRHTap == true){WGzeSRHTap = false;}
      if(bNCATHfNQc == true){bNCATHfNQc = false;}
      if(SSAHXxWJqB == true){SSAHXxWJqB = false;}
      if(oSSyoDEIbe == true){oSSyoDEIbe = false;}
      if(NtJRVlApfV == true){NtJRVlApfV = false;}
      if(UKOtBEFrHV == true){UKOtBEFrHV = false;}
      if(tybYAJuELQ == true){tybYAJuELQ = false;}
      if(CWklOYJikl == true){CWklOYJikl = false;}
      if(wgdVgeEYwj == true){wgdVgeEYwj = false;}
      if(xMBGjORjQM == true){xMBGjORjQM = false;}
      if(qudOSxZcec == true){qudOSxZcec = false;}
      if(uVGUYNTFrV == true){uVGUYNTFrV = false;}
      if(FVIbTpVdBA == true){FVIbTpVdBA = false;}
      if(GYSYuACODj == true){GYSYuACODj = false;}
      if(EasToaFfgV == true){EasToaFfgV = false;}
      if(uLrtGUmCub == true){uLrtGUmCub = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFCNFRUHJH
{ 
  void iQznXXXGPI()
  { 
      bool jzDxkNATwb = false;
      bool aTMqfulcJn = false;
      bool UryZEOTIcO = false;
      bool NCBCYWhbkG = false;
      bool cBZrWTzjzV = false;
      bool ERmYUrBcrV = false;
      bool tqqgNXSJRI = false;
      bool MJrCKTSFDj = false;
      bool PjIGKwPbhf = false;
      bool UFjOMkKrdz = false;
      bool BoRqItYjNB = false;
      bool ZuYHGJijWR = false;
      bool HpblnHZdpZ = false;
      bool JZaEiZSRyP = false;
      bool XfOfGZfcHC = false;
      bool BZUMqKMfDA = false;
      bool UttmrzTUXf = false;
      bool qRkGsbbwfO = false;
      bool bxVmXiFONY = false;
      bool NmOxuclanG = false;
      string iGbwsxylAR;
      string ezZsCictmu;
      string cXjLbdFosT;
      string dzsUPIFrWy;
      string nCkzSEfIDU;
      string czWNIKWPTO;
      string qIsgmeFFct;
      string djWoHZmjrX;
      string yxlXpebfME;
      string koXHGeIELm;
      string zaeJpsbhFh;
      string XmWwQtWUqI;
      string DYrYInMPhb;
      string QhYEXWSbgx;
      string CtZdfyRapM;
      string ImNCjZhFBC;
      string fLzdRpNSXs;
      string atmsGIzNsJ;
      string VkYVTcUVTx;
      string nMaeQqtwMp;
      if(iGbwsxylAR == zaeJpsbhFh){jzDxkNATwb = true;}
      else if(zaeJpsbhFh == iGbwsxylAR){BoRqItYjNB = true;}
      if(ezZsCictmu == XmWwQtWUqI){aTMqfulcJn = true;}
      else if(XmWwQtWUqI == ezZsCictmu){ZuYHGJijWR = true;}
      if(cXjLbdFosT == DYrYInMPhb){UryZEOTIcO = true;}
      else if(DYrYInMPhb == cXjLbdFosT){HpblnHZdpZ = true;}
      if(dzsUPIFrWy == QhYEXWSbgx){NCBCYWhbkG = true;}
      else if(QhYEXWSbgx == dzsUPIFrWy){JZaEiZSRyP = true;}
      if(nCkzSEfIDU == CtZdfyRapM){cBZrWTzjzV = true;}
      else if(CtZdfyRapM == nCkzSEfIDU){XfOfGZfcHC = true;}
      if(czWNIKWPTO == ImNCjZhFBC){ERmYUrBcrV = true;}
      else if(ImNCjZhFBC == czWNIKWPTO){BZUMqKMfDA = true;}
      if(qIsgmeFFct == fLzdRpNSXs){tqqgNXSJRI = true;}
      else if(fLzdRpNSXs == qIsgmeFFct){UttmrzTUXf = true;}
      if(djWoHZmjrX == atmsGIzNsJ){MJrCKTSFDj = true;}
      if(yxlXpebfME == VkYVTcUVTx){PjIGKwPbhf = true;}
      if(koXHGeIELm == nMaeQqtwMp){UFjOMkKrdz = true;}
      while(atmsGIzNsJ == djWoHZmjrX){qRkGsbbwfO = true;}
      while(VkYVTcUVTx == VkYVTcUVTx){bxVmXiFONY = true;}
      while(nMaeQqtwMp == nMaeQqtwMp){NmOxuclanG = true;}
      if(jzDxkNATwb == true){jzDxkNATwb = false;}
      if(aTMqfulcJn == true){aTMqfulcJn = false;}
      if(UryZEOTIcO == true){UryZEOTIcO = false;}
      if(NCBCYWhbkG == true){NCBCYWhbkG = false;}
      if(cBZrWTzjzV == true){cBZrWTzjzV = false;}
      if(ERmYUrBcrV == true){ERmYUrBcrV = false;}
      if(tqqgNXSJRI == true){tqqgNXSJRI = false;}
      if(MJrCKTSFDj == true){MJrCKTSFDj = false;}
      if(PjIGKwPbhf == true){PjIGKwPbhf = false;}
      if(UFjOMkKrdz == true){UFjOMkKrdz = false;}
      if(BoRqItYjNB == true){BoRqItYjNB = false;}
      if(ZuYHGJijWR == true){ZuYHGJijWR = false;}
      if(HpblnHZdpZ == true){HpblnHZdpZ = false;}
      if(JZaEiZSRyP == true){JZaEiZSRyP = false;}
      if(XfOfGZfcHC == true){XfOfGZfcHC = false;}
      if(BZUMqKMfDA == true){BZUMqKMfDA = false;}
      if(UttmrzTUXf == true){UttmrzTUXf = false;}
      if(qRkGsbbwfO == true){qRkGsbbwfO = false;}
      if(bxVmXiFONY == true){bxVmXiFONY = false;}
      if(NmOxuclanG == true){NmOxuclanG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHJMSDFTQW
{ 
  void BSpLpsPRDB()
  { 
      bool PyYJCaPbxP = false;
      bool wQGypOgtbl = false;
      bool AdAGkcarCk = false;
      bool YeegKFAJaS = false;
      bool snWBGDILut = false;
      bool uWctGlyRXZ = false;
      bool AWYLqQkYmk = false;
      bool NXSJsLGyAh = false;
      bool TOxIpCBkaY = false;
      bool HikBRVPLKo = false;
      bool SjXKfXDTBt = false;
      bool ezQpFkZQVn = false;
      bool OAyOddlRqW = false;
      bool wunLOiplbR = false;
      bool zhiftHStuf = false;
      bool uzoWZSkJgB = false;
      bool klcdyjLEaV = false;
      bool unnDogQSTV = false;
      bool LrVKaxFRlw = false;
      bool xfEZgNEEgJ = false;
      string RsHxUPDmVC;
      string QdEaagcnuk;
      string TwkIdAplhV;
      string yCQlQyFtlX;
      string xJwEzDkTpn;
      string dlROJVIzTT;
      string ZQEADOMRJc;
      string ahCWmJAfIa;
      string PVwsrMjCcu;
      string oGaSygFuBk;
      string qSKMNujubz;
      string VbprDDUKIp;
      string dKoOnTHiXG;
      string EEeXixLifw;
      string cnZcYNQhPt;
      string MtmKGgcuYt;
      string nAXUuRxRJF;
      string rkeLNpjMoa;
      string DYTcsJQTRC;
      string TPKlIbQEgH;
      if(RsHxUPDmVC == qSKMNujubz){PyYJCaPbxP = true;}
      else if(qSKMNujubz == RsHxUPDmVC){SjXKfXDTBt = true;}
      if(QdEaagcnuk == VbprDDUKIp){wQGypOgtbl = true;}
      else if(VbprDDUKIp == QdEaagcnuk){ezQpFkZQVn = true;}
      if(TwkIdAplhV == dKoOnTHiXG){AdAGkcarCk = true;}
      else if(dKoOnTHiXG == TwkIdAplhV){OAyOddlRqW = true;}
      if(yCQlQyFtlX == EEeXixLifw){YeegKFAJaS = true;}
      else if(EEeXixLifw == yCQlQyFtlX){wunLOiplbR = true;}
      if(xJwEzDkTpn == cnZcYNQhPt){snWBGDILut = true;}
      else if(cnZcYNQhPt == xJwEzDkTpn){zhiftHStuf = true;}
      if(dlROJVIzTT == MtmKGgcuYt){uWctGlyRXZ = true;}
      else if(MtmKGgcuYt == dlROJVIzTT){uzoWZSkJgB = true;}
      if(ZQEADOMRJc == nAXUuRxRJF){AWYLqQkYmk = true;}
      else if(nAXUuRxRJF == ZQEADOMRJc){klcdyjLEaV = true;}
      if(ahCWmJAfIa == rkeLNpjMoa){NXSJsLGyAh = true;}
      if(PVwsrMjCcu == DYTcsJQTRC){TOxIpCBkaY = true;}
      if(oGaSygFuBk == TPKlIbQEgH){HikBRVPLKo = true;}
      while(rkeLNpjMoa == ahCWmJAfIa){unnDogQSTV = true;}
      while(DYTcsJQTRC == DYTcsJQTRC){LrVKaxFRlw = true;}
      while(TPKlIbQEgH == TPKlIbQEgH){xfEZgNEEgJ = true;}
      if(PyYJCaPbxP == true){PyYJCaPbxP = false;}
      if(wQGypOgtbl == true){wQGypOgtbl = false;}
      if(AdAGkcarCk == true){AdAGkcarCk = false;}
      if(YeegKFAJaS == true){YeegKFAJaS = false;}
      if(snWBGDILut == true){snWBGDILut = false;}
      if(uWctGlyRXZ == true){uWctGlyRXZ = false;}
      if(AWYLqQkYmk == true){AWYLqQkYmk = false;}
      if(NXSJsLGyAh == true){NXSJsLGyAh = false;}
      if(TOxIpCBkaY == true){TOxIpCBkaY = false;}
      if(HikBRVPLKo == true){HikBRVPLKo = false;}
      if(SjXKfXDTBt == true){SjXKfXDTBt = false;}
      if(ezQpFkZQVn == true){ezQpFkZQVn = false;}
      if(OAyOddlRqW == true){OAyOddlRqW = false;}
      if(wunLOiplbR == true){wunLOiplbR = false;}
      if(zhiftHStuf == true){zhiftHStuf = false;}
      if(uzoWZSkJgB == true){uzoWZSkJgB = false;}
      if(klcdyjLEaV == true){klcdyjLEaV = false;}
      if(unnDogQSTV == true){unnDogQSTV = false;}
      if(LrVKaxFRlw == true){LrVKaxFRlw = false;}
      if(xfEZgNEEgJ == true){xfEZgNEEgJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFBJLBEHVC
{ 
  void oJNzXcacrd()
  { 
      bool dbJoJexSfc = false;
      bool fqbqMNOoQJ = false;
      bool HUzWOcwXjd = false;
      bool RHaxXfyalB = false;
      bool izUCqaWiOo = false;
      bool gumKsIclaf = false;
      bool hZiBKYQeTg = false;
      bool OnDOaIzxem = false;
      bool FMItxVTPDP = false;
      bool DLzFSIQTqS = false;
      bool JrPhZrqXjj = false;
      bool IfGmZVQnEo = false;
      bool EAaEcDnywR = false;
      bool qfFMdNwaUE = false;
      bool eufSGXEMex = false;
      bool rbOCNJQLEW = false;
      bool EsbSsbZtJM = false;
      bool YpTAKJUHxF = false;
      bool yaSzZPRDyT = false;
      bool wkWyzkSNZe = false;
      string IxcnSrwuep;
      string ucJHxBOmkc;
      string nWHcMgSoUN;
      string zglWKSsnsN;
      string BShuQtguZp;
      string HJqGploAak;
      string YGZRpNqmxe;
      string HZsWbVnLMR;
      string zWOeGppefY;
      string csNHntrQFC;
      string DtytihPTeU;
      string xcmJlBruKz;
      string XLGYBNLkhh;
      string dXGJOFYUwY;
      string ZVALaAFEVl;
      string CwFFeqmZsU;
      string VdkwpZWdtg;
      string cXzlZCLuxB;
      string HHPufgRBeX;
      string RzaaCukDUA;
      if(IxcnSrwuep == DtytihPTeU){dbJoJexSfc = true;}
      else if(DtytihPTeU == IxcnSrwuep){JrPhZrqXjj = true;}
      if(ucJHxBOmkc == xcmJlBruKz){fqbqMNOoQJ = true;}
      else if(xcmJlBruKz == ucJHxBOmkc){IfGmZVQnEo = true;}
      if(nWHcMgSoUN == XLGYBNLkhh){HUzWOcwXjd = true;}
      else if(XLGYBNLkhh == nWHcMgSoUN){EAaEcDnywR = true;}
      if(zglWKSsnsN == dXGJOFYUwY){RHaxXfyalB = true;}
      else if(dXGJOFYUwY == zglWKSsnsN){qfFMdNwaUE = true;}
      if(BShuQtguZp == ZVALaAFEVl){izUCqaWiOo = true;}
      else if(ZVALaAFEVl == BShuQtguZp){eufSGXEMex = true;}
      if(HJqGploAak == CwFFeqmZsU){gumKsIclaf = true;}
      else if(CwFFeqmZsU == HJqGploAak){rbOCNJQLEW = true;}
      if(YGZRpNqmxe == VdkwpZWdtg){hZiBKYQeTg = true;}
      else if(VdkwpZWdtg == YGZRpNqmxe){EsbSsbZtJM = true;}
      if(HZsWbVnLMR == cXzlZCLuxB){OnDOaIzxem = true;}
      if(zWOeGppefY == HHPufgRBeX){FMItxVTPDP = true;}
      if(csNHntrQFC == RzaaCukDUA){DLzFSIQTqS = true;}
      while(cXzlZCLuxB == HZsWbVnLMR){YpTAKJUHxF = true;}
      while(HHPufgRBeX == HHPufgRBeX){yaSzZPRDyT = true;}
      while(RzaaCukDUA == RzaaCukDUA){wkWyzkSNZe = true;}
      if(dbJoJexSfc == true){dbJoJexSfc = false;}
      if(fqbqMNOoQJ == true){fqbqMNOoQJ = false;}
      if(HUzWOcwXjd == true){HUzWOcwXjd = false;}
      if(RHaxXfyalB == true){RHaxXfyalB = false;}
      if(izUCqaWiOo == true){izUCqaWiOo = false;}
      if(gumKsIclaf == true){gumKsIclaf = false;}
      if(hZiBKYQeTg == true){hZiBKYQeTg = false;}
      if(OnDOaIzxem == true){OnDOaIzxem = false;}
      if(FMItxVTPDP == true){FMItxVTPDP = false;}
      if(DLzFSIQTqS == true){DLzFSIQTqS = false;}
      if(JrPhZrqXjj == true){JrPhZrqXjj = false;}
      if(IfGmZVQnEo == true){IfGmZVQnEo = false;}
      if(EAaEcDnywR == true){EAaEcDnywR = false;}
      if(qfFMdNwaUE == true){qfFMdNwaUE = false;}
      if(eufSGXEMex == true){eufSGXEMex = false;}
      if(rbOCNJQLEW == true){rbOCNJQLEW = false;}
      if(EsbSsbZtJM == true){EsbSsbZtJM = false;}
      if(YpTAKJUHxF == true){YpTAKJUHxF = false;}
      if(yaSzZPRDyT == true){yaSzZPRDyT = false;}
      if(wkWyzkSNZe == true){wkWyzkSNZe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMBIWWWEYI
{ 
  void mTwtoAfAVo()
  { 
      bool PDqiCASMpt = false;
      bool KHxEkcieEX = false;
      bool xelLrelsom = false;
      bool pJtPTJPiep = false;
      bool HHlxhYFmYg = false;
      bool tDaYTjQfqW = false;
      bool OZWDDANgjb = false;
      bool NzzNPosncS = false;
      bool ZyTHrmhUwj = false;
      bool rirIbhkhtg = false;
      bool LXCxTuDMJd = false;
      bool pbDXwPFPLQ = false;
      bool SrkAieHqlh = false;
      bool EKtuGBuWnx = false;
      bool iULRtPfTLL = false;
      bool bUWdOTmCNn = false;
      bool nLabYehHQu = false;
      bool TiaOgxgSFS = false;
      bool zmfZFinQgm = false;
      bool OsIzIWtirO = false;
      string LcSeJVhdsl;
      string QjCSQcmdSu;
      string iYyeckZsNP;
      string eXaXTtKsmy;
      string fAkKfWRuRL;
      string gUyhelenBY;
      string wnPdGsIeyV;
      string RtqTOinmyG;
      string SebChKYsrh;
      string OWqOCqjHDm;
      string OlwusmddSw;
      string yqouFQLMuw;
      string TPmQGtCbRW;
      string yfiLqfhgJu;
      string ftauiWhuIk;
      string fWLHSzzeny;
      string jCMuyRHdDY;
      string ieDzQYnqgi;
      string MGSgqaTbrr;
      string gDrKKdhexR;
      if(LcSeJVhdsl == OlwusmddSw){PDqiCASMpt = true;}
      else if(OlwusmddSw == LcSeJVhdsl){LXCxTuDMJd = true;}
      if(QjCSQcmdSu == yqouFQLMuw){KHxEkcieEX = true;}
      else if(yqouFQLMuw == QjCSQcmdSu){pbDXwPFPLQ = true;}
      if(iYyeckZsNP == TPmQGtCbRW){xelLrelsom = true;}
      else if(TPmQGtCbRW == iYyeckZsNP){SrkAieHqlh = true;}
      if(eXaXTtKsmy == yfiLqfhgJu){pJtPTJPiep = true;}
      else if(yfiLqfhgJu == eXaXTtKsmy){EKtuGBuWnx = true;}
      if(fAkKfWRuRL == ftauiWhuIk){HHlxhYFmYg = true;}
      else if(ftauiWhuIk == fAkKfWRuRL){iULRtPfTLL = true;}
      if(gUyhelenBY == fWLHSzzeny){tDaYTjQfqW = true;}
      else if(fWLHSzzeny == gUyhelenBY){bUWdOTmCNn = true;}
      if(wnPdGsIeyV == jCMuyRHdDY){OZWDDANgjb = true;}
      else if(jCMuyRHdDY == wnPdGsIeyV){nLabYehHQu = true;}
      if(RtqTOinmyG == ieDzQYnqgi){NzzNPosncS = true;}
      if(SebChKYsrh == MGSgqaTbrr){ZyTHrmhUwj = true;}
      if(OWqOCqjHDm == gDrKKdhexR){rirIbhkhtg = true;}
      while(ieDzQYnqgi == RtqTOinmyG){TiaOgxgSFS = true;}
      while(MGSgqaTbrr == MGSgqaTbrr){zmfZFinQgm = true;}
      while(gDrKKdhexR == gDrKKdhexR){OsIzIWtirO = true;}
      if(PDqiCASMpt == true){PDqiCASMpt = false;}
      if(KHxEkcieEX == true){KHxEkcieEX = false;}
      if(xelLrelsom == true){xelLrelsom = false;}
      if(pJtPTJPiep == true){pJtPTJPiep = false;}
      if(HHlxhYFmYg == true){HHlxhYFmYg = false;}
      if(tDaYTjQfqW == true){tDaYTjQfqW = false;}
      if(OZWDDANgjb == true){OZWDDANgjb = false;}
      if(NzzNPosncS == true){NzzNPosncS = false;}
      if(ZyTHrmhUwj == true){ZyTHrmhUwj = false;}
      if(rirIbhkhtg == true){rirIbhkhtg = false;}
      if(LXCxTuDMJd == true){LXCxTuDMJd = false;}
      if(pbDXwPFPLQ == true){pbDXwPFPLQ = false;}
      if(SrkAieHqlh == true){SrkAieHqlh = false;}
      if(EKtuGBuWnx == true){EKtuGBuWnx = false;}
      if(iULRtPfTLL == true){iULRtPfTLL = false;}
      if(bUWdOTmCNn == true){bUWdOTmCNn = false;}
      if(nLabYehHQu == true){nLabYehHQu = false;}
      if(TiaOgxgSFS == true){TiaOgxgSFS = false;}
      if(zmfZFinQgm == true){zmfZFinQgm = false;}
      if(OsIzIWtirO == true){OsIzIWtirO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSSBPSPKKY
{ 
  void LpSUxZrgjk()
  { 
      bool HFHchmIgNZ = false;
      bool SVyKwJAuxS = false;
      bool dPPVEcUbwJ = false;
      bool GXhbhkJLNK = false;
      bool VJMsROzRiQ = false;
      bool MqXuYrolXF = false;
      bool RfjDTtnVbK = false;
      bool AoglxTDVDp = false;
      bool cDsfxOAlDp = false;
      bool uWmIsoYIZW = false;
      bool acoXPXJlyE = false;
      bool nTihbNmEGE = false;
      bool tBSlPcBYrH = false;
      bool ttwfOzNVPZ = false;
      bool EOnyBbnFff = false;
      bool CUCUcYKDIm = false;
      bool VkspKtXCSc = false;
      bool zRogzfNTkm = false;
      bool owrMFZraDo = false;
      bool oKMcDTUynH = false;
      string WaRRdnfyAp;
      string fWhQCFpsmx;
      string ZiGPtLcnrR;
      string OjSYaRNqbW;
      string DsLklZiVXI;
      string HOLXWnUBXS;
      string KqGiauDJoj;
      string qzQQtfXUdT;
      string bHQiJAYtBm;
      string xMSJLLmcKp;
      string VZfmRHxudp;
      string PzWEqDaXYZ;
      string WJHCmefHEh;
      string suKnxCbcQC;
      string DcQLWxoORI;
      string kODjTMRcAl;
      string bppuxUoiGo;
      string axGWWssweo;
      string pRouxdqZTk;
      string jyceZNlUOC;
      if(WaRRdnfyAp == VZfmRHxudp){HFHchmIgNZ = true;}
      else if(VZfmRHxudp == WaRRdnfyAp){acoXPXJlyE = true;}
      if(fWhQCFpsmx == PzWEqDaXYZ){SVyKwJAuxS = true;}
      else if(PzWEqDaXYZ == fWhQCFpsmx){nTihbNmEGE = true;}
      if(ZiGPtLcnrR == WJHCmefHEh){dPPVEcUbwJ = true;}
      else if(WJHCmefHEh == ZiGPtLcnrR){tBSlPcBYrH = true;}
      if(OjSYaRNqbW == suKnxCbcQC){GXhbhkJLNK = true;}
      else if(suKnxCbcQC == OjSYaRNqbW){ttwfOzNVPZ = true;}
      if(DsLklZiVXI == DcQLWxoORI){VJMsROzRiQ = true;}
      else if(DcQLWxoORI == DsLklZiVXI){EOnyBbnFff = true;}
      if(HOLXWnUBXS == kODjTMRcAl){MqXuYrolXF = true;}
      else if(kODjTMRcAl == HOLXWnUBXS){CUCUcYKDIm = true;}
      if(KqGiauDJoj == bppuxUoiGo){RfjDTtnVbK = true;}
      else if(bppuxUoiGo == KqGiauDJoj){VkspKtXCSc = true;}
      if(qzQQtfXUdT == axGWWssweo){AoglxTDVDp = true;}
      if(bHQiJAYtBm == pRouxdqZTk){cDsfxOAlDp = true;}
      if(xMSJLLmcKp == jyceZNlUOC){uWmIsoYIZW = true;}
      while(axGWWssweo == qzQQtfXUdT){zRogzfNTkm = true;}
      while(pRouxdqZTk == pRouxdqZTk){owrMFZraDo = true;}
      while(jyceZNlUOC == jyceZNlUOC){oKMcDTUynH = true;}
      if(HFHchmIgNZ == true){HFHchmIgNZ = false;}
      if(SVyKwJAuxS == true){SVyKwJAuxS = false;}
      if(dPPVEcUbwJ == true){dPPVEcUbwJ = false;}
      if(GXhbhkJLNK == true){GXhbhkJLNK = false;}
      if(VJMsROzRiQ == true){VJMsROzRiQ = false;}
      if(MqXuYrolXF == true){MqXuYrolXF = false;}
      if(RfjDTtnVbK == true){RfjDTtnVbK = false;}
      if(AoglxTDVDp == true){AoglxTDVDp = false;}
      if(cDsfxOAlDp == true){cDsfxOAlDp = false;}
      if(uWmIsoYIZW == true){uWmIsoYIZW = false;}
      if(acoXPXJlyE == true){acoXPXJlyE = false;}
      if(nTihbNmEGE == true){nTihbNmEGE = false;}
      if(tBSlPcBYrH == true){tBSlPcBYrH = false;}
      if(ttwfOzNVPZ == true){ttwfOzNVPZ = false;}
      if(EOnyBbnFff == true){EOnyBbnFff = false;}
      if(CUCUcYKDIm == true){CUCUcYKDIm = false;}
      if(VkspKtXCSc == true){VkspKtXCSc = false;}
      if(zRogzfNTkm == true){zRogzfNTkm = false;}
      if(owrMFZraDo == true){owrMFZraDo = false;}
      if(oKMcDTUynH == true){oKMcDTUynH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYOIZOUCKH
{ 
  void WwcggJyJfR()
  { 
      bool pBARqKsjVD = false;
      bool PWQcRmuLjd = false;
      bool KbiVcSwxcl = false;
      bool uihasVAUZc = false;
      bool BKYlcZHDeR = false;
      bool aQGcDOSdnY = false;
      bool NwHjIgnpiw = false;
      bool makHczCxsD = false;
      bool KsRKLebFWe = false;
      bool DVgBOFDocw = false;
      bool kRTieAezAE = false;
      bool MUkkNTewXd = false;
      bool EiTErQsjrW = false;
      bool wNTxRsYhfL = false;
      bool zcERRhkwmt = false;
      bool ZGQzqByOqN = false;
      bool GuHcHyAnSU = false;
      bool uwQMebeBlK = false;
      bool fxwxwpwUFP = false;
      bool tJqRFDUaKS = false;
      string zCMIiNwhMS;
      string qsXBgwJYcT;
      string fbnxtzzWbk;
      string nZsHIZgdOU;
      string jaVVXeCGSC;
      string lWmgOXOPOi;
      string OZGadRAQrH;
      string PfJHjEGRYO;
      string xrDYzRlLrj;
      string KRPeFJUtqG;
      string elNKmFMfxJ;
      string RxpzlVVgbM;
      string enXIxyQeBZ;
      string jMZRjKeslt;
      string EGNhSNaPri;
      string mnRebpNFMo;
      string nhdWZEWYPa;
      string qcthIXZpoj;
      string WAlRmutuos;
      string xYfxFVcqHO;
      if(zCMIiNwhMS == elNKmFMfxJ){pBARqKsjVD = true;}
      else if(elNKmFMfxJ == zCMIiNwhMS){kRTieAezAE = true;}
      if(qsXBgwJYcT == RxpzlVVgbM){PWQcRmuLjd = true;}
      else if(RxpzlVVgbM == qsXBgwJYcT){MUkkNTewXd = true;}
      if(fbnxtzzWbk == enXIxyQeBZ){KbiVcSwxcl = true;}
      else if(enXIxyQeBZ == fbnxtzzWbk){EiTErQsjrW = true;}
      if(nZsHIZgdOU == jMZRjKeslt){uihasVAUZc = true;}
      else if(jMZRjKeslt == nZsHIZgdOU){wNTxRsYhfL = true;}
      if(jaVVXeCGSC == EGNhSNaPri){BKYlcZHDeR = true;}
      else if(EGNhSNaPri == jaVVXeCGSC){zcERRhkwmt = true;}
      if(lWmgOXOPOi == mnRebpNFMo){aQGcDOSdnY = true;}
      else if(mnRebpNFMo == lWmgOXOPOi){ZGQzqByOqN = true;}
      if(OZGadRAQrH == nhdWZEWYPa){NwHjIgnpiw = true;}
      else if(nhdWZEWYPa == OZGadRAQrH){GuHcHyAnSU = true;}
      if(PfJHjEGRYO == qcthIXZpoj){makHczCxsD = true;}
      if(xrDYzRlLrj == WAlRmutuos){KsRKLebFWe = true;}
      if(KRPeFJUtqG == xYfxFVcqHO){DVgBOFDocw = true;}
      while(qcthIXZpoj == PfJHjEGRYO){uwQMebeBlK = true;}
      while(WAlRmutuos == WAlRmutuos){fxwxwpwUFP = true;}
      while(xYfxFVcqHO == xYfxFVcqHO){tJqRFDUaKS = true;}
      if(pBARqKsjVD == true){pBARqKsjVD = false;}
      if(PWQcRmuLjd == true){PWQcRmuLjd = false;}
      if(KbiVcSwxcl == true){KbiVcSwxcl = false;}
      if(uihasVAUZc == true){uihasVAUZc = false;}
      if(BKYlcZHDeR == true){BKYlcZHDeR = false;}
      if(aQGcDOSdnY == true){aQGcDOSdnY = false;}
      if(NwHjIgnpiw == true){NwHjIgnpiw = false;}
      if(makHczCxsD == true){makHczCxsD = false;}
      if(KsRKLebFWe == true){KsRKLebFWe = false;}
      if(DVgBOFDocw == true){DVgBOFDocw = false;}
      if(kRTieAezAE == true){kRTieAezAE = false;}
      if(MUkkNTewXd == true){MUkkNTewXd = false;}
      if(EiTErQsjrW == true){EiTErQsjrW = false;}
      if(wNTxRsYhfL == true){wNTxRsYhfL = false;}
      if(zcERRhkwmt == true){zcERRhkwmt = false;}
      if(ZGQzqByOqN == true){ZGQzqByOqN = false;}
      if(GuHcHyAnSU == true){GuHcHyAnSU = false;}
      if(uwQMebeBlK == true){uwQMebeBlK = false;}
      if(fxwxwpwUFP == true){fxwxwpwUFP = false;}
      if(tJqRFDUaKS == true){tJqRFDUaKS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXBDSONHQM
{ 
  void dImWfbfobO()
  { 
      bool jhnfrMfZLQ = false;
      bool cpEtUJREup = false;
      bool ibnrGJPqlU = false;
      bool btQrpuyYTR = false;
      bool wfqBtJZXzB = false;
      bool odVlDHtuZi = false;
      bool wonpoiZLEY = false;
      bool KsjdtDklyw = false;
      bool irqjexYdoh = false;
      bool BCykUHqALL = false;
      bool jNSZpwsrrA = false;
      bool VHxczExEKr = false;
      bool JuWVXItzJm = false;
      bool LjamMUYQsi = false;
      bool EgknMsFUkP = false;
      bool JloTBnqxCh = false;
      bool BthFnkgKQd = false;
      bool ffKbmcKhJe = false;
      bool CZNscZtGkX = false;
      bool dbOKhKyfAa = false;
      string FoCnUzugBj;
      string BgpTTdpMKW;
      string gfgZBOtePC;
      string imiPSsTTml;
      string goauxsBqic;
      string IogpfYHclF;
      string FQRyAOxZAZ;
      string JWZYprFlcI;
      string MDulstGrjt;
      string kpgggPXbti;
      string uapISlPHAm;
      string SVAcsBUeEG;
      string HEpGoTprqZ;
      string UdqsNlNlTH;
      string dyrwbOoDnf;
      string urXnapkiTz;
      string wWQZSoeGPH;
      string mhLxbJMteZ;
      string dlELecFCSX;
      string AdSULHhRcl;
      if(FoCnUzugBj == uapISlPHAm){jhnfrMfZLQ = true;}
      else if(uapISlPHAm == FoCnUzugBj){jNSZpwsrrA = true;}
      if(BgpTTdpMKW == SVAcsBUeEG){cpEtUJREup = true;}
      else if(SVAcsBUeEG == BgpTTdpMKW){VHxczExEKr = true;}
      if(gfgZBOtePC == HEpGoTprqZ){ibnrGJPqlU = true;}
      else if(HEpGoTprqZ == gfgZBOtePC){JuWVXItzJm = true;}
      if(imiPSsTTml == UdqsNlNlTH){btQrpuyYTR = true;}
      else if(UdqsNlNlTH == imiPSsTTml){LjamMUYQsi = true;}
      if(goauxsBqic == dyrwbOoDnf){wfqBtJZXzB = true;}
      else if(dyrwbOoDnf == goauxsBqic){EgknMsFUkP = true;}
      if(IogpfYHclF == urXnapkiTz){odVlDHtuZi = true;}
      else if(urXnapkiTz == IogpfYHclF){JloTBnqxCh = true;}
      if(FQRyAOxZAZ == wWQZSoeGPH){wonpoiZLEY = true;}
      else if(wWQZSoeGPH == FQRyAOxZAZ){BthFnkgKQd = true;}
      if(JWZYprFlcI == mhLxbJMteZ){KsjdtDklyw = true;}
      if(MDulstGrjt == dlELecFCSX){irqjexYdoh = true;}
      if(kpgggPXbti == AdSULHhRcl){BCykUHqALL = true;}
      while(mhLxbJMteZ == JWZYprFlcI){ffKbmcKhJe = true;}
      while(dlELecFCSX == dlELecFCSX){CZNscZtGkX = true;}
      while(AdSULHhRcl == AdSULHhRcl){dbOKhKyfAa = true;}
      if(jhnfrMfZLQ == true){jhnfrMfZLQ = false;}
      if(cpEtUJREup == true){cpEtUJREup = false;}
      if(ibnrGJPqlU == true){ibnrGJPqlU = false;}
      if(btQrpuyYTR == true){btQrpuyYTR = false;}
      if(wfqBtJZXzB == true){wfqBtJZXzB = false;}
      if(odVlDHtuZi == true){odVlDHtuZi = false;}
      if(wonpoiZLEY == true){wonpoiZLEY = false;}
      if(KsjdtDklyw == true){KsjdtDklyw = false;}
      if(irqjexYdoh == true){irqjexYdoh = false;}
      if(BCykUHqALL == true){BCykUHqALL = false;}
      if(jNSZpwsrrA == true){jNSZpwsrrA = false;}
      if(VHxczExEKr == true){VHxczExEKr = false;}
      if(JuWVXItzJm == true){JuWVXItzJm = false;}
      if(LjamMUYQsi == true){LjamMUYQsi = false;}
      if(EgknMsFUkP == true){EgknMsFUkP = false;}
      if(JloTBnqxCh == true){JloTBnqxCh = false;}
      if(BthFnkgKQd == true){BthFnkgKQd = false;}
      if(ffKbmcKhJe == true){ffKbmcKhJe = false;}
      if(CZNscZtGkX == true){CZNscZtGkX = false;}
      if(dbOKhKyfAa == true){dbOKhKyfAa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXQFCCLKUG
{ 
  void YriBZGWwIB()
  { 
      bool WySbgHCUzL = false;
      bool ceFSjbNZoR = false;
      bool qoFCaBQXYW = false;
      bool sQjGikCuka = false;
      bool hkuHTIWTOS = false;
      bool GViWngsQBf = false;
      bool qdwcRMuyiz = false;
      bool YRnOjFtyhR = false;
      bool ewIGPXhNRB = false;
      bool rltFiDoSoH = false;
      bool NXjPsohTmi = false;
      bool mthiAuVpMt = false;
      bool dgghGlWhff = false;
      bool QbJZDHLrMa = false;
      bool oNZiOyELFn = false;
      bool hzFtcfpCJH = false;
      bool RznGRKkIes = false;
      bool icckEQHySI = false;
      bool hLcqyQVOwX = false;
      bool QJiFIpZTQD = false;
      string TULyTEhrYd;
      string KuLBUgjkVz;
      string ofVTRycYAk;
      string YUwsLcINVi;
      string hLltUAlzcC;
      string HQIiqmyrfU;
      string aJqmFoyRpq;
      string YVPlRdsbzR;
      string McuycHLNCY;
      string dQgAIYTyoe;
      string CTJkclBWRM;
      string sWrOIxNsKx;
      string dkPRMInPds;
      string KulTOsTKUq;
      string GnwpeHXSqK;
      string KanqBRErXU;
      string xksXByjYzP;
      string cCXSqonYlF;
      string jVXShjGuSx;
      string nblztUuXnf;
      if(TULyTEhrYd == CTJkclBWRM){WySbgHCUzL = true;}
      else if(CTJkclBWRM == TULyTEhrYd){NXjPsohTmi = true;}
      if(KuLBUgjkVz == sWrOIxNsKx){ceFSjbNZoR = true;}
      else if(sWrOIxNsKx == KuLBUgjkVz){mthiAuVpMt = true;}
      if(ofVTRycYAk == dkPRMInPds){qoFCaBQXYW = true;}
      else if(dkPRMInPds == ofVTRycYAk){dgghGlWhff = true;}
      if(YUwsLcINVi == KulTOsTKUq){sQjGikCuka = true;}
      else if(KulTOsTKUq == YUwsLcINVi){QbJZDHLrMa = true;}
      if(hLltUAlzcC == GnwpeHXSqK){hkuHTIWTOS = true;}
      else if(GnwpeHXSqK == hLltUAlzcC){oNZiOyELFn = true;}
      if(HQIiqmyrfU == KanqBRErXU){GViWngsQBf = true;}
      else if(KanqBRErXU == HQIiqmyrfU){hzFtcfpCJH = true;}
      if(aJqmFoyRpq == xksXByjYzP){qdwcRMuyiz = true;}
      else if(xksXByjYzP == aJqmFoyRpq){RznGRKkIes = true;}
      if(YVPlRdsbzR == cCXSqonYlF){YRnOjFtyhR = true;}
      if(McuycHLNCY == jVXShjGuSx){ewIGPXhNRB = true;}
      if(dQgAIYTyoe == nblztUuXnf){rltFiDoSoH = true;}
      while(cCXSqonYlF == YVPlRdsbzR){icckEQHySI = true;}
      while(jVXShjGuSx == jVXShjGuSx){hLcqyQVOwX = true;}
      while(nblztUuXnf == nblztUuXnf){QJiFIpZTQD = true;}
      if(WySbgHCUzL == true){WySbgHCUzL = false;}
      if(ceFSjbNZoR == true){ceFSjbNZoR = false;}
      if(qoFCaBQXYW == true){qoFCaBQXYW = false;}
      if(sQjGikCuka == true){sQjGikCuka = false;}
      if(hkuHTIWTOS == true){hkuHTIWTOS = false;}
      if(GViWngsQBf == true){GViWngsQBf = false;}
      if(qdwcRMuyiz == true){qdwcRMuyiz = false;}
      if(YRnOjFtyhR == true){YRnOjFtyhR = false;}
      if(ewIGPXhNRB == true){ewIGPXhNRB = false;}
      if(rltFiDoSoH == true){rltFiDoSoH = false;}
      if(NXjPsohTmi == true){NXjPsohTmi = false;}
      if(mthiAuVpMt == true){mthiAuVpMt = false;}
      if(dgghGlWhff == true){dgghGlWhff = false;}
      if(QbJZDHLrMa == true){QbJZDHLrMa = false;}
      if(oNZiOyELFn == true){oNZiOyELFn = false;}
      if(hzFtcfpCJH == true){hzFtcfpCJH = false;}
      if(RznGRKkIes == true){RznGRKkIes = false;}
      if(icckEQHySI == true){icckEQHySI = false;}
      if(hLcqyQVOwX == true){hLcqyQVOwX = false;}
      if(QJiFIpZTQD == true){QJiFIpZTQD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHRKEJXDPF
{ 
  void kdZLyhStgF()
  { 
      bool arkGBJGxKc = false;
      bool BcDHNLtOmj = false;
      bool LFXmEydsjq = false;
      bool NfFQTKFSrs = false;
      bool tqXWHPYeSQ = false;
      bool cpSqZUUyCC = false;
      bool eNNTOUWmnC = false;
      bool GbWsoThAfn = false;
      bool YyaSOXNNpz = false;
      bool pGQpNgcEHl = false;
      bool slqPKBTYCF = false;
      bool lTSNdfmuEp = false;
      bool HJwoMAKffH = false;
      bool qdssumHKIM = false;
      bool EnLkMVnCLg = false;
      bool thzQdioCCJ = false;
      bool pmstOIaYSp = false;
      bool YbmrlSxLbq = false;
      bool LITyMIebOL = false;
      bool yEHyVRuRWE = false;
      string EKYjEaBbTW;
      string IqOIbhVBiH;
      string sCVdesooWW;
      string YhuklDebQY;
      string tIAeDPiOln;
      string RhogEBotFL;
      string kLFxxZwcWY;
      string DsjJMkCpZO;
      string JaDhEpsOgj;
      string NjWFmiDDgd;
      string TGrNjYyeTS;
      string zyTpBKHWrG;
      string ggulKTWdWd;
      string gzJwuDipxe;
      string rNuNkPPfEc;
      string afKZwmKFCQ;
      string CTIolzoXux;
      string bRZMOTkhBt;
      string DpZsCBnizI;
      string scmfcXFFbk;
      if(EKYjEaBbTW == TGrNjYyeTS){arkGBJGxKc = true;}
      else if(TGrNjYyeTS == EKYjEaBbTW){slqPKBTYCF = true;}
      if(IqOIbhVBiH == zyTpBKHWrG){BcDHNLtOmj = true;}
      else if(zyTpBKHWrG == IqOIbhVBiH){lTSNdfmuEp = true;}
      if(sCVdesooWW == ggulKTWdWd){LFXmEydsjq = true;}
      else if(ggulKTWdWd == sCVdesooWW){HJwoMAKffH = true;}
      if(YhuklDebQY == gzJwuDipxe){NfFQTKFSrs = true;}
      else if(gzJwuDipxe == YhuklDebQY){qdssumHKIM = true;}
      if(tIAeDPiOln == rNuNkPPfEc){tqXWHPYeSQ = true;}
      else if(rNuNkPPfEc == tIAeDPiOln){EnLkMVnCLg = true;}
      if(RhogEBotFL == afKZwmKFCQ){cpSqZUUyCC = true;}
      else if(afKZwmKFCQ == RhogEBotFL){thzQdioCCJ = true;}
      if(kLFxxZwcWY == CTIolzoXux){eNNTOUWmnC = true;}
      else if(CTIolzoXux == kLFxxZwcWY){pmstOIaYSp = true;}
      if(DsjJMkCpZO == bRZMOTkhBt){GbWsoThAfn = true;}
      if(JaDhEpsOgj == DpZsCBnizI){YyaSOXNNpz = true;}
      if(NjWFmiDDgd == scmfcXFFbk){pGQpNgcEHl = true;}
      while(bRZMOTkhBt == DsjJMkCpZO){YbmrlSxLbq = true;}
      while(DpZsCBnizI == DpZsCBnizI){LITyMIebOL = true;}
      while(scmfcXFFbk == scmfcXFFbk){yEHyVRuRWE = true;}
      if(arkGBJGxKc == true){arkGBJGxKc = false;}
      if(BcDHNLtOmj == true){BcDHNLtOmj = false;}
      if(LFXmEydsjq == true){LFXmEydsjq = false;}
      if(NfFQTKFSrs == true){NfFQTKFSrs = false;}
      if(tqXWHPYeSQ == true){tqXWHPYeSQ = false;}
      if(cpSqZUUyCC == true){cpSqZUUyCC = false;}
      if(eNNTOUWmnC == true){eNNTOUWmnC = false;}
      if(GbWsoThAfn == true){GbWsoThAfn = false;}
      if(YyaSOXNNpz == true){YyaSOXNNpz = false;}
      if(pGQpNgcEHl == true){pGQpNgcEHl = false;}
      if(slqPKBTYCF == true){slqPKBTYCF = false;}
      if(lTSNdfmuEp == true){lTSNdfmuEp = false;}
      if(HJwoMAKffH == true){HJwoMAKffH = false;}
      if(qdssumHKIM == true){qdssumHKIM = false;}
      if(EnLkMVnCLg == true){EnLkMVnCLg = false;}
      if(thzQdioCCJ == true){thzQdioCCJ = false;}
      if(pmstOIaYSp == true){pmstOIaYSp = false;}
      if(YbmrlSxLbq == true){YbmrlSxLbq = false;}
      if(LITyMIebOL == true){LITyMIebOL = false;}
      if(yEHyVRuRWE == true){yEHyVRuRWE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVOJPFUVAA
{ 
  void LkniNiAgaf()
  { 
      bool WBNttyLSeU = false;
      bool WkkTYwRWuM = false;
      bool lrWqXIknTi = false;
      bool dirqmgKrWT = false;
      bool gHopDodjCq = false;
      bool jAEbQeeWWl = false;
      bool MWyuqmstfq = false;
      bool kZAbfeDfmh = false;
      bool eAkczceQZI = false;
      bool CnVkGJIszP = false;
      bool wiDKFJAcwk = false;
      bool ayjnGMlVwN = false;
      bool IcTXoxEOUV = false;
      bool VJfWkuxZXo = false;
      bool cCTogDEgdt = false;
      bool XmxkHTPeUH = false;
      bool FkHZORSMDK = false;
      bool OLyGkGIdql = false;
      bool sWjZyiLtPQ = false;
      bool fREPiqttZO = false;
      string oblBHMlEtb;
      string bxcXzCujBG;
      string XjkCSaMHys;
      string rcSiiXjMSi;
      string perrihmdAq;
      string IBqkQFpiig;
      string zeFBizesnb;
      string ShRSQrqsSj;
      string miGHjqkgSd;
      string gAdliLYqIj;
      string DsoYYajYTY;
      string NxQysQXyQr;
      string NxaKtREfjF;
      string SAjhgtshhJ;
      string GMNtPjjesR;
      string maZQWGSedG;
      string VEnNFMMhRy;
      string WoPHkBigtK;
      string hYlRRrZTLa;
      string aODbmCXzoD;
      if(oblBHMlEtb == DsoYYajYTY){WBNttyLSeU = true;}
      else if(DsoYYajYTY == oblBHMlEtb){wiDKFJAcwk = true;}
      if(bxcXzCujBG == NxQysQXyQr){WkkTYwRWuM = true;}
      else if(NxQysQXyQr == bxcXzCujBG){ayjnGMlVwN = true;}
      if(XjkCSaMHys == NxaKtREfjF){lrWqXIknTi = true;}
      else if(NxaKtREfjF == XjkCSaMHys){IcTXoxEOUV = true;}
      if(rcSiiXjMSi == SAjhgtshhJ){dirqmgKrWT = true;}
      else if(SAjhgtshhJ == rcSiiXjMSi){VJfWkuxZXo = true;}
      if(perrihmdAq == GMNtPjjesR){gHopDodjCq = true;}
      else if(GMNtPjjesR == perrihmdAq){cCTogDEgdt = true;}
      if(IBqkQFpiig == maZQWGSedG){jAEbQeeWWl = true;}
      else if(maZQWGSedG == IBqkQFpiig){XmxkHTPeUH = true;}
      if(zeFBizesnb == VEnNFMMhRy){MWyuqmstfq = true;}
      else if(VEnNFMMhRy == zeFBizesnb){FkHZORSMDK = true;}
      if(ShRSQrqsSj == WoPHkBigtK){kZAbfeDfmh = true;}
      if(miGHjqkgSd == hYlRRrZTLa){eAkczceQZI = true;}
      if(gAdliLYqIj == aODbmCXzoD){CnVkGJIszP = true;}
      while(WoPHkBigtK == ShRSQrqsSj){OLyGkGIdql = true;}
      while(hYlRRrZTLa == hYlRRrZTLa){sWjZyiLtPQ = true;}
      while(aODbmCXzoD == aODbmCXzoD){fREPiqttZO = true;}
      if(WBNttyLSeU == true){WBNttyLSeU = false;}
      if(WkkTYwRWuM == true){WkkTYwRWuM = false;}
      if(lrWqXIknTi == true){lrWqXIknTi = false;}
      if(dirqmgKrWT == true){dirqmgKrWT = false;}
      if(gHopDodjCq == true){gHopDodjCq = false;}
      if(jAEbQeeWWl == true){jAEbQeeWWl = false;}
      if(MWyuqmstfq == true){MWyuqmstfq = false;}
      if(kZAbfeDfmh == true){kZAbfeDfmh = false;}
      if(eAkczceQZI == true){eAkczceQZI = false;}
      if(CnVkGJIszP == true){CnVkGJIszP = false;}
      if(wiDKFJAcwk == true){wiDKFJAcwk = false;}
      if(ayjnGMlVwN == true){ayjnGMlVwN = false;}
      if(IcTXoxEOUV == true){IcTXoxEOUV = false;}
      if(VJfWkuxZXo == true){VJfWkuxZXo = false;}
      if(cCTogDEgdt == true){cCTogDEgdt = false;}
      if(XmxkHTPeUH == true){XmxkHTPeUH = false;}
      if(FkHZORSMDK == true){FkHZORSMDK = false;}
      if(OLyGkGIdql == true){OLyGkGIdql = false;}
      if(sWjZyiLtPQ == true){sWjZyiLtPQ = false;}
      if(fREPiqttZO == true){fREPiqttZO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BEALQBRNNH
{ 
  void LGWSizstze()
  { 
      bool rtojAJYgfh = false;
      bool ERArfPQRAs = false;
      bool ETcEEWxdJY = false;
      bool elaCRBCGIH = false;
      bool TqrwfEQOlh = false;
      bool gCQFIYQjfd = false;
      bool LuXGDSqyZe = false;
      bool NJIsYNagYz = false;
      bool FhrbqcUVss = false;
      bool jRaeuYTksM = false;
      bool NRoHUWsXfu = false;
      bool xjLfXcDwPa = false;
      bool yVFgtuicxA = false;
      bool somMlnskHT = false;
      bool ixoywAGuGR = false;
      bool UXVSOrMIMY = false;
      bool nPZeBHwysj = false;
      bool jSnuqAfGkt = false;
      bool onWeeVTUyt = false;
      bool akXhfSXKxn = false;
      string dPkOMyVZsc;
      string ZtDmexQGAB;
      string uSmdtJVBOw;
      string gJeJugchDo;
      string uVBdqItPut;
      string MOmBZKcGUD;
      string cTKxwQOtry;
      string UiDLFZRJll;
      string OGGTiRWdjj;
      string DVMALbLDga;
      string sAXwZdLauA;
      string rTThoWNpNd;
      string tkJHtyVCzd;
      string NObLrNhJtF;
      string GuhjqjCeLo;
      string NUoDgHqQCb;
      string HIbQldrIoa;
      string nEwHWyCYPJ;
      string uqqJQsYXek;
      string WRHRyyTQyN;
      if(dPkOMyVZsc == sAXwZdLauA){rtojAJYgfh = true;}
      else if(sAXwZdLauA == dPkOMyVZsc){NRoHUWsXfu = true;}
      if(ZtDmexQGAB == rTThoWNpNd){ERArfPQRAs = true;}
      else if(rTThoWNpNd == ZtDmexQGAB){xjLfXcDwPa = true;}
      if(uSmdtJVBOw == tkJHtyVCzd){ETcEEWxdJY = true;}
      else if(tkJHtyVCzd == uSmdtJVBOw){yVFgtuicxA = true;}
      if(gJeJugchDo == NObLrNhJtF){elaCRBCGIH = true;}
      else if(NObLrNhJtF == gJeJugchDo){somMlnskHT = true;}
      if(uVBdqItPut == GuhjqjCeLo){TqrwfEQOlh = true;}
      else if(GuhjqjCeLo == uVBdqItPut){ixoywAGuGR = true;}
      if(MOmBZKcGUD == NUoDgHqQCb){gCQFIYQjfd = true;}
      else if(NUoDgHqQCb == MOmBZKcGUD){UXVSOrMIMY = true;}
      if(cTKxwQOtry == HIbQldrIoa){LuXGDSqyZe = true;}
      else if(HIbQldrIoa == cTKxwQOtry){nPZeBHwysj = true;}
      if(UiDLFZRJll == nEwHWyCYPJ){NJIsYNagYz = true;}
      if(OGGTiRWdjj == uqqJQsYXek){FhrbqcUVss = true;}
      if(DVMALbLDga == WRHRyyTQyN){jRaeuYTksM = true;}
      while(nEwHWyCYPJ == UiDLFZRJll){jSnuqAfGkt = true;}
      while(uqqJQsYXek == uqqJQsYXek){onWeeVTUyt = true;}
      while(WRHRyyTQyN == WRHRyyTQyN){akXhfSXKxn = true;}
      if(rtojAJYgfh == true){rtojAJYgfh = false;}
      if(ERArfPQRAs == true){ERArfPQRAs = false;}
      if(ETcEEWxdJY == true){ETcEEWxdJY = false;}
      if(elaCRBCGIH == true){elaCRBCGIH = false;}
      if(TqrwfEQOlh == true){TqrwfEQOlh = false;}
      if(gCQFIYQjfd == true){gCQFIYQjfd = false;}
      if(LuXGDSqyZe == true){LuXGDSqyZe = false;}
      if(NJIsYNagYz == true){NJIsYNagYz = false;}
      if(FhrbqcUVss == true){FhrbqcUVss = false;}
      if(jRaeuYTksM == true){jRaeuYTksM = false;}
      if(NRoHUWsXfu == true){NRoHUWsXfu = false;}
      if(xjLfXcDwPa == true){xjLfXcDwPa = false;}
      if(yVFgtuicxA == true){yVFgtuicxA = false;}
      if(somMlnskHT == true){somMlnskHT = false;}
      if(ixoywAGuGR == true){ixoywAGuGR = false;}
      if(UXVSOrMIMY == true){UXVSOrMIMY = false;}
      if(nPZeBHwysj == true){nPZeBHwysj = false;}
      if(jSnuqAfGkt == true){jSnuqAfGkt = false;}
      if(onWeeVTUyt == true){onWeeVTUyt = false;}
      if(akXhfSXKxn == true){akXhfSXKxn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUEZWUGLLF
{ 
  void euMVODQXcb()
  { 
      bool wCiXKiIOBw = false;
      bool LLrtRDFrQS = false;
      bool mxAHCQzTPd = false;
      bool imYPcyopsA = false;
      bool PqQRERwqJk = false;
      bool SoAlCzCaUt = false;
      bool jnyXMYmbQS = false;
      bool NOyQCufhCk = false;
      bool TIKeKtmlMd = false;
      bool uOVzQasrFf = false;
      bool dTZpWEqjjH = false;
      bool SUXiZbdTNS = false;
      bool lAOlXzszzb = false;
      bool CncWGAhUHG = false;
      bool CDCFKaplYn = false;
      bool xYelsdEnSX = false;
      bool KqjHFeqAbZ = false;
      bool tILGPiyJaw = false;
      bool IHZLdcIpcc = false;
      bool utCjuLTtzf = false;
      string SHSaTVBZMT;
      string bmsYqTdHxY;
      string pnymBlFBAV;
      string qkrEgHolkW;
      string KTcbAhDfpR;
      string zKpTpdIeYg;
      string QAYpbpunrj;
      string drWZNWLWmT;
      string hZKhWgtXOC;
      string yKMDGJtlzJ;
      string mPmFmHmQFS;
      string SlrFzqopTu;
      string uWZolTeSTE;
      string bYWcgSlFuP;
      string sdSuiLRGEP;
      string TESENPoyTT;
      string bUwBpsPOXf;
      string EjuDCREdFZ;
      string BXOEjXGSOQ;
      string cnkanYhQEp;
      if(SHSaTVBZMT == mPmFmHmQFS){wCiXKiIOBw = true;}
      else if(mPmFmHmQFS == SHSaTVBZMT){dTZpWEqjjH = true;}
      if(bmsYqTdHxY == SlrFzqopTu){LLrtRDFrQS = true;}
      else if(SlrFzqopTu == bmsYqTdHxY){SUXiZbdTNS = true;}
      if(pnymBlFBAV == uWZolTeSTE){mxAHCQzTPd = true;}
      else if(uWZolTeSTE == pnymBlFBAV){lAOlXzszzb = true;}
      if(qkrEgHolkW == bYWcgSlFuP){imYPcyopsA = true;}
      else if(bYWcgSlFuP == qkrEgHolkW){CncWGAhUHG = true;}
      if(KTcbAhDfpR == sdSuiLRGEP){PqQRERwqJk = true;}
      else if(sdSuiLRGEP == KTcbAhDfpR){CDCFKaplYn = true;}
      if(zKpTpdIeYg == TESENPoyTT){SoAlCzCaUt = true;}
      else if(TESENPoyTT == zKpTpdIeYg){xYelsdEnSX = true;}
      if(QAYpbpunrj == bUwBpsPOXf){jnyXMYmbQS = true;}
      else if(bUwBpsPOXf == QAYpbpunrj){KqjHFeqAbZ = true;}
      if(drWZNWLWmT == EjuDCREdFZ){NOyQCufhCk = true;}
      if(hZKhWgtXOC == BXOEjXGSOQ){TIKeKtmlMd = true;}
      if(yKMDGJtlzJ == cnkanYhQEp){uOVzQasrFf = true;}
      while(EjuDCREdFZ == drWZNWLWmT){tILGPiyJaw = true;}
      while(BXOEjXGSOQ == BXOEjXGSOQ){IHZLdcIpcc = true;}
      while(cnkanYhQEp == cnkanYhQEp){utCjuLTtzf = true;}
      if(wCiXKiIOBw == true){wCiXKiIOBw = false;}
      if(LLrtRDFrQS == true){LLrtRDFrQS = false;}
      if(mxAHCQzTPd == true){mxAHCQzTPd = false;}
      if(imYPcyopsA == true){imYPcyopsA = false;}
      if(PqQRERwqJk == true){PqQRERwqJk = false;}
      if(SoAlCzCaUt == true){SoAlCzCaUt = false;}
      if(jnyXMYmbQS == true){jnyXMYmbQS = false;}
      if(NOyQCufhCk == true){NOyQCufhCk = false;}
      if(TIKeKtmlMd == true){TIKeKtmlMd = false;}
      if(uOVzQasrFf == true){uOVzQasrFf = false;}
      if(dTZpWEqjjH == true){dTZpWEqjjH = false;}
      if(SUXiZbdTNS == true){SUXiZbdTNS = false;}
      if(lAOlXzszzb == true){lAOlXzszzb = false;}
      if(CncWGAhUHG == true){CncWGAhUHG = false;}
      if(CDCFKaplYn == true){CDCFKaplYn = false;}
      if(xYelsdEnSX == true){xYelsdEnSX = false;}
      if(KqjHFeqAbZ == true){KqjHFeqAbZ = false;}
      if(tILGPiyJaw == true){tILGPiyJaw = false;}
      if(IHZLdcIpcc == true){IHZLdcIpcc = false;}
      if(utCjuLTtzf == true){utCjuLTtzf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGRHJYHIOY
{ 
  void bJOafYnuoB()
  { 
      bool DdNsiYKzzZ = false;
      bool cPiutzznmm = false;
      bool zRlpyxoBzO = false;
      bool MrWdrFMtPU = false;
      bool tbssjpKRDm = false;
      bool eVFWZlqXuk = false;
      bool jJzjNksECo = false;
      bool lFYSrWYsFI = false;
      bool mWyMjplzEG = false;
      bool NoydjkbIey = false;
      bool wFONAZwmeC = false;
      bool NyRmyMLmAX = false;
      bool ztzwawGthH = false;
      bool uPNHLgIjLK = false;
      bool syTCrPXLfX = false;
      bool YoHHyCGSlE = false;
      bool TCFXHxjKbQ = false;
      bool EbapdBZxDK = false;
      bool XuOKiFIGIJ = false;
      bool aoxHpqrwut = false;
      string AnoCHBmFOJ;
      string ZUVXSsVmLq;
      string pMzhSPIbCk;
      string GsfXcyPgwp;
      string qnOIyPekVb;
      string GPhCLmnHiq;
      string sKCcCfoxtU;
      string copVAByqiD;
      string jWFadqKcMo;
      string JIxEwfkkFR;
      string ahqByRYMCJ;
      string owXfGWFayL;
      string ULjEKTqkYU;
      string PNlQbCfDbM;
      string RyaDANkQxZ;
      string ZKlsxOxlqd;
      string ZmmgsaJGDD;
      string qBzlsWkgDw;
      string ianztFbrTN;
      string FsMxldKsKY;
      if(AnoCHBmFOJ == ahqByRYMCJ){DdNsiYKzzZ = true;}
      else if(ahqByRYMCJ == AnoCHBmFOJ){wFONAZwmeC = true;}
      if(ZUVXSsVmLq == owXfGWFayL){cPiutzznmm = true;}
      else if(owXfGWFayL == ZUVXSsVmLq){NyRmyMLmAX = true;}
      if(pMzhSPIbCk == ULjEKTqkYU){zRlpyxoBzO = true;}
      else if(ULjEKTqkYU == pMzhSPIbCk){ztzwawGthH = true;}
      if(GsfXcyPgwp == PNlQbCfDbM){MrWdrFMtPU = true;}
      else if(PNlQbCfDbM == GsfXcyPgwp){uPNHLgIjLK = true;}
      if(qnOIyPekVb == RyaDANkQxZ){tbssjpKRDm = true;}
      else if(RyaDANkQxZ == qnOIyPekVb){syTCrPXLfX = true;}
      if(GPhCLmnHiq == ZKlsxOxlqd){eVFWZlqXuk = true;}
      else if(ZKlsxOxlqd == GPhCLmnHiq){YoHHyCGSlE = true;}
      if(sKCcCfoxtU == ZmmgsaJGDD){jJzjNksECo = true;}
      else if(ZmmgsaJGDD == sKCcCfoxtU){TCFXHxjKbQ = true;}
      if(copVAByqiD == qBzlsWkgDw){lFYSrWYsFI = true;}
      if(jWFadqKcMo == ianztFbrTN){mWyMjplzEG = true;}
      if(JIxEwfkkFR == FsMxldKsKY){NoydjkbIey = true;}
      while(qBzlsWkgDw == copVAByqiD){EbapdBZxDK = true;}
      while(ianztFbrTN == ianztFbrTN){XuOKiFIGIJ = true;}
      while(FsMxldKsKY == FsMxldKsKY){aoxHpqrwut = true;}
      if(DdNsiYKzzZ == true){DdNsiYKzzZ = false;}
      if(cPiutzznmm == true){cPiutzznmm = false;}
      if(zRlpyxoBzO == true){zRlpyxoBzO = false;}
      if(MrWdrFMtPU == true){MrWdrFMtPU = false;}
      if(tbssjpKRDm == true){tbssjpKRDm = false;}
      if(eVFWZlqXuk == true){eVFWZlqXuk = false;}
      if(jJzjNksECo == true){jJzjNksECo = false;}
      if(lFYSrWYsFI == true){lFYSrWYsFI = false;}
      if(mWyMjplzEG == true){mWyMjplzEG = false;}
      if(NoydjkbIey == true){NoydjkbIey = false;}
      if(wFONAZwmeC == true){wFONAZwmeC = false;}
      if(NyRmyMLmAX == true){NyRmyMLmAX = false;}
      if(ztzwawGthH == true){ztzwawGthH = false;}
      if(uPNHLgIjLK == true){uPNHLgIjLK = false;}
      if(syTCrPXLfX == true){syTCrPXLfX = false;}
      if(YoHHyCGSlE == true){YoHHyCGSlE = false;}
      if(TCFXHxjKbQ == true){TCFXHxjKbQ = false;}
      if(EbapdBZxDK == true){EbapdBZxDK = false;}
      if(XuOKiFIGIJ == true){XuOKiFIGIJ = false;}
      if(aoxHpqrwut == true){aoxHpqrwut = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWMGRPTYTT
{ 
  void ehbfIodfhQ()
  { 
      bool YCnJVRthQy = false;
      bool bDTixnInGi = false;
      bool eAuJYMFdKn = false;
      bool fQCFSFRcLL = false;
      bool GQRdFRSeCq = false;
      bool iOHefYGekI = false;
      bool MPWbRKANPr = false;
      bool WfbtbOhREG = false;
      bool sZbTFQJWYt = false;
      bool ylqDyqsoLt = false;
      bool REOJTDmMCR = false;
      bool pnadPmnDWB = false;
      bool BcoVsknYwk = false;
      bool VsGJooKRzB = false;
      bool dwUHEJKNmL = false;
      bool CoRKrnPsPi = false;
      bool POQQwxhQoZ = false;
      bool bWDUWEIgRj = false;
      bool ZakjifauRB = false;
      bool YQBQlOfELH = false;
      string nOXhxdmwHi;
      string VjgwGcGeTb;
      string UaDrgluOUi;
      string qQIFCimKzZ;
      string RkNHtKLiyb;
      string bRSJtNLfAK;
      string hXbXqEaatX;
      string ouftJiMwyW;
      string ZLPrGYxyKo;
      string XHJoqtIoPo;
      string ijoamflYAL;
      string APgdjVIjQS;
      string HcQEAhkqCP;
      string ZWfJmoWoFa;
      string lYyznIZeEU;
      string kYYxgGTjaF;
      string tuVjkciXpt;
      string zSepfidQQr;
      string HGlhdByibg;
      string VlNAfqCNOK;
      if(nOXhxdmwHi == ijoamflYAL){YCnJVRthQy = true;}
      else if(ijoamflYAL == nOXhxdmwHi){REOJTDmMCR = true;}
      if(VjgwGcGeTb == APgdjVIjQS){bDTixnInGi = true;}
      else if(APgdjVIjQS == VjgwGcGeTb){pnadPmnDWB = true;}
      if(UaDrgluOUi == HcQEAhkqCP){eAuJYMFdKn = true;}
      else if(HcQEAhkqCP == UaDrgluOUi){BcoVsknYwk = true;}
      if(qQIFCimKzZ == ZWfJmoWoFa){fQCFSFRcLL = true;}
      else if(ZWfJmoWoFa == qQIFCimKzZ){VsGJooKRzB = true;}
      if(RkNHtKLiyb == lYyznIZeEU){GQRdFRSeCq = true;}
      else if(lYyznIZeEU == RkNHtKLiyb){dwUHEJKNmL = true;}
      if(bRSJtNLfAK == kYYxgGTjaF){iOHefYGekI = true;}
      else if(kYYxgGTjaF == bRSJtNLfAK){CoRKrnPsPi = true;}
      if(hXbXqEaatX == tuVjkciXpt){MPWbRKANPr = true;}
      else if(tuVjkciXpt == hXbXqEaatX){POQQwxhQoZ = true;}
      if(ouftJiMwyW == zSepfidQQr){WfbtbOhREG = true;}
      if(ZLPrGYxyKo == HGlhdByibg){sZbTFQJWYt = true;}
      if(XHJoqtIoPo == VlNAfqCNOK){ylqDyqsoLt = true;}
      while(zSepfidQQr == ouftJiMwyW){bWDUWEIgRj = true;}
      while(HGlhdByibg == HGlhdByibg){ZakjifauRB = true;}
      while(VlNAfqCNOK == VlNAfqCNOK){YQBQlOfELH = true;}
      if(YCnJVRthQy == true){YCnJVRthQy = false;}
      if(bDTixnInGi == true){bDTixnInGi = false;}
      if(eAuJYMFdKn == true){eAuJYMFdKn = false;}
      if(fQCFSFRcLL == true){fQCFSFRcLL = false;}
      if(GQRdFRSeCq == true){GQRdFRSeCq = false;}
      if(iOHefYGekI == true){iOHefYGekI = false;}
      if(MPWbRKANPr == true){MPWbRKANPr = false;}
      if(WfbtbOhREG == true){WfbtbOhREG = false;}
      if(sZbTFQJWYt == true){sZbTFQJWYt = false;}
      if(ylqDyqsoLt == true){ylqDyqsoLt = false;}
      if(REOJTDmMCR == true){REOJTDmMCR = false;}
      if(pnadPmnDWB == true){pnadPmnDWB = false;}
      if(BcoVsknYwk == true){BcoVsknYwk = false;}
      if(VsGJooKRzB == true){VsGJooKRzB = false;}
      if(dwUHEJKNmL == true){dwUHEJKNmL = false;}
      if(CoRKrnPsPi == true){CoRKrnPsPi = false;}
      if(POQQwxhQoZ == true){POQQwxhQoZ = false;}
      if(bWDUWEIgRj == true){bWDUWEIgRj = false;}
      if(ZakjifauRB == true){ZakjifauRB = false;}
      if(YQBQlOfELH == true){YQBQlOfELH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULYJHAKTAJ
{ 
  void CmCJLgJihZ()
  { 
      bool MOnJpVbsnL = false;
      bool LXNbgQzrFj = false;
      bool DVUSPrPcFm = false;
      bool kGBhcZTTZE = false;
      bool eMWKxaeeTJ = false;
      bool HOJrYpsVtx = false;
      bool GynAZEVezH = false;
      bool xfRAEqzKUn = false;
      bool MkJufVxJJl = false;
      bool gyYbyfXVjs = false;
      bool FAeMMaxImg = false;
      bool piBFkUorTD = false;
      bool HMUMZyGoBY = false;
      bool ScZbiLFxiE = false;
      bool YnVbuyxTqd = false;
      bool qeBgksfSlN = false;
      bool UHGONNIYWY = false;
      bool OqJOeSprQb = false;
      bool BmxXgnaspo = false;
      bool fmLVjQgGNh = false;
      string ABTLwbsXlk;
      string AWeeFswxmN;
      string aYSREdkadF;
      string nfHEECZoGT;
      string FDlKfObxCl;
      string FWRJdbhCHR;
      string pStfwUPZaC;
      string TGqTIXlHko;
      string CnXqzQNxac;
      string TXhncmJGNL;
      string zBWzSyfyBG;
      string paQRPCtCge;
      string HRzyiuYCpU;
      string OfsZpBRXXA;
      string kOwUlsGPYa;
      string sGZiDgCYQW;
      string ZdHgqJgqbO;
      string kWdftrVeLo;
      string oIdPaHGKVI;
      string yrGBaGGOcc;
      if(ABTLwbsXlk == zBWzSyfyBG){MOnJpVbsnL = true;}
      else if(zBWzSyfyBG == ABTLwbsXlk){FAeMMaxImg = true;}
      if(AWeeFswxmN == paQRPCtCge){LXNbgQzrFj = true;}
      else if(paQRPCtCge == AWeeFswxmN){piBFkUorTD = true;}
      if(aYSREdkadF == HRzyiuYCpU){DVUSPrPcFm = true;}
      else if(HRzyiuYCpU == aYSREdkadF){HMUMZyGoBY = true;}
      if(nfHEECZoGT == OfsZpBRXXA){kGBhcZTTZE = true;}
      else if(OfsZpBRXXA == nfHEECZoGT){ScZbiLFxiE = true;}
      if(FDlKfObxCl == kOwUlsGPYa){eMWKxaeeTJ = true;}
      else if(kOwUlsGPYa == FDlKfObxCl){YnVbuyxTqd = true;}
      if(FWRJdbhCHR == sGZiDgCYQW){HOJrYpsVtx = true;}
      else if(sGZiDgCYQW == FWRJdbhCHR){qeBgksfSlN = true;}
      if(pStfwUPZaC == ZdHgqJgqbO){GynAZEVezH = true;}
      else if(ZdHgqJgqbO == pStfwUPZaC){UHGONNIYWY = true;}
      if(TGqTIXlHko == kWdftrVeLo){xfRAEqzKUn = true;}
      if(CnXqzQNxac == oIdPaHGKVI){MkJufVxJJl = true;}
      if(TXhncmJGNL == yrGBaGGOcc){gyYbyfXVjs = true;}
      while(kWdftrVeLo == TGqTIXlHko){OqJOeSprQb = true;}
      while(oIdPaHGKVI == oIdPaHGKVI){BmxXgnaspo = true;}
      while(yrGBaGGOcc == yrGBaGGOcc){fmLVjQgGNh = true;}
      if(MOnJpVbsnL == true){MOnJpVbsnL = false;}
      if(LXNbgQzrFj == true){LXNbgQzrFj = false;}
      if(DVUSPrPcFm == true){DVUSPrPcFm = false;}
      if(kGBhcZTTZE == true){kGBhcZTTZE = false;}
      if(eMWKxaeeTJ == true){eMWKxaeeTJ = false;}
      if(HOJrYpsVtx == true){HOJrYpsVtx = false;}
      if(GynAZEVezH == true){GynAZEVezH = false;}
      if(xfRAEqzKUn == true){xfRAEqzKUn = false;}
      if(MkJufVxJJl == true){MkJufVxJJl = false;}
      if(gyYbyfXVjs == true){gyYbyfXVjs = false;}
      if(FAeMMaxImg == true){FAeMMaxImg = false;}
      if(piBFkUorTD == true){piBFkUorTD = false;}
      if(HMUMZyGoBY == true){HMUMZyGoBY = false;}
      if(ScZbiLFxiE == true){ScZbiLFxiE = false;}
      if(YnVbuyxTqd == true){YnVbuyxTqd = false;}
      if(qeBgksfSlN == true){qeBgksfSlN = false;}
      if(UHGONNIYWY == true){UHGONNIYWY = false;}
      if(OqJOeSprQb == true){OqJOeSprQb = false;}
      if(BmxXgnaspo == true){BmxXgnaspo = false;}
      if(fmLVjQgGNh == true){fmLVjQgGNh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMXNJOYLET
{ 
  void GQSTAFBmIc()
  { 
      bool lRfcaPxnsa = false;
      bool qygLzKJuyu = false;
      bool ZumlrbEnpl = false;
      bool jUMGIdWSBB = false;
      bool JeaIYUiqkM = false;
      bool tgGSopetky = false;
      bool KIyHpWlZCV = false;
      bool mqtxkuUdMX = false;
      bool sMDdqDNsRS = false;
      bool ycgCpBgSSC = false;
      bool hIoPYDmJhs = false;
      bool UAgNFyFUQl = false;
      bool JsHjWKJqHj = false;
      bool OCLKojXmFm = false;
      bool PDLXxywTwr = false;
      bool uMBfsoAErO = false;
      bool twCxeSoWXU = false;
      bool ZRPdWFhilY = false;
      bool NotOnCAeRA = false;
      bool jStprTBNse = false;
      string ugfHoGLYZc;
      string yWdRxTzuSq;
      string zIYLcWriIn;
      string aOClMdBwNr;
      string QslklhKoWw;
      string DYtdmmHTeR;
      string NcQkBiUqFS;
      string RDgZaGWnZu;
      string MCMLkBUYyZ;
      string VhRudmbBjC;
      string NSiDezqTDg;
      string PTsjFLQFzA;
      string Ourfxjklum;
      string dVDWhsSIfl;
      string JAVRJCnhoS;
      string WWBjnRZDGu;
      string OFXPCtPVCL;
      string rHZNpNZaVu;
      string uDwcQHTTiP;
      string TPCkWEcFOP;
      if(ugfHoGLYZc == NSiDezqTDg){lRfcaPxnsa = true;}
      else if(NSiDezqTDg == ugfHoGLYZc){hIoPYDmJhs = true;}
      if(yWdRxTzuSq == PTsjFLQFzA){qygLzKJuyu = true;}
      else if(PTsjFLQFzA == yWdRxTzuSq){UAgNFyFUQl = true;}
      if(zIYLcWriIn == Ourfxjklum){ZumlrbEnpl = true;}
      else if(Ourfxjklum == zIYLcWriIn){JsHjWKJqHj = true;}
      if(aOClMdBwNr == dVDWhsSIfl){jUMGIdWSBB = true;}
      else if(dVDWhsSIfl == aOClMdBwNr){OCLKojXmFm = true;}
      if(QslklhKoWw == JAVRJCnhoS){JeaIYUiqkM = true;}
      else if(JAVRJCnhoS == QslklhKoWw){PDLXxywTwr = true;}
      if(DYtdmmHTeR == WWBjnRZDGu){tgGSopetky = true;}
      else if(WWBjnRZDGu == DYtdmmHTeR){uMBfsoAErO = true;}
      if(NcQkBiUqFS == OFXPCtPVCL){KIyHpWlZCV = true;}
      else if(OFXPCtPVCL == NcQkBiUqFS){twCxeSoWXU = true;}
      if(RDgZaGWnZu == rHZNpNZaVu){mqtxkuUdMX = true;}
      if(MCMLkBUYyZ == uDwcQHTTiP){sMDdqDNsRS = true;}
      if(VhRudmbBjC == TPCkWEcFOP){ycgCpBgSSC = true;}
      while(rHZNpNZaVu == RDgZaGWnZu){ZRPdWFhilY = true;}
      while(uDwcQHTTiP == uDwcQHTTiP){NotOnCAeRA = true;}
      while(TPCkWEcFOP == TPCkWEcFOP){jStprTBNse = true;}
      if(lRfcaPxnsa == true){lRfcaPxnsa = false;}
      if(qygLzKJuyu == true){qygLzKJuyu = false;}
      if(ZumlrbEnpl == true){ZumlrbEnpl = false;}
      if(jUMGIdWSBB == true){jUMGIdWSBB = false;}
      if(JeaIYUiqkM == true){JeaIYUiqkM = false;}
      if(tgGSopetky == true){tgGSopetky = false;}
      if(KIyHpWlZCV == true){KIyHpWlZCV = false;}
      if(mqtxkuUdMX == true){mqtxkuUdMX = false;}
      if(sMDdqDNsRS == true){sMDdqDNsRS = false;}
      if(ycgCpBgSSC == true){ycgCpBgSSC = false;}
      if(hIoPYDmJhs == true){hIoPYDmJhs = false;}
      if(UAgNFyFUQl == true){UAgNFyFUQl = false;}
      if(JsHjWKJqHj == true){JsHjWKJqHj = false;}
      if(OCLKojXmFm == true){OCLKojXmFm = false;}
      if(PDLXxywTwr == true){PDLXxywTwr = false;}
      if(uMBfsoAErO == true){uMBfsoAErO = false;}
      if(twCxeSoWXU == true){twCxeSoWXU = false;}
      if(ZRPdWFhilY == true){ZRPdWFhilY = false;}
      if(NotOnCAeRA == true){NotOnCAeRA = false;}
      if(jStprTBNse == true){jStprTBNse = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STTRQHKPCN
{ 
  void UnjsNXLzXn()
  { 
      bool YLLcuIFJtL = false;
      bool iGiaCDTiFw = false;
      bool IJWxeNUCRq = false;
      bool ucHFxepLgl = false;
      bool ODbcPeSHfF = false;
      bool FDgQDPnOyg = false;
      bool mCrCQFzddW = false;
      bool NIBShFgthA = false;
      bool uMWLkrwpBg = false;
      bool qaNzyLKYMK = false;
      bool endIqxBOix = false;
      bool htfxlZefQX = false;
      bool IIbwfltBTV = false;
      bool tIhXUGiNUn = false;
      bool phHEzwuPNY = false;
      bool geHnBVMgbE = false;
      bool CztMDZLIbe = false;
      bool pQKchaBXxi = false;
      bool qenuoOAtWz = false;
      bool tClPkqmtAZ = false;
      string AlThUVUSZz;
      string ByoiUzCpUs;
      string ONeQrHzcVG;
      string YUDpkZUqjB;
      string oBrlHuWxUm;
      string byUKnlGDpM;
      string VrxTagtzxt;
      string eLFTDNUsJx;
      string jCHieazsCz;
      string SQBWexEYLa;
      string AXzZHPrAGZ;
      string RNtrcTkNoz;
      string gBxybNKinG;
      string JwhhwMCgbO;
      string iylcgFWItL;
      string LpiLtyaAys;
      string FILzPUfLwQ;
      string QDkZQhPTRW;
      string qCoctTMVny;
      string kCihIZllML;
      if(AlThUVUSZz == AXzZHPrAGZ){YLLcuIFJtL = true;}
      else if(AXzZHPrAGZ == AlThUVUSZz){endIqxBOix = true;}
      if(ByoiUzCpUs == RNtrcTkNoz){iGiaCDTiFw = true;}
      else if(RNtrcTkNoz == ByoiUzCpUs){htfxlZefQX = true;}
      if(ONeQrHzcVG == gBxybNKinG){IJWxeNUCRq = true;}
      else if(gBxybNKinG == ONeQrHzcVG){IIbwfltBTV = true;}
      if(YUDpkZUqjB == JwhhwMCgbO){ucHFxepLgl = true;}
      else if(JwhhwMCgbO == YUDpkZUqjB){tIhXUGiNUn = true;}
      if(oBrlHuWxUm == iylcgFWItL){ODbcPeSHfF = true;}
      else if(iylcgFWItL == oBrlHuWxUm){phHEzwuPNY = true;}
      if(byUKnlGDpM == LpiLtyaAys){FDgQDPnOyg = true;}
      else if(LpiLtyaAys == byUKnlGDpM){geHnBVMgbE = true;}
      if(VrxTagtzxt == FILzPUfLwQ){mCrCQFzddW = true;}
      else if(FILzPUfLwQ == VrxTagtzxt){CztMDZLIbe = true;}
      if(eLFTDNUsJx == QDkZQhPTRW){NIBShFgthA = true;}
      if(jCHieazsCz == qCoctTMVny){uMWLkrwpBg = true;}
      if(SQBWexEYLa == kCihIZllML){qaNzyLKYMK = true;}
      while(QDkZQhPTRW == eLFTDNUsJx){pQKchaBXxi = true;}
      while(qCoctTMVny == qCoctTMVny){qenuoOAtWz = true;}
      while(kCihIZllML == kCihIZllML){tClPkqmtAZ = true;}
      if(YLLcuIFJtL == true){YLLcuIFJtL = false;}
      if(iGiaCDTiFw == true){iGiaCDTiFw = false;}
      if(IJWxeNUCRq == true){IJWxeNUCRq = false;}
      if(ucHFxepLgl == true){ucHFxepLgl = false;}
      if(ODbcPeSHfF == true){ODbcPeSHfF = false;}
      if(FDgQDPnOyg == true){FDgQDPnOyg = false;}
      if(mCrCQFzddW == true){mCrCQFzddW = false;}
      if(NIBShFgthA == true){NIBShFgthA = false;}
      if(uMWLkrwpBg == true){uMWLkrwpBg = false;}
      if(qaNzyLKYMK == true){qaNzyLKYMK = false;}
      if(endIqxBOix == true){endIqxBOix = false;}
      if(htfxlZefQX == true){htfxlZefQX = false;}
      if(IIbwfltBTV == true){IIbwfltBTV = false;}
      if(tIhXUGiNUn == true){tIhXUGiNUn = false;}
      if(phHEzwuPNY == true){phHEzwuPNY = false;}
      if(geHnBVMgbE == true){geHnBVMgbE = false;}
      if(CztMDZLIbe == true){CztMDZLIbe = false;}
      if(pQKchaBXxi == true){pQKchaBXxi = false;}
      if(qenuoOAtWz == true){qenuoOAtWz = false;}
      if(tClPkqmtAZ == true){tClPkqmtAZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOKEFQWCQV
{ 
  void jVqRiyARxT()
  { 
      bool lrYuiGopBJ = false;
      bool cgrlAgOUeZ = false;
      bool RTmckFgAeI = false;
      bool dtgcOTzkfi = false;
      bool qwrJOkRQtx = false;
      bool PCmUCSEuJc = false;
      bool ZnLsfizOXf = false;
      bool gcouhUadOz = false;
      bool nPGgraGMau = false;
      bool OEaCIDkyce = false;
      bool kCsNPlMqlg = false;
      bool qafJoJhdAE = false;
      bool bmmcRcCmle = false;
      bool jcBiOkWsQG = false;
      bool OOZtDnYQMz = false;
      bool VGyXDxOPum = false;
      bool jZEHxOYwuD = false;
      bool mnNtpMNsYd = false;
      bool EkZmJcdcfQ = false;
      bool WGxcWnJSwo = false;
      string nUHYgiSdlo;
      string ncxZONkTMb;
      string SRsZytJLyo;
      string dbpxmURVNl;
      string aQnLdbjzgT;
      string keXCZVbgZm;
      string YGewKLmAms;
      string wOFaACdhwW;
      string JKedEyEnXQ;
      string sjwaMTkqAR;
      string ojLmXVYxBW;
      string rtkCcObBqM;
      string HzbVALRdNg;
      string QmgdgZzqGi;
      string ZGlAYzzsyy;
      string qjznKpHomL;
      string EujTGFMGUC;
      string PkuIlAMaxA;
      string LXfOogmsSq;
      string RJDtddWRtT;
      if(nUHYgiSdlo == ojLmXVYxBW){lrYuiGopBJ = true;}
      else if(ojLmXVYxBW == nUHYgiSdlo){kCsNPlMqlg = true;}
      if(ncxZONkTMb == rtkCcObBqM){cgrlAgOUeZ = true;}
      else if(rtkCcObBqM == ncxZONkTMb){qafJoJhdAE = true;}
      if(SRsZytJLyo == HzbVALRdNg){RTmckFgAeI = true;}
      else if(HzbVALRdNg == SRsZytJLyo){bmmcRcCmle = true;}
      if(dbpxmURVNl == QmgdgZzqGi){dtgcOTzkfi = true;}
      else if(QmgdgZzqGi == dbpxmURVNl){jcBiOkWsQG = true;}
      if(aQnLdbjzgT == ZGlAYzzsyy){qwrJOkRQtx = true;}
      else if(ZGlAYzzsyy == aQnLdbjzgT){OOZtDnYQMz = true;}
      if(keXCZVbgZm == qjznKpHomL){PCmUCSEuJc = true;}
      else if(qjznKpHomL == keXCZVbgZm){VGyXDxOPum = true;}
      if(YGewKLmAms == EujTGFMGUC){ZnLsfizOXf = true;}
      else if(EujTGFMGUC == YGewKLmAms){jZEHxOYwuD = true;}
      if(wOFaACdhwW == PkuIlAMaxA){gcouhUadOz = true;}
      if(JKedEyEnXQ == LXfOogmsSq){nPGgraGMau = true;}
      if(sjwaMTkqAR == RJDtddWRtT){OEaCIDkyce = true;}
      while(PkuIlAMaxA == wOFaACdhwW){mnNtpMNsYd = true;}
      while(LXfOogmsSq == LXfOogmsSq){EkZmJcdcfQ = true;}
      while(RJDtddWRtT == RJDtddWRtT){WGxcWnJSwo = true;}
      if(lrYuiGopBJ == true){lrYuiGopBJ = false;}
      if(cgrlAgOUeZ == true){cgrlAgOUeZ = false;}
      if(RTmckFgAeI == true){RTmckFgAeI = false;}
      if(dtgcOTzkfi == true){dtgcOTzkfi = false;}
      if(qwrJOkRQtx == true){qwrJOkRQtx = false;}
      if(PCmUCSEuJc == true){PCmUCSEuJc = false;}
      if(ZnLsfizOXf == true){ZnLsfizOXf = false;}
      if(gcouhUadOz == true){gcouhUadOz = false;}
      if(nPGgraGMau == true){nPGgraGMau = false;}
      if(OEaCIDkyce == true){OEaCIDkyce = false;}
      if(kCsNPlMqlg == true){kCsNPlMqlg = false;}
      if(qafJoJhdAE == true){qafJoJhdAE = false;}
      if(bmmcRcCmle == true){bmmcRcCmle = false;}
      if(jcBiOkWsQG == true){jcBiOkWsQG = false;}
      if(OOZtDnYQMz == true){OOZtDnYQMz = false;}
      if(VGyXDxOPum == true){VGyXDxOPum = false;}
      if(jZEHxOYwuD == true){jZEHxOYwuD = false;}
      if(mnNtpMNsYd == true){mnNtpMNsYd = false;}
      if(EkZmJcdcfQ == true){EkZmJcdcfQ = false;}
      if(WGxcWnJSwo == true){WGxcWnJSwo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDDVEBYUUV
{ 
  void SHWeqmRFFQ()
  { 
      bool UwzsDGTfXK = false;
      bool dqXSrkIRNT = false;
      bool LGUHbLJHLA = false;
      bool XUSkDePnnf = false;
      bool sYzfDWxFwR = false;
      bool qstptNaqQr = false;
      bool wMUWmJYlPN = false;
      bool UUdgZmHnEE = false;
      bool NDKsJdacqo = false;
      bool DYWwifEbst = false;
      bool xKpixWPMPG = false;
      bool GmmLdsCaNJ = false;
      bool hwtaJuxhyt = false;
      bool ieuJHDNaum = false;
      bool OONkhPkLRo = false;
      bool dcOjLBQPZC = false;
      bool ZgNVWbrdEa = false;
      bool fbfatTiJrt = false;
      bool KlPIPGPKxF = false;
      bool lxBsNgAqNG = false;
      string eFnufWKNSU;
      string ehiQCkEeFY;
      string eBTBkiriBp;
      string eSSMPJteFd;
      string MgoHNFLeGr;
      string ffLlJclmKx;
      string daMbpMPWAs;
      string pZYaMyMMne;
      string XNcIJyGfCm;
      string WHUIAlTMQB;
      string pndMBGHkZL;
      string PYzeYQxDSr;
      string FiTNViFQaZ;
      string dzumoijPHD;
      string qVGqWyIoii;
      string nQtYuGUPqS;
      string ApJzgQcMpp;
      string fhwOBjbcqX;
      string aPgqlNEWqh;
      string OUYoDALHJF;
      if(eFnufWKNSU == pndMBGHkZL){UwzsDGTfXK = true;}
      else if(pndMBGHkZL == eFnufWKNSU){xKpixWPMPG = true;}
      if(ehiQCkEeFY == PYzeYQxDSr){dqXSrkIRNT = true;}
      else if(PYzeYQxDSr == ehiQCkEeFY){GmmLdsCaNJ = true;}
      if(eBTBkiriBp == FiTNViFQaZ){LGUHbLJHLA = true;}
      else if(FiTNViFQaZ == eBTBkiriBp){hwtaJuxhyt = true;}
      if(eSSMPJteFd == dzumoijPHD){XUSkDePnnf = true;}
      else if(dzumoijPHD == eSSMPJteFd){ieuJHDNaum = true;}
      if(MgoHNFLeGr == qVGqWyIoii){sYzfDWxFwR = true;}
      else if(qVGqWyIoii == MgoHNFLeGr){OONkhPkLRo = true;}
      if(ffLlJclmKx == nQtYuGUPqS){qstptNaqQr = true;}
      else if(nQtYuGUPqS == ffLlJclmKx){dcOjLBQPZC = true;}
      if(daMbpMPWAs == ApJzgQcMpp){wMUWmJYlPN = true;}
      else if(ApJzgQcMpp == daMbpMPWAs){ZgNVWbrdEa = true;}
      if(pZYaMyMMne == fhwOBjbcqX){UUdgZmHnEE = true;}
      if(XNcIJyGfCm == aPgqlNEWqh){NDKsJdacqo = true;}
      if(WHUIAlTMQB == OUYoDALHJF){DYWwifEbst = true;}
      while(fhwOBjbcqX == pZYaMyMMne){fbfatTiJrt = true;}
      while(aPgqlNEWqh == aPgqlNEWqh){KlPIPGPKxF = true;}
      while(OUYoDALHJF == OUYoDALHJF){lxBsNgAqNG = true;}
      if(UwzsDGTfXK == true){UwzsDGTfXK = false;}
      if(dqXSrkIRNT == true){dqXSrkIRNT = false;}
      if(LGUHbLJHLA == true){LGUHbLJHLA = false;}
      if(XUSkDePnnf == true){XUSkDePnnf = false;}
      if(sYzfDWxFwR == true){sYzfDWxFwR = false;}
      if(qstptNaqQr == true){qstptNaqQr = false;}
      if(wMUWmJYlPN == true){wMUWmJYlPN = false;}
      if(UUdgZmHnEE == true){UUdgZmHnEE = false;}
      if(NDKsJdacqo == true){NDKsJdacqo = false;}
      if(DYWwifEbst == true){DYWwifEbst = false;}
      if(xKpixWPMPG == true){xKpixWPMPG = false;}
      if(GmmLdsCaNJ == true){GmmLdsCaNJ = false;}
      if(hwtaJuxhyt == true){hwtaJuxhyt = false;}
      if(ieuJHDNaum == true){ieuJHDNaum = false;}
      if(OONkhPkLRo == true){OONkhPkLRo = false;}
      if(dcOjLBQPZC == true){dcOjLBQPZC = false;}
      if(ZgNVWbrdEa == true){ZgNVWbrdEa = false;}
      if(fbfatTiJrt == true){fbfatTiJrt = false;}
      if(KlPIPGPKxF == true){KlPIPGPKxF = false;}
      if(lxBsNgAqNG == true){lxBsNgAqNG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXZZBRZJEO
{ 
  void eZisLwbjZb()
  { 
      bool wKCbrGNbby = false;
      bool wigqCyIDuM = false;
      bool mHrhwgqEJO = false;
      bool FxpLMgtnVG = false;
      bool WyVaIinEMu = false;
      bool sJEVFoRUeL = false;
      bool OIRNrysVdU = false;
      bool DTgooolQYN = false;
      bool rmrOUwrUFX = false;
      bool OYJKqNfHiK = false;
      bool oRZqqZcPfQ = false;
      bool DBwRSaQCrw = false;
      bool FYQFFdKVxb = false;
      bool IdhNYaMBWu = false;
      bool TcnoUNcrqP = false;
      bool xdPlFPBTkM = false;
      bool OGRDHYThsr = false;
      bool NOewcbjbkr = false;
      bool BSdgdeNuII = false;
      bool YsPKgMLjgu = false;
      string LClPfDVnjj;
      string BuwDmBcyjB;
      string oQYYcCmdnU;
      string fwRsTcxNJV;
      string SKmrTdPgVR;
      string xVouuudNlc;
      string QqzPEEcCjK;
      string DOnOhdcfFz;
      string mFHWWJGVxY;
      string zjbgFbKXnO;
      string AMxLNhgaNR;
      string RxHloKicrt;
      string yGEKLTmHJF;
      string SFrpzZIwIo;
      string beIfGBbpqt;
      string shetQtHlAt;
      string uZRHyMFRmO;
      string CmTDRSyXEJ;
      string qxQOMkZxZE;
      string SVuOsCMAhs;
      if(LClPfDVnjj == AMxLNhgaNR){wKCbrGNbby = true;}
      else if(AMxLNhgaNR == LClPfDVnjj){oRZqqZcPfQ = true;}
      if(BuwDmBcyjB == RxHloKicrt){wigqCyIDuM = true;}
      else if(RxHloKicrt == BuwDmBcyjB){DBwRSaQCrw = true;}
      if(oQYYcCmdnU == yGEKLTmHJF){mHrhwgqEJO = true;}
      else if(yGEKLTmHJF == oQYYcCmdnU){FYQFFdKVxb = true;}
      if(fwRsTcxNJV == SFrpzZIwIo){FxpLMgtnVG = true;}
      else if(SFrpzZIwIo == fwRsTcxNJV){IdhNYaMBWu = true;}
      if(SKmrTdPgVR == beIfGBbpqt){WyVaIinEMu = true;}
      else if(beIfGBbpqt == SKmrTdPgVR){TcnoUNcrqP = true;}
      if(xVouuudNlc == shetQtHlAt){sJEVFoRUeL = true;}
      else if(shetQtHlAt == xVouuudNlc){xdPlFPBTkM = true;}
      if(QqzPEEcCjK == uZRHyMFRmO){OIRNrysVdU = true;}
      else if(uZRHyMFRmO == QqzPEEcCjK){OGRDHYThsr = true;}
      if(DOnOhdcfFz == CmTDRSyXEJ){DTgooolQYN = true;}
      if(mFHWWJGVxY == qxQOMkZxZE){rmrOUwrUFX = true;}
      if(zjbgFbKXnO == SVuOsCMAhs){OYJKqNfHiK = true;}
      while(CmTDRSyXEJ == DOnOhdcfFz){NOewcbjbkr = true;}
      while(qxQOMkZxZE == qxQOMkZxZE){BSdgdeNuII = true;}
      while(SVuOsCMAhs == SVuOsCMAhs){YsPKgMLjgu = true;}
      if(wKCbrGNbby == true){wKCbrGNbby = false;}
      if(wigqCyIDuM == true){wigqCyIDuM = false;}
      if(mHrhwgqEJO == true){mHrhwgqEJO = false;}
      if(FxpLMgtnVG == true){FxpLMgtnVG = false;}
      if(WyVaIinEMu == true){WyVaIinEMu = false;}
      if(sJEVFoRUeL == true){sJEVFoRUeL = false;}
      if(OIRNrysVdU == true){OIRNrysVdU = false;}
      if(DTgooolQYN == true){DTgooolQYN = false;}
      if(rmrOUwrUFX == true){rmrOUwrUFX = false;}
      if(OYJKqNfHiK == true){OYJKqNfHiK = false;}
      if(oRZqqZcPfQ == true){oRZqqZcPfQ = false;}
      if(DBwRSaQCrw == true){DBwRSaQCrw = false;}
      if(FYQFFdKVxb == true){FYQFFdKVxb = false;}
      if(IdhNYaMBWu == true){IdhNYaMBWu = false;}
      if(TcnoUNcrqP == true){TcnoUNcrqP = false;}
      if(xdPlFPBTkM == true){xdPlFPBTkM = false;}
      if(OGRDHYThsr == true){OGRDHYThsr = false;}
      if(NOewcbjbkr == true){NOewcbjbkr = false;}
      if(BSdgdeNuII == true){BSdgdeNuII = false;}
      if(YsPKgMLjgu == true){YsPKgMLjgu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTKUAFHQIO
{ 
  void uHqUBZwnNB()
  { 
      bool XUZJwspFZL = false;
      bool tAYWdchogP = false;
      bool ZfiXFJqdgT = false;
      bool scnLdrUkkg = false;
      bool JezUchsXiZ = false;
      bool AijGfqlBDm = false;
      bool CMXGRQLNsk = false;
      bool HwDAGtgNtX = false;
      bool PStHSJsgel = false;
      bool GSgydxHrDM = false;
      bool VfdxSEfjAk = false;
      bool KYHfWiRQmH = false;
      bool WdhHenPFVI = false;
      bool mnKhBjownO = false;
      bool dJgsbgLAau = false;
      bool epFuprxWSd = false;
      bool nZNqyVNYem = false;
      bool tUbXdMxofx = false;
      bool bOdZcwiPrI = false;
      bool mRdKZEuouG = false;
      string JfRtpMetNP;
      string HmfzJDoppI;
      string jxcmWCszAp;
      string WRluNprySb;
      string RYWjhGwKZD;
      string dqrCJLCeWn;
      string SftWsoAkkT;
      string LpWOqLZsEQ;
      string FiZxMeZikC;
      string mMaeIkdAps;
      string FLZFqmTdLx;
      string kIaGhjGxKN;
      string ORzifzPqFF;
      string gZCKLtITFZ;
      string KwWmQdkUxX;
      string egocdnLpYr;
      string WbXGPKGPum;
      string blqjCStLRB;
      string NtthZAkZgW;
      string hRuNChYQWG;
      if(JfRtpMetNP == FLZFqmTdLx){XUZJwspFZL = true;}
      else if(FLZFqmTdLx == JfRtpMetNP){VfdxSEfjAk = true;}
      if(HmfzJDoppI == kIaGhjGxKN){tAYWdchogP = true;}
      else if(kIaGhjGxKN == HmfzJDoppI){KYHfWiRQmH = true;}
      if(jxcmWCszAp == ORzifzPqFF){ZfiXFJqdgT = true;}
      else if(ORzifzPqFF == jxcmWCszAp){WdhHenPFVI = true;}
      if(WRluNprySb == gZCKLtITFZ){scnLdrUkkg = true;}
      else if(gZCKLtITFZ == WRluNprySb){mnKhBjownO = true;}
      if(RYWjhGwKZD == KwWmQdkUxX){JezUchsXiZ = true;}
      else if(KwWmQdkUxX == RYWjhGwKZD){dJgsbgLAau = true;}
      if(dqrCJLCeWn == egocdnLpYr){AijGfqlBDm = true;}
      else if(egocdnLpYr == dqrCJLCeWn){epFuprxWSd = true;}
      if(SftWsoAkkT == WbXGPKGPum){CMXGRQLNsk = true;}
      else if(WbXGPKGPum == SftWsoAkkT){nZNqyVNYem = true;}
      if(LpWOqLZsEQ == blqjCStLRB){HwDAGtgNtX = true;}
      if(FiZxMeZikC == NtthZAkZgW){PStHSJsgel = true;}
      if(mMaeIkdAps == hRuNChYQWG){GSgydxHrDM = true;}
      while(blqjCStLRB == LpWOqLZsEQ){tUbXdMxofx = true;}
      while(NtthZAkZgW == NtthZAkZgW){bOdZcwiPrI = true;}
      while(hRuNChYQWG == hRuNChYQWG){mRdKZEuouG = true;}
      if(XUZJwspFZL == true){XUZJwspFZL = false;}
      if(tAYWdchogP == true){tAYWdchogP = false;}
      if(ZfiXFJqdgT == true){ZfiXFJqdgT = false;}
      if(scnLdrUkkg == true){scnLdrUkkg = false;}
      if(JezUchsXiZ == true){JezUchsXiZ = false;}
      if(AijGfqlBDm == true){AijGfqlBDm = false;}
      if(CMXGRQLNsk == true){CMXGRQLNsk = false;}
      if(HwDAGtgNtX == true){HwDAGtgNtX = false;}
      if(PStHSJsgel == true){PStHSJsgel = false;}
      if(GSgydxHrDM == true){GSgydxHrDM = false;}
      if(VfdxSEfjAk == true){VfdxSEfjAk = false;}
      if(KYHfWiRQmH == true){KYHfWiRQmH = false;}
      if(WdhHenPFVI == true){WdhHenPFVI = false;}
      if(mnKhBjownO == true){mnKhBjownO = false;}
      if(dJgsbgLAau == true){dJgsbgLAau = false;}
      if(epFuprxWSd == true){epFuprxWSd = false;}
      if(nZNqyVNYem == true){nZNqyVNYem = false;}
      if(tUbXdMxofx == true){tUbXdMxofx = false;}
      if(bOdZcwiPrI == true){bOdZcwiPrI = false;}
      if(mRdKZEuouG == true){mRdKZEuouG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCXBOWXITN
{ 
  void ZdiTMiZCIg()
  { 
      bool EfikpZbnMT = false;
      bool tbThsgggYF = false;
      bool pWDabCQruK = false;
      bool iJtjOONMRF = false;
      bool cNbazByexk = false;
      bool OMpxmgbIIm = false;
      bool IisBjkgiSd = false;
      bool TUOTbctbaa = false;
      bool EluKuVSwxg = false;
      bool lFDewsUaqO = false;
      bool TOLSQtyWUK = false;
      bool mAghiWniFN = false;
      bool RklkrOQjWi = false;
      bool HTkMGoZbsB = false;
      bool XwbmtlXVuY = false;
      bool FkUcwicZaC = false;
      bool dNzlCSOTbs = false;
      bool xLpEpVIyqG = false;
      bool ptnxcVzIPW = false;
      bool MABpXKwojb = false;
      string cPDgNorDke;
      string zJzrfJlgWL;
      string OOmLaSxCzy;
      string CxPBkMNusX;
      string jbxdKDgbEI;
      string WHGMNOcrGt;
      string qpDlcCsyHT;
      string upmzbmQIAW;
      string lVyqbtpDmV;
      string jVnzftXLBI;
      string JiUjMfTHkZ;
      string yTqiIVqMJh;
      string LpKliZBnSh;
      string PEHrNCANdw;
      string aiRNWPeFpK;
      string CKCSwSYhBm;
      string deoDKsLyVF;
      string UciNGcXxOS;
      string twxHeECout;
      string cRMpRwsOCd;
      if(cPDgNorDke == JiUjMfTHkZ){EfikpZbnMT = true;}
      else if(JiUjMfTHkZ == cPDgNorDke){TOLSQtyWUK = true;}
      if(zJzrfJlgWL == yTqiIVqMJh){tbThsgggYF = true;}
      else if(yTqiIVqMJh == zJzrfJlgWL){mAghiWniFN = true;}
      if(OOmLaSxCzy == LpKliZBnSh){pWDabCQruK = true;}
      else if(LpKliZBnSh == OOmLaSxCzy){RklkrOQjWi = true;}
      if(CxPBkMNusX == PEHrNCANdw){iJtjOONMRF = true;}
      else if(PEHrNCANdw == CxPBkMNusX){HTkMGoZbsB = true;}
      if(jbxdKDgbEI == aiRNWPeFpK){cNbazByexk = true;}
      else if(aiRNWPeFpK == jbxdKDgbEI){XwbmtlXVuY = true;}
      if(WHGMNOcrGt == CKCSwSYhBm){OMpxmgbIIm = true;}
      else if(CKCSwSYhBm == WHGMNOcrGt){FkUcwicZaC = true;}
      if(qpDlcCsyHT == deoDKsLyVF){IisBjkgiSd = true;}
      else if(deoDKsLyVF == qpDlcCsyHT){dNzlCSOTbs = true;}
      if(upmzbmQIAW == UciNGcXxOS){TUOTbctbaa = true;}
      if(lVyqbtpDmV == twxHeECout){EluKuVSwxg = true;}
      if(jVnzftXLBI == cRMpRwsOCd){lFDewsUaqO = true;}
      while(UciNGcXxOS == upmzbmQIAW){xLpEpVIyqG = true;}
      while(twxHeECout == twxHeECout){ptnxcVzIPW = true;}
      while(cRMpRwsOCd == cRMpRwsOCd){MABpXKwojb = true;}
      if(EfikpZbnMT == true){EfikpZbnMT = false;}
      if(tbThsgggYF == true){tbThsgggYF = false;}
      if(pWDabCQruK == true){pWDabCQruK = false;}
      if(iJtjOONMRF == true){iJtjOONMRF = false;}
      if(cNbazByexk == true){cNbazByexk = false;}
      if(OMpxmgbIIm == true){OMpxmgbIIm = false;}
      if(IisBjkgiSd == true){IisBjkgiSd = false;}
      if(TUOTbctbaa == true){TUOTbctbaa = false;}
      if(EluKuVSwxg == true){EluKuVSwxg = false;}
      if(lFDewsUaqO == true){lFDewsUaqO = false;}
      if(TOLSQtyWUK == true){TOLSQtyWUK = false;}
      if(mAghiWniFN == true){mAghiWniFN = false;}
      if(RklkrOQjWi == true){RklkrOQjWi = false;}
      if(HTkMGoZbsB == true){HTkMGoZbsB = false;}
      if(XwbmtlXVuY == true){XwbmtlXVuY = false;}
      if(FkUcwicZaC == true){FkUcwicZaC = false;}
      if(dNzlCSOTbs == true){dNzlCSOTbs = false;}
      if(xLpEpVIyqG == true){xLpEpVIyqG = false;}
      if(ptnxcVzIPW == true){ptnxcVzIPW = false;}
      if(MABpXKwojb == true){MABpXKwojb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLNYMDVBVW
{ 
  void oTmVPktVEe()
  { 
      bool xSBcUXOuxi = false;
      bool iQmbjKNcxw = false;
      bool KNeHOguQZl = false;
      bool RGmxSYmjBs = false;
      bool jFJHujguLm = false;
      bool pYLWWjntNm = false;
      bool bxUKQbcoJK = false;
      bool XdbEMEEWMd = false;
      bool AzFlusuQZh = false;
      bool krWNRljypS = false;
      bool GqlAOMwGJR = false;
      bool fQhjmcriOX = false;
      bool gLPaZeHOmZ = false;
      bool TFfsXJMEWh = false;
      bool wnGHCUKlZn = false;
      bool tBiSktaLaj = false;
      bool FhTjxZjnLd = false;
      bool PmLfarFHXE = false;
      bool TUnyeSWNIc = false;
      bool hBdmcOTWKc = false;
      string UemNcTCtPT;
      string DgrBUZFcUc;
      string JjHFjTHecY;
      string hmymHFmdpT;
      string wadymUzhow;
      string BTsDDjXhcI;
      string LXQqlPiFtP;
      string lbmBgiFIRO;
      string TYogWNtuiW;
      string gFAgIYJmMX;
      string ltnZJZgrWU;
      string dPPNolhiUX;
      string UnVWhgaFrH;
      string YSuscYkPXx;
      string fBXOrRolrV;
      string pZSoCyXQrb;
      string zazOuLTVkP;
      string BSLXqTPHdP;
      string rnNWQyAGqd;
      string BTXuxEBITg;
      if(UemNcTCtPT == ltnZJZgrWU){xSBcUXOuxi = true;}
      else if(ltnZJZgrWU == UemNcTCtPT){GqlAOMwGJR = true;}
      if(DgrBUZFcUc == dPPNolhiUX){iQmbjKNcxw = true;}
      else if(dPPNolhiUX == DgrBUZFcUc){fQhjmcriOX = true;}
      if(JjHFjTHecY == UnVWhgaFrH){KNeHOguQZl = true;}
      else if(UnVWhgaFrH == JjHFjTHecY){gLPaZeHOmZ = true;}
      if(hmymHFmdpT == YSuscYkPXx){RGmxSYmjBs = true;}
      else if(YSuscYkPXx == hmymHFmdpT){TFfsXJMEWh = true;}
      if(wadymUzhow == fBXOrRolrV){jFJHujguLm = true;}
      else if(fBXOrRolrV == wadymUzhow){wnGHCUKlZn = true;}
      if(BTsDDjXhcI == pZSoCyXQrb){pYLWWjntNm = true;}
      else if(pZSoCyXQrb == BTsDDjXhcI){tBiSktaLaj = true;}
      if(LXQqlPiFtP == zazOuLTVkP){bxUKQbcoJK = true;}
      else if(zazOuLTVkP == LXQqlPiFtP){FhTjxZjnLd = true;}
      if(lbmBgiFIRO == BSLXqTPHdP){XdbEMEEWMd = true;}
      if(TYogWNtuiW == rnNWQyAGqd){AzFlusuQZh = true;}
      if(gFAgIYJmMX == BTXuxEBITg){krWNRljypS = true;}
      while(BSLXqTPHdP == lbmBgiFIRO){PmLfarFHXE = true;}
      while(rnNWQyAGqd == rnNWQyAGqd){TUnyeSWNIc = true;}
      while(BTXuxEBITg == BTXuxEBITg){hBdmcOTWKc = true;}
      if(xSBcUXOuxi == true){xSBcUXOuxi = false;}
      if(iQmbjKNcxw == true){iQmbjKNcxw = false;}
      if(KNeHOguQZl == true){KNeHOguQZl = false;}
      if(RGmxSYmjBs == true){RGmxSYmjBs = false;}
      if(jFJHujguLm == true){jFJHujguLm = false;}
      if(pYLWWjntNm == true){pYLWWjntNm = false;}
      if(bxUKQbcoJK == true){bxUKQbcoJK = false;}
      if(XdbEMEEWMd == true){XdbEMEEWMd = false;}
      if(AzFlusuQZh == true){AzFlusuQZh = false;}
      if(krWNRljypS == true){krWNRljypS = false;}
      if(GqlAOMwGJR == true){GqlAOMwGJR = false;}
      if(fQhjmcriOX == true){fQhjmcriOX = false;}
      if(gLPaZeHOmZ == true){gLPaZeHOmZ = false;}
      if(TFfsXJMEWh == true){TFfsXJMEWh = false;}
      if(wnGHCUKlZn == true){wnGHCUKlZn = false;}
      if(tBiSktaLaj == true){tBiSktaLaj = false;}
      if(FhTjxZjnLd == true){FhTjxZjnLd = false;}
      if(PmLfarFHXE == true){PmLfarFHXE = false;}
      if(TUnyeSWNIc == true){TUnyeSWNIc = false;}
      if(hBdmcOTWKc == true){hBdmcOTWKc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKDFSZWILD
{ 
  void YaUpOLleps()
  { 
      bool GVDIEGhSbZ = false;
      bool UIpXebwEQR = false;
      bool wkTZXNYnEl = false;
      bool eyCsXewASf = false;
      bool JyGTWcEEKb = false;
      bool twInQVCdkq = false;
      bool htOouWFwzz = false;
      bool fukkIxezDt = false;
      bool ITccrhpObB = false;
      bool bSPbxOjQYA = false;
      bool WIFKwyLWeT = false;
      bool qCZphNQlxM = false;
      bool fqUxWMfJms = false;
      bool MOaDWAOSgt = false;
      bool WTiHKZrYsi = false;
      bool xyTMTfmHmi = false;
      bool SCilGcbWSh = false;
      bool zyFCoMHMmx = false;
      bool TGPEuNuOiq = false;
      bool MHexaUjxAh = false;
      string HVQkydFWBR;
      string HoIHuOIsfu;
      string GtxjBqKjle;
      string QFMEtHeKmg;
      string KsleSWupwA;
      string ymNjZNYfiH;
      string TUjVBBcENn;
      string iyGzkMIRRe;
      string uTnlgcrbdf;
      string hyaeNoJPdQ;
      string sqcIQAgOzN;
      string FHOEMzgyoY;
      string JAZgFkWblu;
      string DrnAkDqeUg;
      string uccQaajWRN;
      string ILaFGsRwCf;
      string cFbDKNTNSJ;
      string IBcIcfXJGe;
      string BAJXmrRhtr;
      string ktcoDpAYGM;
      if(HVQkydFWBR == sqcIQAgOzN){GVDIEGhSbZ = true;}
      else if(sqcIQAgOzN == HVQkydFWBR){WIFKwyLWeT = true;}
      if(HoIHuOIsfu == FHOEMzgyoY){UIpXebwEQR = true;}
      else if(FHOEMzgyoY == HoIHuOIsfu){qCZphNQlxM = true;}
      if(GtxjBqKjle == JAZgFkWblu){wkTZXNYnEl = true;}
      else if(JAZgFkWblu == GtxjBqKjle){fqUxWMfJms = true;}
      if(QFMEtHeKmg == DrnAkDqeUg){eyCsXewASf = true;}
      else if(DrnAkDqeUg == QFMEtHeKmg){MOaDWAOSgt = true;}
      if(KsleSWupwA == uccQaajWRN){JyGTWcEEKb = true;}
      else if(uccQaajWRN == KsleSWupwA){WTiHKZrYsi = true;}
      if(ymNjZNYfiH == ILaFGsRwCf){twInQVCdkq = true;}
      else if(ILaFGsRwCf == ymNjZNYfiH){xyTMTfmHmi = true;}
      if(TUjVBBcENn == cFbDKNTNSJ){htOouWFwzz = true;}
      else if(cFbDKNTNSJ == TUjVBBcENn){SCilGcbWSh = true;}
      if(iyGzkMIRRe == IBcIcfXJGe){fukkIxezDt = true;}
      if(uTnlgcrbdf == BAJXmrRhtr){ITccrhpObB = true;}
      if(hyaeNoJPdQ == ktcoDpAYGM){bSPbxOjQYA = true;}
      while(IBcIcfXJGe == iyGzkMIRRe){zyFCoMHMmx = true;}
      while(BAJXmrRhtr == BAJXmrRhtr){TGPEuNuOiq = true;}
      while(ktcoDpAYGM == ktcoDpAYGM){MHexaUjxAh = true;}
      if(GVDIEGhSbZ == true){GVDIEGhSbZ = false;}
      if(UIpXebwEQR == true){UIpXebwEQR = false;}
      if(wkTZXNYnEl == true){wkTZXNYnEl = false;}
      if(eyCsXewASf == true){eyCsXewASf = false;}
      if(JyGTWcEEKb == true){JyGTWcEEKb = false;}
      if(twInQVCdkq == true){twInQVCdkq = false;}
      if(htOouWFwzz == true){htOouWFwzz = false;}
      if(fukkIxezDt == true){fukkIxezDt = false;}
      if(ITccrhpObB == true){ITccrhpObB = false;}
      if(bSPbxOjQYA == true){bSPbxOjQYA = false;}
      if(WIFKwyLWeT == true){WIFKwyLWeT = false;}
      if(qCZphNQlxM == true){qCZphNQlxM = false;}
      if(fqUxWMfJms == true){fqUxWMfJms = false;}
      if(MOaDWAOSgt == true){MOaDWAOSgt = false;}
      if(WTiHKZrYsi == true){WTiHKZrYsi = false;}
      if(xyTMTfmHmi == true){xyTMTfmHmi = false;}
      if(SCilGcbWSh == true){SCilGcbWSh = false;}
      if(zyFCoMHMmx == true){zyFCoMHMmx = false;}
      if(TGPEuNuOiq == true){TGPEuNuOiq = false;}
      if(MHexaUjxAh == true){MHexaUjxAh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QUYKQKBAJW
{ 
  void bexCpeNtYx()
  { 
      bool UjuwEYiYyf = false;
      bool TYRWLSUFRJ = false;
      bool YEZouJqKet = false;
      bool QlTqlAphjL = false;
      bool enegiTJkgR = false;
      bool WxBpCQKGAt = false;
      bool hYtDOhFakL = false;
      bool bmVFejZrGb = false;
      bool AFcMWSjcnU = false;
      bool pjgpdFsaSA = false;
      bool OhzVojbuLR = false;
      bool qRAYsbuggu = false;
      bool yblPVrGebY = false;
      bool qyZFNRGHXm = false;
      bool pnQVdXjHwC = false;
      bool JMtWClwjAx = false;
      bool cxTmasqtLb = false;
      bool VnJsEJKQlx = false;
      bool HyiZOdECDa = false;
      bool VWGZJsTdtk = false;
      string EBgXmmkUIj;
      string GJgRgsilTl;
      string wSbwcpTYhg;
      string zNFwlWKBJE;
      string URVzNCUtyn;
      string LrnaCkYjtw;
      string TMlaksEkfJ;
      string igcOQexciZ;
      string VYatUGYetA;
      string yZHMjIeuOU;
      string yjOnEePZJW;
      string nuBTaukrFd;
      string TZpeKIZPdH;
      string ACNNblKlop;
      string qzUWMDXmko;
      string XlokAYsidw;
      string FzuBWkhmro;
      string kyDPlUETRH;
      string jldojNMcNC;
      string saHskrDSza;
      if(EBgXmmkUIj == yjOnEePZJW){UjuwEYiYyf = true;}
      else if(yjOnEePZJW == EBgXmmkUIj){OhzVojbuLR = true;}
      if(GJgRgsilTl == nuBTaukrFd){TYRWLSUFRJ = true;}
      else if(nuBTaukrFd == GJgRgsilTl){qRAYsbuggu = true;}
      if(wSbwcpTYhg == TZpeKIZPdH){YEZouJqKet = true;}
      else if(TZpeKIZPdH == wSbwcpTYhg){yblPVrGebY = true;}
      if(zNFwlWKBJE == ACNNblKlop){QlTqlAphjL = true;}
      else if(ACNNblKlop == zNFwlWKBJE){qyZFNRGHXm = true;}
      if(URVzNCUtyn == qzUWMDXmko){enegiTJkgR = true;}
      else if(qzUWMDXmko == URVzNCUtyn){pnQVdXjHwC = true;}
      if(LrnaCkYjtw == XlokAYsidw){WxBpCQKGAt = true;}
      else if(XlokAYsidw == LrnaCkYjtw){JMtWClwjAx = true;}
      if(TMlaksEkfJ == FzuBWkhmro){hYtDOhFakL = true;}
      else if(FzuBWkhmro == TMlaksEkfJ){cxTmasqtLb = true;}
      if(igcOQexciZ == kyDPlUETRH){bmVFejZrGb = true;}
      if(VYatUGYetA == jldojNMcNC){AFcMWSjcnU = true;}
      if(yZHMjIeuOU == saHskrDSza){pjgpdFsaSA = true;}
      while(kyDPlUETRH == igcOQexciZ){VnJsEJKQlx = true;}
      while(jldojNMcNC == jldojNMcNC){HyiZOdECDa = true;}
      while(saHskrDSza == saHskrDSza){VWGZJsTdtk = true;}
      if(UjuwEYiYyf == true){UjuwEYiYyf = false;}
      if(TYRWLSUFRJ == true){TYRWLSUFRJ = false;}
      if(YEZouJqKet == true){YEZouJqKet = false;}
      if(QlTqlAphjL == true){QlTqlAphjL = false;}
      if(enegiTJkgR == true){enegiTJkgR = false;}
      if(WxBpCQKGAt == true){WxBpCQKGAt = false;}
      if(hYtDOhFakL == true){hYtDOhFakL = false;}
      if(bmVFejZrGb == true){bmVFejZrGb = false;}
      if(AFcMWSjcnU == true){AFcMWSjcnU = false;}
      if(pjgpdFsaSA == true){pjgpdFsaSA = false;}
      if(OhzVojbuLR == true){OhzVojbuLR = false;}
      if(qRAYsbuggu == true){qRAYsbuggu = false;}
      if(yblPVrGebY == true){yblPVrGebY = false;}
      if(qyZFNRGHXm == true){qyZFNRGHXm = false;}
      if(pnQVdXjHwC == true){pnQVdXjHwC = false;}
      if(JMtWClwjAx == true){JMtWClwjAx = false;}
      if(cxTmasqtLb == true){cxTmasqtLb = false;}
      if(VnJsEJKQlx == true){VnJsEJKQlx = false;}
      if(HyiZOdECDa == true){HyiZOdECDa = false;}
      if(VWGZJsTdtk == true){VWGZJsTdtk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IDTNAQYNXO
{ 
  void neRSKAztEe()
  { 
      bool cVzHEtBPEQ = false;
      bool KfJSyEMcXL = false;
      bool QORYlWoUPZ = false;
      bool sOUppiaJid = false;
      bool XOihCHzDsy = false;
      bool llSwVNEaVh = false;
      bool EfzeWuKTcP = false;
      bool cCssmBejVd = false;
      bool XlbRnHuYTb = false;
      bool eAmBZrPEKG = false;
      bool xeadUirYIU = false;
      bool hTEqJSEgqP = false;
      bool AlzBjcPrSu = false;
      bool laZOgrKxxE = false;
      bool OVPzsKuwqH = false;
      bool mhNuGKeZsr = false;
      bool TAFNiHtoJQ = false;
      bool HGjlAdVAHZ = false;
      bool gSALIDMdIW = false;
      bool NkEFkOPCQl = false;
      string MpeBzLwJGn;
      string HEwAPPQGSA;
      string mGbHBzqfGf;
      string jxxFyPxCDg;
      string saJgWPWzkN;
      string GebilGOXAz;
      string TQCZEJHpCA;
      string ROClHMxtjk;
      string crtrZEVOTq;
      string AZBDMcXicN;
      string IfwkwrbpaZ;
      string JUmPVbVJAA;
      string nrWKzrMyYe;
      string nNQWcwuJwh;
      string bfmshfllhk;
      string GOicYPIllE;
      string edQwkuDPlZ;
      string fMMSXIFcbS;
      string FaQnXZenyM;
      string mIWrCyOqIl;
      if(MpeBzLwJGn == IfwkwrbpaZ){cVzHEtBPEQ = true;}
      else if(IfwkwrbpaZ == MpeBzLwJGn){xeadUirYIU = true;}
      if(HEwAPPQGSA == JUmPVbVJAA){KfJSyEMcXL = true;}
      else if(JUmPVbVJAA == HEwAPPQGSA){hTEqJSEgqP = true;}
      if(mGbHBzqfGf == nrWKzrMyYe){QORYlWoUPZ = true;}
      else if(nrWKzrMyYe == mGbHBzqfGf){AlzBjcPrSu = true;}
      if(jxxFyPxCDg == nNQWcwuJwh){sOUppiaJid = true;}
      else if(nNQWcwuJwh == jxxFyPxCDg){laZOgrKxxE = true;}
      if(saJgWPWzkN == bfmshfllhk){XOihCHzDsy = true;}
      else if(bfmshfllhk == saJgWPWzkN){OVPzsKuwqH = true;}
      if(GebilGOXAz == GOicYPIllE){llSwVNEaVh = true;}
      else if(GOicYPIllE == GebilGOXAz){mhNuGKeZsr = true;}
      if(TQCZEJHpCA == edQwkuDPlZ){EfzeWuKTcP = true;}
      else if(edQwkuDPlZ == TQCZEJHpCA){TAFNiHtoJQ = true;}
      if(ROClHMxtjk == fMMSXIFcbS){cCssmBejVd = true;}
      if(crtrZEVOTq == FaQnXZenyM){XlbRnHuYTb = true;}
      if(AZBDMcXicN == mIWrCyOqIl){eAmBZrPEKG = true;}
      while(fMMSXIFcbS == ROClHMxtjk){HGjlAdVAHZ = true;}
      while(FaQnXZenyM == FaQnXZenyM){gSALIDMdIW = true;}
      while(mIWrCyOqIl == mIWrCyOqIl){NkEFkOPCQl = true;}
      if(cVzHEtBPEQ == true){cVzHEtBPEQ = false;}
      if(KfJSyEMcXL == true){KfJSyEMcXL = false;}
      if(QORYlWoUPZ == true){QORYlWoUPZ = false;}
      if(sOUppiaJid == true){sOUppiaJid = false;}
      if(XOihCHzDsy == true){XOihCHzDsy = false;}
      if(llSwVNEaVh == true){llSwVNEaVh = false;}
      if(EfzeWuKTcP == true){EfzeWuKTcP = false;}
      if(cCssmBejVd == true){cCssmBejVd = false;}
      if(XlbRnHuYTb == true){XlbRnHuYTb = false;}
      if(eAmBZrPEKG == true){eAmBZrPEKG = false;}
      if(xeadUirYIU == true){xeadUirYIU = false;}
      if(hTEqJSEgqP == true){hTEqJSEgqP = false;}
      if(AlzBjcPrSu == true){AlzBjcPrSu = false;}
      if(laZOgrKxxE == true){laZOgrKxxE = false;}
      if(OVPzsKuwqH == true){OVPzsKuwqH = false;}
      if(mhNuGKeZsr == true){mhNuGKeZsr = false;}
      if(TAFNiHtoJQ == true){TAFNiHtoJQ = false;}
      if(HGjlAdVAHZ == true){HGjlAdVAHZ = false;}
      if(gSALIDMdIW == true){gSALIDMdIW = false;}
      if(NkEFkOPCQl == true){NkEFkOPCQl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUPGIFDMHT
{ 
  void ZOPZAIsfJG()
  { 
      bool zoiAndUiPS = false;
      bool WCmwCmciaC = false;
      bool QAFdYiWpyo = false;
      bool KGULprIlMh = false;
      bool hRjKBIRrQH = false;
      bool KSHPBziFbE = false;
      bool GekaIQhaGJ = false;
      bool dqVrUyQtcP = false;
      bool ReZqdqzEJq = false;
      bool JDKIaCgICk = false;
      bool ZpkGcTxOuD = false;
      bool incLlbFsxQ = false;
      bool QdROAafNQR = false;
      bool RHrqpbsSOJ = false;
      bool tjIGIUZzWz = false;
      bool xmLkTuYVFB = false;
      bool njxdkawkUK = false;
      bool hlemWgVKGe = false;
      bool AfpRTduGWu = false;
      bool CWNMVKmeVg = false;
      string reHwGjJHBu;
      string dJhslXXzMF;
      string NWSXCTYQDy;
      string WckOADATHx;
      string XryzhuSXKL;
      string OecXGULjtl;
      string KsDCYBXSsh;
      string WErOgUYSpH;
      string BAFrjqAMIe;
      string rQZUldouag;
      string WAecoJmNpk;
      string ursmkJnLSh;
      string AKKNpFeWcC;
      string fdrJjBVbCZ;
      string EmVWjzXljb;
      string pdbsfLpQmj;
      string ePjnERziCj;
      string nLIscNomdp;
      string grmAMCBzdY;
      string LEoStnChSR;
      if(reHwGjJHBu == WAecoJmNpk){zoiAndUiPS = true;}
      else if(WAecoJmNpk == reHwGjJHBu){ZpkGcTxOuD = true;}
      if(dJhslXXzMF == ursmkJnLSh){WCmwCmciaC = true;}
      else if(ursmkJnLSh == dJhslXXzMF){incLlbFsxQ = true;}
      if(NWSXCTYQDy == AKKNpFeWcC){QAFdYiWpyo = true;}
      else if(AKKNpFeWcC == NWSXCTYQDy){QdROAafNQR = true;}
      if(WckOADATHx == fdrJjBVbCZ){KGULprIlMh = true;}
      else if(fdrJjBVbCZ == WckOADATHx){RHrqpbsSOJ = true;}
      if(XryzhuSXKL == EmVWjzXljb){hRjKBIRrQH = true;}
      else if(EmVWjzXljb == XryzhuSXKL){tjIGIUZzWz = true;}
      if(OecXGULjtl == pdbsfLpQmj){KSHPBziFbE = true;}
      else if(pdbsfLpQmj == OecXGULjtl){xmLkTuYVFB = true;}
      if(KsDCYBXSsh == ePjnERziCj){GekaIQhaGJ = true;}
      else if(ePjnERziCj == KsDCYBXSsh){njxdkawkUK = true;}
      if(WErOgUYSpH == nLIscNomdp){dqVrUyQtcP = true;}
      if(BAFrjqAMIe == grmAMCBzdY){ReZqdqzEJq = true;}
      if(rQZUldouag == LEoStnChSR){JDKIaCgICk = true;}
      while(nLIscNomdp == WErOgUYSpH){hlemWgVKGe = true;}
      while(grmAMCBzdY == grmAMCBzdY){AfpRTduGWu = true;}
      while(LEoStnChSR == LEoStnChSR){CWNMVKmeVg = true;}
      if(zoiAndUiPS == true){zoiAndUiPS = false;}
      if(WCmwCmciaC == true){WCmwCmciaC = false;}
      if(QAFdYiWpyo == true){QAFdYiWpyo = false;}
      if(KGULprIlMh == true){KGULprIlMh = false;}
      if(hRjKBIRrQH == true){hRjKBIRrQH = false;}
      if(KSHPBziFbE == true){KSHPBziFbE = false;}
      if(GekaIQhaGJ == true){GekaIQhaGJ = false;}
      if(dqVrUyQtcP == true){dqVrUyQtcP = false;}
      if(ReZqdqzEJq == true){ReZqdqzEJq = false;}
      if(JDKIaCgICk == true){JDKIaCgICk = false;}
      if(ZpkGcTxOuD == true){ZpkGcTxOuD = false;}
      if(incLlbFsxQ == true){incLlbFsxQ = false;}
      if(QdROAafNQR == true){QdROAafNQR = false;}
      if(RHrqpbsSOJ == true){RHrqpbsSOJ = false;}
      if(tjIGIUZzWz == true){tjIGIUZzWz = false;}
      if(xmLkTuYVFB == true){xmLkTuYVFB = false;}
      if(njxdkawkUK == true){njxdkawkUK = false;}
      if(hlemWgVKGe == true){hlemWgVKGe = false;}
      if(AfpRTduGWu == true){AfpRTduGWu = false;}
      if(CWNMVKmeVg == true){CWNMVKmeVg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWFKKMWNVC
{ 
  void hnoYwsONPG()
  { 
      bool XkubUFPHPo = false;
      bool RWjjgSOeyo = false;
      bool XuGPJXfSVR = false;
      bool gWkJKjYmrT = false;
      bool WcaTtJSXoH = false;
      bool hinKscdeSx = false;
      bool ZwlyItlaYx = false;
      bool tbleRuUmUz = false;
      bool EHcNixiZPh = false;
      bool GsUttZpcLA = false;
      bool WryrNGxIrx = false;
      bool IqKSrRSYOK = false;
      bool KLKqqAHrkq = false;
      bool EqaUcMJkzc = false;
      bool AZhRZOiBBb = false;
      bool GRNBoLgHBN = false;
      bool zEWAsQPppf = false;
      bool IhYlJjdsRb = false;
      bool QFpIjlcZeQ = false;
      bool eBjlcuDhYI = false;
      string fyYBieXaLQ;
      string HsEGhsSRnu;
      string FbxeCtQRKF;
      string iyWpdUImlx;
      string QnVEwRjoaK;
      string KsqUoEBtzo;
      string OGQFgIVObN;
      string kefqdRFrhj;
      string JapztpGBAZ;
      string TNmxiKXPWm;
      string wVNNZeNAqW;
      string yILPemQQLq;
      string CUNCtWrhIS;
      string toVunnNbZO;
      string bGKcaKBXSu;
      string tGEekaHKTC;
      string merXcJlQbp;
      string ZnpwOuJkai;
      string UUPMYmkqJM;
      string gCIWaxOlzR;
      if(fyYBieXaLQ == wVNNZeNAqW){XkubUFPHPo = true;}
      else if(wVNNZeNAqW == fyYBieXaLQ){WryrNGxIrx = true;}
      if(HsEGhsSRnu == yILPemQQLq){RWjjgSOeyo = true;}
      else if(yILPemQQLq == HsEGhsSRnu){IqKSrRSYOK = true;}
      if(FbxeCtQRKF == CUNCtWrhIS){XuGPJXfSVR = true;}
      else if(CUNCtWrhIS == FbxeCtQRKF){KLKqqAHrkq = true;}
      if(iyWpdUImlx == toVunnNbZO){gWkJKjYmrT = true;}
      else if(toVunnNbZO == iyWpdUImlx){EqaUcMJkzc = true;}
      if(QnVEwRjoaK == bGKcaKBXSu){WcaTtJSXoH = true;}
      else if(bGKcaKBXSu == QnVEwRjoaK){AZhRZOiBBb = true;}
      if(KsqUoEBtzo == tGEekaHKTC){hinKscdeSx = true;}
      else if(tGEekaHKTC == KsqUoEBtzo){GRNBoLgHBN = true;}
      if(OGQFgIVObN == merXcJlQbp){ZwlyItlaYx = true;}
      else if(merXcJlQbp == OGQFgIVObN){zEWAsQPppf = true;}
      if(kefqdRFrhj == ZnpwOuJkai){tbleRuUmUz = true;}
      if(JapztpGBAZ == UUPMYmkqJM){EHcNixiZPh = true;}
      if(TNmxiKXPWm == gCIWaxOlzR){GsUttZpcLA = true;}
      while(ZnpwOuJkai == kefqdRFrhj){IhYlJjdsRb = true;}
      while(UUPMYmkqJM == UUPMYmkqJM){QFpIjlcZeQ = true;}
      while(gCIWaxOlzR == gCIWaxOlzR){eBjlcuDhYI = true;}
      if(XkubUFPHPo == true){XkubUFPHPo = false;}
      if(RWjjgSOeyo == true){RWjjgSOeyo = false;}
      if(XuGPJXfSVR == true){XuGPJXfSVR = false;}
      if(gWkJKjYmrT == true){gWkJKjYmrT = false;}
      if(WcaTtJSXoH == true){WcaTtJSXoH = false;}
      if(hinKscdeSx == true){hinKscdeSx = false;}
      if(ZwlyItlaYx == true){ZwlyItlaYx = false;}
      if(tbleRuUmUz == true){tbleRuUmUz = false;}
      if(EHcNixiZPh == true){EHcNixiZPh = false;}
      if(GsUttZpcLA == true){GsUttZpcLA = false;}
      if(WryrNGxIrx == true){WryrNGxIrx = false;}
      if(IqKSrRSYOK == true){IqKSrRSYOK = false;}
      if(KLKqqAHrkq == true){KLKqqAHrkq = false;}
      if(EqaUcMJkzc == true){EqaUcMJkzc = false;}
      if(AZhRZOiBBb == true){AZhRZOiBBb = false;}
      if(GRNBoLgHBN == true){GRNBoLgHBN = false;}
      if(zEWAsQPppf == true){zEWAsQPppf = false;}
      if(IhYlJjdsRb == true){IhYlJjdsRb = false;}
      if(QFpIjlcZeQ == true){QFpIjlcZeQ = false;}
      if(eBjlcuDhYI == true){eBjlcuDhYI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWPHIBMVED
{ 
  void KqGghcgWBW()
  { 
      bool UoVCATwuie = false;
      bool pIqByuswif = false;
      bool SXrUQVbjsX = false;
      bool pTkPzkxmTF = false;
      bool kzKJIEOlRa = false;
      bool PUSHOwwAle = false;
      bool qLBKoVXbBM = false;
      bool yFcduSNiLL = false;
      bool HpSSHUAcBC = false;
      bool nxBoNYyzTm = false;
      bool gljEbJqoLu = false;
      bool iNnZXBrhCT = false;
      bool VtZyYBEnPV = false;
      bool UNOYdUFOpx = false;
      bool cLRFTaIaQM = false;
      bool gQwARmMkea = false;
      bool FDZpaUyPuC = false;
      bool wdqFpJcUey = false;
      bool rcWDoDQOHq = false;
      bool ITiPrZkbdy = false;
      string XrMDteAAXH;
      string heLKGHsFzy;
      string xmRGOVajCN;
      string gASuAniMdD;
      string biVQGGVtws;
      string EhHoEkaGoX;
      string EPxJZgLPJS;
      string YgbuVORAzH;
      string AfnIIzsdqP;
      string MbXFzMkLqZ;
      string uFjcUXGLSp;
      string TaGgXXbnAa;
      string nhYtGwJWuJ;
      string cFJZMtwKnk;
      string sgKAwlVpgb;
      string jwKQlMgpWY;
      string OiPIMNQfUd;
      string bQAPgGWXyU;
      string ZSpTYgtsnz;
      string NFnPVJQCmh;
      if(XrMDteAAXH == uFjcUXGLSp){UoVCATwuie = true;}
      else if(uFjcUXGLSp == XrMDteAAXH){gljEbJqoLu = true;}
      if(heLKGHsFzy == TaGgXXbnAa){pIqByuswif = true;}
      else if(TaGgXXbnAa == heLKGHsFzy){iNnZXBrhCT = true;}
      if(xmRGOVajCN == nhYtGwJWuJ){SXrUQVbjsX = true;}
      else if(nhYtGwJWuJ == xmRGOVajCN){VtZyYBEnPV = true;}
      if(gASuAniMdD == cFJZMtwKnk){pTkPzkxmTF = true;}
      else if(cFJZMtwKnk == gASuAniMdD){UNOYdUFOpx = true;}
      if(biVQGGVtws == sgKAwlVpgb){kzKJIEOlRa = true;}
      else if(sgKAwlVpgb == biVQGGVtws){cLRFTaIaQM = true;}
      if(EhHoEkaGoX == jwKQlMgpWY){PUSHOwwAle = true;}
      else if(jwKQlMgpWY == EhHoEkaGoX){gQwARmMkea = true;}
      if(EPxJZgLPJS == OiPIMNQfUd){qLBKoVXbBM = true;}
      else if(OiPIMNQfUd == EPxJZgLPJS){FDZpaUyPuC = true;}
      if(YgbuVORAzH == bQAPgGWXyU){yFcduSNiLL = true;}
      if(AfnIIzsdqP == ZSpTYgtsnz){HpSSHUAcBC = true;}
      if(MbXFzMkLqZ == NFnPVJQCmh){nxBoNYyzTm = true;}
      while(bQAPgGWXyU == YgbuVORAzH){wdqFpJcUey = true;}
      while(ZSpTYgtsnz == ZSpTYgtsnz){rcWDoDQOHq = true;}
      while(NFnPVJQCmh == NFnPVJQCmh){ITiPrZkbdy = true;}
      if(UoVCATwuie == true){UoVCATwuie = false;}
      if(pIqByuswif == true){pIqByuswif = false;}
      if(SXrUQVbjsX == true){SXrUQVbjsX = false;}
      if(pTkPzkxmTF == true){pTkPzkxmTF = false;}
      if(kzKJIEOlRa == true){kzKJIEOlRa = false;}
      if(PUSHOwwAle == true){PUSHOwwAle = false;}
      if(qLBKoVXbBM == true){qLBKoVXbBM = false;}
      if(yFcduSNiLL == true){yFcduSNiLL = false;}
      if(HpSSHUAcBC == true){HpSSHUAcBC = false;}
      if(nxBoNYyzTm == true){nxBoNYyzTm = false;}
      if(gljEbJqoLu == true){gljEbJqoLu = false;}
      if(iNnZXBrhCT == true){iNnZXBrhCT = false;}
      if(VtZyYBEnPV == true){VtZyYBEnPV = false;}
      if(UNOYdUFOpx == true){UNOYdUFOpx = false;}
      if(cLRFTaIaQM == true){cLRFTaIaQM = false;}
      if(gQwARmMkea == true){gQwARmMkea = false;}
      if(FDZpaUyPuC == true){FDZpaUyPuC = false;}
      if(wdqFpJcUey == true){wdqFpJcUey = false;}
      if(rcWDoDQOHq == true){rcWDoDQOHq = false;}
      if(ITiPrZkbdy == true){ITiPrZkbdy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RETTXFEBVZ
{ 
  void kbUVktpeZB()
  { 
      bool cxAoIuNiqb = false;
      bool IjalsqkdrV = false;
      bool pGEbdtMkpK = false;
      bool hstzKsiQqa = false;
      bool NwkWnSFkhK = false;
      bool juLNjVrXKO = false;
      bool ibrgtOpbbA = false;
      bool ITlRHtVgnK = false;
      bool naDfalhgOn = false;
      bool ALFbqkDDcY = false;
      bool ccIgCPItFp = false;
      bool zLiAZHYLGH = false;
      bool gJMnAwNKZV = false;
      bool pSEPhLSWdK = false;
      bool cnaYnobFCj = false;
      bool MqxUqTQUgF = false;
      bool CyUiAgGTSO = false;
      bool oBhudshnzK = false;
      bool UHHoIyUiXN = false;
      bool txoYIeTrYG = false;
      string WogriwqBmP;
      string oSPKipEDhf;
      string GmtLtxgnrE;
      string uIRbLoKwGG;
      string QHghdWKYSG;
      string qQogyjtVxl;
      string PDJiUfAmzs;
      string fHxaPzFLgX;
      string mHVkMeTkdb;
      string toyUqMxyMx;
      string VWZYajSORy;
      string dhnZyIgXVp;
      string MPJXzqIbjC;
      string BHzjBQhxKc;
      string LESfxLAYVi;
      string fZbWjFNBZi;
      string apeOxWiDYg;
      string ZjMreHxcZm;
      string pjFAWafbzw;
      string DfXaBUZDia;
      if(WogriwqBmP == VWZYajSORy){cxAoIuNiqb = true;}
      else if(VWZYajSORy == WogriwqBmP){ccIgCPItFp = true;}
      if(oSPKipEDhf == dhnZyIgXVp){IjalsqkdrV = true;}
      else if(dhnZyIgXVp == oSPKipEDhf){zLiAZHYLGH = true;}
      if(GmtLtxgnrE == MPJXzqIbjC){pGEbdtMkpK = true;}
      else if(MPJXzqIbjC == GmtLtxgnrE){gJMnAwNKZV = true;}
      if(uIRbLoKwGG == BHzjBQhxKc){hstzKsiQqa = true;}
      else if(BHzjBQhxKc == uIRbLoKwGG){pSEPhLSWdK = true;}
      if(QHghdWKYSG == LESfxLAYVi){NwkWnSFkhK = true;}
      else if(LESfxLAYVi == QHghdWKYSG){cnaYnobFCj = true;}
      if(qQogyjtVxl == fZbWjFNBZi){juLNjVrXKO = true;}
      else if(fZbWjFNBZi == qQogyjtVxl){MqxUqTQUgF = true;}
      if(PDJiUfAmzs == apeOxWiDYg){ibrgtOpbbA = true;}
      else if(apeOxWiDYg == PDJiUfAmzs){CyUiAgGTSO = true;}
      if(fHxaPzFLgX == ZjMreHxcZm){ITlRHtVgnK = true;}
      if(mHVkMeTkdb == pjFAWafbzw){naDfalhgOn = true;}
      if(toyUqMxyMx == DfXaBUZDia){ALFbqkDDcY = true;}
      while(ZjMreHxcZm == fHxaPzFLgX){oBhudshnzK = true;}
      while(pjFAWafbzw == pjFAWafbzw){UHHoIyUiXN = true;}
      while(DfXaBUZDia == DfXaBUZDia){txoYIeTrYG = true;}
      if(cxAoIuNiqb == true){cxAoIuNiqb = false;}
      if(IjalsqkdrV == true){IjalsqkdrV = false;}
      if(pGEbdtMkpK == true){pGEbdtMkpK = false;}
      if(hstzKsiQqa == true){hstzKsiQqa = false;}
      if(NwkWnSFkhK == true){NwkWnSFkhK = false;}
      if(juLNjVrXKO == true){juLNjVrXKO = false;}
      if(ibrgtOpbbA == true){ibrgtOpbbA = false;}
      if(ITlRHtVgnK == true){ITlRHtVgnK = false;}
      if(naDfalhgOn == true){naDfalhgOn = false;}
      if(ALFbqkDDcY == true){ALFbqkDDcY = false;}
      if(ccIgCPItFp == true){ccIgCPItFp = false;}
      if(zLiAZHYLGH == true){zLiAZHYLGH = false;}
      if(gJMnAwNKZV == true){gJMnAwNKZV = false;}
      if(pSEPhLSWdK == true){pSEPhLSWdK = false;}
      if(cnaYnobFCj == true){cnaYnobFCj = false;}
      if(MqxUqTQUgF == true){MqxUqTQUgF = false;}
      if(CyUiAgGTSO == true){CyUiAgGTSO = false;}
      if(oBhudshnzK == true){oBhudshnzK = false;}
      if(UHHoIyUiXN == true){UHHoIyUiXN = false;}
      if(txoYIeTrYG == true){txoYIeTrYG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZJJBHUOAI
{ 
  void qxCgsAkPCU()
  { 
      bool nJLBXCPyRJ = false;
      bool cnDBYKwxzB = false;
      bool SxXxIfQsNl = false;
      bool JuAjFCKoGD = false;
      bool ZYTBznTKLQ = false;
      bool DqePdqkNrq = false;
      bool kWkfAgmSuW = false;
      bool zGpwbtdVyT = false;
      bool MGgwhRQkGO = false;
      bool QxwPSCmnBR = false;
      bool AAOoQxBinj = false;
      bool MOPYddpnxh = false;
      bool QCMgFCKadY = false;
      bool GoUgTLrqfk = false;
      bool QgwVBChXkn = false;
      bool MypTAxnhjN = false;
      bool mZFOcXsiES = false;
      bool lyIMRjFpeC = false;
      bool UlooMIzBfV = false;
      bool XJHRxpbgrd = false;
      string mTarlBGHrZ;
      string nDtxLrqVET;
      string elYesDbByr;
      string yYRlosrpnM;
      string TBmFmznOfo;
      string qwZqDAtuzh;
      string ZFIAaOlIIR;
      string AAgrAczTrs;
      string ONUJABzahn;
      string zwqFmOsmdX;
      string NfFOnqOhpa;
      string BZDFTLjzzY;
      string PKZUSEIbFk;
      string jLpTeiIGUJ;
      string mRjHmYslla;
      string etnEIDGkuj;
      string hlbFqpjjZk;
      string DcdolyZRgt;
      string LWpdFoWlLb;
      string bWLkbAoeQw;
      if(mTarlBGHrZ == NfFOnqOhpa){nJLBXCPyRJ = true;}
      else if(NfFOnqOhpa == mTarlBGHrZ){AAOoQxBinj = true;}
      if(nDtxLrqVET == BZDFTLjzzY){cnDBYKwxzB = true;}
      else if(BZDFTLjzzY == nDtxLrqVET){MOPYddpnxh = true;}
      if(elYesDbByr == PKZUSEIbFk){SxXxIfQsNl = true;}
      else if(PKZUSEIbFk == elYesDbByr){QCMgFCKadY = true;}
      if(yYRlosrpnM == jLpTeiIGUJ){JuAjFCKoGD = true;}
      else if(jLpTeiIGUJ == yYRlosrpnM){GoUgTLrqfk = true;}
      if(TBmFmznOfo == mRjHmYslla){ZYTBznTKLQ = true;}
      else if(mRjHmYslla == TBmFmznOfo){QgwVBChXkn = true;}
      if(qwZqDAtuzh == etnEIDGkuj){DqePdqkNrq = true;}
      else if(etnEIDGkuj == qwZqDAtuzh){MypTAxnhjN = true;}
      if(ZFIAaOlIIR == hlbFqpjjZk){kWkfAgmSuW = true;}
      else if(hlbFqpjjZk == ZFIAaOlIIR){mZFOcXsiES = true;}
      if(AAgrAczTrs == DcdolyZRgt){zGpwbtdVyT = true;}
      if(ONUJABzahn == LWpdFoWlLb){MGgwhRQkGO = true;}
      if(zwqFmOsmdX == bWLkbAoeQw){QxwPSCmnBR = true;}
      while(DcdolyZRgt == AAgrAczTrs){lyIMRjFpeC = true;}
      while(LWpdFoWlLb == LWpdFoWlLb){UlooMIzBfV = true;}
      while(bWLkbAoeQw == bWLkbAoeQw){XJHRxpbgrd = true;}
      if(nJLBXCPyRJ == true){nJLBXCPyRJ = false;}
      if(cnDBYKwxzB == true){cnDBYKwxzB = false;}
      if(SxXxIfQsNl == true){SxXxIfQsNl = false;}
      if(JuAjFCKoGD == true){JuAjFCKoGD = false;}
      if(ZYTBznTKLQ == true){ZYTBznTKLQ = false;}
      if(DqePdqkNrq == true){DqePdqkNrq = false;}
      if(kWkfAgmSuW == true){kWkfAgmSuW = false;}
      if(zGpwbtdVyT == true){zGpwbtdVyT = false;}
      if(MGgwhRQkGO == true){MGgwhRQkGO = false;}
      if(QxwPSCmnBR == true){QxwPSCmnBR = false;}
      if(AAOoQxBinj == true){AAOoQxBinj = false;}
      if(MOPYddpnxh == true){MOPYddpnxh = false;}
      if(QCMgFCKadY == true){QCMgFCKadY = false;}
      if(GoUgTLrqfk == true){GoUgTLrqfk = false;}
      if(QgwVBChXkn == true){QgwVBChXkn = false;}
      if(MypTAxnhjN == true){MypTAxnhjN = false;}
      if(mZFOcXsiES == true){mZFOcXsiES = false;}
      if(lyIMRjFpeC == true){lyIMRjFpeC = false;}
      if(UlooMIzBfV == true){UlooMIzBfV = false;}
      if(XJHRxpbgrd == true){XJHRxpbgrd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHQQRJGOGG
{ 
  void erBaBdhjJn()
  { 
      bool ZTVFUCqsgj = false;
      bool JyVlwlZDqO = false;
      bool qyhmtMtlRH = false;
      bool xKGByMrcHV = false;
      bool kDJVWWojZc = false;
      bool HJDpHaliLH = false;
      bool HEaYlzrUni = false;
      bool twwUcnoMPW = false;
      bool XKMoAnGQtX = false;
      bool aIRzNgckiX = false;
      bool eTwpiKMhMT = false;
      bool lZTnjxqkYy = false;
      bool rbaPIkexHw = false;
      bool LDcrrDOVGo = false;
      bool aYDZlBocOQ = false;
      bool oqMjeDsfhx = false;
      bool fPaQIhwawg = false;
      bool hVdiWSXAdH = false;
      bool uBhpGTqrMo = false;
      bool JimJIKxmRD = false;
      string yOeNclNyEL;
      string CCursWwaMy;
      string XpwqbknkWj;
      string fIZXGljnHu;
      string rksgrEouGE;
      string NeQLGHSmkq;
      string xbbUftbXlH;
      string lHTRGlwOyW;
      string wreSWAqOQy;
      string TwDPxPJYBx;
      string bQJySFLzFU;
      string LDoNuFxJye;
      string CNHmnoEDTp;
      string cWNAtehgzQ;
      string orIwmPHoUr;
      string SAaWtOJWKc;
      string BHeOqnpnSP;
      string XQJgoKEKAX;
      string gOhbXcwqFf;
      string VLVWOgMtEy;
      if(yOeNclNyEL == bQJySFLzFU){ZTVFUCqsgj = true;}
      else if(bQJySFLzFU == yOeNclNyEL){eTwpiKMhMT = true;}
      if(CCursWwaMy == LDoNuFxJye){JyVlwlZDqO = true;}
      else if(LDoNuFxJye == CCursWwaMy){lZTnjxqkYy = true;}
      if(XpwqbknkWj == CNHmnoEDTp){qyhmtMtlRH = true;}
      else if(CNHmnoEDTp == XpwqbknkWj){rbaPIkexHw = true;}
      if(fIZXGljnHu == cWNAtehgzQ){xKGByMrcHV = true;}
      else if(cWNAtehgzQ == fIZXGljnHu){LDcrrDOVGo = true;}
      if(rksgrEouGE == orIwmPHoUr){kDJVWWojZc = true;}
      else if(orIwmPHoUr == rksgrEouGE){aYDZlBocOQ = true;}
      if(NeQLGHSmkq == SAaWtOJWKc){HJDpHaliLH = true;}
      else if(SAaWtOJWKc == NeQLGHSmkq){oqMjeDsfhx = true;}
      if(xbbUftbXlH == BHeOqnpnSP){HEaYlzrUni = true;}
      else if(BHeOqnpnSP == xbbUftbXlH){fPaQIhwawg = true;}
      if(lHTRGlwOyW == XQJgoKEKAX){twwUcnoMPW = true;}
      if(wreSWAqOQy == gOhbXcwqFf){XKMoAnGQtX = true;}
      if(TwDPxPJYBx == VLVWOgMtEy){aIRzNgckiX = true;}
      while(XQJgoKEKAX == lHTRGlwOyW){hVdiWSXAdH = true;}
      while(gOhbXcwqFf == gOhbXcwqFf){uBhpGTqrMo = true;}
      while(VLVWOgMtEy == VLVWOgMtEy){JimJIKxmRD = true;}
      if(ZTVFUCqsgj == true){ZTVFUCqsgj = false;}
      if(JyVlwlZDqO == true){JyVlwlZDqO = false;}
      if(qyhmtMtlRH == true){qyhmtMtlRH = false;}
      if(xKGByMrcHV == true){xKGByMrcHV = false;}
      if(kDJVWWojZc == true){kDJVWWojZc = false;}
      if(HJDpHaliLH == true){HJDpHaliLH = false;}
      if(HEaYlzrUni == true){HEaYlzrUni = false;}
      if(twwUcnoMPW == true){twwUcnoMPW = false;}
      if(XKMoAnGQtX == true){XKMoAnGQtX = false;}
      if(aIRzNgckiX == true){aIRzNgckiX = false;}
      if(eTwpiKMhMT == true){eTwpiKMhMT = false;}
      if(lZTnjxqkYy == true){lZTnjxqkYy = false;}
      if(rbaPIkexHw == true){rbaPIkexHw = false;}
      if(LDcrrDOVGo == true){LDcrrDOVGo = false;}
      if(aYDZlBocOQ == true){aYDZlBocOQ = false;}
      if(oqMjeDsfhx == true){oqMjeDsfhx = false;}
      if(fPaQIhwawg == true){fPaQIhwawg = false;}
      if(hVdiWSXAdH == true){hVdiWSXAdH = false;}
      if(uBhpGTqrMo == true){uBhpGTqrMo = false;}
      if(JimJIKxmRD == true){JimJIKxmRD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUUUMNXNLD
{ 
  void WxSddnRtTz()
  { 
      bool fgATjsjYjG = false;
      bool PsAMhZOGcI = false;
      bool TXQUqsPrpl = false;
      bool PbuhAIrFBJ = false;
      bool IFBacNWNCd = false;
      bool mUnVuIQecq = false;
      bool dqhxqnySMZ = false;
      bool hJETzNVprc = false;
      bool WBpLytmZmq = false;
      bool qMbKeQWDjn = false;
      bool PDBbwcPTVg = false;
      bool lamATcBVzw = false;
      bool AXfUhVhtni = false;
      bool qRFDNSzNPV = false;
      bool eTEFFQYbpC = false;
      bool PAEnnqXgta = false;
      bool uVfmpTUjlB = false;
      bool cnGdRgTZOQ = false;
      bool wGDkTpNRPW = false;
      bool tRSoZInRPk = false;
      string ABebqQZSbo;
      string PZttUOoufV;
      string paUJJTAeeO;
      string lFRzeogzNE;
      string nlwHTHTWub;
      string QNGALYfVSX;
      string PtnNDJHtPe;
      string hogbgDeNpB;
      string zcjCxXyRnG;
      string ILgpntyhDJ;
      string zZHPtafeTH;
      string sSeQXmKkPf;
      string KpGJWVIqmm;
      string FwJfCZVTIV;
      string qTxfMpfPRB;
      string jMRXyISysX;
      string SorfBxJyOx;
      string QpcsnqrZxg;
      string psZlDsdkhs;
      string GXajDCaQdO;
      if(ABebqQZSbo == zZHPtafeTH){fgATjsjYjG = true;}
      else if(zZHPtafeTH == ABebqQZSbo){PDBbwcPTVg = true;}
      if(PZttUOoufV == sSeQXmKkPf){PsAMhZOGcI = true;}
      else if(sSeQXmKkPf == PZttUOoufV){lamATcBVzw = true;}
      if(paUJJTAeeO == KpGJWVIqmm){TXQUqsPrpl = true;}
      else if(KpGJWVIqmm == paUJJTAeeO){AXfUhVhtni = true;}
      if(lFRzeogzNE == FwJfCZVTIV){PbuhAIrFBJ = true;}
      else if(FwJfCZVTIV == lFRzeogzNE){qRFDNSzNPV = true;}
      if(nlwHTHTWub == qTxfMpfPRB){IFBacNWNCd = true;}
      else if(qTxfMpfPRB == nlwHTHTWub){eTEFFQYbpC = true;}
      if(QNGALYfVSX == jMRXyISysX){mUnVuIQecq = true;}
      else if(jMRXyISysX == QNGALYfVSX){PAEnnqXgta = true;}
      if(PtnNDJHtPe == SorfBxJyOx){dqhxqnySMZ = true;}
      else if(SorfBxJyOx == PtnNDJHtPe){uVfmpTUjlB = true;}
      if(hogbgDeNpB == QpcsnqrZxg){hJETzNVprc = true;}
      if(zcjCxXyRnG == psZlDsdkhs){WBpLytmZmq = true;}
      if(ILgpntyhDJ == GXajDCaQdO){qMbKeQWDjn = true;}
      while(QpcsnqrZxg == hogbgDeNpB){cnGdRgTZOQ = true;}
      while(psZlDsdkhs == psZlDsdkhs){wGDkTpNRPW = true;}
      while(GXajDCaQdO == GXajDCaQdO){tRSoZInRPk = true;}
      if(fgATjsjYjG == true){fgATjsjYjG = false;}
      if(PsAMhZOGcI == true){PsAMhZOGcI = false;}
      if(TXQUqsPrpl == true){TXQUqsPrpl = false;}
      if(PbuhAIrFBJ == true){PbuhAIrFBJ = false;}
      if(IFBacNWNCd == true){IFBacNWNCd = false;}
      if(mUnVuIQecq == true){mUnVuIQecq = false;}
      if(dqhxqnySMZ == true){dqhxqnySMZ = false;}
      if(hJETzNVprc == true){hJETzNVprc = false;}
      if(WBpLytmZmq == true){WBpLytmZmq = false;}
      if(qMbKeQWDjn == true){qMbKeQWDjn = false;}
      if(PDBbwcPTVg == true){PDBbwcPTVg = false;}
      if(lamATcBVzw == true){lamATcBVzw = false;}
      if(AXfUhVhtni == true){AXfUhVhtni = false;}
      if(qRFDNSzNPV == true){qRFDNSzNPV = false;}
      if(eTEFFQYbpC == true){eTEFFQYbpC = false;}
      if(PAEnnqXgta == true){PAEnnqXgta = false;}
      if(uVfmpTUjlB == true){uVfmpTUjlB = false;}
      if(cnGdRgTZOQ == true){cnGdRgTZOQ = false;}
      if(wGDkTpNRPW == true){wGDkTpNRPW = false;}
      if(tRSoZInRPk == true){tRSoZInRPk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJQVDSDKJE
{ 
  void CejIsDglQD()
  { 
      bool OrACrTBNtm = false;
      bool scEWRtrYWG = false;
      bool uLCtyKcVCz = false;
      bool plGHVgjHRh = false;
      bool gCHLVVojmV = false;
      bool VHYliCpGDg = false;
      bool pfKuwGWwBj = false;
      bool JjHnZrEqXc = false;
      bool VshgchNTYS = false;
      bool qdEkrBqMOP = false;
      bool zshDLkAjLp = false;
      bool yziaLxxdRO = false;
      bool rCXisffWwY = false;
      bool AqbIccKdVq = false;
      bool gcIhTqtdYt = false;
      bool DNuAWxUzKe = false;
      bool FdnmpGWaxi = false;
      bool lSHZgOtpOB = false;
      bool lCxBVlwbkf = false;
      bool HLTplCoUqM = false;
      string jMTbTmFSsY;
      string twMbplhMbx;
      string rgoEHKtVmE;
      string TwqwCZRdff;
      string mflqwkarke;
      string frnpMDWPUI;
      string rifoFxFQZP;
      string UEguKLtxHV;
      string jCjHYaIBiy;
      string CBIXmDAxlz;
      string fJRUKbLrfA;
      string IYIzXpzXPd;
      string nEhaNSuJIG;
      string KxKIpajOxw;
      string PQUhocsJzx;
      string EcgIKbbpHq;
      string fBjYoLOAIx;
      string FjaSNXizlj;
      string ZkJKChQCyO;
      string ytHFQNgwsd;
      if(jMTbTmFSsY == fJRUKbLrfA){OrACrTBNtm = true;}
      else if(fJRUKbLrfA == jMTbTmFSsY){zshDLkAjLp = true;}
      if(twMbplhMbx == IYIzXpzXPd){scEWRtrYWG = true;}
      else if(IYIzXpzXPd == twMbplhMbx){yziaLxxdRO = true;}
      if(rgoEHKtVmE == nEhaNSuJIG){uLCtyKcVCz = true;}
      else if(nEhaNSuJIG == rgoEHKtVmE){rCXisffWwY = true;}
      if(TwqwCZRdff == KxKIpajOxw){plGHVgjHRh = true;}
      else if(KxKIpajOxw == TwqwCZRdff){AqbIccKdVq = true;}
      if(mflqwkarke == PQUhocsJzx){gCHLVVojmV = true;}
      else if(PQUhocsJzx == mflqwkarke){gcIhTqtdYt = true;}
      if(frnpMDWPUI == EcgIKbbpHq){VHYliCpGDg = true;}
      else if(EcgIKbbpHq == frnpMDWPUI){DNuAWxUzKe = true;}
      if(rifoFxFQZP == fBjYoLOAIx){pfKuwGWwBj = true;}
      else if(fBjYoLOAIx == rifoFxFQZP){FdnmpGWaxi = true;}
      if(UEguKLtxHV == FjaSNXizlj){JjHnZrEqXc = true;}
      if(jCjHYaIBiy == ZkJKChQCyO){VshgchNTYS = true;}
      if(CBIXmDAxlz == ytHFQNgwsd){qdEkrBqMOP = true;}
      while(FjaSNXizlj == UEguKLtxHV){lSHZgOtpOB = true;}
      while(ZkJKChQCyO == ZkJKChQCyO){lCxBVlwbkf = true;}
      while(ytHFQNgwsd == ytHFQNgwsd){HLTplCoUqM = true;}
      if(OrACrTBNtm == true){OrACrTBNtm = false;}
      if(scEWRtrYWG == true){scEWRtrYWG = false;}
      if(uLCtyKcVCz == true){uLCtyKcVCz = false;}
      if(plGHVgjHRh == true){plGHVgjHRh = false;}
      if(gCHLVVojmV == true){gCHLVVojmV = false;}
      if(VHYliCpGDg == true){VHYliCpGDg = false;}
      if(pfKuwGWwBj == true){pfKuwGWwBj = false;}
      if(JjHnZrEqXc == true){JjHnZrEqXc = false;}
      if(VshgchNTYS == true){VshgchNTYS = false;}
      if(qdEkrBqMOP == true){qdEkrBqMOP = false;}
      if(zshDLkAjLp == true){zshDLkAjLp = false;}
      if(yziaLxxdRO == true){yziaLxxdRO = false;}
      if(rCXisffWwY == true){rCXisffWwY = false;}
      if(AqbIccKdVq == true){AqbIccKdVq = false;}
      if(gcIhTqtdYt == true){gcIhTqtdYt = false;}
      if(DNuAWxUzKe == true){DNuAWxUzKe = false;}
      if(FdnmpGWaxi == true){FdnmpGWaxi = false;}
      if(lSHZgOtpOB == true){lSHZgOtpOB = false;}
      if(lCxBVlwbkf == true){lCxBVlwbkf = false;}
      if(HLTplCoUqM == true){HLTplCoUqM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHTVNVZGGZ
{ 
  void rlexhjCNJR()
  { 
      bool NKwujIbHQk = false;
      bool gkBbuxRsXy = false;
      bool obzTKRxXlO = false;
      bool AiaUYLzxzI = false;
      bool lelCPlxZIg = false;
      bool UfwnilKbjR = false;
      bool KEVBkyJgDi = false;
      bool xUsOMJpwEY = false;
      bool UXOEsTlmkl = false;
      bool BXMhygJjRR = false;
      bool bQWZizmhbY = false;
      bool wNXLxloQHR = false;
      bool LWuQgZIKPe = false;
      bool AGelwDBoVs = false;
      bool fEKLpmAAkL = false;
      bool qrbzFEVFrI = false;
      bool qcRwYpikOs = false;
      bool kztOlHMiat = false;
      bool ZHZDmHdefr = false;
      bool huxMCDlNmA = false;
      string OTqeieAHPy;
      string SSacuSEbrz;
      string YCjRFtrYCz;
      string RZjeyZLjWx;
      string AFdxedJOOt;
      string XlJMzLjZYo;
      string lbFQfrhudU;
      string GUEuySYllb;
      string jcKIafQWfl;
      string plKhKYANRm;
      string uNksmDhNNf;
      string mymxEJQwoz;
      string bLOqeUJWkY;
      string SLTzfWrQUX;
      string yCIAzryNdB;
      string IDXRKizsOR;
      string sKcnNbdnQh;
      string QAaQBZCOrl;
      string WwsjQOmCnw;
      string WyCDemZTmX;
      if(OTqeieAHPy == uNksmDhNNf){NKwujIbHQk = true;}
      else if(uNksmDhNNf == OTqeieAHPy){bQWZizmhbY = true;}
      if(SSacuSEbrz == mymxEJQwoz){gkBbuxRsXy = true;}
      else if(mymxEJQwoz == SSacuSEbrz){wNXLxloQHR = true;}
      if(YCjRFtrYCz == bLOqeUJWkY){obzTKRxXlO = true;}
      else if(bLOqeUJWkY == YCjRFtrYCz){LWuQgZIKPe = true;}
      if(RZjeyZLjWx == SLTzfWrQUX){AiaUYLzxzI = true;}
      else if(SLTzfWrQUX == RZjeyZLjWx){AGelwDBoVs = true;}
      if(AFdxedJOOt == yCIAzryNdB){lelCPlxZIg = true;}
      else if(yCIAzryNdB == AFdxedJOOt){fEKLpmAAkL = true;}
      if(XlJMzLjZYo == IDXRKizsOR){UfwnilKbjR = true;}
      else if(IDXRKizsOR == XlJMzLjZYo){qrbzFEVFrI = true;}
      if(lbFQfrhudU == sKcnNbdnQh){KEVBkyJgDi = true;}
      else if(sKcnNbdnQh == lbFQfrhudU){qcRwYpikOs = true;}
      if(GUEuySYllb == QAaQBZCOrl){xUsOMJpwEY = true;}
      if(jcKIafQWfl == WwsjQOmCnw){UXOEsTlmkl = true;}
      if(plKhKYANRm == WyCDemZTmX){BXMhygJjRR = true;}
      while(QAaQBZCOrl == GUEuySYllb){kztOlHMiat = true;}
      while(WwsjQOmCnw == WwsjQOmCnw){ZHZDmHdefr = true;}
      while(WyCDemZTmX == WyCDemZTmX){huxMCDlNmA = true;}
      if(NKwujIbHQk == true){NKwujIbHQk = false;}
      if(gkBbuxRsXy == true){gkBbuxRsXy = false;}
      if(obzTKRxXlO == true){obzTKRxXlO = false;}
      if(AiaUYLzxzI == true){AiaUYLzxzI = false;}
      if(lelCPlxZIg == true){lelCPlxZIg = false;}
      if(UfwnilKbjR == true){UfwnilKbjR = false;}
      if(KEVBkyJgDi == true){KEVBkyJgDi = false;}
      if(xUsOMJpwEY == true){xUsOMJpwEY = false;}
      if(UXOEsTlmkl == true){UXOEsTlmkl = false;}
      if(BXMhygJjRR == true){BXMhygJjRR = false;}
      if(bQWZizmhbY == true){bQWZizmhbY = false;}
      if(wNXLxloQHR == true){wNXLxloQHR = false;}
      if(LWuQgZIKPe == true){LWuQgZIKPe = false;}
      if(AGelwDBoVs == true){AGelwDBoVs = false;}
      if(fEKLpmAAkL == true){fEKLpmAAkL = false;}
      if(qrbzFEVFrI == true){qrbzFEVFrI = false;}
      if(qcRwYpikOs == true){qcRwYpikOs = false;}
      if(kztOlHMiat == true){kztOlHMiat = false;}
      if(ZHZDmHdefr == true){ZHZDmHdefr = false;}
      if(huxMCDlNmA == true){huxMCDlNmA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HINGHBSKND
{ 
  void xXiKiRmxtc()
  { 
      bool oTaNtydUOp = false;
      bool ghDlTVCyuU = false;
      bool ZiawrWJfqb = false;
      bool HhfSWShxQQ = false;
      bool UJcJqLWgQN = false;
      bool gWQMdGreUW = false;
      bool oycmhyCjOB = false;
      bool mEgdzPFRFg = false;
      bool zcOdtkQSoP = false;
      bool ZDctbWfpar = false;
      bool ImROZcolMO = false;
      bool BaYmWLizrx = false;
      bool giuybjamCc = false;
      bool iPpMYMKzEQ = false;
      bool ueGZOzdpXP = false;
      bool mgxdKZrSmo = false;
      bool CCjiekjMOK = false;
      bool BiubBCbUjb = false;
      bool GkPloCSMCy = false;
      bool TqMOOstWud = false;
      string PMUrXixmmH;
      string uhNqxMynnU;
      string rcPaeudJxB;
      string dwofYIlcDu;
      string ItUMcltWQP;
      string EJEONlxtNb;
      string EmpkczrhRn;
      string aUksMyICxs;
      string BGsgxUqZRl;
      string LrPapUDiic;
      string sLFboiXLCP;
      string dtwTaytInI;
      string IRPechEKCq;
      string tZSUzoARrN;
      string weXCIQuuzq;
      string autaTauZyG;
      string eNJLUEabUl;
      string xcQZLdtNWM;
      string lIKKPzerAX;
      string saSkiiVMhD;
      if(PMUrXixmmH == sLFboiXLCP){oTaNtydUOp = true;}
      else if(sLFboiXLCP == PMUrXixmmH){ImROZcolMO = true;}
      if(uhNqxMynnU == dtwTaytInI){ghDlTVCyuU = true;}
      else if(dtwTaytInI == uhNqxMynnU){BaYmWLizrx = true;}
      if(rcPaeudJxB == IRPechEKCq){ZiawrWJfqb = true;}
      else if(IRPechEKCq == rcPaeudJxB){giuybjamCc = true;}
      if(dwofYIlcDu == tZSUzoARrN){HhfSWShxQQ = true;}
      else if(tZSUzoARrN == dwofYIlcDu){iPpMYMKzEQ = true;}
      if(ItUMcltWQP == weXCIQuuzq){UJcJqLWgQN = true;}
      else if(weXCIQuuzq == ItUMcltWQP){ueGZOzdpXP = true;}
      if(EJEONlxtNb == autaTauZyG){gWQMdGreUW = true;}
      else if(autaTauZyG == EJEONlxtNb){mgxdKZrSmo = true;}
      if(EmpkczrhRn == eNJLUEabUl){oycmhyCjOB = true;}
      else if(eNJLUEabUl == EmpkczrhRn){CCjiekjMOK = true;}
      if(aUksMyICxs == xcQZLdtNWM){mEgdzPFRFg = true;}
      if(BGsgxUqZRl == lIKKPzerAX){zcOdtkQSoP = true;}
      if(LrPapUDiic == saSkiiVMhD){ZDctbWfpar = true;}
      while(xcQZLdtNWM == aUksMyICxs){BiubBCbUjb = true;}
      while(lIKKPzerAX == lIKKPzerAX){GkPloCSMCy = true;}
      while(saSkiiVMhD == saSkiiVMhD){TqMOOstWud = true;}
      if(oTaNtydUOp == true){oTaNtydUOp = false;}
      if(ghDlTVCyuU == true){ghDlTVCyuU = false;}
      if(ZiawrWJfqb == true){ZiawrWJfqb = false;}
      if(HhfSWShxQQ == true){HhfSWShxQQ = false;}
      if(UJcJqLWgQN == true){UJcJqLWgQN = false;}
      if(gWQMdGreUW == true){gWQMdGreUW = false;}
      if(oycmhyCjOB == true){oycmhyCjOB = false;}
      if(mEgdzPFRFg == true){mEgdzPFRFg = false;}
      if(zcOdtkQSoP == true){zcOdtkQSoP = false;}
      if(ZDctbWfpar == true){ZDctbWfpar = false;}
      if(ImROZcolMO == true){ImROZcolMO = false;}
      if(BaYmWLizrx == true){BaYmWLizrx = false;}
      if(giuybjamCc == true){giuybjamCc = false;}
      if(iPpMYMKzEQ == true){iPpMYMKzEQ = false;}
      if(ueGZOzdpXP == true){ueGZOzdpXP = false;}
      if(mgxdKZrSmo == true){mgxdKZrSmo = false;}
      if(CCjiekjMOK == true){CCjiekjMOK = false;}
      if(BiubBCbUjb == true){BiubBCbUjb = false;}
      if(GkPloCSMCy == true){GkPloCSMCy = false;}
      if(TqMOOstWud == true){TqMOOstWud = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARYVBGCKFI
{ 
  void YYqshnIYJQ()
  { 
      bool TjgHUQQbYt = false;
      bool cDokmBAcKo = false;
      bool ilgTuCtygV = false;
      bool jXeiWtgUIW = false;
      bool uSjjeztAEK = false;
      bool ZEOiRhCNMS = false;
      bool WRuCJFYFOs = false;
      bool UfUmtPBxnu = false;
      bool IssVueJuQn = false;
      bool qTHpAcXgaZ = false;
      bool ZnkLpsjaoC = false;
      bool fFYQJcYYGe = false;
      bool udoaBBYdlR = false;
      bool rUVNVUHhfB = false;
      bool thGOHktqfX = false;
      bool DyZudwzKJo = false;
      bool UGnXJLiKuo = false;
      bool UpsEjMWZTQ = false;
      bool GgxONstajY = false;
      bool UxXpgntiFu = false;
      string dVliEXReWl;
      string zuMNNrwMhP;
      string pdrVwBcZZo;
      string VKUpYSQGQw;
      string kNXoJTHecV;
      string bGdNwAdPmC;
      string trFhQoZWot;
      string bpuldbFDMb;
      string tywENOgGtY;
      string oATNBsIpXU;
      string sjohskKqiT;
      string tZDKIuuBUB;
      string HTcPFaWhjk;
      string SPeqhKJOKb;
      string EoWZeOwIFG;
      string xHUVMZHZbR;
      string OcGyBdtLby;
      string lgpsxSwDjp;
      string eNbdnLuIeI;
      string CilrMahYYB;
      if(dVliEXReWl == sjohskKqiT){TjgHUQQbYt = true;}
      else if(sjohskKqiT == dVliEXReWl){ZnkLpsjaoC = true;}
      if(zuMNNrwMhP == tZDKIuuBUB){cDokmBAcKo = true;}
      else if(tZDKIuuBUB == zuMNNrwMhP){fFYQJcYYGe = true;}
      if(pdrVwBcZZo == HTcPFaWhjk){ilgTuCtygV = true;}
      else if(HTcPFaWhjk == pdrVwBcZZo){udoaBBYdlR = true;}
      if(VKUpYSQGQw == SPeqhKJOKb){jXeiWtgUIW = true;}
      else if(SPeqhKJOKb == VKUpYSQGQw){rUVNVUHhfB = true;}
      if(kNXoJTHecV == EoWZeOwIFG){uSjjeztAEK = true;}
      else if(EoWZeOwIFG == kNXoJTHecV){thGOHktqfX = true;}
      if(bGdNwAdPmC == xHUVMZHZbR){ZEOiRhCNMS = true;}
      else if(xHUVMZHZbR == bGdNwAdPmC){DyZudwzKJo = true;}
      if(trFhQoZWot == OcGyBdtLby){WRuCJFYFOs = true;}
      else if(OcGyBdtLby == trFhQoZWot){UGnXJLiKuo = true;}
      if(bpuldbFDMb == lgpsxSwDjp){UfUmtPBxnu = true;}
      if(tywENOgGtY == eNbdnLuIeI){IssVueJuQn = true;}
      if(oATNBsIpXU == CilrMahYYB){qTHpAcXgaZ = true;}
      while(lgpsxSwDjp == bpuldbFDMb){UpsEjMWZTQ = true;}
      while(eNbdnLuIeI == eNbdnLuIeI){GgxONstajY = true;}
      while(CilrMahYYB == CilrMahYYB){UxXpgntiFu = true;}
      if(TjgHUQQbYt == true){TjgHUQQbYt = false;}
      if(cDokmBAcKo == true){cDokmBAcKo = false;}
      if(ilgTuCtygV == true){ilgTuCtygV = false;}
      if(jXeiWtgUIW == true){jXeiWtgUIW = false;}
      if(uSjjeztAEK == true){uSjjeztAEK = false;}
      if(ZEOiRhCNMS == true){ZEOiRhCNMS = false;}
      if(WRuCJFYFOs == true){WRuCJFYFOs = false;}
      if(UfUmtPBxnu == true){UfUmtPBxnu = false;}
      if(IssVueJuQn == true){IssVueJuQn = false;}
      if(qTHpAcXgaZ == true){qTHpAcXgaZ = false;}
      if(ZnkLpsjaoC == true){ZnkLpsjaoC = false;}
      if(fFYQJcYYGe == true){fFYQJcYYGe = false;}
      if(udoaBBYdlR == true){udoaBBYdlR = false;}
      if(rUVNVUHhfB == true){rUVNVUHhfB = false;}
      if(thGOHktqfX == true){thGOHktqfX = false;}
      if(DyZudwzKJo == true){DyZudwzKJo = false;}
      if(UGnXJLiKuo == true){UGnXJLiKuo = false;}
      if(UpsEjMWZTQ == true){UpsEjMWZTQ = false;}
      if(GgxONstajY == true){GgxONstajY = false;}
      if(UxXpgntiFu == true){UxXpgntiFu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZLYJZRPZH
{ 
  void rUFyppQEHs()
  { 
      bool jcPiTzTedk = false;
      bool dNWuSgaaZr = false;
      bool BnVGLxzuuI = false;
      bool ZZTcROMIIj = false;
      bool uJbMnliKqh = false;
      bool hRgDOwHJXV = false;
      bool AYiULDttcE = false;
      bool URSoxqMJRY = false;
      bool OnENaHrPNV = false;
      bool GDkljWaGAj = false;
      bool qohmNPzqGW = false;
      bool iyryHLTVsE = false;
      bool LdfGyQffFa = false;
      bool QFIggZGRzK = false;
      bool HAIqlHKmdX = false;
      bool CEMwYNIanw = false;
      bool iSlfFdoKQh = false;
      bool FCViwKUnUp = false;
      bool GsCgXLrMHT = false;
      bool QfcDbnOckI = false;
      string yFwwKeLVaj;
      string DWKYaRnUuC;
      string pXODHtWVam;
      string HqKpARKeAC;
      string CxQUgURmmG;
      string jZswoaprnQ;
      string IpuncMLUYI;
      string GIUrzrGtWl;
      string bjhUChxNAZ;
      string aSpitLBbqT;
      string JxOezbEBxx;
      string TwVCoXIalu;
      string PyTygnRlym;
      string peCCcdVDUZ;
      string cwQDFewntV;
      string DapwEKdPxK;
      string KSCJHotSYK;
      string CEGLSSgPsC;
      string qcrbiPnFxS;
      string zFFKPJsHwP;
      if(yFwwKeLVaj == JxOezbEBxx){jcPiTzTedk = true;}
      else if(JxOezbEBxx == yFwwKeLVaj){qohmNPzqGW = true;}
      if(DWKYaRnUuC == TwVCoXIalu){dNWuSgaaZr = true;}
      else if(TwVCoXIalu == DWKYaRnUuC){iyryHLTVsE = true;}
      if(pXODHtWVam == PyTygnRlym){BnVGLxzuuI = true;}
      else if(PyTygnRlym == pXODHtWVam){LdfGyQffFa = true;}
      if(HqKpARKeAC == peCCcdVDUZ){ZZTcROMIIj = true;}
      else if(peCCcdVDUZ == HqKpARKeAC){QFIggZGRzK = true;}
      if(CxQUgURmmG == cwQDFewntV){uJbMnliKqh = true;}
      else if(cwQDFewntV == CxQUgURmmG){HAIqlHKmdX = true;}
      if(jZswoaprnQ == DapwEKdPxK){hRgDOwHJXV = true;}
      else if(DapwEKdPxK == jZswoaprnQ){CEMwYNIanw = true;}
      if(IpuncMLUYI == KSCJHotSYK){AYiULDttcE = true;}
      else if(KSCJHotSYK == IpuncMLUYI){iSlfFdoKQh = true;}
      if(GIUrzrGtWl == CEGLSSgPsC){URSoxqMJRY = true;}
      if(bjhUChxNAZ == qcrbiPnFxS){OnENaHrPNV = true;}
      if(aSpitLBbqT == zFFKPJsHwP){GDkljWaGAj = true;}
      while(CEGLSSgPsC == GIUrzrGtWl){FCViwKUnUp = true;}
      while(qcrbiPnFxS == qcrbiPnFxS){GsCgXLrMHT = true;}
      while(zFFKPJsHwP == zFFKPJsHwP){QfcDbnOckI = true;}
      if(jcPiTzTedk == true){jcPiTzTedk = false;}
      if(dNWuSgaaZr == true){dNWuSgaaZr = false;}
      if(BnVGLxzuuI == true){BnVGLxzuuI = false;}
      if(ZZTcROMIIj == true){ZZTcROMIIj = false;}
      if(uJbMnliKqh == true){uJbMnliKqh = false;}
      if(hRgDOwHJXV == true){hRgDOwHJXV = false;}
      if(AYiULDttcE == true){AYiULDttcE = false;}
      if(URSoxqMJRY == true){URSoxqMJRY = false;}
      if(OnENaHrPNV == true){OnENaHrPNV = false;}
      if(GDkljWaGAj == true){GDkljWaGAj = false;}
      if(qohmNPzqGW == true){qohmNPzqGW = false;}
      if(iyryHLTVsE == true){iyryHLTVsE = false;}
      if(LdfGyQffFa == true){LdfGyQffFa = false;}
      if(QFIggZGRzK == true){QFIggZGRzK = false;}
      if(HAIqlHKmdX == true){HAIqlHKmdX = false;}
      if(CEMwYNIanw == true){CEMwYNIanw = false;}
      if(iSlfFdoKQh == true){iSlfFdoKQh = false;}
      if(FCViwKUnUp == true){FCViwKUnUp = false;}
      if(GsCgXLrMHT == true){GsCgXLrMHT = false;}
      if(QfcDbnOckI == true){QfcDbnOckI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BATNXIPZLD
{ 
  void EoMuWcSEUs()
  { 
      bool hQIXRmbVkS = false;
      bool mIlpOpOlLb = false;
      bool XQpgjjFdPh = false;
      bool EakhsBVFpB = false;
      bool bJLClHsfpf = false;
      bool QYixAQZanh = false;
      bool gyGCOLXEwM = false;
      bool UJwJAOFntb = false;
      bool pZmiRermgc = false;
      bool btRITcCJna = false;
      bool joicLHcYxl = false;
      bool LlfLqHKXji = false;
      bool SjWTkaqnpW = false;
      bool LuATrBpKXK = false;
      bool CTouRoNFQM = false;
      bool ReYEHzROqj = false;
      bool PoiZZPlLTp = false;
      bool QAAZgztbCw = false;
      bool MlWdFgWuMr = false;
      bool iaSmuMkPUB = false;
      string RBDmeeiZsT;
      string GEMtUHoZfG;
      string TxNdtXkrkK;
      string TqntosRuPR;
      string WVViUnDhPT;
      string GDzorTnYsG;
      string sqniAOPRFb;
      string otKOjxbdJF;
      string UCbREPrzBU;
      string FsBJXehmiF;
      string YkcndMskEu;
      string rJPmkpPWdj;
      string WPQjWwrBpE;
      string PnuDgjZmmq;
      string WGtFcucOXh;
      string PLIyiITsQh;
      string UqtAfDNLFA;
      string QbilNPVKGa;
      string SdcHoDfxUY;
      string QfVFWeLtZY;
      if(RBDmeeiZsT == YkcndMskEu){hQIXRmbVkS = true;}
      else if(YkcndMskEu == RBDmeeiZsT){joicLHcYxl = true;}
      if(GEMtUHoZfG == rJPmkpPWdj){mIlpOpOlLb = true;}
      else if(rJPmkpPWdj == GEMtUHoZfG){LlfLqHKXji = true;}
      if(TxNdtXkrkK == WPQjWwrBpE){XQpgjjFdPh = true;}
      else if(WPQjWwrBpE == TxNdtXkrkK){SjWTkaqnpW = true;}
      if(TqntosRuPR == PnuDgjZmmq){EakhsBVFpB = true;}
      else if(PnuDgjZmmq == TqntosRuPR){LuATrBpKXK = true;}
      if(WVViUnDhPT == WGtFcucOXh){bJLClHsfpf = true;}
      else if(WGtFcucOXh == WVViUnDhPT){CTouRoNFQM = true;}
      if(GDzorTnYsG == PLIyiITsQh){QYixAQZanh = true;}
      else if(PLIyiITsQh == GDzorTnYsG){ReYEHzROqj = true;}
      if(sqniAOPRFb == UqtAfDNLFA){gyGCOLXEwM = true;}
      else if(UqtAfDNLFA == sqniAOPRFb){PoiZZPlLTp = true;}
      if(otKOjxbdJF == QbilNPVKGa){UJwJAOFntb = true;}
      if(UCbREPrzBU == SdcHoDfxUY){pZmiRermgc = true;}
      if(FsBJXehmiF == QfVFWeLtZY){btRITcCJna = true;}
      while(QbilNPVKGa == otKOjxbdJF){QAAZgztbCw = true;}
      while(SdcHoDfxUY == SdcHoDfxUY){MlWdFgWuMr = true;}
      while(QfVFWeLtZY == QfVFWeLtZY){iaSmuMkPUB = true;}
      if(hQIXRmbVkS == true){hQIXRmbVkS = false;}
      if(mIlpOpOlLb == true){mIlpOpOlLb = false;}
      if(XQpgjjFdPh == true){XQpgjjFdPh = false;}
      if(EakhsBVFpB == true){EakhsBVFpB = false;}
      if(bJLClHsfpf == true){bJLClHsfpf = false;}
      if(QYixAQZanh == true){QYixAQZanh = false;}
      if(gyGCOLXEwM == true){gyGCOLXEwM = false;}
      if(UJwJAOFntb == true){UJwJAOFntb = false;}
      if(pZmiRermgc == true){pZmiRermgc = false;}
      if(btRITcCJna == true){btRITcCJna = false;}
      if(joicLHcYxl == true){joicLHcYxl = false;}
      if(LlfLqHKXji == true){LlfLqHKXji = false;}
      if(SjWTkaqnpW == true){SjWTkaqnpW = false;}
      if(LuATrBpKXK == true){LuATrBpKXK = false;}
      if(CTouRoNFQM == true){CTouRoNFQM = false;}
      if(ReYEHzROqj == true){ReYEHzROqj = false;}
      if(PoiZZPlLTp == true){PoiZZPlLTp = false;}
      if(QAAZgztbCw == true){QAAZgztbCw = false;}
      if(MlWdFgWuMr == true){MlWdFgWuMr = false;}
      if(iaSmuMkPUB == true){iaSmuMkPUB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXGPREDPJD
{ 
  void inGcQUbXlu()
  { 
      bool KzKdSKPZMP = false;
      bool erGlmguxRz = false;
      bool zuUCWkKaEr = false;
      bool qqqIjPBust = false;
      bool RdrXtgfLWa = false;
      bool UcFnXPeHHg = false;
      bool AoUUXnAyBX = false;
      bool fzDWgUDxHo = false;
      bool EzDdWNlDjU = false;
      bool ksnMtbIXzG = false;
      bool ghKzuVZhGC = false;
      bool MgzRbAlqxK = false;
      bool BxNfmlLqbF = false;
      bool MeyBIWoDhB = false;
      bool mDwgIDsVjt = false;
      bool pQZoEiUdMI = false;
      bool JiFBpgixIF = false;
      bool KhJwWxAfWi = false;
      bool roGhOuEIxY = false;
      bool CLqYqEyuqb = false;
      string gcSzpQOHTD;
      string JaWlFTkJIx;
      string buImeauGTP;
      string BIXmHINDlM;
      string PpERjGGZlf;
      string XtJeCkTeUP;
      string VInEBACidw;
      string FgXuglpqDX;
      string TVUnqHysjV;
      string niiWqHCzPi;
      string DWuoZpVNxQ;
      string tcbwuzmANt;
      string CJzHHWyBEZ;
      string jqaTTxaeNA;
      string kjuTbLHlbq;
      string TClVgtXmhC;
      string rUJXgDBHbx;
      string YIlMIROefu;
      string PLZMFhEFmZ;
      string ZmxKHQaWmX;
      if(gcSzpQOHTD == DWuoZpVNxQ){KzKdSKPZMP = true;}
      else if(DWuoZpVNxQ == gcSzpQOHTD){ghKzuVZhGC = true;}
      if(JaWlFTkJIx == tcbwuzmANt){erGlmguxRz = true;}
      else if(tcbwuzmANt == JaWlFTkJIx){MgzRbAlqxK = true;}
      if(buImeauGTP == CJzHHWyBEZ){zuUCWkKaEr = true;}
      else if(CJzHHWyBEZ == buImeauGTP){BxNfmlLqbF = true;}
      if(BIXmHINDlM == jqaTTxaeNA){qqqIjPBust = true;}
      else if(jqaTTxaeNA == BIXmHINDlM){MeyBIWoDhB = true;}
      if(PpERjGGZlf == kjuTbLHlbq){RdrXtgfLWa = true;}
      else if(kjuTbLHlbq == PpERjGGZlf){mDwgIDsVjt = true;}
      if(XtJeCkTeUP == TClVgtXmhC){UcFnXPeHHg = true;}
      else if(TClVgtXmhC == XtJeCkTeUP){pQZoEiUdMI = true;}
      if(VInEBACidw == rUJXgDBHbx){AoUUXnAyBX = true;}
      else if(rUJXgDBHbx == VInEBACidw){JiFBpgixIF = true;}
      if(FgXuglpqDX == YIlMIROefu){fzDWgUDxHo = true;}
      if(TVUnqHysjV == PLZMFhEFmZ){EzDdWNlDjU = true;}
      if(niiWqHCzPi == ZmxKHQaWmX){ksnMtbIXzG = true;}
      while(YIlMIROefu == FgXuglpqDX){KhJwWxAfWi = true;}
      while(PLZMFhEFmZ == PLZMFhEFmZ){roGhOuEIxY = true;}
      while(ZmxKHQaWmX == ZmxKHQaWmX){CLqYqEyuqb = true;}
      if(KzKdSKPZMP == true){KzKdSKPZMP = false;}
      if(erGlmguxRz == true){erGlmguxRz = false;}
      if(zuUCWkKaEr == true){zuUCWkKaEr = false;}
      if(qqqIjPBust == true){qqqIjPBust = false;}
      if(RdrXtgfLWa == true){RdrXtgfLWa = false;}
      if(UcFnXPeHHg == true){UcFnXPeHHg = false;}
      if(AoUUXnAyBX == true){AoUUXnAyBX = false;}
      if(fzDWgUDxHo == true){fzDWgUDxHo = false;}
      if(EzDdWNlDjU == true){EzDdWNlDjU = false;}
      if(ksnMtbIXzG == true){ksnMtbIXzG = false;}
      if(ghKzuVZhGC == true){ghKzuVZhGC = false;}
      if(MgzRbAlqxK == true){MgzRbAlqxK = false;}
      if(BxNfmlLqbF == true){BxNfmlLqbF = false;}
      if(MeyBIWoDhB == true){MeyBIWoDhB = false;}
      if(mDwgIDsVjt == true){mDwgIDsVjt = false;}
      if(pQZoEiUdMI == true){pQZoEiUdMI = false;}
      if(JiFBpgixIF == true){JiFBpgixIF = false;}
      if(KhJwWxAfWi == true){KhJwWxAfWi = false;}
      if(roGhOuEIxY == true){roGhOuEIxY = false;}
      if(CLqYqEyuqb == true){CLqYqEyuqb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWJGBDLCUC
{ 
  void CtAqmmoLPC()
  { 
      bool poKPyGxgmH = false;
      bool zaGpTnryoF = false;
      bool ONpLpIgtyy = false;
      bool dITgFuGcqu = false;
      bool HEAgxqbmMD = false;
      bool xMJSEcyzZo = false;
      bool ZDhodpGYjX = false;
      bool hPGsyJMJNz = false;
      bool gthuBQyAcc = false;
      bool wGDCVDWLDG = false;
      bool jDCnUhFPUt = false;
      bool QokZIeUmmM = false;
      bool rGwHbbLEXt = false;
      bool mAGHPcqtZT = false;
      bool KieiLHVcsp = false;
      bool iiYpOcHuLs = false;
      bool VAraGPhdKf = false;
      bool maMTBIaMuU = false;
      bool FhLgLDbPrl = false;
      bool VuhgxKpEbu = false;
      string xSLsuqfxfJ;
      string HaSPjNaZYQ;
      string zOsXTWsQrB;
      string PuYUOkYHpU;
      string GnqkzIqcZy;
      string KlZWzhZnYY;
      string xPEesLBxBz;
      string oTiDKLWHXL;
      string eQpspdVCVf;
      string KjhRWpiMqm;
      string GtbaJqCVLm;
      string LRPNsgYKoP;
      string pzaUnEkRfT;
      string cJQkEkoOjy;
      string aAqiUrTTXp;
      string RXXbxHSGlE;
      string GkoqKBBeII;
      string qKZpnoHrAw;
      string kRspCElnnx;
      string RhcfroLzYS;
      if(xSLsuqfxfJ == GtbaJqCVLm){poKPyGxgmH = true;}
      else if(GtbaJqCVLm == xSLsuqfxfJ){jDCnUhFPUt = true;}
      if(HaSPjNaZYQ == LRPNsgYKoP){zaGpTnryoF = true;}
      else if(LRPNsgYKoP == HaSPjNaZYQ){QokZIeUmmM = true;}
      if(zOsXTWsQrB == pzaUnEkRfT){ONpLpIgtyy = true;}
      else if(pzaUnEkRfT == zOsXTWsQrB){rGwHbbLEXt = true;}
      if(PuYUOkYHpU == cJQkEkoOjy){dITgFuGcqu = true;}
      else if(cJQkEkoOjy == PuYUOkYHpU){mAGHPcqtZT = true;}
      if(GnqkzIqcZy == aAqiUrTTXp){HEAgxqbmMD = true;}
      else if(aAqiUrTTXp == GnqkzIqcZy){KieiLHVcsp = true;}
      if(KlZWzhZnYY == RXXbxHSGlE){xMJSEcyzZo = true;}
      else if(RXXbxHSGlE == KlZWzhZnYY){iiYpOcHuLs = true;}
      if(xPEesLBxBz == GkoqKBBeII){ZDhodpGYjX = true;}
      else if(GkoqKBBeII == xPEesLBxBz){VAraGPhdKf = true;}
      if(oTiDKLWHXL == qKZpnoHrAw){hPGsyJMJNz = true;}
      if(eQpspdVCVf == kRspCElnnx){gthuBQyAcc = true;}
      if(KjhRWpiMqm == RhcfroLzYS){wGDCVDWLDG = true;}
      while(qKZpnoHrAw == oTiDKLWHXL){maMTBIaMuU = true;}
      while(kRspCElnnx == kRspCElnnx){FhLgLDbPrl = true;}
      while(RhcfroLzYS == RhcfroLzYS){VuhgxKpEbu = true;}
      if(poKPyGxgmH == true){poKPyGxgmH = false;}
      if(zaGpTnryoF == true){zaGpTnryoF = false;}
      if(ONpLpIgtyy == true){ONpLpIgtyy = false;}
      if(dITgFuGcqu == true){dITgFuGcqu = false;}
      if(HEAgxqbmMD == true){HEAgxqbmMD = false;}
      if(xMJSEcyzZo == true){xMJSEcyzZo = false;}
      if(ZDhodpGYjX == true){ZDhodpGYjX = false;}
      if(hPGsyJMJNz == true){hPGsyJMJNz = false;}
      if(gthuBQyAcc == true){gthuBQyAcc = false;}
      if(wGDCVDWLDG == true){wGDCVDWLDG = false;}
      if(jDCnUhFPUt == true){jDCnUhFPUt = false;}
      if(QokZIeUmmM == true){QokZIeUmmM = false;}
      if(rGwHbbLEXt == true){rGwHbbLEXt = false;}
      if(mAGHPcqtZT == true){mAGHPcqtZT = false;}
      if(KieiLHVcsp == true){KieiLHVcsp = false;}
      if(iiYpOcHuLs == true){iiYpOcHuLs = false;}
      if(VAraGPhdKf == true){VAraGPhdKf = false;}
      if(maMTBIaMuU == true){maMTBIaMuU = false;}
      if(FhLgLDbPrl == true){FhLgLDbPrl = false;}
      if(VuhgxKpEbu == true){VuhgxKpEbu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDSXFWFFZL
{ 
  void WHxMKszMVC()
  { 
      bool juYMxqdxlI = false;
      bool qWZxyUlgVs = false;
      bool DilHAVYshq = false;
      bool CElRNPLzDQ = false;
      bool PKTdPqMCtc = false;
      bool wYZBFBIRLa = false;
      bool RkPuGljIji = false;
      bool ImdEcrOIqJ = false;
      bool IWyEucekLM = false;
      bool GtmbyeuYWc = false;
      bool GESLTItUXN = false;
      bool lAZCRulKAc = false;
      bool HyxXcOzCFx = false;
      bool xpkOCEEmkl = false;
      bool iJNyZFTjJC = false;
      bool sjYsUIHtiF = false;
      bool IrPaPwOLAN = false;
      bool qzZNtykzxW = false;
      bool uPrCEMRqst = false;
      bool wJDfcqtmhd = false;
      string ViBLOsXhzq;
      string znljkSydCb;
      string zZmFiuGnDi;
      string MalsQeradq;
      string TibzmTKRZO;
      string BoyKNwwubS;
      string midQeYBsSG;
      string aXAKIPxmSP;
      string jnOogWbbeU;
      string hwzKEjFLUO;
      string RRzTmdonCy;
      string yIcLhyTniH;
      string wZNxXdXoGX;
      string KlSEySouCD;
      string hnZgVZTmcG;
      string PQcMRqDBuI;
      string FzgdmMoYNP;
      string JYleZIAgay;
      string KkMAItIGlG;
      string OmzsxiGutJ;
      if(ViBLOsXhzq == RRzTmdonCy){juYMxqdxlI = true;}
      else if(RRzTmdonCy == ViBLOsXhzq){GESLTItUXN = true;}
      if(znljkSydCb == yIcLhyTniH){qWZxyUlgVs = true;}
      else if(yIcLhyTniH == znljkSydCb){lAZCRulKAc = true;}
      if(zZmFiuGnDi == wZNxXdXoGX){DilHAVYshq = true;}
      else if(wZNxXdXoGX == zZmFiuGnDi){HyxXcOzCFx = true;}
      if(MalsQeradq == KlSEySouCD){CElRNPLzDQ = true;}
      else if(KlSEySouCD == MalsQeradq){xpkOCEEmkl = true;}
      if(TibzmTKRZO == hnZgVZTmcG){PKTdPqMCtc = true;}
      else if(hnZgVZTmcG == TibzmTKRZO){iJNyZFTjJC = true;}
      if(BoyKNwwubS == PQcMRqDBuI){wYZBFBIRLa = true;}
      else if(PQcMRqDBuI == BoyKNwwubS){sjYsUIHtiF = true;}
      if(midQeYBsSG == FzgdmMoYNP){RkPuGljIji = true;}
      else if(FzgdmMoYNP == midQeYBsSG){IrPaPwOLAN = true;}
      if(aXAKIPxmSP == JYleZIAgay){ImdEcrOIqJ = true;}
      if(jnOogWbbeU == KkMAItIGlG){IWyEucekLM = true;}
      if(hwzKEjFLUO == OmzsxiGutJ){GtmbyeuYWc = true;}
      while(JYleZIAgay == aXAKIPxmSP){qzZNtykzxW = true;}
      while(KkMAItIGlG == KkMAItIGlG){uPrCEMRqst = true;}
      while(OmzsxiGutJ == OmzsxiGutJ){wJDfcqtmhd = true;}
      if(juYMxqdxlI == true){juYMxqdxlI = false;}
      if(qWZxyUlgVs == true){qWZxyUlgVs = false;}
      if(DilHAVYshq == true){DilHAVYshq = false;}
      if(CElRNPLzDQ == true){CElRNPLzDQ = false;}
      if(PKTdPqMCtc == true){PKTdPqMCtc = false;}
      if(wYZBFBIRLa == true){wYZBFBIRLa = false;}
      if(RkPuGljIji == true){RkPuGljIji = false;}
      if(ImdEcrOIqJ == true){ImdEcrOIqJ = false;}
      if(IWyEucekLM == true){IWyEucekLM = false;}
      if(GtmbyeuYWc == true){GtmbyeuYWc = false;}
      if(GESLTItUXN == true){GESLTItUXN = false;}
      if(lAZCRulKAc == true){lAZCRulKAc = false;}
      if(HyxXcOzCFx == true){HyxXcOzCFx = false;}
      if(xpkOCEEmkl == true){xpkOCEEmkl = false;}
      if(iJNyZFTjJC == true){iJNyZFTjJC = false;}
      if(sjYsUIHtiF == true){sjYsUIHtiF = false;}
      if(IrPaPwOLAN == true){IrPaPwOLAN = false;}
      if(qzZNtykzxW == true){qzZNtykzxW = false;}
      if(uPrCEMRqst == true){uPrCEMRqst = false;}
      if(wJDfcqtmhd == true){wJDfcqtmhd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSFPBTJXJY
{ 
  void UCTqCEkhMF()
  { 
      bool GctoJepema = false;
      bool bmVuGcowaP = false;
      bool xuDjbBWcQm = false;
      bool YwRbgMxINe = false;
      bool kVAlqQOIWx = false;
      bool MqxpJKZKMI = false;
      bool INNzBfVsOt = false;
      bool fghuebuRrL = false;
      bool mOGSZgzaSW = false;
      bool lmwEWXHAjL = false;
      bool tUtbRfJBLh = false;
      bool OIRBVtHtZT = false;
      bool ftaqHrkcXH = false;
      bool TuggRRTdBt = false;
      bool XxPkHdVtic = false;
      bool QMaPezsCUY = false;
      bool ufdDNTajjD = false;
      bool Zcsewiepic = false;
      bool WptuqHURBR = false;
      bool YQIbzrTLWn = false;
      string xYGUsDATTR;
      string ZAJBWkipRg;
      string SpFdKEtggY;
      string oOIcjGobFd;
      string pQGjTSKLdb;
      string RrXtRGTcKn;
      string JSlucLrfRQ;
      string uGjmpCjVKq;
      string siCFGxqNLc;
      string mMRQUXdLGI;
      string aesNfKHjEO;
      string WxSTuZQgne;
      string TdTodioTRR;
      string XXOBPOooZw;
      string pGJwFosxVt;
      string HxWbnwKEjw;
      string UnSlqyiQDf;
      string kbGroMUWin;
      string oqyWKaAmNT;
      string DjEdaCnXFG;
      if(xYGUsDATTR == aesNfKHjEO){GctoJepema = true;}
      else if(aesNfKHjEO == xYGUsDATTR){tUtbRfJBLh = true;}
      if(ZAJBWkipRg == WxSTuZQgne){bmVuGcowaP = true;}
      else if(WxSTuZQgne == ZAJBWkipRg){OIRBVtHtZT = true;}
      if(SpFdKEtggY == TdTodioTRR){xuDjbBWcQm = true;}
      else if(TdTodioTRR == SpFdKEtggY){ftaqHrkcXH = true;}
      if(oOIcjGobFd == XXOBPOooZw){YwRbgMxINe = true;}
      else if(XXOBPOooZw == oOIcjGobFd){TuggRRTdBt = true;}
      if(pQGjTSKLdb == pGJwFosxVt){kVAlqQOIWx = true;}
      else if(pGJwFosxVt == pQGjTSKLdb){XxPkHdVtic = true;}
      if(RrXtRGTcKn == HxWbnwKEjw){MqxpJKZKMI = true;}
      else if(HxWbnwKEjw == RrXtRGTcKn){QMaPezsCUY = true;}
      if(JSlucLrfRQ == UnSlqyiQDf){INNzBfVsOt = true;}
      else if(UnSlqyiQDf == JSlucLrfRQ){ufdDNTajjD = true;}
      if(uGjmpCjVKq == kbGroMUWin){fghuebuRrL = true;}
      if(siCFGxqNLc == oqyWKaAmNT){mOGSZgzaSW = true;}
      if(mMRQUXdLGI == DjEdaCnXFG){lmwEWXHAjL = true;}
      while(kbGroMUWin == uGjmpCjVKq){Zcsewiepic = true;}
      while(oqyWKaAmNT == oqyWKaAmNT){WptuqHURBR = true;}
      while(DjEdaCnXFG == DjEdaCnXFG){YQIbzrTLWn = true;}
      if(GctoJepema == true){GctoJepema = false;}
      if(bmVuGcowaP == true){bmVuGcowaP = false;}
      if(xuDjbBWcQm == true){xuDjbBWcQm = false;}
      if(YwRbgMxINe == true){YwRbgMxINe = false;}
      if(kVAlqQOIWx == true){kVAlqQOIWx = false;}
      if(MqxpJKZKMI == true){MqxpJKZKMI = false;}
      if(INNzBfVsOt == true){INNzBfVsOt = false;}
      if(fghuebuRrL == true){fghuebuRrL = false;}
      if(mOGSZgzaSW == true){mOGSZgzaSW = false;}
      if(lmwEWXHAjL == true){lmwEWXHAjL = false;}
      if(tUtbRfJBLh == true){tUtbRfJBLh = false;}
      if(OIRBVtHtZT == true){OIRBVtHtZT = false;}
      if(ftaqHrkcXH == true){ftaqHrkcXH = false;}
      if(TuggRRTdBt == true){TuggRRTdBt = false;}
      if(XxPkHdVtic == true){XxPkHdVtic = false;}
      if(QMaPezsCUY == true){QMaPezsCUY = false;}
      if(ufdDNTajjD == true){ufdDNTajjD = false;}
      if(Zcsewiepic == true){Zcsewiepic = false;}
      if(WptuqHURBR == true){WptuqHURBR = false;}
      if(YQIbzrTLWn == true){YQIbzrTLWn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEKAMXXJOZ
{ 
  void qPrAcEORjA()
  { 
      bool lsPmcGVaSy = false;
      bool IDKxRScEcF = false;
      bool HclJmQKcwu = false;
      bool ghFtHxiQXN = false;
      bool soHlPONFrI = false;
      bool SiAaMJHFAL = false;
      bool wrdWRZyQoT = false;
      bool jLgOMSVzsX = false;
      bool DFjncxgdgy = false;
      bool pdQLRAKjUp = false;
      bool QwPYXGBkOt = false;
      bool nHLbIpHosT = false;
      bool sTjqcGuUxL = false;
      bool HkeDHGoKPW = false;
      bool uuOmKhRnCa = false;
      bool rUpBwwMYwR = false;
      bool KgnDmCcHUC = false;
      bool BwYWXxExgu = false;
      bool nGRVSltcGK = false;
      bool sPOyLOHLAH = false;
      string rGFcmIZmVF;
      string CVCgdtSDAW;
      string sYJxEpqzxt;
      string hUUXxWxwBY;
      string DFryNGGOfN;
      string kdBGeSwIXw;
      string RapaWgAejH;
      string wVBbSmfKix;
      string jcSiJETOrd;
      string ZoYFHcPRbf;
      string FbeYQPcZmq;
      string lkYZMnHGRS;
      string NllFhHxwTp;
      string XOiCrHytSs;
      string bsaAqnPyrS;
      string UJzJSToYpI;
      string RgFxTWCVhF;
      string pNmXpULlNs;
      string qzDAUOPZjY;
      string RYDJbuncfT;
      if(rGFcmIZmVF == FbeYQPcZmq){lsPmcGVaSy = true;}
      else if(FbeYQPcZmq == rGFcmIZmVF){QwPYXGBkOt = true;}
      if(CVCgdtSDAW == lkYZMnHGRS){IDKxRScEcF = true;}
      else if(lkYZMnHGRS == CVCgdtSDAW){nHLbIpHosT = true;}
      if(sYJxEpqzxt == NllFhHxwTp){HclJmQKcwu = true;}
      else if(NllFhHxwTp == sYJxEpqzxt){sTjqcGuUxL = true;}
      if(hUUXxWxwBY == XOiCrHytSs){ghFtHxiQXN = true;}
      else if(XOiCrHytSs == hUUXxWxwBY){HkeDHGoKPW = true;}
      if(DFryNGGOfN == bsaAqnPyrS){soHlPONFrI = true;}
      else if(bsaAqnPyrS == DFryNGGOfN){uuOmKhRnCa = true;}
      if(kdBGeSwIXw == UJzJSToYpI){SiAaMJHFAL = true;}
      else if(UJzJSToYpI == kdBGeSwIXw){rUpBwwMYwR = true;}
      if(RapaWgAejH == RgFxTWCVhF){wrdWRZyQoT = true;}
      else if(RgFxTWCVhF == RapaWgAejH){KgnDmCcHUC = true;}
      if(wVBbSmfKix == pNmXpULlNs){jLgOMSVzsX = true;}
      if(jcSiJETOrd == qzDAUOPZjY){DFjncxgdgy = true;}
      if(ZoYFHcPRbf == RYDJbuncfT){pdQLRAKjUp = true;}
      while(pNmXpULlNs == wVBbSmfKix){BwYWXxExgu = true;}
      while(qzDAUOPZjY == qzDAUOPZjY){nGRVSltcGK = true;}
      while(RYDJbuncfT == RYDJbuncfT){sPOyLOHLAH = true;}
      if(lsPmcGVaSy == true){lsPmcGVaSy = false;}
      if(IDKxRScEcF == true){IDKxRScEcF = false;}
      if(HclJmQKcwu == true){HclJmQKcwu = false;}
      if(ghFtHxiQXN == true){ghFtHxiQXN = false;}
      if(soHlPONFrI == true){soHlPONFrI = false;}
      if(SiAaMJHFAL == true){SiAaMJHFAL = false;}
      if(wrdWRZyQoT == true){wrdWRZyQoT = false;}
      if(jLgOMSVzsX == true){jLgOMSVzsX = false;}
      if(DFjncxgdgy == true){DFjncxgdgy = false;}
      if(pdQLRAKjUp == true){pdQLRAKjUp = false;}
      if(QwPYXGBkOt == true){QwPYXGBkOt = false;}
      if(nHLbIpHosT == true){nHLbIpHosT = false;}
      if(sTjqcGuUxL == true){sTjqcGuUxL = false;}
      if(HkeDHGoKPW == true){HkeDHGoKPW = false;}
      if(uuOmKhRnCa == true){uuOmKhRnCa = false;}
      if(rUpBwwMYwR == true){rUpBwwMYwR = false;}
      if(KgnDmCcHUC == true){KgnDmCcHUC = false;}
      if(BwYWXxExgu == true){BwYWXxExgu = false;}
      if(nGRVSltcGK == true){nGRVSltcGK = false;}
      if(sPOyLOHLAH == true){sPOyLOHLAH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BDKNTPWHDB
{ 
  void BsrQqnPqJl()
  { 
      bool UOVhInnRSP = false;
      bool XdGNSPAeVw = false;
      bool opJihzoBGm = false;
      bool aYHrVXtast = false;
      bool TNIfGTNrUt = false;
      bool WqnAJeEmzJ = false;
      bool zlKfozVNqt = false;
      bool VZkbcbhcbO = false;
      bool lwgLPikGip = false;
      bool TGajuhCbqH = false;
      bool xzAZYxGLXg = false;
      bool waKkXCEyPG = false;
      bool OPdBaOzBgu = false;
      bool YGlURlwGmS = false;
      bool bYiBsrwoLs = false;
      bool cDLjshVzzJ = false;
      bool yFebIpnoTk = false;
      bool FxLxdofbHi = false;
      bool SJomRVtBbj = false;
      bool QwHdUWsGsC = false;
      string WppVtMMqZp;
      string kzYKrJNEPt;
      string rfuEeKAOEr;
      string mTPatEUbIY;
      string mwYVfnnYVA;
      string TaDdjpulqi;
      string LylgCRixPm;
      string olwqHuGYXp;
      string WarEYLPkpD;
      string JhkZMoKrTO;
      string EpJhLgeLWo;
      string jWOAMjFhIp;
      string BxGLdGBVeR;
      string jOEIlgRKrq;
      string fEOBTmTjNb;
      string icicMGiyEF;
      string fJgEEURFOe;
      string SuoRJxiFqq;
      string lQIChHeaue;
      string xTFmKWWJxy;
      if(WppVtMMqZp == EpJhLgeLWo){UOVhInnRSP = true;}
      else if(EpJhLgeLWo == WppVtMMqZp){xzAZYxGLXg = true;}
      if(kzYKrJNEPt == jWOAMjFhIp){XdGNSPAeVw = true;}
      else if(jWOAMjFhIp == kzYKrJNEPt){waKkXCEyPG = true;}
      if(rfuEeKAOEr == BxGLdGBVeR){opJihzoBGm = true;}
      else if(BxGLdGBVeR == rfuEeKAOEr){OPdBaOzBgu = true;}
      if(mTPatEUbIY == jOEIlgRKrq){aYHrVXtast = true;}
      else if(jOEIlgRKrq == mTPatEUbIY){YGlURlwGmS = true;}
      if(mwYVfnnYVA == fEOBTmTjNb){TNIfGTNrUt = true;}
      else if(fEOBTmTjNb == mwYVfnnYVA){bYiBsrwoLs = true;}
      if(TaDdjpulqi == icicMGiyEF){WqnAJeEmzJ = true;}
      else if(icicMGiyEF == TaDdjpulqi){cDLjshVzzJ = true;}
      if(LylgCRixPm == fJgEEURFOe){zlKfozVNqt = true;}
      else if(fJgEEURFOe == LylgCRixPm){yFebIpnoTk = true;}
      if(olwqHuGYXp == SuoRJxiFqq){VZkbcbhcbO = true;}
      if(WarEYLPkpD == lQIChHeaue){lwgLPikGip = true;}
      if(JhkZMoKrTO == xTFmKWWJxy){TGajuhCbqH = true;}
      while(SuoRJxiFqq == olwqHuGYXp){FxLxdofbHi = true;}
      while(lQIChHeaue == lQIChHeaue){SJomRVtBbj = true;}
      while(xTFmKWWJxy == xTFmKWWJxy){QwHdUWsGsC = true;}
      if(UOVhInnRSP == true){UOVhInnRSP = false;}
      if(XdGNSPAeVw == true){XdGNSPAeVw = false;}
      if(opJihzoBGm == true){opJihzoBGm = false;}
      if(aYHrVXtast == true){aYHrVXtast = false;}
      if(TNIfGTNrUt == true){TNIfGTNrUt = false;}
      if(WqnAJeEmzJ == true){WqnAJeEmzJ = false;}
      if(zlKfozVNqt == true){zlKfozVNqt = false;}
      if(VZkbcbhcbO == true){VZkbcbhcbO = false;}
      if(lwgLPikGip == true){lwgLPikGip = false;}
      if(TGajuhCbqH == true){TGajuhCbqH = false;}
      if(xzAZYxGLXg == true){xzAZYxGLXg = false;}
      if(waKkXCEyPG == true){waKkXCEyPG = false;}
      if(OPdBaOzBgu == true){OPdBaOzBgu = false;}
      if(YGlURlwGmS == true){YGlURlwGmS = false;}
      if(bYiBsrwoLs == true){bYiBsrwoLs = false;}
      if(cDLjshVzzJ == true){cDLjshVzzJ = false;}
      if(yFebIpnoTk == true){yFebIpnoTk = false;}
      if(FxLxdofbHi == true){FxLxdofbHi = false;}
      if(SJomRVtBbj == true){SJomRVtBbj = false;}
      if(QwHdUWsGsC == true){QwHdUWsGsC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLIWULDMEL
{ 
  void zUBJRVTDXN()
  { 
      bool iwgMjWKxbZ = false;
      bool dLkUtzjDSK = false;
      bool VBdCIalTqa = false;
      bool NxtzoNirZb = false;
      bool gTbGPBqfGw = false;
      bool dghRqhReDJ = false;
      bool jqGBMgQkff = false;
      bool QrcqdCYXlG = false;
      bool iFNuwfOcIH = false;
      bool wDnQqpNZti = false;
      bool kFAaflDpnn = false;
      bool ItrwadcKFf = false;
      bool RmbYiMDMAn = false;
      bool nydDVcFmPK = false;
      bool bXoTyCLqpM = false;
      bool MCUNQydbqS = false;
      bool hqpzzJQnax = false;
      bool XpuuEsyIZg = false;
      bool BMWmaldPlX = false;
      bool zduwbkhoTn = false;
      string EaKBYNYoiW;
      string FgQOCHRnuj;
      string jgRPTZzmnR;
      string xrWIMYRczf;
      string fGyklDrNjM;
      string yQdcDWIthy;
      string OlBRZNKHCc;
      string ponPDcigdP;
      string gkCbTfOsFo;
      string PXuAQtFgKY;
      string skLGWJcNZZ;
      string nbQRRciZxs;
      string zQCNMRsmyI;
      string XBVFVuZuEK;
      string DASeAnHcim;
      string KfjRYbhxtE;
      string PoORCmFKuV;
      string CnUlozyWMY;
      string KPEKyrQEfs;
      string MbBAuOkBbM;
      if(EaKBYNYoiW == skLGWJcNZZ){iwgMjWKxbZ = true;}
      else if(skLGWJcNZZ == EaKBYNYoiW){kFAaflDpnn = true;}
      if(FgQOCHRnuj == nbQRRciZxs){dLkUtzjDSK = true;}
      else if(nbQRRciZxs == FgQOCHRnuj){ItrwadcKFf = true;}
      if(jgRPTZzmnR == zQCNMRsmyI){VBdCIalTqa = true;}
      else if(zQCNMRsmyI == jgRPTZzmnR){RmbYiMDMAn = true;}
      if(xrWIMYRczf == XBVFVuZuEK){NxtzoNirZb = true;}
      else if(XBVFVuZuEK == xrWIMYRczf){nydDVcFmPK = true;}
      if(fGyklDrNjM == DASeAnHcim){gTbGPBqfGw = true;}
      else if(DASeAnHcim == fGyklDrNjM){bXoTyCLqpM = true;}
      if(yQdcDWIthy == KfjRYbhxtE){dghRqhReDJ = true;}
      else if(KfjRYbhxtE == yQdcDWIthy){MCUNQydbqS = true;}
      if(OlBRZNKHCc == PoORCmFKuV){jqGBMgQkff = true;}
      else if(PoORCmFKuV == OlBRZNKHCc){hqpzzJQnax = true;}
      if(ponPDcigdP == CnUlozyWMY){QrcqdCYXlG = true;}
      if(gkCbTfOsFo == KPEKyrQEfs){iFNuwfOcIH = true;}
      if(PXuAQtFgKY == MbBAuOkBbM){wDnQqpNZti = true;}
      while(CnUlozyWMY == ponPDcigdP){XpuuEsyIZg = true;}
      while(KPEKyrQEfs == KPEKyrQEfs){BMWmaldPlX = true;}
      while(MbBAuOkBbM == MbBAuOkBbM){zduwbkhoTn = true;}
      if(iwgMjWKxbZ == true){iwgMjWKxbZ = false;}
      if(dLkUtzjDSK == true){dLkUtzjDSK = false;}
      if(VBdCIalTqa == true){VBdCIalTqa = false;}
      if(NxtzoNirZb == true){NxtzoNirZb = false;}
      if(gTbGPBqfGw == true){gTbGPBqfGw = false;}
      if(dghRqhReDJ == true){dghRqhReDJ = false;}
      if(jqGBMgQkff == true){jqGBMgQkff = false;}
      if(QrcqdCYXlG == true){QrcqdCYXlG = false;}
      if(iFNuwfOcIH == true){iFNuwfOcIH = false;}
      if(wDnQqpNZti == true){wDnQqpNZti = false;}
      if(kFAaflDpnn == true){kFAaflDpnn = false;}
      if(ItrwadcKFf == true){ItrwadcKFf = false;}
      if(RmbYiMDMAn == true){RmbYiMDMAn = false;}
      if(nydDVcFmPK == true){nydDVcFmPK = false;}
      if(bXoTyCLqpM == true){bXoTyCLqpM = false;}
      if(MCUNQydbqS == true){MCUNQydbqS = false;}
      if(hqpzzJQnax == true){hqpzzJQnax = false;}
      if(XpuuEsyIZg == true){XpuuEsyIZg = false;}
      if(BMWmaldPlX == true){BMWmaldPlX = false;}
      if(zduwbkhoTn == true){zduwbkhoTn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQQHMTCTTO
{ 
  void xdVPzpctjK()
  { 
      bool DzByGYRnMR = false;
      bool lugzorlwGD = false;
      bool gTTXCqgrjT = false;
      bool OKKCrPDrOx = false;
      bool zsElhQomjd = false;
      bool xqEmEjfcwP = false;
      bool qZErCajeHZ = false;
      bool nthJDmPgol = false;
      bool CtHFVXGXyI = false;
      bool jZuyFZoLiG = false;
      bool fJfKpCJtiQ = false;
      bool UynKNxRzVe = false;
      bool ULfypOyiEd = false;
      bool yDxiFrOxOT = false;
      bool OLngnklkkH = false;
      bool HooElUcgTa = false;
      bool DZpFSQAEEU = false;
      bool iTjCQJXzKE = false;
      bool bNxwVIOsxk = false;
      bool OhcnPnUiNW = false;
      string BjCVtuFpTX;
      string IZRLZctFua;
      string cLFCEJomXb;
      string NljcfjUfSf;
      string PyNqzIunWA;
      string KTXDzoeAQj;
      string GSSqKVpoep;
      string IOlPLeyNCu;
      string NAPWQtNfdq;
      string FUOiZweVgc;
      string SGJgrwgIrT;
      string qQxUVFDwaQ;
      string IKKnjmzDpO;
      string zcgYcHqieT;
      string MFnJznXtMU;
      string sitPUIuVwE;
      string xcRcTOjXrO;
      string NTRGDCVAnw;
      string PFpVVQhQEU;
      string LVmZWjmLpk;
      if(BjCVtuFpTX == SGJgrwgIrT){DzByGYRnMR = true;}
      else if(SGJgrwgIrT == BjCVtuFpTX){fJfKpCJtiQ = true;}
      if(IZRLZctFua == qQxUVFDwaQ){lugzorlwGD = true;}
      else if(qQxUVFDwaQ == IZRLZctFua){UynKNxRzVe = true;}
      if(cLFCEJomXb == IKKnjmzDpO){gTTXCqgrjT = true;}
      else if(IKKnjmzDpO == cLFCEJomXb){ULfypOyiEd = true;}
      if(NljcfjUfSf == zcgYcHqieT){OKKCrPDrOx = true;}
      else if(zcgYcHqieT == NljcfjUfSf){yDxiFrOxOT = true;}
      if(PyNqzIunWA == MFnJznXtMU){zsElhQomjd = true;}
      else if(MFnJznXtMU == PyNqzIunWA){OLngnklkkH = true;}
      if(KTXDzoeAQj == sitPUIuVwE){xqEmEjfcwP = true;}
      else if(sitPUIuVwE == KTXDzoeAQj){HooElUcgTa = true;}
      if(GSSqKVpoep == xcRcTOjXrO){qZErCajeHZ = true;}
      else if(xcRcTOjXrO == GSSqKVpoep){DZpFSQAEEU = true;}
      if(IOlPLeyNCu == NTRGDCVAnw){nthJDmPgol = true;}
      if(NAPWQtNfdq == PFpVVQhQEU){CtHFVXGXyI = true;}
      if(FUOiZweVgc == LVmZWjmLpk){jZuyFZoLiG = true;}
      while(NTRGDCVAnw == IOlPLeyNCu){iTjCQJXzKE = true;}
      while(PFpVVQhQEU == PFpVVQhQEU){bNxwVIOsxk = true;}
      while(LVmZWjmLpk == LVmZWjmLpk){OhcnPnUiNW = true;}
      if(DzByGYRnMR == true){DzByGYRnMR = false;}
      if(lugzorlwGD == true){lugzorlwGD = false;}
      if(gTTXCqgrjT == true){gTTXCqgrjT = false;}
      if(OKKCrPDrOx == true){OKKCrPDrOx = false;}
      if(zsElhQomjd == true){zsElhQomjd = false;}
      if(xqEmEjfcwP == true){xqEmEjfcwP = false;}
      if(qZErCajeHZ == true){qZErCajeHZ = false;}
      if(nthJDmPgol == true){nthJDmPgol = false;}
      if(CtHFVXGXyI == true){CtHFVXGXyI = false;}
      if(jZuyFZoLiG == true){jZuyFZoLiG = false;}
      if(fJfKpCJtiQ == true){fJfKpCJtiQ = false;}
      if(UynKNxRzVe == true){UynKNxRzVe = false;}
      if(ULfypOyiEd == true){ULfypOyiEd = false;}
      if(yDxiFrOxOT == true){yDxiFrOxOT = false;}
      if(OLngnklkkH == true){OLngnklkkH = false;}
      if(HooElUcgTa == true){HooElUcgTa = false;}
      if(DZpFSQAEEU == true){DZpFSQAEEU = false;}
      if(iTjCQJXzKE == true){iTjCQJXzKE = false;}
      if(bNxwVIOsxk == true){bNxwVIOsxk = false;}
      if(OhcnPnUiNW == true){OhcnPnUiNW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFIYJNGCQV
{ 
  void txWnMBRYRG()
  { 
      bool jgNWSypxFV = false;
      bool qJoBkfrUVA = false;
      bool iHAEcdCYQO = false;
      bool lQjZUPumjx = false;
      bool wHbZMMGgCV = false;
      bool LuQnqbgItn = false;
      bool wRfpiZYOfU = false;
      bool jEjXEafZrQ = false;
      bool XUVuCpzwir = false;
      bool imswBdbkpl = false;
      bool mqBhlHLsiP = false;
      bool wGQcPaukms = false;
      bool acfmkxKmWZ = false;
      bool ztjFdfTmIu = false;
      bool dGNSwcVQfZ = false;
      bool ipxwLJKNxn = false;
      bool wYVIQBVKzi = false;
      bool HHbrOTPNqI = false;
      bool btGxqJwmtT = false;
      bool UFpUyFjECt = false;
      string NjpfkrUXPL;
      string YKPafKsmKF;
      string XCesVmnRJp;
      string pauHkcpkbJ;
      string NyDWLStwpd;
      string cwTqCKFxJy;
      string EDNZVxOHpD;
      string UHKAqZzIgC;
      string rrbfNsHEFZ;
      string WsbcEKkcBN;
      string ElFlJUkTzc;
      string KxPGFMahLb;
      string pJCPfaehug;
      string oWGTyGloVr;
      string HnFcOZdVWr;
      string jCQYXujpGh;
      string pDXSmnpwHz;
      string ZkLTTCDZAF;
      string xJKDwlFhuD;
      string VuimCEPmoa;
      if(NjpfkrUXPL == ElFlJUkTzc){jgNWSypxFV = true;}
      else if(ElFlJUkTzc == NjpfkrUXPL){mqBhlHLsiP = true;}
      if(YKPafKsmKF == KxPGFMahLb){qJoBkfrUVA = true;}
      else if(KxPGFMahLb == YKPafKsmKF){wGQcPaukms = true;}
      if(XCesVmnRJp == pJCPfaehug){iHAEcdCYQO = true;}
      else if(pJCPfaehug == XCesVmnRJp){acfmkxKmWZ = true;}
      if(pauHkcpkbJ == oWGTyGloVr){lQjZUPumjx = true;}
      else if(oWGTyGloVr == pauHkcpkbJ){ztjFdfTmIu = true;}
      if(NyDWLStwpd == HnFcOZdVWr){wHbZMMGgCV = true;}
      else if(HnFcOZdVWr == NyDWLStwpd){dGNSwcVQfZ = true;}
      if(cwTqCKFxJy == jCQYXujpGh){LuQnqbgItn = true;}
      else if(jCQYXujpGh == cwTqCKFxJy){ipxwLJKNxn = true;}
      if(EDNZVxOHpD == pDXSmnpwHz){wRfpiZYOfU = true;}
      else if(pDXSmnpwHz == EDNZVxOHpD){wYVIQBVKzi = true;}
      if(UHKAqZzIgC == ZkLTTCDZAF){jEjXEafZrQ = true;}
      if(rrbfNsHEFZ == xJKDwlFhuD){XUVuCpzwir = true;}
      if(WsbcEKkcBN == VuimCEPmoa){imswBdbkpl = true;}
      while(ZkLTTCDZAF == UHKAqZzIgC){HHbrOTPNqI = true;}
      while(xJKDwlFhuD == xJKDwlFhuD){btGxqJwmtT = true;}
      while(VuimCEPmoa == VuimCEPmoa){UFpUyFjECt = true;}
      if(jgNWSypxFV == true){jgNWSypxFV = false;}
      if(qJoBkfrUVA == true){qJoBkfrUVA = false;}
      if(iHAEcdCYQO == true){iHAEcdCYQO = false;}
      if(lQjZUPumjx == true){lQjZUPumjx = false;}
      if(wHbZMMGgCV == true){wHbZMMGgCV = false;}
      if(LuQnqbgItn == true){LuQnqbgItn = false;}
      if(wRfpiZYOfU == true){wRfpiZYOfU = false;}
      if(jEjXEafZrQ == true){jEjXEafZrQ = false;}
      if(XUVuCpzwir == true){XUVuCpzwir = false;}
      if(imswBdbkpl == true){imswBdbkpl = false;}
      if(mqBhlHLsiP == true){mqBhlHLsiP = false;}
      if(wGQcPaukms == true){wGQcPaukms = false;}
      if(acfmkxKmWZ == true){acfmkxKmWZ = false;}
      if(ztjFdfTmIu == true){ztjFdfTmIu = false;}
      if(dGNSwcVQfZ == true){dGNSwcVQfZ = false;}
      if(ipxwLJKNxn == true){ipxwLJKNxn = false;}
      if(wYVIQBVKzi == true){wYVIQBVKzi = false;}
      if(HHbrOTPNqI == true){HHbrOTPNqI = false;}
      if(btGxqJwmtT == true){btGxqJwmtT = false;}
      if(UFpUyFjECt == true){UFpUyFjECt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXHBRTJVDN
{ 
  void xPMtuZSkXX()
  { 
      bool CYICPxPzcB = false;
      bool aAmctkwObe = false;
      bool RDJTKEznBK = false;
      bool hUgzHEqbZJ = false;
      bool HTTLWVLNLN = false;
      bool fJOwTyPorK = false;
      bool xaySTFTmVo = false;
      bool sToRWyjxwn = false;
      bool slbmdYGkeI = false;
      bool oCjPMfUArR = false;
      bool CXqWTLTwYV = false;
      bool NRrDQLzKnu = false;
      bool zhIMzqiZFq = false;
      bool djFelVtFSS = false;
      bool EJLJuWJgyA = false;
      bool gJMxRTOeWc = false;
      bool ctqhrdMNQu = false;
      bool RtqVqpWzRb = false;
      bool gCbFJTXHMR = false;
      bool GPhppJSdRR = false;
      string blsjIPFwmb;
      string ljJaaQnxiQ;
      string xSFjYUfGtI;
      string tJrKlxzmke;
      string JiPmUQtXcQ;
      string MBRlxIfIKn;
      string jzBehbrznc;
      string RBLEGNDROI;
      string aHdcurqFMd;
      string QpbxuKgjFs;
      string XujzzKoNfi;
      string FNsBMbVXjo;
      string jllKMaZOIw;
      string gTMVjfXddj;
      string CdZdXDwZjS;
      string oJAPIlIYmX;
      string kaEiClAXRg;
      string DqsAlGLIlJ;
      string dAeoHWTwNy;
      string WyqFybYpal;
      if(blsjIPFwmb == XujzzKoNfi){CYICPxPzcB = true;}
      else if(XujzzKoNfi == blsjIPFwmb){CXqWTLTwYV = true;}
      if(ljJaaQnxiQ == FNsBMbVXjo){aAmctkwObe = true;}
      else if(FNsBMbVXjo == ljJaaQnxiQ){NRrDQLzKnu = true;}
      if(xSFjYUfGtI == jllKMaZOIw){RDJTKEznBK = true;}
      else if(jllKMaZOIw == xSFjYUfGtI){zhIMzqiZFq = true;}
      if(tJrKlxzmke == gTMVjfXddj){hUgzHEqbZJ = true;}
      else if(gTMVjfXddj == tJrKlxzmke){djFelVtFSS = true;}
      if(JiPmUQtXcQ == CdZdXDwZjS){HTTLWVLNLN = true;}
      else if(CdZdXDwZjS == JiPmUQtXcQ){EJLJuWJgyA = true;}
      if(MBRlxIfIKn == oJAPIlIYmX){fJOwTyPorK = true;}
      else if(oJAPIlIYmX == MBRlxIfIKn){gJMxRTOeWc = true;}
      if(jzBehbrznc == kaEiClAXRg){xaySTFTmVo = true;}
      else if(kaEiClAXRg == jzBehbrznc){ctqhrdMNQu = true;}
      if(RBLEGNDROI == DqsAlGLIlJ){sToRWyjxwn = true;}
      if(aHdcurqFMd == dAeoHWTwNy){slbmdYGkeI = true;}
      if(QpbxuKgjFs == WyqFybYpal){oCjPMfUArR = true;}
      while(DqsAlGLIlJ == RBLEGNDROI){RtqVqpWzRb = true;}
      while(dAeoHWTwNy == dAeoHWTwNy){gCbFJTXHMR = true;}
      while(WyqFybYpal == WyqFybYpal){GPhppJSdRR = true;}
      if(CYICPxPzcB == true){CYICPxPzcB = false;}
      if(aAmctkwObe == true){aAmctkwObe = false;}
      if(RDJTKEznBK == true){RDJTKEznBK = false;}
      if(hUgzHEqbZJ == true){hUgzHEqbZJ = false;}
      if(HTTLWVLNLN == true){HTTLWVLNLN = false;}
      if(fJOwTyPorK == true){fJOwTyPorK = false;}
      if(xaySTFTmVo == true){xaySTFTmVo = false;}
      if(sToRWyjxwn == true){sToRWyjxwn = false;}
      if(slbmdYGkeI == true){slbmdYGkeI = false;}
      if(oCjPMfUArR == true){oCjPMfUArR = false;}
      if(CXqWTLTwYV == true){CXqWTLTwYV = false;}
      if(NRrDQLzKnu == true){NRrDQLzKnu = false;}
      if(zhIMzqiZFq == true){zhIMzqiZFq = false;}
      if(djFelVtFSS == true){djFelVtFSS = false;}
      if(EJLJuWJgyA == true){EJLJuWJgyA = false;}
      if(gJMxRTOeWc == true){gJMxRTOeWc = false;}
      if(ctqhrdMNQu == true){ctqhrdMNQu = false;}
      if(RtqVqpWzRb == true){RtqVqpWzRb = false;}
      if(gCbFJTXHMR == true){gCbFJTXHMR = false;}
      if(GPhppJSdRR == true){GPhppJSdRR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRUNDUQYBA
{ 
  void sAEZDUBHCJ()
  { 
      bool LFBRQiiJZt = false;
      bool YIAyENXRAV = false;
      bool quBsjmJdtM = false;
      bool ANbgAAQsWi = false;
      bool bedXaLKtcI = false;
      bool cJlYcQEHgd = false;
      bool YEPMsLgSxE = false;
      bool xduQtLQcSY = false;
      bool cOAkjqaCEi = false;
      bool uJMsKWPQdO = false;
      bool eqxYLyNUeQ = false;
      bool AaoIBJEdcC = false;
      bool jdONJnQCGW = false;
      bool wAzDskRbZl = false;
      bool cGWmiTTEqA = false;
      bool RknbeAbiPX = false;
      bool hLOHUzbkOP = false;
      bool rcEqYdGbeo = false;
      bool TMKGELLXYr = false;
      bool IhLBDQrPSi = false;
      string qbXqELpUmZ;
      string leMPxOPasg;
      string pdIzSTdxhT;
      string cjwBLVEmOL;
      string klPgfNnJKz;
      string WcrSoMSYYk;
      string hsmSwBiKDa;
      string JbLhwEObSE;
      string eUmhxArcLz;
      string CeOcdrzxje;
      string edGiotQKWk;
      string yqGTGNGEUw;
      string JFyDXeNhEE;
      string FQqmZAODrD;
      string igFaBLYuWP;
      string ktbmVYfCKK;
      string fiGSfgzStF;
      string zCLRNbAWBM;
      string FRLnSKoERA;
      string ULshWAaluU;
      if(qbXqELpUmZ == edGiotQKWk){LFBRQiiJZt = true;}
      else if(edGiotQKWk == qbXqELpUmZ){eqxYLyNUeQ = true;}
      if(leMPxOPasg == yqGTGNGEUw){YIAyENXRAV = true;}
      else if(yqGTGNGEUw == leMPxOPasg){AaoIBJEdcC = true;}
      if(pdIzSTdxhT == JFyDXeNhEE){quBsjmJdtM = true;}
      else if(JFyDXeNhEE == pdIzSTdxhT){jdONJnQCGW = true;}
      if(cjwBLVEmOL == FQqmZAODrD){ANbgAAQsWi = true;}
      else if(FQqmZAODrD == cjwBLVEmOL){wAzDskRbZl = true;}
      if(klPgfNnJKz == igFaBLYuWP){bedXaLKtcI = true;}
      else if(igFaBLYuWP == klPgfNnJKz){cGWmiTTEqA = true;}
      if(WcrSoMSYYk == ktbmVYfCKK){cJlYcQEHgd = true;}
      else if(ktbmVYfCKK == WcrSoMSYYk){RknbeAbiPX = true;}
      if(hsmSwBiKDa == fiGSfgzStF){YEPMsLgSxE = true;}
      else if(fiGSfgzStF == hsmSwBiKDa){hLOHUzbkOP = true;}
      if(JbLhwEObSE == zCLRNbAWBM){xduQtLQcSY = true;}
      if(eUmhxArcLz == FRLnSKoERA){cOAkjqaCEi = true;}
      if(CeOcdrzxje == ULshWAaluU){uJMsKWPQdO = true;}
      while(zCLRNbAWBM == JbLhwEObSE){rcEqYdGbeo = true;}
      while(FRLnSKoERA == FRLnSKoERA){TMKGELLXYr = true;}
      while(ULshWAaluU == ULshWAaluU){IhLBDQrPSi = true;}
      if(LFBRQiiJZt == true){LFBRQiiJZt = false;}
      if(YIAyENXRAV == true){YIAyENXRAV = false;}
      if(quBsjmJdtM == true){quBsjmJdtM = false;}
      if(ANbgAAQsWi == true){ANbgAAQsWi = false;}
      if(bedXaLKtcI == true){bedXaLKtcI = false;}
      if(cJlYcQEHgd == true){cJlYcQEHgd = false;}
      if(YEPMsLgSxE == true){YEPMsLgSxE = false;}
      if(xduQtLQcSY == true){xduQtLQcSY = false;}
      if(cOAkjqaCEi == true){cOAkjqaCEi = false;}
      if(uJMsKWPQdO == true){uJMsKWPQdO = false;}
      if(eqxYLyNUeQ == true){eqxYLyNUeQ = false;}
      if(AaoIBJEdcC == true){AaoIBJEdcC = false;}
      if(jdONJnQCGW == true){jdONJnQCGW = false;}
      if(wAzDskRbZl == true){wAzDskRbZl = false;}
      if(cGWmiTTEqA == true){cGWmiTTEqA = false;}
      if(RknbeAbiPX == true){RknbeAbiPX = false;}
      if(hLOHUzbkOP == true){hLOHUzbkOP = false;}
      if(rcEqYdGbeo == true){rcEqYdGbeo = false;}
      if(TMKGELLXYr == true){TMKGELLXYr = false;}
      if(IhLBDQrPSi == true){IhLBDQrPSi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APTUBOUWKX
{ 
  void yYjVyqIREB()
  { 
      bool QxwrlaVnbp = false;
      bool AVuzfWDOHD = false;
      bool OtoULSekeF = false;
      bool mdqTZsuSDI = false;
      bool GZlkSMjIds = false;
      bool TUxMtVHagT = false;
      bool ukJWCWdaYm = false;
      bool bjKyxoHECz = false;
      bool iWGkkSfeZD = false;
      bool kTljNVQPhu = false;
      bool hIjqRjJzPF = false;
      bool ODXhkYdXlj = false;
      bool pzBUBHyaka = false;
      bool XrWHQZmPTB = false;
      bool IgPTohuDzn = false;
      bool qsdxEhGPoJ = false;
      bool kiNngVgQQK = false;
      bool lNDjbJjgeS = false;
      bool LtawieOYCi = false;
      bool TXaJPYSbmT = false;
      string BuqEDPfuQT;
      string yhJgwLpgBi;
      string SPaWuDRnIS;
      string DQShAYmkql;
      string ofHlHdJWgz;
      string wCuhMkTUIz;
      string yqlxQhPafX;
      string XFoOtmIoOR;
      string tuHJWAUjVP;
      string ESbqnxsKUZ;
      string OhpJbqNfnZ;
      string bdFqFDjcaP;
      string MeEQSEcxaw;
      string syToCLEyge;
      string mowwmaNklk;
      string MQjFNidYpW;
      string OPFqfdJQns;
      string yluucWiHdq;
      string pqLpjbOOaS;
      string hfHKQXjEQJ;
      if(BuqEDPfuQT == OhpJbqNfnZ){QxwrlaVnbp = true;}
      else if(OhpJbqNfnZ == BuqEDPfuQT){hIjqRjJzPF = true;}
      if(yhJgwLpgBi == bdFqFDjcaP){AVuzfWDOHD = true;}
      else if(bdFqFDjcaP == yhJgwLpgBi){ODXhkYdXlj = true;}
      if(SPaWuDRnIS == MeEQSEcxaw){OtoULSekeF = true;}
      else if(MeEQSEcxaw == SPaWuDRnIS){pzBUBHyaka = true;}
      if(DQShAYmkql == syToCLEyge){mdqTZsuSDI = true;}
      else if(syToCLEyge == DQShAYmkql){XrWHQZmPTB = true;}
      if(ofHlHdJWgz == mowwmaNklk){GZlkSMjIds = true;}
      else if(mowwmaNklk == ofHlHdJWgz){IgPTohuDzn = true;}
      if(wCuhMkTUIz == MQjFNidYpW){TUxMtVHagT = true;}
      else if(MQjFNidYpW == wCuhMkTUIz){qsdxEhGPoJ = true;}
      if(yqlxQhPafX == OPFqfdJQns){ukJWCWdaYm = true;}
      else if(OPFqfdJQns == yqlxQhPafX){kiNngVgQQK = true;}
      if(XFoOtmIoOR == yluucWiHdq){bjKyxoHECz = true;}
      if(tuHJWAUjVP == pqLpjbOOaS){iWGkkSfeZD = true;}
      if(ESbqnxsKUZ == hfHKQXjEQJ){kTljNVQPhu = true;}
      while(yluucWiHdq == XFoOtmIoOR){lNDjbJjgeS = true;}
      while(pqLpjbOOaS == pqLpjbOOaS){LtawieOYCi = true;}
      while(hfHKQXjEQJ == hfHKQXjEQJ){TXaJPYSbmT = true;}
      if(QxwrlaVnbp == true){QxwrlaVnbp = false;}
      if(AVuzfWDOHD == true){AVuzfWDOHD = false;}
      if(OtoULSekeF == true){OtoULSekeF = false;}
      if(mdqTZsuSDI == true){mdqTZsuSDI = false;}
      if(GZlkSMjIds == true){GZlkSMjIds = false;}
      if(TUxMtVHagT == true){TUxMtVHagT = false;}
      if(ukJWCWdaYm == true){ukJWCWdaYm = false;}
      if(bjKyxoHECz == true){bjKyxoHECz = false;}
      if(iWGkkSfeZD == true){iWGkkSfeZD = false;}
      if(kTljNVQPhu == true){kTljNVQPhu = false;}
      if(hIjqRjJzPF == true){hIjqRjJzPF = false;}
      if(ODXhkYdXlj == true){ODXhkYdXlj = false;}
      if(pzBUBHyaka == true){pzBUBHyaka = false;}
      if(XrWHQZmPTB == true){XrWHQZmPTB = false;}
      if(IgPTohuDzn == true){IgPTohuDzn = false;}
      if(qsdxEhGPoJ == true){qsdxEhGPoJ = false;}
      if(kiNngVgQQK == true){kiNngVgQQK = false;}
      if(lNDjbJjgeS == true){lNDjbJjgeS = false;}
      if(LtawieOYCi == true){LtawieOYCi = false;}
      if(TXaJPYSbmT == true){TXaJPYSbmT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHZTCRXREQ
{ 
  void ctrgTPOXgQ()
  { 
      bool hipYGTUusD = false;
      bool GtCWPZYSpp = false;
      bool QigeshJXsm = false;
      bool dHgVEKjDOc = false;
      bool wJBVSbhxMT = false;
      bool VhGAqyBLeY = false;
      bool KwCGZyMfSF = false;
      bool pVENsGgLLR = false;
      bool zMLYRwAgeF = false;
      bool IYYoRzHuwU = false;
      bool OCdHdzcsGj = false;
      bool QpzNYykcoc = false;
      bool xfBNwRxPut = false;
      bool zlPpCwhEtR = false;
      bool SGZtoSYKPT = false;
      bool OdGSWiBQKM = false;
      bool CNyMkdZJLc = false;
      bool PgiWJqFHXc = false;
      bool rlzaeUfxTT = false;
      bool uRshOFINIK = false;
      string bKnNxwxman;
      string DGlHFaIdIx;
      string YMeKpUCESh;
      string sKAcGsjGUD;
      string xdIBxGusTk;
      string VcmhmPedXc;
      string trUsusGJBM;
      string pCJEAuDcNi;
      string YJkgMQXRoq;
      string NGhrJFIPGE;
      string zkqHtSThhr;
      string LBPnDjHmfe;
      string UnTKyjTQtu;
      string lnWIjmRcms;
      string xojweMptnY;
      string yUiaiKRgIJ;
      string zCnmGWeGEP;
      string SdAmheEWel;
      string tZcUwQFuZY;
      string VkTctuBxpI;
      if(bKnNxwxman == zkqHtSThhr){hipYGTUusD = true;}
      else if(zkqHtSThhr == bKnNxwxman){OCdHdzcsGj = true;}
      if(DGlHFaIdIx == LBPnDjHmfe){GtCWPZYSpp = true;}
      else if(LBPnDjHmfe == DGlHFaIdIx){QpzNYykcoc = true;}
      if(YMeKpUCESh == UnTKyjTQtu){QigeshJXsm = true;}
      else if(UnTKyjTQtu == YMeKpUCESh){xfBNwRxPut = true;}
      if(sKAcGsjGUD == lnWIjmRcms){dHgVEKjDOc = true;}
      else if(lnWIjmRcms == sKAcGsjGUD){zlPpCwhEtR = true;}
      if(xdIBxGusTk == xojweMptnY){wJBVSbhxMT = true;}
      else if(xojweMptnY == xdIBxGusTk){SGZtoSYKPT = true;}
      if(VcmhmPedXc == yUiaiKRgIJ){VhGAqyBLeY = true;}
      else if(yUiaiKRgIJ == VcmhmPedXc){OdGSWiBQKM = true;}
      if(trUsusGJBM == zCnmGWeGEP){KwCGZyMfSF = true;}
      else if(zCnmGWeGEP == trUsusGJBM){CNyMkdZJLc = true;}
      if(pCJEAuDcNi == SdAmheEWel){pVENsGgLLR = true;}
      if(YJkgMQXRoq == tZcUwQFuZY){zMLYRwAgeF = true;}
      if(NGhrJFIPGE == VkTctuBxpI){IYYoRzHuwU = true;}
      while(SdAmheEWel == pCJEAuDcNi){PgiWJqFHXc = true;}
      while(tZcUwQFuZY == tZcUwQFuZY){rlzaeUfxTT = true;}
      while(VkTctuBxpI == VkTctuBxpI){uRshOFINIK = true;}
      if(hipYGTUusD == true){hipYGTUusD = false;}
      if(GtCWPZYSpp == true){GtCWPZYSpp = false;}
      if(QigeshJXsm == true){QigeshJXsm = false;}
      if(dHgVEKjDOc == true){dHgVEKjDOc = false;}
      if(wJBVSbhxMT == true){wJBVSbhxMT = false;}
      if(VhGAqyBLeY == true){VhGAqyBLeY = false;}
      if(KwCGZyMfSF == true){KwCGZyMfSF = false;}
      if(pVENsGgLLR == true){pVENsGgLLR = false;}
      if(zMLYRwAgeF == true){zMLYRwAgeF = false;}
      if(IYYoRzHuwU == true){IYYoRzHuwU = false;}
      if(OCdHdzcsGj == true){OCdHdzcsGj = false;}
      if(QpzNYykcoc == true){QpzNYykcoc = false;}
      if(xfBNwRxPut == true){xfBNwRxPut = false;}
      if(zlPpCwhEtR == true){zlPpCwhEtR = false;}
      if(SGZtoSYKPT == true){SGZtoSYKPT = false;}
      if(OdGSWiBQKM == true){OdGSWiBQKM = false;}
      if(CNyMkdZJLc == true){CNyMkdZJLc = false;}
      if(PgiWJqFHXc == true){PgiWJqFHXc = false;}
      if(rlzaeUfxTT == true){rlzaeUfxTT = false;}
      if(uRshOFINIK == true){uRshOFINIK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QVUMXNHSTP
{ 
  void MllbQGfiNj()
  { 
      bool DtiibYNVbM = false;
      bool cQPPbeSTZJ = false;
      bool VMWfVJKhte = false;
      bool HAxWfDJzxi = false;
      bool iFCshnLCwR = false;
      bool iVCWspXDMR = false;
      bool OfbxFcSsjX = false;
      bool VTVpZPJcyg = false;
      bool yHkcwlxZco = false;
      bool fGlfUDdFnE = false;
      bool USSYuOzMxd = false;
      bool ftEeSHtyAT = false;
      bool esPtqPgpUV = false;
      bool lEosMenMhg = false;
      bool lkczIlBHMN = false;
      bool JeEUZbCXge = false;
      bool gJqaqbEKSm = false;
      bool ShQTgtPQlF = false;
      bool OZcHMGAUTj = false;
      bool bQeCActCHg = false;
      string VXwHiqWieB;
      string IAAMwLzAuy;
      string PPJtrxrfiF;
      string UMIYIpUxWd;
      string nYzaljlIjm;
      string sXxDNFOCPl;
      string zqAYguraEG;
      string pBdQJpQhHI;
      string KiwuMxOFKD;
      string aShkdxYZsp;
      string rKEdxqsftX;
      string nftHaQuEMj;
      string fmQBeWTrmL;
      string RpnQPzeRyU;
      string DiKmOuXaKN;
      string CTNJKFtCzZ;
      string XBsiGyqdqa;
      string lcGqgxbdmi;
      string yrhYIxbeGK;
      string FbSXwBobfP;
      if(VXwHiqWieB == rKEdxqsftX){DtiibYNVbM = true;}
      else if(rKEdxqsftX == VXwHiqWieB){USSYuOzMxd = true;}
      if(IAAMwLzAuy == nftHaQuEMj){cQPPbeSTZJ = true;}
      else if(nftHaQuEMj == IAAMwLzAuy){ftEeSHtyAT = true;}
      if(PPJtrxrfiF == fmQBeWTrmL){VMWfVJKhte = true;}
      else if(fmQBeWTrmL == PPJtrxrfiF){esPtqPgpUV = true;}
      if(UMIYIpUxWd == RpnQPzeRyU){HAxWfDJzxi = true;}
      else if(RpnQPzeRyU == UMIYIpUxWd){lEosMenMhg = true;}
      if(nYzaljlIjm == DiKmOuXaKN){iFCshnLCwR = true;}
      else if(DiKmOuXaKN == nYzaljlIjm){lkczIlBHMN = true;}
      if(sXxDNFOCPl == CTNJKFtCzZ){iVCWspXDMR = true;}
      else if(CTNJKFtCzZ == sXxDNFOCPl){JeEUZbCXge = true;}
      if(zqAYguraEG == XBsiGyqdqa){OfbxFcSsjX = true;}
      else if(XBsiGyqdqa == zqAYguraEG){gJqaqbEKSm = true;}
      if(pBdQJpQhHI == lcGqgxbdmi){VTVpZPJcyg = true;}
      if(KiwuMxOFKD == yrhYIxbeGK){yHkcwlxZco = true;}
      if(aShkdxYZsp == FbSXwBobfP){fGlfUDdFnE = true;}
      while(lcGqgxbdmi == pBdQJpQhHI){ShQTgtPQlF = true;}
      while(yrhYIxbeGK == yrhYIxbeGK){OZcHMGAUTj = true;}
      while(FbSXwBobfP == FbSXwBobfP){bQeCActCHg = true;}
      if(DtiibYNVbM == true){DtiibYNVbM = false;}
      if(cQPPbeSTZJ == true){cQPPbeSTZJ = false;}
      if(VMWfVJKhte == true){VMWfVJKhte = false;}
      if(HAxWfDJzxi == true){HAxWfDJzxi = false;}
      if(iFCshnLCwR == true){iFCshnLCwR = false;}
      if(iVCWspXDMR == true){iVCWspXDMR = false;}
      if(OfbxFcSsjX == true){OfbxFcSsjX = false;}
      if(VTVpZPJcyg == true){VTVpZPJcyg = false;}
      if(yHkcwlxZco == true){yHkcwlxZco = false;}
      if(fGlfUDdFnE == true){fGlfUDdFnE = false;}
      if(USSYuOzMxd == true){USSYuOzMxd = false;}
      if(ftEeSHtyAT == true){ftEeSHtyAT = false;}
      if(esPtqPgpUV == true){esPtqPgpUV = false;}
      if(lEosMenMhg == true){lEosMenMhg = false;}
      if(lkczIlBHMN == true){lkczIlBHMN = false;}
      if(JeEUZbCXge == true){JeEUZbCXge = false;}
      if(gJqaqbEKSm == true){gJqaqbEKSm = false;}
      if(ShQTgtPQlF == true){ShQTgtPQlF = false;}
      if(OZcHMGAUTj == true){OZcHMGAUTj = false;}
      if(bQeCActCHg == true){bQeCActCHg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDHIOODYPO
{ 
  void TbFflLpHyU()
  { 
      bool HPVVxzMOim = false;
      bool jBebzdsmkp = false;
      bool kxSzGMllzt = false;
      bool NdMHNrImKT = false;
      bool bNdbkVLfWu = false;
      bool mkxwDKxVOk = false;
      bool NaPoYGnWOG = false;
      bool UFbQOXSpOj = false;
      bool BFPEGcfPEC = false;
      bool tlXYFByoDd = false;
      bool hnRPZgIfhf = false;
      bool qGHejHLKhu = false;
      bool ZXSLLigDLM = false;
      bool YdmjBMmzeY = false;
      bool TzgXLnesnx = false;
      bool omGHEKVFDp = false;
      bool AEUVGMSWcW = false;
      bool TLfIaZptzX = false;
      bool EnONXlWffq = false;
      bool phwnYPeLRy = false;
      string GmNFoHTJER;
      string dhlxTjWLHB;
      string uTMYIqwYgm;
      string OCeKScJYAe;
      string qgKVFxwFeo;
      string aVfaClZoxx;
      string KubRCbCaeq;
      string axKcJNJqSL;
      string tqtqLsWDHf;
      string CTbCTwEsTd;
      string tUZmOdKDRo;
      string ciVkDTBjFJ;
      string FyTzoGUIIN;
      string JPXnQYQGcg;
      string iSlSCTypzA;
      string tTmJYwBayH;
      string ICuDeNLhUd;
      string CtHYalLAwV;
      string IeIISobNOU;
      string XpIVYfXhmn;
      if(GmNFoHTJER == tUZmOdKDRo){HPVVxzMOim = true;}
      else if(tUZmOdKDRo == GmNFoHTJER){hnRPZgIfhf = true;}
      if(dhlxTjWLHB == ciVkDTBjFJ){jBebzdsmkp = true;}
      else if(ciVkDTBjFJ == dhlxTjWLHB){qGHejHLKhu = true;}
      if(uTMYIqwYgm == FyTzoGUIIN){kxSzGMllzt = true;}
      else if(FyTzoGUIIN == uTMYIqwYgm){ZXSLLigDLM = true;}
      if(OCeKScJYAe == JPXnQYQGcg){NdMHNrImKT = true;}
      else if(JPXnQYQGcg == OCeKScJYAe){YdmjBMmzeY = true;}
      if(qgKVFxwFeo == iSlSCTypzA){bNdbkVLfWu = true;}
      else if(iSlSCTypzA == qgKVFxwFeo){TzgXLnesnx = true;}
      if(aVfaClZoxx == tTmJYwBayH){mkxwDKxVOk = true;}
      else if(tTmJYwBayH == aVfaClZoxx){omGHEKVFDp = true;}
      if(KubRCbCaeq == ICuDeNLhUd){NaPoYGnWOG = true;}
      else if(ICuDeNLhUd == KubRCbCaeq){AEUVGMSWcW = true;}
      if(axKcJNJqSL == CtHYalLAwV){UFbQOXSpOj = true;}
      if(tqtqLsWDHf == IeIISobNOU){BFPEGcfPEC = true;}
      if(CTbCTwEsTd == XpIVYfXhmn){tlXYFByoDd = true;}
      while(CtHYalLAwV == axKcJNJqSL){TLfIaZptzX = true;}
      while(IeIISobNOU == IeIISobNOU){EnONXlWffq = true;}
      while(XpIVYfXhmn == XpIVYfXhmn){phwnYPeLRy = true;}
      if(HPVVxzMOim == true){HPVVxzMOim = false;}
      if(jBebzdsmkp == true){jBebzdsmkp = false;}
      if(kxSzGMllzt == true){kxSzGMllzt = false;}
      if(NdMHNrImKT == true){NdMHNrImKT = false;}
      if(bNdbkVLfWu == true){bNdbkVLfWu = false;}
      if(mkxwDKxVOk == true){mkxwDKxVOk = false;}
      if(NaPoYGnWOG == true){NaPoYGnWOG = false;}
      if(UFbQOXSpOj == true){UFbQOXSpOj = false;}
      if(BFPEGcfPEC == true){BFPEGcfPEC = false;}
      if(tlXYFByoDd == true){tlXYFByoDd = false;}
      if(hnRPZgIfhf == true){hnRPZgIfhf = false;}
      if(qGHejHLKhu == true){qGHejHLKhu = false;}
      if(ZXSLLigDLM == true){ZXSLLigDLM = false;}
      if(YdmjBMmzeY == true){YdmjBMmzeY = false;}
      if(TzgXLnesnx == true){TzgXLnesnx = false;}
      if(omGHEKVFDp == true){omGHEKVFDp = false;}
      if(AEUVGMSWcW == true){AEUVGMSWcW = false;}
      if(TLfIaZptzX == true){TLfIaZptzX = false;}
      if(EnONXlWffq == true){EnONXlWffq = false;}
      if(phwnYPeLRy == true){phwnYPeLRy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSVMDSNWTJ
{ 
  void reJGIJAPtc()
  { 
      bool NoMNrAAPNV = false;
      bool EJJQTYULKb = false;
      bool rBzaAVbgWY = false;
      bool xxoYmQEUnp = false;
      bool QFyOXclfsw = false;
      bool bEzOOMolMV = false;
      bool XSroYHTkdD = false;
      bool TAXUKlDkCW = false;
      bool iumZwryZJZ = false;
      bool aSHRRxNJoQ = false;
      bool JBBocbgeDc = false;
      bool JDjomceRrf = false;
      bool IsbEcBrFCN = false;
      bool XtwkNhsyxU = false;
      bool LTVgQWiSeo = false;
      bool RwQIIPZxMa = false;
      bool iacpEPHyaF = false;
      bool igUWUnWtnF = false;
      bool SYaMubcmcx = false;
      bool HwlVljqfbA = false;
      string hbOWiCWbwk;
      string ihdFMPTPwx;
      string kyQlFmYVDE;
      string bZgbtxGaOr;
      string QzGONhFyKM;
      string RnkAoiLcQw;
      string dAXrJJABKP;
      string IrBEglrBXW;
      string gZLqlmnflL;
      string ldJRNPaOFE;
      string gEnuEYmgTD;
      string qJEsPDogFV;
      string UUOzcehjpR;
      string KdwTpbkPmM;
      string AHMiTbYQBJ;
      string ZtIiiMooRZ;
      string qDqCrNNjDn;
      string RZtsVMHfeB;
      string FRhfqQVMjc;
      string mwxNVwPKpG;
      if(hbOWiCWbwk == gEnuEYmgTD){NoMNrAAPNV = true;}
      else if(gEnuEYmgTD == hbOWiCWbwk){JBBocbgeDc = true;}
      if(ihdFMPTPwx == qJEsPDogFV){EJJQTYULKb = true;}
      else if(qJEsPDogFV == ihdFMPTPwx){JDjomceRrf = true;}
      if(kyQlFmYVDE == UUOzcehjpR){rBzaAVbgWY = true;}
      else if(UUOzcehjpR == kyQlFmYVDE){IsbEcBrFCN = true;}
      if(bZgbtxGaOr == KdwTpbkPmM){xxoYmQEUnp = true;}
      else if(KdwTpbkPmM == bZgbtxGaOr){XtwkNhsyxU = true;}
      if(QzGONhFyKM == AHMiTbYQBJ){QFyOXclfsw = true;}
      else if(AHMiTbYQBJ == QzGONhFyKM){LTVgQWiSeo = true;}
      if(RnkAoiLcQw == ZtIiiMooRZ){bEzOOMolMV = true;}
      else if(ZtIiiMooRZ == RnkAoiLcQw){RwQIIPZxMa = true;}
      if(dAXrJJABKP == qDqCrNNjDn){XSroYHTkdD = true;}
      else if(qDqCrNNjDn == dAXrJJABKP){iacpEPHyaF = true;}
      if(IrBEglrBXW == RZtsVMHfeB){TAXUKlDkCW = true;}
      if(gZLqlmnflL == FRhfqQVMjc){iumZwryZJZ = true;}
      if(ldJRNPaOFE == mwxNVwPKpG){aSHRRxNJoQ = true;}
      while(RZtsVMHfeB == IrBEglrBXW){igUWUnWtnF = true;}
      while(FRhfqQVMjc == FRhfqQVMjc){SYaMubcmcx = true;}
      while(mwxNVwPKpG == mwxNVwPKpG){HwlVljqfbA = true;}
      if(NoMNrAAPNV == true){NoMNrAAPNV = false;}
      if(EJJQTYULKb == true){EJJQTYULKb = false;}
      if(rBzaAVbgWY == true){rBzaAVbgWY = false;}
      if(xxoYmQEUnp == true){xxoYmQEUnp = false;}
      if(QFyOXclfsw == true){QFyOXclfsw = false;}
      if(bEzOOMolMV == true){bEzOOMolMV = false;}
      if(XSroYHTkdD == true){XSroYHTkdD = false;}
      if(TAXUKlDkCW == true){TAXUKlDkCW = false;}
      if(iumZwryZJZ == true){iumZwryZJZ = false;}
      if(aSHRRxNJoQ == true){aSHRRxNJoQ = false;}
      if(JBBocbgeDc == true){JBBocbgeDc = false;}
      if(JDjomceRrf == true){JDjomceRrf = false;}
      if(IsbEcBrFCN == true){IsbEcBrFCN = false;}
      if(XtwkNhsyxU == true){XtwkNhsyxU = false;}
      if(LTVgQWiSeo == true){LTVgQWiSeo = false;}
      if(RwQIIPZxMa == true){RwQIIPZxMa = false;}
      if(iacpEPHyaF == true){iacpEPHyaF = false;}
      if(igUWUnWtnF == true){igUWUnWtnF = false;}
      if(SYaMubcmcx == true){SYaMubcmcx = false;}
      if(HwlVljqfbA == true){HwlVljqfbA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHFFXJTENR
{ 
  void DyWyuuDoGb()
  { 
      bool ViUqHTJkqW = false;
      bool qLNnRgQKKq = false;
      bool ouKoAgnjzA = false;
      bool hhWsEAyGao = false;
      bool xUHEScnafB = false;
      bool wksqVaXepZ = false;
      bool eZkqoJoTiQ = false;
      bool iJjVtTmGWW = false;
      bool sMDxEwnfXd = false;
      bool cSPAJXiQPI = false;
      bool nUqOSlBXxB = false;
      bool mRITgRWnmr = false;
      bool VJwFnQsiMV = false;
      bool jVqNhXVneR = false;
      bool uQhVpLJwTq = false;
      bool BudWmeXlaC = false;
      bool sRKaQQZtkI = false;
      bool whJUwEaZOc = false;
      bool GxOVUorTaD = false;
      bool AjMbXcFHFY = false;
      string DGAPsUUxke;
      string YnanZhSsYL;
      string uaFpzkPAFA;
      string UxHGCRsYlC;
      string ZTTEtVYPOw;
      string fApjZbAJQI;
      string FTrjJagTlI;
      string otHWkbHAuc;
      string LzkITUHWfZ;
      string QiHcxFbiuT;
      string nEdGHlrSyy;
      string TAOmwFhiQo;
      string SKmLqFldZf;
      string zYFbnGUeAh;
      string boXhGQUTfq;
      string WrSFAdRSPC;
      string zOsSzutlzo;
      string jDhhNdlFEa;
      string jSxhIHFzaJ;
      string oCPyiMuEiL;
      if(DGAPsUUxke == nEdGHlrSyy){ViUqHTJkqW = true;}
      else if(nEdGHlrSyy == DGAPsUUxke){nUqOSlBXxB = true;}
      if(YnanZhSsYL == TAOmwFhiQo){qLNnRgQKKq = true;}
      else if(TAOmwFhiQo == YnanZhSsYL){mRITgRWnmr = true;}
      if(uaFpzkPAFA == SKmLqFldZf){ouKoAgnjzA = true;}
      else if(SKmLqFldZf == uaFpzkPAFA){VJwFnQsiMV = true;}
      if(UxHGCRsYlC == zYFbnGUeAh){hhWsEAyGao = true;}
      else if(zYFbnGUeAh == UxHGCRsYlC){jVqNhXVneR = true;}
      if(ZTTEtVYPOw == boXhGQUTfq){xUHEScnafB = true;}
      else if(boXhGQUTfq == ZTTEtVYPOw){uQhVpLJwTq = true;}
      if(fApjZbAJQI == WrSFAdRSPC){wksqVaXepZ = true;}
      else if(WrSFAdRSPC == fApjZbAJQI){BudWmeXlaC = true;}
      if(FTrjJagTlI == zOsSzutlzo){eZkqoJoTiQ = true;}
      else if(zOsSzutlzo == FTrjJagTlI){sRKaQQZtkI = true;}
      if(otHWkbHAuc == jDhhNdlFEa){iJjVtTmGWW = true;}
      if(LzkITUHWfZ == jSxhIHFzaJ){sMDxEwnfXd = true;}
      if(QiHcxFbiuT == oCPyiMuEiL){cSPAJXiQPI = true;}
      while(jDhhNdlFEa == otHWkbHAuc){whJUwEaZOc = true;}
      while(jSxhIHFzaJ == jSxhIHFzaJ){GxOVUorTaD = true;}
      while(oCPyiMuEiL == oCPyiMuEiL){AjMbXcFHFY = true;}
      if(ViUqHTJkqW == true){ViUqHTJkqW = false;}
      if(qLNnRgQKKq == true){qLNnRgQKKq = false;}
      if(ouKoAgnjzA == true){ouKoAgnjzA = false;}
      if(hhWsEAyGao == true){hhWsEAyGao = false;}
      if(xUHEScnafB == true){xUHEScnafB = false;}
      if(wksqVaXepZ == true){wksqVaXepZ = false;}
      if(eZkqoJoTiQ == true){eZkqoJoTiQ = false;}
      if(iJjVtTmGWW == true){iJjVtTmGWW = false;}
      if(sMDxEwnfXd == true){sMDxEwnfXd = false;}
      if(cSPAJXiQPI == true){cSPAJXiQPI = false;}
      if(nUqOSlBXxB == true){nUqOSlBXxB = false;}
      if(mRITgRWnmr == true){mRITgRWnmr = false;}
      if(VJwFnQsiMV == true){VJwFnQsiMV = false;}
      if(jVqNhXVneR == true){jVqNhXVneR = false;}
      if(uQhVpLJwTq == true){uQhVpLJwTq = false;}
      if(BudWmeXlaC == true){BudWmeXlaC = false;}
      if(sRKaQQZtkI == true){sRKaQQZtkI = false;}
      if(whJUwEaZOc == true){whJUwEaZOc = false;}
      if(GxOVUorTaD == true){GxOVUorTaD = false;}
      if(AjMbXcFHFY == true){AjMbXcFHFY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VXJCJZCJZR
{ 
  void DFBJEdJygk()
  { 
      bool wztWEMkJNz = false;
      bool VwBrHjRgYC = false;
      bool ydTAYZYrNg = false;
      bool teibjCRNjs = false;
      bool QGYHhVYkeS = false;
      bool pGYFdSftyd = false;
      bool msufEqMZIF = false;
      bool SDwflqFLRD = false;
      bool BnMtqnFdxR = false;
      bool VWPGFWLrCq = false;
      bool IycZAlKrTl = false;
      bool MTbubzfAoQ = false;
      bool khbpiunoZO = false;
      bool fMJatCLmtF = false;
      bool cNKKEBuUeG = false;
      bool qKDlFaWlpF = false;
      bool xUREGAKABY = false;
      bool mrGjmWXQkg = false;
      bool ATKTWUIXUS = false;
      bool fYxoHIuGEE = false;
      string oCYLPujyAf;
      string eBBfddjJgp;
      string OzFywXeGlc;
      string UQSPmQNUBC;
      string AEQNlnbwhC;
      string VJtpgoxZPr;
      string PdLXLNilsN;
      string PPIepKiqLI;
      string uiXjGLWchx;
      string SnFJlVrrCX;
      string FpCUlGBOzW;
      string FFNGwgGbRz;
      string qGDwtbKysU;
      string RqonCFfDxz;
      string KIcLqNZyNE;
      string OQaCgzmGZK;
      string wCUeEOQZDp;
      string ACeRohcqEg;
      string CLknFBPlGD;
      string RZdmDHmyHc;
      if(oCYLPujyAf == FpCUlGBOzW){wztWEMkJNz = true;}
      else if(FpCUlGBOzW == oCYLPujyAf){IycZAlKrTl = true;}
      if(eBBfddjJgp == FFNGwgGbRz){VwBrHjRgYC = true;}
      else if(FFNGwgGbRz == eBBfddjJgp){MTbubzfAoQ = true;}
      if(OzFywXeGlc == qGDwtbKysU){ydTAYZYrNg = true;}
      else if(qGDwtbKysU == OzFywXeGlc){khbpiunoZO = true;}
      if(UQSPmQNUBC == RqonCFfDxz){teibjCRNjs = true;}
      else if(RqonCFfDxz == UQSPmQNUBC){fMJatCLmtF = true;}
      if(AEQNlnbwhC == KIcLqNZyNE){QGYHhVYkeS = true;}
      else if(KIcLqNZyNE == AEQNlnbwhC){cNKKEBuUeG = true;}
      if(VJtpgoxZPr == OQaCgzmGZK){pGYFdSftyd = true;}
      else if(OQaCgzmGZK == VJtpgoxZPr){qKDlFaWlpF = true;}
      if(PdLXLNilsN == wCUeEOQZDp){msufEqMZIF = true;}
      else if(wCUeEOQZDp == PdLXLNilsN){xUREGAKABY = true;}
      if(PPIepKiqLI == ACeRohcqEg){SDwflqFLRD = true;}
      if(uiXjGLWchx == CLknFBPlGD){BnMtqnFdxR = true;}
      if(SnFJlVrrCX == RZdmDHmyHc){VWPGFWLrCq = true;}
      while(ACeRohcqEg == PPIepKiqLI){mrGjmWXQkg = true;}
      while(CLknFBPlGD == CLknFBPlGD){ATKTWUIXUS = true;}
      while(RZdmDHmyHc == RZdmDHmyHc){fYxoHIuGEE = true;}
      if(wztWEMkJNz == true){wztWEMkJNz = false;}
      if(VwBrHjRgYC == true){VwBrHjRgYC = false;}
      if(ydTAYZYrNg == true){ydTAYZYrNg = false;}
      if(teibjCRNjs == true){teibjCRNjs = false;}
      if(QGYHhVYkeS == true){QGYHhVYkeS = false;}
      if(pGYFdSftyd == true){pGYFdSftyd = false;}
      if(msufEqMZIF == true){msufEqMZIF = false;}
      if(SDwflqFLRD == true){SDwflqFLRD = false;}
      if(BnMtqnFdxR == true){BnMtqnFdxR = false;}
      if(VWPGFWLrCq == true){VWPGFWLrCq = false;}
      if(IycZAlKrTl == true){IycZAlKrTl = false;}
      if(MTbubzfAoQ == true){MTbubzfAoQ = false;}
      if(khbpiunoZO == true){khbpiunoZO = false;}
      if(fMJatCLmtF == true){fMJatCLmtF = false;}
      if(cNKKEBuUeG == true){cNKKEBuUeG = false;}
      if(qKDlFaWlpF == true){qKDlFaWlpF = false;}
      if(xUREGAKABY == true){xUREGAKABY = false;}
      if(mrGjmWXQkg == true){mrGjmWXQkg = false;}
      if(ATKTWUIXUS == true){ATKTWUIXUS = false;}
      if(fYxoHIuGEE == true){fYxoHIuGEE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFHGXJKCKX
{ 
  void HtBSlGpeAn()
  { 
      bool XcXXEzKFUD = false;
      bool lwoRjNqWsc = false;
      bool hOnelDeBVE = false;
      bool ObJUYpYzPg = false;
      bool eCwnweuchV = false;
      bool YNpWJIorlA = false;
      bool TJiQoJlTss = false;
      bool nrHLyfSAiG = false;
      bool IBSAeBkmLP = false;
      bool BfNONVSeyl = false;
      bool sajoggFeYc = false;
      bool pnJfqRpilm = false;
      bool XzHdqIdsxb = false;
      bool MmBxNgRcSx = false;
      bool wFNhZMWgWu = false;
      bool ejsLNsTFxY = false;
      bool DMgwQCmLSK = false;
      bool zNPnqSkYEd = false;
      bool lwVCwcspiT = false;
      bool NLfttjYRRW = false;
      string UlRSxnjqeg;
      string WBWcRCgiKk;
      string CdAOblbbyr;
      string XPoklbnUre;
      string TNxBmdUpEu;
      string FQizcqlDpL;
      string LIslJHLkqp;
      string OMpfRofzax;
      string QkXDmGfpHt;
      string pkdgSKULre;
      string SizNgsZDgn;
      string LlbruajpzC;
      string bUdwzchJMH;
      string UTGueglJVs;
      string gbJTiDJklr;
      string ZdLpDxFCOD;
      string KPqZTqffMN;
      string naTFUzLJNw;
      string TxXTgpIQrh;
      string bjuSiQkiAr;
      if(UlRSxnjqeg == SizNgsZDgn){XcXXEzKFUD = true;}
      else if(SizNgsZDgn == UlRSxnjqeg){sajoggFeYc = true;}
      if(WBWcRCgiKk == LlbruajpzC){lwoRjNqWsc = true;}
      else if(LlbruajpzC == WBWcRCgiKk){pnJfqRpilm = true;}
      if(CdAOblbbyr == bUdwzchJMH){hOnelDeBVE = true;}
      else if(bUdwzchJMH == CdAOblbbyr){XzHdqIdsxb = true;}
      if(XPoklbnUre == UTGueglJVs){ObJUYpYzPg = true;}
      else if(UTGueglJVs == XPoklbnUre){MmBxNgRcSx = true;}
      if(TNxBmdUpEu == gbJTiDJklr){eCwnweuchV = true;}
      else if(gbJTiDJklr == TNxBmdUpEu){wFNhZMWgWu = true;}
      if(FQizcqlDpL == ZdLpDxFCOD){YNpWJIorlA = true;}
      else if(ZdLpDxFCOD == FQizcqlDpL){ejsLNsTFxY = true;}
      if(LIslJHLkqp == KPqZTqffMN){TJiQoJlTss = true;}
      else if(KPqZTqffMN == LIslJHLkqp){DMgwQCmLSK = true;}
      if(OMpfRofzax == naTFUzLJNw){nrHLyfSAiG = true;}
      if(QkXDmGfpHt == TxXTgpIQrh){IBSAeBkmLP = true;}
      if(pkdgSKULre == bjuSiQkiAr){BfNONVSeyl = true;}
      while(naTFUzLJNw == OMpfRofzax){zNPnqSkYEd = true;}
      while(TxXTgpIQrh == TxXTgpIQrh){lwVCwcspiT = true;}
      while(bjuSiQkiAr == bjuSiQkiAr){NLfttjYRRW = true;}
      if(XcXXEzKFUD == true){XcXXEzKFUD = false;}
      if(lwoRjNqWsc == true){lwoRjNqWsc = false;}
      if(hOnelDeBVE == true){hOnelDeBVE = false;}
      if(ObJUYpYzPg == true){ObJUYpYzPg = false;}
      if(eCwnweuchV == true){eCwnweuchV = false;}
      if(YNpWJIorlA == true){YNpWJIorlA = false;}
      if(TJiQoJlTss == true){TJiQoJlTss = false;}
      if(nrHLyfSAiG == true){nrHLyfSAiG = false;}
      if(IBSAeBkmLP == true){IBSAeBkmLP = false;}
      if(BfNONVSeyl == true){BfNONVSeyl = false;}
      if(sajoggFeYc == true){sajoggFeYc = false;}
      if(pnJfqRpilm == true){pnJfqRpilm = false;}
      if(XzHdqIdsxb == true){XzHdqIdsxb = false;}
      if(MmBxNgRcSx == true){MmBxNgRcSx = false;}
      if(wFNhZMWgWu == true){wFNhZMWgWu = false;}
      if(ejsLNsTFxY == true){ejsLNsTFxY = false;}
      if(DMgwQCmLSK == true){DMgwQCmLSK = false;}
      if(zNPnqSkYEd == true){zNPnqSkYEd = false;}
      if(lwVCwcspiT == true){lwVCwcspiT = false;}
      if(NLfttjYRRW == true){NLfttjYRRW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKGSTWHVSX
{ 
  void pdYXtXEkOP()
  { 
      bool ALnsgPXonz = false;
      bool OYLkDFgJEB = false;
      bool QFZaYHsFtn = false;
      bool KiWuLcxknf = false;
      bool uJwkZJDhXa = false;
      bool RupiStlMUZ = false;
      bool WStzofCPYZ = false;
      bool IuUXFHJnBO = false;
      bool DKhTWPrnbR = false;
      bool pjQNJcOwut = false;
      bool HnIxRVZRcL = false;
      bool kxLFVLjacZ = false;
      bool mNmHiXdGOc = false;
      bool rNsHGPCjBA = false;
      bool oaKQfsYKqx = false;
      bool rnSVHsAAOs = false;
      bool qSCzTWEDyG = false;
      bool JzZbjLDWap = false;
      bool zSORkDtWAN = false;
      bool OBVHIVXKwI = false;
      string AmoHydHphD;
      string sTeyPuoQDg;
      string GsFRLPSLSd;
      string DEYTlXEyJt;
      string CcQXDLElsu;
      string YzOEVGgXwi;
      string LwXDAntKMr;
      string qqGJecbhNz;
      string KgRWFDoUxe;
      string pfBZiGFNXO;
      string RtYADgrFYs;
      string dzJxYddAyx;
      string zYMgCLpgZY;
      string XOKzgQHRTX;
      string KjuEApVEBE;
      string bEPZOrgryr;
      string qLeAUPoJPH;
      string WMgalPdHfM;
      string okeVwSyjjn;
      string iPTafyEtjj;
      if(AmoHydHphD == RtYADgrFYs){ALnsgPXonz = true;}
      else if(RtYADgrFYs == AmoHydHphD){HnIxRVZRcL = true;}
      if(sTeyPuoQDg == dzJxYddAyx){OYLkDFgJEB = true;}
      else if(dzJxYddAyx == sTeyPuoQDg){kxLFVLjacZ = true;}
      if(GsFRLPSLSd == zYMgCLpgZY){QFZaYHsFtn = true;}
      else if(zYMgCLpgZY == GsFRLPSLSd){mNmHiXdGOc = true;}
      if(DEYTlXEyJt == XOKzgQHRTX){KiWuLcxknf = true;}
      else if(XOKzgQHRTX == DEYTlXEyJt){rNsHGPCjBA = true;}
      if(CcQXDLElsu == KjuEApVEBE){uJwkZJDhXa = true;}
      else if(KjuEApVEBE == CcQXDLElsu){oaKQfsYKqx = true;}
      if(YzOEVGgXwi == bEPZOrgryr){RupiStlMUZ = true;}
      else if(bEPZOrgryr == YzOEVGgXwi){rnSVHsAAOs = true;}
      if(LwXDAntKMr == qLeAUPoJPH){WStzofCPYZ = true;}
      else if(qLeAUPoJPH == LwXDAntKMr){qSCzTWEDyG = true;}
      if(qqGJecbhNz == WMgalPdHfM){IuUXFHJnBO = true;}
      if(KgRWFDoUxe == okeVwSyjjn){DKhTWPrnbR = true;}
      if(pfBZiGFNXO == iPTafyEtjj){pjQNJcOwut = true;}
      while(WMgalPdHfM == qqGJecbhNz){JzZbjLDWap = true;}
      while(okeVwSyjjn == okeVwSyjjn){zSORkDtWAN = true;}
      while(iPTafyEtjj == iPTafyEtjj){OBVHIVXKwI = true;}
      if(ALnsgPXonz == true){ALnsgPXonz = false;}
      if(OYLkDFgJEB == true){OYLkDFgJEB = false;}
      if(QFZaYHsFtn == true){QFZaYHsFtn = false;}
      if(KiWuLcxknf == true){KiWuLcxknf = false;}
      if(uJwkZJDhXa == true){uJwkZJDhXa = false;}
      if(RupiStlMUZ == true){RupiStlMUZ = false;}
      if(WStzofCPYZ == true){WStzofCPYZ = false;}
      if(IuUXFHJnBO == true){IuUXFHJnBO = false;}
      if(DKhTWPrnbR == true){DKhTWPrnbR = false;}
      if(pjQNJcOwut == true){pjQNJcOwut = false;}
      if(HnIxRVZRcL == true){HnIxRVZRcL = false;}
      if(kxLFVLjacZ == true){kxLFVLjacZ = false;}
      if(mNmHiXdGOc == true){mNmHiXdGOc = false;}
      if(rNsHGPCjBA == true){rNsHGPCjBA = false;}
      if(oaKQfsYKqx == true){oaKQfsYKqx = false;}
      if(rnSVHsAAOs == true){rnSVHsAAOs = false;}
      if(qSCzTWEDyG == true){qSCzTWEDyG = false;}
      if(JzZbjLDWap == true){JzZbjLDWap = false;}
      if(zSORkDtWAN == true){zSORkDtWAN = false;}
      if(OBVHIVXKwI == true){OBVHIVXKwI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UIXODJFILI
{ 
  void cqyzJMxafi()
  { 
      bool NsfRjRTHib = false;
      bool TYSStfHjOw = false;
      bool xTUAyQJFJh = false;
      bool EcjXJkFLqn = false;
      bool PqePXLakHK = false;
      bool BixmStXeSS = false;
      bool IOxAWqntJJ = false;
      bool ZusagGoFbl = false;
      bool pXxzgVewEO = false;
      bool MarYeBsdsg = false;
      bool WfbyjFpWGM = false;
      bool ESCfcjQyTA = false;
      bool LrptwzCTue = false;
      bool MLMuPKwzOa = false;
      bool eHprKtXMwu = false;
      bool kuJrUephBk = false;
      bool CVbaArFHQR = false;
      bool nRjrVEByiC = false;
      bool bpXAtQCUZj = false;
      bool UOxcXJfOqR = false;
      string LYNrtHHNjF;
      string fORPaDYTwN;
      string FhDOQbmyqq;
      string MQJYuoItdX;
      string shJDTkWduE;
      string GEFYPcVzaR;
      string TIWsrPFsUl;
      string tdpYUWXzuf;
      string FJCljILjIR;
      string SJTLDjLQKD;
      string ecJJKbOfEr;
      string EWDtLJFjIj;
      string DVjCTkKdUj;
      string LHnqBcAsbH;
      string sefQNwFYAs;
      string dbIZAJrGoZ;
      string RkLTfxhMsi;
      string JMHAqYoTnW;
      string ekcaFjzNqr;
      string jsDCpITMjQ;
      if(LYNrtHHNjF == ecJJKbOfEr){NsfRjRTHib = true;}
      else if(ecJJKbOfEr == LYNrtHHNjF){WfbyjFpWGM = true;}
      if(fORPaDYTwN == EWDtLJFjIj){TYSStfHjOw = true;}
      else if(EWDtLJFjIj == fORPaDYTwN){ESCfcjQyTA = true;}
      if(FhDOQbmyqq == DVjCTkKdUj){xTUAyQJFJh = true;}
      else if(DVjCTkKdUj == FhDOQbmyqq){LrptwzCTue = true;}
      if(MQJYuoItdX == LHnqBcAsbH){EcjXJkFLqn = true;}
      else if(LHnqBcAsbH == MQJYuoItdX){MLMuPKwzOa = true;}
      if(shJDTkWduE == sefQNwFYAs){PqePXLakHK = true;}
      else if(sefQNwFYAs == shJDTkWduE){eHprKtXMwu = true;}
      if(GEFYPcVzaR == dbIZAJrGoZ){BixmStXeSS = true;}
      else if(dbIZAJrGoZ == GEFYPcVzaR){kuJrUephBk = true;}
      if(TIWsrPFsUl == RkLTfxhMsi){IOxAWqntJJ = true;}
      else if(RkLTfxhMsi == TIWsrPFsUl){CVbaArFHQR = true;}
      if(tdpYUWXzuf == JMHAqYoTnW){ZusagGoFbl = true;}
      if(FJCljILjIR == ekcaFjzNqr){pXxzgVewEO = true;}
      if(SJTLDjLQKD == jsDCpITMjQ){MarYeBsdsg = true;}
      while(JMHAqYoTnW == tdpYUWXzuf){nRjrVEByiC = true;}
      while(ekcaFjzNqr == ekcaFjzNqr){bpXAtQCUZj = true;}
      while(jsDCpITMjQ == jsDCpITMjQ){UOxcXJfOqR = true;}
      if(NsfRjRTHib == true){NsfRjRTHib = false;}
      if(TYSStfHjOw == true){TYSStfHjOw = false;}
      if(xTUAyQJFJh == true){xTUAyQJFJh = false;}
      if(EcjXJkFLqn == true){EcjXJkFLqn = false;}
      if(PqePXLakHK == true){PqePXLakHK = false;}
      if(BixmStXeSS == true){BixmStXeSS = false;}
      if(IOxAWqntJJ == true){IOxAWqntJJ = false;}
      if(ZusagGoFbl == true){ZusagGoFbl = false;}
      if(pXxzgVewEO == true){pXxzgVewEO = false;}
      if(MarYeBsdsg == true){MarYeBsdsg = false;}
      if(WfbyjFpWGM == true){WfbyjFpWGM = false;}
      if(ESCfcjQyTA == true){ESCfcjQyTA = false;}
      if(LrptwzCTue == true){LrptwzCTue = false;}
      if(MLMuPKwzOa == true){MLMuPKwzOa = false;}
      if(eHprKtXMwu == true){eHprKtXMwu = false;}
      if(kuJrUephBk == true){kuJrUephBk = false;}
      if(CVbaArFHQR == true){CVbaArFHQR = false;}
      if(nRjrVEByiC == true){nRjrVEByiC = false;}
      if(bpXAtQCUZj == true){bpXAtQCUZj = false;}
      if(UOxcXJfOqR == true){UOxcXJfOqR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEOLGOPVBU
{ 
  void VBhmHHWeRP()
  { 
      bool JYRTEGBeLd = false;
      bool cRonprAxeU = false;
      bool jNRNJRRKcZ = false;
      bool SZqVCCEsVd = false;
      bool BnDCGKnJFT = false;
      bool hLwZkuGDJl = false;
      bool nqBlLDaTlm = false;
      bool nGbBSwJPGz = false;
      bool cHFIqGdQkG = false;
      bool wAjioKlQpD = false;
      bool iUXRfbjuHn = false;
      bool lqxKJfkruE = false;
      bool YKheqmWsLH = false;
      bool JrYCPHjncP = false;
      bool WiIwUEDYYI = false;
      bool ZtVkdXmrZr = false;
      bool EpiAesRtuB = false;
      bool wxPehpCkJl = false;
      bool jxTDhPVmXq = false;
      bool UrNkKfAIRb = false;
      string VdBDQECIqj;
      string ESgLRLqfKf;
      string QGKKFGmsIu;
      string EOSZfTBaka;
      string rcgDGVQdwb;
      string RbiIWPTpxK;
      string RJAufpAHfy;
      string KQtjnmYGEj;
      string pJwfdcfJCP;
      string zKdaIhblWQ;
      string UIxyRBgyUi;
      string pMlNTHMTRD;
      string JpEQyzlTaF;
      string LmimOgLxNb;
      string ugoSYlXPGA;
      string VHTTGdEgAS;
      string ONXOXDcyym;
      string wOGoHbAlqL;
      string bVMZjDSPgj;
      string cdxuMhJauU;
      if(VdBDQECIqj == UIxyRBgyUi){JYRTEGBeLd = true;}
      else if(UIxyRBgyUi == VdBDQECIqj){iUXRfbjuHn = true;}
      if(ESgLRLqfKf == pMlNTHMTRD){cRonprAxeU = true;}
      else if(pMlNTHMTRD == ESgLRLqfKf){lqxKJfkruE = true;}
      if(QGKKFGmsIu == JpEQyzlTaF){jNRNJRRKcZ = true;}
      else if(JpEQyzlTaF == QGKKFGmsIu){YKheqmWsLH = true;}
      if(EOSZfTBaka == LmimOgLxNb){SZqVCCEsVd = true;}
      else if(LmimOgLxNb == EOSZfTBaka){JrYCPHjncP = true;}
      if(rcgDGVQdwb == ugoSYlXPGA){BnDCGKnJFT = true;}
      else if(ugoSYlXPGA == rcgDGVQdwb){WiIwUEDYYI = true;}
      if(RbiIWPTpxK == VHTTGdEgAS){hLwZkuGDJl = true;}
      else if(VHTTGdEgAS == RbiIWPTpxK){ZtVkdXmrZr = true;}
      if(RJAufpAHfy == ONXOXDcyym){nqBlLDaTlm = true;}
      else if(ONXOXDcyym == RJAufpAHfy){EpiAesRtuB = true;}
      if(KQtjnmYGEj == wOGoHbAlqL){nGbBSwJPGz = true;}
      if(pJwfdcfJCP == bVMZjDSPgj){cHFIqGdQkG = true;}
      if(zKdaIhblWQ == cdxuMhJauU){wAjioKlQpD = true;}
      while(wOGoHbAlqL == KQtjnmYGEj){wxPehpCkJl = true;}
      while(bVMZjDSPgj == bVMZjDSPgj){jxTDhPVmXq = true;}
      while(cdxuMhJauU == cdxuMhJauU){UrNkKfAIRb = true;}
      if(JYRTEGBeLd == true){JYRTEGBeLd = false;}
      if(cRonprAxeU == true){cRonprAxeU = false;}
      if(jNRNJRRKcZ == true){jNRNJRRKcZ = false;}
      if(SZqVCCEsVd == true){SZqVCCEsVd = false;}
      if(BnDCGKnJFT == true){BnDCGKnJFT = false;}
      if(hLwZkuGDJl == true){hLwZkuGDJl = false;}
      if(nqBlLDaTlm == true){nqBlLDaTlm = false;}
      if(nGbBSwJPGz == true){nGbBSwJPGz = false;}
      if(cHFIqGdQkG == true){cHFIqGdQkG = false;}
      if(wAjioKlQpD == true){wAjioKlQpD = false;}
      if(iUXRfbjuHn == true){iUXRfbjuHn = false;}
      if(lqxKJfkruE == true){lqxKJfkruE = false;}
      if(YKheqmWsLH == true){YKheqmWsLH = false;}
      if(JrYCPHjncP == true){JrYCPHjncP = false;}
      if(WiIwUEDYYI == true){WiIwUEDYYI = false;}
      if(ZtVkdXmrZr == true){ZtVkdXmrZr = false;}
      if(EpiAesRtuB == true){EpiAesRtuB = false;}
      if(wxPehpCkJl == true){wxPehpCkJl = false;}
      if(jxTDhPVmXq == true){jxTDhPVmXq = false;}
      if(UrNkKfAIRb == true){UrNkKfAIRb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LIIDSERDAE
{ 
  void EOXrOhYpKi()
  { 
      bool octItxzgUk = false;
      bool akdNohcjYb = false;
      bool koumRiZGJV = false;
      bool hxnUopQCrt = false;
      bool tsKDSpQwGW = false;
      bool kuLygAgHpK = false;
      bool XsWzDcwJXz = false;
      bool QZqehrdrUb = false;
      bool RcAljlkomo = false;
      bool IJMhVBVLzo = false;
      bool sHXGFLDgQo = false;
      bool WnlOrtrjOQ = false;
      bool rGViqHNJIg = false;
      bool VRrfhKFtgY = false;
      bool iDYySTXxoa = false;
      bool IkxhwlloPy = false;
      bool ytXiSEwGfh = false;
      bool oyDphnhWQW = false;
      bool jPUhYjUJiu = false;
      bool XPdiZofoeN = false;
      string AmubwCDzDc;
      string uCYDDgZSis;
      string RlGSEjMczH;
      string ntcsYxOehH;
      string xKGePOtOoG;
      string akKlaNgbWL;
      string paAuoAYfdG;
      string RtjbwHfaDp;
      string pymrgDjqRL;
      string PlHWQVKKpO;
      string oOjingBhpT;
      string gFYgUrnHOl;
      string PhNRpflMLZ;
      string xVjnAbNDEz;
      string BCAydKNaBY;
      string hCuEzHARsI;
      string tnWPWLUjfs;
      string ejCOjNgPne;
      string SLLlqtZfos;
      string auKwFNejaS;
      if(AmubwCDzDc == oOjingBhpT){octItxzgUk = true;}
      else if(oOjingBhpT == AmubwCDzDc){sHXGFLDgQo = true;}
      if(uCYDDgZSis == gFYgUrnHOl){akdNohcjYb = true;}
      else if(gFYgUrnHOl == uCYDDgZSis){WnlOrtrjOQ = true;}
      if(RlGSEjMczH == PhNRpflMLZ){koumRiZGJV = true;}
      else if(PhNRpflMLZ == RlGSEjMczH){rGViqHNJIg = true;}
      if(ntcsYxOehH == xVjnAbNDEz){hxnUopQCrt = true;}
      else if(xVjnAbNDEz == ntcsYxOehH){VRrfhKFtgY = true;}
      if(xKGePOtOoG == BCAydKNaBY){tsKDSpQwGW = true;}
      else if(BCAydKNaBY == xKGePOtOoG){iDYySTXxoa = true;}
      if(akKlaNgbWL == hCuEzHARsI){kuLygAgHpK = true;}
      else if(hCuEzHARsI == akKlaNgbWL){IkxhwlloPy = true;}
      if(paAuoAYfdG == tnWPWLUjfs){XsWzDcwJXz = true;}
      else if(tnWPWLUjfs == paAuoAYfdG){ytXiSEwGfh = true;}
      if(RtjbwHfaDp == ejCOjNgPne){QZqehrdrUb = true;}
      if(pymrgDjqRL == SLLlqtZfos){RcAljlkomo = true;}
      if(PlHWQVKKpO == auKwFNejaS){IJMhVBVLzo = true;}
      while(ejCOjNgPne == RtjbwHfaDp){oyDphnhWQW = true;}
      while(SLLlqtZfos == SLLlqtZfos){jPUhYjUJiu = true;}
      while(auKwFNejaS == auKwFNejaS){XPdiZofoeN = true;}
      if(octItxzgUk == true){octItxzgUk = false;}
      if(akdNohcjYb == true){akdNohcjYb = false;}
      if(koumRiZGJV == true){koumRiZGJV = false;}
      if(hxnUopQCrt == true){hxnUopQCrt = false;}
      if(tsKDSpQwGW == true){tsKDSpQwGW = false;}
      if(kuLygAgHpK == true){kuLygAgHpK = false;}
      if(XsWzDcwJXz == true){XsWzDcwJXz = false;}
      if(QZqehrdrUb == true){QZqehrdrUb = false;}
      if(RcAljlkomo == true){RcAljlkomo = false;}
      if(IJMhVBVLzo == true){IJMhVBVLzo = false;}
      if(sHXGFLDgQo == true){sHXGFLDgQo = false;}
      if(WnlOrtrjOQ == true){WnlOrtrjOQ = false;}
      if(rGViqHNJIg == true){rGViqHNJIg = false;}
      if(VRrfhKFtgY == true){VRrfhKFtgY = false;}
      if(iDYySTXxoa == true){iDYySTXxoa = false;}
      if(IkxhwlloPy == true){IkxhwlloPy = false;}
      if(ytXiSEwGfh == true){ytXiSEwGfh = false;}
      if(oyDphnhWQW == true){oyDphnhWQW = false;}
      if(jPUhYjUJiu == true){jPUhYjUJiu = false;}
      if(XPdiZofoeN == true){XPdiZofoeN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXVOAPYPJQ
{ 
  void PVLdcwKdZL()
  { 
      bool WowBONlASQ = false;
      bool GYTpgTDIVC = false;
      bool yPdhoRgHhI = false;
      bool ZRSFcZWGNt = false;
      bool dSzxsabbjQ = false;
      bool DGsEBGLNLx = false;
      bool fdRKqnGONG = false;
      bool wxuaYfQgoN = false;
      bool oEWRFTYNDV = false;
      bool OItQNzAoFE = false;
      bool UMOdTFKRfV = false;
      bool peYyHaGAEX = false;
      bool PsLqrmCeMY = false;
      bool ebajrcpsxz = false;
      bool IHggfjjwIm = false;
      bool rAjhobAWlf = false;
      bool DfEHqODnFe = false;
      bool kNCEPHLeLI = false;
      bool DGVZgeqsuQ = false;
      bool bSHRwbCZpQ = false;
      string AlTGFPNqoV;
      string dFFNjRYBhj;
      string TBlphQLxwq;
      string OymlToXZVQ;
      string otGVafRqqm;
      string inHtTyAcYn;
      string EQuxGeRSst;
      string syeRtZtQPB;
      string yTGIHZprSV;
      string ouBgMYyIOu;
      string NyxwtjIpzs;
      string DjMWpjKmpf;
      string oZzXFxxyEV;
      string alBUnzVJNW;
      string QArZRFhdqc;
      string NLSiFnzZpw;
      string mKkdRRhrhp;
      string NAYSPogZFA;
      string PSHbHPSSOA;
      string AwSRjGOOHA;
      if(AlTGFPNqoV == NyxwtjIpzs){WowBONlASQ = true;}
      else if(NyxwtjIpzs == AlTGFPNqoV){UMOdTFKRfV = true;}
      if(dFFNjRYBhj == DjMWpjKmpf){GYTpgTDIVC = true;}
      else if(DjMWpjKmpf == dFFNjRYBhj){peYyHaGAEX = true;}
      if(TBlphQLxwq == oZzXFxxyEV){yPdhoRgHhI = true;}
      else if(oZzXFxxyEV == TBlphQLxwq){PsLqrmCeMY = true;}
      if(OymlToXZVQ == alBUnzVJNW){ZRSFcZWGNt = true;}
      else if(alBUnzVJNW == OymlToXZVQ){ebajrcpsxz = true;}
      if(otGVafRqqm == QArZRFhdqc){dSzxsabbjQ = true;}
      else if(QArZRFhdqc == otGVafRqqm){IHggfjjwIm = true;}
      if(inHtTyAcYn == NLSiFnzZpw){DGsEBGLNLx = true;}
      else if(NLSiFnzZpw == inHtTyAcYn){rAjhobAWlf = true;}
      if(EQuxGeRSst == mKkdRRhrhp){fdRKqnGONG = true;}
      else if(mKkdRRhrhp == EQuxGeRSst){DfEHqODnFe = true;}
      if(syeRtZtQPB == NAYSPogZFA){wxuaYfQgoN = true;}
      if(yTGIHZprSV == PSHbHPSSOA){oEWRFTYNDV = true;}
      if(ouBgMYyIOu == AwSRjGOOHA){OItQNzAoFE = true;}
      while(NAYSPogZFA == syeRtZtQPB){kNCEPHLeLI = true;}
      while(PSHbHPSSOA == PSHbHPSSOA){DGVZgeqsuQ = true;}
      while(AwSRjGOOHA == AwSRjGOOHA){bSHRwbCZpQ = true;}
      if(WowBONlASQ == true){WowBONlASQ = false;}
      if(GYTpgTDIVC == true){GYTpgTDIVC = false;}
      if(yPdhoRgHhI == true){yPdhoRgHhI = false;}
      if(ZRSFcZWGNt == true){ZRSFcZWGNt = false;}
      if(dSzxsabbjQ == true){dSzxsabbjQ = false;}
      if(DGsEBGLNLx == true){DGsEBGLNLx = false;}
      if(fdRKqnGONG == true){fdRKqnGONG = false;}
      if(wxuaYfQgoN == true){wxuaYfQgoN = false;}
      if(oEWRFTYNDV == true){oEWRFTYNDV = false;}
      if(OItQNzAoFE == true){OItQNzAoFE = false;}
      if(UMOdTFKRfV == true){UMOdTFKRfV = false;}
      if(peYyHaGAEX == true){peYyHaGAEX = false;}
      if(PsLqrmCeMY == true){PsLqrmCeMY = false;}
      if(ebajrcpsxz == true){ebajrcpsxz = false;}
      if(IHggfjjwIm == true){IHggfjjwIm = false;}
      if(rAjhobAWlf == true){rAjhobAWlf = false;}
      if(DfEHqODnFe == true){DfEHqODnFe = false;}
      if(kNCEPHLeLI == true){kNCEPHLeLI = false;}
      if(DGVZgeqsuQ == true){DGVZgeqsuQ = false;}
      if(bSHRwbCZpQ == true){bSHRwbCZpQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AAEUSLNPHJ
{ 
  void cHIiouwbVy()
  { 
      bool DEwCgayuWj = false;
      bool bNYQwzCQEE = false;
      bool ImWQAYSaxH = false;
      bool jrcQzFAGPi = false;
      bool qsGeKtwleE = false;
      bool MFiaIPhfBH = false;
      bool HXxPzikHQp = false;
      bool zuBUMOfqGF = false;
      bool cfustdIBIj = false;
      bool WUFIbTwqfa = false;
      bool JnVoEREOOs = false;
      bool iqZudabEUU = false;
      bool aiyfSeossr = false;
      bool SoLewnKGnc = false;
      bool ZtlPAftJdA = false;
      bool qqWKAZpoVZ = false;
      bool bLUWZtftzp = false;
      bool PUPqufxifm = false;
      bool jfOsAaRAeV = false;
      bool yVkOBOYPoF = false;
      string xEQJOgpPVU;
      string jqZMjEPBRp;
      string rdGidmejma;
      string PXldRFRZcx;
      string uOttttBzVu;
      string hGDPQTyhea;
      string BGbuFLEwue;
      string lpYTudjLoi;
      string kfNqrITWMy;
      string HjtCwolyoh;
      string pFEqIrhjUm;
      string imswoVrkCw;
      string qhixXCuVWG;
      string rkVGsfbWhA;
      string ajCZOTqyMa;
      string wBwrqHWGTG;
      string wLNNtxQlCJ;
      string tVCBVHfIhD;
      string KwJwJpocPl;
      string IUCaEOWneQ;
      if(xEQJOgpPVU == pFEqIrhjUm){DEwCgayuWj = true;}
      else if(pFEqIrhjUm == xEQJOgpPVU){JnVoEREOOs = true;}
      if(jqZMjEPBRp == imswoVrkCw){bNYQwzCQEE = true;}
      else if(imswoVrkCw == jqZMjEPBRp){iqZudabEUU = true;}
      if(rdGidmejma == qhixXCuVWG){ImWQAYSaxH = true;}
      else if(qhixXCuVWG == rdGidmejma){aiyfSeossr = true;}
      if(PXldRFRZcx == rkVGsfbWhA){jrcQzFAGPi = true;}
      else if(rkVGsfbWhA == PXldRFRZcx){SoLewnKGnc = true;}
      if(uOttttBzVu == ajCZOTqyMa){qsGeKtwleE = true;}
      else if(ajCZOTqyMa == uOttttBzVu){ZtlPAftJdA = true;}
      if(hGDPQTyhea == wBwrqHWGTG){MFiaIPhfBH = true;}
      else if(wBwrqHWGTG == hGDPQTyhea){qqWKAZpoVZ = true;}
      if(BGbuFLEwue == wLNNtxQlCJ){HXxPzikHQp = true;}
      else if(wLNNtxQlCJ == BGbuFLEwue){bLUWZtftzp = true;}
      if(lpYTudjLoi == tVCBVHfIhD){zuBUMOfqGF = true;}
      if(kfNqrITWMy == KwJwJpocPl){cfustdIBIj = true;}
      if(HjtCwolyoh == IUCaEOWneQ){WUFIbTwqfa = true;}
      while(tVCBVHfIhD == lpYTudjLoi){PUPqufxifm = true;}
      while(KwJwJpocPl == KwJwJpocPl){jfOsAaRAeV = true;}
      while(IUCaEOWneQ == IUCaEOWneQ){yVkOBOYPoF = true;}
      if(DEwCgayuWj == true){DEwCgayuWj = false;}
      if(bNYQwzCQEE == true){bNYQwzCQEE = false;}
      if(ImWQAYSaxH == true){ImWQAYSaxH = false;}
      if(jrcQzFAGPi == true){jrcQzFAGPi = false;}
      if(qsGeKtwleE == true){qsGeKtwleE = false;}
      if(MFiaIPhfBH == true){MFiaIPhfBH = false;}
      if(HXxPzikHQp == true){HXxPzikHQp = false;}
      if(zuBUMOfqGF == true){zuBUMOfqGF = false;}
      if(cfustdIBIj == true){cfustdIBIj = false;}
      if(WUFIbTwqfa == true){WUFIbTwqfa = false;}
      if(JnVoEREOOs == true){JnVoEREOOs = false;}
      if(iqZudabEUU == true){iqZudabEUU = false;}
      if(aiyfSeossr == true){aiyfSeossr = false;}
      if(SoLewnKGnc == true){SoLewnKGnc = false;}
      if(ZtlPAftJdA == true){ZtlPAftJdA = false;}
      if(qqWKAZpoVZ == true){qqWKAZpoVZ = false;}
      if(bLUWZtftzp == true){bLUWZtftzp = false;}
      if(PUPqufxifm == true){PUPqufxifm = false;}
      if(jfOsAaRAeV == true){jfOsAaRAeV = false;}
      if(yVkOBOYPoF == true){yVkOBOYPoF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLQMCSQGFA
{ 
  void UEnnZVmciV()
  { 
      bool hZlyYcKtsY = false;
      bool bOtSrmbZHy = false;
      bool nIwlHxsdUH = false;
      bool UDFmnLGRSf = false;
      bool qBmGEXpiTW = false;
      bool ZArAeYcApa = false;
      bool igZkDYIGdf = false;
      bool gJGbHmVphi = false;
      bool GKJxhULFIP = false;
      bool hFbqwJbCCe = false;
      bool OjEnoQsPrq = false;
      bool DmSHUXXbCi = false;
      bool NDyOxbhOex = false;
      bool KTnCTWFVIQ = false;
      bool auMQMumTWX = false;
      bool lAzSRLkppN = false;
      bool iektfizPmx = false;
      bool SBSlIRqgCC = false;
      bool nNrHLKUUjI = false;
      bool lPethwKSjc = false;
      string cIfZjnGcVA;
      string zkuxsSBZWQ;
      string GFwDmGWtne;
      string AEEoeGDVWs;
      string XVnGAdcaUf;
      string JEuqmWMcmd;
      string QLoqzufFRl;
      string OfCcsjRoDJ;
      string cwZIUuJNCI;
      string saiscLgwGE;
      string xWJhRdBRxC;
      string FWZdAUlfWD;
      string lSDIsmxJAg;
      string CVhyLFlqpq;
      string tqPzCWBErH;
      string YAZCSeSAod;
      string frRPAjnaSt;
      string iupeJtCEGW;
      string lrQrIBufef;
      string mkBMKBZzyS;
      if(cIfZjnGcVA == xWJhRdBRxC){hZlyYcKtsY = true;}
      else if(xWJhRdBRxC == cIfZjnGcVA){OjEnoQsPrq = true;}
      if(zkuxsSBZWQ == FWZdAUlfWD){bOtSrmbZHy = true;}
      else if(FWZdAUlfWD == zkuxsSBZWQ){DmSHUXXbCi = true;}
      if(GFwDmGWtne == lSDIsmxJAg){nIwlHxsdUH = true;}
      else if(lSDIsmxJAg == GFwDmGWtne){NDyOxbhOex = true;}
      if(AEEoeGDVWs == CVhyLFlqpq){UDFmnLGRSf = true;}
      else if(CVhyLFlqpq == AEEoeGDVWs){KTnCTWFVIQ = true;}
      if(XVnGAdcaUf == tqPzCWBErH){qBmGEXpiTW = true;}
      else if(tqPzCWBErH == XVnGAdcaUf){auMQMumTWX = true;}
      if(JEuqmWMcmd == YAZCSeSAod){ZArAeYcApa = true;}
      else if(YAZCSeSAod == JEuqmWMcmd){lAzSRLkppN = true;}
      if(QLoqzufFRl == frRPAjnaSt){igZkDYIGdf = true;}
      else if(frRPAjnaSt == QLoqzufFRl){iektfizPmx = true;}
      if(OfCcsjRoDJ == iupeJtCEGW){gJGbHmVphi = true;}
      if(cwZIUuJNCI == lrQrIBufef){GKJxhULFIP = true;}
      if(saiscLgwGE == mkBMKBZzyS){hFbqwJbCCe = true;}
      while(iupeJtCEGW == OfCcsjRoDJ){SBSlIRqgCC = true;}
      while(lrQrIBufef == lrQrIBufef){nNrHLKUUjI = true;}
      while(mkBMKBZzyS == mkBMKBZzyS){lPethwKSjc = true;}
      if(hZlyYcKtsY == true){hZlyYcKtsY = false;}
      if(bOtSrmbZHy == true){bOtSrmbZHy = false;}
      if(nIwlHxsdUH == true){nIwlHxsdUH = false;}
      if(UDFmnLGRSf == true){UDFmnLGRSf = false;}
      if(qBmGEXpiTW == true){qBmGEXpiTW = false;}
      if(ZArAeYcApa == true){ZArAeYcApa = false;}
      if(igZkDYIGdf == true){igZkDYIGdf = false;}
      if(gJGbHmVphi == true){gJGbHmVphi = false;}
      if(GKJxhULFIP == true){GKJxhULFIP = false;}
      if(hFbqwJbCCe == true){hFbqwJbCCe = false;}
      if(OjEnoQsPrq == true){OjEnoQsPrq = false;}
      if(DmSHUXXbCi == true){DmSHUXXbCi = false;}
      if(NDyOxbhOex == true){NDyOxbhOex = false;}
      if(KTnCTWFVIQ == true){KTnCTWFVIQ = false;}
      if(auMQMumTWX == true){auMQMumTWX = false;}
      if(lAzSRLkppN == true){lAzSRLkppN = false;}
      if(iektfizPmx == true){iektfizPmx = false;}
      if(SBSlIRqgCC == true){SBSlIRqgCC = false;}
      if(nNrHLKUUjI == true){nNrHLKUUjI = false;}
      if(lPethwKSjc == true){lPethwKSjc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMMHFRIXXE
{ 
  void UlBsPqZpxP()
  { 
      bool GcabFzetiP = false;
      bool GbuthAOKIw = false;
      bool ilQqGiPGlO = false;
      bool xWTLHqSbji = false;
      bool QzkZAQjNtA = false;
      bool PktOQTLiVW = false;
      bool iXIUSjIilp = false;
      bool glZYejApqo = false;
      bool yBMlyLcEun = false;
      bool fjGMAspQHQ = false;
      bool IAbDSdKUjg = false;
      bool SUrgXhKVVG = false;
      bool HDnxKxfMYk = false;
      bool siiZgyYJSU = false;
      bool AHTNUKqZoS = false;
      bool iUuBIEMdsV = false;
      bool xywznjlRzZ = false;
      bool IADAFziZcz = false;
      bool FGXFBXngQb = false;
      bool ktQwWCLUZk = false;
      string xsnXDcWrum;
      string pQhyhkRReT;
      string UAXmyQwfoD;
      string zuFtdnplMA;
      string CfHGrKbPeB;
      string tDoOpxVAZm;
      string fpCqmuKmUt;
      string tfEdRnrQum;
      string ngBmJwGqEg;
      string RoLYTLdQTw;
      string zotjHNyKxB;
      string EEFlyzoPhq;
      string nThnbETeJF;
      string JbxymzlQfu;
      string xwtCbNjZaT;
      string WOhbIfGGID;
      string tSAqqcHHyy;
      string NXjmsrZeLO;
      string UtEphusUpH;
      string reIcAeuCLz;
      if(xsnXDcWrum == zotjHNyKxB){GcabFzetiP = true;}
      else if(zotjHNyKxB == xsnXDcWrum){IAbDSdKUjg = true;}
      if(pQhyhkRReT == EEFlyzoPhq){GbuthAOKIw = true;}
      else if(EEFlyzoPhq == pQhyhkRReT){SUrgXhKVVG = true;}
      if(UAXmyQwfoD == nThnbETeJF){ilQqGiPGlO = true;}
      else if(nThnbETeJF == UAXmyQwfoD){HDnxKxfMYk = true;}
      if(zuFtdnplMA == JbxymzlQfu){xWTLHqSbji = true;}
      else if(JbxymzlQfu == zuFtdnplMA){siiZgyYJSU = true;}
      if(CfHGrKbPeB == xwtCbNjZaT){QzkZAQjNtA = true;}
      else if(xwtCbNjZaT == CfHGrKbPeB){AHTNUKqZoS = true;}
      if(tDoOpxVAZm == WOhbIfGGID){PktOQTLiVW = true;}
      else if(WOhbIfGGID == tDoOpxVAZm){iUuBIEMdsV = true;}
      if(fpCqmuKmUt == tSAqqcHHyy){iXIUSjIilp = true;}
      else if(tSAqqcHHyy == fpCqmuKmUt){xywznjlRzZ = true;}
      if(tfEdRnrQum == NXjmsrZeLO){glZYejApqo = true;}
      if(ngBmJwGqEg == UtEphusUpH){yBMlyLcEun = true;}
      if(RoLYTLdQTw == reIcAeuCLz){fjGMAspQHQ = true;}
      while(NXjmsrZeLO == tfEdRnrQum){IADAFziZcz = true;}
      while(UtEphusUpH == UtEphusUpH){FGXFBXngQb = true;}
      while(reIcAeuCLz == reIcAeuCLz){ktQwWCLUZk = true;}
      if(GcabFzetiP == true){GcabFzetiP = false;}
      if(GbuthAOKIw == true){GbuthAOKIw = false;}
      if(ilQqGiPGlO == true){ilQqGiPGlO = false;}
      if(xWTLHqSbji == true){xWTLHqSbji = false;}
      if(QzkZAQjNtA == true){QzkZAQjNtA = false;}
      if(PktOQTLiVW == true){PktOQTLiVW = false;}
      if(iXIUSjIilp == true){iXIUSjIilp = false;}
      if(glZYejApqo == true){glZYejApqo = false;}
      if(yBMlyLcEun == true){yBMlyLcEun = false;}
      if(fjGMAspQHQ == true){fjGMAspQHQ = false;}
      if(IAbDSdKUjg == true){IAbDSdKUjg = false;}
      if(SUrgXhKVVG == true){SUrgXhKVVG = false;}
      if(HDnxKxfMYk == true){HDnxKxfMYk = false;}
      if(siiZgyYJSU == true){siiZgyYJSU = false;}
      if(AHTNUKqZoS == true){AHTNUKqZoS = false;}
      if(iUuBIEMdsV == true){iUuBIEMdsV = false;}
      if(xywznjlRzZ == true){xywznjlRzZ = false;}
      if(IADAFziZcz == true){IADAFziZcz = false;}
      if(FGXFBXngQb == true){FGXFBXngQb = false;}
      if(ktQwWCLUZk == true){ktQwWCLUZk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNUNGLJUWX
{ 
  void OjaoiyYAEp()
  { 
      bool jZeioIFCZx = false;
      bool JVhIVNWEqF = false;
      bool kyIdiObUWW = false;
      bool ihxYMaEwIj = false;
      bool IBZtjibBxD = false;
      bool eBRirlRBzZ = false;
      bool gjfCOaYJut = false;
      bool IZwHwjXOtA = false;
      bool laXSqgQNfa = false;
      bool JDxhDYVXeI = false;
      bool JSFCuFFJlI = false;
      bool NDGznFLMKg = false;
      bool KLcUjEcNDW = false;
      bool NAikpTVUWl = false;
      bool bGaWMGwytx = false;
      bool MIMyyyojSq = false;
      bool brGOuNTVIT = false;
      bool jppXEDjFId = false;
      bool HdSFKEnjlq = false;
      bool dlCfJjALby = false;
      string LjTYKRzkJr;
      string IVUCadpYIb;
      string VmEYVrpzSD;
      string AkUqbNybsL;
      string tpzXJndjyd;
      string BmLDHXetCR;
      string aASFrXBcaN;
      string fNfwgenfPh;
      string OFAnCMYQjD;
      string hEYbjtXsfk;
      string lAJkymHPWb;
      string jzdUCVAdDe;
      string yksWfboEMl;
      string HtAduNwOpP;
      string FJsHTiZEYO;
      string sspAmBHlFW;
      string yCCjToyzYo;
      string YknnZoqkDw;
      string BjfyrODAqt;
      string FKJSRCGInd;
      if(LjTYKRzkJr == lAJkymHPWb){jZeioIFCZx = true;}
      else if(lAJkymHPWb == LjTYKRzkJr){JSFCuFFJlI = true;}
      if(IVUCadpYIb == jzdUCVAdDe){JVhIVNWEqF = true;}
      else if(jzdUCVAdDe == IVUCadpYIb){NDGznFLMKg = true;}
      if(VmEYVrpzSD == yksWfboEMl){kyIdiObUWW = true;}
      else if(yksWfboEMl == VmEYVrpzSD){KLcUjEcNDW = true;}
      if(AkUqbNybsL == HtAduNwOpP){ihxYMaEwIj = true;}
      else if(HtAduNwOpP == AkUqbNybsL){NAikpTVUWl = true;}
      if(tpzXJndjyd == FJsHTiZEYO){IBZtjibBxD = true;}
      else if(FJsHTiZEYO == tpzXJndjyd){bGaWMGwytx = true;}
      if(BmLDHXetCR == sspAmBHlFW){eBRirlRBzZ = true;}
      else if(sspAmBHlFW == BmLDHXetCR){MIMyyyojSq = true;}
      if(aASFrXBcaN == yCCjToyzYo){gjfCOaYJut = true;}
      else if(yCCjToyzYo == aASFrXBcaN){brGOuNTVIT = true;}
      if(fNfwgenfPh == YknnZoqkDw){IZwHwjXOtA = true;}
      if(OFAnCMYQjD == BjfyrODAqt){laXSqgQNfa = true;}
      if(hEYbjtXsfk == FKJSRCGInd){JDxhDYVXeI = true;}
      while(YknnZoqkDw == fNfwgenfPh){jppXEDjFId = true;}
      while(BjfyrODAqt == BjfyrODAqt){HdSFKEnjlq = true;}
      while(FKJSRCGInd == FKJSRCGInd){dlCfJjALby = true;}
      if(jZeioIFCZx == true){jZeioIFCZx = false;}
      if(JVhIVNWEqF == true){JVhIVNWEqF = false;}
      if(kyIdiObUWW == true){kyIdiObUWW = false;}
      if(ihxYMaEwIj == true){ihxYMaEwIj = false;}
      if(IBZtjibBxD == true){IBZtjibBxD = false;}
      if(eBRirlRBzZ == true){eBRirlRBzZ = false;}
      if(gjfCOaYJut == true){gjfCOaYJut = false;}
      if(IZwHwjXOtA == true){IZwHwjXOtA = false;}
      if(laXSqgQNfa == true){laXSqgQNfa = false;}
      if(JDxhDYVXeI == true){JDxhDYVXeI = false;}
      if(JSFCuFFJlI == true){JSFCuFFJlI = false;}
      if(NDGznFLMKg == true){NDGznFLMKg = false;}
      if(KLcUjEcNDW == true){KLcUjEcNDW = false;}
      if(NAikpTVUWl == true){NAikpTVUWl = false;}
      if(bGaWMGwytx == true){bGaWMGwytx = false;}
      if(MIMyyyojSq == true){MIMyyyojSq = false;}
      if(brGOuNTVIT == true){brGOuNTVIT = false;}
      if(jppXEDjFId == true){jppXEDjFId = false;}
      if(HdSFKEnjlq == true){HdSFKEnjlq = false;}
      if(dlCfJjALby == true){dlCfJjALby = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQNRXSFPVO
{ 
  void dOCTFHilHB()
  { 
      bool nbLTYnkJUp = false;
      bool mAcqVVrlhn = false;
      bool zNzWBQRlyr = false;
      bool swMoEKbIsZ = false;
      bool ZryZwsGmEj = false;
      bool AExmaabnSI = false;
      bool WyLbwqnnlL = false;
      bool sjsIOHOZaI = false;
      bool KdhOrnyZOd = false;
      bool inpkCagWcE = false;
      bool ESArpPLnXT = false;
      bool LCNJxrPwjH = false;
      bool sOYIcFtHGm = false;
      bool arxVDrcoXc = false;
      bool cJBuRgZfmK = false;
      bool KjmULpsrPk = false;
      bool VDhjrTErFF = false;
      bool OaXHeiMdpw = false;
      bool eNTucqFbJM = false;
      bool zkZmGYaQCy = false;
      string ysrsyUhBgx;
      string TmqtHekplP;
      string PhHlQkgHif;
      string XoLsJODDFp;
      string VMidlwAUrN;
      string zxtnKQkGbN;
      string naSBYdbxkr;
      string ahjutCydzU;
      string jLOVgauWis;
      string cxarCuthEI;
      string UCjzlQMytH;
      string RHGHcbLwTy;
      string hEOqPdHrsy;
      string IPZqAgbOiP;
      string NxbabVqSPZ;
      string jxOFaPnrjI;
      string JUFwzBgPHu;
      string AwMEkkbnPs;
      string lnbSNKBTPj;
      string sieaFrqfaZ;
      if(ysrsyUhBgx == UCjzlQMytH){nbLTYnkJUp = true;}
      else if(UCjzlQMytH == ysrsyUhBgx){ESArpPLnXT = true;}
      if(TmqtHekplP == RHGHcbLwTy){mAcqVVrlhn = true;}
      else if(RHGHcbLwTy == TmqtHekplP){LCNJxrPwjH = true;}
      if(PhHlQkgHif == hEOqPdHrsy){zNzWBQRlyr = true;}
      else if(hEOqPdHrsy == PhHlQkgHif){sOYIcFtHGm = true;}
      if(XoLsJODDFp == IPZqAgbOiP){swMoEKbIsZ = true;}
      else if(IPZqAgbOiP == XoLsJODDFp){arxVDrcoXc = true;}
      if(VMidlwAUrN == NxbabVqSPZ){ZryZwsGmEj = true;}
      else if(NxbabVqSPZ == VMidlwAUrN){cJBuRgZfmK = true;}
      if(zxtnKQkGbN == jxOFaPnrjI){AExmaabnSI = true;}
      else if(jxOFaPnrjI == zxtnKQkGbN){KjmULpsrPk = true;}
      if(naSBYdbxkr == JUFwzBgPHu){WyLbwqnnlL = true;}
      else if(JUFwzBgPHu == naSBYdbxkr){VDhjrTErFF = true;}
      if(ahjutCydzU == AwMEkkbnPs){sjsIOHOZaI = true;}
      if(jLOVgauWis == lnbSNKBTPj){KdhOrnyZOd = true;}
      if(cxarCuthEI == sieaFrqfaZ){inpkCagWcE = true;}
      while(AwMEkkbnPs == ahjutCydzU){OaXHeiMdpw = true;}
      while(lnbSNKBTPj == lnbSNKBTPj){eNTucqFbJM = true;}
      while(sieaFrqfaZ == sieaFrqfaZ){zkZmGYaQCy = true;}
      if(nbLTYnkJUp == true){nbLTYnkJUp = false;}
      if(mAcqVVrlhn == true){mAcqVVrlhn = false;}
      if(zNzWBQRlyr == true){zNzWBQRlyr = false;}
      if(swMoEKbIsZ == true){swMoEKbIsZ = false;}
      if(ZryZwsGmEj == true){ZryZwsGmEj = false;}
      if(AExmaabnSI == true){AExmaabnSI = false;}
      if(WyLbwqnnlL == true){WyLbwqnnlL = false;}
      if(sjsIOHOZaI == true){sjsIOHOZaI = false;}
      if(KdhOrnyZOd == true){KdhOrnyZOd = false;}
      if(inpkCagWcE == true){inpkCagWcE = false;}
      if(ESArpPLnXT == true){ESArpPLnXT = false;}
      if(LCNJxrPwjH == true){LCNJxrPwjH = false;}
      if(sOYIcFtHGm == true){sOYIcFtHGm = false;}
      if(arxVDrcoXc == true){arxVDrcoXc = false;}
      if(cJBuRgZfmK == true){cJBuRgZfmK = false;}
      if(KjmULpsrPk == true){KjmULpsrPk = false;}
      if(VDhjrTErFF == true){VDhjrTErFF = false;}
      if(OaXHeiMdpw == true){OaXHeiMdpw = false;}
      if(eNTucqFbJM == true){eNTucqFbJM = false;}
      if(zkZmGYaQCy == true){zkZmGYaQCy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZWQAUODNW
{ 
  void KqRweSexan()
  { 
      bool rPHKBSkQwS = false;
      bool mokNtcwycf = false;
      bool niKmWxXOOt = false;
      bool ljSRJNwlwY = false;
      bool QaYlAQDbwd = false;
      bool nTbpSJFUnE = false;
      bool uVBBgCVSDf = false;
      bool gKCEPMJXlF = false;
      bool tuSjFRIczA = false;
      bool IaxrctZWFx = false;
      bool tjXPxdRXZF = false;
      bool zghhKADRuO = false;
      bool tsSDXFMJaU = false;
      bool mmSoLJWClb = false;
      bool AjCsAbsOhc = false;
      bool qIapDBQUrr = false;
      bool QHwFSMOsWB = false;
      bool cAeTOJpZCw = false;
      bool MxbydeLblJ = false;
      bool rCKtLrnxan = false;
      string oYtlTRRcLr;
      string PVaCdQhHtH;
      string hzngmzIfKo;
      string YukFohjWVh;
      string kdVFMdrkLN;
      string ePuPcojMyU;
      string IlRVSUkUMw;
      string fKkLWDdiUI;
      string HXTwJIzUcz;
      string xWXAYyLzlr;
      string sWXOgUdjsY;
      string LArpMkRULK;
      string UQrNzIljlX;
      string rexbPjzFPo;
      string ePaDnwehmn;
      string fpmbWcdKPX;
      string hsxVgfDPZc;
      string lMFWeEooZC;
      string dExyrBrUFm;
      string FnoqHkSFVH;
      if(oYtlTRRcLr == sWXOgUdjsY){rPHKBSkQwS = true;}
      else if(sWXOgUdjsY == oYtlTRRcLr){tjXPxdRXZF = true;}
      if(PVaCdQhHtH == LArpMkRULK){mokNtcwycf = true;}
      else if(LArpMkRULK == PVaCdQhHtH){zghhKADRuO = true;}
      if(hzngmzIfKo == UQrNzIljlX){niKmWxXOOt = true;}
      else if(UQrNzIljlX == hzngmzIfKo){tsSDXFMJaU = true;}
      if(YukFohjWVh == rexbPjzFPo){ljSRJNwlwY = true;}
      else if(rexbPjzFPo == YukFohjWVh){mmSoLJWClb = true;}
      if(kdVFMdrkLN == ePaDnwehmn){QaYlAQDbwd = true;}
      else if(ePaDnwehmn == kdVFMdrkLN){AjCsAbsOhc = true;}
      if(ePuPcojMyU == fpmbWcdKPX){nTbpSJFUnE = true;}
      else if(fpmbWcdKPX == ePuPcojMyU){qIapDBQUrr = true;}
      if(IlRVSUkUMw == hsxVgfDPZc){uVBBgCVSDf = true;}
      else if(hsxVgfDPZc == IlRVSUkUMw){QHwFSMOsWB = true;}
      if(fKkLWDdiUI == lMFWeEooZC){gKCEPMJXlF = true;}
      if(HXTwJIzUcz == dExyrBrUFm){tuSjFRIczA = true;}
      if(xWXAYyLzlr == FnoqHkSFVH){IaxrctZWFx = true;}
      while(lMFWeEooZC == fKkLWDdiUI){cAeTOJpZCw = true;}
      while(dExyrBrUFm == dExyrBrUFm){MxbydeLblJ = true;}
      while(FnoqHkSFVH == FnoqHkSFVH){rCKtLrnxan = true;}
      if(rPHKBSkQwS == true){rPHKBSkQwS = false;}
      if(mokNtcwycf == true){mokNtcwycf = false;}
      if(niKmWxXOOt == true){niKmWxXOOt = false;}
      if(ljSRJNwlwY == true){ljSRJNwlwY = false;}
      if(QaYlAQDbwd == true){QaYlAQDbwd = false;}
      if(nTbpSJFUnE == true){nTbpSJFUnE = false;}
      if(uVBBgCVSDf == true){uVBBgCVSDf = false;}
      if(gKCEPMJXlF == true){gKCEPMJXlF = false;}
      if(tuSjFRIczA == true){tuSjFRIczA = false;}
      if(IaxrctZWFx == true){IaxrctZWFx = false;}
      if(tjXPxdRXZF == true){tjXPxdRXZF = false;}
      if(zghhKADRuO == true){zghhKADRuO = false;}
      if(tsSDXFMJaU == true){tsSDXFMJaU = false;}
      if(mmSoLJWClb == true){mmSoLJWClb = false;}
      if(AjCsAbsOhc == true){AjCsAbsOhc = false;}
      if(qIapDBQUrr == true){qIapDBQUrr = false;}
      if(QHwFSMOsWB == true){QHwFSMOsWB = false;}
      if(cAeTOJpZCw == true){cAeTOJpZCw = false;}
      if(MxbydeLblJ == true){MxbydeLblJ = false;}
      if(rCKtLrnxan == true){rCKtLrnxan = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNGGOBJCDA
{ 
  void EjECslbWxr()
  { 
      bool TCeemBgeGs = false;
      bool dlGkDcKTHN = false;
      bool lExJqyAaoX = false;
      bool RworBmiKQz = false;
      bool bHfPPaYmZH = false;
      bool zVqwmPFUno = false;
      bool BFphbgwOiQ = false;
      bool sADIkdXhtQ = false;
      bool ZMAgYwFsEl = false;
      bool hOVbxVRxmh = false;
      bool dJEJNyRiKI = false;
      bool qWZXOnEIJe = false;
      bool bDKxieeaKO = false;
      bool MatMlPIqSZ = false;
      bool dWhuuKoxMI = false;
      bool QInIFZzGai = false;
      bool TqXuwQcNkz = false;
      bool fNojBFVOCX = false;
      bool pgOByDllGM = false;
      bool QBPiFmylyd = false;
      string iEkSjYobUz;
      string CUGzVAORnG;
      string PVYlGPCRjC;
      string UWdaYJZOGU;
      string BFYNDPyMzT;
      string mjNoaMezLU;
      string WWrRdepfaL;
      string azKTFJxLhq;
      string RoSPPjIozL;
      string eaClydNGiX;
      string YSlmsmYtiR;
      string OTQUCgDbBs;
      string WBfOgzwYVa;
      string uqbKRzDeWb;
      string KOGgxLJhiQ;
      string ZlEoBXlXGs;
      string qAYHWXqGDD;
      string dYEZiHtzQV;
      string pNoEAJlmIs;
      string MeYdkKpyJY;
      if(iEkSjYobUz == YSlmsmYtiR){TCeemBgeGs = true;}
      else if(YSlmsmYtiR == iEkSjYobUz){dJEJNyRiKI = true;}
      if(CUGzVAORnG == OTQUCgDbBs){dlGkDcKTHN = true;}
      else if(OTQUCgDbBs == CUGzVAORnG){qWZXOnEIJe = true;}
      if(PVYlGPCRjC == WBfOgzwYVa){lExJqyAaoX = true;}
      else if(WBfOgzwYVa == PVYlGPCRjC){bDKxieeaKO = true;}
      if(UWdaYJZOGU == uqbKRzDeWb){RworBmiKQz = true;}
      else if(uqbKRzDeWb == UWdaYJZOGU){MatMlPIqSZ = true;}
      if(BFYNDPyMzT == KOGgxLJhiQ){bHfPPaYmZH = true;}
      else if(KOGgxLJhiQ == BFYNDPyMzT){dWhuuKoxMI = true;}
      if(mjNoaMezLU == ZlEoBXlXGs){zVqwmPFUno = true;}
      else if(ZlEoBXlXGs == mjNoaMezLU){QInIFZzGai = true;}
      if(WWrRdepfaL == qAYHWXqGDD){BFphbgwOiQ = true;}
      else if(qAYHWXqGDD == WWrRdepfaL){TqXuwQcNkz = true;}
      if(azKTFJxLhq == dYEZiHtzQV){sADIkdXhtQ = true;}
      if(RoSPPjIozL == pNoEAJlmIs){ZMAgYwFsEl = true;}
      if(eaClydNGiX == MeYdkKpyJY){hOVbxVRxmh = true;}
      while(dYEZiHtzQV == azKTFJxLhq){fNojBFVOCX = true;}
      while(pNoEAJlmIs == pNoEAJlmIs){pgOByDllGM = true;}
      while(MeYdkKpyJY == MeYdkKpyJY){QBPiFmylyd = true;}
      if(TCeemBgeGs == true){TCeemBgeGs = false;}
      if(dlGkDcKTHN == true){dlGkDcKTHN = false;}
      if(lExJqyAaoX == true){lExJqyAaoX = false;}
      if(RworBmiKQz == true){RworBmiKQz = false;}
      if(bHfPPaYmZH == true){bHfPPaYmZH = false;}
      if(zVqwmPFUno == true){zVqwmPFUno = false;}
      if(BFphbgwOiQ == true){BFphbgwOiQ = false;}
      if(sADIkdXhtQ == true){sADIkdXhtQ = false;}
      if(ZMAgYwFsEl == true){ZMAgYwFsEl = false;}
      if(hOVbxVRxmh == true){hOVbxVRxmh = false;}
      if(dJEJNyRiKI == true){dJEJNyRiKI = false;}
      if(qWZXOnEIJe == true){qWZXOnEIJe = false;}
      if(bDKxieeaKO == true){bDKxieeaKO = false;}
      if(MatMlPIqSZ == true){MatMlPIqSZ = false;}
      if(dWhuuKoxMI == true){dWhuuKoxMI = false;}
      if(QInIFZzGai == true){QInIFZzGai = false;}
      if(TqXuwQcNkz == true){TqXuwQcNkz = false;}
      if(fNojBFVOCX == true){fNojBFVOCX = false;}
      if(pgOByDllGM == true){pgOByDllGM = false;}
      if(QBPiFmylyd == true){QBPiFmylyd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEDYQJEJQH
{ 
  void pWXFGznOyB()
  { 
      bool VepVGoWOhW = false;
      bool OtuFKlxfVO = false;
      bool OHVzzkOSqC = false;
      bool xEAhcWMKBs = false;
      bool uHGbihoant = false;
      bool zKhHuNIqWV = false;
      bool aEXeZJsNcm = false;
      bool ZldcTHBtPQ = false;
      bool umdwDlVrlO = false;
      bool OVnfSqibBY = false;
      bool nbxBUMfFnn = false;
      bool MNaFamZaam = false;
      bool mBaNXEyyKc = false;
      bool XYspcTpcbq = false;
      bool GQExCAtiEe = false;
      bool QIBNlmAjcQ = false;
      bool OgtKQmUkcH = false;
      bool xxzigVwcLW = false;
      bool JOseLPXeEo = false;
      bool SFAKcYWsgP = false;
      string ShSeNAMYlu;
      string YnZHcgjbgk;
      string pdoyADEaWk;
      string nwnEdczldV;
      string CSjNIoOEUw;
      string fFmHLnsUdK;
      string wlCAHczUcA;
      string gyyLiWsaoL;
      string nAFZEhIgsp;
      string jeHTYPQjGf;
      string otaUOgHbXn;
      string uReSVufbwY;
      string URbmQCqdlS;
      string GJUJVtYkLW;
      string ZfJEuRznxc;
      string jnngKXRnEM;
      string pdoEhkwUxb;
      string WuQYznIXry;
      string CDfIiSVnyy;
      string bkfygwqEWJ;
      if(ShSeNAMYlu == otaUOgHbXn){VepVGoWOhW = true;}
      else if(otaUOgHbXn == ShSeNAMYlu){nbxBUMfFnn = true;}
      if(YnZHcgjbgk == uReSVufbwY){OtuFKlxfVO = true;}
      else if(uReSVufbwY == YnZHcgjbgk){MNaFamZaam = true;}
      if(pdoyADEaWk == URbmQCqdlS){OHVzzkOSqC = true;}
      else if(URbmQCqdlS == pdoyADEaWk){mBaNXEyyKc = true;}
      if(nwnEdczldV == GJUJVtYkLW){xEAhcWMKBs = true;}
      else if(GJUJVtYkLW == nwnEdczldV){XYspcTpcbq = true;}
      if(CSjNIoOEUw == ZfJEuRznxc){uHGbihoant = true;}
      else if(ZfJEuRznxc == CSjNIoOEUw){GQExCAtiEe = true;}
      if(fFmHLnsUdK == jnngKXRnEM){zKhHuNIqWV = true;}
      else if(jnngKXRnEM == fFmHLnsUdK){QIBNlmAjcQ = true;}
      if(wlCAHczUcA == pdoEhkwUxb){aEXeZJsNcm = true;}
      else if(pdoEhkwUxb == wlCAHczUcA){OgtKQmUkcH = true;}
      if(gyyLiWsaoL == WuQYznIXry){ZldcTHBtPQ = true;}
      if(nAFZEhIgsp == CDfIiSVnyy){umdwDlVrlO = true;}
      if(jeHTYPQjGf == bkfygwqEWJ){OVnfSqibBY = true;}
      while(WuQYznIXry == gyyLiWsaoL){xxzigVwcLW = true;}
      while(CDfIiSVnyy == CDfIiSVnyy){JOseLPXeEo = true;}
      while(bkfygwqEWJ == bkfygwqEWJ){SFAKcYWsgP = true;}
      if(VepVGoWOhW == true){VepVGoWOhW = false;}
      if(OtuFKlxfVO == true){OtuFKlxfVO = false;}
      if(OHVzzkOSqC == true){OHVzzkOSqC = false;}
      if(xEAhcWMKBs == true){xEAhcWMKBs = false;}
      if(uHGbihoant == true){uHGbihoant = false;}
      if(zKhHuNIqWV == true){zKhHuNIqWV = false;}
      if(aEXeZJsNcm == true){aEXeZJsNcm = false;}
      if(ZldcTHBtPQ == true){ZldcTHBtPQ = false;}
      if(umdwDlVrlO == true){umdwDlVrlO = false;}
      if(OVnfSqibBY == true){OVnfSqibBY = false;}
      if(nbxBUMfFnn == true){nbxBUMfFnn = false;}
      if(MNaFamZaam == true){MNaFamZaam = false;}
      if(mBaNXEyyKc == true){mBaNXEyyKc = false;}
      if(XYspcTpcbq == true){XYspcTpcbq = false;}
      if(GQExCAtiEe == true){GQExCAtiEe = false;}
      if(QIBNlmAjcQ == true){QIBNlmAjcQ = false;}
      if(OgtKQmUkcH == true){OgtKQmUkcH = false;}
      if(xxzigVwcLW == true){xxzigVwcLW = false;}
      if(JOseLPXeEo == true){JOseLPXeEo = false;}
      if(SFAKcYWsgP == true){SFAKcYWsgP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFDMNEDAHY
{ 
  void enNibxIgNc()
  { 
      bool NNBBccDNfz = false;
      bool ROpKRQfGlN = false;
      bool ySmfnAqxhb = false;
      bool PPhrNKtmrR = false;
      bool OclTEjJOJM = false;
      bool MoECGuZUNb = false;
      bool kGeDjCfxwH = false;
      bool VsOTyUfSbE = false;
      bool qcmUPZLflS = false;
      bool jYZPfIxhjC = false;
      bool DLRBqTajDk = false;
      bool OGsJkISKnJ = false;
      bool pALdXxTymp = false;
      bool WxiZAfLldu = false;
      bool yabAEcePdX = false;
      bool pmtZLDzndt = false;
      bool AcwNNQXTIF = false;
      bool xfgrKPXKZu = false;
      bool RDTOAjDINx = false;
      bool fXIjuVeOmm = false;
      string RxIJtgYVRW;
      string MySkuPsMbp;
      string TUmxRhgUfO;
      string ahbFwPRryO;
      string cHdgYWRRtg;
      string MNlikwKKqM;
      string AEoDweVMof;
      string yAOMNMqFYu;
      string POazBMwsTz;
      string EGAkOXRaks;
      string AEcNhLyYVY;
      string FFlwxldpBi;
      string hcrparzcxo;
      string tPTetKlMRo;
      string NWWuszUDnc;
      string tbYBKXMlmo;
      string LUageokGCl;
      string zRYLULFxwb;
      string XuoUtRqSTV;
      string yzZbdsupPE;
      if(RxIJtgYVRW == AEcNhLyYVY){NNBBccDNfz = true;}
      else if(AEcNhLyYVY == RxIJtgYVRW){DLRBqTajDk = true;}
      if(MySkuPsMbp == FFlwxldpBi){ROpKRQfGlN = true;}
      else if(FFlwxldpBi == MySkuPsMbp){OGsJkISKnJ = true;}
      if(TUmxRhgUfO == hcrparzcxo){ySmfnAqxhb = true;}
      else if(hcrparzcxo == TUmxRhgUfO){pALdXxTymp = true;}
      if(ahbFwPRryO == tPTetKlMRo){PPhrNKtmrR = true;}
      else if(tPTetKlMRo == ahbFwPRryO){WxiZAfLldu = true;}
      if(cHdgYWRRtg == NWWuszUDnc){OclTEjJOJM = true;}
      else if(NWWuszUDnc == cHdgYWRRtg){yabAEcePdX = true;}
      if(MNlikwKKqM == tbYBKXMlmo){MoECGuZUNb = true;}
      else if(tbYBKXMlmo == MNlikwKKqM){pmtZLDzndt = true;}
      if(AEoDweVMof == LUageokGCl){kGeDjCfxwH = true;}
      else if(LUageokGCl == AEoDweVMof){AcwNNQXTIF = true;}
      if(yAOMNMqFYu == zRYLULFxwb){VsOTyUfSbE = true;}
      if(POazBMwsTz == XuoUtRqSTV){qcmUPZLflS = true;}
      if(EGAkOXRaks == yzZbdsupPE){jYZPfIxhjC = true;}
      while(zRYLULFxwb == yAOMNMqFYu){xfgrKPXKZu = true;}
      while(XuoUtRqSTV == XuoUtRqSTV){RDTOAjDINx = true;}
      while(yzZbdsupPE == yzZbdsupPE){fXIjuVeOmm = true;}
      if(NNBBccDNfz == true){NNBBccDNfz = false;}
      if(ROpKRQfGlN == true){ROpKRQfGlN = false;}
      if(ySmfnAqxhb == true){ySmfnAqxhb = false;}
      if(PPhrNKtmrR == true){PPhrNKtmrR = false;}
      if(OclTEjJOJM == true){OclTEjJOJM = false;}
      if(MoECGuZUNb == true){MoECGuZUNb = false;}
      if(kGeDjCfxwH == true){kGeDjCfxwH = false;}
      if(VsOTyUfSbE == true){VsOTyUfSbE = false;}
      if(qcmUPZLflS == true){qcmUPZLflS = false;}
      if(jYZPfIxhjC == true){jYZPfIxhjC = false;}
      if(DLRBqTajDk == true){DLRBqTajDk = false;}
      if(OGsJkISKnJ == true){OGsJkISKnJ = false;}
      if(pALdXxTymp == true){pALdXxTymp = false;}
      if(WxiZAfLldu == true){WxiZAfLldu = false;}
      if(yabAEcePdX == true){yabAEcePdX = false;}
      if(pmtZLDzndt == true){pmtZLDzndt = false;}
      if(AcwNNQXTIF == true){AcwNNQXTIF = false;}
      if(xfgrKPXKZu == true){xfgrKPXKZu = false;}
      if(RDTOAjDINx == true){RDTOAjDINx = false;}
      if(fXIjuVeOmm == true){fXIjuVeOmm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAKWXHUPMT
{ 
  void zHLhGhjWXa()
  { 
      bool wZXfITMZmh = false;
      bool TDdsoIJJLy = false;
      bool PlHbBByYzH = false;
      bool VEuhjSGMDG = false;
      bool ijcDcExOLe = false;
      bool GPPJuKSwdH = false;
      bool UnZeMPHuIW = false;
      bool BwGFOfIEyx = false;
      bool EjMUAFnlmZ = false;
      bool AKhwktJxqM = false;
      bool wBFocJJKtP = false;
      bool BNxgDkbFeG = false;
      bool aUIiWqOJTU = false;
      bool VKNlACeWqp = false;
      bool udrWXlMBsA = false;
      bool SDSjlbsWSk = false;
      bool uApYspALgA = false;
      bool GENnKxbkKk = false;
      bool eMPTBSrcAX = false;
      bool IIEGuumTdg = false;
      string soUrUFTsFk;
      string PrYHpKTIHx;
      string NpfYfVZuHx;
      string nCyoojXbMt;
      string khlBkouVKf;
      string GhiyJDIwLy;
      string fXkHxMtjRG;
      string lqwMMfDemq;
      string ZDkbqFTzel;
      string baQNOMweDX;
      string tLEEsOlVld;
      string zcIUXbmJPr;
      string stEfeLaiyz;
      string iYaPwOzgib;
      string TxNBlySwol;
      string ZmOLdAGXZh;
      string nCWltaBrXJ;
      string cFZnXwfDtf;
      string resMZwKPkw;
      string HaHBnQZbHL;
      if(soUrUFTsFk == tLEEsOlVld){wZXfITMZmh = true;}
      else if(tLEEsOlVld == soUrUFTsFk){wBFocJJKtP = true;}
      if(PrYHpKTIHx == zcIUXbmJPr){TDdsoIJJLy = true;}
      else if(zcIUXbmJPr == PrYHpKTIHx){BNxgDkbFeG = true;}
      if(NpfYfVZuHx == stEfeLaiyz){PlHbBByYzH = true;}
      else if(stEfeLaiyz == NpfYfVZuHx){aUIiWqOJTU = true;}
      if(nCyoojXbMt == iYaPwOzgib){VEuhjSGMDG = true;}
      else if(iYaPwOzgib == nCyoojXbMt){VKNlACeWqp = true;}
      if(khlBkouVKf == TxNBlySwol){ijcDcExOLe = true;}
      else if(TxNBlySwol == khlBkouVKf){udrWXlMBsA = true;}
      if(GhiyJDIwLy == ZmOLdAGXZh){GPPJuKSwdH = true;}
      else if(ZmOLdAGXZh == GhiyJDIwLy){SDSjlbsWSk = true;}
      if(fXkHxMtjRG == nCWltaBrXJ){UnZeMPHuIW = true;}
      else if(nCWltaBrXJ == fXkHxMtjRG){uApYspALgA = true;}
      if(lqwMMfDemq == cFZnXwfDtf){BwGFOfIEyx = true;}
      if(ZDkbqFTzel == resMZwKPkw){EjMUAFnlmZ = true;}
      if(baQNOMweDX == HaHBnQZbHL){AKhwktJxqM = true;}
      while(cFZnXwfDtf == lqwMMfDemq){GENnKxbkKk = true;}
      while(resMZwKPkw == resMZwKPkw){eMPTBSrcAX = true;}
      while(HaHBnQZbHL == HaHBnQZbHL){IIEGuumTdg = true;}
      if(wZXfITMZmh == true){wZXfITMZmh = false;}
      if(TDdsoIJJLy == true){TDdsoIJJLy = false;}
      if(PlHbBByYzH == true){PlHbBByYzH = false;}
      if(VEuhjSGMDG == true){VEuhjSGMDG = false;}
      if(ijcDcExOLe == true){ijcDcExOLe = false;}
      if(GPPJuKSwdH == true){GPPJuKSwdH = false;}
      if(UnZeMPHuIW == true){UnZeMPHuIW = false;}
      if(BwGFOfIEyx == true){BwGFOfIEyx = false;}
      if(EjMUAFnlmZ == true){EjMUAFnlmZ = false;}
      if(AKhwktJxqM == true){AKhwktJxqM = false;}
      if(wBFocJJKtP == true){wBFocJJKtP = false;}
      if(BNxgDkbFeG == true){BNxgDkbFeG = false;}
      if(aUIiWqOJTU == true){aUIiWqOJTU = false;}
      if(VKNlACeWqp == true){VKNlACeWqp = false;}
      if(udrWXlMBsA == true){udrWXlMBsA = false;}
      if(SDSjlbsWSk == true){SDSjlbsWSk = false;}
      if(uApYspALgA == true){uApYspALgA = false;}
      if(GENnKxbkKk == true){GENnKxbkKk = false;}
      if(eMPTBSrcAX == true){eMPTBSrcAX = false;}
      if(IIEGuumTdg == true){IIEGuumTdg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGUMVJQXLJ
{ 
  void KJmleDIhmc()
  { 
      bool fJaJIfYwRX = false;
      bool ZRJJKNdlXl = false;
      bool mXZjNRHGXS = false;
      bool psYjqKnARo = false;
      bool JLjgKbkEBa = false;
      bool fCDIVHjpuq = false;
      bool YSXygfsYRz = false;
      bool ZcUhcbnrZl = false;
      bool fCFwlnpPNj = false;
      bool ayFaQqmkAd = false;
      bool hMlBBDgVft = false;
      bool TrQJKVNaMr = false;
      bool pcKhYbXtRk = false;
      bool nCquDTQDui = false;
      bool GUiTQhguPu = false;
      bool cLYHnFBEcZ = false;
      bool fmDtFQAUGq = false;
      bool EJfckUtqQp = false;
      bool tbdVHcdiGy = false;
      bool SLaVCTQnNz = false;
      string CZAsZOqufB;
      string kJjwcsMhMU;
      string OihTceIWGt;
      string LsijiVHJAk;
      string joaMbMYLRa;
      string oxizWTrfPt;
      string GTokpqZAMH;
      string kCgakZHUrQ;
      string FwFfFNKiNP;
      string dbsFePApWj;
      string lYzKolPIOw;
      string LXmznJOIfb;
      string gplwdJJbuV;
      string ZRxIegxtqS;
      string yBURDGntQU;
      string AqJuDumCge;
      string cnMsVtZeTH;
      string MURNceVUsX;
      string UOKZUiHBFj;
      string ttNLoKnbuI;
      if(CZAsZOqufB == lYzKolPIOw){fJaJIfYwRX = true;}
      else if(lYzKolPIOw == CZAsZOqufB){hMlBBDgVft = true;}
      if(kJjwcsMhMU == LXmznJOIfb){ZRJJKNdlXl = true;}
      else if(LXmznJOIfb == kJjwcsMhMU){TrQJKVNaMr = true;}
      if(OihTceIWGt == gplwdJJbuV){mXZjNRHGXS = true;}
      else if(gplwdJJbuV == OihTceIWGt){pcKhYbXtRk = true;}
      if(LsijiVHJAk == ZRxIegxtqS){psYjqKnARo = true;}
      else if(ZRxIegxtqS == LsijiVHJAk){nCquDTQDui = true;}
      if(joaMbMYLRa == yBURDGntQU){JLjgKbkEBa = true;}
      else if(yBURDGntQU == joaMbMYLRa){GUiTQhguPu = true;}
      if(oxizWTrfPt == AqJuDumCge){fCDIVHjpuq = true;}
      else if(AqJuDumCge == oxizWTrfPt){cLYHnFBEcZ = true;}
      if(GTokpqZAMH == cnMsVtZeTH){YSXygfsYRz = true;}
      else if(cnMsVtZeTH == GTokpqZAMH){fmDtFQAUGq = true;}
      if(kCgakZHUrQ == MURNceVUsX){ZcUhcbnrZl = true;}
      if(FwFfFNKiNP == UOKZUiHBFj){fCFwlnpPNj = true;}
      if(dbsFePApWj == ttNLoKnbuI){ayFaQqmkAd = true;}
      while(MURNceVUsX == kCgakZHUrQ){EJfckUtqQp = true;}
      while(UOKZUiHBFj == UOKZUiHBFj){tbdVHcdiGy = true;}
      while(ttNLoKnbuI == ttNLoKnbuI){SLaVCTQnNz = true;}
      if(fJaJIfYwRX == true){fJaJIfYwRX = false;}
      if(ZRJJKNdlXl == true){ZRJJKNdlXl = false;}
      if(mXZjNRHGXS == true){mXZjNRHGXS = false;}
      if(psYjqKnARo == true){psYjqKnARo = false;}
      if(JLjgKbkEBa == true){JLjgKbkEBa = false;}
      if(fCDIVHjpuq == true){fCDIVHjpuq = false;}
      if(YSXygfsYRz == true){YSXygfsYRz = false;}
      if(ZcUhcbnrZl == true){ZcUhcbnrZl = false;}
      if(fCFwlnpPNj == true){fCFwlnpPNj = false;}
      if(ayFaQqmkAd == true){ayFaQqmkAd = false;}
      if(hMlBBDgVft == true){hMlBBDgVft = false;}
      if(TrQJKVNaMr == true){TrQJKVNaMr = false;}
      if(pcKhYbXtRk == true){pcKhYbXtRk = false;}
      if(nCquDTQDui == true){nCquDTQDui = false;}
      if(GUiTQhguPu == true){GUiTQhguPu = false;}
      if(cLYHnFBEcZ == true){cLYHnFBEcZ = false;}
      if(fmDtFQAUGq == true){fmDtFQAUGq = false;}
      if(EJfckUtqQp == true){EJfckUtqQp = false;}
      if(tbdVHcdiGy == true){tbdVHcdiGy = false;}
      if(SLaVCTQnNz == true){SLaVCTQnNz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCNJTRORGH
{ 
  void zVhSBweynd()
  { 
      bool txtBRUgwzL = false;
      bool XGZfBjZjYS = false;
      bool eZXfQBYGES = false;
      bool cPEZeihFGx = false;
      bool cLmJieMkBS = false;
      bool wPdUiUYOkP = false;
      bool wZqfhIBzAR = false;
      bool BUcaoTmOwk = false;
      bool omFlWNkjqK = false;
      bool KSUqBCTGba = false;
      bool dMkiQbmDeP = false;
      bool hKRAaIUFJT = false;
      bool WRIoHhzlYl = false;
      bool zflUHcCVUu = false;
      bool agEaczBUPs = false;
      bool hOxHEMDuah = false;
      bool bBesPBYwry = false;
      bool FzkOsoMgMI = false;
      bool geVfEkieQu = false;
      bool YHtlSZCLLb = false;
      string BueZaLKLzg;
      string wTNbjEpQeH;
      string OSppkzJhWp;
      string oOpLjDjKQA;
      string CbhbGhJzVc;
      string DrSZQiEnob;
      string BboIqgcCrg;
      string UfzdEmjNjC;
      string pJMtlxwPtA;
      string ywUoyalYjZ;
      string EGHnHXrnVd;
      string ypElkqOuVt;
      string kNIqhYLKfd;
      string AKcKyjCXlO;
      string EHtPCHqhDG;
      string LpDpnqyPGi;
      string MhIqcmNtmB;
      string opJGpcSroZ;
      string gcHYSKHmVH;
      string kmRDCWzDmO;
      if(BueZaLKLzg == EGHnHXrnVd){txtBRUgwzL = true;}
      else if(EGHnHXrnVd == BueZaLKLzg){dMkiQbmDeP = true;}
      if(wTNbjEpQeH == ypElkqOuVt){XGZfBjZjYS = true;}
      else if(ypElkqOuVt == wTNbjEpQeH){hKRAaIUFJT = true;}
      if(OSppkzJhWp == kNIqhYLKfd){eZXfQBYGES = true;}
      else if(kNIqhYLKfd == OSppkzJhWp){WRIoHhzlYl = true;}
      if(oOpLjDjKQA == AKcKyjCXlO){cPEZeihFGx = true;}
      else if(AKcKyjCXlO == oOpLjDjKQA){zflUHcCVUu = true;}
      if(CbhbGhJzVc == EHtPCHqhDG){cLmJieMkBS = true;}
      else if(EHtPCHqhDG == CbhbGhJzVc){agEaczBUPs = true;}
      if(DrSZQiEnob == LpDpnqyPGi){wPdUiUYOkP = true;}
      else if(LpDpnqyPGi == DrSZQiEnob){hOxHEMDuah = true;}
      if(BboIqgcCrg == MhIqcmNtmB){wZqfhIBzAR = true;}
      else if(MhIqcmNtmB == BboIqgcCrg){bBesPBYwry = true;}
      if(UfzdEmjNjC == opJGpcSroZ){BUcaoTmOwk = true;}
      if(pJMtlxwPtA == gcHYSKHmVH){omFlWNkjqK = true;}
      if(ywUoyalYjZ == kmRDCWzDmO){KSUqBCTGba = true;}
      while(opJGpcSroZ == UfzdEmjNjC){FzkOsoMgMI = true;}
      while(gcHYSKHmVH == gcHYSKHmVH){geVfEkieQu = true;}
      while(kmRDCWzDmO == kmRDCWzDmO){YHtlSZCLLb = true;}
      if(txtBRUgwzL == true){txtBRUgwzL = false;}
      if(XGZfBjZjYS == true){XGZfBjZjYS = false;}
      if(eZXfQBYGES == true){eZXfQBYGES = false;}
      if(cPEZeihFGx == true){cPEZeihFGx = false;}
      if(cLmJieMkBS == true){cLmJieMkBS = false;}
      if(wPdUiUYOkP == true){wPdUiUYOkP = false;}
      if(wZqfhIBzAR == true){wZqfhIBzAR = false;}
      if(BUcaoTmOwk == true){BUcaoTmOwk = false;}
      if(omFlWNkjqK == true){omFlWNkjqK = false;}
      if(KSUqBCTGba == true){KSUqBCTGba = false;}
      if(dMkiQbmDeP == true){dMkiQbmDeP = false;}
      if(hKRAaIUFJT == true){hKRAaIUFJT = false;}
      if(WRIoHhzlYl == true){WRIoHhzlYl = false;}
      if(zflUHcCVUu == true){zflUHcCVUu = false;}
      if(agEaczBUPs == true){agEaczBUPs = false;}
      if(hOxHEMDuah == true){hOxHEMDuah = false;}
      if(bBesPBYwry == true){bBesPBYwry = false;}
      if(FzkOsoMgMI == true){FzkOsoMgMI = false;}
      if(geVfEkieQu == true){geVfEkieQu = false;}
      if(YHtlSZCLLb == true){YHtlSZCLLb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CNUTUXPTGQ
{ 
  void xECWLtgaJY()
  { 
      bool CEwGyHiuUW = false;
      bool PfeFurLKoe = false;
      bool FszZeEosNJ = false;
      bool rsiRVwOlpM = false;
      bool lDtBQbMfAk = false;
      bool GAhwSJFWas = false;
      bool RogLdVwMjz = false;
      bool dYTbsByyID = false;
      bool rIrbCrLmyL = false;
      bool qqLxtwWhWu = false;
      bool ezwBHhfFDR = false;
      bool KGOWBIwFIk = false;
      bool JINXHlNWhw = false;
      bool eQaMYrMqTU = false;
      bool MFjgBjcnuk = false;
      bool zQZkkWkYsU = false;
      bool TIXGmtfByI = false;
      bool wFkmYEYgWW = false;
      bool JZbwxNpoaB = false;
      bool GmxzADhcsG = false;
      string IwuaPnedXg;
      string UeSjamUEBe;
      string NYRjOFbIYC;
      string UMmNzKJimP;
      string yMeIwWfZdE;
      string DHUstidKLJ;
      string LWEVMHrEjP;
      string clQlfBtInr;
      string YCdUyNrtTQ;
      string fzWdDbIJwo;
      string eboNaRqhNs;
      string nUWTjJriXy;
      string OxkSidOlhD;
      string sjMyNxNQsg;
      string WKgabKcDst;
      string jYlxagpVdx;
      string DEzJzDIXGm;
      string wboqbDQKpY;
      string BKsnTUyPXg;
      string HqlwcRKWaY;
      if(IwuaPnedXg == eboNaRqhNs){CEwGyHiuUW = true;}
      else if(eboNaRqhNs == IwuaPnedXg){ezwBHhfFDR = true;}
      if(UeSjamUEBe == nUWTjJriXy){PfeFurLKoe = true;}
      else if(nUWTjJriXy == UeSjamUEBe){KGOWBIwFIk = true;}
      if(NYRjOFbIYC == OxkSidOlhD){FszZeEosNJ = true;}
      else if(OxkSidOlhD == NYRjOFbIYC){JINXHlNWhw = true;}
      if(UMmNzKJimP == sjMyNxNQsg){rsiRVwOlpM = true;}
      else if(sjMyNxNQsg == UMmNzKJimP){eQaMYrMqTU = true;}
      if(yMeIwWfZdE == WKgabKcDst){lDtBQbMfAk = true;}
      else if(WKgabKcDst == yMeIwWfZdE){MFjgBjcnuk = true;}
      if(DHUstidKLJ == jYlxagpVdx){GAhwSJFWas = true;}
      else if(jYlxagpVdx == DHUstidKLJ){zQZkkWkYsU = true;}
      if(LWEVMHrEjP == DEzJzDIXGm){RogLdVwMjz = true;}
      else if(DEzJzDIXGm == LWEVMHrEjP){TIXGmtfByI = true;}
      if(clQlfBtInr == wboqbDQKpY){dYTbsByyID = true;}
      if(YCdUyNrtTQ == BKsnTUyPXg){rIrbCrLmyL = true;}
      if(fzWdDbIJwo == HqlwcRKWaY){qqLxtwWhWu = true;}
      while(wboqbDQKpY == clQlfBtInr){wFkmYEYgWW = true;}
      while(BKsnTUyPXg == BKsnTUyPXg){JZbwxNpoaB = true;}
      while(HqlwcRKWaY == HqlwcRKWaY){GmxzADhcsG = true;}
      if(CEwGyHiuUW == true){CEwGyHiuUW = false;}
      if(PfeFurLKoe == true){PfeFurLKoe = false;}
      if(FszZeEosNJ == true){FszZeEosNJ = false;}
      if(rsiRVwOlpM == true){rsiRVwOlpM = false;}
      if(lDtBQbMfAk == true){lDtBQbMfAk = false;}
      if(GAhwSJFWas == true){GAhwSJFWas = false;}
      if(RogLdVwMjz == true){RogLdVwMjz = false;}
      if(dYTbsByyID == true){dYTbsByyID = false;}
      if(rIrbCrLmyL == true){rIrbCrLmyL = false;}
      if(qqLxtwWhWu == true){qqLxtwWhWu = false;}
      if(ezwBHhfFDR == true){ezwBHhfFDR = false;}
      if(KGOWBIwFIk == true){KGOWBIwFIk = false;}
      if(JINXHlNWhw == true){JINXHlNWhw = false;}
      if(eQaMYrMqTU == true){eQaMYrMqTU = false;}
      if(MFjgBjcnuk == true){MFjgBjcnuk = false;}
      if(zQZkkWkYsU == true){zQZkkWkYsU = false;}
      if(TIXGmtfByI == true){TIXGmtfByI = false;}
      if(wFkmYEYgWW == true){wFkmYEYgWW = false;}
      if(JZbwxNpoaB == true){JZbwxNpoaB = false;}
      if(GmxzADhcsG == true){GmxzADhcsG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTBDPSRCKL
{ 
  void uCswFNfWFO()
  { 
      bool VPmQqpJBQj = false;
      bool AqblZhAqOL = false;
      bool DhxaxrtNRs = false;
      bool LFduzBXNhQ = false;
      bool gFMpsbwrdg = false;
      bool oKACwnSLTz = false;
      bool wwjWXtNfmX = false;
      bool KlJxexUGhU = false;
      bool uCijEAFbzL = false;
      bool hLtiUjUoRy = false;
      bool OQEFWCBCXy = false;
      bool SLdyDtNASX = false;
      bool okgbozract = false;
      bool beniFexcNB = false;
      bool yCDArWguea = false;
      bool WUVtJcicPW = false;
      bool KaZcVmXusY = false;
      bool wklRYlhgiS = false;
      bool RxuCXHItYb = false;
      bool uUMpqWcadE = false;
      string PiiTtBeXGm;
      string VsErVSagGW;
      string uAIjueRaVt;
      string UUMKaxgPRE;
      string cokYfGjsgg;
      string XHBkZPZzXP;
      string jDBMSAfsQY;
      string lKOCtFOjDo;
      string tXtoVNSakK;
      string WhqCTYmYFe;
      string ZqcItMrzqU;
      string ApuiULJMpF;
      string gEIFBDTMhV;
      string RpdXODuktJ;
      string VTjPKgmIhI;
      string OaiAxUiWGp;
      string seQUCKLWUQ;
      string QYRgjNUruU;
      string QKeZGqHdZs;
      string TXdEPpCONz;
      if(PiiTtBeXGm == ZqcItMrzqU){VPmQqpJBQj = true;}
      else if(ZqcItMrzqU == PiiTtBeXGm){OQEFWCBCXy = true;}
      if(VsErVSagGW == ApuiULJMpF){AqblZhAqOL = true;}
      else if(ApuiULJMpF == VsErVSagGW){SLdyDtNASX = true;}
      if(uAIjueRaVt == gEIFBDTMhV){DhxaxrtNRs = true;}
      else if(gEIFBDTMhV == uAIjueRaVt){okgbozract = true;}
      if(UUMKaxgPRE == RpdXODuktJ){LFduzBXNhQ = true;}
      else if(RpdXODuktJ == UUMKaxgPRE){beniFexcNB = true;}
      if(cokYfGjsgg == VTjPKgmIhI){gFMpsbwrdg = true;}
      else if(VTjPKgmIhI == cokYfGjsgg){yCDArWguea = true;}
      if(XHBkZPZzXP == OaiAxUiWGp){oKACwnSLTz = true;}
      else if(OaiAxUiWGp == XHBkZPZzXP){WUVtJcicPW = true;}
      if(jDBMSAfsQY == seQUCKLWUQ){wwjWXtNfmX = true;}
      else if(seQUCKLWUQ == jDBMSAfsQY){KaZcVmXusY = true;}
      if(lKOCtFOjDo == QYRgjNUruU){KlJxexUGhU = true;}
      if(tXtoVNSakK == QKeZGqHdZs){uCijEAFbzL = true;}
      if(WhqCTYmYFe == TXdEPpCONz){hLtiUjUoRy = true;}
      while(QYRgjNUruU == lKOCtFOjDo){wklRYlhgiS = true;}
      while(QKeZGqHdZs == QKeZGqHdZs){RxuCXHItYb = true;}
      while(TXdEPpCONz == TXdEPpCONz){uUMpqWcadE = true;}
      if(VPmQqpJBQj == true){VPmQqpJBQj = false;}
      if(AqblZhAqOL == true){AqblZhAqOL = false;}
      if(DhxaxrtNRs == true){DhxaxrtNRs = false;}
      if(LFduzBXNhQ == true){LFduzBXNhQ = false;}
      if(gFMpsbwrdg == true){gFMpsbwrdg = false;}
      if(oKACwnSLTz == true){oKACwnSLTz = false;}
      if(wwjWXtNfmX == true){wwjWXtNfmX = false;}
      if(KlJxexUGhU == true){KlJxexUGhU = false;}
      if(uCijEAFbzL == true){uCijEAFbzL = false;}
      if(hLtiUjUoRy == true){hLtiUjUoRy = false;}
      if(OQEFWCBCXy == true){OQEFWCBCXy = false;}
      if(SLdyDtNASX == true){SLdyDtNASX = false;}
      if(okgbozract == true){okgbozract = false;}
      if(beniFexcNB == true){beniFexcNB = false;}
      if(yCDArWguea == true){yCDArWguea = false;}
      if(WUVtJcicPW == true){WUVtJcicPW = false;}
      if(KaZcVmXusY == true){KaZcVmXusY = false;}
      if(wklRYlhgiS == true){wklRYlhgiS = false;}
      if(RxuCXHItYb == true){RxuCXHItYb = false;}
      if(uUMpqWcadE == true){uUMpqWcadE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYZGWUCOJT
{ 
  void GYeClNqmWC()
  { 
      bool yluexhnULW = false;
      bool ByfbBNGyBI = false;
      bool KHZzhbIYVp = false;
      bool MSmoBOEWGz = false;
      bool pTzuaKNIrJ = false;
      bool RUyZFpMuxV = false;
      bool ZOzVJiLqam = false;
      bool IjrCRpIdYX = false;
      bool NAgLYrTMiK = false;
      bool BIYkYbTclq = false;
      bool yVgFAhcwIO = false;
      bool giWYHZhmwR = false;
      bool OyIPkAKHdp = false;
      bool WeqgYqSbLq = false;
      bool OXETcSlAcz = false;
      bool tggUcANRTA = false;
      bool XURSrCroAP = false;
      bool HFbECpsnlR = false;
      bool NJddupxVEY = false;
      bool dAHKTtFlaa = false;
      string fAWbnbmnXT;
      string GmOHVJRNBa;
      string ehmfcglfqa;
      string LJHdRijwyK;
      string lUneDFtydJ;
      string FxOfixNqyG;
      string pHxxIwfkpl;
      string ZUPqnJtIcX;
      string lnCgUNtbtT;
      string VsyqUeXpVG;
      string ZJHqjjgXrY;
      string DFOaTBEQcu;
      string CDpVPfWYVI;
      string lDlVycfLxj;
      string fVjUQQeWWS;
      string aHNaDVTlaD;
      string NIBimzSrbq;
      string VrSrOgTUFz;
      string BzCDgeoKSc;
      string ItjsWXTAhQ;
      if(fAWbnbmnXT == ZJHqjjgXrY){yluexhnULW = true;}
      else if(ZJHqjjgXrY == fAWbnbmnXT){yVgFAhcwIO = true;}
      if(GmOHVJRNBa == DFOaTBEQcu){ByfbBNGyBI = true;}
      else if(DFOaTBEQcu == GmOHVJRNBa){giWYHZhmwR = true;}
      if(ehmfcglfqa == CDpVPfWYVI){KHZzhbIYVp = true;}
      else if(CDpVPfWYVI == ehmfcglfqa){OyIPkAKHdp = true;}
      if(LJHdRijwyK == lDlVycfLxj){MSmoBOEWGz = true;}
      else if(lDlVycfLxj == LJHdRijwyK){WeqgYqSbLq = true;}
      if(lUneDFtydJ == fVjUQQeWWS){pTzuaKNIrJ = true;}
      else if(fVjUQQeWWS == lUneDFtydJ){OXETcSlAcz = true;}
      if(FxOfixNqyG == aHNaDVTlaD){RUyZFpMuxV = true;}
      else if(aHNaDVTlaD == FxOfixNqyG){tggUcANRTA = true;}
      if(pHxxIwfkpl == NIBimzSrbq){ZOzVJiLqam = true;}
      else if(NIBimzSrbq == pHxxIwfkpl){XURSrCroAP = true;}
      if(ZUPqnJtIcX == VrSrOgTUFz){IjrCRpIdYX = true;}
      if(lnCgUNtbtT == BzCDgeoKSc){NAgLYrTMiK = true;}
      if(VsyqUeXpVG == ItjsWXTAhQ){BIYkYbTclq = true;}
      while(VrSrOgTUFz == ZUPqnJtIcX){HFbECpsnlR = true;}
      while(BzCDgeoKSc == BzCDgeoKSc){NJddupxVEY = true;}
      while(ItjsWXTAhQ == ItjsWXTAhQ){dAHKTtFlaa = true;}
      if(yluexhnULW == true){yluexhnULW = false;}
      if(ByfbBNGyBI == true){ByfbBNGyBI = false;}
      if(KHZzhbIYVp == true){KHZzhbIYVp = false;}
      if(MSmoBOEWGz == true){MSmoBOEWGz = false;}
      if(pTzuaKNIrJ == true){pTzuaKNIrJ = false;}
      if(RUyZFpMuxV == true){RUyZFpMuxV = false;}
      if(ZOzVJiLqam == true){ZOzVJiLqam = false;}
      if(IjrCRpIdYX == true){IjrCRpIdYX = false;}
      if(NAgLYrTMiK == true){NAgLYrTMiK = false;}
      if(BIYkYbTclq == true){BIYkYbTclq = false;}
      if(yVgFAhcwIO == true){yVgFAhcwIO = false;}
      if(giWYHZhmwR == true){giWYHZhmwR = false;}
      if(OyIPkAKHdp == true){OyIPkAKHdp = false;}
      if(WeqgYqSbLq == true){WeqgYqSbLq = false;}
      if(OXETcSlAcz == true){OXETcSlAcz = false;}
      if(tggUcANRTA == true){tggUcANRTA = false;}
      if(XURSrCroAP == true){XURSrCroAP = false;}
      if(HFbECpsnlR == true){HFbECpsnlR = false;}
      if(NJddupxVEY == true){NJddupxVEY = false;}
      if(dAHKTtFlaa == true){dAHKTtFlaa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKCSPUQJGG
{ 
  void PMlQRKNqoc()
  { 
      bool mIZENFMfFZ = false;
      bool NBndaIIAfO = false;
      bool BROPzBVeUZ = false;
      bool uTXGTKErRB = false;
      bool fzMdLzikYz = false;
      bool ylbaKUtJEL = false;
      bool ihLeeschKP = false;
      bool EQheiCFjDz = false;
      bool SjFUaJrxuy = false;
      bool QumFRxnhzS = false;
      bool WAaJuhExqI = false;
      bool PJFFsycpDV = false;
      bool AfmLzJcbMl = false;
      bool OWkkcRJwZs = false;
      bool EuFliGohMT = false;
      bool UxddRpNOJk = false;
      bool FbjFtrYTba = false;
      bool ofQKQFaAcr = false;
      bool TuOsQQsGTl = false;
      bool EtlnmbKzrp = false;
      string yUxbqGXkXW;
      string tBomkMPOII;
      string YFowtcAVcW;
      string FbwkJsIBmx;
      string fXiAaSgzGs;
      string tiKOsseBgO;
      string FBHAQRFEdr;
      string DNaKcAWoUb;
      string uAOibVRgqQ;
      string NHUYrdPhiI;
      string McVOofIzlr;
      string VpfESElYYu;
      string AXMNdusCSy;
      string joFMOReAtu;
      string NSuytXbPFm;
      string qqJmIoQHjt;
      string mFfmHgjSoB;
      string YlechhbOSG;
      string TdwfGseSEZ;
      string BXPzIHlHpM;
      if(yUxbqGXkXW == McVOofIzlr){mIZENFMfFZ = true;}
      else if(McVOofIzlr == yUxbqGXkXW){WAaJuhExqI = true;}
      if(tBomkMPOII == VpfESElYYu){NBndaIIAfO = true;}
      else if(VpfESElYYu == tBomkMPOII){PJFFsycpDV = true;}
      if(YFowtcAVcW == AXMNdusCSy){BROPzBVeUZ = true;}
      else if(AXMNdusCSy == YFowtcAVcW){AfmLzJcbMl = true;}
      if(FbwkJsIBmx == joFMOReAtu){uTXGTKErRB = true;}
      else if(joFMOReAtu == FbwkJsIBmx){OWkkcRJwZs = true;}
      if(fXiAaSgzGs == NSuytXbPFm){fzMdLzikYz = true;}
      else if(NSuytXbPFm == fXiAaSgzGs){EuFliGohMT = true;}
      if(tiKOsseBgO == qqJmIoQHjt){ylbaKUtJEL = true;}
      else if(qqJmIoQHjt == tiKOsseBgO){UxddRpNOJk = true;}
      if(FBHAQRFEdr == mFfmHgjSoB){ihLeeschKP = true;}
      else if(mFfmHgjSoB == FBHAQRFEdr){FbjFtrYTba = true;}
      if(DNaKcAWoUb == YlechhbOSG){EQheiCFjDz = true;}
      if(uAOibVRgqQ == TdwfGseSEZ){SjFUaJrxuy = true;}
      if(NHUYrdPhiI == BXPzIHlHpM){QumFRxnhzS = true;}
      while(YlechhbOSG == DNaKcAWoUb){ofQKQFaAcr = true;}
      while(TdwfGseSEZ == TdwfGseSEZ){TuOsQQsGTl = true;}
      while(BXPzIHlHpM == BXPzIHlHpM){EtlnmbKzrp = true;}
      if(mIZENFMfFZ == true){mIZENFMfFZ = false;}
      if(NBndaIIAfO == true){NBndaIIAfO = false;}
      if(BROPzBVeUZ == true){BROPzBVeUZ = false;}
      if(uTXGTKErRB == true){uTXGTKErRB = false;}
      if(fzMdLzikYz == true){fzMdLzikYz = false;}
      if(ylbaKUtJEL == true){ylbaKUtJEL = false;}
      if(ihLeeschKP == true){ihLeeschKP = false;}
      if(EQheiCFjDz == true){EQheiCFjDz = false;}
      if(SjFUaJrxuy == true){SjFUaJrxuy = false;}
      if(QumFRxnhzS == true){QumFRxnhzS = false;}
      if(WAaJuhExqI == true){WAaJuhExqI = false;}
      if(PJFFsycpDV == true){PJFFsycpDV = false;}
      if(AfmLzJcbMl == true){AfmLzJcbMl = false;}
      if(OWkkcRJwZs == true){OWkkcRJwZs = false;}
      if(EuFliGohMT == true){EuFliGohMT = false;}
      if(UxddRpNOJk == true){UxddRpNOJk = false;}
      if(FbjFtrYTba == true){FbjFtrYTba = false;}
      if(ofQKQFaAcr == true){ofQKQFaAcr = false;}
      if(TuOsQQsGTl == true){TuOsQQsGTl = false;}
      if(EtlnmbKzrp == true){EtlnmbKzrp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWBJGSETCP
{ 
  void CSdFgkjzgb()
  { 
      bool LXCSSgHVCy = false;
      bool CznRdhTeYV = false;
      bool XIVtqsJCOM = false;
      bool VlbIZFzoLx = false;
      bool IIPmubTwjO = false;
      bool shPAZDBHaZ = false;
      bool WFGocPWeqY = false;
      bool ieSbNPsizP = false;
      bool YMSATnWahW = false;
      bool DqOlZDBZKf = false;
      bool FoEKfOOmlK = false;
      bool JSILBKmGVo = false;
      bool ruxTUqQgBK = false;
      bool OSYSJjHHUE = false;
      bool YioXMkiDjP = false;
      bool PtEUnJqkon = false;
      bool yglbuqtoBQ = false;
      bool CekQPIGYGj = false;
      bool HMwltTODeA = false;
      bool rWRfGqxMcV = false;
      string PdEPDlAHJi;
      string kxJlHJTYAS;
      string tPPXVfdKcE;
      string FEyPOXpIBe;
      string lrdXSxAYNm;
      string rsbSdANgsX;
      string IoeEcgzsWi;
      string TLXUfCkqFY;
      string eExpMLcekO;
      string JIOdWxNZuk;
      string xGCdSfVGmb;
      string OWbTrDrnrQ;
      string ETIHYKwsyi;
      string oLwTaYCTWf;
      string pVrJAmgukT;
      string FYhdgdxtEI;
      string jbIDlCaIrS;
      string AXQLahbyGl;
      string dBHddPdRlx;
      string aHOOwNMoWy;
      if(PdEPDlAHJi == xGCdSfVGmb){LXCSSgHVCy = true;}
      else if(xGCdSfVGmb == PdEPDlAHJi){FoEKfOOmlK = true;}
      if(kxJlHJTYAS == OWbTrDrnrQ){CznRdhTeYV = true;}
      else if(OWbTrDrnrQ == kxJlHJTYAS){JSILBKmGVo = true;}
      if(tPPXVfdKcE == ETIHYKwsyi){XIVtqsJCOM = true;}
      else if(ETIHYKwsyi == tPPXVfdKcE){ruxTUqQgBK = true;}
      if(FEyPOXpIBe == oLwTaYCTWf){VlbIZFzoLx = true;}
      else if(oLwTaYCTWf == FEyPOXpIBe){OSYSJjHHUE = true;}
      if(lrdXSxAYNm == pVrJAmgukT){IIPmubTwjO = true;}
      else if(pVrJAmgukT == lrdXSxAYNm){YioXMkiDjP = true;}
      if(rsbSdANgsX == FYhdgdxtEI){shPAZDBHaZ = true;}
      else if(FYhdgdxtEI == rsbSdANgsX){PtEUnJqkon = true;}
      if(IoeEcgzsWi == jbIDlCaIrS){WFGocPWeqY = true;}
      else if(jbIDlCaIrS == IoeEcgzsWi){yglbuqtoBQ = true;}
      if(TLXUfCkqFY == AXQLahbyGl){ieSbNPsizP = true;}
      if(eExpMLcekO == dBHddPdRlx){YMSATnWahW = true;}
      if(JIOdWxNZuk == aHOOwNMoWy){DqOlZDBZKf = true;}
      while(AXQLahbyGl == TLXUfCkqFY){CekQPIGYGj = true;}
      while(dBHddPdRlx == dBHddPdRlx){HMwltTODeA = true;}
      while(aHOOwNMoWy == aHOOwNMoWy){rWRfGqxMcV = true;}
      if(LXCSSgHVCy == true){LXCSSgHVCy = false;}
      if(CznRdhTeYV == true){CznRdhTeYV = false;}
      if(XIVtqsJCOM == true){XIVtqsJCOM = false;}
      if(VlbIZFzoLx == true){VlbIZFzoLx = false;}
      if(IIPmubTwjO == true){IIPmubTwjO = false;}
      if(shPAZDBHaZ == true){shPAZDBHaZ = false;}
      if(WFGocPWeqY == true){WFGocPWeqY = false;}
      if(ieSbNPsizP == true){ieSbNPsizP = false;}
      if(YMSATnWahW == true){YMSATnWahW = false;}
      if(DqOlZDBZKf == true){DqOlZDBZKf = false;}
      if(FoEKfOOmlK == true){FoEKfOOmlK = false;}
      if(JSILBKmGVo == true){JSILBKmGVo = false;}
      if(ruxTUqQgBK == true){ruxTUqQgBK = false;}
      if(OSYSJjHHUE == true){OSYSJjHHUE = false;}
      if(YioXMkiDjP == true){YioXMkiDjP = false;}
      if(PtEUnJqkon == true){PtEUnJqkon = false;}
      if(yglbuqtoBQ == true){yglbuqtoBQ = false;}
      if(CekQPIGYGj == true){CekQPIGYGj = false;}
      if(HMwltTODeA == true){HMwltTODeA = false;}
      if(rWRfGqxMcV == true){rWRfGqxMcV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KMUQOMXQDF
{ 
  void oUmQYCCqmk()
  { 
      bool DJTJqCbBnp = false;
      bool JqeQLpzKzE = false;
      bool mVJzfMRYdn = false;
      bool iflNOcmcyY = false;
      bool ADDkHZVLFI = false;
      bool pRgwsgzUcd = false;
      bool jDWzHdFRCh = false;
      bool DVMaEiSXqF = false;
      bool qGTVyQypUg = false;
      bool dSzTnwgDdd = false;
      bool UEJWFTFGqJ = false;
      bool OacXmdjBAp = false;
      bool eOxUEkWrlH = false;
      bool COtNkmwwQe = false;
      bool KryKSCobgK = false;
      bool MfDmyFHoSU = false;
      bool xNTiHzgPlA = false;
      bool gnkVemQlBB = false;
      bool utLbuWLGOf = false;
      bool eHcwhxXOCT = false;
      string XPFhNuySWe;
      string YMlnLkDYzP;
      string nGMWzbjPSJ;
      string WLjFSpsWiH;
      string mVRfDTgOmX;
      string WRmbtQCihl;
      string LizMIMcgUV;
      string qfoqcRnfTe;
      string uUcumEYHKB;
      string mJnxwDWEWp;
      string qzsQfpcuzb;
      string bWODqpGEZE;
      string nUVThhrruY;
      string tjJdmubLOx;
      string acHhYQtjFF;
      string xRdRBVdZiy;
      string ykAahrNkQw;
      string OuocdLMmtR;
      string mHloacFqbQ;
      string QBcQyocgAf;
      if(XPFhNuySWe == qzsQfpcuzb){DJTJqCbBnp = true;}
      else if(qzsQfpcuzb == XPFhNuySWe){UEJWFTFGqJ = true;}
      if(YMlnLkDYzP == bWODqpGEZE){JqeQLpzKzE = true;}
      else if(bWODqpGEZE == YMlnLkDYzP){OacXmdjBAp = true;}
      if(nGMWzbjPSJ == nUVThhrruY){mVJzfMRYdn = true;}
      else if(nUVThhrruY == nGMWzbjPSJ){eOxUEkWrlH = true;}
      if(WLjFSpsWiH == tjJdmubLOx){iflNOcmcyY = true;}
      else if(tjJdmubLOx == WLjFSpsWiH){COtNkmwwQe = true;}
      if(mVRfDTgOmX == acHhYQtjFF){ADDkHZVLFI = true;}
      else if(acHhYQtjFF == mVRfDTgOmX){KryKSCobgK = true;}
      if(WRmbtQCihl == xRdRBVdZiy){pRgwsgzUcd = true;}
      else if(xRdRBVdZiy == WRmbtQCihl){MfDmyFHoSU = true;}
      if(LizMIMcgUV == ykAahrNkQw){jDWzHdFRCh = true;}
      else if(ykAahrNkQw == LizMIMcgUV){xNTiHzgPlA = true;}
      if(qfoqcRnfTe == OuocdLMmtR){DVMaEiSXqF = true;}
      if(uUcumEYHKB == mHloacFqbQ){qGTVyQypUg = true;}
      if(mJnxwDWEWp == QBcQyocgAf){dSzTnwgDdd = true;}
      while(OuocdLMmtR == qfoqcRnfTe){gnkVemQlBB = true;}
      while(mHloacFqbQ == mHloacFqbQ){utLbuWLGOf = true;}
      while(QBcQyocgAf == QBcQyocgAf){eHcwhxXOCT = true;}
      if(DJTJqCbBnp == true){DJTJqCbBnp = false;}
      if(JqeQLpzKzE == true){JqeQLpzKzE = false;}
      if(mVJzfMRYdn == true){mVJzfMRYdn = false;}
      if(iflNOcmcyY == true){iflNOcmcyY = false;}
      if(ADDkHZVLFI == true){ADDkHZVLFI = false;}
      if(pRgwsgzUcd == true){pRgwsgzUcd = false;}
      if(jDWzHdFRCh == true){jDWzHdFRCh = false;}
      if(DVMaEiSXqF == true){DVMaEiSXqF = false;}
      if(qGTVyQypUg == true){qGTVyQypUg = false;}
      if(dSzTnwgDdd == true){dSzTnwgDdd = false;}
      if(UEJWFTFGqJ == true){UEJWFTFGqJ = false;}
      if(OacXmdjBAp == true){OacXmdjBAp = false;}
      if(eOxUEkWrlH == true){eOxUEkWrlH = false;}
      if(COtNkmwwQe == true){COtNkmwwQe = false;}
      if(KryKSCobgK == true){KryKSCobgK = false;}
      if(MfDmyFHoSU == true){MfDmyFHoSU = false;}
      if(xNTiHzgPlA == true){xNTiHzgPlA = false;}
      if(gnkVemQlBB == true){gnkVemQlBB = false;}
      if(utLbuWLGOf == true){utLbuWLGOf = false;}
      if(eHcwhxXOCT == true){eHcwhxXOCT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOVTDGTQDR
{ 
  void mfdlwktbxn()
  { 
      bool TcFUuhHVCG = false;
      bool hONTGCRaHY = false;
      bool JkAdJsnatq = false;
      bool WAWkMBTuYD = false;
      bool bpnGVkJxOj = false;
      bool eDKUShbbKB = false;
      bool sfbLihrbGF = false;
      bool hVCDxSwtIX = false;
      bool iqMJLSoBRd = false;
      bool YrkWKuOcWm = false;
      bool shpICIBHXA = false;
      bool khSlSCSRzQ = false;
      bool sqJbgokesB = false;
      bool ETXVeBBDHC = false;
      bool QhcRsqZyEH = false;
      bool cxdGtBXNbM = false;
      bool XVNWuRKxHQ = false;
      bool BOJwzLNqio = false;
      bool PmakYHoQbc = false;
      bool dmbuetTGWa = false;
      string NsCBXoUgle;
      string TpLkBEpJzF;
      string WNlQbAfFPk;
      string CpfrlQKAsm;
      string XZzpMpTpMB;
      string fsnArAHlYX;
      string IORAccJTzk;
      string toQLhwNuDk;
      string fpsNFIBezk;
      string IYaVeIIyMi;
      string fApbGpcbSw;
      string lLhmqRVDuU;
      string aeTNbVNtgY;
      string nPiUFfAQGO;
      string fZMDzwpneM;
      string mECrHBfbzk;
      string bhusIWcNhK;
      string RFwgoBSQOf;
      string eZPTliMqMD;
      string AXQUlxeStc;
      if(NsCBXoUgle == fApbGpcbSw){TcFUuhHVCG = true;}
      else if(fApbGpcbSw == NsCBXoUgle){shpICIBHXA = true;}
      if(TpLkBEpJzF == lLhmqRVDuU){hONTGCRaHY = true;}
      else if(lLhmqRVDuU == TpLkBEpJzF){khSlSCSRzQ = true;}
      if(WNlQbAfFPk == aeTNbVNtgY){JkAdJsnatq = true;}
      else if(aeTNbVNtgY == WNlQbAfFPk){sqJbgokesB = true;}
      if(CpfrlQKAsm == nPiUFfAQGO){WAWkMBTuYD = true;}
      else if(nPiUFfAQGO == CpfrlQKAsm){ETXVeBBDHC = true;}
      if(XZzpMpTpMB == fZMDzwpneM){bpnGVkJxOj = true;}
      else if(fZMDzwpneM == XZzpMpTpMB){QhcRsqZyEH = true;}
      if(fsnArAHlYX == mECrHBfbzk){eDKUShbbKB = true;}
      else if(mECrHBfbzk == fsnArAHlYX){cxdGtBXNbM = true;}
      if(IORAccJTzk == bhusIWcNhK){sfbLihrbGF = true;}
      else if(bhusIWcNhK == IORAccJTzk){XVNWuRKxHQ = true;}
      if(toQLhwNuDk == RFwgoBSQOf){hVCDxSwtIX = true;}
      if(fpsNFIBezk == eZPTliMqMD){iqMJLSoBRd = true;}
      if(IYaVeIIyMi == AXQUlxeStc){YrkWKuOcWm = true;}
      while(RFwgoBSQOf == toQLhwNuDk){BOJwzLNqio = true;}
      while(eZPTliMqMD == eZPTliMqMD){PmakYHoQbc = true;}
      while(AXQUlxeStc == AXQUlxeStc){dmbuetTGWa = true;}
      if(TcFUuhHVCG == true){TcFUuhHVCG = false;}
      if(hONTGCRaHY == true){hONTGCRaHY = false;}
      if(JkAdJsnatq == true){JkAdJsnatq = false;}
      if(WAWkMBTuYD == true){WAWkMBTuYD = false;}
      if(bpnGVkJxOj == true){bpnGVkJxOj = false;}
      if(eDKUShbbKB == true){eDKUShbbKB = false;}
      if(sfbLihrbGF == true){sfbLihrbGF = false;}
      if(hVCDxSwtIX == true){hVCDxSwtIX = false;}
      if(iqMJLSoBRd == true){iqMJLSoBRd = false;}
      if(YrkWKuOcWm == true){YrkWKuOcWm = false;}
      if(shpICIBHXA == true){shpICIBHXA = false;}
      if(khSlSCSRzQ == true){khSlSCSRzQ = false;}
      if(sqJbgokesB == true){sqJbgokesB = false;}
      if(ETXVeBBDHC == true){ETXVeBBDHC = false;}
      if(QhcRsqZyEH == true){QhcRsqZyEH = false;}
      if(cxdGtBXNbM == true){cxdGtBXNbM = false;}
      if(XVNWuRKxHQ == true){XVNWuRKxHQ = false;}
      if(BOJwzLNqio == true){BOJwzLNqio = false;}
      if(PmakYHoQbc == true){PmakYHoQbc = false;}
      if(dmbuetTGWa == true){dmbuetTGWa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLDRZLYODF
{ 
  void udHERBFpGr()
  { 
      bool tzNlHYUfDJ = false;
      bool ZcrCLnlYuY = false;
      bool NijuFrbcXX = false;
      bool blZwRdGFjn = false;
      bool YtjKBTgDyT = false;
      bool QTLXsLORfP = false;
      bool xqIehmDwjh = false;
      bool gfnHATyZsl = false;
      bool KYeEGIaCDG = false;
      bool OoZTpglEcN = false;
      bool QkSQljeEWY = false;
      bool MoYtEYMDYZ = false;
      bool MArcSrGTQS = false;
      bool htxeVZFNSV = false;
      bool cVfdtZPePR = false;
      bool UhfCBPrpxt = false;
      bool cKnEqSqsXe = false;
      bool SykCwqUOis = false;
      bool bbEyxzOtdF = false;
      bool gOQXsSgamb = false;
      string thsqZiuqXX;
      string YkQMdNFuwo;
      string wZphyoejjz;
      string XFmwqwVwYQ;
      string QAflaZFPYO;
      string WfNyOUrLrj;
      string DLHXATxTUg;
      string rJVeXutDGY;
      string iPKUcqqohW;
      string EJEoNFsHlH;
      string cltqWNKhZT;
      string anETAmAluI;
      string cIkychFfRR;
      string BlRzwxVTyP;
      string gIOOuQEkoZ;
      string FHLddTAuOn;
      string IdQHRnVFWC;
      string RgmeaTsWDM;
      string cTqrMsamUb;
      string xZFJHDrGwG;
      if(thsqZiuqXX == cltqWNKhZT){tzNlHYUfDJ = true;}
      else if(cltqWNKhZT == thsqZiuqXX){QkSQljeEWY = true;}
      if(YkQMdNFuwo == anETAmAluI){ZcrCLnlYuY = true;}
      else if(anETAmAluI == YkQMdNFuwo){MoYtEYMDYZ = true;}
      if(wZphyoejjz == cIkychFfRR){NijuFrbcXX = true;}
      else if(cIkychFfRR == wZphyoejjz){MArcSrGTQS = true;}
      if(XFmwqwVwYQ == BlRzwxVTyP){blZwRdGFjn = true;}
      else if(BlRzwxVTyP == XFmwqwVwYQ){htxeVZFNSV = true;}
      if(QAflaZFPYO == gIOOuQEkoZ){YtjKBTgDyT = true;}
      else if(gIOOuQEkoZ == QAflaZFPYO){cVfdtZPePR = true;}
      if(WfNyOUrLrj == FHLddTAuOn){QTLXsLORfP = true;}
      else if(FHLddTAuOn == WfNyOUrLrj){UhfCBPrpxt = true;}
      if(DLHXATxTUg == IdQHRnVFWC){xqIehmDwjh = true;}
      else if(IdQHRnVFWC == DLHXATxTUg){cKnEqSqsXe = true;}
      if(rJVeXutDGY == RgmeaTsWDM){gfnHATyZsl = true;}
      if(iPKUcqqohW == cTqrMsamUb){KYeEGIaCDG = true;}
      if(EJEoNFsHlH == xZFJHDrGwG){OoZTpglEcN = true;}
      while(RgmeaTsWDM == rJVeXutDGY){SykCwqUOis = true;}
      while(cTqrMsamUb == cTqrMsamUb){bbEyxzOtdF = true;}
      while(xZFJHDrGwG == xZFJHDrGwG){gOQXsSgamb = true;}
      if(tzNlHYUfDJ == true){tzNlHYUfDJ = false;}
      if(ZcrCLnlYuY == true){ZcrCLnlYuY = false;}
      if(NijuFrbcXX == true){NijuFrbcXX = false;}
      if(blZwRdGFjn == true){blZwRdGFjn = false;}
      if(YtjKBTgDyT == true){YtjKBTgDyT = false;}
      if(QTLXsLORfP == true){QTLXsLORfP = false;}
      if(xqIehmDwjh == true){xqIehmDwjh = false;}
      if(gfnHATyZsl == true){gfnHATyZsl = false;}
      if(KYeEGIaCDG == true){KYeEGIaCDG = false;}
      if(OoZTpglEcN == true){OoZTpglEcN = false;}
      if(QkSQljeEWY == true){QkSQljeEWY = false;}
      if(MoYtEYMDYZ == true){MoYtEYMDYZ = false;}
      if(MArcSrGTQS == true){MArcSrGTQS = false;}
      if(htxeVZFNSV == true){htxeVZFNSV = false;}
      if(cVfdtZPePR == true){cVfdtZPePR = false;}
      if(UhfCBPrpxt == true){UhfCBPrpxt = false;}
      if(cKnEqSqsXe == true){cKnEqSqsXe = false;}
      if(SykCwqUOis == true){SykCwqUOis = false;}
      if(bbEyxzOtdF == true){bbEyxzOtdF = false;}
      if(gOQXsSgamb == true){gOQXsSgamb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FVFDJSUKGL
{ 
  void FaStERsWTc()
  { 
      bool HujCfMqUeb = false;
      bool JAOjPyjQZB = false;
      bool eXSuZMGufk = false;
      bool nOsdKpuWBo = false;
      bool RejjqCPLae = false;
      bool aIqkrjcncT = false;
      bool GwnsntGjZZ = false;
      bool DMOkjzmhDW = false;
      bool xtTBKeXHka = false;
      bool NGthhVpqux = false;
      bool welBbNtFBr = false;
      bool xtkFWLbmiJ = false;
      bool WyyyMwSfCN = false;
      bool JwlGaRISYw = false;
      bool kRGrdSVoLW = false;
      bool tCHlaxgmne = false;
      bool uNCmiAHddF = false;
      bool DINmXErFUs = false;
      bool adUfTGnAfd = false;
      bool jUdtAWOSJc = false;
      string Xzkfhxhgkz;
      string OXUKZrusXO;
      string AmiXkcxQrU;
      string wyLtunWPwI;
      string gAMxrcjiBj;
      string VLTYyjPNuF;
      string zQoPCQMZPk;
      string VfwOgzaleH;
      string sNOHyjdlwL;
      string YITqIQLwtb;
      string QJTPOpOFry;
      string JdhmLkBgRS;
      string lZdDMMLFFQ;
      string ndqCqitzsH;
      string UYsxCtafeX;
      string OedbppfPDB;
      string dJzbKemewc;
      string qCmJxNgfBS;
      string keZhBJzPMB;
      string CdwqdLZRmX;
      if(Xzkfhxhgkz == QJTPOpOFry){HujCfMqUeb = true;}
      else if(QJTPOpOFry == Xzkfhxhgkz){welBbNtFBr = true;}
      if(OXUKZrusXO == JdhmLkBgRS){JAOjPyjQZB = true;}
      else if(JdhmLkBgRS == OXUKZrusXO){xtkFWLbmiJ = true;}
      if(AmiXkcxQrU == lZdDMMLFFQ){eXSuZMGufk = true;}
      else if(lZdDMMLFFQ == AmiXkcxQrU){WyyyMwSfCN = true;}
      if(wyLtunWPwI == ndqCqitzsH){nOsdKpuWBo = true;}
      else if(ndqCqitzsH == wyLtunWPwI){JwlGaRISYw = true;}
      if(gAMxrcjiBj == UYsxCtafeX){RejjqCPLae = true;}
      else if(UYsxCtafeX == gAMxrcjiBj){kRGrdSVoLW = true;}
      if(VLTYyjPNuF == OedbppfPDB){aIqkrjcncT = true;}
      else if(OedbppfPDB == VLTYyjPNuF){tCHlaxgmne = true;}
      if(zQoPCQMZPk == dJzbKemewc){GwnsntGjZZ = true;}
      else if(dJzbKemewc == zQoPCQMZPk){uNCmiAHddF = true;}
      if(VfwOgzaleH == qCmJxNgfBS){DMOkjzmhDW = true;}
      if(sNOHyjdlwL == keZhBJzPMB){xtTBKeXHka = true;}
      if(YITqIQLwtb == CdwqdLZRmX){NGthhVpqux = true;}
      while(qCmJxNgfBS == VfwOgzaleH){DINmXErFUs = true;}
      while(keZhBJzPMB == keZhBJzPMB){adUfTGnAfd = true;}
      while(CdwqdLZRmX == CdwqdLZRmX){jUdtAWOSJc = true;}
      if(HujCfMqUeb == true){HujCfMqUeb = false;}
      if(JAOjPyjQZB == true){JAOjPyjQZB = false;}
      if(eXSuZMGufk == true){eXSuZMGufk = false;}
      if(nOsdKpuWBo == true){nOsdKpuWBo = false;}
      if(RejjqCPLae == true){RejjqCPLae = false;}
      if(aIqkrjcncT == true){aIqkrjcncT = false;}
      if(GwnsntGjZZ == true){GwnsntGjZZ = false;}
      if(DMOkjzmhDW == true){DMOkjzmhDW = false;}
      if(xtTBKeXHka == true){xtTBKeXHka = false;}
      if(NGthhVpqux == true){NGthhVpqux = false;}
      if(welBbNtFBr == true){welBbNtFBr = false;}
      if(xtkFWLbmiJ == true){xtkFWLbmiJ = false;}
      if(WyyyMwSfCN == true){WyyyMwSfCN = false;}
      if(JwlGaRISYw == true){JwlGaRISYw = false;}
      if(kRGrdSVoLW == true){kRGrdSVoLW = false;}
      if(tCHlaxgmne == true){tCHlaxgmne = false;}
      if(uNCmiAHddF == true){uNCmiAHddF = false;}
      if(DINmXErFUs == true){DINmXErFUs = false;}
      if(adUfTGnAfd == true){adUfTGnAfd = false;}
      if(jUdtAWOSJc == true){jUdtAWOSJc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SALPSIPSTS
{ 
  void BiSIeKaNHs()
  { 
      bool jXDfTSCSWc = false;
      bool uoxcysUfni = false;
      bool xZSWTWVxtE = false;
      bool eoNXWHTjWK = false;
      bool AfEpzbXmAx = false;
      bool PaYdAJEfMx = false;
      bool wFXSyFbZGq = false;
      bool ZjIdhRUcXq = false;
      bool zhxxnDQiXM = false;
      bool DmXZNuHlqs = false;
      bool AxgJXfRuwh = false;
      bool nbIUyOIadu = false;
      bool orCsnlLiPm = false;
      bool KikdpBBmYI = false;
      bool lUmoYaeCbz = false;
      bool mfHwEHumVl = false;
      bool TieIXFpdew = false;
      bool MUCVITFMUM = false;
      bool GJHQAdboYi = false;
      bool FNRmnDpdRT = false;
      string ggqxUVxRYV;
      string uQaMDiqsun;
      string kZeJOdQepH;
      string XbFLCfMPby;
      string LESTxpFsBp;
      string ljXbWHBgiq;
      string ERaRxTKOKX;
      string VaRxbgGKMX;
      string XXdzUnEdou;
      string dfgjsscBVd;
      string epicULSazp;
      string AqUKSgnbwJ;
      string OgZPspthDi;
      string DEnhshnAdJ;
      string UddztmKVQM;
      string FAFLOyPSje;
      string RkWQlwClRk;
      string rmxlokCaVG;
      string fXQqcDybTt;
      string RVQzqjGMNx;
      if(ggqxUVxRYV == epicULSazp){jXDfTSCSWc = true;}
      else if(epicULSazp == ggqxUVxRYV){AxgJXfRuwh = true;}
      if(uQaMDiqsun == AqUKSgnbwJ){uoxcysUfni = true;}
      else if(AqUKSgnbwJ == uQaMDiqsun){nbIUyOIadu = true;}
      if(kZeJOdQepH == OgZPspthDi){xZSWTWVxtE = true;}
      else if(OgZPspthDi == kZeJOdQepH){orCsnlLiPm = true;}
      if(XbFLCfMPby == DEnhshnAdJ){eoNXWHTjWK = true;}
      else if(DEnhshnAdJ == XbFLCfMPby){KikdpBBmYI = true;}
      if(LESTxpFsBp == UddztmKVQM){AfEpzbXmAx = true;}
      else if(UddztmKVQM == LESTxpFsBp){lUmoYaeCbz = true;}
      if(ljXbWHBgiq == FAFLOyPSje){PaYdAJEfMx = true;}
      else if(FAFLOyPSje == ljXbWHBgiq){mfHwEHumVl = true;}
      if(ERaRxTKOKX == RkWQlwClRk){wFXSyFbZGq = true;}
      else if(RkWQlwClRk == ERaRxTKOKX){TieIXFpdew = true;}
      if(VaRxbgGKMX == rmxlokCaVG){ZjIdhRUcXq = true;}
      if(XXdzUnEdou == fXQqcDybTt){zhxxnDQiXM = true;}
      if(dfgjsscBVd == RVQzqjGMNx){DmXZNuHlqs = true;}
      while(rmxlokCaVG == VaRxbgGKMX){MUCVITFMUM = true;}
      while(fXQqcDybTt == fXQqcDybTt){GJHQAdboYi = true;}
      while(RVQzqjGMNx == RVQzqjGMNx){FNRmnDpdRT = true;}
      if(jXDfTSCSWc == true){jXDfTSCSWc = false;}
      if(uoxcysUfni == true){uoxcysUfni = false;}
      if(xZSWTWVxtE == true){xZSWTWVxtE = false;}
      if(eoNXWHTjWK == true){eoNXWHTjWK = false;}
      if(AfEpzbXmAx == true){AfEpzbXmAx = false;}
      if(PaYdAJEfMx == true){PaYdAJEfMx = false;}
      if(wFXSyFbZGq == true){wFXSyFbZGq = false;}
      if(ZjIdhRUcXq == true){ZjIdhRUcXq = false;}
      if(zhxxnDQiXM == true){zhxxnDQiXM = false;}
      if(DmXZNuHlqs == true){DmXZNuHlqs = false;}
      if(AxgJXfRuwh == true){AxgJXfRuwh = false;}
      if(nbIUyOIadu == true){nbIUyOIadu = false;}
      if(orCsnlLiPm == true){orCsnlLiPm = false;}
      if(KikdpBBmYI == true){KikdpBBmYI = false;}
      if(lUmoYaeCbz == true){lUmoYaeCbz = false;}
      if(mfHwEHumVl == true){mfHwEHumVl = false;}
      if(TieIXFpdew == true){TieIXFpdew = false;}
      if(MUCVITFMUM == true){MUCVITFMUM = false;}
      if(GJHQAdboYi == true){GJHQAdboYi = false;}
      if(FNRmnDpdRT == true){FNRmnDpdRT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEUDCYBIOI
{ 
  void kSLPSzpupp()
  { 
      bool fxICKKNyPN = false;
      bool nBlTsMTDUh = false;
      bool ECVoYOYQie = false;
      bool SKhGUnJMuH = false;
      bool cQxczTGEWf = false;
      bool rHjVOcaSdw = false;
      bool kxPktdSezE = false;
      bool DGIMFnEspE = false;
      bool IUsDlLZMrr = false;
      bool NqizVeBMhU = false;
      bool BaESckyWPa = false;
      bool XhbYmQELyi = false;
      bool DGmGqMXJqZ = false;
      bool mrKVDhPZaB = false;
      bool MCwRTfOKLF = false;
      bool aoNzRtnyaP = false;
      bool NofonfWGUF = false;
      bool AdkxVAJUlL = false;
      bool xNykzxdLDI = false;
      bool tRzKnXWGdn = false;
      string QiEAzuJBEk;
      string BxOXKlsrZY;
      string fsjdZbGHCz;
      string GumIRfhhaU;
      string AWdWAVLdwe;
      string tOojTXyZZW;
      string oBzEdGKFGe;
      string DLRFXIONcE;
      string QbLWFrFDot;
      string gHHDfyWZrs;
      string LFXRahwjLK;
      string IkwVFMpbzl;
      string AGQLxwDNYZ;
      string koUjrKEsuW;
      string uVqdlwKlyS;
      string HtZGrEnLUe;
      string eiKlYSQMcu;
      string HxgbpePmZA;
      string lRPGRpONqn;
      string VrXQrLLEES;
      if(QiEAzuJBEk == LFXRahwjLK){fxICKKNyPN = true;}
      else if(LFXRahwjLK == QiEAzuJBEk){BaESckyWPa = true;}
      if(BxOXKlsrZY == IkwVFMpbzl){nBlTsMTDUh = true;}
      else if(IkwVFMpbzl == BxOXKlsrZY){XhbYmQELyi = true;}
      if(fsjdZbGHCz == AGQLxwDNYZ){ECVoYOYQie = true;}
      else if(AGQLxwDNYZ == fsjdZbGHCz){DGmGqMXJqZ = true;}
      if(GumIRfhhaU == koUjrKEsuW){SKhGUnJMuH = true;}
      else if(koUjrKEsuW == GumIRfhhaU){mrKVDhPZaB = true;}
      if(AWdWAVLdwe == uVqdlwKlyS){cQxczTGEWf = true;}
      else if(uVqdlwKlyS == AWdWAVLdwe){MCwRTfOKLF = true;}
      if(tOojTXyZZW == HtZGrEnLUe){rHjVOcaSdw = true;}
      else if(HtZGrEnLUe == tOojTXyZZW){aoNzRtnyaP = true;}
      if(oBzEdGKFGe == eiKlYSQMcu){kxPktdSezE = true;}
      else if(eiKlYSQMcu == oBzEdGKFGe){NofonfWGUF = true;}
      if(DLRFXIONcE == HxgbpePmZA){DGIMFnEspE = true;}
      if(QbLWFrFDot == lRPGRpONqn){IUsDlLZMrr = true;}
      if(gHHDfyWZrs == VrXQrLLEES){NqizVeBMhU = true;}
      while(HxgbpePmZA == DLRFXIONcE){AdkxVAJUlL = true;}
      while(lRPGRpONqn == lRPGRpONqn){xNykzxdLDI = true;}
      while(VrXQrLLEES == VrXQrLLEES){tRzKnXWGdn = true;}
      if(fxICKKNyPN == true){fxICKKNyPN = false;}
      if(nBlTsMTDUh == true){nBlTsMTDUh = false;}
      if(ECVoYOYQie == true){ECVoYOYQie = false;}
      if(SKhGUnJMuH == true){SKhGUnJMuH = false;}
      if(cQxczTGEWf == true){cQxczTGEWf = false;}
      if(rHjVOcaSdw == true){rHjVOcaSdw = false;}
      if(kxPktdSezE == true){kxPktdSezE = false;}
      if(DGIMFnEspE == true){DGIMFnEspE = false;}
      if(IUsDlLZMrr == true){IUsDlLZMrr = false;}
      if(NqizVeBMhU == true){NqizVeBMhU = false;}
      if(BaESckyWPa == true){BaESckyWPa = false;}
      if(XhbYmQELyi == true){XhbYmQELyi = false;}
      if(DGmGqMXJqZ == true){DGmGqMXJqZ = false;}
      if(mrKVDhPZaB == true){mrKVDhPZaB = false;}
      if(MCwRTfOKLF == true){MCwRTfOKLF = false;}
      if(aoNzRtnyaP == true){aoNzRtnyaP = false;}
      if(NofonfWGUF == true){NofonfWGUF = false;}
      if(AdkxVAJUlL == true){AdkxVAJUlL = false;}
      if(xNykzxdLDI == true){xNykzxdLDI = false;}
      if(tRzKnXWGdn == true){tRzKnXWGdn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SEYWVWYFMM
{ 
  void UXDDwuifAI()
  { 
      bool HxoWVlZzWU = false;
      bool xoAnNtfHeu = false;
      bool fyyKauCmmC = false;
      bool rHkGigCAyV = false;
      bool nAISTzbJUr = false;
      bool tyogGIydwa = false;
      bool ilMUcoEsEg = false;
      bool rfIJGfpepb = false;
      bool SrRtIsSDAZ = false;
      bool hXEXlBmnpe = false;
      bool thEmANpeaZ = false;
      bool SSmTHqTRLj = false;
      bool VArdzTbkWE = false;
      bool sCoLgjmett = false;
      bool DmbaHOjjPu = false;
      bool hUbFIspanf = false;
      bool lEIWgQdbmX = false;
      bool DoXQfiYRWj = false;
      bool jqUbWXZiDm = false;
      bool tMpNIyeFtq = false;
      string puZrxrhIYB;
      string cAmKScsmPq;
      string dnwTbATRdG;
      string CUdgatkAnM;
      string gXpHJdHqfx;
      string mLtqZCzFQx;
      string XPdRyHVGjX;
      string rrzDKFxoKy;
      string rclfTqZmGX;
      string uejpnQtXIB;
      string HBGHFtMqfU;
      string FJuSFtdxyH;
      string hhzMcNIIOs;
      string LYfIppWdaY;
      string diGlSkjRkt;
      string lwZATYCteq;
      string lDblJfdmbO;
      string XAWZcybNsq;
      string dqWUHOzenQ;
      string ncyimaGTbl;
      if(puZrxrhIYB == HBGHFtMqfU){HxoWVlZzWU = true;}
      else if(HBGHFtMqfU == puZrxrhIYB){thEmANpeaZ = true;}
      if(cAmKScsmPq == FJuSFtdxyH){xoAnNtfHeu = true;}
      else if(FJuSFtdxyH == cAmKScsmPq){SSmTHqTRLj = true;}
      if(dnwTbATRdG == hhzMcNIIOs){fyyKauCmmC = true;}
      else if(hhzMcNIIOs == dnwTbATRdG){VArdzTbkWE = true;}
      if(CUdgatkAnM == LYfIppWdaY){rHkGigCAyV = true;}
      else if(LYfIppWdaY == CUdgatkAnM){sCoLgjmett = true;}
      if(gXpHJdHqfx == diGlSkjRkt){nAISTzbJUr = true;}
      else if(diGlSkjRkt == gXpHJdHqfx){DmbaHOjjPu = true;}
      if(mLtqZCzFQx == lwZATYCteq){tyogGIydwa = true;}
      else if(lwZATYCteq == mLtqZCzFQx){hUbFIspanf = true;}
      if(XPdRyHVGjX == lDblJfdmbO){ilMUcoEsEg = true;}
      else if(lDblJfdmbO == XPdRyHVGjX){lEIWgQdbmX = true;}
      if(rrzDKFxoKy == XAWZcybNsq){rfIJGfpepb = true;}
      if(rclfTqZmGX == dqWUHOzenQ){SrRtIsSDAZ = true;}
      if(uejpnQtXIB == ncyimaGTbl){hXEXlBmnpe = true;}
      while(XAWZcybNsq == rrzDKFxoKy){DoXQfiYRWj = true;}
      while(dqWUHOzenQ == dqWUHOzenQ){jqUbWXZiDm = true;}
      while(ncyimaGTbl == ncyimaGTbl){tMpNIyeFtq = true;}
      if(HxoWVlZzWU == true){HxoWVlZzWU = false;}
      if(xoAnNtfHeu == true){xoAnNtfHeu = false;}
      if(fyyKauCmmC == true){fyyKauCmmC = false;}
      if(rHkGigCAyV == true){rHkGigCAyV = false;}
      if(nAISTzbJUr == true){nAISTzbJUr = false;}
      if(tyogGIydwa == true){tyogGIydwa = false;}
      if(ilMUcoEsEg == true){ilMUcoEsEg = false;}
      if(rfIJGfpepb == true){rfIJGfpepb = false;}
      if(SrRtIsSDAZ == true){SrRtIsSDAZ = false;}
      if(hXEXlBmnpe == true){hXEXlBmnpe = false;}
      if(thEmANpeaZ == true){thEmANpeaZ = false;}
      if(SSmTHqTRLj == true){SSmTHqTRLj = false;}
      if(VArdzTbkWE == true){VArdzTbkWE = false;}
      if(sCoLgjmett == true){sCoLgjmett = false;}
      if(DmbaHOjjPu == true){DmbaHOjjPu = false;}
      if(hUbFIspanf == true){hUbFIspanf = false;}
      if(lEIWgQdbmX == true){lEIWgQdbmX = false;}
      if(DoXQfiYRWj == true){DoXQfiYRWj = false;}
      if(jqUbWXZiDm == true){jqUbWXZiDm = false;}
      if(tMpNIyeFtq == true){tMpNIyeFtq = false;}
    } 
}; 
