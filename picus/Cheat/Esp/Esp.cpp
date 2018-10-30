#include "Esp.h"

#include "../../Cheat/GrenadeHelper/CGrenadeAPI.h"


using namespace Client;
//[enc_string_enable /]
//[junk_enable /]



enum
{
	PITCH = 0, // up / down
	YAW, // left / right
	ROLL // fall over
};

void inline SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

void AngleVectors(const QAngle& angles, Vector* forward)
{
	float sp, sy, cp, cy;

	SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

int StringToWeapon(std::string weapon) {
	if (!strcmp(weapon.c_str(), "smokegrenade"))
		return 45;
	if (!strcmp(weapon.c_str(), "flashbang"))
		return 43;
	if (!strcmp(weapon.c_str(), "incgrenade"))
		return 46;
}


CSoundEsp::CSoundEsp()
{
	SoundColor = Color::White();
}

void CSoundEsp::Update()
{
	for (size_t i = 0; i < Sound.size(); i++)
	{
		if (Sound[i].dwTime + 800 <= GetTickCount64())
		{
			Sound.erase(Sound.begin() + i);
		}
	}
}

SDK::PlayerInfo GetInfo(int Index)
{
	SDK::PlayerInfo info;
	Interfaces::Engine()->GetPlayerInfo(Index, &info);
	return info;
}

typedef void(__cdecl* MsgFn)(const char* msg, va_list);
void Msg(const char* msg, ...)
{

	if (msg == nullptr)
		return;
	static MsgFn fn = (MsgFn)GetProcAddress(GetModuleHandle("tier0.dll"), "Msg");
	char buffer[989];
	va_list list;
	va_start(list, msg);

	vsprintf(buffer, msg, list);
	va_end(list);

	fn(buffer, list);
}

char* HitgroupToName(int hitgroup)
{
	switch (hitgroup)
	{
	case HITGROUP_HEAD:
		return "head";
	case HITGROUP_LEFTLEG:
		return "leg";
	case HITGROUP_RIGHTLEG:
		return "leg";
	case HITGROUP_LEFTARM:
		return "arm";
	case HITGROUP_RIGHTARM:
		return "arm";
	case HITGROUP_STOMACH:
		return "chest";
	default:
		return "chest";
	}
}


void CSoundEsp::AddSound(Vector vOrigin)
{
	Sound_s Sound_Entry;

	Sound_Entry.dwTime = GetTickCount64();
	Sound_Entry.vOrigin = vOrigin;

	Sound.push_back(Sound_Entry);
}

void CSoundEsp::DrawSoundEsp()
{
	for (size_t i = 0; i < Sound.size(); i++)
	{
		Vector vScreen;

		if (WorldToScreen(Sound[i].vOrigin, vScreen))
		{
			if (Settings::Esp::esp_Sound)
				g_pRender->DrawBox((int)vScreen.x, (int)vScreen.y, 10, 10, SoundColor);
		}
	}
}



CEsp::CEsp()
{
	// ����� �� ����

	CT_HP_ColorM.SetColor(255, 64, 64);
	TT_HP_ColorM.SetColor(255, 64, 64);

	// ����� ����� ����

	CT_AR_ColorM.SetColor(255, 64, 64);
	TT_AR_ColorM.SetColor(255, 64, 64);

	visible_flat = nullptr;
	visible_tex = nullptr;
	hidden_flat = nullptr;
	hidden_tex = nullptr;

	fExplodeC4Timer = 0.f;
	fC4Timer = 0.f;
}

Color CEsp::GetPlayerColor(CPlayer* pPlayer)
{
	Color CT_Color(int(Settings::Esp::esp_Color_CT[0] * 255.f), int(Settings::Esp::esp_Color_CT[1] * 255.f), int(Settings::Esp::esp_Color_CT[2] * 255.f));
	Color TT_Color(int(Settings::Esp::esp_Color_TT[0] * 255.f), int(Settings::Esp::esp_Color_TT[1] * 255.f), int(Settings::Esp::esp_Color_TT[2] * 255.f));

	if (pPlayer->Team == TEAM_CT)
	{
		return CT_Color;
	}
	else if (pPlayer->Team == TEAM_TT)
	{
		return TT_Color;
	}

	return Color::White();
}

Color CEsp::GetPlayerVisibleColor(CPlayer* pPlayer)
{
	Color PlayerColor = GetPlayerColor(pPlayer);

	bool SetColor = false;

	// ������������ ������ ���� ����� �����:

	if (pPlayer->bVisible)
	{
		if (Settings::Esp::esp_Visible == 0 && pPlayer->Team != g_pPlayers->GetLocal()->Team) // �����������
		{
			SetColor = true;
		}
		else if (Settings::Esp::esp_Visible == 1 && pPlayer->Team == g_pPlayers->GetLocal()->Team) // �����
		{
			SetColor = true;
		}
		else if (Settings::Esp::esp_Visible == 2) // ����
		{
			SetColor = true;
		}

		Color VCT_Color(int(Settings::Esp::esp_Color_VCT[0] * 255.f), int(Settings::Esp::esp_Color_VCT[1] * 255.f), int(Settings::Esp::esp_Color_VCT[2] * 255.f));
		Color VTT_Color(int(Settings::Esp::esp_Color_VTT[0] * 255.f), int(Settings::Esp::esp_Color_VTT[1] * 255.f), int(Settings::Esp::esp_Color_VTT[2] * 255.f));

		if (SetColor)
		{
			if (pPlayer->Team == TEAM_CT)
			{
				PlayerColor = VCT_Color;
			}
			else if (pPlayer->Team == TEAM_TT)
			{
				PlayerColor = VTT_Color;
			}
		}
	}

	return PlayerColor;
}

bool CEsp::CheckPlayerTeam(CPlayer* pPlayer)
{
	bool CheckTeam = false;
	bool PlayerVisible = pPlayer->bVisible;

	// ���������� esp ������ ��:
	if (Settings::Esp::esp_Enemy && pPlayer->Team != g_pPlayers->GetLocal()->Team) // �����������
		CheckTeam = true;

	if (Settings::Esp::esp_Team && pPlayer->Team == g_pPlayers->GetLocal()->Team) // �����
		CheckTeam = true;

	if (Settings::Esp::esp_Visible >= 3 && !PlayerVisible)
		CheckTeam = false;

	return CheckTeam;
}

void CEsp::Ambient()
{
	float AmbientRedAmount = Settings::Esp::esp_Ambient[0];
	float AmbientGreenAmount = Settings::Esp::esp_Ambient[1];
	float AmbientBlueAmount = Settings::Esp::esp_Ambient[2];

	ConVar* AmbientRedCvar = Interfaces::GetConVar()->FindVar("mat_ambient_light_r");
	*(float*)((DWORD)&AmbientRedCvar->fnChangeCallback + 0xC) = NULL;
	AmbientRedCvar->SetValue(AmbientRedAmount);

	ConVar* AmbientGreenCvar = Interfaces::GetConVar()->FindVar("mat_ambient_light_g");
	*(float*)((DWORD)&AmbientGreenCvar->fnChangeCallback + 0xC) = NULL;
	AmbientGreenCvar->SetValue(AmbientGreenAmount);

	ConVar* AmbientBlueCvar = Interfaces::GetConVar()->FindVar("mat_ambient_light_b");
	*(float*)((DWORD)&AmbientBlueCvar->fnChangeCallback + 0xC) = NULL;
	AmbientBlueCvar->SetValue(AmbientBlueAmount);
}






void CEsp::AsusWalls()
{
	bool AsusDone = false;

	if (Settings::Esp::esp_AsusWalls)
	{
		if (!AsusDone)
		{
			static auto r_DrawSpecificStaticProp = Interfaces::GetConVar()->FindVar("r_DrawSpecificStaticProp");
			r_DrawSpecificStaticProp->SetValue(1);

			for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				double XD = 100;
				double Opacity = int(Settings::Esp::esp_WallsOpacity);
				double RealOpacity = Opacity / XD;

				/*if (strstr(group, "StaticProp"))
				{
				pMaterial->AlphaModulate(RealOpacity);
				pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}*/
				if (strstr(group, "World textures"))
				{
					pMaterial->AlphaModulate(RealOpacity);
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{
					pMaterial->AlphaModulate(RealOpacity);
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}

				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}
				AsusDone = true;
			}

		}

	}
	else
	{
		if (AsusDone)
		{
			for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{

					pMaterial->AlphaModulate(1);
				}
				if (strstr(group, "StaticProp"))
				{
					pMaterial->AlphaModulate(1);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{

					pMaterial->AlphaModulate(1);
				}
				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}

			AsusDone = false;
		}
	}
}




void CEsp::Espwarning()
{

	if (Settings::Esp::bEspWarnings)
	{
		if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
		{
			std::stringstream text1 = std::stringstream("");
			std::stringstream text2 = std::stringstream("");
			CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			if (!pLocal)
				return;

			for (int i = 1; i <= Interfaces::Engine()->GetMaxClients(); i++)
			{

				CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

				if (pPlayer)
				{
					if (!pPlayer->IsValid())
						continue;
					if (pPlayer->GetTeam() == pLocal->GetTeam() && !Settings::Esp::esp_Team)
						continue;

					PlayerInfo info;
					if (!Interfaces::Engine()->GetPlayerInfo(i, &info))
						continue;

					Vector src, dst, forward;
					trace_t tr;
					Ray_t ray;
					CTraceFilter filter;
					AngleVectors(pPlayer->GetEyeAngles(), forward);
					filter.pSkip = pPlayer;
					src = pPlayer->GetBestEyePos(true);
					dst = src + (forward * 8192);
					ray.Init(src, dst);
					Interfaces::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);
					bool AimingToLocal = (tr.m_pEnt && tr.hitgroup > 0 && tr.hitgroup <= 7);
					bool CanSeeLocal = pPlayer->IsVisible(pLocal);

					if (AimingToLocal)
					{
						text2 << info.m_szPlayerName << " ";
					}
					if (CanSeeLocal)
					{
						text1 << info.m_szPlayerName << " ";
					}
				}
			}


			text2 << "is aiming at you";
			text1 << "can see You";
			int screensizeX, screensizeY;
			Interfaces::Engine()->GetScreenSize(screensizeX, screensizeY);
			g_pRender->Text(screensizeX / 2, 100, true, true, Color::Red(), text2.str().c_str());
			g_pRender->Text(screensizeX / 2, 120, true, true, Color::Green(), text1.str().c_str());

		}

	}

}



void CEsp::HitmarkerEvents(IGameEvent* event)
{

	if (!strcmp(event->GetName(), "bullet_impact"))
	{
		CBaseEntity* LocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (LocalPlayer)
		{
			auto index = Interfaces::Engine()->GetPlayerForUserID(event->GetInt("userid"));

			if (index != Interfaces::Engine()->GetLocalPlayer())
				return;

			auto local = static_cast<CBaseEntity*>(Interfaces::EntityList()->GetClientEntity(index));

			Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));

			Ray_t ray;

			ray.Init(local->GetEyePosition(), position);

			CTraceFilter filter;

			filter.pSkip = local;

			trace_t tr;
			Interfaces::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

			if (!local)
				return;
			{
			
			}


		}
	}


	if (!strcmp(event->GetName(), "player_hurt"))
	{
		if (Settings::Esp::esp_HitMarker)
		{

			int attacker = event->GetInt("attacker");
			if (Interfaces::Engine()->GetPlayerForUserID(attacker) == Interfaces::Engine()->GetLocalPlayer())
			{
				switch (Settings::Esp::esp_HitMarkerSound)
				{
				case 0: break;
				case 1: PlaySoundA(rawData, NULL, SND_ASYNC | SND_MEMORY); break;
				case 2: PlaySoundA(metallic, NULL, SND_ASYNC | SND_MEMORY); break;
				case 3: PlaySoundA(roblox, NULL, SND_ASYNC | SND_MEMORY); break;
				case 4: PlaySoundA(winxp_wav, NULL, SND_ASYNC | SND_MEMORY); break;


				}
				Settings::hitmarkerAlpha = 1.f;
			}
		}
		int attackerid = event->GetInt("attacker");
		int entityid = Interfaces::Engine()->GetPlayerForUserID(attackerid);
		if (entityid == Interfaces::Engine()->GetLocalPlayer())
		{

			int nUserID = event->GetInt("attacker");
			int nDead = event->GetInt("userid");
			if (nUserID || nDead)
			{
				SDK::PlayerInfo killed_info = GetInfo(Interfaces::Engine()->GetPlayerForUserID(nDead));
				SDK::PlayerInfo killer_info = GetInfo(Interfaces::Engine()->GetPlayerForUserID(nUserID));
				std::string before = ("You ");
				std::string two = ("shot ");
				std::string three = killed_info.m_szPlayerName;
				std::string four = (" in his ");
				std::string five = HitgroupToName(event->GetInt("hitgroup"));
				std::string sixa = " for ";
				std::string sevena = event->GetString("dmg_health");
				std::string damage = " damage";
				std::string sixb = " (";
				std::string sevenb = event->GetString("health");
				std::string ate = " health remaining)";
				std::string newline = "\n";
				if (Settings::Esp::esp_HitMarker)
				{
					Interfaces::Engine()->ExecuteClientCmd("developer 1");
					Interfaces::Engine()->ExecuteClientCmd("con_filter_enable 2 ");
					Interfaces::Engine()->ExecuteClientCmd("con_filter_text Hit ");
					Msg((before + two + three + four + five + sixa + sevena + damage + sixb + sevenb + ate + newline).c_str());
				}

			}
		}
	}
}

void CEsp::DrawHitmarker()
{
	if (Settings::hitmarkerAlpha < 0.f)
		Settings::hitmarkerAlpha = 0.f;
	else if (Settings::hitmarkerAlpha > 0.f)
		Settings::hitmarkerAlpha -= 0.01f;

	int W, H;
	Interfaces::Engine()->GetScreenSize(W, H);

	float r = Settings::Esp::esp_HitMarkerColor[0] * 255.f;
	float g = Settings::Esp::esp_HitMarkerColor[1] * 255.f;
	float b = Settings::Esp::esp_HitMarkerColor[2] * 255.f;

	if (Settings::hitmarkerAlpha > 0.f)
	{
		g_pRender->DrawLine(W / 2 - 10, H / 2 - 10, W / 2 - 5, H / 2 - 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));
		g_pRender->DrawLine(W / 2 - 10, H / 2 + 10, W / 2 - 5, H / 2 + 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));
		g_pRender->DrawLine(W / 2 + 10, H / 2 - 10, W / 2 + 5, H / 2 - 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));
		g_pRender->DrawLine(W / 2 + 10, H / 2 + 10, W / 2 + 5, H / 2 + 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));

	}
}

void hitmarker::player_hurt_listener::start()
{
	if (!Interfaces::GameEvent()->AddListener(this, "player_hurt", false)) {
		throw exception("Failed to register the event");
	}
	if (!Interfaces::GameEvent()->AddListener(this, "bullet_impact", false))
	{
		throw exception("Failed to register the event");
	}
}
void hitmarker::player_hurt_listener::stop()
{
	Interfaces::GameEvent()->RemoveListener(this);
}
void hitmarker::player_hurt_listener::FireGameEvent(IGameEvent *event)
{
	g_pEsp->HitmarkerEvents(event);
}
int hitmarker::player_hurt_listener::GetEventDebugID(void)
{
	return 0x2A;
}

/*
void CEsp::GrenadePrediction()
{
if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
{
CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

const float TIMEALIVE = 5.f;
const float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.4f;

float fStep = 0.1f;
float fGravity = 800.0f / 8.f;

Vector vPos, vThrow, vThrow2;
Vector vStart;

int iCollisions = 0;

QAngle vViewAngles;
Interfaces::Engine()->GetViewAngles(vViewAngles);

vThrow[0] = vViewAngles[0];
vThrow[1] = vViewAngles[1];
vThrow[2] = vViewAngles[2];

if (vThrow[0] < 0)
vThrow[0] = -10 + vThrow[0] * ((90 - 10) / 90.0);
else
vThrow[0] = -10 + vThrow[0] * ((90 + 10) / 90.0);

float fVel = (90 - vThrow[0]) * 4;
if (fVel > 500)
fVel = 500;

AngleVectors(vThrow, vThrow2);

Vector vEye = pLocal->GetEyePosition();
vStart[0] = vEye[0] + vThrow2[0] * 16;
vStart[1] = vEye[1] + vThrow2[1] * 16;
vStart[2] = vEye[2] + vThrow2[2] * 16;

vThrow2[0] = (vThrow2[0] * fVel) + pLocal->GetVelocity()[0];
vThrow2[1] = (vThrow2[1] * fVel) + pLocal->GetVelocity()[1];
vThrow2[2] = (vThrow2[2] * fVel) + pLocal->GetVelocity()[2];

#define IsGrenade g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SMOKEGRENADE | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_HEGRENADE | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_INCGRENADE | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_MOLOTOV | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_DECOY | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_FLASHBANG

if (!pLocal->IsDead() && IsGrenade)
{
for (float fTime = 0.0f; fTime < TIMEALIVE; fTime += fStep)
{
vPos = vStart + vThrow2 * fStep;

Ray_t ray;
trace_t tr;
CTraceFilter loc;
loc.pSkip = pLocal;

ray.Init(vStart, vPos);
Interfaces::EngineTrace()->TraceRay(ray, MASK_SOLID, &loc, &tr);
Color color = Color(0, 255, 0);
if (tr.DidHit())
{
float anglez = DotProduct(Vector(0, 0, 1), tr.plane.normal);
float invanglez = DotProduct(Vector(0, 0, -1), tr.plane.normal);
float angley = DotProduct(Vector(0, 1, 0), tr.plane.normal);
float invangley = DotProduct(Vector(0, -1, 0), tr.plane.normal);
float anglex = DotProduct(Vector(1, 0, 0), tr.plane.normal);
float invanglex = DotProduct(Vector(3 - 1, 0, 0), tr.plane.normal);
float scale = tr.endpos.DistTo(pLocal->GetOrigin()) / 60;
Color color = Color(0, 0, 255);
if (anglez > 0.5)
{
tr.endpos.z += 1;
Vector startPos = tr.endpos + Vector(-scale, 0, 0);
Vector endPos = tr.endpos + Vector(scale, 0, 0);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(0, -scale, 0);
endPos = tr.endpos + Vector(0, scale, 0);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (invanglez > 0.5)
{
tr.endpos.z += 1;
Vector startPos = tr.endpos + Vector(-scale, 0, 0);
Vector endPos = tr.endpos + Vector(scale, 0, 0);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(0, -scale, 0);
endPos = tr.endpos + Vector(0, scale, 0);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (angley > 0.5)
{
tr.endpos.y += 1;
Vector startPos = tr.endpos + Vector(0, 0, -scale);
Vector endPos = tr.endpos + Vector(0, 0, scale);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(-scale, 0, 0);
endPos = tr.endpos + Vector(scale, 0, 0);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (invangley > 0.5)
{
tr.endpos.y += 1;
Vector startPos = tr.endpos + Vector(0, 0, -scale);
Vector endPos = tr.endpos + Vector(0, 0, scale);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(-scale, 0, 0);
endPos = tr.endpos + Vector(scale, 0, 0);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (anglex > 0.5)
{
tr.endpos.x += 1;
Vector startPos = tr.endpos + Vector(0, -scale, 0);
Vector endPos = tr.endpos + Vector(0, scale, 0);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(0, 0, -scale);
endPos = tr.endpos + Vector(0, 0, scale);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (invanglex > 0.5)
{
tr.endpos.x += 1;
Vector startPos = tr.endpos + Vector(0, -scale, 0);
Vector endPos = tr.endpos + Vector(0, scale, 0);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(0, 0, -scale);
endPos = tr.endpos + Vector(0, 0, scale);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}

vThrow2 = tr.plane.normal * -2.0f * DotProduct(vThrow2, tr.plane.normal) + vThrow2;
vThrow2 *= GRENADE_COEFFICIENT_OF_RESTITUTION;

iCollisions++;
if (iCollisions > 2)
break;

vPos = vStart + vThrow2 * tr.fraction * fStep;
fTime += (fStep * (1 - tr.fraction));
}

Vector vOutStart, vOutEnd;

if (WorldToScreen(vStart, vOutStart) && WorldToScreen(vPos, vOutEnd))
g_pRender->DrawLine((int)vOutStart.x, (int)vOutStart.y, (int)vOutEnd.x, (int)vOutEnd.y, Color::Blue());

vStart = vPos;
vThrow2.z -= fGravity * tr.fraction * fStep;
}
}
}
}
*/

void CEsp::ChromeWorld() //chromeworld u blind niggur
{
	if (Settings::Esp::esp_ChromeWorld)
	{
		ConVar* Chromeworld = Interfaces::GetConVar()->FindVar("r_showenvcubemap");
		if (Chromeworld)
		{
			Chromeworld->SetValue(1);
		}
	}
	else
	{
		ConVar* Chromeworld = Interfaces::GetConVar()->FindVar("r_showenvcubemap");
		if (Chromeworld)
		{
			Chromeworld->SetValue(0);
		}
	}
}

void CEsp::MinecraftMode()
{
	if (Settings::Esp::esp_MinecraftMode)
	{
		ConVar* Minecraftmode = Interfaces::GetConVar()->FindVar("mat_showlowresimage");
		if (Minecraftmode)
		{
			Minecraftmode->SetValue(1);
		}
	}
	else
	{
		ConVar* Minecraftmode = Interfaces::GetConVar()->FindVar("mat_showlowresimage");
		if (Minecraftmode)
		{
			Minecraftmode->SetValue(0);
		}
	}
}

void CEsp::LSDMode()
{
	if (Settings::Esp::esp_LSDMode)
	{
		ConVar* lsdmode = Interfaces::GetConVar()->FindVar("mat_showmiplevels");
		if (lsdmode)
		{
			lsdmode->SetValue(1);
		}
	}
	else
	{
		ConVar* lsdmode = Interfaces::GetConVar()->FindVar("mat_showmiplevels");
		if (lsdmode)
		{
			lsdmode->SetValue(0);
		}
	}
}

//CustomModels
bool PrecacheModel(const char* szModelName)
{
	auto m_pModelPrecacheTable = Interfaces::ClientStringTableContainer()->FindTable("modelprecache");

	if (m_pModelPrecacheTable)
	{
		Interfaces::ModelInfo()->FindOrLoadModel(szModelName);
		int idx = m_pModelPrecacheTable->AddString(false, szModelName);
		if (idx == INVALID_STRING_INDEX)
			return false;
	}
	return true;
}

void CEsp::OnRender()
{
	if (Settings::Esp::esp_Sound)
		SoundEsp.DrawSoundEsp();
	
	
	if (g_pAimbot)
		g_pAimbot->OnRender();

	// if (Settings::Esp::esp_GrenadePrediction)
	// 	GrenadePrediction();

	if (g_pTriggerbot)
		g_pTriggerbot->TriggerShowStatus();

	if (Settings::Esp::esp_HitMarker)
		DrawHitmarker();

	if (Settings::Esp::bEspWarnings)
		Espwarning();


	Ambient();
	LSDMode();
	MinecraftMode();
	ChromeWorld();
	AsusWalls();

	if (Settings::Misc::misc_AwpAim && IsLocalAlive())
	{
		ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(1);
		ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(999999999);
	}
	else
	{
		ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(0);
		ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(0);
	}
	NightMode();

	for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

		if (pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate && CheckPlayerTeam(pPlayer))
		{
			if (g_pTriggerbot)
				g_pTriggerbot->TriggerShow(pPlayer);

			DrawPlayerEsp(pPlayer);

			if (Settings::Esp::esp_Skeleton)
				DrawPlayerSkeleton(pPlayer);

			if (Settings::Esp::esp_BulletTrace)
				DrawPlayerBulletTrace(pPlayer);
		}
	}





	

	if (Settings::Esp::esp_BombTimer)
	{
		if (bC4Timer && iC4Timer)
		{
			float fTimeStamp = Interfaces::Engine()->GetLastTimeStamp();

			if (!fExplodeC4Timer)
			{
				fExplodeC4Timer = fTimeStamp + (float)iC4Timer;
			}
			else
			{
				fC4Timer = fExplodeC4Timer - fTimeStamp;

				if (fC4Timer < 0.f)
					fC4Timer = 0.f;
			}
		}
		else
		{
			fExplodeC4Timer = 0.f;
			fC4Timer = 0.f;
		}
	}


	Color GrenadeHelper = Color(int(Settings::Esp::GrenadeHelper[0] * 255.f),
		int(Settings::Esp::GrenadeHelper[1] * 255.f),
		int(Settings::Esp::GrenadeHelper[2] * 255.f));

	if (Settings::Esp::helper && Interfaces::Engine()->IsConnected())
	{

		CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		for (int i = 0; i < cGrenade.GrenadeInfo.size(); i++)
		{
			GrenadeInfo_t info;
			if (!cGrenade.GetInfo(i, &info))
				continue;

			int iGrenadeID = StringToWeapon(info.szWeapon);


			if (!local->GetBaseWeapon())
				continue;

			if (!(local->GetBaseWeapon()->GeteAttributableItem()->GetItemDefinitionIndex2() == iGrenadeID || (iGrenadeID == 46 && local->GetBaseWeapon()->GeteAttributableItem()->GetItemDefinitionIndex2() == 48)))
				continue;

			Vector vecOnScreenOrigin, vecOnScreenAngles;
			int iCenterY, iCenterX;
			Interfaces::Engine()->GetScreenSize(iCenterY, iCenterX);
			iCenterX /= 2;
			iCenterY /= 2;

			float dist = sqrt(pow(local->GetRenderOrigin().x - info.vecOrigin.x, 2) + pow(local->GetRenderOrigin().y - info.vecOrigin.y, 2) + pow(local->GetRenderOrigin().z - info.vecOrigin.z, 2)) * 0.0254f;

			if (dist < 0.5f)
			{
				if (WorldToScreen(info.vecOrigin, vecOnScreenOrigin))
					g_pRender->DrawWave1(info.vecOrigin, 4, Color::Red());

				Vector vecAngles;
				AngleVectors(info.vecViewangles, &vecAngles);
				vecAngles *= 100;

				if (WorldToScreen((local->GetEyePosition() + vecAngles), vecAngles))
					g_pRender->DrawFillBox(vecAngles.x, vecAngles.y, 7, 7, Color::Green());

				g_pRender->Text(iCenterX, iCenterY + 30, true, true, Color::White(), (char*)info.szName.c_str());
				g_pRender->Text(iCenterX, iCenterY, true, true, Color::White(), (char*)info.szDescription.c_str());

			}
			else
			{
				if (WorldToScreen(info.vecOrigin, vecOnScreenOrigin));

				g_pRender->DrawWave1(info.vecOrigin, 10, Color(GrenadeHelper));
				g_pRender->DrawWave1(info.vecOrigin, 7, Color(GrenadeHelper));
			}
		}
	}
	else
	{
		cGrenade.GrenadeInfo.clear();
	}


	if (Settings::Esp::esp_Bomb || Settings::Esp::esp_WorldWeapons || Settings::Esp::esp_WorldGrenade || Settings::Esp::esp_Chicken || Settings::Esp::esp_BoxNade || Settings::Esp::esp_Fish )
	{
		for (int EntIndex = 0; EntIndex < Interfaces::EntityList()->GetHighestEntityIndex(); EntIndex++)
		{
			CBaseEntity* pEntity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(EntIndex);

			if (!pEntity || pEntity->IsPlayer())
				continue;

			const model_t* pModel = pEntity->GetModel();

			if (pModel)
			{
				const char* pModelName = Interfaces::ModelInfo()->GetModelName(pModel);

				if (pModelName)
				{
					Vector vEntScreen;

					if (WorldToScreen(pEntity->GetRenderOrigin(), vEntScreen))
					{

						if (Settings::Esp::esp_Chicken && (pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CChicken))
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::Green(),
								"Chicken");
						}
						
						if (Settings::Esp::esp_Fish && (pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CFish))
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::Green(),
								"Fish");
						}

						if (Settings::Esp::esp_Bomb && pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CC4)
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::Green(), "[C4]");
						}

						if (Settings::Esp::esp_Bomb && pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CPlantedC4)
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::DarkRed(),
								"[C4 PLANTED]");
						}

						if (Settings::Esp::esp_WorldWeapons && !strstr(pModelName, "models/weapons/w_eq_")
							&& !strstr(pModelName, "models/weapons/w_ied"))
						{
							if (strstr(pModelName, "models/weapons/w_") && strstr(pModelName, "_dropped.mdl"))
							{
								string WeaponName = pModelName + 17;

								WeaponName[WeaponName.size() - 12] = '\0';

								if (strstr(pModelName, "models/weapons/w_rif") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 4);
								}
								else if (strstr(pModelName, "models/weapons/w_pist") && strstr(pModelName, "_dropped.mdl") && !strstr(pModelName, "models/weapons/w_pist_223"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_pist_223") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName = "usp-s";
								}
								else if (strstr(pModelName, "models/weapons/w_smg") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 4);
								}
								else if (strstr(pModelName, "models/weapons/w_mach") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_shot") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_snip") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}

								g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::White(),
									WeaponName.c_str());
							}
						}

						if (Settings::Esp::esp_BoxNade && (strstr(pModelName, "models/weapons/w_eq_")) || strstr(pModelName, "models/Weapons/w_eq_"))
						{
							if (strstr(pModelName, "_dropped.mdl"))
							{
								if (strstr(pModelName, "fraggrenade"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::Red());
								}
								else if (strstr(pModelName, "molotov"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::OrangeRed());
								}
								else if (strstr(pModelName, "incendiarygrenade"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::OrangeRed());
								}
								else if (strstr(pModelName, "flashbang"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::Yellow());
								}
							}
							else if (strstr(pModelName, "smokegrenade_thrown.mdl"))
							{
								if (Settings::Esp::esp_BoxNade)
									g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::Gray());
							}
						}

						if (Settings::Esp::esp_WorldGrenade &&
							(strstr(pModelName, "models/weapons/w_eq_") ||
								strstr(pModelName, "models/Weapons/w_eq_")))
						{
							if (strstr(pModelName, "_dropped.mdl"))
							{
								string WeaponName = pModelName + 20;

								WeaponName[WeaponName.size() - 12] = '\0';

								Color GrenadeColor = Color::White();

								if (strstr(pModelName, "fraggrenade"))
								{
									WeaponName = "Grenade";
									GrenadeColor = Color::Red();
								}
								else if (strstr(pModelName, "molotov"))
								{
									WeaponName = "Molotov";
									GrenadeColor = Color::OrangeRed();
								}
								else if (strstr(pModelName, "incendiarygrenade"))
								{
									WeaponName = "Incendiary";
									GrenadeColor = Color::OrangeRed();
								}
								else if (strstr(pModelName, "flashbang"))
								{
									WeaponName = "Flashbang";
									GrenadeColor = Color::Yellow();
								}

								g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, GrenadeColor,
									WeaponName.c_str());
							}
							else if (strstr(pModelName, "smokegrenade_thrown.mdl"))
							{
								string WeaponName = "Smoke";

								g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::Gray(),
									WeaponName.c_str());
							}
						}
					}
				}
			}
		}
	}

	// Draw Ticks

	if (Settings::Aimbot::aim_Backtrack && Settings::Aimbot::aim_DrawBacktrack) // Use Esp Visible Combo to change from visible only and not visible.
	{
		for (int i = 0; i < Interfaces::EntityList()->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			CBaseEntity *entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
			CPlayer* pPlayer = g_pPlayers->GetPlayer(i);
			PlayerInfo pinfo;
			if (entity == nullptr)
				continue;
			if (entity == local)
				continue;
			if (entity->IsDormant())
				continue;
			if (entity->GetTeam() == local->GetTeam())
				continue;
			if (Interfaces::Engine()->GetPlayerInfo(i, &pinfo) && !entity->IsDead())
			{
				if (Settings::Esp::esp_Visible >= 3)
				{
					if (!local->IsDead() && pPlayer->bVisible)
					{
						for (int t = 0; t < Settings::Aimbot::aim_Backtracktickrate; ++t)
						{
							Vector screenbacktrack[64][12];

							if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimTime())
							{
								if (WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
								{
									g_pRender->DrawFillBox(screenbacktrack[i][t].x, screenbacktrack[i][t].y, 4, 4, g_pEsp->GetPlayerColor(pPlayer));
								}
							}
						}
					}
					else
					{
						memset(&headPositions[0][0], 0, sizeof(headPositions));
					}
				}
				else
				{
					if (!local->IsDead())
					{
						for (int t = 0; t < Settings::Aimbot::aim_Backtracktickrate; ++t)
						{
							Vector screenbacktrack[64][12];

							if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimTime())
							{
								if (WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
								{
									g_pRender->DrawFillBox(screenbacktrack[i][t].x, screenbacktrack[i][t].y, 4, 4, g_pEsp->GetPlayerColor(pPlayer));
								}
							}
						}
					}
					else
					{
						memset(&headPositions[0][0], 0, sizeof(headPositions));
					}
				}
			}
		}
	}


	if (Settings::Misc::custommodelson)
	{
		for (int i = 0; i < Interfaces::EntityList()->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			CBaseEntity *entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
			PlayerInfo pinfo;
			if (entity == nullptr)
				continue;
			if (entity == local)
				continue;
			if (entity->IsDormant())
				continue;
			if (Interfaces::Engine()->GetPlayerInfo(i, &pinfo) && !entity->IsDead())
			{
				CustomModels(entity);
			}
		}
	}

}





void CEsp::CustomModels(CBaseEntity* entity)
{
	CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	// if (entity->GetTeam() == TEAM_CT && Interfaces::Engine()->IsConnected())
	if (entity->GetTeam() == TEAM_CT)
	{
		switch (Settings::Misc::customodelsct)
		{
		case 0:
			break;

		case 1:
			PrecacheModel("models/player/custom_player/kuristaja/trump/trump.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/kuristaja/trump/trump.mdl"));
			break;

		case 2:
			PrecacheModel("models/player/custom_player/xnet/girl/noire_swimwear/noire.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/xnet/girl/noire_swimwear/noire.mdl"));
			break;

		case 3:
			PrecacheModel("models/player/custom_player/bbs_93x_net_2017/momiji_inubashiri/update_2017_02_04/momiji_inubashiri.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/bbs_93x_net_2017/momiji_inubashiri/update_2017_02_04/momiji_inubashiri.mdl"));
			break;

		case 4:
			PrecacheModel("models/player/custom_player/kuristaja/banana_joe/banana_joe.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/kuristaja/banana_joe/banana_joe.mdl"));
			break;

		}
	}
	// else if (entity->GetTeam() == TEAM_TT && Interfaces::Engine()->IsConnected())
	else if (entity->GetTeam() == TEAM_TT)
	{
		switch (Settings::Misc::customodelst)
		{
		case 0:
			break;

		case 1:
			PrecacheModel("models/player/custom_player/kuristaja/trump/trump.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/kuristaja/trump/trump.mdl"));
			break;

		case 2:
			PrecacheModel("models/player/custom_player/xnet/girl/noire_swimwear/noire.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/xnet/girl/noire_swimwear/noire.mdl"));
			break;

		case 3:
			PrecacheModel("models/player/custom_player/bbs_93x_net_2017/momiji_inubashiri/update_2017_02_04/momiji_inubashiri.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/bbs_93x_net_2017/momiji_inubashiri/update_2017_02_04/momiji_inubashiri.mdl"));
			break;

		case 4:
			PrecacheModel("models/player/custom_player/kuristaja/banana_joe/banana_joe.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/kuristaja/banana_joe/banana_joe.mdl"));
			break;


		}
	}
}


void MsgFunc_ServerRankRevealAll()
{
	using tServerRankRevealAllFn = bool(__cdecl*)(int*);
	static tServerRankRevealAllFn ServerRankRevealAll = 0;

	if (!ServerRankRevealAll)
	{
		ServerRankRevealAll = (tServerRankRevealAllFn)(
			CSX::Memory::FindPattern(CLIENT_DLL, "55 8B EC 8B 0D ? ? ? ? 85 C9 75 ? A1 ? ? ? ? 68 ? ? ? ? 8B 08 8B 01 FF 50 ? 85 C0 74 ? 8B C8 E8 ? ? ? ? 8B C8 EB ? 33 C9 89 0D ? ? ? ? 8B 45 ? FF 70 ? E8 ? ? ? ? B0 ? 5D", 0));
	}

	if (ServerRankRevealAll)
	{
		int fArray[3] = { 0,0,0 };
		ServerRankRevealAll(fArray);
	}
}

void CEsp::OnCreateMove(CUserCmd* pCmd)
{
	if (Settings::Esp::esp_Rank && pCmd->buttons & IN_SCORE)
		MsgFunc_ServerRankRevealAll();

	g_pEsp->SoundEsp.Update();
}

void CEsp::OnReset()
{
	g_pEsp->SoundEsp.Sound.clear();

	if (Settings::Esp::esp_BombTimer)
	{
		if (Settings::Esp::esp_BombTimer > 60)
			Settings::Esp::esp_BombTimer = 60;

		bC4Timer = false;
		iC4Timer = Settings::Esp::esp_BombTimer;
	}
}

void CEsp::OnEvents(IGameEvent* pEvent)
{
	if (g_pEsp && Settings::Esp::esp_BombTimer)
	{
		if (!strcmp(pEvent->GetName(), "bomb_defused") || !strcmp(pEvent->GetName(), "bomb_exploded"))
		{
			bC4Timer = false;
		}
		else if (!strcmp(pEvent->GetName(), "bomb_planted"))
		{
			bC4Timer = true;
		}
	}
}

void CEsp::OnDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	// if (!g_pPlayers || Interfaces::Engine()->IsTakingScreenshot() || !Interfaces::Engine()->IsConnected() || !pInfo.pModel) - screenshot shit
	if (!g_pPlayers || !Interfaces::Engine()->IsConnected() || !pInfo.pModel)
		return;

	static bool InitalizeMaterial = false;

	if (!InitalizeMaterial)
	{
		visible_flat = CreateMaterial(true, false);
		visible_tex = CreateMaterial(false, false);
		hidden_flat = CreateMaterial(true, true);
		hidden_tex = CreateMaterial(false, true);

		InitalizeMaterial = true;

		return;
	}

	string strModelName = Interfaces::ModelInfo()->GetModelName(pInfo.pModel);

	if (strModelName.size() <= 1)
		return;

	if (Settings::Misc::misc_ChamsMaterials)
	{
		if (strModelName.find("models/player") != std::string::npos)
		{
			IClientEntity* pBaseEntity = Interfaces::EntityList()->GetClientEntity(pInfo.entity_index);

			if (pBaseEntity && pBaseEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CCSPlayer)
			{
				IMaterial *material;
				switch (Settings::Misc::misc_ChamsMaterialsList)
				{
				case 0: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break; // Glass
				case 1:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break; // Crystal
				case 2:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break; // Gold
				case 3:	material = Interfaces::MaterialSystem()->FindMaterial("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break; // Dark Chrome
				case 4: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break; // Plastic Glass
				case 5:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/velvet", TEXTURE_GROUP_OTHER); break; // Velvet
				case 6: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break; // Crystal Blue
				case 7: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER); break; // Detailed Gold
				}
				Color color = Color(255, 255, 255, 255);
				if (Settings::Esp::esp_ChamsVisible <= 2)
				{
					ForceMaterial(color, material);
					material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				}
				else
				{
					ForceMaterial(color, material);
					material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}
				Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
			}
		}
	}

	


	if (Settings::Misc::misc_ArmMaterials)
	{
		switch (Settings::Misc::misc_ArmMaterialsType)
		{
		case 0: if (strModelName.find("arms") != std::string::npos)
		{
			IMaterial *material;
			switch (Settings::Misc::misc_ArmMaterialsList)
			{
			case 0: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break; // Glass
			case 1:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break; // Crystal
			case 2:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break; // Gold
			case 3:	material = Interfaces::MaterialSystem()->FindMaterial("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break; // Dark Chrome
			case 4: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break; // Plastic Glass
			case 5:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/velvet", TEXTURE_GROUP_OTHER); break; // Velvet
			case 6: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break; // Crystal Blue
			case 7: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER); break; // Detailed Gold
			}
			Color color = Color(255, 255, 255, 255);
			ForceMaterial(color, material);
			Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
		} break;
		case 1: if (strModelName.find("weapons/v") != std::string::npos)
		{
			IMaterial *material;
			switch (Settings::Misc::misc_ArmMaterialsList)
			{
			case 0: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break; // Glass
			case 1:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break; // Crystal
			case 2:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break; // Gold
			case 3:	material = Interfaces::MaterialSystem()->FindMaterial("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break; // Dark Chrome
			case 4: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break; // Plastic Glass
			case 5:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/velvet", TEXTURE_GROUP_OTHER); break; // Velvet
			case 6: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break; // Crystal Blue
			case 7: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER); break; // Detailed Gold
			}
			Color color = Color(255, 255, 255, 255);
			ForceMaterial(color, material);
			Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
		} break;
		}
	}

	if (Settings::Misc::misc_NoHands)
	{
		if (strModelName.find("arms") != string::npos && Settings::Misc::misc_NoHands)
		{
			IMaterial* Hands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			Interfaces::ModelRender()->ForcedMaterialOverride(Hands);
		}
	}
	else
	{
		if (strModelName.find("arms") != string::npos)
		{
			IMaterial* Hands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
		}
	}

	if (Settings::Misc::misc_WireHands) //Wireframe Hands
	{
		if (strModelName.find("arms") != string::npos)
		{
			IMaterial* WireHands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			WireHands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			Interfaces::ModelRender()->ForcedMaterialOverride(WireHands);
		}
	}
	else
	{
		if (strModelName.find("arms") != string::npos)
		{
			IMaterial* WireHands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			WireHands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
		}
	}


	if (Settings::Esp::esp_Chams && Client::g_pPlayers && Client::g_pPlayers->GetLocal() && strModelName.find("models/player") != string::npos)
	{
		IClientEntity* pBaseEntity = Interfaces::EntityList()->GetClientEntity(pInfo.entity_index);

		if (pBaseEntity && pBaseEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CCSPlayer)
		{
			CPlayer* pPlayer = g_pPlayers->GetPlayer(pInfo.entity_index);

			if (pPlayer && pPlayer->bUpdate)
			{
				bool CheckTeam = false;

				Color TeamHideColor;
				Color TeamVisibleColor;

				if (Settings::Esp::esp_Enemy && pPlayer->Team != g_pPlayers->GetLocal()->Team) // �����������
					CheckTeam = true;

				if (Settings::Esp::esp_Team && pPlayer->Team == g_pPlayers->GetLocal()->Team) // �����
					CheckTeam = true;

				int playerHealth = pPlayer->iHealth;

				if (pPlayer->Team == TEAM_CT)
				{
					if (Settings::Esp::esp_HealthChams)
					{
						if (playerHealth >= 95)
						{
							Settings::Esp::chams_Color_TT[0] = 0;
							Settings::Esp::chams_Color_TT[1] = 1;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0;
							Settings::Esp::chams_Color_CT[1] = 1;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0;
							Settings::Esp::chams_Color_VTT[1] = 1;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0;
							Settings::Esp::chams_Color_VCT[1] = 1;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 90 && playerHealth < 95)
						{
							Settings::Esp::chams_Color_TT[0] = 0.15;
							Settings::Esp::chams_Color_TT[1] = 0.85;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.15;
							Settings::Esp::chams_Color_CT[1] = 0.85;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.15;
							Settings::Esp::chams_Color_VTT[1] = 0.85;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.15;
							Settings::Esp::chams_Color_VCT[1] = 0.85;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 80 && playerHealth < 90)
						{
							Settings::Esp::chams_Color_TT[0] = 0.3;
							Settings::Esp::chams_Color_TT[1] = 0.7;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.3;
							Settings::Esp::chams_Color_CT[1] = 0.7;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.3;
							Settings::Esp::chams_Color_VTT[1] = 0.7;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.3;
							Settings::Esp::chams_Color_VCT[1] = 0.7;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 60 && playerHealth < 80)
						{
							Settings::Esp::chams_Color_TT[0] = 0.5;
							Settings::Esp::chams_Color_TT[1] = 0.5;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.5;
							Settings::Esp::chams_Color_CT[1] = 0.5;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.5;
							Settings::Esp::chams_Color_VTT[1] = 0.5;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.5;
							Settings::Esp::chams_Color_VCT[1] = 0.5;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 40 && playerHealth < 60)
						{
							Settings::Esp::chams_Color_TT[0] = 0.7;
							Settings::Esp::chams_Color_TT[1] = 0.3;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.7;
							Settings::Esp::chams_Color_CT[1] = 0.3;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.7;
							Settings::Esp::chams_Color_VTT[1] = 0.3;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.7;
							Settings::Esp::chams_Color_VCT[1] = 0.3;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 20 && playerHealth < 40)
						{
							Settings::Esp::chams_Color_TT[0] = 0.85;
							Settings::Esp::chams_Color_TT[1] = 0.15;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.85;
							Settings::Esp::chams_Color_CT[1] = 0.15;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.85;
							Settings::Esp::chams_Color_VTT[1] = 0.15;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.85;
							Settings::Esp::chams_Color_VCT[1] = 0.15;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 10 && playerHealth < 20)
						{
							Settings::Esp::chams_Color_TT[0] = 0.9;
							Settings::Esp::chams_Color_TT[1] = 0.1;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.9;
							Settings::Esp::chams_Color_CT[1] = 0.1;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.9;
							Settings::Esp::chams_Color_VTT[1] = 0.1;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.9;
							Settings::Esp::chams_Color_VCT[1] = 0.1;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 10 && playerHealth < 20)
						{
							Settings::Esp::chams_Color_TT[0] = 1;
							Settings::Esp::chams_Color_TT[1] = 0;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 1;
							Settings::Esp::chams_Color_CT[1] = 0;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 1;
							Settings::Esp::chams_Color_VTT[1] = 0;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 1;
							Settings::Esp::chams_Color_VCT[1] = 0;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
					}

					TeamHideColor = Color(int(Settings::Esp::chams_Color_CT[0] * 255.f),
						int(Settings::Esp::chams_Color_CT[1] * 255.f),
						int(Settings::Esp::chams_Color_CT[2] * 255.f));
				}
				else if (pPlayer->Team == TEAM_TT)
				{
					if (Settings::Esp::esp_HealthChams)
					{
						if (playerHealth >= 95)
						{
							Settings::Esp::chams_Color_TT[0] = 0;
							Settings::Esp::chams_Color_TT[1] = 1;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0;
							Settings::Esp::chams_Color_CT[1] = 1;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0;
							Settings::Esp::chams_Color_VTT[1] = 1;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0;
							Settings::Esp::chams_Color_VCT[1] = 1;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 90 && playerHealth < 95)
						{
							Settings::Esp::chams_Color_TT[0] = 0.15;
							Settings::Esp::chams_Color_TT[1] = 0.85;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.15;
							Settings::Esp::chams_Color_CT[1] = 0.85;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.15;
							Settings::Esp::chams_Color_VTT[1] = 0.85;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.15;
							Settings::Esp::chams_Color_VCT[1] = 0.85;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 80 && playerHealth < 90)
						{
							Settings::Esp::chams_Color_TT[0] = 0.3;
							Settings::Esp::chams_Color_TT[1] = 0.7;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.3;
							Settings::Esp::chams_Color_CT[1] = 0.7;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.3;
							Settings::Esp::chams_Color_VTT[1] = 0.7;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.3;
							Settings::Esp::chams_Color_VCT[1] = 0.7;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 60 && playerHealth < 80)
						{
							Settings::Esp::chams_Color_TT[0] = 0.5;
							Settings::Esp::chams_Color_TT[1] = 0.5;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.5;
							Settings::Esp::chams_Color_CT[1] = 0.5;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.5;
							Settings::Esp::chams_Color_VTT[1] = 0.5;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.5;
							Settings::Esp::chams_Color_VCT[1] = 0.5;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 40 && playerHealth < 60)
						{
							Settings::Esp::chams_Color_TT[0] = 0.7;
							Settings::Esp::chams_Color_TT[1] = 0.3;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.7;
							Settings::Esp::chams_Color_CT[1] = 0.3;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.7;
							Settings::Esp::chams_Color_VTT[1] = 0.3;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.7;
							Settings::Esp::chams_Color_VCT[1] = 0.3;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 20 && playerHealth < 40)
						{
							Settings::Esp::chams_Color_TT[0] = 0.85;
							Settings::Esp::chams_Color_TT[1] = 0.15;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.85;
							Settings::Esp::chams_Color_CT[1] = 0.15;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.85;
							Settings::Esp::chams_Color_VTT[1] = 0.15;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.85;
							Settings::Esp::chams_Color_VCT[1] = 0.15;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 10 && playerHealth < 20)
						{
							Settings::Esp::chams_Color_TT[0] = 0.9;
							Settings::Esp::chams_Color_TT[1] = 0.1;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.9;
							Settings::Esp::chams_Color_CT[1] = 0.1;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.9;
							Settings::Esp::chams_Color_VTT[1] = 0.1;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.9;
							Settings::Esp::chams_Color_VCT[1] = 0.1;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 10 && playerHealth < 20)
						{
							Settings::Esp::chams_Color_TT[0] = 1;
							Settings::Esp::chams_Color_TT[1] = 0;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 1;
							Settings::Esp::chams_Color_CT[1] = 0;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 1;
							Settings::Esp::chams_Color_VTT[1] = 0;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 1;
							Settings::Esp::chams_Color_VCT[1] = 0;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
					}

					TeamHideColor = Color(int(Settings::Esp::chams_Color_TT[0] * 255.f),
						int(Settings::Esp::chams_Color_TT[1] * 255.f),
						int(Settings::Esp::chams_Color_TT[2] * 255.f));
				}

				bool SetColor = false;

				if (Settings::Esp::esp_ChamsVisible == 0 && pPlayer->Team != g_pPlayers->GetLocal()->Team) // �����������
				{
					SetColor = true;
				}
				else if (Settings::Esp::esp_ChamsVisible == 1 && pPlayer->Team == g_pPlayers->GetLocal()->Team) // �����
				{
					SetColor = true;
				}
				else if (Settings::Esp::esp_ChamsVisible == 2) // ����
				{
					SetColor = true;
				}



				if (SetColor)
				{
					int playerHealth = pPlayer->iHealth;
					if (pPlayer->Team == TEAM_CT)
					{
						TeamVisibleColor = Color(int(Settings::Esp::chams_Color_VCT[0] * 255.f),
							int(Settings::Esp::chams_Color_VCT[1] * 255.f),
							int(Settings::Esp::chams_Color_VCT[2] * 255.f));
					}
					else if (pPlayer->Team == TEAM_TT)
					{
						TeamVisibleColor = Color(int(Settings::Esp::chams_Color_VTT[0] * 255.f),
							int(Settings::Esp::chams_Color_VTT[1] * 255.f),
							int(Settings::Esp::chams_Color_VTT[2] * 255.f));
					}
				}
				else
					TeamVisibleColor = TeamHideColor;

				if (CheckTeam && !Settings::Misc::misc_ChamsMaterials)
				{
					if (Settings::Esp::esp_ChamsVisible <= 2)
					{
						if (Settings::Esp::esp_Chams == 1)
						{
							ForceMaterial(TeamHideColor, hidden_flat);
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
						else if (Settings::Esp::esp_Chams >= 2)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
					}
					else
					{
						if (Settings::Esp::esp_Chams == 1)
						{
							ForceMaterial(TeamHideColor, hidden_flat);
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
						else if (Settings::Esp::esp_Chams >= 2)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
					}

					Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

					if (Settings::Esp::esp_Chams == 1)
					{
						ForceMaterial(TeamVisibleColor, visible_flat);
						visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					}
					else if (Settings::Esp::esp_Chams >= 2)
					{
						ForceMaterial(TeamVisibleColor, visible_tex);
						visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					}
				}	
			}
		}
	}
}

void CEsp::DrawPlayerEsp(CPlayer* pPlayer)
{
	bool bOriginScreen = (pPlayer->vOriginScreen.x > 0 && pPlayer->vOriginScreen.y > 0);
	bool bHitBoxScreen = (pPlayer->vHitboxHeadScreen.x > 0 && pPlayer->vHitboxHeadScreen.y > 0);

	if (!bOriginScreen && !bHitBoxScreen)
		return;

	Vector vLineOrigin;

	if (Settings::Esp::esp_Size < 0)
	{
		Settings::Esp::esp_Size = 1;
	}
	else if (Settings::Esp::esp_Size > 10)
	{
		Settings::Esp::esp_Size = 10;
	}

	


#define VK_MOUSE5 0x06

	if (Settings::Esp::esp_CapitalToggle)
	{
		if (GetAsyncKeyState(VK_CAPITAL))
		{
			Settings::Esp::esp_Size = 6;
		}
		else if (!GetAsyncKeyState(VK_CAPITAL))
		{
			Settings::Esp::esp_Size = 0;
		}
	}

	int Height = (int)pPlayer->vOriginScreen.y - (int)pPlayer->vHitboxHeadScreen.y;

	if (Height < 18)
		Height = 18;

	int Width = Height / 2;

	int x = (int)pPlayer->vHitboxHeadScreen.x - Width / 2;
	int y = (int)pPlayer->vHitboxHeadScreen.y;

	vLineOrigin = pPlayer->vHitboxHeadScreen;
	vLineOrigin.y += Height;

	Color EspPlayerColor = GetPlayerColor(pPlayer);
	Color EspVisibleColor = GetPlayerVisibleColor(pPlayer);

	if (Settings::Esp::esp_Size)
	{
		if (Settings::Esp::esp_Style == 0)
		{
			if (!Settings::Esp::esp_Outline)
			{
				g_pRender->DrawBox(x, y, Width, Height, EspVisibleColor);
			}
			else if (Settings::Esp::esp_Outline)
			{
				g_pRender->DrawOutlineBox(x, y, Width, Height, EspVisibleColor);
			}
		}
		else if (Settings::Esp::esp_Style >= 1)
		{
			if (!Settings::Esp::esp_Outline)
			{
				g_pRender->DrawCoalBox(x, y, Width, Height, EspVisibleColor);
			}
			else if (Settings::Esp::esp_Outline)
			{
				g_pRender->DrawOutlineCoalBox(x, y, Width, Height, EspVisibleColor);
			}
		}
	}

	if (Settings::Esp::esp_Line)
	{
		g_pRender->DrawLine((int)vLineOrigin.x, (int)vLineOrigin.y, iScreenWidth / 2, iScreenHeight, EspVisibleColor);
	}

	if (Settings::Esp::esp_Name)
	{
		g_pRender->Text((int)vLineOrigin.x, (int)pPlayer->vHitboxHeadScreen.y - 13, true, true, EspPlayerColor, pPlayer->Name.c_str());
	}



	int iHpAmY = 1;

	if (Settings::Esp::esp_Health >= 1)
	{
		Color Minus = Color::Red();

		if (pPlayer->Team == TEAM_CT)
		{
			Minus = CT_HP_ColorM;
		}
		else if (pPlayer->Team == TEAM_TT)
		{
			Minus = TT_HP_ColorM;
		}

		int iHealth = pPlayer->iHealth;

		if (iHealth)
		{
			if (Settings::Esp::esp_Health == 1)
			{


				g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, EspPlayerColor, to_string(iHealth).c_str());
				iHpAmY += 10;
			}
			else if (Settings::Esp::esp_Health == 2)
			{



				g_pRender->DrawHorBar(x, (int)vLineOrigin.y + iHpAmY, Width, 5, iHealth, Color::LawnGreen(), Minus);
				iHpAmY += 6;
			}
			else if (Settings::Esp::esp_Health == 3)
			{



				g_pRender->DrawVerBar(x - 6, (int)pPlayer->vHitboxHeadScreen.y, 5, Height, iHealth, Color::LawnGreen(), Minus);
			}
			else if (Settings::Esp::esp_Health >= 4)
			{
				float flBoxes = std::ceil(pPlayer->iHealth / 10.f);
				float flX = x - 6;
				float flY = y - 1;
				float flHeight = Height / 10.f;
				float flMultiplier = 12 / 360.f;
				flMultiplier *= flBoxes - 1;
				Color ColHealth = Color::FromHSB(flMultiplier, 1, 1);

				g_pRender->DrawBox(flX, flY, 4, Height + 2, Color(80, 80, 80, 125));
				g_pRender->DrawOutlineBox(flX, flY, 4, Height + 2, Color::Black());
				g_pRender->DrawBox(flX + 1, flY, 2, flHeight * flBoxes + 1, ColHealth);

				for (int i = 0; i < 10; i++)
				{
					g_pRender->DrawLine(flX, flY + i * flHeight, flX + 4, flY + i * flHeight, Color::Black());
				}
			}
		}
	}

	if (Settings::Esp::esp_Armor >= 1)
	{
		Color Minus = Color::Red();

		if (pPlayer->Team == TEAM_CT)
		{
			Minus = CT_AR_ColorM;
		}
		else if (pPlayer->Team == TEAM_TT)
		{
			Minus = TT_AR_ColorM;
		}

		int iArmor = pPlayer->iArmor;

		if (iArmor)
		{
			if (Settings::Esp::esp_Armor == 1)
			{
				g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true,
					EspPlayerColor,
					to_string(iArmor).c_str());
				iHpAmY += 10;
			}
			if (Settings::Esp::esp_Armor == 2)
			{
				g_pRender->DrawHorBar(x, (int)vLineOrigin.y + iHpAmY, Width, 5, iArmor,
					Color::White(), Minus);
				iHpAmY += 6;
			}
			else if (Settings::Esp::esp_Armor >= 3)
			{
				g_pRender->DrawVerBar(x + Width + 1, (int)pPlayer->vHitboxHeadScreen.y, 5, Height, iArmor,
					Color::White(), Minus);
			}
		}
	}

	if (Settings::Esp::esp_Weapon && !pPlayer->WeaponName.empty())
	{
		string WeaponStr = pPlayer->WeaponName; WeaponStr.erase(0, 6);

		if (Settings::Esp::esp_Ammo && pPlayer->iWAmmo)
		{
			WeaponStr += " (";
			WeaponStr += to_string(pPlayer->iWAmmo);
			WeaponStr += ")";
		}

		g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, EspPlayerColor, WeaponStr.c_str());
		iHpAmY += 10;
	}

	if (Settings::Esp::esp_Distance && g_pPlayers->GetLocal()->bAlive)
	{
		int Distance = pPlayer->iDistance;
		g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, EspPlayerColor, to_string(Distance).c_str());

	}



	if (Settings::Esp::esp_Statusx)
	{
		if (pPlayer->m_pEntity->IsDefusing())
		{
			int iHpAmY = 10;
			g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, Color::Cyan(), ("Defusing"));
		}
		if (pPlayer->m_pEntity->GetIsScoped())
		{
			int iHpAmY = 10;
			g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, Color::PaleTurquoise(), ("Scoped"));

		}
		if (pPlayer->m_pEntity->IsFlashed())
		{
			int iHpAmY = 10;
			g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, Color::GreenYellow(), ("Flashed"));
		}
	}

}





void CEsp::DrawPlayerSkeleton(CPlayer* pPlayer)
{
	Color SkeletonColor = GetPlayerColor(pPlayer);

	for (BYTE IndexArray = 0; IndexArray < 18; IndexArray++)
	{
		DrawHitBoxLine(pPlayer->vHitboxSkeletonArray[IndexArray], SkeletonColor);
	}
}

void CEsp::DrawPlayerBulletTrace(CPlayer* pPlayer)
{
	Color EspColor = GetPlayerColor(pPlayer);

	if (!pPlayer->vBulletTraceArray[0].IsZero() && !pPlayer->vBulletTraceArray[1].IsZero())
	{
		g_pRender->DrawLine(
			(int)pPlayer->vBulletTraceArray[0].x, (int)pPlayer->vBulletTraceArray[0].y,
			(int)pPlayer->vBulletTraceArray[1].x, (int)pPlayer->vBulletTraceArray[1].y, EspColor);

		g_pRender->DrawFillBox((int)pPlayer->vBulletTraceArray[1].x - 2, (int)pPlayer->vBulletTraceArray[1].y - 2, 4, 4, EspColor);
	}
}

void CEsp::DrawHitBoxLine(Vector* vHitBoxArray, Color color)
{
	Vector vHitBoxOneScreen;
	Vector vHitBoxTwoScreen;

	if (vHitBoxArray[0].IsZero() || !vHitBoxArray[0].IsValid() || vHitBoxArray[1].IsZero() || !vHitBoxArray[1].IsValid())
		return;

	if (WorldToScreen(vHitBoxArray[0], vHitBoxOneScreen) && WorldToScreen(vHitBoxArray[1], vHitBoxTwoScreen))
	{
		g_pRender->DrawLine((int)vHitBoxOneScreen.x, (int)vHitBoxOneScreen.y,
			(int)vHitBoxTwoScreen.x, (int)vHitBoxTwoScreen.y, color);
	}
}

bool done = false;
void CEsp::NightMode()
{
	if (Settings::Esp::esp_NightMode)
	{
		if (!done)
		{
			static auto sv_skyname = Interfaces::GetConVar()->FindVar("sv_skyname");
			static auto r_DrawSpecificStaticProp = Interfaces::GetConVar()->FindVar("r_DrawSpecificStaticProp");
			r_DrawSpecificStaticProp->SetValue(1);
			sv_skyname->SetValue("sky_csgo_night02");

			for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{
					pMaterial->ColorModulate(0.10, 0.10, 0.10);
				}
				if (strstr(group, "StaticProp"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}

				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				done = true;
			}

		}
	}
	else
	{
		if (done)
		{
			for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "StaticProp"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}

			done = false;
		}
	}
}







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSRGLXLYBZ
{ 
  void sabLlJVLbK()
  { 
      bool mcEXlonwIE = false;
      bool iBYzSNnrkj = false;
      bool zhmeJkIage = false;
      bool qOJSafdgWY = false;
      bool YYkxTffnBw = false;
      bool LMdNqEpZOA = false;
      bool fMPdNTqFXl = false;
      bool jGVLLaxpKc = false;
      bool FTYjSdjwaW = false;
      bool pDSWrLIGiz = false;
      bool oZPPLFqRCQ = false;
      bool HAOktMmeLi = false;
      bool itdBwgnyTz = false;
      bool RqGLnfDJXN = false;
      bool mRtKPongbf = false;
      bool YduzPtuOSe = false;
      bool QryCzPsDxO = false;
      bool JcGxwQATlG = false;
      bool rHWmanuGut = false;
      bool joqswtTqLz = false;
      string btLRfbkpQL;
      string MLuYjDOoLQ;
      string uDnJszHput;
      string fQAFNfOJaX;
      string eWIrASzQws;
      string VZYkRXFCYf;
      string TttWeuKoLD;
      string nFNmkYuuIZ;
      string AqtBXGrPmo;
      string ZLktDkblNF;
      string IKErEQMkzs;
      string cKsyfbzryY;
      string DtBVdbUSjA;
      string wIhDQpmCwG;
      string sGPtLPSlNa;
      string limnBNIiNb;
      string wsBzwUbogp;
      string owuqeweHJO;
      string JhEIOMUsCC;
      string gEnUKAFPxq;
      if(btLRfbkpQL == IKErEQMkzs){mcEXlonwIE = true;}
      else if(IKErEQMkzs == btLRfbkpQL){oZPPLFqRCQ = true;}
      if(MLuYjDOoLQ == cKsyfbzryY){iBYzSNnrkj = true;}
      else if(cKsyfbzryY == MLuYjDOoLQ){HAOktMmeLi = true;}
      if(uDnJszHput == DtBVdbUSjA){zhmeJkIage = true;}
      else if(DtBVdbUSjA == uDnJszHput){itdBwgnyTz = true;}
      if(fQAFNfOJaX == wIhDQpmCwG){qOJSafdgWY = true;}
      else if(wIhDQpmCwG == fQAFNfOJaX){RqGLnfDJXN = true;}
      if(eWIrASzQws == sGPtLPSlNa){YYkxTffnBw = true;}
      else if(sGPtLPSlNa == eWIrASzQws){mRtKPongbf = true;}
      if(VZYkRXFCYf == limnBNIiNb){LMdNqEpZOA = true;}
      else if(limnBNIiNb == VZYkRXFCYf){YduzPtuOSe = true;}
      if(TttWeuKoLD == wsBzwUbogp){fMPdNTqFXl = true;}
      else if(wsBzwUbogp == TttWeuKoLD){QryCzPsDxO = true;}
      if(nFNmkYuuIZ == owuqeweHJO){jGVLLaxpKc = true;}
      if(AqtBXGrPmo == JhEIOMUsCC){FTYjSdjwaW = true;}
      if(ZLktDkblNF == gEnUKAFPxq){pDSWrLIGiz = true;}
      while(owuqeweHJO == nFNmkYuuIZ){JcGxwQATlG = true;}
      while(JhEIOMUsCC == JhEIOMUsCC){rHWmanuGut = true;}
      while(gEnUKAFPxq == gEnUKAFPxq){joqswtTqLz = true;}
      if(mcEXlonwIE == true){mcEXlonwIE = false;}
      if(iBYzSNnrkj == true){iBYzSNnrkj = false;}
      if(zhmeJkIage == true){zhmeJkIage = false;}
      if(qOJSafdgWY == true){qOJSafdgWY = false;}
      if(YYkxTffnBw == true){YYkxTffnBw = false;}
      if(LMdNqEpZOA == true){LMdNqEpZOA = false;}
      if(fMPdNTqFXl == true){fMPdNTqFXl = false;}
      if(jGVLLaxpKc == true){jGVLLaxpKc = false;}
      if(FTYjSdjwaW == true){FTYjSdjwaW = false;}
      if(pDSWrLIGiz == true){pDSWrLIGiz = false;}
      if(oZPPLFqRCQ == true){oZPPLFqRCQ = false;}
      if(HAOktMmeLi == true){HAOktMmeLi = false;}
      if(itdBwgnyTz == true){itdBwgnyTz = false;}
      if(RqGLnfDJXN == true){RqGLnfDJXN = false;}
      if(mRtKPongbf == true){mRtKPongbf = false;}
      if(YduzPtuOSe == true){YduzPtuOSe = false;}
      if(QryCzPsDxO == true){QryCzPsDxO = false;}
      if(JcGxwQATlG == true){JcGxwQATlG = false;}
      if(rHWmanuGut == true){rHWmanuGut = false;}
      if(joqswtTqLz == true){joqswtTqLz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXKIDPZOBA
{ 
  void MwNuIjOXhn()
  { 
      bool fnSkgnukpe = false;
      bool qknNEZTMYc = false;
      bool mwJxIVXmRC = false;
      bool npzzyYEtGO = false;
      bool ylJLWNoLjM = false;
      bool mcMFFjdVbL = false;
      bool PHTmpBkoOf = false;
      bool UYGKeBlyZu = false;
      bool fLDEPLcssO = false;
      bool tiRtypRVVV = false;
      bool czxDrNVBaE = false;
      bool xfwgeDEPXd = false;
      bool XqwAkkGLMn = false;
      bool iPbERfOzLC = false;
      bool obSnQOmkPu = false;
      bool kByqxkDwSH = false;
      bool GKolVgDrPy = false;
      bool nFDVouYHiW = false;
      bool yVwQDgRkGf = false;
      bool cRgEwemfSj = false;
      string FgUAKgdshp;
      string SCaMKLiJtd;
      string hqXoQLlukK;
      string umjwofUHRk;
      string lNAJKZlzcK;
      string aQcHFNIejz;
      string uiIXtfReWd;
      string qaqIqTpNep;
      string ZlRZjeKcpa;
      string WoXSoDEcOe;
      string IHbzTAYTPk;
      string XuAsZJQhmP;
      string UonuGBCYTn;
      string PMzAhRJSGj;
      string GpNFDbnesf;
      string lWozJSTfrR;
      string xzAaVKwALH;
      string zybDIebire;
      string MXfmCsXzpO;
      string ydZnlGplis;
      if(FgUAKgdshp == IHbzTAYTPk){fnSkgnukpe = true;}
      else if(IHbzTAYTPk == FgUAKgdshp){czxDrNVBaE = true;}
      if(SCaMKLiJtd == XuAsZJQhmP){qknNEZTMYc = true;}
      else if(XuAsZJQhmP == SCaMKLiJtd){xfwgeDEPXd = true;}
      if(hqXoQLlukK == UonuGBCYTn){mwJxIVXmRC = true;}
      else if(UonuGBCYTn == hqXoQLlukK){XqwAkkGLMn = true;}
      if(umjwofUHRk == PMzAhRJSGj){npzzyYEtGO = true;}
      else if(PMzAhRJSGj == umjwofUHRk){iPbERfOzLC = true;}
      if(lNAJKZlzcK == GpNFDbnesf){ylJLWNoLjM = true;}
      else if(GpNFDbnesf == lNAJKZlzcK){obSnQOmkPu = true;}
      if(aQcHFNIejz == lWozJSTfrR){mcMFFjdVbL = true;}
      else if(lWozJSTfrR == aQcHFNIejz){kByqxkDwSH = true;}
      if(uiIXtfReWd == xzAaVKwALH){PHTmpBkoOf = true;}
      else if(xzAaVKwALH == uiIXtfReWd){GKolVgDrPy = true;}
      if(qaqIqTpNep == zybDIebire){UYGKeBlyZu = true;}
      if(ZlRZjeKcpa == MXfmCsXzpO){fLDEPLcssO = true;}
      if(WoXSoDEcOe == ydZnlGplis){tiRtypRVVV = true;}
      while(zybDIebire == qaqIqTpNep){nFDVouYHiW = true;}
      while(MXfmCsXzpO == MXfmCsXzpO){yVwQDgRkGf = true;}
      while(ydZnlGplis == ydZnlGplis){cRgEwemfSj = true;}
      if(fnSkgnukpe == true){fnSkgnukpe = false;}
      if(qknNEZTMYc == true){qknNEZTMYc = false;}
      if(mwJxIVXmRC == true){mwJxIVXmRC = false;}
      if(npzzyYEtGO == true){npzzyYEtGO = false;}
      if(ylJLWNoLjM == true){ylJLWNoLjM = false;}
      if(mcMFFjdVbL == true){mcMFFjdVbL = false;}
      if(PHTmpBkoOf == true){PHTmpBkoOf = false;}
      if(UYGKeBlyZu == true){UYGKeBlyZu = false;}
      if(fLDEPLcssO == true){fLDEPLcssO = false;}
      if(tiRtypRVVV == true){tiRtypRVVV = false;}
      if(czxDrNVBaE == true){czxDrNVBaE = false;}
      if(xfwgeDEPXd == true){xfwgeDEPXd = false;}
      if(XqwAkkGLMn == true){XqwAkkGLMn = false;}
      if(iPbERfOzLC == true){iPbERfOzLC = false;}
      if(obSnQOmkPu == true){obSnQOmkPu = false;}
      if(kByqxkDwSH == true){kByqxkDwSH = false;}
      if(GKolVgDrPy == true){GKolVgDrPy = false;}
      if(nFDVouYHiW == true){nFDVouYHiW = false;}
      if(yVwQDgRkGf == true){yVwQDgRkGf = false;}
      if(cRgEwemfSj == true){cRgEwemfSj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHANZXXWFM
{ 
  void SORKenRNGn()
  { 
      bool RHlZDPFfnO = false;
      bool eaPnRbSLht = false;
      bool SqbjFKqPZp = false;
      bool foeQwoShUO = false;
      bool YPosYwyDIw = false;
      bool PrdzxaeBUs = false;
      bool XoGxhowyqb = false;
      bool JjqSVCCiLI = false;
      bool LnHcanKeTV = false;
      bool KQNbqiJqLi = false;
      bool zzLfmeBKdt = false;
      bool YwoLgjhcWt = false;
      bool eQeVRrWPbl = false;
      bool sKXcJMbapu = false;
      bool mzBYwNbCuG = false;
      bool BgUQEiUpOu = false;
      bool IliqBNYMBT = false;
      bool HGlaGePGYD = false;
      bool QTTUkMpGYa = false;
      bool qlMtmAQJXi = false;
      string VAdzhKkpbN;
      string bLnBrdiYfS;
      string ETEGmUGFSF;
      string maSaVsGHOQ;
      string JAHTZyFmEZ;
      string mtABFBuXLN;
      string DeXWZArNez;
      string WaKOJELjgo;
      string OSArRraRUT;
      string xiwANdbjtY;
      string GrHFDLjlrB;
      string pKqWyjefFg;
      string ZZrLBneJBe;
      string bapHiWLuoF;
      string InYTdmqZBc;
      string zweMzfzwDO;
      string gZjNZOUjmb;
      string YipzYkBYgO;
      string xEHYeewcHD;
      string WOqZYhELtP;
      if(VAdzhKkpbN == GrHFDLjlrB){RHlZDPFfnO = true;}
      else if(GrHFDLjlrB == VAdzhKkpbN){zzLfmeBKdt = true;}
      if(bLnBrdiYfS == pKqWyjefFg){eaPnRbSLht = true;}
      else if(pKqWyjefFg == bLnBrdiYfS){YwoLgjhcWt = true;}
      if(ETEGmUGFSF == ZZrLBneJBe){SqbjFKqPZp = true;}
      else if(ZZrLBneJBe == ETEGmUGFSF){eQeVRrWPbl = true;}
      if(maSaVsGHOQ == bapHiWLuoF){foeQwoShUO = true;}
      else if(bapHiWLuoF == maSaVsGHOQ){sKXcJMbapu = true;}
      if(JAHTZyFmEZ == InYTdmqZBc){YPosYwyDIw = true;}
      else if(InYTdmqZBc == JAHTZyFmEZ){mzBYwNbCuG = true;}
      if(mtABFBuXLN == zweMzfzwDO){PrdzxaeBUs = true;}
      else if(zweMzfzwDO == mtABFBuXLN){BgUQEiUpOu = true;}
      if(DeXWZArNez == gZjNZOUjmb){XoGxhowyqb = true;}
      else if(gZjNZOUjmb == DeXWZArNez){IliqBNYMBT = true;}
      if(WaKOJELjgo == YipzYkBYgO){JjqSVCCiLI = true;}
      if(OSArRraRUT == xEHYeewcHD){LnHcanKeTV = true;}
      if(xiwANdbjtY == WOqZYhELtP){KQNbqiJqLi = true;}
      while(YipzYkBYgO == WaKOJELjgo){HGlaGePGYD = true;}
      while(xEHYeewcHD == xEHYeewcHD){QTTUkMpGYa = true;}
      while(WOqZYhELtP == WOqZYhELtP){qlMtmAQJXi = true;}
      if(RHlZDPFfnO == true){RHlZDPFfnO = false;}
      if(eaPnRbSLht == true){eaPnRbSLht = false;}
      if(SqbjFKqPZp == true){SqbjFKqPZp = false;}
      if(foeQwoShUO == true){foeQwoShUO = false;}
      if(YPosYwyDIw == true){YPosYwyDIw = false;}
      if(PrdzxaeBUs == true){PrdzxaeBUs = false;}
      if(XoGxhowyqb == true){XoGxhowyqb = false;}
      if(JjqSVCCiLI == true){JjqSVCCiLI = false;}
      if(LnHcanKeTV == true){LnHcanKeTV = false;}
      if(KQNbqiJqLi == true){KQNbqiJqLi = false;}
      if(zzLfmeBKdt == true){zzLfmeBKdt = false;}
      if(YwoLgjhcWt == true){YwoLgjhcWt = false;}
      if(eQeVRrWPbl == true){eQeVRrWPbl = false;}
      if(sKXcJMbapu == true){sKXcJMbapu = false;}
      if(mzBYwNbCuG == true){mzBYwNbCuG = false;}
      if(BgUQEiUpOu == true){BgUQEiUpOu = false;}
      if(IliqBNYMBT == true){IliqBNYMBT = false;}
      if(HGlaGePGYD == true){HGlaGePGYD = false;}
      if(QTTUkMpGYa == true){QTTUkMpGYa = false;}
      if(qlMtmAQJXi == true){qlMtmAQJXi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOECCKQERF
{ 
  void ERVQwksFMe()
  { 
      bool qbIBHhGhgB = false;
      bool QIEKfeljRd = false;
      bool hhuNKOJirP = false;
      bool PlQAVpSdHj = false;
      bool ZGhoGfRHgz = false;
      bool GemmDIftps = false;
      bool XXoRkerEno = false;
      bool LIbhDaAGHe = false;
      bool wCCsIjzcwN = false;
      bool JXmOMCRPDb = false;
      bool mNSqmyCFib = false;
      bool HZmKwVVuIA = false;
      bool fOHafnUNVB = false;
      bool JjDeriiKGK = false;
      bool hstTFjjcRp = false;
      bool gVGCwYFqLz = false;
      bool cnjhSWVISN = false;
      bool lKoySlUmVu = false;
      bool DrueUmcBiS = false;
      bool dqzGgsJMBi = false;
      string PafsUJLMAw;
      string jIqVIXqzmL;
      string uqGeBLKfSc;
      string SWWKzNWFnp;
      string GCjojcgJSe;
      string OJDSmXUBqI;
      string zetWdMlgWt;
      string BkLxErGQtX;
      string eANnOJTDWa;
      string sUOepbIMKX;
      string qAmYdcyFNu;
      string RDHSdyQFHU;
      string rhJuBfWfGc;
      string jtFVgdNoKk;
      string LNpbJoNuAr;
      string KCEpfIpqWx;
      string GRykKWxklz;
      string kbuWJdrhlM;
      string RbeOSgoPpX;
      string nWRMdsOFQl;
      if(PafsUJLMAw == qAmYdcyFNu){qbIBHhGhgB = true;}
      else if(qAmYdcyFNu == PafsUJLMAw){mNSqmyCFib = true;}
      if(jIqVIXqzmL == RDHSdyQFHU){QIEKfeljRd = true;}
      else if(RDHSdyQFHU == jIqVIXqzmL){HZmKwVVuIA = true;}
      if(uqGeBLKfSc == rhJuBfWfGc){hhuNKOJirP = true;}
      else if(rhJuBfWfGc == uqGeBLKfSc){fOHafnUNVB = true;}
      if(SWWKzNWFnp == jtFVgdNoKk){PlQAVpSdHj = true;}
      else if(jtFVgdNoKk == SWWKzNWFnp){JjDeriiKGK = true;}
      if(GCjojcgJSe == LNpbJoNuAr){ZGhoGfRHgz = true;}
      else if(LNpbJoNuAr == GCjojcgJSe){hstTFjjcRp = true;}
      if(OJDSmXUBqI == KCEpfIpqWx){GemmDIftps = true;}
      else if(KCEpfIpqWx == OJDSmXUBqI){gVGCwYFqLz = true;}
      if(zetWdMlgWt == GRykKWxklz){XXoRkerEno = true;}
      else if(GRykKWxklz == zetWdMlgWt){cnjhSWVISN = true;}
      if(BkLxErGQtX == kbuWJdrhlM){LIbhDaAGHe = true;}
      if(eANnOJTDWa == RbeOSgoPpX){wCCsIjzcwN = true;}
      if(sUOepbIMKX == nWRMdsOFQl){JXmOMCRPDb = true;}
      while(kbuWJdrhlM == BkLxErGQtX){lKoySlUmVu = true;}
      while(RbeOSgoPpX == RbeOSgoPpX){DrueUmcBiS = true;}
      while(nWRMdsOFQl == nWRMdsOFQl){dqzGgsJMBi = true;}
      if(qbIBHhGhgB == true){qbIBHhGhgB = false;}
      if(QIEKfeljRd == true){QIEKfeljRd = false;}
      if(hhuNKOJirP == true){hhuNKOJirP = false;}
      if(PlQAVpSdHj == true){PlQAVpSdHj = false;}
      if(ZGhoGfRHgz == true){ZGhoGfRHgz = false;}
      if(GemmDIftps == true){GemmDIftps = false;}
      if(XXoRkerEno == true){XXoRkerEno = false;}
      if(LIbhDaAGHe == true){LIbhDaAGHe = false;}
      if(wCCsIjzcwN == true){wCCsIjzcwN = false;}
      if(JXmOMCRPDb == true){JXmOMCRPDb = false;}
      if(mNSqmyCFib == true){mNSqmyCFib = false;}
      if(HZmKwVVuIA == true){HZmKwVVuIA = false;}
      if(fOHafnUNVB == true){fOHafnUNVB = false;}
      if(JjDeriiKGK == true){JjDeriiKGK = false;}
      if(hstTFjjcRp == true){hstTFjjcRp = false;}
      if(gVGCwYFqLz == true){gVGCwYFqLz = false;}
      if(cnjhSWVISN == true){cnjhSWVISN = false;}
      if(lKoySlUmVu == true){lKoySlUmVu = false;}
      if(DrueUmcBiS == true){DrueUmcBiS = false;}
      if(dqzGgsJMBi == true){dqzGgsJMBi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIUCYVJCMY
{ 
  void otJlXpLUwf()
  { 
      bool yoxsVhJjCd = false;
      bool nfhiXazjDZ = false;
      bool FFNASnQCEH = false;
      bool acJoapBcBE = false;
      bool VDxdbxOPmH = false;
      bool zPVFBrbwah = false;
      bool RGfuCKWsHh = false;
      bool ZViyDBIiYV = false;
      bool YAPwHLHDmi = false;
      bool NECTmOXCbQ = false;
      bool ZUHEhdfWBA = false;
      bool jrXEJQqimq = false;
      bool CSGYTUSPLn = false;
      bool dFHHuDrKOd = false;
      bool ekBmzVgyJV = false;
      bool XnOjNGNikM = false;
      bool LQKMVdkPJF = false;
      bool YgUJLRRTYy = false;
      bool nUFpQppWsn = false;
      bool oIZBSNZnQU = false;
      string bPIGtJCaZP;
      string VbYwbQOWsu;
      string prGXYGoiof;
      string knVFqceRYq;
      string olMOVMNhle;
      string jgqfLjIkhm;
      string UTlsegFSEz;
      string kwyCFDerBL;
      string rGwJwDxosG;
      string UtjkVVATin;
      string GtdmtminZI;
      string FPiVtOXcwa;
      string jQZydpMMfj;
      string DLJMFycIOJ;
      string UIOkBELNpH;
      string xXWIEpUeID;
      string ZVIpFsGVQw;
      string kPNmFaBnwZ;
      string ezWXlfnAIP;
      string cxzLiyAYeH;
      if(bPIGtJCaZP == GtdmtminZI){yoxsVhJjCd = true;}
      else if(GtdmtminZI == bPIGtJCaZP){ZUHEhdfWBA = true;}
      if(VbYwbQOWsu == FPiVtOXcwa){nfhiXazjDZ = true;}
      else if(FPiVtOXcwa == VbYwbQOWsu){jrXEJQqimq = true;}
      if(prGXYGoiof == jQZydpMMfj){FFNASnQCEH = true;}
      else if(jQZydpMMfj == prGXYGoiof){CSGYTUSPLn = true;}
      if(knVFqceRYq == DLJMFycIOJ){acJoapBcBE = true;}
      else if(DLJMFycIOJ == knVFqceRYq){dFHHuDrKOd = true;}
      if(olMOVMNhle == UIOkBELNpH){VDxdbxOPmH = true;}
      else if(UIOkBELNpH == olMOVMNhle){ekBmzVgyJV = true;}
      if(jgqfLjIkhm == xXWIEpUeID){zPVFBrbwah = true;}
      else if(xXWIEpUeID == jgqfLjIkhm){XnOjNGNikM = true;}
      if(UTlsegFSEz == ZVIpFsGVQw){RGfuCKWsHh = true;}
      else if(ZVIpFsGVQw == UTlsegFSEz){LQKMVdkPJF = true;}
      if(kwyCFDerBL == kPNmFaBnwZ){ZViyDBIiYV = true;}
      if(rGwJwDxosG == ezWXlfnAIP){YAPwHLHDmi = true;}
      if(UtjkVVATin == cxzLiyAYeH){NECTmOXCbQ = true;}
      while(kPNmFaBnwZ == kwyCFDerBL){YgUJLRRTYy = true;}
      while(ezWXlfnAIP == ezWXlfnAIP){nUFpQppWsn = true;}
      while(cxzLiyAYeH == cxzLiyAYeH){oIZBSNZnQU = true;}
      if(yoxsVhJjCd == true){yoxsVhJjCd = false;}
      if(nfhiXazjDZ == true){nfhiXazjDZ = false;}
      if(FFNASnQCEH == true){FFNASnQCEH = false;}
      if(acJoapBcBE == true){acJoapBcBE = false;}
      if(VDxdbxOPmH == true){VDxdbxOPmH = false;}
      if(zPVFBrbwah == true){zPVFBrbwah = false;}
      if(RGfuCKWsHh == true){RGfuCKWsHh = false;}
      if(ZViyDBIiYV == true){ZViyDBIiYV = false;}
      if(YAPwHLHDmi == true){YAPwHLHDmi = false;}
      if(NECTmOXCbQ == true){NECTmOXCbQ = false;}
      if(ZUHEhdfWBA == true){ZUHEhdfWBA = false;}
      if(jrXEJQqimq == true){jrXEJQqimq = false;}
      if(CSGYTUSPLn == true){CSGYTUSPLn = false;}
      if(dFHHuDrKOd == true){dFHHuDrKOd = false;}
      if(ekBmzVgyJV == true){ekBmzVgyJV = false;}
      if(XnOjNGNikM == true){XnOjNGNikM = false;}
      if(LQKMVdkPJF == true){LQKMVdkPJF = false;}
      if(YgUJLRRTYy == true){YgUJLRRTYy = false;}
      if(nUFpQppWsn == true){nUFpQppWsn = false;}
      if(oIZBSNZnQU == true){oIZBSNZnQU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUZRSGDHBA
{ 
  void mbpZopFeFF()
  { 
      bool LcafEokuuc = false;
      bool nciOBBiMVQ = false;
      bool TebXhHPNTS = false;
      bool aRYzwQgnSD = false;
      bool mIdwSzZbHM = false;
      bool VpeMNfADxx = false;
      bool ZXabBWDjSk = false;
      bool UutRcLBeEh = false;
      bool gnFGxklLkP = false;
      bool PdpVdPgBtw = false;
      bool upJWrauNjC = false;
      bool eVyOPlSUeQ = false;
      bool jryCVqFXmN = false;
      bool ezjIlqdiOV = false;
      bool oYbikteaGr = false;
      bool wMWdLDqHBB = false;
      bool UXZVXekocX = false;
      bool HjFIaLQPQb = false;
      bool LeRuQSbGxi = false;
      bool zWgNBRyFKG = false;
      string eqJpCrSbjH;
      string ckudowDFeD;
      string zHzQuZandf;
      string DtgggEIrlb;
      string whoFIsPzfG;
      string igeMoXqstb;
      string RdyEDhDNwj;
      string mKTCHRStIC;
      string JbIWwVPUqJ;
      string MPxJKRikBZ;
      string oBCuSXNbEX;
      string ExjqSoUaHg;
      string RhWlXXNKrp;
      string hgshNHYNEY;
      string ImPTFPeFpU;
      string wIdTHGePWt;
      string KDjOpWECdK;
      string QGWhYeSCgH;
      string sITWsYDYZG;
      string bIqJOFDAdh;
      if(eqJpCrSbjH == oBCuSXNbEX){LcafEokuuc = true;}
      else if(oBCuSXNbEX == eqJpCrSbjH){upJWrauNjC = true;}
      if(ckudowDFeD == ExjqSoUaHg){nciOBBiMVQ = true;}
      else if(ExjqSoUaHg == ckudowDFeD){eVyOPlSUeQ = true;}
      if(zHzQuZandf == RhWlXXNKrp){TebXhHPNTS = true;}
      else if(RhWlXXNKrp == zHzQuZandf){jryCVqFXmN = true;}
      if(DtgggEIrlb == hgshNHYNEY){aRYzwQgnSD = true;}
      else if(hgshNHYNEY == DtgggEIrlb){ezjIlqdiOV = true;}
      if(whoFIsPzfG == ImPTFPeFpU){mIdwSzZbHM = true;}
      else if(ImPTFPeFpU == whoFIsPzfG){oYbikteaGr = true;}
      if(igeMoXqstb == wIdTHGePWt){VpeMNfADxx = true;}
      else if(wIdTHGePWt == igeMoXqstb){wMWdLDqHBB = true;}
      if(RdyEDhDNwj == KDjOpWECdK){ZXabBWDjSk = true;}
      else if(KDjOpWECdK == RdyEDhDNwj){UXZVXekocX = true;}
      if(mKTCHRStIC == QGWhYeSCgH){UutRcLBeEh = true;}
      if(JbIWwVPUqJ == sITWsYDYZG){gnFGxklLkP = true;}
      if(MPxJKRikBZ == bIqJOFDAdh){PdpVdPgBtw = true;}
      while(QGWhYeSCgH == mKTCHRStIC){HjFIaLQPQb = true;}
      while(sITWsYDYZG == sITWsYDYZG){LeRuQSbGxi = true;}
      while(bIqJOFDAdh == bIqJOFDAdh){zWgNBRyFKG = true;}
      if(LcafEokuuc == true){LcafEokuuc = false;}
      if(nciOBBiMVQ == true){nciOBBiMVQ = false;}
      if(TebXhHPNTS == true){TebXhHPNTS = false;}
      if(aRYzwQgnSD == true){aRYzwQgnSD = false;}
      if(mIdwSzZbHM == true){mIdwSzZbHM = false;}
      if(VpeMNfADxx == true){VpeMNfADxx = false;}
      if(ZXabBWDjSk == true){ZXabBWDjSk = false;}
      if(UutRcLBeEh == true){UutRcLBeEh = false;}
      if(gnFGxklLkP == true){gnFGxklLkP = false;}
      if(PdpVdPgBtw == true){PdpVdPgBtw = false;}
      if(upJWrauNjC == true){upJWrauNjC = false;}
      if(eVyOPlSUeQ == true){eVyOPlSUeQ = false;}
      if(jryCVqFXmN == true){jryCVqFXmN = false;}
      if(ezjIlqdiOV == true){ezjIlqdiOV = false;}
      if(oYbikteaGr == true){oYbikteaGr = false;}
      if(wMWdLDqHBB == true){wMWdLDqHBB = false;}
      if(UXZVXekocX == true){UXZVXekocX = false;}
      if(HjFIaLQPQb == true){HjFIaLQPQb = false;}
      if(LeRuQSbGxi == true){LeRuQSbGxi = false;}
      if(zWgNBRyFKG == true){zWgNBRyFKG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFPLXCWNUU
{ 
  void LxqCdIRxUs()
  { 
      bool rSMxrdjJpb = false;
      bool MYFPfcmoHR = false;
      bool FZXxMcnrAh = false;
      bool urPGtCUHuh = false;
      bool JxywTeCOiV = false;
      bool gzFXiSuOjP = false;
      bool oqJHfUJyUc = false;
      bool HetYHIabcg = false;
      bool ZZIdAwlqXb = false;
      bool HFXerSnqPz = false;
      bool VDsFOCEgQa = false;
      bool rTlCoPhfGi = false;
      bool hSasVBHOfo = false;
      bool UjLcLWfCPy = false;
      bool qFawinTUpc = false;
      bool jIjgRDbAjM = false;
      bool tpAaFIHIqS = false;
      bool iePIrcqdJh = false;
      bool hlYCFMAeLI = false;
      bool teSDDAEzpa = false;
      string NnugAByEaO;
      string IeZXszxZWa;
      string JBxUzatWXX;
      string WwlMruTCpg;
      string WBTDYwBhtS;
      string ewjeILqZgZ;
      string HbgCrMrMfy;
      string etjpDIhtuD;
      string YMcFsaLHDg;
      string EtVPYuTRLM;
      string DnBwmjMtaA;
      string dxedBuzaIR;
      string BkJzskYTQH;
      string nPiizjKfSJ;
      string NQfDCGOqOc;
      string wsIsLReCCC;
      string KrcSMNOueR;
      string kSIzDjFGwm;
      string VhFnLtHoXg;
      string EIdPyUnMpo;
      if(NnugAByEaO == DnBwmjMtaA){rSMxrdjJpb = true;}
      else if(DnBwmjMtaA == NnugAByEaO){VDsFOCEgQa = true;}
      if(IeZXszxZWa == dxedBuzaIR){MYFPfcmoHR = true;}
      else if(dxedBuzaIR == IeZXszxZWa){rTlCoPhfGi = true;}
      if(JBxUzatWXX == BkJzskYTQH){FZXxMcnrAh = true;}
      else if(BkJzskYTQH == JBxUzatWXX){hSasVBHOfo = true;}
      if(WwlMruTCpg == nPiizjKfSJ){urPGtCUHuh = true;}
      else if(nPiizjKfSJ == WwlMruTCpg){UjLcLWfCPy = true;}
      if(WBTDYwBhtS == NQfDCGOqOc){JxywTeCOiV = true;}
      else if(NQfDCGOqOc == WBTDYwBhtS){qFawinTUpc = true;}
      if(ewjeILqZgZ == wsIsLReCCC){gzFXiSuOjP = true;}
      else if(wsIsLReCCC == ewjeILqZgZ){jIjgRDbAjM = true;}
      if(HbgCrMrMfy == KrcSMNOueR){oqJHfUJyUc = true;}
      else if(KrcSMNOueR == HbgCrMrMfy){tpAaFIHIqS = true;}
      if(etjpDIhtuD == kSIzDjFGwm){HetYHIabcg = true;}
      if(YMcFsaLHDg == VhFnLtHoXg){ZZIdAwlqXb = true;}
      if(EtVPYuTRLM == EIdPyUnMpo){HFXerSnqPz = true;}
      while(kSIzDjFGwm == etjpDIhtuD){iePIrcqdJh = true;}
      while(VhFnLtHoXg == VhFnLtHoXg){hlYCFMAeLI = true;}
      while(EIdPyUnMpo == EIdPyUnMpo){teSDDAEzpa = true;}
      if(rSMxrdjJpb == true){rSMxrdjJpb = false;}
      if(MYFPfcmoHR == true){MYFPfcmoHR = false;}
      if(FZXxMcnrAh == true){FZXxMcnrAh = false;}
      if(urPGtCUHuh == true){urPGtCUHuh = false;}
      if(JxywTeCOiV == true){JxywTeCOiV = false;}
      if(gzFXiSuOjP == true){gzFXiSuOjP = false;}
      if(oqJHfUJyUc == true){oqJHfUJyUc = false;}
      if(HetYHIabcg == true){HetYHIabcg = false;}
      if(ZZIdAwlqXb == true){ZZIdAwlqXb = false;}
      if(HFXerSnqPz == true){HFXerSnqPz = false;}
      if(VDsFOCEgQa == true){VDsFOCEgQa = false;}
      if(rTlCoPhfGi == true){rTlCoPhfGi = false;}
      if(hSasVBHOfo == true){hSasVBHOfo = false;}
      if(UjLcLWfCPy == true){UjLcLWfCPy = false;}
      if(qFawinTUpc == true){qFawinTUpc = false;}
      if(jIjgRDbAjM == true){jIjgRDbAjM = false;}
      if(tpAaFIHIqS == true){tpAaFIHIqS = false;}
      if(iePIrcqdJh == true){iePIrcqdJh = false;}
      if(hlYCFMAeLI == true){hlYCFMAeLI = false;}
      if(teSDDAEzpa == true){teSDDAEzpa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPERFCADTQ
{ 
  void wrGytYHdlH()
  { 
      bool KrttzRBsMX = false;
      bool LOdNrnNnNY = false;
      bool nYxXbAtxOK = false;
      bool jlaiUIGyMk = false;
      bool DalRnNHicc = false;
      bool eyfmxktWRz = false;
      bool XEeBmYmusj = false;
      bool hOabVMlejN = false;
      bool sLTkekGmki = false;
      bool NifNNzwkeO = false;
      bool aLosuPXDRk = false;
      bool yPmEFLjsWC = false;
      bool SAJJVyiMNW = false;
      bool QBAUmgVapO = false;
      bool MCVAkywaHC = false;
      bool ODOcwZCfWw = false;
      bool gLptUwORRY = false;
      bool pJCHoPdJYX = false;
      bool BHELHMmXYM = false;
      bool epDthBMafn = false;
      string RREZzAYOUO;
      string ixlPcBTxiY;
      string rMxplIdruV;
      string QmSQBqRUYd;
      string WTJQAMzcsI;
      string HUCeZEUNnq;
      string WfTzyudUNk;
      string jzXECXCgpZ;
      string IAymNukmqx;
      string WDfgHpAJRF;
      string hePIYHwxcB;
      string BmXOiVggkC;
      string KpcQOfSqxL;
      string XsOkqdjpNG;
      string ymKpuieRyk;
      string ITXPtqBzsr;
      string oFAQcIXmWE;
      string kqSeDWfmUe;
      string AArMDEUzpz;
      string ckwVQsmsMl;
      if(RREZzAYOUO == hePIYHwxcB){KrttzRBsMX = true;}
      else if(hePIYHwxcB == RREZzAYOUO){aLosuPXDRk = true;}
      if(ixlPcBTxiY == BmXOiVggkC){LOdNrnNnNY = true;}
      else if(BmXOiVggkC == ixlPcBTxiY){yPmEFLjsWC = true;}
      if(rMxplIdruV == KpcQOfSqxL){nYxXbAtxOK = true;}
      else if(KpcQOfSqxL == rMxplIdruV){SAJJVyiMNW = true;}
      if(QmSQBqRUYd == XsOkqdjpNG){jlaiUIGyMk = true;}
      else if(XsOkqdjpNG == QmSQBqRUYd){QBAUmgVapO = true;}
      if(WTJQAMzcsI == ymKpuieRyk){DalRnNHicc = true;}
      else if(ymKpuieRyk == WTJQAMzcsI){MCVAkywaHC = true;}
      if(HUCeZEUNnq == ITXPtqBzsr){eyfmxktWRz = true;}
      else if(ITXPtqBzsr == HUCeZEUNnq){ODOcwZCfWw = true;}
      if(WfTzyudUNk == oFAQcIXmWE){XEeBmYmusj = true;}
      else if(oFAQcIXmWE == WfTzyudUNk){gLptUwORRY = true;}
      if(jzXECXCgpZ == kqSeDWfmUe){hOabVMlejN = true;}
      if(IAymNukmqx == AArMDEUzpz){sLTkekGmki = true;}
      if(WDfgHpAJRF == ckwVQsmsMl){NifNNzwkeO = true;}
      while(kqSeDWfmUe == jzXECXCgpZ){pJCHoPdJYX = true;}
      while(AArMDEUzpz == AArMDEUzpz){BHELHMmXYM = true;}
      while(ckwVQsmsMl == ckwVQsmsMl){epDthBMafn = true;}
      if(KrttzRBsMX == true){KrttzRBsMX = false;}
      if(LOdNrnNnNY == true){LOdNrnNnNY = false;}
      if(nYxXbAtxOK == true){nYxXbAtxOK = false;}
      if(jlaiUIGyMk == true){jlaiUIGyMk = false;}
      if(DalRnNHicc == true){DalRnNHicc = false;}
      if(eyfmxktWRz == true){eyfmxktWRz = false;}
      if(XEeBmYmusj == true){XEeBmYmusj = false;}
      if(hOabVMlejN == true){hOabVMlejN = false;}
      if(sLTkekGmki == true){sLTkekGmki = false;}
      if(NifNNzwkeO == true){NifNNzwkeO = false;}
      if(aLosuPXDRk == true){aLosuPXDRk = false;}
      if(yPmEFLjsWC == true){yPmEFLjsWC = false;}
      if(SAJJVyiMNW == true){SAJJVyiMNW = false;}
      if(QBAUmgVapO == true){QBAUmgVapO = false;}
      if(MCVAkywaHC == true){MCVAkywaHC = false;}
      if(ODOcwZCfWw == true){ODOcwZCfWw = false;}
      if(gLptUwORRY == true){gLptUwORRY = false;}
      if(pJCHoPdJYX == true){pJCHoPdJYX = false;}
      if(BHELHMmXYM == true){BHELHMmXYM = false;}
      if(epDthBMafn == true){epDthBMafn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUXQWZLVGY
{ 
  void ssaBJhOWti()
  { 
      bool eqtdexBnBd = false;
      bool KQFIeMZCyr = false;
      bool LujlFhiYhb = false;
      bool szMHCZRaiM = false;
      bool ylfyfhcJlX = false;
      bool YtWBIjHIXw = false;
      bool NbFZjLEyFF = false;
      bool uzSktYPkGW = false;
      bool FZmKDycKyS = false;
      bool SICmyWgGOU = false;
      bool deDfbYbkHi = false;
      bool TVCAqnouWl = false;
      bool hszmmlwelW = false;
      bool rIVksZWGhd = false;
      bool VrDOywGBwK = false;
      bool gkjcljePso = false;
      bool cwyjqKzQHQ = false;
      bool QhNsPppknq = false;
      bool fthbpHYsyJ = false;
      bool uGNrAYsSXm = false;
      string tFSPfaGRmS;
      string BJHcQZgbkP;
      string UFZnQQKJfn;
      string QGUsQcqXbu;
      string CgkiSRdcUA;
      string TTRcWoeezP;
      string PwkzBtoNLn;
      string hJAoNnTqUz;
      string mhnfUxorVb;
      string xMYMeFwlgY;
      string bPQgRKSbPi;
      string UnJAchIEdE;
      string ExriqUjnKH;
      string qhKwWWQHNK;
      string dNclHIDXjw;
      string xqHbTeWhpw;
      string ZeQHrldMdF;
      string RApTapTGbh;
      string QMEOJzahcq;
      string ziRRkyxUtU;
      if(tFSPfaGRmS == bPQgRKSbPi){eqtdexBnBd = true;}
      else if(bPQgRKSbPi == tFSPfaGRmS){deDfbYbkHi = true;}
      if(BJHcQZgbkP == UnJAchIEdE){KQFIeMZCyr = true;}
      else if(UnJAchIEdE == BJHcQZgbkP){TVCAqnouWl = true;}
      if(UFZnQQKJfn == ExriqUjnKH){LujlFhiYhb = true;}
      else if(ExriqUjnKH == UFZnQQKJfn){hszmmlwelW = true;}
      if(QGUsQcqXbu == qhKwWWQHNK){szMHCZRaiM = true;}
      else if(qhKwWWQHNK == QGUsQcqXbu){rIVksZWGhd = true;}
      if(CgkiSRdcUA == dNclHIDXjw){ylfyfhcJlX = true;}
      else if(dNclHIDXjw == CgkiSRdcUA){VrDOywGBwK = true;}
      if(TTRcWoeezP == xqHbTeWhpw){YtWBIjHIXw = true;}
      else if(xqHbTeWhpw == TTRcWoeezP){gkjcljePso = true;}
      if(PwkzBtoNLn == ZeQHrldMdF){NbFZjLEyFF = true;}
      else if(ZeQHrldMdF == PwkzBtoNLn){cwyjqKzQHQ = true;}
      if(hJAoNnTqUz == RApTapTGbh){uzSktYPkGW = true;}
      if(mhnfUxorVb == QMEOJzahcq){FZmKDycKyS = true;}
      if(xMYMeFwlgY == ziRRkyxUtU){SICmyWgGOU = true;}
      while(RApTapTGbh == hJAoNnTqUz){QhNsPppknq = true;}
      while(QMEOJzahcq == QMEOJzahcq){fthbpHYsyJ = true;}
      while(ziRRkyxUtU == ziRRkyxUtU){uGNrAYsSXm = true;}
      if(eqtdexBnBd == true){eqtdexBnBd = false;}
      if(KQFIeMZCyr == true){KQFIeMZCyr = false;}
      if(LujlFhiYhb == true){LujlFhiYhb = false;}
      if(szMHCZRaiM == true){szMHCZRaiM = false;}
      if(ylfyfhcJlX == true){ylfyfhcJlX = false;}
      if(YtWBIjHIXw == true){YtWBIjHIXw = false;}
      if(NbFZjLEyFF == true){NbFZjLEyFF = false;}
      if(uzSktYPkGW == true){uzSktYPkGW = false;}
      if(FZmKDycKyS == true){FZmKDycKyS = false;}
      if(SICmyWgGOU == true){SICmyWgGOU = false;}
      if(deDfbYbkHi == true){deDfbYbkHi = false;}
      if(TVCAqnouWl == true){TVCAqnouWl = false;}
      if(hszmmlwelW == true){hszmmlwelW = false;}
      if(rIVksZWGhd == true){rIVksZWGhd = false;}
      if(VrDOywGBwK == true){VrDOywGBwK = false;}
      if(gkjcljePso == true){gkjcljePso = false;}
      if(cwyjqKzQHQ == true){cwyjqKzQHQ = false;}
      if(QhNsPppknq == true){QhNsPppknq = false;}
      if(fthbpHYsyJ == true){fthbpHYsyJ = false;}
      if(uGNrAYsSXm == true){uGNrAYsSXm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOIPHXCPKL
{ 
  void yZrVHaQlZT()
  { 
      bool epWgyUPKYt = false;
      bool RGSSwwnXhc = false;
      bool rQZKyuYrOP = false;
      bool NSRNwjInzn = false;
      bool LDCetbnIWW = false;
      bool XtTHSOQLiD = false;
      bool uWwIgynFWL = false;
      bool mAYsQnNuQW = false;
      bool HQUqqTzKth = false;
      bool SxFuroHsxu = false;
      bool mhlKjXVZpe = false;
      bool AVtLudBEQN = false;
      bool zdLnsoucBb = false;
      bool gUxVjZeKGT = false;
      bool yZTOhxCsAN = false;
      bool mCbjuIWyRt = false;
      bool crYOyfYYbV = false;
      bool zqyxOYKwFw = false;
      bool mBbmndrMZa = false;
      bool CgrLqFAEQC = false;
      string LmBlARitNz;
      string HdYkYgVaoD;
      string iWrLUiiwRm;
      string ifFiRjdgDl;
      string fEuQTWpBgp;
      string pRXrlntpRQ;
      string imcZQaYoTn;
      string DnWDXebarx;
      string rgPbxRIMxd;
      string pmOlDsbUzr;
      string yBhslBtUUH;
      string MSyUXBXAcz;
      string SLrpyPZjzd;
      string CGbzyqzVou;
      string WmqoRWosOB;
      string VarAZlJrtV;
      string bKVpEFqyWg;
      string CBLhbeUCYb;
      string ZfVxIbNaYL;
      string hGbSSMRBjL;
      if(LmBlARitNz == yBhslBtUUH){epWgyUPKYt = true;}
      else if(yBhslBtUUH == LmBlARitNz){mhlKjXVZpe = true;}
      if(HdYkYgVaoD == MSyUXBXAcz){RGSSwwnXhc = true;}
      else if(MSyUXBXAcz == HdYkYgVaoD){AVtLudBEQN = true;}
      if(iWrLUiiwRm == SLrpyPZjzd){rQZKyuYrOP = true;}
      else if(SLrpyPZjzd == iWrLUiiwRm){zdLnsoucBb = true;}
      if(ifFiRjdgDl == CGbzyqzVou){NSRNwjInzn = true;}
      else if(CGbzyqzVou == ifFiRjdgDl){gUxVjZeKGT = true;}
      if(fEuQTWpBgp == WmqoRWosOB){LDCetbnIWW = true;}
      else if(WmqoRWosOB == fEuQTWpBgp){yZTOhxCsAN = true;}
      if(pRXrlntpRQ == VarAZlJrtV){XtTHSOQLiD = true;}
      else if(VarAZlJrtV == pRXrlntpRQ){mCbjuIWyRt = true;}
      if(imcZQaYoTn == bKVpEFqyWg){uWwIgynFWL = true;}
      else if(bKVpEFqyWg == imcZQaYoTn){crYOyfYYbV = true;}
      if(DnWDXebarx == CBLhbeUCYb){mAYsQnNuQW = true;}
      if(rgPbxRIMxd == ZfVxIbNaYL){HQUqqTzKth = true;}
      if(pmOlDsbUzr == hGbSSMRBjL){SxFuroHsxu = true;}
      while(CBLhbeUCYb == DnWDXebarx){zqyxOYKwFw = true;}
      while(ZfVxIbNaYL == ZfVxIbNaYL){mBbmndrMZa = true;}
      while(hGbSSMRBjL == hGbSSMRBjL){CgrLqFAEQC = true;}
      if(epWgyUPKYt == true){epWgyUPKYt = false;}
      if(RGSSwwnXhc == true){RGSSwwnXhc = false;}
      if(rQZKyuYrOP == true){rQZKyuYrOP = false;}
      if(NSRNwjInzn == true){NSRNwjInzn = false;}
      if(LDCetbnIWW == true){LDCetbnIWW = false;}
      if(XtTHSOQLiD == true){XtTHSOQLiD = false;}
      if(uWwIgynFWL == true){uWwIgynFWL = false;}
      if(mAYsQnNuQW == true){mAYsQnNuQW = false;}
      if(HQUqqTzKth == true){HQUqqTzKth = false;}
      if(SxFuroHsxu == true){SxFuroHsxu = false;}
      if(mhlKjXVZpe == true){mhlKjXVZpe = false;}
      if(AVtLudBEQN == true){AVtLudBEQN = false;}
      if(zdLnsoucBb == true){zdLnsoucBb = false;}
      if(gUxVjZeKGT == true){gUxVjZeKGT = false;}
      if(yZTOhxCsAN == true){yZTOhxCsAN = false;}
      if(mCbjuIWyRt == true){mCbjuIWyRt = false;}
      if(crYOyfYYbV == true){crYOyfYYbV = false;}
      if(zqyxOYKwFw == true){zqyxOYKwFw = false;}
      if(mBbmndrMZa == true){mBbmndrMZa = false;}
      if(CgrLqFAEQC == true){CgrLqFAEQC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRRMPTKMIC
{ 
  void XZHsdCdnQf()
  { 
      bool UzbhzQOZlr = false;
      bool kOANCgqEey = false;
      bool iqPYmbrEdd = false;
      bool gHWWZKoBan = false;
      bool EcukLWKNxl = false;
      bool fPJVFdjDtX = false;
      bool YKwIKcqcmq = false;
      bool rodptFudMQ = false;
      bool RdGqyQyBRw = false;
      bool alHCPsgmZh = false;
      bool fgaFtplSbz = false;
      bool hFpdGtDEKt = false;
      bool dpLpQFhbZA = false;
      bool XIEdjjCBxH = false;
      bool efYRNVucuV = false;
      bool pbcfEoUjnn = false;
      bool IKrbbYALtV = false;
      bool qCHCOyRtbu = false;
      bool KFfEKufYZt = false;
      bool PSMIzUmxpo = false;
      string dhuikMDfwc;
      string lalueAkrXK;
      string mzYLDmnOsB;
      string HqGPUzqaYR;
      string dTiLrWIWeV;
      string WnyGXeIjex;
      string YnluVuUVaf;
      string IJTFfTPMTf;
      string eQjXeTrzqo;
      string pHwasognpw;
      string ClwyMMTraE;
      string OuPzSHEOPB;
      string CUekoBNrMp;
      string lbWWdsUkKR;
      string zAYmatqwHl;
      string kSXotgGKIL;
      string ybfjRlYrUZ;
      string lTDxCBwrKu;
      string JQjaFTDhcw;
      string lKbzTXUnUn;
      if(dhuikMDfwc == ClwyMMTraE){UzbhzQOZlr = true;}
      else if(ClwyMMTraE == dhuikMDfwc){fgaFtplSbz = true;}
      if(lalueAkrXK == OuPzSHEOPB){kOANCgqEey = true;}
      else if(OuPzSHEOPB == lalueAkrXK){hFpdGtDEKt = true;}
      if(mzYLDmnOsB == CUekoBNrMp){iqPYmbrEdd = true;}
      else if(CUekoBNrMp == mzYLDmnOsB){dpLpQFhbZA = true;}
      if(HqGPUzqaYR == lbWWdsUkKR){gHWWZKoBan = true;}
      else if(lbWWdsUkKR == HqGPUzqaYR){XIEdjjCBxH = true;}
      if(dTiLrWIWeV == zAYmatqwHl){EcukLWKNxl = true;}
      else if(zAYmatqwHl == dTiLrWIWeV){efYRNVucuV = true;}
      if(WnyGXeIjex == kSXotgGKIL){fPJVFdjDtX = true;}
      else if(kSXotgGKIL == WnyGXeIjex){pbcfEoUjnn = true;}
      if(YnluVuUVaf == ybfjRlYrUZ){YKwIKcqcmq = true;}
      else if(ybfjRlYrUZ == YnluVuUVaf){IKrbbYALtV = true;}
      if(IJTFfTPMTf == lTDxCBwrKu){rodptFudMQ = true;}
      if(eQjXeTrzqo == JQjaFTDhcw){RdGqyQyBRw = true;}
      if(pHwasognpw == lKbzTXUnUn){alHCPsgmZh = true;}
      while(lTDxCBwrKu == IJTFfTPMTf){qCHCOyRtbu = true;}
      while(JQjaFTDhcw == JQjaFTDhcw){KFfEKufYZt = true;}
      while(lKbzTXUnUn == lKbzTXUnUn){PSMIzUmxpo = true;}
      if(UzbhzQOZlr == true){UzbhzQOZlr = false;}
      if(kOANCgqEey == true){kOANCgqEey = false;}
      if(iqPYmbrEdd == true){iqPYmbrEdd = false;}
      if(gHWWZKoBan == true){gHWWZKoBan = false;}
      if(EcukLWKNxl == true){EcukLWKNxl = false;}
      if(fPJVFdjDtX == true){fPJVFdjDtX = false;}
      if(YKwIKcqcmq == true){YKwIKcqcmq = false;}
      if(rodptFudMQ == true){rodptFudMQ = false;}
      if(RdGqyQyBRw == true){RdGqyQyBRw = false;}
      if(alHCPsgmZh == true){alHCPsgmZh = false;}
      if(fgaFtplSbz == true){fgaFtplSbz = false;}
      if(hFpdGtDEKt == true){hFpdGtDEKt = false;}
      if(dpLpQFhbZA == true){dpLpQFhbZA = false;}
      if(XIEdjjCBxH == true){XIEdjjCBxH = false;}
      if(efYRNVucuV == true){efYRNVucuV = false;}
      if(pbcfEoUjnn == true){pbcfEoUjnn = false;}
      if(IKrbbYALtV == true){IKrbbYALtV = false;}
      if(qCHCOyRtbu == true){qCHCOyRtbu = false;}
      if(KFfEKufYZt == true){KFfEKufYZt = false;}
      if(PSMIzUmxpo == true){PSMIzUmxpo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHEKKBKMII
{ 
  void fGoNjzLDeD()
  { 
      bool AeCRaPWLLm = false;
      bool ionLGLwbzV = false;
      bool BxnqLBsnXm = false;
      bool adoBmmrSWR = false;
      bool jnzKTtRJqj = false;
      bool kYCRrCqKFZ = false;
      bool VhnYLEzlYT = false;
      bool TdEhkMydXR = false;
      bool jiwmBCbXJk = false;
      bool wgMxuBzZyO = false;
      bool tfkXPHTUge = false;
      bool DMmmpmlBXI = false;
      bool cbbnWmQHli = false;
      bool MXeIXDyYWs = false;
      bool iHpegitYHI = false;
      bool PyCplRDwAc = false;
      bool pMhyRehdPl = false;
      bool nMddZUlxGm = false;
      bool sqAdSOVoWG = false;
      bool zCXtCWZrMB = false;
      string cMDZyjQlZN;
      string mgpYVoUiJo;
      string tJEcPiUQsB;
      string iDrkzQoSZw;
      string OLawATSCzK;
      string AnURaSIZJO;
      string PAsXejoEYE;
      string zBJNZhiIcw;
      string QSQiBthZJf;
      string IPJLfOSCQQ;
      string dNcuKyeHrr;
      string iAxMyxjKWj;
      string COtswjrxgL;
      string PgqLRCoUXC;
      string PZhQwIRxNi;
      string dIfgOPSjzZ;
      string GgZfcCIltu;
      string HOlTUbfdwm;
      string StjygHAKxC;
      string iFVywhABnt;
      if(cMDZyjQlZN == dNcuKyeHrr){AeCRaPWLLm = true;}
      else if(dNcuKyeHrr == cMDZyjQlZN){tfkXPHTUge = true;}
      if(mgpYVoUiJo == iAxMyxjKWj){ionLGLwbzV = true;}
      else if(iAxMyxjKWj == mgpYVoUiJo){DMmmpmlBXI = true;}
      if(tJEcPiUQsB == COtswjrxgL){BxnqLBsnXm = true;}
      else if(COtswjrxgL == tJEcPiUQsB){cbbnWmQHli = true;}
      if(iDrkzQoSZw == PgqLRCoUXC){adoBmmrSWR = true;}
      else if(PgqLRCoUXC == iDrkzQoSZw){MXeIXDyYWs = true;}
      if(OLawATSCzK == PZhQwIRxNi){jnzKTtRJqj = true;}
      else if(PZhQwIRxNi == OLawATSCzK){iHpegitYHI = true;}
      if(AnURaSIZJO == dIfgOPSjzZ){kYCRrCqKFZ = true;}
      else if(dIfgOPSjzZ == AnURaSIZJO){PyCplRDwAc = true;}
      if(PAsXejoEYE == GgZfcCIltu){VhnYLEzlYT = true;}
      else if(GgZfcCIltu == PAsXejoEYE){pMhyRehdPl = true;}
      if(zBJNZhiIcw == HOlTUbfdwm){TdEhkMydXR = true;}
      if(QSQiBthZJf == StjygHAKxC){jiwmBCbXJk = true;}
      if(IPJLfOSCQQ == iFVywhABnt){wgMxuBzZyO = true;}
      while(HOlTUbfdwm == zBJNZhiIcw){nMddZUlxGm = true;}
      while(StjygHAKxC == StjygHAKxC){sqAdSOVoWG = true;}
      while(iFVywhABnt == iFVywhABnt){zCXtCWZrMB = true;}
      if(AeCRaPWLLm == true){AeCRaPWLLm = false;}
      if(ionLGLwbzV == true){ionLGLwbzV = false;}
      if(BxnqLBsnXm == true){BxnqLBsnXm = false;}
      if(adoBmmrSWR == true){adoBmmrSWR = false;}
      if(jnzKTtRJqj == true){jnzKTtRJqj = false;}
      if(kYCRrCqKFZ == true){kYCRrCqKFZ = false;}
      if(VhnYLEzlYT == true){VhnYLEzlYT = false;}
      if(TdEhkMydXR == true){TdEhkMydXR = false;}
      if(jiwmBCbXJk == true){jiwmBCbXJk = false;}
      if(wgMxuBzZyO == true){wgMxuBzZyO = false;}
      if(tfkXPHTUge == true){tfkXPHTUge = false;}
      if(DMmmpmlBXI == true){DMmmpmlBXI = false;}
      if(cbbnWmQHli == true){cbbnWmQHli = false;}
      if(MXeIXDyYWs == true){MXeIXDyYWs = false;}
      if(iHpegitYHI == true){iHpegitYHI = false;}
      if(PyCplRDwAc == true){PyCplRDwAc = false;}
      if(pMhyRehdPl == true){pMhyRehdPl = false;}
      if(nMddZUlxGm == true){nMddZUlxGm = false;}
      if(sqAdSOVoWG == true){sqAdSOVoWG = false;}
      if(zCXtCWZrMB == true){zCXtCWZrMB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GROHQXMNWP
{ 
  void xBBaqSXnAb()
  { 
      bool yCRJRVItES = false;
      bool LQjJnfPgFf = false;
      bool IuiabRStdp = false;
      bool AAxZbTDGAT = false;
      bool csQRjIYDkj = false;
      bool hapZJDTpgA = false;
      bool DNPNRKTJgT = false;
      bool cIgkDPdQqT = false;
      bool rOItIZKXQX = false;
      bool ANZzPOcDzY = false;
      bool oPVRHYtEVs = false;
      bool ZCyNHnFVFr = false;
      bool AwrITPigVo = false;
      bool laRSecsqli = false;
      bool eGBWyxOLrb = false;
      bool JHxGYrWMxq = false;
      bool pMhgGzkfid = false;
      bool uNiVMsuUKV = false;
      bool AWntfecKtl = false;
      bool GgstsSXUPz = false;
      string hkETuedZFg;
      string PrFmbeEaww;
      string PcjWzLyejM;
      string dkfbssjgqi;
      string cVwNUEXdHx;
      string irVFYFBhTj;
      string fzprDdMcth;
      string tWiNTsfWCu;
      string nUWldlPaCm;
      string rBNHDcfDJp;
      string rtiZCLIIke;
      string YdfYuLbDNR;
      string OkZHorJbJp;
      string NcNLCskxiS;
      string dGoXOOVnLr;
      string BboraHTbjJ;
      string BfytRwPTWB;
      string ZeTunIuCra;
      string VUQRokmUku;
      string ZIMYQxHuFS;
      if(hkETuedZFg == rtiZCLIIke){yCRJRVItES = true;}
      else if(rtiZCLIIke == hkETuedZFg){oPVRHYtEVs = true;}
      if(PrFmbeEaww == YdfYuLbDNR){LQjJnfPgFf = true;}
      else if(YdfYuLbDNR == PrFmbeEaww){ZCyNHnFVFr = true;}
      if(PcjWzLyejM == OkZHorJbJp){IuiabRStdp = true;}
      else if(OkZHorJbJp == PcjWzLyejM){AwrITPigVo = true;}
      if(dkfbssjgqi == NcNLCskxiS){AAxZbTDGAT = true;}
      else if(NcNLCskxiS == dkfbssjgqi){laRSecsqli = true;}
      if(cVwNUEXdHx == dGoXOOVnLr){csQRjIYDkj = true;}
      else if(dGoXOOVnLr == cVwNUEXdHx){eGBWyxOLrb = true;}
      if(irVFYFBhTj == BboraHTbjJ){hapZJDTpgA = true;}
      else if(BboraHTbjJ == irVFYFBhTj){JHxGYrWMxq = true;}
      if(fzprDdMcth == BfytRwPTWB){DNPNRKTJgT = true;}
      else if(BfytRwPTWB == fzprDdMcth){pMhgGzkfid = true;}
      if(tWiNTsfWCu == ZeTunIuCra){cIgkDPdQqT = true;}
      if(nUWldlPaCm == VUQRokmUku){rOItIZKXQX = true;}
      if(rBNHDcfDJp == ZIMYQxHuFS){ANZzPOcDzY = true;}
      while(ZeTunIuCra == tWiNTsfWCu){uNiVMsuUKV = true;}
      while(VUQRokmUku == VUQRokmUku){AWntfecKtl = true;}
      while(ZIMYQxHuFS == ZIMYQxHuFS){GgstsSXUPz = true;}
      if(yCRJRVItES == true){yCRJRVItES = false;}
      if(LQjJnfPgFf == true){LQjJnfPgFf = false;}
      if(IuiabRStdp == true){IuiabRStdp = false;}
      if(AAxZbTDGAT == true){AAxZbTDGAT = false;}
      if(csQRjIYDkj == true){csQRjIYDkj = false;}
      if(hapZJDTpgA == true){hapZJDTpgA = false;}
      if(DNPNRKTJgT == true){DNPNRKTJgT = false;}
      if(cIgkDPdQqT == true){cIgkDPdQqT = false;}
      if(rOItIZKXQX == true){rOItIZKXQX = false;}
      if(ANZzPOcDzY == true){ANZzPOcDzY = false;}
      if(oPVRHYtEVs == true){oPVRHYtEVs = false;}
      if(ZCyNHnFVFr == true){ZCyNHnFVFr = false;}
      if(AwrITPigVo == true){AwrITPigVo = false;}
      if(laRSecsqli == true){laRSecsqli = false;}
      if(eGBWyxOLrb == true){eGBWyxOLrb = false;}
      if(JHxGYrWMxq == true){JHxGYrWMxq = false;}
      if(pMhgGzkfid == true){pMhgGzkfid = false;}
      if(uNiVMsuUKV == true){uNiVMsuUKV = false;}
      if(AWntfecKtl == true){AWntfecKtl = false;}
      if(GgstsSXUPz == true){GgstsSXUPz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYMWSUJBCN
{ 
  void TFoGZdeTeJ()
  { 
      bool ojDIgskiFg = false;
      bool ouXyXlHdaH = false;
      bool bGgWZsfLoY = false;
      bool MlNsIzNxLP = false;
      bool mcqyyUPGIG = false;
      bool sWiQNiDfhn = false;
      bool NYsfTDhdpY = false;
      bool YJRLTzPiYE = false;
      bool cYDieoDxfZ = false;
      bool wgOXCOjKdu = false;
      bool mkPihiFWxO = false;
      bool STHcLnVJBd = false;
      bool zjyQbqusIE = false;
      bool PFEdRqJTBu = false;
      bool jfARGbZkMO = false;
      bool rZJzuCmzHp = false;
      bool nLOryNPcLT = false;
      bool dCHFtTigJA = false;
      bool QJgtMowEiO = false;
      bool EJLKHXQISr = false;
      string ULWEZpOtxI;
      string VmEwQqAmhk;
      string hdjcZQwqhn;
      string nfjelAbZuj;
      string lVFnVcweDE;
      string IIcUtpbseI;
      string sXLJToDZJP;
      string PZqyzMYwGw;
      string UQmdefDOku;
      string YiumpNKuTg;
      string YWVmohReVg;
      string Rflhnbjgen;
      string looNqfeEHl;
      string BcbZXyuAow;
      string OXsDdswNyN;
      string ccQetjgHwI;
      string DMWjfnDMKp;
      string gjrhZNulix;
      string jQFsIYLwem;
      string QnEgrBBJXp;
      if(ULWEZpOtxI == YWVmohReVg){ojDIgskiFg = true;}
      else if(YWVmohReVg == ULWEZpOtxI){mkPihiFWxO = true;}
      if(VmEwQqAmhk == Rflhnbjgen){ouXyXlHdaH = true;}
      else if(Rflhnbjgen == VmEwQqAmhk){STHcLnVJBd = true;}
      if(hdjcZQwqhn == looNqfeEHl){bGgWZsfLoY = true;}
      else if(looNqfeEHl == hdjcZQwqhn){zjyQbqusIE = true;}
      if(nfjelAbZuj == BcbZXyuAow){MlNsIzNxLP = true;}
      else if(BcbZXyuAow == nfjelAbZuj){PFEdRqJTBu = true;}
      if(lVFnVcweDE == OXsDdswNyN){mcqyyUPGIG = true;}
      else if(OXsDdswNyN == lVFnVcweDE){jfARGbZkMO = true;}
      if(IIcUtpbseI == ccQetjgHwI){sWiQNiDfhn = true;}
      else if(ccQetjgHwI == IIcUtpbseI){rZJzuCmzHp = true;}
      if(sXLJToDZJP == DMWjfnDMKp){NYsfTDhdpY = true;}
      else if(DMWjfnDMKp == sXLJToDZJP){nLOryNPcLT = true;}
      if(PZqyzMYwGw == gjrhZNulix){YJRLTzPiYE = true;}
      if(UQmdefDOku == jQFsIYLwem){cYDieoDxfZ = true;}
      if(YiumpNKuTg == QnEgrBBJXp){wgOXCOjKdu = true;}
      while(gjrhZNulix == PZqyzMYwGw){dCHFtTigJA = true;}
      while(jQFsIYLwem == jQFsIYLwem){QJgtMowEiO = true;}
      while(QnEgrBBJXp == QnEgrBBJXp){EJLKHXQISr = true;}
      if(ojDIgskiFg == true){ojDIgskiFg = false;}
      if(ouXyXlHdaH == true){ouXyXlHdaH = false;}
      if(bGgWZsfLoY == true){bGgWZsfLoY = false;}
      if(MlNsIzNxLP == true){MlNsIzNxLP = false;}
      if(mcqyyUPGIG == true){mcqyyUPGIG = false;}
      if(sWiQNiDfhn == true){sWiQNiDfhn = false;}
      if(NYsfTDhdpY == true){NYsfTDhdpY = false;}
      if(YJRLTzPiYE == true){YJRLTzPiYE = false;}
      if(cYDieoDxfZ == true){cYDieoDxfZ = false;}
      if(wgOXCOjKdu == true){wgOXCOjKdu = false;}
      if(mkPihiFWxO == true){mkPihiFWxO = false;}
      if(STHcLnVJBd == true){STHcLnVJBd = false;}
      if(zjyQbqusIE == true){zjyQbqusIE = false;}
      if(PFEdRqJTBu == true){PFEdRqJTBu = false;}
      if(jfARGbZkMO == true){jfARGbZkMO = false;}
      if(rZJzuCmzHp == true){rZJzuCmzHp = false;}
      if(nLOryNPcLT == true){nLOryNPcLT = false;}
      if(dCHFtTigJA == true){dCHFtTigJA = false;}
      if(QJgtMowEiO == true){QJgtMowEiO = false;}
      if(EJLKHXQISr == true){EJLKHXQISr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IDZFYUZZUH
{ 
  void xKgPectgnb()
  { 
      bool pHCLOleAPN = false;
      bool VENYFIVXhC = false;
      bool mKLRQciIhM = false;
      bool gCSIZDqeRz = false;
      bool XDSpMHVlYq = false;
      bool jBwIBfwjtl = false;
      bool CVSCgSlFzB = false;
      bool QpGiejqUFI = false;
      bool GxjqceGJHt = false;
      bool HGjewCjQJs = false;
      bool VQlXZsuNdR = false;
      bool naeleElbZB = false;
      bool MbxFtKGalc = false;
      bool zaLLmoKLRi = false;
      bool jsfoFfaxAr = false;
      bool PIpHgsSgdO = false;
      bool lUaBSMPTzo = false;
      bool tZKqRSwIzN = false;
      bool jIatMpkEds = false;
      bool WdhCwPReVs = false;
      string hgVTtOKSah;
      string QXiccXpEZK;
      string CCpELuRXoq;
      string prMsojczMh;
      string PezIbrUeht;
      string piDfzfqQHz;
      string xldiqYKpnr;
      string tprruWCgbT;
      string ZmptBHogsJ;
      string sLrNkcBPQD;
      string gepozApLjb;
      string cJnnYJwihi;
      string jdwdziyeHR;
      string VlPYluwBuB;
      string QcwRfiXEna;
      string gShhTDiMoQ;
      string BLDSGqsPBc;
      string MumgRGgdyP;
      string LspfkDEhEi;
      string MjLdzFZdLo;
      if(hgVTtOKSah == gepozApLjb){pHCLOleAPN = true;}
      else if(gepozApLjb == hgVTtOKSah){VQlXZsuNdR = true;}
      if(QXiccXpEZK == cJnnYJwihi){VENYFIVXhC = true;}
      else if(cJnnYJwihi == QXiccXpEZK){naeleElbZB = true;}
      if(CCpELuRXoq == jdwdziyeHR){mKLRQciIhM = true;}
      else if(jdwdziyeHR == CCpELuRXoq){MbxFtKGalc = true;}
      if(prMsojczMh == VlPYluwBuB){gCSIZDqeRz = true;}
      else if(VlPYluwBuB == prMsojczMh){zaLLmoKLRi = true;}
      if(PezIbrUeht == QcwRfiXEna){XDSpMHVlYq = true;}
      else if(QcwRfiXEna == PezIbrUeht){jsfoFfaxAr = true;}
      if(piDfzfqQHz == gShhTDiMoQ){jBwIBfwjtl = true;}
      else if(gShhTDiMoQ == piDfzfqQHz){PIpHgsSgdO = true;}
      if(xldiqYKpnr == BLDSGqsPBc){CVSCgSlFzB = true;}
      else if(BLDSGqsPBc == xldiqYKpnr){lUaBSMPTzo = true;}
      if(tprruWCgbT == MumgRGgdyP){QpGiejqUFI = true;}
      if(ZmptBHogsJ == LspfkDEhEi){GxjqceGJHt = true;}
      if(sLrNkcBPQD == MjLdzFZdLo){HGjewCjQJs = true;}
      while(MumgRGgdyP == tprruWCgbT){tZKqRSwIzN = true;}
      while(LspfkDEhEi == LspfkDEhEi){jIatMpkEds = true;}
      while(MjLdzFZdLo == MjLdzFZdLo){WdhCwPReVs = true;}
      if(pHCLOleAPN == true){pHCLOleAPN = false;}
      if(VENYFIVXhC == true){VENYFIVXhC = false;}
      if(mKLRQciIhM == true){mKLRQciIhM = false;}
      if(gCSIZDqeRz == true){gCSIZDqeRz = false;}
      if(XDSpMHVlYq == true){XDSpMHVlYq = false;}
      if(jBwIBfwjtl == true){jBwIBfwjtl = false;}
      if(CVSCgSlFzB == true){CVSCgSlFzB = false;}
      if(QpGiejqUFI == true){QpGiejqUFI = false;}
      if(GxjqceGJHt == true){GxjqceGJHt = false;}
      if(HGjewCjQJs == true){HGjewCjQJs = false;}
      if(VQlXZsuNdR == true){VQlXZsuNdR = false;}
      if(naeleElbZB == true){naeleElbZB = false;}
      if(MbxFtKGalc == true){MbxFtKGalc = false;}
      if(zaLLmoKLRi == true){zaLLmoKLRi = false;}
      if(jsfoFfaxAr == true){jsfoFfaxAr = false;}
      if(PIpHgsSgdO == true){PIpHgsSgdO = false;}
      if(lUaBSMPTzo == true){lUaBSMPTzo = false;}
      if(tZKqRSwIzN == true){tZKqRSwIzN = false;}
      if(jIatMpkEds == true){jIatMpkEds = false;}
      if(WdhCwPReVs == true){WdhCwPReVs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LIAICAHMWR
{ 
  void MufGjGIQaQ()
  { 
      bool UdsNQGnwma = false;
      bool zrVrYGIgtw = false;
      bool JJiiDtRKkD = false;
      bool dUqJUJaKyr = false;
      bool IUYmpycxFp = false;
      bool BeiYQLtJKV = false;
      bool ocKixdBLWO = false;
      bool exhBnnjusF = false;
      bool QTFuCylRsJ = false;
      bool ORAbCeKppM = false;
      bool wRZpKEwgkb = false;
      bool ayQEFUWPgz = false;
      bool qiSNzNwFzI = false;
      bool ctFfIzsPjx = false;
      bool BEgQhQBwWg = false;
      bool HtIqUNyMpw = false;
      bool HqhbzfsjuF = false;
      bool bHeixmBCfi = false;
      bool MAiRBikOKu = false;
      bool BgZmpKWFQB = false;
      string BAKkdWaIDO;
      string BlyZpDMnYR;
      string lBtjTPiJNO;
      string AbomUhguKs;
      string KDXWoOprWx;
      string drzMDzGZQN;
      string mRuoNZxKEH;
      string VQdeGidWuE;
      string ZplQjHbbjV;
      string aGdwGsHiIO;
      string RemOaMOUGU;
      string VjeLnwedEG;
      string xUaigPlgYM;
      string auNfmtDXoW;
      string rHVOAqbRHJ;
      string NddBRxEEhL;
      string ahussaVyYt;
      string sHohOpyLio;
      string mTYOyxRMOo;
      string pzpdwKLcUZ;
      if(BAKkdWaIDO == RemOaMOUGU){UdsNQGnwma = true;}
      else if(RemOaMOUGU == BAKkdWaIDO){wRZpKEwgkb = true;}
      if(BlyZpDMnYR == VjeLnwedEG){zrVrYGIgtw = true;}
      else if(VjeLnwedEG == BlyZpDMnYR){ayQEFUWPgz = true;}
      if(lBtjTPiJNO == xUaigPlgYM){JJiiDtRKkD = true;}
      else if(xUaigPlgYM == lBtjTPiJNO){qiSNzNwFzI = true;}
      if(AbomUhguKs == auNfmtDXoW){dUqJUJaKyr = true;}
      else if(auNfmtDXoW == AbomUhguKs){ctFfIzsPjx = true;}
      if(KDXWoOprWx == rHVOAqbRHJ){IUYmpycxFp = true;}
      else if(rHVOAqbRHJ == KDXWoOprWx){BEgQhQBwWg = true;}
      if(drzMDzGZQN == NddBRxEEhL){BeiYQLtJKV = true;}
      else if(NddBRxEEhL == drzMDzGZQN){HtIqUNyMpw = true;}
      if(mRuoNZxKEH == ahussaVyYt){ocKixdBLWO = true;}
      else if(ahussaVyYt == mRuoNZxKEH){HqhbzfsjuF = true;}
      if(VQdeGidWuE == sHohOpyLio){exhBnnjusF = true;}
      if(ZplQjHbbjV == mTYOyxRMOo){QTFuCylRsJ = true;}
      if(aGdwGsHiIO == pzpdwKLcUZ){ORAbCeKppM = true;}
      while(sHohOpyLio == VQdeGidWuE){bHeixmBCfi = true;}
      while(mTYOyxRMOo == mTYOyxRMOo){MAiRBikOKu = true;}
      while(pzpdwKLcUZ == pzpdwKLcUZ){BgZmpKWFQB = true;}
      if(UdsNQGnwma == true){UdsNQGnwma = false;}
      if(zrVrYGIgtw == true){zrVrYGIgtw = false;}
      if(JJiiDtRKkD == true){JJiiDtRKkD = false;}
      if(dUqJUJaKyr == true){dUqJUJaKyr = false;}
      if(IUYmpycxFp == true){IUYmpycxFp = false;}
      if(BeiYQLtJKV == true){BeiYQLtJKV = false;}
      if(ocKixdBLWO == true){ocKixdBLWO = false;}
      if(exhBnnjusF == true){exhBnnjusF = false;}
      if(QTFuCylRsJ == true){QTFuCylRsJ = false;}
      if(ORAbCeKppM == true){ORAbCeKppM = false;}
      if(wRZpKEwgkb == true){wRZpKEwgkb = false;}
      if(ayQEFUWPgz == true){ayQEFUWPgz = false;}
      if(qiSNzNwFzI == true){qiSNzNwFzI = false;}
      if(ctFfIzsPjx == true){ctFfIzsPjx = false;}
      if(BEgQhQBwWg == true){BEgQhQBwWg = false;}
      if(HtIqUNyMpw == true){HtIqUNyMpw = false;}
      if(HqhbzfsjuF == true){HqhbzfsjuF = false;}
      if(bHeixmBCfi == true){bHeixmBCfi = false;}
      if(MAiRBikOKu == true){MAiRBikOKu = false;}
      if(BgZmpKWFQB == true){BgZmpKWFQB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOMBVEORZA
{ 
  void mujHFmzXVQ()
  { 
      bool MuesOrXIQH = false;
      bool NmjZujRqMQ = false;
      bool uYLrhAAzoZ = false;
      bool eDpXmzHLFE = false;
      bool aoKHnlTTXN = false;
      bool WOTeQmilLN = false;
      bool qXTpbKxMlu = false;
      bool cGlHpGOEDu = false;
      bool ffbbDQjKHA = false;
      bool QUAqNDUTfd = false;
      bool oHgcjPcLoJ = false;
      bool YdhQgKwrmK = false;
      bool alFldIGttm = false;
      bool ktYZFYzyqm = false;
      bool nYVxalljKC = false;
      bool GcgUDDCuzb = false;
      bool JiQCYeFIKH = false;
      bool LyAzWBQHKq = false;
      bool VWirfHMDVC = false;
      bool VEzOdFHSYw = false;
      string DIuVAkHncD;
      string MUDPcKTHtK;
      string YPlLDSYitR;
      string lxMjgrnmqJ;
      string ZNQXJfrqYc;
      string OuicQnVjRh;
      string LYtLRPIShj;
      string VgQkjKzNBW;
      string ZgJQCpNiSs;
      string VEUJxBTEGt;
      string WZIoHhexrG;
      string nIhuHdOcIa;
      string BZzoNQLGmi;
      string ptHHAAYUJU;
      string LQpMFNVZBT;
      string lqwfrxZTap;
      string WXKJPsBauH;
      string FtTmOkjmjA;
      string ulFTwyxbOC;
      string ZEtTynFfwL;
      if(DIuVAkHncD == WZIoHhexrG){MuesOrXIQH = true;}
      else if(WZIoHhexrG == DIuVAkHncD){oHgcjPcLoJ = true;}
      if(MUDPcKTHtK == nIhuHdOcIa){NmjZujRqMQ = true;}
      else if(nIhuHdOcIa == MUDPcKTHtK){YdhQgKwrmK = true;}
      if(YPlLDSYitR == BZzoNQLGmi){uYLrhAAzoZ = true;}
      else if(BZzoNQLGmi == YPlLDSYitR){alFldIGttm = true;}
      if(lxMjgrnmqJ == ptHHAAYUJU){eDpXmzHLFE = true;}
      else if(ptHHAAYUJU == lxMjgrnmqJ){ktYZFYzyqm = true;}
      if(ZNQXJfrqYc == LQpMFNVZBT){aoKHnlTTXN = true;}
      else if(LQpMFNVZBT == ZNQXJfrqYc){nYVxalljKC = true;}
      if(OuicQnVjRh == lqwfrxZTap){WOTeQmilLN = true;}
      else if(lqwfrxZTap == OuicQnVjRh){GcgUDDCuzb = true;}
      if(LYtLRPIShj == WXKJPsBauH){qXTpbKxMlu = true;}
      else if(WXKJPsBauH == LYtLRPIShj){JiQCYeFIKH = true;}
      if(VgQkjKzNBW == FtTmOkjmjA){cGlHpGOEDu = true;}
      if(ZgJQCpNiSs == ulFTwyxbOC){ffbbDQjKHA = true;}
      if(VEUJxBTEGt == ZEtTynFfwL){QUAqNDUTfd = true;}
      while(FtTmOkjmjA == VgQkjKzNBW){LyAzWBQHKq = true;}
      while(ulFTwyxbOC == ulFTwyxbOC){VWirfHMDVC = true;}
      while(ZEtTynFfwL == ZEtTynFfwL){VEzOdFHSYw = true;}
      if(MuesOrXIQH == true){MuesOrXIQH = false;}
      if(NmjZujRqMQ == true){NmjZujRqMQ = false;}
      if(uYLrhAAzoZ == true){uYLrhAAzoZ = false;}
      if(eDpXmzHLFE == true){eDpXmzHLFE = false;}
      if(aoKHnlTTXN == true){aoKHnlTTXN = false;}
      if(WOTeQmilLN == true){WOTeQmilLN = false;}
      if(qXTpbKxMlu == true){qXTpbKxMlu = false;}
      if(cGlHpGOEDu == true){cGlHpGOEDu = false;}
      if(ffbbDQjKHA == true){ffbbDQjKHA = false;}
      if(QUAqNDUTfd == true){QUAqNDUTfd = false;}
      if(oHgcjPcLoJ == true){oHgcjPcLoJ = false;}
      if(YdhQgKwrmK == true){YdhQgKwrmK = false;}
      if(alFldIGttm == true){alFldIGttm = false;}
      if(ktYZFYzyqm == true){ktYZFYzyqm = false;}
      if(nYVxalljKC == true){nYVxalljKC = false;}
      if(GcgUDDCuzb == true){GcgUDDCuzb = false;}
      if(JiQCYeFIKH == true){JiQCYeFIKH = false;}
      if(LyAzWBQHKq == true){LyAzWBQHKq = false;}
      if(VWirfHMDVC == true){VWirfHMDVC = false;}
      if(VEzOdFHSYw == true){VEzOdFHSYw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEVZJIJKPL
{ 
  void MUZnqnFZkh()
  { 
      bool dNKVdTOSWX = false;
      bool KgOGWCsZSW = false;
      bool ChFIBOlccD = false;
      bool FRXtlMwiRa = false;
      bool THUcNZIxic = false;
      bool QeOoCwHBTP = false;
      bool gloTRsITUJ = false;
      bool FJHqCtMbub = false;
      bool FnsAmaDirp = false;
      bool EuOCsgSBKU = false;
      bool QocYWGWWlI = false;
      bool ieGrJsrnfq = false;
      bool oZbeEKtEyU = false;
      bool bLRZLPLUdf = false;
      bool DfwjGZnWrA = false;
      bool odUTeqNyTM = false;
      bool MRXRfXNfgt = false;
      bool gXKAmIdrXe = false;
      bool VXLyfxpyuT = false;
      bool CNAQTlHeDh = false;
      string CjLFnTUWMg;
      string iUMNRGXeju;
      string huzSAPSjpQ;
      string UnNGTqCOil;
      string NQUQPLYnRu;
      string RdeACGjsFX;
      string AkguLuHFta;
      string DIuxhQahDn;
      string qeStypIMDM;
      string GJJLkcjYFT;
      string EStqqJihSl;
      string eCoQgVRlxU;
      string ltBgTtzjLF;
      string gCbiiXjaDo;
      string HatRhDTreP;
      string KxajhKRNWx;
      string JyVNFcZGhI;
      string kpiIMKzjzP;
      string ZHFwtiarAY;
      string GWEFeJEgLE;
      if(CjLFnTUWMg == EStqqJihSl){dNKVdTOSWX = true;}
      else if(EStqqJihSl == CjLFnTUWMg){QocYWGWWlI = true;}
      if(iUMNRGXeju == eCoQgVRlxU){KgOGWCsZSW = true;}
      else if(eCoQgVRlxU == iUMNRGXeju){ieGrJsrnfq = true;}
      if(huzSAPSjpQ == ltBgTtzjLF){ChFIBOlccD = true;}
      else if(ltBgTtzjLF == huzSAPSjpQ){oZbeEKtEyU = true;}
      if(UnNGTqCOil == gCbiiXjaDo){FRXtlMwiRa = true;}
      else if(gCbiiXjaDo == UnNGTqCOil){bLRZLPLUdf = true;}
      if(NQUQPLYnRu == HatRhDTreP){THUcNZIxic = true;}
      else if(HatRhDTreP == NQUQPLYnRu){DfwjGZnWrA = true;}
      if(RdeACGjsFX == KxajhKRNWx){QeOoCwHBTP = true;}
      else if(KxajhKRNWx == RdeACGjsFX){odUTeqNyTM = true;}
      if(AkguLuHFta == JyVNFcZGhI){gloTRsITUJ = true;}
      else if(JyVNFcZGhI == AkguLuHFta){MRXRfXNfgt = true;}
      if(DIuxhQahDn == kpiIMKzjzP){FJHqCtMbub = true;}
      if(qeStypIMDM == ZHFwtiarAY){FnsAmaDirp = true;}
      if(GJJLkcjYFT == GWEFeJEgLE){EuOCsgSBKU = true;}
      while(kpiIMKzjzP == DIuxhQahDn){gXKAmIdrXe = true;}
      while(ZHFwtiarAY == ZHFwtiarAY){VXLyfxpyuT = true;}
      while(GWEFeJEgLE == GWEFeJEgLE){CNAQTlHeDh = true;}
      if(dNKVdTOSWX == true){dNKVdTOSWX = false;}
      if(KgOGWCsZSW == true){KgOGWCsZSW = false;}
      if(ChFIBOlccD == true){ChFIBOlccD = false;}
      if(FRXtlMwiRa == true){FRXtlMwiRa = false;}
      if(THUcNZIxic == true){THUcNZIxic = false;}
      if(QeOoCwHBTP == true){QeOoCwHBTP = false;}
      if(gloTRsITUJ == true){gloTRsITUJ = false;}
      if(FJHqCtMbub == true){FJHqCtMbub = false;}
      if(FnsAmaDirp == true){FnsAmaDirp = false;}
      if(EuOCsgSBKU == true){EuOCsgSBKU = false;}
      if(QocYWGWWlI == true){QocYWGWWlI = false;}
      if(ieGrJsrnfq == true){ieGrJsrnfq = false;}
      if(oZbeEKtEyU == true){oZbeEKtEyU = false;}
      if(bLRZLPLUdf == true){bLRZLPLUdf = false;}
      if(DfwjGZnWrA == true){DfwjGZnWrA = false;}
      if(odUTeqNyTM == true){odUTeqNyTM = false;}
      if(MRXRfXNfgt == true){MRXRfXNfgt = false;}
      if(gXKAmIdrXe == true){gXKAmIdrXe = false;}
      if(VXLyfxpyuT == true){VXLyfxpyuT = false;}
      if(CNAQTlHeDh == true){CNAQTlHeDh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JAOHKNBIKV
{ 
  void yDXGtYhxSf()
  { 
      bool YXwtSgzGIT = false;
      bool TWBYtpHVKE = false;
      bool BYAUedMeHL = false;
      bool EUwLjamBVK = false;
      bool YHkOdyDBlH = false;
      bool SCmXnAXbPn = false;
      bool UTzwPzapoS = false;
      bool DGAzfsnkqg = false;
      bool ZKszsBhYWi = false;
      bool DKkgoEHnye = false;
      bool XNLSDMCmru = false;
      bool MljiOJaACN = false;
      bool QCSFOrUSKa = false;
      bool kzmLJLyZug = false;
      bool ztfbWRZCRe = false;
      bool cHljNUtGEL = false;
      bool qicQJMyYZC = false;
      bool KBEUOVVqhx = false;
      bool RRBexcNCyn = false;
      bool QrUjoPROSJ = false;
      string aInWVBUwIQ;
      string KmrJHrffqk;
      string bVBnbKneql;
      string aRGADGTNZG;
      string HzIBAlRSkU;
      string qBirlEGAtL;
      string MpFVpsgrGA;
      string XSFjcbNzmp;
      string rUsVuYhOOy;
      string zTTOtQtlLH;
      string FZLjxXuzOJ;
      string qHNDSrwjaQ;
      string KSdIBEzqpM;
      string hanekRIJYW;
      string dhzEGrFPuB;
      string UKLuwmwDir;
      string YDJCbQShSA;
      string imKElcSYBJ;
      string yiwnrXOshy;
      string VFafxZXxbp;
      if(aInWVBUwIQ == FZLjxXuzOJ){YXwtSgzGIT = true;}
      else if(FZLjxXuzOJ == aInWVBUwIQ){XNLSDMCmru = true;}
      if(KmrJHrffqk == qHNDSrwjaQ){TWBYtpHVKE = true;}
      else if(qHNDSrwjaQ == KmrJHrffqk){MljiOJaACN = true;}
      if(bVBnbKneql == KSdIBEzqpM){BYAUedMeHL = true;}
      else if(KSdIBEzqpM == bVBnbKneql){QCSFOrUSKa = true;}
      if(aRGADGTNZG == hanekRIJYW){EUwLjamBVK = true;}
      else if(hanekRIJYW == aRGADGTNZG){kzmLJLyZug = true;}
      if(HzIBAlRSkU == dhzEGrFPuB){YHkOdyDBlH = true;}
      else if(dhzEGrFPuB == HzIBAlRSkU){ztfbWRZCRe = true;}
      if(qBirlEGAtL == UKLuwmwDir){SCmXnAXbPn = true;}
      else if(UKLuwmwDir == qBirlEGAtL){cHljNUtGEL = true;}
      if(MpFVpsgrGA == YDJCbQShSA){UTzwPzapoS = true;}
      else if(YDJCbQShSA == MpFVpsgrGA){qicQJMyYZC = true;}
      if(XSFjcbNzmp == imKElcSYBJ){DGAzfsnkqg = true;}
      if(rUsVuYhOOy == yiwnrXOshy){ZKszsBhYWi = true;}
      if(zTTOtQtlLH == VFafxZXxbp){DKkgoEHnye = true;}
      while(imKElcSYBJ == XSFjcbNzmp){KBEUOVVqhx = true;}
      while(yiwnrXOshy == yiwnrXOshy){RRBexcNCyn = true;}
      while(VFafxZXxbp == VFafxZXxbp){QrUjoPROSJ = true;}
      if(YXwtSgzGIT == true){YXwtSgzGIT = false;}
      if(TWBYtpHVKE == true){TWBYtpHVKE = false;}
      if(BYAUedMeHL == true){BYAUedMeHL = false;}
      if(EUwLjamBVK == true){EUwLjamBVK = false;}
      if(YHkOdyDBlH == true){YHkOdyDBlH = false;}
      if(SCmXnAXbPn == true){SCmXnAXbPn = false;}
      if(UTzwPzapoS == true){UTzwPzapoS = false;}
      if(DGAzfsnkqg == true){DGAzfsnkqg = false;}
      if(ZKszsBhYWi == true){ZKszsBhYWi = false;}
      if(DKkgoEHnye == true){DKkgoEHnye = false;}
      if(XNLSDMCmru == true){XNLSDMCmru = false;}
      if(MljiOJaACN == true){MljiOJaACN = false;}
      if(QCSFOrUSKa == true){QCSFOrUSKa = false;}
      if(kzmLJLyZug == true){kzmLJLyZug = false;}
      if(ztfbWRZCRe == true){ztfbWRZCRe = false;}
      if(cHljNUtGEL == true){cHljNUtGEL = false;}
      if(qicQJMyYZC == true){qicQJMyYZC = false;}
      if(KBEUOVVqhx == true){KBEUOVVqhx = false;}
      if(RRBexcNCyn == true){RRBexcNCyn = false;}
      if(QrUjoPROSJ == true){QrUjoPROSJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFPQCRTTVA
{ 
  void HtfZieUjRM()
  { 
      bool lANKkMDAXS = false;
      bool rVOBUYmnBN = false;
      bool ZeJSOOSZMs = false;
      bool iZNQGxAxKF = false;
      bool lYBOHhBqQV = false;
      bool LAGqEGptwV = false;
      bool sdmeiRIxtW = false;
      bool XpduaBduLg = false;
      bool NaIqhiTWMA = false;
      bool HFBnLIkWeo = false;
      bool YEwsxVVKPC = false;
      bool cuiOISUuxA = false;
      bool yljtPSnpjS = false;
      bool PHPWHJdOtL = false;
      bool MJGJWMWlfs = false;
      bool noYdplTCde = false;
      bool geawmVeLHy = false;
      bool nFBkmoeZWD = false;
      bool uCKpeahlfU = false;
      bool obkPehhJWB = false;
      string izodfmkFPE;
      string LzGAueqjNE;
      string EZLPeNZSWN;
      string ntHORZgXHh;
      string pQxSEYGQAG;
      string AKaXxImZzS;
      string NRhBQQqrhV;
      string xSbfOncsKG;
      string GISPNcTjRJ;
      string lGYoUXhuCm;
      string gOieJghuJJ;
      string ftOrLEzSnm;
      string wHZYjptlKp;
      string FgpXZrZmFg;
      string tYZIcqqfdP;
      string XPHPpZnJtT;
      string lwjSDzEqSS;
      string eLMHrXgRus;
      string yNIuRpYZgz;
      string EPsltyoHEd;
      if(izodfmkFPE == gOieJghuJJ){lANKkMDAXS = true;}
      else if(gOieJghuJJ == izodfmkFPE){YEwsxVVKPC = true;}
      if(LzGAueqjNE == ftOrLEzSnm){rVOBUYmnBN = true;}
      else if(ftOrLEzSnm == LzGAueqjNE){cuiOISUuxA = true;}
      if(EZLPeNZSWN == wHZYjptlKp){ZeJSOOSZMs = true;}
      else if(wHZYjptlKp == EZLPeNZSWN){yljtPSnpjS = true;}
      if(ntHORZgXHh == FgpXZrZmFg){iZNQGxAxKF = true;}
      else if(FgpXZrZmFg == ntHORZgXHh){PHPWHJdOtL = true;}
      if(pQxSEYGQAG == tYZIcqqfdP){lYBOHhBqQV = true;}
      else if(tYZIcqqfdP == pQxSEYGQAG){MJGJWMWlfs = true;}
      if(AKaXxImZzS == XPHPpZnJtT){LAGqEGptwV = true;}
      else if(XPHPpZnJtT == AKaXxImZzS){noYdplTCde = true;}
      if(NRhBQQqrhV == lwjSDzEqSS){sdmeiRIxtW = true;}
      else if(lwjSDzEqSS == NRhBQQqrhV){geawmVeLHy = true;}
      if(xSbfOncsKG == eLMHrXgRus){XpduaBduLg = true;}
      if(GISPNcTjRJ == yNIuRpYZgz){NaIqhiTWMA = true;}
      if(lGYoUXhuCm == EPsltyoHEd){HFBnLIkWeo = true;}
      while(eLMHrXgRus == xSbfOncsKG){nFBkmoeZWD = true;}
      while(yNIuRpYZgz == yNIuRpYZgz){uCKpeahlfU = true;}
      while(EPsltyoHEd == EPsltyoHEd){obkPehhJWB = true;}
      if(lANKkMDAXS == true){lANKkMDAXS = false;}
      if(rVOBUYmnBN == true){rVOBUYmnBN = false;}
      if(ZeJSOOSZMs == true){ZeJSOOSZMs = false;}
      if(iZNQGxAxKF == true){iZNQGxAxKF = false;}
      if(lYBOHhBqQV == true){lYBOHhBqQV = false;}
      if(LAGqEGptwV == true){LAGqEGptwV = false;}
      if(sdmeiRIxtW == true){sdmeiRIxtW = false;}
      if(XpduaBduLg == true){XpduaBduLg = false;}
      if(NaIqhiTWMA == true){NaIqhiTWMA = false;}
      if(HFBnLIkWeo == true){HFBnLIkWeo = false;}
      if(YEwsxVVKPC == true){YEwsxVVKPC = false;}
      if(cuiOISUuxA == true){cuiOISUuxA = false;}
      if(yljtPSnpjS == true){yljtPSnpjS = false;}
      if(PHPWHJdOtL == true){PHPWHJdOtL = false;}
      if(MJGJWMWlfs == true){MJGJWMWlfs = false;}
      if(noYdplTCde == true){noYdplTCde = false;}
      if(geawmVeLHy == true){geawmVeLHy = false;}
      if(nFBkmoeZWD == true){nFBkmoeZWD = false;}
      if(uCKpeahlfU == true){uCKpeahlfU = false;}
      if(obkPehhJWB == true){obkPehhJWB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JVQAIRCAXI
{ 
  void VKiQKIVAiE()
  { 
      bool auCRPyUmRN = false;
      bool hyuUYPnoFU = false;
      bool kOHCRdpiMe = false;
      bool iMkcNEYxei = false;
      bool IDjTOuSeWZ = false;
      bool NzkbFLmAzl = false;
      bool IkZmeVMSHT = false;
      bool ppKVLgenmW = false;
      bool KKMlRjaJXB = false;
      bool RXysaWcxos = false;
      bool hAXCiWnOPX = false;
      bool gzNcayYnUu = false;
      bool tDuFCRqRuo = false;
      bool EhysnJlKDt = false;
      bool uLtzUSKURb = false;
      bool yobtzeFSAR = false;
      bool eVTZTyAToQ = false;
      bool LNkazhIuji = false;
      bool GWASqOGEtI = false;
      bool ETKkOYrTfW = false;
      string MILdJpZwPA;
      string yoQnulcBRz;
      string EFIyulnaSg;
      string MmPVeIGRoh;
      string mcEXusDJbn;
      string fJYXBGAMiW;
      string BydhnLZuJm;
      string eLLjMbAjDB;
      string ieydACNqTX;
      string HtiRfnzVji;
      string THAoJTxnLZ;
      string FQJgnWzzhk;
      string xhakfjctDX;
      string cezThadJUf;
      string FZesRqjBdI;
      string oznylkgOJY;
      string qDjnxaQozM;
      string speBfXDhTn;
      string zbPthcpBhw;
      string tOAuoBoqwp;
      if(MILdJpZwPA == THAoJTxnLZ){auCRPyUmRN = true;}
      else if(THAoJTxnLZ == MILdJpZwPA){hAXCiWnOPX = true;}
      if(yoQnulcBRz == FQJgnWzzhk){hyuUYPnoFU = true;}
      else if(FQJgnWzzhk == yoQnulcBRz){gzNcayYnUu = true;}
      if(EFIyulnaSg == xhakfjctDX){kOHCRdpiMe = true;}
      else if(xhakfjctDX == EFIyulnaSg){tDuFCRqRuo = true;}
      if(MmPVeIGRoh == cezThadJUf){iMkcNEYxei = true;}
      else if(cezThadJUf == MmPVeIGRoh){EhysnJlKDt = true;}
      if(mcEXusDJbn == FZesRqjBdI){IDjTOuSeWZ = true;}
      else if(FZesRqjBdI == mcEXusDJbn){uLtzUSKURb = true;}
      if(fJYXBGAMiW == oznylkgOJY){NzkbFLmAzl = true;}
      else if(oznylkgOJY == fJYXBGAMiW){yobtzeFSAR = true;}
      if(BydhnLZuJm == qDjnxaQozM){IkZmeVMSHT = true;}
      else if(qDjnxaQozM == BydhnLZuJm){eVTZTyAToQ = true;}
      if(eLLjMbAjDB == speBfXDhTn){ppKVLgenmW = true;}
      if(ieydACNqTX == zbPthcpBhw){KKMlRjaJXB = true;}
      if(HtiRfnzVji == tOAuoBoqwp){RXysaWcxos = true;}
      while(speBfXDhTn == eLLjMbAjDB){LNkazhIuji = true;}
      while(zbPthcpBhw == zbPthcpBhw){GWASqOGEtI = true;}
      while(tOAuoBoqwp == tOAuoBoqwp){ETKkOYrTfW = true;}
      if(auCRPyUmRN == true){auCRPyUmRN = false;}
      if(hyuUYPnoFU == true){hyuUYPnoFU = false;}
      if(kOHCRdpiMe == true){kOHCRdpiMe = false;}
      if(iMkcNEYxei == true){iMkcNEYxei = false;}
      if(IDjTOuSeWZ == true){IDjTOuSeWZ = false;}
      if(NzkbFLmAzl == true){NzkbFLmAzl = false;}
      if(IkZmeVMSHT == true){IkZmeVMSHT = false;}
      if(ppKVLgenmW == true){ppKVLgenmW = false;}
      if(KKMlRjaJXB == true){KKMlRjaJXB = false;}
      if(RXysaWcxos == true){RXysaWcxos = false;}
      if(hAXCiWnOPX == true){hAXCiWnOPX = false;}
      if(gzNcayYnUu == true){gzNcayYnUu = false;}
      if(tDuFCRqRuo == true){tDuFCRqRuo = false;}
      if(EhysnJlKDt == true){EhysnJlKDt = false;}
      if(uLtzUSKURb == true){uLtzUSKURb = false;}
      if(yobtzeFSAR == true){yobtzeFSAR = false;}
      if(eVTZTyAToQ == true){eVTZTyAToQ = false;}
      if(LNkazhIuji == true){LNkazhIuji = false;}
      if(GWASqOGEtI == true){GWASqOGEtI = false;}
      if(ETKkOYrTfW == true){ETKkOYrTfW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWYCZQFLVY
{ 
  void gHauLsMZNp()
  { 
      bool XICdprJsgm = false;
      bool QBeHndNlZg = false;
      bool uMbVhKzUmI = false;
      bool AZrNhfiLXB = false;
      bool IDezaISLUV = false;
      bool dPZNKLffwf = false;
      bool rnFXlqJQYH = false;
      bool tCNXYqgcuZ = false;
      bool qmARejzeCW = false;
      bool ADOqIUxHMi = false;
      bool zBlMbbCBoT = false;
      bool dDjWnFmnsC = false;
      bool qdOCHqmVPE = false;
      bool sZPLZoAmpD = false;
      bool hxpiswSrDD = false;
      bool gJNKqUmjFj = false;
      bool nfljZDmYwy = false;
      bool EzypTtnfIK = false;
      bool YtSLWjMFTF = false;
      bool CQhFOCKFIo = false;
      string KMEKoksgqT;
      string TUprjEqKqg;
      string BbQosZSpqJ;
      string IyhKENdcfX;
      string PsPpQYCEoP;
      string euhoLiuOQP;
      string SCpgKVmfnV;
      string aNdSQHMaXU;
      string WNBaeNQryU;
      string ROMQFMChfu;
      string lWQSoQROXE;
      string WUqwsFBPBx;
      string FtgSEMBNNE;
      string EduciAwhkO;
      string wCTtyxWPXz;
      string KmghpqoyOc;
      string ODATzrZONs;
      string ISdmBCZmTG;
      string okpOsRxMlq;
      string KyTIzrCAtG;
      if(KMEKoksgqT == lWQSoQROXE){XICdprJsgm = true;}
      else if(lWQSoQROXE == KMEKoksgqT){zBlMbbCBoT = true;}
      if(TUprjEqKqg == WUqwsFBPBx){QBeHndNlZg = true;}
      else if(WUqwsFBPBx == TUprjEqKqg){dDjWnFmnsC = true;}
      if(BbQosZSpqJ == FtgSEMBNNE){uMbVhKzUmI = true;}
      else if(FtgSEMBNNE == BbQosZSpqJ){qdOCHqmVPE = true;}
      if(IyhKENdcfX == EduciAwhkO){AZrNhfiLXB = true;}
      else if(EduciAwhkO == IyhKENdcfX){sZPLZoAmpD = true;}
      if(PsPpQYCEoP == wCTtyxWPXz){IDezaISLUV = true;}
      else if(wCTtyxWPXz == PsPpQYCEoP){hxpiswSrDD = true;}
      if(euhoLiuOQP == KmghpqoyOc){dPZNKLffwf = true;}
      else if(KmghpqoyOc == euhoLiuOQP){gJNKqUmjFj = true;}
      if(SCpgKVmfnV == ODATzrZONs){rnFXlqJQYH = true;}
      else if(ODATzrZONs == SCpgKVmfnV){nfljZDmYwy = true;}
      if(aNdSQHMaXU == ISdmBCZmTG){tCNXYqgcuZ = true;}
      if(WNBaeNQryU == okpOsRxMlq){qmARejzeCW = true;}
      if(ROMQFMChfu == KyTIzrCAtG){ADOqIUxHMi = true;}
      while(ISdmBCZmTG == aNdSQHMaXU){EzypTtnfIK = true;}
      while(okpOsRxMlq == okpOsRxMlq){YtSLWjMFTF = true;}
      while(KyTIzrCAtG == KyTIzrCAtG){CQhFOCKFIo = true;}
      if(XICdprJsgm == true){XICdprJsgm = false;}
      if(QBeHndNlZg == true){QBeHndNlZg = false;}
      if(uMbVhKzUmI == true){uMbVhKzUmI = false;}
      if(AZrNhfiLXB == true){AZrNhfiLXB = false;}
      if(IDezaISLUV == true){IDezaISLUV = false;}
      if(dPZNKLffwf == true){dPZNKLffwf = false;}
      if(rnFXlqJQYH == true){rnFXlqJQYH = false;}
      if(tCNXYqgcuZ == true){tCNXYqgcuZ = false;}
      if(qmARejzeCW == true){qmARejzeCW = false;}
      if(ADOqIUxHMi == true){ADOqIUxHMi = false;}
      if(zBlMbbCBoT == true){zBlMbbCBoT = false;}
      if(dDjWnFmnsC == true){dDjWnFmnsC = false;}
      if(qdOCHqmVPE == true){qdOCHqmVPE = false;}
      if(sZPLZoAmpD == true){sZPLZoAmpD = false;}
      if(hxpiswSrDD == true){hxpiswSrDD = false;}
      if(gJNKqUmjFj == true){gJNKqUmjFj = false;}
      if(nfljZDmYwy == true){nfljZDmYwy = false;}
      if(EzypTtnfIK == true){EzypTtnfIK = false;}
      if(YtSLWjMFTF == true){YtSLWjMFTF = false;}
      if(CQhFOCKFIo == true){CQhFOCKFIo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWLUMNIMMG
{ 
  void oiwJreVPhO()
  { 
      bool YBilCMfzCP = false;
      bool FmyfZkdhpx = false;
      bool GVjIkPLCJq = false;
      bool tHhZfVGXtb = false;
      bool MGNXPbcIPU = false;
      bool VOYbMDRZAl = false;
      bool BdoLVxEXzE = false;
      bool eFnNjzHLsI = false;
      bool lCloUeiGNc = false;
      bool EfXHaiRBCS = false;
      bool XEILpQaLqM = false;
      bool uFfrzyqApp = false;
      bool NyKWAyhflA = false;
      bool hGJakhtayE = false;
      bool EXOAgyzeHc = false;
      bool rRLLEZtkLq = false;
      bool htYpeouFHR = false;
      bool DQBklpjKoB = false;
      bool zCXJIPuyVL = false;
      bool nIOHWJyXVr = false;
      string VrwuflHniC;
      string ciGSKYxZwe;
      string wELIbtpDWb;
      string zNrIemgHhB;
      string qWUbnjQEZm;
      string SbQThRfmSl;
      string wEQHCOpymX;
      string qprunYijTq;
      string ckcjJXwYZN;
      string HsnuEmGNYY;
      string tSRCubjUeJ;
      string hwSaJKagxe;
      string SRXYQxBwpA;
      string SVKuxJTang;
      string nbtQfKZMls;
      string MYPtGctrlx;
      string ZneeqMlXdA;
      string qAsQqqWHsF;
      string XoJwnsFQnU;
      string ObnpGzwOZT;
      if(VrwuflHniC == tSRCubjUeJ){YBilCMfzCP = true;}
      else if(tSRCubjUeJ == VrwuflHniC){XEILpQaLqM = true;}
      if(ciGSKYxZwe == hwSaJKagxe){FmyfZkdhpx = true;}
      else if(hwSaJKagxe == ciGSKYxZwe){uFfrzyqApp = true;}
      if(wELIbtpDWb == SRXYQxBwpA){GVjIkPLCJq = true;}
      else if(SRXYQxBwpA == wELIbtpDWb){NyKWAyhflA = true;}
      if(zNrIemgHhB == SVKuxJTang){tHhZfVGXtb = true;}
      else if(SVKuxJTang == zNrIemgHhB){hGJakhtayE = true;}
      if(qWUbnjQEZm == nbtQfKZMls){MGNXPbcIPU = true;}
      else if(nbtQfKZMls == qWUbnjQEZm){EXOAgyzeHc = true;}
      if(SbQThRfmSl == MYPtGctrlx){VOYbMDRZAl = true;}
      else if(MYPtGctrlx == SbQThRfmSl){rRLLEZtkLq = true;}
      if(wEQHCOpymX == ZneeqMlXdA){BdoLVxEXzE = true;}
      else if(ZneeqMlXdA == wEQHCOpymX){htYpeouFHR = true;}
      if(qprunYijTq == qAsQqqWHsF){eFnNjzHLsI = true;}
      if(ckcjJXwYZN == XoJwnsFQnU){lCloUeiGNc = true;}
      if(HsnuEmGNYY == ObnpGzwOZT){EfXHaiRBCS = true;}
      while(qAsQqqWHsF == qprunYijTq){DQBklpjKoB = true;}
      while(XoJwnsFQnU == XoJwnsFQnU){zCXJIPuyVL = true;}
      while(ObnpGzwOZT == ObnpGzwOZT){nIOHWJyXVr = true;}
      if(YBilCMfzCP == true){YBilCMfzCP = false;}
      if(FmyfZkdhpx == true){FmyfZkdhpx = false;}
      if(GVjIkPLCJq == true){GVjIkPLCJq = false;}
      if(tHhZfVGXtb == true){tHhZfVGXtb = false;}
      if(MGNXPbcIPU == true){MGNXPbcIPU = false;}
      if(VOYbMDRZAl == true){VOYbMDRZAl = false;}
      if(BdoLVxEXzE == true){BdoLVxEXzE = false;}
      if(eFnNjzHLsI == true){eFnNjzHLsI = false;}
      if(lCloUeiGNc == true){lCloUeiGNc = false;}
      if(EfXHaiRBCS == true){EfXHaiRBCS = false;}
      if(XEILpQaLqM == true){XEILpQaLqM = false;}
      if(uFfrzyqApp == true){uFfrzyqApp = false;}
      if(NyKWAyhflA == true){NyKWAyhflA = false;}
      if(hGJakhtayE == true){hGJakhtayE = false;}
      if(EXOAgyzeHc == true){EXOAgyzeHc = false;}
      if(rRLLEZtkLq == true){rRLLEZtkLq = false;}
      if(htYpeouFHR == true){htYpeouFHR = false;}
      if(DQBklpjKoB == true){DQBklpjKoB = false;}
      if(zCXJIPuyVL == true){zCXJIPuyVL = false;}
      if(nIOHWJyXVr == true){nIOHWJyXVr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GKJTKDGKQY
{ 
  void wLzuVrwzza()
  { 
      bool DAVqLUpCsP = false;
      bool mfUQjpLMxx = false;
      bool oMbHUxxRJw = false;
      bool bzDFWQVhOl = false;
      bool XnDbqikVqL = false;
      bool cpjWkpXOWN = false;
      bool XYswmncPtS = false;
      bool UcxKZAIAPk = false;
      bool LaayTlPfTf = false;
      bool sGLAOzuHnD = false;
      bool GVbXpArYxk = false;
      bool gWzkBwxucA = false;
      bool XwwNZNQxwZ = false;
      bool FBMLepzDHT = false;
      bool spiizWHZyR = false;
      bool CAenfJYNyb = false;
      bool iucWffJmGL = false;
      bool xtmJHhNMOC = false;
      bool GqydXEWYfU = false;
      bool RkEfjyMLDS = false;
      string ffJhHSCpHK;
      string AkzUknTrBg;
      string oheDFcLbHu;
      string jNKEpzeXJi;
      string wlUOCPCQRt;
      string dVuDMyAFbd;
      string GahLZmaudl;
      string IuhRjCNPAo;
      string atKNROSGqr;
      string yYufbVEIoP;
      string oHmekhncTK;
      string kkFmDLPUtL;
      string UTDlnjACpN;
      string yEakASHebi;
      string ZomfGNTIbP;
      string GiNdtUDAqA;
      string hllFMfJTlj;
      string EksKkegWfZ;
      string QqZZHOqwqe;
      string PGmaBnCgTZ;
      if(ffJhHSCpHK == oHmekhncTK){DAVqLUpCsP = true;}
      else if(oHmekhncTK == ffJhHSCpHK){GVbXpArYxk = true;}
      if(AkzUknTrBg == kkFmDLPUtL){mfUQjpLMxx = true;}
      else if(kkFmDLPUtL == AkzUknTrBg){gWzkBwxucA = true;}
      if(oheDFcLbHu == UTDlnjACpN){oMbHUxxRJw = true;}
      else if(UTDlnjACpN == oheDFcLbHu){XwwNZNQxwZ = true;}
      if(jNKEpzeXJi == yEakASHebi){bzDFWQVhOl = true;}
      else if(yEakASHebi == jNKEpzeXJi){FBMLepzDHT = true;}
      if(wlUOCPCQRt == ZomfGNTIbP){XnDbqikVqL = true;}
      else if(ZomfGNTIbP == wlUOCPCQRt){spiizWHZyR = true;}
      if(dVuDMyAFbd == GiNdtUDAqA){cpjWkpXOWN = true;}
      else if(GiNdtUDAqA == dVuDMyAFbd){CAenfJYNyb = true;}
      if(GahLZmaudl == hllFMfJTlj){XYswmncPtS = true;}
      else if(hllFMfJTlj == GahLZmaudl){iucWffJmGL = true;}
      if(IuhRjCNPAo == EksKkegWfZ){UcxKZAIAPk = true;}
      if(atKNROSGqr == QqZZHOqwqe){LaayTlPfTf = true;}
      if(yYufbVEIoP == PGmaBnCgTZ){sGLAOzuHnD = true;}
      while(EksKkegWfZ == IuhRjCNPAo){xtmJHhNMOC = true;}
      while(QqZZHOqwqe == QqZZHOqwqe){GqydXEWYfU = true;}
      while(PGmaBnCgTZ == PGmaBnCgTZ){RkEfjyMLDS = true;}
      if(DAVqLUpCsP == true){DAVqLUpCsP = false;}
      if(mfUQjpLMxx == true){mfUQjpLMxx = false;}
      if(oMbHUxxRJw == true){oMbHUxxRJw = false;}
      if(bzDFWQVhOl == true){bzDFWQVhOl = false;}
      if(XnDbqikVqL == true){XnDbqikVqL = false;}
      if(cpjWkpXOWN == true){cpjWkpXOWN = false;}
      if(XYswmncPtS == true){XYswmncPtS = false;}
      if(UcxKZAIAPk == true){UcxKZAIAPk = false;}
      if(LaayTlPfTf == true){LaayTlPfTf = false;}
      if(sGLAOzuHnD == true){sGLAOzuHnD = false;}
      if(GVbXpArYxk == true){GVbXpArYxk = false;}
      if(gWzkBwxucA == true){gWzkBwxucA = false;}
      if(XwwNZNQxwZ == true){XwwNZNQxwZ = false;}
      if(FBMLepzDHT == true){FBMLepzDHT = false;}
      if(spiizWHZyR == true){spiizWHZyR = false;}
      if(CAenfJYNyb == true){CAenfJYNyb = false;}
      if(iucWffJmGL == true){iucWffJmGL = false;}
      if(xtmJHhNMOC == true){xtmJHhNMOC = false;}
      if(GqydXEWYfU == true){GqydXEWYfU = false;}
      if(RkEfjyMLDS == true){RkEfjyMLDS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELZOUPLHVS
{ 
  void ejALdkjxSX()
  { 
      bool bjuENmdOpS = false;
      bool gEzCCeIEVZ = false;
      bool ukJEOUwEZo = false;
      bool criZnInQdc = false;
      bool OECLkCoFRh = false;
      bool LPNSzpZqpr = false;
      bool pYnBooUZNs = false;
      bool pqZsLqhySM = false;
      bool fqmrcNePax = false;
      bool ixakmoPBVw = false;
      bool gPrYqToUHH = false;
      bool HaXdMzlwXb = false;
      bool KFzQKsPoFV = false;
      bool bgcWeQzOAI = false;
      bool YJISoHYxYn = false;
      bool CTdtlbPaOy = false;
      bool DzOlfayByu = false;
      bool zXuOCAxfaC = false;
      bool TSPQSHCijD = false;
      bool AXzCEYuVmN = false;
      string ZIzANoDioL;
      string hKtdzrddOy;
      string uHmqNuTHRh;
      string drsdJyQHAJ;
      string SHWnSalPqo;
      string nEQaCSVHmR;
      string UwQHgoRQTA;
      string aWdEemjzXl;
      string JDQcsZbRbq;
      string cIThoWqPGc;
      string JVwpNRaLuO;
      string hWjAIRenOH;
      string NzocXRCwPI;
      string wTrtcmHaPa;
      string yPWMIGYSZX;
      string rCBzPJgSSu;
      string OewmSNdoXU;
      string JEYmIxbbTQ;
      string sjVrQsSseS;
      string GnHTMTTjst;
      if(ZIzANoDioL == JVwpNRaLuO){bjuENmdOpS = true;}
      else if(JVwpNRaLuO == ZIzANoDioL){gPrYqToUHH = true;}
      if(hKtdzrddOy == hWjAIRenOH){gEzCCeIEVZ = true;}
      else if(hWjAIRenOH == hKtdzrddOy){HaXdMzlwXb = true;}
      if(uHmqNuTHRh == NzocXRCwPI){ukJEOUwEZo = true;}
      else if(NzocXRCwPI == uHmqNuTHRh){KFzQKsPoFV = true;}
      if(drsdJyQHAJ == wTrtcmHaPa){criZnInQdc = true;}
      else if(wTrtcmHaPa == drsdJyQHAJ){bgcWeQzOAI = true;}
      if(SHWnSalPqo == yPWMIGYSZX){OECLkCoFRh = true;}
      else if(yPWMIGYSZX == SHWnSalPqo){YJISoHYxYn = true;}
      if(nEQaCSVHmR == rCBzPJgSSu){LPNSzpZqpr = true;}
      else if(rCBzPJgSSu == nEQaCSVHmR){CTdtlbPaOy = true;}
      if(UwQHgoRQTA == OewmSNdoXU){pYnBooUZNs = true;}
      else if(OewmSNdoXU == UwQHgoRQTA){DzOlfayByu = true;}
      if(aWdEemjzXl == JEYmIxbbTQ){pqZsLqhySM = true;}
      if(JDQcsZbRbq == sjVrQsSseS){fqmrcNePax = true;}
      if(cIThoWqPGc == GnHTMTTjst){ixakmoPBVw = true;}
      while(JEYmIxbbTQ == aWdEemjzXl){zXuOCAxfaC = true;}
      while(sjVrQsSseS == sjVrQsSseS){TSPQSHCijD = true;}
      while(GnHTMTTjst == GnHTMTTjst){AXzCEYuVmN = true;}
      if(bjuENmdOpS == true){bjuENmdOpS = false;}
      if(gEzCCeIEVZ == true){gEzCCeIEVZ = false;}
      if(ukJEOUwEZo == true){ukJEOUwEZo = false;}
      if(criZnInQdc == true){criZnInQdc = false;}
      if(OECLkCoFRh == true){OECLkCoFRh = false;}
      if(LPNSzpZqpr == true){LPNSzpZqpr = false;}
      if(pYnBooUZNs == true){pYnBooUZNs = false;}
      if(pqZsLqhySM == true){pqZsLqhySM = false;}
      if(fqmrcNePax == true){fqmrcNePax = false;}
      if(ixakmoPBVw == true){ixakmoPBVw = false;}
      if(gPrYqToUHH == true){gPrYqToUHH = false;}
      if(HaXdMzlwXb == true){HaXdMzlwXb = false;}
      if(KFzQKsPoFV == true){KFzQKsPoFV = false;}
      if(bgcWeQzOAI == true){bgcWeQzOAI = false;}
      if(YJISoHYxYn == true){YJISoHYxYn = false;}
      if(CTdtlbPaOy == true){CTdtlbPaOy = false;}
      if(DzOlfayByu == true){DzOlfayByu = false;}
      if(zXuOCAxfaC == true){zXuOCAxfaC = false;}
      if(TSPQSHCijD == true){TSPQSHCijD = false;}
      if(AXzCEYuVmN == true){AXzCEYuVmN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BHTUYIXRGH
{ 
  void tdARiYTKEc()
  { 
      bool qcBZGzfyft = false;
      bool ijPtbswVsJ = false;
      bool gONPzflxpa = false;
      bool jZyPUiURFS = false;
      bool YPdwmVtqjL = false;
      bool jTmMhcOkaa = false;
      bool NiHEJIlzYr = false;
      bool XdQZjRjQcc = false;
      bool ktMepQmlhq = false;
      bool TiqdFoHZle = false;
      bool juRrmGDMbP = false;
      bool syIypSVbNs = false;
      bool UzRhXomlUu = false;
      bool JJdxrpcUrj = false;
      bool MZJRyVZrnm = false;
      bool SfMsJjcjTy = false;
      bool TQrgGiTKFA = false;
      bool oBjcfupziB = false;
      bool OtxhbdxknI = false;
      bool MsBtQugcLP = false;
      string EhzZMTYqRe;
      string aNpomYXChM;
      string eiwIdbgdBJ;
      string RLWsjXkfhe;
      string imRfgeGpzU;
      string QhteAUlpwk;
      string luoINOqxEO;
      string nrUCdrRPbz;
      string UqdgriQrrO;
      string luiwrnxJRR;
      string nJkjgXNrAI;
      string DVNwQuQIPd;
      string yyEpcsIYJo;
      string tHxJLKFszT;
      string VXqjKPgmfx;
      string WosnToEuHn;
      string PoiLNuXDkF;
      string pXIuIZGUeM;
      string MVrMSENJpV;
      string GKlLEgofVP;
      if(EhzZMTYqRe == nJkjgXNrAI){qcBZGzfyft = true;}
      else if(nJkjgXNrAI == EhzZMTYqRe){juRrmGDMbP = true;}
      if(aNpomYXChM == DVNwQuQIPd){ijPtbswVsJ = true;}
      else if(DVNwQuQIPd == aNpomYXChM){syIypSVbNs = true;}
      if(eiwIdbgdBJ == yyEpcsIYJo){gONPzflxpa = true;}
      else if(yyEpcsIYJo == eiwIdbgdBJ){UzRhXomlUu = true;}
      if(RLWsjXkfhe == tHxJLKFszT){jZyPUiURFS = true;}
      else if(tHxJLKFszT == RLWsjXkfhe){JJdxrpcUrj = true;}
      if(imRfgeGpzU == VXqjKPgmfx){YPdwmVtqjL = true;}
      else if(VXqjKPgmfx == imRfgeGpzU){MZJRyVZrnm = true;}
      if(QhteAUlpwk == WosnToEuHn){jTmMhcOkaa = true;}
      else if(WosnToEuHn == QhteAUlpwk){SfMsJjcjTy = true;}
      if(luoINOqxEO == PoiLNuXDkF){NiHEJIlzYr = true;}
      else if(PoiLNuXDkF == luoINOqxEO){TQrgGiTKFA = true;}
      if(nrUCdrRPbz == pXIuIZGUeM){XdQZjRjQcc = true;}
      if(UqdgriQrrO == MVrMSENJpV){ktMepQmlhq = true;}
      if(luiwrnxJRR == GKlLEgofVP){TiqdFoHZle = true;}
      while(pXIuIZGUeM == nrUCdrRPbz){oBjcfupziB = true;}
      while(MVrMSENJpV == MVrMSENJpV){OtxhbdxknI = true;}
      while(GKlLEgofVP == GKlLEgofVP){MsBtQugcLP = true;}
      if(qcBZGzfyft == true){qcBZGzfyft = false;}
      if(ijPtbswVsJ == true){ijPtbswVsJ = false;}
      if(gONPzflxpa == true){gONPzflxpa = false;}
      if(jZyPUiURFS == true){jZyPUiURFS = false;}
      if(YPdwmVtqjL == true){YPdwmVtqjL = false;}
      if(jTmMhcOkaa == true){jTmMhcOkaa = false;}
      if(NiHEJIlzYr == true){NiHEJIlzYr = false;}
      if(XdQZjRjQcc == true){XdQZjRjQcc = false;}
      if(ktMepQmlhq == true){ktMepQmlhq = false;}
      if(TiqdFoHZle == true){TiqdFoHZle = false;}
      if(juRrmGDMbP == true){juRrmGDMbP = false;}
      if(syIypSVbNs == true){syIypSVbNs = false;}
      if(UzRhXomlUu == true){UzRhXomlUu = false;}
      if(JJdxrpcUrj == true){JJdxrpcUrj = false;}
      if(MZJRyVZrnm == true){MZJRyVZrnm = false;}
      if(SfMsJjcjTy == true){SfMsJjcjTy = false;}
      if(TQrgGiTKFA == true){TQrgGiTKFA = false;}
      if(oBjcfupziB == true){oBjcfupziB = false;}
      if(OtxhbdxknI == true){OtxhbdxknI = false;}
      if(MsBtQugcLP == true){MsBtQugcLP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPMEEGPTML
{ 
  void DiIAjodfbe()
  { 
      bool jNABMjkicc = false;
      bool sDpODdOLBj = false;
      bool xcWgyMWmNg = false;
      bool xAqbqmTmZO = false;
      bool JVaUrdQbut = false;
      bool rVHXMHpSCA = false;
      bool MxVwfrLOWQ = false;
      bool KalmZbBCnU = false;
      bool uuqSnbrTPj = false;
      bool wAkYBMAeoA = false;
      bool RCEejQjUxj = false;
      bool FndgERFCHD = false;
      bool ArymTKpMlN = false;
      bool aVMnDspMiW = false;
      bool rXVedIVDTi = false;
      bool GxWkzZDQLY = false;
      bool aWhjJiapdL = false;
      bool asSjLbVTIL = false;
      bool olrCHdybod = false;
      bool pYAJwUolVt = false;
      string ekpdsnYyaR;
      string TRsMcCMPAq;
      string VxrrJyZOUK;
      string fPqRXOIwtx;
      string CpsDVxTPyf;
      string CtTkdgsyUu;
      string NKdQkEZboO;
      string sPUCneDnWL;
      string dKPoIkuGmp;
      string VKbzjrMcRQ;
      string WraillZQwy;
      string dEbIRDtnHA;
      string ITnysinVSw;
      string SaWFokigCV;
      string LeJnMRiTgf;
      string xXURHDDbpD;
      string yDxAfCgVSf;
      string TNllndJAlb;
      string ATnlyuFEyl;
      string gHpyXHgJIJ;
      if(ekpdsnYyaR == WraillZQwy){jNABMjkicc = true;}
      else if(WraillZQwy == ekpdsnYyaR){RCEejQjUxj = true;}
      if(TRsMcCMPAq == dEbIRDtnHA){sDpODdOLBj = true;}
      else if(dEbIRDtnHA == TRsMcCMPAq){FndgERFCHD = true;}
      if(VxrrJyZOUK == ITnysinVSw){xcWgyMWmNg = true;}
      else if(ITnysinVSw == VxrrJyZOUK){ArymTKpMlN = true;}
      if(fPqRXOIwtx == SaWFokigCV){xAqbqmTmZO = true;}
      else if(SaWFokigCV == fPqRXOIwtx){aVMnDspMiW = true;}
      if(CpsDVxTPyf == LeJnMRiTgf){JVaUrdQbut = true;}
      else if(LeJnMRiTgf == CpsDVxTPyf){rXVedIVDTi = true;}
      if(CtTkdgsyUu == xXURHDDbpD){rVHXMHpSCA = true;}
      else if(xXURHDDbpD == CtTkdgsyUu){GxWkzZDQLY = true;}
      if(NKdQkEZboO == yDxAfCgVSf){MxVwfrLOWQ = true;}
      else if(yDxAfCgVSf == NKdQkEZboO){aWhjJiapdL = true;}
      if(sPUCneDnWL == TNllndJAlb){KalmZbBCnU = true;}
      if(dKPoIkuGmp == ATnlyuFEyl){uuqSnbrTPj = true;}
      if(VKbzjrMcRQ == gHpyXHgJIJ){wAkYBMAeoA = true;}
      while(TNllndJAlb == sPUCneDnWL){asSjLbVTIL = true;}
      while(ATnlyuFEyl == ATnlyuFEyl){olrCHdybod = true;}
      while(gHpyXHgJIJ == gHpyXHgJIJ){pYAJwUolVt = true;}
      if(jNABMjkicc == true){jNABMjkicc = false;}
      if(sDpODdOLBj == true){sDpODdOLBj = false;}
      if(xcWgyMWmNg == true){xcWgyMWmNg = false;}
      if(xAqbqmTmZO == true){xAqbqmTmZO = false;}
      if(JVaUrdQbut == true){JVaUrdQbut = false;}
      if(rVHXMHpSCA == true){rVHXMHpSCA = false;}
      if(MxVwfrLOWQ == true){MxVwfrLOWQ = false;}
      if(KalmZbBCnU == true){KalmZbBCnU = false;}
      if(uuqSnbrTPj == true){uuqSnbrTPj = false;}
      if(wAkYBMAeoA == true){wAkYBMAeoA = false;}
      if(RCEejQjUxj == true){RCEejQjUxj = false;}
      if(FndgERFCHD == true){FndgERFCHD = false;}
      if(ArymTKpMlN == true){ArymTKpMlN = false;}
      if(aVMnDspMiW == true){aVMnDspMiW = false;}
      if(rXVedIVDTi == true){rXVedIVDTi = false;}
      if(GxWkzZDQLY == true){GxWkzZDQLY = false;}
      if(aWhjJiapdL == true){aWhjJiapdL = false;}
      if(asSjLbVTIL == true){asSjLbVTIL = false;}
      if(olrCHdybod == true){olrCHdybod = false;}
      if(pYAJwUolVt == true){pYAJwUolVt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXOMZKGCIR
{ 
  void UuuuuRbpxp()
  { 
      bool lauyaOinqd = false;
      bool lBiJbZJUeq = false;
      bool dHEKbyqjSt = false;
      bool VVVrKqCBdS = false;
      bool HnVGMEntUx = false;
      bool ESOJJdWjWc = false;
      bool WzUxHPfqzk = false;
      bool XIqMiplxyW = false;
      bool JxPUoDGLhf = false;
      bool TRdAuISYzw = false;
      bool YxtiZubCaS = false;
      bool rYlATZjAHE = false;
      bool JUITRFdpQa = false;
      bool XMyBxLCfut = false;
      bool aEkOnufdfV = false;
      bool YSRumEoaRU = false;
      bool QlkzueZkCH = false;
      bool XDEMcEisfV = false;
      bool YzJuCFuDNs = false;
      bool WaOacoSkTI = false;
      string YuPbpmFAPZ;
      string xUnXMnTtCL;
      string epTQoSAaHK;
      string efhKpRcCSr;
      string yhTaeNIXEn;
      string qQmTlibzmX;
      string ldsEtRldht;
      string LRaJMwVslb;
      string JcVTTNrOXH;
      string pcPtGToOfN;
      string adoKbYpdGo;
      string MhNKNIIYkf;
      string YXFZEhCfCs;
      string HGMYBemLqt;
      string XOHitHPEgx;
      string LQdznCYPGt;
      string WJaMhGVoJh;
      string VwgpIKQWfw;
      string RxzFhqbNjy;
      string GXExWOntBn;
      if(YuPbpmFAPZ == adoKbYpdGo){lauyaOinqd = true;}
      else if(adoKbYpdGo == YuPbpmFAPZ){YxtiZubCaS = true;}
      if(xUnXMnTtCL == MhNKNIIYkf){lBiJbZJUeq = true;}
      else if(MhNKNIIYkf == xUnXMnTtCL){rYlATZjAHE = true;}
      if(epTQoSAaHK == YXFZEhCfCs){dHEKbyqjSt = true;}
      else if(YXFZEhCfCs == epTQoSAaHK){JUITRFdpQa = true;}
      if(efhKpRcCSr == HGMYBemLqt){VVVrKqCBdS = true;}
      else if(HGMYBemLqt == efhKpRcCSr){XMyBxLCfut = true;}
      if(yhTaeNIXEn == XOHitHPEgx){HnVGMEntUx = true;}
      else if(XOHitHPEgx == yhTaeNIXEn){aEkOnufdfV = true;}
      if(qQmTlibzmX == LQdznCYPGt){ESOJJdWjWc = true;}
      else if(LQdznCYPGt == qQmTlibzmX){YSRumEoaRU = true;}
      if(ldsEtRldht == WJaMhGVoJh){WzUxHPfqzk = true;}
      else if(WJaMhGVoJh == ldsEtRldht){QlkzueZkCH = true;}
      if(LRaJMwVslb == VwgpIKQWfw){XIqMiplxyW = true;}
      if(JcVTTNrOXH == RxzFhqbNjy){JxPUoDGLhf = true;}
      if(pcPtGToOfN == GXExWOntBn){TRdAuISYzw = true;}
      while(VwgpIKQWfw == LRaJMwVslb){XDEMcEisfV = true;}
      while(RxzFhqbNjy == RxzFhqbNjy){YzJuCFuDNs = true;}
      while(GXExWOntBn == GXExWOntBn){WaOacoSkTI = true;}
      if(lauyaOinqd == true){lauyaOinqd = false;}
      if(lBiJbZJUeq == true){lBiJbZJUeq = false;}
      if(dHEKbyqjSt == true){dHEKbyqjSt = false;}
      if(VVVrKqCBdS == true){VVVrKqCBdS = false;}
      if(HnVGMEntUx == true){HnVGMEntUx = false;}
      if(ESOJJdWjWc == true){ESOJJdWjWc = false;}
      if(WzUxHPfqzk == true){WzUxHPfqzk = false;}
      if(XIqMiplxyW == true){XIqMiplxyW = false;}
      if(JxPUoDGLhf == true){JxPUoDGLhf = false;}
      if(TRdAuISYzw == true){TRdAuISYzw = false;}
      if(YxtiZubCaS == true){YxtiZubCaS = false;}
      if(rYlATZjAHE == true){rYlATZjAHE = false;}
      if(JUITRFdpQa == true){JUITRFdpQa = false;}
      if(XMyBxLCfut == true){XMyBxLCfut = false;}
      if(aEkOnufdfV == true){aEkOnufdfV = false;}
      if(YSRumEoaRU == true){YSRumEoaRU = false;}
      if(QlkzueZkCH == true){QlkzueZkCH = false;}
      if(XDEMcEisfV == true){XDEMcEisfV = false;}
      if(YzJuCFuDNs == true){YzJuCFuDNs = false;}
      if(WaOacoSkTI == true){WaOacoSkTI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTTZTBBMBV
{ 
  void cJSOZtRPpA()
  { 
      bool pVlFGljJRW = false;
      bool oGwTXUSyNz = false;
      bool znHYkWpbpl = false;
      bool ODKbrPBRtY = false;
      bool ALyMJFsmEK = false;
      bool xIorYBOMUj = false;
      bool uHTfIlwTbI = false;
      bool SBEnzmpuPe = false;
      bool cDXenGOSDp = false;
      bool AnwJcsrRDX = false;
      bool JYKwqwDArl = false;
      bool LTxoGrinqC = false;
      bool WcQkHeEtKG = false;
      bool tXqrVDsbmq = false;
      bool CNZRegqGCk = false;
      bool JEaBAfIYoM = false;
      bool rJolqmcFTD = false;
      bool yGAAzJCzGZ = false;
      bool mxrZwpxoqo = false;
      bool uTmaysYmaq = false;
      string rSZclNKbcU;
      string giLnlWxznO;
      string cfUNjJhUla;
      string ngCycdrVAA;
      string eWpJSKACjo;
      string gPIFOMyMrc;
      string fpoBgzfNKH;
      string ebynjFoLtZ;
      string IekxsXYxjQ;
      string fedXTngnbS;
      string emrcJFQTUI;
      string WlSSTAFrII;
      string aictazxaUu;
      string YBibtVmHmm;
      string GFbassMKDT;
      string ioeTruJxBK;
      string HpzZjUDpXx;
      string MxEVCUGCAh;
      string lmXALjVPiz;
      string MpGbeQGCqX;
      if(rSZclNKbcU == emrcJFQTUI){pVlFGljJRW = true;}
      else if(emrcJFQTUI == rSZclNKbcU){JYKwqwDArl = true;}
      if(giLnlWxznO == WlSSTAFrII){oGwTXUSyNz = true;}
      else if(WlSSTAFrII == giLnlWxznO){LTxoGrinqC = true;}
      if(cfUNjJhUla == aictazxaUu){znHYkWpbpl = true;}
      else if(aictazxaUu == cfUNjJhUla){WcQkHeEtKG = true;}
      if(ngCycdrVAA == YBibtVmHmm){ODKbrPBRtY = true;}
      else if(YBibtVmHmm == ngCycdrVAA){tXqrVDsbmq = true;}
      if(eWpJSKACjo == GFbassMKDT){ALyMJFsmEK = true;}
      else if(GFbassMKDT == eWpJSKACjo){CNZRegqGCk = true;}
      if(gPIFOMyMrc == ioeTruJxBK){xIorYBOMUj = true;}
      else if(ioeTruJxBK == gPIFOMyMrc){JEaBAfIYoM = true;}
      if(fpoBgzfNKH == HpzZjUDpXx){uHTfIlwTbI = true;}
      else if(HpzZjUDpXx == fpoBgzfNKH){rJolqmcFTD = true;}
      if(ebynjFoLtZ == MxEVCUGCAh){SBEnzmpuPe = true;}
      if(IekxsXYxjQ == lmXALjVPiz){cDXenGOSDp = true;}
      if(fedXTngnbS == MpGbeQGCqX){AnwJcsrRDX = true;}
      while(MxEVCUGCAh == ebynjFoLtZ){yGAAzJCzGZ = true;}
      while(lmXALjVPiz == lmXALjVPiz){mxrZwpxoqo = true;}
      while(MpGbeQGCqX == MpGbeQGCqX){uTmaysYmaq = true;}
      if(pVlFGljJRW == true){pVlFGljJRW = false;}
      if(oGwTXUSyNz == true){oGwTXUSyNz = false;}
      if(znHYkWpbpl == true){znHYkWpbpl = false;}
      if(ODKbrPBRtY == true){ODKbrPBRtY = false;}
      if(ALyMJFsmEK == true){ALyMJFsmEK = false;}
      if(xIorYBOMUj == true){xIorYBOMUj = false;}
      if(uHTfIlwTbI == true){uHTfIlwTbI = false;}
      if(SBEnzmpuPe == true){SBEnzmpuPe = false;}
      if(cDXenGOSDp == true){cDXenGOSDp = false;}
      if(AnwJcsrRDX == true){AnwJcsrRDX = false;}
      if(JYKwqwDArl == true){JYKwqwDArl = false;}
      if(LTxoGrinqC == true){LTxoGrinqC = false;}
      if(WcQkHeEtKG == true){WcQkHeEtKG = false;}
      if(tXqrVDsbmq == true){tXqrVDsbmq = false;}
      if(CNZRegqGCk == true){CNZRegqGCk = false;}
      if(JEaBAfIYoM == true){JEaBAfIYoM = false;}
      if(rJolqmcFTD == true){rJolqmcFTD = false;}
      if(yGAAzJCzGZ == true){yGAAzJCzGZ = false;}
      if(mxrZwpxoqo == true){mxrZwpxoqo = false;}
      if(uTmaysYmaq == true){uTmaysYmaq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYMWZRTUSZ
{ 
  void eVcRjMhVmx()
  { 
      bool xsDnWthOUT = false;
      bool kfUwSfgVFN = false;
      bool naIBqRLoQo = false;
      bool uMZpUSgLJJ = false;
      bool QNWMPttfFG = false;
      bool hmgRVWjBwF = false;
      bool hsyfYYFdbz = false;
      bool zVLwwaDwlx = false;
      bool WfiJHHeHTy = false;
      bool hfOEbXOqmp = false;
      bool nQEGHLbkUu = false;
      bool SnOziCJoYQ = false;
      bool sxJdQTGHTX = false;
      bool LMIuIGacBu = false;
      bool ftmYftQPVY = false;
      bool OZSWxpGaon = false;
      bool ETQwiFfTpb = false;
      bool afmckzKjyW = false;
      bool DqltJlslyS = false;
      bool zAnNpLcppZ = false;
      string EcozyLFYcp;
      string SlLrPprsoA;
      string OUAApaFddH;
      string GAxNYdRFGd;
      string sHxJGWfTkz;
      string uYzDOjbnJX;
      string FauViRoxSl;
      string YmmKGGWqtT;
      string tlrdMhBszo;
      string BcwhXSMbZo;
      string giAzaHloxH;
      string MktocTiQIA;
      string QwxdjuqElm;
      string tuRElLlsDE;
      string wLwrbQiGFE;
      string juSYXkkWPe;
      string QgCJMQSoDR;
      string goNDEEzFBS;
      string MjzgDzcrfB;
      string ZPcXmPImeK;
      if(EcozyLFYcp == giAzaHloxH){xsDnWthOUT = true;}
      else if(giAzaHloxH == EcozyLFYcp){nQEGHLbkUu = true;}
      if(SlLrPprsoA == MktocTiQIA){kfUwSfgVFN = true;}
      else if(MktocTiQIA == SlLrPprsoA){SnOziCJoYQ = true;}
      if(OUAApaFddH == QwxdjuqElm){naIBqRLoQo = true;}
      else if(QwxdjuqElm == OUAApaFddH){sxJdQTGHTX = true;}
      if(GAxNYdRFGd == tuRElLlsDE){uMZpUSgLJJ = true;}
      else if(tuRElLlsDE == GAxNYdRFGd){LMIuIGacBu = true;}
      if(sHxJGWfTkz == wLwrbQiGFE){QNWMPttfFG = true;}
      else if(wLwrbQiGFE == sHxJGWfTkz){ftmYftQPVY = true;}
      if(uYzDOjbnJX == juSYXkkWPe){hmgRVWjBwF = true;}
      else if(juSYXkkWPe == uYzDOjbnJX){OZSWxpGaon = true;}
      if(FauViRoxSl == QgCJMQSoDR){hsyfYYFdbz = true;}
      else if(QgCJMQSoDR == FauViRoxSl){ETQwiFfTpb = true;}
      if(YmmKGGWqtT == goNDEEzFBS){zVLwwaDwlx = true;}
      if(tlrdMhBszo == MjzgDzcrfB){WfiJHHeHTy = true;}
      if(BcwhXSMbZo == ZPcXmPImeK){hfOEbXOqmp = true;}
      while(goNDEEzFBS == YmmKGGWqtT){afmckzKjyW = true;}
      while(MjzgDzcrfB == MjzgDzcrfB){DqltJlslyS = true;}
      while(ZPcXmPImeK == ZPcXmPImeK){zAnNpLcppZ = true;}
      if(xsDnWthOUT == true){xsDnWthOUT = false;}
      if(kfUwSfgVFN == true){kfUwSfgVFN = false;}
      if(naIBqRLoQo == true){naIBqRLoQo = false;}
      if(uMZpUSgLJJ == true){uMZpUSgLJJ = false;}
      if(QNWMPttfFG == true){QNWMPttfFG = false;}
      if(hmgRVWjBwF == true){hmgRVWjBwF = false;}
      if(hsyfYYFdbz == true){hsyfYYFdbz = false;}
      if(zVLwwaDwlx == true){zVLwwaDwlx = false;}
      if(WfiJHHeHTy == true){WfiJHHeHTy = false;}
      if(hfOEbXOqmp == true){hfOEbXOqmp = false;}
      if(nQEGHLbkUu == true){nQEGHLbkUu = false;}
      if(SnOziCJoYQ == true){SnOziCJoYQ = false;}
      if(sxJdQTGHTX == true){sxJdQTGHTX = false;}
      if(LMIuIGacBu == true){LMIuIGacBu = false;}
      if(ftmYftQPVY == true){ftmYftQPVY = false;}
      if(OZSWxpGaon == true){OZSWxpGaon = false;}
      if(ETQwiFfTpb == true){ETQwiFfTpb = false;}
      if(afmckzKjyW == true){afmckzKjyW = false;}
      if(DqltJlslyS == true){DqltJlslyS = false;}
      if(zAnNpLcppZ == true){zAnNpLcppZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRVFCYQUHQ
{ 
  void tjJUnEYNxA()
  { 
      bool BGSNFqbfNh = false;
      bool zHDRYNKLjG = false;
      bool XbgfhLsTGk = false;
      bool fnzGqjuDUy = false;
      bool HVsSNsBaUm = false;
      bool wIzFYZZmft = false;
      bool yIZbBLHxao = false;
      bool SHqkzChNRn = false;
      bool JRySoXnshR = false;
      bool JIXZAzwRQC = false;
      bool kEAfUoQOGW = false;
      bool qLUqjfJGmd = false;
      bool WOPIeKiQjz = false;
      bool FQwPCFQRyz = false;
      bool GZlKaxmgpT = false;
      bool oodleWorBK = false;
      bool GAdHQZPFnd = false;
      bool PrInXxbEhg = false;
      bool WCaPJQmKjf = false;
      bool QYPmrGuesA = false;
      string SxCCOQkbFj;
      string TUCXFkbLYq;
      string lsuLgMqBss;
      string dWjVLnxLza;
      string DxhrlpMuHk;
      string QCggEZCpUB;
      string ZjhLGwkfMR;
      string mPLymoKCYp;
      string AusIcapDRl;
      string lGpxATPVlo;
      string FghpxApisP;
      string OARdBdpYie;
      string GhNaegZNxT;
      string YoPikTNDLb;
      string kGJCWloLwW;
      string dpmHhXSHKQ;
      string aclZpZjhsh;
      string QlNGsAXLDs;
      string qNRZpiBHBN;
      string AFstAHTjMx;
      if(SxCCOQkbFj == FghpxApisP){BGSNFqbfNh = true;}
      else if(FghpxApisP == SxCCOQkbFj){kEAfUoQOGW = true;}
      if(TUCXFkbLYq == OARdBdpYie){zHDRYNKLjG = true;}
      else if(OARdBdpYie == TUCXFkbLYq){qLUqjfJGmd = true;}
      if(lsuLgMqBss == GhNaegZNxT){XbgfhLsTGk = true;}
      else if(GhNaegZNxT == lsuLgMqBss){WOPIeKiQjz = true;}
      if(dWjVLnxLza == YoPikTNDLb){fnzGqjuDUy = true;}
      else if(YoPikTNDLb == dWjVLnxLza){FQwPCFQRyz = true;}
      if(DxhrlpMuHk == kGJCWloLwW){HVsSNsBaUm = true;}
      else if(kGJCWloLwW == DxhrlpMuHk){GZlKaxmgpT = true;}
      if(QCggEZCpUB == dpmHhXSHKQ){wIzFYZZmft = true;}
      else if(dpmHhXSHKQ == QCggEZCpUB){oodleWorBK = true;}
      if(ZjhLGwkfMR == aclZpZjhsh){yIZbBLHxao = true;}
      else if(aclZpZjhsh == ZjhLGwkfMR){GAdHQZPFnd = true;}
      if(mPLymoKCYp == QlNGsAXLDs){SHqkzChNRn = true;}
      if(AusIcapDRl == qNRZpiBHBN){JRySoXnshR = true;}
      if(lGpxATPVlo == AFstAHTjMx){JIXZAzwRQC = true;}
      while(QlNGsAXLDs == mPLymoKCYp){PrInXxbEhg = true;}
      while(qNRZpiBHBN == qNRZpiBHBN){WCaPJQmKjf = true;}
      while(AFstAHTjMx == AFstAHTjMx){QYPmrGuesA = true;}
      if(BGSNFqbfNh == true){BGSNFqbfNh = false;}
      if(zHDRYNKLjG == true){zHDRYNKLjG = false;}
      if(XbgfhLsTGk == true){XbgfhLsTGk = false;}
      if(fnzGqjuDUy == true){fnzGqjuDUy = false;}
      if(HVsSNsBaUm == true){HVsSNsBaUm = false;}
      if(wIzFYZZmft == true){wIzFYZZmft = false;}
      if(yIZbBLHxao == true){yIZbBLHxao = false;}
      if(SHqkzChNRn == true){SHqkzChNRn = false;}
      if(JRySoXnshR == true){JRySoXnshR = false;}
      if(JIXZAzwRQC == true){JIXZAzwRQC = false;}
      if(kEAfUoQOGW == true){kEAfUoQOGW = false;}
      if(qLUqjfJGmd == true){qLUqjfJGmd = false;}
      if(WOPIeKiQjz == true){WOPIeKiQjz = false;}
      if(FQwPCFQRyz == true){FQwPCFQRyz = false;}
      if(GZlKaxmgpT == true){GZlKaxmgpT = false;}
      if(oodleWorBK == true){oodleWorBK = false;}
      if(GAdHQZPFnd == true){GAdHQZPFnd = false;}
      if(PrInXxbEhg == true){PrInXxbEhg = false;}
      if(WCaPJQmKjf == true){WCaPJQmKjf = false;}
      if(QYPmrGuesA == true){QYPmrGuesA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IIKOCEBPDA
{ 
  void EWjPXmcrHA()
  { 
      bool nAwKNTzTGl = false;
      bool iXPuPQbUsA = false;
      bool jSWuQnhwCm = false;
      bool YDsVKonkIP = false;
      bool sgeDXDeIXO = false;
      bool LXEmxVdAsY = false;
      bool lDRTNfdtka = false;
      bool bpLcHDmSXN = false;
      bool IYYmaByGXn = false;
      bool KnrjdoOLpq = false;
      bool ZkXwmVLaft = false;
      bool iKbfPMeesM = false;
      bool gXVwPmxbzR = false;
      bool nbbfmXBczE = false;
      bool oWZdFzLMUQ = false;
      bool KiSdKCOafz = false;
      bool XjbOFHiurq = false;
      bool LCenXJxrqP = false;
      bool bkHiGFJyVk = false;
      bool IZwzgEuLYx = false;
      string WgUAXSyMLF;
      string SVkpeHZlLo;
      string fPYIxsRdhf;
      string jUuQOWiwIw;
      string JpwmFopPsg;
      string NBZzLHHMCd;
      string ATdfUxZUbH;
      string YcdPfoSkDH;
      string DCjBRiuwEG;
      string PWtduoMPSH;
      string PVnlHkXKTW;
      string nWIuayjcOl;
      string CdPUqCizTp;
      string cDSurhNysg;
      string LjbhSrNyDx;
      string FiBgEkFStF;
      string BXqdskDMCs;
      string jkjgZRBhCz;
      string okwVjsBkpG;
      string buDmemsyng;
      if(WgUAXSyMLF == PVnlHkXKTW){nAwKNTzTGl = true;}
      else if(PVnlHkXKTW == WgUAXSyMLF){ZkXwmVLaft = true;}
      if(SVkpeHZlLo == nWIuayjcOl){iXPuPQbUsA = true;}
      else if(nWIuayjcOl == SVkpeHZlLo){iKbfPMeesM = true;}
      if(fPYIxsRdhf == CdPUqCizTp){jSWuQnhwCm = true;}
      else if(CdPUqCizTp == fPYIxsRdhf){gXVwPmxbzR = true;}
      if(jUuQOWiwIw == cDSurhNysg){YDsVKonkIP = true;}
      else if(cDSurhNysg == jUuQOWiwIw){nbbfmXBczE = true;}
      if(JpwmFopPsg == LjbhSrNyDx){sgeDXDeIXO = true;}
      else if(LjbhSrNyDx == JpwmFopPsg){oWZdFzLMUQ = true;}
      if(NBZzLHHMCd == FiBgEkFStF){LXEmxVdAsY = true;}
      else if(FiBgEkFStF == NBZzLHHMCd){KiSdKCOafz = true;}
      if(ATdfUxZUbH == BXqdskDMCs){lDRTNfdtka = true;}
      else if(BXqdskDMCs == ATdfUxZUbH){XjbOFHiurq = true;}
      if(YcdPfoSkDH == jkjgZRBhCz){bpLcHDmSXN = true;}
      if(DCjBRiuwEG == okwVjsBkpG){IYYmaByGXn = true;}
      if(PWtduoMPSH == buDmemsyng){KnrjdoOLpq = true;}
      while(jkjgZRBhCz == YcdPfoSkDH){LCenXJxrqP = true;}
      while(okwVjsBkpG == okwVjsBkpG){bkHiGFJyVk = true;}
      while(buDmemsyng == buDmemsyng){IZwzgEuLYx = true;}
      if(nAwKNTzTGl == true){nAwKNTzTGl = false;}
      if(iXPuPQbUsA == true){iXPuPQbUsA = false;}
      if(jSWuQnhwCm == true){jSWuQnhwCm = false;}
      if(YDsVKonkIP == true){YDsVKonkIP = false;}
      if(sgeDXDeIXO == true){sgeDXDeIXO = false;}
      if(LXEmxVdAsY == true){LXEmxVdAsY = false;}
      if(lDRTNfdtka == true){lDRTNfdtka = false;}
      if(bpLcHDmSXN == true){bpLcHDmSXN = false;}
      if(IYYmaByGXn == true){IYYmaByGXn = false;}
      if(KnrjdoOLpq == true){KnrjdoOLpq = false;}
      if(ZkXwmVLaft == true){ZkXwmVLaft = false;}
      if(iKbfPMeesM == true){iKbfPMeesM = false;}
      if(gXVwPmxbzR == true){gXVwPmxbzR = false;}
      if(nbbfmXBczE == true){nbbfmXBczE = false;}
      if(oWZdFzLMUQ == true){oWZdFzLMUQ = false;}
      if(KiSdKCOafz == true){KiSdKCOafz = false;}
      if(XjbOFHiurq == true){XjbOFHiurq = false;}
      if(LCenXJxrqP == true){LCenXJxrqP = false;}
      if(bkHiGFJyVk == true){bkHiGFJyVk = false;}
      if(IZwzgEuLYx == true){IZwzgEuLYx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQRGBYQHCW
{ 
  void AaigJrzfEu()
  { 
      bool wsOxRkldPF = false;
      bool gWwXFMRcwh = false;
      bool USmjpGsGos = false;
      bool niEsKXUjla = false;
      bool HinLMdDXFX = false;
      bool GDMcudFeHL = false;
      bool qfoVRxSDMg = false;
      bool rhqVZleaWL = false;
      bool CVBQmkVaxg = false;
      bool RobaibsRtP = false;
      bool LzLXfXMqDJ = false;
      bool zeHwIUdXig = false;
      bool aqFeOCFPly = false;
      bool rMgHzCJcjP = false;
      bool XeXmhmhfSN = false;
      bool xViNnTtfId = false;
      bool RwEERlxAwF = false;
      bool LBmSIuTSwb = false;
      bool TZxXAWdTSe = false;
      bool IdTGxbaSVw = false;
      string XjMQpPelCr;
      string pHIaoJIQXR;
      string WxSNNijiTq;
      string HljpWpwqZN;
      string nVVJLIGRDz;
      string mMRXbZQzCG;
      string ewSKkDXRDy;
      string MQpJdBbJBF;
      string bSeTDtULOw;
      string ZwoTiqCKXI;
      string koNEmWWHta;
      string yHyxdLQyGp;
      string hLCHYPaWal;
      string yQkrTmFagg;
      string XNRmyRyroW;
      string aEEhaZlFeW;
      string uzgHbgVFcq;
      string FpRZRUsPJH;
      string RihDLtMDRs;
      string BzwKkXfJLQ;
      if(XjMQpPelCr == koNEmWWHta){wsOxRkldPF = true;}
      else if(koNEmWWHta == XjMQpPelCr){LzLXfXMqDJ = true;}
      if(pHIaoJIQXR == yHyxdLQyGp){gWwXFMRcwh = true;}
      else if(yHyxdLQyGp == pHIaoJIQXR){zeHwIUdXig = true;}
      if(WxSNNijiTq == hLCHYPaWal){USmjpGsGos = true;}
      else if(hLCHYPaWal == WxSNNijiTq){aqFeOCFPly = true;}
      if(HljpWpwqZN == yQkrTmFagg){niEsKXUjla = true;}
      else if(yQkrTmFagg == HljpWpwqZN){rMgHzCJcjP = true;}
      if(nVVJLIGRDz == XNRmyRyroW){HinLMdDXFX = true;}
      else if(XNRmyRyroW == nVVJLIGRDz){XeXmhmhfSN = true;}
      if(mMRXbZQzCG == aEEhaZlFeW){GDMcudFeHL = true;}
      else if(aEEhaZlFeW == mMRXbZQzCG){xViNnTtfId = true;}
      if(ewSKkDXRDy == uzgHbgVFcq){qfoVRxSDMg = true;}
      else if(uzgHbgVFcq == ewSKkDXRDy){RwEERlxAwF = true;}
      if(MQpJdBbJBF == FpRZRUsPJH){rhqVZleaWL = true;}
      if(bSeTDtULOw == RihDLtMDRs){CVBQmkVaxg = true;}
      if(ZwoTiqCKXI == BzwKkXfJLQ){RobaibsRtP = true;}
      while(FpRZRUsPJH == MQpJdBbJBF){LBmSIuTSwb = true;}
      while(RihDLtMDRs == RihDLtMDRs){TZxXAWdTSe = true;}
      while(BzwKkXfJLQ == BzwKkXfJLQ){IdTGxbaSVw = true;}
      if(wsOxRkldPF == true){wsOxRkldPF = false;}
      if(gWwXFMRcwh == true){gWwXFMRcwh = false;}
      if(USmjpGsGos == true){USmjpGsGos = false;}
      if(niEsKXUjla == true){niEsKXUjla = false;}
      if(HinLMdDXFX == true){HinLMdDXFX = false;}
      if(GDMcudFeHL == true){GDMcudFeHL = false;}
      if(qfoVRxSDMg == true){qfoVRxSDMg = false;}
      if(rhqVZleaWL == true){rhqVZleaWL = false;}
      if(CVBQmkVaxg == true){CVBQmkVaxg = false;}
      if(RobaibsRtP == true){RobaibsRtP = false;}
      if(LzLXfXMqDJ == true){LzLXfXMqDJ = false;}
      if(zeHwIUdXig == true){zeHwIUdXig = false;}
      if(aqFeOCFPly == true){aqFeOCFPly = false;}
      if(rMgHzCJcjP == true){rMgHzCJcjP = false;}
      if(XeXmhmhfSN == true){XeXmhmhfSN = false;}
      if(xViNnTtfId == true){xViNnTtfId = false;}
      if(RwEERlxAwF == true){RwEERlxAwF = false;}
      if(LBmSIuTSwb == true){LBmSIuTSwb = false;}
      if(TZxXAWdTSe == true){TZxXAWdTSe = false;}
      if(IdTGxbaSVw == true){IdTGxbaSVw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKVDCNVPIH
{ 
  void IdjBqjNNqz()
  { 
      bool JjCAQaEfSO = false;
      bool amQrDaoyfK = false;
      bool sXgWoNjqjD = false;
      bool ndcNrZqVQR = false;
      bool KJyhXfYYYq = false;
      bool NiEtPkCeLC = false;
      bool pNuPaxJCzd = false;
      bool iShOziYzyI = false;
      bool oLRroEZiyH = false;
      bool WLKNaxNiHa = false;
      bool WVYuItBpug = false;
      bool LCgCNdwDZW = false;
      bool XZErGXITmC = false;
      bool VprWlTmWju = false;
      bool CimQuTdHAx = false;
      bool AKIkDwQgnj = false;
      bool kgDsKVKJPt = false;
      bool qYSeTnmmwl = false;
      bool sATpBKgGTp = false;
      bool CFhzJUftGZ = false;
      string mQTJeIGqeD;
      string MaoQalJCOT;
      string piBFqMukHQ;
      string dfCgCtnEUM;
      string KSlSCmpPch;
      string qYiBmEOORR;
      string MUjOZgXHNg;
      string xFhBJXwiCE;
      string VfHZYFwAty;
      string eZlDAohXsU;
      string OhCwjlphrP;
      string HfLNufNJoU;
      string jXNOBWSeBT;
      string oYpgpmcLol;
      string OOIeqzNYHT;
      string bYiYjpUntM;
      string TLfXZhodWH;
      string DBTCFVOhWC;
      string JsWgrPoRwz;
      string SoQcSChkEI;
      if(mQTJeIGqeD == OhCwjlphrP){JjCAQaEfSO = true;}
      else if(OhCwjlphrP == mQTJeIGqeD){WVYuItBpug = true;}
      if(MaoQalJCOT == HfLNufNJoU){amQrDaoyfK = true;}
      else if(HfLNufNJoU == MaoQalJCOT){LCgCNdwDZW = true;}
      if(piBFqMukHQ == jXNOBWSeBT){sXgWoNjqjD = true;}
      else if(jXNOBWSeBT == piBFqMukHQ){XZErGXITmC = true;}
      if(dfCgCtnEUM == oYpgpmcLol){ndcNrZqVQR = true;}
      else if(oYpgpmcLol == dfCgCtnEUM){VprWlTmWju = true;}
      if(KSlSCmpPch == OOIeqzNYHT){KJyhXfYYYq = true;}
      else if(OOIeqzNYHT == KSlSCmpPch){CimQuTdHAx = true;}
      if(qYiBmEOORR == bYiYjpUntM){NiEtPkCeLC = true;}
      else if(bYiYjpUntM == qYiBmEOORR){AKIkDwQgnj = true;}
      if(MUjOZgXHNg == TLfXZhodWH){pNuPaxJCzd = true;}
      else if(TLfXZhodWH == MUjOZgXHNg){kgDsKVKJPt = true;}
      if(xFhBJXwiCE == DBTCFVOhWC){iShOziYzyI = true;}
      if(VfHZYFwAty == JsWgrPoRwz){oLRroEZiyH = true;}
      if(eZlDAohXsU == SoQcSChkEI){WLKNaxNiHa = true;}
      while(DBTCFVOhWC == xFhBJXwiCE){qYSeTnmmwl = true;}
      while(JsWgrPoRwz == JsWgrPoRwz){sATpBKgGTp = true;}
      while(SoQcSChkEI == SoQcSChkEI){CFhzJUftGZ = true;}
      if(JjCAQaEfSO == true){JjCAQaEfSO = false;}
      if(amQrDaoyfK == true){amQrDaoyfK = false;}
      if(sXgWoNjqjD == true){sXgWoNjqjD = false;}
      if(ndcNrZqVQR == true){ndcNrZqVQR = false;}
      if(KJyhXfYYYq == true){KJyhXfYYYq = false;}
      if(NiEtPkCeLC == true){NiEtPkCeLC = false;}
      if(pNuPaxJCzd == true){pNuPaxJCzd = false;}
      if(iShOziYzyI == true){iShOziYzyI = false;}
      if(oLRroEZiyH == true){oLRroEZiyH = false;}
      if(WLKNaxNiHa == true){WLKNaxNiHa = false;}
      if(WVYuItBpug == true){WVYuItBpug = false;}
      if(LCgCNdwDZW == true){LCgCNdwDZW = false;}
      if(XZErGXITmC == true){XZErGXITmC = false;}
      if(VprWlTmWju == true){VprWlTmWju = false;}
      if(CimQuTdHAx == true){CimQuTdHAx = false;}
      if(AKIkDwQgnj == true){AKIkDwQgnj = false;}
      if(kgDsKVKJPt == true){kgDsKVKJPt = false;}
      if(qYSeTnmmwl == true){qYSeTnmmwl = false;}
      if(sATpBKgGTp == true){sATpBKgGTp = false;}
      if(CFhzJUftGZ == true){CFhzJUftGZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOOXSPSBNJ
{ 
  void KNWYiXVlhj()
  { 
      bool LnSaRJMQgR = false;
      bool AjhlybtdhY = false;
      bool dQqQIOAVOG = false;
      bool uMJdsIlmzG = false;
      bool RqitxNxWQh = false;
      bool IFHPyuxCSD = false;
      bool JqCZVmaEsp = false;
      bool oGdbHlhwTt = false;
      bool QcEfypFsex = false;
      bool KjTwwaoIYJ = false;
      bool mscarBafHL = false;
      bool NBhYlflVaf = false;
      bool hgYueFlheg = false;
      bool xYXKGXzdnx = false;
      bool OZkTjJBuKQ = false;
      bool nSgrbFTgum = false;
      bool OsAaNncXRO = false;
      bool fIhdRIuFKV = false;
      bool DqWOsdrfhA = false;
      bool DRhBhUYKFw = false;
      string mNZSmpIWBR;
      string HhlGLhrcZs;
      string IwJsGtzHdT;
      string ioSXoilIMS;
      string emosaJnXRg;
      string FUhwAqDfLs;
      string pAsgiROOQc;
      string ujPHOVGQSw;
      string GapwOOGWXx;
      string eGwTbetIKI;
      string uZHokVEahe;
      string jmNOlOKwRT;
      string LqqSxomwej;
      string byGJBfTBLs;
      string KfnrNrrggM;
      string TxppxDhnqu;
      string hIwyDlfDNG;
      string uJkYJeDyFE;
      string xFORPdHPMx;
      string xfJPKCjpob;
      if(mNZSmpIWBR == uZHokVEahe){LnSaRJMQgR = true;}
      else if(uZHokVEahe == mNZSmpIWBR){mscarBafHL = true;}
      if(HhlGLhrcZs == jmNOlOKwRT){AjhlybtdhY = true;}
      else if(jmNOlOKwRT == HhlGLhrcZs){NBhYlflVaf = true;}
      if(IwJsGtzHdT == LqqSxomwej){dQqQIOAVOG = true;}
      else if(LqqSxomwej == IwJsGtzHdT){hgYueFlheg = true;}
      if(ioSXoilIMS == byGJBfTBLs){uMJdsIlmzG = true;}
      else if(byGJBfTBLs == ioSXoilIMS){xYXKGXzdnx = true;}
      if(emosaJnXRg == KfnrNrrggM){RqitxNxWQh = true;}
      else if(KfnrNrrggM == emosaJnXRg){OZkTjJBuKQ = true;}
      if(FUhwAqDfLs == TxppxDhnqu){IFHPyuxCSD = true;}
      else if(TxppxDhnqu == FUhwAqDfLs){nSgrbFTgum = true;}
      if(pAsgiROOQc == hIwyDlfDNG){JqCZVmaEsp = true;}
      else if(hIwyDlfDNG == pAsgiROOQc){OsAaNncXRO = true;}
      if(ujPHOVGQSw == uJkYJeDyFE){oGdbHlhwTt = true;}
      if(GapwOOGWXx == xFORPdHPMx){QcEfypFsex = true;}
      if(eGwTbetIKI == xfJPKCjpob){KjTwwaoIYJ = true;}
      while(uJkYJeDyFE == ujPHOVGQSw){fIhdRIuFKV = true;}
      while(xFORPdHPMx == xFORPdHPMx){DqWOsdrfhA = true;}
      while(xfJPKCjpob == xfJPKCjpob){DRhBhUYKFw = true;}
      if(LnSaRJMQgR == true){LnSaRJMQgR = false;}
      if(AjhlybtdhY == true){AjhlybtdhY = false;}
      if(dQqQIOAVOG == true){dQqQIOAVOG = false;}
      if(uMJdsIlmzG == true){uMJdsIlmzG = false;}
      if(RqitxNxWQh == true){RqitxNxWQh = false;}
      if(IFHPyuxCSD == true){IFHPyuxCSD = false;}
      if(JqCZVmaEsp == true){JqCZVmaEsp = false;}
      if(oGdbHlhwTt == true){oGdbHlhwTt = false;}
      if(QcEfypFsex == true){QcEfypFsex = false;}
      if(KjTwwaoIYJ == true){KjTwwaoIYJ = false;}
      if(mscarBafHL == true){mscarBafHL = false;}
      if(NBhYlflVaf == true){NBhYlflVaf = false;}
      if(hgYueFlheg == true){hgYueFlheg = false;}
      if(xYXKGXzdnx == true){xYXKGXzdnx = false;}
      if(OZkTjJBuKQ == true){OZkTjJBuKQ = false;}
      if(nSgrbFTgum == true){nSgrbFTgum = false;}
      if(OsAaNncXRO == true){OsAaNncXRO = false;}
      if(fIhdRIuFKV == true){fIhdRIuFKV = false;}
      if(DqWOsdrfhA == true){DqWOsdrfhA = false;}
      if(DRhBhUYKFw == true){DRhBhUYKFw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZBVJWSTBU
{ 
  void zhINiARnFd()
  { 
      bool OHOxliFdnP = false;
      bool bpWZuBtLBg = false;
      bool JCUgGszHbK = false;
      bool INbCCRobWB = false;
      bool RaaubJNmUT = false;
      bool mJJCDMlgqs = false;
      bool iyBcGNOTWd = false;
      bool LRnAOiaZFx = false;
      bool fMlHWyEYzp = false;
      bool fIkdRTYynN = false;
      bool tsPqIVUJmU = false;
      bool kLasMWLtFH = false;
      bool JpUfyDfKhu = false;
      bool KckrClwuzB = false;
      bool dtkeFTgrRt = false;
      bool IdrgDEYirE = false;
      bool oKarKHaipZ = false;
      bool aPtEdPEpae = false;
      bool VnsmlfkEny = false;
      bool NMDtMSSsUy = false;
      string KuFtNqoPnr;
      string gzqHjTuPHH;
      string KkEweBpflh;
      string sXRuunhEYR;
      string SSFcZEyolS;
      string zpkEzZqIPL;
      string BJcFzIhwMw;
      string lqqpnqeaWZ;
      string DAtShClMwV;
      string xYnMQJozdQ;
      string VBcpgIzuPH;
      string tPloIAPKXw;
      string WVApzMDeZd;
      string CfxFEBWDlZ;
      string DqwnagmzEP;
      string tebgtABlqU;
      string EUVkENSfkG;
      string dLYxseYLPR;
      string YDZJjXEPKD;
      string zjMQUhVKjM;
      if(KuFtNqoPnr == VBcpgIzuPH){OHOxliFdnP = true;}
      else if(VBcpgIzuPH == KuFtNqoPnr){tsPqIVUJmU = true;}
      if(gzqHjTuPHH == tPloIAPKXw){bpWZuBtLBg = true;}
      else if(tPloIAPKXw == gzqHjTuPHH){kLasMWLtFH = true;}
      if(KkEweBpflh == WVApzMDeZd){JCUgGszHbK = true;}
      else if(WVApzMDeZd == KkEweBpflh){JpUfyDfKhu = true;}
      if(sXRuunhEYR == CfxFEBWDlZ){INbCCRobWB = true;}
      else if(CfxFEBWDlZ == sXRuunhEYR){KckrClwuzB = true;}
      if(SSFcZEyolS == DqwnagmzEP){RaaubJNmUT = true;}
      else if(DqwnagmzEP == SSFcZEyolS){dtkeFTgrRt = true;}
      if(zpkEzZqIPL == tebgtABlqU){mJJCDMlgqs = true;}
      else if(tebgtABlqU == zpkEzZqIPL){IdrgDEYirE = true;}
      if(BJcFzIhwMw == EUVkENSfkG){iyBcGNOTWd = true;}
      else if(EUVkENSfkG == BJcFzIhwMw){oKarKHaipZ = true;}
      if(lqqpnqeaWZ == dLYxseYLPR){LRnAOiaZFx = true;}
      if(DAtShClMwV == YDZJjXEPKD){fMlHWyEYzp = true;}
      if(xYnMQJozdQ == zjMQUhVKjM){fIkdRTYynN = true;}
      while(dLYxseYLPR == lqqpnqeaWZ){aPtEdPEpae = true;}
      while(YDZJjXEPKD == YDZJjXEPKD){VnsmlfkEny = true;}
      while(zjMQUhVKjM == zjMQUhVKjM){NMDtMSSsUy = true;}
      if(OHOxliFdnP == true){OHOxliFdnP = false;}
      if(bpWZuBtLBg == true){bpWZuBtLBg = false;}
      if(JCUgGszHbK == true){JCUgGszHbK = false;}
      if(INbCCRobWB == true){INbCCRobWB = false;}
      if(RaaubJNmUT == true){RaaubJNmUT = false;}
      if(mJJCDMlgqs == true){mJJCDMlgqs = false;}
      if(iyBcGNOTWd == true){iyBcGNOTWd = false;}
      if(LRnAOiaZFx == true){LRnAOiaZFx = false;}
      if(fMlHWyEYzp == true){fMlHWyEYzp = false;}
      if(fIkdRTYynN == true){fIkdRTYynN = false;}
      if(tsPqIVUJmU == true){tsPqIVUJmU = false;}
      if(kLasMWLtFH == true){kLasMWLtFH = false;}
      if(JpUfyDfKhu == true){JpUfyDfKhu = false;}
      if(KckrClwuzB == true){KckrClwuzB = false;}
      if(dtkeFTgrRt == true){dtkeFTgrRt = false;}
      if(IdrgDEYirE == true){IdrgDEYirE = false;}
      if(oKarKHaipZ == true){oKarKHaipZ = false;}
      if(aPtEdPEpae == true){aPtEdPEpae = false;}
      if(VnsmlfkEny == true){VnsmlfkEny = false;}
      if(NMDtMSSsUy == true){NMDtMSSsUy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SBGSBQTYNH
{ 
  void ybZyqnMtrP()
  { 
      bool MPzShKfSYM = false;
      bool GhsxBKAaFw = false;
      bool BOOrEqZGko = false;
      bool lypzpPRNIa = false;
      bool AcMkgDqNll = false;
      bool SDdLbxBHOp = false;
      bool jZgiZIrsGk = false;
      bool rmRduXCcLA = false;
      bool zMTzWiTdXr = false;
      bool OKyRqZwdLY = false;
      bool LyGAsfkAPE = false;
      bool uXwNqWGgLq = false;
      bool nNUOWhnzmV = false;
      bool bXRmoAGSGq = false;
      bool xTOTxqNkaT = false;
      bool TORTjxcqdL = false;
      bool qkNtcWFJYp = false;
      bool QmaUsUyBRe = false;
      bool TDYSBMGyCq = false;
      bool XOouzMGUqZ = false;
      string TzqGdzRIOV;
      string wGCyGGAEBr;
      string MTXhbsirhI;
      string sWyAWHcQAI;
      string RQNQPEOBPU;
      string JYJzfAaIej;
      string QYaFbYHBay;
      string diErZwFHSX;
      string dgcMzUMzTV;
      string gTlPrroHop;
      string wMaRqZURYj;
      string uTpGGiwOGH;
      string MIhEQJxoAh;
      string HxSbaQGLUY;
      string zuajaNdeIJ;
      string uZAgdneVAg;
      string cfRqcxANeo;
      string bkshIQhxcD;
      string fRfplgwkym;
      string kkKmwSdiHc;
      if(TzqGdzRIOV == wMaRqZURYj){MPzShKfSYM = true;}
      else if(wMaRqZURYj == TzqGdzRIOV){LyGAsfkAPE = true;}
      if(wGCyGGAEBr == uTpGGiwOGH){GhsxBKAaFw = true;}
      else if(uTpGGiwOGH == wGCyGGAEBr){uXwNqWGgLq = true;}
      if(MTXhbsirhI == MIhEQJxoAh){BOOrEqZGko = true;}
      else if(MIhEQJxoAh == MTXhbsirhI){nNUOWhnzmV = true;}
      if(sWyAWHcQAI == HxSbaQGLUY){lypzpPRNIa = true;}
      else if(HxSbaQGLUY == sWyAWHcQAI){bXRmoAGSGq = true;}
      if(RQNQPEOBPU == zuajaNdeIJ){AcMkgDqNll = true;}
      else if(zuajaNdeIJ == RQNQPEOBPU){xTOTxqNkaT = true;}
      if(JYJzfAaIej == uZAgdneVAg){SDdLbxBHOp = true;}
      else if(uZAgdneVAg == JYJzfAaIej){TORTjxcqdL = true;}
      if(QYaFbYHBay == cfRqcxANeo){jZgiZIrsGk = true;}
      else if(cfRqcxANeo == QYaFbYHBay){qkNtcWFJYp = true;}
      if(diErZwFHSX == bkshIQhxcD){rmRduXCcLA = true;}
      if(dgcMzUMzTV == fRfplgwkym){zMTzWiTdXr = true;}
      if(gTlPrroHop == kkKmwSdiHc){OKyRqZwdLY = true;}
      while(bkshIQhxcD == diErZwFHSX){QmaUsUyBRe = true;}
      while(fRfplgwkym == fRfplgwkym){TDYSBMGyCq = true;}
      while(kkKmwSdiHc == kkKmwSdiHc){XOouzMGUqZ = true;}
      if(MPzShKfSYM == true){MPzShKfSYM = false;}
      if(GhsxBKAaFw == true){GhsxBKAaFw = false;}
      if(BOOrEqZGko == true){BOOrEqZGko = false;}
      if(lypzpPRNIa == true){lypzpPRNIa = false;}
      if(AcMkgDqNll == true){AcMkgDqNll = false;}
      if(SDdLbxBHOp == true){SDdLbxBHOp = false;}
      if(jZgiZIrsGk == true){jZgiZIrsGk = false;}
      if(rmRduXCcLA == true){rmRduXCcLA = false;}
      if(zMTzWiTdXr == true){zMTzWiTdXr = false;}
      if(OKyRqZwdLY == true){OKyRqZwdLY = false;}
      if(LyGAsfkAPE == true){LyGAsfkAPE = false;}
      if(uXwNqWGgLq == true){uXwNqWGgLq = false;}
      if(nNUOWhnzmV == true){nNUOWhnzmV = false;}
      if(bXRmoAGSGq == true){bXRmoAGSGq = false;}
      if(xTOTxqNkaT == true){xTOTxqNkaT = false;}
      if(TORTjxcqdL == true){TORTjxcqdL = false;}
      if(qkNtcWFJYp == true){qkNtcWFJYp = false;}
      if(QmaUsUyBRe == true){QmaUsUyBRe = false;}
      if(TDYSBMGyCq == true){TDYSBMGyCq = false;}
      if(XOouzMGUqZ == true){XOouzMGUqZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZOHLNIEXY
{ 
  void qRqiOipDuz()
  { 
      bool YZiMcpQRBA = false;
      bool FikgpNwJxQ = false;
      bool NhasEPjYTf = false;
      bool kuzbzPjspj = false;
      bool OSXCOKXuoY = false;
      bool zjWpbqzoIN = false;
      bool FqxVPKjIga = false;
      bool cDTNBuJXdt = false;
      bool rniufBYIAI = false;
      bool QukcdXUClE = false;
      bool ZOOOuwPIng = false;
      bool gaKNUQICoO = false;
      bool kbIYKhRpid = false;
      bool ZGkYTcZUAj = false;
      bool kPTTaojWHN = false;
      bool PSNXSyGoEM = false;
      bool dZZKGaoktq = false;
      bool qnBEdVHoyU = false;
      bool xtiVOHsNGV = false;
      bool WjPmFLpJMz = false;
      string PooTKtrTfA;
      string DPwMPxxVJN;
      string ZBQPtskDSl;
      string CgRkKQocKy;
      string lmsFCaKMJh;
      string TgKajOXZZQ;
      string JnBtyWyKCy;
      string IULLalHLNT;
      string iXskSUVqBu;
      string sPDsoylzHe;
      string czKKYyUzzx;
      string GMLFhluQac;
      string AGJGFsQRVc;
      string AIEhqiMhLT;
      string AVqDngDxLC;
      string CUXdeVoDFf;
      string gDcWwyHdOy;
      string YMEGcdPGSY;
      string oTGTZfjZDU;
      string tIcflwsTHp;
      if(PooTKtrTfA == czKKYyUzzx){YZiMcpQRBA = true;}
      else if(czKKYyUzzx == PooTKtrTfA){ZOOOuwPIng = true;}
      if(DPwMPxxVJN == GMLFhluQac){FikgpNwJxQ = true;}
      else if(GMLFhluQac == DPwMPxxVJN){gaKNUQICoO = true;}
      if(ZBQPtskDSl == AGJGFsQRVc){NhasEPjYTf = true;}
      else if(AGJGFsQRVc == ZBQPtskDSl){kbIYKhRpid = true;}
      if(CgRkKQocKy == AIEhqiMhLT){kuzbzPjspj = true;}
      else if(AIEhqiMhLT == CgRkKQocKy){ZGkYTcZUAj = true;}
      if(lmsFCaKMJh == AVqDngDxLC){OSXCOKXuoY = true;}
      else if(AVqDngDxLC == lmsFCaKMJh){kPTTaojWHN = true;}
      if(TgKajOXZZQ == CUXdeVoDFf){zjWpbqzoIN = true;}
      else if(CUXdeVoDFf == TgKajOXZZQ){PSNXSyGoEM = true;}
      if(JnBtyWyKCy == gDcWwyHdOy){FqxVPKjIga = true;}
      else if(gDcWwyHdOy == JnBtyWyKCy){dZZKGaoktq = true;}
      if(IULLalHLNT == YMEGcdPGSY){cDTNBuJXdt = true;}
      if(iXskSUVqBu == oTGTZfjZDU){rniufBYIAI = true;}
      if(sPDsoylzHe == tIcflwsTHp){QukcdXUClE = true;}
      while(YMEGcdPGSY == IULLalHLNT){qnBEdVHoyU = true;}
      while(oTGTZfjZDU == oTGTZfjZDU){xtiVOHsNGV = true;}
      while(tIcflwsTHp == tIcflwsTHp){WjPmFLpJMz = true;}
      if(YZiMcpQRBA == true){YZiMcpQRBA = false;}
      if(FikgpNwJxQ == true){FikgpNwJxQ = false;}
      if(NhasEPjYTf == true){NhasEPjYTf = false;}
      if(kuzbzPjspj == true){kuzbzPjspj = false;}
      if(OSXCOKXuoY == true){OSXCOKXuoY = false;}
      if(zjWpbqzoIN == true){zjWpbqzoIN = false;}
      if(FqxVPKjIga == true){FqxVPKjIga = false;}
      if(cDTNBuJXdt == true){cDTNBuJXdt = false;}
      if(rniufBYIAI == true){rniufBYIAI = false;}
      if(QukcdXUClE == true){QukcdXUClE = false;}
      if(ZOOOuwPIng == true){ZOOOuwPIng = false;}
      if(gaKNUQICoO == true){gaKNUQICoO = false;}
      if(kbIYKhRpid == true){kbIYKhRpid = false;}
      if(ZGkYTcZUAj == true){ZGkYTcZUAj = false;}
      if(kPTTaojWHN == true){kPTTaojWHN = false;}
      if(PSNXSyGoEM == true){PSNXSyGoEM = false;}
      if(dZZKGaoktq == true){dZZKGaoktq = false;}
      if(qnBEdVHoyU == true){qnBEdVHoyU = false;}
      if(xtiVOHsNGV == true){xtiVOHsNGV = false;}
      if(WjPmFLpJMz == true){WjPmFLpJMz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VATERNYWCR
{ 
  void imxJTzAjKO()
  { 
      bool ALFhzMVyIq = false;
      bool sbyZGLIHEz = false;
      bool EQEUgELYgI = false;
      bool ZJDUdNWjyM = false;
      bool GlKuoDlaNg = false;
      bool ptsAWiGkAt = false;
      bool BxQAQjXdur = false;
      bool nXJqsSGJec = false;
      bool SjKARfQCxu = false;
      bool HliDLIUJdF = false;
      bool eIfVrRjBHE = false;
      bool cxFWbQlPhk = false;
      bool SVgAkCoFfj = false;
      bool xweZyJEoHz = false;
      bool uPurRJfLbt = false;
      bool WEbslJbekp = false;
      bool ceUXGfReYR = false;
      bool MwHhoDZnha = false;
      bool VcdkMrUlno = false;
      bool hYERWQtXll = false;
      string VThqlgKzgN;
      string MHfdacjdOZ;
      string HiTglyXRwR;
      string WiVJBFAADS;
      string jJtmcUfjpm;
      string JMmRPlAAEn;
      string IsCOqdlWbU;
      string ciawoxnfER;
      string SmaJHKwDsO;
      string FzwPJqHfwz;
      string iIIUJakpbR;
      string xTwmVURrGf;
      string ghdNPclLly;
      string pIiEiJeFAg;
      string YFaaQkDJso;
      string YOYPSAetEf;
      string nZEdaojqDL;
      string oMrZHaGCwe;
      string ZcRxYbjSli;
      string ekATryBxzb;
      if(VThqlgKzgN == iIIUJakpbR){ALFhzMVyIq = true;}
      else if(iIIUJakpbR == VThqlgKzgN){eIfVrRjBHE = true;}
      if(MHfdacjdOZ == xTwmVURrGf){sbyZGLIHEz = true;}
      else if(xTwmVURrGf == MHfdacjdOZ){cxFWbQlPhk = true;}
      if(HiTglyXRwR == ghdNPclLly){EQEUgELYgI = true;}
      else if(ghdNPclLly == HiTglyXRwR){SVgAkCoFfj = true;}
      if(WiVJBFAADS == pIiEiJeFAg){ZJDUdNWjyM = true;}
      else if(pIiEiJeFAg == WiVJBFAADS){xweZyJEoHz = true;}
      if(jJtmcUfjpm == YFaaQkDJso){GlKuoDlaNg = true;}
      else if(YFaaQkDJso == jJtmcUfjpm){uPurRJfLbt = true;}
      if(JMmRPlAAEn == YOYPSAetEf){ptsAWiGkAt = true;}
      else if(YOYPSAetEf == JMmRPlAAEn){WEbslJbekp = true;}
      if(IsCOqdlWbU == nZEdaojqDL){BxQAQjXdur = true;}
      else if(nZEdaojqDL == IsCOqdlWbU){ceUXGfReYR = true;}
      if(ciawoxnfER == oMrZHaGCwe){nXJqsSGJec = true;}
      if(SmaJHKwDsO == ZcRxYbjSli){SjKARfQCxu = true;}
      if(FzwPJqHfwz == ekATryBxzb){HliDLIUJdF = true;}
      while(oMrZHaGCwe == ciawoxnfER){MwHhoDZnha = true;}
      while(ZcRxYbjSli == ZcRxYbjSli){VcdkMrUlno = true;}
      while(ekATryBxzb == ekATryBxzb){hYERWQtXll = true;}
      if(ALFhzMVyIq == true){ALFhzMVyIq = false;}
      if(sbyZGLIHEz == true){sbyZGLIHEz = false;}
      if(EQEUgELYgI == true){EQEUgELYgI = false;}
      if(ZJDUdNWjyM == true){ZJDUdNWjyM = false;}
      if(GlKuoDlaNg == true){GlKuoDlaNg = false;}
      if(ptsAWiGkAt == true){ptsAWiGkAt = false;}
      if(BxQAQjXdur == true){BxQAQjXdur = false;}
      if(nXJqsSGJec == true){nXJqsSGJec = false;}
      if(SjKARfQCxu == true){SjKARfQCxu = false;}
      if(HliDLIUJdF == true){HliDLIUJdF = false;}
      if(eIfVrRjBHE == true){eIfVrRjBHE = false;}
      if(cxFWbQlPhk == true){cxFWbQlPhk = false;}
      if(SVgAkCoFfj == true){SVgAkCoFfj = false;}
      if(xweZyJEoHz == true){xweZyJEoHz = false;}
      if(uPurRJfLbt == true){uPurRJfLbt = false;}
      if(WEbslJbekp == true){WEbslJbekp = false;}
      if(ceUXGfReYR == true){ceUXGfReYR = false;}
      if(MwHhoDZnha == true){MwHhoDZnha = false;}
      if(VcdkMrUlno == true){VcdkMrUlno = false;}
      if(hYERWQtXll == true){hYERWQtXll = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XUZIVVZPPH
{ 
  void cGeXMquSSI()
  { 
      bool eZqLEeyaFz = false;
      bool nPZkDzPSxW = false;
      bool cDNZHYIIWw = false;
      bool XIWCPuoCfM = false;
      bool hpchOOEabb = false;
      bool sTqQSbMQEf = false;
      bool VoDIbfrXUH = false;
      bool JMmkomZfLs = false;
      bool ThguCDQGin = false;
      bool iXyAprlUGh = false;
      bool VgFTRggGbf = false;
      bool BfFKLnHIFY = false;
      bool OlngYkOmuw = false;
      bool AFZcWmcNdV = false;
      bool VKeCmCRmnB = false;
      bool jdOgSjrYtf = false;
      bool SsLeewGcnX = false;
      bool LtejCEHktW = false;
      bool SaysMWqrJl = false;
      bool tDSxDcyzXq = false;
      string uHCZOXnAwy;
      string cdEClFsZoQ;
      string qobIDjAnmE;
      string ZnrkicEHUj;
      string MrUcCzyiCS;
      string RuAiVFetVd;
      string XzNqXokSTJ;
      string BlEEDyTzFD;
      string kRlUmemJPc;
      string xKlqMNedEM;
      string OeOsQfqueW;
      string kfnRrFNrEs;
      string CbDpMqAMrp;
      string TptroFCsEG;
      string mqdrqQVTyH;
      string zmYLKlbYgY;
      string fdDnDulucl;
      string CUnyFKyLyu;
      string VfOjqfRihC;
      string ddLeaJmonw;
      if(uHCZOXnAwy == OeOsQfqueW){eZqLEeyaFz = true;}
      else if(OeOsQfqueW == uHCZOXnAwy){VgFTRggGbf = true;}
      if(cdEClFsZoQ == kfnRrFNrEs){nPZkDzPSxW = true;}
      else if(kfnRrFNrEs == cdEClFsZoQ){BfFKLnHIFY = true;}
      if(qobIDjAnmE == CbDpMqAMrp){cDNZHYIIWw = true;}
      else if(CbDpMqAMrp == qobIDjAnmE){OlngYkOmuw = true;}
      if(ZnrkicEHUj == TptroFCsEG){XIWCPuoCfM = true;}
      else if(TptroFCsEG == ZnrkicEHUj){AFZcWmcNdV = true;}
      if(MrUcCzyiCS == mqdrqQVTyH){hpchOOEabb = true;}
      else if(mqdrqQVTyH == MrUcCzyiCS){VKeCmCRmnB = true;}
      if(RuAiVFetVd == zmYLKlbYgY){sTqQSbMQEf = true;}
      else if(zmYLKlbYgY == RuAiVFetVd){jdOgSjrYtf = true;}
      if(XzNqXokSTJ == fdDnDulucl){VoDIbfrXUH = true;}
      else if(fdDnDulucl == XzNqXokSTJ){SsLeewGcnX = true;}
      if(BlEEDyTzFD == CUnyFKyLyu){JMmkomZfLs = true;}
      if(kRlUmemJPc == VfOjqfRihC){ThguCDQGin = true;}
      if(xKlqMNedEM == ddLeaJmonw){iXyAprlUGh = true;}
      while(CUnyFKyLyu == BlEEDyTzFD){LtejCEHktW = true;}
      while(VfOjqfRihC == VfOjqfRihC){SaysMWqrJl = true;}
      while(ddLeaJmonw == ddLeaJmonw){tDSxDcyzXq = true;}
      if(eZqLEeyaFz == true){eZqLEeyaFz = false;}
      if(nPZkDzPSxW == true){nPZkDzPSxW = false;}
      if(cDNZHYIIWw == true){cDNZHYIIWw = false;}
      if(XIWCPuoCfM == true){XIWCPuoCfM = false;}
      if(hpchOOEabb == true){hpchOOEabb = false;}
      if(sTqQSbMQEf == true){sTqQSbMQEf = false;}
      if(VoDIbfrXUH == true){VoDIbfrXUH = false;}
      if(JMmkomZfLs == true){JMmkomZfLs = false;}
      if(ThguCDQGin == true){ThguCDQGin = false;}
      if(iXyAprlUGh == true){iXyAprlUGh = false;}
      if(VgFTRggGbf == true){VgFTRggGbf = false;}
      if(BfFKLnHIFY == true){BfFKLnHIFY = false;}
      if(OlngYkOmuw == true){OlngYkOmuw = false;}
      if(AFZcWmcNdV == true){AFZcWmcNdV = false;}
      if(VKeCmCRmnB == true){VKeCmCRmnB = false;}
      if(jdOgSjrYtf == true){jdOgSjrYtf = false;}
      if(SsLeewGcnX == true){SsLeewGcnX = false;}
      if(LtejCEHktW == true){LtejCEHktW = false;}
      if(SaysMWqrJl == true){SaysMWqrJl = false;}
      if(tDSxDcyzXq == true){tDSxDcyzXq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKGVKTGAET
{ 
  void GgQlyYAaIC()
  { 
      bool RljzlOAMJd = false;
      bool ZRhDwhxCdK = false;
      bool SVfVnIQQBk = false;
      bool RuhOMSYsor = false;
      bool jIFpAMbRFs = false;
      bool YCzHwuGOLd = false;
      bool yiLXMeiTpd = false;
      bool JEMlaKQoUb = false;
      bool gzLHMOuaRR = false;
      bool LJgLtAwgdV = false;
      bool cHabiUoNfl = false;
      bool dRsjwyXDLx = false;
      bool iICYRAWBqZ = false;
      bool NjKyyYXiYr = false;
      bool ZhtemtPxOu = false;
      bool crUgmUEBKi = false;
      bool xmWFXtGukW = false;
      bool ZoeTXBNWkX = false;
      bool jYmuxUOdLd = false;
      bool UWYptlKoHs = false;
      string ifXwcMsNcy;
      string XDZrIGoYdy;
      string DjsbHiDjse;
      string NbDBEHEsdD;
      string zKkYBqEjQu;
      string cxjrqzlwnt;
      string IIUykwAXnB;
      string BuuZysyUZQ;
      string dSSxBPrKKF;
      string UIEitppmmF;
      string pfwPthCJtx;
      string ARVXQpoWwV;
      string EpNigrpLfH;
      string DLgUaxWDDT;
      string NhQMECmgSE;
      string ASpRAzSMhB;
      string qpcltnkAwS;
      string SlScHVZAdd;
      string FIsaHjVOUa;
      string eKUCbWEdRP;
      if(ifXwcMsNcy == pfwPthCJtx){RljzlOAMJd = true;}
      else if(pfwPthCJtx == ifXwcMsNcy){cHabiUoNfl = true;}
      if(XDZrIGoYdy == ARVXQpoWwV){ZRhDwhxCdK = true;}
      else if(ARVXQpoWwV == XDZrIGoYdy){dRsjwyXDLx = true;}
      if(DjsbHiDjse == EpNigrpLfH){SVfVnIQQBk = true;}
      else if(EpNigrpLfH == DjsbHiDjse){iICYRAWBqZ = true;}
      if(NbDBEHEsdD == DLgUaxWDDT){RuhOMSYsor = true;}
      else if(DLgUaxWDDT == NbDBEHEsdD){NjKyyYXiYr = true;}
      if(zKkYBqEjQu == NhQMECmgSE){jIFpAMbRFs = true;}
      else if(NhQMECmgSE == zKkYBqEjQu){ZhtemtPxOu = true;}
      if(cxjrqzlwnt == ASpRAzSMhB){YCzHwuGOLd = true;}
      else if(ASpRAzSMhB == cxjrqzlwnt){crUgmUEBKi = true;}
      if(IIUykwAXnB == qpcltnkAwS){yiLXMeiTpd = true;}
      else if(qpcltnkAwS == IIUykwAXnB){xmWFXtGukW = true;}
      if(BuuZysyUZQ == SlScHVZAdd){JEMlaKQoUb = true;}
      if(dSSxBPrKKF == FIsaHjVOUa){gzLHMOuaRR = true;}
      if(UIEitppmmF == eKUCbWEdRP){LJgLtAwgdV = true;}
      while(SlScHVZAdd == BuuZysyUZQ){ZoeTXBNWkX = true;}
      while(FIsaHjVOUa == FIsaHjVOUa){jYmuxUOdLd = true;}
      while(eKUCbWEdRP == eKUCbWEdRP){UWYptlKoHs = true;}
      if(RljzlOAMJd == true){RljzlOAMJd = false;}
      if(ZRhDwhxCdK == true){ZRhDwhxCdK = false;}
      if(SVfVnIQQBk == true){SVfVnIQQBk = false;}
      if(RuhOMSYsor == true){RuhOMSYsor = false;}
      if(jIFpAMbRFs == true){jIFpAMbRFs = false;}
      if(YCzHwuGOLd == true){YCzHwuGOLd = false;}
      if(yiLXMeiTpd == true){yiLXMeiTpd = false;}
      if(JEMlaKQoUb == true){JEMlaKQoUb = false;}
      if(gzLHMOuaRR == true){gzLHMOuaRR = false;}
      if(LJgLtAwgdV == true){LJgLtAwgdV = false;}
      if(cHabiUoNfl == true){cHabiUoNfl = false;}
      if(dRsjwyXDLx == true){dRsjwyXDLx = false;}
      if(iICYRAWBqZ == true){iICYRAWBqZ = false;}
      if(NjKyyYXiYr == true){NjKyyYXiYr = false;}
      if(ZhtemtPxOu == true){ZhtemtPxOu = false;}
      if(crUgmUEBKi == true){crUgmUEBKi = false;}
      if(xmWFXtGukW == true){xmWFXtGukW = false;}
      if(ZoeTXBNWkX == true){ZoeTXBNWkX = false;}
      if(jYmuxUOdLd == true){jYmuxUOdLd = false;}
      if(UWYptlKoHs == true){UWYptlKoHs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGVTIOFBAZ
{ 
  void yOeOzrmUgm()
  { 
      bool bJoyjpBBSu = false;
      bool extMnAYCLo = false;
      bool zSJAjAshAh = false;
      bool htlhackGup = false;
      bool jzLkKKRmoB = false;
      bool EaoXqIzoNj = false;
      bool wTAkMjLLlL = false;
      bool ORGUEzHYoY = false;
      bool iFrzdHENqR = false;
      bool cwsLtQyZYZ = false;
      bool yFBcllTTSq = false;
      bool BaznBpbAHF = false;
      bool fxUThRYuan = false;
      bool BgAPacEONq = false;
      bool mktzQCxEKD = false;
      bool oxSStBkhtT = false;
      bool NYsepUZiNX = false;
      bool lMmPRuCVDf = false;
      bool UUkXyDOgUY = false;
      bool qVTsdOrPIu = false;
      string wFghGQabYj;
      string waWrqkSCUe;
      string qHxmtXIGsj;
      string lDeUilWZUA;
      string QNVsWNkrxb;
      string aGfYFoIsmi;
      string IUinxswCJF;
      string OsgUNdkDQg;
      string mPJRJfWFPs;
      string ccllqwdhuc;
      string QiirMhYLKa;
      string DEcGwsLQdR;
      string WpmPblGucR;
      string zDHmPDfQEb;
      string GLtnpYzfpx;
      string jNDdGawTQa;
      string adhsazwppr;
      string MtLCKLuyYD;
      string laEfglAdfo;
      string HMAdBccBMp;
      if(wFghGQabYj == QiirMhYLKa){bJoyjpBBSu = true;}
      else if(QiirMhYLKa == wFghGQabYj){yFBcllTTSq = true;}
      if(waWrqkSCUe == DEcGwsLQdR){extMnAYCLo = true;}
      else if(DEcGwsLQdR == waWrqkSCUe){BaznBpbAHF = true;}
      if(qHxmtXIGsj == WpmPblGucR){zSJAjAshAh = true;}
      else if(WpmPblGucR == qHxmtXIGsj){fxUThRYuan = true;}
      if(lDeUilWZUA == zDHmPDfQEb){htlhackGup = true;}
      else if(zDHmPDfQEb == lDeUilWZUA){BgAPacEONq = true;}
      if(QNVsWNkrxb == GLtnpYzfpx){jzLkKKRmoB = true;}
      else if(GLtnpYzfpx == QNVsWNkrxb){mktzQCxEKD = true;}
      if(aGfYFoIsmi == jNDdGawTQa){EaoXqIzoNj = true;}
      else if(jNDdGawTQa == aGfYFoIsmi){oxSStBkhtT = true;}
      if(IUinxswCJF == adhsazwppr){wTAkMjLLlL = true;}
      else if(adhsazwppr == IUinxswCJF){NYsepUZiNX = true;}
      if(OsgUNdkDQg == MtLCKLuyYD){ORGUEzHYoY = true;}
      if(mPJRJfWFPs == laEfglAdfo){iFrzdHENqR = true;}
      if(ccllqwdhuc == HMAdBccBMp){cwsLtQyZYZ = true;}
      while(MtLCKLuyYD == OsgUNdkDQg){lMmPRuCVDf = true;}
      while(laEfglAdfo == laEfglAdfo){UUkXyDOgUY = true;}
      while(HMAdBccBMp == HMAdBccBMp){qVTsdOrPIu = true;}
      if(bJoyjpBBSu == true){bJoyjpBBSu = false;}
      if(extMnAYCLo == true){extMnAYCLo = false;}
      if(zSJAjAshAh == true){zSJAjAshAh = false;}
      if(htlhackGup == true){htlhackGup = false;}
      if(jzLkKKRmoB == true){jzLkKKRmoB = false;}
      if(EaoXqIzoNj == true){EaoXqIzoNj = false;}
      if(wTAkMjLLlL == true){wTAkMjLLlL = false;}
      if(ORGUEzHYoY == true){ORGUEzHYoY = false;}
      if(iFrzdHENqR == true){iFrzdHENqR = false;}
      if(cwsLtQyZYZ == true){cwsLtQyZYZ = false;}
      if(yFBcllTTSq == true){yFBcllTTSq = false;}
      if(BaznBpbAHF == true){BaznBpbAHF = false;}
      if(fxUThRYuan == true){fxUThRYuan = false;}
      if(BgAPacEONq == true){BgAPacEONq = false;}
      if(mktzQCxEKD == true){mktzQCxEKD = false;}
      if(oxSStBkhtT == true){oxSStBkhtT = false;}
      if(NYsepUZiNX == true){NYsepUZiNX = false;}
      if(lMmPRuCVDf == true){lMmPRuCVDf = false;}
      if(UUkXyDOgUY == true){UUkXyDOgUY = false;}
      if(qVTsdOrPIu == true){qVTsdOrPIu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHVJWCUHIQ
{ 
  void TDOdwpZZNJ()
  { 
      bool TTGAfbFEXs = false;
      bool cdJCcUAfzm = false;
      bool McyFmZDznI = false;
      bool FFZJUPRWJd = false;
      bool NPDeiOzoml = false;
      bool mJfITqVBNF = false;
      bool XGQPnXDzgN = false;
      bool CcVVYxZSVX = false;
      bool ZOLBVwZRpd = false;
      bool tQJDFHynqL = false;
      bool KAIYiJmKiV = false;
      bool QCfoeJtOsr = false;
      bool xlIDTlTSPR = false;
      bool ylbJMZGmSM = false;
      bool IPhUMqkTXw = false;
      bool NjtzOYqEFx = false;
      bool pUtRWeZVcF = false;
      bool DHwfihEnpb = false;
      bool AztTENqcun = false;
      bool iBgUWnUPxh = false;
      string IWoCziMJrX;
      string YhFkoWuKeO;
      string PwwwsHcnDD;
      string beomWAUcyP;
      string eQiXndpQwo;
      string KnrUrLZrJq;
      string FYFousrSNo;
      string CRLPjyMYHO;
      string QMqOsnmUuL;
      string ZbTHJFLtbt;
      string lXCGlrbbjs;
      string yBktZsgquH;
      string GWXCOayEGd;
      string mSwNbsJkbA;
      string LLkBMYqYgP;
      string YTyUnOAArL;
      string tXVFFfEWRf;
      string jwOtwulVpo;
      string iYXpFSTbYM;
      string sJrPGmofuf;
      if(IWoCziMJrX == lXCGlrbbjs){TTGAfbFEXs = true;}
      else if(lXCGlrbbjs == IWoCziMJrX){KAIYiJmKiV = true;}
      if(YhFkoWuKeO == yBktZsgquH){cdJCcUAfzm = true;}
      else if(yBktZsgquH == YhFkoWuKeO){QCfoeJtOsr = true;}
      if(PwwwsHcnDD == GWXCOayEGd){McyFmZDznI = true;}
      else if(GWXCOayEGd == PwwwsHcnDD){xlIDTlTSPR = true;}
      if(beomWAUcyP == mSwNbsJkbA){FFZJUPRWJd = true;}
      else if(mSwNbsJkbA == beomWAUcyP){ylbJMZGmSM = true;}
      if(eQiXndpQwo == LLkBMYqYgP){NPDeiOzoml = true;}
      else if(LLkBMYqYgP == eQiXndpQwo){IPhUMqkTXw = true;}
      if(KnrUrLZrJq == YTyUnOAArL){mJfITqVBNF = true;}
      else if(YTyUnOAArL == KnrUrLZrJq){NjtzOYqEFx = true;}
      if(FYFousrSNo == tXVFFfEWRf){XGQPnXDzgN = true;}
      else if(tXVFFfEWRf == FYFousrSNo){pUtRWeZVcF = true;}
      if(CRLPjyMYHO == jwOtwulVpo){CcVVYxZSVX = true;}
      if(QMqOsnmUuL == iYXpFSTbYM){ZOLBVwZRpd = true;}
      if(ZbTHJFLtbt == sJrPGmofuf){tQJDFHynqL = true;}
      while(jwOtwulVpo == CRLPjyMYHO){DHwfihEnpb = true;}
      while(iYXpFSTbYM == iYXpFSTbYM){AztTENqcun = true;}
      while(sJrPGmofuf == sJrPGmofuf){iBgUWnUPxh = true;}
      if(TTGAfbFEXs == true){TTGAfbFEXs = false;}
      if(cdJCcUAfzm == true){cdJCcUAfzm = false;}
      if(McyFmZDznI == true){McyFmZDznI = false;}
      if(FFZJUPRWJd == true){FFZJUPRWJd = false;}
      if(NPDeiOzoml == true){NPDeiOzoml = false;}
      if(mJfITqVBNF == true){mJfITqVBNF = false;}
      if(XGQPnXDzgN == true){XGQPnXDzgN = false;}
      if(CcVVYxZSVX == true){CcVVYxZSVX = false;}
      if(ZOLBVwZRpd == true){ZOLBVwZRpd = false;}
      if(tQJDFHynqL == true){tQJDFHynqL = false;}
      if(KAIYiJmKiV == true){KAIYiJmKiV = false;}
      if(QCfoeJtOsr == true){QCfoeJtOsr = false;}
      if(xlIDTlTSPR == true){xlIDTlTSPR = false;}
      if(ylbJMZGmSM == true){ylbJMZGmSM = false;}
      if(IPhUMqkTXw == true){IPhUMqkTXw = false;}
      if(NjtzOYqEFx == true){NjtzOYqEFx = false;}
      if(pUtRWeZVcF == true){pUtRWeZVcF = false;}
      if(DHwfihEnpb == true){DHwfihEnpb = false;}
      if(AztTENqcun == true){AztTENqcun = false;}
      if(iBgUWnUPxh == true){iBgUWnUPxh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNZKNURRAX
{ 
  void IBoZelQYlo()
  { 
      bool foqsUPjLrM = false;
      bool XEKXRjKGds = false;
      bool eyaWouLxum = false;
      bool wHMOTucMRQ = false;
      bool PGnAGCbQge = false;
      bool ZIlInhOUEY = false;
      bool ElPFPQquEV = false;
      bool GynNdYKZQl = false;
      bool TtPQMnUDak = false;
      bool gIIsMdphko = false;
      bool KfMLXbTYeO = false;
      bool WnERFJWzrb = false;
      bool umUSoypuBz = false;
      bool hboaamhErj = false;
      bool TwYLOsEpnC = false;
      bool GppIsXLsVZ = false;
      bool lXXegtycpR = false;
      bool bSGHIyOJEw = false;
      bool tzHysqlfhD = false;
      bool anhSyuYsdT = false;
      string zmjoBxuVNP;
      string nusnIczrER;
      string HSTfsXOiEr;
      string bdPJkHIQmy;
      string qwYdCYQskk;
      string DPnhlgSEuc;
      string hMRVmJejDB;
      string TiEFaLsodT;
      string HUyToMpgWE;
      string oEUKPeeDqr;
      string sgpjRTKhGa;
      string mcZbVMOyfZ;
      string TyMyLOOtow;
      string foxlZadNBU;
      string BHawQLdsnD;
      string QfWQXuTrXC;
      string FQrKtxenBu;
      string hAwLYLXPhA;
      string kUFlfASfNd;
      string GlozPkOPCS;
      if(zmjoBxuVNP == sgpjRTKhGa){foqsUPjLrM = true;}
      else if(sgpjRTKhGa == zmjoBxuVNP){KfMLXbTYeO = true;}
      if(nusnIczrER == mcZbVMOyfZ){XEKXRjKGds = true;}
      else if(mcZbVMOyfZ == nusnIczrER){WnERFJWzrb = true;}
      if(HSTfsXOiEr == TyMyLOOtow){eyaWouLxum = true;}
      else if(TyMyLOOtow == HSTfsXOiEr){umUSoypuBz = true;}
      if(bdPJkHIQmy == foxlZadNBU){wHMOTucMRQ = true;}
      else if(foxlZadNBU == bdPJkHIQmy){hboaamhErj = true;}
      if(qwYdCYQskk == BHawQLdsnD){PGnAGCbQge = true;}
      else if(BHawQLdsnD == qwYdCYQskk){TwYLOsEpnC = true;}
      if(DPnhlgSEuc == QfWQXuTrXC){ZIlInhOUEY = true;}
      else if(QfWQXuTrXC == DPnhlgSEuc){GppIsXLsVZ = true;}
      if(hMRVmJejDB == FQrKtxenBu){ElPFPQquEV = true;}
      else if(FQrKtxenBu == hMRVmJejDB){lXXegtycpR = true;}
      if(TiEFaLsodT == hAwLYLXPhA){GynNdYKZQl = true;}
      if(HUyToMpgWE == kUFlfASfNd){TtPQMnUDak = true;}
      if(oEUKPeeDqr == GlozPkOPCS){gIIsMdphko = true;}
      while(hAwLYLXPhA == TiEFaLsodT){bSGHIyOJEw = true;}
      while(kUFlfASfNd == kUFlfASfNd){tzHysqlfhD = true;}
      while(GlozPkOPCS == GlozPkOPCS){anhSyuYsdT = true;}
      if(foqsUPjLrM == true){foqsUPjLrM = false;}
      if(XEKXRjKGds == true){XEKXRjKGds = false;}
      if(eyaWouLxum == true){eyaWouLxum = false;}
      if(wHMOTucMRQ == true){wHMOTucMRQ = false;}
      if(PGnAGCbQge == true){PGnAGCbQge = false;}
      if(ZIlInhOUEY == true){ZIlInhOUEY = false;}
      if(ElPFPQquEV == true){ElPFPQquEV = false;}
      if(GynNdYKZQl == true){GynNdYKZQl = false;}
      if(TtPQMnUDak == true){TtPQMnUDak = false;}
      if(gIIsMdphko == true){gIIsMdphko = false;}
      if(KfMLXbTYeO == true){KfMLXbTYeO = false;}
      if(WnERFJWzrb == true){WnERFJWzrb = false;}
      if(umUSoypuBz == true){umUSoypuBz = false;}
      if(hboaamhErj == true){hboaamhErj = false;}
      if(TwYLOsEpnC == true){TwYLOsEpnC = false;}
      if(GppIsXLsVZ == true){GppIsXLsVZ = false;}
      if(lXXegtycpR == true){lXXegtycpR = false;}
      if(bSGHIyOJEw == true){bSGHIyOJEw = false;}
      if(tzHysqlfhD == true){tzHysqlfhD = false;}
      if(anhSyuYsdT == true){anhSyuYsdT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPXEYWHVRL
{ 
  void ytGMlOAxNN()
  { 
      bool ieOSTDjzwz = false;
      bool htMQScKxyu = false;
      bool nGdBPmNtLw = false;
      bool kjaYJGfjhw = false;
      bool MosPSyVtXx = false;
      bool dDAOhbBMDf = false;
      bool opnzNySnHM = false;
      bool xZOBhzMNiQ = false;
      bool RTVNRhiMpg = false;
      bool FTgBHWBsBT = false;
      bool fgmKAEnzgi = false;
      bool OmclOVTZhf = false;
      bool PGxZHcrNtK = false;
      bool ySLPkjfKNM = false;
      bool sjfHSRqumk = false;
      bool CaLVDYjNDX = false;
      bool LaFVkubMAd = false;
      bool oJMUlfZoGp = false;
      bool lxZIHWHoLM = false;
      bool ASHpBSdJWW = false;
      string xDxzhrwkpN;
      string yzqCdOWUtK;
      string LttbOKpDwT;
      string dWuqFHnWfC;
      string NquDBzSyCn;
      string jhgXeDJVjX;
      string CsoVibDAwV;
      string aznqxTzpaO;
      string qqAIjwoXMC;
      string ySmIAUBYTY;
      string wSBgMjsoaK;
      string DStVgKrglm;
      string lemtXIMeqb;
      string RaVBRXoTuz;
      string CzxCzeXRbo;
      string bUlglQeHIE;
      string XNyyrcwsDI;
      string VYkmjlhkur;
      string ktDBAxnoPB;
      string rhKqanAyJV;
      if(xDxzhrwkpN == wSBgMjsoaK){ieOSTDjzwz = true;}
      else if(wSBgMjsoaK == xDxzhrwkpN){fgmKAEnzgi = true;}
      if(yzqCdOWUtK == DStVgKrglm){htMQScKxyu = true;}
      else if(DStVgKrglm == yzqCdOWUtK){OmclOVTZhf = true;}
      if(LttbOKpDwT == lemtXIMeqb){nGdBPmNtLw = true;}
      else if(lemtXIMeqb == LttbOKpDwT){PGxZHcrNtK = true;}
      if(dWuqFHnWfC == RaVBRXoTuz){kjaYJGfjhw = true;}
      else if(RaVBRXoTuz == dWuqFHnWfC){ySLPkjfKNM = true;}
      if(NquDBzSyCn == CzxCzeXRbo){MosPSyVtXx = true;}
      else if(CzxCzeXRbo == NquDBzSyCn){sjfHSRqumk = true;}
      if(jhgXeDJVjX == bUlglQeHIE){dDAOhbBMDf = true;}
      else if(bUlglQeHIE == jhgXeDJVjX){CaLVDYjNDX = true;}
      if(CsoVibDAwV == XNyyrcwsDI){opnzNySnHM = true;}
      else if(XNyyrcwsDI == CsoVibDAwV){LaFVkubMAd = true;}
      if(aznqxTzpaO == VYkmjlhkur){xZOBhzMNiQ = true;}
      if(qqAIjwoXMC == ktDBAxnoPB){RTVNRhiMpg = true;}
      if(ySmIAUBYTY == rhKqanAyJV){FTgBHWBsBT = true;}
      while(VYkmjlhkur == aznqxTzpaO){oJMUlfZoGp = true;}
      while(ktDBAxnoPB == ktDBAxnoPB){lxZIHWHoLM = true;}
      while(rhKqanAyJV == rhKqanAyJV){ASHpBSdJWW = true;}
      if(ieOSTDjzwz == true){ieOSTDjzwz = false;}
      if(htMQScKxyu == true){htMQScKxyu = false;}
      if(nGdBPmNtLw == true){nGdBPmNtLw = false;}
      if(kjaYJGfjhw == true){kjaYJGfjhw = false;}
      if(MosPSyVtXx == true){MosPSyVtXx = false;}
      if(dDAOhbBMDf == true){dDAOhbBMDf = false;}
      if(opnzNySnHM == true){opnzNySnHM = false;}
      if(xZOBhzMNiQ == true){xZOBhzMNiQ = false;}
      if(RTVNRhiMpg == true){RTVNRhiMpg = false;}
      if(FTgBHWBsBT == true){FTgBHWBsBT = false;}
      if(fgmKAEnzgi == true){fgmKAEnzgi = false;}
      if(OmclOVTZhf == true){OmclOVTZhf = false;}
      if(PGxZHcrNtK == true){PGxZHcrNtK = false;}
      if(ySLPkjfKNM == true){ySLPkjfKNM = false;}
      if(sjfHSRqumk == true){sjfHSRqumk = false;}
      if(CaLVDYjNDX == true){CaLVDYjNDX = false;}
      if(LaFVkubMAd == true){LaFVkubMAd = false;}
      if(oJMUlfZoGp == true){oJMUlfZoGp = false;}
      if(lxZIHWHoLM == true){lxZIHWHoLM = false;}
      if(ASHpBSdJWW == true){ASHpBSdJWW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPMKHCGDZB
{ 
  void FuVMNqnzPy()
  { 
      bool UDFTGipyeK = false;
      bool ywMFPdcmSt = false;
      bool GtXtbCuEKJ = false;
      bool PlfkzoxELD = false;
      bool YBbHIZDdYV = false;
      bool PyYUXafLrE = false;
      bool nlnUuLQbGZ = false;
      bool gXaPUERQlB = false;
      bool zQensRNKNX = false;
      bool JlMHOmNGMw = false;
      bool JbXyoqXJAS = false;
      bool IOYpFWHzac = false;
      bool yGNhQtKSAh = false;
      bool qLDorXsfyC = false;
      bool tEJuPtNVCr = false;
      bool eNeiyCNoht = false;
      bool fEISaxKiyg = false;
      bool daAYitwSSV = false;
      bool goQICcfUqo = false;
      bool JExEVouqTR = false;
      string KdZBaoMblm;
      string BtQiPXRpzY;
      string ggZVbmFusS;
      string DTNPeNUQSU;
      string UIVLllMhTz;
      string rPcKgcDEZm;
      string iQiSihfBEB;
      string DAWdEYLOio;
      string ZWbsZmpDhC;
      string KPqfkDYCbE;
      string FLdRwqsyFI;
      string QnVjNLopsu;
      string rcTBqmJqsA;
      string zJmejOsKxh;
      string tqxYlWtGSZ;
      string NiIfLcqcZI;
      string hBFFJHBpAy;
      string SerKBBeuPU;
      string sDYSlPAGSG;
      string WPjnArkrOd;
      if(KdZBaoMblm == FLdRwqsyFI){UDFTGipyeK = true;}
      else if(FLdRwqsyFI == KdZBaoMblm){JbXyoqXJAS = true;}
      if(BtQiPXRpzY == QnVjNLopsu){ywMFPdcmSt = true;}
      else if(QnVjNLopsu == BtQiPXRpzY){IOYpFWHzac = true;}
      if(ggZVbmFusS == rcTBqmJqsA){GtXtbCuEKJ = true;}
      else if(rcTBqmJqsA == ggZVbmFusS){yGNhQtKSAh = true;}
      if(DTNPeNUQSU == zJmejOsKxh){PlfkzoxELD = true;}
      else if(zJmejOsKxh == DTNPeNUQSU){qLDorXsfyC = true;}
      if(UIVLllMhTz == tqxYlWtGSZ){YBbHIZDdYV = true;}
      else if(tqxYlWtGSZ == UIVLllMhTz){tEJuPtNVCr = true;}
      if(rPcKgcDEZm == NiIfLcqcZI){PyYUXafLrE = true;}
      else if(NiIfLcqcZI == rPcKgcDEZm){eNeiyCNoht = true;}
      if(iQiSihfBEB == hBFFJHBpAy){nlnUuLQbGZ = true;}
      else if(hBFFJHBpAy == iQiSihfBEB){fEISaxKiyg = true;}
      if(DAWdEYLOio == SerKBBeuPU){gXaPUERQlB = true;}
      if(ZWbsZmpDhC == sDYSlPAGSG){zQensRNKNX = true;}
      if(KPqfkDYCbE == WPjnArkrOd){JlMHOmNGMw = true;}
      while(SerKBBeuPU == DAWdEYLOio){daAYitwSSV = true;}
      while(sDYSlPAGSG == sDYSlPAGSG){goQICcfUqo = true;}
      while(WPjnArkrOd == WPjnArkrOd){JExEVouqTR = true;}
      if(UDFTGipyeK == true){UDFTGipyeK = false;}
      if(ywMFPdcmSt == true){ywMFPdcmSt = false;}
      if(GtXtbCuEKJ == true){GtXtbCuEKJ = false;}
      if(PlfkzoxELD == true){PlfkzoxELD = false;}
      if(YBbHIZDdYV == true){YBbHIZDdYV = false;}
      if(PyYUXafLrE == true){PyYUXafLrE = false;}
      if(nlnUuLQbGZ == true){nlnUuLQbGZ = false;}
      if(gXaPUERQlB == true){gXaPUERQlB = false;}
      if(zQensRNKNX == true){zQensRNKNX = false;}
      if(JlMHOmNGMw == true){JlMHOmNGMw = false;}
      if(JbXyoqXJAS == true){JbXyoqXJAS = false;}
      if(IOYpFWHzac == true){IOYpFWHzac = false;}
      if(yGNhQtKSAh == true){yGNhQtKSAh = false;}
      if(qLDorXsfyC == true){qLDorXsfyC = false;}
      if(tEJuPtNVCr == true){tEJuPtNVCr = false;}
      if(eNeiyCNoht == true){eNeiyCNoht = false;}
      if(fEISaxKiyg == true){fEISaxKiyg = false;}
      if(daAYitwSSV == true){daAYitwSSV = false;}
      if(goQICcfUqo == true){goQICcfUqo = false;}
      if(JExEVouqTR == true){JExEVouqTR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBSTZODCQR
{ 
  void eJlNyqdAlI()
  { 
      bool UMcGzxVdxw = false;
      bool jRUBDEZGPD = false;
      bool botJpwbieF = false;
      bool lLsVeAOmZd = false;
      bool HflrPZdfrB = false;
      bool orIMVfSSQC = false;
      bool UmzrKXYyVD = false;
      bool omflwuCBtP = false;
      bool RwpcQsDfAz = false;
      bool gwWWIUgtgq = false;
      bool AfJoMBLWQZ = false;
      bool cQXAkYwVbQ = false;
      bool UryWVsQJca = false;
      bool OIUCPlmBQO = false;
      bool hfPZWQXVlj = false;
      bool XLRQWHhmST = false;
      bool kCsoLTuVjz = false;
      bool kuENincXAE = false;
      bool UtXsDDqEfH = false;
      bool DAhxcfmaOC = false;
      string mYfeEqetKp;
      string UoKpogiNsN;
      string twZIHCaCRw;
      string FbxsnVXnqt;
      string dVREoOAtSf;
      string UWyHjqyXWC;
      string PccOjrqQBT;
      string ItVyiXdVSr;
      string BgikbhdoJx;
      string XAQodAsDTw;
      string WiszXZAzYL;
      string MbEeAitrmB;
      string OBHEwHdgTh;
      string eZCVUSnjMB;
      string hdQxjuulnu;
      string GBPRgVanCP;
      string uSeqglZiJh;
      string uJekTkkJTA;
      string MqsYacKjnz;
      string qzgwFOyYQx;
      if(mYfeEqetKp == WiszXZAzYL){UMcGzxVdxw = true;}
      else if(WiszXZAzYL == mYfeEqetKp){AfJoMBLWQZ = true;}
      if(UoKpogiNsN == MbEeAitrmB){jRUBDEZGPD = true;}
      else if(MbEeAitrmB == UoKpogiNsN){cQXAkYwVbQ = true;}
      if(twZIHCaCRw == OBHEwHdgTh){botJpwbieF = true;}
      else if(OBHEwHdgTh == twZIHCaCRw){UryWVsQJca = true;}
      if(FbxsnVXnqt == eZCVUSnjMB){lLsVeAOmZd = true;}
      else if(eZCVUSnjMB == FbxsnVXnqt){OIUCPlmBQO = true;}
      if(dVREoOAtSf == hdQxjuulnu){HflrPZdfrB = true;}
      else if(hdQxjuulnu == dVREoOAtSf){hfPZWQXVlj = true;}
      if(UWyHjqyXWC == GBPRgVanCP){orIMVfSSQC = true;}
      else if(GBPRgVanCP == UWyHjqyXWC){XLRQWHhmST = true;}
      if(PccOjrqQBT == uSeqglZiJh){UmzrKXYyVD = true;}
      else if(uSeqglZiJh == PccOjrqQBT){kCsoLTuVjz = true;}
      if(ItVyiXdVSr == uJekTkkJTA){omflwuCBtP = true;}
      if(BgikbhdoJx == MqsYacKjnz){RwpcQsDfAz = true;}
      if(XAQodAsDTw == qzgwFOyYQx){gwWWIUgtgq = true;}
      while(uJekTkkJTA == ItVyiXdVSr){kuENincXAE = true;}
      while(MqsYacKjnz == MqsYacKjnz){UtXsDDqEfH = true;}
      while(qzgwFOyYQx == qzgwFOyYQx){DAhxcfmaOC = true;}
      if(UMcGzxVdxw == true){UMcGzxVdxw = false;}
      if(jRUBDEZGPD == true){jRUBDEZGPD = false;}
      if(botJpwbieF == true){botJpwbieF = false;}
      if(lLsVeAOmZd == true){lLsVeAOmZd = false;}
      if(HflrPZdfrB == true){HflrPZdfrB = false;}
      if(orIMVfSSQC == true){orIMVfSSQC = false;}
      if(UmzrKXYyVD == true){UmzrKXYyVD = false;}
      if(omflwuCBtP == true){omflwuCBtP = false;}
      if(RwpcQsDfAz == true){RwpcQsDfAz = false;}
      if(gwWWIUgtgq == true){gwWWIUgtgq = false;}
      if(AfJoMBLWQZ == true){AfJoMBLWQZ = false;}
      if(cQXAkYwVbQ == true){cQXAkYwVbQ = false;}
      if(UryWVsQJca == true){UryWVsQJca = false;}
      if(OIUCPlmBQO == true){OIUCPlmBQO = false;}
      if(hfPZWQXVlj == true){hfPZWQXVlj = false;}
      if(XLRQWHhmST == true){XLRQWHhmST = false;}
      if(kCsoLTuVjz == true){kCsoLTuVjz = false;}
      if(kuENincXAE == true){kuENincXAE = false;}
      if(UtXsDDqEfH == true){UtXsDDqEfH = false;}
      if(DAhxcfmaOC == true){DAhxcfmaOC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIDBOBMFQD
{ 
  void xqtytHiKlY()
  { 
      bool onnSIOHNUH = false;
      bool MPplkzDtNz = false;
      bool KIdjlKXhCI = false;
      bool rDSDAcBUAw = false;
      bool nKDPIfrZQc = false;
      bool PpnoMgKEgy = false;
      bool qZKMOIxmlH = false;
      bool yhsRLAFNaF = false;
      bool RyQZrCPdqS = false;
      bool RwnBFNzpBA = false;
      bool iEnIdhxVdL = false;
      bool bxcafsJkUM = false;
      bool sSwSpBsqLx = false;
      bool AOMaVNJHuK = false;
      bool EsAeqUSMVM = false;
      bool EOVnHQIVSc = false;
      bool nFKfLMkCFS = false;
      bool iBoJHzSRaU = false;
      bool hgVzslsXTF = false;
      bool EnnSVziUSd = false;
      string dWHQkSHfQq;
      string rdcqRdpamN;
      string zaQkiDdEeg;
      string OWiTGfVUjh;
      string bgXMYtWgaQ;
      string sWTVBCGVhh;
      string oDBjcVtIjl;
      string HVqEkSDEMn;
      string gwdNnqDMRE;
      string YzmBsYeniD;
      string ANxoJWfOki;
      string yCJsBrYmul;
      string RgpfMHioKL;
      string mPUInSznEQ;
      string KnbiFWpsAB;
      string zqrwkSWQbC;
      string nqDZuhgBFh;
      string rjiebdFHZp;
      string RonJLwXYXV;
      string whMBbSkBnW;
      if(dWHQkSHfQq == ANxoJWfOki){onnSIOHNUH = true;}
      else if(ANxoJWfOki == dWHQkSHfQq){iEnIdhxVdL = true;}
      if(rdcqRdpamN == yCJsBrYmul){MPplkzDtNz = true;}
      else if(yCJsBrYmul == rdcqRdpamN){bxcafsJkUM = true;}
      if(zaQkiDdEeg == RgpfMHioKL){KIdjlKXhCI = true;}
      else if(RgpfMHioKL == zaQkiDdEeg){sSwSpBsqLx = true;}
      if(OWiTGfVUjh == mPUInSznEQ){rDSDAcBUAw = true;}
      else if(mPUInSznEQ == OWiTGfVUjh){AOMaVNJHuK = true;}
      if(bgXMYtWgaQ == KnbiFWpsAB){nKDPIfrZQc = true;}
      else if(KnbiFWpsAB == bgXMYtWgaQ){EsAeqUSMVM = true;}
      if(sWTVBCGVhh == zqrwkSWQbC){PpnoMgKEgy = true;}
      else if(zqrwkSWQbC == sWTVBCGVhh){EOVnHQIVSc = true;}
      if(oDBjcVtIjl == nqDZuhgBFh){qZKMOIxmlH = true;}
      else if(nqDZuhgBFh == oDBjcVtIjl){nFKfLMkCFS = true;}
      if(HVqEkSDEMn == rjiebdFHZp){yhsRLAFNaF = true;}
      if(gwdNnqDMRE == RonJLwXYXV){RyQZrCPdqS = true;}
      if(YzmBsYeniD == whMBbSkBnW){RwnBFNzpBA = true;}
      while(rjiebdFHZp == HVqEkSDEMn){iBoJHzSRaU = true;}
      while(RonJLwXYXV == RonJLwXYXV){hgVzslsXTF = true;}
      while(whMBbSkBnW == whMBbSkBnW){EnnSVziUSd = true;}
      if(onnSIOHNUH == true){onnSIOHNUH = false;}
      if(MPplkzDtNz == true){MPplkzDtNz = false;}
      if(KIdjlKXhCI == true){KIdjlKXhCI = false;}
      if(rDSDAcBUAw == true){rDSDAcBUAw = false;}
      if(nKDPIfrZQc == true){nKDPIfrZQc = false;}
      if(PpnoMgKEgy == true){PpnoMgKEgy = false;}
      if(qZKMOIxmlH == true){qZKMOIxmlH = false;}
      if(yhsRLAFNaF == true){yhsRLAFNaF = false;}
      if(RyQZrCPdqS == true){RyQZrCPdqS = false;}
      if(RwnBFNzpBA == true){RwnBFNzpBA = false;}
      if(iEnIdhxVdL == true){iEnIdhxVdL = false;}
      if(bxcafsJkUM == true){bxcafsJkUM = false;}
      if(sSwSpBsqLx == true){sSwSpBsqLx = false;}
      if(AOMaVNJHuK == true){AOMaVNJHuK = false;}
      if(EsAeqUSMVM == true){EsAeqUSMVM = false;}
      if(EOVnHQIVSc == true){EOVnHQIVSc = false;}
      if(nFKfLMkCFS == true){nFKfLMkCFS = false;}
      if(iBoJHzSRaU == true){iBoJHzSRaU = false;}
      if(hgVzslsXTF == true){hgVzslsXTF = false;}
      if(EnnSVziUSd == true){EnnSVziUSd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWHKMZXFGP
{ 
  void wrBuUNlZPN()
  { 
      bool eEBnNudNAz = false;
      bool MAxOWRRoKY = false;
      bool BtEgkpHGrR = false;
      bool EhQMiHSMQO = false;
      bool BPAfjhhgrw = false;
      bool yrCBPjzUCX = false;
      bool nWUiueijeP = false;
      bool yFXwWltYwD = false;
      bool HaOwSMfPxz = false;
      bool IxJsZetQkE = false;
      bool yyBcxsTFdc = false;
      bool oaXzQNIYPh = false;
      bool zTmeHBueVr = false;
      bool rcmrEIYlyZ = false;
      bool rZkTKgYKbM = false;
      bool VUBCFdLWUw = false;
      bool yoiljLmftH = false;
      bool nVZopZhSUZ = false;
      bool bkCIVWbjma = false;
      bool xCQCbDpziy = false;
      string sezoJNRXZa;
      string dOjgQnyokW;
      string dqOzQfUBRi;
      string xBYBdWrkeG;
      string obRdEatHLg;
      string ylOLlCQzXd;
      string rPGqcbpiDt;
      string uMJdhBYkup;
      string kNokkLmMOa;
      string FsNBOYVaAb;
      string kLERkkbjdj;
      string dfDhseaVGR;
      string ocUbnBzIPI;
      string fyjSEYIXzz;
      string iChdxZoeHj;
      string yAUimHqbcj;
      string lSUUEeukcT;
      string VCVGhmtpeO;
      string MTBeKfcAfw;
      string hfuPNQhMZR;
      if(sezoJNRXZa == kLERkkbjdj){eEBnNudNAz = true;}
      else if(kLERkkbjdj == sezoJNRXZa){yyBcxsTFdc = true;}
      if(dOjgQnyokW == dfDhseaVGR){MAxOWRRoKY = true;}
      else if(dfDhseaVGR == dOjgQnyokW){oaXzQNIYPh = true;}
      if(dqOzQfUBRi == ocUbnBzIPI){BtEgkpHGrR = true;}
      else if(ocUbnBzIPI == dqOzQfUBRi){zTmeHBueVr = true;}
      if(xBYBdWrkeG == fyjSEYIXzz){EhQMiHSMQO = true;}
      else if(fyjSEYIXzz == xBYBdWrkeG){rcmrEIYlyZ = true;}
      if(obRdEatHLg == iChdxZoeHj){BPAfjhhgrw = true;}
      else if(iChdxZoeHj == obRdEatHLg){rZkTKgYKbM = true;}
      if(ylOLlCQzXd == yAUimHqbcj){yrCBPjzUCX = true;}
      else if(yAUimHqbcj == ylOLlCQzXd){VUBCFdLWUw = true;}
      if(rPGqcbpiDt == lSUUEeukcT){nWUiueijeP = true;}
      else if(lSUUEeukcT == rPGqcbpiDt){yoiljLmftH = true;}
      if(uMJdhBYkup == VCVGhmtpeO){yFXwWltYwD = true;}
      if(kNokkLmMOa == MTBeKfcAfw){HaOwSMfPxz = true;}
      if(FsNBOYVaAb == hfuPNQhMZR){IxJsZetQkE = true;}
      while(VCVGhmtpeO == uMJdhBYkup){nVZopZhSUZ = true;}
      while(MTBeKfcAfw == MTBeKfcAfw){bkCIVWbjma = true;}
      while(hfuPNQhMZR == hfuPNQhMZR){xCQCbDpziy = true;}
      if(eEBnNudNAz == true){eEBnNudNAz = false;}
      if(MAxOWRRoKY == true){MAxOWRRoKY = false;}
      if(BtEgkpHGrR == true){BtEgkpHGrR = false;}
      if(EhQMiHSMQO == true){EhQMiHSMQO = false;}
      if(BPAfjhhgrw == true){BPAfjhhgrw = false;}
      if(yrCBPjzUCX == true){yrCBPjzUCX = false;}
      if(nWUiueijeP == true){nWUiueijeP = false;}
      if(yFXwWltYwD == true){yFXwWltYwD = false;}
      if(HaOwSMfPxz == true){HaOwSMfPxz = false;}
      if(IxJsZetQkE == true){IxJsZetQkE = false;}
      if(yyBcxsTFdc == true){yyBcxsTFdc = false;}
      if(oaXzQNIYPh == true){oaXzQNIYPh = false;}
      if(zTmeHBueVr == true){zTmeHBueVr = false;}
      if(rcmrEIYlyZ == true){rcmrEIYlyZ = false;}
      if(rZkTKgYKbM == true){rZkTKgYKbM = false;}
      if(VUBCFdLWUw == true){VUBCFdLWUw = false;}
      if(yoiljLmftH == true){yoiljLmftH = false;}
      if(nVZopZhSUZ == true){nVZopZhSUZ = false;}
      if(bkCIVWbjma == true){bkCIVWbjma = false;}
      if(xCQCbDpziy == true){xCQCbDpziy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRGCQCMPQT
{ 
  void eliFUoEkyX()
  { 
      bool gSInsrYYFw = false;
      bool aCwuEosuTZ = false;
      bool JXTOSlHIDZ = false;
      bool gHNbFcelfA = false;
      bool MLCZtOwFDM = false;
      bool dokEUJzsUG = false;
      bool kPUeOToToa = false;
      bool JHPTMyUtUE = false;
      bool pBFqwqVJGw = false;
      bool dlQZOxqXKa = false;
      bool ZcPbCVZQqW = false;
      bool oFYQQjKciW = false;
      bool xfMsxXpoFP = false;
      bool GwiseMkdnZ = false;
      bool RFRiGXNzJe = false;
      bool lNnmdsPVee = false;
      bool fkLbQrVelD = false;
      bool ygnJFqNdlY = false;
      bool JpfZcrIuPk = false;
      bool xOyJtftpSO = false;
      string GmGUSkHDrB;
      string kRclyXebEj;
      string BStHygdAMS;
      string AnOOWwhKHG;
      string zHnrjVqyjw;
      string doPqimryWl;
      string GHqYAwCOPC;
      string oUUxksdCXb;
      string oeQQnLXXfi;
      string DjmVzrQOqm;
      string ScigGJTSFo;
      string JpatwaqZjo;
      string XehfzFgzxs;
      string cOKkJLuiJe;
      string qFRpYMIsYY;
      string ApdCOntChB;
      string cTUMMtfpkj;
      string eIQFxSMrGl;
      string wnaYrljIVV;
      string RsBHBWkFde;
      if(GmGUSkHDrB == ScigGJTSFo){gSInsrYYFw = true;}
      else if(ScigGJTSFo == GmGUSkHDrB){ZcPbCVZQqW = true;}
      if(kRclyXebEj == JpatwaqZjo){aCwuEosuTZ = true;}
      else if(JpatwaqZjo == kRclyXebEj){oFYQQjKciW = true;}
      if(BStHygdAMS == XehfzFgzxs){JXTOSlHIDZ = true;}
      else if(XehfzFgzxs == BStHygdAMS){xfMsxXpoFP = true;}
      if(AnOOWwhKHG == cOKkJLuiJe){gHNbFcelfA = true;}
      else if(cOKkJLuiJe == AnOOWwhKHG){GwiseMkdnZ = true;}
      if(zHnrjVqyjw == qFRpYMIsYY){MLCZtOwFDM = true;}
      else if(qFRpYMIsYY == zHnrjVqyjw){RFRiGXNzJe = true;}
      if(doPqimryWl == ApdCOntChB){dokEUJzsUG = true;}
      else if(ApdCOntChB == doPqimryWl){lNnmdsPVee = true;}
      if(GHqYAwCOPC == cTUMMtfpkj){kPUeOToToa = true;}
      else if(cTUMMtfpkj == GHqYAwCOPC){fkLbQrVelD = true;}
      if(oUUxksdCXb == eIQFxSMrGl){JHPTMyUtUE = true;}
      if(oeQQnLXXfi == wnaYrljIVV){pBFqwqVJGw = true;}
      if(DjmVzrQOqm == RsBHBWkFde){dlQZOxqXKa = true;}
      while(eIQFxSMrGl == oUUxksdCXb){ygnJFqNdlY = true;}
      while(wnaYrljIVV == wnaYrljIVV){JpfZcrIuPk = true;}
      while(RsBHBWkFde == RsBHBWkFde){xOyJtftpSO = true;}
      if(gSInsrYYFw == true){gSInsrYYFw = false;}
      if(aCwuEosuTZ == true){aCwuEosuTZ = false;}
      if(JXTOSlHIDZ == true){JXTOSlHIDZ = false;}
      if(gHNbFcelfA == true){gHNbFcelfA = false;}
      if(MLCZtOwFDM == true){MLCZtOwFDM = false;}
      if(dokEUJzsUG == true){dokEUJzsUG = false;}
      if(kPUeOToToa == true){kPUeOToToa = false;}
      if(JHPTMyUtUE == true){JHPTMyUtUE = false;}
      if(pBFqwqVJGw == true){pBFqwqVJGw = false;}
      if(dlQZOxqXKa == true){dlQZOxqXKa = false;}
      if(ZcPbCVZQqW == true){ZcPbCVZQqW = false;}
      if(oFYQQjKciW == true){oFYQQjKciW = false;}
      if(xfMsxXpoFP == true){xfMsxXpoFP = false;}
      if(GwiseMkdnZ == true){GwiseMkdnZ = false;}
      if(RFRiGXNzJe == true){RFRiGXNzJe = false;}
      if(lNnmdsPVee == true){lNnmdsPVee = false;}
      if(fkLbQrVelD == true){fkLbQrVelD = false;}
      if(ygnJFqNdlY == true){ygnJFqNdlY = false;}
      if(JpfZcrIuPk == true){JpfZcrIuPk = false;}
      if(xOyJtftpSO == true){xOyJtftpSO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBWPNMMILA
{ 
  void WPGhTggMeg()
  { 
      bool msysxzECjy = false;
      bool CZVOrTVQmI = false;
      bool nDWQOXQJRh = false;
      bool CUGNoBsWAZ = false;
      bool XoYRSOrTiu = false;
      bool ZtKXkiVhdZ = false;
      bool htkBuhTHZq = false;
      bool ZyPNkzdFxA = false;
      bool exaVIHJibF = false;
      bool eLsaqcDWWk = false;
      bool tjtqVaexll = false;
      bool EQjcujTPsm = false;
      bool XjfTLOFoVI = false;
      bool wHiMFtDiAg = false;
      bool cMxpAObPeH = false;
      bool JmciMKEZfG = false;
      bool VpbdpxhXWA = false;
      bool gjPMKLmoTx = false;
      bool moJOyIdzzu = false;
      bool odDsKljSAC = false;
      string MCfsoPipTp;
      string JEIxdIeqAg;
      string ZjToVOhTNw;
      string wxcgpSlmbZ;
      string lRPUMctJck;
      string fOYfLbhqXZ;
      string hObXtMbaHL;
      string WrOauHTybs;
      string UYpcPhXwVN;
      string juPCrWoraA;
      string BSCRNnzxkD;
      string HjOeFIXzIM;
      string neFsaacMhX;
      string RbXbrBWYOa;
      string haLRFzfkwi;
      string ypjNLVNIpm;
      string LlPMkfMmlD;
      string kzkgdNTmmb;
      string trQyYbrJPV;
      string nNhaPwKygZ;
      if(MCfsoPipTp == BSCRNnzxkD){msysxzECjy = true;}
      else if(BSCRNnzxkD == MCfsoPipTp){tjtqVaexll = true;}
      if(JEIxdIeqAg == HjOeFIXzIM){CZVOrTVQmI = true;}
      else if(HjOeFIXzIM == JEIxdIeqAg){EQjcujTPsm = true;}
      if(ZjToVOhTNw == neFsaacMhX){nDWQOXQJRh = true;}
      else if(neFsaacMhX == ZjToVOhTNw){XjfTLOFoVI = true;}
      if(wxcgpSlmbZ == RbXbrBWYOa){CUGNoBsWAZ = true;}
      else if(RbXbrBWYOa == wxcgpSlmbZ){wHiMFtDiAg = true;}
      if(lRPUMctJck == haLRFzfkwi){XoYRSOrTiu = true;}
      else if(haLRFzfkwi == lRPUMctJck){cMxpAObPeH = true;}
      if(fOYfLbhqXZ == ypjNLVNIpm){ZtKXkiVhdZ = true;}
      else if(ypjNLVNIpm == fOYfLbhqXZ){JmciMKEZfG = true;}
      if(hObXtMbaHL == LlPMkfMmlD){htkBuhTHZq = true;}
      else if(LlPMkfMmlD == hObXtMbaHL){VpbdpxhXWA = true;}
      if(WrOauHTybs == kzkgdNTmmb){ZyPNkzdFxA = true;}
      if(UYpcPhXwVN == trQyYbrJPV){exaVIHJibF = true;}
      if(juPCrWoraA == nNhaPwKygZ){eLsaqcDWWk = true;}
      while(kzkgdNTmmb == WrOauHTybs){gjPMKLmoTx = true;}
      while(trQyYbrJPV == trQyYbrJPV){moJOyIdzzu = true;}
      while(nNhaPwKygZ == nNhaPwKygZ){odDsKljSAC = true;}
      if(msysxzECjy == true){msysxzECjy = false;}
      if(CZVOrTVQmI == true){CZVOrTVQmI = false;}
      if(nDWQOXQJRh == true){nDWQOXQJRh = false;}
      if(CUGNoBsWAZ == true){CUGNoBsWAZ = false;}
      if(XoYRSOrTiu == true){XoYRSOrTiu = false;}
      if(ZtKXkiVhdZ == true){ZtKXkiVhdZ = false;}
      if(htkBuhTHZq == true){htkBuhTHZq = false;}
      if(ZyPNkzdFxA == true){ZyPNkzdFxA = false;}
      if(exaVIHJibF == true){exaVIHJibF = false;}
      if(eLsaqcDWWk == true){eLsaqcDWWk = false;}
      if(tjtqVaexll == true){tjtqVaexll = false;}
      if(EQjcujTPsm == true){EQjcujTPsm = false;}
      if(XjfTLOFoVI == true){XjfTLOFoVI = false;}
      if(wHiMFtDiAg == true){wHiMFtDiAg = false;}
      if(cMxpAObPeH == true){cMxpAObPeH = false;}
      if(JmciMKEZfG == true){JmciMKEZfG = false;}
      if(VpbdpxhXWA == true){VpbdpxhXWA = false;}
      if(gjPMKLmoTx == true){gjPMKLmoTx = false;}
      if(moJOyIdzzu == true){moJOyIdzzu = false;}
      if(odDsKljSAC == true){odDsKljSAC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAWEHYLJCG
{ 
  void DtFnATlhNX()
  { 
      bool xmtTfXUTXj = false;
      bool JjQISQlehW = false;
      bool PMQFCBgGTH = false;
      bool mkQPGIqIPe = false;
      bool MqdBDKewOA = false;
      bool EhgOAkWnQe = false;
      bool qNAPwYTABJ = false;
      bool YcODJXiOCq = false;
      bool VjrTDEDBPV = false;
      bool lDqjnzqNEe = false;
      bool qduEbaTdEb = false;
      bool BHlYJGUfMr = false;
      bool URkeXVldOK = false;
      bool gUKXArnnrc = false;
      bool jYwmUeQRag = false;
      bool dKBLJYrQgF = false;
      bool noPttgxOYR = false;
      bool SgniHwVxKs = false;
      bool FUCgfWSyNa = false;
      bool zXGlnuJCsm = false;
      string gTSOVpAdpW;
      string UXtIFbTjSr;
      string LMiAramxuR;
      string JnXPDldVsX;
      string QbjkFLLZzy;
      string xyxYdUkRVu;
      string DChYNfAeFT;
      string xxquaibxtg;
      string OMyxTLqyki;
      string BMAxTOsLXY;
      string KgTeAAHCxt;
      string rnWnfpEkFC;
      string oBsWRkxsaM;
      string pQYUVhsSwT;
      string DoApqNoLRd;
      string JIFVjJmxNO;
      string CNbkEaPBRx;
      string xlnkyAACfE;
      string wkbwCgLCkM;
      string uwFgRpNPlP;
      if(gTSOVpAdpW == KgTeAAHCxt){xmtTfXUTXj = true;}
      else if(KgTeAAHCxt == gTSOVpAdpW){qduEbaTdEb = true;}
      if(UXtIFbTjSr == rnWnfpEkFC){JjQISQlehW = true;}
      else if(rnWnfpEkFC == UXtIFbTjSr){BHlYJGUfMr = true;}
      if(LMiAramxuR == oBsWRkxsaM){PMQFCBgGTH = true;}
      else if(oBsWRkxsaM == LMiAramxuR){URkeXVldOK = true;}
      if(JnXPDldVsX == pQYUVhsSwT){mkQPGIqIPe = true;}
      else if(pQYUVhsSwT == JnXPDldVsX){gUKXArnnrc = true;}
      if(QbjkFLLZzy == DoApqNoLRd){MqdBDKewOA = true;}
      else if(DoApqNoLRd == QbjkFLLZzy){jYwmUeQRag = true;}
      if(xyxYdUkRVu == JIFVjJmxNO){EhgOAkWnQe = true;}
      else if(JIFVjJmxNO == xyxYdUkRVu){dKBLJYrQgF = true;}
      if(DChYNfAeFT == CNbkEaPBRx){qNAPwYTABJ = true;}
      else if(CNbkEaPBRx == DChYNfAeFT){noPttgxOYR = true;}
      if(xxquaibxtg == xlnkyAACfE){YcODJXiOCq = true;}
      if(OMyxTLqyki == wkbwCgLCkM){VjrTDEDBPV = true;}
      if(BMAxTOsLXY == uwFgRpNPlP){lDqjnzqNEe = true;}
      while(xlnkyAACfE == xxquaibxtg){SgniHwVxKs = true;}
      while(wkbwCgLCkM == wkbwCgLCkM){FUCgfWSyNa = true;}
      while(uwFgRpNPlP == uwFgRpNPlP){zXGlnuJCsm = true;}
      if(xmtTfXUTXj == true){xmtTfXUTXj = false;}
      if(JjQISQlehW == true){JjQISQlehW = false;}
      if(PMQFCBgGTH == true){PMQFCBgGTH = false;}
      if(mkQPGIqIPe == true){mkQPGIqIPe = false;}
      if(MqdBDKewOA == true){MqdBDKewOA = false;}
      if(EhgOAkWnQe == true){EhgOAkWnQe = false;}
      if(qNAPwYTABJ == true){qNAPwYTABJ = false;}
      if(YcODJXiOCq == true){YcODJXiOCq = false;}
      if(VjrTDEDBPV == true){VjrTDEDBPV = false;}
      if(lDqjnzqNEe == true){lDqjnzqNEe = false;}
      if(qduEbaTdEb == true){qduEbaTdEb = false;}
      if(BHlYJGUfMr == true){BHlYJGUfMr = false;}
      if(URkeXVldOK == true){URkeXVldOK = false;}
      if(gUKXArnnrc == true){gUKXArnnrc = false;}
      if(jYwmUeQRag == true){jYwmUeQRag = false;}
      if(dKBLJYrQgF == true){dKBLJYrQgF = false;}
      if(noPttgxOYR == true){noPttgxOYR = false;}
      if(SgniHwVxKs == true){SgniHwVxKs = false;}
      if(FUCgfWSyNa == true){FUCgfWSyNa = false;}
      if(zXGlnuJCsm == true){zXGlnuJCsm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PCBMTKPETT
{ 
  void lXobqpnFaO()
  { 
      bool cogDJPlKbT = false;
      bool ShHrTapICF = false;
      bool nQcmYanNOS = false;
      bool WaFDxtnzwF = false;
      bool YBAPaaONzD = false;
      bool oDJbtLLteh = false;
      bool bXwIxqbDuY = false;
      bool lqMwglQMLx = false;
      bool MaNLcTRdJk = false;
      bool hsTOdBFqRi = false;
      bool yKRaQyqMuH = false;
      bool tyihUAJjfd = false;
      bool ZytJprWxSe = false;
      bool gZtcyBJmte = false;
      bool cEiBqiKlsc = false;
      bool qULnIAQHjY = false;
      bool astPaUDFiT = false;
      bool qWpBBVOrSH = false;
      bool gkEonLOGTy = false;
      bool kBDUDiJTaV = false;
      string jgTYjFXMoJ;
      string UIaVhthpxq;
      string rghTPgMRtP;
      string dLzsBSDDCO;
      string ioueVlqheg;
      string JVJLyCzzJC;
      string sFRYfJJhTP;
      string qdnhIClCyc;
      string oemNFHBmuz;
      string SDtzVcXVzL;
      string cJOOpfhaDu;
      string PwAfNOSESY;
      string IWmUwminMf;
      string dPDmzfPXWZ;
      string ZZiziWCNkH;
      string KSDaCFVsSD;
      string wsOXQAsNfh;
      string ytgryhmnlZ;
      string jVCFVKMbjs;
      string JWFTdfLLhh;
      if(jgTYjFXMoJ == cJOOpfhaDu){cogDJPlKbT = true;}
      else if(cJOOpfhaDu == jgTYjFXMoJ){yKRaQyqMuH = true;}
      if(UIaVhthpxq == PwAfNOSESY){ShHrTapICF = true;}
      else if(PwAfNOSESY == UIaVhthpxq){tyihUAJjfd = true;}
      if(rghTPgMRtP == IWmUwminMf){nQcmYanNOS = true;}
      else if(IWmUwminMf == rghTPgMRtP){ZytJprWxSe = true;}
      if(dLzsBSDDCO == dPDmzfPXWZ){WaFDxtnzwF = true;}
      else if(dPDmzfPXWZ == dLzsBSDDCO){gZtcyBJmte = true;}
      if(ioueVlqheg == ZZiziWCNkH){YBAPaaONzD = true;}
      else if(ZZiziWCNkH == ioueVlqheg){cEiBqiKlsc = true;}
      if(JVJLyCzzJC == KSDaCFVsSD){oDJbtLLteh = true;}
      else if(KSDaCFVsSD == JVJLyCzzJC){qULnIAQHjY = true;}
      if(sFRYfJJhTP == wsOXQAsNfh){bXwIxqbDuY = true;}
      else if(wsOXQAsNfh == sFRYfJJhTP){astPaUDFiT = true;}
      if(qdnhIClCyc == ytgryhmnlZ){lqMwglQMLx = true;}
      if(oemNFHBmuz == jVCFVKMbjs){MaNLcTRdJk = true;}
      if(SDtzVcXVzL == JWFTdfLLhh){hsTOdBFqRi = true;}
      while(ytgryhmnlZ == qdnhIClCyc){qWpBBVOrSH = true;}
      while(jVCFVKMbjs == jVCFVKMbjs){gkEonLOGTy = true;}
      while(JWFTdfLLhh == JWFTdfLLhh){kBDUDiJTaV = true;}
      if(cogDJPlKbT == true){cogDJPlKbT = false;}
      if(ShHrTapICF == true){ShHrTapICF = false;}
      if(nQcmYanNOS == true){nQcmYanNOS = false;}
      if(WaFDxtnzwF == true){WaFDxtnzwF = false;}
      if(YBAPaaONzD == true){YBAPaaONzD = false;}
      if(oDJbtLLteh == true){oDJbtLLteh = false;}
      if(bXwIxqbDuY == true){bXwIxqbDuY = false;}
      if(lqMwglQMLx == true){lqMwglQMLx = false;}
      if(MaNLcTRdJk == true){MaNLcTRdJk = false;}
      if(hsTOdBFqRi == true){hsTOdBFqRi = false;}
      if(yKRaQyqMuH == true){yKRaQyqMuH = false;}
      if(tyihUAJjfd == true){tyihUAJjfd = false;}
      if(ZytJprWxSe == true){ZytJprWxSe = false;}
      if(gZtcyBJmte == true){gZtcyBJmte = false;}
      if(cEiBqiKlsc == true){cEiBqiKlsc = false;}
      if(qULnIAQHjY == true){qULnIAQHjY = false;}
      if(astPaUDFiT == true){astPaUDFiT = false;}
      if(qWpBBVOrSH == true){qWpBBVOrSH = false;}
      if(gkEonLOGTy == true){gkEonLOGTy = false;}
      if(kBDUDiJTaV == true){kBDUDiJTaV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFSRRVYCNJ
{ 
  void DIzyxieSCT()
  { 
      bool foFBUqwmcX = false;
      bool OuOPuYpWMr = false;
      bool baJzjLcYua = false;
      bool yxqaAYqGpW = false;
      bool IMEpTunlxO = false;
      bool oRixOEeGQI = false;
      bool NXrBYQEnOW = false;
      bool gigojPWTfo = false;
      bool XqaflfOtLw = false;
      bool skpgIjUDQC = false;
      bool qzWZgFksNz = false;
      bool hLabkWwLOr = false;
      bool CKbSdwsAfz = false;
      bool tSCcxXTBzf = false;
      bool uUfMNgJOul = false;
      bool mJnYzgXEuk = false;
      bool MjMNEOJxdN = false;
      bool DuMixgdOEx = false;
      bool mdEtLkedcQ = false;
      bool zPFOSKHRHz = false;
      string xGeZHgLafC;
      string MmyEGCqBQi;
      string uNxfnqcQQU;
      string GDlYBWMwpn;
      string usaOgZXXAb;
      string CtEATjIykP;
      string EtJLuJBZDi;
      string puLcmCliyO;
      string SFQoRLykER;
      string NNKZiBiPSX;
      string YyTRlHiaNQ;
      string yZzWwzdUsi;
      string LQUlUbkktl;
      string TVQapUkyDK;
      string cWWmSnNmci;
      string WOViMHchwJ;
      string WygbxbIYgb;
      string OeRiGnsgSg;
      string NxHKOFzgOh;
      string qCCsneoupq;
      if(xGeZHgLafC == YyTRlHiaNQ){foFBUqwmcX = true;}
      else if(YyTRlHiaNQ == xGeZHgLafC){qzWZgFksNz = true;}
      if(MmyEGCqBQi == yZzWwzdUsi){OuOPuYpWMr = true;}
      else if(yZzWwzdUsi == MmyEGCqBQi){hLabkWwLOr = true;}
      if(uNxfnqcQQU == LQUlUbkktl){baJzjLcYua = true;}
      else if(LQUlUbkktl == uNxfnqcQQU){CKbSdwsAfz = true;}
      if(GDlYBWMwpn == TVQapUkyDK){yxqaAYqGpW = true;}
      else if(TVQapUkyDK == GDlYBWMwpn){tSCcxXTBzf = true;}
      if(usaOgZXXAb == cWWmSnNmci){IMEpTunlxO = true;}
      else if(cWWmSnNmci == usaOgZXXAb){uUfMNgJOul = true;}
      if(CtEATjIykP == WOViMHchwJ){oRixOEeGQI = true;}
      else if(WOViMHchwJ == CtEATjIykP){mJnYzgXEuk = true;}
      if(EtJLuJBZDi == WygbxbIYgb){NXrBYQEnOW = true;}
      else if(WygbxbIYgb == EtJLuJBZDi){MjMNEOJxdN = true;}
      if(puLcmCliyO == OeRiGnsgSg){gigojPWTfo = true;}
      if(SFQoRLykER == NxHKOFzgOh){XqaflfOtLw = true;}
      if(NNKZiBiPSX == qCCsneoupq){skpgIjUDQC = true;}
      while(OeRiGnsgSg == puLcmCliyO){DuMixgdOEx = true;}
      while(NxHKOFzgOh == NxHKOFzgOh){mdEtLkedcQ = true;}
      while(qCCsneoupq == qCCsneoupq){zPFOSKHRHz = true;}
      if(foFBUqwmcX == true){foFBUqwmcX = false;}
      if(OuOPuYpWMr == true){OuOPuYpWMr = false;}
      if(baJzjLcYua == true){baJzjLcYua = false;}
      if(yxqaAYqGpW == true){yxqaAYqGpW = false;}
      if(IMEpTunlxO == true){IMEpTunlxO = false;}
      if(oRixOEeGQI == true){oRixOEeGQI = false;}
      if(NXrBYQEnOW == true){NXrBYQEnOW = false;}
      if(gigojPWTfo == true){gigojPWTfo = false;}
      if(XqaflfOtLw == true){XqaflfOtLw = false;}
      if(skpgIjUDQC == true){skpgIjUDQC = false;}
      if(qzWZgFksNz == true){qzWZgFksNz = false;}
      if(hLabkWwLOr == true){hLabkWwLOr = false;}
      if(CKbSdwsAfz == true){CKbSdwsAfz = false;}
      if(tSCcxXTBzf == true){tSCcxXTBzf = false;}
      if(uUfMNgJOul == true){uUfMNgJOul = false;}
      if(mJnYzgXEuk == true){mJnYzgXEuk = false;}
      if(MjMNEOJxdN == true){MjMNEOJxdN = false;}
      if(DuMixgdOEx == true){DuMixgdOEx = false;}
      if(mdEtLkedcQ == true){mdEtLkedcQ = false;}
      if(zPFOSKHRHz == true){zPFOSKHRHz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCTNCOKYNW
{ 
  void HBjsQeCGeM()
  { 
      bool TIhGmKXwPG = false;
      bool UNDyTFRScU = false;
      bool rqtqaxyIim = false;
      bool ZAjPBCHYoI = false;
      bool SdMLsAGCKF = false;
      bool klpqlbOpfo = false;
      bool MPMbfTcnwR = false;
      bool yscTCNdhya = false;
      bool quydCnKsdY = false;
      bool nQrzwDQkfY = false;
      bool WRFrGrIVoX = false;
      bool xfrEyQQiYr = false;
      bool JjKXcgAdXy = false;
      bool wsCYDYpFWK = false;
      bool enEFaHXnAf = false;
      bool mhLmPmHhOZ = false;
      bool qeypbEdTAZ = false;
      bool ZKMONVeFxV = false;
      bool IMcrKOhOJQ = false;
      bool RIqxSAoNdW = false;
      string YXgCQSkXEA;
      string dyZtWtxQJA;
      string ogprVxFWDY;
      string kaYPXWaadY;
      string rdXLUxqJaf;
      string tLFiargnfT;
      string MOUfPCZKVz;
      string TWlkHLIeWY;
      string FwuWeYVpnf;
      string pltKMdIrwS;
      string WgnbMXYUaP;
      string iCQHNQSxBp;
      string giVpIgbbYd;
      string CQhEBYITKG;
      string ABPYwnVmwu;
      string KLpFlnKxSf;
      string uxuwMSTMFo;
      string IzmtpeTxsU;
      string LofcTqZbSN;
      string NKAdLCFSMd;
      if(YXgCQSkXEA == WgnbMXYUaP){TIhGmKXwPG = true;}
      else if(WgnbMXYUaP == YXgCQSkXEA){WRFrGrIVoX = true;}
      if(dyZtWtxQJA == iCQHNQSxBp){UNDyTFRScU = true;}
      else if(iCQHNQSxBp == dyZtWtxQJA){xfrEyQQiYr = true;}
      if(ogprVxFWDY == giVpIgbbYd){rqtqaxyIim = true;}
      else if(giVpIgbbYd == ogprVxFWDY){JjKXcgAdXy = true;}
      if(kaYPXWaadY == CQhEBYITKG){ZAjPBCHYoI = true;}
      else if(CQhEBYITKG == kaYPXWaadY){wsCYDYpFWK = true;}
      if(rdXLUxqJaf == ABPYwnVmwu){SdMLsAGCKF = true;}
      else if(ABPYwnVmwu == rdXLUxqJaf){enEFaHXnAf = true;}
      if(tLFiargnfT == KLpFlnKxSf){klpqlbOpfo = true;}
      else if(KLpFlnKxSf == tLFiargnfT){mhLmPmHhOZ = true;}
      if(MOUfPCZKVz == uxuwMSTMFo){MPMbfTcnwR = true;}
      else if(uxuwMSTMFo == MOUfPCZKVz){qeypbEdTAZ = true;}
      if(TWlkHLIeWY == IzmtpeTxsU){yscTCNdhya = true;}
      if(FwuWeYVpnf == LofcTqZbSN){quydCnKsdY = true;}
      if(pltKMdIrwS == NKAdLCFSMd){nQrzwDQkfY = true;}
      while(IzmtpeTxsU == TWlkHLIeWY){ZKMONVeFxV = true;}
      while(LofcTqZbSN == LofcTqZbSN){IMcrKOhOJQ = true;}
      while(NKAdLCFSMd == NKAdLCFSMd){RIqxSAoNdW = true;}
      if(TIhGmKXwPG == true){TIhGmKXwPG = false;}
      if(UNDyTFRScU == true){UNDyTFRScU = false;}
      if(rqtqaxyIim == true){rqtqaxyIim = false;}
      if(ZAjPBCHYoI == true){ZAjPBCHYoI = false;}
      if(SdMLsAGCKF == true){SdMLsAGCKF = false;}
      if(klpqlbOpfo == true){klpqlbOpfo = false;}
      if(MPMbfTcnwR == true){MPMbfTcnwR = false;}
      if(yscTCNdhya == true){yscTCNdhya = false;}
      if(quydCnKsdY == true){quydCnKsdY = false;}
      if(nQrzwDQkfY == true){nQrzwDQkfY = false;}
      if(WRFrGrIVoX == true){WRFrGrIVoX = false;}
      if(xfrEyQQiYr == true){xfrEyQQiYr = false;}
      if(JjKXcgAdXy == true){JjKXcgAdXy = false;}
      if(wsCYDYpFWK == true){wsCYDYpFWK = false;}
      if(enEFaHXnAf == true){enEFaHXnAf = false;}
      if(mhLmPmHhOZ == true){mhLmPmHhOZ = false;}
      if(qeypbEdTAZ == true){qeypbEdTAZ = false;}
      if(ZKMONVeFxV == true){ZKMONVeFxV = false;}
      if(IMcrKOhOJQ == true){IMcrKOhOJQ = false;}
      if(RIqxSAoNdW == true){RIqxSAoNdW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWUJSJPGIW
{ 
  void JHiMpWtPBh()
  { 
      bool SlNALtiDWe = false;
      bool kGYSaiKlfy = false;
      bool UyHHHVKUZe = false;
      bool bhsBIhObxM = false;
      bool UqmZGxlDce = false;
      bool FrSpLTdGso = false;
      bool jOcqDDMWKs = false;
      bool TioTcdLgAJ = false;
      bool jGqtYjPDoo = false;
      bool DIiIcGNwWD = false;
      bool kPsjKWDyMh = false;
      bool IwFiEcWiRS = false;
      bool mIgVoLzfqW = false;
      bool PPJxXTNHiC = false;
      bool gQpGfGCzDz = false;
      bool iedEPbhXuz = false;
      bool WWHpSsmIKj = false;
      bool PPzPlWSZoh = false;
      bool JAbqnjkFgw = false;
      bool loLjeJIAnm = false;
      string ucfJTmsiox;
      string LWBeIijjuI;
      string MywWGGdcyt;
      string PLuSxsMYdB;
      string tSDAPMyVMj;
      string OhpkKxgJCN;
      string IQkuhAbigP;
      string VLFtNttuGt;
      string IHPNegUJIA;
      string MCVQsdgISP;
      string jPoxODcwXQ;
      string CkDIEAAXQA;
      string eSZgCSpoBj;
      string NlbpJsSRzb;
      string EYlrxazMLr;
      string cIqSkRoHtu;
      string MmumDPINzL;
      string ghYnwFghia;
      string TccIHEtJFr;
      string EKWEOQdyog;
      if(ucfJTmsiox == jPoxODcwXQ){SlNALtiDWe = true;}
      else if(jPoxODcwXQ == ucfJTmsiox){kPsjKWDyMh = true;}
      if(LWBeIijjuI == CkDIEAAXQA){kGYSaiKlfy = true;}
      else if(CkDIEAAXQA == LWBeIijjuI){IwFiEcWiRS = true;}
      if(MywWGGdcyt == eSZgCSpoBj){UyHHHVKUZe = true;}
      else if(eSZgCSpoBj == MywWGGdcyt){mIgVoLzfqW = true;}
      if(PLuSxsMYdB == NlbpJsSRzb){bhsBIhObxM = true;}
      else if(NlbpJsSRzb == PLuSxsMYdB){PPJxXTNHiC = true;}
      if(tSDAPMyVMj == EYlrxazMLr){UqmZGxlDce = true;}
      else if(EYlrxazMLr == tSDAPMyVMj){gQpGfGCzDz = true;}
      if(OhpkKxgJCN == cIqSkRoHtu){FrSpLTdGso = true;}
      else if(cIqSkRoHtu == OhpkKxgJCN){iedEPbhXuz = true;}
      if(IQkuhAbigP == MmumDPINzL){jOcqDDMWKs = true;}
      else if(MmumDPINzL == IQkuhAbigP){WWHpSsmIKj = true;}
      if(VLFtNttuGt == ghYnwFghia){TioTcdLgAJ = true;}
      if(IHPNegUJIA == TccIHEtJFr){jGqtYjPDoo = true;}
      if(MCVQsdgISP == EKWEOQdyog){DIiIcGNwWD = true;}
      while(ghYnwFghia == VLFtNttuGt){PPzPlWSZoh = true;}
      while(TccIHEtJFr == TccIHEtJFr){JAbqnjkFgw = true;}
      while(EKWEOQdyog == EKWEOQdyog){loLjeJIAnm = true;}
      if(SlNALtiDWe == true){SlNALtiDWe = false;}
      if(kGYSaiKlfy == true){kGYSaiKlfy = false;}
      if(UyHHHVKUZe == true){UyHHHVKUZe = false;}
      if(bhsBIhObxM == true){bhsBIhObxM = false;}
      if(UqmZGxlDce == true){UqmZGxlDce = false;}
      if(FrSpLTdGso == true){FrSpLTdGso = false;}
      if(jOcqDDMWKs == true){jOcqDDMWKs = false;}
      if(TioTcdLgAJ == true){TioTcdLgAJ = false;}
      if(jGqtYjPDoo == true){jGqtYjPDoo = false;}
      if(DIiIcGNwWD == true){DIiIcGNwWD = false;}
      if(kPsjKWDyMh == true){kPsjKWDyMh = false;}
      if(IwFiEcWiRS == true){IwFiEcWiRS = false;}
      if(mIgVoLzfqW == true){mIgVoLzfqW = false;}
      if(PPJxXTNHiC == true){PPJxXTNHiC = false;}
      if(gQpGfGCzDz == true){gQpGfGCzDz = false;}
      if(iedEPbhXuz == true){iedEPbhXuz = false;}
      if(WWHpSsmIKj == true){WWHpSsmIKj = false;}
      if(PPzPlWSZoh == true){PPzPlWSZoh = false;}
      if(JAbqnjkFgw == true){JAbqnjkFgw = false;}
      if(loLjeJIAnm == true){loLjeJIAnm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXXKRCSBRA
{ 
  void mAIGxJDmQA()
  { 
      bool SqVFbXnnST = false;
      bool HRLlJQqslC = false;
      bool QbmRVIBumy = false;
      bool uZxQBAASxI = false;
      bool FKbcUzKZqM = false;
      bool wbGLUqEDjS = false;
      bool VsBTXhTujJ = false;
      bool QYwdxGzJxV = false;
      bool xaDZCSTlwK = false;
      bool uwhdmMJIEl = false;
      bool fPohwWfcNN = false;
      bool qtGOUtoaRE = false;
      bool NhyZNUpSqj = false;
      bool xqEKphkVde = false;
      bool mqXhSApTIr = false;
      bool XhpzXxQPTa = false;
      bool fNkdPAouYm = false;
      bool ITxlRWKQHM = false;
      bool dWKyMPAFlr = false;
      bool RVBCyZFsRS = false;
      string SisAmOhbkk;
      string cqALCuUtqN;
      string aEQErKxUEM;
      string JlPmjeiVDn;
      string eILVfhOtlg;
      string XYASwNSoHc;
      string RNWXapaNaW;
      string MzqCiSruXJ;
      string uChWoklwpW;
      string MsNZVQlnup;
      string GASPUXgyjd;
      string UWRygPfzhp;
      string EeXEJSkQfR;
      string fEAhDtjRCQ;
      string DnLLCobPrG;
      string klFEkacNFB;
      string mPRSxPWjtm;
      string eNxQlQSLCT;
      string qVYYftyuwb;
      string RVLBdmVsOl;
      if(SisAmOhbkk == GASPUXgyjd){SqVFbXnnST = true;}
      else if(GASPUXgyjd == SisAmOhbkk){fPohwWfcNN = true;}
      if(cqALCuUtqN == UWRygPfzhp){HRLlJQqslC = true;}
      else if(UWRygPfzhp == cqALCuUtqN){qtGOUtoaRE = true;}
      if(aEQErKxUEM == EeXEJSkQfR){QbmRVIBumy = true;}
      else if(EeXEJSkQfR == aEQErKxUEM){NhyZNUpSqj = true;}
      if(JlPmjeiVDn == fEAhDtjRCQ){uZxQBAASxI = true;}
      else if(fEAhDtjRCQ == JlPmjeiVDn){xqEKphkVde = true;}
      if(eILVfhOtlg == DnLLCobPrG){FKbcUzKZqM = true;}
      else if(DnLLCobPrG == eILVfhOtlg){mqXhSApTIr = true;}
      if(XYASwNSoHc == klFEkacNFB){wbGLUqEDjS = true;}
      else if(klFEkacNFB == XYASwNSoHc){XhpzXxQPTa = true;}
      if(RNWXapaNaW == mPRSxPWjtm){VsBTXhTujJ = true;}
      else if(mPRSxPWjtm == RNWXapaNaW){fNkdPAouYm = true;}
      if(MzqCiSruXJ == eNxQlQSLCT){QYwdxGzJxV = true;}
      if(uChWoklwpW == qVYYftyuwb){xaDZCSTlwK = true;}
      if(MsNZVQlnup == RVLBdmVsOl){uwhdmMJIEl = true;}
      while(eNxQlQSLCT == MzqCiSruXJ){ITxlRWKQHM = true;}
      while(qVYYftyuwb == qVYYftyuwb){dWKyMPAFlr = true;}
      while(RVLBdmVsOl == RVLBdmVsOl){RVBCyZFsRS = true;}
      if(SqVFbXnnST == true){SqVFbXnnST = false;}
      if(HRLlJQqslC == true){HRLlJQqslC = false;}
      if(QbmRVIBumy == true){QbmRVIBumy = false;}
      if(uZxQBAASxI == true){uZxQBAASxI = false;}
      if(FKbcUzKZqM == true){FKbcUzKZqM = false;}
      if(wbGLUqEDjS == true){wbGLUqEDjS = false;}
      if(VsBTXhTujJ == true){VsBTXhTujJ = false;}
      if(QYwdxGzJxV == true){QYwdxGzJxV = false;}
      if(xaDZCSTlwK == true){xaDZCSTlwK = false;}
      if(uwhdmMJIEl == true){uwhdmMJIEl = false;}
      if(fPohwWfcNN == true){fPohwWfcNN = false;}
      if(qtGOUtoaRE == true){qtGOUtoaRE = false;}
      if(NhyZNUpSqj == true){NhyZNUpSqj = false;}
      if(xqEKphkVde == true){xqEKphkVde = false;}
      if(mqXhSApTIr == true){mqXhSApTIr = false;}
      if(XhpzXxQPTa == true){XhpzXxQPTa = false;}
      if(fNkdPAouYm == true){fNkdPAouYm = false;}
      if(ITxlRWKQHM == true){ITxlRWKQHM = false;}
      if(dWKyMPAFlr == true){dWKyMPAFlr = false;}
      if(RVBCyZFsRS == true){RVBCyZFsRS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSOBOWEAOT
{ 
  void QVKCnBOkYl()
  { 
      bool zWXuTMXLHJ = false;
      bool YQDVFCQGiG = false;
      bool oxqjNQlCeh = false;
      bool WfByRsTkfg = false;
      bool ppBoREfkaO = false;
      bool BXyEWBemgC = false;
      bool ZVgZmsOEEL = false;
      bool heaCPywBSJ = false;
      bool kBaPgygxaP = false;
      bool NfEcGUJbCY = false;
      bool oafOgVxwnY = false;
      bool FcUXRYtRrn = false;
      bool LRdoyBZxwu = false;
      bool oTytTKUMiK = false;
      bool BkJCJjLfLg = false;
      bool aqiONXwpQe = false;
      bool uAzsildaEH = false;
      bool EhhglZHafN = false;
      bool ptkOTxjjgu = false;
      bool NdwEOAkQTW = false;
      string IGZTEqLbYp;
      string XUgqrXykZf;
      string ikuLUCTRrX;
      string DXHTapdDNo;
      string mYOIAaisMr;
      string dfKUzWLNzB;
      string XsiAlAMMQC;
      string stWjsJWmLs;
      string TZFAtXMmUD;
      string ePELQsoNVA;
      string NVbKyiIZbo;
      string AXCFgxniGO;
      string nZrNXdpLTz;
      string TJQLeyxtBK;
      string OlKfDGNydT;
      string FFHHLncOmU;
      string sxGcUqGqai;
      string zshuzCOMKQ;
      string PqgzsNBJzp;
      string UiHfQRehKL;
      if(IGZTEqLbYp == NVbKyiIZbo){zWXuTMXLHJ = true;}
      else if(NVbKyiIZbo == IGZTEqLbYp){oafOgVxwnY = true;}
      if(XUgqrXykZf == AXCFgxniGO){YQDVFCQGiG = true;}
      else if(AXCFgxniGO == XUgqrXykZf){FcUXRYtRrn = true;}
      if(ikuLUCTRrX == nZrNXdpLTz){oxqjNQlCeh = true;}
      else if(nZrNXdpLTz == ikuLUCTRrX){LRdoyBZxwu = true;}
      if(DXHTapdDNo == TJQLeyxtBK){WfByRsTkfg = true;}
      else if(TJQLeyxtBK == DXHTapdDNo){oTytTKUMiK = true;}
      if(mYOIAaisMr == OlKfDGNydT){ppBoREfkaO = true;}
      else if(OlKfDGNydT == mYOIAaisMr){BkJCJjLfLg = true;}
      if(dfKUzWLNzB == FFHHLncOmU){BXyEWBemgC = true;}
      else if(FFHHLncOmU == dfKUzWLNzB){aqiONXwpQe = true;}
      if(XsiAlAMMQC == sxGcUqGqai){ZVgZmsOEEL = true;}
      else if(sxGcUqGqai == XsiAlAMMQC){uAzsildaEH = true;}
      if(stWjsJWmLs == zshuzCOMKQ){heaCPywBSJ = true;}
      if(TZFAtXMmUD == PqgzsNBJzp){kBaPgygxaP = true;}
      if(ePELQsoNVA == UiHfQRehKL){NfEcGUJbCY = true;}
      while(zshuzCOMKQ == stWjsJWmLs){EhhglZHafN = true;}
      while(PqgzsNBJzp == PqgzsNBJzp){ptkOTxjjgu = true;}
      while(UiHfQRehKL == UiHfQRehKL){NdwEOAkQTW = true;}
      if(zWXuTMXLHJ == true){zWXuTMXLHJ = false;}
      if(YQDVFCQGiG == true){YQDVFCQGiG = false;}
      if(oxqjNQlCeh == true){oxqjNQlCeh = false;}
      if(WfByRsTkfg == true){WfByRsTkfg = false;}
      if(ppBoREfkaO == true){ppBoREfkaO = false;}
      if(BXyEWBemgC == true){BXyEWBemgC = false;}
      if(ZVgZmsOEEL == true){ZVgZmsOEEL = false;}
      if(heaCPywBSJ == true){heaCPywBSJ = false;}
      if(kBaPgygxaP == true){kBaPgygxaP = false;}
      if(NfEcGUJbCY == true){NfEcGUJbCY = false;}
      if(oafOgVxwnY == true){oafOgVxwnY = false;}
      if(FcUXRYtRrn == true){FcUXRYtRrn = false;}
      if(LRdoyBZxwu == true){LRdoyBZxwu = false;}
      if(oTytTKUMiK == true){oTytTKUMiK = false;}
      if(BkJCJjLfLg == true){BkJCJjLfLg = false;}
      if(aqiONXwpQe == true){aqiONXwpQe = false;}
      if(uAzsildaEH == true){uAzsildaEH = false;}
      if(EhhglZHafN == true){EhhglZHafN = false;}
      if(ptkOTxjjgu == true){ptkOTxjjgu = false;}
      if(NdwEOAkQTW == true){NdwEOAkQTW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NBJMLPLDET
{ 
  void hQdxBNGSra()
  { 
      bool ZtebioRTut = false;
      bool loucpCMfck = false;
      bool hlRONklBWG = false;
      bool tjNXqXnqhz = false;
      bool SJmDwlLQcS = false;
      bool aTwhFncPNx = false;
      bool DPxnABbXkS = false;
      bool NUycSYzNSa = false;
      bool YVXDfanfSD = false;
      bool uYdjwCMyDt = false;
      bool KnfKEFVSOg = false;
      bool oOwmXhrsIZ = false;
      bool NwEhWoqNgQ = false;
      bool MAKYQkoMyZ = false;
      bool EUQlNfbpMO = false;
      bool JSocgNixnP = false;
      bool OHlyUnEXWm = false;
      bool reuiUsfSTp = false;
      bool NBBSGsLgqC = false;
      bool BrYiKxhRQZ = false;
      string aXNwNQaGXz;
      string ATjLWdFbNK;
      string IitnsiVIrb;
      string uQyhuTmFjg;
      string IAtLSSskLc;
      string RIYeBrcZCd;
      string tROwDjUCPD;
      string pzqgBIohVa;
      string pkwPKmqTgD;
      string pNDFlqkyIh;
      string xqUIlRRrcr;
      string DuDanJUykQ;
      string sBUMNcuktK;
      string WpZmdyPncr;
      string UyqnAuJbRc;
      string VmMqowVItJ;
      string WgyRVMUPxp;
      string sfUrutJfMR;
      string STTRojdiyh;
      string bHsTVnAZSn;
      if(aXNwNQaGXz == xqUIlRRrcr){ZtebioRTut = true;}
      else if(xqUIlRRrcr == aXNwNQaGXz){KnfKEFVSOg = true;}
      if(ATjLWdFbNK == DuDanJUykQ){loucpCMfck = true;}
      else if(DuDanJUykQ == ATjLWdFbNK){oOwmXhrsIZ = true;}
      if(IitnsiVIrb == sBUMNcuktK){hlRONklBWG = true;}
      else if(sBUMNcuktK == IitnsiVIrb){NwEhWoqNgQ = true;}
      if(uQyhuTmFjg == WpZmdyPncr){tjNXqXnqhz = true;}
      else if(WpZmdyPncr == uQyhuTmFjg){MAKYQkoMyZ = true;}
      if(IAtLSSskLc == UyqnAuJbRc){SJmDwlLQcS = true;}
      else if(UyqnAuJbRc == IAtLSSskLc){EUQlNfbpMO = true;}
      if(RIYeBrcZCd == VmMqowVItJ){aTwhFncPNx = true;}
      else if(VmMqowVItJ == RIYeBrcZCd){JSocgNixnP = true;}
      if(tROwDjUCPD == WgyRVMUPxp){DPxnABbXkS = true;}
      else if(WgyRVMUPxp == tROwDjUCPD){OHlyUnEXWm = true;}
      if(pzqgBIohVa == sfUrutJfMR){NUycSYzNSa = true;}
      if(pkwPKmqTgD == STTRojdiyh){YVXDfanfSD = true;}
      if(pNDFlqkyIh == bHsTVnAZSn){uYdjwCMyDt = true;}
      while(sfUrutJfMR == pzqgBIohVa){reuiUsfSTp = true;}
      while(STTRojdiyh == STTRojdiyh){NBBSGsLgqC = true;}
      while(bHsTVnAZSn == bHsTVnAZSn){BrYiKxhRQZ = true;}
      if(ZtebioRTut == true){ZtebioRTut = false;}
      if(loucpCMfck == true){loucpCMfck = false;}
      if(hlRONklBWG == true){hlRONklBWG = false;}
      if(tjNXqXnqhz == true){tjNXqXnqhz = false;}
      if(SJmDwlLQcS == true){SJmDwlLQcS = false;}
      if(aTwhFncPNx == true){aTwhFncPNx = false;}
      if(DPxnABbXkS == true){DPxnABbXkS = false;}
      if(NUycSYzNSa == true){NUycSYzNSa = false;}
      if(YVXDfanfSD == true){YVXDfanfSD = false;}
      if(uYdjwCMyDt == true){uYdjwCMyDt = false;}
      if(KnfKEFVSOg == true){KnfKEFVSOg = false;}
      if(oOwmXhrsIZ == true){oOwmXhrsIZ = false;}
      if(NwEhWoqNgQ == true){NwEhWoqNgQ = false;}
      if(MAKYQkoMyZ == true){MAKYQkoMyZ = false;}
      if(EUQlNfbpMO == true){EUQlNfbpMO = false;}
      if(JSocgNixnP == true){JSocgNixnP = false;}
      if(OHlyUnEXWm == true){OHlyUnEXWm = false;}
      if(reuiUsfSTp == true){reuiUsfSTp = false;}
      if(NBBSGsLgqC == true){NBBSGsLgqC = false;}
      if(BrYiKxhRQZ == true){BrYiKxhRQZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJIAIYVTYI
{ 
  void wISPFlOnOP()
  { 
      bool gNBQTqMtQh = false;
      bool oTctfQdQNz = false;
      bool OFYpbNytbV = false;
      bool POxjdgLoda = false;
      bool ISrAoaXWxc = false;
      bool rVTmVanKoG = false;
      bool sRRuRaVsQy = false;
      bool FnllqwNYBA = false;
      bool oawzcttKNC = false;
      bool rAAXhpAxhO = false;
      bool EeGzWDigwZ = false;
      bool NPJoQSVSRX = false;
      bool fLeOFEnNEA = false;
      bool wPpluKTxbY = false;
      bool KMOnncqKHP = false;
      bool UheJiszrsS = false;
      bool PUcudxYWsG = false;
      bool yXprNSwqZc = false;
      bool NcGofNjfDB = false;
      bool KbEJJojTKq = false;
      string HWqsWxDgJE;
      string XcqGSEyaNj;
      string CRQEsIHgHj;
      string TUuVHhmHXl;
      string QkgrsePdxK;
      string ChXZpoFmAO;
      string pWYZjCgVzj;
      string RpDbTQjYKO;
      string rcjxhlxUfR;
      string czHJusLHHp;
      string xseMsLeuGY;
      string EgckVMmbqy;
      string ELpgHRhtfZ;
      string EcRTQyyWEV;
      string GCOGMwWVmh;
      string GjPIklDxFa;
      string cjOgTbOIUW;
      string OPXVrCwjUK;
      string uMGySUMIid;
      string uBRcsVmhlk;
      if(HWqsWxDgJE == xseMsLeuGY){gNBQTqMtQh = true;}
      else if(xseMsLeuGY == HWqsWxDgJE){EeGzWDigwZ = true;}
      if(XcqGSEyaNj == EgckVMmbqy){oTctfQdQNz = true;}
      else if(EgckVMmbqy == XcqGSEyaNj){NPJoQSVSRX = true;}
      if(CRQEsIHgHj == ELpgHRhtfZ){OFYpbNytbV = true;}
      else if(ELpgHRhtfZ == CRQEsIHgHj){fLeOFEnNEA = true;}
      if(TUuVHhmHXl == EcRTQyyWEV){POxjdgLoda = true;}
      else if(EcRTQyyWEV == TUuVHhmHXl){wPpluKTxbY = true;}
      if(QkgrsePdxK == GCOGMwWVmh){ISrAoaXWxc = true;}
      else if(GCOGMwWVmh == QkgrsePdxK){KMOnncqKHP = true;}
      if(ChXZpoFmAO == GjPIklDxFa){rVTmVanKoG = true;}
      else if(GjPIklDxFa == ChXZpoFmAO){UheJiszrsS = true;}
      if(pWYZjCgVzj == cjOgTbOIUW){sRRuRaVsQy = true;}
      else if(cjOgTbOIUW == pWYZjCgVzj){PUcudxYWsG = true;}
      if(RpDbTQjYKO == OPXVrCwjUK){FnllqwNYBA = true;}
      if(rcjxhlxUfR == uMGySUMIid){oawzcttKNC = true;}
      if(czHJusLHHp == uBRcsVmhlk){rAAXhpAxhO = true;}
      while(OPXVrCwjUK == RpDbTQjYKO){yXprNSwqZc = true;}
      while(uMGySUMIid == uMGySUMIid){NcGofNjfDB = true;}
      while(uBRcsVmhlk == uBRcsVmhlk){KbEJJojTKq = true;}
      if(gNBQTqMtQh == true){gNBQTqMtQh = false;}
      if(oTctfQdQNz == true){oTctfQdQNz = false;}
      if(OFYpbNytbV == true){OFYpbNytbV = false;}
      if(POxjdgLoda == true){POxjdgLoda = false;}
      if(ISrAoaXWxc == true){ISrAoaXWxc = false;}
      if(rVTmVanKoG == true){rVTmVanKoG = false;}
      if(sRRuRaVsQy == true){sRRuRaVsQy = false;}
      if(FnllqwNYBA == true){FnllqwNYBA = false;}
      if(oawzcttKNC == true){oawzcttKNC = false;}
      if(rAAXhpAxhO == true){rAAXhpAxhO = false;}
      if(EeGzWDigwZ == true){EeGzWDigwZ = false;}
      if(NPJoQSVSRX == true){NPJoQSVSRX = false;}
      if(fLeOFEnNEA == true){fLeOFEnNEA = false;}
      if(wPpluKTxbY == true){wPpluKTxbY = false;}
      if(KMOnncqKHP == true){KMOnncqKHP = false;}
      if(UheJiszrsS == true){UheJiszrsS = false;}
      if(PUcudxYWsG == true){PUcudxYWsG = false;}
      if(yXprNSwqZc == true){yXprNSwqZc = false;}
      if(NcGofNjfDB == true){NcGofNjfDB = false;}
      if(KbEJJojTKq == true){KbEJJojTKq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUWGNFAOGB
{ 
  void rkLdquGVDM()
  { 
      bool CiGOLfxlQD = false;
      bool FKNdEGqGOs = false;
      bool OejkyozwZM = false;
      bool PWKTWxREPC = false;
      bool GjUTbaMwjd = false;
      bool ouZmuXyUQW = false;
      bool gBMDmhAsGG = false;
      bool nmqMldJQJW = false;
      bool bCMwXUwWYz = false;
      bool zwmsUFXRfs = false;
      bool aSpcoCENAQ = false;
      bool NhLttdoPeS = false;
      bool lcUHHqzyqg = false;
      bool GrjPuJMiHV = false;
      bool QhWHkQkryq = false;
      bool QImNGyyhUx = false;
      bool CGVTKVyuzk = false;
      bool QFHJBDGMVq = false;
      bool GGzAPxFVIx = false;
      bool LeOJTKMCwP = false;
      string kxhdXsWHmy;
      string okYWIgJLnn;
      string UmsNAgatMQ;
      string rRNiyjOTRb;
      string nntBumPpUb;
      string UWxmRxEUcq;
      string ScuVGWXoYY;
      string SpsMAgrqRM;
      string QjZjuUUZQA;
      string ftpZJKsXuX;
      string OaQuJedkmk;
      string FMCQahDKak;
      string CyXYrYzSCo;
      string mTwtxpSdZP;
      string qjlfuSqZza;
      string GhxKVQDrDk;
      string fKhxykQISk;
      string PZkKtRLrdY;
      string gYSaiEWkXg;
      string laZnjgBogJ;
      if(kxhdXsWHmy == OaQuJedkmk){CiGOLfxlQD = true;}
      else if(OaQuJedkmk == kxhdXsWHmy){aSpcoCENAQ = true;}
      if(okYWIgJLnn == FMCQahDKak){FKNdEGqGOs = true;}
      else if(FMCQahDKak == okYWIgJLnn){NhLttdoPeS = true;}
      if(UmsNAgatMQ == CyXYrYzSCo){OejkyozwZM = true;}
      else if(CyXYrYzSCo == UmsNAgatMQ){lcUHHqzyqg = true;}
      if(rRNiyjOTRb == mTwtxpSdZP){PWKTWxREPC = true;}
      else if(mTwtxpSdZP == rRNiyjOTRb){GrjPuJMiHV = true;}
      if(nntBumPpUb == qjlfuSqZza){GjUTbaMwjd = true;}
      else if(qjlfuSqZza == nntBumPpUb){QhWHkQkryq = true;}
      if(UWxmRxEUcq == GhxKVQDrDk){ouZmuXyUQW = true;}
      else if(GhxKVQDrDk == UWxmRxEUcq){QImNGyyhUx = true;}
      if(ScuVGWXoYY == fKhxykQISk){gBMDmhAsGG = true;}
      else if(fKhxykQISk == ScuVGWXoYY){CGVTKVyuzk = true;}
      if(SpsMAgrqRM == PZkKtRLrdY){nmqMldJQJW = true;}
      if(QjZjuUUZQA == gYSaiEWkXg){bCMwXUwWYz = true;}
      if(ftpZJKsXuX == laZnjgBogJ){zwmsUFXRfs = true;}
      while(PZkKtRLrdY == SpsMAgrqRM){QFHJBDGMVq = true;}
      while(gYSaiEWkXg == gYSaiEWkXg){GGzAPxFVIx = true;}
      while(laZnjgBogJ == laZnjgBogJ){LeOJTKMCwP = true;}
      if(CiGOLfxlQD == true){CiGOLfxlQD = false;}
      if(FKNdEGqGOs == true){FKNdEGqGOs = false;}
      if(OejkyozwZM == true){OejkyozwZM = false;}
      if(PWKTWxREPC == true){PWKTWxREPC = false;}
      if(GjUTbaMwjd == true){GjUTbaMwjd = false;}
      if(ouZmuXyUQW == true){ouZmuXyUQW = false;}
      if(gBMDmhAsGG == true){gBMDmhAsGG = false;}
      if(nmqMldJQJW == true){nmqMldJQJW = false;}
      if(bCMwXUwWYz == true){bCMwXUwWYz = false;}
      if(zwmsUFXRfs == true){zwmsUFXRfs = false;}
      if(aSpcoCENAQ == true){aSpcoCENAQ = false;}
      if(NhLttdoPeS == true){NhLttdoPeS = false;}
      if(lcUHHqzyqg == true){lcUHHqzyqg = false;}
      if(GrjPuJMiHV == true){GrjPuJMiHV = false;}
      if(QhWHkQkryq == true){QhWHkQkryq = false;}
      if(QImNGyyhUx == true){QImNGyyhUx = false;}
      if(CGVTKVyuzk == true){CGVTKVyuzk = false;}
      if(QFHJBDGMVq == true){QFHJBDGMVq = false;}
      if(GGzAPxFVIx == true){GGzAPxFVIx = false;}
      if(LeOJTKMCwP == true){LeOJTKMCwP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDDVADRMEF
{ 
  void oThQCPWQTL()
  { 
      bool yCPGMtSxZe = false;
      bool YkGxzclfja = false;
      bool rFuBNAUdJZ = false;
      bool ZrInNRySIk = false;
      bool OHmTJzlCOE = false;
      bool bxhDqrHNsM = false;
      bool YnmzEfbRjh = false;
      bool dTWyLkSbrO = false;
      bool NSOFxbKEwU = false;
      bool JjYwLZTmOc = false;
      bool WTRgaIaiqG = false;
      bool ZfVezGZhBc = false;
      bool VWUPXstZll = false;
      bool QeMOqsAgdo = false;
      bool BaMptdOtxF = false;
      bool AlkkGzzCJg = false;
      bool OAxFpuSGmF = false;
      bool FrDMbuKeUs = false;
      bool ezcgkdsaIr = false;
      bool txWxZAdGAy = false;
      string dVazWAAkhd;
      string bWYjHeHLDF;
      string KrSDELWZpq;
      string xkmOIQrtVC;
      string SgtLGLHMdX;
      string PfdwdlDWtK;
      string dZtpgpiKaq;
      string mMoAmdxHws;
      string EKwSaQHqkV;
      string NVAKYrlEeQ;
      string bwkmjDpcJz;
      string ouZBFSdaPP;
      string hrYFdQMebt;
      string rscfRHYJhX;
      string ZeglfRwyEG;
      string OKnOhiXfJT;
      string pLBPHwSsix;
      string sUrqoDKmYL;
      string UNZUegENyh;
      string jszOgOdRdj;
      if(dVazWAAkhd == bwkmjDpcJz){yCPGMtSxZe = true;}
      else if(bwkmjDpcJz == dVazWAAkhd){WTRgaIaiqG = true;}
      if(bWYjHeHLDF == ouZBFSdaPP){YkGxzclfja = true;}
      else if(ouZBFSdaPP == bWYjHeHLDF){ZfVezGZhBc = true;}
      if(KrSDELWZpq == hrYFdQMebt){rFuBNAUdJZ = true;}
      else if(hrYFdQMebt == KrSDELWZpq){VWUPXstZll = true;}
      if(xkmOIQrtVC == rscfRHYJhX){ZrInNRySIk = true;}
      else if(rscfRHYJhX == xkmOIQrtVC){QeMOqsAgdo = true;}
      if(SgtLGLHMdX == ZeglfRwyEG){OHmTJzlCOE = true;}
      else if(ZeglfRwyEG == SgtLGLHMdX){BaMptdOtxF = true;}
      if(PfdwdlDWtK == OKnOhiXfJT){bxhDqrHNsM = true;}
      else if(OKnOhiXfJT == PfdwdlDWtK){AlkkGzzCJg = true;}
      if(dZtpgpiKaq == pLBPHwSsix){YnmzEfbRjh = true;}
      else if(pLBPHwSsix == dZtpgpiKaq){OAxFpuSGmF = true;}
      if(mMoAmdxHws == sUrqoDKmYL){dTWyLkSbrO = true;}
      if(EKwSaQHqkV == UNZUegENyh){NSOFxbKEwU = true;}
      if(NVAKYrlEeQ == jszOgOdRdj){JjYwLZTmOc = true;}
      while(sUrqoDKmYL == mMoAmdxHws){FrDMbuKeUs = true;}
      while(UNZUegENyh == UNZUegENyh){ezcgkdsaIr = true;}
      while(jszOgOdRdj == jszOgOdRdj){txWxZAdGAy = true;}
      if(yCPGMtSxZe == true){yCPGMtSxZe = false;}
      if(YkGxzclfja == true){YkGxzclfja = false;}
      if(rFuBNAUdJZ == true){rFuBNAUdJZ = false;}
      if(ZrInNRySIk == true){ZrInNRySIk = false;}
      if(OHmTJzlCOE == true){OHmTJzlCOE = false;}
      if(bxhDqrHNsM == true){bxhDqrHNsM = false;}
      if(YnmzEfbRjh == true){YnmzEfbRjh = false;}
      if(dTWyLkSbrO == true){dTWyLkSbrO = false;}
      if(NSOFxbKEwU == true){NSOFxbKEwU = false;}
      if(JjYwLZTmOc == true){JjYwLZTmOc = false;}
      if(WTRgaIaiqG == true){WTRgaIaiqG = false;}
      if(ZfVezGZhBc == true){ZfVezGZhBc = false;}
      if(VWUPXstZll == true){VWUPXstZll = false;}
      if(QeMOqsAgdo == true){QeMOqsAgdo = false;}
      if(BaMptdOtxF == true){BaMptdOtxF = false;}
      if(AlkkGzzCJg == true){AlkkGzzCJg = false;}
      if(OAxFpuSGmF == true){OAxFpuSGmF = false;}
      if(FrDMbuKeUs == true){FrDMbuKeUs = false;}
      if(ezcgkdsaIr == true){ezcgkdsaIr = false;}
      if(txWxZAdGAy == true){txWxZAdGAy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRWZNPRTFZ
{ 
  void KXqjJTJEXr()
  { 
      bool NzJRePloDJ = false;
      bool HmqrsEMKnj = false;
      bool fClUfmrqhS = false;
      bool hMKmWuDbps = false;
      bool BQqAOzJZCC = false;
      bool JgbEnLMnkq = false;
      bool WtHkbucDVy = false;
      bool AkTthPKlFg = false;
      bool dRneJAjFzK = false;
      bool iOpzWHIGXS = false;
      bool VFEEBXMhWY = false;
      bool BZiEMEFbba = false;
      bool KWELOkuUXZ = false;
      bool GEOlKYNjdk = false;
      bool nCiaIIflmR = false;
      bool BgdxHyBsoP = false;
      bool crKwRxLwsn = false;
      bool qVxqmIncCF = false;
      bool FIhFXYZQdL = false;
      bool WUtNHwrlIL = false;
      string ZdPVrQWGJn;
      string BZCKgcqBIb;
      string weqypbOsTt;
      string HKptVkBdsK;
      string LjFqXIFBVF;
      string qsRxxumQeP;
      string CdlPfpiHnu;
      string aMIxQLZAag;
      string WMWOCNrsxa;
      string ykydIgypLg;
      string ZxMZdekUfk;
      string UloyroHXMR;
      string xoKNxpNeni;
      string NiosHZAwjX;
      string cXMLFLuAkT;
      string ZZdsijlzcn;
      string RGfxXlxwqS;
      string oKnnoZbyHk;
      string tMsUInFuJW;
      string mBSwGWrPnT;
      if(ZdPVrQWGJn == ZxMZdekUfk){NzJRePloDJ = true;}
      else if(ZxMZdekUfk == ZdPVrQWGJn){VFEEBXMhWY = true;}
      if(BZCKgcqBIb == UloyroHXMR){HmqrsEMKnj = true;}
      else if(UloyroHXMR == BZCKgcqBIb){BZiEMEFbba = true;}
      if(weqypbOsTt == xoKNxpNeni){fClUfmrqhS = true;}
      else if(xoKNxpNeni == weqypbOsTt){KWELOkuUXZ = true;}
      if(HKptVkBdsK == NiosHZAwjX){hMKmWuDbps = true;}
      else if(NiosHZAwjX == HKptVkBdsK){GEOlKYNjdk = true;}
      if(LjFqXIFBVF == cXMLFLuAkT){BQqAOzJZCC = true;}
      else if(cXMLFLuAkT == LjFqXIFBVF){nCiaIIflmR = true;}
      if(qsRxxumQeP == ZZdsijlzcn){JgbEnLMnkq = true;}
      else if(ZZdsijlzcn == qsRxxumQeP){BgdxHyBsoP = true;}
      if(CdlPfpiHnu == RGfxXlxwqS){WtHkbucDVy = true;}
      else if(RGfxXlxwqS == CdlPfpiHnu){crKwRxLwsn = true;}
      if(aMIxQLZAag == oKnnoZbyHk){AkTthPKlFg = true;}
      if(WMWOCNrsxa == tMsUInFuJW){dRneJAjFzK = true;}
      if(ykydIgypLg == mBSwGWrPnT){iOpzWHIGXS = true;}
      while(oKnnoZbyHk == aMIxQLZAag){qVxqmIncCF = true;}
      while(tMsUInFuJW == tMsUInFuJW){FIhFXYZQdL = true;}
      while(mBSwGWrPnT == mBSwGWrPnT){WUtNHwrlIL = true;}
      if(NzJRePloDJ == true){NzJRePloDJ = false;}
      if(HmqrsEMKnj == true){HmqrsEMKnj = false;}
      if(fClUfmrqhS == true){fClUfmrqhS = false;}
      if(hMKmWuDbps == true){hMKmWuDbps = false;}
      if(BQqAOzJZCC == true){BQqAOzJZCC = false;}
      if(JgbEnLMnkq == true){JgbEnLMnkq = false;}
      if(WtHkbucDVy == true){WtHkbucDVy = false;}
      if(AkTthPKlFg == true){AkTthPKlFg = false;}
      if(dRneJAjFzK == true){dRneJAjFzK = false;}
      if(iOpzWHIGXS == true){iOpzWHIGXS = false;}
      if(VFEEBXMhWY == true){VFEEBXMhWY = false;}
      if(BZiEMEFbba == true){BZiEMEFbba = false;}
      if(KWELOkuUXZ == true){KWELOkuUXZ = false;}
      if(GEOlKYNjdk == true){GEOlKYNjdk = false;}
      if(nCiaIIflmR == true){nCiaIIflmR = false;}
      if(BgdxHyBsoP == true){BgdxHyBsoP = false;}
      if(crKwRxLwsn == true){crKwRxLwsn = false;}
      if(qVxqmIncCF == true){qVxqmIncCF = false;}
      if(FIhFXYZQdL == true){FIhFXYZQdL = false;}
      if(WUtNHwrlIL == true){WUtNHwrlIL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGLBLFWXBN
{ 
  void Jmyssmauim()
  { 
      bool hZeOIdfmoT = false;
      bool ozZKpBkkKp = false;
      bool GPkWXcYwLt = false;
      bool nzPlPujPpc = false;
      bool EIldorebsj = false;
      bool pLgQjRoHqe = false;
      bool Fibufoimtt = false;
      bool RUuglxdGhe = false;
      bool yxCbEcSzCy = false;
      bool GcXLXUgqxz = false;
      bool IrgyRUQzdl = false;
      bool mhYLgHgzpD = false;
      bool VjkwnnwjJR = false;
      bool PlIiWFQDJi = false;
      bool MTUQKXDMdP = false;
      bool mhBtcYHjKd = false;
      bool XfoMVBYpoa = false;
      bool qcoGqCOTkQ = false;
      bool kjFtdhkOFy = false;
      bool yfsfKfeHtI = false;
      string YygxlaRWgh;
      string ZBWgXehpaU;
      string uUIUtVEjFQ;
      string FCdOhuFtYD;
      string cIByuEhXJQ;
      string ApuGKDoLCQ;
      string WgRPbXXHzc;
      string YnRWrmTJZp;
      string nfanPPGXEd;
      string FtrHgupkWW;
      string fZXfqMYYOW;
      string jekLcpGdAL;
      string RADVXeuJow;
      string whmCKNHtxC;
      string pgIgsZIfdq;
      string oMkKFfVCIM;
      string QPjRZCrhBP;
      string hLgxVkqWcx;
      string VPeyHjwbxd;
      string qFljkaxqGp;
      if(YygxlaRWgh == fZXfqMYYOW){hZeOIdfmoT = true;}
      else if(fZXfqMYYOW == YygxlaRWgh){IrgyRUQzdl = true;}
      if(ZBWgXehpaU == jekLcpGdAL){ozZKpBkkKp = true;}
      else if(jekLcpGdAL == ZBWgXehpaU){mhYLgHgzpD = true;}
      if(uUIUtVEjFQ == RADVXeuJow){GPkWXcYwLt = true;}
      else if(RADVXeuJow == uUIUtVEjFQ){VjkwnnwjJR = true;}
      if(FCdOhuFtYD == whmCKNHtxC){nzPlPujPpc = true;}
      else if(whmCKNHtxC == FCdOhuFtYD){PlIiWFQDJi = true;}
      if(cIByuEhXJQ == pgIgsZIfdq){EIldorebsj = true;}
      else if(pgIgsZIfdq == cIByuEhXJQ){MTUQKXDMdP = true;}
      if(ApuGKDoLCQ == oMkKFfVCIM){pLgQjRoHqe = true;}
      else if(oMkKFfVCIM == ApuGKDoLCQ){mhBtcYHjKd = true;}
      if(WgRPbXXHzc == QPjRZCrhBP){Fibufoimtt = true;}
      else if(QPjRZCrhBP == WgRPbXXHzc){XfoMVBYpoa = true;}
      if(YnRWrmTJZp == hLgxVkqWcx){RUuglxdGhe = true;}
      if(nfanPPGXEd == VPeyHjwbxd){yxCbEcSzCy = true;}
      if(FtrHgupkWW == qFljkaxqGp){GcXLXUgqxz = true;}
      while(hLgxVkqWcx == YnRWrmTJZp){qcoGqCOTkQ = true;}
      while(VPeyHjwbxd == VPeyHjwbxd){kjFtdhkOFy = true;}
      while(qFljkaxqGp == qFljkaxqGp){yfsfKfeHtI = true;}
      if(hZeOIdfmoT == true){hZeOIdfmoT = false;}
      if(ozZKpBkkKp == true){ozZKpBkkKp = false;}
      if(GPkWXcYwLt == true){GPkWXcYwLt = false;}
      if(nzPlPujPpc == true){nzPlPujPpc = false;}
      if(EIldorebsj == true){EIldorebsj = false;}
      if(pLgQjRoHqe == true){pLgQjRoHqe = false;}
      if(Fibufoimtt == true){Fibufoimtt = false;}
      if(RUuglxdGhe == true){RUuglxdGhe = false;}
      if(yxCbEcSzCy == true){yxCbEcSzCy = false;}
      if(GcXLXUgqxz == true){GcXLXUgqxz = false;}
      if(IrgyRUQzdl == true){IrgyRUQzdl = false;}
      if(mhYLgHgzpD == true){mhYLgHgzpD = false;}
      if(VjkwnnwjJR == true){VjkwnnwjJR = false;}
      if(PlIiWFQDJi == true){PlIiWFQDJi = false;}
      if(MTUQKXDMdP == true){MTUQKXDMdP = false;}
      if(mhBtcYHjKd == true){mhBtcYHjKd = false;}
      if(XfoMVBYpoa == true){XfoMVBYpoa = false;}
      if(qcoGqCOTkQ == true){qcoGqCOTkQ = false;}
      if(kjFtdhkOFy == true){kjFtdhkOFy = false;}
      if(yfsfKfeHtI == true){yfsfKfeHtI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYKLJJQIDV
{ 
  void dGEqokVaOK()
  { 
      bool DUDVcZWIty = false;
      bool DhSSlaTDws = false;
      bool NcsqgPNQZs = false;
      bool pKRNWXGsjh = false;
      bool rcIFKrsDex = false;
      bool zDIdkZaMnN = false;
      bool LGhAIsQFuO = false;
      bool UaSOBjUmfo = false;
      bool WKlbtlBmbx = false;
      bool xsEVVktHxR = false;
      bool amIPcXkscB = false;
      bool FmfzqBUGGV = false;
      bool qcdxRaWwsP = false;
      bool oMpONiBVyV = false;
      bool BIJarJNFeT = false;
      bool QnBaaxJKyC = false;
      bool BnANLrxQkH = false;
      bool zyHkUiTCFH = false;
      bool MQRZyBLOnP = false;
      bool ZqWwTNHwOz = false;
      string oVVwLUSWJc;
      string HpXmcGkGLE;
      string JqzHdPVBEm;
      string gfhsmueQeV;
      string bDjSqBXojR;
      string YCYAiyWNRw;
      string yQSVuaHezh;
      string bTaocGGgPc;
      string qfRmOeGgJo;
      string YQziWKkOWP;
      string tsoCpFbiXc;
      string qoyoFRzeHP;
      string UZVKJKTrSS;
      string UrJzixqOwJ;
      string DXJfyiSKcE;
      string KFGHuTXere;
      string kiQEIzfyGH;
      string ajhyMxPoMZ;
      string rJONHOkCEO;
      string ZLVRYTGFXz;
      if(oVVwLUSWJc == tsoCpFbiXc){DUDVcZWIty = true;}
      else if(tsoCpFbiXc == oVVwLUSWJc){amIPcXkscB = true;}
      if(HpXmcGkGLE == qoyoFRzeHP){DhSSlaTDws = true;}
      else if(qoyoFRzeHP == HpXmcGkGLE){FmfzqBUGGV = true;}
      if(JqzHdPVBEm == UZVKJKTrSS){NcsqgPNQZs = true;}
      else if(UZVKJKTrSS == JqzHdPVBEm){qcdxRaWwsP = true;}
      if(gfhsmueQeV == UrJzixqOwJ){pKRNWXGsjh = true;}
      else if(UrJzixqOwJ == gfhsmueQeV){oMpONiBVyV = true;}
      if(bDjSqBXojR == DXJfyiSKcE){rcIFKrsDex = true;}
      else if(DXJfyiSKcE == bDjSqBXojR){BIJarJNFeT = true;}
      if(YCYAiyWNRw == KFGHuTXere){zDIdkZaMnN = true;}
      else if(KFGHuTXere == YCYAiyWNRw){QnBaaxJKyC = true;}
      if(yQSVuaHezh == kiQEIzfyGH){LGhAIsQFuO = true;}
      else if(kiQEIzfyGH == yQSVuaHezh){BnANLrxQkH = true;}
      if(bTaocGGgPc == ajhyMxPoMZ){UaSOBjUmfo = true;}
      if(qfRmOeGgJo == rJONHOkCEO){WKlbtlBmbx = true;}
      if(YQziWKkOWP == ZLVRYTGFXz){xsEVVktHxR = true;}
      while(ajhyMxPoMZ == bTaocGGgPc){zyHkUiTCFH = true;}
      while(rJONHOkCEO == rJONHOkCEO){MQRZyBLOnP = true;}
      while(ZLVRYTGFXz == ZLVRYTGFXz){ZqWwTNHwOz = true;}
      if(DUDVcZWIty == true){DUDVcZWIty = false;}
      if(DhSSlaTDws == true){DhSSlaTDws = false;}
      if(NcsqgPNQZs == true){NcsqgPNQZs = false;}
      if(pKRNWXGsjh == true){pKRNWXGsjh = false;}
      if(rcIFKrsDex == true){rcIFKrsDex = false;}
      if(zDIdkZaMnN == true){zDIdkZaMnN = false;}
      if(LGhAIsQFuO == true){LGhAIsQFuO = false;}
      if(UaSOBjUmfo == true){UaSOBjUmfo = false;}
      if(WKlbtlBmbx == true){WKlbtlBmbx = false;}
      if(xsEVVktHxR == true){xsEVVktHxR = false;}
      if(amIPcXkscB == true){amIPcXkscB = false;}
      if(FmfzqBUGGV == true){FmfzqBUGGV = false;}
      if(qcdxRaWwsP == true){qcdxRaWwsP = false;}
      if(oMpONiBVyV == true){oMpONiBVyV = false;}
      if(BIJarJNFeT == true){BIJarJNFeT = false;}
      if(QnBaaxJKyC == true){QnBaaxJKyC = false;}
      if(BnANLrxQkH == true){BnANLrxQkH = false;}
      if(zyHkUiTCFH == true){zyHkUiTCFH = false;}
      if(MQRZyBLOnP == true){MQRZyBLOnP = false;}
      if(ZqWwTNHwOz == true){ZqWwTNHwOz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVYAULYODY
{ 
  void dimWfbWSiW()
  { 
      bool TMmPfALVun = false;
      bool KYtbWuQijV = false;
      bool NQWWVgXYWl = false;
      bool dkkRUxxglQ = false;
      bool ZVMqMCpFjk = false;
      bool nJSDqCpPsy = false;
      bool blyIKYmcHY = false;
      bool yjxTuqEeJT = false;
      bool pSokyTShZS = false;
      bool GgnmnmXDfn = false;
      bool ONxKmEMzHz = false;
      bool yKFYHJxMKp = false;
      bool FFCoRQuKeH = false;
      bool TAzVFcUdyt = false;
      bool HTZaTwaPed = false;
      bool pKsohJKIsW = false;
      bool IBTAfyLjSe = false;
      bool oSOQilfbUV = false;
      bool pfeBRIGJnw = false;
      bool SMkbkFAZuV = false;
      string CwlxPXqBDk;
      string hCJXSGwnKw;
      string TYkYTXHolb;
      string mGjxKYWcLf;
      string MbRsEImKrp;
      string QyuHddLNcr;
      string PBPaxbSLNt;
      string iSbeiqHqTL;
      string kxwuKnKbTg;
      string NJzTPLMpwc;
      string oawyHyVQYl;
      string WTsRGRETQJ;
      string QqqfgZSIOX;
      string eQuqWJAynM;
      string RtDgKsPhMx;
      string GrYlLyiQQg;
      string fNBAHFYCux;
      string RGfDqWnKVn;
      string KjwRQlqIfX;
      string ajhGgEsCYE;
      if(CwlxPXqBDk == oawyHyVQYl){TMmPfALVun = true;}
      else if(oawyHyVQYl == CwlxPXqBDk){ONxKmEMzHz = true;}
      if(hCJXSGwnKw == WTsRGRETQJ){KYtbWuQijV = true;}
      else if(WTsRGRETQJ == hCJXSGwnKw){yKFYHJxMKp = true;}
      if(TYkYTXHolb == QqqfgZSIOX){NQWWVgXYWl = true;}
      else if(QqqfgZSIOX == TYkYTXHolb){FFCoRQuKeH = true;}
      if(mGjxKYWcLf == eQuqWJAynM){dkkRUxxglQ = true;}
      else if(eQuqWJAynM == mGjxKYWcLf){TAzVFcUdyt = true;}
      if(MbRsEImKrp == RtDgKsPhMx){ZVMqMCpFjk = true;}
      else if(RtDgKsPhMx == MbRsEImKrp){HTZaTwaPed = true;}
      if(QyuHddLNcr == GrYlLyiQQg){nJSDqCpPsy = true;}
      else if(GrYlLyiQQg == QyuHddLNcr){pKsohJKIsW = true;}
      if(PBPaxbSLNt == fNBAHFYCux){blyIKYmcHY = true;}
      else if(fNBAHFYCux == PBPaxbSLNt){IBTAfyLjSe = true;}
      if(iSbeiqHqTL == RGfDqWnKVn){yjxTuqEeJT = true;}
      if(kxwuKnKbTg == KjwRQlqIfX){pSokyTShZS = true;}
      if(NJzTPLMpwc == ajhGgEsCYE){GgnmnmXDfn = true;}
      while(RGfDqWnKVn == iSbeiqHqTL){oSOQilfbUV = true;}
      while(KjwRQlqIfX == KjwRQlqIfX){pfeBRIGJnw = true;}
      while(ajhGgEsCYE == ajhGgEsCYE){SMkbkFAZuV = true;}
      if(TMmPfALVun == true){TMmPfALVun = false;}
      if(KYtbWuQijV == true){KYtbWuQijV = false;}
      if(NQWWVgXYWl == true){NQWWVgXYWl = false;}
      if(dkkRUxxglQ == true){dkkRUxxglQ = false;}
      if(ZVMqMCpFjk == true){ZVMqMCpFjk = false;}
      if(nJSDqCpPsy == true){nJSDqCpPsy = false;}
      if(blyIKYmcHY == true){blyIKYmcHY = false;}
      if(yjxTuqEeJT == true){yjxTuqEeJT = false;}
      if(pSokyTShZS == true){pSokyTShZS = false;}
      if(GgnmnmXDfn == true){GgnmnmXDfn = false;}
      if(ONxKmEMzHz == true){ONxKmEMzHz = false;}
      if(yKFYHJxMKp == true){yKFYHJxMKp = false;}
      if(FFCoRQuKeH == true){FFCoRQuKeH = false;}
      if(TAzVFcUdyt == true){TAzVFcUdyt = false;}
      if(HTZaTwaPed == true){HTZaTwaPed = false;}
      if(pKsohJKIsW == true){pKsohJKIsW = false;}
      if(IBTAfyLjSe == true){IBTAfyLjSe = false;}
      if(oSOQilfbUV == true){oSOQilfbUV = false;}
      if(pfeBRIGJnw == true){pfeBRIGJnw = false;}
      if(SMkbkFAZuV == true){SMkbkFAZuV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WRPFHQMGWJ
{ 
  void EFjeinFsLI()
  { 
      bool uCPbIlypMe = false;
      bool ytRccZluYX = false;
      bool ouaizLYWZI = false;
      bool LybSXwtfXW = false;
      bool gSeSFiALem = false;
      bool JfVzszafcw = false;
      bool NaQESzSzFg = false;
      bool fFXBpVQIdQ = false;
      bool KMrlzebbZY = false;
      bool VNCaJGCazF = false;
      bool QBGyHDIUIW = false;
      bool hSBMlAidEn = false;
      bool XpYfKRCwrj = false;
      bool SoIYAIGsew = false;
      bool VHTCpCLpoI = false;
      bool WXVLhacZmo = false;
      bool AMbYDrJcMc = false;
      bool tozIRPVWpH = false;
      bool FMGiNuSxpZ = false;
      bool ffGpuIetyx = false;
      string rlwIRmugYN;
      string NGQMdQeNXi;
      string yBUgOamOcr;
      string WTQCKwcewC;
      string dwxBFEiBfp;
      string wZRwOqQOsq;
      string AfDgqtpOBh;
      string mzRVFCDTaK;
      string qkhmuxBTmT;
      string fNlECxsPKL;
      string OUAxCxHwpM;
      string mxmizOxPls;
      string sWahBZMNTI;
      string InIPuWkjky;
      string oEcagiZDEm;
      string zcdQSrtSwc;
      string jtchDynXmb;
      string dMemDnszAS;
      string zJIgJfJrxD;
      string cSnINubuXh;
      if(rlwIRmugYN == OUAxCxHwpM){uCPbIlypMe = true;}
      else if(OUAxCxHwpM == rlwIRmugYN){QBGyHDIUIW = true;}
      if(NGQMdQeNXi == mxmizOxPls){ytRccZluYX = true;}
      else if(mxmizOxPls == NGQMdQeNXi){hSBMlAidEn = true;}
      if(yBUgOamOcr == sWahBZMNTI){ouaizLYWZI = true;}
      else if(sWahBZMNTI == yBUgOamOcr){XpYfKRCwrj = true;}
      if(WTQCKwcewC == InIPuWkjky){LybSXwtfXW = true;}
      else if(InIPuWkjky == WTQCKwcewC){SoIYAIGsew = true;}
      if(dwxBFEiBfp == oEcagiZDEm){gSeSFiALem = true;}
      else if(oEcagiZDEm == dwxBFEiBfp){VHTCpCLpoI = true;}
      if(wZRwOqQOsq == zcdQSrtSwc){JfVzszafcw = true;}
      else if(zcdQSrtSwc == wZRwOqQOsq){WXVLhacZmo = true;}
      if(AfDgqtpOBh == jtchDynXmb){NaQESzSzFg = true;}
      else if(jtchDynXmb == AfDgqtpOBh){AMbYDrJcMc = true;}
      if(mzRVFCDTaK == dMemDnszAS){fFXBpVQIdQ = true;}
      if(qkhmuxBTmT == zJIgJfJrxD){KMrlzebbZY = true;}
      if(fNlECxsPKL == cSnINubuXh){VNCaJGCazF = true;}
      while(dMemDnszAS == mzRVFCDTaK){tozIRPVWpH = true;}
      while(zJIgJfJrxD == zJIgJfJrxD){FMGiNuSxpZ = true;}
      while(cSnINubuXh == cSnINubuXh){ffGpuIetyx = true;}
      if(uCPbIlypMe == true){uCPbIlypMe = false;}
      if(ytRccZluYX == true){ytRccZluYX = false;}
      if(ouaizLYWZI == true){ouaizLYWZI = false;}
      if(LybSXwtfXW == true){LybSXwtfXW = false;}
      if(gSeSFiALem == true){gSeSFiALem = false;}
      if(JfVzszafcw == true){JfVzszafcw = false;}
      if(NaQESzSzFg == true){NaQESzSzFg = false;}
      if(fFXBpVQIdQ == true){fFXBpVQIdQ = false;}
      if(KMrlzebbZY == true){KMrlzebbZY = false;}
      if(VNCaJGCazF == true){VNCaJGCazF = false;}
      if(QBGyHDIUIW == true){QBGyHDIUIW = false;}
      if(hSBMlAidEn == true){hSBMlAidEn = false;}
      if(XpYfKRCwrj == true){XpYfKRCwrj = false;}
      if(SoIYAIGsew == true){SoIYAIGsew = false;}
      if(VHTCpCLpoI == true){VHTCpCLpoI = false;}
      if(WXVLhacZmo == true){WXVLhacZmo = false;}
      if(AMbYDrJcMc == true){AMbYDrJcMc = false;}
      if(tozIRPVWpH == true){tozIRPVWpH = false;}
      if(FMGiNuSxpZ == true){FMGiNuSxpZ = false;}
      if(ffGpuIetyx == true){ffGpuIetyx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDHQMLGVNU
{ 
  void TxcqLpwesU()
  { 
      bool pkresOnMwb = false;
      bool ShaGEUykLg = false;
      bool FrCjRjJUYw = false;
      bool dmLXAXaOLx = false;
      bool RjqHuVPkHF = false;
      bool FzWwMyiHNI = false;
      bool ETnAxfVCFg = false;
      bool siZOOUAuow = false;
      bool TXMSpdPPKB = false;
      bool nSBDsywqJO = false;
      bool zNfaMVZIgq = false;
      bool xnSRnfGUJS = false;
      bool QGrDrZhVUP = false;
      bool YJkZwGrlGT = false;
      bool EGhTEAAjOM = false;
      bool ragpyrUbhl = false;
      bool nDmRRnCsUg = false;
      bool nUOpOJYXzq = false;
      bool ZxHIXxctbE = false;
      bool kPDTfASQBP = false;
      string qECAPazIuq;
      string QadfkcXjwd;
      string EqHdaPIJhR;
      string KhptjjKTuU;
      string wCFbSEMYKM;
      string DaqhPAxYZz;
      string SoacgikjuA;
      string SEobhClfKW;
      string DjzUNiqHdj;
      string mksuCGabti;
      string SccKtzlPAN;
      string NQNCwhpGOx;
      string qcFLMgKsYb;
      string aKkaDaHoZO;
      string xbHQVVXqzT;
      string PUMxroWQxN;
      string nrpXmDflyU;
      string aBgzAPVopq;
      string ITsELGxniO;
      string DprMaEkicS;
      if(qECAPazIuq == SccKtzlPAN){pkresOnMwb = true;}
      else if(SccKtzlPAN == qECAPazIuq){zNfaMVZIgq = true;}
      if(QadfkcXjwd == NQNCwhpGOx){ShaGEUykLg = true;}
      else if(NQNCwhpGOx == QadfkcXjwd){xnSRnfGUJS = true;}
      if(EqHdaPIJhR == qcFLMgKsYb){FrCjRjJUYw = true;}
      else if(qcFLMgKsYb == EqHdaPIJhR){QGrDrZhVUP = true;}
      if(KhptjjKTuU == aKkaDaHoZO){dmLXAXaOLx = true;}
      else if(aKkaDaHoZO == KhptjjKTuU){YJkZwGrlGT = true;}
      if(wCFbSEMYKM == xbHQVVXqzT){RjqHuVPkHF = true;}
      else if(xbHQVVXqzT == wCFbSEMYKM){EGhTEAAjOM = true;}
      if(DaqhPAxYZz == PUMxroWQxN){FzWwMyiHNI = true;}
      else if(PUMxroWQxN == DaqhPAxYZz){ragpyrUbhl = true;}
      if(SoacgikjuA == nrpXmDflyU){ETnAxfVCFg = true;}
      else if(nrpXmDflyU == SoacgikjuA){nDmRRnCsUg = true;}
      if(SEobhClfKW == aBgzAPVopq){siZOOUAuow = true;}
      if(DjzUNiqHdj == ITsELGxniO){TXMSpdPPKB = true;}
      if(mksuCGabti == DprMaEkicS){nSBDsywqJO = true;}
      while(aBgzAPVopq == SEobhClfKW){nUOpOJYXzq = true;}
      while(ITsELGxniO == ITsELGxniO){ZxHIXxctbE = true;}
      while(DprMaEkicS == DprMaEkicS){kPDTfASQBP = true;}
      if(pkresOnMwb == true){pkresOnMwb = false;}
      if(ShaGEUykLg == true){ShaGEUykLg = false;}
      if(FrCjRjJUYw == true){FrCjRjJUYw = false;}
      if(dmLXAXaOLx == true){dmLXAXaOLx = false;}
      if(RjqHuVPkHF == true){RjqHuVPkHF = false;}
      if(FzWwMyiHNI == true){FzWwMyiHNI = false;}
      if(ETnAxfVCFg == true){ETnAxfVCFg = false;}
      if(siZOOUAuow == true){siZOOUAuow = false;}
      if(TXMSpdPPKB == true){TXMSpdPPKB = false;}
      if(nSBDsywqJO == true){nSBDsywqJO = false;}
      if(zNfaMVZIgq == true){zNfaMVZIgq = false;}
      if(xnSRnfGUJS == true){xnSRnfGUJS = false;}
      if(QGrDrZhVUP == true){QGrDrZhVUP = false;}
      if(YJkZwGrlGT == true){YJkZwGrlGT = false;}
      if(EGhTEAAjOM == true){EGhTEAAjOM = false;}
      if(ragpyrUbhl == true){ragpyrUbhl = false;}
      if(nDmRRnCsUg == true){nDmRRnCsUg = false;}
      if(nUOpOJYXzq == true){nUOpOJYXzq = false;}
      if(ZxHIXxctbE == true){ZxHIXxctbE = false;}
      if(kPDTfASQBP == true){kPDTfASQBP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVFQSBFEWO
{ 
  void ofUIpHpORu()
  { 
      bool uBXnlOBwGR = false;
      bool QyKDlPtslB = false;
      bool jncJmkPgOd = false;
      bool wCYdnoxpMI = false;
      bool eJVInpQJCo = false;
      bool EfOrBHXOBA = false;
      bool zThbUNYfOw = false;
      bool SDfcWZRUVw = false;
      bool TGdYYPnfbf = false;
      bool RhnLJKasma = false;
      bool QktFWBzkVb = false;
      bool oDsEfroIDF = false;
      bool ZsDhejOUTM = false;
      bool zYgueiLYCX = false;
      bool QCKAqNojfQ = false;
      bool URohAXhLZl = false;
      bool leRJbQVyYx = false;
      bool gQGfnWhCqR = false;
      bool uenDqgiytH = false;
      bool AzyPkkkBXZ = false;
      string XuXnBzGMAD;
      string LicapyDyJF;
      string EOYPqxQxhI;
      string JNkQwIeWDx;
      string ZoSdZgaxPr;
      string ZPECBIVIwE;
      string iIdrtxxMeh;
      string SguMeOwupJ;
      string VTgpisJhPm;
      string lWZzORLZjb;
      string jORhYrUqWl;
      string LaRmhOanJA;
      string nOxquuHuyN;
      string DVKNYGBzRp;
      string XRKcaLFlQz;
      string pXQimURZmc;
      string kYrJhoPDNb;
      string MbVTcVETPj;
      string pUezWfFbZE;
      string nbMoFzZBtk;
      if(XuXnBzGMAD == jORhYrUqWl){uBXnlOBwGR = true;}
      else if(jORhYrUqWl == XuXnBzGMAD){QktFWBzkVb = true;}
      if(LicapyDyJF == LaRmhOanJA){QyKDlPtslB = true;}
      else if(LaRmhOanJA == LicapyDyJF){oDsEfroIDF = true;}
      if(EOYPqxQxhI == nOxquuHuyN){jncJmkPgOd = true;}
      else if(nOxquuHuyN == EOYPqxQxhI){ZsDhejOUTM = true;}
      if(JNkQwIeWDx == DVKNYGBzRp){wCYdnoxpMI = true;}
      else if(DVKNYGBzRp == JNkQwIeWDx){zYgueiLYCX = true;}
      if(ZoSdZgaxPr == XRKcaLFlQz){eJVInpQJCo = true;}
      else if(XRKcaLFlQz == ZoSdZgaxPr){QCKAqNojfQ = true;}
      if(ZPECBIVIwE == pXQimURZmc){EfOrBHXOBA = true;}
      else if(pXQimURZmc == ZPECBIVIwE){URohAXhLZl = true;}
      if(iIdrtxxMeh == kYrJhoPDNb){zThbUNYfOw = true;}
      else if(kYrJhoPDNb == iIdrtxxMeh){leRJbQVyYx = true;}
      if(SguMeOwupJ == MbVTcVETPj){SDfcWZRUVw = true;}
      if(VTgpisJhPm == pUezWfFbZE){TGdYYPnfbf = true;}
      if(lWZzORLZjb == nbMoFzZBtk){RhnLJKasma = true;}
      while(MbVTcVETPj == SguMeOwupJ){gQGfnWhCqR = true;}
      while(pUezWfFbZE == pUezWfFbZE){uenDqgiytH = true;}
      while(nbMoFzZBtk == nbMoFzZBtk){AzyPkkkBXZ = true;}
      if(uBXnlOBwGR == true){uBXnlOBwGR = false;}
      if(QyKDlPtslB == true){QyKDlPtslB = false;}
      if(jncJmkPgOd == true){jncJmkPgOd = false;}
      if(wCYdnoxpMI == true){wCYdnoxpMI = false;}
      if(eJVInpQJCo == true){eJVInpQJCo = false;}
      if(EfOrBHXOBA == true){EfOrBHXOBA = false;}
      if(zThbUNYfOw == true){zThbUNYfOw = false;}
      if(SDfcWZRUVw == true){SDfcWZRUVw = false;}
      if(TGdYYPnfbf == true){TGdYYPnfbf = false;}
      if(RhnLJKasma == true){RhnLJKasma = false;}
      if(QktFWBzkVb == true){QktFWBzkVb = false;}
      if(oDsEfroIDF == true){oDsEfroIDF = false;}
      if(ZsDhejOUTM == true){ZsDhejOUTM = false;}
      if(zYgueiLYCX == true){zYgueiLYCX = false;}
      if(QCKAqNojfQ == true){QCKAqNojfQ = false;}
      if(URohAXhLZl == true){URohAXhLZl = false;}
      if(leRJbQVyYx == true){leRJbQVyYx = false;}
      if(gQGfnWhCqR == true){gQGfnWhCqR = false;}
      if(uenDqgiytH == true){uenDqgiytH = false;}
      if(AzyPkkkBXZ == true){AzyPkkkBXZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJBPGNOZCA
{ 
  void qpufsKQcrj()
  { 
      bool FkiMdlkSFJ = false;
      bool uzUGSmfQuL = false;
      bool COfEGIzWPE = false;
      bool LLdQflgKBj = false;
      bool spdCFGjJGn = false;
      bool PNLBlqEeGU = false;
      bool lODAxjVDZg = false;
      bool GUOKRMjdyz = false;
      bool YpQaoxzbeo = false;
      bool gBEfyelcFU = false;
      bool kgiZgtyAjY = false;
      bool GafHwwxbLz = false;
      bool jsXkzEQiMl = false;
      bool ZHYcNrGqtt = false;
      bool yzrFhFVxjC = false;
      bool gKQFkrIyZc = false;
      bool dPmxzzCDsE = false;
      bool oGhQAjARCs = false;
      bool iSyKEOpSrU = false;
      bool iIQRQiMuGi = false;
      string XPweSafEVa;
      string rVStyyQLuz;
      string UrmNmYYLiK;
      string ebLPJRPCem;
      string xOrxiQnOQa;
      string WgdtJebhrt;
      string CUUKuQKCjg;
      string iOgICGApeW;
      string jJtInyxRGe;
      string pgJjjcsgCS;
      string GlejrIAVrC;
      string elDVKrZMWx;
      string SruFpBExXY;
      string MSnLPxeJPe;
      string ybZDzDcnZr;
      string CgKEzOqZsq;
      string DDxSpLxrFM;
      string NQwqzpSqFl;
      string XPWfWeIiLB;
      string GEQYbueHNn;
      if(XPweSafEVa == GlejrIAVrC){FkiMdlkSFJ = true;}
      else if(GlejrIAVrC == XPweSafEVa){kgiZgtyAjY = true;}
      if(rVStyyQLuz == elDVKrZMWx){uzUGSmfQuL = true;}
      else if(elDVKrZMWx == rVStyyQLuz){GafHwwxbLz = true;}
      if(UrmNmYYLiK == SruFpBExXY){COfEGIzWPE = true;}
      else if(SruFpBExXY == UrmNmYYLiK){jsXkzEQiMl = true;}
      if(ebLPJRPCem == MSnLPxeJPe){LLdQflgKBj = true;}
      else if(MSnLPxeJPe == ebLPJRPCem){ZHYcNrGqtt = true;}
      if(xOrxiQnOQa == ybZDzDcnZr){spdCFGjJGn = true;}
      else if(ybZDzDcnZr == xOrxiQnOQa){yzrFhFVxjC = true;}
      if(WgdtJebhrt == CgKEzOqZsq){PNLBlqEeGU = true;}
      else if(CgKEzOqZsq == WgdtJebhrt){gKQFkrIyZc = true;}
      if(CUUKuQKCjg == DDxSpLxrFM){lODAxjVDZg = true;}
      else if(DDxSpLxrFM == CUUKuQKCjg){dPmxzzCDsE = true;}
      if(iOgICGApeW == NQwqzpSqFl){GUOKRMjdyz = true;}
      if(jJtInyxRGe == XPWfWeIiLB){YpQaoxzbeo = true;}
      if(pgJjjcsgCS == GEQYbueHNn){gBEfyelcFU = true;}
      while(NQwqzpSqFl == iOgICGApeW){oGhQAjARCs = true;}
      while(XPWfWeIiLB == XPWfWeIiLB){iSyKEOpSrU = true;}
      while(GEQYbueHNn == GEQYbueHNn){iIQRQiMuGi = true;}
      if(FkiMdlkSFJ == true){FkiMdlkSFJ = false;}
      if(uzUGSmfQuL == true){uzUGSmfQuL = false;}
      if(COfEGIzWPE == true){COfEGIzWPE = false;}
      if(LLdQflgKBj == true){LLdQflgKBj = false;}
      if(spdCFGjJGn == true){spdCFGjJGn = false;}
      if(PNLBlqEeGU == true){PNLBlqEeGU = false;}
      if(lODAxjVDZg == true){lODAxjVDZg = false;}
      if(GUOKRMjdyz == true){GUOKRMjdyz = false;}
      if(YpQaoxzbeo == true){YpQaoxzbeo = false;}
      if(gBEfyelcFU == true){gBEfyelcFU = false;}
      if(kgiZgtyAjY == true){kgiZgtyAjY = false;}
      if(GafHwwxbLz == true){GafHwwxbLz = false;}
      if(jsXkzEQiMl == true){jsXkzEQiMl = false;}
      if(ZHYcNrGqtt == true){ZHYcNrGqtt = false;}
      if(yzrFhFVxjC == true){yzrFhFVxjC = false;}
      if(gKQFkrIyZc == true){gKQFkrIyZc = false;}
      if(dPmxzzCDsE == true){dPmxzzCDsE = false;}
      if(oGhQAjARCs == true){oGhQAjARCs = false;}
      if(iSyKEOpSrU == true){iSyKEOpSrU = false;}
      if(iIQRQiMuGi == true){iIQRQiMuGi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIAOQVBVTL
{ 
  void RQwWfLVlsH()
  { 
      bool hxHNPOOqIo = false;
      bool TVynGxWJXY = false;
      bool sRgxNcajZN = false;
      bool guowzamPKz = false;
      bool jkFQOxaRkD = false;
      bool TlHYZPQKzm = false;
      bool ndRtIYfCof = false;
      bool JHzYnILPhQ = false;
      bool BIzVstmQVi = false;
      bool JcPXKFSKIp = false;
      bool QYbFsMmijR = false;
      bool EBbhleduAN = false;
      bool kPfFVgqaNi = false;
      bool pAGrAcftcg = false;
      bool GEfEeIAhle = false;
      bool aWKtEBrWjM = false;
      bool ULUBaDtjhI = false;
      bool zjSTGgiaaM = false;
      bool fJoiHTpLmz = false;
      bool jJKPMuieca = false;
      string zxYBtjgOZV;
      string OjKMhWVbFY;
      string bEEHTumdFk;
      string LqaWBPPiCE;
      string IxZSCyDeiu;
      string OxeLpusRhz;
      string xDIoJXInLR;
      string HlZAPdekEU;
      string qHtKVOLOfF;
      string WyBCHFojIe;
      string pPTRncWdwL;
      string PIMMIoJySu;
      string LtHFuJjWsK;
      string otbZeambVs;
      string qhSUoNkotR;
      string wpRNSwIOVe;
      string rzklWVfmgg;
      string BgbZEdbmPg;
      string XucaNybOGi;
      string SYGqAqwfxT;
      if(zxYBtjgOZV == pPTRncWdwL){hxHNPOOqIo = true;}
      else if(pPTRncWdwL == zxYBtjgOZV){QYbFsMmijR = true;}
      if(OjKMhWVbFY == PIMMIoJySu){TVynGxWJXY = true;}
      else if(PIMMIoJySu == OjKMhWVbFY){EBbhleduAN = true;}
      if(bEEHTumdFk == LtHFuJjWsK){sRgxNcajZN = true;}
      else if(LtHFuJjWsK == bEEHTumdFk){kPfFVgqaNi = true;}
      if(LqaWBPPiCE == otbZeambVs){guowzamPKz = true;}
      else if(otbZeambVs == LqaWBPPiCE){pAGrAcftcg = true;}
      if(IxZSCyDeiu == qhSUoNkotR){jkFQOxaRkD = true;}
      else if(qhSUoNkotR == IxZSCyDeiu){GEfEeIAhle = true;}
      if(OxeLpusRhz == wpRNSwIOVe){TlHYZPQKzm = true;}
      else if(wpRNSwIOVe == OxeLpusRhz){aWKtEBrWjM = true;}
      if(xDIoJXInLR == rzklWVfmgg){ndRtIYfCof = true;}
      else if(rzklWVfmgg == xDIoJXInLR){ULUBaDtjhI = true;}
      if(HlZAPdekEU == BgbZEdbmPg){JHzYnILPhQ = true;}
      if(qHtKVOLOfF == XucaNybOGi){BIzVstmQVi = true;}
      if(WyBCHFojIe == SYGqAqwfxT){JcPXKFSKIp = true;}
      while(BgbZEdbmPg == HlZAPdekEU){zjSTGgiaaM = true;}
      while(XucaNybOGi == XucaNybOGi){fJoiHTpLmz = true;}
      while(SYGqAqwfxT == SYGqAqwfxT){jJKPMuieca = true;}
      if(hxHNPOOqIo == true){hxHNPOOqIo = false;}
      if(TVynGxWJXY == true){TVynGxWJXY = false;}
      if(sRgxNcajZN == true){sRgxNcajZN = false;}
      if(guowzamPKz == true){guowzamPKz = false;}
      if(jkFQOxaRkD == true){jkFQOxaRkD = false;}
      if(TlHYZPQKzm == true){TlHYZPQKzm = false;}
      if(ndRtIYfCof == true){ndRtIYfCof = false;}
      if(JHzYnILPhQ == true){JHzYnILPhQ = false;}
      if(BIzVstmQVi == true){BIzVstmQVi = false;}
      if(JcPXKFSKIp == true){JcPXKFSKIp = false;}
      if(QYbFsMmijR == true){QYbFsMmijR = false;}
      if(EBbhleduAN == true){EBbhleduAN = false;}
      if(kPfFVgqaNi == true){kPfFVgqaNi = false;}
      if(pAGrAcftcg == true){pAGrAcftcg = false;}
      if(GEfEeIAhle == true){GEfEeIAhle = false;}
      if(aWKtEBrWjM == true){aWKtEBrWjM = false;}
      if(ULUBaDtjhI == true){ULUBaDtjhI = false;}
      if(zjSTGgiaaM == true){zjSTGgiaaM = false;}
      if(fJoiHTpLmz == true){fJoiHTpLmz = false;}
      if(jJKPMuieca == true){jJKPMuieca = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLGKNBEHJX
{ 
  void fMbmGnSXHe()
  { 
      bool uLoaZiBqdq = false;
      bool zMSeyeRHxz = false;
      bool QbdDXfmWnY = false;
      bool HcJgwgdnSq = false;
      bool MuywtkMfnM = false;
      bool ejsOoSglCs = false;
      bool weCEiWDkiQ = false;
      bool BcoGlVdhIm = false;
      bool TGibtXjtrc = false;
      bool zrkZuhrsMX = false;
      bool gaxWKBulcS = false;
      bool ozcPYowZKL = false;
      bool mIsFRJqOKD = false;
      bool ckUkGsILRr = false;
      bool cxRYnzOVAG = false;
      bool lRhAkXgrFB = false;
      bool JfbYpDdrJe = false;
      bool fjIRioqTQR = false;
      bool tUNERKDTAh = false;
      bool MQGPhwUrik = false;
      string tPgZFueXZQ;
      string jsxPQgZyfg;
      string yXGTAbKsuF;
      string nRKetqmWfS;
      string EZQcDkFXqG;
      string INsLMVJNZc;
      string jkbUbRhSUZ;
      string tDRNcYHcQP;
      string WmBowaYzRX;
      string gYxDhSywBk;
      string CmCRLFufin;
      string OgwKFwjmXB;
      string siBwsUGNeJ;
      string ZKbeMikjcq;
      string esPcJAclxk;
      string iLXAqSkFXq;
      string zhAYODERxW;
      string LzJgVATXmr;
      string rTPsaOmbmt;
      string yeLlrxrpOF;
      if(tPgZFueXZQ == CmCRLFufin){uLoaZiBqdq = true;}
      else if(CmCRLFufin == tPgZFueXZQ){gaxWKBulcS = true;}
      if(jsxPQgZyfg == OgwKFwjmXB){zMSeyeRHxz = true;}
      else if(OgwKFwjmXB == jsxPQgZyfg){ozcPYowZKL = true;}
      if(yXGTAbKsuF == siBwsUGNeJ){QbdDXfmWnY = true;}
      else if(siBwsUGNeJ == yXGTAbKsuF){mIsFRJqOKD = true;}
      if(nRKetqmWfS == ZKbeMikjcq){HcJgwgdnSq = true;}
      else if(ZKbeMikjcq == nRKetqmWfS){ckUkGsILRr = true;}
      if(EZQcDkFXqG == esPcJAclxk){MuywtkMfnM = true;}
      else if(esPcJAclxk == EZQcDkFXqG){cxRYnzOVAG = true;}
      if(INsLMVJNZc == iLXAqSkFXq){ejsOoSglCs = true;}
      else if(iLXAqSkFXq == INsLMVJNZc){lRhAkXgrFB = true;}
      if(jkbUbRhSUZ == zhAYODERxW){weCEiWDkiQ = true;}
      else if(zhAYODERxW == jkbUbRhSUZ){JfbYpDdrJe = true;}
      if(tDRNcYHcQP == LzJgVATXmr){BcoGlVdhIm = true;}
      if(WmBowaYzRX == rTPsaOmbmt){TGibtXjtrc = true;}
      if(gYxDhSywBk == yeLlrxrpOF){zrkZuhrsMX = true;}
      while(LzJgVATXmr == tDRNcYHcQP){fjIRioqTQR = true;}
      while(rTPsaOmbmt == rTPsaOmbmt){tUNERKDTAh = true;}
      while(yeLlrxrpOF == yeLlrxrpOF){MQGPhwUrik = true;}
      if(uLoaZiBqdq == true){uLoaZiBqdq = false;}
      if(zMSeyeRHxz == true){zMSeyeRHxz = false;}
      if(QbdDXfmWnY == true){QbdDXfmWnY = false;}
      if(HcJgwgdnSq == true){HcJgwgdnSq = false;}
      if(MuywtkMfnM == true){MuywtkMfnM = false;}
      if(ejsOoSglCs == true){ejsOoSglCs = false;}
      if(weCEiWDkiQ == true){weCEiWDkiQ = false;}
      if(BcoGlVdhIm == true){BcoGlVdhIm = false;}
      if(TGibtXjtrc == true){TGibtXjtrc = false;}
      if(zrkZuhrsMX == true){zrkZuhrsMX = false;}
      if(gaxWKBulcS == true){gaxWKBulcS = false;}
      if(ozcPYowZKL == true){ozcPYowZKL = false;}
      if(mIsFRJqOKD == true){mIsFRJqOKD = false;}
      if(ckUkGsILRr == true){ckUkGsILRr = false;}
      if(cxRYnzOVAG == true){cxRYnzOVAG = false;}
      if(lRhAkXgrFB == true){lRhAkXgrFB = false;}
      if(JfbYpDdrJe == true){JfbYpDdrJe = false;}
      if(fjIRioqTQR == true){fjIRioqTQR = false;}
      if(tUNERKDTAh == true){tUNERKDTAh = false;}
      if(MQGPhwUrik == true){MQGPhwUrik = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBBXOCOENZ
{ 
  void ROYbxbRUrs()
  { 
      bool KIWixyTnFG = false;
      bool XaVGTzAsUw = false;
      bool mGCnmwpGlN = false;
      bool WXoqODXXSh = false;
      bool UpFnjUJYck = false;
      bool JMxjUEGiwB = false;
      bool HMBqjAldqQ = false;
      bool acambxBNER = false;
      bool lQcADJZEWK = false;
      bool woaQZHnNDj = false;
      bool iehMJgkKIX = false;
      bool DrddOpjBmZ = false;
      bool ZgHgTlBKMT = false;
      bool ImJUiHiQpW = false;
      bool XPwyGELxBj = false;
      bool XmZcJCXArX = false;
      bool fZxnOPhIuH = false;
      bool GSKQBKjIaP = false;
      bool aDIcwVMgLg = false;
      bool iiYSqyRIjp = false;
      string TNfNigcapc;
      string OKqAROwWUg;
      string gJFuBZFDTx;
      string sFcjqmRxDd;
      string cNGAmGsFLt;
      string IypGRJHjMJ;
      string bZHrjJgGIe;
      string xzSqESDEIt;
      string fzqZouPWRg;
      string egktBDFNQd;
      string YmxfwJeyCy;
      string GDbRcchhCn;
      string sKoaAQOXoB;
      string MomeVsBLcf;
      string QQTSaaFSRY;
      string UXKcjNxWff;
      string tGJBkRQwwi;
      string aWEWXcpVAY;
      string LuGPfodKtH;
      string wefxkJGSgI;
      if(TNfNigcapc == YmxfwJeyCy){KIWixyTnFG = true;}
      else if(YmxfwJeyCy == TNfNigcapc){iehMJgkKIX = true;}
      if(OKqAROwWUg == GDbRcchhCn){XaVGTzAsUw = true;}
      else if(GDbRcchhCn == OKqAROwWUg){DrddOpjBmZ = true;}
      if(gJFuBZFDTx == sKoaAQOXoB){mGCnmwpGlN = true;}
      else if(sKoaAQOXoB == gJFuBZFDTx){ZgHgTlBKMT = true;}
      if(sFcjqmRxDd == MomeVsBLcf){WXoqODXXSh = true;}
      else if(MomeVsBLcf == sFcjqmRxDd){ImJUiHiQpW = true;}
      if(cNGAmGsFLt == QQTSaaFSRY){UpFnjUJYck = true;}
      else if(QQTSaaFSRY == cNGAmGsFLt){XPwyGELxBj = true;}
      if(IypGRJHjMJ == UXKcjNxWff){JMxjUEGiwB = true;}
      else if(UXKcjNxWff == IypGRJHjMJ){XmZcJCXArX = true;}
      if(bZHrjJgGIe == tGJBkRQwwi){HMBqjAldqQ = true;}
      else if(tGJBkRQwwi == bZHrjJgGIe){fZxnOPhIuH = true;}
      if(xzSqESDEIt == aWEWXcpVAY){acambxBNER = true;}
      if(fzqZouPWRg == LuGPfodKtH){lQcADJZEWK = true;}
      if(egktBDFNQd == wefxkJGSgI){woaQZHnNDj = true;}
      while(aWEWXcpVAY == xzSqESDEIt){GSKQBKjIaP = true;}
      while(LuGPfodKtH == LuGPfodKtH){aDIcwVMgLg = true;}
      while(wefxkJGSgI == wefxkJGSgI){iiYSqyRIjp = true;}
      if(KIWixyTnFG == true){KIWixyTnFG = false;}
      if(XaVGTzAsUw == true){XaVGTzAsUw = false;}
      if(mGCnmwpGlN == true){mGCnmwpGlN = false;}
      if(WXoqODXXSh == true){WXoqODXXSh = false;}
      if(UpFnjUJYck == true){UpFnjUJYck = false;}
      if(JMxjUEGiwB == true){JMxjUEGiwB = false;}
      if(HMBqjAldqQ == true){HMBqjAldqQ = false;}
      if(acambxBNER == true){acambxBNER = false;}
      if(lQcADJZEWK == true){lQcADJZEWK = false;}
      if(woaQZHnNDj == true){woaQZHnNDj = false;}
      if(iehMJgkKIX == true){iehMJgkKIX = false;}
      if(DrddOpjBmZ == true){DrddOpjBmZ = false;}
      if(ZgHgTlBKMT == true){ZgHgTlBKMT = false;}
      if(ImJUiHiQpW == true){ImJUiHiQpW = false;}
      if(XPwyGELxBj == true){XPwyGELxBj = false;}
      if(XmZcJCXArX == true){XmZcJCXArX = false;}
      if(fZxnOPhIuH == true){fZxnOPhIuH = false;}
      if(GSKQBKjIaP == true){GSKQBKjIaP = false;}
      if(aDIcwVMgLg == true){aDIcwVMgLg = false;}
      if(iiYSqyRIjp == true){iiYSqyRIjp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALDHREIKJU
{ 
  void UWEDEbIBdQ()
  { 
      bool WlRZPapaWl = false;
      bool LZmAXRgnRz = false;
      bool IsTVlLCKjt = false;
      bool NFPKUSZUui = false;
      bool ZAmyhfiqPC = false;
      bool ujfARcSwmD = false;
      bool YepbYGKbfF = false;
      bool qMshYHFVmG = false;
      bool cKthycYPrr = false;
      bool zdhrKuKLYb = false;
      bool VGLKLiqyaJ = false;
      bool WxIfZNjIcu = false;
      bool gtinFNdAWd = false;
      bool xtwLkWziWP = false;
      bool laniUCUBSx = false;
      bool KBhctaWXFx = false;
      bool EqaxMcAxtD = false;
      bool NAkNJGGASC = false;
      bool schZSuMSQK = false;
      bool zbdYKtzqWr = false;
      string xohfERaNcQ;
      string TYdILLObAA;
      string PjKYEAaDKd;
      string xaPNNMMhJQ;
      string WGNmdCjNJW;
      string PGrjcNeIaD;
      string pXDySsJPuz;
      string zfSicIWXtC;
      string PNtnOqhfjA;
      string gEGFZyDPTk;
      string sUSJXjmIGU;
      string pGNYncdOja;
      string LcetRuZMIe;
      string EGDJJutjQd;
      string DYZPJZpgRx;
      string UnfsYPoXrc;
      string JazbPiDDPr;
      string htyFWlDPkq;
      string ErtLJQaJjt;
      string FVqnUcYyzZ;
      if(xohfERaNcQ == sUSJXjmIGU){WlRZPapaWl = true;}
      else if(sUSJXjmIGU == xohfERaNcQ){VGLKLiqyaJ = true;}
      if(TYdILLObAA == pGNYncdOja){LZmAXRgnRz = true;}
      else if(pGNYncdOja == TYdILLObAA){WxIfZNjIcu = true;}
      if(PjKYEAaDKd == LcetRuZMIe){IsTVlLCKjt = true;}
      else if(LcetRuZMIe == PjKYEAaDKd){gtinFNdAWd = true;}
      if(xaPNNMMhJQ == EGDJJutjQd){NFPKUSZUui = true;}
      else if(EGDJJutjQd == xaPNNMMhJQ){xtwLkWziWP = true;}
      if(WGNmdCjNJW == DYZPJZpgRx){ZAmyhfiqPC = true;}
      else if(DYZPJZpgRx == WGNmdCjNJW){laniUCUBSx = true;}
      if(PGrjcNeIaD == UnfsYPoXrc){ujfARcSwmD = true;}
      else if(UnfsYPoXrc == PGrjcNeIaD){KBhctaWXFx = true;}
      if(pXDySsJPuz == JazbPiDDPr){YepbYGKbfF = true;}
      else if(JazbPiDDPr == pXDySsJPuz){EqaxMcAxtD = true;}
      if(zfSicIWXtC == htyFWlDPkq){qMshYHFVmG = true;}
      if(PNtnOqhfjA == ErtLJQaJjt){cKthycYPrr = true;}
      if(gEGFZyDPTk == FVqnUcYyzZ){zdhrKuKLYb = true;}
      while(htyFWlDPkq == zfSicIWXtC){NAkNJGGASC = true;}
      while(ErtLJQaJjt == ErtLJQaJjt){schZSuMSQK = true;}
      while(FVqnUcYyzZ == FVqnUcYyzZ){zbdYKtzqWr = true;}
      if(WlRZPapaWl == true){WlRZPapaWl = false;}
      if(LZmAXRgnRz == true){LZmAXRgnRz = false;}
      if(IsTVlLCKjt == true){IsTVlLCKjt = false;}
      if(NFPKUSZUui == true){NFPKUSZUui = false;}
      if(ZAmyhfiqPC == true){ZAmyhfiqPC = false;}
      if(ujfARcSwmD == true){ujfARcSwmD = false;}
      if(YepbYGKbfF == true){YepbYGKbfF = false;}
      if(qMshYHFVmG == true){qMshYHFVmG = false;}
      if(cKthycYPrr == true){cKthycYPrr = false;}
      if(zdhrKuKLYb == true){zdhrKuKLYb = false;}
      if(VGLKLiqyaJ == true){VGLKLiqyaJ = false;}
      if(WxIfZNjIcu == true){WxIfZNjIcu = false;}
      if(gtinFNdAWd == true){gtinFNdAWd = false;}
      if(xtwLkWziWP == true){xtwLkWziWP = false;}
      if(laniUCUBSx == true){laniUCUBSx = false;}
      if(KBhctaWXFx == true){KBhctaWXFx = false;}
      if(EqaxMcAxtD == true){EqaxMcAxtD = false;}
      if(NAkNJGGASC == true){NAkNJGGASC = false;}
      if(schZSuMSQK == true){schZSuMSQK = false;}
      if(zbdYKtzqWr == true){zbdYKtzqWr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDZZWFYKVV
{ 
  void NOlTfgbpgp()
  { 
      bool RNyzMuaWzX = false;
      bool PIrWqZQxDK = false;
      bool KhuNaCrUcD = false;
      bool bdYzfoEMlq = false;
      bool mRBBqnOcfx = false;
      bool PDyRQjRkYK = false;
      bool CFtuukirqC = false;
      bool UELMWsftWm = false;
      bool nPnenYfHiu = false;
      bool WTnanhXGFG = false;
      bool EVkdbLqkuX = false;
      bool EWOkWmQOGW = false;
      bool EbJueBQjXo = false;
      bool UYoPhRdKDc = false;
      bool guMKqzFCEB = false;
      bool QJzhBcMpya = false;
      bool tHNFCehyDE = false;
      bool IGLdpJOyEe = false;
      bool uNeWXLYHNE = false;
      bool FnLbhYgGIL = false;
      string aCIWmzarbq;
      string wpboZgCkNe;
      string oWQPboRZmU;
      string WGGStGUlzm;
      string CfhzPEUSlq;
      string RzruNDkrty;
      string hBEGTojIuS;
      string MPkZcIoQzW;
      string TynuDXOKFq;
      string UbqBFBbafa;
      string UMXSeBNRRE;
      string OTsXdiMICu;
      string ZYCEykXjUa;
      string gNkYCGZUQB;
      string KxrAbAhTWV;
      string nSYjAuKTUs;
      string ddwqXAiUUX;
      string IrrBkcfBbx;
      string CDMymNoBYG;
      string wGzWXgABbb;
      if(aCIWmzarbq == UMXSeBNRRE){RNyzMuaWzX = true;}
      else if(UMXSeBNRRE == aCIWmzarbq){EVkdbLqkuX = true;}
      if(wpboZgCkNe == OTsXdiMICu){PIrWqZQxDK = true;}
      else if(OTsXdiMICu == wpboZgCkNe){EWOkWmQOGW = true;}
      if(oWQPboRZmU == ZYCEykXjUa){KhuNaCrUcD = true;}
      else if(ZYCEykXjUa == oWQPboRZmU){EbJueBQjXo = true;}
      if(WGGStGUlzm == gNkYCGZUQB){bdYzfoEMlq = true;}
      else if(gNkYCGZUQB == WGGStGUlzm){UYoPhRdKDc = true;}
      if(CfhzPEUSlq == KxrAbAhTWV){mRBBqnOcfx = true;}
      else if(KxrAbAhTWV == CfhzPEUSlq){guMKqzFCEB = true;}
      if(RzruNDkrty == nSYjAuKTUs){PDyRQjRkYK = true;}
      else if(nSYjAuKTUs == RzruNDkrty){QJzhBcMpya = true;}
      if(hBEGTojIuS == ddwqXAiUUX){CFtuukirqC = true;}
      else if(ddwqXAiUUX == hBEGTojIuS){tHNFCehyDE = true;}
      if(MPkZcIoQzW == IrrBkcfBbx){UELMWsftWm = true;}
      if(TynuDXOKFq == CDMymNoBYG){nPnenYfHiu = true;}
      if(UbqBFBbafa == wGzWXgABbb){WTnanhXGFG = true;}
      while(IrrBkcfBbx == MPkZcIoQzW){IGLdpJOyEe = true;}
      while(CDMymNoBYG == CDMymNoBYG){uNeWXLYHNE = true;}
      while(wGzWXgABbb == wGzWXgABbb){FnLbhYgGIL = true;}
      if(RNyzMuaWzX == true){RNyzMuaWzX = false;}
      if(PIrWqZQxDK == true){PIrWqZQxDK = false;}
      if(KhuNaCrUcD == true){KhuNaCrUcD = false;}
      if(bdYzfoEMlq == true){bdYzfoEMlq = false;}
      if(mRBBqnOcfx == true){mRBBqnOcfx = false;}
      if(PDyRQjRkYK == true){PDyRQjRkYK = false;}
      if(CFtuukirqC == true){CFtuukirqC = false;}
      if(UELMWsftWm == true){UELMWsftWm = false;}
      if(nPnenYfHiu == true){nPnenYfHiu = false;}
      if(WTnanhXGFG == true){WTnanhXGFG = false;}
      if(EVkdbLqkuX == true){EVkdbLqkuX = false;}
      if(EWOkWmQOGW == true){EWOkWmQOGW = false;}
      if(EbJueBQjXo == true){EbJueBQjXo = false;}
      if(UYoPhRdKDc == true){UYoPhRdKDc = false;}
      if(guMKqzFCEB == true){guMKqzFCEB = false;}
      if(QJzhBcMpya == true){QJzhBcMpya = false;}
      if(tHNFCehyDE == true){tHNFCehyDE = false;}
      if(IGLdpJOyEe == true){IGLdpJOyEe = false;}
      if(uNeWXLYHNE == true){uNeWXLYHNE = false;}
      if(FnLbhYgGIL == true){FnLbhYgGIL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMMIDBURPP
{ 
  void fMgxUPksjT()
  { 
      bool ruQrlQjgZO = false;
      bool IIuAnppZBM = false;
      bool MwwONAPzMt = false;
      bool cePzJCzoSa = false;
      bool wXYRjCymRa = false;
      bool IrVAIuzCdk = false;
      bool BkTfkdswpk = false;
      bool qBGaPnWddK = false;
      bool CbglkkIPpN = false;
      bool DxKgZLDsgG = false;
      bool JBxgjGkujU = false;
      bool YUXSiYEhtA = false;
      bool UdFbhtqZBD = false;
      bool kdxXBAeACd = false;
      bool zNeVohYqyA = false;
      bool HVyfkewUyo = false;
      bool PLtfitXzRh = false;
      bool tEfPBHyimA = false;
      bool UzaAwOeQlW = false;
      bool EJBMOmSylt = false;
      string qFnEUeyhTK;
      string ZswVHhJMCT;
      string AYqTHipUfs;
      string CLCtoPPiZb;
      string sppqUWUFkc;
      string XJsfYRNUxk;
      string odCZINpBfr;
      string SamZaKhAzk;
      string OjiDVsRWUW;
      string BuknmOnQhG;
      string fSZsKwVSFO;
      string jNVMVFtyEP;
      string uTgIpXoymL;
      string VRRrEwKpsY;
      string WzQFmnYYRg;
      string UoMSLLkQCl;
      string HXfssRucHZ;
      string tDFeswCbUC;
      string yQgFqgFzgs;
      string LsnGRzSXMV;
      if(qFnEUeyhTK == fSZsKwVSFO){ruQrlQjgZO = true;}
      else if(fSZsKwVSFO == qFnEUeyhTK){JBxgjGkujU = true;}
      if(ZswVHhJMCT == jNVMVFtyEP){IIuAnppZBM = true;}
      else if(jNVMVFtyEP == ZswVHhJMCT){YUXSiYEhtA = true;}
      if(AYqTHipUfs == uTgIpXoymL){MwwONAPzMt = true;}
      else if(uTgIpXoymL == AYqTHipUfs){UdFbhtqZBD = true;}
      if(CLCtoPPiZb == VRRrEwKpsY){cePzJCzoSa = true;}
      else if(VRRrEwKpsY == CLCtoPPiZb){kdxXBAeACd = true;}
      if(sppqUWUFkc == WzQFmnYYRg){wXYRjCymRa = true;}
      else if(WzQFmnYYRg == sppqUWUFkc){zNeVohYqyA = true;}
      if(XJsfYRNUxk == UoMSLLkQCl){IrVAIuzCdk = true;}
      else if(UoMSLLkQCl == XJsfYRNUxk){HVyfkewUyo = true;}
      if(odCZINpBfr == HXfssRucHZ){BkTfkdswpk = true;}
      else if(HXfssRucHZ == odCZINpBfr){PLtfitXzRh = true;}
      if(SamZaKhAzk == tDFeswCbUC){qBGaPnWddK = true;}
      if(OjiDVsRWUW == yQgFqgFzgs){CbglkkIPpN = true;}
      if(BuknmOnQhG == LsnGRzSXMV){DxKgZLDsgG = true;}
      while(tDFeswCbUC == SamZaKhAzk){tEfPBHyimA = true;}
      while(yQgFqgFzgs == yQgFqgFzgs){UzaAwOeQlW = true;}
      while(LsnGRzSXMV == LsnGRzSXMV){EJBMOmSylt = true;}
      if(ruQrlQjgZO == true){ruQrlQjgZO = false;}
      if(IIuAnppZBM == true){IIuAnppZBM = false;}
      if(MwwONAPzMt == true){MwwONAPzMt = false;}
      if(cePzJCzoSa == true){cePzJCzoSa = false;}
      if(wXYRjCymRa == true){wXYRjCymRa = false;}
      if(IrVAIuzCdk == true){IrVAIuzCdk = false;}
      if(BkTfkdswpk == true){BkTfkdswpk = false;}
      if(qBGaPnWddK == true){qBGaPnWddK = false;}
      if(CbglkkIPpN == true){CbglkkIPpN = false;}
      if(DxKgZLDsgG == true){DxKgZLDsgG = false;}
      if(JBxgjGkujU == true){JBxgjGkujU = false;}
      if(YUXSiYEhtA == true){YUXSiYEhtA = false;}
      if(UdFbhtqZBD == true){UdFbhtqZBD = false;}
      if(kdxXBAeACd == true){kdxXBAeACd = false;}
      if(zNeVohYqyA == true){zNeVohYqyA = false;}
      if(HVyfkewUyo == true){HVyfkewUyo = false;}
      if(PLtfitXzRh == true){PLtfitXzRh = false;}
      if(tEfPBHyimA == true){tEfPBHyimA = false;}
      if(UzaAwOeQlW == true){UzaAwOeQlW = false;}
      if(EJBMOmSylt == true){EJBMOmSylt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVCGUTRKEI
{ 
  void DgMaLjrfeD()
  { 
      bool PPSREmeAFd = false;
      bool uRBdJkewfU = false;
      bool MJSUihBIkp = false;
      bool VhIMlukteB = false;
      bool MriRGljZMf = false;
      bool tqgKkFwxiW = false;
      bool lWOOHNInrN = false;
      bool zjQdITZBOw = false;
      bool yawEweAxbg = false;
      bool zmLIPodTJs = false;
      bool cuhyfJZCCQ = false;
      bool euilYKZJSc = false;
      bool MKMLNMYINS = false;
      bool pFqVSCsxYl = false;
      bool FxuKBEEYiF = false;
      bool PTBgfSiWjT = false;
      bool jRniZYDNTW = false;
      bool QckfXOOBJJ = false;
      bool IAYIDWEJoA = false;
      bool SWMFBmJMjb = false;
      string YuKWaPqDaR;
      string iSzigxjUaZ;
      string pQZItdYReb;
      string HtEINseize;
      string IFKMGheyjc;
      string kfkTzHVBbw;
      string pYXzJnNqVm;
      string SBUwRjGMCM;
      string zZhBpbJkIF;
      string WcGCnjgKCS;
      string TncwKjKoCP;
      string BIzPxQqWIg;
      string dchPPotRHh;
      string CuJjrKxkqG;
      string RUhsEOdpFX;
      string rKCUnpGMfU;
      string orgUMFyOWm;
      string SFeCPJuoLB;
      string KEMjorsowC;
      string DkEVQYmNfy;
      if(YuKWaPqDaR == TncwKjKoCP){PPSREmeAFd = true;}
      else if(TncwKjKoCP == YuKWaPqDaR){cuhyfJZCCQ = true;}
      if(iSzigxjUaZ == BIzPxQqWIg){uRBdJkewfU = true;}
      else if(BIzPxQqWIg == iSzigxjUaZ){euilYKZJSc = true;}
      if(pQZItdYReb == dchPPotRHh){MJSUihBIkp = true;}
      else if(dchPPotRHh == pQZItdYReb){MKMLNMYINS = true;}
      if(HtEINseize == CuJjrKxkqG){VhIMlukteB = true;}
      else if(CuJjrKxkqG == HtEINseize){pFqVSCsxYl = true;}
      if(IFKMGheyjc == RUhsEOdpFX){MriRGljZMf = true;}
      else if(RUhsEOdpFX == IFKMGheyjc){FxuKBEEYiF = true;}
      if(kfkTzHVBbw == rKCUnpGMfU){tqgKkFwxiW = true;}
      else if(rKCUnpGMfU == kfkTzHVBbw){PTBgfSiWjT = true;}
      if(pYXzJnNqVm == orgUMFyOWm){lWOOHNInrN = true;}
      else if(orgUMFyOWm == pYXzJnNqVm){jRniZYDNTW = true;}
      if(SBUwRjGMCM == SFeCPJuoLB){zjQdITZBOw = true;}
      if(zZhBpbJkIF == KEMjorsowC){yawEweAxbg = true;}
      if(WcGCnjgKCS == DkEVQYmNfy){zmLIPodTJs = true;}
      while(SFeCPJuoLB == SBUwRjGMCM){QckfXOOBJJ = true;}
      while(KEMjorsowC == KEMjorsowC){IAYIDWEJoA = true;}
      while(DkEVQYmNfy == DkEVQYmNfy){SWMFBmJMjb = true;}
      if(PPSREmeAFd == true){PPSREmeAFd = false;}
      if(uRBdJkewfU == true){uRBdJkewfU = false;}
      if(MJSUihBIkp == true){MJSUihBIkp = false;}
      if(VhIMlukteB == true){VhIMlukteB = false;}
      if(MriRGljZMf == true){MriRGljZMf = false;}
      if(tqgKkFwxiW == true){tqgKkFwxiW = false;}
      if(lWOOHNInrN == true){lWOOHNInrN = false;}
      if(zjQdITZBOw == true){zjQdITZBOw = false;}
      if(yawEweAxbg == true){yawEweAxbg = false;}
      if(zmLIPodTJs == true){zmLIPodTJs = false;}
      if(cuhyfJZCCQ == true){cuhyfJZCCQ = false;}
      if(euilYKZJSc == true){euilYKZJSc = false;}
      if(MKMLNMYINS == true){MKMLNMYINS = false;}
      if(pFqVSCsxYl == true){pFqVSCsxYl = false;}
      if(FxuKBEEYiF == true){FxuKBEEYiF = false;}
      if(PTBgfSiWjT == true){PTBgfSiWjT = false;}
      if(jRniZYDNTW == true){jRniZYDNTW = false;}
      if(QckfXOOBJJ == true){QckfXOOBJJ = false;}
      if(IAYIDWEJoA == true){IAYIDWEJoA = false;}
      if(SWMFBmJMjb == true){SWMFBmJMjb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKHBAVVSNM
{ 
  void nmOQainYkn()
  { 
      bool fEFGRTRnsW = false;
      bool qhrGVUikAw = false;
      bool AJKEwYXrWT = false;
      bool CSNwTccnLl = false;
      bool pKjFxnLalU = false;
      bool gnqWqVtBJs = false;
      bool wYQYTYTulr = false;
      bool ruYNFpZEGI = false;
      bool MxFClOaqFy = false;
      bool haeSpQsKlX = false;
      bool UPntblPcRB = false;
      bool wptBfySOmF = false;
      bool ycpnKQPGXn = false;
      bool wPRimxILZz = false;
      bool zyZDCrgclq = false;
      bool xeXgZrYAiK = false;
      bool VIFcFfYLNh = false;
      bool pHomGADllR = false;
      bool jlTfqQqkIu = false;
      bool XHbOcprwyV = false;
      string NOBtxtfuTQ;
      string eQuaKqorsY;
      string hEBwGkjXwh;
      string qnWlBbLXrQ;
      string adtiFEdlJI;
      string DyOkiJMFmM;
      string KHzlYptIYi;
      string fRAcyEJRqC;
      string HxOnesZkCr;
      string OGjeGSdIJO;
      string KUNackykme;
      string AuOkFMsLGf;
      string PIFfTYhUWf;
      string ZAHbqljnLs;
      string tnyXqTqzZs;
      string YRBdyBPgGD;
      string DdOGEzmmsT;
      string bFANkbJgnA;
      string ghtcGHzcco;
      string WDgHpQYqTr;
      if(NOBtxtfuTQ == KUNackykme){fEFGRTRnsW = true;}
      else if(KUNackykme == NOBtxtfuTQ){UPntblPcRB = true;}
      if(eQuaKqorsY == AuOkFMsLGf){qhrGVUikAw = true;}
      else if(AuOkFMsLGf == eQuaKqorsY){wptBfySOmF = true;}
      if(hEBwGkjXwh == PIFfTYhUWf){AJKEwYXrWT = true;}
      else if(PIFfTYhUWf == hEBwGkjXwh){ycpnKQPGXn = true;}
      if(qnWlBbLXrQ == ZAHbqljnLs){CSNwTccnLl = true;}
      else if(ZAHbqljnLs == qnWlBbLXrQ){wPRimxILZz = true;}
      if(adtiFEdlJI == tnyXqTqzZs){pKjFxnLalU = true;}
      else if(tnyXqTqzZs == adtiFEdlJI){zyZDCrgclq = true;}
      if(DyOkiJMFmM == YRBdyBPgGD){gnqWqVtBJs = true;}
      else if(YRBdyBPgGD == DyOkiJMFmM){xeXgZrYAiK = true;}
      if(KHzlYptIYi == DdOGEzmmsT){wYQYTYTulr = true;}
      else if(DdOGEzmmsT == KHzlYptIYi){VIFcFfYLNh = true;}
      if(fRAcyEJRqC == bFANkbJgnA){ruYNFpZEGI = true;}
      if(HxOnesZkCr == ghtcGHzcco){MxFClOaqFy = true;}
      if(OGjeGSdIJO == WDgHpQYqTr){haeSpQsKlX = true;}
      while(bFANkbJgnA == fRAcyEJRqC){pHomGADllR = true;}
      while(ghtcGHzcco == ghtcGHzcco){jlTfqQqkIu = true;}
      while(WDgHpQYqTr == WDgHpQYqTr){XHbOcprwyV = true;}
      if(fEFGRTRnsW == true){fEFGRTRnsW = false;}
      if(qhrGVUikAw == true){qhrGVUikAw = false;}
      if(AJKEwYXrWT == true){AJKEwYXrWT = false;}
      if(CSNwTccnLl == true){CSNwTccnLl = false;}
      if(pKjFxnLalU == true){pKjFxnLalU = false;}
      if(gnqWqVtBJs == true){gnqWqVtBJs = false;}
      if(wYQYTYTulr == true){wYQYTYTulr = false;}
      if(ruYNFpZEGI == true){ruYNFpZEGI = false;}
      if(MxFClOaqFy == true){MxFClOaqFy = false;}
      if(haeSpQsKlX == true){haeSpQsKlX = false;}
      if(UPntblPcRB == true){UPntblPcRB = false;}
      if(wptBfySOmF == true){wptBfySOmF = false;}
      if(ycpnKQPGXn == true){ycpnKQPGXn = false;}
      if(wPRimxILZz == true){wPRimxILZz = false;}
      if(zyZDCrgclq == true){zyZDCrgclq = false;}
      if(xeXgZrYAiK == true){xeXgZrYAiK = false;}
      if(VIFcFfYLNh == true){VIFcFfYLNh = false;}
      if(pHomGADllR == true){pHomGADllR = false;}
      if(jlTfqQqkIu == true){jlTfqQqkIu = false;}
      if(XHbOcprwyV == true){XHbOcprwyV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYAKREMSVF
{ 
  void ThXSNzmZii()
  { 
      bool YWcmPMnRMA = false;
      bool airHEjLgZC = false;
      bool jpnDxPkGfO = false;
      bool unyUNJlUMR = false;
      bool uwowdFoANO = false;
      bool klUIiihYpA = false;
      bool bhkxEmjXtt = false;
      bool xqUIHmAqZq = false;
      bool ZjsRcISokd = false;
      bool aNdMpMLrqq = false;
      bool VRGTRtRMAw = false;
      bool hqzzZqnTUw = false;
      bool TulPSiMISu = false;
      bool bIAhVIcZAh = false;
      bool qGnowjOely = false;
      bool YqWuWaeqAh = false;
      bool gJtFTYqQdQ = false;
      bool OOSlEMGwSh = false;
      bool UhVTWjkEKt = false;
      bool dkYRBhMhVW = false;
      string cXXHhjcxot;
      string FfsAUYHbyb;
      string cjbBYcWiuN;
      string ykKCSfdtzl;
      string rqAzdPrUkT;
      string OeKWUrwWiE;
      string NsCbwTVpgn;
      string uNcMikjcXJ;
      string jCyaySamha;
      string jGLtXznYCJ;
      string sBmxYBBxni;
      string ISzYULtacc;
      string siIGDnBhni;
      string xKaNPhOBCx;
      string QczyRQHlZM;
      string FNwYQKsgsj;
      string zTJElyrkJl;
      string wsYeLPiKnl;
      string fPIbdiNCxF;
      string ogHRyxTuLT;
      if(cXXHhjcxot == sBmxYBBxni){YWcmPMnRMA = true;}
      else if(sBmxYBBxni == cXXHhjcxot){VRGTRtRMAw = true;}
      if(FfsAUYHbyb == ISzYULtacc){airHEjLgZC = true;}
      else if(ISzYULtacc == FfsAUYHbyb){hqzzZqnTUw = true;}
      if(cjbBYcWiuN == siIGDnBhni){jpnDxPkGfO = true;}
      else if(siIGDnBhni == cjbBYcWiuN){TulPSiMISu = true;}
      if(ykKCSfdtzl == xKaNPhOBCx){unyUNJlUMR = true;}
      else if(xKaNPhOBCx == ykKCSfdtzl){bIAhVIcZAh = true;}
      if(rqAzdPrUkT == QczyRQHlZM){uwowdFoANO = true;}
      else if(QczyRQHlZM == rqAzdPrUkT){qGnowjOely = true;}
      if(OeKWUrwWiE == FNwYQKsgsj){klUIiihYpA = true;}
      else if(FNwYQKsgsj == OeKWUrwWiE){YqWuWaeqAh = true;}
      if(NsCbwTVpgn == zTJElyrkJl){bhkxEmjXtt = true;}
      else if(zTJElyrkJl == NsCbwTVpgn){gJtFTYqQdQ = true;}
      if(uNcMikjcXJ == wsYeLPiKnl){xqUIHmAqZq = true;}
      if(jCyaySamha == fPIbdiNCxF){ZjsRcISokd = true;}
      if(jGLtXznYCJ == ogHRyxTuLT){aNdMpMLrqq = true;}
      while(wsYeLPiKnl == uNcMikjcXJ){OOSlEMGwSh = true;}
      while(fPIbdiNCxF == fPIbdiNCxF){UhVTWjkEKt = true;}
      while(ogHRyxTuLT == ogHRyxTuLT){dkYRBhMhVW = true;}
      if(YWcmPMnRMA == true){YWcmPMnRMA = false;}
      if(airHEjLgZC == true){airHEjLgZC = false;}
      if(jpnDxPkGfO == true){jpnDxPkGfO = false;}
      if(unyUNJlUMR == true){unyUNJlUMR = false;}
      if(uwowdFoANO == true){uwowdFoANO = false;}
      if(klUIiihYpA == true){klUIiihYpA = false;}
      if(bhkxEmjXtt == true){bhkxEmjXtt = false;}
      if(xqUIHmAqZq == true){xqUIHmAqZq = false;}
      if(ZjsRcISokd == true){ZjsRcISokd = false;}
      if(aNdMpMLrqq == true){aNdMpMLrqq = false;}
      if(VRGTRtRMAw == true){VRGTRtRMAw = false;}
      if(hqzzZqnTUw == true){hqzzZqnTUw = false;}
      if(TulPSiMISu == true){TulPSiMISu = false;}
      if(bIAhVIcZAh == true){bIAhVIcZAh = false;}
      if(qGnowjOely == true){qGnowjOely = false;}
      if(YqWuWaeqAh == true){YqWuWaeqAh = false;}
      if(gJtFTYqQdQ == true){gJtFTYqQdQ = false;}
      if(OOSlEMGwSh == true){OOSlEMGwSh = false;}
      if(UhVTWjkEKt == true){UhVTWjkEKt = false;}
      if(dkYRBhMhVW == true){dkYRBhMhVW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCXSQUBYZH
{ 
  void LgijmYWHER()
  { 
      bool dVDhczTnLb = false;
      bool HyXGtWNPhr = false;
      bool UXNeflPSkd = false;
      bool dLBwHRFJSw = false;
      bool HtsCclzBmO = false;
      bool XkyGAGIYCq = false;
      bool iADhywwbyb = false;
      bool QDwkjaeLBt = false;
      bool mOfWGsMuuB = false;
      bool JgHbMHqLEg = false;
      bool oWCKyTnMVZ = false;
      bool bxXIDUTgaE = false;
      bool iBfwSjwUYc = false;
      bool iSGTEPLVXm = false;
      bool EzYVZLIyXq = false;
      bool mKjzxnpGqO = false;
      bool WTnspIpDEn = false;
      bool JyImAjbJWG = false;
      bool aywgoYiGWQ = false;
      bool YFdJQkKffQ = false;
      string ETsuCPxzCT;
      string teUkCDJdVW;
      string dKsfEHwkik;
      string XuTXTqGKpc;
      string HAQdwPLAxh;
      string IjnLrsZNpt;
      string SLQQuyLwRK;
      string wymsOdtPio;
      string wwmAbnHHeZ;
      string RsUwJuizix;
      string DOhlkKxuwN;
      string zJdAxWYPnG;
      string qDQrsDdqiS;
      string utgkkhNAPR;
      string qMKQZHOTyl;
      string WTLbGAxpsh;
      string gGLdSEcrPP;
      string JXAWPerzRl;
      string nJrwuaiFek;
      string jWHgkkAgyV;
      if(ETsuCPxzCT == DOhlkKxuwN){dVDhczTnLb = true;}
      else if(DOhlkKxuwN == ETsuCPxzCT){oWCKyTnMVZ = true;}
      if(teUkCDJdVW == zJdAxWYPnG){HyXGtWNPhr = true;}
      else if(zJdAxWYPnG == teUkCDJdVW){bxXIDUTgaE = true;}
      if(dKsfEHwkik == qDQrsDdqiS){UXNeflPSkd = true;}
      else if(qDQrsDdqiS == dKsfEHwkik){iBfwSjwUYc = true;}
      if(XuTXTqGKpc == utgkkhNAPR){dLBwHRFJSw = true;}
      else if(utgkkhNAPR == XuTXTqGKpc){iSGTEPLVXm = true;}
      if(HAQdwPLAxh == qMKQZHOTyl){HtsCclzBmO = true;}
      else if(qMKQZHOTyl == HAQdwPLAxh){EzYVZLIyXq = true;}
      if(IjnLrsZNpt == WTLbGAxpsh){XkyGAGIYCq = true;}
      else if(WTLbGAxpsh == IjnLrsZNpt){mKjzxnpGqO = true;}
      if(SLQQuyLwRK == gGLdSEcrPP){iADhywwbyb = true;}
      else if(gGLdSEcrPP == SLQQuyLwRK){WTnspIpDEn = true;}
      if(wymsOdtPio == JXAWPerzRl){QDwkjaeLBt = true;}
      if(wwmAbnHHeZ == nJrwuaiFek){mOfWGsMuuB = true;}
      if(RsUwJuizix == jWHgkkAgyV){JgHbMHqLEg = true;}
      while(JXAWPerzRl == wymsOdtPio){JyImAjbJWG = true;}
      while(nJrwuaiFek == nJrwuaiFek){aywgoYiGWQ = true;}
      while(jWHgkkAgyV == jWHgkkAgyV){YFdJQkKffQ = true;}
      if(dVDhczTnLb == true){dVDhczTnLb = false;}
      if(HyXGtWNPhr == true){HyXGtWNPhr = false;}
      if(UXNeflPSkd == true){UXNeflPSkd = false;}
      if(dLBwHRFJSw == true){dLBwHRFJSw = false;}
      if(HtsCclzBmO == true){HtsCclzBmO = false;}
      if(XkyGAGIYCq == true){XkyGAGIYCq = false;}
      if(iADhywwbyb == true){iADhywwbyb = false;}
      if(QDwkjaeLBt == true){QDwkjaeLBt = false;}
      if(mOfWGsMuuB == true){mOfWGsMuuB = false;}
      if(JgHbMHqLEg == true){JgHbMHqLEg = false;}
      if(oWCKyTnMVZ == true){oWCKyTnMVZ = false;}
      if(bxXIDUTgaE == true){bxXIDUTgaE = false;}
      if(iBfwSjwUYc == true){iBfwSjwUYc = false;}
      if(iSGTEPLVXm == true){iSGTEPLVXm = false;}
      if(EzYVZLIyXq == true){EzYVZLIyXq = false;}
      if(mKjzxnpGqO == true){mKjzxnpGqO = false;}
      if(WTnspIpDEn == true){WTnspIpDEn = false;}
      if(JyImAjbJWG == true){JyImAjbJWG = false;}
      if(aywgoYiGWQ == true){aywgoYiGWQ = false;}
      if(YFdJQkKffQ == true){YFdJQkKffQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KFHQGKTPCH
{ 
  void xGDUQobUhU()
  { 
      bool ggiDtZiNfJ = false;
      bool PcIbbytpQS = false;
      bool eMkokELiRz = false;
      bool fChElukEer = false;
      bool BYxsFxxdQp = false;
      bool cahHZUutSp = false;
      bool NzugdNtEof = false;
      bool MoKXQGOrin = false;
      bool GhRbWETZeR = false;
      bool AqlndBcPPr = false;
      bool CsnjcmPJpS = false;
      bool FDLdjfhTKY = false;
      bool sTYXfVDVsO = false;
      bool dzbpkMshyj = false;
      bool nJiLLxeIEy = false;
      bool TJFpyhTPDH = false;
      bool jtQboGaUrW = false;
      bool lzVakjjNMi = false;
      bool ptRutUskrD = false;
      bool rcdqztsHWF = false;
      string pjebLMTjmi;
      string BASjhcdqWp;
      string idgltLCLOf;
      string jtpFHxLXjB;
      string TEozrJgbXR;
      string ohROdMDrgz;
      string KHVGzHJMbk;
      string QFHVVengtk;
      string eZnxqBcabu;
      string tTpjpLihAk;
      string zUAlAiausz;
      string XWywUkTXOx;
      string dijgqxPXeK;
      string uGfJlJZBwI;
      string aghcWWUtOF;
      string rKTCGQjSuD;
      string TDPiDRpnKK;
      string KRbGWxBHJT;
      string bUIZRklcCU;
      string ZGFrnWRzZF;
      if(pjebLMTjmi == zUAlAiausz){ggiDtZiNfJ = true;}
      else if(zUAlAiausz == pjebLMTjmi){CsnjcmPJpS = true;}
      if(BASjhcdqWp == XWywUkTXOx){PcIbbytpQS = true;}
      else if(XWywUkTXOx == BASjhcdqWp){FDLdjfhTKY = true;}
      if(idgltLCLOf == dijgqxPXeK){eMkokELiRz = true;}
      else if(dijgqxPXeK == idgltLCLOf){sTYXfVDVsO = true;}
      if(jtpFHxLXjB == uGfJlJZBwI){fChElukEer = true;}
      else if(uGfJlJZBwI == jtpFHxLXjB){dzbpkMshyj = true;}
      if(TEozrJgbXR == aghcWWUtOF){BYxsFxxdQp = true;}
      else if(aghcWWUtOF == TEozrJgbXR){nJiLLxeIEy = true;}
      if(ohROdMDrgz == rKTCGQjSuD){cahHZUutSp = true;}
      else if(rKTCGQjSuD == ohROdMDrgz){TJFpyhTPDH = true;}
      if(KHVGzHJMbk == TDPiDRpnKK){NzugdNtEof = true;}
      else if(TDPiDRpnKK == KHVGzHJMbk){jtQboGaUrW = true;}
      if(QFHVVengtk == KRbGWxBHJT){MoKXQGOrin = true;}
      if(eZnxqBcabu == bUIZRklcCU){GhRbWETZeR = true;}
      if(tTpjpLihAk == ZGFrnWRzZF){AqlndBcPPr = true;}
      while(KRbGWxBHJT == QFHVVengtk){lzVakjjNMi = true;}
      while(bUIZRklcCU == bUIZRklcCU){ptRutUskrD = true;}
      while(ZGFrnWRzZF == ZGFrnWRzZF){rcdqztsHWF = true;}
      if(ggiDtZiNfJ == true){ggiDtZiNfJ = false;}
      if(PcIbbytpQS == true){PcIbbytpQS = false;}
      if(eMkokELiRz == true){eMkokELiRz = false;}
      if(fChElukEer == true){fChElukEer = false;}
      if(BYxsFxxdQp == true){BYxsFxxdQp = false;}
      if(cahHZUutSp == true){cahHZUutSp = false;}
      if(NzugdNtEof == true){NzugdNtEof = false;}
      if(MoKXQGOrin == true){MoKXQGOrin = false;}
      if(GhRbWETZeR == true){GhRbWETZeR = false;}
      if(AqlndBcPPr == true){AqlndBcPPr = false;}
      if(CsnjcmPJpS == true){CsnjcmPJpS = false;}
      if(FDLdjfhTKY == true){FDLdjfhTKY = false;}
      if(sTYXfVDVsO == true){sTYXfVDVsO = false;}
      if(dzbpkMshyj == true){dzbpkMshyj = false;}
      if(nJiLLxeIEy == true){nJiLLxeIEy = false;}
      if(TJFpyhTPDH == true){TJFpyhTPDH = false;}
      if(jtQboGaUrW == true){jtQboGaUrW = false;}
      if(lzVakjjNMi == true){lzVakjjNMi = false;}
      if(ptRutUskrD == true){ptRutUskrD = false;}
      if(rcdqztsHWF == true){rcdqztsHWF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ATZJAYALQX
{ 
  void isSgMGPoGW()
  { 
      bool nZTShgwDwp = false;
      bool lTcoJiFRhG = false;
      bool hczIthmuSO = false;
      bool PHdflJhemX = false;
      bool snrbQiDbhV = false;
      bool XKQHnLZKXA = false;
      bool tAkgadowDA = false;
      bool BZdKNtkXqL = false;
      bool dLNwqEpVqa = false;
      bool iWHmdrCKBl = false;
      bool sGXgTxfGtt = false;
      bool ZCTMVhmopV = false;
      bool nSFcQeSqfV = false;
      bool raVERWmfbt = false;
      bool XjbxAgCtRu = false;
      bool ENTeyaBuQo = false;
      bool doZXBzfPuy = false;
      bool tHMwxDqHbj = false;
      bool bXYkReGpFq = false;
      bool VrOmPiJDuB = false;
      string RgPDajZnGl;
      string pMQjcBlMdD;
      string RPoHTgQJKm;
      string JNGfrtRUVp;
      string nkIsRoBXeE;
      string gIsrABrHjs;
      string SQdTbbFjqi;
      string jQpnOfHupd;
      string frdFFAUOfq;
      string CJkcWXHoQo;
      string iQfwTQSEcU;
      string swRGMZlXNa;
      string HqEAfafNRp;
      string YSdAuPMgko;
      string hPkKxFqePw;
      string liaphrMfPs;
      string jEmlwZRRLx;
      string NEmXsrFsDZ;
      string iByVEoqnRC;
      string CfRrFdbyOW;
      if(RgPDajZnGl == iQfwTQSEcU){nZTShgwDwp = true;}
      else if(iQfwTQSEcU == RgPDajZnGl){sGXgTxfGtt = true;}
      if(pMQjcBlMdD == swRGMZlXNa){lTcoJiFRhG = true;}
      else if(swRGMZlXNa == pMQjcBlMdD){ZCTMVhmopV = true;}
      if(RPoHTgQJKm == HqEAfafNRp){hczIthmuSO = true;}
      else if(HqEAfafNRp == RPoHTgQJKm){nSFcQeSqfV = true;}
      if(JNGfrtRUVp == YSdAuPMgko){PHdflJhemX = true;}
      else if(YSdAuPMgko == JNGfrtRUVp){raVERWmfbt = true;}
      if(nkIsRoBXeE == hPkKxFqePw){snrbQiDbhV = true;}
      else if(hPkKxFqePw == nkIsRoBXeE){XjbxAgCtRu = true;}
      if(gIsrABrHjs == liaphrMfPs){XKQHnLZKXA = true;}
      else if(liaphrMfPs == gIsrABrHjs){ENTeyaBuQo = true;}
      if(SQdTbbFjqi == jEmlwZRRLx){tAkgadowDA = true;}
      else if(jEmlwZRRLx == SQdTbbFjqi){doZXBzfPuy = true;}
      if(jQpnOfHupd == NEmXsrFsDZ){BZdKNtkXqL = true;}
      if(frdFFAUOfq == iByVEoqnRC){dLNwqEpVqa = true;}
      if(CJkcWXHoQo == CfRrFdbyOW){iWHmdrCKBl = true;}
      while(NEmXsrFsDZ == jQpnOfHupd){tHMwxDqHbj = true;}
      while(iByVEoqnRC == iByVEoqnRC){bXYkReGpFq = true;}
      while(CfRrFdbyOW == CfRrFdbyOW){VrOmPiJDuB = true;}
      if(nZTShgwDwp == true){nZTShgwDwp = false;}
      if(lTcoJiFRhG == true){lTcoJiFRhG = false;}
      if(hczIthmuSO == true){hczIthmuSO = false;}
      if(PHdflJhemX == true){PHdflJhemX = false;}
      if(snrbQiDbhV == true){snrbQiDbhV = false;}
      if(XKQHnLZKXA == true){XKQHnLZKXA = false;}
      if(tAkgadowDA == true){tAkgadowDA = false;}
      if(BZdKNtkXqL == true){BZdKNtkXqL = false;}
      if(dLNwqEpVqa == true){dLNwqEpVqa = false;}
      if(iWHmdrCKBl == true){iWHmdrCKBl = false;}
      if(sGXgTxfGtt == true){sGXgTxfGtt = false;}
      if(ZCTMVhmopV == true){ZCTMVhmopV = false;}
      if(nSFcQeSqfV == true){nSFcQeSqfV = false;}
      if(raVERWmfbt == true){raVERWmfbt = false;}
      if(XjbxAgCtRu == true){XjbxAgCtRu = false;}
      if(ENTeyaBuQo == true){ENTeyaBuQo = false;}
      if(doZXBzfPuy == true){doZXBzfPuy = false;}
      if(tHMwxDqHbj == true){tHMwxDqHbj = false;}
      if(bXYkReGpFq == true){bXYkReGpFq = false;}
      if(VrOmPiJDuB == true){VrOmPiJDuB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBHZVLZZHQ
{ 
  void psApTziaQs()
  { 
      bool XeKrRxTJUe = false;
      bool giuuzkwCXt = false;
      bool AtLhTymOUj = false;
      bool FmKoMtVPPh = false;
      bool EdWuTcpBdw = false;
      bool APCKEcScXT = false;
      bool KFnkYsXGhF = false;
      bool OflopVWQNq = false;
      bool IkjXiokAjj = false;
      bool bsqwWzolVZ = false;
      bool EiSYgTdMUi = false;
      bool FBOgKYUQBj = false;
      bool IXVydVooRq = false;
      bool gjtnlYRLqO = false;
      bool LXfBdZdJkx = false;
      bool dYklRgNUtL = false;
      bool entcBVHaul = false;
      bool HIZlXjqUUE = false;
      bool qeETMIzIVE = false;
      bool LxRejXcCAH = false;
      string KkNPqOWOan;
      string rFongdgFdK;
      string OOdnEAyKCh;
      string UrSZYxGhHe;
      string EUEBeXCsJl;
      string piTWyuHYKp;
      string QMMrSAlPPj;
      string WyyyFtKbIf;
      string yEBQqlYubc;
      string ogXQNrIMhe;
      string kmcZOrkURE;
      string kfQdrLLuBg;
      string bqmltpagjN;
      string kysduLbbCz;
      string ADdXrJQsYB;
      string gMKBDtzpeX;
      string REkDSmllif;
      string jisBfXNPtj;
      string YgHhfXmrZA;
      string MlwdgwSZEF;
      if(KkNPqOWOan == kmcZOrkURE){XeKrRxTJUe = true;}
      else if(kmcZOrkURE == KkNPqOWOan){EiSYgTdMUi = true;}
      if(rFongdgFdK == kfQdrLLuBg){giuuzkwCXt = true;}
      else if(kfQdrLLuBg == rFongdgFdK){FBOgKYUQBj = true;}
      if(OOdnEAyKCh == bqmltpagjN){AtLhTymOUj = true;}
      else if(bqmltpagjN == OOdnEAyKCh){IXVydVooRq = true;}
      if(UrSZYxGhHe == kysduLbbCz){FmKoMtVPPh = true;}
      else if(kysduLbbCz == UrSZYxGhHe){gjtnlYRLqO = true;}
      if(EUEBeXCsJl == ADdXrJQsYB){EdWuTcpBdw = true;}
      else if(ADdXrJQsYB == EUEBeXCsJl){LXfBdZdJkx = true;}
      if(piTWyuHYKp == gMKBDtzpeX){APCKEcScXT = true;}
      else if(gMKBDtzpeX == piTWyuHYKp){dYklRgNUtL = true;}
      if(QMMrSAlPPj == REkDSmllif){KFnkYsXGhF = true;}
      else if(REkDSmllif == QMMrSAlPPj){entcBVHaul = true;}
      if(WyyyFtKbIf == jisBfXNPtj){OflopVWQNq = true;}
      if(yEBQqlYubc == YgHhfXmrZA){IkjXiokAjj = true;}
      if(ogXQNrIMhe == MlwdgwSZEF){bsqwWzolVZ = true;}
      while(jisBfXNPtj == WyyyFtKbIf){HIZlXjqUUE = true;}
      while(YgHhfXmrZA == YgHhfXmrZA){qeETMIzIVE = true;}
      while(MlwdgwSZEF == MlwdgwSZEF){LxRejXcCAH = true;}
      if(XeKrRxTJUe == true){XeKrRxTJUe = false;}
      if(giuuzkwCXt == true){giuuzkwCXt = false;}
      if(AtLhTymOUj == true){AtLhTymOUj = false;}
      if(FmKoMtVPPh == true){FmKoMtVPPh = false;}
      if(EdWuTcpBdw == true){EdWuTcpBdw = false;}
      if(APCKEcScXT == true){APCKEcScXT = false;}
      if(KFnkYsXGhF == true){KFnkYsXGhF = false;}
      if(OflopVWQNq == true){OflopVWQNq = false;}
      if(IkjXiokAjj == true){IkjXiokAjj = false;}
      if(bsqwWzolVZ == true){bsqwWzolVZ = false;}
      if(EiSYgTdMUi == true){EiSYgTdMUi = false;}
      if(FBOgKYUQBj == true){FBOgKYUQBj = false;}
      if(IXVydVooRq == true){IXVydVooRq = false;}
      if(gjtnlYRLqO == true){gjtnlYRLqO = false;}
      if(LXfBdZdJkx == true){LXfBdZdJkx = false;}
      if(dYklRgNUtL == true){dYklRgNUtL = false;}
      if(entcBVHaul == true){entcBVHaul = false;}
      if(HIZlXjqUUE == true){HIZlXjqUUE = false;}
      if(qeETMIzIVE == true){qeETMIzIVE = false;}
      if(LxRejXcCAH == true){LxRejXcCAH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASQTWFEPCD
{ 
  void nDbhimyzgP()
  { 
      bool upydOIxVeL = false;
      bool PtAIzyGGJd = false;
      bool bRgXINkyDG = false;
      bool yasCUHlgqZ = false;
      bool eadJtDwCDi = false;
      bool sGhkncJaUA = false;
      bool XySYNoBymr = false;
      bool LZPiyAnWcE = false;
      bool QhuTNrrINr = false;
      bool xLLpCgIFuF = false;
      bool CyOKWSpyln = false;
      bool olyQjoDyKV = false;
      bool wrjutANYfR = false;
      bool qhbWBRTjwt = false;
      bool BtWZDLMuFN = false;
      bool dKuZJKNTQW = false;
      bool FRRUwHKbOR = false;
      bool VSBQUCVKri = false;
      bool nRSSmfmBMq = false;
      bool DzTZoibBcw = false;
      string rxGsraTENr;
      string tBAtDSleKs;
      string XxUJmzCpLr;
      string mrdQPVkMmb;
      string QtgPJIQGsV;
      string ZFaKMubwFr;
      string YdrVFBWidg;
      string gYqhbdQFAe;
      string iuwpRgRTEU;
      string toHtDmBKJH;
      string lgcLoAOrhi;
      string eWuaJcgCDY;
      string jDdImqRweo;
      string bFusrBRjAR;
      string RZkVpWsgkZ;
      string FzHkWhDTYx;
      string iRMsGYbChH;
      string LwBlGKSISP;
      string ykLFicxJVK;
      string yxLDhzMqOQ;
      if(rxGsraTENr == lgcLoAOrhi){upydOIxVeL = true;}
      else if(lgcLoAOrhi == rxGsraTENr){CyOKWSpyln = true;}
      if(tBAtDSleKs == eWuaJcgCDY){PtAIzyGGJd = true;}
      else if(eWuaJcgCDY == tBAtDSleKs){olyQjoDyKV = true;}
      if(XxUJmzCpLr == jDdImqRweo){bRgXINkyDG = true;}
      else if(jDdImqRweo == XxUJmzCpLr){wrjutANYfR = true;}
      if(mrdQPVkMmb == bFusrBRjAR){yasCUHlgqZ = true;}
      else if(bFusrBRjAR == mrdQPVkMmb){qhbWBRTjwt = true;}
      if(QtgPJIQGsV == RZkVpWsgkZ){eadJtDwCDi = true;}
      else if(RZkVpWsgkZ == QtgPJIQGsV){BtWZDLMuFN = true;}
      if(ZFaKMubwFr == FzHkWhDTYx){sGhkncJaUA = true;}
      else if(FzHkWhDTYx == ZFaKMubwFr){dKuZJKNTQW = true;}
      if(YdrVFBWidg == iRMsGYbChH){XySYNoBymr = true;}
      else if(iRMsGYbChH == YdrVFBWidg){FRRUwHKbOR = true;}
      if(gYqhbdQFAe == LwBlGKSISP){LZPiyAnWcE = true;}
      if(iuwpRgRTEU == ykLFicxJVK){QhuTNrrINr = true;}
      if(toHtDmBKJH == yxLDhzMqOQ){xLLpCgIFuF = true;}
      while(LwBlGKSISP == gYqhbdQFAe){VSBQUCVKri = true;}
      while(ykLFicxJVK == ykLFicxJVK){nRSSmfmBMq = true;}
      while(yxLDhzMqOQ == yxLDhzMqOQ){DzTZoibBcw = true;}
      if(upydOIxVeL == true){upydOIxVeL = false;}
      if(PtAIzyGGJd == true){PtAIzyGGJd = false;}
      if(bRgXINkyDG == true){bRgXINkyDG = false;}
      if(yasCUHlgqZ == true){yasCUHlgqZ = false;}
      if(eadJtDwCDi == true){eadJtDwCDi = false;}
      if(sGhkncJaUA == true){sGhkncJaUA = false;}
      if(XySYNoBymr == true){XySYNoBymr = false;}
      if(LZPiyAnWcE == true){LZPiyAnWcE = false;}
      if(QhuTNrrINr == true){QhuTNrrINr = false;}
      if(xLLpCgIFuF == true){xLLpCgIFuF = false;}
      if(CyOKWSpyln == true){CyOKWSpyln = false;}
      if(olyQjoDyKV == true){olyQjoDyKV = false;}
      if(wrjutANYfR == true){wrjutANYfR = false;}
      if(qhbWBRTjwt == true){qhbWBRTjwt = false;}
      if(BtWZDLMuFN == true){BtWZDLMuFN = false;}
      if(dKuZJKNTQW == true){dKuZJKNTQW = false;}
      if(FRRUwHKbOR == true){FRRUwHKbOR = false;}
      if(VSBQUCVKri == true){VSBQUCVKri = false;}
      if(nRSSmfmBMq == true){nRSSmfmBMq = false;}
      if(DzTZoibBcw == true){DzTZoibBcw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVVLRIZALH
{ 
  void yJwfrbLjru()
  { 
      bool ApxaiyZWfr = false;
      bool YRgprZrABk = false;
      bool WpHZLEkZMx = false;
      bool GZnfsJosqi = false;
      bool KUDynEkDZd = false;
      bool yLEprJhWPd = false;
      bool NAJhlzcAwi = false;
      bool jzIRaBlJkG = false;
      bool SgziztUynj = false;
      bool bScMVKLUMo = false;
      bool akHqtzClPq = false;
      bool WXlJLfBaiq = false;
      bool deLLGRVuwP = false;
      bool pQxwegZHnz = false;
      bool rhhxMDfTBo = false;
      bool JklUKwYujc = false;
      bool cGpzAFaodd = false;
      bool FsljzuxOyD = false;
      bool kBtGGFebki = false;
      bool IeXLVkrhwG = false;
      string ybyJdPDCXD;
      string DVIVlhpOmQ;
      string tCZgPlAOEq;
      string NDTWVJEgnk;
      string XUBFPZiCgK;
      string rRIlzwBQsq;
      string OnyfpzBlAc;
      string cJaCsZAUQo;
      string DxhsywthWZ;
      string HnmxViWUPP;
      string YxCEhiqGsY;
      string ufzDmQGEgs;
      string FTOZUoVdfJ;
      string DfFAQFtcLP;
      string EmoydaniJF;
      string bSnVKEicjs;
      string MNaiVOaylh;
      string VdrQoSeQut;
      string AlUahkrjpM;
      string WRsSDqLFbP;
      if(ybyJdPDCXD == YxCEhiqGsY){ApxaiyZWfr = true;}
      else if(YxCEhiqGsY == ybyJdPDCXD){akHqtzClPq = true;}
      if(DVIVlhpOmQ == ufzDmQGEgs){YRgprZrABk = true;}
      else if(ufzDmQGEgs == DVIVlhpOmQ){WXlJLfBaiq = true;}
      if(tCZgPlAOEq == FTOZUoVdfJ){WpHZLEkZMx = true;}
      else if(FTOZUoVdfJ == tCZgPlAOEq){deLLGRVuwP = true;}
      if(NDTWVJEgnk == DfFAQFtcLP){GZnfsJosqi = true;}
      else if(DfFAQFtcLP == NDTWVJEgnk){pQxwegZHnz = true;}
      if(XUBFPZiCgK == EmoydaniJF){KUDynEkDZd = true;}
      else if(EmoydaniJF == XUBFPZiCgK){rhhxMDfTBo = true;}
      if(rRIlzwBQsq == bSnVKEicjs){yLEprJhWPd = true;}
      else if(bSnVKEicjs == rRIlzwBQsq){JklUKwYujc = true;}
      if(OnyfpzBlAc == MNaiVOaylh){NAJhlzcAwi = true;}
      else if(MNaiVOaylh == OnyfpzBlAc){cGpzAFaodd = true;}
      if(cJaCsZAUQo == VdrQoSeQut){jzIRaBlJkG = true;}
      if(DxhsywthWZ == AlUahkrjpM){SgziztUynj = true;}
      if(HnmxViWUPP == WRsSDqLFbP){bScMVKLUMo = true;}
      while(VdrQoSeQut == cJaCsZAUQo){FsljzuxOyD = true;}
      while(AlUahkrjpM == AlUahkrjpM){kBtGGFebki = true;}
      while(WRsSDqLFbP == WRsSDqLFbP){IeXLVkrhwG = true;}
      if(ApxaiyZWfr == true){ApxaiyZWfr = false;}
      if(YRgprZrABk == true){YRgprZrABk = false;}
      if(WpHZLEkZMx == true){WpHZLEkZMx = false;}
      if(GZnfsJosqi == true){GZnfsJosqi = false;}
      if(KUDynEkDZd == true){KUDynEkDZd = false;}
      if(yLEprJhWPd == true){yLEprJhWPd = false;}
      if(NAJhlzcAwi == true){NAJhlzcAwi = false;}
      if(jzIRaBlJkG == true){jzIRaBlJkG = false;}
      if(SgziztUynj == true){SgziztUynj = false;}
      if(bScMVKLUMo == true){bScMVKLUMo = false;}
      if(akHqtzClPq == true){akHqtzClPq = false;}
      if(WXlJLfBaiq == true){WXlJLfBaiq = false;}
      if(deLLGRVuwP == true){deLLGRVuwP = false;}
      if(pQxwegZHnz == true){pQxwegZHnz = false;}
      if(rhhxMDfTBo == true){rhhxMDfTBo = false;}
      if(JklUKwYujc == true){JklUKwYujc = false;}
      if(cGpzAFaodd == true){cGpzAFaodd = false;}
      if(FsljzuxOyD == true){FsljzuxOyD = false;}
      if(kBtGGFebki == true){kBtGGFebki = false;}
      if(IeXLVkrhwG == true){IeXLVkrhwG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYDYNLWNDU
{ 
  void VAoSkOsVGV()
  { 
      bool OQmTyOtTLQ = false;
      bool peLFYPWZYT = false;
      bool RRMtqjBxGQ = false;
      bool jbWqmGlKeK = false;
      bool FlQxbNdRAO = false;
      bool ElwZGwDrcN = false;
      bool NxMtgOHUSS = false;
      bool cMtNOfAPRc = false;
      bool FiwrMyexkp = false;
      bool DsgQxIZWQN = false;
      bool FJzhkqqiLa = false;
      bool wnZzIdAThi = false;
      bool jKjbOiedPG = false;
      bool FdyEXujOHU = false;
      bool GukJtOShIT = false;
      bool HFnhdtZXSB = false;
      bool MNSFUSpVaM = false;
      bool slMNbnYZhA = false;
      bool PxUwyzoPac = false;
      bool VMuFIscfnb = false;
      string PIJyJtNkfp;
      string hFwcTHzZqH;
      string WNVHQUqKGs;
      string GzGRiXxCPU;
      string xqtMHEFiNW;
      string LscXRClCgn;
      string CCdljizesu;
      string KwJVJeSJzM;
      string PIxjhMWhAf;
      string ktVbStMIbY;
      string FaoRMPiGNl;
      string ibCUYsFtDW;
      string LReNKPZhCP;
      string SKhaGnSeWS;
      string dPTNxIrADY;
      string oREEMnwbHx;
      string oBDyTXtaNj;
      string aZXkswxQPB;
      string XYddZAGcOS;
      string rpXZdbLVsY;
      if(PIJyJtNkfp == FaoRMPiGNl){OQmTyOtTLQ = true;}
      else if(FaoRMPiGNl == PIJyJtNkfp){FJzhkqqiLa = true;}
      if(hFwcTHzZqH == ibCUYsFtDW){peLFYPWZYT = true;}
      else if(ibCUYsFtDW == hFwcTHzZqH){wnZzIdAThi = true;}
      if(WNVHQUqKGs == LReNKPZhCP){RRMtqjBxGQ = true;}
      else if(LReNKPZhCP == WNVHQUqKGs){jKjbOiedPG = true;}
      if(GzGRiXxCPU == SKhaGnSeWS){jbWqmGlKeK = true;}
      else if(SKhaGnSeWS == GzGRiXxCPU){FdyEXujOHU = true;}
      if(xqtMHEFiNW == dPTNxIrADY){FlQxbNdRAO = true;}
      else if(dPTNxIrADY == xqtMHEFiNW){GukJtOShIT = true;}
      if(LscXRClCgn == oREEMnwbHx){ElwZGwDrcN = true;}
      else if(oREEMnwbHx == LscXRClCgn){HFnhdtZXSB = true;}
      if(CCdljizesu == oBDyTXtaNj){NxMtgOHUSS = true;}
      else if(oBDyTXtaNj == CCdljizesu){MNSFUSpVaM = true;}
      if(KwJVJeSJzM == aZXkswxQPB){cMtNOfAPRc = true;}
      if(PIxjhMWhAf == XYddZAGcOS){FiwrMyexkp = true;}
      if(ktVbStMIbY == rpXZdbLVsY){DsgQxIZWQN = true;}
      while(aZXkswxQPB == KwJVJeSJzM){slMNbnYZhA = true;}
      while(XYddZAGcOS == XYddZAGcOS){PxUwyzoPac = true;}
      while(rpXZdbLVsY == rpXZdbLVsY){VMuFIscfnb = true;}
      if(OQmTyOtTLQ == true){OQmTyOtTLQ = false;}
      if(peLFYPWZYT == true){peLFYPWZYT = false;}
      if(RRMtqjBxGQ == true){RRMtqjBxGQ = false;}
      if(jbWqmGlKeK == true){jbWqmGlKeK = false;}
      if(FlQxbNdRAO == true){FlQxbNdRAO = false;}
      if(ElwZGwDrcN == true){ElwZGwDrcN = false;}
      if(NxMtgOHUSS == true){NxMtgOHUSS = false;}
      if(cMtNOfAPRc == true){cMtNOfAPRc = false;}
      if(FiwrMyexkp == true){FiwrMyexkp = false;}
      if(DsgQxIZWQN == true){DsgQxIZWQN = false;}
      if(FJzhkqqiLa == true){FJzhkqqiLa = false;}
      if(wnZzIdAThi == true){wnZzIdAThi = false;}
      if(jKjbOiedPG == true){jKjbOiedPG = false;}
      if(FdyEXujOHU == true){FdyEXujOHU = false;}
      if(GukJtOShIT == true){GukJtOShIT = false;}
      if(HFnhdtZXSB == true){HFnhdtZXSB = false;}
      if(MNSFUSpVaM == true){MNSFUSpVaM = false;}
      if(slMNbnYZhA == true){slMNbnYZhA = false;}
      if(PxUwyzoPac == true){PxUwyzoPac = false;}
      if(VMuFIscfnb == true){VMuFIscfnb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAWRIPTZMO
{ 
  void DXlINREhIl()
  { 
      bool eZKYYeaqZh = false;
      bool eTOaaJnTqV = false;
      bool OQATFIMoAk = false;
      bool AzzLayKDWE = false;
      bool YlufSjrqUs = false;
      bool SbiESOYpSQ = false;
      bool SkqnheUCzb = false;
      bool zkxlxbVTBU = false;
      bool QUTHSXQtsM = false;
      bool YTjGkmtGyn = false;
      bool PorsshexGp = false;
      bool rFoxzyQjVJ = false;
      bool OZJmCeBpAK = false;
      bool gOVMFbcaNj = false;
      bool sSmCTTdlGl = false;
      bool VKkoYpeEqO = false;
      bool gnwwJdibrX = false;
      bool VpWkPulHSh = false;
      bool BOiNnWcgnO = false;
      bool wXjzDFWqsp = false;
      string uVVOqyBIbt;
      string wXORChuLBB;
      string jaYlMXaUWh;
      string cYZPJncAJs;
      string TeYAIdMjRQ;
      string XdKDlTxiCS;
      string WfltQWyyIN;
      string FuCHhECXdh;
      string LqDGJzOWcp;
      string qsxpVmrdjl;
      string fNaEKcbCVg;
      string QZFUHfcfjQ;
      string HaUSWLxLlt;
      string LXnqCxPyug;
      string XLBuYQmcio;
      string JMtSdEsIgz;
      string eQQaVrlNRJ;
      string PdkCsuZYsG;
      string XUbwjzdUNx;
      string EHRuCHuZZg;
      if(uVVOqyBIbt == fNaEKcbCVg){eZKYYeaqZh = true;}
      else if(fNaEKcbCVg == uVVOqyBIbt){PorsshexGp = true;}
      if(wXORChuLBB == QZFUHfcfjQ){eTOaaJnTqV = true;}
      else if(QZFUHfcfjQ == wXORChuLBB){rFoxzyQjVJ = true;}
      if(jaYlMXaUWh == HaUSWLxLlt){OQATFIMoAk = true;}
      else if(HaUSWLxLlt == jaYlMXaUWh){OZJmCeBpAK = true;}
      if(cYZPJncAJs == LXnqCxPyug){AzzLayKDWE = true;}
      else if(LXnqCxPyug == cYZPJncAJs){gOVMFbcaNj = true;}
      if(TeYAIdMjRQ == XLBuYQmcio){YlufSjrqUs = true;}
      else if(XLBuYQmcio == TeYAIdMjRQ){sSmCTTdlGl = true;}
      if(XdKDlTxiCS == JMtSdEsIgz){SbiESOYpSQ = true;}
      else if(JMtSdEsIgz == XdKDlTxiCS){VKkoYpeEqO = true;}
      if(WfltQWyyIN == eQQaVrlNRJ){SkqnheUCzb = true;}
      else if(eQQaVrlNRJ == WfltQWyyIN){gnwwJdibrX = true;}
      if(FuCHhECXdh == PdkCsuZYsG){zkxlxbVTBU = true;}
      if(LqDGJzOWcp == XUbwjzdUNx){QUTHSXQtsM = true;}
      if(qsxpVmrdjl == EHRuCHuZZg){YTjGkmtGyn = true;}
      while(PdkCsuZYsG == FuCHhECXdh){VpWkPulHSh = true;}
      while(XUbwjzdUNx == XUbwjzdUNx){BOiNnWcgnO = true;}
      while(EHRuCHuZZg == EHRuCHuZZg){wXjzDFWqsp = true;}
      if(eZKYYeaqZh == true){eZKYYeaqZh = false;}
      if(eTOaaJnTqV == true){eTOaaJnTqV = false;}
      if(OQATFIMoAk == true){OQATFIMoAk = false;}
      if(AzzLayKDWE == true){AzzLayKDWE = false;}
      if(YlufSjrqUs == true){YlufSjrqUs = false;}
      if(SbiESOYpSQ == true){SbiESOYpSQ = false;}
      if(SkqnheUCzb == true){SkqnheUCzb = false;}
      if(zkxlxbVTBU == true){zkxlxbVTBU = false;}
      if(QUTHSXQtsM == true){QUTHSXQtsM = false;}
      if(YTjGkmtGyn == true){YTjGkmtGyn = false;}
      if(PorsshexGp == true){PorsshexGp = false;}
      if(rFoxzyQjVJ == true){rFoxzyQjVJ = false;}
      if(OZJmCeBpAK == true){OZJmCeBpAK = false;}
      if(gOVMFbcaNj == true){gOVMFbcaNj = false;}
      if(sSmCTTdlGl == true){sSmCTTdlGl = false;}
      if(VKkoYpeEqO == true){VKkoYpeEqO = false;}
      if(gnwwJdibrX == true){gnwwJdibrX = false;}
      if(VpWkPulHSh == true){VpWkPulHSh = false;}
      if(BOiNnWcgnO == true){BOiNnWcgnO = false;}
      if(wXjzDFWqsp == true){wXjzDFWqsp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJBFATOHWL
{ 
  void creXBWohjg()
  { 
      bool PVJIjoBwTM = false;
      bool nyHejaIONe = false;
      bool HJLrkVJeFr = false;
      bool mbyydCBFfh = false;
      bool NMVsSLaeiN = false;
      bool aFSlzGKRWN = false;
      bool eVpbZMAJAh = false;
      bool YCifRtnSZZ = false;
      bool udwrQgJMzX = false;
      bool rjiRCqWsTG = false;
      bool LReBnYWlTE = false;
      bool SqqxSAZyKr = false;
      bool DmJcooTQca = false;
      bool XtyTNdzuDr = false;
      bool JWrtFBrkzC = false;
      bool QXhaCXHCLy = false;
      bool EGIsgXrXio = false;
      bool AetSifuPWn = false;
      bool xhRaJzLXQp = false;
      bool VxiEmDNzMg = false;
      string EbVikhPqZM;
      string PAQgDUVAbT;
      string rbbaFBszPW;
      string fUqUQyanIe;
      string bCPLXfmHkQ;
      string nhhIzcAuci;
      string nQaDftIwQF;
      string sgrwqpLPCZ;
      string OlNzhxliUn;
      string xfLYpLaLec;
      string WppfWHpkQJ;
      string QjrCUBCaVi;
      string IZbcHNUSFf;
      string OzkZDYwhca;
      string GARLWNnJEo;
      string JzpwTwONXJ;
      string lWfktQyRzu;
      string FTytbHIPFs;
      string YLOQWOJoFG;
      string KiJSnjUgRG;
      if(EbVikhPqZM == WppfWHpkQJ){PVJIjoBwTM = true;}
      else if(WppfWHpkQJ == EbVikhPqZM){LReBnYWlTE = true;}
      if(PAQgDUVAbT == QjrCUBCaVi){nyHejaIONe = true;}
      else if(QjrCUBCaVi == PAQgDUVAbT){SqqxSAZyKr = true;}
      if(rbbaFBszPW == IZbcHNUSFf){HJLrkVJeFr = true;}
      else if(IZbcHNUSFf == rbbaFBszPW){DmJcooTQca = true;}
      if(fUqUQyanIe == OzkZDYwhca){mbyydCBFfh = true;}
      else if(OzkZDYwhca == fUqUQyanIe){XtyTNdzuDr = true;}
      if(bCPLXfmHkQ == GARLWNnJEo){NMVsSLaeiN = true;}
      else if(GARLWNnJEo == bCPLXfmHkQ){JWrtFBrkzC = true;}
      if(nhhIzcAuci == JzpwTwONXJ){aFSlzGKRWN = true;}
      else if(JzpwTwONXJ == nhhIzcAuci){QXhaCXHCLy = true;}
      if(nQaDftIwQF == lWfktQyRzu){eVpbZMAJAh = true;}
      else if(lWfktQyRzu == nQaDftIwQF){EGIsgXrXio = true;}
      if(sgrwqpLPCZ == FTytbHIPFs){YCifRtnSZZ = true;}
      if(OlNzhxliUn == YLOQWOJoFG){udwrQgJMzX = true;}
      if(xfLYpLaLec == KiJSnjUgRG){rjiRCqWsTG = true;}
      while(FTytbHIPFs == sgrwqpLPCZ){AetSifuPWn = true;}
      while(YLOQWOJoFG == YLOQWOJoFG){xhRaJzLXQp = true;}
      while(KiJSnjUgRG == KiJSnjUgRG){VxiEmDNzMg = true;}
      if(PVJIjoBwTM == true){PVJIjoBwTM = false;}
      if(nyHejaIONe == true){nyHejaIONe = false;}
      if(HJLrkVJeFr == true){HJLrkVJeFr = false;}
      if(mbyydCBFfh == true){mbyydCBFfh = false;}
      if(NMVsSLaeiN == true){NMVsSLaeiN = false;}
      if(aFSlzGKRWN == true){aFSlzGKRWN = false;}
      if(eVpbZMAJAh == true){eVpbZMAJAh = false;}
      if(YCifRtnSZZ == true){YCifRtnSZZ = false;}
      if(udwrQgJMzX == true){udwrQgJMzX = false;}
      if(rjiRCqWsTG == true){rjiRCqWsTG = false;}
      if(LReBnYWlTE == true){LReBnYWlTE = false;}
      if(SqqxSAZyKr == true){SqqxSAZyKr = false;}
      if(DmJcooTQca == true){DmJcooTQca = false;}
      if(XtyTNdzuDr == true){XtyTNdzuDr = false;}
      if(JWrtFBrkzC == true){JWrtFBrkzC = false;}
      if(QXhaCXHCLy == true){QXhaCXHCLy = false;}
      if(EGIsgXrXio == true){EGIsgXrXio = false;}
      if(AetSifuPWn == true){AetSifuPWn = false;}
      if(xhRaJzLXQp == true){xhRaJzLXQp = false;}
      if(VxiEmDNzMg == true){VxiEmDNzMg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APFUDMDJPD
{ 
  void KCWNzmzLkq()
  { 
      bool eMkfYTSEim = false;
      bool oKCrQAawjM = false;
      bool ojVncDPTlj = false;
      bool iXGDixduit = false;
      bool PaIkkPjGFM = false;
      bool sCKQCupwDV = false;
      bool EzSzEQDzJT = false;
      bool WfMpxOakDM = false;
      bool SIOYpgNpBm = false;
      bool GgrMoQIIgT = false;
      bool MkxkoNoTSn = false;
      bool TEspCwjsJW = false;
      bool DMxWMonzAg = false;
      bool FSEiAgKcjc = false;
      bool qsXMSBnBKs = false;
      bool fPzJPzmaYA = false;
      bool ZoTlhBAJpV = false;
      bool kHJfeKojDK = false;
      bool BloHApStSA = false;
      bool sjDjDCZleQ = false;
      string AdHYzyzWjc;
      string nlFMFuMZeI;
      string JgYTXAbwtz;
      string QXkjlTizHO;
      string HWQcVUZiNF;
      string qfswYTEmBz;
      string VDbjMPAUak;
      string MMSQBlPwyD;
      string ZshoHjenLR;
      string PuyHrDufPF;
      string TEHbreNcul;
      string EHnyYbUlcb;
      string jLJJVROKXx;
      string qifsiVlFxc;
      string WCsYNHHziP;
      string iIDnUIuyGa;
      string PCEyuUbtOD;
      string pOozEgSjuO;
      string JOaINherXa;
      string ZmzVNUytcr;
      if(AdHYzyzWjc == TEHbreNcul){eMkfYTSEim = true;}
      else if(TEHbreNcul == AdHYzyzWjc){MkxkoNoTSn = true;}
      if(nlFMFuMZeI == EHnyYbUlcb){oKCrQAawjM = true;}
      else if(EHnyYbUlcb == nlFMFuMZeI){TEspCwjsJW = true;}
      if(JgYTXAbwtz == jLJJVROKXx){ojVncDPTlj = true;}
      else if(jLJJVROKXx == JgYTXAbwtz){DMxWMonzAg = true;}
      if(QXkjlTizHO == qifsiVlFxc){iXGDixduit = true;}
      else if(qifsiVlFxc == QXkjlTizHO){FSEiAgKcjc = true;}
      if(HWQcVUZiNF == WCsYNHHziP){PaIkkPjGFM = true;}
      else if(WCsYNHHziP == HWQcVUZiNF){qsXMSBnBKs = true;}
      if(qfswYTEmBz == iIDnUIuyGa){sCKQCupwDV = true;}
      else if(iIDnUIuyGa == qfswYTEmBz){fPzJPzmaYA = true;}
      if(VDbjMPAUak == PCEyuUbtOD){EzSzEQDzJT = true;}
      else if(PCEyuUbtOD == VDbjMPAUak){ZoTlhBAJpV = true;}
      if(MMSQBlPwyD == pOozEgSjuO){WfMpxOakDM = true;}
      if(ZshoHjenLR == JOaINherXa){SIOYpgNpBm = true;}
      if(PuyHrDufPF == ZmzVNUytcr){GgrMoQIIgT = true;}
      while(pOozEgSjuO == MMSQBlPwyD){kHJfeKojDK = true;}
      while(JOaINherXa == JOaINherXa){BloHApStSA = true;}
      while(ZmzVNUytcr == ZmzVNUytcr){sjDjDCZleQ = true;}
      if(eMkfYTSEim == true){eMkfYTSEim = false;}
      if(oKCrQAawjM == true){oKCrQAawjM = false;}
      if(ojVncDPTlj == true){ojVncDPTlj = false;}
      if(iXGDixduit == true){iXGDixduit = false;}
      if(PaIkkPjGFM == true){PaIkkPjGFM = false;}
      if(sCKQCupwDV == true){sCKQCupwDV = false;}
      if(EzSzEQDzJT == true){EzSzEQDzJT = false;}
      if(WfMpxOakDM == true){WfMpxOakDM = false;}
      if(SIOYpgNpBm == true){SIOYpgNpBm = false;}
      if(GgrMoQIIgT == true){GgrMoQIIgT = false;}
      if(MkxkoNoTSn == true){MkxkoNoTSn = false;}
      if(TEspCwjsJW == true){TEspCwjsJW = false;}
      if(DMxWMonzAg == true){DMxWMonzAg = false;}
      if(FSEiAgKcjc == true){FSEiAgKcjc = false;}
      if(qsXMSBnBKs == true){qsXMSBnBKs = false;}
      if(fPzJPzmaYA == true){fPzJPzmaYA = false;}
      if(ZoTlhBAJpV == true){ZoTlhBAJpV = false;}
      if(kHJfeKojDK == true){kHJfeKojDK = false;}
      if(BloHApStSA == true){BloHApStSA = false;}
      if(sjDjDCZleQ == true){sjDjDCZleQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIOGWUDDMI
{ 
  void ZBmGVUpqih()
  { 
      bool wzEMsbkJZM = false;
      bool KfGMiWFPVL = false;
      bool ToyYpnrHeQ = false;
      bool jbNAxBVJPe = false;
      bool zMEcEOnghP = false;
      bool pTDJUGBfWF = false;
      bool icdJchRFPg = false;
      bool BwAqMHkUTb = false;
      bool zLZPZQYDep = false;
      bool ApmJuVhtAW = false;
      bool wiRANtTLxN = false;
      bool VfLtGXDOjL = false;
      bool JNZYgLIpup = false;
      bool ZpUxeQsYBe = false;
      bool xMFRTTdrDW = false;
      bool SSKnMhJrTC = false;
      bool kcPGnfKNPp = false;
      bool ddMEOwHHEM = false;
      bool gQmXXGegkx = false;
      bool HAFztTwzdn = false;
      string YkaaiGtsBa;
      string LjEbmdsYZc;
      string YJMiSLVqpx;
      string XQbojapQNl;
      string EphYDZiKbN;
      string tFxYbPYqIW;
      string jCDECtIPqL;
      string ncKmXiamfs;
      string cKPbCSSDMU;
      string ByIqBClcVI;
      string RSTPZRuKAs;
      string nkKPtZmaCj;
      string bFDWJoTSkV;
      string wxQWaJqACj;
      string XIDSfQnsxb;
      string OKalgMPwFj;
      string ybYdxpTnnj;
      string hmYRMTBjps;
      string BaVJHkVepO;
      string tttRluiZVo;
      if(YkaaiGtsBa == RSTPZRuKAs){wzEMsbkJZM = true;}
      else if(RSTPZRuKAs == YkaaiGtsBa){wiRANtTLxN = true;}
      if(LjEbmdsYZc == nkKPtZmaCj){KfGMiWFPVL = true;}
      else if(nkKPtZmaCj == LjEbmdsYZc){VfLtGXDOjL = true;}
      if(YJMiSLVqpx == bFDWJoTSkV){ToyYpnrHeQ = true;}
      else if(bFDWJoTSkV == YJMiSLVqpx){JNZYgLIpup = true;}
      if(XQbojapQNl == wxQWaJqACj){jbNAxBVJPe = true;}
      else if(wxQWaJqACj == XQbojapQNl){ZpUxeQsYBe = true;}
      if(EphYDZiKbN == XIDSfQnsxb){zMEcEOnghP = true;}
      else if(XIDSfQnsxb == EphYDZiKbN){xMFRTTdrDW = true;}
      if(tFxYbPYqIW == OKalgMPwFj){pTDJUGBfWF = true;}
      else if(OKalgMPwFj == tFxYbPYqIW){SSKnMhJrTC = true;}
      if(jCDECtIPqL == ybYdxpTnnj){icdJchRFPg = true;}
      else if(ybYdxpTnnj == jCDECtIPqL){kcPGnfKNPp = true;}
      if(ncKmXiamfs == hmYRMTBjps){BwAqMHkUTb = true;}
      if(cKPbCSSDMU == BaVJHkVepO){zLZPZQYDep = true;}
      if(ByIqBClcVI == tttRluiZVo){ApmJuVhtAW = true;}
      while(hmYRMTBjps == ncKmXiamfs){ddMEOwHHEM = true;}
      while(BaVJHkVepO == BaVJHkVepO){gQmXXGegkx = true;}
      while(tttRluiZVo == tttRluiZVo){HAFztTwzdn = true;}
      if(wzEMsbkJZM == true){wzEMsbkJZM = false;}
      if(KfGMiWFPVL == true){KfGMiWFPVL = false;}
      if(ToyYpnrHeQ == true){ToyYpnrHeQ = false;}
      if(jbNAxBVJPe == true){jbNAxBVJPe = false;}
      if(zMEcEOnghP == true){zMEcEOnghP = false;}
      if(pTDJUGBfWF == true){pTDJUGBfWF = false;}
      if(icdJchRFPg == true){icdJchRFPg = false;}
      if(BwAqMHkUTb == true){BwAqMHkUTb = false;}
      if(zLZPZQYDep == true){zLZPZQYDep = false;}
      if(ApmJuVhtAW == true){ApmJuVhtAW = false;}
      if(wiRANtTLxN == true){wiRANtTLxN = false;}
      if(VfLtGXDOjL == true){VfLtGXDOjL = false;}
      if(JNZYgLIpup == true){JNZYgLIpup = false;}
      if(ZpUxeQsYBe == true){ZpUxeQsYBe = false;}
      if(xMFRTTdrDW == true){xMFRTTdrDW = false;}
      if(SSKnMhJrTC == true){SSKnMhJrTC = false;}
      if(kcPGnfKNPp == true){kcPGnfKNPp = false;}
      if(ddMEOwHHEM == true){ddMEOwHHEM = false;}
      if(gQmXXGegkx == true){gQmXXGegkx = false;}
      if(HAFztTwzdn == true){HAFztTwzdn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBIIRTJHRV
{ 
  void OaZtNztpKr()
  { 
      bool YsMTgINMpw = false;
      bool FEiGSCmQWy = false;
      bool UgnNyzQogL = false;
      bool MEnBzhkDLt = false;
      bool YLWyHwTJep = false;
      bool WZBtPrEyUh = false;
      bool rYeejAPgGj = false;
      bool QjEbYJJpGC = false;
      bool eGJpolDskG = false;
      bool cmhdCAfrNG = false;
      bool gmDtZmUYVG = false;
      bool iOrSClOooy = false;
      bool xVuAHdBaZY = false;
      bool cQbzUrDPQB = false;
      bool QdXeWOuPaQ = false;
      bool lqCPJLqCmw = false;
      bool ktzxdSlryK = false;
      bool hyXmgSxQcr = false;
      bool hlAJlkNLpI = false;
      bool BAcUQWeaBE = false;
      string hiSzUgVLMc;
      string qoBzTwscbV;
      string IPloQwwZuO;
      string TDtnAkkuer;
      string MsBKpHLlGH;
      string jyTclRwchX;
      string juPxJmtNzh;
      string LyyiJOOayJ;
      string kKTmeUjRBh;
      string oHMGIQcEBD;
      string MylXwlAjSW;
      string DUeYmZbcSo;
      string DcLQsDlqar;
      string lJZuxmXupr;
      string TzzddTcnTh;
      string ozlLAilUes;
      string AJIZkstjbz;
      string BglZVDdhlY;
      string axWrDlXNuN;
      string ACPxrJpYsk;
      if(hiSzUgVLMc == MylXwlAjSW){YsMTgINMpw = true;}
      else if(MylXwlAjSW == hiSzUgVLMc){gmDtZmUYVG = true;}
      if(qoBzTwscbV == DUeYmZbcSo){FEiGSCmQWy = true;}
      else if(DUeYmZbcSo == qoBzTwscbV){iOrSClOooy = true;}
      if(IPloQwwZuO == DcLQsDlqar){UgnNyzQogL = true;}
      else if(DcLQsDlqar == IPloQwwZuO){xVuAHdBaZY = true;}
      if(TDtnAkkuer == lJZuxmXupr){MEnBzhkDLt = true;}
      else if(lJZuxmXupr == TDtnAkkuer){cQbzUrDPQB = true;}
      if(MsBKpHLlGH == TzzddTcnTh){YLWyHwTJep = true;}
      else if(TzzddTcnTh == MsBKpHLlGH){QdXeWOuPaQ = true;}
      if(jyTclRwchX == ozlLAilUes){WZBtPrEyUh = true;}
      else if(ozlLAilUes == jyTclRwchX){lqCPJLqCmw = true;}
      if(juPxJmtNzh == AJIZkstjbz){rYeejAPgGj = true;}
      else if(AJIZkstjbz == juPxJmtNzh){ktzxdSlryK = true;}
      if(LyyiJOOayJ == BglZVDdhlY){QjEbYJJpGC = true;}
      if(kKTmeUjRBh == axWrDlXNuN){eGJpolDskG = true;}
      if(oHMGIQcEBD == ACPxrJpYsk){cmhdCAfrNG = true;}
      while(BglZVDdhlY == LyyiJOOayJ){hyXmgSxQcr = true;}
      while(axWrDlXNuN == axWrDlXNuN){hlAJlkNLpI = true;}
      while(ACPxrJpYsk == ACPxrJpYsk){BAcUQWeaBE = true;}
      if(YsMTgINMpw == true){YsMTgINMpw = false;}
      if(FEiGSCmQWy == true){FEiGSCmQWy = false;}
      if(UgnNyzQogL == true){UgnNyzQogL = false;}
      if(MEnBzhkDLt == true){MEnBzhkDLt = false;}
      if(YLWyHwTJep == true){YLWyHwTJep = false;}
      if(WZBtPrEyUh == true){WZBtPrEyUh = false;}
      if(rYeejAPgGj == true){rYeejAPgGj = false;}
      if(QjEbYJJpGC == true){QjEbYJJpGC = false;}
      if(eGJpolDskG == true){eGJpolDskG = false;}
      if(cmhdCAfrNG == true){cmhdCAfrNG = false;}
      if(gmDtZmUYVG == true){gmDtZmUYVG = false;}
      if(iOrSClOooy == true){iOrSClOooy = false;}
      if(xVuAHdBaZY == true){xVuAHdBaZY = false;}
      if(cQbzUrDPQB == true){cQbzUrDPQB = false;}
      if(QdXeWOuPaQ == true){QdXeWOuPaQ = false;}
      if(lqCPJLqCmw == true){lqCPJLqCmw = false;}
      if(ktzxdSlryK == true){ktzxdSlryK = false;}
      if(hyXmgSxQcr == true){hyXmgSxQcr = false;}
      if(hlAJlkNLpI == true){hlAJlkNLpI = false;}
      if(BAcUQWeaBE == true){BAcUQWeaBE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UFLXUQRLNM
{ 
  void yoUESFRFMe()
  { 
      bool wzAVsDUlhc = false;
      bool MNtMqFnMwP = false;
      bool FklOYpsglV = false;
      bool OSczoEpHlj = false;
      bool rCRznNArUK = false;
      bool BAZpHKNlwC = false;
      bool JnALOskuXm = false;
      bool OfZMWDSlZK = false;
      bool oALaUOrlre = false;
      bool qELjZEBGku = false;
      bool cFUgwVZNTE = false;
      bool raLkMIbYqz = false;
      bool AyCswKUplR = false;
      bool BMAehifeey = false;
      bool neRnmPrZWR = false;
      bool ccOltdDbkk = false;
      bool AjaBCeagDc = false;
      bool bxsrLVfNGg = false;
      bool StSUoXxOkD = false;
      bool fEstyDEPkH = false;
      string UxdwSbtckZ;
      string mcbjhQqGWb;
      string POJGcFGUKH;
      string jtAYkBkCJp;
      string fdhChaRayq;
      string rMjUnFmXTN;
      string UZRdprbCzg;
      string eowgulgHYB;
      string meVSOWJfke;
      string NNhwVGLDMo;
      string yObRMCQDYC;
      string XfzSZpDyOS;
      string iwRTSRGzLo;
      string ZdtjDYDEGM;
      string GFGhHhOPWe;
      string CMotGCxHyt;
      string wQribtkPOB;
      string lzrCLcpiMk;
      string DqcfmMoAcA;
      string buFLPoNWGM;
      if(UxdwSbtckZ == yObRMCQDYC){wzAVsDUlhc = true;}
      else if(yObRMCQDYC == UxdwSbtckZ){cFUgwVZNTE = true;}
      if(mcbjhQqGWb == XfzSZpDyOS){MNtMqFnMwP = true;}
      else if(XfzSZpDyOS == mcbjhQqGWb){raLkMIbYqz = true;}
      if(POJGcFGUKH == iwRTSRGzLo){FklOYpsglV = true;}
      else if(iwRTSRGzLo == POJGcFGUKH){AyCswKUplR = true;}
      if(jtAYkBkCJp == ZdtjDYDEGM){OSczoEpHlj = true;}
      else if(ZdtjDYDEGM == jtAYkBkCJp){BMAehifeey = true;}
      if(fdhChaRayq == GFGhHhOPWe){rCRznNArUK = true;}
      else if(GFGhHhOPWe == fdhChaRayq){neRnmPrZWR = true;}
      if(rMjUnFmXTN == CMotGCxHyt){BAZpHKNlwC = true;}
      else if(CMotGCxHyt == rMjUnFmXTN){ccOltdDbkk = true;}
      if(UZRdprbCzg == wQribtkPOB){JnALOskuXm = true;}
      else if(wQribtkPOB == UZRdprbCzg){AjaBCeagDc = true;}
      if(eowgulgHYB == lzrCLcpiMk){OfZMWDSlZK = true;}
      if(meVSOWJfke == DqcfmMoAcA){oALaUOrlre = true;}
      if(NNhwVGLDMo == buFLPoNWGM){qELjZEBGku = true;}
      while(lzrCLcpiMk == eowgulgHYB){bxsrLVfNGg = true;}
      while(DqcfmMoAcA == DqcfmMoAcA){StSUoXxOkD = true;}
      while(buFLPoNWGM == buFLPoNWGM){fEstyDEPkH = true;}
      if(wzAVsDUlhc == true){wzAVsDUlhc = false;}
      if(MNtMqFnMwP == true){MNtMqFnMwP = false;}
      if(FklOYpsglV == true){FklOYpsglV = false;}
      if(OSczoEpHlj == true){OSczoEpHlj = false;}
      if(rCRznNArUK == true){rCRznNArUK = false;}
      if(BAZpHKNlwC == true){BAZpHKNlwC = false;}
      if(JnALOskuXm == true){JnALOskuXm = false;}
      if(OfZMWDSlZK == true){OfZMWDSlZK = false;}
      if(oALaUOrlre == true){oALaUOrlre = false;}
      if(qELjZEBGku == true){qELjZEBGku = false;}
      if(cFUgwVZNTE == true){cFUgwVZNTE = false;}
      if(raLkMIbYqz == true){raLkMIbYqz = false;}
      if(AyCswKUplR == true){AyCswKUplR = false;}
      if(BMAehifeey == true){BMAehifeey = false;}
      if(neRnmPrZWR == true){neRnmPrZWR = false;}
      if(ccOltdDbkk == true){ccOltdDbkk = false;}
      if(AjaBCeagDc == true){AjaBCeagDc = false;}
      if(bxsrLVfNGg == true){bxsrLVfNGg = false;}
      if(StSUoXxOkD == true){StSUoXxOkD = false;}
      if(fEstyDEPkH == true){fEstyDEPkH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOGKFBKJXG
{ 
  void jUfPJcChVR()
  { 
      bool UlBcRiShsT = false;
      bool zVYCQkuyQQ = false;
      bool gjjMdegfmH = false;
      bool MrlhDkOhaT = false;
      bool CqiUpKGLpS = false;
      bool xQHKakCnzl = false;
      bool CmulGHjpye = false;
      bool WMWxNpAOWS = false;
      bool XUpUJwjaGR = false;
      bool iZhoQPwxNi = false;
      bool aQMKujsKxk = false;
      bool jmRgNgwZbK = false;
      bool XJiguwehfx = false;
      bool tDAmrHIeYZ = false;
      bool DYcVgwHBaj = false;
      bool TVUDKQgfPy = false;
      bool FKdApgmdnG = false;
      bool YRBCHygMzz = false;
      bool ocHwdYhxca = false;
      bool ZbPZTrtceA = false;
      string fHTEztclGd;
      string lyOVhrukLR;
      string DIKwLtUXmj;
      string ZjsIsLqIVI;
      string UlpwgeRACW;
      string IUPyeXwXrF;
      string ZFyWDCEFcV;
      string BlPDwQROOg;
      string cTVQaETtcU;
      string PSQPhOnTrd;
      string ZLXfVWFMBO;
      string FhIKbGjhuz;
      string iJbHFhVzUh;
      string byVjHQuotE;
      string zGrOPgKFnb;
      string eGYsuQjQan;
      string BGqTlGMYDK;
      string KumpAbQNqX;
      string WPKsDVYbop;
      string geNGDrOYbI;
      if(fHTEztclGd == ZLXfVWFMBO){UlBcRiShsT = true;}
      else if(ZLXfVWFMBO == fHTEztclGd){aQMKujsKxk = true;}
      if(lyOVhrukLR == FhIKbGjhuz){zVYCQkuyQQ = true;}
      else if(FhIKbGjhuz == lyOVhrukLR){jmRgNgwZbK = true;}
      if(DIKwLtUXmj == iJbHFhVzUh){gjjMdegfmH = true;}
      else if(iJbHFhVzUh == DIKwLtUXmj){XJiguwehfx = true;}
      if(ZjsIsLqIVI == byVjHQuotE){MrlhDkOhaT = true;}
      else if(byVjHQuotE == ZjsIsLqIVI){tDAmrHIeYZ = true;}
      if(UlpwgeRACW == zGrOPgKFnb){CqiUpKGLpS = true;}
      else if(zGrOPgKFnb == UlpwgeRACW){DYcVgwHBaj = true;}
      if(IUPyeXwXrF == eGYsuQjQan){xQHKakCnzl = true;}
      else if(eGYsuQjQan == IUPyeXwXrF){TVUDKQgfPy = true;}
      if(ZFyWDCEFcV == BGqTlGMYDK){CmulGHjpye = true;}
      else if(BGqTlGMYDK == ZFyWDCEFcV){FKdApgmdnG = true;}
      if(BlPDwQROOg == KumpAbQNqX){WMWxNpAOWS = true;}
      if(cTVQaETtcU == WPKsDVYbop){XUpUJwjaGR = true;}
      if(PSQPhOnTrd == geNGDrOYbI){iZhoQPwxNi = true;}
      while(KumpAbQNqX == BlPDwQROOg){YRBCHygMzz = true;}
      while(WPKsDVYbop == WPKsDVYbop){ocHwdYhxca = true;}
      while(geNGDrOYbI == geNGDrOYbI){ZbPZTrtceA = true;}
      if(UlBcRiShsT == true){UlBcRiShsT = false;}
      if(zVYCQkuyQQ == true){zVYCQkuyQQ = false;}
      if(gjjMdegfmH == true){gjjMdegfmH = false;}
      if(MrlhDkOhaT == true){MrlhDkOhaT = false;}
      if(CqiUpKGLpS == true){CqiUpKGLpS = false;}
      if(xQHKakCnzl == true){xQHKakCnzl = false;}
      if(CmulGHjpye == true){CmulGHjpye = false;}
      if(WMWxNpAOWS == true){WMWxNpAOWS = false;}
      if(XUpUJwjaGR == true){XUpUJwjaGR = false;}
      if(iZhoQPwxNi == true){iZhoQPwxNi = false;}
      if(aQMKujsKxk == true){aQMKujsKxk = false;}
      if(jmRgNgwZbK == true){jmRgNgwZbK = false;}
      if(XJiguwehfx == true){XJiguwehfx = false;}
      if(tDAmrHIeYZ == true){tDAmrHIeYZ = false;}
      if(DYcVgwHBaj == true){DYcVgwHBaj = false;}
      if(TVUDKQgfPy == true){TVUDKQgfPy = false;}
      if(FKdApgmdnG == true){FKdApgmdnG = false;}
      if(YRBCHygMzz == true){YRBCHygMzz = false;}
      if(ocHwdYhxca == true){ocHwdYhxca = false;}
      if(ZbPZTrtceA == true){ZbPZTrtceA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRBLAROZLX
{ 
  void oAfuzdQNQB()
  { 
      bool ElNcJwrlik = false;
      bool ilaILpVEzi = false;
      bool KkHNnrXjnP = false;
      bool QYmsZUcNbG = false;
      bool mtcqYBeWGM = false;
      bool gWQsgSdzoQ = false;
      bool XHyTTJyhhp = false;
      bool MHcsuPIQol = false;
      bool NBcaitHsLG = false;
      bool qcYKhewJWO = false;
      bool DwnQzYsXxQ = false;
      bool KNKCCWdWjZ = false;
      bool BEVbzihRKQ = false;
      bool TztZiRMMbJ = false;
      bool BjwuudSWHK = false;
      bool AYYwMyaLQP = false;
      bool paNgwLSjTk = false;
      bool JRuZYRIafV = false;
      bool QLKzPuZxNk = false;
      bool pBuLTZWPyj = false;
      string DDWkwBGAeI;
      string JZQLUkKzDt;
      string WlroWklAZL;
      string AzufDZtygl;
      string ZLWswKpnOo;
      string TazYBRLhNL;
      string OGZSHJdjHu;
      string qLRQULOzrL;
      string tykkrYAWel;
      string NMkVXTkEkm;
      string fFfTyHJiDo;
      string CLoBQPUoai;
      string JHFUgeawrB;
      string aKOFfnRRlj;
      string PRSpjCWiEH;
      string yucCcXALmT;
      string gMpCNrxjVb;
      string yCDpSroOkd;
      string HqqkCegLbH;
      string nFeSCCaQbq;
      if(DDWkwBGAeI == fFfTyHJiDo){ElNcJwrlik = true;}
      else if(fFfTyHJiDo == DDWkwBGAeI){DwnQzYsXxQ = true;}
      if(JZQLUkKzDt == CLoBQPUoai){ilaILpVEzi = true;}
      else if(CLoBQPUoai == JZQLUkKzDt){KNKCCWdWjZ = true;}
      if(WlroWklAZL == JHFUgeawrB){KkHNnrXjnP = true;}
      else if(JHFUgeawrB == WlroWklAZL){BEVbzihRKQ = true;}
      if(AzufDZtygl == aKOFfnRRlj){QYmsZUcNbG = true;}
      else if(aKOFfnRRlj == AzufDZtygl){TztZiRMMbJ = true;}
      if(ZLWswKpnOo == PRSpjCWiEH){mtcqYBeWGM = true;}
      else if(PRSpjCWiEH == ZLWswKpnOo){BjwuudSWHK = true;}
      if(TazYBRLhNL == yucCcXALmT){gWQsgSdzoQ = true;}
      else if(yucCcXALmT == TazYBRLhNL){AYYwMyaLQP = true;}
      if(OGZSHJdjHu == gMpCNrxjVb){XHyTTJyhhp = true;}
      else if(gMpCNrxjVb == OGZSHJdjHu){paNgwLSjTk = true;}
      if(qLRQULOzrL == yCDpSroOkd){MHcsuPIQol = true;}
      if(tykkrYAWel == HqqkCegLbH){NBcaitHsLG = true;}
      if(NMkVXTkEkm == nFeSCCaQbq){qcYKhewJWO = true;}
      while(yCDpSroOkd == qLRQULOzrL){JRuZYRIafV = true;}
      while(HqqkCegLbH == HqqkCegLbH){QLKzPuZxNk = true;}
      while(nFeSCCaQbq == nFeSCCaQbq){pBuLTZWPyj = true;}
      if(ElNcJwrlik == true){ElNcJwrlik = false;}
      if(ilaILpVEzi == true){ilaILpVEzi = false;}
      if(KkHNnrXjnP == true){KkHNnrXjnP = false;}
      if(QYmsZUcNbG == true){QYmsZUcNbG = false;}
      if(mtcqYBeWGM == true){mtcqYBeWGM = false;}
      if(gWQsgSdzoQ == true){gWQsgSdzoQ = false;}
      if(XHyTTJyhhp == true){XHyTTJyhhp = false;}
      if(MHcsuPIQol == true){MHcsuPIQol = false;}
      if(NBcaitHsLG == true){NBcaitHsLG = false;}
      if(qcYKhewJWO == true){qcYKhewJWO = false;}
      if(DwnQzYsXxQ == true){DwnQzYsXxQ = false;}
      if(KNKCCWdWjZ == true){KNKCCWdWjZ = false;}
      if(BEVbzihRKQ == true){BEVbzihRKQ = false;}
      if(TztZiRMMbJ == true){TztZiRMMbJ = false;}
      if(BjwuudSWHK == true){BjwuudSWHK = false;}
      if(AYYwMyaLQP == true){AYYwMyaLQP = false;}
      if(paNgwLSjTk == true){paNgwLSjTk = false;}
      if(JRuZYRIafV == true){JRuZYRIafV = false;}
      if(QLKzPuZxNk == true){QLKzPuZxNk = false;}
      if(pBuLTZWPyj == true){pBuLTZWPyj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVAFLUBVZS
{ 
  void REnYBnVGYO()
  { 
      bool cuuXPmwXUz = false;
      bool zNoUwuqiXE = false;
      bool cpCwsOJoIa = false;
      bool ISrASKYwKp = false;
      bool RngJBPsccx = false;
      bool UwPAQlrzdB = false;
      bool dHPtpfUnBk = false;
      bool WtYhloJrud = false;
      bool UfMLGLDrjf = false;
      bool RZRJMKYmTU = false;
      bool tFbrZZXhNa = false;
      bool cAEAfxuDne = false;
      bool ccEUSxbPUb = false;
      bool QVYZjPETkf = false;
      bool nUdIDRVRcO = false;
      bool OUzorQAGZc = false;
      bool yIMkKGadPQ = false;
      bool raRHpHyuRA = false;
      bool bJlGMwWjhS = false;
      bool OytIheIsyw = false;
      string ygpdRWtcPL;
      string WtZuuhKKjf;
      string PBCKTldYrT;
      string BCimHDzEmU;
      string nleapMRAaz;
      string iANSWxdfJf;
      string sUjuJULlnr;
      string hGXPrcVaTH;
      string TdyskAnPQK;
      string ZTtHbSCjQU;
      string BfMiQbcyas;
      string aDLCLOWpKJ;
      string fuUcSOMQnY;
      string ZlJzFnRObI;
      string XpoXiVHruM;
      string uLZHoFKiQC;
      string PLKBSosMwW;
      string xHOBloGxtw;
      string GTUadOLCJA;
      string chyYrLfmEs;
      if(ygpdRWtcPL == BfMiQbcyas){cuuXPmwXUz = true;}
      else if(BfMiQbcyas == ygpdRWtcPL){tFbrZZXhNa = true;}
      if(WtZuuhKKjf == aDLCLOWpKJ){zNoUwuqiXE = true;}
      else if(aDLCLOWpKJ == WtZuuhKKjf){cAEAfxuDne = true;}
      if(PBCKTldYrT == fuUcSOMQnY){cpCwsOJoIa = true;}
      else if(fuUcSOMQnY == PBCKTldYrT){ccEUSxbPUb = true;}
      if(BCimHDzEmU == ZlJzFnRObI){ISrASKYwKp = true;}
      else if(ZlJzFnRObI == BCimHDzEmU){QVYZjPETkf = true;}
      if(nleapMRAaz == XpoXiVHruM){RngJBPsccx = true;}
      else if(XpoXiVHruM == nleapMRAaz){nUdIDRVRcO = true;}
      if(iANSWxdfJf == uLZHoFKiQC){UwPAQlrzdB = true;}
      else if(uLZHoFKiQC == iANSWxdfJf){OUzorQAGZc = true;}
      if(sUjuJULlnr == PLKBSosMwW){dHPtpfUnBk = true;}
      else if(PLKBSosMwW == sUjuJULlnr){yIMkKGadPQ = true;}
      if(hGXPrcVaTH == xHOBloGxtw){WtYhloJrud = true;}
      if(TdyskAnPQK == GTUadOLCJA){UfMLGLDrjf = true;}
      if(ZTtHbSCjQU == chyYrLfmEs){RZRJMKYmTU = true;}
      while(xHOBloGxtw == hGXPrcVaTH){raRHpHyuRA = true;}
      while(GTUadOLCJA == GTUadOLCJA){bJlGMwWjhS = true;}
      while(chyYrLfmEs == chyYrLfmEs){OytIheIsyw = true;}
      if(cuuXPmwXUz == true){cuuXPmwXUz = false;}
      if(zNoUwuqiXE == true){zNoUwuqiXE = false;}
      if(cpCwsOJoIa == true){cpCwsOJoIa = false;}
      if(ISrASKYwKp == true){ISrASKYwKp = false;}
      if(RngJBPsccx == true){RngJBPsccx = false;}
      if(UwPAQlrzdB == true){UwPAQlrzdB = false;}
      if(dHPtpfUnBk == true){dHPtpfUnBk = false;}
      if(WtYhloJrud == true){WtYhloJrud = false;}
      if(UfMLGLDrjf == true){UfMLGLDrjf = false;}
      if(RZRJMKYmTU == true){RZRJMKYmTU = false;}
      if(tFbrZZXhNa == true){tFbrZZXhNa = false;}
      if(cAEAfxuDne == true){cAEAfxuDne = false;}
      if(ccEUSxbPUb == true){ccEUSxbPUb = false;}
      if(QVYZjPETkf == true){QVYZjPETkf = false;}
      if(nUdIDRVRcO == true){nUdIDRVRcO = false;}
      if(OUzorQAGZc == true){OUzorQAGZc = false;}
      if(yIMkKGadPQ == true){yIMkKGadPQ = false;}
      if(raRHpHyuRA == true){raRHpHyuRA = false;}
      if(bJlGMwWjhS == true){bJlGMwWjhS = false;}
      if(OytIheIsyw == true){OytIheIsyw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSUVZJHRAE
{ 
  void qnweAKrtgE()
  { 
      bool oGAHzoGStd = false;
      bool CUGHDfkjqm = false;
      bool nddPoAuIDT = false;
      bool cnuxlZcFQQ = false;
      bool QtnVYCWxoY = false;
      bool QRDYjKbkRz = false;
      bool syPaBOYJVc = false;
      bool CeSaWtpIqm = false;
      bool cxTdCKjWMb = false;
      bool yrmRWReMUJ = false;
      bool cNbLWkybCp = false;
      bool UTteVwdkXp = false;
      bool eCxseKqBEE = false;
      bool PcmhKPUIHR = false;
      bool MITVHeyIwa = false;
      bool nsoedZPifM = false;
      bool sxXxaqfMTF = false;
      bool aVdFdVhblA = false;
      bool LiEdQWnIDj = false;
      bool AlcuYOkWtP = false;
      string ixRcXnwaNT;
      string kOKJkItLpA;
      string GFJaxEVCVt;
      string VDDSuxQayg;
      string YpReYXyoAr;
      string zrETGdmpeS;
      string RsFSxgKqOm;
      string qSNJaQmdBZ;
      string GgCcudyjMR;
      string KZwfOfkyhr;
      string MGZMBfeurp;
      string pIoELkpcXT;
      string hadxcRVgtu;
      string enwJNzGobP;
      string yDrWaBkrTd;
      string oHaOJlccji;
      string KxBxKBMeqM;
      string dABIUeiHVb;
      string fdMQFWNhAb;
      string WdFrFBCuLY;
      if(ixRcXnwaNT == MGZMBfeurp){oGAHzoGStd = true;}
      else if(MGZMBfeurp == ixRcXnwaNT){cNbLWkybCp = true;}
      if(kOKJkItLpA == pIoELkpcXT){CUGHDfkjqm = true;}
      else if(pIoELkpcXT == kOKJkItLpA){UTteVwdkXp = true;}
      if(GFJaxEVCVt == hadxcRVgtu){nddPoAuIDT = true;}
      else if(hadxcRVgtu == GFJaxEVCVt){eCxseKqBEE = true;}
      if(VDDSuxQayg == enwJNzGobP){cnuxlZcFQQ = true;}
      else if(enwJNzGobP == VDDSuxQayg){PcmhKPUIHR = true;}
      if(YpReYXyoAr == yDrWaBkrTd){QtnVYCWxoY = true;}
      else if(yDrWaBkrTd == YpReYXyoAr){MITVHeyIwa = true;}
      if(zrETGdmpeS == oHaOJlccji){QRDYjKbkRz = true;}
      else if(oHaOJlccji == zrETGdmpeS){nsoedZPifM = true;}
      if(RsFSxgKqOm == KxBxKBMeqM){syPaBOYJVc = true;}
      else if(KxBxKBMeqM == RsFSxgKqOm){sxXxaqfMTF = true;}
      if(qSNJaQmdBZ == dABIUeiHVb){CeSaWtpIqm = true;}
      if(GgCcudyjMR == fdMQFWNhAb){cxTdCKjWMb = true;}
      if(KZwfOfkyhr == WdFrFBCuLY){yrmRWReMUJ = true;}
      while(dABIUeiHVb == qSNJaQmdBZ){aVdFdVhblA = true;}
      while(fdMQFWNhAb == fdMQFWNhAb){LiEdQWnIDj = true;}
      while(WdFrFBCuLY == WdFrFBCuLY){AlcuYOkWtP = true;}
      if(oGAHzoGStd == true){oGAHzoGStd = false;}
      if(CUGHDfkjqm == true){CUGHDfkjqm = false;}
      if(nddPoAuIDT == true){nddPoAuIDT = false;}
      if(cnuxlZcFQQ == true){cnuxlZcFQQ = false;}
      if(QtnVYCWxoY == true){QtnVYCWxoY = false;}
      if(QRDYjKbkRz == true){QRDYjKbkRz = false;}
      if(syPaBOYJVc == true){syPaBOYJVc = false;}
      if(CeSaWtpIqm == true){CeSaWtpIqm = false;}
      if(cxTdCKjWMb == true){cxTdCKjWMb = false;}
      if(yrmRWReMUJ == true){yrmRWReMUJ = false;}
      if(cNbLWkybCp == true){cNbLWkybCp = false;}
      if(UTteVwdkXp == true){UTteVwdkXp = false;}
      if(eCxseKqBEE == true){eCxseKqBEE = false;}
      if(PcmhKPUIHR == true){PcmhKPUIHR = false;}
      if(MITVHeyIwa == true){MITVHeyIwa = false;}
      if(nsoedZPifM == true){nsoedZPifM = false;}
      if(sxXxaqfMTF == true){sxXxaqfMTF = false;}
      if(aVdFdVhblA == true){aVdFdVhblA = false;}
      if(LiEdQWnIDj == true){LiEdQWnIDj = false;}
      if(AlcuYOkWtP == true){AlcuYOkWtP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWOOADPBQU
{ 
  void BkWiYNCoBF()
  { 
      bool MUnSgHGmwG = false;
      bool eZeoMnzDLV = false;
      bool HWeUlodeJl = false;
      bool QWCVNRtUUV = false;
      bool kXcMcIXYJG = false;
      bool hxFhBopTfr = false;
      bool dadKpHWJat = false;
      bool sdiokitRqd = false;
      bool QEVCDSRTTY = false;
      bool baocrJtRWU = false;
      bool lNxONEOPxR = false;
      bool tXcCaYFbGW = false;
      bool pDoCRSoGxa = false;
      bool ocuWqCGGoz = false;
      bool EBVCdEymBS = false;
      bool ERKzdiXuxt = false;
      bool PHSWcRcFKX = false;
      bool RylHSogmYN = false;
      bool UBFdVWRwrI = false;
      bool dLJtjwhzZL = false;
      string uHhZxjSnBV;
      string wYjzMzjiZf;
      string FCXCenAOqk;
      string ygAasflPhQ;
      string cagcNnQWhR;
      string sOqXssietI;
      string jEwPXPYIGg;
      string MUAJDeUuoq;
      string XdfZripbhA;
      string wHUYgYdQFy;
      string PHPBEXOhUO;
      string XmoDkGXWXn;
      string ZwaGjFAbbe;
      string AEpqaPNeUT;
      string UHHSbJRQnZ;
      string AHrQXTgJQz;
      string XmFpOTwxbV;
      string srBETRnHda;
      string mimBdrLZSH;
      string iDOVuhBREI;
      if(uHhZxjSnBV == PHPBEXOhUO){MUnSgHGmwG = true;}
      else if(PHPBEXOhUO == uHhZxjSnBV){lNxONEOPxR = true;}
      if(wYjzMzjiZf == XmoDkGXWXn){eZeoMnzDLV = true;}
      else if(XmoDkGXWXn == wYjzMzjiZf){tXcCaYFbGW = true;}
      if(FCXCenAOqk == ZwaGjFAbbe){HWeUlodeJl = true;}
      else if(ZwaGjFAbbe == FCXCenAOqk){pDoCRSoGxa = true;}
      if(ygAasflPhQ == AEpqaPNeUT){QWCVNRtUUV = true;}
      else if(AEpqaPNeUT == ygAasflPhQ){ocuWqCGGoz = true;}
      if(cagcNnQWhR == UHHSbJRQnZ){kXcMcIXYJG = true;}
      else if(UHHSbJRQnZ == cagcNnQWhR){EBVCdEymBS = true;}
      if(sOqXssietI == AHrQXTgJQz){hxFhBopTfr = true;}
      else if(AHrQXTgJQz == sOqXssietI){ERKzdiXuxt = true;}
      if(jEwPXPYIGg == XmFpOTwxbV){dadKpHWJat = true;}
      else if(XmFpOTwxbV == jEwPXPYIGg){PHSWcRcFKX = true;}
      if(MUAJDeUuoq == srBETRnHda){sdiokitRqd = true;}
      if(XdfZripbhA == mimBdrLZSH){QEVCDSRTTY = true;}
      if(wHUYgYdQFy == iDOVuhBREI){baocrJtRWU = true;}
      while(srBETRnHda == MUAJDeUuoq){RylHSogmYN = true;}
      while(mimBdrLZSH == mimBdrLZSH){UBFdVWRwrI = true;}
      while(iDOVuhBREI == iDOVuhBREI){dLJtjwhzZL = true;}
      if(MUnSgHGmwG == true){MUnSgHGmwG = false;}
      if(eZeoMnzDLV == true){eZeoMnzDLV = false;}
      if(HWeUlodeJl == true){HWeUlodeJl = false;}
      if(QWCVNRtUUV == true){QWCVNRtUUV = false;}
      if(kXcMcIXYJG == true){kXcMcIXYJG = false;}
      if(hxFhBopTfr == true){hxFhBopTfr = false;}
      if(dadKpHWJat == true){dadKpHWJat = false;}
      if(sdiokitRqd == true){sdiokitRqd = false;}
      if(QEVCDSRTTY == true){QEVCDSRTTY = false;}
      if(baocrJtRWU == true){baocrJtRWU = false;}
      if(lNxONEOPxR == true){lNxONEOPxR = false;}
      if(tXcCaYFbGW == true){tXcCaYFbGW = false;}
      if(pDoCRSoGxa == true){pDoCRSoGxa = false;}
      if(ocuWqCGGoz == true){ocuWqCGGoz = false;}
      if(EBVCdEymBS == true){EBVCdEymBS = false;}
      if(ERKzdiXuxt == true){ERKzdiXuxt = false;}
      if(PHSWcRcFKX == true){PHSWcRcFKX = false;}
      if(RylHSogmYN == true){RylHSogmYN = false;}
      if(UBFdVWRwrI == true){UBFdVWRwrI = false;}
      if(dLJtjwhzZL == true){dLJtjwhzZL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZISOHNGXHS
{ 
  void GPunlBWuWB()
  { 
      bool lkLZTfHOMz = false;
      bool FKPLMtIJRw = false;
      bool WqqEfDLoCW = false;
      bool hDeeuGcCLA = false;
      bool FkQdaCuHAC = false;
      bool FpQIzttHsP = false;
      bool TRMoQBekPF = false;
      bool QFyRpkaNcd = false;
      bool HEnzQrmVeB = false;
      bool MVIugnYaMZ = false;
      bool WJqukAqzRN = false;
      bool SgdPIPcMXY = false;
      bool OJGOsuwDkC = false;
      bool MzADGxMsOQ = false;
      bool AmDRhersmQ = false;
      bool KLDnLMDcBo = false;
      bool EnOPBTgZIK = false;
      bool CjyHYaGngN = false;
      bool DDQTrAwMrs = false;
      bool sjqYLLYnPN = false;
      string ZPmizyFAAu;
      string NFiqwMulCo;
      string chKqowSRHS;
      string dtMjUGeBWI;
      string rYaBZEsfWk;
      string PwynlqEutD;
      string fmrhRTryWp;
      string hsPswEGJQj;
      string CmtWCguYxc;
      string BjHScEfsiG;
      string LuJgDVgFqh;
      string judJAssVek;
      string YTAsnylwPr;
      string XNaKXHcMSf;
      string zpgPrGFxSj;
      string LKNxhqtQsF;
      string ikoyJWUTkr;
      string PfCykiljAg;
      string rocefNAccg;
      string MLTNwOAiFV;
      if(ZPmizyFAAu == LuJgDVgFqh){lkLZTfHOMz = true;}
      else if(LuJgDVgFqh == ZPmizyFAAu){WJqukAqzRN = true;}
      if(NFiqwMulCo == judJAssVek){FKPLMtIJRw = true;}
      else if(judJAssVek == NFiqwMulCo){SgdPIPcMXY = true;}
      if(chKqowSRHS == YTAsnylwPr){WqqEfDLoCW = true;}
      else if(YTAsnylwPr == chKqowSRHS){OJGOsuwDkC = true;}
      if(dtMjUGeBWI == XNaKXHcMSf){hDeeuGcCLA = true;}
      else if(XNaKXHcMSf == dtMjUGeBWI){MzADGxMsOQ = true;}
      if(rYaBZEsfWk == zpgPrGFxSj){FkQdaCuHAC = true;}
      else if(zpgPrGFxSj == rYaBZEsfWk){AmDRhersmQ = true;}
      if(PwynlqEutD == LKNxhqtQsF){FpQIzttHsP = true;}
      else if(LKNxhqtQsF == PwynlqEutD){KLDnLMDcBo = true;}
      if(fmrhRTryWp == ikoyJWUTkr){TRMoQBekPF = true;}
      else if(ikoyJWUTkr == fmrhRTryWp){EnOPBTgZIK = true;}
      if(hsPswEGJQj == PfCykiljAg){QFyRpkaNcd = true;}
      if(CmtWCguYxc == rocefNAccg){HEnzQrmVeB = true;}
      if(BjHScEfsiG == MLTNwOAiFV){MVIugnYaMZ = true;}
      while(PfCykiljAg == hsPswEGJQj){CjyHYaGngN = true;}
      while(rocefNAccg == rocefNAccg){DDQTrAwMrs = true;}
      while(MLTNwOAiFV == MLTNwOAiFV){sjqYLLYnPN = true;}
      if(lkLZTfHOMz == true){lkLZTfHOMz = false;}
      if(FKPLMtIJRw == true){FKPLMtIJRw = false;}
      if(WqqEfDLoCW == true){WqqEfDLoCW = false;}
      if(hDeeuGcCLA == true){hDeeuGcCLA = false;}
      if(FkQdaCuHAC == true){FkQdaCuHAC = false;}
      if(FpQIzttHsP == true){FpQIzttHsP = false;}
      if(TRMoQBekPF == true){TRMoQBekPF = false;}
      if(QFyRpkaNcd == true){QFyRpkaNcd = false;}
      if(HEnzQrmVeB == true){HEnzQrmVeB = false;}
      if(MVIugnYaMZ == true){MVIugnYaMZ = false;}
      if(WJqukAqzRN == true){WJqukAqzRN = false;}
      if(SgdPIPcMXY == true){SgdPIPcMXY = false;}
      if(OJGOsuwDkC == true){OJGOsuwDkC = false;}
      if(MzADGxMsOQ == true){MzADGxMsOQ = false;}
      if(AmDRhersmQ == true){AmDRhersmQ = false;}
      if(KLDnLMDcBo == true){KLDnLMDcBo = false;}
      if(EnOPBTgZIK == true){EnOPBTgZIK = false;}
      if(CjyHYaGngN == true){CjyHYaGngN = false;}
      if(DDQTrAwMrs == true){DDQTrAwMrs = false;}
      if(sjqYLLYnPN == true){sjqYLLYnPN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZKSVTJEOE
{ 
  void TEoEyUjxlS()
  { 
      bool xGFIxNRYAZ = false;
      bool xcrUtsBUfb = false;
      bool CJMRTYEODC = false;
      bool aVsWKfYVcK = false;
      bool mJkiKsPQAc = false;
      bool eTbjbnsmoY = false;
      bool JCUyzajVJO = false;
      bool TerVnsXdHZ = false;
      bool ImOaXHtIuW = false;
      bool llgDBknmij = false;
      bool JsGkIzbGwh = false;
      bool POeOQVntar = false;
      bool faalbhyoTD = false;
      bool FkuXQPgcSX = false;
      bool emMMHWGSlf = false;
      bool xtMpDhSUJZ = false;
      bool AmlscdTGxB = false;
      bool oKaCMsONeE = false;
      bool bfCnGKYEUh = false;
      bool wLTrWrATjc = false;
      string TTPRZVpnug;
      string iqcurTuPcq;
      string OFAHGkYpgD;
      string MBGSwdFylK;
      string HUIzVDtKtJ;
      string cnSOJOSHKo;
      string xAHrTgjJzN;
      string NwcSitwBlC;
      string qNuWZXirJg;
      string LymxNHMQen;
      string TjLfwgLAfO;
      string RRUIxiEkSu;
      string yqARCPJeEa;
      string gfVyiGCOas;
      string MiMtPscezd;
      string Dbyiobitdf;
      string WfuEhkwWZq;
      string foJYiOeGBI;
      string ldeZXFhlJH;
      string WHktVfnIMe;
      if(TTPRZVpnug == TjLfwgLAfO){xGFIxNRYAZ = true;}
      else if(TjLfwgLAfO == TTPRZVpnug){JsGkIzbGwh = true;}
      if(iqcurTuPcq == RRUIxiEkSu){xcrUtsBUfb = true;}
      else if(RRUIxiEkSu == iqcurTuPcq){POeOQVntar = true;}
      if(OFAHGkYpgD == yqARCPJeEa){CJMRTYEODC = true;}
      else if(yqARCPJeEa == OFAHGkYpgD){faalbhyoTD = true;}
      if(MBGSwdFylK == gfVyiGCOas){aVsWKfYVcK = true;}
      else if(gfVyiGCOas == MBGSwdFylK){FkuXQPgcSX = true;}
      if(HUIzVDtKtJ == MiMtPscezd){mJkiKsPQAc = true;}
      else if(MiMtPscezd == HUIzVDtKtJ){emMMHWGSlf = true;}
      if(cnSOJOSHKo == Dbyiobitdf){eTbjbnsmoY = true;}
      else if(Dbyiobitdf == cnSOJOSHKo){xtMpDhSUJZ = true;}
      if(xAHrTgjJzN == WfuEhkwWZq){JCUyzajVJO = true;}
      else if(WfuEhkwWZq == xAHrTgjJzN){AmlscdTGxB = true;}
      if(NwcSitwBlC == foJYiOeGBI){TerVnsXdHZ = true;}
      if(qNuWZXirJg == ldeZXFhlJH){ImOaXHtIuW = true;}
      if(LymxNHMQen == WHktVfnIMe){llgDBknmij = true;}
      while(foJYiOeGBI == NwcSitwBlC){oKaCMsONeE = true;}
      while(ldeZXFhlJH == ldeZXFhlJH){bfCnGKYEUh = true;}
      while(WHktVfnIMe == WHktVfnIMe){wLTrWrATjc = true;}
      if(xGFIxNRYAZ == true){xGFIxNRYAZ = false;}
      if(xcrUtsBUfb == true){xcrUtsBUfb = false;}
      if(CJMRTYEODC == true){CJMRTYEODC = false;}
      if(aVsWKfYVcK == true){aVsWKfYVcK = false;}
      if(mJkiKsPQAc == true){mJkiKsPQAc = false;}
      if(eTbjbnsmoY == true){eTbjbnsmoY = false;}
      if(JCUyzajVJO == true){JCUyzajVJO = false;}
      if(TerVnsXdHZ == true){TerVnsXdHZ = false;}
      if(ImOaXHtIuW == true){ImOaXHtIuW = false;}
      if(llgDBknmij == true){llgDBknmij = false;}
      if(JsGkIzbGwh == true){JsGkIzbGwh = false;}
      if(POeOQVntar == true){POeOQVntar = false;}
      if(faalbhyoTD == true){faalbhyoTD = false;}
      if(FkuXQPgcSX == true){FkuXQPgcSX = false;}
      if(emMMHWGSlf == true){emMMHWGSlf = false;}
      if(xtMpDhSUJZ == true){xtMpDhSUJZ = false;}
      if(AmlscdTGxB == true){AmlscdTGxB = false;}
      if(oKaCMsONeE == true){oKaCMsONeE = false;}
      if(bfCnGKYEUh == true){bfCnGKYEUh = false;}
      if(wLTrWrATjc == true){wLTrWrATjc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSVIXMOQZT
{ 
  void QhyfiNMZxX()
  { 
      bool PpQOucrwES = false;
      bool tCeVHSpfES = false;
      bool zJWsnOSjZi = false;
      bool CIekqsDrIq = false;
      bool qVZaRdVzPd = false;
      bool UpOPkGSXZf = false;
      bool KHWVPlWsdN = false;
      bool OxXNbdjwaK = false;
      bool sSTuOMsOAk = false;
      bool afRbfizDKf = false;
      bool GcUCPWRBnH = false;
      bool VWwPmrnaHD = false;
      bool rIssmhfwgs = false;
      bool dfkuEQyRfq = false;
      bool urarPEjCnn = false;
      bool uXwHmyibOg = false;
      bool qUTudokAKW = false;
      bool sVtPIAgBdh = false;
      bool ycIsxFjcIG = false;
      bool gWCzAZXfOZ = false;
      string SXXCorzDLb;
      string fglIBSXcUe;
      string zDcOoGsSgr;
      string dwINYRSWjb;
      string lsrzGPpNai;
      string egqDqPuJNi;
      string yfVTyjYXjj;
      string AArrrFKdHZ;
      string PfqyNwEEWI;
      string WIJBdGWYAW;
      string qScqidnyLk;
      string ERBnSSnWFB;
      string eUAaMqppOl;
      string ilckhxCAPi;
      string IGrlEEHViK;
      string RzSyqVRCdq;
      string mxjYCSnQFU;
      string PnHVsYbOWH;
      string jUHDUiSesL;
      string fAVXwKVTik;
      if(SXXCorzDLb == qScqidnyLk){PpQOucrwES = true;}
      else if(qScqidnyLk == SXXCorzDLb){GcUCPWRBnH = true;}
      if(fglIBSXcUe == ERBnSSnWFB){tCeVHSpfES = true;}
      else if(ERBnSSnWFB == fglIBSXcUe){VWwPmrnaHD = true;}
      if(zDcOoGsSgr == eUAaMqppOl){zJWsnOSjZi = true;}
      else if(eUAaMqppOl == zDcOoGsSgr){rIssmhfwgs = true;}
      if(dwINYRSWjb == ilckhxCAPi){CIekqsDrIq = true;}
      else if(ilckhxCAPi == dwINYRSWjb){dfkuEQyRfq = true;}
      if(lsrzGPpNai == IGrlEEHViK){qVZaRdVzPd = true;}
      else if(IGrlEEHViK == lsrzGPpNai){urarPEjCnn = true;}
      if(egqDqPuJNi == RzSyqVRCdq){UpOPkGSXZf = true;}
      else if(RzSyqVRCdq == egqDqPuJNi){uXwHmyibOg = true;}
      if(yfVTyjYXjj == mxjYCSnQFU){KHWVPlWsdN = true;}
      else if(mxjYCSnQFU == yfVTyjYXjj){qUTudokAKW = true;}
      if(AArrrFKdHZ == PnHVsYbOWH){OxXNbdjwaK = true;}
      if(PfqyNwEEWI == jUHDUiSesL){sSTuOMsOAk = true;}
      if(WIJBdGWYAW == fAVXwKVTik){afRbfizDKf = true;}
      while(PnHVsYbOWH == AArrrFKdHZ){sVtPIAgBdh = true;}
      while(jUHDUiSesL == jUHDUiSesL){ycIsxFjcIG = true;}
      while(fAVXwKVTik == fAVXwKVTik){gWCzAZXfOZ = true;}
      if(PpQOucrwES == true){PpQOucrwES = false;}
      if(tCeVHSpfES == true){tCeVHSpfES = false;}
      if(zJWsnOSjZi == true){zJWsnOSjZi = false;}
      if(CIekqsDrIq == true){CIekqsDrIq = false;}
      if(qVZaRdVzPd == true){qVZaRdVzPd = false;}
      if(UpOPkGSXZf == true){UpOPkGSXZf = false;}
      if(KHWVPlWsdN == true){KHWVPlWsdN = false;}
      if(OxXNbdjwaK == true){OxXNbdjwaK = false;}
      if(sSTuOMsOAk == true){sSTuOMsOAk = false;}
      if(afRbfizDKf == true){afRbfizDKf = false;}
      if(GcUCPWRBnH == true){GcUCPWRBnH = false;}
      if(VWwPmrnaHD == true){VWwPmrnaHD = false;}
      if(rIssmhfwgs == true){rIssmhfwgs = false;}
      if(dfkuEQyRfq == true){dfkuEQyRfq = false;}
      if(urarPEjCnn == true){urarPEjCnn = false;}
      if(uXwHmyibOg == true){uXwHmyibOg = false;}
      if(qUTudokAKW == true){qUTudokAKW = false;}
      if(sVtPIAgBdh == true){sVtPIAgBdh = false;}
      if(ycIsxFjcIG == true){ycIsxFjcIG = false;}
      if(gWCzAZXfOZ == true){gWCzAZXfOZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIJJLODIDD
{ 
  void sgmZVMBZoI()
  { 
      bool FCWySFykjh = false;
      bool FOhPUXGXFy = false;
      bool jLByDjrfhF = false;
      bool CdjnePYyYf = false;
      bool kBqCOImJAH = false;
      bool cQWKssBYui = false;
      bool MRDdeadskF = false;
      bool yIzZNhUyit = false;
      bool wieZblGYul = false;
      bool OADpSSxMXm = false;
      bool dtYuIUQxxK = false;
      bool YCoAmcmdCs = false;
      bool UFyzpyFJGt = false;
      bool kHawQCKjQH = false;
      bool UJajMLKCDo = false;
      bool fTKdSXuZEK = false;
      bool PHqDZQbsij = false;
      bool SCMtXLeNle = false;
      bool nCGQNQxwcr = false;
      bool GkeGrNRXKw = false;
      string ryPXFDnINe;
      string QqgujLkLjo;
      string biDkEXkprq;
      string lhufSaRJLS;
      string OcjxDiwuln;
      string iYxaSIteTg;
      string RxPWrhuAbJ;
      string sbzQayzGgU;
      string bpDEINkUNJ;
      string flodAQNNEV;
      string nwSctHYfAT;
      string InxzFbsLOe;
      string wamScHlUPJ;
      string klBKgfWaJA;
      string nETsArooXY;
      string XBzZZMIAAm;
      string UDPqiWmlSZ;
      string FSCNpqGtRj;
      string RwwqkjmakT;
      string WVZVfjncJc;
      if(ryPXFDnINe == nwSctHYfAT){FCWySFykjh = true;}
      else if(nwSctHYfAT == ryPXFDnINe){dtYuIUQxxK = true;}
      if(QqgujLkLjo == InxzFbsLOe){FOhPUXGXFy = true;}
      else if(InxzFbsLOe == QqgujLkLjo){YCoAmcmdCs = true;}
      if(biDkEXkprq == wamScHlUPJ){jLByDjrfhF = true;}
      else if(wamScHlUPJ == biDkEXkprq){UFyzpyFJGt = true;}
      if(lhufSaRJLS == klBKgfWaJA){CdjnePYyYf = true;}
      else if(klBKgfWaJA == lhufSaRJLS){kHawQCKjQH = true;}
      if(OcjxDiwuln == nETsArooXY){kBqCOImJAH = true;}
      else if(nETsArooXY == OcjxDiwuln){UJajMLKCDo = true;}
      if(iYxaSIteTg == XBzZZMIAAm){cQWKssBYui = true;}
      else if(XBzZZMIAAm == iYxaSIteTg){fTKdSXuZEK = true;}
      if(RxPWrhuAbJ == UDPqiWmlSZ){MRDdeadskF = true;}
      else if(UDPqiWmlSZ == RxPWrhuAbJ){PHqDZQbsij = true;}
      if(sbzQayzGgU == FSCNpqGtRj){yIzZNhUyit = true;}
      if(bpDEINkUNJ == RwwqkjmakT){wieZblGYul = true;}
      if(flodAQNNEV == WVZVfjncJc){OADpSSxMXm = true;}
      while(FSCNpqGtRj == sbzQayzGgU){SCMtXLeNle = true;}
      while(RwwqkjmakT == RwwqkjmakT){nCGQNQxwcr = true;}
      while(WVZVfjncJc == WVZVfjncJc){GkeGrNRXKw = true;}
      if(FCWySFykjh == true){FCWySFykjh = false;}
      if(FOhPUXGXFy == true){FOhPUXGXFy = false;}
      if(jLByDjrfhF == true){jLByDjrfhF = false;}
      if(CdjnePYyYf == true){CdjnePYyYf = false;}
      if(kBqCOImJAH == true){kBqCOImJAH = false;}
      if(cQWKssBYui == true){cQWKssBYui = false;}
      if(MRDdeadskF == true){MRDdeadskF = false;}
      if(yIzZNhUyit == true){yIzZNhUyit = false;}
      if(wieZblGYul == true){wieZblGYul = false;}
      if(OADpSSxMXm == true){OADpSSxMXm = false;}
      if(dtYuIUQxxK == true){dtYuIUQxxK = false;}
      if(YCoAmcmdCs == true){YCoAmcmdCs = false;}
      if(UFyzpyFJGt == true){UFyzpyFJGt = false;}
      if(kHawQCKjQH == true){kHawQCKjQH = false;}
      if(UJajMLKCDo == true){UJajMLKCDo = false;}
      if(fTKdSXuZEK == true){fTKdSXuZEK = false;}
      if(PHqDZQbsij == true){PHqDZQbsij = false;}
      if(SCMtXLeNle == true){SCMtXLeNle = false;}
      if(nCGQNQxwcr == true){nCGQNQxwcr = false;}
      if(GkeGrNRXKw == true){GkeGrNRXKw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKNJIIBILK
{ 
  void AznIxEHohJ()
  { 
      bool qKrjRmoqBb = false;
      bool TzeqjeaYuu = false;
      bool uqnsUeycBR = false;
      bool kWFpSoYkPD = false;
      bool UrieuRQxzt = false;
      bool aZKTrAVzPm = false;
      bool nMpjpxsoXt = false;
      bool GpIqaCHIxC = false;
      bool OBdGpLLkxS = false;
      bool TYVbOICyny = false;
      bool YaYEnkRSso = false;
      bool rMBMYmiise = false;
      bool kHqFagTfcR = false;
      bool AJTzdmcYRF = false;
      bool srrHaGWIDb = false;
      bool ZTFJMQiTcH = false;
      bool QkpaoirChk = false;
      bool KJQmkrPjeT = false;
      bool JLcArfEKlN = false;
      bool DIwKoICQRq = false;
      string MLoOLcXQQV;
      string umiHDpLAaX;
      string OMlBOqeZck;
      string PUVCEZMWOZ;
      string BUtsdisNGT;
      string CahZMAZnAU;
      string yxnfFaRgDc;
      string dnlBVsRrWe;
      string xQTIinlwoD;
      string AXWsaEgOmC;
      string RLKdpNogDS;
      string igQUWhcewR;
      string oUqzcGRraR;
      string MCFUMkGpSU;
      string yErVUSGBWs;
      string aBSUMxUKBi;
      string uwFlGfbwIl;
      string amLaSjcVeJ;
      string zQVgqKjkHP;
      string QwniZByGPn;
      if(MLoOLcXQQV == RLKdpNogDS){qKrjRmoqBb = true;}
      else if(RLKdpNogDS == MLoOLcXQQV){YaYEnkRSso = true;}
      if(umiHDpLAaX == igQUWhcewR){TzeqjeaYuu = true;}
      else if(igQUWhcewR == umiHDpLAaX){rMBMYmiise = true;}
      if(OMlBOqeZck == oUqzcGRraR){uqnsUeycBR = true;}
      else if(oUqzcGRraR == OMlBOqeZck){kHqFagTfcR = true;}
      if(PUVCEZMWOZ == MCFUMkGpSU){kWFpSoYkPD = true;}
      else if(MCFUMkGpSU == PUVCEZMWOZ){AJTzdmcYRF = true;}
      if(BUtsdisNGT == yErVUSGBWs){UrieuRQxzt = true;}
      else if(yErVUSGBWs == BUtsdisNGT){srrHaGWIDb = true;}
      if(CahZMAZnAU == aBSUMxUKBi){aZKTrAVzPm = true;}
      else if(aBSUMxUKBi == CahZMAZnAU){ZTFJMQiTcH = true;}
      if(yxnfFaRgDc == uwFlGfbwIl){nMpjpxsoXt = true;}
      else if(uwFlGfbwIl == yxnfFaRgDc){QkpaoirChk = true;}
      if(dnlBVsRrWe == amLaSjcVeJ){GpIqaCHIxC = true;}
      if(xQTIinlwoD == zQVgqKjkHP){OBdGpLLkxS = true;}
      if(AXWsaEgOmC == QwniZByGPn){TYVbOICyny = true;}
      while(amLaSjcVeJ == dnlBVsRrWe){KJQmkrPjeT = true;}
      while(zQVgqKjkHP == zQVgqKjkHP){JLcArfEKlN = true;}
      while(QwniZByGPn == QwniZByGPn){DIwKoICQRq = true;}
      if(qKrjRmoqBb == true){qKrjRmoqBb = false;}
      if(TzeqjeaYuu == true){TzeqjeaYuu = false;}
      if(uqnsUeycBR == true){uqnsUeycBR = false;}
      if(kWFpSoYkPD == true){kWFpSoYkPD = false;}
      if(UrieuRQxzt == true){UrieuRQxzt = false;}
      if(aZKTrAVzPm == true){aZKTrAVzPm = false;}
      if(nMpjpxsoXt == true){nMpjpxsoXt = false;}
      if(GpIqaCHIxC == true){GpIqaCHIxC = false;}
      if(OBdGpLLkxS == true){OBdGpLLkxS = false;}
      if(TYVbOICyny == true){TYVbOICyny = false;}
      if(YaYEnkRSso == true){YaYEnkRSso = false;}
      if(rMBMYmiise == true){rMBMYmiise = false;}
      if(kHqFagTfcR == true){kHqFagTfcR = false;}
      if(AJTzdmcYRF == true){AJTzdmcYRF = false;}
      if(srrHaGWIDb == true){srrHaGWIDb = false;}
      if(ZTFJMQiTcH == true){ZTFJMQiTcH = false;}
      if(QkpaoirChk == true){QkpaoirChk = false;}
      if(KJQmkrPjeT == true){KJQmkrPjeT = false;}
      if(JLcArfEKlN == true){JLcArfEKlN = false;}
      if(DIwKoICQRq == true){DIwKoICQRq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VMLLTOTIZG
{ 
  void ezsAUKMNMj()
  { 
      bool BHiphqskoJ = false;
      bool JaMdDzHceP = false;
      bool iOaDhTmyDB = false;
      bool RdguNLPFtr = false;
      bool AJgkKmOSfF = false;
      bool oYtVGmgeIN = false;
      bool DugmqftRPr = false;
      bool jChmPYhost = false;
      bool FURyMriKoa = false;
      bool ejxgnEcste = false;
      bool sxCmVlqHGh = false;
      bool FqlNIiciay = false;
      bool wiboNzFBzK = false;
      bool wnuNBHRdbZ = false;
      bool BbEGUmyiXE = false;
      bool bsSuhJUNZW = false;
      bool goHulQwXLB = false;
      bool QyGBxUeVTZ = false;
      bool BVctiCVAer = false;
      bool lEEFrLTJUD = false;
      string iQwwlaTlzp;
      string oxgsCNfqOQ;
      string VUZazOZKTg;
      string CsrqBVsKPE;
      string HjYbzKxuap;
      string ZOXfQOqUwW;
      string BISSnuEoqf;
      string UVbKIluxao;
      string RdjcHnULZm;
      string eXOrCzQFnD;
      string GIDtUElNXe;
      string TssHFXYoLA;
      string arOEBxGiHJ;
      string UoJXhIaoHC;
      string BHnuTkdHme;
      string ZatncNtysX;
      string xDFOJdjVYw;
      string wihIzTDSkP;
      string TyucisuVuU;
      string ObwjExBZlo;
      if(iQwwlaTlzp == GIDtUElNXe){BHiphqskoJ = true;}
      else if(GIDtUElNXe == iQwwlaTlzp){sxCmVlqHGh = true;}
      if(oxgsCNfqOQ == TssHFXYoLA){JaMdDzHceP = true;}
      else if(TssHFXYoLA == oxgsCNfqOQ){FqlNIiciay = true;}
      if(VUZazOZKTg == arOEBxGiHJ){iOaDhTmyDB = true;}
      else if(arOEBxGiHJ == VUZazOZKTg){wiboNzFBzK = true;}
      if(CsrqBVsKPE == UoJXhIaoHC){RdguNLPFtr = true;}
      else if(UoJXhIaoHC == CsrqBVsKPE){wnuNBHRdbZ = true;}
      if(HjYbzKxuap == BHnuTkdHme){AJgkKmOSfF = true;}
      else if(BHnuTkdHme == HjYbzKxuap){BbEGUmyiXE = true;}
      if(ZOXfQOqUwW == ZatncNtysX){oYtVGmgeIN = true;}
      else if(ZatncNtysX == ZOXfQOqUwW){bsSuhJUNZW = true;}
      if(BISSnuEoqf == xDFOJdjVYw){DugmqftRPr = true;}
      else if(xDFOJdjVYw == BISSnuEoqf){goHulQwXLB = true;}
      if(UVbKIluxao == wihIzTDSkP){jChmPYhost = true;}
      if(RdjcHnULZm == TyucisuVuU){FURyMriKoa = true;}
      if(eXOrCzQFnD == ObwjExBZlo){ejxgnEcste = true;}
      while(wihIzTDSkP == UVbKIluxao){QyGBxUeVTZ = true;}
      while(TyucisuVuU == TyucisuVuU){BVctiCVAer = true;}
      while(ObwjExBZlo == ObwjExBZlo){lEEFrLTJUD = true;}
      if(BHiphqskoJ == true){BHiphqskoJ = false;}
      if(JaMdDzHceP == true){JaMdDzHceP = false;}
      if(iOaDhTmyDB == true){iOaDhTmyDB = false;}
      if(RdguNLPFtr == true){RdguNLPFtr = false;}
      if(AJgkKmOSfF == true){AJgkKmOSfF = false;}
      if(oYtVGmgeIN == true){oYtVGmgeIN = false;}
      if(DugmqftRPr == true){DugmqftRPr = false;}
      if(jChmPYhost == true){jChmPYhost = false;}
      if(FURyMriKoa == true){FURyMriKoa = false;}
      if(ejxgnEcste == true){ejxgnEcste = false;}
      if(sxCmVlqHGh == true){sxCmVlqHGh = false;}
      if(FqlNIiciay == true){FqlNIiciay = false;}
      if(wiboNzFBzK == true){wiboNzFBzK = false;}
      if(wnuNBHRdbZ == true){wnuNBHRdbZ = false;}
      if(BbEGUmyiXE == true){BbEGUmyiXE = false;}
      if(bsSuhJUNZW == true){bsSuhJUNZW = false;}
      if(goHulQwXLB == true){goHulQwXLB = false;}
      if(QyGBxUeVTZ == true){QyGBxUeVTZ = false;}
      if(BVctiCVAer == true){BVctiCVAer = false;}
      if(lEEFrLTJUD == true){lEEFrLTJUD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYWNMNESPQ
{ 
  void puYtWKXTxO()
  { 
      bool CNuQEbWZCr = false;
      bool yCYBdmNnVW = false;
      bool OwpfJbKWVj = false;
      bool qHNpaHpalQ = false;
      bool sUNziUKMnC = false;
      bool dLBUiGXOGb = false;
      bool QADRApnhaW = false;
      bool xlCEcthqxo = false;
      bool QyiSFfGrHU = false;
      bool jaUJzsQwyr = false;
      bool fclQFrJwro = false;
      bool XgRRKSRjMU = false;
      bool juZFlVRrEj = false;
      bool clrEInLRNN = false;
      bool VJASxDJCyg = false;
      bool afjdIkCgdi = false;
      bool ZRqHLlnMIW = false;
      bool HAWyyZtHIi = false;
      bool MPsXJwCOwX = false;
      bool kdmdmERsHK = false;
      string DmCLoRGFlz;
      string HzpZFJxoOj;
      string zSaPaDEORc;
      string gZgHhloTsk;
      string PFWYkQdAsj;
      string upMgKkMljk;
      string MqmISgSirT;
      string TcwdUtuCdJ;
      string ZEVggqMzww;
      string ZDiHXXROGD;
      string xtHZPSsiLQ;
      string pJHZLIVFba;
      string USlutQtnFw;
      string cgwaMewuRO;
      string xcmfGPuIwP;
      string CLleidIMfz;
      string XFdPnIMgNf;
      string LZnMcqfGnd;
      string UkqpsQtQqh;
      string WiORprzXrx;
      if(DmCLoRGFlz == xtHZPSsiLQ){CNuQEbWZCr = true;}
      else if(xtHZPSsiLQ == DmCLoRGFlz){fclQFrJwro = true;}
      if(HzpZFJxoOj == pJHZLIVFba){yCYBdmNnVW = true;}
      else if(pJHZLIVFba == HzpZFJxoOj){XgRRKSRjMU = true;}
      if(zSaPaDEORc == USlutQtnFw){OwpfJbKWVj = true;}
      else if(USlutQtnFw == zSaPaDEORc){juZFlVRrEj = true;}
      if(gZgHhloTsk == cgwaMewuRO){qHNpaHpalQ = true;}
      else if(cgwaMewuRO == gZgHhloTsk){clrEInLRNN = true;}
      if(PFWYkQdAsj == xcmfGPuIwP){sUNziUKMnC = true;}
      else if(xcmfGPuIwP == PFWYkQdAsj){VJASxDJCyg = true;}
      if(upMgKkMljk == CLleidIMfz){dLBUiGXOGb = true;}
      else if(CLleidIMfz == upMgKkMljk){afjdIkCgdi = true;}
      if(MqmISgSirT == XFdPnIMgNf){QADRApnhaW = true;}
      else if(XFdPnIMgNf == MqmISgSirT){ZRqHLlnMIW = true;}
      if(TcwdUtuCdJ == LZnMcqfGnd){xlCEcthqxo = true;}
      if(ZEVggqMzww == UkqpsQtQqh){QyiSFfGrHU = true;}
      if(ZDiHXXROGD == WiORprzXrx){jaUJzsQwyr = true;}
      while(LZnMcqfGnd == TcwdUtuCdJ){HAWyyZtHIi = true;}
      while(UkqpsQtQqh == UkqpsQtQqh){MPsXJwCOwX = true;}
      while(WiORprzXrx == WiORprzXrx){kdmdmERsHK = true;}
      if(CNuQEbWZCr == true){CNuQEbWZCr = false;}
      if(yCYBdmNnVW == true){yCYBdmNnVW = false;}
      if(OwpfJbKWVj == true){OwpfJbKWVj = false;}
      if(qHNpaHpalQ == true){qHNpaHpalQ = false;}
      if(sUNziUKMnC == true){sUNziUKMnC = false;}
      if(dLBUiGXOGb == true){dLBUiGXOGb = false;}
      if(QADRApnhaW == true){QADRApnhaW = false;}
      if(xlCEcthqxo == true){xlCEcthqxo = false;}
      if(QyiSFfGrHU == true){QyiSFfGrHU = false;}
      if(jaUJzsQwyr == true){jaUJzsQwyr = false;}
      if(fclQFrJwro == true){fclQFrJwro = false;}
      if(XgRRKSRjMU == true){XgRRKSRjMU = false;}
      if(juZFlVRrEj == true){juZFlVRrEj = false;}
      if(clrEInLRNN == true){clrEInLRNN = false;}
      if(VJASxDJCyg == true){VJASxDJCyg = false;}
      if(afjdIkCgdi == true){afjdIkCgdi = false;}
      if(ZRqHLlnMIW == true){ZRqHLlnMIW = false;}
      if(HAWyyZtHIi == true){HAWyyZtHIi = false;}
      if(MPsXJwCOwX == true){MPsXJwCOwX = false;}
      if(kdmdmERsHK == true){kdmdmERsHK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUZRACOZTK
{ 
  void WdjGVYiTbr()
  { 
      bool ZXGZBnkbwP = false;
      bool NuyWPJJotM = false;
      bool YGUsGioJAW = false;
      bool qaehQPKEiG = false;
      bool JpaZMhqwbI = false;
      bool fZLblSCNTR = false;
      bool yabZXlPQFz = false;
      bool zFFmChftfX = false;
      bool rshqpRODux = false;
      bool MxjRIiNABa = false;
      bool RapbJaTYYD = false;
      bool mIguZErjiG = false;
      bool XMUImBUndT = false;
      bool TesFGQDGhP = false;
      bool yoerJEPoqD = false;
      bool qdRuDEGhoH = false;
      bool FeuEiIPboI = false;
      bool BlBSHhhbyh = false;
      bool kfwacpMxCB = false;
      bool KUQZKStZJB = false;
      string phUHDRZcWJ;
      string WrujRgJInl;
      string JMlSXEyAPs;
      string JBmqkJGAiy;
      string JtnCndhiOy;
      string dBaJEduBjy;
      string TZMdzVFDzH;
      string ZJYocOYjes;
      string WOlROHZcmG;
      string OEQkejgKCR;
      string XeiGXUbkgp;
      string FKWpaEmuOr;
      string ucQssUrnKr;
      string gOgMVrfest;
      string eouwBDhaJZ;
      string wlwJWuOpMC;
      string bnZoIqdKTi;
      string YIBTNGgTrp;
      string mRdkuuSWpa;
      string coSqSpOGnK;
      if(phUHDRZcWJ == XeiGXUbkgp){ZXGZBnkbwP = true;}
      else if(XeiGXUbkgp == phUHDRZcWJ){RapbJaTYYD = true;}
      if(WrujRgJInl == FKWpaEmuOr){NuyWPJJotM = true;}
      else if(FKWpaEmuOr == WrujRgJInl){mIguZErjiG = true;}
      if(JMlSXEyAPs == ucQssUrnKr){YGUsGioJAW = true;}
      else if(ucQssUrnKr == JMlSXEyAPs){XMUImBUndT = true;}
      if(JBmqkJGAiy == gOgMVrfest){qaehQPKEiG = true;}
      else if(gOgMVrfest == JBmqkJGAiy){TesFGQDGhP = true;}
      if(JtnCndhiOy == eouwBDhaJZ){JpaZMhqwbI = true;}
      else if(eouwBDhaJZ == JtnCndhiOy){yoerJEPoqD = true;}
      if(dBaJEduBjy == wlwJWuOpMC){fZLblSCNTR = true;}
      else if(wlwJWuOpMC == dBaJEduBjy){qdRuDEGhoH = true;}
      if(TZMdzVFDzH == bnZoIqdKTi){yabZXlPQFz = true;}
      else if(bnZoIqdKTi == TZMdzVFDzH){FeuEiIPboI = true;}
      if(ZJYocOYjes == YIBTNGgTrp){zFFmChftfX = true;}
      if(WOlROHZcmG == mRdkuuSWpa){rshqpRODux = true;}
      if(OEQkejgKCR == coSqSpOGnK){MxjRIiNABa = true;}
      while(YIBTNGgTrp == ZJYocOYjes){BlBSHhhbyh = true;}
      while(mRdkuuSWpa == mRdkuuSWpa){kfwacpMxCB = true;}
      while(coSqSpOGnK == coSqSpOGnK){KUQZKStZJB = true;}
      if(ZXGZBnkbwP == true){ZXGZBnkbwP = false;}
      if(NuyWPJJotM == true){NuyWPJJotM = false;}
      if(YGUsGioJAW == true){YGUsGioJAW = false;}
      if(qaehQPKEiG == true){qaehQPKEiG = false;}
      if(JpaZMhqwbI == true){JpaZMhqwbI = false;}
      if(fZLblSCNTR == true){fZLblSCNTR = false;}
      if(yabZXlPQFz == true){yabZXlPQFz = false;}
      if(zFFmChftfX == true){zFFmChftfX = false;}
      if(rshqpRODux == true){rshqpRODux = false;}
      if(MxjRIiNABa == true){MxjRIiNABa = false;}
      if(RapbJaTYYD == true){RapbJaTYYD = false;}
      if(mIguZErjiG == true){mIguZErjiG = false;}
      if(XMUImBUndT == true){XMUImBUndT = false;}
      if(TesFGQDGhP == true){TesFGQDGhP = false;}
      if(yoerJEPoqD == true){yoerJEPoqD = false;}
      if(qdRuDEGhoH == true){qdRuDEGhoH = false;}
      if(FeuEiIPboI == true){FeuEiIPboI = false;}
      if(BlBSHhhbyh == true){BlBSHhhbyh = false;}
      if(kfwacpMxCB == true){kfwacpMxCB = false;}
      if(KUQZKStZJB == true){KUQZKStZJB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YPSMNTRVRT
{ 
  void IxfNPFfsOL()
  { 
      bool szMqxCCDVS = false;
      bool nLzfGqHpFJ = false;
      bool pLKrTnOAUy = false;
      bool uxigSWMGxE = false;
      bool LbhPYjIRNV = false;
      bool rXoxEgoTXJ = false;
      bool nChWXpcSNj = false;
      bool dAsByNduTj = false;
      bool fwlzFWIkck = false;
      bool gsinQJtLqi = false;
      bool GpEdrrenzp = false;
      bool DtAncqPiQA = false;
      bool hrobCjQEjo = false;
      bool TRDkcprIGN = false;
      bool rUlmgmsuKZ = false;
      bool sKtqAOAbbH = false;
      bool aZDJVlpOLm = false;
      bool yHbDINGCuO = false;
      bool qVtKuJXMjN = false;
      bool pQfzlSQbQu = false;
      string TkXSiLzACk;
      string EGjKEMwgbS;
      string ZOyVuAZosD;
      string KSPaKjAnEL;
      string cxxAXWfUiD;
      string QpqYlFlCWh;
      string kJHzZkqJzT;
      string MIcPobQyyY;
      string UFFolTbqnF;
      string xxQVZSpyZl;
      string fWUOqINaiJ;
      string nnEyNfESMF;
      string JzUsVOqGoV;
      string lRXLsxjqxd;
      string GAHeQJrRHt;
      string OXlTcfBbsc;
      string QGlMXWPsFP;
      string wMUhyJrpbM;
      string VZyuGNfDiM;
      string wHyUNAOtHt;
      if(TkXSiLzACk == fWUOqINaiJ){szMqxCCDVS = true;}
      else if(fWUOqINaiJ == TkXSiLzACk){GpEdrrenzp = true;}
      if(EGjKEMwgbS == nnEyNfESMF){nLzfGqHpFJ = true;}
      else if(nnEyNfESMF == EGjKEMwgbS){DtAncqPiQA = true;}
      if(ZOyVuAZosD == JzUsVOqGoV){pLKrTnOAUy = true;}
      else if(JzUsVOqGoV == ZOyVuAZosD){hrobCjQEjo = true;}
      if(KSPaKjAnEL == lRXLsxjqxd){uxigSWMGxE = true;}
      else if(lRXLsxjqxd == KSPaKjAnEL){TRDkcprIGN = true;}
      if(cxxAXWfUiD == GAHeQJrRHt){LbhPYjIRNV = true;}
      else if(GAHeQJrRHt == cxxAXWfUiD){rUlmgmsuKZ = true;}
      if(QpqYlFlCWh == OXlTcfBbsc){rXoxEgoTXJ = true;}
      else if(OXlTcfBbsc == QpqYlFlCWh){sKtqAOAbbH = true;}
      if(kJHzZkqJzT == QGlMXWPsFP){nChWXpcSNj = true;}
      else if(QGlMXWPsFP == kJHzZkqJzT){aZDJVlpOLm = true;}
      if(MIcPobQyyY == wMUhyJrpbM){dAsByNduTj = true;}
      if(UFFolTbqnF == VZyuGNfDiM){fwlzFWIkck = true;}
      if(xxQVZSpyZl == wHyUNAOtHt){gsinQJtLqi = true;}
      while(wMUhyJrpbM == MIcPobQyyY){yHbDINGCuO = true;}
      while(VZyuGNfDiM == VZyuGNfDiM){qVtKuJXMjN = true;}
      while(wHyUNAOtHt == wHyUNAOtHt){pQfzlSQbQu = true;}
      if(szMqxCCDVS == true){szMqxCCDVS = false;}
      if(nLzfGqHpFJ == true){nLzfGqHpFJ = false;}
      if(pLKrTnOAUy == true){pLKrTnOAUy = false;}
      if(uxigSWMGxE == true){uxigSWMGxE = false;}
      if(LbhPYjIRNV == true){LbhPYjIRNV = false;}
      if(rXoxEgoTXJ == true){rXoxEgoTXJ = false;}
      if(nChWXpcSNj == true){nChWXpcSNj = false;}
      if(dAsByNduTj == true){dAsByNduTj = false;}
      if(fwlzFWIkck == true){fwlzFWIkck = false;}
      if(gsinQJtLqi == true){gsinQJtLqi = false;}
      if(GpEdrrenzp == true){GpEdrrenzp = false;}
      if(DtAncqPiQA == true){DtAncqPiQA = false;}
      if(hrobCjQEjo == true){hrobCjQEjo = false;}
      if(TRDkcprIGN == true){TRDkcprIGN = false;}
      if(rUlmgmsuKZ == true){rUlmgmsuKZ = false;}
      if(sKtqAOAbbH == true){sKtqAOAbbH = false;}
      if(aZDJVlpOLm == true){aZDJVlpOLm = false;}
      if(yHbDINGCuO == true){yHbDINGCuO = false;}
      if(qVtKuJXMjN == true){qVtKuJXMjN = false;}
      if(pQfzlSQbQu == true){pQfzlSQbQu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLHPMHGSNM
{ 
  void COxkqOJdpe()
  { 
      bool LhCOqTFdqw = false;
      bool tFErTrntEL = false;
      bool SgQVDgIwPx = false;
      bool fZwzLdeUoN = false;
      bool hMuLZxupfR = false;
      bool xIoxReRfKJ = false;
      bool LINsQUIFgo = false;
      bool NTFqdGkEwF = false;
      bool lRQyAWkzgg = false;
      bool MzJeCYyBuE = false;
      bool opJpEdDxSL = false;
      bool sMiFXsrPst = false;
      bool iJYAcOJZnE = false;
      bool HjJqQuIasW = false;
      bool TmfUnAPEHJ = false;
      bool giIBUfRJNp = false;
      bool TcJNDJDqob = false;
      bool kQVWZwcDLc = false;
      bool zFSeXXaIWj = false;
      bool dzMDCqdRRd = false;
      string nssrgjYeUg;
      string MwRsCGctZJ;
      string IXcxWXFMWY;
      string FpkGPgQmzZ;
      string OnLuPZjxqp;
      string oVfZJQQuVI;
      string dMIubWLLdV;
      string optAuULggw;
      string mIVfijJLxz;
      string QVQpuCeQSs;
      string OYTVAzafeo;
      string EiNYVVqcLr;
      string MzNeETYEEr;
      string ouOnhOnzfj;
      string IdfItgHrUY;
      string KCEafOKnQf;
      string ZWalzJUYpG;
      string gqwaiiTFjX;
      string MgifgmpmIT;
      string DAizKkDsIk;
      if(nssrgjYeUg == OYTVAzafeo){LhCOqTFdqw = true;}
      else if(OYTVAzafeo == nssrgjYeUg){opJpEdDxSL = true;}
      if(MwRsCGctZJ == EiNYVVqcLr){tFErTrntEL = true;}
      else if(EiNYVVqcLr == MwRsCGctZJ){sMiFXsrPst = true;}
      if(IXcxWXFMWY == MzNeETYEEr){SgQVDgIwPx = true;}
      else if(MzNeETYEEr == IXcxWXFMWY){iJYAcOJZnE = true;}
      if(FpkGPgQmzZ == ouOnhOnzfj){fZwzLdeUoN = true;}
      else if(ouOnhOnzfj == FpkGPgQmzZ){HjJqQuIasW = true;}
      if(OnLuPZjxqp == IdfItgHrUY){hMuLZxupfR = true;}
      else if(IdfItgHrUY == OnLuPZjxqp){TmfUnAPEHJ = true;}
      if(oVfZJQQuVI == KCEafOKnQf){xIoxReRfKJ = true;}
      else if(KCEafOKnQf == oVfZJQQuVI){giIBUfRJNp = true;}
      if(dMIubWLLdV == ZWalzJUYpG){LINsQUIFgo = true;}
      else if(ZWalzJUYpG == dMIubWLLdV){TcJNDJDqob = true;}
      if(optAuULggw == gqwaiiTFjX){NTFqdGkEwF = true;}
      if(mIVfijJLxz == MgifgmpmIT){lRQyAWkzgg = true;}
      if(QVQpuCeQSs == DAizKkDsIk){MzJeCYyBuE = true;}
      while(gqwaiiTFjX == optAuULggw){kQVWZwcDLc = true;}
      while(MgifgmpmIT == MgifgmpmIT){zFSeXXaIWj = true;}
      while(DAizKkDsIk == DAizKkDsIk){dzMDCqdRRd = true;}
      if(LhCOqTFdqw == true){LhCOqTFdqw = false;}
      if(tFErTrntEL == true){tFErTrntEL = false;}
      if(SgQVDgIwPx == true){SgQVDgIwPx = false;}
      if(fZwzLdeUoN == true){fZwzLdeUoN = false;}
      if(hMuLZxupfR == true){hMuLZxupfR = false;}
      if(xIoxReRfKJ == true){xIoxReRfKJ = false;}
      if(LINsQUIFgo == true){LINsQUIFgo = false;}
      if(NTFqdGkEwF == true){NTFqdGkEwF = false;}
      if(lRQyAWkzgg == true){lRQyAWkzgg = false;}
      if(MzJeCYyBuE == true){MzJeCYyBuE = false;}
      if(opJpEdDxSL == true){opJpEdDxSL = false;}
      if(sMiFXsrPst == true){sMiFXsrPst = false;}
      if(iJYAcOJZnE == true){iJYAcOJZnE = false;}
      if(HjJqQuIasW == true){HjJqQuIasW = false;}
      if(TmfUnAPEHJ == true){TmfUnAPEHJ = false;}
      if(giIBUfRJNp == true){giIBUfRJNp = false;}
      if(TcJNDJDqob == true){TcJNDJDqob = false;}
      if(kQVWZwcDLc == true){kQVWZwcDLc = false;}
      if(zFSeXXaIWj == true){zFSeXXaIWj = false;}
      if(dzMDCqdRRd == true){dzMDCqdRRd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIDQOVHQXL
{ 
  void tXHlLimUnS()
  { 
      bool HaJOkWujIN = false;
      bool pMRhyBoEca = false;
      bool nYfYWDKgUf = false;
      bool mRLtfAriKE = false;
      bool EBbmEdpFQc = false;
      bool cFWirhujrg = false;
      bool MOOcaYBWCx = false;
      bool IFsYWmxsUr = false;
      bool MEQqDhubBx = false;
      bool FIpcrolyLf = false;
      bool cTDSTWLyMF = false;
      bool kBPzUHyWYs = false;
      bool cYVErAOPgg = false;
      bool AygnPsBxXg = false;
      bool VxPuMDrpIj = false;
      bool qOZRCDxyaT = false;
      bool HuReElTajb = false;
      bool GAzrXfJZqn = false;
      bool IXHwpkYPkL = false;
      bool uCWEYafkqa = false;
      string kgcFfQomgp;
      string LRJMyLsPyD;
      string mEdGwYerAh;
      string WBltgXYLXu;
      string bQQccLGFEy;
      string QEwdogDWIG;
      string lxmzTKfOfa;
      string mhqCbVmBdj;
      string SZnBQREHFz;
      string TCCQJddRIR;
      string frYcLiNtCS;
      string tCsYnMIlhC;
      string GXIgGkeasx;
      string rUrLEZAKph;
      string EKFlFRIdcx;
      string UrjGKIirWa;
      string DlAFaYKgUN;
      string LywzxwRWan;
      string bBxwbAkkBu;
      string qInOeRJAKg;
      if(kgcFfQomgp == frYcLiNtCS){HaJOkWujIN = true;}
      else if(frYcLiNtCS == kgcFfQomgp){cTDSTWLyMF = true;}
      if(LRJMyLsPyD == tCsYnMIlhC){pMRhyBoEca = true;}
      else if(tCsYnMIlhC == LRJMyLsPyD){kBPzUHyWYs = true;}
      if(mEdGwYerAh == GXIgGkeasx){nYfYWDKgUf = true;}
      else if(GXIgGkeasx == mEdGwYerAh){cYVErAOPgg = true;}
      if(WBltgXYLXu == rUrLEZAKph){mRLtfAriKE = true;}
      else if(rUrLEZAKph == WBltgXYLXu){AygnPsBxXg = true;}
      if(bQQccLGFEy == EKFlFRIdcx){EBbmEdpFQc = true;}
      else if(EKFlFRIdcx == bQQccLGFEy){VxPuMDrpIj = true;}
      if(QEwdogDWIG == UrjGKIirWa){cFWirhujrg = true;}
      else if(UrjGKIirWa == QEwdogDWIG){qOZRCDxyaT = true;}
      if(lxmzTKfOfa == DlAFaYKgUN){MOOcaYBWCx = true;}
      else if(DlAFaYKgUN == lxmzTKfOfa){HuReElTajb = true;}
      if(mhqCbVmBdj == LywzxwRWan){IFsYWmxsUr = true;}
      if(SZnBQREHFz == bBxwbAkkBu){MEQqDhubBx = true;}
      if(TCCQJddRIR == qInOeRJAKg){FIpcrolyLf = true;}
      while(LywzxwRWan == mhqCbVmBdj){GAzrXfJZqn = true;}
      while(bBxwbAkkBu == bBxwbAkkBu){IXHwpkYPkL = true;}
      while(qInOeRJAKg == qInOeRJAKg){uCWEYafkqa = true;}
      if(HaJOkWujIN == true){HaJOkWujIN = false;}
      if(pMRhyBoEca == true){pMRhyBoEca = false;}
      if(nYfYWDKgUf == true){nYfYWDKgUf = false;}
      if(mRLtfAriKE == true){mRLtfAriKE = false;}
      if(EBbmEdpFQc == true){EBbmEdpFQc = false;}
      if(cFWirhujrg == true){cFWirhujrg = false;}
      if(MOOcaYBWCx == true){MOOcaYBWCx = false;}
      if(IFsYWmxsUr == true){IFsYWmxsUr = false;}
      if(MEQqDhubBx == true){MEQqDhubBx = false;}
      if(FIpcrolyLf == true){FIpcrolyLf = false;}
      if(cTDSTWLyMF == true){cTDSTWLyMF = false;}
      if(kBPzUHyWYs == true){kBPzUHyWYs = false;}
      if(cYVErAOPgg == true){cYVErAOPgg = false;}
      if(AygnPsBxXg == true){AygnPsBxXg = false;}
      if(VxPuMDrpIj == true){VxPuMDrpIj = false;}
      if(qOZRCDxyaT == true){qOZRCDxyaT = false;}
      if(HuReElTajb == true){HuReElTajb = false;}
      if(GAzrXfJZqn == true){GAzrXfJZqn = false;}
      if(IXHwpkYPkL == true){IXHwpkYPkL = false;}
      if(uCWEYafkqa == true){uCWEYafkqa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKOZFAITHS
{ 
  void IrrIUykfGJ()
  { 
      bool cdecxnuVys = false;
      bool aVTCRihfdb = false;
      bool oaElunLdZW = false;
      bool VKAoYABkaf = false;
      bool kAmxUEKZxO = false;
      bool UiDGxBYrgJ = false;
      bool cRubXQVdcR = false;
      bool gwFxponHRp = false;
      bool clgLBmGsrW = false;
      bool aJDRDTELZE = false;
      bool ifwfgXcGQH = false;
      bool NRaqgqjiaj = false;
      bool JblGpXsnsW = false;
      bool jbhNGwoBec = false;
      bool JAcjIJhMjM = false;
      bool iUkotHtpoJ = false;
      bool eoMtXkjNjj = false;
      bool BiExaIyCxg = false;
      bool ofDgmOqrSz = false;
      bool BzLUxUniLW = false;
      string wYgLAOcaqS;
      string UTQzCIacxk;
      string garJDmXfIl;
      string hCRTwuNTOA;
      string qOhiDtbZDu;
      string PXpoxUgXHN;
      string qwSFjSBwCG;
      string tGOxsRsJGI;
      string LxcMVJMcVb;
      string OpMBJuucyj;
      string reWwAJJrwe;
      string bXQyCsTFiZ;
      string FYZarDtMnx;
      string WPKVPfafLM;
      string ATfqzpYNzP;
      string bosYeTFuEw;
      string PwEzIMNuiV;
      string SmsWZkribB;
      string egNXUgWlpw;
      string aebPxDPghm;
      if(wYgLAOcaqS == reWwAJJrwe){cdecxnuVys = true;}
      else if(reWwAJJrwe == wYgLAOcaqS){ifwfgXcGQH = true;}
      if(UTQzCIacxk == bXQyCsTFiZ){aVTCRihfdb = true;}
      else if(bXQyCsTFiZ == UTQzCIacxk){NRaqgqjiaj = true;}
      if(garJDmXfIl == FYZarDtMnx){oaElunLdZW = true;}
      else if(FYZarDtMnx == garJDmXfIl){JblGpXsnsW = true;}
      if(hCRTwuNTOA == WPKVPfafLM){VKAoYABkaf = true;}
      else if(WPKVPfafLM == hCRTwuNTOA){jbhNGwoBec = true;}
      if(qOhiDtbZDu == ATfqzpYNzP){kAmxUEKZxO = true;}
      else if(ATfqzpYNzP == qOhiDtbZDu){JAcjIJhMjM = true;}
      if(PXpoxUgXHN == bosYeTFuEw){UiDGxBYrgJ = true;}
      else if(bosYeTFuEw == PXpoxUgXHN){iUkotHtpoJ = true;}
      if(qwSFjSBwCG == PwEzIMNuiV){cRubXQVdcR = true;}
      else if(PwEzIMNuiV == qwSFjSBwCG){eoMtXkjNjj = true;}
      if(tGOxsRsJGI == SmsWZkribB){gwFxponHRp = true;}
      if(LxcMVJMcVb == egNXUgWlpw){clgLBmGsrW = true;}
      if(OpMBJuucyj == aebPxDPghm){aJDRDTELZE = true;}
      while(SmsWZkribB == tGOxsRsJGI){BiExaIyCxg = true;}
      while(egNXUgWlpw == egNXUgWlpw){ofDgmOqrSz = true;}
      while(aebPxDPghm == aebPxDPghm){BzLUxUniLW = true;}
      if(cdecxnuVys == true){cdecxnuVys = false;}
      if(aVTCRihfdb == true){aVTCRihfdb = false;}
      if(oaElunLdZW == true){oaElunLdZW = false;}
      if(VKAoYABkaf == true){VKAoYABkaf = false;}
      if(kAmxUEKZxO == true){kAmxUEKZxO = false;}
      if(UiDGxBYrgJ == true){UiDGxBYrgJ = false;}
      if(cRubXQVdcR == true){cRubXQVdcR = false;}
      if(gwFxponHRp == true){gwFxponHRp = false;}
      if(clgLBmGsrW == true){clgLBmGsrW = false;}
      if(aJDRDTELZE == true){aJDRDTELZE = false;}
      if(ifwfgXcGQH == true){ifwfgXcGQH = false;}
      if(NRaqgqjiaj == true){NRaqgqjiaj = false;}
      if(JblGpXsnsW == true){JblGpXsnsW = false;}
      if(jbhNGwoBec == true){jbhNGwoBec = false;}
      if(JAcjIJhMjM == true){JAcjIJhMjM = false;}
      if(iUkotHtpoJ == true){iUkotHtpoJ = false;}
      if(eoMtXkjNjj == true){eoMtXkjNjj = false;}
      if(BiExaIyCxg == true){BiExaIyCxg = false;}
      if(ofDgmOqrSz == true){ofDgmOqrSz = false;}
      if(BzLUxUniLW == true){BzLUxUniLW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGXYNKXUXN
{ 
  void AsepXnreAx()
  { 
      bool hQDKQLuLiM = false;
      bool nqeRrJcclK = false;
      bool CFcoPEqZMX = false;
      bool wugwpHmJpk = false;
      bool woxkMWAngA = false;
      bool CeymCbmNtM = false;
      bool TUzLPsJhaj = false;
      bool WTmBOMHrcs = false;
      bool DDrLUQxstN = false;
      bool TYOcRbolUS = false;
      bool MRMxdirxYo = false;
      bool TujAJQbnqz = false;
      bool wPnNPxEJil = false;
      bool WVWJgkpugk = false;
      bool YzUEsYnNTA = false;
      bool ABuVWwdzgg = false;
      bool ehNmSyXaTX = false;
      bool ZfGFawujTp = false;
      bool IpoilUaBlj = false;
      bool HqOAGplglu = false;
      string pEDiVxCMHM;
      string cRWuhAJYFe;
      string TyOhbPyeAc;
      string ApGAnPCPKx;
      string YwwdChZwBd;
      string fSBwLqpUHF;
      string zWLeMmLVGS;
      string ysNHGWCjes;
      string oCdVxgnJox;
      string ZhIEyBjRRP;
      string WDphflFton;
      string nFpNPwrohe;
      string yBfJrPkIJF;
      string lkSOWkMuoK;
      string bsUAIUqtoB;
      string IuilRUWfpP;
      string AwkjCDlaqd;
      string jxzWDEffBX;
      string XpTHxqBgxB;
      string NfFZKfIkyE;
      if(pEDiVxCMHM == WDphflFton){hQDKQLuLiM = true;}
      else if(WDphflFton == pEDiVxCMHM){MRMxdirxYo = true;}
      if(cRWuhAJYFe == nFpNPwrohe){nqeRrJcclK = true;}
      else if(nFpNPwrohe == cRWuhAJYFe){TujAJQbnqz = true;}
      if(TyOhbPyeAc == yBfJrPkIJF){CFcoPEqZMX = true;}
      else if(yBfJrPkIJF == TyOhbPyeAc){wPnNPxEJil = true;}
      if(ApGAnPCPKx == lkSOWkMuoK){wugwpHmJpk = true;}
      else if(lkSOWkMuoK == ApGAnPCPKx){WVWJgkpugk = true;}
      if(YwwdChZwBd == bsUAIUqtoB){woxkMWAngA = true;}
      else if(bsUAIUqtoB == YwwdChZwBd){YzUEsYnNTA = true;}
      if(fSBwLqpUHF == IuilRUWfpP){CeymCbmNtM = true;}
      else if(IuilRUWfpP == fSBwLqpUHF){ABuVWwdzgg = true;}
      if(zWLeMmLVGS == AwkjCDlaqd){TUzLPsJhaj = true;}
      else if(AwkjCDlaqd == zWLeMmLVGS){ehNmSyXaTX = true;}
      if(ysNHGWCjes == jxzWDEffBX){WTmBOMHrcs = true;}
      if(oCdVxgnJox == XpTHxqBgxB){DDrLUQxstN = true;}
      if(ZhIEyBjRRP == NfFZKfIkyE){TYOcRbolUS = true;}
      while(jxzWDEffBX == ysNHGWCjes){ZfGFawujTp = true;}
      while(XpTHxqBgxB == XpTHxqBgxB){IpoilUaBlj = true;}
      while(NfFZKfIkyE == NfFZKfIkyE){HqOAGplglu = true;}
      if(hQDKQLuLiM == true){hQDKQLuLiM = false;}
      if(nqeRrJcclK == true){nqeRrJcclK = false;}
      if(CFcoPEqZMX == true){CFcoPEqZMX = false;}
      if(wugwpHmJpk == true){wugwpHmJpk = false;}
      if(woxkMWAngA == true){woxkMWAngA = false;}
      if(CeymCbmNtM == true){CeymCbmNtM = false;}
      if(TUzLPsJhaj == true){TUzLPsJhaj = false;}
      if(WTmBOMHrcs == true){WTmBOMHrcs = false;}
      if(DDrLUQxstN == true){DDrLUQxstN = false;}
      if(TYOcRbolUS == true){TYOcRbolUS = false;}
      if(MRMxdirxYo == true){MRMxdirxYo = false;}
      if(TujAJQbnqz == true){TujAJQbnqz = false;}
      if(wPnNPxEJil == true){wPnNPxEJil = false;}
      if(WVWJgkpugk == true){WVWJgkpugk = false;}
      if(YzUEsYnNTA == true){YzUEsYnNTA = false;}
      if(ABuVWwdzgg == true){ABuVWwdzgg = false;}
      if(ehNmSyXaTX == true){ehNmSyXaTX = false;}
      if(ZfGFawujTp == true){ZfGFawujTp = false;}
      if(IpoilUaBlj == true){IpoilUaBlj = false;}
      if(HqOAGplglu == true){HqOAGplglu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDTDZXZXLA
{ 
  void QEGjKVDubW()
  { 
      bool NAxWDmSJGT = false;
      bool bYnOfhNBjG = false;
      bool QjdgSmnflV = false;
      bool xzocFqTBeP = false;
      bool NjNlJkZLWk = false;
      bool idYGAdWPDP = false;
      bool ymWkWbjLJn = false;
      bool OMWTrfWrWh = false;
      bool McJAlTZhbb = false;
      bool UDxOQaMcPh = false;
      bool AOChWWHFNT = false;
      bool HerVDVdWyC = false;
      bool BCihTLOHCR = false;
      bool TtcogyZadO = false;
      bool MUTHTpKbLu = false;
      bool xpdMfyeUOK = false;
      bool IzCwAMCDoE = false;
      bool wCriofhaNd = false;
      bool AlwHTcPPIh = false;
      bool SFMTGNRXHH = false;
      string pCDAnlCPom;
      string iPyuaLtfyS;
      string jRnTyLiyeQ;
      string rCUdXbIHrG;
      string hsPUXkxdTD;
      string RyOdJYOiCc;
      string DEjYuguUXz;
      string ClnqjpBSuM;
      string NEdbysmpTz;
      string NYFPDdJqZq;
      string pbGTBfKXtT;
      string WwnoOyZIZB;
      string sFBXkcfYmG;
      string gKrEWkxJZS;
      string iPwzcRkPAE;
      string DAQYxkaiiX;
      string zljmlLDjSd;
      string BPhGScIBtT;
      string rQXhDftTGl;
      string KOaCTxfIMR;
      if(pCDAnlCPom == pbGTBfKXtT){NAxWDmSJGT = true;}
      else if(pbGTBfKXtT == pCDAnlCPom){AOChWWHFNT = true;}
      if(iPyuaLtfyS == WwnoOyZIZB){bYnOfhNBjG = true;}
      else if(WwnoOyZIZB == iPyuaLtfyS){HerVDVdWyC = true;}
      if(jRnTyLiyeQ == sFBXkcfYmG){QjdgSmnflV = true;}
      else if(sFBXkcfYmG == jRnTyLiyeQ){BCihTLOHCR = true;}
      if(rCUdXbIHrG == gKrEWkxJZS){xzocFqTBeP = true;}
      else if(gKrEWkxJZS == rCUdXbIHrG){TtcogyZadO = true;}
      if(hsPUXkxdTD == iPwzcRkPAE){NjNlJkZLWk = true;}
      else if(iPwzcRkPAE == hsPUXkxdTD){MUTHTpKbLu = true;}
      if(RyOdJYOiCc == DAQYxkaiiX){idYGAdWPDP = true;}
      else if(DAQYxkaiiX == RyOdJYOiCc){xpdMfyeUOK = true;}
      if(DEjYuguUXz == zljmlLDjSd){ymWkWbjLJn = true;}
      else if(zljmlLDjSd == DEjYuguUXz){IzCwAMCDoE = true;}
      if(ClnqjpBSuM == BPhGScIBtT){OMWTrfWrWh = true;}
      if(NEdbysmpTz == rQXhDftTGl){McJAlTZhbb = true;}
      if(NYFPDdJqZq == KOaCTxfIMR){UDxOQaMcPh = true;}
      while(BPhGScIBtT == ClnqjpBSuM){wCriofhaNd = true;}
      while(rQXhDftTGl == rQXhDftTGl){AlwHTcPPIh = true;}
      while(KOaCTxfIMR == KOaCTxfIMR){SFMTGNRXHH = true;}
      if(NAxWDmSJGT == true){NAxWDmSJGT = false;}
      if(bYnOfhNBjG == true){bYnOfhNBjG = false;}
      if(QjdgSmnflV == true){QjdgSmnflV = false;}
      if(xzocFqTBeP == true){xzocFqTBeP = false;}
      if(NjNlJkZLWk == true){NjNlJkZLWk = false;}
      if(idYGAdWPDP == true){idYGAdWPDP = false;}
      if(ymWkWbjLJn == true){ymWkWbjLJn = false;}
      if(OMWTrfWrWh == true){OMWTrfWrWh = false;}
      if(McJAlTZhbb == true){McJAlTZhbb = false;}
      if(UDxOQaMcPh == true){UDxOQaMcPh = false;}
      if(AOChWWHFNT == true){AOChWWHFNT = false;}
      if(HerVDVdWyC == true){HerVDVdWyC = false;}
      if(BCihTLOHCR == true){BCihTLOHCR = false;}
      if(TtcogyZadO == true){TtcogyZadO = false;}
      if(MUTHTpKbLu == true){MUTHTpKbLu = false;}
      if(xpdMfyeUOK == true){xpdMfyeUOK = false;}
      if(IzCwAMCDoE == true){IzCwAMCDoE = false;}
      if(wCriofhaNd == true){wCriofhaNd = false;}
      if(AlwHTcPPIh == true){AlwHTcPPIh = false;}
      if(SFMTGNRXHH == true){SFMTGNRXHH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXMDMNKGLR
{ 
  void VlMGsEwmdV()
  { 
      bool WCjQcTAXQm = false;
      bool iRbqoOGQrg = false;
      bool AsqErmUpJk = false;
      bool ebdJnFLqgr = false;
      bool ftfazdHIVd = false;
      bool AntHadKeXp = false;
      bool zJOeHGnRDj = false;
      bool COjzAFMQFO = false;
      bool eLUfkqhViK = false;
      bool tgTpsVfASs = false;
      bool ppFlakEtGV = false;
      bool QtYJLmnhsQ = false;
      bool YRhsoUusGe = false;
      bool YMyMYnGiEz = false;
      bool lmONszIJeG = false;
      bool gxHBTXHMwF = false;
      bool pKmbxEwMkW = false;
      bool fFdsdkCUzp = false;
      bool MkOAxaEwrA = false;
      bool ftmzJbAmQo = false;
      string ZbQyBVdQIS;
      string RYsXCbEJEZ;
      string ZpHztzOdpV;
      string IhTenZOtYZ;
      string MjSfYJQaCX;
      string nLPUjiTQDB;
      string GzamKiFNjb;
      string MJjdNpXaaj;
      string hnbSgwSytE;
      string FxpXSMJeVo;
      string EDqZLdalGs;
      string LspTSSXHFN;
      string QGSeWOSMKB;
      string grEkfewCHD;
      string UfrBsLHWEA;
      string oBZIXxjMCw;
      string KOaFMSoEmn;
      string WUABrjORkK;
      string HwIKMfSwNh;
      string ujAKrGFmna;
      if(ZbQyBVdQIS == EDqZLdalGs){WCjQcTAXQm = true;}
      else if(EDqZLdalGs == ZbQyBVdQIS){ppFlakEtGV = true;}
      if(RYsXCbEJEZ == LspTSSXHFN){iRbqoOGQrg = true;}
      else if(LspTSSXHFN == RYsXCbEJEZ){QtYJLmnhsQ = true;}
      if(ZpHztzOdpV == QGSeWOSMKB){AsqErmUpJk = true;}
      else if(QGSeWOSMKB == ZpHztzOdpV){YRhsoUusGe = true;}
      if(IhTenZOtYZ == grEkfewCHD){ebdJnFLqgr = true;}
      else if(grEkfewCHD == IhTenZOtYZ){YMyMYnGiEz = true;}
      if(MjSfYJQaCX == UfrBsLHWEA){ftfazdHIVd = true;}
      else if(UfrBsLHWEA == MjSfYJQaCX){lmONszIJeG = true;}
      if(nLPUjiTQDB == oBZIXxjMCw){AntHadKeXp = true;}
      else if(oBZIXxjMCw == nLPUjiTQDB){gxHBTXHMwF = true;}
      if(GzamKiFNjb == KOaFMSoEmn){zJOeHGnRDj = true;}
      else if(KOaFMSoEmn == GzamKiFNjb){pKmbxEwMkW = true;}
      if(MJjdNpXaaj == WUABrjORkK){COjzAFMQFO = true;}
      if(hnbSgwSytE == HwIKMfSwNh){eLUfkqhViK = true;}
      if(FxpXSMJeVo == ujAKrGFmna){tgTpsVfASs = true;}
      while(WUABrjORkK == MJjdNpXaaj){fFdsdkCUzp = true;}
      while(HwIKMfSwNh == HwIKMfSwNh){MkOAxaEwrA = true;}
      while(ujAKrGFmna == ujAKrGFmna){ftmzJbAmQo = true;}
      if(WCjQcTAXQm == true){WCjQcTAXQm = false;}
      if(iRbqoOGQrg == true){iRbqoOGQrg = false;}
      if(AsqErmUpJk == true){AsqErmUpJk = false;}
      if(ebdJnFLqgr == true){ebdJnFLqgr = false;}
      if(ftfazdHIVd == true){ftfazdHIVd = false;}
      if(AntHadKeXp == true){AntHadKeXp = false;}
      if(zJOeHGnRDj == true){zJOeHGnRDj = false;}
      if(COjzAFMQFO == true){COjzAFMQFO = false;}
      if(eLUfkqhViK == true){eLUfkqhViK = false;}
      if(tgTpsVfASs == true){tgTpsVfASs = false;}
      if(ppFlakEtGV == true){ppFlakEtGV = false;}
      if(QtYJLmnhsQ == true){QtYJLmnhsQ = false;}
      if(YRhsoUusGe == true){YRhsoUusGe = false;}
      if(YMyMYnGiEz == true){YMyMYnGiEz = false;}
      if(lmONszIJeG == true){lmONszIJeG = false;}
      if(gxHBTXHMwF == true){gxHBTXHMwF = false;}
      if(pKmbxEwMkW == true){pKmbxEwMkW = false;}
      if(fFdsdkCUzp == true){fFdsdkCUzp = false;}
      if(MkOAxaEwrA == true){MkOAxaEwrA = false;}
      if(ftmzJbAmQo == true){ftmzJbAmQo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KFZTPRIIAW
{ 
  void CcnTcSDyhJ()
  { 
      bool tzeVjDnnLk = false;
      bool fajKdFYKaR = false;
      bool sWyLOLtjBU = false;
      bool ZzslhqCwdM = false;
      bool bdCrZNNqFO = false;
      bool mDmIdWBSGY = false;
      bool JDlqLghycm = false;
      bool CbfOoPTFkB = false;
      bool yDdlhVLkHL = false;
      bool pjoFDXqLgs = false;
      bool ePOSMKXXSO = false;
      bool CwhFZGZzJo = false;
      bool UxpQwSmZLR = false;
      bool XIXqVhnKZX = false;
      bool ymRsItCiex = false;
      bool yqBqYhYxWs = false;
      bool WxMBptXpjr = false;
      bool ROZlqgewIC = false;
      bool QEtNSfGgSn = false;
      bool JqnfAAaQCN = false;
      string SCfqFdmhqj;
      string AHNxiQoElM;
      string NMaxKNrPLl;
      string RFYZdBpuCh;
      string JFtrtwIIdP;
      string LikKNGbhfq;
      string kXWFRthmSh;
      string asBECHRhCN;
      string EikuZiTOMX;
      string ZHOLwlioaz;
      string NUpuoRggHF;
      string nseRlClaeh;
      string aTatISepIP;
      string XbHDAisoGI;
      string CmGHjfbwYs;
      string AIKrYstumV;
      string mpYqgLlbRD;
      string JwUWfmNSKb;
      string qhROPPROdG;
      string nxCjULNOZX;
      if(SCfqFdmhqj == NUpuoRggHF){tzeVjDnnLk = true;}
      else if(NUpuoRggHF == SCfqFdmhqj){ePOSMKXXSO = true;}
      if(AHNxiQoElM == nseRlClaeh){fajKdFYKaR = true;}
      else if(nseRlClaeh == AHNxiQoElM){CwhFZGZzJo = true;}
      if(NMaxKNrPLl == aTatISepIP){sWyLOLtjBU = true;}
      else if(aTatISepIP == NMaxKNrPLl){UxpQwSmZLR = true;}
      if(RFYZdBpuCh == XbHDAisoGI){ZzslhqCwdM = true;}
      else if(XbHDAisoGI == RFYZdBpuCh){XIXqVhnKZX = true;}
      if(JFtrtwIIdP == CmGHjfbwYs){bdCrZNNqFO = true;}
      else if(CmGHjfbwYs == JFtrtwIIdP){ymRsItCiex = true;}
      if(LikKNGbhfq == AIKrYstumV){mDmIdWBSGY = true;}
      else if(AIKrYstumV == LikKNGbhfq){yqBqYhYxWs = true;}
      if(kXWFRthmSh == mpYqgLlbRD){JDlqLghycm = true;}
      else if(mpYqgLlbRD == kXWFRthmSh){WxMBptXpjr = true;}
      if(asBECHRhCN == JwUWfmNSKb){CbfOoPTFkB = true;}
      if(EikuZiTOMX == qhROPPROdG){yDdlhVLkHL = true;}
      if(ZHOLwlioaz == nxCjULNOZX){pjoFDXqLgs = true;}
      while(JwUWfmNSKb == asBECHRhCN){ROZlqgewIC = true;}
      while(qhROPPROdG == qhROPPROdG){QEtNSfGgSn = true;}
      while(nxCjULNOZX == nxCjULNOZX){JqnfAAaQCN = true;}
      if(tzeVjDnnLk == true){tzeVjDnnLk = false;}
      if(fajKdFYKaR == true){fajKdFYKaR = false;}
      if(sWyLOLtjBU == true){sWyLOLtjBU = false;}
      if(ZzslhqCwdM == true){ZzslhqCwdM = false;}
      if(bdCrZNNqFO == true){bdCrZNNqFO = false;}
      if(mDmIdWBSGY == true){mDmIdWBSGY = false;}
      if(JDlqLghycm == true){JDlqLghycm = false;}
      if(CbfOoPTFkB == true){CbfOoPTFkB = false;}
      if(yDdlhVLkHL == true){yDdlhVLkHL = false;}
      if(pjoFDXqLgs == true){pjoFDXqLgs = false;}
      if(ePOSMKXXSO == true){ePOSMKXXSO = false;}
      if(CwhFZGZzJo == true){CwhFZGZzJo = false;}
      if(UxpQwSmZLR == true){UxpQwSmZLR = false;}
      if(XIXqVhnKZX == true){XIXqVhnKZX = false;}
      if(ymRsItCiex == true){ymRsItCiex = false;}
      if(yqBqYhYxWs == true){yqBqYhYxWs = false;}
      if(WxMBptXpjr == true){WxMBptXpjr = false;}
      if(ROZlqgewIC == true){ROZlqgewIC = false;}
      if(QEtNSfGgSn == true){QEtNSfGgSn = false;}
      if(JqnfAAaQCN == true){JqnfAAaQCN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGSZAHUSXN
{ 
  void qdHVnMVWpI()
  { 
      bool fCdbClKoee = false;
      bool phbGeVBgus = false;
      bool PkhpiJfXzx = false;
      bool fcooLXCXkM = false;
      bool QHbQpaThep = false;
      bool qdLZNuTmsr = false;
      bool GlpgyNsmuG = false;
      bool TcuhbHJQAI = false;
      bool pxsIFCROaQ = false;
      bool EOesGeRuSb = false;
      bool hfmXWOhcxF = false;
      bool lCmkBIrgaw = false;
      bool udLeBEyCbx = false;
      bool pNyXZJKUlq = false;
      bool ToQUeBbtqx = false;
      bool ljTWgDUHVR = false;
      bool PfBAOXDOKq = false;
      bool xWuibGMqAz = false;
      bool cDKdKGsbqW = false;
      bool oCzTamnQFG = false;
      string VxnWeujBhc;
      string kSzxCatbqx;
      string VitcXAGYbD;
      string YObYmunerq;
      string aNHLQDMNWz;
      string BGQYwlDKze;
      string nKYeEVpZKH;
      string lOizWHaiMU;
      string msCbCSyDcB;
      string rdfNDPncHt;
      string MmDONlXRBn;
      string KTxeruIwbl;
      string XlwIPHhVwG;
      string TybSHzonOQ;
      string ufCnpXgBUH;
      string HqBVWaptyF;
      string DBUuUMqeWr;
      string FUgLpqjISq;
      string agAnzbwGwf;
      string JuoJMsKGTd;
      if(VxnWeujBhc == MmDONlXRBn){fCdbClKoee = true;}
      else if(MmDONlXRBn == VxnWeujBhc){hfmXWOhcxF = true;}
      if(kSzxCatbqx == KTxeruIwbl){phbGeVBgus = true;}
      else if(KTxeruIwbl == kSzxCatbqx){lCmkBIrgaw = true;}
      if(VitcXAGYbD == XlwIPHhVwG){PkhpiJfXzx = true;}
      else if(XlwIPHhVwG == VitcXAGYbD){udLeBEyCbx = true;}
      if(YObYmunerq == TybSHzonOQ){fcooLXCXkM = true;}
      else if(TybSHzonOQ == YObYmunerq){pNyXZJKUlq = true;}
      if(aNHLQDMNWz == ufCnpXgBUH){QHbQpaThep = true;}
      else if(ufCnpXgBUH == aNHLQDMNWz){ToQUeBbtqx = true;}
      if(BGQYwlDKze == HqBVWaptyF){qdLZNuTmsr = true;}
      else if(HqBVWaptyF == BGQYwlDKze){ljTWgDUHVR = true;}
      if(nKYeEVpZKH == DBUuUMqeWr){GlpgyNsmuG = true;}
      else if(DBUuUMqeWr == nKYeEVpZKH){PfBAOXDOKq = true;}
      if(lOizWHaiMU == FUgLpqjISq){TcuhbHJQAI = true;}
      if(msCbCSyDcB == agAnzbwGwf){pxsIFCROaQ = true;}
      if(rdfNDPncHt == JuoJMsKGTd){EOesGeRuSb = true;}
      while(FUgLpqjISq == lOizWHaiMU){xWuibGMqAz = true;}
      while(agAnzbwGwf == agAnzbwGwf){cDKdKGsbqW = true;}
      while(JuoJMsKGTd == JuoJMsKGTd){oCzTamnQFG = true;}
      if(fCdbClKoee == true){fCdbClKoee = false;}
      if(phbGeVBgus == true){phbGeVBgus = false;}
      if(PkhpiJfXzx == true){PkhpiJfXzx = false;}
      if(fcooLXCXkM == true){fcooLXCXkM = false;}
      if(QHbQpaThep == true){QHbQpaThep = false;}
      if(qdLZNuTmsr == true){qdLZNuTmsr = false;}
      if(GlpgyNsmuG == true){GlpgyNsmuG = false;}
      if(TcuhbHJQAI == true){TcuhbHJQAI = false;}
      if(pxsIFCROaQ == true){pxsIFCROaQ = false;}
      if(EOesGeRuSb == true){EOesGeRuSb = false;}
      if(hfmXWOhcxF == true){hfmXWOhcxF = false;}
      if(lCmkBIrgaw == true){lCmkBIrgaw = false;}
      if(udLeBEyCbx == true){udLeBEyCbx = false;}
      if(pNyXZJKUlq == true){pNyXZJKUlq = false;}
      if(ToQUeBbtqx == true){ToQUeBbtqx = false;}
      if(ljTWgDUHVR == true){ljTWgDUHVR = false;}
      if(PfBAOXDOKq == true){PfBAOXDOKq = false;}
      if(xWuibGMqAz == true){xWuibGMqAz = false;}
      if(cDKdKGsbqW == true){cDKdKGsbqW = false;}
      if(oCzTamnQFG == true){oCzTamnQFG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLFVAZQBAB
{ 
  void ecZHRtUPKz()
  { 
      bool AFJeYOnLqa = false;
      bool CRdayoyFjw = false;
      bool FQZQcAdUWT = false;
      bool TWclnyMVVy = false;
      bool fSxBxGmrIQ = false;
      bool CraaHjerCY = false;
      bool jTnXHfoqmz = false;
      bool ccikPmSYSV = false;
      bool NlLGQbuBdD = false;
      bool STTwOMdZsR = false;
      bool QuFJnZIoLU = false;
      bool QGYfLxIhGf = false;
      bool jnNigIJlVC = false;
      bool IseBFRgCSp = false;
      bool SFoJmLumkR = false;
      bool EwSNgchVbe = false;
      bool QVTILXbXas = false;
      bool QFPPMdyEwU = false;
      bool NWBEyMZRTb = false;
      bool jKZmZwlgxO = false;
      string IhjYWfplVi;
      string JpLLXWTTWl;
      string zCjiJhzPcE;
      string ZKUgJMesNi;
      string TLzuGxkcVF;
      string goZopGxAPo;
      string gaJQJzVeBK;
      string qZGnRnCocM;
      string wVtXWkjepD;
      string OedYBsChlH;
      string aGbKNGhlWC;
      string EIXCrLglsX;
      string OpnyuLwhlY;
      string kTCUkptiJQ;
      string CxInyGHafp;
      string LQoNrjRcPC;
      string KAAxQkFCRB;
      string QxbcVQhzzn;
      string DVBuMUeobA;
      string YQSHFBxLWN;
      if(IhjYWfplVi == aGbKNGhlWC){AFJeYOnLqa = true;}
      else if(aGbKNGhlWC == IhjYWfplVi){QuFJnZIoLU = true;}
      if(JpLLXWTTWl == EIXCrLglsX){CRdayoyFjw = true;}
      else if(EIXCrLglsX == JpLLXWTTWl){QGYfLxIhGf = true;}
      if(zCjiJhzPcE == OpnyuLwhlY){FQZQcAdUWT = true;}
      else if(OpnyuLwhlY == zCjiJhzPcE){jnNigIJlVC = true;}
      if(ZKUgJMesNi == kTCUkptiJQ){TWclnyMVVy = true;}
      else if(kTCUkptiJQ == ZKUgJMesNi){IseBFRgCSp = true;}
      if(TLzuGxkcVF == CxInyGHafp){fSxBxGmrIQ = true;}
      else if(CxInyGHafp == TLzuGxkcVF){SFoJmLumkR = true;}
      if(goZopGxAPo == LQoNrjRcPC){CraaHjerCY = true;}
      else if(LQoNrjRcPC == goZopGxAPo){EwSNgchVbe = true;}
      if(gaJQJzVeBK == KAAxQkFCRB){jTnXHfoqmz = true;}
      else if(KAAxQkFCRB == gaJQJzVeBK){QVTILXbXas = true;}
      if(qZGnRnCocM == QxbcVQhzzn){ccikPmSYSV = true;}
      if(wVtXWkjepD == DVBuMUeobA){NlLGQbuBdD = true;}
      if(OedYBsChlH == YQSHFBxLWN){STTwOMdZsR = true;}
      while(QxbcVQhzzn == qZGnRnCocM){QFPPMdyEwU = true;}
      while(DVBuMUeobA == DVBuMUeobA){NWBEyMZRTb = true;}
      while(YQSHFBxLWN == YQSHFBxLWN){jKZmZwlgxO = true;}
      if(AFJeYOnLqa == true){AFJeYOnLqa = false;}
      if(CRdayoyFjw == true){CRdayoyFjw = false;}
      if(FQZQcAdUWT == true){FQZQcAdUWT = false;}
      if(TWclnyMVVy == true){TWclnyMVVy = false;}
      if(fSxBxGmrIQ == true){fSxBxGmrIQ = false;}
      if(CraaHjerCY == true){CraaHjerCY = false;}
      if(jTnXHfoqmz == true){jTnXHfoqmz = false;}
      if(ccikPmSYSV == true){ccikPmSYSV = false;}
      if(NlLGQbuBdD == true){NlLGQbuBdD = false;}
      if(STTwOMdZsR == true){STTwOMdZsR = false;}
      if(QuFJnZIoLU == true){QuFJnZIoLU = false;}
      if(QGYfLxIhGf == true){QGYfLxIhGf = false;}
      if(jnNigIJlVC == true){jnNigIJlVC = false;}
      if(IseBFRgCSp == true){IseBFRgCSp = false;}
      if(SFoJmLumkR == true){SFoJmLumkR = false;}
      if(EwSNgchVbe == true){EwSNgchVbe = false;}
      if(QVTILXbXas == true){QVTILXbXas = false;}
      if(QFPPMdyEwU == true){QFPPMdyEwU = false;}
      if(NWBEyMZRTb == true){NWBEyMZRTb = false;}
      if(jKZmZwlgxO == true){jKZmZwlgxO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMPSFOSEEC
{ 
  void gmPrlKBicL()
  { 
      bool byIEczMlUS = false;
      bool bdOBYwHOeh = false;
      bool gXlzOphhOB = false;
      bool cFBWOCTUUs = false;
      bool kMwmWjuRxT = false;
      bool sjNreDMIpm = false;
      bool QdXTpWcqlV = false;
      bool cltlxTbycd = false;
      bool tPjtIsqJrL = false;
      bool pKegbHocxA = false;
      bool GEfbqGobuK = false;
      bool aOfLsBsdKw = false;
      bool eTzZfRHNJp = false;
      bool ezBbXojIDB = false;
      bool EONgjadSna = false;
      bool NLRAUmFFwZ = false;
      bool yaRFfbMEnD = false;
      bool QkZIrQFRoE = false;
      bool mnZibTgAGj = false;
      bool jeMdDcwIBI = false;
      string GEnpuZobqS;
      string qAKNiqkfsq;
      string MGXJCkgRLY;
      string GCDZrcOTpf;
      string kgDWYmZwFw;
      string ZfCVYAfdnJ;
      string sXQSMoxjUF;
      string cQoNFeCAkP;
      string KjLPyZAgBq;
      string xjfglMQkKi;
      string ppbASJpnPt;
      string yfsXyIMATl;
      string nPicHrjIar;
      string NQpBYUILwo;
      string iLQGsQqHhd;
      string AQRXuZGyrZ;
      string YhMXfgorzc;
      string ABEeCbybjq;
      string BcZxrxzRGz;
      string OKSVQBzsaM;
      if(GEnpuZobqS == ppbASJpnPt){byIEczMlUS = true;}
      else if(ppbASJpnPt == GEnpuZobqS){GEfbqGobuK = true;}
      if(qAKNiqkfsq == yfsXyIMATl){bdOBYwHOeh = true;}
      else if(yfsXyIMATl == qAKNiqkfsq){aOfLsBsdKw = true;}
      if(MGXJCkgRLY == nPicHrjIar){gXlzOphhOB = true;}
      else if(nPicHrjIar == MGXJCkgRLY){eTzZfRHNJp = true;}
      if(GCDZrcOTpf == NQpBYUILwo){cFBWOCTUUs = true;}
      else if(NQpBYUILwo == GCDZrcOTpf){ezBbXojIDB = true;}
      if(kgDWYmZwFw == iLQGsQqHhd){kMwmWjuRxT = true;}
      else if(iLQGsQqHhd == kgDWYmZwFw){EONgjadSna = true;}
      if(ZfCVYAfdnJ == AQRXuZGyrZ){sjNreDMIpm = true;}
      else if(AQRXuZGyrZ == ZfCVYAfdnJ){NLRAUmFFwZ = true;}
      if(sXQSMoxjUF == YhMXfgorzc){QdXTpWcqlV = true;}
      else if(YhMXfgorzc == sXQSMoxjUF){yaRFfbMEnD = true;}
      if(cQoNFeCAkP == ABEeCbybjq){cltlxTbycd = true;}
      if(KjLPyZAgBq == BcZxrxzRGz){tPjtIsqJrL = true;}
      if(xjfglMQkKi == OKSVQBzsaM){pKegbHocxA = true;}
      while(ABEeCbybjq == cQoNFeCAkP){QkZIrQFRoE = true;}
      while(BcZxrxzRGz == BcZxrxzRGz){mnZibTgAGj = true;}
      while(OKSVQBzsaM == OKSVQBzsaM){jeMdDcwIBI = true;}
      if(byIEczMlUS == true){byIEczMlUS = false;}
      if(bdOBYwHOeh == true){bdOBYwHOeh = false;}
      if(gXlzOphhOB == true){gXlzOphhOB = false;}
      if(cFBWOCTUUs == true){cFBWOCTUUs = false;}
      if(kMwmWjuRxT == true){kMwmWjuRxT = false;}
      if(sjNreDMIpm == true){sjNreDMIpm = false;}
      if(QdXTpWcqlV == true){QdXTpWcqlV = false;}
      if(cltlxTbycd == true){cltlxTbycd = false;}
      if(tPjtIsqJrL == true){tPjtIsqJrL = false;}
      if(pKegbHocxA == true){pKegbHocxA = false;}
      if(GEfbqGobuK == true){GEfbqGobuK = false;}
      if(aOfLsBsdKw == true){aOfLsBsdKw = false;}
      if(eTzZfRHNJp == true){eTzZfRHNJp = false;}
      if(ezBbXojIDB == true){ezBbXojIDB = false;}
      if(EONgjadSna == true){EONgjadSna = false;}
      if(NLRAUmFFwZ == true){NLRAUmFFwZ = false;}
      if(yaRFfbMEnD == true){yaRFfbMEnD = false;}
      if(QkZIrQFRoE == true){QkZIrQFRoE = false;}
      if(mnZibTgAGj == true){mnZibTgAGj = false;}
      if(jeMdDcwIBI == true){jeMdDcwIBI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCJNVANYXN
{ 
  void wjRFoAXqfH()
  { 
      bool VGkHaCmUki = false;
      bool iGbmKippLF = false;
      bool seWCJHIGVP = false;
      bool lHFbiDffmp = false;
      bool uLkFPYTygA = false;
      bool wIBZzpihyT = false;
      bool tfzUwaBAEG = false;
      bool DKDUKhtRmk = false;
      bool mJZUTcGecr = false;
      bool UxgSuOLPIo = false;
      bool XSsZxkFfPQ = false;
      bool wQuNfkGdAT = false;
      bool TVXLlFcjZu = false;
      bool VdIyNUQzXi = false;
      bool XZPLwDCTmK = false;
      bool IhPoUBuhnr = false;
      bool IUGTuRIxAL = false;
      bool UHGRusFLPh = false;
      bool CIxPmmOScL = false;
      bool YhKeZDTwPe = false;
      string XACaRQBpIk;
      string MMetWkgXNB;
      string iQXRequeUh;
      string kTPzHLWmgt;
      string pSrGAlZUfL;
      string uFQEYGckwa;
      string UVUazrxemL;
      string OsqSKQYQQr;
      string QZyJlfCLaA;
      string ilpGYUxQHI;
      string ouhUxCOytH;
      string hLTEJuXLoT;
      string okElbbCjsp;
      string THJHCVrdMi;
      string QEQSRXRlwd;
      string wlanTDqwrU;
      string zdFEnZBLBn;
      string CsyFCkUkTE;
      string JQnOshgVny;
      string eukrjlzMer;
      if(XACaRQBpIk == ouhUxCOytH){VGkHaCmUki = true;}
      else if(ouhUxCOytH == XACaRQBpIk){XSsZxkFfPQ = true;}
      if(MMetWkgXNB == hLTEJuXLoT){iGbmKippLF = true;}
      else if(hLTEJuXLoT == MMetWkgXNB){wQuNfkGdAT = true;}
      if(iQXRequeUh == okElbbCjsp){seWCJHIGVP = true;}
      else if(okElbbCjsp == iQXRequeUh){TVXLlFcjZu = true;}
      if(kTPzHLWmgt == THJHCVrdMi){lHFbiDffmp = true;}
      else if(THJHCVrdMi == kTPzHLWmgt){VdIyNUQzXi = true;}
      if(pSrGAlZUfL == QEQSRXRlwd){uLkFPYTygA = true;}
      else if(QEQSRXRlwd == pSrGAlZUfL){XZPLwDCTmK = true;}
      if(uFQEYGckwa == wlanTDqwrU){wIBZzpihyT = true;}
      else if(wlanTDqwrU == uFQEYGckwa){IhPoUBuhnr = true;}
      if(UVUazrxemL == zdFEnZBLBn){tfzUwaBAEG = true;}
      else if(zdFEnZBLBn == UVUazrxemL){IUGTuRIxAL = true;}
      if(OsqSKQYQQr == CsyFCkUkTE){DKDUKhtRmk = true;}
      if(QZyJlfCLaA == JQnOshgVny){mJZUTcGecr = true;}
      if(ilpGYUxQHI == eukrjlzMer){UxgSuOLPIo = true;}
      while(CsyFCkUkTE == OsqSKQYQQr){UHGRusFLPh = true;}
      while(JQnOshgVny == JQnOshgVny){CIxPmmOScL = true;}
      while(eukrjlzMer == eukrjlzMer){YhKeZDTwPe = true;}
      if(VGkHaCmUki == true){VGkHaCmUki = false;}
      if(iGbmKippLF == true){iGbmKippLF = false;}
      if(seWCJHIGVP == true){seWCJHIGVP = false;}
      if(lHFbiDffmp == true){lHFbiDffmp = false;}
      if(uLkFPYTygA == true){uLkFPYTygA = false;}
      if(wIBZzpihyT == true){wIBZzpihyT = false;}
      if(tfzUwaBAEG == true){tfzUwaBAEG = false;}
      if(DKDUKhtRmk == true){DKDUKhtRmk = false;}
      if(mJZUTcGecr == true){mJZUTcGecr = false;}
      if(UxgSuOLPIo == true){UxgSuOLPIo = false;}
      if(XSsZxkFfPQ == true){XSsZxkFfPQ = false;}
      if(wQuNfkGdAT == true){wQuNfkGdAT = false;}
      if(TVXLlFcjZu == true){TVXLlFcjZu = false;}
      if(VdIyNUQzXi == true){VdIyNUQzXi = false;}
      if(XZPLwDCTmK == true){XZPLwDCTmK = false;}
      if(IhPoUBuhnr == true){IhPoUBuhnr = false;}
      if(IUGTuRIxAL == true){IUGTuRIxAL = false;}
      if(UHGRusFLPh == true){UHGRusFLPh = false;}
      if(CIxPmmOScL == true){CIxPmmOScL = false;}
      if(YhKeZDTwPe == true){YhKeZDTwPe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FERJUGDXYN
{ 
  void wJzMwAxBaA()
  { 
      bool SGVLMPCMpA = false;
      bool EYhcOYwqoD = false;
      bool HWDMtigJYQ = false;
      bool rdNbDqXuIL = false;
      bool FxaWmnpypm = false;
      bool cpAMCuDIQc = false;
      bool hsnYIZKFYX = false;
      bool AAidyJwfYF = false;
      bool siSlnBdBZH = false;
      bool mPdfdLJBOM = false;
      bool ckYRlbHWOr = false;
      bool zWiLjzZBjG = false;
      bool wJeQjkWDzl = false;
      bool AtRLbHJBAM = false;
      bool tHmhIQfSue = false;
      bool lIRIQSGHgB = false;
      bool EEWbrEFWib = false;
      bool oXBWMoWwIT = false;
      bool EEHUAqcIuI = false;
      bool ABUzIojKoE = false;
      string GycxkwpoBR;
      string bmdLxVDyED;
      string LLQHJrWCwV;
      string uJrOwaekit;
      string woqUNsVxzj;
      string FqMWEthUms;
      string ZmreVRuOPV;
      string pSOKHVUwtP;
      string VZDLQExUKB;
      string sJyoUIxLyu;
      string yGgctmbCPi;
      string ZlaWWAjfOR;
      string UZENcgUYoz;
      string XIxyRPraRd;
      string btFabGiaSU;
      string XQxfaYCTzM;
      string RCMPKRnbFH;
      string HINjpZTclV;
      string xsGUaHKQXr;
      string MXbELYhoPJ;
      if(GycxkwpoBR == yGgctmbCPi){SGVLMPCMpA = true;}
      else if(yGgctmbCPi == GycxkwpoBR){ckYRlbHWOr = true;}
      if(bmdLxVDyED == ZlaWWAjfOR){EYhcOYwqoD = true;}
      else if(ZlaWWAjfOR == bmdLxVDyED){zWiLjzZBjG = true;}
      if(LLQHJrWCwV == UZENcgUYoz){HWDMtigJYQ = true;}
      else if(UZENcgUYoz == LLQHJrWCwV){wJeQjkWDzl = true;}
      if(uJrOwaekit == XIxyRPraRd){rdNbDqXuIL = true;}
      else if(XIxyRPraRd == uJrOwaekit){AtRLbHJBAM = true;}
      if(woqUNsVxzj == btFabGiaSU){FxaWmnpypm = true;}
      else if(btFabGiaSU == woqUNsVxzj){tHmhIQfSue = true;}
      if(FqMWEthUms == XQxfaYCTzM){cpAMCuDIQc = true;}
      else if(XQxfaYCTzM == FqMWEthUms){lIRIQSGHgB = true;}
      if(ZmreVRuOPV == RCMPKRnbFH){hsnYIZKFYX = true;}
      else if(RCMPKRnbFH == ZmreVRuOPV){EEWbrEFWib = true;}
      if(pSOKHVUwtP == HINjpZTclV){AAidyJwfYF = true;}
      if(VZDLQExUKB == xsGUaHKQXr){siSlnBdBZH = true;}
      if(sJyoUIxLyu == MXbELYhoPJ){mPdfdLJBOM = true;}
      while(HINjpZTclV == pSOKHVUwtP){oXBWMoWwIT = true;}
      while(xsGUaHKQXr == xsGUaHKQXr){EEHUAqcIuI = true;}
      while(MXbELYhoPJ == MXbELYhoPJ){ABUzIojKoE = true;}
      if(SGVLMPCMpA == true){SGVLMPCMpA = false;}
      if(EYhcOYwqoD == true){EYhcOYwqoD = false;}
      if(HWDMtigJYQ == true){HWDMtigJYQ = false;}
      if(rdNbDqXuIL == true){rdNbDqXuIL = false;}
      if(FxaWmnpypm == true){FxaWmnpypm = false;}
      if(cpAMCuDIQc == true){cpAMCuDIQc = false;}
      if(hsnYIZKFYX == true){hsnYIZKFYX = false;}
      if(AAidyJwfYF == true){AAidyJwfYF = false;}
      if(siSlnBdBZH == true){siSlnBdBZH = false;}
      if(mPdfdLJBOM == true){mPdfdLJBOM = false;}
      if(ckYRlbHWOr == true){ckYRlbHWOr = false;}
      if(zWiLjzZBjG == true){zWiLjzZBjG = false;}
      if(wJeQjkWDzl == true){wJeQjkWDzl = false;}
      if(AtRLbHJBAM == true){AtRLbHJBAM = false;}
      if(tHmhIQfSue == true){tHmhIQfSue = false;}
      if(lIRIQSGHgB == true){lIRIQSGHgB = false;}
      if(EEWbrEFWib == true){EEWbrEFWib = false;}
      if(oXBWMoWwIT == true){oXBWMoWwIT = false;}
      if(EEHUAqcIuI == true){EEHUAqcIuI = false;}
      if(ABUzIojKoE == true){ABUzIojKoE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCPSXUXWAO
{ 
  void XoRLdrrHfz()
  { 
      bool NFLlDXFjlT = false;
      bool ofPEzhJpqs = false;
      bool RVNkcluqCg = false;
      bool VJEAYNTGky = false;
      bool cQbtSPsIby = false;
      bool EdRkdqqaJR = false;
      bool cNgEyebOfk = false;
      bool NCFsQAtTRN = false;
      bool slODbqqTWh = false;
      bool WsxSUOiWun = false;
      bool ndcpjBXYTc = false;
      bool xXJuYqydbH = false;
      bool nHqyOUFmXB = false;
      bool RWXdYOIXTa = false;
      bool SRztjzjBtd = false;
      bool PFtnzflebP = false;
      bool wkBRLazfWJ = false;
      bool iaJBnVHxNP = false;
      bool kErtlLbidr = false;
      bool bcwEehQhiJ = false;
      string cWSXFUTzHM;
      string zsuFEAmDSs;
      string JcHoyCRWVm;
      string fnKQyqOnBR;
      string rQOWNhjboG;
      string wJUTbzOdZD;
      string DwdTgKheHM;
      string lyCBAsOjbP;
      string RohPqWTqny;
      string bjOxNwmupC;
      string zFUbUxGSSh;
      string kdCJkOONbJ;
      string qqpJjBjEmE;
      string GStZQLTFus;
      string PAXGMxhELy;
      string gYSfKIPLqS;
      string NCfObRjcsY;
      string tISitpSiwm;
      string SesoWhANOI;
      string wINbfNUJeu;
      if(cWSXFUTzHM == zFUbUxGSSh){NFLlDXFjlT = true;}
      else if(zFUbUxGSSh == cWSXFUTzHM){ndcpjBXYTc = true;}
      if(zsuFEAmDSs == kdCJkOONbJ){ofPEzhJpqs = true;}
      else if(kdCJkOONbJ == zsuFEAmDSs){xXJuYqydbH = true;}
      if(JcHoyCRWVm == qqpJjBjEmE){RVNkcluqCg = true;}
      else if(qqpJjBjEmE == JcHoyCRWVm){nHqyOUFmXB = true;}
      if(fnKQyqOnBR == GStZQLTFus){VJEAYNTGky = true;}
      else if(GStZQLTFus == fnKQyqOnBR){RWXdYOIXTa = true;}
      if(rQOWNhjboG == PAXGMxhELy){cQbtSPsIby = true;}
      else if(PAXGMxhELy == rQOWNhjboG){SRztjzjBtd = true;}
      if(wJUTbzOdZD == gYSfKIPLqS){EdRkdqqaJR = true;}
      else if(gYSfKIPLqS == wJUTbzOdZD){PFtnzflebP = true;}
      if(DwdTgKheHM == NCfObRjcsY){cNgEyebOfk = true;}
      else if(NCfObRjcsY == DwdTgKheHM){wkBRLazfWJ = true;}
      if(lyCBAsOjbP == tISitpSiwm){NCFsQAtTRN = true;}
      if(RohPqWTqny == SesoWhANOI){slODbqqTWh = true;}
      if(bjOxNwmupC == wINbfNUJeu){WsxSUOiWun = true;}
      while(tISitpSiwm == lyCBAsOjbP){iaJBnVHxNP = true;}
      while(SesoWhANOI == SesoWhANOI){kErtlLbidr = true;}
      while(wINbfNUJeu == wINbfNUJeu){bcwEehQhiJ = true;}
      if(NFLlDXFjlT == true){NFLlDXFjlT = false;}
      if(ofPEzhJpqs == true){ofPEzhJpqs = false;}
      if(RVNkcluqCg == true){RVNkcluqCg = false;}
      if(VJEAYNTGky == true){VJEAYNTGky = false;}
      if(cQbtSPsIby == true){cQbtSPsIby = false;}
      if(EdRkdqqaJR == true){EdRkdqqaJR = false;}
      if(cNgEyebOfk == true){cNgEyebOfk = false;}
      if(NCFsQAtTRN == true){NCFsQAtTRN = false;}
      if(slODbqqTWh == true){slODbqqTWh = false;}
      if(WsxSUOiWun == true){WsxSUOiWun = false;}
      if(ndcpjBXYTc == true){ndcpjBXYTc = false;}
      if(xXJuYqydbH == true){xXJuYqydbH = false;}
      if(nHqyOUFmXB == true){nHqyOUFmXB = false;}
      if(RWXdYOIXTa == true){RWXdYOIXTa = false;}
      if(SRztjzjBtd == true){SRztjzjBtd = false;}
      if(PFtnzflebP == true){PFtnzflebP = false;}
      if(wkBRLazfWJ == true){wkBRLazfWJ = false;}
      if(iaJBnVHxNP == true){iaJBnVHxNP = false;}
      if(kErtlLbidr == true){kErtlLbidr = false;}
      if(bcwEehQhiJ == true){bcwEehQhiJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESJVEQJXMI
{ 
  void iUOnVRIyQn()
  { 
      bool MOnBkiszzP = false;
      bool aaetGkQGIN = false;
      bool oakdWtzfRa = false;
      bool XOjslFiuAE = false;
      bool TjQBqyaMKf = false;
      bool mTwXwkdKeq = false;
      bool iNhXqLpkIB = false;
      bool CVFDtFJimX = false;
      bool SlUlmESMxA = false;
      bool aXQJUGBsKe = false;
      bool HoEJcROrdp = false;
      bool buXGXxrwjm = false;
      bool sdnHadFuim = false;
      bool DQYHQcgKIV = false;
      bool oZiHYfAJkX = false;
      bool NFIWkdBxiz = false;
      bool MSIplLWPpt = false;
      bool PhmOxSufiu = false;
      bool cuKKYyHBWl = false;
      bool bjbIIWQrUN = false;
      string DspXfAqJHb;
      string XhlytmaxOk;
      string TBgsoKOkKH;
      string zXjKEBzaln;
      string FgqHfNIunC;
      string QVpGRBLxiU;
      string kGzzczybsr;
      string nALaelJZMa;
      string CSxHqchcrC;
      string pBrQDzhqdf;
      string OfBuNQJPbe;
      string rljHSRIqIz;
      string RUiqClHuWe;
      string ESugLVRBsZ;
      string TSBMKDRjyk;
      string pqieOtxKsa;
      string IOrwaYqCuw;
      string AHxifyTVfy;
      string UXxlnMjPRR;
      string YGHRQEZEll;
      if(DspXfAqJHb == OfBuNQJPbe){MOnBkiszzP = true;}
      else if(OfBuNQJPbe == DspXfAqJHb){HoEJcROrdp = true;}
      if(XhlytmaxOk == rljHSRIqIz){aaetGkQGIN = true;}
      else if(rljHSRIqIz == XhlytmaxOk){buXGXxrwjm = true;}
      if(TBgsoKOkKH == RUiqClHuWe){oakdWtzfRa = true;}
      else if(RUiqClHuWe == TBgsoKOkKH){sdnHadFuim = true;}
      if(zXjKEBzaln == ESugLVRBsZ){XOjslFiuAE = true;}
      else if(ESugLVRBsZ == zXjKEBzaln){DQYHQcgKIV = true;}
      if(FgqHfNIunC == TSBMKDRjyk){TjQBqyaMKf = true;}
      else if(TSBMKDRjyk == FgqHfNIunC){oZiHYfAJkX = true;}
      if(QVpGRBLxiU == pqieOtxKsa){mTwXwkdKeq = true;}
      else if(pqieOtxKsa == QVpGRBLxiU){NFIWkdBxiz = true;}
      if(kGzzczybsr == IOrwaYqCuw){iNhXqLpkIB = true;}
      else if(IOrwaYqCuw == kGzzczybsr){MSIplLWPpt = true;}
      if(nALaelJZMa == AHxifyTVfy){CVFDtFJimX = true;}
      if(CSxHqchcrC == UXxlnMjPRR){SlUlmESMxA = true;}
      if(pBrQDzhqdf == YGHRQEZEll){aXQJUGBsKe = true;}
      while(AHxifyTVfy == nALaelJZMa){PhmOxSufiu = true;}
      while(UXxlnMjPRR == UXxlnMjPRR){cuKKYyHBWl = true;}
      while(YGHRQEZEll == YGHRQEZEll){bjbIIWQrUN = true;}
      if(MOnBkiszzP == true){MOnBkiszzP = false;}
      if(aaetGkQGIN == true){aaetGkQGIN = false;}
      if(oakdWtzfRa == true){oakdWtzfRa = false;}
      if(XOjslFiuAE == true){XOjslFiuAE = false;}
      if(TjQBqyaMKf == true){TjQBqyaMKf = false;}
      if(mTwXwkdKeq == true){mTwXwkdKeq = false;}
      if(iNhXqLpkIB == true){iNhXqLpkIB = false;}
      if(CVFDtFJimX == true){CVFDtFJimX = false;}
      if(SlUlmESMxA == true){SlUlmESMxA = false;}
      if(aXQJUGBsKe == true){aXQJUGBsKe = false;}
      if(HoEJcROrdp == true){HoEJcROrdp = false;}
      if(buXGXxrwjm == true){buXGXxrwjm = false;}
      if(sdnHadFuim == true){sdnHadFuim = false;}
      if(DQYHQcgKIV == true){DQYHQcgKIV = false;}
      if(oZiHYfAJkX == true){oZiHYfAJkX = false;}
      if(NFIWkdBxiz == true){NFIWkdBxiz = false;}
      if(MSIplLWPpt == true){MSIplLWPpt = false;}
      if(PhmOxSufiu == true){PhmOxSufiu = false;}
      if(cuKKYyHBWl == true){cuKKYyHBWl = false;}
      if(bjbIIWQrUN == true){bjbIIWQrUN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFCQGXAWHU
{ 
  void ucRxueUzTW()
  { 
      bool NgIDKQXOuP = false;
      bool UxVBcJCkCw = false;
      bool gdKkjajurt = false;
      bool RJiHlhYDTe = false;
      bool KIOfcOGYpP = false;
      bool aknDUiWWTj = false;
      bool fcVAxLONOt = false;
      bool kzRWkXPeHU = false;
      bool ULFcSgUelC = false;
      bool LBiiyhmOhR = false;
      bool ArJuebSRRx = false;
      bool TqPzPUXrgQ = false;
      bool pibMijPiXD = false;
      bool jAwoTbCJyq = false;
      bool NDNohTkjTd = false;
      bool JthRbQPwMt = false;
      bool LjsNMTuZem = false;
      bool RNtoClVmeO = false;
      bool yfOttpSeNC = false;
      bool MFxDedKzbN = false;
      string cBKiRmZadz;
      string lTOVeVBZxL;
      string XzTbxjbJuO;
      string bRQQqEagZh;
      string bpeFyPsZep;
      string iTWFichhlg;
      string LPeOWUCxdZ;
      string uTAOigUNch;
      string pBeFfItLhO;
      string WrurWLLPid;
      string MwuEtOSHVB;
      string ITFEqJkYiO;
      string ZqPPDCXIrW;
      string VEezUtGaKQ;
      string olpfGDmqBN;
      string algUDVgeBr;
      string pKPyfEoFix;
      string CJNSYnAiJA;
      string PgHdwiWKuy;
      string MbZSZdVqAC;
      if(cBKiRmZadz == MwuEtOSHVB){NgIDKQXOuP = true;}
      else if(MwuEtOSHVB == cBKiRmZadz){ArJuebSRRx = true;}
      if(lTOVeVBZxL == ITFEqJkYiO){UxVBcJCkCw = true;}
      else if(ITFEqJkYiO == lTOVeVBZxL){TqPzPUXrgQ = true;}
      if(XzTbxjbJuO == ZqPPDCXIrW){gdKkjajurt = true;}
      else if(ZqPPDCXIrW == XzTbxjbJuO){pibMijPiXD = true;}
      if(bRQQqEagZh == VEezUtGaKQ){RJiHlhYDTe = true;}
      else if(VEezUtGaKQ == bRQQqEagZh){jAwoTbCJyq = true;}
      if(bpeFyPsZep == olpfGDmqBN){KIOfcOGYpP = true;}
      else if(olpfGDmqBN == bpeFyPsZep){NDNohTkjTd = true;}
      if(iTWFichhlg == algUDVgeBr){aknDUiWWTj = true;}
      else if(algUDVgeBr == iTWFichhlg){JthRbQPwMt = true;}
      if(LPeOWUCxdZ == pKPyfEoFix){fcVAxLONOt = true;}
      else if(pKPyfEoFix == LPeOWUCxdZ){LjsNMTuZem = true;}
      if(uTAOigUNch == CJNSYnAiJA){kzRWkXPeHU = true;}
      if(pBeFfItLhO == PgHdwiWKuy){ULFcSgUelC = true;}
      if(WrurWLLPid == MbZSZdVqAC){LBiiyhmOhR = true;}
      while(CJNSYnAiJA == uTAOigUNch){RNtoClVmeO = true;}
      while(PgHdwiWKuy == PgHdwiWKuy){yfOttpSeNC = true;}
      while(MbZSZdVqAC == MbZSZdVqAC){MFxDedKzbN = true;}
      if(NgIDKQXOuP == true){NgIDKQXOuP = false;}
      if(UxVBcJCkCw == true){UxVBcJCkCw = false;}
      if(gdKkjajurt == true){gdKkjajurt = false;}
      if(RJiHlhYDTe == true){RJiHlhYDTe = false;}
      if(KIOfcOGYpP == true){KIOfcOGYpP = false;}
      if(aknDUiWWTj == true){aknDUiWWTj = false;}
      if(fcVAxLONOt == true){fcVAxLONOt = false;}
      if(kzRWkXPeHU == true){kzRWkXPeHU = false;}
      if(ULFcSgUelC == true){ULFcSgUelC = false;}
      if(LBiiyhmOhR == true){LBiiyhmOhR = false;}
      if(ArJuebSRRx == true){ArJuebSRRx = false;}
      if(TqPzPUXrgQ == true){TqPzPUXrgQ = false;}
      if(pibMijPiXD == true){pibMijPiXD = false;}
      if(jAwoTbCJyq == true){jAwoTbCJyq = false;}
      if(NDNohTkjTd == true){NDNohTkjTd = false;}
      if(JthRbQPwMt == true){JthRbQPwMt = false;}
      if(LjsNMTuZem == true){LjsNMTuZem = false;}
      if(RNtoClVmeO == true){RNtoClVmeO = false;}
      if(yfOttpSeNC == true){yfOttpSeNC = false;}
      if(MFxDedKzbN == true){MFxDedKzbN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CENBGWCLXM
{ 
  void QOQmMckJck()
  { 
      bool ibZOLoDcya = false;
      bool gdVfbxtFEY = false;
      bool mGlFfTglkt = false;
      bool cQyXhrTeQe = false;
      bool QttfUUxIQm = false;
      bool CEFDAbpUhr = false;
      bool IRqDyPfyyi = false;
      bool dOoZIrMFjL = false;
      bool VXUyrYKtXF = false;
      bool CywYVyCphE = false;
      bool nzKgJmOftH = false;
      bool OjkWVjwsLY = false;
      bool FkarfeRPDJ = false;
      bool oWWeWVMmoE = false;
      bool JezPpSNZCk = false;
      bool CIdJzCYRAd = false;
      bool UybkRrMFzA = false;
      bool XIEHOZlKBN = false;
      bool QrNRHfrNfU = false;
      bool xtlKiLDOxy = false;
      string UXeALBaloq;
      string KnkYAtaggE;
      string IQwwBWVmos;
      string EanVjoTzQS;
      string GAuBdUReGM;
      string urYADDahyn;
      string enwwlizPoL;
      string abQOxHVuRf;
      string FqfbxLCmSf;
      string NkAcmSEyOu;
      string UBptlTbJDw;
      string hfPShnHUzZ;
      string fLxIyobnae;
      string DWgWKDAloc;
      string jrjVyhUgtz;
      string KiznOIEgww;
      string rnhYsKzsHe;
      string mVeVpmbaKQ;
      string TttbTTXrHC;
      string yToskwKKcm;
      if(UXeALBaloq == UBptlTbJDw){ibZOLoDcya = true;}
      else if(UBptlTbJDw == UXeALBaloq){nzKgJmOftH = true;}
      if(KnkYAtaggE == hfPShnHUzZ){gdVfbxtFEY = true;}
      else if(hfPShnHUzZ == KnkYAtaggE){OjkWVjwsLY = true;}
      if(IQwwBWVmos == fLxIyobnae){mGlFfTglkt = true;}
      else if(fLxIyobnae == IQwwBWVmos){FkarfeRPDJ = true;}
      if(EanVjoTzQS == DWgWKDAloc){cQyXhrTeQe = true;}
      else if(DWgWKDAloc == EanVjoTzQS){oWWeWVMmoE = true;}
      if(GAuBdUReGM == jrjVyhUgtz){QttfUUxIQm = true;}
      else if(jrjVyhUgtz == GAuBdUReGM){JezPpSNZCk = true;}
      if(urYADDahyn == KiznOIEgww){CEFDAbpUhr = true;}
      else if(KiznOIEgww == urYADDahyn){CIdJzCYRAd = true;}
      if(enwwlizPoL == rnhYsKzsHe){IRqDyPfyyi = true;}
      else if(rnhYsKzsHe == enwwlizPoL){UybkRrMFzA = true;}
      if(abQOxHVuRf == mVeVpmbaKQ){dOoZIrMFjL = true;}
      if(FqfbxLCmSf == TttbTTXrHC){VXUyrYKtXF = true;}
      if(NkAcmSEyOu == yToskwKKcm){CywYVyCphE = true;}
      while(mVeVpmbaKQ == abQOxHVuRf){XIEHOZlKBN = true;}
      while(TttbTTXrHC == TttbTTXrHC){QrNRHfrNfU = true;}
      while(yToskwKKcm == yToskwKKcm){xtlKiLDOxy = true;}
      if(ibZOLoDcya == true){ibZOLoDcya = false;}
      if(gdVfbxtFEY == true){gdVfbxtFEY = false;}
      if(mGlFfTglkt == true){mGlFfTglkt = false;}
      if(cQyXhrTeQe == true){cQyXhrTeQe = false;}
      if(QttfUUxIQm == true){QttfUUxIQm = false;}
      if(CEFDAbpUhr == true){CEFDAbpUhr = false;}
      if(IRqDyPfyyi == true){IRqDyPfyyi = false;}
      if(dOoZIrMFjL == true){dOoZIrMFjL = false;}
      if(VXUyrYKtXF == true){VXUyrYKtXF = false;}
      if(CywYVyCphE == true){CywYVyCphE = false;}
      if(nzKgJmOftH == true){nzKgJmOftH = false;}
      if(OjkWVjwsLY == true){OjkWVjwsLY = false;}
      if(FkarfeRPDJ == true){FkarfeRPDJ = false;}
      if(oWWeWVMmoE == true){oWWeWVMmoE = false;}
      if(JezPpSNZCk == true){JezPpSNZCk = false;}
      if(CIdJzCYRAd == true){CIdJzCYRAd = false;}
      if(UybkRrMFzA == true){UybkRrMFzA = false;}
      if(XIEHOZlKBN == true){XIEHOZlKBN = false;}
      if(QrNRHfrNfU == true){QrNRHfrNfU = false;}
      if(xtlKiLDOxy == true){xtlKiLDOxy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHFEAXQPLP
{ 
  void QyGrHYYfbt()
  { 
      bool HXJtgHPezw = false;
      bool DIMiXAaUEm = false;
      bool xLkrTcVUAN = false;
      bool BcgdqWrLHC = false;
      bool CGRPhBazIL = false;
      bool WGCwbumRaE = false;
      bool ktektaahrB = false;
      bool IPNBkptUKR = false;
      bool CVMnqtZjCu = false;
      bool jakCQHbfUG = false;
      bool ZrHHDGsALk = false;
      bool BRHICOhpsz = false;
      bool AqfxQgeKkd = false;
      bool ONzDrJOEkk = false;
      bool BYYRsSTbAB = false;
      bool YlmVGiMJpV = false;
      bool biPgWmREQr = false;
      bool AcFIyaRNDy = false;
      bool NCJjEcadwI = false;
      bool xFOOISJquF = false;
      string YAVzRmhfQC;
      string ePIWzlrgSA;
      string MJQLbloare;
      string ShBWmZPMRO;
      string rIHkkITKqG;
      string WbAtrPjKWf;
      string xHnliwNliY;
      string VePDIDBeaT;
      string RejkIqhHdW;
      string oFpkQkUVCn;
      string thbRjrLwln;
      string OFjCNSWCcq;
      string OGHLiQodmX;
      string ieblZjCRAP;
      string ekVoIjVmXx;
      string NRrLZnZPhT;
      string ChJOFjcxcc;
      string PFCNLcjRDy;
      string uCGoJRlQMk;
      string JmigMxbHjY;
      if(YAVzRmhfQC == thbRjrLwln){HXJtgHPezw = true;}
      else if(thbRjrLwln == YAVzRmhfQC){ZrHHDGsALk = true;}
      if(ePIWzlrgSA == OFjCNSWCcq){DIMiXAaUEm = true;}
      else if(OFjCNSWCcq == ePIWzlrgSA){BRHICOhpsz = true;}
      if(MJQLbloare == OGHLiQodmX){xLkrTcVUAN = true;}
      else if(OGHLiQodmX == MJQLbloare){AqfxQgeKkd = true;}
      if(ShBWmZPMRO == ieblZjCRAP){BcgdqWrLHC = true;}
      else if(ieblZjCRAP == ShBWmZPMRO){ONzDrJOEkk = true;}
      if(rIHkkITKqG == ekVoIjVmXx){CGRPhBazIL = true;}
      else if(ekVoIjVmXx == rIHkkITKqG){BYYRsSTbAB = true;}
      if(WbAtrPjKWf == NRrLZnZPhT){WGCwbumRaE = true;}
      else if(NRrLZnZPhT == WbAtrPjKWf){YlmVGiMJpV = true;}
      if(xHnliwNliY == ChJOFjcxcc){ktektaahrB = true;}
      else if(ChJOFjcxcc == xHnliwNliY){biPgWmREQr = true;}
      if(VePDIDBeaT == PFCNLcjRDy){IPNBkptUKR = true;}
      if(RejkIqhHdW == uCGoJRlQMk){CVMnqtZjCu = true;}
      if(oFpkQkUVCn == JmigMxbHjY){jakCQHbfUG = true;}
      while(PFCNLcjRDy == VePDIDBeaT){AcFIyaRNDy = true;}
      while(uCGoJRlQMk == uCGoJRlQMk){NCJjEcadwI = true;}
      while(JmigMxbHjY == JmigMxbHjY){xFOOISJquF = true;}
      if(HXJtgHPezw == true){HXJtgHPezw = false;}
      if(DIMiXAaUEm == true){DIMiXAaUEm = false;}
      if(xLkrTcVUAN == true){xLkrTcVUAN = false;}
      if(BcgdqWrLHC == true){BcgdqWrLHC = false;}
      if(CGRPhBazIL == true){CGRPhBazIL = false;}
      if(WGCwbumRaE == true){WGCwbumRaE = false;}
      if(ktektaahrB == true){ktektaahrB = false;}
      if(IPNBkptUKR == true){IPNBkptUKR = false;}
      if(CVMnqtZjCu == true){CVMnqtZjCu = false;}
      if(jakCQHbfUG == true){jakCQHbfUG = false;}
      if(ZrHHDGsALk == true){ZrHHDGsALk = false;}
      if(BRHICOhpsz == true){BRHICOhpsz = false;}
      if(AqfxQgeKkd == true){AqfxQgeKkd = false;}
      if(ONzDrJOEkk == true){ONzDrJOEkk = false;}
      if(BYYRsSTbAB == true){BYYRsSTbAB = false;}
      if(YlmVGiMJpV == true){YlmVGiMJpV = false;}
      if(biPgWmREQr == true){biPgWmREQr = false;}
      if(AcFIyaRNDy == true){AcFIyaRNDy = false;}
      if(NCJjEcadwI == true){NCJjEcadwI = false;}
      if(xFOOISJquF == true){xFOOISJquF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DEODWHFRWP
{ 
  void oaatjScSaB()
  { 
      bool ttSRHrXqmy = false;
      bool PinHbQPEWi = false;
      bool sQeACGyMYH = false;
      bool uPsRGhmjOu = false;
      bool jMfsfokqEN = false;
      bool CrfCTdPSPB = false;
      bool sKRfCzoWBt = false;
      bool depbzgjlTM = false;
      bool UHHLFDipxb = false;
      bool RTTMBZtApf = false;
      bool zOpKiWCEDm = false;
      bool tdzCflDGZz = false;
      bool PyYYbJKcZY = false;
      bool liumNGQxch = false;
      bool AemKhnURgO = false;
      bool VnZqPApQhY = false;
      bool LYddAKhLoZ = false;
      bool UGdqykLOpm = false;
      bool osuLDyJEXM = false;
      bool QzODWbAIJX = false;
      string BxSxLZPByO;
      string ttkyrXLfGZ;
      string dEcYhmBNox;
      string JSOgDQMCej;
      string zIDZircCQH;
      string BNIOlxTsOX;
      string XCMBEbeEtb;
      string LIBWaUACop;
      string KzwguuKAuG;
      string wTmGMwwBVH;
      string MXHnwsMlnQ;
      string wRDYNXGeGI;
      string QeJnfrUuKd;
      string YzghclrHkC;
      string iXMdJePOsn;
      string pQuMphOSIE;
      string XRaJqwjVua;
      string fysDZrSfeA;
      string bGCWmHDTqu;
      string XYzgdRxClM;
      if(BxSxLZPByO == MXHnwsMlnQ){ttSRHrXqmy = true;}
      else if(MXHnwsMlnQ == BxSxLZPByO){zOpKiWCEDm = true;}
      if(ttkyrXLfGZ == wRDYNXGeGI){PinHbQPEWi = true;}
      else if(wRDYNXGeGI == ttkyrXLfGZ){tdzCflDGZz = true;}
      if(dEcYhmBNox == QeJnfrUuKd){sQeACGyMYH = true;}
      else if(QeJnfrUuKd == dEcYhmBNox){PyYYbJKcZY = true;}
      if(JSOgDQMCej == YzghclrHkC){uPsRGhmjOu = true;}
      else if(YzghclrHkC == JSOgDQMCej){liumNGQxch = true;}
      if(zIDZircCQH == iXMdJePOsn){jMfsfokqEN = true;}
      else if(iXMdJePOsn == zIDZircCQH){AemKhnURgO = true;}
      if(BNIOlxTsOX == pQuMphOSIE){CrfCTdPSPB = true;}
      else if(pQuMphOSIE == BNIOlxTsOX){VnZqPApQhY = true;}
      if(XCMBEbeEtb == XRaJqwjVua){sKRfCzoWBt = true;}
      else if(XRaJqwjVua == XCMBEbeEtb){LYddAKhLoZ = true;}
      if(LIBWaUACop == fysDZrSfeA){depbzgjlTM = true;}
      if(KzwguuKAuG == bGCWmHDTqu){UHHLFDipxb = true;}
      if(wTmGMwwBVH == XYzgdRxClM){RTTMBZtApf = true;}
      while(fysDZrSfeA == LIBWaUACop){UGdqykLOpm = true;}
      while(bGCWmHDTqu == bGCWmHDTqu){osuLDyJEXM = true;}
      while(XYzgdRxClM == XYzgdRxClM){QzODWbAIJX = true;}
      if(ttSRHrXqmy == true){ttSRHrXqmy = false;}
      if(PinHbQPEWi == true){PinHbQPEWi = false;}
      if(sQeACGyMYH == true){sQeACGyMYH = false;}
      if(uPsRGhmjOu == true){uPsRGhmjOu = false;}
      if(jMfsfokqEN == true){jMfsfokqEN = false;}
      if(CrfCTdPSPB == true){CrfCTdPSPB = false;}
      if(sKRfCzoWBt == true){sKRfCzoWBt = false;}
      if(depbzgjlTM == true){depbzgjlTM = false;}
      if(UHHLFDipxb == true){UHHLFDipxb = false;}
      if(RTTMBZtApf == true){RTTMBZtApf = false;}
      if(zOpKiWCEDm == true){zOpKiWCEDm = false;}
      if(tdzCflDGZz == true){tdzCflDGZz = false;}
      if(PyYYbJKcZY == true){PyYYbJKcZY = false;}
      if(liumNGQxch == true){liumNGQxch = false;}
      if(AemKhnURgO == true){AemKhnURgO = false;}
      if(VnZqPApQhY == true){VnZqPApQhY = false;}
      if(LYddAKhLoZ == true){LYddAKhLoZ = false;}
      if(UGdqykLOpm == true){UGdqykLOpm = false;}
      if(osuLDyJEXM == true){osuLDyJEXM = false;}
      if(QzODWbAIJX == true){QzODWbAIJX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FUHYFEJFLW
{ 
  void oRNcWzqjmT()
  { 
      bool ebhaTXSTXA = false;
      bool BkxRqsIfef = false;
      bool rajitYpKGK = false;
      bool rAeFKxWxIX = false;
      bool HeVEjTJKMQ = false;
      bool pDlTYDryfu = false;
      bool hIMNHAFqHt = false;
      bool WLXGXMFezZ = false;
      bool OexoToOLgH = false;
      bool EXQMpzSIxi = false;
      bool ORDRtefeuM = false;
      bool yNzGfDKWsS = false;
      bool ltKzpyuKQY = false;
      bool sxhQLxafuo = false;
      bool JiPUIqYJgl = false;
      bool nuOewTHEbw = false;
      bool jUNWSBfiti = false;
      bool bebEIDdopz = false;
      bool ZkddjyhCTq = false;
      bool oWDzEnUrCH = false;
      string dIeYVPEdtk;
      string AbbXUSGfXW;
      string NDRdXfjQOC;
      string kAKSKkoZkm;
      string kiFVysJLgk;
      string lZVBuZqBBp;
      string fnOqAARINj;
      string dftjkdywfd;
      string VYidPLeIXj;
      string tmYuHxTNVy;
      string aAxxHGflPQ;
      string btVWUGFkbo;
      string VJkdopHycn;
      string JkZgCUakVJ;
      string frrGHzQCaA;
      string rikgcRPTIQ;
      string ygIbGqUnTz;
      string fTPRJcQeVp;
      string YFXcwazsEk;
      string FHcEKyjQzQ;
      if(dIeYVPEdtk == aAxxHGflPQ){ebhaTXSTXA = true;}
      else if(aAxxHGflPQ == dIeYVPEdtk){ORDRtefeuM = true;}
      if(AbbXUSGfXW == btVWUGFkbo){BkxRqsIfef = true;}
      else if(btVWUGFkbo == AbbXUSGfXW){yNzGfDKWsS = true;}
      if(NDRdXfjQOC == VJkdopHycn){rajitYpKGK = true;}
      else if(VJkdopHycn == NDRdXfjQOC){ltKzpyuKQY = true;}
      if(kAKSKkoZkm == JkZgCUakVJ){rAeFKxWxIX = true;}
      else if(JkZgCUakVJ == kAKSKkoZkm){sxhQLxafuo = true;}
      if(kiFVysJLgk == frrGHzQCaA){HeVEjTJKMQ = true;}
      else if(frrGHzQCaA == kiFVysJLgk){JiPUIqYJgl = true;}
      if(lZVBuZqBBp == rikgcRPTIQ){pDlTYDryfu = true;}
      else if(rikgcRPTIQ == lZVBuZqBBp){nuOewTHEbw = true;}
      if(fnOqAARINj == ygIbGqUnTz){hIMNHAFqHt = true;}
      else if(ygIbGqUnTz == fnOqAARINj){jUNWSBfiti = true;}
      if(dftjkdywfd == fTPRJcQeVp){WLXGXMFezZ = true;}
      if(VYidPLeIXj == YFXcwazsEk){OexoToOLgH = true;}
      if(tmYuHxTNVy == FHcEKyjQzQ){EXQMpzSIxi = true;}
      while(fTPRJcQeVp == dftjkdywfd){bebEIDdopz = true;}
      while(YFXcwazsEk == YFXcwazsEk){ZkddjyhCTq = true;}
      while(FHcEKyjQzQ == FHcEKyjQzQ){oWDzEnUrCH = true;}
      if(ebhaTXSTXA == true){ebhaTXSTXA = false;}
      if(BkxRqsIfef == true){BkxRqsIfef = false;}
      if(rajitYpKGK == true){rajitYpKGK = false;}
      if(rAeFKxWxIX == true){rAeFKxWxIX = false;}
      if(HeVEjTJKMQ == true){HeVEjTJKMQ = false;}
      if(pDlTYDryfu == true){pDlTYDryfu = false;}
      if(hIMNHAFqHt == true){hIMNHAFqHt = false;}
      if(WLXGXMFezZ == true){WLXGXMFezZ = false;}
      if(OexoToOLgH == true){OexoToOLgH = false;}
      if(EXQMpzSIxi == true){EXQMpzSIxi = false;}
      if(ORDRtefeuM == true){ORDRtefeuM = false;}
      if(yNzGfDKWsS == true){yNzGfDKWsS = false;}
      if(ltKzpyuKQY == true){ltKzpyuKQY = false;}
      if(sxhQLxafuo == true){sxhQLxafuo = false;}
      if(JiPUIqYJgl == true){JiPUIqYJgl = false;}
      if(nuOewTHEbw == true){nuOewTHEbw = false;}
      if(jUNWSBfiti == true){jUNWSBfiti = false;}
      if(bebEIDdopz == true){bebEIDdopz = false;}
      if(ZkddjyhCTq == true){ZkddjyhCTq = false;}
      if(oWDzEnUrCH == true){oWDzEnUrCH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQBWEAGHXU
{ 
  void ZlewQEkqTB()
  { 
      bool yVhKKWgajn = false;
      bool rERhGtgzrP = false;
      bool VZgchUjgUy = false;
      bool muYDjixekI = false;
      bool fhmCtsYXlD = false;
      bool phJiYXnFbp = false;
      bool lzFlBwfNxW = false;
      bool xCNjjnmehn = false;
      bool wMtRIFlpeM = false;
      bool trCuVgbABy = false;
      bool NKZPGnTYzj = false;
      bool jJXnsZFmcu = false;
      bool KoikbFzROC = false;
      bool LldjalleLT = false;
      bool kMqtbkUOBu = false;
      bool aoXFmXanmB = false;
      bool nBKwYyemMH = false;
      bool maaJKyynJp = false;
      bool jjQSbWOYwD = false;
      bool KyqKeiBtVd = false;
      string QWWybnqxWr;
      string wnKJGOrnQW;
      string stqtQNVNyC;
      string cKZgcEuXKI;
      string EkGmpaHWwf;
      string YeViGVfchN;
      string SdyUOkNcgC;
      string STcISHnDEo;
      string GyQScxopaH;
      string XSpxpZmkYE;
      string MeptMECNQy;
      string gbXrHTMfqR;
      string wXBYdAdfRr;
      string UCezbaHWFY;
      string tbZcZutypV;
      string NHtHIocRQM;
      string aWuXdexXPf;
      string LpZSWTxYzh;
      string FfoweNIXqm;
      string ypFsxXgCzu;
      if(QWWybnqxWr == MeptMECNQy){yVhKKWgajn = true;}
      else if(MeptMECNQy == QWWybnqxWr){NKZPGnTYzj = true;}
      if(wnKJGOrnQW == gbXrHTMfqR){rERhGtgzrP = true;}
      else if(gbXrHTMfqR == wnKJGOrnQW){jJXnsZFmcu = true;}
      if(stqtQNVNyC == wXBYdAdfRr){VZgchUjgUy = true;}
      else if(wXBYdAdfRr == stqtQNVNyC){KoikbFzROC = true;}
      if(cKZgcEuXKI == UCezbaHWFY){muYDjixekI = true;}
      else if(UCezbaHWFY == cKZgcEuXKI){LldjalleLT = true;}
      if(EkGmpaHWwf == tbZcZutypV){fhmCtsYXlD = true;}
      else if(tbZcZutypV == EkGmpaHWwf){kMqtbkUOBu = true;}
      if(YeViGVfchN == NHtHIocRQM){phJiYXnFbp = true;}
      else if(NHtHIocRQM == YeViGVfchN){aoXFmXanmB = true;}
      if(SdyUOkNcgC == aWuXdexXPf){lzFlBwfNxW = true;}
      else if(aWuXdexXPf == SdyUOkNcgC){nBKwYyemMH = true;}
      if(STcISHnDEo == LpZSWTxYzh){xCNjjnmehn = true;}
      if(GyQScxopaH == FfoweNIXqm){wMtRIFlpeM = true;}
      if(XSpxpZmkYE == ypFsxXgCzu){trCuVgbABy = true;}
      while(LpZSWTxYzh == STcISHnDEo){maaJKyynJp = true;}
      while(FfoweNIXqm == FfoweNIXqm){jjQSbWOYwD = true;}
      while(ypFsxXgCzu == ypFsxXgCzu){KyqKeiBtVd = true;}
      if(yVhKKWgajn == true){yVhKKWgajn = false;}
      if(rERhGtgzrP == true){rERhGtgzrP = false;}
      if(VZgchUjgUy == true){VZgchUjgUy = false;}
      if(muYDjixekI == true){muYDjixekI = false;}
      if(fhmCtsYXlD == true){fhmCtsYXlD = false;}
      if(phJiYXnFbp == true){phJiYXnFbp = false;}
      if(lzFlBwfNxW == true){lzFlBwfNxW = false;}
      if(xCNjjnmehn == true){xCNjjnmehn = false;}
      if(wMtRIFlpeM == true){wMtRIFlpeM = false;}
      if(trCuVgbABy == true){trCuVgbABy = false;}
      if(NKZPGnTYzj == true){NKZPGnTYzj = false;}
      if(jJXnsZFmcu == true){jJXnsZFmcu = false;}
      if(KoikbFzROC == true){KoikbFzROC = false;}
      if(LldjalleLT == true){LldjalleLT = false;}
      if(kMqtbkUOBu == true){kMqtbkUOBu = false;}
      if(aoXFmXanmB == true){aoXFmXanmB = false;}
      if(nBKwYyemMH == true){nBKwYyemMH = false;}
      if(maaJKyynJp == true){maaJKyynJp = false;}
      if(jjQSbWOYwD == true){jjQSbWOYwD = false;}
      if(KyqKeiBtVd == true){KyqKeiBtVd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XFGQFHQIUB
{ 
  void ahreuNsump()
  { 
      bool AejOIXgqJS = false;
      bool EXGmnmwEgc = false;
      bool GdxWkBkrSh = false;
      bool osqWBZphYo = false;
      bool JkxAeGODfV = false;
      bool qGRGqWhMdH = false;
      bool lnXadLgikO = false;
      bool wOerSVfwqe = false;
      bool lhMwpibjed = false;
      bool rcEQDVMWWT = false;
      bool YfSQZcaYnV = false;
      bool qkUyVEabjt = false;
      bool jxDGWTKOnx = false;
      bool IIYXFGOuWN = false;
      bool HCwImGIFuz = false;
      bool tkmcjbbLtF = false;
      bool SMkpNhLxsO = false;
      bool ofEVlhAtSP = false;
      bool KESoDWVwmd = false;
      bool dDAQtuQGuF = false;
      string SDTpOREnYS;
      string ASERDLfPDw;
      string IbJMlRWlFa;
      string PGeSCEIiTr;
      string aCPmJWMtbx;
      string aPKdKqtHEx;
      string uRhyDsnkOy;
      string CwwKVFMVCP;
      string EbJHAAwBIL;
      string JBeVxIUQiP;
      string ibedtdSzHF;
      string dXEnrSIZyD;
      string xlcDnBQZMM;
      string kummgcwfNV;
      string gxsDglwqde;
      string AtSfSwybos;
      string MrltTikRHP;
      string VbMbWzrZVC;
      string EZwhMqbHTj;
      string dUpTJnKziy;
      if(SDTpOREnYS == ibedtdSzHF){AejOIXgqJS = true;}
      else if(ibedtdSzHF == SDTpOREnYS){YfSQZcaYnV = true;}
      if(ASERDLfPDw == dXEnrSIZyD){EXGmnmwEgc = true;}
      else if(dXEnrSIZyD == ASERDLfPDw){qkUyVEabjt = true;}
      if(IbJMlRWlFa == xlcDnBQZMM){GdxWkBkrSh = true;}
      else if(xlcDnBQZMM == IbJMlRWlFa){jxDGWTKOnx = true;}
      if(PGeSCEIiTr == kummgcwfNV){osqWBZphYo = true;}
      else if(kummgcwfNV == PGeSCEIiTr){IIYXFGOuWN = true;}
      if(aCPmJWMtbx == gxsDglwqde){JkxAeGODfV = true;}
      else if(gxsDglwqde == aCPmJWMtbx){HCwImGIFuz = true;}
      if(aPKdKqtHEx == AtSfSwybos){qGRGqWhMdH = true;}
      else if(AtSfSwybos == aPKdKqtHEx){tkmcjbbLtF = true;}
      if(uRhyDsnkOy == MrltTikRHP){lnXadLgikO = true;}
      else if(MrltTikRHP == uRhyDsnkOy){SMkpNhLxsO = true;}
      if(CwwKVFMVCP == VbMbWzrZVC){wOerSVfwqe = true;}
      if(EbJHAAwBIL == EZwhMqbHTj){lhMwpibjed = true;}
      if(JBeVxIUQiP == dUpTJnKziy){rcEQDVMWWT = true;}
      while(VbMbWzrZVC == CwwKVFMVCP){ofEVlhAtSP = true;}
      while(EZwhMqbHTj == EZwhMqbHTj){KESoDWVwmd = true;}
      while(dUpTJnKziy == dUpTJnKziy){dDAQtuQGuF = true;}
      if(AejOIXgqJS == true){AejOIXgqJS = false;}
      if(EXGmnmwEgc == true){EXGmnmwEgc = false;}
      if(GdxWkBkrSh == true){GdxWkBkrSh = false;}
      if(osqWBZphYo == true){osqWBZphYo = false;}
      if(JkxAeGODfV == true){JkxAeGODfV = false;}
      if(qGRGqWhMdH == true){qGRGqWhMdH = false;}
      if(lnXadLgikO == true){lnXadLgikO = false;}
      if(wOerSVfwqe == true){wOerSVfwqe = false;}
      if(lhMwpibjed == true){lhMwpibjed = false;}
      if(rcEQDVMWWT == true){rcEQDVMWWT = false;}
      if(YfSQZcaYnV == true){YfSQZcaYnV = false;}
      if(qkUyVEabjt == true){qkUyVEabjt = false;}
      if(jxDGWTKOnx == true){jxDGWTKOnx = false;}
      if(IIYXFGOuWN == true){IIYXFGOuWN = false;}
      if(HCwImGIFuz == true){HCwImGIFuz = false;}
      if(tkmcjbbLtF == true){tkmcjbbLtF = false;}
      if(SMkpNhLxsO == true){SMkpNhLxsO = false;}
      if(ofEVlhAtSP == true){ofEVlhAtSP = false;}
      if(KESoDWVwmd == true){KESoDWVwmd = false;}
      if(dDAQtuQGuF == true){dDAQtuQGuF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEVHOAEXOE
{ 
  void ANeArATrKW()
  { 
      bool kyViFTAJxl = false;
      bool uHXIInbGGI = false;
      bool LWKlSGYnfg = false;
      bool ocnQOPEzMc = false;
      bool XQUqSuHUXA = false;
      bool aJQkqOniQy = false;
      bool tMcPxSTHss = false;
      bool jbtckuBSTW = false;
      bool zDPfGfLDYA = false;
      bool aUiOiKmFtA = false;
      bool bAbeQyOnzw = false;
      bool MVPsypxxIQ = false;
      bool HPhrROseta = false;
      bool HwYTuybjPI = false;
      bool QWEcnFFoPr = false;
      bool NpwcsLSiMB = false;
      bool EitXnPwwyA = false;
      bool OMgAAjLFEM = false;
      bool JEPBNRAuai = false;
      bool fsXNDgcfnX = false;
      string useXPOBtqp;
      string nVbbTKIrHA;
      string fuZMdFZquF;
      string bUxQhfNbgs;
      string VrntFwLxVT;
      string qMxAOzSRtK;
      string oKzlOSXLsm;
      string wfLNdmHeHh;
      string tcUaOPXxCh;
      string NwhVELsCfl;
      string XzDhXLAiVa;
      string rmJLQLoXXy;
      string taJKZAxoJS;
      string sFzVKtYlDC;
      string OoaapZlWFr;
      string VVegrwpsIW;
      string OLYDglnnAV;
      string mCUUjFAhUA;
      string NZiRwXaRdO;
      string DfdgnCPXsD;
      if(useXPOBtqp == XzDhXLAiVa){kyViFTAJxl = true;}
      else if(XzDhXLAiVa == useXPOBtqp){bAbeQyOnzw = true;}
      if(nVbbTKIrHA == rmJLQLoXXy){uHXIInbGGI = true;}
      else if(rmJLQLoXXy == nVbbTKIrHA){MVPsypxxIQ = true;}
      if(fuZMdFZquF == taJKZAxoJS){LWKlSGYnfg = true;}
      else if(taJKZAxoJS == fuZMdFZquF){HPhrROseta = true;}
      if(bUxQhfNbgs == sFzVKtYlDC){ocnQOPEzMc = true;}
      else if(sFzVKtYlDC == bUxQhfNbgs){HwYTuybjPI = true;}
      if(VrntFwLxVT == OoaapZlWFr){XQUqSuHUXA = true;}
      else if(OoaapZlWFr == VrntFwLxVT){QWEcnFFoPr = true;}
      if(qMxAOzSRtK == VVegrwpsIW){aJQkqOniQy = true;}
      else if(VVegrwpsIW == qMxAOzSRtK){NpwcsLSiMB = true;}
      if(oKzlOSXLsm == OLYDglnnAV){tMcPxSTHss = true;}
      else if(OLYDglnnAV == oKzlOSXLsm){EitXnPwwyA = true;}
      if(wfLNdmHeHh == mCUUjFAhUA){jbtckuBSTW = true;}
      if(tcUaOPXxCh == NZiRwXaRdO){zDPfGfLDYA = true;}
      if(NwhVELsCfl == DfdgnCPXsD){aUiOiKmFtA = true;}
      while(mCUUjFAhUA == wfLNdmHeHh){OMgAAjLFEM = true;}
      while(NZiRwXaRdO == NZiRwXaRdO){JEPBNRAuai = true;}
      while(DfdgnCPXsD == DfdgnCPXsD){fsXNDgcfnX = true;}
      if(kyViFTAJxl == true){kyViFTAJxl = false;}
      if(uHXIInbGGI == true){uHXIInbGGI = false;}
      if(LWKlSGYnfg == true){LWKlSGYnfg = false;}
      if(ocnQOPEzMc == true){ocnQOPEzMc = false;}
      if(XQUqSuHUXA == true){XQUqSuHUXA = false;}
      if(aJQkqOniQy == true){aJQkqOniQy = false;}
      if(tMcPxSTHss == true){tMcPxSTHss = false;}
      if(jbtckuBSTW == true){jbtckuBSTW = false;}
      if(zDPfGfLDYA == true){zDPfGfLDYA = false;}
      if(aUiOiKmFtA == true){aUiOiKmFtA = false;}
      if(bAbeQyOnzw == true){bAbeQyOnzw = false;}
      if(MVPsypxxIQ == true){MVPsypxxIQ = false;}
      if(HPhrROseta == true){HPhrROseta = false;}
      if(HwYTuybjPI == true){HwYTuybjPI = false;}
      if(QWEcnFFoPr == true){QWEcnFFoPr = false;}
      if(NpwcsLSiMB == true){NpwcsLSiMB = false;}
      if(EitXnPwwyA == true){EitXnPwwyA = false;}
      if(OMgAAjLFEM == true){OMgAAjLFEM = false;}
      if(JEPBNRAuai == true){JEPBNRAuai = false;}
      if(fsXNDgcfnX == true){fsXNDgcfnX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDXQRHOPSH
{ 
  void SUBQPoTaem()
  { 
      bool zqroqAYMRJ = false;
      bool acUeVLQcLV = false;
      bool JPjRdZsecy = false;
      bool zcDiNmonQU = false;
      bool bYRGasLEBZ = false;
      bool ONXbEjHaKR = false;
      bool GsiSKyYlRh = false;
      bool WcMpskxcpk = false;
      bool OodDjlEbed = false;
      bool fOcyOhoywc = false;
      bool UYlSCkAghT = false;
      bool ldjZDQPfiY = false;
      bool sxHnBIzNbK = false;
      bool uzfNQoCLAy = false;
      bool kWsKrCdDux = false;
      bool SJPXjWRyQt = false;
      bool kmFWYlxWIN = false;
      bool NEfjmVEwwz = false;
      bool dwSdrljIds = false;
      bool WEtFMyRVlF = false;
      string xtlSfOObZF;
      string MtaglpzzAH;
      string BJemCgebDQ;
      string LYQpGtJkon;
      string WYcuEuiCuG;
      string AXERYnPzQy;
      string ilXJsmckaq;
      string gNJLjbfihH;
      string ybfxQnUzQR;
      string eJUpFjBTCR;
      string RybEYlNrgx;
      string HfQIAGFarF;
      string RdUILXsSGA;
      string aMgQozAbXd;
      string ZbRTKyrLpy;
      string daaxzmdTrB;
      string stlgVuzATA;
      string GdCOepMByM;
      string egcIVAkjQB;
      string VgjWkfpjxO;
      if(xtlSfOObZF == RybEYlNrgx){zqroqAYMRJ = true;}
      else if(RybEYlNrgx == xtlSfOObZF){UYlSCkAghT = true;}
      if(MtaglpzzAH == HfQIAGFarF){acUeVLQcLV = true;}
      else if(HfQIAGFarF == MtaglpzzAH){ldjZDQPfiY = true;}
      if(BJemCgebDQ == RdUILXsSGA){JPjRdZsecy = true;}
      else if(RdUILXsSGA == BJemCgebDQ){sxHnBIzNbK = true;}
      if(LYQpGtJkon == aMgQozAbXd){zcDiNmonQU = true;}
      else if(aMgQozAbXd == LYQpGtJkon){uzfNQoCLAy = true;}
      if(WYcuEuiCuG == ZbRTKyrLpy){bYRGasLEBZ = true;}
      else if(ZbRTKyrLpy == WYcuEuiCuG){kWsKrCdDux = true;}
      if(AXERYnPzQy == daaxzmdTrB){ONXbEjHaKR = true;}
      else if(daaxzmdTrB == AXERYnPzQy){SJPXjWRyQt = true;}
      if(ilXJsmckaq == stlgVuzATA){GsiSKyYlRh = true;}
      else if(stlgVuzATA == ilXJsmckaq){kmFWYlxWIN = true;}
      if(gNJLjbfihH == GdCOepMByM){WcMpskxcpk = true;}
      if(ybfxQnUzQR == egcIVAkjQB){OodDjlEbed = true;}
      if(eJUpFjBTCR == VgjWkfpjxO){fOcyOhoywc = true;}
      while(GdCOepMByM == gNJLjbfihH){NEfjmVEwwz = true;}
      while(egcIVAkjQB == egcIVAkjQB){dwSdrljIds = true;}
      while(VgjWkfpjxO == VgjWkfpjxO){WEtFMyRVlF = true;}
      if(zqroqAYMRJ == true){zqroqAYMRJ = false;}
      if(acUeVLQcLV == true){acUeVLQcLV = false;}
      if(JPjRdZsecy == true){JPjRdZsecy = false;}
      if(zcDiNmonQU == true){zcDiNmonQU = false;}
      if(bYRGasLEBZ == true){bYRGasLEBZ = false;}
      if(ONXbEjHaKR == true){ONXbEjHaKR = false;}
      if(GsiSKyYlRh == true){GsiSKyYlRh = false;}
      if(WcMpskxcpk == true){WcMpskxcpk = false;}
      if(OodDjlEbed == true){OodDjlEbed = false;}
      if(fOcyOhoywc == true){fOcyOhoywc = false;}
      if(UYlSCkAghT == true){UYlSCkAghT = false;}
      if(ldjZDQPfiY == true){ldjZDQPfiY = false;}
      if(sxHnBIzNbK == true){sxHnBIzNbK = false;}
      if(uzfNQoCLAy == true){uzfNQoCLAy = false;}
      if(kWsKrCdDux == true){kWsKrCdDux = false;}
      if(SJPXjWRyQt == true){SJPXjWRyQt = false;}
      if(kmFWYlxWIN == true){kmFWYlxWIN = false;}
      if(NEfjmVEwwz == true){NEfjmVEwwz = false;}
      if(dwSdrljIds == true){dwSdrljIds = false;}
      if(WEtFMyRVlF == true){WEtFMyRVlF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKNQCMNTTM
{ 
  void ldsIHfdRKQ()
  { 
      bool HsIZGJOJTn = false;
      bool sBgIlZokXA = false;
      bool HnGFQIwuLI = false;
      bool WJxlUVnWJZ = false;
      bool wdEDcFApsg = false;
      bool tPfBgTmCJx = false;
      bool MSyLQjDtnQ = false;
      bool kSayDdiCcL = false;
      bool HGCeOHcwEB = false;
      bool hkNLMdeslr = false;
      bool BGBbuanhxC = false;
      bool jjZxpGPTxJ = false;
      bool HHomizFPkZ = false;
      bool ypPjJBEaim = false;
      bool StyCRxLPVG = false;
      bool NLwcktQOsu = false;
      bool VXxWDsUpnn = false;
      bool CojJpMImVk = false;
      bool npseMmsmyO = false;
      bool jognQuxayX = false;
      string oTnZgXdkrZ;
      string wAczFXWFFM;
      string rqFDOciapL;
      string IMXmrjbAgQ;
      string msErSHFZFC;
      string bFzSMxNkLD;
      string oCufRjcoGU;
      string wWXnYzmNkH;
      string XIVmjCMEau;
      string VpndbkxXai;
      string ePTjGFgLtM;
      string KAzEfffHwO;
      string XXNLyFhtLm;
      string BOlCbIokfd;
      string VAKNjVpjxw;
      string EpbMKGBHlB;
      string XlAGLuNxbX;
      string puaRrWNAac;
      string OxwPiLmYqV;
      string GhzeGjAECo;
      if(oTnZgXdkrZ == ePTjGFgLtM){HsIZGJOJTn = true;}
      else if(ePTjGFgLtM == oTnZgXdkrZ){BGBbuanhxC = true;}
      if(wAczFXWFFM == KAzEfffHwO){sBgIlZokXA = true;}
      else if(KAzEfffHwO == wAczFXWFFM){jjZxpGPTxJ = true;}
      if(rqFDOciapL == XXNLyFhtLm){HnGFQIwuLI = true;}
      else if(XXNLyFhtLm == rqFDOciapL){HHomizFPkZ = true;}
      if(IMXmrjbAgQ == BOlCbIokfd){WJxlUVnWJZ = true;}
      else if(BOlCbIokfd == IMXmrjbAgQ){ypPjJBEaim = true;}
      if(msErSHFZFC == VAKNjVpjxw){wdEDcFApsg = true;}
      else if(VAKNjVpjxw == msErSHFZFC){StyCRxLPVG = true;}
      if(bFzSMxNkLD == EpbMKGBHlB){tPfBgTmCJx = true;}
      else if(EpbMKGBHlB == bFzSMxNkLD){NLwcktQOsu = true;}
      if(oCufRjcoGU == XlAGLuNxbX){MSyLQjDtnQ = true;}
      else if(XlAGLuNxbX == oCufRjcoGU){VXxWDsUpnn = true;}
      if(wWXnYzmNkH == puaRrWNAac){kSayDdiCcL = true;}
      if(XIVmjCMEau == OxwPiLmYqV){HGCeOHcwEB = true;}
      if(VpndbkxXai == GhzeGjAECo){hkNLMdeslr = true;}
      while(puaRrWNAac == wWXnYzmNkH){CojJpMImVk = true;}
      while(OxwPiLmYqV == OxwPiLmYqV){npseMmsmyO = true;}
      while(GhzeGjAECo == GhzeGjAECo){jognQuxayX = true;}
      if(HsIZGJOJTn == true){HsIZGJOJTn = false;}
      if(sBgIlZokXA == true){sBgIlZokXA = false;}
      if(HnGFQIwuLI == true){HnGFQIwuLI = false;}
      if(WJxlUVnWJZ == true){WJxlUVnWJZ = false;}
      if(wdEDcFApsg == true){wdEDcFApsg = false;}
      if(tPfBgTmCJx == true){tPfBgTmCJx = false;}
      if(MSyLQjDtnQ == true){MSyLQjDtnQ = false;}
      if(kSayDdiCcL == true){kSayDdiCcL = false;}
      if(HGCeOHcwEB == true){HGCeOHcwEB = false;}
      if(hkNLMdeslr == true){hkNLMdeslr = false;}
      if(BGBbuanhxC == true){BGBbuanhxC = false;}
      if(jjZxpGPTxJ == true){jjZxpGPTxJ = false;}
      if(HHomizFPkZ == true){HHomizFPkZ = false;}
      if(ypPjJBEaim == true){ypPjJBEaim = false;}
      if(StyCRxLPVG == true){StyCRxLPVG = false;}
      if(NLwcktQOsu == true){NLwcktQOsu = false;}
      if(VXxWDsUpnn == true){VXxWDsUpnn = false;}
      if(CojJpMImVk == true){CojJpMImVk = false;}
      if(npseMmsmyO == true){npseMmsmyO = false;}
      if(jognQuxayX == true){jognQuxayX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVBXMGCTEQ
{ 
  void JQrOtmaRdL()
  { 
      bool DCgQmayxYl = false;
      bool mcQjPPGgFF = false;
      bool nQLFRcCBPe = false;
      bool thyXhJpWBl = false;
      bool JNKWLNnleH = false;
      bool PNuCVlqazJ = false;
      bool YwhtqEdsBF = false;
      bool ZifTuZGntD = false;
      bool oPWHOglwBw = false;
      bool SOXqMNePfG = false;
      bool itkYgghbGu = false;
      bool eCfuUJYZfK = false;
      bool RhrEmKKnGh = false;
      bool tpInUtdxZh = false;
      bool yKpFQPhcVD = false;
      bool nFjUnBCflW = false;
      bool VsUXBntrZa = false;
      bool ebzxMHqlmX = false;
      bool chSDtoGmzT = false;
      bool ryLDMEoREb = false;
      string CFsHWIsEin;
      string AZYdmZDrET;
      string cYoNjEcXFa;
      string xtQOhgLiYm;
      string mMrkplTjSY;
      string RZxNecQfXS;
      string eVzIqFJJuG;
      string OUSRfPgEXy;
      string jsEfIXxDiF;
      string QeLGHRNjsk;
      string cKoLKxGfhO;
      string wLHZhlQSzS;
      string HFappiJMJN;
      string CwKmUZDrVL;
      string QRVTIEWkXU;
      string AtkacWiyVa;
      string ntVTMzBUEH;
      string hYwmBpjGgl;
      string LXnnNHLjJy;
      string pFWtXWuBHJ;
      if(CFsHWIsEin == cKoLKxGfhO){DCgQmayxYl = true;}
      else if(cKoLKxGfhO == CFsHWIsEin){itkYgghbGu = true;}
      if(AZYdmZDrET == wLHZhlQSzS){mcQjPPGgFF = true;}
      else if(wLHZhlQSzS == AZYdmZDrET){eCfuUJYZfK = true;}
      if(cYoNjEcXFa == HFappiJMJN){nQLFRcCBPe = true;}
      else if(HFappiJMJN == cYoNjEcXFa){RhrEmKKnGh = true;}
      if(xtQOhgLiYm == CwKmUZDrVL){thyXhJpWBl = true;}
      else if(CwKmUZDrVL == xtQOhgLiYm){tpInUtdxZh = true;}
      if(mMrkplTjSY == QRVTIEWkXU){JNKWLNnleH = true;}
      else if(QRVTIEWkXU == mMrkplTjSY){yKpFQPhcVD = true;}
      if(RZxNecQfXS == AtkacWiyVa){PNuCVlqazJ = true;}
      else if(AtkacWiyVa == RZxNecQfXS){nFjUnBCflW = true;}
      if(eVzIqFJJuG == ntVTMzBUEH){YwhtqEdsBF = true;}
      else if(ntVTMzBUEH == eVzIqFJJuG){VsUXBntrZa = true;}
      if(OUSRfPgEXy == hYwmBpjGgl){ZifTuZGntD = true;}
      if(jsEfIXxDiF == LXnnNHLjJy){oPWHOglwBw = true;}
      if(QeLGHRNjsk == pFWtXWuBHJ){SOXqMNePfG = true;}
      while(hYwmBpjGgl == OUSRfPgEXy){ebzxMHqlmX = true;}
      while(LXnnNHLjJy == LXnnNHLjJy){chSDtoGmzT = true;}
      while(pFWtXWuBHJ == pFWtXWuBHJ){ryLDMEoREb = true;}
      if(DCgQmayxYl == true){DCgQmayxYl = false;}
      if(mcQjPPGgFF == true){mcQjPPGgFF = false;}
      if(nQLFRcCBPe == true){nQLFRcCBPe = false;}
      if(thyXhJpWBl == true){thyXhJpWBl = false;}
      if(JNKWLNnleH == true){JNKWLNnleH = false;}
      if(PNuCVlqazJ == true){PNuCVlqazJ = false;}
      if(YwhtqEdsBF == true){YwhtqEdsBF = false;}
      if(ZifTuZGntD == true){ZifTuZGntD = false;}
      if(oPWHOglwBw == true){oPWHOglwBw = false;}
      if(SOXqMNePfG == true){SOXqMNePfG = false;}
      if(itkYgghbGu == true){itkYgghbGu = false;}
      if(eCfuUJYZfK == true){eCfuUJYZfK = false;}
      if(RhrEmKKnGh == true){RhrEmKKnGh = false;}
      if(tpInUtdxZh == true){tpInUtdxZh = false;}
      if(yKpFQPhcVD == true){yKpFQPhcVD = false;}
      if(nFjUnBCflW == true){nFjUnBCflW = false;}
      if(VsUXBntrZa == true){VsUXBntrZa = false;}
      if(ebzxMHqlmX == true){ebzxMHqlmX = false;}
      if(chSDtoGmzT == true){chSDtoGmzT = false;}
      if(ryLDMEoREb == true){ryLDMEoREb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKVYVZNBRN
{ 
  void RzondjlzyQ()
  { 
      bool AtRnVDwwnP = false;
      bool rfglcadWWS = false;
      bool lPwpBkVBiT = false;
      bool ilIBDtEPFx = false;
      bool oOzuUxJBxS = false;
      bool bjpqZjybmk = false;
      bool guNUfFXeii = false;
      bool WOQZcWPAUE = false;
      bool aTDQqzwRbT = false;
      bool ubcUPtBePO = false;
      bool ZeSOwNSQNC = false;
      bool TxGhJMqxcf = false;
      bool JFCOmtkwJi = false;
      bool UjkFdwBnTd = false;
      bool geEYzyVtKC = false;
      bool CECiFTbEbC = false;
      bool bWGegiMBDN = false;
      bool LDczzdBcOn = false;
      bool XqkGfQhBAK = false;
      bool TwLRCJYYrQ = false;
      string bEYuNxNoeI;
      string CgIRPbfoIo;
      string QQSkJyiuVi;
      string zgaxDwMNqY;
      string WMnmVepfRV;
      string FEFETLlmkP;
      string OSTwJVFKOS;
      string OSyiSEcePd;
      string HCczctaVdq;
      string KYbaJDsrcz;
      string ZeRyHmFWlP;
      string hGXHHMoUSO;
      string tigWIppWYO;
      string KkCQEbkerp;
      string oEjOJEBUTx;
      string OYYNFqytpR;
      string whyWExEGDe;
      string bKbcZpzSND;
      string nVDaAlLnKM;
      string dpnasGGMJL;
      if(bEYuNxNoeI == ZeRyHmFWlP){AtRnVDwwnP = true;}
      else if(ZeRyHmFWlP == bEYuNxNoeI){ZeSOwNSQNC = true;}
      if(CgIRPbfoIo == hGXHHMoUSO){rfglcadWWS = true;}
      else if(hGXHHMoUSO == CgIRPbfoIo){TxGhJMqxcf = true;}
      if(QQSkJyiuVi == tigWIppWYO){lPwpBkVBiT = true;}
      else if(tigWIppWYO == QQSkJyiuVi){JFCOmtkwJi = true;}
      if(zgaxDwMNqY == KkCQEbkerp){ilIBDtEPFx = true;}
      else if(KkCQEbkerp == zgaxDwMNqY){UjkFdwBnTd = true;}
      if(WMnmVepfRV == oEjOJEBUTx){oOzuUxJBxS = true;}
      else if(oEjOJEBUTx == WMnmVepfRV){geEYzyVtKC = true;}
      if(FEFETLlmkP == OYYNFqytpR){bjpqZjybmk = true;}
      else if(OYYNFqytpR == FEFETLlmkP){CECiFTbEbC = true;}
      if(OSTwJVFKOS == whyWExEGDe){guNUfFXeii = true;}
      else if(whyWExEGDe == OSTwJVFKOS){bWGegiMBDN = true;}
      if(OSyiSEcePd == bKbcZpzSND){WOQZcWPAUE = true;}
      if(HCczctaVdq == nVDaAlLnKM){aTDQqzwRbT = true;}
      if(KYbaJDsrcz == dpnasGGMJL){ubcUPtBePO = true;}
      while(bKbcZpzSND == OSyiSEcePd){LDczzdBcOn = true;}
      while(nVDaAlLnKM == nVDaAlLnKM){XqkGfQhBAK = true;}
      while(dpnasGGMJL == dpnasGGMJL){TwLRCJYYrQ = true;}
      if(AtRnVDwwnP == true){AtRnVDwwnP = false;}
      if(rfglcadWWS == true){rfglcadWWS = false;}
      if(lPwpBkVBiT == true){lPwpBkVBiT = false;}
      if(ilIBDtEPFx == true){ilIBDtEPFx = false;}
      if(oOzuUxJBxS == true){oOzuUxJBxS = false;}
      if(bjpqZjybmk == true){bjpqZjybmk = false;}
      if(guNUfFXeii == true){guNUfFXeii = false;}
      if(WOQZcWPAUE == true){WOQZcWPAUE = false;}
      if(aTDQqzwRbT == true){aTDQqzwRbT = false;}
      if(ubcUPtBePO == true){ubcUPtBePO = false;}
      if(ZeSOwNSQNC == true){ZeSOwNSQNC = false;}
      if(TxGhJMqxcf == true){TxGhJMqxcf = false;}
      if(JFCOmtkwJi == true){JFCOmtkwJi = false;}
      if(UjkFdwBnTd == true){UjkFdwBnTd = false;}
      if(geEYzyVtKC == true){geEYzyVtKC = false;}
      if(CECiFTbEbC == true){CECiFTbEbC = false;}
      if(bWGegiMBDN == true){bWGegiMBDN = false;}
      if(LDczzdBcOn == true){LDczzdBcOn = false;}
      if(XqkGfQhBAK == true){XqkGfQhBAK = false;}
      if(TwLRCJYYrQ == true){TwLRCJYYrQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PURAQYNXMR
{ 
  void WEVmhKClNM()
  { 
      bool wALtqDRHyH = false;
      bool DsyRmuqQOb = false;
      bool ZBppuiwWgp = false;
      bool NAyRhJBhWX = false;
      bool QHUQfiUXIk = false;
      bool UkuIxtJVzI = false;
      bool HtaIsCtfic = false;
      bool sItpKRgYJM = false;
      bool NXOuUbFpUm = false;
      bool zeiOQWgLXc = false;
      bool nnoeqLqEyf = false;
      bool NkLltieemR = false;
      bool xELwcOYeZm = false;
      bool jUBgXZijDJ = false;
      bool jArnYOTxUg = false;
      bool qBYFfibrBc = false;
      bool lMeKusjeNT = false;
      bool AubdgxMXWO = false;
      bool tbJrwhwuAn = false;
      bool yphaWXUgrf = false;
      string EUiOyeZHIe;
      string hSPDGAQPQx;
      string hYXGROYXhL;
      string yOyOQDCHbI;
      string QTSRntGbtT;
      string QCuoqfwcwj;
      string GCYwfSTBmC;
      string yJmIgNGGRX;
      string IwdNuwTJXk;
      string GYKrCOuVkV;
      string ZFoqVGOlIc;
      string YpKYaJYKBj;
      string yKcBuYztGR;
      string SjUwyDHlrn;
      string ghAtLQOlRr;
      string pjUBXObnwx;
      string HUepKoUOZW;
      string BlSMCQKiod;
      string JMcNbiPTYj;
      string bSpufMCJjW;
      if(EUiOyeZHIe == ZFoqVGOlIc){wALtqDRHyH = true;}
      else if(ZFoqVGOlIc == EUiOyeZHIe){nnoeqLqEyf = true;}
      if(hSPDGAQPQx == YpKYaJYKBj){DsyRmuqQOb = true;}
      else if(YpKYaJYKBj == hSPDGAQPQx){NkLltieemR = true;}
      if(hYXGROYXhL == yKcBuYztGR){ZBppuiwWgp = true;}
      else if(yKcBuYztGR == hYXGROYXhL){xELwcOYeZm = true;}
      if(yOyOQDCHbI == SjUwyDHlrn){NAyRhJBhWX = true;}
      else if(SjUwyDHlrn == yOyOQDCHbI){jUBgXZijDJ = true;}
      if(QTSRntGbtT == ghAtLQOlRr){QHUQfiUXIk = true;}
      else if(ghAtLQOlRr == QTSRntGbtT){jArnYOTxUg = true;}
      if(QCuoqfwcwj == pjUBXObnwx){UkuIxtJVzI = true;}
      else if(pjUBXObnwx == QCuoqfwcwj){qBYFfibrBc = true;}
      if(GCYwfSTBmC == HUepKoUOZW){HtaIsCtfic = true;}
      else if(HUepKoUOZW == GCYwfSTBmC){lMeKusjeNT = true;}
      if(yJmIgNGGRX == BlSMCQKiod){sItpKRgYJM = true;}
      if(IwdNuwTJXk == JMcNbiPTYj){NXOuUbFpUm = true;}
      if(GYKrCOuVkV == bSpufMCJjW){zeiOQWgLXc = true;}
      while(BlSMCQKiod == yJmIgNGGRX){AubdgxMXWO = true;}
      while(JMcNbiPTYj == JMcNbiPTYj){tbJrwhwuAn = true;}
      while(bSpufMCJjW == bSpufMCJjW){yphaWXUgrf = true;}
      if(wALtqDRHyH == true){wALtqDRHyH = false;}
      if(DsyRmuqQOb == true){DsyRmuqQOb = false;}
      if(ZBppuiwWgp == true){ZBppuiwWgp = false;}
      if(NAyRhJBhWX == true){NAyRhJBhWX = false;}
      if(QHUQfiUXIk == true){QHUQfiUXIk = false;}
      if(UkuIxtJVzI == true){UkuIxtJVzI = false;}
      if(HtaIsCtfic == true){HtaIsCtfic = false;}
      if(sItpKRgYJM == true){sItpKRgYJM = false;}
      if(NXOuUbFpUm == true){NXOuUbFpUm = false;}
      if(zeiOQWgLXc == true){zeiOQWgLXc = false;}
      if(nnoeqLqEyf == true){nnoeqLqEyf = false;}
      if(NkLltieemR == true){NkLltieemR = false;}
      if(xELwcOYeZm == true){xELwcOYeZm = false;}
      if(jUBgXZijDJ == true){jUBgXZijDJ = false;}
      if(jArnYOTxUg == true){jArnYOTxUg = false;}
      if(qBYFfibrBc == true){qBYFfibrBc = false;}
      if(lMeKusjeNT == true){lMeKusjeNT = false;}
      if(AubdgxMXWO == true){AubdgxMXWO = false;}
      if(tbJrwhwuAn == true){tbJrwhwuAn = false;}
      if(yphaWXUgrf == true){yphaWXUgrf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLYOPVWEJS
{ 
  void YGSlFTcJJK()
  { 
      bool XDHYEgafzA = false;
      bool URrIDwbrWQ = false;
      bool OHeqNREYjP = false;
      bool brgNbskheJ = false;
      bool dhhCegRXEd = false;
      bool PbAVjQYPLm = false;
      bool bBuiYcjegK = false;
      bool KsMNmgZcMf = false;
      bool zfUFAAqKcK = false;
      bool UUWrgblydC = false;
      bool wlqsTVOliD = false;
      bool quDemufoiX = false;
      bool kZCVpoWUgK = false;
      bool tazJjMoald = false;
      bool kFbYTYRqEk = false;
      bool uwOFQWjUDd = false;
      bool zsFXIPwsta = false;
      bool GFDFmfxdBQ = false;
      bool XeQuOyMssN = false;
      bool cTXIerzDQE = false;
      string OVVVQJdOdj;
      string xwuIKsBqVo;
      string lMJBUZEogE;
      string zTldKEoeUe;
      string jdqcPwdscn;
      string FxhcoBLTBp;
      string FngZkcJQxG;
      string EWVpFHUglX;
      string wLMryBlIoI;
      string rUceZuwRql;
      string lMuWjiaqXg;
      string fehctsboai;
      string pBboNisqPJ;
      string LDozkiQpIP;
      string atkIbNlAjg;
      string THpHwkkFIA;
      string oiaNUbohrL;
      string blgKIuPTMA;
      string xsHipENgDA;
      string yKgHarTXmz;
      if(OVVVQJdOdj == lMuWjiaqXg){XDHYEgafzA = true;}
      else if(lMuWjiaqXg == OVVVQJdOdj){wlqsTVOliD = true;}
      if(xwuIKsBqVo == fehctsboai){URrIDwbrWQ = true;}
      else if(fehctsboai == xwuIKsBqVo){quDemufoiX = true;}
      if(lMJBUZEogE == pBboNisqPJ){OHeqNREYjP = true;}
      else if(pBboNisqPJ == lMJBUZEogE){kZCVpoWUgK = true;}
      if(zTldKEoeUe == LDozkiQpIP){brgNbskheJ = true;}
      else if(LDozkiQpIP == zTldKEoeUe){tazJjMoald = true;}
      if(jdqcPwdscn == atkIbNlAjg){dhhCegRXEd = true;}
      else if(atkIbNlAjg == jdqcPwdscn){kFbYTYRqEk = true;}
      if(FxhcoBLTBp == THpHwkkFIA){PbAVjQYPLm = true;}
      else if(THpHwkkFIA == FxhcoBLTBp){uwOFQWjUDd = true;}
      if(FngZkcJQxG == oiaNUbohrL){bBuiYcjegK = true;}
      else if(oiaNUbohrL == FngZkcJQxG){zsFXIPwsta = true;}
      if(EWVpFHUglX == blgKIuPTMA){KsMNmgZcMf = true;}
      if(wLMryBlIoI == xsHipENgDA){zfUFAAqKcK = true;}
      if(rUceZuwRql == yKgHarTXmz){UUWrgblydC = true;}
      while(blgKIuPTMA == EWVpFHUglX){GFDFmfxdBQ = true;}
      while(xsHipENgDA == xsHipENgDA){XeQuOyMssN = true;}
      while(yKgHarTXmz == yKgHarTXmz){cTXIerzDQE = true;}
      if(XDHYEgafzA == true){XDHYEgafzA = false;}
      if(URrIDwbrWQ == true){URrIDwbrWQ = false;}
      if(OHeqNREYjP == true){OHeqNREYjP = false;}
      if(brgNbskheJ == true){brgNbskheJ = false;}
      if(dhhCegRXEd == true){dhhCegRXEd = false;}
      if(PbAVjQYPLm == true){PbAVjQYPLm = false;}
      if(bBuiYcjegK == true){bBuiYcjegK = false;}
      if(KsMNmgZcMf == true){KsMNmgZcMf = false;}
      if(zfUFAAqKcK == true){zfUFAAqKcK = false;}
      if(UUWrgblydC == true){UUWrgblydC = false;}
      if(wlqsTVOliD == true){wlqsTVOliD = false;}
      if(quDemufoiX == true){quDemufoiX = false;}
      if(kZCVpoWUgK == true){kZCVpoWUgK = false;}
      if(tazJjMoald == true){tazJjMoald = false;}
      if(kFbYTYRqEk == true){kFbYTYRqEk = false;}
      if(uwOFQWjUDd == true){uwOFQWjUDd = false;}
      if(zsFXIPwsta == true){zsFXIPwsta = false;}
      if(GFDFmfxdBQ == true){GFDFmfxdBQ = false;}
      if(XeQuOyMssN == true){XeQuOyMssN = false;}
      if(cTXIerzDQE == true){cTXIerzDQE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJNXZGHTYF
{ 
  void NWgDZzLACr()
  { 
      bool MgaIkpHYIJ = false;
      bool VMuXsALeZT = false;
      bool tlTwjOTjAS = false;
      bool wrwjSHNViD = false;
      bool zkPQrlGZoK = false;
      bool BeAIRaNeXW = false;
      bool WXXoMcPKFl = false;
      bool lpwWTJVDDy = false;
      bool HstpRRrmSq = false;
      bool tiyMgbMaDP = false;
      bool VuUDXLhcoI = false;
      bool EJbZOcchWu = false;
      bool jcrNrCrjpr = false;
      bool xuzmbLXqRG = false;
      bool iOyKmjHXxD = false;
      bool yeDIesDHLU = false;
      bool SymwKIKnxD = false;
      bool EkPQLUegZH = false;
      bool uTmlsSrpHi = false;
      bool IQfwmkbBzd = false;
      string BZFJPspfgI;
      string eyEfDmsGEj;
      string CMOzozhMhF;
      string HiSPDFOSaW;
      string FJWaciChEU;
      string prDBCnLFTP;
      string KcxaAwfobx;
      string XZfhespnWG;
      string xAINPPeRMO;
      string tJzKLcLuZg;
      string DNFGwPLVWI;
      string yXiNSKTjLk;
      string QObNCOaVVC;
      string htNoDjtCQz;
      string DJuDQWZkqB;
      string IajoPokrDh;
      string opzTaEJsKi;
      string QRSLgGTYwf;
      string nodTsHJXZN;
      string yByiKNKacL;
      if(BZFJPspfgI == DNFGwPLVWI){MgaIkpHYIJ = true;}
      else if(DNFGwPLVWI == BZFJPspfgI){VuUDXLhcoI = true;}
      if(eyEfDmsGEj == yXiNSKTjLk){VMuXsALeZT = true;}
      else if(yXiNSKTjLk == eyEfDmsGEj){EJbZOcchWu = true;}
      if(CMOzozhMhF == QObNCOaVVC){tlTwjOTjAS = true;}
      else if(QObNCOaVVC == CMOzozhMhF){jcrNrCrjpr = true;}
      if(HiSPDFOSaW == htNoDjtCQz){wrwjSHNViD = true;}
      else if(htNoDjtCQz == HiSPDFOSaW){xuzmbLXqRG = true;}
      if(FJWaciChEU == DJuDQWZkqB){zkPQrlGZoK = true;}
      else if(DJuDQWZkqB == FJWaciChEU){iOyKmjHXxD = true;}
      if(prDBCnLFTP == IajoPokrDh){BeAIRaNeXW = true;}
      else if(IajoPokrDh == prDBCnLFTP){yeDIesDHLU = true;}
      if(KcxaAwfobx == opzTaEJsKi){WXXoMcPKFl = true;}
      else if(opzTaEJsKi == KcxaAwfobx){SymwKIKnxD = true;}
      if(XZfhespnWG == QRSLgGTYwf){lpwWTJVDDy = true;}
      if(xAINPPeRMO == nodTsHJXZN){HstpRRrmSq = true;}
      if(tJzKLcLuZg == yByiKNKacL){tiyMgbMaDP = true;}
      while(QRSLgGTYwf == XZfhespnWG){EkPQLUegZH = true;}
      while(nodTsHJXZN == nodTsHJXZN){uTmlsSrpHi = true;}
      while(yByiKNKacL == yByiKNKacL){IQfwmkbBzd = true;}
      if(MgaIkpHYIJ == true){MgaIkpHYIJ = false;}
      if(VMuXsALeZT == true){VMuXsALeZT = false;}
      if(tlTwjOTjAS == true){tlTwjOTjAS = false;}
      if(wrwjSHNViD == true){wrwjSHNViD = false;}
      if(zkPQrlGZoK == true){zkPQrlGZoK = false;}
      if(BeAIRaNeXW == true){BeAIRaNeXW = false;}
      if(WXXoMcPKFl == true){WXXoMcPKFl = false;}
      if(lpwWTJVDDy == true){lpwWTJVDDy = false;}
      if(HstpRRrmSq == true){HstpRRrmSq = false;}
      if(tiyMgbMaDP == true){tiyMgbMaDP = false;}
      if(VuUDXLhcoI == true){VuUDXLhcoI = false;}
      if(EJbZOcchWu == true){EJbZOcchWu = false;}
      if(jcrNrCrjpr == true){jcrNrCrjpr = false;}
      if(xuzmbLXqRG == true){xuzmbLXqRG = false;}
      if(iOyKmjHXxD == true){iOyKmjHXxD = false;}
      if(yeDIesDHLU == true){yeDIesDHLU = false;}
      if(SymwKIKnxD == true){SymwKIKnxD = false;}
      if(EkPQLUegZH == true){EkPQLUegZH = false;}
      if(uTmlsSrpHi == true){uTmlsSrpHi = false;}
      if(IQfwmkbBzd == true){IQfwmkbBzd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGXNKCOLLK
{ 
  void jkoRpPeeBs()
  { 
      bool RgTxQKKYap = false;
      bool dFSUIhOafz = false;
      bool CacwUsJBtd = false;
      bool JIMzjtRJLR = false;
      bool zmXVzVqCie = false;
      bool NYOXbpEWbW = false;
      bool AJewgVsTjN = false;
      bool QFONAODGxy = false;
      bool BHSOQjtnWs = false;
      bool ptgoQoIaod = false;
      bool cXRUOIKAXN = false;
      bool mxZdVsqPfw = false;
      bool aExqXWXZwK = false;
      bool GbRSVdpxAI = false;
      bool ZsPIGrUDSX = false;
      bool yrusCXZZwq = false;
      bool jkDNHKfGIq = false;
      bool CsPXWhnnke = false;
      bool BUGYLNgYQx = false;
      bool EPAIXnpCBu = false;
      string eAXMoGKrJU;
      string FnetQMYDCu;
      string oHbAbBSWMn;
      string xnzJWWsPuV;
      string GDrJcbbpKB;
      string IdhRGWYWjm;
      string nmfVXRnUWs;
      string TJHfnkPRWz;
      string YbLKfTFgCA;
      string yVeHhSXWlL;
      string nHTRhyVCdV;
      string HGAkNMaUoE;
      string MGRWtxeAyU;
      string MsfLKRHtbg;
      string xDDgsrVssU;
      string rDggzgpxWk;
      string TVDIINZnZw;
      string EgrHGIDjdC;
      string bkGccJLyLd;
      string bKWqNbztXe;
      if(eAXMoGKrJU == nHTRhyVCdV){RgTxQKKYap = true;}
      else if(nHTRhyVCdV == eAXMoGKrJU){cXRUOIKAXN = true;}
      if(FnetQMYDCu == HGAkNMaUoE){dFSUIhOafz = true;}
      else if(HGAkNMaUoE == FnetQMYDCu){mxZdVsqPfw = true;}
      if(oHbAbBSWMn == MGRWtxeAyU){CacwUsJBtd = true;}
      else if(MGRWtxeAyU == oHbAbBSWMn){aExqXWXZwK = true;}
      if(xnzJWWsPuV == MsfLKRHtbg){JIMzjtRJLR = true;}
      else if(MsfLKRHtbg == xnzJWWsPuV){GbRSVdpxAI = true;}
      if(GDrJcbbpKB == xDDgsrVssU){zmXVzVqCie = true;}
      else if(xDDgsrVssU == GDrJcbbpKB){ZsPIGrUDSX = true;}
      if(IdhRGWYWjm == rDggzgpxWk){NYOXbpEWbW = true;}
      else if(rDggzgpxWk == IdhRGWYWjm){yrusCXZZwq = true;}
      if(nmfVXRnUWs == TVDIINZnZw){AJewgVsTjN = true;}
      else if(TVDIINZnZw == nmfVXRnUWs){jkDNHKfGIq = true;}
      if(TJHfnkPRWz == EgrHGIDjdC){QFONAODGxy = true;}
      if(YbLKfTFgCA == bkGccJLyLd){BHSOQjtnWs = true;}
      if(yVeHhSXWlL == bKWqNbztXe){ptgoQoIaod = true;}
      while(EgrHGIDjdC == TJHfnkPRWz){CsPXWhnnke = true;}
      while(bkGccJLyLd == bkGccJLyLd){BUGYLNgYQx = true;}
      while(bKWqNbztXe == bKWqNbztXe){EPAIXnpCBu = true;}
      if(RgTxQKKYap == true){RgTxQKKYap = false;}
      if(dFSUIhOafz == true){dFSUIhOafz = false;}
      if(CacwUsJBtd == true){CacwUsJBtd = false;}
      if(JIMzjtRJLR == true){JIMzjtRJLR = false;}
      if(zmXVzVqCie == true){zmXVzVqCie = false;}
      if(NYOXbpEWbW == true){NYOXbpEWbW = false;}
      if(AJewgVsTjN == true){AJewgVsTjN = false;}
      if(QFONAODGxy == true){QFONAODGxy = false;}
      if(BHSOQjtnWs == true){BHSOQjtnWs = false;}
      if(ptgoQoIaod == true){ptgoQoIaod = false;}
      if(cXRUOIKAXN == true){cXRUOIKAXN = false;}
      if(mxZdVsqPfw == true){mxZdVsqPfw = false;}
      if(aExqXWXZwK == true){aExqXWXZwK = false;}
      if(GbRSVdpxAI == true){GbRSVdpxAI = false;}
      if(ZsPIGrUDSX == true){ZsPIGrUDSX = false;}
      if(yrusCXZZwq == true){yrusCXZZwq = false;}
      if(jkDNHKfGIq == true){jkDNHKfGIq = false;}
      if(CsPXWhnnke == true){CsPXWhnnke = false;}
      if(BUGYLNgYQx == true){BUGYLNgYQx = false;}
      if(EPAIXnpCBu == true){EPAIXnpCBu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BIVVZLGRAH
{ 
  void rsatjIgmrP()
  { 
      bool nlzoOmVtQN = false;
      bool HmeNEYBhkm = false;
      bool qZsArsKwka = false;
      bool RUqyZsGstU = false;
      bool UNEXUIABsl = false;
      bool IFeewOrzxU = false;
      bool cYJpwlwfnK = false;
      bool SInQRcUVei = false;
      bool rICyRLoLBL = false;
      bool BHwYquEOah = false;
      bool MUNiTzQNMT = false;
      bool sWTNbTVKXj = false;
      bool xjdbJLMPYW = false;
      bool YFtxVXuTdR = false;
      bool ubzhRdmhwX = false;
      bool YsppkcpkYI = false;
      bool mAnptmbVrE = false;
      bool XCfGoUjwKe = false;
      bool XeTBxePDMs = false;
      bool hJuVetmJnd = false;
      string kqRHCXWqLc;
      string UBxpjCbDnI;
      string hDOUHcGqzT;
      string GQjNXhAXid;
      string JiWFJCjMai;
      string QQxMhhcwAY;
      string RfqqWEQiSC;
      string BEUJyygIKE;
      string rsPPDpTWep;
      string EDWJMdrfiE;
      string kAtYhMunNj;
      string BUlufXQbnf;
      string ksEbxxgLwU;
      string GAYFTryphq;
      string teIuojRacn;
      string NPrCTqwSaj;
      string ejqscAufbn;
      string ZZtxkFjImN;
      string fFhIHpIVlb;
      string wfOxLKnPRn;
      if(kqRHCXWqLc == kAtYhMunNj){nlzoOmVtQN = true;}
      else if(kAtYhMunNj == kqRHCXWqLc){MUNiTzQNMT = true;}
      if(UBxpjCbDnI == BUlufXQbnf){HmeNEYBhkm = true;}
      else if(BUlufXQbnf == UBxpjCbDnI){sWTNbTVKXj = true;}
      if(hDOUHcGqzT == ksEbxxgLwU){qZsArsKwka = true;}
      else if(ksEbxxgLwU == hDOUHcGqzT){xjdbJLMPYW = true;}
      if(GQjNXhAXid == GAYFTryphq){RUqyZsGstU = true;}
      else if(GAYFTryphq == GQjNXhAXid){YFtxVXuTdR = true;}
      if(JiWFJCjMai == teIuojRacn){UNEXUIABsl = true;}
      else if(teIuojRacn == JiWFJCjMai){ubzhRdmhwX = true;}
      if(QQxMhhcwAY == NPrCTqwSaj){IFeewOrzxU = true;}
      else if(NPrCTqwSaj == QQxMhhcwAY){YsppkcpkYI = true;}
      if(RfqqWEQiSC == ejqscAufbn){cYJpwlwfnK = true;}
      else if(ejqscAufbn == RfqqWEQiSC){mAnptmbVrE = true;}
      if(BEUJyygIKE == ZZtxkFjImN){SInQRcUVei = true;}
      if(rsPPDpTWep == fFhIHpIVlb){rICyRLoLBL = true;}
      if(EDWJMdrfiE == wfOxLKnPRn){BHwYquEOah = true;}
      while(ZZtxkFjImN == BEUJyygIKE){XCfGoUjwKe = true;}
      while(fFhIHpIVlb == fFhIHpIVlb){XeTBxePDMs = true;}
      while(wfOxLKnPRn == wfOxLKnPRn){hJuVetmJnd = true;}
      if(nlzoOmVtQN == true){nlzoOmVtQN = false;}
      if(HmeNEYBhkm == true){HmeNEYBhkm = false;}
      if(qZsArsKwka == true){qZsArsKwka = false;}
      if(RUqyZsGstU == true){RUqyZsGstU = false;}
      if(UNEXUIABsl == true){UNEXUIABsl = false;}
      if(IFeewOrzxU == true){IFeewOrzxU = false;}
      if(cYJpwlwfnK == true){cYJpwlwfnK = false;}
      if(SInQRcUVei == true){SInQRcUVei = false;}
      if(rICyRLoLBL == true){rICyRLoLBL = false;}
      if(BHwYquEOah == true){BHwYquEOah = false;}
      if(MUNiTzQNMT == true){MUNiTzQNMT = false;}
      if(sWTNbTVKXj == true){sWTNbTVKXj = false;}
      if(xjdbJLMPYW == true){xjdbJLMPYW = false;}
      if(YFtxVXuTdR == true){YFtxVXuTdR = false;}
      if(ubzhRdmhwX == true){ubzhRdmhwX = false;}
      if(YsppkcpkYI == true){YsppkcpkYI = false;}
      if(mAnptmbVrE == true){mAnptmbVrE = false;}
      if(XCfGoUjwKe == true){XCfGoUjwKe = false;}
      if(XeTBxePDMs == true){XeTBxePDMs = false;}
      if(hJuVetmJnd == true){hJuVetmJnd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZHANNMDSOH
{ 
  void cnjTHgzfqI()
  { 
      bool XIQSopnSPV = false;
      bool IkcAYpoyAZ = false;
      bool pPlunotOFS = false;
      bool nTJmumlEer = false;
      bool ClVDJnqEUC = false;
      bool uPXHNIWUez = false;
      bool wZNwhoboFl = false;
      bool DjTIXEshkz = false;
      bool ypsDWXwBZl = false;
      bool QRYewcXYVU = false;
      bool LByiyKwOjI = false;
      bool OnjeAGfKZJ = false;
      bool sZOSVlLnMt = false;
      bool gUMQmwqJEM = false;
      bool agRQWbhsdp = false;
      bool wNzLalmeNL = false;
      bool zICobtbSrD = false;
      bool OWFNiLIyus = false;
      bool ERJWyTUBoB = false;
      bool JLurNSebnc = false;
      string EUbhgTeKdm;
      string FRWKarGnGG;
      string JRuKgqVVig;
      string cJEXCDwNmt;
      string VxwaDNSUjh;
      string UQuqRlYQBo;
      string yIawKwMyIX;
      string usBMjLVTGT;
      string XBkBMLONGQ;
      string deLxuMWAQH;
      string AUMMlaPhGG;
      string QEKgQxXYiy;
      string hzqqsQgDQX;
      string oVDzTDnYPl;
      string wfHzzZUdgx;
      string oxQRYAcUTU;
      string sLRiRuBLNN;
      string IyJxCCrqrS;
      string wDWThqEkZS;
      string ZTEtrjOXhE;
      if(EUbhgTeKdm == AUMMlaPhGG){XIQSopnSPV = true;}
      else if(AUMMlaPhGG == EUbhgTeKdm){LByiyKwOjI = true;}
      if(FRWKarGnGG == QEKgQxXYiy){IkcAYpoyAZ = true;}
      else if(QEKgQxXYiy == FRWKarGnGG){OnjeAGfKZJ = true;}
      if(JRuKgqVVig == hzqqsQgDQX){pPlunotOFS = true;}
      else if(hzqqsQgDQX == JRuKgqVVig){sZOSVlLnMt = true;}
      if(cJEXCDwNmt == oVDzTDnYPl){nTJmumlEer = true;}
      else if(oVDzTDnYPl == cJEXCDwNmt){gUMQmwqJEM = true;}
      if(VxwaDNSUjh == wfHzzZUdgx){ClVDJnqEUC = true;}
      else if(wfHzzZUdgx == VxwaDNSUjh){agRQWbhsdp = true;}
      if(UQuqRlYQBo == oxQRYAcUTU){uPXHNIWUez = true;}
      else if(oxQRYAcUTU == UQuqRlYQBo){wNzLalmeNL = true;}
      if(yIawKwMyIX == sLRiRuBLNN){wZNwhoboFl = true;}
      else if(sLRiRuBLNN == yIawKwMyIX){zICobtbSrD = true;}
      if(usBMjLVTGT == IyJxCCrqrS){DjTIXEshkz = true;}
      if(XBkBMLONGQ == wDWThqEkZS){ypsDWXwBZl = true;}
      if(deLxuMWAQH == ZTEtrjOXhE){QRYewcXYVU = true;}
      while(IyJxCCrqrS == usBMjLVTGT){OWFNiLIyus = true;}
      while(wDWThqEkZS == wDWThqEkZS){ERJWyTUBoB = true;}
      while(ZTEtrjOXhE == ZTEtrjOXhE){JLurNSebnc = true;}
      if(XIQSopnSPV == true){XIQSopnSPV = false;}
      if(IkcAYpoyAZ == true){IkcAYpoyAZ = false;}
      if(pPlunotOFS == true){pPlunotOFS = false;}
      if(nTJmumlEer == true){nTJmumlEer = false;}
      if(ClVDJnqEUC == true){ClVDJnqEUC = false;}
      if(uPXHNIWUez == true){uPXHNIWUez = false;}
      if(wZNwhoboFl == true){wZNwhoboFl = false;}
      if(DjTIXEshkz == true){DjTIXEshkz = false;}
      if(ypsDWXwBZl == true){ypsDWXwBZl = false;}
      if(QRYewcXYVU == true){QRYewcXYVU = false;}
      if(LByiyKwOjI == true){LByiyKwOjI = false;}
      if(OnjeAGfKZJ == true){OnjeAGfKZJ = false;}
      if(sZOSVlLnMt == true){sZOSVlLnMt = false;}
      if(gUMQmwqJEM == true){gUMQmwqJEM = false;}
      if(agRQWbhsdp == true){agRQWbhsdp = false;}
      if(wNzLalmeNL == true){wNzLalmeNL = false;}
      if(zICobtbSrD == true){zICobtbSrD = false;}
      if(OWFNiLIyus == true){OWFNiLIyus = false;}
      if(ERJWyTUBoB == true){ERJWyTUBoB = false;}
      if(JLurNSebnc == true){JLurNSebnc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVRACNDCCJ
{ 
  void lfnOhqXpht()
  { 
      bool HLWAtkXkxX = false;
      bool AeJhNXBATa = false;
      bool OdaxncRnVV = false;
      bool sBgIiBUEGk = false;
      bool AsfNzzxtYc = false;
      bool cYekockYLR = false;
      bool SjOadzxByL = false;
      bool CxshaVyMxn = false;
      bool fXOssUVwSG = false;
      bool QwroSPdFjA = false;
      bool CwwNZfewJT = false;
      bool eYaXltUUgJ = false;
      bool dBhquGEEOK = false;
      bool qscxliaBTN = false;
      bool oYlzarUUDX = false;
      bool uJXZWAOERT = false;
      bool aZgybludkC = false;
      bool STBTTEOhQD = false;
      bool kiBqPhUCak = false;
      bool TWjzmPrnWn = false;
      string clkluyExqF;
      string PUEcECtCpj;
      string POqowtaZhH;
      string GPBRquGKoQ;
      string GDfggHPRpI;
      string MrHUiOtuoA;
      string WeOizATmlI;
      string wiNZcLiJIo;
      string eJiZtOHfhb;
      string AKVosbnwhg;
      string nbfgLddhqW;
      string ejmAVNwonj;
      string rmEJHkNXgB;
      string XlbaBCcBNQ;
      string jZnLxQXVTe;
      string ezIxoAXVYa;
      string PGBpzsILyS;
      string jtaWARzsMq;
      string NrEBVXddkA;
      string eHbmAdYyLE;
      if(clkluyExqF == nbfgLddhqW){HLWAtkXkxX = true;}
      else if(nbfgLddhqW == clkluyExqF){CwwNZfewJT = true;}
      if(PUEcECtCpj == ejmAVNwonj){AeJhNXBATa = true;}
      else if(ejmAVNwonj == PUEcECtCpj){eYaXltUUgJ = true;}
      if(POqowtaZhH == rmEJHkNXgB){OdaxncRnVV = true;}
      else if(rmEJHkNXgB == POqowtaZhH){dBhquGEEOK = true;}
      if(GPBRquGKoQ == XlbaBCcBNQ){sBgIiBUEGk = true;}
      else if(XlbaBCcBNQ == GPBRquGKoQ){qscxliaBTN = true;}
      if(GDfggHPRpI == jZnLxQXVTe){AsfNzzxtYc = true;}
      else if(jZnLxQXVTe == GDfggHPRpI){oYlzarUUDX = true;}
      if(MrHUiOtuoA == ezIxoAXVYa){cYekockYLR = true;}
      else if(ezIxoAXVYa == MrHUiOtuoA){uJXZWAOERT = true;}
      if(WeOizATmlI == PGBpzsILyS){SjOadzxByL = true;}
      else if(PGBpzsILyS == WeOizATmlI){aZgybludkC = true;}
      if(wiNZcLiJIo == jtaWARzsMq){CxshaVyMxn = true;}
      if(eJiZtOHfhb == NrEBVXddkA){fXOssUVwSG = true;}
      if(AKVosbnwhg == eHbmAdYyLE){QwroSPdFjA = true;}
      while(jtaWARzsMq == wiNZcLiJIo){STBTTEOhQD = true;}
      while(NrEBVXddkA == NrEBVXddkA){kiBqPhUCak = true;}
      while(eHbmAdYyLE == eHbmAdYyLE){TWjzmPrnWn = true;}
      if(HLWAtkXkxX == true){HLWAtkXkxX = false;}
      if(AeJhNXBATa == true){AeJhNXBATa = false;}
      if(OdaxncRnVV == true){OdaxncRnVV = false;}
      if(sBgIiBUEGk == true){sBgIiBUEGk = false;}
      if(AsfNzzxtYc == true){AsfNzzxtYc = false;}
      if(cYekockYLR == true){cYekockYLR = false;}
      if(SjOadzxByL == true){SjOadzxByL = false;}
      if(CxshaVyMxn == true){CxshaVyMxn = false;}
      if(fXOssUVwSG == true){fXOssUVwSG = false;}
      if(QwroSPdFjA == true){QwroSPdFjA = false;}
      if(CwwNZfewJT == true){CwwNZfewJT = false;}
      if(eYaXltUUgJ == true){eYaXltUUgJ = false;}
      if(dBhquGEEOK == true){dBhquGEEOK = false;}
      if(qscxliaBTN == true){qscxliaBTN = false;}
      if(oYlzarUUDX == true){oYlzarUUDX = false;}
      if(uJXZWAOERT == true){uJXZWAOERT = false;}
      if(aZgybludkC == true){aZgybludkC = false;}
      if(STBTTEOhQD == true){STBTTEOhQD = false;}
      if(kiBqPhUCak == true){kiBqPhUCak = false;}
      if(TWjzmPrnWn == true){TWjzmPrnWn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSCWIJPSRF
{ 
  void sMUbCZqrKH()
  { 
      bool ibXIsDTHBa = false;
      bool nJHywlXmRk = false;
      bool pTiGVbRNRX = false;
      bool MdixhWKqcO = false;
      bool hNSDBDGabJ = false;
      bool YfNJIPrQlQ = false;
      bool lGpdNJZKQZ = false;
      bool afJCCcBfFR = false;
      bool UpkHyfQYnS = false;
      bool dtELcaWnoq = false;
      bool dwKChrWKHf = false;
      bool NMLUuuUieh = false;
      bool sBVxugaxZa = false;
      bool FMpNnYehYF = false;
      bool JGRIEQhjPg = false;
      bool FnJHybZNGB = false;
      bool RYkfZBWyfV = false;
      bool QmJYXmiNre = false;
      bool yqgrURChOL = false;
      bool zRbXnkVlhD = false;
      string BEGjdjQcst;
      string txfVNPWnRz;
      string oJdJgqCmSY;
      string WxGqEZkKRW;
      string HVSfKRoarO;
      string jmHqOrZwCm;
      string hdJTXxqoRn;
      string dLWtrTpxyP;
      string BauEojoPcL;
      string znHdodLzIN;
      string ZAJEjXPNzu;
      string BcymkGhFdm;
      string HaLFnoDrEN;
      string HpojoBRpTQ;
      string TbQhJWpUrh;
      string uFUUGznDPu;
      string UXIkmLmNxj;
      string orlNTfKduR;
      string zhAVSCUTdp;
      string NNZXwwSfty;
      if(BEGjdjQcst == ZAJEjXPNzu){ibXIsDTHBa = true;}
      else if(ZAJEjXPNzu == BEGjdjQcst){dwKChrWKHf = true;}
      if(txfVNPWnRz == BcymkGhFdm){nJHywlXmRk = true;}
      else if(BcymkGhFdm == txfVNPWnRz){NMLUuuUieh = true;}
      if(oJdJgqCmSY == HaLFnoDrEN){pTiGVbRNRX = true;}
      else if(HaLFnoDrEN == oJdJgqCmSY){sBVxugaxZa = true;}
      if(WxGqEZkKRW == HpojoBRpTQ){MdixhWKqcO = true;}
      else if(HpojoBRpTQ == WxGqEZkKRW){FMpNnYehYF = true;}
      if(HVSfKRoarO == TbQhJWpUrh){hNSDBDGabJ = true;}
      else if(TbQhJWpUrh == HVSfKRoarO){JGRIEQhjPg = true;}
      if(jmHqOrZwCm == uFUUGznDPu){YfNJIPrQlQ = true;}
      else if(uFUUGznDPu == jmHqOrZwCm){FnJHybZNGB = true;}
      if(hdJTXxqoRn == UXIkmLmNxj){lGpdNJZKQZ = true;}
      else if(UXIkmLmNxj == hdJTXxqoRn){RYkfZBWyfV = true;}
      if(dLWtrTpxyP == orlNTfKduR){afJCCcBfFR = true;}
      if(BauEojoPcL == zhAVSCUTdp){UpkHyfQYnS = true;}
      if(znHdodLzIN == NNZXwwSfty){dtELcaWnoq = true;}
      while(orlNTfKduR == dLWtrTpxyP){QmJYXmiNre = true;}
      while(zhAVSCUTdp == zhAVSCUTdp){yqgrURChOL = true;}
      while(NNZXwwSfty == NNZXwwSfty){zRbXnkVlhD = true;}
      if(ibXIsDTHBa == true){ibXIsDTHBa = false;}
      if(nJHywlXmRk == true){nJHywlXmRk = false;}
      if(pTiGVbRNRX == true){pTiGVbRNRX = false;}
      if(MdixhWKqcO == true){MdixhWKqcO = false;}
      if(hNSDBDGabJ == true){hNSDBDGabJ = false;}
      if(YfNJIPrQlQ == true){YfNJIPrQlQ = false;}
      if(lGpdNJZKQZ == true){lGpdNJZKQZ = false;}
      if(afJCCcBfFR == true){afJCCcBfFR = false;}
      if(UpkHyfQYnS == true){UpkHyfQYnS = false;}
      if(dtELcaWnoq == true){dtELcaWnoq = false;}
      if(dwKChrWKHf == true){dwKChrWKHf = false;}
      if(NMLUuuUieh == true){NMLUuuUieh = false;}
      if(sBVxugaxZa == true){sBVxugaxZa = false;}
      if(FMpNnYehYF == true){FMpNnYehYF = false;}
      if(JGRIEQhjPg == true){JGRIEQhjPg = false;}
      if(FnJHybZNGB == true){FnJHybZNGB = false;}
      if(RYkfZBWyfV == true){RYkfZBWyfV = false;}
      if(QmJYXmiNre == true){QmJYXmiNre = false;}
      if(yqgrURChOL == true){yqgrURChOL = false;}
      if(zRbXnkVlhD == true){zRbXnkVlhD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WMSIEXHZLX
{ 
  void KAUfSNrkik()
  { 
      bool cfGfFrAJta = false;
      bool uQQotkMGDS = false;
      bool zcjegksKCL = false;
      bool nbPsjkVFUN = false;
      bool dtIyGrfKAh = false;
      bool ZRfQYzwayU = false;
      bool zpHilTAXEI = false;
      bool PHkpnEUkXo = false;
      bool EhJTlWuyTj = false;
      bool ntGAOnmYLm = false;
      bool qHFqSSfpbT = false;
      bool eKCJQQfmxP = false;
      bool XBDUUUAkaA = false;
      bool RuZkxwbSBS = false;
      bool pFWzEdqwix = false;
      bool HAbwOpEkWx = false;
      bool RtOaCikRMT = false;
      bool nMldYSeDPq = false;
      bool dDBcrRScWH = false;
      bool rquDBwpuxU = false;
      string nYnEqQbwLQ;
      string rglmrOtQqg;
      string GbYzoHtFJr;
      string qTctckywVY;
      string FEEAfRmlei;
      string dAPehLAnPi;
      string WWmSYXErKG;
      string QytRbBWXTW;
      string TIaZNpEyMQ;
      string kJglChRlbH;
      string NubXSfGxDf;
      string obUrPNwMFh;
      string TGesVGRIPs;
      string ikwMJYfCHh;
      string jGtfbIooWn;
      string lFgsmHPiCM;
      string NxhKwDfIhp;
      string hsFWyMLzRM;
      string RckaGdECYC;
      string IxAuTlYjiX;
      if(nYnEqQbwLQ == NubXSfGxDf){cfGfFrAJta = true;}
      else if(NubXSfGxDf == nYnEqQbwLQ){qHFqSSfpbT = true;}
      if(rglmrOtQqg == obUrPNwMFh){uQQotkMGDS = true;}
      else if(obUrPNwMFh == rglmrOtQqg){eKCJQQfmxP = true;}
      if(GbYzoHtFJr == TGesVGRIPs){zcjegksKCL = true;}
      else if(TGesVGRIPs == GbYzoHtFJr){XBDUUUAkaA = true;}
      if(qTctckywVY == ikwMJYfCHh){nbPsjkVFUN = true;}
      else if(ikwMJYfCHh == qTctckywVY){RuZkxwbSBS = true;}
      if(FEEAfRmlei == jGtfbIooWn){dtIyGrfKAh = true;}
      else if(jGtfbIooWn == FEEAfRmlei){pFWzEdqwix = true;}
      if(dAPehLAnPi == lFgsmHPiCM){ZRfQYzwayU = true;}
      else if(lFgsmHPiCM == dAPehLAnPi){HAbwOpEkWx = true;}
      if(WWmSYXErKG == NxhKwDfIhp){zpHilTAXEI = true;}
      else if(NxhKwDfIhp == WWmSYXErKG){RtOaCikRMT = true;}
      if(QytRbBWXTW == hsFWyMLzRM){PHkpnEUkXo = true;}
      if(TIaZNpEyMQ == RckaGdECYC){EhJTlWuyTj = true;}
      if(kJglChRlbH == IxAuTlYjiX){ntGAOnmYLm = true;}
      while(hsFWyMLzRM == QytRbBWXTW){nMldYSeDPq = true;}
      while(RckaGdECYC == RckaGdECYC){dDBcrRScWH = true;}
      while(IxAuTlYjiX == IxAuTlYjiX){rquDBwpuxU = true;}
      if(cfGfFrAJta == true){cfGfFrAJta = false;}
      if(uQQotkMGDS == true){uQQotkMGDS = false;}
      if(zcjegksKCL == true){zcjegksKCL = false;}
      if(nbPsjkVFUN == true){nbPsjkVFUN = false;}
      if(dtIyGrfKAh == true){dtIyGrfKAh = false;}
      if(ZRfQYzwayU == true){ZRfQYzwayU = false;}
      if(zpHilTAXEI == true){zpHilTAXEI = false;}
      if(PHkpnEUkXo == true){PHkpnEUkXo = false;}
      if(EhJTlWuyTj == true){EhJTlWuyTj = false;}
      if(ntGAOnmYLm == true){ntGAOnmYLm = false;}
      if(qHFqSSfpbT == true){qHFqSSfpbT = false;}
      if(eKCJQQfmxP == true){eKCJQQfmxP = false;}
      if(XBDUUUAkaA == true){XBDUUUAkaA = false;}
      if(RuZkxwbSBS == true){RuZkxwbSBS = false;}
      if(pFWzEdqwix == true){pFWzEdqwix = false;}
      if(HAbwOpEkWx == true){HAbwOpEkWx = false;}
      if(RtOaCikRMT == true){RtOaCikRMT = false;}
      if(nMldYSeDPq == true){nMldYSeDPq = false;}
      if(dDBcrRScWH == true){dDBcrRScWH = false;}
      if(rquDBwpuxU == true){rquDBwpuxU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKCRLQKSOT
{ 
  void xdhLCcJHwr()
  { 
      bool TcjtQpqpBH = false;
      bool ruSBRbmpKx = false;
      bool mAeRHDkRHJ = false;
      bool NORmnzSNes = false;
      bool TPSKTzZtis = false;
      bool CZBmkSxRmN = false;
      bool FYiqscceMR = false;
      bool IZKQcXhUyI = false;
      bool dqiNGmNeCV = false;
      bool BAaRntgbQp = false;
      bool VtgRkcOkJN = false;
      bool kcTdiNpUjG = false;
      bool PxcqPHysbi = false;
      bool pGEHliJRcc = false;
      bool XbVojYgwhZ = false;
      bool ELqKaYRoCc = false;
      bool eVJaWeYLqA = false;
      bool DYrGhmamHp = false;
      bool aBLBddOsgN = false;
      bool RUPzyCSuSE = false;
      string ifqTaHsYUP;
      string WZIkHYLRee;
      string TudUauEsTq;
      string mphqXguSVl;
      string KbZRzsKWga;
      string qypXUmCVre;
      string CzFccgrRNa;
      string cswsTqVLVg;
      string khMrzozKVj;
      string dZZpiLWwoS;
      string BsJGxyBxDc;
      string RpAKtUmMdm;
      string ggudwDSFKI;
      string UYVDfrXFtB;
      string mCGrRnZOwN;
      string XJSBkTxeJt;
      string fwltIsUweB;
      string wgRcAdaCLI;
      string cDIwjLFTRM;
      string tsuAVpQLjY;
      if(ifqTaHsYUP == BsJGxyBxDc){TcjtQpqpBH = true;}
      else if(BsJGxyBxDc == ifqTaHsYUP){VtgRkcOkJN = true;}
      if(WZIkHYLRee == RpAKtUmMdm){ruSBRbmpKx = true;}
      else if(RpAKtUmMdm == WZIkHYLRee){kcTdiNpUjG = true;}
      if(TudUauEsTq == ggudwDSFKI){mAeRHDkRHJ = true;}
      else if(ggudwDSFKI == TudUauEsTq){PxcqPHysbi = true;}
      if(mphqXguSVl == UYVDfrXFtB){NORmnzSNes = true;}
      else if(UYVDfrXFtB == mphqXguSVl){pGEHliJRcc = true;}
      if(KbZRzsKWga == mCGrRnZOwN){TPSKTzZtis = true;}
      else if(mCGrRnZOwN == KbZRzsKWga){XbVojYgwhZ = true;}
      if(qypXUmCVre == XJSBkTxeJt){CZBmkSxRmN = true;}
      else if(XJSBkTxeJt == qypXUmCVre){ELqKaYRoCc = true;}
      if(CzFccgrRNa == fwltIsUweB){FYiqscceMR = true;}
      else if(fwltIsUweB == CzFccgrRNa){eVJaWeYLqA = true;}
      if(cswsTqVLVg == wgRcAdaCLI){IZKQcXhUyI = true;}
      if(khMrzozKVj == cDIwjLFTRM){dqiNGmNeCV = true;}
      if(dZZpiLWwoS == tsuAVpQLjY){BAaRntgbQp = true;}
      while(wgRcAdaCLI == cswsTqVLVg){DYrGhmamHp = true;}
      while(cDIwjLFTRM == cDIwjLFTRM){aBLBddOsgN = true;}
      while(tsuAVpQLjY == tsuAVpQLjY){RUPzyCSuSE = true;}
      if(TcjtQpqpBH == true){TcjtQpqpBH = false;}
      if(ruSBRbmpKx == true){ruSBRbmpKx = false;}
      if(mAeRHDkRHJ == true){mAeRHDkRHJ = false;}
      if(NORmnzSNes == true){NORmnzSNes = false;}
      if(TPSKTzZtis == true){TPSKTzZtis = false;}
      if(CZBmkSxRmN == true){CZBmkSxRmN = false;}
      if(FYiqscceMR == true){FYiqscceMR = false;}
      if(IZKQcXhUyI == true){IZKQcXhUyI = false;}
      if(dqiNGmNeCV == true){dqiNGmNeCV = false;}
      if(BAaRntgbQp == true){BAaRntgbQp = false;}
      if(VtgRkcOkJN == true){VtgRkcOkJN = false;}
      if(kcTdiNpUjG == true){kcTdiNpUjG = false;}
      if(PxcqPHysbi == true){PxcqPHysbi = false;}
      if(pGEHliJRcc == true){pGEHliJRcc = false;}
      if(XbVojYgwhZ == true){XbVojYgwhZ = false;}
      if(ELqKaYRoCc == true){ELqKaYRoCc = false;}
      if(eVJaWeYLqA == true){eVJaWeYLqA = false;}
      if(DYrGhmamHp == true){DYrGhmamHp = false;}
      if(aBLBddOsgN == true){aBLBddOsgN = false;}
      if(RUPzyCSuSE == true){RUPzyCSuSE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKNDKIOINI
{ 
  void reRUtaCzUs()
  { 
      bool ZCATCcXkSm = false;
      bool dYQEUUUeWh = false;
      bool wVHGkkUxoH = false;
      bool eibxDAoNBV = false;
      bool DWhQayrkTO = false;
      bool DJgTGEushR = false;
      bool HZuKHtwSAU = false;
      bool fHdBdYnpfm = false;
      bool rjdZEVCIqz = false;
      bool FuejOdaWIf = false;
      bool BYjziwefog = false;
      bool PENtYWuUGl = false;
      bool rnbBPkbtlA = false;
      bool xRgAlTzeqH = false;
      bool pVTJiAhjKq = false;
      bool hGPWmMxiix = false;
      bool TksnjyWMIE = false;
      bool XQdzuVUSRO = false;
      bool DritSqBKMY = false;
      bool WPusnFbeYj = false;
      string UitNwhFqqM;
      string PrmitWcbJu;
      string EBFLcyLnqQ;
      string SOxtxyUfHo;
      string mJEzAaiKGq;
      string JfFPoTcikx;
      string VQzasBurlw;
      string CxTUIuwGLC;
      string PAhAGlIgEd;
      string UkuKSVJdFz;
      string epYKnMLkHt;
      string WWXhhVizTG;
      string rNnHbQBJBl;
      string kSALWYaXMt;
      string aXZKHxNMcx;
      string mKKzHRCRhX;
      string KCiVIEWLLI;
      string tKmYfTmcAd;
      string CogEyaIAEE;
      string WJoojXnEBC;
      if(UitNwhFqqM == epYKnMLkHt){ZCATCcXkSm = true;}
      else if(epYKnMLkHt == UitNwhFqqM){BYjziwefog = true;}
      if(PrmitWcbJu == WWXhhVizTG){dYQEUUUeWh = true;}
      else if(WWXhhVizTG == PrmitWcbJu){PENtYWuUGl = true;}
      if(EBFLcyLnqQ == rNnHbQBJBl){wVHGkkUxoH = true;}
      else if(rNnHbQBJBl == EBFLcyLnqQ){rnbBPkbtlA = true;}
      if(SOxtxyUfHo == kSALWYaXMt){eibxDAoNBV = true;}
      else if(kSALWYaXMt == SOxtxyUfHo){xRgAlTzeqH = true;}
      if(mJEzAaiKGq == aXZKHxNMcx){DWhQayrkTO = true;}
      else if(aXZKHxNMcx == mJEzAaiKGq){pVTJiAhjKq = true;}
      if(JfFPoTcikx == mKKzHRCRhX){DJgTGEushR = true;}
      else if(mKKzHRCRhX == JfFPoTcikx){hGPWmMxiix = true;}
      if(VQzasBurlw == KCiVIEWLLI){HZuKHtwSAU = true;}
      else if(KCiVIEWLLI == VQzasBurlw){TksnjyWMIE = true;}
      if(CxTUIuwGLC == tKmYfTmcAd){fHdBdYnpfm = true;}
      if(PAhAGlIgEd == CogEyaIAEE){rjdZEVCIqz = true;}
      if(UkuKSVJdFz == WJoojXnEBC){FuejOdaWIf = true;}
      while(tKmYfTmcAd == CxTUIuwGLC){XQdzuVUSRO = true;}
      while(CogEyaIAEE == CogEyaIAEE){DritSqBKMY = true;}
      while(WJoojXnEBC == WJoojXnEBC){WPusnFbeYj = true;}
      if(ZCATCcXkSm == true){ZCATCcXkSm = false;}
      if(dYQEUUUeWh == true){dYQEUUUeWh = false;}
      if(wVHGkkUxoH == true){wVHGkkUxoH = false;}
      if(eibxDAoNBV == true){eibxDAoNBV = false;}
      if(DWhQayrkTO == true){DWhQayrkTO = false;}
      if(DJgTGEushR == true){DJgTGEushR = false;}
      if(HZuKHtwSAU == true){HZuKHtwSAU = false;}
      if(fHdBdYnpfm == true){fHdBdYnpfm = false;}
      if(rjdZEVCIqz == true){rjdZEVCIqz = false;}
      if(FuejOdaWIf == true){FuejOdaWIf = false;}
      if(BYjziwefog == true){BYjziwefog = false;}
      if(PENtYWuUGl == true){PENtYWuUGl = false;}
      if(rnbBPkbtlA == true){rnbBPkbtlA = false;}
      if(xRgAlTzeqH == true){xRgAlTzeqH = false;}
      if(pVTJiAhjKq == true){pVTJiAhjKq = false;}
      if(hGPWmMxiix == true){hGPWmMxiix = false;}
      if(TksnjyWMIE == true){TksnjyWMIE = false;}
      if(XQdzuVUSRO == true){XQdzuVUSRO = false;}
      if(DritSqBKMY == true){DritSqBKMY = false;}
      if(WPusnFbeYj == true){WPusnFbeYj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVHHKHHFYR
{ 
  void lqrlbDVAVh()
  { 
      bool YitzcaLAAh = false;
      bool YoLrEWTWDc = false;
      bool LhfjjQwELW = false;
      bool aOAMwsIVZw = false;
      bool sPWDMaesUG = false;
      bool kCznfpCKPM = false;
      bool eHocHJozwK = false;
      bool NxxHjwKbWI = false;
      bool kDiElXOLgF = false;
      bool pyGMRlatwC = false;
      bool lfxKsmFqEi = false;
      bool eZmGbaXkqi = false;
      bool ucSpTOqjpy = false;
      bool VQfTVFFYKy = false;
      bool SWGxaPLzkp = false;
      bool NoCMHIMHpe = false;
      bool uUBGNNtTjW = false;
      bool VzarQXWVOD = false;
      bool DrzAjfOSLN = false;
      bool rxheDxVAiM = false;
      string cHGCqUtBJc;
      string nHWsNGHoFF;
      string zIKKoTIDyU;
      string GWVbUflauO;
      string gdVRDYUMsf;
      string YDGgyTxuNW;
      string MpDnWRluXh;
      string UfsqXVmsHP;
      string ywJRwCPncA;
      string ipNYCpagtk;
      string mZnLLrJPJc;
      string gEnxYQgkrT;
      string BxRXzdSUog;
      string tFyVbXHyGD;
      string sAeATeBPzk;
      string JpoaipHPMg;
      string ZnabhbFSVA;
      string IhdoaBRREU;
      string cDUDXEPWlk;
      string QqkZdEZDRq;
      if(cHGCqUtBJc == mZnLLrJPJc){YitzcaLAAh = true;}
      else if(mZnLLrJPJc == cHGCqUtBJc){lfxKsmFqEi = true;}
      if(nHWsNGHoFF == gEnxYQgkrT){YoLrEWTWDc = true;}
      else if(gEnxYQgkrT == nHWsNGHoFF){eZmGbaXkqi = true;}
      if(zIKKoTIDyU == BxRXzdSUog){LhfjjQwELW = true;}
      else if(BxRXzdSUog == zIKKoTIDyU){ucSpTOqjpy = true;}
      if(GWVbUflauO == tFyVbXHyGD){aOAMwsIVZw = true;}
      else if(tFyVbXHyGD == GWVbUflauO){VQfTVFFYKy = true;}
      if(gdVRDYUMsf == sAeATeBPzk){sPWDMaesUG = true;}
      else if(sAeATeBPzk == gdVRDYUMsf){SWGxaPLzkp = true;}
      if(YDGgyTxuNW == JpoaipHPMg){kCznfpCKPM = true;}
      else if(JpoaipHPMg == YDGgyTxuNW){NoCMHIMHpe = true;}
      if(MpDnWRluXh == ZnabhbFSVA){eHocHJozwK = true;}
      else if(ZnabhbFSVA == MpDnWRluXh){uUBGNNtTjW = true;}
      if(UfsqXVmsHP == IhdoaBRREU){NxxHjwKbWI = true;}
      if(ywJRwCPncA == cDUDXEPWlk){kDiElXOLgF = true;}
      if(ipNYCpagtk == QqkZdEZDRq){pyGMRlatwC = true;}
      while(IhdoaBRREU == UfsqXVmsHP){VzarQXWVOD = true;}
      while(cDUDXEPWlk == cDUDXEPWlk){DrzAjfOSLN = true;}
      while(QqkZdEZDRq == QqkZdEZDRq){rxheDxVAiM = true;}
      if(YitzcaLAAh == true){YitzcaLAAh = false;}
      if(YoLrEWTWDc == true){YoLrEWTWDc = false;}
      if(LhfjjQwELW == true){LhfjjQwELW = false;}
      if(aOAMwsIVZw == true){aOAMwsIVZw = false;}
      if(sPWDMaesUG == true){sPWDMaesUG = false;}
      if(kCznfpCKPM == true){kCznfpCKPM = false;}
      if(eHocHJozwK == true){eHocHJozwK = false;}
      if(NxxHjwKbWI == true){NxxHjwKbWI = false;}
      if(kDiElXOLgF == true){kDiElXOLgF = false;}
      if(pyGMRlatwC == true){pyGMRlatwC = false;}
      if(lfxKsmFqEi == true){lfxKsmFqEi = false;}
      if(eZmGbaXkqi == true){eZmGbaXkqi = false;}
      if(ucSpTOqjpy == true){ucSpTOqjpy = false;}
      if(VQfTVFFYKy == true){VQfTVFFYKy = false;}
      if(SWGxaPLzkp == true){SWGxaPLzkp = false;}
      if(NoCMHIMHpe == true){NoCMHIMHpe = false;}
      if(uUBGNNtTjW == true){uUBGNNtTjW = false;}
      if(VzarQXWVOD == true){VzarQXWVOD = false;}
      if(DrzAjfOSLN == true){DrzAjfOSLN = false;}
      if(rxheDxVAiM == true){rxheDxVAiM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTRIBPWLCU
{ 
  void RXzbqToqqr()
  { 
      bool GgzFfccbgK = false;
      bool knPnDbJqZo = false;
      bool hRHJikONae = false;
      bool rlcEDzdiFP = false;
      bool ohqTXAfZBd = false;
      bool tGoVxnZpVt = false;
      bool OPACSyKKkE = false;
      bool yakJzzanki = false;
      bool FoLxkkxGHP = false;
      bool ZmNKBYhnBZ = false;
      bool oUnxeTUeWx = false;
      bool MkFloZEDRg = false;
      bool BDDVeKMaIZ = false;
      bool RllLtjAOSR = false;
      bool QRjKCnhaVb = false;
      bool UeWUYkRSST = false;
      bool GtWweZztrE = false;
      bool YpkAQiTsSp = false;
      bool clEfFmPRlI = false;
      bool ShuyKVtmeb = false;
      string STFufkPhFU;
      string msiMktnqLA;
      string FjwlRoEHzw;
      string QTMiTAGKIW;
      string ElMFmBlAoY;
      string fyQNqiWSdq;
      string fHhJDTgAsj;
      string nciouTWqzP;
      string CDRZPRCyqj;
      string dmgRpwEDBS;
      string UkHEkDPbRX;
      string MfSNncpHtk;
      string QhIIGAwRzz;
      string OToguQuMoM;
      string CagTXxTScN;
      string GwJQBlczyj;
      string GycSIrqlSX;
      string gcSgipBojJ;
      string gdnksSKYeJ;
      string nuOFFDyOLe;
      if(STFufkPhFU == UkHEkDPbRX){GgzFfccbgK = true;}
      else if(UkHEkDPbRX == STFufkPhFU){oUnxeTUeWx = true;}
      if(msiMktnqLA == MfSNncpHtk){knPnDbJqZo = true;}
      else if(MfSNncpHtk == msiMktnqLA){MkFloZEDRg = true;}
      if(FjwlRoEHzw == QhIIGAwRzz){hRHJikONae = true;}
      else if(QhIIGAwRzz == FjwlRoEHzw){BDDVeKMaIZ = true;}
      if(QTMiTAGKIW == OToguQuMoM){rlcEDzdiFP = true;}
      else if(OToguQuMoM == QTMiTAGKIW){RllLtjAOSR = true;}
      if(ElMFmBlAoY == CagTXxTScN){ohqTXAfZBd = true;}
      else if(CagTXxTScN == ElMFmBlAoY){QRjKCnhaVb = true;}
      if(fyQNqiWSdq == GwJQBlczyj){tGoVxnZpVt = true;}
      else if(GwJQBlczyj == fyQNqiWSdq){UeWUYkRSST = true;}
      if(fHhJDTgAsj == GycSIrqlSX){OPACSyKKkE = true;}
      else if(GycSIrqlSX == fHhJDTgAsj){GtWweZztrE = true;}
      if(nciouTWqzP == gcSgipBojJ){yakJzzanki = true;}
      if(CDRZPRCyqj == gdnksSKYeJ){FoLxkkxGHP = true;}
      if(dmgRpwEDBS == nuOFFDyOLe){ZmNKBYhnBZ = true;}
      while(gcSgipBojJ == nciouTWqzP){YpkAQiTsSp = true;}
      while(gdnksSKYeJ == gdnksSKYeJ){clEfFmPRlI = true;}
      while(nuOFFDyOLe == nuOFFDyOLe){ShuyKVtmeb = true;}
      if(GgzFfccbgK == true){GgzFfccbgK = false;}
      if(knPnDbJqZo == true){knPnDbJqZo = false;}
      if(hRHJikONae == true){hRHJikONae = false;}
      if(rlcEDzdiFP == true){rlcEDzdiFP = false;}
      if(ohqTXAfZBd == true){ohqTXAfZBd = false;}
      if(tGoVxnZpVt == true){tGoVxnZpVt = false;}
      if(OPACSyKKkE == true){OPACSyKKkE = false;}
      if(yakJzzanki == true){yakJzzanki = false;}
      if(FoLxkkxGHP == true){FoLxkkxGHP = false;}
      if(ZmNKBYhnBZ == true){ZmNKBYhnBZ = false;}
      if(oUnxeTUeWx == true){oUnxeTUeWx = false;}
      if(MkFloZEDRg == true){MkFloZEDRg = false;}
      if(BDDVeKMaIZ == true){BDDVeKMaIZ = false;}
      if(RllLtjAOSR == true){RllLtjAOSR = false;}
      if(QRjKCnhaVb == true){QRjKCnhaVb = false;}
      if(UeWUYkRSST == true){UeWUYkRSST = false;}
      if(GtWweZztrE == true){GtWweZztrE = false;}
      if(YpkAQiTsSp == true){YpkAQiTsSp = false;}
      if(clEfFmPRlI == true){clEfFmPRlI = false;}
      if(ShuyKVtmeb == true){ShuyKVtmeb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKGQYEWLKU
{ 
  void GxTyTsGgsB()
  { 
      bool QaxnFgzDKX = false;
      bool ErdznhCSCW = false;
      bool hcYVeWjRaP = false;
      bool AgXkSbpFtb = false;
      bool fXIZgrSsJq = false;
      bool YcYwonCaJi = false;
      bool xhcuXXUsgL = false;
      bool rxYZpKUzol = false;
      bool EqHiqWIawe = false;
      bool ZOuKeyuNBJ = false;
      bool XYMyzaDyFd = false;
      bool SClXeFZsDA = false;
      bool OswCkdCOur = false;
      bool OHyfNeeJjQ = false;
      bool TJURLXbWfY = false;
      bool XBJBtebKMU = false;
      bool YoDNPLDGKz = false;
      bool aQJmgEXepN = false;
      bool BehVTNxxki = false;
      bool CUxOrdGHCz = false;
      string OynuyVbGqn;
      string PxOLOUlesK;
      string WpqyewFPSi;
      string Dxigxlddqr;
      string aHIDyWdrIj;
      string XiqPMYGoPC;
      string QLmHjROgOb;
      string qHmAiOgnzI;
      string RMHiLUFSTY;
      string enNobOTASg;
      string IxcfsPuqfx;
      string qRpHjDEEwP;
      string LuNpxCsyXT;
      string ufVSzUjbou;
      string YOmVhNyGEY;
      string KPECUNimiq;
      string VxSLCKwWIP;
      string TcPAqwIqIi;
      string DmtzJfbSxl;
      string kwrxZawaTW;
      if(OynuyVbGqn == IxcfsPuqfx){QaxnFgzDKX = true;}
      else if(IxcfsPuqfx == OynuyVbGqn){XYMyzaDyFd = true;}
      if(PxOLOUlesK == qRpHjDEEwP){ErdznhCSCW = true;}
      else if(qRpHjDEEwP == PxOLOUlesK){SClXeFZsDA = true;}
      if(WpqyewFPSi == LuNpxCsyXT){hcYVeWjRaP = true;}
      else if(LuNpxCsyXT == WpqyewFPSi){OswCkdCOur = true;}
      if(Dxigxlddqr == ufVSzUjbou){AgXkSbpFtb = true;}
      else if(ufVSzUjbou == Dxigxlddqr){OHyfNeeJjQ = true;}
      if(aHIDyWdrIj == YOmVhNyGEY){fXIZgrSsJq = true;}
      else if(YOmVhNyGEY == aHIDyWdrIj){TJURLXbWfY = true;}
      if(XiqPMYGoPC == KPECUNimiq){YcYwonCaJi = true;}
      else if(KPECUNimiq == XiqPMYGoPC){XBJBtebKMU = true;}
      if(QLmHjROgOb == VxSLCKwWIP){xhcuXXUsgL = true;}
      else if(VxSLCKwWIP == QLmHjROgOb){YoDNPLDGKz = true;}
      if(qHmAiOgnzI == TcPAqwIqIi){rxYZpKUzol = true;}
      if(RMHiLUFSTY == DmtzJfbSxl){EqHiqWIawe = true;}
      if(enNobOTASg == kwrxZawaTW){ZOuKeyuNBJ = true;}
      while(TcPAqwIqIi == qHmAiOgnzI){aQJmgEXepN = true;}
      while(DmtzJfbSxl == DmtzJfbSxl){BehVTNxxki = true;}
      while(kwrxZawaTW == kwrxZawaTW){CUxOrdGHCz = true;}
      if(QaxnFgzDKX == true){QaxnFgzDKX = false;}
      if(ErdznhCSCW == true){ErdznhCSCW = false;}
      if(hcYVeWjRaP == true){hcYVeWjRaP = false;}
      if(AgXkSbpFtb == true){AgXkSbpFtb = false;}
      if(fXIZgrSsJq == true){fXIZgrSsJq = false;}
      if(YcYwonCaJi == true){YcYwonCaJi = false;}
      if(xhcuXXUsgL == true){xhcuXXUsgL = false;}
      if(rxYZpKUzol == true){rxYZpKUzol = false;}
      if(EqHiqWIawe == true){EqHiqWIawe = false;}
      if(ZOuKeyuNBJ == true){ZOuKeyuNBJ = false;}
      if(XYMyzaDyFd == true){XYMyzaDyFd = false;}
      if(SClXeFZsDA == true){SClXeFZsDA = false;}
      if(OswCkdCOur == true){OswCkdCOur = false;}
      if(OHyfNeeJjQ == true){OHyfNeeJjQ = false;}
      if(TJURLXbWfY == true){TJURLXbWfY = false;}
      if(XBJBtebKMU == true){XBJBtebKMU = false;}
      if(YoDNPLDGKz == true){YoDNPLDGKz = false;}
      if(aQJmgEXepN == true){aQJmgEXepN = false;}
      if(BehVTNxxki == true){BehVTNxxki = false;}
      if(CUxOrdGHCz == true){CUxOrdGHCz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNXAQJBQPU
{ 
  void DrlopYJsBr()
  { 
      bool FpaRdHenCg = false;
      bool BXruzdfVai = false;
      bool KEibmnctma = false;
      bool rnHlPcHTaC = false;
      bool tPSSTpGyfY = false;
      bool ZxwNZAHzdo = false;
      bool ejBaoMQGeV = false;
      bool WMuXoukQHw = false;
      bool gdNOBtrtLO = false;
      bool VIokWJNrcG = false;
      bool ZASKBNCXYd = false;
      bool PqqhHAWlZu = false;
      bool TVtQAOXKAe = false;
      bool gsmAVgKDMm = false;
      bool qUVgzeQGcW = false;
      bool mbShmEFCKm = false;
      bool pqWsxVDpMa = false;
      bool pTYlDzANQU = false;
      bool xQhdrFaFNR = false;
      bool bIrYxAxbjc = false;
      string VNNmwRQCHg;
      string mNonzPAGXX;
      string ZBlrwVKGQO;
      string gmLmSmVrnc;
      string VQfpzhoIdF;
      string cnsbuTbUqZ;
      string GJkszzCBVM;
      string sIRtBIVusN;
      string fCbLkssiqy;
      string LABNWMelpz;
      string fmmRLUVyal;
      string yfbdtDgZHF;
      string GTKWBrGEXo;
      string diFsgrPKzQ;
      string XtHFAfYXTS;
      string eEejsMcPQS;
      string NRakIOZiwB;
      string nWZphLLEWV;
      string TikEKYDVzU;
      string OztfDGTWxk;
      if(VNNmwRQCHg == fmmRLUVyal){FpaRdHenCg = true;}
      else if(fmmRLUVyal == VNNmwRQCHg){ZASKBNCXYd = true;}
      if(mNonzPAGXX == yfbdtDgZHF){BXruzdfVai = true;}
      else if(yfbdtDgZHF == mNonzPAGXX){PqqhHAWlZu = true;}
      if(ZBlrwVKGQO == GTKWBrGEXo){KEibmnctma = true;}
      else if(GTKWBrGEXo == ZBlrwVKGQO){TVtQAOXKAe = true;}
      if(gmLmSmVrnc == diFsgrPKzQ){rnHlPcHTaC = true;}
      else if(diFsgrPKzQ == gmLmSmVrnc){gsmAVgKDMm = true;}
      if(VQfpzhoIdF == XtHFAfYXTS){tPSSTpGyfY = true;}
      else if(XtHFAfYXTS == VQfpzhoIdF){qUVgzeQGcW = true;}
      if(cnsbuTbUqZ == eEejsMcPQS){ZxwNZAHzdo = true;}
      else if(eEejsMcPQS == cnsbuTbUqZ){mbShmEFCKm = true;}
      if(GJkszzCBVM == NRakIOZiwB){ejBaoMQGeV = true;}
      else if(NRakIOZiwB == GJkszzCBVM){pqWsxVDpMa = true;}
      if(sIRtBIVusN == nWZphLLEWV){WMuXoukQHw = true;}
      if(fCbLkssiqy == TikEKYDVzU){gdNOBtrtLO = true;}
      if(LABNWMelpz == OztfDGTWxk){VIokWJNrcG = true;}
      while(nWZphLLEWV == sIRtBIVusN){pTYlDzANQU = true;}
      while(TikEKYDVzU == TikEKYDVzU){xQhdrFaFNR = true;}
      while(OztfDGTWxk == OztfDGTWxk){bIrYxAxbjc = true;}
      if(FpaRdHenCg == true){FpaRdHenCg = false;}
      if(BXruzdfVai == true){BXruzdfVai = false;}
      if(KEibmnctma == true){KEibmnctma = false;}
      if(rnHlPcHTaC == true){rnHlPcHTaC = false;}
      if(tPSSTpGyfY == true){tPSSTpGyfY = false;}
      if(ZxwNZAHzdo == true){ZxwNZAHzdo = false;}
      if(ejBaoMQGeV == true){ejBaoMQGeV = false;}
      if(WMuXoukQHw == true){WMuXoukQHw = false;}
      if(gdNOBtrtLO == true){gdNOBtrtLO = false;}
      if(VIokWJNrcG == true){VIokWJNrcG = false;}
      if(ZASKBNCXYd == true){ZASKBNCXYd = false;}
      if(PqqhHAWlZu == true){PqqhHAWlZu = false;}
      if(TVtQAOXKAe == true){TVtQAOXKAe = false;}
      if(gsmAVgKDMm == true){gsmAVgKDMm = false;}
      if(qUVgzeQGcW == true){qUVgzeQGcW = false;}
      if(mbShmEFCKm == true){mbShmEFCKm = false;}
      if(pqWsxVDpMa == true){pqWsxVDpMa = false;}
      if(pTYlDzANQU == true){pTYlDzANQU = false;}
      if(xQhdrFaFNR == true){xQhdrFaFNR = false;}
      if(bIrYxAxbjc == true){bIrYxAxbjc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQMMZXISJX
{ 
  void maLHDSeRis()
  { 
      bool XmESLeZjin = false;
      bool sHFScozHrN = false;
      bool TfsPnALhPK = false;
      bool DwRdbaVnSB = false;
      bool DeDBQhWsUF = false;
      bool wGpJlrsneL = false;
      bool SrTYkwoapC = false;
      bool TKnpJnbqzG = false;
      bool cSMKNwGIrj = false;
      bool ggJHiLLeQT = false;
      bool rwCSklSzzx = false;
      bool PCoYhAeJKn = false;
      bool pghFUmBfHy = false;
      bool cxaeNgPsYb = false;
      bool dHIuUeqjZh = false;
      bool fBTcdKNwxy = false;
      bool jlqBURaKLA = false;
      bool jlkiKiXmkp = false;
      bool uRGYRadyBC = false;
      bool SSuZqrPHZD = false;
      string zgaCedGfbP;
      string yPVFizUXTh;
      string ehHWEeBSof;
      string oVNbyJIhJN;
      string sSJcBMsUgU;
      string EZNxlQZDyz;
      string bnpuabCsGZ;
      string qmNFoLXeVq;
      string kglTbPIPoh;
      string jEjJkFbOBY;
      string KAOHdRLHIa;
      string sugGNuCVTL;
      string SlDYolCDUi;
      string iJcxgkRdpJ;
      string EBHOooXcwo;
      string CFtpGXwoRq;
      string OHlYqiRjYc;
      string cXfKHReojz;
      string OZHegcPlpJ;
      string ocLytwOhWF;
      if(zgaCedGfbP == KAOHdRLHIa){XmESLeZjin = true;}
      else if(KAOHdRLHIa == zgaCedGfbP){rwCSklSzzx = true;}
      if(yPVFizUXTh == sugGNuCVTL){sHFScozHrN = true;}
      else if(sugGNuCVTL == yPVFizUXTh){PCoYhAeJKn = true;}
      if(ehHWEeBSof == SlDYolCDUi){TfsPnALhPK = true;}
      else if(SlDYolCDUi == ehHWEeBSof){pghFUmBfHy = true;}
      if(oVNbyJIhJN == iJcxgkRdpJ){DwRdbaVnSB = true;}
      else if(iJcxgkRdpJ == oVNbyJIhJN){cxaeNgPsYb = true;}
      if(sSJcBMsUgU == EBHOooXcwo){DeDBQhWsUF = true;}
      else if(EBHOooXcwo == sSJcBMsUgU){dHIuUeqjZh = true;}
      if(EZNxlQZDyz == CFtpGXwoRq){wGpJlrsneL = true;}
      else if(CFtpGXwoRq == EZNxlQZDyz){fBTcdKNwxy = true;}
      if(bnpuabCsGZ == OHlYqiRjYc){SrTYkwoapC = true;}
      else if(OHlYqiRjYc == bnpuabCsGZ){jlqBURaKLA = true;}
      if(qmNFoLXeVq == cXfKHReojz){TKnpJnbqzG = true;}
      if(kglTbPIPoh == OZHegcPlpJ){cSMKNwGIrj = true;}
      if(jEjJkFbOBY == ocLytwOhWF){ggJHiLLeQT = true;}
      while(cXfKHReojz == qmNFoLXeVq){jlkiKiXmkp = true;}
      while(OZHegcPlpJ == OZHegcPlpJ){uRGYRadyBC = true;}
      while(ocLytwOhWF == ocLytwOhWF){SSuZqrPHZD = true;}
      if(XmESLeZjin == true){XmESLeZjin = false;}
      if(sHFScozHrN == true){sHFScozHrN = false;}
      if(TfsPnALhPK == true){TfsPnALhPK = false;}
      if(DwRdbaVnSB == true){DwRdbaVnSB = false;}
      if(DeDBQhWsUF == true){DeDBQhWsUF = false;}
      if(wGpJlrsneL == true){wGpJlrsneL = false;}
      if(SrTYkwoapC == true){SrTYkwoapC = false;}
      if(TKnpJnbqzG == true){TKnpJnbqzG = false;}
      if(cSMKNwGIrj == true){cSMKNwGIrj = false;}
      if(ggJHiLLeQT == true){ggJHiLLeQT = false;}
      if(rwCSklSzzx == true){rwCSklSzzx = false;}
      if(PCoYhAeJKn == true){PCoYhAeJKn = false;}
      if(pghFUmBfHy == true){pghFUmBfHy = false;}
      if(cxaeNgPsYb == true){cxaeNgPsYb = false;}
      if(dHIuUeqjZh == true){dHIuUeqjZh = false;}
      if(fBTcdKNwxy == true){fBTcdKNwxy = false;}
      if(jlqBURaKLA == true){jlqBURaKLA = false;}
      if(jlkiKiXmkp == true){jlkiKiXmkp = false;}
      if(uRGYRadyBC == true){uRGYRadyBC = false;}
      if(SSuZqrPHZD == true){SSuZqrPHZD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRAADULZKP
{ 
  void aSGQxihtgh()
  { 
      bool TRmaVXNpsQ = false;
      bool IIgJNAmVJa = false;
      bool EReCgbJhdh = false;
      bool EatRQoyxpA = false;
      bool MzmlZSASaV = false;
      bool YGiykCljtt = false;
      bool NfLKMhOPsY = false;
      bool CofINFdscN = false;
      bool bpHIJxrufO = false;
      bool CNDulgnbYr = false;
      bool DkZBTjZZkf = false;
      bool XsHfSXYDBO = false;
      bool pTieWnljWf = false;
      bool QBTjJpPFnY = false;
      bool XRJApIGWcO = false;
      bool IkaKCjBuee = false;
      bool yoCEOVYWVb = false;
      bool HSObpXJinN = false;
      bool hOHIXfaIhZ = false;
      bool nUaJahOFkT = false;
      string HtrEPdlOBf;
      string unHaSAYjCD;
      string FyyPedrFzj;
      string RQGZVfLsgx;
      string AeRVVBEnjP;
      string dYeRmIubYl;
      string kfOQNehgFm;
      string ofDECagcsd;
      string ZEViGskomM;
      string jiUuMUPAIq;
      string TWhxZxUZPL;
      string aSiuLfKfJT;
      string srtsCFLIrh;
      string KgUBJDWXII;
      string YLZakRzYif;
      string JjqnyabouU;
      string lMhgBtxhkH;
      string JlWAugSTHk;
      string GlYLXapfCh;
      string ahcnVMcrZp;
      if(HtrEPdlOBf == TWhxZxUZPL){TRmaVXNpsQ = true;}
      else if(TWhxZxUZPL == HtrEPdlOBf){DkZBTjZZkf = true;}
      if(unHaSAYjCD == aSiuLfKfJT){IIgJNAmVJa = true;}
      else if(aSiuLfKfJT == unHaSAYjCD){XsHfSXYDBO = true;}
      if(FyyPedrFzj == srtsCFLIrh){EReCgbJhdh = true;}
      else if(srtsCFLIrh == FyyPedrFzj){pTieWnljWf = true;}
      if(RQGZVfLsgx == KgUBJDWXII){EatRQoyxpA = true;}
      else if(KgUBJDWXII == RQGZVfLsgx){QBTjJpPFnY = true;}
      if(AeRVVBEnjP == YLZakRzYif){MzmlZSASaV = true;}
      else if(YLZakRzYif == AeRVVBEnjP){XRJApIGWcO = true;}
      if(dYeRmIubYl == JjqnyabouU){YGiykCljtt = true;}
      else if(JjqnyabouU == dYeRmIubYl){IkaKCjBuee = true;}
      if(kfOQNehgFm == lMhgBtxhkH){NfLKMhOPsY = true;}
      else if(lMhgBtxhkH == kfOQNehgFm){yoCEOVYWVb = true;}
      if(ofDECagcsd == JlWAugSTHk){CofINFdscN = true;}
      if(ZEViGskomM == GlYLXapfCh){bpHIJxrufO = true;}
      if(jiUuMUPAIq == ahcnVMcrZp){CNDulgnbYr = true;}
      while(JlWAugSTHk == ofDECagcsd){HSObpXJinN = true;}
      while(GlYLXapfCh == GlYLXapfCh){hOHIXfaIhZ = true;}
      while(ahcnVMcrZp == ahcnVMcrZp){nUaJahOFkT = true;}
      if(TRmaVXNpsQ == true){TRmaVXNpsQ = false;}
      if(IIgJNAmVJa == true){IIgJNAmVJa = false;}
      if(EReCgbJhdh == true){EReCgbJhdh = false;}
      if(EatRQoyxpA == true){EatRQoyxpA = false;}
      if(MzmlZSASaV == true){MzmlZSASaV = false;}
      if(YGiykCljtt == true){YGiykCljtt = false;}
      if(NfLKMhOPsY == true){NfLKMhOPsY = false;}
      if(CofINFdscN == true){CofINFdscN = false;}
      if(bpHIJxrufO == true){bpHIJxrufO = false;}
      if(CNDulgnbYr == true){CNDulgnbYr = false;}
      if(DkZBTjZZkf == true){DkZBTjZZkf = false;}
      if(XsHfSXYDBO == true){XsHfSXYDBO = false;}
      if(pTieWnljWf == true){pTieWnljWf = false;}
      if(QBTjJpPFnY == true){QBTjJpPFnY = false;}
      if(XRJApIGWcO == true){XRJApIGWcO = false;}
      if(IkaKCjBuee == true){IkaKCjBuee = false;}
      if(yoCEOVYWVb == true){yoCEOVYWVb = false;}
      if(HSObpXJinN == true){HSObpXJinN = false;}
      if(hOHIXfaIhZ == true){hOHIXfaIhZ = false;}
      if(nUaJahOFkT == true){nUaJahOFkT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGGWAKJSPH
{ 
  void OkAkcDxoEU()
  { 
      bool GwbbEqUjTe = false;
      bool RYZkmgaRfA = false;
      bool fQcCDXiqBP = false;
      bool scbGejkTub = false;
      bool WnNIYYLoye = false;
      bool erHttpTZXg = false;
      bool IdiDlnwTFC = false;
      bool uHWDcrCTde = false;
      bool MsrVjAVgLn = false;
      bool PLwNTsFKWj = false;
      bool bqiuiXVEQC = false;
      bool nAwsUOkMSk = false;
      bool SOHRmjLIjj = false;
      bool lqxtCUKxmM = false;
      bool eRPJAPOCsE = false;
      bool HrqkQMjRIy = false;
      bool LMTgPwCCpz = false;
      bool EnZFFByyRX = false;
      bool UIPebtAMco = false;
      bool krnnASxisD = false;
      string QNZjQPNgdq;
      string DHsqcckHCD;
      string zCduFaCsfd;
      string QNzSVKfQLb;
      string bfQQGtepgL;
      string wqFtzNiddo;
      string NTBAZoIaVS;
      string xUuabTlNoL;
      string wMMThZHESH;
      string aCmWNHePpQ;
      string lDTOObweSf;
      string bVnRsAHgSA;
      string gDINqthYMT;
      string nVXXYrrxFF;
      string dcllfFNUcN;
      string AxxpjiuGWT;
      string tWRyqFyQrB;
      string IJbMVEQWgl;
      string gMuzSqYhnp;
      string xkakLGKmta;
      if(QNZjQPNgdq == lDTOObweSf){GwbbEqUjTe = true;}
      else if(lDTOObweSf == QNZjQPNgdq){bqiuiXVEQC = true;}
      if(DHsqcckHCD == bVnRsAHgSA){RYZkmgaRfA = true;}
      else if(bVnRsAHgSA == DHsqcckHCD){nAwsUOkMSk = true;}
      if(zCduFaCsfd == gDINqthYMT){fQcCDXiqBP = true;}
      else if(gDINqthYMT == zCduFaCsfd){SOHRmjLIjj = true;}
      if(QNzSVKfQLb == nVXXYrrxFF){scbGejkTub = true;}
      else if(nVXXYrrxFF == QNzSVKfQLb){lqxtCUKxmM = true;}
      if(bfQQGtepgL == dcllfFNUcN){WnNIYYLoye = true;}
      else if(dcllfFNUcN == bfQQGtepgL){eRPJAPOCsE = true;}
      if(wqFtzNiddo == AxxpjiuGWT){erHttpTZXg = true;}
      else if(AxxpjiuGWT == wqFtzNiddo){HrqkQMjRIy = true;}
      if(NTBAZoIaVS == tWRyqFyQrB){IdiDlnwTFC = true;}
      else if(tWRyqFyQrB == NTBAZoIaVS){LMTgPwCCpz = true;}
      if(xUuabTlNoL == IJbMVEQWgl){uHWDcrCTde = true;}
      if(wMMThZHESH == gMuzSqYhnp){MsrVjAVgLn = true;}
      if(aCmWNHePpQ == xkakLGKmta){PLwNTsFKWj = true;}
      while(IJbMVEQWgl == xUuabTlNoL){EnZFFByyRX = true;}
      while(gMuzSqYhnp == gMuzSqYhnp){UIPebtAMco = true;}
      while(xkakLGKmta == xkakLGKmta){krnnASxisD = true;}
      if(GwbbEqUjTe == true){GwbbEqUjTe = false;}
      if(RYZkmgaRfA == true){RYZkmgaRfA = false;}
      if(fQcCDXiqBP == true){fQcCDXiqBP = false;}
      if(scbGejkTub == true){scbGejkTub = false;}
      if(WnNIYYLoye == true){WnNIYYLoye = false;}
      if(erHttpTZXg == true){erHttpTZXg = false;}
      if(IdiDlnwTFC == true){IdiDlnwTFC = false;}
      if(uHWDcrCTde == true){uHWDcrCTde = false;}
      if(MsrVjAVgLn == true){MsrVjAVgLn = false;}
      if(PLwNTsFKWj == true){PLwNTsFKWj = false;}
      if(bqiuiXVEQC == true){bqiuiXVEQC = false;}
      if(nAwsUOkMSk == true){nAwsUOkMSk = false;}
      if(SOHRmjLIjj == true){SOHRmjLIjj = false;}
      if(lqxtCUKxmM == true){lqxtCUKxmM = false;}
      if(eRPJAPOCsE == true){eRPJAPOCsE = false;}
      if(HrqkQMjRIy == true){HrqkQMjRIy = false;}
      if(LMTgPwCCpz == true){LMTgPwCCpz = false;}
      if(EnZFFByyRX == true){EnZFFByyRX = false;}
      if(UIPebtAMco == true){UIPebtAMco = false;}
      if(krnnASxisD == true){krnnASxisD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVWTSIMEFS
{ 
  void hiXrxRcUAL()
  { 
      bool yPPCLDXXFB = false;
      bool fIKTVXFlKf = false;
      bool DLeBLrsOxW = false;
      bool wDafTyuSUO = false;
      bool GppszEutUp = false;
      bool itJtUmjNpT = false;
      bool KJZhEcgeAW = false;
      bool bmQwYMUkCH = false;
      bool wytHmCsgLg = false;
      bool NhbBExQIoV = false;
      bool XQtxOwcMUH = false;
      bool RyLiWLOStB = false;
      bool iASSJtLPrb = false;
      bool wMwfjfExrq = false;
      bool YfLEOOWrdr = false;
      bool hyNmmWxamU = false;
      bool kNUsKECfzq = false;
      bool HRZDbCnODt = false;
      bool XSkzsyzIrM = false;
      bool hcJXFKLRtK = false;
      string llwdZZoWzt;
      string WZZCACJKsg;
      string GgMTEIdVjB;
      string fmCiHBNnoY;
      string lspGpunCKZ;
      string NsdAeEZbZQ;
      string uTmxOjWpuz;
      string nVUUtNpFdI;
      string UbLJnmICDC;
      string alNXcRFsrF;
      string YxGKkqXJFR;
      string OUxQwTHcJa;
      string bUmrYCIxqb;
      string HxMXjWUAYx;
      string PyxknFnxbJ;
      string KcjQdDJOli;
      string iaScKQHYgY;
      string yHELLcXBDS;
      string NLUgReNwtf;
      string MGNpNofTaX;
      if(llwdZZoWzt == YxGKkqXJFR){yPPCLDXXFB = true;}
      else if(YxGKkqXJFR == llwdZZoWzt){XQtxOwcMUH = true;}
      if(WZZCACJKsg == OUxQwTHcJa){fIKTVXFlKf = true;}
      else if(OUxQwTHcJa == WZZCACJKsg){RyLiWLOStB = true;}
      if(GgMTEIdVjB == bUmrYCIxqb){DLeBLrsOxW = true;}
      else if(bUmrYCIxqb == GgMTEIdVjB){iASSJtLPrb = true;}
      if(fmCiHBNnoY == HxMXjWUAYx){wDafTyuSUO = true;}
      else if(HxMXjWUAYx == fmCiHBNnoY){wMwfjfExrq = true;}
      if(lspGpunCKZ == PyxknFnxbJ){GppszEutUp = true;}
      else if(PyxknFnxbJ == lspGpunCKZ){YfLEOOWrdr = true;}
      if(NsdAeEZbZQ == KcjQdDJOli){itJtUmjNpT = true;}
      else if(KcjQdDJOli == NsdAeEZbZQ){hyNmmWxamU = true;}
      if(uTmxOjWpuz == iaScKQHYgY){KJZhEcgeAW = true;}
      else if(iaScKQHYgY == uTmxOjWpuz){kNUsKECfzq = true;}
      if(nVUUtNpFdI == yHELLcXBDS){bmQwYMUkCH = true;}
      if(UbLJnmICDC == NLUgReNwtf){wytHmCsgLg = true;}
      if(alNXcRFsrF == MGNpNofTaX){NhbBExQIoV = true;}
      while(yHELLcXBDS == nVUUtNpFdI){HRZDbCnODt = true;}
      while(NLUgReNwtf == NLUgReNwtf){XSkzsyzIrM = true;}
      while(MGNpNofTaX == MGNpNofTaX){hcJXFKLRtK = true;}
      if(yPPCLDXXFB == true){yPPCLDXXFB = false;}
      if(fIKTVXFlKf == true){fIKTVXFlKf = false;}
      if(DLeBLrsOxW == true){DLeBLrsOxW = false;}
      if(wDafTyuSUO == true){wDafTyuSUO = false;}
      if(GppszEutUp == true){GppszEutUp = false;}
      if(itJtUmjNpT == true){itJtUmjNpT = false;}
      if(KJZhEcgeAW == true){KJZhEcgeAW = false;}
      if(bmQwYMUkCH == true){bmQwYMUkCH = false;}
      if(wytHmCsgLg == true){wytHmCsgLg = false;}
      if(NhbBExQIoV == true){NhbBExQIoV = false;}
      if(XQtxOwcMUH == true){XQtxOwcMUH = false;}
      if(RyLiWLOStB == true){RyLiWLOStB = false;}
      if(iASSJtLPrb == true){iASSJtLPrb = false;}
      if(wMwfjfExrq == true){wMwfjfExrq = false;}
      if(YfLEOOWrdr == true){YfLEOOWrdr = false;}
      if(hyNmmWxamU == true){hyNmmWxamU = false;}
      if(kNUsKECfzq == true){kNUsKECfzq = false;}
      if(HRZDbCnODt == true){HRZDbCnODt = false;}
      if(XSkzsyzIrM == true){XSkzsyzIrM = false;}
      if(hcJXFKLRtK == true){hcJXFKLRtK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GENEUBOWCY
{ 
  void VxfdcoMZOP()
  { 
      bool OqiiZKuLpp = false;
      bool IYIksLXBry = false;
      bool iGpfMCVFkQ = false;
      bool MGWyGYGlVp = false;
      bool GaVDwICsew = false;
      bool XgpJTHACWX = false;
      bool opZYdCCKdU = false;
      bool EkeCrHjmjE = false;
      bool zbaosePMdy = false;
      bool YEOyBQBwYt = false;
      bool FrOKrlBnQM = false;
      bool WMSSYMOkey = false;
      bool lofeuAWgBb = false;
      bool GmNpyGMQwH = false;
      bool cbuRbLkwZn = false;
      bool BQRaHPLjOq = false;
      bool PUloFizcUR = false;
      bool zynXVJtODj = false;
      bool OZHMapVmhh = false;
      bool ucBFrIoGLr = false;
      string qyOBCtsSdI;
      string uCEMfqsWSg;
      string yfzBptFQVF;
      string cDzdyOGWPL;
      string XighGTRyYl;
      string iyoPrLzMLH;
      string obwYeqCZNR;
      string kVGGIOyRuV;
      string cGriVeOjll;
      string PsKHWwmHCO;
      string RqkHBMqhGc;
      string MhRpeijMCA;
      string bSnaCqKyjM;
      string bqOgEkUjhJ;
      string ngcIYgbUcn;
      string LZEClyDJFJ;
      string BsxtAVSkls;
      string NAdsLuoeBU;
      string PpUwBBlMtF;
      string gLdYHuiiID;
      if(qyOBCtsSdI == RqkHBMqhGc){OqiiZKuLpp = true;}
      else if(RqkHBMqhGc == qyOBCtsSdI){FrOKrlBnQM = true;}
      if(uCEMfqsWSg == MhRpeijMCA){IYIksLXBry = true;}
      else if(MhRpeijMCA == uCEMfqsWSg){WMSSYMOkey = true;}
      if(yfzBptFQVF == bSnaCqKyjM){iGpfMCVFkQ = true;}
      else if(bSnaCqKyjM == yfzBptFQVF){lofeuAWgBb = true;}
      if(cDzdyOGWPL == bqOgEkUjhJ){MGWyGYGlVp = true;}
      else if(bqOgEkUjhJ == cDzdyOGWPL){GmNpyGMQwH = true;}
      if(XighGTRyYl == ngcIYgbUcn){GaVDwICsew = true;}
      else if(ngcIYgbUcn == XighGTRyYl){cbuRbLkwZn = true;}
      if(iyoPrLzMLH == LZEClyDJFJ){XgpJTHACWX = true;}
      else if(LZEClyDJFJ == iyoPrLzMLH){BQRaHPLjOq = true;}
      if(obwYeqCZNR == BsxtAVSkls){opZYdCCKdU = true;}
      else if(BsxtAVSkls == obwYeqCZNR){PUloFizcUR = true;}
      if(kVGGIOyRuV == NAdsLuoeBU){EkeCrHjmjE = true;}
      if(cGriVeOjll == PpUwBBlMtF){zbaosePMdy = true;}
      if(PsKHWwmHCO == gLdYHuiiID){YEOyBQBwYt = true;}
      while(NAdsLuoeBU == kVGGIOyRuV){zynXVJtODj = true;}
      while(PpUwBBlMtF == PpUwBBlMtF){OZHMapVmhh = true;}
      while(gLdYHuiiID == gLdYHuiiID){ucBFrIoGLr = true;}
      if(OqiiZKuLpp == true){OqiiZKuLpp = false;}
      if(IYIksLXBry == true){IYIksLXBry = false;}
      if(iGpfMCVFkQ == true){iGpfMCVFkQ = false;}
      if(MGWyGYGlVp == true){MGWyGYGlVp = false;}
      if(GaVDwICsew == true){GaVDwICsew = false;}
      if(XgpJTHACWX == true){XgpJTHACWX = false;}
      if(opZYdCCKdU == true){opZYdCCKdU = false;}
      if(EkeCrHjmjE == true){EkeCrHjmjE = false;}
      if(zbaosePMdy == true){zbaosePMdy = false;}
      if(YEOyBQBwYt == true){YEOyBQBwYt = false;}
      if(FrOKrlBnQM == true){FrOKrlBnQM = false;}
      if(WMSSYMOkey == true){WMSSYMOkey = false;}
      if(lofeuAWgBb == true){lofeuAWgBb = false;}
      if(GmNpyGMQwH == true){GmNpyGMQwH = false;}
      if(cbuRbLkwZn == true){cbuRbLkwZn = false;}
      if(BQRaHPLjOq == true){BQRaHPLjOq = false;}
      if(PUloFizcUR == true){PUloFizcUR = false;}
      if(zynXVJtODj == true){zynXVJtODj = false;}
      if(OZHMapVmhh == true){OZHMapVmhh = false;}
      if(ucBFrIoGLr == true){ucBFrIoGLr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MDMZRWKUAH
{ 
  void MTzhsBVGOs()
  { 
      bool keLwRcgEmA = false;
      bool dGDCrusLWi = false;
      bool yRoIzjdQXD = false;
      bool NRSMInAswE = false;
      bool wfkYsQzBcU = false;
      bool aQPHcTpCwg = false;
      bool zPfilMnptD = false;
      bool tAOSlSfPPi = false;
      bool kcnDbwBKio = false;
      bool xywPFgzBlg = false;
      bool cIHYaaBxVK = false;
      bool mamNwVacHp = false;
      bool KcGEGwDzMF = false;
      bool TeciFbVObB = false;
      bool uEoYBVKhSi = false;
      bool FVtwVABCRd = false;
      bool WBjPqIxEIT = false;
      bool AMAGtGnhDj = false;
      bool kVfdAxjgNE = false;
      bool aSwydsTZhr = false;
      string ZqsRnNUndJ;
      string dPXhfffwFo;
      string uhpSxNuPOg;
      string hqdBNFwxGC;
      string AMBPVOyLtI;
      string ujwnqqBZTZ;
      string REZxamkWUa;
      string ihpDoigZxh;
      string PjUFkyupKV;
      string DWdfkumEoh;
      string cbpTYMtryH;
      string KbckKgiTLc;
      string ruLzWMEKSt;
      string wbkOFmtBgX;
      string ECqCKbsrUE;
      string LSrLphPqxL;
      string HiZELipNfX;
      string lhlnYpDJnt;
      string TMpNhcjYYW;
      string XCDUPUblpb;
      if(ZqsRnNUndJ == cbpTYMtryH){keLwRcgEmA = true;}
      else if(cbpTYMtryH == ZqsRnNUndJ){cIHYaaBxVK = true;}
      if(dPXhfffwFo == KbckKgiTLc){dGDCrusLWi = true;}
      else if(KbckKgiTLc == dPXhfffwFo){mamNwVacHp = true;}
      if(uhpSxNuPOg == ruLzWMEKSt){yRoIzjdQXD = true;}
      else if(ruLzWMEKSt == uhpSxNuPOg){KcGEGwDzMF = true;}
      if(hqdBNFwxGC == wbkOFmtBgX){NRSMInAswE = true;}
      else if(wbkOFmtBgX == hqdBNFwxGC){TeciFbVObB = true;}
      if(AMBPVOyLtI == ECqCKbsrUE){wfkYsQzBcU = true;}
      else if(ECqCKbsrUE == AMBPVOyLtI){uEoYBVKhSi = true;}
      if(ujwnqqBZTZ == LSrLphPqxL){aQPHcTpCwg = true;}
      else if(LSrLphPqxL == ujwnqqBZTZ){FVtwVABCRd = true;}
      if(REZxamkWUa == HiZELipNfX){zPfilMnptD = true;}
      else if(HiZELipNfX == REZxamkWUa){WBjPqIxEIT = true;}
      if(ihpDoigZxh == lhlnYpDJnt){tAOSlSfPPi = true;}
      if(PjUFkyupKV == TMpNhcjYYW){kcnDbwBKio = true;}
      if(DWdfkumEoh == XCDUPUblpb){xywPFgzBlg = true;}
      while(lhlnYpDJnt == ihpDoigZxh){AMAGtGnhDj = true;}
      while(TMpNhcjYYW == TMpNhcjYYW){kVfdAxjgNE = true;}
      while(XCDUPUblpb == XCDUPUblpb){aSwydsTZhr = true;}
      if(keLwRcgEmA == true){keLwRcgEmA = false;}
      if(dGDCrusLWi == true){dGDCrusLWi = false;}
      if(yRoIzjdQXD == true){yRoIzjdQXD = false;}
      if(NRSMInAswE == true){NRSMInAswE = false;}
      if(wfkYsQzBcU == true){wfkYsQzBcU = false;}
      if(aQPHcTpCwg == true){aQPHcTpCwg = false;}
      if(zPfilMnptD == true){zPfilMnptD = false;}
      if(tAOSlSfPPi == true){tAOSlSfPPi = false;}
      if(kcnDbwBKio == true){kcnDbwBKio = false;}
      if(xywPFgzBlg == true){xywPFgzBlg = false;}
      if(cIHYaaBxVK == true){cIHYaaBxVK = false;}
      if(mamNwVacHp == true){mamNwVacHp = false;}
      if(KcGEGwDzMF == true){KcGEGwDzMF = false;}
      if(TeciFbVObB == true){TeciFbVObB = false;}
      if(uEoYBVKhSi == true){uEoYBVKhSi = false;}
      if(FVtwVABCRd == true){FVtwVABCRd = false;}
      if(WBjPqIxEIT == true){WBjPqIxEIT = false;}
      if(AMAGtGnhDj == true){AMAGtGnhDj = false;}
      if(kVfdAxjgNE == true){kVfdAxjgNE = false;}
      if(aSwydsTZhr == true){aSwydsTZhr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YOIEYLBUON
{ 
  void PwyZOwqGRY()
  { 
      bool wNpbBVUZox = false;
      bool urnYsPPAVL = false;
      bool zGXpXbaYgd = false;
      bool EIhZdUowJG = false;
      bool aMXDeAfZcM = false;
      bool BmIjBppADY = false;
      bool tusLslKNtY = false;
      bool aSpPklhULX = false;
      bool wBuTcRAyYn = false;
      bool dosjMeTMJr = false;
      bool oReElhwsyP = false;
      bool IVoecszYia = false;
      bool lMoGtkZGDG = false;
      bool RUKSidVpht = false;
      bool VGzJfIzNHS = false;
      bool etdiFcbYKA = false;
      bool IpprxmKVwy = false;
      bool WIqnFeMfZk = false;
      bool kMyjaXpaNF = false;
      bool BxfgkfQHLs = false;
      string BWrQVbakIM;
      string fiNEHyoNuf;
      string OBXJeWpJBP;
      string EWQKwgfTXL;
      string lsLqoTFiRK;
      string FuDPnzyhky;
      string kQisHJSCIZ;
      string RVpisVpgUL;
      string RHqpJISAVw;
      string hyhYaUJSie;
      string BCZrsjETWS;
      string JRNZfcZsiy;
      string pRfMqSnQIX;
      string LWxoJOgzxZ;
      string EydClQkHsx;
      string uQjjoiVNAa;
      string wmLyHlTXQQ;
      string wZuJtqncZa;
      string hfXKbumNAZ;
      string sTzVcQmeuA;
      if(BWrQVbakIM == BCZrsjETWS){wNpbBVUZox = true;}
      else if(BCZrsjETWS == BWrQVbakIM){oReElhwsyP = true;}
      if(fiNEHyoNuf == JRNZfcZsiy){urnYsPPAVL = true;}
      else if(JRNZfcZsiy == fiNEHyoNuf){IVoecszYia = true;}
      if(OBXJeWpJBP == pRfMqSnQIX){zGXpXbaYgd = true;}
      else if(pRfMqSnQIX == OBXJeWpJBP){lMoGtkZGDG = true;}
      if(EWQKwgfTXL == LWxoJOgzxZ){EIhZdUowJG = true;}
      else if(LWxoJOgzxZ == EWQKwgfTXL){RUKSidVpht = true;}
      if(lsLqoTFiRK == EydClQkHsx){aMXDeAfZcM = true;}
      else if(EydClQkHsx == lsLqoTFiRK){VGzJfIzNHS = true;}
      if(FuDPnzyhky == uQjjoiVNAa){BmIjBppADY = true;}
      else if(uQjjoiVNAa == FuDPnzyhky){etdiFcbYKA = true;}
      if(kQisHJSCIZ == wmLyHlTXQQ){tusLslKNtY = true;}
      else if(wmLyHlTXQQ == kQisHJSCIZ){IpprxmKVwy = true;}
      if(RVpisVpgUL == wZuJtqncZa){aSpPklhULX = true;}
      if(RHqpJISAVw == hfXKbumNAZ){wBuTcRAyYn = true;}
      if(hyhYaUJSie == sTzVcQmeuA){dosjMeTMJr = true;}
      while(wZuJtqncZa == RVpisVpgUL){WIqnFeMfZk = true;}
      while(hfXKbumNAZ == hfXKbumNAZ){kMyjaXpaNF = true;}
      while(sTzVcQmeuA == sTzVcQmeuA){BxfgkfQHLs = true;}
      if(wNpbBVUZox == true){wNpbBVUZox = false;}
      if(urnYsPPAVL == true){urnYsPPAVL = false;}
      if(zGXpXbaYgd == true){zGXpXbaYgd = false;}
      if(EIhZdUowJG == true){EIhZdUowJG = false;}
      if(aMXDeAfZcM == true){aMXDeAfZcM = false;}
      if(BmIjBppADY == true){BmIjBppADY = false;}
      if(tusLslKNtY == true){tusLslKNtY = false;}
      if(aSpPklhULX == true){aSpPklhULX = false;}
      if(wBuTcRAyYn == true){wBuTcRAyYn = false;}
      if(dosjMeTMJr == true){dosjMeTMJr = false;}
      if(oReElhwsyP == true){oReElhwsyP = false;}
      if(IVoecszYia == true){IVoecszYia = false;}
      if(lMoGtkZGDG == true){lMoGtkZGDG = false;}
      if(RUKSidVpht == true){RUKSidVpht = false;}
      if(VGzJfIzNHS == true){VGzJfIzNHS = false;}
      if(etdiFcbYKA == true){etdiFcbYKA = false;}
      if(IpprxmKVwy == true){IpprxmKVwy = false;}
      if(WIqnFeMfZk == true){WIqnFeMfZk = false;}
      if(kMyjaXpaNF == true){kMyjaXpaNF = false;}
      if(BxfgkfQHLs == true){BxfgkfQHLs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBDFWOUHFI
{ 
  void ViMUOYDhhV()
  { 
      bool bYMNxwDeUD = false;
      bool iwPRerHMFc = false;
      bool iDVjknLckW = false;
      bool KwrcVPhmLN = false;
      bool wWtNJDsXXd = false;
      bool qNdhMXCbbJ = false;
      bool kZtyslDlwP = false;
      bool KTArgMJIZh = false;
      bool tmFGewSKQx = false;
      bool MFLCbVcuUX = false;
      bool zHaITXMkBz = false;
      bool NtCsOxUmTw = false;
      bool TsUyCEIyQK = false;
      bool jNnCilMxmH = false;
      bool jgJQjSDRnd = false;
      bool BpbXEFmbFP = false;
      bool OOUpPzGAKb = false;
      bool kXAMMljEOj = false;
      bool ApKlItlPyc = false;
      bool zjqWrVMSAj = false;
      string ilOwuCDDQA;
      string tSVGcXapap;
      string AHnxGVLhLP;
      string GqMfmRUQIg;
      string beINXBfQTV;
      string hpUmgbyQpZ;
      string pVrBsDFoTL;
      string DKhtOVyZYE;
      string ouNohPWYyL;
      string TDahpFlHTU;
      string wpxHSWIZYL;
      string cYrkjuHCSd;
      string ggpHrzjzEI;
      string iqFEIzyFVK;
      string HwAmhtLoyt;
      string yjnpnPzoPS;
      string mIVQblSmck;
      string xBfIVjfDZx;
      string ntBJKzCOQs;
      string zIpDWzZjKw;
      if(ilOwuCDDQA == wpxHSWIZYL){bYMNxwDeUD = true;}
      else if(wpxHSWIZYL == ilOwuCDDQA){zHaITXMkBz = true;}
      if(tSVGcXapap == cYrkjuHCSd){iwPRerHMFc = true;}
      else if(cYrkjuHCSd == tSVGcXapap){NtCsOxUmTw = true;}
      if(AHnxGVLhLP == ggpHrzjzEI){iDVjknLckW = true;}
      else if(ggpHrzjzEI == AHnxGVLhLP){TsUyCEIyQK = true;}
      if(GqMfmRUQIg == iqFEIzyFVK){KwrcVPhmLN = true;}
      else if(iqFEIzyFVK == GqMfmRUQIg){jNnCilMxmH = true;}
      if(beINXBfQTV == HwAmhtLoyt){wWtNJDsXXd = true;}
      else if(HwAmhtLoyt == beINXBfQTV){jgJQjSDRnd = true;}
      if(hpUmgbyQpZ == yjnpnPzoPS){qNdhMXCbbJ = true;}
      else if(yjnpnPzoPS == hpUmgbyQpZ){BpbXEFmbFP = true;}
      if(pVrBsDFoTL == mIVQblSmck){kZtyslDlwP = true;}
      else if(mIVQblSmck == pVrBsDFoTL){OOUpPzGAKb = true;}
      if(DKhtOVyZYE == xBfIVjfDZx){KTArgMJIZh = true;}
      if(ouNohPWYyL == ntBJKzCOQs){tmFGewSKQx = true;}
      if(TDahpFlHTU == zIpDWzZjKw){MFLCbVcuUX = true;}
      while(xBfIVjfDZx == DKhtOVyZYE){kXAMMljEOj = true;}
      while(ntBJKzCOQs == ntBJKzCOQs){ApKlItlPyc = true;}
      while(zIpDWzZjKw == zIpDWzZjKw){zjqWrVMSAj = true;}
      if(bYMNxwDeUD == true){bYMNxwDeUD = false;}
      if(iwPRerHMFc == true){iwPRerHMFc = false;}
      if(iDVjknLckW == true){iDVjknLckW = false;}
      if(KwrcVPhmLN == true){KwrcVPhmLN = false;}
      if(wWtNJDsXXd == true){wWtNJDsXXd = false;}
      if(qNdhMXCbbJ == true){qNdhMXCbbJ = false;}
      if(kZtyslDlwP == true){kZtyslDlwP = false;}
      if(KTArgMJIZh == true){KTArgMJIZh = false;}
      if(tmFGewSKQx == true){tmFGewSKQx = false;}
      if(MFLCbVcuUX == true){MFLCbVcuUX = false;}
      if(zHaITXMkBz == true){zHaITXMkBz = false;}
      if(NtCsOxUmTw == true){NtCsOxUmTw = false;}
      if(TsUyCEIyQK == true){TsUyCEIyQK = false;}
      if(jNnCilMxmH == true){jNnCilMxmH = false;}
      if(jgJQjSDRnd == true){jgJQjSDRnd = false;}
      if(BpbXEFmbFP == true){BpbXEFmbFP = false;}
      if(OOUpPzGAKb == true){OOUpPzGAKb = false;}
      if(kXAMMljEOj == true){kXAMMljEOj = false;}
      if(ApKlItlPyc == true){ApKlItlPyc = false;}
      if(zjqWrVMSAj == true){zjqWrVMSAj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFGGCXXEAQ
{ 
  void TSVuBepnKN()
  { 
      bool rlAgQCqiMV = false;
      bool XljrESedSo = false;
      bool ITfirtCHtg = false;
      bool SIhEeGwBKW = false;
      bool WibkaOmWyf = false;
      bool mmeZdXFQnV = false;
      bool ziofCODeNy = false;
      bool VdSwSZruId = false;
      bool HeINtecHZG = false;
      bool AfMoWmtuiL = false;
      bool KHJAKIUiHE = false;
      bool fKIJNUZalW = false;
      bool lwEHxpQcYe = false;
      bool ewLwTAVICk = false;
      bool KtAVZpWDaC = false;
      bool MSJMZOCCCU = false;
      bool rrKbZiyLpN = false;
      bool yRYBLruigH = false;
      bool SNCVRMmzWE = false;
      bool xSFhrRiXuq = false;
      string fKGUDPGmmO;
      string ECnfqocdOx;
      string LdLfFoMoPX;
      string iLcjmJzGRD;
      string jizUGBEcVC;
      string QhZzwBzZON;
      string CRWPesZErh;
      string pWLKMbepZE;
      string jjTMHBlcmk;
      string JYrDASLjpN;
      string aAjnMsVOlT;
      string WIAKcRyKHd;
      string HxQHXQdIJt;
      string PuAMcjAfzN;
      string eWpTOAYhZh;
      string UBcLFdicPw;
      string ONFrDaImgs;
      string RSKsyjGxrW;
      string rwhbYNSnGy;
      string AXPDzRRyPm;
      if(fKGUDPGmmO == aAjnMsVOlT){rlAgQCqiMV = true;}
      else if(aAjnMsVOlT == fKGUDPGmmO){KHJAKIUiHE = true;}
      if(ECnfqocdOx == WIAKcRyKHd){XljrESedSo = true;}
      else if(WIAKcRyKHd == ECnfqocdOx){fKIJNUZalW = true;}
      if(LdLfFoMoPX == HxQHXQdIJt){ITfirtCHtg = true;}
      else if(HxQHXQdIJt == LdLfFoMoPX){lwEHxpQcYe = true;}
      if(iLcjmJzGRD == PuAMcjAfzN){SIhEeGwBKW = true;}
      else if(PuAMcjAfzN == iLcjmJzGRD){ewLwTAVICk = true;}
      if(jizUGBEcVC == eWpTOAYhZh){WibkaOmWyf = true;}
      else if(eWpTOAYhZh == jizUGBEcVC){KtAVZpWDaC = true;}
      if(QhZzwBzZON == UBcLFdicPw){mmeZdXFQnV = true;}
      else if(UBcLFdicPw == QhZzwBzZON){MSJMZOCCCU = true;}
      if(CRWPesZErh == ONFrDaImgs){ziofCODeNy = true;}
      else if(ONFrDaImgs == CRWPesZErh){rrKbZiyLpN = true;}
      if(pWLKMbepZE == RSKsyjGxrW){VdSwSZruId = true;}
      if(jjTMHBlcmk == rwhbYNSnGy){HeINtecHZG = true;}
      if(JYrDASLjpN == AXPDzRRyPm){AfMoWmtuiL = true;}
      while(RSKsyjGxrW == pWLKMbepZE){yRYBLruigH = true;}
      while(rwhbYNSnGy == rwhbYNSnGy){SNCVRMmzWE = true;}
      while(AXPDzRRyPm == AXPDzRRyPm){xSFhrRiXuq = true;}
      if(rlAgQCqiMV == true){rlAgQCqiMV = false;}
      if(XljrESedSo == true){XljrESedSo = false;}
      if(ITfirtCHtg == true){ITfirtCHtg = false;}
      if(SIhEeGwBKW == true){SIhEeGwBKW = false;}
      if(WibkaOmWyf == true){WibkaOmWyf = false;}
      if(mmeZdXFQnV == true){mmeZdXFQnV = false;}
      if(ziofCODeNy == true){ziofCODeNy = false;}
      if(VdSwSZruId == true){VdSwSZruId = false;}
      if(HeINtecHZG == true){HeINtecHZG = false;}
      if(AfMoWmtuiL == true){AfMoWmtuiL = false;}
      if(KHJAKIUiHE == true){KHJAKIUiHE = false;}
      if(fKIJNUZalW == true){fKIJNUZalW = false;}
      if(lwEHxpQcYe == true){lwEHxpQcYe = false;}
      if(ewLwTAVICk == true){ewLwTAVICk = false;}
      if(KtAVZpWDaC == true){KtAVZpWDaC = false;}
      if(MSJMZOCCCU == true){MSJMZOCCCU = false;}
      if(rrKbZiyLpN == true){rrKbZiyLpN = false;}
      if(yRYBLruigH == true){yRYBLruigH = false;}
      if(SNCVRMmzWE == true){SNCVRMmzWE = false;}
      if(xSFhrRiXuq == true){xSFhrRiXuq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOHCQKUQLV
{ 
  void KjIlbZjTsu()
  { 
      bool xyGHynGtgw = false;
      bool BxkZaMpMjY = false;
      bool fVGGXgrdVr = false;
      bool RtuMaqQBFu = false;
      bool hDALEbENnN = false;
      bool dcEiDarziR = false;
      bool wbXodHCYzi = false;
      bool woGnpbVtCw = false;
      bool bdpHNopLJz = false;
      bool zQRnzGeLgw = false;
      bool ZfOERoVPsa = false;
      bool FyxmoRlQan = false;
      bool QpOzjeWSoj = false;
      bool xJMFWuPlpX = false;
      bool TaRisBTeyh = false;
      bool UOjrfiQOUm = false;
      bool RDaJdukqPs = false;
      bool BzZCUpXfGi = false;
      bool KrTHPhZTYn = false;
      bool eBRCGPAIFx = false;
      string pTIqBMLoPz;
      string iWpiOmGuRI;
      string NgnDTbAjPW;
      string layppKtsDb;
      string PzrmZAZjaN;
      string lEeRRIfFWZ;
      string LbZrNIXzrD;
      string rMqorNoBdS;
      string BQIBjgugYh;
      string eoWcQnYzZQ;
      string barWUZNoYD;
      string TeaDXuSYHf;
      string MqZKYDpNYE;
      string ooaMqaXlfK;
      string TFIVNANSFU;
      string UzqsEkBhyQ;
      string jzQTNdDOMx;
      string WfsxMHiDwX;
      string pWIDjoygIG;
      string YpnOaUonIi;
      if(pTIqBMLoPz == barWUZNoYD){xyGHynGtgw = true;}
      else if(barWUZNoYD == pTIqBMLoPz){ZfOERoVPsa = true;}
      if(iWpiOmGuRI == TeaDXuSYHf){BxkZaMpMjY = true;}
      else if(TeaDXuSYHf == iWpiOmGuRI){FyxmoRlQan = true;}
      if(NgnDTbAjPW == MqZKYDpNYE){fVGGXgrdVr = true;}
      else if(MqZKYDpNYE == NgnDTbAjPW){QpOzjeWSoj = true;}
      if(layppKtsDb == ooaMqaXlfK){RtuMaqQBFu = true;}
      else if(ooaMqaXlfK == layppKtsDb){xJMFWuPlpX = true;}
      if(PzrmZAZjaN == TFIVNANSFU){hDALEbENnN = true;}
      else if(TFIVNANSFU == PzrmZAZjaN){TaRisBTeyh = true;}
      if(lEeRRIfFWZ == UzqsEkBhyQ){dcEiDarziR = true;}
      else if(UzqsEkBhyQ == lEeRRIfFWZ){UOjrfiQOUm = true;}
      if(LbZrNIXzrD == jzQTNdDOMx){wbXodHCYzi = true;}
      else if(jzQTNdDOMx == LbZrNIXzrD){RDaJdukqPs = true;}
      if(rMqorNoBdS == WfsxMHiDwX){woGnpbVtCw = true;}
      if(BQIBjgugYh == pWIDjoygIG){bdpHNopLJz = true;}
      if(eoWcQnYzZQ == YpnOaUonIi){zQRnzGeLgw = true;}
      while(WfsxMHiDwX == rMqorNoBdS){BzZCUpXfGi = true;}
      while(pWIDjoygIG == pWIDjoygIG){KrTHPhZTYn = true;}
      while(YpnOaUonIi == YpnOaUonIi){eBRCGPAIFx = true;}
      if(xyGHynGtgw == true){xyGHynGtgw = false;}
      if(BxkZaMpMjY == true){BxkZaMpMjY = false;}
      if(fVGGXgrdVr == true){fVGGXgrdVr = false;}
      if(RtuMaqQBFu == true){RtuMaqQBFu = false;}
      if(hDALEbENnN == true){hDALEbENnN = false;}
      if(dcEiDarziR == true){dcEiDarziR = false;}
      if(wbXodHCYzi == true){wbXodHCYzi = false;}
      if(woGnpbVtCw == true){woGnpbVtCw = false;}
      if(bdpHNopLJz == true){bdpHNopLJz = false;}
      if(zQRnzGeLgw == true){zQRnzGeLgw = false;}
      if(ZfOERoVPsa == true){ZfOERoVPsa = false;}
      if(FyxmoRlQan == true){FyxmoRlQan = false;}
      if(QpOzjeWSoj == true){QpOzjeWSoj = false;}
      if(xJMFWuPlpX == true){xJMFWuPlpX = false;}
      if(TaRisBTeyh == true){TaRisBTeyh = false;}
      if(UOjrfiQOUm == true){UOjrfiQOUm = false;}
      if(RDaJdukqPs == true){RDaJdukqPs = false;}
      if(BzZCUpXfGi == true){BzZCUpXfGi = false;}
      if(KrTHPhZTYn == true){KrTHPhZTYn = false;}
      if(eBRCGPAIFx == true){eBRCGPAIFx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQVVOMKWBU
{ 
  void MJgVAxQMlW()
  { 
      bool iErEPuOtsi = false;
      bool AOoIBzPYMr = false;
      bool LbxynTtcnK = false;
      bool nBREZVfVDL = false;
      bool ijVkpYrYQg = false;
      bool NVPtRGGsPu = false;
      bool AkGhtyxjhf = false;
      bool TsUBIbFLIO = false;
      bool bULGwSlWmT = false;
      bool OlFIKxdnpq = false;
      bool bHqkNTAOko = false;
      bool AukBSfZAkb = false;
      bool MZxORgmMpL = false;
      bool yRUQmUcarb = false;
      bool RXlxSTAEoe = false;
      bool XdCOeBJcTg = false;
      bool gnXZqiZUOy = false;
      bool CzHIKonAux = false;
      bool fiWLmUOGlk = false;
      bool LAHLudzLFj = false;
      string CnduSndQRa;
      string goqcpYbqIE;
      string OiLzGWGBJI;
      string wuThWrDfPD;
      string bGzWYcLdAr;
      string ZagZFTcdnw;
      string hcHJekVJFy;
      string UwbFbHioad;
      string KcBRiUOtbD;
      string OZqSVyzpqn;
      string HBYBWczbxy;
      string jnDKkFbpaJ;
      string VbhBjuEIic;
      string HsxlVIDztF;
      string UmwcTZVggQ;
      string WJPhRfTWRa;
      string XqrTppqRnc;
      string BbuUoieEhJ;
      string ZXaSGxdOTp;
      string nghSgdtcmc;
      if(CnduSndQRa == HBYBWczbxy){iErEPuOtsi = true;}
      else if(HBYBWczbxy == CnduSndQRa){bHqkNTAOko = true;}
      if(goqcpYbqIE == jnDKkFbpaJ){AOoIBzPYMr = true;}
      else if(jnDKkFbpaJ == goqcpYbqIE){AukBSfZAkb = true;}
      if(OiLzGWGBJI == VbhBjuEIic){LbxynTtcnK = true;}
      else if(VbhBjuEIic == OiLzGWGBJI){MZxORgmMpL = true;}
      if(wuThWrDfPD == HsxlVIDztF){nBREZVfVDL = true;}
      else if(HsxlVIDztF == wuThWrDfPD){yRUQmUcarb = true;}
      if(bGzWYcLdAr == UmwcTZVggQ){ijVkpYrYQg = true;}
      else if(UmwcTZVggQ == bGzWYcLdAr){RXlxSTAEoe = true;}
      if(ZagZFTcdnw == WJPhRfTWRa){NVPtRGGsPu = true;}
      else if(WJPhRfTWRa == ZagZFTcdnw){XdCOeBJcTg = true;}
      if(hcHJekVJFy == XqrTppqRnc){AkGhtyxjhf = true;}
      else if(XqrTppqRnc == hcHJekVJFy){gnXZqiZUOy = true;}
      if(UwbFbHioad == BbuUoieEhJ){TsUBIbFLIO = true;}
      if(KcBRiUOtbD == ZXaSGxdOTp){bULGwSlWmT = true;}
      if(OZqSVyzpqn == nghSgdtcmc){OlFIKxdnpq = true;}
      while(BbuUoieEhJ == UwbFbHioad){CzHIKonAux = true;}
      while(ZXaSGxdOTp == ZXaSGxdOTp){fiWLmUOGlk = true;}
      while(nghSgdtcmc == nghSgdtcmc){LAHLudzLFj = true;}
      if(iErEPuOtsi == true){iErEPuOtsi = false;}
      if(AOoIBzPYMr == true){AOoIBzPYMr = false;}
      if(LbxynTtcnK == true){LbxynTtcnK = false;}
      if(nBREZVfVDL == true){nBREZVfVDL = false;}
      if(ijVkpYrYQg == true){ijVkpYrYQg = false;}
      if(NVPtRGGsPu == true){NVPtRGGsPu = false;}
      if(AkGhtyxjhf == true){AkGhtyxjhf = false;}
      if(TsUBIbFLIO == true){TsUBIbFLIO = false;}
      if(bULGwSlWmT == true){bULGwSlWmT = false;}
      if(OlFIKxdnpq == true){OlFIKxdnpq = false;}
      if(bHqkNTAOko == true){bHqkNTAOko = false;}
      if(AukBSfZAkb == true){AukBSfZAkb = false;}
      if(MZxORgmMpL == true){MZxORgmMpL = false;}
      if(yRUQmUcarb == true){yRUQmUcarb = false;}
      if(RXlxSTAEoe == true){RXlxSTAEoe = false;}
      if(XdCOeBJcTg == true){XdCOeBJcTg = false;}
      if(gnXZqiZUOy == true){gnXZqiZUOy = false;}
      if(CzHIKonAux == true){CzHIKonAux = false;}
      if(fiWLmUOGlk == true){fiWLmUOGlk = false;}
      if(LAHLudzLFj == true){LAHLudzLFj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYXWRZHXJS
{ 
  void CFgOnZJqZt()
  { 
      bool MzDGeJVkXt = false;
      bool idlNPUijWb = false;
      bool nhxGmAhQYh = false;
      bool DpiZATeuVE = false;
      bool ormnmNamqn = false;
      bool CfqQOdBwSd = false;
      bool bFLppruMMu = false;
      bool onORmutJSY = false;
      bool ZtYjfXzSLW = false;
      bool Rhbqcjfxyu = false;
      bool SOZwyNRYdS = false;
      bool irdsEggaKS = false;
      bool rbApcHLWoD = false;
      bool OxLWFKUblR = false;
      bool GZnrmZEhlw = false;
      bool CEmeCqNjSq = false;
      bool CtjaElgGnt = false;
      bool MEorLRnIDD = false;
      bool CcjsAJKfUO = false;
      bool wjJtOLpNmB = false;
      string kmhQHYVCNL;
      string xcMuHdnRDr;
      string HHFWeMnnPj;
      string ZtldNkVFLW;
      string jttTnfxwQq;
      string CdMyFchLlt;
      string jgldkDphhV;
      string IiFgIMNkhz;
      string OrWXgugnYj;
      string CJTRlCHPhk;
      string oPNthTYfpr;
      string PxdmerKNwp;
      string VCIyTzPntF;
      string ExDxJzdbpN;
      string WByfUFfgls;
      string qsTrOmGPai;
      string DkkjmRsfcf;
      string OhXiTTEbcN;
      string SiBANKdLiW;
      string rNAHJkQNsC;
      if(kmhQHYVCNL == oPNthTYfpr){MzDGeJVkXt = true;}
      else if(oPNthTYfpr == kmhQHYVCNL){SOZwyNRYdS = true;}
      if(xcMuHdnRDr == PxdmerKNwp){idlNPUijWb = true;}
      else if(PxdmerKNwp == xcMuHdnRDr){irdsEggaKS = true;}
      if(HHFWeMnnPj == VCIyTzPntF){nhxGmAhQYh = true;}
      else if(VCIyTzPntF == HHFWeMnnPj){rbApcHLWoD = true;}
      if(ZtldNkVFLW == ExDxJzdbpN){DpiZATeuVE = true;}
      else if(ExDxJzdbpN == ZtldNkVFLW){OxLWFKUblR = true;}
      if(jttTnfxwQq == WByfUFfgls){ormnmNamqn = true;}
      else if(WByfUFfgls == jttTnfxwQq){GZnrmZEhlw = true;}
      if(CdMyFchLlt == qsTrOmGPai){CfqQOdBwSd = true;}
      else if(qsTrOmGPai == CdMyFchLlt){CEmeCqNjSq = true;}
      if(jgldkDphhV == DkkjmRsfcf){bFLppruMMu = true;}
      else if(DkkjmRsfcf == jgldkDphhV){CtjaElgGnt = true;}
      if(IiFgIMNkhz == OhXiTTEbcN){onORmutJSY = true;}
      if(OrWXgugnYj == SiBANKdLiW){ZtYjfXzSLW = true;}
      if(CJTRlCHPhk == rNAHJkQNsC){Rhbqcjfxyu = true;}
      while(OhXiTTEbcN == IiFgIMNkhz){MEorLRnIDD = true;}
      while(SiBANKdLiW == SiBANKdLiW){CcjsAJKfUO = true;}
      while(rNAHJkQNsC == rNAHJkQNsC){wjJtOLpNmB = true;}
      if(MzDGeJVkXt == true){MzDGeJVkXt = false;}
      if(idlNPUijWb == true){idlNPUijWb = false;}
      if(nhxGmAhQYh == true){nhxGmAhQYh = false;}
      if(DpiZATeuVE == true){DpiZATeuVE = false;}
      if(ormnmNamqn == true){ormnmNamqn = false;}
      if(CfqQOdBwSd == true){CfqQOdBwSd = false;}
      if(bFLppruMMu == true){bFLppruMMu = false;}
      if(onORmutJSY == true){onORmutJSY = false;}
      if(ZtYjfXzSLW == true){ZtYjfXzSLW = false;}
      if(Rhbqcjfxyu == true){Rhbqcjfxyu = false;}
      if(SOZwyNRYdS == true){SOZwyNRYdS = false;}
      if(irdsEggaKS == true){irdsEggaKS = false;}
      if(rbApcHLWoD == true){rbApcHLWoD = false;}
      if(OxLWFKUblR == true){OxLWFKUblR = false;}
      if(GZnrmZEhlw == true){GZnrmZEhlw = false;}
      if(CEmeCqNjSq == true){CEmeCqNjSq = false;}
      if(CtjaElgGnt == true){CtjaElgGnt = false;}
      if(MEorLRnIDD == true){MEorLRnIDD = false;}
      if(CcjsAJKfUO == true){CcjsAJKfUO = false;}
      if(wjJtOLpNmB == true){wjJtOLpNmB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJOYBDNOFF
{ 
  void MIPBYPMRuV()
  { 
      bool jPStlhzpot = false;
      bool HhnctWsVIx = false;
      bool plsKiTxEKX = false;
      bool blyZkNxkfc = false;
      bool DVXSOPmNNn = false;
      bool GeiKVxVILS = false;
      bool kufQSVjOrf = false;
      bool YHoetUNauS = false;
      bool fjpVRwDnEm = false;
      bool qoZNqIoHzs = false;
      bool fYVgPypDPB = false;
      bool jtMrlBEKyW = false;
      bool RuJEnihbnl = false;
      bool eGbCmHNIGT = false;
      bool GAXDDxcgap = false;
      bool DeIbbjOQsf = false;
      bool QNPdVdSKEe = false;
      bool mwDeQQWGBq = false;
      bool GABxiAxzZC = false;
      bool rxPaDrksgZ = false;
      string lAeiubVgmu;
      string xnpOcqZQnp;
      string QGrNJhzElQ;
      string sznEVPeRKH;
      string NyCKmZpUOi;
      string NmUdgfHRZN;
      string bQtWCxzlrM;
      string MIFfcSEhai;
      string reoCCFeKWp;
      string INqxewDfIp;
      string ZEbBWEgoAO;
      string aYqpUxarTw;
      string SnOBEzQIAg;
      string OYZjImCmfy;
      string YoKIOiVAbh;
      string VLLMXloaxX;
      string mYnTACzGhg;
      string umMUXcdGlU;
      string cQfSKCMNMW;
      string ybpIKzBqHL;
      if(lAeiubVgmu == ZEbBWEgoAO){jPStlhzpot = true;}
      else if(ZEbBWEgoAO == lAeiubVgmu){fYVgPypDPB = true;}
      if(xnpOcqZQnp == aYqpUxarTw){HhnctWsVIx = true;}
      else if(aYqpUxarTw == xnpOcqZQnp){jtMrlBEKyW = true;}
      if(QGrNJhzElQ == SnOBEzQIAg){plsKiTxEKX = true;}
      else if(SnOBEzQIAg == QGrNJhzElQ){RuJEnihbnl = true;}
      if(sznEVPeRKH == OYZjImCmfy){blyZkNxkfc = true;}
      else if(OYZjImCmfy == sznEVPeRKH){eGbCmHNIGT = true;}
      if(NyCKmZpUOi == YoKIOiVAbh){DVXSOPmNNn = true;}
      else if(YoKIOiVAbh == NyCKmZpUOi){GAXDDxcgap = true;}
      if(NmUdgfHRZN == VLLMXloaxX){GeiKVxVILS = true;}
      else if(VLLMXloaxX == NmUdgfHRZN){DeIbbjOQsf = true;}
      if(bQtWCxzlrM == mYnTACzGhg){kufQSVjOrf = true;}
      else if(mYnTACzGhg == bQtWCxzlrM){QNPdVdSKEe = true;}
      if(MIFfcSEhai == umMUXcdGlU){YHoetUNauS = true;}
      if(reoCCFeKWp == cQfSKCMNMW){fjpVRwDnEm = true;}
      if(INqxewDfIp == ybpIKzBqHL){qoZNqIoHzs = true;}
      while(umMUXcdGlU == MIFfcSEhai){mwDeQQWGBq = true;}
      while(cQfSKCMNMW == cQfSKCMNMW){GABxiAxzZC = true;}
      while(ybpIKzBqHL == ybpIKzBqHL){rxPaDrksgZ = true;}
      if(jPStlhzpot == true){jPStlhzpot = false;}
      if(HhnctWsVIx == true){HhnctWsVIx = false;}
      if(plsKiTxEKX == true){plsKiTxEKX = false;}
      if(blyZkNxkfc == true){blyZkNxkfc = false;}
      if(DVXSOPmNNn == true){DVXSOPmNNn = false;}
      if(GeiKVxVILS == true){GeiKVxVILS = false;}
      if(kufQSVjOrf == true){kufQSVjOrf = false;}
      if(YHoetUNauS == true){YHoetUNauS = false;}
      if(fjpVRwDnEm == true){fjpVRwDnEm = false;}
      if(qoZNqIoHzs == true){qoZNqIoHzs = false;}
      if(fYVgPypDPB == true){fYVgPypDPB = false;}
      if(jtMrlBEKyW == true){jtMrlBEKyW = false;}
      if(RuJEnihbnl == true){RuJEnihbnl = false;}
      if(eGbCmHNIGT == true){eGbCmHNIGT = false;}
      if(GAXDDxcgap == true){GAXDDxcgap = false;}
      if(DeIbbjOQsf == true){DeIbbjOQsf = false;}
      if(QNPdVdSKEe == true){QNPdVdSKEe = false;}
      if(mwDeQQWGBq == true){mwDeQQWGBq = false;}
      if(GABxiAxzZC == true){GABxiAxzZC = false;}
      if(rxPaDrksgZ == true){rxPaDrksgZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSCOIKGIVT
{ 
  void jBCmOFPrYG()
  { 
      bool gaAmEyMzBV = false;
      bool tRkXBqlyLo = false;
      bool LcGAFpNYBS = false;
      bool BwZCtPuOxg = false;
      bool BjUhORVIHg = false;
      bool TJNSBDUAhO = false;
      bool jmyhTxqhck = false;
      bool uWAdnaIXkm = false;
      bool UFRTyqiHBp = false;
      bool ttgixOllNQ = false;
      bool ameVkxJjda = false;
      bool twOtsdUdjc = false;
      bool OjflpBoRfZ = false;
      bool nWKUMgawhA = false;
      bool hzcawyfloT = false;
      bool sIBkBqHrej = false;
      bool IqDElXlthM = false;
      bool CYujtPGFpr = false;
      bool VCbLffUZSV = false;
      bool ZiQyrpuYnY = false;
      string ABAOhdeLmu;
      string SzmdsRIcDL;
      string aXQVAjrWCw;
      string MhgWqKJIyq;
      string XmBbkVILmd;
      string ryRCzbjdOy;
      string kHIphkRPmh;
      string IzeLmmVojd;
      string afjXEOPeWO;
      string aetzGPeLsA;
      string DrYFVrTGOL;
      string FtsjXEXjlT;
      string UmsXGcFeEX;
      string IKujaiHdCL;
      string tJQKIfkJbC;
      string rtZZfQzAys;
      string mnBqDuzJJo;
      string xthZYKVhPa;
      string quCCfNjVDJ;
      string iGfIYGIYHM;
      if(ABAOhdeLmu == DrYFVrTGOL){gaAmEyMzBV = true;}
      else if(DrYFVrTGOL == ABAOhdeLmu){ameVkxJjda = true;}
      if(SzmdsRIcDL == FtsjXEXjlT){tRkXBqlyLo = true;}
      else if(FtsjXEXjlT == SzmdsRIcDL){twOtsdUdjc = true;}
      if(aXQVAjrWCw == UmsXGcFeEX){LcGAFpNYBS = true;}
      else if(UmsXGcFeEX == aXQVAjrWCw){OjflpBoRfZ = true;}
      if(MhgWqKJIyq == IKujaiHdCL){BwZCtPuOxg = true;}
      else if(IKujaiHdCL == MhgWqKJIyq){nWKUMgawhA = true;}
      if(XmBbkVILmd == tJQKIfkJbC){BjUhORVIHg = true;}
      else if(tJQKIfkJbC == XmBbkVILmd){hzcawyfloT = true;}
      if(ryRCzbjdOy == rtZZfQzAys){TJNSBDUAhO = true;}
      else if(rtZZfQzAys == ryRCzbjdOy){sIBkBqHrej = true;}
      if(kHIphkRPmh == mnBqDuzJJo){jmyhTxqhck = true;}
      else if(mnBqDuzJJo == kHIphkRPmh){IqDElXlthM = true;}
      if(IzeLmmVojd == xthZYKVhPa){uWAdnaIXkm = true;}
      if(afjXEOPeWO == quCCfNjVDJ){UFRTyqiHBp = true;}
      if(aetzGPeLsA == iGfIYGIYHM){ttgixOllNQ = true;}
      while(xthZYKVhPa == IzeLmmVojd){CYujtPGFpr = true;}
      while(quCCfNjVDJ == quCCfNjVDJ){VCbLffUZSV = true;}
      while(iGfIYGIYHM == iGfIYGIYHM){ZiQyrpuYnY = true;}
      if(gaAmEyMzBV == true){gaAmEyMzBV = false;}
      if(tRkXBqlyLo == true){tRkXBqlyLo = false;}
      if(LcGAFpNYBS == true){LcGAFpNYBS = false;}
      if(BwZCtPuOxg == true){BwZCtPuOxg = false;}
      if(BjUhORVIHg == true){BjUhORVIHg = false;}
      if(TJNSBDUAhO == true){TJNSBDUAhO = false;}
      if(jmyhTxqhck == true){jmyhTxqhck = false;}
      if(uWAdnaIXkm == true){uWAdnaIXkm = false;}
      if(UFRTyqiHBp == true){UFRTyqiHBp = false;}
      if(ttgixOllNQ == true){ttgixOllNQ = false;}
      if(ameVkxJjda == true){ameVkxJjda = false;}
      if(twOtsdUdjc == true){twOtsdUdjc = false;}
      if(OjflpBoRfZ == true){OjflpBoRfZ = false;}
      if(nWKUMgawhA == true){nWKUMgawhA = false;}
      if(hzcawyfloT == true){hzcawyfloT = false;}
      if(sIBkBqHrej == true){sIBkBqHrej = false;}
      if(IqDElXlthM == true){IqDElXlthM = false;}
      if(CYujtPGFpr == true){CYujtPGFpr = false;}
      if(VCbLffUZSV == true){VCbLffUZSV = false;}
      if(ZiQyrpuYnY == true){ZiQyrpuYnY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRITDJYCIK
{ 
  void lLCfjAXwAx()
  { 
      bool DJmGlggkto = false;
      bool JkqxuDBTml = false;
      bool anzPeLqlyJ = false;
      bool PQAMXmLTOd = false;
      bool pROpMlDmaL = false;
      bool DnrkmOKWbZ = false;
      bool oumkYrjdYI = false;
      bool qgFIuJYICs = false;
      bool HDKmGbXPYI = false;
      bool bornnuddRT = false;
      bool BYOSTVhiod = false;
      bool pCUiRkjzdw = false;
      bool UUEPfCoQUA = false;
      bool euphqhorSj = false;
      bool soZuSZTIVC = false;
      bool LezUzgUymR = false;
      bool gROoytLlqj = false;
      bool wqgtCetIwG = false;
      bool hftRnAuVhJ = false;
      bool NpFADbZjxX = false;
      string lougADwAFU;
      string ACPYmwXBnG;
      string PdHNKUgBdh;
      string iJfFfwuKXi;
      string plAnFCYfqh;
      string opSiBIggVe;
      string VuVXlqWJrq;
      string BMcFPcdSIH;
      string uBJwsrpwEX;
      string OOnsMuPcBO;
      string fOmAfbMNSX;
      string eOYOiUkYdt;
      string AZFUbmYjsU;
      string NAQsbgNJQR;
      string fcdgrAoZJr;
      string JpyHNFJSYs;
      string CbUyJdxelC;
      string GbIMNXwXba;
      string xzaAKXCIfW;
      string WukWOEHeWO;
      if(lougADwAFU == fOmAfbMNSX){DJmGlggkto = true;}
      else if(fOmAfbMNSX == lougADwAFU){BYOSTVhiod = true;}
      if(ACPYmwXBnG == eOYOiUkYdt){JkqxuDBTml = true;}
      else if(eOYOiUkYdt == ACPYmwXBnG){pCUiRkjzdw = true;}
      if(PdHNKUgBdh == AZFUbmYjsU){anzPeLqlyJ = true;}
      else if(AZFUbmYjsU == PdHNKUgBdh){UUEPfCoQUA = true;}
      if(iJfFfwuKXi == NAQsbgNJQR){PQAMXmLTOd = true;}
      else if(NAQsbgNJQR == iJfFfwuKXi){euphqhorSj = true;}
      if(plAnFCYfqh == fcdgrAoZJr){pROpMlDmaL = true;}
      else if(fcdgrAoZJr == plAnFCYfqh){soZuSZTIVC = true;}
      if(opSiBIggVe == JpyHNFJSYs){DnrkmOKWbZ = true;}
      else if(JpyHNFJSYs == opSiBIggVe){LezUzgUymR = true;}
      if(VuVXlqWJrq == CbUyJdxelC){oumkYrjdYI = true;}
      else if(CbUyJdxelC == VuVXlqWJrq){gROoytLlqj = true;}
      if(BMcFPcdSIH == GbIMNXwXba){qgFIuJYICs = true;}
      if(uBJwsrpwEX == xzaAKXCIfW){HDKmGbXPYI = true;}
      if(OOnsMuPcBO == WukWOEHeWO){bornnuddRT = true;}
      while(GbIMNXwXba == BMcFPcdSIH){wqgtCetIwG = true;}
      while(xzaAKXCIfW == xzaAKXCIfW){hftRnAuVhJ = true;}
      while(WukWOEHeWO == WukWOEHeWO){NpFADbZjxX = true;}
      if(DJmGlggkto == true){DJmGlggkto = false;}
      if(JkqxuDBTml == true){JkqxuDBTml = false;}
      if(anzPeLqlyJ == true){anzPeLqlyJ = false;}
      if(PQAMXmLTOd == true){PQAMXmLTOd = false;}
      if(pROpMlDmaL == true){pROpMlDmaL = false;}
      if(DnrkmOKWbZ == true){DnrkmOKWbZ = false;}
      if(oumkYrjdYI == true){oumkYrjdYI = false;}
      if(qgFIuJYICs == true){qgFIuJYICs = false;}
      if(HDKmGbXPYI == true){HDKmGbXPYI = false;}
      if(bornnuddRT == true){bornnuddRT = false;}
      if(BYOSTVhiod == true){BYOSTVhiod = false;}
      if(pCUiRkjzdw == true){pCUiRkjzdw = false;}
      if(UUEPfCoQUA == true){UUEPfCoQUA = false;}
      if(euphqhorSj == true){euphqhorSj = false;}
      if(soZuSZTIVC == true){soZuSZTIVC = false;}
      if(LezUzgUymR == true){LezUzgUymR = false;}
      if(gROoytLlqj == true){gROoytLlqj = false;}
      if(wqgtCetIwG == true){wqgtCetIwG = false;}
      if(hftRnAuVhJ == true){hftRnAuVhJ = false;}
      if(NpFADbZjxX == true){NpFADbZjxX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYYQLOZKOY
{ 
  void wOZAonSwML()
  { 
      bool QhnqgcrTJo = false;
      bool KmaFNdLzoV = false;
      bool wfkypJaNnx = false;
      bool LzSMMiaXEC = false;
      bool aRSBdRzzuM = false;
      bool LRiPokxoAW = false;
      bool BdeLcLTNse = false;
      bool DntmtdMiUY = false;
      bool KbSbktPDWa = false;
      bool kkXhAxlHXR = false;
      bool xkGPJXWuVL = false;
      bool YNUaMZLDZi = false;
      bool uQqRsRQMmx = false;
      bool qELCbYUCSN = false;
      bool WUgLCXPwUa = false;
      bool ligoWftoVq = false;
      bool HKIXTTBRym = false;
      bool EIjMLaieOV = false;
      bool BTqLLHXVew = false;
      bool effbFMLJqh = false;
      string tbHlqyGYEl;
      string sFNxEzBdSA;
      string riETzacHSa;
      string oaihwMgYuS;
      string ehnxOYEpeX;
      string KLmeiLWnlP;
      string UyGcxSWfAr;
      string SchAUKtHEa;
      string WmbtQcnDzj;
      string ormfyfbKzw;
      string CYomFhdlJX;
      string RPiLshVLMU;
      string dSfQDZpCBo;
      string ijHIYxyonh;
      string zBtaSYIamQ;
      string JPyeRjrXje;
      string rakUogIamu;
      string igWdVcYFxd;
      string QOPkeTkcpn;
      string EZFJpXQYlk;
      if(tbHlqyGYEl == CYomFhdlJX){QhnqgcrTJo = true;}
      else if(CYomFhdlJX == tbHlqyGYEl){xkGPJXWuVL = true;}
      if(sFNxEzBdSA == RPiLshVLMU){KmaFNdLzoV = true;}
      else if(RPiLshVLMU == sFNxEzBdSA){YNUaMZLDZi = true;}
      if(riETzacHSa == dSfQDZpCBo){wfkypJaNnx = true;}
      else if(dSfQDZpCBo == riETzacHSa){uQqRsRQMmx = true;}
      if(oaihwMgYuS == ijHIYxyonh){LzSMMiaXEC = true;}
      else if(ijHIYxyonh == oaihwMgYuS){qELCbYUCSN = true;}
      if(ehnxOYEpeX == zBtaSYIamQ){aRSBdRzzuM = true;}
      else if(zBtaSYIamQ == ehnxOYEpeX){WUgLCXPwUa = true;}
      if(KLmeiLWnlP == JPyeRjrXje){LRiPokxoAW = true;}
      else if(JPyeRjrXje == KLmeiLWnlP){ligoWftoVq = true;}
      if(UyGcxSWfAr == rakUogIamu){BdeLcLTNse = true;}
      else if(rakUogIamu == UyGcxSWfAr){HKIXTTBRym = true;}
      if(SchAUKtHEa == igWdVcYFxd){DntmtdMiUY = true;}
      if(WmbtQcnDzj == QOPkeTkcpn){KbSbktPDWa = true;}
      if(ormfyfbKzw == EZFJpXQYlk){kkXhAxlHXR = true;}
      while(igWdVcYFxd == SchAUKtHEa){EIjMLaieOV = true;}
      while(QOPkeTkcpn == QOPkeTkcpn){BTqLLHXVew = true;}
      while(EZFJpXQYlk == EZFJpXQYlk){effbFMLJqh = true;}
      if(QhnqgcrTJo == true){QhnqgcrTJo = false;}
      if(KmaFNdLzoV == true){KmaFNdLzoV = false;}
      if(wfkypJaNnx == true){wfkypJaNnx = false;}
      if(LzSMMiaXEC == true){LzSMMiaXEC = false;}
      if(aRSBdRzzuM == true){aRSBdRzzuM = false;}
      if(LRiPokxoAW == true){LRiPokxoAW = false;}
      if(BdeLcLTNse == true){BdeLcLTNse = false;}
      if(DntmtdMiUY == true){DntmtdMiUY = false;}
      if(KbSbktPDWa == true){KbSbktPDWa = false;}
      if(kkXhAxlHXR == true){kkXhAxlHXR = false;}
      if(xkGPJXWuVL == true){xkGPJXWuVL = false;}
      if(YNUaMZLDZi == true){YNUaMZLDZi = false;}
      if(uQqRsRQMmx == true){uQqRsRQMmx = false;}
      if(qELCbYUCSN == true){qELCbYUCSN = false;}
      if(WUgLCXPwUa == true){WUgLCXPwUa = false;}
      if(ligoWftoVq == true){ligoWftoVq = false;}
      if(HKIXTTBRym == true){HKIXTTBRym = false;}
      if(EIjMLaieOV == true){EIjMLaieOV = false;}
      if(BTqLLHXVew == true){BTqLLHXVew = false;}
      if(effbFMLJqh == true){effbFMLJqh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKVERWIOIC
{ 
  void SIxljCuCYJ()
  { 
      bool cgiANndbKD = false;
      bool rzVJqJRtum = false;
      bool tMQhKrKwQS = false;
      bool edjDnUxPKa = false;
      bool wYFowzICew = false;
      bool OToVUQQBpV = false;
      bool cgKrXOORVW = false;
      bool MCjUqUGbkL = false;
      bool iIRUDKoOiW = false;
      bool EwZoxONNQh = false;
      bool jpgIjMiUdz = false;
      bool JnPelUPpnM = false;
      bool YAiySPcuWb = false;
      bool GsLDarbJjq = false;
      bool bUjjNPftCb = false;
      bool zWYDIiHhoT = false;
      bool jnxBrQcLDt = false;
      bool sGGwkEQzkD = false;
      bool jhruciTItr = false;
      bool ksTQHmXhqx = false;
      string eCZoOLxLuA;
      string FkRxiZNlmz;
      string eTERKTjHVH;
      string PVBxPFtDCC;
      string HXEHGzYyYR;
      string krLZqKyHdt;
      string boonkjjTgc;
      string eJijqGPwKL;
      string ukhDVWJbGE;
      string HmYIaRiPWW;
      string OFQwlaIbhj;
      string uBwSzpHkRN;
      string aHNcVrkZIY;
      string XzZnwpTkQu;
      string OgsVJFpFJj;
      string KxyJwHqnZt;
      string ohSJMubIWI;
      string WVTWysOrSQ;
      string CfQXOZBPro;
      string yeLWFfOjIO;
      if(eCZoOLxLuA == OFQwlaIbhj){cgiANndbKD = true;}
      else if(OFQwlaIbhj == eCZoOLxLuA){jpgIjMiUdz = true;}
      if(FkRxiZNlmz == uBwSzpHkRN){rzVJqJRtum = true;}
      else if(uBwSzpHkRN == FkRxiZNlmz){JnPelUPpnM = true;}
      if(eTERKTjHVH == aHNcVrkZIY){tMQhKrKwQS = true;}
      else if(aHNcVrkZIY == eTERKTjHVH){YAiySPcuWb = true;}
      if(PVBxPFtDCC == XzZnwpTkQu){edjDnUxPKa = true;}
      else if(XzZnwpTkQu == PVBxPFtDCC){GsLDarbJjq = true;}
      if(HXEHGzYyYR == OgsVJFpFJj){wYFowzICew = true;}
      else if(OgsVJFpFJj == HXEHGzYyYR){bUjjNPftCb = true;}
      if(krLZqKyHdt == KxyJwHqnZt){OToVUQQBpV = true;}
      else if(KxyJwHqnZt == krLZqKyHdt){zWYDIiHhoT = true;}
      if(boonkjjTgc == ohSJMubIWI){cgKrXOORVW = true;}
      else if(ohSJMubIWI == boonkjjTgc){jnxBrQcLDt = true;}
      if(eJijqGPwKL == WVTWysOrSQ){MCjUqUGbkL = true;}
      if(ukhDVWJbGE == CfQXOZBPro){iIRUDKoOiW = true;}
      if(HmYIaRiPWW == yeLWFfOjIO){EwZoxONNQh = true;}
      while(WVTWysOrSQ == eJijqGPwKL){sGGwkEQzkD = true;}
      while(CfQXOZBPro == CfQXOZBPro){jhruciTItr = true;}
      while(yeLWFfOjIO == yeLWFfOjIO){ksTQHmXhqx = true;}
      if(cgiANndbKD == true){cgiANndbKD = false;}
      if(rzVJqJRtum == true){rzVJqJRtum = false;}
      if(tMQhKrKwQS == true){tMQhKrKwQS = false;}
      if(edjDnUxPKa == true){edjDnUxPKa = false;}
      if(wYFowzICew == true){wYFowzICew = false;}
      if(OToVUQQBpV == true){OToVUQQBpV = false;}
      if(cgKrXOORVW == true){cgKrXOORVW = false;}
      if(MCjUqUGbkL == true){MCjUqUGbkL = false;}
      if(iIRUDKoOiW == true){iIRUDKoOiW = false;}
      if(EwZoxONNQh == true){EwZoxONNQh = false;}
      if(jpgIjMiUdz == true){jpgIjMiUdz = false;}
      if(JnPelUPpnM == true){JnPelUPpnM = false;}
      if(YAiySPcuWb == true){YAiySPcuWb = false;}
      if(GsLDarbJjq == true){GsLDarbJjq = false;}
      if(bUjjNPftCb == true){bUjjNPftCb = false;}
      if(zWYDIiHhoT == true){zWYDIiHhoT = false;}
      if(jnxBrQcLDt == true){jnxBrQcLDt = false;}
      if(sGGwkEQzkD == true){sGGwkEQzkD = false;}
      if(jhruciTItr == true){jhruciTItr = false;}
      if(ksTQHmXhqx == true){ksTQHmXhqx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBXFCFUBPH
{ 
  void nMwzPqswXE()
  { 
      bool noOCUeRWTa = false;
      bool VQBWxToEfy = false;
      bool ZVgBeVzSYz = false;
      bool DtLKcXniLr = false;
      bool JVDEgcpxHW = false;
      bool yCCzxSHNXy = false;
      bool ezyUXaEqsZ = false;
      bool eGsnnEScUB = false;
      bool fCKCABqLNK = false;
      bool PaLMMJWhgF = false;
      bool YyDhqrJOLr = false;
      bool zesVRcnwTW = false;
      bool irdiJEufae = false;
      bool gjwOcgycKI = false;
      bool rcAUKkhouj = false;
      bool VaOJVfUUXm = false;
      bool xcmgKOhdsj = false;
      bool eKkLeGrIXX = false;
      bool WGjqIGVlrw = false;
      bool McEXLOoTKw = false;
      string wyUeKjUihT;
      string ZNuBTMqfqF;
      string wzpkHjIrIx;
      string UflymNQwxB;
      string FCCFfqFXtU;
      string oUoZjwHiWZ;
      string bbZkzsbwOF;
      string wuioAsxjEQ;
      string ekymHzqLOp;
      string FgYWZcbQGm;
      string OJIoYslzZq;
      string zWeFupdldz;
      string BPhYAOWMPW;
      string QfdRBVbJON;
      string NqlXphCSai;
      string zomGkzajnJ;
      string WZjDZSsNDY;
      string OUXPlKdKhR;
      string MDkfWasWfC;
      string trUEpmGiyW;
      if(wyUeKjUihT == OJIoYslzZq){noOCUeRWTa = true;}
      else if(OJIoYslzZq == wyUeKjUihT){YyDhqrJOLr = true;}
      if(ZNuBTMqfqF == zWeFupdldz){VQBWxToEfy = true;}
      else if(zWeFupdldz == ZNuBTMqfqF){zesVRcnwTW = true;}
      if(wzpkHjIrIx == BPhYAOWMPW){ZVgBeVzSYz = true;}
      else if(BPhYAOWMPW == wzpkHjIrIx){irdiJEufae = true;}
      if(UflymNQwxB == QfdRBVbJON){DtLKcXniLr = true;}
      else if(QfdRBVbJON == UflymNQwxB){gjwOcgycKI = true;}
      if(FCCFfqFXtU == NqlXphCSai){JVDEgcpxHW = true;}
      else if(NqlXphCSai == FCCFfqFXtU){rcAUKkhouj = true;}
      if(oUoZjwHiWZ == zomGkzajnJ){yCCzxSHNXy = true;}
      else if(zomGkzajnJ == oUoZjwHiWZ){VaOJVfUUXm = true;}
      if(bbZkzsbwOF == WZjDZSsNDY){ezyUXaEqsZ = true;}
      else if(WZjDZSsNDY == bbZkzsbwOF){xcmgKOhdsj = true;}
      if(wuioAsxjEQ == OUXPlKdKhR){eGsnnEScUB = true;}
      if(ekymHzqLOp == MDkfWasWfC){fCKCABqLNK = true;}
      if(FgYWZcbQGm == trUEpmGiyW){PaLMMJWhgF = true;}
      while(OUXPlKdKhR == wuioAsxjEQ){eKkLeGrIXX = true;}
      while(MDkfWasWfC == MDkfWasWfC){WGjqIGVlrw = true;}
      while(trUEpmGiyW == trUEpmGiyW){McEXLOoTKw = true;}
      if(noOCUeRWTa == true){noOCUeRWTa = false;}
      if(VQBWxToEfy == true){VQBWxToEfy = false;}
      if(ZVgBeVzSYz == true){ZVgBeVzSYz = false;}
      if(DtLKcXniLr == true){DtLKcXniLr = false;}
      if(JVDEgcpxHW == true){JVDEgcpxHW = false;}
      if(yCCzxSHNXy == true){yCCzxSHNXy = false;}
      if(ezyUXaEqsZ == true){ezyUXaEqsZ = false;}
      if(eGsnnEScUB == true){eGsnnEScUB = false;}
      if(fCKCABqLNK == true){fCKCABqLNK = false;}
      if(PaLMMJWhgF == true){PaLMMJWhgF = false;}
      if(YyDhqrJOLr == true){YyDhqrJOLr = false;}
      if(zesVRcnwTW == true){zesVRcnwTW = false;}
      if(irdiJEufae == true){irdiJEufae = false;}
      if(gjwOcgycKI == true){gjwOcgycKI = false;}
      if(rcAUKkhouj == true){rcAUKkhouj = false;}
      if(VaOJVfUUXm == true){VaOJVfUUXm = false;}
      if(xcmgKOhdsj == true){xcmgKOhdsj = false;}
      if(eKkLeGrIXX == true){eKkLeGrIXX = false;}
      if(WGjqIGVlrw == true){WGjqIGVlrw = false;}
      if(McEXLOoTKw == true){McEXLOoTKw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCVZAMVZMI
{ 
  void zlBacHRtZw()
  { 
      bool cCauQRFcNJ = false;
      bool IaTcKVIPXH = false;
      bool bSWbChsQXZ = false;
      bool MyotmUjHpw = false;
      bool ciIuFUClgI = false;
      bool eXUBdKfzri = false;
      bool YnEnwKlZoo = false;
      bool lBYaerKaVg = false;
      bool eHjPtocmPc = false;
      bool okOGXndTzu = false;
      bool hcwqWdysWl = false;
      bool zEcLEQEosH = false;
      bool gzKLAAlRDp = false;
      bool OpbayBKsrQ = false;
      bool piPcdjHCCG = false;
      bool jnaqNiSjqV = false;
      bool qgpgWIcCMD = false;
      bool FLxcRxighP = false;
      bool siPwGZPjMP = false;
      bool haBVYIsiGU = false;
      string tNrbYmGHTj;
      string ZmRRTMNkKV;
      string mXoUkJnEOg;
      string SFKbxdqNbQ;
      string rqhEnzOiSF;
      string KOtEkVXWqO;
      string zCrlQUboUo;
      string VAItdwokgl;
      string uElJWEKFpa;
      string FTWMQpywmS;
      string WYNcjKGAZo;
      string gmpFTuQiPL;
      string JWztiBcucn;
      string ysxNOVpIZM;
      string yKeAtSdRsV;
      string ZOgbIAZTsh;
      string gKWlqnobpy;
      string EHIDNzqyAQ;
      string WLCHOiMVFO;
      string wWOqemmsJG;
      if(tNrbYmGHTj == WYNcjKGAZo){cCauQRFcNJ = true;}
      else if(WYNcjKGAZo == tNrbYmGHTj){hcwqWdysWl = true;}
      if(ZmRRTMNkKV == gmpFTuQiPL){IaTcKVIPXH = true;}
      else if(gmpFTuQiPL == ZmRRTMNkKV){zEcLEQEosH = true;}
      if(mXoUkJnEOg == JWztiBcucn){bSWbChsQXZ = true;}
      else if(JWztiBcucn == mXoUkJnEOg){gzKLAAlRDp = true;}
      if(SFKbxdqNbQ == ysxNOVpIZM){MyotmUjHpw = true;}
      else if(ysxNOVpIZM == SFKbxdqNbQ){OpbayBKsrQ = true;}
      if(rqhEnzOiSF == yKeAtSdRsV){ciIuFUClgI = true;}
      else if(yKeAtSdRsV == rqhEnzOiSF){piPcdjHCCG = true;}
      if(KOtEkVXWqO == ZOgbIAZTsh){eXUBdKfzri = true;}
      else if(ZOgbIAZTsh == KOtEkVXWqO){jnaqNiSjqV = true;}
      if(zCrlQUboUo == gKWlqnobpy){YnEnwKlZoo = true;}
      else if(gKWlqnobpy == zCrlQUboUo){qgpgWIcCMD = true;}
      if(VAItdwokgl == EHIDNzqyAQ){lBYaerKaVg = true;}
      if(uElJWEKFpa == WLCHOiMVFO){eHjPtocmPc = true;}
      if(FTWMQpywmS == wWOqemmsJG){okOGXndTzu = true;}
      while(EHIDNzqyAQ == VAItdwokgl){FLxcRxighP = true;}
      while(WLCHOiMVFO == WLCHOiMVFO){siPwGZPjMP = true;}
      while(wWOqemmsJG == wWOqemmsJG){haBVYIsiGU = true;}
      if(cCauQRFcNJ == true){cCauQRFcNJ = false;}
      if(IaTcKVIPXH == true){IaTcKVIPXH = false;}
      if(bSWbChsQXZ == true){bSWbChsQXZ = false;}
      if(MyotmUjHpw == true){MyotmUjHpw = false;}
      if(ciIuFUClgI == true){ciIuFUClgI = false;}
      if(eXUBdKfzri == true){eXUBdKfzri = false;}
      if(YnEnwKlZoo == true){YnEnwKlZoo = false;}
      if(lBYaerKaVg == true){lBYaerKaVg = false;}
      if(eHjPtocmPc == true){eHjPtocmPc = false;}
      if(okOGXndTzu == true){okOGXndTzu = false;}
      if(hcwqWdysWl == true){hcwqWdysWl = false;}
      if(zEcLEQEosH == true){zEcLEQEosH = false;}
      if(gzKLAAlRDp == true){gzKLAAlRDp = false;}
      if(OpbayBKsrQ == true){OpbayBKsrQ = false;}
      if(piPcdjHCCG == true){piPcdjHCCG = false;}
      if(jnaqNiSjqV == true){jnaqNiSjqV = false;}
      if(qgpgWIcCMD == true){qgpgWIcCMD = false;}
      if(FLxcRxighP == true){FLxcRxighP = false;}
      if(siPwGZPjMP == true){siPwGZPjMP = false;}
      if(haBVYIsiGU == true){haBVYIsiGU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUKHMYSYHB
{ 
  void QLTJKVfQCr()
  { 
      bool eezYrxcDgR = false;
      bool FUMopSckkH = false;
      bool NPeYqriAxz = false;
      bool DqrbRjpWos = false;
      bool JsqcPbVaWO = false;
      bool mgKBOPAahA = false;
      bool NcGhONckXF = false;
      bool bGuryUYBJP = false;
      bool VIdhMWgqNB = false;
      bool jPonegmIOB = false;
      bool zkCQmgkRCs = false;
      bool qyRReFyXVr = false;
      bool fkWWVMQGNR = false;
      bool hPmHQjFNue = false;
      bool kPnTJkxWJY = false;
      bool hOmWUNOftZ = false;
      bool PdEkLbLJBt = false;
      bool zjcpGQxCMj = false;
      bool OtxniSbQmC = false;
      bool VZSVOHKCIh = false;
      string OxOsGeLRPX;
      string irjaKeNCgx;
      string nnMeTFrDxM;
      string pXsBEPxbWi;
      string IoFkDBKgxG;
      string ePSFXZkiZB;
      string mHUCgKyiWt;
      string hleyoziaaR;
      string tKFphaFnce;
      string dNCUwAUCEr;
      string DbJCYrjUQY;
      string qKIIHbCdUG;
      string FKFrQTjKBn;
      string dfVhNSBCQp;
      string pjWEmTFtNT;
      string xphxmrVRlE;
      string IZSbuLnZtn;
      string azMePUmBEw;
      string OpwhqmxYuU;
      string wiQMgQRuIb;
      if(OxOsGeLRPX == DbJCYrjUQY){eezYrxcDgR = true;}
      else if(DbJCYrjUQY == OxOsGeLRPX){zkCQmgkRCs = true;}
      if(irjaKeNCgx == qKIIHbCdUG){FUMopSckkH = true;}
      else if(qKIIHbCdUG == irjaKeNCgx){qyRReFyXVr = true;}
      if(nnMeTFrDxM == FKFrQTjKBn){NPeYqriAxz = true;}
      else if(FKFrQTjKBn == nnMeTFrDxM){fkWWVMQGNR = true;}
      if(pXsBEPxbWi == dfVhNSBCQp){DqrbRjpWos = true;}
      else if(dfVhNSBCQp == pXsBEPxbWi){hPmHQjFNue = true;}
      if(IoFkDBKgxG == pjWEmTFtNT){JsqcPbVaWO = true;}
      else if(pjWEmTFtNT == IoFkDBKgxG){kPnTJkxWJY = true;}
      if(ePSFXZkiZB == xphxmrVRlE){mgKBOPAahA = true;}
      else if(xphxmrVRlE == ePSFXZkiZB){hOmWUNOftZ = true;}
      if(mHUCgKyiWt == IZSbuLnZtn){NcGhONckXF = true;}
      else if(IZSbuLnZtn == mHUCgKyiWt){PdEkLbLJBt = true;}
      if(hleyoziaaR == azMePUmBEw){bGuryUYBJP = true;}
      if(tKFphaFnce == OpwhqmxYuU){VIdhMWgqNB = true;}
      if(dNCUwAUCEr == wiQMgQRuIb){jPonegmIOB = true;}
      while(azMePUmBEw == hleyoziaaR){zjcpGQxCMj = true;}
      while(OpwhqmxYuU == OpwhqmxYuU){OtxniSbQmC = true;}
      while(wiQMgQRuIb == wiQMgQRuIb){VZSVOHKCIh = true;}
      if(eezYrxcDgR == true){eezYrxcDgR = false;}
      if(FUMopSckkH == true){FUMopSckkH = false;}
      if(NPeYqriAxz == true){NPeYqriAxz = false;}
      if(DqrbRjpWos == true){DqrbRjpWos = false;}
      if(JsqcPbVaWO == true){JsqcPbVaWO = false;}
      if(mgKBOPAahA == true){mgKBOPAahA = false;}
      if(NcGhONckXF == true){NcGhONckXF = false;}
      if(bGuryUYBJP == true){bGuryUYBJP = false;}
      if(VIdhMWgqNB == true){VIdhMWgqNB = false;}
      if(jPonegmIOB == true){jPonegmIOB = false;}
      if(zkCQmgkRCs == true){zkCQmgkRCs = false;}
      if(qyRReFyXVr == true){qyRReFyXVr = false;}
      if(fkWWVMQGNR == true){fkWWVMQGNR = false;}
      if(hPmHQjFNue == true){hPmHQjFNue = false;}
      if(kPnTJkxWJY == true){kPnTJkxWJY = false;}
      if(hOmWUNOftZ == true){hOmWUNOftZ = false;}
      if(PdEkLbLJBt == true){PdEkLbLJBt = false;}
      if(zjcpGQxCMj == true){zjcpGQxCMj = false;}
      if(OtxniSbQmC == true){OtxniSbQmC = false;}
      if(VZSVOHKCIh == true){VZSVOHKCIh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXTGHBGFWL
{ 
  void xiSBCMlCsp()
  { 
      bool ZRuNFAbPsB = false;
      bool GWQaWlBPxf = false;
      bool mFPeiLjuzN = false;
      bool YmSipgZtqC = false;
      bool MaGnxGcgKt = false;
      bool mctFBTBQdt = false;
      bool QgPfbTDhjp = false;
      bool LGYuTLybgc = false;
      bool iCjFawsNgV = false;
      bool eIPwkfLaLd = false;
      bool CuwTifEylp = false;
      bool VZiBLOwKEf = false;
      bool apBOLCqbJn = false;
      bool AXPDamGQVt = false;
      bool qtbqAEZOkW = false;
      bool iBVfCLsgIf = false;
      bool ocoxoyKeaX = false;
      bool HfnKnfOKOG = false;
      bool cbplEzBiAO = false;
      bool tYIpEOEdBC = false;
      string EgqqaWiQVI;
      string BfzYLyXhSq;
      string qkjgVPRGpE;
      string OGSQAfsWFH;
      string MLhpjWVDTu;
      string IWfbtSwJVL;
      string FcaQsuNhXf;
      string EBcLeeDswy;
      string sOmtwrZpWh;
      string ijBsCikQxn;
      string JnenpHsUxP;
      string PCMWSppfUB;
      string VXLpwUziIw;
      string tlwHoFjyDn;
      string yEsGRfWdaM;
      string rEwwSkboqV;
      string HJLBUcGFhM;
      string GqcgCReEXQ;
      string yVIwDopAoD;
      string ctHhgnrqlo;
      if(EgqqaWiQVI == JnenpHsUxP){ZRuNFAbPsB = true;}
      else if(JnenpHsUxP == EgqqaWiQVI){CuwTifEylp = true;}
      if(BfzYLyXhSq == PCMWSppfUB){GWQaWlBPxf = true;}
      else if(PCMWSppfUB == BfzYLyXhSq){VZiBLOwKEf = true;}
      if(qkjgVPRGpE == VXLpwUziIw){mFPeiLjuzN = true;}
      else if(VXLpwUziIw == qkjgVPRGpE){apBOLCqbJn = true;}
      if(OGSQAfsWFH == tlwHoFjyDn){YmSipgZtqC = true;}
      else if(tlwHoFjyDn == OGSQAfsWFH){AXPDamGQVt = true;}
      if(MLhpjWVDTu == yEsGRfWdaM){MaGnxGcgKt = true;}
      else if(yEsGRfWdaM == MLhpjWVDTu){qtbqAEZOkW = true;}
      if(IWfbtSwJVL == rEwwSkboqV){mctFBTBQdt = true;}
      else if(rEwwSkboqV == IWfbtSwJVL){iBVfCLsgIf = true;}
      if(FcaQsuNhXf == HJLBUcGFhM){QgPfbTDhjp = true;}
      else if(HJLBUcGFhM == FcaQsuNhXf){ocoxoyKeaX = true;}
      if(EBcLeeDswy == GqcgCReEXQ){LGYuTLybgc = true;}
      if(sOmtwrZpWh == yVIwDopAoD){iCjFawsNgV = true;}
      if(ijBsCikQxn == ctHhgnrqlo){eIPwkfLaLd = true;}
      while(GqcgCReEXQ == EBcLeeDswy){HfnKnfOKOG = true;}
      while(yVIwDopAoD == yVIwDopAoD){cbplEzBiAO = true;}
      while(ctHhgnrqlo == ctHhgnrqlo){tYIpEOEdBC = true;}
      if(ZRuNFAbPsB == true){ZRuNFAbPsB = false;}
      if(GWQaWlBPxf == true){GWQaWlBPxf = false;}
      if(mFPeiLjuzN == true){mFPeiLjuzN = false;}
      if(YmSipgZtqC == true){YmSipgZtqC = false;}
      if(MaGnxGcgKt == true){MaGnxGcgKt = false;}
      if(mctFBTBQdt == true){mctFBTBQdt = false;}
      if(QgPfbTDhjp == true){QgPfbTDhjp = false;}
      if(LGYuTLybgc == true){LGYuTLybgc = false;}
      if(iCjFawsNgV == true){iCjFawsNgV = false;}
      if(eIPwkfLaLd == true){eIPwkfLaLd = false;}
      if(CuwTifEylp == true){CuwTifEylp = false;}
      if(VZiBLOwKEf == true){VZiBLOwKEf = false;}
      if(apBOLCqbJn == true){apBOLCqbJn = false;}
      if(AXPDamGQVt == true){AXPDamGQVt = false;}
      if(qtbqAEZOkW == true){qtbqAEZOkW = false;}
      if(iBVfCLsgIf == true){iBVfCLsgIf = false;}
      if(ocoxoyKeaX == true){ocoxoyKeaX = false;}
      if(HfnKnfOKOG == true){HfnKnfOKOG = false;}
      if(cbplEzBiAO == true){cbplEzBiAO = false;}
      if(tYIpEOEdBC == true){tYIpEOEdBC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DOOJEWOLKA
{ 
  void AarAFaGdQy()
  { 
      bool XgRlqoZNQT = false;
      bool XyHQzSEMBL = false;
      bool IsBWupAbFX = false;
      bool qwoDrlGaVm = false;
      bool MlafVrfidE = false;
      bool rLyUgdeupB = false;
      bool oyHscbJDXN = false;
      bool McpOyWSVAD = false;
      bool JRxBefyTWN = false;
      bool GLjUyOdhCt = false;
      bool icKQqPUiWK = false;
      bool LJtmqXBFNw = false;
      bool dogJGBrVPj = false;
      bool rjSGUgGfKP = false;
      bool LOxMCxQwca = false;
      bool NYTGQsuAKp = false;
      bool WySmRapnSK = false;
      bool QUuykOrTHJ = false;
      bool kwroVTPMpa = false;
      bool kGVTrMuJta = false;
      string hqJudLMadZ;
      string uJKHxFSFEW;
      string CKXrGzMuHa;
      string YeINTtjAzk;
      string kClWMxSfIp;
      string PIagRWSQnd;
      string yRTDAQBxnC;
      string VRFTkAYBfJ;
      string gglRLQEaww;
      string bTMUlThhVw;
      string uVrGUxCGwQ;
      string yRkdxReCqj;
      string MaBqZBFkgR;
      string SpeiNLnfwO;
      string OxeexKhhXU;
      string nfpliTUAfS;
      string qRZeyIlBPl;
      string czFcUOwVsP;
      string SXMMcmzrzs;
      string pmzdWxXAgo;
      if(hqJudLMadZ == uVrGUxCGwQ){XgRlqoZNQT = true;}
      else if(uVrGUxCGwQ == hqJudLMadZ){icKQqPUiWK = true;}
      if(uJKHxFSFEW == yRkdxReCqj){XyHQzSEMBL = true;}
      else if(yRkdxReCqj == uJKHxFSFEW){LJtmqXBFNw = true;}
      if(CKXrGzMuHa == MaBqZBFkgR){IsBWupAbFX = true;}
      else if(MaBqZBFkgR == CKXrGzMuHa){dogJGBrVPj = true;}
      if(YeINTtjAzk == SpeiNLnfwO){qwoDrlGaVm = true;}
      else if(SpeiNLnfwO == YeINTtjAzk){rjSGUgGfKP = true;}
      if(kClWMxSfIp == OxeexKhhXU){MlafVrfidE = true;}
      else if(OxeexKhhXU == kClWMxSfIp){LOxMCxQwca = true;}
      if(PIagRWSQnd == nfpliTUAfS){rLyUgdeupB = true;}
      else if(nfpliTUAfS == PIagRWSQnd){NYTGQsuAKp = true;}
      if(yRTDAQBxnC == qRZeyIlBPl){oyHscbJDXN = true;}
      else if(qRZeyIlBPl == yRTDAQBxnC){WySmRapnSK = true;}
      if(VRFTkAYBfJ == czFcUOwVsP){McpOyWSVAD = true;}
      if(gglRLQEaww == SXMMcmzrzs){JRxBefyTWN = true;}
      if(bTMUlThhVw == pmzdWxXAgo){GLjUyOdhCt = true;}
      while(czFcUOwVsP == VRFTkAYBfJ){QUuykOrTHJ = true;}
      while(SXMMcmzrzs == SXMMcmzrzs){kwroVTPMpa = true;}
      while(pmzdWxXAgo == pmzdWxXAgo){kGVTrMuJta = true;}
      if(XgRlqoZNQT == true){XgRlqoZNQT = false;}
      if(XyHQzSEMBL == true){XyHQzSEMBL = false;}
      if(IsBWupAbFX == true){IsBWupAbFX = false;}
      if(qwoDrlGaVm == true){qwoDrlGaVm = false;}
      if(MlafVrfidE == true){MlafVrfidE = false;}
      if(rLyUgdeupB == true){rLyUgdeupB = false;}
      if(oyHscbJDXN == true){oyHscbJDXN = false;}
      if(McpOyWSVAD == true){McpOyWSVAD = false;}
      if(JRxBefyTWN == true){JRxBefyTWN = false;}
      if(GLjUyOdhCt == true){GLjUyOdhCt = false;}
      if(icKQqPUiWK == true){icKQqPUiWK = false;}
      if(LJtmqXBFNw == true){LJtmqXBFNw = false;}
      if(dogJGBrVPj == true){dogJGBrVPj = false;}
      if(rjSGUgGfKP == true){rjSGUgGfKP = false;}
      if(LOxMCxQwca == true){LOxMCxQwca = false;}
      if(NYTGQsuAKp == true){NYTGQsuAKp = false;}
      if(WySmRapnSK == true){WySmRapnSK = false;}
      if(QUuykOrTHJ == true){QUuykOrTHJ = false;}
      if(kwroVTPMpa == true){kwroVTPMpa = false;}
      if(kGVTrMuJta == true){kGVTrMuJta = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRSMXSSTVS
{ 
  void FuXXKyeQHo()
  { 
      bool XmQWHAaDtY = false;
      bool rdiMkPjMTx = false;
      bool IrMMrIfGZC = false;
      bool cBXckBthha = false;
      bool RaYdHWyxsz = false;
      bool FCMMAfaDey = false;
      bool TUdqwpFGaj = false;
      bool VBdrehSiFU = false;
      bool KhMZxZoKcF = false;
      bool ZpDjGxxggQ = false;
      bool RrWJdDXTgS = false;
      bool MryKnlHDtV = false;
      bool BtcVJeytlh = false;
      bool kkBnDRLDwt = false;
      bool BUdKrhrruU = false;
      bool osmLPWOAzy = false;
      bool EdhzgapJHV = false;
      bool aEHzTfQSca = false;
      bool mGyQrrypYg = false;
      bool DKDyoXmdcQ = false;
      string IbchtCQgAI;
      string rYeGhBGZRA;
      string WCqtngCCTR;
      string sZbzOmWGio;
      string YPGZwfZuIx;
      string NCRnDGjisM;
      string zNMiOSxequ;
      string eAqcbHuRyI;
      string HGsWDqHmwI;
      string CmMVpKCXKc;
      string itENRNLoMu;
      string LSjkFrUpeX;
      string KJiirqmVmQ;
      string FXGUYMCeEp;
      string eRaAxiCbPx;
      string pLrmRZLUUZ;
      string apCupnLPLr;
      string pokorshhlI;
      string oKFoaseTCz;
      string AgJePoPfKJ;
      if(IbchtCQgAI == itENRNLoMu){XmQWHAaDtY = true;}
      else if(itENRNLoMu == IbchtCQgAI){RrWJdDXTgS = true;}
      if(rYeGhBGZRA == LSjkFrUpeX){rdiMkPjMTx = true;}
      else if(LSjkFrUpeX == rYeGhBGZRA){MryKnlHDtV = true;}
      if(WCqtngCCTR == KJiirqmVmQ){IrMMrIfGZC = true;}
      else if(KJiirqmVmQ == WCqtngCCTR){BtcVJeytlh = true;}
      if(sZbzOmWGio == FXGUYMCeEp){cBXckBthha = true;}
      else if(FXGUYMCeEp == sZbzOmWGio){kkBnDRLDwt = true;}
      if(YPGZwfZuIx == eRaAxiCbPx){RaYdHWyxsz = true;}
      else if(eRaAxiCbPx == YPGZwfZuIx){BUdKrhrruU = true;}
      if(NCRnDGjisM == pLrmRZLUUZ){FCMMAfaDey = true;}
      else if(pLrmRZLUUZ == NCRnDGjisM){osmLPWOAzy = true;}
      if(zNMiOSxequ == apCupnLPLr){TUdqwpFGaj = true;}
      else if(apCupnLPLr == zNMiOSxequ){EdhzgapJHV = true;}
      if(eAqcbHuRyI == pokorshhlI){VBdrehSiFU = true;}
      if(HGsWDqHmwI == oKFoaseTCz){KhMZxZoKcF = true;}
      if(CmMVpKCXKc == AgJePoPfKJ){ZpDjGxxggQ = true;}
      while(pokorshhlI == eAqcbHuRyI){aEHzTfQSca = true;}
      while(oKFoaseTCz == oKFoaseTCz){mGyQrrypYg = true;}
      while(AgJePoPfKJ == AgJePoPfKJ){DKDyoXmdcQ = true;}
      if(XmQWHAaDtY == true){XmQWHAaDtY = false;}
      if(rdiMkPjMTx == true){rdiMkPjMTx = false;}
      if(IrMMrIfGZC == true){IrMMrIfGZC = false;}
      if(cBXckBthha == true){cBXckBthha = false;}
      if(RaYdHWyxsz == true){RaYdHWyxsz = false;}
      if(FCMMAfaDey == true){FCMMAfaDey = false;}
      if(TUdqwpFGaj == true){TUdqwpFGaj = false;}
      if(VBdrehSiFU == true){VBdrehSiFU = false;}
      if(KhMZxZoKcF == true){KhMZxZoKcF = false;}
      if(ZpDjGxxggQ == true){ZpDjGxxggQ = false;}
      if(RrWJdDXTgS == true){RrWJdDXTgS = false;}
      if(MryKnlHDtV == true){MryKnlHDtV = false;}
      if(BtcVJeytlh == true){BtcVJeytlh = false;}
      if(kkBnDRLDwt == true){kkBnDRLDwt = false;}
      if(BUdKrhrruU == true){BUdKrhrruU = false;}
      if(osmLPWOAzy == true){osmLPWOAzy = false;}
      if(EdhzgapJHV == true){EdhzgapJHV = false;}
      if(aEHzTfQSca == true){aEHzTfQSca = false;}
      if(mGyQrrypYg == true){mGyQrrypYg = false;}
      if(DKDyoXmdcQ == true){DKDyoXmdcQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SEVBJPADTV
{ 
  void monKDQekOz()
  { 
      bool SHjzeSkqae = false;
      bool DoCWEyrVyD = false;
      bool OXuWwRZOOR = false;
      bool AzXBBGdoFi = false;
      bool HsJMalDHAe = false;
      bool HBiDJtLMDN = false;
      bool sWcJdEQAUy = false;
      bool UCQOuVNhwK = false;
      bool NRNiJyPTrH = false;
      bool tQlqpkPAiW = false;
      bool UCmBKFkTIn = false;
      bool fdQrzaItze = false;
      bool nwINDDQYYK = false;
      bool FNzZoKeLYE = false;
      bool NuLDbQAsrO = false;
      bool bVBEhXtZxG = false;
      bool nLuxiSepDn = false;
      bool wwUuQrkEkm = false;
      bool DXgJiiMtqR = false;
      bool QFNRPBANUI = false;
      string JuNXqtmGLw;
      string ncRuiwnFXA;
      string jzlepccFNV;
      string WOElDXKkDa;
      string doJQeYgSxN;
      string QuqwoKIhhO;
      string QgroZZXeqK;
      string kDCxVtoVAQ;
      string wKHAEaXIxs;
      string OcDoJwwUqF;
      string ABalbNssZt;
      string UmhQRGZrjy;
      string CPhyuIAMmZ;
      string yUdtPtiUXq;
      string gdhDXbtlWD;
      string WEjrDkTcpS;
      string MgGAwzJmBX;
      string XETrRXgeZT;
      string NOojCskkqd;
      string aFdFdzXhGY;
      if(JuNXqtmGLw == ABalbNssZt){SHjzeSkqae = true;}
      else if(ABalbNssZt == JuNXqtmGLw){UCmBKFkTIn = true;}
      if(ncRuiwnFXA == UmhQRGZrjy){DoCWEyrVyD = true;}
      else if(UmhQRGZrjy == ncRuiwnFXA){fdQrzaItze = true;}
      if(jzlepccFNV == CPhyuIAMmZ){OXuWwRZOOR = true;}
      else if(CPhyuIAMmZ == jzlepccFNV){nwINDDQYYK = true;}
      if(WOElDXKkDa == yUdtPtiUXq){AzXBBGdoFi = true;}
      else if(yUdtPtiUXq == WOElDXKkDa){FNzZoKeLYE = true;}
      if(doJQeYgSxN == gdhDXbtlWD){HsJMalDHAe = true;}
      else if(gdhDXbtlWD == doJQeYgSxN){NuLDbQAsrO = true;}
      if(QuqwoKIhhO == WEjrDkTcpS){HBiDJtLMDN = true;}
      else if(WEjrDkTcpS == QuqwoKIhhO){bVBEhXtZxG = true;}
      if(QgroZZXeqK == MgGAwzJmBX){sWcJdEQAUy = true;}
      else if(MgGAwzJmBX == QgroZZXeqK){nLuxiSepDn = true;}
      if(kDCxVtoVAQ == XETrRXgeZT){UCQOuVNhwK = true;}
      if(wKHAEaXIxs == NOojCskkqd){NRNiJyPTrH = true;}
      if(OcDoJwwUqF == aFdFdzXhGY){tQlqpkPAiW = true;}
      while(XETrRXgeZT == kDCxVtoVAQ){wwUuQrkEkm = true;}
      while(NOojCskkqd == NOojCskkqd){DXgJiiMtqR = true;}
      while(aFdFdzXhGY == aFdFdzXhGY){QFNRPBANUI = true;}
      if(SHjzeSkqae == true){SHjzeSkqae = false;}
      if(DoCWEyrVyD == true){DoCWEyrVyD = false;}
      if(OXuWwRZOOR == true){OXuWwRZOOR = false;}
      if(AzXBBGdoFi == true){AzXBBGdoFi = false;}
      if(HsJMalDHAe == true){HsJMalDHAe = false;}
      if(HBiDJtLMDN == true){HBiDJtLMDN = false;}
      if(sWcJdEQAUy == true){sWcJdEQAUy = false;}
      if(UCQOuVNhwK == true){UCQOuVNhwK = false;}
      if(NRNiJyPTrH == true){NRNiJyPTrH = false;}
      if(tQlqpkPAiW == true){tQlqpkPAiW = false;}
      if(UCmBKFkTIn == true){UCmBKFkTIn = false;}
      if(fdQrzaItze == true){fdQrzaItze = false;}
      if(nwINDDQYYK == true){nwINDDQYYK = false;}
      if(FNzZoKeLYE == true){FNzZoKeLYE = false;}
      if(NuLDbQAsrO == true){NuLDbQAsrO = false;}
      if(bVBEhXtZxG == true){bVBEhXtZxG = false;}
      if(nLuxiSepDn == true){nLuxiSepDn = false;}
      if(wwUuQrkEkm == true){wwUuQrkEkm = false;}
      if(DXgJiiMtqR == true){DXgJiiMtqR = false;}
      if(QFNRPBANUI == true){QFNRPBANUI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GKSOLQLGEA
{ 
  void udLgaACMUU()
  { 
      bool NpPonhGdQI = false;
      bool tfeiZZceAN = false;
      bool VwxfZQJait = false;
      bool otyrCRihqP = false;
      bool mVCwnbVVao = false;
      bool BjaBoRsiPW = false;
      bool XetVTAgmfH = false;
      bool punjaztBqx = false;
      bool unAtsFSxDk = false;
      bool YASTqIbfcn = false;
      bool uioSyGwpao = false;
      bool XrqRbidzcO = false;
      bool gjiuipcTsR = false;
      bool XNYDCMzgum = false;
      bool IbVNMgIArI = false;
      bool dbCOGKztiI = false;
      bool ccxIQJTnPO = false;
      bool jwEoFEOVhC = false;
      bool hbaknwLJwr = false;
      bool NFymJeeMwD = false;
      string fziDdjzrxH;
      string EhBfUJlnBn;
      string roYCfHgjPR;
      string cGUJTZuOhJ;
      string eWwWpXWemx;
      string ZClCEpZgWW;
      string DPcfdyMqMt;
      string OWGqJUrCLI;
      string jBwRrZTRFc;
      string ANrKGOsQsr;
      string KfRsiDutri;
      string xXVNmBSLnD;
      string dtkisAdujt;
      string bbISyDiDin;
      string eYZWfcreXF;
      string whcoNPtizh;
      string YAJyHUOCOi;
      string RObzYEUODQ;
      string HzWexszSFi;
      string IAEAPdPaPK;
      if(fziDdjzrxH == KfRsiDutri){NpPonhGdQI = true;}
      else if(KfRsiDutri == fziDdjzrxH){uioSyGwpao = true;}
      if(EhBfUJlnBn == xXVNmBSLnD){tfeiZZceAN = true;}
      else if(xXVNmBSLnD == EhBfUJlnBn){XrqRbidzcO = true;}
      if(roYCfHgjPR == dtkisAdujt){VwxfZQJait = true;}
      else if(dtkisAdujt == roYCfHgjPR){gjiuipcTsR = true;}
      if(cGUJTZuOhJ == bbISyDiDin){otyrCRihqP = true;}
      else if(bbISyDiDin == cGUJTZuOhJ){XNYDCMzgum = true;}
      if(eWwWpXWemx == eYZWfcreXF){mVCwnbVVao = true;}
      else if(eYZWfcreXF == eWwWpXWemx){IbVNMgIArI = true;}
      if(ZClCEpZgWW == whcoNPtizh){BjaBoRsiPW = true;}
      else if(whcoNPtizh == ZClCEpZgWW){dbCOGKztiI = true;}
      if(DPcfdyMqMt == YAJyHUOCOi){XetVTAgmfH = true;}
      else if(YAJyHUOCOi == DPcfdyMqMt){ccxIQJTnPO = true;}
      if(OWGqJUrCLI == RObzYEUODQ){punjaztBqx = true;}
      if(jBwRrZTRFc == HzWexszSFi){unAtsFSxDk = true;}
      if(ANrKGOsQsr == IAEAPdPaPK){YASTqIbfcn = true;}
      while(RObzYEUODQ == OWGqJUrCLI){jwEoFEOVhC = true;}
      while(HzWexszSFi == HzWexszSFi){hbaknwLJwr = true;}
      while(IAEAPdPaPK == IAEAPdPaPK){NFymJeeMwD = true;}
      if(NpPonhGdQI == true){NpPonhGdQI = false;}
      if(tfeiZZceAN == true){tfeiZZceAN = false;}
      if(VwxfZQJait == true){VwxfZQJait = false;}
      if(otyrCRihqP == true){otyrCRihqP = false;}
      if(mVCwnbVVao == true){mVCwnbVVao = false;}
      if(BjaBoRsiPW == true){BjaBoRsiPW = false;}
      if(XetVTAgmfH == true){XetVTAgmfH = false;}
      if(punjaztBqx == true){punjaztBqx = false;}
      if(unAtsFSxDk == true){unAtsFSxDk = false;}
      if(YASTqIbfcn == true){YASTqIbfcn = false;}
      if(uioSyGwpao == true){uioSyGwpao = false;}
      if(XrqRbidzcO == true){XrqRbidzcO = false;}
      if(gjiuipcTsR == true){gjiuipcTsR = false;}
      if(XNYDCMzgum == true){XNYDCMzgum = false;}
      if(IbVNMgIArI == true){IbVNMgIArI = false;}
      if(dbCOGKztiI == true){dbCOGKztiI = false;}
      if(ccxIQJTnPO == true){ccxIQJTnPO = false;}
      if(jwEoFEOVhC == true){jwEoFEOVhC = false;}
      if(hbaknwLJwr == true){hbaknwLJwr = false;}
      if(NFymJeeMwD == true){NFymJeeMwD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEBTBNOYQG
{ 
  void EozHoqrhDE()
  { 
      bool hnoyEsfsjR = false;
      bool LhkQmRMZZm = false;
      bool RfPiyOwFYu = false;
      bool JHhdSJRJee = false;
      bool RekhYarFcD = false;
      bool CZejnCXFzp = false;
      bool xZUoHDAHxd = false;
      bool ADtuUmtgJX = false;
      bool WqcUricxoP = false;
      bool kLJogrJwZV = false;
      bool ZjHzDyfiOB = false;
      bool IqwbTGxzwX = false;
      bool aCRhrntENc = false;
      bool cyGnxlicRt = false;
      bool DsinHtPgVa = false;
      bool tKACtXSYGO = false;
      bool EbVlXKjHdh = false;
      bool WTgCUhSdZy = false;
      bool YMimhSyEtZ = false;
      bool TJWDoaXxQx = false;
      string xuHWHYgiOm;
      string eaNbXQYfyN;
      string GBRosGhkZk;
      string XKWEwhQRJd;
      string MhIHQsJhsm;
      string yEKiKwdRcA;
      string qwJdOTEIfp;
      string AGWTAYrKYz;
      string xAqmmSAmtz;
      string EynImQXerw;
      string oBBDlqhpil;
      string DTsdDpFWpw;
      string TQNflCRNgj;
      string ANRcJuymAu;
      string jJEIwjEKFw;
      string LBnwbYmURj;
      string ZUJykpBQUH;
      string rRVuLJMFjB;
      string xHHjYyYVAk;
      string IcVPVPAFWF;
      if(xuHWHYgiOm == oBBDlqhpil){hnoyEsfsjR = true;}
      else if(oBBDlqhpil == xuHWHYgiOm){ZjHzDyfiOB = true;}
      if(eaNbXQYfyN == DTsdDpFWpw){LhkQmRMZZm = true;}
      else if(DTsdDpFWpw == eaNbXQYfyN){IqwbTGxzwX = true;}
      if(GBRosGhkZk == TQNflCRNgj){RfPiyOwFYu = true;}
      else if(TQNflCRNgj == GBRosGhkZk){aCRhrntENc = true;}
      if(XKWEwhQRJd == ANRcJuymAu){JHhdSJRJee = true;}
      else if(ANRcJuymAu == XKWEwhQRJd){cyGnxlicRt = true;}
      if(MhIHQsJhsm == jJEIwjEKFw){RekhYarFcD = true;}
      else if(jJEIwjEKFw == MhIHQsJhsm){DsinHtPgVa = true;}
      if(yEKiKwdRcA == LBnwbYmURj){CZejnCXFzp = true;}
      else if(LBnwbYmURj == yEKiKwdRcA){tKACtXSYGO = true;}
      if(qwJdOTEIfp == ZUJykpBQUH){xZUoHDAHxd = true;}
      else if(ZUJykpBQUH == qwJdOTEIfp){EbVlXKjHdh = true;}
      if(AGWTAYrKYz == rRVuLJMFjB){ADtuUmtgJX = true;}
      if(xAqmmSAmtz == xHHjYyYVAk){WqcUricxoP = true;}
      if(EynImQXerw == IcVPVPAFWF){kLJogrJwZV = true;}
      while(rRVuLJMFjB == AGWTAYrKYz){WTgCUhSdZy = true;}
      while(xHHjYyYVAk == xHHjYyYVAk){YMimhSyEtZ = true;}
      while(IcVPVPAFWF == IcVPVPAFWF){TJWDoaXxQx = true;}
      if(hnoyEsfsjR == true){hnoyEsfsjR = false;}
      if(LhkQmRMZZm == true){LhkQmRMZZm = false;}
      if(RfPiyOwFYu == true){RfPiyOwFYu = false;}
      if(JHhdSJRJee == true){JHhdSJRJee = false;}
      if(RekhYarFcD == true){RekhYarFcD = false;}
      if(CZejnCXFzp == true){CZejnCXFzp = false;}
      if(xZUoHDAHxd == true){xZUoHDAHxd = false;}
      if(ADtuUmtgJX == true){ADtuUmtgJX = false;}
      if(WqcUricxoP == true){WqcUricxoP = false;}
      if(kLJogrJwZV == true){kLJogrJwZV = false;}
      if(ZjHzDyfiOB == true){ZjHzDyfiOB = false;}
      if(IqwbTGxzwX == true){IqwbTGxzwX = false;}
      if(aCRhrntENc == true){aCRhrntENc = false;}
      if(cyGnxlicRt == true){cyGnxlicRt = false;}
      if(DsinHtPgVa == true){DsinHtPgVa = false;}
      if(tKACtXSYGO == true){tKACtXSYGO = false;}
      if(EbVlXKjHdh == true){EbVlXKjHdh = false;}
      if(WTgCUhSdZy == true){WTgCUhSdZy = false;}
      if(YMimhSyEtZ == true){YMimhSyEtZ = false;}
      if(TJWDoaXxQx == true){TJWDoaXxQx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHJMZDRRAR
{ 
  void yCzNBHXYgz()
  { 
      bool OwsRXgujxs = false;
      bool nfiVeosekU = false;
      bool MHBUCKKeZu = false;
      bool aGlnXoqHdE = false;
      bool aJHiMMXGZE = false;
      bool LChwBGtXOM = false;
      bool VQJBSgttyp = false;
      bool xkBftDzSHp = false;
      bool lEEUjYXpmQ = false;
      bool uTrQiJzGQe = false;
      bool ScHjGZABCx = false;
      bool HbPYZQLoQt = false;
      bool JDHhtdsjxj = false;
      bool ErBbXIxUNJ = false;
      bool XVmoISDTqR = false;
      bool yKoWVOVYoc = false;
      bool gQESsOZnBR = false;
      bool SqaGWmQSYb = false;
      bool aYsfltDeFI = false;
      bool mYekcGRUut = false;
      string FcunlQOWxJ;
      string LfyJfmaODY;
      string cNqjJlEhTP;
      string JBujPbscnL;
      string ZoYUhPLDaV;
      string WgObgqkKdA;
      string LfDgAJjOtE;
      string txaqznnWCt;
      string aBHxsclTCX;
      string phymAslqUY;
      string exIWbYFXcs;
      string DOIjZKYFnW;
      string WQMWNLzmqF;
      string CwCdOdrkVT;
      string WOpIUaZONo;
      string UfDxBNjkIQ;
      string ZSgWqGMdUw;
      string RmjTAIZDCl;
      string kjYBkWsEbA;
      string sHbFtEgTRO;
      if(FcunlQOWxJ == exIWbYFXcs){OwsRXgujxs = true;}
      else if(exIWbYFXcs == FcunlQOWxJ){ScHjGZABCx = true;}
      if(LfyJfmaODY == DOIjZKYFnW){nfiVeosekU = true;}
      else if(DOIjZKYFnW == LfyJfmaODY){HbPYZQLoQt = true;}
      if(cNqjJlEhTP == WQMWNLzmqF){MHBUCKKeZu = true;}
      else if(WQMWNLzmqF == cNqjJlEhTP){JDHhtdsjxj = true;}
      if(JBujPbscnL == CwCdOdrkVT){aGlnXoqHdE = true;}
      else if(CwCdOdrkVT == JBujPbscnL){ErBbXIxUNJ = true;}
      if(ZoYUhPLDaV == WOpIUaZONo){aJHiMMXGZE = true;}
      else if(WOpIUaZONo == ZoYUhPLDaV){XVmoISDTqR = true;}
      if(WgObgqkKdA == UfDxBNjkIQ){LChwBGtXOM = true;}
      else if(UfDxBNjkIQ == WgObgqkKdA){yKoWVOVYoc = true;}
      if(LfDgAJjOtE == ZSgWqGMdUw){VQJBSgttyp = true;}
      else if(ZSgWqGMdUw == LfDgAJjOtE){gQESsOZnBR = true;}
      if(txaqznnWCt == RmjTAIZDCl){xkBftDzSHp = true;}
      if(aBHxsclTCX == kjYBkWsEbA){lEEUjYXpmQ = true;}
      if(phymAslqUY == sHbFtEgTRO){uTrQiJzGQe = true;}
      while(RmjTAIZDCl == txaqznnWCt){SqaGWmQSYb = true;}
      while(kjYBkWsEbA == kjYBkWsEbA){aYsfltDeFI = true;}
      while(sHbFtEgTRO == sHbFtEgTRO){mYekcGRUut = true;}
      if(OwsRXgujxs == true){OwsRXgujxs = false;}
      if(nfiVeosekU == true){nfiVeosekU = false;}
      if(MHBUCKKeZu == true){MHBUCKKeZu = false;}
      if(aGlnXoqHdE == true){aGlnXoqHdE = false;}
      if(aJHiMMXGZE == true){aJHiMMXGZE = false;}
      if(LChwBGtXOM == true){LChwBGtXOM = false;}
      if(VQJBSgttyp == true){VQJBSgttyp = false;}
      if(xkBftDzSHp == true){xkBftDzSHp = false;}
      if(lEEUjYXpmQ == true){lEEUjYXpmQ = false;}
      if(uTrQiJzGQe == true){uTrQiJzGQe = false;}
      if(ScHjGZABCx == true){ScHjGZABCx = false;}
      if(HbPYZQLoQt == true){HbPYZQLoQt = false;}
      if(JDHhtdsjxj == true){JDHhtdsjxj = false;}
      if(ErBbXIxUNJ == true){ErBbXIxUNJ = false;}
      if(XVmoISDTqR == true){XVmoISDTqR = false;}
      if(yKoWVOVYoc == true){yKoWVOVYoc = false;}
      if(gQESsOZnBR == true){gQESsOZnBR = false;}
      if(SqaGWmQSYb == true){SqaGWmQSYb = false;}
      if(aYsfltDeFI == true){aYsfltDeFI = false;}
      if(mYekcGRUut == true){mYekcGRUut = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOIMSEYQJE
{ 
  void pbgcncxtYr()
  { 
      bool TNISEwVTOJ = false;
      bool QPmwZSOfLc = false;
      bool KNpjhByRzW = false;
      bool YNfmVcncbR = false;
      bool bHlGZwYnms = false;
      bool IOKlDFWXkD = false;
      bool yEUqjCiAZw = false;
      bool dlDtACbjKk = false;
      bool bJdFNJCsjQ = false;
      bool GPrXSWmtVW = false;
      bool MYNpOWLQkA = false;
      bool dmNzanaPca = false;
      bool zoPJpOsead = false;
      bool PgOmXDumpq = false;
      bool ylIilTCrwd = false;
      bool wXRtWWIEAA = false;
      bool dfpGkxXZaX = false;
      bool smZlcNggWW = false;
      bool LAiwhrOTPA = false;
      bool uqmoMSuByo = false;
      string mzrythGdbx;
      string CJzOHugwPE;
      string hPauEMcTOK;
      string MINyReQwKj;
      string YZmZxdwmlH;
      string iHpyiWYxsg;
      string EmPRjswAwc;
      string ejleeIcAxZ;
      string QpgGbESOPt;
      string FTCcflJVoE;
      string hupJcyULSZ;
      string tXzSPNGIof;
      string agkBWLgJys;
      string zHKsrVAWdd;
      string jHwpAgTjMR;
      string eAfJcBKnlQ;
      string QLMZalNGat;
      string NidLuTkuBo;
      string qxwgNybAPp;
      string LLkMMXtWON;
      if(mzrythGdbx == hupJcyULSZ){TNISEwVTOJ = true;}
      else if(hupJcyULSZ == mzrythGdbx){MYNpOWLQkA = true;}
      if(CJzOHugwPE == tXzSPNGIof){QPmwZSOfLc = true;}
      else if(tXzSPNGIof == CJzOHugwPE){dmNzanaPca = true;}
      if(hPauEMcTOK == agkBWLgJys){KNpjhByRzW = true;}
      else if(agkBWLgJys == hPauEMcTOK){zoPJpOsead = true;}
      if(MINyReQwKj == zHKsrVAWdd){YNfmVcncbR = true;}
      else if(zHKsrVAWdd == MINyReQwKj){PgOmXDumpq = true;}
      if(YZmZxdwmlH == jHwpAgTjMR){bHlGZwYnms = true;}
      else if(jHwpAgTjMR == YZmZxdwmlH){ylIilTCrwd = true;}
      if(iHpyiWYxsg == eAfJcBKnlQ){IOKlDFWXkD = true;}
      else if(eAfJcBKnlQ == iHpyiWYxsg){wXRtWWIEAA = true;}
      if(EmPRjswAwc == QLMZalNGat){yEUqjCiAZw = true;}
      else if(QLMZalNGat == EmPRjswAwc){dfpGkxXZaX = true;}
      if(ejleeIcAxZ == NidLuTkuBo){dlDtACbjKk = true;}
      if(QpgGbESOPt == qxwgNybAPp){bJdFNJCsjQ = true;}
      if(FTCcflJVoE == LLkMMXtWON){GPrXSWmtVW = true;}
      while(NidLuTkuBo == ejleeIcAxZ){smZlcNggWW = true;}
      while(qxwgNybAPp == qxwgNybAPp){LAiwhrOTPA = true;}
      while(LLkMMXtWON == LLkMMXtWON){uqmoMSuByo = true;}
      if(TNISEwVTOJ == true){TNISEwVTOJ = false;}
      if(QPmwZSOfLc == true){QPmwZSOfLc = false;}
      if(KNpjhByRzW == true){KNpjhByRzW = false;}
      if(YNfmVcncbR == true){YNfmVcncbR = false;}
      if(bHlGZwYnms == true){bHlGZwYnms = false;}
      if(IOKlDFWXkD == true){IOKlDFWXkD = false;}
      if(yEUqjCiAZw == true){yEUqjCiAZw = false;}
      if(dlDtACbjKk == true){dlDtACbjKk = false;}
      if(bJdFNJCsjQ == true){bJdFNJCsjQ = false;}
      if(GPrXSWmtVW == true){GPrXSWmtVW = false;}
      if(MYNpOWLQkA == true){MYNpOWLQkA = false;}
      if(dmNzanaPca == true){dmNzanaPca = false;}
      if(zoPJpOsead == true){zoPJpOsead = false;}
      if(PgOmXDumpq == true){PgOmXDumpq = false;}
      if(ylIilTCrwd == true){ylIilTCrwd = false;}
      if(wXRtWWIEAA == true){wXRtWWIEAA = false;}
      if(dfpGkxXZaX == true){dfpGkxXZaX = false;}
      if(smZlcNggWW == true){smZlcNggWW = false;}
      if(LAiwhrOTPA == true){LAiwhrOTPA = false;}
      if(uqmoMSuByo == true){uqmoMSuByo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFNKPTTTPV
{ 
  void ZTKBVaDUmZ()
  { 
      bool KngpFERGhN = false;
      bool dmoGcEDLmK = false;
      bool JIJuEJPsRd = false;
      bool ESILYFbwny = false;
      bool AWubAaJglY = false;
      bool WoRyfCdllw = false;
      bool oXnDILedgX = false;
      bool cGXnJlMhtc = false;
      bool AiGrGPBJeW = false;
      bool apKrJciqSo = false;
      bool ufzOwQRcot = false;
      bool owqIwGQuxs = false;
      bool KVyKwlueef = false;
      bool DVOFgTirwp = false;
      bool yXUkgeyCwC = false;
      bool LmtZdZgnSJ = false;
      bool UlxIpTglab = false;
      bool WYzGtlANdQ = false;
      bool msicUQboaH = false;
      bool muZlVLaMtN = false;
      string GRJDFRcMoJ;
      string jWBKocGDmY;
      string ZSyIrrIwZf;
      string kBEriOyaJU;
      string WJydQnQxwh;
      string JgfFkmTBLN;
      string JgmJYhSJaZ;
      string dfsSCPUTqD;
      string aLzqVEUzGw;
      string uxOwLpWoFh;
      string VHVVEdmNDV;
      string SzJHlxgwmU;
      string NTCeegQwHL;
      string seNJgTodmq;
      string QHwkcumHJN;
      string IaBkTCEqpW;
      string NpFqcmkzZS;
      string HDJuDGXQBj;
      string sImtDRdcoe;
      string OymPdZBEIp;
      if(GRJDFRcMoJ == VHVVEdmNDV){KngpFERGhN = true;}
      else if(VHVVEdmNDV == GRJDFRcMoJ){ufzOwQRcot = true;}
      if(jWBKocGDmY == SzJHlxgwmU){dmoGcEDLmK = true;}
      else if(SzJHlxgwmU == jWBKocGDmY){owqIwGQuxs = true;}
      if(ZSyIrrIwZf == NTCeegQwHL){JIJuEJPsRd = true;}
      else if(NTCeegQwHL == ZSyIrrIwZf){KVyKwlueef = true;}
      if(kBEriOyaJU == seNJgTodmq){ESILYFbwny = true;}
      else if(seNJgTodmq == kBEriOyaJU){DVOFgTirwp = true;}
      if(WJydQnQxwh == QHwkcumHJN){AWubAaJglY = true;}
      else if(QHwkcumHJN == WJydQnQxwh){yXUkgeyCwC = true;}
      if(JgfFkmTBLN == IaBkTCEqpW){WoRyfCdllw = true;}
      else if(IaBkTCEqpW == JgfFkmTBLN){LmtZdZgnSJ = true;}
      if(JgmJYhSJaZ == NpFqcmkzZS){oXnDILedgX = true;}
      else if(NpFqcmkzZS == JgmJYhSJaZ){UlxIpTglab = true;}
      if(dfsSCPUTqD == HDJuDGXQBj){cGXnJlMhtc = true;}
      if(aLzqVEUzGw == sImtDRdcoe){AiGrGPBJeW = true;}
      if(uxOwLpWoFh == OymPdZBEIp){apKrJciqSo = true;}
      while(HDJuDGXQBj == dfsSCPUTqD){WYzGtlANdQ = true;}
      while(sImtDRdcoe == sImtDRdcoe){msicUQboaH = true;}
      while(OymPdZBEIp == OymPdZBEIp){muZlVLaMtN = true;}
      if(KngpFERGhN == true){KngpFERGhN = false;}
      if(dmoGcEDLmK == true){dmoGcEDLmK = false;}
      if(JIJuEJPsRd == true){JIJuEJPsRd = false;}
      if(ESILYFbwny == true){ESILYFbwny = false;}
      if(AWubAaJglY == true){AWubAaJglY = false;}
      if(WoRyfCdllw == true){WoRyfCdllw = false;}
      if(oXnDILedgX == true){oXnDILedgX = false;}
      if(cGXnJlMhtc == true){cGXnJlMhtc = false;}
      if(AiGrGPBJeW == true){AiGrGPBJeW = false;}
      if(apKrJciqSo == true){apKrJciqSo = false;}
      if(ufzOwQRcot == true){ufzOwQRcot = false;}
      if(owqIwGQuxs == true){owqIwGQuxs = false;}
      if(KVyKwlueef == true){KVyKwlueef = false;}
      if(DVOFgTirwp == true){DVOFgTirwp = false;}
      if(yXUkgeyCwC == true){yXUkgeyCwC = false;}
      if(LmtZdZgnSJ == true){LmtZdZgnSJ = false;}
      if(UlxIpTglab == true){UlxIpTglab = false;}
      if(WYzGtlANdQ == true){WYzGtlANdQ = false;}
      if(msicUQboaH == true){msicUQboaH = false;}
      if(muZlVLaMtN == true){muZlVLaMtN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTOVVUXXEI
{ 
  void CznjUXhLUK()
  { 
      bool rNgcRhOTmg = false;
      bool CfhIrwdJzP = false;
      bool IZVSdFtytH = false;
      bool cGyHRaTTBE = false;
      bool ikMjWdDSpG = false;
      bool nCIOfSqOyM = false;
      bool nPZfDugZpR = false;
      bool cKItfWMkuA = false;
      bool BbImSayibz = false;
      bool iFVnQSKgga = false;
      bool xccYcdsNiI = false;
      bool GGSyLLHmMc = false;
      bool xxypiWnTdM = false;
      bool LeETDXyjJn = false;
      bool gkASsclXcE = false;
      bool LXTEdzelpF = false;
      bool oZjVxaBzum = false;
      bool MWcYuMwexG = false;
      bool kQqYAmKAoD = false;
      bool sMtDzHAeUR = false;
      string pWihBKWJBW;
      string SAJuZMyVLk;
      string PUlQduIRZf;
      string QsQqIqtNfR;
      string YcioaKxOdn;
      string IeyqsVkRDG;
      string BEiUGYiSli;
      string RjosMmkwpT;
      string ysnlXktZxm;
      string GcJZQTsOiB;
      string bdctVXpFeG;
      string knbjIHPxxU;
      string eJUyboZObr;
      string sWNnqTQsPA;
      string totqCRAZRI;
      string EwQNWRJeSg;
      string xbcmMNZmrn;
      string qVgwZoOcwJ;
      string nAxSmxFARZ;
      string KlaiCSMHen;
      if(pWihBKWJBW == bdctVXpFeG){rNgcRhOTmg = true;}
      else if(bdctVXpFeG == pWihBKWJBW){xccYcdsNiI = true;}
      if(SAJuZMyVLk == knbjIHPxxU){CfhIrwdJzP = true;}
      else if(knbjIHPxxU == SAJuZMyVLk){GGSyLLHmMc = true;}
      if(PUlQduIRZf == eJUyboZObr){IZVSdFtytH = true;}
      else if(eJUyboZObr == PUlQduIRZf){xxypiWnTdM = true;}
      if(QsQqIqtNfR == sWNnqTQsPA){cGyHRaTTBE = true;}
      else if(sWNnqTQsPA == QsQqIqtNfR){LeETDXyjJn = true;}
      if(YcioaKxOdn == totqCRAZRI){ikMjWdDSpG = true;}
      else if(totqCRAZRI == YcioaKxOdn){gkASsclXcE = true;}
      if(IeyqsVkRDG == EwQNWRJeSg){nCIOfSqOyM = true;}
      else if(EwQNWRJeSg == IeyqsVkRDG){LXTEdzelpF = true;}
      if(BEiUGYiSli == xbcmMNZmrn){nPZfDugZpR = true;}
      else if(xbcmMNZmrn == BEiUGYiSli){oZjVxaBzum = true;}
      if(RjosMmkwpT == qVgwZoOcwJ){cKItfWMkuA = true;}
      if(ysnlXktZxm == nAxSmxFARZ){BbImSayibz = true;}
      if(GcJZQTsOiB == KlaiCSMHen){iFVnQSKgga = true;}
      while(qVgwZoOcwJ == RjosMmkwpT){MWcYuMwexG = true;}
      while(nAxSmxFARZ == nAxSmxFARZ){kQqYAmKAoD = true;}
      while(KlaiCSMHen == KlaiCSMHen){sMtDzHAeUR = true;}
      if(rNgcRhOTmg == true){rNgcRhOTmg = false;}
      if(CfhIrwdJzP == true){CfhIrwdJzP = false;}
      if(IZVSdFtytH == true){IZVSdFtytH = false;}
      if(cGyHRaTTBE == true){cGyHRaTTBE = false;}
      if(ikMjWdDSpG == true){ikMjWdDSpG = false;}
      if(nCIOfSqOyM == true){nCIOfSqOyM = false;}
      if(nPZfDugZpR == true){nPZfDugZpR = false;}
      if(cKItfWMkuA == true){cKItfWMkuA = false;}
      if(BbImSayibz == true){BbImSayibz = false;}
      if(iFVnQSKgga == true){iFVnQSKgga = false;}
      if(xccYcdsNiI == true){xccYcdsNiI = false;}
      if(GGSyLLHmMc == true){GGSyLLHmMc = false;}
      if(xxypiWnTdM == true){xxypiWnTdM = false;}
      if(LeETDXyjJn == true){LeETDXyjJn = false;}
      if(gkASsclXcE == true){gkASsclXcE = false;}
      if(LXTEdzelpF == true){LXTEdzelpF = false;}
      if(oZjVxaBzum == true){oZjVxaBzum = false;}
      if(MWcYuMwexG == true){MWcYuMwexG = false;}
      if(kQqYAmKAoD == true){kQqYAmKAoD = false;}
      if(sMtDzHAeUR == true){sMtDzHAeUR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UPYSVIAEJT
{ 
  void ghaAfjLypg()
  { 
      bool QaUgOHJgQG = false;
      bool PDOSlOacPg = false;
      bool wirLynYfdP = false;
      bool HbVhNyPHYa = false;
      bool BViIhJOdUl = false;
      bool JeZfQgiIha = false;
      bool hdCAyngfEn = false;
      bool ySEoeaAicn = false;
      bool YuLqFbBoRf = false;
      bool PGZysWSiKt = false;
      bool chYfnpajBo = false;
      bool gzfsBlSKtV = false;
      bool lqOYXqsFwH = false;
      bool IQYiLqWeDP = false;
      bool BQnczPafwG = false;
      bool EHnnHkTAIw = false;
      bool xUnsgPawhK = false;
      bool PnHeUUDkYI = false;
      bool QNJoDAcjaa = false;
      bool WVWHRfcuui = false;
      string HoITdMUizr;
      string GRHXQHHdDn;
      string BnFOLsBgqH;
      string oDNOrkVapw;
      string hriVPrTwIF;
      string tnrOISjsHk;
      string KnqrCCEsff;
      string kgnGFIFjzS;
      string ZFXlMBLyFY;
      string AcSEltBqSN;
      string nZQcTNzkJA;
      string NAtnLFQEeB;
      string pGnGeIOiTL;
      string HOQlezntSz;
      string BZnFLAidsf;
      string cwLQWglKxL;
      string yQRyryiHJL;
      string RVleAQRiue;
      string YjonhLCzPx;
      string NdwGAkIpMM;
      if(HoITdMUizr == nZQcTNzkJA){QaUgOHJgQG = true;}
      else if(nZQcTNzkJA == HoITdMUizr){chYfnpajBo = true;}
      if(GRHXQHHdDn == NAtnLFQEeB){PDOSlOacPg = true;}
      else if(NAtnLFQEeB == GRHXQHHdDn){gzfsBlSKtV = true;}
      if(BnFOLsBgqH == pGnGeIOiTL){wirLynYfdP = true;}
      else if(pGnGeIOiTL == BnFOLsBgqH){lqOYXqsFwH = true;}
      if(oDNOrkVapw == HOQlezntSz){HbVhNyPHYa = true;}
      else if(HOQlezntSz == oDNOrkVapw){IQYiLqWeDP = true;}
      if(hriVPrTwIF == BZnFLAidsf){BViIhJOdUl = true;}
      else if(BZnFLAidsf == hriVPrTwIF){BQnczPafwG = true;}
      if(tnrOISjsHk == cwLQWglKxL){JeZfQgiIha = true;}
      else if(cwLQWglKxL == tnrOISjsHk){EHnnHkTAIw = true;}
      if(KnqrCCEsff == yQRyryiHJL){hdCAyngfEn = true;}
      else if(yQRyryiHJL == KnqrCCEsff){xUnsgPawhK = true;}
      if(kgnGFIFjzS == RVleAQRiue){ySEoeaAicn = true;}
      if(ZFXlMBLyFY == YjonhLCzPx){YuLqFbBoRf = true;}
      if(AcSEltBqSN == NdwGAkIpMM){PGZysWSiKt = true;}
      while(RVleAQRiue == kgnGFIFjzS){PnHeUUDkYI = true;}
      while(YjonhLCzPx == YjonhLCzPx){QNJoDAcjaa = true;}
      while(NdwGAkIpMM == NdwGAkIpMM){WVWHRfcuui = true;}
      if(QaUgOHJgQG == true){QaUgOHJgQG = false;}
      if(PDOSlOacPg == true){PDOSlOacPg = false;}
      if(wirLynYfdP == true){wirLynYfdP = false;}
      if(HbVhNyPHYa == true){HbVhNyPHYa = false;}
      if(BViIhJOdUl == true){BViIhJOdUl = false;}
      if(JeZfQgiIha == true){JeZfQgiIha = false;}
      if(hdCAyngfEn == true){hdCAyngfEn = false;}
      if(ySEoeaAicn == true){ySEoeaAicn = false;}
      if(YuLqFbBoRf == true){YuLqFbBoRf = false;}
      if(PGZysWSiKt == true){PGZysWSiKt = false;}
      if(chYfnpajBo == true){chYfnpajBo = false;}
      if(gzfsBlSKtV == true){gzfsBlSKtV = false;}
      if(lqOYXqsFwH == true){lqOYXqsFwH = false;}
      if(IQYiLqWeDP == true){IQYiLqWeDP = false;}
      if(BQnczPafwG == true){BQnczPafwG = false;}
      if(EHnnHkTAIw == true){EHnnHkTAIw = false;}
      if(xUnsgPawhK == true){xUnsgPawhK = false;}
      if(PnHeUUDkYI == true){PnHeUUDkYI = false;}
      if(QNJoDAcjaa == true){QNJoDAcjaa = false;}
      if(WVWHRfcuui == true){WVWHRfcuui = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DGUEQMNSJQ
{ 
  void rsGuDrHNPH()
  { 
      bool QsoIIyPbsn = false;
      bool NXpGWeUpVq = false;
      bool RDKGSUkEeJ = false;
      bool VPnduwbUah = false;
      bool UdIKJAgHNO = false;
      bool ZqEXGNhhon = false;
      bool NLwiSxiMKa = false;
      bool CAPnVntAxS = false;
      bool ncqQjdKPWh = false;
      bool OtemUIgYrL = false;
      bool QTwmLZaPBS = false;
      bool ShjVzjTfzn = false;
      bool lSobLIUcTN = false;
      bool GUIlCUgEFK = false;
      bool DuOEOgJImj = false;
      bool nBZDYxdTaC = false;
      bool ExwnLyZxTe = false;
      bool DPZnkqEjNe = false;
      bool yMpiYEtENF = false;
      bool pMcCGFyZsQ = false;
      string KQRxGVHwjl;
      string zgMmrpZZMy;
      string UOMZysKtEC;
      string SVBJTguUET;
      string qkuPgBXHLA;
      string iyDpBwDrzM;
      string KNqgSdeCTK;
      string tEVsHjTxsw;
      string VDhDTUSLIW;
      string cCVqIcsNwC;
      string WVnBFebKhR;
      string cGzDqHfmNx;
      string LTtwhridje;
      string pFApZzPgyo;
      string sHdptVCSAA;
      string xFAyqDbrSM;
      string uyZDaWFJcq;
      string rzoYEDpDBL;
      string pQcigjFCyW;
      string XWNksthZOX;
      if(KQRxGVHwjl == WVnBFebKhR){QsoIIyPbsn = true;}
      else if(WVnBFebKhR == KQRxGVHwjl){QTwmLZaPBS = true;}
      if(zgMmrpZZMy == cGzDqHfmNx){NXpGWeUpVq = true;}
      else if(cGzDqHfmNx == zgMmrpZZMy){ShjVzjTfzn = true;}
      if(UOMZysKtEC == LTtwhridje){RDKGSUkEeJ = true;}
      else if(LTtwhridje == UOMZysKtEC){lSobLIUcTN = true;}
      if(SVBJTguUET == pFApZzPgyo){VPnduwbUah = true;}
      else if(pFApZzPgyo == SVBJTguUET){GUIlCUgEFK = true;}
      if(qkuPgBXHLA == sHdptVCSAA){UdIKJAgHNO = true;}
      else if(sHdptVCSAA == qkuPgBXHLA){DuOEOgJImj = true;}
      if(iyDpBwDrzM == xFAyqDbrSM){ZqEXGNhhon = true;}
      else if(xFAyqDbrSM == iyDpBwDrzM){nBZDYxdTaC = true;}
      if(KNqgSdeCTK == uyZDaWFJcq){NLwiSxiMKa = true;}
      else if(uyZDaWFJcq == KNqgSdeCTK){ExwnLyZxTe = true;}
      if(tEVsHjTxsw == rzoYEDpDBL){CAPnVntAxS = true;}
      if(VDhDTUSLIW == pQcigjFCyW){ncqQjdKPWh = true;}
      if(cCVqIcsNwC == XWNksthZOX){OtemUIgYrL = true;}
      while(rzoYEDpDBL == tEVsHjTxsw){DPZnkqEjNe = true;}
      while(pQcigjFCyW == pQcigjFCyW){yMpiYEtENF = true;}
      while(XWNksthZOX == XWNksthZOX){pMcCGFyZsQ = true;}
      if(QsoIIyPbsn == true){QsoIIyPbsn = false;}
      if(NXpGWeUpVq == true){NXpGWeUpVq = false;}
      if(RDKGSUkEeJ == true){RDKGSUkEeJ = false;}
      if(VPnduwbUah == true){VPnduwbUah = false;}
      if(UdIKJAgHNO == true){UdIKJAgHNO = false;}
      if(ZqEXGNhhon == true){ZqEXGNhhon = false;}
      if(NLwiSxiMKa == true){NLwiSxiMKa = false;}
      if(CAPnVntAxS == true){CAPnVntAxS = false;}
      if(ncqQjdKPWh == true){ncqQjdKPWh = false;}
      if(OtemUIgYrL == true){OtemUIgYrL = false;}
      if(QTwmLZaPBS == true){QTwmLZaPBS = false;}
      if(ShjVzjTfzn == true){ShjVzjTfzn = false;}
      if(lSobLIUcTN == true){lSobLIUcTN = false;}
      if(GUIlCUgEFK == true){GUIlCUgEFK = false;}
      if(DuOEOgJImj == true){DuOEOgJImj = false;}
      if(nBZDYxdTaC == true){nBZDYxdTaC = false;}
      if(ExwnLyZxTe == true){ExwnLyZxTe = false;}
      if(DPZnkqEjNe == true){DPZnkqEjNe = false;}
      if(yMpiYEtENF == true){yMpiYEtENF = false;}
      if(pMcCGFyZsQ == true){pMcCGFyZsQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQRBDJNHTV
{ 
  void JOASNZPsAp()
  { 
      bool WqAWALerDI = false;
      bool FNXoGhZdYI = false;
      bool pmKgBszxUu = false;
      bool YSdAKIpCOu = false;
      bool CMBtWLLHue = false;
      bool fKAkpifSVG = false;
      bool MgXIiliWdx = false;
      bool rXOdGckQJp = false;
      bool hqCpPORsKa = false;
      bool bXfHiUnsKk = false;
      bool bocxlIuWeM = false;
      bool yPIfYUdhsU = false;
      bool UpLDUTqHuk = false;
      bool orFYNsNFDG = false;
      bool SuOxcMOAiN = false;
      bool qGAoPkcZbS = false;
      bool QnatXGKiRe = false;
      bool GYelCYbOZI = false;
      bool EqYhshqQJc = false;
      bool PncjpeUUYW = false;
      string sDmahtfHNx;
      string AdZJOKClzP;
      string QuZNRpaach;
      string KnfizxPEdN;
      string cRXAatjYlH;
      string WfWfzxcYIr;
      string SFdelLyqKQ;
      string uxIllzXYmX;
      string FCoULdRzjB;
      string TpwktXmsNP;
      string wsNUMZXktA;
      string ZDkkmQQISI;
      string syHJxEBXrN;
      string LeKXaLnTIl;
      string GgFibPEKyc;
      string HdZFVylEWH;
      string YzrfourNKa;
      string cwzgBMrXgh;
      string ApZOGgEFCc;
      string ZixBMGnZsf;
      if(sDmahtfHNx == wsNUMZXktA){WqAWALerDI = true;}
      else if(wsNUMZXktA == sDmahtfHNx){bocxlIuWeM = true;}
      if(AdZJOKClzP == ZDkkmQQISI){FNXoGhZdYI = true;}
      else if(ZDkkmQQISI == AdZJOKClzP){yPIfYUdhsU = true;}
      if(QuZNRpaach == syHJxEBXrN){pmKgBszxUu = true;}
      else if(syHJxEBXrN == QuZNRpaach){UpLDUTqHuk = true;}
      if(KnfizxPEdN == LeKXaLnTIl){YSdAKIpCOu = true;}
      else if(LeKXaLnTIl == KnfizxPEdN){orFYNsNFDG = true;}
      if(cRXAatjYlH == GgFibPEKyc){CMBtWLLHue = true;}
      else if(GgFibPEKyc == cRXAatjYlH){SuOxcMOAiN = true;}
      if(WfWfzxcYIr == HdZFVylEWH){fKAkpifSVG = true;}
      else if(HdZFVylEWH == WfWfzxcYIr){qGAoPkcZbS = true;}
      if(SFdelLyqKQ == YzrfourNKa){MgXIiliWdx = true;}
      else if(YzrfourNKa == SFdelLyqKQ){QnatXGKiRe = true;}
      if(uxIllzXYmX == cwzgBMrXgh){rXOdGckQJp = true;}
      if(FCoULdRzjB == ApZOGgEFCc){hqCpPORsKa = true;}
      if(TpwktXmsNP == ZixBMGnZsf){bXfHiUnsKk = true;}
      while(cwzgBMrXgh == uxIllzXYmX){GYelCYbOZI = true;}
      while(ApZOGgEFCc == ApZOGgEFCc){EqYhshqQJc = true;}
      while(ZixBMGnZsf == ZixBMGnZsf){PncjpeUUYW = true;}
      if(WqAWALerDI == true){WqAWALerDI = false;}
      if(FNXoGhZdYI == true){FNXoGhZdYI = false;}
      if(pmKgBszxUu == true){pmKgBszxUu = false;}
      if(YSdAKIpCOu == true){YSdAKIpCOu = false;}
      if(CMBtWLLHue == true){CMBtWLLHue = false;}
      if(fKAkpifSVG == true){fKAkpifSVG = false;}
      if(MgXIiliWdx == true){MgXIiliWdx = false;}
      if(rXOdGckQJp == true){rXOdGckQJp = false;}
      if(hqCpPORsKa == true){hqCpPORsKa = false;}
      if(bXfHiUnsKk == true){bXfHiUnsKk = false;}
      if(bocxlIuWeM == true){bocxlIuWeM = false;}
      if(yPIfYUdhsU == true){yPIfYUdhsU = false;}
      if(UpLDUTqHuk == true){UpLDUTqHuk = false;}
      if(orFYNsNFDG == true){orFYNsNFDG = false;}
      if(SuOxcMOAiN == true){SuOxcMOAiN = false;}
      if(qGAoPkcZbS == true){qGAoPkcZbS = false;}
      if(QnatXGKiRe == true){QnatXGKiRe = false;}
      if(GYelCYbOZI == true){GYelCYbOZI = false;}
      if(EqYhshqQJc == true){EqYhshqQJc = false;}
      if(PncjpeUUYW == true){PncjpeUUYW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GAMPSGYOLU
{ 
  void UPzIArlnjt()
  { 
      bool iPkkcjAEDA = false;
      bool XmebjpbJRR = false;
      bool FDZrLWZyZL = false;
      bool IeQwxLNjkW = false;
      bool WWRKmKIcsK = false;
      bool KPAFdepsYG = false;
      bool KBdqqsVheY = false;
      bool brYttilOEA = false;
      bool NxFPBrdLRS = false;
      bool VUKdMUsaTt = false;
      bool oayUhSqFKu = false;
      bool sbnYsMwOpz = false;
      bool OKQLCGguhZ = false;
      bool oKuJLmzkgh = false;
      bool BXAVYtflkz = false;
      bool YdjUfeJlRb = false;
      bool lwXkGhgeMF = false;
      bool NLhHxqJtlI = false;
      bool atJiALaadf = false;
      bool cNSFwFAOPq = false;
      string YuTrasDewy;
      string wjxCGeHNMo;
      string shldUnZAfL;
      string MsKqwNVtRP;
      string KwgZTgjQpz;
      string qKVYnpIoWm;
      string SDzklDYFFs;
      string JMuxdxBLKm;
      string DJKfUBWkDG;
      string EfXewHwunP;
      string HdKxpdPYtp;
      string nxeiiJrSQk;
      string gmCzncnQBV;
      string AGXteZzNpp;
      string lxqNRHAoum;
      string OceCiTbLIM;
      string oyXYohYkDJ;
      string Jecaziwogf;
      string bzVNGXbULL;
      string ymEdAmZRXj;
      if(YuTrasDewy == HdKxpdPYtp){iPkkcjAEDA = true;}
      else if(HdKxpdPYtp == YuTrasDewy){oayUhSqFKu = true;}
      if(wjxCGeHNMo == nxeiiJrSQk){XmebjpbJRR = true;}
      else if(nxeiiJrSQk == wjxCGeHNMo){sbnYsMwOpz = true;}
      if(shldUnZAfL == gmCzncnQBV){FDZrLWZyZL = true;}
      else if(gmCzncnQBV == shldUnZAfL){OKQLCGguhZ = true;}
      if(MsKqwNVtRP == AGXteZzNpp){IeQwxLNjkW = true;}
      else if(AGXteZzNpp == MsKqwNVtRP){oKuJLmzkgh = true;}
      if(KwgZTgjQpz == lxqNRHAoum){WWRKmKIcsK = true;}
      else if(lxqNRHAoum == KwgZTgjQpz){BXAVYtflkz = true;}
      if(qKVYnpIoWm == OceCiTbLIM){KPAFdepsYG = true;}
      else if(OceCiTbLIM == qKVYnpIoWm){YdjUfeJlRb = true;}
      if(SDzklDYFFs == oyXYohYkDJ){KBdqqsVheY = true;}
      else if(oyXYohYkDJ == SDzklDYFFs){lwXkGhgeMF = true;}
      if(JMuxdxBLKm == Jecaziwogf){brYttilOEA = true;}
      if(DJKfUBWkDG == bzVNGXbULL){NxFPBrdLRS = true;}
      if(EfXewHwunP == ymEdAmZRXj){VUKdMUsaTt = true;}
      while(Jecaziwogf == JMuxdxBLKm){NLhHxqJtlI = true;}
      while(bzVNGXbULL == bzVNGXbULL){atJiALaadf = true;}
      while(ymEdAmZRXj == ymEdAmZRXj){cNSFwFAOPq = true;}
      if(iPkkcjAEDA == true){iPkkcjAEDA = false;}
      if(XmebjpbJRR == true){XmebjpbJRR = false;}
      if(FDZrLWZyZL == true){FDZrLWZyZL = false;}
      if(IeQwxLNjkW == true){IeQwxLNjkW = false;}
      if(WWRKmKIcsK == true){WWRKmKIcsK = false;}
      if(KPAFdepsYG == true){KPAFdepsYG = false;}
      if(KBdqqsVheY == true){KBdqqsVheY = false;}
      if(brYttilOEA == true){brYttilOEA = false;}
      if(NxFPBrdLRS == true){NxFPBrdLRS = false;}
      if(VUKdMUsaTt == true){VUKdMUsaTt = false;}
      if(oayUhSqFKu == true){oayUhSqFKu = false;}
      if(sbnYsMwOpz == true){sbnYsMwOpz = false;}
      if(OKQLCGguhZ == true){OKQLCGguhZ = false;}
      if(oKuJLmzkgh == true){oKuJLmzkgh = false;}
      if(BXAVYtflkz == true){BXAVYtflkz = false;}
      if(YdjUfeJlRb == true){YdjUfeJlRb = false;}
      if(lwXkGhgeMF == true){lwXkGhgeMF = false;}
      if(NLhHxqJtlI == true){NLhHxqJtlI = false;}
      if(atJiALaadf == true){atJiALaadf = false;}
      if(cNSFwFAOPq == true){cNSFwFAOPq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MDSOTTXSLT
{ 
  void GBfBdmIRSC()
  { 
      bool JRwPhMCzzj = false;
      bool mELVqMqAYe = false;
      bool VXqcjQsSoG = false;
      bool nZQspZljpz = false;
      bool LHlMSaUFyH = false;
      bool LfXFbkZSeQ = false;
      bool SiJswMnSeR = false;
      bool ZGJYTOleKJ = false;
      bool wnThtHCLQF = false;
      bool zTFZgcxsPF = false;
      bool mCZggFWylN = false;
      bool zuIVUdObyn = false;
      bool KcBZRGAiqp = false;
      bool QrOEWsOmBo = false;
      bool jDYCFEKiEC = false;
      bool NVtbtJAzOZ = false;
      bool EmGuxGfDya = false;
      bool PaZIDGDzTN = false;
      bool uQeoctymKM = false;
      bool sOYakxwdFz = false;
      string SxqiTqULaa;
      string kxKqZJycKs;
      string udlUGpIRab;
      string GbhgGiRGMu;
      string BdgfncQEfW;
      string BnsVjnKWbc;
      string iDkzUIPdjq;
      string rrPPrRwGgc;
      string ZDkDZRiLxR;
      string XudiLyrhLe;
      string NmUoeJXcdS;
      string qEpyDfRgYC;
      string ZDfRSwNgEs;
      string YOtBPliwYP;
      string tFgdaTFefe;
      string gKIIEJGCVh;
      string uqYksbJniQ;
      string xUIJIUWBqz;
      string qiAYMNGlwF;
      string ffapTCfwky;
      if(SxqiTqULaa == NmUoeJXcdS){JRwPhMCzzj = true;}
      else if(NmUoeJXcdS == SxqiTqULaa){mCZggFWylN = true;}
      if(kxKqZJycKs == qEpyDfRgYC){mELVqMqAYe = true;}
      else if(qEpyDfRgYC == kxKqZJycKs){zuIVUdObyn = true;}
      if(udlUGpIRab == ZDfRSwNgEs){VXqcjQsSoG = true;}
      else if(ZDfRSwNgEs == udlUGpIRab){KcBZRGAiqp = true;}
      if(GbhgGiRGMu == YOtBPliwYP){nZQspZljpz = true;}
      else if(YOtBPliwYP == GbhgGiRGMu){QrOEWsOmBo = true;}
      if(BdgfncQEfW == tFgdaTFefe){LHlMSaUFyH = true;}
      else if(tFgdaTFefe == BdgfncQEfW){jDYCFEKiEC = true;}
      if(BnsVjnKWbc == gKIIEJGCVh){LfXFbkZSeQ = true;}
      else if(gKIIEJGCVh == BnsVjnKWbc){NVtbtJAzOZ = true;}
      if(iDkzUIPdjq == uqYksbJniQ){SiJswMnSeR = true;}
      else if(uqYksbJniQ == iDkzUIPdjq){EmGuxGfDya = true;}
      if(rrPPrRwGgc == xUIJIUWBqz){ZGJYTOleKJ = true;}
      if(ZDkDZRiLxR == qiAYMNGlwF){wnThtHCLQF = true;}
      if(XudiLyrhLe == ffapTCfwky){zTFZgcxsPF = true;}
      while(xUIJIUWBqz == rrPPrRwGgc){PaZIDGDzTN = true;}
      while(qiAYMNGlwF == qiAYMNGlwF){uQeoctymKM = true;}
      while(ffapTCfwky == ffapTCfwky){sOYakxwdFz = true;}
      if(JRwPhMCzzj == true){JRwPhMCzzj = false;}
      if(mELVqMqAYe == true){mELVqMqAYe = false;}
      if(VXqcjQsSoG == true){VXqcjQsSoG = false;}
      if(nZQspZljpz == true){nZQspZljpz = false;}
      if(LHlMSaUFyH == true){LHlMSaUFyH = false;}
      if(LfXFbkZSeQ == true){LfXFbkZSeQ = false;}
      if(SiJswMnSeR == true){SiJswMnSeR = false;}
      if(ZGJYTOleKJ == true){ZGJYTOleKJ = false;}
      if(wnThtHCLQF == true){wnThtHCLQF = false;}
      if(zTFZgcxsPF == true){zTFZgcxsPF = false;}
      if(mCZggFWylN == true){mCZggFWylN = false;}
      if(zuIVUdObyn == true){zuIVUdObyn = false;}
      if(KcBZRGAiqp == true){KcBZRGAiqp = false;}
      if(QrOEWsOmBo == true){QrOEWsOmBo = false;}
      if(jDYCFEKiEC == true){jDYCFEKiEC = false;}
      if(NVtbtJAzOZ == true){NVtbtJAzOZ = false;}
      if(EmGuxGfDya == true){EmGuxGfDya = false;}
      if(PaZIDGDzTN == true){PaZIDGDzTN = false;}
      if(uQeoctymKM == true){uQeoctymKM = false;}
      if(sOYakxwdFz == true){sOYakxwdFz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBHLSJIHBR
{ 
  void YHnOotcpxY()
  { 
      bool JaUtiKBFfK = false;
      bool xGoYwrwOAM = false;
      bool gmpJbsTSJs = false;
      bool HHtmusjNuS = false;
      bool SAzYFjIlOu = false;
      bool jaOAjWkKSp = false;
      bool phulCoMCcC = false;
      bool IiTgsfmQEr = false;
      bool jhDNJgssDY = false;
      bool IZuEbkFMVP = false;
      bool XFIMmAHgHD = false;
      bool iTFZFIdgcV = false;
      bool wSzEsinOFI = false;
      bool aZunUdYqaI = false;
      bool YMlzooTUyT = false;
      bool GXiATEGESE = false;
      bool MsazbJYQFa = false;
      bool imGUxjfzPE = false;
      bool PSPkBDqtUP = false;
      bool XUXVufkmWf = false;
      string jCoVNolGHa;
      string NNXJyDxwCC;
      string souplQLUlC;
      string BxLuxlRykm;
      string aGrrHitPVX;
      string hmNXTtGzjw;
      string dRTEZQBcML;
      string lzLOblxDhC;
      string WuyNUNinaC;
      string eRNnJIlmRp;
      string gQDJkibzwg;
      string xDRgZiSGjL;
      string hNBJgUkWFS;
      string AJkrVFrnbl;
      string ljqtFbAfOa;
      string ofDFISOtcQ;
      string xFscgmRYLT;
      string qedyZyVHEE;
      string UEIecUGeiC;
      string qxKLngpONR;
      if(jCoVNolGHa == gQDJkibzwg){JaUtiKBFfK = true;}
      else if(gQDJkibzwg == jCoVNolGHa){XFIMmAHgHD = true;}
      if(NNXJyDxwCC == xDRgZiSGjL){xGoYwrwOAM = true;}
      else if(xDRgZiSGjL == NNXJyDxwCC){iTFZFIdgcV = true;}
      if(souplQLUlC == hNBJgUkWFS){gmpJbsTSJs = true;}
      else if(hNBJgUkWFS == souplQLUlC){wSzEsinOFI = true;}
      if(BxLuxlRykm == AJkrVFrnbl){HHtmusjNuS = true;}
      else if(AJkrVFrnbl == BxLuxlRykm){aZunUdYqaI = true;}
      if(aGrrHitPVX == ljqtFbAfOa){SAzYFjIlOu = true;}
      else if(ljqtFbAfOa == aGrrHitPVX){YMlzooTUyT = true;}
      if(hmNXTtGzjw == ofDFISOtcQ){jaOAjWkKSp = true;}
      else if(ofDFISOtcQ == hmNXTtGzjw){GXiATEGESE = true;}
      if(dRTEZQBcML == xFscgmRYLT){phulCoMCcC = true;}
      else if(xFscgmRYLT == dRTEZQBcML){MsazbJYQFa = true;}
      if(lzLOblxDhC == qedyZyVHEE){IiTgsfmQEr = true;}
      if(WuyNUNinaC == UEIecUGeiC){jhDNJgssDY = true;}
      if(eRNnJIlmRp == qxKLngpONR){IZuEbkFMVP = true;}
      while(qedyZyVHEE == lzLOblxDhC){imGUxjfzPE = true;}
      while(UEIecUGeiC == UEIecUGeiC){PSPkBDqtUP = true;}
      while(qxKLngpONR == qxKLngpONR){XUXVufkmWf = true;}
      if(JaUtiKBFfK == true){JaUtiKBFfK = false;}
      if(xGoYwrwOAM == true){xGoYwrwOAM = false;}
      if(gmpJbsTSJs == true){gmpJbsTSJs = false;}
      if(HHtmusjNuS == true){HHtmusjNuS = false;}
      if(SAzYFjIlOu == true){SAzYFjIlOu = false;}
      if(jaOAjWkKSp == true){jaOAjWkKSp = false;}
      if(phulCoMCcC == true){phulCoMCcC = false;}
      if(IiTgsfmQEr == true){IiTgsfmQEr = false;}
      if(jhDNJgssDY == true){jhDNJgssDY = false;}
      if(IZuEbkFMVP == true){IZuEbkFMVP = false;}
      if(XFIMmAHgHD == true){XFIMmAHgHD = false;}
      if(iTFZFIdgcV == true){iTFZFIdgcV = false;}
      if(wSzEsinOFI == true){wSzEsinOFI = false;}
      if(aZunUdYqaI == true){aZunUdYqaI = false;}
      if(YMlzooTUyT == true){YMlzooTUyT = false;}
      if(GXiATEGESE == true){GXiATEGESE = false;}
      if(MsazbJYQFa == true){MsazbJYQFa = false;}
      if(imGUxjfzPE == true){imGUxjfzPE = false;}
      if(PSPkBDqtUP == true){PSPkBDqtUP = false;}
      if(XUXVufkmWf == true){XUXVufkmWf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UANTYNDUGJ
{ 
  void uocsSHjTKt()
  { 
      bool ZCdadUTpwf = false;
      bool kPYREyDpDX = false;
      bool QhXgoMAfwI = false;
      bool xlcTghRDxV = false;
      bool GCOBeFAnGw = false;
      bool JfOaErexlR = false;
      bool TnsmhzlFkV = false;
      bool fzsgROTVBi = false;
      bool MMYzzQXCPo = false;
      bool DUQeCRIbSf = false;
      bool TtDkPJmgIo = false;
      bool XIuCFHPsnR = false;
      bool biouSLhNdA = false;
      bool FrDVPRInjo = false;
      bool dptZQtZOZu = false;
      bool CPmBDjEHRE = false;
      bool bYDIjfFYmm = false;
      bool yaJznloPeX = false;
      bool lTnixoECRe = false;
      bool MAVeMEmkpj = false;
      string OndXCaMfXW;
      string tNMMlGEfRS;
      string SrFDGBftEh;
      string NnXFhXTyIj;
      string idEsOuXLOU;
      string ZUpxYVhZQA;
      string tSaoJGpGeO;
      string lGWgjnnMoL;
      string dUeiIrxZgL;
      string osgHoPCOiI;
      string FQgzhSxJNj;
      string hVkEWZmqgQ;
      string IPYSZsYPqT;
      string kYcgGMnfAo;
      string unLxdSHckP;
      string bLgRzoqOYo;
      string thRtyIsEyJ;
      string lHqqVTDboH;
      string kwdaqZrKgQ;
      string UYGKuMWRyU;
      if(OndXCaMfXW == FQgzhSxJNj){ZCdadUTpwf = true;}
      else if(FQgzhSxJNj == OndXCaMfXW){TtDkPJmgIo = true;}
      if(tNMMlGEfRS == hVkEWZmqgQ){kPYREyDpDX = true;}
      else if(hVkEWZmqgQ == tNMMlGEfRS){XIuCFHPsnR = true;}
      if(SrFDGBftEh == IPYSZsYPqT){QhXgoMAfwI = true;}
      else if(IPYSZsYPqT == SrFDGBftEh){biouSLhNdA = true;}
      if(NnXFhXTyIj == kYcgGMnfAo){xlcTghRDxV = true;}
      else if(kYcgGMnfAo == NnXFhXTyIj){FrDVPRInjo = true;}
      if(idEsOuXLOU == unLxdSHckP){GCOBeFAnGw = true;}
      else if(unLxdSHckP == idEsOuXLOU){dptZQtZOZu = true;}
      if(ZUpxYVhZQA == bLgRzoqOYo){JfOaErexlR = true;}
      else if(bLgRzoqOYo == ZUpxYVhZQA){CPmBDjEHRE = true;}
      if(tSaoJGpGeO == thRtyIsEyJ){TnsmhzlFkV = true;}
      else if(thRtyIsEyJ == tSaoJGpGeO){bYDIjfFYmm = true;}
      if(lGWgjnnMoL == lHqqVTDboH){fzsgROTVBi = true;}
      if(dUeiIrxZgL == kwdaqZrKgQ){MMYzzQXCPo = true;}
      if(osgHoPCOiI == UYGKuMWRyU){DUQeCRIbSf = true;}
      while(lHqqVTDboH == lGWgjnnMoL){yaJznloPeX = true;}
      while(kwdaqZrKgQ == kwdaqZrKgQ){lTnixoECRe = true;}
      while(UYGKuMWRyU == UYGKuMWRyU){MAVeMEmkpj = true;}
      if(ZCdadUTpwf == true){ZCdadUTpwf = false;}
      if(kPYREyDpDX == true){kPYREyDpDX = false;}
      if(QhXgoMAfwI == true){QhXgoMAfwI = false;}
      if(xlcTghRDxV == true){xlcTghRDxV = false;}
      if(GCOBeFAnGw == true){GCOBeFAnGw = false;}
      if(JfOaErexlR == true){JfOaErexlR = false;}
      if(TnsmhzlFkV == true){TnsmhzlFkV = false;}
      if(fzsgROTVBi == true){fzsgROTVBi = false;}
      if(MMYzzQXCPo == true){MMYzzQXCPo = false;}
      if(DUQeCRIbSf == true){DUQeCRIbSf = false;}
      if(TtDkPJmgIo == true){TtDkPJmgIo = false;}
      if(XIuCFHPsnR == true){XIuCFHPsnR = false;}
      if(biouSLhNdA == true){biouSLhNdA = false;}
      if(FrDVPRInjo == true){FrDVPRInjo = false;}
      if(dptZQtZOZu == true){dptZQtZOZu = false;}
      if(CPmBDjEHRE == true){CPmBDjEHRE = false;}
      if(bYDIjfFYmm == true){bYDIjfFYmm = false;}
      if(yaJznloPeX == true){yaJznloPeX = false;}
      if(lTnixoECRe == true){lTnixoECRe = false;}
      if(MAVeMEmkpj == true){MAVeMEmkpj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKGBITMMPC
{ 
  void dAfqLAAwWH()
  { 
      bool XDkChlGYYP = false;
      bool dXEMAmPICs = false;
      bool ihdaRUwwrL = false;
      bool JoGfbnfrga = false;
      bool BbGVmyspxj = false;
      bool MGDhSpYJkM = false;
      bool pJgNFnRYjL = false;
      bool GWabrGbInT = false;
      bool aFzHyClYNl = false;
      bool PWHUkrtsPy = false;
      bool gUFkdofaoL = false;
      bool NQVQkjJZOD = false;
      bool CrKywiPGpA = false;
      bool MiromGANdJ = false;
      bool WKiCXzBqiB = false;
      bool hUdMwnJGnt = false;
      bool ZYkoyeXfce = false;
      bool iuwFgqJIZx = false;
      bool hYXoRqEfsz = false;
      bool xsZiixZsDs = false;
      string JbixWMLtzs;
      string WwrgIqpMQS;
      string NPmRdLUlOh;
      string eitsEfYgSw;
      string WRuEotRgZU;
      string HrHJFtnQTK;
      string rYeQOnCzbc;
      string RItTuuUhbi;
      string tnMsZlajmK;
      string qHNHExlepB;
      string rRExCzymNK;
      string YFojQDMkpc;
      string MRLRkKulPx;
      string IorZqbjOpa;
      string nmVckkSdqA;
      string jBnNoZGlMr;
      string ELXQBjNOrn;
      string SytOnYuhgz;
      string rQuONHBekR;
      string VyCyWcPFbB;
      if(JbixWMLtzs == rRExCzymNK){XDkChlGYYP = true;}
      else if(rRExCzymNK == JbixWMLtzs){gUFkdofaoL = true;}
      if(WwrgIqpMQS == YFojQDMkpc){dXEMAmPICs = true;}
      else if(YFojQDMkpc == WwrgIqpMQS){NQVQkjJZOD = true;}
      if(NPmRdLUlOh == MRLRkKulPx){ihdaRUwwrL = true;}
      else if(MRLRkKulPx == NPmRdLUlOh){CrKywiPGpA = true;}
      if(eitsEfYgSw == IorZqbjOpa){JoGfbnfrga = true;}
      else if(IorZqbjOpa == eitsEfYgSw){MiromGANdJ = true;}
      if(WRuEotRgZU == nmVckkSdqA){BbGVmyspxj = true;}
      else if(nmVckkSdqA == WRuEotRgZU){WKiCXzBqiB = true;}
      if(HrHJFtnQTK == jBnNoZGlMr){MGDhSpYJkM = true;}
      else if(jBnNoZGlMr == HrHJFtnQTK){hUdMwnJGnt = true;}
      if(rYeQOnCzbc == ELXQBjNOrn){pJgNFnRYjL = true;}
      else if(ELXQBjNOrn == rYeQOnCzbc){ZYkoyeXfce = true;}
      if(RItTuuUhbi == SytOnYuhgz){GWabrGbInT = true;}
      if(tnMsZlajmK == rQuONHBekR){aFzHyClYNl = true;}
      if(qHNHExlepB == VyCyWcPFbB){PWHUkrtsPy = true;}
      while(SytOnYuhgz == RItTuuUhbi){iuwFgqJIZx = true;}
      while(rQuONHBekR == rQuONHBekR){hYXoRqEfsz = true;}
      while(VyCyWcPFbB == VyCyWcPFbB){xsZiixZsDs = true;}
      if(XDkChlGYYP == true){XDkChlGYYP = false;}
      if(dXEMAmPICs == true){dXEMAmPICs = false;}
      if(ihdaRUwwrL == true){ihdaRUwwrL = false;}
      if(JoGfbnfrga == true){JoGfbnfrga = false;}
      if(BbGVmyspxj == true){BbGVmyspxj = false;}
      if(MGDhSpYJkM == true){MGDhSpYJkM = false;}
      if(pJgNFnRYjL == true){pJgNFnRYjL = false;}
      if(GWabrGbInT == true){GWabrGbInT = false;}
      if(aFzHyClYNl == true){aFzHyClYNl = false;}
      if(PWHUkrtsPy == true){PWHUkrtsPy = false;}
      if(gUFkdofaoL == true){gUFkdofaoL = false;}
      if(NQVQkjJZOD == true){NQVQkjJZOD = false;}
      if(CrKywiPGpA == true){CrKywiPGpA = false;}
      if(MiromGANdJ == true){MiromGANdJ = false;}
      if(WKiCXzBqiB == true){WKiCXzBqiB = false;}
      if(hUdMwnJGnt == true){hUdMwnJGnt = false;}
      if(ZYkoyeXfce == true){ZYkoyeXfce = false;}
      if(iuwFgqJIZx == true){iuwFgqJIZx = false;}
      if(hYXoRqEfsz == true){hYXoRqEfsz = false;}
      if(xsZiixZsDs == true){xsZiixZsDs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWLLTZKHRL
{ 
  void TrmtVFJoDr()
  { 
      bool NYbUAtRuZA = false;
      bool doLrsQrDag = false;
      bool mxUsVPLRoA = false;
      bool hFGSVMFecb = false;
      bool XbhGqbXkBS = false;
      bool DxPwpPDiyj = false;
      bool iAFYSYhsVg = false;
      bool KMZzJKOOBs = false;
      bool rZPWxjoJbF = false;
      bool JWfrsXWJnS = false;
      bool tdOUHpXQmf = false;
      bool AngErIjiah = false;
      bool iXQQXnfgFk = false;
      bool nFaizNLuOG = false;
      bool MYWwEUpbAj = false;
      bool nnhFiVMywT = false;
      bool KpKBruMxFd = false;
      bool xnTUVKBULC = false;
      bool yEgVxzWVAc = false;
      bool BNyuwVNUEJ = false;
      string blKTjbwoUL;
      string dLHlbizTmp;
      string hGRAzABSLH;
      string lVgYLWdWXR;
      string GungIquRiV;
      string BxemeUUKTj;
      string adcMZIehZE;
      string FbwUilSkqI;
      string FijpGoqstp;
      string CTCmqcRaGA;
      string MNqdQYBJDr;
      string CiSLeqtmGk;
      string QlmjClZIcF;
      string UrdpwqqFZh;
      string ngoCnSAqIA;
      string ieTVjaZHbe;
      string yrfyXKFbOm;
      string znMYwiwkui;
      string khAcWpXHGV;
      string QjcuiuBqdc;
      if(blKTjbwoUL == MNqdQYBJDr){NYbUAtRuZA = true;}
      else if(MNqdQYBJDr == blKTjbwoUL){tdOUHpXQmf = true;}
      if(dLHlbizTmp == CiSLeqtmGk){doLrsQrDag = true;}
      else if(CiSLeqtmGk == dLHlbizTmp){AngErIjiah = true;}
      if(hGRAzABSLH == QlmjClZIcF){mxUsVPLRoA = true;}
      else if(QlmjClZIcF == hGRAzABSLH){iXQQXnfgFk = true;}
      if(lVgYLWdWXR == UrdpwqqFZh){hFGSVMFecb = true;}
      else if(UrdpwqqFZh == lVgYLWdWXR){nFaizNLuOG = true;}
      if(GungIquRiV == ngoCnSAqIA){XbhGqbXkBS = true;}
      else if(ngoCnSAqIA == GungIquRiV){MYWwEUpbAj = true;}
      if(BxemeUUKTj == ieTVjaZHbe){DxPwpPDiyj = true;}
      else if(ieTVjaZHbe == BxemeUUKTj){nnhFiVMywT = true;}
      if(adcMZIehZE == yrfyXKFbOm){iAFYSYhsVg = true;}
      else if(yrfyXKFbOm == adcMZIehZE){KpKBruMxFd = true;}
      if(FbwUilSkqI == znMYwiwkui){KMZzJKOOBs = true;}
      if(FijpGoqstp == khAcWpXHGV){rZPWxjoJbF = true;}
      if(CTCmqcRaGA == QjcuiuBqdc){JWfrsXWJnS = true;}
      while(znMYwiwkui == FbwUilSkqI){xnTUVKBULC = true;}
      while(khAcWpXHGV == khAcWpXHGV){yEgVxzWVAc = true;}
      while(QjcuiuBqdc == QjcuiuBqdc){BNyuwVNUEJ = true;}
      if(NYbUAtRuZA == true){NYbUAtRuZA = false;}
      if(doLrsQrDag == true){doLrsQrDag = false;}
      if(mxUsVPLRoA == true){mxUsVPLRoA = false;}
      if(hFGSVMFecb == true){hFGSVMFecb = false;}
      if(XbhGqbXkBS == true){XbhGqbXkBS = false;}
      if(DxPwpPDiyj == true){DxPwpPDiyj = false;}
      if(iAFYSYhsVg == true){iAFYSYhsVg = false;}
      if(KMZzJKOOBs == true){KMZzJKOOBs = false;}
      if(rZPWxjoJbF == true){rZPWxjoJbF = false;}
      if(JWfrsXWJnS == true){JWfrsXWJnS = false;}
      if(tdOUHpXQmf == true){tdOUHpXQmf = false;}
      if(AngErIjiah == true){AngErIjiah = false;}
      if(iXQQXnfgFk == true){iXQQXnfgFk = false;}
      if(nFaizNLuOG == true){nFaizNLuOG = false;}
      if(MYWwEUpbAj == true){MYWwEUpbAj = false;}
      if(nnhFiVMywT == true){nnhFiVMywT = false;}
      if(KpKBruMxFd == true){KpKBruMxFd = false;}
      if(xnTUVKBULC == true){xnTUVKBULC = false;}
      if(yEgVxzWVAc == true){yEgVxzWVAc = false;}
      if(BNyuwVNUEJ == true){BNyuwVNUEJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWCBBKVTRH
{ 
  void AQGNQqpVcc()
  { 
      bool ISNJBNhnLE = false;
      bool lOHmIumdre = false;
      bool dSsMhNZmep = false;
      bool QlsVucYywV = false;
      bool taHZDInruE = false;
      bool rbrpUoYBan = false;
      bool muIUmzVkqe = false;
      bool VnhWkDLTIY = false;
      bool ZgqZynsDAF = false;
      bool EXWIhzRmlD = false;
      bool mCBPhDtVER = false;
      bool dFrBNFDiWy = false;
      bool GRjkayQYnl = false;
      bool kXgFlWfbqt = false;
      bool tXyibzeUtb = false;
      bool wiQmxUSPoj = false;
      bool mUgSfFXmPq = false;
      bool ZaqbEhTBJa = false;
      bool TudLpCHsIR = false;
      bool EPlHHYpfDV = false;
      string TSZMFWcxHr;
      string pxyikyfrlj;
      string wezEQZdlzY;
      string CLUTFCpMAk;
      string lWPTOWBRYz;
      string FJnchoSUue;
      string rpyhpdbech;
      string HTrByYOept;
      string YLNzTsWqlQ;
      string iVQUruXgdj;
      string tWnpqkRmeI;
      string ZmeBGgbzNw;
      string HjrLzlCWJC;
      string AgAGzBXWIi;
      string ajMcqupPOK;
      string TYSgbJdbqE;
      string hucbHrlXBF;
      string JFqeVXXPUE;
      string wmIyibOTdo;
      string WufDAeGkVy;
      if(TSZMFWcxHr == tWnpqkRmeI){ISNJBNhnLE = true;}
      else if(tWnpqkRmeI == TSZMFWcxHr){mCBPhDtVER = true;}
      if(pxyikyfrlj == ZmeBGgbzNw){lOHmIumdre = true;}
      else if(ZmeBGgbzNw == pxyikyfrlj){dFrBNFDiWy = true;}
      if(wezEQZdlzY == HjrLzlCWJC){dSsMhNZmep = true;}
      else if(HjrLzlCWJC == wezEQZdlzY){GRjkayQYnl = true;}
      if(CLUTFCpMAk == AgAGzBXWIi){QlsVucYywV = true;}
      else if(AgAGzBXWIi == CLUTFCpMAk){kXgFlWfbqt = true;}
      if(lWPTOWBRYz == ajMcqupPOK){taHZDInruE = true;}
      else if(ajMcqupPOK == lWPTOWBRYz){tXyibzeUtb = true;}
      if(FJnchoSUue == TYSgbJdbqE){rbrpUoYBan = true;}
      else if(TYSgbJdbqE == FJnchoSUue){wiQmxUSPoj = true;}
      if(rpyhpdbech == hucbHrlXBF){muIUmzVkqe = true;}
      else if(hucbHrlXBF == rpyhpdbech){mUgSfFXmPq = true;}
      if(HTrByYOept == JFqeVXXPUE){VnhWkDLTIY = true;}
      if(YLNzTsWqlQ == wmIyibOTdo){ZgqZynsDAF = true;}
      if(iVQUruXgdj == WufDAeGkVy){EXWIhzRmlD = true;}
      while(JFqeVXXPUE == HTrByYOept){ZaqbEhTBJa = true;}
      while(wmIyibOTdo == wmIyibOTdo){TudLpCHsIR = true;}
      while(WufDAeGkVy == WufDAeGkVy){EPlHHYpfDV = true;}
      if(ISNJBNhnLE == true){ISNJBNhnLE = false;}
      if(lOHmIumdre == true){lOHmIumdre = false;}
      if(dSsMhNZmep == true){dSsMhNZmep = false;}
      if(QlsVucYywV == true){QlsVucYywV = false;}
      if(taHZDInruE == true){taHZDInruE = false;}
      if(rbrpUoYBan == true){rbrpUoYBan = false;}
      if(muIUmzVkqe == true){muIUmzVkqe = false;}
      if(VnhWkDLTIY == true){VnhWkDLTIY = false;}
      if(ZgqZynsDAF == true){ZgqZynsDAF = false;}
      if(EXWIhzRmlD == true){EXWIhzRmlD = false;}
      if(mCBPhDtVER == true){mCBPhDtVER = false;}
      if(dFrBNFDiWy == true){dFrBNFDiWy = false;}
      if(GRjkayQYnl == true){GRjkayQYnl = false;}
      if(kXgFlWfbqt == true){kXgFlWfbqt = false;}
      if(tXyibzeUtb == true){tXyibzeUtb = false;}
      if(wiQmxUSPoj == true){wiQmxUSPoj = false;}
      if(mUgSfFXmPq == true){mUgSfFXmPq = false;}
      if(ZaqbEhTBJa == true){ZaqbEhTBJa = false;}
      if(TudLpCHsIR == true){TudLpCHsIR = false;}
      if(EPlHHYpfDV == true){EPlHHYpfDV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ATIWDHMSZM
{ 
  void knToUmOwTC()
  { 
      bool ddmqbpBOmh = false;
      bool FMUeEHaCLS = false;
      bool EZAyTYmQbr = false;
      bool JqNOWReAyA = false;
      bool rDYnufsoCU = false;
      bool NNqpgEdoXC = false;
      bool CjluXNyGHl = false;
      bool bZELZAALCn = false;
      bool eyOHduAWgS = false;
      bool nocuxHRdPg = false;
      bool gmgPrmIeQg = false;
      bool DRliWDVdQb = false;
      bool NaYnymxJNR = false;
      bool iWwVHrQyPp = false;
      bool mUGzPVCsYs = false;
      bool lmMnSFNsQF = false;
      bool pzRzygVQbe = false;
      bool mWOaosUZYb = false;
      bool jDkUeuKHDB = false;
      bool dXgKzmDHBh = false;
      string rHUehAAZpg;
      string fYHKmBRfrE;
      string IYCOlkRusB;
      string YBfJjmGcpT;
      string KjNOHpcExq;
      string TDpjFSFGsx;
      string iFfnIesyZz;
      string uooYtXKmGw;
      string HMxCgUKuDQ;
      string hzjsjFDZGc;
      string wedxueOQpg;
      string IRzxoVHdGm;
      string TytJRuEunn;
      string TkfdzciAGC;
      string GsEWIPzlDO;
      string xZSTIyjUfz;
      string ZScCMWlVyM;
      string mHXEfasXAB;
      string uSrZptSMVA;
      string rNTGbnQCJl;
      if(rHUehAAZpg == wedxueOQpg){ddmqbpBOmh = true;}
      else if(wedxueOQpg == rHUehAAZpg){gmgPrmIeQg = true;}
      if(fYHKmBRfrE == IRzxoVHdGm){FMUeEHaCLS = true;}
      else if(IRzxoVHdGm == fYHKmBRfrE){DRliWDVdQb = true;}
      if(IYCOlkRusB == TytJRuEunn){EZAyTYmQbr = true;}
      else if(TytJRuEunn == IYCOlkRusB){NaYnymxJNR = true;}
      if(YBfJjmGcpT == TkfdzciAGC){JqNOWReAyA = true;}
      else if(TkfdzciAGC == YBfJjmGcpT){iWwVHrQyPp = true;}
      if(KjNOHpcExq == GsEWIPzlDO){rDYnufsoCU = true;}
      else if(GsEWIPzlDO == KjNOHpcExq){mUGzPVCsYs = true;}
      if(TDpjFSFGsx == xZSTIyjUfz){NNqpgEdoXC = true;}
      else if(xZSTIyjUfz == TDpjFSFGsx){lmMnSFNsQF = true;}
      if(iFfnIesyZz == ZScCMWlVyM){CjluXNyGHl = true;}
      else if(ZScCMWlVyM == iFfnIesyZz){pzRzygVQbe = true;}
      if(uooYtXKmGw == mHXEfasXAB){bZELZAALCn = true;}
      if(HMxCgUKuDQ == uSrZptSMVA){eyOHduAWgS = true;}
      if(hzjsjFDZGc == rNTGbnQCJl){nocuxHRdPg = true;}
      while(mHXEfasXAB == uooYtXKmGw){mWOaosUZYb = true;}
      while(uSrZptSMVA == uSrZptSMVA){jDkUeuKHDB = true;}
      while(rNTGbnQCJl == rNTGbnQCJl){dXgKzmDHBh = true;}
      if(ddmqbpBOmh == true){ddmqbpBOmh = false;}
      if(FMUeEHaCLS == true){FMUeEHaCLS = false;}
      if(EZAyTYmQbr == true){EZAyTYmQbr = false;}
      if(JqNOWReAyA == true){JqNOWReAyA = false;}
      if(rDYnufsoCU == true){rDYnufsoCU = false;}
      if(NNqpgEdoXC == true){NNqpgEdoXC = false;}
      if(CjluXNyGHl == true){CjluXNyGHl = false;}
      if(bZELZAALCn == true){bZELZAALCn = false;}
      if(eyOHduAWgS == true){eyOHduAWgS = false;}
      if(nocuxHRdPg == true){nocuxHRdPg = false;}
      if(gmgPrmIeQg == true){gmgPrmIeQg = false;}
      if(DRliWDVdQb == true){DRliWDVdQb = false;}
      if(NaYnymxJNR == true){NaYnymxJNR = false;}
      if(iWwVHrQyPp == true){iWwVHrQyPp = false;}
      if(mUGzPVCsYs == true){mUGzPVCsYs = false;}
      if(lmMnSFNsQF == true){lmMnSFNsQF = false;}
      if(pzRzygVQbe == true){pzRzygVQbe = false;}
      if(mWOaosUZYb == true){mWOaosUZYb = false;}
      if(jDkUeuKHDB == true){jDkUeuKHDB = false;}
      if(dXgKzmDHBh == true){dXgKzmDHBh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWFPCXGCFF
{ 
  void QsZiHNqsPw()
  { 
      bool qczVroHHQO = false;
      bool ApeQkPqxtb = false;
      bool peEWOYHnEi = false;
      bool jTqifXWRhD = false;
      bool ZzjIYUqoAi = false;
      bool PgRhNLXbGT = false;
      bool gTChegzwjN = false;
      bool sYPpBqtwyt = false;
      bool hSmVTCCIVT = false;
      bool ztLNVGwCdr = false;
      bool VtEmppQafW = false;
      bool RbdMkOfgNb = false;
      bool dpZQNyNBTu = false;
      bool tqSGYmNAfd = false;
      bool kaczCXPzcG = false;
      bool ZOoBNeTnYq = false;
      bool bPGkbaJXnx = false;
      bool BfBjpDNaOp = false;
      bool iOYMUfBQrs = false;
      bool SZanBVUrWa = false;
      string UgXJSoDtiu;
      string ZjLwCodUwx;
      string bpAzqdHTlG;
      string URVDstEONH;
      string rkaIDZRKqZ;
      string SVbmNdgXRn;
      string hiHbZHOIDI;
      string jOHnEqPqwQ;
      string LwcLnzpioO;
      string NfwYZIcyhu;
      string LJHioDNmiW;
      string OobBckGwna;
      string RfSnuERiOu;
      string NRIAFCosWj;
      string kCzSAXEuun;
      string CgKHdfqSnk;
      string leXmIwgawZ;
      string uMYDpOfAmW;
      string AVmasgGBWY;
      string LWFkyGeLJD;
      if(UgXJSoDtiu == LJHioDNmiW){qczVroHHQO = true;}
      else if(LJHioDNmiW == UgXJSoDtiu){VtEmppQafW = true;}
      if(ZjLwCodUwx == OobBckGwna){ApeQkPqxtb = true;}
      else if(OobBckGwna == ZjLwCodUwx){RbdMkOfgNb = true;}
      if(bpAzqdHTlG == RfSnuERiOu){peEWOYHnEi = true;}
      else if(RfSnuERiOu == bpAzqdHTlG){dpZQNyNBTu = true;}
      if(URVDstEONH == NRIAFCosWj){jTqifXWRhD = true;}
      else if(NRIAFCosWj == URVDstEONH){tqSGYmNAfd = true;}
      if(rkaIDZRKqZ == kCzSAXEuun){ZzjIYUqoAi = true;}
      else if(kCzSAXEuun == rkaIDZRKqZ){kaczCXPzcG = true;}
      if(SVbmNdgXRn == CgKHdfqSnk){PgRhNLXbGT = true;}
      else if(CgKHdfqSnk == SVbmNdgXRn){ZOoBNeTnYq = true;}
      if(hiHbZHOIDI == leXmIwgawZ){gTChegzwjN = true;}
      else if(leXmIwgawZ == hiHbZHOIDI){bPGkbaJXnx = true;}
      if(jOHnEqPqwQ == uMYDpOfAmW){sYPpBqtwyt = true;}
      if(LwcLnzpioO == AVmasgGBWY){hSmVTCCIVT = true;}
      if(NfwYZIcyhu == LWFkyGeLJD){ztLNVGwCdr = true;}
      while(uMYDpOfAmW == jOHnEqPqwQ){BfBjpDNaOp = true;}
      while(AVmasgGBWY == AVmasgGBWY){iOYMUfBQrs = true;}
      while(LWFkyGeLJD == LWFkyGeLJD){SZanBVUrWa = true;}
      if(qczVroHHQO == true){qczVroHHQO = false;}
      if(ApeQkPqxtb == true){ApeQkPqxtb = false;}
      if(peEWOYHnEi == true){peEWOYHnEi = false;}
      if(jTqifXWRhD == true){jTqifXWRhD = false;}
      if(ZzjIYUqoAi == true){ZzjIYUqoAi = false;}
      if(PgRhNLXbGT == true){PgRhNLXbGT = false;}
      if(gTChegzwjN == true){gTChegzwjN = false;}
      if(sYPpBqtwyt == true){sYPpBqtwyt = false;}
      if(hSmVTCCIVT == true){hSmVTCCIVT = false;}
      if(ztLNVGwCdr == true){ztLNVGwCdr = false;}
      if(VtEmppQafW == true){VtEmppQafW = false;}
      if(RbdMkOfgNb == true){RbdMkOfgNb = false;}
      if(dpZQNyNBTu == true){dpZQNyNBTu = false;}
      if(tqSGYmNAfd == true){tqSGYmNAfd = false;}
      if(kaczCXPzcG == true){kaczCXPzcG = false;}
      if(ZOoBNeTnYq == true){ZOoBNeTnYq = false;}
      if(bPGkbaJXnx == true){bPGkbaJXnx = false;}
      if(BfBjpDNaOp == true){BfBjpDNaOp = false;}
      if(iOYMUfBQrs == true){iOYMUfBQrs = false;}
      if(SZanBVUrWa == true){SZanBVUrWa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZJCKLJQZC
{ 
  void TBwSRjmsxN()
  { 
      bool urKZdGSqYs = false;
      bool XAAXpAgwJm = false;
      bool gDaFSpsExI = false;
      bool SgcTXqNXjX = false;
      bool oiUzoprMjp = false;
      bool sWxJZqREGn = false;
      bool MOsPapWgAz = false;
      bool lJLkyxiaQc = false;
      bool ygUHOuiTsf = false;
      bool YIQwLaoEYy = false;
      bool SKLjEjLMLb = false;
      bool HpndofslBe = false;
      bool HDmTZdsPZX = false;
      bool IeCRKmUjCe = false;
      bool jVHRYiUmGe = false;
      bool gCDtqPWrKa = false;
      bool qwmnTcnWTC = false;
      bool KJiVukwVuq = false;
      bool IGItpFbHau = false;
      bool PcZbnniSyu = false;
      string XGyKpBVnei;
      string SreBsKFjmh;
      string HSHoyHRjom;
      string ZnJWipLhry;
      string babHXdziFT;
      string xFZKfFyIMh;
      string jkzrJdiHSC;
      string yXrnGfpzRT;
      string IieUoTOzpc;
      string qDVJNqbjyt;
      string uqPCUZNkDz;
      string OzqrZBGdDp;
      string OiRoLuBhaP;
      string EGBXYQSbzO;
      string GcuqOrLdjM;
      string jxfIeLZaqZ;
      string XeKntHxTSJ;
      string hddnilnZZS;
      string iXyOeHasrM;
      string prkZpaSHwG;
      if(XGyKpBVnei == uqPCUZNkDz){urKZdGSqYs = true;}
      else if(uqPCUZNkDz == XGyKpBVnei){SKLjEjLMLb = true;}
      if(SreBsKFjmh == OzqrZBGdDp){XAAXpAgwJm = true;}
      else if(OzqrZBGdDp == SreBsKFjmh){HpndofslBe = true;}
      if(HSHoyHRjom == OiRoLuBhaP){gDaFSpsExI = true;}
      else if(OiRoLuBhaP == HSHoyHRjom){HDmTZdsPZX = true;}
      if(ZnJWipLhry == EGBXYQSbzO){SgcTXqNXjX = true;}
      else if(EGBXYQSbzO == ZnJWipLhry){IeCRKmUjCe = true;}
      if(babHXdziFT == GcuqOrLdjM){oiUzoprMjp = true;}
      else if(GcuqOrLdjM == babHXdziFT){jVHRYiUmGe = true;}
      if(xFZKfFyIMh == jxfIeLZaqZ){sWxJZqREGn = true;}
      else if(jxfIeLZaqZ == xFZKfFyIMh){gCDtqPWrKa = true;}
      if(jkzrJdiHSC == XeKntHxTSJ){MOsPapWgAz = true;}
      else if(XeKntHxTSJ == jkzrJdiHSC){qwmnTcnWTC = true;}
      if(yXrnGfpzRT == hddnilnZZS){lJLkyxiaQc = true;}
      if(IieUoTOzpc == iXyOeHasrM){ygUHOuiTsf = true;}
      if(qDVJNqbjyt == prkZpaSHwG){YIQwLaoEYy = true;}
      while(hddnilnZZS == yXrnGfpzRT){KJiVukwVuq = true;}
      while(iXyOeHasrM == iXyOeHasrM){IGItpFbHau = true;}
      while(prkZpaSHwG == prkZpaSHwG){PcZbnniSyu = true;}
      if(urKZdGSqYs == true){urKZdGSqYs = false;}
      if(XAAXpAgwJm == true){XAAXpAgwJm = false;}
      if(gDaFSpsExI == true){gDaFSpsExI = false;}
      if(SgcTXqNXjX == true){SgcTXqNXjX = false;}
      if(oiUzoprMjp == true){oiUzoprMjp = false;}
      if(sWxJZqREGn == true){sWxJZqREGn = false;}
      if(MOsPapWgAz == true){MOsPapWgAz = false;}
      if(lJLkyxiaQc == true){lJLkyxiaQc = false;}
      if(ygUHOuiTsf == true){ygUHOuiTsf = false;}
      if(YIQwLaoEYy == true){YIQwLaoEYy = false;}
      if(SKLjEjLMLb == true){SKLjEjLMLb = false;}
      if(HpndofslBe == true){HpndofslBe = false;}
      if(HDmTZdsPZX == true){HDmTZdsPZX = false;}
      if(IeCRKmUjCe == true){IeCRKmUjCe = false;}
      if(jVHRYiUmGe == true){jVHRYiUmGe = false;}
      if(gCDtqPWrKa == true){gCDtqPWrKa = false;}
      if(qwmnTcnWTC == true){qwmnTcnWTC = false;}
      if(KJiVukwVuq == true){KJiVukwVuq = false;}
      if(IGItpFbHau == true){IGItpFbHau = false;}
      if(PcZbnniSyu == true){PcZbnniSyu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXCHFADQBR
{ 
  void CsWQPskMgq()
  { 
      bool nfkkfiwDlO = false;
      bool HYhjmRgIzU = false;
      bool KCanBDIWnH = false;
      bool wDIacnKSAx = false;
      bool nnWnyURYgB = false;
      bool jhqTNkFxjb = false;
      bool ZZPdSDPGHz = false;
      bool GNICgVemog = false;
      bool kjolXOMnNq = false;
      bool iNiXWOXrVt = false;
      bool ELQhuVYomq = false;
      bool FSHDqpjdGD = false;
      bool qbsPQsejeR = false;
      bool xmRubZSHqB = false;
      bool oXBVkQGfgg = false;
      bool dtlRCcRBQC = false;
      bool qoJUtSALaQ = false;
      bool WclEOSZXeA = false;
      bool lyDxnDAzry = false;
      bool IRpoKANfaR = false;
      string YdoZJrzJWU;
      string UTLERQKOmy;
      string fNpkyQMsXN;
      string WWPqtTuGkB;
      string jwJjPXjUPI;
      string rzocQLmDar;
      string eFkJyxETKx;
      string VEdlNjEGVa;
      string grcPUXgmai;
      string fqerVdKAlR;
      string SPJSlmVDPf;
      string HghALlcVnZ;
      string QRsbQdZkPi;
      string ZDUDHQiKcg;
      string BdWubzJdgi;
      string BoLLBBWhBH;
      string NkngFDLdsu;
      string DRrHYltxzQ;
      string TuEfgkrJCF;
      string sAIUTQppoY;
      if(YdoZJrzJWU == SPJSlmVDPf){nfkkfiwDlO = true;}
      else if(SPJSlmVDPf == YdoZJrzJWU){ELQhuVYomq = true;}
      if(UTLERQKOmy == HghALlcVnZ){HYhjmRgIzU = true;}
      else if(HghALlcVnZ == UTLERQKOmy){FSHDqpjdGD = true;}
      if(fNpkyQMsXN == QRsbQdZkPi){KCanBDIWnH = true;}
      else if(QRsbQdZkPi == fNpkyQMsXN){qbsPQsejeR = true;}
      if(WWPqtTuGkB == ZDUDHQiKcg){wDIacnKSAx = true;}
      else if(ZDUDHQiKcg == WWPqtTuGkB){xmRubZSHqB = true;}
      if(jwJjPXjUPI == BdWubzJdgi){nnWnyURYgB = true;}
      else if(BdWubzJdgi == jwJjPXjUPI){oXBVkQGfgg = true;}
      if(rzocQLmDar == BoLLBBWhBH){jhqTNkFxjb = true;}
      else if(BoLLBBWhBH == rzocQLmDar){dtlRCcRBQC = true;}
      if(eFkJyxETKx == NkngFDLdsu){ZZPdSDPGHz = true;}
      else if(NkngFDLdsu == eFkJyxETKx){qoJUtSALaQ = true;}
      if(VEdlNjEGVa == DRrHYltxzQ){GNICgVemog = true;}
      if(grcPUXgmai == TuEfgkrJCF){kjolXOMnNq = true;}
      if(fqerVdKAlR == sAIUTQppoY){iNiXWOXrVt = true;}
      while(DRrHYltxzQ == VEdlNjEGVa){WclEOSZXeA = true;}
      while(TuEfgkrJCF == TuEfgkrJCF){lyDxnDAzry = true;}
      while(sAIUTQppoY == sAIUTQppoY){IRpoKANfaR = true;}
      if(nfkkfiwDlO == true){nfkkfiwDlO = false;}
      if(HYhjmRgIzU == true){HYhjmRgIzU = false;}
      if(KCanBDIWnH == true){KCanBDIWnH = false;}
      if(wDIacnKSAx == true){wDIacnKSAx = false;}
      if(nnWnyURYgB == true){nnWnyURYgB = false;}
      if(jhqTNkFxjb == true){jhqTNkFxjb = false;}
      if(ZZPdSDPGHz == true){ZZPdSDPGHz = false;}
      if(GNICgVemog == true){GNICgVemog = false;}
      if(kjolXOMnNq == true){kjolXOMnNq = false;}
      if(iNiXWOXrVt == true){iNiXWOXrVt = false;}
      if(ELQhuVYomq == true){ELQhuVYomq = false;}
      if(FSHDqpjdGD == true){FSHDqpjdGD = false;}
      if(qbsPQsejeR == true){qbsPQsejeR = false;}
      if(xmRubZSHqB == true){xmRubZSHqB = false;}
      if(oXBVkQGfgg == true){oXBVkQGfgg = false;}
      if(dtlRCcRBQC == true){dtlRCcRBQC = false;}
      if(qoJUtSALaQ == true){qoJUtSALaQ = false;}
      if(WclEOSZXeA == true){WclEOSZXeA = false;}
      if(lyDxnDAzry == true){lyDxnDAzry = false;}
      if(IRpoKANfaR == true){IRpoKANfaR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VREJRQFMIM
{ 
  void OBwClTPNTx()
  { 
      bool FNXlGqzfdh = false;
      bool BYPWerBcfS = false;
      bool wumRgEjSQf = false;
      bool UwXNJfbRJa = false;
      bool IOxJtLAxiF = false;
      bool OunREKaFEB = false;
      bool GgPxMEBBMz = false;
      bool QiSEKhxcWV = false;
      bool EljKRYIFJz = false;
      bool EVNHUayzwp = false;
      bool JyjiofbiHW = false;
      bool MxiixTxEfn = false;
      bool uwrNttVLji = false;
      bool ixffMFCAUl = false;
      bool wZxlmHldKA = false;
      bool dtTItNGWot = false;
      bool KQyYmPQCWq = false;
      bool RxitqVyFam = false;
      bool IqAjEodWky = false;
      bool zeKaafbYzW = false;
      string kxAgSHBMPA;
      string fifiBVHoYc;
      string QNizlPIEqs;
      string yURjyMqIqq;
      string GXWrwTxYSp;
      string aNSkIXNAtC;
      string zxVWCLQwjo;
      string dyyhWrpqDR;
      string SjkARkBgba;
      string ypNnqICApk;
      string CBndMbPjNQ;
      string hWxcjPMUEQ;
      string JjTIqmjJqO;
      string opASORuHnp;
      string VQSLsbskEa;
      string wguYaSgelY;
      string qFsyaqVeNR;
      string UEgOusQIPP;
      string tzEPSItaqw;
      string jPUOyPXTkB;
      if(kxAgSHBMPA == CBndMbPjNQ){FNXlGqzfdh = true;}
      else if(CBndMbPjNQ == kxAgSHBMPA){JyjiofbiHW = true;}
      if(fifiBVHoYc == hWxcjPMUEQ){BYPWerBcfS = true;}
      else if(hWxcjPMUEQ == fifiBVHoYc){MxiixTxEfn = true;}
      if(QNizlPIEqs == JjTIqmjJqO){wumRgEjSQf = true;}
      else if(JjTIqmjJqO == QNizlPIEqs){uwrNttVLji = true;}
      if(yURjyMqIqq == opASORuHnp){UwXNJfbRJa = true;}
      else if(opASORuHnp == yURjyMqIqq){ixffMFCAUl = true;}
      if(GXWrwTxYSp == VQSLsbskEa){IOxJtLAxiF = true;}
      else if(VQSLsbskEa == GXWrwTxYSp){wZxlmHldKA = true;}
      if(aNSkIXNAtC == wguYaSgelY){OunREKaFEB = true;}
      else if(wguYaSgelY == aNSkIXNAtC){dtTItNGWot = true;}
      if(zxVWCLQwjo == qFsyaqVeNR){GgPxMEBBMz = true;}
      else if(qFsyaqVeNR == zxVWCLQwjo){KQyYmPQCWq = true;}
      if(dyyhWrpqDR == UEgOusQIPP){QiSEKhxcWV = true;}
      if(SjkARkBgba == tzEPSItaqw){EljKRYIFJz = true;}
      if(ypNnqICApk == jPUOyPXTkB){EVNHUayzwp = true;}
      while(UEgOusQIPP == dyyhWrpqDR){RxitqVyFam = true;}
      while(tzEPSItaqw == tzEPSItaqw){IqAjEodWky = true;}
      while(jPUOyPXTkB == jPUOyPXTkB){zeKaafbYzW = true;}
      if(FNXlGqzfdh == true){FNXlGqzfdh = false;}
      if(BYPWerBcfS == true){BYPWerBcfS = false;}
      if(wumRgEjSQf == true){wumRgEjSQf = false;}
      if(UwXNJfbRJa == true){UwXNJfbRJa = false;}
      if(IOxJtLAxiF == true){IOxJtLAxiF = false;}
      if(OunREKaFEB == true){OunREKaFEB = false;}
      if(GgPxMEBBMz == true){GgPxMEBBMz = false;}
      if(QiSEKhxcWV == true){QiSEKhxcWV = false;}
      if(EljKRYIFJz == true){EljKRYIFJz = false;}
      if(EVNHUayzwp == true){EVNHUayzwp = false;}
      if(JyjiofbiHW == true){JyjiofbiHW = false;}
      if(MxiixTxEfn == true){MxiixTxEfn = false;}
      if(uwrNttVLji == true){uwrNttVLji = false;}
      if(ixffMFCAUl == true){ixffMFCAUl = false;}
      if(wZxlmHldKA == true){wZxlmHldKA = false;}
      if(dtTItNGWot == true){dtTItNGWot = false;}
      if(KQyYmPQCWq == true){KQyYmPQCWq = false;}
      if(RxitqVyFam == true){RxitqVyFam = false;}
      if(IqAjEodWky == true){IqAjEodWky = false;}
      if(zeKaafbYzW == true){zeKaafbYzW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTNTINCLGW
{ 
  void cGuUEWbGQD()
  { 
      bool mnKHYzhXuP = false;
      bool ytCPcUfiOL = false;
      bool XIuPqHomGt = false;
      bool scDpDrdYUT = false;
      bool rufHFDROgN = false;
      bool zftUSdruQQ = false;
      bool JuQAWVpMMk = false;
      bool qHNtTbbnJm = false;
      bool paFrtNhhWY = false;
      bool ziHDKxefjj = false;
      bool MECwWrSzBp = false;
      bool CEkcaioXFJ = false;
      bool mIonkHzJjV = false;
      bool xuEZZkYIVC = false;
      bool uhfgVuydca = false;
      bool HHZawEONLO = false;
      bool rIPesGzKDp = false;
      bool KfBCNEbIRp = false;
      bool JUgIOoVccU = false;
      bool VKxGKlSBnO = false;
      string nslZwLtMRS;
      string cscjlOKqru;
      string mjaELPalbK;
      string ROAKMVDBxQ;
      string hiFolHBXiJ;
      string ljzkxESgNg;
      string jIkHBOsRXQ;
      string KItbNEekSD;
      string NDDSXhOOMI;
      string DVnQgZyxnX;
      string OjzSydpXWs;
      string YgOJSfFRjS;
      string zdEPMnTctn;
      string GgxuodEjTs;
      string rqrTiWHexA;
      string TfNVXkejFJ;
      string JMcilrjSTo;
      string bUxpZHlkgp;
      string goftTaTbWE;
      string yUeKifOIgq;
      if(nslZwLtMRS == OjzSydpXWs){mnKHYzhXuP = true;}
      else if(OjzSydpXWs == nslZwLtMRS){MECwWrSzBp = true;}
      if(cscjlOKqru == YgOJSfFRjS){ytCPcUfiOL = true;}
      else if(YgOJSfFRjS == cscjlOKqru){CEkcaioXFJ = true;}
      if(mjaELPalbK == zdEPMnTctn){XIuPqHomGt = true;}
      else if(zdEPMnTctn == mjaELPalbK){mIonkHzJjV = true;}
      if(ROAKMVDBxQ == GgxuodEjTs){scDpDrdYUT = true;}
      else if(GgxuodEjTs == ROAKMVDBxQ){xuEZZkYIVC = true;}
      if(hiFolHBXiJ == rqrTiWHexA){rufHFDROgN = true;}
      else if(rqrTiWHexA == hiFolHBXiJ){uhfgVuydca = true;}
      if(ljzkxESgNg == TfNVXkejFJ){zftUSdruQQ = true;}
      else if(TfNVXkejFJ == ljzkxESgNg){HHZawEONLO = true;}
      if(jIkHBOsRXQ == JMcilrjSTo){JuQAWVpMMk = true;}
      else if(JMcilrjSTo == jIkHBOsRXQ){rIPesGzKDp = true;}
      if(KItbNEekSD == bUxpZHlkgp){qHNtTbbnJm = true;}
      if(NDDSXhOOMI == goftTaTbWE){paFrtNhhWY = true;}
      if(DVnQgZyxnX == yUeKifOIgq){ziHDKxefjj = true;}
      while(bUxpZHlkgp == KItbNEekSD){KfBCNEbIRp = true;}
      while(goftTaTbWE == goftTaTbWE){JUgIOoVccU = true;}
      while(yUeKifOIgq == yUeKifOIgq){VKxGKlSBnO = true;}
      if(mnKHYzhXuP == true){mnKHYzhXuP = false;}
      if(ytCPcUfiOL == true){ytCPcUfiOL = false;}
      if(XIuPqHomGt == true){XIuPqHomGt = false;}
      if(scDpDrdYUT == true){scDpDrdYUT = false;}
      if(rufHFDROgN == true){rufHFDROgN = false;}
      if(zftUSdruQQ == true){zftUSdruQQ = false;}
      if(JuQAWVpMMk == true){JuQAWVpMMk = false;}
      if(qHNtTbbnJm == true){qHNtTbbnJm = false;}
      if(paFrtNhhWY == true){paFrtNhhWY = false;}
      if(ziHDKxefjj == true){ziHDKxefjj = false;}
      if(MECwWrSzBp == true){MECwWrSzBp = false;}
      if(CEkcaioXFJ == true){CEkcaioXFJ = false;}
      if(mIonkHzJjV == true){mIonkHzJjV = false;}
      if(xuEZZkYIVC == true){xuEZZkYIVC = false;}
      if(uhfgVuydca == true){uhfgVuydca = false;}
      if(HHZawEONLO == true){HHZawEONLO = false;}
      if(rIPesGzKDp == true){rIPesGzKDp = false;}
      if(KfBCNEbIRp == true){KfBCNEbIRp = false;}
      if(JUgIOoVccU == true){JUgIOoVccU = false;}
      if(VKxGKlSBnO == true){VKxGKlSBnO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPEMFJKQZN
{ 
  void rimplsqBaf()
  { 
      bool UIoZzJqUCo = false;
      bool abUdICPKam = false;
      bool kdlLLmytPy = false;
      bool KVgPRCllZw = false;
      bool gjZqoEIbpP = false;
      bool NqXgBpVdNL = false;
      bool KwEEeEuFLG = false;
      bool PckeGBEuVH = false;
      bool dVDzjSyANb = false;
      bool fIYNkjeVMj = false;
      bool JDQjzjGsaz = false;
      bool laHGhorFTM = false;
      bool GuqjZHEWsV = false;
      bool WihkxaESzA = false;
      bool MEZOoFBRfu = false;
      bool qZBzdOLgKr = false;
      bool fizEcDrVIH = false;
      bool jZFTABVctU = false;
      bool FlqydwgiHi = false;
      bool OXIGTcFUkl = false;
      string zwkbhdOtuB;
      string OKQKbpHlZX;
      string xQQwdNIlEw;
      string LFigHWVFoD;
      string QnezKWsFkc;
      string aCuFehfoxU;
      string UboyoJbiDF;
      string UCxWGIlQkH;
      string TDBbUJKcCY;
      string pfIThnzfJB;
      string tJCeIYFXyV;
      string wODoBRaNdf;
      string zzgeOntdnS;
      string JGHjMJBVTw;
      string EldfcbcSRP;
      string NkCdCucWQT;
      string daifLpHTcr;
      string QEthaMUACm;
      string LbLYFYEcgQ;
      string fdFzRcCyTm;
      if(zwkbhdOtuB == tJCeIYFXyV){UIoZzJqUCo = true;}
      else if(tJCeIYFXyV == zwkbhdOtuB){JDQjzjGsaz = true;}
      if(OKQKbpHlZX == wODoBRaNdf){abUdICPKam = true;}
      else if(wODoBRaNdf == OKQKbpHlZX){laHGhorFTM = true;}
      if(xQQwdNIlEw == zzgeOntdnS){kdlLLmytPy = true;}
      else if(zzgeOntdnS == xQQwdNIlEw){GuqjZHEWsV = true;}
      if(LFigHWVFoD == JGHjMJBVTw){KVgPRCllZw = true;}
      else if(JGHjMJBVTw == LFigHWVFoD){WihkxaESzA = true;}
      if(QnezKWsFkc == EldfcbcSRP){gjZqoEIbpP = true;}
      else if(EldfcbcSRP == QnezKWsFkc){MEZOoFBRfu = true;}
      if(aCuFehfoxU == NkCdCucWQT){NqXgBpVdNL = true;}
      else if(NkCdCucWQT == aCuFehfoxU){qZBzdOLgKr = true;}
      if(UboyoJbiDF == daifLpHTcr){KwEEeEuFLG = true;}
      else if(daifLpHTcr == UboyoJbiDF){fizEcDrVIH = true;}
      if(UCxWGIlQkH == QEthaMUACm){PckeGBEuVH = true;}
      if(TDBbUJKcCY == LbLYFYEcgQ){dVDzjSyANb = true;}
      if(pfIThnzfJB == fdFzRcCyTm){fIYNkjeVMj = true;}
      while(QEthaMUACm == UCxWGIlQkH){jZFTABVctU = true;}
      while(LbLYFYEcgQ == LbLYFYEcgQ){FlqydwgiHi = true;}
      while(fdFzRcCyTm == fdFzRcCyTm){OXIGTcFUkl = true;}
      if(UIoZzJqUCo == true){UIoZzJqUCo = false;}
      if(abUdICPKam == true){abUdICPKam = false;}
      if(kdlLLmytPy == true){kdlLLmytPy = false;}
      if(KVgPRCllZw == true){KVgPRCllZw = false;}
      if(gjZqoEIbpP == true){gjZqoEIbpP = false;}
      if(NqXgBpVdNL == true){NqXgBpVdNL = false;}
      if(KwEEeEuFLG == true){KwEEeEuFLG = false;}
      if(PckeGBEuVH == true){PckeGBEuVH = false;}
      if(dVDzjSyANb == true){dVDzjSyANb = false;}
      if(fIYNkjeVMj == true){fIYNkjeVMj = false;}
      if(JDQjzjGsaz == true){JDQjzjGsaz = false;}
      if(laHGhorFTM == true){laHGhorFTM = false;}
      if(GuqjZHEWsV == true){GuqjZHEWsV = false;}
      if(WihkxaESzA == true){WihkxaESzA = false;}
      if(MEZOoFBRfu == true){MEZOoFBRfu = false;}
      if(qZBzdOLgKr == true){qZBzdOLgKr = false;}
      if(fizEcDrVIH == true){fizEcDrVIH = false;}
      if(jZFTABVctU == true){jZFTABVctU = false;}
      if(FlqydwgiHi == true){FlqydwgiHi = false;}
      if(OXIGTcFUkl == true){OXIGTcFUkl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMUSXRYEYP
{ 
  void nrJKixaJpO()
  { 
      bool lXxDSIjynB = false;
      bool JpDgysjPxk = false;
      bool iRFTtKWlUu = false;
      bool pWBnOQiuTz = false;
      bool LFzVRmbgsY = false;
      bool JCKcxURcJH = false;
      bool lycsLlnORh = false;
      bool KouxYdRjBG = false;
      bool iorwknMXqt = false;
      bool yFlLNNcGJe = false;
      bool zNOLOUGMES = false;
      bool ChbCYwFfHW = false;
      bool ZPWXiEDijL = false;
      bool AKZVHVafgQ = false;
      bool hzTYqQdimQ = false;
      bool IwzlFippcJ = false;
      bool RWcrSqHFuC = false;
      bool VYypoauygS = false;
      bool aTwSCELmQX = false;
      bool ejDXzKWaFz = false;
      string jfYIsXLsow;
      string FZMUBmtGIL;
      string MxAwxdOGgS;
      string yMKJitmQyK;
      string ghoqdxXzia;
      string bPunVlecLO;
      string JEMWysPClH;
      string zdIxeeIISz;
      string GPWFphRWnx;
      string OKEiBbUSrk;
      string hVMaayGxIq;
      string cVJMIsgHfP;
      string bsNosoYYuC;
      string JpQgQkDwdr;
      string bTNwTrAraI;
      string tNlbJoHXhl;
      string ZhCFhmFcuX;
      string pkdnnHeQUB;
      string nfymIwDnWb;
      string deOqSsRHOf;
      if(jfYIsXLsow == hVMaayGxIq){lXxDSIjynB = true;}
      else if(hVMaayGxIq == jfYIsXLsow){zNOLOUGMES = true;}
      if(FZMUBmtGIL == cVJMIsgHfP){JpDgysjPxk = true;}
      else if(cVJMIsgHfP == FZMUBmtGIL){ChbCYwFfHW = true;}
      if(MxAwxdOGgS == bsNosoYYuC){iRFTtKWlUu = true;}
      else if(bsNosoYYuC == MxAwxdOGgS){ZPWXiEDijL = true;}
      if(yMKJitmQyK == JpQgQkDwdr){pWBnOQiuTz = true;}
      else if(JpQgQkDwdr == yMKJitmQyK){AKZVHVafgQ = true;}
      if(ghoqdxXzia == bTNwTrAraI){LFzVRmbgsY = true;}
      else if(bTNwTrAraI == ghoqdxXzia){hzTYqQdimQ = true;}
      if(bPunVlecLO == tNlbJoHXhl){JCKcxURcJH = true;}
      else if(tNlbJoHXhl == bPunVlecLO){IwzlFippcJ = true;}
      if(JEMWysPClH == ZhCFhmFcuX){lycsLlnORh = true;}
      else if(ZhCFhmFcuX == JEMWysPClH){RWcrSqHFuC = true;}
      if(zdIxeeIISz == pkdnnHeQUB){KouxYdRjBG = true;}
      if(GPWFphRWnx == nfymIwDnWb){iorwknMXqt = true;}
      if(OKEiBbUSrk == deOqSsRHOf){yFlLNNcGJe = true;}
      while(pkdnnHeQUB == zdIxeeIISz){VYypoauygS = true;}
      while(nfymIwDnWb == nfymIwDnWb){aTwSCELmQX = true;}
      while(deOqSsRHOf == deOqSsRHOf){ejDXzKWaFz = true;}
      if(lXxDSIjynB == true){lXxDSIjynB = false;}
      if(JpDgysjPxk == true){JpDgysjPxk = false;}
      if(iRFTtKWlUu == true){iRFTtKWlUu = false;}
      if(pWBnOQiuTz == true){pWBnOQiuTz = false;}
      if(LFzVRmbgsY == true){LFzVRmbgsY = false;}
      if(JCKcxURcJH == true){JCKcxURcJH = false;}
      if(lycsLlnORh == true){lycsLlnORh = false;}
      if(KouxYdRjBG == true){KouxYdRjBG = false;}
      if(iorwknMXqt == true){iorwknMXqt = false;}
      if(yFlLNNcGJe == true){yFlLNNcGJe = false;}
      if(zNOLOUGMES == true){zNOLOUGMES = false;}
      if(ChbCYwFfHW == true){ChbCYwFfHW = false;}
      if(ZPWXiEDijL == true){ZPWXiEDijL = false;}
      if(AKZVHVafgQ == true){AKZVHVafgQ = false;}
      if(hzTYqQdimQ == true){hzTYqQdimQ = false;}
      if(IwzlFippcJ == true){IwzlFippcJ = false;}
      if(RWcrSqHFuC == true){RWcrSqHFuC = false;}
      if(VYypoauygS == true){VYypoauygS = false;}
      if(aTwSCELmQX == true){aTwSCELmQX = false;}
      if(ejDXzKWaFz == true){ejDXzKWaFz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHPMYTNRWO
{ 
  void TweXlukyGd()
  { 
      bool HXGzzgDPIN = false;
      bool gMSUVTTomi = false;
      bool ACuzDRDQKV = false;
      bool DjTLrwNuiJ = false;
      bool etTEGiEQax = false;
      bool pYekUEbHuh = false;
      bool clElKxsGbZ = false;
      bool GXGcDGipsU = false;
      bool MmoMfdFhqn = false;
      bool TGAAfrogtJ = false;
      bool oxoBqRRBgO = false;
      bool VkNaVpxrGf = false;
      bool qKPnFzXGwK = false;
      bool QBwjfOxnVN = false;
      bool LDBcRhsZeo = false;
      bool uxaNRdhAur = false;
      bool sLEVxUodtG = false;
      bool rIVrUnJlVW = false;
      bool GyaGOTZiSC = false;
      bool fwscUzyefx = false;
      string nCIjyqAWkb;
      string sDZdHBrHXQ;
      string cAwKVdtojo;
      string lERtcnwVQy;
      string fGXkZRGLaA;
      string bBVcomGyOT;
      string wLlwpnkeAT;
      string EWqZjVcLkD;
      string XiOjMjinFo;
      string gyGwCUUatl;
      string faKHwFKusS;
      string KuMLwMxCiF;
      string FxZLlFPuXO;
      string BBQzWwXGnH;
      string Zmuldlkuzo;
      string XRqnfiAzUp;
      string oPXdRJeNnz;
      string opObfSBmgA;
      string TUuhqiJbSn;
      string wXlxRJORTU;
      if(nCIjyqAWkb == faKHwFKusS){HXGzzgDPIN = true;}
      else if(faKHwFKusS == nCIjyqAWkb){oxoBqRRBgO = true;}
      if(sDZdHBrHXQ == KuMLwMxCiF){gMSUVTTomi = true;}
      else if(KuMLwMxCiF == sDZdHBrHXQ){VkNaVpxrGf = true;}
      if(cAwKVdtojo == FxZLlFPuXO){ACuzDRDQKV = true;}
      else if(FxZLlFPuXO == cAwKVdtojo){qKPnFzXGwK = true;}
      if(lERtcnwVQy == BBQzWwXGnH){DjTLrwNuiJ = true;}
      else if(BBQzWwXGnH == lERtcnwVQy){QBwjfOxnVN = true;}
      if(fGXkZRGLaA == Zmuldlkuzo){etTEGiEQax = true;}
      else if(Zmuldlkuzo == fGXkZRGLaA){LDBcRhsZeo = true;}
      if(bBVcomGyOT == XRqnfiAzUp){pYekUEbHuh = true;}
      else if(XRqnfiAzUp == bBVcomGyOT){uxaNRdhAur = true;}
      if(wLlwpnkeAT == oPXdRJeNnz){clElKxsGbZ = true;}
      else if(oPXdRJeNnz == wLlwpnkeAT){sLEVxUodtG = true;}
      if(EWqZjVcLkD == opObfSBmgA){GXGcDGipsU = true;}
      if(XiOjMjinFo == TUuhqiJbSn){MmoMfdFhqn = true;}
      if(gyGwCUUatl == wXlxRJORTU){TGAAfrogtJ = true;}
      while(opObfSBmgA == EWqZjVcLkD){rIVrUnJlVW = true;}
      while(TUuhqiJbSn == TUuhqiJbSn){GyaGOTZiSC = true;}
      while(wXlxRJORTU == wXlxRJORTU){fwscUzyefx = true;}
      if(HXGzzgDPIN == true){HXGzzgDPIN = false;}
      if(gMSUVTTomi == true){gMSUVTTomi = false;}
      if(ACuzDRDQKV == true){ACuzDRDQKV = false;}
      if(DjTLrwNuiJ == true){DjTLrwNuiJ = false;}
      if(etTEGiEQax == true){etTEGiEQax = false;}
      if(pYekUEbHuh == true){pYekUEbHuh = false;}
      if(clElKxsGbZ == true){clElKxsGbZ = false;}
      if(GXGcDGipsU == true){GXGcDGipsU = false;}
      if(MmoMfdFhqn == true){MmoMfdFhqn = false;}
      if(TGAAfrogtJ == true){TGAAfrogtJ = false;}
      if(oxoBqRRBgO == true){oxoBqRRBgO = false;}
      if(VkNaVpxrGf == true){VkNaVpxrGf = false;}
      if(qKPnFzXGwK == true){qKPnFzXGwK = false;}
      if(QBwjfOxnVN == true){QBwjfOxnVN = false;}
      if(LDBcRhsZeo == true){LDBcRhsZeo = false;}
      if(uxaNRdhAur == true){uxaNRdhAur = false;}
      if(sLEVxUodtG == true){sLEVxUodtG = false;}
      if(rIVrUnJlVW == true){rIVrUnJlVW = false;}
      if(GyaGOTZiSC == true){GyaGOTZiSC = false;}
      if(fwscUzyefx == true){fwscUzyefx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEJHOCWLQJ
{ 
  void xFOedAwlTT()
  { 
      bool xpDwNLhUgp = false;
      bool RYujRTASGB = false;
      bool iiIxtumAgr = false;
      bool DyRyOFJicZ = false;
      bool pfuQKllDnU = false;
      bool zrQuWNhGCR = false;
      bool XgmomSGwVM = false;
      bool KQpgLCnqlH = false;
      bool JjMMsKhVaA = false;
      bool WCgLBJsFdq = false;
      bool fogbKhCjjU = false;
      bool ZpTtHnUawc = false;
      bool kjVVoHjeeC = false;
      bool JhNtbTCjCK = false;
      bool HxlGZghlDN = false;
      bool nSJBGuTKmC = false;
      bool yXEgKqbZSn = false;
      bool kjXlUnyOuH = false;
      bool YxaRNqYMnf = false;
      bool zrxzMisEui = false;
      string ufJgkTioXP;
      string amUdkocgSk;
      string BuPirChSfk;
      string xgTXRoHMql;
      string OYVPixYGOx;
      string oDVlNAPaoi;
      string kPJmRtTxLw;
      string hPpgWbYAAu;
      string cbDiusKgJQ;
      string ZfXIAyPhxn;
      string cbtSOYNoPl;
      string aOasFJLaqX;
      string jmmtWBrhfX;
      string MqCLSAgjTV;
      string fUQXpKFeCp;
      string lnpZEoozwN;
      string gfIrZjMPaF;
      string caGVrOWPEL;
      string uNfpkXAcGc;
      string LgnGnzLXxG;
      if(ufJgkTioXP == cbtSOYNoPl){xpDwNLhUgp = true;}
      else if(cbtSOYNoPl == ufJgkTioXP){fogbKhCjjU = true;}
      if(amUdkocgSk == aOasFJLaqX){RYujRTASGB = true;}
      else if(aOasFJLaqX == amUdkocgSk){ZpTtHnUawc = true;}
      if(BuPirChSfk == jmmtWBrhfX){iiIxtumAgr = true;}
      else if(jmmtWBrhfX == BuPirChSfk){kjVVoHjeeC = true;}
      if(xgTXRoHMql == MqCLSAgjTV){DyRyOFJicZ = true;}
      else if(MqCLSAgjTV == xgTXRoHMql){JhNtbTCjCK = true;}
      if(OYVPixYGOx == fUQXpKFeCp){pfuQKllDnU = true;}
      else if(fUQXpKFeCp == OYVPixYGOx){HxlGZghlDN = true;}
      if(oDVlNAPaoi == lnpZEoozwN){zrQuWNhGCR = true;}
      else if(lnpZEoozwN == oDVlNAPaoi){nSJBGuTKmC = true;}
      if(kPJmRtTxLw == gfIrZjMPaF){XgmomSGwVM = true;}
      else if(gfIrZjMPaF == kPJmRtTxLw){yXEgKqbZSn = true;}
      if(hPpgWbYAAu == caGVrOWPEL){KQpgLCnqlH = true;}
      if(cbDiusKgJQ == uNfpkXAcGc){JjMMsKhVaA = true;}
      if(ZfXIAyPhxn == LgnGnzLXxG){WCgLBJsFdq = true;}
      while(caGVrOWPEL == hPpgWbYAAu){kjXlUnyOuH = true;}
      while(uNfpkXAcGc == uNfpkXAcGc){YxaRNqYMnf = true;}
      while(LgnGnzLXxG == LgnGnzLXxG){zrxzMisEui = true;}
      if(xpDwNLhUgp == true){xpDwNLhUgp = false;}
      if(RYujRTASGB == true){RYujRTASGB = false;}
      if(iiIxtumAgr == true){iiIxtumAgr = false;}
      if(DyRyOFJicZ == true){DyRyOFJicZ = false;}
      if(pfuQKllDnU == true){pfuQKllDnU = false;}
      if(zrQuWNhGCR == true){zrQuWNhGCR = false;}
      if(XgmomSGwVM == true){XgmomSGwVM = false;}
      if(KQpgLCnqlH == true){KQpgLCnqlH = false;}
      if(JjMMsKhVaA == true){JjMMsKhVaA = false;}
      if(WCgLBJsFdq == true){WCgLBJsFdq = false;}
      if(fogbKhCjjU == true){fogbKhCjjU = false;}
      if(ZpTtHnUawc == true){ZpTtHnUawc = false;}
      if(kjVVoHjeeC == true){kjVVoHjeeC = false;}
      if(JhNtbTCjCK == true){JhNtbTCjCK = false;}
      if(HxlGZghlDN == true){HxlGZghlDN = false;}
      if(nSJBGuTKmC == true){nSJBGuTKmC = false;}
      if(yXEgKqbZSn == true){yXEgKqbZSn = false;}
      if(kjXlUnyOuH == true){kjXlUnyOuH = false;}
      if(YxaRNqYMnf == true){YxaRNqYMnf = false;}
      if(zrxzMisEui == true){zrxzMisEui = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEPVCZVSJK
{ 
  void OCMbbMpoho()
  { 
      bool mYtVzXJLyg = false;
      bool jhzWTpDnHK = false;
      bool ATZQmEHpbH = false;
      bool RPujGxiMZP = false;
      bool hyTKbhfNfW = false;
      bool fQjejTzcit = false;
      bool PSjpOTmPPV = false;
      bool HqOqcCzPnE = false;
      bool XsKEaBfPzm = false;
      bool yFceAONduH = false;
      bool uQyJPoBrCh = false;
      bool TjodWVIeON = false;
      bool nWPbXBNjqN = false;
      bool nVTfJGuAnl = false;
      bool znMRTOQzHe = false;
      bool GiOhTYAVkN = false;
      bool aRBotxQIUP = false;
      bool ZHqcOzJyIJ = false;
      bool kObLHFHkMj = false;
      bool GZOaKgmXXW = false;
      string UzHtZNxuwQ;
      string NkfoNWrIRJ;
      string kVtHRCtNSa;
      string klCLMYEjko;
      string tKpiTWSKZW;
      string aSyOWyEAcX;
      string TicUfbiTbn;
      string SHWcPaeKmt;
      string iinuzRmmoN;
      string TEHNULhVDr;
      string nyhlETuVzu;
      string TtMinkugUN;
      string nueOUNAIIE;
      string sJHuFjACpf;
      string WRmstZqXZj;
      string PAAoDrTTQp;
      string SlMuCJlRdD;
      string jrpoqWHlTt;
      string WciYnrJRqM;
      string QfkzNjEqpj;
      if(UzHtZNxuwQ == nyhlETuVzu){mYtVzXJLyg = true;}
      else if(nyhlETuVzu == UzHtZNxuwQ){uQyJPoBrCh = true;}
      if(NkfoNWrIRJ == TtMinkugUN){jhzWTpDnHK = true;}
      else if(TtMinkugUN == NkfoNWrIRJ){TjodWVIeON = true;}
      if(kVtHRCtNSa == nueOUNAIIE){ATZQmEHpbH = true;}
      else if(nueOUNAIIE == kVtHRCtNSa){nWPbXBNjqN = true;}
      if(klCLMYEjko == sJHuFjACpf){RPujGxiMZP = true;}
      else if(sJHuFjACpf == klCLMYEjko){nVTfJGuAnl = true;}
      if(tKpiTWSKZW == WRmstZqXZj){hyTKbhfNfW = true;}
      else if(WRmstZqXZj == tKpiTWSKZW){znMRTOQzHe = true;}
      if(aSyOWyEAcX == PAAoDrTTQp){fQjejTzcit = true;}
      else if(PAAoDrTTQp == aSyOWyEAcX){GiOhTYAVkN = true;}
      if(TicUfbiTbn == SlMuCJlRdD){PSjpOTmPPV = true;}
      else if(SlMuCJlRdD == TicUfbiTbn){aRBotxQIUP = true;}
      if(SHWcPaeKmt == jrpoqWHlTt){HqOqcCzPnE = true;}
      if(iinuzRmmoN == WciYnrJRqM){XsKEaBfPzm = true;}
      if(TEHNULhVDr == QfkzNjEqpj){yFceAONduH = true;}
      while(jrpoqWHlTt == SHWcPaeKmt){ZHqcOzJyIJ = true;}
      while(WciYnrJRqM == WciYnrJRqM){kObLHFHkMj = true;}
      while(QfkzNjEqpj == QfkzNjEqpj){GZOaKgmXXW = true;}
      if(mYtVzXJLyg == true){mYtVzXJLyg = false;}
      if(jhzWTpDnHK == true){jhzWTpDnHK = false;}
      if(ATZQmEHpbH == true){ATZQmEHpbH = false;}
      if(RPujGxiMZP == true){RPujGxiMZP = false;}
      if(hyTKbhfNfW == true){hyTKbhfNfW = false;}
      if(fQjejTzcit == true){fQjejTzcit = false;}
      if(PSjpOTmPPV == true){PSjpOTmPPV = false;}
      if(HqOqcCzPnE == true){HqOqcCzPnE = false;}
      if(XsKEaBfPzm == true){XsKEaBfPzm = false;}
      if(yFceAONduH == true){yFceAONduH = false;}
      if(uQyJPoBrCh == true){uQyJPoBrCh = false;}
      if(TjodWVIeON == true){TjodWVIeON = false;}
      if(nWPbXBNjqN == true){nWPbXBNjqN = false;}
      if(nVTfJGuAnl == true){nVTfJGuAnl = false;}
      if(znMRTOQzHe == true){znMRTOQzHe = false;}
      if(GiOhTYAVkN == true){GiOhTYAVkN = false;}
      if(aRBotxQIUP == true){aRBotxQIUP = false;}
      if(ZHqcOzJyIJ == true){ZHqcOzJyIJ = false;}
      if(kObLHFHkMj == true){kObLHFHkMj = false;}
      if(GZOaKgmXXW == true){GZOaKgmXXW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNPWFRPZTT
{ 
  void hWDlZoFBfh()
  { 
      bool oPUaZVyXRq = false;
      bool kbGXEjpWBm = false;
      bool SPwzyQiMwp = false;
      bool EwDmocRFOL = false;
      bool FznwRQdGFZ = false;
      bool EeKCUYTVbI = false;
      bool llabloXTia = false;
      bool RjHphSbAhh = false;
      bool mcGWlZkBRP = false;
      bool JwcGYTYMJb = false;
      bool rJXeHTXTUB = false;
      bool xSnsUJfEpM = false;
      bool DVBSRVHBQN = false;
      bool tOpFocFaOR = false;
      bool CRgPSpIikP = false;
      bool mUWxYWIENl = false;
      bool MVCGHhchDq = false;
      bool EEoXKknkAa = false;
      bool MXQBaZrsfS = false;
      bool UANbFfOaIj = false;
      string ozAdFkQgZK;
      string bjXAULqHbn;
      string BgFamnNyEZ;
      string XVlsbmwLmR;
      string ubQqWtbKZG;
      string MnjrrHtZqQ;
      string WRbAlFxdYh;
      string PeTJsZQODs;
      string LDXyNjltBT;
      string rWUVtczPER;
      string xylrpgTZzS;
      string pfVxETsdlB;
      string SDbEpsKxOP;
      string ZAJlwNRfHf;
      string QMuhcLAWRa;
      string iUdDysVgBx;
      string WVKirpWjBq;
      string BNWFkGItad;
      string smfngEWGmC;
      string rjdJJtBMpm;
      if(ozAdFkQgZK == xylrpgTZzS){oPUaZVyXRq = true;}
      else if(xylrpgTZzS == ozAdFkQgZK){rJXeHTXTUB = true;}
      if(bjXAULqHbn == pfVxETsdlB){kbGXEjpWBm = true;}
      else if(pfVxETsdlB == bjXAULqHbn){xSnsUJfEpM = true;}
      if(BgFamnNyEZ == SDbEpsKxOP){SPwzyQiMwp = true;}
      else if(SDbEpsKxOP == BgFamnNyEZ){DVBSRVHBQN = true;}
      if(XVlsbmwLmR == ZAJlwNRfHf){EwDmocRFOL = true;}
      else if(ZAJlwNRfHf == XVlsbmwLmR){tOpFocFaOR = true;}
      if(ubQqWtbKZG == QMuhcLAWRa){FznwRQdGFZ = true;}
      else if(QMuhcLAWRa == ubQqWtbKZG){CRgPSpIikP = true;}
      if(MnjrrHtZqQ == iUdDysVgBx){EeKCUYTVbI = true;}
      else if(iUdDysVgBx == MnjrrHtZqQ){mUWxYWIENl = true;}
      if(WRbAlFxdYh == WVKirpWjBq){llabloXTia = true;}
      else if(WVKirpWjBq == WRbAlFxdYh){MVCGHhchDq = true;}
      if(PeTJsZQODs == BNWFkGItad){RjHphSbAhh = true;}
      if(LDXyNjltBT == smfngEWGmC){mcGWlZkBRP = true;}
      if(rWUVtczPER == rjdJJtBMpm){JwcGYTYMJb = true;}
      while(BNWFkGItad == PeTJsZQODs){EEoXKknkAa = true;}
      while(smfngEWGmC == smfngEWGmC){MXQBaZrsfS = true;}
      while(rjdJJtBMpm == rjdJJtBMpm){UANbFfOaIj = true;}
      if(oPUaZVyXRq == true){oPUaZVyXRq = false;}
      if(kbGXEjpWBm == true){kbGXEjpWBm = false;}
      if(SPwzyQiMwp == true){SPwzyQiMwp = false;}
      if(EwDmocRFOL == true){EwDmocRFOL = false;}
      if(FznwRQdGFZ == true){FznwRQdGFZ = false;}
      if(EeKCUYTVbI == true){EeKCUYTVbI = false;}
      if(llabloXTia == true){llabloXTia = false;}
      if(RjHphSbAhh == true){RjHphSbAhh = false;}
      if(mcGWlZkBRP == true){mcGWlZkBRP = false;}
      if(JwcGYTYMJb == true){JwcGYTYMJb = false;}
      if(rJXeHTXTUB == true){rJXeHTXTUB = false;}
      if(xSnsUJfEpM == true){xSnsUJfEpM = false;}
      if(DVBSRVHBQN == true){DVBSRVHBQN = false;}
      if(tOpFocFaOR == true){tOpFocFaOR = false;}
      if(CRgPSpIikP == true){CRgPSpIikP = false;}
      if(mUWxYWIENl == true){mUWxYWIENl = false;}
      if(MVCGHhchDq == true){MVCGHhchDq = false;}
      if(EEoXKknkAa == true){EEoXKknkAa = false;}
      if(MXQBaZrsfS == true){MXQBaZrsfS = false;}
      if(UANbFfOaIj == true){UANbFfOaIj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQHVKHTQZQ
{ 
  void kElmmWhwYF()
  { 
      bool lNSgKuEGnf = false;
      bool qRRIEkjgTz = false;
      bool qyhPHfbiJj = false;
      bool QyNxarTBiF = false;
      bool TxVEQKqknp = false;
      bool QCEuQneCYd = false;
      bool SVwDOrEThM = false;
      bool QixOetbcyx = false;
      bool optTSOtSfl = false;
      bool MQbEmyASpY = false;
      bool GWDbYhEpPW = false;
      bool MBEbobackA = false;
      bool ylnuzzGrbg = false;
      bool tImYpRmRtk = false;
      bool JDDJZKMAPK = false;
      bool XWhoaUiHbZ = false;
      bool bLNhcDOekX = false;
      bool oIizptidUo = false;
      bool mFcRJWayyV = false;
      bool iepUIxoUfW = false;
      string amwhYSuupB;
      string BoQwmbwIHF;
      string RUgxjeoPKK;
      string LKpsxsTiBw;
      string iyDTkfZeWG;
      string MZeIwFFzyt;
      string dejepqyXzt;
      string INHKVSRNMD;
      string FKrDxkegwq;
      string mTkGSENXds;
      string gBecyzSTmd;
      string nrltoTlghE;
      string LRaIHnbArR;
      string FsjSWDePEx;
      string SKtSCthpRy;
      string RgpYgOZWVK;
      string WRaUXtITXk;
      string nWbjkBXIFM;
      string FlhtAYDKkH;
      string cItsaBjYtI;
      if(amwhYSuupB == gBecyzSTmd){lNSgKuEGnf = true;}
      else if(gBecyzSTmd == amwhYSuupB){GWDbYhEpPW = true;}
      if(BoQwmbwIHF == nrltoTlghE){qRRIEkjgTz = true;}
      else if(nrltoTlghE == BoQwmbwIHF){MBEbobackA = true;}
      if(RUgxjeoPKK == LRaIHnbArR){qyhPHfbiJj = true;}
      else if(LRaIHnbArR == RUgxjeoPKK){ylnuzzGrbg = true;}
      if(LKpsxsTiBw == FsjSWDePEx){QyNxarTBiF = true;}
      else if(FsjSWDePEx == LKpsxsTiBw){tImYpRmRtk = true;}
      if(iyDTkfZeWG == SKtSCthpRy){TxVEQKqknp = true;}
      else if(SKtSCthpRy == iyDTkfZeWG){JDDJZKMAPK = true;}
      if(MZeIwFFzyt == RgpYgOZWVK){QCEuQneCYd = true;}
      else if(RgpYgOZWVK == MZeIwFFzyt){XWhoaUiHbZ = true;}
      if(dejepqyXzt == WRaUXtITXk){SVwDOrEThM = true;}
      else if(WRaUXtITXk == dejepqyXzt){bLNhcDOekX = true;}
      if(INHKVSRNMD == nWbjkBXIFM){QixOetbcyx = true;}
      if(FKrDxkegwq == FlhtAYDKkH){optTSOtSfl = true;}
      if(mTkGSENXds == cItsaBjYtI){MQbEmyASpY = true;}
      while(nWbjkBXIFM == INHKVSRNMD){oIizptidUo = true;}
      while(FlhtAYDKkH == FlhtAYDKkH){mFcRJWayyV = true;}
      while(cItsaBjYtI == cItsaBjYtI){iepUIxoUfW = true;}
      if(lNSgKuEGnf == true){lNSgKuEGnf = false;}
      if(qRRIEkjgTz == true){qRRIEkjgTz = false;}
      if(qyhPHfbiJj == true){qyhPHfbiJj = false;}
      if(QyNxarTBiF == true){QyNxarTBiF = false;}
      if(TxVEQKqknp == true){TxVEQKqknp = false;}
      if(QCEuQneCYd == true){QCEuQneCYd = false;}
      if(SVwDOrEThM == true){SVwDOrEThM = false;}
      if(QixOetbcyx == true){QixOetbcyx = false;}
      if(optTSOtSfl == true){optTSOtSfl = false;}
      if(MQbEmyASpY == true){MQbEmyASpY = false;}
      if(GWDbYhEpPW == true){GWDbYhEpPW = false;}
      if(MBEbobackA == true){MBEbobackA = false;}
      if(ylnuzzGrbg == true){ylnuzzGrbg = false;}
      if(tImYpRmRtk == true){tImYpRmRtk = false;}
      if(JDDJZKMAPK == true){JDDJZKMAPK = false;}
      if(XWhoaUiHbZ == true){XWhoaUiHbZ = false;}
      if(bLNhcDOekX == true){bLNhcDOekX = false;}
      if(oIizptidUo == true){oIizptidUo = false;}
      if(mFcRJWayyV == true){mFcRJWayyV = false;}
      if(iepUIxoUfW == true){iepUIxoUfW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNXBWZTJQF
{ 
  void DrxmzRorMo()
  { 
      bool xDEuGaCilp = false;
      bool ouWhdaseno = false;
      bool loewpQMmLt = false;
      bool xdHypALNmO = false;
      bool hKuMPpVouN = false;
      bool qVIAgIXHFp = false;
      bool NOXrsLnXqc = false;
      bool PfrZHasRfA = false;
      bool tXrxDaUHQh = false;
      bool bDIwASmDTE = false;
      bool CxxRxKdhsF = false;
      bool OGbFupWZnR = false;
      bool pfHJAMXuZn = false;
      bool npxbxxZZzr = false;
      bool xmOKSVaCBJ = false;
      bool uMOCOVonRk = false;
      bool mhIEQYIAHx = false;
      bool QxZuUDRwpd = false;
      bool kUsQrbauMb = false;
      bool HlIOFOdJst = false;
      string tVSSbnNIXI;
      string aVxpCpgYnd;
      string OmNqJnPJIy;
      string RxRuPAmkPb;
      string rhqboWGehb;
      string HsrOGGIbJm;
      string YEAYqcEBZB;
      string CuJLlgwkCm;
      string hjagqXFCoJ;
      string rLacDmhRkL;
      string REEgYLjfbY;
      string KWYVFncSgS;
      string XBMQJqUgHy;
      string zdAqUcftHf;
      string nYaPzUlFXO;
      string JOjRnPrnWh;
      string qDXcZfWhBb;
      string IiLBeyawRn;
      string EPJsokshCE;
      string krWYokBxoT;
      if(tVSSbnNIXI == REEgYLjfbY){xDEuGaCilp = true;}
      else if(REEgYLjfbY == tVSSbnNIXI){CxxRxKdhsF = true;}
      if(aVxpCpgYnd == KWYVFncSgS){ouWhdaseno = true;}
      else if(KWYVFncSgS == aVxpCpgYnd){OGbFupWZnR = true;}
      if(OmNqJnPJIy == XBMQJqUgHy){loewpQMmLt = true;}
      else if(XBMQJqUgHy == OmNqJnPJIy){pfHJAMXuZn = true;}
      if(RxRuPAmkPb == zdAqUcftHf){xdHypALNmO = true;}
      else if(zdAqUcftHf == RxRuPAmkPb){npxbxxZZzr = true;}
      if(rhqboWGehb == nYaPzUlFXO){hKuMPpVouN = true;}
      else if(nYaPzUlFXO == rhqboWGehb){xmOKSVaCBJ = true;}
      if(HsrOGGIbJm == JOjRnPrnWh){qVIAgIXHFp = true;}
      else if(JOjRnPrnWh == HsrOGGIbJm){uMOCOVonRk = true;}
      if(YEAYqcEBZB == qDXcZfWhBb){NOXrsLnXqc = true;}
      else if(qDXcZfWhBb == YEAYqcEBZB){mhIEQYIAHx = true;}
      if(CuJLlgwkCm == IiLBeyawRn){PfrZHasRfA = true;}
      if(hjagqXFCoJ == EPJsokshCE){tXrxDaUHQh = true;}
      if(rLacDmhRkL == krWYokBxoT){bDIwASmDTE = true;}
      while(IiLBeyawRn == CuJLlgwkCm){QxZuUDRwpd = true;}
      while(EPJsokshCE == EPJsokshCE){kUsQrbauMb = true;}
      while(krWYokBxoT == krWYokBxoT){HlIOFOdJst = true;}
      if(xDEuGaCilp == true){xDEuGaCilp = false;}
      if(ouWhdaseno == true){ouWhdaseno = false;}
      if(loewpQMmLt == true){loewpQMmLt = false;}
      if(xdHypALNmO == true){xdHypALNmO = false;}
      if(hKuMPpVouN == true){hKuMPpVouN = false;}
      if(qVIAgIXHFp == true){qVIAgIXHFp = false;}
      if(NOXrsLnXqc == true){NOXrsLnXqc = false;}
      if(PfrZHasRfA == true){PfrZHasRfA = false;}
      if(tXrxDaUHQh == true){tXrxDaUHQh = false;}
      if(bDIwASmDTE == true){bDIwASmDTE = false;}
      if(CxxRxKdhsF == true){CxxRxKdhsF = false;}
      if(OGbFupWZnR == true){OGbFupWZnR = false;}
      if(pfHJAMXuZn == true){pfHJAMXuZn = false;}
      if(npxbxxZZzr == true){npxbxxZZzr = false;}
      if(xmOKSVaCBJ == true){xmOKSVaCBJ = false;}
      if(uMOCOVonRk == true){uMOCOVonRk = false;}
      if(mhIEQYIAHx == true){mhIEQYIAHx = false;}
      if(QxZuUDRwpd == true){QxZuUDRwpd = false;}
      if(kUsQrbauMb == true){kUsQrbauMb = false;}
      if(HlIOFOdJst == true){HlIOFOdJst = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTUXRVQNXL
{ 
  void uVxVJXUfGF()
  { 
      bool ZDYsxthcZu = false;
      bool MtAdHooYMN = false;
      bool xqacWRjprN = false;
      bool nccrnOYYwR = false;
      bool mRDGdOrzwS = false;
      bool ZJUtNhbwVe = false;
      bool KqkLGjQIps = false;
      bool PPcuafmTyI = false;
      bool YjsYneHidF = false;
      bool mcCQHugrAt = false;
      bool xjJCCJgZTh = false;
      bool uHxNFZxLXb = false;
      bool bhekGlNLme = false;
      bool zuTELoaqWd = false;
      bool xhOuJefoLg = false;
      bool xVTYROFYwP = false;
      bool wUlnizmrBQ = false;
      bool zGnsdtSiaa = false;
      bool GXAGgdbulx = false;
      bool jBtGhbuaMK = false;
      string FBEJcIolAf;
      string ujBDwVnAxR;
      string bsMtTIrgIc;
      string IDNAdnpSOf;
      string CdxahMJjJE;
      string AljKcLoKpT;
      string PIcXWqVAZH;
      string eUlRPxwlLG;
      string yHXEbWTCWS;
      string yfctQtAYDq;
      string qJKBZfzSuf;
      string ODyjUIkYwA;
      string XScGJzrrAV;
      string wWhUPoxVew;
      string WAHqDugsYH;
      string IbcDSXfDrZ;
      string nHRZirVdTf;
      string KOtAcXKlDN;
      string RySsMUtdCq;
      string IsdEHOihIL;
      if(FBEJcIolAf == qJKBZfzSuf){ZDYsxthcZu = true;}
      else if(qJKBZfzSuf == FBEJcIolAf){xjJCCJgZTh = true;}
      if(ujBDwVnAxR == ODyjUIkYwA){MtAdHooYMN = true;}
      else if(ODyjUIkYwA == ujBDwVnAxR){uHxNFZxLXb = true;}
      if(bsMtTIrgIc == XScGJzrrAV){xqacWRjprN = true;}
      else if(XScGJzrrAV == bsMtTIrgIc){bhekGlNLme = true;}
      if(IDNAdnpSOf == wWhUPoxVew){nccrnOYYwR = true;}
      else if(wWhUPoxVew == IDNAdnpSOf){zuTELoaqWd = true;}
      if(CdxahMJjJE == WAHqDugsYH){mRDGdOrzwS = true;}
      else if(WAHqDugsYH == CdxahMJjJE){xhOuJefoLg = true;}
      if(AljKcLoKpT == IbcDSXfDrZ){ZJUtNhbwVe = true;}
      else if(IbcDSXfDrZ == AljKcLoKpT){xVTYROFYwP = true;}
      if(PIcXWqVAZH == nHRZirVdTf){KqkLGjQIps = true;}
      else if(nHRZirVdTf == PIcXWqVAZH){wUlnizmrBQ = true;}
      if(eUlRPxwlLG == KOtAcXKlDN){PPcuafmTyI = true;}
      if(yHXEbWTCWS == RySsMUtdCq){YjsYneHidF = true;}
      if(yfctQtAYDq == IsdEHOihIL){mcCQHugrAt = true;}
      while(KOtAcXKlDN == eUlRPxwlLG){zGnsdtSiaa = true;}
      while(RySsMUtdCq == RySsMUtdCq){GXAGgdbulx = true;}
      while(IsdEHOihIL == IsdEHOihIL){jBtGhbuaMK = true;}
      if(ZDYsxthcZu == true){ZDYsxthcZu = false;}
      if(MtAdHooYMN == true){MtAdHooYMN = false;}
      if(xqacWRjprN == true){xqacWRjprN = false;}
      if(nccrnOYYwR == true){nccrnOYYwR = false;}
      if(mRDGdOrzwS == true){mRDGdOrzwS = false;}
      if(ZJUtNhbwVe == true){ZJUtNhbwVe = false;}
      if(KqkLGjQIps == true){KqkLGjQIps = false;}
      if(PPcuafmTyI == true){PPcuafmTyI = false;}
      if(YjsYneHidF == true){YjsYneHidF = false;}
      if(mcCQHugrAt == true){mcCQHugrAt = false;}
      if(xjJCCJgZTh == true){xjJCCJgZTh = false;}
      if(uHxNFZxLXb == true){uHxNFZxLXb = false;}
      if(bhekGlNLme == true){bhekGlNLme = false;}
      if(zuTELoaqWd == true){zuTELoaqWd = false;}
      if(xhOuJefoLg == true){xhOuJefoLg = false;}
      if(xVTYROFYwP == true){xVTYROFYwP = false;}
      if(wUlnizmrBQ == true){wUlnizmrBQ = false;}
      if(zGnsdtSiaa == true){zGnsdtSiaa = false;}
      if(GXAGgdbulx == true){GXAGgdbulx = false;}
      if(jBtGhbuaMK == true){jBtGhbuaMK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDEHCYHKDQ
{ 
  void gZdVKieEGc()
  { 
      bool zEcYZoXgWO = false;
      bool cREBlSOoqL = false;
      bool ittnZkitTY = false;
      bool OahSfsVRwV = false;
      bool jcBodqoeHg = false;
      bool oeXIdFJozn = false;
      bool GdNxzBilVs = false;
      bool wxsUaFrEKh = false;
      bool uElljiDZoZ = false;
      bool igRHPGOEob = false;
      bool IDINkrlCgX = false;
      bool MFdRrCqaNP = false;
      bool yJxwKOekFU = false;
      bool qnOhYruYBr = false;
      bool xArQMdCAOM = false;
      bool OmqYcyFMDV = false;
      bool MAxMfYpwrA = false;
      bool GSYUSxQfig = false;
      bool LdVrFDxpFZ = false;
      bool liUfewDfkn = false;
      string XxmnTeCcFd;
      string locGSZhpWC;
      string FXuSRQSfyO;
      string fBzLKLWQWc;
      string EIbjAQbRll;
      string HUgPkACTWC;
      string LVeqxkpRwH;
      string CRSsxxuKSA;
      string oAsMGLTiaK;
      string JDtURhcklP;
      string ZKVeioCnRm;
      string EqBVNLcRjl;
      string QGpkxzXxbP;
      string TKYCadeNdR;
      string IfQmGSCXHF;
      string ELAAyTUjgj;
      string RELCTsSyui;
      string fOnScjpCee;
      string xzpVLHKXEG;
      string JtftzEUOTM;
      if(XxmnTeCcFd == ZKVeioCnRm){zEcYZoXgWO = true;}
      else if(ZKVeioCnRm == XxmnTeCcFd){IDINkrlCgX = true;}
      if(locGSZhpWC == EqBVNLcRjl){cREBlSOoqL = true;}
      else if(EqBVNLcRjl == locGSZhpWC){MFdRrCqaNP = true;}
      if(FXuSRQSfyO == QGpkxzXxbP){ittnZkitTY = true;}
      else if(QGpkxzXxbP == FXuSRQSfyO){yJxwKOekFU = true;}
      if(fBzLKLWQWc == TKYCadeNdR){OahSfsVRwV = true;}
      else if(TKYCadeNdR == fBzLKLWQWc){qnOhYruYBr = true;}
      if(EIbjAQbRll == IfQmGSCXHF){jcBodqoeHg = true;}
      else if(IfQmGSCXHF == EIbjAQbRll){xArQMdCAOM = true;}
      if(HUgPkACTWC == ELAAyTUjgj){oeXIdFJozn = true;}
      else if(ELAAyTUjgj == HUgPkACTWC){OmqYcyFMDV = true;}
      if(LVeqxkpRwH == RELCTsSyui){GdNxzBilVs = true;}
      else if(RELCTsSyui == LVeqxkpRwH){MAxMfYpwrA = true;}
      if(CRSsxxuKSA == fOnScjpCee){wxsUaFrEKh = true;}
      if(oAsMGLTiaK == xzpVLHKXEG){uElljiDZoZ = true;}
      if(JDtURhcklP == JtftzEUOTM){igRHPGOEob = true;}
      while(fOnScjpCee == CRSsxxuKSA){GSYUSxQfig = true;}
      while(xzpVLHKXEG == xzpVLHKXEG){LdVrFDxpFZ = true;}
      while(JtftzEUOTM == JtftzEUOTM){liUfewDfkn = true;}
      if(zEcYZoXgWO == true){zEcYZoXgWO = false;}
      if(cREBlSOoqL == true){cREBlSOoqL = false;}
      if(ittnZkitTY == true){ittnZkitTY = false;}
      if(OahSfsVRwV == true){OahSfsVRwV = false;}
      if(jcBodqoeHg == true){jcBodqoeHg = false;}
      if(oeXIdFJozn == true){oeXIdFJozn = false;}
      if(GdNxzBilVs == true){GdNxzBilVs = false;}
      if(wxsUaFrEKh == true){wxsUaFrEKh = false;}
      if(uElljiDZoZ == true){uElljiDZoZ = false;}
      if(igRHPGOEob == true){igRHPGOEob = false;}
      if(IDINkrlCgX == true){IDINkrlCgX = false;}
      if(MFdRrCqaNP == true){MFdRrCqaNP = false;}
      if(yJxwKOekFU == true){yJxwKOekFU = false;}
      if(qnOhYruYBr == true){qnOhYruYBr = false;}
      if(xArQMdCAOM == true){xArQMdCAOM = false;}
      if(OmqYcyFMDV == true){OmqYcyFMDV = false;}
      if(MAxMfYpwrA == true){MAxMfYpwrA = false;}
      if(GSYUSxQfig == true){GSYUSxQfig = false;}
      if(LdVrFDxpFZ == true){LdVrFDxpFZ = false;}
      if(liUfewDfkn == true){liUfewDfkn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZCTVWXTPN
{ 
  void qyBMKfsOBl()
  { 
      bool HxcYebWejJ = false;
      bool sNLKglqnnf = false;
      bool mptIhKFrje = false;
      bool xSDVqrEMTb = false;
      bool hKtzyWYAQR = false;
      bool pkCpyQCUqT = false;
      bool WeuEMaJoSn = false;
      bool heTLybwtJK = false;
      bool lEaSoLPNWZ = false;
      bool piUzECPomX = false;
      bool NigbjLQprW = false;
      bool UILfhRDbPB = false;
      bool KuSsyyJUHu = false;
      bool LHHlxCWyic = false;
      bool tYVAFgXnRl = false;
      bool znYlMRQndk = false;
      bool BwixKMBYie = false;
      bool uFslGlZRmQ = false;
      bool aVDUwXhUYf = false;
      bool lhUxbypXpr = false;
      string XETXnrYgef;
      string irsJOdlfIo;
      string NpLWqDDkjO;
      string ndgDkQrESL;
      string QVxNSEKMgA;
      string MUHLtgsxgj;
      string nnwPrELpYy;
      string lhMwYqsxDl;
      string spDjCSWUID;
      string XuWiXcZhVN;
      string rUniOdHKmC;
      string nustqxjLMY;
      string hpgVZqKdYu;
      string RKaotYCTVX;
      string LLhGObBcrZ;
      string rNUxfCnRIW;
      string TdlqjcUDAS;
      string uQpoMVIZGy;
      string pglyDEpdJr;
      string jjKyEhYpVk;
      if(XETXnrYgef == rUniOdHKmC){HxcYebWejJ = true;}
      else if(rUniOdHKmC == XETXnrYgef){NigbjLQprW = true;}
      if(irsJOdlfIo == nustqxjLMY){sNLKglqnnf = true;}
      else if(nustqxjLMY == irsJOdlfIo){UILfhRDbPB = true;}
      if(NpLWqDDkjO == hpgVZqKdYu){mptIhKFrje = true;}
      else if(hpgVZqKdYu == NpLWqDDkjO){KuSsyyJUHu = true;}
      if(ndgDkQrESL == RKaotYCTVX){xSDVqrEMTb = true;}
      else if(RKaotYCTVX == ndgDkQrESL){LHHlxCWyic = true;}
      if(QVxNSEKMgA == LLhGObBcrZ){hKtzyWYAQR = true;}
      else if(LLhGObBcrZ == QVxNSEKMgA){tYVAFgXnRl = true;}
      if(MUHLtgsxgj == rNUxfCnRIW){pkCpyQCUqT = true;}
      else if(rNUxfCnRIW == MUHLtgsxgj){znYlMRQndk = true;}
      if(nnwPrELpYy == TdlqjcUDAS){WeuEMaJoSn = true;}
      else if(TdlqjcUDAS == nnwPrELpYy){BwixKMBYie = true;}
      if(lhMwYqsxDl == uQpoMVIZGy){heTLybwtJK = true;}
      if(spDjCSWUID == pglyDEpdJr){lEaSoLPNWZ = true;}
      if(XuWiXcZhVN == jjKyEhYpVk){piUzECPomX = true;}
      while(uQpoMVIZGy == lhMwYqsxDl){uFslGlZRmQ = true;}
      while(pglyDEpdJr == pglyDEpdJr){aVDUwXhUYf = true;}
      while(jjKyEhYpVk == jjKyEhYpVk){lhUxbypXpr = true;}
      if(HxcYebWejJ == true){HxcYebWejJ = false;}
      if(sNLKglqnnf == true){sNLKglqnnf = false;}
      if(mptIhKFrje == true){mptIhKFrje = false;}
      if(xSDVqrEMTb == true){xSDVqrEMTb = false;}
      if(hKtzyWYAQR == true){hKtzyWYAQR = false;}
      if(pkCpyQCUqT == true){pkCpyQCUqT = false;}
      if(WeuEMaJoSn == true){WeuEMaJoSn = false;}
      if(heTLybwtJK == true){heTLybwtJK = false;}
      if(lEaSoLPNWZ == true){lEaSoLPNWZ = false;}
      if(piUzECPomX == true){piUzECPomX = false;}
      if(NigbjLQprW == true){NigbjLQprW = false;}
      if(UILfhRDbPB == true){UILfhRDbPB = false;}
      if(KuSsyyJUHu == true){KuSsyyJUHu = false;}
      if(LHHlxCWyic == true){LHHlxCWyic = false;}
      if(tYVAFgXnRl == true){tYVAFgXnRl = false;}
      if(znYlMRQndk == true){znYlMRQndk = false;}
      if(BwixKMBYie == true){BwixKMBYie = false;}
      if(uFslGlZRmQ == true){uFslGlZRmQ = false;}
      if(aVDUwXhUYf == true){aVDUwXhUYf = false;}
      if(lhUxbypXpr == true){lhUxbypXpr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APXQTYBWCE
{ 
  void zdVTaTxoMc()
  { 
      bool NxROGuhfTV = false;
      bool OSpqFVwDQU = false;
      bool buCZiEYTMq = false;
      bool HrDKiMmzVT = false;
      bool esUMhuHlyn = false;
      bool rrUZARtqeC = false;
      bool WNSbOWPfHr = false;
      bool iwhwpiaorn = false;
      bool xmVXzPWcKQ = false;
      bool SuTTxRZsyK = false;
      bool fbdGFuKYjQ = false;
      bool qEzpEjrubz = false;
      bool zlUpZmbNyX = false;
      bool JhqgIVJORE = false;
      bool FxrsZNwdON = false;
      bool YeQyKsGmfR = false;
      bool SwaLHJNRhh = false;
      bool ZccXtCtbQM = false;
      bool qyykzeQrVP = false;
      bool PVizkIWfkP = false;
      string WsKNfwXcWt;
      string RzGtWJdLSX;
      string nHFzZbsAHL;
      string iopzVHnmtr;
      string pVVoixBUyd;
      string IAtcUOmKnE;
      string DWVKLbIGYO;
      string VqQahSlQQc;
      string ZYBcChuNeG;
      string UcypnSzKcG;
      string ntwiIRjSuB;
      string cWtKdeUsHd;
      string gubRtrrZlO;
      string TbmJnfbRTj;
      string xcRcdxhnMJ;
      string yGCzZrRdoP;
      string ZJffhBikVx;
      string CCYWfDdznx;
      string KENcPMYniw;
      string NxcEKnwkuc;
      if(WsKNfwXcWt == ntwiIRjSuB){NxROGuhfTV = true;}
      else if(ntwiIRjSuB == WsKNfwXcWt){fbdGFuKYjQ = true;}
      if(RzGtWJdLSX == cWtKdeUsHd){OSpqFVwDQU = true;}
      else if(cWtKdeUsHd == RzGtWJdLSX){qEzpEjrubz = true;}
      if(nHFzZbsAHL == gubRtrrZlO){buCZiEYTMq = true;}
      else if(gubRtrrZlO == nHFzZbsAHL){zlUpZmbNyX = true;}
      if(iopzVHnmtr == TbmJnfbRTj){HrDKiMmzVT = true;}
      else if(TbmJnfbRTj == iopzVHnmtr){JhqgIVJORE = true;}
      if(pVVoixBUyd == xcRcdxhnMJ){esUMhuHlyn = true;}
      else if(xcRcdxhnMJ == pVVoixBUyd){FxrsZNwdON = true;}
      if(IAtcUOmKnE == yGCzZrRdoP){rrUZARtqeC = true;}
      else if(yGCzZrRdoP == IAtcUOmKnE){YeQyKsGmfR = true;}
      if(DWVKLbIGYO == ZJffhBikVx){WNSbOWPfHr = true;}
      else if(ZJffhBikVx == DWVKLbIGYO){SwaLHJNRhh = true;}
      if(VqQahSlQQc == CCYWfDdznx){iwhwpiaorn = true;}
      if(ZYBcChuNeG == KENcPMYniw){xmVXzPWcKQ = true;}
      if(UcypnSzKcG == NxcEKnwkuc){SuTTxRZsyK = true;}
      while(CCYWfDdznx == VqQahSlQQc){ZccXtCtbQM = true;}
      while(KENcPMYniw == KENcPMYniw){qyykzeQrVP = true;}
      while(NxcEKnwkuc == NxcEKnwkuc){PVizkIWfkP = true;}
      if(NxROGuhfTV == true){NxROGuhfTV = false;}
      if(OSpqFVwDQU == true){OSpqFVwDQU = false;}
      if(buCZiEYTMq == true){buCZiEYTMq = false;}
      if(HrDKiMmzVT == true){HrDKiMmzVT = false;}
      if(esUMhuHlyn == true){esUMhuHlyn = false;}
      if(rrUZARtqeC == true){rrUZARtqeC = false;}
      if(WNSbOWPfHr == true){WNSbOWPfHr = false;}
      if(iwhwpiaorn == true){iwhwpiaorn = false;}
      if(xmVXzPWcKQ == true){xmVXzPWcKQ = false;}
      if(SuTTxRZsyK == true){SuTTxRZsyK = false;}
      if(fbdGFuKYjQ == true){fbdGFuKYjQ = false;}
      if(qEzpEjrubz == true){qEzpEjrubz = false;}
      if(zlUpZmbNyX == true){zlUpZmbNyX = false;}
      if(JhqgIVJORE == true){JhqgIVJORE = false;}
      if(FxrsZNwdON == true){FxrsZNwdON = false;}
      if(YeQyKsGmfR == true){YeQyKsGmfR = false;}
      if(SwaLHJNRhh == true){SwaLHJNRhh = false;}
      if(ZccXtCtbQM == true){ZccXtCtbQM = false;}
      if(qyykzeQrVP == true){qyykzeQrVP = false;}
      if(PVizkIWfkP == true){PVizkIWfkP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLGESOWVJQ
{ 
  void gCTiVrICWu()
  { 
      bool VyJuguSzFU = false;
      bool VktkDLMtQc = false;
      bool uTMbbeflbR = false;
      bool UREidDrfaW = false;
      bool NQMsbGCxBb = false;
      bool xOuOYBkgSC = false;
      bool OfWmzDgLGA = false;
      bool TfStPeHSAU = false;
      bool bhkAUGWoJc = false;
      bool RLMYHhsZtX = false;
      bool ZqqBIQuAzt = false;
      bool tSgyZftWSr = false;
      bool gqBchHTsmg = false;
      bool khYbujqjrD = false;
      bool KVpOiydOza = false;
      bool mWGBqhoOSA = false;
      bool xCNRJMtFCo = false;
      bool oKdPgKAmti = false;
      bool dEtLtOaWjM = false;
      bool ucQrFIHYFW = false;
      string PZqopyKzUS;
      string GYIWzpHKQK;
      string DObDmoFNJz;
      string LopGUtBKKW;
      string oBCQDLifzU;
      string wgLgDBynBA;
      string swpUGRiCBF;
      string nwAsUCLKzb;
      string GYNoCecIDT;
      string wNJJcrKgJl;
      string bfetfAfSLB;
      string omnZtUhARb;
      string nayhIalqQb;
      string qeAMzZsTJC;
      string zKwCeIYjPH;
      string KKOhyBhxkE;
      string OnCiJKmaZT;
      string aOqPccewCA;
      string BCbIRgPSOy;
      string rwhEnKIMrT;
      if(PZqopyKzUS == bfetfAfSLB){VyJuguSzFU = true;}
      else if(bfetfAfSLB == PZqopyKzUS){ZqqBIQuAzt = true;}
      if(GYIWzpHKQK == omnZtUhARb){VktkDLMtQc = true;}
      else if(omnZtUhARb == GYIWzpHKQK){tSgyZftWSr = true;}
      if(DObDmoFNJz == nayhIalqQb){uTMbbeflbR = true;}
      else if(nayhIalqQb == DObDmoFNJz){gqBchHTsmg = true;}
      if(LopGUtBKKW == qeAMzZsTJC){UREidDrfaW = true;}
      else if(qeAMzZsTJC == LopGUtBKKW){khYbujqjrD = true;}
      if(oBCQDLifzU == zKwCeIYjPH){NQMsbGCxBb = true;}
      else if(zKwCeIYjPH == oBCQDLifzU){KVpOiydOza = true;}
      if(wgLgDBynBA == KKOhyBhxkE){xOuOYBkgSC = true;}
      else if(KKOhyBhxkE == wgLgDBynBA){mWGBqhoOSA = true;}
      if(swpUGRiCBF == OnCiJKmaZT){OfWmzDgLGA = true;}
      else if(OnCiJKmaZT == swpUGRiCBF){xCNRJMtFCo = true;}
      if(nwAsUCLKzb == aOqPccewCA){TfStPeHSAU = true;}
      if(GYNoCecIDT == BCbIRgPSOy){bhkAUGWoJc = true;}
      if(wNJJcrKgJl == rwhEnKIMrT){RLMYHhsZtX = true;}
      while(aOqPccewCA == nwAsUCLKzb){oKdPgKAmti = true;}
      while(BCbIRgPSOy == BCbIRgPSOy){dEtLtOaWjM = true;}
      while(rwhEnKIMrT == rwhEnKIMrT){ucQrFIHYFW = true;}
      if(VyJuguSzFU == true){VyJuguSzFU = false;}
      if(VktkDLMtQc == true){VktkDLMtQc = false;}
      if(uTMbbeflbR == true){uTMbbeflbR = false;}
      if(UREidDrfaW == true){UREidDrfaW = false;}
      if(NQMsbGCxBb == true){NQMsbGCxBb = false;}
      if(xOuOYBkgSC == true){xOuOYBkgSC = false;}
      if(OfWmzDgLGA == true){OfWmzDgLGA = false;}
      if(TfStPeHSAU == true){TfStPeHSAU = false;}
      if(bhkAUGWoJc == true){bhkAUGWoJc = false;}
      if(RLMYHhsZtX == true){RLMYHhsZtX = false;}
      if(ZqqBIQuAzt == true){ZqqBIQuAzt = false;}
      if(tSgyZftWSr == true){tSgyZftWSr = false;}
      if(gqBchHTsmg == true){gqBchHTsmg = false;}
      if(khYbujqjrD == true){khYbujqjrD = false;}
      if(KVpOiydOza == true){KVpOiydOza = false;}
      if(mWGBqhoOSA == true){mWGBqhoOSA = false;}
      if(xCNRJMtFCo == true){xCNRJMtFCo = false;}
      if(oKdPgKAmti == true){oKdPgKAmti = false;}
      if(dEtLtOaWjM == true){dEtLtOaWjM = false;}
      if(ucQrFIHYFW == true){ucQrFIHYFW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPZIEMICYT
{ 
  void oIlXgVopbS()
  { 
      bool WVCXMGremF = false;
      bool GnWheyLbfg = false;
      bool EgVQEEVHZd = false;
      bool eMDalSKFiW = false;
      bool uGzTdZBqAX = false;
      bool QtNfIozkSH = false;
      bool kjEIZskuwM = false;
      bool nFsIlxhCle = false;
      bool DdHCNkyWSw = false;
      bool SYlalLCpsj = false;
      bool oFunjKBEtK = false;
      bool HwynEGcCuo = false;
      bool uNczsOSRWa = false;
      bool uqJCoyiSSD = false;
      bool isbIoVayWe = false;
      bool hzuDoacuuU = false;
      bool qjhTOPmwyF = false;
      bool WJjqGBkTJW = false;
      bool nUtqrwuGMO = false;
      bool VnXxLzLHtZ = false;
      string sKKBXrHWud;
      string CQfncOllkU;
      string ZRNtkKsnGG;
      string eAREkmLSpz;
      string ekwQHShGgd;
      string uEwceawQQN;
      string ySPoyByaDp;
      string CSulpoVxmR;
      string blHbKaEoZK;
      string puCbALUGRF;
      string UHDqbbIJmp;
      string FzcylLKneX;
      string xIBrzHQTkd;
      string UOfhwTiQAh;
      string RuCiEpRDpo;
      string AfbsIMFKqU;
      string LoXIVqTuBR;
      string ctnwGCGRnI;
      string oMcwcnllYj;
      string NXYfWbWsNM;
      if(sKKBXrHWud == UHDqbbIJmp){WVCXMGremF = true;}
      else if(UHDqbbIJmp == sKKBXrHWud){oFunjKBEtK = true;}
      if(CQfncOllkU == FzcylLKneX){GnWheyLbfg = true;}
      else if(FzcylLKneX == CQfncOllkU){HwynEGcCuo = true;}
      if(ZRNtkKsnGG == xIBrzHQTkd){EgVQEEVHZd = true;}
      else if(xIBrzHQTkd == ZRNtkKsnGG){uNczsOSRWa = true;}
      if(eAREkmLSpz == UOfhwTiQAh){eMDalSKFiW = true;}
      else if(UOfhwTiQAh == eAREkmLSpz){uqJCoyiSSD = true;}
      if(ekwQHShGgd == RuCiEpRDpo){uGzTdZBqAX = true;}
      else if(RuCiEpRDpo == ekwQHShGgd){isbIoVayWe = true;}
      if(uEwceawQQN == AfbsIMFKqU){QtNfIozkSH = true;}
      else if(AfbsIMFKqU == uEwceawQQN){hzuDoacuuU = true;}
      if(ySPoyByaDp == LoXIVqTuBR){kjEIZskuwM = true;}
      else if(LoXIVqTuBR == ySPoyByaDp){qjhTOPmwyF = true;}
      if(CSulpoVxmR == ctnwGCGRnI){nFsIlxhCle = true;}
      if(blHbKaEoZK == oMcwcnllYj){DdHCNkyWSw = true;}
      if(puCbALUGRF == NXYfWbWsNM){SYlalLCpsj = true;}
      while(ctnwGCGRnI == CSulpoVxmR){WJjqGBkTJW = true;}
      while(oMcwcnllYj == oMcwcnllYj){nUtqrwuGMO = true;}
      while(NXYfWbWsNM == NXYfWbWsNM){VnXxLzLHtZ = true;}
      if(WVCXMGremF == true){WVCXMGremF = false;}
      if(GnWheyLbfg == true){GnWheyLbfg = false;}
      if(EgVQEEVHZd == true){EgVQEEVHZd = false;}
      if(eMDalSKFiW == true){eMDalSKFiW = false;}
      if(uGzTdZBqAX == true){uGzTdZBqAX = false;}
      if(QtNfIozkSH == true){QtNfIozkSH = false;}
      if(kjEIZskuwM == true){kjEIZskuwM = false;}
      if(nFsIlxhCle == true){nFsIlxhCle = false;}
      if(DdHCNkyWSw == true){DdHCNkyWSw = false;}
      if(SYlalLCpsj == true){SYlalLCpsj = false;}
      if(oFunjKBEtK == true){oFunjKBEtK = false;}
      if(HwynEGcCuo == true){HwynEGcCuo = false;}
      if(uNczsOSRWa == true){uNczsOSRWa = false;}
      if(uqJCoyiSSD == true){uqJCoyiSSD = false;}
      if(isbIoVayWe == true){isbIoVayWe = false;}
      if(hzuDoacuuU == true){hzuDoacuuU = false;}
      if(qjhTOPmwyF == true){qjhTOPmwyF = false;}
      if(WJjqGBkTJW == true){WJjqGBkTJW = false;}
      if(nUtqrwuGMO == true){nUtqrwuGMO = false;}
      if(VnXxLzLHtZ == true){VnXxLzLHtZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXQYALIQFT
{ 
  void lrzfVsYVsM()
  { 
      bool GkoTIMMQFd = false;
      bool IZsVQBVEPq = false;
      bool awTlURaatA = false;
      bool jnjnGtyPNu = false;
      bool CNdHfWMtRq = false;
      bool JPEowKRDyp = false;
      bool kkWFsUoEOW = false;
      bool DFpTnNSMFy = false;
      bool FfICqTitrw = false;
      bool cuRWKQpXOL = false;
      bool hHeunEZkAi = false;
      bool qExAkFcTOY = false;
      bool ktMSsHmSJX = false;
      bool WtxtQxAMOl = false;
      bool txtIEXxQkE = false;
      bool nWJoZmuMCf = false;
      bool QGacMwGCjn = false;
      bool EQEbdnADNV = false;
      bool JWgEizkIUc = false;
      bool BnKiVnWQwH = false;
      string mXrZzCgCXi;
      string ozEeukAuSc;
      string ElBMVKMFKX;
      string EQUVUIwAfC;
      string VFafIxcGVJ;
      string tqrqqBWeEn;
      string oarzdYehKl;
      string oAOPGzKVEX;
      string hGjAcNXceT;
      string lRwrNuNaBj;
      string StuiTtbcjq;
      string pAZfFhqqWQ;
      string ABDpAWEWBL;
      string kjUUFmKAgi;
      string kusmdlqPle;
      string DWEkiQpFix;
      string pFaXGGfFaS;
      string WqKmeFIQMN;
      string fnjVIOeikn;
      string xFQiseUUgX;
      if(mXrZzCgCXi == StuiTtbcjq){GkoTIMMQFd = true;}
      else if(StuiTtbcjq == mXrZzCgCXi){hHeunEZkAi = true;}
      if(ozEeukAuSc == pAZfFhqqWQ){IZsVQBVEPq = true;}
      else if(pAZfFhqqWQ == ozEeukAuSc){qExAkFcTOY = true;}
      if(ElBMVKMFKX == ABDpAWEWBL){awTlURaatA = true;}
      else if(ABDpAWEWBL == ElBMVKMFKX){ktMSsHmSJX = true;}
      if(EQUVUIwAfC == kjUUFmKAgi){jnjnGtyPNu = true;}
      else if(kjUUFmKAgi == EQUVUIwAfC){WtxtQxAMOl = true;}
      if(VFafIxcGVJ == kusmdlqPle){CNdHfWMtRq = true;}
      else if(kusmdlqPle == VFafIxcGVJ){txtIEXxQkE = true;}
      if(tqrqqBWeEn == DWEkiQpFix){JPEowKRDyp = true;}
      else if(DWEkiQpFix == tqrqqBWeEn){nWJoZmuMCf = true;}
      if(oarzdYehKl == pFaXGGfFaS){kkWFsUoEOW = true;}
      else if(pFaXGGfFaS == oarzdYehKl){QGacMwGCjn = true;}
      if(oAOPGzKVEX == WqKmeFIQMN){DFpTnNSMFy = true;}
      if(hGjAcNXceT == fnjVIOeikn){FfICqTitrw = true;}
      if(lRwrNuNaBj == xFQiseUUgX){cuRWKQpXOL = true;}
      while(WqKmeFIQMN == oAOPGzKVEX){EQEbdnADNV = true;}
      while(fnjVIOeikn == fnjVIOeikn){JWgEizkIUc = true;}
      while(xFQiseUUgX == xFQiseUUgX){BnKiVnWQwH = true;}
      if(GkoTIMMQFd == true){GkoTIMMQFd = false;}
      if(IZsVQBVEPq == true){IZsVQBVEPq = false;}
      if(awTlURaatA == true){awTlURaatA = false;}
      if(jnjnGtyPNu == true){jnjnGtyPNu = false;}
      if(CNdHfWMtRq == true){CNdHfWMtRq = false;}
      if(JPEowKRDyp == true){JPEowKRDyp = false;}
      if(kkWFsUoEOW == true){kkWFsUoEOW = false;}
      if(DFpTnNSMFy == true){DFpTnNSMFy = false;}
      if(FfICqTitrw == true){FfICqTitrw = false;}
      if(cuRWKQpXOL == true){cuRWKQpXOL = false;}
      if(hHeunEZkAi == true){hHeunEZkAi = false;}
      if(qExAkFcTOY == true){qExAkFcTOY = false;}
      if(ktMSsHmSJX == true){ktMSsHmSJX = false;}
      if(WtxtQxAMOl == true){WtxtQxAMOl = false;}
      if(txtIEXxQkE == true){txtIEXxQkE = false;}
      if(nWJoZmuMCf == true){nWJoZmuMCf = false;}
      if(QGacMwGCjn == true){QGacMwGCjn = false;}
      if(EQEbdnADNV == true){EQEbdnADNV = false;}
      if(JWgEizkIUc == true){JWgEizkIUc = false;}
      if(BnKiVnWQwH == true){BnKiVnWQwH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFGXNWFBEX
{ 
  void AeLejODVDR()
  { 
      bool lwjFFsNNdQ = false;
      bool zQcgSIHJYS = false;
      bool oscUitOMLy = false;
      bool cgjLWtMbFZ = false;
      bool QXyuwVtEHV = false;
      bool tpyIPsTPVL = false;
      bool dACfmRfRKX = false;
      bool ueDzBQtgYN = false;
      bool AKEoDmibud = false;
      bool axGtuPVRId = false;
      bool ocsjZOlzGz = false;
      bool ylpILSwMbz = false;
      bool iEWfxyYJDk = false;
      bool ubXtXXQUPo = false;
      bool BiUwfoGxic = false;
      bool TIpIujFMlb = false;
      bool ocwUDVNwjm = false;
      bool BaxmyzjaAH = false;
      bool qaZZRllPzm = false;
      bool REhnzXmArJ = false;
      string GeOKhzGUbn;
      string ImblukQqDO;
      string gSZUaXCuVK;
      string JfCnnqaBVH;
      string gZwzVFypLx;
      string UTCkknEtjJ;
      string xLyQecjmxE;
      string JPVuhHVayU;
      string ZLiYpocRDz;
      string lgQLKVaeTs;
      string VLsHmFyHDd;
      string SduPjkbZap;
      string zSjyRcyJkL;
      string fpHFyNSakk;
      string pVOYgIkBbY;
      string sBEdsDatpK;
      string GoVqxbWoQV;
      string SAnpzcEKQI;
      string qxhLSelcMu;
      string lXkaeBzWaF;
      if(GeOKhzGUbn == VLsHmFyHDd){lwjFFsNNdQ = true;}
      else if(VLsHmFyHDd == GeOKhzGUbn){ocsjZOlzGz = true;}
      if(ImblukQqDO == SduPjkbZap){zQcgSIHJYS = true;}
      else if(SduPjkbZap == ImblukQqDO){ylpILSwMbz = true;}
      if(gSZUaXCuVK == zSjyRcyJkL){oscUitOMLy = true;}
      else if(zSjyRcyJkL == gSZUaXCuVK){iEWfxyYJDk = true;}
      if(JfCnnqaBVH == fpHFyNSakk){cgjLWtMbFZ = true;}
      else if(fpHFyNSakk == JfCnnqaBVH){ubXtXXQUPo = true;}
      if(gZwzVFypLx == pVOYgIkBbY){QXyuwVtEHV = true;}
      else if(pVOYgIkBbY == gZwzVFypLx){BiUwfoGxic = true;}
      if(UTCkknEtjJ == sBEdsDatpK){tpyIPsTPVL = true;}
      else if(sBEdsDatpK == UTCkknEtjJ){TIpIujFMlb = true;}
      if(xLyQecjmxE == GoVqxbWoQV){dACfmRfRKX = true;}
      else if(GoVqxbWoQV == xLyQecjmxE){ocwUDVNwjm = true;}
      if(JPVuhHVayU == SAnpzcEKQI){ueDzBQtgYN = true;}
      if(ZLiYpocRDz == qxhLSelcMu){AKEoDmibud = true;}
      if(lgQLKVaeTs == lXkaeBzWaF){axGtuPVRId = true;}
      while(SAnpzcEKQI == JPVuhHVayU){BaxmyzjaAH = true;}
      while(qxhLSelcMu == qxhLSelcMu){qaZZRllPzm = true;}
      while(lXkaeBzWaF == lXkaeBzWaF){REhnzXmArJ = true;}
      if(lwjFFsNNdQ == true){lwjFFsNNdQ = false;}
      if(zQcgSIHJYS == true){zQcgSIHJYS = false;}
      if(oscUitOMLy == true){oscUitOMLy = false;}
      if(cgjLWtMbFZ == true){cgjLWtMbFZ = false;}
      if(QXyuwVtEHV == true){QXyuwVtEHV = false;}
      if(tpyIPsTPVL == true){tpyIPsTPVL = false;}
      if(dACfmRfRKX == true){dACfmRfRKX = false;}
      if(ueDzBQtgYN == true){ueDzBQtgYN = false;}
      if(AKEoDmibud == true){AKEoDmibud = false;}
      if(axGtuPVRId == true){axGtuPVRId = false;}
      if(ocsjZOlzGz == true){ocsjZOlzGz = false;}
      if(ylpILSwMbz == true){ylpILSwMbz = false;}
      if(iEWfxyYJDk == true){iEWfxyYJDk = false;}
      if(ubXtXXQUPo == true){ubXtXXQUPo = false;}
      if(BiUwfoGxic == true){BiUwfoGxic = false;}
      if(TIpIujFMlb == true){TIpIujFMlb = false;}
      if(ocwUDVNwjm == true){ocwUDVNwjm = false;}
      if(BaxmyzjaAH == true){BaxmyzjaAH = false;}
      if(qaZZRllPzm == true){qaZZRllPzm = false;}
      if(REhnzXmArJ == true){REhnzXmArJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGWTOFNNET
{ 
  void NMpwOEDOai()
  { 
      bool uBHtUIsrxh = false;
      bool UwZGfgRpOy = false;
      bool LOwSShIiPW = false;
      bool EqSrINcFaJ = false;
      bool UZfEUqbBmD = false;
      bool BKttUfFoal = false;
      bool zJcacccgyR = false;
      bool ELOFdliqyb = false;
      bool GGwLVtxYWb = false;
      bool IndnJKwFaq = false;
      bool NtDUyouoQi = false;
      bool wNpzfrNRFi = false;
      bool fEKVJQhZwS = false;
      bool ocPGNLDaNf = false;
      bool yIImetxeHR = false;
      bool weArLJjgLh = false;
      bool HUrxsTxikU = false;
      bool nlDYjXwWpO = false;
      bool SCRdVKcXuE = false;
      bool aWPeYcPKsL = false;
      string cOasuWTQFr;
      string fyBihFTPET;
      string xeWJxdCNud;
      string PKpMyqLgQK;
      string RfWpCWMTrn;
      string GOiamxqRuR;
      string TGVabUHokp;
      string smysCRHgHa;
      string RiUHXAbPYA;
      string ztkzqKJwOg;
      string OWhBtTQoYU;
      string oKJUzkkODa;
      string srPjqzBzCq;
      string ILRaLtASMD;
      string jmqEKnjQzF;
      string ZtsnnWHyKt;
      string SQlgLdsiIF;
      string jRBApFBLYD;
      string OkzwRNSdmo;
      string mBISkSAJrg;
      if(cOasuWTQFr == OWhBtTQoYU){uBHtUIsrxh = true;}
      else if(OWhBtTQoYU == cOasuWTQFr){NtDUyouoQi = true;}
      if(fyBihFTPET == oKJUzkkODa){UwZGfgRpOy = true;}
      else if(oKJUzkkODa == fyBihFTPET){wNpzfrNRFi = true;}
      if(xeWJxdCNud == srPjqzBzCq){LOwSShIiPW = true;}
      else if(srPjqzBzCq == xeWJxdCNud){fEKVJQhZwS = true;}
      if(PKpMyqLgQK == ILRaLtASMD){EqSrINcFaJ = true;}
      else if(ILRaLtASMD == PKpMyqLgQK){ocPGNLDaNf = true;}
      if(RfWpCWMTrn == jmqEKnjQzF){UZfEUqbBmD = true;}
      else if(jmqEKnjQzF == RfWpCWMTrn){yIImetxeHR = true;}
      if(GOiamxqRuR == ZtsnnWHyKt){BKttUfFoal = true;}
      else if(ZtsnnWHyKt == GOiamxqRuR){weArLJjgLh = true;}
      if(TGVabUHokp == SQlgLdsiIF){zJcacccgyR = true;}
      else if(SQlgLdsiIF == TGVabUHokp){HUrxsTxikU = true;}
      if(smysCRHgHa == jRBApFBLYD){ELOFdliqyb = true;}
      if(RiUHXAbPYA == OkzwRNSdmo){GGwLVtxYWb = true;}
      if(ztkzqKJwOg == mBISkSAJrg){IndnJKwFaq = true;}
      while(jRBApFBLYD == smysCRHgHa){nlDYjXwWpO = true;}
      while(OkzwRNSdmo == OkzwRNSdmo){SCRdVKcXuE = true;}
      while(mBISkSAJrg == mBISkSAJrg){aWPeYcPKsL = true;}
      if(uBHtUIsrxh == true){uBHtUIsrxh = false;}
      if(UwZGfgRpOy == true){UwZGfgRpOy = false;}
      if(LOwSShIiPW == true){LOwSShIiPW = false;}
      if(EqSrINcFaJ == true){EqSrINcFaJ = false;}
      if(UZfEUqbBmD == true){UZfEUqbBmD = false;}
      if(BKttUfFoal == true){BKttUfFoal = false;}
      if(zJcacccgyR == true){zJcacccgyR = false;}
      if(ELOFdliqyb == true){ELOFdliqyb = false;}
      if(GGwLVtxYWb == true){GGwLVtxYWb = false;}
      if(IndnJKwFaq == true){IndnJKwFaq = false;}
      if(NtDUyouoQi == true){NtDUyouoQi = false;}
      if(wNpzfrNRFi == true){wNpzfrNRFi = false;}
      if(fEKVJQhZwS == true){fEKVJQhZwS = false;}
      if(ocPGNLDaNf == true){ocPGNLDaNf = false;}
      if(yIImetxeHR == true){yIImetxeHR = false;}
      if(weArLJjgLh == true){weArLJjgLh = false;}
      if(HUrxsTxikU == true){HUrxsTxikU = false;}
      if(nlDYjXwWpO == true){nlDYjXwWpO = false;}
      if(SCRdVKcXuE == true){SCRdVKcXuE = false;}
      if(aWPeYcPKsL == true){aWPeYcPKsL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDFTFLOEWT
{ 
  void aNuDNOtrux()
  { 
      bool sQGcxiMzJE = false;
      bool UUplOaOTaz = false;
      bool aRoPUrJHHB = false;
      bool GlRLbPYVYq = false;
      bool GJFefmUlxg = false;
      bool eCwLRaaqHF = false;
      bool YErIxiDeJy = false;
      bool CstjrRMKjg = false;
      bool XXJZVEoFsA = false;
      bool ngNTRBQxgw = false;
      bool jobzdlHLTz = false;
      bool OQHagBtRlr = false;
      bool sxkJJVeZRp = false;
      bool BPdmxhwKuj = false;
      bool xcktlXZmlQ = false;
      bool HzKnCmESoI = false;
      bool GhtdyzmTcz = false;
      bool FjVBuQLqWl = false;
      bool uqmBiBEokK = false;
      bool ccUldPiHum = false;
      string ortpHkztDM;
      string gccgbIZVrq;
      string RPOSDQmGsB;
      string iUcYLFGFdJ;
      string WIxlgLHAYT;
      string cJwMbZdamq;
      string xsACdMzDUW;
      string CUqiTIRckq;
      string ImgYXZYQxk;
      string aeRmLcHtIU;
      string MDeCRIRMrT;
      string HBouhKMaeD;
      string nhGiuWCDWq;
      string AXTQeFHeHO;
      string HLYddZpWFA;
      string QgPEgdxwGu;
      string GNpBSjgYPc;
      string DhTPubJcFU;
      string geyWZTIOiA;
      string HLXLItVXKs;
      if(ortpHkztDM == MDeCRIRMrT){sQGcxiMzJE = true;}
      else if(MDeCRIRMrT == ortpHkztDM){jobzdlHLTz = true;}
      if(gccgbIZVrq == HBouhKMaeD){UUplOaOTaz = true;}
      else if(HBouhKMaeD == gccgbIZVrq){OQHagBtRlr = true;}
      if(RPOSDQmGsB == nhGiuWCDWq){aRoPUrJHHB = true;}
      else if(nhGiuWCDWq == RPOSDQmGsB){sxkJJVeZRp = true;}
      if(iUcYLFGFdJ == AXTQeFHeHO){GlRLbPYVYq = true;}
      else if(AXTQeFHeHO == iUcYLFGFdJ){BPdmxhwKuj = true;}
      if(WIxlgLHAYT == HLYddZpWFA){GJFefmUlxg = true;}
      else if(HLYddZpWFA == WIxlgLHAYT){xcktlXZmlQ = true;}
      if(cJwMbZdamq == QgPEgdxwGu){eCwLRaaqHF = true;}
      else if(QgPEgdxwGu == cJwMbZdamq){HzKnCmESoI = true;}
      if(xsACdMzDUW == GNpBSjgYPc){YErIxiDeJy = true;}
      else if(GNpBSjgYPc == xsACdMzDUW){GhtdyzmTcz = true;}
      if(CUqiTIRckq == DhTPubJcFU){CstjrRMKjg = true;}
      if(ImgYXZYQxk == geyWZTIOiA){XXJZVEoFsA = true;}
      if(aeRmLcHtIU == HLXLItVXKs){ngNTRBQxgw = true;}
      while(DhTPubJcFU == CUqiTIRckq){FjVBuQLqWl = true;}
      while(geyWZTIOiA == geyWZTIOiA){uqmBiBEokK = true;}
      while(HLXLItVXKs == HLXLItVXKs){ccUldPiHum = true;}
      if(sQGcxiMzJE == true){sQGcxiMzJE = false;}
      if(UUplOaOTaz == true){UUplOaOTaz = false;}
      if(aRoPUrJHHB == true){aRoPUrJHHB = false;}
      if(GlRLbPYVYq == true){GlRLbPYVYq = false;}
      if(GJFefmUlxg == true){GJFefmUlxg = false;}
      if(eCwLRaaqHF == true){eCwLRaaqHF = false;}
      if(YErIxiDeJy == true){YErIxiDeJy = false;}
      if(CstjrRMKjg == true){CstjrRMKjg = false;}
      if(XXJZVEoFsA == true){XXJZVEoFsA = false;}
      if(ngNTRBQxgw == true){ngNTRBQxgw = false;}
      if(jobzdlHLTz == true){jobzdlHLTz = false;}
      if(OQHagBtRlr == true){OQHagBtRlr = false;}
      if(sxkJJVeZRp == true){sxkJJVeZRp = false;}
      if(BPdmxhwKuj == true){BPdmxhwKuj = false;}
      if(xcktlXZmlQ == true){xcktlXZmlQ = false;}
      if(HzKnCmESoI == true){HzKnCmESoI = false;}
      if(GhtdyzmTcz == true){GhtdyzmTcz = false;}
      if(FjVBuQLqWl == true){FjVBuQLqWl = false;}
      if(uqmBiBEokK == true){uqmBiBEokK = false;}
      if(ccUldPiHum == true){ccUldPiHum = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKSFHOFQBZ
{ 
  void MeXGzagpUj()
  { 
      bool cZKHDGHZio = false;
      bool CLPEXeLfzO = false;
      bool iGBUFaumVi = false;
      bool pIeNyiiGNm = false;
      bool OJYUYdaugy = false;
      bool ABICaVXpBb = false;
      bool LUDzzsgCFn = false;
      bool uFRMAZhgub = false;
      bool AzFWinAblb = false;
      bool KsFlbtFZVf = false;
      bool wYosDuiwCA = false;
      bool mqtZbLOgPK = false;
      bool rEPccBAfkG = false;
      bool THLPebKMSm = false;
      bool EEZlnTzeJP = false;
      bool eXJKmrILPC = false;
      bool uDKuffeetA = false;
      bool BCNbGnednI = false;
      bool CUVUawyBbm = false;
      bool SywQrBsdFI = false;
      string yZmHMJlBio;
      string JNWODHbBVB;
      string YoYQfQBjHE;
      string dtDPMsqapV;
      string dXFYexMmHs;
      string bBgMHJBVaw;
      string HCseLOJGBK;
      string QBKzXAizli;
      string DNbOccMqIC;
      string rUztNbeaNP;
      string mGkxbaphoG;
      string aBirrsZeBi;
      string CSyzRuBPku;
      string VIlWuxcelC;
      string leBBbqlHCT;
      string BAYeMTHleg;
      string YZwsjROLwu;
      string QurzwXRwWa;
      string JtNQsViHJb;
      string opzFcMhIQJ;
      if(yZmHMJlBio == mGkxbaphoG){cZKHDGHZio = true;}
      else if(mGkxbaphoG == yZmHMJlBio){wYosDuiwCA = true;}
      if(JNWODHbBVB == aBirrsZeBi){CLPEXeLfzO = true;}
      else if(aBirrsZeBi == JNWODHbBVB){mqtZbLOgPK = true;}
      if(YoYQfQBjHE == CSyzRuBPku){iGBUFaumVi = true;}
      else if(CSyzRuBPku == YoYQfQBjHE){rEPccBAfkG = true;}
      if(dtDPMsqapV == VIlWuxcelC){pIeNyiiGNm = true;}
      else if(VIlWuxcelC == dtDPMsqapV){THLPebKMSm = true;}
      if(dXFYexMmHs == leBBbqlHCT){OJYUYdaugy = true;}
      else if(leBBbqlHCT == dXFYexMmHs){EEZlnTzeJP = true;}
      if(bBgMHJBVaw == BAYeMTHleg){ABICaVXpBb = true;}
      else if(BAYeMTHleg == bBgMHJBVaw){eXJKmrILPC = true;}
      if(HCseLOJGBK == YZwsjROLwu){LUDzzsgCFn = true;}
      else if(YZwsjROLwu == HCseLOJGBK){uDKuffeetA = true;}
      if(QBKzXAizli == QurzwXRwWa){uFRMAZhgub = true;}
      if(DNbOccMqIC == JtNQsViHJb){AzFWinAblb = true;}
      if(rUztNbeaNP == opzFcMhIQJ){KsFlbtFZVf = true;}
      while(QurzwXRwWa == QBKzXAizli){BCNbGnednI = true;}
      while(JtNQsViHJb == JtNQsViHJb){CUVUawyBbm = true;}
      while(opzFcMhIQJ == opzFcMhIQJ){SywQrBsdFI = true;}
      if(cZKHDGHZio == true){cZKHDGHZio = false;}
      if(CLPEXeLfzO == true){CLPEXeLfzO = false;}
      if(iGBUFaumVi == true){iGBUFaumVi = false;}
      if(pIeNyiiGNm == true){pIeNyiiGNm = false;}
      if(OJYUYdaugy == true){OJYUYdaugy = false;}
      if(ABICaVXpBb == true){ABICaVXpBb = false;}
      if(LUDzzsgCFn == true){LUDzzsgCFn = false;}
      if(uFRMAZhgub == true){uFRMAZhgub = false;}
      if(AzFWinAblb == true){AzFWinAblb = false;}
      if(KsFlbtFZVf == true){KsFlbtFZVf = false;}
      if(wYosDuiwCA == true){wYosDuiwCA = false;}
      if(mqtZbLOgPK == true){mqtZbLOgPK = false;}
      if(rEPccBAfkG == true){rEPccBAfkG = false;}
      if(THLPebKMSm == true){THLPebKMSm = false;}
      if(EEZlnTzeJP == true){EEZlnTzeJP = false;}
      if(eXJKmrILPC == true){eXJKmrILPC = false;}
      if(uDKuffeetA == true){uDKuffeetA = false;}
      if(BCNbGnednI == true){BCNbGnednI = false;}
      if(CUVUawyBbm == true){CUVUawyBbm = false;}
      if(SywQrBsdFI == true){SywQrBsdFI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NENXQMHYFL
{ 
  void CKPEmrrbVK()
  { 
      bool huwjYnCViT = false;
      bool EHwZaVnuhH = false;
      bool rrDlaMSeAZ = false;
      bool npcIfdBNtf = false;
      bool FWyqjqxVMe = false;
      bool foXjSpqJJL = false;
      bool UWVJeOdmsw = false;
      bool UZABCVtLCj = false;
      bool PwRVszRspp = false;
      bool lqEiKhBnMV = false;
      bool MKcQJFnWhx = false;
      bool ufHZwYFzPf = false;
      bool wkwDJcVRpU = false;
      bool TFzgWETBLm = false;
      bool KuLstGjdml = false;
      bool cBYfYbNYHg = false;
      bool jWfMcpfZCq = false;
      bool EDmbUBYDJC = false;
      bool sqdDqRfSIt = false;
      bool puteDnOyPD = false;
      string qEPttrTxgV;
      string KTWYhfEGAY;
      string HfcZkNkXTD;
      string PXgtKSSwoE;
      string zEVlEqgtax;
      string uMKzuLaoJf;
      string HwccGllbOO;
      string MHQwZDJqVt;
      string fpwWHDNhzy;
      string rcmIxCasfR;
      string EFfLjnuNZr;
      string CjSPzQzFUC;
      string YEcPWiUHzW;
      string bQKEoaJkmT;
      string HzIHwHJWJf;
      string CUXdsAcPoA;
      string TmOCPkYOaY;
      string HOSBtYwUTO;
      string ZxyTUHsgLn;
      string ytwmAUjFrK;
      if(qEPttrTxgV == EFfLjnuNZr){huwjYnCViT = true;}
      else if(EFfLjnuNZr == qEPttrTxgV){MKcQJFnWhx = true;}
      if(KTWYhfEGAY == CjSPzQzFUC){EHwZaVnuhH = true;}
      else if(CjSPzQzFUC == KTWYhfEGAY){ufHZwYFzPf = true;}
      if(HfcZkNkXTD == YEcPWiUHzW){rrDlaMSeAZ = true;}
      else if(YEcPWiUHzW == HfcZkNkXTD){wkwDJcVRpU = true;}
      if(PXgtKSSwoE == bQKEoaJkmT){npcIfdBNtf = true;}
      else if(bQKEoaJkmT == PXgtKSSwoE){TFzgWETBLm = true;}
      if(zEVlEqgtax == HzIHwHJWJf){FWyqjqxVMe = true;}
      else if(HzIHwHJWJf == zEVlEqgtax){KuLstGjdml = true;}
      if(uMKzuLaoJf == CUXdsAcPoA){foXjSpqJJL = true;}
      else if(CUXdsAcPoA == uMKzuLaoJf){cBYfYbNYHg = true;}
      if(HwccGllbOO == TmOCPkYOaY){UWVJeOdmsw = true;}
      else if(TmOCPkYOaY == HwccGllbOO){jWfMcpfZCq = true;}
      if(MHQwZDJqVt == HOSBtYwUTO){UZABCVtLCj = true;}
      if(fpwWHDNhzy == ZxyTUHsgLn){PwRVszRspp = true;}
      if(rcmIxCasfR == ytwmAUjFrK){lqEiKhBnMV = true;}
      while(HOSBtYwUTO == MHQwZDJqVt){EDmbUBYDJC = true;}
      while(ZxyTUHsgLn == ZxyTUHsgLn){sqdDqRfSIt = true;}
      while(ytwmAUjFrK == ytwmAUjFrK){puteDnOyPD = true;}
      if(huwjYnCViT == true){huwjYnCViT = false;}
      if(EHwZaVnuhH == true){EHwZaVnuhH = false;}
      if(rrDlaMSeAZ == true){rrDlaMSeAZ = false;}
      if(npcIfdBNtf == true){npcIfdBNtf = false;}
      if(FWyqjqxVMe == true){FWyqjqxVMe = false;}
      if(foXjSpqJJL == true){foXjSpqJJL = false;}
      if(UWVJeOdmsw == true){UWVJeOdmsw = false;}
      if(UZABCVtLCj == true){UZABCVtLCj = false;}
      if(PwRVszRspp == true){PwRVszRspp = false;}
      if(lqEiKhBnMV == true){lqEiKhBnMV = false;}
      if(MKcQJFnWhx == true){MKcQJFnWhx = false;}
      if(ufHZwYFzPf == true){ufHZwYFzPf = false;}
      if(wkwDJcVRpU == true){wkwDJcVRpU = false;}
      if(TFzgWETBLm == true){TFzgWETBLm = false;}
      if(KuLstGjdml == true){KuLstGjdml = false;}
      if(cBYfYbNYHg == true){cBYfYbNYHg = false;}
      if(jWfMcpfZCq == true){jWfMcpfZCq = false;}
      if(EDmbUBYDJC == true){EDmbUBYDJC = false;}
      if(sqdDqRfSIt == true){sqdDqRfSIt = false;}
      if(puteDnOyPD == true){puteDnOyPD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKLMQASTLG
{ 
  void ZzeUbYhJDn()
  { 
      bool CtXXkqLpSX = false;
      bool aTtgzQXOZP = false;
      bool yudxqDySgP = false;
      bool EkcMfhpORr = false;
      bool bujuUDjHFA = false;
      bool ygHsTHQZgg = false;
      bool rrJDSoqhAR = false;
      bool ZJxhmDKhcn = false;
      bool SpNfRWdirY = false;
      bool QQhjAikgbe = false;
      bool MCHmZnjZFP = false;
      bool whwsOBdcku = false;
      bool LHobAJbMgD = false;
      bool SdFxaQiaGc = false;
      bool mEcbciTnVy = false;
      bool FIufTEMelQ = false;
      bool MXrBxRbyRx = false;
      bool RDWHIHeNzR = false;
      bool omphyJhYdW = false;
      bool DEnoQOLadK = false;
      string WgDHyNxIHo;
      string fATewCOCdD;
      string kBqibZPAZC;
      string DPZeiABgAC;
      string SXpJDfsDwx;
      string slNJpVpUeX;
      string xwhEkPanuu;
      string AgCakNLgeu;
      string gLEcIRBPoN;
      string KgBcEWokYm;
      string FEHAwLjmXb;
      string KIojplrFwT;
      string OKzhkTfYVO;
      string XZIrpcDEgx;
      string gNrMDCqRlS;
      string ejoFYtFYPb;
      string fKRJDjzxsN;
      string hmXylASlei;
      string bOmCinkDSw;
      string WeoERVwhJS;
      if(WgDHyNxIHo == FEHAwLjmXb){CtXXkqLpSX = true;}
      else if(FEHAwLjmXb == WgDHyNxIHo){MCHmZnjZFP = true;}
      if(fATewCOCdD == KIojplrFwT){aTtgzQXOZP = true;}
      else if(KIojplrFwT == fATewCOCdD){whwsOBdcku = true;}
      if(kBqibZPAZC == OKzhkTfYVO){yudxqDySgP = true;}
      else if(OKzhkTfYVO == kBqibZPAZC){LHobAJbMgD = true;}
      if(DPZeiABgAC == XZIrpcDEgx){EkcMfhpORr = true;}
      else if(XZIrpcDEgx == DPZeiABgAC){SdFxaQiaGc = true;}
      if(SXpJDfsDwx == gNrMDCqRlS){bujuUDjHFA = true;}
      else if(gNrMDCqRlS == SXpJDfsDwx){mEcbciTnVy = true;}
      if(slNJpVpUeX == ejoFYtFYPb){ygHsTHQZgg = true;}
      else if(ejoFYtFYPb == slNJpVpUeX){FIufTEMelQ = true;}
      if(xwhEkPanuu == fKRJDjzxsN){rrJDSoqhAR = true;}
      else if(fKRJDjzxsN == xwhEkPanuu){MXrBxRbyRx = true;}
      if(AgCakNLgeu == hmXylASlei){ZJxhmDKhcn = true;}
      if(gLEcIRBPoN == bOmCinkDSw){SpNfRWdirY = true;}
      if(KgBcEWokYm == WeoERVwhJS){QQhjAikgbe = true;}
      while(hmXylASlei == AgCakNLgeu){RDWHIHeNzR = true;}
      while(bOmCinkDSw == bOmCinkDSw){omphyJhYdW = true;}
      while(WeoERVwhJS == WeoERVwhJS){DEnoQOLadK = true;}
      if(CtXXkqLpSX == true){CtXXkqLpSX = false;}
      if(aTtgzQXOZP == true){aTtgzQXOZP = false;}
      if(yudxqDySgP == true){yudxqDySgP = false;}
      if(EkcMfhpORr == true){EkcMfhpORr = false;}
      if(bujuUDjHFA == true){bujuUDjHFA = false;}
      if(ygHsTHQZgg == true){ygHsTHQZgg = false;}
      if(rrJDSoqhAR == true){rrJDSoqhAR = false;}
      if(ZJxhmDKhcn == true){ZJxhmDKhcn = false;}
      if(SpNfRWdirY == true){SpNfRWdirY = false;}
      if(QQhjAikgbe == true){QQhjAikgbe = false;}
      if(MCHmZnjZFP == true){MCHmZnjZFP = false;}
      if(whwsOBdcku == true){whwsOBdcku = false;}
      if(LHobAJbMgD == true){LHobAJbMgD = false;}
      if(SdFxaQiaGc == true){SdFxaQiaGc = false;}
      if(mEcbciTnVy == true){mEcbciTnVy = false;}
      if(FIufTEMelQ == true){FIufTEMelQ = false;}
      if(MXrBxRbyRx == true){MXrBxRbyRx = false;}
      if(RDWHIHeNzR == true){RDWHIHeNzR = false;}
      if(omphyJhYdW == true){omphyJhYdW = false;}
      if(DEnoQOLadK == true){DEnoQOLadK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZNLMWIBVND
{ 
  void EBjGLsZNoT()
  { 
      bool zBTVTDCzjo = false;
      bool sodgrjkzet = false;
      bool BADWYnOSNU = false;
      bool PEtAZHXZAe = false;
      bool nrHADtuecw = false;
      bool Lxxkqyxxxe = false;
      bool nikOZoudGk = false;
      bool LKyAGIsDTd = false;
      bool sjpRJRGIIa = false;
      bool JacUpFHrZN = false;
      bool yQXrjAzwei = false;
      bool FtcSlEsTFI = false;
      bool hlUeakhdKA = false;
      bool BAdFfbLxhJ = false;
      bool SJdZVPxJil = false;
      bool LnmQeMwsRz = false;
      bool RUldgEQWmJ = false;
      bool rukwpXIuJK = false;
      bool mXuXnNNMZT = false;
      bool fSfiqxXArQ = false;
      string DrPUBVzxrX;
      string GMYfGRACwt;
      string bqOKHpIOKc;
      string uuZtfIjqtE;
      string JoKYolkFWk;
      string PNLJHMcFMK;
      string MklPbLmeAx;
      string gIIrjlgpUV;
      string ECqZNhiPmS;
      string eediqXDuwd;
      string yGFYDGFTZU;
      string fmjqFKsLBt;
      string bXqgRCeYAM;
      string iltqXyxSWH;
      string cPpRmrtmcg;
      string dqsBBaOXGA;
      string afSNltssTH;
      string NaotRLgZtZ;
      string IquThqrrow;
      string iYLVfwwcfs;
      if(DrPUBVzxrX == yGFYDGFTZU){zBTVTDCzjo = true;}
      else if(yGFYDGFTZU == DrPUBVzxrX){yQXrjAzwei = true;}
      if(GMYfGRACwt == fmjqFKsLBt){sodgrjkzet = true;}
      else if(fmjqFKsLBt == GMYfGRACwt){FtcSlEsTFI = true;}
      if(bqOKHpIOKc == bXqgRCeYAM){BADWYnOSNU = true;}
      else if(bXqgRCeYAM == bqOKHpIOKc){hlUeakhdKA = true;}
      if(uuZtfIjqtE == iltqXyxSWH){PEtAZHXZAe = true;}
      else if(iltqXyxSWH == uuZtfIjqtE){BAdFfbLxhJ = true;}
      if(JoKYolkFWk == cPpRmrtmcg){nrHADtuecw = true;}
      else if(cPpRmrtmcg == JoKYolkFWk){SJdZVPxJil = true;}
      if(PNLJHMcFMK == dqsBBaOXGA){Lxxkqyxxxe = true;}
      else if(dqsBBaOXGA == PNLJHMcFMK){LnmQeMwsRz = true;}
      if(MklPbLmeAx == afSNltssTH){nikOZoudGk = true;}
      else if(afSNltssTH == MklPbLmeAx){RUldgEQWmJ = true;}
      if(gIIrjlgpUV == NaotRLgZtZ){LKyAGIsDTd = true;}
      if(ECqZNhiPmS == IquThqrrow){sjpRJRGIIa = true;}
      if(eediqXDuwd == iYLVfwwcfs){JacUpFHrZN = true;}
      while(NaotRLgZtZ == gIIrjlgpUV){rukwpXIuJK = true;}
      while(IquThqrrow == IquThqrrow){mXuXnNNMZT = true;}
      while(iYLVfwwcfs == iYLVfwwcfs){fSfiqxXArQ = true;}
      if(zBTVTDCzjo == true){zBTVTDCzjo = false;}
      if(sodgrjkzet == true){sodgrjkzet = false;}
      if(BADWYnOSNU == true){BADWYnOSNU = false;}
      if(PEtAZHXZAe == true){PEtAZHXZAe = false;}
      if(nrHADtuecw == true){nrHADtuecw = false;}
      if(Lxxkqyxxxe == true){Lxxkqyxxxe = false;}
      if(nikOZoudGk == true){nikOZoudGk = false;}
      if(LKyAGIsDTd == true){LKyAGIsDTd = false;}
      if(sjpRJRGIIa == true){sjpRJRGIIa = false;}
      if(JacUpFHrZN == true){JacUpFHrZN = false;}
      if(yQXrjAzwei == true){yQXrjAzwei = false;}
      if(FtcSlEsTFI == true){FtcSlEsTFI = false;}
      if(hlUeakhdKA == true){hlUeakhdKA = false;}
      if(BAdFfbLxhJ == true){BAdFfbLxhJ = false;}
      if(SJdZVPxJil == true){SJdZVPxJil = false;}
      if(LnmQeMwsRz == true){LnmQeMwsRz = false;}
      if(RUldgEQWmJ == true){RUldgEQWmJ = false;}
      if(rukwpXIuJK == true){rukwpXIuJK = false;}
      if(mXuXnNNMZT == true){mXuXnNNMZT = false;}
      if(fSfiqxXArQ == true){fSfiqxXArQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THXZTCKNIP
{ 
  void DsOKLIIgPE()
  { 
      bool YujTRmzPsj = false;
      bool QVQFRDzOAz = false;
      bool ONiuYMxSJH = false;
      bool ogjOCIooul = false;
      bool XEWHHEsSiB = false;
      bool dXuSlLMntE = false;
      bool pgGltjkCDI = false;
      bool OKSOaJqanU = false;
      bool TdiHcQkQcq = false;
      bool uAtqwpyjMX = false;
      bool SqPZmTFgqb = false;
      bool TkAZjLxyJc = false;
      bool yUYMMNPbRj = false;
      bool LHOPBcNIUI = false;
      bool LEYAWKzUGj = false;
      bool szaiYyRDNY = false;
      bool DdOGQMWjYH = false;
      bool xndARtuXoC = false;
      bool NuUhqLgeqC = false;
      bool KKuuEhoRjJ = false;
      string DXpyhCisMC;
      string TxLtIMYUtF;
      string PrzCsXRmlX;
      string EfOQcAmzbn;
      string hPQBsdKwUU;
      string gfkgNKXmEK;
      string juHnxnhuQH;
      string YYsFWzbyJP;
      string NVSRpYuhDR;
      string cztQDmIbDF;
      string uPeMuHleKN;
      string iYdoxOcoxY;
      string rAqyeZecCj;
      string qzuDTxpGVh;
      string mPWoiDVFTo;
      string JSeeMtXfgV;
      string cJbaWidZUz;
      string XWSOkcdCOb;
      string EZJNZXUPqY;
      string ZKYAFdmwRA;
      if(DXpyhCisMC == uPeMuHleKN){YujTRmzPsj = true;}
      else if(uPeMuHleKN == DXpyhCisMC){SqPZmTFgqb = true;}
      if(TxLtIMYUtF == iYdoxOcoxY){QVQFRDzOAz = true;}
      else if(iYdoxOcoxY == TxLtIMYUtF){TkAZjLxyJc = true;}
      if(PrzCsXRmlX == rAqyeZecCj){ONiuYMxSJH = true;}
      else if(rAqyeZecCj == PrzCsXRmlX){yUYMMNPbRj = true;}
      if(EfOQcAmzbn == qzuDTxpGVh){ogjOCIooul = true;}
      else if(qzuDTxpGVh == EfOQcAmzbn){LHOPBcNIUI = true;}
      if(hPQBsdKwUU == mPWoiDVFTo){XEWHHEsSiB = true;}
      else if(mPWoiDVFTo == hPQBsdKwUU){LEYAWKzUGj = true;}
      if(gfkgNKXmEK == JSeeMtXfgV){dXuSlLMntE = true;}
      else if(JSeeMtXfgV == gfkgNKXmEK){szaiYyRDNY = true;}
      if(juHnxnhuQH == cJbaWidZUz){pgGltjkCDI = true;}
      else if(cJbaWidZUz == juHnxnhuQH){DdOGQMWjYH = true;}
      if(YYsFWzbyJP == XWSOkcdCOb){OKSOaJqanU = true;}
      if(NVSRpYuhDR == EZJNZXUPqY){TdiHcQkQcq = true;}
      if(cztQDmIbDF == ZKYAFdmwRA){uAtqwpyjMX = true;}
      while(XWSOkcdCOb == YYsFWzbyJP){xndARtuXoC = true;}
      while(EZJNZXUPqY == EZJNZXUPqY){NuUhqLgeqC = true;}
      while(ZKYAFdmwRA == ZKYAFdmwRA){KKuuEhoRjJ = true;}
      if(YujTRmzPsj == true){YujTRmzPsj = false;}
      if(QVQFRDzOAz == true){QVQFRDzOAz = false;}
      if(ONiuYMxSJH == true){ONiuYMxSJH = false;}
      if(ogjOCIooul == true){ogjOCIooul = false;}
      if(XEWHHEsSiB == true){XEWHHEsSiB = false;}
      if(dXuSlLMntE == true){dXuSlLMntE = false;}
      if(pgGltjkCDI == true){pgGltjkCDI = false;}
      if(OKSOaJqanU == true){OKSOaJqanU = false;}
      if(TdiHcQkQcq == true){TdiHcQkQcq = false;}
      if(uAtqwpyjMX == true){uAtqwpyjMX = false;}
      if(SqPZmTFgqb == true){SqPZmTFgqb = false;}
      if(TkAZjLxyJc == true){TkAZjLxyJc = false;}
      if(yUYMMNPbRj == true){yUYMMNPbRj = false;}
      if(LHOPBcNIUI == true){LHOPBcNIUI = false;}
      if(LEYAWKzUGj == true){LEYAWKzUGj = false;}
      if(szaiYyRDNY == true){szaiYyRDNY = false;}
      if(DdOGQMWjYH == true){DdOGQMWjYH = false;}
      if(xndARtuXoC == true){xndARtuXoC = false;}
      if(NuUhqLgeqC == true){NuUhqLgeqC = false;}
      if(KKuuEhoRjJ == true){KKuuEhoRjJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZYVLEFFWW
{ 
  void hgrnhuqSac()
  { 
      bool AEFkcUQFnE = false;
      bool thxzxNecCR = false;
      bool egFXkhmJug = false;
      bool BbrFgGdImV = false;
      bool tSUoSonJUZ = false;
      bool niwwbSyhAt = false;
      bool gHKGDRprRp = false;
      bool jVpgWLMQFw = false;
      bool tdnVrSfwdN = false;
      bool HwIromINlA = false;
      bool ywqeoRrPYP = false;
      bool GhbEzCToOj = false;
      bool lsODhnNxqi = false;
      bool DzeFxymIfZ = false;
      bool ZPWNHZTEsl = false;
      bool TTzBOEgnwB = false;
      bool EuXpLGDVGB = false;
      bool PKInJVWAuI = false;
      bool TJEFOiAcqr = false;
      bool QyMdVeqgBA = false;
      string pcTcMzeHxJ;
      string MVVPzJqYXo;
      string uEJJhyJAFT;
      string NkFCOxbFZA;
      string fwjdLHDgGG;
      string KJbKelSJtN;
      string pdCcwbQTAC;
      string hlyWIyTexZ;
      string ubszJDJuWc;
      string dRKLKBtHhj;
      string qjgEYYLEBg;
      string RmMTSOkCSr;
      string RUwXXPalLH;
      string DMxMiKtoak;
      string rEspLpEqsw;
      string QrnoSVnJgI;
      string xYrtcEpAkH;
      string TubhANbFLh;
      string LjsPqLYItM;
      string WkISmTLzNG;
      if(pcTcMzeHxJ == qjgEYYLEBg){AEFkcUQFnE = true;}
      else if(qjgEYYLEBg == pcTcMzeHxJ){ywqeoRrPYP = true;}
      if(MVVPzJqYXo == RmMTSOkCSr){thxzxNecCR = true;}
      else if(RmMTSOkCSr == MVVPzJqYXo){GhbEzCToOj = true;}
      if(uEJJhyJAFT == RUwXXPalLH){egFXkhmJug = true;}
      else if(RUwXXPalLH == uEJJhyJAFT){lsODhnNxqi = true;}
      if(NkFCOxbFZA == DMxMiKtoak){BbrFgGdImV = true;}
      else if(DMxMiKtoak == NkFCOxbFZA){DzeFxymIfZ = true;}
      if(fwjdLHDgGG == rEspLpEqsw){tSUoSonJUZ = true;}
      else if(rEspLpEqsw == fwjdLHDgGG){ZPWNHZTEsl = true;}
      if(KJbKelSJtN == QrnoSVnJgI){niwwbSyhAt = true;}
      else if(QrnoSVnJgI == KJbKelSJtN){TTzBOEgnwB = true;}
      if(pdCcwbQTAC == xYrtcEpAkH){gHKGDRprRp = true;}
      else if(xYrtcEpAkH == pdCcwbQTAC){EuXpLGDVGB = true;}
      if(hlyWIyTexZ == TubhANbFLh){jVpgWLMQFw = true;}
      if(ubszJDJuWc == LjsPqLYItM){tdnVrSfwdN = true;}
      if(dRKLKBtHhj == WkISmTLzNG){HwIromINlA = true;}
      while(TubhANbFLh == hlyWIyTexZ){PKInJVWAuI = true;}
      while(LjsPqLYItM == LjsPqLYItM){TJEFOiAcqr = true;}
      while(WkISmTLzNG == WkISmTLzNG){QyMdVeqgBA = true;}
      if(AEFkcUQFnE == true){AEFkcUQFnE = false;}
      if(thxzxNecCR == true){thxzxNecCR = false;}
      if(egFXkhmJug == true){egFXkhmJug = false;}
      if(BbrFgGdImV == true){BbrFgGdImV = false;}
      if(tSUoSonJUZ == true){tSUoSonJUZ = false;}
      if(niwwbSyhAt == true){niwwbSyhAt = false;}
      if(gHKGDRprRp == true){gHKGDRprRp = false;}
      if(jVpgWLMQFw == true){jVpgWLMQFw = false;}
      if(tdnVrSfwdN == true){tdnVrSfwdN = false;}
      if(HwIromINlA == true){HwIromINlA = false;}
      if(ywqeoRrPYP == true){ywqeoRrPYP = false;}
      if(GhbEzCToOj == true){GhbEzCToOj = false;}
      if(lsODhnNxqi == true){lsODhnNxqi = false;}
      if(DzeFxymIfZ == true){DzeFxymIfZ = false;}
      if(ZPWNHZTEsl == true){ZPWNHZTEsl = false;}
      if(TTzBOEgnwB == true){TTzBOEgnwB = false;}
      if(EuXpLGDVGB == true){EuXpLGDVGB = false;}
      if(PKInJVWAuI == true){PKInJVWAuI = false;}
      if(TJEFOiAcqr == true){TJEFOiAcqr = false;}
      if(QyMdVeqgBA == true){QyMdVeqgBA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRMNOWVTZY
{ 
  void YDmqHmruwE()
  { 
      bool DnuYwgfisA = false;
      bool qCakxBYJHH = false;
      bool MjQLJiREKe = false;
      bool ErBHWGfGeh = false;
      bool KyQQGEuUkJ = false;
      bool ZGdtsTWjON = false;
      bool OaYNuzBSOq = false;
      bool UReZxNTAEE = false;
      bool mxTBFyOGOC = false;
      bool iwqRTiZCUH = false;
      bool DcGsnHaExe = false;
      bool zWeKaQHWHw = false;
      bool jtELHYaMFN = false;
      bool nQexBJqZMy = false;
      bool WJJiDMQgqC = false;
      bool aCuXWJYulP = false;
      bool fOyipirhJQ = false;
      bool YgKIZajUHu = false;
      bool HsVDmlVGZq = false;
      bool jwnxRILarT = false;
      string nNKEdmIrUJ;
      string QbOyZsoEtm;
      string UMCLGhIXwQ;
      string wcuFGfncOx;
      string cdPRfjPtZN;
      string UQLzybKzxu;
      string ekwDMnfIrs;
      string FLowKqxkeV;
      string SNxhueQwGd;
      string VofSSqgLEr;
      string EGCgHIaOoH;
      string eYTacQmNHh;
      string WjBNWPfVdS;
      string JkflRLLPam;
      string DBGzzwUEpB;
      string ETDWVTEoKr;
      string cFkVxssgJQ;
      string FXmUdUcCNZ;
      string tafbOpgJQx;
      string HWFhKyPkBF;
      if(nNKEdmIrUJ == EGCgHIaOoH){DnuYwgfisA = true;}
      else if(EGCgHIaOoH == nNKEdmIrUJ){DcGsnHaExe = true;}
      if(QbOyZsoEtm == eYTacQmNHh){qCakxBYJHH = true;}
      else if(eYTacQmNHh == QbOyZsoEtm){zWeKaQHWHw = true;}
      if(UMCLGhIXwQ == WjBNWPfVdS){MjQLJiREKe = true;}
      else if(WjBNWPfVdS == UMCLGhIXwQ){jtELHYaMFN = true;}
      if(wcuFGfncOx == JkflRLLPam){ErBHWGfGeh = true;}
      else if(JkflRLLPam == wcuFGfncOx){nQexBJqZMy = true;}
      if(cdPRfjPtZN == DBGzzwUEpB){KyQQGEuUkJ = true;}
      else if(DBGzzwUEpB == cdPRfjPtZN){WJJiDMQgqC = true;}
      if(UQLzybKzxu == ETDWVTEoKr){ZGdtsTWjON = true;}
      else if(ETDWVTEoKr == UQLzybKzxu){aCuXWJYulP = true;}
      if(ekwDMnfIrs == cFkVxssgJQ){OaYNuzBSOq = true;}
      else if(cFkVxssgJQ == ekwDMnfIrs){fOyipirhJQ = true;}
      if(FLowKqxkeV == FXmUdUcCNZ){UReZxNTAEE = true;}
      if(SNxhueQwGd == tafbOpgJQx){mxTBFyOGOC = true;}
      if(VofSSqgLEr == HWFhKyPkBF){iwqRTiZCUH = true;}
      while(FXmUdUcCNZ == FLowKqxkeV){YgKIZajUHu = true;}
      while(tafbOpgJQx == tafbOpgJQx){HsVDmlVGZq = true;}
      while(HWFhKyPkBF == HWFhKyPkBF){jwnxRILarT = true;}
      if(DnuYwgfisA == true){DnuYwgfisA = false;}
      if(qCakxBYJHH == true){qCakxBYJHH = false;}
      if(MjQLJiREKe == true){MjQLJiREKe = false;}
      if(ErBHWGfGeh == true){ErBHWGfGeh = false;}
      if(KyQQGEuUkJ == true){KyQQGEuUkJ = false;}
      if(ZGdtsTWjON == true){ZGdtsTWjON = false;}
      if(OaYNuzBSOq == true){OaYNuzBSOq = false;}
      if(UReZxNTAEE == true){UReZxNTAEE = false;}
      if(mxTBFyOGOC == true){mxTBFyOGOC = false;}
      if(iwqRTiZCUH == true){iwqRTiZCUH = false;}
      if(DcGsnHaExe == true){DcGsnHaExe = false;}
      if(zWeKaQHWHw == true){zWeKaQHWHw = false;}
      if(jtELHYaMFN == true){jtELHYaMFN = false;}
      if(nQexBJqZMy == true){nQexBJqZMy = false;}
      if(WJJiDMQgqC == true){WJJiDMQgqC = false;}
      if(aCuXWJYulP == true){aCuXWJYulP = false;}
      if(fOyipirhJQ == true){fOyipirhJQ = false;}
      if(YgKIZajUHu == true){YgKIZajUHu = false;}
      if(HsVDmlVGZq == true){HsVDmlVGZq = false;}
      if(jwnxRILarT == true){jwnxRILarT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIVHELBDVV
{ 
  void zRUFBiaEgQ()
  { 
      bool tdixbmNYnB = false;
      bool OZXqYZpTJb = false;
      bool XjeHWeeTJh = false;
      bool ulWKObLaJA = false;
      bool bNECDHoWfO = false;
      bool kXzqTKybaw = false;
      bool HtPGFcDMcx = false;
      bool OOKIzJfcEP = false;
      bool pImuxXmfqE = false;
      bool diANsgyywZ = false;
      bool EcsiAVMpqK = false;
      bool eUXKFzGUJh = false;
      bool pWVYSeOxPR = false;
      bool LggdLMOEta = false;
      bool KwofYILpHs = false;
      bool acoNjgHUPU = false;
      bool HPaYzxnsys = false;
      bool jCZhWshozK = false;
      bool TXoVqhrSse = false;
      bool FtnZStUPgb = false;
      string LngFdaReDp;
      string QYJKgqIcEJ;
      string NCalTmbJmQ;
      string GXACgFjuwy;
      string zmOiShyJKF;
      string kYPcVIMulq;
      string yIqlisXHca;
      string HMgFKZmqSk;
      string nSzhfhIXgX;
      string soJFzpwczZ;
      string JqfixXqKRu;
      string UUbACfJJFB;
      string kAaFhSDbFU;
      string cKqsaxmPjI;
      string qxFkCXMICT;
      string gmWyoJPZBe;
      string TPFxRKciYE;
      string rsYxJmtoCJ;
      string FtYknpmsDR;
      string gMOFnbrISq;
      if(LngFdaReDp == JqfixXqKRu){tdixbmNYnB = true;}
      else if(JqfixXqKRu == LngFdaReDp){EcsiAVMpqK = true;}
      if(QYJKgqIcEJ == UUbACfJJFB){OZXqYZpTJb = true;}
      else if(UUbACfJJFB == QYJKgqIcEJ){eUXKFzGUJh = true;}
      if(NCalTmbJmQ == kAaFhSDbFU){XjeHWeeTJh = true;}
      else if(kAaFhSDbFU == NCalTmbJmQ){pWVYSeOxPR = true;}
      if(GXACgFjuwy == cKqsaxmPjI){ulWKObLaJA = true;}
      else if(cKqsaxmPjI == GXACgFjuwy){LggdLMOEta = true;}
      if(zmOiShyJKF == qxFkCXMICT){bNECDHoWfO = true;}
      else if(qxFkCXMICT == zmOiShyJKF){KwofYILpHs = true;}
      if(kYPcVIMulq == gmWyoJPZBe){kXzqTKybaw = true;}
      else if(gmWyoJPZBe == kYPcVIMulq){acoNjgHUPU = true;}
      if(yIqlisXHca == TPFxRKciYE){HtPGFcDMcx = true;}
      else if(TPFxRKciYE == yIqlisXHca){HPaYzxnsys = true;}
      if(HMgFKZmqSk == rsYxJmtoCJ){OOKIzJfcEP = true;}
      if(nSzhfhIXgX == FtYknpmsDR){pImuxXmfqE = true;}
      if(soJFzpwczZ == gMOFnbrISq){diANsgyywZ = true;}
      while(rsYxJmtoCJ == HMgFKZmqSk){jCZhWshozK = true;}
      while(FtYknpmsDR == FtYknpmsDR){TXoVqhrSse = true;}
      while(gMOFnbrISq == gMOFnbrISq){FtnZStUPgb = true;}
      if(tdixbmNYnB == true){tdixbmNYnB = false;}
      if(OZXqYZpTJb == true){OZXqYZpTJb = false;}
      if(XjeHWeeTJh == true){XjeHWeeTJh = false;}
      if(ulWKObLaJA == true){ulWKObLaJA = false;}
      if(bNECDHoWfO == true){bNECDHoWfO = false;}
      if(kXzqTKybaw == true){kXzqTKybaw = false;}
      if(HtPGFcDMcx == true){HtPGFcDMcx = false;}
      if(OOKIzJfcEP == true){OOKIzJfcEP = false;}
      if(pImuxXmfqE == true){pImuxXmfqE = false;}
      if(diANsgyywZ == true){diANsgyywZ = false;}
      if(EcsiAVMpqK == true){EcsiAVMpqK = false;}
      if(eUXKFzGUJh == true){eUXKFzGUJh = false;}
      if(pWVYSeOxPR == true){pWVYSeOxPR = false;}
      if(LggdLMOEta == true){LggdLMOEta = false;}
      if(KwofYILpHs == true){KwofYILpHs = false;}
      if(acoNjgHUPU == true){acoNjgHUPU = false;}
      if(HPaYzxnsys == true){HPaYzxnsys = false;}
      if(jCZhWshozK == true){jCZhWshozK = false;}
      if(TXoVqhrSse == true){TXoVqhrSse = false;}
      if(FtnZStUPgb == true){FtnZStUPgb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COKGETJGZJ
{ 
  void HBGRhnNtbu()
  { 
      bool hMaxeXBykY = false;
      bool YGLdkPqRih = false;
      bool dsUAgbIVtc = false;
      bool SKduarSkji = false;
      bool JDDtUyPBJn = false;
      bool aExeUoqZPC = false;
      bool PfDIFOcPCr = false;
      bool xFhzYZpaei = false;
      bool LGLFBOMzal = false;
      bool BsUgSdAuoG = false;
      bool VAyQqVWxGt = false;
      bool yQtgpJTyGq = false;
      bool BcoPqDkAft = false;
      bool ZtkYNLHuOf = false;
      bool qOsfmjynqJ = false;
      bool KBnyFrKiYm = false;
      bool kWQLTEeVTd = false;
      bool BXiazljIbH = false;
      bool EwIWjYGmSU = false;
      bool AYWauUxgMi = false;
      string OemHCjdwDu;
      string JdSrFRIyps;
      string yWlZPQioLC;
      string UhfsEMlSIV;
      string GCLuiaUUHc;
      string OhzxQqsMrk;
      string AnjBabxZns;
      string fopTluKppn;
      string wOghmlihbM;
      string SYZXUSSKUH;
      string dtgOxYreKV;
      string gCWEnlGBNn;
      string sOxaZGPSyT;
      string bzUhJChSkO;
      string sDXGfQBVii;
      string LRxfOPxFnp;
      string JZgqsghoul;
      string EmPzuoqqtJ;
      string FsiOHKCnTt;
      string EbetESVgMz;
      if(OemHCjdwDu == dtgOxYreKV){hMaxeXBykY = true;}
      else if(dtgOxYreKV == OemHCjdwDu){VAyQqVWxGt = true;}
      if(JdSrFRIyps == gCWEnlGBNn){YGLdkPqRih = true;}
      else if(gCWEnlGBNn == JdSrFRIyps){yQtgpJTyGq = true;}
      if(yWlZPQioLC == sOxaZGPSyT){dsUAgbIVtc = true;}
      else if(sOxaZGPSyT == yWlZPQioLC){BcoPqDkAft = true;}
      if(UhfsEMlSIV == bzUhJChSkO){SKduarSkji = true;}
      else if(bzUhJChSkO == UhfsEMlSIV){ZtkYNLHuOf = true;}
      if(GCLuiaUUHc == sDXGfQBVii){JDDtUyPBJn = true;}
      else if(sDXGfQBVii == GCLuiaUUHc){qOsfmjynqJ = true;}
      if(OhzxQqsMrk == LRxfOPxFnp){aExeUoqZPC = true;}
      else if(LRxfOPxFnp == OhzxQqsMrk){KBnyFrKiYm = true;}
      if(AnjBabxZns == JZgqsghoul){PfDIFOcPCr = true;}
      else if(JZgqsghoul == AnjBabxZns){kWQLTEeVTd = true;}
      if(fopTluKppn == EmPzuoqqtJ){xFhzYZpaei = true;}
      if(wOghmlihbM == FsiOHKCnTt){LGLFBOMzal = true;}
      if(SYZXUSSKUH == EbetESVgMz){BsUgSdAuoG = true;}
      while(EmPzuoqqtJ == fopTluKppn){BXiazljIbH = true;}
      while(FsiOHKCnTt == FsiOHKCnTt){EwIWjYGmSU = true;}
      while(EbetESVgMz == EbetESVgMz){AYWauUxgMi = true;}
      if(hMaxeXBykY == true){hMaxeXBykY = false;}
      if(YGLdkPqRih == true){YGLdkPqRih = false;}
      if(dsUAgbIVtc == true){dsUAgbIVtc = false;}
      if(SKduarSkji == true){SKduarSkji = false;}
      if(JDDtUyPBJn == true){JDDtUyPBJn = false;}
      if(aExeUoqZPC == true){aExeUoqZPC = false;}
      if(PfDIFOcPCr == true){PfDIFOcPCr = false;}
      if(xFhzYZpaei == true){xFhzYZpaei = false;}
      if(LGLFBOMzal == true){LGLFBOMzal = false;}
      if(BsUgSdAuoG == true){BsUgSdAuoG = false;}
      if(VAyQqVWxGt == true){VAyQqVWxGt = false;}
      if(yQtgpJTyGq == true){yQtgpJTyGq = false;}
      if(BcoPqDkAft == true){BcoPqDkAft = false;}
      if(ZtkYNLHuOf == true){ZtkYNLHuOf = false;}
      if(qOsfmjynqJ == true){qOsfmjynqJ = false;}
      if(KBnyFrKiYm == true){KBnyFrKiYm = false;}
      if(kWQLTEeVTd == true){kWQLTEeVTd = false;}
      if(BXiazljIbH == true){BXiazljIbH = false;}
      if(EwIWjYGmSU == true){EwIWjYGmSU = false;}
      if(AYWauUxgMi == true){AYWauUxgMi = false;}
    } 
}; 
