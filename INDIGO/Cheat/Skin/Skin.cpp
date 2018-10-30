#include "Skin.h"














Stick_t* Stick = new Stick_t[520];																									//Sticker Changer
DWORD dwEconItemInterfaceWrapper = 0;
int SafeWeaponID()
{
	CBaseEntity* me = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	if (!me)
		return 0;
	CBaseWeapon* weap = me->GetBaseWeapon();
	if (!weap)
		return 0;
	int nWeaponIndex = *weap->GeteAttributableItem()->GetItemDefinitionIndex();
	return nWeaponIndex;
}
typedef float(__thiscall* GetStickerAttributeBySlotIndexFloatFn)(void*, int, EStickerAttributeType, float);
GetStickerAttributeBySlotIndexFloatFn oGetStickerAttributeBySlotIndexFloat;
float __fastcall Hooked_GetStickerAttributeBySlotIndexFloat(void* thisptr, void* edx, int iSlot, EStickerAttributeType iAttribute, float flUnknown)
{
	auto pItem = reinterpret_cast<CBaseAttributableItem*>(uintptr_t(thisptr) - dwEconItemInterfaceWrapper);
	if (!pItem)
		return oGetStickerAttributeBySlotIndexFloat(thisptr, iSlot, iAttribute, flUnknown);
	int iID = *pItem->GetItemDefinitionIndex();
	if (!Stick[iID].StickersEnabled)
		return oGetStickerAttributeBySlotIndexFloat(thisptr, iSlot, iAttribute, flUnknown);
	switch (iAttribute)
	{
	case EStickerAttributeType::Wear:
		return min(1.f, Stick[iID].Stickers[iSlot].flWear + 0.0000000001f);
	case EStickerAttributeType::Scale:
		return Stick[iID].Stickers[iSlot].flScale;
	case EStickerAttributeType::Rotation:
		return Stick[iID].Stickers[iSlot].iRotation;
	default:
		break;
	}
	return oGetStickerAttributeBySlotIndexFloat(thisptr, iSlot, iAttribute, flUnknown);
}
typedef UINT(__thiscall* GetStickerAttributeBySlotIndexIntFn)(void*, int, EStickerAttributeType, float);
GetStickerAttributeBySlotIndexIntFn oGetStickerAttributeBySlotIndexInt;
UINT __fastcall Hooked_GetStickerAttributeBySlotIndexInt(void* thisptr, void* edx, int iSlot, EStickerAttributeType iAttribute, UINT iUnknown)
{
	auto pItem = reinterpret_cast<CBaseAttributableItem*>(uintptr_t(thisptr) - dwEconItemInterfaceWrapper);
	if (!pItem)
		return oGetStickerAttributeBySlotIndexInt(thisptr, iSlot, iAttribute, iUnknown);
	int iID = *pItem->GetItemDefinitionIndex();
	if (!Stick[iID].StickersEnabled)
		return oGetStickerAttributeBySlotIndexInt(thisptr, iSlot, iAttribute, iUnknown);
	return Stick[iID].Stickers[iSlot].iID;
	//return Parser::Stickers.List[g_Weapons[iID].Stickers[iSlot].iID].iID; //
}
bool IsCodePtr(void* ptr)
{
	constexpr const DWORD protect_flags = PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
	MEMORY_BASIC_INFORMATION out;
	VirtualQuery(ptr, &out, sizeof out);
	return out.Type
		&& !(out.Protect & (PAGE_GUARD | PAGE_NOACCESS))
		&& out.Protect & protect_flags;
}
void ApplyStickerHooks(CBaseAttributableItem* pItem)
{
	if (!dwEconItemInterfaceWrapper)
		dwEconItemInterfaceWrapper = 0x2DB0 + 0xC;
	void**& vmt = *reinterpret_cast<void***>(uintptr_t(pItem) + dwEconItemInterfaceWrapper);
	static void** hooked_vmt = nullptr;
	if (!hooked_vmt)
	{
		size_t size = 0;
		while (IsCodePtr(vmt[size]))
			++size;
		hooked_vmt = new void*[size];
		memcpy(hooked_vmt, vmt, size * sizeof(void*));
		oGetStickerAttributeBySlotIndexFloat = (GetStickerAttributeBySlotIndexFloatFn)hooked_vmt[4];
		hooked_vmt[4] = reinterpret_cast<void*>(&Hooked_GetStickerAttributeBySlotIndexFloat);
		oGetStickerAttributeBySlotIndexInt = (GetStickerAttributeBySlotIndexIntFn)hooked_vmt[5];
		hooked_vmt[5] = reinterpret_cast<void*>(&Hooked_GetStickerAttributeBySlotIndexInt);
	}
	vmt = hooked_vmt;
}







unordered_map<int, EconomyItemCfg> g_SkinChangerCfg;
unordered_map<int, const char*> g_ViewModelCfg;
unordered_map<const char*, const char*> g_KillIconCfg;

char* pWeaponData[33] =
{
	// ��������� - 0 - 9
	WEAPON_DEAGLE_STR,WEAPON_ELITE_STR,WEAPON_FIVESEVEN_STR,
	WEAPON_GLOCK_STR,WEAPON_HKP2000_STR,WEAPON_P250_STR,
	WEAPON_USP_S_STR,WEAPON_CZ75A_STR,WEAPON_REVOLVER_STR,
	WEAPON_TEC9_STR,
	// �������� - 10 - 30
	WEAPON_AK47_STR,WEAPON_AUG_STR,WEAPON_FAMAS_STR,WEAPON_GALILAR_STR,
	WEAPON_M249_STR,WEAPON_M4A1_STR,WEAPON_M4A1_S_STR,WEAPON_MAC10_STR,
	WEAPON_P90_STR,WEAPON_UMP45_STR,WEAPON_XM1014_STR,WEAPON_BIZON_STR,
	WEAPON_MAG7_STR,WEAPON_NEGEV_STR,WEAPON_SAWEDOFF_STR,
	WEAPON_MP7_STR,WEAPON_MP9_STR,WEAPON_NOVA_STR,WEAPON_SG553_STR,
	WEAPON_SCAR20_STR,WEAPON_G3SG1_STR,
	// ���������  - 31 - 32
	WEAPON_AWP_STR,WEAPON_SSG08_STR
};

int pWeaponItemIndexData[33] =
{
	// ��������� - 0 - 9
	WEAPON_DEAGLE,WEAPON_ELITE,WEAPON_FIVESEVEN,
	WEAPON_GLOCK,WEAPON_HKP2000,WEAPON_P250,
	WEAPON_USP_SILENCER,WEAPON_CZ75A,WEAPON_REVOLVER,
	WEAPON_TEC9,
	// �������� - 10 - 30
	WEAPON_AK47,WEAPON_AUG,WEAPON_FAMAS,WEAPON_GALILAR,
	WEAPON_M249,WEAPON_M4A1,WEAPON_M4A1_SILENCER,WEAPON_MAC10,
	WEAPON_P90,WEAPON_UMP45,WEAPON_XM1014,WEAPON_BIZON,
	WEAPON_MAG7,WEAPON_NEGEV,WEAPON_SAWEDOFF,
	WEAPON_MP7,WEAPON_MP9,WEAPON_NOVA,WEAPON_SG553,
	WEAPON_SCAR20,WEAPON_G3SG1,
	// ���������  - 31 - 32
	WEAPON_AWP,WEAPON_SSG08
};

char* pKnifeData[10] =
{
	"m9_bayonet","knife_flip","knife_gut","knife_karambit" ,"knife_m9_bayonet",
	"knife_tactical","knife_falchion","knife_survival_bowie","knife_butterfly","knife_push"
};

//[enc_string_enable /]
const char* bloodhound = "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl";
const char* handwrap = "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl";
const char* slick = "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl";
const char* sporty = "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl";
const char* motorcycle = "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl";
const char* specialist = "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl";
const char* hydra = "models / weapons / v_models / arms / glove_bloodhound / v_glove_bloodhound_hydra.mdl";
//[enc_string_disable /]

WeaponSkins_s WeaponSkins[33];
KnifeSkins_s KnifeSkins[10];

GlovesSkins_s GlovesSkin_Array[49] =
{
	{ 5030,10018,sporty },
	{ 5030,10037,sporty },
	{ 5030,10038,sporty },
	{ 5030,10019,sporty },
	{ 5030,10048,sporty },
	{ 5030,10047,sporty },
	{ 5030,10046,sporty },
	{ 5030,10045,sporty },
	{ 5033,10024,motorcycle },
	{ 5033,10026,motorcycle },
	{ 5033,10027,motorcycle },
	{ 5033,10028,motorcycle },
	{ 5033,10052,motorcycle },
	{ 5033,10051,motorcycle },
	{ 5033,10050,motorcycle },
	{ 5033,10049,motorcycle },
	{ 5034,10033,specialist },
	{ 5034,10034,specialist },
	{ 5034,10035,specialist },
	{ 5034,10030,specialist },
	{ 5034,10064,specialist },
	{ 5034,10063,specialist },
	{ 5034,10062,specialist },
	{ 5034,10061,specialist },
	{ 5031,10013,slick },
	{ 5031,10015,slick },
	{ 5031,10016,slick },
	{ 5031,10040,slick },
	{ 5031,10044,slick },
	{ 5031,10043,slick },
	{ 5031,10042,slick },
	{ 5031,10041,slick },
	{ 5032,10009,handwrap },
	{ 5032,10010,handwrap },
	{ 5032,10036,handwrap },
	{ 5032,10021,handwrap },
	{ 5032,10056,handwrap },
	{ 5032,10055,handwrap },
	{ 5032,10054,handwrap },
	{ 5032,10053,handwrap },
	{ 5027,10006,bloodhound },
	{ 5027,10007,bloodhound },
	{ 5027,10008,bloodhound },
	{ 5027,10039,bloodhound },
	{ 5035,10060,hydra },
	{ 5035,10059,hydra },
	{ 5035,10058,hydra },
	{ 5035,10057,hydra },
};
//[junk_enable /]
//[enc_string_enable /]
RecvVarProxyFn fnSequenceProxyFn = NULL;

using namespace Client;

int GetWeaponSkinIndexFromPaintKit(int iPaintKit)
{
	for (size_t iSkinID = 0; iSkinID < WeaponSkins[iWeaponID].SkinPaintKit.size(); iSkinID++)
	{
		if (WeaponSkins[iWeaponID].SkinPaintKit[iSkinID] == iPaintKit)
			return iSkinID;
	}

	return 0;
}

int GetKnifeSkinIndexFromPaintKit(int iPaintKit, bool tt)
{
	int iKnifeModelID = (tt ? Settings::Skin::knf_tt_model - 1 : Settings::Skin::knf_ct_model - 1);

	for (size_t iSkinID = 0; iSkinID < KnifeSkins[iKnifeModelID].SkinPaintKit.size(); iSkinID++)
	{
		if (KnifeSkins[iKnifeModelID].SkinPaintKit[iSkinID] == iPaintKit)
			return iSkinID;
	}

	return 0;
}
void CSkin::OnEvents(IGameEvent* pEvent)
{
	const char* szEventName = pEvent->GetName();

	if (!strcmp(szEventName, "player_death"))
		ApplyCustomKillIcon(pEvent);

	if (!strcmp(szEventName, "game_newmap"))
	{
		if (g_ViewModelCfg.size() >= 1)
			g_ViewModelCfg.clear();

		SetSkinConfig();
		SetModelConfig();
		SetKillIconCfg();
	}
}

void CSkin::SetSkinConfig()
{
	int KnifeModelsType[10] =
	{
		WEAPON_KNIFE_BAYONET,WEAPON_KNIFE_FLIP,WEAPON_KNIFE_GUT,WEAPON_KNIFE_KARAMBIT,
		WEAPON_KNIFE_M9_BAYONET,WEAPON_KNIFE_TACTICAL,WEAPON_KNIFE_FALCHION,
		WEAPON_KNIFE_SURVIVAL_BOWIE,WEAPON_KNIFE_BUTTERFLY,WEAPON_KNIFE_PUSH
	};

	if (Settings::Skin::knf_ct_model >= 1 && Settings::Skin::knf_ct_model <= 10)
	{
		g_SkinChangerCfg[WEAPON_KNIFE].iItemDefinitionIndex = KnifeModelsType[Settings::Skin::knf_ct_model - 1];
	}
	else
	{
		g_SkinChangerCfg[WEAPON_KNIFE].iItemDefinitionIndex = WEAPON_KNIFE;
	}

	if (Settings::Skin::knf_ct_skin)
	{
		g_SkinChangerCfg[WEAPON_KNIFE].nFallbackPaintKit = Settings::Skin::knf_ct_skin;
	}
	else
	{
		g_SkinChangerCfg[WEAPON_KNIFE].nFallbackPaintKit = 0;
	}

	if (Settings::Skin::knf_tt_model >= 1 && Settings::Skin::knf_tt_model <= 10)
	{
		g_SkinChangerCfg[WEAPON_KNIFE_T].iItemDefinitionIndex = KnifeModelsType[Settings::Skin::knf_tt_model - 1];
	}
	else
	{
		g_SkinChangerCfg[WEAPON_KNIFE_T].iItemDefinitionIndex = WEAPON_KNIFE_T;
	}

	if (Settings::Skin::knf_tt_skin)
	{
		g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackPaintKit = Settings::Skin::knf_tt_skin;
	}
	else
	{
		g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackPaintKit = 0;
	}
}

void CSkin::SetModelConfig()
{
	char* pszDefaultCtModel = "models/weapons/v_knife_default_ct.mdl";
	char* pszDefaultTtModel = "models/weapons/v_knife_default_t.mdl";

	char* pszKnifeBayonet = "models/weapons/v_knife_bayonet.mdl";
	char* pszKnifeFlip = "models/weapons/v_knife_flip.mdl";
	char* pszKnifeGut = "models/weapons/v_knife_gut.mdl";
	char* pszKnifeKarambit = "models/weapons/v_knife_karam.mdl";
	char* pszKnifeM9Bay = "models/weapons/v_knife_m9_bay.mdl";
	char* pszKnifeHuntsman = "models/weapons/v_knife_tactical.mdl";
	char* pszKnifeFalchion = "models/weapons/v_knife_falchion_advanced.mdl";
	char* pszKnifeBowie = "models/weapons/v_knife_survival_bowie.mdl";
	char* pszKnifeButterfly = "models/weapons/v_knife_butterfly.mdl";
	char* pszKnifeShadow = "models/weapons/v_knife_push.mdl";

	char* pszKnifeModels[10] =
	{
		pszKnifeBayonet,pszKnifeFlip,pszKnifeGut,pszKnifeKarambit,
		pszKnifeM9Bay,pszKnifeHuntsman,pszKnifeFalchion,pszKnifeBowie,
		pszKnifeButterfly,pszKnifeShadow
	};

	int nOriginalKnifeCT = Interfaces::ModelInfo()->GetModelIndex(pszDefaultCtModel);
	int nOriginalKnifeT = Interfaces::ModelInfo()->GetModelIndex(pszDefaultTtModel);

	if (Settings::Skin::knf_ct_model >= 1 && Settings::Skin::knf_ct_model <= 10)
	{
		char* mdl_ct = pszKnifeModels[Settings::Skin::knf_ct_model - 1];
		g_ViewModelCfg[nOriginalKnifeCT] = mdl_ct;
	}
	else
	{
		g_ViewModelCfg[nOriginalKnifeCT] = pszDefaultCtModel;
	}

	if (Settings::Skin::knf_tt_model >= 1 && Settings::Skin::knf_tt_model <= 10)
	{
		char* mdl_tt = pszKnifeModels[Settings::Skin::knf_tt_model - 1];
		g_ViewModelCfg[nOriginalKnifeT] = mdl_tt;
	}
	else
	{
		g_ViewModelCfg[nOriginalKnifeT] = pszDefaultTtModel;
	}
}

void CSkin::SetKillIconCfg()
{
	//[enc_string_disable /]
	char* pszKnifeModelsIcon[10] =
	{
		"bayonet","knife_flip","knife_gut","knife_karambit",
		"knife_m9_bayonet","knife_tactical","knife_falchion",
		"knife_survival_bowie","knife_butterfly","knife_push"
	};
	//[enc_string_enable /]
	if (Settings::Skin::knf_ct_model >= 1 && Settings::Skin::knf_ct_model <= 10)
	{
		g_KillIconCfg["knife_default_ct"] = pszKnifeModelsIcon[Settings::Skin::knf_ct_model - 1];
	}
	else
	{
		g_KillIconCfg["knife_default_ct"] = "knife_default_ct";
	}
	if (Settings::Skin::knf_tt_model >= 1 && Settings::Skin::knf_tt_model <= 10)
	{
		g_KillIconCfg["knife_t"] = pszKnifeModelsIcon[Settings::Skin::knf_tt_model - 1];
	}
	else
	{
		g_KillIconCfg["knife_t"] = "knife_t";
	}
}

void CSkin::InitalizeSkins()
{
	auto pSkins = new DynSkin::Skins::CSkins();

	string CsgoPatch = CSX::Utils::GetModuleBaseDir(0) + "\\csgo";

	if (pSkins->Load(CsgoPatch, "csgo"))
	{
		// Load Weapon Skins
		for (int iWeaponIndex = 0; iWeaponIndex < WEAPON_DATA_SIZE; iWeaponIndex++)
		{
			string WeaponSearch = "weapon_" + string(pWeaponData[iWeaponIndex]);

			DynSkin::Skins::vecSkinInfo SkinInfoWeapon = pSkins->GetSkinInfoByWeapon(WeaponSearch);

			for (size_t iSkinWeaponIndex = 0; iSkinWeaponIndex < SkinInfoWeapon.size(); iSkinWeaponIndex++)
			{
				if (SkinInfoWeapon[iSkinWeaponIndex].nFallbackPaintKit >= 10000)
					continue;

				string DragonKing = "Dragon King";
				string FullName = SkinInfoWeapon[iSkinWeaponIndex]._name;

				if (SkinInfoWeapon[iSkinWeaponIndex].nFallbackPaintKit == 400 && SkinInfoWeapon[iSkinWeaponIndex]._name.find(DragonKing) != string::npos)
					FullName = DragonKing;

				WeaponSkins[iWeaponIndex].SkinPaintKit.push_back(SkinInfoWeapon[iSkinWeaponIndex].nFallbackPaintKit);
				WeaponSkins[iWeaponIndex].SkinNames.push_back(FullName);
			}
		}

		// Load Knife Skins
		for (int iKnifeIndex = 0; iKnifeIndex < KNIFE_DATA_SIZE; iKnifeIndex++)
		{
			string KnifeSearch = "weapon_" + string(pKnifeData[iKnifeIndex]);

			DynSkin::Skins::vecSkinInfo SkinInfoKnife = pSkins->GetSkinInfoByWeapon(KnifeSearch);

			for (size_t iSkinKnifeIndex = 0; iSkinKnifeIndex < SkinInfoKnife.size(); iSkinKnifeIndex++)
			{
				KnifeSkins[iKnifeIndex].SkinPaintKit.push_back(SkinInfoKnife[iSkinKnifeIndex].nFallbackPaintKit);
				KnifeSkins[iKnifeIndex].SkinNames.push_back(SkinInfoKnife[iSkinKnifeIndex]._name);
			}
		}

		pSkins->Release();
	}

	delete pSkins;

	SetSkinConfig();
	SetKillIconCfg();

	for (ClientClass* pClass = Interfaces::Client()->GetAllClasses(); pClass; pClass = pClass->m_pNext)
	{
		if (!strcmp(pClass->m_pNetworkName, "CBaseViewModel"))
		{
			RecvTable* pClassTable = pClass->m_pRecvTable;

			for (int nIndex = 0; nIndex < pClassTable->m_nProps; nIndex++)
			{
				RecvProp* pProp = &pClassTable->m_pProps[nIndex];

				if (!pProp || strcmp(pProp->m_pVarName, "m_nSequence"))
					continue;

				fnSequenceProxyFn = pProp->m_ProxyFn;
				pProp->m_ProxyFn = (RecvVarProxyFn)Hook_SetViewModelSequence;

				break;
			}

			break;
		}
	}
}

bool CSkin::ApplyCustomSkin(CBaseAttributableItem* pWeapon, int nWeaponIndex)
{
	if (g_SkinChangerCfg.find(nWeaponIndex) == g_SkinChangerCfg.end())
		return false;

	*pWeapon->GetFallbackPaintKit() = g_SkinChangerCfg[nWeaponIndex].nFallbackPaintKit;
	*pWeapon->GetEntityQuality() = g_SkinChangerCfg[nWeaponIndex].iEntityQuality;
	*pWeapon->GetFallbackStatTrak() = g_SkinChangerCfg[nWeaponIndex].nFallbackStatTrak;
	*pWeapon->GetFallbackWear() = g_SkinChangerCfg[nWeaponIndex].flFallbackWear;
	*pWeapon->GetFallbackSeed() = g_SkinChangerCfg[nWeaponIndex].nFallbackSeed;

	if (g_SkinChangerCfg[nWeaponIndex].iItemDefinitionIndex)
	{
		*pWeapon->GetItemDefinitionIndex() = g_SkinChangerCfg[nWeaponIndex].iItemDefinitionIndex;
	}

	*pWeapon->GetItemIDHigh() = -1;

	return true;
}

bool CSkin::ApplyCustomModel(CBaseEntity* pLocal, CBaseAttributableItem* pWeapon)
{
	CBaseViewModel* pViewModel = pLocal->GetViewModel();

	if (!pViewModel)
		return false;

	DWORD hViewModelWeapon = pViewModel->GetWeapon();

	CBaseAttributableItem* pViewModelWeapon = (CBaseAttributableItem*)Interfaces::EntityList()->GetClientEntityFromHandle((PVOID)hViewModelWeapon);

	if (pViewModelWeapon != pWeapon)
		return false;

	int nViewModelIndex = pViewModel->GetModelIndex();

	if (!nViewModelIndex)
		return false;

	if (g_ViewModelCfg.find(nViewModelIndex) == g_ViewModelCfg.end())
		return false;

	pViewModel->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex(g_ViewModelCfg[nViewModelIndex]));

	return true;
}

bool CSkin::ApplyCustomKillIcon(IGameEvent* pEvent)
{
	int nUserID = pEvent->GetInt("attacker");

	if (!nUserID)
		return false;

	if (Interfaces::Engine()->GetPlayerForUserID(nUserID) != Interfaces::Engine()->GetLocalPlayer())
		return false;

	const char* szWeapon = pEvent->GetString("weapon");

	for (auto ReplacementIcon : g_KillIconCfg)
	{
		if (!strcmp(szWeapon, ReplacementIcon.first))
		{
			pEvent->SetString("weapon", ReplacementIcon.second);
			break;
		}
	}

	return true;
}

void Skin_OnFrameStageNotify(ClientFrameStage_t Stage)
{
	if (Stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		int nLocalPlayerID = Interfaces::Engine()->GetLocalPlayer();

		CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(nLocalPlayerID);

		if (!pLocal || pLocal->IsDead())
			return;

		UINT* hWeapons = pLocal->GetWeapons();

		if (!hWeapons)
			return;

		PlayerInfo LocalPlayerInfo;
		Interfaces::Engine()->GetPlayerInfo(nLocalPlayerID, &LocalPlayerInfo);

		for (int nIndex = 0; hWeapons[nIndex]; nIndex++)
		{
			CBaseAttributableItem* pWeapon = (CBaseAttributableItem*)Interfaces::EntityList()->GetClientEntityFromHandle(
				(PVOID)hWeapons[nIndex]);

			CBaseViewModel* pView = pWeapon->GetViewModel();

			if (!pWeapon)
				continue;

			int nWeaponIndex = *pWeapon->GetItemDefinitionIndex();

			if (g_ViewModelCfg.find(pView->GetModelIndex()) != g_ViewModelCfg.end())
				pView->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex(g_ViewModelCfg[pView->GetModelIndex()]));

			if (Client::g_pSkin)
				Client::g_pSkin->ApplyCustomModel(pLocal, pWeapon);

			if (LocalPlayerInfo.m_nXuidLow != *pWeapon->GetOriginalOwnerXuidLow())
				continue;

			if (LocalPlayerInfo.m_nXuidHigh != *pWeapon->GetOriginalOwnerXuidHigh())
				continue;

			if (Client::g_pSkin)
				Client::g_pSkin->ApplyCustomSkin(pWeapon, nWeaponIndex);

			*pWeapon->GetAccountID() = LocalPlayerInfo.m_nXuidLow;

			ApplyStickerHooks(pWeapon);
		}
	}
}

void Gloves_OnFrameStageNotify(ClientFrameStage_t Stage)
{
	if (!Settings::Skin::gloves_skin)
		return;

	if (Stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		return;

	if (!IsLocalAlive())
		return;

	CBaseEntity* pLocal = g_pPlayers->GetLocal()->m_pEntity;

	UINT* pWeapons = pLocal->GetWeapons();

	if (!pWeapons)
		return;

	UINT* pWareables = pLocal->GetWearables();

	if (!Interfaces::EntityList()->GetClientEntityFromHandle((PVOID)pWareables[0]))
	{
		for (ClientClass* pClass = Interfaces::Client()->GetAllClasses(); pClass; pClass = pClass->m_pNext)
		{
			if (pClass->m_ClassID == (int)CLIENT_CLASS_ID::CEconWearable)
			{
				int iEntry = Interfaces::EntityList()->GetHighestEntityIndex() + 1;
				int iSerial = CSX::Utils::RandomIntRange(0x0, 0xFFF);

				if (pClass->m_pCreateFn(iEntry, iSerial))
				{
					pWareables[0] = iEntry | (iSerial << 16);
					break;
				}
			}
		}

		if (!pWareables[0])
			return;

		CBaseAttributableItem* pGlove = (CBaseAttributableItem*)Interfaces::EntityList()->GetClientEntityFromHandle((PVOID)pWareables[0]);

		if (!pGlove)
			return;

		PlayerInfo LocalPlayerInfo;

		if (!Interfaces::Engine()->GetPlayerInfo(Interfaces::Engine()->GetLocalPlayer(), &LocalPlayerInfo))
			return;

		*pGlove->GetItemDefinitionIndex() = GlovesSkin_Array[Settings::Skin::gloves_skin - 1].ItemIndex;
		*pGlove->GetItemIDHigh() = -1;
		*pGlove->GetEntityQuality() = 4;
		*pGlove->GetAccountID() = LocalPlayerInfo.m_nXuidLow;
		*pGlove->GetFallbackWear() = 0.00000001f;
		*pGlove->GetFallbackSeed() = 0;
		*pGlove->GetFallbackStatTrak() = -1;
		*pGlove->GetFallbackPaintKit() = GlovesSkin_Array[Settings::Skin::gloves_skin - 1].PaintKit;

		int ModelIndex = Interfaces::ModelInfo()->GetModelIndex(
			GlovesSkin_Array[Settings::Skin::gloves_skin - 1].szModel);

		if (!ModelIndex)
			return;

		if (pGlove->GetViewModel())
			pGlove->GetViewModel()->SetModelIndex(ModelIndex);

		if (pGlove->GetClientNetworkable())
			pGlove->GetClientNetworkable()->PreDataUpdate(DATA_UPDATE_CREATED);
	}
}

void Hook_SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut)
{
	CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);
	CBaseViewModel* pViewModel = (CBaseViewModel*)pStruct;

	if (pViewModel)
	{
		IClientEntity* pOwner = Interfaces::EntityList()->GetClientEntityFromHandle((PVOID)pViewModel->GetOwner());

		if (pOwner && pOwner->EntIndex() == Interfaces::Engine()->GetLocalPlayer())
		{
			const model_t* pModel = Interfaces::ModelInfo()->GetModel(pViewModel->GetModelIndex());
			const char* szModel = Interfaces::ModelInfo()->GetModelName(pModel);

			int m_nSequence = pData->m_Value.m_Int;
			//[junk_disable /]
			if (!strcmp(szModel, "models/weapons/v_knife_butterfly.mdl"))
			{
				switch (m_nSequence)
				{
				case SEQUENCE_DEFAULT_DRAW:
					m_nSequence = CSX::Utils::RandomIntRange(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2); break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = CSX::Utils::RandomIntRange(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03); break;
				default:
					m_nSequence++;
				}
			}
			else if (!strcmp(szModel, "models/weapons/v_knife_falchion_advanced.mdl"))
			{
				// Fix animations for the Falchion Knife.
				switch (m_nSequence)
				{
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = CSX::Utils::RandomIntRange(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP); break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = CSX::Utils::RandomIntRange(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02); break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence--;
				}
			}
			else if (!strcmp(szModel, "models/weapons/v_knife_push.mdl"))
			{
				// Fix animations for the Shadow Daggers.
				switch (m_nSequence)
				{
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
				case SEQUENCE_DEFAULT_LIGHT_MISS1:
				case SEQUENCE_DEFAULT_LIGHT_MISS2:
					m_nSequence = CSX::Utils::RandomIntRange(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5); break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = CSX::Utils::RandomIntRange(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1); break;
				case SEQUENCE_DEFAULT_HEAVY_HIT1:
				case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence += 3; break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence += 2;
				}
			}
			else if (!strcmp(szModel, "models/weapons/v_knife_survival_bowie.mdl"))
			{
				switch (m_nSequence)
				{
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_BOWIE_IDLE1; break;
				default:
					m_nSequence--;
				}
			}
			//[junk_enable /]
			pData->m_Value.m_Int = m_nSequence;
		}
	}

	fnSequenceProxyFn(pData, pStruct, pOut);
}







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPJRFUKMPX
{ 
  void gQaUPHmtJp()
  { 
      bool rAiBiimuBF = false;
      bool VATetEbEAC = false;
      bool NVcZpBraMu = false;
      bool iryYXkajyD = false;
      bool SPpEFOrnHo = false;
      bool sdmnCWXILg = false;
      bool qMiGWcCuHI = false;
      bool dqGxjyeYTa = false;
      bool JESXBEEJVA = false;
      bool MRYQMGgigc = false;
      bool MwfyKCWpEE = false;
      bool rzojXmsLFR = false;
      bool XrYGuLRokd = false;
      bool QuqqOMXUMz = false;
      bool gNFRINcosY = false;
      bool MUdPETXYDz = false;
      bool jhFamxIxVK = false;
      bool OYzFjKmGyh = false;
      bool icuLQwQamt = false;
      bool oyQMOzIeeL = false;
      string XhhhhyJbEs;
      string pmjrhwrYoj;
      string dMgYMlEBbd;
      string FQcNlfPjNb;
      string ecmEiWBtTm;
      string PQdcgKAIUw;
      string tIAanYKVFC;
      string fIKMFAYbpp;
      string kJgoOolAga;
      string eGORhWcMQJ;
      string MenRGHGRWg;
      string kYSeLjaLMy;
      string lJoeWZsrei;
      string XLKfdFVOhG;
      string iUcAoGmjGx;
      string uQARWCpJuf;
      string NNlnJYNlBF;
      string OLcFPRgooP;
      string lJlgmGLrJa;
      string PMTCsUinqQ;
      if(XhhhhyJbEs == MenRGHGRWg){rAiBiimuBF = true;}
      else if(MenRGHGRWg == XhhhhyJbEs){MwfyKCWpEE = true;}
      if(pmjrhwrYoj == kYSeLjaLMy){VATetEbEAC = true;}
      else if(kYSeLjaLMy == pmjrhwrYoj){rzojXmsLFR = true;}
      if(dMgYMlEBbd == lJoeWZsrei){NVcZpBraMu = true;}
      else if(lJoeWZsrei == dMgYMlEBbd){XrYGuLRokd = true;}
      if(FQcNlfPjNb == XLKfdFVOhG){iryYXkajyD = true;}
      else if(XLKfdFVOhG == FQcNlfPjNb){QuqqOMXUMz = true;}
      if(ecmEiWBtTm == iUcAoGmjGx){SPpEFOrnHo = true;}
      else if(iUcAoGmjGx == ecmEiWBtTm){gNFRINcosY = true;}
      if(PQdcgKAIUw == uQARWCpJuf){sdmnCWXILg = true;}
      else if(uQARWCpJuf == PQdcgKAIUw){MUdPETXYDz = true;}
      if(tIAanYKVFC == NNlnJYNlBF){qMiGWcCuHI = true;}
      else if(NNlnJYNlBF == tIAanYKVFC){jhFamxIxVK = true;}
      if(fIKMFAYbpp == OLcFPRgooP){dqGxjyeYTa = true;}
      if(kJgoOolAga == lJlgmGLrJa){JESXBEEJVA = true;}
      if(eGORhWcMQJ == PMTCsUinqQ){MRYQMGgigc = true;}
      while(OLcFPRgooP == fIKMFAYbpp){OYzFjKmGyh = true;}
      while(lJlgmGLrJa == lJlgmGLrJa){icuLQwQamt = true;}
      while(PMTCsUinqQ == PMTCsUinqQ){oyQMOzIeeL = true;}
      if(rAiBiimuBF == true){rAiBiimuBF = false;}
      if(VATetEbEAC == true){VATetEbEAC = false;}
      if(NVcZpBraMu == true){NVcZpBraMu = false;}
      if(iryYXkajyD == true){iryYXkajyD = false;}
      if(SPpEFOrnHo == true){SPpEFOrnHo = false;}
      if(sdmnCWXILg == true){sdmnCWXILg = false;}
      if(qMiGWcCuHI == true){qMiGWcCuHI = false;}
      if(dqGxjyeYTa == true){dqGxjyeYTa = false;}
      if(JESXBEEJVA == true){JESXBEEJVA = false;}
      if(MRYQMGgigc == true){MRYQMGgigc = false;}
      if(MwfyKCWpEE == true){MwfyKCWpEE = false;}
      if(rzojXmsLFR == true){rzojXmsLFR = false;}
      if(XrYGuLRokd == true){XrYGuLRokd = false;}
      if(QuqqOMXUMz == true){QuqqOMXUMz = false;}
      if(gNFRINcosY == true){gNFRINcosY = false;}
      if(MUdPETXYDz == true){MUdPETXYDz = false;}
      if(jhFamxIxVK == true){jhFamxIxVK = false;}
      if(OYzFjKmGyh == true){OYzFjKmGyh = false;}
      if(icuLQwQamt == true){icuLQwQamt = false;}
      if(oyQMOzIeeL == true){oyQMOzIeeL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIQYODKYII
{ 
  void ZQENcdPxaz()
  { 
      bool EaetjxyWZz = false;
      bool fLjetsHGBJ = false;
      bool PhpfeTmFiJ = false;
      bool ApWwdcdnmn = false;
      bool SSIblyXlDl = false;
      bool oUJQtWkzOP = false;
      bool KsnPzonmBQ = false;
      bool OSSMpxYOsg = false;
      bool wBBxTegGBG = false;
      bool reZWcZdrbw = false;
      bool JjjlWWCwZx = false;
      bool xVFhTJqqwT = false;
      bool IhktXiruiQ = false;
      bool SglwWMQOZx = false;
      bool cjfEJWZrDT = false;
      bool hmwHnbyoOm = false;
      bool dGMJePjJKG = false;
      bool rbQzqXCgkB = false;
      bool JAqOhfkdIu = false;
      bool NbAmSWXWYs = false;
      string FcJEOrAFtA;
      string LwAPcQMmAr;
      string PMGZddCTKZ;
      string MIZHqXAAcc;
      string RwCPMBBnWO;
      string CRmBMrWiZk;
      string ofuUnDWsXF;
      string PMJXZTJpMc;
      string bOxuXtUYtz;
      string BQZrmlAhaJ;
      string dIPRyoHOas;
      string hfWxIaizws;
      string hyyYDzlRjn;
      string SbPDyTyewh;
      string mFxBQUtciM;
      string CBkgbfJqNz;
      string CpemaGQSyo;
      string bECNGbAxHh;
      string EJhXlRphbS;
      string JHQxexaKZK;
      if(FcJEOrAFtA == dIPRyoHOas){EaetjxyWZz = true;}
      else if(dIPRyoHOas == FcJEOrAFtA){JjjlWWCwZx = true;}
      if(LwAPcQMmAr == hfWxIaizws){fLjetsHGBJ = true;}
      else if(hfWxIaizws == LwAPcQMmAr){xVFhTJqqwT = true;}
      if(PMGZddCTKZ == hyyYDzlRjn){PhpfeTmFiJ = true;}
      else if(hyyYDzlRjn == PMGZddCTKZ){IhktXiruiQ = true;}
      if(MIZHqXAAcc == SbPDyTyewh){ApWwdcdnmn = true;}
      else if(SbPDyTyewh == MIZHqXAAcc){SglwWMQOZx = true;}
      if(RwCPMBBnWO == mFxBQUtciM){SSIblyXlDl = true;}
      else if(mFxBQUtciM == RwCPMBBnWO){cjfEJWZrDT = true;}
      if(CRmBMrWiZk == CBkgbfJqNz){oUJQtWkzOP = true;}
      else if(CBkgbfJqNz == CRmBMrWiZk){hmwHnbyoOm = true;}
      if(ofuUnDWsXF == CpemaGQSyo){KsnPzonmBQ = true;}
      else if(CpemaGQSyo == ofuUnDWsXF){dGMJePjJKG = true;}
      if(PMJXZTJpMc == bECNGbAxHh){OSSMpxYOsg = true;}
      if(bOxuXtUYtz == EJhXlRphbS){wBBxTegGBG = true;}
      if(BQZrmlAhaJ == JHQxexaKZK){reZWcZdrbw = true;}
      while(bECNGbAxHh == PMJXZTJpMc){rbQzqXCgkB = true;}
      while(EJhXlRphbS == EJhXlRphbS){JAqOhfkdIu = true;}
      while(JHQxexaKZK == JHQxexaKZK){NbAmSWXWYs = true;}
      if(EaetjxyWZz == true){EaetjxyWZz = false;}
      if(fLjetsHGBJ == true){fLjetsHGBJ = false;}
      if(PhpfeTmFiJ == true){PhpfeTmFiJ = false;}
      if(ApWwdcdnmn == true){ApWwdcdnmn = false;}
      if(SSIblyXlDl == true){SSIblyXlDl = false;}
      if(oUJQtWkzOP == true){oUJQtWkzOP = false;}
      if(KsnPzonmBQ == true){KsnPzonmBQ = false;}
      if(OSSMpxYOsg == true){OSSMpxYOsg = false;}
      if(wBBxTegGBG == true){wBBxTegGBG = false;}
      if(reZWcZdrbw == true){reZWcZdrbw = false;}
      if(JjjlWWCwZx == true){JjjlWWCwZx = false;}
      if(xVFhTJqqwT == true){xVFhTJqqwT = false;}
      if(IhktXiruiQ == true){IhktXiruiQ = false;}
      if(SglwWMQOZx == true){SglwWMQOZx = false;}
      if(cjfEJWZrDT == true){cjfEJWZrDT = false;}
      if(hmwHnbyoOm == true){hmwHnbyoOm = false;}
      if(dGMJePjJKG == true){dGMJePjJKG = false;}
      if(rbQzqXCgkB == true){rbQzqXCgkB = false;}
      if(JAqOhfkdIu == true){JAqOhfkdIu = false;}
      if(NbAmSWXWYs == true){NbAmSWXWYs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOHMVDQHAY
{ 
  void yOCoOuhFbh()
  { 
      bool LqYFqyPgYf = false;
      bool jUyxRMfrWj = false;
      bool MgXDGdPXKA = false;
      bool FzufXbxxlk = false;
      bool EgxBnhtqhh = false;
      bool YMRhmeSUyN = false;
      bool hrVYZkYRYp = false;
      bool PiGlffiWPY = false;
      bool jYobasgNss = false;
      bool IbyXCMKYaD = false;
      bool IbRqSpFfCH = false;
      bool uwFZdJCsxg = false;
      bool DKYfhmjiiS = false;
      bool UKuLPHGyJk = false;
      bool nBLkxMWYts = false;
      bool KQatzyCkJe = false;
      bool FWwilkAsKV = false;
      bool CDjMsCzniU = false;
      bool QKnpHDjBMR = false;
      bool EVndeQEbyM = false;
      string OLwaGzfWHC;
      string eTbHXEHsIQ;
      string tPfLrByEcm;
      string TCtDABMJPI;
      string DoqGHjsqCr;
      string DeNFRzejhE;
      string AasTibYXGV;
      string rxczNEXZEI;
      string HHBkjoonlA;
      string VbaLHbwWXe;
      string KVjgAFBNrN;
      string aFfZwsZIjs;
      string mklFzPWRqk;
      string IABZxlWUkd;
      string nbwXZPwAON;
      string CmmdrYidgk;
      string iiVGFZEFbJ;
      string WEXGFLoOfi;
      string SVCciUNWhY;
      string DrnAuEFoSz;
      if(OLwaGzfWHC == KVjgAFBNrN){LqYFqyPgYf = true;}
      else if(KVjgAFBNrN == OLwaGzfWHC){IbRqSpFfCH = true;}
      if(eTbHXEHsIQ == aFfZwsZIjs){jUyxRMfrWj = true;}
      else if(aFfZwsZIjs == eTbHXEHsIQ){uwFZdJCsxg = true;}
      if(tPfLrByEcm == mklFzPWRqk){MgXDGdPXKA = true;}
      else if(mklFzPWRqk == tPfLrByEcm){DKYfhmjiiS = true;}
      if(TCtDABMJPI == IABZxlWUkd){FzufXbxxlk = true;}
      else if(IABZxlWUkd == TCtDABMJPI){UKuLPHGyJk = true;}
      if(DoqGHjsqCr == nbwXZPwAON){EgxBnhtqhh = true;}
      else if(nbwXZPwAON == DoqGHjsqCr){nBLkxMWYts = true;}
      if(DeNFRzejhE == CmmdrYidgk){YMRhmeSUyN = true;}
      else if(CmmdrYidgk == DeNFRzejhE){KQatzyCkJe = true;}
      if(AasTibYXGV == iiVGFZEFbJ){hrVYZkYRYp = true;}
      else if(iiVGFZEFbJ == AasTibYXGV){FWwilkAsKV = true;}
      if(rxczNEXZEI == WEXGFLoOfi){PiGlffiWPY = true;}
      if(HHBkjoonlA == SVCciUNWhY){jYobasgNss = true;}
      if(VbaLHbwWXe == DrnAuEFoSz){IbyXCMKYaD = true;}
      while(WEXGFLoOfi == rxczNEXZEI){CDjMsCzniU = true;}
      while(SVCciUNWhY == SVCciUNWhY){QKnpHDjBMR = true;}
      while(DrnAuEFoSz == DrnAuEFoSz){EVndeQEbyM = true;}
      if(LqYFqyPgYf == true){LqYFqyPgYf = false;}
      if(jUyxRMfrWj == true){jUyxRMfrWj = false;}
      if(MgXDGdPXKA == true){MgXDGdPXKA = false;}
      if(FzufXbxxlk == true){FzufXbxxlk = false;}
      if(EgxBnhtqhh == true){EgxBnhtqhh = false;}
      if(YMRhmeSUyN == true){YMRhmeSUyN = false;}
      if(hrVYZkYRYp == true){hrVYZkYRYp = false;}
      if(PiGlffiWPY == true){PiGlffiWPY = false;}
      if(jYobasgNss == true){jYobasgNss = false;}
      if(IbyXCMKYaD == true){IbyXCMKYaD = false;}
      if(IbRqSpFfCH == true){IbRqSpFfCH = false;}
      if(uwFZdJCsxg == true){uwFZdJCsxg = false;}
      if(DKYfhmjiiS == true){DKYfhmjiiS = false;}
      if(UKuLPHGyJk == true){UKuLPHGyJk = false;}
      if(nBLkxMWYts == true){nBLkxMWYts = false;}
      if(KQatzyCkJe == true){KQatzyCkJe = false;}
      if(FWwilkAsKV == true){FWwilkAsKV = false;}
      if(CDjMsCzniU == true){CDjMsCzniU = false;}
      if(QKnpHDjBMR == true){QKnpHDjBMR = false;}
      if(EVndeQEbyM == true){EVndeQEbyM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZINYWVTME
{ 
  void XHDZzVxnfm()
  { 
      bool rOntArPSlz = false;
      bool ylqtMhtqhV = false;
      bool krAmQqjiGs = false;
      bool AuMYAPsJSd = false;
      bool ZZQjbhPPJb = false;
      bool dWZqJAOAdI = false;
      bool HfLrzDYStx = false;
      bool njXEuKaPKi = false;
      bool bUZdOcUUPz = false;
      bool BsfJVsOXkY = false;
      bool IxUMmsyVwz = false;
      bool ZyotgmGgdV = false;
      bool hECuuuEOhB = false;
      bool wCekaeAMpV = false;
      bool ezXQYDDkbi = false;
      bool lgtOqDtYQr = false;
      bool ojmuCXSETC = false;
      bool ltpHqhflVq = false;
      bool rSlzOPHPtW = false;
      bool kauygtMcNB = false;
      string XpHAAESTWS;
      string tZLfLQNfqg;
      string sFoeKuLIPD;
      string VJgQBpHiBJ;
      string qswpjNEkpe;
      string cOJEVRAboF;
      string rKESwkstdV;
      string IdehozIzux;
      string paRjZHzbuj;
      string oetuQfodsy;
      string TKGTVzibOV;
      string JBgrPRrTro;
      string kRytfdjjRJ;
      string KeGwdeTxOa;
      string XXNYZmyCey;
      string mUkDMCLMmr;
      string PzJELeujOj;
      string ytFRRNDZUs;
      string egESWpsCia;
      string THKWKYNINu;
      if(XpHAAESTWS == TKGTVzibOV){rOntArPSlz = true;}
      else if(TKGTVzibOV == XpHAAESTWS){IxUMmsyVwz = true;}
      if(tZLfLQNfqg == JBgrPRrTro){ylqtMhtqhV = true;}
      else if(JBgrPRrTro == tZLfLQNfqg){ZyotgmGgdV = true;}
      if(sFoeKuLIPD == kRytfdjjRJ){krAmQqjiGs = true;}
      else if(kRytfdjjRJ == sFoeKuLIPD){hECuuuEOhB = true;}
      if(VJgQBpHiBJ == KeGwdeTxOa){AuMYAPsJSd = true;}
      else if(KeGwdeTxOa == VJgQBpHiBJ){wCekaeAMpV = true;}
      if(qswpjNEkpe == XXNYZmyCey){ZZQjbhPPJb = true;}
      else if(XXNYZmyCey == qswpjNEkpe){ezXQYDDkbi = true;}
      if(cOJEVRAboF == mUkDMCLMmr){dWZqJAOAdI = true;}
      else if(mUkDMCLMmr == cOJEVRAboF){lgtOqDtYQr = true;}
      if(rKESwkstdV == PzJELeujOj){HfLrzDYStx = true;}
      else if(PzJELeujOj == rKESwkstdV){ojmuCXSETC = true;}
      if(IdehozIzux == ytFRRNDZUs){njXEuKaPKi = true;}
      if(paRjZHzbuj == egESWpsCia){bUZdOcUUPz = true;}
      if(oetuQfodsy == THKWKYNINu){BsfJVsOXkY = true;}
      while(ytFRRNDZUs == IdehozIzux){ltpHqhflVq = true;}
      while(egESWpsCia == egESWpsCia){rSlzOPHPtW = true;}
      while(THKWKYNINu == THKWKYNINu){kauygtMcNB = true;}
      if(rOntArPSlz == true){rOntArPSlz = false;}
      if(ylqtMhtqhV == true){ylqtMhtqhV = false;}
      if(krAmQqjiGs == true){krAmQqjiGs = false;}
      if(AuMYAPsJSd == true){AuMYAPsJSd = false;}
      if(ZZQjbhPPJb == true){ZZQjbhPPJb = false;}
      if(dWZqJAOAdI == true){dWZqJAOAdI = false;}
      if(HfLrzDYStx == true){HfLrzDYStx = false;}
      if(njXEuKaPKi == true){njXEuKaPKi = false;}
      if(bUZdOcUUPz == true){bUZdOcUUPz = false;}
      if(BsfJVsOXkY == true){BsfJVsOXkY = false;}
      if(IxUMmsyVwz == true){IxUMmsyVwz = false;}
      if(ZyotgmGgdV == true){ZyotgmGgdV = false;}
      if(hECuuuEOhB == true){hECuuuEOhB = false;}
      if(wCekaeAMpV == true){wCekaeAMpV = false;}
      if(ezXQYDDkbi == true){ezXQYDDkbi = false;}
      if(lgtOqDtYQr == true){lgtOqDtYQr = false;}
      if(ojmuCXSETC == true){ojmuCXSETC = false;}
      if(ltpHqhflVq == true){ltpHqhflVq = false;}
      if(rSlzOPHPtW == true){rSlzOPHPtW = false;}
      if(kauygtMcNB == true){kauygtMcNB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTGRYHLWKR
{ 
  void LTPLeiSRQT()
  { 
      bool UOJlqXqxjz = false;
      bool ixMuocLTZo = false;
      bool kcRRoqCzCK = false;
      bool YgJgyeaamd = false;
      bool mMbPDucgoQ = false;
      bool GfaNxrxrxz = false;
      bool UqtZZBmexK = false;
      bool CkfuBXABOt = false;
      bool NVKlDsFwjF = false;
      bool hhdnJwRCoB = false;
      bool HyjeOVzfLY = false;
      bool rudCkzgIVg = false;
      bool upuqcTGrlF = false;
      bool GxMMmPkfXh = false;
      bool sZkLNlEbDJ = false;
      bool PIfIFQCsCt = false;
      bool OHsGRtiQPU = false;
      bool NBknmVFicp = false;
      bool OenboxQDHV = false;
      bool MrccSlfdsT = false;
      string gbEEtJlwbL;
      string ujyzyXTWgH;
      string LdGAVNZfPB;
      string rZRYetSBjH;
      string ewaAQsSnwc;
      string esaJiCUDif;
      string jFgaSVRYUD;
      string ERlZcPDGic;
      string ukjmVyyIpb;
      string YPSEWYPzgu;
      string asTsXNHAfT;
      string zOUFjyVsFT;
      string WJirdoyhCE;
      string AEYnCCRqOI;
      string qxbVcKuNTX;
      string CVtMYQJbOi;
      string OYyaTuofDh;
      string geewcYhMOT;
      string skNdBdJMOl;
      string rpbetSzACh;
      if(gbEEtJlwbL == asTsXNHAfT){UOJlqXqxjz = true;}
      else if(asTsXNHAfT == gbEEtJlwbL){HyjeOVzfLY = true;}
      if(ujyzyXTWgH == zOUFjyVsFT){ixMuocLTZo = true;}
      else if(zOUFjyVsFT == ujyzyXTWgH){rudCkzgIVg = true;}
      if(LdGAVNZfPB == WJirdoyhCE){kcRRoqCzCK = true;}
      else if(WJirdoyhCE == LdGAVNZfPB){upuqcTGrlF = true;}
      if(rZRYetSBjH == AEYnCCRqOI){YgJgyeaamd = true;}
      else if(AEYnCCRqOI == rZRYetSBjH){GxMMmPkfXh = true;}
      if(ewaAQsSnwc == qxbVcKuNTX){mMbPDucgoQ = true;}
      else if(qxbVcKuNTX == ewaAQsSnwc){sZkLNlEbDJ = true;}
      if(esaJiCUDif == CVtMYQJbOi){GfaNxrxrxz = true;}
      else if(CVtMYQJbOi == esaJiCUDif){PIfIFQCsCt = true;}
      if(jFgaSVRYUD == OYyaTuofDh){UqtZZBmexK = true;}
      else if(OYyaTuofDh == jFgaSVRYUD){OHsGRtiQPU = true;}
      if(ERlZcPDGic == geewcYhMOT){CkfuBXABOt = true;}
      if(ukjmVyyIpb == skNdBdJMOl){NVKlDsFwjF = true;}
      if(YPSEWYPzgu == rpbetSzACh){hhdnJwRCoB = true;}
      while(geewcYhMOT == ERlZcPDGic){NBknmVFicp = true;}
      while(skNdBdJMOl == skNdBdJMOl){OenboxQDHV = true;}
      while(rpbetSzACh == rpbetSzACh){MrccSlfdsT = true;}
      if(UOJlqXqxjz == true){UOJlqXqxjz = false;}
      if(ixMuocLTZo == true){ixMuocLTZo = false;}
      if(kcRRoqCzCK == true){kcRRoqCzCK = false;}
      if(YgJgyeaamd == true){YgJgyeaamd = false;}
      if(mMbPDucgoQ == true){mMbPDucgoQ = false;}
      if(GfaNxrxrxz == true){GfaNxrxrxz = false;}
      if(UqtZZBmexK == true){UqtZZBmexK = false;}
      if(CkfuBXABOt == true){CkfuBXABOt = false;}
      if(NVKlDsFwjF == true){NVKlDsFwjF = false;}
      if(hhdnJwRCoB == true){hhdnJwRCoB = false;}
      if(HyjeOVzfLY == true){HyjeOVzfLY = false;}
      if(rudCkzgIVg == true){rudCkzgIVg = false;}
      if(upuqcTGrlF == true){upuqcTGrlF = false;}
      if(GxMMmPkfXh == true){GxMMmPkfXh = false;}
      if(sZkLNlEbDJ == true){sZkLNlEbDJ = false;}
      if(PIfIFQCsCt == true){PIfIFQCsCt = false;}
      if(OHsGRtiQPU == true){OHsGRtiQPU = false;}
      if(NBknmVFicp == true){NBknmVFicp = false;}
      if(OenboxQDHV == true){OenboxQDHV = false;}
      if(MrccSlfdsT == true){MrccSlfdsT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HGCKCVJVIT
{ 
  void MEdQTGpWBJ()
  { 
      bool lfdqzZyubX = false;
      bool HrHeLtqiEo = false;
      bool rsCRkrSjVd = false;
      bool VdGOEesiVG = false;
      bool luIwfoZbjE = false;
      bool DZkJusdMFH = false;
      bool HOZyBdlrZg = false;
      bool AHNyDxkGkw = false;
      bool SpARZuswTL = false;
      bool AgcOzWVJtC = false;
      bool CgBCDwMmGy = false;
      bool HXbJoQOHXF = false;
      bool kpYNgTdyzf = false;
      bool abLisknxNd = false;
      bool iGpUEbFTZh = false;
      bool INknRMInVi = false;
      bool ROnZWfMrPD = false;
      bool cQttWezDJE = false;
      bool OKXQXNpXQg = false;
      bool bAbdMTSQxX = false;
      string tKmMnAhyQS;
      string MmsCOOfMap;
      string btSaCfDZuj;
      string OCuzOYGQRn;
      string IgirHOWZSr;
      string qymAjAqMJH;
      string wICfDJqsno;
      string HPumgtKaTm;
      string IdGDsQPuON;
      string gtGJqAdDnx;
      string XckdjbDASp;
      string pQrVzRBzml;
      string tweaHNIkug;
      string PGlWPfrcSR;
      string NObYWQCjKY;
      string zeQBCbyKVW;
      string SRFlZidVFS;
      string ZYfUYeTFDq;
      string KXaVgjpjTn;
      string hgGwzuJpzn;
      if(tKmMnAhyQS == XckdjbDASp){lfdqzZyubX = true;}
      else if(XckdjbDASp == tKmMnAhyQS){CgBCDwMmGy = true;}
      if(MmsCOOfMap == pQrVzRBzml){HrHeLtqiEo = true;}
      else if(pQrVzRBzml == MmsCOOfMap){HXbJoQOHXF = true;}
      if(btSaCfDZuj == tweaHNIkug){rsCRkrSjVd = true;}
      else if(tweaHNIkug == btSaCfDZuj){kpYNgTdyzf = true;}
      if(OCuzOYGQRn == PGlWPfrcSR){VdGOEesiVG = true;}
      else if(PGlWPfrcSR == OCuzOYGQRn){abLisknxNd = true;}
      if(IgirHOWZSr == NObYWQCjKY){luIwfoZbjE = true;}
      else if(NObYWQCjKY == IgirHOWZSr){iGpUEbFTZh = true;}
      if(qymAjAqMJH == zeQBCbyKVW){DZkJusdMFH = true;}
      else if(zeQBCbyKVW == qymAjAqMJH){INknRMInVi = true;}
      if(wICfDJqsno == SRFlZidVFS){HOZyBdlrZg = true;}
      else if(SRFlZidVFS == wICfDJqsno){ROnZWfMrPD = true;}
      if(HPumgtKaTm == ZYfUYeTFDq){AHNyDxkGkw = true;}
      if(IdGDsQPuON == KXaVgjpjTn){SpARZuswTL = true;}
      if(gtGJqAdDnx == hgGwzuJpzn){AgcOzWVJtC = true;}
      while(ZYfUYeTFDq == HPumgtKaTm){cQttWezDJE = true;}
      while(KXaVgjpjTn == KXaVgjpjTn){OKXQXNpXQg = true;}
      while(hgGwzuJpzn == hgGwzuJpzn){bAbdMTSQxX = true;}
      if(lfdqzZyubX == true){lfdqzZyubX = false;}
      if(HrHeLtqiEo == true){HrHeLtqiEo = false;}
      if(rsCRkrSjVd == true){rsCRkrSjVd = false;}
      if(VdGOEesiVG == true){VdGOEesiVG = false;}
      if(luIwfoZbjE == true){luIwfoZbjE = false;}
      if(DZkJusdMFH == true){DZkJusdMFH = false;}
      if(HOZyBdlrZg == true){HOZyBdlrZg = false;}
      if(AHNyDxkGkw == true){AHNyDxkGkw = false;}
      if(SpARZuswTL == true){SpARZuswTL = false;}
      if(AgcOzWVJtC == true){AgcOzWVJtC = false;}
      if(CgBCDwMmGy == true){CgBCDwMmGy = false;}
      if(HXbJoQOHXF == true){HXbJoQOHXF = false;}
      if(kpYNgTdyzf == true){kpYNgTdyzf = false;}
      if(abLisknxNd == true){abLisknxNd = false;}
      if(iGpUEbFTZh == true){iGpUEbFTZh = false;}
      if(INknRMInVi == true){INknRMInVi = false;}
      if(ROnZWfMrPD == true){ROnZWfMrPD = false;}
      if(cQttWezDJE == true){cQttWezDJE = false;}
      if(OKXQXNpXQg == true){OKXQXNpXQg = false;}
      if(bAbdMTSQxX == true){bAbdMTSQxX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMXZOUDMVF
{ 
  void DPIInyuwdn()
  { 
      bool xCXiguhQMZ = false;
      bool ktVrkrPdDk = false;
      bool pNbtIZMeps = false;
      bool PNAdfdRwlD = false;
      bool eXIdcLIftJ = false;
      bool UYihriZdaG = false;
      bool hDZSJXtqLG = false;
      bool ZTrzFRFxQx = false;
      bool QfkgXpdRkw = false;
      bool DnVeVbxpUF = false;
      bool QQUmjBgjbZ = false;
      bool dbNdpCSstS = false;
      bool tbGODkxNcd = false;
      bool UOcKfzLxwW = false;
      bool JspKRaarnT = false;
      bool JDwBLoKFjy = false;
      bool ETGyFPzCxp = false;
      bool pUxWJAkuwb = false;
      bool KFYJTQSbzp = false;
      bool oFMySomqFC = false;
      string LzlCXsAXZy;
      string gGtedgngBH;
      string ttlwQZDtmG;
      string hKtkKpDbbt;
      string QlGUjnHeTJ;
      string RcJXNRMply;
      string pFkSQVMIUn;
      string cMFHpHmQLb;
      string RXZdoEBWXs;
      string cNpcDLAnDN;
      string byKfgEXBgF;
      string ewdJgReHdM;
      string TokaKOWbEe;
      string GzMyASNtwj;
      string gAoROgifwk;
      string fsJqslNiVR;
      string huxCyeifIN;
      string EkKseTASMd;
      string fpeSyNoUEO;
      string FeYeCkDmSi;
      if(LzlCXsAXZy == byKfgEXBgF){xCXiguhQMZ = true;}
      else if(byKfgEXBgF == LzlCXsAXZy){QQUmjBgjbZ = true;}
      if(gGtedgngBH == ewdJgReHdM){ktVrkrPdDk = true;}
      else if(ewdJgReHdM == gGtedgngBH){dbNdpCSstS = true;}
      if(ttlwQZDtmG == TokaKOWbEe){pNbtIZMeps = true;}
      else if(TokaKOWbEe == ttlwQZDtmG){tbGODkxNcd = true;}
      if(hKtkKpDbbt == GzMyASNtwj){PNAdfdRwlD = true;}
      else if(GzMyASNtwj == hKtkKpDbbt){UOcKfzLxwW = true;}
      if(QlGUjnHeTJ == gAoROgifwk){eXIdcLIftJ = true;}
      else if(gAoROgifwk == QlGUjnHeTJ){JspKRaarnT = true;}
      if(RcJXNRMply == fsJqslNiVR){UYihriZdaG = true;}
      else if(fsJqslNiVR == RcJXNRMply){JDwBLoKFjy = true;}
      if(pFkSQVMIUn == huxCyeifIN){hDZSJXtqLG = true;}
      else if(huxCyeifIN == pFkSQVMIUn){ETGyFPzCxp = true;}
      if(cMFHpHmQLb == EkKseTASMd){ZTrzFRFxQx = true;}
      if(RXZdoEBWXs == fpeSyNoUEO){QfkgXpdRkw = true;}
      if(cNpcDLAnDN == FeYeCkDmSi){DnVeVbxpUF = true;}
      while(EkKseTASMd == cMFHpHmQLb){pUxWJAkuwb = true;}
      while(fpeSyNoUEO == fpeSyNoUEO){KFYJTQSbzp = true;}
      while(FeYeCkDmSi == FeYeCkDmSi){oFMySomqFC = true;}
      if(xCXiguhQMZ == true){xCXiguhQMZ = false;}
      if(ktVrkrPdDk == true){ktVrkrPdDk = false;}
      if(pNbtIZMeps == true){pNbtIZMeps = false;}
      if(PNAdfdRwlD == true){PNAdfdRwlD = false;}
      if(eXIdcLIftJ == true){eXIdcLIftJ = false;}
      if(UYihriZdaG == true){UYihriZdaG = false;}
      if(hDZSJXtqLG == true){hDZSJXtqLG = false;}
      if(ZTrzFRFxQx == true){ZTrzFRFxQx = false;}
      if(QfkgXpdRkw == true){QfkgXpdRkw = false;}
      if(DnVeVbxpUF == true){DnVeVbxpUF = false;}
      if(QQUmjBgjbZ == true){QQUmjBgjbZ = false;}
      if(dbNdpCSstS == true){dbNdpCSstS = false;}
      if(tbGODkxNcd == true){tbGODkxNcd = false;}
      if(UOcKfzLxwW == true){UOcKfzLxwW = false;}
      if(JspKRaarnT == true){JspKRaarnT = false;}
      if(JDwBLoKFjy == true){JDwBLoKFjy = false;}
      if(ETGyFPzCxp == true){ETGyFPzCxp = false;}
      if(pUxWJAkuwb == true){pUxWJAkuwb = false;}
      if(KFYJTQSbzp == true){KFYJTQSbzp = false;}
      if(oFMySomqFC == true){oFMySomqFC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPNCCHURGS
{ 
  void sqSCAWEHWW()
  { 
      bool rCPVeQIemd = false;
      bool aaSmqsthKF = false;
      bool ZnDLcInHAU = false;
      bool eikUTtBgzd = false;
      bool WkzSwZntSa = false;
      bool hUdaZEyDsV = false;
      bool bBdSzroyTx = false;
      bool rMhgiookPC = false;
      bool TtoZlJEKtP = false;
      bool wxncBUGgTE = false;
      bool jpaVhVlxqk = false;
      bool PNnpBhMEfo = false;
      bool meDDAuYEeO = false;
      bool hHRKSdTTqP = false;
      bool XGSIziIxbT = false;
      bool ICAeQElWUm = false;
      bool xgScCHwcXW = false;
      bool NsNQRfLuDR = false;
      bool lacKFfHmtN = false;
      bool rxyDSpnpGr = false;
      string lHtAcQzwFw;
      string MqsYizRhzZ;
      string xRhTHmGkqA;
      string yQpAPomxJS;
      string DyDEDSTJYC;
      string uXRIqTZZso;
      string KOFExuAsIt;
      string MUXgVyNcQn;
      string TxLnFazhJw;
      string OMEUIoryHH;
      string RaAeoaAkmr;
      string FwJFVMCQzW;
      string wSiLeAPCYg;
      string GPVIVrwgze;
      string ZOuRpSDzzu;
      string lazjLyrnzo;
      string KxLFkpZAic;
      string QVRUxhXRUM;
      string xQDdtePlwW;
      string AHgKTcCofA;
      if(lHtAcQzwFw == RaAeoaAkmr){rCPVeQIemd = true;}
      else if(RaAeoaAkmr == lHtAcQzwFw){jpaVhVlxqk = true;}
      if(MqsYizRhzZ == FwJFVMCQzW){aaSmqsthKF = true;}
      else if(FwJFVMCQzW == MqsYizRhzZ){PNnpBhMEfo = true;}
      if(xRhTHmGkqA == wSiLeAPCYg){ZnDLcInHAU = true;}
      else if(wSiLeAPCYg == xRhTHmGkqA){meDDAuYEeO = true;}
      if(yQpAPomxJS == GPVIVrwgze){eikUTtBgzd = true;}
      else if(GPVIVrwgze == yQpAPomxJS){hHRKSdTTqP = true;}
      if(DyDEDSTJYC == ZOuRpSDzzu){WkzSwZntSa = true;}
      else if(ZOuRpSDzzu == DyDEDSTJYC){XGSIziIxbT = true;}
      if(uXRIqTZZso == lazjLyrnzo){hUdaZEyDsV = true;}
      else if(lazjLyrnzo == uXRIqTZZso){ICAeQElWUm = true;}
      if(KOFExuAsIt == KxLFkpZAic){bBdSzroyTx = true;}
      else if(KxLFkpZAic == KOFExuAsIt){xgScCHwcXW = true;}
      if(MUXgVyNcQn == QVRUxhXRUM){rMhgiookPC = true;}
      if(TxLnFazhJw == xQDdtePlwW){TtoZlJEKtP = true;}
      if(OMEUIoryHH == AHgKTcCofA){wxncBUGgTE = true;}
      while(QVRUxhXRUM == MUXgVyNcQn){NsNQRfLuDR = true;}
      while(xQDdtePlwW == xQDdtePlwW){lacKFfHmtN = true;}
      while(AHgKTcCofA == AHgKTcCofA){rxyDSpnpGr = true;}
      if(rCPVeQIemd == true){rCPVeQIemd = false;}
      if(aaSmqsthKF == true){aaSmqsthKF = false;}
      if(ZnDLcInHAU == true){ZnDLcInHAU = false;}
      if(eikUTtBgzd == true){eikUTtBgzd = false;}
      if(WkzSwZntSa == true){WkzSwZntSa = false;}
      if(hUdaZEyDsV == true){hUdaZEyDsV = false;}
      if(bBdSzroyTx == true){bBdSzroyTx = false;}
      if(rMhgiookPC == true){rMhgiookPC = false;}
      if(TtoZlJEKtP == true){TtoZlJEKtP = false;}
      if(wxncBUGgTE == true){wxncBUGgTE = false;}
      if(jpaVhVlxqk == true){jpaVhVlxqk = false;}
      if(PNnpBhMEfo == true){PNnpBhMEfo = false;}
      if(meDDAuYEeO == true){meDDAuYEeO = false;}
      if(hHRKSdTTqP == true){hHRKSdTTqP = false;}
      if(XGSIziIxbT == true){XGSIziIxbT = false;}
      if(ICAeQElWUm == true){ICAeQElWUm = false;}
      if(xgScCHwcXW == true){xgScCHwcXW = false;}
      if(NsNQRfLuDR == true){NsNQRfLuDR = false;}
      if(lacKFfHmtN == true){lacKFfHmtN = false;}
      if(rxyDSpnpGr == true){rxyDSpnpGr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFYKNAFIAO
{ 
  void AURdGlmcVe()
  { 
      bool EEqeXqnbeK = false;
      bool xALNMlmfAw = false;
      bool pwDObQUuRx = false;
      bool hQZsQQQhlZ = false;
      bool MLpkAhPlDL = false;
      bool UlaQNHBbCH = false;
      bool VrJgbfaRxu = false;
      bool UEsZidGROs = false;
      bool AiqGcwpIeI = false;
      bool PoeeETCJJT = false;
      bool HxnIpPrBhj = false;
      bool AiMJGlBDDf = false;
      bool pRloffZOUP = false;
      bool bwItkCuiPN = false;
      bool DnauHgbVYR = false;
      bool SyGcdpLybK = false;
      bool pdfSIEaSXD = false;
      bool qRnobBpqgy = false;
      bool DDpDwcpeQu = false;
      bool qwGFXZHImD = false;
      string SxRbzdeXUR;
      string nFeyCldAHY;
      string ufXfOEeREQ;
      string sGeXcSzPVp;
      string dfCVCBtIJw;
      string ThhpNlYlNu;
      string yMTEXhZHUj;
      string mNdRtOcCcN;
      string KWIHxLYnJp;
      string sMCaqQMyxU;
      string almZIFDPuz;
      string IWIzjbELHM;
      string JkxepZLDZd;
      string CeFImXjizq;
      string HIsKgVEDpP;
      string MAqjLonIih;
      string tApRxdRAML;
      string rUMPFArmxU;
      string VHMJRBnUwx;
      string iaAQxHRaMD;
      if(SxRbzdeXUR == almZIFDPuz){EEqeXqnbeK = true;}
      else if(almZIFDPuz == SxRbzdeXUR){HxnIpPrBhj = true;}
      if(nFeyCldAHY == IWIzjbELHM){xALNMlmfAw = true;}
      else if(IWIzjbELHM == nFeyCldAHY){AiMJGlBDDf = true;}
      if(ufXfOEeREQ == JkxepZLDZd){pwDObQUuRx = true;}
      else if(JkxepZLDZd == ufXfOEeREQ){pRloffZOUP = true;}
      if(sGeXcSzPVp == CeFImXjizq){hQZsQQQhlZ = true;}
      else if(CeFImXjizq == sGeXcSzPVp){bwItkCuiPN = true;}
      if(dfCVCBtIJw == HIsKgVEDpP){MLpkAhPlDL = true;}
      else if(HIsKgVEDpP == dfCVCBtIJw){DnauHgbVYR = true;}
      if(ThhpNlYlNu == MAqjLonIih){UlaQNHBbCH = true;}
      else if(MAqjLonIih == ThhpNlYlNu){SyGcdpLybK = true;}
      if(yMTEXhZHUj == tApRxdRAML){VrJgbfaRxu = true;}
      else if(tApRxdRAML == yMTEXhZHUj){pdfSIEaSXD = true;}
      if(mNdRtOcCcN == rUMPFArmxU){UEsZidGROs = true;}
      if(KWIHxLYnJp == VHMJRBnUwx){AiqGcwpIeI = true;}
      if(sMCaqQMyxU == iaAQxHRaMD){PoeeETCJJT = true;}
      while(rUMPFArmxU == mNdRtOcCcN){qRnobBpqgy = true;}
      while(VHMJRBnUwx == VHMJRBnUwx){DDpDwcpeQu = true;}
      while(iaAQxHRaMD == iaAQxHRaMD){qwGFXZHImD = true;}
      if(EEqeXqnbeK == true){EEqeXqnbeK = false;}
      if(xALNMlmfAw == true){xALNMlmfAw = false;}
      if(pwDObQUuRx == true){pwDObQUuRx = false;}
      if(hQZsQQQhlZ == true){hQZsQQQhlZ = false;}
      if(MLpkAhPlDL == true){MLpkAhPlDL = false;}
      if(UlaQNHBbCH == true){UlaQNHBbCH = false;}
      if(VrJgbfaRxu == true){VrJgbfaRxu = false;}
      if(UEsZidGROs == true){UEsZidGROs = false;}
      if(AiqGcwpIeI == true){AiqGcwpIeI = false;}
      if(PoeeETCJJT == true){PoeeETCJJT = false;}
      if(HxnIpPrBhj == true){HxnIpPrBhj = false;}
      if(AiMJGlBDDf == true){AiMJGlBDDf = false;}
      if(pRloffZOUP == true){pRloffZOUP = false;}
      if(bwItkCuiPN == true){bwItkCuiPN = false;}
      if(DnauHgbVYR == true){DnauHgbVYR = false;}
      if(SyGcdpLybK == true){SyGcdpLybK = false;}
      if(pdfSIEaSXD == true){pdfSIEaSXD = false;}
      if(qRnobBpqgy == true){qRnobBpqgy = false;}
      if(DDpDwcpeQu == true){DDpDwcpeQu = false;}
      if(qwGFXZHImD == true){qwGFXZHImD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYRKBPRYWJ
{ 
  void bUskOTpcmc()
  { 
      bool AYSkNEBVgp = false;
      bool RgCPdxgqVV = false;
      bool hIuPzsmjkH = false;
      bool DjymrCRlLj = false;
      bool BrwRXShrmY = false;
      bool KNzOrrcClT = false;
      bool QRjZmhhOWa = false;
      bool fuekUoLdrf = false;
      bool LuwMwpkjtz = false;
      bool ZOAqTiIWep = false;
      bool jSUMrPhNtD = false;
      bool fzJGIVUWcx = false;
      bool wyUWAQumRk = false;
      bool foyCusZjTg = false;
      bool IWoqSZEtiy = false;
      bool OksgskyxLa = false;
      bool UtwJWqAHKP = false;
      bool ujDwoZJcEZ = false;
      bool MADTVtuRJJ = false;
      bool tcYrLNafTb = false;
      string JWhiQacezq;
      string BuZbqXiHoh;
      string AlgosVuKdo;
      string iWfrhaghxC;
      string fXBoGXrtEz;
      string rXUBFXpsot;
      string fSAJIeOgtQ;
      string qBKmCbjrhV;
      string cAFdwKCemK;
      string jmrCVMXqfa;
      string ILAnIqNgzc;
      string nxKTReMVNy;
      string cjtjfDIIQo;
      string ErLGNRAQVF;
      string xUeJVlbYjq;
      string ABdhyXRPIE;
      string hEQKYulDFz;
      string duAIAHFjNs;
      string ajXYoCNdIp;
      string AjHQWrEUkZ;
      if(JWhiQacezq == ILAnIqNgzc){AYSkNEBVgp = true;}
      else if(ILAnIqNgzc == JWhiQacezq){jSUMrPhNtD = true;}
      if(BuZbqXiHoh == nxKTReMVNy){RgCPdxgqVV = true;}
      else if(nxKTReMVNy == BuZbqXiHoh){fzJGIVUWcx = true;}
      if(AlgosVuKdo == cjtjfDIIQo){hIuPzsmjkH = true;}
      else if(cjtjfDIIQo == AlgosVuKdo){wyUWAQumRk = true;}
      if(iWfrhaghxC == ErLGNRAQVF){DjymrCRlLj = true;}
      else if(ErLGNRAQVF == iWfrhaghxC){foyCusZjTg = true;}
      if(fXBoGXrtEz == xUeJVlbYjq){BrwRXShrmY = true;}
      else if(xUeJVlbYjq == fXBoGXrtEz){IWoqSZEtiy = true;}
      if(rXUBFXpsot == ABdhyXRPIE){KNzOrrcClT = true;}
      else if(ABdhyXRPIE == rXUBFXpsot){OksgskyxLa = true;}
      if(fSAJIeOgtQ == hEQKYulDFz){QRjZmhhOWa = true;}
      else if(hEQKYulDFz == fSAJIeOgtQ){UtwJWqAHKP = true;}
      if(qBKmCbjrhV == duAIAHFjNs){fuekUoLdrf = true;}
      if(cAFdwKCemK == ajXYoCNdIp){LuwMwpkjtz = true;}
      if(jmrCVMXqfa == AjHQWrEUkZ){ZOAqTiIWep = true;}
      while(duAIAHFjNs == qBKmCbjrhV){ujDwoZJcEZ = true;}
      while(ajXYoCNdIp == ajXYoCNdIp){MADTVtuRJJ = true;}
      while(AjHQWrEUkZ == AjHQWrEUkZ){tcYrLNafTb = true;}
      if(AYSkNEBVgp == true){AYSkNEBVgp = false;}
      if(RgCPdxgqVV == true){RgCPdxgqVV = false;}
      if(hIuPzsmjkH == true){hIuPzsmjkH = false;}
      if(DjymrCRlLj == true){DjymrCRlLj = false;}
      if(BrwRXShrmY == true){BrwRXShrmY = false;}
      if(KNzOrrcClT == true){KNzOrrcClT = false;}
      if(QRjZmhhOWa == true){QRjZmhhOWa = false;}
      if(fuekUoLdrf == true){fuekUoLdrf = false;}
      if(LuwMwpkjtz == true){LuwMwpkjtz = false;}
      if(ZOAqTiIWep == true){ZOAqTiIWep = false;}
      if(jSUMrPhNtD == true){jSUMrPhNtD = false;}
      if(fzJGIVUWcx == true){fzJGIVUWcx = false;}
      if(wyUWAQumRk == true){wyUWAQumRk = false;}
      if(foyCusZjTg == true){foyCusZjTg = false;}
      if(IWoqSZEtiy == true){IWoqSZEtiy = false;}
      if(OksgskyxLa == true){OksgskyxLa = false;}
      if(UtwJWqAHKP == true){UtwJWqAHKP = false;}
      if(ujDwoZJcEZ == true){ujDwoZJcEZ = false;}
      if(MADTVtuRJJ == true){MADTVtuRJJ = false;}
      if(tcYrLNafTb == true){tcYrLNafTb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTHDNZHTKO
{ 
  void WcYVqhACgP()
  { 
      bool wJfyHHtjuK = false;
      bool dVXScYuKuL = false;
      bool JaSIGzgqAA = false;
      bool kDdOZkwhWh = false;
      bool CgHSKAaqCY = false;
      bool lEHZKVpWrH = false;
      bool aDitZZqJrq = false;
      bool bNmNJbTzxG = false;
      bool YonbNfuEEE = false;
      bool tZpOHzxMsk = false;
      bool IQyKwYQtQh = false;
      bool BqZlhkOHgs = false;
      bool dmFnwCXXGJ = false;
      bool dGGMxIqdfn = false;
      bool OBnVCDADfV = false;
      bool jpezGVLJOs = false;
      bool BrmGDujMoZ = false;
      bool tkbrdcyikr = false;
      bool CTrjYnaGFa = false;
      bool wgOllWNgSH = false;
      string jhjcGSrlbo;
      string kXPhlMjODx;
      string tYSyyVYMlU;
      string ACNphCYeuF;
      string UpoNxqTiXL;
      string NDXAZLPkdj;
      string teAGoiJZzj;
      string nFSxcDiEBH;
      string BonaHweMPW;
      string lnAKLophXN;
      string gtinXHkaXV;
      string bKiWiEqZzs;
      string DwJcyzFIkm;
      string NBgmZGFADA;
      string KEottaEcaG;
      string yQidKkkGpX;
      string BcokIaduxb;
      string zqVzizHPhW;
      string tcgeowRCcn;
      string VzKeyhODkT;
      if(jhjcGSrlbo == gtinXHkaXV){wJfyHHtjuK = true;}
      else if(gtinXHkaXV == jhjcGSrlbo){IQyKwYQtQh = true;}
      if(kXPhlMjODx == bKiWiEqZzs){dVXScYuKuL = true;}
      else if(bKiWiEqZzs == kXPhlMjODx){BqZlhkOHgs = true;}
      if(tYSyyVYMlU == DwJcyzFIkm){JaSIGzgqAA = true;}
      else if(DwJcyzFIkm == tYSyyVYMlU){dmFnwCXXGJ = true;}
      if(ACNphCYeuF == NBgmZGFADA){kDdOZkwhWh = true;}
      else if(NBgmZGFADA == ACNphCYeuF){dGGMxIqdfn = true;}
      if(UpoNxqTiXL == KEottaEcaG){CgHSKAaqCY = true;}
      else if(KEottaEcaG == UpoNxqTiXL){OBnVCDADfV = true;}
      if(NDXAZLPkdj == yQidKkkGpX){lEHZKVpWrH = true;}
      else if(yQidKkkGpX == NDXAZLPkdj){jpezGVLJOs = true;}
      if(teAGoiJZzj == BcokIaduxb){aDitZZqJrq = true;}
      else if(BcokIaduxb == teAGoiJZzj){BrmGDujMoZ = true;}
      if(nFSxcDiEBH == zqVzizHPhW){bNmNJbTzxG = true;}
      if(BonaHweMPW == tcgeowRCcn){YonbNfuEEE = true;}
      if(lnAKLophXN == VzKeyhODkT){tZpOHzxMsk = true;}
      while(zqVzizHPhW == nFSxcDiEBH){tkbrdcyikr = true;}
      while(tcgeowRCcn == tcgeowRCcn){CTrjYnaGFa = true;}
      while(VzKeyhODkT == VzKeyhODkT){wgOllWNgSH = true;}
      if(wJfyHHtjuK == true){wJfyHHtjuK = false;}
      if(dVXScYuKuL == true){dVXScYuKuL = false;}
      if(JaSIGzgqAA == true){JaSIGzgqAA = false;}
      if(kDdOZkwhWh == true){kDdOZkwhWh = false;}
      if(CgHSKAaqCY == true){CgHSKAaqCY = false;}
      if(lEHZKVpWrH == true){lEHZKVpWrH = false;}
      if(aDitZZqJrq == true){aDitZZqJrq = false;}
      if(bNmNJbTzxG == true){bNmNJbTzxG = false;}
      if(YonbNfuEEE == true){YonbNfuEEE = false;}
      if(tZpOHzxMsk == true){tZpOHzxMsk = false;}
      if(IQyKwYQtQh == true){IQyKwYQtQh = false;}
      if(BqZlhkOHgs == true){BqZlhkOHgs = false;}
      if(dmFnwCXXGJ == true){dmFnwCXXGJ = false;}
      if(dGGMxIqdfn == true){dGGMxIqdfn = false;}
      if(OBnVCDADfV == true){OBnVCDADfV = false;}
      if(jpezGVLJOs == true){jpezGVLJOs = false;}
      if(BrmGDujMoZ == true){BrmGDujMoZ = false;}
      if(tkbrdcyikr == true){tkbrdcyikr = false;}
      if(CTrjYnaGFa == true){CTrjYnaGFa = false;}
      if(wgOllWNgSH == true){wgOllWNgSH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBBBUAHKOP
{ 
  void PTftyQRxAt()
  { 
      bool GblZjXBPBk = false;
      bool LsqZDDBMDu = false;
      bool NzxlDYERJN = false;
      bool LkiZwEcIBM = false;
      bool KOZQoCabNw = false;
      bool FohLIGeAVL = false;
      bool TjFmYaJQcy = false;
      bool asKpkyZgwA = false;
      bool ybDMHWCWRo = false;
      bool ZclprZIlqO = false;
      bool rJyPVMeqaJ = false;
      bool gyDVNqfrfC = false;
      bool XlzmYyGUxK = false;
      bool pmohHndnqu = false;
      bool qLuHHbYQbB = false;
      bool tPGnqGKLqX = false;
      bool GKsQTtIVNZ = false;
      bool NrBkKLpqew = false;
      bool YorwPZgApB = false;
      bool cSwTngRenN = false;
      string GgPqeaYDIm;
      string eVLkJbIMEN;
      string REWAKfaxXJ;
      string nFBnNRqbBV;
      string mAzllyMWFd;
      string lCtaVBKOgy;
      string zaeyzYUXXr;
      string kgKiZRFkNL;
      string TEqtWkLZSL;
      string HbtDVMUBlM;
      string cnzNrFrLBD;
      string wZAVduijbO;
      string NuFLkImHMN;
      string wDyBieEdBR;
      string rAYOOgbYYa;
      string ckYWzhimcj;
      string RkymHrazlz;
      string pFiJVNVpwD;
      string gOiljLeaBA;
      string uRBRAHBkHW;
      if(GgPqeaYDIm == cnzNrFrLBD){GblZjXBPBk = true;}
      else if(cnzNrFrLBD == GgPqeaYDIm){rJyPVMeqaJ = true;}
      if(eVLkJbIMEN == wZAVduijbO){LsqZDDBMDu = true;}
      else if(wZAVduijbO == eVLkJbIMEN){gyDVNqfrfC = true;}
      if(REWAKfaxXJ == NuFLkImHMN){NzxlDYERJN = true;}
      else if(NuFLkImHMN == REWAKfaxXJ){XlzmYyGUxK = true;}
      if(nFBnNRqbBV == wDyBieEdBR){LkiZwEcIBM = true;}
      else if(wDyBieEdBR == nFBnNRqbBV){pmohHndnqu = true;}
      if(mAzllyMWFd == rAYOOgbYYa){KOZQoCabNw = true;}
      else if(rAYOOgbYYa == mAzllyMWFd){qLuHHbYQbB = true;}
      if(lCtaVBKOgy == ckYWzhimcj){FohLIGeAVL = true;}
      else if(ckYWzhimcj == lCtaVBKOgy){tPGnqGKLqX = true;}
      if(zaeyzYUXXr == RkymHrazlz){TjFmYaJQcy = true;}
      else if(RkymHrazlz == zaeyzYUXXr){GKsQTtIVNZ = true;}
      if(kgKiZRFkNL == pFiJVNVpwD){asKpkyZgwA = true;}
      if(TEqtWkLZSL == gOiljLeaBA){ybDMHWCWRo = true;}
      if(HbtDVMUBlM == uRBRAHBkHW){ZclprZIlqO = true;}
      while(pFiJVNVpwD == kgKiZRFkNL){NrBkKLpqew = true;}
      while(gOiljLeaBA == gOiljLeaBA){YorwPZgApB = true;}
      while(uRBRAHBkHW == uRBRAHBkHW){cSwTngRenN = true;}
      if(GblZjXBPBk == true){GblZjXBPBk = false;}
      if(LsqZDDBMDu == true){LsqZDDBMDu = false;}
      if(NzxlDYERJN == true){NzxlDYERJN = false;}
      if(LkiZwEcIBM == true){LkiZwEcIBM = false;}
      if(KOZQoCabNw == true){KOZQoCabNw = false;}
      if(FohLIGeAVL == true){FohLIGeAVL = false;}
      if(TjFmYaJQcy == true){TjFmYaJQcy = false;}
      if(asKpkyZgwA == true){asKpkyZgwA = false;}
      if(ybDMHWCWRo == true){ybDMHWCWRo = false;}
      if(ZclprZIlqO == true){ZclprZIlqO = false;}
      if(rJyPVMeqaJ == true){rJyPVMeqaJ = false;}
      if(gyDVNqfrfC == true){gyDVNqfrfC = false;}
      if(XlzmYyGUxK == true){XlzmYyGUxK = false;}
      if(pmohHndnqu == true){pmohHndnqu = false;}
      if(qLuHHbYQbB == true){qLuHHbYQbB = false;}
      if(tPGnqGKLqX == true){tPGnqGKLqX = false;}
      if(GKsQTtIVNZ == true){GKsQTtIVNZ = false;}
      if(NrBkKLpqew == true){NrBkKLpqew = false;}
      if(YorwPZgApB == true){YorwPZgApB = false;}
      if(cSwTngRenN == true){cSwTngRenN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNBVMIBLVH
{ 
  void BSKrhelYRB()
  { 
      bool SZQzNqFgUt = false;
      bool AflBmwyXNI = false;
      bool GpXMxbaSpL = false;
      bool zQPygqrTNN = false;
      bool bWdisEhWZR = false;
      bool YdsigcCEBl = false;
      bool QlqJtjPnTu = false;
      bool EdJzfjLnSr = false;
      bool sEsXmVWgQE = false;
      bool omRaxofUoJ = false;
      bool otCdNtTsCx = false;
      bool QNkIrMsSVY = false;
      bool MiWPGQMhCp = false;
      bool EpzJDzBOKs = false;
      bool BcdSmaCIij = false;
      bool wMzPxGWmXw = false;
      bool hkqLsaObFr = false;
      bool KeIcXiEDbe = false;
      bool ODzRtqqiMw = false;
      bool bOqOKPlRZM = false;
      string mMHJRxPYCD;
      string pmfniyuncf;
      string AloIsJDGKY;
      string UEFAAYBPws;
      string XymKjDIyUt;
      string SLTUKAXzQH;
      string tJOdhlhfmK;
      string wfqjICzeXo;
      string BEkPGJjkpA;
      string BCyozOiJby;
      string VcLKylTjLI;
      string AraaGoYyXX;
      string CxolIsgCkt;
      string SoDZTXsZRT;
      string oAYhzIbXhJ;
      string okkDuYmYBE;
      string FRyRpKoBHh;
      string wyfEiBXHmA;
      string RITaEgEzdt;
      string kTXNOWBGrn;
      if(mMHJRxPYCD == VcLKylTjLI){SZQzNqFgUt = true;}
      else if(VcLKylTjLI == mMHJRxPYCD){otCdNtTsCx = true;}
      if(pmfniyuncf == AraaGoYyXX){AflBmwyXNI = true;}
      else if(AraaGoYyXX == pmfniyuncf){QNkIrMsSVY = true;}
      if(AloIsJDGKY == CxolIsgCkt){GpXMxbaSpL = true;}
      else if(CxolIsgCkt == AloIsJDGKY){MiWPGQMhCp = true;}
      if(UEFAAYBPws == SoDZTXsZRT){zQPygqrTNN = true;}
      else if(SoDZTXsZRT == UEFAAYBPws){EpzJDzBOKs = true;}
      if(XymKjDIyUt == oAYhzIbXhJ){bWdisEhWZR = true;}
      else if(oAYhzIbXhJ == XymKjDIyUt){BcdSmaCIij = true;}
      if(SLTUKAXzQH == okkDuYmYBE){YdsigcCEBl = true;}
      else if(okkDuYmYBE == SLTUKAXzQH){wMzPxGWmXw = true;}
      if(tJOdhlhfmK == FRyRpKoBHh){QlqJtjPnTu = true;}
      else if(FRyRpKoBHh == tJOdhlhfmK){hkqLsaObFr = true;}
      if(wfqjICzeXo == wyfEiBXHmA){EdJzfjLnSr = true;}
      if(BEkPGJjkpA == RITaEgEzdt){sEsXmVWgQE = true;}
      if(BCyozOiJby == kTXNOWBGrn){omRaxofUoJ = true;}
      while(wyfEiBXHmA == wfqjICzeXo){KeIcXiEDbe = true;}
      while(RITaEgEzdt == RITaEgEzdt){ODzRtqqiMw = true;}
      while(kTXNOWBGrn == kTXNOWBGrn){bOqOKPlRZM = true;}
      if(SZQzNqFgUt == true){SZQzNqFgUt = false;}
      if(AflBmwyXNI == true){AflBmwyXNI = false;}
      if(GpXMxbaSpL == true){GpXMxbaSpL = false;}
      if(zQPygqrTNN == true){zQPygqrTNN = false;}
      if(bWdisEhWZR == true){bWdisEhWZR = false;}
      if(YdsigcCEBl == true){YdsigcCEBl = false;}
      if(QlqJtjPnTu == true){QlqJtjPnTu = false;}
      if(EdJzfjLnSr == true){EdJzfjLnSr = false;}
      if(sEsXmVWgQE == true){sEsXmVWgQE = false;}
      if(omRaxofUoJ == true){omRaxofUoJ = false;}
      if(otCdNtTsCx == true){otCdNtTsCx = false;}
      if(QNkIrMsSVY == true){QNkIrMsSVY = false;}
      if(MiWPGQMhCp == true){MiWPGQMhCp = false;}
      if(EpzJDzBOKs == true){EpzJDzBOKs = false;}
      if(BcdSmaCIij == true){BcdSmaCIij = false;}
      if(wMzPxGWmXw == true){wMzPxGWmXw = false;}
      if(hkqLsaObFr == true){hkqLsaObFr = false;}
      if(KeIcXiEDbe == true){KeIcXiEDbe = false;}
      if(ODzRtqqiMw == true){ODzRtqqiMw = false;}
      if(bOqOKPlRZM == true){bOqOKPlRZM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTQKEJQUXF
{ 
  void rdjkYOOEOd()
  { 
      bool pYtcKCxuPE = false;
      bool CREauwfjQX = false;
      bool aAGXSnJjOy = false;
      bool dbZLDSSdfN = false;
      bool HfYucQBgVs = false;
      bool VdSVfpRVJV = false;
      bool sMgQaarsXb = false;
      bool cCDCPuaLuB = false;
      bool lcOUcAIDfM = false;
      bool AxTKUuyIUB = false;
      bool YIIsPTZPGj = false;
      bool PGaIiQyLnZ = false;
      bool SnNKafhshT = false;
      bool wRqscdTUFI = false;
      bool ZswuxtVLaE = false;
      bool wmUtijuxRi = false;
      bool kghlmxPheF = false;
      bool wcGezYqRNg = false;
      bool KWRcXIxxJr = false;
      bool iVDVXsLKHA = false;
      string dqZklweDkf;
      string FfgQjWyIKn;
      string bRfuyRsMiH;
      string YMNnAkNlVh;
      string iWjPVKUPqT;
      string jKAZlMLdmT;
      string DRTdGsRrPy;
      string ILlbEFhPZm;
      string xdVPXOMnCn;
      string ZjzBeRCGJc;
      string rbzrLXXXVf;
      string duDzWYwEFr;
      string fdpbXXMkwm;
      string DbGwtUdcDA;
      string pnSWJefzdF;
      string VyARwOlWUm;
      string KmahcCoGEB;
      string uSAEBqLTSs;
      string rNGqQFaoAf;
      string iGIQpCNjsG;
      if(dqZklweDkf == rbzrLXXXVf){pYtcKCxuPE = true;}
      else if(rbzrLXXXVf == dqZklweDkf){YIIsPTZPGj = true;}
      if(FfgQjWyIKn == duDzWYwEFr){CREauwfjQX = true;}
      else if(duDzWYwEFr == FfgQjWyIKn){PGaIiQyLnZ = true;}
      if(bRfuyRsMiH == fdpbXXMkwm){aAGXSnJjOy = true;}
      else if(fdpbXXMkwm == bRfuyRsMiH){SnNKafhshT = true;}
      if(YMNnAkNlVh == DbGwtUdcDA){dbZLDSSdfN = true;}
      else if(DbGwtUdcDA == YMNnAkNlVh){wRqscdTUFI = true;}
      if(iWjPVKUPqT == pnSWJefzdF){HfYucQBgVs = true;}
      else if(pnSWJefzdF == iWjPVKUPqT){ZswuxtVLaE = true;}
      if(jKAZlMLdmT == VyARwOlWUm){VdSVfpRVJV = true;}
      else if(VyARwOlWUm == jKAZlMLdmT){wmUtijuxRi = true;}
      if(DRTdGsRrPy == KmahcCoGEB){sMgQaarsXb = true;}
      else if(KmahcCoGEB == DRTdGsRrPy){kghlmxPheF = true;}
      if(ILlbEFhPZm == uSAEBqLTSs){cCDCPuaLuB = true;}
      if(xdVPXOMnCn == rNGqQFaoAf){lcOUcAIDfM = true;}
      if(ZjzBeRCGJc == iGIQpCNjsG){AxTKUuyIUB = true;}
      while(uSAEBqLTSs == ILlbEFhPZm){wcGezYqRNg = true;}
      while(rNGqQFaoAf == rNGqQFaoAf){KWRcXIxxJr = true;}
      while(iGIQpCNjsG == iGIQpCNjsG){iVDVXsLKHA = true;}
      if(pYtcKCxuPE == true){pYtcKCxuPE = false;}
      if(CREauwfjQX == true){CREauwfjQX = false;}
      if(aAGXSnJjOy == true){aAGXSnJjOy = false;}
      if(dbZLDSSdfN == true){dbZLDSSdfN = false;}
      if(HfYucQBgVs == true){HfYucQBgVs = false;}
      if(VdSVfpRVJV == true){VdSVfpRVJV = false;}
      if(sMgQaarsXb == true){sMgQaarsXb = false;}
      if(cCDCPuaLuB == true){cCDCPuaLuB = false;}
      if(lcOUcAIDfM == true){lcOUcAIDfM = false;}
      if(AxTKUuyIUB == true){AxTKUuyIUB = false;}
      if(YIIsPTZPGj == true){YIIsPTZPGj = false;}
      if(PGaIiQyLnZ == true){PGaIiQyLnZ = false;}
      if(SnNKafhshT == true){SnNKafhshT = false;}
      if(wRqscdTUFI == true){wRqscdTUFI = false;}
      if(ZswuxtVLaE == true){ZswuxtVLaE = false;}
      if(wmUtijuxRi == true){wmUtijuxRi = false;}
      if(kghlmxPheF == true){kghlmxPheF = false;}
      if(wcGezYqRNg == true){wcGezYqRNg = false;}
      if(KWRcXIxxJr == true){KWRcXIxxJr = false;}
      if(iVDVXsLKHA == true){iVDVXsLKHA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPKAWZQPVR
{ 
  void HDjsqZyOnL()
  { 
      bool uInzpZHuBm = false;
      bool DXVoSLeLiN = false;
      bool BKVYBGItBh = false;
      bool tuXXUAwjWZ = false;
      bool DbFFZsuTdI = false;
      bool pbqrkkmPyj = false;
      bool QNsTsHzyTR = false;
      bool PtnJJYFPyI = false;
      bool KnPsrSEfmj = false;
      bool NglmJphlMR = false;
      bool txzMsumhhL = false;
      bool fXQpZbxAbZ = false;
      bool DSKjEhIBzT = false;
      bool qSCfNMoDzw = false;
      bool eWybEpPwNg = false;
      bool shKlOblPHK = false;
      bool llhOUMUjbM = false;
      bool msAeugTifO = false;
      bool SMmSZIIPRl = false;
      bool aYuoJsoiHq = false;
      string mTCzdNaWUL;
      string jsEZshnXPM;
      string sekyiPsyXp;
      string WaaegYCNSE;
      string yQjgWYktCo;
      string zVMoNIhDQO;
      string UbzenIRZsT;
      string fZFLNctEbJ;
      string dywhpBOkQX;
      string pyxDiWQFrO;
      string GKBhIYQBak;
      string NdbGkVeQnm;
      string tgJUcgbBbq;
      string LoLNDSxNYR;
      string jMKeKMWqRN;
      string qzRETZBfEb;
      string wOZjZYROCS;
      string XRqWDgVdJP;
      string JkjNALWGsd;
      string QRIxUUmaFl;
      if(mTCzdNaWUL == GKBhIYQBak){uInzpZHuBm = true;}
      else if(GKBhIYQBak == mTCzdNaWUL){txzMsumhhL = true;}
      if(jsEZshnXPM == NdbGkVeQnm){DXVoSLeLiN = true;}
      else if(NdbGkVeQnm == jsEZshnXPM){fXQpZbxAbZ = true;}
      if(sekyiPsyXp == tgJUcgbBbq){BKVYBGItBh = true;}
      else if(tgJUcgbBbq == sekyiPsyXp){DSKjEhIBzT = true;}
      if(WaaegYCNSE == LoLNDSxNYR){tuXXUAwjWZ = true;}
      else if(LoLNDSxNYR == WaaegYCNSE){qSCfNMoDzw = true;}
      if(yQjgWYktCo == jMKeKMWqRN){DbFFZsuTdI = true;}
      else if(jMKeKMWqRN == yQjgWYktCo){eWybEpPwNg = true;}
      if(zVMoNIhDQO == qzRETZBfEb){pbqrkkmPyj = true;}
      else if(qzRETZBfEb == zVMoNIhDQO){shKlOblPHK = true;}
      if(UbzenIRZsT == wOZjZYROCS){QNsTsHzyTR = true;}
      else if(wOZjZYROCS == UbzenIRZsT){llhOUMUjbM = true;}
      if(fZFLNctEbJ == XRqWDgVdJP){PtnJJYFPyI = true;}
      if(dywhpBOkQX == JkjNALWGsd){KnPsrSEfmj = true;}
      if(pyxDiWQFrO == QRIxUUmaFl){NglmJphlMR = true;}
      while(XRqWDgVdJP == fZFLNctEbJ){msAeugTifO = true;}
      while(JkjNALWGsd == JkjNALWGsd){SMmSZIIPRl = true;}
      while(QRIxUUmaFl == QRIxUUmaFl){aYuoJsoiHq = true;}
      if(uInzpZHuBm == true){uInzpZHuBm = false;}
      if(DXVoSLeLiN == true){DXVoSLeLiN = false;}
      if(BKVYBGItBh == true){BKVYBGItBh = false;}
      if(tuXXUAwjWZ == true){tuXXUAwjWZ = false;}
      if(DbFFZsuTdI == true){DbFFZsuTdI = false;}
      if(pbqrkkmPyj == true){pbqrkkmPyj = false;}
      if(QNsTsHzyTR == true){QNsTsHzyTR = false;}
      if(PtnJJYFPyI == true){PtnJJYFPyI = false;}
      if(KnPsrSEfmj == true){KnPsrSEfmj = false;}
      if(NglmJphlMR == true){NglmJphlMR = false;}
      if(txzMsumhhL == true){txzMsumhhL = false;}
      if(fXQpZbxAbZ == true){fXQpZbxAbZ = false;}
      if(DSKjEhIBzT == true){DSKjEhIBzT = false;}
      if(qSCfNMoDzw == true){qSCfNMoDzw = false;}
      if(eWybEpPwNg == true){eWybEpPwNg = false;}
      if(shKlOblPHK == true){shKlOblPHK = false;}
      if(llhOUMUjbM == true){llhOUMUjbM = false;}
      if(msAeugTifO == true){msAeugTifO = false;}
      if(SMmSZIIPRl == true){SMmSZIIPRl = false;}
      if(aYuoJsoiHq == true){aYuoJsoiHq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMSYLZFVRL
{ 
  void HGqNRmyybk()
  { 
      bool kQuhJifJbV = false;
      bool xkqEYcrBdh = false;
      bool JytTwrUHLb = false;
      bool WhmdceWiXc = false;
      bool aWkMxgdZFB = false;
      bool wShNOmValQ = false;
      bool OYyzzOxNbt = false;
      bool FJdBHlMhVP = false;
      bool NtBJfDzZOp = false;
      bool JuxGNCYkMh = false;
      bool iQyLulofGb = false;
      bool ZmFVCTWnTw = false;
      bool OXykjJMWnE = false;
      bool NbUmfxwoOt = false;
      bool NTTlQVpaDt = false;
      bool ejQQSLSMbk = false;
      bool YSrBOxSRoF = false;
      bool XgZZhuDLUN = false;
      bool TlTsZcKDTU = false;
      bool diNcUuaSXS = false;
      string jjRpIywbSk;
      string QmRFOBggNd;
      string mTFqIhrYcH;
      string BhAxBrssWH;
      string DFZqodIPzR;
      string KgsLxQeagZ;
      string GWyLiimTDW;
      string HnJGagtNBe;
      string ZbZKwUonAk;
      string MSLwBfGNHG;
      string qnMbKWWlkP;
      string VQYCAdxmOO;
      string syTRJobNEt;
      string ZfGumlPxAY;
      string xCDkOusJwX;
      string iTzsMrTtSU;
      string uJhpopKcON;
      string NzmoQquiCN;
      string uRQgLGgMhu;
      string RVeednUMuY;
      if(jjRpIywbSk == qnMbKWWlkP){kQuhJifJbV = true;}
      else if(qnMbKWWlkP == jjRpIywbSk){iQyLulofGb = true;}
      if(QmRFOBggNd == VQYCAdxmOO){xkqEYcrBdh = true;}
      else if(VQYCAdxmOO == QmRFOBggNd){ZmFVCTWnTw = true;}
      if(mTFqIhrYcH == syTRJobNEt){JytTwrUHLb = true;}
      else if(syTRJobNEt == mTFqIhrYcH){OXykjJMWnE = true;}
      if(BhAxBrssWH == ZfGumlPxAY){WhmdceWiXc = true;}
      else if(ZfGumlPxAY == BhAxBrssWH){NbUmfxwoOt = true;}
      if(DFZqodIPzR == xCDkOusJwX){aWkMxgdZFB = true;}
      else if(xCDkOusJwX == DFZqodIPzR){NTTlQVpaDt = true;}
      if(KgsLxQeagZ == iTzsMrTtSU){wShNOmValQ = true;}
      else if(iTzsMrTtSU == KgsLxQeagZ){ejQQSLSMbk = true;}
      if(GWyLiimTDW == uJhpopKcON){OYyzzOxNbt = true;}
      else if(uJhpopKcON == GWyLiimTDW){YSrBOxSRoF = true;}
      if(HnJGagtNBe == NzmoQquiCN){FJdBHlMhVP = true;}
      if(ZbZKwUonAk == uRQgLGgMhu){NtBJfDzZOp = true;}
      if(MSLwBfGNHG == RVeednUMuY){JuxGNCYkMh = true;}
      while(NzmoQquiCN == HnJGagtNBe){XgZZhuDLUN = true;}
      while(uRQgLGgMhu == uRQgLGgMhu){TlTsZcKDTU = true;}
      while(RVeednUMuY == RVeednUMuY){diNcUuaSXS = true;}
      if(kQuhJifJbV == true){kQuhJifJbV = false;}
      if(xkqEYcrBdh == true){xkqEYcrBdh = false;}
      if(JytTwrUHLb == true){JytTwrUHLb = false;}
      if(WhmdceWiXc == true){WhmdceWiXc = false;}
      if(aWkMxgdZFB == true){aWkMxgdZFB = false;}
      if(wShNOmValQ == true){wShNOmValQ = false;}
      if(OYyzzOxNbt == true){OYyzzOxNbt = false;}
      if(FJdBHlMhVP == true){FJdBHlMhVP = false;}
      if(NtBJfDzZOp == true){NtBJfDzZOp = false;}
      if(JuxGNCYkMh == true){JuxGNCYkMh = false;}
      if(iQyLulofGb == true){iQyLulofGb = false;}
      if(ZmFVCTWnTw == true){ZmFVCTWnTw = false;}
      if(OXykjJMWnE == true){OXykjJMWnE = false;}
      if(NbUmfxwoOt == true){NbUmfxwoOt = false;}
      if(NTTlQVpaDt == true){NTTlQVpaDt = false;}
      if(ejQQSLSMbk == true){ejQQSLSMbk = false;}
      if(YSrBOxSRoF == true){YSrBOxSRoF = false;}
      if(XgZZhuDLUN == true){XgZZhuDLUN = false;}
      if(TlTsZcKDTU == true){TlTsZcKDTU = false;}
      if(diNcUuaSXS == true){diNcUuaSXS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVRLRSRUHO
{ 
  void OpnhOPugXF()
  { 
      bool WqIsibCMPH = false;
      bool NUjOUeKSwp = false;
      bool LShWNbybxo = false;
      bool SUnDtRhknP = false;
      bool aqSSXubcLA = false;
      bool krbdFDIlfG = false;
      bool daPansgfTD = false;
      bool wZdgOUAPyS = false;
      bool zVPxDarJxp = false;
      bool IwFgkzaqde = false;
      bool OwIHDLNtPk = false;
      bool DrmNGIKSWN = false;
      bool AWidtzTwuP = false;
      bool sIlTEDMIsr = false;
      bool MytMmPJrZc = false;
      bool nIUPeqMeME = false;
      bool rRzzquGTJD = false;
      bool uCYeBBcWpe = false;
      bool pbVRbknVnM = false;
      bool qhuoAuytVr = false;
      string GlDfbHdZkW;
      string JLPGMqpgfc;
      string KknHckbUKd;
      string TtwWMJPSkI;
      string nrYcfZSCZN;
      string AoIlaUxuCp;
      string eIOGDPOrtC;
      string bWwXoSLKbC;
      string SZuwdekJwq;
      string LTPtcedSZP;
      string LZIWlcrjxI;
      string JmTzWFNScX;
      string dEwDqIHCtJ;
      string nskLqsQXKA;
      string lAMnhYzQWX;
      string RKoBkGcEfd;
      string VppnTPBIHd;
      string noHbldrIUR;
      string IqeWqdDiZk;
      string PLqfewKXTR;
      if(GlDfbHdZkW == LZIWlcrjxI){WqIsibCMPH = true;}
      else if(LZIWlcrjxI == GlDfbHdZkW){OwIHDLNtPk = true;}
      if(JLPGMqpgfc == JmTzWFNScX){NUjOUeKSwp = true;}
      else if(JmTzWFNScX == JLPGMqpgfc){DrmNGIKSWN = true;}
      if(KknHckbUKd == dEwDqIHCtJ){LShWNbybxo = true;}
      else if(dEwDqIHCtJ == KknHckbUKd){AWidtzTwuP = true;}
      if(TtwWMJPSkI == nskLqsQXKA){SUnDtRhknP = true;}
      else if(nskLqsQXKA == TtwWMJPSkI){sIlTEDMIsr = true;}
      if(nrYcfZSCZN == lAMnhYzQWX){aqSSXubcLA = true;}
      else if(lAMnhYzQWX == nrYcfZSCZN){MytMmPJrZc = true;}
      if(AoIlaUxuCp == RKoBkGcEfd){krbdFDIlfG = true;}
      else if(RKoBkGcEfd == AoIlaUxuCp){nIUPeqMeME = true;}
      if(eIOGDPOrtC == VppnTPBIHd){daPansgfTD = true;}
      else if(VppnTPBIHd == eIOGDPOrtC){rRzzquGTJD = true;}
      if(bWwXoSLKbC == noHbldrIUR){wZdgOUAPyS = true;}
      if(SZuwdekJwq == IqeWqdDiZk){zVPxDarJxp = true;}
      if(LTPtcedSZP == PLqfewKXTR){IwFgkzaqde = true;}
      while(noHbldrIUR == bWwXoSLKbC){uCYeBBcWpe = true;}
      while(IqeWqdDiZk == IqeWqdDiZk){pbVRbknVnM = true;}
      while(PLqfewKXTR == PLqfewKXTR){qhuoAuytVr = true;}
      if(WqIsibCMPH == true){WqIsibCMPH = false;}
      if(NUjOUeKSwp == true){NUjOUeKSwp = false;}
      if(LShWNbybxo == true){LShWNbybxo = false;}
      if(SUnDtRhknP == true){SUnDtRhknP = false;}
      if(aqSSXubcLA == true){aqSSXubcLA = false;}
      if(krbdFDIlfG == true){krbdFDIlfG = false;}
      if(daPansgfTD == true){daPansgfTD = false;}
      if(wZdgOUAPyS == true){wZdgOUAPyS = false;}
      if(zVPxDarJxp == true){zVPxDarJxp = false;}
      if(IwFgkzaqde == true){IwFgkzaqde = false;}
      if(OwIHDLNtPk == true){OwIHDLNtPk = false;}
      if(DrmNGIKSWN == true){DrmNGIKSWN = false;}
      if(AWidtzTwuP == true){AWidtzTwuP = false;}
      if(sIlTEDMIsr == true){sIlTEDMIsr = false;}
      if(MytMmPJrZc == true){MytMmPJrZc = false;}
      if(nIUPeqMeME == true){nIUPeqMeME = false;}
      if(rRzzquGTJD == true){rRzzquGTJD = false;}
      if(uCYeBBcWpe == true){uCYeBBcWpe = false;}
      if(pbVRbknVnM == true){pbVRbknVnM = false;}
      if(qhuoAuytVr == true){qhuoAuytVr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GLSJALBBOT
{ 
  void AHkuMHYuVZ()
  { 
      bool IkaodsgnEx = false;
      bool CWWKAMBJZB = false;
      bool SAsYFYSDLL = false;
      bool SkgYDLpTgp = false;
      bool DTQhNiRsmx = false;
      bool MZFBJIqBjF = false;
      bool ZcbsdQpxGo = false;
      bool VhbjyziLLV = false;
      bool GYQOyrfeOu = false;
      bool TojbPZqXEx = false;
      bool sTlxbexVDK = false;
      bool YfpNyALNtk = false;
      bool jKhLUgxATX = false;
      bool HLGNbmmSmT = false;
      bool uKbEVmyWcO = false;
      bool OddSMikact = false;
      bool hwBeDNZbkK = false;
      bool NrZZpZhdog = false;
      bool hZWFJchnAs = false;
      bool BLprlyJxAI = false;
      string AINOLghjrK;
      string EStXpaopGO;
      string aUIYhnQuSg;
      string LWQkZzETBj;
      string BSgdnZqaFb;
      string gNtUBezofX;
      string QmRLzhBJyq;
      string WUoVMHmdjH;
      string wpopAybwit;
      string zOncSNAVeF;
      string YhbOFLXXHs;
      string rUEXaaxbKA;
      string GFZDqHgLDz;
      string HRzeiONakn;
      string aEnoCdKPCr;
      string PXKdzSHYWx;
      string dLUIlZVYoM;
      string NWqWZCQkBM;
      string wRJLijHUeP;
      string GoDmKOieDb;
      if(AINOLghjrK == YhbOFLXXHs){IkaodsgnEx = true;}
      else if(YhbOFLXXHs == AINOLghjrK){sTlxbexVDK = true;}
      if(EStXpaopGO == rUEXaaxbKA){CWWKAMBJZB = true;}
      else if(rUEXaaxbKA == EStXpaopGO){YfpNyALNtk = true;}
      if(aUIYhnQuSg == GFZDqHgLDz){SAsYFYSDLL = true;}
      else if(GFZDqHgLDz == aUIYhnQuSg){jKhLUgxATX = true;}
      if(LWQkZzETBj == HRzeiONakn){SkgYDLpTgp = true;}
      else if(HRzeiONakn == LWQkZzETBj){HLGNbmmSmT = true;}
      if(BSgdnZqaFb == aEnoCdKPCr){DTQhNiRsmx = true;}
      else if(aEnoCdKPCr == BSgdnZqaFb){uKbEVmyWcO = true;}
      if(gNtUBezofX == PXKdzSHYWx){MZFBJIqBjF = true;}
      else if(PXKdzSHYWx == gNtUBezofX){OddSMikact = true;}
      if(QmRLzhBJyq == dLUIlZVYoM){ZcbsdQpxGo = true;}
      else if(dLUIlZVYoM == QmRLzhBJyq){hwBeDNZbkK = true;}
      if(WUoVMHmdjH == NWqWZCQkBM){VhbjyziLLV = true;}
      if(wpopAybwit == wRJLijHUeP){GYQOyrfeOu = true;}
      if(zOncSNAVeF == GoDmKOieDb){TojbPZqXEx = true;}
      while(NWqWZCQkBM == WUoVMHmdjH){NrZZpZhdog = true;}
      while(wRJLijHUeP == wRJLijHUeP){hZWFJchnAs = true;}
      while(GoDmKOieDb == GoDmKOieDb){BLprlyJxAI = true;}
      if(IkaodsgnEx == true){IkaodsgnEx = false;}
      if(CWWKAMBJZB == true){CWWKAMBJZB = false;}
      if(SAsYFYSDLL == true){SAsYFYSDLL = false;}
      if(SkgYDLpTgp == true){SkgYDLpTgp = false;}
      if(DTQhNiRsmx == true){DTQhNiRsmx = false;}
      if(MZFBJIqBjF == true){MZFBJIqBjF = false;}
      if(ZcbsdQpxGo == true){ZcbsdQpxGo = false;}
      if(VhbjyziLLV == true){VhbjyziLLV = false;}
      if(GYQOyrfeOu == true){GYQOyrfeOu = false;}
      if(TojbPZqXEx == true){TojbPZqXEx = false;}
      if(sTlxbexVDK == true){sTlxbexVDK = false;}
      if(YfpNyALNtk == true){YfpNyALNtk = false;}
      if(jKhLUgxATX == true){jKhLUgxATX = false;}
      if(HLGNbmmSmT == true){HLGNbmmSmT = false;}
      if(uKbEVmyWcO == true){uKbEVmyWcO = false;}
      if(OddSMikact == true){OddSMikact = false;}
      if(hwBeDNZbkK == true){hwBeDNZbkK = false;}
      if(NrZZpZhdog == true){NrZZpZhdog = false;}
      if(hZWFJchnAs == true){hZWFJchnAs = false;}
      if(BLprlyJxAI == true){BLprlyJxAI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEPUQBBKCV
{ 
  void TIgpiPCcqN()
  { 
      bool gMXTBaUTYe = false;
      bool nxifzDKIHC = false;
      bool StERlimSUn = false;
      bool HZUQBDjXTG = false;
      bool ZTENSVYZEM = false;
      bool UaDnolHGhS = false;
      bool nBzkWNcSeu = false;
      bool TloAbyoqzQ = false;
      bool KMOITgWgaO = false;
      bool wcpASYUTpF = false;
      bool rFuJshlCLp = false;
      bool wQGRHampRp = false;
      bool qwqPzpunhD = false;
      bool dVAtXEREOk = false;
      bool uTUkReWYsq = false;
      bool kdCAOuOeKC = false;
      bool mxUIMaQMsD = false;
      bool JiaguWbGxT = false;
      bool TWuqRzTAeb = false;
      bool oltMxxzLXq = false;
      string NRarfusHhy;
      string SEDtubTxnB;
      string HtIWpOXJEY;
      string uKWfkIbHXY;
      string QkdthueHnr;
      string dsGcHSIDCR;
      string XiCJCHgXIm;
      string ALYOjVPNou;
      string jPVLtCEtYS;
      string zYFGAhiUrZ;
      string NHyBrRUqrk;
      string CtNHgHNqOA;
      string DmypmbGRNC;
      string muVPgbQTTb;
      string gMBnPFKyYs;
      string UrGrVZIINP;
      string LCcpxHYyZF;
      string qsWlSqlKZh;
      string QHrUhundsH;
      string SHGDQeiLpI;
      if(NRarfusHhy == NHyBrRUqrk){gMXTBaUTYe = true;}
      else if(NHyBrRUqrk == NRarfusHhy){rFuJshlCLp = true;}
      if(SEDtubTxnB == CtNHgHNqOA){nxifzDKIHC = true;}
      else if(CtNHgHNqOA == SEDtubTxnB){wQGRHampRp = true;}
      if(HtIWpOXJEY == DmypmbGRNC){StERlimSUn = true;}
      else if(DmypmbGRNC == HtIWpOXJEY){qwqPzpunhD = true;}
      if(uKWfkIbHXY == muVPgbQTTb){HZUQBDjXTG = true;}
      else if(muVPgbQTTb == uKWfkIbHXY){dVAtXEREOk = true;}
      if(QkdthueHnr == gMBnPFKyYs){ZTENSVYZEM = true;}
      else if(gMBnPFKyYs == QkdthueHnr){uTUkReWYsq = true;}
      if(dsGcHSIDCR == UrGrVZIINP){UaDnolHGhS = true;}
      else if(UrGrVZIINP == dsGcHSIDCR){kdCAOuOeKC = true;}
      if(XiCJCHgXIm == LCcpxHYyZF){nBzkWNcSeu = true;}
      else if(LCcpxHYyZF == XiCJCHgXIm){mxUIMaQMsD = true;}
      if(ALYOjVPNou == qsWlSqlKZh){TloAbyoqzQ = true;}
      if(jPVLtCEtYS == QHrUhundsH){KMOITgWgaO = true;}
      if(zYFGAhiUrZ == SHGDQeiLpI){wcpASYUTpF = true;}
      while(qsWlSqlKZh == ALYOjVPNou){JiaguWbGxT = true;}
      while(QHrUhundsH == QHrUhundsH){TWuqRzTAeb = true;}
      while(SHGDQeiLpI == SHGDQeiLpI){oltMxxzLXq = true;}
      if(gMXTBaUTYe == true){gMXTBaUTYe = false;}
      if(nxifzDKIHC == true){nxifzDKIHC = false;}
      if(StERlimSUn == true){StERlimSUn = false;}
      if(HZUQBDjXTG == true){HZUQBDjXTG = false;}
      if(ZTENSVYZEM == true){ZTENSVYZEM = false;}
      if(UaDnolHGhS == true){UaDnolHGhS = false;}
      if(nBzkWNcSeu == true){nBzkWNcSeu = false;}
      if(TloAbyoqzQ == true){TloAbyoqzQ = false;}
      if(KMOITgWgaO == true){KMOITgWgaO = false;}
      if(wcpASYUTpF == true){wcpASYUTpF = false;}
      if(rFuJshlCLp == true){rFuJshlCLp = false;}
      if(wQGRHampRp == true){wQGRHampRp = false;}
      if(qwqPzpunhD == true){qwqPzpunhD = false;}
      if(dVAtXEREOk == true){dVAtXEREOk = false;}
      if(uTUkReWYsq == true){uTUkReWYsq = false;}
      if(kdCAOuOeKC == true){kdCAOuOeKC = false;}
      if(mxUIMaQMsD == true){mxUIMaQMsD = false;}
      if(JiaguWbGxT == true){JiaguWbGxT = false;}
      if(TWuqRzTAeb == true){TWuqRzTAeb = false;}
      if(oltMxxzLXq == true){oltMxxzLXq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COXUILGLAW
{ 
  void GHaxukRApd()
  { 
      bool ngGbJuGwFY = false;
      bool pccgaaRHKY = false;
      bool HfmXnRkYKL = false;
      bool ZuYniTdxUc = false;
      bool csTYQnyiXa = false;
      bool EVBXAHsinr = false;
      bool KgkszuDoxH = false;
      bool wUmhwOLOGz = false;
      bool SBBjGDsBmb = false;
      bool ZuJbSuHZYV = false;
      bool kIlQdjiTbl = false;
      bool webnYIeAmu = false;
      bool BCBUgBKKOA = false;
      bool GkojOJOkGW = false;
      bool TZZBeuTVDJ = false;
      bool PGmcUiHQic = false;
      bool ZYEaeKoqZO = false;
      bool sttPbbczok = false;
      bool goHEjAxLPe = false;
      bool CyBdwtUyWU = false;
      string TYIBldBhAg;
      string lkwiSNNYBL;
      string noBXIYGqNc;
      string UikqflPRPU;
      string axGzzBgdBr;
      string eHzmNeXksM;
      string WKTXLDAFDf;
      string ywIfjqhCXG;
      string qcoUxNixcB;
      string OeYCyQcimw;
      string AbaVtiyTCW;
      string wUMlUtUyZy;
      string TCbBRSWGhT;
      string NyOaGPBTZN;
      string OPuFFsRlgD;
      string ueJocyzZEb;
      string LqliIxFkfF;
      string sAXMiDHWwX;
      string AkZdXioZyH;
      string QbPyBWdMxH;
      if(TYIBldBhAg == AbaVtiyTCW){ngGbJuGwFY = true;}
      else if(AbaVtiyTCW == TYIBldBhAg){kIlQdjiTbl = true;}
      if(lkwiSNNYBL == wUMlUtUyZy){pccgaaRHKY = true;}
      else if(wUMlUtUyZy == lkwiSNNYBL){webnYIeAmu = true;}
      if(noBXIYGqNc == TCbBRSWGhT){HfmXnRkYKL = true;}
      else if(TCbBRSWGhT == noBXIYGqNc){BCBUgBKKOA = true;}
      if(UikqflPRPU == NyOaGPBTZN){ZuYniTdxUc = true;}
      else if(NyOaGPBTZN == UikqflPRPU){GkojOJOkGW = true;}
      if(axGzzBgdBr == OPuFFsRlgD){csTYQnyiXa = true;}
      else if(OPuFFsRlgD == axGzzBgdBr){TZZBeuTVDJ = true;}
      if(eHzmNeXksM == ueJocyzZEb){EVBXAHsinr = true;}
      else if(ueJocyzZEb == eHzmNeXksM){PGmcUiHQic = true;}
      if(WKTXLDAFDf == LqliIxFkfF){KgkszuDoxH = true;}
      else if(LqliIxFkfF == WKTXLDAFDf){ZYEaeKoqZO = true;}
      if(ywIfjqhCXG == sAXMiDHWwX){wUmhwOLOGz = true;}
      if(qcoUxNixcB == AkZdXioZyH){SBBjGDsBmb = true;}
      if(OeYCyQcimw == QbPyBWdMxH){ZuJbSuHZYV = true;}
      while(sAXMiDHWwX == ywIfjqhCXG){sttPbbczok = true;}
      while(AkZdXioZyH == AkZdXioZyH){goHEjAxLPe = true;}
      while(QbPyBWdMxH == QbPyBWdMxH){CyBdwtUyWU = true;}
      if(ngGbJuGwFY == true){ngGbJuGwFY = false;}
      if(pccgaaRHKY == true){pccgaaRHKY = false;}
      if(HfmXnRkYKL == true){HfmXnRkYKL = false;}
      if(ZuYniTdxUc == true){ZuYniTdxUc = false;}
      if(csTYQnyiXa == true){csTYQnyiXa = false;}
      if(EVBXAHsinr == true){EVBXAHsinr = false;}
      if(KgkszuDoxH == true){KgkszuDoxH = false;}
      if(wUmhwOLOGz == true){wUmhwOLOGz = false;}
      if(SBBjGDsBmb == true){SBBjGDsBmb = false;}
      if(ZuJbSuHZYV == true){ZuJbSuHZYV = false;}
      if(kIlQdjiTbl == true){kIlQdjiTbl = false;}
      if(webnYIeAmu == true){webnYIeAmu = false;}
      if(BCBUgBKKOA == true){BCBUgBKKOA = false;}
      if(GkojOJOkGW == true){GkojOJOkGW = false;}
      if(TZZBeuTVDJ == true){TZZBeuTVDJ = false;}
      if(PGmcUiHQic == true){PGmcUiHQic = false;}
      if(ZYEaeKoqZO == true){ZYEaeKoqZO = false;}
      if(sttPbbczok == true){sttPbbczok = false;}
      if(goHEjAxLPe == true){goHEjAxLPe = false;}
      if(CyBdwtUyWU == true){CyBdwtUyWU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEDPSUKPIX
{ 
  void qSZGtdoBjH()
  { 
      bool wZLzNjQTqy = false;
      bool DquOZNbrXq = false;
      bool DLgAMxAogH = false;
      bool KKrzjoCiXO = false;
      bool kQmwnawaey = false;
      bool SpBrgjsLlQ = false;
      bool jalinrzuej = false;
      bool KrTJGlYjLl = false;
      bool BYJioTJASz = false;
      bool wqwHdJeDIu = false;
      bool aAwunZVrkt = false;
      bool LIzAOKRCtU = false;
      bool izcenSwMew = false;
      bool HUaPKBcOtP = false;
      bool xROXmmrwrT = false;
      bool rbJnMbXQGU = false;
      bool dJMomqhjoN = false;
      bool hCHeWRjEqA = false;
      bool azULEeLmDi = false;
      bool dLHZlnEZkw = false;
      string hyPEDhKklz;
      string lhoDLAmllB;
      string DEKRjZNjtU;
      string OBMBlpQtai;
      string bqLkhmNDjq;
      string mjVVRdnyTd;
      string UZqQkkVnQV;
      string jrLCZMrYiw;
      string LJzChdepiI;
      string CRaxNBzuAw;
      string RZmOHtYSuF;
      string kOOWRLaohG;
      string FeFHTRRNoY;
      string MxXmelWktn;
      string EMucXmCDeC;
      string ZKMsqmTeuo;
      string bKdVsmpbre;
      string nptsBribjf;
      string POilyBjeur;
      string SqoFLthYjj;
      if(hyPEDhKklz == RZmOHtYSuF){wZLzNjQTqy = true;}
      else if(RZmOHtYSuF == hyPEDhKklz){aAwunZVrkt = true;}
      if(lhoDLAmllB == kOOWRLaohG){DquOZNbrXq = true;}
      else if(kOOWRLaohG == lhoDLAmllB){LIzAOKRCtU = true;}
      if(DEKRjZNjtU == FeFHTRRNoY){DLgAMxAogH = true;}
      else if(FeFHTRRNoY == DEKRjZNjtU){izcenSwMew = true;}
      if(OBMBlpQtai == MxXmelWktn){KKrzjoCiXO = true;}
      else if(MxXmelWktn == OBMBlpQtai){HUaPKBcOtP = true;}
      if(bqLkhmNDjq == EMucXmCDeC){kQmwnawaey = true;}
      else if(EMucXmCDeC == bqLkhmNDjq){xROXmmrwrT = true;}
      if(mjVVRdnyTd == ZKMsqmTeuo){SpBrgjsLlQ = true;}
      else if(ZKMsqmTeuo == mjVVRdnyTd){rbJnMbXQGU = true;}
      if(UZqQkkVnQV == bKdVsmpbre){jalinrzuej = true;}
      else if(bKdVsmpbre == UZqQkkVnQV){dJMomqhjoN = true;}
      if(jrLCZMrYiw == nptsBribjf){KrTJGlYjLl = true;}
      if(LJzChdepiI == POilyBjeur){BYJioTJASz = true;}
      if(CRaxNBzuAw == SqoFLthYjj){wqwHdJeDIu = true;}
      while(nptsBribjf == jrLCZMrYiw){hCHeWRjEqA = true;}
      while(POilyBjeur == POilyBjeur){azULEeLmDi = true;}
      while(SqoFLthYjj == SqoFLthYjj){dLHZlnEZkw = true;}
      if(wZLzNjQTqy == true){wZLzNjQTqy = false;}
      if(DquOZNbrXq == true){DquOZNbrXq = false;}
      if(DLgAMxAogH == true){DLgAMxAogH = false;}
      if(KKrzjoCiXO == true){KKrzjoCiXO = false;}
      if(kQmwnawaey == true){kQmwnawaey = false;}
      if(SpBrgjsLlQ == true){SpBrgjsLlQ = false;}
      if(jalinrzuej == true){jalinrzuej = false;}
      if(KrTJGlYjLl == true){KrTJGlYjLl = false;}
      if(BYJioTJASz == true){BYJioTJASz = false;}
      if(wqwHdJeDIu == true){wqwHdJeDIu = false;}
      if(aAwunZVrkt == true){aAwunZVrkt = false;}
      if(LIzAOKRCtU == true){LIzAOKRCtU = false;}
      if(izcenSwMew == true){izcenSwMew = false;}
      if(HUaPKBcOtP == true){HUaPKBcOtP = false;}
      if(xROXmmrwrT == true){xROXmmrwrT = false;}
      if(rbJnMbXQGU == true){rbJnMbXQGU = false;}
      if(dJMomqhjoN == true){dJMomqhjoN = false;}
      if(hCHeWRjEqA == true){hCHeWRjEqA = false;}
      if(azULEeLmDi == true){azULEeLmDi = false;}
      if(dLHZlnEZkw == true){dLHZlnEZkw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LIDKZVOQFA
{ 
  void BeRDuIEiSS()
  { 
      bool xhcucNIOpb = false;
      bool RhxewKiTUr = false;
      bool mXJhzPDjCS = false;
      bool wHtRHgXFac = false;
      bool lnSZtYLIKf = false;
      bool mBTzWZXuwM = false;
      bool KYLXfKnfXP = false;
      bool ldrqFzEjmZ = false;
      bool EuYWeumuth = false;
      bool JcJNSMcutj = false;
      bool jekusJIcsX = false;
      bool UnHVIOznrj = false;
      bool WrkpGJTeYs = false;
      bool WIpCoYJdcV = false;
      bool lKCVMVUmFD = false;
      bool MnDJMrtunj = false;
      bool odDzBMxEfi = false;
      bool FVKWxMpOdk = false;
      bool ngYUghFfox = false;
      bool eOosfIGCUA = false;
      string zUmOJCGUHK;
      string orckTWOJLy;
      string QoieGTMxVe;
      string TKkBJjKzXy;
      string fJdTgTKcDh;
      string wYpaoKkHIp;
      string pJzcqdHabi;
      string MOkNSGKPym;
      string JisnhuUJMz;
      string zDqhHVKBbC;
      string MiBUUhmcIh;
      string zUIUgGQKtw;
      string IxObjJWCFw;
      string uJnwaahYSA;
      string HrBdAdtWBB;
      string FAHesOTYjL;
      string KkWLmogMtF;
      string YqqsoQwkbF;
      string OABDquCICM;
      string GInHpWUoqK;
      if(zUmOJCGUHK == MiBUUhmcIh){xhcucNIOpb = true;}
      else if(MiBUUhmcIh == zUmOJCGUHK){jekusJIcsX = true;}
      if(orckTWOJLy == zUIUgGQKtw){RhxewKiTUr = true;}
      else if(zUIUgGQKtw == orckTWOJLy){UnHVIOznrj = true;}
      if(QoieGTMxVe == IxObjJWCFw){mXJhzPDjCS = true;}
      else if(IxObjJWCFw == QoieGTMxVe){WrkpGJTeYs = true;}
      if(TKkBJjKzXy == uJnwaahYSA){wHtRHgXFac = true;}
      else if(uJnwaahYSA == TKkBJjKzXy){WIpCoYJdcV = true;}
      if(fJdTgTKcDh == HrBdAdtWBB){lnSZtYLIKf = true;}
      else if(HrBdAdtWBB == fJdTgTKcDh){lKCVMVUmFD = true;}
      if(wYpaoKkHIp == FAHesOTYjL){mBTzWZXuwM = true;}
      else if(FAHesOTYjL == wYpaoKkHIp){MnDJMrtunj = true;}
      if(pJzcqdHabi == KkWLmogMtF){KYLXfKnfXP = true;}
      else if(KkWLmogMtF == pJzcqdHabi){odDzBMxEfi = true;}
      if(MOkNSGKPym == YqqsoQwkbF){ldrqFzEjmZ = true;}
      if(JisnhuUJMz == OABDquCICM){EuYWeumuth = true;}
      if(zDqhHVKBbC == GInHpWUoqK){JcJNSMcutj = true;}
      while(YqqsoQwkbF == MOkNSGKPym){FVKWxMpOdk = true;}
      while(OABDquCICM == OABDquCICM){ngYUghFfox = true;}
      while(GInHpWUoqK == GInHpWUoqK){eOosfIGCUA = true;}
      if(xhcucNIOpb == true){xhcucNIOpb = false;}
      if(RhxewKiTUr == true){RhxewKiTUr = false;}
      if(mXJhzPDjCS == true){mXJhzPDjCS = false;}
      if(wHtRHgXFac == true){wHtRHgXFac = false;}
      if(lnSZtYLIKf == true){lnSZtYLIKf = false;}
      if(mBTzWZXuwM == true){mBTzWZXuwM = false;}
      if(KYLXfKnfXP == true){KYLXfKnfXP = false;}
      if(ldrqFzEjmZ == true){ldrqFzEjmZ = false;}
      if(EuYWeumuth == true){EuYWeumuth = false;}
      if(JcJNSMcutj == true){JcJNSMcutj = false;}
      if(jekusJIcsX == true){jekusJIcsX = false;}
      if(UnHVIOznrj == true){UnHVIOznrj = false;}
      if(WrkpGJTeYs == true){WrkpGJTeYs = false;}
      if(WIpCoYJdcV == true){WIpCoYJdcV = false;}
      if(lKCVMVUmFD == true){lKCVMVUmFD = false;}
      if(MnDJMrtunj == true){MnDJMrtunj = false;}
      if(odDzBMxEfi == true){odDzBMxEfi = false;}
      if(FVKWxMpOdk == true){FVKWxMpOdk = false;}
      if(ngYUghFfox == true){ngYUghFfox = false;}
      if(eOosfIGCUA == true){eOosfIGCUA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKLRNBFQNU
{ 
  void UGyHWBtcUm()
  { 
      bool wPNXQXpKjq = false;
      bool VXxAyBUyWa = false;
      bool KOMyADFWPO = false;
      bool EtLSJhCjPI = false;
      bool OCADoOtJKN = false;
      bool JpQbdgDPWN = false;
      bool RStVmbLdqQ = false;
      bool ykhNMHNIIk = false;
      bool IwMCFOcjob = false;
      bool emMCquHeQM = false;
      bool DQSsOXICPW = false;
      bool TtGlFVGrPX = false;
      bool zbnOkLYeWR = false;
      bool ziqwhqcSnh = false;
      bool GZUSIkfawU = false;
      bool oPPsNabEIC = false;
      bool zcfxWkCKDN = false;
      bool smEhRYGVFA = false;
      bool fxiCbiSyiG = false;
      bool OXKkhdtWuX = false;
      string pssgMXAobG;
      string QZYkkNzwOS;
      string HGhbOlItcc;
      string zMijZWdOBR;
      string aVAmzVZlVD;
      string psUQsiKQRa;
      string OFMyHDqoLN;
      string jjuwqkGubs;
      string LWYZlFqRpp;
      string LMwaDVJBfw;
      string dkZHTFxXZH;
      string cPnYOqglLB;
      string LZyUBWnUsV;
      string bEPfPawQFg;
      string HSriNwYXML;
      string nWpdjDmEGw;
      string RceEfYAIJn;
      string uQfesrhOHF;
      string yQIggENkuL;
      string mqKIOdnnCn;
      if(pssgMXAobG == dkZHTFxXZH){wPNXQXpKjq = true;}
      else if(dkZHTFxXZH == pssgMXAobG){DQSsOXICPW = true;}
      if(QZYkkNzwOS == cPnYOqglLB){VXxAyBUyWa = true;}
      else if(cPnYOqglLB == QZYkkNzwOS){TtGlFVGrPX = true;}
      if(HGhbOlItcc == LZyUBWnUsV){KOMyADFWPO = true;}
      else if(LZyUBWnUsV == HGhbOlItcc){zbnOkLYeWR = true;}
      if(zMijZWdOBR == bEPfPawQFg){EtLSJhCjPI = true;}
      else if(bEPfPawQFg == zMijZWdOBR){ziqwhqcSnh = true;}
      if(aVAmzVZlVD == HSriNwYXML){OCADoOtJKN = true;}
      else if(HSriNwYXML == aVAmzVZlVD){GZUSIkfawU = true;}
      if(psUQsiKQRa == nWpdjDmEGw){JpQbdgDPWN = true;}
      else if(nWpdjDmEGw == psUQsiKQRa){oPPsNabEIC = true;}
      if(OFMyHDqoLN == RceEfYAIJn){RStVmbLdqQ = true;}
      else if(RceEfYAIJn == OFMyHDqoLN){zcfxWkCKDN = true;}
      if(jjuwqkGubs == uQfesrhOHF){ykhNMHNIIk = true;}
      if(LWYZlFqRpp == yQIggENkuL){IwMCFOcjob = true;}
      if(LMwaDVJBfw == mqKIOdnnCn){emMCquHeQM = true;}
      while(uQfesrhOHF == jjuwqkGubs){smEhRYGVFA = true;}
      while(yQIggENkuL == yQIggENkuL){fxiCbiSyiG = true;}
      while(mqKIOdnnCn == mqKIOdnnCn){OXKkhdtWuX = true;}
      if(wPNXQXpKjq == true){wPNXQXpKjq = false;}
      if(VXxAyBUyWa == true){VXxAyBUyWa = false;}
      if(KOMyADFWPO == true){KOMyADFWPO = false;}
      if(EtLSJhCjPI == true){EtLSJhCjPI = false;}
      if(OCADoOtJKN == true){OCADoOtJKN = false;}
      if(JpQbdgDPWN == true){JpQbdgDPWN = false;}
      if(RStVmbLdqQ == true){RStVmbLdqQ = false;}
      if(ykhNMHNIIk == true){ykhNMHNIIk = false;}
      if(IwMCFOcjob == true){IwMCFOcjob = false;}
      if(emMCquHeQM == true){emMCquHeQM = false;}
      if(DQSsOXICPW == true){DQSsOXICPW = false;}
      if(TtGlFVGrPX == true){TtGlFVGrPX = false;}
      if(zbnOkLYeWR == true){zbnOkLYeWR = false;}
      if(ziqwhqcSnh == true){ziqwhqcSnh = false;}
      if(GZUSIkfawU == true){GZUSIkfawU = false;}
      if(oPPsNabEIC == true){oPPsNabEIC = false;}
      if(zcfxWkCKDN == true){zcfxWkCKDN = false;}
      if(smEhRYGVFA == true){smEhRYGVFA = false;}
      if(fxiCbiSyiG == true){fxiCbiSyiG = false;}
      if(OXKkhdtWuX == true){OXKkhdtWuX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJJICQSOZA
{ 
  void LbBRuCOWhx()
  { 
      bool YDTieFXeOF = false;
      bool fmZbiIfKkr = false;
      bool rrlkibUtWC = false;
      bool ReXhtwssSw = false;
      bool gnFOwKRHiC = false;
      bool JleWDgQhzC = false;
      bool kcHLmBOqgm = false;
      bool PlroKDlWoX = false;
      bool KNKTrfzBdM = false;
      bool eKsPLDfsbu = false;
      bool wZZwmWtpLA = false;
      bool tssbqWSnSH = false;
      bool BMNUHEsbdH = false;
      bool WsutbknOgU = false;
      bool lJpdRkRRXn = false;
      bool krZUsiLEnh = false;
      bool dRLEcByyzG = false;
      bool iDHxUrWjDW = false;
      bool mbDoVeSaAs = false;
      bool ZiayqTxlBP = false;
      string wNWDUPPOZo;
      string KBcjIwtbaC;
      string yxEyFUOEFM;
      string DdBcygeySO;
      string BIphUaXbbK;
      string NHRzcyIYxz;
      string BKJNkgAzkb;
      string QwJLBoHWce;
      string wlctyuMBAz;
      string XGASNpzbwn;
      string aYpzsRyGym;
      string qluSDOgOPo;
      string UyzlEKuqxK;
      string pfanEWudBg;
      string xFDMHkKhOz;
      string JkMGTbZEui;
      string VHImxLLHOf;
      string TDMhrOumdT;
      string zMbyBFSTUc;
      string xqiSLowQOw;
      if(wNWDUPPOZo == aYpzsRyGym){YDTieFXeOF = true;}
      else if(aYpzsRyGym == wNWDUPPOZo){wZZwmWtpLA = true;}
      if(KBcjIwtbaC == qluSDOgOPo){fmZbiIfKkr = true;}
      else if(qluSDOgOPo == KBcjIwtbaC){tssbqWSnSH = true;}
      if(yxEyFUOEFM == UyzlEKuqxK){rrlkibUtWC = true;}
      else if(UyzlEKuqxK == yxEyFUOEFM){BMNUHEsbdH = true;}
      if(DdBcygeySO == pfanEWudBg){ReXhtwssSw = true;}
      else if(pfanEWudBg == DdBcygeySO){WsutbknOgU = true;}
      if(BIphUaXbbK == xFDMHkKhOz){gnFOwKRHiC = true;}
      else if(xFDMHkKhOz == BIphUaXbbK){lJpdRkRRXn = true;}
      if(NHRzcyIYxz == JkMGTbZEui){JleWDgQhzC = true;}
      else if(JkMGTbZEui == NHRzcyIYxz){krZUsiLEnh = true;}
      if(BKJNkgAzkb == VHImxLLHOf){kcHLmBOqgm = true;}
      else if(VHImxLLHOf == BKJNkgAzkb){dRLEcByyzG = true;}
      if(QwJLBoHWce == TDMhrOumdT){PlroKDlWoX = true;}
      if(wlctyuMBAz == zMbyBFSTUc){KNKTrfzBdM = true;}
      if(XGASNpzbwn == xqiSLowQOw){eKsPLDfsbu = true;}
      while(TDMhrOumdT == QwJLBoHWce){iDHxUrWjDW = true;}
      while(zMbyBFSTUc == zMbyBFSTUc){mbDoVeSaAs = true;}
      while(xqiSLowQOw == xqiSLowQOw){ZiayqTxlBP = true;}
      if(YDTieFXeOF == true){YDTieFXeOF = false;}
      if(fmZbiIfKkr == true){fmZbiIfKkr = false;}
      if(rrlkibUtWC == true){rrlkibUtWC = false;}
      if(ReXhtwssSw == true){ReXhtwssSw = false;}
      if(gnFOwKRHiC == true){gnFOwKRHiC = false;}
      if(JleWDgQhzC == true){JleWDgQhzC = false;}
      if(kcHLmBOqgm == true){kcHLmBOqgm = false;}
      if(PlroKDlWoX == true){PlroKDlWoX = false;}
      if(KNKTrfzBdM == true){KNKTrfzBdM = false;}
      if(eKsPLDfsbu == true){eKsPLDfsbu = false;}
      if(wZZwmWtpLA == true){wZZwmWtpLA = false;}
      if(tssbqWSnSH == true){tssbqWSnSH = false;}
      if(BMNUHEsbdH == true){BMNUHEsbdH = false;}
      if(WsutbknOgU == true){WsutbknOgU = false;}
      if(lJpdRkRRXn == true){lJpdRkRRXn = false;}
      if(krZUsiLEnh == true){krZUsiLEnh = false;}
      if(dRLEcByyzG == true){dRLEcByyzG = false;}
      if(iDHxUrWjDW == true){iDHxUrWjDW = false;}
      if(mbDoVeSaAs == true){mbDoVeSaAs = false;}
      if(ZiayqTxlBP == true){ZiayqTxlBP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLBNCNEBBL
{ 
  void XYwBSiThJc()
  { 
      bool jFEmJFCDoZ = false;
      bool gJKsQRRaJD = false;
      bool ZdeJHyluOP = false;
      bool uoTCtAyGoU = false;
      bool dXCNQSWFiO = false;
      bool hYfNUFatfK = false;
      bool SHoYerpIzP = false;
      bool TLlnZBaQsn = false;
      bool bgMzgWIFgn = false;
      bool ZDZdBViciX = false;
      bool cNGSuWmqnT = false;
      bool eKBqiluorI = false;
      bool ikbKpPkHmD = false;
      bool SygVLNZtEK = false;
      bool iRQNJPChuP = false;
      bool atjanrlwcf = false;
      bool lfEkAfcffU = false;
      bool LBjhYRTNAa = false;
      bool MCLWbXNFgT = false;
      bool adQYXDMeMd = false;
      string IiNKAilqBg;
      string FcbxfDNhiM;
      string uGioTpRwDQ;
      string NBxXbXYUmf;
      string rChCrtkXPf;
      string dXPVHCAYqK;
      string RpnkSEeDUH;
      string dstCTrYgwY;
      string EtfXmpkaQZ;
      string XAdcNCOxin;
      string PhCHBkcMBO;
      string cSbRFXKQxc;
      string SDmtidPRnR;
      string daxIJWqXVC;
      string MXYBxEXMWp;
      string qxzFULtIXW;
      string ULYjjBUSHi;
      string gltuQtdkxd;
      string GDtyZgbqnx;
      string bhzzgAzoRu;
      if(IiNKAilqBg == PhCHBkcMBO){jFEmJFCDoZ = true;}
      else if(PhCHBkcMBO == IiNKAilqBg){cNGSuWmqnT = true;}
      if(FcbxfDNhiM == cSbRFXKQxc){gJKsQRRaJD = true;}
      else if(cSbRFXKQxc == FcbxfDNhiM){eKBqiluorI = true;}
      if(uGioTpRwDQ == SDmtidPRnR){ZdeJHyluOP = true;}
      else if(SDmtidPRnR == uGioTpRwDQ){ikbKpPkHmD = true;}
      if(NBxXbXYUmf == daxIJWqXVC){uoTCtAyGoU = true;}
      else if(daxIJWqXVC == NBxXbXYUmf){SygVLNZtEK = true;}
      if(rChCrtkXPf == MXYBxEXMWp){dXCNQSWFiO = true;}
      else if(MXYBxEXMWp == rChCrtkXPf){iRQNJPChuP = true;}
      if(dXPVHCAYqK == qxzFULtIXW){hYfNUFatfK = true;}
      else if(qxzFULtIXW == dXPVHCAYqK){atjanrlwcf = true;}
      if(RpnkSEeDUH == ULYjjBUSHi){SHoYerpIzP = true;}
      else if(ULYjjBUSHi == RpnkSEeDUH){lfEkAfcffU = true;}
      if(dstCTrYgwY == gltuQtdkxd){TLlnZBaQsn = true;}
      if(EtfXmpkaQZ == GDtyZgbqnx){bgMzgWIFgn = true;}
      if(XAdcNCOxin == bhzzgAzoRu){ZDZdBViciX = true;}
      while(gltuQtdkxd == dstCTrYgwY){LBjhYRTNAa = true;}
      while(GDtyZgbqnx == GDtyZgbqnx){MCLWbXNFgT = true;}
      while(bhzzgAzoRu == bhzzgAzoRu){adQYXDMeMd = true;}
      if(jFEmJFCDoZ == true){jFEmJFCDoZ = false;}
      if(gJKsQRRaJD == true){gJKsQRRaJD = false;}
      if(ZdeJHyluOP == true){ZdeJHyluOP = false;}
      if(uoTCtAyGoU == true){uoTCtAyGoU = false;}
      if(dXCNQSWFiO == true){dXCNQSWFiO = false;}
      if(hYfNUFatfK == true){hYfNUFatfK = false;}
      if(SHoYerpIzP == true){SHoYerpIzP = false;}
      if(TLlnZBaQsn == true){TLlnZBaQsn = false;}
      if(bgMzgWIFgn == true){bgMzgWIFgn = false;}
      if(ZDZdBViciX == true){ZDZdBViciX = false;}
      if(cNGSuWmqnT == true){cNGSuWmqnT = false;}
      if(eKBqiluorI == true){eKBqiluorI = false;}
      if(ikbKpPkHmD == true){ikbKpPkHmD = false;}
      if(SygVLNZtEK == true){SygVLNZtEK = false;}
      if(iRQNJPChuP == true){iRQNJPChuP = false;}
      if(atjanrlwcf == true){atjanrlwcf = false;}
      if(lfEkAfcffU == true){lfEkAfcffU = false;}
      if(LBjhYRTNAa == true){LBjhYRTNAa = false;}
      if(MCLWbXNFgT == true){MCLWbXNFgT = false;}
      if(adQYXDMeMd == true){adQYXDMeMd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXIKNDOURD
{ 
  void UeKzpYfSnV()
  { 
      bool NqqdnzjqJJ = false;
      bool HuKpVfrCBk = false;
      bool UoCtphxCBM = false;
      bool ERbWWrnbRh = false;
      bool kQjTswEqdp = false;
      bool BdVmhYnxmF = false;
      bool BhpxFpTmTd = false;
      bool rQkSzDEiAs = false;
      bool dGXKKZuooy = false;
      bool EqnLgDamND = false;
      bool cQXAyjsDmd = false;
      bool TFwsbtJele = false;
      bool teyVZAcYkw = false;
      bool bRUwQMiWMa = false;
      bool gqBKdyttjl = false;
      bool swAhIySCax = false;
      bool HURqCCkzcO = false;
      bool LmRLyCcmqa = false;
      bool GhnyCfQlmR = false;
      bool tgwPSLZKIa = false;
      string TbcOXIAlLm;
      string pdEGoDNhFD;
      string hcDffeSuKr;
      string cXeYVQWNdb;
      string XZmamqKbfr;
      string eTfbZpYwhr;
      string pEbSJRyfkY;
      string fzDdfIpcso;
      string TqPRNJqCye;
      string rZfkkTyTRU;
      string repHLeQBwR;
      string zuDrYynJFA;
      string awgFgFSRsM;
      string JWLXxoAIGh;
      string roGffwWmMl;
      string enORtwxkaF;
      string LyIiHcifui;
      string yfDWHkoBZj;
      string ifFGhVItcA;
      string rPhAVtgXYC;
      if(TbcOXIAlLm == repHLeQBwR){NqqdnzjqJJ = true;}
      else if(repHLeQBwR == TbcOXIAlLm){cQXAyjsDmd = true;}
      if(pdEGoDNhFD == zuDrYynJFA){HuKpVfrCBk = true;}
      else if(zuDrYynJFA == pdEGoDNhFD){TFwsbtJele = true;}
      if(hcDffeSuKr == awgFgFSRsM){UoCtphxCBM = true;}
      else if(awgFgFSRsM == hcDffeSuKr){teyVZAcYkw = true;}
      if(cXeYVQWNdb == JWLXxoAIGh){ERbWWrnbRh = true;}
      else if(JWLXxoAIGh == cXeYVQWNdb){bRUwQMiWMa = true;}
      if(XZmamqKbfr == roGffwWmMl){kQjTswEqdp = true;}
      else if(roGffwWmMl == XZmamqKbfr){gqBKdyttjl = true;}
      if(eTfbZpYwhr == enORtwxkaF){BdVmhYnxmF = true;}
      else if(enORtwxkaF == eTfbZpYwhr){swAhIySCax = true;}
      if(pEbSJRyfkY == LyIiHcifui){BhpxFpTmTd = true;}
      else if(LyIiHcifui == pEbSJRyfkY){HURqCCkzcO = true;}
      if(fzDdfIpcso == yfDWHkoBZj){rQkSzDEiAs = true;}
      if(TqPRNJqCye == ifFGhVItcA){dGXKKZuooy = true;}
      if(rZfkkTyTRU == rPhAVtgXYC){EqnLgDamND = true;}
      while(yfDWHkoBZj == fzDdfIpcso){LmRLyCcmqa = true;}
      while(ifFGhVItcA == ifFGhVItcA){GhnyCfQlmR = true;}
      while(rPhAVtgXYC == rPhAVtgXYC){tgwPSLZKIa = true;}
      if(NqqdnzjqJJ == true){NqqdnzjqJJ = false;}
      if(HuKpVfrCBk == true){HuKpVfrCBk = false;}
      if(UoCtphxCBM == true){UoCtphxCBM = false;}
      if(ERbWWrnbRh == true){ERbWWrnbRh = false;}
      if(kQjTswEqdp == true){kQjTswEqdp = false;}
      if(BdVmhYnxmF == true){BdVmhYnxmF = false;}
      if(BhpxFpTmTd == true){BhpxFpTmTd = false;}
      if(rQkSzDEiAs == true){rQkSzDEiAs = false;}
      if(dGXKKZuooy == true){dGXKKZuooy = false;}
      if(EqnLgDamND == true){EqnLgDamND = false;}
      if(cQXAyjsDmd == true){cQXAyjsDmd = false;}
      if(TFwsbtJele == true){TFwsbtJele = false;}
      if(teyVZAcYkw == true){teyVZAcYkw = false;}
      if(bRUwQMiWMa == true){bRUwQMiWMa = false;}
      if(gqBKdyttjl == true){gqBKdyttjl = false;}
      if(swAhIySCax == true){swAhIySCax = false;}
      if(HURqCCkzcO == true){HURqCCkzcO = false;}
      if(LmRLyCcmqa == true){LmRLyCcmqa = false;}
      if(GhnyCfQlmR == true){GhnyCfQlmR = false;}
      if(tgwPSLZKIa == true){tgwPSLZKIa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PXITPCSPZS
{ 
  void ojsRhjcYYp()
  { 
      bool mSgOXhVKLW = false;
      bool LrcYKKpRYu = false;
      bool oRUByOoagW = false;
      bool BpbdXigDpZ = false;
      bool smDXezEwnX = false;
      bool BKZzpVxfQI = false;
      bool sucoVVPyAa = false;
      bool dlbyCCNwVy = false;
      bool JrlJUpPcmC = false;
      bool kBlggxJNCI = false;
      bool iGuMtPiawm = false;
      bool HAJSzAITUe = false;
      bool GmKypbztRF = false;
      bool sztMODxZOF = false;
      bool GnfAtkrThg = false;
      bool nosXCwuwWR = false;
      bool PoJqtHGwDu = false;
      bool CiEOXRGKDF = false;
      bool jeLjRDGWKS = false;
      bool IADwoReoFm = false;
      string LamgCOhUhn;
      string YmoaTWNfJn;
      string HYVocBLCfk;
      string qKAjRxrOEn;
      string jTynDKzZkZ;
      string NIklJlExDA;
      string CeoxxNlEJW;
      string dzbUEnZgkR;
      string CkRFWhZOae;
      string rtKDlEdBpo;
      string YtQNuNgPgU;
      string LXLkyQNiZP;
      string nWddejnXiz;
      string JYpwsIUDKI;
      string AJgGTThZFU;
      string quaaBBPmiL;
      string ZIghKmgPrp;
      string wJYQOdoXKK;
      string BOSOIOxPuq;
      string rgUyirczuf;
      if(LamgCOhUhn == YtQNuNgPgU){mSgOXhVKLW = true;}
      else if(YtQNuNgPgU == LamgCOhUhn){iGuMtPiawm = true;}
      if(YmoaTWNfJn == LXLkyQNiZP){LrcYKKpRYu = true;}
      else if(LXLkyQNiZP == YmoaTWNfJn){HAJSzAITUe = true;}
      if(HYVocBLCfk == nWddejnXiz){oRUByOoagW = true;}
      else if(nWddejnXiz == HYVocBLCfk){GmKypbztRF = true;}
      if(qKAjRxrOEn == JYpwsIUDKI){BpbdXigDpZ = true;}
      else if(JYpwsIUDKI == qKAjRxrOEn){sztMODxZOF = true;}
      if(jTynDKzZkZ == AJgGTThZFU){smDXezEwnX = true;}
      else if(AJgGTThZFU == jTynDKzZkZ){GnfAtkrThg = true;}
      if(NIklJlExDA == quaaBBPmiL){BKZzpVxfQI = true;}
      else if(quaaBBPmiL == NIklJlExDA){nosXCwuwWR = true;}
      if(CeoxxNlEJW == ZIghKmgPrp){sucoVVPyAa = true;}
      else if(ZIghKmgPrp == CeoxxNlEJW){PoJqtHGwDu = true;}
      if(dzbUEnZgkR == wJYQOdoXKK){dlbyCCNwVy = true;}
      if(CkRFWhZOae == BOSOIOxPuq){JrlJUpPcmC = true;}
      if(rtKDlEdBpo == rgUyirczuf){kBlggxJNCI = true;}
      while(wJYQOdoXKK == dzbUEnZgkR){CiEOXRGKDF = true;}
      while(BOSOIOxPuq == BOSOIOxPuq){jeLjRDGWKS = true;}
      while(rgUyirczuf == rgUyirczuf){IADwoReoFm = true;}
      if(mSgOXhVKLW == true){mSgOXhVKLW = false;}
      if(LrcYKKpRYu == true){LrcYKKpRYu = false;}
      if(oRUByOoagW == true){oRUByOoagW = false;}
      if(BpbdXigDpZ == true){BpbdXigDpZ = false;}
      if(smDXezEwnX == true){smDXezEwnX = false;}
      if(BKZzpVxfQI == true){BKZzpVxfQI = false;}
      if(sucoVVPyAa == true){sucoVVPyAa = false;}
      if(dlbyCCNwVy == true){dlbyCCNwVy = false;}
      if(JrlJUpPcmC == true){JrlJUpPcmC = false;}
      if(kBlggxJNCI == true){kBlggxJNCI = false;}
      if(iGuMtPiawm == true){iGuMtPiawm = false;}
      if(HAJSzAITUe == true){HAJSzAITUe = false;}
      if(GmKypbztRF == true){GmKypbztRF = false;}
      if(sztMODxZOF == true){sztMODxZOF = false;}
      if(GnfAtkrThg == true){GnfAtkrThg = false;}
      if(nosXCwuwWR == true){nosXCwuwWR = false;}
      if(PoJqtHGwDu == true){PoJqtHGwDu = false;}
      if(CiEOXRGKDF == true){CiEOXRGKDF = false;}
      if(jeLjRDGWKS == true){jeLjRDGWKS = false;}
      if(IADwoReoFm == true){IADwoReoFm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOZTCMSSHZ
{ 
  void LKCBtwNWQy()
  { 
      bool tizPOVfRra = false;
      bool jqedhoBzpq = false;
      bool uHFZGpkIhX = false;
      bool kiktMxRqEU = false;
      bool sziqixAwOV = false;
      bool eobePmdZJY = false;
      bool jXiToAGkRj = false;
      bool WJtVywYOpJ = false;
      bool oosMswHFdY = false;
      bool TqgfjUPOBi = false;
      bool pPdeyUuFgT = false;
      bool OOjAiueWas = false;
      bool sBHrQecOlc = false;
      bool gJMGSZKONX = false;
      bool ACXJKEHfwo = false;
      bool psmIpoIkNS = false;
      bool rfTDlECchJ = false;
      bool jQICrqcxhL = false;
      bool XwSwmnVEQd = false;
      bool RYAteUhTXF = false;
      string xeraGJZoyM;
      string okUpXfnYVh;
      string CMLxiooWGE;
      string EdgIyDsjLs;
      string HmPyupGHpp;
      string VnzdrkTtqR;
      string UDhtILDLqT;
      string mDMcaPxNCr;
      string hggPiPdCPM;
      string jyrtXDEVoi;
      string ltPVDRaWDc;
      string nGqzimWRKr;
      string hAuejnKSEW;
      string LbXTFnQLMR;
      string nHzmYcHsLk;
      string glKwBlzkkO;
      string GISgQMiXsu;
      string VLFsEZBHGG;
      string gRHSpZQaRT;
      string nfZxKfnRWL;
      if(xeraGJZoyM == ltPVDRaWDc){tizPOVfRra = true;}
      else if(ltPVDRaWDc == xeraGJZoyM){pPdeyUuFgT = true;}
      if(okUpXfnYVh == nGqzimWRKr){jqedhoBzpq = true;}
      else if(nGqzimWRKr == okUpXfnYVh){OOjAiueWas = true;}
      if(CMLxiooWGE == hAuejnKSEW){uHFZGpkIhX = true;}
      else if(hAuejnKSEW == CMLxiooWGE){sBHrQecOlc = true;}
      if(EdgIyDsjLs == LbXTFnQLMR){kiktMxRqEU = true;}
      else if(LbXTFnQLMR == EdgIyDsjLs){gJMGSZKONX = true;}
      if(HmPyupGHpp == nHzmYcHsLk){sziqixAwOV = true;}
      else if(nHzmYcHsLk == HmPyupGHpp){ACXJKEHfwo = true;}
      if(VnzdrkTtqR == glKwBlzkkO){eobePmdZJY = true;}
      else if(glKwBlzkkO == VnzdrkTtqR){psmIpoIkNS = true;}
      if(UDhtILDLqT == GISgQMiXsu){jXiToAGkRj = true;}
      else if(GISgQMiXsu == UDhtILDLqT){rfTDlECchJ = true;}
      if(mDMcaPxNCr == VLFsEZBHGG){WJtVywYOpJ = true;}
      if(hggPiPdCPM == gRHSpZQaRT){oosMswHFdY = true;}
      if(jyrtXDEVoi == nfZxKfnRWL){TqgfjUPOBi = true;}
      while(VLFsEZBHGG == mDMcaPxNCr){jQICrqcxhL = true;}
      while(gRHSpZQaRT == gRHSpZQaRT){XwSwmnVEQd = true;}
      while(nfZxKfnRWL == nfZxKfnRWL){RYAteUhTXF = true;}
      if(tizPOVfRra == true){tizPOVfRra = false;}
      if(jqedhoBzpq == true){jqedhoBzpq = false;}
      if(uHFZGpkIhX == true){uHFZGpkIhX = false;}
      if(kiktMxRqEU == true){kiktMxRqEU = false;}
      if(sziqixAwOV == true){sziqixAwOV = false;}
      if(eobePmdZJY == true){eobePmdZJY = false;}
      if(jXiToAGkRj == true){jXiToAGkRj = false;}
      if(WJtVywYOpJ == true){WJtVywYOpJ = false;}
      if(oosMswHFdY == true){oosMswHFdY = false;}
      if(TqgfjUPOBi == true){TqgfjUPOBi = false;}
      if(pPdeyUuFgT == true){pPdeyUuFgT = false;}
      if(OOjAiueWas == true){OOjAiueWas = false;}
      if(sBHrQecOlc == true){sBHrQecOlc = false;}
      if(gJMGSZKONX == true){gJMGSZKONX = false;}
      if(ACXJKEHfwo == true){ACXJKEHfwo = false;}
      if(psmIpoIkNS == true){psmIpoIkNS = false;}
      if(rfTDlECchJ == true){rfTDlECchJ = false;}
      if(jQICrqcxhL == true){jQICrqcxhL = false;}
      if(XwSwmnVEQd == true){XwSwmnVEQd = false;}
      if(RYAteUhTXF == true){RYAteUhTXF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQSDAMDZKA
{ 
  void hcthZlATLB()
  { 
      bool oCZQiuQXxB = false;
      bool eACjpQXXif = false;
      bool xxBTVdxAsy = false;
      bool woxbrMnHXG = false;
      bool SPLkjmqYUg = false;
      bool GKDaMqAFuE = false;
      bool yPezEoCard = false;
      bool cPzcMhlQjh = false;
      bool mYfLrklWOA = false;
      bool LhMTICjMft = false;
      bool jPfqDqKZNe = false;
      bool FjVMRYjSGS = false;
      bool DfLqRuCfUK = false;
      bool xZkoxWroIA = false;
      bool aLJjubMzBi = false;
      bool SQFMqEEoYI = false;
      bool neFDgezfOt = false;
      bool gtKGrqVaup = false;
      bool hCdlqfTXys = false;
      bool SCQzMuGGCP = false;
      string CHSiAwlmeR;
      string eBHdwwqdwb;
      string QaIUyZnglb;
      string scokMhtBCU;
      string nDmzbTClJL;
      string sWUbnbyykZ;
      string IEADXBMWQN;
      string BobamNmJrd;
      string XCWZhVIMwj;
      string jwQbMiCjaZ;
      string HeUuKEutoa;
      string onFGCFhaUC;
      string szZgdFYzOD;
      string KDhSWrhaPd;
      string ZOXVuupJZH;
      string BbOYfHEnRE;
      string fwekPkGmjJ;
      string XGKqbebEkh;
      string OOYHBinIlP;
      string nsIKydilGJ;
      if(CHSiAwlmeR == HeUuKEutoa){oCZQiuQXxB = true;}
      else if(HeUuKEutoa == CHSiAwlmeR){jPfqDqKZNe = true;}
      if(eBHdwwqdwb == onFGCFhaUC){eACjpQXXif = true;}
      else if(onFGCFhaUC == eBHdwwqdwb){FjVMRYjSGS = true;}
      if(QaIUyZnglb == szZgdFYzOD){xxBTVdxAsy = true;}
      else if(szZgdFYzOD == QaIUyZnglb){DfLqRuCfUK = true;}
      if(scokMhtBCU == KDhSWrhaPd){woxbrMnHXG = true;}
      else if(KDhSWrhaPd == scokMhtBCU){xZkoxWroIA = true;}
      if(nDmzbTClJL == ZOXVuupJZH){SPLkjmqYUg = true;}
      else if(ZOXVuupJZH == nDmzbTClJL){aLJjubMzBi = true;}
      if(sWUbnbyykZ == BbOYfHEnRE){GKDaMqAFuE = true;}
      else if(BbOYfHEnRE == sWUbnbyykZ){SQFMqEEoYI = true;}
      if(IEADXBMWQN == fwekPkGmjJ){yPezEoCard = true;}
      else if(fwekPkGmjJ == IEADXBMWQN){neFDgezfOt = true;}
      if(BobamNmJrd == XGKqbebEkh){cPzcMhlQjh = true;}
      if(XCWZhVIMwj == OOYHBinIlP){mYfLrklWOA = true;}
      if(jwQbMiCjaZ == nsIKydilGJ){LhMTICjMft = true;}
      while(XGKqbebEkh == BobamNmJrd){gtKGrqVaup = true;}
      while(OOYHBinIlP == OOYHBinIlP){hCdlqfTXys = true;}
      while(nsIKydilGJ == nsIKydilGJ){SCQzMuGGCP = true;}
      if(oCZQiuQXxB == true){oCZQiuQXxB = false;}
      if(eACjpQXXif == true){eACjpQXXif = false;}
      if(xxBTVdxAsy == true){xxBTVdxAsy = false;}
      if(woxbrMnHXG == true){woxbrMnHXG = false;}
      if(SPLkjmqYUg == true){SPLkjmqYUg = false;}
      if(GKDaMqAFuE == true){GKDaMqAFuE = false;}
      if(yPezEoCard == true){yPezEoCard = false;}
      if(cPzcMhlQjh == true){cPzcMhlQjh = false;}
      if(mYfLrklWOA == true){mYfLrklWOA = false;}
      if(LhMTICjMft == true){LhMTICjMft = false;}
      if(jPfqDqKZNe == true){jPfqDqKZNe = false;}
      if(FjVMRYjSGS == true){FjVMRYjSGS = false;}
      if(DfLqRuCfUK == true){DfLqRuCfUK = false;}
      if(xZkoxWroIA == true){xZkoxWroIA = false;}
      if(aLJjubMzBi == true){aLJjubMzBi = false;}
      if(SQFMqEEoYI == true){SQFMqEEoYI = false;}
      if(neFDgezfOt == true){neFDgezfOt = false;}
      if(gtKGrqVaup == true){gtKGrqVaup = false;}
      if(hCdlqfTXys == true){hCdlqfTXys = false;}
      if(SCQzMuGGCP == true){SCQzMuGGCP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXPMDNALWD
{ 
  void JmFDHkiCKH()
  { 
      bool ViadtCNaof = false;
      bool SmZMiwigqa = false;
      bool HqASlgITcz = false;
      bool cscuQINuKc = false;
      bool eOLMsnScAV = false;
      bool oEBVfdhHrN = false;
      bool styoDZJdua = false;
      bool hnVNwsfmYx = false;
      bool NeSGKYqHPm = false;
      bool ZGCxjkQWJT = false;
      bool enhZnAhnYm = false;
      bool ythtzNaqed = false;
      bool hBOIAblXdL = false;
      bool bJcFRZxrSJ = false;
      bool pDibneXHxW = false;
      bool JYrfkcZZYL = false;
      bool OJJMKoQbbZ = false;
      bool PhXUmeSlUU = false;
      bool EdaHCDQxUo = false;
      bool zXTHtfsVRy = false;
      string qMhkdqtEzH;
      string yVCMjwcBgt;
      string wtUdKhfOhO;
      string rYxQtNPdpI;
      string VDIjHhoyXb;
      string dklbVxrEau;
      string KfVjOZYkSW;
      string fyLYXrljVb;
      string rhpGjHlUtx;
      string VLDtxphXVh;
      string JDeAufZNEd;
      string LHhyCcoPAH;
      string mDpVBUtQag;
      string KNOnSoCoLE;
      string hYQQkNcFrU;
      string BRXOtGMJza;
      string kImWTxrteN;
      string ZzEwYOmZjm;
      string qnYFfrpAsM;
      string bspjSYkswn;
      if(qMhkdqtEzH == JDeAufZNEd){ViadtCNaof = true;}
      else if(JDeAufZNEd == qMhkdqtEzH){enhZnAhnYm = true;}
      if(yVCMjwcBgt == LHhyCcoPAH){SmZMiwigqa = true;}
      else if(LHhyCcoPAH == yVCMjwcBgt){ythtzNaqed = true;}
      if(wtUdKhfOhO == mDpVBUtQag){HqASlgITcz = true;}
      else if(mDpVBUtQag == wtUdKhfOhO){hBOIAblXdL = true;}
      if(rYxQtNPdpI == KNOnSoCoLE){cscuQINuKc = true;}
      else if(KNOnSoCoLE == rYxQtNPdpI){bJcFRZxrSJ = true;}
      if(VDIjHhoyXb == hYQQkNcFrU){eOLMsnScAV = true;}
      else if(hYQQkNcFrU == VDIjHhoyXb){pDibneXHxW = true;}
      if(dklbVxrEau == BRXOtGMJza){oEBVfdhHrN = true;}
      else if(BRXOtGMJza == dklbVxrEau){JYrfkcZZYL = true;}
      if(KfVjOZYkSW == kImWTxrteN){styoDZJdua = true;}
      else if(kImWTxrteN == KfVjOZYkSW){OJJMKoQbbZ = true;}
      if(fyLYXrljVb == ZzEwYOmZjm){hnVNwsfmYx = true;}
      if(rhpGjHlUtx == qnYFfrpAsM){NeSGKYqHPm = true;}
      if(VLDtxphXVh == bspjSYkswn){ZGCxjkQWJT = true;}
      while(ZzEwYOmZjm == fyLYXrljVb){PhXUmeSlUU = true;}
      while(qnYFfrpAsM == qnYFfrpAsM){EdaHCDQxUo = true;}
      while(bspjSYkswn == bspjSYkswn){zXTHtfsVRy = true;}
      if(ViadtCNaof == true){ViadtCNaof = false;}
      if(SmZMiwigqa == true){SmZMiwigqa = false;}
      if(HqASlgITcz == true){HqASlgITcz = false;}
      if(cscuQINuKc == true){cscuQINuKc = false;}
      if(eOLMsnScAV == true){eOLMsnScAV = false;}
      if(oEBVfdhHrN == true){oEBVfdhHrN = false;}
      if(styoDZJdua == true){styoDZJdua = false;}
      if(hnVNwsfmYx == true){hnVNwsfmYx = false;}
      if(NeSGKYqHPm == true){NeSGKYqHPm = false;}
      if(ZGCxjkQWJT == true){ZGCxjkQWJT = false;}
      if(enhZnAhnYm == true){enhZnAhnYm = false;}
      if(ythtzNaqed == true){ythtzNaqed = false;}
      if(hBOIAblXdL == true){hBOIAblXdL = false;}
      if(bJcFRZxrSJ == true){bJcFRZxrSJ = false;}
      if(pDibneXHxW == true){pDibneXHxW = false;}
      if(JYrfkcZZYL == true){JYrfkcZZYL = false;}
      if(OJJMKoQbbZ == true){OJJMKoQbbZ = false;}
      if(PhXUmeSlUU == true){PhXUmeSlUU = false;}
      if(EdaHCDQxUo == true){EdaHCDQxUo = false;}
      if(zXTHtfsVRy == true){zXTHtfsVRy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEMOVVFGVV
{ 
  void ZHqeVHHXCM()
  { 
      bool eFkDNoBmmw = false;
      bool MBZimJmiFz = false;
      bool jPkBcgTMWf = false;
      bool dhXytRFfbc = false;
      bool oMWkUxgrWS = false;
      bool JWedEPUiaf = false;
      bool VnQGRddanV = false;
      bool DHHcKWrzge = false;
      bool AaoDVHDste = false;
      bool wWEuHAuPSp = false;
      bool TFEBOCPBTg = false;
      bool XUBuftyMkJ = false;
      bool ajfJYgCLVJ = false;
      bool bbgqLtWnnT = false;
      bool rBZNHbUJPM = false;
      bool BieIPjZtbh = false;
      bool zDfKFunKjl = false;
      bool WKXQRYJRCx = false;
      bool MrwIHrwXab = false;
      bool TcLGTnUPIL = false;
      string InEGDQzJsU;
      string PtJYYxHoCp;
      string WiCOpxTumb;
      string RGgNTpwfPE;
      string VogPEUVcWJ;
      string mLMwnYkpQF;
      string xEWRDIMwFi;
      string BaYxUhClJU;
      string bpXdoGtkZt;
      string EFPJHQRPMu;
      string HYXmHLlObF;
      string WzgudGfsbx;
      string ObVKewKOpD;
      string PmZNMCSjVc;
      string TeITXEYTeA;
      string kYmPgfDMIL;
      string AWYXpjZSib;
      string muXzcjSBmZ;
      string XqioRpzJgg;
      string zGbKbxFkdn;
      if(InEGDQzJsU == HYXmHLlObF){eFkDNoBmmw = true;}
      else if(HYXmHLlObF == InEGDQzJsU){TFEBOCPBTg = true;}
      if(PtJYYxHoCp == WzgudGfsbx){MBZimJmiFz = true;}
      else if(WzgudGfsbx == PtJYYxHoCp){XUBuftyMkJ = true;}
      if(WiCOpxTumb == ObVKewKOpD){jPkBcgTMWf = true;}
      else if(ObVKewKOpD == WiCOpxTumb){ajfJYgCLVJ = true;}
      if(RGgNTpwfPE == PmZNMCSjVc){dhXytRFfbc = true;}
      else if(PmZNMCSjVc == RGgNTpwfPE){bbgqLtWnnT = true;}
      if(VogPEUVcWJ == TeITXEYTeA){oMWkUxgrWS = true;}
      else if(TeITXEYTeA == VogPEUVcWJ){rBZNHbUJPM = true;}
      if(mLMwnYkpQF == kYmPgfDMIL){JWedEPUiaf = true;}
      else if(kYmPgfDMIL == mLMwnYkpQF){BieIPjZtbh = true;}
      if(xEWRDIMwFi == AWYXpjZSib){VnQGRddanV = true;}
      else if(AWYXpjZSib == xEWRDIMwFi){zDfKFunKjl = true;}
      if(BaYxUhClJU == muXzcjSBmZ){DHHcKWrzge = true;}
      if(bpXdoGtkZt == XqioRpzJgg){AaoDVHDste = true;}
      if(EFPJHQRPMu == zGbKbxFkdn){wWEuHAuPSp = true;}
      while(muXzcjSBmZ == BaYxUhClJU){WKXQRYJRCx = true;}
      while(XqioRpzJgg == XqioRpzJgg){MrwIHrwXab = true;}
      while(zGbKbxFkdn == zGbKbxFkdn){TcLGTnUPIL = true;}
      if(eFkDNoBmmw == true){eFkDNoBmmw = false;}
      if(MBZimJmiFz == true){MBZimJmiFz = false;}
      if(jPkBcgTMWf == true){jPkBcgTMWf = false;}
      if(dhXytRFfbc == true){dhXytRFfbc = false;}
      if(oMWkUxgrWS == true){oMWkUxgrWS = false;}
      if(JWedEPUiaf == true){JWedEPUiaf = false;}
      if(VnQGRddanV == true){VnQGRddanV = false;}
      if(DHHcKWrzge == true){DHHcKWrzge = false;}
      if(AaoDVHDste == true){AaoDVHDste = false;}
      if(wWEuHAuPSp == true){wWEuHAuPSp = false;}
      if(TFEBOCPBTg == true){TFEBOCPBTg = false;}
      if(XUBuftyMkJ == true){XUBuftyMkJ = false;}
      if(ajfJYgCLVJ == true){ajfJYgCLVJ = false;}
      if(bbgqLtWnnT == true){bbgqLtWnnT = false;}
      if(rBZNHbUJPM == true){rBZNHbUJPM = false;}
      if(BieIPjZtbh == true){BieIPjZtbh = false;}
      if(zDfKFunKjl == true){zDfKFunKjl = false;}
      if(WKXQRYJRCx == true){WKXQRYJRCx = false;}
      if(MrwIHrwXab == true){MrwIHrwXab = false;}
      if(TcLGTnUPIL == true){TcLGTnUPIL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRFOYZORYI
{ 
  void zgCjPxAMkA()
  { 
      bool psZoYRuAuA = false;
      bool VFbHuVSEHS = false;
      bool MRmbOOGsab = false;
      bool CLkpGAjFWJ = false;
      bool lcAXlUkMaX = false;
      bool areNMXFxaK = false;
      bool KCZTxKTlAu = false;
      bool lMhygiQPot = false;
      bool dsRDAJfXdh = false;
      bool tleMyiDgZb = false;
      bool ByMfkNKggc = false;
      bool GpIfgQkVSn = false;
      bool ewISAAhUAx = false;
      bool ejoNregkRm = false;
      bool yzpAaEdyeg = false;
      bool ygNlxFosfk = false;
      bool fpfjyWAtnB = false;
      bool jzEfoeFIqu = false;
      bool VioSyxVDPm = false;
      bool onFgGISGBE = false;
      string EiktZduKsO;
      string VsanGtETMm;
      string yArYJRZQgW;
      string iYuAHXDJZj;
      string XQleyoxBmf;
      string uiaTZDpMjH;
      string DdcVfxxZgh;
      string qtscPgONZU;
      string UYdBazxbZD;
      string gqZRftmPyA;
      string qWUEoBpyEs;
      string oclOmeAbtf;
      string zVzcAzUawU;
      string syOZdxDYMZ;
      string JzWgOEFKeA;
      string sLUSBUXqDo;
      string fOBiApOLko;
      string abPUWAyROw;
      string tJuwagdwYI;
      string ZMUWttxmgY;
      if(EiktZduKsO == qWUEoBpyEs){psZoYRuAuA = true;}
      else if(qWUEoBpyEs == EiktZduKsO){ByMfkNKggc = true;}
      if(VsanGtETMm == oclOmeAbtf){VFbHuVSEHS = true;}
      else if(oclOmeAbtf == VsanGtETMm){GpIfgQkVSn = true;}
      if(yArYJRZQgW == zVzcAzUawU){MRmbOOGsab = true;}
      else if(zVzcAzUawU == yArYJRZQgW){ewISAAhUAx = true;}
      if(iYuAHXDJZj == syOZdxDYMZ){CLkpGAjFWJ = true;}
      else if(syOZdxDYMZ == iYuAHXDJZj){ejoNregkRm = true;}
      if(XQleyoxBmf == JzWgOEFKeA){lcAXlUkMaX = true;}
      else if(JzWgOEFKeA == XQleyoxBmf){yzpAaEdyeg = true;}
      if(uiaTZDpMjH == sLUSBUXqDo){areNMXFxaK = true;}
      else if(sLUSBUXqDo == uiaTZDpMjH){ygNlxFosfk = true;}
      if(DdcVfxxZgh == fOBiApOLko){KCZTxKTlAu = true;}
      else if(fOBiApOLko == DdcVfxxZgh){fpfjyWAtnB = true;}
      if(qtscPgONZU == abPUWAyROw){lMhygiQPot = true;}
      if(UYdBazxbZD == tJuwagdwYI){dsRDAJfXdh = true;}
      if(gqZRftmPyA == ZMUWttxmgY){tleMyiDgZb = true;}
      while(abPUWAyROw == qtscPgONZU){jzEfoeFIqu = true;}
      while(tJuwagdwYI == tJuwagdwYI){VioSyxVDPm = true;}
      while(ZMUWttxmgY == ZMUWttxmgY){onFgGISGBE = true;}
      if(psZoYRuAuA == true){psZoYRuAuA = false;}
      if(VFbHuVSEHS == true){VFbHuVSEHS = false;}
      if(MRmbOOGsab == true){MRmbOOGsab = false;}
      if(CLkpGAjFWJ == true){CLkpGAjFWJ = false;}
      if(lcAXlUkMaX == true){lcAXlUkMaX = false;}
      if(areNMXFxaK == true){areNMXFxaK = false;}
      if(KCZTxKTlAu == true){KCZTxKTlAu = false;}
      if(lMhygiQPot == true){lMhygiQPot = false;}
      if(dsRDAJfXdh == true){dsRDAJfXdh = false;}
      if(tleMyiDgZb == true){tleMyiDgZb = false;}
      if(ByMfkNKggc == true){ByMfkNKggc = false;}
      if(GpIfgQkVSn == true){GpIfgQkVSn = false;}
      if(ewISAAhUAx == true){ewISAAhUAx = false;}
      if(ejoNregkRm == true){ejoNregkRm = false;}
      if(yzpAaEdyeg == true){yzpAaEdyeg = false;}
      if(ygNlxFosfk == true){ygNlxFosfk = false;}
      if(fpfjyWAtnB == true){fpfjyWAtnB = false;}
      if(jzEfoeFIqu == true){jzEfoeFIqu = false;}
      if(VioSyxVDPm == true){VioSyxVDPm = false;}
      if(onFgGISGBE == true){onFgGISGBE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LLCBMBJUVT
{ 
  void aRUFmzNqWe()
  { 
      bool cDKVaQXFSl = false;
      bool atTBqLQGoW = false;
      bool BaExdpnehY = false;
      bool JFfTFJRxdA = false;
      bool mIWuEqkoGe = false;
      bool wtOMRByNrk = false;
      bool bsWtcVOzug = false;
      bool tTbnirEJrm = false;
      bool FzYDbPpSBE = false;
      bool LDFsYslbSi = false;
      bool cktZjcRZcZ = false;
      bool woUFfbUSSM = false;
      bool fuxpUpOiPo = false;
      bool GbpJKTFySy = false;
      bool yPobHWiANw = false;
      bool YSJGDgmDEt = false;
      bool OiKmSTzLuL = false;
      bool WVATOPFViy = false;
      bool GOUSQnSjGc = false;
      bool gCtYjOECIm = false;
      string RJLzNWZVSH;
      string WToetlusaF;
      string OmHthRbifh;
      string gwQxTJYyrW;
      string qVPSuKgnwU;
      string AqtildCQQu;
      string tppjaaDqLj;
      string MxBENrXnzX;
      string knlKhoCgKo;
      string HIgwbAffrU;
      string GocMIDpoUt;
      string GNRsKGEeCl;
      string XVfVcEPFbN;
      string MqweQuLZCd;
      string zNLQhtpmlV;
      string uBdGwkJGiE;
      string nkMHhORmcP;
      string tecXmKJOmh;
      string NbTFRKNphf;
      string kEpxpNAEiS;
      if(RJLzNWZVSH == GocMIDpoUt){cDKVaQXFSl = true;}
      else if(GocMIDpoUt == RJLzNWZVSH){cktZjcRZcZ = true;}
      if(WToetlusaF == GNRsKGEeCl){atTBqLQGoW = true;}
      else if(GNRsKGEeCl == WToetlusaF){woUFfbUSSM = true;}
      if(OmHthRbifh == XVfVcEPFbN){BaExdpnehY = true;}
      else if(XVfVcEPFbN == OmHthRbifh){fuxpUpOiPo = true;}
      if(gwQxTJYyrW == MqweQuLZCd){JFfTFJRxdA = true;}
      else if(MqweQuLZCd == gwQxTJYyrW){GbpJKTFySy = true;}
      if(qVPSuKgnwU == zNLQhtpmlV){mIWuEqkoGe = true;}
      else if(zNLQhtpmlV == qVPSuKgnwU){yPobHWiANw = true;}
      if(AqtildCQQu == uBdGwkJGiE){wtOMRByNrk = true;}
      else if(uBdGwkJGiE == AqtildCQQu){YSJGDgmDEt = true;}
      if(tppjaaDqLj == nkMHhORmcP){bsWtcVOzug = true;}
      else if(nkMHhORmcP == tppjaaDqLj){OiKmSTzLuL = true;}
      if(MxBENrXnzX == tecXmKJOmh){tTbnirEJrm = true;}
      if(knlKhoCgKo == NbTFRKNphf){FzYDbPpSBE = true;}
      if(HIgwbAffrU == kEpxpNAEiS){LDFsYslbSi = true;}
      while(tecXmKJOmh == MxBENrXnzX){WVATOPFViy = true;}
      while(NbTFRKNphf == NbTFRKNphf){GOUSQnSjGc = true;}
      while(kEpxpNAEiS == kEpxpNAEiS){gCtYjOECIm = true;}
      if(cDKVaQXFSl == true){cDKVaQXFSl = false;}
      if(atTBqLQGoW == true){atTBqLQGoW = false;}
      if(BaExdpnehY == true){BaExdpnehY = false;}
      if(JFfTFJRxdA == true){JFfTFJRxdA = false;}
      if(mIWuEqkoGe == true){mIWuEqkoGe = false;}
      if(wtOMRByNrk == true){wtOMRByNrk = false;}
      if(bsWtcVOzug == true){bsWtcVOzug = false;}
      if(tTbnirEJrm == true){tTbnirEJrm = false;}
      if(FzYDbPpSBE == true){FzYDbPpSBE = false;}
      if(LDFsYslbSi == true){LDFsYslbSi = false;}
      if(cktZjcRZcZ == true){cktZjcRZcZ = false;}
      if(woUFfbUSSM == true){woUFfbUSSM = false;}
      if(fuxpUpOiPo == true){fuxpUpOiPo = false;}
      if(GbpJKTFySy == true){GbpJKTFySy = false;}
      if(yPobHWiANw == true){yPobHWiANw = false;}
      if(YSJGDgmDEt == true){YSJGDgmDEt = false;}
      if(OiKmSTzLuL == true){OiKmSTzLuL = false;}
      if(WVATOPFViy == true){WVATOPFViy = false;}
      if(GOUSQnSjGc == true){GOUSQnSjGc = false;}
      if(gCtYjOECIm == true){gCtYjOECIm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSBKJQKLXG
{ 
  void uYcimmnVyc()
  { 
      bool wVatPtkCdg = false;
      bool sSLGrVqkwo = false;
      bool zBNHdptCXF = false;
      bool dDPCHwztjT = false;
      bool sXRRehswQB = false;
      bool JmuFguHSQY = false;
      bool zidYDpCJyw = false;
      bool WwBbwaiwbu = false;
      bool xylVwpHJVM = false;
      bool ofdKTKtsOo = false;
      bool fjxUeNlSJF = false;
      bool LLqUbBwHbM = false;
      bool hrmkHpRpHl = false;
      bool goglPMARqi = false;
      bool EoAPAcoIiS = false;
      bool NlQCGmwMNn = false;
      bool uuKWXWdEFO = false;
      bool AeQsHsrXjd = false;
      bool BIGoYuXefb = false;
      bool PmDCmJdcqd = false;
      string CIaneFYuZa;
      string pzJmQrYaMh;
      string EQfxxiVueK;
      string PWkTqyJqdr;
      string cwdfQzwhaw;
      string LpPTGkcdqu;
      string jcPPLSOpwS;
      string hgwTEImAfy;
      string lmThyZGRNF;
      string VfAhIzfOUx;
      string kGlHNdswOx;
      string ybxsJxJhQk;
      string MxbpxCgNLE;
      string cXeiMeAMUU;
      string fJCQGsiGYL;
      string pyyijnduKL;
      string wfkKUZxNfd;
      string wwMuFCtLiE;
      string SZozNeZwzY;
      string AFCJXAYqug;
      if(CIaneFYuZa == kGlHNdswOx){wVatPtkCdg = true;}
      else if(kGlHNdswOx == CIaneFYuZa){fjxUeNlSJF = true;}
      if(pzJmQrYaMh == ybxsJxJhQk){sSLGrVqkwo = true;}
      else if(ybxsJxJhQk == pzJmQrYaMh){LLqUbBwHbM = true;}
      if(EQfxxiVueK == MxbpxCgNLE){zBNHdptCXF = true;}
      else if(MxbpxCgNLE == EQfxxiVueK){hrmkHpRpHl = true;}
      if(PWkTqyJqdr == cXeiMeAMUU){dDPCHwztjT = true;}
      else if(cXeiMeAMUU == PWkTqyJqdr){goglPMARqi = true;}
      if(cwdfQzwhaw == fJCQGsiGYL){sXRRehswQB = true;}
      else if(fJCQGsiGYL == cwdfQzwhaw){EoAPAcoIiS = true;}
      if(LpPTGkcdqu == pyyijnduKL){JmuFguHSQY = true;}
      else if(pyyijnduKL == LpPTGkcdqu){NlQCGmwMNn = true;}
      if(jcPPLSOpwS == wfkKUZxNfd){zidYDpCJyw = true;}
      else if(wfkKUZxNfd == jcPPLSOpwS){uuKWXWdEFO = true;}
      if(hgwTEImAfy == wwMuFCtLiE){WwBbwaiwbu = true;}
      if(lmThyZGRNF == SZozNeZwzY){xylVwpHJVM = true;}
      if(VfAhIzfOUx == AFCJXAYqug){ofdKTKtsOo = true;}
      while(wwMuFCtLiE == hgwTEImAfy){AeQsHsrXjd = true;}
      while(SZozNeZwzY == SZozNeZwzY){BIGoYuXefb = true;}
      while(AFCJXAYqug == AFCJXAYqug){PmDCmJdcqd = true;}
      if(wVatPtkCdg == true){wVatPtkCdg = false;}
      if(sSLGrVqkwo == true){sSLGrVqkwo = false;}
      if(zBNHdptCXF == true){zBNHdptCXF = false;}
      if(dDPCHwztjT == true){dDPCHwztjT = false;}
      if(sXRRehswQB == true){sXRRehswQB = false;}
      if(JmuFguHSQY == true){JmuFguHSQY = false;}
      if(zidYDpCJyw == true){zidYDpCJyw = false;}
      if(WwBbwaiwbu == true){WwBbwaiwbu = false;}
      if(xylVwpHJVM == true){xylVwpHJVM = false;}
      if(ofdKTKtsOo == true){ofdKTKtsOo = false;}
      if(fjxUeNlSJF == true){fjxUeNlSJF = false;}
      if(LLqUbBwHbM == true){LLqUbBwHbM = false;}
      if(hrmkHpRpHl == true){hrmkHpRpHl = false;}
      if(goglPMARqi == true){goglPMARqi = false;}
      if(EoAPAcoIiS == true){EoAPAcoIiS = false;}
      if(NlQCGmwMNn == true){NlQCGmwMNn = false;}
      if(uuKWXWdEFO == true){uuKWXWdEFO = false;}
      if(AeQsHsrXjd == true){AeQsHsrXjd = false;}
      if(BIGoYuXefb == true){BIGoYuXefb = false;}
      if(PmDCmJdcqd == true){PmDCmJdcqd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNSQWKGEGA
{ 
  void lcVLyFGMoZ()
  { 
      bool KRoGFVRLXb = false;
      bool ymPxojeNIB = false;
      bool AFaNklnOiF = false;
      bool RHKOrGEKSN = false;
      bool xPqjuzKLLN = false;
      bool cjJQaEpaVT = false;
      bool gCcSJqcBEh = false;
      bool fTttDkOqSl = false;
      bool bcCVbhxtmn = false;
      bool QdozftmYZE = false;
      bool VJGdgJpOMp = false;
      bool pzIjrEzGqb = false;
      bool siNQRCeuOI = false;
      bool yoQOPRVYnR = false;
      bool qihwxQVFGa = false;
      bool ufhyKmupLe = false;
      bool duADrAisTZ = false;
      bool iaSYjJARTA = false;
      bool fYnmNRHRDb = false;
      bool WfMInwidDw = false;
      string xNhVTrIJhV;
      string FaaJMGdQfG;
      string FejxXNVIYb;
      string zrjSQdfSMe;
      string axIcDziqQR;
      string eydbVRcjxG;
      string VzkGVMqHri;
      string ZLDAfIWHtY;
      string eerGwBNHwy;
      string AuUGJbLCGp;
      string HazhrTtdwN;
      string uVpYaqHdJU;
      string zjLshdpxqE;
      string wTADQDeJOb;
      string GjKiDeFweR;
      string TgslqXPFAN;
      string dxlrQbUmHX;
      string LxPgNPYbpC;
      string YsRYjPaOLs;
      string mZJAyIxRRb;
      if(xNhVTrIJhV == HazhrTtdwN){KRoGFVRLXb = true;}
      else if(HazhrTtdwN == xNhVTrIJhV){VJGdgJpOMp = true;}
      if(FaaJMGdQfG == uVpYaqHdJU){ymPxojeNIB = true;}
      else if(uVpYaqHdJU == FaaJMGdQfG){pzIjrEzGqb = true;}
      if(FejxXNVIYb == zjLshdpxqE){AFaNklnOiF = true;}
      else if(zjLshdpxqE == FejxXNVIYb){siNQRCeuOI = true;}
      if(zrjSQdfSMe == wTADQDeJOb){RHKOrGEKSN = true;}
      else if(wTADQDeJOb == zrjSQdfSMe){yoQOPRVYnR = true;}
      if(axIcDziqQR == GjKiDeFweR){xPqjuzKLLN = true;}
      else if(GjKiDeFweR == axIcDziqQR){qihwxQVFGa = true;}
      if(eydbVRcjxG == TgslqXPFAN){cjJQaEpaVT = true;}
      else if(TgslqXPFAN == eydbVRcjxG){ufhyKmupLe = true;}
      if(VzkGVMqHri == dxlrQbUmHX){gCcSJqcBEh = true;}
      else if(dxlrQbUmHX == VzkGVMqHri){duADrAisTZ = true;}
      if(ZLDAfIWHtY == LxPgNPYbpC){fTttDkOqSl = true;}
      if(eerGwBNHwy == YsRYjPaOLs){bcCVbhxtmn = true;}
      if(AuUGJbLCGp == mZJAyIxRRb){QdozftmYZE = true;}
      while(LxPgNPYbpC == ZLDAfIWHtY){iaSYjJARTA = true;}
      while(YsRYjPaOLs == YsRYjPaOLs){fYnmNRHRDb = true;}
      while(mZJAyIxRRb == mZJAyIxRRb){WfMInwidDw = true;}
      if(KRoGFVRLXb == true){KRoGFVRLXb = false;}
      if(ymPxojeNIB == true){ymPxojeNIB = false;}
      if(AFaNklnOiF == true){AFaNklnOiF = false;}
      if(RHKOrGEKSN == true){RHKOrGEKSN = false;}
      if(xPqjuzKLLN == true){xPqjuzKLLN = false;}
      if(cjJQaEpaVT == true){cjJQaEpaVT = false;}
      if(gCcSJqcBEh == true){gCcSJqcBEh = false;}
      if(fTttDkOqSl == true){fTttDkOqSl = false;}
      if(bcCVbhxtmn == true){bcCVbhxtmn = false;}
      if(QdozftmYZE == true){QdozftmYZE = false;}
      if(VJGdgJpOMp == true){VJGdgJpOMp = false;}
      if(pzIjrEzGqb == true){pzIjrEzGqb = false;}
      if(siNQRCeuOI == true){siNQRCeuOI = false;}
      if(yoQOPRVYnR == true){yoQOPRVYnR = false;}
      if(qihwxQVFGa == true){qihwxQVFGa = false;}
      if(ufhyKmupLe == true){ufhyKmupLe = false;}
      if(duADrAisTZ == true){duADrAisTZ = false;}
      if(iaSYjJARTA == true){iaSYjJARTA = false;}
      if(fYnmNRHRDb == true){fYnmNRHRDb = false;}
      if(WfMInwidDw == true){WfMInwidDw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKJXCCIBMR
{ 
  void nGmaYqWoDl()
  { 
      bool RSwEUallNy = false;
      bool GecCyqcnaz = false;
      bool ASKQEnkENb = false;
      bool DyGaBiCqVw = false;
      bool dKrZYcZGOM = false;
      bool zZXPUzHfzf = false;
      bool pgYltHYBBP = false;
      bool nlSeUoajqb = false;
      bool NdpAcdZqFC = false;
      bool aWqoFwkGfQ = false;
      bool EYFzYMGstf = false;
      bool XWnXRMqXJP = false;
      bool ggwynQtcYX = false;
      bool DUEaWoXqbP = false;
      bool XgxZdDhTWs = false;
      bool FMxQiXcHKH = false;
      bool ScUVbDSNAb = false;
      bool nAwsrAiVTj = false;
      bool haFeSpWnqz = false;
      bool MPfUwtMbxa = false;
      string aTWSMasHJf;
      string kEXKnxqbFh;
      string sOWgJcnAGX;
      string hxWHdmQdXT;
      string qlAXQeRWkl;
      string urUirMxoIi;
      string lrBlxnhPgB;
      string fMDkqGNyQe;
      string LRPTbpcnPR;
      string paVogykNZb;
      string xBoiFhniqk;
      string yyYcWUbgKH;
      string LsAPLEqODs;
      string UAYohJcgOs;
      string CsweSqCrRM;
      string VEDSQDBYWA;
      string pZeyPxYjuN;
      string ruSQERxVwT;
      string CzwpWQxGYe;
      string IDJNDcNyOV;
      if(aTWSMasHJf == xBoiFhniqk){RSwEUallNy = true;}
      else if(xBoiFhniqk == aTWSMasHJf){EYFzYMGstf = true;}
      if(kEXKnxqbFh == yyYcWUbgKH){GecCyqcnaz = true;}
      else if(yyYcWUbgKH == kEXKnxqbFh){XWnXRMqXJP = true;}
      if(sOWgJcnAGX == LsAPLEqODs){ASKQEnkENb = true;}
      else if(LsAPLEqODs == sOWgJcnAGX){ggwynQtcYX = true;}
      if(hxWHdmQdXT == UAYohJcgOs){DyGaBiCqVw = true;}
      else if(UAYohJcgOs == hxWHdmQdXT){DUEaWoXqbP = true;}
      if(qlAXQeRWkl == CsweSqCrRM){dKrZYcZGOM = true;}
      else if(CsweSqCrRM == qlAXQeRWkl){XgxZdDhTWs = true;}
      if(urUirMxoIi == VEDSQDBYWA){zZXPUzHfzf = true;}
      else if(VEDSQDBYWA == urUirMxoIi){FMxQiXcHKH = true;}
      if(lrBlxnhPgB == pZeyPxYjuN){pgYltHYBBP = true;}
      else if(pZeyPxYjuN == lrBlxnhPgB){ScUVbDSNAb = true;}
      if(fMDkqGNyQe == ruSQERxVwT){nlSeUoajqb = true;}
      if(LRPTbpcnPR == CzwpWQxGYe){NdpAcdZqFC = true;}
      if(paVogykNZb == IDJNDcNyOV){aWqoFwkGfQ = true;}
      while(ruSQERxVwT == fMDkqGNyQe){nAwsrAiVTj = true;}
      while(CzwpWQxGYe == CzwpWQxGYe){haFeSpWnqz = true;}
      while(IDJNDcNyOV == IDJNDcNyOV){MPfUwtMbxa = true;}
      if(RSwEUallNy == true){RSwEUallNy = false;}
      if(GecCyqcnaz == true){GecCyqcnaz = false;}
      if(ASKQEnkENb == true){ASKQEnkENb = false;}
      if(DyGaBiCqVw == true){DyGaBiCqVw = false;}
      if(dKrZYcZGOM == true){dKrZYcZGOM = false;}
      if(zZXPUzHfzf == true){zZXPUzHfzf = false;}
      if(pgYltHYBBP == true){pgYltHYBBP = false;}
      if(nlSeUoajqb == true){nlSeUoajqb = false;}
      if(NdpAcdZqFC == true){NdpAcdZqFC = false;}
      if(aWqoFwkGfQ == true){aWqoFwkGfQ = false;}
      if(EYFzYMGstf == true){EYFzYMGstf = false;}
      if(XWnXRMqXJP == true){XWnXRMqXJP = false;}
      if(ggwynQtcYX == true){ggwynQtcYX = false;}
      if(DUEaWoXqbP == true){DUEaWoXqbP = false;}
      if(XgxZdDhTWs == true){XgxZdDhTWs = false;}
      if(FMxQiXcHKH == true){FMxQiXcHKH = false;}
      if(ScUVbDSNAb == true){ScUVbDSNAb = false;}
      if(nAwsrAiVTj == true){nAwsrAiVTj = false;}
      if(haFeSpWnqz == true){haFeSpWnqz = false;}
      if(MPfUwtMbxa == true){MPfUwtMbxa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UFASVJITTV
{ 
  void ApOEWPiQRG()
  { 
      bool qpiYRHlhgr = false;
      bool ltDrdGWSmQ = false;
      bool cVHQODqpTt = false;
      bool htBieIEbyX = false;
      bool ZBomtgmRCM = false;
      bool ejfMdUhSKO = false;
      bool QuOlJrrUNU = false;
      bool BuTOpafUVg = false;
      bool PYmGOxNoFJ = false;
      bool ZlQjGdmDcC = false;
      bool oSEhLjQRVC = false;
      bool oNwdyrIIXL = false;
      bool dDOEtOdjHM = false;
      bool ncqSrxUFtd = false;
      bool gwSCTMomlO = false;
      bool UeeRYkDzmw = false;
      bool GfJIOMWdlB = false;
      bool XDNsdhjMjh = false;
      bool ZpxsqIxZtG = false;
      bool sURxXAlJmH = false;
      string QoGlGFKXJP;
      string DZBXEoGbae;
      string DZttaFmrYd;
      string adeNbXmXGI;
      string DpAqetwyzI;
      string zKdjKquMLA;
      string SSyeoZumug;
      string CiVSaNZCPf;
      string JnrQePzuCk;
      string bZMFpkrUCE;
      string zIDSFQoLIx;
      string RrxepdahAY;
      string ZzjJEbVPbp;
      string VEAKgAjYKN;
      string amlFTicgOL;
      string JJUdezYsNc;
      string tYjSbMrmyp;
      string tBXlxlNepV;
      string znBQfLjWeg;
      string bqKgSCDScG;
      if(QoGlGFKXJP == zIDSFQoLIx){qpiYRHlhgr = true;}
      else if(zIDSFQoLIx == QoGlGFKXJP){oSEhLjQRVC = true;}
      if(DZBXEoGbae == RrxepdahAY){ltDrdGWSmQ = true;}
      else if(RrxepdahAY == DZBXEoGbae){oNwdyrIIXL = true;}
      if(DZttaFmrYd == ZzjJEbVPbp){cVHQODqpTt = true;}
      else if(ZzjJEbVPbp == DZttaFmrYd){dDOEtOdjHM = true;}
      if(adeNbXmXGI == VEAKgAjYKN){htBieIEbyX = true;}
      else if(VEAKgAjYKN == adeNbXmXGI){ncqSrxUFtd = true;}
      if(DpAqetwyzI == amlFTicgOL){ZBomtgmRCM = true;}
      else if(amlFTicgOL == DpAqetwyzI){gwSCTMomlO = true;}
      if(zKdjKquMLA == JJUdezYsNc){ejfMdUhSKO = true;}
      else if(JJUdezYsNc == zKdjKquMLA){UeeRYkDzmw = true;}
      if(SSyeoZumug == tYjSbMrmyp){QuOlJrrUNU = true;}
      else if(tYjSbMrmyp == SSyeoZumug){GfJIOMWdlB = true;}
      if(CiVSaNZCPf == tBXlxlNepV){BuTOpafUVg = true;}
      if(JnrQePzuCk == znBQfLjWeg){PYmGOxNoFJ = true;}
      if(bZMFpkrUCE == bqKgSCDScG){ZlQjGdmDcC = true;}
      while(tBXlxlNepV == CiVSaNZCPf){XDNsdhjMjh = true;}
      while(znBQfLjWeg == znBQfLjWeg){ZpxsqIxZtG = true;}
      while(bqKgSCDScG == bqKgSCDScG){sURxXAlJmH = true;}
      if(qpiYRHlhgr == true){qpiYRHlhgr = false;}
      if(ltDrdGWSmQ == true){ltDrdGWSmQ = false;}
      if(cVHQODqpTt == true){cVHQODqpTt = false;}
      if(htBieIEbyX == true){htBieIEbyX = false;}
      if(ZBomtgmRCM == true){ZBomtgmRCM = false;}
      if(ejfMdUhSKO == true){ejfMdUhSKO = false;}
      if(QuOlJrrUNU == true){QuOlJrrUNU = false;}
      if(BuTOpafUVg == true){BuTOpafUVg = false;}
      if(PYmGOxNoFJ == true){PYmGOxNoFJ = false;}
      if(ZlQjGdmDcC == true){ZlQjGdmDcC = false;}
      if(oSEhLjQRVC == true){oSEhLjQRVC = false;}
      if(oNwdyrIIXL == true){oNwdyrIIXL = false;}
      if(dDOEtOdjHM == true){dDOEtOdjHM = false;}
      if(ncqSrxUFtd == true){ncqSrxUFtd = false;}
      if(gwSCTMomlO == true){gwSCTMomlO = false;}
      if(UeeRYkDzmw == true){UeeRYkDzmw = false;}
      if(GfJIOMWdlB == true){GfJIOMWdlB = false;}
      if(XDNsdhjMjh == true){XDNsdhjMjh = false;}
      if(ZpxsqIxZtG == true){ZpxsqIxZtG = false;}
      if(sURxXAlJmH == true){sURxXAlJmH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHASLQGEMC
{ 
  void DUOneJFybR()
  { 
      bool aLlfLfkpCt = false;
      bool TlskAXZrqM = false;
      bool lZyRtqfRUN = false;
      bool pMtkHfruOV = false;
      bool gVDwGDMEDK = false;
      bool MCWjXANUkU = false;
      bool ATUnEGqIcT = false;
      bool eddUeQWBKq = false;
      bool dbNKBmoKMH = false;
      bool SXKsUNAPrA = false;
      bool LEaiehYBEG = false;
      bool dLJtqYFJmQ = false;
      bool QguUBHTjzR = false;
      bool PHJKfYAdfS = false;
      bool OnGGdHOPCw = false;
      bool HqbaieJFhX = false;
      bool NnClqVCzOR = false;
      bool YadTCcaoqt = false;
      bool rEhDKYehbA = false;
      bool PtwHEZkTOH = false;
      string zILRUoHbAL;
      string XXZWXhBscH;
      string XIRwJEDMaN;
      string mHkdElbAho;
      string YaUQtNqMuq;
      string OEqfAqpOIP;
      string ktBmXPluSl;
      string GBKnhxmBBu;
      string NqRiyiQEdN;
      string wNqSDdYhre;
      string autJkMsDxC;
      string DoMMCtcSno;
      string zhRFosJqjD;
      string XFIWTSwIxk;
      string oNHaJGAePJ;
      string BGsCfscoTr;
      string CBSsdyforj;
      string xUVDAkZqui;
      string rebZCRLFqZ;
      string oGoEhmuNwK;
      if(zILRUoHbAL == autJkMsDxC){aLlfLfkpCt = true;}
      else if(autJkMsDxC == zILRUoHbAL){LEaiehYBEG = true;}
      if(XXZWXhBscH == DoMMCtcSno){TlskAXZrqM = true;}
      else if(DoMMCtcSno == XXZWXhBscH){dLJtqYFJmQ = true;}
      if(XIRwJEDMaN == zhRFosJqjD){lZyRtqfRUN = true;}
      else if(zhRFosJqjD == XIRwJEDMaN){QguUBHTjzR = true;}
      if(mHkdElbAho == XFIWTSwIxk){pMtkHfruOV = true;}
      else if(XFIWTSwIxk == mHkdElbAho){PHJKfYAdfS = true;}
      if(YaUQtNqMuq == oNHaJGAePJ){gVDwGDMEDK = true;}
      else if(oNHaJGAePJ == YaUQtNqMuq){OnGGdHOPCw = true;}
      if(OEqfAqpOIP == BGsCfscoTr){MCWjXANUkU = true;}
      else if(BGsCfscoTr == OEqfAqpOIP){HqbaieJFhX = true;}
      if(ktBmXPluSl == CBSsdyforj){ATUnEGqIcT = true;}
      else if(CBSsdyforj == ktBmXPluSl){NnClqVCzOR = true;}
      if(GBKnhxmBBu == xUVDAkZqui){eddUeQWBKq = true;}
      if(NqRiyiQEdN == rebZCRLFqZ){dbNKBmoKMH = true;}
      if(wNqSDdYhre == oGoEhmuNwK){SXKsUNAPrA = true;}
      while(xUVDAkZqui == GBKnhxmBBu){YadTCcaoqt = true;}
      while(rebZCRLFqZ == rebZCRLFqZ){rEhDKYehbA = true;}
      while(oGoEhmuNwK == oGoEhmuNwK){PtwHEZkTOH = true;}
      if(aLlfLfkpCt == true){aLlfLfkpCt = false;}
      if(TlskAXZrqM == true){TlskAXZrqM = false;}
      if(lZyRtqfRUN == true){lZyRtqfRUN = false;}
      if(pMtkHfruOV == true){pMtkHfruOV = false;}
      if(gVDwGDMEDK == true){gVDwGDMEDK = false;}
      if(MCWjXANUkU == true){MCWjXANUkU = false;}
      if(ATUnEGqIcT == true){ATUnEGqIcT = false;}
      if(eddUeQWBKq == true){eddUeQWBKq = false;}
      if(dbNKBmoKMH == true){dbNKBmoKMH = false;}
      if(SXKsUNAPrA == true){SXKsUNAPrA = false;}
      if(LEaiehYBEG == true){LEaiehYBEG = false;}
      if(dLJtqYFJmQ == true){dLJtqYFJmQ = false;}
      if(QguUBHTjzR == true){QguUBHTjzR = false;}
      if(PHJKfYAdfS == true){PHJKfYAdfS = false;}
      if(OnGGdHOPCw == true){OnGGdHOPCw = false;}
      if(HqbaieJFhX == true){HqbaieJFhX = false;}
      if(NnClqVCzOR == true){NnClqVCzOR = false;}
      if(YadTCcaoqt == true){YadTCcaoqt = false;}
      if(rEhDKYehbA == true){rEhDKYehbA = false;}
      if(PtwHEZkTOH == true){PtwHEZkTOH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJUCAHRSDW
{ 
  void YluXHBrubA()
  { 
      bool MpQVXsDiBH = false;
      bool OghOfAeJwn = false;
      bool jHOiheuNRL = false;
      bool wFWUOGjTYT = false;
      bool JtcoGsKoJG = false;
      bool qfIwwEbhns = false;
      bool ypRoLIJMzY = false;
      bool QKjcepeZbo = false;
      bool UFEKUPxaXJ = false;
      bool eBeeVSbmcy = false;
      bool ixojpfufRG = false;
      bool YCGyYrlGUu = false;
      bool LinotOeFGL = false;
      bool NrwcFWPTUn = false;
      bool TRIRjcugGc = false;
      bool gVRhmAIApa = false;
      bool ApYGrgFcrB = false;
      bool bRlfbtaVER = false;
      bool TyycdrZOpF = false;
      bool NPdsncrBZD = false;
      string CqlKLqDtOx;
      string CBgFiWOApj;
      string zebSKmgzaz;
      string tbqdPMUVbE;
      string qzEJBLmWnd;
      string RNiKVXPSzX;
      string KETPDZJCoW;
      string BsXlsAZRRy;
      string zKKwgfrgIr;
      string wCVDtleoFa;
      string CjgQcXoxQV;
      string xxBAXzsXhX;
      string gbtxazWUqG;
      string UjLpwPctTI;
      string puPltyBVet;
      string sHHhsaojpd;
      string BUFKBNlKEI;
      string WzDYglLICb;
      string xBpwNMcdwV;
      string ZrDpHVoFkg;
      if(CqlKLqDtOx == CjgQcXoxQV){MpQVXsDiBH = true;}
      else if(CjgQcXoxQV == CqlKLqDtOx){ixojpfufRG = true;}
      if(CBgFiWOApj == xxBAXzsXhX){OghOfAeJwn = true;}
      else if(xxBAXzsXhX == CBgFiWOApj){YCGyYrlGUu = true;}
      if(zebSKmgzaz == gbtxazWUqG){jHOiheuNRL = true;}
      else if(gbtxazWUqG == zebSKmgzaz){LinotOeFGL = true;}
      if(tbqdPMUVbE == UjLpwPctTI){wFWUOGjTYT = true;}
      else if(UjLpwPctTI == tbqdPMUVbE){NrwcFWPTUn = true;}
      if(qzEJBLmWnd == puPltyBVet){JtcoGsKoJG = true;}
      else if(puPltyBVet == qzEJBLmWnd){TRIRjcugGc = true;}
      if(RNiKVXPSzX == sHHhsaojpd){qfIwwEbhns = true;}
      else if(sHHhsaojpd == RNiKVXPSzX){gVRhmAIApa = true;}
      if(KETPDZJCoW == BUFKBNlKEI){ypRoLIJMzY = true;}
      else if(BUFKBNlKEI == KETPDZJCoW){ApYGrgFcrB = true;}
      if(BsXlsAZRRy == WzDYglLICb){QKjcepeZbo = true;}
      if(zKKwgfrgIr == xBpwNMcdwV){UFEKUPxaXJ = true;}
      if(wCVDtleoFa == ZrDpHVoFkg){eBeeVSbmcy = true;}
      while(WzDYglLICb == BsXlsAZRRy){bRlfbtaVER = true;}
      while(xBpwNMcdwV == xBpwNMcdwV){TyycdrZOpF = true;}
      while(ZrDpHVoFkg == ZrDpHVoFkg){NPdsncrBZD = true;}
      if(MpQVXsDiBH == true){MpQVXsDiBH = false;}
      if(OghOfAeJwn == true){OghOfAeJwn = false;}
      if(jHOiheuNRL == true){jHOiheuNRL = false;}
      if(wFWUOGjTYT == true){wFWUOGjTYT = false;}
      if(JtcoGsKoJG == true){JtcoGsKoJG = false;}
      if(qfIwwEbhns == true){qfIwwEbhns = false;}
      if(ypRoLIJMzY == true){ypRoLIJMzY = false;}
      if(QKjcepeZbo == true){QKjcepeZbo = false;}
      if(UFEKUPxaXJ == true){UFEKUPxaXJ = false;}
      if(eBeeVSbmcy == true){eBeeVSbmcy = false;}
      if(ixojpfufRG == true){ixojpfufRG = false;}
      if(YCGyYrlGUu == true){YCGyYrlGUu = false;}
      if(LinotOeFGL == true){LinotOeFGL = false;}
      if(NrwcFWPTUn == true){NrwcFWPTUn = false;}
      if(TRIRjcugGc == true){TRIRjcugGc = false;}
      if(gVRhmAIApa == true){gVRhmAIApa = false;}
      if(ApYGrgFcrB == true){ApYGrgFcrB = false;}
      if(bRlfbtaVER == true){bRlfbtaVER = false;}
      if(TyycdrZOpF == true){TyycdrZOpF = false;}
      if(NPdsncrBZD == true){NPdsncrBZD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAGBJVIHMB
{ 
  void YUNYUHuHlH()
  { 
      bool bblNlfVRRx = false;
      bool oNXkjwZfBY = false;
      bool qHmChDDNEc = false;
      bool aTxmNDZsgM = false;
      bool NAUrlmskRi = false;
      bool BUeSFUnifh = false;
      bool cIMnWVPkWf = false;
      bool WgznLpluPt = false;
      bool JSwVbGoehr = false;
      bool PpMyjEnfVQ = false;
      bool XINkLTVpHO = false;
      bool hsTkXKMqMQ = false;
      bool fkDeQgTAEG = false;
      bool CGYzWBFKJH = false;
      bool kyXSJVWaZY = false;
      bool rxSFjlFhTe = false;
      bool AUlAMbTUOW = false;
      bool FBgEfhNjUt = false;
      bool KrZeNFmTOj = false;
      bool wWqeHPLWFh = false;
      string tXVPjUQFtU;
      string bhImFoXGAI;
      string FTcNoCAKFw;
      string QbnrLTFkSX;
      string hSYlzJHaZk;
      string WYCTPZtHah;
      string UGAxDztQbl;
      string jlncZmuqOf;
      string tYjTYrYTbk;
      string YyKjCaRahz;
      string OqzmBjjYsc;
      string eDrtmuVgYL;
      string aZnpMkbDZz;
      string UUIOQDZwRn;
      string HzZzGVFPxH;
      string FkCVYoCIaP;
      string IfztIJtddi;
      string UYOjEazojp;
      string fLGSsiSlpb;
      string BRVBfaAfqw;
      if(tXVPjUQFtU == OqzmBjjYsc){bblNlfVRRx = true;}
      else if(OqzmBjjYsc == tXVPjUQFtU){XINkLTVpHO = true;}
      if(bhImFoXGAI == eDrtmuVgYL){oNXkjwZfBY = true;}
      else if(eDrtmuVgYL == bhImFoXGAI){hsTkXKMqMQ = true;}
      if(FTcNoCAKFw == aZnpMkbDZz){qHmChDDNEc = true;}
      else if(aZnpMkbDZz == FTcNoCAKFw){fkDeQgTAEG = true;}
      if(QbnrLTFkSX == UUIOQDZwRn){aTxmNDZsgM = true;}
      else if(UUIOQDZwRn == QbnrLTFkSX){CGYzWBFKJH = true;}
      if(hSYlzJHaZk == HzZzGVFPxH){NAUrlmskRi = true;}
      else if(HzZzGVFPxH == hSYlzJHaZk){kyXSJVWaZY = true;}
      if(WYCTPZtHah == FkCVYoCIaP){BUeSFUnifh = true;}
      else if(FkCVYoCIaP == WYCTPZtHah){rxSFjlFhTe = true;}
      if(UGAxDztQbl == IfztIJtddi){cIMnWVPkWf = true;}
      else if(IfztIJtddi == UGAxDztQbl){AUlAMbTUOW = true;}
      if(jlncZmuqOf == UYOjEazojp){WgznLpluPt = true;}
      if(tYjTYrYTbk == fLGSsiSlpb){JSwVbGoehr = true;}
      if(YyKjCaRahz == BRVBfaAfqw){PpMyjEnfVQ = true;}
      while(UYOjEazojp == jlncZmuqOf){FBgEfhNjUt = true;}
      while(fLGSsiSlpb == fLGSsiSlpb){KrZeNFmTOj = true;}
      while(BRVBfaAfqw == BRVBfaAfqw){wWqeHPLWFh = true;}
      if(bblNlfVRRx == true){bblNlfVRRx = false;}
      if(oNXkjwZfBY == true){oNXkjwZfBY = false;}
      if(qHmChDDNEc == true){qHmChDDNEc = false;}
      if(aTxmNDZsgM == true){aTxmNDZsgM = false;}
      if(NAUrlmskRi == true){NAUrlmskRi = false;}
      if(BUeSFUnifh == true){BUeSFUnifh = false;}
      if(cIMnWVPkWf == true){cIMnWVPkWf = false;}
      if(WgznLpluPt == true){WgznLpluPt = false;}
      if(JSwVbGoehr == true){JSwVbGoehr = false;}
      if(PpMyjEnfVQ == true){PpMyjEnfVQ = false;}
      if(XINkLTVpHO == true){XINkLTVpHO = false;}
      if(hsTkXKMqMQ == true){hsTkXKMqMQ = false;}
      if(fkDeQgTAEG == true){fkDeQgTAEG = false;}
      if(CGYzWBFKJH == true){CGYzWBFKJH = false;}
      if(kyXSJVWaZY == true){kyXSJVWaZY = false;}
      if(rxSFjlFhTe == true){rxSFjlFhTe = false;}
      if(AUlAMbTUOW == true){AUlAMbTUOW = false;}
      if(FBgEfhNjUt == true){FBgEfhNjUt = false;}
      if(KrZeNFmTOj == true){KrZeNFmTOj = false;}
      if(wWqeHPLWFh == true){wWqeHPLWFh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KHXVYRWZFK
{ 
  void uzsTkdzTyM()
  { 
      bool IUSeIpyupH = false;
      bool aaGRjpespm = false;
      bool pxdiFlhCtQ = false;
      bool fHaFRIPenk = false;
      bool QwpTDSydhc = false;
      bool EtCfoKqjZV = false;
      bool HuAYaSzAAb = false;
      bool aAFEWsHJel = false;
      bool mEUQMlFuQG = false;
      bool QeEScUwQrk = false;
      bool SydFCEoxIu = false;
      bool DgEnhCaiMo = false;
      bool MEjsKuumbC = false;
      bool xpRsSoZOOH = false;
      bool xIlVCjaQjZ = false;
      bool tMDDYONjuG = false;
      bool ICVGxNPKUr = false;
      bool cLTErDSOqa = false;
      bool UeCBHklOUE = false;
      bool bpTIzumfXo = false;
      string OmJLkDQCaB;
      string SnZpqEaAHc;
      string cQrXCQZEBm;
      string UyKztlSKPS;
      string xWBAtMMlKD;
      string FPdqqyukJT;
      string cLAmgTcZuE;
      string kQjnfFOrco;
      string DnsygFUTIw;
      string qhAupkVOTa;
      string jmpGRoeoKl;
      string iDHTPoRCFb;
      string zIRyNDPoyt;
      string iAYCFQxmgr;
      string ZeIWNmZgeA;
      string TTIraaVqrN;
      string YpqQCheENz;
      string rdVNBTAukZ;
      string ciKxaOrgae;
      string tFuSSjnrTe;
      if(OmJLkDQCaB == jmpGRoeoKl){IUSeIpyupH = true;}
      else if(jmpGRoeoKl == OmJLkDQCaB){SydFCEoxIu = true;}
      if(SnZpqEaAHc == iDHTPoRCFb){aaGRjpespm = true;}
      else if(iDHTPoRCFb == SnZpqEaAHc){DgEnhCaiMo = true;}
      if(cQrXCQZEBm == zIRyNDPoyt){pxdiFlhCtQ = true;}
      else if(zIRyNDPoyt == cQrXCQZEBm){MEjsKuumbC = true;}
      if(UyKztlSKPS == iAYCFQxmgr){fHaFRIPenk = true;}
      else if(iAYCFQxmgr == UyKztlSKPS){xpRsSoZOOH = true;}
      if(xWBAtMMlKD == ZeIWNmZgeA){QwpTDSydhc = true;}
      else if(ZeIWNmZgeA == xWBAtMMlKD){xIlVCjaQjZ = true;}
      if(FPdqqyukJT == TTIraaVqrN){EtCfoKqjZV = true;}
      else if(TTIraaVqrN == FPdqqyukJT){tMDDYONjuG = true;}
      if(cLAmgTcZuE == YpqQCheENz){HuAYaSzAAb = true;}
      else if(YpqQCheENz == cLAmgTcZuE){ICVGxNPKUr = true;}
      if(kQjnfFOrco == rdVNBTAukZ){aAFEWsHJel = true;}
      if(DnsygFUTIw == ciKxaOrgae){mEUQMlFuQG = true;}
      if(qhAupkVOTa == tFuSSjnrTe){QeEScUwQrk = true;}
      while(rdVNBTAukZ == kQjnfFOrco){cLTErDSOqa = true;}
      while(ciKxaOrgae == ciKxaOrgae){UeCBHklOUE = true;}
      while(tFuSSjnrTe == tFuSSjnrTe){bpTIzumfXo = true;}
      if(IUSeIpyupH == true){IUSeIpyupH = false;}
      if(aaGRjpespm == true){aaGRjpespm = false;}
      if(pxdiFlhCtQ == true){pxdiFlhCtQ = false;}
      if(fHaFRIPenk == true){fHaFRIPenk = false;}
      if(QwpTDSydhc == true){QwpTDSydhc = false;}
      if(EtCfoKqjZV == true){EtCfoKqjZV = false;}
      if(HuAYaSzAAb == true){HuAYaSzAAb = false;}
      if(aAFEWsHJel == true){aAFEWsHJel = false;}
      if(mEUQMlFuQG == true){mEUQMlFuQG = false;}
      if(QeEScUwQrk == true){QeEScUwQrk = false;}
      if(SydFCEoxIu == true){SydFCEoxIu = false;}
      if(DgEnhCaiMo == true){DgEnhCaiMo = false;}
      if(MEjsKuumbC == true){MEjsKuumbC = false;}
      if(xpRsSoZOOH == true){xpRsSoZOOH = false;}
      if(xIlVCjaQjZ == true){xIlVCjaQjZ = false;}
      if(tMDDYONjuG == true){tMDDYONjuG = false;}
      if(ICVGxNPKUr == true){ICVGxNPKUr = false;}
      if(cLTErDSOqa == true){cLTErDSOqa = false;}
      if(UeCBHklOUE == true){UeCBHklOUE = false;}
      if(bpTIzumfXo == true){bpTIzumfXo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVURINBHGG
{ 
  void lxIeqCyCrG()
  { 
      bool rqrwRhEwlM = false;
      bool jrbhCPeCqP = false;
      bool UsmxFALqQN = false;
      bool ImWxpRRhTx = false;
      bool kFhVHbcxhc = false;
      bool hnOSMzDuqR = false;
      bool WNeYExVdqj = false;
      bool yxisdOKRpd = false;
      bool WOJneTXDjq = false;
      bool NVqBaWaJRJ = false;
      bool FyGxdkFVny = false;
      bool nlFMuIEptj = false;
      bool ZRtAWbGgSH = false;
      bool nBzfXXILJs = false;
      bool OBPlCaQdGR = false;
      bool SjPhjnEFaC = false;
      bool eYDgKmmYoW = false;
      bool ArfAUXCHxu = false;
      bool KbZAnDlRwi = false;
      bool SCkHOpyhbP = false;
      string AOAkAThKBh;
      string miULalLaCQ;
      string YicsDCCuLo;
      string FaDNxlkaLE;
      string yAtlEgwCti;
      string DYwuzQkGhy;
      string QmyMcLeGOo;
      string BkOxRXnpoW;
      string GzAckfeHOf;
      string AesNnLBgJs;
      string BonFhSJyda;
      string ctRKqQlVbw;
      string fWrhnVrAJF;
      string VGguVRLuuS;
      string VfdmDFNhWW;
      string YfFMMdxGQL;
      string ZIoXFVNVoZ;
      string FpaJazsEei;
      string IKdlfpBUir;
      string TEejrMqGhg;
      if(AOAkAThKBh == BonFhSJyda){rqrwRhEwlM = true;}
      else if(BonFhSJyda == AOAkAThKBh){FyGxdkFVny = true;}
      if(miULalLaCQ == ctRKqQlVbw){jrbhCPeCqP = true;}
      else if(ctRKqQlVbw == miULalLaCQ){nlFMuIEptj = true;}
      if(YicsDCCuLo == fWrhnVrAJF){UsmxFALqQN = true;}
      else if(fWrhnVrAJF == YicsDCCuLo){ZRtAWbGgSH = true;}
      if(FaDNxlkaLE == VGguVRLuuS){ImWxpRRhTx = true;}
      else if(VGguVRLuuS == FaDNxlkaLE){nBzfXXILJs = true;}
      if(yAtlEgwCti == VfdmDFNhWW){kFhVHbcxhc = true;}
      else if(VfdmDFNhWW == yAtlEgwCti){OBPlCaQdGR = true;}
      if(DYwuzQkGhy == YfFMMdxGQL){hnOSMzDuqR = true;}
      else if(YfFMMdxGQL == DYwuzQkGhy){SjPhjnEFaC = true;}
      if(QmyMcLeGOo == ZIoXFVNVoZ){WNeYExVdqj = true;}
      else if(ZIoXFVNVoZ == QmyMcLeGOo){eYDgKmmYoW = true;}
      if(BkOxRXnpoW == FpaJazsEei){yxisdOKRpd = true;}
      if(GzAckfeHOf == IKdlfpBUir){WOJneTXDjq = true;}
      if(AesNnLBgJs == TEejrMqGhg){NVqBaWaJRJ = true;}
      while(FpaJazsEei == BkOxRXnpoW){ArfAUXCHxu = true;}
      while(IKdlfpBUir == IKdlfpBUir){KbZAnDlRwi = true;}
      while(TEejrMqGhg == TEejrMqGhg){SCkHOpyhbP = true;}
      if(rqrwRhEwlM == true){rqrwRhEwlM = false;}
      if(jrbhCPeCqP == true){jrbhCPeCqP = false;}
      if(UsmxFALqQN == true){UsmxFALqQN = false;}
      if(ImWxpRRhTx == true){ImWxpRRhTx = false;}
      if(kFhVHbcxhc == true){kFhVHbcxhc = false;}
      if(hnOSMzDuqR == true){hnOSMzDuqR = false;}
      if(WNeYExVdqj == true){WNeYExVdqj = false;}
      if(yxisdOKRpd == true){yxisdOKRpd = false;}
      if(WOJneTXDjq == true){WOJneTXDjq = false;}
      if(NVqBaWaJRJ == true){NVqBaWaJRJ = false;}
      if(FyGxdkFVny == true){FyGxdkFVny = false;}
      if(nlFMuIEptj == true){nlFMuIEptj = false;}
      if(ZRtAWbGgSH == true){ZRtAWbGgSH = false;}
      if(nBzfXXILJs == true){nBzfXXILJs = false;}
      if(OBPlCaQdGR == true){OBPlCaQdGR = false;}
      if(SjPhjnEFaC == true){SjPhjnEFaC = false;}
      if(eYDgKmmYoW == true){eYDgKmmYoW = false;}
      if(ArfAUXCHxu == true){ArfAUXCHxu = false;}
      if(KbZAnDlRwi == true){KbZAnDlRwi = false;}
      if(SCkHOpyhbP == true){SCkHOpyhbP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKGGMPERHF
{ 
  void enPWnZOhHm()
  { 
      bool gIOOICoPPZ = false;
      bool SNyUWcUTJx = false;
      bool zaHirHPETk = false;
      bool yCuFIMCarW = false;
      bool TGzMnYxYbk = false;
      bool tKfCxFBfVB = false;
      bool lkueaQRrMK = false;
      bool ZtaldsautT = false;
      bool JqchqnVsIC = false;
      bool KVFqkhLTkX = false;
      bool HEMQLAitXE = false;
      bool eFlBquHMnm = false;
      bool tYjJzDnjAu = false;
      bool gGJVMFeLWp = false;
      bool EbUDXEjDzo = false;
      bool ayfxdhTCRH = false;
      bool LzsbWXwPol = false;
      bool QupxiRDflt = false;
      bool TkjLUiaMrd = false;
      bool kbtPeEisgz = false;
      string VISjWxjkxQ;
      string zfcxsGGLFS;
      string ZSNMflbzje;
      string UoWLOntTGf;
      string JmHnpkdHZc;
      string EzHdwCuGEj;
      string UkARwKJRiE;
      string MlFYJmKYVt;
      string IUYGaUhsOL;
      string snOVLXlorf;
      string bLXVQRthTI;
      string rVjJbzMsqa;
      string cQCWLYWiNk;
      string BUfpSwwDpI;
      string azYGTWDFtL;
      string LryQDKJBJr;
      string tKUiGWptpf;
      string CJDhAcruCo;
      string URoBZIWPlH;
      string musyOPdoAx;
      if(VISjWxjkxQ == bLXVQRthTI){gIOOICoPPZ = true;}
      else if(bLXVQRthTI == VISjWxjkxQ){HEMQLAitXE = true;}
      if(zfcxsGGLFS == rVjJbzMsqa){SNyUWcUTJx = true;}
      else if(rVjJbzMsqa == zfcxsGGLFS){eFlBquHMnm = true;}
      if(ZSNMflbzje == cQCWLYWiNk){zaHirHPETk = true;}
      else if(cQCWLYWiNk == ZSNMflbzje){tYjJzDnjAu = true;}
      if(UoWLOntTGf == BUfpSwwDpI){yCuFIMCarW = true;}
      else if(BUfpSwwDpI == UoWLOntTGf){gGJVMFeLWp = true;}
      if(JmHnpkdHZc == azYGTWDFtL){TGzMnYxYbk = true;}
      else if(azYGTWDFtL == JmHnpkdHZc){EbUDXEjDzo = true;}
      if(EzHdwCuGEj == LryQDKJBJr){tKfCxFBfVB = true;}
      else if(LryQDKJBJr == EzHdwCuGEj){ayfxdhTCRH = true;}
      if(UkARwKJRiE == tKUiGWptpf){lkueaQRrMK = true;}
      else if(tKUiGWptpf == UkARwKJRiE){LzsbWXwPol = true;}
      if(MlFYJmKYVt == CJDhAcruCo){ZtaldsautT = true;}
      if(IUYGaUhsOL == URoBZIWPlH){JqchqnVsIC = true;}
      if(snOVLXlorf == musyOPdoAx){KVFqkhLTkX = true;}
      while(CJDhAcruCo == MlFYJmKYVt){QupxiRDflt = true;}
      while(URoBZIWPlH == URoBZIWPlH){TkjLUiaMrd = true;}
      while(musyOPdoAx == musyOPdoAx){kbtPeEisgz = true;}
      if(gIOOICoPPZ == true){gIOOICoPPZ = false;}
      if(SNyUWcUTJx == true){SNyUWcUTJx = false;}
      if(zaHirHPETk == true){zaHirHPETk = false;}
      if(yCuFIMCarW == true){yCuFIMCarW = false;}
      if(TGzMnYxYbk == true){TGzMnYxYbk = false;}
      if(tKfCxFBfVB == true){tKfCxFBfVB = false;}
      if(lkueaQRrMK == true){lkueaQRrMK = false;}
      if(ZtaldsautT == true){ZtaldsautT = false;}
      if(JqchqnVsIC == true){JqchqnVsIC = false;}
      if(KVFqkhLTkX == true){KVFqkhLTkX = false;}
      if(HEMQLAitXE == true){HEMQLAitXE = false;}
      if(eFlBquHMnm == true){eFlBquHMnm = false;}
      if(tYjJzDnjAu == true){tYjJzDnjAu = false;}
      if(gGJVMFeLWp == true){gGJVMFeLWp = false;}
      if(EbUDXEjDzo == true){EbUDXEjDzo = false;}
      if(ayfxdhTCRH == true){ayfxdhTCRH = false;}
      if(LzsbWXwPol == true){LzsbWXwPol = false;}
      if(QupxiRDflt == true){QupxiRDflt = false;}
      if(TkjLUiaMrd == true){TkjLUiaMrd = false;}
      if(kbtPeEisgz == true){kbtPeEisgz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXIVJKHRKM
{ 
  void BSKBIGOZtI()
  { 
      bool rlKbgtmynh = false;
      bool XlCuRNVphN = false;
      bool yUlbhgOPTy = false;
      bool yucZTCQJoy = false;
      bool WACXhESCXn = false;
      bool OllzkWzhtz = false;
      bool eXdoicJbaP = false;
      bool xMBipxSOtd = false;
      bool OMqfjLJcow = false;
      bool DiPoTzWMnF = false;
      bool upbIpBjDIm = false;
      bool EjnQkSfyFW = false;
      bool SgldMOxMOq = false;
      bool aFZnhXjioh = false;
      bool bGTBqStyDA = false;
      bool SXGQlODxwb = false;
      bool EXnRLzKAhM = false;
      bool hxJXuMMklt = false;
      bool TyJNXDyIBT = false;
      bool TmmMcERBor = false;
      string GVmpgFnXQp;
      string aJdDHjhtQA;
      string UriqVQhryC;
      string VAcoMPgqLq;
      string XVsTBdsuOb;
      string BfrFaOmwUQ;
      string WwYNTZgopq;
      string CqiYczyOoq;
      string XmcVBpIWNy;
      string bjWuTawfAa;
      string xDEWYJwSbb;
      string QYGcsjTCMc;
      string RJbrPSUnFB;
      string DSNOtThFxq;
      string sptkhDdsBi;
      string HsTXJmbMHG;
      string oIMaXxKriY;
      string CNFUibOpKM;
      string nalVsKzpFG;
      string qUypBkcTNj;
      if(GVmpgFnXQp == xDEWYJwSbb){rlKbgtmynh = true;}
      else if(xDEWYJwSbb == GVmpgFnXQp){upbIpBjDIm = true;}
      if(aJdDHjhtQA == QYGcsjTCMc){XlCuRNVphN = true;}
      else if(QYGcsjTCMc == aJdDHjhtQA){EjnQkSfyFW = true;}
      if(UriqVQhryC == RJbrPSUnFB){yUlbhgOPTy = true;}
      else if(RJbrPSUnFB == UriqVQhryC){SgldMOxMOq = true;}
      if(VAcoMPgqLq == DSNOtThFxq){yucZTCQJoy = true;}
      else if(DSNOtThFxq == VAcoMPgqLq){aFZnhXjioh = true;}
      if(XVsTBdsuOb == sptkhDdsBi){WACXhESCXn = true;}
      else if(sptkhDdsBi == XVsTBdsuOb){bGTBqStyDA = true;}
      if(BfrFaOmwUQ == HsTXJmbMHG){OllzkWzhtz = true;}
      else if(HsTXJmbMHG == BfrFaOmwUQ){SXGQlODxwb = true;}
      if(WwYNTZgopq == oIMaXxKriY){eXdoicJbaP = true;}
      else if(oIMaXxKriY == WwYNTZgopq){EXnRLzKAhM = true;}
      if(CqiYczyOoq == CNFUibOpKM){xMBipxSOtd = true;}
      if(XmcVBpIWNy == nalVsKzpFG){OMqfjLJcow = true;}
      if(bjWuTawfAa == qUypBkcTNj){DiPoTzWMnF = true;}
      while(CNFUibOpKM == CqiYczyOoq){hxJXuMMklt = true;}
      while(nalVsKzpFG == nalVsKzpFG){TyJNXDyIBT = true;}
      while(qUypBkcTNj == qUypBkcTNj){TmmMcERBor = true;}
      if(rlKbgtmynh == true){rlKbgtmynh = false;}
      if(XlCuRNVphN == true){XlCuRNVphN = false;}
      if(yUlbhgOPTy == true){yUlbhgOPTy = false;}
      if(yucZTCQJoy == true){yucZTCQJoy = false;}
      if(WACXhESCXn == true){WACXhESCXn = false;}
      if(OllzkWzhtz == true){OllzkWzhtz = false;}
      if(eXdoicJbaP == true){eXdoicJbaP = false;}
      if(xMBipxSOtd == true){xMBipxSOtd = false;}
      if(OMqfjLJcow == true){OMqfjLJcow = false;}
      if(DiPoTzWMnF == true){DiPoTzWMnF = false;}
      if(upbIpBjDIm == true){upbIpBjDIm = false;}
      if(EjnQkSfyFW == true){EjnQkSfyFW = false;}
      if(SgldMOxMOq == true){SgldMOxMOq = false;}
      if(aFZnhXjioh == true){aFZnhXjioh = false;}
      if(bGTBqStyDA == true){bGTBqStyDA = false;}
      if(SXGQlODxwb == true){SXGQlODxwb = false;}
      if(EXnRLzKAhM == true){EXnRLzKAhM = false;}
      if(hxJXuMMklt == true){hxJXuMMklt = false;}
      if(TyJNXDyIBT == true){TyJNXDyIBT = false;}
      if(TmmMcERBor == true){TmmMcERBor = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMIKWQLRVQ
{ 
  void yHmfrSSuVP()
  { 
      bool cOQtcBXwXZ = false;
      bool EThpIpopKQ = false;
      bool QICfXZYrDK = false;
      bool brLcJRGbjx = false;
      bool NrHQtSugOj = false;
      bool HQFhHUMkWD = false;
      bool bfrNyLHFgp = false;
      bool jMGMCXAlkF = false;
      bool drcTDKmcUo = false;
      bool FUFgVhAsRi = false;
      bool KpAYAtKrfj = false;
      bool TazQYjCYKn = false;
      bool XejqkOHZqU = false;
      bool XGTCtmqETJ = false;
      bool AtxkVdVnHk = false;
      bool ebidKfGIml = false;
      bool lkAKLMGxWl = false;
      bool ryFBncgyVG = false;
      bool sTRFouWprO = false;
      bool ghQgWOslZI = false;
      string LKEEOeJhly;
      string zkaImngUpQ;
      string VjGIJhffNB;
      string oxZnaTxeMy;
      string YicCFEbzzV;
      string htowMbDwtg;
      string zdTkIBKlgS;
      string qCHrqmGEDF;
      string FgfrStHcaz;
      string PBjfyuOrsD;
      string toRfeemwEZ;
      string UzsoaSxbRO;
      string tgLgDoRbsw;
      string XOKzLQOAMm;
      string HKXAeQIuFf;
      string ymZeJMdjco;
      string NLDIBFnsdK;
      string DwOdGiIKCl;
      string gWWMyknfpy;
      string ldXWZwHPzY;
      if(LKEEOeJhly == toRfeemwEZ){cOQtcBXwXZ = true;}
      else if(toRfeemwEZ == LKEEOeJhly){KpAYAtKrfj = true;}
      if(zkaImngUpQ == UzsoaSxbRO){EThpIpopKQ = true;}
      else if(UzsoaSxbRO == zkaImngUpQ){TazQYjCYKn = true;}
      if(VjGIJhffNB == tgLgDoRbsw){QICfXZYrDK = true;}
      else if(tgLgDoRbsw == VjGIJhffNB){XejqkOHZqU = true;}
      if(oxZnaTxeMy == XOKzLQOAMm){brLcJRGbjx = true;}
      else if(XOKzLQOAMm == oxZnaTxeMy){XGTCtmqETJ = true;}
      if(YicCFEbzzV == HKXAeQIuFf){NrHQtSugOj = true;}
      else if(HKXAeQIuFf == YicCFEbzzV){AtxkVdVnHk = true;}
      if(htowMbDwtg == ymZeJMdjco){HQFhHUMkWD = true;}
      else if(ymZeJMdjco == htowMbDwtg){ebidKfGIml = true;}
      if(zdTkIBKlgS == NLDIBFnsdK){bfrNyLHFgp = true;}
      else if(NLDIBFnsdK == zdTkIBKlgS){lkAKLMGxWl = true;}
      if(qCHrqmGEDF == DwOdGiIKCl){jMGMCXAlkF = true;}
      if(FgfrStHcaz == gWWMyknfpy){drcTDKmcUo = true;}
      if(PBjfyuOrsD == ldXWZwHPzY){FUFgVhAsRi = true;}
      while(DwOdGiIKCl == qCHrqmGEDF){ryFBncgyVG = true;}
      while(gWWMyknfpy == gWWMyknfpy){sTRFouWprO = true;}
      while(ldXWZwHPzY == ldXWZwHPzY){ghQgWOslZI = true;}
      if(cOQtcBXwXZ == true){cOQtcBXwXZ = false;}
      if(EThpIpopKQ == true){EThpIpopKQ = false;}
      if(QICfXZYrDK == true){QICfXZYrDK = false;}
      if(brLcJRGbjx == true){brLcJRGbjx = false;}
      if(NrHQtSugOj == true){NrHQtSugOj = false;}
      if(HQFhHUMkWD == true){HQFhHUMkWD = false;}
      if(bfrNyLHFgp == true){bfrNyLHFgp = false;}
      if(jMGMCXAlkF == true){jMGMCXAlkF = false;}
      if(drcTDKmcUo == true){drcTDKmcUo = false;}
      if(FUFgVhAsRi == true){FUFgVhAsRi = false;}
      if(KpAYAtKrfj == true){KpAYAtKrfj = false;}
      if(TazQYjCYKn == true){TazQYjCYKn = false;}
      if(XejqkOHZqU == true){XejqkOHZqU = false;}
      if(XGTCtmqETJ == true){XGTCtmqETJ = false;}
      if(AtxkVdVnHk == true){AtxkVdVnHk = false;}
      if(ebidKfGIml == true){ebidKfGIml = false;}
      if(lkAKLMGxWl == true){lkAKLMGxWl = false;}
      if(ryFBncgyVG == true){ryFBncgyVG = false;}
      if(sTRFouWprO == true){sTRFouWprO = false;}
      if(ghQgWOslZI == true){ghQgWOslZI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZICPXSKIW
{ 
  void icayeNGQiU()
  { 
      bool CuDtVXGbVc = false;
      bool NXexgcOrlr = false;
      bool AiIYFFFTWA = false;
      bool hVCIdmrGdl = false;
      bool wFAmfociya = false;
      bool FAGMOTldoQ = false;
      bool SlEVtqUVSt = false;
      bool jHOAwuiUsP = false;
      bool bVVuthOptK = false;
      bool AORMTJAdsn = false;
      bool TGQDqykGPT = false;
      bool jQjYnwQJbM = false;
      bool bebHtUoBfm = false;
      bool tEbEwUERDu = false;
      bool wIZZZidsYW = false;
      bool spCfLneIJV = false;
      bool JjZcYeoecS = false;
      bool qyFgPTEBgK = false;
      bool qwcJsECusH = false;
      bool pwIhkMhxAu = false;
      string PwFmTropIu;
      string ELYsQBeyEL;
      string KNWbudkNll;
      string cdANNAoCMN;
      string iDZOqryCib;
      string SORsKCZcqp;
      string GaDVSZLLeP;
      string MckpbHmIkC;
      string ehdKSNMGDL;
      string aLKWHHzEuQ;
      string gmXTPpdaQD;
      string PRrnKXxsCE;
      string MEHToARNiU;
      string HhMTVrKKtb;
      string jkoAwISVMi;
      string KFBpEbeDdO;
      string YPrwugFXSR;
      string MlzZUaOHXg;
      string hwBzKCgVPs;
      string MHgeDUssFO;
      if(PwFmTropIu == gmXTPpdaQD){CuDtVXGbVc = true;}
      else if(gmXTPpdaQD == PwFmTropIu){TGQDqykGPT = true;}
      if(ELYsQBeyEL == PRrnKXxsCE){NXexgcOrlr = true;}
      else if(PRrnKXxsCE == ELYsQBeyEL){jQjYnwQJbM = true;}
      if(KNWbudkNll == MEHToARNiU){AiIYFFFTWA = true;}
      else if(MEHToARNiU == KNWbudkNll){bebHtUoBfm = true;}
      if(cdANNAoCMN == HhMTVrKKtb){hVCIdmrGdl = true;}
      else if(HhMTVrKKtb == cdANNAoCMN){tEbEwUERDu = true;}
      if(iDZOqryCib == jkoAwISVMi){wFAmfociya = true;}
      else if(jkoAwISVMi == iDZOqryCib){wIZZZidsYW = true;}
      if(SORsKCZcqp == KFBpEbeDdO){FAGMOTldoQ = true;}
      else if(KFBpEbeDdO == SORsKCZcqp){spCfLneIJV = true;}
      if(GaDVSZLLeP == YPrwugFXSR){SlEVtqUVSt = true;}
      else if(YPrwugFXSR == GaDVSZLLeP){JjZcYeoecS = true;}
      if(MckpbHmIkC == MlzZUaOHXg){jHOAwuiUsP = true;}
      if(ehdKSNMGDL == hwBzKCgVPs){bVVuthOptK = true;}
      if(aLKWHHzEuQ == MHgeDUssFO){AORMTJAdsn = true;}
      while(MlzZUaOHXg == MckpbHmIkC){qyFgPTEBgK = true;}
      while(hwBzKCgVPs == hwBzKCgVPs){qwcJsECusH = true;}
      while(MHgeDUssFO == MHgeDUssFO){pwIhkMhxAu = true;}
      if(CuDtVXGbVc == true){CuDtVXGbVc = false;}
      if(NXexgcOrlr == true){NXexgcOrlr = false;}
      if(AiIYFFFTWA == true){AiIYFFFTWA = false;}
      if(hVCIdmrGdl == true){hVCIdmrGdl = false;}
      if(wFAmfociya == true){wFAmfociya = false;}
      if(FAGMOTldoQ == true){FAGMOTldoQ = false;}
      if(SlEVtqUVSt == true){SlEVtqUVSt = false;}
      if(jHOAwuiUsP == true){jHOAwuiUsP = false;}
      if(bVVuthOptK == true){bVVuthOptK = false;}
      if(AORMTJAdsn == true){AORMTJAdsn = false;}
      if(TGQDqykGPT == true){TGQDqykGPT = false;}
      if(jQjYnwQJbM == true){jQjYnwQJbM = false;}
      if(bebHtUoBfm == true){bebHtUoBfm = false;}
      if(tEbEwUERDu == true){tEbEwUERDu = false;}
      if(wIZZZidsYW == true){wIZZZidsYW = false;}
      if(spCfLneIJV == true){spCfLneIJV = false;}
      if(JjZcYeoecS == true){JjZcYeoecS = false;}
      if(qyFgPTEBgK == true){qyFgPTEBgK = false;}
      if(qwcJsECusH == true){qwcJsECusH = false;}
      if(pwIhkMhxAu == true){pwIhkMhxAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HJNRZGPZIQ
{ 
  void JyVIwlcLDd()
  { 
      bool GTxWjAlGbL = false;
      bool sarCkuJbBK = false;
      bool TpKIzfmPBj = false;
      bool AlAxpKGpoz = false;
      bool rdDcAGHJIt = false;
      bool MRoJbQIoWE = false;
      bool MWFrKHauLa = false;
      bool nSmBRplhHs = false;
      bool XcGHWhxqVZ = false;
      bool BRTjlVYLRr = false;
      bool eMyhFtdmqk = false;
      bool dagdfjQxUc = false;
      bool KjYlZWzCOw = false;
      bool QaPPOLeYBc = false;
      bool EJzjuZkoEC = false;
      bool EapohtmMIh = false;
      bool ubXuUDLQPU = false;
      bool ErurXAknpz = false;
      bool lJyLqpjahT = false;
      bool XSQShbkEPr = false;
      string HyzmlMzqdn;
      string fYiUoGLJlU;
      string CHOPNadCxK;
      string GBJgmzwqbP;
      string IKwQZGYMQY;
      string VXNOIzjiYL;
      string hxsThdPBgp;
      string KUhWLrLxpG;
      string BQkYoimtYn;
      string PMRPgLQchw;
      string qXeZNBoqCP;
      string mlsRKRLUez;
      string pUcsaxCSoA;
      string aiOtPclLKm;
      string swrIAcSzEP;
      string AwyiFVulzP;
      string yWBBoEWzCh;
      string fzJqGtbTsx;
      string eDNZAekfnt;
      string hAMtoVtpTu;
      if(HyzmlMzqdn == qXeZNBoqCP){GTxWjAlGbL = true;}
      else if(qXeZNBoqCP == HyzmlMzqdn){eMyhFtdmqk = true;}
      if(fYiUoGLJlU == mlsRKRLUez){sarCkuJbBK = true;}
      else if(mlsRKRLUez == fYiUoGLJlU){dagdfjQxUc = true;}
      if(CHOPNadCxK == pUcsaxCSoA){TpKIzfmPBj = true;}
      else if(pUcsaxCSoA == CHOPNadCxK){KjYlZWzCOw = true;}
      if(GBJgmzwqbP == aiOtPclLKm){AlAxpKGpoz = true;}
      else if(aiOtPclLKm == GBJgmzwqbP){QaPPOLeYBc = true;}
      if(IKwQZGYMQY == swrIAcSzEP){rdDcAGHJIt = true;}
      else if(swrIAcSzEP == IKwQZGYMQY){EJzjuZkoEC = true;}
      if(VXNOIzjiYL == AwyiFVulzP){MRoJbQIoWE = true;}
      else if(AwyiFVulzP == VXNOIzjiYL){EapohtmMIh = true;}
      if(hxsThdPBgp == yWBBoEWzCh){MWFrKHauLa = true;}
      else if(yWBBoEWzCh == hxsThdPBgp){ubXuUDLQPU = true;}
      if(KUhWLrLxpG == fzJqGtbTsx){nSmBRplhHs = true;}
      if(BQkYoimtYn == eDNZAekfnt){XcGHWhxqVZ = true;}
      if(PMRPgLQchw == hAMtoVtpTu){BRTjlVYLRr = true;}
      while(fzJqGtbTsx == KUhWLrLxpG){ErurXAknpz = true;}
      while(eDNZAekfnt == eDNZAekfnt){lJyLqpjahT = true;}
      while(hAMtoVtpTu == hAMtoVtpTu){XSQShbkEPr = true;}
      if(GTxWjAlGbL == true){GTxWjAlGbL = false;}
      if(sarCkuJbBK == true){sarCkuJbBK = false;}
      if(TpKIzfmPBj == true){TpKIzfmPBj = false;}
      if(AlAxpKGpoz == true){AlAxpKGpoz = false;}
      if(rdDcAGHJIt == true){rdDcAGHJIt = false;}
      if(MRoJbQIoWE == true){MRoJbQIoWE = false;}
      if(MWFrKHauLa == true){MWFrKHauLa = false;}
      if(nSmBRplhHs == true){nSmBRplhHs = false;}
      if(XcGHWhxqVZ == true){XcGHWhxqVZ = false;}
      if(BRTjlVYLRr == true){BRTjlVYLRr = false;}
      if(eMyhFtdmqk == true){eMyhFtdmqk = false;}
      if(dagdfjQxUc == true){dagdfjQxUc = false;}
      if(KjYlZWzCOw == true){KjYlZWzCOw = false;}
      if(QaPPOLeYBc == true){QaPPOLeYBc = false;}
      if(EJzjuZkoEC == true){EJzjuZkoEC = false;}
      if(EapohtmMIh == true){EapohtmMIh = false;}
      if(ubXuUDLQPU == true){ubXuUDLQPU = false;}
      if(ErurXAknpz == true){ErurXAknpz = false;}
      if(lJyLqpjahT == true){lJyLqpjahT = false;}
      if(XSQShbkEPr == true){XSQShbkEPr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CONSKPGCSI
{ 
  void QNiOaZkoDy()
  { 
      bool QjWOQYcbpS = false;
      bool zEgCCzlrsq = false;
      bool baQVfuAtbP = false;
      bool FmUikGsLBy = false;
      bool MCFPIPxTDH = false;
      bool klqwrpSBiU = false;
      bool YhzaMLixQu = false;
      bool FZqteZUBMP = false;
      bool ygqUdSuXqt = false;
      bool nqcfZdDeCx = false;
      bool fACHBLuwRS = false;
      bool UQoSWrqewt = false;
      bool PKFVHOxKUA = false;
      bool WpyOixdjTS = false;
      bool WyGYZWCJJh = false;
      bool mXhHhUtfzm = false;
      bool NkbQweRZiY = false;
      bool NHLcXQEgwk = false;
      bool LnAmNyHpgN = false;
      bool CyjfFkWoct = false;
      string aLQbRQLmQq;
      string rpCZnJYulR;
      string damToKxsZJ;
      string gMdHWKQxFz;
      string ImWLHKlSXK;
      string HsFroAYwmH;
      string TRMHKfMuCc;
      string saomJqEaMd;
      string YeVPCmGkRW;
      string lTKyeqZPAb;
      string ypPuRfDRix;
      string uxjJiowxEW;
      string YacepYQqIR;
      string RoZkfhOZxV;
      string joCTaniAPp;
      string tbKdCXNkEr;
      string PMJQfGWzdA;
      string ZVzimjYIDC;
      string pPaRXodwhH;
      string UdVFGWeknU;
      if(aLQbRQLmQq == ypPuRfDRix){QjWOQYcbpS = true;}
      else if(ypPuRfDRix == aLQbRQLmQq){fACHBLuwRS = true;}
      if(rpCZnJYulR == uxjJiowxEW){zEgCCzlrsq = true;}
      else if(uxjJiowxEW == rpCZnJYulR){UQoSWrqewt = true;}
      if(damToKxsZJ == YacepYQqIR){baQVfuAtbP = true;}
      else if(YacepYQqIR == damToKxsZJ){PKFVHOxKUA = true;}
      if(gMdHWKQxFz == RoZkfhOZxV){FmUikGsLBy = true;}
      else if(RoZkfhOZxV == gMdHWKQxFz){WpyOixdjTS = true;}
      if(ImWLHKlSXK == joCTaniAPp){MCFPIPxTDH = true;}
      else if(joCTaniAPp == ImWLHKlSXK){WyGYZWCJJh = true;}
      if(HsFroAYwmH == tbKdCXNkEr){klqwrpSBiU = true;}
      else if(tbKdCXNkEr == HsFroAYwmH){mXhHhUtfzm = true;}
      if(TRMHKfMuCc == PMJQfGWzdA){YhzaMLixQu = true;}
      else if(PMJQfGWzdA == TRMHKfMuCc){NkbQweRZiY = true;}
      if(saomJqEaMd == ZVzimjYIDC){FZqteZUBMP = true;}
      if(YeVPCmGkRW == pPaRXodwhH){ygqUdSuXqt = true;}
      if(lTKyeqZPAb == UdVFGWeknU){nqcfZdDeCx = true;}
      while(ZVzimjYIDC == saomJqEaMd){NHLcXQEgwk = true;}
      while(pPaRXodwhH == pPaRXodwhH){LnAmNyHpgN = true;}
      while(UdVFGWeknU == UdVFGWeknU){CyjfFkWoct = true;}
      if(QjWOQYcbpS == true){QjWOQYcbpS = false;}
      if(zEgCCzlrsq == true){zEgCCzlrsq = false;}
      if(baQVfuAtbP == true){baQVfuAtbP = false;}
      if(FmUikGsLBy == true){FmUikGsLBy = false;}
      if(MCFPIPxTDH == true){MCFPIPxTDH = false;}
      if(klqwrpSBiU == true){klqwrpSBiU = false;}
      if(YhzaMLixQu == true){YhzaMLixQu = false;}
      if(FZqteZUBMP == true){FZqteZUBMP = false;}
      if(ygqUdSuXqt == true){ygqUdSuXqt = false;}
      if(nqcfZdDeCx == true){nqcfZdDeCx = false;}
      if(fACHBLuwRS == true){fACHBLuwRS = false;}
      if(UQoSWrqewt == true){UQoSWrqewt = false;}
      if(PKFVHOxKUA == true){PKFVHOxKUA = false;}
      if(WpyOixdjTS == true){WpyOixdjTS = false;}
      if(WyGYZWCJJh == true){WyGYZWCJJh = false;}
      if(mXhHhUtfzm == true){mXhHhUtfzm = false;}
      if(NkbQweRZiY == true){NkbQweRZiY = false;}
      if(NHLcXQEgwk == true){NHLcXQEgwk = false;}
      if(LnAmNyHpgN == true){LnAmNyHpgN = false;}
      if(CyjfFkWoct == true){CyjfFkWoct = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBAOSEEVTT
{ 
  void TqedYcohrM()
  { 
      bool FnFegRdMEp = false;
      bool puRHMjEnAq = false;
      bool jkbIZRqDct = false;
      bool uIgMlhYujq = false;
      bool eQyTIRETJZ = false;
      bool ewPpCTMxFP = false;
      bool ZZiJugOEUe = false;
      bool KJEJLTmHzI = false;
      bool NXtCOzspKS = false;
      bool VapTQFhnYa = false;
      bool DAyeOVrFdh = false;
      bool gEyxCCffuw = false;
      bool nXsCJjSjsF = false;
      bool lyiXEMYOns = false;
      bool GmMckQcsRO = false;
      bool ZBsbmeHwVe = false;
      bool CHMXwhUZro = false;
      bool cQrBoALQRr = false;
      bool GZSdfjFGkZ = false;
      bool FcsIqyanfC = false;
      string hRHELuBPJW;
      string KbyQJWzjME;
      string tAcQLZOxBN;
      string lICGYGiZNc;
      string gxJNslxJmR;
      string fuaZKhnpsl;
      string gDOukCZrqD;
      string nYViWwqOXY;
      string bFKigpgbuq;
      string SrgbwdiNcq;
      string MFRjdHZrCN;
      string qYSTJaseNt;
      string UxwAkursls;
      string MckfMWmZEZ;
      string PoYhAsZMSV;
      string kDAiVOJRzh;
      string PfFJANnlGm;
      string nSZndfYNzq;
      string VeaQIIcCKy;
      string MVaWKjjPgl;
      if(hRHELuBPJW == MFRjdHZrCN){FnFegRdMEp = true;}
      else if(MFRjdHZrCN == hRHELuBPJW){DAyeOVrFdh = true;}
      if(KbyQJWzjME == qYSTJaseNt){puRHMjEnAq = true;}
      else if(qYSTJaseNt == KbyQJWzjME){gEyxCCffuw = true;}
      if(tAcQLZOxBN == UxwAkursls){jkbIZRqDct = true;}
      else if(UxwAkursls == tAcQLZOxBN){nXsCJjSjsF = true;}
      if(lICGYGiZNc == MckfMWmZEZ){uIgMlhYujq = true;}
      else if(MckfMWmZEZ == lICGYGiZNc){lyiXEMYOns = true;}
      if(gxJNslxJmR == PoYhAsZMSV){eQyTIRETJZ = true;}
      else if(PoYhAsZMSV == gxJNslxJmR){GmMckQcsRO = true;}
      if(fuaZKhnpsl == kDAiVOJRzh){ewPpCTMxFP = true;}
      else if(kDAiVOJRzh == fuaZKhnpsl){ZBsbmeHwVe = true;}
      if(gDOukCZrqD == PfFJANnlGm){ZZiJugOEUe = true;}
      else if(PfFJANnlGm == gDOukCZrqD){CHMXwhUZro = true;}
      if(nYViWwqOXY == nSZndfYNzq){KJEJLTmHzI = true;}
      if(bFKigpgbuq == VeaQIIcCKy){NXtCOzspKS = true;}
      if(SrgbwdiNcq == MVaWKjjPgl){VapTQFhnYa = true;}
      while(nSZndfYNzq == nYViWwqOXY){cQrBoALQRr = true;}
      while(VeaQIIcCKy == VeaQIIcCKy){GZSdfjFGkZ = true;}
      while(MVaWKjjPgl == MVaWKjjPgl){FcsIqyanfC = true;}
      if(FnFegRdMEp == true){FnFegRdMEp = false;}
      if(puRHMjEnAq == true){puRHMjEnAq = false;}
      if(jkbIZRqDct == true){jkbIZRqDct = false;}
      if(uIgMlhYujq == true){uIgMlhYujq = false;}
      if(eQyTIRETJZ == true){eQyTIRETJZ = false;}
      if(ewPpCTMxFP == true){ewPpCTMxFP = false;}
      if(ZZiJugOEUe == true){ZZiJugOEUe = false;}
      if(KJEJLTmHzI == true){KJEJLTmHzI = false;}
      if(NXtCOzspKS == true){NXtCOzspKS = false;}
      if(VapTQFhnYa == true){VapTQFhnYa = false;}
      if(DAyeOVrFdh == true){DAyeOVrFdh = false;}
      if(gEyxCCffuw == true){gEyxCCffuw = false;}
      if(nXsCJjSjsF == true){nXsCJjSjsF = false;}
      if(lyiXEMYOns == true){lyiXEMYOns = false;}
      if(GmMckQcsRO == true){GmMckQcsRO = false;}
      if(ZBsbmeHwVe == true){ZBsbmeHwVe = false;}
      if(CHMXwhUZro == true){CHMXwhUZro = false;}
      if(cQrBoALQRr == true){cQrBoALQRr = false;}
      if(GZSdfjFGkZ == true){GZSdfjFGkZ = false;}
      if(FcsIqyanfC == true){FcsIqyanfC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAJOEILUEU
{ 
  void PbHONROBnC()
  { 
      bool UNwnyprWet = false;
      bool EPVHcuPobB = false;
      bool RGBTjWuMVh = false;
      bool UdRRgMWqWt = false;
      bool uBxdFDwdxP = false;
      bool yfbZsNMcEb = false;
      bool tfBwZaxEZP = false;
      bool YYRhFQJWNg = false;
      bool aRPFjoCqYT = false;
      bool AtmuzPABEe = false;
      bool FrEhqYNtUc = false;
      bool EoOXAbQuLk = false;
      bool YGfFOekWhp = false;
      bool PHSiaiNgOK = false;
      bool aHWuOLfPtW = false;
      bool zEpTGzLySM = false;
      bool mqLeMxWewR = false;
      bool OigAJQijpD = false;
      bool yVbKpKRzca = false;
      bool WPOBWjuqhR = false;
      string tmqNkjIXVm;
      string rrpdQPCDDn;
      string fmLpDFeXHg;
      string zWIDcSZJFz;
      string iNzWaUHgNJ;
      string ATXYbHbAJe;
      string EkPnmUilBx;
      string osyDERnnPi;
      string yxJygfzjaV;
      string qZAZtxxLjF;
      string lUfPTHUTTJ;
      string SmjagHaRHH;
      string VyKfGPrYIH;
      string UcEJxcRtdZ;
      string KfQRCDoZrm;
      string WfDbjmJzJD;
      string OwKMopiadD;
      string ogmgxohscC;
      string aSfVjnYbYJ;
      string TRkZLOUEbL;
      if(tmqNkjIXVm == lUfPTHUTTJ){UNwnyprWet = true;}
      else if(lUfPTHUTTJ == tmqNkjIXVm){FrEhqYNtUc = true;}
      if(rrpdQPCDDn == SmjagHaRHH){EPVHcuPobB = true;}
      else if(SmjagHaRHH == rrpdQPCDDn){EoOXAbQuLk = true;}
      if(fmLpDFeXHg == VyKfGPrYIH){RGBTjWuMVh = true;}
      else if(VyKfGPrYIH == fmLpDFeXHg){YGfFOekWhp = true;}
      if(zWIDcSZJFz == UcEJxcRtdZ){UdRRgMWqWt = true;}
      else if(UcEJxcRtdZ == zWIDcSZJFz){PHSiaiNgOK = true;}
      if(iNzWaUHgNJ == KfQRCDoZrm){uBxdFDwdxP = true;}
      else if(KfQRCDoZrm == iNzWaUHgNJ){aHWuOLfPtW = true;}
      if(ATXYbHbAJe == WfDbjmJzJD){yfbZsNMcEb = true;}
      else if(WfDbjmJzJD == ATXYbHbAJe){zEpTGzLySM = true;}
      if(EkPnmUilBx == OwKMopiadD){tfBwZaxEZP = true;}
      else if(OwKMopiadD == EkPnmUilBx){mqLeMxWewR = true;}
      if(osyDERnnPi == ogmgxohscC){YYRhFQJWNg = true;}
      if(yxJygfzjaV == aSfVjnYbYJ){aRPFjoCqYT = true;}
      if(qZAZtxxLjF == TRkZLOUEbL){AtmuzPABEe = true;}
      while(ogmgxohscC == osyDERnnPi){OigAJQijpD = true;}
      while(aSfVjnYbYJ == aSfVjnYbYJ){yVbKpKRzca = true;}
      while(TRkZLOUEbL == TRkZLOUEbL){WPOBWjuqhR = true;}
      if(UNwnyprWet == true){UNwnyprWet = false;}
      if(EPVHcuPobB == true){EPVHcuPobB = false;}
      if(RGBTjWuMVh == true){RGBTjWuMVh = false;}
      if(UdRRgMWqWt == true){UdRRgMWqWt = false;}
      if(uBxdFDwdxP == true){uBxdFDwdxP = false;}
      if(yfbZsNMcEb == true){yfbZsNMcEb = false;}
      if(tfBwZaxEZP == true){tfBwZaxEZP = false;}
      if(YYRhFQJWNg == true){YYRhFQJWNg = false;}
      if(aRPFjoCqYT == true){aRPFjoCqYT = false;}
      if(AtmuzPABEe == true){AtmuzPABEe = false;}
      if(FrEhqYNtUc == true){FrEhqYNtUc = false;}
      if(EoOXAbQuLk == true){EoOXAbQuLk = false;}
      if(YGfFOekWhp == true){YGfFOekWhp = false;}
      if(PHSiaiNgOK == true){PHSiaiNgOK = false;}
      if(aHWuOLfPtW == true){aHWuOLfPtW = false;}
      if(zEpTGzLySM == true){zEpTGzLySM = false;}
      if(mqLeMxWewR == true){mqLeMxWewR = false;}
      if(OigAJQijpD == true){OigAJQijpD = false;}
      if(yVbKpKRzca == true){yVbKpKRzca = false;}
      if(WPOBWjuqhR == true){WPOBWjuqhR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSXBHXEEIM
{ 
  void NWgunYCueh()
  { 
      bool lLSCmVVlOT = false;
      bool HBnzPDnBQf = false;
      bool bFgoNFEjfd = false;
      bool cAtLUQqbZi = false;
      bool qSgWyoEPxY = false;
      bool QjVhYgddog = false;
      bool RkFkqHGbdy = false;
      bool MMbgoJXKpX = false;
      bool AnlGMrdMmm = false;
      bool mNlrQFMwfq = false;
      bool hckyMDInrP = false;
      bool ITmQfcyzXy = false;
      bool dtoqLzZiQj = false;
      bool xbdzpXDmtJ = false;
      bool ioTWdSZVLm = false;
      bool GMXgMnnsmN = false;
      bool cZXIRgonaI = false;
      bool YLENPoZRMr = false;
      bool ZEWccjExlB = false;
      bool jJAgfJQLFx = false;
      string GdTlTbNPfC;
      string lcsFGofeoK;
      string dajAzqtCEA;
      string VGJzubyxlL;
      string meclcISFfu;
      string VuqlVfsSmc;
      string gKKegeSsJd;
      string qiscWyyyWp;
      string YoWIdZOXdP;
      string ieKJdcTxEy;
      string pYuBDmCNPW;
      string huwwDrnBBG;
      string PuPtuLYjzt;
      string dAsYAzsUFq;
      string XBIGhniOFl;
      string oRwxhtJAGr;
      string NSOVrgBXuD;
      string ySwJiOmIMH;
      string cKdMEMEupG;
      string prOMcFlmNA;
      if(GdTlTbNPfC == pYuBDmCNPW){lLSCmVVlOT = true;}
      else if(pYuBDmCNPW == GdTlTbNPfC){hckyMDInrP = true;}
      if(lcsFGofeoK == huwwDrnBBG){HBnzPDnBQf = true;}
      else if(huwwDrnBBG == lcsFGofeoK){ITmQfcyzXy = true;}
      if(dajAzqtCEA == PuPtuLYjzt){bFgoNFEjfd = true;}
      else if(PuPtuLYjzt == dajAzqtCEA){dtoqLzZiQj = true;}
      if(VGJzubyxlL == dAsYAzsUFq){cAtLUQqbZi = true;}
      else if(dAsYAzsUFq == VGJzubyxlL){xbdzpXDmtJ = true;}
      if(meclcISFfu == XBIGhniOFl){qSgWyoEPxY = true;}
      else if(XBIGhniOFl == meclcISFfu){ioTWdSZVLm = true;}
      if(VuqlVfsSmc == oRwxhtJAGr){QjVhYgddog = true;}
      else if(oRwxhtJAGr == VuqlVfsSmc){GMXgMnnsmN = true;}
      if(gKKegeSsJd == NSOVrgBXuD){RkFkqHGbdy = true;}
      else if(NSOVrgBXuD == gKKegeSsJd){cZXIRgonaI = true;}
      if(qiscWyyyWp == ySwJiOmIMH){MMbgoJXKpX = true;}
      if(YoWIdZOXdP == cKdMEMEupG){AnlGMrdMmm = true;}
      if(ieKJdcTxEy == prOMcFlmNA){mNlrQFMwfq = true;}
      while(ySwJiOmIMH == qiscWyyyWp){YLENPoZRMr = true;}
      while(cKdMEMEupG == cKdMEMEupG){ZEWccjExlB = true;}
      while(prOMcFlmNA == prOMcFlmNA){jJAgfJQLFx = true;}
      if(lLSCmVVlOT == true){lLSCmVVlOT = false;}
      if(HBnzPDnBQf == true){HBnzPDnBQf = false;}
      if(bFgoNFEjfd == true){bFgoNFEjfd = false;}
      if(cAtLUQqbZi == true){cAtLUQqbZi = false;}
      if(qSgWyoEPxY == true){qSgWyoEPxY = false;}
      if(QjVhYgddog == true){QjVhYgddog = false;}
      if(RkFkqHGbdy == true){RkFkqHGbdy = false;}
      if(MMbgoJXKpX == true){MMbgoJXKpX = false;}
      if(AnlGMrdMmm == true){AnlGMrdMmm = false;}
      if(mNlrQFMwfq == true){mNlrQFMwfq = false;}
      if(hckyMDInrP == true){hckyMDInrP = false;}
      if(ITmQfcyzXy == true){ITmQfcyzXy = false;}
      if(dtoqLzZiQj == true){dtoqLzZiQj = false;}
      if(xbdzpXDmtJ == true){xbdzpXDmtJ = false;}
      if(ioTWdSZVLm == true){ioTWdSZVLm = false;}
      if(GMXgMnnsmN == true){GMXgMnnsmN = false;}
      if(cZXIRgonaI == true){cZXIRgonaI = false;}
      if(YLENPoZRMr == true){YLENPoZRMr = false;}
      if(ZEWccjExlB == true){ZEWccjExlB = false;}
      if(jJAgfJQLFx == true){jJAgfJQLFx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAQURPJKYK
{ 
  void reAkKJeLBT()
  { 
      bool TVTeWZkDfa = false;
      bool drDEXzTxfj = false;
      bool nSMVrYbGcN = false;
      bool HaGiQnJMTV = false;
      bool rKIVTIgQTx = false;
      bool IEHerBJymx = false;
      bool yeZRSCkUni = false;
      bool pHcKqcJpBj = false;
      bool rLlfFDTbpO = false;
      bool eKZVXNkqCR = false;
      bool WMcjGBbxmO = false;
      bool rSwDFlrtMP = false;
      bool iJdYEegGld = false;
      bool rRnjMeiCYD = false;
      bool aVnaWLOWQl = false;
      bool UpdliNiDeb = false;
      bool UULJWZeMpa = false;
      bool DpVJoMVDCs = false;
      bool QKpAICmCBy = false;
      bool wfWwiFKdEw = false;
      string dAUMfFwOxg;
      string sLOXqqmGCG;
      string LPPKlxUZmd;
      string jnPIsgfXNg;
      string ElwzqVUxMk;
      string JUiABOkJai;
      string kWbTwFuGdJ;
      string LOsUCYTPTQ;
      string bWNBTPEOGe;
      string wVxdwgKbDl;
      string ZNSCZtaNyc;
      string tUpJGOIZzf;
      string AgAzMpQPYU;
      string OqMhpODKbZ;
      string oqQdjbemWg;
      string XjcWksNSoi;
      string cLocOCHITr;
      string KxyZqJPVPk;
      string KdrqwdOowx;
      string AkVrwcBnPg;
      if(dAUMfFwOxg == ZNSCZtaNyc){TVTeWZkDfa = true;}
      else if(ZNSCZtaNyc == dAUMfFwOxg){WMcjGBbxmO = true;}
      if(sLOXqqmGCG == tUpJGOIZzf){drDEXzTxfj = true;}
      else if(tUpJGOIZzf == sLOXqqmGCG){rSwDFlrtMP = true;}
      if(LPPKlxUZmd == AgAzMpQPYU){nSMVrYbGcN = true;}
      else if(AgAzMpQPYU == LPPKlxUZmd){iJdYEegGld = true;}
      if(jnPIsgfXNg == OqMhpODKbZ){HaGiQnJMTV = true;}
      else if(OqMhpODKbZ == jnPIsgfXNg){rRnjMeiCYD = true;}
      if(ElwzqVUxMk == oqQdjbemWg){rKIVTIgQTx = true;}
      else if(oqQdjbemWg == ElwzqVUxMk){aVnaWLOWQl = true;}
      if(JUiABOkJai == XjcWksNSoi){IEHerBJymx = true;}
      else if(XjcWksNSoi == JUiABOkJai){UpdliNiDeb = true;}
      if(kWbTwFuGdJ == cLocOCHITr){yeZRSCkUni = true;}
      else if(cLocOCHITr == kWbTwFuGdJ){UULJWZeMpa = true;}
      if(LOsUCYTPTQ == KxyZqJPVPk){pHcKqcJpBj = true;}
      if(bWNBTPEOGe == KdrqwdOowx){rLlfFDTbpO = true;}
      if(wVxdwgKbDl == AkVrwcBnPg){eKZVXNkqCR = true;}
      while(KxyZqJPVPk == LOsUCYTPTQ){DpVJoMVDCs = true;}
      while(KdrqwdOowx == KdrqwdOowx){QKpAICmCBy = true;}
      while(AkVrwcBnPg == AkVrwcBnPg){wfWwiFKdEw = true;}
      if(TVTeWZkDfa == true){TVTeWZkDfa = false;}
      if(drDEXzTxfj == true){drDEXzTxfj = false;}
      if(nSMVrYbGcN == true){nSMVrYbGcN = false;}
      if(HaGiQnJMTV == true){HaGiQnJMTV = false;}
      if(rKIVTIgQTx == true){rKIVTIgQTx = false;}
      if(IEHerBJymx == true){IEHerBJymx = false;}
      if(yeZRSCkUni == true){yeZRSCkUni = false;}
      if(pHcKqcJpBj == true){pHcKqcJpBj = false;}
      if(rLlfFDTbpO == true){rLlfFDTbpO = false;}
      if(eKZVXNkqCR == true){eKZVXNkqCR = false;}
      if(WMcjGBbxmO == true){WMcjGBbxmO = false;}
      if(rSwDFlrtMP == true){rSwDFlrtMP = false;}
      if(iJdYEegGld == true){iJdYEegGld = false;}
      if(rRnjMeiCYD == true){rRnjMeiCYD = false;}
      if(aVnaWLOWQl == true){aVnaWLOWQl = false;}
      if(UpdliNiDeb == true){UpdliNiDeb = false;}
      if(UULJWZeMpa == true){UULJWZeMpa = false;}
      if(DpVJoMVDCs == true){DpVJoMVDCs = false;}
      if(QKpAICmCBy == true){QKpAICmCBy = false;}
      if(wfWwiFKdEw == true){wfWwiFKdEw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBCIOUAPLU
{ 
  void PEAGBSOkhL()
  { 
      bool TQsNoSyXyY = false;
      bool PqeLhmnPVc = false;
      bool LBSaJccFOV = false;
      bool oMrntgIsPe = false;
      bool gZZdVnKHTd = false;
      bool RrNMwRyREL = false;
      bool psJcjCzpQB = false;
      bool euzqukaoFV = false;
      bool SUkjDwzerc = false;
      bool ipoEnnQwsS = false;
      bool oTpSzWsVRK = false;
      bool pIMhrUIZZm = false;
      bool DTynSnFuCH = false;
      bool UeulfydRjf = false;
      bool DcNglZcGLT = false;
      bool fpWFPVVCzL = false;
      bool RxTJpLNaCt = false;
      bool pppsjZFQCs = false;
      bool KyihbdHoWJ = false;
      bool cbSXOFJDqZ = false;
      string fhcTPZBTMX;
      string hFzeeUHegd;
      string TZBIABmleW;
      string hwYWlBCjPd;
      string QkfwjqkhLg;
      string TWkrcGfUTN;
      string mOnoplfbsc;
      string RXODNhsFYI;
      string QEayCKKgte;
      string UhQCpCwqFy;
      string KInhPwIhet;
      string MawKxinple;
      string ayhNIiHMML;
      string lCAZyHPrhG;
      string CcCzRtlFEH;
      string NGEaWMaaZf;
      string owUSIKaVMp;
      string SuHfbxwiuO;
      string xBHExfyYDk;
      string foSCRGIipH;
      if(fhcTPZBTMX == KInhPwIhet){TQsNoSyXyY = true;}
      else if(KInhPwIhet == fhcTPZBTMX){oTpSzWsVRK = true;}
      if(hFzeeUHegd == MawKxinple){PqeLhmnPVc = true;}
      else if(MawKxinple == hFzeeUHegd){pIMhrUIZZm = true;}
      if(TZBIABmleW == ayhNIiHMML){LBSaJccFOV = true;}
      else if(ayhNIiHMML == TZBIABmleW){DTynSnFuCH = true;}
      if(hwYWlBCjPd == lCAZyHPrhG){oMrntgIsPe = true;}
      else if(lCAZyHPrhG == hwYWlBCjPd){UeulfydRjf = true;}
      if(QkfwjqkhLg == CcCzRtlFEH){gZZdVnKHTd = true;}
      else if(CcCzRtlFEH == QkfwjqkhLg){DcNglZcGLT = true;}
      if(TWkrcGfUTN == NGEaWMaaZf){RrNMwRyREL = true;}
      else if(NGEaWMaaZf == TWkrcGfUTN){fpWFPVVCzL = true;}
      if(mOnoplfbsc == owUSIKaVMp){psJcjCzpQB = true;}
      else if(owUSIKaVMp == mOnoplfbsc){RxTJpLNaCt = true;}
      if(RXODNhsFYI == SuHfbxwiuO){euzqukaoFV = true;}
      if(QEayCKKgte == xBHExfyYDk){SUkjDwzerc = true;}
      if(UhQCpCwqFy == foSCRGIipH){ipoEnnQwsS = true;}
      while(SuHfbxwiuO == RXODNhsFYI){pppsjZFQCs = true;}
      while(xBHExfyYDk == xBHExfyYDk){KyihbdHoWJ = true;}
      while(foSCRGIipH == foSCRGIipH){cbSXOFJDqZ = true;}
      if(TQsNoSyXyY == true){TQsNoSyXyY = false;}
      if(PqeLhmnPVc == true){PqeLhmnPVc = false;}
      if(LBSaJccFOV == true){LBSaJccFOV = false;}
      if(oMrntgIsPe == true){oMrntgIsPe = false;}
      if(gZZdVnKHTd == true){gZZdVnKHTd = false;}
      if(RrNMwRyREL == true){RrNMwRyREL = false;}
      if(psJcjCzpQB == true){psJcjCzpQB = false;}
      if(euzqukaoFV == true){euzqukaoFV = false;}
      if(SUkjDwzerc == true){SUkjDwzerc = false;}
      if(ipoEnnQwsS == true){ipoEnnQwsS = false;}
      if(oTpSzWsVRK == true){oTpSzWsVRK = false;}
      if(pIMhrUIZZm == true){pIMhrUIZZm = false;}
      if(DTynSnFuCH == true){DTynSnFuCH = false;}
      if(UeulfydRjf == true){UeulfydRjf = false;}
      if(DcNglZcGLT == true){DcNglZcGLT = false;}
      if(fpWFPVVCzL == true){fpWFPVVCzL = false;}
      if(RxTJpLNaCt == true){RxTJpLNaCt = false;}
      if(pppsjZFQCs == true){pppsjZFQCs = false;}
      if(KyihbdHoWJ == true){KyihbdHoWJ = false;}
      if(cbSXOFJDqZ == true){cbSXOFJDqZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVYSSFWOYT
{ 
  void dVtRcoonOs()
  { 
      bool MwGiEDAuBw = false;
      bool mEMMrloRGW = false;
      bool aSsJRjafit = false;
      bool cDahSrCUFm = false;
      bool mhERHaLkbK = false;
      bool OPzfxsDwQU = false;
      bool bULHSicetA = false;
      bool iTLTisOaBq = false;
      bool XpDYeNEtjY = false;
      bool oFDkKRVxzY = false;
      bool xfqbatDfwE = false;
      bool ebuZwlRmbF = false;
      bool eiuULdQaIQ = false;
      bool WQbcsryaxj = false;
      bool KXyfsMJcnY = false;
      bool AiUssOkVQx = false;
      bool dbXegOASfE = false;
      bool nporuGkPay = false;
      bool UnljQmuiie = false;
      bool HbJzGhASye = false;
      string npfJEUFDVp;
      string ksISdenEBV;
      string XcMGGLVpZt;
      string WDFEwuFMgN;
      string HfZMJAbZqz;
      string pzpgqKdYDs;
      string yOcbShmDVh;
      string YbWnNrCzwF;
      string jwzaEXMXMk;
      string QgInPsCytb;
      string MXDIZNbCSz;
      string IecxIBPBWt;
      string UOpjRrTiYU;
      string oEFUsLrpBq;
      string wKENclEKeN;
      string cBazGxgTqg;
      string trcyKEYHEw;
      string IZAfyKKcGe;
      string nIDKqncGOu;
      string eYyUwDgGCY;
      if(npfJEUFDVp == MXDIZNbCSz){MwGiEDAuBw = true;}
      else if(MXDIZNbCSz == npfJEUFDVp){xfqbatDfwE = true;}
      if(ksISdenEBV == IecxIBPBWt){mEMMrloRGW = true;}
      else if(IecxIBPBWt == ksISdenEBV){ebuZwlRmbF = true;}
      if(XcMGGLVpZt == UOpjRrTiYU){aSsJRjafit = true;}
      else if(UOpjRrTiYU == XcMGGLVpZt){eiuULdQaIQ = true;}
      if(WDFEwuFMgN == oEFUsLrpBq){cDahSrCUFm = true;}
      else if(oEFUsLrpBq == WDFEwuFMgN){WQbcsryaxj = true;}
      if(HfZMJAbZqz == wKENclEKeN){mhERHaLkbK = true;}
      else if(wKENclEKeN == HfZMJAbZqz){KXyfsMJcnY = true;}
      if(pzpgqKdYDs == cBazGxgTqg){OPzfxsDwQU = true;}
      else if(cBazGxgTqg == pzpgqKdYDs){AiUssOkVQx = true;}
      if(yOcbShmDVh == trcyKEYHEw){bULHSicetA = true;}
      else if(trcyKEYHEw == yOcbShmDVh){dbXegOASfE = true;}
      if(YbWnNrCzwF == IZAfyKKcGe){iTLTisOaBq = true;}
      if(jwzaEXMXMk == nIDKqncGOu){XpDYeNEtjY = true;}
      if(QgInPsCytb == eYyUwDgGCY){oFDkKRVxzY = true;}
      while(IZAfyKKcGe == YbWnNrCzwF){nporuGkPay = true;}
      while(nIDKqncGOu == nIDKqncGOu){UnljQmuiie = true;}
      while(eYyUwDgGCY == eYyUwDgGCY){HbJzGhASye = true;}
      if(MwGiEDAuBw == true){MwGiEDAuBw = false;}
      if(mEMMrloRGW == true){mEMMrloRGW = false;}
      if(aSsJRjafit == true){aSsJRjafit = false;}
      if(cDahSrCUFm == true){cDahSrCUFm = false;}
      if(mhERHaLkbK == true){mhERHaLkbK = false;}
      if(OPzfxsDwQU == true){OPzfxsDwQU = false;}
      if(bULHSicetA == true){bULHSicetA = false;}
      if(iTLTisOaBq == true){iTLTisOaBq = false;}
      if(XpDYeNEtjY == true){XpDYeNEtjY = false;}
      if(oFDkKRVxzY == true){oFDkKRVxzY = false;}
      if(xfqbatDfwE == true){xfqbatDfwE = false;}
      if(ebuZwlRmbF == true){ebuZwlRmbF = false;}
      if(eiuULdQaIQ == true){eiuULdQaIQ = false;}
      if(WQbcsryaxj == true){WQbcsryaxj = false;}
      if(KXyfsMJcnY == true){KXyfsMJcnY = false;}
      if(AiUssOkVQx == true){AiUssOkVQx = false;}
      if(dbXegOASfE == true){dbXegOASfE = false;}
      if(nporuGkPay == true){nporuGkPay = false;}
      if(UnljQmuiie == true){UnljQmuiie = false;}
      if(HbJzGhASye == true){HbJzGhASye = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PZUOYVOQFW
{ 
  void PdogRcaTHZ()
  { 
      bool fgIetRyAxb = false;
      bool YwuQuwTTwS = false;
      bool rILMWwyRVn = false;
      bool qrSwJEmiOk = false;
      bool aSghRqiwwT = false;
      bool fYSKEXUwHx = false;
      bool SfdJjfczHq = false;
      bool IjELrYactf = false;
      bool NCVCHRZIql = false;
      bool iqaQRtoXyk = false;
      bool NioFKwTHRf = false;
      bool wrBbiQJbBS = false;
      bool FTIUHRImtx = false;
      bool iDeIReNQqL = false;
      bool xSpLpqpzhA = false;
      bool jNVffsaTxs = false;
      bool mgNUwsMrJE = false;
      bool DsjpUmdweQ = false;
      bool aJFsMVgzcY = false;
      bool DsSxXQFVPw = false;
      string nBMmihwkKg;
      string BhyLbNarLV;
      string wfZgoEdeED;
      string oXSpixbhIS;
      string cXpAtQQTtI;
      string sUyYxHbexd;
      string DRfGqdPIcd;
      string lrirrYoYlX;
      string nJjwKUZsra;
      string VwjeOLqiIP;
      string BIqPWAlFfX;
      string RCrYptgiwW;
      string EVPCIoHDcg;
      string gGPVWeSUYJ;
      string hUNTISDLoU;
      string dImlLfrnHg;
      string shbyqLmVCK;
      string aMJmnjHwsp;
      string lwOICYSdKp;
      string mdNrQArOcx;
      if(nBMmihwkKg == BIqPWAlFfX){fgIetRyAxb = true;}
      else if(BIqPWAlFfX == nBMmihwkKg){NioFKwTHRf = true;}
      if(BhyLbNarLV == RCrYptgiwW){YwuQuwTTwS = true;}
      else if(RCrYptgiwW == BhyLbNarLV){wrBbiQJbBS = true;}
      if(wfZgoEdeED == EVPCIoHDcg){rILMWwyRVn = true;}
      else if(EVPCIoHDcg == wfZgoEdeED){FTIUHRImtx = true;}
      if(oXSpixbhIS == gGPVWeSUYJ){qrSwJEmiOk = true;}
      else if(gGPVWeSUYJ == oXSpixbhIS){iDeIReNQqL = true;}
      if(cXpAtQQTtI == hUNTISDLoU){aSghRqiwwT = true;}
      else if(hUNTISDLoU == cXpAtQQTtI){xSpLpqpzhA = true;}
      if(sUyYxHbexd == dImlLfrnHg){fYSKEXUwHx = true;}
      else if(dImlLfrnHg == sUyYxHbexd){jNVffsaTxs = true;}
      if(DRfGqdPIcd == shbyqLmVCK){SfdJjfczHq = true;}
      else if(shbyqLmVCK == DRfGqdPIcd){mgNUwsMrJE = true;}
      if(lrirrYoYlX == aMJmnjHwsp){IjELrYactf = true;}
      if(nJjwKUZsra == lwOICYSdKp){NCVCHRZIql = true;}
      if(VwjeOLqiIP == mdNrQArOcx){iqaQRtoXyk = true;}
      while(aMJmnjHwsp == lrirrYoYlX){DsjpUmdweQ = true;}
      while(lwOICYSdKp == lwOICYSdKp){aJFsMVgzcY = true;}
      while(mdNrQArOcx == mdNrQArOcx){DsSxXQFVPw = true;}
      if(fgIetRyAxb == true){fgIetRyAxb = false;}
      if(YwuQuwTTwS == true){YwuQuwTTwS = false;}
      if(rILMWwyRVn == true){rILMWwyRVn = false;}
      if(qrSwJEmiOk == true){qrSwJEmiOk = false;}
      if(aSghRqiwwT == true){aSghRqiwwT = false;}
      if(fYSKEXUwHx == true){fYSKEXUwHx = false;}
      if(SfdJjfczHq == true){SfdJjfczHq = false;}
      if(IjELrYactf == true){IjELrYactf = false;}
      if(NCVCHRZIql == true){NCVCHRZIql = false;}
      if(iqaQRtoXyk == true){iqaQRtoXyk = false;}
      if(NioFKwTHRf == true){NioFKwTHRf = false;}
      if(wrBbiQJbBS == true){wrBbiQJbBS = false;}
      if(FTIUHRImtx == true){FTIUHRImtx = false;}
      if(iDeIReNQqL == true){iDeIReNQqL = false;}
      if(xSpLpqpzhA == true){xSpLpqpzhA = false;}
      if(jNVffsaTxs == true){jNVffsaTxs = false;}
      if(mgNUwsMrJE == true){mgNUwsMrJE = false;}
      if(DsjpUmdweQ == true){DsjpUmdweQ = false;}
      if(aJFsMVgzcY == true){aJFsMVgzcY = false;}
      if(DsSxXQFVPw == true){DsSxXQFVPw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOUPJEEKCL
{ 
  void gMYqGiYfXg()
  { 
      bool ElTHnnKfac = false;
      bool YtYdggDtHX = false;
      bool JtcgHDIBsq = false;
      bool IFnLIkqliH = false;
      bool isQJdsGXly = false;
      bool JtrMBJImzj = false;
      bool fJmiTSGMVu = false;
      bool pRKzoPdTCN = false;
      bool xjOuhNNaKy = false;
      bool bElzbZGgoL = false;
      bool msCpIrjsXk = false;
      bool fojllutqBG = false;
      bool EeCXTkeLWP = false;
      bool JwdqZEhXmo = false;
      bool cUDYRmUAMg = false;
      bool eOfhGIpdWW = false;
      bool NXVIbiKrLh = false;
      bool MVELcjadFf = false;
      bool QdzpjtQukR = false;
      bool ODBPbFyuwi = false;
      string SLFLcccaGb;
      string cYKhbxqTLC;
      string RTjnYVcigZ;
      string GHJmHZtHOi;
      string zSjRyDSmuf;
      string rAoEqyaQlG;
      string AssfVVOWZB;
      string CjFcDzjSoV;
      string DonAgFSFuI;
      string ydUHhFYEuc;
      string nuNtcIuLBr;
      string OIbQDKFryP;
      string DJbQCYPxtx;
      string ZfWLgHbtXY;
      string KGDCtpBDDW;
      string AfFfZdTwqE;
      string sxRERikPjw;
      string iLUYExFYWM;
      string WLsWwtZqlC;
      string neCTfNozkK;
      if(SLFLcccaGb == nuNtcIuLBr){ElTHnnKfac = true;}
      else if(nuNtcIuLBr == SLFLcccaGb){msCpIrjsXk = true;}
      if(cYKhbxqTLC == OIbQDKFryP){YtYdggDtHX = true;}
      else if(OIbQDKFryP == cYKhbxqTLC){fojllutqBG = true;}
      if(RTjnYVcigZ == DJbQCYPxtx){JtcgHDIBsq = true;}
      else if(DJbQCYPxtx == RTjnYVcigZ){EeCXTkeLWP = true;}
      if(GHJmHZtHOi == ZfWLgHbtXY){IFnLIkqliH = true;}
      else if(ZfWLgHbtXY == GHJmHZtHOi){JwdqZEhXmo = true;}
      if(zSjRyDSmuf == KGDCtpBDDW){isQJdsGXly = true;}
      else if(KGDCtpBDDW == zSjRyDSmuf){cUDYRmUAMg = true;}
      if(rAoEqyaQlG == AfFfZdTwqE){JtrMBJImzj = true;}
      else if(AfFfZdTwqE == rAoEqyaQlG){eOfhGIpdWW = true;}
      if(AssfVVOWZB == sxRERikPjw){fJmiTSGMVu = true;}
      else if(sxRERikPjw == AssfVVOWZB){NXVIbiKrLh = true;}
      if(CjFcDzjSoV == iLUYExFYWM){pRKzoPdTCN = true;}
      if(DonAgFSFuI == WLsWwtZqlC){xjOuhNNaKy = true;}
      if(ydUHhFYEuc == neCTfNozkK){bElzbZGgoL = true;}
      while(iLUYExFYWM == CjFcDzjSoV){MVELcjadFf = true;}
      while(WLsWwtZqlC == WLsWwtZqlC){QdzpjtQukR = true;}
      while(neCTfNozkK == neCTfNozkK){ODBPbFyuwi = true;}
      if(ElTHnnKfac == true){ElTHnnKfac = false;}
      if(YtYdggDtHX == true){YtYdggDtHX = false;}
      if(JtcgHDIBsq == true){JtcgHDIBsq = false;}
      if(IFnLIkqliH == true){IFnLIkqliH = false;}
      if(isQJdsGXly == true){isQJdsGXly = false;}
      if(JtrMBJImzj == true){JtrMBJImzj = false;}
      if(fJmiTSGMVu == true){fJmiTSGMVu = false;}
      if(pRKzoPdTCN == true){pRKzoPdTCN = false;}
      if(xjOuhNNaKy == true){xjOuhNNaKy = false;}
      if(bElzbZGgoL == true){bElzbZGgoL = false;}
      if(msCpIrjsXk == true){msCpIrjsXk = false;}
      if(fojllutqBG == true){fojllutqBG = false;}
      if(EeCXTkeLWP == true){EeCXTkeLWP = false;}
      if(JwdqZEhXmo == true){JwdqZEhXmo = false;}
      if(cUDYRmUAMg == true){cUDYRmUAMg = false;}
      if(eOfhGIpdWW == true){eOfhGIpdWW = false;}
      if(NXVIbiKrLh == true){NXVIbiKrLh = false;}
      if(MVELcjadFf == true){MVELcjadFf = false;}
      if(QdzpjtQukR == true){QdzpjtQukR = false;}
      if(ODBPbFyuwi == true){ODBPbFyuwi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHKQLNIKBP
{ 
  void hPMuhwBsVK()
  { 
      bool eIJjmbgCYK = false;
      bool RGwwAdSYhS = false;
      bool pGrFbjcHIY = false;
      bool WNxGMCATVS = false;
      bool EyRQyDSdSa = false;
      bool qpbNlXQEID = false;
      bool yZsAnEIojx = false;
      bool cyCOOroaGX = false;
      bool QynhgfkjUo = false;
      bool lwLSTdERct = false;
      bool udtUxrnNzt = false;
      bool hoxjlAkLSI = false;
      bool TYUtLglitk = false;
      bool mXyMcmDTjo = false;
      bool qXjaGxybfT = false;
      bool rryUZWJAJQ = false;
      bool GETNGKpjGz = false;
      bool xRbdQunsmO = false;
      bool hJCZruYdlG = false;
      bool cDJThlEWTw = false;
      string hzpkfUPeiw;
      string pQnCdhuIlQ;
      string AmjrCCtXtE;
      string DgRlWmUsfI;
      string quzPnxEOzO;
      string gZGbCuPxid;
      string arjdsIyBeq;
      string MBbcYEmTEF;
      string xeXfXdZojb;
      string WXKChzLVWe;
      string yCiIBexcCx;
      string IusdfuTEFO;
      string iJRDToqZuZ;
      string sQxYGtuPdr;
      string gwllTbdgVl;
      string eHPHwokfnL;
      string nWhcEqxUWk;
      string zDZNhlWeiq;
      string LKEIukApbQ;
      string JPaSEJOJgb;
      if(hzpkfUPeiw == yCiIBexcCx){eIJjmbgCYK = true;}
      else if(yCiIBexcCx == hzpkfUPeiw){udtUxrnNzt = true;}
      if(pQnCdhuIlQ == IusdfuTEFO){RGwwAdSYhS = true;}
      else if(IusdfuTEFO == pQnCdhuIlQ){hoxjlAkLSI = true;}
      if(AmjrCCtXtE == iJRDToqZuZ){pGrFbjcHIY = true;}
      else if(iJRDToqZuZ == AmjrCCtXtE){TYUtLglitk = true;}
      if(DgRlWmUsfI == sQxYGtuPdr){WNxGMCATVS = true;}
      else if(sQxYGtuPdr == DgRlWmUsfI){mXyMcmDTjo = true;}
      if(quzPnxEOzO == gwllTbdgVl){EyRQyDSdSa = true;}
      else if(gwllTbdgVl == quzPnxEOzO){qXjaGxybfT = true;}
      if(gZGbCuPxid == eHPHwokfnL){qpbNlXQEID = true;}
      else if(eHPHwokfnL == gZGbCuPxid){rryUZWJAJQ = true;}
      if(arjdsIyBeq == nWhcEqxUWk){yZsAnEIojx = true;}
      else if(nWhcEqxUWk == arjdsIyBeq){GETNGKpjGz = true;}
      if(MBbcYEmTEF == zDZNhlWeiq){cyCOOroaGX = true;}
      if(xeXfXdZojb == LKEIukApbQ){QynhgfkjUo = true;}
      if(WXKChzLVWe == JPaSEJOJgb){lwLSTdERct = true;}
      while(zDZNhlWeiq == MBbcYEmTEF){xRbdQunsmO = true;}
      while(LKEIukApbQ == LKEIukApbQ){hJCZruYdlG = true;}
      while(JPaSEJOJgb == JPaSEJOJgb){cDJThlEWTw = true;}
      if(eIJjmbgCYK == true){eIJjmbgCYK = false;}
      if(RGwwAdSYhS == true){RGwwAdSYhS = false;}
      if(pGrFbjcHIY == true){pGrFbjcHIY = false;}
      if(WNxGMCATVS == true){WNxGMCATVS = false;}
      if(EyRQyDSdSa == true){EyRQyDSdSa = false;}
      if(qpbNlXQEID == true){qpbNlXQEID = false;}
      if(yZsAnEIojx == true){yZsAnEIojx = false;}
      if(cyCOOroaGX == true){cyCOOroaGX = false;}
      if(QynhgfkjUo == true){QynhgfkjUo = false;}
      if(lwLSTdERct == true){lwLSTdERct = false;}
      if(udtUxrnNzt == true){udtUxrnNzt = false;}
      if(hoxjlAkLSI == true){hoxjlAkLSI = false;}
      if(TYUtLglitk == true){TYUtLglitk = false;}
      if(mXyMcmDTjo == true){mXyMcmDTjo = false;}
      if(qXjaGxybfT == true){qXjaGxybfT = false;}
      if(rryUZWJAJQ == true){rryUZWJAJQ = false;}
      if(GETNGKpjGz == true){GETNGKpjGz = false;}
      if(xRbdQunsmO == true){xRbdQunsmO = false;}
      if(hJCZruYdlG == true){hJCZruYdlG = false;}
      if(cDJThlEWTw == true){cDJThlEWTw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DAHIFTDCCP
{ 
  void CaGgCqAzmg()
  { 
      bool mNylsufkID = false;
      bool WQshYlQLKR = false;
      bool iXAbBhirIw = false;
      bool ilsfbHjZqf = false;
      bool dHWjVgNxrk = false;
      bool PJFVePMWkL = false;
      bool MncLUkWMFR = false;
      bool BqTdnbBQFT = false;
      bool TkzWfYfXBM = false;
      bool tNnfToeKOk = false;
      bool KAraiYpbhC = false;
      bool NuQQqanFfw = false;
      bool FzLrWnCnKy = false;
      bool xqCUJTsYmG = false;
      bool iEpyzzwWnr = false;
      bool BYdSfLnzEt = false;
      bool WBQiFWsuHX = false;
      bool gORYMAINsW = false;
      bool reARwYMinx = false;
      bool etTsjhmGsb = false;
      string BqhsKyeAkH;
      string oXQQlPFzyP;
      string RUhRIXyFEz;
      string lhpcGTEsUP;
      string bGYsnLghWc;
      string jDzNlfIPkm;
      string zZwlUGgmKR;
      string LLeinKuodw;
      string pQhbOhibqZ;
      string KnIhPBKmXg;
      string dtWEQXYPYb;
      string jTlnwhqUWl;
      string XFwjHWDxSl;
      string AIQxSwscKq;
      string JSCOpqCUkh;
      string KpQkIYymxs;
      string UbxmbbDoVz;
      string nOJecECgtP;
      string UhLkbJrens;
      string yGeQWgVPmN;
      if(BqhsKyeAkH == dtWEQXYPYb){mNylsufkID = true;}
      else if(dtWEQXYPYb == BqhsKyeAkH){KAraiYpbhC = true;}
      if(oXQQlPFzyP == jTlnwhqUWl){WQshYlQLKR = true;}
      else if(jTlnwhqUWl == oXQQlPFzyP){NuQQqanFfw = true;}
      if(RUhRIXyFEz == XFwjHWDxSl){iXAbBhirIw = true;}
      else if(XFwjHWDxSl == RUhRIXyFEz){FzLrWnCnKy = true;}
      if(lhpcGTEsUP == AIQxSwscKq){ilsfbHjZqf = true;}
      else if(AIQxSwscKq == lhpcGTEsUP){xqCUJTsYmG = true;}
      if(bGYsnLghWc == JSCOpqCUkh){dHWjVgNxrk = true;}
      else if(JSCOpqCUkh == bGYsnLghWc){iEpyzzwWnr = true;}
      if(jDzNlfIPkm == KpQkIYymxs){PJFVePMWkL = true;}
      else if(KpQkIYymxs == jDzNlfIPkm){BYdSfLnzEt = true;}
      if(zZwlUGgmKR == UbxmbbDoVz){MncLUkWMFR = true;}
      else if(UbxmbbDoVz == zZwlUGgmKR){WBQiFWsuHX = true;}
      if(LLeinKuodw == nOJecECgtP){BqTdnbBQFT = true;}
      if(pQhbOhibqZ == UhLkbJrens){TkzWfYfXBM = true;}
      if(KnIhPBKmXg == yGeQWgVPmN){tNnfToeKOk = true;}
      while(nOJecECgtP == LLeinKuodw){gORYMAINsW = true;}
      while(UhLkbJrens == UhLkbJrens){reARwYMinx = true;}
      while(yGeQWgVPmN == yGeQWgVPmN){etTsjhmGsb = true;}
      if(mNylsufkID == true){mNylsufkID = false;}
      if(WQshYlQLKR == true){WQshYlQLKR = false;}
      if(iXAbBhirIw == true){iXAbBhirIw = false;}
      if(ilsfbHjZqf == true){ilsfbHjZqf = false;}
      if(dHWjVgNxrk == true){dHWjVgNxrk = false;}
      if(PJFVePMWkL == true){PJFVePMWkL = false;}
      if(MncLUkWMFR == true){MncLUkWMFR = false;}
      if(BqTdnbBQFT == true){BqTdnbBQFT = false;}
      if(TkzWfYfXBM == true){TkzWfYfXBM = false;}
      if(tNnfToeKOk == true){tNnfToeKOk = false;}
      if(KAraiYpbhC == true){KAraiYpbhC = false;}
      if(NuQQqanFfw == true){NuQQqanFfw = false;}
      if(FzLrWnCnKy == true){FzLrWnCnKy = false;}
      if(xqCUJTsYmG == true){xqCUJTsYmG = false;}
      if(iEpyzzwWnr == true){iEpyzzwWnr = false;}
      if(BYdSfLnzEt == true){BYdSfLnzEt = false;}
      if(WBQiFWsuHX == true){WBQiFWsuHX = false;}
      if(gORYMAINsW == true){gORYMAINsW = false;}
      if(reARwYMinx == true){reARwYMinx = false;}
      if(etTsjhmGsb == true){etTsjhmGsb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKJFKWGNXM
{ 
  void uUwYpZYbMf()
  { 
      bool WmNHmYBznp = false;
      bool NtMBZAtVCS = false;
      bool juKdFhpYpW = false;
      bool yugdntbyFC = false;
      bool kWCaBOqeCt = false;
      bool jdooqabjBE = false;
      bool hbJRqSMiMe = false;
      bool YwPAgMsjcq = false;
      bool qLVumUFrlM = false;
      bool SqwBUINkih = false;
      bool BHRXUmNoHd = false;
      bool hqHJMVGNdW = false;
      bool MUxAMgzOfX = false;
      bool zHBtpisyZz = false;
      bool GQjHdailny = false;
      bool CAGLVfKRKn = false;
      bool nzJieZpNTc = false;
      bool bImeQwkoVl = false;
      bool xNagVyBoXJ = false;
      bool YbmlLHHAbE = false;
      string ngGASKsPXc;
      string gftDxiNYad;
      string uOKPQeVEna;
      string pbBhTynARY;
      string yQCIHozqez;
      string BihfYYVpjm;
      string onbwmFeLjy;
      string tNGCfdLCHa;
      string fdYoZGsVIu;
      string cxPdjJoGVB;
      string KmHgEnbfzu;
      string MTiIHKOlWf;
      string MJDnUwxbRV;
      string oFgGPrWrkl;
      string dNVNiJOGWZ;
      string uCjpoBjSMH;
      string qANdFGlbrO;
      string mWBkBymoFK;
      string gpFralVqQO;
      string IEfctdzrIb;
      if(ngGASKsPXc == KmHgEnbfzu){WmNHmYBznp = true;}
      else if(KmHgEnbfzu == ngGASKsPXc){BHRXUmNoHd = true;}
      if(gftDxiNYad == MTiIHKOlWf){NtMBZAtVCS = true;}
      else if(MTiIHKOlWf == gftDxiNYad){hqHJMVGNdW = true;}
      if(uOKPQeVEna == MJDnUwxbRV){juKdFhpYpW = true;}
      else if(MJDnUwxbRV == uOKPQeVEna){MUxAMgzOfX = true;}
      if(pbBhTynARY == oFgGPrWrkl){yugdntbyFC = true;}
      else if(oFgGPrWrkl == pbBhTynARY){zHBtpisyZz = true;}
      if(yQCIHozqez == dNVNiJOGWZ){kWCaBOqeCt = true;}
      else if(dNVNiJOGWZ == yQCIHozqez){GQjHdailny = true;}
      if(BihfYYVpjm == uCjpoBjSMH){jdooqabjBE = true;}
      else if(uCjpoBjSMH == BihfYYVpjm){CAGLVfKRKn = true;}
      if(onbwmFeLjy == qANdFGlbrO){hbJRqSMiMe = true;}
      else if(qANdFGlbrO == onbwmFeLjy){nzJieZpNTc = true;}
      if(tNGCfdLCHa == mWBkBymoFK){YwPAgMsjcq = true;}
      if(fdYoZGsVIu == gpFralVqQO){qLVumUFrlM = true;}
      if(cxPdjJoGVB == IEfctdzrIb){SqwBUINkih = true;}
      while(mWBkBymoFK == tNGCfdLCHa){bImeQwkoVl = true;}
      while(gpFralVqQO == gpFralVqQO){xNagVyBoXJ = true;}
      while(IEfctdzrIb == IEfctdzrIb){YbmlLHHAbE = true;}
      if(WmNHmYBznp == true){WmNHmYBznp = false;}
      if(NtMBZAtVCS == true){NtMBZAtVCS = false;}
      if(juKdFhpYpW == true){juKdFhpYpW = false;}
      if(yugdntbyFC == true){yugdntbyFC = false;}
      if(kWCaBOqeCt == true){kWCaBOqeCt = false;}
      if(jdooqabjBE == true){jdooqabjBE = false;}
      if(hbJRqSMiMe == true){hbJRqSMiMe = false;}
      if(YwPAgMsjcq == true){YwPAgMsjcq = false;}
      if(qLVumUFrlM == true){qLVumUFrlM = false;}
      if(SqwBUINkih == true){SqwBUINkih = false;}
      if(BHRXUmNoHd == true){BHRXUmNoHd = false;}
      if(hqHJMVGNdW == true){hqHJMVGNdW = false;}
      if(MUxAMgzOfX == true){MUxAMgzOfX = false;}
      if(zHBtpisyZz == true){zHBtpisyZz = false;}
      if(GQjHdailny == true){GQjHdailny = false;}
      if(CAGLVfKRKn == true){CAGLVfKRKn = false;}
      if(nzJieZpNTc == true){nzJieZpNTc = false;}
      if(bImeQwkoVl == true){bImeQwkoVl = false;}
      if(xNagVyBoXJ == true){xNagVyBoXJ = false;}
      if(YbmlLHHAbE == true){YbmlLHHAbE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBCJFGVQCL
{ 
  void SyrnnCrUsK()
  { 
      bool MnkWZfScwh = false;
      bool SWRuruHPGS = false;
      bool xqBwIqxAWK = false;
      bool lnohttMQwI = false;
      bool fTryptwxqB = false;
      bool SwXVrVlnNh = false;
      bool iRGluegjBx = false;
      bool iqTxlcyDGO = false;
      bool tAJUqpPSoY = false;
      bool HYCOZONGCL = false;
      bool MMusSbcZjO = false;
      bool WihzniIltF = false;
      bool OOtcoKnEXX = false;
      bool PrAtBgEPBO = false;
      bool NpiaBYpCZp = false;
      bool FaLxwyRSEI = false;
      bool nXBLzehmyG = false;
      bool esjerYeTaQ = false;
      bool TlegSnfDyD = false;
      bool OkKsapnXbW = false;
      string kbtLHlhaaM;
      string FkKwOXGNoG;
      string gtKHiIczpq;
      string FTIuPPCWny;
      string ngrxQHCbCA;
      string REeZTqRlcy;
      string JhjjHlcOfz;
      string UiYqRzCMqa;
      string GAxoYAnibY;
      string yQtooGxHod;
      string enwCehenHT;
      string oEtCrJjtKH;
      string xslHAEojBL;
      string CtXMuSDtKp;
      string VzaHjsVqwe;
      string VCxhglBoCa;
      string sumwRtghGZ;
      string FojTkySeWG;
      string ixmWozxofJ;
      string QOrixaMeoo;
      if(kbtLHlhaaM == enwCehenHT){MnkWZfScwh = true;}
      else if(enwCehenHT == kbtLHlhaaM){MMusSbcZjO = true;}
      if(FkKwOXGNoG == oEtCrJjtKH){SWRuruHPGS = true;}
      else if(oEtCrJjtKH == FkKwOXGNoG){WihzniIltF = true;}
      if(gtKHiIczpq == xslHAEojBL){xqBwIqxAWK = true;}
      else if(xslHAEojBL == gtKHiIczpq){OOtcoKnEXX = true;}
      if(FTIuPPCWny == CtXMuSDtKp){lnohttMQwI = true;}
      else if(CtXMuSDtKp == FTIuPPCWny){PrAtBgEPBO = true;}
      if(ngrxQHCbCA == VzaHjsVqwe){fTryptwxqB = true;}
      else if(VzaHjsVqwe == ngrxQHCbCA){NpiaBYpCZp = true;}
      if(REeZTqRlcy == VCxhglBoCa){SwXVrVlnNh = true;}
      else if(VCxhglBoCa == REeZTqRlcy){FaLxwyRSEI = true;}
      if(JhjjHlcOfz == sumwRtghGZ){iRGluegjBx = true;}
      else if(sumwRtghGZ == JhjjHlcOfz){nXBLzehmyG = true;}
      if(UiYqRzCMqa == FojTkySeWG){iqTxlcyDGO = true;}
      if(GAxoYAnibY == ixmWozxofJ){tAJUqpPSoY = true;}
      if(yQtooGxHod == QOrixaMeoo){HYCOZONGCL = true;}
      while(FojTkySeWG == UiYqRzCMqa){esjerYeTaQ = true;}
      while(ixmWozxofJ == ixmWozxofJ){TlegSnfDyD = true;}
      while(QOrixaMeoo == QOrixaMeoo){OkKsapnXbW = true;}
      if(MnkWZfScwh == true){MnkWZfScwh = false;}
      if(SWRuruHPGS == true){SWRuruHPGS = false;}
      if(xqBwIqxAWK == true){xqBwIqxAWK = false;}
      if(lnohttMQwI == true){lnohttMQwI = false;}
      if(fTryptwxqB == true){fTryptwxqB = false;}
      if(SwXVrVlnNh == true){SwXVrVlnNh = false;}
      if(iRGluegjBx == true){iRGluegjBx = false;}
      if(iqTxlcyDGO == true){iqTxlcyDGO = false;}
      if(tAJUqpPSoY == true){tAJUqpPSoY = false;}
      if(HYCOZONGCL == true){HYCOZONGCL = false;}
      if(MMusSbcZjO == true){MMusSbcZjO = false;}
      if(WihzniIltF == true){WihzniIltF = false;}
      if(OOtcoKnEXX == true){OOtcoKnEXX = false;}
      if(PrAtBgEPBO == true){PrAtBgEPBO = false;}
      if(NpiaBYpCZp == true){NpiaBYpCZp = false;}
      if(FaLxwyRSEI == true){FaLxwyRSEI = false;}
      if(nXBLzehmyG == true){nXBLzehmyG = false;}
      if(esjerYeTaQ == true){esjerYeTaQ = false;}
      if(TlegSnfDyD == true){TlegSnfDyD = false;}
      if(OkKsapnXbW == true){OkKsapnXbW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YATEFARPQC
{ 
  void EkfKdudhLf()
  { 
      bool eOoFbxpVQX = false;
      bool fkGTLIjsWV = false;
      bool PWlyRaZrPE = false;
      bool sdcadcaXRi = false;
      bool bhfJMsdELb = false;
      bool xLSYPHcqnB = false;
      bool XyFLeCHfpi = false;
      bool gManthqbkX = false;
      bool xUgmGgKEKV = false;
      bool AjiQKdbTdJ = false;
      bool lxObtkjeeh = false;
      bool QAFQDDQSFx = false;
      bool rDUTixdJcP = false;
      bool FWybkzFErV = false;
      bool xeYcFzdSNH = false;
      bool MJOgRicusx = false;
      bool GaCObtCdeE = false;
      bool xLZiAMdrOi = false;
      bool SLwUDwHQKC = false;
      bool WKKuOWcJAL = false;
      string pHMETUmCSV;
      string QWlzERcqGJ;
      string LlzcKdqzJX;
      string yNhfxbnLab;
      string jpdLODXWMF;
      string nIAGiDIjsp;
      string dmsuXCoFBb;
      string cQQeZVInNH;
      string FTmDioMaxt;
      string TDSkxwwimL;
      string NRUkcXrUgN;
      string tUVkjJApLi;
      string oNIHHYyegc;
      string YZACsnyBaK;
      string wrtjAzhgBm;
      string wGWDVAJNcD;
      string ZNmDnTTSqu;
      string LyPBmxTYHI;
      string qQctgSDwgs;
      string djYWkhEpuf;
      if(pHMETUmCSV == NRUkcXrUgN){eOoFbxpVQX = true;}
      else if(NRUkcXrUgN == pHMETUmCSV){lxObtkjeeh = true;}
      if(QWlzERcqGJ == tUVkjJApLi){fkGTLIjsWV = true;}
      else if(tUVkjJApLi == QWlzERcqGJ){QAFQDDQSFx = true;}
      if(LlzcKdqzJX == oNIHHYyegc){PWlyRaZrPE = true;}
      else if(oNIHHYyegc == LlzcKdqzJX){rDUTixdJcP = true;}
      if(yNhfxbnLab == YZACsnyBaK){sdcadcaXRi = true;}
      else if(YZACsnyBaK == yNhfxbnLab){FWybkzFErV = true;}
      if(jpdLODXWMF == wrtjAzhgBm){bhfJMsdELb = true;}
      else if(wrtjAzhgBm == jpdLODXWMF){xeYcFzdSNH = true;}
      if(nIAGiDIjsp == wGWDVAJNcD){xLSYPHcqnB = true;}
      else if(wGWDVAJNcD == nIAGiDIjsp){MJOgRicusx = true;}
      if(dmsuXCoFBb == ZNmDnTTSqu){XyFLeCHfpi = true;}
      else if(ZNmDnTTSqu == dmsuXCoFBb){GaCObtCdeE = true;}
      if(cQQeZVInNH == LyPBmxTYHI){gManthqbkX = true;}
      if(FTmDioMaxt == qQctgSDwgs){xUgmGgKEKV = true;}
      if(TDSkxwwimL == djYWkhEpuf){AjiQKdbTdJ = true;}
      while(LyPBmxTYHI == cQQeZVInNH){xLZiAMdrOi = true;}
      while(qQctgSDwgs == qQctgSDwgs){SLwUDwHQKC = true;}
      while(djYWkhEpuf == djYWkhEpuf){WKKuOWcJAL = true;}
      if(eOoFbxpVQX == true){eOoFbxpVQX = false;}
      if(fkGTLIjsWV == true){fkGTLIjsWV = false;}
      if(PWlyRaZrPE == true){PWlyRaZrPE = false;}
      if(sdcadcaXRi == true){sdcadcaXRi = false;}
      if(bhfJMsdELb == true){bhfJMsdELb = false;}
      if(xLSYPHcqnB == true){xLSYPHcqnB = false;}
      if(XyFLeCHfpi == true){XyFLeCHfpi = false;}
      if(gManthqbkX == true){gManthqbkX = false;}
      if(xUgmGgKEKV == true){xUgmGgKEKV = false;}
      if(AjiQKdbTdJ == true){AjiQKdbTdJ = false;}
      if(lxObtkjeeh == true){lxObtkjeeh = false;}
      if(QAFQDDQSFx == true){QAFQDDQSFx = false;}
      if(rDUTixdJcP == true){rDUTixdJcP = false;}
      if(FWybkzFErV == true){FWybkzFErV = false;}
      if(xeYcFzdSNH == true){xeYcFzdSNH = false;}
      if(MJOgRicusx == true){MJOgRicusx = false;}
      if(GaCObtCdeE == true){GaCObtCdeE = false;}
      if(xLZiAMdrOi == true){xLZiAMdrOi = false;}
      if(SLwUDwHQKC == true){SLwUDwHQKC = false;}
      if(WKKuOWcJAL == true){WKKuOWcJAL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZCKEYZUAB
{ 
  void UdYOPBAjFE()
  { 
      bool UAtWgiyTMT = false;
      bool VlmBaqjMAh = false;
      bool cNLETjThBg = false;
      bool ppUltAnfIJ = false;
      bool xzJVdynfHn = false;
      bool GczFyGnoCw = false;
      bool OPSfcfRBGa = false;
      bool CDDpjcEoaV = false;
      bool wnaMZNqOmn = false;
      bool LzdLtggdsy = false;
      bool flYfkDYIUU = false;
      bool CzNgAaoFFP = false;
      bool nCNSODYrwD = false;
      bool wZuboJPtbW = false;
      bool nhtSlLkxLT = false;
      bool qbXdJdYFRh = false;
      bool dgMRYbDlqp = false;
      bool KuchbGItgC = false;
      bool RbgcLTCRRL = false;
      bool kJbtsGVbtJ = false;
      string zKulYlTaPD;
      string eDOiztyiBg;
      string AgZoIrglMT;
      string GdCmHgyxrl;
      string SCehaxtPDY;
      string IJAkjSjFdg;
      string FhOuxBAbbR;
      string uBpPOxCrOK;
      string xQinLwcQCo;
      string xsSLgjnikY;
      string xSnkdHSkWl;
      string PrqSinzZjA;
      string YjYlUChehd;
      string JSGpNecxJE;
      string drsQYFBzbr;
      string kNzjzMtBQb;
      string YmCscxkBFE;
      string LBPfWfpHNO;
      string AhDosuTWpA;
      string jagheppzmb;
      if(zKulYlTaPD == xSnkdHSkWl){UAtWgiyTMT = true;}
      else if(xSnkdHSkWl == zKulYlTaPD){flYfkDYIUU = true;}
      if(eDOiztyiBg == PrqSinzZjA){VlmBaqjMAh = true;}
      else if(PrqSinzZjA == eDOiztyiBg){CzNgAaoFFP = true;}
      if(AgZoIrglMT == YjYlUChehd){cNLETjThBg = true;}
      else if(YjYlUChehd == AgZoIrglMT){nCNSODYrwD = true;}
      if(GdCmHgyxrl == JSGpNecxJE){ppUltAnfIJ = true;}
      else if(JSGpNecxJE == GdCmHgyxrl){wZuboJPtbW = true;}
      if(SCehaxtPDY == drsQYFBzbr){xzJVdynfHn = true;}
      else if(drsQYFBzbr == SCehaxtPDY){nhtSlLkxLT = true;}
      if(IJAkjSjFdg == kNzjzMtBQb){GczFyGnoCw = true;}
      else if(kNzjzMtBQb == IJAkjSjFdg){qbXdJdYFRh = true;}
      if(FhOuxBAbbR == YmCscxkBFE){OPSfcfRBGa = true;}
      else if(YmCscxkBFE == FhOuxBAbbR){dgMRYbDlqp = true;}
      if(uBpPOxCrOK == LBPfWfpHNO){CDDpjcEoaV = true;}
      if(xQinLwcQCo == AhDosuTWpA){wnaMZNqOmn = true;}
      if(xsSLgjnikY == jagheppzmb){LzdLtggdsy = true;}
      while(LBPfWfpHNO == uBpPOxCrOK){KuchbGItgC = true;}
      while(AhDosuTWpA == AhDosuTWpA){RbgcLTCRRL = true;}
      while(jagheppzmb == jagheppzmb){kJbtsGVbtJ = true;}
      if(UAtWgiyTMT == true){UAtWgiyTMT = false;}
      if(VlmBaqjMAh == true){VlmBaqjMAh = false;}
      if(cNLETjThBg == true){cNLETjThBg = false;}
      if(ppUltAnfIJ == true){ppUltAnfIJ = false;}
      if(xzJVdynfHn == true){xzJVdynfHn = false;}
      if(GczFyGnoCw == true){GczFyGnoCw = false;}
      if(OPSfcfRBGa == true){OPSfcfRBGa = false;}
      if(CDDpjcEoaV == true){CDDpjcEoaV = false;}
      if(wnaMZNqOmn == true){wnaMZNqOmn = false;}
      if(LzdLtggdsy == true){LzdLtggdsy = false;}
      if(flYfkDYIUU == true){flYfkDYIUU = false;}
      if(CzNgAaoFFP == true){CzNgAaoFFP = false;}
      if(nCNSODYrwD == true){nCNSODYrwD = false;}
      if(wZuboJPtbW == true){wZuboJPtbW = false;}
      if(nhtSlLkxLT == true){nhtSlLkxLT = false;}
      if(qbXdJdYFRh == true){qbXdJdYFRh = false;}
      if(dgMRYbDlqp == true){dgMRYbDlqp = false;}
      if(KuchbGItgC == true){KuchbGItgC = false;}
      if(RbgcLTCRRL == true){RbgcLTCRRL = false;}
      if(kJbtsGVbtJ == true){kJbtsGVbtJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACGHNVXHNV
{ 
  void fkzUcqtrib()
  { 
      bool gOsEjKXhgf = false;
      bool QHaqJWfhoJ = false;
      bool zcGJfeEiXI = false;
      bool EQwiIQTERa = false;
      bool RWhVWHEtBd = false;
      bool YkXfsDIjXF = false;
      bool GnKXaALqis = false;
      bool CaQOqcujmY = false;
      bool ZKhsiSrPpE = false;
      bool HjgMTdLJtV = false;
      bool uMKHbyUInP = false;
      bool IXxyewFQoI = false;
      bool HuBdkRtDtN = false;
      bool QkpQcMzZRk = false;
      bool yjbawilhgX = false;
      bool XuTlNzLgWJ = false;
      bool DQOZyWhgVR = false;
      bool xfzEKXTahB = false;
      bool fMWVpVRECc = false;
      bool BRDIggUBbZ = false;
      string NZPBCaRKZG;
      string HlylaNVAab;
      string YYNUcUWwVp;
      string FyPaBlculq;
      string eCyDmhrMic;
      string PMPMdoMtYg;
      string DVniAJVXkn;
      string kaNjxVZKht;
      string cKMsasiDxL;
      string ZiVEmJNOCd;
      string MTburoyfOH;
      string OBLeEsIuIH;
      string aRaYOCEJwm;
      string IKIEhIhRAk;
      string tCnoxYWqAt;
      string BSGtDtsCgo;
      string joibzErHxu;
      string KptXNXckbo;
      string fNIBloEOBm;
      string OfkKAFSMor;
      if(NZPBCaRKZG == MTburoyfOH){gOsEjKXhgf = true;}
      else if(MTburoyfOH == NZPBCaRKZG){uMKHbyUInP = true;}
      if(HlylaNVAab == OBLeEsIuIH){QHaqJWfhoJ = true;}
      else if(OBLeEsIuIH == HlylaNVAab){IXxyewFQoI = true;}
      if(YYNUcUWwVp == aRaYOCEJwm){zcGJfeEiXI = true;}
      else if(aRaYOCEJwm == YYNUcUWwVp){HuBdkRtDtN = true;}
      if(FyPaBlculq == IKIEhIhRAk){EQwiIQTERa = true;}
      else if(IKIEhIhRAk == FyPaBlculq){QkpQcMzZRk = true;}
      if(eCyDmhrMic == tCnoxYWqAt){RWhVWHEtBd = true;}
      else if(tCnoxYWqAt == eCyDmhrMic){yjbawilhgX = true;}
      if(PMPMdoMtYg == BSGtDtsCgo){YkXfsDIjXF = true;}
      else if(BSGtDtsCgo == PMPMdoMtYg){XuTlNzLgWJ = true;}
      if(DVniAJVXkn == joibzErHxu){GnKXaALqis = true;}
      else if(joibzErHxu == DVniAJVXkn){DQOZyWhgVR = true;}
      if(kaNjxVZKht == KptXNXckbo){CaQOqcujmY = true;}
      if(cKMsasiDxL == fNIBloEOBm){ZKhsiSrPpE = true;}
      if(ZiVEmJNOCd == OfkKAFSMor){HjgMTdLJtV = true;}
      while(KptXNXckbo == kaNjxVZKht){xfzEKXTahB = true;}
      while(fNIBloEOBm == fNIBloEOBm){fMWVpVRECc = true;}
      while(OfkKAFSMor == OfkKAFSMor){BRDIggUBbZ = true;}
      if(gOsEjKXhgf == true){gOsEjKXhgf = false;}
      if(QHaqJWfhoJ == true){QHaqJWfhoJ = false;}
      if(zcGJfeEiXI == true){zcGJfeEiXI = false;}
      if(EQwiIQTERa == true){EQwiIQTERa = false;}
      if(RWhVWHEtBd == true){RWhVWHEtBd = false;}
      if(YkXfsDIjXF == true){YkXfsDIjXF = false;}
      if(GnKXaALqis == true){GnKXaALqis = false;}
      if(CaQOqcujmY == true){CaQOqcujmY = false;}
      if(ZKhsiSrPpE == true){ZKhsiSrPpE = false;}
      if(HjgMTdLJtV == true){HjgMTdLJtV = false;}
      if(uMKHbyUInP == true){uMKHbyUInP = false;}
      if(IXxyewFQoI == true){IXxyewFQoI = false;}
      if(HuBdkRtDtN == true){HuBdkRtDtN = false;}
      if(QkpQcMzZRk == true){QkpQcMzZRk = false;}
      if(yjbawilhgX == true){yjbawilhgX = false;}
      if(XuTlNzLgWJ == true){XuTlNzLgWJ = false;}
      if(DQOZyWhgVR == true){DQOZyWhgVR = false;}
      if(xfzEKXTahB == true){xfzEKXTahB = false;}
      if(fMWVpVRECc == true){fMWVpVRECc = false;}
      if(BRDIggUBbZ == true){BRDIggUBbZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRARNNEKIL
{ 
  void jUBtIeZRrC()
  { 
      bool iweBmniCUW = false;
      bool OkZcuoYgzf = false;
      bool CLENCjLkMw = false;
      bool bZXTTBgdWr = false;
      bool nOgIgNJfqU = false;
      bool fZsAqXqRyD = false;
      bool cyoYtnMGIt = false;
      bool HtJHqmewgo = false;
      bool ZesrPCgWbw = false;
      bool KPfTOpYHNr = false;
      bool BDWxMkPkJD = false;
      bool stkJcxFxIr = false;
      bool HodMirNprA = false;
      bool OWhnnVHuee = false;
      bool luNYDPeVpR = false;
      bool kbzVjLZKNU = false;
      bool WZrIoVMwVH = false;
      bool pJSdFMbEJT = false;
      bool MrzaPlXMDb = false;
      bool wxhJHLCEig = false;
      string KaByNVWTzW;
      string dBKSFcxcxH;
      string TFnFIFroIA;
      string PlSAZVxRAe;
      string AYHlfHnGRD;
      string jRcaeFmuoH;
      string dhKzHqiJsj;
      string fecSGtxBZB;
      string RkXFQyIrUT;
      string hBcsASNHen;
      string XdMhXEoKTk;
      string HkVmorJFiJ;
      string hqoYBdCjSn;
      string foWkcnXogL;
      string JyXjLxfoDH;
      string IHYUGgomgs;
      string BEqeESNjJB;
      string UTYWAiSEND;
      string xMfKfXQCew;
      string yjImJEGrfs;
      if(KaByNVWTzW == XdMhXEoKTk){iweBmniCUW = true;}
      else if(XdMhXEoKTk == KaByNVWTzW){BDWxMkPkJD = true;}
      if(dBKSFcxcxH == HkVmorJFiJ){OkZcuoYgzf = true;}
      else if(HkVmorJFiJ == dBKSFcxcxH){stkJcxFxIr = true;}
      if(TFnFIFroIA == hqoYBdCjSn){CLENCjLkMw = true;}
      else if(hqoYBdCjSn == TFnFIFroIA){HodMirNprA = true;}
      if(PlSAZVxRAe == foWkcnXogL){bZXTTBgdWr = true;}
      else if(foWkcnXogL == PlSAZVxRAe){OWhnnVHuee = true;}
      if(AYHlfHnGRD == JyXjLxfoDH){nOgIgNJfqU = true;}
      else if(JyXjLxfoDH == AYHlfHnGRD){luNYDPeVpR = true;}
      if(jRcaeFmuoH == IHYUGgomgs){fZsAqXqRyD = true;}
      else if(IHYUGgomgs == jRcaeFmuoH){kbzVjLZKNU = true;}
      if(dhKzHqiJsj == BEqeESNjJB){cyoYtnMGIt = true;}
      else if(BEqeESNjJB == dhKzHqiJsj){WZrIoVMwVH = true;}
      if(fecSGtxBZB == UTYWAiSEND){HtJHqmewgo = true;}
      if(RkXFQyIrUT == xMfKfXQCew){ZesrPCgWbw = true;}
      if(hBcsASNHen == yjImJEGrfs){KPfTOpYHNr = true;}
      while(UTYWAiSEND == fecSGtxBZB){pJSdFMbEJT = true;}
      while(xMfKfXQCew == xMfKfXQCew){MrzaPlXMDb = true;}
      while(yjImJEGrfs == yjImJEGrfs){wxhJHLCEig = true;}
      if(iweBmniCUW == true){iweBmniCUW = false;}
      if(OkZcuoYgzf == true){OkZcuoYgzf = false;}
      if(CLENCjLkMw == true){CLENCjLkMw = false;}
      if(bZXTTBgdWr == true){bZXTTBgdWr = false;}
      if(nOgIgNJfqU == true){nOgIgNJfqU = false;}
      if(fZsAqXqRyD == true){fZsAqXqRyD = false;}
      if(cyoYtnMGIt == true){cyoYtnMGIt = false;}
      if(HtJHqmewgo == true){HtJHqmewgo = false;}
      if(ZesrPCgWbw == true){ZesrPCgWbw = false;}
      if(KPfTOpYHNr == true){KPfTOpYHNr = false;}
      if(BDWxMkPkJD == true){BDWxMkPkJD = false;}
      if(stkJcxFxIr == true){stkJcxFxIr = false;}
      if(HodMirNprA == true){HodMirNprA = false;}
      if(OWhnnVHuee == true){OWhnnVHuee = false;}
      if(luNYDPeVpR == true){luNYDPeVpR = false;}
      if(kbzVjLZKNU == true){kbzVjLZKNU = false;}
      if(WZrIoVMwVH == true){WZrIoVMwVH = false;}
      if(pJSdFMbEJT == true){pJSdFMbEJT = false;}
      if(MrzaPlXMDb == true){MrzaPlXMDb = false;}
      if(wxhJHLCEig == true){wxhJHLCEig = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVJAULLJBW
{ 
  void mKAxSjjXWQ()
  { 
      bool HrMlKyoLZT = false;
      bool piIOHYGTYI = false;
      bool qdnBAPEStJ = false;
      bool nXjcFXLaTY = false;
      bool zacQplbTZA = false;
      bool eXoqGcEKlu = false;
      bool sVRQeSyeJi = false;
      bool MeAAIPBXLN = false;
      bool njrtdQhsWc = false;
      bool TBoYfcJMlX = false;
      bool mwKpmzWohq = false;
      bool bgzXHIdWlO = false;
      bool kFIfPLpbUe = false;
      bool GnkmaqZBGd = false;
      bool srKfBmBQQW = false;
      bool zlaXlhmeab = false;
      bool JuUCjmuLxP = false;
      bool ibPHUrtcec = false;
      bool JZKxfTNNBs = false;
      bool EtaeUyWHuN = false;
      string OcAFjtFApX;
      string pcecAEdtbT;
      string shXhZpSQeN;
      string XnPZDBtUJH;
      string ZRwYZnDLbR;
      string aZIzCgFSet;
      string bnUbACNEYy;
      string KJjUtalyIk;
      string lHoNmxePXW;
      string wboOekwTYX;
      string azldGQpnEa;
      string uHJsHUzHoC;
      string WxfCBiTUoI;
      string dRYkKmUKGV;
      string HpKwaoRuHK;
      string loeVAcSjbX;
      string xUywxdhYiU;
      string AnASufljaM;
      string QYNdWnmDjg;
      string UjihYlrOzx;
      if(OcAFjtFApX == azldGQpnEa){HrMlKyoLZT = true;}
      else if(azldGQpnEa == OcAFjtFApX){mwKpmzWohq = true;}
      if(pcecAEdtbT == uHJsHUzHoC){piIOHYGTYI = true;}
      else if(uHJsHUzHoC == pcecAEdtbT){bgzXHIdWlO = true;}
      if(shXhZpSQeN == WxfCBiTUoI){qdnBAPEStJ = true;}
      else if(WxfCBiTUoI == shXhZpSQeN){kFIfPLpbUe = true;}
      if(XnPZDBtUJH == dRYkKmUKGV){nXjcFXLaTY = true;}
      else if(dRYkKmUKGV == XnPZDBtUJH){GnkmaqZBGd = true;}
      if(ZRwYZnDLbR == HpKwaoRuHK){zacQplbTZA = true;}
      else if(HpKwaoRuHK == ZRwYZnDLbR){srKfBmBQQW = true;}
      if(aZIzCgFSet == loeVAcSjbX){eXoqGcEKlu = true;}
      else if(loeVAcSjbX == aZIzCgFSet){zlaXlhmeab = true;}
      if(bnUbACNEYy == xUywxdhYiU){sVRQeSyeJi = true;}
      else if(xUywxdhYiU == bnUbACNEYy){JuUCjmuLxP = true;}
      if(KJjUtalyIk == AnASufljaM){MeAAIPBXLN = true;}
      if(lHoNmxePXW == QYNdWnmDjg){njrtdQhsWc = true;}
      if(wboOekwTYX == UjihYlrOzx){TBoYfcJMlX = true;}
      while(AnASufljaM == KJjUtalyIk){ibPHUrtcec = true;}
      while(QYNdWnmDjg == QYNdWnmDjg){JZKxfTNNBs = true;}
      while(UjihYlrOzx == UjihYlrOzx){EtaeUyWHuN = true;}
      if(HrMlKyoLZT == true){HrMlKyoLZT = false;}
      if(piIOHYGTYI == true){piIOHYGTYI = false;}
      if(qdnBAPEStJ == true){qdnBAPEStJ = false;}
      if(nXjcFXLaTY == true){nXjcFXLaTY = false;}
      if(zacQplbTZA == true){zacQplbTZA = false;}
      if(eXoqGcEKlu == true){eXoqGcEKlu = false;}
      if(sVRQeSyeJi == true){sVRQeSyeJi = false;}
      if(MeAAIPBXLN == true){MeAAIPBXLN = false;}
      if(njrtdQhsWc == true){njrtdQhsWc = false;}
      if(TBoYfcJMlX == true){TBoYfcJMlX = false;}
      if(mwKpmzWohq == true){mwKpmzWohq = false;}
      if(bgzXHIdWlO == true){bgzXHIdWlO = false;}
      if(kFIfPLpbUe == true){kFIfPLpbUe = false;}
      if(GnkmaqZBGd == true){GnkmaqZBGd = false;}
      if(srKfBmBQQW == true){srKfBmBQQW = false;}
      if(zlaXlhmeab == true){zlaXlhmeab = false;}
      if(JuUCjmuLxP == true){JuUCjmuLxP = false;}
      if(ibPHUrtcec == true){ibPHUrtcec = false;}
      if(JZKxfTNNBs == true){JZKxfTNNBs = false;}
      if(EtaeUyWHuN == true){EtaeUyWHuN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKCEMJUNSA
{ 
  void KsudaZRywE()
  { 
      bool yYbkGXqRXm = false;
      bool fOXiAMCOEA = false;
      bool lRBgyZLVkV = false;
      bool hWNAjnxAAk = false;
      bool mMlVYhxoIA = false;
      bool RIUrcgWumg = false;
      bool MUfCEIBWzM = false;
      bool OCNSNYefIQ = false;
      bool bVNkDZBUWC = false;
      bool QCMSYRfjQP = false;
      bool gZowkOtCeE = false;
      bool CqmVFpHuye = false;
      bool HfAxuMousw = false;
      bool rtOrjBfQAn = false;
      bool ezpSAYPpNi = false;
      bool JkklIAZrAX = false;
      bool YzIiLHctlD = false;
      bool JquJAIogxW = false;
      bool xyhKlGJcji = false;
      bool anPbOepHGs = false;
      string SGLVjIbFfE;
      string nFtGCnGpOh;
      string btSGKDOgaL;
      string mRBKRQzobA;
      string eCieNQjXNx;
      string nVthFXnEKg;
      string tueUQVDjol;
      string oQOOCYKmss;
      string SqSdWQXTEs;
      string btduFjXONq;
      string MAhbHXHeff;
      string NBLRNDbBxz;
      string yjeuJulSJR;
      string BwYBgSIqVy;
      string JrmXfahMgC;
      string IWQOsbVmRM;
      string lnVNeQbJku;
      string ujeypFwGPh;
      string MYlHJdeKIE;
      string xVYIMUWZsO;
      if(SGLVjIbFfE == MAhbHXHeff){yYbkGXqRXm = true;}
      else if(MAhbHXHeff == SGLVjIbFfE){gZowkOtCeE = true;}
      if(nFtGCnGpOh == NBLRNDbBxz){fOXiAMCOEA = true;}
      else if(NBLRNDbBxz == nFtGCnGpOh){CqmVFpHuye = true;}
      if(btSGKDOgaL == yjeuJulSJR){lRBgyZLVkV = true;}
      else if(yjeuJulSJR == btSGKDOgaL){HfAxuMousw = true;}
      if(mRBKRQzobA == BwYBgSIqVy){hWNAjnxAAk = true;}
      else if(BwYBgSIqVy == mRBKRQzobA){rtOrjBfQAn = true;}
      if(eCieNQjXNx == JrmXfahMgC){mMlVYhxoIA = true;}
      else if(JrmXfahMgC == eCieNQjXNx){ezpSAYPpNi = true;}
      if(nVthFXnEKg == IWQOsbVmRM){RIUrcgWumg = true;}
      else if(IWQOsbVmRM == nVthFXnEKg){JkklIAZrAX = true;}
      if(tueUQVDjol == lnVNeQbJku){MUfCEIBWzM = true;}
      else if(lnVNeQbJku == tueUQVDjol){YzIiLHctlD = true;}
      if(oQOOCYKmss == ujeypFwGPh){OCNSNYefIQ = true;}
      if(SqSdWQXTEs == MYlHJdeKIE){bVNkDZBUWC = true;}
      if(btduFjXONq == xVYIMUWZsO){QCMSYRfjQP = true;}
      while(ujeypFwGPh == oQOOCYKmss){JquJAIogxW = true;}
      while(MYlHJdeKIE == MYlHJdeKIE){xyhKlGJcji = true;}
      while(xVYIMUWZsO == xVYIMUWZsO){anPbOepHGs = true;}
      if(yYbkGXqRXm == true){yYbkGXqRXm = false;}
      if(fOXiAMCOEA == true){fOXiAMCOEA = false;}
      if(lRBgyZLVkV == true){lRBgyZLVkV = false;}
      if(hWNAjnxAAk == true){hWNAjnxAAk = false;}
      if(mMlVYhxoIA == true){mMlVYhxoIA = false;}
      if(RIUrcgWumg == true){RIUrcgWumg = false;}
      if(MUfCEIBWzM == true){MUfCEIBWzM = false;}
      if(OCNSNYefIQ == true){OCNSNYefIQ = false;}
      if(bVNkDZBUWC == true){bVNkDZBUWC = false;}
      if(QCMSYRfjQP == true){QCMSYRfjQP = false;}
      if(gZowkOtCeE == true){gZowkOtCeE = false;}
      if(CqmVFpHuye == true){CqmVFpHuye = false;}
      if(HfAxuMousw == true){HfAxuMousw = false;}
      if(rtOrjBfQAn == true){rtOrjBfQAn = false;}
      if(ezpSAYPpNi == true){ezpSAYPpNi = false;}
      if(JkklIAZrAX == true){JkklIAZrAX = false;}
      if(YzIiLHctlD == true){YzIiLHctlD = false;}
      if(JquJAIogxW == true){JquJAIogxW = false;}
      if(xyhKlGJcji == true){xyhKlGJcji = false;}
      if(anPbOepHGs == true){anPbOepHGs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTSPLPXPNS
{ 
  void HUWfcsCnZA()
  { 
      bool gulsIOfCgT = false;
      bool xTFOxVYiuV = false;
      bool EhCCIiIpCM = false;
      bool SOheeGAnom = false;
      bool LZmczCPofb = false;
      bool SzDXizrjjZ = false;
      bool FozTBhlZjq = false;
      bool VktIKdtZCG = false;
      bool STKZtSKJuf = false;
      bool OPDOgVaSbQ = false;
      bool QoFoGhEuNF = false;
      bool ERgdGleZZh = false;
      bool XbeEbFgeao = false;
      bool DbxkocOUTM = false;
      bool NPwoawiZIu = false;
      bool pBrtsnKAMA = false;
      bool AZTYCcUwnd = false;
      bool WJFNTHfpcf = false;
      bool WHWfyCiCqB = false;
      bool SNITLnuWmy = false;
      string DKGCTiNyke;
      string ufpDjJnBfW;
      string uAFaWWhPfm;
      string KTAwjwwWUL;
      string ULIJQyYdLJ;
      string yuLclDEeex;
      string ByRxTafsTn;
      string NQfUBjqwKY;
      string yDEWoPHWJf;
      string rQrXKWsLpp;
      string ReKXugPqbC;
      string LIUGyxttIE;
      string SIimwxYHKd;
      string peFTGSsfbH;
      string zQuHTiulYM;
      string cyDkWJwXby;
      string IHgxMfCAzf;
      string ENSAECMbSM;
      string BlhxBqbTxw;
      string WUEcyriytm;
      if(DKGCTiNyke == ReKXugPqbC){gulsIOfCgT = true;}
      else if(ReKXugPqbC == DKGCTiNyke){QoFoGhEuNF = true;}
      if(ufpDjJnBfW == LIUGyxttIE){xTFOxVYiuV = true;}
      else if(LIUGyxttIE == ufpDjJnBfW){ERgdGleZZh = true;}
      if(uAFaWWhPfm == SIimwxYHKd){EhCCIiIpCM = true;}
      else if(SIimwxYHKd == uAFaWWhPfm){XbeEbFgeao = true;}
      if(KTAwjwwWUL == peFTGSsfbH){SOheeGAnom = true;}
      else if(peFTGSsfbH == KTAwjwwWUL){DbxkocOUTM = true;}
      if(ULIJQyYdLJ == zQuHTiulYM){LZmczCPofb = true;}
      else if(zQuHTiulYM == ULIJQyYdLJ){NPwoawiZIu = true;}
      if(yuLclDEeex == cyDkWJwXby){SzDXizrjjZ = true;}
      else if(cyDkWJwXby == yuLclDEeex){pBrtsnKAMA = true;}
      if(ByRxTafsTn == IHgxMfCAzf){FozTBhlZjq = true;}
      else if(IHgxMfCAzf == ByRxTafsTn){AZTYCcUwnd = true;}
      if(NQfUBjqwKY == ENSAECMbSM){VktIKdtZCG = true;}
      if(yDEWoPHWJf == BlhxBqbTxw){STKZtSKJuf = true;}
      if(rQrXKWsLpp == WUEcyriytm){OPDOgVaSbQ = true;}
      while(ENSAECMbSM == NQfUBjqwKY){WJFNTHfpcf = true;}
      while(BlhxBqbTxw == BlhxBqbTxw){WHWfyCiCqB = true;}
      while(WUEcyriytm == WUEcyriytm){SNITLnuWmy = true;}
      if(gulsIOfCgT == true){gulsIOfCgT = false;}
      if(xTFOxVYiuV == true){xTFOxVYiuV = false;}
      if(EhCCIiIpCM == true){EhCCIiIpCM = false;}
      if(SOheeGAnom == true){SOheeGAnom = false;}
      if(LZmczCPofb == true){LZmczCPofb = false;}
      if(SzDXizrjjZ == true){SzDXizrjjZ = false;}
      if(FozTBhlZjq == true){FozTBhlZjq = false;}
      if(VktIKdtZCG == true){VktIKdtZCG = false;}
      if(STKZtSKJuf == true){STKZtSKJuf = false;}
      if(OPDOgVaSbQ == true){OPDOgVaSbQ = false;}
      if(QoFoGhEuNF == true){QoFoGhEuNF = false;}
      if(ERgdGleZZh == true){ERgdGleZZh = false;}
      if(XbeEbFgeao == true){XbeEbFgeao = false;}
      if(DbxkocOUTM == true){DbxkocOUTM = false;}
      if(NPwoawiZIu == true){NPwoawiZIu = false;}
      if(pBrtsnKAMA == true){pBrtsnKAMA = false;}
      if(AZTYCcUwnd == true){AZTYCcUwnd = false;}
      if(WJFNTHfpcf == true){WJFNTHfpcf = false;}
      if(WHWfyCiCqB == true){WHWfyCiCqB = false;}
      if(SNITLnuWmy == true){SNITLnuWmy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUZGLHZCPU
{ 
  void pBWdGibWhD()
  { 
      bool ijXmuxXRuA = false;
      bool zlWqyxaKCK = false;
      bool ctCQOhImOh = false;
      bool RqUTqAhVKS = false;
      bool whFyhPpNwt = false;
      bool eFhlhogGYN = false;
      bool okDMhHRCzx = false;
      bool PEAiOtoDiy = false;
      bool ruqTDLJhkC = false;
      bool SbxxdKesPZ = false;
      bool ymOyeZFyXn = false;
      bool AdWZUttjIV = false;
      bool yiRxenHCFD = false;
      bool PumIAFfrod = false;
      bool GLKxCoEXbj = false;
      bool QtjtbOVQTp = false;
      bool SCrTXEpOYP = false;
      bool NBuePmYTtp = false;
      bool jiZVlUKsgl = false;
      bool jPXyKESpYy = false;
      string KDreBKGUpj;
      string QBJGzRKgqy;
      string FGahFcQcaM;
      string TGUhukcEwt;
      string ZLFdFnZfjs;
      string lgLUzEbJYX;
      string tcsdQJfbKN;
      string nGkxYsBxbQ;
      string DjshaluAhq;
      string ISeXAwRbNw;
      string HxVVEewNwF;
      string CehIUJjLCd;
      string OftTEVbMxc;
      string aZjfJFOWcu;
      string ogDbndkVDp;
      string LGYigbDBRi;
      string DjQTecuByP;
      string uNhGngbRea;
      string jFJGQTAAyh;
      string BMEtrFPjxK;
      if(KDreBKGUpj == HxVVEewNwF){ijXmuxXRuA = true;}
      else if(HxVVEewNwF == KDreBKGUpj){ymOyeZFyXn = true;}
      if(QBJGzRKgqy == CehIUJjLCd){zlWqyxaKCK = true;}
      else if(CehIUJjLCd == QBJGzRKgqy){AdWZUttjIV = true;}
      if(FGahFcQcaM == OftTEVbMxc){ctCQOhImOh = true;}
      else if(OftTEVbMxc == FGahFcQcaM){yiRxenHCFD = true;}
      if(TGUhukcEwt == aZjfJFOWcu){RqUTqAhVKS = true;}
      else if(aZjfJFOWcu == TGUhukcEwt){PumIAFfrod = true;}
      if(ZLFdFnZfjs == ogDbndkVDp){whFyhPpNwt = true;}
      else if(ogDbndkVDp == ZLFdFnZfjs){GLKxCoEXbj = true;}
      if(lgLUzEbJYX == LGYigbDBRi){eFhlhogGYN = true;}
      else if(LGYigbDBRi == lgLUzEbJYX){QtjtbOVQTp = true;}
      if(tcsdQJfbKN == DjQTecuByP){okDMhHRCzx = true;}
      else if(DjQTecuByP == tcsdQJfbKN){SCrTXEpOYP = true;}
      if(nGkxYsBxbQ == uNhGngbRea){PEAiOtoDiy = true;}
      if(DjshaluAhq == jFJGQTAAyh){ruqTDLJhkC = true;}
      if(ISeXAwRbNw == BMEtrFPjxK){SbxxdKesPZ = true;}
      while(uNhGngbRea == nGkxYsBxbQ){NBuePmYTtp = true;}
      while(jFJGQTAAyh == jFJGQTAAyh){jiZVlUKsgl = true;}
      while(BMEtrFPjxK == BMEtrFPjxK){jPXyKESpYy = true;}
      if(ijXmuxXRuA == true){ijXmuxXRuA = false;}
      if(zlWqyxaKCK == true){zlWqyxaKCK = false;}
      if(ctCQOhImOh == true){ctCQOhImOh = false;}
      if(RqUTqAhVKS == true){RqUTqAhVKS = false;}
      if(whFyhPpNwt == true){whFyhPpNwt = false;}
      if(eFhlhogGYN == true){eFhlhogGYN = false;}
      if(okDMhHRCzx == true){okDMhHRCzx = false;}
      if(PEAiOtoDiy == true){PEAiOtoDiy = false;}
      if(ruqTDLJhkC == true){ruqTDLJhkC = false;}
      if(SbxxdKesPZ == true){SbxxdKesPZ = false;}
      if(ymOyeZFyXn == true){ymOyeZFyXn = false;}
      if(AdWZUttjIV == true){AdWZUttjIV = false;}
      if(yiRxenHCFD == true){yiRxenHCFD = false;}
      if(PumIAFfrod == true){PumIAFfrod = false;}
      if(GLKxCoEXbj == true){GLKxCoEXbj = false;}
      if(QtjtbOVQTp == true){QtjtbOVQTp = false;}
      if(SCrTXEpOYP == true){SCrTXEpOYP = false;}
      if(NBuePmYTtp == true){NBuePmYTtp = false;}
      if(jiZVlUKsgl == true){jiZVlUKsgl = false;}
      if(jPXyKESpYy == true){jPXyKESpYy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DISQVGEBXS
{ 
  void BuqVGXLSQE()
  { 
      bool cjzLJzjrNB = false;
      bool nBYTIUHpwk = false;
      bool QZTwyPHNCE = false;
      bool DqhyNfENyc = false;
      bool KmSIdmNWMg = false;
      bool LSYAPDPDNt = false;
      bool qWpJxwTaFb = false;
      bool PtqTacHLSK = false;
      bool BkAUrkRghK = false;
      bool PBzEknxILg = false;
      bool TlQjRQaFYm = false;
      bool wEkCrGVVQM = false;
      bool dmstMNtmhm = false;
      bool eyAkqOTQCa = false;
      bool JMHtOKQwLd = false;
      bool RbryCgsWXD = false;
      bool VmWlHxEzLc = false;
      bool lESoCReyeB = false;
      bool xybDUDFBhK = false;
      bool VxszFVoVmQ = false;
      string KQljoReTcQ;
      string MGIngQSmax;
      string agRfcXVxtc;
      string jSJLeDVCPB;
      string cTbpaEETNx;
      string IcrRAdyGGQ;
      string uhYAfsxxId;
      string tPWZTHEbEY;
      string SCjxUGZqKB;
      string EPwyFutbKg;
      string GHKiDsGSxs;
      string YWBgysybfY;
      string TGlHYeTYUY;
      string MbRWSKqAsa;
      string AHsRchOOzM;
      string xSwkNAVDKY;
      string YgyXfwFdOm;
      string CxhEXMMTdq;
      string QEYIbtffJR;
      string ompUBTIUlf;
      if(KQljoReTcQ == GHKiDsGSxs){cjzLJzjrNB = true;}
      else if(GHKiDsGSxs == KQljoReTcQ){TlQjRQaFYm = true;}
      if(MGIngQSmax == YWBgysybfY){nBYTIUHpwk = true;}
      else if(YWBgysybfY == MGIngQSmax){wEkCrGVVQM = true;}
      if(agRfcXVxtc == TGlHYeTYUY){QZTwyPHNCE = true;}
      else if(TGlHYeTYUY == agRfcXVxtc){dmstMNtmhm = true;}
      if(jSJLeDVCPB == MbRWSKqAsa){DqhyNfENyc = true;}
      else if(MbRWSKqAsa == jSJLeDVCPB){eyAkqOTQCa = true;}
      if(cTbpaEETNx == AHsRchOOzM){KmSIdmNWMg = true;}
      else if(AHsRchOOzM == cTbpaEETNx){JMHtOKQwLd = true;}
      if(IcrRAdyGGQ == xSwkNAVDKY){LSYAPDPDNt = true;}
      else if(xSwkNAVDKY == IcrRAdyGGQ){RbryCgsWXD = true;}
      if(uhYAfsxxId == YgyXfwFdOm){qWpJxwTaFb = true;}
      else if(YgyXfwFdOm == uhYAfsxxId){VmWlHxEzLc = true;}
      if(tPWZTHEbEY == CxhEXMMTdq){PtqTacHLSK = true;}
      if(SCjxUGZqKB == QEYIbtffJR){BkAUrkRghK = true;}
      if(EPwyFutbKg == ompUBTIUlf){PBzEknxILg = true;}
      while(CxhEXMMTdq == tPWZTHEbEY){lESoCReyeB = true;}
      while(QEYIbtffJR == QEYIbtffJR){xybDUDFBhK = true;}
      while(ompUBTIUlf == ompUBTIUlf){VxszFVoVmQ = true;}
      if(cjzLJzjrNB == true){cjzLJzjrNB = false;}
      if(nBYTIUHpwk == true){nBYTIUHpwk = false;}
      if(QZTwyPHNCE == true){QZTwyPHNCE = false;}
      if(DqhyNfENyc == true){DqhyNfENyc = false;}
      if(KmSIdmNWMg == true){KmSIdmNWMg = false;}
      if(LSYAPDPDNt == true){LSYAPDPDNt = false;}
      if(qWpJxwTaFb == true){qWpJxwTaFb = false;}
      if(PtqTacHLSK == true){PtqTacHLSK = false;}
      if(BkAUrkRghK == true){BkAUrkRghK = false;}
      if(PBzEknxILg == true){PBzEknxILg = false;}
      if(TlQjRQaFYm == true){TlQjRQaFYm = false;}
      if(wEkCrGVVQM == true){wEkCrGVVQM = false;}
      if(dmstMNtmhm == true){dmstMNtmhm = false;}
      if(eyAkqOTQCa == true){eyAkqOTQCa = false;}
      if(JMHtOKQwLd == true){JMHtOKQwLd = false;}
      if(RbryCgsWXD == true){RbryCgsWXD = false;}
      if(VmWlHxEzLc == true){VmWlHxEzLc = false;}
      if(lESoCReyeB == true){lESoCReyeB = false;}
      if(xybDUDFBhK == true){xybDUDFBhK = false;}
      if(VxszFVoVmQ == true){VxszFVoVmQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVYEUGBTYY
{ 
  void BYJupAQEaL()
  { 
      bool JRfPXcJOZH = false;
      bool kGeUaDxeqT = false;
      bool zTWuyEtdIK = false;
      bool cYWfSozVuj = false;
      bool FlTEmOkUsl = false;
      bool yiikrotjQS = false;
      bool ifFPeLizBk = false;
      bool EbiHNNARIj = false;
      bool SZjWLsolmc = false;
      bool uOEcAZfDZa = false;
      bool flSHhVAaWe = false;
      bool obbfzJuiDk = false;
      bool VwLYpoWGHm = false;
      bool hwrgEfHbnp = false;
      bool sOOInSmYcq = false;
      bool ewAnFiatRr = false;
      bool ysTixrjubT = false;
      bool BStNqHgCjW = false;
      bool CycPIkwDbV = false;
      bool FNJwqztfLw = false;
      string CIofsLobZf;
      string EmmjxGnHNs;
      string VsdidRfllN;
      string LexaOoBegP;
      string kuwlYFNpEt;
      string YcImfJeFBb;
      string fDpMTYoMVI;
      string EJZxIawqKY;
      string EohqohWKtE;
      string JwcFjhEjRz;
      string PAUupPDLeF;
      string MmtcWpVyWk;
      string BeRQyIfTMZ;
      string VMZKIDUlBY;
      string eLeorWBAis;
      string MGMfyjiDwg;
      string iiyEizNjTT;
      string VixyGpzcYb;
      string GfkTMPAsMX;
      string UQoTowNaFr;
      if(CIofsLobZf == PAUupPDLeF){JRfPXcJOZH = true;}
      else if(PAUupPDLeF == CIofsLobZf){flSHhVAaWe = true;}
      if(EmmjxGnHNs == MmtcWpVyWk){kGeUaDxeqT = true;}
      else if(MmtcWpVyWk == EmmjxGnHNs){obbfzJuiDk = true;}
      if(VsdidRfllN == BeRQyIfTMZ){zTWuyEtdIK = true;}
      else if(BeRQyIfTMZ == VsdidRfllN){VwLYpoWGHm = true;}
      if(LexaOoBegP == VMZKIDUlBY){cYWfSozVuj = true;}
      else if(VMZKIDUlBY == LexaOoBegP){hwrgEfHbnp = true;}
      if(kuwlYFNpEt == eLeorWBAis){FlTEmOkUsl = true;}
      else if(eLeorWBAis == kuwlYFNpEt){sOOInSmYcq = true;}
      if(YcImfJeFBb == MGMfyjiDwg){yiikrotjQS = true;}
      else if(MGMfyjiDwg == YcImfJeFBb){ewAnFiatRr = true;}
      if(fDpMTYoMVI == iiyEizNjTT){ifFPeLizBk = true;}
      else if(iiyEizNjTT == fDpMTYoMVI){ysTixrjubT = true;}
      if(EJZxIawqKY == VixyGpzcYb){EbiHNNARIj = true;}
      if(EohqohWKtE == GfkTMPAsMX){SZjWLsolmc = true;}
      if(JwcFjhEjRz == UQoTowNaFr){uOEcAZfDZa = true;}
      while(VixyGpzcYb == EJZxIawqKY){BStNqHgCjW = true;}
      while(GfkTMPAsMX == GfkTMPAsMX){CycPIkwDbV = true;}
      while(UQoTowNaFr == UQoTowNaFr){FNJwqztfLw = true;}
      if(JRfPXcJOZH == true){JRfPXcJOZH = false;}
      if(kGeUaDxeqT == true){kGeUaDxeqT = false;}
      if(zTWuyEtdIK == true){zTWuyEtdIK = false;}
      if(cYWfSozVuj == true){cYWfSozVuj = false;}
      if(FlTEmOkUsl == true){FlTEmOkUsl = false;}
      if(yiikrotjQS == true){yiikrotjQS = false;}
      if(ifFPeLizBk == true){ifFPeLizBk = false;}
      if(EbiHNNARIj == true){EbiHNNARIj = false;}
      if(SZjWLsolmc == true){SZjWLsolmc = false;}
      if(uOEcAZfDZa == true){uOEcAZfDZa = false;}
      if(flSHhVAaWe == true){flSHhVAaWe = false;}
      if(obbfzJuiDk == true){obbfzJuiDk = false;}
      if(VwLYpoWGHm == true){VwLYpoWGHm = false;}
      if(hwrgEfHbnp == true){hwrgEfHbnp = false;}
      if(sOOInSmYcq == true){sOOInSmYcq = false;}
      if(ewAnFiatRr == true){ewAnFiatRr = false;}
      if(ysTixrjubT == true){ysTixrjubT = false;}
      if(BStNqHgCjW == true){BStNqHgCjW = false;}
      if(CycPIkwDbV == true){CycPIkwDbV = false;}
      if(FNJwqztfLw == true){FNJwqztfLw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLJCZGEFOA
{ 
  void OegniVazPf()
  { 
      bool xcJUMqAgss = false;
      bool jmuIGLomKG = false;
      bool bfwwgynDHQ = false;
      bool pGBDhDmTRa = false;
      bool AQeOlrDbbg = false;
      bool oqZupRfMmN = false;
      bool CwZbDdkraD = false;
      bool YVUjGKAhJo = false;
      bool uLaZbyfGMQ = false;
      bool XZfEXDpCKH = false;
      bool GKBYISVpnf = false;
      bool QyCyRqVzAE = false;
      bool yefJeyoQLD = false;
      bool UxWCijKBRI = false;
      bool bpRfAYXhlg = false;
      bool gpCGJaeqtJ = false;
      bool cFdkKSbAOg = false;
      bool gThqcIMzJG = false;
      bool aHdeVeuQrH = false;
      bool FSHIeWLgVg = false;
      string AnoqQoXaVN;
      string pQEZzQNUnN;
      string KgNHrChZwk;
      string zUkjPursfc;
      string OaSHCMZnbY;
      string CoRLeSZgyN;
      string GxejNUeTKE;
      string YUnKziNGEf;
      string csxWiJDZFx;
      string VKuRWQuisg;
      string gFdXAhAGLu;
      string EScRjMzIBE;
      string RFNNiNYWni;
      string neNXzWPZVB;
      string IwNJrChchJ;
      string QmgoObqQom;
      string IdRcHZFFSM;
      string xZlzuUqEVf;
      string fwndRAyYIW;
      string eykireekCR;
      if(AnoqQoXaVN == gFdXAhAGLu){xcJUMqAgss = true;}
      else if(gFdXAhAGLu == AnoqQoXaVN){GKBYISVpnf = true;}
      if(pQEZzQNUnN == EScRjMzIBE){jmuIGLomKG = true;}
      else if(EScRjMzIBE == pQEZzQNUnN){QyCyRqVzAE = true;}
      if(KgNHrChZwk == RFNNiNYWni){bfwwgynDHQ = true;}
      else if(RFNNiNYWni == KgNHrChZwk){yefJeyoQLD = true;}
      if(zUkjPursfc == neNXzWPZVB){pGBDhDmTRa = true;}
      else if(neNXzWPZVB == zUkjPursfc){UxWCijKBRI = true;}
      if(OaSHCMZnbY == IwNJrChchJ){AQeOlrDbbg = true;}
      else if(IwNJrChchJ == OaSHCMZnbY){bpRfAYXhlg = true;}
      if(CoRLeSZgyN == QmgoObqQom){oqZupRfMmN = true;}
      else if(QmgoObqQom == CoRLeSZgyN){gpCGJaeqtJ = true;}
      if(GxejNUeTKE == IdRcHZFFSM){CwZbDdkraD = true;}
      else if(IdRcHZFFSM == GxejNUeTKE){cFdkKSbAOg = true;}
      if(YUnKziNGEf == xZlzuUqEVf){YVUjGKAhJo = true;}
      if(csxWiJDZFx == fwndRAyYIW){uLaZbyfGMQ = true;}
      if(VKuRWQuisg == eykireekCR){XZfEXDpCKH = true;}
      while(xZlzuUqEVf == YUnKziNGEf){gThqcIMzJG = true;}
      while(fwndRAyYIW == fwndRAyYIW){aHdeVeuQrH = true;}
      while(eykireekCR == eykireekCR){FSHIeWLgVg = true;}
      if(xcJUMqAgss == true){xcJUMqAgss = false;}
      if(jmuIGLomKG == true){jmuIGLomKG = false;}
      if(bfwwgynDHQ == true){bfwwgynDHQ = false;}
      if(pGBDhDmTRa == true){pGBDhDmTRa = false;}
      if(AQeOlrDbbg == true){AQeOlrDbbg = false;}
      if(oqZupRfMmN == true){oqZupRfMmN = false;}
      if(CwZbDdkraD == true){CwZbDdkraD = false;}
      if(YVUjGKAhJo == true){YVUjGKAhJo = false;}
      if(uLaZbyfGMQ == true){uLaZbyfGMQ = false;}
      if(XZfEXDpCKH == true){XZfEXDpCKH = false;}
      if(GKBYISVpnf == true){GKBYISVpnf = false;}
      if(QyCyRqVzAE == true){QyCyRqVzAE = false;}
      if(yefJeyoQLD == true){yefJeyoQLD = false;}
      if(UxWCijKBRI == true){UxWCijKBRI = false;}
      if(bpRfAYXhlg == true){bpRfAYXhlg = false;}
      if(gpCGJaeqtJ == true){gpCGJaeqtJ = false;}
      if(cFdkKSbAOg == true){cFdkKSbAOg = false;}
      if(gThqcIMzJG == true){gThqcIMzJG = false;}
      if(aHdeVeuQrH == true){aHdeVeuQrH = false;}
      if(FSHIeWLgVg == true){FSHIeWLgVg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YIBGBILEIU
{ 
  void DrKpkkwzaE()
  { 
      bool tSGhYjqJSw = false;
      bool XGIUeSYJWA = false;
      bool uSpUWTuluc = false;
      bool RdCkrmcxDB = false;
      bool xxibninlEo = false;
      bool duFgIaclKF = false;
      bool nFOpdtEXcr = false;
      bool pbGVCyiNfn = false;
      bool eJgFyWXUbQ = false;
      bool JplyMqhsxt = false;
      bool eQJLzBnjdK = false;
      bool rOFVZeXIqH = false;
      bool ViuLhzpHIK = false;
      bool PpQlJOzUGx = false;
      bool hmqRYukPXh = false;
      bool SYCpXuVxdz = false;
      bool LfaStByTML = false;
      bool eDCsYiqcmm = false;
      bool OZjaqpnZON = false;
      bool sCqGlBMXWW = false;
      string CHkZUCOhuB;
      string ReoZjpZVNX;
      string zfyHpzFXus;
      string bMXRAuPsIw;
      string uqfLkdVRyA;
      string GpTHAWJciV;
      string xqlCYFHXYn;
      string agMQbHzmWM;
      string cmYullsPQd;
      string lmJmzEEdle;
      string VxrJYZdCes;
      string XVFWrKRqPm;
      string MqHuCmWZRX;
      string CUAqpftOVL;
      string HpkXGPgmto;
      string lNNySdpxHl;
      string DEkHpCUOfM;
      string QCVEfWGjol;
      string GjebkoGCXL;
      string owHjIDEcgD;
      if(CHkZUCOhuB == VxrJYZdCes){tSGhYjqJSw = true;}
      else if(VxrJYZdCes == CHkZUCOhuB){eQJLzBnjdK = true;}
      if(ReoZjpZVNX == XVFWrKRqPm){XGIUeSYJWA = true;}
      else if(XVFWrKRqPm == ReoZjpZVNX){rOFVZeXIqH = true;}
      if(zfyHpzFXus == MqHuCmWZRX){uSpUWTuluc = true;}
      else if(MqHuCmWZRX == zfyHpzFXus){ViuLhzpHIK = true;}
      if(bMXRAuPsIw == CUAqpftOVL){RdCkrmcxDB = true;}
      else if(CUAqpftOVL == bMXRAuPsIw){PpQlJOzUGx = true;}
      if(uqfLkdVRyA == HpkXGPgmto){xxibninlEo = true;}
      else if(HpkXGPgmto == uqfLkdVRyA){hmqRYukPXh = true;}
      if(GpTHAWJciV == lNNySdpxHl){duFgIaclKF = true;}
      else if(lNNySdpxHl == GpTHAWJciV){SYCpXuVxdz = true;}
      if(xqlCYFHXYn == DEkHpCUOfM){nFOpdtEXcr = true;}
      else if(DEkHpCUOfM == xqlCYFHXYn){LfaStByTML = true;}
      if(agMQbHzmWM == QCVEfWGjol){pbGVCyiNfn = true;}
      if(cmYullsPQd == GjebkoGCXL){eJgFyWXUbQ = true;}
      if(lmJmzEEdle == owHjIDEcgD){JplyMqhsxt = true;}
      while(QCVEfWGjol == agMQbHzmWM){eDCsYiqcmm = true;}
      while(GjebkoGCXL == GjebkoGCXL){OZjaqpnZON = true;}
      while(owHjIDEcgD == owHjIDEcgD){sCqGlBMXWW = true;}
      if(tSGhYjqJSw == true){tSGhYjqJSw = false;}
      if(XGIUeSYJWA == true){XGIUeSYJWA = false;}
      if(uSpUWTuluc == true){uSpUWTuluc = false;}
      if(RdCkrmcxDB == true){RdCkrmcxDB = false;}
      if(xxibninlEo == true){xxibninlEo = false;}
      if(duFgIaclKF == true){duFgIaclKF = false;}
      if(nFOpdtEXcr == true){nFOpdtEXcr = false;}
      if(pbGVCyiNfn == true){pbGVCyiNfn = false;}
      if(eJgFyWXUbQ == true){eJgFyWXUbQ = false;}
      if(JplyMqhsxt == true){JplyMqhsxt = false;}
      if(eQJLzBnjdK == true){eQJLzBnjdK = false;}
      if(rOFVZeXIqH == true){rOFVZeXIqH = false;}
      if(ViuLhzpHIK == true){ViuLhzpHIK = false;}
      if(PpQlJOzUGx == true){PpQlJOzUGx = false;}
      if(hmqRYukPXh == true){hmqRYukPXh = false;}
      if(SYCpXuVxdz == true){SYCpXuVxdz = false;}
      if(LfaStByTML == true){LfaStByTML = false;}
      if(eDCsYiqcmm == true){eDCsYiqcmm = false;}
      if(OZjaqpnZON == true){OZjaqpnZON = false;}
      if(sCqGlBMXWW == true){sCqGlBMXWW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLMQVCYXXD
{ 
  void YNTKKgmglc()
  { 
      bool qWTHZphfeF = false;
      bool ZzxANVUQnT = false;
      bool KxQOeKdZeU = false;
      bool qpCVbsxhjr = false;
      bool DHcwwcQUrq = false;
      bool ApaWitFEcP = false;
      bool LHBJOjxbYU = false;
      bool YlfuPDTURB = false;
      bool sJgmUAPflg = false;
      bool mrFUguFTgM = false;
      bool fouWSOKeGf = false;
      bool ajmaVBaOoO = false;
      bool UQpqhgfKOT = false;
      bool xAmFVENJUF = false;
      bool pjZFGCFeze = false;
      bool UqeSrPyEol = false;
      bool hzQliZxgFR = false;
      bool nQsiXkpkje = false;
      bool aBLizFVUMF = false;
      bool FJUiWqSmWf = false;
      string koBnFjRGip;
      string ZDWIcBZfPt;
      string swkiYXiDVg;
      string TVditigJcD;
      string rOSOpxUjdD;
      string YUzxioERPh;
      string ANjBVEYnNt;
      string TPCMCedVsa;
      string DyYSIyVgzE;
      string dOsuCdeQsl;
      string XgWjiIRltE;
      string LhYneCoQrW;
      string hrnIPFVHKX;
      string zMcGDVbojA;
      string filuswoFQz;
      string oOYVEfsNTd;
      string mKbWEyESkI;
      string ZzfrpyFsPT;
      string PQpKhknHBW;
      string cOUGNVHPpt;
      if(koBnFjRGip == XgWjiIRltE){qWTHZphfeF = true;}
      else if(XgWjiIRltE == koBnFjRGip){fouWSOKeGf = true;}
      if(ZDWIcBZfPt == LhYneCoQrW){ZzxANVUQnT = true;}
      else if(LhYneCoQrW == ZDWIcBZfPt){ajmaVBaOoO = true;}
      if(swkiYXiDVg == hrnIPFVHKX){KxQOeKdZeU = true;}
      else if(hrnIPFVHKX == swkiYXiDVg){UQpqhgfKOT = true;}
      if(TVditigJcD == zMcGDVbojA){qpCVbsxhjr = true;}
      else if(zMcGDVbojA == TVditigJcD){xAmFVENJUF = true;}
      if(rOSOpxUjdD == filuswoFQz){DHcwwcQUrq = true;}
      else if(filuswoFQz == rOSOpxUjdD){pjZFGCFeze = true;}
      if(YUzxioERPh == oOYVEfsNTd){ApaWitFEcP = true;}
      else if(oOYVEfsNTd == YUzxioERPh){UqeSrPyEol = true;}
      if(ANjBVEYnNt == mKbWEyESkI){LHBJOjxbYU = true;}
      else if(mKbWEyESkI == ANjBVEYnNt){hzQliZxgFR = true;}
      if(TPCMCedVsa == ZzfrpyFsPT){YlfuPDTURB = true;}
      if(DyYSIyVgzE == PQpKhknHBW){sJgmUAPflg = true;}
      if(dOsuCdeQsl == cOUGNVHPpt){mrFUguFTgM = true;}
      while(ZzfrpyFsPT == TPCMCedVsa){nQsiXkpkje = true;}
      while(PQpKhknHBW == PQpKhknHBW){aBLizFVUMF = true;}
      while(cOUGNVHPpt == cOUGNVHPpt){FJUiWqSmWf = true;}
      if(qWTHZphfeF == true){qWTHZphfeF = false;}
      if(ZzxANVUQnT == true){ZzxANVUQnT = false;}
      if(KxQOeKdZeU == true){KxQOeKdZeU = false;}
      if(qpCVbsxhjr == true){qpCVbsxhjr = false;}
      if(DHcwwcQUrq == true){DHcwwcQUrq = false;}
      if(ApaWitFEcP == true){ApaWitFEcP = false;}
      if(LHBJOjxbYU == true){LHBJOjxbYU = false;}
      if(YlfuPDTURB == true){YlfuPDTURB = false;}
      if(sJgmUAPflg == true){sJgmUAPflg = false;}
      if(mrFUguFTgM == true){mrFUguFTgM = false;}
      if(fouWSOKeGf == true){fouWSOKeGf = false;}
      if(ajmaVBaOoO == true){ajmaVBaOoO = false;}
      if(UQpqhgfKOT == true){UQpqhgfKOT = false;}
      if(xAmFVENJUF == true){xAmFVENJUF = false;}
      if(pjZFGCFeze == true){pjZFGCFeze = false;}
      if(UqeSrPyEol == true){UqeSrPyEol = false;}
      if(hzQliZxgFR == true){hzQliZxgFR = false;}
      if(nQsiXkpkje == true){nQsiXkpkje = false;}
      if(aBLizFVUMF == true){aBLizFVUMF = false;}
      if(FJUiWqSmWf == true){FJUiWqSmWf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUEQCQSRNJ
{ 
  void IHcDQNrqBp()
  { 
      bool DoqXlEDnGs = false;
      bool AWUVWQXKEP = false;
      bool efAtIJhPRK = false;
      bool oFfNgpRRJn = false;
      bool wIsbpUTBGB = false;
      bool CpfMBWnxPc = false;
      bool WnWuDtpGof = false;
      bool zFBQSVmYDn = false;
      bool ofIPIzZSMK = false;
      bool CTBfRIlxXu = false;
      bool dNLZCwoOse = false;
      bool iPtampeGmD = false;
      bool TXsedfEUzK = false;
      bool joAIKbUhML = false;
      bool KLZgalZZsa = false;
      bool ceKUbGTgwW = false;
      bool rTPiutPkQL = false;
      bool VxtasIxMDr = false;
      bool FdbXgEefgE = false;
      bool ImlpTpupkg = false;
      string cfPdYMskel;
      string rkzdFLihae;
      string qJFHQwqElu;
      string AAepXfoFXI;
      string iWlAXVqWzN;
      string pkGwiTaIMc;
      string VoyilqGJFY;
      string VdJSwUWEju;
      string FTEXFOthGE;
      string FgrultXCOf;
      string OhQZqLbmAN;
      string wVXQWBjZdX;
      string xXCBTokNgC;
      string xUpDgWDdgs;
      string mGhsHiJbXk;
      string JxXpipfOGC;
      string aNGxPafUjA;
      string yFsjjppItj;
      string eJpwrAwzUp;
      string qnXdSZAjcf;
      if(cfPdYMskel == OhQZqLbmAN){DoqXlEDnGs = true;}
      else if(OhQZqLbmAN == cfPdYMskel){dNLZCwoOse = true;}
      if(rkzdFLihae == wVXQWBjZdX){AWUVWQXKEP = true;}
      else if(wVXQWBjZdX == rkzdFLihae){iPtampeGmD = true;}
      if(qJFHQwqElu == xXCBTokNgC){efAtIJhPRK = true;}
      else if(xXCBTokNgC == qJFHQwqElu){TXsedfEUzK = true;}
      if(AAepXfoFXI == xUpDgWDdgs){oFfNgpRRJn = true;}
      else if(xUpDgWDdgs == AAepXfoFXI){joAIKbUhML = true;}
      if(iWlAXVqWzN == mGhsHiJbXk){wIsbpUTBGB = true;}
      else if(mGhsHiJbXk == iWlAXVqWzN){KLZgalZZsa = true;}
      if(pkGwiTaIMc == JxXpipfOGC){CpfMBWnxPc = true;}
      else if(JxXpipfOGC == pkGwiTaIMc){ceKUbGTgwW = true;}
      if(VoyilqGJFY == aNGxPafUjA){WnWuDtpGof = true;}
      else if(aNGxPafUjA == VoyilqGJFY){rTPiutPkQL = true;}
      if(VdJSwUWEju == yFsjjppItj){zFBQSVmYDn = true;}
      if(FTEXFOthGE == eJpwrAwzUp){ofIPIzZSMK = true;}
      if(FgrultXCOf == qnXdSZAjcf){CTBfRIlxXu = true;}
      while(yFsjjppItj == VdJSwUWEju){VxtasIxMDr = true;}
      while(eJpwrAwzUp == eJpwrAwzUp){FdbXgEefgE = true;}
      while(qnXdSZAjcf == qnXdSZAjcf){ImlpTpupkg = true;}
      if(DoqXlEDnGs == true){DoqXlEDnGs = false;}
      if(AWUVWQXKEP == true){AWUVWQXKEP = false;}
      if(efAtIJhPRK == true){efAtIJhPRK = false;}
      if(oFfNgpRRJn == true){oFfNgpRRJn = false;}
      if(wIsbpUTBGB == true){wIsbpUTBGB = false;}
      if(CpfMBWnxPc == true){CpfMBWnxPc = false;}
      if(WnWuDtpGof == true){WnWuDtpGof = false;}
      if(zFBQSVmYDn == true){zFBQSVmYDn = false;}
      if(ofIPIzZSMK == true){ofIPIzZSMK = false;}
      if(CTBfRIlxXu == true){CTBfRIlxXu = false;}
      if(dNLZCwoOse == true){dNLZCwoOse = false;}
      if(iPtampeGmD == true){iPtampeGmD = false;}
      if(TXsedfEUzK == true){TXsedfEUzK = false;}
      if(joAIKbUhML == true){joAIKbUhML = false;}
      if(KLZgalZZsa == true){KLZgalZZsa = false;}
      if(ceKUbGTgwW == true){ceKUbGTgwW = false;}
      if(rTPiutPkQL == true){rTPiutPkQL = false;}
      if(VxtasIxMDr == true){VxtasIxMDr = false;}
      if(FdbXgEefgE == true){FdbXgEefgE = false;}
      if(ImlpTpupkg == true){ImlpTpupkg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTSMZKGVYD
{ 
  void EIqsfZPngM()
  { 
      bool frdWDYZsen = false;
      bool qhHtXfNYtW = false;
      bool BiefXRWeAE = false;
      bool BiySxaxLSa = false;
      bool yaNsqutJUq = false;
      bool QzHbZwMxzk = false;
      bool BtsZlIjoxw = false;
      bool hBGSXZUlnc = false;
      bool XNKInCaWsA = false;
      bool NzMgZDhmGi = false;
      bool LFMXIOsoDz = false;
      bool aaJVNmjjkj = false;
      bool gMuwiioYsU = false;
      bool rgeFRSBlzZ = false;
      bool JlStYmppTl = false;
      bool SxCWByJPoZ = false;
      bool YTuiGsuDEt = false;
      bool lxjLautAXu = false;
      bool szEHBteIES = false;
      bool IlxZAoqjme = false;
      string rBVxEMwHcU;
      string lBHPYLIZJh;
      string kepKzKoNBV;
      string ekfDSAYSfT;
      string iKZMHdbqfC;
      string QzdrrNKKxt;
      string WhGGoAUDxY;
      string lptozaFcCV;
      string hygzEfHnLF;
      string oNVkwAESWH;
      string JXtGPaFnrR;
      string IhIbLYBGBJ;
      string sgrqjYUIsy;
      string VlGuLJEZid;
      string aSutxHFsYW;
      string zxRNNcfCWq;
      string GwusuVbMPB;
      string TaXXiZkxtc;
      string TaiVzYUrgi;
      string dCDrWdXBya;
      if(rBVxEMwHcU == JXtGPaFnrR){frdWDYZsen = true;}
      else if(JXtGPaFnrR == rBVxEMwHcU){LFMXIOsoDz = true;}
      if(lBHPYLIZJh == IhIbLYBGBJ){qhHtXfNYtW = true;}
      else if(IhIbLYBGBJ == lBHPYLIZJh){aaJVNmjjkj = true;}
      if(kepKzKoNBV == sgrqjYUIsy){BiefXRWeAE = true;}
      else if(sgrqjYUIsy == kepKzKoNBV){gMuwiioYsU = true;}
      if(ekfDSAYSfT == VlGuLJEZid){BiySxaxLSa = true;}
      else if(VlGuLJEZid == ekfDSAYSfT){rgeFRSBlzZ = true;}
      if(iKZMHdbqfC == aSutxHFsYW){yaNsqutJUq = true;}
      else if(aSutxHFsYW == iKZMHdbqfC){JlStYmppTl = true;}
      if(QzdrrNKKxt == zxRNNcfCWq){QzHbZwMxzk = true;}
      else if(zxRNNcfCWq == QzdrrNKKxt){SxCWByJPoZ = true;}
      if(WhGGoAUDxY == GwusuVbMPB){BtsZlIjoxw = true;}
      else if(GwusuVbMPB == WhGGoAUDxY){YTuiGsuDEt = true;}
      if(lptozaFcCV == TaXXiZkxtc){hBGSXZUlnc = true;}
      if(hygzEfHnLF == TaiVzYUrgi){XNKInCaWsA = true;}
      if(oNVkwAESWH == dCDrWdXBya){NzMgZDhmGi = true;}
      while(TaXXiZkxtc == lptozaFcCV){lxjLautAXu = true;}
      while(TaiVzYUrgi == TaiVzYUrgi){szEHBteIES = true;}
      while(dCDrWdXBya == dCDrWdXBya){IlxZAoqjme = true;}
      if(frdWDYZsen == true){frdWDYZsen = false;}
      if(qhHtXfNYtW == true){qhHtXfNYtW = false;}
      if(BiefXRWeAE == true){BiefXRWeAE = false;}
      if(BiySxaxLSa == true){BiySxaxLSa = false;}
      if(yaNsqutJUq == true){yaNsqutJUq = false;}
      if(QzHbZwMxzk == true){QzHbZwMxzk = false;}
      if(BtsZlIjoxw == true){BtsZlIjoxw = false;}
      if(hBGSXZUlnc == true){hBGSXZUlnc = false;}
      if(XNKInCaWsA == true){XNKInCaWsA = false;}
      if(NzMgZDhmGi == true){NzMgZDhmGi = false;}
      if(LFMXIOsoDz == true){LFMXIOsoDz = false;}
      if(aaJVNmjjkj == true){aaJVNmjjkj = false;}
      if(gMuwiioYsU == true){gMuwiioYsU = false;}
      if(rgeFRSBlzZ == true){rgeFRSBlzZ = false;}
      if(JlStYmppTl == true){JlStYmppTl = false;}
      if(SxCWByJPoZ == true){SxCWByJPoZ = false;}
      if(YTuiGsuDEt == true){YTuiGsuDEt = false;}
      if(lxjLautAXu == true){lxjLautAXu = false;}
      if(szEHBteIES == true){szEHBteIES = false;}
      if(IlxZAoqjme == true){IlxZAoqjme = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDXICXRUMV
{ 
  void abkPEmWIwC()
  { 
      bool gLyAsJUDkO = false;
      bool XGAoYrmybS = false;
      bool RicXHdZQqV = false;
      bool gMoABaYTQC = false;
      bool PahxqwKnnM = false;
      bool uNgxTyiarO = false;
      bool jEMOhLRAny = false;
      bool TShZCqAefL = false;
      bool SkbdaSeqgD = false;
      bool qxaBRLOSPf = false;
      bool dKApsbfGtb = false;
      bool xEugwybhnO = false;
      bool fZSjGVqgIq = false;
      bool chPAgIkljy = false;
      bool mYxEFmCtES = false;
      bool jfdAzEqPiX = false;
      bool jyyDzOntzm = false;
      bool NoxpbHcOdT = false;
      bool SxboHwDOAc = false;
      bool QVDMOoZsEq = false;
      string yyomyYfFZL;
      string HsRMBMzeQy;
      string UZypRVlmaO;
      string lbNjiqLFNG;
      string JgdIAsUiyB;
      string TGICbYzzUb;
      string msdLZffhdJ;
      string AtRJomwpoX;
      string BCoZteSLIJ;
      string rLjkSPDRiU;
      string NlFnAZnzNn;
      string bJKxZkDDQt;
      string MTZTQnJfqY;
      string jeHUJPwAZU;
      string pTyThiBlLh;
      string MzAnHtMlXL;
      string PIHnDwBomK;
      string nCdwDsVFkh;
      string mXUJLkeSMP;
      string CKcNFhLJQk;
      if(yyomyYfFZL == NlFnAZnzNn){gLyAsJUDkO = true;}
      else if(NlFnAZnzNn == yyomyYfFZL){dKApsbfGtb = true;}
      if(HsRMBMzeQy == bJKxZkDDQt){XGAoYrmybS = true;}
      else if(bJKxZkDDQt == HsRMBMzeQy){xEugwybhnO = true;}
      if(UZypRVlmaO == MTZTQnJfqY){RicXHdZQqV = true;}
      else if(MTZTQnJfqY == UZypRVlmaO){fZSjGVqgIq = true;}
      if(lbNjiqLFNG == jeHUJPwAZU){gMoABaYTQC = true;}
      else if(jeHUJPwAZU == lbNjiqLFNG){chPAgIkljy = true;}
      if(JgdIAsUiyB == pTyThiBlLh){PahxqwKnnM = true;}
      else if(pTyThiBlLh == JgdIAsUiyB){mYxEFmCtES = true;}
      if(TGICbYzzUb == MzAnHtMlXL){uNgxTyiarO = true;}
      else if(MzAnHtMlXL == TGICbYzzUb){jfdAzEqPiX = true;}
      if(msdLZffhdJ == PIHnDwBomK){jEMOhLRAny = true;}
      else if(PIHnDwBomK == msdLZffhdJ){jyyDzOntzm = true;}
      if(AtRJomwpoX == nCdwDsVFkh){TShZCqAefL = true;}
      if(BCoZteSLIJ == mXUJLkeSMP){SkbdaSeqgD = true;}
      if(rLjkSPDRiU == CKcNFhLJQk){qxaBRLOSPf = true;}
      while(nCdwDsVFkh == AtRJomwpoX){NoxpbHcOdT = true;}
      while(mXUJLkeSMP == mXUJLkeSMP){SxboHwDOAc = true;}
      while(CKcNFhLJQk == CKcNFhLJQk){QVDMOoZsEq = true;}
      if(gLyAsJUDkO == true){gLyAsJUDkO = false;}
      if(XGAoYrmybS == true){XGAoYrmybS = false;}
      if(RicXHdZQqV == true){RicXHdZQqV = false;}
      if(gMoABaYTQC == true){gMoABaYTQC = false;}
      if(PahxqwKnnM == true){PahxqwKnnM = false;}
      if(uNgxTyiarO == true){uNgxTyiarO = false;}
      if(jEMOhLRAny == true){jEMOhLRAny = false;}
      if(TShZCqAefL == true){TShZCqAefL = false;}
      if(SkbdaSeqgD == true){SkbdaSeqgD = false;}
      if(qxaBRLOSPf == true){qxaBRLOSPf = false;}
      if(dKApsbfGtb == true){dKApsbfGtb = false;}
      if(xEugwybhnO == true){xEugwybhnO = false;}
      if(fZSjGVqgIq == true){fZSjGVqgIq = false;}
      if(chPAgIkljy == true){chPAgIkljy = false;}
      if(mYxEFmCtES == true){mYxEFmCtES = false;}
      if(jfdAzEqPiX == true){jfdAzEqPiX = false;}
      if(jyyDzOntzm == true){jyyDzOntzm = false;}
      if(NoxpbHcOdT == true){NoxpbHcOdT = false;}
      if(SxboHwDOAc == true){SxboHwDOAc = false;}
      if(QVDMOoZsEq == true){QVDMOoZsEq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TZQSWCCKBA
{ 
  void rQqqldJPMB()
  { 
      bool MumcLIywdd = false;
      bool SZdcnEEENs = false;
      bool DfDhVyCijC = false;
      bool XctyqXTCdL = false;
      bool GgPGLLtlsh = false;
      bool rtsYOfqEHN = false;
      bool FPMbGpfelQ = false;
      bool kBZCmVQwWK = false;
      bool DQoCJciUjK = false;
      bool fOuQFqUmAV = false;
      bool ePzbwpUqlr = false;
      bool PuhwJoZKSc = false;
      bool GKuakVGIwu = false;
      bool BcwAenRMFS = false;
      bool IriqukgzGQ = false;
      bool RKUWOUUXqa = false;
      bool jLupqlygRV = false;
      bool XMEzUObDfz = false;
      bool oGCedpIZkK = false;
      bool TsVehxxrzI = false;
      string WzgBlQIdcm;
      string QbFoACRRCG;
      string RIPBoRqYXq;
      string UkgrsVoKjB;
      string XbXexZdJDX;
      string ZjVMIOieMT;
      string ZiGkSfuNwd;
      string MGgBiojjEO;
      string nhVAQkOTje;
      string lKyQanUmMR;
      string ePMYKTCUdS;
      string dyaxerNGTh;
      string QadRrCHQZu;
      string TwXliXUwox;
      string htpQAmjBki;
      string ZOSdBDlugH;
      string LktiyhanNH;
      string XRQVzWkMRE;
      string SGfpUEdtke;
      string kYOhlxzHSS;
      if(WzgBlQIdcm == ePMYKTCUdS){MumcLIywdd = true;}
      else if(ePMYKTCUdS == WzgBlQIdcm){ePzbwpUqlr = true;}
      if(QbFoACRRCG == dyaxerNGTh){SZdcnEEENs = true;}
      else if(dyaxerNGTh == QbFoACRRCG){PuhwJoZKSc = true;}
      if(RIPBoRqYXq == QadRrCHQZu){DfDhVyCijC = true;}
      else if(QadRrCHQZu == RIPBoRqYXq){GKuakVGIwu = true;}
      if(UkgrsVoKjB == TwXliXUwox){XctyqXTCdL = true;}
      else if(TwXliXUwox == UkgrsVoKjB){BcwAenRMFS = true;}
      if(XbXexZdJDX == htpQAmjBki){GgPGLLtlsh = true;}
      else if(htpQAmjBki == XbXexZdJDX){IriqukgzGQ = true;}
      if(ZjVMIOieMT == ZOSdBDlugH){rtsYOfqEHN = true;}
      else if(ZOSdBDlugH == ZjVMIOieMT){RKUWOUUXqa = true;}
      if(ZiGkSfuNwd == LktiyhanNH){FPMbGpfelQ = true;}
      else if(LktiyhanNH == ZiGkSfuNwd){jLupqlygRV = true;}
      if(MGgBiojjEO == XRQVzWkMRE){kBZCmVQwWK = true;}
      if(nhVAQkOTje == SGfpUEdtke){DQoCJciUjK = true;}
      if(lKyQanUmMR == kYOhlxzHSS){fOuQFqUmAV = true;}
      while(XRQVzWkMRE == MGgBiojjEO){XMEzUObDfz = true;}
      while(SGfpUEdtke == SGfpUEdtke){oGCedpIZkK = true;}
      while(kYOhlxzHSS == kYOhlxzHSS){TsVehxxrzI = true;}
      if(MumcLIywdd == true){MumcLIywdd = false;}
      if(SZdcnEEENs == true){SZdcnEEENs = false;}
      if(DfDhVyCijC == true){DfDhVyCijC = false;}
      if(XctyqXTCdL == true){XctyqXTCdL = false;}
      if(GgPGLLtlsh == true){GgPGLLtlsh = false;}
      if(rtsYOfqEHN == true){rtsYOfqEHN = false;}
      if(FPMbGpfelQ == true){FPMbGpfelQ = false;}
      if(kBZCmVQwWK == true){kBZCmVQwWK = false;}
      if(DQoCJciUjK == true){DQoCJciUjK = false;}
      if(fOuQFqUmAV == true){fOuQFqUmAV = false;}
      if(ePzbwpUqlr == true){ePzbwpUqlr = false;}
      if(PuhwJoZKSc == true){PuhwJoZKSc = false;}
      if(GKuakVGIwu == true){GKuakVGIwu = false;}
      if(BcwAenRMFS == true){BcwAenRMFS = false;}
      if(IriqukgzGQ == true){IriqukgzGQ = false;}
      if(RKUWOUUXqa == true){RKUWOUUXqa = false;}
      if(jLupqlygRV == true){jLupqlygRV = false;}
      if(XMEzUObDfz == true){XMEzUObDfz = false;}
      if(oGCedpIZkK == true){oGCedpIZkK = false;}
      if(TsVehxxrzI == true){TsVehxxrzI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQYTCNRSJJ
{ 
  void KUGyoPAOEi()
  { 
      bool JIPWgisFxy = false;
      bool ZcJRaBOqBJ = false;
      bool QOgBkIZrkt = false;
      bool jQOSwTODBt = false;
      bool pzzeNronLZ = false;
      bool mqFNEtaOkY = false;
      bool JBTCNJNqUG = false;
      bool lLoHTRPCms = false;
      bool SkfKHsKAOC = false;
      bool sARcjoewQD = false;
      bool eyTEnbBxtm = false;
      bool dXarFYUJuU = false;
      bool zNbSNlsMWe = false;
      bool lTliOUQbWe = false;
      bool qMGbXUYZXL = false;
      bool TVAuEQVBqC = false;
      bool ioZPAKkqdj = false;
      bool HsmPclGAtr = false;
      bool MSnKKQSpex = false;
      bool zPjTwClqaM = false;
      string tAwooHJTFX;
      string yKuEsfVqqa;
      string IqaHSsZXIK;
      string BSsXmwMDRa;
      string KFhDWYpwuS;
      string jRNlECYoVu;
      string hlLuVfRWRx;
      string SSZPPCJXkt;
      string DcbpZiFHSj;
      string WXgVsYtmgq;
      string HSeyzRrxVC;
      string rBEbrEJVUm;
      string ZJDgaukDWq;
      string IWpslkxdpI;
      string pHlQrUSFdn;
      string OYRtQyOyXD;
      string gnZdsVLKoH;
      string HfeMwRXlnF;
      string ceZicjEwcn;
      string VyGmbBhHXV;
      if(tAwooHJTFX == HSeyzRrxVC){JIPWgisFxy = true;}
      else if(HSeyzRrxVC == tAwooHJTFX){eyTEnbBxtm = true;}
      if(yKuEsfVqqa == rBEbrEJVUm){ZcJRaBOqBJ = true;}
      else if(rBEbrEJVUm == yKuEsfVqqa){dXarFYUJuU = true;}
      if(IqaHSsZXIK == ZJDgaukDWq){QOgBkIZrkt = true;}
      else if(ZJDgaukDWq == IqaHSsZXIK){zNbSNlsMWe = true;}
      if(BSsXmwMDRa == IWpslkxdpI){jQOSwTODBt = true;}
      else if(IWpslkxdpI == BSsXmwMDRa){lTliOUQbWe = true;}
      if(KFhDWYpwuS == pHlQrUSFdn){pzzeNronLZ = true;}
      else if(pHlQrUSFdn == KFhDWYpwuS){qMGbXUYZXL = true;}
      if(jRNlECYoVu == OYRtQyOyXD){mqFNEtaOkY = true;}
      else if(OYRtQyOyXD == jRNlECYoVu){TVAuEQVBqC = true;}
      if(hlLuVfRWRx == gnZdsVLKoH){JBTCNJNqUG = true;}
      else if(gnZdsVLKoH == hlLuVfRWRx){ioZPAKkqdj = true;}
      if(SSZPPCJXkt == HfeMwRXlnF){lLoHTRPCms = true;}
      if(DcbpZiFHSj == ceZicjEwcn){SkfKHsKAOC = true;}
      if(WXgVsYtmgq == VyGmbBhHXV){sARcjoewQD = true;}
      while(HfeMwRXlnF == SSZPPCJXkt){HsmPclGAtr = true;}
      while(ceZicjEwcn == ceZicjEwcn){MSnKKQSpex = true;}
      while(VyGmbBhHXV == VyGmbBhHXV){zPjTwClqaM = true;}
      if(JIPWgisFxy == true){JIPWgisFxy = false;}
      if(ZcJRaBOqBJ == true){ZcJRaBOqBJ = false;}
      if(QOgBkIZrkt == true){QOgBkIZrkt = false;}
      if(jQOSwTODBt == true){jQOSwTODBt = false;}
      if(pzzeNronLZ == true){pzzeNronLZ = false;}
      if(mqFNEtaOkY == true){mqFNEtaOkY = false;}
      if(JBTCNJNqUG == true){JBTCNJNqUG = false;}
      if(lLoHTRPCms == true){lLoHTRPCms = false;}
      if(SkfKHsKAOC == true){SkfKHsKAOC = false;}
      if(sARcjoewQD == true){sARcjoewQD = false;}
      if(eyTEnbBxtm == true){eyTEnbBxtm = false;}
      if(dXarFYUJuU == true){dXarFYUJuU = false;}
      if(zNbSNlsMWe == true){zNbSNlsMWe = false;}
      if(lTliOUQbWe == true){lTliOUQbWe = false;}
      if(qMGbXUYZXL == true){qMGbXUYZXL = false;}
      if(TVAuEQVBqC == true){TVAuEQVBqC = false;}
      if(ioZPAKkqdj == true){ioZPAKkqdj = false;}
      if(HsmPclGAtr == true){HsmPclGAtr = false;}
      if(MSnKKQSpex == true){MSnKKQSpex = false;}
      if(zPjTwClqaM == true){zPjTwClqaM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPUGWOJPXE
{ 
  void pEnjFXODsS()
  { 
      bool fCleGmczjJ = false;
      bool FWIndqHxHh = false;
      bool wXzaNBHBoZ = false;
      bool AsRfMwYFKC = false;
      bool LlDuYcEqxf = false;
      bool sRRYSHCLQE = false;
      bool eaKJILEbah = false;
      bool SCmFVKUEBk = false;
      bool xPDIgibsNE = false;
      bool tMnFWkbsmN = false;
      bool XbPPNqdMCI = false;
      bool myKfHPXBcY = false;
      bool jLOWmFNghk = false;
      bool haRnMUAntp = false;
      bool FPpERwCIyH = false;
      bool NaQNcLNsbI = false;
      bool cxdRaMfWSl = false;
      bool OiGlTUVJEq = false;
      bool CFhZXHJDKA = false;
      bool GGLlMIkYdF = false;
      string zcXdnhRoRr;
      string rIsgiRfjgt;
      string wUnqDlmmRu;
      string MSjwIsWbEt;
      string ELWJsltXHd;
      string MAmBBdogZB;
      string teWWfZXxYo;
      string uEflojxdyR;
      string rPeniMeiud;
      string EoBCAZoAdT;
      string NxySiHUBMR;
      string fLiIJezinS;
      string toBtkFDclP;
      string txzdDuQMFa;
      string rdVcyrGrsU;
      string ZGLLZYuEgc;
      string DqOxWhMEFN;
      string OmcMaPSXws;
      string yLjQonknEe;
      string AMfbXAOYGP;
      if(zcXdnhRoRr == NxySiHUBMR){fCleGmczjJ = true;}
      else if(NxySiHUBMR == zcXdnhRoRr){XbPPNqdMCI = true;}
      if(rIsgiRfjgt == fLiIJezinS){FWIndqHxHh = true;}
      else if(fLiIJezinS == rIsgiRfjgt){myKfHPXBcY = true;}
      if(wUnqDlmmRu == toBtkFDclP){wXzaNBHBoZ = true;}
      else if(toBtkFDclP == wUnqDlmmRu){jLOWmFNghk = true;}
      if(MSjwIsWbEt == txzdDuQMFa){AsRfMwYFKC = true;}
      else if(txzdDuQMFa == MSjwIsWbEt){haRnMUAntp = true;}
      if(ELWJsltXHd == rdVcyrGrsU){LlDuYcEqxf = true;}
      else if(rdVcyrGrsU == ELWJsltXHd){FPpERwCIyH = true;}
      if(MAmBBdogZB == ZGLLZYuEgc){sRRYSHCLQE = true;}
      else if(ZGLLZYuEgc == MAmBBdogZB){NaQNcLNsbI = true;}
      if(teWWfZXxYo == DqOxWhMEFN){eaKJILEbah = true;}
      else if(DqOxWhMEFN == teWWfZXxYo){cxdRaMfWSl = true;}
      if(uEflojxdyR == OmcMaPSXws){SCmFVKUEBk = true;}
      if(rPeniMeiud == yLjQonknEe){xPDIgibsNE = true;}
      if(EoBCAZoAdT == AMfbXAOYGP){tMnFWkbsmN = true;}
      while(OmcMaPSXws == uEflojxdyR){OiGlTUVJEq = true;}
      while(yLjQonknEe == yLjQonknEe){CFhZXHJDKA = true;}
      while(AMfbXAOYGP == AMfbXAOYGP){GGLlMIkYdF = true;}
      if(fCleGmczjJ == true){fCleGmczjJ = false;}
      if(FWIndqHxHh == true){FWIndqHxHh = false;}
      if(wXzaNBHBoZ == true){wXzaNBHBoZ = false;}
      if(AsRfMwYFKC == true){AsRfMwYFKC = false;}
      if(LlDuYcEqxf == true){LlDuYcEqxf = false;}
      if(sRRYSHCLQE == true){sRRYSHCLQE = false;}
      if(eaKJILEbah == true){eaKJILEbah = false;}
      if(SCmFVKUEBk == true){SCmFVKUEBk = false;}
      if(xPDIgibsNE == true){xPDIgibsNE = false;}
      if(tMnFWkbsmN == true){tMnFWkbsmN = false;}
      if(XbPPNqdMCI == true){XbPPNqdMCI = false;}
      if(myKfHPXBcY == true){myKfHPXBcY = false;}
      if(jLOWmFNghk == true){jLOWmFNghk = false;}
      if(haRnMUAntp == true){haRnMUAntp = false;}
      if(FPpERwCIyH == true){FPpERwCIyH = false;}
      if(NaQNcLNsbI == true){NaQNcLNsbI = false;}
      if(cxdRaMfWSl == true){cxdRaMfWSl = false;}
      if(OiGlTUVJEq == true){OiGlTUVJEq = false;}
      if(CFhZXHJDKA == true){CFhZXHJDKA = false;}
      if(GGLlMIkYdF == true){GGLlMIkYdF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVKFYNYMKY
{ 
  void ZoYyzQwVYA()
  { 
      bool suWNdVAtUJ = false;
      bool QIzNsRKdRh = false;
      bool bbjewFCHLk = false;
      bool CEGwdSQNho = false;
      bool VfEMlJrgoe = false;
      bool uUlCuRLrQY = false;
      bool TshiGMBDiZ = false;
      bool BxwbMuWXrm = false;
      bool MURgohSDBM = false;
      bool HYwJVcxUGZ = false;
      bool HoyPdyXJpz = false;
      bool tmzdLybBtX = false;
      bool sxBVRbAmFi = false;
      bool xBRRfXWCCp = false;
      bool JJNCSTYSxX = false;
      bool BwahgJnbxB = false;
      bool ykDGBrVhxm = false;
      bool aYyDNjjyDy = false;
      bool CgohhBZikV = false;
      bool jtEArYFGAZ = false;
      string KbTqJRGshH;
      string dFGmJRiCpo;
      string IfDxlbkruQ;
      string lTaNlHLWpR;
      string LWiSMsaMGe;
      string MCBkEeXWEg;
      string gOyQUJerAC;
      string FMMXclwjjr;
      string BXkQDjSoJH;
      string ioRIkxXRxC;
      string OiMEYApcIS;
      string hnmMfJdgMk;
      string qohsSQtDme;
      string NelgcRLfqD;
      string sogpYuBFbb;
      string TpEMLZATkI;
      string GlpcFCBFiO;
      string xxpJrCIrTX;
      string OnbLLWaZVD;
      string RrtixGzDkW;
      if(KbTqJRGshH == OiMEYApcIS){suWNdVAtUJ = true;}
      else if(OiMEYApcIS == KbTqJRGshH){HoyPdyXJpz = true;}
      if(dFGmJRiCpo == hnmMfJdgMk){QIzNsRKdRh = true;}
      else if(hnmMfJdgMk == dFGmJRiCpo){tmzdLybBtX = true;}
      if(IfDxlbkruQ == qohsSQtDme){bbjewFCHLk = true;}
      else if(qohsSQtDme == IfDxlbkruQ){sxBVRbAmFi = true;}
      if(lTaNlHLWpR == NelgcRLfqD){CEGwdSQNho = true;}
      else if(NelgcRLfqD == lTaNlHLWpR){xBRRfXWCCp = true;}
      if(LWiSMsaMGe == sogpYuBFbb){VfEMlJrgoe = true;}
      else if(sogpYuBFbb == LWiSMsaMGe){JJNCSTYSxX = true;}
      if(MCBkEeXWEg == TpEMLZATkI){uUlCuRLrQY = true;}
      else if(TpEMLZATkI == MCBkEeXWEg){BwahgJnbxB = true;}
      if(gOyQUJerAC == GlpcFCBFiO){TshiGMBDiZ = true;}
      else if(GlpcFCBFiO == gOyQUJerAC){ykDGBrVhxm = true;}
      if(FMMXclwjjr == xxpJrCIrTX){BxwbMuWXrm = true;}
      if(BXkQDjSoJH == OnbLLWaZVD){MURgohSDBM = true;}
      if(ioRIkxXRxC == RrtixGzDkW){HYwJVcxUGZ = true;}
      while(xxpJrCIrTX == FMMXclwjjr){aYyDNjjyDy = true;}
      while(OnbLLWaZVD == OnbLLWaZVD){CgohhBZikV = true;}
      while(RrtixGzDkW == RrtixGzDkW){jtEArYFGAZ = true;}
      if(suWNdVAtUJ == true){suWNdVAtUJ = false;}
      if(QIzNsRKdRh == true){QIzNsRKdRh = false;}
      if(bbjewFCHLk == true){bbjewFCHLk = false;}
      if(CEGwdSQNho == true){CEGwdSQNho = false;}
      if(VfEMlJrgoe == true){VfEMlJrgoe = false;}
      if(uUlCuRLrQY == true){uUlCuRLrQY = false;}
      if(TshiGMBDiZ == true){TshiGMBDiZ = false;}
      if(BxwbMuWXrm == true){BxwbMuWXrm = false;}
      if(MURgohSDBM == true){MURgohSDBM = false;}
      if(HYwJVcxUGZ == true){HYwJVcxUGZ = false;}
      if(HoyPdyXJpz == true){HoyPdyXJpz = false;}
      if(tmzdLybBtX == true){tmzdLybBtX = false;}
      if(sxBVRbAmFi == true){sxBVRbAmFi = false;}
      if(xBRRfXWCCp == true){xBRRfXWCCp = false;}
      if(JJNCSTYSxX == true){JJNCSTYSxX = false;}
      if(BwahgJnbxB == true){BwahgJnbxB = false;}
      if(ykDGBrVhxm == true){ykDGBrVhxm = false;}
      if(aYyDNjjyDy == true){aYyDNjjyDy = false;}
      if(CgohhBZikV == true){CgohhBZikV = false;}
      if(jtEArYFGAZ == true){jtEArYFGAZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NMDSSHVEDN
{ 
  void MXQzRhOsWx()
  { 
      bool ObAzDRayQB = false;
      bool EoQsKgdIjM = false;
      bool PneucJneGL = false;
      bool bcAnZsYNZF = false;
      bool CxhxadPqaO = false;
      bool cUhckZxEWs = false;
      bool dwqEZbocSR = false;
      bool HQheJSGgUz = false;
      bool swDqiGtXCz = false;
      bool wUqfbFFcXy = false;
      bool omXJHMmDSR = false;
      bool TPiWAgrzVS = false;
      bool gQZTUmYBCE = false;
      bool McJVJFXtjW = false;
      bool TqFkfgkTfu = false;
      bool MFHEQXNEnT = false;
      bool mkAOEpGMNt = false;
      bool JyPzypLonn = false;
      bool CEVHqHVEFk = false;
      bool rTGQiippfo = false;
      string iGeDFAKzNT;
      string cnJEqaXmrL;
      string XXBJtLacty;
      string CfSxgcKpkx;
      string PdURZrMflW;
      string oCFTGLEUIt;
      string YgEOQwVMXO;
      string QhBuwtCijC;
      string yupXJzZyqU;
      string XpgqXhYGAc;
      string WAIXGGBJWL;
      string IVjGudqgFR;
      string VWUCpaAJXO;
      string VwhGeymRQC;
      string yPaeMCFawt;
      string qqBiHAeFgf;
      string GqlIpLmdaw;
      string pYPCSFuoon;
      string UYNdXduyze;
      string TgkkwGdSoB;
      if(iGeDFAKzNT == WAIXGGBJWL){ObAzDRayQB = true;}
      else if(WAIXGGBJWL == iGeDFAKzNT){omXJHMmDSR = true;}
      if(cnJEqaXmrL == IVjGudqgFR){EoQsKgdIjM = true;}
      else if(IVjGudqgFR == cnJEqaXmrL){TPiWAgrzVS = true;}
      if(XXBJtLacty == VWUCpaAJXO){PneucJneGL = true;}
      else if(VWUCpaAJXO == XXBJtLacty){gQZTUmYBCE = true;}
      if(CfSxgcKpkx == VwhGeymRQC){bcAnZsYNZF = true;}
      else if(VwhGeymRQC == CfSxgcKpkx){McJVJFXtjW = true;}
      if(PdURZrMflW == yPaeMCFawt){CxhxadPqaO = true;}
      else if(yPaeMCFawt == PdURZrMflW){TqFkfgkTfu = true;}
      if(oCFTGLEUIt == qqBiHAeFgf){cUhckZxEWs = true;}
      else if(qqBiHAeFgf == oCFTGLEUIt){MFHEQXNEnT = true;}
      if(YgEOQwVMXO == GqlIpLmdaw){dwqEZbocSR = true;}
      else if(GqlIpLmdaw == YgEOQwVMXO){mkAOEpGMNt = true;}
      if(QhBuwtCijC == pYPCSFuoon){HQheJSGgUz = true;}
      if(yupXJzZyqU == UYNdXduyze){swDqiGtXCz = true;}
      if(XpgqXhYGAc == TgkkwGdSoB){wUqfbFFcXy = true;}
      while(pYPCSFuoon == QhBuwtCijC){JyPzypLonn = true;}
      while(UYNdXduyze == UYNdXduyze){CEVHqHVEFk = true;}
      while(TgkkwGdSoB == TgkkwGdSoB){rTGQiippfo = true;}
      if(ObAzDRayQB == true){ObAzDRayQB = false;}
      if(EoQsKgdIjM == true){EoQsKgdIjM = false;}
      if(PneucJneGL == true){PneucJneGL = false;}
      if(bcAnZsYNZF == true){bcAnZsYNZF = false;}
      if(CxhxadPqaO == true){CxhxadPqaO = false;}
      if(cUhckZxEWs == true){cUhckZxEWs = false;}
      if(dwqEZbocSR == true){dwqEZbocSR = false;}
      if(HQheJSGgUz == true){HQheJSGgUz = false;}
      if(swDqiGtXCz == true){swDqiGtXCz = false;}
      if(wUqfbFFcXy == true){wUqfbFFcXy = false;}
      if(omXJHMmDSR == true){omXJHMmDSR = false;}
      if(TPiWAgrzVS == true){TPiWAgrzVS = false;}
      if(gQZTUmYBCE == true){gQZTUmYBCE = false;}
      if(McJVJFXtjW == true){McJVJFXtjW = false;}
      if(TqFkfgkTfu == true){TqFkfgkTfu = false;}
      if(MFHEQXNEnT == true){MFHEQXNEnT = false;}
      if(mkAOEpGMNt == true){mkAOEpGMNt = false;}
      if(JyPzypLonn == true){JyPzypLonn = false;}
      if(CEVHqHVEFk == true){CEVHqHVEFk = false;}
      if(rTGQiippfo == true){rTGQiippfo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FAGFUZWHMW
{ 
  void rNTEwJnEcq()
  { 
      bool TSjecKXNyi = false;
      bool bxktqIxgJN = false;
      bool MWXdwJDjlJ = false;
      bool CsIyoqhIzf = false;
      bool yrumJglVXa = false;
      bool UosOSwtGhT = false;
      bool GmanfiomEA = false;
      bool ZogdOTbkUP = false;
      bool WgMKoNAses = false;
      bool wbZfYLQGGZ = false;
      bool qyRXBfHOAy = false;
      bool TIkSxZaQzS = false;
      bool iwILDyOBED = false;
      bool DVetYXPoJI = false;
      bool FksfYmqHiz = false;
      bool jzGmqupFTC = false;
      bool RGJwtycpsY = false;
      bool JlHqNxCblP = false;
      bool GHSFSDOrDc = false;
      bool hJUGqyawka = false;
      string OVhcyseQXc;
      string TEnrDxQWsH;
      string SEFZZOwbPm;
      string JpgzNmqZfa;
      string UmAbntUTMc;
      string iYNIJJQICi;
      string wCBkSdXndP;
      string FpqRleDdle;
      string tcPlEkbYpD;
      string WiXwdRlPIJ;
      string WgowWsgwVd;
      string GlVXoTmOfg;
      string CzxasWRumU;
      string snUbINmTPK;
      string EeDMxjMzGK;
      string dWiaGXiOCA;
      string alJAjRQtOb;
      string gTzVcXukcI;
      string JSncpWFsVk;
      string eXQOjSVCbe;
      if(OVhcyseQXc == WgowWsgwVd){TSjecKXNyi = true;}
      else if(WgowWsgwVd == OVhcyseQXc){qyRXBfHOAy = true;}
      if(TEnrDxQWsH == GlVXoTmOfg){bxktqIxgJN = true;}
      else if(GlVXoTmOfg == TEnrDxQWsH){TIkSxZaQzS = true;}
      if(SEFZZOwbPm == CzxasWRumU){MWXdwJDjlJ = true;}
      else if(CzxasWRumU == SEFZZOwbPm){iwILDyOBED = true;}
      if(JpgzNmqZfa == snUbINmTPK){CsIyoqhIzf = true;}
      else if(snUbINmTPK == JpgzNmqZfa){DVetYXPoJI = true;}
      if(UmAbntUTMc == EeDMxjMzGK){yrumJglVXa = true;}
      else if(EeDMxjMzGK == UmAbntUTMc){FksfYmqHiz = true;}
      if(iYNIJJQICi == dWiaGXiOCA){UosOSwtGhT = true;}
      else if(dWiaGXiOCA == iYNIJJQICi){jzGmqupFTC = true;}
      if(wCBkSdXndP == alJAjRQtOb){GmanfiomEA = true;}
      else if(alJAjRQtOb == wCBkSdXndP){RGJwtycpsY = true;}
      if(FpqRleDdle == gTzVcXukcI){ZogdOTbkUP = true;}
      if(tcPlEkbYpD == JSncpWFsVk){WgMKoNAses = true;}
      if(WiXwdRlPIJ == eXQOjSVCbe){wbZfYLQGGZ = true;}
      while(gTzVcXukcI == FpqRleDdle){JlHqNxCblP = true;}
      while(JSncpWFsVk == JSncpWFsVk){GHSFSDOrDc = true;}
      while(eXQOjSVCbe == eXQOjSVCbe){hJUGqyawka = true;}
      if(TSjecKXNyi == true){TSjecKXNyi = false;}
      if(bxktqIxgJN == true){bxktqIxgJN = false;}
      if(MWXdwJDjlJ == true){MWXdwJDjlJ = false;}
      if(CsIyoqhIzf == true){CsIyoqhIzf = false;}
      if(yrumJglVXa == true){yrumJglVXa = false;}
      if(UosOSwtGhT == true){UosOSwtGhT = false;}
      if(GmanfiomEA == true){GmanfiomEA = false;}
      if(ZogdOTbkUP == true){ZogdOTbkUP = false;}
      if(WgMKoNAses == true){WgMKoNAses = false;}
      if(wbZfYLQGGZ == true){wbZfYLQGGZ = false;}
      if(qyRXBfHOAy == true){qyRXBfHOAy = false;}
      if(TIkSxZaQzS == true){TIkSxZaQzS = false;}
      if(iwILDyOBED == true){iwILDyOBED = false;}
      if(DVetYXPoJI == true){DVetYXPoJI = false;}
      if(FksfYmqHiz == true){FksfYmqHiz = false;}
      if(jzGmqupFTC == true){jzGmqupFTC = false;}
      if(RGJwtycpsY == true){RGJwtycpsY = false;}
      if(JlHqNxCblP == true){JlHqNxCblP = false;}
      if(GHSFSDOrDc == true){GHSFSDOrDc = false;}
      if(hJUGqyawka == true){hJUGqyawka = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPXJNAZXMT
{ 
  void GfGrgyfyGP()
  { 
      bool GbYYbeyXNc = false;
      bool KGdddHgrVk = false;
      bool qhAQWsStbi = false;
      bool qIcpHapwLB = false;
      bool bahLxjPqmV = false;
      bool jwZJPYaHCi = false;
      bool LEudkBcmVC = false;
      bool RjfUIQzoTm = false;
      bool caGFzuiTai = false;
      bool zhtcoXeEZu = false;
      bool GcUjEzPEBy = false;
      bool YlnOFjxpep = false;
      bool SJMlCipDej = false;
      bool luOYfAGWAz = false;
      bool edSbKNteXE = false;
      bool anZibxPigV = false;
      bool JMZQMdWOiF = false;
      bool dZpeLopjbo = false;
      bool oKfaJxVfwh = false;
      bool jXoepSECOf = false;
      string UuPEffZUYO;
      string NXcHWQqNws;
      string WoRVPSdSQe;
      string RITxuAwiiX;
      string aVcbOXnjNU;
      string soGTwecsnN;
      string BGEswEEeMW;
      string UIdXSBMoHq;
      string dsFwlcCABQ;
      string XCtVWTQjfK;
      string TIXqzkKhBu;
      string SmlwiIBHGS;
      string BDdwySNIBy;
      string jbJxXVVNxB;
      string SUyFxjQymO;
      string SJcNIPebrf;
      string WCfCLpdnYN;
      string lmKFzfFXyO;
      string CPVmfayunH;
      string psUQdQowtH;
      if(UuPEffZUYO == TIXqzkKhBu){GbYYbeyXNc = true;}
      else if(TIXqzkKhBu == UuPEffZUYO){GcUjEzPEBy = true;}
      if(NXcHWQqNws == SmlwiIBHGS){KGdddHgrVk = true;}
      else if(SmlwiIBHGS == NXcHWQqNws){YlnOFjxpep = true;}
      if(WoRVPSdSQe == BDdwySNIBy){qhAQWsStbi = true;}
      else if(BDdwySNIBy == WoRVPSdSQe){SJMlCipDej = true;}
      if(RITxuAwiiX == jbJxXVVNxB){qIcpHapwLB = true;}
      else if(jbJxXVVNxB == RITxuAwiiX){luOYfAGWAz = true;}
      if(aVcbOXnjNU == SUyFxjQymO){bahLxjPqmV = true;}
      else if(SUyFxjQymO == aVcbOXnjNU){edSbKNteXE = true;}
      if(soGTwecsnN == SJcNIPebrf){jwZJPYaHCi = true;}
      else if(SJcNIPebrf == soGTwecsnN){anZibxPigV = true;}
      if(BGEswEEeMW == WCfCLpdnYN){LEudkBcmVC = true;}
      else if(WCfCLpdnYN == BGEswEEeMW){JMZQMdWOiF = true;}
      if(UIdXSBMoHq == lmKFzfFXyO){RjfUIQzoTm = true;}
      if(dsFwlcCABQ == CPVmfayunH){caGFzuiTai = true;}
      if(XCtVWTQjfK == psUQdQowtH){zhtcoXeEZu = true;}
      while(lmKFzfFXyO == UIdXSBMoHq){dZpeLopjbo = true;}
      while(CPVmfayunH == CPVmfayunH){oKfaJxVfwh = true;}
      while(psUQdQowtH == psUQdQowtH){jXoepSECOf = true;}
      if(GbYYbeyXNc == true){GbYYbeyXNc = false;}
      if(KGdddHgrVk == true){KGdddHgrVk = false;}
      if(qhAQWsStbi == true){qhAQWsStbi = false;}
      if(qIcpHapwLB == true){qIcpHapwLB = false;}
      if(bahLxjPqmV == true){bahLxjPqmV = false;}
      if(jwZJPYaHCi == true){jwZJPYaHCi = false;}
      if(LEudkBcmVC == true){LEudkBcmVC = false;}
      if(RjfUIQzoTm == true){RjfUIQzoTm = false;}
      if(caGFzuiTai == true){caGFzuiTai = false;}
      if(zhtcoXeEZu == true){zhtcoXeEZu = false;}
      if(GcUjEzPEBy == true){GcUjEzPEBy = false;}
      if(YlnOFjxpep == true){YlnOFjxpep = false;}
      if(SJMlCipDej == true){SJMlCipDej = false;}
      if(luOYfAGWAz == true){luOYfAGWAz = false;}
      if(edSbKNteXE == true){edSbKNteXE = false;}
      if(anZibxPigV == true){anZibxPigV = false;}
      if(JMZQMdWOiF == true){JMZQMdWOiF = false;}
      if(dZpeLopjbo == true){dZpeLopjbo = false;}
      if(oKfaJxVfwh == true){oKfaJxVfwh = false;}
      if(jXoepSECOf == true){jXoepSECOf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRGOAOYCKD
{ 
  void GQrNmyXELa()
  { 
      bool QtBDTBCZsG = false;
      bool YGYpbCLIWP = false;
      bool DcExAAfnHp = false;
      bool JNgXZbWicW = false;
      bool UtDSVJLqEA = false;
      bool xQfGemoDCT = false;
      bool UORCxKYBPz = false;
      bool fbeztIZlbp = false;
      bool nnjHsshasl = false;
      bool mTfJBGbAUK = false;
      bool kKaETUlfLV = false;
      bool NDaLegdJJD = false;
      bool bxIdMMuVyn = false;
      bool gZQRFdNfmX = false;
      bool HCPWYirTdU = false;
      bool bSqRhnCxqH = false;
      bool YPhXonmJGB = false;
      bool SyVkwZgkEc = false;
      bool TaqcLNhziR = false;
      bool aPnfyqTrhk = false;
      string YEuGIChBPD;
      string HlxgotaMaX;
      string OREeoWrccD;
      string jEqsnEhmuQ;
      string uumRIAajAF;
      string fWRKBGAQRl;
      string JEXMTCuEsk;
      string LmQJcSelWo;
      string wHcXWMmfrg;
      string ERVJHpXZyF;
      string EWqOsrFHhh;
      string bNtbpBbzoG;
      string OOMLgtRGCl;
      string uEnQjZQOed;
      string HeyJFpXsTF;
      string OXkrqoJegy;
      string ayFumWZdrQ;
      string kNULyjQDGq;
      string WXmxXXTwYt;
      string PkgfDIZCVh;
      if(YEuGIChBPD == EWqOsrFHhh){QtBDTBCZsG = true;}
      else if(EWqOsrFHhh == YEuGIChBPD){kKaETUlfLV = true;}
      if(HlxgotaMaX == bNtbpBbzoG){YGYpbCLIWP = true;}
      else if(bNtbpBbzoG == HlxgotaMaX){NDaLegdJJD = true;}
      if(OREeoWrccD == OOMLgtRGCl){DcExAAfnHp = true;}
      else if(OOMLgtRGCl == OREeoWrccD){bxIdMMuVyn = true;}
      if(jEqsnEhmuQ == uEnQjZQOed){JNgXZbWicW = true;}
      else if(uEnQjZQOed == jEqsnEhmuQ){gZQRFdNfmX = true;}
      if(uumRIAajAF == HeyJFpXsTF){UtDSVJLqEA = true;}
      else if(HeyJFpXsTF == uumRIAajAF){HCPWYirTdU = true;}
      if(fWRKBGAQRl == OXkrqoJegy){xQfGemoDCT = true;}
      else if(OXkrqoJegy == fWRKBGAQRl){bSqRhnCxqH = true;}
      if(JEXMTCuEsk == ayFumWZdrQ){UORCxKYBPz = true;}
      else if(ayFumWZdrQ == JEXMTCuEsk){YPhXonmJGB = true;}
      if(LmQJcSelWo == kNULyjQDGq){fbeztIZlbp = true;}
      if(wHcXWMmfrg == WXmxXXTwYt){nnjHsshasl = true;}
      if(ERVJHpXZyF == PkgfDIZCVh){mTfJBGbAUK = true;}
      while(kNULyjQDGq == LmQJcSelWo){SyVkwZgkEc = true;}
      while(WXmxXXTwYt == WXmxXXTwYt){TaqcLNhziR = true;}
      while(PkgfDIZCVh == PkgfDIZCVh){aPnfyqTrhk = true;}
      if(QtBDTBCZsG == true){QtBDTBCZsG = false;}
      if(YGYpbCLIWP == true){YGYpbCLIWP = false;}
      if(DcExAAfnHp == true){DcExAAfnHp = false;}
      if(JNgXZbWicW == true){JNgXZbWicW = false;}
      if(UtDSVJLqEA == true){UtDSVJLqEA = false;}
      if(xQfGemoDCT == true){xQfGemoDCT = false;}
      if(UORCxKYBPz == true){UORCxKYBPz = false;}
      if(fbeztIZlbp == true){fbeztIZlbp = false;}
      if(nnjHsshasl == true){nnjHsshasl = false;}
      if(mTfJBGbAUK == true){mTfJBGbAUK = false;}
      if(kKaETUlfLV == true){kKaETUlfLV = false;}
      if(NDaLegdJJD == true){NDaLegdJJD = false;}
      if(bxIdMMuVyn == true){bxIdMMuVyn = false;}
      if(gZQRFdNfmX == true){gZQRFdNfmX = false;}
      if(HCPWYirTdU == true){HCPWYirTdU = false;}
      if(bSqRhnCxqH == true){bSqRhnCxqH = false;}
      if(YPhXonmJGB == true){YPhXonmJGB = false;}
      if(SyVkwZgkEc == true){SyVkwZgkEc = false;}
      if(TaqcLNhziR == true){TaqcLNhziR = false;}
      if(aPnfyqTrhk == true){aPnfyqTrhk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NIQLCYJIUH
{ 
  void iuXlJNyCMa()
  { 
      bool NYWiuWXZUp = false;
      bool fFWLWUpASG = false;
      bool WHtDaOFyxX = false;
      bool MoESQGkDfd = false;
      bool uiHodgcjWC = false;
      bool CEZdDGdTIf = false;
      bool QYbwdpBEtP = false;
      bool imUnLnzFZt = false;
      bool lVbtVHOZPK = false;
      bool cRuzNVGLKm = false;
      bool fYoGTPjkSP = false;
      bool GXsOttxgZW = false;
      bool abnjmRqUao = false;
      bool gntlONgUaG = false;
      bool WdGzDEYgES = false;
      bool YZknLDjETC = false;
      bool XPKchRdGAg = false;
      bool NcGTzxUofh = false;
      bool rKQIQHDFaK = false;
      bool cbAYhHScQl = false;
      string qZAMSIVWIG;
      string TojpxRFyeh;
      string MjoqsssiEM;
      string fdlQydYoTE;
      string xXNAwMOJia;
      string ntlexGkJSZ;
      string OlSwapCTrT;
      string sPeZknWntg;
      string diAcYlrHTq;
      string sOVsoKFRZG;
      string JuRPgXOLtI;
      string jwPkwfloWn;
      string xuAAZeskjZ;
      string iENnXhQkwB;
      string WfMKGwzkxJ;
      string YPulINuQoC;
      string ddaTZfiaNN;
      string OBrVRRhosd;
      string eImaBSIbfJ;
      string mAutXsFska;
      if(qZAMSIVWIG == JuRPgXOLtI){NYWiuWXZUp = true;}
      else if(JuRPgXOLtI == qZAMSIVWIG){fYoGTPjkSP = true;}
      if(TojpxRFyeh == jwPkwfloWn){fFWLWUpASG = true;}
      else if(jwPkwfloWn == TojpxRFyeh){GXsOttxgZW = true;}
      if(MjoqsssiEM == xuAAZeskjZ){WHtDaOFyxX = true;}
      else if(xuAAZeskjZ == MjoqsssiEM){abnjmRqUao = true;}
      if(fdlQydYoTE == iENnXhQkwB){MoESQGkDfd = true;}
      else if(iENnXhQkwB == fdlQydYoTE){gntlONgUaG = true;}
      if(xXNAwMOJia == WfMKGwzkxJ){uiHodgcjWC = true;}
      else if(WfMKGwzkxJ == xXNAwMOJia){WdGzDEYgES = true;}
      if(ntlexGkJSZ == YPulINuQoC){CEZdDGdTIf = true;}
      else if(YPulINuQoC == ntlexGkJSZ){YZknLDjETC = true;}
      if(OlSwapCTrT == ddaTZfiaNN){QYbwdpBEtP = true;}
      else if(ddaTZfiaNN == OlSwapCTrT){XPKchRdGAg = true;}
      if(sPeZknWntg == OBrVRRhosd){imUnLnzFZt = true;}
      if(diAcYlrHTq == eImaBSIbfJ){lVbtVHOZPK = true;}
      if(sOVsoKFRZG == mAutXsFska){cRuzNVGLKm = true;}
      while(OBrVRRhosd == sPeZknWntg){NcGTzxUofh = true;}
      while(eImaBSIbfJ == eImaBSIbfJ){rKQIQHDFaK = true;}
      while(mAutXsFska == mAutXsFska){cbAYhHScQl = true;}
      if(NYWiuWXZUp == true){NYWiuWXZUp = false;}
      if(fFWLWUpASG == true){fFWLWUpASG = false;}
      if(WHtDaOFyxX == true){WHtDaOFyxX = false;}
      if(MoESQGkDfd == true){MoESQGkDfd = false;}
      if(uiHodgcjWC == true){uiHodgcjWC = false;}
      if(CEZdDGdTIf == true){CEZdDGdTIf = false;}
      if(QYbwdpBEtP == true){QYbwdpBEtP = false;}
      if(imUnLnzFZt == true){imUnLnzFZt = false;}
      if(lVbtVHOZPK == true){lVbtVHOZPK = false;}
      if(cRuzNVGLKm == true){cRuzNVGLKm = false;}
      if(fYoGTPjkSP == true){fYoGTPjkSP = false;}
      if(GXsOttxgZW == true){GXsOttxgZW = false;}
      if(abnjmRqUao == true){abnjmRqUao = false;}
      if(gntlONgUaG == true){gntlONgUaG = false;}
      if(WdGzDEYgES == true){WdGzDEYgES = false;}
      if(YZknLDjETC == true){YZknLDjETC = false;}
      if(XPKchRdGAg == true){XPKchRdGAg = false;}
      if(NcGTzxUofh == true){NcGTzxUofh = false;}
      if(rKQIQHDFaK == true){rKQIQHDFaK = false;}
      if(cbAYhHScQl == true){cbAYhHScQl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JALZBWXROM
{ 
  void CuGlufTEuS()
  { 
      bool aGenQGhWNx = false;
      bool gKjeYalAst = false;
      bool QAnpZwkhCx = false;
      bool tiloCnVZsZ = false;
      bool VOSjSorzpf = false;
      bool KjfMiaRoOT = false;
      bool UATQCxYtbj = false;
      bool ELHTYBhEXj = false;
      bool DlrWmKDYGb = false;
      bool WgLYEVuCgU = false;
      bool QyWFazbLng = false;
      bool sNRdQhHxcr = false;
      bool tznzNXAhOD = false;
      bool GeXCSFPmum = false;
      bool hrkYiJPgIW = false;
      bool NxYnaQKWqD = false;
      bool ztwkaNoOKK = false;
      bool SUBoKBOOQE = false;
      bool ISZrpIFibC = false;
      bool ururnnuAxV = false;
      string EWnsClsGos;
      string PPMtPdxMYr;
      string SsIwXJtDyL;
      string bifVguyXnI;
      string PVCRjixcRW;
      string aBbEfKOqVs;
      string roIdRgjqMU;
      string eZXQbxppMo;
      string MRkbjZGboV;
      string gHCuQZMYAC;
      string yGPxqAcLbi;
      string TXefgZEgsq;
      string aIBqmWXcAC;
      string jRpJpGBnjj;
      string xuzGBJbVOp;
      string VffIbpFYJU;
      string cAKZyChVpZ;
      string YPxJteItod;
      string uBOKfElggz;
      string AbdPGwjZHz;
      if(EWnsClsGos == yGPxqAcLbi){aGenQGhWNx = true;}
      else if(yGPxqAcLbi == EWnsClsGos){QyWFazbLng = true;}
      if(PPMtPdxMYr == TXefgZEgsq){gKjeYalAst = true;}
      else if(TXefgZEgsq == PPMtPdxMYr){sNRdQhHxcr = true;}
      if(SsIwXJtDyL == aIBqmWXcAC){QAnpZwkhCx = true;}
      else if(aIBqmWXcAC == SsIwXJtDyL){tznzNXAhOD = true;}
      if(bifVguyXnI == jRpJpGBnjj){tiloCnVZsZ = true;}
      else if(jRpJpGBnjj == bifVguyXnI){GeXCSFPmum = true;}
      if(PVCRjixcRW == xuzGBJbVOp){VOSjSorzpf = true;}
      else if(xuzGBJbVOp == PVCRjixcRW){hrkYiJPgIW = true;}
      if(aBbEfKOqVs == VffIbpFYJU){KjfMiaRoOT = true;}
      else if(VffIbpFYJU == aBbEfKOqVs){NxYnaQKWqD = true;}
      if(roIdRgjqMU == cAKZyChVpZ){UATQCxYtbj = true;}
      else if(cAKZyChVpZ == roIdRgjqMU){ztwkaNoOKK = true;}
      if(eZXQbxppMo == YPxJteItod){ELHTYBhEXj = true;}
      if(MRkbjZGboV == uBOKfElggz){DlrWmKDYGb = true;}
      if(gHCuQZMYAC == AbdPGwjZHz){WgLYEVuCgU = true;}
      while(YPxJteItod == eZXQbxppMo){SUBoKBOOQE = true;}
      while(uBOKfElggz == uBOKfElggz){ISZrpIFibC = true;}
      while(AbdPGwjZHz == AbdPGwjZHz){ururnnuAxV = true;}
      if(aGenQGhWNx == true){aGenQGhWNx = false;}
      if(gKjeYalAst == true){gKjeYalAst = false;}
      if(QAnpZwkhCx == true){QAnpZwkhCx = false;}
      if(tiloCnVZsZ == true){tiloCnVZsZ = false;}
      if(VOSjSorzpf == true){VOSjSorzpf = false;}
      if(KjfMiaRoOT == true){KjfMiaRoOT = false;}
      if(UATQCxYtbj == true){UATQCxYtbj = false;}
      if(ELHTYBhEXj == true){ELHTYBhEXj = false;}
      if(DlrWmKDYGb == true){DlrWmKDYGb = false;}
      if(WgLYEVuCgU == true){WgLYEVuCgU = false;}
      if(QyWFazbLng == true){QyWFazbLng = false;}
      if(sNRdQhHxcr == true){sNRdQhHxcr = false;}
      if(tznzNXAhOD == true){tznzNXAhOD = false;}
      if(GeXCSFPmum == true){GeXCSFPmum = false;}
      if(hrkYiJPgIW == true){hrkYiJPgIW = false;}
      if(NxYnaQKWqD == true){NxYnaQKWqD = false;}
      if(ztwkaNoOKK == true){ztwkaNoOKK = false;}
      if(SUBoKBOOQE == true){SUBoKBOOQE = false;}
      if(ISZrpIFibC == true){ISZrpIFibC = false;}
      if(ururnnuAxV == true){ururnnuAxV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYRHCVJQMP
{ 
  void aOhcJxcZME()
  { 
      bool BLZioiHaDW = false;
      bool gFXUKQPqmR = false;
      bool ByCVpryhmz = false;
      bool FoCcCxFcqp = false;
      bool wghMmKnWXG = false;
      bool TnLalCJErx = false;
      bool kZmEQqDtRN = false;
      bool KmzwVTPpif = false;
      bool DaJgfQcbqA = false;
      bool mBjsEWsduu = false;
      bool GtEJufoPER = false;
      bool mTVMtKPGYz = false;
      bool ObCRZJDFqz = false;
      bool ZltmYIVAkz = false;
      bool bNWZNTfWzt = false;
      bool GmFwgeqmil = false;
      bool ciXFqAZhnk = false;
      bool oOUYXBEcEG = false;
      bool cfGxrlgyGs = false;
      bool RiQyWspQhM = false;
      string gljkQUdiqN;
      string SsBVAUXegL;
      string ITUWzNNlly;
      string fbVdKNngQG;
      string boJOkqjLDI;
      string krZxRMQNlC;
      string GrxshpXXKm;
      string gqOajTKGkH;
      string dBhdNnCYMy;
      string wZtNzjqQgu;
      string TMAPasczMx;
      string CKbdXFJTet;
      string nzKMpGwBaA;
      string bsYpnRASCT;
      string KDLOwlxQot;
      string ZXkmHTBnZT;
      string wbXMVIklpG;
      string EqQKikmuQE;
      string IfLgZDHliT;
      string PMriWieysm;
      if(gljkQUdiqN == TMAPasczMx){BLZioiHaDW = true;}
      else if(TMAPasczMx == gljkQUdiqN){GtEJufoPER = true;}
      if(SsBVAUXegL == CKbdXFJTet){gFXUKQPqmR = true;}
      else if(CKbdXFJTet == SsBVAUXegL){mTVMtKPGYz = true;}
      if(ITUWzNNlly == nzKMpGwBaA){ByCVpryhmz = true;}
      else if(nzKMpGwBaA == ITUWzNNlly){ObCRZJDFqz = true;}
      if(fbVdKNngQG == bsYpnRASCT){FoCcCxFcqp = true;}
      else if(bsYpnRASCT == fbVdKNngQG){ZltmYIVAkz = true;}
      if(boJOkqjLDI == KDLOwlxQot){wghMmKnWXG = true;}
      else if(KDLOwlxQot == boJOkqjLDI){bNWZNTfWzt = true;}
      if(krZxRMQNlC == ZXkmHTBnZT){TnLalCJErx = true;}
      else if(ZXkmHTBnZT == krZxRMQNlC){GmFwgeqmil = true;}
      if(GrxshpXXKm == wbXMVIklpG){kZmEQqDtRN = true;}
      else if(wbXMVIklpG == GrxshpXXKm){ciXFqAZhnk = true;}
      if(gqOajTKGkH == EqQKikmuQE){KmzwVTPpif = true;}
      if(dBhdNnCYMy == IfLgZDHliT){DaJgfQcbqA = true;}
      if(wZtNzjqQgu == PMriWieysm){mBjsEWsduu = true;}
      while(EqQKikmuQE == gqOajTKGkH){oOUYXBEcEG = true;}
      while(IfLgZDHliT == IfLgZDHliT){cfGxrlgyGs = true;}
      while(PMriWieysm == PMriWieysm){RiQyWspQhM = true;}
      if(BLZioiHaDW == true){BLZioiHaDW = false;}
      if(gFXUKQPqmR == true){gFXUKQPqmR = false;}
      if(ByCVpryhmz == true){ByCVpryhmz = false;}
      if(FoCcCxFcqp == true){FoCcCxFcqp = false;}
      if(wghMmKnWXG == true){wghMmKnWXG = false;}
      if(TnLalCJErx == true){TnLalCJErx = false;}
      if(kZmEQqDtRN == true){kZmEQqDtRN = false;}
      if(KmzwVTPpif == true){KmzwVTPpif = false;}
      if(DaJgfQcbqA == true){DaJgfQcbqA = false;}
      if(mBjsEWsduu == true){mBjsEWsduu = false;}
      if(GtEJufoPER == true){GtEJufoPER = false;}
      if(mTVMtKPGYz == true){mTVMtKPGYz = false;}
      if(ObCRZJDFqz == true){ObCRZJDFqz = false;}
      if(ZltmYIVAkz == true){ZltmYIVAkz = false;}
      if(bNWZNTfWzt == true){bNWZNTfWzt = false;}
      if(GmFwgeqmil == true){GmFwgeqmil = false;}
      if(ciXFqAZhnk == true){ciXFqAZhnk = false;}
      if(oOUYXBEcEG == true){oOUYXBEcEG = false;}
      if(cfGxrlgyGs == true){cfGxrlgyGs = false;}
      if(RiQyWspQhM == true){RiQyWspQhM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBTBQXRZHO
{ 
  void MiOiGhNyFM()
  { 
      bool ZuaVweXpEM = false;
      bool UjXDtWrOVl = false;
      bool jnwoRllaTe = false;
      bool FnfzeXxhxx = false;
      bool ELClXWmERL = false;
      bool hIWSbkzkEJ = false;
      bool swVYGgEXXW = false;
      bool YJQYhYkJRt = false;
      bool zhIHxwQMXs = false;
      bool YMdnDHpdfp = false;
      bool SOfulXqykC = false;
      bool ApSJKLmObK = false;
      bool PqAexMecVZ = false;
      bool iHdabjBNUY = false;
      bool ESbUsisUcq = false;
      bool UbBUabOAxZ = false;
      bool rObLTrLqhZ = false;
      bool JZsCFxOekO = false;
      bool TKAdFHGIAA = false;
      bool VBPugppQBB = false;
      string dMFWCHGVkM;
      string psMUPiIyub;
      string HdrfUyYwGA;
      string OBaneEzoAU;
      string rqKlpuxiuH;
      string utWiSATYCD;
      string hJOkxoSYoL;
      string iTxZiQTGoY;
      string BoAzFUdrUe;
      string jZlxlhbYnA;
      string cYtjXawxzC;
      string gNjdCrJPfc;
      string KZDKaJgzmA;
      string ntRoucuQad;
      string XgrSyVpIus;
      string YMrKpCUjIN;
      string txJyNlwuhY;
      string xsnCFchkLF;
      string TXEtbbBHyr;
      string HLHMiaXsEL;
      if(dMFWCHGVkM == cYtjXawxzC){ZuaVweXpEM = true;}
      else if(cYtjXawxzC == dMFWCHGVkM){SOfulXqykC = true;}
      if(psMUPiIyub == gNjdCrJPfc){UjXDtWrOVl = true;}
      else if(gNjdCrJPfc == psMUPiIyub){ApSJKLmObK = true;}
      if(HdrfUyYwGA == KZDKaJgzmA){jnwoRllaTe = true;}
      else if(KZDKaJgzmA == HdrfUyYwGA){PqAexMecVZ = true;}
      if(OBaneEzoAU == ntRoucuQad){FnfzeXxhxx = true;}
      else if(ntRoucuQad == OBaneEzoAU){iHdabjBNUY = true;}
      if(rqKlpuxiuH == XgrSyVpIus){ELClXWmERL = true;}
      else if(XgrSyVpIus == rqKlpuxiuH){ESbUsisUcq = true;}
      if(utWiSATYCD == YMrKpCUjIN){hIWSbkzkEJ = true;}
      else if(YMrKpCUjIN == utWiSATYCD){UbBUabOAxZ = true;}
      if(hJOkxoSYoL == txJyNlwuhY){swVYGgEXXW = true;}
      else if(txJyNlwuhY == hJOkxoSYoL){rObLTrLqhZ = true;}
      if(iTxZiQTGoY == xsnCFchkLF){YJQYhYkJRt = true;}
      if(BoAzFUdrUe == TXEtbbBHyr){zhIHxwQMXs = true;}
      if(jZlxlhbYnA == HLHMiaXsEL){YMdnDHpdfp = true;}
      while(xsnCFchkLF == iTxZiQTGoY){JZsCFxOekO = true;}
      while(TXEtbbBHyr == TXEtbbBHyr){TKAdFHGIAA = true;}
      while(HLHMiaXsEL == HLHMiaXsEL){VBPugppQBB = true;}
      if(ZuaVweXpEM == true){ZuaVweXpEM = false;}
      if(UjXDtWrOVl == true){UjXDtWrOVl = false;}
      if(jnwoRllaTe == true){jnwoRllaTe = false;}
      if(FnfzeXxhxx == true){FnfzeXxhxx = false;}
      if(ELClXWmERL == true){ELClXWmERL = false;}
      if(hIWSbkzkEJ == true){hIWSbkzkEJ = false;}
      if(swVYGgEXXW == true){swVYGgEXXW = false;}
      if(YJQYhYkJRt == true){YJQYhYkJRt = false;}
      if(zhIHxwQMXs == true){zhIHxwQMXs = false;}
      if(YMdnDHpdfp == true){YMdnDHpdfp = false;}
      if(SOfulXqykC == true){SOfulXqykC = false;}
      if(ApSJKLmObK == true){ApSJKLmObK = false;}
      if(PqAexMecVZ == true){PqAexMecVZ = false;}
      if(iHdabjBNUY == true){iHdabjBNUY = false;}
      if(ESbUsisUcq == true){ESbUsisUcq = false;}
      if(UbBUabOAxZ == true){UbBUabOAxZ = false;}
      if(rObLTrLqhZ == true){rObLTrLqhZ = false;}
      if(JZsCFxOekO == true){JZsCFxOekO = false;}
      if(TKAdFHGIAA == true){TKAdFHGIAA = false;}
      if(VBPugppQBB == true){VBPugppQBB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VUHVSMYEMX
{ 
  void mCczczYiOG()
  { 
      bool uIkHlChoXj = false;
      bool zzJgHFjxhj = false;
      bool FqoZSajOWT = false;
      bool nYnclwlgRr = false;
      bool FgkEEDNOgr = false;
      bool GwXgSDSKoL = false;
      bool RTRDwaLguL = false;
      bool SDfoeXGkVO = false;
      bool NVgeNqAGJh = false;
      bool carGZlPgHc = false;
      bool rgSVYDQiBu = false;
      bool xhoZxwlmpE = false;
      bool ZEWNhqKZOs = false;
      bool IZcrWgCLFJ = false;
      bool aRFOjulRId = false;
      bool zcpDDmJFmh = false;
      bool rqTIlXExDQ = false;
      bool sZggdIzHcm = false;
      bool EsRksfiZoi = false;
      bool WwYXQjywcM = false;
      string NoNDgOxkHR;
      string JsfNskidQP;
      string OVwUQqdGbX;
      string gqsyAeSRAF;
      string OzmuPphdFV;
      string hWDFLqrrmp;
      string jqJjkRzgNO;
      string RRdLAOiBFZ;
      string JAAFpJnmlJ;
      string lZdKUXpDJx;
      string qAPqEPsqFx;
      string HqmNfipEta;
      string dMuDbrmTpc;
      string YfqIiJjJBZ;
      string QwhoBumPdl;
      string hkIiSdFMOM;
      string cYBbXbzeeW;
      string zfDTKhdFCg;
      string EXoEtmWIoE;
      string DXuoxqtFRY;
      if(NoNDgOxkHR == qAPqEPsqFx){uIkHlChoXj = true;}
      else if(qAPqEPsqFx == NoNDgOxkHR){rgSVYDQiBu = true;}
      if(JsfNskidQP == HqmNfipEta){zzJgHFjxhj = true;}
      else if(HqmNfipEta == JsfNskidQP){xhoZxwlmpE = true;}
      if(OVwUQqdGbX == dMuDbrmTpc){FqoZSajOWT = true;}
      else if(dMuDbrmTpc == OVwUQqdGbX){ZEWNhqKZOs = true;}
      if(gqsyAeSRAF == YfqIiJjJBZ){nYnclwlgRr = true;}
      else if(YfqIiJjJBZ == gqsyAeSRAF){IZcrWgCLFJ = true;}
      if(OzmuPphdFV == QwhoBumPdl){FgkEEDNOgr = true;}
      else if(QwhoBumPdl == OzmuPphdFV){aRFOjulRId = true;}
      if(hWDFLqrrmp == hkIiSdFMOM){GwXgSDSKoL = true;}
      else if(hkIiSdFMOM == hWDFLqrrmp){zcpDDmJFmh = true;}
      if(jqJjkRzgNO == cYBbXbzeeW){RTRDwaLguL = true;}
      else if(cYBbXbzeeW == jqJjkRzgNO){rqTIlXExDQ = true;}
      if(RRdLAOiBFZ == zfDTKhdFCg){SDfoeXGkVO = true;}
      if(JAAFpJnmlJ == EXoEtmWIoE){NVgeNqAGJh = true;}
      if(lZdKUXpDJx == DXuoxqtFRY){carGZlPgHc = true;}
      while(zfDTKhdFCg == RRdLAOiBFZ){sZggdIzHcm = true;}
      while(EXoEtmWIoE == EXoEtmWIoE){EsRksfiZoi = true;}
      while(DXuoxqtFRY == DXuoxqtFRY){WwYXQjywcM = true;}
      if(uIkHlChoXj == true){uIkHlChoXj = false;}
      if(zzJgHFjxhj == true){zzJgHFjxhj = false;}
      if(FqoZSajOWT == true){FqoZSajOWT = false;}
      if(nYnclwlgRr == true){nYnclwlgRr = false;}
      if(FgkEEDNOgr == true){FgkEEDNOgr = false;}
      if(GwXgSDSKoL == true){GwXgSDSKoL = false;}
      if(RTRDwaLguL == true){RTRDwaLguL = false;}
      if(SDfoeXGkVO == true){SDfoeXGkVO = false;}
      if(NVgeNqAGJh == true){NVgeNqAGJh = false;}
      if(carGZlPgHc == true){carGZlPgHc = false;}
      if(rgSVYDQiBu == true){rgSVYDQiBu = false;}
      if(xhoZxwlmpE == true){xhoZxwlmpE = false;}
      if(ZEWNhqKZOs == true){ZEWNhqKZOs = false;}
      if(IZcrWgCLFJ == true){IZcrWgCLFJ = false;}
      if(aRFOjulRId == true){aRFOjulRId = false;}
      if(zcpDDmJFmh == true){zcpDDmJFmh = false;}
      if(rqTIlXExDQ == true){rqTIlXExDQ = false;}
      if(sZggdIzHcm == true){sZggdIzHcm = false;}
      if(EsRksfiZoi == true){EsRksfiZoi = false;}
      if(WwYXQjywcM == true){WwYXQjywcM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VAJADRIMLS
{ 
  void luyqOGUsdZ()
  { 
      bool cjmNiKEQHq = false;
      bool VOdMwLYUQZ = false;
      bool OxOdtqozEc = false;
      bool sueTtCYaVM = false;
      bool YHOjndUIRC = false;
      bool hzStOfVJTq = false;
      bool UELexZjKSs = false;
      bool lxyEAGhdoP = false;
      bool WggCtscjEO = false;
      bool gOGdrUwjlO = false;
      bool tJoYPkAOsH = false;
      bool xqTEUnWIjE = false;
      bool wzFELXpUMf = false;
      bool KyqZUMqImJ = false;
      bool sOpwRptCJD = false;
      bool xmzhRuEkMr = false;
      bool tfCNxyztiH = false;
      bool xOVaKgIIlV = false;
      bool cmKIiXyIHZ = false;
      bool IFutOMMczS = false;
      string VgOAXPwKUy;
      string ZZpZeUJbun;
      string EglChfgUEV;
      string SWPsAbJtnZ;
      string LhlaMPjPIJ;
      string ZsYJVotLRq;
      string haFzeDKwZC;
      string LOnVbWtKoR;
      string uQLuuZxFXK;
      string gxbxqjbmwJ;
      string FmpGxKEDgy;
      string tiVAuRPKDE;
      string FEYOVOmqdr;
      string uHOfLHaFxk;
      string UsYYQyabBZ;
      string URiqDBObji;
      string WNYoDmUpnm;
      string pJNSjMfAxX;
      string mLoEXcXWbK;
      string syUNNGTjUd;
      if(VgOAXPwKUy == FmpGxKEDgy){cjmNiKEQHq = true;}
      else if(FmpGxKEDgy == VgOAXPwKUy){tJoYPkAOsH = true;}
      if(ZZpZeUJbun == tiVAuRPKDE){VOdMwLYUQZ = true;}
      else if(tiVAuRPKDE == ZZpZeUJbun){xqTEUnWIjE = true;}
      if(EglChfgUEV == FEYOVOmqdr){OxOdtqozEc = true;}
      else if(FEYOVOmqdr == EglChfgUEV){wzFELXpUMf = true;}
      if(SWPsAbJtnZ == uHOfLHaFxk){sueTtCYaVM = true;}
      else if(uHOfLHaFxk == SWPsAbJtnZ){KyqZUMqImJ = true;}
      if(LhlaMPjPIJ == UsYYQyabBZ){YHOjndUIRC = true;}
      else if(UsYYQyabBZ == LhlaMPjPIJ){sOpwRptCJD = true;}
      if(ZsYJVotLRq == URiqDBObji){hzStOfVJTq = true;}
      else if(URiqDBObji == ZsYJVotLRq){xmzhRuEkMr = true;}
      if(haFzeDKwZC == WNYoDmUpnm){UELexZjKSs = true;}
      else if(WNYoDmUpnm == haFzeDKwZC){tfCNxyztiH = true;}
      if(LOnVbWtKoR == pJNSjMfAxX){lxyEAGhdoP = true;}
      if(uQLuuZxFXK == mLoEXcXWbK){WggCtscjEO = true;}
      if(gxbxqjbmwJ == syUNNGTjUd){gOGdrUwjlO = true;}
      while(pJNSjMfAxX == LOnVbWtKoR){xOVaKgIIlV = true;}
      while(mLoEXcXWbK == mLoEXcXWbK){cmKIiXyIHZ = true;}
      while(syUNNGTjUd == syUNNGTjUd){IFutOMMczS = true;}
      if(cjmNiKEQHq == true){cjmNiKEQHq = false;}
      if(VOdMwLYUQZ == true){VOdMwLYUQZ = false;}
      if(OxOdtqozEc == true){OxOdtqozEc = false;}
      if(sueTtCYaVM == true){sueTtCYaVM = false;}
      if(YHOjndUIRC == true){YHOjndUIRC = false;}
      if(hzStOfVJTq == true){hzStOfVJTq = false;}
      if(UELexZjKSs == true){UELexZjKSs = false;}
      if(lxyEAGhdoP == true){lxyEAGhdoP = false;}
      if(WggCtscjEO == true){WggCtscjEO = false;}
      if(gOGdrUwjlO == true){gOGdrUwjlO = false;}
      if(tJoYPkAOsH == true){tJoYPkAOsH = false;}
      if(xqTEUnWIjE == true){xqTEUnWIjE = false;}
      if(wzFELXpUMf == true){wzFELXpUMf = false;}
      if(KyqZUMqImJ == true){KyqZUMqImJ = false;}
      if(sOpwRptCJD == true){sOpwRptCJD = false;}
      if(xmzhRuEkMr == true){xmzhRuEkMr = false;}
      if(tfCNxyztiH == true){tfCNxyztiH = false;}
      if(xOVaKgIIlV == true){xOVaKgIIlV = false;}
      if(cmKIiXyIHZ == true){cmKIiXyIHZ = false;}
      if(IFutOMMczS == true){IFutOMMczS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVMOIKWWEI
{ 
  void sBBdbejGfe()
  { 
      bool RkuKAkkelm = false;
      bool drcwLCVPOF = false;
      bool msDhrBAaNN = false;
      bool uMFPgDIdPH = false;
      bool SZisKdbmNR = false;
      bool aLiTLYgNSy = false;
      bool kKRXrRlMPI = false;
      bool tqAGmMKKWN = false;
      bool YNNwmjckDH = false;
      bool VtLQVHIKBs = false;
      bool qOWEWjLcgy = false;
      bool NWpEYXxUkH = false;
      bool nBJHmzfije = false;
      bool DAIdVJpIYC = false;
      bool XADEtyDGqy = false;
      bool KnZsFpFORX = false;
      bool DbrBuNOMhO = false;
      bool gouhjmxENn = false;
      bool uYrkUPZOYf = false;
      bool EbpBzuICJg = false;
      string cEWSHsxSow;
      string fujOPXtTkM;
      string ZbrKhRyZHZ;
      string zrCkFXLDXE;
      string KWkLcykFSW;
      string UTiYCBLLjp;
      string tXKOxnsyJq;
      string LpwfCCpfhi;
      string grHkFeJciD;
      string LAThJlLWOo;
      string FmwaLdXCWz;
      string LedAICQZJR;
      string dPOFeKWNWP;
      string pSRrdtufZa;
      string GGFiqfWSYG;
      string VlNwKoXpuA;
      string HJeHJrNkWO;
      string GjAhKWKeNy;
      string nEnPsDFUgo;
      string WEjYTwaxZy;
      if(cEWSHsxSow == FmwaLdXCWz){RkuKAkkelm = true;}
      else if(FmwaLdXCWz == cEWSHsxSow){qOWEWjLcgy = true;}
      if(fujOPXtTkM == LedAICQZJR){drcwLCVPOF = true;}
      else if(LedAICQZJR == fujOPXtTkM){NWpEYXxUkH = true;}
      if(ZbrKhRyZHZ == dPOFeKWNWP){msDhrBAaNN = true;}
      else if(dPOFeKWNWP == ZbrKhRyZHZ){nBJHmzfije = true;}
      if(zrCkFXLDXE == pSRrdtufZa){uMFPgDIdPH = true;}
      else if(pSRrdtufZa == zrCkFXLDXE){DAIdVJpIYC = true;}
      if(KWkLcykFSW == GGFiqfWSYG){SZisKdbmNR = true;}
      else if(GGFiqfWSYG == KWkLcykFSW){XADEtyDGqy = true;}
      if(UTiYCBLLjp == VlNwKoXpuA){aLiTLYgNSy = true;}
      else if(VlNwKoXpuA == UTiYCBLLjp){KnZsFpFORX = true;}
      if(tXKOxnsyJq == HJeHJrNkWO){kKRXrRlMPI = true;}
      else if(HJeHJrNkWO == tXKOxnsyJq){DbrBuNOMhO = true;}
      if(LpwfCCpfhi == GjAhKWKeNy){tqAGmMKKWN = true;}
      if(grHkFeJciD == nEnPsDFUgo){YNNwmjckDH = true;}
      if(LAThJlLWOo == WEjYTwaxZy){VtLQVHIKBs = true;}
      while(GjAhKWKeNy == LpwfCCpfhi){gouhjmxENn = true;}
      while(nEnPsDFUgo == nEnPsDFUgo){uYrkUPZOYf = true;}
      while(WEjYTwaxZy == WEjYTwaxZy){EbpBzuICJg = true;}
      if(RkuKAkkelm == true){RkuKAkkelm = false;}
      if(drcwLCVPOF == true){drcwLCVPOF = false;}
      if(msDhrBAaNN == true){msDhrBAaNN = false;}
      if(uMFPgDIdPH == true){uMFPgDIdPH = false;}
      if(SZisKdbmNR == true){SZisKdbmNR = false;}
      if(aLiTLYgNSy == true){aLiTLYgNSy = false;}
      if(kKRXrRlMPI == true){kKRXrRlMPI = false;}
      if(tqAGmMKKWN == true){tqAGmMKKWN = false;}
      if(YNNwmjckDH == true){YNNwmjckDH = false;}
      if(VtLQVHIKBs == true){VtLQVHIKBs = false;}
      if(qOWEWjLcgy == true){qOWEWjLcgy = false;}
      if(NWpEYXxUkH == true){NWpEYXxUkH = false;}
      if(nBJHmzfije == true){nBJHmzfije = false;}
      if(DAIdVJpIYC == true){DAIdVJpIYC = false;}
      if(XADEtyDGqy == true){XADEtyDGqy = false;}
      if(KnZsFpFORX == true){KnZsFpFORX = false;}
      if(DbrBuNOMhO == true){DbrBuNOMhO = false;}
      if(gouhjmxENn == true){gouhjmxENn = false;}
      if(uYrkUPZOYf == true){uYrkUPZOYf = false;}
      if(EbpBzuICJg == true){EbpBzuICJg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBDEMBLGWR
{ 
  void OdrSWpikFh()
  { 
      bool PaRdiSXAts = false;
      bool rkDuTGEXKE = false;
      bool tPJNfsLLzW = false;
      bool SbtbdMMgEa = false;
      bool UZCJAQUtSX = false;
      bool pPVzoAQEyp = false;
      bool HLAXaQpbRH = false;
      bool tXSiiTMAMP = false;
      bool XQragCFuld = false;
      bool uHiOTIZeij = false;
      bool ZscLdSwmPV = false;
      bool mQqiRqSZpX = false;
      bool KuomLlnEPZ = false;
      bool thRcodmgxO = false;
      bool GSePpdQAwc = false;
      bool pAnKZeDpzr = false;
      bool dqWobFzOsm = false;
      bool DlbbRqPYxg = false;
      bool UnIljtsGCJ = false;
      bool axgEjOuonk = false;
      string ytjfHaLPWZ;
      string ItLbuCzdmB;
      string PwWOmQxgrY;
      string uCsAgXXTXm;
      string hlTUJwtblO;
      string UtBmoBXUrp;
      string cdWxdFAKuX;
      string efFASdbBFp;
      string VVudEAAFLe;
      string zDbgJDOWqD;
      string uifOiooBTL;
      string ZWOBUHissd;
      string EtzQXbEXpO;
      string OEJBtlogtO;
      string LzlAEcnZMC;
      string UVdMzBjPpH;
      string kQLEwUMMHh;
      string SBydRFIyLt;
      string neLntraxCs;
      string CYpmdumgDj;
      if(ytjfHaLPWZ == uifOiooBTL){PaRdiSXAts = true;}
      else if(uifOiooBTL == ytjfHaLPWZ){ZscLdSwmPV = true;}
      if(ItLbuCzdmB == ZWOBUHissd){rkDuTGEXKE = true;}
      else if(ZWOBUHissd == ItLbuCzdmB){mQqiRqSZpX = true;}
      if(PwWOmQxgrY == EtzQXbEXpO){tPJNfsLLzW = true;}
      else if(EtzQXbEXpO == PwWOmQxgrY){KuomLlnEPZ = true;}
      if(uCsAgXXTXm == OEJBtlogtO){SbtbdMMgEa = true;}
      else if(OEJBtlogtO == uCsAgXXTXm){thRcodmgxO = true;}
      if(hlTUJwtblO == LzlAEcnZMC){UZCJAQUtSX = true;}
      else if(LzlAEcnZMC == hlTUJwtblO){GSePpdQAwc = true;}
      if(UtBmoBXUrp == UVdMzBjPpH){pPVzoAQEyp = true;}
      else if(UVdMzBjPpH == UtBmoBXUrp){pAnKZeDpzr = true;}
      if(cdWxdFAKuX == kQLEwUMMHh){HLAXaQpbRH = true;}
      else if(kQLEwUMMHh == cdWxdFAKuX){dqWobFzOsm = true;}
      if(efFASdbBFp == SBydRFIyLt){tXSiiTMAMP = true;}
      if(VVudEAAFLe == neLntraxCs){XQragCFuld = true;}
      if(zDbgJDOWqD == CYpmdumgDj){uHiOTIZeij = true;}
      while(SBydRFIyLt == efFASdbBFp){DlbbRqPYxg = true;}
      while(neLntraxCs == neLntraxCs){UnIljtsGCJ = true;}
      while(CYpmdumgDj == CYpmdumgDj){axgEjOuonk = true;}
      if(PaRdiSXAts == true){PaRdiSXAts = false;}
      if(rkDuTGEXKE == true){rkDuTGEXKE = false;}
      if(tPJNfsLLzW == true){tPJNfsLLzW = false;}
      if(SbtbdMMgEa == true){SbtbdMMgEa = false;}
      if(UZCJAQUtSX == true){UZCJAQUtSX = false;}
      if(pPVzoAQEyp == true){pPVzoAQEyp = false;}
      if(HLAXaQpbRH == true){HLAXaQpbRH = false;}
      if(tXSiiTMAMP == true){tXSiiTMAMP = false;}
      if(XQragCFuld == true){XQragCFuld = false;}
      if(uHiOTIZeij == true){uHiOTIZeij = false;}
      if(ZscLdSwmPV == true){ZscLdSwmPV = false;}
      if(mQqiRqSZpX == true){mQqiRqSZpX = false;}
      if(KuomLlnEPZ == true){KuomLlnEPZ = false;}
      if(thRcodmgxO == true){thRcodmgxO = false;}
      if(GSePpdQAwc == true){GSePpdQAwc = false;}
      if(pAnKZeDpzr == true){pAnKZeDpzr = false;}
      if(dqWobFzOsm == true){dqWobFzOsm = false;}
      if(DlbbRqPYxg == true){DlbbRqPYxg = false;}
      if(UnIljtsGCJ == true){UnIljtsGCJ = false;}
      if(axgEjOuonk == true){axgEjOuonk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGVWSTZUUL
{ 
  void duVuZrUEbp()
  { 
      bool bEQcBoDsCj = false;
      bool wRxJzhoYwp = false;
      bool CrHUesoPqn = false;
      bool YmbQLzuUVV = false;
      bool PciYcqENCw = false;
      bool wHrzxjxwxH = false;
      bool zmCOKIpfxz = false;
      bool mUDaaZIhqn = false;
      bool obNuqRucTa = false;
      bool CyWNVbZUOT = false;
      bool AYPCIbDRXW = false;
      bool bOEJSXZHWs = false;
      bool NNMWxnyoEy = false;
      bool AmTXmQLKmP = false;
      bool NcEwzmtMux = false;
      bool BSxUGmLsFT = false;
      bool cNMYWougVB = false;
      bool MPUHejIQWJ = false;
      bool tksHxgoyQA = false;
      bool ERFSlzQfYK = false;
      string whNUgUobLS;
      string LaoNdlKmLb;
      string eowYhGrwWb;
      string qjkbpkamYj;
      string dysEAmMZjn;
      string mPqSeGkolZ;
      string bsFiabpNXs;
      string LWNbygwrXu;
      string sRLhoarRxi;
      string zlByHjrJcY;
      string xzCqcPBPUx;
      string KsQqgKhWtz;
      string iYQotZVOTN;
      string nlOzxsOUFY;
      string ZcwzYGVJRx;
      string CVPcpYiNxD;
      string tmwHJYdQsn;
      string uMRVZFbQQm;
      string DLxWKSVlJY;
      string JBWBdlgooz;
      if(whNUgUobLS == xzCqcPBPUx){bEQcBoDsCj = true;}
      else if(xzCqcPBPUx == whNUgUobLS){AYPCIbDRXW = true;}
      if(LaoNdlKmLb == KsQqgKhWtz){wRxJzhoYwp = true;}
      else if(KsQqgKhWtz == LaoNdlKmLb){bOEJSXZHWs = true;}
      if(eowYhGrwWb == iYQotZVOTN){CrHUesoPqn = true;}
      else if(iYQotZVOTN == eowYhGrwWb){NNMWxnyoEy = true;}
      if(qjkbpkamYj == nlOzxsOUFY){YmbQLzuUVV = true;}
      else if(nlOzxsOUFY == qjkbpkamYj){AmTXmQLKmP = true;}
      if(dysEAmMZjn == ZcwzYGVJRx){PciYcqENCw = true;}
      else if(ZcwzYGVJRx == dysEAmMZjn){NcEwzmtMux = true;}
      if(mPqSeGkolZ == CVPcpYiNxD){wHrzxjxwxH = true;}
      else if(CVPcpYiNxD == mPqSeGkolZ){BSxUGmLsFT = true;}
      if(bsFiabpNXs == tmwHJYdQsn){zmCOKIpfxz = true;}
      else if(tmwHJYdQsn == bsFiabpNXs){cNMYWougVB = true;}
      if(LWNbygwrXu == uMRVZFbQQm){mUDaaZIhqn = true;}
      if(sRLhoarRxi == DLxWKSVlJY){obNuqRucTa = true;}
      if(zlByHjrJcY == JBWBdlgooz){CyWNVbZUOT = true;}
      while(uMRVZFbQQm == LWNbygwrXu){MPUHejIQWJ = true;}
      while(DLxWKSVlJY == DLxWKSVlJY){tksHxgoyQA = true;}
      while(JBWBdlgooz == JBWBdlgooz){ERFSlzQfYK = true;}
      if(bEQcBoDsCj == true){bEQcBoDsCj = false;}
      if(wRxJzhoYwp == true){wRxJzhoYwp = false;}
      if(CrHUesoPqn == true){CrHUesoPqn = false;}
      if(YmbQLzuUVV == true){YmbQLzuUVV = false;}
      if(PciYcqENCw == true){PciYcqENCw = false;}
      if(wHrzxjxwxH == true){wHrzxjxwxH = false;}
      if(zmCOKIpfxz == true){zmCOKIpfxz = false;}
      if(mUDaaZIhqn == true){mUDaaZIhqn = false;}
      if(obNuqRucTa == true){obNuqRucTa = false;}
      if(CyWNVbZUOT == true){CyWNVbZUOT = false;}
      if(AYPCIbDRXW == true){AYPCIbDRXW = false;}
      if(bOEJSXZHWs == true){bOEJSXZHWs = false;}
      if(NNMWxnyoEy == true){NNMWxnyoEy = false;}
      if(AmTXmQLKmP == true){AmTXmQLKmP = false;}
      if(NcEwzmtMux == true){NcEwzmtMux = false;}
      if(BSxUGmLsFT == true){BSxUGmLsFT = false;}
      if(cNMYWougVB == true){cNMYWougVB = false;}
      if(MPUHejIQWJ == true){MPUHejIQWJ = false;}
      if(tksHxgoyQA == true){tksHxgoyQA = false;}
      if(ERFSlzQfYK == true){ERFSlzQfYK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPNCZHCZOH
{ 
  void nWSHEGmMkt()
  { 
      bool sFBiaGoOWU = false;
      bool kErVJcYytb = false;
      bool cJfQTJefID = false;
      bool YQhDqeFKrm = false;
      bool lcJfXSbUFA = false;
      bool ULMAYiZjOQ = false;
      bool aIGSuUWode = false;
      bool WNGGozzAsB = false;
      bool hKaHiNDgeH = false;
      bool EVwaLdWqjC = false;
      bool wlpacGFGLY = false;
      bool jYpMiQgyjh = false;
      bool RoKWZBRetL = false;
      bool bIQqFwUAeb = false;
      bool IxVFWfeiru = false;
      bool wYGCjGbSBa = false;
      bool oZLzxaIzHm = false;
      bool wgTIZUSEzs = false;
      bool WhmzODCNGy = false;
      bool UBzDlhkVIw = false;
      string aAdfSNiUjg;
      string RCwwAjLMQy;
      string QWZTsqZtqE;
      string TleJmDkHio;
      string hRerwzuiXQ;
      string WRRZNDZKmb;
      string mndfMfXmJx;
      string yDcaPzqhWt;
      string uqWZgCTEui;
      string caUHBtmzfQ;
      string bHYZRSoqJO;
      string MrmrfwRDzK;
      string LSqaUXiVYV;
      string LrBFSnRwIN;
      string MbufVjmbaF;
      string bjzUEJPxFs;
      string jSRnDUpgZr;
      string dVukxjXLEj;
      string jHtTtargBJ;
      string XUpOcsKGcB;
      if(aAdfSNiUjg == bHYZRSoqJO){sFBiaGoOWU = true;}
      else if(bHYZRSoqJO == aAdfSNiUjg){wlpacGFGLY = true;}
      if(RCwwAjLMQy == MrmrfwRDzK){kErVJcYytb = true;}
      else if(MrmrfwRDzK == RCwwAjLMQy){jYpMiQgyjh = true;}
      if(QWZTsqZtqE == LSqaUXiVYV){cJfQTJefID = true;}
      else if(LSqaUXiVYV == QWZTsqZtqE){RoKWZBRetL = true;}
      if(TleJmDkHio == LrBFSnRwIN){YQhDqeFKrm = true;}
      else if(LrBFSnRwIN == TleJmDkHio){bIQqFwUAeb = true;}
      if(hRerwzuiXQ == MbufVjmbaF){lcJfXSbUFA = true;}
      else if(MbufVjmbaF == hRerwzuiXQ){IxVFWfeiru = true;}
      if(WRRZNDZKmb == bjzUEJPxFs){ULMAYiZjOQ = true;}
      else if(bjzUEJPxFs == WRRZNDZKmb){wYGCjGbSBa = true;}
      if(mndfMfXmJx == jSRnDUpgZr){aIGSuUWode = true;}
      else if(jSRnDUpgZr == mndfMfXmJx){oZLzxaIzHm = true;}
      if(yDcaPzqhWt == dVukxjXLEj){WNGGozzAsB = true;}
      if(uqWZgCTEui == jHtTtargBJ){hKaHiNDgeH = true;}
      if(caUHBtmzfQ == XUpOcsKGcB){EVwaLdWqjC = true;}
      while(dVukxjXLEj == yDcaPzqhWt){wgTIZUSEzs = true;}
      while(jHtTtargBJ == jHtTtargBJ){WhmzODCNGy = true;}
      while(XUpOcsKGcB == XUpOcsKGcB){UBzDlhkVIw = true;}
      if(sFBiaGoOWU == true){sFBiaGoOWU = false;}
      if(kErVJcYytb == true){kErVJcYytb = false;}
      if(cJfQTJefID == true){cJfQTJefID = false;}
      if(YQhDqeFKrm == true){YQhDqeFKrm = false;}
      if(lcJfXSbUFA == true){lcJfXSbUFA = false;}
      if(ULMAYiZjOQ == true){ULMAYiZjOQ = false;}
      if(aIGSuUWode == true){aIGSuUWode = false;}
      if(WNGGozzAsB == true){WNGGozzAsB = false;}
      if(hKaHiNDgeH == true){hKaHiNDgeH = false;}
      if(EVwaLdWqjC == true){EVwaLdWqjC = false;}
      if(wlpacGFGLY == true){wlpacGFGLY = false;}
      if(jYpMiQgyjh == true){jYpMiQgyjh = false;}
      if(RoKWZBRetL == true){RoKWZBRetL = false;}
      if(bIQqFwUAeb == true){bIQqFwUAeb = false;}
      if(IxVFWfeiru == true){IxVFWfeiru = false;}
      if(wYGCjGbSBa == true){wYGCjGbSBa = false;}
      if(oZLzxaIzHm == true){oZLzxaIzHm = false;}
      if(wgTIZUSEzs == true){wgTIZUSEzs = false;}
      if(WhmzODCNGy == true){WhmzODCNGy = false;}
      if(UBzDlhkVIw == true){UBzDlhkVIw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGRVQBVBHF
{ 
  void rfjozjJpOS()
  { 
      bool eFkVsDfTMY = false;
      bool gGzENKrxmu = false;
      bool udFPMOgFSs = false;
      bool YXQRlzjeMY = false;
      bool EgrCELByap = false;
      bool UkMwxBzUJe = false;
      bool VZBSAJpgSN = false;
      bool aMkOpOkDLA = false;
      bool MidbYmLTUj = false;
      bool APUhCdeYBt = false;
      bool VTfNPHAyFh = false;
      bool PwIIRlwZtN = false;
      bool yVMhNLrDLM = false;
      bool jMBQerDQLQ = false;
      bool mMNlUDGLPP = false;
      bool hFenwzHxzE = false;
      bool PwlsyDtrdY = false;
      bool ieNcZkHaNJ = false;
      bool FfmudegMTe = false;
      bool kFRHBpaUnR = false;
      string FCjwPGzbTd;
      string eTsRWWCWlk;
      string qpuLPXITDy;
      string OdkwpZBNFj;
      string aCLsccslwh;
      string cMVpgPHYfq;
      string yeXVOBiwaw;
      string VoQBKodBil;
      string eVWUUCHtPa;
      string ScgNkudoea;
      string twKzMmwTeq;
      string kFotMbHDBM;
      string tngAdsHCQP;
      string LoWHrhLXIg;
      string FmPXoNmmBJ;
      string manSfFPKUT;
      string fsDPfwhgCe;
      string PjtTGHXIKQ;
      string FUBGbjAEbl;
      string SBCoBMiArs;
      if(FCjwPGzbTd == twKzMmwTeq){eFkVsDfTMY = true;}
      else if(twKzMmwTeq == FCjwPGzbTd){VTfNPHAyFh = true;}
      if(eTsRWWCWlk == kFotMbHDBM){gGzENKrxmu = true;}
      else if(kFotMbHDBM == eTsRWWCWlk){PwIIRlwZtN = true;}
      if(qpuLPXITDy == tngAdsHCQP){udFPMOgFSs = true;}
      else if(tngAdsHCQP == qpuLPXITDy){yVMhNLrDLM = true;}
      if(OdkwpZBNFj == LoWHrhLXIg){YXQRlzjeMY = true;}
      else if(LoWHrhLXIg == OdkwpZBNFj){jMBQerDQLQ = true;}
      if(aCLsccslwh == FmPXoNmmBJ){EgrCELByap = true;}
      else if(FmPXoNmmBJ == aCLsccslwh){mMNlUDGLPP = true;}
      if(cMVpgPHYfq == manSfFPKUT){UkMwxBzUJe = true;}
      else if(manSfFPKUT == cMVpgPHYfq){hFenwzHxzE = true;}
      if(yeXVOBiwaw == fsDPfwhgCe){VZBSAJpgSN = true;}
      else if(fsDPfwhgCe == yeXVOBiwaw){PwlsyDtrdY = true;}
      if(VoQBKodBil == PjtTGHXIKQ){aMkOpOkDLA = true;}
      if(eVWUUCHtPa == FUBGbjAEbl){MidbYmLTUj = true;}
      if(ScgNkudoea == SBCoBMiArs){APUhCdeYBt = true;}
      while(PjtTGHXIKQ == VoQBKodBil){ieNcZkHaNJ = true;}
      while(FUBGbjAEbl == FUBGbjAEbl){FfmudegMTe = true;}
      while(SBCoBMiArs == SBCoBMiArs){kFRHBpaUnR = true;}
      if(eFkVsDfTMY == true){eFkVsDfTMY = false;}
      if(gGzENKrxmu == true){gGzENKrxmu = false;}
      if(udFPMOgFSs == true){udFPMOgFSs = false;}
      if(YXQRlzjeMY == true){YXQRlzjeMY = false;}
      if(EgrCELByap == true){EgrCELByap = false;}
      if(UkMwxBzUJe == true){UkMwxBzUJe = false;}
      if(VZBSAJpgSN == true){VZBSAJpgSN = false;}
      if(aMkOpOkDLA == true){aMkOpOkDLA = false;}
      if(MidbYmLTUj == true){MidbYmLTUj = false;}
      if(APUhCdeYBt == true){APUhCdeYBt = false;}
      if(VTfNPHAyFh == true){VTfNPHAyFh = false;}
      if(PwIIRlwZtN == true){PwIIRlwZtN = false;}
      if(yVMhNLrDLM == true){yVMhNLrDLM = false;}
      if(jMBQerDQLQ == true){jMBQerDQLQ = false;}
      if(mMNlUDGLPP == true){mMNlUDGLPP = false;}
      if(hFenwzHxzE == true){hFenwzHxzE = false;}
      if(PwlsyDtrdY == true){PwlsyDtrdY = false;}
      if(ieNcZkHaNJ == true){ieNcZkHaNJ = false;}
      if(FfmudegMTe == true){FfmudegMTe = false;}
      if(kFRHBpaUnR == true){kFRHBpaUnR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AWCTNVGPLD
{ 
  void sJBMqrsrnd()
  { 
      bool HqWslxoCYH = false;
      bool dBtVgyELta = false;
      bool IQHeIqYIkd = false;
      bool FlmLBWzWbr = false;
      bool aeeKPZpjSt = false;
      bool itXAyqiqkt = false;
      bool YgQuCrOiTK = false;
      bool yhjBAdkwOi = false;
      bool BooquKOlNK = false;
      bool mHlgTsOjIX = false;
      bool LHPIuAKWAU = false;
      bool FmbBsjrYzr = false;
      bool dbUJXqwCgG = false;
      bool PBnqWsYgwt = false;
      bool zqlrFzejnj = false;
      bool BojQtilFkD = false;
      bool EHosEDykeA = false;
      bool KKcFrlpcDX = false;
      bool MLOwFaQXxn = false;
      bool GTwroqBrnB = false;
      string dIzzDoXToh;
      string naxEIooQWS;
      string nscpZoeEwB;
      string jJNrlZjYSB;
      string KYKPqEByAc;
      string CMYJUkeJYN;
      string JTWnxdMESh;
      string EQyUIPhNyV;
      string mfDTyXkEXA;
      string uazErqBVRM;
      string rwfSYlODBF;
      string CRKDacPDpZ;
      string sHgRmdRscQ;
      string NMukdpAkuM;
      string IgCSxcPucO;
      string ayfqTjPOet;
      string TUZjqpVYYj;
      string cdIdRLFOTJ;
      string NVPNpPgERt;
      string akFArmGSbH;
      if(dIzzDoXToh == rwfSYlODBF){HqWslxoCYH = true;}
      else if(rwfSYlODBF == dIzzDoXToh){LHPIuAKWAU = true;}
      if(naxEIooQWS == CRKDacPDpZ){dBtVgyELta = true;}
      else if(CRKDacPDpZ == naxEIooQWS){FmbBsjrYzr = true;}
      if(nscpZoeEwB == sHgRmdRscQ){IQHeIqYIkd = true;}
      else if(sHgRmdRscQ == nscpZoeEwB){dbUJXqwCgG = true;}
      if(jJNrlZjYSB == NMukdpAkuM){FlmLBWzWbr = true;}
      else if(NMukdpAkuM == jJNrlZjYSB){PBnqWsYgwt = true;}
      if(KYKPqEByAc == IgCSxcPucO){aeeKPZpjSt = true;}
      else if(IgCSxcPucO == KYKPqEByAc){zqlrFzejnj = true;}
      if(CMYJUkeJYN == ayfqTjPOet){itXAyqiqkt = true;}
      else if(ayfqTjPOet == CMYJUkeJYN){BojQtilFkD = true;}
      if(JTWnxdMESh == TUZjqpVYYj){YgQuCrOiTK = true;}
      else if(TUZjqpVYYj == JTWnxdMESh){EHosEDykeA = true;}
      if(EQyUIPhNyV == cdIdRLFOTJ){yhjBAdkwOi = true;}
      if(mfDTyXkEXA == NVPNpPgERt){BooquKOlNK = true;}
      if(uazErqBVRM == akFArmGSbH){mHlgTsOjIX = true;}
      while(cdIdRLFOTJ == EQyUIPhNyV){KKcFrlpcDX = true;}
      while(NVPNpPgERt == NVPNpPgERt){MLOwFaQXxn = true;}
      while(akFArmGSbH == akFArmGSbH){GTwroqBrnB = true;}
      if(HqWslxoCYH == true){HqWslxoCYH = false;}
      if(dBtVgyELta == true){dBtVgyELta = false;}
      if(IQHeIqYIkd == true){IQHeIqYIkd = false;}
      if(FlmLBWzWbr == true){FlmLBWzWbr = false;}
      if(aeeKPZpjSt == true){aeeKPZpjSt = false;}
      if(itXAyqiqkt == true){itXAyqiqkt = false;}
      if(YgQuCrOiTK == true){YgQuCrOiTK = false;}
      if(yhjBAdkwOi == true){yhjBAdkwOi = false;}
      if(BooquKOlNK == true){BooquKOlNK = false;}
      if(mHlgTsOjIX == true){mHlgTsOjIX = false;}
      if(LHPIuAKWAU == true){LHPIuAKWAU = false;}
      if(FmbBsjrYzr == true){FmbBsjrYzr = false;}
      if(dbUJXqwCgG == true){dbUJXqwCgG = false;}
      if(PBnqWsYgwt == true){PBnqWsYgwt = false;}
      if(zqlrFzejnj == true){zqlrFzejnj = false;}
      if(BojQtilFkD == true){BojQtilFkD = false;}
      if(EHosEDykeA == true){EHosEDykeA = false;}
      if(KKcFrlpcDX == true){KKcFrlpcDX = false;}
      if(MLOwFaQXxn == true){MLOwFaQXxn = false;}
      if(GTwroqBrnB == true){GTwroqBrnB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHFLUQBJOQ
{ 
  void icoybyczdk()
  { 
      bool KIXjLFojdh = false;
      bool sTDiXceLiD = false;
      bool YCUKsCOagi = false;
      bool BWshrwuGlS = false;
      bool PkeCYHrxYA = false;
      bool ZQpEWInMpI = false;
      bool pODtfVaUqb = false;
      bool gXZPnmWRlk = false;
      bool KRCgIkgoKj = false;
      bool IhPcbAhjWC = false;
      bool gWFxSCqZPj = false;
      bool kVaFxYMWlt = false;
      bool okKHSzHwnm = false;
      bool FltiEnLENG = false;
      bool tHYaylHKeC = false;
      bool nLybNuLyeT = false;
      bool ttkcezarAJ = false;
      bool NHJeAgMiJf = false;
      bool rwQlytnSUJ = false;
      bool bMZsLAVwwy = false;
      string DfubxBTgZg;
      string cURegcmycz;
      string TwoTXqyZHC;
      string bKgEIzrlel;
      string JmBjuCDWti;
      string PkHVJGqaDG;
      string CtYWESmNVh;
      string kATqoguFYV;
      string mbeYmqCLtB;
      string IQhXiPNdeb;
      string PoALyOQQfc;
      string LlChSZOziN;
      string PaTTZTSuHY;
      string TQZwFybSaY;
      string ZleRpVOzEJ;
      string BNuQLnVgld;
      string uUJGJtLFbU;
      string yuYKmduBdD;
      string FSpxXFVIkR;
      string bufxcEbYIu;
      if(DfubxBTgZg == PoALyOQQfc){KIXjLFojdh = true;}
      else if(PoALyOQQfc == DfubxBTgZg){gWFxSCqZPj = true;}
      if(cURegcmycz == LlChSZOziN){sTDiXceLiD = true;}
      else if(LlChSZOziN == cURegcmycz){kVaFxYMWlt = true;}
      if(TwoTXqyZHC == PaTTZTSuHY){YCUKsCOagi = true;}
      else if(PaTTZTSuHY == TwoTXqyZHC){okKHSzHwnm = true;}
      if(bKgEIzrlel == TQZwFybSaY){BWshrwuGlS = true;}
      else if(TQZwFybSaY == bKgEIzrlel){FltiEnLENG = true;}
      if(JmBjuCDWti == ZleRpVOzEJ){PkeCYHrxYA = true;}
      else if(ZleRpVOzEJ == JmBjuCDWti){tHYaylHKeC = true;}
      if(PkHVJGqaDG == BNuQLnVgld){ZQpEWInMpI = true;}
      else if(BNuQLnVgld == PkHVJGqaDG){nLybNuLyeT = true;}
      if(CtYWESmNVh == uUJGJtLFbU){pODtfVaUqb = true;}
      else if(uUJGJtLFbU == CtYWESmNVh){ttkcezarAJ = true;}
      if(kATqoguFYV == yuYKmduBdD){gXZPnmWRlk = true;}
      if(mbeYmqCLtB == FSpxXFVIkR){KRCgIkgoKj = true;}
      if(IQhXiPNdeb == bufxcEbYIu){IhPcbAhjWC = true;}
      while(yuYKmduBdD == kATqoguFYV){NHJeAgMiJf = true;}
      while(FSpxXFVIkR == FSpxXFVIkR){rwQlytnSUJ = true;}
      while(bufxcEbYIu == bufxcEbYIu){bMZsLAVwwy = true;}
      if(KIXjLFojdh == true){KIXjLFojdh = false;}
      if(sTDiXceLiD == true){sTDiXceLiD = false;}
      if(YCUKsCOagi == true){YCUKsCOagi = false;}
      if(BWshrwuGlS == true){BWshrwuGlS = false;}
      if(PkeCYHrxYA == true){PkeCYHrxYA = false;}
      if(ZQpEWInMpI == true){ZQpEWInMpI = false;}
      if(pODtfVaUqb == true){pODtfVaUqb = false;}
      if(gXZPnmWRlk == true){gXZPnmWRlk = false;}
      if(KRCgIkgoKj == true){KRCgIkgoKj = false;}
      if(IhPcbAhjWC == true){IhPcbAhjWC = false;}
      if(gWFxSCqZPj == true){gWFxSCqZPj = false;}
      if(kVaFxYMWlt == true){kVaFxYMWlt = false;}
      if(okKHSzHwnm == true){okKHSzHwnm = false;}
      if(FltiEnLENG == true){FltiEnLENG = false;}
      if(tHYaylHKeC == true){tHYaylHKeC = false;}
      if(nLybNuLyeT == true){nLybNuLyeT = false;}
      if(ttkcezarAJ == true){ttkcezarAJ = false;}
      if(NHJeAgMiJf == true){NHJeAgMiJf = false;}
      if(rwQlytnSUJ == true){rwQlytnSUJ = false;}
      if(bMZsLAVwwy == true){bMZsLAVwwy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTWUHOJSZX
{ 
  void LjrPQzCKuJ()
  { 
      bool arXJaLsnsh = false;
      bool lfYXYKdPEC = false;
      bool cEBklpNTLq = false;
      bool wFeQtBtZkh = false;
      bool uQuPiTqXGd = false;
      bool IfgNXVpmWk = false;
      bool yZbBlgAIdX = false;
      bool QDeWGMJlCS = false;
      bool yoNgiPXRrX = false;
      bool KGCziVnscB = false;
      bool SithNEBKGL = false;
      bool MEjEmIMtSV = false;
      bool JiPGMJBfmj = false;
      bool XPIBzOueTd = false;
      bool ONKgKGWxMa = false;
      bool JtaHqjTnVE = false;
      bool DUWVmxuiEX = false;
      bool MgaoHwXiuF = false;
      bool mDSMadoBJP = false;
      bool uHJPaspnsN = false;
      string BxTEtUrMOn;
      string VWYAGPgKDX;
      string RXfaqaFVLB;
      string TItjnpLyZL;
      string orVUGiUEyI;
      string IcNwAdQsNS;
      string OVBMUNbnLP;
      string DhkqhZCLTH;
      string GAXDsquyjK;
      string ZRkGwTqIAs;
      string HfriEZqWNa;
      string aFZGLOyyTc;
      string RcEBplxdtO;
      string isLZzaHoyS;
      string zYkIiUreuh;
      string UsoWbdaqsS;
      string cMbyrhsAGk;
      string GJzBdsquRU;
      string sSiLsoEnyU;
      string zQufolwlQB;
      if(BxTEtUrMOn == HfriEZqWNa){arXJaLsnsh = true;}
      else if(HfriEZqWNa == BxTEtUrMOn){SithNEBKGL = true;}
      if(VWYAGPgKDX == aFZGLOyyTc){lfYXYKdPEC = true;}
      else if(aFZGLOyyTc == VWYAGPgKDX){MEjEmIMtSV = true;}
      if(RXfaqaFVLB == RcEBplxdtO){cEBklpNTLq = true;}
      else if(RcEBplxdtO == RXfaqaFVLB){JiPGMJBfmj = true;}
      if(TItjnpLyZL == isLZzaHoyS){wFeQtBtZkh = true;}
      else if(isLZzaHoyS == TItjnpLyZL){XPIBzOueTd = true;}
      if(orVUGiUEyI == zYkIiUreuh){uQuPiTqXGd = true;}
      else if(zYkIiUreuh == orVUGiUEyI){ONKgKGWxMa = true;}
      if(IcNwAdQsNS == UsoWbdaqsS){IfgNXVpmWk = true;}
      else if(UsoWbdaqsS == IcNwAdQsNS){JtaHqjTnVE = true;}
      if(OVBMUNbnLP == cMbyrhsAGk){yZbBlgAIdX = true;}
      else if(cMbyrhsAGk == OVBMUNbnLP){DUWVmxuiEX = true;}
      if(DhkqhZCLTH == GJzBdsquRU){QDeWGMJlCS = true;}
      if(GAXDsquyjK == sSiLsoEnyU){yoNgiPXRrX = true;}
      if(ZRkGwTqIAs == zQufolwlQB){KGCziVnscB = true;}
      while(GJzBdsquRU == DhkqhZCLTH){MgaoHwXiuF = true;}
      while(sSiLsoEnyU == sSiLsoEnyU){mDSMadoBJP = true;}
      while(zQufolwlQB == zQufolwlQB){uHJPaspnsN = true;}
      if(arXJaLsnsh == true){arXJaLsnsh = false;}
      if(lfYXYKdPEC == true){lfYXYKdPEC = false;}
      if(cEBklpNTLq == true){cEBklpNTLq = false;}
      if(wFeQtBtZkh == true){wFeQtBtZkh = false;}
      if(uQuPiTqXGd == true){uQuPiTqXGd = false;}
      if(IfgNXVpmWk == true){IfgNXVpmWk = false;}
      if(yZbBlgAIdX == true){yZbBlgAIdX = false;}
      if(QDeWGMJlCS == true){QDeWGMJlCS = false;}
      if(yoNgiPXRrX == true){yoNgiPXRrX = false;}
      if(KGCziVnscB == true){KGCziVnscB = false;}
      if(SithNEBKGL == true){SithNEBKGL = false;}
      if(MEjEmIMtSV == true){MEjEmIMtSV = false;}
      if(JiPGMJBfmj == true){JiPGMJBfmj = false;}
      if(XPIBzOueTd == true){XPIBzOueTd = false;}
      if(ONKgKGWxMa == true){ONKgKGWxMa = false;}
      if(JtaHqjTnVE == true){JtaHqjTnVE = false;}
      if(DUWVmxuiEX == true){DUWVmxuiEX = false;}
      if(MgaoHwXiuF == true){MgaoHwXiuF = false;}
      if(mDSMadoBJP == true){mDSMadoBJP = false;}
      if(uHJPaspnsN == true){uHJPaspnsN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQZUQJYUFV
{ 
  void pgGqxnkoFf()
  { 
      bool DPNQXIkDgR = false;
      bool mdlZpysWeE = false;
      bool fKcTxkImIP = false;
      bool hdYwdToVtQ = false;
      bool KpXOJQKohX = false;
      bool mGLsWrmtSl = false;
      bool zytRiJFpuV = false;
      bool IXbOsomNJg = false;
      bool ZTEjbaSeZk = false;
      bool guCHRMwFeA = false;
      bool KUsMOOdwzg = false;
      bool EYklLesJoI = false;
      bool pZQJnNVUxg = false;
      bool shhIVEZrUM = false;
      bool wVfrgIJPul = false;
      bool TlQWKkEiXB = false;
      bool sJzRmWpbQG = false;
      bool EAnbLTtXcf = false;
      bool DFYKMHQKyk = false;
      bool AqUTSmWNEJ = false;
      string wbVgQwaRzQ;
      string yPOSDhsEoc;
      string KYIibHdDVi;
      string QoswGkeHIr;
      string xFGmQuocZl;
      string XZKnAXTlEI;
      string SXuQAIVRMS;
      string ClwxeESURf;
      string SAdiLpeEui;
      string RsCzYZJomH;
      string ZWQHjkcMJw;
      string EyTXoSsLFJ;
      string dQVdAJiwXE;
      string tdhKGwjVzZ;
      string MRuzdTYeJG;
      string fyicdIAlGa;
      string CfnEBaPJQs;
      string iXMfwLVWzg;
      string jDmRYwtEgx;
      string uxOYWgdqyD;
      if(wbVgQwaRzQ == ZWQHjkcMJw){DPNQXIkDgR = true;}
      else if(ZWQHjkcMJw == wbVgQwaRzQ){KUsMOOdwzg = true;}
      if(yPOSDhsEoc == EyTXoSsLFJ){mdlZpysWeE = true;}
      else if(EyTXoSsLFJ == yPOSDhsEoc){EYklLesJoI = true;}
      if(KYIibHdDVi == dQVdAJiwXE){fKcTxkImIP = true;}
      else if(dQVdAJiwXE == KYIibHdDVi){pZQJnNVUxg = true;}
      if(QoswGkeHIr == tdhKGwjVzZ){hdYwdToVtQ = true;}
      else if(tdhKGwjVzZ == QoswGkeHIr){shhIVEZrUM = true;}
      if(xFGmQuocZl == MRuzdTYeJG){KpXOJQKohX = true;}
      else if(MRuzdTYeJG == xFGmQuocZl){wVfrgIJPul = true;}
      if(XZKnAXTlEI == fyicdIAlGa){mGLsWrmtSl = true;}
      else if(fyicdIAlGa == XZKnAXTlEI){TlQWKkEiXB = true;}
      if(SXuQAIVRMS == CfnEBaPJQs){zytRiJFpuV = true;}
      else if(CfnEBaPJQs == SXuQAIVRMS){sJzRmWpbQG = true;}
      if(ClwxeESURf == iXMfwLVWzg){IXbOsomNJg = true;}
      if(SAdiLpeEui == jDmRYwtEgx){ZTEjbaSeZk = true;}
      if(RsCzYZJomH == uxOYWgdqyD){guCHRMwFeA = true;}
      while(iXMfwLVWzg == ClwxeESURf){EAnbLTtXcf = true;}
      while(jDmRYwtEgx == jDmRYwtEgx){DFYKMHQKyk = true;}
      while(uxOYWgdqyD == uxOYWgdqyD){AqUTSmWNEJ = true;}
      if(DPNQXIkDgR == true){DPNQXIkDgR = false;}
      if(mdlZpysWeE == true){mdlZpysWeE = false;}
      if(fKcTxkImIP == true){fKcTxkImIP = false;}
      if(hdYwdToVtQ == true){hdYwdToVtQ = false;}
      if(KpXOJQKohX == true){KpXOJQKohX = false;}
      if(mGLsWrmtSl == true){mGLsWrmtSl = false;}
      if(zytRiJFpuV == true){zytRiJFpuV = false;}
      if(IXbOsomNJg == true){IXbOsomNJg = false;}
      if(ZTEjbaSeZk == true){ZTEjbaSeZk = false;}
      if(guCHRMwFeA == true){guCHRMwFeA = false;}
      if(KUsMOOdwzg == true){KUsMOOdwzg = false;}
      if(EYklLesJoI == true){EYklLesJoI = false;}
      if(pZQJnNVUxg == true){pZQJnNVUxg = false;}
      if(shhIVEZrUM == true){shhIVEZrUM = false;}
      if(wVfrgIJPul == true){wVfrgIJPul = false;}
      if(TlQWKkEiXB == true){TlQWKkEiXB = false;}
      if(sJzRmWpbQG == true){sJzRmWpbQG = false;}
      if(EAnbLTtXcf == true){EAnbLTtXcf = false;}
      if(DFYKMHQKyk == true){DFYKMHQKyk = false;}
      if(AqUTSmWNEJ == true){AqUTSmWNEJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOVILJUILV
{ 
  void pMSrcrZWcG()
  { 
      bool CTEcdlFAnQ = false;
      bool dNOJhmWHll = false;
      bool YpLCCxMdbZ = false;
      bool tfoVnBTJNb = false;
      bool zdHdxejWfe = false;
      bool jfdtALHCZf = false;
      bool YaXNVxXsUg = false;
      bool SNtKluihFW = false;
      bool NoywpOBuVc = false;
      bool sRigCYGsHz = false;
      bool GqCzLWlTHF = false;
      bool cYxDSjcaXG = false;
      bool ucXrmBeMHN = false;
      bool noZFPWmykS = false;
      bool chnQzUUeNS = false;
      bool weUBDdTKLK = false;
      bool rYLsQmyqmw = false;
      bool wdpEdNnGrS = false;
      bool gzzoQJUYBk = false;
      bool CcmZaDVtzM = false;
      string IbQOfNBGzp;
      string wRqQCDxgim;
      string wimFwAMOfe;
      string IWxchfjeai;
      string pjnCsHsSCQ;
      string jYRoIYnLSe;
      string AlZUhYUOhW;
      string TRFAwMtkMn;
      string HtMPujEITI;
      string qYMuhEJTTT;
      string mdjfxRSRru;
      string eDydXGZKYy;
      string UMtZetFJSr;
      string DZQrBcJgRd;
      string QlPYdnZhXa;
      string eyuVyZjKAC;
      string LJzzrElGcu;
      string xrsthhwVuq;
      string UXlqNFeuta;
      string szfOSHmPfZ;
      if(IbQOfNBGzp == mdjfxRSRru){CTEcdlFAnQ = true;}
      else if(mdjfxRSRru == IbQOfNBGzp){GqCzLWlTHF = true;}
      if(wRqQCDxgim == eDydXGZKYy){dNOJhmWHll = true;}
      else if(eDydXGZKYy == wRqQCDxgim){cYxDSjcaXG = true;}
      if(wimFwAMOfe == UMtZetFJSr){YpLCCxMdbZ = true;}
      else if(UMtZetFJSr == wimFwAMOfe){ucXrmBeMHN = true;}
      if(IWxchfjeai == DZQrBcJgRd){tfoVnBTJNb = true;}
      else if(DZQrBcJgRd == IWxchfjeai){noZFPWmykS = true;}
      if(pjnCsHsSCQ == QlPYdnZhXa){zdHdxejWfe = true;}
      else if(QlPYdnZhXa == pjnCsHsSCQ){chnQzUUeNS = true;}
      if(jYRoIYnLSe == eyuVyZjKAC){jfdtALHCZf = true;}
      else if(eyuVyZjKAC == jYRoIYnLSe){weUBDdTKLK = true;}
      if(AlZUhYUOhW == LJzzrElGcu){YaXNVxXsUg = true;}
      else if(LJzzrElGcu == AlZUhYUOhW){rYLsQmyqmw = true;}
      if(TRFAwMtkMn == xrsthhwVuq){SNtKluihFW = true;}
      if(HtMPujEITI == UXlqNFeuta){NoywpOBuVc = true;}
      if(qYMuhEJTTT == szfOSHmPfZ){sRigCYGsHz = true;}
      while(xrsthhwVuq == TRFAwMtkMn){wdpEdNnGrS = true;}
      while(UXlqNFeuta == UXlqNFeuta){gzzoQJUYBk = true;}
      while(szfOSHmPfZ == szfOSHmPfZ){CcmZaDVtzM = true;}
      if(CTEcdlFAnQ == true){CTEcdlFAnQ = false;}
      if(dNOJhmWHll == true){dNOJhmWHll = false;}
      if(YpLCCxMdbZ == true){YpLCCxMdbZ = false;}
      if(tfoVnBTJNb == true){tfoVnBTJNb = false;}
      if(zdHdxejWfe == true){zdHdxejWfe = false;}
      if(jfdtALHCZf == true){jfdtALHCZf = false;}
      if(YaXNVxXsUg == true){YaXNVxXsUg = false;}
      if(SNtKluihFW == true){SNtKluihFW = false;}
      if(NoywpOBuVc == true){NoywpOBuVc = false;}
      if(sRigCYGsHz == true){sRigCYGsHz = false;}
      if(GqCzLWlTHF == true){GqCzLWlTHF = false;}
      if(cYxDSjcaXG == true){cYxDSjcaXG = false;}
      if(ucXrmBeMHN == true){ucXrmBeMHN = false;}
      if(noZFPWmykS == true){noZFPWmykS = false;}
      if(chnQzUUeNS == true){chnQzUUeNS = false;}
      if(weUBDdTKLK == true){weUBDdTKLK = false;}
      if(rYLsQmyqmw == true){rYLsQmyqmw = false;}
      if(wdpEdNnGrS == true){wdpEdNnGrS = false;}
      if(gzzoQJUYBk == true){gzzoQJUYBk = false;}
      if(CcmZaDVtzM == true){CcmZaDVtzM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZXQDGMOCX
{ 
  void LVBBeatPXu()
  { 
      bool koTxHtFnaM = false;
      bool xTirqRAZMD = false;
      bool qOUtLGmGQt = false;
      bool AcjzjGVBgb = false;
      bool rgLzaDNFwi = false;
      bool FmiNlWTYlA = false;
      bool HzWfMUjiHk = false;
      bool uysjKKCUTH = false;
      bool shJgoMsVMM = false;
      bool lwPfUsJemF = false;
      bool TdxLmGtzCb = false;
      bool TzFdHYooqA = false;
      bool bNWtyziMPR = false;
      bool AXhNnOjyth = false;
      bool RtTjsmplYu = false;
      bool ETmlcFHCMn = false;
      bool XhikbwQrpr = false;
      bool opuJhhtlBL = false;
      bool IwnTNfjujh = false;
      bool HhlFJjKhIw = false;
      string AjiCfUsocr;
      string RsiVfbTHAc;
      string mFVHQTRQqJ;
      string BhZqXSSnUa;
      string CSyYBticjM;
      string QRoKUtOakM;
      string CbySpiTqxM;
      string IfmZZTGxGW;
      string jogdsjrPVd;
      string EqCIYZUfhR;
      string aqfWDjdPjB;
      string mQUObMuUZG;
      string qEVTIRceAA;
      string zaOnusJKZI;
      string FceTpmVmfL;
      string dAFbaWVMNl;
      string HzOiCMBgTi;
      string DjtRANYBcV;
      string uoyoVyUmMY;
      string XwxmAGNwRd;
      if(AjiCfUsocr == aqfWDjdPjB){koTxHtFnaM = true;}
      else if(aqfWDjdPjB == AjiCfUsocr){TdxLmGtzCb = true;}
      if(RsiVfbTHAc == mQUObMuUZG){xTirqRAZMD = true;}
      else if(mQUObMuUZG == RsiVfbTHAc){TzFdHYooqA = true;}
      if(mFVHQTRQqJ == qEVTIRceAA){qOUtLGmGQt = true;}
      else if(qEVTIRceAA == mFVHQTRQqJ){bNWtyziMPR = true;}
      if(BhZqXSSnUa == zaOnusJKZI){AcjzjGVBgb = true;}
      else if(zaOnusJKZI == BhZqXSSnUa){AXhNnOjyth = true;}
      if(CSyYBticjM == FceTpmVmfL){rgLzaDNFwi = true;}
      else if(FceTpmVmfL == CSyYBticjM){RtTjsmplYu = true;}
      if(QRoKUtOakM == dAFbaWVMNl){FmiNlWTYlA = true;}
      else if(dAFbaWVMNl == QRoKUtOakM){ETmlcFHCMn = true;}
      if(CbySpiTqxM == HzOiCMBgTi){HzWfMUjiHk = true;}
      else if(HzOiCMBgTi == CbySpiTqxM){XhikbwQrpr = true;}
      if(IfmZZTGxGW == DjtRANYBcV){uysjKKCUTH = true;}
      if(jogdsjrPVd == uoyoVyUmMY){shJgoMsVMM = true;}
      if(EqCIYZUfhR == XwxmAGNwRd){lwPfUsJemF = true;}
      while(DjtRANYBcV == IfmZZTGxGW){opuJhhtlBL = true;}
      while(uoyoVyUmMY == uoyoVyUmMY){IwnTNfjujh = true;}
      while(XwxmAGNwRd == XwxmAGNwRd){HhlFJjKhIw = true;}
      if(koTxHtFnaM == true){koTxHtFnaM = false;}
      if(xTirqRAZMD == true){xTirqRAZMD = false;}
      if(qOUtLGmGQt == true){qOUtLGmGQt = false;}
      if(AcjzjGVBgb == true){AcjzjGVBgb = false;}
      if(rgLzaDNFwi == true){rgLzaDNFwi = false;}
      if(FmiNlWTYlA == true){FmiNlWTYlA = false;}
      if(HzWfMUjiHk == true){HzWfMUjiHk = false;}
      if(uysjKKCUTH == true){uysjKKCUTH = false;}
      if(shJgoMsVMM == true){shJgoMsVMM = false;}
      if(lwPfUsJemF == true){lwPfUsJemF = false;}
      if(TdxLmGtzCb == true){TdxLmGtzCb = false;}
      if(TzFdHYooqA == true){TzFdHYooqA = false;}
      if(bNWtyziMPR == true){bNWtyziMPR = false;}
      if(AXhNnOjyth == true){AXhNnOjyth = false;}
      if(RtTjsmplYu == true){RtTjsmplYu = false;}
      if(ETmlcFHCMn == true){ETmlcFHCMn = false;}
      if(XhikbwQrpr == true){XhikbwQrpr = false;}
      if(opuJhhtlBL == true){opuJhhtlBL = false;}
      if(IwnTNfjujh == true){IwnTNfjujh = false;}
      if(HhlFJjKhIw == true){HhlFJjKhIw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MAVDTYWJUW
{ 
  void IPTKCDHKxC()
  { 
      bool FzOPytmkuK = false;
      bool gHVVLFVSaY = false;
      bool sReMuqNqEg = false;
      bool eechpxMWTy = false;
      bool KihiXWaJpN = false;
      bool pJXsOmUCTH = false;
      bool gwfOfBdmfN = false;
      bool rzycOKjunY = false;
      bool QEAppUHiTC = false;
      bool cKCMQOCSCV = false;
      bool rncbVqKtdE = false;
      bool DYNuqcuoYL = false;
      bool ttSdkhxlLA = false;
      bool HQsRfbbXUy = false;
      bool JMFOzDwGVn = false;
      bool SNtqayUyqn = false;
      bool tYhdxlfuPO = false;
      bool BWTZBhoEeg = false;
      bool kpQXgtWCqh = false;
      bool HcggEkdaQM = false;
      string MZEBQBmiYg;
      string HrjfKbtyup;
      string iLqQunYktH;
      string OgcFKyxVYJ;
      string fWAVOWSsZH;
      string PJcJNAimGc;
      string bBnRSaPdVL;
      string eYYlJMLUBX;
      string VfLlrFESrJ;
      string OJPwgdhhCn;
      string HnXNcqjpzB;
      string oNlhGupCYN;
      string VwlLwUJbEf;
      string dcSMPgIxJB;
      string UOSpUBXgol;
      string mfJnSKCLRH;
      string gIkTXMuYRZ;
      string msrXsHdupu;
      string wblSryTdtF;
      string dwfBTMczSH;
      if(MZEBQBmiYg == HnXNcqjpzB){FzOPytmkuK = true;}
      else if(HnXNcqjpzB == MZEBQBmiYg){rncbVqKtdE = true;}
      if(HrjfKbtyup == oNlhGupCYN){gHVVLFVSaY = true;}
      else if(oNlhGupCYN == HrjfKbtyup){DYNuqcuoYL = true;}
      if(iLqQunYktH == VwlLwUJbEf){sReMuqNqEg = true;}
      else if(VwlLwUJbEf == iLqQunYktH){ttSdkhxlLA = true;}
      if(OgcFKyxVYJ == dcSMPgIxJB){eechpxMWTy = true;}
      else if(dcSMPgIxJB == OgcFKyxVYJ){HQsRfbbXUy = true;}
      if(fWAVOWSsZH == UOSpUBXgol){KihiXWaJpN = true;}
      else if(UOSpUBXgol == fWAVOWSsZH){JMFOzDwGVn = true;}
      if(PJcJNAimGc == mfJnSKCLRH){pJXsOmUCTH = true;}
      else if(mfJnSKCLRH == PJcJNAimGc){SNtqayUyqn = true;}
      if(bBnRSaPdVL == gIkTXMuYRZ){gwfOfBdmfN = true;}
      else if(gIkTXMuYRZ == bBnRSaPdVL){tYhdxlfuPO = true;}
      if(eYYlJMLUBX == msrXsHdupu){rzycOKjunY = true;}
      if(VfLlrFESrJ == wblSryTdtF){QEAppUHiTC = true;}
      if(OJPwgdhhCn == dwfBTMczSH){cKCMQOCSCV = true;}
      while(msrXsHdupu == eYYlJMLUBX){BWTZBhoEeg = true;}
      while(wblSryTdtF == wblSryTdtF){kpQXgtWCqh = true;}
      while(dwfBTMczSH == dwfBTMczSH){HcggEkdaQM = true;}
      if(FzOPytmkuK == true){FzOPytmkuK = false;}
      if(gHVVLFVSaY == true){gHVVLFVSaY = false;}
      if(sReMuqNqEg == true){sReMuqNqEg = false;}
      if(eechpxMWTy == true){eechpxMWTy = false;}
      if(KihiXWaJpN == true){KihiXWaJpN = false;}
      if(pJXsOmUCTH == true){pJXsOmUCTH = false;}
      if(gwfOfBdmfN == true){gwfOfBdmfN = false;}
      if(rzycOKjunY == true){rzycOKjunY = false;}
      if(QEAppUHiTC == true){QEAppUHiTC = false;}
      if(cKCMQOCSCV == true){cKCMQOCSCV = false;}
      if(rncbVqKtdE == true){rncbVqKtdE = false;}
      if(DYNuqcuoYL == true){DYNuqcuoYL = false;}
      if(ttSdkhxlLA == true){ttSdkhxlLA = false;}
      if(HQsRfbbXUy == true){HQsRfbbXUy = false;}
      if(JMFOzDwGVn == true){JMFOzDwGVn = false;}
      if(SNtqayUyqn == true){SNtqayUyqn = false;}
      if(tYhdxlfuPO == true){tYhdxlfuPO = false;}
      if(BWTZBhoEeg == true){BWTZBhoEeg = false;}
      if(kpQXgtWCqh == true){kpQXgtWCqh = false;}
      if(HcggEkdaQM == true){HcggEkdaQM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCXQALVQCY
{ 
  void UaTuxXKEBQ()
  { 
      bool wJSUfLhibL = false;
      bool tYgUyBRdME = false;
      bool jIWOVgnHUJ = false;
      bool OqENjIOZzZ = false;
      bool EoawXRVnQn = false;
      bool PehAGmlEyy = false;
      bool XaNSxCTSjp = false;
      bool lqdlzugZpE = false;
      bool KzpgsiJEGw = false;
      bool VKaBCdaIzU = false;
      bool xCEaCXBuAK = false;
      bool GMNtmYkgYN = false;
      bool sPLmTaQbjV = false;
      bool TXZVHHuPdU = false;
      bool gNDwpJxgNd = false;
      bool rtjlbgqQGa = false;
      bool HYLdpilqle = false;
      bool cUCDgeLPxK = false;
      bool djOGcZnnsZ = false;
      bool QdICNHCYFG = false;
      string MJoVaubxfh;
      string WJATgOUDWi;
      string QszCjgtUqJ;
      string OKrPrByMKn;
      string XPyXlbWQUn;
      string WgmFjTKmkt;
      string AGGVSMRjbe;
      string QHsiLAtbQH;
      string JczDmhWmeY;
      string qKbQmQIcEY;
      string KlooWOnEsi;
      string YiWcjXHDik;
      string peEDnGfbuu;
      string rQWqxXnKfX;
      string sSsuzHnygP;
      string IFsTifgkBQ;
      string iLJyqHLefL;
      string jxWKqXlIEf;
      string RgtflmXDIR;
      string pCIPogItEq;
      if(MJoVaubxfh == KlooWOnEsi){wJSUfLhibL = true;}
      else if(KlooWOnEsi == MJoVaubxfh){xCEaCXBuAK = true;}
      if(WJATgOUDWi == YiWcjXHDik){tYgUyBRdME = true;}
      else if(YiWcjXHDik == WJATgOUDWi){GMNtmYkgYN = true;}
      if(QszCjgtUqJ == peEDnGfbuu){jIWOVgnHUJ = true;}
      else if(peEDnGfbuu == QszCjgtUqJ){sPLmTaQbjV = true;}
      if(OKrPrByMKn == rQWqxXnKfX){OqENjIOZzZ = true;}
      else if(rQWqxXnKfX == OKrPrByMKn){TXZVHHuPdU = true;}
      if(XPyXlbWQUn == sSsuzHnygP){EoawXRVnQn = true;}
      else if(sSsuzHnygP == XPyXlbWQUn){gNDwpJxgNd = true;}
      if(WgmFjTKmkt == IFsTifgkBQ){PehAGmlEyy = true;}
      else if(IFsTifgkBQ == WgmFjTKmkt){rtjlbgqQGa = true;}
      if(AGGVSMRjbe == iLJyqHLefL){XaNSxCTSjp = true;}
      else if(iLJyqHLefL == AGGVSMRjbe){HYLdpilqle = true;}
      if(QHsiLAtbQH == jxWKqXlIEf){lqdlzugZpE = true;}
      if(JczDmhWmeY == RgtflmXDIR){KzpgsiJEGw = true;}
      if(qKbQmQIcEY == pCIPogItEq){VKaBCdaIzU = true;}
      while(jxWKqXlIEf == QHsiLAtbQH){cUCDgeLPxK = true;}
      while(RgtflmXDIR == RgtflmXDIR){djOGcZnnsZ = true;}
      while(pCIPogItEq == pCIPogItEq){QdICNHCYFG = true;}
      if(wJSUfLhibL == true){wJSUfLhibL = false;}
      if(tYgUyBRdME == true){tYgUyBRdME = false;}
      if(jIWOVgnHUJ == true){jIWOVgnHUJ = false;}
      if(OqENjIOZzZ == true){OqENjIOZzZ = false;}
      if(EoawXRVnQn == true){EoawXRVnQn = false;}
      if(PehAGmlEyy == true){PehAGmlEyy = false;}
      if(XaNSxCTSjp == true){XaNSxCTSjp = false;}
      if(lqdlzugZpE == true){lqdlzugZpE = false;}
      if(KzpgsiJEGw == true){KzpgsiJEGw = false;}
      if(VKaBCdaIzU == true){VKaBCdaIzU = false;}
      if(xCEaCXBuAK == true){xCEaCXBuAK = false;}
      if(GMNtmYkgYN == true){GMNtmYkgYN = false;}
      if(sPLmTaQbjV == true){sPLmTaQbjV = false;}
      if(TXZVHHuPdU == true){TXZVHHuPdU = false;}
      if(gNDwpJxgNd == true){gNDwpJxgNd = false;}
      if(rtjlbgqQGa == true){rtjlbgqQGa = false;}
      if(HYLdpilqle == true){HYLdpilqle = false;}
      if(cUCDgeLPxK == true){cUCDgeLPxK = false;}
      if(djOGcZnnsZ == true){djOGcZnnsZ = false;}
      if(QdICNHCYFG == true){QdICNHCYFG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZJHHXXFGD
{ 
  void eyGXxfissH()
  { 
      bool HQLdWrocIw = false;
      bool BCDPYQCSAG = false;
      bool ZxmzVYkDJi = false;
      bool kAKnJHgixf = false;
      bool LmOczyTBJz = false;
      bool zpCqTJdMIy = false;
      bool HkSZKArPGR = false;
      bool iTVTtmhJAW = false;
      bool FitJiuxSTz = false;
      bool dUZzYaToSy = false;
      bool GEuqQeUhwg = false;
      bool bTMkrXqJqP = false;
      bool CYwGnNtVuT = false;
      bool SsqBQBmCsD = false;
      bool ZOVlXJInGA = false;
      bool jKxCugHoDC = false;
      bool kymcOhcKUq = false;
      bool knPmonCJhe = false;
      bool EFPtjHunGi = false;
      bool sxzpSbasWo = false;
      string mUVKdLjeJX;
      string caGodmZzMn;
      string QJPuTMnJhV;
      string XNcBYUgFBy;
      string XrozwgcWjE;
      string hapIKdEapR;
      string XawmAOyEPJ;
      string GTxOQYTQym;
      string iQYdnwXTqu;
      string PFOiZwuByh;
      string hXGZxOdark;
      string JmcDhGBSzD;
      string qdNUsAENnT;
      string dSSQELJyfZ;
      string SwaFlbcLBT;
      string ubCtqDKlgx;
      string JPmYHqUMzW;
      string wCmZktCHiQ;
      string XsMUYBQXZA;
      string BXRiPCICxt;
      if(mUVKdLjeJX == hXGZxOdark){HQLdWrocIw = true;}
      else if(hXGZxOdark == mUVKdLjeJX){GEuqQeUhwg = true;}
      if(caGodmZzMn == JmcDhGBSzD){BCDPYQCSAG = true;}
      else if(JmcDhGBSzD == caGodmZzMn){bTMkrXqJqP = true;}
      if(QJPuTMnJhV == qdNUsAENnT){ZxmzVYkDJi = true;}
      else if(qdNUsAENnT == QJPuTMnJhV){CYwGnNtVuT = true;}
      if(XNcBYUgFBy == dSSQELJyfZ){kAKnJHgixf = true;}
      else if(dSSQELJyfZ == XNcBYUgFBy){SsqBQBmCsD = true;}
      if(XrozwgcWjE == SwaFlbcLBT){LmOczyTBJz = true;}
      else if(SwaFlbcLBT == XrozwgcWjE){ZOVlXJInGA = true;}
      if(hapIKdEapR == ubCtqDKlgx){zpCqTJdMIy = true;}
      else if(ubCtqDKlgx == hapIKdEapR){jKxCugHoDC = true;}
      if(XawmAOyEPJ == JPmYHqUMzW){HkSZKArPGR = true;}
      else if(JPmYHqUMzW == XawmAOyEPJ){kymcOhcKUq = true;}
      if(GTxOQYTQym == wCmZktCHiQ){iTVTtmhJAW = true;}
      if(iQYdnwXTqu == XsMUYBQXZA){FitJiuxSTz = true;}
      if(PFOiZwuByh == BXRiPCICxt){dUZzYaToSy = true;}
      while(wCmZktCHiQ == GTxOQYTQym){knPmonCJhe = true;}
      while(XsMUYBQXZA == XsMUYBQXZA){EFPtjHunGi = true;}
      while(BXRiPCICxt == BXRiPCICxt){sxzpSbasWo = true;}
      if(HQLdWrocIw == true){HQLdWrocIw = false;}
      if(BCDPYQCSAG == true){BCDPYQCSAG = false;}
      if(ZxmzVYkDJi == true){ZxmzVYkDJi = false;}
      if(kAKnJHgixf == true){kAKnJHgixf = false;}
      if(LmOczyTBJz == true){LmOczyTBJz = false;}
      if(zpCqTJdMIy == true){zpCqTJdMIy = false;}
      if(HkSZKArPGR == true){HkSZKArPGR = false;}
      if(iTVTtmhJAW == true){iTVTtmhJAW = false;}
      if(FitJiuxSTz == true){FitJiuxSTz = false;}
      if(dUZzYaToSy == true){dUZzYaToSy = false;}
      if(GEuqQeUhwg == true){GEuqQeUhwg = false;}
      if(bTMkrXqJqP == true){bTMkrXqJqP = false;}
      if(CYwGnNtVuT == true){CYwGnNtVuT = false;}
      if(SsqBQBmCsD == true){SsqBQBmCsD = false;}
      if(ZOVlXJInGA == true){ZOVlXJInGA = false;}
      if(jKxCugHoDC == true){jKxCugHoDC = false;}
      if(kymcOhcKUq == true){kymcOhcKUq = false;}
      if(knPmonCJhe == true){knPmonCJhe = false;}
      if(EFPtjHunGi == true){EFPtjHunGi = false;}
      if(sxzpSbasWo == true){sxzpSbasWo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUXIRUMRMH
{ 
  void oMaBHYXWJA()
  { 
      bool qqGFKMQqwU = false;
      bool zVDjYSKrZg = false;
      bool cpfwPINXWI = false;
      bool GAwDGiKScY = false;
      bool qCYAUfUcgL = false;
      bool XEPlkBLJpC = false;
      bool ysTmOyYAco = false;
      bool HrPBoZQebj = false;
      bool nkpLjBjJRF = false;
      bool XAcaZyhklV = false;
      bool GUArDfoNxK = false;
      bool jfhFNNDIDM = false;
      bool NOhWRHOobq = false;
      bool rfsFcSkyHD = false;
      bool MWMHVrRWMM = false;
      bool tZhZHqmcaw = false;
      bool QAlGSElbct = false;
      bool cEBzzqCZBY = false;
      bool orbOwRxTyk = false;
      bool fHXKmLjGoR = false;
      string MXZZtWdutB;
      string RmFAJpAFzt;
      string LFCcHoidrs;
      string xwHbCojPhD;
      string KfJzbOoUBW;
      string HBHUYGVwSF;
      string mzDBDVfcyT;
      string GjXwjfwDAr;
      string AOcVkunmCw;
      string TnwbQKbIuG;
      string iLWgQXdLks;
      string KSuZFYWhPI;
      string grZCzRmueY;
      string DmHtJnruEN;
      string RcBJkBrWWq;
      string ntsmYplThy;
      string jifLpWKBPR;
      string gacBqDpQQx;
      string ZQXnkItUVT;
      string BXNFdhxpTN;
      if(MXZZtWdutB == iLWgQXdLks){qqGFKMQqwU = true;}
      else if(iLWgQXdLks == MXZZtWdutB){GUArDfoNxK = true;}
      if(RmFAJpAFzt == KSuZFYWhPI){zVDjYSKrZg = true;}
      else if(KSuZFYWhPI == RmFAJpAFzt){jfhFNNDIDM = true;}
      if(LFCcHoidrs == grZCzRmueY){cpfwPINXWI = true;}
      else if(grZCzRmueY == LFCcHoidrs){NOhWRHOobq = true;}
      if(xwHbCojPhD == DmHtJnruEN){GAwDGiKScY = true;}
      else if(DmHtJnruEN == xwHbCojPhD){rfsFcSkyHD = true;}
      if(KfJzbOoUBW == RcBJkBrWWq){qCYAUfUcgL = true;}
      else if(RcBJkBrWWq == KfJzbOoUBW){MWMHVrRWMM = true;}
      if(HBHUYGVwSF == ntsmYplThy){XEPlkBLJpC = true;}
      else if(ntsmYplThy == HBHUYGVwSF){tZhZHqmcaw = true;}
      if(mzDBDVfcyT == jifLpWKBPR){ysTmOyYAco = true;}
      else if(jifLpWKBPR == mzDBDVfcyT){QAlGSElbct = true;}
      if(GjXwjfwDAr == gacBqDpQQx){HrPBoZQebj = true;}
      if(AOcVkunmCw == ZQXnkItUVT){nkpLjBjJRF = true;}
      if(TnwbQKbIuG == BXNFdhxpTN){XAcaZyhklV = true;}
      while(gacBqDpQQx == GjXwjfwDAr){cEBzzqCZBY = true;}
      while(ZQXnkItUVT == ZQXnkItUVT){orbOwRxTyk = true;}
      while(BXNFdhxpTN == BXNFdhxpTN){fHXKmLjGoR = true;}
      if(qqGFKMQqwU == true){qqGFKMQqwU = false;}
      if(zVDjYSKrZg == true){zVDjYSKrZg = false;}
      if(cpfwPINXWI == true){cpfwPINXWI = false;}
      if(GAwDGiKScY == true){GAwDGiKScY = false;}
      if(qCYAUfUcgL == true){qCYAUfUcgL = false;}
      if(XEPlkBLJpC == true){XEPlkBLJpC = false;}
      if(ysTmOyYAco == true){ysTmOyYAco = false;}
      if(HrPBoZQebj == true){HrPBoZQebj = false;}
      if(nkpLjBjJRF == true){nkpLjBjJRF = false;}
      if(XAcaZyhklV == true){XAcaZyhklV = false;}
      if(GUArDfoNxK == true){GUArDfoNxK = false;}
      if(jfhFNNDIDM == true){jfhFNNDIDM = false;}
      if(NOhWRHOobq == true){NOhWRHOobq = false;}
      if(rfsFcSkyHD == true){rfsFcSkyHD = false;}
      if(MWMHVrRWMM == true){MWMHVrRWMM = false;}
      if(tZhZHqmcaw == true){tZhZHqmcaw = false;}
      if(QAlGSElbct == true){QAlGSElbct = false;}
      if(cEBzzqCZBY == true){cEBzzqCZBY = false;}
      if(orbOwRxTyk == true){orbOwRxTyk = false;}
      if(fHXKmLjGoR == true){fHXKmLjGoR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQYXERWQWX
{ 
  void apfKkpdLKa()
  { 
      bool taCOVRICqH = false;
      bool RLYTAzMKbK = false;
      bool ZbggzohaiR = false;
      bool zrqcyFYEUG = false;
      bool ouWfMtYQIF = false;
      bool HzXObStVPg = false;
      bool jgTYIYUuVu = false;
      bool aIpUUeEATE = false;
      bool PRScKzUcAf = false;
      bool KCnnWHayWm = false;
      bool ZcuMezJDsx = false;
      bool NsBKQSOpOJ = false;
      bool EqupjXTBxN = false;
      bool DGdfemVFyL = false;
      bool oQjDRRBdXE = false;
      bool skiMihhFcH = false;
      bool fIFfsHOUfd = false;
      bool wIqDUmHqYS = false;
      bool WpdsURWQxw = false;
      bool EQcpfgLEKJ = false;
      string gTkxMUnXYu;
      string FuNqFlJEFb;
      string rVeREOQfCL;
      string mTnjyHoGHE;
      string MlWXYKEDoF;
      string RREaEKoTsy;
      string DIVNHkGdsx;
      string xCxBOGyHss;
      string JMpxtUPMfm;
      string SVNIAEQJPm;
      string EaKqHOUCLy;
      string MhZAnpRYSm;
      string VsxFdaonBK;
      string pnqFoiCyoe;
      string AMBgakuNTJ;
      string lrqcRKcENf;
      string ZfBAIXpULF;
      string nTinlJrQes;
      string faTqYxxOnd;
      string GykIETKAYC;
      if(gTkxMUnXYu == EaKqHOUCLy){taCOVRICqH = true;}
      else if(EaKqHOUCLy == gTkxMUnXYu){ZcuMezJDsx = true;}
      if(FuNqFlJEFb == MhZAnpRYSm){RLYTAzMKbK = true;}
      else if(MhZAnpRYSm == FuNqFlJEFb){NsBKQSOpOJ = true;}
      if(rVeREOQfCL == VsxFdaonBK){ZbggzohaiR = true;}
      else if(VsxFdaonBK == rVeREOQfCL){EqupjXTBxN = true;}
      if(mTnjyHoGHE == pnqFoiCyoe){zrqcyFYEUG = true;}
      else if(pnqFoiCyoe == mTnjyHoGHE){DGdfemVFyL = true;}
      if(MlWXYKEDoF == AMBgakuNTJ){ouWfMtYQIF = true;}
      else if(AMBgakuNTJ == MlWXYKEDoF){oQjDRRBdXE = true;}
      if(RREaEKoTsy == lrqcRKcENf){HzXObStVPg = true;}
      else if(lrqcRKcENf == RREaEKoTsy){skiMihhFcH = true;}
      if(DIVNHkGdsx == ZfBAIXpULF){jgTYIYUuVu = true;}
      else if(ZfBAIXpULF == DIVNHkGdsx){fIFfsHOUfd = true;}
      if(xCxBOGyHss == nTinlJrQes){aIpUUeEATE = true;}
      if(JMpxtUPMfm == faTqYxxOnd){PRScKzUcAf = true;}
      if(SVNIAEQJPm == GykIETKAYC){KCnnWHayWm = true;}
      while(nTinlJrQes == xCxBOGyHss){wIqDUmHqYS = true;}
      while(faTqYxxOnd == faTqYxxOnd){WpdsURWQxw = true;}
      while(GykIETKAYC == GykIETKAYC){EQcpfgLEKJ = true;}
      if(taCOVRICqH == true){taCOVRICqH = false;}
      if(RLYTAzMKbK == true){RLYTAzMKbK = false;}
      if(ZbggzohaiR == true){ZbggzohaiR = false;}
      if(zrqcyFYEUG == true){zrqcyFYEUG = false;}
      if(ouWfMtYQIF == true){ouWfMtYQIF = false;}
      if(HzXObStVPg == true){HzXObStVPg = false;}
      if(jgTYIYUuVu == true){jgTYIYUuVu = false;}
      if(aIpUUeEATE == true){aIpUUeEATE = false;}
      if(PRScKzUcAf == true){PRScKzUcAf = false;}
      if(KCnnWHayWm == true){KCnnWHayWm = false;}
      if(ZcuMezJDsx == true){ZcuMezJDsx = false;}
      if(NsBKQSOpOJ == true){NsBKQSOpOJ = false;}
      if(EqupjXTBxN == true){EqupjXTBxN = false;}
      if(DGdfemVFyL == true){DGdfemVFyL = false;}
      if(oQjDRRBdXE == true){oQjDRRBdXE = false;}
      if(skiMihhFcH == true){skiMihhFcH = false;}
      if(fIFfsHOUfd == true){fIFfsHOUfd = false;}
      if(wIqDUmHqYS == true){wIqDUmHqYS = false;}
      if(WpdsURWQxw == true){WpdsURWQxw = false;}
      if(EQcpfgLEKJ == true){EQcpfgLEKJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RERSDLUNZX
{ 
  void VPPpCrFaAB()
  { 
      bool AadHkHoOlV = false;
      bool eUSOqEIjEb = false;
      bool WUeBcMVUqU = false;
      bool pYCYQYbKLm = false;
      bool hEheLXIuHZ = false;
      bool QiiANfwbdY = false;
      bool kUWQeGRtxR = false;
      bool cxYQtSlzoF = false;
      bool DZMQDGoCLk = false;
      bool czfmBNgRzE = false;
      bool FOxoxTKRGu = false;
      bool swmYULHFNX = false;
      bool QPhModQkPf = false;
      bool kUzjznbXTj = false;
      bool wXuQqfLHRo = false;
      bool GbDampgkzT = false;
      bool CYBaKYwCYg = false;
      bool ijldbsTQUJ = false;
      bool RJSZZIQYwJ = false;
      bool HqXzhWWUGS = false;
      string kkIcCCNsiC;
      string OKEYkSbGWI;
      string EnTbcgnJBs;
      string kytlRxxzPg;
      string PImsGFcUcQ;
      string QNsabwQgzU;
      string NDroRPQSGn;
      string VcppswBaVX;
      string ETfjcWESJV;
      string fQztTLPxap;
      string oKNoumWDgf;
      string tpKbQtXHLt;
      string KxJkHFcwVh;
      string fEAfitFqoo;
      string ABlcapFWdY;
      string nIkfeqBcgp;
      string KagyApoesV;
      string nfSWtJLfJR;
      string zFRwtXSUAq;
      string sbKyeZTmcj;
      if(kkIcCCNsiC == oKNoumWDgf){AadHkHoOlV = true;}
      else if(oKNoumWDgf == kkIcCCNsiC){FOxoxTKRGu = true;}
      if(OKEYkSbGWI == tpKbQtXHLt){eUSOqEIjEb = true;}
      else if(tpKbQtXHLt == OKEYkSbGWI){swmYULHFNX = true;}
      if(EnTbcgnJBs == KxJkHFcwVh){WUeBcMVUqU = true;}
      else if(KxJkHFcwVh == EnTbcgnJBs){QPhModQkPf = true;}
      if(kytlRxxzPg == fEAfitFqoo){pYCYQYbKLm = true;}
      else if(fEAfitFqoo == kytlRxxzPg){kUzjznbXTj = true;}
      if(PImsGFcUcQ == ABlcapFWdY){hEheLXIuHZ = true;}
      else if(ABlcapFWdY == PImsGFcUcQ){wXuQqfLHRo = true;}
      if(QNsabwQgzU == nIkfeqBcgp){QiiANfwbdY = true;}
      else if(nIkfeqBcgp == QNsabwQgzU){GbDampgkzT = true;}
      if(NDroRPQSGn == KagyApoesV){kUWQeGRtxR = true;}
      else if(KagyApoesV == NDroRPQSGn){CYBaKYwCYg = true;}
      if(VcppswBaVX == nfSWtJLfJR){cxYQtSlzoF = true;}
      if(ETfjcWESJV == zFRwtXSUAq){DZMQDGoCLk = true;}
      if(fQztTLPxap == sbKyeZTmcj){czfmBNgRzE = true;}
      while(nfSWtJLfJR == VcppswBaVX){ijldbsTQUJ = true;}
      while(zFRwtXSUAq == zFRwtXSUAq){RJSZZIQYwJ = true;}
      while(sbKyeZTmcj == sbKyeZTmcj){HqXzhWWUGS = true;}
      if(AadHkHoOlV == true){AadHkHoOlV = false;}
      if(eUSOqEIjEb == true){eUSOqEIjEb = false;}
      if(WUeBcMVUqU == true){WUeBcMVUqU = false;}
      if(pYCYQYbKLm == true){pYCYQYbKLm = false;}
      if(hEheLXIuHZ == true){hEheLXIuHZ = false;}
      if(QiiANfwbdY == true){QiiANfwbdY = false;}
      if(kUWQeGRtxR == true){kUWQeGRtxR = false;}
      if(cxYQtSlzoF == true){cxYQtSlzoF = false;}
      if(DZMQDGoCLk == true){DZMQDGoCLk = false;}
      if(czfmBNgRzE == true){czfmBNgRzE = false;}
      if(FOxoxTKRGu == true){FOxoxTKRGu = false;}
      if(swmYULHFNX == true){swmYULHFNX = false;}
      if(QPhModQkPf == true){QPhModQkPf = false;}
      if(kUzjznbXTj == true){kUzjznbXTj = false;}
      if(wXuQqfLHRo == true){wXuQqfLHRo = false;}
      if(GbDampgkzT == true){GbDampgkzT = false;}
      if(CYBaKYwCYg == true){CYBaKYwCYg = false;}
      if(ijldbsTQUJ == true){ijldbsTQUJ = false;}
      if(RJSZZIQYwJ == true){RJSZZIQYwJ = false;}
      if(HqXzhWWUGS == true){HqXzhWWUGS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKBDFYBEEB
{ 
  void nKzAAsfTcg()
  { 
      bool TLWQSzwNEL = false;
      bool BFakyhgDiG = false;
      bool OEyaqBLWUa = false;
      bool zXFoyAYNjb = false;
      bool akjVroeFRF = false;
      bool IXIlOONwZQ = false;
      bool nYrdMcAlly = false;
      bool ISSHfcUbhB = false;
      bool VFEORaPSZi = false;
      bool mcmTmBrFJP = false;
      bool osSTxoFBGl = false;
      bool tkNYthTdMk = false;
      bool NgLDKfezTe = false;
      bool jORSLcmkRb = false;
      bool VNMnnBPOYF = false;
      bool gOsYBHhOJQ = false;
      bool KGhaCfStMR = false;
      bool uiLjPzTWPI = false;
      bool QQZNyUUsRE = false;
      bool uXaAROfllI = false;
      string NtDMDyjJMY;
      string hFiDTJFgBq;
      string NQsklmnMDG;
      string NJyCVTLwHq;
      string TGBxUqJkjM;
      string YSsJsxASZQ;
      string KXGGLYGfhz;
      string xJYJXHPwQu;
      string dDcpgtQnJY;
      string SsWqguzulu;
      string jcDjOPsilk;
      string hEBemHtPYQ;
      string ISWJgEmhcb;
      string HUKUKBzsbQ;
      string AgCXpOrqDZ;
      string AjVUmRFsDK;
      string cLFKdNtfTl;
      string HBnIPaPzSR;
      string LueCaWyohs;
      string uGpQmoarsc;
      if(NtDMDyjJMY == jcDjOPsilk){TLWQSzwNEL = true;}
      else if(jcDjOPsilk == NtDMDyjJMY){osSTxoFBGl = true;}
      if(hFiDTJFgBq == hEBemHtPYQ){BFakyhgDiG = true;}
      else if(hEBemHtPYQ == hFiDTJFgBq){tkNYthTdMk = true;}
      if(NQsklmnMDG == ISWJgEmhcb){OEyaqBLWUa = true;}
      else if(ISWJgEmhcb == NQsklmnMDG){NgLDKfezTe = true;}
      if(NJyCVTLwHq == HUKUKBzsbQ){zXFoyAYNjb = true;}
      else if(HUKUKBzsbQ == NJyCVTLwHq){jORSLcmkRb = true;}
      if(TGBxUqJkjM == AgCXpOrqDZ){akjVroeFRF = true;}
      else if(AgCXpOrqDZ == TGBxUqJkjM){VNMnnBPOYF = true;}
      if(YSsJsxASZQ == AjVUmRFsDK){IXIlOONwZQ = true;}
      else if(AjVUmRFsDK == YSsJsxASZQ){gOsYBHhOJQ = true;}
      if(KXGGLYGfhz == cLFKdNtfTl){nYrdMcAlly = true;}
      else if(cLFKdNtfTl == KXGGLYGfhz){KGhaCfStMR = true;}
      if(xJYJXHPwQu == HBnIPaPzSR){ISSHfcUbhB = true;}
      if(dDcpgtQnJY == LueCaWyohs){VFEORaPSZi = true;}
      if(SsWqguzulu == uGpQmoarsc){mcmTmBrFJP = true;}
      while(HBnIPaPzSR == xJYJXHPwQu){uiLjPzTWPI = true;}
      while(LueCaWyohs == LueCaWyohs){QQZNyUUsRE = true;}
      while(uGpQmoarsc == uGpQmoarsc){uXaAROfllI = true;}
      if(TLWQSzwNEL == true){TLWQSzwNEL = false;}
      if(BFakyhgDiG == true){BFakyhgDiG = false;}
      if(OEyaqBLWUa == true){OEyaqBLWUa = false;}
      if(zXFoyAYNjb == true){zXFoyAYNjb = false;}
      if(akjVroeFRF == true){akjVroeFRF = false;}
      if(IXIlOONwZQ == true){IXIlOONwZQ = false;}
      if(nYrdMcAlly == true){nYrdMcAlly = false;}
      if(ISSHfcUbhB == true){ISSHfcUbhB = false;}
      if(VFEORaPSZi == true){VFEORaPSZi = false;}
      if(mcmTmBrFJP == true){mcmTmBrFJP = false;}
      if(osSTxoFBGl == true){osSTxoFBGl = false;}
      if(tkNYthTdMk == true){tkNYthTdMk = false;}
      if(NgLDKfezTe == true){NgLDKfezTe = false;}
      if(jORSLcmkRb == true){jORSLcmkRb = false;}
      if(VNMnnBPOYF == true){VNMnnBPOYF = false;}
      if(gOsYBHhOJQ == true){gOsYBHhOJQ = false;}
      if(KGhaCfStMR == true){KGhaCfStMR = false;}
      if(uiLjPzTWPI == true){uiLjPzTWPI = false;}
      if(QQZNyUUsRE == true){QQZNyUUsRE = false;}
      if(uXaAROfllI == true){uXaAROfllI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSFPRCGUMH
{ 
  void BqoXJyUzxT()
  { 
      bool lSonFwHqHJ = false;
      bool ynEiWFHqUd = false;
      bool xsBHgkFwoD = false;
      bool OHoosmPdmF = false;
      bool nPSgzyFbGB = false;
      bool mQMBrsQgGT = false;
      bool pKCEuqzPoi = false;
      bool ocEPohZUIi = false;
      bool edonPxumwA = false;
      bool WiXSOcNNkI = false;
      bool zplWLJMwMJ = false;
      bool SwYXoLVNoy = false;
      bool wMSoMGFkAL = false;
      bool UMiAiorRbF = false;
      bool jyalgaJzdC = false;
      bool HzYmLmXwKF = false;
      bool EbwAoGMYnA = false;
      bool TDliOxkfHl = false;
      bool wFGxDVnunw = false;
      bool QuHVBHBZxa = false;
      string TgxpxKhYRW;
      string UYkwHOmeJi;
      string leYIfyWSrc;
      string egqCgOSyab;
      string RumRkNRWsp;
      string AGKCtoHoJy;
      string nPgnrmhhPs;
      string woEgQqqGWR;
      string fzZBcXWoIq;
      string GdnbnCNyZy;
      string fiGAtLCckD;
      string xARrRnofLT;
      string QrZXlRBbsO;
      string csgYlxrYGQ;
      string VsDFsGLuJA;
      string MglGgmJiOc;
      string KZjWZETsGU;
      string uQZuyWnUdf;
      string FFSrBwGaqy;
      string mJKdGuIgeo;
      if(TgxpxKhYRW == fiGAtLCckD){lSonFwHqHJ = true;}
      else if(fiGAtLCckD == TgxpxKhYRW){zplWLJMwMJ = true;}
      if(UYkwHOmeJi == xARrRnofLT){ynEiWFHqUd = true;}
      else if(xARrRnofLT == UYkwHOmeJi){SwYXoLVNoy = true;}
      if(leYIfyWSrc == QrZXlRBbsO){xsBHgkFwoD = true;}
      else if(QrZXlRBbsO == leYIfyWSrc){wMSoMGFkAL = true;}
      if(egqCgOSyab == csgYlxrYGQ){OHoosmPdmF = true;}
      else if(csgYlxrYGQ == egqCgOSyab){UMiAiorRbF = true;}
      if(RumRkNRWsp == VsDFsGLuJA){nPSgzyFbGB = true;}
      else if(VsDFsGLuJA == RumRkNRWsp){jyalgaJzdC = true;}
      if(AGKCtoHoJy == MglGgmJiOc){mQMBrsQgGT = true;}
      else if(MglGgmJiOc == AGKCtoHoJy){HzYmLmXwKF = true;}
      if(nPgnrmhhPs == KZjWZETsGU){pKCEuqzPoi = true;}
      else if(KZjWZETsGU == nPgnrmhhPs){EbwAoGMYnA = true;}
      if(woEgQqqGWR == uQZuyWnUdf){ocEPohZUIi = true;}
      if(fzZBcXWoIq == FFSrBwGaqy){edonPxumwA = true;}
      if(GdnbnCNyZy == mJKdGuIgeo){WiXSOcNNkI = true;}
      while(uQZuyWnUdf == woEgQqqGWR){TDliOxkfHl = true;}
      while(FFSrBwGaqy == FFSrBwGaqy){wFGxDVnunw = true;}
      while(mJKdGuIgeo == mJKdGuIgeo){QuHVBHBZxa = true;}
      if(lSonFwHqHJ == true){lSonFwHqHJ = false;}
      if(ynEiWFHqUd == true){ynEiWFHqUd = false;}
      if(xsBHgkFwoD == true){xsBHgkFwoD = false;}
      if(OHoosmPdmF == true){OHoosmPdmF = false;}
      if(nPSgzyFbGB == true){nPSgzyFbGB = false;}
      if(mQMBrsQgGT == true){mQMBrsQgGT = false;}
      if(pKCEuqzPoi == true){pKCEuqzPoi = false;}
      if(ocEPohZUIi == true){ocEPohZUIi = false;}
      if(edonPxumwA == true){edonPxumwA = false;}
      if(WiXSOcNNkI == true){WiXSOcNNkI = false;}
      if(zplWLJMwMJ == true){zplWLJMwMJ = false;}
      if(SwYXoLVNoy == true){SwYXoLVNoy = false;}
      if(wMSoMGFkAL == true){wMSoMGFkAL = false;}
      if(UMiAiorRbF == true){UMiAiorRbF = false;}
      if(jyalgaJzdC == true){jyalgaJzdC = false;}
      if(HzYmLmXwKF == true){HzYmLmXwKF = false;}
      if(EbwAoGMYnA == true){EbwAoGMYnA = false;}
      if(TDliOxkfHl == true){TDliOxkfHl = false;}
      if(wFGxDVnunw == true){wFGxDVnunw = false;}
      if(QuHVBHBZxa == true){QuHVBHBZxa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQXCCPZHHP
{ 
  void YNmmoNqmWI()
  { 
      bool ADodGTNPET = false;
      bool qEqUZJBBuk = false;
      bool OedYNVdKxw = false;
      bool DHSZicdGkV = false;
      bool UUTzCJBSPj = false;
      bool qDqYnUZPQj = false;
      bool oCSIQikRlw = false;
      bool fuQYQsLdWD = false;
      bool ULuMFAQskN = false;
      bool DNpAgRCKiS = false;
      bool XjfSDulSIu = false;
      bool IurMPcHFCQ = false;
      bool SrfYsRFPqy = false;
      bool qAuEfjebJJ = false;
      bool NykpEHVcjD = false;
      bool KwISAfEHYk = false;
      bool pWaKDHzngf = false;
      bool yewrCUHpTk = false;
      bool wbemnurcDz = false;
      bool fXDXTqWZlw = false;
      string cbRNkpirwg;
      string xYSeqILHLT;
      string CWYljbunII;
      string EfWRCdbgmw;
      string stIqCDpeEV;
      string hwXmXGDecJ;
      string uuinbQBBcM;
      string fdTPZHNgif;
      string kQjlZHHjsw;
      string ZxDdByLUOl;
      string CoBqpDcIMP;
      string rWuwXdLxNU;
      string IQHgmiZpOb;
      string wrSxdwOrwW;
      string ezWdDDBHFW;
      string lNGtckhUEG;
      string cltkTADySb;
      string PSAqoJtcci;
      string gSjrphkXTs;
      string NsnotrFlKD;
      if(cbRNkpirwg == CoBqpDcIMP){ADodGTNPET = true;}
      else if(CoBqpDcIMP == cbRNkpirwg){XjfSDulSIu = true;}
      if(xYSeqILHLT == rWuwXdLxNU){qEqUZJBBuk = true;}
      else if(rWuwXdLxNU == xYSeqILHLT){IurMPcHFCQ = true;}
      if(CWYljbunII == IQHgmiZpOb){OedYNVdKxw = true;}
      else if(IQHgmiZpOb == CWYljbunII){SrfYsRFPqy = true;}
      if(EfWRCdbgmw == wrSxdwOrwW){DHSZicdGkV = true;}
      else if(wrSxdwOrwW == EfWRCdbgmw){qAuEfjebJJ = true;}
      if(stIqCDpeEV == ezWdDDBHFW){UUTzCJBSPj = true;}
      else if(ezWdDDBHFW == stIqCDpeEV){NykpEHVcjD = true;}
      if(hwXmXGDecJ == lNGtckhUEG){qDqYnUZPQj = true;}
      else if(lNGtckhUEG == hwXmXGDecJ){KwISAfEHYk = true;}
      if(uuinbQBBcM == cltkTADySb){oCSIQikRlw = true;}
      else if(cltkTADySb == uuinbQBBcM){pWaKDHzngf = true;}
      if(fdTPZHNgif == PSAqoJtcci){fuQYQsLdWD = true;}
      if(kQjlZHHjsw == gSjrphkXTs){ULuMFAQskN = true;}
      if(ZxDdByLUOl == NsnotrFlKD){DNpAgRCKiS = true;}
      while(PSAqoJtcci == fdTPZHNgif){yewrCUHpTk = true;}
      while(gSjrphkXTs == gSjrphkXTs){wbemnurcDz = true;}
      while(NsnotrFlKD == NsnotrFlKD){fXDXTqWZlw = true;}
      if(ADodGTNPET == true){ADodGTNPET = false;}
      if(qEqUZJBBuk == true){qEqUZJBBuk = false;}
      if(OedYNVdKxw == true){OedYNVdKxw = false;}
      if(DHSZicdGkV == true){DHSZicdGkV = false;}
      if(UUTzCJBSPj == true){UUTzCJBSPj = false;}
      if(qDqYnUZPQj == true){qDqYnUZPQj = false;}
      if(oCSIQikRlw == true){oCSIQikRlw = false;}
      if(fuQYQsLdWD == true){fuQYQsLdWD = false;}
      if(ULuMFAQskN == true){ULuMFAQskN = false;}
      if(DNpAgRCKiS == true){DNpAgRCKiS = false;}
      if(XjfSDulSIu == true){XjfSDulSIu = false;}
      if(IurMPcHFCQ == true){IurMPcHFCQ = false;}
      if(SrfYsRFPqy == true){SrfYsRFPqy = false;}
      if(qAuEfjebJJ == true){qAuEfjebJJ = false;}
      if(NykpEHVcjD == true){NykpEHVcjD = false;}
      if(KwISAfEHYk == true){KwISAfEHYk = false;}
      if(pWaKDHzngf == true){pWaKDHzngf = false;}
      if(yewrCUHpTk == true){yewrCUHpTk = false;}
      if(wbemnurcDz == true){wbemnurcDz = false;}
      if(fXDXTqWZlw == true){fXDXTqWZlw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PIIWWNBWOW
{ 
  void PEGpEVNYfd()
  { 
      bool FPPidHoebP = false;
      bool lstxEzzKbf = false;
      bool GHBpsjzwCt = false;
      bool aGIXYNAAXL = false;
      bool VUAxEUGqYK = false;
      bool yENuxxNYos = false;
      bool HscgnfkWYq = false;
      bool yymQJkHElX = false;
      bool dHWrwWrMZa = false;
      bool zaLdDcqSIX = false;
      bool jiRhLARxlL = false;
      bool pIlQPAVkkR = false;
      bool mXwyqXlINf = false;
      bool snwOmupofw = false;
      bool EuaOjpntOD = false;
      bool GGhpkMlTqn = false;
      bool NIiFRCMXcU = false;
      bool JfEnMrwhNA = false;
      bool irtKZmFFca = false;
      bool IVyrhwLVxh = false;
      string DOOXdQIIdm;
      string xraXYFMqwf;
      string WiwodAfrRr;
      string WXRjcmjwWI;
      string QsOHxpZBgM;
      string qfRXwTSYsc;
      string kQqlPYaqtl;
      string UPUnOcUnqn;
      string adLEAqGsmJ;
      string TLCsWABcrY;
      string OhHtrbKdIT;
      string yegFBHFlkX;
      string SgEkSIMbQN;
      string aruSYsWQMY;
      string fbkTKnewqO;
      string uPqTFhdVbi;
      string OiMtrGiOgI;
      string knZLrpwjad;
      string dPjBSLAbMp;
      string OAodJxPpbD;
      if(DOOXdQIIdm == OhHtrbKdIT){FPPidHoebP = true;}
      else if(OhHtrbKdIT == DOOXdQIIdm){jiRhLARxlL = true;}
      if(xraXYFMqwf == yegFBHFlkX){lstxEzzKbf = true;}
      else if(yegFBHFlkX == xraXYFMqwf){pIlQPAVkkR = true;}
      if(WiwodAfrRr == SgEkSIMbQN){GHBpsjzwCt = true;}
      else if(SgEkSIMbQN == WiwodAfrRr){mXwyqXlINf = true;}
      if(WXRjcmjwWI == aruSYsWQMY){aGIXYNAAXL = true;}
      else if(aruSYsWQMY == WXRjcmjwWI){snwOmupofw = true;}
      if(QsOHxpZBgM == fbkTKnewqO){VUAxEUGqYK = true;}
      else if(fbkTKnewqO == QsOHxpZBgM){EuaOjpntOD = true;}
      if(qfRXwTSYsc == uPqTFhdVbi){yENuxxNYos = true;}
      else if(uPqTFhdVbi == qfRXwTSYsc){GGhpkMlTqn = true;}
      if(kQqlPYaqtl == OiMtrGiOgI){HscgnfkWYq = true;}
      else if(OiMtrGiOgI == kQqlPYaqtl){NIiFRCMXcU = true;}
      if(UPUnOcUnqn == knZLrpwjad){yymQJkHElX = true;}
      if(adLEAqGsmJ == dPjBSLAbMp){dHWrwWrMZa = true;}
      if(TLCsWABcrY == OAodJxPpbD){zaLdDcqSIX = true;}
      while(knZLrpwjad == UPUnOcUnqn){JfEnMrwhNA = true;}
      while(dPjBSLAbMp == dPjBSLAbMp){irtKZmFFca = true;}
      while(OAodJxPpbD == OAodJxPpbD){IVyrhwLVxh = true;}
      if(FPPidHoebP == true){FPPidHoebP = false;}
      if(lstxEzzKbf == true){lstxEzzKbf = false;}
      if(GHBpsjzwCt == true){GHBpsjzwCt = false;}
      if(aGIXYNAAXL == true){aGIXYNAAXL = false;}
      if(VUAxEUGqYK == true){VUAxEUGqYK = false;}
      if(yENuxxNYos == true){yENuxxNYos = false;}
      if(HscgnfkWYq == true){HscgnfkWYq = false;}
      if(yymQJkHElX == true){yymQJkHElX = false;}
      if(dHWrwWrMZa == true){dHWrwWrMZa = false;}
      if(zaLdDcqSIX == true){zaLdDcqSIX = false;}
      if(jiRhLARxlL == true){jiRhLARxlL = false;}
      if(pIlQPAVkkR == true){pIlQPAVkkR = false;}
      if(mXwyqXlINf == true){mXwyqXlINf = false;}
      if(snwOmupofw == true){snwOmupofw = false;}
      if(EuaOjpntOD == true){EuaOjpntOD = false;}
      if(GGhpkMlTqn == true){GGhpkMlTqn = false;}
      if(NIiFRCMXcU == true){NIiFRCMXcU = false;}
      if(JfEnMrwhNA == true){JfEnMrwhNA = false;}
      if(irtKZmFFca == true){irtKZmFFca = false;}
      if(IVyrhwLVxh == true){IVyrhwLVxh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJYENMCJLO
{ 
  void meCSJdcQWf()
  { 
      bool klNDWVNUIY = false;
      bool OKCmkVZphC = false;
      bool qyOFHMEeVz = false;
      bool mqDybyHXOQ = false;
      bool Gskeodqqor = false;
      bool XjWfLmWHwK = false;
      bool QizJlWHDKm = false;
      bool OBaRuxMiQc = false;
      bool VNpdbDUWmo = false;
      bool azbEzXtbsR = false;
      bool WmfCdVIEkN = false;
      bool ZnpSnDsUgh = false;
      bool CjQVLOZWRW = false;
      bool DkpzGhhmAF = false;
      bool uPlZOmJIPw = false;
      bool eYtKPlWJpO = false;
      bool wkmNKnxqMG = false;
      bool VFUamlyqHX = false;
      bool FRHVqdpejU = false;
      bool LXxkJJcXPZ = false;
      string YZtIZXKfir;
      string YLsOeQDEfI;
      string ojdtmSMaWH;
      string TVElWRNQqo;
      string AeVaDptEEO;
      string UpfSUnuzVH;
      string KiJbYDHHqM;
      string DmMqHJOCpx;
      string YIVHmcokQh;
      string VNujdRUtCA;
      string hmMqLhdnKL;
      string ZrIXiBMBow;
      string NWpJqoqcNp;
      string nTApOlwdwE;
      string yAZFIdEWAb;
      string ESFGlLwDAV;
      string pBaUWFrSJx;
      string FhFjxMwkAN;
      string jUbklUOtED;
      string osdZNxZFhC;
      if(YZtIZXKfir == hmMqLhdnKL){klNDWVNUIY = true;}
      else if(hmMqLhdnKL == YZtIZXKfir){WmfCdVIEkN = true;}
      if(YLsOeQDEfI == ZrIXiBMBow){OKCmkVZphC = true;}
      else if(ZrIXiBMBow == YLsOeQDEfI){ZnpSnDsUgh = true;}
      if(ojdtmSMaWH == NWpJqoqcNp){qyOFHMEeVz = true;}
      else if(NWpJqoqcNp == ojdtmSMaWH){CjQVLOZWRW = true;}
      if(TVElWRNQqo == nTApOlwdwE){mqDybyHXOQ = true;}
      else if(nTApOlwdwE == TVElWRNQqo){DkpzGhhmAF = true;}
      if(AeVaDptEEO == yAZFIdEWAb){Gskeodqqor = true;}
      else if(yAZFIdEWAb == AeVaDptEEO){uPlZOmJIPw = true;}
      if(UpfSUnuzVH == ESFGlLwDAV){XjWfLmWHwK = true;}
      else if(ESFGlLwDAV == UpfSUnuzVH){eYtKPlWJpO = true;}
      if(KiJbYDHHqM == pBaUWFrSJx){QizJlWHDKm = true;}
      else if(pBaUWFrSJx == KiJbYDHHqM){wkmNKnxqMG = true;}
      if(DmMqHJOCpx == FhFjxMwkAN){OBaRuxMiQc = true;}
      if(YIVHmcokQh == jUbklUOtED){VNpdbDUWmo = true;}
      if(VNujdRUtCA == osdZNxZFhC){azbEzXtbsR = true;}
      while(FhFjxMwkAN == DmMqHJOCpx){VFUamlyqHX = true;}
      while(jUbklUOtED == jUbklUOtED){FRHVqdpejU = true;}
      while(osdZNxZFhC == osdZNxZFhC){LXxkJJcXPZ = true;}
      if(klNDWVNUIY == true){klNDWVNUIY = false;}
      if(OKCmkVZphC == true){OKCmkVZphC = false;}
      if(qyOFHMEeVz == true){qyOFHMEeVz = false;}
      if(mqDybyHXOQ == true){mqDybyHXOQ = false;}
      if(Gskeodqqor == true){Gskeodqqor = false;}
      if(XjWfLmWHwK == true){XjWfLmWHwK = false;}
      if(QizJlWHDKm == true){QizJlWHDKm = false;}
      if(OBaRuxMiQc == true){OBaRuxMiQc = false;}
      if(VNpdbDUWmo == true){VNpdbDUWmo = false;}
      if(azbEzXtbsR == true){azbEzXtbsR = false;}
      if(WmfCdVIEkN == true){WmfCdVIEkN = false;}
      if(ZnpSnDsUgh == true){ZnpSnDsUgh = false;}
      if(CjQVLOZWRW == true){CjQVLOZWRW = false;}
      if(DkpzGhhmAF == true){DkpzGhhmAF = false;}
      if(uPlZOmJIPw == true){uPlZOmJIPw = false;}
      if(eYtKPlWJpO == true){eYtKPlWJpO = false;}
      if(wkmNKnxqMG == true){wkmNKnxqMG = false;}
      if(VFUamlyqHX == true){VFUamlyqHX = false;}
      if(FRHVqdpejU == true){FRHVqdpejU = false;}
      if(LXxkJJcXPZ == true){LXxkJJcXPZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZYORXXRSP
{ 
  void uEAykSCWDL()
  { 
      bool cDPRUXWCoU = false;
      bool VdkyBOoCrY = false;
      bool ifhrdlzUrX = false;
      bool jQHLwUrCjl = false;
      bool TRIEPmyiok = false;
      bool gwGnqxVWmh = false;
      bool XBJRjFVZCg = false;
      bool WlSFEQXccq = false;
      bool nQeGpmKSTz = false;
      bool yUOBNRHqUJ = false;
      bool QYgIOudAiZ = false;
      bool ZrtwtHWDaw = false;
      bool tCGChBWQrm = false;
      bool JfISZPiWru = false;
      bool JJjsZGZSHG = false;
      bool uEPXPNRdZM = false;
      bool XMIwQsibVe = false;
      bool XzKfmjSNcb = false;
      bool bEJkrEQkDM = false;
      bool xFxeWxBnbf = false;
      string YsXpgXPWSI;
      string bbCzTmUpLz;
      string EkrOMPyQRM;
      string NcrpkTFYnt;
      string qRNDrlGCFq;
      string TrTZanAIcR;
      string ZyEGtyiLNA;
      string gwCQIlWoWa;
      string IuKarVISPw;
      string SxuVUrMHIs;
      string CtnFJWpCRn;
      string RLkBJdmdNY;
      string oQwQgjBgwP;
      string ZOgdXOHFRV;
      string eFAbeHLsMq;
      string FitiDlyXXZ;
      string VJGCODdHdt;
      string WgMrsiPUlZ;
      string XHUEJpTyZl;
      string QjhqzVzyMa;
      if(YsXpgXPWSI == CtnFJWpCRn){cDPRUXWCoU = true;}
      else if(CtnFJWpCRn == YsXpgXPWSI){QYgIOudAiZ = true;}
      if(bbCzTmUpLz == RLkBJdmdNY){VdkyBOoCrY = true;}
      else if(RLkBJdmdNY == bbCzTmUpLz){ZrtwtHWDaw = true;}
      if(EkrOMPyQRM == oQwQgjBgwP){ifhrdlzUrX = true;}
      else if(oQwQgjBgwP == EkrOMPyQRM){tCGChBWQrm = true;}
      if(NcrpkTFYnt == ZOgdXOHFRV){jQHLwUrCjl = true;}
      else if(ZOgdXOHFRV == NcrpkTFYnt){JfISZPiWru = true;}
      if(qRNDrlGCFq == eFAbeHLsMq){TRIEPmyiok = true;}
      else if(eFAbeHLsMq == qRNDrlGCFq){JJjsZGZSHG = true;}
      if(TrTZanAIcR == FitiDlyXXZ){gwGnqxVWmh = true;}
      else if(FitiDlyXXZ == TrTZanAIcR){uEPXPNRdZM = true;}
      if(ZyEGtyiLNA == VJGCODdHdt){XBJRjFVZCg = true;}
      else if(VJGCODdHdt == ZyEGtyiLNA){XMIwQsibVe = true;}
      if(gwCQIlWoWa == WgMrsiPUlZ){WlSFEQXccq = true;}
      if(IuKarVISPw == XHUEJpTyZl){nQeGpmKSTz = true;}
      if(SxuVUrMHIs == QjhqzVzyMa){yUOBNRHqUJ = true;}
      while(WgMrsiPUlZ == gwCQIlWoWa){XzKfmjSNcb = true;}
      while(XHUEJpTyZl == XHUEJpTyZl){bEJkrEQkDM = true;}
      while(QjhqzVzyMa == QjhqzVzyMa){xFxeWxBnbf = true;}
      if(cDPRUXWCoU == true){cDPRUXWCoU = false;}
      if(VdkyBOoCrY == true){VdkyBOoCrY = false;}
      if(ifhrdlzUrX == true){ifhrdlzUrX = false;}
      if(jQHLwUrCjl == true){jQHLwUrCjl = false;}
      if(TRIEPmyiok == true){TRIEPmyiok = false;}
      if(gwGnqxVWmh == true){gwGnqxVWmh = false;}
      if(XBJRjFVZCg == true){XBJRjFVZCg = false;}
      if(WlSFEQXccq == true){WlSFEQXccq = false;}
      if(nQeGpmKSTz == true){nQeGpmKSTz = false;}
      if(yUOBNRHqUJ == true){yUOBNRHqUJ = false;}
      if(QYgIOudAiZ == true){QYgIOudAiZ = false;}
      if(ZrtwtHWDaw == true){ZrtwtHWDaw = false;}
      if(tCGChBWQrm == true){tCGChBWQrm = false;}
      if(JfISZPiWru == true){JfISZPiWru = false;}
      if(JJjsZGZSHG == true){JJjsZGZSHG = false;}
      if(uEPXPNRdZM == true){uEPXPNRdZM = false;}
      if(XMIwQsibVe == true){XMIwQsibVe = false;}
      if(XzKfmjSNcb == true){XzKfmjSNcb = false;}
      if(bEJkrEQkDM == true){bEJkrEQkDM = false;}
      if(xFxeWxBnbf == true){xFxeWxBnbf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JFMKDIJHBD
{ 
  void WDDUXaWTQI()
  { 
      bool OVgRapenVh = false;
      bool RqmUeorbaC = false;
      bool NMtaAhadUa = false;
      bool yNftwGqMAF = false;
      bool YdlskMxOdc = false;
      bool LoHhJBaGRr = false;
      bool OAStjDKrXY = false;
      bool yfbUcjaAom = false;
      bool jMAqOIGykt = false;
      bool ejuHqXKqJg = false;
      bool BFpFefNmEY = false;
      bool aaQdICAbfa = false;
      bool xMGdtNkUdF = false;
      bool ZipIkeVuLi = false;
      bool uTtLTDTQyn = false;
      bool XhLijoyMKR = false;
      bool trIyzqjIrd = false;
      bool gFPwedSuJp = false;
      bool sTVohqXHYw = false;
      bool fIjtnCKuMb = false;
      string kRIxGLHKCR;
      string HCGgQoOXwh;
      string AaYJXNliSI;
      string NhZhkGjcha;
      string DLnKEqlVnd;
      string gOrzQKryZs;
      string YYqtEYbXuK;
      string ElpVdolOEf;
      string aQuoazpaRa;
      string NkDnBeTtFf;
      string POZcZuXWVa;
      string XdtsRIcCSF;
      string iBGUwShBTy;
      string UrIYQMpRPf;
      string aTFpCjqJWs;
      string CRaAxNHFgG;
      string MWCWFeUVcE;
      string SLmmeOwQRL;
      string bXdawDRHaC;
      string EjjISDQhjW;
      if(kRIxGLHKCR == POZcZuXWVa){OVgRapenVh = true;}
      else if(POZcZuXWVa == kRIxGLHKCR){BFpFefNmEY = true;}
      if(HCGgQoOXwh == XdtsRIcCSF){RqmUeorbaC = true;}
      else if(XdtsRIcCSF == HCGgQoOXwh){aaQdICAbfa = true;}
      if(AaYJXNliSI == iBGUwShBTy){NMtaAhadUa = true;}
      else if(iBGUwShBTy == AaYJXNliSI){xMGdtNkUdF = true;}
      if(NhZhkGjcha == UrIYQMpRPf){yNftwGqMAF = true;}
      else if(UrIYQMpRPf == NhZhkGjcha){ZipIkeVuLi = true;}
      if(DLnKEqlVnd == aTFpCjqJWs){YdlskMxOdc = true;}
      else if(aTFpCjqJWs == DLnKEqlVnd){uTtLTDTQyn = true;}
      if(gOrzQKryZs == CRaAxNHFgG){LoHhJBaGRr = true;}
      else if(CRaAxNHFgG == gOrzQKryZs){XhLijoyMKR = true;}
      if(YYqtEYbXuK == MWCWFeUVcE){OAStjDKrXY = true;}
      else if(MWCWFeUVcE == YYqtEYbXuK){trIyzqjIrd = true;}
      if(ElpVdolOEf == SLmmeOwQRL){yfbUcjaAom = true;}
      if(aQuoazpaRa == bXdawDRHaC){jMAqOIGykt = true;}
      if(NkDnBeTtFf == EjjISDQhjW){ejuHqXKqJg = true;}
      while(SLmmeOwQRL == ElpVdolOEf){gFPwedSuJp = true;}
      while(bXdawDRHaC == bXdawDRHaC){sTVohqXHYw = true;}
      while(EjjISDQhjW == EjjISDQhjW){fIjtnCKuMb = true;}
      if(OVgRapenVh == true){OVgRapenVh = false;}
      if(RqmUeorbaC == true){RqmUeorbaC = false;}
      if(NMtaAhadUa == true){NMtaAhadUa = false;}
      if(yNftwGqMAF == true){yNftwGqMAF = false;}
      if(YdlskMxOdc == true){YdlskMxOdc = false;}
      if(LoHhJBaGRr == true){LoHhJBaGRr = false;}
      if(OAStjDKrXY == true){OAStjDKrXY = false;}
      if(yfbUcjaAom == true){yfbUcjaAom = false;}
      if(jMAqOIGykt == true){jMAqOIGykt = false;}
      if(ejuHqXKqJg == true){ejuHqXKqJg = false;}
      if(BFpFefNmEY == true){BFpFefNmEY = false;}
      if(aaQdICAbfa == true){aaQdICAbfa = false;}
      if(xMGdtNkUdF == true){xMGdtNkUdF = false;}
      if(ZipIkeVuLi == true){ZipIkeVuLi = false;}
      if(uTtLTDTQyn == true){uTtLTDTQyn = false;}
      if(XhLijoyMKR == true){XhLijoyMKR = false;}
      if(trIyzqjIrd == true){trIyzqjIrd = false;}
      if(gFPwedSuJp == true){gFPwedSuJp = false;}
      if(sTVohqXHYw == true){sTVohqXHYw = false;}
      if(fIjtnCKuMb == true){fIjtnCKuMb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIOYBQWIKV
{ 
  void IknHpspdNY()
  { 
      bool NnaFbMrPFc = false;
      bool eafQXEVUrd = false;
      bool ykaAFmRGRn = false;
      bool iMEyeYZFwW = false;
      bool uiXTAQTFfG = false;
      bool jJpxzcNZAn = false;
      bool tlxRtRVgkz = false;
      bool ePXUhPMGAo = false;
      bool SLaKEYVHzC = false;
      bool KzFHcIkGZh = false;
      bool tlTfbTkUOj = false;
      bool PHZLUiLmMV = false;
      bool wOhinfKQrY = false;
      bool dGgRufrthj = false;
      bool mArOmDYtls = false;
      bool xxtDleEkrw = false;
      bool JUcpFJZHQn = false;
      bool qRFbhuWSwk = false;
      bool GQeybgMceP = false;
      bool bGBlaSXCJc = false;
      string IYDoKBQGZS;
      string mWXXVAipKI;
      string oqQbIiojIA;
      string yBpzzdAcaq;
      string CxNDNQEsXJ;
      string TMyRyQHbfa;
      string MgxZTlfYYr;
      string zFPSFqdNOr;
      string ewMzfkCXAh;
      string VYwzeVAmia;
      string jfTfKOxfMH;
      string msMnwPUyth;
      string jIYqVZIPmj;
      string pqenHycgnQ;
      string nWLrtcMHDO;
      string ACrApbHcJk;
      string FhrbRwOXgx;
      string mnJctMwfws;
      string MALXinydxf;
      string qzWDLFdiax;
      if(IYDoKBQGZS == jfTfKOxfMH){NnaFbMrPFc = true;}
      else if(jfTfKOxfMH == IYDoKBQGZS){tlTfbTkUOj = true;}
      if(mWXXVAipKI == msMnwPUyth){eafQXEVUrd = true;}
      else if(msMnwPUyth == mWXXVAipKI){PHZLUiLmMV = true;}
      if(oqQbIiojIA == jIYqVZIPmj){ykaAFmRGRn = true;}
      else if(jIYqVZIPmj == oqQbIiojIA){wOhinfKQrY = true;}
      if(yBpzzdAcaq == pqenHycgnQ){iMEyeYZFwW = true;}
      else if(pqenHycgnQ == yBpzzdAcaq){dGgRufrthj = true;}
      if(CxNDNQEsXJ == nWLrtcMHDO){uiXTAQTFfG = true;}
      else if(nWLrtcMHDO == CxNDNQEsXJ){mArOmDYtls = true;}
      if(TMyRyQHbfa == ACrApbHcJk){jJpxzcNZAn = true;}
      else if(ACrApbHcJk == TMyRyQHbfa){xxtDleEkrw = true;}
      if(MgxZTlfYYr == FhrbRwOXgx){tlxRtRVgkz = true;}
      else if(FhrbRwOXgx == MgxZTlfYYr){JUcpFJZHQn = true;}
      if(zFPSFqdNOr == mnJctMwfws){ePXUhPMGAo = true;}
      if(ewMzfkCXAh == MALXinydxf){SLaKEYVHzC = true;}
      if(VYwzeVAmia == qzWDLFdiax){KzFHcIkGZh = true;}
      while(mnJctMwfws == zFPSFqdNOr){qRFbhuWSwk = true;}
      while(MALXinydxf == MALXinydxf){GQeybgMceP = true;}
      while(qzWDLFdiax == qzWDLFdiax){bGBlaSXCJc = true;}
      if(NnaFbMrPFc == true){NnaFbMrPFc = false;}
      if(eafQXEVUrd == true){eafQXEVUrd = false;}
      if(ykaAFmRGRn == true){ykaAFmRGRn = false;}
      if(iMEyeYZFwW == true){iMEyeYZFwW = false;}
      if(uiXTAQTFfG == true){uiXTAQTFfG = false;}
      if(jJpxzcNZAn == true){jJpxzcNZAn = false;}
      if(tlxRtRVgkz == true){tlxRtRVgkz = false;}
      if(ePXUhPMGAo == true){ePXUhPMGAo = false;}
      if(SLaKEYVHzC == true){SLaKEYVHzC = false;}
      if(KzFHcIkGZh == true){KzFHcIkGZh = false;}
      if(tlTfbTkUOj == true){tlTfbTkUOj = false;}
      if(PHZLUiLmMV == true){PHZLUiLmMV = false;}
      if(wOhinfKQrY == true){wOhinfKQrY = false;}
      if(dGgRufrthj == true){dGgRufrthj = false;}
      if(mArOmDYtls == true){mArOmDYtls = false;}
      if(xxtDleEkrw == true){xxtDleEkrw = false;}
      if(JUcpFJZHQn == true){JUcpFJZHQn = false;}
      if(qRFbhuWSwk == true){qRFbhuWSwk = false;}
      if(GQeybgMceP == true){GQeybgMceP = false;}
      if(bGBlaSXCJc == true){bGBlaSXCJc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUIVPMZHYQ
{ 
  void rOYbFLlndY()
  { 
      bool yYWyGBweKy = false;
      bool ARwKApaDtp = false;
      bool TMmWGarTMs = false;
      bool EExxRsAUAf = false;
      bool lgRYSrlzya = false;
      bool WcfWbklAqe = false;
      bool IbSRtwUyrH = false;
      bool pFDOEmuODO = false;
      bool osUkVbXaVg = false;
      bool HzcUWJOAdW = false;
      bool XmGqkQYRRo = false;
      bool pWwbpPGhuS = false;
      bool XscLzqciru = false;
      bool XujgqCldAF = false;
      bool CGIgpjDBdH = false;
      bool CfELydKtqs = false;
      bool npYWQulOkn = false;
      bool cchpPQkuUP = false;
      bool nbEkrrpYiN = false;
      bool qrlGRMgkQu = false;
      string ufaiPdLoIz;
      string mGogEyxluV;
      string XAyldxHIQS;
      string xiGgbqqIkW;
      string tYJkROjTsc;
      string mdHoWthnFR;
      string WCYoBEzIFN;
      string GnBXbyqNUO;
      string NmPneTaQKg;
      string IDDSAqATiM;
      string PaOeVzbiNX;
      string DUSpDimkKh;
      string ciyXEDkhXk;
      string yWdHzmYjRf;
      string qrDmcnjNOQ;
      string DPJBjfcpaS;
      string NtLbYgpLpQ;
      string JCSdpkfKtP;
      string SWSHghMcXT;
      string JhJzRxgaNw;
      if(ufaiPdLoIz == PaOeVzbiNX){yYWyGBweKy = true;}
      else if(PaOeVzbiNX == ufaiPdLoIz){XmGqkQYRRo = true;}
      if(mGogEyxluV == DUSpDimkKh){ARwKApaDtp = true;}
      else if(DUSpDimkKh == mGogEyxluV){pWwbpPGhuS = true;}
      if(XAyldxHIQS == ciyXEDkhXk){TMmWGarTMs = true;}
      else if(ciyXEDkhXk == XAyldxHIQS){XscLzqciru = true;}
      if(xiGgbqqIkW == yWdHzmYjRf){EExxRsAUAf = true;}
      else if(yWdHzmYjRf == xiGgbqqIkW){XujgqCldAF = true;}
      if(tYJkROjTsc == qrDmcnjNOQ){lgRYSrlzya = true;}
      else if(qrDmcnjNOQ == tYJkROjTsc){CGIgpjDBdH = true;}
      if(mdHoWthnFR == DPJBjfcpaS){WcfWbklAqe = true;}
      else if(DPJBjfcpaS == mdHoWthnFR){CfELydKtqs = true;}
      if(WCYoBEzIFN == NtLbYgpLpQ){IbSRtwUyrH = true;}
      else if(NtLbYgpLpQ == WCYoBEzIFN){npYWQulOkn = true;}
      if(GnBXbyqNUO == JCSdpkfKtP){pFDOEmuODO = true;}
      if(NmPneTaQKg == SWSHghMcXT){osUkVbXaVg = true;}
      if(IDDSAqATiM == JhJzRxgaNw){HzcUWJOAdW = true;}
      while(JCSdpkfKtP == GnBXbyqNUO){cchpPQkuUP = true;}
      while(SWSHghMcXT == SWSHghMcXT){nbEkrrpYiN = true;}
      while(JhJzRxgaNw == JhJzRxgaNw){qrlGRMgkQu = true;}
      if(yYWyGBweKy == true){yYWyGBweKy = false;}
      if(ARwKApaDtp == true){ARwKApaDtp = false;}
      if(TMmWGarTMs == true){TMmWGarTMs = false;}
      if(EExxRsAUAf == true){EExxRsAUAf = false;}
      if(lgRYSrlzya == true){lgRYSrlzya = false;}
      if(WcfWbklAqe == true){WcfWbklAqe = false;}
      if(IbSRtwUyrH == true){IbSRtwUyrH = false;}
      if(pFDOEmuODO == true){pFDOEmuODO = false;}
      if(osUkVbXaVg == true){osUkVbXaVg = false;}
      if(HzcUWJOAdW == true){HzcUWJOAdW = false;}
      if(XmGqkQYRRo == true){XmGqkQYRRo = false;}
      if(pWwbpPGhuS == true){pWwbpPGhuS = false;}
      if(XscLzqciru == true){XscLzqciru = false;}
      if(XujgqCldAF == true){XujgqCldAF = false;}
      if(CGIgpjDBdH == true){CGIgpjDBdH = false;}
      if(CfELydKtqs == true){CfELydKtqs = false;}
      if(npYWQulOkn == true){npYWQulOkn = false;}
      if(cchpPQkuUP == true){cchpPQkuUP = false;}
      if(nbEkrrpYiN == true){nbEkrrpYiN = false;}
      if(qrlGRMgkQu == true){qrlGRMgkQu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOYSUJCVWT
{ 
  void jReuhhEDOa()
  { 
      bool nHMneGgaiB = false;
      bool rRAkRjbxkM = false;
      bool EQyWChNngG = false;
      bool lNQwTAVhnC = false;
      bool epYDQidXdQ = false;
      bool oxdfBXIpkw = false;
      bool rrscOdBDRQ = false;
      bool NsIhgNruFS = false;
      bool EpKPQojjuw = false;
      bool rfxqJlxuol = false;
      bool gZGMDwnuzm = false;
      bool fMkSrChcLY = false;
      bool tQIVYhwQYt = false;
      bool QwGSldjxMU = false;
      bool BokHPetdzG = false;
      bool EUiQrPRjnV = false;
      bool AWVEWjGRgN = false;
      bool SkPqWEfAFs = false;
      bool mRRRpwMpZV = false;
      bool LzIqTeSgkf = false;
      string xQdRsEtwMk;
      string ClbDZZiTug;
      string wPRYUguEas;
      string WTKdDBFBiw;
      string rseIKhBgmM;
      string cwcVHgyExL;
      string IoUSNiayAX;
      string TgjzoDkJOl;
      string fOQOQapoVW;
      string CBEWmCYLta;
      string HDgOrwLdgE;
      string uopLftYGCm;
      string slbdVScNMl;
      string eZPmecgBVT;
      string PLIRaNKsqr;
      string cRIHhVbDsZ;
      string SyRtYUYDfD;
      string MWjhXgcJCH;
      string HiVTIMQIEJ;
      string BdIwAQtOsF;
      if(xQdRsEtwMk == HDgOrwLdgE){nHMneGgaiB = true;}
      else if(HDgOrwLdgE == xQdRsEtwMk){gZGMDwnuzm = true;}
      if(ClbDZZiTug == uopLftYGCm){rRAkRjbxkM = true;}
      else if(uopLftYGCm == ClbDZZiTug){fMkSrChcLY = true;}
      if(wPRYUguEas == slbdVScNMl){EQyWChNngG = true;}
      else if(slbdVScNMl == wPRYUguEas){tQIVYhwQYt = true;}
      if(WTKdDBFBiw == eZPmecgBVT){lNQwTAVhnC = true;}
      else if(eZPmecgBVT == WTKdDBFBiw){QwGSldjxMU = true;}
      if(rseIKhBgmM == PLIRaNKsqr){epYDQidXdQ = true;}
      else if(PLIRaNKsqr == rseIKhBgmM){BokHPetdzG = true;}
      if(cwcVHgyExL == cRIHhVbDsZ){oxdfBXIpkw = true;}
      else if(cRIHhVbDsZ == cwcVHgyExL){EUiQrPRjnV = true;}
      if(IoUSNiayAX == SyRtYUYDfD){rrscOdBDRQ = true;}
      else if(SyRtYUYDfD == IoUSNiayAX){AWVEWjGRgN = true;}
      if(TgjzoDkJOl == MWjhXgcJCH){NsIhgNruFS = true;}
      if(fOQOQapoVW == HiVTIMQIEJ){EpKPQojjuw = true;}
      if(CBEWmCYLta == BdIwAQtOsF){rfxqJlxuol = true;}
      while(MWjhXgcJCH == TgjzoDkJOl){SkPqWEfAFs = true;}
      while(HiVTIMQIEJ == HiVTIMQIEJ){mRRRpwMpZV = true;}
      while(BdIwAQtOsF == BdIwAQtOsF){LzIqTeSgkf = true;}
      if(nHMneGgaiB == true){nHMneGgaiB = false;}
      if(rRAkRjbxkM == true){rRAkRjbxkM = false;}
      if(EQyWChNngG == true){EQyWChNngG = false;}
      if(lNQwTAVhnC == true){lNQwTAVhnC = false;}
      if(epYDQidXdQ == true){epYDQidXdQ = false;}
      if(oxdfBXIpkw == true){oxdfBXIpkw = false;}
      if(rrscOdBDRQ == true){rrscOdBDRQ = false;}
      if(NsIhgNruFS == true){NsIhgNruFS = false;}
      if(EpKPQojjuw == true){EpKPQojjuw = false;}
      if(rfxqJlxuol == true){rfxqJlxuol = false;}
      if(gZGMDwnuzm == true){gZGMDwnuzm = false;}
      if(fMkSrChcLY == true){fMkSrChcLY = false;}
      if(tQIVYhwQYt == true){tQIVYhwQYt = false;}
      if(QwGSldjxMU == true){QwGSldjxMU = false;}
      if(BokHPetdzG == true){BokHPetdzG = false;}
      if(EUiQrPRjnV == true){EUiQrPRjnV = false;}
      if(AWVEWjGRgN == true){AWVEWjGRgN = false;}
      if(SkPqWEfAFs == true){SkPqWEfAFs = false;}
      if(mRRRpwMpZV == true){mRRRpwMpZV = false;}
      if(LzIqTeSgkf == true){LzIqTeSgkf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWBEDDVILE
{ 
  void LyWppyckhJ()
  { 
      bool LTLkAJRIFH = false;
      bool HayBrqxbTA = false;
      bool lYuiVYuFAb = false;
      bool HUiNsDuMlP = false;
      bool YmxUbQZpWr = false;
      bool cCFCPlYbPb = false;
      bool NLIdAlqkIo = false;
      bool ukpEayaZGE = false;
      bool yFhHzEOgyG = false;
      bool dTwJBMeTTo = false;
      bool ZohgwqLAaQ = false;
      bool LyULdIdAeu = false;
      bool XKlCLbogDO = false;
      bool SHFQdIXBLH = false;
      bool sOFgufyker = false;
      bool ienYRPDeVT = false;
      bool CewMxDrEgV = false;
      bool kboWCJEEHe = false;
      bool dDBLenSgzO = false;
      bool FreqFORrjq = false;
      string XrsdIOLzRI;
      string sOxoggRytk;
      string OzLAUpaXod;
      string VRNBfKftjX;
      string axzTCRpXXf;
      string JGWblXgsJR;
      string nnJmmbAwIW;
      string BXOVKQArxD;
      string zCAJUOukPI;
      string cmkRjlmLfa;
      string QtOAdlrARU;
      string XnuFSknASX;
      string fOgAsOmwkX;
      string doLWlFmzei;
      string VtTtjoqeyy;
      string ymrHtCNOGP;
      string zuPsqicXTN;
      string xnUjCltlPE;
      string WHxmYpwDcj;
      string rYrPjZeZDB;
      if(XrsdIOLzRI == QtOAdlrARU){LTLkAJRIFH = true;}
      else if(QtOAdlrARU == XrsdIOLzRI){ZohgwqLAaQ = true;}
      if(sOxoggRytk == XnuFSknASX){HayBrqxbTA = true;}
      else if(XnuFSknASX == sOxoggRytk){LyULdIdAeu = true;}
      if(OzLAUpaXod == fOgAsOmwkX){lYuiVYuFAb = true;}
      else if(fOgAsOmwkX == OzLAUpaXod){XKlCLbogDO = true;}
      if(VRNBfKftjX == doLWlFmzei){HUiNsDuMlP = true;}
      else if(doLWlFmzei == VRNBfKftjX){SHFQdIXBLH = true;}
      if(axzTCRpXXf == VtTtjoqeyy){YmxUbQZpWr = true;}
      else if(VtTtjoqeyy == axzTCRpXXf){sOFgufyker = true;}
      if(JGWblXgsJR == ymrHtCNOGP){cCFCPlYbPb = true;}
      else if(ymrHtCNOGP == JGWblXgsJR){ienYRPDeVT = true;}
      if(nnJmmbAwIW == zuPsqicXTN){NLIdAlqkIo = true;}
      else if(zuPsqicXTN == nnJmmbAwIW){CewMxDrEgV = true;}
      if(BXOVKQArxD == xnUjCltlPE){ukpEayaZGE = true;}
      if(zCAJUOukPI == WHxmYpwDcj){yFhHzEOgyG = true;}
      if(cmkRjlmLfa == rYrPjZeZDB){dTwJBMeTTo = true;}
      while(xnUjCltlPE == BXOVKQArxD){kboWCJEEHe = true;}
      while(WHxmYpwDcj == WHxmYpwDcj){dDBLenSgzO = true;}
      while(rYrPjZeZDB == rYrPjZeZDB){FreqFORrjq = true;}
      if(LTLkAJRIFH == true){LTLkAJRIFH = false;}
      if(HayBrqxbTA == true){HayBrqxbTA = false;}
      if(lYuiVYuFAb == true){lYuiVYuFAb = false;}
      if(HUiNsDuMlP == true){HUiNsDuMlP = false;}
      if(YmxUbQZpWr == true){YmxUbQZpWr = false;}
      if(cCFCPlYbPb == true){cCFCPlYbPb = false;}
      if(NLIdAlqkIo == true){NLIdAlqkIo = false;}
      if(ukpEayaZGE == true){ukpEayaZGE = false;}
      if(yFhHzEOgyG == true){yFhHzEOgyG = false;}
      if(dTwJBMeTTo == true){dTwJBMeTTo = false;}
      if(ZohgwqLAaQ == true){ZohgwqLAaQ = false;}
      if(LyULdIdAeu == true){LyULdIdAeu = false;}
      if(XKlCLbogDO == true){XKlCLbogDO = false;}
      if(SHFQdIXBLH == true){SHFQdIXBLH = false;}
      if(sOFgufyker == true){sOFgufyker = false;}
      if(ienYRPDeVT == true){ienYRPDeVT = false;}
      if(CewMxDrEgV == true){CewMxDrEgV = false;}
      if(kboWCJEEHe == true){kboWCJEEHe = false;}
      if(dDBLenSgzO == true){dDBLenSgzO = false;}
      if(FreqFORrjq == true){FreqFORrjq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHRFRKHRNU
{ 
  void HBouHPdBth()
  { 
      bool DCqphOqUuU = false;
      bool JeopjHkdBh = false;
      bool ECuIRxpCua = false;
      bool BpzkBYzXGf = false;
      bool KPtksaWxWF = false;
      bool juXLOAGiXj = false;
      bool XoYUSTfDoK = false;
      bool IMXVWoIJOq = false;
      bool aseppFSmWA = false;
      bool RPzVHUpZSZ = false;
      bool tSILxWWBnY = false;
      bool qwUgJeJieM = false;
      bool AsgnsrMCOC = false;
      bool ziqnwHjTrS = false;
      bool iRzxJVtSLc = false;
      bool KGuFYBkTSF = false;
      bool JUmkZIEfjB = false;
      bool tppLdisjeW = false;
      bool xtpkqrnlPt = false;
      bool VQBmIOeNWA = false;
      string DUMXZIkOLX;
      string mbQBFONfOr;
      string klGqrBkthl;
      string MbjfdjbYnc;
      string xHXRaCdbQb;
      string hSkdPRNUeY;
      string WqgYKLqkXV;
      string lnqltdNnQo;
      string WIdGEtqFPL;
      string VHsPFGayHP;
      string LsEuosayjl;
      string DZDpBNNZUP;
      string TkVLAetbfm;
      string COgBddEhQL;
      string TrVcHwDDNq;
      string sAdquZXrtK;
      string yySwjorBLX;
      string JeIIuaPrDE;
      string aqNntCjoGD;
      string GLnGMUZYsS;
      if(DUMXZIkOLX == LsEuosayjl){DCqphOqUuU = true;}
      else if(LsEuosayjl == DUMXZIkOLX){tSILxWWBnY = true;}
      if(mbQBFONfOr == DZDpBNNZUP){JeopjHkdBh = true;}
      else if(DZDpBNNZUP == mbQBFONfOr){qwUgJeJieM = true;}
      if(klGqrBkthl == TkVLAetbfm){ECuIRxpCua = true;}
      else if(TkVLAetbfm == klGqrBkthl){AsgnsrMCOC = true;}
      if(MbjfdjbYnc == COgBddEhQL){BpzkBYzXGf = true;}
      else if(COgBddEhQL == MbjfdjbYnc){ziqnwHjTrS = true;}
      if(xHXRaCdbQb == TrVcHwDDNq){KPtksaWxWF = true;}
      else if(TrVcHwDDNq == xHXRaCdbQb){iRzxJVtSLc = true;}
      if(hSkdPRNUeY == sAdquZXrtK){juXLOAGiXj = true;}
      else if(sAdquZXrtK == hSkdPRNUeY){KGuFYBkTSF = true;}
      if(WqgYKLqkXV == yySwjorBLX){XoYUSTfDoK = true;}
      else if(yySwjorBLX == WqgYKLqkXV){JUmkZIEfjB = true;}
      if(lnqltdNnQo == JeIIuaPrDE){IMXVWoIJOq = true;}
      if(WIdGEtqFPL == aqNntCjoGD){aseppFSmWA = true;}
      if(VHsPFGayHP == GLnGMUZYsS){RPzVHUpZSZ = true;}
      while(JeIIuaPrDE == lnqltdNnQo){tppLdisjeW = true;}
      while(aqNntCjoGD == aqNntCjoGD){xtpkqrnlPt = true;}
      while(GLnGMUZYsS == GLnGMUZYsS){VQBmIOeNWA = true;}
      if(DCqphOqUuU == true){DCqphOqUuU = false;}
      if(JeopjHkdBh == true){JeopjHkdBh = false;}
      if(ECuIRxpCua == true){ECuIRxpCua = false;}
      if(BpzkBYzXGf == true){BpzkBYzXGf = false;}
      if(KPtksaWxWF == true){KPtksaWxWF = false;}
      if(juXLOAGiXj == true){juXLOAGiXj = false;}
      if(XoYUSTfDoK == true){XoYUSTfDoK = false;}
      if(IMXVWoIJOq == true){IMXVWoIJOq = false;}
      if(aseppFSmWA == true){aseppFSmWA = false;}
      if(RPzVHUpZSZ == true){RPzVHUpZSZ = false;}
      if(tSILxWWBnY == true){tSILxWWBnY = false;}
      if(qwUgJeJieM == true){qwUgJeJieM = false;}
      if(AsgnsrMCOC == true){AsgnsrMCOC = false;}
      if(ziqnwHjTrS == true){ziqnwHjTrS = false;}
      if(iRzxJVtSLc == true){iRzxJVtSLc = false;}
      if(KGuFYBkTSF == true){KGuFYBkTSF = false;}
      if(JUmkZIEfjB == true){JUmkZIEfjB = false;}
      if(tppLdisjeW == true){tppLdisjeW = false;}
      if(xtpkqrnlPt == true){xtpkqrnlPt = false;}
      if(VQBmIOeNWA == true){VQBmIOeNWA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLMSAKKPFV
{ 
  void KsqXyHRxjQ()
  { 
      bool UPrtGkuIiO = false;
      bool PhHkMnjsZJ = false;
      bool SPkZcGbymc = false;
      bool ZkUtMCLzbq = false;
      bool doNOkFgrrZ = false;
      bool IHXYCEeRRz = false;
      bool JxUGneNNYK = false;
      bool bkQhfdCWoX = false;
      bool ZjFNTSMuqH = false;
      bool XthchgTHZG = false;
      bool rSShyXppsY = false;
      bool CHctZYqHlV = false;
      bool SRVQmhCnAy = false;
      bool JtwieGQXPu = false;
      bool cWCSFPQnDI = false;
      bool oMVEnZxCuP = false;
      bool VCotOHKtOS = false;
      bool ITqpruODLW = false;
      bool QOjqJxYruF = false;
      bool JOczZagIEy = false;
      string ThlYRVyEjK;
      string nHEVhLSkAb;
      string IVMuSrZWAF;
      string FwCDIUCAbF;
      string RswHjlJmtl;
      string htHfZyVqGZ;
      string ubEdFrEAMN;
      string IRJtJPZEKf;
      string hmbOWKoVdK;
      string yLsCKpoRBr;
      string gIZgcQkMVK;
      string YQgZqIzoHu;
      string DiWCOxXGjT;
      string ZHDRzZMtkG;
      string YbATlheTLB;
      string pzJFoylXRf;
      string rebCjQNOaQ;
      string uEDBWahDPg;
      string SEthcZxxcA;
      string nocFNsAxiV;
      if(ThlYRVyEjK == gIZgcQkMVK){UPrtGkuIiO = true;}
      else if(gIZgcQkMVK == ThlYRVyEjK){rSShyXppsY = true;}
      if(nHEVhLSkAb == YQgZqIzoHu){PhHkMnjsZJ = true;}
      else if(YQgZqIzoHu == nHEVhLSkAb){CHctZYqHlV = true;}
      if(IVMuSrZWAF == DiWCOxXGjT){SPkZcGbymc = true;}
      else if(DiWCOxXGjT == IVMuSrZWAF){SRVQmhCnAy = true;}
      if(FwCDIUCAbF == ZHDRzZMtkG){ZkUtMCLzbq = true;}
      else if(ZHDRzZMtkG == FwCDIUCAbF){JtwieGQXPu = true;}
      if(RswHjlJmtl == YbATlheTLB){doNOkFgrrZ = true;}
      else if(YbATlheTLB == RswHjlJmtl){cWCSFPQnDI = true;}
      if(htHfZyVqGZ == pzJFoylXRf){IHXYCEeRRz = true;}
      else if(pzJFoylXRf == htHfZyVqGZ){oMVEnZxCuP = true;}
      if(ubEdFrEAMN == rebCjQNOaQ){JxUGneNNYK = true;}
      else if(rebCjQNOaQ == ubEdFrEAMN){VCotOHKtOS = true;}
      if(IRJtJPZEKf == uEDBWahDPg){bkQhfdCWoX = true;}
      if(hmbOWKoVdK == SEthcZxxcA){ZjFNTSMuqH = true;}
      if(yLsCKpoRBr == nocFNsAxiV){XthchgTHZG = true;}
      while(uEDBWahDPg == IRJtJPZEKf){ITqpruODLW = true;}
      while(SEthcZxxcA == SEthcZxxcA){QOjqJxYruF = true;}
      while(nocFNsAxiV == nocFNsAxiV){JOczZagIEy = true;}
      if(UPrtGkuIiO == true){UPrtGkuIiO = false;}
      if(PhHkMnjsZJ == true){PhHkMnjsZJ = false;}
      if(SPkZcGbymc == true){SPkZcGbymc = false;}
      if(ZkUtMCLzbq == true){ZkUtMCLzbq = false;}
      if(doNOkFgrrZ == true){doNOkFgrrZ = false;}
      if(IHXYCEeRRz == true){IHXYCEeRRz = false;}
      if(JxUGneNNYK == true){JxUGneNNYK = false;}
      if(bkQhfdCWoX == true){bkQhfdCWoX = false;}
      if(ZjFNTSMuqH == true){ZjFNTSMuqH = false;}
      if(XthchgTHZG == true){XthchgTHZG = false;}
      if(rSShyXppsY == true){rSShyXppsY = false;}
      if(CHctZYqHlV == true){CHctZYqHlV = false;}
      if(SRVQmhCnAy == true){SRVQmhCnAy = false;}
      if(JtwieGQXPu == true){JtwieGQXPu = false;}
      if(cWCSFPQnDI == true){cWCSFPQnDI = false;}
      if(oMVEnZxCuP == true){oMVEnZxCuP = false;}
      if(VCotOHKtOS == true){VCotOHKtOS = false;}
      if(ITqpruODLW == true){ITqpruODLW = false;}
      if(QOjqJxYruF == true){QOjqJxYruF = false;}
      if(JOczZagIEy == true){JOczZagIEy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LZKYFCLBEK
{ 
  void lnWxhxQlXX()
  { 
      bool IGYHZOZdSh = false;
      bool XpaxMiRlpq = false;
      bool yoIwMkTmLF = false;
      bool UgDrunjsnO = false;
      bool GPdOiPpHGS = false;
      bool TGpdDTybuo = false;
      bool tmRNMqlhCY = false;
      bool yXxbkhKsNw = false;
      bool tMfrlNqZob = false;
      bool oIyzTTxQCr = false;
      bool cHEgUuJOsU = false;
      bool IEOythGZby = false;
      bool AMsZjpYyHQ = false;
      bool jtqUSmHzXp = false;
      bool EbgTSjsAEl = false;
      bool MXnDrQNexd = false;
      bool VKHbjNNseH = false;
      bool aGBktXeZHz = false;
      bool wYtVEMGncB = false;
      bool YcBsTtUFjF = false;
      string YSmmcKmsli;
      string hDkylSXDPk;
      string MMMtwhWAUI;
      string nnCokwCOKF;
      string DkcAxCdYre;
      string knCQLMGsqt;
      string mmXdutAwNp;
      string PIrJgaiMwt;
      string EyIpWzlkdX;
      string pIXQSQNyFD;
      string BhKBOcurjk;
      string ctxwoodgHu;
      string HPRoAGkbqP;
      string MkHrsVmGat;
      string EsBstuLbac;
      string lfqJulPVBH;
      string rSATXrmEDS;
      string CXGNpNNYtE;
      string uIBOcgsxwG;
      string GRESBksgUC;
      if(YSmmcKmsli == BhKBOcurjk){IGYHZOZdSh = true;}
      else if(BhKBOcurjk == YSmmcKmsli){cHEgUuJOsU = true;}
      if(hDkylSXDPk == ctxwoodgHu){XpaxMiRlpq = true;}
      else if(ctxwoodgHu == hDkylSXDPk){IEOythGZby = true;}
      if(MMMtwhWAUI == HPRoAGkbqP){yoIwMkTmLF = true;}
      else if(HPRoAGkbqP == MMMtwhWAUI){AMsZjpYyHQ = true;}
      if(nnCokwCOKF == MkHrsVmGat){UgDrunjsnO = true;}
      else if(MkHrsVmGat == nnCokwCOKF){jtqUSmHzXp = true;}
      if(DkcAxCdYre == EsBstuLbac){GPdOiPpHGS = true;}
      else if(EsBstuLbac == DkcAxCdYre){EbgTSjsAEl = true;}
      if(knCQLMGsqt == lfqJulPVBH){TGpdDTybuo = true;}
      else if(lfqJulPVBH == knCQLMGsqt){MXnDrQNexd = true;}
      if(mmXdutAwNp == rSATXrmEDS){tmRNMqlhCY = true;}
      else if(rSATXrmEDS == mmXdutAwNp){VKHbjNNseH = true;}
      if(PIrJgaiMwt == CXGNpNNYtE){yXxbkhKsNw = true;}
      if(EyIpWzlkdX == uIBOcgsxwG){tMfrlNqZob = true;}
      if(pIXQSQNyFD == GRESBksgUC){oIyzTTxQCr = true;}
      while(CXGNpNNYtE == PIrJgaiMwt){aGBktXeZHz = true;}
      while(uIBOcgsxwG == uIBOcgsxwG){wYtVEMGncB = true;}
      while(GRESBksgUC == GRESBksgUC){YcBsTtUFjF = true;}
      if(IGYHZOZdSh == true){IGYHZOZdSh = false;}
      if(XpaxMiRlpq == true){XpaxMiRlpq = false;}
      if(yoIwMkTmLF == true){yoIwMkTmLF = false;}
      if(UgDrunjsnO == true){UgDrunjsnO = false;}
      if(GPdOiPpHGS == true){GPdOiPpHGS = false;}
      if(TGpdDTybuo == true){TGpdDTybuo = false;}
      if(tmRNMqlhCY == true){tmRNMqlhCY = false;}
      if(yXxbkhKsNw == true){yXxbkhKsNw = false;}
      if(tMfrlNqZob == true){tMfrlNqZob = false;}
      if(oIyzTTxQCr == true){oIyzTTxQCr = false;}
      if(cHEgUuJOsU == true){cHEgUuJOsU = false;}
      if(IEOythGZby == true){IEOythGZby = false;}
      if(AMsZjpYyHQ == true){AMsZjpYyHQ = false;}
      if(jtqUSmHzXp == true){jtqUSmHzXp = false;}
      if(EbgTSjsAEl == true){EbgTSjsAEl = false;}
      if(MXnDrQNexd == true){MXnDrQNexd = false;}
      if(VKHbjNNseH == true){VKHbjNNseH = false;}
      if(aGBktXeZHz == true){aGBktXeZHz = false;}
      if(wYtVEMGncB == true){wYtVEMGncB = false;}
      if(YcBsTtUFjF == true){YcBsTtUFjF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HHCFPPCHSS
{ 
  void XndLUPiSHZ()
  { 
      bool WZcOWuXpss = false;
      bool VzqFymJyab = false;
      bool wJhGRLpfBr = false;
      bool nSTLzQcfzK = false;
      bool gWFURDdyNQ = false;
      bool lwLxBNqVxL = false;
      bool FroAECffGg = false;
      bool KdyQtYDNnN = false;
      bool gqSkGqHVJk = false;
      bool YGhmFohFPP = false;
      bool XyrfFHxuCc = false;
      bool JdhjeNYDtM = false;
      bool uJVUHEuLKF = false;
      bool pyxYphzmey = false;
      bool tLTgauYyIr = false;
      bool QdKDTNcXXB = false;
      bool MlkxlLfIsw = false;
      bool NlYuSjpnsM = false;
      bool fwDSoMmtEb = false;
      bool FbOdkHZWuP = false;
      string CrMZurAQQZ;
      string GMDsjlUhmP;
      string daAGwqyNYw;
      string ztmrBMPKDC;
      string DASxnbDJCX;
      string dOgogarFdD;
      string slrUaMYKqW;
      string VJdjMcHDST;
      string noLARkMxKa;
      string UJgzIQHyWb;
      string DrReBUjwcD;
      string SomKPEaqCo;
      string zaAQCMbebu;
      string VJfpPuWfzx;
      string BPUHHfVWiE;
      string oPugcbrBbn;
      string sFUghJIwtU;
      string gtqFniGrJW;
      string pFuWGFNyNm;
      string DVELEwumYx;
      if(CrMZurAQQZ == DrReBUjwcD){WZcOWuXpss = true;}
      else if(DrReBUjwcD == CrMZurAQQZ){XyrfFHxuCc = true;}
      if(GMDsjlUhmP == SomKPEaqCo){VzqFymJyab = true;}
      else if(SomKPEaqCo == GMDsjlUhmP){JdhjeNYDtM = true;}
      if(daAGwqyNYw == zaAQCMbebu){wJhGRLpfBr = true;}
      else if(zaAQCMbebu == daAGwqyNYw){uJVUHEuLKF = true;}
      if(ztmrBMPKDC == VJfpPuWfzx){nSTLzQcfzK = true;}
      else if(VJfpPuWfzx == ztmrBMPKDC){pyxYphzmey = true;}
      if(DASxnbDJCX == BPUHHfVWiE){gWFURDdyNQ = true;}
      else if(BPUHHfVWiE == DASxnbDJCX){tLTgauYyIr = true;}
      if(dOgogarFdD == oPugcbrBbn){lwLxBNqVxL = true;}
      else if(oPugcbrBbn == dOgogarFdD){QdKDTNcXXB = true;}
      if(slrUaMYKqW == sFUghJIwtU){FroAECffGg = true;}
      else if(sFUghJIwtU == slrUaMYKqW){MlkxlLfIsw = true;}
      if(VJdjMcHDST == gtqFniGrJW){KdyQtYDNnN = true;}
      if(noLARkMxKa == pFuWGFNyNm){gqSkGqHVJk = true;}
      if(UJgzIQHyWb == DVELEwumYx){YGhmFohFPP = true;}
      while(gtqFniGrJW == VJdjMcHDST){NlYuSjpnsM = true;}
      while(pFuWGFNyNm == pFuWGFNyNm){fwDSoMmtEb = true;}
      while(DVELEwumYx == DVELEwumYx){FbOdkHZWuP = true;}
      if(WZcOWuXpss == true){WZcOWuXpss = false;}
      if(VzqFymJyab == true){VzqFymJyab = false;}
      if(wJhGRLpfBr == true){wJhGRLpfBr = false;}
      if(nSTLzQcfzK == true){nSTLzQcfzK = false;}
      if(gWFURDdyNQ == true){gWFURDdyNQ = false;}
      if(lwLxBNqVxL == true){lwLxBNqVxL = false;}
      if(FroAECffGg == true){FroAECffGg = false;}
      if(KdyQtYDNnN == true){KdyQtYDNnN = false;}
      if(gqSkGqHVJk == true){gqSkGqHVJk = false;}
      if(YGhmFohFPP == true){YGhmFohFPP = false;}
      if(XyrfFHxuCc == true){XyrfFHxuCc = false;}
      if(JdhjeNYDtM == true){JdhjeNYDtM = false;}
      if(uJVUHEuLKF == true){uJVUHEuLKF = false;}
      if(pyxYphzmey == true){pyxYphzmey = false;}
      if(tLTgauYyIr == true){tLTgauYyIr = false;}
      if(QdKDTNcXXB == true){QdKDTNcXXB = false;}
      if(MlkxlLfIsw == true){MlkxlLfIsw = false;}
      if(NlYuSjpnsM == true){NlYuSjpnsM = false;}
      if(fwDSoMmtEb == true){fwDSoMmtEb = false;}
      if(FbOdkHZWuP == true){FbOdkHZWuP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFMNPWRVSQ
{ 
  void yaSnQciPqs()
  { 
      bool wAVOsrnLkX = false;
      bool DoknyyKaMF = false;
      bool iHLTLliyMZ = false;
      bool AokKLybShJ = false;
      bool yPcUTsruIL = false;
      bool rCrmxonCDH = false;
      bool IoyKXNDZcz = false;
      bool WqsDHTepzS = false;
      bool smpBgxwyNW = false;
      bool JYPZAIQRxG = false;
      bool oRSIoAJoed = false;
      bool JxDjNUzxcZ = false;
      bool QFMGpxbSCy = false;
      bool CMsrdbUhMf = false;
      bool nHTiMLVfMe = false;
      bool JToWpiEMRq = false;
      bool YpmfaxEKFk = false;
      bool AQkwlJkcsd = false;
      bool awGWnhXVCt = false;
      bool XIPUHxTmHO = false;
      string iOFEaVbiFU;
      string tKjOTWGodq;
      string AkEyIrgVSK;
      string PQyMObMUpR;
      string RSKppZGNQM;
      string tjyBEyKHui;
      string nFPuEdLWAr;
      string KkzMYhaNHi;
      string lSFGQfSwHP;
      string QFZHcLCOlM;
      string NiNYCIjlbW;
      string XxzMxUAJeX;
      string KPOjbELriN;
      string eLatVCFgEH;
      string ugTkrSFMJI;
      string LsiNByTcxx;
      string xrCOrLVEqt;
      string OSFXcdudqI;
      string zyhaBlbNsW;
      string icjGKCdFrg;
      if(iOFEaVbiFU == NiNYCIjlbW){wAVOsrnLkX = true;}
      else if(NiNYCIjlbW == iOFEaVbiFU){oRSIoAJoed = true;}
      if(tKjOTWGodq == XxzMxUAJeX){DoknyyKaMF = true;}
      else if(XxzMxUAJeX == tKjOTWGodq){JxDjNUzxcZ = true;}
      if(AkEyIrgVSK == KPOjbELriN){iHLTLliyMZ = true;}
      else if(KPOjbELriN == AkEyIrgVSK){QFMGpxbSCy = true;}
      if(PQyMObMUpR == eLatVCFgEH){AokKLybShJ = true;}
      else if(eLatVCFgEH == PQyMObMUpR){CMsrdbUhMf = true;}
      if(RSKppZGNQM == ugTkrSFMJI){yPcUTsruIL = true;}
      else if(ugTkrSFMJI == RSKppZGNQM){nHTiMLVfMe = true;}
      if(tjyBEyKHui == LsiNByTcxx){rCrmxonCDH = true;}
      else if(LsiNByTcxx == tjyBEyKHui){JToWpiEMRq = true;}
      if(nFPuEdLWAr == xrCOrLVEqt){IoyKXNDZcz = true;}
      else if(xrCOrLVEqt == nFPuEdLWAr){YpmfaxEKFk = true;}
      if(KkzMYhaNHi == OSFXcdudqI){WqsDHTepzS = true;}
      if(lSFGQfSwHP == zyhaBlbNsW){smpBgxwyNW = true;}
      if(QFZHcLCOlM == icjGKCdFrg){JYPZAIQRxG = true;}
      while(OSFXcdudqI == KkzMYhaNHi){AQkwlJkcsd = true;}
      while(zyhaBlbNsW == zyhaBlbNsW){awGWnhXVCt = true;}
      while(icjGKCdFrg == icjGKCdFrg){XIPUHxTmHO = true;}
      if(wAVOsrnLkX == true){wAVOsrnLkX = false;}
      if(DoknyyKaMF == true){DoknyyKaMF = false;}
      if(iHLTLliyMZ == true){iHLTLliyMZ = false;}
      if(AokKLybShJ == true){AokKLybShJ = false;}
      if(yPcUTsruIL == true){yPcUTsruIL = false;}
      if(rCrmxonCDH == true){rCrmxonCDH = false;}
      if(IoyKXNDZcz == true){IoyKXNDZcz = false;}
      if(WqsDHTepzS == true){WqsDHTepzS = false;}
      if(smpBgxwyNW == true){smpBgxwyNW = false;}
      if(JYPZAIQRxG == true){JYPZAIQRxG = false;}
      if(oRSIoAJoed == true){oRSIoAJoed = false;}
      if(JxDjNUzxcZ == true){JxDjNUzxcZ = false;}
      if(QFMGpxbSCy == true){QFMGpxbSCy = false;}
      if(CMsrdbUhMf == true){CMsrdbUhMf = false;}
      if(nHTiMLVfMe == true){nHTiMLVfMe = false;}
      if(JToWpiEMRq == true){JToWpiEMRq = false;}
      if(YpmfaxEKFk == true){YpmfaxEKFk = false;}
      if(AQkwlJkcsd == true){AQkwlJkcsd = false;}
      if(awGWnhXVCt == true){awGWnhXVCt = false;}
      if(XIPUHxTmHO == true){XIPUHxTmHO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBIFXIMPDI
{ 
  void brXTFleSOt()
  { 
      bool UXpZsbCDGA = false;
      bool nyRLnEVgrQ = false;
      bool ONOzVtxRcm = false;
      bool XhNnRqhaKi = false;
      bool eDfUClpwbo = false;
      bool ZFHgkGJpDz = false;
      bool ejaTcFkcsw = false;
      bool WuVIkLhtwi = false;
      bool DApnMSafDK = false;
      bool hqWLEtbLrx = false;
      bool BMCeReizwY = false;
      bool YPtTudtmGJ = false;
      bool dEZhOeXJDq = false;
      bool jVCyhqxKVg = false;
      bool ibjdlRxDPa = false;
      bool AoEhSwmTQm = false;
      bool HYuEoCNulE = false;
      bool fiQZaCTuww = false;
      bool gUtcptQTfk = false;
      bool DdtiZJfeoj = false;
      string jiniNeoRiR;
      string qQCTtJxPUA;
      string pbmBLxhRUg;
      string rDfiiqLHzI;
      string PjXSdqkCGZ;
      string YUwgWIwmWP;
      string wWxCZmjTkC;
      string xpQLkFEUWT;
      string MfKuHWHzMZ;
      string uYjiMrmVrq;
      string HRQEbiDjwQ;
      string EbPDCQLBuC;
      string fkGKGYFgzr;
      string ShbfMuOGTX;
      string SWDuVTIggu;
      string gkapKVKGyD;
      string dWkDyVzjpH;
      string CFhWiJhLnl;
      string PYAELhGlVq;
      string kHIPtwlzxA;
      if(jiniNeoRiR == HRQEbiDjwQ){UXpZsbCDGA = true;}
      else if(HRQEbiDjwQ == jiniNeoRiR){BMCeReizwY = true;}
      if(qQCTtJxPUA == EbPDCQLBuC){nyRLnEVgrQ = true;}
      else if(EbPDCQLBuC == qQCTtJxPUA){YPtTudtmGJ = true;}
      if(pbmBLxhRUg == fkGKGYFgzr){ONOzVtxRcm = true;}
      else if(fkGKGYFgzr == pbmBLxhRUg){dEZhOeXJDq = true;}
      if(rDfiiqLHzI == ShbfMuOGTX){XhNnRqhaKi = true;}
      else if(ShbfMuOGTX == rDfiiqLHzI){jVCyhqxKVg = true;}
      if(PjXSdqkCGZ == SWDuVTIggu){eDfUClpwbo = true;}
      else if(SWDuVTIggu == PjXSdqkCGZ){ibjdlRxDPa = true;}
      if(YUwgWIwmWP == gkapKVKGyD){ZFHgkGJpDz = true;}
      else if(gkapKVKGyD == YUwgWIwmWP){AoEhSwmTQm = true;}
      if(wWxCZmjTkC == dWkDyVzjpH){ejaTcFkcsw = true;}
      else if(dWkDyVzjpH == wWxCZmjTkC){HYuEoCNulE = true;}
      if(xpQLkFEUWT == CFhWiJhLnl){WuVIkLhtwi = true;}
      if(MfKuHWHzMZ == PYAELhGlVq){DApnMSafDK = true;}
      if(uYjiMrmVrq == kHIPtwlzxA){hqWLEtbLrx = true;}
      while(CFhWiJhLnl == xpQLkFEUWT){fiQZaCTuww = true;}
      while(PYAELhGlVq == PYAELhGlVq){gUtcptQTfk = true;}
      while(kHIPtwlzxA == kHIPtwlzxA){DdtiZJfeoj = true;}
      if(UXpZsbCDGA == true){UXpZsbCDGA = false;}
      if(nyRLnEVgrQ == true){nyRLnEVgrQ = false;}
      if(ONOzVtxRcm == true){ONOzVtxRcm = false;}
      if(XhNnRqhaKi == true){XhNnRqhaKi = false;}
      if(eDfUClpwbo == true){eDfUClpwbo = false;}
      if(ZFHgkGJpDz == true){ZFHgkGJpDz = false;}
      if(ejaTcFkcsw == true){ejaTcFkcsw = false;}
      if(WuVIkLhtwi == true){WuVIkLhtwi = false;}
      if(DApnMSafDK == true){DApnMSafDK = false;}
      if(hqWLEtbLrx == true){hqWLEtbLrx = false;}
      if(BMCeReizwY == true){BMCeReizwY = false;}
      if(YPtTudtmGJ == true){YPtTudtmGJ = false;}
      if(dEZhOeXJDq == true){dEZhOeXJDq = false;}
      if(jVCyhqxKVg == true){jVCyhqxKVg = false;}
      if(ibjdlRxDPa == true){ibjdlRxDPa = false;}
      if(AoEhSwmTQm == true){AoEhSwmTQm = false;}
      if(HYuEoCNulE == true){HYuEoCNulE = false;}
      if(fiQZaCTuww == true){fiQZaCTuww = false;}
      if(gUtcptQTfk == true){gUtcptQTfk = false;}
      if(DdtiZJfeoj == true){DdtiZJfeoj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVDJYHKUTM
{ 
  void VRPssTMLQV()
  { 
      bool mTNEtIebUp = false;
      bool DtZoQSCtkU = false;
      bool XqQtuVbzkJ = false;
      bool kwjIRQVeOb = false;
      bool KeLuCknjmL = false;
      bool WVmZxwDTJX = false;
      bool ffpLEHJQWA = false;
      bool xWeIJrfUqK = false;
      bool gqLZlPIKKV = false;
      bool NBVpueozqu = false;
      bool aWMmNzpePE = false;
      bool QhczqnUPYn = false;
      bool zzFBlwBnMe = false;
      bool DfdwiJeYLm = false;
      bool ZctFFeXWzG = false;
      bool KYZCuaRLAR = false;
      bool xBRkBjEgPg = false;
      bool JuDlOVEAwH = false;
      bool XdoGUeGaAH = false;
      bool rSXtoXLJEU = false;
      string chCbiqaGLA;
      string xRTDtcnXxB;
      string kLqhctpage;
      string qRusuKUtzf;
      string dSWIrKhpuQ;
      string ubHlCRqUyo;
      string BzZgJeWZHj;
      string HtYQWRnioS;
      string LzePiOJIpc;
      string TAuJedrpyM;
      string mIhLJBCpOk;
      string cHefdBUJxt;
      string UOjdQGyPls;
      string YyjceDRTGg;
      string MTtFALVOec;
      string JirDqYXDtC;
      string CmDULdXBAa;
      string iADPhBUddF;
      string kjjJjpGfkG;
      string eNYEeYPYtV;
      if(chCbiqaGLA == mIhLJBCpOk){mTNEtIebUp = true;}
      else if(mIhLJBCpOk == chCbiqaGLA){aWMmNzpePE = true;}
      if(xRTDtcnXxB == cHefdBUJxt){DtZoQSCtkU = true;}
      else if(cHefdBUJxt == xRTDtcnXxB){QhczqnUPYn = true;}
      if(kLqhctpage == UOjdQGyPls){XqQtuVbzkJ = true;}
      else if(UOjdQGyPls == kLqhctpage){zzFBlwBnMe = true;}
      if(qRusuKUtzf == YyjceDRTGg){kwjIRQVeOb = true;}
      else if(YyjceDRTGg == qRusuKUtzf){DfdwiJeYLm = true;}
      if(dSWIrKhpuQ == MTtFALVOec){KeLuCknjmL = true;}
      else if(MTtFALVOec == dSWIrKhpuQ){ZctFFeXWzG = true;}
      if(ubHlCRqUyo == JirDqYXDtC){WVmZxwDTJX = true;}
      else if(JirDqYXDtC == ubHlCRqUyo){KYZCuaRLAR = true;}
      if(BzZgJeWZHj == CmDULdXBAa){ffpLEHJQWA = true;}
      else if(CmDULdXBAa == BzZgJeWZHj){xBRkBjEgPg = true;}
      if(HtYQWRnioS == iADPhBUddF){xWeIJrfUqK = true;}
      if(LzePiOJIpc == kjjJjpGfkG){gqLZlPIKKV = true;}
      if(TAuJedrpyM == eNYEeYPYtV){NBVpueozqu = true;}
      while(iADPhBUddF == HtYQWRnioS){JuDlOVEAwH = true;}
      while(kjjJjpGfkG == kjjJjpGfkG){XdoGUeGaAH = true;}
      while(eNYEeYPYtV == eNYEeYPYtV){rSXtoXLJEU = true;}
      if(mTNEtIebUp == true){mTNEtIebUp = false;}
      if(DtZoQSCtkU == true){DtZoQSCtkU = false;}
      if(XqQtuVbzkJ == true){XqQtuVbzkJ = false;}
      if(kwjIRQVeOb == true){kwjIRQVeOb = false;}
      if(KeLuCknjmL == true){KeLuCknjmL = false;}
      if(WVmZxwDTJX == true){WVmZxwDTJX = false;}
      if(ffpLEHJQWA == true){ffpLEHJQWA = false;}
      if(xWeIJrfUqK == true){xWeIJrfUqK = false;}
      if(gqLZlPIKKV == true){gqLZlPIKKV = false;}
      if(NBVpueozqu == true){NBVpueozqu = false;}
      if(aWMmNzpePE == true){aWMmNzpePE = false;}
      if(QhczqnUPYn == true){QhczqnUPYn = false;}
      if(zzFBlwBnMe == true){zzFBlwBnMe = false;}
      if(DfdwiJeYLm == true){DfdwiJeYLm = false;}
      if(ZctFFeXWzG == true){ZctFFeXWzG = false;}
      if(KYZCuaRLAR == true){KYZCuaRLAR = false;}
      if(xBRkBjEgPg == true){xBRkBjEgPg = false;}
      if(JuDlOVEAwH == true){JuDlOVEAwH = false;}
      if(XdoGUeGaAH == true){XdoGUeGaAH = false;}
      if(rSXtoXLJEU == true){rSXtoXLJEU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUZPWEYRTJ
{ 
  void xrRqIXIioY()
  { 
      bool cFCVMLGsJx = false;
      bool jnKQlirjmi = false;
      bool KMlrJnrnGQ = false;
      bool PpEiFnHpNU = false;
      bool DRHdCRNpnO = false;
      bool LDynKPTKMY = false;
      bool SSlrgsjaLy = false;
      bool aBVSesEIpq = false;
      bool ZCzrFMrPYo = false;
      bool TxdoBkeOxI = false;
      bool hmdpmJgeJQ = false;
      bool KLUUyQStmU = false;
      bool AUBVddXgQs = false;
      bool OpKgJmXIEu = false;
      bool fNFIeIcJpk = false;
      bool RkacHMkIMJ = false;
      bool lzOPCUAmKL = false;
      bool rJoromPsqU = false;
      bool ANqeacOhZx = false;
      bool BPwuIfyoGJ = false;
      string xgKPtcGjnk;
      string NmYQdwqVFc;
      string iRDrpabEOQ;
      string sAmnAJaluc;
      string TLQzOutbJO;
      string ofoUxedRZT;
      string BBUXqMAjQU;
      string VEacJWBDcu;
      string fzuzbNLRqU;
      string fIMabRqsIC;
      string uJLnskEMLZ;
      string dZoenBGVud;
      string BhswoMqABq;
      string fIuazWnGGq;
      string IyFRqGTgmZ;
      string KVxeAMPPzf;
      string sELTsVdNeQ;
      string MzOEUDbbEh;
      string sKMagKKQam;
      string GYGaxDmkXU;
      if(xgKPtcGjnk == uJLnskEMLZ){cFCVMLGsJx = true;}
      else if(uJLnskEMLZ == xgKPtcGjnk){hmdpmJgeJQ = true;}
      if(NmYQdwqVFc == dZoenBGVud){jnKQlirjmi = true;}
      else if(dZoenBGVud == NmYQdwqVFc){KLUUyQStmU = true;}
      if(iRDrpabEOQ == BhswoMqABq){KMlrJnrnGQ = true;}
      else if(BhswoMqABq == iRDrpabEOQ){AUBVddXgQs = true;}
      if(sAmnAJaluc == fIuazWnGGq){PpEiFnHpNU = true;}
      else if(fIuazWnGGq == sAmnAJaluc){OpKgJmXIEu = true;}
      if(TLQzOutbJO == IyFRqGTgmZ){DRHdCRNpnO = true;}
      else if(IyFRqGTgmZ == TLQzOutbJO){fNFIeIcJpk = true;}
      if(ofoUxedRZT == KVxeAMPPzf){LDynKPTKMY = true;}
      else if(KVxeAMPPzf == ofoUxedRZT){RkacHMkIMJ = true;}
      if(BBUXqMAjQU == sELTsVdNeQ){SSlrgsjaLy = true;}
      else if(sELTsVdNeQ == BBUXqMAjQU){lzOPCUAmKL = true;}
      if(VEacJWBDcu == MzOEUDbbEh){aBVSesEIpq = true;}
      if(fzuzbNLRqU == sKMagKKQam){ZCzrFMrPYo = true;}
      if(fIMabRqsIC == GYGaxDmkXU){TxdoBkeOxI = true;}
      while(MzOEUDbbEh == VEacJWBDcu){rJoromPsqU = true;}
      while(sKMagKKQam == sKMagKKQam){ANqeacOhZx = true;}
      while(GYGaxDmkXU == GYGaxDmkXU){BPwuIfyoGJ = true;}
      if(cFCVMLGsJx == true){cFCVMLGsJx = false;}
      if(jnKQlirjmi == true){jnKQlirjmi = false;}
      if(KMlrJnrnGQ == true){KMlrJnrnGQ = false;}
      if(PpEiFnHpNU == true){PpEiFnHpNU = false;}
      if(DRHdCRNpnO == true){DRHdCRNpnO = false;}
      if(LDynKPTKMY == true){LDynKPTKMY = false;}
      if(SSlrgsjaLy == true){SSlrgsjaLy = false;}
      if(aBVSesEIpq == true){aBVSesEIpq = false;}
      if(ZCzrFMrPYo == true){ZCzrFMrPYo = false;}
      if(TxdoBkeOxI == true){TxdoBkeOxI = false;}
      if(hmdpmJgeJQ == true){hmdpmJgeJQ = false;}
      if(KLUUyQStmU == true){KLUUyQStmU = false;}
      if(AUBVddXgQs == true){AUBVddXgQs = false;}
      if(OpKgJmXIEu == true){OpKgJmXIEu = false;}
      if(fNFIeIcJpk == true){fNFIeIcJpk = false;}
      if(RkacHMkIMJ == true){RkacHMkIMJ = false;}
      if(lzOPCUAmKL == true){lzOPCUAmKL = false;}
      if(rJoromPsqU == true){rJoromPsqU = false;}
      if(ANqeacOhZx == true){ANqeacOhZx = false;}
      if(BPwuIfyoGJ == true){BPwuIfyoGJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IMXHAKEFLZ
{ 
  void PlRCZHWlrV()
  { 
      bool eYlolVdgcZ = false;
      bool BQrVScgqWi = false;
      bool wzDiCNSRbL = false;
      bool euZGfmkJsY = false;
      bool ZwiQozWCaL = false;
      bool tlCylfVDmX = false;
      bool CLERtFqloe = false;
      bool qXyxJAPlsC = false;
      bool qPqPQssbUA = false;
      bool RhWVWNqRVi = false;
      bool IkNuTWnEok = false;
      bool QiJjglUnAB = false;
      bool MPQoNIAcau = false;
      bool IxQKtFCwws = false;
      bool EoliihYloj = false;
      bool sCQTVsTXgK = false;
      bool VKcscSRzpa = false;
      bool jYrGwXcgFe = false;
      bool jOnqBGfxnA = false;
      bool keOkXtLrGQ = false;
      string mPefUTrjSt;
      string EkdpooGnkP;
      string QKnrBVOFNn;
      string EZJAkHXaQx;
      string xxhAYIekQb;
      string PKFrzcbmdz;
      string FlWeoebcFg;
      string QfXmSTcnTs;
      string qcokYtTQAH;
      string ekwQrKaCKt;
      string gBeiLjlSZf;
      string znSkIbxkFt;
      string KLbxCeiGuH;
      string sZcZLoyFZo;
      string HBqUHqSLIP;
      string NoxPiVYhgf;
      string AfWRmZLsYS;
      string dqLQmJTHoL;
      string MXyetDcMpp;
      string QPYsnbdYhh;
      if(mPefUTrjSt == gBeiLjlSZf){eYlolVdgcZ = true;}
      else if(gBeiLjlSZf == mPefUTrjSt){IkNuTWnEok = true;}
      if(EkdpooGnkP == znSkIbxkFt){BQrVScgqWi = true;}
      else if(znSkIbxkFt == EkdpooGnkP){QiJjglUnAB = true;}
      if(QKnrBVOFNn == KLbxCeiGuH){wzDiCNSRbL = true;}
      else if(KLbxCeiGuH == QKnrBVOFNn){MPQoNIAcau = true;}
      if(EZJAkHXaQx == sZcZLoyFZo){euZGfmkJsY = true;}
      else if(sZcZLoyFZo == EZJAkHXaQx){IxQKtFCwws = true;}
      if(xxhAYIekQb == HBqUHqSLIP){ZwiQozWCaL = true;}
      else if(HBqUHqSLIP == xxhAYIekQb){EoliihYloj = true;}
      if(PKFrzcbmdz == NoxPiVYhgf){tlCylfVDmX = true;}
      else if(NoxPiVYhgf == PKFrzcbmdz){sCQTVsTXgK = true;}
      if(FlWeoebcFg == AfWRmZLsYS){CLERtFqloe = true;}
      else if(AfWRmZLsYS == FlWeoebcFg){VKcscSRzpa = true;}
      if(QfXmSTcnTs == dqLQmJTHoL){qXyxJAPlsC = true;}
      if(qcokYtTQAH == MXyetDcMpp){qPqPQssbUA = true;}
      if(ekwQrKaCKt == QPYsnbdYhh){RhWVWNqRVi = true;}
      while(dqLQmJTHoL == QfXmSTcnTs){jYrGwXcgFe = true;}
      while(MXyetDcMpp == MXyetDcMpp){jOnqBGfxnA = true;}
      while(QPYsnbdYhh == QPYsnbdYhh){keOkXtLrGQ = true;}
      if(eYlolVdgcZ == true){eYlolVdgcZ = false;}
      if(BQrVScgqWi == true){BQrVScgqWi = false;}
      if(wzDiCNSRbL == true){wzDiCNSRbL = false;}
      if(euZGfmkJsY == true){euZGfmkJsY = false;}
      if(ZwiQozWCaL == true){ZwiQozWCaL = false;}
      if(tlCylfVDmX == true){tlCylfVDmX = false;}
      if(CLERtFqloe == true){CLERtFqloe = false;}
      if(qXyxJAPlsC == true){qXyxJAPlsC = false;}
      if(qPqPQssbUA == true){qPqPQssbUA = false;}
      if(RhWVWNqRVi == true){RhWVWNqRVi = false;}
      if(IkNuTWnEok == true){IkNuTWnEok = false;}
      if(QiJjglUnAB == true){QiJjglUnAB = false;}
      if(MPQoNIAcau == true){MPQoNIAcau = false;}
      if(IxQKtFCwws == true){IxQKtFCwws = false;}
      if(EoliihYloj == true){EoliihYloj = false;}
      if(sCQTVsTXgK == true){sCQTVsTXgK = false;}
      if(VKcscSRzpa == true){VKcscSRzpa = false;}
      if(jYrGwXcgFe == true){jYrGwXcgFe = false;}
      if(jOnqBGfxnA == true){jOnqBGfxnA = false;}
      if(keOkXtLrGQ == true){keOkXtLrGQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCSVWSEDMQ
{ 
  void pmltqaEhtr()
  { 
      bool tInwneQkDk = false;
      bool pnZwjEKxxL = false;
      bool jQBBhWpAyp = false;
      bool eOFVhXteuy = false;
      bool uNZiCitGUl = false;
      bool hIHgHdGlNQ = false;
      bool oPlNGbhEOM = false;
      bool KfBzPWqRyy = false;
      bool cjfLIVGYOD = false;
      bool QHQeJfaLca = false;
      bool BpqIbBGIQj = false;
      bool mnmOmEiaFj = false;
      bool VJpKuCOWoj = false;
      bool weoXxmrXiG = false;
      bool OxHdQcUCqE = false;
      bool wzFsFqzgMZ = false;
      bool mjSgnIzPRA = false;
      bool LKqzUXBMtS = false;
      bool hMekmwYwSF = false;
      bool mLKJTedaoI = false;
      string tGspfSWDoW;
      string dzBhuyowGn;
      string GSdqfBjecl;
      string LWnNKctqxN;
      string nYyMDTozJf;
      string CPndobcBKd;
      string iqZDKHKmWR;
      string DxyrzhTRmM;
      string MjUxiwhKXh;
      string ArgTdwyuBu;
      string JBbrbEQudH;
      string HKNxQzWbTO;
      string YzOnRKQdOD;
      string iYQqCKHcVe;
      string emfQaoeiCe;
      string ZWamWJlnZQ;
      string mlgaXitVtG;
      string qtFoikTyNc;
      string fhbidMydUs;
      string XTDEqsGFrr;
      if(tGspfSWDoW == JBbrbEQudH){tInwneQkDk = true;}
      else if(JBbrbEQudH == tGspfSWDoW){BpqIbBGIQj = true;}
      if(dzBhuyowGn == HKNxQzWbTO){pnZwjEKxxL = true;}
      else if(HKNxQzWbTO == dzBhuyowGn){mnmOmEiaFj = true;}
      if(GSdqfBjecl == YzOnRKQdOD){jQBBhWpAyp = true;}
      else if(YzOnRKQdOD == GSdqfBjecl){VJpKuCOWoj = true;}
      if(LWnNKctqxN == iYQqCKHcVe){eOFVhXteuy = true;}
      else if(iYQqCKHcVe == LWnNKctqxN){weoXxmrXiG = true;}
      if(nYyMDTozJf == emfQaoeiCe){uNZiCitGUl = true;}
      else if(emfQaoeiCe == nYyMDTozJf){OxHdQcUCqE = true;}
      if(CPndobcBKd == ZWamWJlnZQ){hIHgHdGlNQ = true;}
      else if(ZWamWJlnZQ == CPndobcBKd){wzFsFqzgMZ = true;}
      if(iqZDKHKmWR == mlgaXitVtG){oPlNGbhEOM = true;}
      else if(mlgaXitVtG == iqZDKHKmWR){mjSgnIzPRA = true;}
      if(DxyrzhTRmM == qtFoikTyNc){KfBzPWqRyy = true;}
      if(MjUxiwhKXh == fhbidMydUs){cjfLIVGYOD = true;}
      if(ArgTdwyuBu == XTDEqsGFrr){QHQeJfaLca = true;}
      while(qtFoikTyNc == DxyrzhTRmM){LKqzUXBMtS = true;}
      while(fhbidMydUs == fhbidMydUs){hMekmwYwSF = true;}
      while(XTDEqsGFrr == XTDEqsGFrr){mLKJTedaoI = true;}
      if(tInwneQkDk == true){tInwneQkDk = false;}
      if(pnZwjEKxxL == true){pnZwjEKxxL = false;}
      if(jQBBhWpAyp == true){jQBBhWpAyp = false;}
      if(eOFVhXteuy == true){eOFVhXteuy = false;}
      if(uNZiCitGUl == true){uNZiCitGUl = false;}
      if(hIHgHdGlNQ == true){hIHgHdGlNQ = false;}
      if(oPlNGbhEOM == true){oPlNGbhEOM = false;}
      if(KfBzPWqRyy == true){KfBzPWqRyy = false;}
      if(cjfLIVGYOD == true){cjfLIVGYOD = false;}
      if(QHQeJfaLca == true){QHQeJfaLca = false;}
      if(BpqIbBGIQj == true){BpqIbBGIQj = false;}
      if(mnmOmEiaFj == true){mnmOmEiaFj = false;}
      if(VJpKuCOWoj == true){VJpKuCOWoj = false;}
      if(weoXxmrXiG == true){weoXxmrXiG = false;}
      if(OxHdQcUCqE == true){OxHdQcUCqE = false;}
      if(wzFsFqzgMZ == true){wzFsFqzgMZ = false;}
      if(mjSgnIzPRA == true){mjSgnIzPRA = false;}
      if(LKqzUXBMtS == true){LKqzUXBMtS = false;}
      if(hMekmwYwSF == true){hMekmwYwSF = false;}
      if(mLKJTedaoI == true){mLKJTedaoI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLYQDVFSBG
{ 
  void lMxoqPPLCq()
  { 
      bool PiMJtUnEeg = false;
      bool LfdwrIUmJd = false;
      bool acbenVsgRU = false;
      bool nXtpTPOZdM = false;
      bool tSDAFSTuaj = false;
      bool kyXxflHgUY = false;
      bool bHmKsmlmcb = false;
      bool suIwjIZaYV = false;
      bool BxFhipzwJg = false;
      bool IgFFklerHR = false;
      bool ffSzpoobMX = false;
      bool MfIzWdBFaC = false;
      bool nocuSLpDLx = false;
      bool cgSGoUdGqt = false;
      bool BXjlUbYFhG = false;
      bool kZREdqDXfd = false;
      bool zkPPtfNBJB = false;
      bool ztNgBPFpaq = false;
      bool mjVEMDONcy = false;
      bool RGaMtPHTqn = false;
      string nnPHFmYQRm;
      string pTJIyjMFzw;
      string ZSHCCElxLj;
      string DdmcMJCplH;
      string qDgamardgR;
      string oFmiFVgMEA;
      string BaEgiMggwn;
      string hVSqEVkfOa;
      string MHQtuxqDXq;
      string cpllGQyzqa;
      string sLhrjTluei;
      string jAxcnsJKkl;
      string UcJFLrjgkn;
      string WknngAZYKb;
      string LuYnGbrIxM;
      string GnOFGQBcfq;
      string jFKqMyLJwm;
      string SkzJZYEVyj;
      string zajXhhWihQ;
      string yxrSrFkgaH;
      if(nnPHFmYQRm == sLhrjTluei){PiMJtUnEeg = true;}
      else if(sLhrjTluei == nnPHFmYQRm){ffSzpoobMX = true;}
      if(pTJIyjMFzw == jAxcnsJKkl){LfdwrIUmJd = true;}
      else if(jAxcnsJKkl == pTJIyjMFzw){MfIzWdBFaC = true;}
      if(ZSHCCElxLj == UcJFLrjgkn){acbenVsgRU = true;}
      else if(UcJFLrjgkn == ZSHCCElxLj){nocuSLpDLx = true;}
      if(DdmcMJCplH == WknngAZYKb){nXtpTPOZdM = true;}
      else if(WknngAZYKb == DdmcMJCplH){cgSGoUdGqt = true;}
      if(qDgamardgR == LuYnGbrIxM){tSDAFSTuaj = true;}
      else if(LuYnGbrIxM == qDgamardgR){BXjlUbYFhG = true;}
      if(oFmiFVgMEA == GnOFGQBcfq){kyXxflHgUY = true;}
      else if(GnOFGQBcfq == oFmiFVgMEA){kZREdqDXfd = true;}
      if(BaEgiMggwn == jFKqMyLJwm){bHmKsmlmcb = true;}
      else if(jFKqMyLJwm == BaEgiMggwn){zkPPtfNBJB = true;}
      if(hVSqEVkfOa == SkzJZYEVyj){suIwjIZaYV = true;}
      if(MHQtuxqDXq == zajXhhWihQ){BxFhipzwJg = true;}
      if(cpllGQyzqa == yxrSrFkgaH){IgFFklerHR = true;}
      while(SkzJZYEVyj == hVSqEVkfOa){ztNgBPFpaq = true;}
      while(zajXhhWihQ == zajXhhWihQ){mjVEMDONcy = true;}
      while(yxrSrFkgaH == yxrSrFkgaH){RGaMtPHTqn = true;}
      if(PiMJtUnEeg == true){PiMJtUnEeg = false;}
      if(LfdwrIUmJd == true){LfdwrIUmJd = false;}
      if(acbenVsgRU == true){acbenVsgRU = false;}
      if(nXtpTPOZdM == true){nXtpTPOZdM = false;}
      if(tSDAFSTuaj == true){tSDAFSTuaj = false;}
      if(kyXxflHgUY == true){kyXxflHgUY = false;}
      if(bHmKsmlmcb == true){bHmKsmlmcb = false;}
      if(suIwjIZaYV == true){suIwjIZaYV = false;}
      if(BxFhipzwJg == true){BxFhipzwJg = false;}
      if(IgFFklerHR == true){IgFFklerHR = false;}
      if(ffSzpoobMX == true){ffSzpoobMX = false;}
      if(MfIzWdBFaC == true){MfIzWdBFaC = false;}
      if(nocuSLpDLx == true){nocuSLpDLx = false;}
      if(cgSGoUdGqt == true){cgSGoUdGqt = false;}
      if(BXjlUbYFhG == true){BXjlUbYFhG = false;}
      if(kZREdqDXfd == true){kZREdqDXfd = false;}
      if(zkPPtfNBJB == true){zkPPtfNBJB = false;}
      if(ztNgBPFpaq == true){ztNgBPFpaq = false;}
      if(mjVEMDONcy == true){mjVEMDONcy = false;}
      if(RGaMtPHTqn == true){RGaMtPHTqn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBYNJHNZUM
{ 
  void gVwriVlAEw()
  { 
      bool UrTEuUxykJ = false;
      bool ZLFnekfmMg = false;
      bool gUKolqxbtL = false;
      bool uCuRwFeXgc = false;
      bool aEHCTmcUaO = false;
      bool tDeZGAheRD = false;
      bool WUEYNWQmqZ = false;
      bool GIFjFcNIUz = false;
      bool OcAfRrWULw = false;
      bool WzGdFFzhnx = false;
      bool WocBHlyuTc = false;
      bool lZJSntUYHV = false;
      bool zuauDGCadA = false;
      bool deUXbYAzXe = false;
      bool sbAiJxonpL = false;
      bool kaZRxbOhyA = false;
      bool jWRTzHFlpO = false;
      bool tVAbbXtrkF = false;
      bool ROkRPCECZA = false;
      bool KRBXuWJgiC = false;
      string qUMSrBbOGT;
      string abKmMThmVH;
      string pqgplCClVH;
      string oPqbEAOgfl;
      string lpWWxELVRu;
      string lgxFIAnWfp;
      string yorzdKkhhM;
      string EBHjVATJsh;
      string qgTZUISlTE;
      string MrAomwxXsm;
      string TcnFpkZMiH;
      string fdcxzRURdU;
      string qyOczMARxY;
      string DwQGONrOjj;
      string hFCLXhOCpU;
      string aesXuUOKFc;
      string jHPKEjNVil;
      string ZGhtlluCFR;
      string yybcxXCrLt;
      string zhIGAaprHm;
      if(qUMSrBbOGT == TcnFpkZMiH){UrTEuUxykJ = true;}
      else if(TcnFpkZMiH == qUMSrBbOGT){WocBHlyuTc = true;}
      if(abKmMThmVH == fdcxzRURdU){ZLFnekfmMg = true;}
      else if(fdcxzRURdU == abKmMThmVH){lZJSntUYHV = true;}
      if(pqgplCClVH == qyOczMARxY){gUKolqxbtL = true;}
      else if(qyOczMARxY == pqgplCClVH){zuauDGCadA = true;}
      if(oPqbEAOgfl == DwQGONrOjj){uCuRwFeXgc = true;}
      else if(DwQGONrOjj == oPqbEAOgfl){deUXbYAzXe = true;}
      if(lpWWxELVRu == hFCLXhOCpU){aEHCTmcUaO = true;}
      else if(hFCLXhOCpU == lpWWxELVRu){sbAiJxonpL = true;}
      if(lgxFIAnWfp == aesXuUOKFc){tDeZGAheRD = true;}
      else if(aesXuUOKFc == lgxFIAnWfp){kaZRxbOhyA = true;}
      if(yorzdKkhhM == jHPKEjNVil){WUEYNWQmqZ = true;}
      else if(jHPKEjNVil == yorzdKkhhM){jWRTzHFlpO = true;}
      if(EBHjVATJsh == ZGhtlluCFR){GIFjFcNIUz = true;}
      if(qgTZUISlTE == yybcxXCrLt){OcAfRrWULw = true;}
      if(MrAomwxXsm == zhIGAaprHm){WzGdFFzhnx = true;}
      while(ZGhtlluCFR == EBHjVATJsh){tVAbbXtrkF = true;}
      while(yybcxXCrLt == yybcxXCrLt){ROkRPCECZA = true;}
      while(zhIGAaprHm == zhIGAaprHm){KRBXuWJgiC = true;}
      if(UrTEuUxykJ == true){UrTEuUxykJ = false;}
      if(ZLFnekfmMg == true){ZLFnekfmMg = false;}
      if(gUKolqxbtL == true){gUKolqxbtL = false;}
      if(uCuRwFeXgc == true){uCuRwFeXgc = false;}
      if(aEHCTmcUaO == true){aEHCTmcUaO = false;}
      if(tDeZGAheRD == true){tDeZGAheRD = false;}
      if(WUEYNWQmqZ == true){WUEYNWQmqZ = false;}
      if(GIFjFcNIUz == true){GIFjFcNIUz = false;}
      if(OcAfRrWULw == true){OcAfRrWULw = false;}
      if(WzGdFFzhnx == true){WzGdFFzhnx = false;}
      if(WocBHlyuTc == true){WocBHlyuTc = false;}
      if(lZJSntUYHV == true){lZJSntUYHV = false;}
      if(zuauDGCadA == true){zuauDGCadA = false;}
      if(deUXbYAzXe == true){deUXbYAzXe = false;}
      if(sbAiJxonpL == true){sbAiJxonpL = false;}
      if(kaZRxbOhyA == true){kaZRxbOhyA = false;}
      if(jWRTzHFlpO == true){jWRTzHFlpO = false;}
      if(tVAbbXtrkF == true){tVAbbXtrkF = false;}
      if(ROkRPCECZA == true){ROkRPCECZA = false;}
      if(KRBXuWJgiC == true){KRBXuWJgiC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IODCMHXLMS
{ 
  void YKDSSNXrVh()
  { 
      bool MbISFgVEaS = false;
      bool lcCGSVoSqj = false;
      bool GaOfaWGBhr = false;
      bool sHLyVXCGuF = false;
      bool rqPVpEcbrm = false;
      bool ntGoqkNcqh = false;
      bool ZTVhZdRDjt = false;
      bool ShXkrPLrpV = false;
      bool sdJuEzAWGk = false;
      bool KYOMeXUgwL = false;
      bool mYqxTFVVwb = false;
      bool YUmUnwKadZ = false;
      bool ctwzjsSLGT = false;
      bool tdwdiTmLay = false;
      bool ceZeLolsXi = false;
      bool MtDViscqMZ = false;
      bool mKOcgtXIlT = false;
      bool IzzfxxTRnt = false;
      bool HYmWGzaZup = false;
      bool quyBLRQxxQ = false;
      string sYgjrhLVPa;
      string ilBzgVjtDN;
      string FfYmOQUYEg;
      string HkqbHjrOJE;
      string VnMcKUwqyc;
      string fAbcLMAsVa;
      string MmQiTxuYrw;
      string dVjzqRTubs;
      string UdZbBHJNQt;
      string jysiqiWcIN;
      string ZWyCyKPbls;
      string sERbGiMohM;
      string nhIyMfcBII;
      string upmOTxfXcp;
      string qgbWAefQbH;
      string VhuwZrOAoS;
      string gOTcyCRDHJ;
      string CoLqUGFkxh;
      string ALYAlNupob;
      string hfiKIcNyYy;
      if(sYgjrhLVPa == ZWyCyKPbls){MbISFgVEaS = true;}
      else if(ZWyCyKPbls == sYgjrhLVPa){mYqxTFVVwb = true;}
      if(ilBzgVjtDN == sERbGiMohM){lcCGSVoSqj = true;}
      else if(sERbGiMohM == ilBzgVjtDN){YUmUnwKadZ = true;}
      if(FfYmOQUYEg == nhIyMfcBII){GaOfaWGBhr = true;}
      else if(nhIyMfcBII == FfYmOQUYEg){ctwzjsSLGT = true;}
      if(HkqbHjrOJE == upmOTxfXcp){sHLyVXCGuF = true;}
      else if(upmOTxfXcp == HkqbHjrOJE){tdwdiTmLay = true;}
      if(VnMcKUwqyc == qgbWAefQbH){rqPVpEcbrm = true;}
      else if(qgbWAefQbH == VnMcKUwqyc){ceZeLolsXi = true;}
      if(fAbcLMAsVa == VhuwZrOAoS){ntGoqkNcqh = true;}
      else if(VhuwZrOAoS == fAbcLMAsVa){MtDViscqMZ = true;}
      if(MmQiTxuYrw == gOTcyCRDHJ){ZTVhZdRDjt = true;}
      else if(gOTcyCRDHJ == MmQiTxuYrw){mKOcgtXIlT = true;}
      if(dVjzqRTubs == CoLqUGFkxh){ShXkrPLrpV = true;}
      if(UdZbBHJNQt == ALYAlNupob){sdJuEzAWGk = true;}
      if(jysiqiWcIN == hfiKIcNyYy){KYOMeXUgwL = true;}
      while(CoLqUGFkxh == dVjzqRTubs){IzzfxxTRnt = true;}
      while(ALYAlNupob == ALYAlNupob){HYmWGzaZup = true;}
      while(hfiKIcNyYy == hfiKIcNyYy){quyBLRQxxQ = true;}
      if(MbISFgVEaS == true){MbISFgVEaS = false;}
      if(lcCGSVoSqj == true){lcCGSVoSqj = false;}
      if(GaOfaWGBhr == true){GaOfaWGBhr = false;}
      if(sHLyVXCGuF == true){sHLyVXCGuF = false;}
      if(rqPVpEcbrm == true){rqPVpEcbrm = false;}
      if(ntGoqkNcqh == true){ntGoqkNcqh = false;}
      if(ZTVhZdRDjt == true){ZTVhZdRDjt = false;}
      if(ShXkrPLrpV == true){ShXkrPLrpV = false;}
      if(sdJuEzAWGk == true){sdJuEzAWGk = false;}
      if(KYOMeXUgwL == true){KYOMeXUgwL = false;}
      if(mYqxTFVVwb == true){mYqxTFVVwb = false;}
      if(YUmUnwKadZ == true){YUmUnwKadZ = false;}
      if(ctwzjsSLGT == true){ctwzjsSLGT = false;}
      if(tdwdiTmLay == true){tdwdiTmLay = false;}
      if(ceZeLolsXi == true){ceZeLolsXi = false;}
      if(MtDViscqMZ == true){MtDViscqMZ = false;}
      if(mKOcgtXIlT == true){mKOcgtXIlT = false;}
      if(IzzfxxTRnt == true){IzzfxxTRnt = false;}
      if(HYmWGzaZup == true){HYmWGzaZup = false;}
      if(quyBLRQxxQ == true){quyBLRQxxQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZNNGQHIETM
{ 
  void dBLgNyBiOR()
  { 
      bool lRBYGfQlHd = false;
      bool LfiVJzXNpV = false;
      bool aPFXFXGAru = false;
      bool GrLEGjklor = false;
      bool QUiipwgrhc = false;
      bool QrhYpWMdTh = false;
      bool ZQtLXTUdOZ = false;
      bool NlXxEGfVgI = false;
      bool qNRPeOJlOj = false;
      bool WHRGSAZWLV = false;
      bool bCcHOeTkUi = false;
      bool pqwLqLyegJ = false;
      bool KhPeDGTQdE = false;
      bool fIJLfnjKAz = false;
      bool tXResfLGPH = false;
      bool CupCKtlyEI = false;
      bool LDGQDggjeC = false;
      bool amdgOlPklW = false;
      bool tMBWBkSHAl = false;
      bool BlFrnqRBbL = false;
      string sqUuWwLuIh;
      string zdlKUwnsFt;
      string wtTbdKonxJ;
      string AJtjtEAuTL;
      string UBpiGRxrOt;
      string satPozXrQM;
      string GWyzhojBQQ;
      string usYtYtDjUM;
      string MxZCPZOett;
      string fIeGEyDpBQ;
      string huayzABzpt;
      string unWEzJwujI;
      string aFHVjmNRpa;
      string pNiDeRVbDO;
      string XOnzzqkaHt;
      string BIGrpcnFNL;
      string miJPEhFSZh;
      string nUqUkLQHVr;
      string BmKuYhGpNB;
      string cPNqboFYuR;
      if(sqUuWwLuIh == huayzABzpt){lRBYGfQlHd = true;}
      else if(huayzABzpt == sqUuWwLuIh){bCcHOeTkUi = true;}
      if(zdlKUwnsFt == unWEzJwujI){LfiVJzXNpV = true;}
      else if(unWEzJwujI == zdlKUwnsFt){pqwLqLyegJ = true;}
      if(wtTbdKonxJ == aFHVjmNRpa){aPFXFXGAru = true;}
      else if(aFHVjmNRpa == wtTbdKonxJ){KhPeDGTQdE = true;}
      if(AJtjtEAuTL == pNiDeRVbDO){GrLEGjklor = true;}
      else if(pNiDeRVbDO == AJtjtEAuTL){fIJLfnjKAz = true;}
      if(UBpiGRxrOt == XOnzzqkaHt){QUiipwgrhc = true;}
      else if(XOnzzqkaHt == UBpiGRxrOt){tXResfLGPH = true;}
      if(satPozXrQM == BIGrpcnFNL){QrhYpWMdTh = true;}
      else if(BIGrpcnFNL == satPozXrQM){CupCKtlyEI = true;}
      if(GWyzhojBQQ == miJPEhFSZh){ZQtLXTUdOZ = true;}
      else if(miJPEhFSZh == GWyzhojBQQ){LDGQDggjeC = true;}
      if(usYtYtDjUM == nUqUkLQHVr){NlXxEGfVgI = true;}
      if(MxZCPZOett == BmKuYhGpNB){qNRPeOJlOj = true;}
      if(fIeGEyDpBQ == cPNqboFYuR){WHRGSAZWLV = true;}
      while(nUqUkLQHVr == usYtYtDjUM){amdgOlPklW = true;}
      while(BmKuYhGpNB == BmKuYhGpNB){tMBWBkSHAl = true;}
      while(cPNqboFYuR == cPNqboFYuR){BlFrnqRBbL = true;}
      if(lRBYGfQlHd == true){lRBYGfQlHd = false;}
      if(LfiVJzXNpV == true){LfiVJzXNpV = false;}
      if(aPFXFXGAru == true){aPFXFXGAru = false;}
      if(GrLEGjklor == true){GrLEGjklor = false;}
      if(QUiipwgrhc == true){QUiipwgrhc = false;}
      if(QrhYpWMdTh == true){QrhYpWMdTh = false;}
      if(ZQtLXTUdOZ == true){ZQtLXTUdOZ = false;}
      if(NlXxEGfVgI == true){NlXxEGfVgI = false;}
      if(qNRPeOJlOj == true){qNRPeOJlOj = false;}
      if(WHRGSAZWLV == true){WHRGSAZWLV = false;}
      if(bCcHOeTkUi == true){bCcHOeTkUi = false;}
      if(pqwLqLyegJ == true){pqwLqLyegJ = false;}
      if(KhPeDGTQdE == true){KhPeDGTQdE = false;}
      if(fIJLfnjKAz == true){fIJLfnjKAz = false;}
      if(tXResfLGPH == true){tXResfLGPH = false;}
      if(CupCKtlyEI == true){CupCKtlyEI = false;}
      if(LDGQDggjeC == true){LDGQDggjeC = false;}
      if(amdgOlPklW == true){amdgOlPklW = false;}
      if(tMBWBkSHAl == true){tMBWBkSHAl = false;}
      if(BlFrnqRBbL == true){BlFrnqRBbL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXCRVFLCTF
{ 
  void COnxnpoOzQ()
  { 
      bool IDFKQScoVR = false;
      bool ZlTwpxWiUI = false;
      bool EqhsWoBMwh = false;
      bool SwEYdfFJpI = false;
      bool YdPjhjwwQo = false;
      bool OMjuYRVMmb = false;
      bool RPsnycgtRJ = false;
      bool rMrLiabyKm = false;
      bool rEwGTFMIAL = false;
      bool KrVNqIjakE = false;
      bool CCdGxBTYLy = false;
      bool pXBAjMTlTr = false;
      bool QYtFyzpdTa = false;
      bool pAMGjoZoJR = false;
      bool lmwBVmpVdd = false;
      bool oyHrndHXIx = false;
      bool KoEkIpKuPt = false;
      bool ldbCGcbsjL = false;
      bool IUAolqsTRG = false;
      bool hCgMGwiLsf = false;
      string EwXkzOOdFq;
      string ajatNGDDQN;
      string UujwjCIHBG;
      string BVtdZAfrNW;
      string pZBZjUQuVX;
      string kHOHEIMbAw;
      string GHczoFpxUM;
      string aKptWusKLO;
      string kNkcVtGlYQ;
      string nDrQPiwCje;
      string eTZIxaRUkJ;
      string PCQkLsVzdu;
      string zDXDYWRZdn;
      string yqZgjRmcfu;
      string bkBPBkmGEW;
      string MwXoebuWjZ;
      string IqpwKXbiBt;
      string FsSiSNBICm;
      string jKUHbCSkBH;
      string WQrGlkuEEc;
      if(EwXkzOOdFq == eTZIxaRUkJ){IDFKQScoVR = true;}
      else if(eTZIxaRUkJ == EwXkzOOdFq){CCdGxBTYLy = true;}
      if(ajatNGDDQN == PCQkLsVzdu){ZlTwpxWiUI = true;}
      else if(PCQkLsVzdu == ajatNGDDQN){pXBAjMTlTr = true;}
      if(UujwjCIHBG == zDXDYWRZdn){EqhsWoBMwh = true;}
      else if(zDXDYWRZdn == UujwjCIHBG){QYtFyzpdTa = true;}
      if(BVtdZAfrNW == yqZgjRmcfu){SwEYdfFJpI = true;}
      else if(yqZgjRmcfu == BVtdZAfrNW){pAMGjoZoJR = true;}
      if(pZBZjUQuVX == bkBPBkmGEW){YdPjhjwwQo = true;}
      else if(bkBPBkmGEW == pZBZjUQuVX){lmwBVmpVdd = true;}
      if(kHOHEIMbAw == MwXoebuWjZ){OMjuYRVMmb = true;}
      else if(MwXoebuWjZ == kHOHEIMbAw){oyHrndHXIx = true;}
      if(GHczoFpxUM == IqpwKXbiBt){RPsnycgtRJ = true;}
      else if(IqpwKXbiBt == GHczoFpxUM){KoEkIpKuPt = true;}
      if(aKptWusKLO == FsSiSNBICm){rMrLiabyKm = true;}
      if(kNkcVtGlYQ == jKUHbCSkBH){rEwGTFMIAL = true;}
      if(nDrQPiwCje == WQrGlkuEEc){KrVNqIjakE = true;}
      while(FsSiSNBICm == aKptWusKLO){ldbCGcbsjL = true;}
      while(jKUHbCSkBH == jKUHbCSkBH){IUAolqsTRG = true;}
      while(WQrGlkuEEc == WQrGlkuEEc){hCgMGwiLsf = true;}
      if(IDFKQScoVR == true){IDFKQScoVR = false;}
      if(ZlTwpxWiUI == true){ZlTwpxWiUI = false;}
      if(EqhsWoBMwh == true){EqhsWoBMwh = false;}
      if(SwEYdfFJpI == true){SwEYdfFJpI = false;}
      if(YdPjhjwwQo == true){YdPjhjwwQo = false;}
      if(OMjuYRVMmb == true){OMjuYRVMmb = false;}
      if(RPsnycgtRJ == true){RPsnycgtRJ = false;}
      if(rMrLiabyKm == true){rMrLiabyKm = false;}
      if(rEwGTFMIAL == true){rEwGTFMIAL = false;}
      if(KrVNqIjakE == true){KrVNqIjakE = false;}
      if(CCdGxBTYLy == true){CCdGxBTYLy = false;}
      if(pXBAjMTlTr == true){pXBAjMTlTr = false;}
      if(QYtFyzpdTa == true){QYtFyzpdTa = false;}
      if(pAMGjoZoJR == true){pAMGjoZoJR = false;}
      if(lmwBVmpVdd == true){lmwBVmpVdd = false;}
      if(oyHrndHXIx == true){oyHrndHXIx = false;}
      if(KoEkIpKuPt == true){KoEkIpKuPt = false;}
      if(ldbCGcbsjL == true){ldbCGcbsjL = false;}
      if(IUAolqsTRG == true){IUAolqsTRG = false;}
      if(hCgMGwiLsf == true){hCgMGwiLsf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJZXFTCLFB
{ 
  void aBILFuIrmx()
  { 
      bool cfNpuImPMk = false;
      bool uzIHydIdgj = false;
      bool ynUekZoski = false;
      bool pPRYqRjJhL = false;
      bool UXrmiiwtPT = false;
      bool iBBTJoLiEU = false;
      bool TtedufhjQf = false;
      bool szuVPauguC = false;
      bool dtcQAnOxOC = false;
      bool GBEMrasOrD = false;
      bool BMciajFfEi = false;
      bool sdnCqYQOdH = false;
      bool RjVOZquicn = false;
      bool hgorAQQsoP = false;
      bool hhsfIcNBUS = false;
      bool JekjkRpOJi = false;
      bool oWCQALnuBZ = false;
      bool IWYNYipoFx = false;
      bool dsNJdDwEGi = false;
      bool aCjFaKfbex = false;
      string yHkHYPfHea;
      string bNSgAhRExg;
      string TgNSWCaMNy;
      string hSVEkBOpIp;
      string oFnGYUFNPk;
      string ZPTOKRsRjW;
      string nSsgsIqOwy;
      string SbwGqOsGtC;
      string wNwbXSzHsT;
      string IwFkCWLGNP;
      string cqRRSySMWw;
      string YlXhZaVQIZ;
      string IiUbpWVKEU;
      string ClseYFueJZ;
      string zmkxuVYWLa;
      string AtynGtWpbu;
      string bHHCslssJU;
      string fqHhaVyWgT;
      string xyzdUImFXe;
      string iFCNxqfiEI;
      if(yHkHYPfHea == cqRRSySMWw){cfNpuImPMk = true;}
      else if(cqRRSySMWw == yHkHYPfHea){BMciajFfEi = true;}
      if(bNSgAhRExg == YlXhZaVQIZ){uzIHydIdgj = true;}
      else if(YlXhZaVQIZ == bNSgAhRExg){sdnCqYQOdH = true;}
      if(TgNSWCaMNy == IiUbpWVKEU){ynUekZoski = true;}
      else if(IiUbpWVKEU == TgNSWCaMNy){RjVOZquicn = true;}
      if(hSVEkBOpIp == ClseYFueJZ){pPRYqRjJhL = true;}
      else if(ClseYFueJZ == hSVEkBOpIp){hgorAQQsoP = true;}
      if(oFnGYUFNPk == zmkxuVYWLa){UXrmiiwtPT = true;}
      else if(zmkxuVYWLa == oFnGYUFNPk){hhsfIcNBUS = true;}
      if(ZPTOKRsRjW == AtynGtWpbu){iBBTJoLiEU = true;}
      else if(AtynGtWpbu == ZPTOKRsRjW){JekjkRpOJi = true;}
      if(nSsgsIqOwy == bHHCslssJU){TtedufhjQf = true;}
      else if(bHHCslssJU == nSsgsIqOwy){oWCQALnuBZ = true;}
      if(SbwGqOsGtC == fqHhaVyWgT){szuVPauguC = true;}
      if(wNwbXSzHsT == xyzdUImFXe){dtcQAnOxOC = true;}
      if(IwFkCWLGNP == iFCNxqfiEI){GBEMrasOrD = true;}
      while(fqHhaVyWgT == SbwGqOsGtC){IWYNYipoFx = true;}
      while(xyzdUImFXe == xyzdUImFXe){dsNJdDwEGi = true;}
      while(iFCNxqfiEI == iFCNxqfiEI){aCjFaKfbex = true;}
      if(cfNpuImPMk == true){cfNpuImPMk = false;}
      if(uzIHydIdgj == true){uzIHydIdgj = false;}
      if(ynUekZoski == true){ynUekZoski = false;}
      if(pPRYqRjJhL == true){pPRYqRjJhL = false;}
      if(UXrmiiwtPT == true){UXrmiiwtPT = false;}
      if(iBBTJoLiEU == true){iBBTJoLiEU = false;}
      if(TtedufhjQf == true){TtedufhjQf = false;}
      if(szuVPauguC == true){szuVPauguC = false;}
      if(dtcQAnOxOC == true){dtcQAnOxOC = false;}
      if(GBEMrasOrD == true){GBEMrasOrD = false;}
      if(BMciajFfEi == true){BMciajFfEi = false;}
      if(sdnCqYQOdH == true){sdnCqYQOdH = false;}
      if(RjVOZquicn == true){RjVOZquicn = false;}
      if(hgorAQQsoP == true){hgorAQQsoP = false;}
      if(hhsfIcNBUS == true){hhsfIcNBUS = false;}
      if(JekjkRpOJi == true){JekjkRpOJi = false;}
      if(oWCQALnuBZ == true){oWCQALnuBZ = false;}
      if(IWYNYipoFx == true){IWYNYipoFx = false;}
      if(dsNJdDwEGi == true){dsNJdDwEGi = false;}
      if(aCjFaKfbex == true){aCjFaKfbex = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCBOYROAJF
{ 
  void DYSyOxxaND()
  { 
      bool LxhDUxVYWj = false;
      bool ZBamejJJtN = false;
      bool fozyiSlrym = false;
      bool TGQhduqgeG = false;
      bool uDXYZoXYjj = false;
      bool PLDlLVyjTC = false;
      bool LcZjPTjsIj = false;
      bool sbenSbRaYt = false;
      bool tNINXHCdVI = false;
      bool xHMbuRdnIF = false;
      bool EePzpmgPSj = false;
      bool EWKZHxULLI = false;
      bool QFWAmlOCrB = false;
      bool ydRSpPxIXj = false;
      bool amLlDZwmUx = false;
      bool wRbAoyIPME = false;
      bool YeWRkaFqjq = false;
      bool AMnahctjwN = false;
      bool oaguEgBRdq = false;
      bool HhwSLuQsBc = false;
      string ZdjdqTGkXU;
      string LfJUSNSnCK;
      string GoTQomSPde;
      string LQgGOVQAOI;
      string ZigYneRkLS;
      string jipjzjKToD;
      string BqHrItyDGx;
      string wSYtjXHubK;
      string VgDKucaxHd;
      string LxLKGianPs;
      string fNeOWQJwAb;
      string bPqdgTmwxf;
      string TBwckyHOmA;
      string wTeieHBond;
      string TexeBuGgcm;
      string weqjZeRCcX;
      string JtJzeIjIzZ;
      string RyISMoEQao;
      string rZkzERbuIA;
      string pzLPUYVxAr;
      if(ZdjdqTGkXU == fNeOWQJwAb){LxhDUxVYWj = true;}
      else if(fNeOWQJwAb == ZdjdqTGkXU){EePzpmgPSj = true;}
      if(LfJUSNSnCK == bPqdgTmwxf){ZBamejJJtN = true;}
      else if(bPqdgTmwxf == LfJUSNSnCK){EWKZHxULLI = true;}
      if(GoTQomSPde == TBwckyHOmA){fozyiSlrym = true;}
      else if(TBwckyHOmA == GoTQomSPde){QFWAmlOCrB = true;}
      if(LQgGOVQAOI == wTeieHBond){TGQhduqgeG = true;}
      else if(wTeieHBond == LQgGOVQAOI){ydRSpPxIXj = true;}
      if(ZigYneRkLS == TexeBuGgcm){uDXYZoXYjj = true;}
      else if(TexeBuGgcm == ZigYneRkLS){amLlDZwmUx = true;}
      if(jipjzjKToD == weqjZeRCcX){PLDlLVyjTC = true;}
      else if(weqjZeRCcX == jipjzjKToD){wRbAoyIPME = true;}
      if(BqHrItyDGx == JtJzeIjIzZ){LcZjPTjsIj = true;}
      else if(JtJzeIjIzZ == BqHrItyDGx){YeWRkaFqjq = true;}
      if(wSYtjXHubK == RyISMoEQao){sbenSbRaYt = true;}
      if(VgDKucaxHd == rZkzERbuIA){tNINXHCdVI = true;}
      if(LxLKGianPs == pzLPUYVxAr){xHMbuRdnIF = true;}
      while(RyISMoEQao == wSYtjXHubK){AMnahctjwN = true;}
      while(rZkzERbuIA == rZkzERbuIA){oaguEgBRdq = true;}
      while(pzLPUYVxAr == pzLPUYVxAr){HhwSLuQsBc = true;}
      if(LxhDUxVYWj == true){LxhDUxVYWj = false;}
      if(ZBamejJJtN == true){ZBamejJJtN = false;}
      if(fozyiSlrym == true){fozyiSlrym = false;}
      if(TGQhduqgeG == true){TGQhduqgeG = false;}
      if(uDXYZoXYjj == true){uDXYZoXYjj = false;}
      if(PLDlLVyjTC == true){PLDlLVyjTC = false;}
      if(LcZjPTjsIj == true){LcZjPTjsIj = false;}
      if(sbenSbRaYt == true){sbenSbRaYt = false;}
      if(tNINXHCdVI == true){tNINXHCdVI = false;}
      if(xHMbuRdnIF == true){xHMbuRdnIF = false;}
      if(EePzpmgPSj == true){EePzpmgPSj = false;}
      if(EWKZHxULLI == true){EWKZHxULLI = false;}
      if(QFWAmlOCrB == true){QFWAmlOCrB = false;}
      if(ydRSpPxIXj == true){ydRSpPxIXj = false;}
      if(amLlDZwmUx == true){amLlDZwmUx = false;}
      if(wRbAoyIPME == true){wRbAoyIPME = false;}
      if(YeWRkaFqjq == true){YeWRkaFqjq = false;}
      if(AMnahctjwN == true){AMnahctjwN = false;}
      if(oaguEgBRdq == true){oaguEgBRdq = false;}
      if(HhwSLuQsBc == true){HhwSLuQsBc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVRELXJXBX
{ 
  void rRPHRtTsFh()
  { 
      bool lzUlpsHJct = false;
      bool LOgPhzkyNG = false;
      bool zBgOHCBJHy = false;
      bool UTcjTSwRMa = false;
      bool zpscfnXgNX = false;
      bool tMaUHkRFdm = false;
      bool qxCdYqkwuO = false;
      bool CSklGIHDiT = false;
      bool dTwjEIsIch = false;
      bool AqnYiCnPDn = false;
      bool DbkyUaanNz = false;
      bool cNWKJXBSYQ = false;
      bool ycTMOLeLDE = false;
      bool TrAtPChxOc = false;
      bool gEtcElTcPL = false;
      bool AVplpaIYjJ = false;
      bool wPkJekNbtG = false;
      bool oEDuithpIc = false;
      bool qBuqDxCNEo = false;
      bool tJMEgRSjyT = false;
      string xUtaiDjZIl;
      string uPMWNsJbAs;
      string QOpfzQRPIs;
      string esXscnTVwS;
      string afUKSpgQLs;
      string wVhJUheObR;
      string kUQOGCrSsY;
      string ZmfgRkteNJ;
      string jAEOwJLNYt;
      string IEtegGOFDP;
      string xNWlTJpArj;
      string nzBShjPBRx;
      string pdtyPUsAzK;
      string VnbxLWdRum;
      string TKVoGJDbww;
      string pNnGZTTYVz;
      string QoAgNzWEGK;
      string GxFdceIErG;
      string RQDCTHAVWq;
      string DEwuWeKnaH;
      if(xUtaiDjZIl == xNWlTJpArj){lzUlpsHJct = true;}
      else if(xNWlTJpArj == xUtaiDjZIl){DbkyUaanNz = true;}
      if(uPMWNsJbAs == nzBShjPBRx){LOgPhzkyNG = true;}
      else if(nzBShjPBRx == uPMWNsJbAs){cNWKJXBSYQ = true;}
      if(QOpfzQRPIs == pdtyPUsAzK){zBgOHCBJHy = true;}
      else if(pdtyPUsAzK == QOpfzQRPIs){ycTMOLeLDE = true;}
      if(esXscnTVwS == VnbxLWdRum){UTcjTSwRMa = true;}
      else if(VnbxLWdRum == esXscnTVwS){TrAtPChxOc = true;}
      if(afUKSpgQLs == TKVoGJDbww){zpscfnXgNX = true;}
      else if(TKVoGJDbww == afUKSpgQLs){gEtcElTcPL = true;}
      if(wVhJUheObR == pNnGZTTYVz){tMaUHkRFdm = true;}
      else if(pNnGZTTYVz == wVhJUheObR){AVplpaIYjJ = true;}
      if(kUQOGCrSsY == QoAgNzWEGK){qxCdYqkwuO = true;}
      else if(QoAgNzWEGK == kUQOGCrSsY){wPkJekNbtG = true;}
      if(ZmfgRkteNJ == GxFdceIErG){CSklGIHDiT = true;}
      if(jAEOwJLNYt == RQDCTHAVWq){dTwjEIsIch = true;}
      if(IEtegGOFDP == DEwuWeKnaH){AqnYiCnPDn = true;}
      while(GxFdceIErG == ZmfgRkteNJ){oEDuithpIc = true;}
      while(RQDCTHAVWq == RQDCTHAVWq){qBuqDxCNEo = true;}
      while(DEwuWeKnaH == DEwuWeKnaH){tJMEgRSjyT = true;}
      if(lzUlpsHJct == true){lzUlpsHJct = false;}
      if(LOgPhzkyNG == true){LOgPhzkyNG = false;}
      if(zBgOHCBJHy == true){zBgOHCBJHy = false;}
      if(UTcjTSwRMa == true){UTcjTSwRMa = false;}
      if(zpscfnXgNX == true){zpscfnXgNX = false;}
      if(tMaUHkRFdm == true){tMaUHkRFdm = false;}
      if(qxCdYqkwuO == true){qxCdYqkwuO = false;}
      if(CSklGIHDiT == true){CSklGIHDiT = false;}
      if(dTwjEIsIch == true){dTwjEIsIch = false;}
      if(AqnYiCnPDn == true){AqnYiCnPDn = false;}
      if(DbkyUaanNz == true){DbkyUaanNz = false;}
      if(cNWKJXBSYQ == true){cNWKJXBSYQ = false;}
      if(ycTMOLeLDE == true){ycTMOLeLDE = false;}
      if(TrAtPChxOc == true){TrAtPChxOc = false;}
      if(gEtcElTcPL == true){gEtcElTcPL = false;}
      if(AVplpaIYjJ == true){AVplpaIYjJ = false;}
      if(wPkJekNbtG == true){wPkJekNbtG = false;}
      if(oEDuithpIc == true){oEDuithpIc = false;}
      if(qBuqDxCNEo == true){qBuqDxCNEo = false;}
      if(tJMEgRSjyT == true){tJMEgRSjyT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMBEPLSUYN
{ 
  void HRoxRUsZni()
  { 
      bool YwxpMenVBc = false;
      bool XKwHMrKmxb = false;
      bool aqfceRxdrf = false;
      bool pMhCKJAyTK = false;
      bool xYVVChRFir = false;
      bool GaqefgQTLu = false;
      bool gJdUlKctxD = false;
      bool qLSleBVJZx = false;
      bool zqtzZPUCVd = false;
      bool sfmXcmuAiq = false;
      bool FXIfAtIFAd = false;
      bool LGtNwpPduW = false;
      bool pZXSKKYuJr = false;
      bool GUahqbhOye = false;
      bool HPCqRllYbm = false;
      bool WQELBezpUp = false;
      bool UMwIXpfLWT = false;
      bool HBePPaXgAX = false;
      bool YASVUoPOgM = false;
      bool crsIJtTsSb = false;
      string JxFmjrVxRq;
      string DiuXreJtZk;
      string SEcnhKfipC;
      string JoHButGIHF;
      string uMNsjeETMY;
      string opNKSEUQFY;
      string MmHOgObsbx;
      string XBmToFqiDC;
      string FLVQNTbxhp;
      string ZoChsIFyMV;
      string DLqPBnDsUN;
      string NlNCSARpBN;
      string mdKlXhyEZg;
      string ArWhztTFPZ;
      string PhcUcnbAPs;
      string qOxzhYAFrS;
      string ozTmNVOeDY;
      string fLabxFBpJj;
      string FxogpktXzZ;
      string sONwjQOoHG;
      if(JxFmjrVxRq == DLqPBnDsUN){YwxpMenVBc = true;}
      else if(DLqPBnDsUN == JxFmjrVxRq){FXIfAtIFAd = true;}
      if(DiuXreJtZk == NlNCSARpBN){XKwHMrKmxb = true;}
      else if(NlNCSARpBN == DiuXreJtZk){LGtNwpPduW = true;}
      if(SEcnhKfipC == mdKlXhyEZg){aqfceRxdrf = true;}
      else if(mdKlXhyEZg == SEcnhKfipC){pZXSKKYuJr = true;}
      if(JoHButGIHF == ArWhztTFPZ){pMhCKJAyTK = true;}
      else if(ArWhztTFPZ == JoHButGIHF){GUahqbhOye = true;}
      if(uMNsjeETMY == PhcUcnbAPs){xYVVChRFir = true;}
      else if(PhcUcnbAPs == uMNsjeETMY){HPCqRllYbm = true;}
      if(opNKSEUQFY == qOxzhYAFrS){GaqefgQTLu = true;}
      else if(qOxzhYAFrS == opNKSEUQFY){WQELBezpUp = true;}
      if(MmHOgObsbx == ozTmNVOeDY){gJdUlKctxD = true;}
      else if(ozTmNVOeDY == MmHOgObsbx){UMwIXpfLWT = true;}
      if(XBmToFqiDC == fLabxFBpJj){qLSleBVJZx = true;}
      if(FLVQNTbxhp == FxogpktXzZ){zqtzZPUCVd = true;}
      if(ZoChsIFyMV == sONwjQOoHG){sfmXcmuAiq = true;}
      while(fLabxFBpJj == XBmToFqiDC){HBePPaXgAX = true;}
      while(FxogpktXzZ == FxogpktXzZ){YASVUoPOgM = true;}
      while(sONwjQOoHG == sONwjQOoHG){crsIJtTsSb = true;}
      if(YwxpMenVBc == true){YwxpMenVBc = false;}
      if(XKwHMrKmxb == true){XKwHMrKmxb = false;}
      if(aqfceRxdrf == true){aqfceRxdrf = false;}
      if(pMhCKJAyTK == true){pMhCKJAyTK = false;}
      if(xYVVChRFir == true){xYVVChRFir = false;}
      if(GaqefgQTLu == true){GaqefgQTLu = false;}
      if(gJdUlKctxD == true){gJdUlKctxD = false;}
      if(qLSleBVJZx == true){qLSleBVJZx = false;}
      if(zqtzZPUCVd == true){zqtzZPUCVd = false;}
      if(sfmXcmuAiq == true){sfmXcmuAiq = false;}
      if(FXIfAtIFAd == true){FXIfAtIFAd = false;}
      if(LGtNwpPduW == true){LGtNwpPduW = false;}
      if(pZXSKKYuJr == true){pZXSKKYuJr = false;}
      if(GUahqbhOye == true){GUahqbhOye = false;}
      if(HPCqRllYbm == true){HPCqRllYbm = false;}
      if(WQELBezpUp == true){WQELBezpUp = false;}
      if(UMwIXpfLWT == true){UMwIXpfLWT = false;}
      if(HBePPaXgAX == true){HBePPaXgAX = false;}
      if(YASVUoPOgM == true){YASVUoPOgM = false;}
      if(crsIJtTsSb == true){crsIJtTsSb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZNQGUHCZQS
{ 
  void yWLTjiYfjn()
  { 
      bool zCRDsHdOyc = false;
      bool RyiAUmEjSu = false;
      bool McWkXnhZdY = false;
      bool GcPYREHxZQ = false;
      bool lFOauHGjZp = false;
      bool RPhQuVegeE = false;
      bool YDjZVnhKiQ = false;
      bool fHKBJHNwoQ = false;
      bool hyzmGquzdu = false;
      bool ZaRUrhUnFH = false;
      bool YuAJKKEgHm = false;
      bool HiqOWaEwSe = false;
      bool rignpEooIa = false;
      bool lYqhqlypcw = false;
      bool lNrpmqjDyQ = false;
      bool dYVZOoOMSF = false;
      bool UPXfBhqIWj = false;
      bool cOTWreqqAz = false;
      bool UlqrwNDQSB = false;
      bool XkWWbWpLnE = false;
      string TEXgIkwCGf;
      string piehHTRwfu;
      string VggczmJxaL;
      string olbdzLoEQh;
      string xRRIwYcSVq;
      string QVpqemWugV;
      string azatqEHAhu;
      string dNexyEOYfZ;
      string JqbitTukzM;
      string nsWuHypWRr;
      string RbkZMDpsra;
      string XyPGLjWqAX;
      string IVBUHkpjpA;
      string OqHnIgFCWq;
      string cCrYnpdQiW;
      string ayWsiuaPRb;
      string MGCqLgqbye;
      string dTUIuGdcfQ;
      string GZBSYPTNEM;
      string GpkudVzAMH;
      if(TEXgIkwCGf == RbkZMDpsra){zCRDsHdOyc = true;}
      else if(RbkZMDpsra == TEXgIkwCGf){YuAJKKEgHm = true;}
      if(piehHTRwfu == XyPGLjWqAX){RyiAUmEjSu = true;}
      else if(XyPGLjWqAX == piehHTRwfu){HiqOWaEwSe = true;}
      if(VggczmJxaL == IVBUHkpjpA){McWkXnhZdY = true;}
      else if(IVBUHkpjpA == VggczmJxaL){rignpEooIa = true;}
      if(olbdzLoEQh == OqHnIgFCWq){GcPYREHxZQ = true;}
      else if(OqHnIgFCWq == olbdzLoEQh){lYqhqlypcw = true;}
      if(xRRIwYcSVq == cCrYnpdQiW){lFOauHGjZp = true;}
      else if(cCrYnpdQiW == xRRIwYcSVq){lNrpmqjDyQ = true;}
      if(QVpqemWugV == ayWsiuaPRb){RPhQuVegeE = true;}
      else if(ayWsiuaPRb == QVpqemWugV){dYVZOoOMSF = true;}
      if(azatqEHAhu == MGCqLgqbye){YDjZVnhKiQ = true;}
      else if(MGCqLgqbye == azatqEHAhu){UPXfBhqIWj = true;}
      if(dNexyEOYfZ == dTUIuGdcfQ){fHKBJHNwoQ = true;}
      if(JqbitTukzM == GZBSYPTNEM){hyzmGquzdu = true;}
      if(nsWuHypWRr == GpkudVzAMH){ZaRUrhUnFH = true;}
      while(dTUIuGdcfQ == dNexyEOYfZ){cOTWreqqAz = true;}
      while(GZBSYPTNEM == GZBSYPTNEM){UlqrwNDQSB = true;}
      while(GpkudVzAMH == GpkudVzAMH){XkWWbWpLnE = true;}
      if(zCRDsHdOyc == true){zCRDsHdOyc = false;}
      if(RyiAUmEjSu == true){RyiAUmEjSu = false;}
      if(McWkXnhZdY == true){McWkXnhZdY = false;}
      if(GcPYREHxZQ == true){GcPYREHxZQ = false;}
      if(lFOauHGjZp == true){lFOauHGjZp = false;}
      if(RPhQuVegeE == true){RPhQuVegeE = false;}
      if(YDjZVnhKiQ == true){YDjZVnhKiQ = false;}
      if(fHKBJHNwoQ == true){fHKBJHNwoQ = false;}
      if(hyzmGquzdu == true){hyzmGquzdu = false;}
      if(ZaRUrhUnFH == true){ZaRUrhUnFH = false;}
      if(YuAJKKEgHm == true){YuAJKKEgHm = false;}
      if(HiqOWaEwSe == true){HiqOWaEwSe = false;}
      if(rignpEooIa == true){rignpEooIa = false;}
      if(lYqhqlypcw == true){lYqhqlypcw = false;}
      if(lNrpmqjDyQ == true){lNrpmqjDyQ = false;}
      if(dYVZOoOMSF == true){dYVZOoOMSF = false;}
      if(UPXfBhqIWj == true){UPXfBhqIWj = false;}
      if(cOTWreqqAz == true){cOTWreqqAz = false;}
      if(UlqrwNDQSB == true){UlqrwNDQSB = false;}
      if(XkWWbWpLnE == true){XkWWbWpLnE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZQXQXOYNAM
{ 
  void WpVjJANqgM()
  { 
      bool SThVRrGmpM = false;
      bool FSsfOYAYCD = false;
      bool GgWgdeAFHJ = false;
      bool czhYebabPa = false;
      bool lARwLGUNbI = false;
      bool liYyAlxArl = false;
      bool rAefjFjTAl = false;
      bool yXJaRGOZVX = false;
      bool JlczWtaiYs = false;
      bool eZjcikUkMF = false;
      bool VANpKOZxgs = false;
      bool WWdUbFWfJp = false;
      bool eAuHGXnfrf = false;
      bool kdNPBJYmoI = false;
      bool UcCeWIuOAc = false;
      bool NobVaUFFil = false;
      bool ZsFAIrJNSS = false;
      bool gjqAVBxPjy = false;
      bool cZeOSuCqof = false;
      bool DSEChaWCWd = false;
      string VnIsdcOTNB;
      string JCIOuWkcFk;
      string JPjOygzoIX;
      string IwHgSxiUAV;
      string bLUQJyQDhx;
      string mzijoGEstw;
      string cYKosMubuy;
      string mPbjIxuTEz;
      string QwHLkJNXqM;
      string roaErDBfWx;
      string DnIjJWWyar;
      string KkntegRyDi;
      string zXjhFyoXrF;
      string uPwHwcnXCO;
      string lOwzCHBfYK;
      string lCbnxfDZdL;
      string gzGVwuogyC;
      string sswoxkakfy;
      string wIygSrnIJQ;
      string YNspgmHaCH;
      if(VnIsdcOTNB == DnIjJWWyar){SThVRrGmpM = true;}
      else if(DnIjJWWyar == VnIsdcOTNB){VANpKOZxgs = true;}
      if(JCIOuWkcFk == KkntegRyDi){FSsfOYAYCD = true;}
      else if(KkntegRyDi == JCIOuWkcFk){WWdUbFWfJp = true;}
      if(JPjOygzoIX == zXjhFyoXrF){GgWgdeAFHJ = true;}
      else if(zXjhFyoXrF == JPjOygzoIX){eAuHGXnfrf = true;}
      if(IwHgSxiUAV == uPwHwcnXCO){czhYebabPa = true;}
      else if(uPwHwcnXCO == IwHgSxiUAV){kdNPBJYmoI = true;}
      if(bLUQJyQDhx == lOwzCHBfYK){lARwLGUNbI = true;}
      else if(lOwzCHBfYK == bLUQJyQDhx){UcCeWIuOAc = true;}
      if(mzijoGEstw == lCbnxfDZdL){liYyAlxArl = true;}
      else if(lCbnxfDZdL == mzijoGEstw){NobVaUFFil = true;}
      if(cYKosMubuy == gzGVwuogyC){rAefjFjTAl = true;}
      else if(gzGVwuogyC == cYKosMubuy){ZsFAIrJNSS = true;}
      if(mPbjIxuTEz == sswoxkakfy){yXJaRGOZVX = true;}
      if(QwHLkJNXqM == wIygSrnIJQ){JlczWtaiYs = true;}
      if(roaErDBfWx == YNspgmHaCH){eZjcikUkMF = true;}
      while(sswoxkakfy == mPbjIxuTEz){gjqAVBxPjy = true;}
      while(wIygSrnIJQ == wIygSrnIJQ){cZeOSuCqof = true;}
      while(YNspgmHaCH == YNspgmHaCH){DSEChaWCWd = true;}
      if(SThVRrGmpM == true){SThVRrGmpM = false;}
      if(FSsfOYAYCD == true){FSsfOYAYCD = false;}
      if(GgWgdeAFHJ == true){GgWgdeAFHJ = false;}
      if(czhYebabPa == true){czhYebabPa = false;}
      if(lARwLGUNbI == true){lARwLGUNbI = false;}
      if(liYyAlxArl == true){liYyAlxArl = false;}
      if(rAefjFjTAl == true){rAefjFjTAl = false;}
      if(yXJaRGOZVX == true){yXJaRGOZVX = false;}
      if(JlczWtaiYs == true){JlczWtaiYs = false;}
      if(eZjcikUkMF == true){eZjcikUkMF = false;}
      if(VANpKOZxgs == true){VANpKOZxgs = false;}
      if(WWdUbFWfJp == true){WWdUbFWfJp = false;}
      if(eAuHGXnfrf == true){eAuHGXnfrf = false;}
      if(kdNPBJYmoI == true){kdNPBJYmoI = false;}
      if(UcCeWIuOAc == true){UcCeWIuOAc = false;}
      if(NobVaUFFil == true){NobVaUFFil = false;}
      if(ZsFAIrJNSS == true){ZsFAIrJNSS = false;}
      if(gjqAVBxPjy == true){gjqAVBxPjy = false;}
      if(cZeOSuCqof == true){cZeOSuCqof = false;}
      if(DSEChaWCWd == true){DSEChaWCWd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYIPZMIILB
{ 
  void FhEHhlbMLH()
  { 
      bool kdfZkrGnzI = false;
      bool kAOXyfCOGr = false;
      bool eSaEpJZwMV = false;
      bool hVglRPrNcB = false;
      bool FlhXlIGHSE = false;
      bool VCbUXSCaia = false;
      bool SKacZPTcFh = false;
      bool mokFmrjDSg = false;
      bool DScIzftLNz = false;
      bool MQdBiuKExW = false;
      bool ocBjQgQWhe = false;
      bool hzICXAgSct = false;
      bool UHOGUVKiVr = false;
      bool hfFwqZQsqS = false;
      bool OXdhQNIbdh = false;
      bool NraDBhOtOt = false;
      bool VhAoxCtMKy = false;
      bool inaKfxcfpH = false;
      bool MiFmdoECuI = false;
      bool KWdwwgWojO = false;
      string JUlVyoYhyj;
      string FkgxYuJgCp;
      string WLLtnjGpan;
      string IIUPXWceqD;
      string pyeeAuYcTq;
      string OqGrKxIrgO;
      string hhGJawQRYC;
      string RdozzYgfsr;
      string KdWjYQCbEZ;
      string NkxcUIqVED;
      string eHDQZkCHrl;
      string QbyoDEKWkJ;
      string tnMzoggMdq;
      string gKbpNDZGJn;
      string OtjSJklHYP;
      string xTjtIptEar;
      string EpcBFFAIbz;
      string eENwuAEtoD;
      string tYmOtMaggW;
      string JUeQjYRiND;
      if(JUlVyoYhyj == eHDQZkCHrl){kdfZkrGnzI = true;}
      else if(eHDQZkCHrl == JUlVyoYhyj){ocBjQgQWhe = true;}
      if(FkgxYuJgCp == QbyoDEKWkJ){kAOXyfCOGr = true;}
      else if(QbyoDEKWkJ == FkgxYuJgCp){hzICXAgSct = true;}
      if(WLLtnjGpan == tnMzoggMdq){eSaEpJZwMV = true;}
      else if(tnMzoggMdq == WLLtnjGpan){UHOGUVKiVr = true;}
      if(IIUPXWceqD == gKbpNDZGJn){hVglRPrNcB = true;}
      else if(gKbpNDZGJn == IIUPXWceqD){hfFwqZQsqS = true;}
      if(pyeeAuYcTq == OtjSJklHYP){FlhXlIGHSE = true;}
      else if(OtjSJklHYP == pyeeAuYcTq){OXdhQNIbdh = true;}
      if(OqGrKxIrgO == xTjtIptEar){VCbUXSCaia = true;}
      else if(xTjtIptEar == OqGrKxIrgO){NraDBhOtOt = true;}
      if(hhGJawQRYC == EpcBFFAIbz){SKacZPTcFh = true;}
      else if(EpcBFFAIbz == hhGJawQRYC){VhAoxCtMKy = true;}
      if(RdozzYgfsr == eENwuAEtoD){mokFmrjDSg = true;}
      if(KdWjYQCbEZ == tYmOtMaggW){DScIzftLNz = true;}
      if(NkxcUIqVED == JUeQjYRiND){MQdBiuKExW = true;}
      while(eENwuAEtoD == RdozzYgfsr){inaKfxcfpH = true;}
      while(tYmOtMaggW == tYmOtMaggW){MiFmdoECuI = true;}
      while(JUeQjYRiND == JUeQjYRiND){KWdwwgWojO = true;}
      if(kdfZkrGnzI == true){kdfZkrGnzI = false;}
      if(kAOXyfCOGr == true){kAOXyfCOGr = false;}
      if(eSaEpJZwMV == true){eSaEpJZwMV = false;}
      if(hVglRPrNcB == true){hVglRPrNcB = false;}
      if(FlhXlIGHSE == true){FlhXlIGHSE = false;}
      if(VCbUXSCaia == true){VCbUXSCaia = false;}
      if(SKacZPTcFh == true){SKacZPTcFh = false;}
      if(mokFmrjDSg == true){mokFmrjDSg = false;}
      if(DScIzftLNz == true){DScIzftLNz = false;}
      if(MQdBiuKExW == true){MQdBiuKExW = false;}
      if(ocBjQgQWhe == true){ocBjQgQWhe = false;}
      if(hzICXAgSct == true){hzICXAgSct = false;}
      if(UHOGUVKiVr == true){UHOGUVKiVr = false;}
      if(hfFwqZQsqS == true){hfFwqZQsqS = false;}
      if(OXdhQNIbdh == true){OXdhQNIbdh = false;}
      if(NraDBhOtOt == true){NraDBhOtOt = false;}
      if(VhAoxCtMKy == true){VhAoxCtMKy = false;}
      if(inaKfxcfpH == true){inaKfxcfpH = false;}
      if(MiFmdoECuI == true){MiFmdoECuI = false;}
      if(KWdwwgWojO == true){KWdwwgWojO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJXWSFKOFL
{ 
  void ILRlQEsZFS()
  { 
      bool VxtfZtxMnA = false;
      bool dlSlOjDxdD = false;
      bool eIkmhaoTHc = false;
      bool gIiFAawKoV = false;
      bool unJMxsxfyd = false;
      bool FMyiNNMHxy = false;
      bool FdELSVCMlm = false;
      bool msHIHpzXoo = false;
      bool cIUdWTJzql = false;
      bool NoMpQRixtb = false;
      bool pjtLpMFpbX = false;
      bool OoRIVwIaoy = false;
      bool LCVzYyfQrp = false;
      bool GBcNyrOJnJ = false;
      bool OTXSXYXEUT = false;
      bool JIIuPmOtlq = false;
      bool goylQMMDJc = false;
      bool hzmejreDbA = false;
      bool abuXfysgyL = false;
      bool dUWwcYVlBK = false;
      string tGJGhNJdgT;
      string CtIzilCgzC;
      string fzjtibVtnG;
      string sZAAldPmBf;
      string AAUshSXBMe;
      string pKLPyuVPWF;
      string rPpaabsINF;
      string VPeTCfeqLQ;
      string EUgJPiOkBp;
      string HAPunjJtRG;
      string YPnGIaerMS;
      string QeDGBXhgKq;
      string NIGWyVzjfS;
      string VjYFqnfaAo;
      string EVXiYbwJsQ;
      string CciarPIQIm;
      string atLtwfGyON;
      string qHfVlqkWyV;
      string YppOQrBxNb;
      string ePSMNJKcms;
      if(tGJGhNJdgT == YPnGIaerMS){VxtfZtxMnA = true;}
      else if(YPnGIaerMS == tGJGhNJdgT){pjtLpMFpbX = true;}
      if(CtIzilCgzC == QeDGBXhgKq){dlSlOjDxdD = true;}
      else if(QeDGBXhgKq == CtIzilCgzC){OoRIVwIaoy = true;}
      if(fzjtibVtnG == NIGWyVzjfS){eIkmhaoTHc = true;}
      else if(NIGWyVzjfS == fzjtibVtnG){LCVzYyfQrp = true;}
      if(sZAAldPmBf == VjYFqnfaAo){gIiFAawKoV = true;}
      else if(VjYFqnfaAo == sZAAldPmBf){GBcNyrOJnJ = true;}
      if(AAUshSXBMe == EVXiYbwJsQ){unJMxsxfyd = true;}
      else if(EVXiYbwJsQ == AAUshSXBMe){OTXSXYXEUT = true;}
      if(pKLPyuVPWF == CciarPIQIm){FMyiNNMHxy = true;}
      else if(CciarPIQIm == pKLPyuVPWF){JIIuPmOtlq = true;}
      if(rPpaabsINF == atLtwfGyON){FdELSVCMlm = true;}
      else if(atLtwfGyON == rPpaabsINF){goylQMMDJc = true;}
      if(VPeTCfeqLQ == qHfVlqkWyV){msHIHpzXoo = true;}
      if(EUgJPiOkBp == YppOQrBxNb){cIUdWTJzql = true;}
      if(HAPunjJtRG == ePSMNJKcms){NoMpQRixtb = true;}
      while(qHfVlqkWyV == VPeTCfeqLQ){hzmejreDbA = true;}
      while(YppOQrBxNb == YppOQrBxNb){abuXfysgyL = true;}
      while(ePSMNJKcms == ePSMNJKcms){dUWwcYVlBK = true;}
      if(VxtfZtxMnA == true){VxtfZtxMnA = false;}
      if(dlSlOjDxdD == true){dlSlOjDxdD = false;}
      if(eIkmhaoTHc == true){eIkmhaoTHc = false;}
      if(gIiFAawKoV == true){gIiFAawKoV = false;}
      if(unJMxsxfyd == true){unJMxsxfyd = false;}
      if(FMyiNNMHxy == true){FMyiNNMHxy = false;}
      if(FdELSVCMlm == true){FdELSVCMlm = false;}
      if(msHIHpzXoo == true){msHIHpzXoo = false;}
      if(cIUdWTJzql == true){cIUdWTJzql = false;}
      if(NoMpQRixtb == true){NoMpQRixtb = false;}
      if(pjtLpMFpbX == true){pjtLpMFpbX = false;}
      if(OoRIVwIaoy == true){OoRIVwIaoy = false;}
      if(LCVzYyfQrp == true){LCVzYyfQrp = false;}
      if(GBcNyrOJnJ == true){GBcNyrOJnJ = false;}
      if(OTXSXYXEUT == true){OTXSXYXEUT = false;}
      if(JIIuPmOtlq == true){JIIuPmOtlq = false;}
      if(goylQMMDJc == true){goylQMMDJc = false;}
      if(hzmejreDbA == true){hzmejreDbA = false;}
      if(abuXfysgyL == true){abuXfysgyL = false;}
      if(dUWwcYVlBK == true){dUWwcYVlBK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXCFYRTUZZ
{ 
  void KjOYrssxxZ()
  { 
      bool xQHXyXBoth = false;
      bool tdhVXTwUPt = false;
      bool FGKnoHqfxB = false;
      bool mDQMEmLkie = false;
      bool bGzhqexIOK = false;
      bool lLDkipGShq = false;
      bool fVrrupNURk = false;
      bool IKljRyHbwK = false;
      bool JiQlPazecN = false;
      bool grDqyGOGmA = false;
      bool QbpdCaZSSk = false;
      bool idVWgxEFcT = false;
      bool qirDDPHulL = false;
      bool jAnwthrljn = false;
      bool BfLreCVgJB = false;
      bool BIcSJgjmZl = false;
      bool TdgHBhoZbz = false;
      bool ESVoSKWzXB = false;
      bool takjJaWVlM = false;
      bool yFMxTWzEqx = false;
      string XgJRuKKNAw;
      string psXqslUekZ;
      string ZjepNFRPrA;
      string xfgzsXEMtf;
      string LXKDQlxZrF;
      string uVadYnBSDo;
      string stUzzJLYxV;
      string gIjFNBYbZb;
      string HqXmFaFCZF;
      string WkIEmQDLDG;
      string ZYbVXmlUPW;
      string OYsbhBWhtY;
      string EJyrzuzfSx;
      string yNYSCiOBOR;
      string njlDpxqgWk;
      string sUQeCQZjWb;
      string mFCSXBAaZy;
      string lVSbjTWuBB;
      string DSJgDdwsQk;
      string IedmeigTeo;
      if(XgJRuKKNAw == ZYbVXmlUPW){xQHXyXBoth = true;}
      else if(ZYbVXmlUPW == XgJRuKKNAw){QbpdCaZSSk = true;}
      if(psXqslUekZ == OYsbhBWhtY){tdhVXTwUPt = true;}
      else if(OYsbhBWhtY == psXqslUekZ){idVWgxEFcT = true;}
      if(ZjepNFRPrA == EJyrzuzfSx){FGKnoHqfxB = true;}
      else if(EJyrzuzfSx == ZjepNFRPrA){qirDDPHulL = true;}
      if(xfgzsXEMtf == yNYSCiOBOR){mDQMEmLkie = true;}
      else if(yNYSCiOBOR == xfgzsXEMtf){jAnwthrljn = true;}
      if(LXKDQlxZrF == njlDpxqgWk){bGzhqexIOK = true;}
      else if(njlDpxqgWk == LXKDQlxZrF){BfLreCVgJB = true;}
      if(uVadYnBSDo == sUQeCQZjWb){lLDkipGShq = true;}
      else if(sUQeCQZjWb == uVadYnBSDo){BIcSJgjmZl = true;}
      if(stUzzJLYxV == mFCSXBAaZy){fVrrupNURk = true;}
      else if(mFCSXBAaZy == stUzzJLYxV){TdgHBhoZbz = true;}
      if(gIjFNBYbZb == lVSbjTWuBB){IKljRyHbwK = true;}
      if(HqXmFaFCZF == DSJgDdwsQk){JiQlPazecN = true;}
      if(WkIEmQDLDG == IedmeigTeo){grDqyGOGmA = true;}
      while(lVSbjTWuBB == gIjFNBYbZb){ESVoSKWzXB = true;}
      while(DSJgDdwsQk == DSJgDdwsQk){takjJaWVlM = true;}
      while(IedmeigTeo == IedmeigTeo){yFMxTWzEqx = true;}
      if(xQHXyXBoth == true){xQHXyXBoth = false;}
      if(tdhVXTwUPt == true){tdhVXTwUPt = false;}
      if(FGKnoHqfxB == true){FGKnoHqfxB = false;}
      if(mDQMEmLkie == true){mDQMEmLkie = false;}
      if(bGzhqexIOK == true){bGzhqexIOK = false;}
      if(lLDkipGShq == true){lLDkipGShq = false;}
      if(fVrrupNURk == true){fVrrupNURk = false;}
      if(IKljRyHbwK == true){IKljRyHbwK = false;}
      if(JiQlPazecN == true){JiQlPazecN = false;}
      if(grDqyGOGmA == true){grDqyGOGmA = false;}
      if(QbpdCaZSSk == true){QbpdCaZSSk = false;}
      if(idVWgxEFcT == true){idVWgxEFcT = false;}
      if(qirDDPHulL == true){qirDDPHulL = false;}
      if(jAnwthrljn == true){jAnwthrljn = false;}
      if(BfLreCVgJB == true){BfLreCVgJB = false;}
      if(BIcSJgjmZl == true){BIcSJgjmZl = false;}
      if(TdgHBhoZbz == true){TdgHBhoZbz = false;}
      if(ESVoSKWzXB == true){ESVoSKWzXB = false;}
      if(takjJaWVlM == true){takjJaWVlM = false;}
      if(yFMxTWzEqx == true){yFMxTWzEqx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSQSCUREMS
{ 
  void POmUsKsNVo()
  { 
      bool mxDbKwGgnQ = false;
      bool EjxbapJfQu = false;
      bool ZcKBkdXZZz = false;
      bool XjMqbYfCkP = false;
      bool fkTZPtLpTD = false;
      bool zigoKKmCqg = false;
      bool XfHosTXGAC = false;
      bool JHuBOoIklq = false;
      bool RhGVzoDWfR = false;
      bool lcLDqzcegu = false;
      bool VFoRsqmeaV = false;
      bool BCQzOpZkoE = false;
      bool QBZiQfwqJO = false;
      bool LdDpULrnbI = false;
      bool BXwKPjMLoB = false;
      bool ZqpcdUeGBM = false;
      bool uuVLJXyZeC = false;
      bool xkIfCsEPSf = false;
      bool TjCHoTmaMz = false;
      bool glmPMFCjAr = false;
      string CYQcfOFKji;
      string hUCzJZiFLM;
      string SjbwCqhRnt;
      string RrMUGJMZLz;
      string bMdUVCfWdd;
      string qGgLDRwTan;
      string gnWoRoIgsz;
      string MItLkFGHZA;
      string KLnJCKLARn;
      string MrzWSmpnDg;
      string tyddRiMUZy;
      string LotadUANmG;
      string cHPElTIXsy;
      string PSEsFMhJrT;
      string yqZScXyYsx;
      string lbAwDlhYqx;
      string ZobbhrkAUQ;
      string mpVSIlhxbO;
      string VjeuLmRHpT;
      string eISusJOxjk;
      if(CYQcfOFKji == tyddRiMUZy){mxDbKwGgnQ = true;}
      else if(tyddRiMUZy == CYQcfOFKji){VFoRsqmeaV = true;}
      if(hUCzJZiFLM == LotadUANmG){EjxbapJfQu = true;}
      else if(LotadUANmG == hUCzJZiFLM){BCQzOpZkoE = true;}
      if(SjbwCqhRnt == cHPElTIXsy){ZcKBkdXZZz = true;}
      else if(cHPElTIXsy == SjbwCqhRnt){QBZiQfwqJO = true;}
      if(RrMUGJMZLz == PSEsFMhJrT){XjMqbYfCkP = true;}
      else if(PSEsFMhJrT == RrMUGJMZLz){LdDpULrnbI = true;}
      if(bMdUVCfWdd == yqZScXyYsx){fkTZPtLpTD = true;}
      else if(yqZScXyYsx == bMdUVCfWdd){BXwKPjMLoB = true;}
      if(qGgLDRwTan == lbAwDlhYqx){zigoKKmCqg = true;}
      else if(lbAwDlhYqx == qGgLDRwTan){ZqpcdUeGBM = true;}
      if(gnWoRoIgsz == ZobbhrkAUQ){XfHosTXGAC = true;}
      else if(ZobbhrkAUQ == gnWoRoIgsz){uuVLJXyZeC = true;}
      if(MItLkFGHZA == mpVSIlhxbO){JHuBOoIklq = true;}
      if(KLnJCKLARn == VjeuLmRHpT){RhGVzoDWfR = true;}
      if(MrzWSmpnDg == eISusJOxjk){lcLDqzcegu = true;}
      while(mpVSIlhxbO == MItLkFGHZA){xkIfCsEPSf = true;}
      while(VjeuLmRHpT == VjeuLmRHpT){TjCHoTmaMz = true;}
      while(eISusJOxjk == eISusJOxjk){glmPMFCjAr = true;}
      if(mxDbKwGgnQ == true){mxDbKwGgnQ = false;}
      if(EjxbapJfQu == true){EjxbapJfQu = false;}
      if(ZcKBkdXZZz == true){ZcKBkdXZZz = false;}
      if(XjMqbYfCkP == true){XjMqbYfCkP = false;}
      if(fkTZPtLpTD == true){fkTZPtLpTD = false;}
      if(zigoKKmCqg == true){zigoKKmCqg = false;}
      if(XfHosTXGAC == true){XfHosTXGAC = false;}
      if(JHuBOoIklq == true){JHuBOoIklq = false;}
      if(RhGVzoDWfR == true){RhGVzoDWfR = false;}
      if(lcLDqzcegu == true){lcLDqzcegu = false;}
      if(VFoRsqmeaV == true){VFoRsqmeaV = false;}
      if(BCQzOpZkoE == true){BCQzOpZkoE = false;}
      if(QBZiQfwqJO == true){QBZiQfwqJO = false;}
      if(LdDpULrnbI == true){LdDpULrnbI = false;}
      if(BXwKPjMLoB == true){BXwKPjMLoB = false;}
      if(ZqpcdUeGBM == true){ZqpcdUeGBM = false;}
      if(uuVLJXyZeC == true){uuVLJXyZeC = false;}
      if(xkIfCsEPSf == true){xkIfCsEPSf = false;}
      if(TjCHoTmaMz == true){TjCHoTmaMz = false;}
      if(glmPMFCjAr == true){glmPMFCjAr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKBFJJYYDT
{ 
  void VicFcCaJZg()
  { 
      bool TFYsRKUjgu = false;
      bool swERTibmcx = false;
      bool DQDGtmDnWy = false;
      bool zFpJoHBunQ = false;
      bool SIDtWIMqVF = false;
      bool VzMSdDCRzd = false;
      bool GfMhwmGtbM = false;
      bool gfyMeuMIjk = false;
      bool ZMRQcAsXel = false;
      bool EiwJJluUyi = false;
      bool CROJXoAAmh = false;
      bool pthNDtNwFu = false;
      bool thPpHyjoCr = false;
      bool ArJBiIxIrm = false;
      bool AsjwuKBhFO = false;
      bool XzPCnTCXCZ = false;
      bool FKxthyjgeu = false;
      bool wFDRuBySux = false;
      bool wCinUAbHMO = false;
      bool GYFShoupOw = false;
      string MeRBqSHMhZ;
      string zMcVUWOSqi;
      string UjNiwNZQou;
      string BhYsnDwZfd;
      string MbqLOPtxYU;
      string SmhaRbRhFc;
      string rpXlYRmigR;
      string ZolMVrrBTf;
      string TbrTbOAyaM;
      string lNTDkWEFmx;
      string cKPHudAUEZ;
      string iPOZIPyEJK;
      string QnHUfMUibz;
      string nmNVDILkYy;
      string NesBdVyttV;
      string XAucfnCubh;
      string JQsEkuBrVA;
      string DMeLwkuGqJ;
      string NZoFbnrkoP;
      string FQJpoxloPh;
      if(MeRBqSHMhZ == cKPHudAUEZ){TFYsRKUjgu = true;}
      else if(cKPHudAUEZ == MeRBqSHMhZ){CROJXoAAmh = true;}
      if(zMcVUWOSqi == iPOZIPyEJK){swERTibmcx = true;}
      else if(iPOZIPyEJK == zMcVUWOSqi){pthNDtNwFu = true;}
      if(UjNiwNZQou == QnHUfMUibz){DQDGtmDnWy = true;}
      else if(QnHUfMUibz == UjNiwNZQou){thPpHyjoCr = true;}
      if(BhYsnDwZfd == nmNVDILkYy){zFpJoHBunQ = true;}
      else if(nmNVDILkYy == BhYsnDwZfd){ArJBiIxIrm = true;}
      if(MbqLOPtxYU == NesBdVyttV){SIDtWIMqVF = true;}
      else if(NesBdVyttV == MbqLOPtxYU){AsjwuKBhFO = true;}
      if(SmhaRbRhFc == XAucfnCubh){VzMSdDCRzd = true;}
      else if(XAucfnCubh == SmhaRbRhFc){XzPCnTCXCZ = true;}
      if(rpXlYRmigR == JQsEkuBrVA){GfMhwmGtbM = true;}
      else if(JQsEkuBrVA == rpXlYRmigR){FKxthyjgeu = true;}
      if(ZolMVrrBTf == DMeLwkuGqJ){gfyMeuMIjk = true;}
      if(TbrTbOAyaM == NZoFbnrkoP){ZMRQcAsXel = true;}
      if(lNTDkWEFmx == FQJpoxloPh){EiwJJluUyi = true;}
      while(DMeLwkuGqJ == ZolMVrrBTf){wFDRuBySux = true;}
      while(NZoFbnrkoP == NZoFbnrkoP){wCinUAbHMO = true;}
      while(FQJpoxloPh == FQJpoxloPh){GYFShoupOw = true;}
      if(TFYsRKUjgu == true){TFYsRKUjgu = false;}
      if(swERTibmcx == true){swERTibmcx = false;}
      if(DQDGtmDnWy == true){DQDGtmDnWy = false;}
      if(zFpJoHBunQ == true){zFpJoHBunQ = false;}
      if(SIDtWIMqVF == true){SIDtWIMqVF = false;}
      if(VzMSdDCRzd == true){VzMSdDCRzd = false;}
      if(GfMhwmGtbM == true){GfMhwmGtbM = false;}
      if(gfyMeuMIjk == true){gfyMeuMIjk = false;}
      if(ZMRQcAsXel == true){ZMRQcAsXel = false;}
      if(EiwJJluUyi == true){EiwJJluUyi = false;}
      if(CROJXoAAmh == true){CROJXoAAmh = false;}
      if(pthNDtNwFu == true){pthNDtNwFu = false;}
      if(thPpHyjoCr == true){thPpHyjoCr = false;}
      if(ArJBiIxIrm == true){ArJBiIxIrm = false;}
      if(AsjwuKBhFO == true){AsjwuKBhFO = false;}
      if(XzPCnTCXCZ == true){XzPCnTCXCZ = false;}
      if(FKxthyjgeu == true){FKxthyjgeu = false;}
      if(wFDRuBySux == true){wFDRuBySux = false;}
      if(wCinUAbHMO == true){wCinUAbHMO = false;}
      if(GYFShoupOw == true){GYFShoupOw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NRQNUNCQNW
{ 
  void GMfXgmCaop()
  { 
      bool RTwicripsD = false;
      bool AuTZYTZnOK = false;
      bool LiPUsITWMm = false;
      bool UIhGJMogLB = false;
      bool RPEagGQFuW = false;
      bool ojlmIhDboT = false;
      bool XLdGhrNMQL = false;
      bool erbNrueomm = false;
      bool qOaoxkVtya = false;
      bool IMrqdFkxrn = false;
      bool sEnjrwHYtM = false;
      bool DOnCbIkoJx = false;
      bool VTOpCRzjjm = false;
      bool JgwzsmaqwB = false;
      bool cxzkXtYpOV = false;
      bool UwntSZpygZ = false;
      bool wWoHDVRoIo = false;
      bool gsrHUYTcRI = false;
      bool sJUNRMrCfT = false;
      bool xcJVEFHrhB = false;
      string lSdCJWZxoa;
      string OefiAEwZOU;
      string zYuofpKkFE;
      string dhFxRyYRYH;
      string LhdzXFxXcf;
      string TmtCDMXnWS;
      string LnqjxgYhQB;
      string feBGIRtuRZ;
      string rlHZkpmDtE;
      string ajtFwXqsBp;
      string gOGaAokmsl;
      string SbVwZYfQzG;
      string sUnMZujuKk;
      string aAsbsdefZw;
      string EAKIlzOyeW;
      string qZtuxLatBF;
      string EpbIKRhtCw;
      string szqDBsKeaa;
      string gkPnsAGydh;
      string CkeTqOXBxT;
      if(lSdCJWZxoa == gOGaAokmsl){RTwicripsD = true;}
      else if(gOGaAokmsl == lSdCJWZxoa){sEnjrwHYtM = true;}
      if(OefiAEwZOU == SbVwZYfQzG){AuTZYTZnOK = true;}
      else if(SbVwZYfQzG == OefiAEwZOU){DOnCbIkoJx = true;}
      if(zYuofpKkFE == sUnMZujuKk){LiPUsITWMm = true;}
      else if(sUnMZujuKk == zYuofpKkFE){VTOpCRzjjm = true;}
      if(dhFxRyYRYH == aAsbsdefZw){UIhGJMogLB = true;}
      else if(aAsbsdefZw == dhFxRyYRYH){JgwzsmaqwB = true;}
      if(LhdzXFxXcf == EAKIlzOyeW){RPEagGQFuW = true;}
      else if(EAKIlzOyeW == LhdzXFxXcf){cxzkXtYpOV = true;}
      if(TmtCDMXnWS == qZtuxLatBF){ojlmIhDboT = true;}
      else if(qZtuxLatBF == TmtCDMXnWS){UwntSZpygZ = true;}
      if(LnqjxgYhQB == EpbIKRhtCw){XLdGhrNMQL = true;}
      else if(EpbIKRhtCw == LnqjxgYhQB){wWoHDVRoIo = true;}
      if(feBGIRtuRZ == szqDBsKeaa){erbNrueomm = true;}
      if(rlHZkpmDtE == gkPnsAGydh){qOaoxkVtya = true;}
      if(ajtFwXqsBp == CkeTqOXBxT){IMrqdFkxrn = true;}
      while(szqDBsKeaa == feBGIRtuRZ){gsrHUYTcRI = true;}
      while(gkPnsAGydh == gkPnsAGydh){sJUNRMrCfT = true;}
      while(CkeTqOXBxT == CkeTqOXBxT){xcJVEFHrhB = true;}
      if(RTwicripsD == true){RTwicripsD = false;}
      if(AuTZYTZnOK == true){AuTZYTZnOK = false;}
      if(LiPUsITWMm == true){LiPUsITWMm = false;}
      if(UIhGJMogLB == true){UIhGJMogLB = false;}
      if(RPEagGQFuW == true){RPEagGQFuW = false;}
      if(ojlmIhDboT == true){ojlmIhDboT = false;}
      if(XLdGhrNMQL == true){XLdGhrNMQL = false;}
      if(erbNrueomm == true){erbNrueomm = false;}
      if(qOaoxkVtya == true){qOaoxkVtya = false;}
      if(IMrqdFkxrn == true){IMrqdFkxrn = false;}
      if(sEnjrwHYtM == true){sEnjrwHYtM = false;}
      if(DOnCbIkoJx == true){DOnCbIkoJx = false;}
      if(VTOpCRzjjm == true){VTOpCRzjjm = false;}
      if(JgwzsmaqwB == true){JgwzsmaqwB = false;}
      if(cxzkXtYpOV == true){cxzkXtYpOV = false;}
      if(UwntSZpygZ == true){UwntSZpygZ = false;}
      if(wWoHDVRoIo == true){wWoHDVRoIo = false;}
      if(gsrHUYTcRI == true){gsrHUYTcRI = false;}
      if(sJUNRMrCfT == true){sJUNRMrCfT = false;}
      if(xcJVEFHrhB == true){xcJVEFHrhB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZNEKQSFBS
{ 
  void jnjTUGlDke()
  { 
      bool rSHyRhrdIg = false;
      bool PIwxToNatI = false;
      bool TYReHetEZC = false;
      bool BRcULMYDwC = false;
      bool EpuOuCkKHW = false;
      bool inoqBTBbpl = false;
      bool mmDGeyeblH = false;
      bool QJdrEccCjF = false;
      bool sjxDTNclSq = false;
      bool LwMJOQmoiw = false;
      bool WJYzFYJxlX = false;
      bool pyrjrDpAlR = false;
      bool UsItwUxUcn = false;
      bool pnSmiiLxxt = false;
      bool DfzuBMDbRL = false;
      bool ZmCRadBdDk = false;
      bool boTyhBeEBI = false;
      bool qrCrNosNsi = false;
      bool QUDQNDlBLE = false;
      bool hhtLSOLAMz = false;
      string DRpzhdrhaf;
      string dSYQLukOOS;
      string YHzbWBktqY;
      string cZlJebzqNH;
      string xWlVTNjaJG;
      string rioWcuRNbg;
      string syqBDEfPli;
      string wsAHVBVcIJ;
      string RKjjgskPgj;
      string JkPgNzfkRP;
      string gUoaJzhgBa;
      string ZnFRPiNGUK;
      string SPhBYKcSsV;
      string VkLrbwVJZh;
      string LDOFKUfxRe;
      string kYPHwRlmBy;
      string VOneFncNpS;
      string NDflyPBcqD;
      string efBNjwUEuK;
      string KhIaMwOizV;
      if(DRpzhdrhaf == gUoaJzhgBa){rSHyRhrdIg = true;}
      else if(gUoaJzhgBa == DRpzhdrhaf){WJYzFYJxlX = true;}
      if(dSYQLukOOS == ZnFRPiNGUK){PIwxToNatI = true;}
      else if(ZnFRPiNGUK == dSYQLukOOS){pyrjrDpAlR = true;}
      if(YHzbWBktqY == SPhBYKcSsV){TYReHetEZC = true;}
      else if(SPhBYKcSsV == YHzbWBktqY){UsItwUxUcn = true;}
      if(cZlJebzqNH == VkLrbwVJZh){BRcULMYDwC = true;}
      else if(VkLrbwVJZh == cZlJebzqNH){pnSmiiLxxt = true;}
      if(xWlVTNjaJG == LDOFKUfxRe){EpuOuCkKHW = true;}
      else if(LDOFKUfxRe == xWlVTNjaJG){DfzuBMDbRL = true;}
      if(rioWcuRNbg == kYPHwRlmBy){inoqBTBbpl = true;}
      else if(kYPHwRlmBy == rioWcuRNbg){ZmCRadBdDk = true;}
      if(syqBDEfPli == VOneFncNpS){mmDGeyeblH = true;}
      else if(VOneFncNpS == syqBDEfPli){boTyhBeEBI = true;}
      if(wsAHVBVcIJ == NDflyPBcqD){QJdrEccCjF = true;}
      if(RKjjgskPgj == efBNjwUEuK){sjxDTNclSq = true;}
      if(JkPgNzfkRP == KhIaMwOizV){LwMJOQmoiw = true;}
      while(NDflyPBcqD == wsAHVBVcIJ){qrCrNosNsi = true;}
      while(efBNjwUEuK == efBNjwUEuK){QUDQNDlBLE = true;}
      while(KhIaMwOizV == KhIaMwOizV){hhtLSOLAMz = true;}
      if(rSHyRhrdIg == true){rSHyRhrdIg = false;}
      if(PIwxToNatI == true){PIwxToNatI = false;}
      if(TYReHetEZC == true){TYReHetEZC = false;}
      if(BRcULMYDwC == true){BRcULMYDwC = false;}
      if(EpuOuCkKHW == true){EpuOuCkKHW = false;}
      if(inoqBTBbpl == true){inoqBTBbpl = false;}
      if(mmDGeyeblH == true){mmDGeyeblH = false;}
      if(QJdrEccCjF == true){QJdrEccCjF = false;}
      if(sjxDTNclSq == true){sjxDTNclSq = false;}
      if(LwMJOQmoiw == true){LwMJOQmoiw = false;}
      if(WJYzFYJxlX == true){WJYzFYJxlX = false;}
      if(pyrjrDpAlR == true){pyrjrDpAlR = false;}
      if(UsItwUxUcn == true){UsItwUxUcn = false;}
      if(pnSmiiLxxt == true){pnSmiiLxxt = false;}
      if(DfzuBMDbRL == true){DfzuBMDbRL = false;}
      if(ZmCRadBdDk == true){ZmCRadBdDk = false;}
      if(boTyhBeEBI == true){boTyhBeEBI = false;}
      if(qrCrNosNsi == true){qrCrNosNsi = false;}
      if(QUDQNDlBLE == true){QUDQNDlBLE = false;}
      if(hhtLSOLAMz == true){hhtLSOLAMz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDUNECMRKG
{ 
  void eYysBkPyFq()
  { 
      bool qYqUMDAbjf = false;
      bool kzrMVDrAPN = false;
      bool EFjMLUuDhH = false;
      bool czRgRCMCPf = false;
      bool ViyyxBuVNr = false;
      bool YVOQnkoeJr = false;
      bool IwscDkhKuS = false;
      bool qokirVGkPK = false;
      bool YZopiGjArf = false;
      bool NhsXXYoVtL = false;
      bool SjZuBikfYR = false;
      bool eEOyShGCsx = false;
      bool BhSOFJwMLS = false;
      bool gkpDqnztoA = false;
      bool UEaZBISuEp = false;
      bool RmbxKkRLpr = false;
      bool lXTFktNLGd = false;
      bool hMNsbwGrNw = false;
      bool pBIUAtIsrG = false;
      bool WnExNwjUnH = false;
      string PduXCDWuMk;
      string sIoyEAYJhy;
      string leljFkgYhb;
      string ZYATaDXzKD;
      string OUZbxhdZKn;
      string YVCCKkqLRR;
      string VxNkLTHVXA;
      string bYzdiQFJmX;
      string GHOsDEWyJo;
      string MMgshQHnQc;
      string ZIBJMzWXSs;
      string fgYtKNiThG;
      string xJMinPqGwS;
      string JQsKyxFEgD;
      string hyePIemmhT;
      string hmGJePwSVx;
      string HQbAjPnOuM;
      string HdmdYyewZI;
      string bEXbjVKieh;
      string BmhiuQVees;
      if(PduXCDWuMk == ZIBJMzWXSs){qYqUMDAbjf = true;}
      else if(ZIBJMzWXSs == PduXCDWuMk){SjZuBikfYR = true;}
      if(sIoyEAYJhy == fgYtKNiThG){kzrMVDrAPN = true;}
      else if(fgYtKNiThG == sIoyEAYJhy){eEOyShGCsx = true;}
      if(leljFkgYhb == xJMinPqGwS){EFjMLUuDhH = true;}
      else if(xJMinPqGwS == leljFkgYhb){BhSOFJwMLS = true;}
      if(ZYATaDXzKD == JQsKyxFEgD){czRgRCMCPf = true;}
      else if(JQsKyxFEgD == ZYATaDXzKD){gkpDqnztoA = true;}
      if(OUZbxhdZKn == hyePIemmhT){ViyyxBuVNr = true;}
      else if(hyePIemmhT == OUZbxhdZKn){UEaZBISuEp = true;}
      if(YVCCKkqLRR == hmGJePwSVx){YVOQnkoeJr = true;}
      else if(hmGJePwSVx == YVCCKkqLRR){RmbxKkRLpr = true;}
      if(VxNkLTHVXA == HQbAjPnOuM){IwscDkhKuS = true;}
      else if(HQbAjPnOuM == VxNkLTHVXA){lXTFktNLGd = true;}
      if(bYzdiQFJmX == HdmdYyewZI){qokirVGkPK = true;}
      if(GHOsDEWyJo == bEXbjVKieh){YZopiGjArf = true;}
      if(MMgshQHnQc == BmhiuQVees){NhsXXYoVtL = true;}
      while(HdmdYyewZI == bYzdiQFJmX){hMNsbwGrNw = true;}
      while(bEXbjVKieh == bEXbjVKieh){pBIUAtIsrG = true;}
      while(BmhiuQVees == BmhiuQVees){WnExNwjUnH = true;}
      if(qYqUMDAbjf == true){qYqUMDAbjf = false;}
      if(kzrMVDrAPN == true){kzrMVDrAPN = false;}
      if(EFjMLUuDhH == true){EFjMLUuDhH = false;}
      if(czRgRCMCPf == true){czRgRCMCPf = false;}
      if(ViyyxBuVNr == true){ViyyxBuVNr = false;}
      if(YVOQnkoeJr == true){YVOQnkoeJr = false;}
      if(IwscDkhKuS == true){IwscDkhKuS = false;}
      if(qokirVGkPK == true){qokirVGkPK = false;}
      if(YZopiGjArf == true){YZopiGjArf = false;}
      if(NhsXXYoVtL == true){NhsXXYoVtL = false;}
      if(SjZuBikfYR == true){SjZuBikfYR = false;}
      if(eEOyShGCsx == true){eEOyShGCsx = false;}
      if(BhSOFJwMLS == true){BhSOFJwMLS = false;}
      if(gkpDqnztoA == true){gkpDqnztoA = false;}
      if(UEaZBISuEp == true){UEaZBISuEp = false;}
      if(RmbxKkRLpr == true){RmbxKkRLpr = false;}
      if(lXTFktNLGd == true){lXTFktNLGd = false;}
      if(hMNsbwGrNw == true){hMNsbwGrNw = false;}
      if(pBIUAtIsrG == true){pBIUAtIsrG = false;}
      if(WnExNwjUnH == true){WnExNwjUnH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNJICQCAEE
{ 
  void CFgmfAQlmr()
  { 
      bool sRKgIpDpYJ = false;
      bool qbKRTsqisE = false;
      bool HRoJnwkgoO = false;
      bool IbnwuKdPZq = false;
      bool DCpJXtunQH = false;
      bool GHmyYbcBrL = false;
      bool EVAKAOmOVJ = false;
      bool PaICBFbelt = false;
      bool BxQhHAnoXT = false;
      bool gcXOmhBeII = false;
      bool GgRHrfzkxS = false;
      bool zyPxJHFSDA = false;
      bool axpCblDsPT = false;
      bool EwVcnUfJoa = false;
      bool BCrFTiNaFf = false;
      bool bhbIgIpPfF = false;
      bool cFVdODblIn = false;
      bool awdbzXFkhr = false;
      bool YbnjqVTMuf = false;
      bool ePciyugOqQ = false;
      string LuRnOzRiAb;
      string INwgwHjkCe;
      string ADdlSyIczl;
      string RgtmPZqqGz;
      string bDVsrkiPsQ;
      string yFNtjHReUP;
      string pniNJaSJRW;
      string PseCCwgjth;
      string PsiinMTACH;
      string HLVqImUHiQ;
      string SZyVBEaKqm;
      string ZhkmzxFzZx;
      string HSGJODWmsP;
      string bZAcOotNhi;
      string kIIOgZaiqL;
      string hUgkIATnGx;
      string hmRbLAgIXK;
      string DqRqMzJqco;
      string cnwhhGrOTO;
      string VGGkByqgDf;
      if(LuRnOzRiAb == SZyVBEaKqm){sRKgIpDpYJ = true;}
      else if(SZyVBEaKqm == LuRnOzRiAb){GgRHrfzkxS = true;}
      if(INwgwHjkCe == ZhkmzxFzZx){qbKRTsqisE = true;}
      else if(ZhkmzxFzZx == INwgwHjkCe){zyPxJHFSDA = true;}
      if(ADdlSyIczl == HSGJODWmsP){HRoJnwkgoO = true;}
      else if(HSGJODWmsP == ADdlSyIczl){axpCblDsPT = true;}
      if(RgtmPZqqGz == bZAcOotNhi){IbnwuKdPZq = true;}
      else if(bZAcOotNhi == RgtmPZqqGz){EwVcnUfJoa = true;}
      if(bDVsrkiPsQ == kIIOgZaiqL){DCpJXtunQH = true;}
      else if(kIIOgZaiqL == bDVsrkiPsQ){BCrFTiNaFf = true;}
      if(yFNtjHReUP == hUgkIATnGx){GHmyYbcBrL = true;}
      else if(hUgkIATnGx == yFNtjHReUP){bhbIgIpPfF = true;}
      if(pniNJaSJRW == hmRbLAgIXK){EVAKAOmOVJ = true;}
      else if(hmRbLAgIXK == pniNJaSJRW){cFVdODblIn = true;}
      if(PseCCwgjth == DqRqMzJqco){PaICBFbelt = true;}
      if(PsiinMTACH == cnwhhGrOTO){BxQhHAnoXT = true;}
      if(HLVqImUHiQ == VGGkByqgDf){gcXOmhBeII = true;}
      while(DqRqMzJqco == PseCCwgjth){awdbzXFkhr = true;}
      while(cnwhhGrOTO == cnwhhGrOTO){YbnjqVTMuf = true;}
      while(VGGkByqgDf == VGGkByqgDf){ePciyugOqQ = true;}
      if(sRKgIpDpYJ == true){sRKgIpDpYJ = false;}
      if(qbKRTsqisE == true){qbKRTsqisE = false;}
      if(HRoJnwkgoO == true){HRoJnwkgoO = false;}
      if(IbnwuKdPZq == true){IbnwuKdPZq = false;}
      if(DCpJXtunQH == true){DCpJXtunQH = false;}
      if(GHmyYbcBrL == true){GHmyYbcBrL = false;}
      if(EVAKAOmOVJ == true){EVAKAOmOVJ = false;}
      if(PaICBFbelt == true){PaICBFbelt = false;}
      if(BxQhHAnoXT == true){BxQhHAnoXT = false;}
      if(gcXOmhBeII == true){gcXOmhBeII = false;}
      if(GgRHrfzkxS == true){GgRHrfzkxS = false;}
      if(zyPxJHFSDA == true){zyPxJHFSDA = false;}
      if(axpCblDsPT == true){axpCblDsPT = false;}
      if(EwVcnUfJoa == true){EwVcnUfJoa = false;}
      if(BCrFTiNaFf == true){BCrFTiNaFf = false;}
      if(bhbIgIpPfF == true){bhbIgIpPfF = false;}
      if(cFVdODblIn == true){cFVdODblIn = false;}
      if(awdbzXFkhr == true){awdbzXFkhr = false;}
      if(YbnjqVTMuf == true){YbnjqVTMuf = false;}
      if(ePciyugOqQ == true){ePciyugOqQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZTYQSZMHA
{ 
  void DZcTdRydWh()
  { 
      bool TACIzSurbh = false;
      bool kSdyuNcxGD = false;
      bool tkYyPbOtFZ = false;
      bool wywjSHpkTf = false;
      bool LxRiQJhcZG = false;
      bool ASrsghaDrX = false;
      bool EAlClmVtfm = false;
      bool XrcaqxTphF = false;
      bool tlUyYcFCDj = false;
      bool glswbLKOwc = false;
      bool nmxliIpRBj = false;
      bool OkVlcRencJ = false;
      bool hSpuGkzfyf = false;
      bool lEtERGniPP = false;
      bool lmBTVuQGTJ = false;
      bool gWkluUwCey = false;
      bool JKSVxJpRUV = false;
      bool cuXNXtRWYK = false;
      bool UrMozPSHIx = false;
      bool JlERGbUeVL = false;
      string xwtpmMmhun;
      string UiPBQoetZZ;
      string cbbphDFyTP;
      string NUJdYZxuRl;
      string CLzNoLAoOt;
      string ltNnsUUDHj;
      string GnNeZAZlbq;
      string ribnXQbNAW;
      string CPjZdTGVjE;
      string FsnheNyTmn;
      string lNNWBCRZPc;
      string rGCkgqDmBG;
      string sDBXlyutIJ;
      string RIaMjoCMXa;
      string BgFHLzpCAn;
      string JKSguiMpkD;
      string GWQGKjepAr;
      string npPZEMxsLm;
      string HrsTzHotRB;
      string bLbUUdPzxa;
      if(xwtpmMmhun == lNNWBCRZPc){TACIzSurbh = true;}
      else if(lNNWBCRZPc == xwtpmMmhun){nmxliIpRBj = true;}
      if(UiPBQoetZZ == rGCkgqDmBG){kSdyuNcxGD = true;}
      else if(rGCkgqDmBG == UiPBQoetZZ){OkVlcRencJ = true;}
      if(cbbphDFyTP == sDBXlyutIJ){tkYyPbOtFZ = true;}
      else if(sDBXlyutIJ == cbbphDFyTP){hSpuGkzfyf = true;}
      if(NUJdYZxuRl == RIaMjoCMXa){wywjSHpkTf = true;}
      else if(RIaMjoCMXa == NUJdYZxuRl){lEtERGniPP = true;}
      if(CLzNoLAoOt == BgFHLzpCAn){LxRiQJhcZG = true;}
      else if(BgFHLzpCAn == CLzNoLAoOt){lmBTVuQGTJ = true;}
      if(ltNnsUUDHj == JKSguiMpkD){ASrsghaDrX = true;}
      else if(JKSguiMpkD == ltNnsUUDHj){gWkluUwCey = true;}
      if(GnNeZAZlbq == GWQGKjepAr){EAlClmVtfm = true;}
      else if(GWQGKjepAr == GnNeZAZlbq){JKSVxJpRUV = true;}
      if(ribnXQbNAW == npPZEMxsLm){XrcaqxTphF = true;}
      if(CPjZdTGVjE == HrsTzHotRB){tlUyYcFCDj = true;}
      if(FsnheNyTmn == bLbUUdPzxa){glswbLKOwc = true;}
      while(npPZEMxsLm == ribnXQbNAW){cuXNXtRWYK = true;}
      while(HrsTzHotRB == HrsTzHotRB){UrMozPSHIx = true;}
      while(bLbUUdPzxa == bLbUUdPzxa){JlERGbUeVL = true;}
      if(TACIzSurbh == true){TACIzSurbh = false;}
      if(kSdyuNcxGD == true){kSdyuNcxGD = false;}
      if(tkYyPbOtFZ == true){tkYyPbOtFZ = false;}
      if(wywjSHpkTf == true){wywjSHpkTf = false;}
      if(LxRiQJhcZG == true){LxRiQJhcZG = false;}
      if(ASrsghaDrX == true){ASrsghaDrX = false;}
      if(EAlClmVtfm == true){EAlClmVtfm = false;}
      if(XrcaqxTphF == true){XrcaqxTphF = false;}
      if(tlUyYcFCDj == true){tlUyYcFCDj = false;}
      if(glswbLKOwc == true){glswbLKOwc = false;}
      if(nmxliIpRBj == true){nmxliIpRBj = false;}
      if(OkVlcRencJ == true){OkVlcRencJ = false;}
      if(hSpuGkzfyf == true){hSpuGkzfyf = false;}
      if(lEtERGniPP == true){lEtERGniPP = false;}
      if(lmBTVuQGTJ == true){lmBTVuQGTJ = false;}
      if(gWkluUwCey == true){gWkluUwCey = false;}
      if(JKSVxJpRUV == true){JKSVxJpRUV = false;}
      if(cuXNXtRWYK == true){cuXNXtRWYK = false;}
      if(UrMozPSHIx == true){UrMozPSHIx = false;}
      if(JlERGbUeVL == true){JlERGbUeVL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CNYAUGVYYZ
{ 
  void fDIdzKmlQx()
  { 
      bool yldJtsfHSP = false;
      bool BeqtmooBtc = false;
      bool ODOhlPHPKB = false;
      bool oDRDKyToTD = false;
      bool YOWzMYpbZU = false;
      bool UTScIuWuXe = false;
      bool lQxRayMmio = false;
      bool VAgqEAfPUM = false;
      bool YepogVkntP = false;
      bool aXRoQIQEXO = false;
      bool MCrkzTlbYH = false;
      bool OGaKFGZHkF = false;
      bool MXrSNyhqZu = false;
      bool jarFAWlFpM = false;
      bool iJPmBTwHjJ = false;
      bool hITSCnJZWB = false;
      bool ktBdXmOVKi = false;
      bool TURXVDIFQs = false;
      bool CaHPMaGYCL = false;
      bool MMhoanHlOO = false;
      string laRwEqaxQQ;
      string bFXAqBkJnD;
      string mJzluknrWs;
      string TXUYVhPHPs;
      string IzQnZYOiNL;
      string mhQFlcafBS;
      string DhZWxDjzdI;
      string ldtutnrLLW;
      string WFeLGlHOls;
      string GjFwoZYspW;
      string nPEFZJmVKx;
      string jOTewyDOQK;
      string wUMkBBXyFT;
      string PyVohGAZkw;
      string zkEnJrQazq;
      string WJceZSCSDX;
      string lnPqhksdxp;
      string xccULKQXbJ;
      string kxyOwFVpOO;
      string DhVNJKUMGX;
      if(laRwEqaxQQ == nPEFZJmVKx){yldJtsfHSP = true;}
      else if(nPEFZJmVKx == laRwEqaxQQ){MCrkzTlbYH = true;}
      if(bFXAqBkJnD == jOTewyDOQK){BeqtmooBtc = true;}
      else if(jOTewyDOQK == bFXAqBkJnD){OGaKFGZHkF = true;}
      if(mJzluknrWs == wUMkBBXyFT){ODOhlPHPKB = true;}
      else if(wUMkBBXyFT == mJzluknrWs){MXrSNyhqZu = true;}
      if(TXUYVhPHPs == PyVohGAZkw){oDRDKyToTD = true;}
      else if(PyVohGAZkw == TXUYVhPHPs){jarFAWlFpM = true;}
      if(IzQnZYOiNL == zkEnJrQazq){YOWzMYpbZU = true;}
      else if(zkEnJrQazq == IzQnZYOiNL){iJPmBTwHjJ = true;}
      if(mhQFlcafBS == WJceZSCSDX){UTScIuWuXe = true;}
      else if(WJceZSCSDX == mhQFlcafBS){hITSCnJZWB = true;}
      if(DhZWxDjzdI == lnPqhksdxp){lQxRayMmio = true;}
      else if(lnPqhksdxp == DhZWxDjzdI){ktBdXmOVKi = true;}
      if(ldtutnrLLW == xccULKQXbJ){VAgqEAfPUM = true;}
      if(WFeLGlHOls == kxyOwFVpOO){YepogVkntP = true;}
      if(GjFwoZYspW == DhVNJKUMGX){aXRoQIQEXO = true;}
      while(xccULKQXbJ == ldtutnrLLW){TURXVDIFQs = true;}
      while(kxyOwFVpOO == kxyOwFVpOO){CaHPMaGYCL = true;}
      while(DhVNJKUMGX == DhVNJKUMGX){MMhoanHlOO = true;}
      if(yldJtsfHSP == true){yldJtsfHSP = false;}
      if(BeqtmooBtc == true){BeqtmooBtc = false;}
      if(ODOhlPHPKB == true){ODOhlPHPKB = false;}
      if(oDRDKyToTD == true){oDRDKyToTD = false;}
      if(YOWzMYpbZU == true){YOWzMYpbZU = false;}
      if(UTScIuWuXe == true){UTScIuWuXe = false;}
      if(lQxRayMmio == true){lQxRayMmio = false;}
      if(VAgqEAfPUM == true){VAgqEAfPUM = false;}
      if(YepogVkntP == true){YepogVkntP = false;}
      if(aXRoQIQEXO == true){aXRoQIQEXO = false;}
      if(MCrkzTlbYH == true){MCrkzTlbYH = false;}
      if(OGaKFGZHkF == true){OGaKFGZHkF = false;}
      if(MXrSNyhqZu == true){MXrSNyhqZu = false;}
      if(jarFAWlFpM == true){jarFAWlFpM = false;}
      if(iJPmBTwHjJ == true){iJPmBTwHjJ = false;}
      if(hITSCnJZWB == true){hITSCnJZWB = false;}
      if(ktBdXmOVKi == true){ktBdXmOVKi = false;}
      if(TURXVDIFQs == true){TURXVDIFQs = false;}
      if(CaHPMaGYCL == true){CaHPMaGYCL = false;}
      if(MMhoanHlOO == true){MMhoanHlOO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SMJUGXHVNM
{ 
  void hzUnVIaNVp()
  { 
      bool aQdzUpGMQu = false;
      bool HkBXeIeJGy = false;
      bool TUxpertwjc = false;
      bool uNIeaTEUGS = false;
      bool rAVGhDhLrQ = false;
      bool bSargGSnTb = false;
      bool wJbmztbVxL = false;
      bool DKDmFSzqHb = false;
      bool JhETAclQxT = false;
      bool BPAdWhXhGn = false;
      bool aMOgMROmmO = false;
      bool GafqSOFImW = false;
      bool HLXcJnJZQW = false;
      bool tRkTAwTXHi = false;
      bool OzdiNajJLI = false;
      bool cPtigPnkWY = false;
      bool IoWPUooLqV = false;
      bool thBEIIgoPi = false;
      bool DAOItdWCmk = false;
      bool IiAhaYbNOY = false;
      string zWcwMbBPgL;
      string AUqMILcEJM;
      string DAAjeVWqEJ;
      string dsfrywbBEw;
      string VtTXLmXJVA;
      string KlWlgyVrRq;
      string FKLXhHnzNL;
      string jbzNpIgbYr;
      string xMUDyrVtLz;
      string aiiMpKiwpE;
      string yXuKQilIuX;
      string RsTZssoHYp;
      string ktmNjArmXe;
      string ZjlTsZQKmP;
      string FNynhhPJSw;
      string VaWASDkgZP;
      string pykQxgGzfT;
      string beTJjXwzfB;
      string jhTaJzNlBp;
      string njjXYHbhpA;
      if(zWcwMbBPgL == yXuKQilIuX){aQdzUpGMQu = true;}
      else if(yXuKQilIuX == zWcwMbBPgL){aMOgMROmmO = true;}
      if(AUqMILcEJM == RsTZssoHYp){HkBXeIeJGy = true;}
      else if(RsTZssoHYp == AUqMILcEJM){GafqSOFImW = true;}
      if(DAAjeVWqEJ == ktmNjArmXe){TUxpertwjc = true;}
      else if(ktmNjArmXe == DAAjeVWqEJ){HLXcJnJZQW = true;}
      if(dsfrywbBEw == ZjlTsZQKmP){uNIeaTEUGS = true;}
      else if(ZjlTsZQKmP == dsfrywbBEw){tRkTAwTXHi = true;}
      if(VtTXLmXJVA == FNynhhPJSw){rAVGhDhLrQ = true;}
      else if(FNynhhPJSw == VtTXLmXJVA){OzdiNajJLI = true;}
      if(KlWlgyVrRq == VaWASDkgZP){bSargGSnTb = true;}
      else if(VaWASDkgZP == KlWlgyVrRq){cPtigPnkWY = true;}
      if(FKLXhHnzNL == pykQxgGzfT){wJbmztbVxL = true;}
      else if(pykQxgGzfT == FKLXhHnzNL){IoWPUooLqV = true;}
      if(jbzNpIgbYr == beTJjXwzfB){DKDmFSzqHb = true;}
      if(xMUDyrVtLz == jhTaJzNlBp){JhETAclQxT = true;}
      if(aiiMpKiwpE == njjXYHbhpA){BPAdWhXhGn = true;}
      while(beTJjXwzfB == jbzNpIgbYr){thBEIIgoPi = true;}
      while(jhTaJzNlBp == jhTaJzNlBp){DAOItdWCmk = true;}
      while(njjXYHbhpA == njjXYHbhpA){IiAhaYbNOY = true;}
      if(aQdzUpGMQu == true){aQdzUpGMQu = false;}
      if(HkBXeIeJGy == true){HkBXeIeJGy = false;}
      if(TUxpertwjc == true){TUxpertwjc = false;}
      if(uNIeaTEUGS == true){uNIeaTEUGS = false;}
      if(rAVGhDhLrQ == true){rAVGhDhLrQ = false;}
      if(bSargGSnTb == true){bSargGSnTb = false;}
      if(wJbmztbVxL == true){wJbmztbVxL = false;}
      if(DKDmFSzqHb == true){DKDmFSzqHb = false;}
      if(JhETAclQxT == true){JhETAclQxT = false;}
      if(BPAdWhXhGn == true){BPAdWhXhGn = false;}
      if(aMOgMROmmO == true){aMOgMROmmO = false;}
      if(GafqSOFImW == true){GafqSOFImW = false;}
      if(HLXcJnJZQW == true){HLXcJnJZQW = false;}
      if(tRkTAwTXHi == true){tRkTAwTXHi = false;}
      if(OzdiNajJLI == true){OzdiNajJLI = false;}
      if(cPtigPnkWY == true){cPtigPnkWY = false;}
      if(IoWPUooLqV == true){IoWPUooLqV = false;}
      if(thBEIIgoPi == true){thBEIIgoPi = false;}
      if(DAOItdWCmk == true){DAOItdWCmk = false;}
      if(IiAhaYbNOY == true){IiAhaYbNOY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMWLWDBPPY
{ 
  void jiOyXqgERO()
  { 
      bool xEdxDoXwOo = false;
      bool HuGOKxfuzf = false;
      bool FRSGHoZPRQ = false;
      bool dNnjYjgMyb = false;
      bool RkeObgsBPc = false;
      bool sibnrflWoN = false;
      bool PHdxLtHVpa = false;
      bool PSwXOUlDeZ = false;
      bool uYAoXtkzrr = false;
      bool yKWkMJHgDh = false;
      bool ZXLnNZlEZX = false;
      bool thqOSpHoZQ = false;
      bool IHdxcEuLKE = false;
      bool NEzxAXMLax = false;
      bool HgZTyPTHRV = false;
      bool CRHmYRsNLI = false;
      bool easUKoisOu = false;
      bool cuNcIbgKzN = false;
      bool kmsoCuxMXh = false;
      bool dzARRgmFJJ = false;
      string FmYNGPtTdT;
      string fjtWlSsnUF;
      string TETSfFiiPe;
      string SbscAlEXzD;
      string iiOLkUUhQb;
      string JVIkKBSFgB;
      string fKEyBDpRVz;
      string NVoQVjoIhK;
      string jBSmVwTHRz;
      string TypyWXeQJg;
      string eDLQNmgqOa;
      string MJXVQerQbF;
      string jhzVfOeqtx;
      string EXyBfgoBZi;
      string ObsqmJaTgr;
      string fOoExwEokz;
      string IpxQVnLWpj;
      string opprpHoIiW;
      string nLJBRphsEi;
      string cAPaZYdbUy;
      if(FmYNGPtTdT == eDLQNmgqOa){xEdxDoXwOo = true;}
      else if(eDLQNmgqOa == FmYNGPtTdT){ZXLnNZlEZX = true;}
      if(fjtWlSsnUF == MJXVQerQbF){HuGOKxfuzf = true;}
      else if(MJXVQerQbF == fjtWlSsnUF){thqOSpHoZQ = true;}
      if(TETSfFiiPe == jhzVfOeqtx){FRSGHoZPRQ = true;}
      else if(jhzVfOeqtx == TETSfFiiPe){IHdxcEuLKE = true;}
      if(SbscAlEXzD == EXyBfgoBZi){dNnjYjgMyb = true;}
      else if(EXyBfgoBZi == SbscAlEXzD){NEzxAXMLax = true;}
      if(iiOLkUUhQb == ObsqmJaTgr){RkeObgsBPc = true;}
      else if(ObsqmJaTgr == iiOLkUUhQb){HgZTyPTHRV = true;}
      if(JVIkKBSFgB == fOoExwEokz){sibnrflWoN = true;}
      else if(fOoExwEokz == JVIkKBSFgB){CRHmYRsNLI = true;}
      if(fKEyBDpRVz == IpxQVnLWpj){PHdxLtHVpa = true;}
      else if(IpxQVnLWpj == fKEyBDpRVz){easUKoisOu = true;}
      if(NVoQVjoIhK == opprpHoIiW){PSwXOUlDeZ = true;}
      if(jBSmVwTHRz == nLJBRphsEi){uYAoXtkzrr = true;}
      if(TypyWXeQJg == cAPaZYdbUy){yKWkMJHgDh = true;}
      while(opprpHoIiW == NVoQVjoIhK){cuNcIbgKzN = true;}
      while(nLJBRphsEi == nLJBRphsEi){kmsoCuxMXh = true;}
      while(cAPaZYdbUy == cAPaZYdbUy){dzARRgmFJJ = true;}
      if(xEdxDoXwOo == true){xEdxDoXwOo = false;}
      if(HuGOKxfuzf == true){HuGOKxfuzf = false;}
      if(FRSGHoZPRQ == true){FRSGHoZPRQ = false;}
      if(dNnjYjgMyb == true){dNnjYjgMyb = false;}
      if(RkeObgsBPc == true){RkeObgsBPc = false;}
      if(sibnrflWoN == true){sibnrflWoN = false;}
      if(PHdxLtHVpa == true){PHdxLtHVpa = false;}
      if(PSwXOUlDeZ == true){PSwXOUlDeZ = false;}
      if(uYAoXtkzrr == true){uYAoXtkzrr = false;}
      if(yKWkMJHgDh == true){yKWkMJHgDh = false;}
      if(ZXLnNZlEZX == true){ZXLnNZlEZX = false;}
      if(thqOSpHoZQ == true){thqOSpHoZQ = false;}
      if(IHdxcEuLKE == true){IHdxcEuLKE = false;}
      if(NEzxAXMLax == true){NEzxAXMLax = false;}
      if(HgZTyPTHRV == true){HgZTyPTHRV = false;}
      if(CRHmYRsNLI == true){CRHmYRsNLI = false;}
      if(easUKoisOu == true){easUKoisOu = false;}
      if(cuNcIbgKzN == true){cuNcIbgKzN = false;}
      if(kmsoCuxMXh == true){kmsoCuxMXh = false;}
      if(dzARRgmFJJ == true){dzARRgmFJJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIZUZFLWLU
{ 
  void wXbFQlQEGl()
  { 
      bool cjHZlgwqcV = false;
      bool puTuJAnoOG = false;
      bool rdbmBcZlBj = false;
      bool ciUyGCtMib = false;
      bool poSExrrFeo = false;
      bool SksMayITYJ = false;
      bool GJpsrGZVnH = false;
      bool GbGmPDLWpJ = false;
      bool jTGMQroIWI = false;
      bool tZmZUfzYLp = false;
      bool SWRWhqeGwX = false;
      bool mkdPYlCdcA = false;
      bool RQyeNfngRi = false;
      bool DlLzpNCidY = false;
      bool NhLzUIuXAh = false;
      bool cVwKYBXlJC = false;
      bool CxnMTBYeYL = false;
      bool jSzDmiEzKE = false;
      bool kPfjGhoAao = false;
      bool pPZbVPszeT = false;
      string owlrRXGJpH;
      string ulXEgWHWJE;
      string APsRXAoAob;
      string UMrKIyJwsy;
      string WFghAyusBh;
      string xHSWxYDTTQ;
      string iGTNmisMuh;
      string NLdLhuiLRZ;
      string FuzGdMsVNj;
      string uobbOPkStQ;
      string FhxSUldHoC;
      string pqCtLmHNjZ;
      string pXzLmYiCwR;
      string JPQAUWyflr;
      string ilfKsDlgPa;
      string IXiUZgilew;
      string CaKXrZaCZo;
      string oaaqqEqnRj;
      string lBmUIlgwZm;
      string mMBopHaIST;
      if(owlrRXGJpH == FhxSUldHoC){cjHZlgwqcV = true;}
      else if(FhxSUldHoC == owlrRXGJpH){SWRWhqeGwX = true;}
      if(ulXEgWHWJE == pqCtLmHNjZ){puTuJAnoOG = true;}
      else if(pqCtLmHNjZ == ulXEgWHWJE){mkdPYlCdcA = true;}
      if(APsRXAoAob == pXzLmYiCwR){rdbmBcZlBj = true;}
      else if(pXzLmYiCwR == APsRXAoAob){RQyeNfngRi = true;}
      if(UMrKIyJwsy == JPQAUWyflr){ciUyGCtMib = true;}
      else if(JPQAUWyflr == UMrKIyJwsy){DlLzpNCidY = true;}
      if(WFghAyusBh == ilfKsDlgPa){poSExrrFeo = true;}
      else if(ilfKsDlgPa == WFghAyusBh){NhLzUIuXAh = true;}
      if(xHSWxYDTTQ == IXiUZgilew){SksMayITYJ = true;}
      else if(IXiUZgilew == xHSWxYDTTQ){cVwKYBXlJC = true;}
      if(iGTNmisMuh == CaKXrZaCZo){GJpsrGZVnH = true;}
      else if(CaKXrZaCZo == iGTNmisMuh){CxnMTBYeYL = true;}
      if(NLdLhuiLRZ == oaaqqEqnRj){GbGmPDLWpJ = true;}
      if(FuzGdMsVNj == lBmUIlgwZm){jTGMQroIWI = true;}
      if(uobbOPkStQ == mMBopHaIST){tZmZUfzYLp = true;}
      while(oaaqqEqnRj == NLdLhuiLRZ){jSzDmiEzKE = true;}
      while(lBmUIlgwZm == lBmUIlgwZm){kPfjGhoAao = true;}
      while(mMBopHaIST == mMBopHaIST){pPZbVPszeT = true;}
      if(cjHZlgwqcV == true){cjHZlgwqcV = false;}
      if(puTuJAnoOG == true){puTuJAnoOG = false;}
      if(rdbmBcZlBj == true){rdbmBcZlBj = false;}
      if(ciUyGCtMib == true){ciUyGCtMib = false;}
      if(poSExrrFeo == true){poSExrrFeo = false;}
      if(SksMayITYJ == true){SksMayITYJ = false;}
      if(GJpsrGZVnH == true){GJpsrGZVnH = false;}
      if(GbGmPDLWpJ == true){GbGmPDLWpJ = false;}
      if(jTGMQroIWI == true){jTGMQroIWI = false;}
      if(tZmZUfzYLp == true){tZmZUfzYLp = false;}
      if(SWRWhqeGwX == true){SWRWhqeGwX = false;}
      if(mkdPYlCdcA == true){mkdPYlCdcA = false;}
      if(RQyeNfngRi == true){RQyeNfngRi = false;}
      if(DlLzpNCidY == true){DlLzpNCidY = false;}
      if(NhLzUIuXAh == true){NhLzUIuXAh = false;}
      if(cVwKYBXlJC == true){cVwKYBXlJC = false;}
      if(CxnMTBYeYL == true){CxnMTBYeYL = false;}
      if(jSzDmiEzKE == true){jSzDmiEzKE = false;}
      if(kPfjGhoAao == true){kPfjGhoAao = false;}
      if(pPZbVPszeT == true){pPZbVPszeT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOFAGPDGUZ
{ 
  void pVHGGerKtL()
  { 
      bool EGmFhHkinF = false;
      bool NRPBJMoSsr = false;
      bool gSECOSHUAC = false;
      bool fbULVcsBQz = false;
      bool FfuUNmUJrk = false;
      bool fMubrlCkqO = false;
      bool zPikZkwEef = false;
      bool TmCsmBWina = false;
      bool yxbOWSgsSi = false;
      bool ZIJBzowKub = false;
      bool qQeMRrKBnq = false;
      bool OTwQQCmTNG = false;
      bool ECkuFLcBty = false;
      bool EMnMigSPxd = false;
      bool IeFbTGLsjx = false;
      bool BcwnXneiGF = false;
      bool PJHpmCfjgi = false;
      bool iXVjyYxJaz = false;
      bool zjQxwaPAnu = false;
      bool CjJqOyXOoR = false;
      string imscqLsnsE;
      string QqZFmfcpUu;
      string jRpCBubqIV;
      string QJPtgBAcCK;
      string hIuqhKgguu;
      string oSKtIQwqau;
      string jBfWnHaeXl;
      string fznJNaWyTp;
      string OtwMgxyVkQ;
      string EJCGafbXDa;
      string jBIJPpeAgh;
      string txXkgoFTpq;
      string JFsHgVxhig;
      string yyurGMlmwq;
      string SxnDVGlQZk;
      string ZIhMReHBbt;
      string rxRziwBedT;
      string DSXyXLQpka;
      string jfHyGpPiab;
      string FjKCyUfnUZ;
      if(imscqLsnsE == jBIJPpeAgh){EGmFhHkinF = true;}
      else if(jBIJPpeAgh == imscqLsnsE){qQeMRrKBnq = true;}
      if(QqZFmfcpUu == txXkgoFTpq){NRPBJMoSsr = true;}
      else if(txXkgoFTpq == QqZFmfcpUu){OTwQQCmTNG = true;}
      if(jRpCBubqIV == JFsHgVxhig){gSECOSHUAC = true;}
      else if(JFsHgVxhig == jRpCBubqIV){ECkuFLcBty = true;}
      if(QJPtgBAcCK == yyurGMlmwq){fbULVcsBQz = true;}
      else if(yyurGMlmwq == QJPtgBAcCK){EMnMigSPxd = true;}
      if(hIuqhKgguu == SxnDVGlQZk){FfuUNmUJrk = true;}
      else if(SxnDVGlQZk == hIuqhKgguu){IeFbTGLsjx = true;}
      if(oSKtIQwqau == ZIhMReHBbt){fMubrlCkqO = true;}
      else if(ZIhMReHBbt == oSKtIQwqau){BcwnXneiGF = true;}
      if(jBfWnHaeXl == rxRziwBedT){zPikZkwEef = true;}
      else if(rxRziwBedT == jBfWnHaeXl){PJHpmCfjgi = true;}
      if(fznJNaWyTp == DSXyXLQpka){TmCsmBWina = true;}
      if(OtwMgxyVkQ == jfHyGpPiab){yxbOWSgsSi = true;}
      if(EJCGafbXDa == FjKCyUfnUZ){ZIJBzowKub = true;}
      while(DSXyXLQpka == fznJNaWyTp){iXVjyYxJaz = true;}
      while(jfHyGpPiab == jfHyGpPiab){zjQxwaPAnu = true;}
      while(FjKCyUfnUZ == FjKCyUfnUZ){CjJqOyXOoR = true;}
      if(EGmFhHkinF == true){EGmFhHkinF = false;}
      if(NRPBJMoSsr == true){NRPBJMoSsr = false;}
      if(gSECOSHUAC == true){gSECOSHUAC = false;}
      if(fbULVcsBQz == true){fbULVcsBQz = false;}
      if(FfuUNmUJrk == true){FfuUNmUJrk = false;}
      if(fMubrlCkqO == true){fMubrlCkqO = false;}
      if(zPikZkwEef == true){zPikZkwEef = false;}
      if(TmCsmBWina == true){TmCsmBWina = false;}
      if(yxbOWSgsSi == true){yxbOWSgsSi = false;}
      if(ZIJBzowKub == true){ZIJBzowKub = false;}
      if(qQeMRrKBnq == true){qQeMRrKBnq = false;}
      if(OTwQQCmTNG == true){OTwQQCmTNG = false;}
      if(ECkuFLcBty == true){ECkuFLcBty = false;}
      if(EMnMigSPxd == true){EMnMigSPxd = false;}
      if(IeFbTGLsjx == true){IeFbTGLsjx = false;}
      if(BcwnXneiGF == true){BcwnXneiGF = false;}
      if(PJHpmCfjgi == true){PJHpmCfjgi = false;}
      if(iXVjyYxJaz == true){iXVjyYxJaz = false;}
      if(zjQxwaPAnu == true){zjQxwaPAnu = false;}
      if(CjJqOyXOoR == true){CjJqOyXOoR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPDHMVJJYN
{ 
  void arNhnBDUMM()
  { 
      bool BzGFLaZhMM = false;
      bool BZNoRIYGqk = false;
      bool IuxEJonqXr = false;
      bool mQANYtFarW = false;
      bool MXrZeiiEFM = false;
      bool XucodFCCuV = false;
      bool lhJUYkZAPX = false;
      bool CxOUXkDWZa = false;
      bool GilLUrmLjT = false;
      bool rDfVjeNXAs = false;
      bool JhngJZgIQr = false;
      bool BebUPDwyAg = false;
      bool yOQwfyRrjs = false;
      bool XfWfQXtEBt = false;
      bool KetqRMbLGg = false;
      bool iPXSuuRrBL = false;
      bool HoXWUUHuDq = false;
      bool IqwFWTTYdS = false;
      bool WGkDKIIDkV = false;
      bool GCDpmVGXWx = false;
      string wAEmoWTSyi;
      string MAnpzRKVUt;
      string dFthfducwx;
      string eiCQnOfFNW;
      string oLMwjeuSbY;
      string fSJySpFWGL;
      string aqWBDcyWBk;
      string kEHxERsyxB;
      string hcAWRMZDyy;
      string IIyCuyoLrG;
      string gYQqmaKMtA;
      string wGZFcypzjq;
      string DtXCbbFFBF;
      string bhGpTJLIip;
      string BNJyBBirYx;
      string IobBDmAOOL;
      string UFKoXOAjlT;
      string lgPsopkZAZ;
      string sMfDxmFEmg;
      string JxsXUwCUZm;
      if(wAEmoWTSyi == gYQqmaKMtA){BzGFLaZhMM = true;}
      else if(gYQqmaKMtA == wAEmoWTSyi){JhngJZgIQr = true;}
      if(MAnpzRKVUt == wGZFcypzjq){BZNoRIYGqk = true;}
      else if(wGZFcypzjq == MAnpzRKVUt){BebUPDwyAg = true;}
      if(dFthfducwx == DtXCbbFFBF){IuxEJonqXr = true;}
      else if(DtXCbbFFBF == dFthfducwx){yOQwfyRrjs = true;}
      if(eiCQnOfFNW == bhGpTJLIip){mQANYtFarW = true;}
      else if(bhGpTJLIip == eiCQnOfFNW){XfWfQXtEBt = true;}
      if(oLMwjeuSbY == BNJyBBirYx){MXrZeiiEFM = true;}
      else if(BNJyBBirYx == oLMwjeuSbY){KetqRMbLGg = true;}
      if(fSJySpFWGL == IobBDmAOOL){XucodFCCuV = true;}
      else if(IobBDmAOOL == fSJySpFWGL){iPXSuuRrBL = true;}
      if(aqWBDcyWBk == UFKoXOAjlT){lhJUYkZAPX = true;}
      else if(UFKoXOAjlT == aqWBDcyWBk){HoXWUUHuDq = true;}
      if(kEHxERsyxB == lgPsopkZAZ){CxOUXkDWZa = true;}
      if(hcAWRMZDyy == sMfDxmFEmg){GilLUrmLjT = true;}
      if(IIyCuyoLrG == JxsXUwCUZm){rDfVjeNXAs = true;}
      while(lgPsopkZAZ == kEHxERsyxB){IqwFWTTYdS = true;}
      while(sMfDxmFEmg == sMfDxmFEmg){WGkDKIIDkV = true;}
      while(JxsXUwCUZm == JxsXUwCUZm){GCDpmVGXWx = true;}
      if(BzGFLaZhMM == true){BzGFLaZhMM = false;}
      if(BZNoRIYGqk == true){BZNoRIYGqk = false;}
      if(IuxEJonqXr == true){IuxEJonqXr = false;}
      if(mQANYtFarW == true){mQANYtFarW = false;}
      if(MXrZeiiEFM == true){MXrZeiiEFM = false;}
      if(XucodFCCuV == true){XucodFCCuV = false;}
      if(lhJUYkZAPX == true){lhJUYkZAPX = false;}
      if(CxOUXkDWZa == true){CxOUXkDWZa = false;}
      if(GilLUrmLjT == true){GilLUrmLjT = false;}
      if(rDfVjeNXAs == true){rDfVjeNXAs = false;}
      if(JhngJZgIQr == true){JhngJZgIQr = false;}
      if(BebUPDwyAg == true){BebUPDwyAg = false;}
      if(yOQwfyRrjs == true){yOQwfyRrjs = false;}
      if(XfWfQXtEBt == true){XfWfQXtEBt = false;}
      if(KetqRMbLGg == true){KetqRMbLGg = false;}
      if(iPXSuuRrBL == true){iPXSuuRrBL = false;}
      if(HoXWUUHuDq == true){HoXWUUHuDq = false;}
      if(IqwFWTTYdS == true){IqwFWTTYdS = false;}
      if(WGkDKIIDkV == true){WGkDKIIDkV = false;}
      if(GCDpmVGXWx == true){GCDpmVGXWx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYXGQFFSSI
{ 
  void rFzyKBWSjr()
  { 
      bool MerflhiuMo = false;
      bool ZBcXAKEVEe = false;
      bool aEQouWPgKY = false;
      bool xDQrBDZQsk = false;
      bool sXQioxKFEF = false;
      bool HXWuUIODjO = false;
      bool RCknrVkjWx = false;
      bool kmcSlDmhzy = false;
      bool MKbERZfVXs = false;
      bool oWgdTqlcpS = false;
      bool LZiHUTtEJR = false;
      bool UgDlCGZfVR = false;
      bool oPMcIOGzzt = false;
      bool QJqglmaUjy = false;
      bool fbLFXHSubM = false;
      bool QGHYcuMFyG = false;
      bool MtEOBLpWzO = false;
      bool fFwXlNDHFA = false;
      bool uLXldJCSDp = false;
      bool ZVVckkXxDL = false;
      string IBXViTsmar;
      string CNCALAoyRk;
      string zmNEomCXhR;
      string DpPpwthCLd;
      string FCCmeicBMF;
      string eNRxCUmTfw;
      string QUEIoLxLEQ;
      string RlmnewjaYG;
      string JBLcmoYRma;
      string HOWOMkxsyT;
      string kQwumracSF;
      string kLtZmPJbVz;
      string meYdJDPYbt;
      string yqcFUrFPot;
      string NuzhouTxaw;
      string aVXygFrRlj;
      string cCBXHtioEu;
      string KslbkqfpnN;
      string iSxeSbSdXP;
      string zmdFQLtbZu;
      if(IBXViTsmar == kQwumracSF){MerflhiuMo = true;}
      else if(kQwumracSF == IBXViTsmar){LZiHUTtEJR = true;}
      if(CNCALAoyRk == kLtZmPJbVz){ZBcXAKEVEe = true;}
      else if(kLtZmPJbVz == CNCALAoyRk){UgDlCGZfVR = true;}
      if(zmNEomCXhR == meYdJDPYbt){aEQouWPgKY = true;}
      else if(meYdJDPYbt == zmNEomCXhR){oPMcIOGzzt = true;}
      if(DpPpwthCLd == yqcFUrFPot){xDQrBDZQsk = true;}
      else if(yqcFUrFPot == DpPpwthCLd){QJqglmaUjy = true;}
      if(FCCmeicBMF == NuzhouTxaw){sXQioxKFEF = true;}
      else if(NuzhouTxaw == FCCmeicBMF){fbLFXHSubM = true;}
      if(eNRxCUmTfw == aVXygFrRlj){HXWuUIODjO = true;}
      else if(aVXygFrRlj == eNRxCUmTfw){QGHYcuMFyG = true;}
      if(QUEIoLxLEQ == cCBXHtioEu){RCknrVkjWx = true;}
      else if(cCBXHtioEu == QUEIoLxLEQ){MtEOBLpWzO = true;}
      if(RlmnewjaYG == KslbkqfpnN){kmcSlDmhzy = true;}
      if(JBLcmoYRma == iSxeSbSdXP){MKbERZfVXs = true;}
      if(HOWOMkxsyT == zmdFQLtbZu){oWgdTqlcpS = true;}
      while(KslbkqfpnN == RlmnewjaYG){fFwXlNDHFA = true;}
      while(iSxeSbSdXP == iSxeSbSdXP){uLXldJCSDp = true;}
      while(zmdFQLtbZu == zmdFQLtbZu){ZVVckkXxDL = true;}
      if(MerflhiuMo == true){MerflhiuMo = false;}
      if(ZBcXAKEVEe == true){ZBcXAKEVEe = false;}
      if(aEQouWPgKY == true){aEQouWPgKY = false;}
      if(xDQrBDZQsk == true){xDQrBDZQsk = false;}
      if(sXQioxKFEF == true){sXQioxKFEF = false;}
      if(HXWuUIODjO == true){HXWuUIODjO = false;}
      if(RCknrVkjWx == true){RCknrVkjWx = false;}
      if(kmcSlDmhzy == true){kmcSlDmhzy = false;}
      if(MKbERZfVXs == true){MKbERZfVXs = false;}
      if(oWgdTqlcpS == true){oWgdTqlcpS = false;}
      if(LZiHUTtEJR == true){LZiHUTtEJR = false;}
      if(UgDlCGZfVR == true){UgDlCGZfVR = false;}
      if(oPMcIOGzzt == true){oPMcIOGzzt = false;}
      if(QJqglmaUjy == true){QJqglmaUjy = false;}
      if(fbLFXHSubM == true){fbLFXHSubM = false;}
      if(QGHYcuMFyG == true){QGHYcuMFyG = false;}
      if(MtEOBLpWzO == true){MtEOBLpWzO = false;}
      if(fFwXlNDHFA == true){fFwXlNDHFA = false;}
      if(uLXldJCSDp == true){uLXldJCSDp = false;}
      if(ZVVckkXxDL == true){ZVVckkXxDL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSVLPQETNW
{ 
  void yahawfeVRr()
  { 
      bool sSaEMrNiAP = false;
      bool ijkFbUtjgn = false;
      bool TlnpjjKsqQ = false;
      bool YEAPPkNbcc = false;
      bool frSYSdzSpw = false;
      bool WnnWVHdkUb = false;
      bool hUrjpejVop = false;
      bool HRGEHbTPWG = false;
      bool jrDtskQdtH = false;
      bool HcHAuLAhhn = false;
      bool tdczoFgiOt = false;
      bool mNNOroQxqF = false;
      bool NFahidJFJu = false;
      bool blhiLGODEm = false;
      bool DgPATsOsIF = false;
      bool uCpcZnCuQL = false;
      bool wbZSRBfdCk = false;
      bool aNsDBgpaNp = false;
      bool OPwEAZuFJW = false;
      bool DTlsqbHwhS = false;
      string ISDJpCccHA;
      string klJJpuRlrX;
      string cxAMpSqxnh;
      string TtRGOZSolp;
      string cYBoAZFdmI;
      string qNztILSqTX;
      string KfoYfqTDtP;
      string bbACuEuKLQ;
      string NMJepGuWxC;
      string HbVOexjbIJ;
      string FCjWgPNwzD;
      string PHeCKxVJiZ;
      string wwFrIAGlWx;
      string UTBCKKclyZ;
      string ryWtlzwSEg;
      string bZrhNIwqOf;
      string IbZCiwFcrz;
      string UiLIgxYLFJ;
      string EngoVtbTnC;
      string OkXRRQXUKp;
      if(ISDJpCccHA == FCjWgPNwzD){sSaEMrNiAP = true;}
      else if(FCjWgPNwzD == ISDJpCccHA){tdczoFgiOt = true;}
      if(klJJpuRlrX == PHeCKxVJiZ){ijkFbUtjgn = true;}
      else if(PHeCKxVJiZ == klJJpuRlrX){mNNOroQxqF = true;}
      if(cxAMpSqxnh == wwFrIAGlWx){TlnpjjKsqQ = true;}
      else if(wwFrIAGlWx == cxAMpSqxnh){NFahidJFJu = true;}
      if(TtRGOZSolp == UTBCKKclyZ){YEAPPkNbcc = true;}
      else if(UTBCKKclyZ == TtRGOZSolp){blhiLGODEm = true;}
      if(cYBoAZFdmI == ryWtlzwSEg){frSYSdzSpw = true;}
      else if(ryWtlzwSEg == cYBoAZFdmI){DgPATsOsIF = true;}
      if(qNztILSqTX == bZrhNIwqOf){WnnWVHdkUb = true;}
      else if(bZrhNIwqOf == qNztILSqTX){uCpcZnCuQL = true;}
      if(KfoYfqTDtP == IbZCiwFcrz){hUrjpejVop = true;}
      else if(IbZCiwFcrz == KfoYfqTDtP){wbZSRBfdCk = true;}
      if(bbACuEuKLQ == UiLIgxYLFJ){HRGEHbTPWG = true;}
      if(NMJepGuWxC == EngoVtbTnC){jrDtskQdtH = true;}
      if(HbVOexjbIJ == OkXRRQXUKp){HcHAuLAhhn = true;}
      while(UiLIgxYLFJ == bbACuEuKLQ){aNsDBgpaNp = true;}
      while(EngoVtbTnC == EngoVtbTnC){OPwEAZuFJW = true;}
      while(OkXRRQXUKp == OkXRRQXUKp){DTlsqbHwhS = true;}
      if(sSaEMrNiAP == true){sSaEMrNiAP = false;}
      if(ijkFbUtjgn == true){ijkFbUtjgn = false;}
      if(TlnpjjKsqQ == true){TlnpjjKsqQ = false;}
      if(YEAPPkNbcc == true){YEAPPkNbcc = false;}
      if(frSYSdzSpw == true){frSYSdzSpw = false;}
      if(WnnWVHdkUb == true){WnnWVHdkUb = false;}
      if(hUrjpejVop == true){hUrjpejVop = false;}
      if(HRGEHbTPWG == true){HRGEHbTPWG = false;}
      if(jrDtskQdtH == true){jrDtskQdtH = false;}
      if(HcHAuLAhhn == true){HcHAuLAhhn = false;}
      if(tdczoFgiOt == true){tdczoFgiOt = false;}
      if(mNNOroQxqF == true){mNNOroQxqF = false;}
      if(NFahidJFJu == true){NFahidJFJu = false;}
      if(blhiLGODEm == true){blhiLGODEm = false;}
      if(DgPATsOsIF == true){DgPATsOsIF = false;}
      if(uCpcZnCuQL == true){uCpcZnCuQL = false;}
      if(wbZSRBfdCk == true){wbZSRBfdCk = false;}
      if(aNsDBgpaNp == true){aNsDBgpaNp = false;}
      if(OPwEAZuFJW == true){OPwEAZuFJW = false;}
      if(DTlsqbHwhS == true){DTlsqbHwhS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXJNMDOMCX
{ 
  void qLlMXrmyBZ()
  { 
      bool PtUIohkIHA = false;
      bool EdoMiiUILT = false;
      bool KjaoOlcLoi = false;
      bool wxxJAUCmun = false;
      bool ntPzxDNZoo = false;
      bool nWMyOfSfsC = false;
      bool EYTXDGfeMO = false;
      bool fgMWePTbqL = false;
      bool YDWzuZjzuU = false;
      bool CWtsjPZqwq = false;
      bool WiNaIGKpSz = false;
      bool LpnhdABTcc = false;
      bool VfjrMJmSmP = false;
      bool oceAnopwpn = false;
      bool PtguILhLOi = false;
      bool NGNSUpzUNz = false;
      bool TqCDJiKmsn = false;
      bool KFdoMazniA = false;
      bool aaDEBiOMfx = false;
      bool pUhqTYrdlZ = false;
      string CcVaFzyJtp;
      string mCmxEnrUtr;
      string QZLOanLkwb;
      string iENNBQfdsh;
      string rqiYKsspEq;
      string ErVCNcQHAR;
      string mNMRHhnZum;
      string INbLzZpmDg;
      string tVgFXphKzY;
      string AYdauedQQb;
      string ETtQhqQJDn;
      string lcDSWQfHtR;
      string AdZVmjiAQU;
      string uYWbbaaPWf;
      string YXHKlWULEe;
      string yVWzbasYcy;
      string HQshsMGapw;
      string oPkNrbWPjQ;
      string OXukWYCWzB;
      string gCmYYIeYRZ;
      if(CcVaFzyJtp == ETtQhqQJDn){PtUIohkIHA = true;}
      else if(ETtQhqQJDn == CcVaFzyJtp){WiNaIGKpSz = true;}
      if(mCmxEnrUtr == lcDSWQfHtR){EdoMiiUILT = true;}
      else if(lcDSWQfHtR == mCmxEnrUtr){LpnhdABTcc = true;}
      if(QZLOanLkwb == AdZVmjiAQU){KjaoOlcLoi = true;}
      else if(AdZVmjiAQU == QZLOanLkwb){VfjrMJmSmP = true;}
      if(iENNBQfdsh == uYWbbaaPWf){wxxJAUCmun = true;}
      else if(uYWbbaaPWf == iENNBQfdsh){oceAnopwpn = true;}
      if(rqiYKsspEq == YXHKlWULEe){ntPzxDNZoo = true;}
      else if(YXHKlWULEe == rqiYKsspEq){PtguILhLOi = true;}
      if(ErVCNcQHAR == yVWzbasYcy){nWMyOfSfsC = true;}
      else if(yVWzbasYcy == ErVCNcQHAR){NGNSUpzUNz = true;}
      if(mNMRHhnZum == HQshsMGapw){EYTXDGfeMO = true;}
      else if(HQshsMGapw == mNMRHhnZum){TqCDJiKmsn = true;}
      if(INbLzZpmDg == oPkNrbWPjQ){fgMWePTbqL = true;}
      if(tVgFXphKzY == OXukWYCWzB){YDWzuZjzuU = true;}
      if(AYdauedQQb == gCmYYIeYRZ){CWtsjPZqwq = true;}
      while(oPkNrbWPjQ == INbLzZpmDg){KFdoMazniA = true;}
      while(OXukWYCWzB == OXukWYCWzB){aaDEBiOMfx = true;}
      while(gCmYYIeYRZ == gCmYYIeYRZ){pUhqTYrdlZ = true;}
      if(PtUIohkIHA == true){PtUIohkIHA = false;}
      if(EdoMiiUILT == true){EdoMiiUILT = false;}
      if(KjaoOlcLoi == true){KjaoOlcLoi = false;}
      if(wxxJAUCmun == true){wxxJAUCmun = false;}
      if(ntPzxDNZoo == true){ntPzxDNZoo = false;}
      if(nWMyOfSfsC == true){nWMyOfSfsC = false;}
      if(EYTXDGfeMO == true){EYTXDGfeMO = false;}
      if(fgMWePTbqL == true){fgMWePTbqL = false;}
      if(YDWzuZjzuU == true){YDWzuZjzuU = false;}
      if(CWtsjPZqwq == true){CWtsjPZqwq = false;}
      if(WiNaIGKpSz == true){WiNaIGKpSz = false;}
      if(LpnhdABTcc == true){LpnhdABTcc = false;}
      if(VfjrMJmSmP == true){VfjrMJmSmP = false;}
      if(oceAnopwpn == true){oceAnopwpn = false;}
      if(PtguILhLOi == true){PtguILhLOi = false;}
      if(NGNSUpzUNz == true){NGNSUpzUNz = false;}
      if(TqCDJiKmsn == true){TqCDJiKmsn = false;}
      if(KFdoMazniA == true){KFdoMazniA = false;}
      if(aaDEBiOMfx == true){aaDEBiOMfx = false;}
      if(pUhqTYrdlZ == true){pUhqTYrdlZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFUBNYTIVX
{ 
  void MIuAOajHfl()
  { 
      bool iwogMNfTIi = false;
      bool LgmJVBXPnk = false;
      bool IdoBrkMdkw = false;
      bool LcwNwPpuBI = false;
      bool BThZZNmUjA = false;
      bool zckqwFHnob = false;
      bool AChMXikYNF = false;
      bool KcNfiouOae = false;
      bool yrskwhqERp = false;
      bool ICGZHzkVCq = false;
      bool bNHeoWOFIH = false;
      bool JrNJcIIxPo = false;
      bool qfHWxHVnXi = false;
      bool EZMiCjjOuZ = false;
      bool SlwKgPowwy = false;
      bool qmFNAwGkgg = false;
      bool AagYCiedGs = false;
      bool YtBoVEixog = false;
      bool SYqYrQTziG = false;
      bool dzgOYrFXHx = false;
      string LyiDmBsYjm;
      string PMwVumgYVM;
      string jwWfMbzqTo;
      string YECRHTqHTS;
      string TuYhXKDpzm;
      string PDSeFObCpL;
      string BCFuNLJeNa;
      string wZFCrnXnIC;
      string YJqfYVkWLr;
      string rnQHQQpcUM;
      string BXbXqpxPlQ;
      string qnsnmrKZVr;
      string ZmSUiHIxlb;
      string ytTuAAgToi;
      string XVjtBDucUX;
      string FQHcmOFGoi;
      string gAcKSwUymm;
      string LqjmTDCXTe;
      string MfcNVhmqIl;
      string tZeGBWrZbF;
      if(LyiDmBsYjm == BXbXqpxPlQ){iwogMNfTIi = true;}
      else if(BXbXqpxPlQ == LyiDmBsYjm){bNHeoWOFIH = true;}
      if(PMwVumgYVM == qnsnmrKZVr){LgmJVBXPnk = true;}
      else if(qnsnmrKZVr == PMwVumgYVM){JrNJcIIxPo = true;}
      if(jwWfMbzqTo == ZmSUiHIxlb){IdoBrkMdkw = true;}
      else if(ZmSUiHIxlb == jwWfMbzqTo){qfHWxHVnXi = true;}
      if(YECRHTqHTS == ytTuAAgToi){LcwNwPpuBI = true;}
      else if(ytTuAAgToi == YECRHTqHTS){EZMiCjjOuZ = true;}
      if(TuYhXKDpzm == XVjtBDucUX){BThZZNmUjA = true;}
      else if(XVjtBDucUX == TuYhXKDpzm){SlwKgPowwy = true;}
      if(PDSeFObCpL == FQHcmOFGoi){zckqwFHnob = true;}
      else if(FQHcmOFGoi == PDSeFObCpL){qmFNAwGkgg = true;}
      if(BCFuNLJeNa == gAcKSwUymm){AChMXikYNF = true;}
      else if(gAcKSwUymm == BCFuNLJeNa){AagYCiedGs = true;}
      if(wZFCrnXnIC == LqjmTDCXTe){KcNfiouOae = true;}
      if(YJqfYVkWLr == MfcNVhmqIl){yrskwhqERp = true;}
      if(rnQHQQpcUM == tZeGBWrZbF){ICGZHzkVCq = true;}
      while(LqjmTDCXTe == wZFCrnXnIC){YtBoVEixog = true;}
      while(MfcNVhmqIl == MfcNVhmqIl){SYqYrQTziG = true;}
      while(tZeGBWrZbF == tZeGBWrZbF){dzgOYrFXHx = true;}
      if(iwogMNfTIi == true){iwogMNfTIi = false;}
      if(LgmJVBXPnk == true){LgmJVBXPnk = false;}
      if(IdoBrkMdkw == true){IdoBrkMdkw = false;}
      if(LcwNwPpuBI == true){LcwNwPpuBI = false;}
      if(BThZZNmUjA == true){BThZZNmUjA = false;}
      if(zckqwFHnob == true){zckqwFHnob = false;}
      if(AChMXikYNF == true){AChMXikYNF = false;}
      if(KcNfiouOae == true){KcNfiouOae = false;}
      if(yrskwhqERp == true){yrskwhqERp = false;}
      if(ICGZHzkVCq == true){ICGZHzkVCq = false;}
      if(bNHeoWOFIH == true){bNHeoWOFIH = false;}
      if(JrNJcIIxPo == true){JrNJcIIxPo = false;}
      if(qfHWxHVnXi == true){qfHWxHVnXi = false;}
      if(EZMiCjjOuZ == true){EZMiCjjOuZ = false;}
      if(SlwKgPowwy == true){SlwKgPowwy = false;}
      if(qmFNAwGkgg == true){qmFNAwGkgg = false;}
      if(AagYCiedGs == true){AagYCiedGs = false;}
      if(YtBoVEixog == true){YtBoVEixog = false;}
      if(SYqYrQTziG == true){SYqYrQTziG = false;}
      if(dzgOYrFXHx == true){dzgOYrFXHx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAVHKRDFZP
{ 
  void qNoCrMnmHz()
  { 
      bool esCEEkTikA = false;
      bool KjIGWYToAh = false;
      bool VldhbkagEE = false;
      bool QfeAEBBahw = false;
      bool DkbLqKTsGt = false;
      bool GQSFGrPUbS = false;
      bool KldgidFHCV = false;
      bool XsGDdkJRpR = false;
      bool QgZKxANYtM = false;
      bool kgyOkRGubM = false;
      bool EMqkWNJOaU = false;
      bool ixdKCcLTji = false;
      bool QfMokptqRM = false;
      bool dOpcMEpomj = false;
      bool pzyZcmCnMI = false;
      bool FmKrwYABAf = false;
      bool SRwOqTGBxx = false;
      bool lVfAsRhmMx = false;
      bool nGdJGqDyfn = false;
      bool EooGQXCiiI = false;
      string ollgRjkXsh;
      string OILtHWfgMQ;
      string bQIFLlNXXI;
      string ttezKkmFbO;
      string rlMIwnaRaf;
      string tMeBxXcgUf;
      string WNzjmUdMiV;
      string jaExYoEzJX;
      string KwwrOhPdBm;
      string IFjwrdlbVb;
      string KNhEwSHgcI;
      string TdWxUaRHUF;
      string EALwNdpHEt;
      string CbdhMxNqww;
      string ZhBsTdimbR;
      string MeHQWKCkqR;
      string czchFqzojW;
      string MaLYeWzRcj;
      string uDfmhXUNLC;
      string tbAdTaFSmb;
      if(ollgRjkXsh == KNhEwSHgcI){esCEEkTikA = true;}
      else if(KNhEwSHgcI == ollgRjkXsh){EMqkWNJOaU = true;}
      if(OILtHWfgMQ == TdWxUaRHUF){KjIGWYToAh = true;}
      else if(TdWxUaRHUF == OILtHWfgMQ){ixdKCcLTji = true;}
      if(bQIFLlNXXI == EALwNdpHEt){VldhbkagEE = true;}
      else if(EALwNdpHEt == bQIFLlNXXI){QfMokptqRM = true;}
      if(ttezKkmFbO == CbdhMxNqww){QfeAEBBahw = true;}
      else if(CbdhMxNqww == ttezKkmFbO){dOpcMEpomj = true;}
      if(rlMIwnaRaf == ZhBsTdimbR){DkbLqKTsGt = true;}
      else if(ZhBsTdimbR == rlMIwnaRaf){pzyZcmCnMI = true;}
      if(tMeBxXcgUf == MeHQWKCkqR){GQSFGrPUbS = true;}
      else if(MeHQWKCkqR == tMeBxXcgUf){FmKrwYABAf = true;}
      if(WNzjmUdMiV == czchFqzojW){KldgidFHCV = true;}
      else if(czchFqzojW == WNzjmUdMiV){SRwOqTGBxx = true;}
      if(jaExYoEzJX == MaLYeWzRcj){XsGDdkJRpR = true;}
      if(KwwrOhPdBm == uDfmhXUNLC){QgZKxANYtM = true;}
      if(IFjwrdlbVb == tbAdTaFSmb){kgyOkRGubM = true;}
      while(MaLYeWzRcj == jaExYoEzJX){lVfAsRhmMx = true;}
      while(uDfmhXUNLC == uDfmhXUNLC){nGdJGqDyfn = true;}
      while(tbAdTaFSmb == tbAdTaFSmb){EooGQXCiiI = true;}
      if(esCEEkTikA == true){esCEEkTikA = false;}
      if(KjIGWYToAh == true){KjIGWYToAh = false;}
      if(VldhbkagEE == true){VldhbkagEE = false;}
      if(QfeAEBBahw == true){QfeAEBBahw = false;}
      if(DkbLqKTsGt == true){DkbLqKTsGt = false;}
      if(GQSFGrPUbS == true){GQSFGrPUbS = false;}
      if(KldgidFHCV == true){KldgidFHCV = false;}
      if(XsGDdkJRpR == true){XsGDdkJRpR = false;}
      if(QgZKxANYtM == true){QgZKxANYtM = false;}
      if(kgyOkRGubM == true){kgyOkRGubM = false;}
      if(EMqkWNJOaU == true){EMqkWNJOaU = false;}
      if(ixdKCcLTji == true){ixdKCcLTji = false;}
      if(QfMokptqRM == true){QfMokptqRM = false;}
      if(dOpcMEpomj == true){dOpcMEpomj = false;}
      if(pzyZcmCnMI == true){pzyZcmCnMI = false;}
      if(FmKrwYABAf == true){FmKrwYABAf = false;}
      if(SRwOqTGBxx == true){SRwOqTGBxx = false;}
      if(lVfAsRhmMx == true){lVfAsRhmMx = false;}
      if(nGdJGqDyfn == true){nGdJGqDyfn = false;}
      if(EooGQXCiiI == true){EooGQXCiiI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYJZCJMYEP
{ 
  void XICVzajnXk()
  { 
      bool fKWppexEiJ = false;
      bool ErFDcCwrNC = false;
      bool qQGndWilDw = false;
      bool EIxqrVHccU = false;
      bool UbakRBBXVb = false;
      bool SweqXPDiLS = false;
      bool uLAmFuuNKH = false;
      bool uSOshOpVVc = false;
      bool VLPbcHdFTc = false;
      bool SYQJYIbmeW = false;
      bool GmMOgzgkJI = false;
      bool YhMixiuYJy = false;
      bool RotgnWCFTY = false;
      bool mCpzViyAuc = false;
      bool ZrwKEkLgMp = false;
      bool NCdgEQrfZJ = false;
      bool xbRjVWqNNO = false;
      bool kucfXZsjcD = false;
      bool KVrdLjXJtF = false;
      bool pSZkfxZLng = false;
      string gHihWnMccf;
      string EPTFVQYgBb;
      string KknmJAMkWd;
      string QJDecFJskt;
      string gihzrWfkYJ;
      string YqIwwwTuYV;
      string aaGzPuMobQ;
      string GfuHtbCnul;
      string UbLMEZBGig;
      string kNTOSFbhjw;
      string KpIHDsuABT;
      string seAlByPtto;
      string sFGuesLfno;
      string zUEybdTEIL;
      string dAEOnGMgNU;
      string phmtCFjMbJ;
      string gOLMTXaCKX;
      string dLkiLsAqHY;
      string fdSTzRgJuW;
      string sGbzeOortP;
      if(gHihWnMccf == KpIHDsuABT){fKWppexEiJ = true;}
      else if(KpIHDsuABT == gHihWnMccf){GmMOgzgkJI = true;}
      if(EPTFVQYgBb == seAlByPtto){ErFDcCwrNC = true;}
      else if(seAlByPtto == EPTFVQYgBb){YhMixiuYJy = true;}
      if(KknmJAMkWd == sFGuesLfno){qQGndWilDw = true;}
      else if(sFGuesLfno == KknmJAMkWd){RotgnWCFTY = true;}
      if(QJDecFJskt == zUEybdTEIL){EIxqrVHccU = true;}
      else if(zUEybdTEIL == QJDecFJskt){mCpzViyAuc = true;}
      if(gihzrWfkYJ == dAEOnGMgNU){UbakRBBXVb = true;}
      else if(dAEOnGMgNU == gihzrWfkYJ){ZrwKEkLgMp = true;}
      if(YqIwwwTuYV == phmtCFjMbJ){SweqXPDiLS = true;}
      else if(phmtCFjMbJ == YqIwwwTuYV){NCdgEQrfZJ = true;}
      if(aaGzPuMobQ == gOLMTXaCKX){uLAmFuuNKH = true;}
      else if(gOLMTXaCKX == aaGzPuMobQ){xbRjVWqNNO = true;}
      if(GfuHtbCnul == dLkiLsAqHY){uSOshOpVVc = true;}
      if(UbLMEZBGig == fdSTzRgJuW){VLPbcHdFTc = true;}
      if(kNTOSFbhjw == sGbzeOortP){SYQJYIbmeW = true;}
      while(dLkiLsAqHY == GfuHtbCnul){kucfXZsjcD = true;}
      while(fdSTzRgJuW == fdSTzRgJuW){KVrdLjXJtF = true;}
      while(sGbzeOortP == sGbzeOortP){pSZkfxZLng = true;}
      if(fKWppexEiJ == true){fKWppexEiJ = false;}
      if(ErFDcCwrNC == true){ErFDcCwrNC = false;}
      if(qQGndWilDw == true){qQGndWilDw = false;}
      if(EIxqrVHccU == true){EIxqrVHccU = false;}
      if(UbakRBBXVb == true){UbakRBBXVb = false;}
      if(SweqXPDiLS == true){SweqXPDiLS = false;}
      if(uLAmFuuNKH == true){uLAmFuuNKH = false;}
      if(uSOshOpVVc == true){uSOshOpVVc = false;}
      if(VLPbcHdFTc == true){VLPbcHdFTc = false;}
      if(SYQJYIbmeW == true){SYQJYIbmeW = false;}
      if(GmMOgzgkJI == true){GmMOgzgkJI = false;}
      if(YhMixiuYJy == true){YhMixiuYJy = false;}
      if(RotgnWCFTY == true){RotgnWCFTY = false;}
      if(mCpzViyAuc == true){mCpzViyAuc = false;}
      if(ZrwKEkLgMp == true){ZrwKEkLgMp = false;}
      if(NCdgEQrfZJ == true){NCdgEQrfZJ = false;}
      if(xbRjVWqNNO == true){xbRjVWqNNO = false;}
      if(kucfXZsjcD == true){kucfXZsjcD = false;}
      if(KVrdLjXJtF == true){KVrdLjXJtF = false;}
      if(pSZkfxZLng == true){pSZkfxZLng = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACZZASHLKB
{ 
  void HBytkAZHsk()
  { 
      bool HVNybedjqD = false;
      bool bPFSZDteeo = false;
      bool orQaudufAE = false;
      bool WYSkjJbNAm = false;
      bool NIDfLjQNxR = false;
      bool DpcqKPElDx = false;
      bool iyjmfDwUhQ = false;
      bool afdrafnjPL = false;
      bool MghiAfuaZU = false;
      bool EoKCDPXQAH = false;
      bool mufgpXLjPd = false;
      bool aTVrkBPBlz = false;
      bool HVuNLlUboL = false;
      bool HXjHXRBArc = false;
      bool ULKuskSSRB = false;
      bool zWeAARASUD = false;
      bool CjuEVDiOTS = false;
      bool AOIIewKzTa = false;
      bool SBJmLkrjHF = false;
      bool QifoakPFYo = false;
      string sWyAqDCOnN;
      string HJpMogrJYh;
      string UbKWzsPtwj;
      string oxwLfhcnAd;
      string igqXaHFrFL;
      string NWHUsQMaBx;
      string mIREXKNdgH;
      string DEJuznkmuq;
      string nXokWRoaSO;
      string UCmCqZOmzQ;
      string taKxHJNMVF;
      string fZfKIOTggG;
      string UlLSmBRGEY;
      string YymewNNqcM;
      string EcFMhtWbsb;
      string GgFsuIOqKF;
      string rGHxfhlAOu;
      string AbDUBrgzkr;
      string eoMbRqstim;
      string zWfXUxVHfA;
      if(sWyAqDCOnN == taKxHJNMVF){HVNybedjqD = true;}
      else if(taKxHJNMVF == sWyAqDCOnN){mufgpXLjPd = true;}
      if(HJpMogrJYh == fZfKIOTggG){bPFSZDteeo = true;}
      else if(fZfKIOTggG == HJpMogrJYh){aTVrkBPBlz = true;}
      if(UbKWzsPtwj == UlLSmBRGEY){orQaudufAE = true;}
      else if(UlLSmBRGEY == UbKWzsPtwj){HVuNLlUboL = true;}
      if(oxwLfhcnAd == YymewNNqcM){WYSkjJbNAm = true;}
      else if(YymewNNqcM == oxwLfhcnAd){HXjHXRBArc = true;}
      if(igqXaHFrFL == EcFMhtWbsb){NIDfLjQNxR = true;}
      else if(EcFMhtWbsb == igqXaHFrFL){ULKuskSSRB = true;}
      if(NWHUsQMaBx == GgFsuIOqKF){DpcqKPElDx = true;}
      else if(GgFsuIOqKF == NWHUsQMaBx){zWeAARASUD = true;}
      if(mIREXKNdgH == rGHxfhlAOu){iyjmfDwUhQ = true;}
      else if(rGHxfhlAOu == mIREXKNdgH){CjuEVDiOTS = true;}
      if(DEJuznkmuq == AbDUBrgzkr){afdrafnjPL = true;}
      if(nXokWRoaSO == eoMbRqstim){MghiAfuaZU = true;}
      if(UCmCqZOmzQ == zWfXUxVHfA){EoKCDPXQAH = true;}
      while(AbDUBrgzkr == DEJuznkmuq){AOIIewKzTa = true;}
      while(eoMbRqstim == eoMbRqstim){SBJmLkrjHF = true;}
      while(zWfXUxVHfA == zWfXUxVHfA){QifoakPFYo = true;}
      if(HVNybedjqD == true){HVNybedjqD = false;}
      if(bPFSZDteeo == true){bPFSZDteeo = false;}
      if(orQaudufAE == true){orQaudufAE = false;}
      if(WYSkjJbNAm == true){WYSkjJbNAm = false;}
      if(NIDfLjQNxR == true){NIDfLjQNxR = false;}
      if(DpcqKPElDx == true){DpcqKPElDx = false;}
      if(iyjmfDwUhQ == true){iyjmfDwUhQ = false;}
      if(afdrafnjPL == true){afdrafnjPL = false;}
      if(MghiAfuaZU == true){MghiAfuaZU = false;}
      if(EoKCDPXQAH == true){EoKCDPXQAH = false;}
      if(mufgpXLjPd == true){mufgpXLjPd = false;}
      if(aTVrkBPBlz == true){aTVrkBPBlz = false;}
      if(HVuNLlUboL == true){HVuNLlUboL = false;}
      if(HXjHXRBArc == true){HXjHXRBArc = false;}
      if(ULKuskSSRB == true){ULKuskSSRB = false;}
      if(zWeAARASUD == true){zWeAARASUD = false;}
      if(CjuEVDiOTS == true){CjuEVDiOTS = false;}
      if(AOIIewKzTa == true){AOIIewKzTa = false;}
      if(SBJmLkrjHF == true){SBJmLkrjHF = false;}
      if(QifoakPFYo == true){QifoakPFYo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKEZOWQEVM
{ 
  void TTxeZpnGnq()
  { 
      bool CenlVwzGmc = false;
      bool pOKrIQPKlP = false;
      bool TiaqsslNyU = false;
      bool NVdQmnaLYg = false;
      bool nuZxDxqKLT = false;
      bool skiucSEwsb = false;
      bool JlISOUktEU = false;
      bool pDlEaXJdnw = false;
      bool BbBeaclhnU = false;
      bool jdSwXCmHih = false;
      bool LxGqcpyeTE = false;
      bool JZHwZhjdqk = false;
      bool hCGjkMkpgY = false;
      bool kCuGjEUKCk = false;
      bool eHNiLJVVVp = false;
      bool RJPxzIqWGP = false;
      bool FIxuSHeBMV = false;
      bool MZbGGaoWYb = false;
      bool pOTqGblxGa = false;
      bool NyDleVJSQD = false;
      string AKKlLmaAPG;
      string HNpjJRMCkY;
      string zGnkmUorwf;
      string ffWxZwVlBl;
      string uQYrZBzMjX;
      string uFOHItVZzp;
      string yhDjabqrKN;
      string uaByciguLl;
      string VbHYjaQPnf;
      string ZumLmNMoRx;
      string JGCVbTDPdZ;
      string NaOMTVaezA;
      string KbDenAnpLP;
      string VqdNbOZkwQ;
      string WAkORygZqR;
      string lhoQmhDXhb;
      string fNEODVwBkE;
      string wphidJqoMo;
      string SOytcnCMZs;
      string LCDUjIuVKw;
      if(AKKlLmaAPG == JGCVbTDPdZ){CenlVwzGmc = true;}
      else if(JGCVbTDPdZ == AKKlLmaAPG){LxGqcpyeTE = true;}
      if(HNpjJRMCkY == NaOMTVaezA){pOKrIQPKlP = true;}
      else if(NaOMTVaezA == HNpjJRMCkY){JZHwZhjdqk = true;}
      if(zGnkmUorwf == KbDenAnpLP){TiaqsslNyU = true;}
      else if(KbDenAnpLP == zGnkmUorwf){hCGjkMkpgY = true;}
      if(ffWxZwVlBl == VqdNbOZkwQ){NVdQmnaLYg = true;}
      else if(VqdNbOZkwQ == ffWxZwVlBl){kCuGjEUKCk = true;}
      if(uQYrZBzMjX == WAkORygZqR){nuZxDxqKLT = true;}
      else if(WAkORygZqR == uQYrZBzMjX){eHNiLJVVVp = true;}
      if(uFOHItVZzp == lhoQmhDXhb){skiucSEwsb = true;}
      else if(lhoQmhDXhb == uFOHItVZzp){RJPxzIqWGP = true;}
      if(yhDjabqrKN == fNEODVwBkE){JlISOUktEU = true;}
      else if(fNEODVwBkE == yhDjabqrKN){FIxuSHeBMV = true;}
      if(uaByciguLl == wphidJqoMo){pDlEaXJdnw = true;}
      if(VbHYjaQPnf == SOytcnCMZs){BbBeaclhnU = true;}
      if(ZumLmNMoRx == LCDUjIuVKw){jdSwXCmHih = true;}
      while(wphidJqoMo == uaByciguLl){MZbGGaoWYb = true;}
      while(SOytcnCMZs == SOytcnCMZs){pOTqGblxGa = true;}
      while(LCDUjIuVKw == LCDUjIuVKw){NyDleVJSQD = true;}
      if(CenlVwzGmc == true){CenlVwzGmc = false;}
      if(pOKrIQPKlP == true){pOKrIQPKlP = false;}
      if(TiaqsslNyU == true){TiaqsslNyU = false;}
      if(NVdQmnaLYg == true){NVdQmnaLYg = false;}
      if(nuZxDxqKLT == true){nuZxDxqKLT = false;}
      if(skiucSEwsb == true){skiucSEwsb = false;}
      if(JlISOUktEU == true){JlISOUktEU = false;}
      if(pDlEaXJdnw == true){pDlEaXJdnw = false;}
      if(BbBeaclhnU == true){BbBeaclhnU = false;}
      if(jdSwXCmHih == true){jdSwXCmHih = false;}
      if(LxGqcpyeTE == true){LxGqcpyeTE = false;}
      if(JZHwZhjdqk == true){JZHwZhjdqk = false;}
      if(hCGjkMkpgY == true){hCGjkMkpgY = false;}
      if(kCuGjEUKCk == true){kCuGjEUKCk = false;}
      if(eHNiLJVVVp == true){eHNiLJVVVp = false;}
      if(RJPxzIqWGP == true){RJPxzIqWGP = false;}
      if(FIxuSHeBMV == true){FIxuSHeBMV = false;}
      if(MZbGGaoWYb == true){MZbGGaoWYb = false;}
      if(pOTqGblxGa == true){pOTqGblxGa = false;}
      if(NyDleVJSQD == true){NyDleVJSQD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDZRTOEVOV
{ 
  void LoILHEUpCw()
  { 
      bool ehhmsgYgzs = false;
      bool cLcARwOxBb = false;
      bool UEzmLBBaDk = false;
      bool QVqhBMKYLG = false;
      bool SdKUxlnHsU = false;
      bool fzkmMZitbq = false;
      bool fycObHTuzE = false;
      bool koltJqsdoY = false;
      bool NsghERjEUa = false;
      bool cQxTaTAwsp = false;
      bool RrIojqNpdV = false;
      bool fEECclRtJJ = false;
      bool WPaXaTqRTo = false;
      bool pxkyGVjryN = false;
      bool EtZyuXLuqn = false;
      bool CGmiTBRkNP = false;
      bool AuVofiTFuH = false;
      bool BZwwFcpbbC = false;
      bool IuafliJBeE = false;
      bool DzdhMIXjRM = false;
      string WyIjzBZmnf;
      string VJGgJVoOGE;
      string ejRldrqdBa;
      string XqfFthAcfz;
      string kGrqxxNJhY;
      string pRZmwlgVGG;
      string KukNHdcBla;
      string ULhGTXrZnf;
      string egwbkFRsII;
      string BdWYooUeiS;
      string TMWGEdjSSX;
      string sGhZbczJbC;
      string MirdZqoIQd;
      string DNqULSJoXG;
      string VyajOtuwwM;
      string pKCfGkTsgM;
      string oaCnUfPNOJ;
      string SJlVfNIHPf;
      string usMEmrKKNa;
      string yQIKRuwlPh;
      if(WyIjzBZmnf == TMWGEdjSSX){ehhmsgYgzs = true;}
      else if(TMWGEdjSSX == WyIjzBZmnf){RrIojqNpdV = true;}
      if(VJGgJVoOGE == sGhZbczJbC){cLcARwOxBb = true;}
      else if(sGhZbczJbC == VJGgJVoOGE){fEECclRtJJ = true;}
      if(ejRldrqdBa == MirdZqoIQd){UEzmLBBaDk = true;}
      else if(MirdZqoIQd == ejRldrqdBa){WPaXaTqRTo = true;}
      if(XqfFthAcfz == DNqULSJoXG){QVqhBMKYLG = true;}
      else if(DNqULSJoXG == XqfFthAcfz){pxkyGVjryN = true;}
      if(kGrqxxNJhY == VyajOtuwwM){SdKUxlnHsU = true;}
      else if(VyajOtuwwM == kGrqxxNJhY){EtZyuXLuqn = true;}
      if(pRZmwlgVGG == pKCfGkTsgM){fzkmMZitbq = true;}
      else if(pKCfGkTsgM == pRZmwlgVGG){CGmiTBRkNP = true;}
      if(KukNHdcBla == oaCnUfPNOJ){fycObHTuzE = true;}
      else if(oaCnUfPNOJ == KukNHdcBla){AuVofiTFuH = true;}
      if(ULhGTXrZnf == SJlVfNIHPf){koltJqsdoY = true;}
      if(egwbkFRsII == usMEmrKKNa){NsghERjEUa = true;}
      if(BdWYooUeiS == yQIKRuwlPh){cQxTaTAwsp = true;}
      while(SJlVfNIHPf == ULhGTXrZnf){BZwwFcpbbC = true;}
      while(usMEmrKKNa == usMEmrKKNa){IuafliJBeE = true;}
      while(yQIKRuwlPh == yQIKRuwlPh){DzdhMIXjRM = true;}
      if(ehhmsgYgzs == true){ehhmsgYgzs = false;}
      if(cLcARwOxBb == true){cLcARwOxBb = false;}
      if(UEzmLBBaDk == true){UEzmLBBaDk = false;}
      if(QVqhBMKYLG == true){QVqhBMKYLG = false;}
      if(SdKUxlnHsU == true){SdKUxlnHsU = false;}
      if(fzkmMZitbq == true){fzkmMZitbq = false;}
      if(fycObHTuzE == true){fycObHTuzE = false;}
      if(koltJqsdoY == true){koltJqsdoY = false;}
      if(NsghERjEUa == true){NsghERjEUa = false;}
      if(cQxTaTAwsp == true){cQxTaTAwsp = false;}
      if(RrIojqNpdV == true){RrIojqNpdV = false;}
      if(fEECclRtJJ == true){fEECclRtJJ = false;}
      if(WPaXaTqRTo == true){WPaXaTqRTo = false;}
      if(pxkyGVjryN == true){pxkyGVjryN = false;}
      if(EtZyuXLuqn == true){EtZyuXLuqn = false;}
      if(CGmiTBRkNP == true){CGmiTBRkNP = false;}
      if(AuVofiTFuH == true){AuVofiTFuH = false;}
      if(BZwwFcpbbC == true){BZwwFcpbbC = false;}
      if(IuafliJBeE == true){IuafliJBeE = false;}
      if(DzdhMIXjRM == true){DzdhMIXjRM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMXMMOCADB
{ 
  void UkWIFmOohO()
  { 
      bool QoeqasBKaC = false;
      bool HaDUBRDIhI = false;
      bool bTiPszQQmt = false;
      bool IntUsSLgwn = false;
      bool PmaLBNRODh = false;
      bool VoNtIwFPyb = false;
      bool bjXgtSfhbi = false;
      bool FVMtsorXNe = false;
      bool gBMEXTaAMw = false;
      bool MwhTLeOtQh = false;
      bool gjmUbzbTAT = false;
      bool DgBSuaWSIa = false;
      bool rfVeVInshN = false;
      bool ZyGfywNqbX = false;
      bool qGzrreuOYk = false;
      bool IukpoBOIzT = false;
      bool LilmsFaUUy = false;
      bool Mepkilfclp = false;
      bool NYUwFdMPpx = false;
      bool hFrIMIUMzm = false;
      string lNKuapiViU;
      string BlRmswLlQH;
      string FeeXgXhZUf;
      string UojBnotpUC;
      string TIsQGqNagD;
      string WqMeKGhlOD;
      string HJADzMBQzE;
      string BUQNmwkOQp;
      string JHrQJdbEpg;
      string GHbRuKHpQs;
      string oxbcCBayrN;
      string UTUYszQjsV;
      string jxZRxssySb;
      string nuxXALePNH;
      string CdMbLmlCYu;
      string tXxtJrXJeI;
      string IcfQZZWxXg;
      string UBVlTGjxGK;
      string HpYWhQxCOI;
      string nVjFzZxwCk;
      if(lNKuapiViU == oxbcCBayrN){QoeqasBKaC = true;}
      else if(oxbcCBayrN == lNKuapiViU){gjmUbzbTAT = true;}
      if(BlRmswLlQH == UTUYszQjsV){HaDUBRDIhI = true;}
      else if(UTUYszQjsV == BlRmswLlQH){DgBSuaWSIa = true;}
      if(FeeXgXhZUf == jxZRxssySb){bTiPszQQmt = true;}
      else if(jxZRxssySb == FeeXgXhZUf){rfVeVInshN = true;}
      if(UojBnotpUC == nuxXALePNH){IntUsSLgwn = true;}
      else if(nuxXALePNH == UojBnotpUC){ZyGfywNqbX = true;}
      if(TIsQGqNagD == CdMbLmlCYu){PmaLBNRODh = true;}
      else if(CdMbLmlCYu == TIsQGqNagD){qGzrreuOYk = true;}
      if(WqMeKGhlOD == tXxtJrXJeI){VoNtIwFPyb = true;}
      else if(tXxtJrXJeI == WqMeKGhlOD){IukpoBOIzT = true;}
      if(HJADzMBQzE == IcfQZZWxXg){bjXgtSfhbi = true;}
      else if(IcfQZZWxXg == HJADzMBQzE){LilmsFaUUy = true;}
      if(BUQNmwkOQp == UBVlTGjxGK){FVMtsorXNe = true;}
      if(JHrQJdbEpg == HpYWhQxCOI){gBMEXTaAMw = true;}
      if(GHbRuKHpQs == nVjFzZxwCk){MwhTLeOtQh = true;}
      while(UBVlTGjxGK == BUQNmwkOQp){Mepkilfclp = true;}
      while(HpYWhQxCOI == HpYWhQxCOI){NYUwFdMPpx = true;}
      while(nVjFzZxwCk == nVjFzZxwCk){hFrIMIUMzm = true;}
      if(QoeqasBKaC == true){QoeqasBKaC = false;}
      if(HaDUBRDIhI == true){HaDUBRDIhI = false;}
      if(bTiPszQQmt == true){bTiPszQQmt = false;}
      if(IntUsSLgwn == true){IntUsSLgwn = false;}
      if(PmaLBNRODh == true){PmaLBNRODh = false;}
      if(VoNtIwFPyb == true){VoNtIwFPyb = false;}
      if(bjXgtSfhbi == true){bjXgtSfhbi = false;}
      if(FVMtsorXNe == true){FVMtsorXNe = false;}
      if(gBMEXTaAMw == true){gBMEXTaAMw = false;}
      if(MwhTLeOtQh == true){MwhTLeOtQh = false;}
      if(gjmUbzbTAT == true){gjmUbzbTAT = false;}
      if(DgBSuaWSIa == true){DgBSuaWSIa = false;}
      if(rfVeVInshN == true){rfVeVInshN = false;}
      if(ZyGfywNqbX == true){ZyGfywNqbX = false;}
      if(qGzrreuOYk == true){qGzrreuOYk = false;}
      if(IukpoBOIzT == true){IukpoBOIzT = false;}
      if(LilmsFaUUy == true){LilmsFaUUy = false;}
      if(Mepkilfclp == true){Mepkilfclp = false;}
      if(NYUwFdMPpx == true){NYUwFdMPpx = false;}
      if(hFrIMIUMzm == true){hFrIMIUMzm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LQMYRXKGOO
{ 
  void QVoihmOREZ()
  { 
      bool rkUqgmShLr = false;
      bool STaTozeOeR = false;
      bool CCMNbHBHJF = false;
      bool fLhgQNqbHT = false;
      bool Lileurnuht = false;
      bool spjFMoYHPY = false;
      bool lLYGMHksDa = false;
      bool HCGLFTQhRi = false;
      bool TFYPLoabTa = false;
      bool oiLhhAJfSn = false;
      bool HtqHlpiYAs = false;
      bool YppgFflJtX = false;
      bool fIZckXqYdE = false;
      bool JkOdbYNRdV = false;
      bool FCbaCysecB = false;
      bool OAkuHyUOVN = false;
      bool zKtuinaMFf = false;
      bool STfXRdgyZm = false;
      bool eMubpJzTVd = false;
      bool DywPVuHgqO = false;
      string AFDwiiPehw;
      string JxMNgxsjXS;
      string ZfnseQhiOt;
      string aKUoaySAaP;
      string tGhKVzZqMp;
      string QGEVsURJQS;
      string BfPmUzbXmh;
      string esIHYTxcXf;
      string pqWXdUFzuG;
      string gIiIONptoW;
      string WCDdLWywxZ;
      string WnlkbKJrJA;
      string scbfBVKzsK;
      string cCmBImmrMG;
      string WIBUirWxfE;
      string DykoctaXco;
      string MyDlxTAkbn;
      string WQeCdkaGwI;
      string zMToGeRyXO;
      string MPPXsXFPXP;
      if(AFDwiiPehw == WCDdLWywxZ){rkUqgmShLr = true;}
      else if(WCDdLWywxZ == AFDwiiPehw){HtqHlpiYAs = true;}
      if(JxMNgxsjXS == WnlkbKJrJA){STaTozeOeR = true;}
      else if(WnlkbKJrJA == JxMNgxsjXS){YppgFflJtX = true;}
      if(ZfnseQhiOt == scbfBVKzsK){CCMNbHBHJF = true;}
      else if(scbfBVKzsK == ZfnseQhiOt){fIZckXqYdE = true;}
      if(aKUoaySAaP == cCmBImmrMG){fLhgQNqbHT = true;}
      else if(cCmBImmrMG == aKUoaySAaP){JkOdbYNRdV = true;}
      if(tGhKVzZqMp == WIBUirWxfE){Lileurnuht = true;}
      else if(WIBUirWxfE == tGhKVzZqMp){FCbaCysecB = true;}
      if(QGEVsURJQS == DykoctaXco){spjFMoYHPY = true;}
      else if(DykoctaXco == QGEVsURJQS){OAkuHyUOVN = true;}
      if(BfPmUzbXmh == MyDlxTAkbn){lLYGMHksDa = true;}
      else if(MyDlxTAkbn == BfPmUzbXmh){zKtuinaMFf = true;}
      if(esIHYTxcXf == WQeCdkaGwI){HCGLFTQhRi = true;}
      if(pqWXdUFzuG == zMToGeRyXO){TFYPLoabTa = true;}
      if(gIiIONptoW == MPPXsXFPXP){oiLhhAJfSn = true;}
      while(WQeCdkaGwI == esIHYTxcXf){STfXRdgyZm = true;}
      while(zMToGeRyXO == zMToGeRyXO){eMubpJzTVd = true;}
      while(MPPXsXFPXP == MPPXsXFPXP){DywPVuHgqO = true;}
      if(rkUqgmShLr == true){rkUqgmShLr = false;}
      if(STaTozeOeR == true){STaTozeOeR = false;}
      if(CCMNbHBHJF == true){CCMNbHBHJF = false;}
      if(fLhgQNqbHT == true){fLhgQNqbHT = false;}
      if(Lileurnuht == true){Lileurnuht = false;}
      if(spjFMoYHPY == true){spjFMoYHPY = false;}
      if(lLYGMHksDa == true){lLYGMHksDa = false;}
      if(HCGLFTQhRi == true){HCGLFTQhRi = false;}
      if(TFYPLoabTa == true){TFYPLoabTa = false;}
      if(oiLhhAJfSn == true){oiLhhAJfSn = false;}
      if(HtqHlpiYAs == true){HtqHlpiYAs = false;}
      if(YppgFflJtX == true){YppgFflJtX = false;}
      if(fIZckXqYdE == true){fIZckXqYdE = false;}
      if(JkOdbYNRdV == true){JkOdbYNRdV = false;}
      if(FCbaCysecB == true){FCbaCysecB = false;}
      if(OAkuHyUOVN == true){OAkuHyUOVN = false;}
      if(zKtuinaMFf == true){zKtuinaMFf = false;}
      if(STfXRdgyZm == true){STfXRdgyZm = false;}
      if(eMubpJzTVd == true){eMubpJzTVd = false;}
      if(DywPVuHgqO == true){DywPVuHgqO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTNRMEYIRF
{ 
  void YTJDJdihtx()
  { 
      bool gUlhTTitqX = false;
      bool TJghYHSoSZ = false;
      bool QFugmLtfrc = false;
      bool GJRPPTKHbb = false;
      bool UYQIPOrhaY = false;
      bool nCLEobZFtI = false;
      bool ZCCNQJqRRF = false;
      bool wKMpEqnmQY = false;
      bool TMFToEyMZn = false;
      bool sFNTCRWCqF = false;
      bool WaPUbdoUzx = false;
      bool mmnUnNxiYL = false;
      bool LeqdLqwrnm = false;
      bool TkuKCrwjqK = false;
      bool PcMbBGQseo = false;
      bool UndftqilIj = false;
      bool gwgMcBqdRu = false;
      bool QMqNwhSPbF = false;
      bool aDNzRfHPQL = false;
      bool JJaGdSwAyz = false;
      string ToIYWmoeEQ;
      string IBgXVLNUoS;
      string sjlhjyhRXH;
      string LTkaxqAAEV;
      string HRXdjENqAK;
      string RGFBXiCanX;
      string EWHxEnPFae;
      string KMPSLbMHxf;
      string jqQNoFOiCN;
      string nZLgRjJZZu;
      string nHPVzFplpu;
      string WtcInMFtIy;
      string ZgCMpkAiBa;
      string SlhBqbbuNj;
      string ObsHqswDsE;
      string eORaVHECeN;
      string EHkOckMaQL;
      string kKfXjynuVx;
      string nxowwDTHfj;
      string XYPAfGqddG;
      if(ToIYWmoeEQ == nHPVzFplpu){gUlhTTitqX = true;}
      else if(nHPVzFplpu == ToIYWmoeEQ){WaPUbdoUzx = true;}
      if(IBgXVLNUoS == WtcInMFtIy){TJghYHSoSZ = true;}
      else if(WtcInMFtIy == IBgXVLNUoS){mmnUnNxiYL = true;}
      if(sjlhjyhRXH == ZgCMpkAiBa){QFugmLtfrc = true;}
      else if(ZgCMpkAiBa == sjlhjyhRXH){LeqdLqwrnm = true;}
      if(LTkaxqAAEV == SlhBqbbuNj){GJRPPTKHbb = true;}
      else if(SlhBqbbuNj == LTkaxqAAEV){TkuKCrwjqK = true;}
      if(HRXdjENqAK == ObsHqswDsE){UYQIPOrhaY = true;}
      else if(ObsHqswDsE == HRXdjENqAK){PcMbBGQseo = true;}
      if(RGFBXiCanX == eORaVHECeN){nCLEobZFtI = true;}
      else if(eORaVHECeN == RGFBXiCanX){UndftqilIj = true;}
      if(EWHxEnPFae == EHkOckMaQL){ZCCNQJqRRF = true;}
      else if(EHkOckMaQL == EWHxEnPFae){gwgMcBqdRu = true;}
      if(KMPSLbMHxf == kKfXjynuVx){wKMpEqnmQY = true;}
      if(jqQNoFOiCN == nxowwDTHfj){TMFToEyMZn = true;}
      if(nZLgRjJZZu == XYPAfGqddG){sFNTCRWCqF = true;}
      while(kKfXjynuVx == KMPSLbMHxf){QMqNwhSPbF = true;}
      while(nxowwDTHfj == nxowwDTHfj){aDNzRfHPQL = true;}
      while(XYPAfGqddG == XYPAfGqddG){JJaGdSwAyz = true;}
      if(gUlhTTitqX == true){gUlhTTitqX = false;}
      if(TJghYHSoSZ == true){TJghYHSoSZ = false;}
      if(QFugmLtfrc == true){QFugmLtfrc = false;}
      if(GJRPPTKHbb == true){GJRPPTKHbb = false;}
      if(UYQIPOrhaY == true){UYQIPOrhaY = false;}
      if(nCLEobZFtI == true){nCLEobZFtI = false;}
      if(ZCCNQJqRRF == true){ZCCNQJqRRF = false;}
      if(wKMpEqnmQY == true){wKMpEqnmQY = false;}
      if(TMFToEyMZn == true){TMFToEyMZn = false;}
      if(sFNTCRWCqF == true){sFNTCRWCqF = false;}
      if(WaPUbdoUzx == true){WaPUbdoUzx = false;}
      if(mmnUnNxiYL == true){mmnUnNxiYL = false;}
      if(LeqdLqwrnm == true){LeqdLqwrnm = false;}
      if(TkuKCrwjqK == true){TkuKCrwjqK = false;}
      if(PcMbBGQseo == true){PcMbBGQseo = false;}
      if(UndftqilIj == true){UndftqilIj = false;}
      if(gwgMcBqdRu == true){gwgMcBqdRu = false;}
      if(QMqNwhSPbF == true){QMqNwhSPbF = false;}
      if(aDNzRfHPQL == true){aDNzRfHPQL = false;}
      if(JJaGdSwAyz == true){JJaGdSwAyz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IJNJNJZLHQ
{ 
  void esGnBRqaPc()
  { 
      bool JCkCmnuynl = false;
      bool GlSRFpCwjX = false;
      bool ZjdtrmFDWT = false;
      bool EnexDjUtIo = false;
      bool WaHQgrFLbJ = false;
      bool xCbukYXqKA = false;
      bool hqaUgSHUOV = false;
      bool VHntBycMMz = false;
      bool gtaNWCLiLd = false;
      bool LcjHHeAmjO = false;
      bool kkwGmoNhtm = false;
      bool wLdLSnPMye = false;
      bool GXIkJrXfmW = false;
      bool ypcxNwxUZg = false;
      bool ndoYgAyXoS = false;
      bool OmnFINbKxu = false;
      bool QhuWnGigxW = false;
      bool qumQpbhiDJ = false;
      bool szpTHKBWoA = false;
      bool TlWdPGiSja = false;
      string oKoTLchlAX;
      string zdlJPpYxZP;
      string oLwmQMTzjN;
      string gZSeimLBMT;
      string ywbRJpBWIt;
      string tItegdNCDy;
      string IiCmqZLGZb;
      string eXkGQrjdcZ;
      string KxppSXemyF;
      string YIxNKPtoaj;
      string etwgOWXnOn;
      string tjZcmLrMTS;
      string tYIUCVZXuB;
      string ytDrtQAIaw;
      string zqYJLoiTZz;
      string XgUHoGkber;
      string wArNpzfgiW;
      string LilWSDzzJM;
      string lFxwcRYuDn;
      string eXdhAzyLTL;
      if(oKoTLchlAX == etwgOWXnOn){JCkCmnuynl = true;}
      else if(etwgOWXnOn == oKoTLchlAX){kkwGmoNhtm = true;}
      if(zdlJPpYxZP == tjZcmLrMTS){GlSRFpCwjX = true;}
      else if(tjZcmLrMTS == zdlJPpYxZP){wLdLSnPMye = true;}
      if(oLwmQMTzjN == tYIUCVZXuB){ZjdtrmFDWT = true;}
      else if(tYIUCVZXuB == oLwmQMTzjN){GXIkJrXfmW = true;}
      if(gZSeimLBMT == ytDrtQAIaw){EnexDjUtIo = true;}
      else if(ytDrtQAIaw == gZSeimLBMT){ypcxNwxUZg = true;}
      if(ywbRJpBWIt == zqYJLoiTZz){WaHQgrFLbJ = true;}
      else if(zqYJLoiTZz == ywbRJpBWIt){ndoYgAyXoS = true;}
      if(tItegdNCDy == XgUHoGkber){xCbukYXqKA = true;}
      else if(XgUHoGkber == tItegdNCDy){OmnFINbKxu = true;}
      if(IiCmqZLGZb == wArNpzfgiW){hqaUgSHUOV = true;}
      else if(wArNpzfgiW == IiCmqZLGZb){QhuWnGigxW = true;}
      if(eXkGQrjdcZ == LilWSDzzJM){VHntBycMMz = true;}
      if(KxppSXemyF == lFxwcRYuDn){gtaNWCLiLd = true;}
      if(YIxNKPtoaj == eXdhAzyLTL){LcjHHeAmjO = true;}
      while(LilWSDzzJM == eXkGQrjdcZ){qumQpbhiDJ = true;}
      while(lFxwcRYuDn == lFxwcRYuDn){szpTHKBWoA = true;}
      while(eXdhAzyLTL == eXdhAzyLTL){TlWdPGiSja = true;}
      if(JCkCmnuynl == true){JCkCmnuynl = false;}
      if(GlSRFpCwjX == true){GlSRFpCwjX = false;}
      if(ZjdtrmFDWT == true){ZjdtrmFDWT = false;}
      if(EnexDjUtIo == true){EnexDjUtIo = false;}
      if(WaHQgrFLbJ == true){WaHQgrFLbJ = false;}
      if(xCbukYXqKA == true){xCbukYXqKA = false;}
      if(hqaUgSHUOV == true){hqaUgSHUOV = false;}
      if(VHntBycMMz == true){VHntBycMMz = false;}
      if(gtaNWCLiLd == true){gtaNWCLiLd = false;}
      if(LcjHHeAmjO == true){LcjHHeAmjO = false;}
      if(kkwGmoNhtm == true){kkwGmoNhtm = false;}
      if(wLdLSnPMye == true){wLdLSnPMye = false;}
      if(GXIkJrXfmW == true){GXIkJrXfmW = false;}
      if(ypcxNwxUZg == true){ypcxNwxUZg = false;}
      if(ndoYgAyXoS == true){ndoYgAyXoS = false;}
      if(OmnFINbKxu == true){OmnFINbKxu = false;}
      if(QhuWnGigxW == true){QhuWnGigxW = false;}
      if(qumQpbhiDJ == true){qumQpbhiDJ = false;}
      if(szpTHKBWoA == true){szpTHKBWoA = false;}
      if(TlWdPGiSja == true){TlWdPGiSja = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XEQBNHCPUA
{ 
  void FPFRidgXsl()
  { 
      bool MJwjmPwufl = false;
      bool lKNJwrBlEL = false;
      bool VSSRtuiUZP = false;
      bool nRicghPMOq = false;
      bool JiyQwFoAWR = false;
      bool bSagVtpeor = false;
      bool faUPxTakbO = false;
      bool bnWMCmTBUo = false;
      bool GixHnVqCGm = false;
      bool qkXWKhNhTc = false;
      bool dDXIpmuOei = false;
      bool ZoJAkxdMbb = false;
      bool cXeoWqQABU = false;
      bool YlhqKCLnRA = false;
      bool ZbXWMCaWkN = false;
      bool DBFqAFXhly = false;
      bool WuMKJnGRoi = false;
      bool loubCAAHcT = false;
      bool PsOnQXfpqE = false;
      bool dcCScdPNMY = false;
      string EpucAVPwAC;
      string cbFXewxCHQ;
      string VCmmTIzqgT;
      string MPVAFOqXAt;
      string mxMlidePWO;
      string orqEgBDIIq;
      string VYOfpNGFRP;
      string EZBMdYpBEp;
      string cjTReTYRSD;
      string LiPJXNhfwU;
      string XZxGJPqdaI;
      string KBESNlFxAV;
      string onmNDVJroP;
      string qJEiRDmMHP;
      string ctpKsJdxul;
      string IkfZfimiDn;
      string FyoLRAxUAK;
      string yrokstxbUs;
      string qMxCGFdeCh;
      string PDJTKdFerr;
      if(EpucAVPwAC == XZxGJPqdaI){MJwjmPwufl = true;}
      else if(XZxGJPqdaI == EpucAVPwAC){dDXIpmuOei = true;}
      if(cbFXewxCHQ == KBESNlFxAV){lKNJwrBlEL = true;}
      else if(KBESNlFxAV == cbFXewxCHQ){ZoJAkxdMbb = true;}
      if(VCmmTIzqgT == onmNDVJroP){VSSRtuiUZP = true;}
      else if(onmNDVJroP == VCmmTIzqgT){cXeoWqQABU = true;}
      if(MPVAFOqXAt == qJEiRDmMHP){nRicghPMOq = true;}
      else if(qJEiRDmMHP == MPVAFOqXAt){YlhqKCLnRA = true;}
      if(mxMlidePWO == ctpKsJdxul){JiyQwFoAWR = true;}
      else if(ctpKsJdxul == mxMlidePWO){ZbXWMCaWkN = true;}
      if(orqEgBDIIq == IkfZfimiDn){bSagVtpeor = true;}
      else if(IkfZfimiDn == orqEgBDIIq){DBFqAFXhly = true;}
      if(VYOfpNGFRP == FyoLRAxUAK){faUPxTakbO = true;}
      else if(FyoLRAxUAK == VYOfpNGFRP){WuMKJnGRoi = true;}
      if(EZBMdYpBEp == yrokstxbUs){bnWMCmTBUo = true;}
      if(cjTReTYRSD == qMxCGFdeCh){GixHnVqCGm = true;}
      if(LiPJXNhfwU == PDJTKdFerr){qkXWKhNhTc = true;}
      while(yrokstxbUs == EZBMdYpBEp){loubCAAHcT = true;}
      while(qMxCGFdeCh == qMxCGFdeCh){PsOnQXfpqE = true;}
      while(PDJTKdFerr == PDJTKdFerr){dcCScdPNMY = true;}
      if(MJwjmPwufl == true){MJwjmPwufl = false;}
      if(lKNJwrBlEL == true){lKNJwrBlEL = false;}
      if(VSSRtuiUZP == true){VSSRtuiUZP = false;}
      if(nRicghPMOq == true){nRicghPMOq = false;}
      if(JiyQwFoAWR == true){JiyQwFoAWR = false;}
      if(bSagVtpeor == true){bSagVtpeor = false;}
      if(faUPxTakbO == true){faUPxTakbO = false;}
      if(bnWMCmTBUo == true){bnWMCmTBUo = false;}
      if(GixHnVqCGm == true){GixHnVqCGm = false;}
      if(qkXWKhNhTc == true){qkXWKhNhTc = false;}
      if(dDXIpmuOei == true){dDXIpmuOei = false;}
      if(ZoJAkxdMbb == true){ZoJAkxdMbb = false;}
      if(cXeoWqQABU == true){cXeoWqQABU = false;}
      if(YlhqKCLnRA == true){YlhqKCLnRA = false;}
      if(ZbXWMCaWkN == true){ZbXWMCaWkN = false;}
      if(DBFqAFXhly == true){DBFqAFXhly = false;}
      if(WuMKJnGRoi == true){WuMKJnGRoi = false;}
      if(loubCAAHcT == true){loubCAAHcT = false;}
      if(PsOnQXfpqE == true){PsOnQXfpqE = false;}
      if(dcCScdPNMY == true){dcCScdPNMY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIBIKJHXGH
{ 
  void CYJYEMRtJC()
  { 
      bool ctJUqTOwIW = false;
      bool XuArKwkdHf = false;
      bool GkOhUyUqWd = false;
      bool UjAzBpSEZU = false;
      bool MgcmoaTnGx = false;
      bool DtNbDrebAs = false;
      bool yWZdCntBpT = false;
      bool cgDmSYHbss = false;
      bool dgkZaZWXuJ = false;
      bool KqDgVpHzkB = false;
      bool fRxlTWqZJd = false;
      bool jDiGORkzDc = false;
      bool QWFfJlcVRb = false;
      bool RIqqMLizFD = false;
      bool hwORYGIxSD = false;
      bool EHuHjJMQbh = false;
      bool sUIgLbMqtC = false;
      bool ilsztUHmGC = false;
      bool cfDNXJMiHC = false;
      bool zRWXKMmgFw = false;
      string PQkfmFgIXW;
      string wDEFypFNXN;
      string IzUhwTUXdL;
      string HsHNjgUcxp;
      string hUKKezRfST;
      string jLDksPwCjT;
      string jJdLOCuqVQ;
      string VbPgfnoKDw;
      string BnFJbupWTT;
      string kSsdFXpyuc;
      string DaKByHwVEE;
      string akznRwDTjS;
      string MYWBeDhkaI;
      string xqOZracDLT;
      string zTROszSFMJ;
      string TWNbPeDIWu;
      string ZKuwGjWYuq;
      string SAIQTsGIIe;
      string jcYRnadlJN;
      string WUfQsoXVHJ;
      if(PQkfmFgIXW == DaKByHwVEE){ctJUqTOwIW = true;}
      else if(DaKByHwVEE == PQkfmFgIXW){fRxlTWqZJd = true;}
      if(wDEFypFNXN == akznRwDTjS){XuArKwkdHf = true;}
      else if(akznRwDTjS == wDEFypFNXN){jDiGORkzDc = true;}
      if(IzUhwTUXdL == MYWBeDhkaI){GkOhUyUqWd = true;}
      else if(MYWBeDhkaI == IzUhwTUXdL){QWFfJlcVRb = true;}
      if(HsHNjgUcxp == xqOZracDLT){UjAzBpSEZU = true;}
      else if(xqOZracDLT == HsHNjgUcxp){RIqqMLizFD = true;}
      if(hUKKezRfST == zTROszSFMJ){MgcmoaTnGx = true;}
      else if(zTROszSFMJ == hUKKezRfST){hwORYGIxSD = true;}
      if(jLDksPwCjT == TWNbPeDIWu){DtNbDrebAs = true;}
      else if(TWNbPeDIWu == jLDksPwCjT){EHuHjJMQbh = true;}
      if(jJdLOCuqVQ == ZKuwGjWYuq){yWZdCntBpT = true;}
      else if(ZKuwGjWYuq == jJdLOCuqVQ){sUIgLbMqtC = true;}
      if(VbPgfnoKDw == SAIQTsGIIe){cgDmSYHbss = true;}
      if(BnFJbupWTT == jcYRnadlJN){dgkZaZWXuJ = true;}
      if(kSsdFXpyuc == WUfQsoXVHJ){KqDgVpHzkB = true;}
      while(SAIQTsGIIe == VbPgfnoKDw){ilsztUHmGC = true;}
      while(jcYRnadlJN == jcYRnadlJN){cfDNXJMiHC = true;}
      while(WUfQsoXVHJ == WUfQsoXVHJ){zRWXKMmgFw = true;}
      if(ctJUqTOwIW == true){ctJUqTOwIW = false;}
      if(XuArKwkdHf == true){XuArKwkdHf = false;}
      if(GkOhUyUqWd == true){GkOhUyUqWd = false;}
      if(UjAzBpSEZU == true){UjAzBpSEZU = false;}
      if(MgcmoaTnGx == true){MgcmoaTnGx = false;}
      if(DtNbDrebAs == true){DtNbDrebAs = false;}
      if(yWZdCntBpT == true){yWZdCntBpT = false;}
      if(cgDmSYHbss == true){cgDmSYHbss = false;}
      if(dgkZaZWXuJ == true){dgkZaZWXuJ = false;}
      if(KqDgVpHzkB == true){KqDgVpHzkB = false;}
      if(fRxlTWqZJd == true){fRxlTWqZJd = false;}
      if(jDiGORkzDc == true){jDiGORkzDc = false;}
      if(QWFfJlcVRb == true){QWFfJlcVRb = false;}
      if(RIqqMLizFD == true){RIqqMLizFD = false;}
      if(hwORYGIxSD == true){hwORYGIxSD = false;}
      if(EHuHjJMQbh == true){EHuHjJMQbh = false;}
      if(sUIgLbMqtC == true){sUIgLbMqtC = false;}
      if(ilsztUHmGC == true){ilsztUHmGC = false;}
      if(cfDNXJMiHC == true){cfDNXJMiHC = false;}
      if(zRWXKMmgFw == true){zRWXKMmgFw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNWDKIWTDZ
{ 
  void wOAsslfcWx()
  { 
      bool dNWikZhepW = false;
      bool PJYdegYlWR = false;
      bool bhtqiPFwYm = false;
      bool olFaTcOrsz = false;
      bool bEarNarAlu = false;
      bool rlQswuSeAU = false;
      bool TkFDhcDxKB = false;
      bool RfrWoWHBdH = false;
      bool XFKctCVLeX = false;
      bool JirYfqyWJj = false;
      bool WtojcMssDY = false;
      bool nRBrxNZbJf = false;
      bool GqSlqimTqy = false;
      bool YjrtkcQZAh = false;
      bool IcHFjrhAaR = false;
      bool QVNdcfbCrt = false;
      bool YYCEADYHGT = false;
      bool xzbaWdiMCz = false;
      bool AmsYhCVNQF = false;
      bool BNhFIjZDFf = false;
      string aDiCzMZbox;
      string KMUQAauBpi;
      string YJMkwjtbCz;
      string fCjAZhektF;
      string yVShwcxyTe;
      string GkyRhQqyGP;
      string RxYpRHcUqR;
      string uJHkkCqdnS;
      string mwHXsuERRI;
      string qgednAxcQn;
      string AcGCjxcNgf;
      string ZMJmcVpBwV;
      string DKCiaNdcwj;
      string FOMASJoFmu;
      string RpjlidWrBR;
      string KufukoZXaV;
      string SAQxaKAJUS;
      string gjNBENZQzx;
      string qlbeZJiRPc;
      string jQdQbRYmKX;
      if(aDiCzMZbox == AcGCjxcNgf){dNWikZhepW = true;}
      else if(AcGCjxcNgf == aDiCzMZbox){WtojcMssDY = true;}
      if(KMUQAauBpi == ZMJmcVpBwV){PJYdegYlWR = true;}
      else if(ZMJmcVpBwV == KMUQAauBpi){nRBrxNZbJf = true;}
      if(YJMkwjtbCz == DKCiaNdcwj){bhtqiPFwYm = true;}
      else if(DKCiaNdcwj == YJMkwjtbCz){GqSlqimTqy = true;}
      if(fCjAZhektF == FOMASJoFmu){olFaTcOrsz = true;}
      else if(FOMASJoFmu == fCjAZhektF){YjrtkcQZAh = true;}
      if(yVShwcxyTe == RpjlidWrBR){bEarNarAlu = true;}
      else if(RpjlidWrBR == yVShwcxyTe){IcHFjrhAaR = true;}
      if(GkyRhQqyGP == KufukoZXaV){rlQswuSeAU = true;}
      else if(KufukoZXaV == GkyRhQqyGP){QVNdcfbCrt = true;}
      if(RxYpRHcUqR == SAQxaKAJUS){TkFDhcDxKB = true;}
      else if(SAQxaKAJUS == RxYpRHcUqR){YYCEADYHGT = true;}
      if(uJHkkCqdnS == gjNBENZQzx){RfrWoWHBdH = true;}
      if(mwHXsuERRI == qlbeZJiRPc){XFKctCVLeX = true;}
      if(qgednAxcQn == jQdQbRYmKX){JirYfqyWJj = true;}
      while(gjNBENZQzx == uJHkkCqdnS){xzbaWdiMCz = true;}
      while(qlbeZJiRPc == qlbeZJiRPc){AmsYhCVNQF = true;}
      while(jQdQbRYmKX == jQdQbRYmKX){BNhFIjZDFf = true;}
      if(dNWikZhepW == true){dNWikZhepW = false;}
      if(PJYdegYlWR == true){PJYdegYlWR = false;}
      if(bhtqiPFwYm == true){bhtqiPFwYm = false;}
      if(olFaTcOrsz == true){olFaTcOrsz = false;}
      if(bEarNarAlu == true){bEarNarAlu = false;}
      if(rlQswuSeAU == true){rlQswuSeAU = false;}
      if(TkFDhcDxKB == true){TkFDhcDxKB = false;}
      if(RfrWoWHBdH == true){RfrWoWHBdH = false;}
      if(XFKctCVLeX == true){XFKctCVLeX = false;}
      if(JirYfqyWJj == true){JirYfqyWJj = false;}
      if(WtojcMssDY == true){WtojcMssDY = false;}
      if(nRBrxNZbJf == true){nRBrxNZbJf = false;}
      if(GqSlqimTqy == true){GqSlqimTqy = false;}
      if(YjrtkcQZAh == true){YjrtkcQZAh = false;}
      if(IcHFjrhAaR == true){IcHFjrhAaR = false;}
      if(QVNdcfbCrt == true){QVNdcfbCrt = false;}
      if(YYCEADYHGT == true){YYCEADYHGT = false;}
      if(xzbaWdiMCz == true){xzbaWdiMCz = false;}
      if(AmsYhCVNQF == true){AmsYhCVNQF = false;}
      if(BNhFIjZDFf == true){BNhFIjZDFf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZUOBRFQQP
{ 
  void phiIwRhAEd()
  { 
      bool MqbajPYNWp = false;
      bool cAHTpBuzAV = false;
      bool WeGclNfZcQ = false;
      bool gGqLhPnPdE = false;
      bool cfSnkUGHMb = false;
      bool AmneCgjzoV = false;
      bool iykFIVJwka = false;
      bool NeVwrpMSqR = false;
      bool HYNAQtRLIB = false;
      bool enaHUetNfO = false;
      bool KKVlOVQrlL = false;
      bool URIWNKkknO = false;
      bool ExmjuYDNaN = false;
      bool wymbGxCalu = false;
      bool dYZxgNfDsK = false;
      bool sJYRKNWlpo = false;
      bool RCRYPVegPQ = false;
      bool HJysjeXoCh = false;
      bool szTQTlYVQs = false;
      bool ZQjwdaHBhL = false;
      string WOqfasGHjX;
      string wkdgXdgRST;
      string bHTAgnmZxj;
      string iqEOkVryoA;
      string DqWRiMVOsQ;
      string koFeNPuqzl;
      string GfKAnFfPuC;
      string kicSPkjBRT;
      string SYgfytlYAU;
      string ZByCsWfVcc;
      string fGSpfCMlOc;
      string esYeThydCt;
      string TGOabijZYs;
      string EOYnnMFpAu;
      string hzKXpgbTiL;
      string XCTiJYqrOx;
      string RlMVXQUkqH;
      string bIdGMTwqjt;
      string GQqNUCtodO;
      string UNbDduloAY;
      if(WOqfasGHjX == fGSpfCMlOc){MqbajPYNWp = true;}
      else if(fGSpfCMlOc == WOqfasGHjX){KKVlOVQrlL = true;}
      if(wkdgXdgRST == esYeThydCt){cAHTpBuzAV = true;}
      else if(esYeThydCt == wkdgXdgRST){URIWNKkknO = true;}
      if(bHTAgnmZxj == TGOabijZYs){WeGclNfZcQ = true;}
      else if(TGOabijZYs == bHTAgnmZxj){ExmjuYDNaN = true;}
      if(iqEOkVryoA == EOYnnMFpAu){gGqLhPnPdE = true;}
      else if(EOYnnMFpAu == iqEOkVryoA){wymbGxCalu = true;}
      if(DqWRiMVOsQ == hzKXpgbTiL){cfSnkUGHMb = true;}
      else if(hzKXpgbTiL == DqWRiMVOsQ){dYZxgNfDsK = true;}
      if(koFeNPuqzl == XCTiJYqrOx){AmneCgjzoV = true;}
      else if(XCTiJYqrOx == koFeNPuqzl){sJYRKNWlpo = true;}
      if(GfKAnFfPuC == RlMVXQUkqH){iykFIVJwka = true;}
      else if(RlMVXQUkqH == GfKAnFfPuC){RCRYPVegPQ = true;}
      if(kicSPkjBRT == bIdGMTwqjt){NeVwrpMSqR = true;}
      if(SYgfytlYAU == GQqNUCtodO){HYNAQtRLIB = true;}
      if(ZByCsWfVcc == UNbDduloAY){enaHUetNfO = true;}
      while(bIdGMTwqjt == kicSPkjBRT){HJysjeXoCh = true;}
      while(GQqNUCtodO == GQqNUCtodO){szTQTlYVQs = true;}
      while(UNbDduloAY == UNbDduloAY){ZQjwdaHBhL = true;}
      if(MqbajPYNWp == true){MqbajPYNWp = false;}
      if(cAHTpBuzAV == true){cAHTpBuzAV = false;}
      if(WeGclNfZcQ == true){WeGclNfZcQ = false;}
      if(gGqLhPnPdE == true){gGqLhPnPdE = false;}
      if(cfSnkUGHMb == true){cfSnkUGHMb = false;}
      if(AmneCgjzoV == true){AmneCgjzoV = false;}
      if(iykFIVJwka == true){iykFIVJwka = false;}
      if(NeVwrpMSqR == true){NeVwrpMSqR = false;}
      if(HYNAQtRLIB == true){HYNAQtRLIB = false;}
      if(enaHUetNfO == true){enaHUetNfO = false;}
      if(KKVlOVQrlL == true){KKVlOVQrlL = false;}
      if(URIWNKkknO == true){URIWNKkknO = false;}
      if(ExmjuYDNaN == true){ExmjuYDNaN = false;}
      if(wymbGxCalu == true){wymbGxCalu = false;}
      if(dYZxgNfDsK == true){dYZxgNfDsK = false;}
      if(sJYRKNWlpo == true){sJYRKNWlpo = false;}
      if(RCRYPVegPQ == true){RCRYPVegPQ = false;}
      if(HJysjeXoCh == true){HJysjeXoCh = false;}
      if(szTQTlYVQs == true){szTQTlYVQs = false;}
      if(ZQjwdaHBhL == true){ZQjwdaHBhL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQNWJOJQRB
{ 
  void uBFqrEUOhK()
  { 
      bool MtjRUSWCrR = false;
      bool yBaOkfgfrC = false;
      bool pPQDyFxTnB = false;
      bool dnPNLfMzqq = false;
      bool qUiWaAUpeM = false;
      bool dlQNjxcgSP = false;
      bool UCNqnJkMDF = false;
      bool ShnBLUgtby = false;
      bool jHobXqXBcO = false;
      bool DefbWnHqhR = false;
      bool OIlZswxPBP = false;
      bool PhEUfMNkSw = false;
      bool lijoBmBMeW = false;
      bool NoLKiaVOib = false;
      bool tIzNyUaLwJ = false;
      bool aVYlfeXwYF = false;
      bool tkjdCZWtkE = false;
      bool qyCqCcjVqg = false;
      bool MpPVwqQYeE = false;
      bool DYpdgIXULX = false;
      string AeMZaslOha;
      string QjiIPVSCKS;
      string smyhuLegkW;
      string MZcAWJmsQu;
      string VAupKPfcWU;
      string NTofeMfeeP;
      string NFdKOqHilG;
      string iZkPxrrIWe;
      string fBJPJrjwUJ;
      string cIOBgQWkaT;
      string IwqQlniZim;
      string UXIAiLuOBV;
      string GLOccZLjhf;
      string VGgCWiKrcU;
      string JKMhnEzNRV;
      string VIiFNwhOmL;
      string cyrDQNqFcA;
      string BCkgMwygnY;
      string axRLKNXanZ;
      string BwEQrKRJQa;
      if(AeMZaslOha == IwqQlniZim){MtjRUSWCrR = true;}
      else if(IwqQlniZim == AeMZaslOha){OIlZswxPBP = true;}
      if(QjiIPVSCKS == UXIAiLuOBV){yBaOkfgfrC = true;}
      else if(UXIAiLuOBV == QjiIPVSCKS){PhEUfMNkSw = true;}
      if(smyhuLegkW == GLOccZLjhf){pPQDyFxTnB = true;}
      else if(GLOccZLjhf == smyhuLegkW){lijoBmBMeW = true;}
      if(MZcAWJmsQu == VGgCWiKrcU){dnPNLfMzqq = true;}
      else if(VGgCWiKrcU == MZcAWJmsQu){NoLKiaVOib = true;}
      if(VAupKPfcWU == JKMhnEzNRV){qUiWaAUpeM = true;}
      else if(JKMhnEzNRV == VAupKPfcWU){tIzNyUaLwJ = true;}
      if(NTofeMfeeP == VIiFNwhOmL){dlQNjxcgSP = true;}
      else if(VIiFNwhOmL == NTofeMfeeP){aVYlfeXwYF = true;}
      if(NFdKOqHilG == cyrDQNqFcA){UCNqnJkMDF = true;}
      else if(cyrDQNqFcA == NFdKOqHilG){tkjdCZWtkE = true;}
      if(iZkPxrrIWe == BCkgMwygnY){ShnBLUgtby = true;}
      if(fBJPJrjwUJ == axRLKNXanZ){jHobXqXBcO = true;}
      if(cIOBgQWkaT == BwEQrKRJQa){DefbWnHqhR = true;}
      while(BCkgMwygnY == iZkPxrrIWe){qyCqCcjVqg = true;}
      while(axRLKNXanZ == axRLKNXanZ){MpPVwqQYeE = true;}
      while(BwEQrKRJQa == BwEQrKRJQa){DYpdgIXULX = true;}
      if(MtjRUSWCrR == true){MtjRUSWCrR = false;}
      if(yBaOkfgfrC == true){yBaOkfgfrC = false;}
      if(pPQDyFxTnB == true){pPQDyFxTnB = false;}
      if(dnPNLfMzqq == true){dnPNLfMzqq = false;}
      if(qUiWaAUpeM == true){qUiWaAUpeM = false;}
      if(dlQNjxcgSP == true){dlQNjxcgSP = false;}
      if(UCNqnJkMDF == true){UCNqnJkMDF = false;}
      if(ShnBLUgtby == true){ShnBLUgtby = false;}
      if(jHobXqXBcO == true){jHobXqXBcO = false;}
      if(DefbWnHqhR == true){DefbWnHqhR = false;}
      if(OIlZswxPBP == true){OIlZswxPBP = false;}
      if(PhEUfMNkSw == true){PhEUfMNkSw = false;}
      if(lijoBmBMeW == true){lijoBmBMeW = false;}
      if(NoLKiaVOib == true){NoLKiaVOib = false;}
      if(tIzNyUaLwJ == true){tIzNyUaLwJ = false;}
      if(aVYlfeXwYF == true){aVYlfeXwYF = false;}
      if(tkjdCZWtkE == true){tkjdCZWtkE = false;}
      if(qyCqCcjVqg == true){qyCqCcjVqg = false;}
      if(MpPVwqQYeE == true){MpPVwqQYeE = false;}
      if(DYpdgIXULX == true){DYpdgIXULX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZPAPMMJAQ
{ 
  void IlNdoGEjMt()
  { 
      bool iYTDezCQjd = false;
      bool wZSFfBEKKS = false;
      bool RauHmoiNsC = false;
      bool XeEDeZzILf = false;
      bool uGOoaqSUZM = false;
      bool nJdOPIcLQp = false;
      bool QnWgGQUOZF = false;
      bool CwzdXKLGgw = false;
      bool VOngONBonW = false;
      bool xmrVPGihiJ = false;
      bool VDtTKrKzqE = false;
      bool wWeTTCApSr = false;
      bool PfaDIOEdOR = false;
      bool adXWaRTTVW = false;
      bool DByjZaHXBN = false;
      bool FsPptpcqLu = false;
      bool mgjYcSyIsB = false;
      bool hfTwoNgqch = false;
      bool GgbALhOgcj = false;
      bool ocIaiWQZGH = false;
      string iciyGtyNzt;
      string dDmXTGQIKy;
      string gkHBexcLDn;
      string qqqQGiZjyo;
      string ykZpYbUcaz;
      string SuUfgxVgTJ;
      string RmJLDlLWQj;
      string fgJUzuLRcC;
      string bAjEUwWLjJ;
      string NsPoXKaOll;
      string PyLpSlkzfk;
      string lEERgQCFpG;
      string PzlHWmRTxn;
      string Twepmcoski;
      string KWfzWInyHG;
      string IVYfWPMDTf;
      string URBqQoZOdD;
      string aITHwrTmkN;
      string zSMqfxXySW;
      string QlZFNsUohg;
      if(iciyGtyNzt == PyLpSlkzfk){iYTDezCQjd = true;}
      else if(PyLpSlkzfk == iciyGtyNzt){VDtTKrKzqE = true;}
      if(dDmXTGQIKy == lEERgQCFpG){wZSFfBEKKS = true;}
      else if(lEERgQCFpG == dDmXTGQIKy){wWeTTCApSr = true;}
      if(gkHBexcLDn == PzlHWmRTxn){RauHmoiNsC = true;}
      else if(PzlHWmRTxn == gkHBexcLDn){PfaDIOEdOR = true;}
      if(qqqQGiZjyo == Twepmcoski){XeEDeZzILf = true;}
      else if(Twepmcoski == qqqQGiZjyo){adXWaRTTVW = true;}
      if(ykZpYbUcaz == KWfzWInyHG){uGOoaqSUZM = true;}
      else if(KWfzWInyHG == ykZpYbUcaz){DByjZaHXBN = true;}
      if(SuUfgxVgTJ == IVYfWPMDTf){nJdOPIcLQp = true;}
      else if(IVYfWPMDTf == SuUfgxVgTJ){FsPptpcqLu = true;}
      if(RmJLDlLWQj == URBqQoZOdD){QnWgGQUOZF = true;}
      else if(URBqQoZOdD == RmJLDlLWQj){mgjYcSyIsB = true;}
      if(fgJUzuLRcC == aITHwrTmkN){CwzdXKLGgw = true;}
      if(bAjEUwWLjJ == zSMqfxXySW){VOngONBonW = true;}
      if(NsPoXKaOll == QlZFNsUohg){xmrVPGihiJ = true;}
      while(aITHwrTmkN == fgJUzuLRcC){hfTwoNgqch = true;}
      while(zSMqfxXySW == zSMqfxXySW){GgbALhOgcj = true;}
      while(QlZFNsUohg == QlZFNsUohg){ocIaiWQZGH = true;}
      if(iYTDezCQjd == true){iYTDezCQjd = false;}
      if(wZSFfBEKKS == true){wZSFfBEKKS = false;}
      if(RauHmoiNsC == true){RauHmoiNsC = false;}
      if(XeEDeZzILf == true){XeEDeZzILf = false;}
      if(uGOoaqSUZM == true){uGOoaqSUZM = false;}
      if(nJdOPIcLQp == true){nJdOPIcLQp = false;}
      if(QnWgGQUOZF == true){QnWgGQUOZF = false;}
      if(CwzdXKLGgw == true){CwzdXKLGgw = false;}
      if(VOngONBonW == true){VOngONBonW = false;}
      if(xmrVPGihiJ == true){xmrVPGihiJ = false;}
      if(VDtTKrKzqE == true){VDtTKrKzqE = false;}
      if(wWeTTCApSr == true){wWeTTCApSr = false;}
      if(PfaDIOEdOR == true){PfaDIOEdOR = false;}
      if(adXWaRTTVW == true){adXWaRTTVW = false;}
      if(DByjZaHXBN == true){DByjZaHXBN = false;}
      if(FsPptpcqLu == true){FsPptpcqLu = false;}
      if(mgjYcSyIsB == true){mgjYcSyIsB = false;}
      if(hfTwoNgqch == true){hfTwoNgqch = false;}
      if(GgbALhOgcj == true){GgbALhOgcj = false;}
      if(ocIaiWQZGH == true){ocIaiWQZGH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXWCFIVUVD
{ 
  void MYgXZouCRV()
  { 
      bool qOtoOhGkOb = false;
      bool IjjiLIxuFb = false;
      bool uxiPJsYAAd = false;
      bool ClOUjnweYZ = false;
      bool WJjBHzNpQg = false;
      bool LqSFYtfeeU = false;
      bool IFjjZWVOzX = false;
      bool LRWfFlNhHK = false;
      bool fijSSLSIwp = false;
      bool IQzDRQZzbj = false;
      bool cypsUsTmzl = false;
      bool fyWUoZVQRN = false;
      bool EMRJPuRSOn = false;
      bool MOFXggrqyY = false;
      bool qeJKJJteOr = false;
      bool uIgNfPggdZ = false;
      bool bAYKZRrzmI = false;
      bool geSrWYDHAF = false;
      bool AlEWsDgrrR = false;
      bool AKMXxpGykq = false;
      string WpjcWGcEaW;
      string wgXmnWXgsN;
      string fdhHIgtiuk;
      string OmtlPpKMif;
      string JOyVkFBxXH;
      string cSoFhrHcUp;
      string LtJoIJmlXx;
      string MKxMDQfMWD;
      string fxKmHuyoDW;
      string hgrsTPFJNb;
      string SPZZuRVbBQ;
      string MuGQKOiVgM;
      string KyiAOeSDsn;
      string LWztkQWjrp;
      string ZVmlKmaaiF;
      string fibBQTgZKP;
      string zRiNEpuLfs;
      string qycqloKwob;
      string DqUmHctycQ;
      string jxZcpImYgT;
      if(WpjcWGcEaW == SPZZuRVbBQ){qOtoOhGkOb = true;}
      else if(SPZZuRVbBQ == WpjcWGcEaW){cypsUsTmzl = true;}
      if(wgXmnWXgsN == MuGQKOiVgM){IjjiLIxuFb = true;}
      else if(MuGQKOiVgM == wgXmnWXgsN){fyWUoZVQRN = true;}
      if(fdhHIgtiuk == KyiAOeSDsn){uxiPJsYAAd = true;}
      else if(KyiAOeSDsn == fdhHIgtiuk){EMRJPuRSOn = true;}
      if(OmtlPpKMif == LWztkQWjrp){ClOUjnweYZ = true;}
      else if(LWztkQWjrp == OmtlPpKMif){MOFXggrqyY = true;}
      if(JOyVkFBxXH == ZVmlKmaaiF){WJjBHzNpQg = true;}
      else if(ZVmlKmaaiF == JOyVkFBxXH){qeJKJJteOr = true;}
      if(cSoFhrHcUp == fibBQTgZKP){LqSFYtfeeU = true;}
      else if(fibBQTgZKP == cSoFhrHcUp){uIgNfPggdZ = true;}
      if(LtJoIJmlXx == zRiNEpuLfs){IFjjZWVOzX = true;}
      else if(zRiNEpuLfs == LtJoIJmlXx){bAYKZRrzmI = true;}
      if(MKxMDQfMWD == qycqloKwob){LRWfFlNhHK = true;}
      if(fxKmHuyoDW == DqUmHctycQ){fijSSLSIwp = true;}
      if(hgrsTPFJNb == jxZcpImYgT){IQzDRQZzbj = true;}
      while(qycqloKwob == MKxMDQfMWD){geSrWYDHAF = true;}
      while(DqUmHctycQ == DqUmHctycQ){AlEWsDgrrR = true;}
      while(jxZcpImYgT == jxZcpImYgT){AKMXxpGykq = true;}
      if(qOtoOhGkOb == true){qOtoOhGkOb = false;}
      if(IjjiLIxuFb == true){IjjiLIxuFb = false;}
      if(uxiPJsYAAd == true){uxiPJsYAAd = false;}
      if(ClOUjnweYZ == true){ClOUjnweYZ = false;}
      if(WJjBHzNpQg == true){WJjBHzNpQg = false;}
      if(LqSFYtfeeU == true){LqSFYtfeeU = false;}
      if(IFjjZWVOzX == true){IFjjZWVOzX = false;}
      if(LRWfFlNhHK == true){LRWfFlNhHK = false;}
      if(fijSSLSIwp == true){fijSSLSIwp = false;}
      if(IQzDRQZzbj == true){IQzDRQZzbj = false;}
      if(cypsUsTmzl == true){cypsUsTmzl = false;}
      if(fyWUoZVQRN == true){fyWUoZVQRN = false;}
      if(EMRJPuRSOn == true){EMRJPuRSOn = false;}
      if(MOFXggrqyY == true){MOFXggrqyY = false;}
      if(qeJKJJteOr == true){qeJKJJteOr = false;}
      if(uIgNfPggdZ == true){uIgNfPggdZ = false;}
      if(bAYKZRrzmI == true){bAYKZRrzmI = false;}
      if(geSrWYDHAF == true){geSrWYDHAF = false;}
      if(AlEWsDgrrR == true){AlEWsDgrrR = false;}
      if(AKMXxpGykq == true){AKMXxpGykq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQRYMRZSEE
{ 
  void NHGjmERFwt()
  { 
      bool sVgtMXFcQo = false;
      bool nwUoEXSGJy = false;
      bool yZJjtwHVmF = false;
      bool rbXgVkPRdl = false;
      bool NXnGcWQnas = false;
      bool jqKLRTLwAP = false;
      bool QjoLwLXmST = false;
      bool HAbXkakDHW = false;
      bool fStsVBRMPC = false;
      bool YSROUcicJQ = false;
      bool zcUHliOlaq = false;
      bool iHocjxpwot = false;
      bool tLWQtniNCI = false;
      bool rHtpXCxlHm = false;
      bool mflYSQdneX = false;
      bool lmnPWmGENx = false;
      bool zAjSzbNyEg = false;
      bool zEnCHOZyyc = false;
      bool KuidVFTdTk = false;
      bool wsYJmluTZq = false;
      string BywbGssBlC;
      string wZSxRSbKOX;
      string GMoZCHZwVG;
      string aeNnlrdKTy;
      string afErhgTpTj;
      string SqAkToIWYz;
      string TxefaQMeKY;
      string oRpQxaHxqV;
      string miclnjebUx;
      string jGkUedAYRQ;
      string UofttBBinr;
      string gLeCLjTsqq;
      string ljKNoifVkT;
      string ahfZByCiqm;
      string hunbPYaiIt;
      string JHgZejeRFL;
      string UfyTRzeFBN;
      string gkBEIpwhxP;
      string HxMqKSAFuQ;
      string TkdfRCxTJQ;
      if(BywbGssBlC == UofttBBinr){sVgtMXFcQo = true;}
      else if(UofttBBinr == BywbGssBlC){zcUHliOlaq = true;}
      if(wZSxRSbKOX == gLeCLjTsqq){nwUoEXSGJy = true;}
      else if(gLeCLjTsqq == wZSxRSbKOX){iHocjxpwot = true;}
      if(GMoZCHZwVG == ljKNoifVkT){yZJjtwHVmF = true;}
      else if(ljKNoifVkT == GMoZCHZwVG){tLWQtniNCI = true;}
      if(aeNnlrdKTy == ahfZByCiqm){rbXgVkPRdl = true;}
      else if(ahfZByCiqm == aeNnlrdKTy){rHtpXCxlHm = true;}
      if(afErhgTpTj == hunbPYaiIt){NXnGcWQnas = true;}
      else if(hunbPYaiIt == afErhgTpTj){mflYSQdneX = true;}
      if(SqAkToIWYz == JHgZejeRFL){jqKLRTLwAP = true;}
      else if(JHgZejeRFL == SqAkToIWYz){lmnPWmGENx = true;}
      if(TxefaQMeKY == UfyTRzeFBN){QjoLwLXmST = true;}
      else if(UfyTRzeFBN == TxefaQMeKY){zAjSzbNyEg = true;}
      if(oRpQxaHxqV == gkBEIpwhxP){HAbXkakDHW = true;}
      if(miclnjebUx == HxMqKSAFuQ){fStsVBRMPC = true;}
      if(jGkUedAYRQ == TkdfRCxTJQ){YSROUcicJQ = true;}
      while(gkBEIpwhxP == oRpQxaHxqV){zEnCHOZyyc = true;}
      while(HxMqKSAFuQ == HxMqKSAFuQ){KuidVFTdTk = true;}
      while(TkdfRCxTJQ == TkdfRCxTJQ){wsYJmluTZq = true;}
      if(sVgtMXFcQo == true){sVgtMXFcQo = false;}
      if(nwUoEXSGJy == true){nwUoEXSGJy = false;}
      if(yZJjtwHVmF == true){yZJjtwHVmF = false;}
      if(rbXgVkPRdl == true){rbXgVkPRdl = false;}
      if(NXnGcWQnas == true){NXnGcWQnas = false;}
      if(jqKLRTLwAP == true){jqKLRTLwAP = false;}
      if(QjoLwLXmST == true){QjoLwLXmST = false;}
      if(HAbXkakDHW == true){HAbXkakDHW = false;}
      if(fStsVBRMPC == true){fStsVBRMPC = false;}
      if(YSROUcicJQ == true){YSROUcicJQ = false;}
      if(zcUHliOlaq == true){zcUHliOlaq = false;}
      if(iHocjxpwot == true){iHocjxpwot = false;}
      if(tLWQtniNCI == true){tLWQtniNCI = false;}
      if(rHtpXCxlHm == true){rHtpXCxlHm = false;}
      if(mflYSQdneX == true){mflYSQdneX = false;}
      if(lmnPWmGENx == true){lmnPWmGENx = false;}
      if(zAjSzbNyEg == true){zAjSzbNyEg = false;}
      if(zEnCHOZyyc == true){zEnCHOZyyc = false;}
      if(KuidVFTdTk == true){KuidVFTdTk = false;}
      if(wsYJmluTZq == true){wsYJmluTZq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZTQDQEDQN
{ 
  void CFKsonEqzd()
  { 
      bool EKIjjGnQKb = false;
      bool WqnFVCrqsn = false;
      bool DPFbnHjQnn = false;
      bool VBhqUwjkkP = false;
      bool imWnXiKVcI = false;
      bool fcFPmoEfwc = false;
      bool VWbWFUJxjY = false;
      bool RGFdFPrRDE = false;
      bool wOnfIswSDf = false;
      bool rDoIsLLAhD = false;
      bool ZMkDpYWbJW = false;
      bool wmcqfHhuOM = false;
      bool YptEgORxks = false;
      bool EqiAejckoi = false;
      bool VUJgiEaybk = false;
      bool dPlVeiSgVb = false;
      bool HZqPSEEbLu = false;
      bool exGepDgNVc = false;
      bool mSUzPnFMUu = false;
      bool RwOMbwdsNd = false;
      string SnCTZcmVbC;
      string fhTyQfMGtu;
      string EyLfYVdFjs;
      string kGzNshGQVQ;
      string ThGkMUlHpp;
      string QSCfKTcWtD;
      string yhliQZhFFh;
      string YukdaWrZTE;
      string jWOtbSESDZ;
      string FjVRRlwXUl;
      string lfBHRUgXEm;
      string aCDpSaSqHx;
      string UOCfcnZTLo;
      string aTEgSEUGbG;
      string kfOPyCgfyp;
      string SEQWQWdVec;
      string uNMPLHxVXO;
      string GLPAMoAlhZ;
      string HsUVVWDhPu;
      string aybyLXTyDp;
      if(SnCTZcmVbC == lfBHRUgXEm){EKIjjGnQKb = true;}
      else if(lfBHRUgXEm == SnCTZcmVbC){ZMkDpYWbJW = true;}
      if(fhTyQfMGtu == aCDpSaSqHx){WqnFVCrqsn = true;}
      else if(aCDpSaSqHx == fhTyQfMGtu){wmcqfHhuOM = true;}
      if(EyLfYVdFjs == UOCfcnZTLo){DPFbnHjQnn = true;}
      else if(UOCfcnZTLo == EyLfYVdFjs){YptEgORxks = true;}
      if(kGzNshGQVQ == aTEgSEUGbG){VBhqUwjkkP = true;}
      else if(aTEgSEUGbG == kGzNshGQVQ){EqiAejckoi = true;}
      if(ThGkMUlHpp == kfOPyCgfyp){imWnXiKVcI = true;}
      else if(kfOPyCgfyp == ThGkMUlHpp){VUJgiEaybk = true;}
      if(QSCfKTcWtD == SEQWQWdVec){fcFPmoEfwc = true;}
      else if(SEQWQWdVec == QSCfKTcWtD){dPlVeiSgVb = true;}
      if(yhliQZhFFh == uNMPLHxVXO){VWbWFUJxjY = true;}
      else if(uNMPLHxVXO == yhliQZhFFh){HZqPSEEbLu = true;}
      if(YukdaWrZTE == GLPAMoAlhZ){RGFdFPrRDE = true;}
      if(jWOtbSESDZ == HsUVVWDhPu){wOnfIswSDf = true;}
      if(FjVRRlwXUl == aybyLXTyDp){rDoIsLLAhD = true;}
      while(GLPAMoAlhZ == YukdaWrZTE){exGepDgNVc = true;}
      while(HsUVVWDhPu == HsUVVWDhPu){mSUzPnFMUu = true;}
      while(aybyLXTyDp == aybyLXTyDp){RwOMbwdsNd = true;}
      if(EKIjjGnQKb == true){EKIjjGnQKb = false;}
      if(WqnFVCrqsn == true){WqnFVCrqsn = false;}
      if(DPFbnHjQnn == true){DPFbnHjQnn = false;}
      if(VBhqUwjkkP == true){VBhqUwjkkP = false;}
      if(imWnXiKVcI == true){imWnXiKVcI = false;}
      if(fcFPmoEfwc == true){fcFPmoEfwc = false;}
      if(VWbWFUJxjY == true){VWbWFUJxjY = false;}
      if(RGFdFPrRDE == true){RGFdFPrRDE = false;}
      if(wOnfIswSDf == true){wOnfIswSDf = false;}
      if(rDoIsLLAhD == true){rDoIsLLAhD = false;}
      if(ZMkDpYWbJW == true){ZMkDpYWbJW = false;}
      if(wmcqfHhuOM == true){wmcqfHhuOM = false;}
      if(YptEgORxks == true){YptEgORxks = false;}
      if(EqiAejckoi == true){EqiAejckoi = false;}
      if(VUJgiEaybk == true){VUJgiEaybk = false;}
      if(dPlVeiSgVb == true){dPlVeiSgVb = false;}
      if(HZqPSEEbLu == true){HZqPSEEbLu = false;}
      if(exGepDgNVc == true){exGepDgNVc = false;}
      if(mSUzPnFMUu == true){mSUzPnFMUu = false;}
      if(RwOMbwdsNd == true){RwOMbwdsNd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUAQUYNJMO
{ 
  void rUsTxRebUz()
  { 
      bool QPRaPaLHIu = false;
      bool FZtzEiHZhs = false;
      bool ZBseNkLyEh = false;
      bool ciMBTgTytc = false;
      bool lIFUgbSoFm = false;
      bool RoyjXPWmNe = false;
      bool OMDaSWNreW = false;
      bool PJfFHRuXxk = false;
      bool RVsRQnkbdE = false;
      bool KfjPNZFeCJ = false;
      bool OaJhXHIrcF = false;
      bool TyobMsTlJd = false;
      bool lkOaMiYPrg = false;
      bool MQVnVqMKsI = false;
      bool erzXkLqHCU = false;
      bool GSUXWdLhUo = false;
      bool isAusCcBGV = false;
      bool fJrBztkqoB = false;
      bool qQNXasuxQq = false;
      bool edoEZlrDeh = false;
      string FGJMuxeYGL;
      string NolybtZxMf;
      string AJCNbPzbTE;
      string tMZubfitFS;
      string CsFtfQTGzj;
      string VpDsPuDuke;
      string yCECRBOqWu;
      string KeqsdGDIhK;
      string urcjhEJgeg;
      string cmJaUAoDce;
      string CcjDYpyJPJ;
      string quNZiGZUTN;
      string qgLpSWVQYd;
      string RAeDISHZLr;
      string FzRVogZjqO;
      string ZTjPmUQtkB;
      string UgkkqqQJRP;
      string yzIbHrOpAk;
      string xlYKDxQOQm;
      string CNnJWYOfdy;
      if(FGJMuxeYGL == CcjDYpyJPJ){QPRaPaLHIu = true;}
      else if(CcjDYpyJPJ == FGJMuxeYGL){OaJhXHIrcF = true;}
      if(NolybtZxMf == quNZiGZUTN){FZtzEiHZhs = true;}
      else if(quNZiGZUTN == NolybtZxMf){TyobMsTlJd = true;}
      if(AJCNbPzbTE == qgLpSWVQYd){ZBseNkLyEh = true;}
      else if(qgLpSWVQYd == AJCNbPzbTE){lkOaMiYPrg = true;}
      if(tMZubfitFS == RAeDISHZLr){ciMBTgTytc = true;}
      else if(RAeDISHZLr == tMZubfitFS){MQVnVqMKsI = true;}
      if(CsFtfQTGzj == FzRVogZjqO){lIFUgbSoFm = true;}
      else if(FzRVogZjqO == CsFtfQTGzj){erzXkLqHCU = true;}
      if(VpDsPuDuke == ZTjPmUQtkB){RoyjXPWmNe = true;}
      else if(ZTjPmUQtkB == VpDsPuDuke){GSUXWdLhUo = true;}
      if(yCECRBOqWu == UgkkqqQJRP){OMDaSWNreW = true;}
      else if(UgkkqqQJRP == yCECRBOqWu){isAusCcBGV = true;}
      if(KeqsdGDIhK == yzIbHrOpAk){PJfFHRuXxk = true;}
      if(urcjhEJgeg == xlYKDxQOQm){RVsRQnkbdE = true;}
      if(cmJaUAoDce == CNnJWYOfdy){KfjPNZFeCJ = true;}
      while(yzIbHrOpAk == KeqsdGDIhK){fJrBztkqoB = true;}
      while(xlYKDxQOQm == xlYKDxQOQm){qQNXasuxQq = true;}
      while(CNnJWYOfdy == CNnJWYOfdy){edoEZlrDeh = true;}
      if(QPRaPaLHIu == true){QPRaPaLHIu = false;}
      if(FZtzEiHZhs == true){FZtzEiHZhs = false;}
      if(ZBseNkLyEh == true){ZBseNkLyEh = false;}
      if(ciMBTgTytc == true){ciMBTgTytc = false;}
      if(lIFUgbSoFm == true){lIFUgbSoFm = false;}
      if(RoyjXPWmNe == true){RoyjXPWmNe = false;}
      if(OMDaSWNreW == true){OMDaSWNreW = false;}
      if(PJfFHRuXxk == true){PJfFHRuXxk = false;}
      if(RVsRQnkbdE == true){RVsRQnkbdE = false;}
      if(KfjPNZFeCJ == true){KfjPNZFeCJ = false;}
      if(OaJhXHIrcF == true){OaJhXHIrcF = false;}
      if(TyobMsTlJd == true){TyobMsTlJd = false;}
      if(lkOaMiYPrg == true){lkOaMiYPrg = false;}
      if(MQVnVqMKsI == true){MQVnVqMKsI = false;}
      if(erzXkLqHCU == true){erzXkLqHCU = false;}
      if(GSUXWdLhUo == true){GSUXWdLhUo = false;}
      if(isAusCcBGV == true){isAusCcBGV = false;}
      if(fJrBztkqoB == true){fJrBztkqoB = false;}
      if(qQNXasuxQq == true){qQNXasuxQq = false;}
      if(edoEZlrDeh == true){edoEZlrDeh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSXHEVPOQT
{ 
  void IwyEkfdhIi()
  { 
      bool KqhECdaGno = false;
      bool HmlVJRMDJU = false;
      bool LxfLYuSbmQ = false;
      bool Obwqmzncma = false;
      bool QMIWNOusQr = false;
      bool LrYHXMLVeH = false;
      bool KzSXZfpthJ = false;
      bool ciQiDznJxK = false;
      bool AZKuEVCoTa = false;
      bool nRxePRskwh = false;
      bool XBKHObbpDY = false;
      bool XBYUHknXSE = false;
      bool dAZHULlkTl = false;
      bool FDMPlyPDgc = false;
      bool sMkuCmscXe = false;
      bool cVRqEXaDlD = false;
      bool oqWRSUoIhI = false;
      bool VkpoLROeEh = false;
      bool RJMnIikUKO = false;
      bool WMQdmCoTbh = false;
      string KrePPpbdhi;
      string tkLFhSsVyo;
      string NjPPcqSGxQ;
      string HpzdsDDWqa;
      string wmOIENGRBr;
      string uklWIZbOlY;
      string XUgQbEkhLd;
      string PVeXraVGLP;
      string kAFEVWDcVT;
      string ankSCbFygz;
      string bXFWcYFOeg;
      string DUDVmWPctE;
      string AIMrDbkMUQ;
      string UXZLnMthax;
      string QoxnPFjOee;
      string LcDbzSLNTB;
      string mssOMfurga;
      string chBxnKKXbx;
      string qVgoErTxLV;
      string BgOZJXwibj;
      if(KrePPpbdhi == bXFWcYFOeg){KqhECdaGno = true;}
      else if(bXFWcYFOeg == KrePPpbdhi){XBKHObbpDY = true;}
      if(tkLFhSsVyo == DUDVmWPctE){HmlVJRMDJU = true;}
      else if(DUDVmWPctE == tkLFhSsVyo){XBYUHknXSE = true;}
      if(NjPPcqSGxQ == AIMrDbkMUQ){LxfLYuSbmQ = true;}
      else if(AIMrDbkMUQ == NjPPcqSGxQ){dAZHULlkTl = true;}
      if(HpzdsDDWqa == UXZLnMthax){Obwqmzncma = true;}
      else if(UXZLnMthax == HpzdsDDWqa){FDMPlyPDgc = true;}
      if(wmOIENGRBr == QoxnPFjOee){QMIWNOusQr = true;}
      else if(QoxnPFjOee == wmOIENGRBr){sMkuCmscXe = true;}
      if(uklWIZbOlY == LcDbzSLNTB){LrYHXMLVeH = true;}
      else if(LcDbzSLNTB == uklWIZbOlY){cVRqEXaDlD = true;}
      if(XUgQbEkhLd == mssOMfurga){KzSXZfpthJ = true;}
      else if(mssOMfurga == XUgQbEkhLd){oqWRSUoIhI = true;}
      if(PVeXraVGLP == chBxnKKXbx){ciQiDznJxK = true;}
      if(kAFEVWDcVT == qVgoErTxLV){AZKuEVCoTa = true;}
      if(ankSCbFygz == BgOZJXwibj){nRxePRskwh = true;}
      while(chBxnKKXbx == PVeXraVGLP){VkpoLROeEh = true;}
      while(qVgoErTxLV == qVgoErTxLV){RJMnIikUKO = true;}
      while(BgOZJXwibj == BgOZJXwibj){WMQdmCoTbh = true;}
      if(KqhECdaGno == true){KqhECdaGno = false;}
      if(HmlVJRMDJU == true){HmlVJRMDJU = false;}
      if(LxfLYuSbmQ == true){LxfLYuSbmQ = false;}
      if(Obwqmzncma == true){Obwqmzncma = false;}
      if(QMIWNOusQr == true){QMIWNOusQr = false;}
      if(LrYHXMLVeH == true){LrYHXMLVeH = false;}
      if(KzSXZfpthJ == true){KzSXZfpthJ = false;}
      if(ciQiDznJxK == true){ciQiDznJxK = false;}
      if(AZKuEVCoTa == true){AZKuEVCoTa = false;}
      if(nRxePRskwh == true){nRxePRskwh = false;}
      if(XBKHObbpDY == true){XBKHObbpDY = false;}
      if(XBYUHknXSE == true){XBYUHknXSE = false;}
      if(dAZHULlkTl == true){dAZHULlkTl = false;}
      if(FDMPlyPDgc == true){FDMPlyPDgc = false;}
      if(sMkuCmscXe == true){sMkuCmscXe = false;}
      if(cVRqEXaDlD == true){cVRqEXaDlD = false;}
      if(oqWRSUoIhI == true){oqWRSUoIhI = false;}
      if(VkpoLROeEh == true){VkpoLROeEh = false;}
      if(RJMnIikUKO == true){RJMnIikUKO = false;}
      if(WMQdmCoTbh == true){WMQdmCoTbh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TREGARIJSN
{ 
  void bmqQrPrNkG()
  { 
      bool XhBHalhINw = false;
      bool CHTyKyJCMT = false;
      bool polAQfkhHI = false;
      bool KYdnVUEduK = false;
      bool sTUjMGFXMd = false;
      bool XhfPqhwApt = false;
      bool AABFkccecp = false;
      bool tfHCaWUBnK = false;
      bool ZNVckcrOxm = false;
      bool XDmAJrSPyi = false;
      bool cZuVirZdnU = false;
      bool NtMfTmdXUI = false;
      bool kNhoRqrHsh = false;
      bool EECFgzSzsr = false;
      bool COacZdpHfV = false;
      bool OtupxOrGEr = false;
      bool ASkFPJqHzT = false;
      bool UedbFVmEOn = false;
      bool AjaWTJJMHR = false;
      bool HMuBqidUMQ = false;
      string zdXNDJzIGz;
      string yfeidCebCr;
      string RZEIntKdPb;
      string iKIuSgGpGA;
      string lXpplOxffM;
      string RmbFEZZOZJ;
      string zVsdQnXiQx;
      string unUCGsiNWZ;
      string wdyCKuiCpr;
      string HrQxAQdMZx;
      string pNOiQcRZzK;
      string pLqzMUWpSU;
      string FVsYoDXWBp;
      string OWnYjhPPkh;
      string dICeBuARkf;
      string snsFrUUpsN;
      string FuXJuTXSPd;
      string FHFjqwSNWt;
      string CGkVwacifO;
      string NYWWchksih;
      if(zdXNDJzIGz == pNOiQcRZzK){XhBHalhINw = true;}
      else if(pNOiQcRZzK == zdXNDJzIGz){cZuVirZdnU = true;}
      if(yfeidCebCr == pLqzMUWpSU){CHTyKyJCMT = true;}
      else if(pLqzMUWpSU == yfeidCebCr){NtMfTmdXUI = true;}
      if(RZEIntKdPb == FVsYoDXWBp){polAQfkhHI = true;}
      else if(FVsYoDXWBp == RZEIntKdPb){kNhoRqrHsh = true;}
      if(iKIuSgGpGA == OWnYjhPPkh){KYdnVUEduK = true;}
      else if(OWnYjhPPkh == iKIuSgGpGA){EECFgzSzsr = true;}
      if(lXpplOxffM == dICeBuARkf){sTUjMGFXMd = true;}
      else if(dICeBuARkf == lXpplOxffM){COacZdpHfV = true;}
      if(RmbFEZZOZJ == snsFrUUpsN){XhfPqhwApt = true;}
      else if(snsFrUUpsN == RmbFEZZOZJ){OtupxOrGEr = true;}
      if(zVsdQnXiQx == FuXJuTXSPd){AABFkccecp = true;}
      else if(FuXJuTXSPd == zVsdQnXiQx){ASkFPJqHzT = true;}
      if(unUCGsiNWZ == FHFjqwSNWt){tfHCaWUBnK = true;}
      if(wdyCKuiCpr == CGkVwacifO){ZNVckcrOxm = true;}
      if(HrQxAQdMZx == NYWWchksih){XDmAJrSPyi = true;}
      while(FHFjqwSNWt == unUCGsiNWZ){UedbFVmEOn = true;}
      while(CGkVwacifO == CGkVwacifO){AjaWTJJMHR = true;}
      while(NYWWchksih == NYWWchksih){HMuBqidUMQ = true;}
      if(XhBHalhINw == true){XhBHalhINw = false;}
      if(CHTyKyJCMT == true){CHTyKyJCMT = false;}
      if(polAQfkhHI == true){polAQfkhHI = false;}
      if(KYdnVUEduK == true){KYdnVUEduK = false;}
      if(sTUjMGFXMd == true){sTUjMGFXMd = false;}
      if(XhfPqhwApt == true){XhfPqhwApt = false;}
      if(AABFkccecp == true){AABFkccecp = false;}
      if(tfHCaWUBnK == true){tfHCaWUBnK = false;}
      if(ZNVckcrOxm == true){ZNVckcrOxm = false;}
      if(XDmAJrSPyi == true){XDmAJrSPyi = false;}
      if(cZuVirZdnU == true){cZuVirZdnU = false;}
      if(NtMfTmdXUI == true){NtMfTmdXUI = false;}
      if(kNhoRqrHsh == true){kNhoRqrHsh = false;}
      if(EECFgzSzsr == true){EECFgzSzsr = false;}
      if(COacZdpHfV == true){COacZdpHfV = false;}
      if(OtupxOrGEr == true){OtupxOrGEr = false;}
      if(ASkFPJqHzT == true){ASkFPJqHzT = false;}
      if(UedbFVmEOn == true){UedbFVmEOn = false;}
      if(AjaWTJJMHR == true){AjaWTJJMHR = false;}
      if(HMuBqidUMQ == true){HMuBqidUMQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVWQXDLNVN
{ 
  void PXPdPGgPzu()
  { 
      bool GfcQGGygdG = false;
      bool MdOOUcKjnN = false;
      bool KOAUDDWmbL = false;
      bool CqecgPaFGY = false;
      bool yJkIXIDFgb = false;
      bool MJGmnrfHNC = false;
      bool jKEREVylgF = false;
      bool BFdOPBcqwu = false;
      bool AQGAzrkqno = false;
      bool iSrDomFTDC = false;
      bool JRYaZHfqWm = false;
      bool OnLRCSEERM = false;
      bool jGxqViNZYc = false;
      bool wJntkhqeZr = false;
      bool LsUBauHZBW = false;
      bool hABqRCTgFq = false;
      bool tGStpFAQgT = false;
      bool bZdZApluQa = false;
      bool bmYCuuIwbi = false;
      bool OJYhyFaZKU = false;
      string ePUQgnBqBu;
      string qGigqxFxUL;
      string PmeYrxeoGe;
      string tVujxaawbT;
      string WgCCNJzCqe;
      string bfokdqjuXi;
      string JLjVBUKyiP;
      string WJVBnhkcLi;
      string xcyaDNfKGG;
      string qeXrJKxfAr;
      string yBSaIRJnwu;
      string FGiolfNISm;
      string nzqbYqlcqc;
      string kEbSjwJWSk;
      string ErNLAjwhGd;
      string xnNMDyJqCQ;
      string fgxTKBdPFo;
      string Wqpgiwlfbn;
      string uDVNfwpPPk;
      string lSUCEWttBz;
      if(ePUQgnBqBu == yBSaIRJnwu){GfcQGGygdG = true;}
      else if(yBSaIRJnwu == ePUQgnBqBu){JRYaZHfqWm = true;}
      if(qGigqxFxUL == FGiolfNISm){MdOOUcKjnN = true;}
      else if(FGiolfNISm == qGigqxFxUL){OnLRCSEERM = true;}
      if(PmeYrxeoGe == nzqbYqlcqc){KOAUDDWmbL = true;}
      else if(nzqbYqlcqc == PmeYrxeoGe){jGxqViNZYc = true;}
      if(tVujxaawbT == kEbSjwJWSk){CqecgPaFGY = true;}
      else if(kEbSjwJWSk == tVujxaawbT){wJntkhqeZr = true;}
      if(WgCCNJzCqe == ErNLAjwhGd){yJkIXIDFgb = true;}
      else if(ErNLAjwhGd == WgCCNJzCqe){LsUBauHZBW = true;}
      if(bfokdqjuXi == xnNMDyJqCQ){MJGmnrfHNC = true;}
      else if(xnNMDyJqCQ == bfokdqjuXi){hABqRCTgFq = true;}
      if(JLjVBUKyiP == fgxTKBdPFo){jKEREVylgF = true;}
      else if(fgxTKBdPFo == JLjVBUKyiP){tGStpFAQgT = true;}
      if(WJVBnhkcLi == Wqpgiwlfbn){BFdOPBcqwu = true;}
      if(xcyaDNfKGG == uDVNfwpPPk){AQGAzrkqno = true;}
      if(qeXrJKxfAr == lSUCEWttBz){iSrDomFTDC = true;}
      while(Wqpgiwlfbn == WJVBnhkcLi){bZdZApluQa = true;}
      while(uDVNfwpPPk == uDVNfwpPPk){bmYCuuIwbi = true;}
      while(lSUCEWttBz == lSUCEWttBz){OJYhyFaZKU = true;}
      if(GfcQGGygdG == true){GfcQGGygdG = false;}
      if(MdOOUcKjnN == true){MdOOUcKjnN = false;}
      if(KOAUDDWmbL == true){KOAUDDWmbL = false;}
      if(CqecgPaFGY == true){CqecgPaFGY = false;}
      if(yJkIXIDFgb == true){yJkIXIDFgb = false;}
      if(MJGmnrfHNC == true){MJGmnrfHNC = false;}
      if(jKEREVylgF == true){jKEREVylgF = false;}
      if(BFdOPBcqwu == true){BFdOPBcqwu = false;}
      if(AQGAzrkqno == true){AQGAzrkqno = false;}
      if(iSrDomFTDC == true){iSrDomFTDC = false;}
      if(JRYaZHfqWm == true){JRYaZHfqWm = false;}
      if(OnLRCSEERM == true){OnLRCSEERM = false;}
      if(jGxqViNZYc == true){jGxqViNZYc = false;}
      if(wJntkhqeZr == true){wJntkhqeZr = false;}
      if(LsUBauHZBW == true){LsUBauHZBW = false;}
      if(hABqRCTgFq == true){hABqRCTgFq = false;}
      if(tGStpFAQgT == true){tGStpFAQgT = false;}
      if(bZdZApluQa == true){bZdZApluQa = false;}
      if(bmYCuuIwbi == true){bmYCuuIwbi = false;}
      if(OJYhyFaZKU == true){OJYhyFaZKU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJOVQYWUQL
{ 
  void yKyHMwnpfp()
  { 
      bool USoXZhAgPt = false;
      bool kZcxLGBSrf = false;
      bool CFywRRdXSM = false;
      bool VzeNegXnsU = false;
      bool FdsclWZGFH = false;
      bool yQtmUOTsGH = false;
      bool EcNCXkuPSd = false;
      bool hNYWaYMUJt = false;
      bool rWRKNFFqrQ = false;
      bool MehlPbPpEA = false;
      bool bJnbZkqWMw = false;
      bool BzjLOhKDoS = false;
      bool fDXCQDemHy = false;
      bool IWPIShhpkc = false;
      bool NheuONtVWh = false;
      bool QLBlUXllKV = false;
      bool FEPNmeiasf = false;
      bool AUSLEyYbmC = false;
      bool IJPYgwUdnt = false;
      bool wueOWJRQIi = false;
      string MwTsOIFmyL;
      string OsSEDyShJo;
      string zWBZraYlwJ;
      string JQdYMhbXLP;
      string UxSIZGYZCU;
      string jitijpusAm;
      string jTqnCyOtqV;
      string VtWtUBDszl;
      string ByiaYZVunW;
      string lhXXfBFdFb;
      string qehgzpLANh;
      string lCsOkkjQPb;
      string bTFUinWyNS;
      string uYmXuWPCbh;
      string OVgGjjnIlt;
      string QoOdAXYNxK;
      string TNltlMPVTO;
      string UhngNFlzjz;
      string zNLSCFKJXX;
      string xCEQOAjlTW;
      if(MwTsOIFmyL == qehgzpLANh){USoXZhAgPt = true;}
      else if(qehgzpLANh == MwTsOIFmyL){bJnbZkqWMw = true;}
      if(OsSEDyShJo == lCsOkkjQPb){kZcxLGBSrf = true;}
      else if(lCsOkkjQPb == OsSEDyShJo){BzjLOhKDoS = true;}
      if(zWBZraYlwJ == bTFUinWyNS){CFywRRdXSM = true;}
      else if(bTFUinWyNS == zWBZraYlwJ){fDXCQDemHy = true;}
      if(JQdYMhbXLP == uYmXuWPCbh){VzeNegXnsU = true;}
      else if(uYmXuWPCbh == JQdYMhbXLP){IWPIShhpkc = true;}
      if(UxSIZGYZCU == OVgGjjnIlt){FdsclWZGFH = true;}
      else if(OVgGjjnIlt == UxSIZGYZCU){NheuONtVWh = true;}
      if(jitijpusAm == QoOdAXYNxK){yQtmUOTsGH = true;}
      else if(QoOdAXYNxK == jitijpusAm){QLBlUXllKV = true;}
      if(jTqnCyOtqV == TNltlMPVTO){EcNCXkuPSd = true;}
      else if(TNltlMPVTO == jTqnCyOtqV){FEPNmeiasf = true;}
      if(VtWtUBDszl == UhngNFlzjz){hNYWaYMUJt = true;}
      if(ByiaYZVunW == zNLSCFKJXX){rWRKNFFqrQ = true;}
      if(lhXXfBFdFb == xCEQOAjlTW){MehlPbPpEA = true;}
      while(UhngNFlzjz == VtWtUBDszl){AUSLEyYbmC = true;}
      while(zNLSCFKJXX == zNLSCFKJXX){IJPYgwUdnt = true;}
      while(xCEQOAjlTW == xCEQOAjlTW){wueOWJRQIi = true;}
      if(USoXZhAgPt == true){USoXZhAgPt = false;}
      if(kZcxLGBSrf == true){kZcxLGBSrf = false;}
      if(CFywRRdXSM == true){CFywRRdXSM = false;}
      if(VzeNegXnsU == true){VzeNegXnsU = false;}
      if(FdsclWZGFH == true){FdsclWZGFH = false;}
      if(yQtmUOTsGH == true){yQtmUOTsGH = false;}
      if(EcNCXkuPSd == true){EcNCXkuPSd = false;}
      if(hNYWaYMUJt == true){hNYWaYMUJt = false;}
      if(rWRKNFFqrQ == true){rWRKNFFqrQ = false;}
      if(MehlPbPpEA == true){MehlPbPpEA = false;}
      if(bJnbZkqWMw == true){bJnbZkqWMw = false;}
      if(BzjLOhKDoS == true){BzjLOhKDoS = false;}
      if(fDXCQDemHy == true){fDXCQDemHy = false;}
      if(IWPIShhpkc == true){IWPIShhpkc = false;}
      if(NheuONtVWh == true){NheuONtVWh = false;}
      if(QLBlUXllKV == true){QLBlUXllKV = false;}
      if(FEPNmeiasf == true){FEPNmeiasf = false;}
      if(AUSLEyYbmC == true){AUSLEyYbmC = false;}
      if(IJPYgwUdnt == true){IJPYgwUdnt = false;}
      if(wueOWJRQIi == true){wueOWJRQIi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDWQVGQGXY
{ 
  void PglcTZGpaj()
  { 
      bool WDyDoXRbjk = false;
      bool IXKjAaRcUb = false;
      bool KhwomTZlgk = false;
      bool xnXrOauSlJ = false;
      bool VYmKzyeRNV = false;
      bool iJfcooGJPU = false;
      bool yeuymTzRUY = false;
      bool eypLGktloo = false;
      bool nIXLCnIuDZ = false;
      bool TlDRLpdoWf = false;
      bool zMwnpkSUWE = false;
      bool tUTZfoGiwy = false;
      bool KDOuFstYAP = false;
      bool HFOJpbLjUR = false;
      bool UnYyfyRckV = false;
      bool itrXUuyBiw = false;
      bool ptUGxnGKjE = false;
      bool dWNecWeQOG = false;
      bool bQmdfMMqou = false;
      bool dJAYaaTRBq = false;
      string DWTcWzrJuz;
      string arSkOundno;
      string KdcBaQrkWY;
      string MeIbCVUAAJ;
      string GuWkpbrpcc;
      string yAJSjYsSCG;
      string GHlVmujqhr;
      string ancdhOHrKy;
      string YCHtaLVoqd;
      string cCytDzJAxt;
      string rBIjCJWekV;
      string RAHDgEzqta;
      string ZtzEOYoiah;
      string FGtPGXtXqR;
      string npEVLctuMz;
      string ARFWUyBDVd;
      string UnEDPLFqwJ;
      string Jbzclipdsl;
      string dtWbhnBXuH;
      string VpBNwAlBFA;
      if(DWTcWzrJuz == rBIjCJWekV){WDyDoXRbjk = true;}
      else if(rBIjCJWekV == DWTcWzrJuz){zMwnpkSUWE = true;}
      if(arSkOundno == RAHDgEzqta){IXKjAaRcUb = true;}
      else if(RAHDgEzqta == arSkOundno){tUTZfoGiwy = true;}
      if(KdcBaQrkWY == ZtzEOYoiah){KhwomTZlgk = true;}
      else if(ZtzEOYoiah == KdcBaQrkWY){KDOuFstYAP = true;}
      if(MeIbCVUAAJ == FGtPGXtXqR){xnXrOauSlJ = true;}
      else if(FGtPGXtXqR == MeIbCVUAAJ){HFOJpbLjUR = true;}
      if(GuWkpbrpcc == npEVLctuMz){VYmKzyeRNV = true;}
      else if(npEVLctuMz == GuWkpbrpcc){UnYyfyRckV = true;}
      if(yAJSjYsSCG == ARFWUyBDVd){iJfcooGJPU = true;}
      else if(ARFWUyBDVd == yAJSjYsSCG){itrXUuyBiw = true;}
      if(GHlVmujqhr == UnEDPLFqwJ){yeuymTzRUY = true;}
      else if(UnEDPLFqwJ == GHlVmujqhr){ptUGxnGKjE = true;}
      if(ancdhOHrKy == Jbzclipdsl){eypLGktloo = true;}
      if(YCHtaLVoqd == dtWbhnBXuH){nIXLCnIuDZ = true;}
      if(cCytDzJAxt == VpBNwAlBFA){TlDRLpdoWf = true;}
      while(Jbzclipdsl == ancdhOHrKy){dWNecWeQOG = true;}
      while(dtWbhnBXuH == dtWbhnBXuH){bQmdfMMqou = true;}
      while(VpBNwAlBFA == VpBNwAlBFA){dJAYaaTRBq = true;}
      if(WDyDoXRbjk == true){WDyDoXRbjk = false;}
      if(IXKjAaRcUb == true){IXKjAaRcUb = false;}
      if(KhwomTZlgk == true){KhwomTZlgk = false;}
      if(xnXrOauSlJ == true){xnXrOauSlJ = false;}
      if(VYmKzyeRNV == true){VYmKzyeRNV = false;}
      if(iJfcooGJPU == true){iJfcooGJPU = false;}
      if(yeuymTzRUY == true){yeuymTzRUY = false;}
      if(eypLGktloo == true){eypLGktloo = false;}
      if(nIXLCnIuDZ == true){nIXLCnIuDZ = false;}
      if(TlDRLpdoWf == true){TlDRLpdoWf = false;}
      if(zMwnpkSUWE == true){zMwnpkSUWE = false;}
      if(tUTZfoGiwy == true){tUTZfoGiwy = false;}
      if(KDOuFstYAP == true){KDOuFstYAP = false;}
      if(HFOJpbLjUR == true){HFOJpbLjUR = false;}
      if(UnYyfyRckV == true){UnYyfyRckV = false;}
      if(itrXUuyBiw == true){itrXUuyBiw = false;}
      if(ptUGxnGKjE == true){ptUGxnGKjE = false;}
      if(dWNecWeQOG == true){dWNecWeQOG = false;}
      if(bQmdfMMqou == true){bQmdfMMqou = false;}
      if(dJAYaaTRBq == true){dJAYaaTRBq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSVNTTABCU
{ 
  void UyVhpztqQB()
  { 
      bool tgoEVNdRhx = false;
      bool yngMZUdQZl = false;
      bool NpRGEPgGlo = false;
      bool mKnAUSDtAq = false;
      bool nSaXTpImPb = false;
      bool MEuwpDOhAF = false;
      bool fXerJmzfqH = false;
      bool RjPhytOsmN = false;
      bool GtqKbiPqJQ = false;
      bool DUstKPmhNg = false;
      bool pbuHJboMyw = false;
      bool oVumylgTPa = false;
      bool WHVaDwqUWh = false;
      bool GfeGWdyiAA = false;
      bool tDsNbhZGuY = false;
      bool iTRmJiGUDN = false;
      bool kToPoIpnPU = false;
      bool mxSPgTNHyV = false;
      bool WkYyzmNrxn = false;
      bool XdemPZNdYS = false;
      string HoFCYHjdMi;
      string CXOlpHBzXb;
      string ouimakEPHo;
      string ypNQwTDLAO;
      string XIQykUWiFy;
      string KOuidMFSbm;
      string DTVXjMKypV;
      string EpzJEfdjBG;
      string OUKJdjtdli;
      string OjiMKEmsNY;
      string JXrisUPley;
      string hVQUYhIMsA;
      string RfLGHTGlyA;
      string sjWcwpbaPJ;
      string TIznBrTOmb;
      string uaANGdLlbZ;
      string NcmeExymYh;
      string GgwifJfXEO;
      string zryWERjIVR;
      string dpzpwqVUiE;
      if(HoFCYHjdMi == JXrisUPley){tgoEVNdRhx = true;}
      else if(JXrisUPley == HoFCYHjdMi){pbuHJboMyw = true;}
      if(CXOlpHBzXb == hVQUYhIMsA){yngMZUdQZl = true;}
      else if(hVQUYhIMsA == CXOlpHBzXb){oVumylgTPa = true;}
      if(ouimakEPHo == RfLGHTGlyA){NpRGEPgGlo = true;}
      else if(RfLGHTGlyA == ouimakEPHo){WHVaDwqUWh = true;}
      if(ypNQwTDLAO == sjWcwpbaPJ){mKnAUSDtAq = true;}
      else if(sjWcwpbaPJ == ypNQwTDLAO){GfeGWdyiAA = true;}
      if(XIQykUWiFy == TIznBrTOmb){nSaXTpImPb = true;}
      else if(TIznBrTOmb == XIQykUWiFy){tDsNbhZGuY = true;}
      if(KOuidMFSbm == uaANGdLlbZ){MEuwpDOhAF = true;}
      else if(uaANGdLlbZ == KOuidMFSbm){iTRmJiGUDN = true;}
      if(DTVXjMKypV == NcmeExymYh){fXerJmzfqH = true;}
      else if(NcmeExymYh == DTVXjMKypV){kToPoIpnPU = true;}
      if(EpzJEfdjBG == GgwifJfXEO){RjPhytOsmN = true;}
      if(OUKJdjtdli == zryWERjIVR){GtqKbiPqJQ = true;}
      if(OjiMKEmsNY == dpzpwqVUiE){DUstKPmhNg = true;}
      while(GgwifJfXEO == EpzJEfdjBG){mxSPgTNHyV = true;}
      while(zryWERjIVR == zryWERjIVR){WkYyzmNrxn = true;}
      while(dpzpwqVUiE == dpzpwqVUiE){XdemPZNdYS = true;}
      if(tgoEVNdRhx == true){tgoEVNdRhx = false;}
      if(yngMZUdQZl == true){yngMZUdQZl = false;}
      if(NpRGEPgGlo == true){NpRGEPgGlo = false;}
      if(mKnAUSDtAq == true){mKnAUSDtAq = false;}
      if(nSaXTpImPb == true){nSaXTpImPb = false;}
      if(MEuwpDOhAF == true){MEuwpDOhAF = false;}
      if(fXerJmzfqH == true){fXerJmzfqH = false;}
      if(RjPhytOsmN == true){RjPhytOsmN = false;}
      if(GtqKbiPqJQ == true){GtqKbiPqJQ = false;}
      if(DUstKPmhNg == true){DUstKPmhNg = false;}
      if(pbuHJboMyw == true){pbuHJboMyw = false;}
      if(oVumylgTPa == true){oVumylgTPa = false;}
      if(WHVaDwqUWh == true){WHVaDwqUWh = false;}
      if(GfeGWdyiAA == true){GfeGWdyiAA = false;}
      if(tDsNbhZGuY == true){tDsNbhZGuY = false;}
      if(iTRmJiGUDN == true){iTRmJiGUDN = false;}
      if(kToPoIpnPU == true){kToPoIpnPU = false;}
      if(mxSPgTNHyV == true){mxSPgTNHyV = false;}
      if(WkYyzmNrxn == true){WkYyzmNrxn = false;}
      if(XdemPZNdYS == true){XdemPZNdYS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DELUDSTSQM
{ 
  void oUYFjKKGKk()
  { 
      bool ouwZLOkcFC = false;
      bool kxBZwPdyTZ = false;
      bool NrJFWVkAAn = false;
      bool HUueKxwpsB = false;
      bool hkuBYgqhyi = false;
      bool ccVcGxlpDp = false;
      bool djcRuPCVPz = false;
      bool TnESrcxIgo = false;
      bool dDCQKeyRYM = false;
      bool LFlCWxIcGJ = false;
      bool dURyPoXCkd = false;
      bool zcJNLahLGQ = false;
      bool QkxCmNBCwu = false;
      bool UTBWLJkDBV = false;
      bool GwgtNhwYqw = false;
      bool PwWprsXOLB = false;
      bool mVGpIfblCC = false;
      bool odJkJUECoF = false;
      bool RcKAeXxLdR = false;
      bool lVrzhjoqkh = false;
      string UaUIrTeDrD;
      string xdZWjgiwLP;
      string idgXwuMLrT;
      string TSFpHXNuBs;
      string EXFgfGbPUN;
      string AgCUCqtxLx;
      string GTKXjdXiPL;
      string TnuSKLXzro;
      string TwqeSmPknQ;
      string dPiElkMgxB;
      string irAIsMkjJq;
      string StFWcKbfFw;
      string OmuyhDEqgY;
      string ypBqGbuhkG;
      string BeawxiKMaa;
      string IfbAlwwCZp;
      string HtDkrcsOPB;
      string OsuyuiLzAz;
      string srPFQSOAEJ;
      string esIuyHbpDU;
      if(UaUIrTeDrD == irAIsMkjJq){ouwZLOkcFC = true;}
      else if(irAIsMkjJq == UaUIrTeDrD){dURyPoXCkd = true;}
      if(xdZWjgiwLP == StFWcKbfFw){kxBZwPdyTZ = true;}
      else if(StFWcKbfFw == xdZWjgiwLP){zcJNLahLGQ = true;}
      if(idgXwuMLrT == OmuyhDEqgY){NrJFWVkAAn = true;}
      else if(OmuyhDEqgY == idgXwuMLrT){QkxCmNBCwu = true;}
      if(TSFpHXNuBs == ypBqGbuhkG){HUueKxwpsB = true;}
      else if(ypBqGbuhkG == TSFpHXNuBs){UTBWLJkDBV = true;}
      if(EXFgfGbPUN == BeawxiKMaa){hkuBYgqhyi = true;}
      else if(BeawxiKMaa == EXFgfGbPUN){GwgtNhwYqw = true;}
      if(AgCUCqtxLx == IfbAlwwCZp){ccVcGxlpDp = true;}
      else if(IfbAlwwCZp == AgCUCqtxLx){PwWprsXOLB = true;}
      if(GTKXjdXiPL == HtDkrcsOPB){djcRuPCVPz = true;}
      else if(HtDkrcsOPB == GTKXjdXiPL){mVGpIfblCC = true;}
      if(TnuSKLXzro == OsuyuiLzAz){TnESrcxIgo = true;}
      if(TwqeSmPknQ == srPFQSOAEJ){dDCQKeyRYM = true;}
      if(dPiElkMgxB == esIuyHbpDU){LFlCWxIcGJ = true;}
      while(OsuyuiLzAz == TnuSKLXzro){odJkJUECoF = true;}
      while(srPFQSOAEJ == srPFQSOAEJ){RcKAeXxLdR = true;}
      while(esIuyHbpDU == esIuyHbpDU){lVrzhjoqkh = true;}
      if(ouwZLOkcFC == true){ouwZLOkcFC = false;}
      if(kxBZwPdyTZ == true){kxBZwPdyTZ = false;}
      if(NrJFWVkAAn == true){NrJFWVkAAn = false;}
      if(HUueKxwpsB == true){HUueKxwpsB = false;}
      if(hkuBYgqhyi == true){hkuBYgqhyi = false;}
      if(ccVcGxlpDp == true){ccVcGxlpDp = false;}
      if(djcRuPCVPz == true){djcRuPCVPz = false;}
      if(TnESrcxIgo == true){TnESrcxIgo = false;}
      if(dDCQKeyRYM == true){dDCQKeyRYM = false;}
      if(LFlCWxIcGJ == true){LFlCWxIcGJ = false;}
      if(dURyPoXCkd == true){dURyPoXCkd = false;}
      if(zcJNLahLGQ == true){zcJNLahLGQ = false;}
      if(QkxCmNBCwu == true){QkxCmNBCwu = false;}
      if(UTBWLJkDBV == true){UTBWLJkDBV = false;}
      if(GwgtNhwYqw == true){GwgtNhwYqw = false;}
      if(PwWprsXOLB == true){PwWprsXOLB = false;}
      if(mVGpIfblCC == true){mVGpIfblCC = false;}
      if(odJkJUECoF == true){odJkJUECoF = false;}
      if(RcKAeXxLdR == true){RcKAeXxLdR = false;}
      if(lVrzhjoqkh == true){lVrzhjoqkh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSCTMOBVPV
{ 
  void HhWHcudtKQ()
  { 
      bool EtrkSsndec = false;
      bool LTkJYRBbDM = false;
      bool dxnujdJDLl = false;
      bool NPuYjmkYGP = false;
      bool pPVzJkaxnT = false;
      bool KVpdjHFxAn = false;
      bool jjRrPwYMZl = false;
      bool gcUmWNaoky = false;
      bool DLOrbrYQnb = false;
      bool gnXReFydjN = false;
      bool MNWCmhBCHW = false;
      bool fQMCjXUZQX = false;
      bool WHYxFrECHQ = false;
      bool OxEWlpoMEt = false;
      bool pVJQuPaVhH = false;
      bool jXNMqFoYxt = false;
      bool cytqHiLoQt = false;
      bool iIUVgAyHCo = false;
      bool QhUAfqirff = false;
      bool APPKQrbSIM = false;
      string CdPnxqdLwc;
      string gZEHJksmKE;
      string cfXNKDiKGA;
      string jmWUClxrWq;
      string CyCsulNBNl;
      string jNDiHWGCds;
      string HTFwstCjEW;
      string mAPSCdcdSY;
      string pgwTQVimMf;
      string euNdjhrGAA;
      string idxpzixjgc;
      string sbiFCaWleW;
      string KOWYqrlliT;
      string kVdSoMjGUh;
      string XzGjlDLIaJ;
      string KGbcoTGXyG;
      string wLBMrXyQPp;
      string pQRxyLImmn;
      string gdKZJetAcU;
      string FLHNlLxsqN;
      if(CdPnxqdLwc == idxpzixjgc){EtrkSsndec = true;}
      else if(idxpzixjgc == CdPnxqdLwc){MNWCmhBCHW = true;}
      if(gZEHJksmKE == sbiFCaWleW){LTkJYRBbDM = true;}
      else if(sbiFCaWleW == gZEHJksmKE){fQMCjXUZQX = true;}
      if(cfXNKDiKGA == KOWYqrlliT){dxnujdJDLl = true;}
      else if(KOWYqrlliT == cfXNKDiKGA){WHYxFrECHQ = true;}
      if(jmWUClxrWq == kVdSoMjGUh){NPuYjmkYGP = true;}
      else if(kVdSoMjGUh == jmWUClxrWq){OxEWlpoMEt = true;}
      if(CyCsulNBNl == XzGjlDLIaJ){pPVzJkaxnT = true;}
      else if(XzGjlDLIaJ == CyCsulNBNl){pVJQuPaVhH = true;}
      if(jNDiHWGCds == KGbcoTGXyG){KVpdjHFxAn = true;}
      else if(KGbcoTGXyG == jNDiHWGCds){jXNMqFoYxt = true;}
      if(HTFwstCjEW == wLBMrXyQPp){jjRrPwYMZl = true;}
      else if(wLBMrXyQPp == HTFwstCjEW){cytqHiLoQt = true;}
      if(mAPSCdcdSY == pQRxyLImmn){gcUmWNaoky = true;}
      if(pgwTQVimMf == gdKZJetAcU){DLOrbrYQnb = true;}
      if(euNdjhrGAA == FLHNlLxsqN){gnXReFydjN = true;}
      while(pQRxyLImmn == mAPSCdcdSY){iIUVgAyHCo = true;}
      while(gdKZJetAcU == gdKZJetAcU){QhUAfqirff = true;}
      while(FLHNlLxsqN == FLHNlLxsqN){APPKQrbSIM = true;}
      if(EtrkSsndec == true){EtrkSsndec = false;}
      if(LTkJYRBbDM == true){LTkJYRBbDM = false;}
      if(dxnujdJDLl == true){dxnujdJDLl = false;}
      if(NPuYjmkYGP == true){NPuYjmkYGP = false;}
      if(pPVzJkaxnT == true){pPVzJkaxnT = false;}
      if(KVpdjHFxAn == true){KVpdjHFxAn = false;}
      if(jjRrPwYMZl == true){jjRrPwYMZl = false;}
      if(gcUmWNaoky == true){gcUmWNaoky = false;}
      if(DLOrbrYQnb == true){DLOrbrYQnb = false;}
      if(gnXReFydjN == true){gnXReFydjN = false;}
      if(MNWCmhBCHW == true){MNWCmhBCHW = false;}
      if(fQMCjXUZQX == true){fQMCjXUZQX = false;}
      if(WHYxFrECHQ == true){WHYxFrECHQ = false;}
      if(OxEWlpoMEt == true){OxEWlpoMEt = false;}
      if(pVJQuPaVhH == true){pVJQuPaVhH = false;}
      if(jXNMqFoYxt == true){jXNMqFoYxt = false;}
      if(cytqHiLoQt == true){cytqHiLoQt = false;}
      if(iIUVgAyHCo == true){iIUVgAyHCo = false;}
      if(QhUAfqirff == true){QhUAfqirff = false;}
      if(APPKQrbSIM == true){APPKQrbSIM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DAMXAONFZC
{ 
  void bjUfyawsxy()
  { 
      bool xXKzbqThXW = false;
      bool NDfGHTSDZF = false;
      bool LrzAiIpwJR = false;
      bool umNYRNCYgU = false;
      bool yWuPZyDHiF = false;
      bool QlQyoEXJQT = false;
      bool AXXFaZpHnt = false;
      bool RsWEGowiaj = false;
      bool FiMEBIWOjM = false;
      bool orHNUayooz = false;
      bool HuSonWPLqz = false;
      bool HoifNRKTER = false;
      bool DbXaEYkJje = false;
      bool pHtabJPWPd = false;
      bool sLWjFAIbzC = false;
      bool QekWwfXqkO = false;
      bool kGaMJAtIDD = false;
      bool BmDZYqEmVE = false;
      bool PJJhOLVXdw = false;
      bool lYlBsmjKZE = false;
      string igtQkNMoHg;
      string ygFRmBBDLc;
      string dUnVNinBuU;
      string gQBgTEPVyd;
      string qYrydfqxaY;
      string XGXeEOrYCC;
      string ZLtlAgeYxi;
      string keFhlFboqg;
      string qpZWxZsWcE;
      string LpTwDeeFyw;
      string BSzrmrApsz;
      string mCgUKikWoZ;
      string nIwrWtLJdG;
      string ZVqufYqhiF;
      string ZCdcRIJykU;
      string tHQXIrWGUr;
      string fqMlYQLlnk;
      string rDmiAkeSZO;
      string kMXIMSESln;
      string CjNqYipqEB;
      if(igtQkNMoHg == BSzrmrApsz){xXKzbqThXW = true;}
      else if(BSzrmrApsz == igtQkNMoHg){HuSonWPLqz = true;}
      if(ygFRmBBDLc == mCgUKikWoZ){NDfGHTSDZF = true;}
      else if(mCgUKikWoZ == ygFRmBBDLc){HoifNRKTER = true;}
      if(dUnVNinBuU == nIwrWtLJdG){LrzAiIpwJR = true;}
      else if(nIwrWtLJdG == dUnVNinBuU){DbXaEYkJje = true;}
      if(gQBgTEPVyd == ZVqufYqhiF){umNYRNCYgU = true;}
      else if(ZVqufYqhiF == gQBgTEPVyd){pHtabJPWPd = true;}
      if(qYrydfqxaY == ZCdcRIJykU){yWuPZyDHiF = true;}
      else if(ZCdcRIJykU == qYrydfqxaY){sLWjFAIbzC = true;}
      if(XGXeEOrYCC == tHQXIrWGUr){QlQyoEXJQT = true;}
      else if(tHQXIrWGUr == XGXeEOrYCC){QekWwfXqkO = true;}
      if(ZLtlAgeYxi == fqMlYQLlnk){AXXFaZpHnt = true;}
      else if(fqMlYQLlnk == ZLtlAgeYxi){kGaMJAtIDD = true;}
      if(keFhlFboqg == rDmiAkeSZO){RsWEGowiaj = true;}
      if(qpZWxZsWcE == kMXIMSESln){FiMEBIWOjM = true;}
      if(LpTwDeeFyw == CjNqYipqEB){orHNUayooz = true;}
      while(rDmiAkeSZO == keFhlFboqg){BmDZYqEmVE = true;}
      while(kMXIMSESln == kMXIMSESln){PJJhOLVXdw = true;}
      while(CjNqYipqEB == CjNqYipqEB){lYlBsmjKZE = true;}
      if(xXKzbqThXW == true){xXKzbqThXW = false;}
      if(NDfGHTSDZF == true){NDfGHTSDZF = false;}
      if(LrzAiIpwJR == true){LrzAiIpwJR = false;}
      if(umNYRNCYgU == true){umNYRNCYgU = false;}
      if(yWuPZyDHiF == true){yWuPZyDHiF = false;}
      if(QlQyoEXJQT == true){QlQyoEXJQT = false;}
      if(AXXFaZpHnt == true){AXXFaZpHnt = false;}
      if(RsWEGowiaj == true){RsWEGowiaj = false;}
      if(FiMEBIWOjM == true){FiMEBIWOjM = false;}
      if(orHNUayooz == true){orHNUayooz = false;}
      if(HuSonWPLqz == true){HuSonWPLqz = false;}
      if(HoifNRKTER == true){HoifNRKTER = false;}
      if(DbXaEYkJje == true){DbXaEYkJje = false;}
      if(pHtabJPWPd == true){pHtabJPWPd = false;}
      if(sLWjFAIbzC == true){sLWjFAIbzC = false;}
      if(QekWwfXqkO == true){QekWwfXqkO = false;}
      if(kGaMJAtIDD == true){kGaMJAtIDD = false;}
      if(BmDZYqEmVE == true){BmDZYqEmVE = false;}
      if(PJJhOLVXdw == true){PJJhOLVXdw = false;}
      if(lYlBsmjKZE == true){lYlBsmjKZE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNRIOPOKPD
{ 
  void FaPxgtSORA()
  { 
      bool KthLyODZKx = false;
      bool mjYmlQbLfc = false;
      bool oQnXIwdEzU = false;
      bool KmqDjtQdee = false;
      bool efzZhOqiCg = false;
      bool QYWNStGJCB = false;
      bool kyaplzrUDr = false;
      bool zyfAxIQOpt = false;
      bool EtCSDlPcjo = false;
      bool nGbctfFJmh = false;
      bool VVfKgSrWPJ = false;
      bool drTHxpwHlA = false;
      bool jOkNEsVCGQ = false;
      bool DHaHXhOqlk = false;
      bool ssMZLumTfE = false;
      bool jxWlyHkSGm = false;
      bool wpPyGVQLjO = false;
      bool bEUBHqBKCI = false;
      bool GCWBgFjoJQ = false;
      bool xwkynDcNTo = false;
      string rgMRoVdmDZ;
      string TJzPNJGkFT;
      string wFpLbxDHmp;
      string OwbWRlhKjq;
      string pItJjfdzpy;
      string mbrNelpBor;
      string RVzNLXhbxb;
      string bwAOdnLgaw;
      string SDRnDlDNrf;
      string ufUrYTIgxL;
      string xCCNWpadjp;
      string aJZrYNELJY;
      string TTjRfuaIoJ;
      string fdiOyQBDQM;
      string LYdBFkFbSK;
      string PxWYrdRkgb;
      string PRoZKwaKsH;
      string MAtwNtphMt;
      string ozodthGKWU;
      string yQVoxsjDpI;
      if(rgMRoVdmDZ == xCCNWpadjp){KthLyODZKx = true;}
      else if(xCCNWpadjp == rgMRoVdmDZ){VVfKgSrWPJ = true;}
      if(TJzPNJGkFT == aJZrYNELJY){mjYmlQbLfc = true;}
      else if(aJZrYNELJY == TJzPNJGkFT){drTHxpwHlA = true;}
      if(wFpLbxDHmp == TTjRfuaIoJ){oQnXIwdEzU = true;}
      else if(TTjRfuaIoJ == wFpLbxDHmp){jOkNEsVCGQ = true;}
      if(OwbWRlhKjq == fdiOyQBDQM){KmqDjtQdee = true;}
      else if(fdiOyQBDQM == OwbWRlhKjq){DHaHXhOqlk = true;}
      if(pItJjfdzpy == LYdBFkFbSK){efzZhOqiCg = true;}
      else if(LYdBFkFbSK == pItJjfdzpy){ssMZLumTfE = true;}
      if(mbrNelpBor == PxWYrdRkgb){QYWNStGJCB = true;}
      else if(PxWYrdRkgb == mbrNelpBor){jxWlyHkSGm = true;}
      if(RVzNLXhbxb == PRoZKwaKsH){kyaplzrUDr = true;}
      else if(PRoZKwaKsH == RVzNLXhbxb){wpPyGVQLjO = true;}
      if(bwAOdnLgaw == MAtwNtphMt){zyfAxIQOpt = true;}
      if(SDRnDlDNrf == ozodthGKWU){EtCSDlPcjo = true;}
      if(ufUrYTIgxL == yQVoxsjDpI){nGbctfFJmh = true;}
      while(MAtwNtphMt == bwAOdnLgaw){bEUBHqBKCI = true;}
      while(ozodthGKWU == ozodthGKWU){GCWBgFjoJQ = true;}
      while(yQVoxsjDpI == yQVoxsjDpI){xwkynDcNTo = true;}
      if(KthLyODZKx == true){KthLyODZKx = false;}
      if(mjYmlQbLfc == true){mjYmlQbLfc = false;}
      if(oQnXIwdEzU == true){oQnXIwdEzU = false;}
      if(KmqDjtQdee == true){KmqDjtQdee = false;}
      if(efzZhOqiCg == true){efzZhOqiCg = false;}
      if(QYWNStGJCB == true){QYWNStGJCB = false;}
      if(kyaplzrUDr == true){kyaplzrUDr = false;}
      if(zyfAxIQOpt == true){zyfAxIQOpt = false;}
      if(EtCSDlPcjo == true){EtCSDlPcjo = false;}
      if(nGbctfFJmh == true){nGbctfFJmh = false;}
      if(VVfKgSrWPJ == true){VVfKgSrWPJ = false;}
      if(drTHxpwHlA == true){drTHxpwHlA = false;}
      if(jOkNEsVCGQ == true){jOkNEsVCGQ = false;}
      if(DHaHXhOqlk == true){DHaHXhOqlk = false;}
      if(ssMZLumTfE == true){ssMZLumTfE = false;}
      if(jxWlyHkSGm == true){jxWlyHkSGm = false;}
      if(wpPyGVQLjO == true){wpPyGVQLjO = false;}
      if(bEUBHqBKCI == true){bEUBHqBKCI = false;}
      if(GCWBgFjoJQ == true){GCWBgFjoJQ = false;}
      if(xwkynDcNTo == true){xwkynDcNTo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKJJXUDSYL
{ 
  void loKRKIaHmn()
  { 
      bool DOwVjUrhfK = false;
      bool NVceSYaOOt = false;
      bool hoistoUSEB = false;
      bool TwDHUVLJdL = false;
      bool taUAHqpJhp = false;
      bool deTPdNfCau = false;
      bool zZcdqRRVJw = false;
      bool NQkCzGUilD = false;
      bool yKjOWnbmcH = false;
      bool pIiiLUxpIp = false;
      bool YUAkcMsRQW = false;
      bool rwQWxnoOHC = false;
      bool oerCGEhCpd = false;
      bool IeZuedKylJ = false;
      bool tKWGOsqLkX = false;
      bool eihGBtbyeX = false;
      bool eqalNNWVrS = false;
      bool dpcxIdHlmN = false;
      bool MWQSyZwTtj = false;
      bool CLTOeDjjrA = false;
      string gVWGltjHWe;
      string SZOMhpwIGl;
      string tDyzLziVfK;
      string hWgmitJkTe;
      string tKcDFuPxJd;
      string MFNxPcXXum;
      string LOaMwusbcn;
      string fKobqiatsQ;
      string ikMCxcJjWF;
      string WlpfTfjPHK;
      string CmTUxBPlFf;
      string CcddDZBXOT;
      string lIEWRsUIHK;
      string zKmiOwQqEu;
      string MXdqDsIMcs;
      string dLBmXsixDD;
      string gGdugqptPH;
      string IJTSHNeNTY;
      string kIfOfmJAKV;
      string MTnBOFtiJL;
      if(gVWGltjHWe == CmTUxBPlFf){DOwVjUrhfK = true;}
      else if(CmTUxBPlFf == gVWGltjHWe){YUAkcMsRQW = true;}
      if(SZOMhpwIGl == CcddDZBXOT){NVceSYaOOt = true;}
      else if(CcddDZBXOT == SZOMhpwIGl){rwQWxnoOHC = true;}
      if(tDyzLziVfK == lIEWRsUIHK){hoistoUSEB = true;}
      else if(lIEWRsUIHK == tDyzLziVfK){oerCGEhCpd = true;}
      if(hWgmitJkTe == zKmiOwQqEu){TwDHUVLJdL = true;}
      else if(zKmiOwQqEu == hWgmitJkTe){IeZuedKylJ = true;}
      if(tKcDFuPxJd == MXdqDsIMcs){taUAHqpJhp = true;}
      else if(MXdqDsIMcs == tKcDFuPxJd){tKWGOsqLkX = true;}
      if(MFNxPcXXum == dLBmXsixDD){deTPdNfCau = true;}
      else if(dLBmXsixDD == MFNxPcXXum){eihGBtbyeX = true;}
      if(LOaMwusbcn == gGdugqptPH){zZcdqRRVJw = true;}
      else if(gGdugqptPH == LOaMwusbcn){eqalNNWVrS = true;}
      if(fKobqiatsQ == IJTSHNeNTY){NQkCzGUilD = true;}
      if(ikMCxcJjWF == kIfOfmJAKV){yKjOWnbmcH = true;}
      if(WlpfTfjPHK == MTnBOFtiJL){pIiiLUxpIp = true;}
      while(IJTSHNeNTY == fKobqiatsQ){dpcxIdHlmN = true;}
      while(kIfOfmJAKV == kIfOfmJAKV){MWQSyZwTtj = true;}
      while(MTnBOFtiJL == MTnBOFtiJL){CLTOeDjjrA = true;}
      if(DOwVjUrhfK == true){DOwVjUrhfK = false;}
      if(NVceSYaOOt == true){NVceSYaOOt = false;}
      if(hoistoUSEB == true){hoistoUSEB = false;}
      if(TwDHUVLJdL == true){TwDHUVLJdL = false;}
      if(taUAHqpJhp == true){taUAHqpJhp = false;}
      if(deTPdNfCau == true){deTPdNfCau = false;}
      if(zZcdqRRVJw == true){zZcdqRRVJw = false;}
      if(NQkCzGUilD == true){NQkCzGUilD = false;}
      if(yKjOWnbmcH == true){yKjOWnbmcH = false;}
      if(pIiiLUxpIp == true){pIiiLUxpIp = false;}
      if(YUAkcMsRQW == true){YUAkcMsRQW = false;}
      if(rwQWxnoOHC == true){rwQWxnoOHC = false;}
      if(oerCGEhCpd == true){oerCGEhCpd = false;}
      if(IeZuedKylJ == true){IeZuedKylJ = false;}
      if(tKWGOsqLkX == true){tKWGOsqLkX = false;}
      if(eihGBtbyeX == true){eihGBtbyeX = false;}
      if(eqalNNWVrS == true){eqalNNWVrS = false;}
      if(dpcxIdHlmN == true){dpcxIdHlmN = false;}
      if(MWQSyZwTtj == true){MWQSyZwTtj = false;}
      if(CLTOeDjjrA == true){CLTOeDjjrA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class POCXGVMDUL
{ 
  void DKWaClANVA()
  { 
      bool XfreWXHiSq = false;
      bool xogRNZoUGZ = false;
      bool NMYnPJuKGn = false;
      bool sYwIdSESML = false;
      bool siPioCUywQ = false;
      bool oxcJKLHDON = false;
      bool bxcexYsYnu = false;
      bool VVHugexozN = false;
      bool oxNozuulxS = false;
      bool LAEziwGkkP = false;
      bool IwJBuSphcf = false;
      bool NRDBXeimeB = false;
      bool cGaVjURIMj = false;
      bool YMDiEsmMtf = false;
      bool FNIREsxCaE = false;
      bool MSFjlCUnRa = false;
      bool AhVsGBNTxe = false;
      bool qWszuPyJQp = false;
      bool XOgHWFGTwC = false;
      bool XytTeXqPKC = false;
      string CiikAixjqY;
      string fFdasmlyfD;
      string RjfnlBpYij;
      string CyoTDmCkGC;
      string FUwqVFYZxY;
      string lOCHCSDuzy;
      string rYBHWgQJXF;
      string jArdyxmnSg;
      string cQbKynwhQk;
      string iHkHKfSoUn;
      string nOBqnkWYIF;
      string ePcSVawpJi;
      string jhrmWcOjSS;
      string dyTdrNPkVM;
      string QXZLFTdSli;
      string icfkDFVNUL;
      string VmFoafuyaH;
      string LLUwRMIggC;
      string ywxjiBShZl;
      string rBQKpdSjjY;
      if(CiikAixjqY == nOBqnkWYIF){XfreWXHiSq = true;}
      else if(nOBqnkWYIF == CiikAixjqY){IwJBuSphcf = true;}
      if(fFdasmlyfD == ePcSVawpJi){xogRNZoUGZ = true;}
      else if(ePcSVawpJi == fFdasmlyfD){NRDBXeimeB = true;}
      if(RjfnlBpYij == jhrmWcOjSS){NMYnPJuKGn = true;}
      else if(jhrmWcOjSS == RjfnlBpYij){cGaVjURIMj = true;}
      if(CyoTDmCkGC == dyTdrNPkVM){sYwIdSESML = true;}
      else if(dyTdrNPkVM == CyoTDmCkGC){YMDiEsmMtf = true;}
      if(FUwqVFYZxY == QXZLFTdSli){siPioCUywQ = true;}
      else if(QXZLFTdSli == FUwqVFYZxY){FNIREsxCaE = true;}
      if(lOCHCSDuzy == icfkDFVNUL){oxcJKLHDON = true;}
      else if(icfkDFVNUL == lOCHCSDuzy){MSFjlCUnRa = true;}
      if(rYBHWgQJXF == VmFoafuyaH){bxcexYsYnu = true;}
      else if(VmFoafuyaH == rYBHWgQJXF){AhVsGBNTxe = true;}
      if(jArdyxmnSg == LLUwRMIggC){VVHugexozN = true;}
      if(cQbKynwhQk == ywxjiBShZl){oxNozuulxS = true;}
      if(iHkHKfSoUn == rBQKpdSjjY){LAEziwGkkP = true;}
      while(LLUwRMIggC == jArdyxmnSg){qWszuPyJQp = true;}
      while(ywxjiBShZl == ywxjiBShZl){XOgHWFGTwC = true;}
      while(rBQKpdSjjY == rBQKpdSjjY){XytTeXqPKC = true;}
      if(XfreWXHiSq == true){XfreWXHiSq = false;}
      if(xogRNZoUGZ == true){xogRNZoUGZ = false;}
      if(NMYnPJuKGn == true){NMYnPJuKGn = false;}
      if(sYwIdSESML == true){sYwIdSESML = false;}
      if(siPioCUywQ == true){siPioCUywQ = false;}
      if(oxcJKLHDON == true){oxcJKLHDON = false;}
      if(bxcexYsYnu == true){bxcexYsYnu = false;}
      if(VVHugexozN == true){VVHugexozN = false;}
      if(oxNozuulxS == true){oxNozuulxS = false;}
      if(LAEziwGkkP == true){LAEziwGkkP = false;}
      if(IwJBuSphcf == true){IwJBuSphcf = false;}
      if(NRDBXeimeB == true){NRDBXeimeB = false;}
      if(cGaVjURIMj == true){cGaVjURIMj = false;}
      if(YMDiEsmMtf == true){YMDiEsmMtf = false;}
      if(FNIREsxCaE == true){FNIREsxCaE = false;}
      if(MSFjlCUnRa == true){MSFjlCUnRa = false;}
      if(AhVsGBNTxe == true){AhVsGBNTxe = false;}
      if(qWszuPyJQp == true){qWszuPyJQp = false;}
      if(XOgHWFGTwC == true){XOgHWFGTwC = false;}
      if(XytTeXqPKC == true){XytTeXqPKC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AHKFYQDQLH
{ 
  void AGpwsCxkGU()
  { 
      bool NsBJgTLkyS = false;
      bool HxiaXOdPer = false;
      bool iPuQNHooGa = false;
      bool kxILrUJqJm = false;
      bool mpkkmcRZdr = false;
      bool mtHieyxjwZ = false;
      bool eWdXgJoWhD = false;
      bool ElFrFseJdj = false;
      bool oOLOmppYft = false;
      bool WYujHQLNDc = false;
      bool mtqZmBoPdl = false;
      bool SnGLjQKPjq = false;
      bool TQqnffqVjn = false;
      bool gQGBxuWkal = false;
      bool BZtsaiSizq = false;
      bool FwdMIVDDsG = false;
      bool JSeoFChEOo = false;
      bool sZnxotVxMx = false;
      bool NHVshjlssa = false;
      bool qTqUbhuEnX = false;
      string hdlOldxtlT;
      string zMIYYYlgkk;
      string efAgaupqiO;
      string DibrMRMAlw;
      string mtOuplBVID;
      string jadAeBdFmq;
      string mFLXQQjQLH;
      string MkuoykQEpn;
      string tUieebFaMK;
      string mGMuIgiqeY;
      string BkKBqyfnCs;
      string kZPzxSWfsn;
      string LIDATFYAgQ;
      string CZZQmIKhnf;
      string wQYSZNqNyo;
      string JDypNrhJgl;
      string ZfGlqKzyLn;
      string IoqMrujjaG;
      string NKBqGzbjDt;
      string aAACGQJlbO;
      if(hdlOldxtlT == BkKBqyfnCs){NsBJgTLkyS = true;}
      else if(BkKBqyfnCs == hdlOldxtlT){mtqZmBoPdl = true;}
      if(zMIYYYlgkk == kZPzxSWfsn){HxiaXOdPer = true;}
      else if(kZPzxSWfsn == zMIYYYlgkk){SnGLjQKPjq = true;}
      if(efAgaupqiO == LIDATFYAgQ){iPuQNHooGa = true;}
      else if(LIDATFYAgQ == efAgaupqiO){TQqnffqVjn = true;}
      if(DibrMRMAlw == CZZQmIKhnf){kxILrUJqJm = true;}
      else if(CZZQmIKhnf == DibrMRMAlw){gQGBxuWkal = true;}
      if(mtOuplBVID == wQYSZNqNyo){mpkkmcRZdr = true;}
      else if(wQYSZNqNyo == mtOuplBVID){BZtsaiSizq = true;}
      if(jadAeBdFmq == JDypNrhJgl){mtHieyxjwZ = true;}
      else if(JDypNrhJgl == jadAeBdFmq){FwdMIVDDsG = true;}
      if(mFLXQQjQLH == ZfGlqKzyLn){eWdXgJoWhD = true;}
      else if(ZfGlqKzyLn == mFLXQQjQLH){JSeoFChEOo = true;}
      if(MkuoykQEpn == IoqMrujjaG){ElFrFseJdj = true;}
      if(tUieebFaMK == NKBqGzbjDt){oOLOmppYft = true;}
      if(mGMuIgiqeY == aAACGQJlbO){WYujHQLNDc = true;}
      while(IoqMrujjaG == MkuoykQEpn){sZnxotVxMx = true;}
      while(NKBqGzbjDt == NKBqGzbjDt){NHVshjlssa = true;}
      while(aAACGQJlbO == aAACGQJlbO){qTqUbhuEnX = true;}
      if(NsBJgTLkyS == true){NsBJgTLkyS = false;}
      if(HxiaXOdPer == true){HxiaXOdPer = false;}
      if(iPuQNHooGa == true){iPuQNHooGa = false;}
      if(kxILrUJqJm == true){kxILrUJqJm = false;}
      if(mpkkmcRZdr == true){mpkkmcRZdr = false;}
      if(mtHieyxjwZ == true){mtHieyxjwZ = false;}
      if(eWdXgJoWhD == true){eWdXgJoWhD = false;}
      if(ElFrFseJdj == true){ElFrFseJdj = false;}
      if(oOLOmppYft == true){oOLOmppYft = false;}
      if(WYujHQLNDc == true){WYujHQLNDc = false;}
      if(mtqZmBoPdl == true){mtqZmBoPdl = false;}
      if(SnGLjQKPjq == true){SnGLjQKPjq = false;}
      if(TQqnffqVjn == true){TQqnffqVjn = false;}
      if(gQGBxuWkal == true){gQGBxuWkal = false;}
      if(BZtsaiSizq == true){BZtsaiSizq = false;}
      if(FwdMIVDDsG == true){FwdMIVDDsG = false;}
      if(JSeoFChEOo == true){JSeoFChEOo = false;}
      if(sZnxotVxMx == true){sZnxotVxMx = false;}
      if(NHVshjlssa == true){NHVshjlssa = false;}
      if(qTqUbhuEnX == true){qTqUbhuEnX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YFYQPVGGEH
{ 
  void yEBBswmZtq()
  { 
      bool gTXeKoWeDY = false;
      bool CaHJFAEURB = false;
      bool yxyOYJJSZB = false;
      bool smjQYaKaVm = false;
      bool PHVjgGaull = false;
      bool JqEsWiVIFB = false;
      bool eDEBeOqqke = false;
      bool ocyelpbNgR = false;
      bool hOfnrCiqto = false;
      bool EBUUILCTER = false;
      bool PjKHwfrZGf = false;
      bool HIbmSQWQJc = false;
      bool fAwuanIdVa = false;
      bool mHIOCyDYqL = false;
      bool JIjNhuYgCr = false;
      bool nlKblOmOfI = false;
      bool XODfsAzNkU = false;
      bool MyYxTXQiNe = false;
      bool OaadlBwgcm = false;
      bool KnsimtEDUg = false;
      string YisTqAZAyP;
      string bMLuGxMPat;
      string LJUKqkOtfM;
      string CErFifEsoN;
      string WFJUXHayzP;
      string FbAzNOOhcG;
      string lfTlNXTFMa;
      string sTaMXFAzmi;
      string JPtPGZDsqT;
      string RWPhaplWHz;
      string mUlYWlBnbI;
      string OOttwWkDfn;
      string UaOrIWDrkg;
      string TcrmwodVrT;
      string XOQiFDbVlE;
      string EhpTeLGtPA;
      string hJCtnkVHyH;
      string sPKLPFJelF;
      string uhFgbllYIj;
      string hiFrlNMWuU;
      if(YisTqAZAyP == mUlYWlBnbI){gTXeKoWeDY = true;}
      else if(mUlYWlBnbI == YisTqAZAyP){PjKHwfrZGf = true;}
      if(bMLuGxMPat == OOttwWkDfn){CaHJFAEURB = true;}
      else if(OOttwWkDfn == bMLuGxMPat){HIbmSQWQJc = true;}
      if(LJUKqkOtfM == UaOrIWDrkg){yxyOYJJSZB = true;}
      else if(UaOrIWDrkg == LJUKqkOtfM){fAwuanIdVa = true;}
      if(CErFifEsoN == TcrmwodVrT){smjQYaKaVm = true;}
      else if(TcrmwodVrT == CErFifEsoN){mHIOCyDYqL = true;}
      if(WFJUXHayzP == XOQiFDbVlE){PHVjgGaull = true;}
      else if(XOQiFDbVlE == WFJUXHayzP){JIjNhuYgCr = true;}
      if(FbAzNOOhcG == EhpTeLGtPA){JqEsWiVIFB = true;}
      else if(EhpTeLGtPA == FbAzNOOhcG){nlKblOmOfI = true;}
      if(lfTlNXTFMa == hJCtnkVHyH){eDEBeOqqke = true;}
      else if(hJCtnkVHyH == lfTlNXTFMa){XODfsAzNkU = true;}
      if(sTaMXFAzmi == sPKLPFJelF){ocyelpbNgR = true;}
      if(JPtPGZDsqT == uhFgbllYIj){hOfnrCiqto = true;}
      if(RWPhaplWHz == hiFrlNMWuU){EBUUILCTER = true;}
      while(sPKLPFJelF == sTaMXFAzmi){MyYxTXQiNe = true;}
      while(uhFgbllYIj == uhFgbllYIj){OaadlBwgcm = true;}
      while(hiFrlNMWuU == hiFrlNMWuU){KnsimtEDUg = true;}
      if(gTXeKoWeDY == true){gTXeKoWeDY = false;}
      if(CaHJFAEURB == true){CaHJFAEURB = false;}
      if(yxyOYJJSZB == true){yxyOYJJSZB = false;}
      if(smjQYaKaVm == true){smjQYaKaVm = false;}
      if(PHVjgGaull == true){PHVjgGaull = false;}
      if(JqEsWiVIFB == true){JqEsWiVIFB = false;}
      if(eDEBeOqqke == true){eDEBeOqqke = false;}
      if(ocyelpbNgR == true){ocyelpbNgR = false;}
      if(hOfnrCiqto == true){hOfnrCiqto = false;}
      if(EBUUILCTER == true){EBUUILCTER = false;}
      if(PjKHwfrZGf == true){PjKHwfrZGf = false;}
      if(HIbmSQWQJc == true){HIbmSQWQJc = false;}
      if(fAwuanIdVa == true){fAwuanIdVa = false;}
      if(mHIOCyDYqL == true){mHIOCyDYqL = false;}
      if(JIjNhuYgCr == true){JIjNhuYgCr = false;}
      if(nlKblOmOfI == true){nlKblOmOfI = false;}
      if(XODfsAzNkU == true){XODfsAzNkU = false;}
      if(MyYxTXQiNe == true){MyYxTXQiNe = false;}
      if(OaadlBwgcm == true){OaadlBwgcm = false;}
      if(KnsimtEDUg == true){KnsimtEDUg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQTIXBQBES
{ 
  void yMzGFnjaoc()
  { 
      bool abiqojtfSj = false;
      bool qzPxJcAsDa = false;
      bool GykhIQMJwz = false;
      bool RQOTZuHyyH = false;
      bool IjJfyfBOXQ = false;
      bool AEhWucpBhX = false;
      bool WkiTRZkuWO = false;
      bool VBuwRWnFic = false;
      bool PylfzNirXx = false;
      bool EGQZjXApNX = false;
      bool uGqItyJlEX = false;
      bool nkRFIYyCTE = false;
      bool qrWZKOkULt = false;
      bool WyqKgJHckB = false;
      bool EwnAISnLQL = false;
      bool YxVIgDiQxf = false;
      bool NnaKBpsGXz = false;
      bool RVRSAuEWRq = false;
      bool ZYDzUYbhdd = false;
      bool ZpeFmPUcyS = false;
      string yCJgGVzaxA;
      string EpgkoXyayr;
      string baUdKezyYL;
      string CjZxFJblpe;
      string utMKQukNic;
      string exLtBWhfWb;
      string WABkxUPjee;
      string wMjSxhNJNO;
      string tkPufEYeui;
      string auOOIuraMw;
      string eBhDgSMrxT;
      string JYSHhkkGEr;
      string wknwEAyVKB;
      string olxQjrDLON;
      string rfhbZCcGfW;
      string JlWTAtMlzg;
      string UphudWaBXo;
      string hZqpAPDMWB;
      string WqpnrDPcQo;
      string fQMhsBylxC;
      if(yCJgGVzaxA == eBhDgSMrxT){abiqojtfSj = true;}
      else if(eBhDgSMrxT == yCJgGVzaxA){uGqItyJlEX = true;}
      if(EpgkoXyayr == JYSHhkkGEr){qzPxJcAsDa = true;}
      else if(JYSHhkkGEr == EpgkoXyayr){nkRFIYyCTE = true;}
      if(baUdKezyYL == wknwEAyVKB){GykhIQMJwz = true;}
      else if(wknwEAyVKB == baUdKezyYL){qrWZKOkULt = true;}
      if(CjZxFJblpe == olxQjrDLON){RQOTZuHyyH = true;}
      else if(olxQjrDLON == CjZxFJblpe){WyqKgJHckB = true;}
      if(utMKQukNic == rfhbZCcGfW){IjJfyfBOXQ = true;}
      else if(rfhbZCcGfW == utMKQukNic){EwnAISnLQL = true;}
      if(exLtBWhfWb == JlWTAtMlzg){AEhWucpBhX = true;}
      else if(JlWTAtMlzg == exLtBWhfWb){YxVIgDiQxf = true;}
      if(WABkxUPjee == UphudWaBXo){WkiTRZkuWO = true;}
      else if(UphudWaBXo == WABkxUPjee){NnaKBpsGXz = true;}
      if(wMjSxhNJNO == hZqpAPDMWB){VBuwRWnFic = true;}
      if(tkPufEYeui == WqpnrDPcQo){PylfzNirXx = true;}
      if(auOOIuraMw == fQMhsBylxC){EGQZjXApNX = true;}
      while(hZqpAPDMWB == wMjSxhNJNO){RVRSAuEWRq = true;}
      while(WqpnrDPcQo == WqpnrDPcQo){ZYDzUYbhdd = true;}
      while(fQMhsBylxC == fQMhsBylxC){ZpeFmPUcyS = true;}
      if(abiqojtfSj == true){abiqojtfSj = false;}
      if(qzPxJcAsDa == true){qzPxJcAsDa = false;}
      if(GykhIQMJwz == true){GykhIQMJwz = false;}
      if(RQOTZuHyyH == true){RQOTZuHyyH = false;}
      if(IjJfyfBOXQ == true){IjJfyfBOXQ = false;}
      if(AEhWucpBhX == true){AEhWucpBhX = false;}
      if(WkiTRZkuWO == true){WkiTRZkuWO = false;}
      if(VBuwRWnFic == true){VBuwRWnFic = false;}
      if(PylfzNirXx == true){PylfzNirXx = false;}
      if(EGQZjXApNX == true){EGQZjXApNX = false;}
      if(uGqItyJlEX == true){uGqItyJlEX = false;}
      if(nkRFIYyCTE == true){nkRFIYyCTE = false;}
      if(qrWZKOkULt == true){qrWZKOkULt = false;}
      if(WyqKgJHckB == true){WyqKgJHckB = false;}
      if(EwnAISnLQL == true){EwnAISnLQL = false;}
      if(YxVIgDiQxf == true){YxVIgDiQxf = false;}
      if(NnaKBpsGXz == true){NnaKBpsGXz = false;}
      if(RVRSAuEWRq == true){RVRSAuEWRq = false;}
      if(ZYDzUYbhdd == true){ZYDzUYbhdd = false;}
      if(ZpeFmPUcyS == true){ZpeFmPUcyS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLWAWWNLTG
{ 
  void rpoqRnsXNq()
  { 
      bool MztaIefAyr = false;
      bool yfZUTGIjNr = false;
      bool gqGQpOcJGL = false;
      bool PaOCeNmyAk = false;
      bool nMUCMJubqX = false;
      bool hDKcDUsdkt = false;
      bool CWslbWRXoG = false;
      bool TKjcETWEDf = false;
      bool SAShdLQkzJ = false;
      bool UJNGhRTiZo = false;
      bool rXmjEXTgYi = false;
      bool ynZEaBDKIP = false;
      bool GfYelKwctl = false;
      bool AndNnuNidF = false;
      bool riMPLfiIff = false;
      bool OIZKiLzHxs = false;
      bool aplliJKLPe = false;
      bool nUgCWWTJSG = false;
      bool bmxOXqNSec = false;
      bool wFkjdBxZfB = false;
      string jVwDkSwpXr;
      string QKZyuQGoQO;
      string AzsdKLicoI;
      string axHmIdKyRy;
      string GPHuDCVUrB;
      string ylQGTkbRrZ;
      string iSBPQTCloQ;
      string GHXSHjqyaI;
      string oOkmJnfBSX;
      string BrFqOmOrdj;
      string ziebupOxyi;
      string sdqjkUhNFc;
      string mBTRONCfDU;
      string VzTpIFiIrT;
      string ZhCieWAUGt;
      string EBlBwxPNMg;
      string nhtdNtKAae;
      string kYUlDEzjmr;
      string MgZJPUMStK;
      string oVwKeqnXVj;
      if(jVwDkSwpXr == ziebupOxyi){MztaIefAyr = true;}
      else if(ziebupOxyi == jVwDkSwpXr){rXmjEXTgYi = true;}
      if(QKZyuQGoQO == sdqjkUhNFc){yfZUTGIjNr = true;}
      else if(sdqjkUhNFc == QKZyuQGoQO){ynZEaBDKIP = true;}
      if(AzsdKLicoI == mBTRONCfDU){gqGQpOcJGL = true;}
      else if(mBTRONCfDU == AzsdKLicoI){GfYelKwctl = true;}
      if(axHmIdKyRy == VzTpIFiIrT){PaOCeNmyAk = true;}
      else if(VzTpIFiIrT == axHmIdKyRy){AndNnuNidF = true;}
      if(GPHuDCVUrB == ZhCieWAUGt){nMUCMJubqX = true;}
      else if(ZhCieWAUGt == GPHuDCVUrB){riMPLfiIff = true;}
      if(ylQGTkbRrZ == EBlBwxPNMg){hDKcDUsdkt = true;}
      else if(EBlBwxPNMg == ylQGTkbRrZ){OIZKiLzHxs = true;}
      if(iSBPQTCloQ == nhtdNtKAae){CWslbWRXoG = true;}
      else if(nhtdNtKAae == iSBPQTCloQ){aplliJKLPe = true;}
      if(GHXSHjqyaI == kYUlDEzjmr){TKjcETWEDf = true;}
      if(oOkmJnfBSX == MgZJPUMStK){SAShdLQkzJ = true;}
      if(BrFqOmOrdj == oVwKeqnXVj){UJNGhRTiZo = true;}
      while(kYUlDEzjmr == GHXSHjqyaI){nUgCWWTJSG = true;}
      while(MgZJPUMStK == MgZJPUMStK){bmxOXqNSec = true;}
      while(oVwKeqnXVj == oVwKeqnXVj){wFkjdBxZfB = true;}
      if(MztaIefAyr == true){MztaIefAyr = false;}
      if(yfZUTGIjNr == true){yfZUTGIjNr = false;}
      if(gqGQpOcJGL == true){gqGQpOcJGL = false;}
      if(PaOCeNmyAk == true){PaOCeNmyAk = false;}
      if(nMUCMJubqX == true){nMUCMJubqX = false;}
      if(hDKcDUsdkt == true){hDKcDUsdkt = false;}
      if(CWslbWRXoG == true){CWslbWRXoG = false;}
      if(TKjcETWEDf == true){TKjcETWEDf = false;}
      if(SAShdLQkzJ == true){SAShdLQkzJ = false;}
      if(UJNGhRTiZo == true){UJNGhRTiZo = false;}
      if(rXmjEXTgYi == true){rXmjEXTgYi = false;}
      if(ynZEaBDKIP == true){ynZEaBDKIP = false;}
      if(GfYelKwctl == true){GfYelKwctl = false;}
      if(AndNnuNidF == true){AndNnuNidF = false;}
      if(riMPLfiIff == true){riMPLfiIff = false;}
      if(OIZKiLzHxs == true){OIZKiLzHxs = false;}
      if(aplliJKLPe == true){aplliJKLPe = false;}
      if(nUgCWWTJSG == true){nUgCWWTJSG = false;}
      if(bmxOXqNSec == true){bmxOXqNSec = false;}
      if(wFkjdBxZfB == true){wFkjdBxZfB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROBPPJOIGC
{ 
  void JgBPpStTBP()
  { 
      bool PqHmaiTxuj = false;
      bool eCnpjEotfw = false;
      bool bammDAXdNu = false;
      bool DNyFCwndpx = false;
      bool YAFLIjqycS = false;
      bool iftHnoDTia = false;
      bool LojAfQEhnm = false;
      bool QLEhXbUaeT = false;
      bool IZBtLXTpRM = false;
      bool rUtPliQFfq = false;
      bool eIKoCXaLjL = false;
      bool UboPRknonH = false;
      bool xNQatuRown = false;
      bool LPumnzPLqn = false;
      bool wHGFrPedxA = false;
      bool taQXtQritG = false;
      bool GlPuAEgBaS = false;
      bool VbyzKpHLhe = false;
      bool QmqwskyWsW = false;
      bool GfQjhKrLEm = false;
      string fgwaniLowR;
      string pErEqqmoIX;
      string UrPKuQAfre;
      string nCBOoyGthJ;
      string mgNoSubmMV;
      string YIgZenQkfW;
      string hewRcmCdOr;
      string jsGyjmdaqz;
      string oNTVFfVbjB;
      string hUOLaHkuLf;
      string syXUlfBioq;
      string JptfgULZLx;
      string RatNKOduWc;
      string ChOKFqoyjZ;
      string dllrqqahdG;
      string wKjNOSEJJX;
      string BGLMnaaiZp;
      string eMplSenBVS;
      string nwQQgryAwm;
      string leoMXXaZDQ;
      if(fgwaniLowR == syXUlfBioq){PqHmaiTxuj = true;}
      else if(syXUlfBioq == fgwaniLowR){eIKoCXaLjL = true;}
      if(pErEqqmoIX == JptfgULZLx){eCnpjEotfw = true;}
      else if(JptfgULZLx == pErEqqmoIX){UboPRknonH = true;}
      if(UrPKuQAfre == RatNKOduWc){bammDAXdNu = true;}
      else if(RatNKOduWc == UrPKuQAfre){xNQatuRown = true;}
      if(nCBOoyGthJ == ChOKFqoyjZ){DNyFCwndpx = true;}
      else if(ChOKFqoyjZ == nCBOoyGthJ){LPumnzPLqn = true;}
      if(mgNoSubmMV == dllrqqahdG){YAFLIjqycS = true;}
      else if(dllrqqahdG == mgNoSubmMV){wHGFrPedxA = true;}
      if(YIgZenQkfW == wKjNOSEJJX){iftHnoDTia = true;}
      else if(wKjNOSEJJX == YIgZenQkfW){taQXtQritG = true;}
      if(hewRcmCdOr == BGLMnaaiZp){LojAfQEhnm = true;}
      else if(BGLMnaaiZp == hewRcmCdOr){GlPuAEgBaS = true;}
      if(jsGyjmdaqz == eMplSenBVS){QLEhXbUaeT = true;}
      if(oNTVFfVbjB == nwQQgryAwm){IZBtLXTpRM = true;}
      if(hUOLaHkuLf == leoMXXaZDQ){rUtPliQFfq = true;}
      while(eMplSenBVS == jsGyjmdaqz){VbyzKpHLhe = true;}
      while(nwQQgryAwm == nwQQgryAwm){QmqwskyWsW = true;}
      while(leoMXXaZDQ == leoMXXaZDQ){GfQjhKrLEm = true;}
      if(PqHmaiTxuj == true){PqHmaiTxuj = false;}
      if(eCnpjEotfw == true){eCnpjEotfw = false;}
      if(bammDAXdNu == true){bammDAXdNu = false;}
      if(DNyFCwndpx == true){DNyFCwndpx = false;}
      if(YAFLIjqycS == true){YAFLIjqycS = false;}
      if(iftHnoDTia == true){iftHnoDTia = false;}
      if(LojAfQEhnm == true){LojAfQEhnm = false;}
      if(QLEhXbUaeT == true){QLEhXbUaeT = false;}
      if(IZBtLXTpRM == true){IZBtLXTpRM = false;}
      if(rUtPliQFfq == true){rUtPliQFfq = false;}
      if(eIKoCXaLjL == true){eIKoCXaLjL = false;}
      if(UboPRknonH == true){UboPRknonH = false;}
      if(xNQatuRown == true){xNQatuRown = false;}
      if(LPumnzPLqn == true){LPumnzPLqn = false;}
      if(wHGFrPedxA == true){wHGFrPedxA = false;}
      if(taQXtQritG == true){taQXtQritG = false;}
      if(GlPuAEgBaS == true){GlPuAEgBaS = false;}
      if(VbyzKpHLhe == true){VbyzKpHLhe = false;}
      if(QmqwskyWsW == true){QmqwskyWsW = false;}
      if(GfQjhKrLEm == true){GfQjhKrLEm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWRNZYZUQF
{ 
  void XVjGVLwest()
  { 
      bool PRUaVtCyle = false;
      bool kOwOwOEAPz = false;
      bool ohiJVsirwQ = false;
      bool MrNjFAKewU = false;
      bool pQxNaLHmIN = false;
      bool FrDIthhKEc = false;
      bool KKCURrALIw = false;
      bool EZDuJYkUhJ = false;
      bool kwihKUoEoX = false;
      bool RzZTJeNbui = false;
      bool KudMIfnHzV = false;
      bool wNctqObTJx = false;
      bool CwWjeEzjld = false;
      bool KIZzyoRVZe = false;
      bool ggFSaDWect = false;
      bool DsSxgOYshE = false;
      bool fDVULnndwB = false;
      bool wFtdQUqDJa = false;
      bool hTHqaQpbSj = false;
      bool QYnUzcKjHm = false;
      string CoExJZDjZF;
      string kaqSHrEJdu;
      string lFVTDjLHZr;
      string AAsgcMiODC;
      string ybAOmnRPhg;
      string FrgVuwSktZ;
      string OwKhEjgJpu;
      string IpFaxKFGfP;
      string SuYrlHSWlf;
      string syUdnCRSKC;
      string GHZmYPlGYk;
      string qMFdGTWRuw;
      string RJWJCKVbmt;
      string rmwdIKUlTW;
      string ULyBofspWT;
      string eAWNkwjQjN;
      string tKTerEQbVw;
      string ykxXbFLVTV;
      string ReFSOrPirL;
      string ZEBFbKrSIj;
      if(CoExJZDjZF == GHZmYPlGYk){PRUaVtCyle = true;}
      else if(GHZmYPlGYk == CoExJZDjZF){KudMIfnHzV = true;}
      if(kaqSHrEJdu == qMFdGTWRuw){kOwOwOEAPz = true;}
      else if(qMFdGTWRuw == kaqSHrEJdu){wNctqObTJx = true;}
      if(lFVTDjLHZr == RJWJCKVbmt){ohiJVsirwQ = true;}
      else if(RJWJCKVbmt == lFVTDjLHZr){CwWjeEzjld = true;}
      if(AAsgcMiODC == rmwdIKUlTW){MrNjFAKewU = true;}
      else if(rmwdIKUlTW == AAsgcMiODC){KIZzyoRVZe = true;}
      if(ybAOmnRPhg == ULyBofspWT){pQxNaLHmIN = true;}
      else if(ULyBofspWT == ybAOmnRPhg){ggFSaDWect = true;}
      if(FrgVuwSktZ == eAWNkwjQjN){FrDIthhKEc = true;}
      else if(eAWNkwjQjN == FrgVuwSktZ){DsSxgOYshE = true;}
      if(OwKhEjgJpu == tKTerEQbVw){KKCURrALIw = true;}
      else if(tKTerEQbVw == OwKhEjgJpu){fDVULnndwB = true;}
      if(IpFaxKFGfP == ykxXbFLVTV){EZDuJYkUhJ = true;}
      if(SuYrlHSWlf == ReFSOrPirL){kwihKUoEoX = true;}
      if(syUdnCRSKC == ZEBFbKrSIj){RzZTJeNbui = true;}
      while(ykxXbFLVTV == IpFaxKFGfP){wFtdQUqDJa = true;}
      while(ReFSOrPirL == ReFSOrPirL){hTHqaQpbSj = true;}
      while(ZEBFbKrSIj == ZEBFbKrSIj){QYnUzcKjHm = true;}
      if(PRUaVtCyle == true){PRUaVtCyle = false;}
      if(kOwOwOEAPz == true){kOwOwOEAPz = false;}
      if(ohiJVsirwQ == true){ohiJVsirwQ = false;}
      if(MrNjFAKewU == true){MrNjFAKewU = false;}
      if(pQxNaLHmIN == true){pQxNaLHmIN = false;}
      if(FrDIthhKEc == true){FrDIthhKEc = false;}
      if(KKCURrALIw == true){KKCURrALIw = false;}
      if(EZDuJYkUhJ == true){EZDuJYkUhJ = false;}
      if(kwihKUoEoX == true){kwihKUoEoX = false;}
      if(RzZTJeNbui == true){RzZTJeNbui = false;}
      if(KudMIfnHzV == true){KudMIfnHzV = false;}
      if(wNctqObTJx == true){wNctqObTJx = false;}
      if(CwWjeEzjld == true){CwWjeEzjld = false;}
      if(KIZzyoRVZe == true){KIZzyoRVZe = false;}
      if(ggFSaDWect == true){ggFSaDWect = false;}
      if(DsSxgOYshE == true){DsSxgOYshE = false;}
      if(fDVULnndwB == true){fDVULnndwB = false;}
      if(wFtdQUqDJa == true){wFtdQUqDJa = false;}
      if(hTHqaQpbSj == true){hTHqaQpbSj = false;}
      if(QYnUzcKjHm == true){QYnUzcKjHm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUCIKDZPKV
{ 
  void VMhQlfsxai()
  { 
      bool SLumPscVLY = false;
      bool nbfnAObtTi = false;
      bool JhqPrFIwcI = false;
      bool JeBofPQnYg = false;
      bool gfNjjMuiAW = false;
      bool jRlSokUfuK = false;
      bool kgrCOIZpHk = false;
      bool xnVmBdTHee = false;
      bool JYuGXqsizu = false;
      bool tkrNuznLUa = false;
      bool lEaPYuwyQL = false;
      bool QMAPALlkdW = false;
      bool OqpMpMwIrC = false;
      bool oImErExfgc = false;
      bool uuRnehkbMi = false;
      bool NCgxLuOOZM = false;
      bool znGOVHZuXu = false;
      bool NFDBbTYCgI = false;
      bool aTuInmborx = false;
      bool piGUcHnCRX = false;
      string VflCAcWfch;
      string UuNMnsclSH;
      string EYtOGAnCNR;
      string fnMoFZnOUL;
      string mSXUuwCZbU;
      string iQZPPxlXuz;
      string oTSKBgiXGN;
      string ENQGUkAYSK;
      string yNarhPOwZH;
      string nQSVWTANSO;
      string MdSNPVzSud;
      string xNEkBasZbl;
      string SlyyZntujA;
      string klFExTuMcM;
      string QuAuKZMhTu;
      string ZZkguZeTnb;
      string aDitsLHAmg;
      string fgxPVWlDnz;
      string bLanZKBYIX;
      string oaXAlMMGBz;
      if(VflCAcWfch == MdSNPVzSud){SLumPscVLY = true;}
      else if(MdSNPVzSud == VflCAcWfch){lEaPYuwyQL = true;}
      if(UuNMnsclSH == xNEkBasZbl){nbfnAObtTi = true;}
      else if(xNEkBasZbl == UuNMnsclSH){QMAPALlkdW = true;}
      if(EYtOGAnCNR == SlyyZntujA){JhqPrFIwcI = true;}
      else if(SlyyZntujA == EYtOGAnCNR){OqpMpMwIrC = true;}
      if(fnMoFZnOUL == klFExTuMcM){JeBofPQnYg = true;}
      else if(klFExTuMcM == fnMoFZnOUL){oImErExfgc = true;}
      if(mSXUuwCZbU == QuAuKZMhTu){gfNjjMuiAW = true;}
      else if(QuAuKZMhTu == mSXUuwCZbU){uuRnehkbMi = true;}
      if(iQZPPxlXuz == ZZkguZeTnb){jRlSokUfuK = true;}
      else if(ZZkguZeTnb == iQZPPxlXuz){NCgxLuOOZM = true;}
      if(oTSKBgiXGN == aDitsLHAmg){kgrCOIZpHk = true;}
      else if(aDitsLHAmg == oTSKBgiXGN){znGOVHZuXu = true;}
      if(ENQGUkAYSK == fgxPVWlDnz){xnVmBdTHee = true;}
      if(yNarhPOwZH == bLanZKBYIX){JYuGXqsizu = true;}
      if(nQSVWTANSO == oaXAlMMGBz){tkrNuznLUa = true;}
      while(fgxPVWlDnz == ENQGUkAYSK){NFDBbTYCgI = true;}
      while(bLanZKBYIX == bLanZKBYIX){aTuInmborx = true;}
      while(oaXAlMMGBz == oaXAlMMGBz){piGUcHnCRX = true;}
      if(SLumPscVLY == true){SLumPscVLY = false;}
      if(nbfnAObtTi == true){nbfnAObtTi = false;}
      if(JhqPrFIwcI == true){JhqPrFIwcI = false;}
      if(JeBofPQnYg == true){JeBofPQnYg = false;}
      if(gfNjjMuiAW == true){gfNjjMuiAW = false;}
      if(jRlSokUfuK == true){jRlSokUfuK = false;}
      if(kgrCOIZpHk == true){kgrCOIZpHk = false;}
      if(xnVmBdTHee == true){xnVmBdTHee = false;}
      if(JYuGXqsizu == true){JYuGXqsizu = false;}
      if(tkrNuznLUa == true){tkrNuznLUa = false;}
      if(lEaPYuwyQL == true){lEaPYuwyQL = false;}
      if(QMAPALlkdW == true){QMAPALlkdW = false;}
      if(OqpMpMwIrC == true){OqpMpMwIrC = false;}
      if(oImErExfgc == true){oImErExfgc = false;}
      if(uuRnehkbMi == true){uuRnehkbMi = false;}
      if(NCgxLuOOZM == true){NCgxLuOOZM = false;}
      if(znGOVHZuXu == true){znGOVHZuXu = false;}
      if(NFDBbTYCgI == true){NFDBbTYCgI = false;}
      if(aTuInmborx == true){aTuInmborx = false;}
      if(piGUcHnCRX == true){piGUcHnCRX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NIUAPDIBDN
{ 
  void NpbJxeyNHa()
  { 
      bool lebyxtiALW = false;
      bool tEFDRzftiq = false;
      bool QZAWbJXhzJ = false;
      bool NcNlUntWLJ = false;
      bool JEBiYkKrgx = false;
      bool hSOewMeEVn = false;
      bool VAABIQqTid = false;
      bool EIhZhLXRxq = false;
      bool yfACbtNhpI = false;
      bool JpBXmIEzZH = false;
      bool tqICrYkoxj = false;
      bool nMGeoozyZO = false;
      bool CIcaUOHKlY = false;
      bool HYqpxHWyJD = false;
      bool JYkFUwiVhx = false;
      bool IFZLEkNhhc = false;
      bool QZCXcOUQgh = false;
      bool SBoWEcXXGY = false;
      bool fkbnQByfkL = false;
      bool snPfliWMcF = false;
      string SpVzRnPNNU;
      string fENqOwYEWb;
      string TahWCRkmTT;
      string gmDdAUuqJV;
      string ScILfhMcmr;
      string qflNhqHzxz;
      string CbttnrBjpt;
      string AgtAIpRVpT;
      string FHAbcABowI;
      string MutJSphOXn;
      string fblrqJkkEq;
      string ZlJctubRQm;
      string pLnhhFmjgR;
      string IDyCmcUHkT;
      string OQkEialQPX;
      string OPxjxUnEKk;
      string VBDmiVnGoR;
      string ZUgxXZaiyH;
      string TVUJDrFNFS;
      string oQwzxNMyVM;
      if(SpVzRnPNNU == fblrqJkkEq){lebyxtiALW = true;}
      else if(fblrqJkkEq == SpVzRnPNNU){tqICrYkoxj = true;}
      if(fENqOwYEWb == ZlJctubRQm){tEFDRzftiq = true;}
      else if(ZlJctubRQm == fENqOwYEWb){nMGeoozyZO = true;}
      if(TahWCRkmTT == pLnhhFmjgR){QZAWbJXhzJ = true;}
      else if(pLnhhFmjgR == TahWCRkmTT){CIcaUOHKlY = true;}
      if(gmDdAUuqJV == IDyCmcUHkT){NcNlUntWLJ = true;}
      else if(IDyCmcUHkT == gmDdAUuqJV){HYqpxHWyJD = true;}
      if(ScILfhMcmr == OQkEialQPX){JEBiYkKrgx = true;}
      else if(OQkEialQPX == ScILfhMcmr){JYkFUwiVhx = true;}
      if(qflNhqHzxz == OPxjxUnEKk){hSOewMeEVn = true;}
      else if(OPxjxUnEKk == qflNhqHzxz){IFZLEkNhhc = true;}
      if(CbttnrBjpt == VBDmiVnGoR){VAABIQqTid = true;}
      else if(VBDmiVnGoR == CbttnrBjpt){QZCXcOUQgh = true;}
      if(AgtAIpRVpT == ZUgxXZaiyH){EIhZhLXRxq = true;}
      if(FHAbcABowI == TVUJDrFNFS){yfACbtNhpI = true;}
      if(MutJSphOXn == oQwzxNMyVM){JpBXmIEzZH = true;}
      while(ZUgxXZaiyH == AgtAIpRVpT){SBoWEcXXGY = true;}
      while(TVUJDrFNFS == TVUJDrFNFS){fkbnQByfkL = true;}
      while(oQwzxNMyVM == oQwzxNMyVM){snPfliWMcF = true;}
      if(lebyxtiALW == true){lebyxtiALW = false;}
      if(tEFDRzftiq == true){tEFDRzftiq = false;}
      if(QZAWbJXhzJ == true){QZAWbJXhzJ = false;}
      if(NcNlUntWLJ == true){NcNlUntWLJ = false;}
      if(JEBiYkKrgx == true){JEBiYkKrgx = false;}
      if(hSOewMeEVn == true){hSOewMeEVn = false;}
      if(VAABIQqTid == true){VAABIQqTid = false;}
      if(EIhZhLXRxq == true){EIhZhLXRxq = false;}
      if(yfACbtNhpI == true){yfACbtNhpI = false;}
      if(JpBXmIEzZH == true){JpBXmIEzZH = false;}
      if(tqICrYkoxj == true){tqICrYkoxj = false;}
      if(nMGeoozyZO == true){nMGeoozyZO = false;}
      if(CIcaUOHKlY == true){CIcaUOHKlY = false;}
      if(HYqpxHWyJD == true){HYqpxHWyJD = false;}
      if(JYkFUwiVhx == true){JYkFUwiVhx = false;}
      if(IFZLEkNhhc == true){IFZLEkNhhc = false;}
      if(QZCXcOUQgh == true){QZCXcOUQgh = false;}
      if(SBoWEcXXGY == true){SBoWEcXXGY = false;}
      if(fkbnQByfkL == true){fkbnQByfkL = false;}
      if(snPfliWMcF == true){snPfliWMcF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVMCAENHQF
{ 
  void QExRDTHqWu()
  { 
      bool NzieHDwIrr = false;
      bool UVQwJRyFEI = false;
      bool DXqpfcHUWh = false;
      bool hZbGkXNOLY = false;
      bool KHeKPUCqFX = false;
      bool RxfaIpIrze = false;
      bool wakKKusKLk = false;
      bool EjsfywsgaL = false;
      bool ZQPyPjsBxu = false;
      bool PUPgciVUzU = false;
      bool arfTTgDAbL = false;
      bool waRmFfLltZ = false;
      bool BqMQVjULDO = false;
      bool ZYgGjgjuei = false;
      bool fsYlynDbbx = false;
      bool XjZZSiePyj = false;
      bool MrxNkXtLDX = false;
      bool uPHLsHRaRg = false;
      bool gsjFppyGmA = false;
      bool CUwtVnwLAa = false;
      string dapGTruJid;
      string gJGyOFSuVQ;
      string lAHsqLEXht;
      string axByOlRODr;
      string FnbyYRxRhm;
      string WeYWAdSwPH;
      string mXaoCjIHjc;
      string mEqcLyYJUY;
      string NlpuWwXdyk;
      string TVzuFhMmwo;
      string JphFzSnwLB;
      string FJaptAgfRF;
      string LdIyJRFuXd;
      string lkNfPXDjwE;
      string IaSxfJtIBE;
      string AfVpcfgjwg;
      string NrYhOTutZW;
      string wwjNxjKLSz;
      string XwsTcGPXDj;
      string pTnOpPCkiM;
      if(dapGTruJid == JphFzSnwLB){NzieHDwIrr = true;}
      else if(JphFzSnwLB == dapGTruJid){arfTTgDAbL = true;}
      if(gJGyOFSuVQ == FJaptAgfRF){UVQwJRyFEI = true;}
      else if(FJaptAgfRF == gJGyOFSuVQ){waRmFfLltZ = true;}
      if(lAHsqLEXht == LdIyJRFuXd){DXqpfcHUWh = true;}
      else if(LdIyJRFuXd == lAHsqLEXht){BqMQVjULDO = true;}
      if(axByOlRODr == lkNfPXDjwE){hZbGkXNOLY = true;}
      else if(lkNfPXDjwE == axByOlRODr){ZYgGjgjuei = true;}
      if(FnbyYRxRhm == IaSxfJtIBE){KHeKPUCqFX = true;}
      else if(IaSxfJtIBE == FnbyYRxRhm){fsYlynDbbx = true;}
      if(WeYWAdSwPH == AfVpcfgjwg){RxfaIpIrze = true;}
      else if(AfVpcfgjwg == WeYWAdSwPH){XjZZSiePyj = true;}
      if(mXaoCjIHjc == NrYhOTutZW){wakKKusKLk = true;}
      else if(NrYhOTutZW == mXaoCjIHjc){MrxNkXtLDX = true;}
      if(mEqcLyYJUY == wwjNxjKLSz){EjsfywsgaL = true;}
      if(NlpuWwXdyk == XwsTcGPXDj){ZQPyPjsBxu = true;}
      if(TVzuFhMmwo == pTnOpPCkiM){PUPgciVUzU = true;}
      while(wwjNxjKLSz == mEqcLyYJUY){uPHLsHRaRg = true;}
      while(XwsTcGPXDj == XwsTcGPXDj){gsjFppyGmA = true;}
      while(pTnOpPCkiM == pTnOpPCkiM){CUwtVnwLAa = true;}
      if(NzieHDwIrr == true){NzieHDwIrr = false;}
      if(UVQwJRyFEI == true){UVQwJRyFEI = false;}
      if(DXqpfcHUWh == true){DXqpfcHUWh = false;}
      if(hZbGkXNOLY == true){hZbGkXNOLY = false;}
      if(KHeKPUCqFX == true){KHeKPUCqFX = false;}
      if(RxfaIpIrze == true){RxfaIpIrze = false;}
      if(wakKKusKLk == true){wakKKusKLk = false;}
      if(EjsfywsgaL == true){EjsfywsgaL = false;}
      if(ZQPyPjsBxu == true){ZQPyPjsBxu = false;}
      if(PUPgciVUzU == true){PUPgciVUzU = false;}
      if(arfTTgDAbL == true){arfTTgDAbL = false;}
      if(waRmFfLltZ == true){waRmFfLltZ = false;}
      if(BqMQVjULDO == true){BqMQVjULDO = false;}
      if(ZYgGjgjuei == true){ZYgGjgjuei = false;}
      if(fsYlynDbbx == true){fsYlynDbbx = false;}
      if(XjZZSiePyj == true){XjZZSiePyj = false;}
      if(MrxNkXtLDX == true){MrxNkXtLDX = false;}
      if(uPHLsHRaRg == true){uPHLsHRaRg = false;}
      if(gsjFppyGmA == true){gsjFppyGmA = false;}
      if(CUwtVnwLAa == true){CUwtVnwLAa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMVZDLGBXD
{ 
  void mtltDZoiit()
  { 
      bool HFgndQBNEC = false;
      bool IGSdoXMaBH = false;
      bool sPxUAiuGDL = false;
      bool mTufURXVTb = false;
      bool qGtupGsBtG = false;
      bool xtMXdqIMnu = false;
      bool VuJrOnKmJX = false;
      bool AqGYPlVBes = false;
      bool ptMwOsHXBc = false;
      bool IKgXGwwBfB = false;
      bool uFqVGFmnHq = false;
      bool VHgtEahNdV = false;
      bool glkfOpJiRT = false;
      bool pUUcxjCqpI = false;
      bool GSQKHBcmTf = false;
      bool OiWKUJULHP = false;
      bool wEVnBBlEwT = false;
      bool XqWUPNVaYM = false;
      bool MWOlEGxKIn = false;
      bool PqiaMBxbIF = false;
      string RsuWtSQTbw;
      string CzxDLEFgsI;
      string UfBWozAIxq;
      string bLQXACbpHT;
      string OCZyCQOKPO;
      string yKVaEkqXgt;
      string RHWjUqhZCJ;
      string cOZZsRGDTX;
      string jpsirRopSO;
      string KEJMBHfodL;
      string ioIGlijwgm;
      string enDIJbOmrD;
      string BrGmzXFMXl;
      string lRZIougmxI;
      string gsIfjVAACZ;
      string rrxaKqhVGN;
      string cWYtANOuSN;
      string ubpiVHiaCc;
      string XFKyssUyyy;
      string NLfieJUOeW;
      if(RsuWtSQTbw == ioIGlijwgm){HFgndQBNEC = true;}
      else if(ioIGlijwgm == RsuWtSQTbw){uFqVGFmnHq = true;}
      if(CzxDLEFgsI == enDIJbOmrD){IGSdoXMaBH = true;}
      else if(enDIJbOmrD == CzxDLEFgsI){VHgtEahNdV = true;}
      if(UfBWozAIxq == BrGmzXFMXl){sPxUAiuGDL = true;}
      else if(BrGmzXFMXl == UfBWozAIxq){glkfOpJiRT = true;}
      if(bLQXACbpHT == lRZIougmxI){mTufURXVTb = true;}
      else if(lRZIougmxI == bLQXACbpHT){pUUcxjCqpI = true;}
      if(OCZyCQOKPO == gsIfjVAACZ){qGtupGsBtG = true;}
      else if(gsIfjVAACZ == OCZyCQOKPO){GSQKHBcmTf = true;}
      if(yKVaEkqXgt == rrxaKqhVGN){xtMXdqIMnu = true;}
      else if(rrxaKqhVGN == yKVaEkqXgt){OiWKUJULHP = true;}
      if(RHWjUqhZCJ == cWYtANOuSN){VuJrOnKmJX = true;}
      else if(cWYtANOuSN == RHWjUqhZCJ){wEVnBBlEwT = true;}
      if(cOZZsRGDTX == ubpiVHiaCc){AqGYPlVBes = true;}
      if(jpsirRopSO == XFKyssUyyy){ptMwOsHXBc = true;}
      if(KEJMBHfodL == NLfieJUOeW){IKgXGwwBfB = true;}
      while(ubpiVHiaCc == cOZZsRGDTX){XqWUPNVaYM = true;}
      while(XFKyssUyyy == XFKyssUyyy){MWOlEGxKIn = true;}
      while(NLfieJUOeW == NLfieJUOeW){PqiaMBxbIF = true;}
      if(HFgndQBNEC == true){HFgndQBNEC = false;}
      if(IGSdoXMaBH == true){IGSdoXMaBH = false;}
      if(sPxUAiuGDL == true){sPxUAiuGDL = false;}
      if(mTufURXVTb == true){mTufURXVTb = false;}
      if(qGtupGsBtG == true){qGtupGsBtG = false;}
      if(xtMXdqIMnu == true){xtMXdqIMnu = false;}
      if(VuJrOnKmJX == true){VuJrOnKmJX = false;}
      if(AqGYPlVBes == true){AqGYPlVBes = false;}
      if(ptMwOsHXBc == true){ptMwOsHXBc = false;}
      if(IKgXGwwBfB == true){IKgXGwwBfB = false;}
      if(uFqVGFmnHq == true){uFqVGFmnHq = false;}
      if(VHgtEahNdV == true){VHgtEahNdV = false;}
      if(glkfOpJiRT == true){glkfOpJiRT = false;}
      if(pUUcxjCqpI == true){pUUcxjCqpI = false;}
      if(GSQKHBcmTf == true){GSQKHBcmTf = false;}
      if(OiWKUJULHP == true){OiWKUJULHP = false;}
      if(wEVnBBlEwT == true){wEVnBBlEwT = false;}
      if(XqWUPNVaYM == true){XqWUPNVaYM = false;}
      if(MWOlEGxKIn == true){MWOlEGxKIn = false;}
      if(PqiaMBxbIF == true){PqiaMBxbIF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRPSTSRYZV
{ 
  void unqBZgkOEP()
  { 
      bool HYUjHwUAEP = false;
      bool bznlXPtXEM = false;
      bool RLJowEtGzf = false;
      bool gRzZKQEpfb = false;
      bool QEarBVDlRg = false;
      bool BhQEbuOfnC = false;
      bool BNBXiJAOaH = false;
      bool LErcuMkRmZ = false;
      bool AIoSeyBtxO = false;
      bool BXCcZDDCIr = false;
      bool VoKJUxomJO = false;
      bool JxrNBsYisj = false;
      bool HFRLGmCPCq = false;
      bool JiIuELxexg = false;
      bool JNkhFDfnag = false;
      bool dUJYjPXyDh = false;
      bool uZjRFanxIp = false;
      bool uskLasUiGC = false;
      bool HNnVNoYjLo = false;
      bool nzaPljcSce = false;
      string scAqDTYkXM;
      string BVgfRPIUzt;
      string dkhEoVXipA;
      string yZXkByPylB;
      string yKCqkxpams;
      string LgCKUIuwBg;
      string wpuWNbyweT;
      string AJhxuShpSq;
      string exuwnRWMQr;
      string DTxEEIPedI;
      string ztuTsCzEOB;
      string ZEcJCztyhu;
      string FkelQfMcsl;
      string DCMKrkBbCl;
      string SRxPRyqmCF;
      string OQxhCOPIDN;
      string oVLcyXqRRR;
      string xSwwcmmPTR;
      string oZamXlFeHc;
      string UrXowwGUQt;
      if(scAqDTYkXM == ztuTsCzEOB){HYUjHwUAEP = true;}
      else if(ztuTsCzEOB == scAqDTYkXM){VoKJUxomJO = true;}
      if(BVgfRPIUzt == ZEcJCztyhu){bznlXPtXEM = true;}
      else if(ZEcJCztyhu == BVgfRPIUzt){JxrNBsYisj = true;}
      if(dkhEoVXipA == FkelQfMcsl){RLJowEtGzf = true;}
      else if(FkelQfMcsl == dkhEoVXipA){HFRLGmCPCq = true;}
      if(yZXkByPylB == DCMKrkBbCl){gRzZKQEpfb = true;}
      else if(DCMKrkBbCl == yZXkByPylB){JiIuELxexg = true;}
      if(yKCqkxpams == SRxPRyqmCF){QEarBVDlRg = true;}
      else if(SRxPRyqmCF == yKCqkxpams){JNkhFDfnag = true;}
      if(LgCKUIuwBg == OQxhCOPIDN){BhQEbuOfnC = true;}
      else if(OQxhCOPIDN == LgCKUIuwBg){dUJYjPXyDh = true;}
      if(wpuWNbyweT == oVLcyXqRRR){BNBXiJAOaH = true;}
      else if(oVLcyXqRRR == wpuWNbyweT){uZjRFanxIp = true;}
      if(AJhxuShpSq == xSwwcmmPTR){LErcuMkRmZ = true;}
      if(exuwnRWMQr == oZamXlFeHc){AIoSeyBtxO = true;}
      if(DTxEEIPedI == UrXowwGUQt){BXCcZDDCIr = true;}
      while(xSwwcmmPTR == AJhxuShpSq){uskLasUiGC = true;}
      while(oZamXlFeHc == oZamXlFeHc){HNnVNoYjLo = true;}
      while(UrXowwGUQt == UrXowwGUQt){nzaPljcSce = true;}
      if(HYUjHwUAEP == true){HYUjHwUAEP = false;}
      if(bznlXPtXEM == true){bznlXPtXEM = false;}
      if(RLJowEtGzf == true){RLJowEtGzf = false;}
      if(gRzZKQEpfb == true){gRzZKQEpfb = false;}
      if(QEarBVDlRg == true){QEarBVDlRg = false;}
      if(BhQEbuOfnC == true){BhQEbuOfnC = false;}
      if(BNBXiJAOaH == true){BNBXiJAOaH = false;}
      if(LErcuMkRmZ == true){LErcuMkRmZ = false;}
      if(AIoSeyBtxO == true){AIoSeyBtxO = false;}
      if(BXCcZDDCIr == true){BXCcZDDCIr = false;}
      if(VoKJUxomJO == true){VoKJUxomJO = false;}
      if(JxrNBsYisj == true){JxrNBsYisj = false;}
      if(HFRLGmCPCq == true){HFRLGmCPCq = false;}
      if(JiIuELxexg == true){JiIuELxexg = false;}
      if(JNkhFDfnag == true){JNkhFDfnag = false;}
      if(dUJYjPXyDh == true){dUJYjPXyDh = false;}
      if(uZjRFanxIp == true){uZjRFanxIp = false;}
      if(uskLasUiGC == true){uskLasUiGC = false;}
      if(HNnVNoYjLo == true){HNnVNoYjLo = false;}
      if(nzaPljcSce == true){nzaPljcSce = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPBZEUBECI
{ 
  void maEwpSlprM()
  { 
      bool zdjxSWtcMg = false;
      bool jSUtnMGBbo = false;
      bool uTyIeQARhD = false;
      bool ijNwhBZCdJ = false;
      bool qBJVKkXzCm = false;
      bool xlEFcefaRC = false;
      bool VbtIyzFXLm = false;
      bool mEXSxtKbys = false;
      bool rAOuGxfITD = false;
      bool UyjamOGBXK = false;
      bool fzmOzsOkHh = false;
      bool UDcXKUNzCA = false;
      bool TxEIRoTwfh = false;
      bool nJDmNrNzuN = false;
      bool itAkiRUMQR = false;
      bool BGyWpitexK = false;
      bool YREYsKAoKR = false;
      bool HNEoRYwTZA = false;
      bool TGfOggKfxd = false;
      bool xhCknQoaqX = false;
      string HgWZHSCYEY;
      string johbaPkcsD;
      string weYtSFjPPD;
      string LUkRrfQwzB;
      string VgTxaMUstb;
      string JPNnfbIcGB;
      string imIAMODPju;
      string yndqgOKaSF;
      string kqVnsuHwlP;
      string WnoxSiYTkL;
      string IEIzcVlVGQ;
      string RgJBQqQUGQ;
      string HHdTXJyfXy;
      string pqpHwfhVKX;
      string JkoUypengb;
      string REMTDBaobS;
      string WFxIaZqBEj;
      string IuJiHWRIUg;
      string eJzwfldWDu;
      string ErtqADmgtY;
      if(HgWZHSCYEY == IEIzcVlVGQ){zdjxSWtcMg = true;}
      else if(IEIzcVlVGQ == HgWZHSCYEY){fzmOzsOkHh = true;}
      if(johbaPkcsD == RgJBQqQUGQ){jSUtnMGBbo = true;}
      else if(RgJBQqQUGQ == johbaPkcsD){UDcXKUNzCA = true;}
      if(weYtSFjPPD == HHdTXJyfXy){uTyIeQARhD = true;}
      else if(HHdTXJyfXy == weYtSFjPPD){TxEIRoTwfh = true;}
      if(LUkRrfQwzB == pqpHwfhVKX){ijNwhBZCdJ = true;}
      else if(pqpHwfhVKX == LUkRrfQwzB){nJDmNrNzuN = true;}
      if(VgTxaMUstb == JkoUypengb){qBJVKkXzCm = true;}
      else if(JkoUypengb == VgTxaMUstb){itAkiRUMQR = true;}
      if(JPNnfbIcGB == REMTDBaobS){xlEFcefaRC = true;}
      else if(REMTDBaobS == JPNnfbIcGB){BGyWpitexK = true;}
      if(imIAMODPju == WFxIaZqBEj){VbtIyzFXLm = true;}
      else if(WFxIaZqBEj == imIAMODPju){YREYsKAoKR = true;}
      if(yndqgOKaSF == IuJiHWRIUg){mEXSxtKbys = true;}
      if(kqVnsuHwlP == eJzwfldWDu){rAOuGxfITD = true;}
      if(WnoxSiYTkL == ErtqADmgtY){UyjamOGBXK = true;}
      while(IuJiHWRIUg == yndqgOKaSF){HNEoRYwTZA = true;}
      while(eJzwfldWDu == eJzwfldWDu){TGfOggKfxd = true;}
      while(ErtqADmgtY == ErtqADmgtY){xhCknQoaqX = true;}
      if(zdjxSWtcMg == true){zdjxSWtcMg = false;}
      if(jSUtnMGBbo == true){jSUtnMGBbo = false;}
      if(uTyIeQARhD == true){uTyIeQARhD = false;}
      if(ijNwhBZCdJ == true){ijNwhBZCdJ = false;}
      if(qBJVKkXzCm == true){qBJVKkXzCm = false;}
      if(xlEFcefaRC == true){xlEFcefaRC = false;}
      if(VbtIyzFXLm == true){VbtIyzFXLm = false;}
      if(mEXSxtKbys == true){mEXSxtKbys = false;}
      if(rAOuGxfITD == true){rAOuGxfITD = false;}
      if(UyjamOGBXK == true){UyjamOGBXK = false;}
      if(fzmOzsOkHh == true){fzmOzsOkHh = false;}
      if(UDcXKUNzCA == true){UDcXKUNzCA = false;}
      if(TxEIRoTwfh == true){TxEIRoTwfh = false;}
      if(nJDmNrNzuN == true){nJDmNrNzuN = false;}
      if(itAkiRUMQR == true){itAkiRUMQR = false;}
      if(BGyWpitexK == true){BGyWpitexK = false;}
      if(YREYsKAoKR == true){YREYsKAoKR = false;}
      if(HNEoRYwTZA == true){HNEoRYwTZA = false;}
      if(TGfOggKfxd == true){TGfOggKfxd = false;}
      if(xhCknQoaqX == true){xhCknQoaqX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WDHVTTQSFN
{ 
  void cNlyWxmlki()
  { 
      bool VhTjbAWmYw = false;
      bool metftsUcmF = false;
      bool NaxETVGfNj = false;
      bool KUGMEulbCZ = false;
      bool qTIGdlJNFP = false;
      bool aXfsHtjPQG = false;
      bool sqYnlRXgay = false;
      bool GraMOsRpah = false;
      bool LsaxJloNEK = false;
      bool LWLwgztUUL = false;
      bool NbmHJhwSdN = false;
      bool btoitAPaeA = false;
      bool cJcQmjgefO = false;
      bool zxVOTiGTna = false;
      bool oViphQhcBf = false;
      bool jSoUiDzVTY = false;
      bool BRlPOeXZOK = false;
      bool twlDKGaliV = false;
      bool CDdAefHAfP = false;
      bool jjzPZXiTbC = false;
      string TSolkPYRcx;
      string mkrOKLHnfB;
      string xcSkgqdIDu;
      string uVsQQbBIAs;
      string UVWQupixuu;
      string sDZWMqzEFs;
      string lQNhBRrayh;
      string JynmgaFCpq;
      string IfNICrwWEZ;
      string bxDGHEIoOd;
      string xHzMktOmol;
      string kxNOkFCEeJ;
      string UVWXFMuheb;
      string RQnMsAfBXI;
      string cJgRoeioUB;
      string BDJFIbjbGX;
      string zgHNTTJBUj;
      string ZBfWfLnFha;
      string dFMdZOGhDQ;
      string QDtAIuBTyU;
      if(TSolkPYRcx == xHzMktOmol){VhTjbAWmYw = true;}
      else if(xHzMktOmol == TSolkPYRcx){NbmHJhwSdN = true;}
      if(mkrOKLHnfB == kxNOkFCEeJ){metftsUcmF = true;}
      else if(kxNOkFCEeJ == mkrOKLHnfB){btoitAPaeA = true;}
      if(xcSkgqdIDu == UVWXFMuheb){NaxETVGfNj = true;}
      else if(UVWXFMuheb == xcSkgqdIDu){cJcQmjgefO = true;}
      if(uVsQQbBIAs == RQnMsAfBXI){KUGMEulbCZ = true;}
      else if(RQnMsAfBXI == uVsQQbBIAs){zxVOTiGTna = true;}
      if(UVWQupixuu == cJgRoeioUB){qTIGdlJNFP = true;}
      else if(cJgRoeioUB == UVWQupixuu){oViphQhcBf = true;}
      if(sDZWMqzEFs == BDJFIbjbGX){aXfsHtjPQG = true;}
      else if(BDJFIbjbGX == sDZWMqzEFs){jSoUiDzVTY = true;}
      if(lQNhBRrayh == zgHNTTJBUj){sqYnlRXgay = true;}
      else if(zgHNTTJBUj == lQNhBRrayh){BRlPOeXZOK = true;}
      if(JynmgaFCpq == ZBfWfLnFha){GraMOsRpah = true;}
      if(IfNICrwWEZ == dFMdZOGhDQ){LsaxJloNEK = true;}
      if(bxDGHEIoOd == QDtAIuBTyU){LWLwgztUUL = true;}
      while(ZBfWfLnFha == JynmgaFCpq){twlDKGaliV = true;}
      while(dFMdZOGhDQ == dFMdZOGhDQ){CDdAefHAfP = true;}
      while(QDtAIuBTyU == QDtAIuBTyU){jjzPZXiTbC = true;}
      if(VhTjbAWmYw == true){VhTjbAWmYw = false;}
      if(metftsUcmF == true){metftsUcmF = false;}
      if(NaxETVGfNj == true){NaxETVGfNj = false;}
      if(KUGMEulbCZ == true){KUGMEulbCZ = false;}
      if(qTIGdlJNFP == true){qTIGdlJNFP = false;}
      if(aXfsHtjPQG == true){aXfsHtjPQG = false;}
      if(sqYnlRXgay == true){sqYnlRXgay = false;}
      if(GraMOsRpah == true){GraMOsRpah = false;}
      if(LsaxJloNEK == true){LsaxJloNEK = false;}
      if(LWLwgztUUL == true){LWLwgztUUL = false;}
      if(NbmHJhwSdN == true){NbmHJhwSdN = false;}
      if(btoitAPaeA == true){btoitAPaeA = false;}
      if(cJcQmjgefO == true){cJcQmjgefO = false;}
      if(zxVOTiGTna == true){zxVOTiGTna = false;}
      if(oViphQhcBf == true){oViphQhcBf = false;}
      if(jSoUiDzVTY == true){jSoUiDzVTY = false;}
      if(BRlPOeXZOK == true){BRlPOeXZOK = false;}
      if(twlDKGaliV == true){twlDKGaliV = false;}
      if(CDdAefHAfP == true){CDdAefHAfP = false;}
      if(jjzPZXiTbC == true){jjzPZXiTbC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNFXELVRMS
{ 
  void emlufktEHc()
  { 
      bool CODgfCxczm = false;
      bool ZnPUtptgzF = false;
      bool gzqipnujEi = false;
      bool NoZyKqkGPq = false;
      bool NlLxVCSPcK = false;
      bool ECCmFDXUpr = false;
      bool HMYQYjNQKC = false;
      bool FmRIqtmsMn = false;
      bool UfHsdLmmsG = false;
      bool SPPWiAMuYk = false;
      bool nBEZEQktuK = false;
      bool QeHCXaFfmN = false;
      bool waXEipWtYq = false;
      bool grTazSahnM = false;
      bool asrhpnHNzI = false;
      bool ugILoNcApO = false;
      bool spUDcXKgCE = false;
      bool AXqZlDhpNu = false;
      bool hIuQwAjIlk = false;
      bool oaqZSkXnFS = false;
      string XwcUZhEtFN;
      string YqZrtnbmZT;
      string YJHNOUYbzj;
      string lYrMsEDeuS;
      string JcpUwArTzf;
      string AYidZNoPFF;
      string JbuVaAzMzp;
      string jxqHJuSlRN;
      string bEcSiNoNle;
      string PnZpIhgUtw;
      string BfUJwChbUe;
      string uCxqcFzclN;
      string KkZUawXAyb;
      string OyrVMwiTVg;
      string fMsHiMphNC;
      string hDhgkQFAhz;
      string egcrPwKbdg;
      string WfGFgxqRkN;
      string FomwsKPKku;
      string phkWByjBrl;
      if(XwcUZhEtFN == BfUJwChbUe){CODgfCxczm = true;}
      else if(BfUJwChbUe == XwcUZhEtFN){nBEZEQktuK = true;}
      if(YqZrtnbmZT == uCxqcFzclN){ZnPUtptgzF = true;}
      else if(uCxqcFzclN == YqZrtnbmZT){QeHCXaFfmN = true;}
      if(YJHNOUYbzj == KkZUawXAyb){gzqipnujEi = true;}
      else if(KkZUawXAyb == YJHNOUYbzj){waXEipWtYq = true;}
      if(lYrMsEDeuS == OyrVMwiTVg){NoZyKqkGPq = true;}
      else if(OyrVMwiTVg == lYrMsEDeuS){grTazSahnM = true;}
      if(JcpUwArTzf == fMsHiMphNC){NlLxVCSPcK = true;}
      else if(fMsHiMphNC == JcpUwArTzf){asrhpnHNzI = true;}
      if(AYidZNoPFF == hDhgkQFAhz){ECCmFDXUpr = true;}
      else if(hDhgkQFAhz == AYidZNoPFF){ugILoNcApO = true;}
      if(JbuVaAzMzp == egcrPwKbdg){HMYQYjNQKC = true;}
      else if(egcrPwKbdg == JbuVaAzMzp){spUDcXKgCE = true;}
      if(jxqHJuSlRN == WfGFgxqRkN){FmRIqtmsMn = true;}
      if(bEcSiNoNle == FomwsKPKku){UfHsdLmmsG = true;}
      if(PnZpIhgUtw == phkWByjBrl){SPPWiAMuYk = true;}
      while(WfGFgxqRkN == jxqHJuSlRN){AXqZlDhpNu = true;}
      while(FomwsKPKku == FomwsKPKku){hIuQwAjIlk = true;}
      while(phkWByjBrl == phkWByjBrl){oaqZSkXnFS = true;}
      if(CODgfCxczm == true){CODgfCxczm = false;}
      if(ZnPUtptgzF == true){ZnPUtptgzF = false;}
      if(gzqipnujEi == true){gzqipnujEi = false;}
      if(NoZyKqkGPq == true){NoZyKqkGPq = false;}
      if(NlLxVCSPcK == true){NlLxVCSPcK = false;}
      if(ECCmFDXUpr == true){ECCmFDXUpr = false;}
      if(HMYQYjNQKC == true){HMYQYjNQKC = false;}
      if(FmRIqtmsMn == true){FmRIqtmsMn = false;}
      if(UfHsdLmmsG == true){UfHsdLmmsG = false;}
      if(SPPWiAMuYk == true){SPPWiAMuYk = false;}
      if(nBEZEQktuK == true){nBEZEQktuK = false;}
      if(QeHCXaFfmN == true){QeHCXaFfmN = false;}
      if(waXEipWtYq == true){waXEipWtYq = false;}
      if(grTazSahnM == true){grTazSahnM = false;}
      if(asrhpnHNzI == true){asrhpnHNzI = false;}
      if(ugILoNcApO == true){ugILoNcApO = false;}
      if(spUDcXKgCE == true){spUDcXKgCE = false;}
      if(AXqZlDhpNu == true){AXqZlDhpNu = false;}
      if(hIuQwAjIlk == true){hIuQwAjIlk = false;}
      if(oaqZSkXnFS == true){oaqZSkXnFS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYVZZZOYDL
{ 
  void UVqjeXrYDg()
  { 
      bool MXgjiGWttd = false;
      bool OxGPpsbGpm = false;
      bool TjUkYDsBMY = false;
      bool DKTXPtkgnR = false;
      bool cNampbkCQi = false;
      bool IiCxKcCwKe = false;
      bool NVgVZEchAu = false;
      bool HuRXKGIhuw = false;
      bool SpjdPUIWNl = false;
      bool roWIEHfFNl = false;
      bool zCCUaMQdmD = false;
      bool UUANMWlCFF = false;
      bool wGUNDSYJTC = false;
      bool ZDTIxQnODD = false;
      bool DdiJRWnIug = false;
      bool UczIpsgnRI = false;
      bool nGKjdQArQw = false;
      bool iWzCBRXLwg = false;
      bool dPNlgwDLSE = false;
      bool iAxtOwSyfA = false;
      string SRYMCfytzl;
      string PTbirJcHNi;
      string csTVzPSfMa;
      string bEuDzxqzwl;
      string FnlCuzFAhH;
      string hEFhJZyCMl;
      string MSgXKLXYit;
      string SdKacoGRZz;
      string JRxFsWyMtZ;
      string znlKYmHOqj;
      string bgRmnEseFU;
      string TfcNbuUaem;
      string MKdIudqABp;
      string gqZoWcAKRo;
      string dSHYGSLYid;
      string RgjEXRCIrJ;
      string MsdOnbFmqz;
      string uKJoJsCFCb;
      string SSQWYAHVRF;
      string ZqRHbkorkd;
      if(SRYMCfytzl == bgRmnEseFU){MXgjiGWttd = true;}
      else if(bgRmnEseFU == SRYMCfytzl){zCCUaMQdmD = true;}
      if(PTbirJcHNi == TfcNbuUaem){OxGPpsbGpm = true;}
      else if(TfcNbuUaem == PTbirJcHNi){UUANMWlCFF = true;}
      if(csTVzPSfMa == MKdIudqABp){TjUkYDsBMY = true;}
      else if(MKdIudqABp == csTVzPSfMa){wGUNDSYJTC = true;}
      if(bEuDzxqzwl == gqZoWcAKRo){DKTXPtkgnR = true;}
      else if(gqZoWcAKRo == bEuDzxqzwl){ZDTIxQnODD = true;}
      if(FnlCuzFAhH == dSHYGSLYid){cNampbkCQi = true;}
      else if(dSHYGSLYid == FnlCuzFAhH){DdiJRWnIug = true;}
      if(hEFhJZyCMl == RgjEXRCIrJ){IiCxKcCwKe = true;}
      else if(RgjEXRCIrJ == hEFhJZyCMl){UczIpsgnRI = true;}
      if(MSgXKLXYit == MsdOnbFmqz){NVgVZEchAu = true;}
      else if(MsdOnbFmqz == MSgXKLXYit){nGKjdQArQw = true;}
      if(SdKacoGRZz == uKJoJsCFCb){HuRXKGIhuw = true;}
      if(JRxFsWyMtZ == SSQWYAHVRF){SpjdPUIWNl = true;}
      if(znlKYmHOqj == ZqRHbkorkd){roWIEHfFNl = true;}
      while(uKJoJsCFCb == SdKacoGRZz){iWzCBRXLwg = true;}
      while(SSQWYAHVRF == SSQWYAHVRF){dPNlgwDLSE = true;}
      while(ZqRHbkorkd == ZqRHbkorkd){iAxtOwSyfA = true;}
      if(MXgjiGWttd == true){MXgjiGWttd = false;}
      if(OxGPpsbGpm == true){OxGPpsbGpm = false;}
      if(TjUkYDsBMY == true){TjUkYDsBMY = false;}
      if(DKTXPtkgnR == true){DKTXPtkgnR = false;}
      if(cNampbkCQi == true){cNampbkCQi = false;}
      if(IiCxKcCwKe == true){IiCxKcCwKe = false;}
      if(NVgVZEchAu == true){NVgVZEchAu = false;}
      if(HuRXKGIhuw == true){HuRXKGIhuw = false;}
      if(SpjdPUIWNl == true){SpjdPUIWNl = false;}
      if(roWIEHfFNl == true){roWIEHfFNl = false;}
      if(zCCUaMQdmD == true){zCCUaMQdmD = false;}
      if(UUANMWlCFF == true){UUANMWlCFF = false;}
      if(wGUNDSYJTC == true){wGUNDSYJTC = false;}
      if(ZDTIxQnODD == true){ZDTIxQnODD = false;}
      if(DdiJRWnIug == true){DdiJRWnIug = false;}
      if(UczIpsgnRI == true){UczIpsgnRI = false;}
      if(nGKjdQArQw == true){nGKjdQArQw = false;}
      if(iWzCBRXLwg == true){iWzCBRXLwg = false;}
      if(dPNlgwDLSE == true){dPNlgwDLSE = false;}
      if(iAxtOwSyfA == true){iAxtOwSyfA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUBCLTKVFI
{ 
  void itmWwwJOQW()
  { 
      bool IOHnweQDmf = false;
      bool SflougzsqV = false;
      bool iwRaFGgQHD = false;
      bool NDrbGESYNc = false;
      bool uxKTsSDXYf = false;
      bool BUCSzLxgip = false;
      bool xAwiROmKhp = false;
      bool OZfNallxhl = false;
      bool CJqaCsBYcu = false;
      bool HkoXetAaCd = false;
      bool esphRaonrM = false;
      bool ZzzwnnIUgX = false;
      bool NOglidkHhg = false;
      bool kKuDHITJJb = false;
      bool EMgPVHkrjq = false;
      bool lftdQQLDzn = false;
      bool ogGLbOEuoe = false;
      bool TzKETAgRPb = false;
      bool rrXqtEPQmq = false;
      bool wQJUlXGVmG = false;
      string AjVzaCUquD;
      string hrdoiziWKD;
      string cyAjDcBVWF;
      string JNbDfZrEHd;
      string jqGBYVukgW;
      string GfmAhCjluy;
      string BzTosUQaII;
      string HdOfSkqyLg;
      string gQnzycZaUd;
      string oGIJcjWQHD;
      string FTbXPcQHhx;
      string KkZOQjKUqQ;
      string uoFdTAUFCh;
      string OapIbMnQiV;
      string LSrXSDgtrr;
      string ZCZqIPNxEO;
      string HLEzhjuRlD;
      string wtkVEbxhLP;
      string TZMKILAyzL;
      string ypMTNAOsoi;
      if(AjVzaCUquD == FTbXPcQHhx){IOHnweQDmf = true;}
      else if(FTbXPcQHhx == AjVzaCUquD){esphRaonrM = true;}
      if(hrdoiziWKD == KkZOQjKUqQ){SflougzsqV = true;}
      else if(KkZOQjKUqQ == hrdoiziWKD){ZzzwnnIUgX = true;}
      if(cyAjDcBVWF == uoFdTAUFCh){iwRaFGgQHD = true;}
      else if(uoFdTAUFCh == cyAjDcBVWF){NOglidkHhg = true;}
      if(JNbDfZrEHd == OapIbMnQiV){NDrbGESYNc = true;}
      else if(OapIbMnQiV == JNbDfZrEHd){kKuDHITJJb = true;}
      if(jqGBYVukgW == LSrXSDgtrr){uxKTsSDXYf = true;}
      else if(LSrXSDgtrr == jqGBYVukgW){EMgPVHkrjq = true;}
      if(GfmAhCjluy == ZCZqIPNxEO){BUCSzLxgip = true;}
      else if(ZCZqIPNxEO == GfmAhCjluy){lftdQQLDzn = true;}
      if(BzTosUQaII == HLEzhjuRlD){xAwiROmKhp = true;}
      else if(HLEzhjuRlD == BzTosUQaII){ogGLbOEuoe = true;}
      if(HdOfSkqyLg == wtkVEbxhLP){OZfNallxhl = true;}
      if(gQnzycZaUd == TZMKILAyzL){CJqaCsBYcu = true;}
      if(oGIJcjWQHD == ypMTNAOsoi){HkoXetAaCd = true;}
      while(wtkVEbxhLP == HdOfSkqyLg){TzKETAgRPb = true;}
      while(TZMKILAyzL == TZMKILAyzL){rrXqtEPQmq = true;}
      while(ypMTNAOsoi == ypMTNAOsoi){wQJUlXGVmG = true;}
      if(IOHnweQDmf == true){IOHnweQDmf = false;}
      if(SflougzsqV == true){SflougzsqV = false;}
      if(iwRaFGgQHD == true){iwRaFGgQHD = false;}
      if(NDrbGESYNc == true){NDrbGESYNc = false;}
      if(uxKTsSDXYf == true){uxKTsSDXYf = false;}
      if(BUCSzLxgip == true){BUCSzLxgip = false;}
      if(xAwiROmKhp == true){xAwiROmKhp = false;}
      if(OZfNallxhl == true){OZfNallxhl = false;}
      if(CJqaCsBYcu == true){CJqaCsBYcu = false;}
      if(HkoXetAaCd == true){HkoXetAaCd = false;}
      if(esphRaonrM == true){esphRaonrM = false;}
      if(ZzzwnnIUgX == true){ZzzwnnIUgX = false;}
      if(NOglidkHhg == true){NOglidkHhg = false;}
      if(kKuDHITJJb == true){kKuDHITJJb = false;}
      if(EMgPVHkrjq == true){EMgPVHkrjq = false;}
      if(lftdQQLDzn == true){lftdQQLDzn = false;}
      if(ogGLbOEuoe == true){ogGLbOEuoe = false;}
      if(TzKETAgRPb == true){TzKETAgRPb = false;}
      if(rrXqtEPQmq == true){rrXqtEPQmq = false;}
      if(wQJUlXGVmG == true){wQJUlXGVmG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXSSMWYEKF
{ 
  void pPBWflmlhJ()
  { 
      bool qlOcIYaKyS = false;
      bool EljHaTUMUY = false;
      bool xZrdwKfyuS = false;
      bool MiQlRgyIxM = false;
      bool aWLTNjlXKW = false;
      bool GHmUCRtkfy = false;
      bool rbOfGUVyos = false;
      bool ULOHyaNYPL = false;
      bool XInXLEuwiA = false;
      bool mNczTyIfMs = false;
      bool OmhQCureVb = false;
      bool DUUTZjnpTC = false;
      bool YYPoFHiPnz = false;
      bool RhLWxjZWVQ = false;
      bool LQZHxRrIZi = false;
      bool KRLKToXsKt = false;
      bool McqWJUIyWo = false;
      bool JQUCpIzIqn = false;
      bool OZpEoAWBCH = false;
      bool MgLaEiYCxc = false;
      string SBdpnrCnEb;
      string LdXrUfnjrP;
      string pYqDOHguMU;
      string dkhkjXKwQc;
      string ACoSuyNxyB;
      string uHfqctKZag;
      string KGaiyZwmIx;
      string VrSPPnjXIQ;
      string tixLZVFpIp;
      string NjUjRsaFUU;
      string CaoAfDoQbn;
      string JmRKmbIPJb;
      string UFdSjkWhxV;
      string NdDmOStwfW;
      string gnNTfaRKwp;
      string kLwsAwwWQt;
      string fGTFaeiewT;
      string hLjltgqJlJ;
      string TMlGkCgJlR;
      string WWfkpaUIsA;
      if(SBdpnrCnEb == CaoAfDoQbn){qlOcIYaKyS = true;}
      else if(CaoAfDoQbn == SBdpnrCnEb){OmhQCureVb = true;}
      if(LdXrUfnjrP == JmRKmbIPJb){EljHaTUMUY = true;}
      else if(JmRKmbIPJb == LdXrUfnjrP){DUUTZjnpTC = true;}
      if(pYqDOHguMU == UFdSjkWhxV){xZrdwKfyuS = true;}
      else if(UFdSjkWhxV == pYqDOHguMU){YYPoFHiPnz = true;}
      if(dkhkjXKwQc == NdDmOStwfW){MiQlRgyIxM = true;}
      else if(NdDmOStwfW == dkhkjXKwQc){RhLWxjZWVQ = true;}
      if(ACoSuyNxyB == gnNTfaRKwp){aWLTNjlXKW = true;}
      else if(gnNTfaRKwp == ACoSuyNxyB){LQZHxRrIZi = true;}
      if(uHfqctKZag == kLwsAwwWQt){GHmUCRtkfy = true;}
      else if(kLwsAwwWQt == uHfqctKZag){KRLKToXsKt = true;}
      if(KGaiyZwmIx == fGTFaeiewT){rbOfGUVyos = true;}
      else if(fGTFaeiewT == KGaiyZwmIx){McqWJUIyWo = true;}
      if(VrSPPnjXIQ == hLjltgqJlJ){ULOHyaNYPL = true;}
      if(tixLZVFpIp == TMlGkCgJlR){XInXLEuwiA = true;}
      if(NjUjRsaFUU == WWfkpaUIsA){mNczTyIfMs = true;}
      while(hLjltgqJlJ == VrSPPnjXIQ){JQUCpIzIqn = true;}
      while(TMlGkCgJlR == TMlGkCgJlR){OZpEoAWBCH = true;}
      while(WWfkpaUIsA == WWfkpaUIsA){MgLaEiYCxc = true;}
      if(qlOcIYaKyS == true){qlOcIYaKyS = false;}
      if(EljHaTUMUY == true){EljHaTUMUY = false;}
      if(xZrdwKfyuS == true){xZrdwKfyuS = false;}
      if(MiQlRgyIxM == true){MiQlRgyIxM = false;}
      if(aWLTNjlXKW == true){aWLTNjlXKW = false;}
      if(GHmUCRtkfy == true){GHmUCRtkfy = false;}
      if(rbOfGUVyos == true){rbOfGUVyos = false;}
      if(ULOHyaNYPL == true){ULOHyaNYPL = false;}
      if(XInXLEuwiA == true){XInXLEuwiA = false;}
      if(mNczTyIfMs == true){mNczTyIfMs = false;}
      if(OmhQCureVb == true){OmhQCureVb = false;}
      if(DUUTZjnpTC == true){DUUTZjnpTC = false;}
      if(YYPoFHiPnz == true){YYPoFHiPnz = false;}
      if(RhLWxjZWVQ == true){RhLWxjZWVQ = false;}
      if(LQZHxRrIZi == true){LQZHxRrIZi = false;}
      if(KRLKToXsKt == true){KRLKToXsKt = false;}
      if(McqWJUIyWo == true){McqWJUIyWo = false;}
      if(JQUCpIzIqn == true){JQUCpIzIqn = false;}
      if(OZpEoAWBCH == true){OZpEoAWBCH = false;}
      if(MgLaEiYCxc == true){MgLaEiYCxc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLAPAHXPPF
{ 
  void aMGplqhleQ()
  { 
      bool PjlsCsgwhb = false;
      bool theryPDcFM = false;
      bool lbFhUiQZbj = false;
      bool PASjqyEDfc = false;
      bool NrjIPbKyNH = false;
      bool diZDcneEXT = false;
      bool cGTxMsOtBz = false;
      bool LzxbzsqwRr = false;
      bool YRLTGfZPHD = false;
      bool TzfLAGXlwV = false;
      bool NPwOwdlyDj = false;
      bool whleuKtAqf = false;
      bool TzmyeLTkar = false;
      bool UFAweIVxXb = false;
      bool tbLWGlNAQp = false;
      bool LXtQCNcyij = false;
      bool KBWLOqhpzl = false;
      bool oxcPlqmPrs = false;
      bool ySTkfxKjtR = false;
      bool fXNmRrEAIP = false;
      string cxzYdbWCga;
      string ZZdDoiwjZd;
      string cLTfDXuPmA;
      string YkecPAVYjy;
      string HOECqHYHGC;
      string xUtWiQdSVF;
      string fHPfCouAnn;
      string MWzaWNHRou;
      string znIjDDpHsy;
      string WDDeSzzXzB;
      string MXTRpZVTzV;
      string JMcZGryfcz;
      string ymGoRITUIX;
      string NiRmiaTqsd;
      string hWHXoKZcXZ;
      string ASuzDZQeAg;
      string GAKbHZtpqe;
      string XHlzRafizH;
      string ipwhWtnSjJ;
      string JoqMWgLePO;
      if(cxzYdbWCga == MXTRpZVTzV){PjlsCsgwhb = true;}
      else if(MXTRpZVTzV == cxzYdbWCga){NPwOwdlyDj = true;}
      if(ZZdDoiwjZd == JMcZGryfcz){theryPDcFM = true;}
      else if(JMcZGryfcz == ZZdDoiwjZd){whleuKtAqf = true;}
      if(cLTfDXuPmA == ymGoRITUIX){lbFhUiQZbj = true;}
      else if(ymGoRITUIX == cLTfDXuPmA){TzmyeLTkar = true;}
      if(YkecPAVYjy == NiRmiaTqsd){PASjqyEDfc = true;}
      else if(NiRmiaTqsd == YkecPAVYjy){UFAweIVxXb = true;}
      if(HOECqHYHGC == hWHXoKZcXZ){NrjIPbKyNH = true;}
      else if(hWHXoKZcXZ == HOECqHYHGC){tbLWGlNAQp = true;}
      if(xUtWiQdSVF == ASuzDZQeAg){diZDcneEXT = true;}
      else if(ASuzDZQeAg == xUtWiQdSVF){LXtQCNcyij = true;}
      if(fHPfCouAnn == GAKbHZtpqe){cGTxMsOtBz = true;}
      else if(GAKbHZtpqe == fHPfCouAnn){KBWLOqhpzl = true;}
      if(MWzaWNHRou == XHlzRafizH){LzxbzsqwRr = true;}
      if(znIjDDpHsy == ipwhWtnSjJ){YRLTGfZPHD = true;}
      if(WDDeSzzXzB == JoqMWgLePO){TzfLAGXlwV = true;}
      while(XHlzRafizH == MWzaWNHRou){oxcPlqmPrs = true;}
      while(ipwhWtnSjJ == ipwhWtnSjJ){ySTkfxKjtR = true;}
      while(JoqMWgLePO == JoqMWgLePO){fXNmRrEAIP = true;}
      if(PjlsCsgwhb == true){PjlsCsgwhb = false;}
      if(theryPDcFM == true){theryPDcFM = false;}
      if(lbFhUiQZbj == true){lbFhUiQZbj = false;}
      if(PASjqyEDfc == true){PASjqyEDfc = false;}
      if(NrjIPbKyNH == true){NrjIPbKyNH = false;}
      if(diZDcneEXT == true){diZDcneEXT = false;}
      if(cGTxMsOtBz == true){cGTxMsOtBz = false;}
      if(LzxbzsqwRr == true){LzxbzsqwRr = false;}
      if(YRLTGfZPHD == true){YRLTGfZPHD = false;}
      if(TzfLAGXlwV == true){TzfLAGXlwV = false;}
      if(NPwOwdlyDj == true){NPwOwdlyDj = false;}
      if(whleuKtAqf == true){whleuKtAqf = false;}
      if(TzmyeLTkar == true){TzmyeLTkar = false;}
      if(UFAweIVxXb == true){UFAweIVxXb = false;}
      if(tbLWGlNAQp == true){tbLWGlNAQp = false;}
      if(LXtQCNcyij == true){LXtQCNcyij = false;}
      if(KBWLOqhpzl == true){KBWLOqhpzl = false;}
      if(oxcPlqmPrs == true){oxcPlqmPrs = false;}
      if(ySTkfxKjtR == true){ySTkfxKjtR = false;}
      if(fXNmRrEAIP == true){fXNmRrEAIP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEFGYSUBLU
{ 
  void CPoJFdAAJS()
  { 
      bool hWFOyYEKuQ = false;
      bool OQENISqNtJ = false;
      bool WPLcirtrJq = false;
      bool IOYlgdebLa = false;
      bool oBVCsRtNtG = false;
      bool zuQucRLbfF = false;
      bool eLBEIAqRfd = false;
      bool nPCSTVsIjR = false;
      bool yfyDrMydJO = false;
      bool SCuGwdARtr = false;
      bool ZcgPSjsxaH = false;
      bool YCrOHzNxLu = false;
      bool CNHRLkTuWp = false;
      bool VaOqqUyhkI = false;
      bool TADCpQKgyx = false;
      bool PCGypMUPEg = false;
      bool PxZjlxmAWl = false;
      bool AeMDbBJFat = false;
      bool alxZZSUQBd = false;
      bool zidDrWZSQs = false;
      string BTeVbolLPO;
      string tisaiigVVa;
      string zuFPSaHxZs;
      string dsEEfIxdZC;
      string KueWhzTGjz;
      string iApHAGNOCA;
      string gnkWkBdoua;
      string lDuTQDPihS;
      string HANaJdDxDZ;
      string uiaYUVKIlf;
      string VeLINfEVpw;
      string pegisfaJNH;
      string yfkUfDbWyu;
      string sHwBxboENd;
      string YgGHiPBqfo;
      string tAudhotpcK;
      string DhXuCihelQ;
      string qVwjhRZdlP;
      string BkpJAsMRTI;
      string hybDZqILEz;
      if(BTeVbolLPO == VeLINfEVpw){hWFOyYEKuQ = true;}
      else if(VeLINfEVpw == BTeVbolLPO){ZcgPSjsxaH = true;}
      if(tisaiigVVa == pegisfaJNH){OQENISqNtJ = true;}
      else if(pegisfaJNH == tisaiigVVa){YCrOHzNxLu = true;}
      if(zuFPSaHxZs == yfkUfDbWyu){WPLcirtrJq = true;}
      else if(yfkUfDbWyu == zuFPSaHxZs){CNHRLkTuWp = true;}
      if(dsEEfIxdZC == sHwBxboENd){IOYlgdebLa = true;}
      else if(sHwBxboENd == dsEEfIxdZC){VaOqqUyhkI = true;}
      if(KueWhzTGjz == YgGHiPBqfo){oBVCsRtNtG = true;}
      else if(YgGHiPBqfo == KueWhzTGjz){TADCpQKgyx = true;}
      if(iApHAGNOCA == tAudhotpcK){zuQucRLbfF = true;}
      else if(tAudhotpcK == iApHAGNOCA){PCGypMUPEg = true;}
      if(gnkWkBdoua == DhXuCihelQ){eLBEIAqRfd = true;}
      else if(DhXuCihelQ == gnkWkBdoua){PxZjlxmAWl = true;}
      if(lDuTQDPihS == qVwjhRZdlP){nPCSTVsIjR = true;}
      if(HANaJdDxDZ == BkpJAsMRTI){yfyDrMydJO = true;}
      if(uiaYUVKIlf == hybDZqILEz){SCuGwdARtr = true;}
      while(qVwjhRZdlP == lDuTQDPihS){AeMDbBJFat = true;}
      while(BkpJAsMRTI == BkpJAsMRTI){alxZZSUQBd = true;}
      while(hybDZqILEz == hybDZqILEz){zidDrWZSQs = true;}
      if(hWFOyYEKuQ == true){hWFOyYEKuQ = false;}
      if(OQENISqNtJ == true){OQENISqNtJ = false;}
      if(WPLcirtrJq == true){WPLcirtrJq = false;}
      if(IOYlgdebLa == true){IOYlgdebLa = false;}
      if(oBVCsRtNtG == true){oBVCsRtNtG = false;}
      if(zuQucRLbfF == true){zuQucRLbfF = false;}
      if(eLBEIAqRfd == true){eLBEIAqRfd = false;}
      if(nPCSTVsIjR == true){nPCSTVsIjR = false;}
      if(yfyDrMydJO == true){yfyDrMydJO = false;}
      if(SCuGwdARtr == true){SCuGwdARtr = false;}
      if(ZcgPSjsxaH == true){ZcgPSjsxaH = false;}
      if(YCrOHzNxLu == true){YCrOHzNxLu = false;}
      if(CNHRLkTuWp == true){CNHRLkTuWp = false;}
      if(VaOqqUyhkI == true){VaOqqUyhkI = false;}
      if(TADCpQKgyx == true){TADCpQKgyx = false;}
      if(PCGypMUPEg == true){PCGypMUPEg = false;}
      if(PxZjlxmAWl == true){PxZjlxmAWl = false;}
      if(AeMDbBJFat == true){AeMDbBJFat = false;}
      if(alxZZSUQBd == true){alxZZSUQBd = false;}
      if(zidDrWZSQs == true){zidDrWZSQs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVTKAKQCXI
{ 
  void rViRAWNucK()
  { 
      bool iXjpjOrpAL = false;
      bool CeQpSAQXfV = false;
      bool RMbFDbtknK = false;
      bool RXURzmTMZo = false;
      bool cWHdWICngV = false;
      bool DmTxUWwdmI = false;
      bool TGBpteKzpe = false;
      bool fExpsuExiu = false;
      bool YFESGeDXwc = false;
      bool qoZRVVURjr = false;
      bool xDyBozocDY = false;
      bool RyuriNBhjO = false;
      bool amCMnqeeUW = false;
      bool amMqxUHDdG = false;
      bool oaTWKrtgiH = false;
      bool UlgUQKBkNx = false;
      bool UKIfyelDuN = false;
      bool GyEcZzSeCu = false;
      bool wxwMCnFqZl = false;
      bool TVogleRnXf = false;
      string CwIILLkEOP;
      string YUacUFbNeY;
      string GMxbqoymeh;
      string GozcyPRMAa;
      string ORPIqGPUTU;
      string lPaldozfQV;
      string MxZfJiVyeF;
      string mOMDJoxnkk;
      string YdSKwpOMzJ;
      string QkudNRqjzH;
      string jRpOgWCWbn;
      string rKufxidOiS;
      string TIyVoCSior;
      string xMocAGnEdY;
      string nrjKRFpPge;
      string ncAfmaTUZe;
      string DShjqeVRep;
      string uZkJebXnEi;
      string LDCKDUMIpY;
      string mSezVUKATm;
      if(CwIILLkEOP == jRpOgWCWbn){iXjpjOrpAL = true;}
      else if(jRpOgWCWbn == CwIILLkEOP){xDyBozocDY = true;}
      if(YUacUFbNeY == rKufxidOiS){CeQpSAQXfV = true;}
      else if(rKufxidOiS == YUacUFbNeY){RyuriNBhjO = true;}
      if(GMxbqoymeh == TIyVoCSior){RMbFDbtknK = true;}
      else if(TIyVoCSior == GMxbqoymeh){amCMnqeeUW = true;}
      if(GozcyPRMAa == xMocAGnEdY){RXURzmTMZo = true;}
      else if(xMocAGnEdY == GozcyPRMAa){amMqxUHDdG = true;}
      if(ORPIqGPUTU == nrjKRFpPge){cWHdWICngV = true;}
      else if(nrjKRFpPge == ORPIqGPUTU){oaTWKrtgiH = true;}
      if(lPaldozfQV == ncAfmaTUZe){DmTxUWwdmI = true;}
      else if(ncAfmaTUZe == lPaldozfQV){UlgUQKBkNx = true;}
      if(MxZfJiVyeF == DShjqeVRep){TGBpteKzpe = true;}
      else if(DShjqeVRep == MxZfJiVyeF){UKIfyelDuN = true;}
      if(mOMDJoxnkk == uZkJebXnEi){fExpsuExiu = true;}
      if(YdSKwpOMzJ == LDCKDUMIpY){YFESGeDXwc = true;}
      if(QkudNRqjzH == mSezVUKATm){qoZRVVURjr = true;}
      while(uZkJebXnEi == mOMDJoxnkk){GyEcZzSeCu = true;}
      while(LDCKDUMIpY == LDCKDUMIpY){wxwMCnFqZl = true;}
      while(mSezVUKATm == mSezVUKATm){TVogleRnXf = true;}
      if(iXjpjOrpAL == true){iXjpjOrpAL = false;}
      if(CeQpSAQXfV == true){CeQpSAQXfV = false;}
      if(RMbFDbtknK == true){RMbFDbtknK = false;}
      if(RXURzmTMZo == true){RXURzmTMZo = false;}
      if(cWHdWICngV == true){cWHdWICngV = false;}
      if(DmTxUWwdmI == true){DmTxUWwdmI = false;}
      if(TGBpteKzpe == true){TGBpteKzpe = false;}
      if(fExpsuExiu == true){fExpsuExiu = false;}
      if(YFESGeDXwc == true){YFESGeDXwc = false;}
      if(qoZRVVURjr == true){qoZRVVURjr = false;}
      if(xDyBozocDY == true){xDyBozocDY = false;}
      if(RyuriNBhjO == true){RyuriNBhjO = false;}
      if(amCMnqeeUW == true){amCMnqeeUW = false;}
      if(amMqxUHDdG == true){amMqxUHDdG = false;}
      if(oaTWKrtgiH == true){oaTWKrtgiH = false;}
      if(UlgUQKBkNx == true){UlgUQKBkNx = false;}
      if(UKIfyelDuN == true){UKIfyelDuN = false;}
      if(GyEcZzSeCu == true){GyEcZzSeCu = false;}
      if(wxwMCnFqZl == true){wxwMCnFqZl = false;}
      if(TVogleRnXf == true){TVogleRnXf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IITBRTZNZE
{ 
  void FRcKkKiVLp()
  { 
      bool OMMKEoZOfu = false;
      bool zUgoZTPTfR = false;
      bool XZjeNmiJlm = false;
      bool NJyWrYFGHI = false;
      bool xLocfjTPxn = false;
      bool cuNgznbgwR = false;
      bool FQbrhpWJxB = false;
      bool NJMWULkGzd = false;
      bool STLxKSwQWD = false;
      bool wXJpDfjxtp = false;
      bool NJRuaTipMn = false;
      bool DVhSykEdgP = false;
      bool sFmtFozVTn = false;
      bool bmMIQJCQWq = false;
      bool iGDizapprS = false;
      bool bGPewHVWpk = false;
      bool TMWYLPJYCo = false;
      bool hnGofmBDte = false;
      bool zIdBMVXgMI = false;
      bool meZlXWieWi = false;
      string QDAyrTsJRt;
      string lgUuZFdyEX;
      string lxYzrZiluF;
      string nedbYSaXkr;
      string bkMYEfxOUw;
      string inxBUTdAGR;
      string jHOMGGCsVG;
      string eGMMwAjAuL;
      string bUQzWAhcHF;
      string oZRSHUWASx;
      string cErOQbakFT;
      string idFtpPpPpF;
      string YZlQRFotEb;
      string djhxiXbBht;
      string ZwWnVKUWcr;
      string dGJMYCSbwK;
      string lggdoywIKS;
      string mngufcDxtG;
      string kRQMxWaVYf;
      string EAFXIrPszX;
      if(QDAyrTsJRt == cErOQbakFT){OMMKEoZOfu = true;}
      else if(cErOQbakFT == QDAyrTsJRt){NJRuaTipMn = true;}
      if(lgUuZFdyEX == idFtpPpPpF){zUgoZTPTfR = true;}
      else if(idFtpPpPpF == lgUuZFdyEX){DVhSykEdgP = true;}
      if(lxYzrZiluF == YZlQRFotEb){XZjeNmiJlm = true;}
      else if(YZlQRFotEb == lxYzrZiluF){sFmtFozVTn = true;}
      if(nedbYSaXkr == djhxiXbBht){NJyWrYFGHI = true;}
      else if(djhxiXbBht == nedbYSaXkr){bmMIQJCQWq = true;}
      if(bkMYEfxOUw == ZwWnVKUWcr){xLocfjTPxn = true;}
      else if(ZwWnVKUWcr == bkMYEfxOUw){iGDizapprS = true;}
      if(inxBUTdAGR == dGJMYCSbwK){cuNgznbgwR = true;}
      else if(dGJMYCSbwK == inxBUTdAGR){bGPewHVWpk = true;}
      if(jHOMGGCsVG == lggdoywIKS){FQbrhpWJxB = true;}
      else if(lggdoywIKS == jHOMGGCsVG){TMWYLPJYCo = true;}
      if(eGMMwAjAuL == mngufcDxtG){NJMWULkGzd = true;}
      if(bUQzWAhcHF == kRQMxWaVYf){STLxKSwQWD = true;}
      if(oZRSHUWASx == EAFXIrPszX){wXJpDfjxtp = true;}
      while(mngufcDxtG == eGMMwAjAuL){hnGofmBDte = true;}
      while(kRQMxWaVYf == kRQMxWaVYf){zIdBMVXgMI = true;}
      while(EAFXIrPszX == EAFXIrPszX){meZlXWieWi = true;}
      if(OMMKEoZOfu == true){OMMKEoZOfu = false;}
      if(zUgoZTPTfR == true){zUgoZTPTfR = false;}
      if(XZjeNmiJlm == true){XZjeNmiJlm = false;}
      if(NJyWrYFGHI == true){NJyWrYFGHI = false;}
      if(xLocfjTPxn == true){xLocfjTPxn = false;}
      if(cuNgznbgwR == true){cuNgznbgwR = false;}
      if(FQbrhpWJxB == true){FQbrhpWJxB = false;}
      if(NJMWULkGzd == true){NJMWULkGzd = false;}
      if(STLxKSwQWD == true){STLxKSwQWD = false;}
      if(wXJpDfjxtp == true){wXJpDfjxtp = false;}
      if(NJRuaTipMn == true){NJRuaTipMn = false;}
      if(DVhSykEdgP == true){DVhSykEdgP = false;}
      if(sFmtFozVTn == true){sFmtFozVTn = false;}
      if(bmMIQJCQWq == true){bmMIQJCQWq = false;}
      if(iGDizapprS == true){iGDizapprS = false;}
      if(bGPewHVWpk == true){bGPewHVWpk = false;}
      if(TMWYLPJYCo == true){TMWYLPJYCo = false;}
      if(hnGofmBDte == true){hnGofmBDte = false;}
      if(zIdBMVXgMI == true){zIdBMVXgMI = false;}
      if(meZlXWieWi == true){meZlXWieWi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLJIQQRFDT
{ 
  void CIgAAHpJsd()
  { 
      bool mZORdOccll = false;
      bool rfwErufaCY = false;
      bool GFRNZfjFtK = false;
      bool SmjQFwhSLw = false;
      bool tJTbBkrHof = false;
      bool SIcUJhHAqy = false;
      bool eWhaTFufzw = false;
      bool MMOGewloMn = false;
      bool mcPNrJJOGW = false;
      bool ngbMRXarIu = false;
      bool pMIsSFsWpM = false;
      bool uRnCKCGTiJ = false;
      bool wfYbHfkCnG = false;
      bool UtgRyZTWul = false;
      bool QlYsbWsYBP = false;
      bool QHIyyJngkm = false;
      bool UqiirBjVEk = false;
      bool hjYxrKHezk = false;
      bool lMAYpNkhSn = false;
      bool llkIRZDoBZ = false;
      string ceWrUZALIE;
      string FDBTFkdaEM;
      string Gbrszqrurp;
      string FuIBozTbFX;
      string WTEUzTgBwH;
      string MenbYBlcrc;
      string gFTRzJtzeG;
      string RCUgomWXse;
      string JqzkcZHgcm;
      string NpibpRzmVp;
      string ZhWooKJHlk;
      string dNjNTpFinZ;
      string CNWqrbSspX;
      string njCDFbUJuS;
      string PAtqJzGVIA;
      string LQywnLKexN;
      string qQQOxsLgHq;
      string VwmVJBSehs;
      string VwjpLXlFOs;
      string QoLhaziftQ;
      if(ceWrUZALIE == ZhWooKJHlk){mZORdOccll = true;}
      else if(ZhWooKJHlk == ceWrUZALIE){pMIsSFsWpM = true;}
      if(FDBTFkdaEM == dNjNTpFinZ){rfwErufaCY = true;}
      else if(dNjNTpFinZ == FDBTFkdaEM){uRnCKCGTiJ = true;}
      if(Gbrszqrurp == CNWqrbSspX){GFRNZfjFtK = true;}
      else if(CNWqrbSspX == Gbrszqrurp){wfYbHfkCnG = true;}
      if(FuIBozTbFX == njCDFbUJuS){SmjQFwhSLw = true;}
      else if(njCDFbUJuS == FuIBozTbFX){UtgRyZTWul = true;}
      if(WTEUzTgBwH == PAtqJzGVIA){tJTbBkrHof = true;}
      else if(PAtqJzGVIA == WTEUzTgBwH){QlYsbWsYBP = true;}
      if(MenbYBlcrc == LQywnLKexN){SIcUJhHAqy = true;}
      else if(LQywnLKexN == MenbYBlcrc){QHIyyJngkm = true;}
      if(gFTRzJtzeG == qQQOxsLgHq){eWhaTFufzw = true;}
      else if(qQQOxsLgHq == gFTRzJtzeG){UqiirBjVEk = true;}
      if(RCUgomWXse == VwmVJBSehs){MMOGewloMn = true;}
      if(JqzkcZHgcm == VwjpLXlFOs){mcPNrJJOGW = true;}
      if(NpibpRzmVp == QoLhaziftQ){ngbMRXarIu = true;}
      while(VwmVJBSehs == RCUgomWXse){hjYxrKHezk = true;}
      while(VwjpLXlFOs == VwjpLXlFOs){lMAYpNkhSn = true;}
      while(QoLhaziftQ == QoLhaziftQ){llkIRZDoBZ = true;}
      if(mZORdOccll == true){mZORdOccll = false;}
      if(rfwErufaCY == true){rfwErufaCY = false;}
      if(GFRNZfjFtK == true){GFRNZfjFtK = false;}
      if(SmjQFwhSLw == true){SmjQFwhSLw = false;}
      if(tJTbBkrHof == true){tJTbBkrHof = false;}
      if(SIcUJhHAqy == true){SIcUJhHAqy = false;}
      if(eWhaTFufzw == true){eWhaTFufzw = false;}
      if(MMOGewloMn == true){MMOGewloMn = false;}
      if(mcPNrJJOGW == true){mcPNrJJOGW = false;}
      if(ngbMRXarIu == true){ngbMRXarIu = false;}
      if(pMIsSFsWpM == true){pMIsSFsWpM = false;}
      if(uRnCKCGTiJ == true){uRnCKCGTiJ = false;}
      if(wfYbHfkCnG == true){wfYbHfkCnG = false;}
      if(UtgRyZTWul == true){UtgRyZTWul = false;}
      if(QlYsbWsYBP == true){QlYsbWsYBP = false;}
      if(QHIyyJngkm == true){QHIyyJngkm = false;}
      if(UqiirBjVEk == true){UqiirBjVEk = false;}
      if(hjYxrKHezk == true){hjYxrKHezk = false;}
      if(lMAYpNkhSn == true){lMAYpNkhSn = false;}
      if(llkIRZDoBZ == true){llkIRZDoBZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUFUUINAZP
{ 
  void yziaVfFGbF()
  { 
      bool MXiePLcLCU = false;
      bool MGKQGOpnoc = false;
      bool xZfxuEhfYo = false;
      bool bCCTeNbzfQ = false;
      bool DGEthfqgug = false;
      bool fNmnQmqljK = false;
      bool cwmMsKDqlr = false;
      bool lqHXYqVkPO = false;
      bool NBjqINOOCr = false;
      bool VpOVmHTqBX = false;
      bool czuDtoFPPZ = false;
      bool QGVUxbLuEe = false;
      bool uonsVwbljQ = false;
      bool WeirlNFgxT = false;
      bool IzzcaPTtXL = false;
      bool uYlWbnLCgy = false;
      bool NTeyClXdii = false;
      bool VexkWwoLSG = false;
      bool cgNYVxrMPy = false;
      bool CDzzFnTAZn = false;
      string rwmJAXTnNa;
      string xgfgIyhhbd;
      string lLKzbYQbUo;
      string SpZJZdQnhg;
      string ZGrZVXqNYd;
      string GMyqggkmha;
      string GqSXIHGWGd;
      string hsztDeSkcD;
      string gDCphFqhbs;
      string scGHahmUQO;
      string QUHtwMNEmB;
      string NAJetDoboD;
      string QYtNkEmrTV;
      string rxTOlMwHtU;
      string rltaesSbMW;
      string sKeNyqZsJr;
      string ZVjRJPfurg;
      string HghTLdeThr;
      string kLewcgSGPt;
      string lCyCuWBbQO;
      if(rwmJAXTnNa == QUHtwMNEmB){MXiePLcLCU = true;}
      else if(QUHtwMNEmB == rwmJAXTnNa){czuDtoFPPZ = true;}
      if(xgfgIyhhbd == NAJetDoboD){MGKQGOpnoc = true;}
      else if(NAJetDoboD == xgfgIyhhbd){QGVUxbLuEe = true;}
      if(lLKzbYQbUo == QYtNkEmrTV){xZfxuEhfYo = true;}
      else if(QYtNkEmrTV == lLKzbYQbUo){uonsVwbljQ = true;}
      if(SpZJZdQnhg == rxTOlMwHtU){bCCTeNbzfQ = true;}
      else if(rxTOlMwHtU == SpZJZdQnhg){WeirlNFgxT = true;}
      if(ZGrZVXqNYd == rltaesSbMW){DGEthfqgug = true;}
      else if(rltaesSbMW == ZGrZVXqNYd){IzzcaPTtXL = true;}
      if(GMyqggkmha == sKeNyqZsJr){fNmnQmqljK = true;}
      else if(sKeNyqZsJr == GMyqggkmha){uYlWbnLCgy = true;}
      if(GqSXIHGWGd == ZVjRJPfurg){cwmMsKDqlr = true;}
      else if(ZVjRJPfurg == GqSXIHGWGd){NTeyClXdii = true;}
      if(hsztDeSkcD == HghTLdeThr){lqHXYqVkPO = true;}
      if(gDCphFqhbs == kLewcgSGPt){NBjqINOOCr = true;}
      if(scGHahmUQO == lCyCuWBbQO){VpOVmHTqBX = true;}
      while(HghTLdeThr == hsztDeSkcD){VexkWwoLSG = true;}
      while(kLewcgSGPt == kLewcgSGPt){cgNYVxrMPy = true;}
      while(lCyCuWBbQO == lCyCuWBbQO){CDzzFnTAZn = true;}
      if(MXiePLcLCU == true){MXiePLcLCU = false;}
      if(MGKQGOpnoc == true){MGKQGOpnoc = false;}
      if(xZfxuEhfYo == true){xZfxuEhfYo = false;}
      if(bCCTeNbzfQ == true){bCCTeNbzfQ = false;}
      if(DGEthfqgug == true){DGEthfqgug = false;}
      if(fNmnQmqljK == true){fNmnQmqljK = false;}
      if(cwmMsKDqlr == true){cwmMsKDqlr = false;}
      if(lqHXYqVkPO == true){lqHXYqVkPO = false;}
      if(NBjqINOOCr == true){NBjqINOOCr = false;}
      if(VpOVmHTqBX == true){VpOVmHTqBX = false;}
      if(czuDtoFPPZ == true){czuDtoFPPZ = false;}
      if(QGVUxbLuEe == true){QGVUxbLuEe = false;}
      if(uonsVwbljQ == true){uonsVwbljQ = false;}
      if(WeirlNFgxT == true){WeirlNFgxT = false;}
      if(IzzcaPTtXL == true){IzzcaPTtXL = false;}
      if(uYlWbnLCgy == true){uYlWbnLCgy = false;}
      if(NTeyClXdii == true){NTeyClXdii = false;}
      if(VexkWwoLSG == true){VexkWwoLSG = false;}
      if(cgNYVxrMPy == true){cgNYVxrMPy = false;}
      if(CDzzFnTAZn == true){CDzzFnTAZn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXJSZJNYDQ
{ 
  void ygKsqFPEGw()
  { 
      bool HLzsHxYTGf = false;
      bool NAOEGSIUIR = false;
      bool tETZlnUzRI = false;
      bool buHLgipEjw = false;
      bool DbKkpepytT = false;
      bool ZumjZCrYGS = false;
      bool cZBxESrDWW = false;
      bool cEkLOStiiH = false;
      bool xVEyifHWkd = false;
      bool qQxQTcaMgX = false;
      bool mmbXpVJbVH = false;
      bool IIpzVHVDOX = false;
      bool LURsfMGUrk = false;
      bool qgCLUKtgHM = false;
      bool VeBcUhZxuM = false;
      bool HWxIMRViqc = false;
      bool OojjQbGeeK = false;
      bool MouBBfTnXx = false;
      bool lIYedTisyC = false;
      bool oLodyguRMs = false;
      string yanytoVHwg;
      string dCYzOskRaY;
      string LpBfIbBtFa;
      string yasXgkeFml;
      string ReuLwESInI;
      string FtsZdHZIpR;
      string naBViCJBSc;
      string OfeoGgupiD;
      string IrGxUDgStY;
      string LWOUxpdZbs;
      string uRpKtZPETx;
      string MiZlJwUDAe;
      string VpHsRrRJrQ;
      string CVNoIpCwDu;
      string nczxMcwcLB;
      string VZYxXEKwsB;
      string HFMDtqUkdS;
      string tXAFqrqKgn;
      string uoxqtcwQQD;
      string fFDBmhQwCU;
      if(yanytoVHwg == uRpKtZPETx){HLzsHxYTGf = true;}
      else if(uRpKtZPETx == yanytoVHwg){mmbXpVJbVH = true;}
      if(dCYzOskRaY == MiZlJwUDAe){NAOEGSIUIR = true;}
      else if(MiZlJwUDAe == dCYzOskRaY){IIpzVHVDOX = true;}
      if(LpBfIbBtFa == VpHsRrRJrQ){tETZlnUzRI = true;}
      else if(VpHsRrRJrQ == LpBfIbBtFa){LURsfMGUrk = true;}
      if(yasXgkeFml == CVNoIpCwDu){buHLgipEjw = true;}
      else if(CVNoIpCwDu == yasXgkeFml){qgCLUKtgHM = true;}
      if(ReuLwESInI == nczxMcwcLB){DbKkpepytT = true;}
      else if(nczxMcwcLB == ReuLwESInI){VeBcUhZxuM = true;}
      if(FtsZdHZIpR == VZYxXEKwsB){ZumjZCrYGS = true;}
      else if(VZYxXEKwsB == FtsZdHZIpR){HWxIMRViqc = true;}
      if(naBViCJBSc == HFMDtqUkdS){cZBxESrDWW = true;}
      else if(HFMDtqUkdS == naBViCJBSc){OojjQbGeeK = true;}
      if(OfeoGgupiD == tXAFqrqKgn){cEkLOStiiH = true;}
      if(IrGxUDgStY == uoxqtcwQQD){xVEyifHWkd = true;}
      if(LWOUxpdZbs == fFDBmhQwCU){qQxQTcaMgX = true;}
      while(tXAFqrqKgn == OfeoGgupiD){MouBBfTnXx = true;}
      while(uoxqtcwQQD == uoxqtcwQQD){lIYedTisyC = true;}
      while(fFDBmhQwCU == fFDBmhQwCU){oLodyguRMs = true;}
      if(HLzsHxYTGf == true){HLzsHxYTGf = false;}
      if(NAOEGSIUIR == true){NAOEGSIUIR = false;}
      if(tETZlnUzRI == true){tETZlnUzRI = false;}
      if(buHLgipEjw == true){buHLgipEjw = false;}
      if(DbKkpepytT == true){DbKkpepytT = false;}
      if(ZumjZCrYGS == true){ZumjZCrYGS = false;}
      if(cZBxESrDWW == true){cZBxESrDWW = false;}
      if(cEkLOStiiH == true){cEkLOStiiH = false;}
      if(xVEyifHWkd == true){xVEyifHWkd = false;}
      if(qQxQTcaMgX == true){qQxQTcaMgX = false;}
      if(mmbXpVJbVH == true){mmbXpVJbVH = false;}
      if(IIpzVHVDOX == true){IIpzVHVDOX = false;}
      if(LURsfMGUrk == true){LURsfMGUrk = false;}
      if(qgCLUKtgHM == true){qgCLUKtgHM = false;}
      if(VeBcUhZxuM == true){VeBcUhZxuM = false;}
      if(HWxIMRViqc == true){HWxIMRViqc = false;}
      if(OojjQbGeeK == true){OojjQbGeeK = false;}
      if(MouBBfTnXx == true){MouBBfTnXx = false;}
      if(lIYedTisyC == true){lIYedTisyC = false;}
      if(oLodyguRMs == true){oLodyguRMs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCSODLNUND
{ 
  void agYhHEbyYK()
  { 
      bool SHVfYKNVzX = false;
      bool yVbbXWspVf = false;
      bool TbToLwPOub = false;
      bool mUTXwIuzQN = false;
      bool oamxyxZzgj = false;
      bool BntpypmfUb = false;
      bool tyZXkcBEfO = false;
      bool bsYHproWpO = false;
      bool VQgLazacZF = false;
      bool UOeoSpBOMV = false;
      bool uVTRIHOlAF = false;
      bool BQoGGdROxk = false;
      bool CYdZtMNjnz = false;
      bool qZJUSzwOCS = false;
      bool kncTEEYYho = false;
      bool YmRbTWqtXu = false;
      bool sdyAOaHUmG = false;
      bool gCLdANuKUp = false;
      bool moBzaDHhAw = false;
      bool HCqGYGpcEc = false;
      string FoKAGZQYng;
      string iTmqtxOYcZ;
      string haAcTLtwOd;
      string ICrTyshKOX;
      string iDghyGZioS;
      string SZzMweoggt;
      string fTJJXfaSrA;
      string PEKFqdsSeM;
      string kLHwKiDfXT;
      string EAdTrOtXKS;
      string eGpnCOPsVS;
      string lWCTITLMyo;
      string buuXwOapNb;
      string iVHMgdUTsu;
      string SKJFhgyJKX;
      string DgYUpjLRqn;
      string nYftiQOpmd;
      string zrTDVRkppO;
      string QRfoYCwlVx;
      string SCbFHtdPWR;
      if(FoKAGZQYng == eGpnCOPsVS){SHVfYKNVzX = true;}
      else if(eGpnCOPsVS == FoKAGZQYng){uVTRIHOlAF = true;}
      if(iTmqtxOYcZ == lWCTITLMyo){yVbbXWspVf = true;}
      else if(lWCTITLMyo == iTmqtxOYcZ){BQoGGdROxk = true;}
      if(haAcTLtwOd == buuXwOapNb){TbToLwPOub = true;}
      else if(buuXwOapNb == haAcTLtwOd){CYdZtMNjnz = true;}
      if(ICrTyshKOX == iVHMgdUTsu){mUTXwIuzQN = true;}
      else if(iVHMgdUTsu == ICrTyshKOX){qZJUSzwOCS = true;}
      if(iDghyGZioS == SKJFhgyJKX){oamxyxZzgj = true;}
      else if(SKJFhgyJKX == iDghyGZioS){kncTEEYYho = true;}
      if(SZzMweoggt == DgYUpjLRqn){BntpypmfUb = true;}
      else if(DgYUpjLRqn == SZzMweoggt){YmRbTWqtXu = true;}
      if(fTJJXfaSrA == nYftiQOpmd){tyZXkcBEfO = true;}
      else if(nYftiQOpmd == fTJJXfaSrA){sdyAOaHUmG = true;}
      if(PEKFqdsSeM == zrTDVRkppO){bsYHproWpO = true;}
      if(kLHwKiDfXT == QRfoYCwlVx){VQgLazacZF = true;}
      if(EAdTrOtXKS == SCbFHtdPWR){UOeoSpBOMV = true;}
      while(zrTDVRkppO == PEKFqdsSeM){gCLdANuKUp = true;}
      while(QRfoYCwlVx == QRfoYCwlVx){moBzaDHhAw = true;}
      while(SCbFHtdPWR == SCbFHtdPWR){HCqGYGpcEc = true;}
      if(SHVfYKNVzX == true){SHVfYKNVzX = false;}
      if(yVbbXWspVf == true){yVbbXWspVf = false;}
      if(TbToLwPOub == true){TbToLwPOub = false;}
      if(mUTXwIuzQN == true){mUTXwIuzQN = false;}
      if(oamxyxZzgj == true){oamxyxZzgj = false;}
      if(BntpypmfUb == true){BntpypmfUb = false;}
      if(tyZXkcBEfO == true){tyZXkcBEfO = false;}
      if(bsYHproWpO == true){bsYHproWpO = false;}
      if(VQgLazacZF == true){VQgLazacZF = false;}
      if(UOeoSpBOMV == true){UOeoSpBOMV = false;}
      if(uVTRIHOlAF == true){uVTRIHOlAF = false;}
      if(BQoGGdROxk == true){BQoGGdROxk = false;}
      if(CYdZtMNjnz == true){CYdZtMNjnz = false;}
      if(qZJUSzwOCS == true){qZJUSzwOCS = false;}
      if(kncTEEYYho == true){kncTEEYYho = false;}
      if(YmRbTWqtXu == true){YmRbTWqtXu = false;}
      if(sdyAOaHUmG == true){sdyAOaHUmG = false;}
      if(gCLdANuKUp == true){gCLdANuKUp = false;}
      if(moBzaDHhAw == true){moBzaDHhAw = false;}
      if(HCqGYGpcEc == true){HCqGYGpcEc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGECFQFOII
{ 
  void VhywNcqaOq()
  { 
      bool jKzkfxjWcB = false;
      bool RUOFbifqmj = false;
      bool thEHxQoJJZ = false;
      bool NAQqXzebKG = false;
      bool JlQctmhRbr = false;
      bool CdOgrBGrmP = false;
      bool IZNCmREWhb = false;
      bool EEffaIRaMK = false;
      bool iWhRXikizV = false;
      bool smnuxiXNpb = false;
      bool iLjznyyhGj = false;
      bool jeecglrueE = false;
      bool gUWLiQPjiq = false;
      bool jDjjbXlhdZ = false;
      bool jCcPlNHKNK = false;
      bool qbhkuNnYQW = false;
      bool hNzPzftuBJ = false;
      bool zJRFTerGZU = false;
      bool JFVXAHVzoN = false;
      bool iNRGqWCNQF = false;
      string mmIHIrrAQe;
      string gTQLPXmMZj;
      string eQdWIGqgQk;
      string YVYagccTFu;
      string QlObiLTpRj;
      string gCyZMWJlyB;
      string BKjeGLupdl;
      string tTGeTrBBmx;
      string mAOfDVXzOK;
      string TqUEtFBjVX;
      string PdLeoNuTFT;
      string UHyBOAuEaj;
      string mubTSDyCjO;
      string qRfPgJnipp;
      string aEstoLsTps;
      string JxIljUBrMl;
      string OriqcDbiTE;
      string MLNkIiCgdH;
      string JeMqEsIseM;
      string HwWEahVCQl;
      if(mmIHIrrAQe == PdLeoNuTFT){jKzkfxjWcB = true;}
      else if(PdLeoNuTFT == mmIHIrrAQe){iLjznyyhGj = true;}
      if(gTQLPXmMZj == UHyBOAuEaj){RUOFbifqmj = true;}
      else if(UHyBOAuEaj == gTQLPXmMZj){jeecglrueE = true;}
      if(eQdWIGqgQk == mubTSDyCjO){thEHxQoJJZ = true;}
      else if(mubTSDyCjO == eQdWIGqgQk){gUWLiQPjiq = true;}
      if(YVYagccTFu == qRfPgJnipp){NAQqXzebKG = true;}
      else if(qRfPgJnipp == YVYagccTFu){jDjjbXlhdZ = true;}
      if(QlObiLTpRj == aEstoLsTps){JlQctmhRbr = true;}
      else if(aEstoLsTps == QlObiLTpRj){jCcPlNHKNK = true;}
      if(gCyZMWJlyB == JxIljUBrMl){CdOgrBGrmP = true;}
      else if(JxIljUBrMl == gCyZMWJlyB){qbhkuNnYQW = true;}
      if(BKjeGLupdl == OriqcDbiTE){IZNCmREWhb = true;}
      else if(OriqcDbiTE == BKjeGLupdl){hNzPzftuBJ = true;}
      if(tTGeTrBBmx == MLNkIiCgdH){EEffaIRaMK = true;}
      if(mAOfDVXzOK == JeMqEsIseM){iWhRXikizV = true;}
      if(TqUEtFBjVX == HwWEahVCQl){smnuxiXNpb = true;}
      while(MLNkIiCgdH == tTGeTrBBmx){zJRFTerGZU = true;}
      while(JeMqEsIseM == JeMqEsIseM){JFVXAHVzoN = true;}
      while(HwWEahVCQl == HwWEahVCQl){iNRGqWCNQF = true;}
      if(jKzkfxjWcB == true){jKzkfxjWcB = false;}
      if(RUOFbifqmj == true){RUOFbifqmj = false;}
      if(thEHxQoJJZ == true){thEHxQoJJZ = false;}
      if(NAQqXzebKG == true){NAQqXzebKG = false;}
      if(JlQctmhRbr == true){JlQctmhRbr = false;}
      if(CdOgrBGrmP == true){CdOgrBGrmP = false;}
      if(IZNCmREWhb == true){IZNCmREWhb = false;}
      if(EEffaIRaMK == true){EEffaIRaMK = false;}
      if(iWhRXikizV == true){iWhRXikizV = false;}
      if(smnuxiXNpb == true){smnuxiXNpb = false;}
      if(iLjznyyhGj == true){iLjznyyhGj = false;}
      if(jeecglrueE == true){jeecglrueE = false;}
      if(gUWLiQPjiq == true){gUWLiQPjiq = false;}
      if(jDjjbXlhdZ == true){jDjjbXlhdZ = false;}
      if(jCcPlNHKNK == true){jCcPlNHKNK = false;}
      if(qbhkuNnYQW == true){qbhkuNnYQW = false;}
      if(hNzPzftuBJ == true){hNzPzftuBJ = false;}
      if(zJRFTerGZU == true){zJRFTerGZU = false;}
      if(JFVXAHVzoN == true){JFVXAHVzoN = false;}
      if(iNRGqWCNQF == true){iNRGqWCNQF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJLIJLRYJR
{ 
  void ZTnGYPGMNn()
  { 
      bool IejJnWcsGu = false;
      bool CZAyZKmmsf = false;
      bool ohQntJeWqe = false;
      bool MhNeXsTzzq = false;
      bool EUJIlgkcPX = false;
      bool bQMwcaOuPd = false;
      bool rGCbiTLVaf = false;
      bool qmnCaTXHBM = false;
      bool XBHSCuVQBw = false;
      bool eXjUzyShZS = false;
      bool UPCigocKVI = false;
      bool CGtCGpzjYm = false;
      bool yuTdASDSDc = false;
      bool BphirIzXkM = false;
      bool SLurtYcgOI = false;
      bool yhImUZuXhO = false;
      bool lKGrHMYLKx = false;
      bool pazMUlzbjb = false;
      bool pWDtdSgtOS = false;
      bool NaoWaHEDkg = false;
      string VtcfHPgFxd;
      string wXimKNAWiN;
      string PMKOsSlwtx;
      string uTDbOEBLVt;
      string cBonlPCmXi;
      string USnlAIjOmn;
      string dkLzhcUHXG;
      string LoBnkOXVbc;
      string QyXLcceQbG;
      string TmXgPqppFJ;
      string uuORWeQzBl;
      string kNmKWeNAWF;
      string xDeRlYRTYs;
      string XgPRgViGnx;
      string LfOpUGANKj;
      string dpSAMqPxey;
      string NwaINDxUcA;
      string wGMZtQoowf;
      string YDJnOhOPEo;
      string GlboiOEGbR;
      if(VtcfHPgFxd == uuORWeQzBl){IejJnWcsGu = true;}
      else if(uuORWeQzBl == VtcfHPgFxd){UPCigocKVI = true;}
      if(wXimKNAWiN == kNmKWeNAWF){CZAyZKmmsf = true;}
      else if(kNmKWeNAWF == wXimKNAWiN){CGtCGpzjYm = true;}
      if(PMKOsSlwtx == xDeRlYRTYs){ohQntJeWqe = true;}
      else if(xDeRlYRTYs == PMKOsSlwtx){yuTdASDSDc = true;}
      if(uTDbOEBLVt == XgPRgViGnx){MhNeXsTzzq = true;}
      else if(XgPRgViGnx == uTDbOEBLVt){BphirIzXkM = true;}
      if(cBonlPCmXi == LfOpUGANKj){EUJIlgkcPX = true;}
      else if(LfOpUGANKj == cBonlPCmXi){SLurtYcgOI = true;}
      if(USnlAIjOmn == dpSAMqPxey){bQMwcaOuPd = true;}
      else if(dpSAMqPxey == USnlAIjOmn){yhImUZuXhO = true;}
      if(dkLzhcUHXG == NwaINDxUcA){rGCbiTLVaf = true;}
      else if(NwaINDxUcA == dkLzhcUHXG){lKGrHMYLKx = true;}
      if(LoBnkOXVbc == wGMZtQoowf){qmnCaTXHBM = true;}
      if(QyXLcceQbG == YDJnOhOPEo){XBHSCuVQBw = true;}
      if(TmXgPqppFJ == GlboiOEGbR){eXjUzyShZS = true;}
      while(wGMZtQoowf == LoBnkOXVbc){pazMUlzbjb = true;}
      while(YDJnOhOPEo == YDJnOhOPEo){pWDtdSgtOS = true;}
      while(GlboiOEGbR == GlboiOEGbR){NaoWaHEDkg = true;}
      if(IejJnWcsGu == true){IejJnWcsGu = false;}
      if(CZAyZKmmsf == true){CZAyZKmmsf = false;}
      if(ohQntJeWqe == true){ohQntJeWqe = false;}
      if(MhNeXsTzzq == true){MhNeXsTzzq = false;}
      if(EUJIlgkcPX == true){EUJIlgkcPX = false;}
      if(bQMwcaOuPd == true){bQMwcaOuPd = false;}
      if(rGCbiTLVaf == true){rGCbiTLVaf = false;}
      if(qmnCaTXHBM == true){qmnCaTXHBM = false;}
      if(XBHSCuVQBw == true){XBHSCuVQBw = false;}
      if(eXjUzyShZS == true){eXjUzyShZS = false;}
      if(UPCigocKVI == true){UPCigocKVI = false;}
      if(CGtCGpzjYm == true){CGtCGpzjYm = false;}
      if(yuTdASDSDc == true){yuTdASDSDc = false;}
      if(BphirIzXkM == true){BphirIzXkM = false;}
      if(SLurtYcgOI == true){SLurtYcgOI = false;}
      if(yhImUZuXhO == true){yhImUZuXhO = false;}
      if(lKGrHMYLKx == true){lKGrHMYLKx = false;}
      if(pazMUlzbjb == true){pazMUlzbjb = false;}
      if(pWDtdSgtOS == true){pWDtdSgtOS = false;}
      if(NaoWaHEDkg == true){NaoWaHEDkg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSOBDOSDEC
{ 
  void TDXQuMbiUa()
  { 
      bool LFGYfehQuH = false;
      bool tINntQHXUh = false;
      bool ydMNozOJlQ = false;
      bool DJEWTPBNSU = false;
      bool AnheoAcICk = false;
      bool HsbEFhssjg = false;
      bool PXddDjDqTd = false;
      bool OtFzhKugXn = false;
      bool WGHBIJhAQl = false;
      bool VIclFbJDaE = false;
      bool wknXVNnbVu = false;
      bool lLUuKIQcVt = false;
      bool CDahIGQTtG = false;
      bool AqGSqkSifu = false;
      bool VFdUzJmgaw = false;
      bool KghgCsJGPO = false;
      bool wTgPtuFBDY = false;
      bool pgwZXwYGhy = false;
      bool TirxuTIYQy = false;
      bool bMTQyBYOZD = false;
      string IbJJAAtIWD;
      string mqCJzgUbfk;
      string IUqoXobimw;
      string BqtNHSmWoR;
      string ccsTjSkYzj;
      string joISTnkTkL;
      string YKVZBuxoBg;
      string tylOHebWFE;
      string ECiCMLiasT;
      string gTkdrRHSRo;
      string VuWSplCsKo;
      string MNOgGVbSNo;
      string LVuhzZMIVp;
      string XJFPiIfPMZ;
      string JpQEHTEEWW;
      string pnEbczzoTP;
      string YsXURCHyxx;
      string pLGmfVFqaf;
      string VIlzziEdli;
      string IpwwBPRwmE;
      if(IbJJAAtIWD == VuWSplCsKo){LFGYfehQuH = true;}
      else if(VuWSplCsKo == IbJJAAtIWD){wknXVNnbVu = true;}
      if(mqCJzgUbfk == MNOgGVbSNo){tINntQHXUh = true;}
      else if(MNOgGVbSNo == mqCJzgUbfk){lLUuKIQcVt = true;}
      if(IUqoXobimw == LVuhzZMIVp){ydMNozOJlQ = true;}
      else if(LVuhzZMIVp == IUqoXobimw){CDahIGQTtG = true;}
      if(BqtNHSmWoR == XJFPiIfPMZ){DJEWTPBNSU = true;}
      else if(XJFPiIfPMZ == BqtNHSmWoR){AqGSqkSifu = true;}
      if(ccsTjSkYzj == JpQEHTEEWW){AnheoAcICk = true;}
      else if(JpQEHTEEWW == ccsTjSkYzj){VFdUzJmgaw = true;}
      if(joISTnkTkL == pnEbczzoTP){HsbEFhssjg = true;}
      else if(pnEbczzoTP == joISTnkTkL){KghgCsJGPO = true;}
      if(YKVZBuxoBg == YsXURCHyxx){PXddDjDqTd = true;}
      else if(YsXURCHyxx == YKVZBuxoBg){wTgPtuFBDY = true;}
      if(tylOHebWFE == pLGmfVFqaf){OtFzhKugXn = true;}
      if(ECiCMLiasT == VIlzziEdli){WGHBIJhAQl = true;}
      if(gTkdrRHSRo == IpwwBPRwmE){VIclFbJDaE = true;}
      while(pLGmfVFqaf == tylOHebWFE){pgwZXwYGhy = true;}
      while(VIlzziEdli == VIlzziEdli){TirxuTIYQy = true;}
      while(IpwwBPRwmE == IpwwBPRwmE){bMTQyBYOZD = true;}
      if(LFGYfehQuH == true){LFGYfehQuH = false;}
      if(tINntQHXUh == true){tINntQHXUh = false;}
      if(ydMNozOJlQ == true){ydMNozOJlQ = false;}
      if(DJEWTPBNSU == true){DJEWTPBNSU = false;}
      if(AnheoAcICk == true){AnheoAcICk = false;}
      if(HsbEFhssjg == true){HsbEFhssjg = false;}
      if(PXddDjDqTd == true){PXddDjDqTd = false;}
      if(OtFzhKugXn == true){OtFzhKugXn = false;}
      if(WGHBIJhAQl == true){WGHBIJhAQl = false;}
      if(VIclFbJDaE == true){VIclFbJDaE = false;}
      if(wknXVNnbVu == true){wknXVNnbVu = false;}
      if(lLUuKIQcVt == true){lLUuKIQcVt = false;}
      if(CDahIGQTtG == true){CDahIGQTtG = false;}
      if(AqGSqkSifu == true){AqGSqkSifu = false;}
      if(VFdUzJmgaw == true){VFdUzJmgaw = false;}
      if(KghgCsJGPO == true){KghgCsJGPO = false;}
      if(wTgPtuFBDY == true){wTgPtuFBDY = false;}
      if(pgwZXwYGhy == true){pgwZXwYGhy = false;}
      if(TirxuTIYQy == true){TirxuTIYQy = false;}
      if(bMTQyBYOZD == true){bMTQyBYOZD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THUARSZIGN
{ 
  void EXsEjsHBlV()
  { 
      bool UXSpuMmPrn = false;
      bool JmmKwfGHup = false;
      bool tSjwxEJmUx = false;
      bool NRBMbpEeqa = false;
      bool JhzqaXOyLV = false;
      bool dCkYpCnWrp = false;
      bool DzutZrlZhF = false;
      bool bbPUgLTsUZ = false;
      bool oLbzSLfcVZ = false;
      bool BgmBWKlEQi = false;
      bool lnQFsClQre = false;
      bool huCSAqXwbO = false;
      bool LIEHDtoOxV = false;
      bool ZObkmAtVFQ = false;
      bool ZPjqqGeUAe = false;
      bool locBXcjICy = false;
      bool NWSVFTSQez = false;
      bool wCqLowYMPx = false;
      bool OUORjjlaNK = false;
      bool QlSGCCwOlX = false;
      string DePBTlAhMB;
      string RZHTEZKeXa;
      string RYOeNEsRnD;
      string xDwQkVdNmn;
      string upXaAzPtSI;
      string WnRfudPjnO;
      string shsIENdphi;
      string wwrifbAndO;
      string ozzffIlPVG;
      string GsZXuNwPVm;
      string VYLjMauhAS;
      string dbGZYthNbu;
      string aNTabCWTnR;
      string ekRqsPmPSF;
      string MDODcemzzB;
      string ehmZLHEkHK;
      string DbthmrJOgJ;
      string GRuWhXyQxx;
      string OWUlmxyqek;
      string LCIHCkJfPk;
      if(DePBTlAhMB == VYLjMauhAS){UXSpuMmPrn = true;}
      else if(VYLjMauhAS == DePBTlAhMB){lnQFsClQre = true;}
      if(RZHTEZKeXa == dbGZYthNbu){JmmKwfGHup = true;}
      else if(dbGZYthNbu == RZHTEZKeXa){huCSAqXwbO = true;}
      if(RYOeNEsRnD == aNTabCWTnR){tSjwxEJmUx = true;}
      else if(aNTabCWTnR == RYOeNEsRnD){LIEHDtoOxV = true;}
      if(xDwQkVdNmn == ekRqsPmPSF){NRBMbpEeqa = true;}
      else if(ekRqsPmPSF == xDwQkVdNmn){ZObkmAtVFQ = true;}
      if(upXaAzPtSI == MDODcemzzB){JhzqaXOyLV = true;}
      else if(MDODcemzzB == upXaAzPtSI){ZPjqqGeUAe = true;}
      if(WnRfudPjnO == ehmZLHEkHK){dCkYpCnWrp = true;}
      else if(ehmZLHEkHK == WnRfudPjnO){locBXcjICy = true;}
      if(shsIENdphi == DbthmrJOgJ){DzutZrlZhF = true;}
      else if(DbthmrJOgJ == shsIENdphi){NWSVFTSQez = true;}
      if(wwrifbAndO == GRuWhXyQxx){bbPUgLTsUZ = true;}
      if(ozzffIlPVG == OWUlmxyqek){oLbzSLfcVZ = true;}
      if(GsZXuNwPVm == LCIHCkJfPk){BgmBWKlEQi = true;}
      while(GRuWhXyQxx == wwrifbAndO){wCqLowYMPx = true;}
      while(OWUlmxyqek == OWUlmxyqek){OUORjjlaNK = true;}
      while(LCIHCkJfPk == LCIHCkJfPk){QlSGCCwOlX = true;}
      if(UXSpuMmPrn == true){UXSpuMmPrn = false;}
      if(JmmKwfGHup == true){JmmKwfGHup = false;}
      if(tSjwxEJmUx == true){tSjwxEJmUx = false;}
      if(NRBMbpEeqa == true){NRBMbpEeqa = false;}
      if(JhzqaXOyLV == true){JhzqaXOyLV = false;}
      if(dCkYpCnWrp == true){dCkYpCnWrp = false;}
      if(DzutZrlZhF == true){DzutZrlZhF = false;}
      if(bbPUgLTsUZ == true){bbPUgLTsUZ = false;}
      if(oLbzSLfcVZ == true){oLbzSLfcVZ = false;}
      if(BgmBWKlEQi == true){BgmBWKlEQi = false;}
      if(lnQFsClQre == true){lnQFsClQre = false;}
      if(huCSAqXwbO == true){huCSAqXwbO = false;}
      if(LIEHDtoOxV == true){LIEHDtoOxV = false;}
      if(ZObkmAtVFQ == true){ZObkmAtVFQ = false;}
      if(ZPjqqGeUAe == true){ZPjqqGeUAe = false;}
      if(locBXcjICy == true){locBXcjICy = false;}
      if(NWSVFTSQez == true){NWSVFTSQez = false;}
      if(wCqLowYMPx == true){wCqLowYMPx = false;}
      if(OUORjjlaNK == true){OUORjjlaNK = false;}
      if(QlSGCCwOlX == true){QlSGCCwOlX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEYEHFVGDT
{ 
  void JigmgiVSxQ()
  { 
      bool jFyLrDYmao = false;
      bool DNcWYZyRJD = false;
      bool HYXArAWbJI = false;
      bool OHtCqZFtAA = false;
      bool pDBQZwXWds = false;
      bool pKTGSLgxTr = false;
      bool gxcSawTafy = false;
      bool UDQIMEWGZu = false;
      bool bAxQRDmmif = false;
      bool sHaITrZhpd = false;
      bool bwpfXlsKsN = false;
      bool naXXPgzMAW = false;
      bool JfqAFNcIoT = false;
      bool enQwTfJRrf = false;
      bool JbtVqRjCrm = false;
      bool rMhSTwFoZK = false;
      bool JkVYizJaEj = false;
      bool WhUUMglVIm = false;
      bool daPCaSGxbW = false;
      bool aTqgVYGUlr = false;
      string YAnkQhSXIU;
      string rXxNwdNKSs;
      string KWlZENHHKZ;
      string JaSFgzOGuc;
      string pCZYbVopFi;
      string RonorCOOfC;
      string ZLNiKRFrgw;
      string PGOpDHxNxi;
      string YQBaIUlcMd;
      string kAZsCdopNK;
      string QxJJTKaylk;
      string FAQxdIJlap;
      string ebeCLPgVmY;
      string SGzlSbHrHx;
      string snqbYjicOs;
      string UDPXfnRGyE;
      string dFLNRyAdeC;
      string BQdcwqkDca;
      string fDGsDOpbGd;
      string KBtCTnbcJa;
      if(YAnkQhSXIU == QxJJTKaylk){jFyLrDYmao = true;}
      else if(QxJJTKaylk == YAnkQhSXIU){bwpfXlsKsN = true;}
      if(rXxNwdNKSs == FAQxdIJlap){DNcWYZyRJD = true;}
      else if(FAQxdIJlap == rXxNwdNKSs){naXXPgzMAW = true;}
      if(KWlZENHHKZ == ebeCLPgVmY){HYXArAWbJI = true;}
      else if(ebeCLPgVmY == KWlZENHHKZ){JfqAFNcIoT = true;}
      if(JaSFgzOGuc == SGzlSbHrHx){OHtCqZFtAA = true;}
      else if(SGzlSbHrHx == JaSFgzOGuc){enQwTfJRrf = true;}
      if(pCZYbVopFi == snqbYjicOs){pDBQZwXWds = true;}
      else if(snqbYjicOs == pCZYbVopFi){JbtVqRjCrm = true;}
      if(RonorCOOfC == UDPXfnRGyE){pKTGSLgxTr = true;}
      else if(UDPXfnRGyE == RonorCOOfC){rMhSTwFoZK = true;}
      if(ZLNiKRFrgw == dFLNRyAdeC){gxcSawTafy = true;}
      else if(dFLNRyAdeC == ZLNiKRFrgw){JkVYizJaEj = true;}
      if(PGOpDHxNxi == BQdcwqkDca){UDQIMEWGZu = true;}
      if(YQBaIUlcMd == fDGsDOpbGd){bAxQRDmmif = true;}
      if(kAZsCdopNK == KBtCTnbcJa){sHaITrZhpd = true;}
      while(BQdcwqkDca == PGOpDHxNxi){WhUUMglVIm = true;}
      while(fDGsDOpbGd == fDGsDOpbGd){daPCaSGxbW = true;}
      while(KBtCTnbcJa == KBtCTnbcJa){aTqgVYGUlr = true;}
      if(jFyLrDYmao == true){jFyLrDYmao = false;}
      if(DNcWYZyRJD == true){DNcWYZyRJD = false;}
      if(HYXArAWbJI == true){HYXArAWbJI = false;}
      if(OHtCqZFtAA == true){OHtCqZFtAA = false;}
      if(pDBQZwXWds == true){pDBQZwXWds = false;}
      if(pKTGSLgxTr == true){pKTGSLgxTr = false;}
      if(gxcSawTafy == true){gxcSawTafy = false;}
      if(UDQIMEWGZu == true){UDQIMEWGZu = false;}
      if(bAxQRDmmif == true){bAxQRDmmif = false;}
      if(sHaITrZhpd == true){sHaITrZhpd = false;}
      if(bwpfXlsKsN == true){bwpfXlsKsN = false;}
      if(naXXPgzMAW == true){naXXPgzMAW = false;}
      if(JfqAFNcIoT == true){JfqAFNcIoT = false;}
      if(enQwTfJRrf == true){enQwTfJRrf = false;}
      if(JbtVqRjCrm == true){JbtVqRjCrm = false;}
      if(rMhSTwFoZK == true){rMhSTwFoZK = false;}
      if(JkVYizJaEj == true){JkVYizJaEj = false;}
      if(WhUUMglVIm == true){WhUUMglVIm = false;}
      if(daPCaSGxbW == true){daPCaSGxbW = false;}
      if(aTqgVYGUlr == true){aTqgVYGUlr = false;}
    } 
}; 
