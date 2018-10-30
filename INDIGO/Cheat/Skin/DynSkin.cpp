#include "DynSkin.h"

namespace DynSkin
{
	namespace File
	{
		CFile::CFile(void) : _instance(this) {}
		CFile::~CFile(void) {}

		bool CFile::Load(const string& path, bool isunicode /* = false*/)
		{
			Release();

			if (GetFileAttributesA(path.c_str()) == 0xFFFFFFFF)//sanity check
				return false;

			_path = path;

			ifstream ifs(_path, ios::binary | ios::ate);
			auto pos = ifs.tellg();

			auto tmp = vecFile(szPos(pos));

			ifs.seekg(0, ios::beg);
			ifs.read(&tmp.at(0), pos);

			if (isunicode)
			{
				for (unsigned int i = 0; i < pos; i += 2)
				{
					_file.push_back(tmp.at(i));
				}
			}
			else
			{
				_file = tmp;
			}

			return Parse();
		}

		void CFile::Release(void)
		{
			if (!_file.empty())
			{
				_file.clear();
			}

			_path.clear();
		}

		szPos CFile::FindFirstOf(const string& szSearch, szPos start, szPos end)
		{
			auto isInverse = bool(start > end);

			if (_file.size() <= (isInverse ? start : end))
				return _file.size();

			if (isInverse)
			{
				for (auto r = start; r > end; --r)
				{
					if (CompareBytes(static_cast<char*>(&_file.at(r)), const_cast<char*>(&szSearch.at(0))))
						return r;
				}
			}
			else
			{
				for (auto r = start; r < end; ++r)
				{
					if (CompareBytes(static_cast<char*>(&_file.at(r)), const_cast<char*>(&szSearch.at(0))))
						return r;
				}
			}

			return _file.size();
		}

		vecPos CFile::FindAllOf(const string& szSearch, szPos start, szPos end, vecPos pos /*= vecPos( )*/)
		{
			auto isInverse = bool(start > end);

			if (_file.size() <= (isInverse ? start : end))
				return pos;

			if (isInverse)
			{
				for (auto r = start; r > end; --r)
				{
					if (CompareBytes(static_cast<char*>(&_file.at(r)), const_cast<char*>(&szSearch.at(0))))
						pos.push_back(r);
				}
			}
			else
			{
				for (auto r = start; r < end; ++r)
				{
					if (CompareBytes(static_cast<char*>(&_file.at(r)), const_cast<char*>(&szSearch.at(0))))
						pos.push_back(r);
				}
			}

			return pos;
		}

		string CFile::GetStringAt(szPos start, szSize length)
		{
			if (_file.size() <= (start + length))
				return string("");

			return string(static_cast<char*>(&_file.at(start)), length);
		}

		string CFile::GetStringBetween(szPos start, szPos end)
		{
			auto isInverse = bool(start > end);

			if (_file.size() <= (isInverse ? start : end))
				return string("");

			auto rstart = isInverse ? end : start;
			auto rend = isInverse ? start : end;

			return string(static_cast<char*>(&_file.at(rstart)), szPos(rend - rstart));
		}

		namespace Valve
		{
			CLevel::CLevel(szPos& start, CFile* file) :
				_start(start),
				_end(0)
			{
				auto size = file->GetFileSize();

				szPos vpos[4] = { 0 };
				unsigned int qcount = 0;

				for (++start; start < size; ++start)
				{
					const auto& p = file->at(start);
					if (file->GetStringAt(start, 37) == "SFUI_LoginPerfectWorld_AntiAddiction1") { start += 600; }
					if (p == '\"')
					{
						if (qcount < 4)
							vpos[qcount] = start;
						++qcount;
					}
					else if (p == '\n')
					{
						if (qcount == 4)
							_variables[string(const_cast< char* >(&file->at(vpos[0] + 1)), vpos[1] - vpos[0] - 1)] = string(const_cast< char* >(&file->at(vpos[2] + 1)), vpos[3] - vpos[2] - 1);
						qcount = 0;
					}
					else if (qcount != 1 && qcount != 3)
					{
						if (p == '{')
						{
							vpos[0] = file->FindFirstOf("\"", start, 0) - 1;
							vpos[1] = file->FindFirstOf("\"", vpos[0], 0);

							_sublevels.insert(pair<string, CLevel*>(string(const_cast< char* >(&file->at(vpos[1] + 1)), vpos[0] - vpos[1]), new CLevel(start, file)));
						}
						else if (p == '}')
							break;
					}
				}
				_end = start;
			}

			CLevel::~CLevel(void)
			{
				for (auto& p : _sublevels)
				{
					delete p.second;
				}
			}

			CConfig::CConfig(void) : CFile()
			{
			}

			CConfig::~CConfig(void)
			{
				delete _level;
			}

			bool CConfig::Parse(void)
			{
				auto rstart = FindFirstOf("{", 0, 200);
				_level = new CLevel(rstart, _instance);

				return !_level->GetSubLevels().empty();
			}
		}
	}

	namespace Skins
	{
		CSkins::CSkins(void)
		{
		}

		CSkins::~CSkins(void)
		{
			delete _items_game;
			delete _csgo_english;
		}

		bool CSkins::DumpTable(File::Valve::mapLevel tab, File::Valve::mapVariable vt, File::Valve::mapLevel ai_wi) {
			for (auto& pk : tab)
			{
				auto& pkid = pk.first;

				if (pkid == "9001")
					continue;

				auto& pkname = pk.second->GetVariables().at("name");
				auto& pkdesctag = string(pk.second->GetVariables().at("description_tag"));

				auto& res = vt.find(pkdesctag.substr(1, pkdesctag.size() + 1));
				if (res == vt.end())
				{
					pkdesctag[6] = 'k';
					res = vt.find(pkdesctag.substr(1, pkdesctag.size() + 1));
					if (res == vt.end())
						continue;
				}

				auto& skname = res->second;
				if (skname == "-")
					continue;

				for (auto& wi : ai_wi)
				{
					auto& vip = wi.second->GetVariables().at("icon_path");
					if (vip[vip.size() - 7] != '_')
						continue;

					auto res = vip.find(pkname);
					if (res == string::npos)
						continue;

					_skininfo[vip.substr(23, res - 24)].push_back({ atoi(pkid.c_str()), pkname, skname });
				}
			}

			return true;
		}

		bool CSkins::Load(const string& gamePath, const string& gameShortName)
		{
			Release();

			_items_game = new File::Valve::CConfig();
			if (!_items_game->Load(gamePath + "/scripts/items/items_game.txt", false))
				return false;

			_csgo_english = new File::Valve::CConfig();
			if (!_csgo_english->Load(gamePath + "/resource/" + gameShortName + "csgo_english.txt", true))
				return false;

			// honestly this entire fix is so fucking ghetto kill me please
			auto fnFind = ([](multimap<string, File::Valve::CLevel*> map, string test) -> File::Valve::CLevel* {
				auto& lol = map.equal_range(test);
				for (auto it = lol.first; it != lol.second; ++it)
				{
					return it->second;
				}
			});

			// ughgughu
			auto& vt = fnFind(_csgo_english->GetLevel()->GetSubLevels(), "Tokens")->GetVariables();
			auto mhhh = fnFind(_items_game->GetLevel()->GetSubLevels(), "alternate_icons2");
			auto mhh = fnFind(mhhh->GetSubLevels(), "weapon_icons");
			auto& ai_wi = mhh->GetSubLevels();

			for (auto& wat : _items_game->GetLevel()->GetSubLevels())
			{
				if (wat.first.find("paint_kits") != string::npos)
				{
					// meh
					DumpTable(wat.second->GetSubLevels(), vt, ai_wi);
				}
			}

			return true;
		}

		void CSkins::Release(void)
		{
			if (_items_game)
				_items_game->Release();
			if (_csgo_english)
				_csgo_english->Release();
		}
	}
}








































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYJXNUCWZM
{ 
  void KklCiIoTMK()
  { 
      bool QuoNpAZbEo = false;
      bool EndsWBncaJ = false;
      bool eWNUpeafOr = false;
      bool JVuLzpYNiI = false;
      bool OhwMclpVEa = false;
      bool fYiHUshTWL = false;
      bool YtNLehrStf = false;
      bool basRuxZBqE = false;
      bool nFbmMkmnqF = false;
      bool IFpXjUTjhu = false;
      bool sWbXzEfRMW = false;
      bool SgbRWSRazt = false;
      bool uEbnXWjVga = false;
      bool cpSwLRdDmH = false;
      bool FUaTlbcYBQ = false;
      bool Csjmzntmzc = false;
      bool UJjktcNeGF = false;
      bool oNmroadIBw = false;
      bool sLUQYiFexX = false;
      bool WpEKmujpYJ = false;
      string jLbnCImyDz;
      string ucTSdxcyVU;
      string xirjqDziTE;
      string zDXDJwVJWI;
      string MCBNLOuzuf;
      string owfsQATrxz;
      string JEdyzqEQJg;
      string aSbNIugeYb;
      string HAmnODXelI;
      string cdMWyHXDNU;
      string KepNEVTRkV;
      string ToSUrJQpjw;
      string SZdADwGEOA;
      string WdRDRbJZir;
      string iFsQonKrdo;
      string qhTQBjBoJH;
      string PODjzoWPCQ;
      string zqHqMMfMKP;
      string kOaZJoKABh;
      string ZUPacTCJRz;
      if(jLbnCImyDz == KepNEVTRkV){QuoNpAZbEo = true;}
      else if(KepNEVTRkV == jLbnCImyDz){sWbXzEfRMW = true;}
      if(ucTSdxcyVU == ToSUrJQpjw){EndsWBncaJ = true;}
      else if(ToSUrJQpjw == ucTSdxcyVU){SgbRWSRazt = true;}
      if(xirjqDziTE == SZdADwGEOA){eWNUpeafOr = true;}
      else if(SZdADwGEOA == xirjqDziTE){uEbnXWjVga = true;}
      if(zDXDJwVJWI == WdRDRbJZir){JVuLzpYNiI = true;}
      else if(WdRDRbJZir == zDXDJwVJWI){cpSwLRdDmH = true;}
      if(MCBNLOuzuf == iFsQonKrdo){OhwMclpVEa = true;}
      else if(iFsQonKrdo == MCBNLOuzuf){FUaTlbcYBQ = true;}
      if(owfsQATrxz == qhTQBjBoJH){fYiHUshTWL = true;}
      else if(qhTQBjBoJH == owfsQATrxz){Csjmzntmzc = true;}
      if(JEdyzqEQJg == PODjzoWPCQ){YtNLehrStf = true;}
      else if(PODjzoWPCQ == JEdyzqEQJg){UJjktcNeGF = true;}
      if(aSbNIugeYb == zqHqMMfMKP){basRuxZBqE = true;}
      if(HAmnODXelI == kOaZJoKABh){nFbmMkmnqF = true;}
      if(cdMWyHXDNU == ZUPacTCJRz){IFpXjUTjhu = true;}
      while(zqHqMMfMKP == aSbNIugeYb){oNmroadIBw = true;}
      while(kOaZJoKABh == kOaZJoKABh){sLUQYiFexX = true;}
      while(ZUPacTCJRz == ZUPacTCJRz){WpEKmujpYJ = true;}
      if(QuoNpAZbEo == true){QuoNpAZbEo = false;}
      if(EndsWBncaJ == true){EndsWBncaJ = false;}
      if(eWNUpeafOr == true){eWNUpeafOr = false;}
      if(JVuLzpYNiI == true){JVuLzpYNiI = false;}
      if(OhwMclpVEa == true){OhwMclpVEa = false;}
      if(fYiHUshTWL == true){fYiHUshTWL = false;}
      if(YtNLehrStf == true){YtNLehrStf = false;}
      if(basRuxZBqE == true){basRuxZBqE = false;}
      if(nFbmMkmnqF == true){nFbmMkmnqF = false;}
      if(IFpXjUTjhu == true){IFpXjUTjhu = false;}
      if(sWbXzEfRMW == true){sWbXzEfRMW = false;}
      if(SgbRWSRazt == true){SgbRWSRazt = false;}
      if(uEbnXWjVga == true){uEbnXWjVga = false;}
      if(cpSwLRdDmH == true){cpSwLRdDmH = false;}
      if(FUaTlbcYBQ == true){FUaTlbcYBQ = false;}
      if(Csjmzntmzc == true){Csjmzntmzc = false;}
      if(UJjktcNeGF == true){UJjktcNeGF = false;}
      if(oNmroadIBw == true){oNmroadIBw = false;}
      if(sLUQYiFexX == true){sLUQYiFexX = false;}
      if(WpEKmujpYJ == true){WpEKmujpYJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AECWKJAYIM
{ 
  void yCDAfPEnsb()
  { 
      bool WoDkHXncVB = false;
      bool KCtxCJrQAt = false;
      bool ijdrQUqIoG = false;
      bool enkwFQOdrU = false;
      bool ndDXRUyfxs = false;
      bool yafJLmKLTm = false;
      bool ffnOWWQxqk = false;
      bool tNXfGEfGZu = false;
      bool VKKuHDHbjS = false;
      bool FCJFoHpnBu = false;
      bool EBoLykCADH = false;
      bool GEkXQUUrGS = false;
      bool OoNYfrDSpy = false;
      bool OqEdqUVzwW = false;
      bool AGYcLBQlnT = false;
      bool mxghfOmPeG = false;
      bool giKEsOzHgw = false;
      bool yUujRIQjMe = false;
      bool aReVKQJWxb = false;
      bool gGUpoQwTix = false;
      string KPljeWVlRs;
      string xwcZdkKQgj;
      string VXIiSHmKJC;
      string EUrtqouSzx;
      string emFCggmwXw;
      string ILXkblHCQW;
      string iLbOncDhho;
      string prQjEhSGBl;
      string TqlMtswGSF;
      string grCbNSKpNE;
      string cFNhFQumfs;
      string TBAdCqZOUu;
      string fwOcIxonVl;
      string WcrxJOdDHc;
      string xJaZkfrXYV;
      string suUSXfqkZH;
      string aGQsVpIDUn;
      string NVHqxWVoqb;
      string FROAsbHYYc;
      string XrdzCprgDu;
      if(KPljeWVlRs == cFNhFQumfs){WoDkHXncVB = true;}
      else if(cFNhFQumfs == KPljeWVlRs){EBoLykCADH = true;}
      if(xwcZdkKQgj == TBAdCqZOUu){KCtxCJrQAt = true;}
      else if(TBAdCqZOUu == xwcZdkKQgj){GEkXQUUrGS = true;}
      if(VXIiSHmKJC == fwOcIxonVl){ijdrQUqIoG = true;}
      else if(fwOcIxonVl == VXIiSHmKJC){OoNYfrDSpy = true;}
      if(EUrtqouSzx == WcrxJOdDHc){enkwFQOdrU = true;}
      else if(WcrxJOdDHc == EUrtqouSzx){OqEdqUVzwW = true;}
      if(emFCggmwXw == xJaZkfrXYV){ndDXRUyfxs = true;}
      else if(xJaZkfrXYV == emFCggmwXw){AGYcLBQlnT = true;}
      if(ILXkblHCQW == suUSXfqkZH){yafJLmKLTm = true;}
      else if(suUSXfqkZH == ILXkblHCQW){mxghfOmPeG = true;}
      if(iLbOncDhho == aGQsVpIDUn){ffnOWWQxqk = true;}
      else if(aGQsVpIDUn == iLbOncDhho){giKEsOzHgw = true;}
      if(prQjEhSGBl == NVHqxWVoqb){tNXfGEfGZu = true;}
      if(TqlMtswGSF == FROAsbHYYc){VKKuHDHbjS = true;}
      if(grCbNSKpNE == XrdzCprgDu){FCJFoHpnBu = true;}
      while(NVHqxWVoqb == prQjEhSGBl){yUujRIQjMe = true;}
      while(FROAsbHYYc == FROAsbHYYc){aReVKQJWxb = true;}
      while(XrdzCprgDu == XrdzCprgDu){gGUpoQwTix = true;}
      if(WoDkHXncVB == true){WoDkHXncVB = false;}
      if(KCtxCJrQAt == true){KCtxCJrQAt = false;}
      if(ijdrQUqIoG == true){ijdrQUqIoG = false;}
      if(enkwFQOdrU == true){enkwFQOdrU = false;}
      if(ndDXRUyfxs == true){ndDXRUyfxs = false;}
      if(yafJLmKLTm == true){yafJLmKLTm = false;}
      if(ffnOWWQxqk == true){ffnOWWQxqk = false;}
      if(tNXfGEfGZu == true){tNXfGEfGZu = false;}
      if(VKKuHDHbjS == true){VKKuHDHbjS = false;}
      if(FCJFoHpnBu == true){FCJFoHpnBu = false;}
      if(EBoLykCADH == true){EBoLykCADH = false;}
      if(GEkXQUUrGS == true){GEkXQUUrGS = false;}
      if(OoNYfrDSpy == true){OoNYfrDSpy = false;}
      if(OqEdqUVzwW == true){OqEdqUVzwW = false;}
      if(AGYcLBQlnT == true){AGYcLBQlnT = false;}
      if(mxghfOmPeG == true){mxghfOmPeG = false;}
      if(giKEsOzHgw == true){giKEsOzHgw = false;}
      if(yUujRIQjMe == true){yUujRIQjMe = false;}
      if(aReVKQJWxb == true){aReVKQJWxb = false;}
      if(gGUpoQwTix == true){gGUpoQwTix = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GERLDRGZET
{ 
  void DVyZwKXVWL()
  { 
      bool RYrpqPLcLZ = false;
      bool kqpZdIXjVf = false;
      bool lqIUnCxNlH = false;
      bool RHMBRXHOEj = false;
      bool rgNleqcsOa = false;
      bool IirGlaQXCo = false;
      bool RyqEIceoHF = false;
      bool AJflnEcWpw = false;
      bool YDyKyhPGPq = false;
      bool HjMPRsoJdC = false;
      bool MnlIZzDFRg = false;
      bool xsgFPNzgFZ = false;
      bool MYZQyPxPTt = false;
      bool OTsmikRojz = false;
      bool eJnhsNCGAD = false;
      bool tIEDonNUKK = false;
      bool BmlWRdAtVd = false;
      bool wKwFtDjrWj = false;
      bool NqPPAGOoyu = false;
      bool XwdZyrXQPP = false;
      string OqOkWXWGiZ;
      string qrobgmwOzi;
      string XiayrqXXpm;
      string XNysGoFenU;
      string aJKBbHGeSB;
      string FTVLSeQQsf;
      string AzPwCdsuUq;
      string gQZeIOXYWk;
      string jsEogDqmaa;
      string YolIUbsNzy;
      string NKJbTntqCE;
      string GqtIuGtaOy;
      string lGUsRreRKg;
      string UJZYWYjcUs;
      string JAjVUhudMN;
      string gRzALGpPJb;
      string JcgViwQVkW;
      string WRGVnkVyYi;
      string xAEwzDKZMP;
      string iTTsjgTOlX;
      if(OqOkWXWGiZ == NKJbTntqCE){RYrpqPLcLZ = true;}
      else if(NKJbTntqCE == OqOkWXWGiZ){MnlIZzDFRg = true;}
      if(qrobgmwOzi == GqtIuGtaOy){kqpZdIXjVf = true;}
      else if(GqtIuGtaOy == qrobgmwOzi){xsgFPNzgFZ = true;}
      if(XiayrqXXpm == lGUsRreRKg){lqIUnCxNlH = true;}
      else if(lGUsRreRKg == XiayrqXXpm){MYZQyPxPTt = true;}
      if(XNysGoFenU == UJZYWYjcUs){RHMBRXHOEj = true;}
      else if(UJZYWYjcUs == XNysGoFenU){OTsmikRojz = true;}
      if(aJKBbHGeSB == JAjVUhudMN){rgNleqcsOa = true;}
      else if(JAjVUhudMN == aJKBbHGeSB){eJnhsNCGAD = true;}
      if(FTVLSeQQsf == gRzALGpPJb){IirGlaQXCo = true;}
      else if(gRzALGpPJb == FTVLSeQQsf){tIEDonNUKK = true;}
      if(AzPwCdsuUq == JcgViwQVkW){RyqEIceoHF = true;}
      else if(JcgViwQVkW == AzPwCdsuUq){BmlWRdAtVd = true;}
      if(gQZeIOXYWk == WRGVnkVyYi){AJflnEcWpw = true;}
      if(jsEogDqmaa == xAEwzDKZMP){YDyKyhPGPq = true;}
      if(YolIUbsNzy == iTTsjgTOlX){HjMPRsoJdC = true;}
      while(WRGVnkVyYi == gQZeIOXYWk){wKwFtDjrWj = true;}
      while(xAEwzDKZMP == xAEwzDKZMP){NqPPAGOoyu = true;}
      while(iTTsjgTOlX == iTTsjgTOlX){XwdZyrXQPP = true;}
      if(RYrpqPLcLZ == true){RYrpqPLcLZ = false;}
      if(kqpZdIXjVf == true){kqpZdIXjVf = false;}
      if(lqIUnCxNlH == true){lqIUnCxNlH = false;}
      if(RHMBRXHOEj == true){RHMBRXHOEj = false;}
      if(rgNleqcsOa == true){rgNleqcsOa = false;}
      if(IirGlaQXCo == true){IirGlaQXCo = false;}
      if(RyqEIceoHF == true){RyqEIceoHF = false;}
      if(AJflnEcWpw == true){AJflnEcWpw = false;}
      if(YDyKyhPGPq == true){YDyKyhPGPq = false;}
      if(HjMPRsoJdC == true){HjMPRsoJdC = false;}
      if(MnlIZzDFRg == true){MnlIZzDFRg = false;}
      if(xsgFPNzgFZ == true){xsgFPNzgFZ = false;}
      if(MYZQyPxPTt == true){MYZQyPxPTt = false;}
      if(OTsmikRojz == true){OTsmikRojz = false;}
      if(eJnhsNCGAD == true){eJnhsNCGAD = false;}
      if(tIEDonNUKK == true){tIEDonNUKK = false;}
      if(BmlWRdAtVd == true){BmlWRdAtVd = false;}
      if(wKwFtDjrWj == true){wKwFtDjrWj = false;}
      if(NqPPAGOoyu == true){NqPPAGOoyu = false;}
      if(XwdZyrXQPP == true){XwdZyrXQPP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHSBGFGJEP
{ 
  void nPRCuquBkP()
  { 
      bool lxVjwnkJar = false;
      bool NwbgSFoltW = false;
      bool PkxJFtEmQV = false;
      bool oNJHcCCsuO = false;
      bool UDpdHGXDYp = false;
      bool RRmIhBzMdB = false;
      bool jxrEDzmUEQ = false;
      bool CwpeBLuSCy = false;
      bool VAOaEWaAZb = false;
      bool CpOseWLkaI = false;
      bool SDzImVaHGW = false;
      bool FgKeeiiRAg = false;
      bool XlubNLgxAe = false;
      bool AJrsfSBFmi = false;
      bool uStCVUfiOu = false;
      bool nsktjfHXub = false;
      bool ndHbVwnQzL = false;
      bool hdeRkFrrFr = false;
      bool fxiFpGYyJz = false;
      bool KcKLtRLRfZ = false;
      string WKxDffOQod;
      string RFrGozSSas;
      string QSFAgLQGjV;
      string LzWlpUpgId;
      string JmaZeSnaWr;
      string pyGNcDFwWT;
      string PHgSRSiFPU;
      string JkJwicqeUN;
      string WpjrfNrIIl;
      string PsKoOBFIIM;
      string iiKBhFnKdA;
      string LZbIwYXolD;
      string aZxdFQaUgg;
      string WiWIdnfhJZ;
      string ZhdIZoQBro;
      string dQVEkJkfwR;
      string eSdxccDTeI;
      string soeMdsunEP;
      string zYcqCGNRWU;
      string CzkquHEgex;
      if(WKxDffOQod == iiKBhFnKdA){lxVjwnkJar = true;}
      else if(iiKBhFnKdA == WKxDffOQod){SDzImVaHGW = true;}
      if(RFrGozSSas == LZbIwYXolD){NwbgSFoltW = true;}
      else if(LZbIwYXolD == RFrGozSSas){FgKeeiiRAg = true;}
      if(QSFAgLQGjV == aZxdFQaUgg){PkxJFtEmQV = true;}
      else if(aZxdFQaUgg == QSFAgLQGjV){XlubNLgxAe = true;}
      if(LzWlpUpgId == WiWIdnfhJZ){oNJHcCCsuO = true;}
      else if(WiWIdnfhJZ == LzWlpUpgId){AJrsfSBFmi = true;}
      if(JmaZeSnaWr == ZhdIZoQBro){UDpdHGXDYp = true;}
      else if(ZhdIZoQBro == JmaZeSnaWr){uStCVUfiOu = true;}
      if(pyGNcDFwWT == dQVEkJkfwR){RRmIhBzMdB = true;}
      else if(dQVEkJkfwR == pyGNcDFwWT){nsktjfHXub = true;}
      if(PHgSRSiFPU == eSdxccDTeI){jxrEDzmUEQ = true;}
      else if(eSdxccDTeI == PHgSRSiFPU){ndHbVwnQzL = true;}
      if(JkJwicqeUN == soeMdsunEP){CwpeBLuSCy = true;}
      if(WpjrfNrIIl == zYcqCGNRWU){VAOaEWaAZb = true;}
      if(PsKoOBFIIM == CzkquHEgex){CpOseWLkaI = true;}
      while(soeMdsunEP == JkJwicqeUN){hdeRkFrrFr = true;}
      while(zYcqCGNRWU == zYcqCGNRWU){fxiFpGYyJz = true;}
      while(CzkquHEgex == CzkquHEgex){KcKLtRLRfZ = true;}
      if(lxVjwnkJar == true){lxVjwnkJar = false;}
      if(NwbgSFoltW == true){NwbgSFoltW = false;}
      if(PkxJFtEmQV == true){PkxJFtEmQV = false;}
      if(oNJHcCCsuO == true){oNJHcCCsuO = false;}
      if(UDpdHGXDYp == true){UDpdHGXDYp = false;}
      if(RRmIhBzMdB == true){RRmIhBzMdB = false;}
      if(jxrEDzmUEQ == true){jxrEDzmUEQ = false;}
      if(CwpeBLuSCy == true){CwpeBLuSCy = false;}
      if(VAOaEWaAZb == true){VAOaEWaAZb = false;}
      if(CpOseWLkaI == true){CpOseWLkaI = false;}
      if(SDzImVaHGW == true){SDzImVaHGW = false;}
      if(FgKeeiiRAg == true){FgKeeiiRAg = false;}
      if(XlubNLgxAe == true){XlubNLgxAe = false;}
      if(AJrsfSBFmi == true){AJrsfSBFmi = false;}
      if(uStCVUfiOu == true){uStCVUfiOu = false;}
      if(nsktjfHXub == true){nsktjfHXub = false;}
      if(ndHbVwnQzL == true){ndHbVwnQzL = false;}
      if(hdeRkFrrFr == true){hdeRkFrrFr = false;}
      if(fxiFpGYyJz == true){fxiFpGYyJz = false;}
      if(KcKLtRLRfZ == true){KcKLtRLRfZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLDPIIWBGG
{ 
  void cQntAyQIRu()
  { 
      bool VdBdAcahKR = false;
      bool CLmSgdnUiI = false;
      bool iBEWrYmjQf = false;
      bool VyxXYkluVS = false;
      bool XuJZMFlhuX = false;
      bool AWMdwUZdlb = false;
      bool pqQewENOsw = false;
      bool rszQjmreKm = false;
      bool lEnrezkTbE = false;
      bool LHJsbgdedI = false;
      bool qWozfHXwsI = false;
      bool cuSzolCYzw = false;
      bool StlnjjiFnD = false;
      bool JMACuPOoLX = false;
      bool aoZTbQnJEo = false;
      bool dFegowjAOu = false;
      bool XRHpzPtQDZ = false;
      bool XMMbUcTSMT = false;
      bool uZBzYEhSMy = false;
      bool eNaPzJhiUM = false;
      string XnnCrZorSo;
      string ZhSVpIUwEV;
      string oLNSdgMUrQ;
      string jktysnTIWY;
      string naqJRDsMDd;
      string ECqaJLZVXK;
      string MTABFonTbB;
      string oLZfhNUEAa;
      string mAQOMgsToh;
      string NxkLLTZpEb;
      string PZjBnrcKsu;
      string qVVxWMClnY;
      string wTdtnqaOUN;
      string mezXKNPOZU;
      string Dhatqrbmny;
      string RnBefuwpNx;
      string ROpeHLVxlJ;
      string xnMTUNsjDu;
      string PmZVwzcTrO;
      string RYBcCoqule;
      if(XnnCrZorSo == PZjBnrcKsu){VdBdAcahKR = true;}
      else if(PZjBnrcKsu == XnnCrZorSo){qWozfHXwsI = true;}
      if(ZhSVpIUwEV == qVVxWMClnY){CLmSgdnUiI = true;}
      else if(qVVxWMClnY == ZhSVpIUwEV){cuSzolCYzw = true;}
      if(oLNSdgMUrQ == wTdtnqaOUN){iBEWrYmjQf = true;}
      else if(wTdtnqaOUN == oLNSdgMUrQ){StlnjjiFnD = true;}
      if(jktysnTIWY == mezXKNPOZU){VyxXYkluVS = true;}
      else if(mezXKNPOZU == jktysnTIWY){JMACuPOoLX = true;}
      if(naqJRDsMDd == Dhatqrbmny){XuJZMFlhuX = true;}
      else if(Dhatqrbmny == naqJRDsMDd){aoZTbQnJEo = true;}
      if(ECqaJLZVXK == RnBefuwpNx){AWMdwUZdlb = true;}
      else if(RnBefuwpNx == ECqaJLZVXK){dFegowjAOu = true;}
      if(MTABFonTbB == ROpeHLVxlJ){pqQewENOsw = true;}
      else if(ROpeHLVxlJ == MTABFonTbB){XRHpzPtQDZ = true;}
      if(oLZfhNUEAa == xnMTUNsjDu){rszQjmreKm = true;}
      if(mAQOMgsToh == PmZVwzcTrO){lEnrezkTbE = true;}
      if(NxkLLTZpEb == RYBcCoqule){LHJsbgdedI = true;}
      while(xnMTUNsjDu == oLZfhNUEAa){XMMbUcTSMT = true;}
      while(PmZVwzcTrO == PmZVwzcTrO){uZBzYEhSMy = true;}
      while(RYBcCoqule == RYBcCoqule){eNaPzJhiUM = true;}
      if(VdBdAcahKR == true){VdBdAcahKR = false;}
      if(CLmSgdnUiI == true){CLmSgdnUiI = false;}
      if(iBEWrYmjQf == true){iBEWrYmjQf = false;}
      if(VyxXYkluVS == true){VyxXYkluVS = false;}
      if(XuJZMFlhuX == true){XuJZMFlhuX = false;}
      if(AWMdwUZdlb == true){AWMdwUZdlb = false;}
      if(pqQewENOsw == true){pqQewENOsw = false;}
      if(rszQjmreKm == true){rszQjmreKm = false;}
      if(lEnrezkTbE == true){lEnrezkTbE = false;}
      if(LHJsbgdedI == true){LHJsbgdedI = false;}
      if(qWozfHXwsI == true){qWozfHXwsI = false;}
      if(cuSzolCYzw == true){cuSzolCYzw = false;}
      if(StlnjjiFnD == true){StlnjjiFnD = false;}
      if(JMACuPOoLX == true){JMACuPOoLX = false;}
      if(aoZTbQnJEo == true){aoZTbQnJEo = false;}
      if(dFegowjAOu == true){dFegowjAOu = false;}
      if(XRHpzPtQDZ == true){XRHpzPtQDZ = false;}
      if(XMMbUcTSMT == true){XMMbUcTSMT = false;}
      if(uZBzYEhSMy == true){uZBzYEhSMy = false;}
      if(eNaPzJhiUM == true){eNaPzJhiUM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RXOCTVQAFJ
{ 
  void BPcgGWLNqL()
  { 
      bool BbwazObunF = false;
      bool BrHuRgXtDz = false;
      bool ciWImloJIB = false;
      bool TYJlbAqdAw = false;
      bool blamwuVTTp = false;
      bool ceSKzSFmnN = false;
      bool YRlllbiUTR = false;
      bool ostHXpIiMq = false;
      bool PVoSYoFymI = false;
      bool uDpmXJAnBT = false;
      bool LBzCAjkLmI = false;
      bool KWawyCcSNx = false;
      bool WkhKWkDHiO = false;
      bool oUhreOVmRo = false;
      bool DsLdyYcsoU = false;
      bool ggZDxaSofP = false;
      bool gdcYTonhQi = false;
      bool goBYscZDLy = false;
      bool IJSOhHtduE = false;
      bool ugHCHZQlKJ = false;
      string IdhmisTGni;
      string kcQnUmapPx;
      string yhwRMLEfhL;
      string noRsflQdCT;
      string DXaSKoQflk;
      string IYHmCahPZW;
      string nnYbuwLXHh;
      string VwnwtZHdHX;
      string tYswDOgdpF;
      string EAEefOzyWO;
      string dsXDPLkLsc;
      string SEIBcPubXf;
      string OggBdUqIQe;
      string ZIGstAAogq;
      string dUkNmArDCP;
      string TWaqzwMWZt;
      string UcuOCKyPGb;
      string PFufCsuTOd;
      string cnFAKDgOsx;
      string ndPlWAZWKb;
      if(IdhmisTGni == dsXDPLkLsc){BbwazObunF = true;}
      else if(dsXDPLkLsc == IdhmisTGni){LBzCAjkLmI = true;}
      if(kcQnUmapPx == SEIBcPubXf){BrHuRgXtDz = true;}
      else if(SEIBcPubXf == kcQnUmapPx){KWawyCcSNx = true;}
      if(yhwRMLEfhL == OggBdUqIQe){ciWImloJIB = true;}
      else if(OggBdUqIQe == yhwRMLEfhL){WkhKWkDHiO = true;}
      if(noRsflQdCT == ZIGstAAogq){TYJlbAqdAw = true;}
      else if(ZIGstAAogq == noRsflQdCT){oUhreOVmRo = true;}
      if(DXaSKoQflk == dUkNmArDCP){blamwuVTTp = true;}
      else if(dUkNmArDCP == DXaSKoQflk){DsLdyYcsoU = true;}
      if(IYHmCahPZW == TWaqzwMWZt){ceSKzSFmnN = true;}
      else if(TWaqzwMWZt == IYHmCahPZW){ggZDxaSofP = true;}
      if(nnYbuwLXHh == UcuOCKyPGb){YRlllbiUTR = true;}
      else if(UcuOCKyPGb == nnYbuwLXHh){gdcYTonhQi = true;}
      if(VwnwtZHdHX == PFufCsuTOd){ostHXpIiMq = true;}
      if(tYswDOgdpF == cnFAKDgOsx){PVoSYoFymI = true;}
      if(EAEefOzyWO == ndPlWAZWKb){uDpmXJAnBT = true;}
      while(PFufCsuTOd == VwnwtZHdHX){goBYscZDLy = true;}
      while(cnFAKDgOsx == cnFAKDgOsx){IJSOhHtduE = true;}
      while(ndPlWAZWKb == ndPlWAZWKb){ugHCHZQlKJ = true;}
      if(BbwazObunF == true){BbwazObunF = false;}
      if(BrHuRgXtDz == true){BrHuRgXtDz = false;}
      if(ciWImloJIB == true){ciWImloJIB = false;}
      if(TYJlbAqdAw == true){TYJlbAqdAw = false;}
      if(blamwuVTTp == true){blamwuVTTp = false;}
      if(ceSKzSFmnN == true){ceSKzSFmnN = false;}
      if(YRlllbiUTR == true){YRlllbiUTR = false;}
      if(ostHXpIiMq == true){ostHXpIiMq = false;}
      if(PVoSYoFymI == true){PVoSYoFymI = false;}
      if(uDpmXJAnBT == true){uDpmXJAnBT = false;}
      if(LBzCAjkLmI == true){LBzCAjkLmI = false;}
      if(KWawyCcSNx == true){KWawyCcSNx = false;}
      if(WkhKWkDHiO == true){WkhKWkDHiO = false;}
      if(oUhreOVmRo == true){oUhreOVmRo = false;}
      if(DsLdyYcsoU == true){DsLdyYcsoU = false;}
      if(ggZDxaSofP == true){ggZDxaSofP = false;}
      if(gdcYTonhQi == true){gdcYTonhQi = false;}
      if(goBYscZDLy == true){goBYscZDLy = false;}
      if(IJSOhHtduE == true){IJSOhHtduE = false;}
      if(ugHCHZQlKJ == true){ugHCHZQlKJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVPZTIFQKI
{ 
  void tCKypFJKeH()
  { 
      bool mmbSmRLqoG = false;
      bool wtJWVcRncV = false;
      bool jRPMsQhKgA = false;
      bool bLNgPooQoN = false;
      bool SOeOgTMgPO = false;
      bool hVCsyVWOZW = false;
      bool iBKnejgbHg = false;
      bool nBzPCUlBfZ = false;
      bool DAuRRFJUht = false;
      bool RZqSdREpjw = false;
      bool mjZhagWlpc = false;
      bool iVizShGrWY = false;
      bool aLsNPNJfkk = false;
      bool QuQilSaMpj = false;
      bool hWeFKupqzu = false;
      bool LLTKVapMSN = false;
      bool XpAEMmFANA = false;
      bool HsBlpDgnCT = false;
      bool WRgpYEbFNK = false;
      bool bNscMrVZsW = false;
      string GNSKXxYeSZ;
      string nxXcQfVAOW;
      string euOrTYEcOu;
      string HchWzTBPUC;
      string QDyLTiTsyd;
      string hrfzQKzZqz;
      string suPXSLOAdx;
      string dGfLFaxDXj;
      string FKejMPwiGn;
      string UbXUIUnZsI;
      string TSPBAbMTto;
      string NwBGtiQfKD;
      string OftpbChKCj;
      string mWJPQludjk;
      string CboQZYZRaZ;
      string EHPosmXYYy;
      string sCRJBqllpH;
      string mmwYAlqcPC;
      string bQjcfeGTVc;
      string OVEkrAKfPi;
      if(GNSKXxYeSZ == TSPBAbMTto){mmbSmRLqoG = true;}
      else if(TSPBAbMTto == GNSKXxYeSZ){mjZhagWlpc = true;}
      if(nxXcQfVAOW == NwBGtiQfKD){wtJWVcRncV = true;}
      else if(NwBGtiQfKD == nxXcQfVAOW){iVizShGrWY = true;}
      if(euOrTYEcOu == OftpbChKCj){jRPMsQhKgA = true;}
      else if(OftpbChKCj == euOrTYEcOu){aLsNPNJfkk = true;}
      if(HchWzTBPUC == mWJPQludjk){bLNgPooQoN = true;}
      else if(mWJPQludjk == HchWzTBPUC){QuQilSaMpj = true;}
      if(QDyLTiTsyd == CboQZYZRaZ){SOeOgTMgPO = true;}
      else if(CboQZYZRaZ == QDyLTiTsyd){hWeFKupqzu = true;}
      if(hrfzQKzZqz == EHPosmXYYy){hVCsyVWOZW = true;}
      else if(EHPosmXYYy == hrfzQKzZqz){LLTKVapMSN = true;}
      if(suPXSLOAdx == sCRJBqllpH){iBKnejgbHg = true;}
      else if(sCRJBqllpH == suPXSLOAdx){XpAEMmFANA = true;}
      if(dGfLFaxDXj == mmwYAlqcPC){nBzPCUlBfZ = true;}
      if(FKejMPwiGn == bQjcfeGTVc){DAuRRFJUht = true;}
      if(UbXUIUnZsI == OVEkrAKfPi){RZqSdREpjw = true;}
      while(mmwYAlqcPC == dGfLFaxDXj){HsBlpDgnCT = true;}
      while(bQjcfeGTVc == bQjcfeGTVc){WRgpYEbFNK = true;}
      while(OVEkrAKfPi == OVEkrAKfPi){bNscMrVZsW = true;}
      if(mmbSmRLqoG == true){mmbSmRLqoG = false;}
      if(wtJWVcRncV == true){wtJWVcRncV = false;}
      if(jRPMsQhKgA == true){jRPMsQhKgA = false;}
      if(bLNgPooQoN == true){bLNgPooQoN = false;}
      if(SOeOgTMgPO == true){SOeOgTMgPO = false;}
      if(hVCsyVWOZW == true){hVCsyVWOZW = false;}
      if(iBKnejgbHg == true){iBKnejgbHg = false;}
      if(nBzPCUlBfZ == true){nBzPCUlBfZ = false;}
      if(DAuRRFJUht == true){DAuRRFJUht = false;}
      if(RZqSdREpjw == true){RZqSdREpjw = false;}
      if(mjZhagWlpc == true){mjZhagWlpc = false;}
      if(iVizShGrWY == true){iVizShGrWY = false;}
      if(aLsNPNJfkk == true){aLsNPNJfkk = false;}
      if(QuQilSaMpj == true){QuQilSaMpj = false;}
      if(hWeFKupqzu == true){hWeFKupqzu = false;}
      if(LLTKVapMSN == true){LLTKVapMSN = false;}
      if(XpAEMmFANA == true){XpAEMmFANA = false;}
      if(HsBlpDgnCT == true){HsBlpDgnCT = false;}
      if(WRgpYEbFNK == true){WRgpYEbFNK = false;}
      if(bNscMrVZsW == true){bNscMrVZsW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQZTRBXEAH
{ 
  void KNhIBNFRin()
  { 
      bool WPaQHLSNty = false;
      bool ltyXDNYyyE = false;
      bool wFTSffPtxb = false;
      bool ewRQzPpNTk = false;
      bool BRIAgHhVzw = false;
      bool WolqmQwIja = false;
      bool uYQRTpcgYn = false;
      bool XKdNDdxSkX = false;
      bool ytuAEoJZdi = false;
      bool SgcspbBqgq = false;
      bool eAxKYMKYnI = false;
      bool TdWLbBdQMe = false;
      bool fDDoVphkXa = false;
      bool cFltsywjar = false;
      bool djlUPoJQQn = false;
      bool xjdCKbwHoh = false;
      bool dZBMfNrcSd = false;
      bool FtoTAuQhZf = false;
      bool fQTicrbjiR = false;
      bool BntrOEiZoB = false;
      string sBqOLajdey;
      string jKoqPEBUwx;
      string yrJnRMxxMd;
      string qPzYpCWito;
      string IPVxVuIJKd;
      string cJdDsAqDwz;
      string dlQAGULPAN;
      string gRZGoiWMSW;
      string EmlhBhlwfo;
      string KTmuKVyUpA;
      string irIxwKiWOJ;
      string dejZtqzhyX;
      string iPjKCNeewS;
      string jBVRmLdokq;
      string zPgVLfiNAT;
      string VPVSRTIyti;
      string fDauYbJSli;
      string MKwHXThNzW;
      string eRebwUfDzT;
      string CftCKwnkwi;
      if(sBqOLajdey == irIxwKiWOJ){WPaQHLSNty = true;}
      else if(irIxwKiWOJ == sBqOLajdey){eAxKYMKYnI = true;}
      if(jKoqPEBUwx == dejZtqzhyX){ltyXDNYyyE = true;}
      else if(dejZtqzhyX == jKoqPEBUwx){TdWLbBdQMe = true;}
      if(yrJnRMxxMd == iPjKCNeewS){wFTSffPtxb = true;}
      else if(iPjKCNeewS == yrJnRMxxMd){fDDoVphkXa = true;}
      if(qPzYpCWito == jBVRmLdokq){ewRQzPpNTk = true;}
      else if(jBVRmLdokq == qPzYpCWito){cFltsywjar = true;}
      if(IPVxVuIJKd == zPgVLfiNAT){BRIAgHhVzw = true;}
      else if(zPgVLfiNAT == IPVxVuIJKd){djlUPoJQQn = true;}
      if(cJdDsAqDwz == VPVSRTIyti){WolqmQwIja = true;}
      else if(VPVSRTIyti == cJdDsAqDwz){xjdCKbwHoh = true;}
      if(dlQAGULPAN == fDauYbJSli){uYQRTpcgYn = true;}
      else if(fDauYbJSli == dlQAGULPAN){dZBMfNrcSd = true;}
      if(gRZGoiWMSW == MKwHXThNzW){XKdNDdxSkX = true;}
      if(EmlhBhlwfo == eRebwUfDzT){ytuAEoJZdi = true;}
      if(KTmuKVyUpA == CftCKwnkwi){SgcspbBqgq = true;}
      while(MKwHXThNzW == gRZGoiWMSW){FtoTAuQhZf = true;}
      while(eRebwUfDzT == eRebwUfDzT){fQTicrbjiR = true;}
      while(CftCKwnkwi == CftCKwnkwi){BntrOEiZoB = true;}
      if(WPaQHLSNty == true){WPaQHLSNty = false;}
      if(ltyXDNYyyE == true){ltyXDNYyyE = false;}
      if(wFTSffPtxb == true){wFTSffPtxb = false;}
      if(ewRQzPpNTk == true){ewRQzPpNTk = false;}
      if(BRIAgHhVzw == true){BRIAgHhVzw = false;}
      if(WolqmQwIja == true){WolqmQwIja = false;}
      if(uYQRTpcgYn == true){uYQRTpcgYn = false;}
      if(XKdNDdxSkX == true){XKdNDdxSkX = false;}
      if(ytuAEoJZdi == true){ytuAEoJZdi = false;}
      if(SgcspbBqgq == true){SgcspbBqgq = false;}
      if(eAxKYMKYnI == true){eAxKYMKYnI = false;}
      if(TdWLbBdQMe == true){TdWLbBdQMe = false;}
      if(fDDoVphkXa == true){fDDoVphkXa = false;}
      if(cFltsywjar == true){cFltsywjar = false;}
      if(djlUPoJQQn == true){djlUPoJQQn = false;}
      if(xjdCKbwHoh == true){xjdCKbwHoh = false;}
      if(dZBMfNrcSd == true){dZBMfNrcSd = false;}
      if(FtoTAuQhZf == true){FtoTAuQhZf = false;}
      if(fQTicrbjiR == true){fQTicrbjiR = false;}
      if(BntrOEiZoB == true){BntrOEiZoB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIWKKECLTV
{ 
  void GYGLixhoOJ()
  { 
      bool wwygDXCqCW = false;
      bool CmiRtUfxmG = false;
      bool jjqjnJVKfV = false;
      bool pPMOIdLFko = false;
      bool ZODoLTHViG = false;
      bool GkabwLEOrt = false;
      bool CqLgflZUIP = false;
      bool IZLygUfCYU = false;
      bool BzaYPFokRx = false;
      bool ZxNqlhDWIY = false;
      bool tmMTygYcua = false;
      bool eBpXrCQlQa = false;
      bool xoCLpLMULy = false;
      bool RJszZOmHah = false;
      bool fMppRXHozj = false;
      bool RQFhbFkAdm = false;
      bool TEQwJVIpxd = false;
      bool PILitjyLtR = false;
      bool DWVbgADLXU = false;
      bool dldmNbusgu = false;
      string ujABiiYFcC;
      string FxrOwIxKjp;
      string ChcopMufZX;
      string xGyMeFWBiN;
      string tHQgoXaeGg;
      string gJDpuMHKLV;
      string mseEEyzeiq;
      string lwaVutRwzS;
      string kQZsqnDHRR;
      string yLoMaBbMcq;
      string XwuOukhgtA;
      string uKLsjVTlNP;
      string uqNRrZGOtt;
      string RFTHtoUKyF;
      string GVNRWmzwbE;
      string gpyMwfidWU;
      string dSmAhpqDyu;
      string BJnHJYdwtE;
      string ZJmoMbGGLN;
      string GqmcamiNif;
      if(ujABiiYFcC == XwuOukhgtA){wwygDXCqCW = true;}
      else if(XwuOukhgtA == ujABiiYFcC){tmMTygYcua = true;}
      if(FxrOwIxKjp == uKLsjVTlNP){CmiRtUfxmG = true;}
      else if(uKLsjVTlNP == FxrOwIxKjp){eBpXrCQlQa = true;}
      if(ChcopMufZX == uqNRrZGOtt){jjqjnJVKfV = true;}
      else if(uqNRrZGOtt == ChcopMufZX){xoCLpLMULy = true;}
      if(xGyMeFWBiN == RFTHtoUKyF){pPMOIdLFko = true;}
      else if(RFTHtoUKyF == xGyMeFWBiN){RJszZOmHah = true;}
      if(tHQgoXaeGg == GVNRWmzwbE){ZODoLTHViG = true;}
      else if(GVNRWmzwbE == tHQgoXaeGg){fMppRXHozj = true;}
      if(gJDpuMHKLV == gpyMwfidWU){GkabwLEOrt = true;}
      else if(gpyMwfidWU == gJDpuMHKLV){RQFhbFkAdm = true;}
      if(mseEEyzeiq == dSmAhpqDyu){CqLgflZUIP = true;}
      else if(dSmAhpqDyu == mseEEyzeiq){TEQwJVIpxd = true;}
      if(lwaVutRwzS == BJnHJYdwtE){IZLygUfCYU = true;}
      if(kQZsqnDHRR == ZJmoMbGGLN){BzaYPFokRx = true;}
      if(yLoMaBbMcq == GqmcamiNif){ZxNqlhDWIY = true;}
      while(BJnHJYdwtE == lwaVutRwzS){PILitjyLtR = true;}
      while(ZJmoMbGGLN == ZJmoMbGGLN){DWVbgADLXU = true;}
      while(GqmcamiNif == GqmcamiNif){dldmNbusgu = true;}
      if(wwygDXCqCW == true){wwygDXCqCW = false;}
      if(CmiRtUfxmG == true){CmiRtUfxmG = false;}
      if(jjqjnJVKfV == true){jjqjnJVKfV = false;}
      if(pPMOIdLFko == true){pPMOIdLFko = false;}
      if(ZODoLTHViG == true){ZODoLTHViG = false;}
      if(GkabwLEOrt == true){GkabwLEOrt = false;}
      if(CqLgflZUIP == true){CqLgflZUIP = false;}
      if(IZLygUfCYU == true){IZLygUfCYU = false;}
      if(BzaYPFokRx == true){BzaYPFokRx = false;}
      if(ZxNqlhDWIY == true){ZxNqlhDWIY = false;}
      if(tmMTygYcua == true){tmMTygYcua = false;}
      if(eBpXrCQlQa == true){eBpXrCQlQa = false;}
      if(xoCLpLMULy == true){xoCLpLMULy = false;}
      if(RJszZOmHah == true){RJszZOmHah = false;}
      if(fMppRXHozj == true){fMppRXHozj = false;}
      if(RQFhbFkAdm == true){RQFhbFkAdm = false;}
      if(TEQwJVIpxd == true){TEQwJVIpxd = false;}
      if(PILitjyLtR == true){PILitjyLtR = false;}
      if(DWVbgADLXU == true){DWVbgADLXU = false;}
      if(dldmNbusgu == true){dldmNbusgu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHIGOEBAQD
{ 
  void SRWwXbeJiG()
  { 
      bool fayGNOhxhx = false;
      bool VOUOKmQfyC = false;
      bool DBgOAXDFtl = false;
      bool cFNcSPtEqj = false;
      bool yiWZweSuDl = false;
      bool BbfOTesiGo = false;
      bool LcDuTQArut = false;
      bool sLoOEUeGRU = false;
      bool FIBHjAZzIn = false;
      bool VKyBYUfaFf = false;
      bool eZzJspmRJz = false;
      bool zmQkjCbuKS = false;
      bool pAiHXhNmoj = false;
      bool nDBlpeJqNt = false;
      bool NIoJnitMRW = false;
      bool sjQlodqqkL = false;
      bool cAbZKwkeuE = false;
      bool sjgPFhKYTo = false;
      bool mAUSpDlOwM = false;
      bool nRGCQNfPzq = false;
      string jZDajUxEKG;
      string eeFIemzdWH;
      string jNzWamNqda;
      string WrPGKJYmgA;
      string TOZVBhYaTn;
      string QmkNnVZgzx;
      string GGajimOyxU;
      string OLxWnVncVr;
      string OlWpKjHCSo;
      string iqmjsMmplO;
      string SZdzYEoNZR;
      string hxLHhUjkYz;
      string eMfIkWYNca;
      string ixqGYnIWQF;
      string tscAHlffBY;
      string bCQliGtVNB;
      string fbkyijFEht;
      string LMTTEljeAz;
      string qrLEzffEXS;
      string tmJOZRIdRX;
      if(jZDajUxEKG == SZdzYEoNZR){fayGNOhxhx = true;}
      else if(SZdzYEoNZR == jZDajUxEKG){eZzJspmRJz = true;}
      if(eeFIemzdWH == hxLHhUjkYz){VOUOKmQfyC = true;}
      else if(hxLHhUjkYz == eeFIemzdWH){zmQkjCbuKS = true;}
      if(jNzWamNqda == eMfIkWYNca){DBgOAXDFtl = true;}
      else if(eMfIkWYNca == jNzWamNqda){pAiHXhNmoj = true;}
      if(WrPGKJYmgA == ixqGYnIWQF){cFNcSPtEqj = true;}
      else if(ixqGYnIWQF == WrPGKJYmgA){nDBlpeJqNt = true;}
      if(TOZVBhYaTn == tscAHlffBY){yiWZweSuDl = true;}
      else if(tscAHlffBY == TOZVBhYaTn){NIoJnitMRW = true;}
      if(QmkNnVZgzx == bCQliGtVNB){BbfOTesiGo = true;}
      else if(bCQliGtVNB == QmkNnVZgzx){sjQlodqqkL = true;}
      if(GGajimOyxU == fbkyijFEht){LcDuTQArut = true;}
      else if(fbkyijFEht == GGajimOyxU){cAbZKwkeuE = true;}
      if(OLxWnVncVr == LMTTEljeAz){sLoOEUeGRU = true;}
      if(OlWpKjHCSo == qrLEzffEXS){FIBHjAZzIn = true;}
      if(iqmjsMmplO == tmJOZRIdRX){VKyBYUfaFf = true;}
      while(LMTTEljeAz == OLxWnVncVr){sjgPFhKYTo = true;}
      while(qrLEzffEXS == qrLEzffEXS){mAUSpDlOwM = true;}
      while(tmJOZRIdRX == tmJOZRIdRX){nRGCQNfPzq = true;}
      if(fayGNOhxhx == true){fayGNOhxhx = false;}
      if(VOUOKmQfyC == true){VOUOKmQfyC = false;}
      if(DBgOAXDFtl == true){DBgOAXDFtl = false;}
      if(cFNcSPtEqj == true){cFNcSPtEqj = false;}
      if(yiWZweSuDl == true){yiWZweSuDl = false;}
      if(BbfOTesiGo == true){BbfOTesiGo = false;}
      if(LcDuTQArut == true){LcDuTQArut = false;}
      if(sLoOEUeGRU == true){sLoOEUeGRU = false;}
      if(FIBHjAZzIn == true){FIBHjAZzIn = false;}
      if(VKyBYUfaFf == true){VKyBYUfaFf = false;}
      if(eZzJspmRJz == true){eZzJspmRJz = false;}
      if(zmQkjCbuKS == true){zmQkjCbuKS = false;}
      if(pAiHXhNmoj == true){pAiHXhNmoj = false;}
      if(nDBlpeJqNt == true){nDBlpeJqNt = false;}
      if(NIoJnitMRW == true){NIoJnitMRW = false;}
      if(sjQlodqqkL == true){sjQlodqqkL = false;}
      if(cAbZKwkeuE == true){cAbZKwkeuE = false;}
      if(sjgPFhKYTo == true){sjgPFhKYTo = false;}
      if(mAUSpDlOwM == true){mAUSpDlOwM = false;}
      if(nRGCQNfPzq == true){nRGCQNfPzq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SEDAMGOIBR
{ 
  void OjRKYySayT()
  { 
      bool YgqFixGCDP = false;
      bool XJUgCOHnOB = false;
      bool zdsSmFDjEJ = false;
      bool scpDQOwSTy = false;
      bool SZKqpWDeiJ = false;
      bool UffbNunYSd = false;
      bool sVxtWtSQQn = false;
      bool SoTPhZSBbP = false;
      bool CYBuoNxNoV = false;
      bool aWzpExbQUu = false;
      bool DlOupeMPsn = false;
      bool blxCbUUCEI = false;
      bool xEbuMuodLk = false;
      bool xBgfMPKFFJ = false;
      bool AhUBsoZxNi = false;
      bool bZMLyzKTht = false;
      bool phDHqZEQpL = false;
      bool KOxuIPjZBX = false;
      bool VrPbJWoVgM = false;
      bool FqWKTSdMKS = false;
      string noLhMelATn;
      string tQFielSnQA;
      string mOCmHXjWhc;
      string KyPxAEqqpx;
      string cBYNzYLdGW;
      string oZcqOZmYao;
      string uPSqduAIhZ;
      string ubxTXkoonh;
      string MGPLnjVYia;
      string QRPBCNihjD;
      string XCufaNbJTc;
      string jykrbozGCs;
      string ZbZHIcLwQJ;
      string CHEjKJLijZ;
      string HMEFpSgXYN;
      string NcepducmWy;
      string CerKabsAgS;
      string dPVclNXTRp;
      string umXDuZcOGO;
      string fXLlXbTtdN;
      if(noLhMelATn == XCufaNbJTc){YgqFixGCDP = true;}
      else if(XCufaNbJTc == noLhMelATn){DlOupeMPsn = true;}
      if(tQFielSnQA == jykrbozGCs){XJUgCOHnOB = true;}
      else if(jykrbozGCs == tQFielSnQA){blxCbUUCEI = true;}
      if(mOCmHXjWhc == ZbZHIcLwQJ){zdsSmFDjEJ = true;}
      else if(ZbZHIcLwQJ == mOCmHXjWhc){xEbuMuodLk = true;}
      if(KyPxAEqqpx == CHEjKJLijZ){scpDQOwSTy = true;}
      else if(CHEjKJLijZ == KyPxAEqqpx){xBgfMPKFFJ = true;}
      if(cBYNzYLdGW == HMEFpSgXYN){SZKqpWDeiJ = true;}
      else if(HMEFpSgXYN == cBYNzYLdGW){AhUBsoZxNi = true;}
      if(oZcqOZmYao == NcepducmWy){UffbNunYSd = true;}
      else if(NcepducmWy == oZcqOZmYao){bZMLyzKTht = true;}
      if(uPSqduAIhZ == CerKabsAgS){sVxtWtSQQn = true;}
      else if(CerKabsAgS == uPSqduAIhZ){phDHqZEQpL = true;}
      if(ubxTXkoonh == dPVclNXTRp){SoTPhZSBbP = true;}
      if(MGPLnjVYia == umXDuZcOGO){CYBuoNxNoV = true;}
      if(QRPBCNihjD == fXLlXbTtdN){aWzpExbQUu = true;}
      while(dPVclNXTRp == ubxTXkoonh){KOxuIPjZBX = true;}
      while(umXDuZcOGO == umXDuZcOGO){VrPbJWoVgM = true;}
      while(fXLlXbTtdN == fXLlXbTtdN){FqWKTSdMKS = true;}
      if(YgqFixGCDP == true){YgqFixGCDP = false;}
      if(XJUgCOHnOB == true){XJUgCOHnOB = false;}
      if(zdsSmFDjEJ == true){zdsSmFDjEJ = false;}
      if(scpDQOwSTy == true){scpDQOwSTy = false;}
      if(SZKqpWDeiJ == true){SZKqpWDeiJ = false;}
      if(UffbNunYSd == true){UffbNunYSd = false;}
      if(sVxtWtSQQn == true){sVxtWtSQQn = false;}
      if(SoTPhZSBbP == true){SoTPhZSBbP = false;}
      if(CYBuoNxNoV == true){CYBuoNxNoV = false;}
      if(aWzpExbQUu == true){aWzpExbQUu = false;}
      if(DlOupeMPsn == true){DlOupeMPsn = false;}
      if(blxCbUUCEI == true){blxCbUUCEI = false;}
      if(xEbuMuodLk == true){xEbuMuodLk = false;}
      if(xBgfMPKFFJ == true){xBgfMPKFFJ = false;}
      if(AhUBsoZxNi == true){AhUBsoZxNi = false;}
      if(bZMLyzKTht == true){bZMLyzKTht = false;}
      if(phDHqZEQpL == true){phDHqZEQpL = false;}
      if(KOxuIPjZBX == true){KOxuIPjZBX = false;}
      if(VrPbJWoVgM == true){VrPbJWoVgM = false;}
      if(FqWKTSdMKS == true){FqWKTSdMKS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDJQYGBEMI
{ 
  void UXHPGuOynn()
  { 
      bool HtoDYHhgIq = false;
      bool iZnXsAHrwf = false;
      bool KLYkMTwNAA = false;
      bool OmSLmnqPUZ = false;
      bool nRStgDPrQV = false;
      bool gnccIuUDqE = false;
      bool LTfIcuGckF = false;
      bool JqXVqrseDI = false;
      bool EDxeSaJpCq = false;
      bool SmYPOUlKRl = false;
      bool xmHLLpPGkP = false;
      bool CpzhAHWBoB = false;
      bool kQZslWSHHW = false;
      bool GhMRLQwkTb = false;
      bool KCElncnpPG = false;
      bool xkUPAgMNYo = false;
      bool XHzOJTdgWi = false;
      bool KkgMqiLnFJ = false;
      bool ibrAZVMwRe = false;
      bool EiMdEDDpbT = false;
      string neDUhWhPRe;
      string QWwjwnRfXJ;
      string asoohrayAj;
      string UGYQkxGqEn;
      string wfLNMJVaHx;
      string dPLqZtoOlp;
      string ujOgKJxezy;
      string gaaiMthbbX;
      string VzpDGEugqp;
      string IrENsMReDC;
      string LpbIQDnbde;
      string MMlNUwsLZF;
      string OQnIpnWNpA;
      string cDYZLeXhlD;
      string PSDLduGpsx;
      string SGExmuCTRb;
      string galdCJmLBo;
      string XLYWouMcet;
      string hfTsgVzalQ;
      string cEPKWogZJT;
      if(neDUhWhPRe == LpbIQDnbde){HtoDYHhgIq = true;}
      else if(LpbIQDnbde == neDUhWhPRe){xmHLLpPGkP = true;}
      if(QWwjwnRfXJ == MMlNUwsLZF){iZnXsAHrwf = true;}
      else if(MMlNUwsLZF == QWwjwnRfXJ){CpzhAHWBoB = true;}
      if(asoohrayAj == OQnIpnWNpA){KLYkMTwNAA = true;}
      else if(OQnIpnWNpA == asoohrayAj){kQZslWSHHW = true;}
      if(UGYQkxGqEn == cDYZLeXhlD){OmSLmnqPUZ = true;}
      else if(cDYZLeXhlD == UGYQkxGqEn){GhMRLQwkTb = true;}
      if(wfLNMJVaHx == PSDLduGpsx){nRStgDPrQV = true;}
      else if(PSDLduGpsx == wfLNMJVaHx){KCElncnpPG = true;}
      if(dPLqZtoOlp == SGExmuCTRb){gnccIuUDqE = true;}
      else if(SGExmuCTRb == dPLqZtoOlp){xkUPAgMNYo = true;}
      if(ujOgKJxezy == galdCJmLBo){LTfIcuGckF = true;}
      else if(galdCJmLBo == ujOgKJxezy){XHzOJTdgWi = true;}
      if(gaaiMthbbX == XLYWouMcet){JqXVqrseDI = true;}
      if(VzpDGEugqp == hfTsgVzalQ){EDxeSaJpCq = true;}
      if(IrENsMReDC == cEPKWogZJT){SmYPOUlKRl = true;}
      while(XLYWouMcet == gaaiMthbbX){KkgMqiLnFJ = true;}
      while(hfTsgVzalQ == hfTsgVzalQ){ibrAZVMwRe = true;}
      while(cEPKWogZJT == cEPKWogZJT){EiMdEDDpbT = true;}
      if(HtoDYHhgIq == true){HtoDYHhgIq = false;}
      if(iZnXsAHrwf == true){iZnXsAHrwf = false;}
      if(KLYkMTwNAA == true){KLYkMTwNAA = false;}
      if(OmSLmnqPUZ == true){OmSLmnqPUZ = false;}
      if(nRStgDPrQV == true){nRStgDPrQV = false;}
      if(gnccIuUDqE == true){gnccIuUDqE = false;}
      if(LTfIcuGckF == true){LTfIcuGckF = false;}
      if(JqXVqrseDI == true){JqXVqrseDI = false;}
      if(EDxeSaJpCq == true){EDxeSaJpCq = false;}
      if(SmYPOUlKRl == true){SmYPOUlKRl = false;}
      if(xmHLLpPGkP == true){xmHLLpPGkP = false;}
      if(CpzhAHWBoB == true){CpzhAHWBoB = false;}
      if(kQZslWSHHW == true){kQZslWSHHW = false;}
      if(GhMRLQwkTb == true){GhMRLQwkTb = false;}
      if(KCElncnpPG == true){KCElncnpPG = false;}
      if(xkUPAgMNYo == true){xkUPAgMNYo = false;}
      if(XHzOJTdgWi == true){XHzOJTdgWi = false;}
      if(KkgMqiLnFJ == true){KkgMqiLnFJ = false;}
      if(ibrAZVMwRe == true){ibrAZVMwRe = false;}
      if(EiMdEDDpbT == true){EiMdEDDpbT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEMHVTLVGN
{ 
  void qolErNzwAK()
  { 
      bool XcQOCnHxmD = false;
      bool JieMOMrnjZ = false;
      bool GwCuaEyNMj = false;
      bool CTluEiNVbN = false;
      bool TKtgRBDAeF = false;
      bool rulIyaaVny = false;
      bool ptjCApxiIf = false;
      bool zVLWGuBUcY = false;
      bool AxiHqGgcxc = false;
      bool IrhcXYaqfa = false;
      bool ETryGVjPCD = false;
      bool ZFrOxrLcKt = false;
      bool ITleXGnhyg = false;
      bool UJoBUgEkBU = false;
      bool VRatDCzSfe = false;
      bool NxflSjhNZz = false;
      bool hBQUhPQptQ = false;
      bool nZapXqsraV = false;
      bool HUCTTWcDij = false;
      bool zpKCmUAGLm = false;
      string iMiojaXYpW;
      string ctkMTsJLYQ;
      string ZfMRSmHmZf;
      string htADWUqGXK;
      string ApbfNspqQD;
      string LdCEaDAQWx;
      string SkyJnhtgoy;
      string BCmNQiDgEY;
      string xQVWTErwbT;
      string UajarOrSqe;
      string yIBSBJpomr;
      string zTLxACOboi;
      string pyEUcaRMUB;
      string pkoZanODUK;
      string ODIjTBOmap;
      string APcHozDfoa;
      string rdTlBOdlVL;
      string mLHeUlpUBb;
      string LekeBaIhja;
      string jiNtSkjWiF;
      if(iMiojaXYpW == yIBSBJpomr){XcQOCnHxmD = true;}
      else if(yIBSBJpomr == iMiojaXYpW){ETryGVjPCD = true;}
      if(ctkMTsJLYQ == zTLxACOboi){JieMOMrnjZ = true;}
      else if(zTLxACOboi == ctkMTsJLYQ){ZFrOxrLcKt = true;}
      if(ZfMRSmHmZf == pyEUcaRMUB){GwCuaEyNMj = true;}
      else if(pyEUcaRMUB == ZfMRSmHmZf){ITleXGnhyg = true;}
      if(htADWUqGXK == pkoZanODUK){CTluEiNVbN = true;}
      else if(pkoZanODUK == htADWUqGXK){UJoBUgEkBU = true;}
      if(ApbfNspqQD == ODIjTBOmap){TKtgRBDAeF = true;}
      else if(ODIjTBOmap == ApbfNspqQD){VRatDCzSfe = true;}
      if(LdCEaDAQWx == APcHozDfoa){rulIyaaVny = true;}
      else if(APcHozDfoa == LdCEaDAQWx){NxflSjhNZz = true;}
      if(SkyJnhtgoy == rdTlBOdlVL){ptjCApxiIf = true;}
      else if(rdTlBOdlVL == SkyJnhtgoy){hBQUhPQptQ = true;}
      if(BCmNQiDgEY == mLHeUlpUBb){zVLWGuBUcY = true;}
      if(xQVWTErwbT == LekeBaIhja){AxiHqGgcxc = true;}
      if(UajarOrSqe == jiNtSkjWiF){IrhcXYaqfa = true;}
      while(mLHeUlpUBb == BCmNQiDgEY){nZapXqsraV = true;}
      while(LekeBaIhja == LekeBaIhja){HUCTTWcDij = true;}
      while(jiNtSkjWiF == jiNtSkjWiF){zpKCmUAGLm = true;}
      if(XcQOCnHxmD == true){XcQOCnHxmD = false;}
      if(JieMOMrnjZ == true){JieMOMrnjZ = false;}
      if(GwCuaEyNMj == true){GwCuaEyNMj = false;}
      if(CTluEiNVbN == true){CTluEiNVbN = false;}
      if(TKtgRBDAeF == true){TKtgRBDAeF = false;}
      if(rulIyaaVny == true){rulIyaaVny = false;}
      if(ptjCApxiIf == true){ptjCApxiIf = false;}
      if(zVLWGuBUcY == true){zVLWGuBUcY = false;}
      if(AxiHqGgcxc == true){AxiHqGgcxc = false;}
      if(IrhcXYaqfa == true){IrhcXYaqfa = false;}
      if(ETryGVjPCD == true){ETryGVjPCD = false;}
      if(ZFrOxrLcKt == true){ZFrOxrLcKt = false;}
      if(ITleXGnhyg == true){ITleXGnhyg = false;}
      if(UJoBUgEkBU == true){UJoBUgEkBU = false;}
      if(VRatDCzSfe == true){VRatDCzSfe = false;}
      if(NxflSjhNZz == true){NxflSjhNZz = false;}
      if(hBQUhPQptQ == true){hBQUhPQptQ = false;}
      if(nZapXqsraV == true){nZapXqsraV = false;}
      if(HUCTTWcDij == true){HUCTTWcDij = false;}
      if(zpKCmUAGLm == true){zpKCmUAGLm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTLDPHMKYN
{ 
  void qBfaphTKOO()
  { 
      bool KOFBiWGsLq = false;
      bool dFHoTTDgcC = false;
      bool kIdzsbeoVX = false;
      bool CQHQAxOVfP = false;
      bool qcGKSBfJSz = false;
      bool FNDMcCjFHH = false;
      bool rQXnoNyqoV = false;
      bool EhBNKIBSgr = false;
      bool uVWVRnNumx = false;
      bool NJNYXaERVE = false;
      bool CoTwuXLpBT = false;
      bool AQYPLWsCVA = false;
      bool ACDrIuTcoj = false;
      bool DixboFBaZt = false;
      bool bXtSwwkyMA = false;
      bool gCwUEzlbmA = false;
      bool EiAQPRTxZF = false;
      bool VScaYcIjuM = false;
      bool KVPoCBmbWo = false;
      bool TYmYprXcCe = false;
      string ZhpgVrrUkl;
      string QbQQAnicAZ;
      string mcawPomQTW;
      string oVckfeNoSu;
      string GdsGZUrYSN;
      string EIRZpxHtQg;
      string EaANwuyfkU;
      string atKFTJjUVu;
      string wOxFRgEDui;
      string XTXlpeceJe;
      string VMnymKyLFf;
      string MlXVjpdtwP;
      string ptkBxHWXOo;
      string fELqYiZzSH;
      string irxOWluCBz;
      string BhhsoablAf;
      string nZxQAHagxA;
      string PdbogxxVeL;
      string LTWPmxVSCx;
      string HnylTIufOO;
      if(ZhpgVrrUkl == VMnymKyLFf){KOFBiWGsLq = true;}
      else if(VMnymKyLFf == ZhpgVrrUkl){CoTwuXLpBT = true;}
      if(QbQQAnicAZ == MlXVjpdtwP){dFHoTTDgcC = true;}
      else if(MlXVjpdtwP == QbQQAnicAZ){AQYPLWsCVA = true;}
      if(mcawPomQTW == ptkBxHWXOo){kIdzsbeoVX = true;}
      else if(ptkBxHWXOo == mcawPomQTW){ACDrIuTcoj = true;}
      if(oVckfeNoSu == fELqYiZzSH){CQHQAxOVfP = true;}
      else if(fELqYiZzSH == oVckfeNoSu){DixboFBaZt = true;}
      if(GdsGZUrYSN == irxOWluCBz){qcGKSBfJSz = true;}
      else if(irxOWluCBz == GdsGZUrYSN){bXtSwwkyMA = true;}
      if(EIRZpxHtQg == BhhsoablAf){FNDMcCjFHH = true;}
      else if(BhhsoablAf == EIRZpxHtQg){gCwUEzlbmA = true;}
      if(EaANwuyfkU == nZxQAHagxA){rQXnoNyqoV = true;}
      else if(nZxQAHagxA == EaANwuyfkU){EiAQPRTxZF = true;}
      if(atKFTJjUVu == PdbogxxVeL){EhBNKIBSgr = true;}
      if(wOxFRgEDui == LTWPmxVSCx){uVWVRnNumx = true;}
      if(XTXlpeceJe == HnylTIufOO){NJNYXaERVE = true;}
      while(PdbogxxVeL == atKFTJjUVu){VScaYcIjuM = true;}
      while(LTWPmxVSCx == LTWPmxVSCx){KVPoCBmbWo = true;}
      while(HnylTIufOO == HnylTIufOO){TYmYprXcCe = true;}
      if(KOFBiWGsLq == true){KOFBiWGsLq = false;}
      if(dFHoTTDgcC == true){dFHoTTDgcC = false;}
      if(kIdzsbeoVX == true){kIdzsbeoVX = false;}
      if(CQHQAxOVfP == true){CQHQAxOVfP = false;}
      if(qcGKSBfJSz == true){qcGKSBfJSz = false;}
      if(FNDMcCjFHH == true){FNDMcCjFHH = false;}
      if(rQXnoNyqoV == true){rQXnoNyqoV = false;}
      if(EhBNKIBSgr == true){EhBNKIBSgr = false;}
      if(uVWVRnNumx == true){uVWVRnNumx = false;}
      if(NJNYXaERVE == true){NJNYXaERVE = false;}
      if(CoTwuXLpBT == true){CoTwuXLpBT = false;}
      if(AQYPLWsCVA == true){AQYPLWsCVA = false;}
      if(ACDrIuTcoj == true){ACDrIuTcoj = false;}
      if(DixboFBaZt == true){DixboFBaZt = false;}
      if(bXtSwwkyMA == true){bXtSwwkyMA = false;}
      if(gCwUEzlbmA == true){gCwUEzlbmA = false;}
      if(EiAQPRTxZF == true){EiAQPRTxZF = false;}
      if(VScaYcIjuM == true){VScaYcIjuM = false;}
      if(KVPoCBmbWo == true){KVPoCBmbWo = false;}
      if(TYmYprXcCe == true){TYmYprXcCe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCGYIMUCWD
{ 
  void RpTuWmtcBH()
  { 
      bool qrLDWrwojZ = false;
      bool KoULlFQWws = false;
      bool hVOBELOOAs = false;
      bool THVyXTgAPZ = false;
      bool XRMjBrXmcj = false;
      bool UXHnsUcJzL = false;
      bool dhnpFDTWnS = false;
      bool XPGVUQJezL = false;
      bool nakQXwAhEC = false;
      bool pWAEupcVdy = false;
      bool XAzJLEQkSc = false;
      bool LyJmWCwWRI = false;
      bool DkSkcAOCae = false;
      bool mnABmmbaFT = false;
      bool fOPbqqNNgs = false;
      bool sFDVumhNgK = false;
      bool oOKmoXyIzj = false;
      bool aURycnVqsk = false;
      bool mBUgkgjeFA = false;
      bool FNttdQEclT = false;
      string zFinkPEEji;
      string jtVtoamaah;
      string HfQILHunaF;
      string dnMVLcMzfo;
      string MulFDepUMm;
      string DJKITToacd;
      string TQddFwgAhM;
      string NnukULsKEf;
      string QaamBTdECq;
      string mlVCVwQHzG;
      string yplAZPNYmH;
      string adVwMsoqck;
      string SbxqYbRsPY;
      string tkLxhanaNl;
      string GERtQJPZob;
      string GZeOnVruay;
      string xUJNNoSXOl;
      string EOdpeOKDZO;
      string LrDmRTGwJM;
      string hszPoktDgb;
      if(zFinkPEEji == yplAZPNYmH){qrLDWrwojZ = true;}
      else if(yplAZPNYmH == zFinkPEEji){XAzJLEQkSc = true;}
      if(jtVtoamaah == adVwMsoqck){KoULlFQWws = true;}
      else if(adVwMsoqck == jtVtoamaah){LyJmWCwWRI = true;}
      if(HfQILHunaF == SbxqYbRsPY){hVOBELOOAs = true;}
      else if(SbxqYbRsPY == HfQILHunaF){DkSkcAOCae = true;}
      if(dnMVLcMzfo == tkLxhanaNl){THVyXTgAPZ = true;}
      else if(tkLxhanaNl == dnMVLcMzfo){mnABmmbaFT = true;}
      if(MulFDepUMm == GERtQJPZob){XRMjBrXmcj = true;}
      else if(GERtQJPZob == MulFDepUMm){fOPbqqNNgs = true;}
      if(DJKITToacd == GZeOnVruay){UXHnsUcJzL = true;}
      else if(GZeOnVruay == DJKITToacd){sFDVumhNgK = true;}
      if(TQddFwgAhM == xUJNNoSXOl){dhnpFDTWnS = true;}
      else if(xUJNNoSXOl == TQddFwgAhM){oOKmoXyIzj = true;}
      if(NnukULsKEf == EOdpeOKDZO){XPGVUQJezL = true;}
      if(QaamBTdECq == LrDmRTGwJM){nakQXwAhEC = true;}
      if(mlVCVwQHzG == hszPoktDgb){pWAEupcVdy = true;}
      while(EOdpeOKDZO == NnukULsKEf){aURycnVqsk = true;}
      while(LrDmRTGwJM == LrDmRTGwJM){mBUgkgjeFA = true;}
      while(hszPoktDgb == hszPoktDgb){FNttdQEclT = true;}
      if(qrLDWrwojZ == true){qrLDWrwojZ = false;}
      if(KoULlFQWws == true){KoULlFQWws = false;}
      if(hVOBELOOAs == true){hVOBELOOAs = false;}
      if(THVyXTgAPZ == true){THVyXTgAPZ = false;}
      if(XRMjBrXmcj == true){XRMjBrXmcj = false;}
      if(UXHnsUcJzL == true){UXHnsUcJzL = false;}
      if(dhnpFDTWnS == true){dhnpFDTWnS = false;}
      if(XPGVUQJezL == true){XPGVUQJezL = false;}
      if(nakQXwAhEC == true){nakQXwAhEC = false;}
      if(pWAEupcVdy == true){pWAEupcVdy = false;}
      if(XAzJLEQkSc == true){XAzJLEQkSc = false;}
      if(LyJmWCwWRI == true){LyJmWCwWRI = false;}
      if(DkSkcAOCae == true){DkSkcAOCae = false;}
      if(mnABmmbaFT == true){mnABmmbaFT = false;}
      if(fOPbqqNNgs == true){fOPbqqNNgs = false;}
      if(sFDVumhNgK == true){sFDVumhNgK = false;}
      if(oOKmoXyIzj == true){oOKmoXyIzj = false;}
      if(aURycnVqsk == true){aURycnVqsk = false;}
      if(mBUgkgjeFA == true){mBUgkgjeFA = false;}
      if(FNttdQEclT == true){FNttdQEclT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFRPDZRWOD
{ 
  void QZVOTrNGok()
  { 
      bool yfwxXiQBSd = false;
      bool qdFQAFVyEK = false;
      bool sOTdLZfxCH = false;
      bool MoArmlRVsJ = false;
      bool hHAlkKbRIG = false;
      bool YmJJUiMRlx = false;
      bool DTyLQCcMdN = false;
      bool mAEtclOgsB = false;
      bool yOowhYeqXD = false;
      bool ZzjuGOIoVi = false;
      bool gPmtTYiOgi = false;
      bool UeYjzneBcq = false;
      bool WloZnmPImN = false;
      bool cYLJTibtcJ = false;
      bool pQJnhuazwS = false;
      bool jGMdMtZNGf = false;
      bool IZaTGwSPPQ = false;
      bool MjYTBGcAqr = false;
      bool MQMUdVMhxZ = false;
      bool INnwAPophl = false;
      string OHULcxNiNg;
      string bAhJCbnVqz;
      string EFjSDzUEQC;
      string CKjWycxoQL;
      string IZWluYLswi;
      string kLthLJWCIc;
      string cIRLdQQLKZ;
      string ezFfqeiyXe;
      string nbIgQqPCLo;
      string FugmhzHKId;
      string HzhWDkGNpg;
      string ZYddoBAjtm;
      string BOAVTjRRyr;
      string WYosWnskcf;
      string jBLeOgQDyf;
      string yXPVcszLDT;
      string ToPyJBijHA;
      string HOGOCzCVGl;
      string SOTRszITQc;
      string ohhJLulNUN;
      if(OHULcxNiNg == HzhWDkGNpg){yfwxXiQBSd = true;}
      else if(HzhWDkGNpg == OHULcxNiNg){gPmtTYiOgi = true;}
      if(bAhJCbnVqz == ZYddoBAjtm){qdFQAFVyEK = true;}
      else if(ZYddoBAjtm == bAhJCbnVqz){UeYjzneBcq = true;}
      if(EFjSDzUEQC == BOAVTjRRyr){sOTdLZfxCH = true;}
      else if(BOAVTjRRyr == EFjSDzUEQC){WloZnmPImN = true;}
      if(CKjWycxoQL == WYosWnskcf){MoArmlRVsJ = true;}
      else if(WYosWnskcf == CKjWycxoQL){cYLJTibtcJ = true;}
      if(IZWluYLswi == jBLeOgQDyf){hHAlkKbRIG = true;}
      else if(jBLeOgQDyf == IZWluYLswi){pQJnhuazwS = true;}
      if(kLthLJWCIc == yXPVcszLDT){YmJJUiMRlx = true;}
      else if(yXPVcszLDT == kLthLJWCIc){jGMdMtZNGf = true;}
      if(cIRLdQQLKZ == ToPyJBijHA){DTyLQCcMdN = true;}
      else if(ToPyJBijHA == cIRLdQQLKZ){IZaTGwSPPQ = true;}
      if(ezFfqeiyXe == HOGOCzCVGl){mAEtclOgsB = true;}
      if(nbIgQqPCLo == SOTRszITQc){yOowhYeqXD = true;}
      if(FugmhzHKId == ohhJLulNUN){ZzjuGOIoVi = true;}
      while(HOGOCzCVGl == ezFfqeiyXe){MjYTBGcAqr = true;}
      while(SOTRszITQc == SOTRszITQc){MQMUdVMhxZ = true;}
      while(ohhJLulNUN == ohhJLulNUN){INnwAPophl = true;}
      if(yfwxXiQBSd == true){yfwxXiQBSd = false;}
      if(qdFQAFVyEK == true){qdFQAFVyEK = false;}
      if(sOTdLZfxCH == true){sOTdLZfxCH = false;}
      if(MoArmlRVsJ == true){MoArmlRVsJ = false;}
      if(hHAlkKbRIG == true){hHAlkKbRIG = false;}
      if(YmJJUiMRlx == true){YmJJUiMRlx = false;}
      if(DTyLQCcMdN == true){DTyLQCcMdN = false;}
      if(mAEtclOgsB == true){mAEtclOgsB = false;}
      if(yOowhYeqXD == true){yOowhYeqXD = false;}
      if(ZzjuGOIoVi == true){ZzjuGOIoVi = false;}
      if(gPmtTYiOgi == true){gPmtTYiOgi = false;}
      if(UeYjzneBcq == true){UeYjzneBcq = false;}
      if(WloZnmPImN == true){WloZnmPImN = false;}
      if(cYLJTibtcJ == true){cYLJTibtcJ = false;}
      if(pQJnhuazwS == true){pQJnhuazwS = false;}
      if(jGMdMtZNGf == true){jGMdMtZNGf = false;}
      if(IZaTGwSPPQ == true){IZaTGwSPPQ = false;}
      if(MjYTBGcAqr == true){MjYTBGcAqr = false;}
      if(MQMUdVMhxZ == true){MQMUdVMhxZ = false;}
      if(INnwAPophl == true){INnwAPophl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJZGHJJFAU
{ 
  void khJmFpWoPk()
  { 
      bool QeNMuJMHia = false;
      bool EgTDssuGGQ = false;
      bool EVQBRzAnFQ = false;
      bool cdyxbNMEZe = false;
      bool TjnfXoXDHb = false;
      bool DBRLWtNLtw = false;
      bool JXBSxZiVaf = false;
      bool fqgaxUgkdc = false;
      bool awfcMbLlZh = false;
      bool zBJcVwhVix = false;
      bool FBbbuMUqNC = false;
      bool NcgRUMqYFU = false;
      bool OwwsfegDFB = false;
      bool mLCgWYTEhA = false;
      bool HUYXUWTrII = false;
      bool FJPNiIFhwQ = false;
      bool eQkMPBaAtu = false;
      bool slpFNsXXYI = false;
      bool KntwwdunxO = false;
      bool TkIQUpiMIS = false;
      string FOIRJIFiic;
      string RGGZdSGPnf;
      string sNwToCGnlo;
      string JbKAjwfhbQ;
      string udqwVaOfhS;
      string LSHmtqSncG;
      string CRxsTouGog;
      string lYmWjOWAyO;
      string mZFTcqUXFr;
      string crFUOdfxbf;
      string eIpAfmejCf;
      string USoNTbLdPb;
      string UXAxEtSSIG;
      string hYXRiejEmo;
      string LjUZXKCrBm;
      string RChzLHIrwl;
      string UMbwxutXdo;
      string qHpaQkCaYs;
      string raQVofqXGb;
      string WqHBUzHYcb;
      if(FOIRJIFiic == eIpAfmejCf){QeNMuJMHia = true;}
      else if(eIpAfmejCf == FOIRJIFiic){FBbbuMUqNC = true;}
      if(RGGZdSGPnf == USoNTbLdPb){EgTDssuGGQ = true;}
      else if(USoNTbLdPb == RGGZdSGPnf){NcgRUMqYFU = true;}
      if(sNwToCGnlo == UXAxEtSSIG){EVQBRzAnFQ = true;}
      else if(UXAxEtSSIG == sNwToCGnlo){OwwsfegDFB = true;}
      if(JbKAjwfhbQ == hYXRiejEmo){cdyxbNMEZe = true;}
      else if(hYXRiejEmo == JbKAjwfhbQ){mLCgWYTEhA = true;}
      if(udqwVaOfhS == LjUZXKCrBm){TjnfXoXDHb = true;}
      else if(LjUZXKCrBm == udqwVaOfhS){HUYXUWTrII = true;}
      if(LSHmtqSncG == RChzLHIrwl){DBRLWtNLtw = true;}
      else if(RChzLHIrwl == LSHmtqSncG){FJPNiIFhwQ = true;}
      if(CRxsTouGog == UMbwxutXdo){JXBSxZiVaf = true;}
      else if(UMbwxutXdo == CRxsTouGog){eQkMPBaAtu = true;}
      if(lYmWjOWAyO == qHpaQkCaYs){fqgaxUgkdc = true;}
      if(mZFTcqUXFr == raQVofqXGb){awfcMbLlZh = true;}
      if(crFUOdfxbf == WqHBUzHYcb){zBJcVwhVix = true;}
      while(qHpaQkCaYs == lYmWjOWAyO){slpFNsXXYI = true;}
      while(raQVofqXGb == raQVofqXGb){KntwwdunxO = true;}
      while(WqHBUzHYcb == WqHBUzHYcb){TkIQUpiMIS = true;}
      if(QeNMuJMHia == true){QeNMuJMHia = false;}
      if(EgTDssuGGQ == true){EgTDssuGGQ = false;}
      if(EVQBRzAnFQ == true){EVQBRzAnFQ = false;}
      if(cdyxbNMEZe == true){cdyxbNMEZe = false;}
      if(TjnfXoXDHb == true){TjnfXoXDHb = false;}
      if(DBRLWtNLtw == true){DBRLWtNLtw = false;}
      if(JXBSxZiVaf == true){JXBSxZiVaf = false;}
      if(fqgaxUgkdc == true){fqgaxUgkdc = false;}
      if(awfcMbLlZh == true){awfcMbLlZh = false;}
      if(zBJcVwhVix == true){zBJcVwhVix = false;}
      if(FBbbuMUqNC == true){FBbbuMUqNC = false;}
      if(NcgRUMqYFU == true){NcgRUMqYFU = false;}
      if(OwwsfegDFB == true){OwwsfegDFB = false;}
      if(mLCgWYTEhA == true){mLCgWYTEhA = false;}
      if(HUYXUWTrII == true){HUYXUWTrII = false;}
      if(FJPNiIFhwQ == true){FJPNiIFhwQ = false;}
      if(eQkMPBaAtu == true){eQkMPBaAtu = false;}
      if(slpFNsXXYI == true){slpFNsXXYI = false;}
      if(KntwwdunxO == true){KntwwdunxO = false;}
      if(TkIQUpiMIS == true){TkIQUpiMIS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIRGISBMUW
{ 
  void skywDVDAib()
  { 
      bool LROZkVxdOd = false;
      bool IROOVdmxLE = false;
      bool eYWLqtmsAg = false;
      bool xaraRbVlrE = false;
      bool ZKuubnHMAu = false;
      bool rOSTNmuDhp = false;
      bool hEchggZnxs = false;
      bool IBEHdUcbiD = false;
      bool larEnhHXMe = false;
      bool gRECVVgNOu = false;
      bool OTOGmqKLps = false;
      bool JSTeDHLXsy = false;
      bool YBaSMpxClI = false;
      bool mONnnSLlRx = false;
      bool XwhTUNxYyN = false;
      bool JJUPVMswtw = false;
      bool tHYgGtFfpk = false;
      bool wZGuabTHyy = false;
      bool sXDXydtxRb = false;
      bool YOqVDPXANZ = false;
      string YPoxqfVYVB;
      string zfIKlPpYRZ;
      string XwleOSpxOH;
      string rGrcCuiogN;
      string sYheeafWJE;
      string KbLdNbdKiX;
      string oXKNJsmfHq;
      string gBrEfzOHAm;
      string mTnJxPuOOa;
      string RYGIXVNUUl;
      string mzOSXJjGxN;
      string NVKukVjAPs;
      string xYRgYItjfK;
      string kslNznEUkn;
      string fnRAMuOKWC;
      string kMEbnOhhsP;
      string OAalcTiwux;
      string QOPaMJGQTd;
      string tjMdZXnKYj;
      string FWbVZfMeXs;
      if(YPoxqfVYVB == mzOSXJjGxN){LROZkVxdOd = true;}
      else if(mzOSXJjGxN == YPoxqfVYVB){OTOGmqKLps = true;}
      if(zfIKlPpYRZ == NVKukVjAPs){IROOVdmxLE = true;}
      else if(NVKukVjAPs == zfIKlPpYRZ){JSTeDHLXsy = true;}
      if(XwleOSpxOH == xYRgYItjfK){eYWLqtmsAg = true;}
      else if(xYRgYItjfK == XwleOSpxOH){YBaSMpxClI = true;}
      if(rGrcCuiogN == kslNznEUkn){xaraRbVlrE = true;}
      else if(kslNznEUkn == rGrcCuiogN){mONnnSLlRx = true;}
      if(sYheeafWJE == fnRAMuOKWC){ZKuubnHMAu = true;}
      else if(fnRAMuOKWC == sYheeafWJE){XwhTUNxYyN = true;}
      if(KbLdNbdKiX == kMEbnOhhsP){rOSTNmuDhp = true;}
      else if(kMEbnOhhsP == KbLdNbdKiX){JJUPVMswtw = true;}
      if(oXKNJsmfHq == OAalcTiwux){hEchggZnxs = true;}
      else if(OAalcTiwux == oXKNJsmfHq){tHYgGtFfpk = true;}
      if(gBrEfzOHAm == QOPaMJGQTd){IBEHdUcbiD = true;}
      if(mTnJxPuOOa == tjMdZXnKYj){larEnhHXMe = true;}
      if(RYGIXVNUUl == FWbVZfMeXs){gRECVVgNOu = true;}
      while(QOPaMJGQTd == gBrEfzOHAm){wZGuabTHyy = true;}
      while(tjMdZXnKYj == tjMdZXnKYj){sXDXydtxRb = true;}
      while(FWbVZfMeXs == FWbVZfMeXs){YOqVDPXANZ = true;}
      if(LROZkVxdOd == true){LROZkVxdOd = false;}
      if(IROOVdmxLE == true){IROOVdmxLE = false;}
      if(eYWLqtmsAg == true){eYWLqtmsAg = false;}
      if(xaraRbVlrE == true){xaraRbVlrE = false;}
      if(ZKuubnHMAu == true){ZKuubnHMAu = false;}
      if(rOSTNmuDhp == true){rOSTNmuDhp = false;}
      if(hEchggZnxs == true){hEchggZnxs = false;}
      if(IBEHdUcbiD == true){IBEHdUcbiD = false;}
      if(larEnhHXMe == true){larEnhHXMe = false;}
      if(gRECVVgNOu == true){gRECVVgNOu = false;}
      if(OTOGmqKLps == true){OTOGmqKLps = false;}
      if(JSTeDHLXsy == true){JSTeDHLXsy = false;}
      if(YBaSMpxClI == true){YBaSMpxClI = false;}
      if(mONnnSLlRx == true){mONnnSLlRx = false;}
      if(XwhTUNxYyN == true){XwhTUNxYyN = false;}
      if(JJUPVMswtw == true){JJUPVMswtw = false;}
      if(tHYgGtFfpk == true){tHYgGtFfpk = false;}
      if(wZGuabTHyy == true){wZGuabTHyy = false;}
      if(sXDXydtxRb == true){sXDXydtxRb = false;}
      if(YOqVDPXANZ == true){YOqVDPXANZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NBACKFWGWA
{ 
  void ziBjUxqteO()
  { 
      bool EbinSWHUsw = false;
      bool ZeNBiORNZj = false;
      bool yjzpEgFAKt = false;
      bool UllAeXnzgw = false;
      bool qqFWqAGcfF = false;
      bool mKdsxUcsjl = false;
      bool RHKyamsMVK = false;
      bool ZSfcsGdbzE = false;
      bool ZbUEHKIsCJ = false;
      bool tuOuejfGuD = false;
      bool GsHUeUdAAp = false;
      bool qAtfLolGqQ = false;
      bool eAKLPeDkxI = false;
      bool aWguxgUzYm = false;
      bool fHsLStAiio = false;
      bool xZPdXGhuFz = false;
      bool RsCqPTTyie = false;
      bool UmgDkXGzsV = false;
      bool eTCILAGCXp = false;
      bool yZtZVmECuy = false;
      string DGIBEzyJzc;
      string TOJcZtqhlQ;
      string ahiBgBeWVD;
      string qUOVyldylS;
      string iWhnVAHpxu;
      string tOAAHVWHUD;
      string Tanwlzznem;
      string QrwShDzufg;
      string soZaJcTOOc;
      string PVdiyHilCV;
      string ATLJdBSgSD;
      string WbbmJeAMlJ;
      string fkZCXtOMTZ;
      string UMrJfZcQxH;
      string JluKGntpYT;
      string GWAspPtJki;
      string mFNrhKiRGj;
      string BjOezsoOwj;
      string AXnzSyLzSQ;
      string fTeOUEYDcu;
      if(DGIBEzyJzc == ATLJdBSgSD){EbinSWHUsw = true;}
      else if(ATLJdBSgSD == DGIBEzyJzc){GsHUeUdAAp = true;}
      if(TOJcZtqhlQ == WbbmJeAMlJ){ZeNBiORNZj = true;}
      else if(WbbmJeAMlJ == TOJcZtqhlQ){qAtfLolGqQ = true;}
      if(ahiBgBeWVD == fkZCXtOMTZ){yjzpEgFAKt = true;}
      else if(fkZCXtOMTZ == ahiBgBeWVD){eAKLPeDkxI = true;}
      if(qUOVyldylS == UMrJfZcQxH){UllAeXnzgw = true;}
      else if(UMrJfZcQxH == qUOVyldylS){aWguxgUzYm = true;}
      if(iWhnVAHpxu == JluKGntpYT){qqFWqAGcfF = true;}
      else if(JluKGntpYT == iWhnVAHpxu){fHsLStAiio = true;}
      if(tOAAHVWHUD == GWAspPtJki){mKdsxUcsjl = true;}
      else if(GWAspPtJki == tOAAHVWHUD){xZPdXGhuFz = true;}
      if(Tanwlzznem == mFNrhKiRGj){RHKyamsMVK = true;}
      else if(mFNrhKiRGj == Tanwlzznem){RsCqPTTyie = true;}
      if(QrwShDzufg == BjOezsoOwj){ZSfcsGdbzE = true;}
      if(soZaJcTOOc == AXnzSyLzSQ){ZbUEHKIsCJ = true;}
      if(PVdiyHilCV == fTeOUEYDcu){tuOuejfGuD = true;}
      while(BjOezsoOwj == QrwShDzufg){UmgDkXGzsV = true;}
      while(AXnzSyLzSQ == AXnzSyLzSQ){eTCILAGCXp = true;}
      while(fTeOUEYDcu == fTeOUEYDcu){yZtZVmECuy = true;}
      if(EbinSWHUsw == true){EbinSWHUsw = false;}
      if(ZeNBiORNZj == true){ZeNBiORNZj = false;}
      if(yjzpEgFAKt == true){yjzpEgFAKt = false;}
      if(UllAeXnzgw == true){UllAeXnzgw = false;}
      if(qqFWqAGcfF == true){qqFWqAGcfF = false;}
      if(mKdsxUcsjl == true){mKdsxUcsjl = false;}
      if(RHKyamsMVK == true){RHKyamsMVK = false;}
      if(ZSfcsGdbzE == true){ZSfcsGdbzE = false;}
      if(ZbUEHKIsCJ == true){ZbUEHKIsCJ = false;}
      if(tuOuejfGuD == true){tuOuejfGuD = false;}
      if(GsHUeUdAAp == true){GsHUeUdAAp = false;}
      if(qAtfLolGqQ == true){qAtfLolGqQ = false;}
      if(eAKLPeDkxI == true){eAKLPeDkxI = false;}
      if(aWguxgUzYm == true){aWguxgUzYm = false;}
      if(fHsLStAiio == true){fHsLStAiio = false;}
      if(xZPdXGhuFz == true){xZPdXGhuFz = false;}
      if(RsCqPTTyie == true){RsCqPTTyie = false;}
      if(UmgDkXGzsV == true){UmgDkXGzsV = false;}
      if(eTCILAGCXp == true){eTCILAGCXp = false;}
      if(yZtZVmECuy == true){yZtZVmECuy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMJAZOPDQT
{ 
  void lcNUGsfAzC()
  { 
      bool FcMsCSBidZ = false;
      bool zrzdwIaDVo = false;
      bool HuXspEeWaw = false;
      bool HFHISbyQsE = false;
      bool tHbWKlNLPk = false;
      bool feSOWKETCx = false;
      bool meHhStkqKT = false;
      bool KKKRuATBhD = false;
      bool qTGpQbmrlI = false;
      bool WdOuROzsEP = false;
      bool BWAwZVUBTW = false;
      bool pDlyGSXRQp = false;
      bool HsECxfwOzf = false;
      bool AZwSCTTKPu = false;
      bool HkXPRSrPny = false;
      bool qgcOIHRyyt = false;
      bool ZGBnVQHSwm = false;
      bool zNCVhVUojd = false;
      bool mfZAoSwhJt = false;
      bool BULUVBjjsA = false;
      string iEHmxFJaCA;
      string yGsXdIEENn;
      string ILwTGDkbLI;
      string CXtkpEVENH;
      string fwfcPgNjFr;
      string wAXKdWImgt;
      string TgPtyZLIhZ;
      string mAqFHMeSDZ;
      string oBWSLBAjGS;
      string uhXSnyglep;
      string UFBfFwJRCR;
      string qoiHESKwiw;
      string YaBOdEbXRJ;
      string fsnNEiApNO;
      string rigobGzQNU;
      string mjDhQtElBB;
      string UkArkxBVDU;
      string SUiUDptLmX;
      string FLJwWupFxK;
      string eNoLsHinEd;
      if(iEHmxFJaCA == UFBfFwJRCR){FcMsCSBidZ = true;}
      else if(UFBfFwJRCR == iEHmxFJaCA){BWAwZVUBTW = true;}
      if(yGsXdIEENn == qoiHESKwiw){zrzdwIaDVo = true;}
      else if(qoiHESKwiw == yGsXdIEENn){pDlyGSXRQp = true;}
      if(ILwTGDkbLI == YaBOdEbXRJ){HuXspEeWaw = true;}
      else if(YaBOdEbXRJ == ILwTGDkbLI){HsECxfwOzf = true;}
      if(CXtkpEVENH == fsnNEiApNO){HFHISbyQsE = true;}
      else if(fsnNEiApNO == CXtkpEVENH){AZwSCTTKPu = true;}
      if(fwfcPgNjFr == rigobGzQNU){tHbWKlNLPk = true;}
      else if(rigobGzQNU == fwfcPgNjFr){HkXPRSrPny = true;}
      if(wAXKdWImgt == mjDhQtElBB){feSOWKETCx = true;}
      else if(mjDhQtElBB == wAXKdWImgt){qgcOIHRyyt = true;}
      if(TgPtyZLIhZ == UkArkxBVDU){meHhStkqKT = true;}
      else if(UkArkxBVDU == TgPtyZLIhZ){ZGBnVQHSwm = true;}
      if(mAqFHMeSDZ == SUiUDptLmX){KKKRuATBhD = true;}
      if(oBWSLBAjGS == FLJwWupFxK){qTGpQbmrlI = true;}
      if(uhXSnyglep == eNoLsHinEd){WdOuROzsEP = true;}
      while(SUiUDptLmX == mAqFHMeSDZ){zNCVhVUojd = true;}
      while(FLJwWupFxK == FLJwWupFxK){mfZAoSwhJt = true;}
      while(eNoLsHinEd == eNoLsHinEd){BULUVBjjsA = true;}
      if(FcMsCSBidZ == true){FcMsCSBidZ = false;}
      if(zrzdwIaDVo == true){zrzdwIaDVo = false;}
      if(HuXspEeWaw == true){HuXspEeWaw = false;}
      if(HFHISbyQsE == true){HFHISbyQsE = false;}
      if(tHbWKlNLPk == true){tHbWKlNLPk = false;}
      if(feSOWKETCx == true){feSOWKETCx = false;}
      if(meHhStkqKT == true){meHhStkqKT = false;}
      if(KKKRuATBhD == true){KKKRuATBhD = false;}
      if(qTGpQbmrlI == true){qTGpQbmrlI = false;}
      if(WdOuROzsEP == true){WdOuROzsEP = false;}
      if(BWAwZVUBTW == true){BWAwZVUBTW = false;}
      if(pDlyGSXRQp == true){pDlyGSXRQp = false;}
      if(HsECxfwOzf == true){HsECxfwOzf = false;}
      if(AZwSCTTKPu == true){AZwSCTTKPu = false;}
      if(HkXPRSrPny == true){HkXPRSrPny = false;}
      if(qgcOIHRyyt == true){qgcOIHRyyt = false;}
      if(ZGBnVQHSwm == true){ZGBnVQHSwm = false;}
      if(zNCVhVUojd == true){zNCVhVUojd = false;}
      if(mfZAoSwhJt == true){mfZAoSwhJt = false;}
      if(BULUVBjjsA == true){BULUVBjjsA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQZPISOYSK
{ 
  void VDHwrZWHXV()
  { 
      bool uiQcMZpdoO = false;
      bool zrxoibWUdd = false;
      bool gbZfdpPQti = false;
      bool RgIDpEYMHh = false;
      bool TRabyjuHJs = false;
      bool ScdlwSJkyV = false;
      bool KYjFxSjszd = false;
      bool DKNuKOBxgt = false;
      bool uHHAQnCWHW = false;
      bool umNkXthUef = false;
      bool ABHeoIPiah = false;
      bool RMEEZCRioI = false;
      bool PMlciPwbXP = false;
      bool fgRBsszbLH = false;
      bool XTuYEiiJLU = false;
      bool bzeVPmPewY = false;
      bool MmKLCjtCKg = false;
      bool DpWgjuRMXA = false;
      bool glQDnfCwlG = false;
      bool cUflukIjWU = false;
      string ZXYMnJTOfG;
      string FnFioEagKA;
      string JXegoDPKNm;
      string nKdeYEdgVt;
      string ganIcgSbkl;
      string xyTBeBsqWk;
      string sJBrRtKaKk;
      string atKPThjVEI;
      string knYbppqbzW;
      string LlJkAXYuqh;
      string WqRALCmDhw;
      string RWmOAFjZCb;
      string DhamZnjZOu;
      string JoeVksWXPm;
      string CmtDFnztju;
      string mzsOenQdaW;
      string RMnlmcrQcH;
      string iMJOYPnXgk;
      string nppTIJwPqx;
      string crxrUpyHPc;
      if(ZXYMnJTOfG == WqRALCmDhw){uiQcMZpdoO = true;}
      else if(WqRALCmDhw == ZXYMnJTOfG){ABHeoIPiah = true;}
      if(FnFioEagKA == RWmOAFjZCb){zrxoibWUdd = true;}
      else if(RWmOAFjZCb == FnFioEagKA){RMEEZCRioI = true;}
      if(JXegoDPKNm == DhamZnjZOu){gbZfdpPQti = true;}
      else if(DhamZnjZOu == JXegoDPKNm){PMlciPwbXP = true;}
      if(nKdeYEdgVt == JoeVksWXPm){RgIDpEYMHh = true;}
      else if(JoeVksWXPm == nKdeYEdgVt){fgRBsszbLH = true;}
      if(ganIcgSbkl == CmtDFnztju){TRabyjuHJs = true;}
      else if(CmtDFnztju == ganIcgSbkl){XTuYEiiJLU = true;}
      if(xyTBeBsqWk == mzsOenQdaW){ScdlwSJkyV = true;}
      else if(mzsOenQdaW == xyTBeBsqWk){bzeVPmPewY = true;}
      if(sJBrRtKaKk == RMnlmcrQcH){KYjFxSjszd = true;}
      else if(RMnlmcrQcH == sJBrRtKaKk){MmKLCjtCKg = true;}
      if(atKPThjVEI == iMJOYPnXgk){DKNuKOBxgt = true;}
      if(knYbppqbzW == nppTIJwPqx){uHHAQnCWHW = true;}
      if(LlJkAXYuqh == crxrUpyHPc){umNkXthUef = true;}
      while(iMJOYPnXgk == atKPThjVEI){DpWgjuRMXA = true;}
      while(nppTIJwPqx == nppTIJwPqx){glQDnfCwlG = true;}
      while(crxrUpyHPc == crxrUpyHPc){cUflukIjWU = true;}
      if(uiQcMZpdoO == true){uiQcMZpdoO = false;}
      if(zrxoibWUdd == true){zrxoibWUdd = false;}
      if(gbZfdpPQti == true){gbZfdpPQti = false;}
      if(RgIDpEYMHh == true){RgIDpEYMHh = false;}
      if(TRabyjuHJs == true){TRabyjuHJs = false;}
      if(ScdlwSJkyV == true){ScdlwSJkyV = false;}
      if(KYjFxSjszd == true){KYjFxSjszd = false;}
      if(DKNuKOBxgt == true){DKNuKOBxgt = false;}
      if(uHHAQnCWHW == true){uHHAQnCWHW = false;}
      if(umNkXthUef == true){umNkXthUef = false;}
      if(ABHeoIPiah == true){ABHeoIPiah = false;}
      if(RMEEZCRioI == true){RMEEZCRioI = false;}
      if(PMlciPwbXP == true){PMlciPwbXP = false;}
      if(fgRBsszbLH == true){fgRBsszbLH = false;}
      if(XTuYEiiJLU == true){XTuYEiiJLU = false;}
      if(bzeVPmPewY == true){bzeVPmPewY = false;}
      if(MmKLCjtCKg == true){MmKLCjtCKg = false;}
      if(DpWgjuRMXA == true){DpWgjuRMXA = false;}
      if(glQDnfCwlG == true){glQDnfCwlG = false;}
      if(cUflukIjWU == true){cUflukIjWU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYHRATPSPK
{ 
  void LmOXELhBZF()
  { 
      bool XPazNMoDbY = false;
      bool opahkrrQbb = false;
      bool FMrnLbTWWC = false;
      bool tcnDgylCen = false;
      bool XHnJNokrwn = false;
      bool GCtLWKWmmk = false;
      bool rSgZeMBXBm = false;
      bool GpknDyYiZV = false;
      bool qbZiwqhcgV = false;
      bool azOtuFZNdB = false;
      bool nNpIgQQGHY = false;
      bool kmMQtQrydm = false;
      bool dXqfMHaqrx = false;
      bool XKEYhclQBe = false;
      bool abUHjmlxze = false;
      bool MbjqXPVKwZ = false;
      bool oZOKBahnhQ = false;
      bool dawyMBDiuY = false;
      bool UdqMjuaNBS = false;
      bool GbUapBMKGJ = false;
      string UmqbXmsGGE;
      string OXpXjYGHXA;
      string tXDxHQedhs;
      string jqoMXHgXkS;
      string dEJoAYyeWw;
      string UHJFlwjsTG;
      string IPXNUXiczc;
      string riVFVoONxi;
      string RzHlXcgiZa;
      string WmDdKOgwUc;
      string oUfsEkkEjx;
      string hVwknIIlor;
      string pzDYFEfqtH;
      string IRrUsxTNgl;
      string qczbrBqSpC;
      string GtGclpRHmz;
      string FsJcoQcaqq;
      string ntEDANAafE;
      string NNBrANKPhD;
      string eMahfySWmb;
      if(UmqbXmsGGE == oUfsEkkEjx){XPazNMoDbY = true;}
      else if(oUfsEkkEjx == UmqbXmsGGE){nNpIgQQGHY = true;}
      if(OXpXjYGHXA == hVwknIIlor){opahkrrQbb = true;}
      else if(hVwknIIlor == OXpXjYGHXA){kmMQtQrydm = true;}
      if(tXDxHQedhs == pzDYFEfqtH){FMrnLbTWWC = true;}
      else if(pzDYFEfqtH == tXDxHQedhs){dXqfMHaqrx = true;}
      if(jqoMXHgXkS == IRrUsxTNgl){tcnDgylCen = true;}
      else if(IRrUsxTNgl == jqoMXHgXkS){XKEYhclQBe = true;}
      if(dEJoAYyeWw == qczbrBqSpC){XHnJNokrwn = true;}
      else if(qczbrBqSpC == dEJoAYyeWw){abUHjmlxze = true;}
      if(UHJFlwjsTG == GtGclpRHmz){GCtLWKWmmk = true;}
      else if(GtGclpRHmz == UHJFlwjsTG){MbjqXPVKwZ = true;}
      if(IPXNUXiczc == FsJcoQcaqq){rSgZeMBXBm = true;}
      else if(FsJcoQcaqq == IPXNUXiczc){oZOKBahnhQ = true;}
      if(riVFVoONxi == ntEDANAafE){GpknDyYiZV = true;}
      if(RzHlXcgiZa == NNBrANKPhD){qbZiwqhcgV = true;}
      if(WmDdKOgwUc == eMahfySWmb){azOtuFZNdB = true;}
      while(ntEDANAafE == riVFVoONxi){dawyMBDiuY = true;}
      while(NNBrANKPhD == NNBrANKPhD){UdqMjuaNBS = true;}
      while(eMahfySWmb == eMahfySWmb){GbUapBMKGJ = true;}
      if(XPazNMoDbY == true){XPazNMoDbY = false;}
      if(opahkrrQbb == true){opahkrrQbb = false;}
      if(FMrnLbTWWC == true){FMrnLbTWWC = false;}
      if(tcnDgylCen == true){tcnDgylCen = false;}
      if(XHnJNokrwn == true){XHnJNokrwn = false;}
      if(GCtLWKWmmk == true){GCtLWKWmmk = false;}
      if(rSgZeMBXBm == true){rSgZeMBXBm = false;}
      if(GpknDyYiZV == true){GpknDyYiZV = false;}
      if(qbZiwqhcgV == true){qbZiwqhcgV = false;}
      if(azOtuFZNdB == true){azOtuFZNdB = false;}
      if(nNpIgQQGHY == true){nNpIgQQGHY = false;}
      if(kmMQtQrydm == true){kmMQtQrydm = false;}
      if(dXqfMHaqrx == true){dXqfMHaqrx = false;}
      if(XKEYhclQBe == true){XKEYhclQBe = false;}
      if(abUHjmlxze == true){abUHjmlxze = false;}
      if(MbjqXPVKwZ == true){MbjqXPVKwZ = false;}
      if(oZOKBahnhQ == true){oZOKBahnhQ = false;}
      if(dawyMBDiuY == true){dawyMBDiuY = false;}
      if(UdqMjuaNBS == true){UdqMjuaNBS = false;}
      if(GbUapBMKGJ == true){GbUapBMKGJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ILYHVNFOWI
{ 
  void wzWGRppjiA()
  { 
      bool rmKLKTUrpP = false;
      bool rrTpBmRwhM = false;
      bool FgODpxrGLN = false;
      bool PRHPftZBTe = false;
      bool CLBZDNcYCM = false;
      bool lBqKbLYHUN = false;
      bool bOgbzajDKH = false;
      bool NQcCKseozc = false;
      bool USEyaOawnU = false;
      bool URfFDmeYZc = false;
      bool cYOtzVXnAh = false;
      bool fjIrsIKiAk = false;
      bool znPplujWzW = false;
      bool OGPVzuEJyF = false;
      bool pluFokJnMt = false;
      bool cuXncnJXID = false;
      bool lBocTYUlry = false;
      bool EBjuuNrKBB = false;
      bool luKEtSiarK = false;
      bool kfBuToxRkP = false;
      string isPsCPneWP;
      string HVFlJzRtmW;
      string APGNCnkTmu;
      string fmKSgcOgtq;
      string hTQthpzNks;
      string DyFwUTlBqN;
      string eUqbiTKmEf;
      string kkAunfzMfL;
      string oWitqghNyN;
      string qMpfMNcoKN;
      string fMIEHSyJIn;
      string UZVeYHlxjB;
      string kwoqoYuTia;
      string DJBRfcNdmY;
      string iXFJsQqKHE;
      string beEJciWROi;
      string XdagkKYDzw;
      string sHKLSMpeyX;
      string gjMdzXErow;
      string FwPDAExYXh;
      if(isPsCPneWP == fMIEHSyJIn){rmKLKTUrpP = true;}
      else if(fMIEHSyJIn == isPsCPneWP){cYOtzVXnAh = true;}
      if(HVFlJzRtmW == UZVeYHlxjB){rrTpBmRwhM = true;}
      else if(UZVeYHlxjB == HVFlJzRtmW){fjIrsIKiAk = true;}
      if(APGNCnkTmu == kwoqoYuTia){FgODpxrGLN = true;}
      else if(kwoqoYuTia == APGNCnkTmu){znPplujWzW = true;}
      if(fmKSgcOgtq == DJBRfcNdmY){PRHPftZBTe = true;}
      else if(DJBRfcNdmY == fmKSgcOgtq){OGPVzuEJyF = true;}
      if(hTQthpzNks == iXFJsQqKHE){CLBZDNcYCM = true;}
      else if(iXFJsQqKHE == hTQthpzNks){pluFokJnMt = true;}
      if(DyFwUTlBqN == beEJciWROi){lBqKbLYHUN = true;}
      else if(beEJciWROi == DyFwUTlBqN){cuXncnJXID = true;}
      if(eUqbiTKmEf == XdagkKYDzw){bOgbzajDKH = true;}
      else if(XdagkKYDzw == eUqbiTKmEf){lBocTYUlry = true;}
      if(kkAunfzMfL == sHKLSMpeyX){NQcCKseozc = true;}
      if(oWitqghNyN == gjMdzXErow){USEyaOawnU = true;}
      if(qMpfMNcoKN == FwPDAExYXh){URfFDmeYZc = true;}
      while(sHKLSMpeyX == kkAunfzMfL){EBjuuNrKBB = true;}
      while(gjMdzXErow == gjMdzXErow){luKEtSiarK = true;}
      while(FwPDAExYXh == FwPDAExYXh){kfBuToxRkP = true;}
      if(rmKLKTUrpP == true){rmKLKTUrpP = false;}
      if(rrTpBmRwhM == true){rrTpBmRwhM = false;}
      if(FgODpxrGLN == true){FgODpxrGLN = false;}
      if(PRHPftZBTe == true){PRHPftZBTe = false;}
      if(CLBZDNcYCM == true){CLBZDNcYCM = false;}
      if(lBqKbLYHUN == true){lBqKbLYHUN = false;}
      if(bOgbzajDKH == true){bOgbzajDKH = false;}
      if(NQcCKseozc == true){NQcCKseozc = false;}
      if(USEyaOawnU == true){USEyaOawnU = false;}
      if(URfFDmeYZc == true){URfFDmeYZc = false;}
      if(cYOtzVXnAh == true){cYOtzVXnAh = false;}
      if(fjIrsIKiAk == true){fjIrsIKiAk = false;}
      if(znPplujWzW == true){znPplujWzW = false;}
      if(OGPVzuEJyF == true){OGPVzuEJyF = false;}
      if(pluFokJnMt == true){pluFokJnMt = false;}
      if(cuXncnJXID == true){cuXncnJXID = false;}
      if(lBocTYUlry == true){lBocTYUlry = false;}
      if(EBjuuNrKBB == true){EBjuuNrKBB = false;}
      if(luKEtSiarK == true){luKEtSiarK = false;}
      if(kfBuToxRkP == true){kfBuToxRkP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XBATPILILQ
{ 
  void cBMjGIjrCb()
  { 
      bool KOajeoAxNt = false;
      bool aBEAuzxVkf = false;
      bool OVGXEGoPgd = false;
      bool wbmwcIAWAe = false;
      bool nFPOPadxMH = false;
      bool POgCaoICfY = false;
      bool AkQixyOHWl = false;
      bool zaVGrIFrIc = false;
      bool bqDYOgujVn = false;
      bool AxpbeDofQQ = false;
      bool MVZZHosZKR = false;
      bool iQsCxIhqUQ = false;
      bool CdlilCjtbo = false;
      bool TYarQFRcQZ = false;
      bool mUYDEiDndV = false;
      bool VxLANhjpmF = false;
      bool EzyVyJoBlq = false;
      bool qEZuchFhdD = false;
      bool ywPFTVNadi = false;
      bool VaoLUnWDFt = false;
      string KhaGiFywwl;
      string mOVVKqWtct;
      string IFFsfGoAzy;
      string mZWIRULpZw;
      string xWGKKfJkbB;
      string XuixVEchac;
      string QxxxzMqMEp;
      string fgUfwlythA;
      string wEYxZqqYmM;
      string rcPxfAYJLy;
      string nxglVqaCBi;
      string GhzZfLYzWH;
      string VSZqxCQWAu;
      string NohjLzXlbi;
      string QnXEGJdoQT;
      string bYlEbVWonT;
      string aDCFURzOOg;
      string nlXnqhtVkn;
      string XaGfToCdIp;
      string bhxIHMkSio;
      if(KhaGiFywwl == nxglVqaCBi){KOajeoAxNt = true;}
      else if(nxglVqaCBi == KhaGiFywwl){MVZZHosZKR = true;}
      if(mOVVKqWtct == GhzZfLYzWH){aBEAuzxVkf = true;}
      else if(GhzZfLYzWH == mOVVKqWtct){iQsCxIhqUQ = true;}
      if(IFFsfGoAzy == VSZqxCQWAu){OVGXEGoPgd = true;}
      else if(VSZqxCQWAu == IFFsfGoAzy){CdlilCjtbo = true;}
      if(mZWIRULpZw == NohjLzXlbi){wbmwcIAWAe = true;}
      else if(NohjLzXlbi == mZWIRULpZw){TYarQFRcQZ = true;}
      if(xWGKKfJkbB == QnXEGJdoQT){nFPOPadxMH = true;}
      else if(QnXEGJdoQT == xWGKKfJkbB){mUYDEiDndV = true;}
      if(XuixVEchac == bYlEbVWonT){POgCaoICfY = true;}
      else if(bYlEbVWonT == XuixVEchac){VxLANhjpmF = true;}
      if(QxxxzMqMEp == aDCFURzOOg){AkQixyOHWl = true;}
      else if(aDCFURzOOg == QxxxzMqMEp){EzyVyJoBlq = true;}
      if(fgUfwlythA == nlXnqhtVkn){zaVGrIFrIc = true;}
      if(wEYxZqqYmM == XaGfToCdIp){bqDYOgujVn = true;}
      if(rcPxfAYJLy == bhxIHMkSio){AxpbeDofQQ = true;}
      while(nlXnqhtVkn == fgUfwlythA){qEZuchFhdD = true;}
      while(XaGfToCdIp == XaGfToCdIp){ywPFTVNadi = true;}
      while(bhxIHMkSio == bhxIHMkSio){VaoLUnWDFt = true;}
      if(KOajeoAxNt == true){KOajeoAxNt = false;}
      if(aBEAuzxVkf == true){aBEAuzxVkf = false;}
      if(OVGXEGoPgd == true){OVGXEGoPgd = false;}
      if(wbmwcIAWAe == true){wbmwcIAWAe = false;}
      if(nFPOPadxMH == true){nFPOPadxMH = false;}
      if(POgCaoICfY == true){POgCaoICfY = false;}
      if(AkQixyOHWl == true){AkQixyOHWl = false;}
      if(zaVGrIFrIc == true){zaVGrIFrIc = false;}
      if(bqDYOgujVn == true){bqDYOgujVn = false;}
      if(AxpbeDofQQ == true){AxpbeDofQQ = false;}
      if(MVZZHosZKR == true){MVZZHosZKR = false;}
      if(iQsCxIhqUQ == true){iQsCxIhqUQ = false;}
      if(CdlilCjtbo == true){CdlilCjtbo = false;}
      if(TYarQFRcQZ == true){TYarQFRcQZ = false;}
      if(mUYDEiDndV == true){mUYDEiDndV = false;}
      if(VxLANhjpmF == true){VxLANhjpmF = false;}
      if(EzyVyJoBlq == true){EzyVyJoBlq = false;}
      if(qEZuchFhdD == true){qEZuchFhdD = false;}
      if(ywPFTVNadi == true){ywPFTVNadi = false;}
      if(VaoLUnWDFt == true){VaoLUnWDFt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTPUHPXSRY
{ 
  void XNUwiqGyiC()
  { 
      bool TDZJGJLUTB = false;
      bool cXtlRbrWNt = false;
      bool mwLkNffyUH = false;
      bool MwZCtGTGqc = false;
      bool cMLXmsbQpI = false;
      bool AXRreWrowa = false;
      bool cNALngxrrK = false;
      bool HlejQZkmxU = false;
      bool DPHLHodhXX = false;
      bool NeKPzPMzjG = false;
      bool wjYfBNrgaF = false;
      bool lFqaXNGnEy = false;
      bool CPUUwcbOjB = false;
      bool NlDqXSqbKt = false;
      bool xxGRkImirl = false;
      bool JXtkDfPEiX = false;
      bool kcxZqABADE = false;
      bool WddKBFICim = false;
      bool osWyqoqSmr = false;
      bool DmrlITzfZk = false;
      string TIheUPIBQX;
      string hfHWBzarFt;
      string arLBWYNGyH;
      string FWIQtUoHRA;
      string hLwoolHBrl;
      string KogtFbxfIw;
      string BBDISKXqbg;
      string JTaFMPwVMj;
      string QLOMxQoOKS;
      string WJyUyfImWd;
      string OPYKbpOagp;
      string eaTXfompLC;
      string VIgJJAUFGf;
      string GJzhVAmDjG;
      string BOgUnuoaoJ;
      string sRaTIFiPAb;
      string VITBiVbkBe;
      string CiGFAHbLUO;
      string KsPxmoheZQ;
      string QWCHkstflS;
      if(TIheUPIBQX == OPYKbpOagp){TDZJGJLUTB = true;}
      else if(OPYKbpOagp == TIheUPIBQX){wjYfBNrgaF = true;}
      if(hfHWBzarFt == eaTXfompLC){cXtlRbrWNt = true;}
      else if(eaTXfompLC == hfHWBzarFt){lFqaXNGnEy = true;}
      if(arLBWYNGyH == VIgJJAUFGf){mwLkNffyUH = true;}
      else if(VIgJJAUFGf == arLBWYNGyH){CPUUwcbOjB = true;}
      if(FWIQtUoHRA == GJzhVAmDjG){MwZCtGTGqc = true;}
      else if(GJzhVAmDjG == FWIQtUoHRA){NlDqXSqbKt = true;}
      if(hLwoolHBrl == BOgUnuoaoJ){cMLXmsbQpI = true;}
      else if(BOgUnuoaoJ == hLwoolHBrl){xxGRkImirl = true;}
      if(KogtFbxfIw == sRaTIFiPAb){AXRreWrowa = true;}
      else if(sRaTIFiPAb == KogtFbxfIw){JXtkDfPEiX = true;}
      if(BBDISKXqbg == VITBiVbkBe){cNALngxrrK = true;}
      else if(VITBiVbkBe == BBDISKXqbg){kcxZqABADE = true;}
      if(JTaFMPwVMj == CiGFAHbLUO){HlejQZkmxU = true;}
      if(QLOMxQoOKS == KsPxmoheZQ){DPHLHodhXX = true;}
      if(WJyUyfImWd == QWCHkstflS){NeKPzPMzjG = true;}
      while(CiGFAHbLUO == JTaFMPwVMj){WddKBFICim = true;}
      while(KsPxmoheZQ == KsPxmoheZQ){osWyqoqSmr = true;}
      while(QWCHkstflS == QWCHkstflS){DmrlITzfZk = true;}
      if(TDZJGJLUTB == true){TDZJGJLUTB = false;}
      if(cXtlRbrWNt == true){cXtlRbrWNt = false;}
      if(mwLkNffyUH == true){mwLkNffyUH = false;}
      if(MwZCtGTGqc == true){MwZCtGTGqc = false;}
      if(cMLXmsbQpI == true){cMLXmsbQpI = false;}
      if(AXRreWrowa == true){AXRreWrowa = false;}
      if(cNALngxrrK == true){cNALngxrrK = false;}
      if(HlejQZkmxU == true){HlejQZkmxU = false;}
      if(DPHLHodhXX == true){DPHLHodhXX = false;}
      if(NeKPzPMzjG == true){NeKPzPMzjG = false;}
      if(wjYfBNrgaF == true){wjYfBNrgaF = false;}
      if(lFqaXNGnEy == true){lFqaXNGnEy = false;}
      if(CPUUwcbOjB == true){CPUUwcbOjB = false;}
      if(NlDqXSqbKt == true){NlDqXSqbKt = false;}
      if(xxGRkImirl == true){xxGRkImirl = false;}
      if(JXtkDfPEiX == true){JXtkDfPEiX = false;}
      if(kcxZqABADE == true){kcxZqABADE = false;}
      if(WddKBFICim == true){WddKBFICim = false;}
      if(osWyqoqSmr == true){osWyqoqSmr = false;}
      if(DmrlITzfZk == true){DmrlITzfZk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAOASMGZGO
{ 
  void UOhUurBlfI()
  { 
      bool xPyAnYoCMO = false;
      bool cJRpfLcupr = false;
      bool JwMOwHpNDJ = false;
      bool amICEgAYMS = false;
      bool BDNBHSmyWD = false;
      bool WWkPLACiEg = false;
      bool hbyCmoAOlz = false;
      bool KEhWpFhLGc = false;
      bool TrqzlEBrqE = false;
      bool dQUfkZEKOR = false;
      bool RYMXsSnOYF = false;
      bool SqcaMpjzPi = false;
      bool mIXhUsjCkQ = false;
      bool BWxnKufTGT = false;
      bool QmTkkmnsSu = false;
      bool oFufdJBeCA = false;
      bool ikcIEutnPR = false;
      bool KQrwRAolwh = false;
      bool EpipbubRKB = false;
      bool tBQFkeKKgo = false;
      string RZHgXdaueV;
      string wonBqNHUXm;
      string ygcVQGcRAF;
      string FadGOienTK;
      string ZynyjZSjVB;
      string ZCMqgkxlQR;
      string BJuYPVKhlH;
      string iTBMMArekp;
      string nswyfDNmYd;
      string lsXCJQCPhO;
      string OjyOSGBzdg;
      string rSAZcIMwsM;
      string HXJIVowyDw;
      string xcwWaDuhfZ;
      string COJrkTrxYB;
      string DGVVHqaosc;
      string KCwhiPVcyY;
      string MeQTJsOQXC;
      string wyYBrqGZPj;
      string cFoCPARaIU;
      if(RZHgXdaueV == OjyOSGBzdg){xPyAnYoCMO = true;}
      else if(OjyOSGBzdg == RZHgXdaueV){RYMXsSnOYF = true;}
      if(wonBqNHUXm == rSAZcIMwsM){cJRpfLcupr = true;}
      else if(rSAZcIMwsM == wonBqNHUXm){SqcaMpjzPi = true;}
      if(ygcVQGcRAF == HXJIVowyDw){JwMOwHpNDJ = true;}
      else if(HXJIVowyDw == ygcVQGcRAF){mIXhUsjCkQ = true;}
      if(FadGOienTK == xcwWaDuhfZ){amICEgAYMS = true;}
      else if(xcwWaDuhfZ == FadGOienTK){BWxnKufTGT = true;}
      if(ZynyjZSjVB == COJrkTrxYB){BDNBHSmyWD = true;}
      else if(COJrkTrxYB == ZynyjZSjVB){QmTkkmnsSu = true;}
      if(ZCMqgkxlQR == DGVVHqaosc){WWkPLACiEg = true;}
      else if(DGVVHqaosc == ZCMqgkxlQR){oFufdJBeCA = true;}
      if(BJuYPVKhlH == KCwhiPVcyY){hbyCmoAOlz = true;}
      else if(KCwhiPVcyY == BJuYPVKhlH){ikcIEutnPR = true;}
      if(iTBMMArekp == MeQTJsOQXC){KEhWpFhLGc = true;}
      if(nswyfDNmYd == wyYBrqGZPj){TrqzlEBrqE = true;}
      if(lsXCJQCPhO == cFoCPARaIU){dQUfkZEKOR = true;}
      while(MeQTJsOQXC == iTBMMArekp){KQrwRAolwh = true;}
      while(wyYBrqGZPj == wyYBrqGZPj){EpipbubRKB = true;}
      while(cFoCPARaIU == cFoCPARaIU){tBQFkeKKgo = true;}
      if(xPyAnYoCMO == true){xPyAnYoCMO = false;}
      if(cJRpfLcupr == true){cJRpfLcupr = false;}
      if(JwMOwHpNDJ == true){JwMOwHpNDJ = false;}
      if(amICEgAYMS == true){amICEgAYMS = false;}
      if(BDNBHSmyWD == true){BDNBHSmyWD = false;}
      if(WWkPLACiEg == true){WWkPLACiEg = false;}
      if(hbyCmoAOlz == true){hbyCmoAOlz = false;}
      if(KEhWpFhLGc == true){KEhWpFhLGc = false;}
      if(TrqzlEBrqE == true){TrqzlEBrqE = false;}
      if(dQUfkZEKOR == true){dQUfkZEKOR = false;}
      if(RYMXsSnOYF == true){RYMXsSnOYF = false;}
      if(SqcaMpjzPi == true){SqcaMpjzPi = false;}
      if(mIXhUsjCkQ == true){mIXhUsjCkQ = false;}
      if(BWxnKufTGT == true){BWxnKufTGT = false;}
      if(QmTkkmnsSu == true){QmTkkmnsSu = false;}
      if(oFufdJBeCA == true){oFufdJBeCA = false;}
      if(ikcIEutnPR == true){ikcIEutnPR = false;}
      if(KQrwRAolwh == true){KQrwRAolwh = false;}
      if(EpipbubRKB == true){EpipbubRKB = false;}
      if(tBQFkeKKgo == true){tBQFkeKKgo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPXDBJUQOO
{ 
  void xoBEwbouaR()
  { 
      bool SqhzqjWmuq = false;
      bool iBWmTOWrFK = false;
      bool rQyfiRSjzE = false;
      bool pcXDuLPNoo = false;
      bool pyMbGMHwsl = false;
      bool HSOQpCrCPZ = false;
      bool QlmpAGdTqH = false;
      bool zJDPTsDWYV = false;
      bool JWqNwXNGMs = false;
      bool SMxPYELVaA = false;
      bool imEllyPzxw = false;
      bool yVctPtuYsc = false;
      bool sWHyolMmqP = false;
      bool hhwYmWSEby = false;
      bool INIPtxjCAd = false;
      bool IlbxHLfFwz = false;
      bool kbHgNQYEHs = false;
      bool apxuUeOqEq = false;
      bool CJmMGwFyRa = false;
      bool pMHbMfFaBc = false;
      string yTURhCzBdW;
      string rUsKiLowAD;
      string kTuwXKUOBn;
      string RWcquaLqeF;
      string NBrgCVzXRi;
      string MKpineYXtW;
      string gkApFUqBPI;
      string zyRtpiaNtB;
      string LwwSbHgsDQ;
      string CmwHYcBBbg;
      string exIJiNsusE;
      string DKdrLjogNx;
      string nyxzGMBJVN;
      string gYlMWNnljN;
      string OlAyMqJEwn;
      string mTndsfAJCW;
      string MjZfWdXRVx;
      string wCxAiCxylO;
      string DxMgZMkHSp;
      string NeiMAeLUai;
      if(yTURhCzBdW == exIJiNsusE){SqhzqjWmuq = true;}
      else if(exIJiNsusE == yTURhCzBdW){imEllyPzxw = true;}
      if(rUsKiLowAD == DKdrLjogNx){iBWmTOWrFK = true;}
      else if(DKdrLjogNx == rUsKiLowAD){yVctPtuYsc = true;}
      if(kTuwXKUOBn == nyxzGMBJVN){rQyfiRSjzE = true;}
      else if(nyxzGMBJVN == kTuwXKUOBn){sWHyolMmqP = true;}
      if(RWcquaLqeF == gYlMWNnljN){pcXDuLPNoo = true;}
      else if(gYlMWNnljN == RWcquaLqeF){hhwYmWSEby = true;}
      if(NBrgCVzXRi == OlAyMqJEwn){pyMbGMHwsl = true;}
      else if(OlAyMqJEwn == NBrgCVzXRi){INIPtxjCAd = true;}
      if(MKpineYXtW == mTndsfAJCW){HSOQpCrCPZ = true;}
      else if(mTndsfAJCW == MKpineYXtW){IlbxHLfFwz = true;}
      if(gkApFUqBPI == MjZfWdXRVx){QlmpAGdTqH = true;}
      else if(MjZfWdXRVx == gkApFUqBPI){kbHgNQYEHs = true;}
      if(zyRtpiaNtB == wCxAiCxylO){zJDPTsDWYV = true;}
      if(LwwSbHgsDQ == DxMgZMkHSp){JWqNwXNGMs = true;}
      if(CmwHYcBBbg == NeiMAeLUai){SMxPYELVaA = true;}
      while(wCxAiCxylO == zyRtpiaNtB){apxuUeOqEq = true;}
      while(DxMgZMkHSp == DxMgZMkHSp){CJmMGwFyRa = true;}
      while(NeiMAeLUai == NeiMAeLUai){pMHbMfFaBc = true;}
      if(SqhzqjWmuq == true){SqhzqjWmuq = false;}
      if(iBWmTOWrFK == true){iBWmTOWrFK = false;}
      if(rQyfiRSjzE == true){rQyfiRSjzE = false;}
      if(pcXDuLPNoo == true){pcXDuLPNoo = false;}
      if(pyMbGMHwsl == true){pyMbGMHwsl = false;}
      if(HSOQpCrCPZ == true){HSOQpCrCPZ = false;}
      if(QlmpAGdTqH == true){QlmpAGdTqH = false;}
      if(zJDPTsDWYV == true){zJDPTsDWYV = false;}
      if(JWqNwXNGMs == true){JWqNwXNGMs = false;}
      if(SMxPYELVaA == true){SMxPYELVaA = false;}
      if(imEllyPzxw == true){imEllyPzxw = false;}
      if(yVctPtuYsc == true){yVctPtuYsc = false;}
      if(sWHyolMmqP == true){sWHyolMmqP = false;}
      if(hhwYmWSEby == true){hhwYmWSEby = false;}
      if(INIPtxjCAd == true){INIPtxjCAd = false;}
      if(IlbxHLfFwz == true){IlbxHLfFwz = false;}
      if(kbHgNQYEHs == true){kbHgNQYEHs = false;}
      if(apxuUeOqEq == true){apxuUeOqEq = false;}
      if(CJmMGwFyRa == true){CJmMGwFyRa = false;}
      if(pMHbMfFaBc == true){pMHbMfFaBc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSFJBQNHFS
{ 
  void aayNWJNVMu()
  { 
      bool jfSFLkMciL = false;
      bool XSNoOLFlxN = false;
      bool rrKUjGEaOU = false;
      bool AbKemVqPeC = false;
      bool upaEEOlqGi = false;
      bool srNDArVyUF = false;
      bool gkNNLwIhBs = false;
      bool UoGtSBQGPV = false;
      bool TMTebINHdu = false;
      bool AsuZUJcNsI = false;
      bool GEoNODkTkz = false;
      bool aOhzkUQhkC = false;
      bool iAEFrbtfYI = false;
      bool YCMHOPWGQX = false;
      bool WsVeTkKunA = false;
      bool rtbpZFzjUm = false;
      bool IFtbZXCZjV = false;
      bool xKRNeoeYlH = false;
      bool QzqYPeaWhJ = false;
      bool PmkcORzsEu = false;
      string RfOVQzhifU;
      string gWMJmHuJTu;
      string CcEuDjJrkn;
      string cAuXLcITyA;
      string mqGqJVyLeY;
      string YfGDynbTSf;
      string poxqrganyK;
      string ybLTHLVMkh;
      string lyNMOwtqZW;
      string BoBRJytPzc;
      string tJMUZxUmum;
      string RPhjtqbjbu;
      string liObIIasJJ;
      string RGNHmbkrmR;
      string aHwmElGQXR;
      string VJmDqKtkLQ;
      string VbckVLBaxR;
      string GjxKUembXW;
      string BKVqnHTJQb;
      string gAfVuzdLQr;
      if(RfOVQzhifU == tJMUZxUmum){jfSFLkMciL = true;}
      else if(tJMUZxUmum == RfOVQzhifU){GEoNODkTkz = true;}
      if(gWMJmHuJTu == RPhjtqbjbu){XSNoOLFlxN = true;}
      else if(RPhjtqbjbu == gWMJmHuJTu){aOhzkUQhkC = true;}
      if(CcEuDjJrkn == liObIIasJJ){rrKUjGEaOU = true;}
      else if(liObIIasJJ == CcEuDjJrkn){iAEFrbtfYI = true;}
      if(cAuXLcITyA == RGNHmbkrmR){AbKemVqPeC = true;}
      else if(RGNHmbkrmR == cAuXLcITyA){YCMHOPWGQX = true;}
      if(mqGqJVyLeY == aHwmElGQXR){upaEEOlqGi = true;}
      else if(aHwmElGQXR == mqGqJVyLeY){WsVeTkKunA = true;}
      if(YfGDynbTSf == VJmDqKtkLQ){srNDArVyUF = true;}
      else if(VJmDqKtkLQ == YfGDynbTSf){rtbpZFzjUm = true;}
      if(poxqrganyK == VbckVLBaxR){gkNNLwIhBs = true;}
      else if(VbckVLBaxR == poxqrganyK){IFtbZXCZjV = true;}
      if(ybLTHLVMkh == GjxKUembXW){UoGtSBQGPV = true;}
      if(lyNMOwtqZW == BKVqnHTJQb){TMTebINHdu = true;}
      if(BoBRJytPzc == gAfVuzdLQr){AsuZUJcNsI = true;}
      while(GjxKUembXW == ybLTHLVMkh){xKRNeoeYlH = true;}
      while(BKVqnHTJQb == BKVqnHTJQb){QzqYPeaWhJ = true;}
      while(gAfVuzdLQr == gAfVuzdLQr){PmkcORzsEu = true;}
      if(jfSFLkMciL == true){jfSFLkMciL = false;}
      if(XSNoOLFlxN == true){XSNoOLFlxN = false;}
      if(rrKUjGEaOU == true){rrKUjGEaOU = false;}
      if(AbKemVqPeC == true){AbKemVqPeC = false;}
      if(upaEEOlqGi == true){upaEEOlqGi = false;}
      if(srNDArVyUF == true){srNDArVyUF = false;}
      if(gkNNLwIhBs == true){gkNNLwIhBs = false;}
      if(UoGtSBQGPV == true){UoGtSBQGPV = false;}
      if(TMTebINHdu == true){TMTebINHdu = false;}
      if(AsuZUJcNsI == true){AsuZUJcNsI = false;}
      if(GEoNODkTkz == true){GEoNODkTkz = false;}
      if(aOhzkUQhkC == true){aOhzkUQhkC = false;}
      if(iAEFrbtfYI == true){iAEFrbtfYI = false;}
      if(YCMHOPWGQX == true){YCMHOPWGQX = false;}
      if(WsVeTkKunA == true){WsVeTkKunA = false;}
      if(rtbpZFzjUm == true){rtbpZFzjUm = false;}
      if(IFtbZXCZjV == true){IFtbZXCZjV = false;}
      if(xKRNeoeYlH == true){xKRNeoeYlH = false;}
      if(QzqYPeaWhJ == true){QzqYPeaWhJ = false;}
      if(PmkcORzsEu == true){PmkcORzsEu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGSBINVJID
{ 
  void VJPGIjBREF()
  { 
      bool rlVLkozMuH = false;
      bool EncxnwTigL = false;
      bool HSZVVGBGSc = false;
      bool dOghiVOWuT = false;
      bool ALqzaUEaVT = false;
      bool asZVmZMApe = false;
      bool nrsRcpHuNS = false;
      bool hxmNLwaatA = false;
      bool BZkzCknKtJ = false;
      bool IOfQfIRYVj = false;
      bool NJNDldFMKq = false;
      bool ylFpcNHtPr = false;
      bool CwBEJSRVgD = false;
      bool dCEKlrMgMY = false;
      bool eaACLWIonS = false;
      bool AWJdhRHIsS = false;
      bool MjfGMwguEk = false;
      bool AZgqMauysl = false;
      bool KbhNCHsZbU = false;
      bool jEntLuuspP = false;
      string DhhqldsziE;
      string IemPutVNsU;
      string zBbChTyZwM;
      string KwtHfNzkDi;
      string HsAhXgsweS;
      string ZlgdjCFfIS;
      string eSCVsMkfjg;
      string ujJKNGAteB;
      string ZBudmYOPWd;
      string ITcjDnpenK;
      string uMMxWobWQc;
      string BLAGrdXYhU;
      string xUIFYaHZGZ;
      string QUFTFNoxGy;
      string wrztbxSWqZ;
      string PQwTMaDGYw;
      string hCPqLfFgAe;
      string nZRjXFVOda;
      string HkhgJzYlGe;
      string JhYKQtbHhu;
      if(DhhqldsziE == uMMxWobWQc){rlVLkozMuH = true;}
      else if(uMMxWobWQc == DhhqldsziE){NJNDldFMKq = true;}
      if(IemPutVNsU == BLAGrdXYhU){EncxnwTigL = true;}
      else if(BLAGrdXYhU == IemPutVNsU){ylFpcNHtPr = true;}
      if(zBbChTyZwM == xUIFYaHZGZ){HSZVVGBGSc = true;}
      else if(xUIFYaHZGZ == zBbChTyZwM){CwBEJSRVgD = true;}
      if(KwtHfNzkDi == QUFTFNoxGy){dOghiVOWuT = true;}
      else if(QUFTFNoxGy == KwtHfNzkDi){dCEKlrMgMY = true;}
      if(HsAhXgsweS == wrztbxSWqZ){ALqzaUEaVT = true;}
      else if(wrztbxSWqZ == HsAhXgsweS){eaACLWIonS = true;}
      if(ZlgdjCFfIS == PQwTMaDGYw){asZVmZMApe = true;}
      else if(PQwTMaDGYw == ZlgdjCFfIS){AWJdhRHIsS = true;}
      if(eSCVsMkfjg == hCPqLfFgAe){nrsRcpHuNS = true;}
      else if(hCPqLfFgAe == eSCVsMkfjg){MjfGMwguEk = true;}
      if(ujJKNGAteB == nZRjXFVOda){hxmNLwaatA = true;}
      if(ZBudmYOPWd == HkhgJzYlGe){BZkzCknKtJ = true;}
      if(ITcjDnpenK == JhYKQtbHhu){IOfQfIRYVj = true;}
      while(nZRjXFVOda == ujJKNGAteB){AZgqMauysl = true;}
      while(HkhgJzYlGe == HkhgJzYlGe){KbhNCHsZbU = true;}
      while(JhYKQtbHhu == JhYKQtbHhu){jEntLuuspP = true;}
      if(rlVLkozMuH == true){rlVLkozMuH = false;}
      if(EncxnwTigL == true){EncxnwTigL = false;}
      if(HSZVVGBGSc == true){HSZVVGBGSc = false;}
      if(dOghiVOWuT == true){dOghiVOWuT = false;}
      if(ALqzaUEaVT == true){ALqzaUEaVT = false;}
      if(asZVmZMApe == true){asZVmZMApe = false;}
      if(nrsRcpHuNS == true){nrsRcpHuNS = false;}
      if(hxmNLwaatA == true){hxmNLwaatA = false;}
      if(BZkzCknKtJ == true){BZkzCknKtJ = false;}
      if(IOfQfIRYVj == true){IOfQfIRYVj = false;}
      if(NJNDldFMKq == true){NJNDldFMKq = false;}
      if(ylFpcNHtPr == true){ylFpcNHtPr = false;}
      if(CwBEJSRVgD == true){CwBEJSRVgD = false;}
      if(dCEKlrMgMY == true){dCEKlrMgMY = false;}
      if(eaACLWIonS == true){eaACLWIonS = false;}
      if(AWJdhRHIsS == true){AWJdhRHIsS = false;}
      if(MjfGMwguEk == true){MjfGMwguEk = false;}
      if(AZgqMauysl == true){AZgqMauysl = false;}
      if(KbhNCHsZbU == true){KbhNCHsZbU = false;}
      if(jEntLuuspP == true){jEntLuuspP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZIJAIEDVD
{ 
  void EqKHXHmTVS()
  { 
      bool NZSsgbbzGf = false;
      bool JlcIrMVlUh = false;
      bool XpQAoyGJKg = false;
      bool OLZeaWjhNm = false;
      bool EsrVhwVTuG = false;
      bool zYzBaWJSEi = false;
      bool USoYQyMyhU = false;
      bool cnXhcdyuRs = false;
      bool blNDhoLXED = false;
      bool MQceRlETEj = false;
      bool iXlZdLBRXw = false;
      bool YOALHiEkqa = false;
      bool losdILKsQq = false;
      bool YephJDAnZV = false;
      bool ntzHeyQRWi = false;
      bool gTcdytdIRS = false;
      bool AIBfXsYRBD = false;
      bool hQLUlqolyJ = false;
      bool tsVgKECLjP = false;
      bool ZqVGVesSjk = false;
      string lqjbBOWTSz;
      string pZSHcbbVEs;
      string ggFcpOEwnr;
      string QUXqJlWZHs;
      string wcRPudeyfh;
      string fFSHXElGll;
      string KZeZiVBaxq;
      string FBOKxDPogL;
      string iGPFMLBPSE;
      string zQmUiVyqgZ;
      string cEAocdqIKU;
      string oxYaDDKYNW;
      string TlHsqnOsaa;
      string FXHHieGabi;
      string TsEyPCqLRe;
      string LYdJGpwGxo;
      string PxhjOQoRrX;
      string xjwdDagJdo;
      string wCbuOgsyBr;
      string izcmTVLUjy;
      if(lqjbBOWTSz == cEAocdqIKU){NZSsgbbzGf = true;}
      else if(cEAocdqIKU == lqjbBOWTSz){iXlZdLBRXw = true;}
      if(pZSHcbbVEs == oxYaDDKYNW){JlcIrMVlUh = true;}
      else if(oxYaDDKYNW == pZSHcbbVEs){YOALHiEkqa = true;}
      if(ggFcpOEwnr == TlHsqnOsaa){XpQAoyGJKg = true;}
      else if(TlHsqnOsaa == ggFcpOEwnr){losdILKsQq = true;}
      if(QUXqJlWZHs == FXHHieGabi){OLZeaWjhNm = true;}
      else if(FXHHieGabi == QUXqJlWZHs){YephJDAnZV = true;}
      if(wcRPudeyfh == TsEyPCqLRe){EsrVhwVTuG = true;}
      else if(TsEyPCqLRe == wcRPudeyfh){ntzHeyQRWi = true;}
      if(fFSHXElGll == LYdJGpwGxo){zYzBaWJSEi = true;}
      else if(LYdJGpwGxo == fFSHXElGll){gTcdytdIRS = true;}
      if(KZeZiVBaxq == PxhjOQoRrX){USoYQyMyhU = true;}
      else if(PxhjOQoRrX == KZeZiVBaxq){AIBfXsYRBD = true;}
      if(FBOKxDPogL == xjwdDagJdo){cnXhcdyuRs = true;}
      if(iGPFMLBPSE == wCbuOgsyBr){blNDhoLXED = true;}
      if(zQmUiVyqgZ == izcmTVLUjy){MQceRlETEj = true;}
      while(xjwdDagJdo == FBOKxDPogL){hQLUlqolyJ = true;}
      while(wCbuOgsyBr == wCbuOgsyBr){tsVgKECLjP = true;}
      while(izcmTVLUjy == izcmTVLUjy){ZqVGVesSjk = true;}
      if(NZSsgbbzGf == true){NZSsgbbzGf = false;}
      if(JlcIrMVlUh == true){JlcIrMVlUh = false;}
      if(XpQAoyGJKg == true){XpQAoyGJKg = false;}
      if(OLZeaWjhNm == true){OLZeaWjhNm = false;}
      if(EsrVhwVTuG == true){EsrVhwVTuG = false;}
      if(zYzBaWJSEi == true){zYzBaWJSEi = false;}
      if(USoYQyMyhU == true){USoYQyMyhU = false;}
      if(cnXhcdyuRs == true){cnXhcdyuRs = false;}
      if(blNDhoLXED == true){blNDhoLXED = false;}
      if(MQceRlETEj == true){MQceRlETEj = false;}
      if(iXlZdLBRXw == true){iXlZdLBRXw = false;}
      if(YOALHiEkqa == true){YOALHiEkqa = false;}
      if(losdILKsQq == true){losdILKsQq = false;}
      if(YephJDAnZV == true){YephJDAnZV = false;}
      if(ntzHeyQRWi == true){ntzHeyQRWi = false;}
      if(gTcdytdIRS == true){gTcdytdIRS = false;}
      if(AIBfXsYRBD == true){AIBfXsYRBD = false;}
      if(hQLUlqolyJ == true){hQLUlqolyJ = false;}
      if(tsVgKECLjP == true){tsVgKECLjP = false;}
      if(ZqVGVesSjk == true){ZqVGVesSjk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OATJLKZNSK
{ 
  void PeCwHtAPlK()
  { 
      bool ZjnAUGmkYs = false;
      bool fhKuklOSGi = false;
      bool ntuUPDXInI = false;
      bool mERGpiidnD = false;
      bool VFetdYICKu = false;
      bool RuYgqfoSkR = false;
      bool hdxPGbPEFC = false;
      bool CkdDNiOAqq = false;
      bool tVyrprfkOK = false;
      bool tPrVUqIOnC = false;
      bool IDxHrgQVTI = false;
      bool QnbtWLfEYO = false;
      bool weotIlrHhV = false;
      bool azMnhqYpAJ = false;
      bool aJRGsFnyzJ = false;
      bool KDpYGcOCzF = false;
      bool nInxhRbmLf = false;
      bool mpEPmlNiAD = false;
      bool ytIYKWJmhF = false;
      bool cVqtVRVTYb = false;
      string ZazUygozGW;
      string nZcJhtMJHA;
      string niMNtZjtED;
      string kdwmbCWypa;
      string EqUQtYwagN;
      string NOKynpNkaX;
      string wtuClJcohe;
      string XNTfwwOwTV;
      string dJNppVTyzl;
      string okXReJwRdj;
      string uGsCpzudCq;
      string aQREtmgELP;
      string pepwolpBBl;
      string AwSiZXPKAq;
      string apuHKYTSWr;
      string cqGNtPQwME;
      string JsbPqeyieW;
      string WVEUoAjhlQ;
      string SWdJJIpEnJ;
      string GSywggNePf;
      if(ZazUygozGW == uGsCpzudCq){ZjnAUGmkYs = true;}
      else if(uGsCpzudCq == ZazUygozGW){IDxHrgQVTI = true;}
      if(nZcJhtMJHA == aQREtmgELP){fhKuklOSGi = true;}
      else if(aQREtmgELP == nZcJhtMJHA){QnbtWLfEYO = true;}
      if(niMNtZjtED == pepwolpBBl){ntuUPDXInI = true;}
      else if(pepwolpBBl == niMNtZjtED){weotIlrHhV = true;}
      if(kdwmbCWypa == AwSiZXPKAq){mERGpiidnD = true;}
      else if(AwSiZXPKAq == kdwmbCWypa){azMnhqYpAJ = true;}
      if(EqUQtYwagN == apuHKYTSWr){VFetdYICKu = true;}
      else if(apuHKYTSWr == EqUQtYwagN){aJRGsFnyzJ = true;}
      if(NOKynpNkaX == cqGNtPQwME){RuYgqfoSkR = true;}
      else if(cqGNtPQwME == NOKynpNkaX){KDpYGcOCzF = true;}
      if(wtuClJcohe == JsbPqeyieW){hdxPGbPEFC = true;}
      else if(JsbPqeyieW == wtuClJcohe){nInxhRbmLf = true;}
      if(XNTfwwOwTV == WVEUoAjhlQ){CkdDNiOAqq = true;}
      if(dJNppVTyzl == SWdJJIpEnJ){tVyrprfkOK = true;}
      if(okXReJwRdj == GSywggNePf){tPrVUqIOnC = true;}
      while(WVEUoAjhlQ == XNTfwwOwTV){mpEPmlNiAD = true;}
      while(SWdJJIpEnJ == SWdJJIpEnJ){ytIYKWJmhF = true;}
      while(GSywggNePf == GSywggNePf){cVqtVRVTYb = true;}
      if(ZjnAUGmkYs == true){ZjnAUGmkYs = false;}
      if(fhKuklOSGi == true){fhKuklOSGi = false;}
      if(ntuUPDXInI == true){ntuUPDXInI = false;}
      if(mERGpiidnD == true){mERGpiidnD = false;}
      if(VFetdYICKu == true){VFetdYICKu = false;}
      if(RuYgqfoSkR == true){RuYgqfoSkR = false;}
      if(hdxPGbPEFC == true){hdxPGbPEFC = false;}
      if(CkdDNiOAqq == true){CkdDNiOAqq = false;}
      if(tVyrprfkOK == true){tVyrprfkOK = false;}
      if(tPrVUqIOnC == true){tPrVUqIOnC = false;}
      if(IDxHrgQVTI == true){IDxHrgQVTI = false;}
      if(QnbtWLfEYO == true){QnbtWLfEYO = false;}
      if(weotIlrHhV == true){weotIlrHhV = false;}
      if(azMnhqYpAJ == true){azMnhqYpAJ = false;}
      if(aJRGsFnyzJ == true){aJRGsFnyzJ = false;}
      if(KDpYGcOCzF == true){KDpYGcOCzF = false;}
      if(nInxhRbmLf == true){nInxhRbmLf = false;}
      if(mpEPmlNiAD == true){mpEPmlNiAD = false;}
      if(ytIYKWJmhF == true){ytIYKWJmhF = false;}
      if(cVqtVRVTYb == true){cVqtVRVTYb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUCZHJNPXK
{ 
  void hXptaACmHX()
  { 
      bool mDdPlimDoG = false;
      bool ATPouWbpJd = false;
      bool rFMxnHjrnA = false;
      bool lTqFmWZbTL = false;
      bool wsjZqWCoXJ = false;
      bool IZudQgpfbe = false;
      bool yuOoUfbKCX = false;
      bool wzWxhyVmGR = false;
      bool EuTeqLXNnG = false;
      bool fsAoMBdtEK = false;
      bool trmzMJDyuR = false;
      bool KDZJaDajyJ = false;
      bool HOVuqCzgjg = false;
      bool TahuXLHTRh = false;
      bool HZRWucTpOJ = false;
      bool ZtuuCeWqIJ = false;
      bool JVNOxjVdlO = false;
      bool uGSQBhxzAO = false;
      bool iISaGZelsr = false;
      bool oQLHXlLDYL = false;
      string rbirJaMFbs;
      string okYVkhrwEP;
      string GHfiPVKBZu;
      string rwynwtfzXB;
      string RbiQTrXSzt;
      string pfStYjuzbm;
      string QLegBsljZq;
      string CsXDydXPPW;
      string yqCfELcEPL;
      string yfWjkGxBPZ;
      string GnsIqxHPut;
      string MfiEoYIzco;
      string QgUNrWVmSr;
      string gWApQJytnH;
      string ENIUzSwRuM;
      string xyYZJYTePU;
      string aTwDMofsne;
      string ZOKUjCYzOZ;
      string ZDrGtixZgq;
      string pSeSfjQEHJ;
      if(rbirJaMFbs == GnsIqxHPut){mDdPlimDoG = true;}
      else if(GnsIqxHPut == rbirJaMFbs){trmzMJDyuR = true;}
      if(okYVkhrwEP == MfiEoYIzco){ATPouWbpJd = true;}
      else if(MfiEoYIzco == okYVkhrwEP){KDZJaDajyJ = true;}
      if(GHfiPVKBZu == QgUNrWVmSr){rFMxnHjrnA = true;}
      else if(QgUNrWVmSr == GHfiPVKBZu){HOVuqCzgjg = true;}
      if(rwynwtfzXB == gWApQJytnH){lTqFmWZbTL = true;}
      else if(gWApQJytnH == rwynwtfzXB){TahuXLHTRh = true;}
      if(RbiQTrXSzt == ENIUzSwRuM){wsjZqWCoXJ = true;}
      else if(ENIUzSwRuM == RbiQTrXSzt){HZRWucTpOJ = true;}
      if(pfStYjuzbm == xyYZJYTePU){IZudQgpfbe = true;}
      else if(xyYZJYTePU == pfStYjuzbm){ZtuuCeWqIJ = true;}
      if(QLegBsljZq == aTwDMofsne){yuOoUfbKCX = true;}
      else if(aTwDMofsne == QLegBsljZq){JVNOxjVdlO = true;}
      if(CsXDydXPPW == ZOKUjCYzOZ){wzWxhyVmGR = true;}
      if(yqCfELcEPL == ZDrGtixZgq){EuTeqLXNnG = true;}
      if(yfWjkGxBPZ == pSeSfjQEHJ){fsAoMBdtEK = true;}
      while(ZOKUjCYzOZ == CsXDydXPPW){uGSQBhxzAO = true;}
      while(ZDrGtixZgq == ZDrGtixZgq){iISaGZelsr = true;}
      while(pSeSfjQEHJ == pSeSfjQEHJ){oQLHXlLDYL = true;}
      if(mDdPlimDoG == true){mDdPlimDoG = false;}
      if(ATPouWbpJd == true){ATPouWbpJd = false;}
      if(rFMxnHjrnA == true){rFMxnHjrnA = false;}
      if(lTqFmWZbTL == true){lTqFmWZbTL = false;}
      if(wsjZqWCoXJ == true){wsjZqWCoXJ = false;}
      if(IZudQgpfbe == true){IZudQgpfbe = false;}
      if(yuOoUfbKCX == true){yuOoUfbKCX = false;}
      if(wzWxhyVmGR == true){wzWxhyVmGR = false;}
      if(EuTeqLXNnG == true){EuTeqLXNnG = false;}
      if(fsAoMBdtEK == true){fsAoMBdtEK = false;}
      if(trmzMJDyuR == true){trmzMJDyuR = false;}
      if(KDZJaDajyJ == true){KDZJaDajyJ = false;}
      if(HOVuqCzgjg == true){HOVuqCzgjg = false;}
      if(TahuXLHTRh == true){TahuXLHTRh = false;}
      if(HZRWucTpOJ == true){HZRWucTpOJ = false;}
      if(ZtuuCeWqIJ == true){ZtuuCeWqIJ = false;}
      if(JVNOxjVdlO == true){JVNOxjVdlO = false;}
      if(uGSQBhxzAO == true){uGSQBhxzAO = false;}
      if(iISaGZelsr == true){iISaGZelsr = false;}
      if(oQLHXlLDYL == true){oQLHXlLDYL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSYCWIVRNJ
{ 
  void dVTqGwkVnA()
  { 
      bool UEYaQJyMRR = false;
      bool WraTsxBROX = false;
      bool HcOHtQyGNn = false;
      bool utsOJdRPGV = false;
      bool nZbAhoPmtn = false;
      bool cCOgurpQfA = false;
      bool KqzcVczMJO = false;
      bool elLrigBNYF = false;
      bool AKLZLseLTR = false;
      bool nAjFLwaydF = false;
      bool pCdfIqpWxN = false;
      bool qbrazzfZRc = false;
      bool xmsrZeBFfm = false;
      bool GCjTOxgfQT = false;
      bool CIOFaLIIGL = false;
      bool QAfBHCJkFd = false;
      bool ojpKGnrXLB = false;
      bool SzIxZoXmRN = false;
      bool WszUVGVhMM = false;
      bool nwZmeRREyl = false;
      string HoVoInATlr;
      string IklaKsZWKs;
      string JdhhmkFKwb;
      string robYUxGzZz;
      string TatbZyNNhi;
      string nhuOWcGnCW;
      string ipXKASIMFM;
      string mZwKYhiGHo;
      string XqbMmJsNCq;
      string qSxCPdDjbH;
      string oAHUwOljon;
      string tAgMzqNKXp;
      string YuKOVUbsuu;
      string ezdAzWjHPX;
      string WJXNxpkkDX;
      string PrMkhtoszb;
      string mrotJtVgMb;
      string HGtzTPXxRe;
      string ippWflmsRF;
      string hqHnkeUcEC;
      if(HoVoInATlr == oAHUwOljon){UEYaQJyMRR = true;}
      else if(oAHUwOljon == HoVoInATlr){pCdfIqpWxN = true;}
      if(IklaKsZWKs == tAgMzqNKXp){WraTsxBROX = true;}
      else if(tAgMzqNKXp == IklaKsZWKs){qbrazzfZRc = true;}
      if(JdhhmkFKwb == YuKOVUbsuu){HcOHtQyGNn = true;}
      else if(YuKOVUbsuu == JdhhmkFKwb){xmsrZeBFfm = true;}
      if(robYUxGzZz == ezdAzWjHPX){utsOJdRPGV = true;}
      else if(ezdAzWjHPX == robYUxGzZz){GCjTOxgfQT = true;}
      if(TatbZyNNhi == WJXNxpkkDX){nZbAhoPmtn = true;}
      else if(WJXNxpkkDX == TatbZyNNhi){CIOFaLIIGL = true;}
      if(nhuOWcGnCW == PrMkhtoszb){cCOgurpQfA = true;}
      else if(PrMkhtoszb == nhuOWcGnCW){QAfBHCJkFd = true;}
      if(ipXKASIMFM == mrotJtVgMb){KqzcVczMJO = true;}
      else if(mrotJtVgMb == ipXKASIMFM){ojpKGnrXLB = true;}
      if(mZwKYhiGHo == HGtzTPXxRe){elLrigBNYF = true;}
      if(XqbMmJsNCq == ippWflmsRF){AKLZLseLTR = true;}
      if(qSxCPdDjbH == hqHnkeUcEC){nAjFLwaydF = true;}
      while(HGtzTPXxRe == mZwKYhiGHo){SzIxZoXmRN = true;}
      while(ippWflmsRF == ippWflmsRF){WszUVGVhMM = true;}
      while(hqHnkeUcEC == hqHnkeUcEC){nwZmeRREyl = true;}
      if(UEYaQJyMRR == true){UEYaQJyMRR = false;}
      if(WraTsxBROX == true){WraTsxBROX = false;}
      if(HcOHtQyGNn == true){HcOHtQyGNn = false;}
      if(utsOJdRPGV == true){utsOJdRPGV = false;}
      if(nZbAhoPmtn == true){nZbAhoPmtn = false;}
      if(cCOgurpQfA == true){cCOgurpQfA = false;}
      if(KqzcVczMJO == true){KqzcVczMJO = false;}
      if(elLrigBNYF == true){elLrigBNYF = false;}
      if(AKLZLseLTR == true){AKLZLseLTR = false;}
      if(nAjFLwaydF == true){nAjFLwaydF = false;}
      if(pCdfIqpWxN == true){pCdfIqpWxN = false;}
      if(qbrazzfZRc == true){qbrazzfZRc = false;}
      if(xmsrZeBFfm == true){xmsrZeBFfm = false;}
      if(GCjTOxgfQT == true){GCjTOxgfQT = false;}
      if(CIOFaLIIGL == true){CIOFaLIIGL = false;}
      if(QAfBHCJkFd == true){QAfBHCJkFd = false;}
      if(ojpKGnrXLB == true){ojpKGnrXLB = false;}
      if(SzIxZoXmRN == true){SzIxZoXmRN = false;}
      if(WszUVGVhMM == true){WszUVGVhMM = false;}
      if(nwZmeRREyl == true){nwZmeRREyl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSQEZAVBDD
{ 
  void zGVrojQcBL()
  { 
      bool nJFsYzckRo = false;
      bool aflutYrxHK = false;
      bool LBzFtHRSoP = false;
      bool EQONSNpjAQ = false;
      bool kDepiOxaXr = false;
      bool TJjHRmJzzQ = false;
      bool gJwBjKRXcf = false;
      bool iHwpYIWJWe = false;
      bool KquwwtgGwf = false;
      bool EqkijbGcFY = false;
      bool wYyrJLNshJ = false;
      bool PAbTGoOAEo = false;
      bool cKbwbqWMFx = false;
      bool BsDyhlsDlj = false;
      bool gmXmPDORct = false;
      bool NFYPulwBPR = false;
      bool oAnkHWwdkT = false;
      bool wLOUIolofX = false;
      bool cEiKjwUnDw = false;
      bool oqmTtgzmes = false;
      string iNgccGbklY;
      string nkRsdznMrw;
      string afewSoqoDO;
      string tIXDNJlpTj;
      string oPKiWSxeRq;
      string lbThLCikJn;
      string PlgWdeMOfT;
      string NyrIGKUuYA;
      string qLXMbSopqK;
      string ZBffTChnFq;
      string GiyxdniKaB;
      string gnMJxEOUuL;
      string pWWUtLRMnD;
      string bgpgsHNZin;
      string idOpclnViP;
      string nNrsBiMdDR;
      string VWWWYAxePo;
      string qokGbMIfqH;
      string XwdYPOnweJ;
      string uiWRRMHqRc;
      if(iNgccGbklY == GiyxdniKaB){nJFsYzckRo = true;}
      else if(GiyxdniKaB == iNgccGbklY){wYyrJLNshJ = true;}
      if(nkRsdznMrw == gnMJxEOUuL){aflutYrxHK = true;}
      else if(gnMJxEOUuL == nkRsdznMrw){PAbTGoOAEo = true;}
      if(afewSoqoDO == pWWUtLRMnD){LBzFtHRSoP = true;}
      else if(pWWUtLRMnD == afewSoqoDO){cKbwbqWMFx = true;}
      if(tIXDNJlpTj == bgpgsHNZin){EQONSNpjAQ = true;}
      else if(bgpgsHNZin == tIXDNJlpTj){BsDyhlsDlj = true;}
      if(oPKiWSxeRq == idOpclnViP){kDepiOxaXr = true;}
      else if(idOpclnViP == oPKiWSxeRq){gmXmPDORct = true;}
      if(lbThLCikJn == nNrsBiMdDR){TJjHRmJzzQ = true;}
      else if(nNrsBiMdDR == lbThLCikJn){NFYPulwBPR = true;}
      if(PlgWdeMOfT == VWWWYAxePo){gJwBjKRXcf = true;}
      else if(VWWWYAxePo == PlgWdeMOfT){oAnkHWwdkT = true;}
      if(NyrIGKUuYA == qokGbMIfqH){iHwpYIWJWe = true;}
      if(qLXMbSopqK == XwdYPOnweJ){KquwwtgGwf = true;}
      if(ZBffTChnFq == uiWRRMHqRc){EqkijbGcFY = true;}
      while(qokGbMIfqH == NyrIGKUuYA){wLOUIolofX = true;}
      while(XwdYPOnweJ == XwdYPOnweJ){cEiKjwUnDw = true;}
      while(uiWRRMHqRc == uiWRRMHqRc){oqmTtgzmes = true;}
      if(nJFsYzckRo == true){nJFsYzckRo = false;}
      if(aflutYrxHK == true){aflutYrxHK = false;}
      if(LBzFtHRSoP == true){LBzFtHRSoP = false;}
      if(EQONSNpjAQ == true){EQONSNpjAQ = false;}
      if(kDepiOxaXr == true){kDepiOxaXr = false;}
      if(TJjHRmJzzQ == true){TJjHRmJzzQ = false;}
      if(gJwBjKRXcf == true){gJwBjKRXcf = false;}
      if(iHwpYIWJWe == true){iHwpYIWJWe = false;}
      if(KquwwtgGwf == true){KquwwtgGwf = false;}
      if(EqkijbGcFY == true){EqkijbGcFY = false;}
      if(wYyrJLNshJ == true){wYyrJLNshJ = false;}
      if(PAbTGoOAEo == true){PAbTGoOAEo = false;}
      if(cKbwbqWMFx == true){cKbwbqWMFx = false;}
      if(BsDyhlsDlj == true){BsDyhlsDlj = false;}
      if(gmXmPDORct == true){gmXmPDORct = false;}
      if(NFYPulwBPR == true){NFYPulwBPR = false;}
      if(oAnkHWwdkT == true){oAnkHWwdkT = false;}
      if(wLOUIolofX == true){wLOUIolofX = false;}
      if(cEiKjwUnDw == true){cEiKjwUnDw = false;}
      if(oqmTtgzmes == true){oqmTtgzmes = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHUQLRDVZE
{ 
  void ZJBdXJOJib()
  { 
      bool KgGQPiVRJB = false;
      bool BUEDIVkAbV = false;
      bool CeOlEdwKMD = false;
      bool jLwAORiKHm = false;
      bool FQBIceoUQE = false;
      bool gbsKBeSUMk = false;
      bool mKFGRoXDoq = false;
      bool masoPldGJY = false;
      bool obtHVISlyi = false;
      bool zOxVzuLupm = false;
      bool GkeZRGhDtP = false;
      bool BLLmwLPxjI = false;
      bool WlFFqXcWpU = false;
      bool ahPWSDwUpP = false;
      bool ZPrihmDJZm = false;
      bool eNLgPTfYhs = false;
      bool cLNYnTwnUr = false;
      bool PuGUiHtVXE = false;
      bool UTxDpMVhGy = false;
      bool XWmxlNCStO = false;
      string iKIsWzBgtG;
      string aJNSJFkoLD;
      string upAOVUUYSD;
      string PhRxIwwWWp;
      string DnVZRaTORW;
      string oaBYmsKsWB;
      string ecOpqrrPKM;
      string INRUAHTaxt;
      string BGGwOogrJP;
      string kCzVLZYfhY;
      string hDDENaJgYf;
      string YiwbAYVSaC;
      string LAGuaFNwJZ;
      string hmrXMxCBhn;
      string fzTdpCGWUl;
      string DGEfNhxIcI;
      string MMXyxkqYPD;
      string WUjmWLgcEY;
      string zpbWVbhLJd;
      string zsXZaSbUfE;
      if(iKIsWzBgtG == hDDENaJgYf){KgGQPiVRJB = true;}
      else if(hDDENaJgYf == iKIsWzBgtG){GkeZRGhDtP = true;}
      if(aJNSJFkoLD == YiwbAYVSaC){BUEDIVkAbV = true;}
      else if(YiwbAYVSaC == aJNSJFkoLD){BLLmwLPxjI = true;}
      if(upAOVUUYSD == LAGuaFNwJZ){CeOlEdwKMD = true;}
      else if(LAGuaFNwJZ == upAOVUUYSD){WlFFqXcWpU = true;}
      if(PhRxIwwWWp == hmrXMxCBhn){jLwAORiKHm = true;}
      else if(hmrXMxCBhn == PhRxIwwWWp){ahPWSDwUpP = true;}
      if(DnVZRaTORW == fzTdpCGWUl){FQBIceoUQE = true;}
      else if(fzTdpCGWUl == DnVZRaTORW){ZPrihmDJZm = true;}
      if(oaBYmsKsWB == DGEfNhxIcI){gbsKBeSUMk = true;}
      else if(DGEfNhxIcI == oaBYmsKsWB){eNLgPTfYhs = true;}
      if(ecOpqrrPKM == MMXyxkqYPD){mKFGRoXDoq = true;}
      else if(MMXyxkqYPD == ecOpqrrPKM){cLNYnTwnUr = true;}
      if(INRUAHTaxt == WUjmWLgcEY){masoPldGJY = true;}
      if(BGGwOogrJP == zpbWVbhLJd){obtHVISlyi = true;}
      if(kCzVLZYfhY == zsXZaSbUfE){zOxVzuLupm = true;}
      while(WUjmWLgcEY == INRUAHTaxt){PuGUiHtVXE = true;}
      while(zpbWVbhLJd == zpbWVbhLJd){UTxDpMVhGy = true;}
      while(zsXZaSbUfE == zsXZaSbUfE){XWmxlNCStO = true;}
      if(KgGQPiVRJB == true){KgGQPiVRJB = false;}
      if(BUEDIVkAbV == true){BUEDIVkAbV = false;}
      if(CeOlEdwKMD == true){CeOlEdwKMD = false;}
      if(jLwAORiKHm == true){jLwAORiKHm = false;}
      if(FQBIceoUQE == true){FQBIceoUQE = false;}
      if(gbsKBeSUMk == true){gbsKBeSUMk = false;}
      if(mKFGRoXDoq == true){mKFGRoXDoq = false;}
      if(masoPldGJY == true){masoPldGJY = false;}
      if(obtHVISlyi == true){obtHVISlyi = false;}
      if(zOxVzuLupm == true){zOxVzuLupm = false;}
      if(GkeZRGhDtP == true){GkeZRGhDtP = false;}
      if(BLLmwLPxjI == true){BLLmwLPxjI = false;}
      if(WlFFqXcWpU == true){WlFFqXcWpU = false;}
      if(ahPWSDwUpP == true){ahPWSDwUpP = false;}
      if(ZPrihmDJZm == true){ZPrihmDJZm = false;}
      if(eNLgPTfYhs == true){eNLgPTfYhs = false;}
      if(cLNYnTwnUr == true){cLNYnTwnUr = false;}
      if(PuGUiHtVXE == true){PuGUiHtVXE = false;}
      if(UTxDpMVhGy == true){UTxDpMVhGy = false;}
      if(XWmxlNCStO == true){XWmxlNCStO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUYSXSXFBA
{ 
  void iogYjlTZQk()
  { 
      bool dJJCkcDJoU = false;
      bool QYQYgaftMj = false;
      bool EmkAEObcmY = false;
      bool HqcJxeCpsK = false;
      bool sXzSqoxrRZ = false;
      bool OLXxlpXIyW = false;
      bool AZWPNZwHaB = false;
      bool YpACpgmRJO = false;
      bool QjKMJuSeXG = false;
      bool GsrWJTBjFQ = false;
      bool spQPBYLUHE = false;
      bool CGziFQOJFS = false;
      bool GQiTufxdsW = false;
      bool fDMsVZSuLk = false;
      bool jyXSEAtJQr = false;
      bool ErelJbGxUV = false;
      bool agajYzsFMf = false;
      bool xTxTiIrQPu = false;
      bool knMBSnYZis = false;
      bool SVZpKCWnsE = false;
      string iRyuxbOVQt;
      string MInmVYGQVj;
      string tNsHaVrCJh;
      string waynPFVxPG;
      string snIwLRKRAu;
      string bnfBPVXqTb;
      string iMLixlKzXQ;
      string CJBPqFExuI;
      string KaBOGHtwYt;
      string gedmWgcZyY;
      string HLtjsSmQKJ;
      string QauKRIKxbo;
      string qNaciXeNrJ;
      string ceyWBzfRUn;
      string UdlPcGiSUN;
      string VfxJhsjQAV;
      string mYXAglbYIS;
      string csbnUMbLAb;
      string nLrdmxgonI;
      string OOQzBuFkhq;
      if(iRyuxbOVQt == HLtjsSmQKJ){dJJCkcDJoU = true;}
      else if(HLtjsSmQKJ == iRyuxbOVQt){spQPBYLUHE = true;}
      if(MInmVYGQVj == QauKRIKxbo){QYQYgaftMj = true;}
      else if(QauKRIKxbo == MInmVYGQVj){CGziFQOJFS = true;}
      if(tNsHaVrCJh == qNaciXeNrJ){EmkAEObcmY = true;}
      else if(qNaciXeNrJ == tNsHaVrCJh){GQiTufxdsW = true;}
      if(waynPFVxPG == ceyWBzfRUn){HqcJxeCpsK = true;}
      else if(ceyWBzfRUn == waynPFVxPG){fDMsVZSuLk = true;}
      if(snIwLRKRAu == UdlPcGiSUN){sXzSqoxrRZ = true;}
      else if(UdlPcGiSUN == snIwLRKRAu){jyXSEAtJQr = true;}
      if(bnfBPVXqTb == VfxJhsjQAV){OLXxlpXIyW = true;}
      else if(VfxJhsjQAV == bnfBPVXqTb){ErelJbGxUV = true;}
      if(iMLixlKzXQ == mYXAglbYIS){AZWPNZwHaB = true;}
      else if(mYXAglbYIS == iMLixlKzXQ){agajYzsFMf = true;}
      if(CJBPqFExuI == csbnUMbLAb){YpACpgmRJO = true;}
      if(KaBOGHtwYt == nLrdmxgonI){QjKMJuSeXG = true;}
      if(gedmWgcZyY == OOQzBuFkhq){GsrWJTBjFQ = true;}
      while(csbnUMbLAb == CJBPqFExuI){xTxTiIrQPu = true;}
      while(nLrdmxgonI == nLrdmxgonI){knMBSnYZis = true;}
      while(OOQzBuFkhq == OOQzBuFkhq){SVZpKCWnsE = true;}
      if(dJJCkcDJoU == true){dJJCkcDJoU = false;}
      if(QYQYgaftMj == true){QYQYgaftMj = false;}
      if(EmkAEObcmY == true){EmkAEObcmY = false;}
      if(HqcJxeCpsK == true){HqcJxeCpsK = false;}
      if(sXzSqoxrRZ == true){sXzSqoxrRZ = false;}
      if(OLXxlpXIyW == true){OLXxlpXIyW = false;}
      if(AZWPNZwHaB == true){AZWPNZwHaB = false;}
      if(YpACpgmRJO == true){YpACpgmRJO = false;}
      if(QjKMJuSeXG == true){QjKMJuSeXG = false;}
      if(GsrWJTBjFQ == true){GsrWJTBjFQ = false;}
      if(spQPBYLUHE == true){spQPBYLUHE = false;}
      if(CGziFQOJFS == true){CGziFQOJFS = false;}
      if(GQiTufxdsW == true){GQiTufxdsW = false;}
      if(fDMsVZSuLk == true){fDMsVZSuLk = false;}
      if(jyXSEAtJQr == true){jyXSEAtJQr = false;}
      if(ErelJbGxUV == true){ErelJbGxUV = false;}
      if(agajYzsFMf == true){agajYzsFMf = false;}
      if(xTxTiIrQPu == true){xTxTiIrQPu = false;}
      if(knMBSnYZis == true){knMBSnYZis = false;}
      if(SVZpKCWnsE == true){SVZpKCWnsE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWFGHHHEDR
{ 
  void UxWEyGmFOO()
  { 
      bool jegjDrxSrq = false;
      bool xMOHRRFTOt = false;
      bool nADEOSiLUx = false;
      bool pdMHQKphwA = false;
      bool hFDILOWnzV = false;
      bool FLekpjacUk = false;
      bool IlyuATAGpG = false;
      bool aWXNMhwurA = false;
      bool uuLzqeybRg = false;
      bool jNMLrwHIHr = false;
      bool OQxsthnRYH = false;
      bool mejToNZzDV = false;
      bool UXnJWMKLUP = false;
      bool amnAlexSEJ = false;
      bool qgDKsEdrWe = false;
      bool VIElWpbmVg = false;
      bool XbwIgzqjhJ = false;
      bool PHttenUdQR = false;
      bool iRopsRiBcw = false;
      bool DJwWkOjtcs = false;
      string KuKCldRKbm;
      string capyPpYyVF;
      string NpOrdbVpFF;
      string BXXDUHSOIJ;
      string hfgbqAqFxC;
      string SFqwPTgSYJ;
      string IbEWkFClcI;
      string XJpLXhJmAd;
      string kPrDlwgbnB;
      string aApyBGbKpl;
      string xEcoeJOeYg;
      string KtRtXriBjo;
      string XaybgXTrKQ;
      string GyxNfgmDXc;
      string gBCGpghuaJ;
      string XZZAOWFAHG;
      string oWUHaMwDOp;
      string FecHHWYrlA;
      string oXRAsfXwzJ;
      string bluQmKftfd;
      if(KuKCldRKbm == xEcoeJOeYg){jegjDrxSrq = true;}
      else if(xEcoeJOeYg == KuKCldRKbm){OQxsthnRYH = true;}
      if(capyPpYyVF == KtRtXriBjo){xMOHRRFTOt = true;}
      else if(KtRtXriBjo == capyPpYyVF){mejToNZzDV = true;}
      if(NpOrdbVpFF == XaybgXTrKQ){nADEOSiLUx = true;}
      else if(XaybgXTrKQ == NpOrdbVpFF){UXnJWMKLUP = true;}
      if(BXXDUHSOIJ == GyxNfgmDXc){pdMHQKphwA = true;}
      else if(GyxNfgmDXc == BXXDUHSOIJ){amnAlexSEJ = true;}
      if(hfgbqAqFxC == gBCGpghuaJ){hFDILOWnzV = true;}
      else if(gBCGpghuaJ == hfgbqAqFxC){qgDKsEdrWe = true;}
      if(SFqwPTgSYJ == XZZAOWFAHG){FLekpjacUk = true;}
      else if(XZZAOWFAHG == SFqwPTgSYJ){VIElWpbmVg = true;}
      if(IbEWkFClcI == oWUHaMwDOp){IlyuATAGpG = true;}
      else if(oWUHaMwDOp == IbEWkFClcI){XbwIgzqjhJ = true;}
      if(XJpLXhJmAd == FecHHWYrlA){aWXNMhwurA = true;}
      if(kPrDlwgbnB == oXRAsfXwzJ){uuLzqeybRg = true;}
      if(aApyBGbKpl == bluQmKftfd){jNMLrwHIHr = true;}
      while(FecHHWYrlA == XJpLXhJmAd){PHttenUdQR = true;}
      while(oXRAsfXwzJ == oXRAsfXwzJ){iRopsRiBcw = true;}
      while(bluQmKftfd == bluQmKftfd){DJwWkOjtcs = true;}
      if(jegjDrxSrq == true){jegjDrxSrq = false;}
      if(xMOHRRFTOt == true){xMOHRRFTOt = false;}
      if(nADEOSiLUx == true){nADEOSiLUx = false;}
      if(pdMHQKphwA == true){pdMHQKphwA = false;}
      if(hFDILOWnzV == true){hFDILOWnzV = false;}
      if(FLekpjacUk == true){FLekpjacUk = false;}
      if(IlyuATAGpG == true){IlyuATAGpG = false;}
      if(aWXNMhwurA == true){aWXNMhwurA = false;}
      if(uuLzqeybRg == true){uuLzqeybRg = false;}
      if(jNMLrwHIHr == true){jNMLrwHIHr = false;}
      if(OQxsthnRYH == true){OQxsthnRYH = false;}
      if(mejToNZzDV == true){mejToNZzDV = false;}
      if(UXnJWMKLUP == true){UXnJWMKLUP = false;}
      if(amnAlexSEJ == true){amnAlexSEJ = false;}
      if(qgDKsEdrWe == true){qgDKsEdrWe = false;}
      if(VIElWpbmVg == true){VIElWpbmVg = false;}
      if(XbwIgzqjhJ == true){XbwIgzqjhJ = false;}
      if(PHttenUdQR == true){PHttenUdQR = false;}
      if(iRopsRiBcw == true){iRopsRiBcw = false;}
      if(DJwWkOjtcs == true){DJwWkOjtcs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTJBOQBKOJ
{ 
  void kQjSZQxTmY()
  { 
      bool ldoPCmjIyR = false;
      bool YhMOmxniff = false;
      bool HItYRGnJLE = false;
      bool hcBWQCoSuh = false;
      bool zzlfSLPSnl = false;
      bool FVkQNciQxw = false;
      bool yaxsjugoxj = false;
      bool HUnxgIWOGG = false;
      bool pVVYzLqjIn = false;
      bool SYVyjYCswW = false;
      bool daVDdjhnjF = false;
      bool GUKpFcFXsY = false;
      bool DwfJQizoNH = false;
      bool FcRicPARuO = false;
      bool cDADhyOesG = false;
      bool TezXTgtLlt = false;
      bool ksabzcDaNp = false;
      bool cmbduAwcbS = false;
      bool UTwGnactPu = false;
      bool VnfAdjbYDE = false;
      string WdXBGiKcmI;
      string lFMLMeOlbO;
      string TTLpjDynXE;
      string yJsRRXDxPn;
      string CItUHslenB;
      string eCFshCRgQC;
      string jVEhJcMutn;
      string bRWnLKYqip;
      string QSzWZuDzjO;
      string FVfMDfEMKe;
      string fqkAZNfRgW;
      string cayakRVhHN;
      string YMKehFkJjf;
      string GMgEKZhzwM;
      string PlSMleXFal;
      string JVEwFSfFRU;
      string cVgBQPssPL;
      string iWkuymtxsC;
      string gehyVjIjyq;
      string schbjsFQwV;
      if(WdXBGiKcmI == fqkAZNfRgW){ldoPCmjIyR = true;}
      else if(fqkAZNfRgW == WdXBGiKcmI){daVDdjhnjF = true;}
      if(lFMLMeOlbO == cayakRVhHN){YhMOmxniff = true;}
      else if(cayakRVhHN == lFMLMeOlbO){GUKpFcFXsY = true;}
      if(TTLpjDynXE == YMKehFkJjf){HItYRGnJLE = true;}
      else if(YMKehFkJjf == TTLpjDynXE){DwfJQizoNH = true;}
      if(yJsRRXDxPn == GMgEKZhzwM){hcBWQCoSuh = true;}
      else if(GMgEKZhzwM == yJsRRXDxPn){FcRicPARuO = true;}
      if(CItUHslenB == PlSMleXFal){zzlfSLPSnl = true;}
      else if(PlSMleXFal == CItUHslenB){cDADhyOesG = true;}
      if(eCFshCRgQC == JVEwFSfFRU){FVkQNciQxw = true;}
      else if(JVEwFSfFRU == eCFshCRgQC){TezXTgtLlt = true;}
      if(jVEhJcMutn == cVgBQPssPL){yaxsjugoxj = true;}
      else if(cVgBQPssPL == jVEhJcMutn){ksabzcDaNp = true;}
      if(bRWnLKYqip == iWkuymtxsC){HUnxgIWOGG = true;}
      if(QSzWZuDzjO == gehyVjIjyq){pVVYzLqjIn = true;}
      if(FVfMDfEMKe == schbjsFQwV){SYVyjYCswW = true;}
      while(iWkuymtxsC == bRWnLKYqip){cmbduAwcbS = true;}
      while(gehyVjIjyq == gehyVjIjyq){UTwGnactPu = true;}
      while(schbjsFQwV == schbjsFQwV){VnfAdjbYDE = true;}
      if(ldoPCmjIyR == true){ldoPCmjIyR = false;}
      if(YhMOmxniff == true){YhMOmxniff = false;}
      if(HItYRGnJLE == true){HItYRGnJLE = false;}
      if(hcBWQCoSuh == true){hcBWQCoSuh = false;}
      if(zzlfSLPSnl == true){zzlfSLPSnl = false;}
      if(FVkQNciQxw == true){FVkQNciQxw = false;}
      if(yaxsjugoxj == true){yaxsjugoxj = false;}
      if(HUnxgIWOGG == true){HUnxgIWOGG = false;}
      if(pVVYzLqjIn == true){pVVYzLqjIn = false;}
      if(SYVyjYCswW == true){SYVyjYCswW = false;}
      if(daVDdjhnjF == true){daVDdjhnjF = false;}
      if(GUKpFcFXsY == true){GUKpFcFXsY = false;}
      if(DwfJQizoNH == true){DwfJQizoNH = false;}
      if(FcRicPARuO == true){FcRicPARuO = false;}
      if(cDADhyOesG == true){cDADhyOesG = false;}
      if(TezXTgtLlt == true){TezXTgtLlt = false;}
      if(ksabzcDaNp == true){ksabzcDaNp = false;}
      if(cmbduAwcbS == true){cmbduAwcbS = false;}
      if(UTwGnactPu == true){UTwGnactPu = false;}
      if(VnfAdjbYDE == true){VnfAdjbYDE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BDQTYXWJDB
{ 
  void NTbXBgNZtU()
  { 
      bool hWHqLWbRWr = false;
      bool pbrpUurlQf = false;
      bool MsYNJfLHFW = false;
      bool YIqMUBxGMU = false;
      bool zIQxIjbLwX = false;
      bool ZUtGboyshe = false;
      bool KTMzTgjeVT = false;
      bool xkZufEcaFY = false;
      bool EzKhxEOkke = false;
      bool CDYgJeuQda = false;
      bool zwpcZntzZW = false;
      bool MXnIaLJeCP = false;
      bool SytpRtLslA = false;
      bool JLxeZIJhHI = false;
      bool JOLNSdPPFy = false;
      bool VQNNHBBzKf = false;
      bool cBNYNAaIiS = false;
      bool BaWtGDmgXm = false;
      bool dwmmeryiWY = false;
      bool HJWbfIBlzR = false;
      string ZETXJOhtak;
      string UsgriylzeW;
      string FVUJtZQVsm;
      string cMEeiaZUkW;
      string DnVPamdfRc;
      string rQCCBDiKdi;
      string xLBmIHoBII;
      string YQNISQzFhH;
      string ujEPuLKBdf;
      string qOqBYqmiHT;
      string xcWJEaDsik;
      string DdcVnNHkrw;
      string wmWcQKZMia;
      string cQxNJRNtLT;
      string IQSsbNlUNL;
      string jBpKXKFsrs;
      string ApKHHmfOMV;
      string zNZXneTdBC;
      string XFyXqbZmpy;
      string MTBRSRGKln;
      if(ZETXJOhtak == xcWJEaDsik){hWHqLWbRWr = true;}
      else if(xcWJEaDsik == ZETXJOhtak){zwpcZntzZW = true;}
      if(UsgriylzeW == DdcVnNHkrw){pbrpUurlQf = true;}
      else if(DdcVnNHkrw == UsgriylzeW){MXnIaLJeCP = true;}
      if(FVUJtZQVsm == wmWcQKZMia){MsYNJfLHFW = true;}
      else if(wmWcQKZMia == FVUJtZQVsm){SytpRtLslA = true;}
      if(cMEeiaZUkW == cQxNJRNtLT){YIqMUBxGMU = true;}
      else if(cQxNJRNtLT == cMEeiaZUkW){JLxeZIJhHI = true;}
      if(DnVPamdfRc == IQSsbNlUNL){zIQxIjbLwX = true;}
      else if(IQSsbNlUNL == DnVPamdfRc){JOLNSdPPFy = true;}
      if(rQCCBDiKdi == jBpKXKFsrs){ZUtGboyshe = true;}
      else if(jBpKXKFsrs == rQCCBDiKdi){VQNNHBBzKf = true;}
      if(xLBmIHoBII == ApKHHmfOMV){KTMzTgjeVT = true;}
      else if(ApKHHmfOMV == xLBmIHoBII){cBNYNAaIiS = true;}
      if(YQNISQzFhH == zNZXneTdBC){xkZufEcaFY = true;}
      if(ujEPuLKBdf == XFyXqbZmpy){EzKhxEOkke = true;}
      if(qOqBYqmiHT == MTBRSRGKln){CDYgJeuQda = true;}
      while(zNZXneTdBC == YQNISQzFhH){BaWtGDmgXm = true;}
      while(XFyXqbZmpy == XFyXqbZmpy){dwmmeryiWY = true;}
      while(MTBRSRGKln == MTBRSRGKln){HJWbfIBlzR = true;}
      if(hWHqLWbRWr == true){hWHqLWbRWr = false;}
      if(pbrpUurlQf == true){pbrpUurlQf = false;}
      if(MsYNJfLHFW == true){MsYNJfLHFW = false;}
      if(YIqMUBxGMU == true){YIqMUBxGMU = false;}
      if(zIQxIjbLwX == true){zIQxIjbLwX = false;}
      if(ZUtGboyshe == true){ZUtGboyshe = false;}
      if(KTMzTgjeVT == true){KTMzTgjeVT = false;}
      if(xkZufEcaFY == true){xkZufEcaFY = false;}
      if(EzKhxEOkke == true){EzKhxEOkke = false;}
      if(CDYgJeuQda == true){CDYgJeuQda = false;}
      if(zwpcZntzZW == true){zwpcZntzZW = false;}
      if(MXnIaLJeCP == true){MXnIaLJeCP = false;}
      if(SytpRtLslA == true){SytpRtLslA = false;}
      if(JLxeZIJhHI == true){JLxeZIJhHI = false;}
      if(JOLNSdPPFy == true){JOLNSdPPFy = false;}
      if(VQNNHBBzKf == true){VQNNHBBzKf = false;}
      if(cBNYNAaIiS == true){cBNYNAaIiS = false;}
      if(BaWtGDmgXm == true){BaWtGDmgXm = false;}
      if(dwmmeryiWY == true){dwmmeryiWY = false;}
      if(HJWbfIBlzR == true){HJWbfIBlzR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNABWZMJDN
{ 
  void rPOeaufDcV()
  { 
      bool iFIrRTwULO = false;
      bool IesecNGWQl = false;
      bool QLElFixenB = false;
      bool VbhGjPpJuH = false;
      bool uEOUynIjlS = false;
      bool rfdlDWAWmh = false;
      bool VRgJsgwmtM = false;
      bool WwbJpMxjnQ = false;
      bool aNrUJpxwDN = false;
      bool PTVMldWEbQ = false;
      bool qVoZuuDUup = false;
      bool ZPhWHIYLAD = false;
      bool iAigxDZOWL = false;
      bool prIWYEXSYN = false;
      bool lcANmzlzFc = false;
      bool ELEXhqlIcr = false;
      bool VoxizhHKxC = false;
      bool jGllRGzVsx = false;
      bool QZJsGdmjog = false;
      bool SPogrweQNF = false;
      string QDzayPKAcW;
      string JKsmPIWlQI;
      string YsVRTVgeNF;
      string cLKSldmnXq;
      string pmaNwqVGak;
      string xrYUAWhgHc;
      string hflWsyAaAl;
      string VhOYSkSHVb;
      string zaDcIkmoRO;
      string wFgtJJADUy;
      string ptFoOOczBO;
      string EZLecGbJOI;
      string LKJkpPBTPI;
      string jOmWlEVOOt;
      string HmnCKVtBRC;
      string gqoMmekTzy;
      string MIjrepmosY;
      string kNtUAXWGaT;
      string VzCMbrYajG;
      string SBPPgyCuXU;
      if(QDzayPKAcW == ptFoOOczBO){iFIrRTwULO = true;}
      else if(ptFoOOczBO == QDzayPKAcW){qVoZuuDUup = true;}
      if(JKsmPIWlQI == EZLecGbJOI){IesecNGWQl = true;}
      else if(EZLecGbJOI == JKsmPIWlQI){ZPhWHIYLAD = true;}
      if(YsVRTVgeNF == LKJkpPBTPI){QLElFixenB = true;}
      else if(LKJkpPBTPI == YsVRTVgeNF){iAigxDZOWL = true;}
      if(cLKSldmnXq == jOmWlEVOOt){VbhGjPpJuH = true;}
      else if(jOmWlEVOOt == cLKSldmnXq){prIWYEXSYN = true;}
      if(pmaNwqVGak == HmnCKVtBRC){uEOUynIjlS = true;}
      else if(HmnCKVtBRC == pmaNwqVGak){lcANmzlzFc = true;}
      if(xrYUAWhgHc == gqoMmekTzy){rfdlDWAWmh = true;}
      else if(gqoMmekTzy == xrYUAWhgHc){ELEXhqlIcr = true;}
      if(hflWsyAaAl == MIjrepmosY){VRgJsgwmtM = true;}
      else if(MIjrepmosY == hflWsyAaAl){VoxizhHKxC = true;}
      if(VhOYSkSHVb == kNtUAXWGaT){WwbJpMxjnQ = true;}
      if(zaDcIkmoRO == VzCMbrYajG){aNrUJpxwDN = true;}
      if(wFgtJJADUy == SBPPgyCuXU){PTVMldWEbQ = true;}
      while(kNtUAXWGaT == VhOYSkSHVb){jGllRGzVsx = true;}
      while(VzCMbrYajG == VzCMbrYajG){QZJsGdmjog = true;}
      while(SBPPgyCuXU == SBPPgyCuXU){SPogrweQNF = true;}
      if(iFIrRTwULO == true){iFIrRTwULO = false;}
      if(IesecNGWQl == true){IesecNGWQl = false;}
      if(QLElFixenB == true){QLElFixenB = false;}
      if(VbhGjPpJuH == true){VbhGjPpJuH = false;}
      if(uEOUynIjlS == true){uEOUynIjlS = false;}
      if(rfdlDWAWmh == true){rfdlDWAWmh = false;}
      if(VRgJsgwmtM == true){VRgJsgwmtM = false;}
      if(WwbJpMxjnQ == true){WwbJpMxjnQ = false;}
      if(aNrUJpxwDN == true){aNrUJpxwDN = false;}
      if(PTVMldWEbQ == true){PTVMldWEbQ = false;}
      if(qVoZuuDUup == true){qVoZuuDUup = false;}
      if(ZPhWHIYLAD == true){ZPhWHIYLAD = false;}
      if(iAigxDZOWL == true){iAigxDZOWL = false;}
      if(prIWYEXSYN == true){prIWYEXSYN = false;}
      if(lcANmzlzFc == true){lcANmzlzFc = false;}
      if(ELEXhqlIcr == true){ELEXhqlIcr = false;}
      if(VoxizhHKxC == true){VoxizhHKxC = false;}
      if(jGllRGzVsx == true){jGllRGzVsx = false;}
      if(QZJsGdmjog == true){QZJsGdmjog = false;}
      if(SPogrweQNF == true){SPogrweQNF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOKALGMOAG
{ 
  void AmcCHgPkTU()
  { 
      bool PDXqoydDcX = false;
      bool eLkPpIEFuS = false;
      bool ZFfHJKjJFY = false;
      bool aIbwDtjCwa = false;
      bool FqVXnLHIoQ = false;
      bool NRozsJWQhe = false;
      bool NTxEwVjnMu = false;
      bool XCITNhiITx = false;
      bool DbUoKJTbCs = false;
      bool WTURNksRaR = false;
      bool bSwsrLIUlL = false;
      bool aOwjakzIsm = false;
      bool BIkSYEgqFb = false;
      bool nRgBVkfbxy = false;
      bool BzoqSHWjpb = false;
      bool kkXmPSgcTn = false;
      bool dQOKWIguOo = false;
      bool FXLulCStAR = false;
      bool gxBdpCstkC = false;
      bool ECHIUjjeUJ = false;
      string BnUZTVhnGy;
      string SYsBuRdyuf;
      string pWSbqJhjzT;
      string FXSEOOQBuc;
      string XOpVccJnDQ;
      string CVoKedUrhK;
      string nyomruFnlg;
      string AbDSHagwzO;
      string zsfhQjiHYj;
      string sXTjnZYDch;
      string WVBWPZRVCE;
      string xYsTLuRGVI;
      string LyPCmbISeh;
      string BcTRrdqISq;
      string RNEUmUezYs;
      string HRhTVXGzim;
      string RyqUCUEbbg;
      string DJneqystOS;
      string xItlZitzuT;
      string XrYeYSWjSS;
      if(BnUZTVhnGy == WVBWPZRVCE){PDXqoydDcX = true;}
      else if(WVBWPZRVCE == BnUZTVhnGy){bSwsrLIUlL = true;}
      if(SYsBuRdyuf == xYsTLuRGVI){eLkPpIEFuS = true;}
      else if(xYsTLuRGVI == SYsBuRdyuf){aOwjakzIsm = true;}
      if(pWSbqJhjzT == LyPCmbISeh){ZFfHJKjJFY = true;}
      else if(LyPCmbISeh == pWSbqJhjzT){BIkSYEgqFb = true;}
      if(FXSEOOQBuc == BcTRrdqISq){aIbwDtjCwa = true;}
      else if(BcTRrdqISq == FXSEOOQBuc){nRgBVkfbxy = true;}
      if(XOpVccJnDQ == RNEUmUezYs){FqVXnLHIoQ = true;}
      else if(RNEUmUezYs == XOpVccJnDQ){BzoqSHWjpb = true;}
      if(CVoKedUrhK == HRhTVXGzim){NRozsJWQhe = true;}
      else if(HRhTVXGzim == CVoKedUrhK){kkXmPSgcTn = true;}
      if(nyomruFnlg == RyqUCUEbbg){NTxEwVjnMu = true;}
      else if(RyqUCUEbbg == nyomruFnlg){dQOKWIguOo = true;}
      if(AbDSHagwzO == DJneqystOS){XCITNhiITx = true;}
      if(zsfhQjiHYj == xItlZitzuT){DbUoKJTbCs = true;}
      if(sXTjnZYDch == XrYeYSWjSS){WTURNksRaR = true;}
      while(DJneqystOS == AbDSHagwzO){FXLulCStAR = true;}
      while(xItlZitzuT == xItlZitzuT){gxBdpCstkC = true;}
      while(XrYeYSWjSS == XrYeYSWjSS){ECHIUjjeUJ = true;}
      if(PDXqoydDcX == true){PDXqoydDcX = false;}
      if(eLkPpIEFuS == true){eLkPpIEFuS = false;}
      if(ZFfHJKjJFY == true){ZFfHJKjJFY = false;}
      if(aIbwDtjCwa == true){aIbwDtjCwa = false;}
      if(FqVXnLHIoQ == true){FqVXnLHIoQ = false;}
      if(NRozsJWQhe == true){NRozsJWQhe = false;}
      if(NTxEwVjnMu == true){NTxEwVjnMu = false;}
      if(XCITNhiITx == true){XCITNhiITx = false;}
      if(DbUoKJTbCs == true){DbUoKJTbCs = false;}
      if(WTURNksRaR == true){WTURNksRaR = false;}
      if(bSwsrLIUlL == true){bSwsrLIUlL = false;}
      if(aOwjakzIsm == true){aOwjakzIsm = false;}
      if(BIkSYEgqFb == true){BIkSYEgqFb = false;}
      if(nRgBVkfbxy == true){nRgBVkfbxy = false;}
      if(BzoqSHWjpb == true){BzoqSHWjpb = false;}
      if(kkXmPSgcTn == true){kkXmPSgcTn = false;}
      if(dQOKWIguOo == true){dQOKWIguOo = false;}
      if(FXLulCStAR == true){FXLulCStAR = false;}
      if(gxBdpCstkC == true){gxBdpCstkC = false;}
      if(ECHIUjjeUJ == true){ECHIUjjeUJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASFGMQFYKV
{ 
  void PQOUVPAyLX()
  { 
      bool xjduFULhzN = false;
      bool MFeOMZwmnX = false;
      bool PBVuobpByi = false;
      bool cpVqlsgGWQ = false;
      bool CGRZnVLnDh = false;
      bool PZgJDwOiFc = false;
      bool eJiQkVjnbS = false;
      bool soPWVJiuHT = false;
      bool PCxPSDJMmp = false;
      bool eyBtlrWBoR = false;
      bool lXLjoaJJmt = false;
      bool MSakMbLTyg = false;
      bool MXAlnumVjd = false;
      bool mhGpgrqMaq = false;
      bool szYscMWPgJ = false;
      bool fDCIEOXYws = false;
      bool mnYJHeMkEU = false;
      bool kyrGmMyGJa = false;
      bool XXnaxiexkS = false;
      bool TRQgEFZPlx = false;
      string aeZsoeBOwl;
      string EbyopsJNPL;
      string DblEPUUDOa;
      string LpzbCpUZjl;
      string FFKZlICMAo;
      string HouecyrVcT;
      string KxzUZNbWmz;
      string YiddGxRLRG;
      string RHCYSVtTzD;
      string yzxPbHFozX;
      string gfZBQYLRYe;
      string ffDVCCtaBE;
      string THWiBYlOBy;
      string rbMsZkhBIt;
      string JcuTXRuaMY;
      string MdntEYIpzq;
      string lxPZlDTKwR;
      string TrSGtpLDLj;
      string dLBclNnRnA;
      string bqCQILMVgT;
      if(aeZsoeBOwl == gfZBQYLRYe){xjduFULhzN = true;}
      else if(gfZBQYLRYe == aeZsoeBOwl){lXLjoaJJmt = true;}
      if(EbyopsJNPL == ffDVCCtaBE){MFeOMZwmnX = true;}
      else if(ffDVCCtaBE == EbyopsJNPL){MSakMbLTyg = true;}
      if(DblEPUUDOa == THWiBYlOBy){PBVuobpByi = true;}
      else if(THWiBYlOBy == DblEPUUDOa){MXAlnumVjd = true;}
      if(LpzbCpUZjl == rbMsZkhBIt){cpVqlsgGWQ = true;}
      else if(rbMsZkhBIt == LpzbCpUZjl){mhGpgrqMaq = true;}
      if(FFKZlICMAo == JcuTXRuaMY){CGRZnVLnDh = true;}
      else if(JcuTXRuaMY == FFKZlICMAo){szYscMWPgJ = true;}
      if(HouecyrVcT == MdntEYIpzq){PZgJDwOiFc = true;}
      else if(MdntEYIpzq == HouecyrVcT){fDCIEOXYws = true;}
      if(KxzUZNbWmz == lxPZlDTKwR){eJiQkVjnbS = true;}
      else if(lxPZlDTKwR == KxzUZNbWmz){mnYJHeMkEU = true;}
      if(YiddGxRLRG == TrSGtpLDLj){soPWVJiuHT = true;}
      if(RHCYSVtTzD == dLBclNnRnA){PCxPSDJMmp = true;}
      if(yzxPbHFozX == bqCQILMVgT){eyBtlrWBoR = true;}
      while(TrSGtpLDLj == YiddGxRLRG){kyrGmMyGJa = true;}
      while(dLBclNnRnA == dLBclNnRnA){XXnaxiexkS = true;}
      while(bqCQILMVgT == bqCQILMVgT){TRQgEFZPlx = true;}
      if(xjduFULhzN == true){xjduFULhzN = false;}
      if(MFeOMZwmnX == true){MFeOMZwmnX = false;}
      if(PBVuobpByi == true){PBVuobpByi = false;}
      if(cpVqlsgGWQ == true){cpVqlsgGWQ = false;}
      if(CGRZnVLnDh == true){CGRZnVLnDh = false;}
      if(PZgJDwOiFc == true){PZgJDwOiFc = false;}
      if(eJiQkVjnbS == true){eJiQkVjnbS = false;}
      if(soPWVJiuHT == true){soPWVJiuHT = false;}
      if(PCxPSDJMmp == true){PCxPSDJMmp = false;}
      if(eyBtlrWBoR == true){eyBtlrWBoR = false;}
      if(lXLjoaJJmt == true){lXLjoaJJmt = false;}
      if(MSakMbLTyg == true){MSakMbLTyg = false;}
      if(MXAlnumVjd == true){MXAlnumVjd = false;}
      if(mhGpgrqMaq == true){mhGpgrqMaq = false;}
      if(szYscMWPgJ == true){szYscMWPgJ = false;}
      if(fDCIEOXYws == true){fDCIEOXYws = false;}
      if(mnYJHeMkEU == true){mnYJHeMkEU = false;}
      if(kyrGmMyGJa == true){kyrGmMyGJa = false;}
      if(XXnaxiexkS == true){XXnaxiexkS = false;}
      if(TRQgEFZPlx == true){TRQgEFZPlx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGCOOWLCCV
{ 
  void RHETjKLMwW()
  { 
      bool NVMPCmpnJx = false;
      bool GJhXEyUyVq = false;
      bool pmXLNgVKie = false;
      bool EWrXTTymrX = false;
      bool HKYWaHoDJF = false;
      bool AokAaaxACU = false;
      bool QfFerjRKEk = false;
      bool AgGyjeNAkF = false;
      bool qSAcdOkqxr = false;
      bool VyjWGaEtep = false;
      bool peyYFSimQu = false;
      bool NxPxcyebAc = false;
      bool zZMMOCxiqI = false;
      bool aSVtOMTbXL = false;
      bool fxaCeYhmtI = false;
      bool wbtCqQRlJD = false;
      bool UAuHUtbUhQ = false;
      bool dCEnwBzKhp = false;
      bool TKoiLyYSCy = false;
      bool tgSTpfBShj = false;
      string zGdnnIbVmX;
      string pwwMRRbcdS;
      string BbzzIdwpdw;
      string RjLwtDwutT;
      string DpVGWnJjkU;
      string GDGsNWGeeJ;
      string LkqqFFkzSO;
      string VfhJOLFsbU;
      string UMEIoNdSiW;
      string xRPjHRydBR;
      string DJRWzZVwdC;
      string QNDKozfiCr;
      string aSQuQEQyCw;
      string MarKRKthJO;
      string rhngGiOFtH;
      string lPbIpjsWFu;
      string JXsgooVrse;
      string FyYmzsdjng;
      string pKDtKxziUg;
      string RXbOEUnHrQ;
      if(zGdnnIbVmX == DJRWzZVwdC){NVMPCmpnJx = true;}
      else if(DJRWzZVwdC == zGdnnIbVmX){peyYFSimQu = true;}
      if(pwwMRRbcdS == QNDKozfiCr){GJhXEyUyVq = true;}
      else if(QNDKozfiCr == pwwMRRbcdS){NxPxcyebAc = true;}
      if(BbzzIdwpdw == aSQuQEQyCw){pmXLNgVKie = true;}
      else if(aSQuQEQyCw == BbzzIdwpdw){zZMMOCxiqI = true;}
      if(RjLwtDwutT == MarKRKthJO){EWrXTTymrX = true;}
      else if(MarKRKthJO == RjLwtDwutT){aSVtOMTbXL = true;}
      if(DpVGWnJjkU == rhngGiOFtH){HKYWaHoDJF = true;}
      else if(rhngGiOFtH == DpVGWnJjkU){fxaCeYhmtI = true;}
      if(GDGsNWGeeJ == lPbIpjsWFu){AokAaaxACU = true;}
      else if(lPbIpjsWFu == GDGsNWGeeJ){wbtCqQRlJD = true;}
      if(LkqqFFkzSO == JXsgooVrse){QfFerjRKEk = true;}
      else if(JXsgooVrse == LkqqFFkzSO){UAuHUtbUhQ = true;}
      if(VfhJOLFsbU == FyYmzsdjng){AgGyjeNAkF = true;}
      if(UMEIoNdSiW == pKDtKxziUg){qSAcdOkqxr = true;}
      if(xRPjHRydBR == RXbOEUnHrQ){VyjWGaEtep = true;}
      while(FyYmzsdjng == VfhJOLFsbU){dCEnwBzKhp = true;}
      while(pKDtKxziUg == pKDtKxziUg){TKoiLyYSCy = true;}
      while(RXbOEUnHrQ == RXbOEUnHrQ){tgSTpfBShj = true;}
      if(NVMPCmpnJx == true){NVMPCmpnJx = false;}
      if(GJhXEyUyVq == true){GJhXEyUyVq = false;}
      if(pmXLNgVKie == true){pmXLNgVKie = false;}
      if(EWrXTTymrX == true){EWrXTTymrX = false;}
      if(HKYWaHoDJF == true){HKYWaHoDJF = false;}
      if(AokAaaxACU == true){AokAaaxACU = false;}
      if(QfFerjRKEk == true){QfFerjRKEk = false;}
      if(AgGyjeNAkF == true){AgGyjeNAkF = false;}
      if(qSAcdOkqxr == true){qSAcdOkqxr = false;}
      if(VyjWGaEtep == true){VyjWGaEtep = false;}
      if(peyYFSimQu == true){peyYFSimQu = false;}
      if(NxPxcyebAc == true){NxPxcyebAc = false;}
      if(zZMMOCxiqI == true){zZMMOCxiqI = false;}
      if(aSVtOMTbXL == true){aSVtOMTbXL = false;}
      if(fxaCeYhmtI == true){fxaCeYhmtI = false;}
      if(wbtCqQRlJD == true){wbtCqQRlJD = false;}
      if(UAuHUtbUhQ == true){UAuHUtbUhQ = false;}
      if(dCEnwBzKhp == true){dCEnwBzKhp = false;}
      if(TKoiLyYSCy == true){TKoiLyYSCy = false;}
      if(tgSTpfBShj == true){tgSTpfBShj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKQWXGWFEO
{ 
  void nWyVLjZIGw()
  { 
      bool rgiFAFVncF = false;
      bool bSryrAHbsr = false;
      bool tytosiuAIC = false;
      bool mVWfwrHkXe = false;
      bool SQdLhYLXKm = false;
      bool SQcWfsltLR = false;
      bool JVeZSGuMCA = false;
      bool rVEOZcThHU = false;
      bool XWoVjVrzAC = false;
      bool FNYFUwlEsa = false;
      bool cyVKtwLOxC = false;
      bool YEmqsmgJpw = false;
      bool OuMAtexzsc = false;
      bool qPofqYBdam = false;
      bool JdCxcBagMg = false;
      bool PbNwMglUPP = false;
      bool zMUTLJOGAT = false;
      bool kCiDljsPWs = false;
      bool DPlMNOCrTJ = false;
      bool mfOKmwJikT = false;
      string fdqlOtPcRy;
      string yueKKHMqAK;
      string dlnMVzRHFu;
      string pOWBLHjblI;
      string FTiQwhQfaE;
      string AkGnHtpdQO;
      string bHXVHiXcyC;
      string WjErEKDWPm;
      string ikgBtFIhtR;
      string QGLWfxuMIM;
      string JmgXgPfNjw;
      string pTNcfqaWbC;
      string apigkQYhMG;
      string OpNDduDITe;
      string Ytyxaxrhpn;
      string WYkGlTEzlQ;
      string qyAchAFKzk;
      string mRCwcfqlGn;
      string YpqYjoFHQK;
      string qEWCmasVOa;
      if(fdqlOtPcRy == JmgXgPfNjw){rgiFAFVncF = true;}
      else if(JmgXgPfNjw == fdqlOtPcRy){cyVKtwLOxC = true;}
      if(yueKKHMqAK == pTNcfqaWbC){bSryrAHbsr = true;}
      else if(pTNcfqaWbC == yueKKHMqAK){YEmqsmgJpw = true;}
      if(dlnMVzRHFu == apigkQYhMG){tytosiuAIC = true;}
      else if(apigkQYhMG == dlnMVzRHFu){OuMAtexzsc = true;}
      if(pOWBLHjblI == OpNDduDITe){mVWfwrHkXe = true;}
      else if(OpNDduDITe == pOWBLHjblI){qPofqYBdam = true;}
      if(FTiQwhQfaE == Ytyxaxrhpn){SQdLhYLXKm = true;}
      else if(Ytyxaxrhpn == FTiQwhQfaE){JdCxcBagMg = true;}
      if(AkGnHtpdQO == WYkGlTEzlQ){SQcWfsltLR = true;}
      else if(WYkGlTEzlQ == AkGnHtpdQO){PbNwMglUPP = true;}
      if(bHXVHiXcyC == qyAchAFKzk){JVeZSGuMCA = true;}
      else if(qyAchAFKzk == bHXVHiXcyC){zMUTLJOGAT = true;}
      if(WjErEKDWPm == mRCwcfqlGn){rVEOZcThHU = true;}
      if(ikgBtFIhtR == YpqYjoFHQK){XWoVjVrzAC = true;}
      if(QGLWfxuMIM == qEWCmasVOa){FNYFUwlEsa = true;}
      while(mRCwcfqlGn == WjErEKDWPm){kCiDljsPWs = true;}
      while(YpqYjoFHQK == YpqYjoFHQK){DPlMNOCrTJ = true;}
      while(qEWCmasVOa == qEWCmasVOa){mfOKmwJikT = true;}
      if(rgiFAFVncF == true){rgiFAFVncF = false;}
      if(bSryrAHbsr == true){bSryrAHbsr = false;}
      if(tytosiuAIC == true){tytosiuAIC = false;}
      if(mVWfwrHkXe == true){mVWfwrHkXe = false;}
      if(SQdLhYLXKm == true){SQdLhYLXKm = false;}
      if(SQcWfsltLR == true){SQcWfsltLR = false;}
      if(JVeZSGuMCA == true){JVeZSGuMCA = false;}
      if(rVEOZcThHU == true){rVEOZcThHU = false;}
      if(XWoVjVrzAC == true){XWoVjVrzAC = false;}
      if(FNYFUwlEsa == true){FNYFUwlEsa = false;}
      if(cyVKtwLOxC == true){cyVKtwLOxC = false;}
      if(YEmqsmgJpw == true){YEmqsmgJpw = false;}
      if(OuMAtexzsc == true){OuMAtexzsc = false;}
      if(qPofqYBdam == true){qPofqYBdam = false;}
      if(JdCxcBagMg == true){JdCxcBagMg = false;}
      if(PbNwMglUPP == true){PbNwMglUPP = false;}
      if(zMUTLJOGAT == true){zMUTLJOGAT = false;}
      if(kCiDljsPWs == true){kCiDljsPWs = false;}
      if(DPlMNOCrTJ == true){DPlMNOCrTJ = false;}
      if(mfOKmwJikT == true){mfOKmwJikT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBRNORIHAC
{ 
  void oDHlKOPfNi()
  { 
      bool WyHBQAUOki = false;
      bool aGtwjQVQXA = false;
      bool qRfPkxDosL = false;
      bool QdJZduYRgC = false;
      bool kamrikPPEF = false;
      bool jRklyFSrQT = false;
      bool xfUYSxxUSo = false;
      bool rDiUOQemfA = false;
      bool hnjnbyrXbY = false;
      bool bgBMFFFOZl = false;
      bool mtxPNghPWg = false;
      bool afLPlJugxU = false;
      bool EZssMLBWPJ = false;
      bool KPNtMmqUau = false;
      bool QcBtxwUlau = false;
      bool JXQFgNBDCB = false;
      bool eLzMWKSRDz = false;
      bool SaGCDbYyuQ = false;
      bool qPwTzmzHMy = false;
      bool kmRYPFcnXm = false;
      string yZAPpCbwse;
      string RuXSlGlQJx;
      string uLNtEeOeCg;
      string dooZJqfrOm;
      string mqaTGsqCHE;
      string DrHHRlMGLL;
      string nwtMAcGyIt;
      string ZtCVKDjtmL;
      string mMWxclhhIX;
      string eZgDzpwOSc;
      string lssMdJokwN;
      string BRSzXaZxiO;
      string uXpjOAMzWU;
      string GUbKYtSJSS;
      string wwktVNGgeY;
      string QzeDhOCJyd;
      string wpObHgpIZc;
      string HPdQSymwOB;
      string sfTyDGoXbK;
      string qJLoWGhJlo;
      if(yZAPpCbwse == lssMdJokwN){WyHBQAUOki = true;}
      else if(lssMdJokwN == yZAPpCbwse){mtxPNghPWg = true;}
      if(RuXSlGlQJx == BRSzXaZxiO){aGtwjQVQXA = true;}
      else if(BRSzXaZxiO == RuXSlGlQJx){afLPlJugxU = true;}
      if(uLNtEeOeCg == uXpjOAMzWU){qRfPkxDosL = true;}
      else if(uXpjOAMzWU == uLNtEeOeCg){EZssMLBWPJ = true;}
      if(dooZJqfrOm == GUbKYtSJSS){QdJZduYRgC = true;}
      else if(GUbKYtSJSS == dooZJqfrOm){KPNtMmqUau = true;}
      if(mqaTGsqCHE == wwktVNGgeY){kamrikPPEF = true;}
      else if(wwktVNGgeY == mqaTGsqCHE){QcBtxwUlau = true;}
      if(DrHHRlMGLL == QzeDhOCJyd){jRklyFSrQT = true;}
      else if(QzeDhOCJyd == DrHHRlMGLL){JXQFgNBDCB = true;}
      if(nwtMAcGyIt == wpObHgpIZc){xfUYSxxUSo = true;}
      else if(wpObHgpIZc == nwtMAcGyIt){eLzMWKSRDz = true;}
      if(ZtCVKDjtmL == HPdQSymwOB){rDiUOQemfA = true;}
      if(mMWxclhhIX == sfTyDGoXbK){hnjnbyrXbY = true;}
      if(eZgDzpwOSc == qJLoWGhJlo){bgBMFFFOZl = true;}
      while(HPdQSymwOB == ZtCVKDjtmL){SaGCDbYyuQ = true;}
      while(sfTyDGoXbK == sfTyDGoXbK){qPwTzmzHMy = true;}
      while(qJLoWGhJlo == qJLoWGhJlo){kmRYPFcnXm = true;}
      if(WyHBQAUOki == true){WyHBQAUOki = false;}
      if(aGtwjQVQXA == true){aGtwjQVQXA = false;}
      if(qRfPkxDosL == true){qRfPkxDosL = false;}
      if(QdJZduYRgC == true){QdJZduYRgC = false;}
      if(kamrikPPEF == true){kamrikPPEF = false;}
      if(jRklyFSrQT == true){jRklyFSrQT = false;}
      if(xfUYSxxUSo == true){xfUYSxxUSo = false;}
      if(rDiUOQemfA == true){rDiUOQemfA = false;}
      if(hnjnbyrXbY == true){hnjnbyrXbY = false;}
      if(bgBMFFFOZl == true){bgBMFFFOZl = false;}
      if(mtxPNghPWg == true){mtxPNghPWg = false;}
      if(afLPlJugxU == true){afLPlJugxU = false;}
      if(EZssMLBWPJ == true){EZssMLBWPJ = false;}
      if(KPNtMmqUau == true){KPNtMmqUau = false;}
      if(QcBtxwUlau == true){QcBtxwUlau = false;}
      if(JXQFgNBDCB == true){JXQFgNBDCB = false;}
      if(eLzMWKSRDz == true){eLzMWKSRDz = false;}
      if(SaGCDbYyuQ == true){SaGCDbYyuQ = false;}
      if(qPwTzmzHMy == true){qPwTzmzHMy = false;}
      if(kmRYPFcnXm == true){kmRYPFcnXm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXUQDMWRFX
{ 
  void EXwAcyMVEU()
  { 
      bool MhsCsGbtiw = false;
      bool HTKsDbjTHr = false;
      bool YgihpQALQT = false;
      bool UTOMFfizgM = false;
      bool XYlqYmqTcj = false;
      bool AMRTceyKMb = false;
      bool GPcObmFymX = false;
      bool rjmuTAurJD = false;
      bool ZfigTHCtjZ = false;
      bool gYmEFIwWPk = false;
      bool gsfFrPZVAc = false;
      bool jFBJCZguuT = false;
      bool kLOMpSxhpL = false;
      bool EXbXVfAcoD = false;
      bool hftGpaXcCf = false;
      bool bAauAVeSOY = false;
      bool SrfnYMccmV = false;
      bool ZDGrlEQHWO = false;
      bool uUeKjDwgXA = false;
      bool BgNPjpAFhd = false;
      string NZMKoncbjs;
      string bgKCgfVhLE;
      string MXiiiJfYDj;
      string DmXKRUtffP;
      string KhQHRFcUGV;
      string eqdIropcaf;
      string HEXzonJAkM;
      string koCusdHbQd;
      string fLRhFMJPSb;
      string dREzIGJQRd;
      string ucisjoohON;
      string hNLxzulpsc;
      string dtgJhTkCmm;
      string UpKmhCbYxQ;
      string XbAFtPFHzM;
      string TTWnzBuZLQ;
      string EltarrDXOx;
      string TNrcFCsaOR;
      string NcCaSASVng;
      string GCMfLkgZMC;
      if(NZMKoncbjs == ucisjoohON){MhsCsGbtiw = true;}
      else if(ucisjoohON == NZMKoncbjs){gsfFrPZVAc = true;}
      if(bgKCgfVhLE == hNLxzulpsc){HTKsDbjTHr = true;}
      else if(hNLxzulpsc == bgKCgfVhLE){jFBJCZguuT = true;}
      if(MXiiiJfYDj == dtgJhTkCmm){YgihpQALQT = true;}
      else if(dtgJhTkCmm == MXiiiJfYDj){kLOMpSxhpL = true;}
      if(DmXKRUtffP == UpKmhCbYxQ){UTOMFfizgM = true;}
      else if(UpKmhCbYxQ == DmXKRUtffP){EXbXVfAcoD = true;}
      if(KhQHRFcUGV == XbAFtPFHzM){XYlqYmqTcj = true;}
      else if(XbAFtPFHzM == KhQHRFcUGV){hftGpaXcCf = true;}
      if(eqdIropcaf == TTWnzBuZLQ){AMRTceyKMb = true;}
      else if(TTWnzBuZLQ == eqdIropcaf){bAauAVeSOY = true;}
      if(HEXzonJAkM == EltarrDXOx){GPcObmFymX = true;}
      else if(EltarrDXOx == HEXzonJAkM){SrfnYMccmV = true;}
      if(koCusdHbQd == TNrcFCsaOR){rjmuTAurJD = true;}
      if(fLRhFMJPSb == NcCaSASVng){ZfigTHCtjZ = true;}
      if(dREzIGJQRd == GCMfLkgZMC){gYmEFIwWPk = true;}
      while(TNrcFCsaOR == koCusdHbQd){ZDGrlEQHWO = true;}
      while(NcCaSASVng == NcCaSASVng){uUeKjDwgXA = true;}
      while(GCMfLkgZMC == GCMfLkgZMC){BgNPjpAFhd = true;}
      if(MhsCsGbtiw == true){MhsCsGbtiw = false;}
      if(HTKsDbjTHr == true){HTKsDbjTHr = false;}
      if(YgihpQALQT == true){YgihpQALQT = false;}
      if(UTOMFfizgM == true){UTOMFfizgM = false;}
      if(XYlqYmqTcj == true){XYlqYmqTcj = false;}
      if(AMRTceyKMb == true){AMRTceyKMb = false;}
      if(GPcObmFymX == true){GPcObmFymX = false;}
      if(rjmuTAurJD == true){rjmuTAurJD = false;}
      if(ZfigTHCtjZ == true){ZfigTHCtjZ = false;}
      if(gYmEFIwWPk == true){gYmEFIwWPk = false;}
      if(gsfFrPZVAc == true){gsfFrPZVAc = false;}
      if(jFBJCZguuT == true){jFBJCZguuT = false;}
      if(kLOMpSxhpL == true){kLOMpSxhpL = false;}
      if(EXbXVfAcoD == true){EXbXVfAcoD = false;}
      if(hftGpaXcCf == true){hftGpaXcCf = false;}
      if(bAauAVeSOY == true){bAauAVeSOY = false;}
      if(SrfnYMccmV == true){SrfnYMccmV = false;}
      if(ZDGrlEQHWO == true){ZDGrlEQHWO = false;}
      if(uUeKjDwgXA == true){uUeKjDwgXA = false;}
      if(BgNPjpAFhd == true){BgNPjpAFhd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXPHODBNCC
{ 
  void fIhFeggAiL()
  { 
      bool FKMJeKoOdb = false;
      bool YIMxzlQlaq = false;
      bool UWjjTzRiYC = false;
      bool AaaYoKXcEc = false;
      bool cqJelDJHkO = false;
      bool NtdRWiZcpe = false;
      bool sGoaaxgnHn = false;
      bool NngyOdNFxP = false;
      bool pKxKoFxICG = false;
      bool kulYiWBhDn = false;
      bool WVzwAYMeDr = false;
      bool UUeZoiIelU = false;
      bool AXkBDSBHPq = false;
      bool beCJsTKBKP = false;
      bool sRFJkPQLjA = false;
      bool OWwhnyjysg = false;
      bool XFPLQpSUgV = false;
      bool XGUVbhSbPm = false;
      bool CpXOcFhTVt = false;
      bool iLHcrmCssu = false;
      string ELBUCsCjye;
      string TMKSlxRVZl;
      string IBenjNFjQO;
      string AbHzrDTEQO;
      string RAVGhMJokU;
      string bkSDsCgMjo;
      string nRTjeqFKah;
      string dMELTHfYGX;
      string DPzumOIDFp;
      string WHTbZzgkaq;
      string HyOCqPfHik;
      string VHGMkXSXxP;
      string hBFjKVrclU;
      string atxPQFBwEX;
      string hBUTTPBHpC;
      string gInKIFsdrU;
      string WDVOKbJquf;
      string WVTZgggkQu;
      string UjlimSGmGK;
      string LWEjAefFJr;
      if(ELBUCsCjye == HyOCqPfHik){FKMJeKoOdb = true;}
      else if(HyOCqPfHik == ELBUCsCjye){WVzwAYMeDr = true;}
      if(TMKSlxRVZl == VHGMkXSXxP){YIMxzlQlaq = true;}
      else if(VHGMkXSXxP == TMKSlxRVZl){UUeZoiIelU = true;}
      if(IBenjNFjQO == hBFjKVrclU){UWjjTzRiYC = true;}
      else if(hBFjKVrclU == IBenjNFjQO){AXkBDSBHPq = true;}
      if(AbHzrDTEQO == atxPQFBwEX){AaaYoKXcEc = true;}
      else if(atxPQFBwEX == AbHzrDTEQO){beCJsTKBKP = true;}
      if(RAVGhMJokU == hBUTTPBHpC){cqJelDJHkO = true;}
      else if(hBUTTPBHpC == RAVGhMJokU){sRFJkPQLjA = true;}
      if(bkSDsCgMjo == gInKIFsdrU){NtdRWiZcpe = true;}
      else if(gInKIFsdrU == bkSDsCgMjo){OWwhnyjysg = true;}
      if(nRTjeqFKah == WDVOKbJquf){sGoaaxgnHn = true;}
      else if(WDVOKbJquf == nRTjeqFKah){XFPLQpSUgV = true;}
      if(dMELTHfYGX == WVTZgggkQu){NngyOdNFxP = true;}
      if(DPzumOIDFp == UjlimSGmGK){pKxKoFxICG = true;}
      if(WHTbZzgkaq == LWEjAefFJr){kulYiWBhDn = true;}
      while(WVTZgggkQu == dMELTHfYGX){XGUVbhSbPm = true;}
      while(UjlimSGmGK == UjlimSGmGK){CpXOcFhTVt = true;}
      while(LWEjAefFJr == LWEjAefFJr){iLHcrmCssu = true;}
      if(FKMJeKoOdb == true){FKMJeKoOdb = false;}
      if(YIMxzlQlaq == true){YIMxzlQlaq = false;}
      if(UWjjTzRiYC == true){UWjjTzRiYC = false;}
      if(AaaYoKXcEc == true){AaaYoKXcEc = false;}
      if(cqJelDJHkO == true){cqJelDJHkO = false;}
      if(NtdRWiZcpe == true){NtdRWiZcpe = false;}
      if(sGoaaxgnHn == true){sGoaaxgnHn = false;}
      if(NngyOdNFxP == true){NngyOdNFxP = false;}
      if(pKxKoFxICG == true){pKxKoFxICG = false;}
      if(kulYiWBhDn == true){kulYiWBhDn = false;}
      if(WVzwAYMeDr == true){WVzwAYMeDr = false;}
      if(UUeZoiIelU == true){UUeZoiIelU = false;}
      if(AXkBDSBHPq == true){AXkBDSBHPq = false;}
      if(beCJsTKBKP == true){beCJsTKBKP = false;}
      if(sRFJkPQLjA == true){sRFJkPQLjA = false;}
      if(OWwhnyjysg == true){OWwhnyjysg = false;}
      if(XFPLQpSUgV == true){XFPLQpSUgV = false;}
      if(XGUVbhSbPm == true){XGUVbhSbPm = false;}
      if(CpXOcFhTVt == true){CpXOcFhTVt = false;}
      if(iLHcrmCssu == true){iLHcrmCssu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LQNLIKNTBZ
{ 
  void BnrLUgorKT()
  { 
      bool VidELHjqRc = false;
      bool MGsbWIUrnM = false;
      bool ZjLSsSMHZs = false;
      bool owggZFetOe = false;
      bool IOzuIXHdXy = false;
      bool ytcZwkXLLr = false;
      bool ucQYmPYMBQ = false;
      bool cadIELkPJV = false;
      bool LhibtuTHjo = false;
      bool gTiVifyZIs = false;
      bool ytcGUXQTVk = false;
      bool AIBpgMtodr = false;
      bool wRcMjJrHZX = false;
      bool NKGQWQFcGW = false;
      bool dzlznYRsnW = false;
      bool lIuQwgRQWL = false;
      bool fItxXpBkSQ = false;
      bool GRhHNwedXK = false;
      bool qzTClEOpTp = false;
      bool yoFupVEoay = false;
      string cTtADFRPDF;
      string RnpGfBgObX;
      string DJuOrehAhg;
      string SGDujsMHeW;
      string nbATxQjceI;
      string QfcXNTYeIY;
      string XQgVmKkuWm;
      string oYiEjaIbQa;
      string tEUZQlcfgP;
      string TgzGzWtdfm;
      string foFqTrxXnm;
      string LxNhdSwHFB;
      string gFNHTHZbFM;
      string feuduFzdGY;
      string nFqsDWSQcf;
      string ZlXeFZaxXL;
      string RUSaGgBjmX;
      string TSBgMbNTDw;
      string nIzZmsGQYU;
      string dBFtGTlQmW;
      if(cTtADFRPDF == foFqTrxXnm){VidELHjqRc = true;}
      else if(foFqTrxXnm == cTtADFRPDF){ytcGUXQTVk = true;}
      if(RnpGfBgObX == LxNhdSwHFB){MGsbWIUrnM = true;}
      else if(LxNhdSwHFB == RnpGfBgObX){AIBpgMtodr = true;}
      if(DJuOrehAhg == gFNHTHZbFM){ZjLSsSMHZs = true;}
      else if(gFNHTHZbFM == DJuOrehAhg){wRcMjJrHZX = true;}
      if(SGDujsMHeW == feuduFzdGY){owggZFetOe = true;}
      else if(feuduFzdGY == SGDujsMHeW){NKGQWQFcGW = true;}
      if(nbATxQjceI == nFqsDWSQcf){IOzuIXHdXy = true;}
      else if(nFqsDWSQcf == nbATxQjceI){dzlznYRsnW = true;}
      if(QfcXNTYeIY == ZlXeFZaxXL){ytcZwkXLLr = true;}
      else if(ZlXeFZaxXL == QfcXNTYeIY){lIuQwgRQWL = true;}
      if(XQgVmKkuWm == RUSaGgBjmX){ucQYmPYMBQ = true;}
      else if(RUSaGgBjmX == XQgVmKkuWm){fItxXpBkSQ = true;}
      if(oYiEjaIbQa == TSBgMbNTDw){cadIELkPJV = true;}
      if(tEUZQlcfgP == nIzZmsGQYU){LhibtuTHjo = true;}
      if(TgzGzWtdfm == dBFtGTlQmW){gTiVifyZIs = true;}
      while(TSBgMbNTDw == oYiEjaIbQa){GRhHNwedXK = true;}
      while(nIzZmsGQYU == nIzZmsGQYU){qzTClEOpTp = true;}
      while(dBFtGTlQmW == dBFtGTlQmW){yoFupVEoay = true;}
      if(VidELHjqRc == true){VidELHjqRc = false;}
      if(MGsbWIUrnM == true){MGsbWIUrnM = false;}
      if(ZjLSsSMHZs == true){ZjLSsSMHZs = false;}
      if(owggZFetOe == true){owggZFetOe = false;}
      if(IOzuIXHdXy == true){IOzuIXHdXy = false;}
      if(ytcZwkXLLr == true){ytcZwkXLLr = false;}
      if(ucQYmPYMBQ == true){ucQYmPYMBQ = false;}
      if(cadIELkPJV == true){cadIELkPJV = false;}
      if(LhibtuTHjo == true){LhibtuTHjo = false;}
      if(gTiVifyZIs == true){gTiVifyZIs = false;}
      if(ytcGUXQTVk == true){ytcGUXQTVk = false;}
      if(AIBpgMtodr == true){AIBpgMtodr = false;}
      if(wRcMjJrHZX == true){wRcMjJrHZX = false;}
      if(NKGQWQFcGW == true){NKGQWQFcGW = false;}
      if(dzlznYRsnW == true){dzlznYRsnW = false;}
      if(lIuQwgRQWL == true){lIuQwgRQWL = false;}
      if(fItxXpBkSQ == true){fItxXpBkSQ = false;}
      if(GRhHNwedXK == true){GRhHNwedXK = false;}
      if(qzTClEOpTp == true){qzTClEOpTp = false;}
      if(yoFupVEoay == true){yoFupVEoay = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVPNMRGJSC
{ 
  void NwaxoffneE()
  { 
      bool USYFZnjAjY = false;
      bool ShpBIbOfLk = false;
      bool mHpoBzqUYZ = false;
      bool LtouPzPotf = false;
      bool RsmhPYiTbw = false;
      bool XuBEhMbjDa = false;
      bool wPaJMXsukJ = false;
      bool MYleTsTIYc = false;
      bool PWrcCQsjMC = false;
      bool WekSiBRdUq = false;
      bool fnhRjyIVkn = false;
      bool rSLaKZWyHw = false;
      bool eIhilgnSuS = false;
      bool bpmhwbnarD = false;
      bool HWzXJETJIJ = false;
      bool eTWYLWFzfC = false;
      bool JpZSMCfcdh = false;
      bool kwFDnHIJYh = false;
      bool NdKlmHTNVZ = false;
      bool VoupsRxgLH = false;
      string EPwTNtbepG;
      string FaJdDEHYsC;
      string uytkDmegrJ;
      string kqhohTqsUT;
      string OuSXpTrWEW;
      string QWtofFUKPZ;
      string OumfVNsTui;
      string NODYnAeVui;
      string tIbUrNxsJb;
      string zfctFTImCb;
      string aYaVICSUAe;
      string ZyPfeGSRnH;
      string QAJTjhkJTU;
      string rrSSIVgGLp;
      string ucrdCAPwOz;
      string ApyuLZOHka;
      string QJBfmgexWJ;
      string YMFyLmHfQj;
      string RotUTBtXGh;
      string HZUkYlbMpV;
      if(EPwTNtbepG == aYaVICSUAe){USYFZnjAjY = true;}
      else if(aYaVICSUAe == EPwTNtbepG){fnhRjyIVkn = true;}
      if(FaJdDEHYsC == ZyPfeGSRnH){ShpBIbOfLk = true;}
      else if(ZyPfeGSRnH == FaJdDEHYsC){rSLaKZWyHw = true;}
      if(uytkDmegrJ == QAJTjhkJTU){mHpoBzqUYZ = true;}
      else if(QAJTjhkJTU == uytkDmegrJ){eIhilgnSuS = true;}
      if(kqhohTqsUT == rrSSIVgGLp){LtouPzPotf = true;}
      else if(rrSSIVgGLp == kqhohTqsUT){bpmhwbnarD = true;}
      if(OuSXpTrWEW == ucrdCAPwOz){RsmhPYiTbw = true;}
      else if(ucrdCAPwOz == OuSXpTrWEW){HWzXJETJIJ = true;}
      if(QWtofFUKPZ == ApyuLZOHka){XuBEhMbjDa = true;}
      else if(ApyuLZOHka == QWtofFUKPZ){eTWYLWFzfC = true;}
      if(OumfVNsTui == QJBfmgexWJ){wPaJMXsukJ = true;}
      else if(QJBfmgexWJ == OumfVNsTui){JpZSMCfcdh = true;}
      if(NODYnAeVui == YMFyLmHfQj){MYleTsTIYc = true;}
      if(tIbUrNxsJb == RotUTBtXGh){PWrcCQsjMC = true;}
      if(zfctFTImCb == HZUkYlbMpV){WekSiBRdUq = true;}
      while(YMFyLmHfQj == NODYnAeVui){kwFDnHIJYh = true;}
      while(RotUTBtXGh == RotUTBtXGh){NdKlmHTNVZ = true;}
      while(HZUkYlbMpV == HZUkYlbMpV){VoupsRxgLH = true;}
      if(USYFZnjAjY == true){USYFZnjAjY = false;}
      if(ShpBIbOfLk == true){ShpBIbOfLk = false;}
      if(mHpoBzqUYZ == true){mHpoBzqUYZ = false;}
      if(LtouPzPotf == true){LtouPzPotf = false;}
      if(RsmhPYiTbw == true){RsmhPYiTbw = false;}
      if(XuBEhMbjDa == true){XuBEhMbjDa = false;}
      if(wPaJMXsukJ == true){wPaJMXsukJ = false;}
      if(MYleTsTIYc == true){MYleTsTIYc = false;}
      if(PWrcCQsjMC == true){PWrcCQsjMC = false;}
      if(WekSiBRdUq == true){WekSiBRdUq = false;}
      if(fnhRjyIVkn == true){fnhRjyIVkn = false;}
      if(rSLaKZWyHw == true){rSLaKZWyHw = false;}
      if(eIhilgnSuS == true){eIhilgnSuS = false;}
      if(bpmhwbnarD == true){bpmhwbnarD = false;}
      if(HWzXJETJIJ == true){HWzXJETJIJ = false;}
      if(eTWYLWFzfC == true){eTWYLWFzfC = false;}
      if(JpZSMCfcdh == true){JpZSMCfcdh = false;}
      if(kwFDnHIJYh == true){kwFDnHIJYh = false;}
      if(NdKlmHTNVZ == true){NdKlmHTNVZ = false;}
      if(VoupsRxgLH == true){VoupsRxgLH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DILURWSKFJ
{ 
  void NxLeYDXaMI()
  { 
      bool qTJwaFwMQo = false;
      bool rsGhdQywye = false;
      bool GTINZrfldb = false;
      bool LSXwmagwEN = false;
      bool cPkxjbzkrm = false;
      bool HhueZWLwVi = false;
      bool YJhncYVKtD = false;
      bool iBrkCphKcy = false;
      bool rutpTdWrVQ = false;
      bool PkZUnShwTK = false;
      bool FoqoEFoKci = false;
      bool oASXqdPqUz = false;
      bool CdocmybXwi = false;
      bool IkqRsDDElN = false;
      bool nLPlaPRBdJ = false;
      bool DpbUIbANCF = false;
      bool cRNsaDJAen = false;
      bool ZLEGKpOCBX = false;
      bool gZtmfRIVJQ = false;
      bool DpCgjWyVLX = false;
      string izVpLdZkaS;
      string dSPQEYNXwC;
      string iLCLKtSMAU;
      string SqtUxelBCa;
      string wtwbPBVycV;
      string KwDtWXwJfQ;
      string KNjFAlXuTZ;
      string lLUVGnOawJ;
      string XUieKWnAxZ;
      string hcVkPiKpad;
      string cZdDiyagnh;
      string IVNVspdFuc;
      string xXxtqJpjFW;
      string dYzSgxqewL;
      string wGLOQMOzrZ;
      string EFuxfEbjMY;
      string HpbQEjVuou;
      string yyIigpMice;
      string uqreSYcClb;
      string UGSWEFetKg;
      if(izVpLdZkaS == cZdDiyagnh){qTJwaFwMQo = true;}
      else if(cZdDiyagnh == izVpLdZkaS){FoqoEFoKci = true;}
      if(dSPQEYNXwC == IVNVspdFuc){rsGhdQywye = true;}
      else if(IVNVspdFuc == dSPQEYNXwC){oASXqdPqUz = true;}
      if(iLCLKtSMAU == xXxtqJpjFW){GTINZrfldb = true;}
      else if(xXxtqJpjFW == iLCLKtSMAU){CdocmybXwi = true;}
      if(SqtUxelBCa == dYzSgxqewL){LSXwmagwEN = true;}
      else if(dYzSgxqewL == SqtUxelBCa){IkqRsDDElN = true;}
      if(wtwbPBVycV == wGLOQMOzrZ){cPkxjbzkrm = true;}
      else if(wGLOQMOzrZ == wtwbPBVycV){nLPlaPRBdJ = true;}
      if(KwDtWXwJfQ == EFuxfEbjMY){HhueZWLwVi = true;}
      else if(EFuxfEbjMY == KwDtWXwJfQ){DpbUIbANCF = true;}
      if(KNjFAlXuTZ == HpbQEjVuou){YJhncYVKtD = true;}
      else if(HpbQEjVuou == KNjFAlXuTZ){cRNsaDJAen = true;}
      if(lLUVGnOawJ == yyIigpMice){iBrkCphKcy = true;}
      if(XUieKWnAxZ == uqreSYcClb){rutpTdWrVQ = true;}
      if(hcVkPiKpad == UGSWEFetKg){PkZUnShwTK = true;}
      while(yyIigpMice == lLUVGnOawJ){ZLEGKpOCBX = true;}
      while(uqreSYcClb == uqreSYcClb){gZtmfRIVJQ = true;}
      while(UGSWEFetKg == UGSWEFetKg){DpCgjWyVLX = true;}
      if(qTJwaFwMQo == true){qTJwaFwMQo = false;}
      if(rsGhdQywye == true){rsGhdQywye = false;}
      if(GTINZrfldb == true){GTINZrfldb = false;}
      if(LSXwmagwEN == true){LSXwmagwEN = false;}
      if(cPkxjbzkrm == true){cPkxjbzkrm = false;}
      if(HhueZWLwVi == true){HhueZWLwVi = false;}
      if(YJhncYVKtD == true){YJhncYVKtD = false;}
      if(iBrkCphKcy == true){iBrkCphKcy = false;}
      if(rutpTdWrVQ == true){rutpTdWrVQ = false;}
      if(PkZUnShwTK == true){PkZUnShwTK = false;}
      if(FoqoEFoKci == true){FoqoEFoKci = false;}
      if(oASXqdPqUz == true){oASXqdPqUz = false;}
      if(CdocmybXwi == true){CdocmybXwi = false;}
      if(IkqRsDDElN == true){IkqRsDDElN = false;}
      if(nLPlaPRBdJ == true){nLPlaPRBdJ = false;}
      if(DpbUIbANCF == true){DpbUIbANCF = false;}
      if(cRNsaDJAen == true){cRNsaDJAen = false;}
      if(ZLEGKpOCBX == true){ZLEGKpOCBX = false;}
      if(gZtmfRIVJQ == true){gZtmfRIVJQ = false;}
      if(DpCgjWyVLX == true){DpCgjWyVLX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJRDTAXEUH
{ 
  void kLKlkCagwz()
  { 
      bool bPKctsYIgY = false;
      bool ICRzquwojB = false;
      bool VnrEalEZkN = false;
      bool igSduwwmQN = false;
      bool rKPkmCISQB = false;
      bool AzcfInWFCI = false;
      bool oyXSpajmEu = false;
      bool zJXVILXHRY = false;
      bool ckIjNiElVG = false;
      bool YpkIYsmxtL = false;
      bool SVOUBqaGXx = false;
      bool PPndeDpmFH = false;
      bool WxRxVIXOxO = false;
      bool YaMFFHWmhV = false;
      bool IxOYqJBHdU = false;
      bool DzqmoUEQyr = false;
      bool SLJIYoDiXX = false;
      bool gCEiyZirGM = false;
      bool HQkcLYiYPk = false;
      bool DFnoDwmGzB = false;
      string eNZOyYrPEd;
      string oHnxsMdUat;
      string EyjySAGgfI;
      string KRnAASFEwm;
      string piRggTpBhn;
      string qMHTLfdbwy;
      string SLjuTWSnxZ;
      string HYYmDVfCRy;
      string JEyqQyJUoT;
      string ocHyUeyVNJ;
      string ACDIgSnTPo;
      string zaKxnNNreU;
      string MyzckdQZSY;
      string WKoHxHApKx;
      string KoEzTNSKJG;
      string QGprwCCaWC;
      string BNBqRokDzf;
      string MXhhKWtzIW;
      string LGQLHQTxKu;
      string FZSHwxnMge;
      if(eNZOyYrPEd == ACDIgSnTPo){bPKctsYIgY = true;}
      else if(ACDIgSnTPo == eNZOyYrPEd){SVOUBqaGXx = true;}
      if(oHnxsMdUat == zaKxnNNreU){ICRzquwojB = true;}
      else if(zaKxnNNreU == oHnxsMdUat){PPndeDpmFH = true;}
      if(EyjySAGgfI == MyzckdQZSY){VnrEalEZkN = true;}
      else if(MyzckdQZSY == EyjySAGgfI){WxRxVIXOxO = true;}
      if(KRnAASFEwm == WKoHxHApKx){igSduwwmQN = true;}
      else if(WKoHxHApKx == KRnAASFEwm){YaMFFHWmhV = true;}
      if(piRggTpBhn == KoEzTNSKJG){rKPkmCISQB = true;}
      else if(KoEzTNSKJG == piRggTpBhn){IxOYqJBHdU = true;}
      if(qMHTLfdbwy == QGprwCCaWC){AzcfInWFCI = true;}
      else if(QGprwCCaWC == qMHTLfdbwy){DzqmoUEQyr = true;}
      if(SLjuTWSnxZ == BNBqRokDzf){oyXSpajmEu = true;}
      else if(BNBqRokDzf == SLjuTWSnxZ){SLJIYoDiXX = true;}
      if(HYYmDVfCRy == MXhhKWtzIW){zJXVILXHRY = true;}
      if(JEyqQyJUoT == LGQLHQTxKu){ckIjNiElVG = true;}
      if(ocHyUeyVNJ == FZSHwxnMge){YpkIYsmxtL = true;}
      while(MXhhKWtzIW == HYYmDVfCRy){gCEiyZirGM = true;}
      while(LGQLHQTxKu == LGQLHQTxKu){HQkcLYiYPk = true;}
      while(FZSHwxnMge == FZSHwxnMge){DFnoDwmGzB = true;}
      if(bPKctsYIgY == true){bPKctsYIgY = false;}
      if(ICRzquwojB == true){ICRzquwojB = false;}
      if(VnrEalEZkN == true){VnrEalEZkN = false;}
      if(igSduwwmQN == true){igSduwwmQN = false;}
      if(rKPkmCISQB == true){rKPkmCISQB = false;}
      if(AzcfInWFCI == true){AzcfInWFCI = false;}
      if(oyXSpajmEu == true){oyXSpajmEu = false;}
      if(zJXVILXHRY == true){zJXVILXHRY = false;}
      if(ckIjNiElVG == true){ckIjNiElVG = false;}
      if(YpkIYsmxtL == true){YpkIYsmxtL = false;}
      if(SVOUBqaGXx == true){SVOUBqaGXx = false;}
      if(PPndeDpmFH == true){PPndeDpmFH = false;}
      if(WxRxVIXOxO == true){WxRxVIXOxO = false;}
      if(YaMFFHWmhV == true){YaMFFHWmhV = false;}
      if(IxOYqJBHdU == true){IxOYqJBHdU = false;}
      if(DzqmoUEQyr == true){DzqmoUEQyr = false;}
      if(SLJIYoDiXX == true){SLJIYoDiXX = false;}
      if(gCEiyZirGM == true){gCEiyZirGM = false;}
      if(HQkcLYiYPk == true){HQkcLYiYPk = false;}
      if(DFnoDwmGzB == true){DFnoDwmGzB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QASWTAAWQS
{ 
  void gjUDcxakGM()
  { 
      bool FbQVQPhXEo = false;
      bool eVapnYSQYP = false;
      bool XaiWuAjQpd = false;
      bool kJVdGndCmP = false;
      bool YfMJugyGeZ = false;
      bool YNImMersaQ = false;
      bool eRhZDVAxiz = false;
      bool tPdIprOZaN = false;
      bool CdkQFXAhQb = false;
      bool wjbVjHylFZ = false;
      bool gAXfeIjzxU = false;
      bool PRSMOBfQUf = false;
      bool USfGDJnHXi = false;
      bool tbUBgBGFkw = false;
      bool nBjwLdRPHi = false;
      bool agRYEOTQbU = false;
      bool UbaOZnwQeN = false;
      bool uZeXrThjuY = false;
      bool rXAoHMJwwS = false;
      bool gocQaLZVVX = false;
      string eeZAAORFtp;
      string gJpVdWeWdj;
      string gCZRCJoVys;
      string RDKTklCJJE;
      string bgSDwBQFGy;
      string zyoowcEHxp;
      string YwHAYczWkr;
      string UVMZHziVVA;
      string sjOAtTOUWH;
      string guLSeeZSeS;
      string CtTOcckPhx;
      string sikwxohGFE;
      string OezdKZJttc;
      string ZQqDyyPAWR;
      string izmZNyJOUp;
      string xSMZEWupDD;
      string TqUEWcrhyz;
      string YgjnVPqYPM;
      string PuYDfHEQya;
      string DYxSyqdhDk;
      if(eeZAAORFtp == CtTOcckPhx){FbQVQPhXEo = true;}
      else if(CtTOcckPhx == eeZAAORFtp){gAXfeIjzxU = true;}
      if(gJpVdWeWdj == sikwxohGFE){eVapnYSQYP = true;}
      else if(sikwxohGFE == gJpVdWeWdj){PRSMOBfQUf = true;}
      if(gCZRCJoVys == OezdKZJttc){XaiWuAjQpd = true;}
      else if(OezdKZJttc == gCZRCJoVys){USfGDJnHXi = true;}
      if(RDKTklCJJE == ZQqDyyPAWR){kJVdGndCmP = true;}
      else if(ZQqDyyPAWR == RDKTklCJJE){tbUBgBGFkw = true;}
      if(bgSDwBQFGy == izmZNyJOUp){YfMJugyGeZ = true;}
      else if(izmZNyJOUp == bgSDwBQFGy){nBjwLdRPHi = true;}
      if(zyoowcEHxp == xSMZEWupDD){YNImMersaQ = true;}
      else if(xSMZEWupDD == zyoowcEHxp){agRYEOTQbU = true;}
      if(YwHAYczWkr == TqUEWcrhyz){eRhZDVAxiz = true;}
      else if(TqUEWcrhyz == YwHAYczWkr){UbaOZnwQeN = true;}
      if(UVMZHziVVA == YgjnVPqYPM){tPdIprOZaN = true;}
      if(sjOAtTOUWH == PuYDfHEQya){CdkQFXAhQb = true;}
      if(guLSeeZSeS == DYxSyqdhDk){wjbVjHylFZ = true;}
      while(YgjnVPqYPM == UVMZHziVVA){uZeXrThjuY = true;}
      while(PuYDfHEQya == PuYDfHEQya){rXAoHMJwwS = true;}
      while(DYxSyqdhDk == DYxSyqdhDk){gocQaLZVVX = true;}
      if(FbQVQPhXEo == true){FbQVQPhXEo = false;}
      if(eVapnYSQYP == true){eVapnYSQYP = false;}
      if(XaiWuAjQpd == true){XaiWuAjQpd = false;}
      if(kJVdGndCmP == true){kJVdGndCmP = false;}
      if(YfMJugyGeZ == true){YfMJugyGeZ = false;}
      if(YNImMersaQ == true){YNImMersaQ = false;}
      if(eRhZDVAxiz == true){eRhZDVAxiz = false;}
      if(tPdIprOZaN == true){tPdIprOZaN = false;}
      if(CdkQFXAhQb == true){CdkQFXAhQb = false;}
      if(wjbVjHylFZ == true){wjbVjHylFZ = false;}
      if(gAXfeIjzxU == true){gAXfeIjzxU = false;}
      if(PRSMOBfQUf == true){PRSMOBfQUf = false;}
      if(USfGDJnHXi == true){USfGDJnHXi = false;}
      if(tbUBgBGFkw == true){tbUBgBGFkw = false;}
      if(nBjwLdRPHi == true){nBjwLdRPHi = false;}
      if(agRYEOTQbU == true){agRYEOTQbU = false;}
      if(UbaOZnwQeN == true){UbaOZnwQeN = false;}
      if(uZeXrThjuY == true){uZeXrThjuY = false;}
      if(rXAoHMJwwS == true){rXAoHMJwwS = false;}
      if(gocQaLZVVX == true){gocQaLZVVX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQBPCJCWKJ
{ 
  void wkNpCbBSWx()
  { 
      bool arImZsBwih = false;
      bool ruUrQDFBYX = false;
      bool ldMxTXTufg = false;
      bool cpzTlVoweq = false;
      bool RLEjeKQgDE = false;
      bool bbCUbxeLSB = false;
      bool ZGPCEBwBFt = false;
      bool OIVhGaZcRI = false;
      bool HmrbEBmdqo = false;
      bool qcdcRLuBec = false;
      bool OOaIoSFUOB = false;
      bool WCsJtlNnxD = false;
      bool ORJPDkesQt = false;
      bool fXxotrLill = false;
      bool uSPpRnjThe = false;
      bool xGEbOxFLFD = false;
      bool mLETVzEDPC = false;
      bool aeCLHwBTxO = false;
      bool BLKkxYSVaw = false;
      bool mAchyiOwUS = false;
      string XPBYyJcLKU;
      string MHuJWXfwmO;
      string cDsgdRZKeW;
      string bskFRScZPR;
      string dMYaxiGnRN;
      string iSPRrTVUuf;
      string jRgmsTVpqE;
      string uFfUjQeSjt;
      string LlsRnIdSMy;
      string wIeigMfkgd;
      string MQwNRcltgb;
      string nDkBUyYOzj;
      string pDcrHlaxnX;
      string jskFgtoezK;
      string VikkJsXcNi;
      string mQkxnJnDGe;
      string BoGJqtReUa;
      string JsPoNGRriN;
      string OxiEjTHnRW;
      string GkYTIgcbsO;
      if(XPBYyJcLKU == MQwNRcltgb){arImZsBwih = true;}
      else if(MQwNRcltgb == XPBYyJcLKU){OOaIoSFUOB = true;}
      if(MHuJWXfwmO == nDkBUyYOzj){ruUrQDFBYX = true;}
      else if(nDkBUyYOzj == MHuJWXfwmO){WCsJtlNnxD = true;}
      if(cDsgdRZKeW == pDcrHlaxnX){ldMxTXTufg = true;}
      else if(pDcrHlaxnX == cDsgdRZKeW){ORJPDkesQt = true;}
      if(bskFRScZPR == jskFgtoezK){cpzTlVoweq = true;}
      else if(jskFgtoezK == bskFRScZPR){fXxotrLill = true;}
      if(dMYaxiGnRN == VikkJsXcNi){RLEjeKQgDE = true;}
      else if(VikkJsXcNi == dMYaxiGnRN){uSPpRnjThe = true;}
      if(iSPRrTVUuf == mQkxnJnDGe){bbCUbxeLSB = true;}
      else if(mQkxnJnDGe == iSPRrTVUuf){xGEbOxFLFD = true;}
      if(jRgmsTVpqE == BoGJqtReUa){ZGPCEBwBFt = true;}
      else if(BoGJqtReUa == jRgmsTVpqE){mLETVzEDPC = true;}
      if(uFfUjQeSjt == JsPoNGRriN){OIVhGaZcRI = true;}
      if(LlsRnIdSMy == OxiEjTHnRW){HmrbEBmdqo = true;}
      if(wIeigMfkgd == GkYTIgcbsO){qcdcRLuBec = true;}
      while(JsPoNGRriN == uFfUjQeSjt){aeCLHwBTxO = true;}
      while(OxiEjTHnRW == OxiEjTHnRW){BLKkxYSVaw = true;}
      while(GkYTIgcbsO == GkYTIgcbsO){mAchyiOwUS = true;}
      if(arImZsBwih == true){arImZsBwih = false;}
      if(ruUrQDFBYX == true){ruUrQDFBYX = false;}
      if(ldMxTXTufg == true){ldMxTXTufg = false;}
      if(cpzTlVoweq == true){cpzTlVoweq = false;}
      if(RLEjeKQgDE == true){RLEjeKQgDE = false;}
      if(bbCUbxeLSB == true){bbCUbxeLSB = false;}
      if(ZGPCEBwBFt == true){ZGPCEBwBFt = false;}
      if(OIVhGaZcRI == true){OIVhGaZcRI = false;}
      if(HmrbEBmdqo == true){HmrbEBmdqo = false;}
      if(qcdcRLuBec == true){qcdcRLuBec = false;}
      if(OOaIoSFUOB == true){OOaIoSFUOB = false;}
      if(WCsJtlNnxD == true){WCsJtlNnxD = false;}
      if(ORJPDkesQt == true){ORJPDkesQt = false;}
      if(fXxotrLill == true){fXxotrLill = false;}
      if(uSPpRnjThe == true){uSPpRnjThe = false;}
      if(xGEbOxFLFD == true){xGEbOxFLFD = false;}
      if(mLETVzEDPC == true){mLETVzEDPC = false;}
      if(aeCLHwBTxO == true){aeCLHwBTxO = false;}
      if(BLKkxYSVaw == true){BLKkxYSVaw = false;}
      if(mAchyiOwUS == true){mAchyiOwUS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSLTRGRYBX
{ 
  void sjrUddDrDP()
  { 
      bool WLQQFpTNHa = false;
      bool xnGKCNDZXt = false;
      bool gXeuXEnTZC = false;
      bool sqwacNzcyL = false;
      bool qlFnljMfft = false;
      bool HzpCPygUrB = false;
      bool BAmEgFqehn = false;
      bool OaaLDuSqJn = false;
      bool qImfutBtKe = false;
      bool gdjxKpyBHf = false;
      bool shyqffXdyT = false;
      bool foKEKsMHJm = false;
      bool ExTCGjqdBM = false;
      bool xRjduJJwAO = false;
      bool VXuqzqSfmR = false;
      bool dpqTbuNuju = false;
      bool otblWNFgJA = false;
      bool iQHuQgCcDP = false;
      bool QKqjiGZPBz = false;
      bool wOLEYauIUk = false;
      string xBCMcSdrdZ;
      string usVuGXhWfi;
      string WOGaNsSZOk;
      string nILmnWjLzz;
      string HKGeCeLnDw;
      string LarYyiuazj;
      string AEcrklgiHj;
      string nWWgaMHbYi;
      string heVRZNPmnF;
      string bILPyDgNsP;
      string xbgTHnELyl;
      string aTCQCVhLSX;
      string WtuCIfLGhX;
      string fthIkFxCJk;
      string JDoCdHFuNc;
      string UUuVsCgdLb;
      string cxdaFgktew;
      string XeBhOSFsXA;
      string ZPsECKzMOi;
      string XTqhHLYOwx;
      if(xBCMcSdrdZ == xbgTHnELyl){WLQQFpTNHa = true;}
      else if(xbgTHnELyl == xBCMcSdrdZ){shyqffXdyT = true;}
      if(usVuGXhWfi == aTCQCVhLSX){xnGKCNDZXt = true;}
      else if(aTCQCVhLSX == usVuGXhWfi){foKEKsMHJm = true;}
      if(WOGaNsSZOk == WtuCIfLGhX){gXeuXEnTZC = true;}
      else if(WtuCIfLGhX == WOGaNsSZOk){ExTCGjqdBM = true;}
      if(nILmnWjLzz == fthIkFxCJk){sqwacNzcyL = true;}
      else if(fthIkFxCJk == nILmnWjLzz){xRjduJJwAO = true;}
      if(HKGeCeLnDw == JDoCdHFuNc){qlFnljMfft = true;}
      else if(JDoCdHFuNc == HKGeCeLnDw){VXuqzqSfmR = true;}
      if(LarYyiuazj == UUuVsCgdLb){HzpCPygUrB = true;}
      else if(UUuVsCgdLb == LarYyiuazj){dpqTbuNuju = true;}
      if(AEcrklgiHj == cxdaFgktew){BAmEgFqehn = true;}
      else if(cxdaFgktew == AEcrklgiHj){otblWNFgJA = true;}
      if(nWWgaMHbYi == XeBhOSFsXA){OaaLDuSqJn = true;}
      if(heVRZNPmnF == ZPsECKzMOi){qImfutBtKe = true;}
      if(bILPyDgNsP == XTqhHLYOwx){gdjxKpyBHf = true;}
      while(XeBhOSFsXA == nWWgaMHbYi){iQHuQgCcDP = true;}
      while(ZPsECKzMOi == ZPsECKzMOi){QKqjiGZPBz = true;}
      while(XTqhHLYOwx == XTqhHLYOwx){wOLEYauIUk = true;}
      if(WLQQFpTNHa == true){WLQQFpTNHa = false;}
      if(xnGKCNDZXt == true){xnGKCNDZXt = false;}
      if(gXeuXEnTZC == true){gXeuXEnTZC = false;}
      if(sqwacNzcyL == true){sqwacNzcyL = false;}
      if(qlFnljMfft == true){qlFnljMfft = false;}
      if(HzpCPygUrB == true){HzpCPygUrB = false;}
      if(BAmEgFqehn == true){BAmEgFqehn = false;}
      if(OaaLDuSqJn == true){OaaLDuSqJn = false;}
      if(qImfutBtKe == true){qImfutBtKe = false;}
      if(gdjxKpyBHf == true){gdjxKpyBHf = false;}
      if(shyqffXdyT == true){shyqffXdyT = false;}
      if(foKEKsMHJm == true){foKEKsMHJm = false;}
      if(ExTCGjqdBM == true){ExTCGjqdBM = false;}
      if(xRjduJJwAO == true){xRjduJJwAO = false;}
      if(VXuqzqSfmR == true){VXuqzqSfmR = false;}
      if(dpqTbuNuju == true){dpqTbuNuju = false;}
      if(otblWNFgJA == true){otblWNFgJA = false;}
      if(iQHuQgCcDP == true){iQHuQgCcDP = false;}
      if(QKqjiGZPBz == true){QKqjiGZPBz = false;}
      if(wOLEYauIUk == true){wOLEYauIUk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUKVANEAQY
{ 
  void zPfWWTMJts()
  { 
      bool GptVdzbmdJ = false;
      bool CkNtZPuWQy = false;
      bool IxiSjXOtUJ = false;
      bool AfVonyFtYx = false;
      bool FAZJoInxKO = false;
      bool LYyEgJHblG = false;
      bool jhSUJVPYGa = false;
      bool JBxTrIWYcb = false;
      bool iQiFyahQHe = false;
      bool pcHSMWhFAT = false;
      bool sPqiFJbdMY = false;
      bool lhzKWSyMVi = false;
      bool nzQbkfseGU = false;
      bool ZQYJhTZAAn = false;
      bool zEEirIdxut = false;
      bool YUiRftyPyY = false;
      bool PwWqyVIpbD = false;
      bool ryMhjithib = false;
      bool CwiMwEgHcn = false;
      bool UKBbXCgMjW = false;
      string hWSGFYBUIA;
      string pYOVFzbjmO;
      string jApruBwiux;
      string UTIArquPlE;
      string OJrKtkfoHA;
      string gZQPuggZKD;
      string cRYKeVPNdN;
      string DLyizZIexK;
      string VGbuQuDrFL;
      string KVFhawkgeX;
      string URLswVbhPV;
      string XBbAhVpdtj;
      string SXIRDhFPHC;
      string oazYoDuhyt;
      string SVbimIsFAE;
      string GHmuFxJspO;
      string PLZNfxBCKd;
      string aHezQwuYeu;
      string nAPDwhnETr;
      string sCrjeHwODp;
      if(hWSGFYBUIA == URLswVbhPV){GptVdzbmdJ = true;}
      else if(URLswVbhPV == hWSGFYBUIA){sPqiFJbdMY = true;}
      if(pYOVFzbjmO == XBbAhVpdtj){CkNtZPuWQy = true;}
      else if(XBbAhVpdtj == pYOVFzbjmO){lhzKWSyMVi = true;}
      if(jApruBwiux == SXIRDhFPHC){IxiSjXOtUJ = true;}
      else if(SXIRDhFPHC == jApruBwiux){nzQbkfseGU = true;}
      if(UTIArquPlE == oazYoDuhyt){AfVonyFtYx = true;}
      else if(oazYoDuhyt == UTIArquPlE){ZQYJhTZAAn = true;}
      if(OJrKtkfoHA == SVbimIsFAE){FAZJoInxKO = true;}
      else if(SVbimIsFAE == OJrKtkfoHA){zEEirIdxut = true;}
      if(gZQPuggZKD == GHmuFxJspO){LYyEgJHblG = true;}
      else if(GHmuFxJspO == gZQPuggZKD){YUiRftyPyY = true;}
      if(cRYKeVPNdN == PLZNfxBCKd){jhSUJVPYGa = true;}
      else if(PLZNfxBCKd == cRYKeVPNdN){PwWqyVIpbD = true;}
      if(DLyizZIexK == aHezQwuYeu){JBxTrIWYcb = true;}
      if(VGbuQuDrFL == nAPDwhnETr){iQiFyahQHe = true;}
      if(KVFhawkgeX == sCrjeHwODp){pcHSMWhFAT = true;}
      while(aHezQwuYeu == DLyizZIexK){ryMhjithib = true;}
      while(nAPDwhnETr == nAPDwhnETr){CwiMwEgHcn = true;}
      while(sCrjeHwODp == sCrjeHwODp){UKBbXCgMjW = true;}
      if(GptVdzbmdJ == true){GptVdzbmdJ = false;}
      if(CkNtZPuWQy == true){CkNtZPuWQy = false;}
      if(IxiSjXOtUJ == true){IxiSjXOtUJ = false;}
      if(AfVonyFtYx == true){AfVonyFtYx = false;}
      if(FAZJoInxKO == true){FAZJoInxKO = false;}
      if(LYyEgJHblG == true){LYyEgJHblG = false;}
      if(jhSUJVPYGa == true){jhSUJVPYGa = false;}
      if(JBxTrIWYcb == true){JBxTrIWYcb = false;}
      if(iQiFyahQHe == true){iQiFyahQHe = false;}
      if(pcHSMWhFAT == true){pcHSMWhFAT = false;}
      if(sPqiFJbdMY == true){sPqiFJbdMY = false;}
      if(lhzKWSyMVi == true){lhzKWSyMVi = false;}
      if(nzQbkfseGU == true){nzQbkfseGU = false;}
      if(ZQYJhTZAAn == true){ZQYJhTZAAn = false;}
      if(zEEirIdxut == true){zEEirIdxut = false;}
      if(YUiRftyPyY == true){YUiRftyPyY = false;}
      if(PwWqyVIpbD == true){PwWqyVIpbD = false;}
      if(ryMhjithib == true){ryMhjithib = false;}
      if(CwiMwEgHcn == true){CwiMwEgHcn = false;}
      if(UKBbXCgMjW == true){UKBbXCgMjW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAJVFOWVWO
{ 
  void ccUWdjTBHI()
  { 
      bool YAIgseGhsI = false;
      bool rLhsNifkFC = false;
      bool MjHpStMRYf = false;
      bool iDkjkipbcG = false;
      bool ZPpcZlExCn = false;
      bool oSjEInsSOz = false;
      bool RoJMYoZyId = false;
      bool rEIzbwtdQg = false;
      bool oPOjpQTfbx = false;
      bool pXNdnkFcEk = false;
      bool MGnXwkKjcL = false;
      bool sOBgKBZZVI = false;
      bool VsWLnTpeKp = false;
      bool qQZfThapmF = false;
      bool FiDQDaVfTm = false;
      bool LfGwOSicjb = false;
      bool tfZlTcoVMb = false;
      bool ailQClpGIM = false;
      bool yKLXeKJdQB = false;
      bool yxGLKZJQwZ = false;
      string CEocPdAzOy;
      string HThTZYGxTf;
      string aERkxGXBOD;
      string cuBEQeZKYn;
      string fUsdHeRZBZ;
      string wUgKJymEeI;
      string GzjKUMRdCt;
      string zwXeAFKmcR;
      string oxAoHHNqtS;
      string rUeQhgjhIu;
      string MmWGaAwCKE;
      string mzaNSIyuDM;
      string yaijCdRHwT;
      string UcehECatNG;
      string KKgpessRyZ;
      string hneuwlEmDx;
      string ioGpiKTsIQ;
      string gDhwBnssEJ;
      string jzJVkgxilR;
      string xmqPXVEpHU;
      if(CEocPdAzOy == MmWGaAwCKE){YAIgseGhsI = true;}
      else if(MmWGaAwCKE == CEocPdAzOy){MGnXwkKjcL = true;}
      if(HThTZYGxTf == mzaNSIyuDM){rLhsNifkFC = true;}
      else if(mzaNSIyuDM == HThTZYGxTf){sOBgKBZZVI = true;}
      if(aERkxGXBOD == yaijCdRHwT){MjHpStMRYf = true;}
      else if(yaijCdRHwT == aERkxGXBOD){VsWLnTpeKp = true;}
      if(cuBEQeZKYn == UcehECatNG){iDkjkipbcG = true;}
      else if(UcehECatNG == cuBEQeZKYn){qQZfThapmF = true;}
      if(fUsdHeRZBZ == KKgpessRyZ){ZPpcZlExCn = true;}
      else if(KKgpessRyZ == fUsdHeRZBZ){FiDQDaVfTm = true;}
      if(wUgKJymEeI == hneuwlEmDx){oSjEInsSOz = true;}
      else if(hneuwlEmDx == wUgKJymEeI){LfGwOSicjb = true;}
      if(GzjKUMRdCt == ioGpiKTsIQ){RoJMYoZyId = true;}
      else if(ioGpiKTsIQ == GzjKUMRdCt){tfZlTcoVMb = true;}
      if(zwXeAFKmcR == gDhwBnssEJ){rEIzbwtdQg = true;}
      if(oxAoHHNqtS == jzJVkgxilR){oPOjpQTfbx = true;}
      if(rUeQhgjhIu == xmqPXVEpHU){pXNdnkFcEk = true;}
      while(gDhwBnssEJ == zwXeAFKmcR){ailQClpGIM = true;}
      while(jzJVkgxilR == jzJVkgxilR){yKLXeKJdQB = true;}
      while(xmqPXVEpHU == xmqPXVEpHU){yxGLKZJQwZ = true;}
      if(YAIgseGhsI == true){YAIgseGhsI = false;}
      if(rLhsNifkFC == true){rLhsNifkFC = false;}
      if(MjHpStMRYf == true){MjHpStMRYf = false;}
      if(iDkjkipbcG == true){iDkjkipbcG = false;}
      if(ZPpcZlExCn == true){ZPpcZlExCn = false;}
      if(oSjEInsSOz == true){oSjEInsSOz = false;}
      if(RoJMYoZyId == true){RoJMYoZyId = false;}
      if(rEIzbwtdQg == true){rEIzbwtdQg = false;}
      if(oPOjpQTfbx == true){oPOjpQTfbx = false;}
      if(pXNdnkFcEk == true){pXNdnkFcEk = false;}
      if(MGnXwkKjcL == true){MGnXwkKjcL = false;}
      if(sOBgKBZZVI == true){sOBgKBZZVI = false;}
      if(VsWLnTpeKp == true){VsWLnTpeKp = false;}
      if(qQZfThapmF == true){qQZfThapmF = false;}
      if(FiDQDaVfTm == true){FiDQDaVfTm = false;}
      if(LfGwOSicjb == true){LfGwOSicjb = false;}
      if(tfZlTcoVMb == true){tfZlTcoVMb = false;}
      if(ailQClpGIM == true){ailQClpGIM = false;}
      if(yKLXeKJdQB == true){yKLXeKJdQB = false;}
      if(yxGLKZJQwZ == true){yxGLKZJQwZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGPGODNRGP
{ 
  void NsQdxbhrsC()
  { 
      bool AtylCqOfpb = false;
      bool CZQPoQmCIZ = false;
      bool dKyKgWFJex = false;
      bool DqiyUSqsMK = false;
      bool rDroCilhRj = false;
      bool DCdtcpwmEe = false;
      bool lFAsXKqRtW = false;
      bool YtpxhaSIIx = false;
      bool kWqtsANnUe = false;
      bool WEngYlCyRq = false;
      bool rTmuLJLfMC = false;
      bool WmeHsPNFAW = false;
      bool xCwPATGIYu = false;
      bool XTqQFRiwij = false;
      bool ngaSHiZfnJ = false;
      bool XxyttoWXtq = false;
      bool CDHQdDwNBa = false;
      bool fRWPhPadHQ = false;
      bool tZUOXaUwWQ = false;
      bool uKBqgkZKoE = false;
      string BCfYhnXcyw;
      string QaQiROZIKh;
      string PyCufkVCOs;
      string OEslfANHAs;
      string DVDKbnOARc;
      string bgYmOCzksx;
      string SVNEgLgdDQ;
      string BSIQdttrSr;
      string VUjlQheGWc;
      string BcOCZgHzdQ;
      string GjwAbJXIIU;
      string IHRAaylbmy;
      string faGaPXDFpx;
      string muNCklXiKH;
      string JWxCUtKNab;
      string tfLekfdVkD;
      string GSRLgNsPPo;
      string ZCQfnIcDFV;
      string NoeOCGihQE;
      string ICxHAqFlUH;
      if(BCfYhnXcyw == GjwAbJXIIU){AtylCqOfpb = true;}
      else if(GjwAbJXIIU == BCfYhnXcyw){rTmuLJLfMC = true;}
      if(QaQiROZIKh == IHRAaylbmy){CZQPoQmCIZ = true;}
      else if(IHRAaylbmy == QaQiROZIKh){WmeHsPNFAW = true;}
      if(PyCufkVCOs == faGaPXDFpx){dKyKgWFJex = true;}
      else if(faGaPXDFpx == PyCufkVCOs){xCwPATGIYu = true;}
      if(OEslfANHAs == muNCklXiKH){DqiyUSqsMK = true;}
      else if(muNCklXiKH == OEslfANHAs){XTqQFRiwij = true;}
      if(DVDKbnOARc == JWxCUtKNab){rDroCilhRj = true;}
      else if(JWxCUtKNab == DVDKbnOARc){ngaSHiZfnJ = true;}
      if(bgYmOCzksx == tfLekfdVkD){DCdtcpwmEe = true;}
      else if(tfLekfdVkD == bgYmOCzksx){XxyttoWXtq = true;}
      if(SVNEgLgdDQ == GSRLgNsPPo){lFAsXKqRtW = true;}
      else if(GSRLgNsPPo == SVNEgLgdDQ){CDHQdDwNBa = true;}
      if(BSIQdttrSr == ZCQfnIcDFV){YtpxhaSIIx = true;}
      if(VUjlQheGWc == NoeOCGihQE){kWqtsANnUe = true;}
      if(BcOCZgHzdQ == ICxHAqFlUH){WEngYlCyRq = true;}
      while(ZCQfnIcDFV == BSIQdttrSr){fRWPhPadHQ = true;}
      while(NoeOCGihQE == NoeOCGihQE){tZUOXaUwWQ = true;}
      while(ICxHAqFlUH == ICxHAqFlUH){uKBqgkZKoE = true;}
      if(AtylCqOfpb == true){AtylCqOfpb = false;}
      if(CZQPoQmCIZ == true){CZQPoQmCIZ = false;}
      if(dKyKgWFJex == true){dKyKgWFJex = false;}
      if(DqiyUSqsMK == true){DqiyUSqsMK = false;}
      if(rDroCilhRj == true){rDroCilhRj = false;}
      if(DCdtcpwmEe == true){DCdtcpwmEe = false;}
      if(lFAsXKqRtW == true){lFAsXKqRtW = false;}
      if(YtpxhaSIIx == true){YtpxhaSIIx = false;}
      if(kWqtsANnUe == true){kWqtsANnUe = false;}
      if(WEngYlCyRq == true){WEngYlCyRq = false;}
      if(rTmuLJLfMC == true){rTmuLJLfMC = false;}
      if(WmeHsPNFAW == true){WmeHsPNFAW = false;}
      if(xCwPATGIYu == true){xCwPATGIYu = false;}
      if(XTqQFRiwij == true){XTqQFRiwij = false;}
      if(ngaSHiZfnJ == true){ngaSHiZfnJ = false;}
      if(XxyttoWXtq == true){XxyttoWXtq = false;}
      if(CDHQdDwNBa == true){CDHQdDwNBa = false;}
      if(fRWPhPadHQ == true){fRWPhPadHQ = false;}
      if(tZUOXaUwWQ == true){tZUOXaUwWQ = false;}
      if(uKBqgkZKoE == true){uKBqgkZKoE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTTPGDDFAO
{ 
  void jxyJroDxdE()
  { 
      bool mKDcpTNOhx = false;
      bool WJobqIqpyd = false;
      bool SuwhKQsjTP = false;
      bool ctBHcLGwlB = false;
      bool rqzqiypkWO = false;
      bool sdaIkqOUSZ = false;
      bool ZcuSUbHhzf = false;
      bool CtDwlauEzM = false;
      bool aHMEVySrWk = false;
      bool wkdLaPwfVG = false;
      bool qHlqMyZeWJ = false;
      bool wJVGzRPpwW = false;
      bool IOLNjRQqVV = false;
      bool eOirUSVVrW = false;
      bool YnVMolOXMJ = false;
      bool zFjzxcwXHu = false;
      bool hhIAdgackg = false;
      bool wsyZyUsyYx = false;
      bool CreLWZejur = false;
      bool VxOxnpeUhI = false;
      string FUfOFEPMAQ;
      string pVXlgdtGrB;
      string nZcybOGeYI;
      string WjBlowwPNN;
      string VdcdjZxkFN;
      string ygNtLeqgmq;
      string yjnqsFUlxj;
      string gdsefJwzNB;
      string RUZKKpVHZJ;
      string FOcVPkpljd;
      string EKnVgTniNC;
      string hqTkZcKcgC;
      string jNMmdRBWPu;
      string SKOixGgEdp;
      string CmsWbOuqwl;
      string ZMFhtqyBqO;
      string SRSSjXbjnS;
      string wGzqAwUoLP;
      string WJZcUFFgnF;
      string HeMOWkTZmD;
      if(FUfOFEPMAQ == EKnVgTniNC){mKDcpTNOhx = true;}
      else if(EKnVgTniNC == FUfOFEPMAQ){qHlqMyZeWJ = true;}
      if(pVXlgdtGrB == hqTkZcKcgC){WJobqIqpyd = true;}
      else if(hqTkZcKcgC == pVXlgdtGrB){wJVGzRPpwW = true;}
      if(nZcybOGeYI == jNMmdRBWPu){SuwhKQsjTP = true;}
      else if(jNMmdRBWPu == nZcybOGeYI){IOLNjRQqVV = true;}
      if(WjBlowwPNN == SKOixGgEdp){ctBHcLGwlB = true;}
      else if(SKOixGgEdp == WjBlowwPNN){eOirUSVVrW = true;}
      if(VdcdjZxkFN == CmsWbOuqwl){rqzqiypkWO = true;}
      else if(CmsWbOuqwl == VdcdjZxkFN){YnVMolOXMJ = true;}
      if(ygNtLeqgmq == ZMFhtqyBqO){sdaIkqOUSZ = true;}
      else if(ZMFhtqyBqO == ygNtLeqgmq){zFjzxcwXHu = true;}
      if(yjnqsFUlxj == SRSSjXbjnS){ZcuSUbHhzf = true;}
      else if(SRSSjXbjnS == yjnqsFUlxj){hhIAdgackg = true;}
      if(gdsefJwzNB == wGzqAwUoLP){CtDwlauEzM = true;}
      if(RUZKKpVHZJ == WJZcUFFgnF){aHMEVySrWk = true;}
      if(FOcVPkpljd == HeMOWkTZmD){wkdLaPwfVG = true;}
      while(wGzqAwUoLP == gdsefJwzNB){wsyZyUsyYx = true;}
      while(WJZcUFFgnF == WJZcUFFgnF){CreLWZejur = true;}
      while(HeMOWkTZmD == HeMOWkTZmD){VxOxnpeUhI = true;}
      if(mKDcpTNOhx == true){mKDcpTNOhx = false;}
      if(WJobqIqpyd == true){WJobqIqpyd = false;}
      if(SuwhKQsjTP == true){SuwhKQsjTP = false;}
      if(ctBHcLGwlB == true){ctBHcLGwlB = false;}
      if(rqzqiypkWO == true){rqzqiypkWO = false;}
      if(sdaIkqOUSZ == true){sdaIkqOUSZ = false;}
      if(ZcuSUbHhzf == true){ZcuSUbHhzf = false;}
      if(CtDwlauEzM == true){CtDwlauEzM = false;}
      if(aHMEVySrWk == true){aHMEVySrWk = false;}
      if(wkdLaPwfVG == true){wkdLaPwfVG = false;}
      if(qHlqMyZeWJ == true){qHlqMyZeWJ = false;}
      if(wJVGzRPpwW == true){wJVGzRPpwW = false;}
      if(IOLNjRQqVV == true){IOLNjRQqVV = false;}
      if(eOirUSVVrW == true){eOirUSVVrW = false;}
      if(YnVMolOXMJ == true){YnVMolOXMJ = false;}
      if(zFjzxcwXHu == true){zFjzxcwXHu = false;}
      if(hhIAdgackg == true){hhIAdgackg = false;}
      if(wsyZyUsyYx == true){wsyZyUsyYx = false;}
      if(CreLWZejur == true){CreLWZejur = false;}
      if(VxOxnpeUhI == true){VxOxnpeUhI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXASRVQNSU
{ 
  void VsubhOHJJU()
  { 
      bool KcJUuttpwI = false;
      bool hgNogCuVLf = false;
      bool fDcsjhUFmN = false;
      bool xNpXzxqOxh = false;
      bool QsDPAmdsbH = false;
      bool NcSgeHAPkM = false;
      bool YoChLTqooj = false;
      bool LgXdOlzNsw = false;
      bool EadfAUuIrr = false;
      bool xbckIbpVDg = false;
      bool wnDqwgEoRr = false;
      bool HmWnIyLWgq = false;
      bool YhxxmiDmUl = false;
      bool wdJLAPWljT = false;
      bool PFqzkJFocK = false;
      bool QTnMHNqGEM = false;
      bool cRTfwcdKnr = false;
      bool aZmNaSqxLc = false;
      bool dOJKVbowEm = false;
      bool YQgWpykLCH = false;
      string DabDUpjUXu;
      string ToJFKtPlqj;
      string JpJFVMfpIG;
      string JTzkdBeErs;
      string bAROOaPjhc;
      string BhbUUNQVgH;
      string JsLQkAoXbJ;
      string OKtyHIYuqu;
      string xwHfEaqeQQ;
      string jJXjiioAcN;
      string krHYNpndML;
      string nVelKNlfLJ;
      string JKHLYFmJOY;
      string TXScJFnhRN;
      string mNREbOelZU;
      string xInSEajwAI;
      string DdOmqPDBcE;
      string ZDOxWurCiK;
      string aAisbLjzYi;
      string UqhJKIyeML;
      if(DabDUpjUXu == krHYNpndML){KcJUuttpwI = true;}
      else if(krHYNpndML == DabDUpjUXu){wnDqwgEoRr = true;}
      if(ToJFKtPlqj == nVelKNlfLJ){hgNogCuVLf = true;}
      else if(nVelKNlfLJ == ToJFKtPlqj){HmWnIyLWgq = true;}
      if(JpJFVMfpIG == JKHLYFmJOY){fDcsjhUFmN = true;}
      else if(JKHLYFmJOY == JpJFVMfpIG){YhxxmiDmUl = true;}
      if(JTzkdBeErs == TXScJFnhRN){xNpXzxqOxh = true;}
      else if(TXScJFnhRN == JTzkdBeErs){wdJLAPWljT = true;}
      if(bAROOaPjhc == mNREbOelZU){QsDPAmdsbH = true;}
      else if(mNREbOelZU == bAROOaPjhc){PFqzkJFocK = true;}
      if(BhbUUNQVgH == xInSEajwAI){NcSgeHAPkM = true;}
      else if(xInSEajwAI == BhbUUNQVgH){QTnMHNqGEM = true;}
      if(JsLQkAoXbJ == DdOmqPDBcE){YoChLTqooj = true;}
      else if(DdOmqPDBcE == JsLQkAoXbJ){cRTfwcdKnr = true;}
      if(OKtyHIYuqu == ZDOxWurCiK){LgXdOlzNsw = true;}
      if(xwHfEaqeQQ == aAisbLjzYi){EadfAUuIrr = true;}
      if(jJXjiioAcN == UqhJKIyeML){xbckIbpVDg = true;}
      while(ZDOxWurCiK == OKtyHIYuqu){aZmNaSqxLc = true;}
      while(aAisbLjzYi == aAisbLjzYi){dOJKVbowEm = true;}
      while(UqhJKIyeML == UqhJKIyeML){YQgWpykLCH = true;}
      if(KcJUuttpwI == true){KcJUuttpwI = false;}
      if(hgNogCuVLf == true){hgNogCuVLf = false;}
      if(fDcsjhUFmN == true){fDcsjhUFmN = false;}
      if(xNpXzxqOxh == true){xNpXzxqOxh = false;}
      if(QsDPAmdsbH == true){QsDPAmdsbH = false;}
      if(NcSgeHAPkM == true){NcSgeHAPkM = false;}
      if(YoChLTqooj == true){YoChLTqooj = false;}
      if(LgXdOlzNsw == true){LgXdOlzNsw = false;}
      if(EadfAUuIrr == true){EadfAUuIrr = false;}
      if(xbckIbpVDg == true){xbckIbpVDg = false;}
      if(wnDqwgEoRr == true){wnDqwgEoRr = false;}
      if(HmWnIyLWgq == true){HmWnIyLWgq = false;}
      if(YhxxmiDmUl == true){YhxxmiDmUl = false;}
      if(wdJLAPWljT == true){wdJLAPWljT = false;}
      if(PFqzkJFocK == true){PFqzkJFocK = false;}
      if(QTnMHNqGEM == true){QTnMHNqGEM = false;}
      if(cRTfwcdKnr == true){cRTfwcdKnr = false;}
      if(aZmNaSqxLc == true){aZmNaSqxLc = false;}
      if(dOJKVbowEm == true){dOJKVbowEm = false;}
      if(YQgWpykLCH == true){YQgWpykLCH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYRYSLEJFK
{ 
  void sMYQYXRUgA()
  { 
      bool SQsBiieFZm = false;
      bool WJlJFOKlXT = false;
      bool kyMpXQfeIC = false;
      bool uLafoGmnKn = false;
      bool KxzTEeQnTM = false;
      bool ylfRQTECdR = false;
      bool DzxWqKiGTy = false;
      bool aWbjJnyrlr = false;
      bool zrKuEIfIOV = false;
      bool BkJrjKAbcs = false;
      bool uKTUkaKuIc = false;
      bool UMPkSLoBSh = false;
      bool daqxwpNizy = false;
      bool nWPrxoXoKc = false;
      bool yjzkAoUXZY = false;
      bool VyJtOUSVYt = false;
      bool NawJoyxXnd = false;
      bool mzppjsaGxH = false;
      bool VoJacoNUcb = false;
      bool VBQPOWnowB = false;
      string JEVAOLjAls;
      string MlLgpdOouL;
      string DrGoGCDOEY;
      string JDtalUAhzD;
      string YmHpqrNmjO;
      string RuUQyQygsM;
      string IUwMiIqjtU;
      string cfprmPkQxO;
      string oQdoHOhccV;
      string WToluDqtGh;
      string AcrPlkEcdh;
      string egieXrqHFU;
      string ZOHXxIpEwi;
      string YqKPNLXOCV;
      string JFytpokKOD;
      string LjnkHlVTRc;
      string uAfuInWTRM;
      string TcEiLUPMhI;
      string XfosWoCYHa;
      string oDxYaIYDlC;
      if(JEVAOLjAls == AcrPlkEcdh){SQsBiieFZm = true;}
      else if(AcrPlkEcdh == JEVAOLjAls){uKTUkaKuIc = true;}
      if(MlLgpdOouL == egieXrqHFU){WJlJFOKlXT = true;}
      else if(egieXrqHFU == MlLgpdOouL){UMPkSLoBSh = true;}
      if(DrGoGCDOEY == ZOHXxIpEwi){kyMpXQfeIC = true;}
      else if(ZOHXxIpEwi == DrGoGCDOEY){daqxwpNizy = true;}
      if(JDtalUAhzD == YqKPNLXOCV){uLafoGmnKn = true;}
      else if(YqKPNLXOCV == JDtalUAhzD){nWPrxoXoKc = true;}
      if(YmHpqrNmjO == JFytpokKOD){KxzTEeQnTM = true;}
      else if(JFytpokKOD == YmHpqrNmjO){yjzkAoUXZY = true;}
      if(RuUQyQygsM == LjnkHlVTRc){ylfRQTECdR = true;}
      else if(LjnkHlVTRc == RuUQyQygsM){VyJtOUSVYt = true;}
      if(IUwMiIqjtU == uAfuInWTRM){DzxWqKiGTy = true;}
      else if(uAfuInWTRM == IUwMiIqjtU){NawJoyxXnd = true;}
      if(cfprmPkQxO == TcEiLUPMhI){aWbjJnyrlr = true;}
      if(oQdoHOhccV == XfosWoCYHa){zrKuEIfIOV = true;}
      if(WToluDqtGh == oDxYaIYDlC){BkJrjKAbcs = true;}
      while(TcEiLUPMhI == cfprmPkQxO){mzppjsaGxH = true;}
      while(XfosWoCYHa == XfosWoCYHa){VoJacoNUcb = true;}
      while(oDxYaIYDlC == oDxYaIYDlC){VBQPOWnowB = true;}
      if(SQsBiieFZm == true){SQsBiieFZm = false;}
      if(WJlJFOKlXT == true){WJlJFOKlXT = false;}
      if(kyMpXQfeIC == true){kyMpXQfeIC = false;}
      if(uLafoGmnKn == true){uLafoGmnKn = false;}
      if(KxzTEeQnTM == true){KxzTEeQnTM = false;}
      if(ylfRQTECdR == true){ylfRQTECdR = false;}
      if(DzxWqKiGTy == true){DzxWqKiGTy = false;}
      if(aWbjJnyrlr == true){aWbjJnyrlr = false;}
      if(zrKuEIfIOV == true){zrKuEIfIOV = false;}
      if(BkJrjKAbcs == true){BkJrjKAbcs = false;}
      if(uKTUkaKuIc == true){uKTUkaKuIc = false;}
      if(UMPkSLoBSh == true){UMPkSLoBSh = false;}
      if(daqxwpNizy == true){daqxwpNizy = false;}
      if(nWPrxoXoKc == true){nWPrxoXoKc = false;}
      if(yjzkAoUXZY == true){yjzkAoUXZY = false;}
      if(VyJtOUSVYt == true){VyJtOUSVYt = false;}
      if(NawJoyxXnd == true){NawJoyxXnd = false;}
      if(mzppjsaGxH == true){mzppjsaGxH = false;}
      if(VoJacoNUcb == true){VoJacoNUcb = false;}
      if(VBQPOWnowB == true){VBQPOWnowB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAIXYLWYQP
{ 
  void ZJVQXQAGQt()
  { 
      bool XAErxpftAc = false;
      bool PmtBeDQKgV = false;
      bool NReObPISin = false;
      bool EeRDdSCqAQ = false;
      bool NwVjOhyeef = false;
      bool hmIOyGUpPg = false;
      bool hNLMYkUqWL = false;
      bool AZJQIRuuAt = false;
      bool QdnDGQVCFX = false;
      bool yLaTiAjJKd = false;
      bool NHHSeHdrGf = false;
      bool KYpVQDYHFH = false;
      bool ORkzNnyphI = false;
      bool gljVfJVVXy = false;
      bool mdwYMYVFCe = false;
      bool acDCOuVIEq = false;
      bool JnJyyYoToH = false;
      bool hDjHUjUMmn = false;
      bool SrmDgEigHk = false;
      bool mMQgnyTyam = false;
      string MHOyZwQbGl;
      string cczQTqXiyU;
      string uZXupOoqWj;
      string YCXfLuzNKa;
      string dzwlOpLuqD;
      string azjRNljTHL;
      string HYEVMaFTFY;
      string rKYXqwdkgA;
      string CtATJZSFRY;
      string KfFyTEtZZn;
      string krpRKPaMaR;
      string IylHIMYkMl;
      string HzCfOMFZEm;
      string CDKsPKDiIt;
      string zFdzQLsxpG;
      string fINnfkoKDy;
      string KAInOEnsrx;
      string JocSmCUCPC;
      string SHjyGspWNd;
      string VsfJiyxpjL;
      if(MHOyZwQbGl == krpRKPaMaR){XAErxpftAc = true;}
      else if(krpRKPaMaR == MHOyZwQbGl){NHHSeHdrGf = true;}
      if(cczQTqXiyU == IylHIMYkMl){PmtBeDQKgV = true;}
      else if(IylHIMYkMl == cczQTqXiyU){KYpVQDYHFH = true;}
      if(uZXupOoqWj == HzCfOMFZEm){NReObPISin = true;}
      else if(HzCfOMFZEm == uZXupOoqWj){ORkzNnyphI = true;}
      if(YCXfLuzNKa == CDKsPKDiIt){EeRDdSCqAQ = true;}
      else if(CDKsPKDiIt == YCXfLuzNKa){gljVfJVVXy = true;}
      if(dzwlOpLuqD == zFdzQLsxpG){NwVjOhyeef = true;}
      else if(zFdzQLsxpG == dzwlOpLuqD){mdwYMYVFCe = true;}
      if(azjRNljTHL == fINnfkoKDy){hmIOyGUpPg = true;}
      else if(fINnfkoKDy == azjRNljTHL){acDCOuVIEq = true;}
      if(HYEVMaFTFY == KAInOEnsrx){hNLMYkUqWL = true;}
      else if(KAInOEnsrx == HYEVMaFTFY){JnJyyYoToH = true;}
      if(rKYXqwdkgA == JocSmCUCPC){AZJQIRuuAt = true;}
      if(CtATJZSFRY == SHjyGspWNd){QdnDGQVCFX = true;}
      if(KfFyTEtZZn == VsfJiyxpjL){yLaTiAjJKd = true;}
      while(JocSmCUCPC == rKYXqwdkgA){hDjHUjUMmn = true;}
      while(SHjyGspWNd == SHjyGspWNd){SrmDgEigHk = true;}
      while(VsfJiyxpjL == VsfJiyxpjL){mMQgnyTyam = true;}
      if(XAErxpftAc == true){XAErxpftAc = false;}
      if(PmtBeDQKgV == true){PmtBeDQKgV = false;}
      if(NReObPISin == true){NReObPISin = false;}
      if(EeRDdSCqAQ == true){EeRDdSCqAQ = false;}
      if(NwVjOhyeef == true){NwVjOhyeef = false;}
      if(hmIOyGUpPg == true){hmIOyGUpPg = false;}
      if(hNLMYkUqWL == true){hNLMYkUqWL = false;}
      if(AZJQIRuuAt == true){AZJQIRuuAt = false;}
      if(QdnDGQVCFX == true){QdnDGQVCFX = false;}
      if(yLaTiAjJKd == true){yLaTiAjJKd = false;}
      if(NHHSeHdrGf == true){NHHSeHdrGf = false;}
      if(KYpVQDYHFH == true){KYpVQDYHFH = false;}
      if(ORkzNnyphI == true){ORkzNnyphI = false;}
      if(gljVfJVVXy == true){gljVfJVVXy = false;}
      if(mdwYMYVFCe == true){mdwYMYVFCe = false;}
      if(acDCOuVIEq == true){acDCOuVIEq = false;}
      if(JnJyyYoToH == true){JnJyyYoToH = false;}
      if(hDjHUjUMmn == true){hDjHUjUMmn = false;}
      if(SrmDgEigHk == true){SrmDgEigHk = false;}
      if(mMQgnyTyam == true){mMQgnyTyam = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWRIMTPXTD
{ 
  void BIzCSGsCSk()
  { 
      bool TNLuYODYVH = false;
      bool KtrMuCCPrM = false;
      bool tYBIchrdKu = false;
      bool dnIyQApcGy = false;
      bool LuSOIpPJtq = false;
      bool bxlBetMCRp = false;
      bool VZOZcWlsut = false;
      bool LYJsAyFmzm = false;
      bool SiiSSgBGTW = false;
      bool nnKPclgrkl = false;
      bool DVNAeCnsAf = false;
      bool nYDeXmquHw = false;
      bool UeZYGXNsQO = false;
      bool QMBMixUhmP = false;
      bool sIGmhOjfrp = false;
      bool ulkoRYuotG = false;
      bool otclPaWpwZ = false;
      bool RIHqCLXlpq = false;
      bool nhBZTebMuJ = false;
      bool BfnfazfUXG = false;
      string ymkAPrQWqO;
      string GLQCmaZNFh;
      string rHdUtYiyws;
      string VHcxpouULj;
      string ePdSyOulNn;
      string zJJyrpJPGp;
      string JSaxryhSLx;
      string eEBUCbdKVe;
      string cxjHsMxeFA;
      string feOVaMofaA;
      string gcZPItHouP;
      string MysaNMiSDe;
      string ACMKRzpftp;
      string mxjVyAWTyz;
      string FIjpngknHO;
      string cWcuzdQOxI;
      string EauFcONXbM;
      string oOTEZrSVWk;
      string NCXeMPUoVT;
      string jHVptdNdNY;
      if(ymkAPrQWqO == gcZPItHouP){TNLuYODYVH = true;}
      else if(gcZPItHouP == ymkAPrQWqO){DVNAeCnsAf = true;}
      if(GLQCmaZNFh == MysaNMiSDe){KtrMuCCPrM = true;}
      else if(MysaNMiSDe == GLQCmaZNFh){nYDeXmquHw = true;}
      if(rHdUtYiyws == ACMKRzpftp){tYBIchrdKu = true;}
      else if(ACMKRzpftp == rHdUtYiyws){UeZYGXNsQO = true;}
      if(VHcxpouULj == mxjVyAWTyz){dnIyQApcGy = true;}
      else if(mxjVyAWTyz == VHcxpouULj){QMBMixUhmP = true;}
      if(ePdSyOulNn == FIjpngknHO){LuSOIpPJtq = true;}
      else if(FIjpngknHO == ePdSyOulNn){sIGmhOjfrp = true;}
      if(zJJyrpJPGp == cWcuzdQOxI){bxlBetMCRp = true;}
      else if(cWcuzdQOxI == zJJyrpJPGp){ulkoRYuotG = true;}
      if(JSaxryhSLx == EauFcONXbM){VZOZcWlsut = true;}
      else if(EauFcONXbM == JSaxryhSLx){otclPaWpwZ = true;}
      if(eEBUCbdKVe == oOTEZrSVWk){LYJsAyFmzm = true;}
      if(cxjHsMxeFA == NCXeMPUoVT){SiiSSgBGTW = true;}
      if(feOVaMofaA == jHVptdNdNY){nnKPclgrkl = true;}
      while(oOTEZrSVWk == eEBUCbdKVe){RIHqCLXlpq = true;}
      while(NCXeMPUoVT == NCXeMPUoVT){nhBZTebMuJ = true;}
      while(jHVptdNdNY == jHVptdNdNY){BfnfazfUXG = true;}
      if(TNLuYODYVH == true){TNLuYODYVH = false;}
      if(KtrMuCCPrM == true){KtrMuCCPrM = false;}
      if(tYBIchrdKu == true){tYBIchrdKu = false;}
      if(dnIyQApcGy == true){dnIyQApcGy = false;}
      if(LuSOIpPJtq == true){LuSOIpPJtq = false;}
      if(bxlBetMCRp == true){bxlBetMCRp = false;}
      if(VZOZcWlsut == true){VZOZcWlsut = false;}
      if(LYJsAyFmzm == true){LYJsAyFmzm = false;}
      if(SiiSSgBGTW == true){SiiSSgBGTW = false;}
      if(nnKPclgrkl == true){nnKPclgrkl = false;}
      if(DVNAeCnsAf == true){DVNAeCnsAf = false;}
      if(nYDeXmquHw == true){nYDeXmquHw = false;}
      if(UeZYGXNsQO == true){UeZYGXNsQO = false;}
      if(QMBMixUhmP == true){QMBMixUhmP = false;}
      if(sIGmhOjfrp == true){sIGmhOjfrp = false;}
      if(ulkoRYuotG == true){ulkoRYuotG = false;}
      if(otclPaWpwZ == true){otclPaWpwZ = false;}
      if(RIHqCLXlpq == true){RIHqCLXlpq = false;}
      if(nhBZTebMuJ == true){nhBZTebMuJ = false;}
      if(BfnfazfUXG == true){BfnfazfUXG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWYUIYGMEX
{ 
  void UqzJqlMpnC()
  { 
      bool PBGZPmojbK = false;
      bool aUKdMzIYsY = false;
      bool qoQFmdTKJn = false;
      bool BthlnzKpiD = false;
      bool dxAjpIlSJS = false;
      bool lkgEHajAlk = false;
      bool TdamIgmYpN = false;
      bool oSpputngPe = false;
      bool rABpBPNceN = false;
      bool OJDxizWNaJ = false;
      bool VMcwdTupJM = false;
      bool lDkHsTcjks = false;
      bool SKtcyeOsHu = false;
      bool XaFFIeWELh = false;
      bool UWSRaKXwDO = false;
      bool VlbhpLSAxy = false;
      bool ECiNnLyezO = false;
      bool xYYDYuqbBm = false;
      bool GSorZlyXPx = false;
      bool LVGNcRnEcO = false;
      string jjAKaXyOXN;
      string wpFZZAxxeC;
      string xzYpkZEylP;
      string IGUSazznVe;
      string DRgUGwAEwa;
      string UHMeNjKKZB;
      string TAbIEoUlza;
      string BIbAzeSEin;
      string YzCKuAtpEp;
      string nnOTLDoYPR;
      string aOFUZLfLfh;
      string RGbkbUyRME;
      string tehIlMtHnu;
      string psnQNKsgjj;
      string ThKVXhMdqp;
      string EWMLWwgwiN;
      string QYXjrYRKWR;
      string aRhbjMULkE;
      string AQPypSgctR;
      string dxxWSuKZdz;
      if(jjAKaXyOXN == aOFUZLfLfh){PBGZPmojbK = true;}
      else if(aOFUZLfLfh == jjAKaXyOXN){VMcwdTupJM = true;}
      if(wpFZZAxxeC == RGbkbUyRME){aUKdMzIYsY = true;}
      else if(RGbkbUyRME == wpFZZAxxeC){lDkHsTcjks = true;}
      if(xzYpkZEylP == tehIlMtHnu){qoQFmdTKJn = true;}
      else if(tehIlMtHnu == xzYpkZEylP){SKtcyeOsHu = true;}
      if(IGUSazznVe == psnQNKsgjj){BthlnzKpiD = true;}
      else if(psnQNKsgjj == IGUSazznVe){XaFFIeWELh = true;}
      if(DRgUGwAEwa == ThKVXhMdqp){dxAjpIlSJS = true;}
      else if(ThKVXhMdqp == DRgUGwAEwa){UWSRaKXwDO = true;}
      if(UHMeNjKKZB == EWMLWwgwiN){lkgEHajAlk = true;}
      else if(EWMLWwgwiN == UHMeNjKKZB){VlbhpLSAxy = true;}
      if(TAbIEoUlza == QYXjrYRKWR){TdamIgmYpN = true;}
      else if(QYXjrYRKWR == TAbIEoUlza){ECiNnLyezO = true;}
      if(BIbAzeSEin == aRhbjMULkE){oSpputngPe = true;}
      if(YzCKuAtpEp == AQPypSgctR){rABpBPNceN = true;}
      if(nnOTLDoYPR == dxxWSuKZdz){OJDxizWNaJ = true;}
      while(aRhbjMULkE == BIbAzeSEin){xYYDYuqbBm = true;}
      while(AQPypSgctR == AQPypSgctR){GSorZlyXPx = true;}
      while(dxxWSuKZdz == dxxWSuKZdz){LVGNcRnEcO = true;}
      if(PBGZPmojbK == true){PBGZPmojbK = false;}
      if(aUKdMzIYsY == true){aUKdMzIYsY = false;}
      if(qoQFmdTKJn == true){qoQFmdTKJn = false;}
      if(BthlnzKpiD == true){BthlnzKpiD = false;}
      if(dxAjpIlSJS == true){dxAjpIlSJS = false;}
      if(lkgEHajAlk == true){lkgEHajAlk = false;}
      if(TdamIgmYpN == true){TdamIgmYpN = false;}
      if(oSpputngPe == true){oSpputngPe = false;}
      if(rABpBPNceN == true){rABpBPNceN = false;}
      if(OJDxizWNaJ == true){OJDxizWNaJ = false;}
      if(VMcwdTupJM == true){VMcwdTupJM = false;}
      if(lDkHsTcjks == true){lDkHsTcjks = false;}
      if(SKtcyeOsHu == true){SKtcyeOsHu = false;}
      if(XaFFIeWELh == true){XaFFIeWELh = false;}
      if(UWSRaKXwDO == true){UWSRaKXwDO = false;}
      if(VlbhpLSAxy == true){VlbhpLSAxy = false;}
      if(ECiNnLyezO == true){ECiNnLyezO = false;}
      if(xYYDYuqbBm == true){xYYDYuqbBm = false;}
      if(GSorZlyXPx == true){GSorZlyXPx = false;}
      if(LVGNcRnEcO == true){LVGNcRnEcO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZIGALWDEE
{ 
  void IyZWfhuahz()
  { 
      bool RkksFqnfQe = false;
      bool zkAHKOrRDm = false;
      bool lmNGxgWlei = false;
      bool uVOqMEbVjs = false;
      bool cLiEJunkDj = false;
      bool NpWGCdWeuY = false;
      bool UCBhidWJuG = false;
      bool mVhKKZDJxC = false;
      bool rkhtVEzIni = false;
      bool hxaLXZJBUf = false;
      bool YepxxqILwb = false;
      bool ZMhsfiTGLd = false;
      bool dNVMXpuWlj = false;
      bool QCnQcNukxd = false;
      bool wmMLIVOgfn = false;
      bool FDoqBKIdYH = false;
      bool wlYLLXYQQR = false;
      bool niJhhqBKDC = false;
      bool aOqydMMxPR = false;
      bool ERLohKNAzj = false;
      string JKYKZbLmXs;
      string VdswDFsgHx;
      string SJumbqfMix;
      string cIXdyQiGNR;
      string BIpbQOPdJt;
      string dQQbVzPkih;
      string uyDZQNGOyl;
      string VlTouKSTVN;
      string bCDnTLruIz;
      string BxXeVCEQLD;
      string HAfWYqxagK;
      string fuPVGsuPGE;
      string ULGyjXOnSr;
      string GCHRFaWfPb;
      string OQOySFhBYc;
      string HoKGiwtgmA;
      string bIInEdnxPe;
      string WPAdpEwIfe;
      string oNPpkRqAiJ;
      string gosOzGIZso;
      if(JKYKZbLmXs == HAfWYqxagK){RkksFqnfQe = true;}
      else if(HAfWYqxagK == JKYKZbLmXs){YepxxqILwb = true;}
      if(VdswDFsgHx == fuPVGsuPGE){zkAHKOrRDm = true;}
      else if(fuPVGsuPGE == VdswDFsgHx){ZMhsfiTGLd = true;}
      if(SJumbqfMix == ULGyjXOnSr){lmNGxgWlei = true;}
      else if(ULGyjXOnSr == SJumbqfMix){dNVMXpuWlj = true;}
      if(cIXdyQiGNR == GCHRFaWfPb){uVOqMEbVjs = true;}
      else if(GCHRFaWfPb == cIXdyQiGNR){QCnQcNukxd = true;}
      if(BIpbQOPdJt == OQOySFhBYc){cLiEJunkDj = true;}
      else if(OQOySFhBYc == BIpbQOPdJt){wmMLIVOgfn = true;}
      if(dQQbVzPkih == HoKGiwtgmA){NpWGCdWeuY = true;}
      else if(HoKGiwtgmA == dQQbVzPkih){FDoqBKIdYH = true;}
      if(uyDZQNGOyl == bIInEdnxPe){UCBhidWJuG = true;}
      else if(bIInEdnxPe == uyDZQNGOyl){wlYLLXYQQR = true;}
      if(VlTouKSTVN == WPAdpEwIfe){mVhKKZDJxC = true;}
      if(bCDnTLruIz == oNPpkRqAiJ){rkhtVEzIni = true;}
      if(BxXeVCEQLD == gosOzGIZso){hxaLXZJBUf = true;}
      while(WPAdpEwIfe == VlTouKSTVN){niJhhqBKDC = true;}
      while(oNPpkRqAiJ == oNPpkRqAiJ){aOqydMMxPR = true;}
      while(gosOzGIZso == gosOzGIZso){ERLohKNAzj = true;}
      if(RkksFqnfQe == true){RkksFqnfQe = false;}
      if(zkAHKOrRDm == true){zkAHKOrRDm = false;}
      if(lmNGxgWlei == true){lmNGxgWlei = false;}
      if(uVOqMEbVjs == true){uVOqMEbVjs = false;}
      if(cLiEJunkDj == true){cLiEJunkDj = false;}
      if(NpWGCdWeuY == true){NpWGCdWeuY = false;}
      if(UCBhidWJuG == true){UCBhidWJuG = false;}
      if(mVhKKZDJxC == true){mVhKKZDJxC = false;}
      if(rkhtVEzIni == true){rkhtVEzIni = false;}
      if(hxaLXZJBUf == true){hxaLXZJBUf = false;}
      if(YepxxqILwb == true){YepxxqILwb = false;}
      if(ZMhsfiTGLd == true){ZMhsfiTGLd = false;}
      if(dNVMXpuWlj == true){dNVMXpuWlj = false;}
      if(QCnQcNukxd == true){QCnQcNukxd = false;}
      if(wmMLIVOgfn == true){wmMLIVOgfn = false;}
      if(FDoqBKIdYH == true){FDoqBKIdYH = false;}
      if(wlYLLXYQQR == true){wlYLLXYQQR = false;}
      if(niJhhqBKDC == true){niJhhqBKDC = false;}
      if(aOqydMMxPR == true){aOqydMMxPR = false;}
      if(ERLohKNAzj == true){ERLohKNAzj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PXMWBPITYH
{ 
  void RhncWETkTu()
  { 
      bool grjwzeVYLT = false;
      bool MUJHPVjFuM = false;
      bool cfCtRRLBMN = false;
      bool ESHUEyJTyP = false;
      bool BFgreEAlhZ = false;
      bool AGdIIApoeg = false;
      bool SULyOtMoCQ = false;
      bool LPHeKXzKOM = false;
      bool RZSlMynzME = false;
      bool IToRwgshck = false;
      bool qLiQNjyyxj = false;
      bool BeaROsBZlP = false;
      bool FNbyIraphd = false;
      bool dQgcUGqCXb = false;
      bool ApBbCcrWCD = false;
      bool eTwMedijIV = false;
      bool JIPSGjxywI = false;
      bool BzBJPPLAue = false;
      bool zEndzKUUxq = false;
      bool XGtBSrZiVS = false;
      string GsiHQOxlzY;
      string DQxDhGOTfD;
      string AaSIQBThZn;
      string ycUerIquPZ;
      string siMUsHybKS;
      string xIigufZZqP;
      string uPLKZauSLZ;
      string OSDFJQNxPI;
      string CqXHppsmiL;
      string hREAecXCtS;
      string MfQjDeEdWd;
      string SbKhNDrDUj;
      string gHizqxODZf;
      string sLDwwWamEL;
      string lPPFsFGVmb;
      string kUgKkExQsG;
      string PADqkHYNlp;
      string cFyIyQqcGk;
      string psQxuXdsLr;
      string YKsxwkLYUl;
      if(GsiHQOxlzY == MfQjDeEdWd){grjwzeVYLT = true;}
      else if(MfQjDeEdWd == GsiHQOxlzY){qLiQNjyyxj = true;}
      if(DQxDhGOTfD == SbKhNDrDUj){MUJHPVjFuM = true;}
      else if(SbKhNDrDUj == DQxDhGOTfD){BeaROsBZlP = true;}
      if(AaSIQBThZn == gHizqxODZf){cfCtRRLBMN = true;}
      else if(gHizqxODZf == AaSIQBThZn){FNbyIraphd = true;}
      if(ycUerIquPZ == sLDwwWamEL){ESHUEyJTyP = true;}
      else if(sLDwwWamEL == ycUerIquPZ){dQgcUGqCXb = true;}
      if(siMUsHybKS == lPPFsFGVmb){BFgreEAlhZ = true;}
      else if(lPPFsFGVmb == siMUsHybKS){ApBbCcrWCD = true;}
      if(xIigufZZqP == kUgKkExQsG){AGdIIApoeg = true;}
      else if(kUgKkExQsG == xIigufZZqP){eTwMedijIV = true;}
      if(uPLKZauSLZ == PADqkHYNlp){SULyOtMoCQ = true;}
      else if(PADqkHYNlp == uPLKZauSLZ){JIPSGjxywI = true;}
      if(OSDFJQNxPI == cFyIyQqcGk){LPHeKXzKOM = true;}
      if(CqXHppsmiL == psQxuXdsLr){RZSlMynzME = true;}
      if(hREAecXCtS == YKsxwkLYUl){IToRwgshck = true;}
      while(cFyIyQqcGk == OSDFJQNxPI){BzBJPPLAue = true;}
      while(psQxuXdsLr == psQxuXdsLr){zEndzKUUxq = true;}
      while(YKsxwkLYUl == YKsxwkLYUl){XGtBSrZiVS = true;}
      if(grjwzeVYLT == true){grjwzeVYLT = false;}
      if(MUJHPVjFuM == true){MUJHPVjFuM = false;}
      if(cfCtRRLBMN == true){cfCtRRLBMN = false;}
      if(ESHUEyJTyP == true){ESHUEyJTyP = false;}
      if(BFgreEAlhZ == true){BFgreEAlhZ = false;}
      if(AGdIIApoeg == true){AGdIIApoeg = false;}
      if(SULyOtMoCQ == true){SULyOtMoCQ = false;}
      if(LPHeKXzKOM == true){LPHeKXzKOM = false;}
      if(RZSlMynzME == true){RZSlMynzME = false;}
      if(IToRwgshck == true){IToRwgshck = false;}
      if(qLiQNjyyxj == true){qLiQNjyyxj = false;}
      if(BeaROsBZlP == true){BeaROsBZlP = false;}
      if(FNbyIraphd == true){FNbyIraphd = false;}
      if(dQgcUGqCXb == true){dQgcUGqCXb = false;}
      if(ApBbCcrWCD == true){ApBbCcrWCD = false;}
      if(eTwMedijIV == true){eTwMedijIV = false;}
      if(JIPSGjxywI == true){JIPSGjxywI = false;}
      if(BzBJPPLAue == true){BzBJPPLAue = false;}
      if(zEndzKUUxq == true){zEndzKUUxq = false;}
      if(XGtBSrZiVS == true){XGtBSrZiVS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFFGEDEHSA
{ 
  void WedQltMJPg()
  { 
      bool jDJipWsakU = false;
      bool zrJBhqCBse = false;
      bool mixAsLQkpW = false;
      bool kCzYzojgZg = false;
      bool HeTtlfybsY = false;
      bool MYbzkBFJpd = false;
      bool FIjNixrjBs = false;
      bool GVbLWHPDON = false;
      bool MoqRJMZzny = false;
      bool japubzuFLn = false;
      bool mNZARqwQcd = false;
      bool lCtcQQQSEV = false;
      bool XswDIfegiX = false;
      bool MJrZZzOpzS = false;
      bool QIWJMhfNdK = false;
      bool hbAoQsRVrl = false;
      bool MPhFRbJUCR = false;
      bool BaTlFOWlqa = false;
      bool zRCXojICIg = false;
      bool hsyNGAaRrj = false;
      string SeceOtWEXK;
      string RZGfVlwyaq;
      string GEusKAZCBn;
      string ZjySOYGMXK;
      string taZbPnxnrO;
      string LJEOTNjjTN;
      string TTDjjhamQx;
      string ejaPwfeTcW;
      string DlJmcQejyB;
      string nWsKqaXpqh;
      string NJWtibhoRn;
      string iPHwKhJQHT;
      string CpnPIIpPXU;
      string IobtJsOPDA;
      string hpSKRYPwAI;
      string QGhWfXVHla;
      string kSQxfsnMmQ;
      string StNGlLXdxj;
      string rtPPEBGEOl;
      string XHcbPPZUeX;
      if(SeceOtWEXK == NJWtibhoRn){jDJipWsakU = true;}
      else if(NJWtibhoRn == SeceOtWEXK){mNZARqwQcd = true;}
      if(RZGfVlwyaq == iPHwKhJQHT){zrJBhqCBse = true;}
      else if(iPHwKhJQHT == RZGfVlwyaq){lCtcQQQSEV = true;}
      if(GEusKAZCBn == CpnPIIpPXU){mixAsLQkpW = true;}
      else if(CpnPIIpPXU == GEusKAZCBn){XswDIfegiX = true;}
      if(ZjySOYGMXK == IobtJsOPDA){kCzYzojgZg = true;}
      else if(IobtJsOPDA == ZjySOYGMXK){MJrZZzOpzS = true;}
      if(taZbPnxnrO == hpSKRYPwAI){HeTtlfybsY = true;}
      else if(hpSKRYPwAI == taZbPnxnrO){QIWJMhfNdK = true;}
      if(LJEOTNjjTN == QGhWfXVHla){MYbzkBFJpd = true;}
      else if(QGhWfXVHla == LJEOTNjjTN){hbAoQsRVrl = true;}
      if(TTDjjhamQx == kSQxfsnMmQ){FIjNixrjBs = true;}
      else if(kSQxfsnMmQ == TTDjjhamQx){MPhFRbJUCR = true;}
      if(ejaPwfeTcW == StNGlLXdxj){GVbLWHPDON = true;}
      if(DlJmcQejyB == rtPPEBGEOl){MoqRJMZzny = true;}
      if(nWsKqaXpqh == XHcbPPZUeX){japubzuFLn = true;}
      while(StNGlLXdxj == ejaPwfeTcW){BaTlFOWlqa = true;}
      while(rtPPEBGEOl == rtPPEBGEOl){zRCXojICIg = true;}
      while(XHcbPPZUeX == XHcbPPZUeX){hsyNGAaRrj = true;}
      if(jDJipWsakU == true){jDJipWsakU = false;}
      if(zrJBhqCBse == true){zrJBhqCBse = false;}
      if(mixAsLQkpW == true){mixAsLQkpW = false;}
      if(kCzYzojgZg == true){kCzYzojgZg = false;}
      if(HeTtlfybsY == true){HeTtlfybsY = false;}
      if(MYbzkBFJpd == true){MYbzkBFJpd = false;}
      if(FIjNixrjBs == true){FIjNixrjBs = false;}
      if(GVbLWHPDON == true){GVbLWHPDON = false;}
      if(MoqRJMZzny == true){MoqRJMZzny = false;}
      if(japubzuFLn == true){japubzuFLn = false;}
      if(mNZARqwQcd == true){mNZARqwQcd = false;}
      if(lCtcQQQSEV == true){lCtcQQQSEV = false;}
      if(XswDIfegiX == true){XswDIfegiX = false;}
      if(MJrZZzOpzS == true){MJrZZzOpzS = false;}
      if(QIWJMhfNdK == true){QIWJMhfNdK = false;}
      if(hbAoQsRVrl == true){hbAoQsRVrl = false;}
      if(MPhFRbJUCR == true){MPhFRbJUCR = false;}
      if(BaTlFOWlqa == true){BaTlFOWlqa = false;}
      if(zRCXojICIg == true){zRCXojICIg = false;}
      if(hsyNGAaRrj == true){hsyNGAaRrj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBMUXRFWUG
{ 
  void dOguSlwrzh()
  { 
      bool HsmaQPXHjJ = false;
      bool PzsXeRoPDm = false;
      bool fYnYInrNMk = false;
      bool HJpdPqLICC = false;
      bool qfmJMDpGbt = false;
      bool VmoQEiENSc = false;
      bool WJtyBGJOHn = false;
      bool GfMAwAldME = false;
      bool yklROUTYYg = false;
      bool lxpZfgknIF = false;
      bool taynnoZnTE = false;
      bool waANdlXbjg = false;
      bool ljpaBIplUO = false;
      bool PyVGKWmydY = false;
      bool teETkLwcws = false;
      bool JIEaSJkXle = false;
      bool zmTFoxEtDG = false;
      bool yZyKlHfVpp = false;
      bool LNpaFGttmA = false;
      bool lPLzZHLzem = false;
      string RNEGMoqRtW;
      string KQqxygqZsP;
      string qYxCbIHyEK;
      string EgHWkSzQCi;
      string byUfuuPnBh;
      string dVBPErQCdE;
      string gsNjRcJTMe;
      string hZWJnsERGg;
      string sSwVgieqSr;
      string CwmyBhjjOS;
      string kubWADyrbL;
      string nyuxKNwqDh;
      string yRBTbkmXHF;
      string IUCnuyqZVc;
      string kmPGEDAonn;
      string lsgfTStIuO;
      string QZjWCSuHCM;
      string WWUZwKCtPX;
      string jyjTSPmWTc;
      string DidGMLDsEk;
      if(RNEGMoqRtW == kubWADyrbL){HsmaQPXHjJ = true;}
      else if(kubWADyrbL == RNEGMoqRtW){taynnoZnTE = true;}
      if(KQqxygqZsP == nyuxKNwqDh){PzsXeRoPDm = true;}
      else if(nyuxKNwqDh == KQqxygqZsP){waANdlXbjg = true;}
      if(qYxCbIHyEK == yRBTbkmXHF){fYnYInrNMk = true;}
      else if(yRBTbkmXHF == qYxCbIHyEK){ljpaBIplUO = true;}
      if(EgHWkSzQCi == IUCnuyqZVc){HJpdPqLICC = true;}
      else if(IUCnuyqZVc == EgHWkSzQCi){PyVGKWmydY = true;}
      if(byUfuuPnBh == kmPGEDAonn){qfmJMDpGbt = true;}
      else if(kmPGEDAonn == byUfuuPnBh){teETkLwcws = true;}
      if(dVBPErQCdE == lsgfTStIuO){VmoQEiENSc = true;}
      else if(lsgfTStIuO == dVBPErQCdE){JIEaSJkXle = true;}
      if(gsNjRcJTMe == QZjWCSuHCM){WJtyBGJOHn = true;}
      else if(QZjWCSuHCM == gsNjRcJTMe){zmTFoxEtDG = true;}
      if(hZWJnsERGg == WWUZwKCtPX){GfMAwAldME = true;}
      if(sSwVgieqSr == jyjTSPmWTc){yklROUTYYg = true;}
      if(CwmyBhjjOS == DidGMLDsEk){lxpZfgknIF = true;}
      while(WWUZwKCtPX == hZWJnsERGg){yZyKlHfVpp = true;}
      while(jyjTSPmWTc == jyjTSPmWTc){LNpaFGttmA = true;}
      while(DidGMLDsEk == DidGMLDsEk){lPLzZHLzem = true;}
      if(HsmaQPXHjJ == true){HsmaQPXHjJ = false;}
      if(PzsXeRoPDm == true){PzsXeRoPDm = false;}
      if(fYnYInrNMk == true){fYnYInrNMk = false;}
      if(HJpdPqLICC == true){HJpdPqLICC = false;}
      if(qfmJMDpGbt == true){qfmJMDpGbt = false;}
      if(VmoQEiENSc == true){VmoQEiENSc = false;}
      if(WJtyBGJOHn == true){WJtyBGJOHn = false;}
      if(GfMAwAldME == true){GfMAwAldME = false;}
      if(yklROUTYYg == true){yklROUTYYg = false;}
      if(lxpZfgknIF == true){lxpZfgknIF = false;}
      if(taynnoZnTE == true){taynnoZnTE = false;}
      if(waANdlXbjg == true){waANdlXbjg = false;}
      if(ljpaBIplUO == true){ljpaBIplUO = false;}
      if(PyVGKWmydY == true){PyVGKWmydY = false;}
      if(teETkLwcws == true){teETkLwcws = false;}
      if(JIEaSJkXle == true){JIEaSJkXle = false;}
      if(zmTFoxEtDG == true){zmTFoxEtDG = false;}
      if(yZyKlHfVpp == true){yZyKlHfVpp = false;}
      if(LNpaFGttmA == true){LNpaFGttmA = false;}
      if(lPLzZHLzem == true){lPLzZHLzem = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKRZCQQXHL
{ 
  void pjmiKwODTE()
  { 
      bool nMQlxZQzss = false;
      bool zPwugbQFjF = false;
      bool WhweuiZnRA = false;
      bool coUXjNDClj = false;
      bool bOnusGfqLc = false;
      bool HIPEaFQkpN = false;
      bool AchrQKuXKS = false;
      bool YOSzcItAkn = false;
      bool DibosTZPxe = false;
      bool xSLYjzgudi = false;
      bool LIfrEsoPbS = false;
      bool LPzCKQBrzx = false;
      bool keafVFCtPc = false;
      bool ayWCbuDikz = false;
      bool dJndThSJNS = false;
      bool ynugxggzWy = false;
      bool puzyqMsxZP = false;
      bool NRHzSaqwMn = false;
      bool msfwelCoEu = false;
      bool NDLlJiKolG = false;
      string ZRuOQgUEJm;
      string RCzdIETNze;
      string RRabAbGxpZ;
      string HggLPKZLep;
      string bthCTsXmtJ;
      string PfrtMHpSNo;
      string ZWOjekVmNx;
      string eHhICWjYIG;
      string DTDfJanlyH;
      string UHxpPFfxWh;
      string XjYweHxiqp;
      string XQKHlGShZD;
      string xinGbWKrsw;
      string qlBZhSuGBC;
      string dFtIjDxpEI;
      string lxXTknuSTH;
      string xEptykPjYS;
      string LMgXZrneVY;
      string ZUnjKsOhns;
      string WblsFYOzKy;
      if(ZRuOQgUEJm == XjYweHxiqp){nMQlxZQzss = true;}
      else if(XjYweHxiqp == ZRuOQgUEJm){LIfrEsoPbS = true;}
      if(RCzdIETNze == XQKHlGShZD){zPwugbQFjF = true;}
      else if(XQKHlGShZD == RCzdIETNze){LPzCKQBrzx = true;}
      if(RRabAbGxpZ == xinGbWKrsw){WhweuiZnRA = true;}
      else if(xinGbWKrsw == RRabAbGxpZ){keafVFCtPc = true;}
      if(HggLPKZLep == qlBZhSuGBC){coUXjNDClj = true;}
      else if(qlBZhSuGBC == HggLPKZLep){ayWCbuDikz = true;}
      if(bthCTsXmtJ == dFtIjDxpEI){bOnusGfqLc = true;}
      else if(dFtIjDxpEI == bthCTsXmtJ){dJndThSJNS = true;}
      if(PfrtMHpSNo == lxXTknuSTH){HIPEaFQkpN = true;}
      else if(lxXTknuSTH == PfrtMHpSNo){ynugxggzWy = true;}
      if(ZWOjekVmNx == xEptykPjYS){AchrQKuXKS = true;}
      else if(xEptykPjYS == ZWOjekVmNx){puzyqMsxZP = true;}
      if(eHhICWjYIG == LMgXZrneVY){YOSzcItAkn = true;}
      if(DTDfJanlyH == ZUnjKsOhns){DibosTZPxe = true;}
      if(UHxpPFfxWh == WblsFYOzKy){xSLYjzgudi = true;}
      while(LMgXZrneVY == eHhICWjYIG){NRHzSaqwMn = true;}
      while(ZUnjKsOhns == ZUnjKsOhns){msfwelCoEu = true;}
      while(WblsFYOzKy == WblsFYOzKy){NDLlJiKolG = true;}
      if(nMQlxZQzss == true){nMQlxZQzss = false;}
      if(zPwugbQFjF == true){zPwugbQFjF = false;}
      if(WhweuiZnRA == true){WhweuiZnRA = false;}
      if(coUXjNDClj == true){coUXjNDClj = false;}
      if(bOnusGfqLc == true){bOnusGfqLc = false;}
      if(HIPEaFQkpN == true){HIPEaFQkpN = false;}
      if(AchrQKuXKS == true){AchrQKuXKS = false;}
      if(YOSzcItAkn == true){YOSzcItAkn = false;}
      if(DibosTZPxe == true){DibosTZPxe = false;}
      if(xSLYjzgudi == true){xSLYjzgudi = false;}
      if(LIfrEsoPbS == true){LIfrEsoPbS = false;}
      if(LPzCKQBrzx == true){LPzCKQBrzx = false;}
      if(keafVFCtPc == true){keafVFCtPc = false;}
      if(ayWCbuDikz == true){ayWCbuDikz = false;}
      if(dJndThSJNS == true){dJndThSJNS = false;}
      if(ynugxggzWy == true){ynugxggzWy = false;}
      if(puzyqMsxZP == true){puzyqMsxZP = false;}
      if(NRHzSaqwMn == true){NRHzSaqwMn = false;}
      if(msfwelCoEu == true){msfwelCoEu = false;}
      if(NDLlJiKolG == true){NDLlJiKolG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JETCJETCDT
{ 
  void KNItOaPTOb()
  { 
      bool ubPZqpNVKu = false;
      bool GDTweGnYAY = false;
      bool MoyGdpFHVJ = false;
      bool lhfsRYmJBN = false;
      bool xpHFLlKiMw = false;
      bool bAJgsFdJuB = false;
      bool jGzAJXWadF = false;
      bool SeWlbWgrur = false;
      bool eWuZhkXzAL = false;
      bool udNAcppGwm = false;
      bool OjEGcxcWFV = false;
      bool YlOCVNLZSY = false;
      bool AXZRKoQVJk = false;
      bool fawHduRnwk = false;
      bool HAsdmJPLeP = false;
      bool eQnXmpJmwm = false;
      bool fHNUpxoGYZ = false;
      bool wWchQzewdB = false;
      bool YFqtFOmYTn = false;
      bool kerJEAlXmp = false;
      string ogUDqyOIrZ;
      string xerQMTMRhb;
      string CWPwpriWDo;
      string ScURbgIpsu;
      string trjJdRsmGU;
      string XaLTTRRYNz;
      string PqFDHTJaof;
      string LVXlhKmFRY;
      string ywQhQqQByK;
      string OictfClgBJ;
      string HSxaJCCYkI;
      string eLHoASaXlP;
      string DIbdQcrdGf;
      string YGEHQfyoXN;
      string orPoeDbntM;
      string bNtkGzpTJf;
      string KYSFiYHzXT;
      string UkzYaKrlzN;
      string BDjsEKLSBR;
      string oeerCQYKFF;
      if(ogUDqyOIrZ == HSxaJCCYkI){ubPZqpNVKu = true;}
      else if(HSxaJCCYkI == ogUDqyOIrZ){OjEGcxcWFV = true;}
      if(xerQMTMRhb == eLHoASaXlP){GDTweGnYAY = true;}
      else if(eLHoASaXlP == xerQMTMRhb){YlOCVNLZSY = true;}
      if(CWPwpriWDo == DIbdQcrdGf){MoyGdpFHVJ = true;}
      else if(DIbdQcrdGf == CWPwpriWDo){AXZRKoQVJk = true;}
      if(ScURbgIpsu == YGEHQfyoXN){lhfsRYmJBN = true;}
      else if(YGEHQfyoXN == ScURbgIpsu){fawHduRnwk = true;}
      if(trjJdRsmGU == orPoeDbntM){xpHFLlKiMw = true;}
      else if(orPoeDbntM == trjJdRsmGU){HAsdmJPLeP = true;}
      if(XaLTTRRYNz == bNtkGzpTJf){bAJgsFdJuB = true;}
      else if(bNtkGzpTJf == XaLTTRRYNz){eQnXmpJmwm = true;}
      if(PqFDHTJaof == KYSFiYHzXT){jGzAJXWadF = true;}
      else if(KYSFiYHzXT == PqFDHTJaof){fHNUpxoGYZ = true;}
      if(LVXlhKmFRY == UkzYaKrlzN){SeWlbWgrur = true;}
      if(ywQhQqQByK == BDjsEKLSBR){eWuZhkXzAL = true;}
      if(OictfClgBJ == oeerCQYKFF){udNAcppGwm = true;}
      while(UkzYaKrlzN == LVXlhKmFRY){wWchQzewdB = true;}
      while(BDjsEKLSBR == BDjsEKLSBR){YFqtFOmYTn = true;}
      while(oeerCQYKFF == oeerCQYKFF){kerJEAlXmp = true;}
      if(ubPZqpNVKu == true){ubPZqpNVKu = false;}
      if(GDTweGnYAY == true){GDTweGnYAY = false;}
      if(MoyGdpFHVJ == true){MoyGdpFHVJ = false;}
      if(lhfsRYmJBN == true){lhfsRYmJBN = false;}
      if(xpHFLlKiMw == true){xpHFLlKiMw = false;}
      if(bAJgsFdJuB == true){bAJgsFdJuB = false;}
      if(jGzAJXWadF == true){jGzAJXWadF = false;}
      if(SeWlbWgrur == true){SeWlbWgrur = false;}
      if(eWuZhkXzAL == true){eWuZhkXzAL = false;}
      if(udNAcppGwm == true){udNAcppGwm = false;}
      if(OjEGcxcWFV == true){OjEGcxcWFV = false;}
      if(YlOCVNLZSY == true){YlOCVNLZSY = false;}
      if(AXZRKoQVJk == true){AXZRKoQVJk = false;}
      if(fawHduRnwk == true){fawHduRnwk = false;}
      if(HAsdmJPLeP == true){HAsdmJPLeP = false;}
      if(eQnXmpJmwm == true){eQnXmpJmwm = false;}
      if(fHNUpxoGYZ == true){fHNUpxoGYZ = false;}
      if(wWchQzewdB == true){wWchQzewdB = false;}
      if(YFqtFOmYTn == true){YFqtFOmYTn = false;}
      if(kerJEAlXmp == true){kerJEAlXmp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVFNONLLIO
{ 
  void rBaCBMkVgC()
  { 
      bool yjLSkkZhYC = false;
      bool IqlQKQRjaX = false;
      bool pxOSzslYCf = false;
      bool DikupRiNct = false;
      bool YVBlXMzooY = false;
      bool ZxbbuAVrTr = false;
      bool yBfrzYGpas = false;
      bool hEHfyUubtl = false;
      bool txidGGHIzo = false;
      bool uptkwXoImz = false;
      bool GIOwpUpuca = false;
      bool FsxgxBRCls = false;
      bool QxplxqKVja = false;
      bool eloufkimmk = false;
      bool QLfYjCsMmt = false;
      bool FlWthJSbyz = false;
      bool KTKBuSECBM = false;
      bool SePAbFQRBu = false;
      bool xyioUsPuMV = false;
      bool SGomawAddR = false;
      string FoWUpWEerK;
      string nEwDeoYGCL;
      string ZgHKbtxWbe;
      string COixfBfezY;
      string RogVdKgHtL;
      string LIGJFYhMru;
      string ZhDNIYUyWd;
      string IsGdtjzkgQ;
      string NobQTsIYrH;
      string STmEzjlTME;
      string phjPCRBcPU;
      string ZwfahjFmsP;
      string QuGPKoGCdJ;
      string yeXbaeFLNB;
      string qfIWgWmLVP;
      string dzaxmtaTFM;
      string LzyGWuXDzC;
      string dsYrXkljhn;
      string BtgOezEaog;
      string DkGAorgCzl;
      if(FoWUpWEerK == phjPCRBcPU){yjLSkkZhYC = true;}
      else if(phjPCRBcPU == FoWUpWEerK){GIOwpUpuca = true;}
      if(nEwDeoYGCL == ZwfahjFmsP){IqlQKQRjaX = true;}
      else if(ZwfahjFmsP == nEwDeoYGCL){FsxgxBRCls = true;}
      if(ZgHKbtxWbe == QuGPKoGCdJ){pxOSzslYCf = true;}
      else if(QuGPKoGCdJ == ZgHKbtxWbe){QxplxqKVja = true;}
      if(COixfBfezY == yeXbaeFLNB){DikupRiNct = true;}
      else if(yeXbaeFLNB == COixfBfezY){eloufkimmk = true;}
      if(RogVdKgHtL == qfIWgWmLVP){YVBlXMzooY = true;}
      else if(qfIWgWmLVP == RogVdKgHtL){QLfYjCsMmt = true;}
      if(LIGJFYhMru == dzaxmtaTFM){ZxbbuAVrTr = true;}
      else if(dzaxmtaTFM == LIGJFYhMru){FlWthJSbyz = true;}
      if(ZhDNIYUyWd == LzyGWuXDzC){yBfrzYGpas = true;}
      else if(LzyGWuXDzC == ZhDNIYUyWd){KTKBuSECBM = true;}
      if(IsGdtjzkgQ == dsYrXkljhn){hEHfyUubtl = true;}
      if(NobQTsIYrH == BtgOezEaog){txidGGHIzo = true;}
      if(STmEzjlTME == DkGAorgCzl){uptkwXoImz = true;}
      while(dsYrXkljhn == IsGdtjzkgQ){SePAbFQRBu = true;}
      while(BtgOezEaog == BtgOezEaog){xyioUsPuMV = true;}
      while(DkGAorgCzl == DkGAorgCzl){SGomawAddR = true;}
      if(yjLSkkZhYC == true){yjLSkkZhYC = false;}
      if(IqlQKQRjaX == true){IqlQKQRjaX = false;}
      if(pxOSzslYCf == true){pxOSzslYCf = false;}
      if(DikupRiNct == true){DikupRiNct = false;}
      if(YVBlXMzooY == true){YVBlXMzooY = false;}
      if(ZxbbuAVrTr == true){ZxbbuAVrTr = false;}
      if(yBfrzYGpas == true){yBfrzYGpas = false;}
      if(hEHfyUubtl == true){hEHfyUubtl = false;}
      if(txidGGHIzo == true){txidGGHIzo = false;}
      if(uptkwXoImz == true){uptkwXoImz = false;}
      if(GIOwpUpuca == true){GIOwpUpuca = false;}
      if(FsxgxBRCls == true){FsxgxBRCls = false;}
      if(QxplxqKVja == true){QxplxqKVja = false;}
      if(eloufkimmk == true){eloufkimmk = false;}
      if(QLfYjCsMmt == true){QLfYjCsMmt = false;}
      if(FlWthJSbyz == true){FlWthJSbyz = false;}
      if(KTKBuSECBM == true){KTKBuSECBM = false;}
      if(SePAbFQRBu == true){SePAbFQRBu = false;}
      if(xyioUsPuMV == true){xyioUsPuMV = false;}
      if(SGomawAddR == true){SGomawAddR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQSYJTBUKW
{ 
  void cdObpQJFZo()
  { 
      bool wYPbbTyrzc = false;
      bool FFfBSUBTaC = false;
      bool DHBxuirBXd = false;
      bool zpTSfajRaV = false;
      bool sWWbcDcEqr = false;
      bool xdduKnXRfs = false;
      bool bwTUcPkNUr = false;
      bool kjrFIfjZUr = false;
      bool FmKffVLXHq = false;
      bool DRlhswDBzM = false;
      bool RPjzGNkYle = false;
      bool ExwmnokmoH = false;
      bool DNGdnSyKLL = false;
      bool chaIZpDLZR = false;
      bool jmkbmFUytE = false;
      bool LPMrIEIFKm = false;
      bool PaMZCVWnMx = false;
      bool lYNXWQbdqi = false;
      bool xzQGAMVizV = false;
      bool gxBlBJaLZQ = false;
      string CPYAfoutnO;
      string HnZwggoDEF;
      string QCnKgjcycW;
      string aUbfqdhfMw;
      string xQNnheYeiz;
      string YLDgtAbOSu;
      string MxRQnlMtED;
      string zIpHHAozbC;
      string KxOcxPRukq;
      string BSMQjAywAu;
      string SeZezQUuYt;
      string KbmQjPhoSX;
      string UQINBfuZXH;
      string BryfjfWjcg;
      string tVVqfZfwfU;
      string RJcbaBWMcS;
      string UuXQsRdGgE;
      string ryLkcyuRgb;
      string AzsDpqOVEi;
      string IJGJMzyFxO;
      if(CPYAfoutnO == SeZezQUuYt){wYPbbTyrzc = true;}
      else if(SeZezQUuYt == CPYAfoutnO){RPjzGNkYle = true;}
      if(HnZwggoDEF == KbmQjPhoSX){FFfBSUBTaC = true;}
      else if(KbmQjPhoSX == HnZwggoDEF){ExwmnokmoH = true;}
      if(QCnKgjcycW == UQINBfuZXH){DHBxuirBXd = true;}
      else if(UQINBfuZXH == QCnKgjcycW){DNGdnSyKLL = true;}
      if(aUbfqdhfMw == BryfjfWjcg){zpTSfajRaV = true;}
      else if(BryfjfWjcg == aUbfqdhfMw){chaIZpDLZR = true;}
      if(xQNnheYeiz == tVVqfZfwfU){sWWbcDcEqr = true;}
      else if(tVVqfZfwfU == xQNnheYeiz){jmkbmFUytE = true;}
      if(YLDgtAbOSu == RJcbaBWMcS){xdduKnXRfs = true;}
      else if(RJcbaBWMcS == YLDgtAbOSu){LPMrIEIFKm = true;}
      if(MxRQnlMtED == UuXQsRdGgE){bwTUcPkNUr = true;}
      else if(UuXQsRdGgE == MxRQnlMtED){PaMZCVWnMx = true;}
      if(zIpHHAozbC == ryLkcyuRgb){kjrFIfjZUr = true;}
      if(KxOcxPRukq == AzsDpqOVEi){FmKffVLXHq = true;}
      if(BSMQjAywAu == IJGJMzyFxO){DRlhswDBzM = true;}
      while(ryLkcyuRgb == zIpHHAozbC){lYNXWQbdqi = true;}
      while(AzsDpqOVEi == AzsDpqOVEi){xzQGAMVizV = true;}
      while(IJGJMzyFxO == IJGJMzyFxO){gxBlBJaLZQ = true;}
      if(wYPbbTyrzc == true){wYPbbTyrzc = false;}
      if(FFfBSUBTaC == true){FFfBSUBTaC = false;}
      if(DHBxuirBXd == true){DHBxuirBXd = false;}
      if(zpTSfajRaV == true){zpTSfajRaV = false;}
      if(sWWbcDcEqr == true){sWWbcDcEqr = false;}
      if(xdduKnXRfs == true){xdduKnXRfs = false;}
      if(bwTUcPkNUr == true){bwTUcPkNUr = false;}
      if(kjrFIfjZUr == true){kjrFIfjZUr = false;}
      if(FmKffVLXHq == true){FmKffVLXHq = false;}
      if(DRlhswDBzM == true){DRlhswDBzM = false;}
      if(RPjzGNkYle == true){RPjzGNkYle = false;}
      if(ExwmnokmoH == true){ExwmnokmoH = false;}
      if(DNGdnSyKLL == true){DNGdnSyKLL = false;}
      if(chaIZpDLZR == true){chaIZpDLZR = false;}
      if(jmkbmFUytE == true){jmkbmFUytE = false;}
      if(LPMrIEIFKm == true){LPMrIEIFKm = false;}
      if(PaMZCVWnMx == true){PaMZCVWnMx = false;}
      if(lYNXWQbdqi == true){lYNXWQbdqi = false;}
      if(xzQGAMVizV == true){xzQGAMVizV = false;}
      if(gxBlBJaLZQ == true){gxBlBJaLZQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAJOZFMNGB
{ 
  void JLripgMheA()
  { 
      bool dKYOCORyTX = false;
      bool hCJnUqJxze = false;
      bool LmPJOxNJTd = false;
      bool MiLaUCiKWT = false;
      bool lLKFQgBgzd = false;
      bool NsmTqqtPzF = false;
      bool AIdoKyphTS = false;
      bool HyZerzbKsh = false;
      bool wgJpQTwqic = false;
      bool HTLRSdgVtR = false;
      bool pSMgVOTHbq = false;
      bool PjWRITynXq = false;
      bool CyzqKnmHMN = false;
      bool RFPaqdTcTC = false;
      bool AoPqNXwsIz = false;
      bool fsxDPqSVVh = false;
      bool aLtNYJTwZe = false;
      bool AVTVpMhHcm = false;
      bool qtzMhYHLKz = false;
      bool KxGlaotCRD = false;
      string VkMTMXOqGb;
      string GknFMInsHw;
      string hIqUKRdeMm;
      string pXPcHGrCAI;
      string ZGPOZOQonN;
      string bNEiLNtrIt;
      string sieTkiVKxG;
      string QkryWbscuw;
      string BnqzKcSfRt;
      string MAtFOpbucq;
      string sFqgxpVFMi;
      string TQwLsFrfII;
      string PosDtPqlif;
      string AxzDDuxJBT;
      string GMShZuDhMJ;
      string xwmUaEMmmg;
      string ziWgiWQsIx;
      string HidnBDVKdy;
      string MIZZhEKdcz;
      string iKVTUWplyD;
      if(VkMTMXOqGb == sFqgxpVFMi){dKYOCORyTX = true;}
      else if(sFqgxpVFMi == VkMTMXOqGb){pSMgVOTHbq = true;}
      if(GknFMInsHw == TQwLsFrfII){hCJnUqJxze = true;}
      else if(TQwLsFrfII == GknFMInsHw){PjWRITynXq = true;}
      if(hIqUKRdeMm == PosDtPqlif){LmPJOxNJTd = true;}
      else if(PosDtPqlif == hIqUKRdeMm){CyzqKnmHMN = true;}
      if(pXPcHGrCAI == AxzDDuxJBT){MiLaUCiKWT = true;}
      else if(AxzDDuxJBT == pXPcHGrCAI){RFPaqdTcTC = true;}
      if(ZGPOZOQonN == GMShZuDhMJ){lLKFQgBgzd = true;}
      else if(GMShZuDhMJ == ZGPOZOQonN){AoPqNXwsIz = true;}
      if(bNEiLNtrIt == xwmUaEMmmg){NsmTqqtPzF = true;}
      else if(xwmUaEMmmg == bNEiLNtrIt){fsxDPqSVVh = true;}
      if(sieTkiVKxG == ziWgiWQsIx){AIdoKyphTS = true;}
      else if(ziWgiWQsIx == sieTkiVKxG){aLtNYJTwZe = true;}
      if(QkryWbscuw == HidnBDVKdy){HyZerzbKsh = true;}
      if(BnqzKcSfRt == MIZZhEKdcz){wgJpQTwqic = true;}
      if(MAtFOpbucq == iKVTUWplyD){HTLRSdgVtR = true;}
      while(HidnBDVKdy == QkryWbscuw){AVTVpMhHcm = true;}
      while(MIZZhEKdcz == MIZZhEKdcz){qtzMhYHLKz = true;}
      while(iKVTUWplyD == iKVTUWplyD){KxGlaotCRD = true;}
      if(dKYOCORyTX == true){dKYOCORyTX = false;}
      if(hCJnUqJxze == true){hCJnUqJxze = false;}
      if(LmPJOxNJTd == true){LmPJOxNJTd = false;}
      if(MiLaUCiKWT == true){MiLaUCiKWT = false;}
      if(lLKFQgBgzd == true){lLKFQgBgzd = false;}
      if(NsmTqqtPzF == true){NsmTqqtPzF = false;}
      if(AIdoKyphTS == true){AIdoKyphTS = false;}
      if(HyZerzbKsh == true){HyZerzbKsh = false;}
      if(wgJpQTwqic == true){wgJpQTwqic = false;}
      if(HTLRSdgVtR == true){HTLRSdgVtR = false;}
      if(pSMgVOTHbq == true){pSMgVOTHbq = false;}
      if(PjWRITynXq == true){PjWRITynXq = false;}
      if(CyzqKnmHMN == true){CyzqKnmHMN = false;}
      if(RFPaqdTcTC == true){RFPaqdTcTC = false;}
      if(AoPqNXwsIz == true){AoPqNXwsIz = false;}
      if(fsxDPqSVVh == true){fsxDPqSVVh = false;}
      if(aLtNYJTwZe == true){aLtNYJTwZe = false;}
      if(AVTVpMhHcm == true){AVTVpMhHcm = false;}
      if(qtzMhYHLKz == true){qtzMhYHLKz = false;}
      if(KxGlaotCRD == true){KxGlaotCRD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MRZRTEKACI
{ 
  void ArrHEyAPrc()
  { 
      bool oBAODIjMuM = false;
      bool KUBSxEMcJs = false;
      bool CywBjfsBgW = false;
      bool tUVuDxPDpj = false;
      bool RhEdgRWAPB = false;
      bool OYuOeqFzeW = false;
      bool OheXRpzFPz = false;
      bool nImYaUtSTR = false;
      bool JskeHVZGPL = false;
      bool rQYSVjCfLq = false;
      bool SRjQNFkVnK = false;
      bool xmeMNVxzQu = false;
      bool ProDGWjUDq = false;
      bool RNGczrIURB = false;
      bool kESFOFlLFz = false;
      bool lDPPbZbgJp = false;
      bool VQSwrifCNV = false;
      bool MchOKLZjnB = false;
      bool kXPDEOxpAY = false;
      bool PbKafUkVMf = false;
      string qYqeIAqIoY;
      string xTAubDMXWD;
      string MsoaNfEbpR;
      string bfPSSPpiXJ;
      string bokwwUNOEx;
      string KjkrTyjQQb;
      string uORWxRDgbM;
      string McANaWHres;
      string SoWsHquXzU;
      string fZRuNMWOze;
      string QflrjgjWQw;
      string pqlWJGqXOF;
      string VfgHgmLEAO;
      string AsszclCeJa;
      string HYGDdnntlH;
      string VyzsJjzeLw;
      string UeWCuwyltW;
      string DMOmywYddr;
      string zQSssCtzpr;
      string mXSMGbCEIh;
      if(qYqeIAqIoY == QflrjgjWQw){oBAODIjMuM = true;}
      else if(QflrjgjWQw == qYqeIAqIoY){SRjQNFkVnK = true;}
      if(xTAubDMXWD == pqlWJGqXOF){KUBSxEMcJs = true;}
      else if(pqlWJGqXOF == xTAubDMXWD){xmeMNVxzQu = true;}
      if(MsoaNfEbpR == VfgHgmLEAO){CywBjfsBgW = true;}
      else if(VfgHgmLEAO == MsoaNfEbpR){ProDGWjUDq = true;}
      if(bfPSSPpiXJ == AsszclCeJa){tUVuDxPDpj = true;}
      else if(AsszclCeJa == bfPSSPpiXJ){RNGczrIURB = true;}
      if(bokwwUNOEx == HYGDdnntlH){RhEdgRWAPB = true;}
      else if(HYGDdnntlH == bokwwUNOEx){kESFOFlLFz = true;}
      if(KjkrTyjQQb == VyzsJjzeLw){OYuOeqFzeW = true;}
      else if(VyzsJjzeLw == KjkrTyjQQb){lDPPbZbgJp = true;}
      if(uORWxRDgbM == UeWCuwyltW){OheXRpzFPz = true;}
      else if(UeWCuwyltW == uORWxRDgbM){VQSwrifCNV = true;}
      if(McANaWHres == DMOmywYddr){nImYaUtSTR = true;}
      if(SoWsHquXzU == zQSssCtzpr){JskeHVZGPL = true;}
      if(fZRuNMWOze == mXSMGbCEIh){rQYSVjCfLq = true;}
      while(DMOmywYddr == McANaWHres){MchOKLZjnB = true;}
      while(zQSssCtzpr == zQSssCtzpr){kXPDEOxpAY = true;}
      while(mXSMGbCEIh == mXSMGbCEIh){PbKafUkVMf = true;}
      if(oBAODIjMuM == true){oBAODIjMuM = false;}
      if(KUBSxEMcJs == true){KUBSxEMcJs = false;}
      if(CywBjfsBgW == true){CywBjfsBgW = false;}
      if(tUVuDxPDpj == true){tUVuDxPDpj = false;}
      if(RhEdgRWAPB == true){RhEdgRWAPB = false;}
      if(OYuOeqFzeW == true){OYuOeqFzeW = false;}
      if(OheXRpzFPz == true){OheXRpzFPz = false;}
      if(nImYaUtSTR == true){nImYaUtSTR = false;}
      if(JskeHVZGPL == true){JskeHVZGPL = false;}
      if(rQYSVjCfLq == true){rQYSVjCfLq = false;}
      if(SRjQNFkVnK == true){SRjQNFkVnK = false;}
      if(xmeMNVxzQu == true){xmeMNVxzQu = false;}
      if(ProDGWjUDq == true){ProDGWjUDq = false;}
      if(RNGczrIURB == true){RNGczrIURB = false;}
      if(kESFOFlLFz == true){kESFOFlLFz = false;}
      if(lDPPbZbgJp == true){lDPPbZbgJp = false;}
      if(VQSwrifCNV == true){VQSwrifCNV = false;}
      if(MchOKLZjnB == true){MchOKLZjnB = false;}
      if(kXPDEOxpAY == true){kXPDEOxpAY = false;}
      if(PbKafUkVMf == true){PbKafUkVMf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCRYKODITH
{ 
  void GpAFZZThbZ()
  { 
      bool tbSCxBWdmu = false;
      bool hflDHzsfkJ = false;
      bool faLXcnleTP = false;
      bool IglMTJqhYP = false;
      bool HSCGdakzWL = false;
      bool GxUYrSPuZJ = false;
      bool OqKWlAtZjx = false;
      bool HLGVCMXFsC = false;
      bool DmHIILMMUA = false;
      bool twHPAPIfTd = false;
      bool fKPZDuqzWe = false;
      bool uJCXFbjCNa = false;
      bool mhFjCLDpUm = false;
      bool ErkOVrXgEN = false;
      bool TMppEjsjKY = false;
      bool eFRspyFfWr = false;
      bool rAdiZDXnBM = false;
      bool EDxAGaqOeR = false;
      bool RSfwHzZrXX = false;
      bool mqJMUTiGPB = false;
      string FGGEDBICjx;
      string lAGGMhVXdZ;
      string NJHXkInqau;
      string bBjrhTUnXe;
      string RowRmiHihh;
      string EzjRWwzhTt;
      string NRaoUkPNYs;
      string NgAzHYMokB;
      string BFIsqbRSVk;
      string UlUdRzOGwB;
      string SsKoUWzjJy;
      string iJxRrHIhys;
      string TxrmXaMVgH;
      string KFsihIuTXT;
      string cgIWBKoClK;
      string pfIDhVBXQs;
      string JcDCndQNjj;
      string MoJdPmnUkN;
      string lKjWQdxpBM;
      string GXCeKAdGiX;
      if(FGGEDBICjx == SsKoUWzjJy){tbSCxBWdmu = true;}
      else if(SsKoUWzjJy == FGGEDBICjx){fKPZDuqzWe = true;}
      if(lAGGMhVXdZ == iJxRrHIhys){hflDHzsfkJ = true;}
      else if(iJxRrHIhys == lAGGMhVXdZ){uJCXFbjCNa = true;}
      if(NJHXkInqau == TxrmXaMVgH){faLXcnleTP = true;}
      else if(TxrmXaMVgH == NJHXkInqau){mhFjCLDpUm = true;}
      if(bBjrhTUnXe == KFsihIuTXT){IglMTJqhYP = true;}
      else if(KFsihIuTXT == bBjrhTUnXe){ErkOVrXgEN = true;}
      if(RowRmiHihh == cgIWBKoClK){HSCGdakzWL = true;}
      else if(cgIWBKoClK == RowRmiHihh){TMppEjsjKY = true;}
      if(EzjRWwzhTt == pfIDhVBXQs){GxUYrSPuZJ = true;}
      else if(pfIDhVBXQs == EzjRWwzhTt){eFRspyFfWr = true;}
      if(NRaoUkPNYs == JcDCndQNjj){OqKWlAtZjx = true;}
      else if(JcDCndQNjj == NRaoUkPNYs){rAdiZDXnBM = true;}
      if(NgAzHYMokB == MoJdPmnUkN){HLGVCMXFsC = true;}
      if(BFIsqbRSVk == lKjWQdxpBM){DmHIILMMUA = true;}
      if(UlUdRzOGwB == GXCeKAdGiX){twHPAPIfTd = true;}
      while(MoJdPmnUkN == NgAzHYMokB){EDxAGaqOeR = true;}
      while(lKjWQdxpBM == lKjWQdxpBM){RSfwHzZrXX = true;}
      while(GXCeKAdGiX == GXCeKAdGiX){mqJMUTiGPB = true;}
      if(tbSCxBWdmu == true){tbSCxBWdmu = false;}
      if(hflDHzsfkJ == true){hflDHzsfkJ = false;}
      if(faLXcnleTP == true){faLXcnleTP = false;}
      if(IglMTJqhYP == true){IglMTJqhYP = false;}
      if(HSCGdakzWL == true){HSCGdakzWL = false;}
      if(GxUYrSPuZJ == true){GxUYrSPuZJ = false;}
      if(OqKWlAtZjx == true){OqKWlAtZjx = false;}
      if(HLGVCMXFsC == true){HLGVCMXFsC = false;}
      if(DmHIILMMUA == true){DmHIILMMUA = false;}
      if(twHPAPIfTd == true){twHPAPIfTd = false;}
      if(fKPZDuqzWe == true){fKPZDuqzWe = false;}
      if(uJCXFbjCNa == true){uJCXFbjCNa = false;}
      if(mhFjCLDpUm == true){mhFjCLDpUm = false;}
      if(ErkOVrXgEN == true){ErkOVrXgEN = false;}
      if(TMppEjsjKY == true){TMppEjsjKY = false;}
      if(eFRspyFfWr == true){eFRspyFfWr = false;}
      if(rAdiZDXnBM == true){rAdiZDXnBM = false;}
      if(EDxAGaqOeR == true){EDxAGaqOeR = false;}
      if(RSfwHzZrXX == true){RSfwHzZrXX = false;}
      if(mqJMUTiGPB == true){mqJMUTiGPB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXISQPJBQX
{ 
  void fjHFNZYmZc()
  { 
      bool mCkthntmWa = false;
      bool HuGIODCNQY = false;
      bool XqzVoTRxDm = false;
      bool uiDLUhWtQD = false;
      bool GfhAqgXmPa = false;
      bool ZbWNTuDPEN = false;
      bool VwiifYqung = false;
      bool gHxNRqJzdI = false;
      bool uehcNSLpqY = false;
      bool eGoCgJwyTS = false;
      bool ocyhsReJub = false;
      bool lElwRpOGVN = false;
      bool MBDOBaRufI = false;
      bool tKeKSSfziw = false;
      bool nBtOmaUsjp = false;
      bool tpcGFmYifS = false;
      bool zjcmhaYacz = false;
      bool JPXZYLHoba = false;
      bool FYKpNEhXFf = false;
      bool txSPwEYGgL = false;
      string xSbPXDhOFi;
      string PoKldFyJmx;
      string YcVWptfmPM;
      string qhXBjRxeSp;
      string YapLhOuwSW;
      string tgnZtTwEZc;
      string WuzsrgQIBL;
      string HTpxXymKoa;
      string zjTsRJsyHP;
      string UsEpSdbxTA;
      string xluGOaqqBu;
      string glPydmaFah;
      string nSBkpOOAdt;
      string WppncMnMdq;
      string SCwLiidGLf;
      string CVWlMdkJQz;
      string LqMHYqwaUQ;
      string yObiOkWpCH;
      string kInyqATEbz;
      string bewdebpnlq;
      if(xSbPXDhOFi == xluGOaqqBu){mCkthntmWa = true;}
      else if(xluGOaqqBu == xSbPXDhOFi){ocyhsReJub = true;}
      if(PoKldFyJmx == glPydmaFah){HuGIODCNQY = true;}
      else if(glPydmaFah == PoKldFyJmx){lElwRpOGVN = true;}
      if(YcVWptfmPM == nSBkpOOAdt){XqzVoTRxDm = true;}
      else if(nSBkpOOAdt == YcVWptfmPM){MBDOBaRufI = true;}
      if(qhXBjRxeSp == WppncMnMdq){uiDLUhWtQD = true;}
      else if(WppncMnMdq == qhXBjRxeSp){tKeKSSfziw = true;}
      if(YapLhOuwSW == SCwLiidGLf){GfhAqgXmPa = true;}
      else if(SCwLiidGLf == YapLhOuwSW){nBtOmaUsjp = true;}
      if(tgnZtTwEZc == CVWlMdkJQz){ZbWNTuDPEN = true;}
      else if(CVWlMdkJQz == tgnZtTwEZc){tpcGFmYifS = true;}
      if(WuzsrgQIBL == LqMHYqwaUQ){VwiifYqung = true;}
      else if(LqMHYqwaUQ == WuzsrgQIBL){zjcmhaYacz = true;}
      if(HTpxXymKoa == yObiOkWpCH){gHxNRqJzdI = true;}
      if(zjTsRJsyHP == kInyqATEbz){uehcNSLpqY = true;}
      if(UsEpSdbxTA == bewdebpnlq){eGoCgJwyTS = true;}
      while(yObiOkWpCH == HTpxXymKoa){JPXZYLHoba = true;}
      while(kInyqATEbz == kInyqATEbz){FYKpNEhXFf = true;}
      while(bewdebpnlq == bewdebpnlq){txSPwEYGgL = true;}
      if(mCkthntmWa == true){mCkthntmWa = false;}
      if(HuGIODCNQY == true){HuGIODCNQY = false;}
      if(XqzVoTRxDm == true){XqzVoTRxDm = false;}
      if(uiDLUhWtQD == true){uiDLUhWtQD = false;}
      if(GfhAqgXmPa == true){GfhAqgXmPa = false;}
      if(ZbWNTuDPEN == true){ZbWNTuDPEN = false;}
      if(VwiifYqung == true){VwiifYqung = false;}
      if(gHxNRqJzdI == true){gHxNRqJzdI = false;}
      if(uehcNSLpqY == true){uehcNSLpqY = false;}
      if(eGoCgJwyTS == true){eGoCgJwyTS = false;}
      if(ocyhsReJub == true){ocyhsReJub = false;}
      if(lElwRpOGVN == true){lElwRpOGVN = false;}
      if(MBDOBaRufI == true){MBDOBaRufI = false;}
      if(tKeKSSfziw == true){tKeKSSfziw = false;}
      if(nBtOmaUsjp == true){nBtOmaUsjp = false;}
      if(tpcGFmYifS == true){tpcGFmYifS = false;}
      if(zjcmhaYacz == true){zjcmhaYacz = false;}
      if(JPXZYLHoba == true){JPXZYLHoba = false;}
      if(FYKpNEhXFf == true){FYKpNEhXFf = false;}
      if(txSPwEYGgL == true){txSPwEYGgL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAWFPUTCKE
{ 
  void mmwzNSlZAw()
  { 
      bool ThtLQzKfCf = false;
      bool ucSlqKgPUV = false;
      bool hweaMzzxXW = false;
      bool FkcECyNblS = false;
      bool SArRKFiegb = false;
      bool qQHnaWCTzR = false;
      bool ANHfaKzNjs = false;
      bool wEdCCgDNPG = false;
      bool PTQwencnde = false;
      bool uscTSFrMpz = false;
      bool GUunemmFks = false;
      bool TnErBfwLAl = false;
      bool gKjFxDbJix = false;
      bool opXQAtYcQr = false;
      bool BXCkKGojSm = false;
      bool JgMERukppb = false;
      bool KcVnEcQnrG = false;
      bool HTtIjJHytq = false;
      bool NqqwnHdSyE = false;
      bool IhmohYBOfg = false;
      string JoMOXlnyme;
      string UWRCtRhSHE;
      string hAWxMJDhWR;
      string dwDsNPTZSk;
      string MYZocIpETM;
      string KRJOUISOBO;
      string iFaVBXTYnd;
      string xHAWqIZgUE;
      string SyOKGLlnXE;
      string xFXECHxEmE;
      string nRPoOCRmXM;
      string ikswwjpQOo;
      string keAigrjwUi;
      string LVsQPAiYuE;
      string tzQLVLLbHR;
      string QgoySJRfHW;
      string SVSnANqcgu;
      string BQVJulNnNV;
      string fInCSdfuxG;
      string iCRXlYgcKI;
      if(JoMOXlnyme == nRPoOCRmXM){ThtLQzKfCf = true;}
      else if(nRPoOCRmXM == JoMOXlnyme){GUunemmFks = true;}
      if(UWRCtRhSHE == ikswwjpQOo){ucSlqKgPUV = true;}
      else if(ikswwjpQOo == UWRCtRhSHE){TnErBfwLAl = true;}
      if(hAWxMJDhWR == keAigrjwUi){hweaMzzxXW = true;}
      else if(keAigrjwUi == hAWxMJDhWR){gKjFxDbJix = true;}
      if(dwDsNPTZSk == LVsQPAiYuE){FkcECyNblS = true;}
      else if(LVsQPAiYuE == dwDsNPTZSk){opXQAtYcQr = true;}
      if(MYZocIpETM == tzQLVLLbHR){SArRKFiegb = true;}
      else if(tzQLVLLbHR == MYZocIpETM){BXCkKGojSm = true;}
      if(KRJOUISOBO == QgoySJRfHW){qQHnaWCTzR = true;}
      else if(QgoySJRfHW == KRJOUISOBO){JgMERukppb = true;}
      if(iFaVBXTYnd == SVSnANqcgu){ANHfaKzNjs = true;}
      else if(SVSnANqcgu == iFaVBXTYnd){KcVnEcQnrG = true;}
      if(xHAWqIZgUE == BQVJulNnNV){wEdCCgDNPG = true;}
      if(SyOKGLlnXE == fInCSdfuxG){PTQwencnde = true;}
      if(xFXECHxEmE == iCRXlYgcKI){uscTSFrMpz = true;}
      while(BQVJulNnNV == xHAWqIZgUE){HTtIjJHytq = true;}
      while(fInCSdfuxG == fInCSdfuxG){NqqwnHdSyE = true;}
      while(iCRXlYgcKI == iCRXlYgcKI){IhmohYBOfg = true;}
      if(ThtLQzKfCf == true){ThtLQzKfCf = false;}
      if(ucSlqKgPUV == true){ucSlqKgPUV = false;}
      if(hweaMzzxXW == true){hweaMzzxXW = false;}
      if(FkcECyNblS == true){FkcECyNblS = false;}
      if(SArRKFiegb == true){SArRKFiegb = false;}
      if(qQHnaWCTzR == true){qQHnaWCTzR = false;}
      if(ANHfaKzNjs == true){ANHfaKzNjs = false;}
      if(wEdCCgDNPG == true){wEdCCgDNPG = false;}
      if(PTQwencnde == true){PTQwencnde = false;}
      if(uscTSFrMpz == true){uscTSFrMpz = false;}
      if(GUunemmFks == true){GUunemmFks = false;}
      if(TnErBfwLAl == true){TnErBfwLAl = false;}
      if(gKjFxDbJix == true){gKjFxDbJix = false;}
      if(opXQAtYcQr == true){opXQAtYcQr = false;}
      if(BXCkKGojSm == true){BXCkKGojSm = false;}
      if(JgMERukppb == true){JgMERukppb = false;}
      if(KcVnEcQnrG == true){KcVnEcQnrG = false;}
      if(HTtIjJHytq == true){HTtIjJHytq = false;}
      if(NqqwnHdSyE == true){NqqwnHdSyE = false;}
      if(IhmohYBOfg == true){IhmohYBOfg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KKGLJQCAJH
{ 
  void CizEZrBYTZ()
  { 
      bool jfdFiJWyNF = false;
      bool RzhMWDeszU = false;
      bool dYcGDrHamd = false;
      bool kywfLzrXsd = false;
      bool FRRSjRsGWB = false;
      bool OlIbOKDXBq = false;
      bool CuKiUSDCBW = false;
      bool LGzVPMGJVk = false;
      bool yAElOypTQA = false;
      bool wUVCbJGhyR = false;
      bool OqFAoHmmMC = false;
      bool EsBPsCqYTV = false;
      bool cikBZqkxtF = false;
      bool FXLEWGtEwH = false;
      bool LCGOwDSFIY = false;
      bool ShOcneFEay = false;
      bool WpsGwfhwsl = false;
      bool HlbMJZbWFV = false;
      bool XenUmWJiPq = false;
      bool ApdyjVJARP = false;
      string kYXYmVcrKb;
      string RtxGzylmwb;
      string JQasmRRFQa;
      string muiAHGIGbJ;
      string NhxzKlcRkG;
      string NXpaqTxekU;
      string DXajnWKxzs;
      string peKmOaTbhB;
      string oATKMOEIJm;
      string JcVGGoHMKn;
      string aeRrPhMDMP;
      string AUwieCDPWZ;
      string RCmLiMIEgY;
      string SGQtaJibue;
      string CBusmnglaD;
      string kqpkVYrGIC;
      string ZIWmwtEBIU;
      string TbUrXPGsYu;
      string fVccnbPeYC;
      string RbTsEseIxr;
      if(kYXYmVcrKb == aeRrPhMDMP){jfdFiJWyNF = true;}
      else if(aeRrPhMDMP == kYXYmVcrKb){OqFAoHmmMC = true;}
      if(RtxGzylmwb == AUwieCDPWZ){RzhMWDeszU = true;}
      else if(AUwieCDPWZ == RtxGzylmwb){EsBPsCqYTV = true;}
      if(JQasmRRFQa == RCmLiMIEgY){dYcGDrHamd = true;}
      else if(RCmLiMIEgY == JQasmRRFQa){cikBZqkxtF = true;}
      if(muiAHGIGbJ == SGQtaJibue){kywfLzrXsd = true;}
      else if(SGQtaJibue == muiAHGIGbJ){FXLEWGtEwH = true;}
      if(NhxzKlcRkG == CBusmnglaD){FRRSjRsGWB = true;}
      else if(CBusmnglaD == NhxzKlcRkG){LCGOwDSFIY = true;}
      if(NXpaqTxekU == kqpkVYrGIC){OlIbOKDXBq = true;}
      else if(kqpkVYrGIC == NXpaqTxekU){ShOcneFEay = true;}
      if(DXajnWKxzs == ZIWmwtEBIU){CuKiUSDCBW = true;}
      else if(ZIWmwtEBIU == DXajnWKxzs){WpsGwfhwsl = true;}
      if(peKmOaTbhB == TbUrXPGsYu){LGzVPMGJVk = true;}
      if(oATKMOEIJm == fVccnbPeYC){yAElOypTQA = true;}
      if(JcVGGoHMKn == RbTsEseIxr){wUVCbJGhyR = true;}
      while(TbUrXPGsYu == peKmOaTbhB){HlbMJZbWFV = true;}
      while(fVccnbPeYC == fVccnbPeYC){XenUmWJiPq = true;}
      while(RbTsEseIxr == RbTsEseIxr){ApdyjVJARP = true;}
      if(jfdFiJWyNF == true){jfdFiJWyNF = false;}
      if(RzhMWDeszU == true){RzhMWDeszU = false;}
      if(dYcGDrHamd == true){dYcGDrHamd = false;}
      if(kywfLzrXsd == true){kywfLzrXsd = false;}
      if(FRRSjRsGWB == true){FRRSjRsGWB = false;}
      if(OlIbOKDXBq == true){OlIbOKDXBq = false;}
      if(CuKiUSDCBW == true){CuKiUSDCBW = false;}
      if(LGzVPMGJVk == true){LGzVPMGJVk = false;}
      if(yAElOypTQA == true){yAElOypTQA = false;}
      if(wUVCbJGhyR == true){wUVCbJGhyR = false;}
      if(OqFAoHmmMC == true){OqFAoHmmMC = false;}
      if(EsBPsCqYTV == true){EsBPsCqYTV = false;}
      if(cikBZqkxtF == true){cikBZqkxtF = false;}
      if(FXLEWGtEwH == true){FXLEWGtEwH = false;}
      if(LCGOwDSFIY == true){LCGOwDSFIY = false;}
      if(ShOcneFEay == true){ShOcneFEay = false;}
      if(WpsGwfhwsl == true){WpsGwfhwsl = false;}
      if(HlbMJZbWFV == true){HlbMJZbWFV = false;}
      if(XenUmWJiPq == true){XenUmWJiPq = false;}
      if(ApdyjVJARP == true){ApdyjVJARP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEWDRKMTNK
{ 
  void jkBnyGJEMN()
  { 
      bool XLdDrinIVo = false;
      bool fliSqXCCFI = false;
      bool KudtQurVdG = false;
      bool pntDBsQVnD = false;
      bool TDjIHaOyOU = false;
      bool AsUinchimx = false;
      bool qRePyqrfRy = false;
      bool GgOBnHLUlo = false;
      bool ftGIFxTKPY = false;
      bool KghqMBXUKP = false;
      bool iifQNTeSuf = false;
      bool QMxyQwLWJA = false;
      bool XgQsmZyXol = false;
      bool jqKVFxNoul = false;
      bool RBPiHyjjZP = false;
      bool pBKJrCSmdn = false;
      bool UHcIwZBarT = false;
      bool hVaWhWRglo = false;
      bool oNxYuifBdD = false;
      bool daLHRKXGlg = false;
      string yoWntyggMJ;
      string EjzQelqdYd;
      string ifoELUWKLu;
      string DJKFEPGFXq;
      string jPcdmANYHU;
      string KofSIRARbY;
      string bWUQFtYsLP;
      string fkFgtSDLRK;
      string HxCpjOdqxl;
      string PndzPNtLXr;
      string bUMrnZizYo;
      string OoAQRdTdgq;
      string QguZzrHGQg;
      string XqmYimkJCK;
      string fdSIWZmMhk;
      string sPegbtYlrw;
      string SbhrQXBahd;
      string sJbVKlOlDZ;
      string EtYfmHMGxn;
      string NyQGrDwZrz;
      if(yoWntyggMJ == bUMrnZizYo){XLdDrinIVo = true;}
      else if(bUMrnZizYo == yoWntyggMJ){iifQNTeSuf = true;}
      if(EjzQelqdYd == OoAQRdTdgq){fliSqXCCFI = true;}
      else if(OoAQRdTdgq == EjzQelqdYd){QMxyQwLWJA = true;}
      if(ifoELUWKLu == QguZzrHGQg){KudtQurVdG = true;}
      else if(QguZzrHGQg == ifoELUWKLu){XgQsmZyXol = true;}
      if(DJKFEPGFXq == XqmYimkJCK){pntDBsQVnD = true;}
      else if(XqmYimkJCK == DJKFEPGFXq){jqKVFxNoul = true;}
      if(jPcdmANYHU == fdSIWZmMhk){TDjIHaOyOU = true;}
      else if(fdSIWZmMhk == jPcdmANYHU){RBPiHyjjZP = true;}
      if(KofSIRARbY == sPegbtYlrw){AsUinchimx = true;}
      else if(sPegbtYlrw == KofSIRARbY){pBKJrCSmdn = true;}
      if(bWUQFtYsLP == SbhrQXBahd){qRePyqrfRy = true;}
      else if(SbhrQXBahd == bWUQFtYsLP){UHcIwZBarT = true;}
      if(fkFgtSDLRK == sJbVKlOlDZ){GgOBnHLUlo = true;}
      if(HxCpjOdqxl == EtYfmHMGxn){ftGIFxTKPY = true;}
      if(PndzPNtLXr == NyQGrDwZrz){KghqMBXUKP = true;}
      while(sJbVKlOlDZ == fkFgtSDLRK){hVaWhWRglo = true;}
      while(EtYfmHMGxn == EtYfmHMGxn){oNxYuifBdD = true;}
      while(NyQGrDwZrz == NyQGrDwZrz){daLHRKXGlg = true;}
      if(XLdDrinIVo == true){XLdDrinIVo = false;}
      if(fliSqXCCFI == true){fliSqXCCFI = false;}
      if(KudtQurVdG == true){KudtQurVdG = false;}
      if(pntDBsQVnD == true){pntDBsQVnD = false;}
      if(TDjIHaOyOU == true){TDjIHaOyOU = false;}
      if(AsUinchimx == true){AsUinchimx = false;}
      if(qRePyqrfRy == true){qRePyqrfRy = false;}
      if(GgOBnHLUlo == true){GgOBnHLUlo = false;}
      if(ftGIFxTKPY == true){ftGIFxTKPY = false;}
      if(KghqMBXUKP == true){KghqMBXUKP = false;}
      if(iifQNTeSuf == true){iifQNTeSuf = false;}
      if(QMxyQwLWJA == true){QMxyQwLWJA = false;}
      if(XgQsmZyXol == true){XgQsmZyXol = false;}
      if(jqKVFxNoul == true){jqKVFxNoul = false;}
      if(RBPiHyjjZP == true){RBPiHyjjZP = false;}
      if(pBKJrCSmdn == true){pBKJrCSmdn = false;}
      if(UHcIwZBarT == true){UHcIwZBarT = false;}
      if(hVaWhWRglo == true){hVaWhWRglo = false;}
      if(oNxYuifBdD == true){oNxYuifBdD = false;}
      if(daLHRKXGlg == true){daLHRKXGlg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LXCWOLAUBS
{ 
  void tnEqurjTux()
  { 
      bool bzOBAXJMTP = false;
      bool dtdKPiOFpV = false;
      bool VlVRqbZLAc = false;
      bool KaUOWXlCxN = false;
      bool qpLwNrTmnN = false;
      bool LETcbpcwJY = false;
      bool yxLpECZOmr = false;
      bool xMIbefaZDz = false;
      bool HlXmRFHqlg = false;
      bool torYOsdUqK = false;
      bool REAuQzwqyw = false;
      bool PDsKQLYYYy = false;
      bool uhcGxITjMk = false;
      bool BFirhClcVS = false;
      bool JQsoQquhHD = false;
      bool TEurPibtxI = false;
      bool eMdMuJTAbO = false;
      bool ZwDGodonoG = false;
      bool MlbJQxKpcy = false;
      bool ZreNnwlftH = false;
      string LcSABJMakr;
      string FaauJeLrac;
      string UTlSqQhUoN;
      string xdLTCDMywP;
      string TQNOyzLTII;
      string WAmRBrqzIj;
      string brlWtbPHsF;
      string RNwLJEFWTq;
      string ENLgpxpsSJ;
      string MMoLmbdqUW;
      string jDZDqIDbIw;
      string mTfQeNfFfx;
      string kVojsEYjXg;
      string ZNCxHBnIph;
      string sOkVWsgXfZ;
      string uYLXlOOpKl;
      string jSDaWYQhJd;
      string ZXPyDVjTMz;
      string WAExkACeLr;
      string lxyDxZKJyy;
      if(LcSABJMakr == jDZDqIDbIw){bzOBAXJMTP = true;}
      else if(jDZDqIDbIw == LcSABJMakr){REAuQzwqyw = true;}
      if(FaauJeLrac == mTfQeNfFfx){dtdKPiOFpV = true;}
      else if(mTfQeNfFfx == FaauJeLrac){PDsKQLYYYy = true;}
      if(UTlSqQhUoN == kVojsEYjXg){VlVRqbZLAc = true;}
      else if(kVojsEYjXg == UTlSqQhUoN){uhcGxITjMk = true;}
      if(xdLTCDMywP == ZNCxHBnIph){KaUOWXlCxN = true;}
      else if(ZNCxHBnIph == xdLTCDMywP){BFirhClcVS = true;}
      if(TQNOyzLTII == sOkVWsgXfZ){qpLwNrTmnN = true;}
      else if(sOkVWsgXfZ == TQNOyzLTII){JQsoQquhHD = true;}
      if(WAmRBrqzIj == uYLXlOOpKl){LETcbpcwJY = true;}
      else if(uYLXlOOpKl == WAmRBrqzIj){TEurPibtxI = true;}
      if(brlWtbPHsF == jSDaWYQhJd){yxLpECZOmr = true;}
      else if(jSDaWYQhJd == brlWtbPHsF){eMdMuJTAbO = true;}
      if(RNwLJEFWTq == ZXPyDVjTMz){xMIbefaZDz = true;}
      if(ENLgpxpsSJ == WAExkACeLr){HlXmRFHqlg = true;}
      if(MMoLmbdqUW == lxyDxZKJyy){torYOsdUqK = true;}
      while(ZXPyDVjTMz == RNwLJEFWTq){ZwDGodonoG = true;}
      while(WAExkACeLr == WAExkACeLr){MlbJQxKpcy = true;}
      while(lxyDxZKJyy == lxyDxZKJyy){ZreNnwlftH = true;}
      if(bzOBAXJMTP == true){bzOBAXJMTP = false;}
      if(dtdKPiOFpV == true){dtdKPiOFpV = false;}
      if(VlVRqbZLAc == true){VlVRqbZLAc = false;}
      if(KaUOWXlCxN == true){KaUOWXlCxN = false;}
      if(qpLwNrTmnN == true){qpLwNrTmnN = false;}
      if(LETcbpcwJY == true){LETcbpcwJY = false;}
      if(yxLpECZOmr == true){yxLpECZOmr = false;}
      if(xMIbefaZDz == true){xMIbefaZDz = false;}
      if(HlXmRFHqlg == true){HlXmRFHqlg = false;}
      if(torYOsdUqK == true){torYOsdUqK = false;}
      if(REAuQzwqyw == true){REAuQzwqyw = false;}
      if(PDsKQLYYYy == true){PDsKQLYYYy = false;}
      if(uhcGxITjMk == true){uhcGxITjMk = false;}
      if(BFirhClcVS == true){BFirhClcVS = false;}
      if(JQsoQquhHD == true){JQsoQquhHD = false;}
      if(TEurPibtxI == true){TEurPibtxI = false;}
      if(eMdMuJTAbO == true){eMdMuJTAbO = false;}
      if(ZwDGodonoG == true){ZwDGodonoG = false;}
      if(MlbJQxKpcy == true){MlbJQxKpcy = false;}
      if(ZreNnwlftH == true){ZreNnwlftH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQHZSJIINV
{ 
  void zgAQwwFqZM()
  { 
      bool XSHskuhAfN = false;
      bool skCQSgcREV = false;
      bool PjfDiKblJi = false;
      bool kPmjHkYYke = false;
      bool NPMBetbgZo = false;
      bool oIFfLnmDKZ = false;
      bool SuqwbdxSIg = false;
      bool IEfZHzXdXo = false;
      bool htMTsbJHYT = false;
      bool yUNKLRYPZB = false;
      bool wJYsgkcfXL = false;
      bool PJeVrYiXDz = false;
      bool TptnhmpUNp = false;
      bool ZIDWrYUTlH = false;
      bool zdiMEoorSm = false;
      bool hBLZhGOjKt = false;
      bool tHRhkGFIcS = false;
      bool DPkuzpGgjs = false;
      bool xyCZHYwdnl = false;
      bool JkIqNrLBax = false;
      string ljikbOcJiB;
      string MHbGHlPiYS;
      string QQNKqUGjKH;
      string DnacFYVxhR;
      string hDXsWPggMF;
      string uVpKlUVXtH;
      string IrybxXfyBi;
      string QSAGjNrUna;
      string mYXEMhxPqj;
      string CxCaJoFuwz;
      string ihfcocUjZY;
      string cBjTTiUsPO;
      string ZPHRgSPZwu;
      string HwYoqFstOj;
      string NNpSGANiHa;
      string ULfgYSZNwW;
      string MumeQfbubN;
      string pZdfBLZoKf;
      string EfRVZuQrPX;
      string eeyrWSZKBa;
      if(ljikbOcJiB == ihfcocUjZY){XSHskuhAfN = true;}
      else if(ihfcocUjZY == ljikbOcJiB){wJYsgkcfXL = true;}
      if(MHbGHlPiYS == cBjTTiUsPO){skCQSgcREV = true;}
      else if(cBjTTiUsPO == MHbGHlPiYS){PJeVrYiXDz = true;}
      if(QQNKqUGjKH == ZPHRgSPZwu){PjfDiKblJi = true;}
      else if(ZPHRgSPZwu == QQNKqUGjKH){TptnhmpUNp = true;}
      if(DnacFYVxhR == HwYoqFstOj){kPmjHkYYke = true;}
      else if(HwYoqFstOj == DnacFYVxhR){ZIDWrYUTlH = true;}
      if(hDXsWPggMF == NNpSGANiHa){NPMBetbgZo = true;}
      else if(NNpSGANiHa == hDXsWPggMF){zdiMEoorSm = true;}
      if(uVpKlUVXtH == ULfgYSZNwW){oIFfLnmDKZ = true;}
      else if(ULfgYSZNwW == uVpKlUVXtH){hBLZhGOjKt = true;}
      if(IrybxXfyBi == MumeQfbubN){SuqwbdxSIg = true;}
      else if(MumeQfbubN == IrybxXfyBi){tHRhkGFIcS = true;}
      if(QSAGjNrUna == pZdfBLZoKf){IEfZHzXdXo = true;}
      if(mYXEMhxPqj == EfRVZuQrPX){htMTsbJHYT = true;}
      if(CxCaJoFuwz == eeyrWSZKBa){yUNKLRYPZB = true;}
      while(pZdfBLZoKf == QSAGjNrUna){DPkuzpGgjs = true;}
      while(EfRVZuQrPX == EfRVZuQrPX){xyCZHYwdnl = true;}
      while(eeyrWSZKBa == eeyrWSZKBa){JkIqNrLBax = true;}
      if(XSHskuhAfN == true){XSHskuhAfN = false;}
      if(skCQSgcREV == true){skCQSgcREV = false;}
      if(PjfDiKblJi == true){PjfDiKblJi = false;}
      if(kPmjHkYYke == true){kPmjHkYYke = false;}
      if(NPMBetbgZo == true){NPMBetbgZo = false;}
      if(oIFfLnmDKZ == true){oIFfLnmDKZ = false;}
      if(SuqwbdxSIg == true){SuqwbdxSIg = false;}
      if(IEfZHzXdXo == true){IEfZHzXdXo = false;}
      if(htMTsbJHYT == true){htMTsbJHYT = false;}
      if(yUNKLRYPZB == true){yUNKLRYPZB = false;}
      if(wJYsgkcfXL == true){wJYsgkcfXL = false;}
      if(PJeVrYiXDz == true){PJeVrYiXDz = false;}
      if(TptnhmpUNp == true){TptnhmpUNp = false;}
      if(ZIDWrYUTlH == true){ZIDWrYUTlH = false;}
      if(zdiMEoorSm == true){zdiMEoorSm = false;}
      if(hBLZhGOjKt == true){hBLZhGOjKt = false;}
      if(tHRhkGFIcS == true){tHRhkGFIcS = false;}
      if(DPkuzpGgjs == true){DPkuzpGgjs = false;}
      if(xyCZHYwdnl == true){xyCZHYwdnl = false;}
      if(JkIqNrLBax == true){JkIqNrLBax = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUWVYMORSB
{ 
  void fVjdyMoyfd()
  { 
      bool OGGsRmjlhn = false;
      bool PXMlpOYrqU = false;
      bool facgDxPkUM = false;
      bool eeIIzhVmbH = false;
      bool UmqaVlFSPD = false;
      bool ErWuxndZpT = false;
      bool XzQVIjPEmH = false;
      bool slPizsiBKQ = false;
      bool qwURHmHMLL = false;
      bool EwxHjVVURl = false;
      bool WBfIKSbnwD = false;
      bool EbPYcadzNV = false;
      bool bDsbDwnIzd = false;
      bool XNiXtpPMGo = false;
      bool KTQHGbgXdI = false;
      bool qVHwKSHEFN = false;
      bool dSoRfpsqem = false;
      bool LRrYKHlkUa = false;
      bool PQdplBGmMa = false;
      bool hKHsLqeybQ = false;
      string kwjrfqGrow;
      string HoqiCUkkdU;
      string NEARgpUAOl;
      string qmIgWKZxSm;
      string mfdCJiVgSL;
      string gMEVlgwRKo;
      string WGdDEUfJMq;
      string tnRqhgaxHx;
      string TmgCEeimup;
      string OHlcQgCZyo;
      string CLUbRstMmE;
      string GzJNViYbzZ;
      string lsOVclBnaB;
      string eAySuHSEkK;
      string jVzpjOxYHh;
      string HaaYDJxzze;
      string rGkkZFAqSN;
      string PUpnpPsYlN;
      string ncgstEZZOl;
      string KSFFSdjOQd;
      if(kwjrfqGrow == CLUbRstMmE){OGGsRmjlhn = true;}
      else if(CLUbRstMmE == kwjrfqGrow){WBfIKSbnwD = true;}
      if(HoqiCUkkdU == GzJNViYbzZ){PXMlpOYrqU = true;}
      else if(GzJNViYbzZ == HoqiCUkkdU){EbPYcadzNV = true;}
      if(NEARgpUAOl == lsOVclBnaB){facgDxPkUM = true;}
      else if(lsOVclBnaB == NEARgpUAOl){bDsbDwnIzd = true;}
      if(qmIgWKZxSm == eAySuHSEkK){eeIIzhVmbH = true;}
      else if(eAySuHSEkK == qmIgWKZxSm){XNiXtpPMGo = true;}
      if(mfdCJiVgSL == jVzpjOxYHh){UmqaVlFSPD = true;}
      else if(jVzpjOxYHh == mfdCJiVgSL){KTQHGbgXdI = true;}
      if(gMEVlgwRKo == HaaYDJxzze){ErWuxndZpT = true;}
      else if(HaaYDJxzze == gMEVlgwRKo){qVHwKSHEFN = true;}
      if(WGdDEUfJMq == rGkkZFAqSN){XzQVIjPEmH = true;}
      else if(rGkkZFAqSN == WGdDEUfJMq){dSoRfpsqem = true;}
      if(tnRqhgaxHx == PUpnpPsYlN){slPizsiBKQ = true;}
      if(TmgCEeimup == ncgstEZZOl){qwURHmHMLL = true;}
      if(OHlcQgCZyo == KSFFSdjOQd){EwxHjVVURl = true;}
      while(PUpnpPsYlN == tnRqhgaxHx){LRrYKHlkUa = true;}
      while(ncgstEZZOl == ncgstEZZOl){PQdplBGmMa = true;}
      while(KSFFSdjOQd == KSFFSdjOQd){hKHsLqeybQ = true;}
      if(OGGsRmjlhn == true){OGGsRmjlhn = false;}
      if(PXMlpOYrqU == true){PXMlpOYrqU = false;}
      if(facgDxPkUM == true){facgDxPkUM = false;}
      if(eeIIzhVmbH == true){eeIIzhVmbH = false;}
      if(UmqaVlFSPD == true){UmqaVlFSPD = false;}
      if(ErWuxndZpT == true){ErWuxndZpT = false;}
      if(XzQVIjPEmH == true){XzQVIjPEmH = false;}
      if(slPizsiBKQ == true){slPizsiBKQ = false;}
      if(qwURHmHMLL == true){qwURHmHMLL = false;}
      if(EwxHjVVURl == true){EwxHjVVURl = false;}
      if(WBfIKSbnwD == true){WBfIKSbnwD = false;}
      if(EbPYcadzNV == true){EbPYcadzNV = false;}
      if(bDsbDwnIzd == true){bDsbDwnIzd = false;}
      if(XNiXtpPMGo == true){XNiXtpPMGo = false;}
      if(KTQHGbgXdI == true){KTQHGbgXdI = false;}
      if(qVHwKSHEFN == true){qVHwKSHEFN = false;}
      if(dSoRfpsqem == true){dSoRfpsqem = false;}
      if(LRrYKHlkUa == true){LRrYKHlkUa = false;}
      if(PQdplBGmMa == true){PQdplBGmMa = false;}
      if(hKHsLqeybQ == true){hKHsLqeybQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMBPKZCMCE
{ 
  void zILPZzuHPb()
  { 
      bool zsQZwhtQIK = false;
      bool ZrXCDXIPCn = false;
      bool ffncCUkFbs = false;
      bool WUFaqczDuH = false;
      bool AsQONHKdGg = false;
      bool wTzmTSFmWb = false;
      bool wonOnElxLa = false;
      bool XEUunmOYPu = false;
      bool JGzuxCVRHX = false;
      bool WMfSLLEBZI = false;
      bool UNSfIqzEzg = false;
      bool EfWbRoosRl = false;
      bool iTomDLXCic = false;
      bool hMyHZwnTlG = false;
      bool DRSZTqoEAV = false;
      bool VKjnZAXfbw = false;
      bool SxUWyqgPBV = false;
      bool BVGLiQBPTM = false;
      bool WTBNGWcKhY = false;
      bool XIqomFxwbb = false;
      string iNhHWwtNGK;
      string QisOwQSkBc;
      string HIxSGCNocA;
      string mYpAMIbjZV;
      string wsdTJHKQbq;
      string TDfOBaQOBU;
      string iEjGXrsrBn;
      string ohLegNecJz;
      string rxNkfirbzk;
      string rMiFlqIXwR;
      string OSOnClrAgn;
      string wmFBblqyZo;
      string zQrPucyGro;
      string EGgrkZhYis;
      string prtLoFGhcA;
      string zJxHRxZyrY;
      string nlHrioFNQC;
      string DRPgyGWgap;
      string VQcrotJZZm;
      string zigJEEjBbz;
      if(iNhHWwtNGK == OSOnClrAgn){zsQZwhtQIK = true;}
      else if(OSOnClrAgn == iNhHWwtNGK){UNSfIqzEzg = true;}
      if(QisOwQSkBc == wmFBblqyZo){ZrXCDXIPCn = true;}
      else if(wmFBblqyZo == QisOwQSkBc){EfWbRoosRl = true;}
      if(HIxSGCNocA == zQrPucyGro){ffncCUkFbs = true;}
      else if(zQrPucyGro == HIxSGCNocA){iTomDLXCic = true;}
      if(mYpAMIbjZV == EGgrkZhYis){WUFaqczDuH = true;}
      else if(EGgrkZhYis == mYpAMIbjZV){hMyHZwnTlG = true;}
      if(wsdTJHKQbq == prtLoFGhcA){AsQONHKdGg = true;}
      else if(prtLoFGhcA == wsdTJHKQbq){DRSZTqoEAV = true;}
      if(TDfOBaQOBU == zJxHRxZyrY){wTzmTSFmWb = true;}
      else if(zJxHRxZyrY == TDfOBaQOBU){VKjnZAXfbw = true;}
      if(iEjGXrsrBn == nlHrioFNQC){wonOnElxLa = true;}
      else if(nlHrioFNQC == iEjGXrsrBn){SxUWyqgPBV = true;}
      if(ohLegNecJz == DRPgyGWgap){XEUunmOYPu = true;}
      if(rxNkfirbzk == VQcrotJZZm){JGzuxCVRHX = true;}
      if(rMiFlqIXwR == zigJEEjBbz){WMfSLLEBZI = true;}
      while(DRPgyGWgap == ohLegNecJz){BVGLiQBPTM = true;}
      while(VQcrotJZZm == VQcrotJZZm){WTBNGWcKhY = true;}
      while(zigJEEjBbz == zigJEEjBbz){XIqomFxwbb = true;}
      if(zsQZwhtQIK == true){zsQZwhtQIK = false;}
      if(ZrXCDXIPCn == true){ZrXCDXIPCn = false;}
      if(ffncCUkFbs == true){ffncCUkFbs = false;}
      if(WUFaqczDuH == true){WUFaqczDuH = false;}
      if(AsQONHKdGg == true){AsQONHKdGg = false;}
      if(wTzmTSFmWb == true){wTzmTSFmWb = false;}
      if(wonOnElxLa == true){wonOnElxLa = false;}
      if(XEUunmOYPu == true){XEUunmOYPu = false;}
      if(JGzuxCVRHX == true){JGzuxCVRHX = false;}
      if(WMfSLLEBZI == true){WMfSLLEBZI = false;}
      if(UNSfIqzEzg == true){UNSfIqzEzg = false;}
      if(EfWbRoosRl == true){EfWbRoosRl = false;}
      if(iTomDLXCic == true){iTomDLXCic = false;}
      if(hMyHZwnTlG == true){hMyHZwnTlG = false;}
      if(DRSZTqoEAV == true){DRSZTqoEAV = false;}
      if(VKjnZAXfbw == true){VKjnZAXfbw = false;}
      if(SxUWyqgPBV == true){SxUWyqgPBV = false;}
      if(BVGLiQBPTM == true){BVGLiQBPTM = false;}
      if(WTBNGWcKhY == true){WTBNGWcKhY = false;}
      if(XIqomFxwbb == true){XIqomFxwbb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XFTHCAVAVN
{ 
  void uQrklkCDMS()
  { 
      bool GSGuwWPUzJ = false;
      bool FJrlYibqeW = false;
      bool OOkBNrjBtu = false;
      bool fmtwPUrNse = false;
      bool fgRoKIxkYJ = false;
      bool OnLYprhEhE = false;
      bool lOaDdSOwVE = false;
      bool pOyzqhwuqF = false;
      bool tzbkgrbVFW = false;
      bool lmforRFNLq = false;
      bool sAOUSzpLgI = false;
      bool umNbJmlpWk = false;
      bool pspzRDiJGZ = false;
      bool biizLskHRg = false;
      bool BQnxbzZDeF = false;
      bool eOqZBAKODO = false;
      bool QgEHfMDNPP = false;
      bool BdXoiZEsWR = false;
      bool cedBtNqIyL = false;
      bool iVECQUMgQP = false;
      string usuRnnWong;
      string yiCSgSJtOs;
      string hpKgMWcoQw;
      string XSuFADUwnD;
      string xyLIWZBfsB;
      string RaIJNFiOFR;
      string LgYqJfmxRc;
      string xNGKwjeBKm;
      string UwuOewJkru;
      string UGpWrPYUyq;
      string lEOQDEUyNc;
      string ahDSwOlJMN;
      string VCEVIqWjRf;
      string KJCTAQheKZ;
      string bLXOUlDXac;
      string dOHkUjzrHM;
      string hkfgSQfjRe;
      string gHzllKdpAV;
      string nyIoCuCQzQ;
      string RoWxrpepuE;
      if(usuRnnWong == lEOQDEUyNc){GSGuwWPUzJ = true;}
      else if(lEOQDEUyNc == usuRnnWong){sAOUSzpLgI = true;}
      if(yiCSgSJtOs == ahDSwOlJMN){FJrlYibqeW = true;}
      else if(ahDSwOlJMN == yiCSgSJtOs){umNbJmlpWk = true;}
      if(hpKgMWcoQw == VCEVIqWjRf){OOkBNrjBtu = true;}
      else if(VCEVIqWjRf == hpKgMWcoQw){pspzRDiJGZ = true;}
      if(XSuFADUwnD == KJCTAQheKZ){fmtwPUrNse = true;}
      else if(KJCTAQheKZ == XSuFADUwnD){biizLskHRg = true;}
      if(xyLIWZBfsB == bLXOUlDXac){fgRoKIxkYJ = true;}
      else if(bLXOUlDXac == xyLIWZBfsB){BQnxbzZDeF = true;}
      if(RaIJNFiOFR == dOHkUjzrHM){OnLYprhEhE = true;}
      else if(dOHkUjzrHM == RaIJNFiOFR){eOqZBAKODO = true;}
      if(LgYqJfmxRc == hkfgSQfjRe){lOaDdSOwVE = true;}
      else if(hkfgSQfjRe == LgYqJfmxRc){QgEHfMDNPP = true;}
      if(xNGKwjeBKm == gHzllKdpAV){pOyzqhwuqF = true;}
      if(UwuOewJkru == nyIoCuCQzQ){tzbkgrbVFW = true;}
      if(UGpWrPYUyq == RoWxrpepuE){lmforRFNLq = true;}
      while(gHzllKdpAV == xNGKwjeBKm){BdXoiZEsWR = true;}
      while(nyIoCuCQzQ == nyIoCuCQzQ){cedBtNqIyL = true;}
      while(RoWxrpepuE == RoWxrpepuE){iVECQUMgQP = true;}
      if(GSGuwWPUzJ == true){GSGuwWPUzJ = false;}
      if(FJrlYibqeW == true){FJrlYibqeW = false;}
      if(OOkBNrjBtu == true){OOkBNrjBtu = false;}
      if(fmtwPUrNse == true){fmtwPUrNse = false;}
      if(fgRoKIxkYJ == true){fgRoKIxkYJ = false;}
      if(OnLYprhEhE == true){OnLYprhEhE = false;}
      if(lOaDdSOwVE == true){lOaDdSOwVE = false;}
      if(pOyzqhwuqF == true){pOyzqhwuqF = false;}
      if(tzbkgrbVFW == true){tzbkgrbVFW = false;}
      if(lmforRFNLq == true){lmforRFNLq = false;}
      if(sAOUSzpLgI == true){sAOUSzpLgI = false;}
      if(umNbJmlpWk == true){umNbJmlpWk = false;}
      if(pspzRDiJGZ == true){pspzRDiJGZ = false;}
      if(biizLskHRg == true){biizLskHRg = false;}
      if(BQnxbzZDeF == true){BQnxbzZDeF = false;}
      if(eOqZBAKODO == true){eOqZBAKODO = false;}
      if(QgEHfMDNPP == true){QgEHfMDNPP = false;}
      if(BdXoiZEsWR == true){BdXoiZEsWR = false;}
      if(cedBtNqIyL == true){cedBtNqIyL = false;}
      if(iVECQUMgQP == true){iVECQUMgQP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPXCJOYBKI
{ 
  void lYRpzHiriP()
  { 
      bool mOJYzXPUwc = false;
      bool iJFkyqdrWw = false;
      bool IFSXRRDZRW = false;
      bool qxLMhdQsZh = false;
      bool cLQTwUQRsu = false;
      bool JuAjMhukHh = false;
      bool ToDZlkyrCT = false;
      bool ajSnTwozbx = false;
      bool AkgVMuwaAA = false;
      bool ielqOmIphK = false;
      bool VXOYTZbMQP = false;
      bool rwJJghIgNp = false;
      bool oWrCkuxaZf = false;
      bool nyRRabVHCm = false;
      bool TjKkHmVcJf = false;
      bool ebcrVzfMnY = false;
      bool bAljbtdqhF = false;
      bool LBeaVEMGty = false;
      bool YURtBLUZub = false;
      bool wJScKSxZJN = false;
      string WNSKpUHhUV;
      string flEphgfQeh;
      string knzFPObziB;
      string AMDFoJLtbf;
      string DeAYKHQhGk;
      string qbdqUiONtb;
      string rIySUShzAX;
      string VlozeFmZtI;
      string xsryJXiMkG;
      string uxzzmtghEq;
      string YQhiPFmdMO;
      string unSldzQAIw;
      string jUOsbXmoMj;
      string YFVDigKJiE;
      string kFAVKGdMVm;
      string dgYHHDCnGq;
      string RxRbooSPDw;
      string nGQEKeUrhV;
      string sZSYFrgNwe;
      string dWDqlnmXgU;
      if(WNSKpUHhUV == YQhiPFmdMO){mOJYzXPUwc = true;}
      else if(YQhiPFmdMO == WNSKpUHhUV){VXOYTZbMQP = true;}
      if(flEphgfQeh == unSldzQAIw){iJFkyqdrWw = true;}
      else if(unSldzQAIw == flEphgfQeh){rwJJghIgNp = true;}
      if(knzFPObziB == jUOsbXmoMj){IFSXRRDZRW = true;}
      else if(jUOsbXmoMj == knzFPObziB){oWrCkuxaZf = true;}
      if(AMDFoJLtbf == YFVDigKJiE){qxLMhdQsZh = true;}
      else if(YFVDigKJiE == AMDFoJLtbf){nyRRabVHCm = true;}
      if(DeAYKHQhGk == kFAVKGdMVm){cLQTwUQRsu = true;}
      else if(kFAVKGdMVm == DeAYKHQhGk){TjKkHmVcJf = true;}
      if(qbdqUiONtb == dgYHHDCnGq){JuAjMhukHh = true;}
      else if(dgYHHDCnGq == qbdqUiONtb){ebcrVzfMnY = true;}
      if(rIySUShzAX == RxRbooSPDw){ToDZlkyrCT = true;}
      else if(RxRbooSPDw == rIySUShzAX){bAljbtdqhF = true;}
      if(VlozeFmZtI == nGQEKeUrhV){ajSnTwozbx = true;}
      if(xsryJXiMkG == sZSYFrgNwe){AkgVMuwaAA = true;}
      if(uxzzmtghEq == dWDqlnmXgU){ielqOmIphK = true;}
      while(nGQEKeUrhV == VlozeFmZtI){LBeaVEMGty = true;}
      while(sZSYFrgNwe == sZSYFrgNwe){YURtBLUZub = true;}
      while(dWDqlnmXgU == dWDqlnmXgU){wJScKSxZJN = true;}
      if(mOJYzXPUwc == true){mOJYzXPUwc = false;}
      if(iJFkyqdrWw == true){iJFkyqdrWw = false;}
      if(IFSXRRDZRW == true){IFSXRRDZRW = false;}
      if(qxLMhdQsZh == true){qxLMhdQsZh = false;}
      if(cLQTwUQRsu == true){cLQTwUQRsu = false;}
      if(JuAjMhukHh == true){JuAjMhukHh = false;}
      if(ToDZlkyrCT == true){ToDZlkyrCT = false;}
      if(ajSnTwozbx == true){ajSnTwozbx = false;}
      if(AkgVMuwaAA == true){AkgVMuwaAA = false;}
      if(ielqOmIphK == true){ielqOmIphK = false;}
      if(VXOYTZbMQP == true){VXOYTZbMQP = false;}
      if(rwJJghIgNp == true){rwJJghIgNp = false;}
      if(oWrCkuxaZf == true){oWrCkuxaZf = false;}
      if(nyRRabVHCm == true){nyRRabVHCm = false;}
      if(TjKkHmVcJf == true){TjKkHmVcJf = false;}
      if(ebcrVzfMnY == true){ebcrVzfMnY = false;}
      if(bAljbtdqhF == true){bAljbtdqhF = false;}
      if(LBeaVEMGty == true){LBeaVEMGty = false;}
      if(YURtBLUZub == true){YURtBLUZub = false;}
      if(wJScKSxZJN == true){wJScKSxZJN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMATGJXLDI
{ 
  void BzAgsssRMJ()
  { 
      bool EuQefgOBHg = false;
      bool dwohBNrjog = false;
      bool CHghJFeXFL = false;
      bool elHIetLXmr = false;
      bool hNEZsfrEQM = false;
      bool lLOVcwNiVa = false;
      bool BquwCrngDH = false;
      bool CTwxyoDHnc = false;
      bool NaGsZSWleh = false;
      bool fcCMppRIWB = false;
      bool rKAIKRORWn = false;
      bool sGurNajCWj = false;
      bool UCBUaZRjHI = false;
      bool WtjmkCZyhH = false;
      bool DFOqoZhJyO = false;
      bool GPlmfoJfhk = false;
      bool AeJOQzVHHL = false;
      bool BlTOfPnKfB = false;
      bool rHlrBHHwGu = false;
      bool rsPxGYuzZo = false;
      string MHEgxNYlST;
      string HtJJcGIAwQ;
      string qQzAMqoVIO;
      string MohDJNrosp;
      string XikWBpGOpg;
      string IWxdowIDUG;
      string YCcEHSMGzO;
      string OSGFrIebyV;
      string jZfbGpqDNN;
      string FnUmRUFgPi;
      string dAOaRoPqkg;
      string QfEyVyWAyQ;
      string aIrkIZyTmW;
      string CyLPrjKEKQ;
      string ZASgxYjVQT;
      string yFiyIUHcRr;
      string puDNdRUoFl;
      string mRpgpapKni;
      string pbDTYxPMHX;
      string cgmSaewEDe;
      if(MHEgxNYlST == dAOaRoPqkg){EuQefgOBHg = true;}
      else if(dAOaRoPqkg == MHEgxNYlST){rKAIKRORWn = true;}
      if(HtJJcGIAwQ == QfEyVyWAyQ){dwohBNrjog = true;}
      else if(QfEyVyWAyQ == HtJJcGIAwQ){sGurNajCWj = true;}
      if(qQzAMqoVIO == aIrkIZyTmW){CHghJFeXFL = true;}
      else if(aIrkIZyTmW == qQzAMqoVIO){UCBUaZRjHI = true;}
      if(MohDJNrosp == CyLPrjKEKQ){elHIetLXmr = true;}
      else if(CyLPrjKEKQ == MohDJNrosp){WtjmkCZyhH = true;}
      if(XikWBpGOpg == ZASgxYjVQT){hNEZsfrEQM = true;}
      else if(ZASgxYjVQT == XikWBpGOpg){DFOqoZhJyO = true;}
      if(IWxdowIDUG == yFiyIUHcRr){lLOVcwNiVa = true;}
      else if(yFiyIUHcRr == IWxdowIDUG){GPlmfoJfhk = true;}
      if(YCcEHSMGzO == puDNdRUoFl){BquwCrngDH = true;}
      else if(puDNdRUoFl == YCcEHSMGzO){AeJOQzVHHL = true;}
      if(OSGFrIebyV == mRpgpapKni){CTwxyoDHnc = true;}
      if(jZfbGpqDNN == pbDTYxPMHX){NaGsZSWleh = true;}
      if(FnUmRUFgPi == cgmSaewEDe){fcCMppRIWB = true;}
      while(mRpgpapKni == OSGFrIebyV){BlTOfPnKfB = true;}
      while(pbDTYxPMHX == pbDTYxPMHX){rHlrBHHwGu = true;}
      while(cgmSaewEDe == cgmSaewEDe){rsPxGYuzZo = true;}
      if(EuQefgOBHg == true){EuQefgOBHg = false;}
      if(dwohBNrjog == true){dwohBNrjog = false;}
      if(CHghJFeXFL == true){CHghJFeXFL = false;}
      if(elHIetLXmr == true){elHIetLXmr = false;}
      if(hNEZsfrEQM == true){hNEZsfrEQM = false;}
      if(lLOVcwNiVa == true){lLOVcwNiVa = false;}
      if(BquwCrngDH == true){BquwCrngDH = false;}
      if(CTwxyoDHnc == true){CTwxyoDHnc = false;}
      if(NaGsZSWleh == true){NaGsZSWleh = false;}
      if(fcCMppRIWB == true){fcCMppRIWB = false;}
      if(rKAIKRORWn == true){rKAIKRORWn = false;}
      if(sGurNajCWj == true){sGurNajCWj = false;}
      if(UCBUaZRjHI == true){UCBUaZRjHI = false;}
      if(WtjmkCZyhH == true){WtjmkCZyhH = false;}
      if(DFOqoZhJyO == true){DFOqoZhJyO = false;}
      if(GPlmfoJfhk == true){GPlmfoJfhk = false;}
      if(AeJOQzVHHL == true){AeJOQzVHHL = false;}
      if(BlTOfPnKfB == true){BlTOfPnKfB = false;}
      if(rHlrBHHwGu == true){rHlrBHHwGu = false;}
      if(rsPxGYuzZo == true){rsPxGYuzZo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTIVXEOWFA
{ 
  void zJWhAYOBxy()
  { 
      bool FBwiHTeQHm = false;
      bool aDgNwqbtTa = false;
      bool dqlIbZQkYA = false;
      bool xbRujitTdb = false;
      bool PwWeFzZlXC = false;
      bool rBgAHOPmHh = false;
      bool DtqGozlkcN = false;
      bool wIPrLhTGDb = false;
      bool zdMVIwtQnV = false;
      bool THLwYVEQpF = false;
      bool NnJKGjlooY = false;
      bool tIiehYgVys = false;
      bool FUxGsowSTp = false;
      bool dDQxOLUCPX = false;
      bool JEbPbKXgOz = false;
      bool nhRwArqCQQ = false;
      bool nSUytprkPW = false;
      bool EeFZjAsgei = false;
      bool QOETBulUxW = false;
      bool TRkyjpjcUk = false;
      string jDZAngOuGb;
      string GJNuFeGaur;
      string AaWNrTnRJe;
      string ICAWXjYTOg;
      string DdERIIeuqg;
      string uKTkXJgLIU;
      string swkbTEJpXU;
      string GlMNnWWEFi;
      string oraciyhOyO;
      string DNKtnHrbyE;
      string znXVaIxFxA;
      string lbGZeAVHsV;
      string WtqJRrbRZg;
      string euGAjAUECa;
      string AbRybaHkOm;
      string kjichExNEh;
      string gffPVqUFoe;
      string fQFRUtcsgp;
      string kpDlutMdSf;
      string DGAUsUwBbk;
      if(jDZAngOuGb == znXVaIxFxA){FBwiHTeQHm = true;}
      else if(znXVaIxFxA == jDZAngOuGb){NnJKGjlooY = true;}
      if(GJNuFeGaur == lbGZeAVHsV){aDgNwqbtTa = true;}
      else if(lbGZeAVHsV == GJNuFeGaur){tIiehYgVys = true;}
      if(AaWNrTnRJe == WtqJRrbRZg){dqlIbZQkYA = true;}
      else if(WtqJRrbRZg == AaWNrTnRJe){FUxGsowSTp = true;}
      if(ICAWXjYTOg == euGAjAUECa){xbRujitTdb = true;}
      else if(euGAjAUECa == ICAWXjYTOg){dDQxOLUCPX = true;}
      if(DdERIIeuqg == AbRybaHkOm){PwWeFzZlXC = true;}
      else if(AbRybaHkOm == DdERIIeuqg){JEbPbKXgOz = true;}
      if(uKTkXJgLIU == kjichExNEh){rBgAHOPmHh = true;}
      else if(kjichExNEh == uKTkXJgLIU){nhRwArqCQQ = true;}
      if(swkbTEJpXU == gffPVqUFoe){DtqGozlkcN = true;}
      else if(gffPVqUFoe == swkbTEJpXU){nSUytprkPW = true;}
      if(GlMNnWWEFi == fQFRUtcsgp){wIPrLhTGDb = true;}
      if(oraciyhOyO == kpDlutMdSf){zdMVIwtQnV = true;}
      if(DNKtnHrbyE == DGAUsUwBbk){THLwYVEQpF = true;}
      while(fQFRUtcsgp == GlMNnWWEFi){EeFZjAsgei = true;}
      while(kpDlutMdSf == kpDlutMdSf){QOETBulUxW = true;}
      while(DGAUsUwBbk == DGAUsUwBbk){TRkyjpjcUk = true;}
      if(FBwiHTeQHm == true){FBwiHTeQHm = false;}
      if(aDgNwqbtTa == true){aDgNwqbtTa = false;}
      if(dqlIbZQkYA == true){dqlIbZQkYA = false;}
      if(xbRujitTdb == true){xbRujitTdb = false;}
      if(PwWeFzZlXC == true){PwWeFzZlXC = false;}
      if(rBgAHOPmHh == true){rBgAHOPmHh = false;}
      if(DtqGozlkcN == true){DtqGozlkcN = false;}
      if(wIPrLhTGDb == true){wIPrLhTGDb = false;}
      if(zdMVIwtQnV == true){zdMVIwtQnV = false;}
      if(THLwYVEQpF == true){THLwYVEQpF = false;}
      if(NnJKGjlooY == true){NnJKGjlooY = false;}
      if(tIiehYgVys == true){tIiehYgVys = false;}
      if(FUxGsowSTp == true){FUxGsowSTp = false;}
      if(dDQxOLUCPX == true){dDQxOLUCPX = false;}
      if(JEbPbKXgOz == true){JEbPbKXgOz = false;}
      if(nhRwArqCQQ == true){nhRwArqCQQ = false;}
      if(nSUytprkPW == true){nSUytprkPW = false;}
      if(EeFZjAsgei == true){EeFZjAsgei = false;}
      if(QOETBulUxW == true){QOETBulUxW = false;}
      if(TRkyjpjcUk == true){TRkyjpjcUk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZMJQNDMAOB
{ 
  void klhEcJWHJZ()
  { 
      bool kwDXGiYNke = false;
      bool BniDaQcfBg = false;
      bool rfcUbxeVqs = false;
      bool rghuZeKxPC = false;
      bool teAkdtwikF = false;
      bool IKPGYFTiwJ = false;
      bool DCWrlUFmdw = false;
      bool FeQylMeqpg = false;
      bool AwklkhQaWU = false;
      bool LbBFyrIIyJ = false;
      bool nIFozctQUL = false;
      bool ZbrOIHQkHE = false;
      bool DeQIjcdKAs = false;
      bool EWrgsrqwlH = false;
      bool mAGKuijmxq = false;
      bool aXBtGJrwEW = false;
      bool zjQaGCjLUQ = false;
      bool PUyzQCYFNA = false;
      bool spMIRgVyaj = false;
      bool zuqPHDjeEr = false;
      string WdiZVCzSBi;
      string eDwwTmnpRi;
      string WHWoQFPyjq;
      string eBTWYfHpAY;
      string XoykTksgRz;
      string tqAmIPGtJP;
      string lAiJDciYXn;
      string eyorKgIkVe;
      string MifjwmAgOI;
      string YNgklWGnhp;
      string BTJdUwCHba;
      string GVXdCCUyNQ;
      string bCJOOQRDFn;
      string aUDedrZCPA;
      string krEnCDoDhj;
      string CHaQOyJtPD;
      string eyCnAlRszK;
      string cSiMfixVLL;
      string bOVVlTslQe;
      string hemMVlpQnQ;
      if(WdiZVCzSBi == BTJdUwCHba){kwDXGiYNke = true;}
      else if(BTJdUwCHba == WdiZVCzSBi){nIFozctQUL = true;}
      if(eDwwTmnpRi == GVXdCCUyNQ){BniDaQcfBg = true;}
      else if(GVXdCCUyNQ == eDwwTmnpRi){ZbrOIHQkHE = true;}
      if(WHWoQFPyjq == bCJOOQRDFn){rfcUbxeVqs = true;}
      else if(bCJOOQRDFn == WHWoQFPyjq){DeQIjcdKAs = true;}
      if(eBTWYfHpAY == aUDedrZCPA){rghuZeKxPC = true;}
      else if(aUDedrZCPA == eBTWYfHpAY){EWrgsrqwlH = true;}
      if(XoykTksgRz == krEnCDoDhj){teAkdtwikF = true;}
      else if(krEnCDoDhj == XoykTksgRz){mAGKuijmxq = true;}
      if(tqAmIPGtJP == CHaQOyJtPD){IKPGYFTiwJ = true;}
      else if(CHaQOyJtPD == tqAmIPGtJP){aXBtGJrwEW = true;}
      if(lAiJDciYXn == eyCnAlRszK){DCWrlUFmdw = true;}
      else if(eyCnAlRszK == lAiJDciYXn){zjQaGCjLUQ = true;}
      if(eyorKgIkVe == cSiMfixVLL){FeQylMeqpg = true;}
      if(MifjwmAgOI == bOVVlTslQe){AwklkhQaWU = true;}
      if(YNgklWGnhp == hemMVlpQnQ){LbBFyrIIyJ = true;}
      while(cSiMfixVLL == eyorKgIkVe){PUyzQCYFNA = true;}
      while(bOVVlTslQe == bOVVlTslQe){spMIRgVyaj = true;}
      while(hemMVlpQnQ == hemMVlpQnQ){zuqPHDjeEr = true;}
      if(kwDXGiYNke == true){kwDXGiYNke = false;}
      if(BniDaQcfBg == true){BniDaQcfBg = false;}
      if(rfcUbxeVqs == true){rfcUbxeVqs = false;}
      if(rghuZeKxPC == true){rghuZeKxPC = false;}
      if(teAkdtwikF == true){teAkdtwikF = false;}
      if(IKPGYFTiwJ == true){IKPGYFTiwJ = false;}
      if(DCWrlUFmdw == true){DCWrlUFmdw = false;}
      if(FeQylMeqpg == true){FeQylMeqpg = false;}
      if(AwklkhQaWU == true){AwklkhQaWU = false;}
      if(LbBFyrIIyJ == true){LbBFyrIIyJ = false;}
      if(nIFozctQUL == true){nIFozctQUL = false;}
      if(ZbrOIHQkHE == true){ZbrOIHQkHE = false;}
      if(DeQIjcdKAs == true){DeQIjcdKAs = false;}
      if(EWrgsrqwlH == true){EWrgsrqwlH = false;}
      if(mAGKuijmxq == true){mAGKuijmxq = false;}
      if(aXBtGJrwEW == true){aXBtGJrwEW = false;}
      if(zjQaGCjLUQ == true){zjQaGCjLUQ = false;}
      if(PUyzQCYFNA == true){PUyzQCYFNA = false;}
      if(spMIRgVyaj == true){spMIRgVyaj = false;}
      if(zuqPHDjeEr == true){zuqPHDjeEr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICGBNZGYZQ
{ 
  void oKELpDrRKa()
  { 
      bool bXFJbHWMAl = false;
      bool tRcZUZXncq = false;
      bool KyPWFwcQDS = false;
      bool GtagGnYGBl = false;
      bool eijSJJXrYn = false;
      bool DuNhXdIhEf = false;
      bool eFJgfzqwTf = false;
      bool AQlpLaOwNu = false;
      bool XjrOPKfrIc = false;
      bool fqCVHZZCmJ = false;
      bool SaYrmmJXWx = false;
      bool PLUJHuNtRU = false;
      bool SznqAJOPil = false;
      bool ALIDcwKzab = false;
      bool BIULNTVsOL = false;
      bool LfkSqSmhrd = false;
      bool YtojwDDRgL = false;
      bool jNSoTKdcdf = false;
      bool mUBWZUZpMJ = false;
      bool JcHxDHTkPJ = false;
      string jStxiHENMF;
      string YHnUwIPyXC;
      string cPQmYcVCJx;
      string hKaaqbEOYD;
      string cYcdiLxbWr;
      string PVosfTBHXG;
      string lCEPXOgMcT;
      string DBZTYEmlDN;
      string eseQgLVhtW;
      string ZxpRRaUMGU;
      string djyCoOwUUb;
      string gODKarXmiL;
      string rySFtGKHCx;
      string iZfhittbbR;
      string PBNSpLsfqY;
      string DgduceRsIh;
      string EnRWrGiUag;
      string xuKQupkAPi;
      string MdQdtBwjFD;
      string bBStNbjpZi;
      if(jStxiHENMF == djyCoOwUUb){bXFJbHWMAl = true;}
      else if(djyCoOwUUb == jStxiHENMF){SaYrmmJXWx = true;}
      if(YHnUwIPyXC == gODKarXmiL){tRcZUZXncq = true;}
      else if(gODKarXmiL == YHnUwIPyXC){PLUJHuNtRU = true;}
      if(cPQmYcVCJx == rySFtGKHCx){KyPWFwcQDS = true;}
      else if(rySFtGKHCx == cPQmYcVCJx){SznqAJOPil = true;}
      if(hKaaqbEOYD == iZfhittbbR){GtagGnYGBl = true;}
      else if(iZfhittbbR == hKaaqbEOYD){ALIDcwKzab = true;}
      if(cYcdiLxbWr == PBNSpLsfqY){eijSJJXrYn = true;}
      else if(PBNSpLsfqY == cYcdiLxbWr){BIULNTVsOL = true;}
      if(PVosfTBHXG == DgduceRsIh){DuNhXdIhEf = true;}
      else if(DgduceRsIh == PVosfTBHXG){LfkSqSmhrd = true;}
      if(lCEPXOgMcT == EnRWrGiUag){eFJgfzqwTf = true;}
      else if(EnRWrGiUag == lCEPXOgMcT){YtojwDDRgL = true;}
      if(DBZTYEmlDN == xuKQupkAPi){AQlpLaOwNu = true;}
      if(eseQgLVhtW == MdQdtBwjFD){XjrOPKfrIc = true;}
      if(ZxpRRaUMGU == bBStNbjpZi){fqCVHZZCmJ = true;}
      while(xuKQupkAPi == DBZTYEmlDN){jNSoTKdcdf = true;}
      while(MdQdtBwjFD == MdQdtBwjFD){mUBWZUZpMJ = true;}
      while(bBStNbjpZi == bBStNbjpZi){JcHxDHTkPJ = true;}
      if(bXFJbHWMAl == true){bXFJbHWMAl = false;}
      if(tRcZUZXncq == true){tRcZUZXncq = false;}
      if(KyPWFwcQDS == true){KyPWFwcQDS = false;}
      if(GtagGnYGBl == true){GtagGnYGBl = false;}
      if(eijSJJXrYn == true){eijSJJXrYn = false;}
      if(DuNhXdIhEf == true){DuNhXdIhEf = false;}
      if(eFJgfzqwTf == true){eFJgfzqwTf = false;}
      if(AQlpLaOwNu == true){AQlpLaOwNu = false;}
      if(XjrOPKfrIc == true){XjrOPKfrIc = false;}
      if(fqCVHZZCmJ == true){fqCVHZZCmJ = false;}
      if(SaYrmmJXWx == true){SaYrmmJXWx = false;}
      if(PLUJHuNtRU == true){PLUJHuNtRU = false;}
      if(SznqAJOPil == true){SznqAJOPil = false;}
      if(ALIDcwKzab == true){ALIDcwKzab = false;}
      if(BIULNTVsOL == true){BIULNTVsOL = false;}
      if(LfkSqSmhrd == true){LfkSqSmhrd = false;}
      if(YtojwDDRgL == true){YtojwDDRgL = false;}
      if(jNSoTKdcdf == true){jNSoTKdcdf = false;}
      if(mUBWZUZpMJ == true){mUBWZUZpMJ = false;}
      if(JcHxDHTkPJ == true){JcHxDHTkPJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQKRJGSXGM
{ 
  void iNrzHQBTVZ()
  { 
      bool OqqgrcDoQr = false;
      bool LtddMoMrGy = false;
      bool tSlgjqVWTC = false;
      bool BUXxbswPfl = false;
      bool TFLCRhApLb = false;
      bool uINUTuFKwB = false;
      bool GgVNqpWfBT = false;
      bool swMUeoHiOC = false;
      bool qeKqHsHCcg = false;
      bool nkTeeljyLb = false;
      bool LTorhywspe = false;
      bool nVutJaVdFy = false;
      bool iTCUeIcgor = false;
      bool FJXmqWpSJJ = false;
      bool xOMyrRoYUE = false;
      bool PFrNsqRTMZ = false;
      bool UOExZeyIDm = false;
      bool kDUwATHEbN = false;
      bool SEMjbzRJtz = false;
      bool FVFiniKOYN = false;
      string QXaMObpyLg;
      string zEadhfZmKe;
      string FdNBMIKwyQ;
      string iMgNAVWraU;
      string uRCDyCdjiR;
      string COsnflKZzF;
      string QtzuylXMdM;
      string IhMpjnbJCJ;
      string eaMgOTTsgN;
      string KxrUDBRGFM;
      string eQGWJTBCDr;
      string KAXoapgSfd;
      string SdfPBKpqli;
      string WUEoeNTpWu;
      string SQooDKZCtN;
      string TzabtAkpUy;
      string cKQUVouhKM;
      string VqukKBopMq;
      string kmxXOWtcud;
      string cdUYRIATSO;
      if(QXaMObpyLg == eQGWJTBCDr){OqqgrcDoQr = true;}
      else if(eQGWJTBCDr == QXaMObpyLg){LTorhywspe = true;}
      if(zEadhfZmKe == KAXoapgSfd){LtddMoMrGy = true;}
      else if(KAXoapgSfd == zEadhfZmKe){nVutJaVdFy = true;}
      if(FdNBMIKwyQ == SdfPBKpqli){tSlgjqVWTC = true;}
      else if(SdfPBKpqli == FdNBMIKwyQ){iTCUeIcgor = true;}
      if(iMgNAVWraU == WUEoeNTpWu){BUXxbswPfl = true;}
      else if(WUEoeNTpWu == iMgNAVWraU){FJXmqWpSJJ = true;}
      if(uRCDyCdjiR == SQooDKZCtN){TFLCRhApLb = true;}
      else if(SQooDKZCtN == uRCDyCdjiR){xOMyrRoYUE = true;}
      if(COsnflKZzF == TzabtAkpUy){uINUTuFKwB = true;}
      else if(TzabtAkpUy == COsnflKZzF){PFrNsqRTMZ = true;}
      if(QtzuylXMdM == cKQUVouhKM){GgVNqpWfBT = true;}
      else if(cKQUVouhKM == QtzuylXMdM){UOExZeyIDm = true;}
      if(IhMpjnbJCJ == VqukKBopMq){swMUeoHiOC = true;}
      if(eaMgOTTsgN == kmxXOWtcud){qeKqHsHCcg = true;}
      if(KxrUDBRGFM == cdUYRIATSO){nkTeeljyLb = true;}
      while(VqukKBopMq == IhMpjnbJCJ){kDUwATHEbN = true;}
      while(kmxXOWtcud == kmxXOWtcud){SEMjbzRJtz = true;}
      while(cdUYRIATSO == cdUYRIATSO){FVFiniKOYN = true;}
      if(OqqgrcDoQr == true){OqqgrcDoQr = false;}
      if(LtddMoMrGy == true){LtddMoMrGy = false;}
      if(tSlgjqVWTC == true){tSlgjqVWTC = false;}
      if(BUXxbswPfl == true){BUXxbswPfl = false;}
      if(TFLCRhApLb == true){TFLCRhApLb = false;}
      if(uINUTuFKwB == true){uINUTuFKwB = false;}
      if(GgVNqpWfBT == true){GgVNqpWfBT = false;}
      if(swMUeoHiOC == true){swMUeoHiOC = false;}
      if(qeKqHsHCcg == true){qeKqHsHCcg = false;}
      if(nkTeeljyLb == true){nkTeeljyLb = false;}
      if(LTorhywspe == true){LTorhywspe = false;}
      if(nVutJaVdFy == true){nVutJaVdFy = false;}
      if(iTCUeIcgor == true){iTCUeIcgor = false;}
      if(FJXmqWpSJJ == true){FJXmqWpSJJ = false;}
      if(xOMyrRoYUE == true){xOMyrRoYUE = false;}
      if(PFrNsqRTMZ == true){PFrNsqRTMZ = false;}
      if(UOExZeyIDm == true){UOExZeyIDm = false;}
      if(kDUwATHEbN == true){kDUwATHEbN = false;}
      if(SEMjbzRJtz == true){SEMjbzRJtz = false;}
      if(FVFiniKOYN == true){FVFiniKOYN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMWFUDWDMT
{ 
  void paoneiVUxZ()
  { 
      bool UlMARSEzft = false;
      bool nVliLfECMu = false;
      bool YaxEBRISsS = false;
      bool TMSjBGjqLe = false;
      bool mwKZsanqTp = false;
      bool TeyJjsnIzz = false;
      bool KlFNabDBgF = false;
      bool wMpgIbQXKZ = false;
      bool dQyCynNIAH = false;
      bool RaqLUAqwzR = false;
      bool XlJOtHnRBI = false;
      bool cQyZVsnDPl = false;
      bool NtBZnVUeMH = false;
      bool kTYsBqGiIp = false;
      bool zwGqeAcRpb = false;
      bool MmfMDdjjaX = false;
      bool lJFsXIrEXd = false;
      bool lEuYmQmJum = false;
      bool sDnjuxmLoX = false;
      bool GWIjEoqNTV = false;
      string lhkbiEmkPu;
      string tpeRZTsDPm;
      string pNDfpwugQZ;
      string ayLpiyoQYS;
      string VIVEGlxkoe;
      string BRQcPYeFkl;
      string IFUoUwdohb;
      string ebdxQhryYD;
      string yJrkYIgiZK;
      string SifmJPmfiK;
      string IIDMAYnTLh;
      string ggfgnzNjQL;
      string OuPWIuwqnA;
      string uLOOupGekA;
      string UNWrdlDzyK;
      string CDPXuNsfEE;
      string cwfLmURQly;
      string riyQqBYXsV;
      string rwrcyqwqTh;
      string waZfWYhLFI;
      if(lhkbiEmkPu == IIDMAYnTLh){UlMARSEzft = true;}
      else if(IIDMAYnTLh == lhkbiEmkPu){XlJOtHnRBI = true;}
      if(tpeRZTsDPm == ggfgnzNjQL){nVliLfECMu = true;}
      else if(ggfgnzNjQL == tpeRZTsDPm){cQyZVsnDPl = true;}
      if(pNDfpwugQZ == OuPWIuwqnA){YaxEBRISsS = true;}
      else if(OuPWIuwqnA == pNDfpwugQZ){NtBZnVUeMH = true;}
      if(ayLpiyoQYS == uLOOupGekA){TMSjBGjqLe = true;}
      else if(uLOOupGekA == ayLpiyoQYS){kTYsBqGiIp = true;}
      if(VIVEGlxkoe == UNWrdlDzyK){mwKZsanqTp = true;}
      else if(UNWrdlDzyK == VIVEGlxkoe){zwGqeAcRpb = true;}
      if(BRQcPYeFkl == CDPXuNsfEE){TeyJjsnIzz = true;}
      else if(CDPXuNsfEE == BRQcPYeFkl){MmfMDdjjaX = true;}
      if(IFUoUwdohb == cwfLmURQly){KlFNabDBgF = true;}
      else if(cwfLmURQly == IFUoUwdohb){lJFsXIrEXd = true;}
      if(ebdxQhryYD == riyQqBYXsV){wMpgIbQXKZ = true;}
      if(yJrkYIgiZK == rwrcyqwqTh){dQyCynNIAH = true;}
      if(SifmJPmfiK == waZfWYhLFI){RaqLUAqwzR = true;}
      while(riyQqBYXsV == ebdxQhryYD){lEuYmQmJum = true;}
      while(rwrcyqwqTh == rwrcyqwqTh){sDnjuxmLoX = true;}
      while(waZfWYhLFI == waZfWYhLFI){GWIjEoqNTV = true;}
      if(UlMARSEzft == true){UlMARSEzft = false;}
      if(nVliLfECMu == true){nVliLfECMu = false;}
      if(YaxEBRISsS == true){YaxEBRISsS = false;}
      if(TMSjBGjqLe == true){TMSjBGjqLe = false;}
      if(mwKZsanqTp == true){mwKZsanqTp = false;}
      if(TeyJjsnIzz == true){TeyJjsnIzz = false;}
      if(KlFNabDBgF == true){KlFNabDBgF = false;}
      if(wMpgIbQXKZ == true){wMpgIbQXKZ = false;}
      if(dQyCynNIAH == true){dQyCynNIAH = false;}
      if(RaqLUAqwzR == true){RaqLUAqwzR = false;}
      if(XlJOtHnRBI == true){XlJOtHnRBI = false;}
      if(cQyZVsnDPl == true){cQyZVsnDPl = false;}
      if(NtBZnVUeMH == true){NtBZnVUeMH = false;}
      if(kTYsBqGiIp == true){kTYsBqGiIp = false;}
      if(zwGqeAcRpb == true){zwGqeAcRpb = false;}
      if(MmfMDdjjaX == true){MmfMDdjjaX = false;}
      if(lJFsXIrEXd == true){lJFsXIrEXd = false;}
      if(lEuYmQmJum == true){lEuYmQmJum = false;}
      if(sDnjuxmLoX == true){sDnjuxmLoX = false;}
      if(GWIjEoqNTV == true){GWIjEoqNTV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORLQYEVNEE
{ 
  void sVUhtPnTlb()
  { 
      bool FDzsCVMleS = false;
      bool QdXQjAWQUP = false;
      bool wEGFiXHngt = false;
      bool PBOyDdhZJV = false;
      bool bmpIYWurFy = false;
      bool KWsdaBxtKe = false;
      bool NXFjDOPZNG = false;
      bool SwGzmINyfL = false;
      bool bPhhjrHkWB = false;
      bool gmPeHEhFEJ = false;
      bool HVdzfNQspR = false;
      bool mzNyCxoWAL = false;
      bool GdCLYegbri = false;
      bool aHsWEGkiCV = false;
      bool bNuEOgYQbJ = false;
      bool OKFrCcSRZA = false;
      bool fnBGqfFqtu = false;
      bool MGUejrixxq = false;
      bool FQAhUPCBUb = false;
      bool nSIComMnNi = false;
      string EBWrFBprAI;
      string KnKcDXNtmI;
      string POJBeGSoNs;
      string uodYzcmYyh;
      string oHoVLicppU;
      string zioKroqUNz;
      string hAdHMUKlca;
      string jnuFSIZmou;
      string cbzrsLASgK;
      string kRLyzncgIq;
      string YqNPkKmiqi;
      string PEfRVFBlOB;
      string TqFRoSbwGe;
      string erdyWlOiHh;
      string YQaxufktcs;
      string mqSHWgluZR;
      string ipcMEWahti;
      string qRdfcDQHWI;
      string ghTMqnZVbo;
      string ATJpzhnOsX;
      if(EBWrFBprAI == YqNPkKmiqi){FDzsCVMleS = true;}
      else if(YqNPkKmiqi == EBWrFBprAI){HVdzfNQspR = true;}
      if(KnKcDXNtmI == PEfRVFBlOB){QdXQjAWQUP = true;}
      else if(PEfRVFBlOB == KnKcDXNtmI){mzNyCxoWAL = true;}
      if(POJBeGSoNs == TqFRoSbwGe){wEGFiXHngt = true;}
      else if(TqFRoSbwGe == POJBeGSoNs){GdCLYegbri = true;}
      if(uodYzcmYyh == erdyWlOiHh){PBOyDdhZJV = true;}
      else if(erdyWlOiHh == uodYzcmYyh){aHsWEGkiCV = true;}
      if(oHoVLicppU == YQaxufktcs){bmpIYWurFy = true;}
      else if(YQaxufktcs == oHoVLicppU){bNuEOgYQbJ = true;}
      if(zioKroqUNz == mqSHWgluZR){KWsdaBxtKe = true;}
      else if(mqSHWgluZR == zioKroqUNz){OKFrCcSRZA = true;}
      if(hAdHMUKlca == ipcMEWahti){NXFjDOPZNG = true;}
      else if(ipcMEWahti == hAdHMUKlca){fnBGqfFqtu = true;}
      if(jnuFSIZmou == qRdfcDQHWI){SwGzmINyfL = true;}
      if(cbzrsLASgK == ghTMqnZVbo){bPhhjrHkWB = true;}
      if(kRLyzncgIq == ATJpzhnOsX){gmPeHEhFEJ = true;}
      while(qRdfcDQHWI == jnuFSIZmou){MGUejrixxq = true;}
      while(ghTMqnZVbo == ghTMqnZVbo){FQAhUPCBUb = true;}
      while(ATJpzhnOsX == ATJpzhnOsX){nSIComMnNi = true;}
      if(FDzsCVMleS == true){FDzsCVMleS = false;}
      if(QdXQjAWQUP == true){QdXQjAWQUP = false;}
      if(wEGFiXHngt == true){wEGFiXHngt = false;}
      if(PBOyDdhZJV == true){PBOyDdhZJV = false;}
      if(bmpIYWurFy == true){bmpIYWurFy = false;}
      if(KWsdaBxtKe == true){KWsdaBxtKe = false;}
      if(NXFjDOPZNG == true){NXFjDOPZNG = false;}
      if(SwGzmINyfL == true){SwGzmINyfL = false;}
      if(bPhhjrHkWB == true){bPhhjrHkWB = false;}
      if(gmPeHEhFEJ == true){gmPeHEhFEJ = false;}
      if(HVdzfNQspR == true){HVdzfNQspR = false;}
      if(mzNyCxoWAL == true){mzNyCxoWAL = false;}
      if(GdCLYegbri == true){GdCLYegbri = false;}
      if(aHsWEGkiCV == true){aHsWEGkiCV = false;}
      if(bNuEOgYQbJ == true){bNuEOgYQbJ = false;}
      if(OKFrCcSRZA == true){OKFrCcSRZA = false;}
      if(fnBGqfFqtu == true){fnBGqfFqtu = false;}
      if(MGUejrixxq == true){MGUejrixxq = false;}
      if(FQAhUPCBUb == true){FQAhUPCBUb = false;}
      if(nSIComMnNi == true){nSIComMnNi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDZPHXBVXI
{ 
  void qGDgRUYooF()
  { 
      bool FAVhXeIlWS = false;
      bool bUsdBWThiL = false;
      bool jrlGHewaby = false;
      bool NYyAJLCrcM = false;
      bool nzKrFpNCce = false;
      bool FHFZDNNPZr = false;
      bool hhJXEDWrTo = false;
      bool UaEWWkgtAR = false;
      bool RtxwrGSXww = false;
      bool xlRkdFommC = false;
      bool SUhmKdCiDS = false;
      bool fSOIankMey = false;
      bool jywXrhJTrQ = false;
      bool utHyywLJlO = false;
      bool DiUdQdXJJp = false;
      bool UcHoRUYKub = false;
      bool UiqlXkLPJd = false;
      bool baZQtAdRGN = false;
      bool KzJBwSmRfd = false;
      bool WBOKtUriGe = false;
      string JmozSTDgKC;
      string NKzbTWjjcx;
      string qqaepgZhVH;
      string XOkFzrlfWe;
      string hVuPyueHRH;
      string gisqpSLKIl;
      string sUKCeyYtcb;
      string kEMxOVuLgu;
      string BSQOZoUsOf;
      string faWkkNKsjz;
      string VkdoWcVucT;
      string WAdMjaEwbp;
      string ceexuJhbLB;
      string LCagYQnaqx;
      string SZQtIexJBK;
      string INQsVqFgtM;
      string utjbIUZxnS;
      string lcEeWDOjnP;
      string LXZBrxkgKh;
      string LGgdCYpolm;
      if(JmozSTDgKC == VkdoWcVucT){FAVhXeIlWS = true;}
      else if(VkdoWcVucT == JmozSTDgKC){SUhmKdCiDS = true;}
      if(NKzbTWjjcx == WAdMjaEwbp){bUsdBWThiL = true;}
      else if(WAdMjaEwbp == NKzbTWjjcx){fSOIankMey = true;}
      if(qqaepgZhVH == ceexuJhbLB){jrlGHewaby = true;}
      else if(ceexuJhbLB == qqaepgZhVH){jywXrhJTrQ = true;}
      if(XOkFzrlfWe == LCagYQnaqx){NYyAJLCrcM = true;}
      else if(LCagYQnaqx == XOkFzrlfWe){utHyywLJlO = true;}
      if(hVuPyueHRH == SZQtIexJBK){nzKrFpNCce = true;}
      else if(SZQtIexJBK == hVuPyueHRH){DiUdQdXJJp = true;}
      if(gisqpSLKIl == INQsVqFgtM){FHFZDNNPZr = true;}
      else if(INQsVqFgtM == gisqpSLKIl){UcHoRUYKub = true;}
      if(sUKCeyYtcb == utjbIUZxnS){hhJXEDWrTo = true;}
      else if(utjbIUZxnS == sUKCeyYtcb){UiqlXkLPJd = true;}
      if(kEMxOVuLgu == lcEeWDOjnP){UaEWWkgtAR = true;}
      if(BSQOZoUsOf == LXZBrxkgKh){RtxwrGSXww = true;}
      if(faWkkNKsjz == LGgdCYpolm){xlRkdFommC = true;}
      while(lcEeWDOjnP == kEMxOVuLgu){baZQtAdRGN = true;}
      while(LXZBrxkgKh == LXZBrxkgKh){KzJBwSmRfd = true;}
      while(LGgdCYpolm == LGgdCYpolm){WBOKtUriGe = true;}
      if(FAVhXeIlWS == true){FAVhXeIlWS = false;}
      if(bUsdBWThiL == true){bUsdBWThiL = false;}
      if(jrlGHewaby == true){jrlGHewaby = false;}
      if(NYyAJLCrcM == true){NYyAJLCrcM = false;}
      if(nzKrFpNCce == true){nzKrFpNCce = false;}
      if(FHFZDNNPZr == true){FHFZDNNPZr = false;}
      if(hhJXEDWrTo == true){hhJXEDWrTo = false;}
      if(UaEWWkgtAR == true){UaEWWkgtAR = false;}
      if(RtxwrGSXww == true){RtxwrGSXww = false;}
      if(xlRkdFommC == true){xlRkdFommC = false;}
      if(SUhmKdCiDS == true){SUhmKdCiDS = false;}
      if(fSOIankMey == true){fSOIankMey = false;}
      if(jywXrhJTrQ == true){jywXrhJTrQ = false;}
      if(utHyywLJlO == true){utHyywLJlO = false;}
      if(DiUdQdXJJp == true){DiUdQdXJJp = false;}
      if(UcHoRUYKub == true){UcHoRUYKub = false;}
      if(UiqlXkLPJd == true){UiqlXkLPJd = false;}
      if(baZQtAdRGN == true){baZQtAdRGN = false;}
      if(KzJBwSmRfd == true){KzJBwSmRfd = false;}
      if(WBOKtUriGe == true){WBOKtUriGe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUEDCJNCLG
{ 
  void OCnOayCDuJ()
  { 
      bool MwWUWQmpzB = false;
      bool CtZuFPNFqU = false;
      bool FTDBUBCQtQ = false;
      bool XroZEQKKsq = false;
      bool NXGOfDHKRZ = false;
      bool NwrMCsrUAV = false;
      bool NWwhcJFApo = false;
      bool FCLAHgMnVQ = false;
      bool sqzUDaAbWK = false;
      bool XoJXcqbXlV = false;
      bool yHUbTKkqFU = false;
      bool fDzjbWWaeC = false;
      bool IcceQQsnWP = false;
      bool FnCzRlVWBr = false;
      bool pIVBdToZuF = false;
      bool TAsiMUdoLC = false;
      bool RwUpPrBARo = false;
      bool BAZmMAGaAw = false;
      bool bSsQuFuTlw = false;
      bool IgKyatnfll = false;
      string fQiWdCXszX;
      string SENjsFxGBq;
      string xhsGVjXNgD;
      string gEchkfCEQF;
      string KQtsoRZQdx;
      string eBnMeyWbAt;
      string dKMwpObeyN;
      string CrpwffnARD;
      string KHijYePPDm;
      string JaEWazEyCZ;
      string ptSQtlLqfy;
      string KWKxiWacWL;
      string yLbKDbnSUf;
      string bpxqMQnSom;
      string TYiEclPHmE;
      string YaaqaeRHMR;
      string xrVzVUZTjS;
      string hInjrZbXhR;
      string MgeQHBOFPh;
      string ygGWoaCjhI;
      if(fQiWdCXszX == ptSQtlLqfy){MwWUWQmpzB = true;}
      else if(ptSQtlLqfy == fQiWdCXszX){yHUbTKkqFU = true;}
      if(SENjsFxGBq == KWKxiWacWL){CtZuFPNFqU = true;}
      else if(KWKxiWacWL == SENjsFxGBq){fDzjbWWaeC = true;}
      if(xhsGVjXNgD == yLbKDbnSUf){FTDBUBCQtQ = true;}
      else if(yLbKDbnSUf == xhsGVjXNgD){IcceQQsnWP = true;}
      if(gEchkfCEQF == bpxqMQnSom){XroZEQKKsq = true;}
      else if(bpxqMQnSom == gEchkfCEQF){FnCzRlVWBr = true;}
      if(KQtsoRZQdx == TYiEclPHmE){NXGOfDHKRZ = true;}
      else if(TYiEclPHmE == KQtsoRZQdx){pIVBdToZuF = true;}
      if(eBnMeyWbAt == YaaqaeRHMR){NwrMCsrUAV = true;}
      else if(YaaqaeRHMR == eBnMeyWbAt){TAsiMUdoLC = true;}
      if(dKMwpObeyN == xrVzVUZTjS){NWwhcJFApo = true;}
      else if(xrVzVUZTjS == dKMwpObeyN){RwUpPrBARo = true;}
      if(CrpwffnARD == hInjrZbXhR){FCLAHgMnVQ = true;}
      if(KHijYePPDm == MgeQHBOFPh){sqzUDaAbWK = true;}
      if(JaEWazEyCZ == ygGWoaCjhI){XoJXcqbXlV = true;}
      while(hInjrZbXhR == CrpwffnARD){BAZmMAGaAw = true;}
      while(MgeQHBOFPh == MgeQHBOFPh){bSsQuFuTlw = true;}
      while(ygGWoaCjhI == ygGWoaCjhI){IgKyatnfll = true;}
      if(MwWUWQmpzB == true){MwWUWQmpzB = false;}
      if(CtZuFPNFqU == true){CtZuFPNFqU = false;}
      if(FTDBUBCQtQ == true){FTDBUBCQtQ = false;}
      if(XroZEQKKsq == true){XroZEQKKsq = false;}
      if(NXGOfDHKRZ == true){NXGOfDHKRZ = false;}
      if(NwrMCsrUAV == true){NwrMCsrUAV = false;}
      if(NWwhcJFApo == true){NWwhcJFApo = false;}
      if(FCLAHgMnVQ == true){FCLAHgMnVQ = false;}
      if(sqzUDaAbWK == true){sqzUDaAbWK = false;}
      if(XoJXcqbXlV == true){XoJXcqbXlV = false;}
      if(yHUbTKkqFU == true){yHUbTKkqFU = false;}
      if(fDzjbWWaeC == true){fDzjbWWaeC = false;}
      if(IcceQQsnWP == true){IcceQQsnWP = false;}
      if(FnCzRlVWBr == true){FnCzRlVWBr = false;}
      if(pIVBdToZuF == true){pIVBdToZuF = false;}
      if(TAsiMUdoLC == true){TAsiMUdoLC = false;}
      if(RwUpPrBARo == true){RwUpPrBARo = false;}
      if(BAZmMAGaAw == true){BAZmMAGaAw = false;}
      if(bSsQuFuTlw == true){bSsQuFuTlw = false;}
      if(IgKyatnfll == true){IgKyatnfll = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHUBBITHMH
{ 
  void BrfYBhdhXe()
  { 
      bool iWIOEhhhiW = false;
      bool wBICVPrMwI = false;
      bool prhUaswwDY = false;
      bool xbowEzNibW = false;
      bool FinBcRxYKf = false;
      bool HuPZqqnnnK = false;
      bool lldJYTLMyV = false;
      bool CJjZCHEgrI = false;
      bool wWlXRCMOFN = false;
      bool LYtRkTFebI = false;
      bool FjandxLpWi = false;
      bool mGweNOzGqW = false;
      bool HxHkKcOSni = false;
      bool BZFiDLuxsU = false;
      bool qVqVaFcPDV = false;
      bool TzmFAHcpdB = false;
      bool hrBngMBMbB = false;
      bool SCMWelGkKF = false;
      bool AzOSPClAhu = false;
      bool iFTrlyTDnN = false;
      string YdsOhTyTPp;
      string ZXVhaMuCbx;
      string EDeCLbYJxn;
      string lpwpRsbLAs;
      string mmpbSOHXLd;
      string uyMWNUyqCF;
      string toWaDjbfQh;
      string kiBiJQNDix;
      string TAxSsndZcw;
      string tkItyyQOXi;
      string lbHdsLxcMx;
      string GuHFlsqDgP;
      string FBDTmzZGkL;
      string AyeAKrsSZg;
      string pANeozcDIE;
      string GMhIckYmqs;
      string lprBwHPGtt;
      string AXdzYFnXdn;
      string WVxfEnQWXZ;
      string SGbguAHLih;
      if(YdsOhTyTPp == lbHdsLxcMx){iWIOEhhhiW = true;}
      else if(lbHdsLxcMx == YdsOhTyTPp){FjandxLpWi = true;}
      if(ZXVhaMuCbx == GuHFlsqDgP){wBICVPrMwI = true;}
      else if(GuHFlsqDgP == ZXVhaMuCbx){mGweNOzGqW = true;}
      if(EDeCLbYJxn == FBDTmzZGkL){prhUaswwDY = true;}
      else if(FBDTmzZGkL == EDeCLbYJxn){HxHkKcOSni = true;}
      if(lpwpRsbLAs == AyeAKrsSZg){xbowEzNibW = true;}
      else if(AyeAKrsSZg == lpwpRsbLAs){BZFiDLuxsU = true;}
      if(mmpbSOHXLd == pANeozcDIE){FinBcRxYKf = true;}
      else if(pANeozcDIE == mmpbSOHXLd){qVqVaFcPDV = true;}
      if(uyMWNUyqCF == GMhIckYmqs){HuPZqqnnnK = true;}
      else if(GMhIckYmqs == uyMWNUyqCF){TzmFAHcpdB = true;}
      if(toWaDjbfQh == lprBwHPGtt){lldJYTLMyV = true;}
      else if(lprBwHPGtt == toWaDjbfQh){hrBngMBMbB = true;}
      if(kiBiJQNDix == AXdzYFnXdn){CJjZCHEgrI = true;}
      if(TAxSsndZcw == WVxfEnQWXZ){wWlXRCMOFN = true;}
      if(tkItyyQOXi == SGbguAHLih){LYtRkTFebI = true;}
      while(AXdzYFnXdn == kiBiJQNDix){SCMWelGkKF = true;}
      while(WVxfEnQWXZ == WVxfEnQWXZ){AzOSPClAhu = true;}
      while(SGbguAHLih == SGbguAHLih){iFTrlyTDnN = true;}
      if(iWIOEhhhiW == true){iWIOEhhhiW = false;}
      if(wBICVPrMwI == true){wBICVPrMwI = false;}
      if(prhUaswwDY == true){prhUaswwDY = false;}
      if(xbowEzNibW == true){xbowEzNibW = false;}
      if(FinBcRxYKf == true){FinBcRxYKf = false;}
      if(HuPZqqnnnK == true){HuPZqqnnnK = false;}
      if(lldJYTLMyV == true){lldJYTLMyV = false;}
      if(CJjZCHEgrI == true){CJjZCHEgrI = false;}
      if(wWlXRCMOFN == true){wWlXRCMOFN = false;}
      if(LYtRkTFebI == true){LYtRkTFebI = false;}
      if(FjandxLpWi == true){FjandxLpWi = false;}
      if(mGweNOzGqW == true){mGweNOzGqW = false;}
      if(HxHkKcOSni == true){HxHkKcOSni = false;}
      if(BZFiDLuxsU == true){BZFiDLuxsU = false;}
      if(qVqVaFcPDV == true){qVqVaFcPDV = false;}
      if(TzmFAHcpdB == true){TzmFAHcpdB = false;}
      if(hrBngMBMbB == true){hrBngMBMbB = false;}
      if(SCMWelGkKF == true){SCMWelGkKF = false;}
      if(AzOSPClAhu == true){AzOSPClAhu = false;}
      if(iFTrlyTDnN == true){iFTrlyTDnN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSEKVMPQLE
{ 
  void xlDSFfjIaX()
  { 
      bool gdFsPHdXWd = false;
      bool pfAMaZLfhm = false;
      bool SHUBuoZRgK = false;
      bool gIrdZsoOJn = false;
      bool NMJzuwAqxx = false;
      bool SnPijZIDxa = false;
      bool gLqLwgnWlh = false;
      bool jwWsYFxUGy = false;
      bool oiUjrrsIsA = false;
      bool klRhHCVxDN = false;
      bool IdEPMWQWJd = false;
      bool bmwzlxqHTD = false;
      bool neclxyeolW = false;
      bool jARspLeFWV = false;
      bool aWzOXxoSwJ = false;
      bool LOdzZcARSO = false;
      bool rbjmtbUDIa = false;
      bool SljybRfNNz = false;
      bool IMrbLVVSTM = false;
      bool KMlIdylMUw = false;
      string LsmGwIQlKN;
      string swwlCsBsKd;
      string PIVNVLiuCM;
      string gEWjaXJzBC;
      string ISWewFZgag;
      string KmshoCWYkj;
      string ZViyfnYMLd;
      string iBrIUwlqRP;
      string lCTUBsLouX;
      string BjOQcmiYyI;
      string gMUwxIukMr;
      string QfHVyWBOwm;
      string ciRnczmaeh;
      string MMrIiYgXWr;
      string yacCGUbrSF;
      string kUbLfxugTy;
      string UTFeeDnymY;
      string odqEoBGOgH;
      string WuIYwrkfck;
      string cADYWdUyWD;
      if(LsmGwIQlKN == gMUwxIukMr){gdFsPHdXWd = true;}
      else if(gMUwxIukMr == LsmGwIQlKN){IdEPMWQWJd = true;}
      if(swwlCsBsKd == QfHVyWBOwm){pfAMaZLfhm = true;}
      else if(QfHVyWBOwm == swwlCsBsKd){bmwzlxqHTD = true;}
      if(PIVNVLiuCM == ciRnczmaeh){SHUBuoZRgK = true;}
      else if(ciRnczmaeh == PIVNVLiuCM){neclxyeolW = true;}
      if(gEWjaXJzBC == MMrIiYgXWr){gIrdZsoOJn = true;}
      else if(MMrIiYgXWr == gEWjaXJzBC){jARspLeFWV = true;}
      if(ISWewFZgag == yacCGUbrSF){NMJzuwAqxx = true;}
      else if(yacCGUbrSF == ISWewFZgag){aWzOXxoSwJ = true;}
      if(KmshoCWYkj == kUbLfxugTy){SnPijZIDxa = true;}
      else if(kUbLfxugTy == KmshoCWYkj){LOdzZcARSO = true;}
      if(ZViyfnYMLd == UTFeeDnymY){gLqLwgnWlh = true;}
      else if(UTFeeDnymY == ZViyfnYMLd){rbjmtbUDIa = true;}
      if(iBrIUwlqRP == odqEoBGOgH){jwWsYFxUGy = true;}
      if(lCTUBsLouX == WuIYwrkfck){oiUjrrsIsA = true;}
      if(BjOQcmiYyI == cADYWdUyWD){klRhHCVxDN = true;}
      while(odqEoBGOgH == iBrIUwlqRP){SljybRfNNz = true;}
      while(WuIYwrkfck == WuIYwrkfck){IMrbLVVSTM = true;}
      while(cADYWdUyWD == cADYWdUyWD){KMlIdylMUw = true;}
      if(gdFsPHdXWd == true){gdFsPHdXWd = false;}
      if(pfAMaZLfhm == true){pfAMaZLfhm = false;}
      if(SHUBuoZRgK == true){SHUBuoZRgK = false;}
      if(gIrdZsoOJn == true){gIrdZsoOJn = false;}
      if(NMJzuwAqxx == true){NMJzuwAqxx = false;}
      if(SnPijZIDxa == true){SnPijZIDxa = false;}
      if(gLqLwgnWlh == true){gLqLwgnWlh = false;}
      if(jwWsYFxUGy == true){jwWsYFxUGy = false;}
      if(oiUjrrsIsA == true){oiUjrrsIsA = false;}
      if(klRhHCVxDN == true){klRhHCVxDN = false;}
      if(IdEPMWQWJd == true){IdEPMWQWJd = false;}
      if(bmwzlxqHTD == true){bmwzlxqHTD = false;}
      if(neclxyeolW == true){neclxyeolW = false;}
      if(jARspLeFWV == true){jARspLeFWV = false;}
      if(aWzOXxoSwJ == true){aWzOXxoSwJ = false;}
      if(LOdzZcARSO == true){LOdzZcARSO = false;}
      if(rbjmtbUDIa == true){rbjmtbUDIa = false;}
      if(SljybRfNNz == true){SljybRfNNz = false;}
      if(IMrbLVVSTM == true){IMrbLVVSTM = false;}
      if(KMlIdylMUw == true){KMlIdylMUw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSMKVRWAZP
{ 
  void ezDISrdubJ()
  { 
      bool rgFNKkmQIT = false;
      bool ULDeDFEllf = false;
      bool OwiQWDRPxZ = false;
      bool yLGThVIbxO = false;
      bool qlBqplacqT = false;
      bool aEJnauxoqG = false;
      bool TXThUJEjwh = false;
      bool xcoWoburZj = false;
      bool cnXcytBSrm = false;
      bool XTkptTSSVf = false;
      bool hpgJVyPlyz = false;
      bool zFOHcezpia = false;
      bool IkrIJdrzcU = false;
      bool JbVsBlHNHA = false;
      bool dOTrmSEdMO = false;
      bool TbitXwyXAr = false;
      bool GPJcpWjUFq = false;
      bool XliiwsRzUq = false;
      bool YNlNBgsaUF = false;
      bool niNPsOFpBQ = false;
      string iBRIiaHrqA;
      string xuQGqdLlcf;
      string ybxxnygcqQ;
      string YpdrYkJSZL;
      string ZLeYqhSLkE;
      string HeLBZGEUUk;
      string sdAZbGRYhG;
      string TrMRGmxXFF;
      string eUrmIsecRR;
      string foxnRwKFxk;
      string QtdekOStum;
      string JgOPFYlNQh;
      string anGQZduXAJ;
      string brZUnkqMCs;
      string akgeHzaghr;
      string KxnPJbmMFG;
      string TttkKRHtbU;
      string hYKWGpHaJa;
      string CNoHzdDKKL;
      string ydHuZfquUo;
      if(iBRIiaHrqA == QtdekOStum){rgFNKkmQIT = true;}
      else if(QtdekOStum == iBRIiaHrqA){hpgJVyPlyz = true;}
      if(xuQGqdLlcf == JgOPFYlNQh){ULDeDFEllf = true;}
      else if(JgOPFYlNQh == xuQGqdLlcf){zFOHcezpia = true;}
      if(ybxxnygcqQ == anGQZduXAJ){OwiQWDRPxZ = true;}
      else if(anGQZduXAJ == ybxxnygcqQ){IkrIJdrzcU = true;}
      if(YpdrYkJSZL == brZUnkqMCs){yLGThVIbxO = true;}
      else if(brZUnkqMCs == YpdrYkJSZL){JbVsBlHNHA = true;}
      if(ZLeYqhSLkE == akgeHzaghr){qlBqplacqT = true;}
      else if(akgeHzaghr == ZLeYqhSLkE){dOTrmSEdMO = true;}
      if(HeLBZGEUUk == KxnPJbmMFG){aEJnauxoqG = true;}
      else if(KxnPJbmMFG == HeLBZGEUUk){TbitXwyXAr = true;}
      if(sdAZbGRYhG == TttkKRHtbU){TXThUJEjwh = true;}
      else if(TttkKRHtbU == sdAZbGRYhG){GPJcpWjUFq = true;}
      if(TrMRGmxXFF == hYKWGpHaJa){xcoWoburZj = true;}
      if(eUrmIsecRR == CNoHzdDKKL){cnXcytBSrm = true;}
      if(foxnRwKFxk == ydHuZfquUo){XTkptTSSVf = true;}
      while(hYKWGpHaJa == TrMRGmxXFF){XliiwsRzUq = true;}
      while(CNoHzdDKKL == CNoHzdDKKL){YNlNBgsaUF = true;}
      while(ydHuZfquUo == ydHuZfquUo){niNPsOFpBQ = true;}
      if(rgFNKkmQIT == true){rgFNKkmQIT = false;}
      if(ULDeDFEllf == true){ULDeDFEllf = false;}
      if(OwiQWDRPxZ == true){OwiQWDRPxZ = false;}
      if(yLGThVIbxO == true){yLGThVIbxO = false;}
      if(qlBqplacqT == true){qlBqplacqT = false;}
      if(aEJnauxoqG == true){aEJnauxoqG = false;}
      if(TXThUJEjwh == true){TXThUJEjwh = false;}
      if(xcoWoburZj == true){xcoWoburZj = false;}
      if(cnXcytBSrm == true){cnXcytBSrm = false;}
      if(XTkptTSSVf == true){XTkptTSSVf = false;}
      if(hpgJVyPlyz == true){hpgJVyPlyz = false;}
      if(zFOHcezpia == true){zFOHcezpia = false;}
      if(IkrIJdrzcU == true){IkrIJdrzcU = false;}
      if(JbVsBlHNHA == true){JbVsBlHNHA = false;}
      if(dOTrmSEdMO == true){dOTrmSEdMO = false;}
      if(TbitXwyXAr == true){TbitXwyXAr = false;}
      if(GPJcpWjUFq == true){GPJcpWjUFq = false;}
      if(XliiwsRzUq == true){XliiwsRzUq = false;}
      if(YNlNBgsaUF == true){YNlNBgsaUF = false;}
      if(niNPsOFpBQ == true){niNPsOFpBQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTGOTOKNIM
{ 
  void WVBbLCjjUd()
  { 
      bool ZoasSUMjIp = false;
      bool JjMraeGhcW = false;
      bool CzprXPLmYX = false;
      bool XplfTWkUkq = false;
      bool jbcukPGuaL = false;
      bool aXpMCaziVD = false;
      bool JYKjRTxfXE = false;
      bool skwllaVtGI = false;
      bool IPMNxzzZds = false;
      bool XCzghKRrcQ = false;
      bool RZXVRoaEZb = false;
      bool EEbNtsLwmR = false;
      bool TXCegplPDb = false;
      bool JcRopirquH = false;
      bool YuABnSZkmn = false;
      bool yUFKxtWrob = false;
      bool CLAxSammXK = false;
      bool BUAesYWBqN = false;
      bool PAbPcnXGru = false;
      bool MABTEMuCiM = false;
      string czJiQGGcAl;
      string giNZtyFclX;
      string rwxiiGeKuF;
      string bejTZuXPDd;
      string rNpdoiXGqp;
      string GYyDyfBZAK;
      string auhtJBytAy;
      string aoYIeeGSsz;
      string hYTEyCggVt;
      string sxPsDxfuUn;
      string kdFrPQApXS;
      string ZigBbBbcwH;
      string URXGFcZfEh;
      string zKyFOESang;
      string CqICTKQNQB;
      string VCzNTSFzmm;
      string qUkoTOjbmW;
      string iAoPEdIVlt;
      string LMODMxLkku;
      string zTnBpgFSiF;
      if(czJiQGGcAl == kdFrPQApXS){ZoasSUMjIp = true;}
      else if(kdFrPQApXS == czJiQGGcAl){RZXVRoaEZb = true;}
      if(giNZtyFclX == ZigBbBbcwH){JjMraeGhcW = true;}
      else if(ZigBbBbcwH == giNZtyFclX){EEbNtsLwmR = true;}
      if(rwxiiGeKuF == URXGFcZfEh){CzprXPLmYX = true;}
      else if(URXGFcZfEh == rwxiiGeKuF){TXCegplPDb = true;}
      if(bejTZuXPDd == zKyFOESang){XplfTWkUkq = true;}
      else if(zKyFOESang == bejTZuXPDd){JcRopirquH = true;}
      if(rNpdoiXGqp == CqICTKQNQB){jbcukPGuaL = true;}
      else if(CqICTKQNQB == rNpdoiXGqp){YuABnSZkmn = true;}
      if(GYyDyfBZAK == VCzNTSFzmm){aXpMCaziVD = true;}
      else if(VCzNTSFzmm == GYyDyfBZAK){yUFKxtWrob = true;}
      if(auhtJBytAy == qUkoTOjbmW){JYKjRTxfXE = true;}
      else if(qUkoTOjbmW == auhtJBytAy){CLAxSammXK = true;}
      if(aoYIeeGSsz == iAoPEdIVlt){skwllaVtGI = true;}
      if(hYTEyCggVt == LMODMxLkku){IPMNxzzZds = true;}
      if(sxPsDxfuUn == zTnBpgFSiF){XCzghKRrcQ = true;}
      while(iAoPEdIVlt == aoYIeeGSsz){BUAesYWBqN = true;}
      while(LMODMxLkku == LMODMxLkku){PAbPcnXGru = true;}
      while(zTnBpgFSiF == zTnBpgFSiF){MABTEMuCiM = true;}
      if(ZoasSUMjIp == true){ZoasSUMjIp = false;}
      if(JjMraeGhcW == true){JjMraeGhcW = false;}
      if(CzprXPLmYX == true){CzprXPLmYX = false;}
      if(XplfTWkUkq == true){XplfTWkUkq = false;}
      if(jbcukPGuaL == true){jbcukPGuaL = false;}
      if(aXpMCaziVD == true){aXpMCaziVD = false;}
      if(JYKjRTxfXE == true){JYKjRTxfXE = false;}
      if(skwllaVtGI == true){skwllaVtGI = false;}
      if(IPMNxzzZds == true){IPMNxzzZds = false;}
      if(XCzghKRrcQ == true){XCzghKRrcQ = false;}
      if(RZXVRoaEZb == true){RZXVRoaEZb = false;}
      if(EEbNtsLwmR == true){EEbNtsLwmR = false;}
      if(TXCegplPDb == true){TXCegplPDb = false;}
      if(JcRopirquH == true){JcRopirquH = false;}
      if(YuABnSZkmn == true){YuABnSZkmn = false;}
      if(yUFKxtWrob == true){yUFKxtWrob = false;}
      if(CLAxSammXK == true){CLAxSammXK = false;}
      if(BUAesYWBqN == true){BUAesYWBqN = false;}
      if(PAbPcnXGru == true){PAbPcnXGru = false;}
      if(MABTEMuCiM == true){MABTEMuCiM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQBJQQCSEO
{ 
  void GsFEYpnQTS()
  { 
      bool OmsUwQrjzQ = false;
      bool GComzpjcUr = false;
      bool SofQVHkAFp = false;
      bool mMGIkRiwbc = false;
      bool nkZGqNYpDd = false;
      bool FgokyZHbzn = false;
      bool freJdtwgCg = false;
      bool HnBrDgPYZH = false;
      bool itxbjGWVKK = false;
      bool KGxnxwGPcw = false;
      bool RrnVVRfwgQ = false;
      bool JiBqFktDYW = false;
      bool WZVqVBpMuH = false;
      bool azudopGaFS = false;
      bool aansAbEFhL = false;
      bool BDqFZrVwzU = false;
      bool aSAZpKmXCO = false;
      bool eTxGwwkbqt = false;
      bool wkejFXIoDx = false;
      bool UKajrHZODp = false;
      string IeudVwqFiB;
      string UqdHELbqCJ;
      string CgBukzXcne;
      string MHilBbhrVr;
      string ZWcrkiSztf;
      string nuDWhadAsW;
      string YOREoNIrFc;
      string djVKjfEJJC;
      string fXiIqQELEa;
      string ygzyTLEXDX;
      string ZatRBDYrmB;
      string VTpqqAfJNX;
      string IwmedwkXqX;
      string bgFlbEdQGm;
      string qLYCFdqIGS;
      string euKfOdmOmE;
      string SBBOYnODOl;
      string WOCZfxWjYz;
      string FbQXsgVYXx;
      string QOdCUpJKdQ;
      if(IeudVwqFiB == ZatRBDYrmB){OmsUwQrjzQ = true;}
      else if(ZatRBDYrmB == IeudVwqFiB){RrnVVRfwgQ = true;}
      if(UqdHELbqCJ == VTpqqAfJNX){GComzpjcUr = true;}
      else if(VTpqqAfJNX == UqdHELbqCJ){JiBqFktDYW = true;}
      if(CgBukzXcne == IwmedwkXqX){SofQVHkAFp = true;}
      else if(IwmedwkXqX == CgBukzXcne){WZVqVBpMuH = true;}
      if(MHilBbhrVr == bgFlbEdQGm){mMGIkRiwbc = true;}
      else if(bgFlbEdQGm == MHilBbhrVr){azudopGaFS = true;}
      if(ZWcrkiSztf == qLYCFdqIGS){nkZGqNYpDd = true;}
      else if(qLYCFdqIGS == ZWcrkiSztf){aansAbEFhL = true;}
      if(nuDWhadAsW == euKfOdmOmE){FgokyZHbzn = true;}
      else if(euKfOdmOmE == nuDWhadAsW){BDqFZrVwzU = true;}
      if(YOREoNIrFc == SBBOYnODOl){freJdtwgCg = true;}
      else if(SBBOYnODOl == YOREoNIrFc){aSAZpKmXCO = true;}
      if(djVKjfEJJC == WOCZfxWjYz){HnBrDgPYZH = true;}
      if(fXiIqQELEa == FbQXsgVYXx){itxbjGWVKK = true;}
      if(ygzyTLEXDX == QOdCUpJKdQ){KGxnxwGPcw = true;}
      while(WOCZfxWjYz == djVKjfEJJC){eTxGwwkbqt = true;}
      while(FbQXsgVYXx == FbQXsgVYXx){wkejFXIoDx = true;}
      while(QOdCUpJKdQ == QOdCUpJKdQ){UKajrHZODp = true;}
      if(OmsUwQrjzQ == true){OmsUwQrjzQ = false;}
      if(GComzpjcUr == true){GComzpjcUr = false;}
      if(SofQVHkAFp == true){SofQVHkAFp = false;}
      if(mMGIkRiwbc == true){mMGIkRiwbc = false;}
      if(nkZGqNYpDd == true){nkZGqNYpDd = false;}
      if(FgokyZHbzn == true){FgokyZHbzn = false;}
      if(freJdtwgCg == true){freJdtwgCg = false;}
      if(HnBrDgPYZH == true){HnBrDgPYZH = false;}
      if(itxbjGWVKK == true){itxbjGWVKK = false;}
      if(KGxnxwGPcw == true){KGxnxwGPcw = false;}
      if(RrnVVRfwgQ == true){RrnVVRfwgQ = false;}
      if(JiBqFktDYW == true){JiBqFktDYW = false;}
      if(WZVqVBpMuH == true){WZVqVBpMuH = false;}
      if(azudopGaFS == true){azudopGaFS = false;}
      if(aansAbEFhL == true){aansAbEFhL = false;}
      if(BDqFZrVwzU == true){BDqFZrVwzU = false;}
      if(aSAZpKmXCO == true){aSAZpKmXCO = false;}
      if(eTxGwwkbqt == true){eTxGwwkbqt = false;}
      if(wkejFXIoDx == true){wkejFXIoDx = false;}
      if(UKajrHZODp == true){UKajrHZODp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GATMUMLCBH
{ 
  void KDwdTQezQL()
  { 
      bool SZjtQuwBts = false;
      bool GQzeTMzJNm = false;
      bool eUBGmSUaAN = false;
      bool gQgPnmTINz = false;
      bool liisxYiJpA = false;
      bool clfCEyXdHx = false;
      bool ZUBgMoijqf = false;
      bool spwNAulIIO = false;
      bool jLkzjujeKp = false;
      bool PpBPZRgBgH = false;
      bool oySJGmpRBI = false;
      bool LOUsNOjBwQ = false;
      bool FDYAQDofni = false;
      bool OjbAYkrasx = false;
      bool ERdCdAUHBK = false;
      bool gfFPCkZSsC = false;
      bool xJcStbmTTb = false;
      bool VIIzLmZWVP = false;
      bool igedBheLym = false;
      bool LZgpzuoKIC = false;
      string IhtTzqaQGS;
      string bfopKpTfFI;
      string FoCEtxgArZ;
      string nyJJfICydI;
      string RgkiMyAFNu;
      string iffALSepZB;
      string JZXgddVeKC;
      string mVCwqYETqw;
      string xbmxpISJxN;
      string cMXbzqIEFh;
      string bUuLHNciIl;
      string OLydEhlapU;
      string LLgxYaxawA;
      string QzNJTbfbpc;
      string eiBKyQNtWR;
      string FgOjWPmymf;
      string PCmIVPynJb;
      string BKkMpcJWyH;
      string MDDdtijcmD;
      string ohoJMbusoi;
      if(IhtTzqaQGS == bUuLHNciIl){SZjtQuwBts = true;}
      else if(bUuLHNciIl == IhtTzqaQGS){oySJGmpRBI = true;}
      if(bfopKpTfFI == OLydEhlapU){GQzeTMzJNm = true;}
      else if(OLydEhlapU == bfopKpTfFI){LOUsNOjBwQ = true;}
      if(FoCEtxgArZ == LLgxYaxawA){eUBGmSUaAN = true;}
      else if(LLgxYaxawA == FoCEtxgArZ){FDYAQDofni = true;}
      if(nyJJfICydI == QzNJTbfbpc){gQgPnmTINz = true;}
      else if(QzNJTbfbpc == nyJJfICydI){OjbAYkrasx = true;}
      if(RgkiMyAFNu == eiBKyQNtWR){liisxYiJpA = true;}
      else if(eiBKyQNtWR == RgkiMyAFNu){ERdCdAUHBK = true;}
      if(iffALSepZB == FgOjWPmymf){clfCEyXdHx = true;}
      else if(FgOjWPmymf == iffALSepZB){gfFPCkZSsC = true;}
      if(JZXgddVeKC == PCmIVPynJb){ZUBgMoijqf = true;}
      else if(PCmIVPynJb == JZXgddVeKC){xJcStbmTTb = true;}
      if(mVCwqYETqw == BKkMpcJWyH){spwNAulIIO = true;}
      if(xbmxpISJxN == MDDdtijcmD){jLkzjujeKp = true;}
      if(cMXbzqIEFh == ohoJMbusoi){PpBPZRgBgH = true;}
      while(BKkMpcJWyH == mVCwqYETqw){VIIzLmZWVP = true;}
      while(MDDdtijcmD == MDDdtijcmD){igedBheLym = true;}
      while(ohoJMbusoi == ohoJMbusoi){LZgpzuoKIC = true;}
      if(SZjtQuwBts == true){SZjtQuwBts = false;}
      if(GQzeTMzJNm == true){GQzeTMzJNm = false;}
      if(eUBGmSUaAN == true){eUBGmSUaAN = false;}
      if(gQgPnmTINz == true){gQgPnmTINz = false;}
      if(liisxYiJpA == true){liisxYiJpA = false;}
      if(clfCEyXdHx == true){clfCEyXdHx = false;}
      if(ZUBgMoijqf == true){ZUBgMoijqf = false;}
      if(spwNAulIIO == true){spwNAulIIO = false;}
      if(jLkzjujeKp == true){jLkzjujeKp = false;}
      if(PpBPZRgBgH == true){PpBPZRgBgH = false;}
      if(oySJGmpRBI == true){oySJGmpRBI = false;}
      if(LOUsNOjBwQ == true){LOUsNOjBwQ = false;}
      if(FDYAQDofni == true){FDYAQDofni = false;}
      if(OjbAYkrasx == true){OjbAYkrasx = false;}
      if(ERdCdAUHBK == true){ERdCdAUHBK = false;}
      if(gfFPCkZSsC == true){gfFPCkZSsC = false;}
      if(xJcStbmTTb == true){xJcStbmTTb = false;}
      if(VIIzLmZWVP == true){VIIzLmZWVP = false;}
      if(igedBheLym == true){igedBheLym = false;}
      if(LZgpzuoKIC == true){LZgpzuoKIC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAXDYVVUWU
{ 
  void ZjjEUgFBbF()
  { 
      bool kqjbszbLqh = false;
      bool rjMNHhpyHC = false;
      bool EGRdWZowIJ = false;
      bool LoiEGckLCP = false;
      bool ukgfnrSdVo = false;
      bool azNEydYGFS = false;
      bool JeCgWCBHHe = false;
      bool xdurHTYlpe = false;
      bool GLaThLbdGb = false;
      bool DdGjFQhAIk = false;
      bool pLWqrwEUxe = false;
      bool FlQZLyEiyL = false;
      bool aXBebSXLmq = false;
      bool lYdEnunial = false;
      bool GGfaWQNfXG = false;
      bool MyBxJRKrPZ = false;
      bool YshGsfILlQ = false;
      bool KUHMEUqZHK = false;
      bool EqmfdmXfuW = false;
      bool kwTBMNYZhq = false;
      string aRQsPSDLPi;
      string yJzqXDUdoL;
      string HrVbMJdOBO;
      string aQrsffzSjr;
      string CuBtbXFtEY;
      string UmkeLhungG;
      string noKBIgRGLr;
      string EBsxJLpaAn;
      string DiJbsnfNhx;
      string jLldDMkAlt;
      string GziMUSsmUA;
      string rUmrCFehHU;
      string BDYNHrPPsx;
      string ZpoGhDAxGa;
      string trshFPXtay;
      string hCrQrCaUFb;
      string DdtXZBegJz;
      string FhafZJKpIq;
      string UVnuPWxXOf;
      string berdXQyVHD;
      if(aRQsPSDLPi == GziMUSsmUA){kqjbszbLqh = true;}
      else if(GziMUSsmUA == aRQsPSDLPi){pLWqrwEUxe = true;}
      if(yJzqXDUdoL == rUmrCFehHU){rjMNHhpyHC = true;}
      else if(rUmrCFehHU == yJzqXDUdoL){FlQZLyEiyL = true;}
      if(HrVbMJdOBO == BDYNHrPPsx){EGRdWZowIJ = true;}
      else if(BDYNHrPPsx == HrVbMJdOBO){aXBebSXLmq = true;}
      if(aQrsffzSjr == ZpoGhDAxGa){LoiEGckLCP = true;}
      else if(ZpoGhDAxGa == aQrsffzSjr){lYdEnunial = true;}
      if(CuBtbXFtEY == trshFPXtay){ukgfnrSdVo = true;}
      else if(trshFPXtay == CuBtbXFtEY){GGfaWQNfXG = true;}
      if(UmkeLhungG == hCrQrCaUFb){azNEydYGFS = true;}
      else if(hCrQrCaUFb == UmkeLhungG){MyBxJRKrPZ = true;}
      if(noKBIgRGLr == DdtXZBegJz){JeCgWCBHHe = true;}
      else if(DdtXZBegJz == noKBIgRGLr){YshGsfILlQ = true;}
      if(EBsxJLpaAn == FhafZJKpIq){xdurHTYlpe = true;}
      if(DiJbsnfNhx == UVnuPWxXOf){GLaThLbdGb = true;}
      if(jLldDMkAlt == berdXQyVHD){DdGjFQhAIk = true;}
      while(FhafZJKpIq == EBsxJLpaAn){KUHMEUqZHK = true;}
      while(UVnuPWxXOf == UVnuPWxXOf){EqmfdmXfuW = true;}
      while(berdXQyVHD == berdXQyVHD){kwTBMNYZhq = true;}
      if(kqjbszbLqh == true){kqjbszbLqh = false;}
      if(rjMNHhpyHC == true){rjMNHhpyHC = false;}
      if(EGRdWZowIJ == true){EGRdWZowIJ = false;}
      if(LoiEGckLCP == true){LoiEGckLCP = false;}
      if(ukgfnrSdVo == true){ukgfnrSdVo = false;}
      if(azNEydYGFS == true){azNEydYGFS = false;}
      if(JeCgWCBHHe == true){JeCgWCBHHe = false;}
      if(xdurHTYlpe == true){xdurHTYlpe = false;}
      if(GLaThLbdGb == true){GLaThLbdGb = false;}
      if(DdGjFQhAIk == true){DdGjFQhAIk = false;}
      if(pLWqrwEUxe == true){pLWqrwEUxe = false;}
      if(FlQZLyEiyL == true){FlQZLyEiyL = false;}
      if(aXBebSXLmq == true){aXBebSXLmq = false;}
      if(lYdEnunial == true){lYdEnunial = false;}
      if(GGfaWQNfXG == true){GGfaWQNfXG = false;}
      if(MyBxJRKrPZ == true){MyBxJRKrPZ = false;}
      if(YshGsfILlQ == true){YshGsfILlQ = false;}
      if(KUHMEUqZHK == true){KUHMEUqZHK = false;}
      if(EqmfdmXfuW == true){EqmfdmXfuW = false;}
      if(kwTBMNYZhq == true){kwTBMNYZhq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBVAXXENIJ
{ 
  void nRyPnkZpmH()
  { 
      bool VmSmBHcjWZ = false;
      bool aRpqnrxuew = false;
      bool nODeHZKgLN = false;
      bool ayHaYGujyY = false;
      bool YTVOkiBJqF = false;
      bool RGWcwGjneb = false;
      bool wwXJzbJPRg = false;
      bool xNwGWTsnsY = false;
      bool XBoGuTbdeS = false;
      bool WGEVbcuMPJ = false;
      bool YlqJIEJQFb = false;
      bool NutGDuGRNe = false;
      bool AekzKpIadt = false;
      bool YfXjzlJfxp = false;
      bool KKYCFaMxRg = false;
      bool VcykItArzR = false;
      bool uimLDgXKHR = false;
      bool kZUWToGhsi = false;
      bool dKIwXugmaE = false;
      bool kQgetbXMzX = false;
      string ataJtjMUcI;
      string GoikeGLmds;
      string WWsZBglKWc;
      string bXENZdQyRd;
      string WOLpIYaBLz;
      string sHNgzEBBHN;
      string xByzfhjUKA;
      string pNVzVILCRc;
      string FkzWjUKXOV;
      string bPpDfVQLKZ;
      string nFpKIelNKp;
      string rzjeIMBaPL;
      string XMGnXZXRTA;
      string rAqqnAtnNF;
      string iwMXccfKuT;
      string UouzBazCmi;
      string GTtKyrHrqI;
      string RMMKbbAhLu;
      string tNWzfCEroM;
      string ArBeyOBBZj;
      if(ataJtjMUcI == nFpKIelNKp){VmSmBHcjWZ = true;}
      else if(nFpKIelNKp == ataJtjMUcI){YlqJIEJQFb = true;}
      if(GoikeGLmds == rzjeIMBaPL){aRpqnrxuew = true;}
      else if(rzjeIMBaPL == GoikeGLmds){NutGDuGRNe = true;}
      if(WWsZBglKWc == XMGnXZXRTA){nODeHZKgLN = true;}
      else if(XMGnXZXRTA == WWsZBglKWc){AekzKpIadt = true;}
      if(bXENZdQyRd == rAqqnAtnNF){ayHaYGujyY = true;}
      else if(rAqqnAtnNF == bXENZdQyRd){YfXjzlJfxp = true;}
      if(WOLpIYaBLz == iwMXccfKuT){YTVOkiBJqF = true;}
      else if(iwMXccfKuT == WOLpIYaBLz){KKYCFaMxRg = true;}
      if(sHNgzEBBHN == UouzBazCmi){RGWcwGjneb = true;}
      else if(UouzBazCmi == sHNgzEBBHN){VcykItArzR = true;}
      if(xByzfhjUKA == GTtKyrHrqI){wwXJzbJPRg = true;}
      else if(GTtKyrHrqI == xByzfhjUKA){uimLDgXKHR = true;}
      if(pNVzVILCRc == RMMKbbAhLu){xNwGWTsnsY = true;}
      if(FkzWjUKXOV == tNWzfCEroM){XBoGuTbdeS = true;}
      if(bPpDfVQLKZ == ArBeyOBBZj){WGEVbcuMPJ = true;}
      while(RMMKbbAhLu == pNVzVILCRc){kZUWToGhsi = true;}
      while(tNWzfCEroM == tNWzfCEroM){dKIwXugmaE = true;}
      while(ArBeyOBBZj == ArBeyOBBZj){kQgetbXMzX = true;}
      if(VmSmBHcjWZ == true){VmSmBHcjWZ = false;}
      if(aRpqnrxuew == true){aRpqnrxuew = false;}
      if(nODeHZKgLN == true){nODeHZKgLN = false;}
      if(ayHaYGujyY == true){ayHaYGujyY = false;}
      if(YTVOkiBJqF == true){YTVOkiBJqF = false;}
      if(RGWcwGjneb == true){RGWcwGjneb = false;}
      if(wwXJzbJPRg == true){wwXJzbJPRg = false;}
      if(xNwGWTsnsY == true){xNwGWTsnsY = false;}
      if(XBoGuTbdeS == true){XBoGuTbdeS = false;}
      if(WGEVbcuMPJ == true){WGEVbcuMPJ = false;}
      if(YlqJIEJQFb == true){YlqJIEJQFb = false;}
      if(NutGDuGRNe == true){NutGDuGRNe = false;}
      if(AekzKpIadt == true){AekzKpIadt = false;}
      if(YfXjzlJfxp == true){YfXjzlJfxp = false;}
      if(KKYCFaMxRg == true){KKYCFaMxRg = false;}
      if(VcykItArzR == true){VcykItArzR = false;}
      if(uimLDgXKHR == true){uimLDgXKHR = false;}
      if(kZUWToGhsi == true){kZUWToGhsi = false;}
      if(dKIwXugmaE == true){dKIwXugmaE = false;}
      if(kQgetbXMzX == true){kQgetbXMzX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MALVFJCMBL
{ 
  void OCZjiKHXAx()
  { 
      bool OZrJTiDVoa = false;
      bool FiWPERRtBV = false;
      bool bLaSSgZVri = false;
      bool FdrIWNjdWw = false;
      bool IyHxKhhukR = false;
      bool OFzJWDyYpl = false;
      bool IhdFVbpOrp = false;
      bool hmWEMcDcHk = false;
      bool zejaUAdikT = false;
      bool OKnknaUCbh = false;
      bool qSCujahtwt = false;
      bool zVRFmcyDkU = false;
      bool xHdYbWzlQl = false;
      bool HBBYtfcops = false;
      bool RjlpUsshxK = false;
      bool cRQGkjodSM = false;
      bool awdJmxUrLH = false;
      bool AIMqDNUmDi = false;
      bool cQnFJoktnJ = false;
      bool pzVdRVFcDW = false;
      string DPouYCtRWb;
      string dnRQuHBAkC;
      string WOuHQGOZlm;
      string xVNMBDNnRN;
      string kmoleVtxDz;
      string KVEzqoUhdS;
      string mTfjdIZEPr;
      string sNhWRiYJbu;
      string LRWmbaROUL;
      string hfJzaQHFHW;
      string uohKFxnggI;
      string PKFiGVwrHC;
      string pLjDJNDhwA;
      string aSBFAWiLge;
      string mkgMwXZasF;
      string TOyEfiFdBq;
      string tGkghwIAij;
      string lkLbPFdWHl;
      string mbnpfLUxYQ;
      string QEKojfzAez;
      if(DPouYCtRWb == uohKFxnggI){OZrJTiDVoa = true;}
      else if(uohKFxnggI == DPouYCtRWb){qSCujahtwt = true;}
      if(dnRQuHBAkC == PKFiGVwrHC){FiWPERRtBV = true;}
      else if(PKFiGVwrHC == dnRQuHBAkC){zVRFmcyDkU = true;}
      if(WOuHQGOZlm == pLjDJNDhwA){bLaSSgZVri = true;}
      else if(pLjDJNDhwA == WOuHQGOZlm){xHdYbWzlQl = true;}
      if(xVNMBDNnRN == aSBFAWiLge){FdrIWNjdWw = true;}
      else if(aSBFAWiLge == xVNMBDNnRN){HBBYtfcops = true;}
      if(kmoleVtxDz == mkgMwXZasF){IyHxKhhukR = true;}
      else if(mkgMwXZasF == kmoleVtxDz){RjlpUsshxK = true;}
      if(KVEzqoUhdS == TOyEfiFdBq){OFzJWDyYpl = true;}
      else if(TOyEfiFdBq == KVEzqoUhdS){cRQGkjodSM = true;}
      if(mTfjdIZEPr == tGkghwIAij){IhdFVbpOrp = true;}
      else if(tGkghwIAij == mTfjdIZEPr){awdJmxUrLH = true;}
      if(sNhWRiYJbu == lkLbPFdWHl){hmWEMcDcHk = true;}
      if(LRWmbaROUL == mbnpfLUxYQ){zejaUAdikT = true;}
      if(hfJzaQHFHW == QEKojfzAez){OKnknaUCbh = true;}
      while(lkLbPFdWHl == sNhWRiYJbu){AIMqDNUmDi = true;}
      while(mbnpfLUxYQ == mbnpfLUxYQ){cQnFJoktnJ = true;}
      while(QEKojfzAez == QEKojfzAez){pzVdRVFcDW = true;}
      if(OZrJTiDVoa == true){OZrJTiDVoa = false;}
      if(FiWPERRtBV == true){FiWPERRtBV = false;}
      if(bLaSSgZVri == true){bLaSSgZVri = false;}
      if(FdrIWNjdWw == true){FdrIWNjdWw = false;}
      if(IyHxKhhukR == true){IyHxKhhukR = false;}
      if(OFzJWDyYpl == true){OFzJWDyYpl = false;}
      if(IhdFVbpOrp == true){IhdFVbpOrp = false;}
      if(hmWEMcDcHk == true){hmWEMcDcHk = false;}
      if(zejaUAdikT == true){zejaUAdikT = false;}
      if(OKnknaUCbh == true){OKnknaUCbh = false;}
      if(qSCujahtwt == true){qSCujahtwt = false;}
      if(zVRFmcyDkU == true){zVRFmcyDkU = false;}
      if(xHdYbWzlQl == true){xHdYbWzlQl = false;}
      if(HBBYtfcops == true){HBBYtfcops = false;}
      if(RjlpUsshxK == true){RjlpUsshxK = false;}
      if(cRQGkjodSM == true){cRQGkjodSM = false;}
      if(awdJmxUrLH == true){awdJmxUrLH = false;}
      if(AIMqDNUmDi == true){AIMqDNUmDi = false;}
      if(cQnFJoktnJ == true){cQnFJoktnJ = false;}
      if(pzVdRVFcDW == true){pzVdRVFcDW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTRSRZGPCE
{ 
  void lWkBDqkKoA()
  { 
      bool HqhbmigiFE = false;
      bool uCaTZJuGxp = false;
      bool VPyYFTEprD = false;
      bool mwzEzZMrJE = false;
      bool BnqLedXrMt = false;
      bool eeartqsIVT = false;
      bool dqpCQzDVUz = false;
      bool wCwrogYlsb = false;
      bool uMcyYIUHJH = false;
      bool gEWoaKyouf = false;
      bool ZBWMxbhiCN = false;
      bool SGOtYQNrdH = false;
      bool dwMMSrfHRe = false;
      bool iiqNBsoPAw = false;
      bool alEunZobQK = false;
      bool wFLmBdoJtF = false;
      bool uaRWdjOBse = false;
      bool axrggrqRYr = false;
      bool CEpGhdXELW = false;
      bool EfVtBzUgQE = false;
      string zYUlZMfmVr;
      string bRKYgiNKUu;
      string XQufCefjna;
      string jUCxnqAJLz;
      string COdLxMmKrw;
      string kwaSYhcoiu;
      string gwytHHPNko;
      string hDzUsIljhp;
      string qUqrpmtiXF;
      string NLaQSFQjDp;
      string xZZDNgxFYQ;
      string wsGsDMFGET;
      string MfoebWchCn;
      string qCfrrRtndI;
      string pnKHJUFhNF;
      string AJeicRkuaq;
      string EPDkYsMNAl;
      string SRcwdYVhUH;
      string RuTwmhXxPa;
      string gyMmDZkYiQ;
      if(zYUlZMfmVr == xZZDNgxFYQ){HqhbmigiFE = true;}
      else if(xZZDNgxFYQ == zYUlZMfmVr){ZBWMxbhiCN = true;}
      if(bRKYgiNKUu == wsGsDMFGET){uCaTZJuGxp = true;}
      else if(wsGsDMFGET == bRKYgiNKUu){SGOtYQNrdH = true;}
      if(XQufCefjna == MfoebWchCn){VPyYFTEprD = true;}
      else if(MfoebWchCn == XQufCefjna){dwMMSrfHRe = true;}
      if(jUCxnqAJLz == qCfrrRtndI){mwzEzZMrJE = true;}
      else if(qCfrrRtndI == jUCxnqAJLz){iiqNBsoPAw = true;}
      if(COdLxMmKrw == pnKHJUFhNF){BnqLedXrMt = true;}
      else if(pnKHJUFhNF == COdLxMmKrw){alEunZobQK = true;}
      if(kwaSYhcoiu == AJeicRkuaq){eeartqsIVT = true;}
      else if(AJeicRkuaq == kwaSYhcoiu){wFLmBdoJtF = true;}
      if(gwytHHPNko == EPDkYsMNAl){dqpCQzDVUz = true;}
      else if(EPDkYsMNAl == gwytHHPNko){uaRWdjOBse = true;}
      if(hDzUsIljhp == SRcwdYVhUH){wCwrogYlsb = true;}
      if(qUqrpmtiXF == RuTwmhXxPa){uMcyYIUHJH = true;}
      if(NLaQSFQjDp == gyMmDZkYiQ){gEWoaKyouf = true;}
      while(SRcwdYVhUH == hDzUsIljhp){axrggrqRYr = true;}
      while(RuTwmhXxPa == RuTwmhXxPa){CEpGhdXELW = true;}
      while(gyMmDZkYiQ == gyMmDZkYiQ){EfVtBzUgQE = true;}
      if(HqhbmigiFE == true){HqhbmigiFE = false;}
      if(uCaTZJuGxp == true){uCaTZJuGxp = false;}
      if(VPyYFTEprD == true){VPyYFTEprD = false;}
      if(mwzEzZMrJE == true){mwzEzZMrJE = false;}
      if(BnqLedXrMt == true){BnqLedXrMt = false;}
      if(eeartqsIVT == true){eeartqsIVT = false;}
      if(dqpCQzDVUz == true){dqpCQzDVUz = false;}
      if(wCwrogYlsb == true){wCwrogYlsb = false;}
      if(uMcyYIUHJH == true){uMcyYIUHJH = false;}
      if(gEWoaKyouf == true){gEWoaKyouf = false;}
      if(ZBWMxbhiCN == true){ZBWMxbhiCN = false;}
      if(SGOtYQNrdH == true){SGOtYQNrdH = false;}
      if(dwMMSrfHRe == true){dwMMSrfHRe = false;}
      if(iiqNBsoPAw == true){iiqNBsoPAw = false;}
      if(alEunZobQK == true){alEunZobQK = false;}
      if(wFLmBdoJtF == true){wFLmBdoJtF = false;}
      if(uaRWdjOBse == true){uaRWdjOBse = false;}
      if(axrggrqRYr == true){axrggrqRYr = false;}
      if(CEpGhdXELW == true){CEpGhdXELW = false;}
      if(EfVtBzUgQE == true){EfVtBzUgQE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBIPEELZLM
{ 
  void IiLNqHZCxa()
  { 
      bool dmtgqZlnWj = false;
      bool sVqrswlUoo = false;
      bool ZorcruPRBj = false;
      bool PFYwkjnQpE = false;
      bool yYqoobndKa = false;
      bool OVAxcntQou = false;
      bool KUlmUnwtGJ = false;
      bool HVejpAyDnQ = false;
      bool HkHaVtFaTx = false;
      bool pWbttdlDUB = false;
      bool esWBSrpPGb = false;
      bool oqcXnYNLQZ = false;
      bool iVaJSjtkpM = false;
      bool NthlkNNFHc = false;
      bool DoTqHytDFU = false;
      bool PamtSJSNhh = false;
      bool yFYtOuIpmZ = false;
      bool LHEnWsBiBT = false;
      bool ppeVwmHnTb = false;
      bool uzWYdyQZcM = false;
      string XTqZAgijHX;
      string IKzZkDKLfk;
      string CusxctemcM;
      string KMotfgjjyQ;
      string VHhrnNJaGN;
      string sSQXObatxF;
      string BuHtNuUEtD;
      string TaNOPtNAJO;
      string jDgPTquRfD;
      string GpmrPZAmer;
      string rFgDtRFBIT;
      string NZjhUxOqaW;
      string ADXpwcmUzo;
      string tZVRWeWcUB;
      string ksIMpgFFWR;
      string LIMIqngqHQ;
      string ejCSZmDSKp;
      string akVYkGuLzO;
      string WhxgdkNNZh;
      string xeVEWAqolC;
      if(XTqZAgijHX == rFgDtRFBIT){dmtgqZlnWj = true;}
      else if(rFgDtRFBIT == XTqZAgijHX){esWBSrpPGb = true;}
      if(IKzZkDKLfk == NZjhUxOqaW){sVqrswlUoo = true;}
      else if(NZjhUxOqaW == IKzZkDKLfk){oqcXnYNLQZ = true;}
      if(CusxctemcM == ADXpwcmUzo){ZorcruPRBj = true;}
      else if(ADXpwcmUzo == CusxctemcM){iVaJSjtkpM = true;}
      if(KMotfgjjyQ == tZVRWeWcUB){PFYwkjnQpE = true;}
      else if(tZVRWeWcUB == KMotfgjjyQ){NthlkNNFHc = true;}
      if(VHhrnNJaGN == ksIMpgFFWR){yYqoobndKa = true;}
      else if(ksIMpgFFWR == VHhrnNJaGN){DoTqHytDFU = true;}
      if(sSQXObatxF == LIMIqngqHQ){OVAxcntQou = true;}
      else if(LIMIqngqHQ == sSQXObatxF){PamtSJSNhh = true;}
      if(BuHtNuUEtD == ejCSZmDSKp){KUlmUnwtGJ = true;}
      else if(ejCSZmDSKp == BuHtNuUEtD){yFYtOuIpmZ = true;}
      if(TaNOPtNAJO == akVYkGuLzO){HVejpAyDnQ = true;}
      if(jDgPTquRfD == WhxgdkNNZh){HkHaVtFaTx = true;}
      if(GpmrPZAmer == xeVEWAqolC){pWbttdlDUB = true;}
      while(akVYkGuLzO == TaNOPtNAJO){LHEnWsBiBT = true;}
      while(WhxgdkNNZh == WhxgdkNNZh){ppeVwmHnTb = true;}
      while(xeVEWAqolC == xeVEWAqolC){uzWYdyQZcM = true;}
      if(dmtgqZlnWj == true){dmtgqZlnWj = false;}
      if(sVqrswlUoo == true){sVqrswlUoo = false;}
      if(ZorcruPRBj == true){ZorcruPRBj = false;}
      if(PFYwkjnQpE == true){PFYwkjnQpE = false;}
      if(yYqoobndKa == true){yYqoobndKa = false;}
      if(OVAxcntQou == true){OVAxcntQou = false;}
      if(KUlmUnwtGJ == true){KUlmUnwtGJ = false;}
      if(HVejpAyDnQ == true){HVejpAyDnQ = false;}
      if(HkHaVtFaTx == true){HkHaVtFaTx = false;}
      if(pWbttdlDUB == true){pWbttdlDUB = false;}
      if(esWBSrpPGb == true){esWBSrpPGb = false;}
      if(oqcXnYNLQZ == true){oqcXnYNLQZ = false;}
      if(iVaJSjtkpM == true){iVaJSjtkpM = false;}
      if(NthlkNNFHc == true){NthlkNNFHc = false;}
      if(DoTqHytDFU == true){DoTqHytDFU = false;}
      if(PamtSJSNhh == true){PamtSJSNhh = false;}
      if(yFYtOuIpmZ == true){yFYtOuIpmZ = false;}
      if(LHEnWsBiBT == true){LHEnWsBiBT = false;}
      if(ppeVwmHnTb == true){ppeVwmHnTb = false;}
      if(uzWYdyQZcM == true){uzWYdyQZcM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFUONUNCAX
{ 
  void BtVKNHHHOk()
  { 
      bool LocBCzzXeu = false;
      bool JLKsGgpyWl = false;
      bool fQpjkKytKV = false;
      bool YFbfRWiuaX = false;
      bool BOGbZZuQdT = false;
      bool IBJWGtysQq = false;
      bool BFNJWDidaj = false;
      bool xtXzjRJOJL = false;
      bool OgQpNWwFZX = false;
      bool XpeiVuAxFW = false;
      bool pRosVNdKln = false;
      bool jjiFbToWwz = false;
      bool HdEDLHPnco = false;
      bool QMImVxqWUz = false;
      bool skTkmnGZGC = false;
      bool GdBGPLNlhO = false;
      bool yohxXXawje = false;
      bool bSCwFVJSQW = false;
      bool AphZhmKCWJ = false;
      bool jFoGBEDWNP = false;
      string CbFBGmlJNE;
      string rLVLcGqxXE;
      string VDwjMnCDqI;
      string DqyZshfkxF;
      string ddsFVWZSJH;
      string KIqzKzeVnS;
      string jhREAAMwRu;
      string ZGARZrKpNo;
      string NjtjytAzOt;
      string DKwdUuMnFU;
      string JdANgDIYYS;
      string onHzFAnhFF;
      string ANgXrOJVxe;
      string fVkrfiifCt;
      string laawFODxYT;
      string HeizUwxcVR;
      string tmbtmSDOTW;
      string RHeKTYmkSc;
      string LMxcWBmlXi;
      string lGJjAyzgIl;
      if(CbFBGmlJNE == JdANgDIYYS){LocBCzzXeu = true;}
      else if(JdANgDIYYS == CbFBGmlJNE){pRosVNdKln = true;}
      if(rLVLcGqxXE == onHzFAnhFF){JLKsGgpyWl = true;}
      else if(onHzFAnhFF == rLVLcGqxXE){jjiFbToWwz = true;}
      if(VDwjMnCDqI == ANgXrOJVxe){fQpjkKytKV = true;}
      else if(ANgXrOJVxe == VDwjMnCDqI){HdEDLHPnco = true;}
      if(DqyZshfkxF == fVkrfiifCt){YFbfRWiuaX = true;}
      else if(fVkrfiifCt == DqyZshfkxF){QMImVxqWUz = true;}
      if(ddsFVWZSJH == laawFODxYT){BOGbZZuQdT = true;}
      else if(laawFODxYT == ddsFVWZSJH){skTkmnGZGC = true;}
      if(KIqzKzeVnS == HeizUwxcVR){IBJWGtysQq = true;}
      else if(HeizUwxcVR == KIqzKzeVnS){GdBGPLNlhO = true;}
      if(jhREAAMwRu == tmbtmSDOTW){BFNJWDidaj = true;}
      else if(tmbtmSDOTW == jhREAAMwRu){yohxXXawje = true;}
      if(ZGARZrKpNo == RHeKTYmkSc){xtXzjRJOJL = true;}
      if(NjtjytAzOt == LMxcWBmlXi){OgQpNWwFZX = true;}
      if(DKwdUuMnFU == lGJjAyzgIl){XpeiVuAxFW = true;}
      while(RHeKTYmkSc == ZGARZrKpNo){bSCwFVJSQW = true;}
      while(LMxcWBmlXi == LMxcWBmlXi){AphZhmKCWJ = true;}
      while(lGJjAyzgIl == lGJjAyzgIl){jFoGBEDWNP = true;}
      if(LocBCzzXeu == true){LocBCzzXeu = false;}
      if(JLKsGgpyWl == true){JLKsGgpyWl = false;}
      if(fQpjkKytKV == true){fQpjkKytKV = false;}
      if(YFbfRWiuaX == true){YFbfRWiuaX = false;}
      if(BOGbZZuQdT == true){BOGbZZuQdT = false;}
      if(IBJWGtysQq == true){IBJWGtysQq = false;}
      if(BFNJWDidaj == true){BFNJWDidaj = false;}
      if(xtXzjRJOJL == true){xtXzjRJOJL = false;}
      if(OgQpNWwFZX == true){OgQpNWwFZX = false;}
      if(XpeiVuAxFW == true){XpeiVuAxFW = false;}
      if(pRosVNdKln == true){pRosVNdKln = false;}
      if(jjiFbToWwz == true){jjiFbToWwz = false;}
      if(HdEDLHPnco == true){HdEDLHPnco = false;}
      if(QMImVxqWUz == true){QMImVxqWUz = false;}
      if(skTkmnGZGC == true){skTkmnGZGC = false;}
      if(GdBGPLNlhO == true){GdBGPLNlhO = false;}
      if(yohxXXawje == true){yohxXXawje = false;}
      if(bSCwFVJSQW == true){bSCwFVJSQW = false;}
      if(AphZhmKCWJ == true){AphZhmKCWJ = false;}
      if(jFoGBEDWNP == true){jFoGBEDWNP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONCKMAEYJP
{ 
  void FSutqbVKDx()
  { 
      bool XTagDjpJpM = false;
      bool YHEWhxhYab = false;
      bool AQeCQZaUVF = false;
      bool OWyMNXZkhZ = false;
      bool CelcVLkcOx = false;
      bool LabAzGoYPd = false;
      bool JVnkxBIqIK = false;
      bool WwqBZUdBfF = false;
      bool oyFYsnuyMH = false;
      bool hBVDQfqBfU = false;
      bool CsTDZPiZZd = false;
      bool bmsKoKPPqI = false;
      bool FKeBbVZnjs = false;
      bool dcUKCudByd = false;
      bool EUXhetILOF = false;
      bool PaKWOrORbE = false;
      bool pupgAzShHs = false;
      bool gORNEjlwWg = false;
      bool MNYedCSywK = false;
      bool gMZsnJeqhe = false;
      string DbchBiVHyc;
      string oldqfkyreR;
      string OCKXjEnQoZ;
      string FmYmuweLBj;
      string APFHEbwOwL;
      string KaLaUBQEyw;
      string uESXXCNpwi;
      string FmpuRywDTH;
      string IYUcPdbySt;
      string fZNFouxhiC;
      string OGSMGWjQIV;
      string ENkpmVjoIs;
      string aPWBDfYjFW;
      string BOTQsCGIWr;
      string tLowoRnXRT;
      string LIZpbyiQIZ;
      string yAKlUotTwk;
      string PaRPzPZaMl;
      string qBSlKrocot;
      string TozxtsADbz;
      if(DbchBiVHyc == OGSMGWjQIV){XTagDjpJpM = true;}
      else if(OGSMGWjQIV == DbchBiVHyc){CsTDZPiZZd = true;}
      if(oldqfkyreR == ENkpmVjoIs){YHEWhxhYab = true;}
      else if(ENkpmVjoIs == oldqfkyreR){bmsKoKPPqI = true;}
      if(OCKXjEnQoZ == aPWBDfYjFW){AQeCQZaUVF = true;}
      else if(aPWBDfYjFW == OCKXjEnQoZ){FKeBbVZnjs = true;}
      if(FmYmuweLBj == BOTQsCGIWr){OWyMNXZkhZ = true;}
      else if(BOTQsCGIWr == FmYmuweLBj){dcUKCudByd = true;}
      if(APFHEbwOwL == tLowoRnXRT){CelcVLkcOx = true;}
      else if(tLowoRnXRT == APFHEbwOwL){EUXhetILOF = true;}
      if(KaLaUBQEyw == LIZpbyiQIZ){LabAzGoYPd = true;}
      else if(LIZpbyiQIZ == KaLaUBQEyw){PaKWOrORbE = true;}
      if(uESXXCNpwi == yAKlUotTwk){JVnkxBIqIK = true;}
      else if(yAKlUotTwk == uESXXCNpwi){pupgAzShHs = true;}
      if(FmpuRywDTH == PaRPzPZaMl){WwqBZUdBfF = true;}
      if(IYUcPdbySt == qBSlKrocot){oyFYsnuyMH = true;}
      if(fZNFouxhiC == TozxtsADbz){hBVDQfqBfU = true;}
      while(PaRPzPZaMl == FmpuRywDTH){gORNEjlwWg = true;}
      while(qBSlKrocot == qBSlKrocot){MNYedCSywK = true;}
      while(TozxtsADbz == TozxtsADbz){gMZsnJeqhe = true;}
      if(XTagDjpJpM == true){XTagDjpJpM = false;}
      if(YHEWhxhYab == true){YHEWhxhYab = false;}
      if(AQeCQZaUVF == true){AQeCQZaUVF = false;}
      if(OWyMNXZkhZ == true){OWyMNXZkhZ = false;}
      if(CelcVLkcOx == true){CelcVLkcOx = false;}
      if(LabAzGoYPd == true){LabAzGoYPd = false;}
      if(JVnkxBIqIK == true){JVnkxBIqIK = false;}
      if(WwqBZUdBfF == true){WwqBZUdBfF = false;}
      if(oyFYsnuyMH == true){oyFYsnuyMH = false;}
      if(hBVDQfqBfU == true){hBVDQfqBfU = false;}
      if(CsTDZPiZZd == true){CsTDZPiZZd = false;}
      if(bmsKoKPPqI == true){bmsKoKPPqI = false;}
      if(FKeBbVZnjs == true){FKeBbVZnjs = false;}
      if(dcUKCudByd == true){dcUKCudByd = false;}
      if(EUXhetILOF == true){EUXhetILOF = false;}
      if(PaKWOrORbE == true){PaKWOrORbE = false;}
      if(pupgAzShHs == true){pupgAzShHs = false;}
      if(gORNEjlwWg == true){gORNEjlwWg = false;}
      if(MNYedCSywK == true){MNYedCSywK = false;}
      if(gMZsnJeqhe == true){gMZsnJeqhe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDOJROAKXK
{ 
  void PgsOjrTQjg()
  { 
      bool YmeFdMjspb = false;
      bool QKFNQTzghE = false;
      bool HenVtrWugD = false;
      bool ZQAupFVdFy = false;
      bool wQhLNDqUzr = false;
      bool UbgdPtzIKk = false;
      bool pnMmCzKJXL = false;
      bool yUbiHpwcIq = false;
      bool BBunhxjVfw = false;
      bool GMSTIHEuIN = false;
      bool shxntzAxVZ = false;
      bool xVATjnsXEE = false;
      bool PndaEkCHaA = false;
      bool lBTtxSEHti = false;
      bool xlzGzjLyiT = false;
      bool OfqDyEEViI = false;
      bool wrWVmuBFVR = false;
      bool jkdUHcnWbU = false;
      bool YEXGlGKPws = false;
      bool OhXklEOdSD = false;
      string IfyKoFQxpr;
      string FpkoossQaE;
      string ciRzTZsOPe;
      string lzUEdeqAqr;
      string nQXscGZqfU;
      string uEDnYZNyqO;
      string MCgKGGUgLJ;
      string BrZiQLKYVN;
      string ABitjguffD;
      string RrJceliNmW;
      string ksfVTCeUXM;
      string OobcOKSmZY;
      string KnAHrJhxDd;
      string cxlzbGVMag;
      string CaISocPgNT;
      string SwmNLxrXdJ;
      string UhQsjRDcBI;
      string oFLsWifhSP;
      string sBiiLfKXne;
      string NxiQMTJOhW;
      if(IfyKoFQxpr == ksfVTCeUXM){YmeFdMjspb = true;}
      else if(ksfVTCeUXM == IfyKoFQxpr){shxntzAxVZ = true;}
      if(FpkoossQaE == OobcOKSmZY){QKFNQTzghE = true;}
      else if(OobcOKSmZY == FpkoossQaE){xVATjnsXEE = true;}
      if(ciRzTZsOPe == KnAHrJhxDd){HenVtrWugD = true;}
      else if(KnAHrJhxDd == ciRzTZsOPe){PndaEkCHaA = true;}
      if(lzUEdeqAqr == cxlzbGVMag){ZQAupFVdFy = true;}
      else if(cxlzbGVMag == lzUEdeqAqr){lBTtxSEHti = true;}
      if(nQXscGZqfU == CaISocPgNT){wQhLNDqUzr = true;}
      else if(CaISocPgNT == nQXscGZqfU){xlzGzjLyiT = true;}
      if(uEDnYZNyqO == SwmNLxrXdJ){UbgdPtzIKk = true;}
      else if(SwmNLxrXdJ == uEDnYZNyqO){OfqDyEEViI = true;}
      if(MCgKGGUgLJ == UhQsjRDcBI){pnMmCzKJXL = true;}
      else if(UhQsjRDcBI == MCgKGGUgLJ){wrWVmuBFVR = true;}
      if(BrZiQLKYVN == oFLsWifhSP){yUbiHpwcIq = true;}
      if(ABitjguffD == sBiiLfKXne){BBunhxjVfw = true;}
      if(RrJceliNmW == NxiQMTJOhW){GMSTIHEuIN = true;}
      while(oFLsWifhSP == BrZiQLKYVN){jkdUHcnWbU = true;}
      while(sBiiLfKXne == sBiiLfKXne){YEXGlGKPws = true;}
      while(NxiQMTJOhW == NxiQMTJOhW){OhXklEOdSD = true;}
      if(YmeFdMjspb == true){YmeFdMjspb = false;}
      if(QKFNQTzghE == true){QKFNQTzghE = false;}
      if(HenVtrWugD == true){HenVtrWugD = false;}
      if(ZQAupFVdFy == true){ZQAupFVdFy = false;}
      if(wQhLNDqUzr == true){wQhLNDqUzr = false;}
      if(UbgdPtzIKk == true){UbgdPtzIKk = false;}
      if(pnMmCzKJXL == true){pnMmCzKJXL = false;}
      if(yUbiHpwcIq == true){yUbiHpwcIq = false;}
      if(BBunhxjVfw == true){BBunhxjVfw = false;}
      if(GMSTIHEuIN == true){GMSTIHEuIN = false;}
      if(shxntzAxVZ == true){shxntzAxVZ = false;}
      if(xVATjnsXEE == true){xVATjnsXEE = false;}
      if(PndaEkCHaA == true){PndaEkCHaA = false;}
      if(lBTtxSEHti == true){lBTtxSEHti = false;}
      if(xlzGzjLyiT == true){xlzGzjLyiT = false;}
      if(OfqDyEEViI == true){OfqDyEEViI = false;}
      if(wrWVmuBFVR == true){wrWVmuBFVR = false;}
      if(jkdUHcnWbU == true){jkdUHcnWbU = false;}
      if(YEXGlGKPws == true){YEXGlGKPws = false;}
      if(OhXklEOdSD == true){OhXklEOdSD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HHEGVCHGKB
{ 
  void wroDVeztBG()
  { 
      bool ODCFfDmmie = false;
      bool KqmGRKGJnK = false;
      bool gxAhlxWslK = false;
      bool BsxwcHyDbf = false;
      bool CDPdjxMWAn = false;
      bool POFEpQDTTi = false;
      bool gtAYdQtqcJ = false;
      bool LCgIHdhWxn = false;
      bool jzrxtmmrFL = false;
      bool EdisyHCqzS = false;
      bool DVspcNgwwM = false;
      bool igWfygCDeq = false;
      bool dBkQFgSnJA = false;
      bool bpWdkOFBUf = false;
      bool FqwscXHDuR = false;
      bool FyLHoBjcku = false;
      bool trmwjrJrui = false;
      bool aAiyllFrnh = false;
      bool YOsrucdPni = false;
      bool ecPYlMEzIj = false;
      string HxHzgoJYTy;
      string SkWtFABnlA;
      string MqoEglDEPY;
      string oNDpxeoTwT;
      string iQMrXkMWbP;
      string XxVblPIDSt;
      string lEIuJFgfxZ;
      string LgrSQwexfw;
      string ZgcAAqrbEg;
      string WkBBheHRhS;
      string DfYBDqFCKo;
      string kLXVUEaItS;
      string NFbQDZfpkl;
      string oNONssHbwJ;
      string loRPwLNegc;
      string DzWPExEHyd;
      string KPRXAXwJca;
      string xzLjgYmMUr;
      string LAJHippyJu;
      string ozcSyWXtOX;
      if(HxHzgoJYTy == DfYBDqFCKo){ODCFfDmmie = true;}
      else if(DfYBDqFCKo == HxHzgoJYTy){DVspcNgwwM = true;}
      if(SkWtFABnlA == kLXVUEaItS){KqmGRKGJnK = true;}
      else if(kLXVUEaItS == SkWtFABnlA){igWfygCDeq = true;}
      if(MqoEglDEPY == NFbQDZfpkl){gxAhlxWslK = true;}
      else if(NFbQDZfpkl == MqoEglDEPY){dBkQFgSnJA = true;}
      if(oNDpxeoTwT == oNONssHbwJ){BsxwcHyDbf = true;}
      else if(oNONssHbwJ == oNDpxeoTwT){bpWdkOFBUf = true;}
      if(iQMrXkMWbP == loRPwLNegc){CDPdjxMWAn = true;}
      else if(loRPwLNegc == iQMrXkMWbP){FqwscXHDuR = true;}
      if(XxVblPIDSt == DzWPExEHyd){POFEpQDTTi = true;}
      else if(DzWPExEHyd == XxVblPIDSt){FyLHoBjcku = true;}
      if(lEIuJFgfxZ == KPRXAXwJca){gtAYdQtqcJ = true;}
      else if(KPRXAXwJca == lEIuJFgfxZ){trmwjrJrui = true;}
      if(LgrSQwexfw == xzLjgYmMUr){LCgIHdhWxn = true;}
      if(ZgcAAqrbEg == LAJHippyJu){jzrxtmmrFL = true;}
      if(WkBBheHRhS == ozcSyWXtOX){EdisyHCqzS = true;}
      while(xzLjgYmMUr == LgrSQwexfw){aAiyllFrnh = true;}
      while(LAJHippyJu == LAJHippyJu){YOsrucdPni = true;}
      while(ozcSyWXtOX == ozcSyWXtOX){ecPYlMEzIj = true;}
      if(ODCFfDmmie == true){ODCFfDmmie = false;}
      if(KqmGRKGJnK == true){KqmGRKGJnK = false;}
      if(gxAhlxWslK == true){gxAhlxWslK = false;}
      if(BsxwcHyDbf == true){BsxwcHyDbf = false;}
      if(CDPdjxMWAn == true){CDPdjxMWAn = false;}
      if(POFEpQDTTi == true){POFEpQDTTi = false;}
      if(gtAYdQtqcJ == true){gtAYdQtqcJ = false;}
      if(LCgIHdhWxn == true){LCgIHdhWxn = false;}
      if(jzrxtmmrFL == true){jzrxtmmrFL = false;}
      if(EdisyHCqzS == true){EdisyHCqzS = false;}
      if(DVspcNgwwM == true){DVspcNgwwM = false;}
      if(igWfygCDeq == true){igWfygCDeq = false;}
      if(dBkQFgSnJA == true){dBkQFgSnJA = false;}
      if(bpWdkOFBUf == true){bpWdkOFBUf = false;}
      if(FqwscXHDuR == true){FqwscXHDuR = false;}
      if(FyLHoBjcku == true){FyLHoBjcku = false;}
      if(trmwjrJrui == true){trmwjrJrui = false;}
      if(aAiyllFrnh == true){aAiyllFrnh = false;}
      if(YOsrucdPni == true){YOsrucdPni = false;}
      if(ecPYlMEzIj == true){ecPYlMEzIj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XIULTAKCUD
{ 
  void mCTBFnkUkf()
  { 
      bool ctPEiQwNeB = false;
      bool RpcaCzKHNz = false;
      bool iVsurhgwYs = false;
      bool rEikodEZrf = false;
      bool fmqehuBFXr = false;
      bool YaibgHATMB = false;
      bool jAnkJMGrkX = false;
      bool ukOgTwdNNw = false;
      bool fbXgUQVGEh = false;
      bool djMqwfyFVU = false;
      bool nJTzxmLCIj = false;
      bool cmGPUIbHQr = false;
      bool qzmCtKXXjm = false;
      bool xYqsHWHYjg = false;
      bool ETyUFqdwVn = false;
      bool DqocdnVQEl = false;
      bool PnRUlEuMIy = false;
      bool ACWjnWBSxD = false;
      bool faCwjGjOOS = false;
      bool BpTxRQCchB = false;
      string pFfasuPiEU;
      string fTpkxSijNx;
      string ZllPTVlXnO;
      string pQTsTNUeXZ;
      string HlyrkaOxQR;
      string DOsaNDSPGX;
      string JrtoePAwRi;
      string yDMmpnnses;
      string GnGVLbWreP;
      string uEYzQOqINU;
      string aSfgTzBFkZ;
      string PYjNRUkXdD;
      string rHQBnseMWa;
      string wefJSmIYBM;
      string ZRGFAVUKhu;
      string dSeJcSBdsa;
      string ToiKcjraud;
      string LMWRdaBLBS;
      string XTdaxcAWgz;
      string ldfZrjiwbP;
      if(pFfasuPiEU == aSfgTzBFkZ){ctPEiQwNeB = true;}
      else if(aSfgTzBFkZ == pFfasuPiEU){nJTzxmLCIj = true;}
      if(fTpkxSijNx == PYjNRUkXdD){RpcaCzKHNz = true;}
      else if(PYjNRUkXdD == fTpkxSijNx){cmGPUIbHQr = true;}
      if(ZllPTVlXnO == rHQBnseMWa){iVsurhgwYs = true;}
      else if(rHQBnseMWa == ZllPTVlXnO){qzmCtKXXjm = true;}
      if(pQTsTNUeXZ == wefJSmIYBM){rEikodEZrf = true;}
      else if(wefJSmIYBM == pQTsTNUeXZ){xYqsHWHYjg = true;}
      if(HlyrkaOxQR == ZRGFAVUKhu){fmqehuBFXr = true;}
      else if(ZRGFAVUKhu == HlyrkaOxQR){ETyUFqdwVn = true;}
      if(DOsaNDSPGX == dSeJcSBdsa){YaibgHATMB = true;}
      else if(dSeJcSBdsa == DOsaNDSPGX){DqocdnVQEl = true;}
      if(JrtoePAwRi == ToiKcjraud){jAnkJMGrkX = true;}
      else if(ToiKcjraud == JrtoePAwRi){PnRUlEuMIy = true;}
      if(yDMmpnnses == LMWRdaBLBS){ukOgTwdNNw = true;}
      if(GnGVLbWreP == XTdaxcAWgz){fbXgUQVGEh = true;}
      if(uEYzQOqINU == ldfZrjiwbP){djMqwfyFVU = true;}
      while(LMWRdaBLBS == yDMmpnnses){ACWjnWBSxD = true;}
      while(XTdaxcAWgz == XTdaxcAWgz){faCwjGjOOS = true;}
      while(ldfZrjiwbP == ldfZrjiwbP){BpTxRQCchB = true;}
      if(ctPEiQwNeB == true){ctPEiQwNeB = false;}
      if(RpcaCzKHNz == true){RpcaCzKHNz = false;}
      if(iVsurhgwYs == true){iVsurhgwYs = false;}
      if(rEikodEZrf == true){rEikodEZrf = false;}
      if(fmqehuBFXr == true){fmqehuBFXr = false;}
      if(YaibgHATMB == true){YaibgHATMB = false;}
      if(jAnkJMGrkX == true){jAnkJMGrkX = false;}
      if(ukOgTwdNNw == true){ukOgTwdNNw = false;}
      if(fbXgUQVGEh == true){fbXgUQVGEh = false;}
      if(djMqwfyFVU == true){djMqwfyFVU = false;}
      if(nJTzxmLCIj == true){nJTzxmLCIj = false;}
      if(cmGPUIbHQr == true){cmGPUIbHQr = false;}
      if(qzmCtKXXjm == true){qzmCtKXXjm = false;}
      if(xYqsHWHYjg == true){xYqsHWHYjg = false;}
      if(ETyUFqdwVn == true){ETyUFqdwVn = false;}
      if(DqocdnVQEl == true){DqocdnVQEl = false;}
      if(PnRUlEuMIy == true){PnRUlEuMIy = false;}
      if(ACWjnWBSxD == true){ACWjnWBSxD = false;}
      if(faCwjGjOOS == true){faCwjGjOOS = false;}
      if(BpTxRQCchB == true){BpTxRQCchB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWXMTOTCMA
{ 
  void cIKuesDjGZ()
  { 
      bool koOVEiWqyy = false;
      bool udrFJlloGg = false;
      bool GPsgqiVWlU = false;
      bool MSNppNiUqS = false;
      bool sZfjEfpeUj = false;
      bool rICjGUugeU = false;
      bool NzEclcPCPw = false;
      bool CRxmmfjJbK = false;
      bool spCCcDPdiU = false;
      bool RCpWFtVDxb = false;
      bool QmPYgaKPwa = false;
      bool kkETbWxBzi = false;
      bool NkTtdAbags = false;
      bool JfLAsFadUB = false;
      bool rzhIjfxVui = false;
      bool wTDONfTUtg = false;
      bool zjiDQEZDaW = false;
      bool wTfypNDKKy = false;
      bool CGfywpbxlN = false;
      bool kFjnBIQdre = false;
      string QHzNFUicFL;
      string OytKTKmoUH;
      string ttAhUQJDLG;
      string CfizxJEsgf;
      string wkMQlfwwxm;
      string WArNxWGQso;
      string KfRyJhOtNJ;
      string GsHnKJgiwn;
      string UNFXiBnUBa;
      string DmArUQSOGD;
      string QBhmfcsECn;
      string pWUEUxZsOI;
      string ttsmGTsPSt;
      string pRcrWSeRqF;
      string IiRNjfRuXW;
      string qZAyJWIugM;
      string jdkIxXtcgB;
      string SHCIAKbeCa;
      string CxquCQRdiA;
      string KikeVeyJQM;
      if(QHzNFUicFL == QBhmfcsECn){koOVEiWqyy = true;}
      else if(QBhmfcsECn == QHzNFUicFL){QmPYgaKPwa = true;}
      if(OytKTKmoUH == pWUEUxZsOI){udrFJlloGg = true;}
      else if(pWUEUxZsOI == OytKTKmoUH){kkETbWxBzi = true;}
      if(ttAhUQJDLG == ttsmGTsPSt){GPsgqiVWlU = true;}
      else if(ttsmGTsPSt == ttAhUQJDLG){NkTtdAbags = true;}
      if(CfizxJEsgf == pRcrWSeRqF){MSNppNiUqS = true;}
      else if(pRcrWSeRqF == CfizxJEsgf){JfLAsFadUB = true;}
      if(wkMQlfwwxm == IiRNjfRuXW){sZfjEfpeUj = true;}
      else if(IiRNjfRuXW == wkMQlfwwxm){rzhIjfxVui = true;}
      if(WArNxWGQso == qZAyJWIugM){rICjGUugeU = true;}
      else if(qZAyJWIugM == WArNxWGQso){wTDONfTUtg = true;}
      if(KfRyJhOtNJ == jdkIxXtcgB){NzEclcPCPw = true;}
      else if(jdkIxXtcgB == KfRyJhOtNJ){zjiDQEZDaW = true;}
      if(GsHnKJgiwn == SHCIAKbeCa){CRxmmfjJbK = true;}
      if(UNFXiBnUBa == CxquCQRdiA){spCCcDPdiU = true;}
      if(DmArUQSOGD == KikeVeyJQM){RCpWFtVDxb = true;}
      while(SHCIAKbeCa == GsHnKJgiwn){wTfypNDKKy = true;}
      while(CxquCQRdiA == CxquCQRdiA){CGfywpbxlN = true;}
      while(KikeVeyJQM == KikeVeyJQM){kFjnBIQdre = true;}
      if(koOVEiWqyy == true){koOVEiWqyy = false;}
      if(udrFJlloGg == true){udrFJlloGg = false;}
      if(GPsgqiVWlU == true){GPsgqiVWlU = false;}
      if(MSNppNiUqS == true){MSNppNiUqS = false;}
      if(sZfjEfpeUj == true){sZfjEfpeUj = false;}
      if(rICjGUugeU == true){rICjGUugeU = false;}
      if(NzEclcPCPw == true){NzEclcPCPw = false;}
      if(CRxmmfjJbK == true){CRxmmfjJbK = false;}
      if(spCCcDPdiU == true){spCCcDPdiU = false;}
      if(RCpWFtVDxb == true){RCpWFtVDxb = false;}
      if(QmPYgaKPwa == true){QmPYgaKPwa = false;}
      if(kkETbWxBzi == true){kkETbWxBzi = false;}
      if(NkTtdAbags == true){NkTtdAbags = false;}
      if(JfLAsFadUB == true){JfLAsFadUB = false;}
      if(rzhIjfxVui == true){rzhIjfxVui = false;}
      if(wTDONfTUtg == true){wTDONfTUtg = false;}
      if(zjiDQEZDaW == true){zjiDQEZDaW = false;}
      if(wTfypNDKKy == true){wTfypNDKKy = false;}
      if(CGfywpbxlN == true){CGfywpbxlN = false;}
      if(kFjnBIQdre == true){kFjnBIQdre = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZKAMNAWXX
{ 
  void hAZGRDXNDT()
  { 
      bool FTaobMVuNC = false;
      bool RKIoPqLPEV = false;
      bool dHEMEabiSD = false;
      bool Jonbkxbfwl = false;
      bool KTkOMJmyjn = false;
      bool BISKUxOOkB = false;
      bool jmbJsbVgDR = false;
      bool PfTSLKWoAt = false;
      bool ndyeCAWdGm = false;
      bool hMutBWqaVj = false;
      bool mFtRYUoAyK = false;
      bool aZOpNFnxHs = false;
      bool FrZQjCkYQn = false;
      bool SuTPGhigFg = false;
      bool KVeuLIyEgu = false;
      bool htTceufdhV = false;
      bool jPiJreGzjf = false;
      bool VHrahiMeEb = false;
      bool EgrUGYbqkL = false;
      bool BFyiwulUDf = false;
      string adpQpkQQFT;
      string TKmkqxmGCf;
      string HAdgmmBggt;
      string wBSNVtZxmg;
      string tDbMxKGTeL;
      string FjeOrZzJdC;
      string ijjLXRqYPw;
      string XoTUkEXRic;
      string fhBUoLWDVu;
      string tQTjyKTPof;
      string ShDhnPQKcm;
      string ChZBWAhOWL;
      string tmDTCHViVa;
      string kIbDJyeSfY;
      string uMZisLpSNy;
      string bEsdkeeifg;
      string thnCCsFWqX;
      string VPhxQhNUaq;
      string QDVXyfOyRd;
      string TumzeMYXfz;
      if(adpQpkQQFT == ShDhnPQKcm){FTaobMVuNC = true;}
      else if(ShDhnPQKcm == adpQpkQQFT){mFtRYUoAyK = true;}
      if(TKmkqxmGCf == ChZBWAhOWL){RKIoPqLPEV = true;}
      else if(ChZBWAhOWL == TKmkqxmGCf){aZOpNFnxHs = true;}
      if(HAdgmmBggt == tmDTCHViVa){dHEMEabiSD = true;}
      else if(tmDTCHViVa == HAdgmmBggt){FrZQjCkYQn = true;}
      if(wBSNVtZxmg == kIbDJyeSfY){Jonbkxbfwl = true;}
      else if(kIbDJyeSfY == wBSNVtZxmg){SuTPGhigFg = true;}
      if(tDbMxKGTeL == uMZisLpSNy){KTkOMJmyjn = true;}
      else if(uMZisLpSNy == tDbMxKGTeL){KVeuLIyEgu = true;}
      if(FjeOrZzJdC == bEsdkeeifg){BISKUxOOkB = true;}
      else if(bEsdkeeifg == FjeOrZzJdC){htTceufdhV = true;}
      if(ijjLXRqYPw == thnCCsFWqX){jmbJsbVgDR = true;}
      else if(thnCCsFWqX == ijjLXRqYPw){jPiJreGzjf = true;}
      if(XoTUkEXRic == VPhxQhNUaq){PfTSLKWoAt = true;}
      if(fhBUoLWDVu == QDVXyfOyRd){ndyeCAWdGm = true;}
      if(tQTjyKTPof == TumzeMYXfz){hMutBWqaVj = true;}
      while(VPhxQhNUaq == XoTUkEXRic){VHrahiMeEb = true;}
      while(QDVXyfOyRd == QDVXyfOyRd){EgrUGYbqkL = true;}
      while(TumzeMYXfz == TumzeMYXfz){BFyiwulUDf = true;}
      if(FTaobMVuNC == true){FTaobMVuNC = false;}
      if(RKIoPqLPEV == true){RKIoPqLPEV = false;}
      if(dHEMEabiSD == true){dHEMEabiSD = false;}
      if(Jonbkxbfwl == true){Jonbkxbfwl = false;}
      if(KTkOMJmyjn == true){KTkOMJmyjn = false;}
      if(BISKUxOOkB == true){BISKUxOOkB = false;}
      if(jmbJsbVgDR == true){jmbJsbVgDR = false;}
      if(PfTSLKWoAt == true){PfTSLKWoAt = false;}
      if(ndyeCAWdGm == true){ndyeCAWdGm = false;}
      if(hMutBWqaVj == true){hMutBWqaVj = false;}
      if(mFtRYUoAyK == true){mFtRYUoAyK = false;}
      if(aZOpNFnxHs == true){aZOpNFnxHs = false;}
      if(FrZQjCkYQn == true){FrZQjCkYQn = false;}
      if(SuTPGhigFg == true){SuTPGhigFg = false;}
      if(KVeuLIyEgu == true){KVeuLIyEgu = false;}
      if(htTceufdhV == true){htTceufdhV = false;}
      if(jPiJreGzjf == true){jPiJreGzjf = false;}
      if(VHrahiMeEb == true){VHrahiMeEb = false;}
      if(EgrUGYbqkL == true){EgrUGYbqkL = false;}
      if(BFyiwulUDf == true){BFyiwulUDf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDMIGFFCJO
{ 
  void BmSjeYuMbK()
  { 
      bool dnxSZPuBXs = false;
      bool KSIhqTfXee = false;
      bool BcFcrzzzHo = false;
      bool mHfuhtUcos = false;
      bool NZASkynupB = false;
      bool FUCKgAiTZa = false;
      bool PushFCmMAx = false;
      bool zDilQaclrt = false;
      bool KDJGjRFUNg = false;
      bool LBCOcRgSNi = false;
      bool LburBClPtG = false;
      bool XwafPLlmxm = false;
      bool xRySlyAUJz = false;
      bool tJYJhiIQEh = false;
      bool foaHJPZWyQ = false;
      bool fsUaksccGD = false;
      bool BRGtLNXRxf = false;
      bool DUhPGIqpJW = false;
      bool XcVsSAoxXo = false;
      bool FfKBfOifwu = false;
      string MwTgujrzGr;
      string ocfxiqFUiz;
      string fEKmAknjln;
      string kSBdFoqYCw;
      string CchxLoqXcP;
      string GULnaHlfgJ;
      string uHMSHVaCqs;
      string AfRlxCWNbK;
      string tQGWhQHNCy;
      string DKrsAtQPoo;
      string NnfjPZCYqY;
      string kYEVPeAokp;
      string OMzsponYkC;
      string kGXlwFjWHH;
      string OhWdNeGVcV;
      string sbezZAnmsZ;
      string lcnnndBRYJ;
      string udgcbgpVeL;
      string hRwPIIbXMu;
      string QwdgVlshpi;
      if(MwTgujrzGr == NnfjPZCYqY){dnxSZPuBXs = true;}
      else if(NnfjPZCYqY == MwTgujrzGr){LburBClPtG = true;}
      if(ocfxiqFUiz == kYEVPeAokp){KSIhqTfXee = true;}
      else if(kYEVPeAokp == ocfxiqFUiz){XwafPLlmxm = true;}
      if(fEKmAknjln == OMzsponYkC){BcFcrzzzHo = true;}
      else if(OMzsponYkC == fEKmAknjln){xRySlyAUJz = true;}
      if(kSBdFoqYCw == kGXlwFjWHH){mHfuhtUcos = true;}
      else if(kGXlwFjWHH == kSBdFoqYCw){tJYJhiIQEh = true;}
      if(CchxLoqXcP == OhWdNeGVcV){NZASkynupB = true;}
      else if(OhWdNeGVcV == CchxLoqXcP){foaHJPZWyQ = true;}
      if(GULnaHlfgJ == sbezZAnmsZ){FUCKgAiTZa = true;}
      else if(sbezZAnmsZ == GULnaHlfgJ){fsUaksccGD = true;}
      if(uHMSHVaCqs == lcnnndBRYJ){PushFCmMAx = true;}
      else if(lcnnndBRYJ == uHMSHVaCqs){BRGtLNXRxf = true;}
      if(AfRlxCWNbK == udgcbgpVeL){zDilQaclrt = true;}
      if(tQGWhQHNCy == hRwPIIbXMu){KDJGjRFUNg = true;}
      if(DKrsAtQPoo == QwdgVlshpi){LBCOcRgSNi = true;}
      while(udgcbgpVeL == AfRlxCWNbK){DUhPGIqpJW = true;}
      while(hRwPIIbXMu == hRwPIIbXMu){XcVsSAoxXo = true;}
      while(QwdgVlshpi == QwdgVlshpi){FfKBfOifwu = true;}
      if(dnxSZPuBXs == true){dnxSZPuBXs = false;}
      if(KSIhqTfXee == true){KSIhqTfXee = false;}
      if(BcFcrzzzHo == true){BcFcrzzzHo = false;}
      if(mHfuhtUcos == true){mHfuhtUcos = false;}
      if(NZASkynupB == true){NZASkynupB = false;}
      if(FUCKgAiTZa == true){FUCKgAiTZa = false;}
      if(PushFCmMAx == true){PushFCmMAx = false;}
      if(zDilQaclrt == true){zDilQaclrt = false;}
      if(KDJGjRFUNg == true){KDJGjRFUNg = false;}
      if(LBCOcRgSNi == true){LBCOcRgSNi = false;}
      if(LburBClPtG == true){LburBClPtG = false;}
      if(XwafPLlmxm == true){XwafPLlmxm = false;}
      if(xRySlyAUJz == true){xRySlyAUJz = false;}
      if(tJYJhiIQEh == true){tJYJhiIQEh = false;}
      if(foaHJPZWyQ == true){foaHJPZWyQ = false;}
      if(fsUaksccGD == true){fsUaksccGD = false;}
      if(BRGtLNXRxf == true){BRGtLNXRxf = false;}
      if(DUhPGIqpJW == true){DUhPGIqpJW = false;}
      if(XcVsSAoxXo == true){XcVsSAoxXo = false;}
      if(FfKBfOifwu == true){FfKBfOifwu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOHKJDUQFJ
{ 
  void NIBZdohfYe()
  { 
      bool EPFFYHaDNA = false;
      bool fZMTAzMjnL = false;
      bool gaONVDlVJB = false;
      bool gZkTrdVPIt = false;
      bool XLIgPntAWY = false;
      bool lIZmwdAqiU = false;
      bool UEtLTForaV = false;
      bool dxatmURhxh = false;
      bool IkzkPXAxXO = false;
      bool ddgnZSRxMK = false;
      bool zCYAtogfzb = false;
      bool LSsAMiFJuu = false;
      bool FqUMrAPmUT = false;
      bool CTUmiGLypa = false;
      bool pUxuCKjfap = false;
      bool NICQEHhMHt = false;
      bool YtKfYqxGRF = false;
      bool XGSUFksYKg = false;
      bool QjLeGtREia = false;
      bool XzqwBwJRVK = false;
      string SweMkEkOWa;
      string tnwuhEogSM;
      string HtgJCGculV;
      string VNiQyzjEam;
      string sIWAqThexT;
      string DxQYcXOUKe;
      string aocBFgEfxi;
      string TkGeTyXfRh;
      string XyyRSXwKmZ;
      string jOswMEeUuK;
      string PBgOzSqkFd;
      string zhDcGbpKhg;
      string jtrXyFqJSO;
      string TCkHRWQjRz;
      string fKEJZCLQoj;
      string NTlOZVIJPt;
      string agSpKwxwKj;
      string KGsiAYoixw;
      string saUhBzPWgw;
      string NHTWYyrOyc;
      if(SweMkEkOWa == PBgOzSqkFd){EPFFYHaDNA = true;}
      else if(PBgOzSqkFd == SweMkEkOWa){zCYAtogfzb = true;}
      if(tnwuhEogSM == zhDcGbpKhg){fZMTAzMjnL = true;}
      else if(zhDcGbpKhg == tnwuhEogSM){LSsAMiFJuu = true;}
      if(HtgJCGculV == jtrXyFqJSO){gaONVDlVJB = true;}
      else if(jtrXyFqJSO == HtgJCGculV){FqUMrAPmUT = true;}
      if(VNiQyzjEam == TCkHRWQjRz){gZkTrdVPIt = true;}
      else if(TCkHRWQjRz == VNiQyzjEam){CTUmiGLypa = true;}
      if(sIWAqThexT == fKEJZCLQoj){XLIgPntAWY = true;}
      else if(fKEJZCLQoj == sIWAqThexT){pUxuCKjfap = true;}
      if(DxQYcXOUKe == NTlOZVIJPt){lIZmwdAqiU = true;}
      else if(NTlOZVIJPt == DxQYcXOUKe){NICQEHhMHt = true;}
      if(aocBFgEfxi == agSpKwxwKj){UEtLTForaV = true;}
      else if(agSpKwxwKj == aocBFgEfxi){YtKfYqxGRF = true;}
      if(TkGeTyXfRh == KGsiAYoixw){dxatmURhxh = true;}
      if(XyyRSXwKmZ == saUhBzPWgw){IkzkPXAxXO = true;}
      if(jOswMEeUuK == NHTWYyrOyc){ddgnZSRxMK = true;}
      while(KGsiAYoixw == TkGeTyXfRh){XGSUFksYKg = true;}
      while(saUhBzPWgw == saUhBzPWgw){QjLeGtREia = true;}
      while(NHTWYyrOyc == NHTWYyrOyc){XzqwBwJRVK = true;}
      if(EPFFYHaDNA == true){EPFFYHaDNA = false;}
      if(fZMTAzMjnL == true){fZMTAzMjnL = false;}
      if(gaONVDlVJB == true){gaONVDlVJB = false;}
      if(gZkTrdVPIt == true){gZkTrdVPIt = false;}
      if(XLIgPntAWY == true){XLIgPntAWY = false;}
      if(lIZmwdAqiU == true){lIZmwdAqiU = false;}
      if(UEtLTForaV == true){UEtLTForaV = false;}
      if(dxatmURhxh == true){dxatmURhxh = false;}
      if(IkzkPXAxXO == true){IkzkPXAxXO = false;}
      if(ddgnZSRxMK == true){ddgnZSRxMK = false;}
      if(zCYAtogfzb == true){zCYAtogfzb = false;}
      if(LSsAMiFJuu == true){LSsAMiFJuu = false;}
      if(FqUMrAPmUT == true){FqUMrAPmUT = false;}
      if(CTUmiGLypa == true){CTUmiGLypa = false;}
      if(pUxuCKjfap == true){pUxuCKjfap = false;}
      if(NICQEHhMHt == true){NICQEHhMHt = false;}
      if(YtKfYqxGRF == true){YtKfYqxGRF = false;}
      if(XGSUFksYKg == true){XGSUFksYKg = false;}
      if(QjLeGtREia == true){QjLeGtREia = false;}
      if(XzqwBwJRVK == true){XzqwBwJRVK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWNUTFKVOG
{ 
  void tsCESwlngR()
  { 
      bool qRJcVCrkql = false;
      bool mTxoSpsYGq = false;
      bool SNsuUDeNKj = false;
      bool JeRlUeZjnE = false;
      bool KbDlVAECKT = false;
      bool aysHUcXNHS = false;
      bool XdZHbICLTm = false;
      bool PIjBgqKHYU = false;
      bool ycDqILkJRq = false;
      bool HLcVggBuKN = false;
      bool xshXERNqac = false;
      bool RQolTtZiyP = false;
      bool XstbeDfOUA = false;
      bool oPwLWFtelq = false;
      bool yshnYqWpCl = false;
      bool GSxtpEzFrA = false;
      bool lyWanCTdPN = false;
      bool AtwGRdKFCn = false;
      bool gpMhsWRCVR = false;
      bool GomlEzWHzV = false;
      string gpYKhjGfhj;
      string NOyHUWEDbc;
      string wCdTskOiIW;
      string rxQLxJyMJe;
      string KqWPWHiZZT;
      string PeTKkeLFRx;
      string UXXLqQxlKK;
      string YrswSEeNwk;
      string CoInGMcFaS;
      string xrtMJmSLYF;
      string JxOOuWlWrf;
      string zxIftfOjEd;
      string mrLrMfxfme;
      string lToqbFZsri;
      string ZGNtSAiNSc;
      string XiGtSRkWBP;
      string YGiNtfIREo;
      string GVqUDgdRYM;
      string wiNKGCMtXJ;
      string TCqcJTWzzm;
      if(gpYKhjGfhj == JxOOuWlWrf){qRJcVCrkql = true;}
      else if(JxOOuWlWrf == gpYKhjGfhj){xshXERNqac = true;}
      if(NOyHUWEDbc == zxIftfOjEd){mTxoSpsYGq = true;}
      else if(zxIftfOjEd == NOyHUWEDbc){RQolTtZiyP = true;}
      if(wCdTskOiIW == mrLrMfxfme){SNsuUDeNKj = true;}
      else if(mrLrMfxfme == wCdTskOiIW){XstbeDfOUA = true;}
      if(rxQLxJyMJe == lToqbFZsri){JeRlUeZjnE = true;}
      else if(lToqbFZsri == rxQLxJyMJe){oPwLWFtelq = true;}
      if(KqWPWHiZZT == ZGNtSAiNSc){KbDlVAECKT = true;}
      else if(ZGNtSAiNSc == KqWPWHiZZT){yshnYqWpCl = true;}
      if(PeTKkeLFRx == XiGtSRkWBP){aysHUcXNHS = true;}
      else if(XiGtSRkWBP == PeTKkeLFRx){GSxtpEzFrA = true;}
      if(UXXLqQxlKK == YGiNtfIREo){XdZHbICLTm = true;}
      else if(YGiNtfIREo == UXXLqQxlKK){lyWanCTdPN = true;}
      if(YrswSEeNwk == GVqUDgdRYM){PIjBgqKHYU = true;}
      if(CoInGMcFaS == wiNKGCMtXJ){ycDqILkJRq = true;}
      if(xrtMJmSLYF == TCqcJTWzzm){HLcVggBuKN = true;}
      while(GVqUDgdRYM == YrswSEeNwk){AtwGRdKFCn = true;}
      while(wiNKGCMtXJ == wiNKGCMtXJ){gpMhsWRCVR = true;}
      while(TCqcJTWzzm == TCqcJTWzzm){GomlEzWHzV = true;}
      if(qRJcVCrkql == true){qRJcVCrkql = false;}
      if(mTxoSpsYGq == true){mTxoSpsYGq = false;}
      if(SNsuUDeNKj == true){SNsuUDeNKj = false;}
      if(JeRlUeZjnE == true){JeRlUeZjnE = false;}
      if(KbDlVAECKT == true){KbDlVAECKT = false;}
      if(aysHUcXNHS == true){aysHUcXNHS = false;}
      if(XdZHbICLTm == true){XdZHbICLTm = false;}
      if(PIjBgqKHYU == true){PIjBgqKHYU = false;}
      if(ycDqILkJRq == true){ycDqILkJRq = false;}
      if(HLcVggBuKN == true){HLcVggBuKN = false;}
      if(xshXERNqac == true){xshXERNqac = false;}
      if(RQolTtZiyP == true){RQolTtZiyP = false;}
      if(XstbeDfOUA == true){XstbeDfOUA = false;}
      if(oPwLWFtelq == true){oPwLWFtelq = false;}
      if(yshnYqWpCl == true){yshnYqWpCl = false;}
      if(GSxtpEzFrA == true){GSxtpEzFrA = false;}
      if(lyWanCTdPN == true){lyWanCTdPN = false;}
      if(AtwGRdKFCn == true){AtwGRdKFCn = false;}
      if(gpMhsWRCVR == true){gpMhsWRCVR = false;}
      if(GomlEzWHzV == true){GomlEzWHzV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCJSWKCTLA
{ 
  void ncQsJDDIam()
  { 
      bool CcZkiwpeIc = false;
      bool iejaKmCrVt = false;
      bool oPPVRpHyhA = false;
      bool daHhTRAhZB = false;
      bool xgMraIUfxs = false;
      bool fglrKmNETs = false;
      bool nqwHyIXBHr = false;
      bool mURTxHCXtJ = false;
      bool UbBnUwnOWf = false;
      bool EwOgNFkFsS = false;
      bool kTXFGLPStD = false;
      bool kpJKYLpHmC = false;
      bool TIeamqFjFq = false;
      bool WxdbYBDuhI = false;
      bool gVTTuOlEIB = false;
      bool OdRqybnxRO = false;
      bool FeMDgmLglW = false;
      bool ItYdUxnLfY = false;
      bool EBbDcsemcw = false;
      bool MGcSDCJQmH = false;
      string qxPFHLyxnT;
      string kiBVZHbyZE;
      string IWERrnSQBk;
      string qpVAddydco;
      string NKJKFnntDY;
      string sDZSOUryNS;
      string rhuCctMArw;
      string JyUkpyMtLD;
      string AYMcqnQDkI;
      string lzQJxfOGgK;
      string amBHPuhocQ;
      string HylJSSUSLo;
      string dJOiJJgKnJ;
      string iGMBcMXFNu;
      string FaaUBmNGqd;
      string LutqfRYRxF;
      string NWBShBkjgF;
      string uPFPiDhthV;
      string uaTJxmLUUK;
      string nFHHgiYHlA;
      if(qxPFHLyxnT == amBHPuhocQ){CcZkiwpeIc = true;}
      else if(amBHPuhocQ == qxPFHLyxnT){kTXFGLPStD = true;}
      if(kiBVZHbyZE == HylJSSUSLo){iejaKmCrVt = true;}
      else if(HylJSSUSLo == kiBVZHbyZE){kpJKYLpHmC = true;}
      if(IWERrnSQBk == dJOiJJgKnJ){oPPVRpHyhA = true;}
      else if(dJOiJJgKnJ == IWERrnSQBk){TIeamqFjFq = true;}
      if(qpVAddydco == iGMBcMXFNu){daHhTRAhZB = true;}
      else if(iGMBcMXFNu == qpVAddydco){WxdbYBDuhI = true;}
      if(NKJKFnntDY == FaaUBmNGqd){xgMraIUfxs = true;}
      else if(FaaUBmNGqd == NKJKFnntDY){gVTTuOlEIB = true;}
      if(sDZSOUryNS == LutqfRYRxF){fglrKmNETs = true;}
      else if(LutqfRYRxF == sDZSOUryNS){OdRqybnxRO = true;}
      if(rhuCctMArw == NWBShBkjgF){nqwHyIXBHr = true;}
      else if(NWBShBkjgF == rhuCctMArw){FeMDgmLglW = true;}
      if(JyUkpyMtLD == uPFPiDhthV){mURTxHCXtJ = true;}
      if(AYMcqnQDkI == uaTJxmLUUK){UbBnUwnOWf = true;}
      if(lzQJxfOGgK == nFHHgiYHlA){EwOgNFkFsS = true;}
      while(uPFPiDhthV == JyUkpyMtLD){ItYdUxnLfY = true;}
      while(uaTJxmLUUK == uaTJxmLUUK){EBbDcsemcw = true;}
      while(nFHHgiYHlA == nFHHgiYHlA){MGcSDCJQmH = true;}
      if(CcZkiwpeIc == true){CcZkiwpeIc = false;}
      if(iejaKmCrVt == true){iejaKmCrVt = false;}
      if(oPPVRpHyhA == true){oPPVRpHyhA = false;}
      if(daHhTRAhZB == true){daHhTRAhZB = false;}
      if(xgMraIUfxs == true){xgMraIUfxs = false;}
      if(fglrKmNETs == true){fglrKmNETs = false;}
      if(nqwHyIXBHr == true){nqwHyIXBHr = false;}
      if(mURTxHCXtJ == true){mURTxHCXtJ = false;}
      if(UbBnUwnOWf == true){UbBnUwnOWf = false;}
      if(EwOgNFkFsS == true){EwOgNFkFsS = false;}
      if(kTXFGLPStD == true){kTXFGLPStD = false;}
      if(kpJKYLpHmC == true){kpJKYLpHmC = false;}
      if(TIeamqFjFq == true){TIeamqFjFq = false;}
      if(WxdbYBDuhI == true){WxdbYBDuhI = false;}
      if(gVTTuOlEIB == true){gVTTuOlEIB = false;}
      if(OdRqybnxRO == true){OdRqybnxRO = false;}
      if(FeMDgmLglW == true){FeMDgmLglW = false;}
      if(ItYdUxnLfY == true){ItYdUxnLfY = false;}
      if(EBbDcsemcw == true){EBbDcsemcw = false;}
      if(MGcSDCJQmH == true){MGcSDCJQmH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJWAACHISC
{ 
  void UZBxbkQCLt()
  { 
      bool iXYQlIRsBU = false;
      bool OhzMkpToeI = false;
      bool NFQcUDuBwk = false;
      bool rhGuZoSzXD = false;
      bool lNlGUBViiR = false;
      bool NwMKSdGuuh = false;
      bool NQxPbfbDlw = false;
      bool XUQaVASKIT = false;
      bool gLSdXwVubw = false;
      bool hWDopVPVdn = false;
      bool ZSwmsreknS = false;
      bool KwmbBBxSre = false;
      bool KfapNBQakA = false;
      bool jwgUsOOfke = false;
      bool RkGJkljann = false;
      bool XxdydtqGYr = false;
      bool aDznhNORim = false;
      bool mRhMNYYRFb = false;
      bool QpmwbmSiqz = false;
      bool XIGrENkSbX = false;
      string sIfTkacRBl;
      string wzQqMEdjEG;
      string ibqXMaEwiI;
      string ObGSpuqddC;
      string mMhcipPEXn;
      string JbWUdRQIHJ;
      string VfirXUsxBQ;
      string MzFBSWsOoV;
      string LAXtzmFkoY;
      string eiWTgHcpFO;
      string xRDHbJVUCH;
      string XCSkyVHnsk;
      string OIIblcckUL;
      string sDIaYswQSo;
      string RkhhAcQkVK;
      string znxUzoJaUy;
      string gjzqNTsrME;
      string YpVDSdZabI;
      string MqPJLEGnai;
      string jVuTHgkqTf;
      if(sIfTkacRBl == xRDHbJVUCH){iXYQlIRsBU = true;}
      else if(xRDHbJVUCH == sIfTkacRBl){ZSwmsreknS = true;}
      if(wzQqMEdjEG == XCSkyVHnsk){OhzMkpToeI = true;}
      else if(XCSkyVHnsk == wzQqMEdjEG){KwmbBBxSre = true;}
      if(ibqXMaEwiI == OIIblcckUL){NFQcUDuBwk = true;}
      else if(OIIblcckUL == ibqXMaEwiI){KfapNBQakA = true;}
      if(ObGSpuqddC == sDIaYswQSo){rhGuZoSzXD = true;}
      else if(sDIaYswQSo == ObGSpuqddC){jwgUsOOfke = true;}
      if(mMhcipPEXn == RkhhAcQkVK){lNlGUBViiR = true;}
      else if(RkhhAcQkVK == mMhcipPEXn){RkGJkljann = true;}
      if(JbWUdRQIHJ == znxUzoJaUy){NwMKSdGuuh = true;}
      else if(znxUzoJaUy == JbWUdRQIHJ){XxdydtqGYr = true;}
      if(VfirXUsxBQ == gjzqNTsrME){NQxPbfbDlw = true;}
      else if(gjzqNTsrME == VfirXUsxBQ){aDznhNORim = true;}
      if(MzFBSWsOoV == YpVDSdZabI){XUQaVASKIT = true;}
      if(LAXtzmFkoY == MqPJLEGnai){gLSdXwVubw = true;}
      if(eiWTgHcpFO == jVuTHgkqTf){hWDopVPVdn = true;}
      while(YpVDSdZabI == MzFBSWsOoV){mRhMNYYRFb = true;}
      while(MqPJLEGnai == MqPJLEGnai){QpmwbmSiqz = true;}
      while(jVuTHgkqTf == jVuTHgkqTf){XIGrENkSbX = true;}
      if(iXYQlIRsBU == true){iXYQlIRsBU = false;}
      if(OhzMkpToeI == true){OhzMkpToeI = false;}
      if(NFQcUDuBwk == true){NFQcUDuBwk = false;}
      if(rhGuZoSzXD == true){rhGuZoSzXD = false;}
      if(lNlGUBViiR == true){lNlGUBViiR = false;}
      if(NwMKSdGuuh == true){NwMKSdGuuh = false;}
      if(NQxPbfbDlw == true){NQxPbfbDlw = false;}
      if(XUQaVASKIT == true){XUQaVASKIT = false;}
      if(gLSdXwVubw == true){gLSdXwVubw = false;}
      if(hWDopVPVdn == true){hWDopVPVdn = false;}
      if(ZSwmsreknS == true){ZSwmsreknS = false;}
      if(KwmbBBxSre == true){KwmbBBxSre = false;}
      if(KfapNBQakA == true){KfapNBQakA = false;}
      if(jwgUsOOfke == true){jwgUsOOfke = false;}
      if(RkGJkljann == true){RkGJkljann = false;}
      if(XxdydtqGYr == true){XxdydtqGYr = false;}
      if(aDznhNORim == true){aDznhNORim = false;}
      if(mRhMNYYRFb == true){mRhMNYYRFb = false;}
      if(QpmwbmSiqz == true){QpmwbmSiqz = false;}
      if(XIGrENkSbX == true){XIGrENkSbX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JRKOATVVWG
{ 
  void UckMlMPYCE()
  { 
      bool SbpJCZmSwz = false;
      bool cMeEDJCVqX = false;
      bool JcJNaeBqln = false;
      bool qyFqSRocIQ = false;
      bool bBJuxLJicY = false;
      bool VDeimpSchX = false;
      bool XwgIIdGmkk = false;
      bool UZNawHTOPP = false;
      bool USNNSmTWEb = false;
      bool yMtjrfTAlT = false;
      bool EWxqDuoEme = false;
      bool WEMSCFhTpV = false;
      bool KjiIlIedhQ = false;
      bool nSbwKyUWJW = false;
      bool yOjYEtzbgl = false;
      bool xAKQJUmnEu = false;
      bool PLVVqEbQHE = false;
      bool kLKSWuAJDr = false;
      bool IDwwSmHLlo = false;
      bool KfRNGlsNhA = false;
      string TKzlHZGzqH;
      string ObLTolBkFw;
      string spLhecDdxZ;
      string iTNyqANzjW;
      string JLzJhjwLTw;
      string CkyXsdzQHd;
      string VcBRYtNNco;
      string XCAilhpBAt;
      string grJBXyVoFN;
      string AxrFAgJhkn;
      string VhieXzjOlK;
      string myQMxdSAsa;
      string XYIOnaKthE;
      string XIPLXyJdcX;
      string NGDtaBgeIW;
      string OJnJQxZTqx;
      string ooggldhEnz;
      string UnWUMQUNnl;
      string telKpOUFua;
      string XomfiYZVHw;
      if(TKzlHZGzqH == VhieXzjOlK){SbpJCZmSwz = true;}
      else if(VhieXzjOlK == TKzlHZGzqH){EWxqDuoEme = true;}
      if(ObLTolBkFw == myQMxdSAsa){cMeEDJCVqX = true;}
      else if(myQMxdSAsa == ObLTolBkFw){WEMSCFhTpV = true;}
      if(spLhecDdxZ == XYIOnaKthE){JcJNaeBqln = true;}
      else if(XYIOnaKthE == spLhecDdxZ){KjiIlIedhQ = true;}
      if(iTNyqANzjW == XIPLXyJdcX){qyFqSRocIQ = true;}
      else if(XIPLXyJdcX == iTNyqANzjW){nSbwKyUWJW = true;}
      if(JLzJhjwLTw == NGDtaBgeIW){bBJuxLJicY = true;}
      else if(NGDtaBgeIW == JLzJhjwLTw){yOjYEtzbgl = true;}
      if(CkyXsdzQHd == OJnJQxZTqx){VDeimpSchX = true;}
      else if(OJnJQxZTqx == CkyXsdzQHd){xAKQJUmnEu = true;}
      if(VcBRYtNNco == ooggldhEnz){XwgIIdGmkk = true;}
      else if(ooggldhEnz == VcBRYtNNco){PLVVqEbQHE = true;}
      if(XCAilhpBAt == UnWUMQUNnl){UZNawHTOPP = true;}
      if(grJBXyVoFN == telKpOUFua){USNNSmTWEb = true;}
      if(AxrFAgJhkn == XomfiYZVHw){yMtjrfTAlT = true;}
      while(UnWUMQUNnl == XCAilhpBAt){kLKSWuAJDr = true;}
      while(telKpOUFua == telKpOUFua){IDwwSmHLlo = true;}
      while(XomfiYZVHw == XomfiYZVHw){KfRNGlsNhA = true;}
      if(SbpJCZmSwz == true){SbpJCZmSwz = false;}
      if(cMeEDJCVqX == true){cMeEDJCVqX = false;}
      if(JcJNaeBqln == true){JcJNaeBqln = false;}
      if(qyFqSRocIQ == true){qyFqSRocIQ = false;}
      if(bBJuxLJicY == true){bBJuxLJicY = false;}
      if(VDeimpSchX == true){VDeimpSchX = false;}
      if(XwgIIdGmkk == true){XwgIIdGmkk = false;}
      if(UZNawHTOPP == true){UZNawHTOPP = false;}
      if(USNNSmTWEb == true){USNNSmTWEb = false;}
      if(yMtjrfTAlT == true){yMtjrfTAlT = false;}
      if(EWxqDuoEme == true){EWxqDuoEme = false;}
      if(WEMSCFhTpV == true){WEMSCFhTpV = false;}
      if(KjiIlIedhQ == true){KjiIlIedhQ = false;}
      if(nSbwKyUWJW == true){nSbwKyUWJW = false;}
      if(yOjYEtzbgl == true){yOjYEtzbgl = false;}
      if(xAKQJUmnEu == true){xAKQJUmnEu = false;}
      if(PLVVqEbQHE == true){PLVVqEbQHE = false;}
      if(kLKSWuAJDr == true){kLKSWuAJDr = false;}
      if(IDwwSmHLlo == true){IDwwSmHLlo = false;}
      if(KfRNGlsNhA == true){KfRNGlsNhA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMMWTTYIOX
{ 
  void fnMFNbEQNA()
  { 
      bool HZMqppDinD = false;
      bool wkwFygPPfE = false;
      bool ARbzmRGTwD = false;
      bool KibxeOmMIV = false;
      bool TNWJulzTrj = false;
      bool QXeYLpyNEX = false;
      bool iiljrMJzai = false;
      bool tDGJkmtRDA = false;
      bool SmbMlmDDln = false;
      bool PYHkljamRh = false;
      bool cArIoNQVnY = false;
      bool ugKDFwHZxF = false;
      bool JFMlTUuVWB = false;
      bool MGAUXRtSWY = false;
      bool VgONsiOEep = false;
      bool bApLYWmGoT = false;
      bool SuymLofofm = false;
      bool CoDXicpzsj = false;
      bool GqpgYLQnwB = false;
      bool encDGaibBD = false;
      string zLQhsHoyuk;
      string jbFGTPCzkq;
      string HHHslBPNmz;
      string cMAZpApWSM;
      string sQFQaPinhQ;
      string PEqXFrDWur;
      string qbLwIWafPS;
      string YefYyqCqSW;
      string SaeViXVcTy;
      string wTbaUQEJID;
      string nDXOrjYSYO;
      string oLEYZQwoMj;
      string ByLRWEDFDg;
      string lsiOhOCQdy;
      string zCDFIjPDBE;
      string UOwXBpqGrm;
      string gSOrbwcopK;
      string NeLNjytFJl;
      string ozDzLWwLMq;
      string XwYqRfnLdL;
      if(zLQhsHoyuk == nDXOrjYSYO){HZMqppDinD = true;}
      else if(nDXOrjYSYO == zLQhsHoyuk){cArIoNQVnY = true;}
      if(jbFGTPCzkq == oLEYZQwoMj){wkwFygPPfE = true;}
      else if(oLEYZQwoMj == jbFGTPCzkq){ugKDFwHZxF = true;}
      if(HHHslBPNmz == ByLRWEDFDg){ARbzmRGTwD = true;}
      else if(ByLRWEDFDg == HHHslBPNmz){JFMlTUuVWB = true;}
      if(cMAZpApWSM == lsiOhOCQdy){KibxeOmMIV = true;}
      else if(lsiOhOCQdy == cMAZpApWSM){MGAUXRtSWY = true;}
      if(sQFQaPinhQ == zCDFIjPDBE){TNWJulzTrj = true;}
      else if(zCDFIjPDBE == sQFQaPinhQ){VgONsiOEep = true;}
      if(PEqXFrDWur == UOwXBpqGrm){QXeYLpyNEX = true;}
      else if(UOwXBpqGrm == PEqXFrDWur){bApLYWmGoT = true;}
      if(qbLwIWafPS == gSOrbwcopK){iiljrMJzai = true;}
      else if(gSOrbwcopK == qbLwIWafPS){SuymLofofm = true;}
      if(YefYyqCqSW == NeLNjytFJl){tDGJkmtRDA = true;}
      if(SaeViXVcTy == ozDzLWwLMq){SmbMlmDDln = true;}
      if(wTbaUQEJID == XwYqRfnLdL){PYHkljamRh = true;}
      while(NeLNjytFJl == YefYyqCqSW){CoDXicpzsj = true;}
      while(ozDzLWwLMq == ozDzLWwLMq){GqpgYLQnwB = true;}
      while(XwYqRfnLdL == XwYqRfnLdL){encDGaibBD = true;}
      if(HZMqppDinD == true){HZMqppDinD = false;}
      if(wkwFygPPfE == true){wkwFygPPfE = false;}
      if(ARbzmRGTwD == true){ARbzmRGTwD = false;}
      if(KibxeOmMIV == true){KibxeOmMIV = false;}
      if(TNWJulzTrj == true){TNWJulzTrj = false;}
      if(QXeYLpyNEX == true){QXeYLpyNEX = false;}
      if(iiljrMJzai == true){iiljrMJzai = false;}
      if(tDGJkmtRDA == true){tDGJkmtRDA = false;}
      if(SmbMlmDDln == true){SmbMlmDDln = false;}
      if(PYHkljamRh == true){PYHkljamRh = false;}
      if(cArIoNQVnY == true){cArIoNQVnY = false;}
      if(ugKDFwHZxF == true){ugKDFwHZxF = false;}
      if(JFMlTUuVWB == true){JFMlTUuVWB = false;}
      if(MGAUXRtSWY == true){MGAUXRtSWY = false;}
      if(VgONsiOEep == true){VgONsiOEep = false;}
      if(bApLYWmGoT == true){bApLYWmGoT = false;}
      if(SuymLofofm == true){SuymLofofm = false;}
      if(CoDXicpzsj == true){CoDXicpzsj = false;}
      if(GqpgYLQnwB == true){GqpgYLQnwB = false;}
      if(encDGaibBD == true){encDGaibBD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUYHTRLRVH
{ 
  void eudWpuyzWB()
  { 
      bool ZHTTIwXhCQ = false;
      bool MqjfalPXXD = false;
      bool iteMzSKLAa = false;
      bool qcicKlRqpy = false;
      bool AzlpGLqaAa = false;
      bool fJlPLecHTp = false;
      bool kMgbYiIHVn = false;
      bool UYhYCjHnFn = false;
      bool aiKZuhpSRe = false;
      bool JJWAMnRJRW = false;
      bool DjFLGHbNMa = false;
      bool XnBfOCBHgq = false;
      bool sooqeLBgLO = false;
      bool RyWikqdyTm = false;
      bool GcFpHUHqlK = false;
      bool lKcadNtNgt = false;
      bool FtByIYQStW = false;
      bool YDnsjPiyjJ = false;
      bool DKuBbHUwFW = false;
      bool xPRYhLbHgh = false;
      string iFuFbXKMgX;
      string qOuTgxQQXo;
      string DObsWlOmbm;
      string wjsqbifgLo;
      string bcotblxkFY;
      string sOGokUdBio;
      string IWksaHVErx;
      string RiFiNaYgRj;
      string odgCtgcEFH;
      string FdyWgEruSU;
      string QrsIHJJXbK;
      string uxjyzephzs;
      string dQyjrmkhBI;
      string hdNxSxjXuk;
      string WEcuMItzWC;
      string NKwYpAtIQT;
      string XaWSbQileC;
      string tRlNWYmCXj;
      string slLytXhoHS;
      string CbHaMuhKTu;
      if(iFuFbXKMgX == QrsIHJJXbK){ZHTTIwXhCQ = true;}
      else if(QrsIHJJXbK == iFuFbXKMgX){DjFLGHbNMa = true;}
      if(qOuTgxQQXo == uxjyzephzs){MqjfalPXXD = true;}
      else if(uxjyzephzs == qOuTgxQQXo){XnBfOCBHgq = true;}
      if(DObsWlOmbm == dQyjrmkhBI){iteMzSKLAa = true;}
      else if(dQyjrmkhBI == DObsWlOmbm){sooqeLBgLO = true;}
      if(wjsqbifgLo == hdNxSxjXuk){qcicKlRqpy = true;}
      else if(hdNxSxjXuk == wjsqbifgLo){RyWikqdyTm = true;}
      if(bcotblxkFY == WEcuMItzWC){AzlpGLqaAa = true;}
      else if(WEcuMItzWC == bcotblxkFY){GcFpHUHqlK = true;}
      if(sOGokUdBio == NKwYpAtIQT){fJlPLecHTp = true;}
      else if(NKwYpAtIQT == sOGokUdBio){lKcadNtNgt = true;}
      if(IWksaHVErx == XaWSbQileC){kMgbYiIHVn = true;}
      else if(XaWSbQileC == IWksaHVErx){FtByIYQStW = true;}
      if(RiFiNaYgRj == tRlNWYmCXj){UYhYCjHnFn = true;}
      if(odgCtgcEFH == slLytXhoHS){aiKZuhpSRe = true;}
      if(FdyWgEruSU == CbHaMuhKTu){JJWAMnRJRW = true;}
      while(tRlNWYmCXj == RiFiNaYgRj){YDnsjPiyjJ = true;}
      while(slLytXhoHS == slLytXhoHS){DKuBbHUwFW = true;}
      while(CbHaMuhKTu == CbHaMuhKTu){xPRYhLbHgh = true;}
      if(ZHTTIwXhCQ == true){ZHTTIwXhCQ = false;}
      if(MqjfalPXXD == true){MqjfalPXXD = false;}
      if(iteMzSKLAa == true){iteMzSKLAa = false;}
      if(qcicKlRqpy == true){qcicKlRqpy = false;}
      if(AzlpGLqaAa == true){AzlpGLqaAa = false;}
      if(fJlPLecHTp == true){fJlPLecHTp = false;}
      if(kMgbYiIHVn == true){kMgbYiIHVn = false;}
      if(UYhYCjHnFn == true){UYhYCjHnFn = false;}
      if(aiKZuhpSRe == true){aiKZuhpSRe = false;}
      if(JJWAMnRJRW == true){JJWAMnRJRW = false;}
      if(DjFLGHbNMa == true){DjFLGHbNMa = false;}
      if(XnBfOCBHgq == true){XnBfOCBHgq = false;}
      if(sooqeLBgLO == true){sooqeLBgLO = false;}
      if(RyWikqdyTm == true){RyWikqdyTm = false;}
      if(GcFpHUHqlK == true){GcFpHUHqlK = false;}
      if(lKcadNtNgt == true){lKcadNtNgt = false;}
      if(FtByIYQStW == true){FtByIYQStW = false;}
      if(YDnsjPiyjJ == true){YDnsjPiyjJ = false;}
      if(DKuBbHUwFW == true){DKuBbHUwFW = false;}
      if(xPRYhLbHgh == true){xPRYhLbHgh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BUMWNIZQJM
{ 
  void sNJcxAfHIh()
  { 
      bool MVSNQnIErO = false;
      bool aJYPDrCQJC = false;
      bool ugMsuztQQI = false;
      bool OMLfYfKiSW = false;
      bool SnwJLkQxla = false;
      bool NHerFeJYRR = false;
      bool tqnjANxrqW = false;
      bool hSyliHkChK = false;
      bool ixdotGgTZs = false;
      bool VlQAcbzMIx = false;
      bool nXFPstJsIx = false;
      bool tGqGiwMyot = false;
      bool fcSxAuBxIH = false;
      bool IYtjWKqOuz = false;
      bool xnLbyPuJRf = false;
      bool OBWOQKEIOx = false;
      bool sLjBoVMGjX = false;
      bool EyCpwrRpyk = false;
      bool ArebrGBeTL = false;
      bool GizyGkDKlc = false;
      string pxhlXybQWU;
      string LipKQyNQdp;
      string mYNgnSnZDI;
      string TilUbpUqKz;
      string RedFqkONsr;
      string TFTAcQiByF;
      string KBNOBcxViZ;
      string cVGdXIuIoC;
      string DagKnNPlrK;
      string HSsFoQRODO;
      string nseSPyzpbT;
      string UZLuBjUCZm;
      string MLdXSJbAoH;
      string pgEaOKuNup;
      string OZJXpgHyEF;
      string uPnQBcPGAF;
      string VyAUcnUkfp;
      string nHGjYmBGhk;
      string CcwjLarnYl;
      string toMpTPYntB;
      if(pxhlXybQWU == nseSPyzpbT){MVSNQnIErO = true;}
      else if(nseSPyzpbT == pxhlXybQWU){nXFPstJsIx = true;}
      if(LipKQyNQdp == UZLuBjUCZm){aJYPDrCQJC = true;}
      else if(UZLuBjUCZm == LipKQyNQdp){tGqGiwMyot = true;}
      if(mYNgnSnZDI == MLdXSJbAoH){ugMsuztQQI = true;}
      else if(MLdXSJbAoH == mYNgnSnZDI){fcSxAuBxIH = true;}
      if(TilUbpUqKz == pgEaOKuNup){OMLfYfKiSW = true;}
      else if(pgEaOKuNup == TilUbpUqKz){IYtjWKqOuz = true;}
      if(RedFqkONsr == OZJXpgHyEF){SnwJLkQxla = true;}
      else if(OZJXpgHyEF == RedFqkONsr){xnLbyPuJRf = true;}
      if(TFTAcQiByF == uPnQBcPGAF){NHerFeJYRR = true;}
      else if(uPnQBcPGAF == TFTAcQiByF){OBWOQKEIOx = true;}
      if(KBNOBcxViZ == VyAUcnUkfp){tqnjANxrqW = true;}
      else if(VyAUcnUkfp == KBNOBcxViZ){sLjBoVMGjX = true;}
      if(cVGdXIuIoC == nHGjYmBGhk){hSyliHkChK = true;}
      if(DagKnNPlrK == CcwjLarnYl){ixdotGgTZs = true;}
      if(HSsFoQRODO == toMpTPYntB){VlQAcbzMIx = true;}
      while(nHGjYmBGhk == cVGdXIuIoC){EyCpwrRpyk = true;}
      while(CcwjLarnYl == CcwjLarnYl){ArebrGBeTL = true;}
      while(toMpTPYntB == toMpTPYntB){GizyGkDKlc = true;}
      if(MVSNQnIErO == true){MVSNQnIErO = false;}
      if(aJYPDrCQJC == true){aJYPDrCQJC = false;}
      if(ugMsuztQQI == true){ugMsuztQQI = false;}
      if(OMLfYfKiSW == true){OMLfYfKiSW = false;}
      if(SnwJLkQxla == true){SnwJLkQxla = false;}
      if(NHerFeJYRR == true){NHerFeJYRR = false;}
      if(tqnjANxrqW == true){tqnjANxrqW = false;}
      if(hSyliHkChK == true){hSyliHkChK = false;}
      if(ixdotGgTZs == true){ixdotGgTZs = false;}
      if(VlQAcbzMIx == true){VlQAcbzMIx = false;}
      if(nXFPstJsIx == true){nXFPstJsIx = false;}
      if(tGqGiwMyot == true){tGqGiwMyot = false;}
      if(fcSxAuBxIH == true){fcSxAuBxIH = false;}
      if(IYtjWKqOuz == true){IYtjWKqOuz = false;}
      if(xnLbyPuJRf == true){xnLbyPuJRf = false;}
      if(OBWOQKEIOx == true){OBWOQKEIOx = false;}
      if(sLjBoVMGjX == true){sLjBoVMGjX = false;}
      if(EyCpwrRpyk == true){EyCpwrRpyk = false;}
      if(ArebrGBeTL == true){ArebrGBeTL = false;}
      if(GizyGkDKlc == true){GizyGkDKlc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HUBTIVPHRQ
{ 
  void FPWdxJqRBX()
  { 
      bool UxzXkAKAaV = false;
      bool JSYzkEdzCK = false;
      bool DDVdDsxIbS = false;
      bool sIgYYPhPsB = false;
      bool nxhBRmoYim = false;
      bool PsBkBRbVTq = false;
      bool CCXIbBlzZU = false;
      bool WNGBWFUTMP = false;
      bool DYYnCAGwXH = false;
      bool nLuBzlYZZQ = false;
      bool BpyNQBlAOu = false;
      bool wIJDndciFb = false;
      bool uoaSgKREBj = false;
      bool gusuOMZLXB = false;
      bool NFhbKeCrNU = false;
      bool IpTxVMOfgF = false;
      bool ihzdOAONoa = false;
      bool ERLEOoHzIC = false;
      bool HZpgbpbuZB = false;
      bool yteSReGENJ = false;
      string cAOzqmqUoa;
      string sMOzVCMHjQ;
      string kSktzxHUxh;
      string FMBblEiMow;
      string gJceyFQBjX;
      string bGnMYKOTAt;
      string eWWHVgLlMQ;
      string TARniaoFwt;
      string gGjYGzXnDb;
      string pOMuRJmVJQ;
      string tdnSEanAdy;
      string UIXFMYmyAW;
      string JWhkaEnWWY;
      string nTwezCRQUe;
      string KWJFGgpGhr;
      string WnVmHWwDrz;
      string mRdFJBMsGK;
      string HVdULlNcds;
      string NhndCzxJXb;
      string GOXUrssEuF;
      if(cAOzqmqUoa == tdnSEanAdy){UxzXkAKAaV = true;}
      else if(tdnSEanAdy == cAOzqmqUoa){BpyNQBlAOu = true;}
      if(sMOzVCMHjQ == UIXFMYmyAW){JSYzkEdzCK = true;}
      else if(UIXFMYmyAW == sMOzVCMHjQ){wIJDndciFb = true;}
      if(kSktzxHUxh == JWhkaEnWWY){DDVdDsxIbS = true;}
      else if(JWhkaEnWWY == kSktzxHUxh){uoaSgKREBj = true;}
      if(FMBblEiMow == nTwezCRQUe){sIgYYPhPsB = true;}
      else if(nTwezCRQUe == FMBblEiMow){gusuOMZLXB = true;}
      if(gJceyFQBjX == KWJFGgpGhr){nxhBRmoYim = true;}
      else if(KWJFGgpGhr == gJceyFQBjX){NFhbKeCrNU = true;}
      if(bGnMYKOTAt == WnVmHWwDrz){PsBkBRbVTq = true;}
      else if(WnVmHWwDrz == bGnMYKOTAt){IpTxVMOfgF = true;}
      if(eWWHVgLlMQ == mRdFJBMsGK){CCXIbBlzZU = true;}
      else if(mRdFJBMsGK == eWWHVgLlMQ){ihzdOAONoa = true;}
      if(TARniaoFwt == HVdULlNcds){WNGBWFUTMP = true;}
      if(gGjYGzXnDb == NhndCzxJXb){DYYnCAGwXH = true;}
      if(pOMuRJmVJQ == GOXUrssEuF){nLuBzlYZZQ = true;}
      while(HVdULlNcds == TARniaoFwt){ERLEOoHzIC = true;}
      while(NhndCzxJXb == NhndCzxJXb){HZpgbpbuZB = true;}
      while(GOXUrssEuF == GOXUrssEuF){yteSReGENJ = true;}
      if(UxzXkAKAaV == true){UxzXkAKAaV = false;}
      if(JSYzkEdzCK == true){JSYzkEdzCK = false;}
      if(DDVdDsxIbS == true){DDVdDsxIbS = false;}
      if(sIgYYPhPsB == true){sIgYYPhPsB = false;}
      if(nxhBRmoYim == true){nxhBRmoYim = false;}
      if(PsBkBRbVTq == true){PsBkBRbVTq = false;}
      if(CCXIbBlzZU == true){CCXIbBlzZU = false;}
      if(WNGBWFUTMP == true){WNGBWFUTMP = false;}
      if(DYYnCAGwXH == true){DYYnCAGwXH = false;}
      if(nLuBzlYZZQ == true){nLuBzlYZZQ = false;}
      if(BpyNQBlAOu == true){BpyNQBlAOu = false;}
      if(wIJDndciFb == true){wIJDndciFb = false;}
      if(uoaSgKREBj == true){uoaSgKREBj = false;}
      if(gusuOMZLXB == true){gusuOMZLXB = false;}
      if(NFhbKeCrNU == true){NFhbKeCrNU = false;}
      if(IpTxVMOfgF == true){IpTxVMOfgF = false;}
      if(ihzdOAONoa == true){ihzdOAONoa = false;}
      if(ERLEOoHzIC == true){ERLEOoHzIC = false;}
      if(HZpgbpbuZB == true){HZpgbpbuZB = false;}
      if(yteSReGENJ == true){yteSReGENJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COSZXBISLX
{ 
  void nGDlJywTFK()
  { 
      bool nJcgQPOhZY = false;
      bool iCWoLtNVMi = false;
      bool uxSiwRwTqF = false;
      bool BORcguRXyF = false;
      bool bMdLTBYZDG = false;
      bool xZcDAqptkz = false;
      bool TtpUWUksHQ = false;
      bool cpXGGhSHOu = false;
      bool rVPjHakNbp = false;
      bool EWmzkhWJoy = false;
      bool QfSmdHCVwR = false;
      bool XiepGxdFMu = false;
      bool iWQQLFCYUX = false;
      bool LJRQeMDcGA = false;
      bool YORJSVqwrn = false;
      bool EQxtOsOBbX = false;
      bool EcBYGOQOLs = false;
      bool tBzMVTEHyo = false;
      bool OFggSuLXBk = false;
      bool yBAhuwNrDE = false;
      string GfcidNMQNB;
      string KbmzRicDMS;
      string yNCHAqMYlo;
      string TSxupQsabj;
      string EthUwtMPYX;
      string AhGtTrdVim;
      string BneXhreqJA;
      string oBbbOEfgKG;
      string dxAOokLDby;
      string mXroiQOJmD;
      string OVGYhyGdfP;
      string LwKcIEnQiw;
      string faPKMRJlsy;
      string oVtHqIqafp;
      string ehWLlpMOgd;
      string cyapWnFuLQ;
      string oTkhZpBDlz;
      string NMjsQyEDYV;
      string EtFOVquEjD;
      string DuPPBLwolu;
      if(GfcidNMQNB == OVGYhyGdfP){nJcgQPOhZY = true;}
      else if(OVGYhyGdfP == GfcidNMQNB){QfSmdHCVwR = true;}
      if(KbmzRicDMS == LwKcIEnQiw){iCWoLtNVMi = true;}
      else if(LwKcIEnQiw == KbmzRicDMS){XiepGxdFMu = true;}
      if(yNCHAqMYlo == faPKMRJlsy){uxSiwRwTqF = true;}
      else if(faPKMRJlsy == yNCHAqMYlo){iWQQLFCYUX = true;}
      if(TSxupQsabj == oVtHqIqafp){BORcguRXyF = true;}
      else if(oVtHqIqafp == TSxupQsabj){LJRQeMDcGA = true;}
      if(EthUwtMPYX == ehWLlpMOgd){bMdLTBYZDG = true;}
      else if(ehWLlpMOgd == EthUwtMPYX){YORJSVqwrn = true;}
      if(AhGtTrdVim == cyapWnFuLQ){xZcDAqptkz = true;}
      else if(cyapWnFuLQ == AhGtTrdVim){EQxtOsOBbX = true;}
      if(BneXhreqJA == oTkhZpBDlz){TtpUWUksHQ = true;}
      else if(oTkhZpBDlz == BneXhreqJA){EcBYGOQOLs = true;}
      if(oBbbOEfgKG == NMjsQyEDYV){cpXGGhSHOu = true;}
      if(dxAOokLDby == EtFOVquEjD){rVPjHakNbp = true;}
      if(mXroiQOJmD == DuPPBLwolu){EWmzkhWJoy = true;}
      while(NMjsQyEDYV == oBbbOEfgKG){tBzMVTEHyo = true;}
      while(EtFOVquEjD == EtFOVquEjD){OFggSuLXBk = true;}
      while(DuPPBLwolu == DuPPBLwolu){yBAhuwNrDE = true;}
      if(nJcgQPOhZY == true){nJcgQPOhZY = false;}
      if(iCWoLtNVMi == true){iCWoLtNVMi = false;}
      if(uxSiwRwTqF == true){uxSiwRwTqF = false;}
      if(BORcguRXyF == true){BORcguRXyF = false;}
      if(bMdLTBYZDG == true){bMdLTBYZDG = false;}
      if(xZcDAqptkz == true){xZcDAqptkz = false;}
      if(TtpUWUksHQ == true){TtpUWUksHQ = false;}
      if(cpXGGhSHOu == true){cpXGGhSHOu = false;}
      if(rVPjHakNbp == true){rVPjHakNbp = false;}
      if(EWmzkhWJoy == true){EWmzkhWJoy = false;}
      if(QfSmdHCVwR == true){QfSmdHCVwR = false;}
      if(XiepGxdFMu == true){XiepGxdFMu = false;}
      if(iWQQLFCYUX == true){iWQQLFCYUX = false;}
      if(LJRQeMDcGA == true){LJRQeMDcGA = false;}
      if(YORJSVqwrn == true){YORJSVqwrn = false;}
      if(EQxtOsOBbX == true){EQxtOsOBbX = false;}
      if(EcBYGOQOLs == true){EcBYGOQOLs = false;}
      if(tBzMVTEHyo == true){tBzMVTEHyo = false;}
      if(OFggSuLXBk == true){OFggSuLXBk = false;}
      if(yBAhuwNrDE == true){yBAhuwNrDE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJMITXAIFS
{ 
  void jpcjjAYcsF()
  { 
      bool pUktkrjDoM = false;
      bool pZCxOgIfHE = false;
      bool LwMVhIYWkH = false;
      bool spmHxuYJmU = false;
      bool bUXWFuOlth = false;
      bool hHTWlsHPMc = false;
      bool TNShSAmuzT = false;
      bool IzslcqYpPl = false;
      bool slbDZkVPUD = false;
      bool mIwKANCoDF = false;
      bool ISlaZiOgsu = false;
      bool URAZigkPHg = false;
      bool dWawfzChlO = false;
      bool nilKdZABcq = false;
      bool WoVYiVIVaT = false;
      bool cmgWakrptZ = false;
      bool fgueGkeowJ = false;
      bool filQKoBCMK = false;
      bool pfHRkBBPjr = false;
      bool hKGCKotqRx = false;
      string izLaYngEhU;
      string iqktHpJDjn;
      string QczkfANMjK;
      string AWBpFKSUlm;
      string xEkIiIqnUj;
      string wgmYEGAatX;
      string aTTXTMotox;
      string XoRwpMqpBX;
      string IZrAOSjcly;
      string JqaNMcjNoW;
      string TxzXLGPphr;
      string OKZWPAbTIB;
      string bLIpmgODjN;
      string bdBdELaTnH;
      string DtusjzQDyL;
      string APEntHoIke;
      string rMFTQkJwRD;
      string ZIfAyhQOFm;
      string PKEYMLYNiw;
      string VRiIPpnaby;
      if(izLaYngEhU == TxzXLGPphr){pUktkrjDoM = true;}
      else if(TxzXLGPphr == izLaYngEhU){ISlaZiOgsu = true;}
      if(iqktHpJDjn == OKZWPAbTIB){pZCxOgIfHE = true;}
      else if(OKZWPAbTIB == iqktHpJDjn){URAZigkPHg = true;}
      if(QczkfANMjK == bLIpmgODjN){LwMVhIYWkH = true;}
      else if(bLIpmgODjN == QczkfANMjK){dWawfzChlO = true;}
      if(AWBpFKSUlm == bdBdELaTnH){spmHxuYJmU = true;}
      else if(bdBdELaTnH == AWBpFKSUlm){nilKdZABcq = true;}
      if(xEkIiIqnUj == DtusjzQDyL){bUXWFuOlth = true;}
      else if(DtusjzQDyL == xEkIiIqnUj){WoVYiVIVaT = true;}
      if(wgmYEGAatX == APEntHoIke){hHTWlsHPMc = true;}
      else if(APEntHoIke == wgmYEGAatX){cmgWakrptZ = true;}
      if(aTTXTMotox == rMFTQkJwRD){TNShSAmuzT = true;}
      else if(rMFTQkJwRD == aTTXTMotox){fgueGkeowJ = true;}
      if(XoRwpMqpBX == ZIfAyhQOFm){IzslcqYpPl = true;}
      if(IZrAOSjcly == PKEYMLYNiw){slbDZkVPUD = true;}
      if(JqaNMcjNoW == VRiIPpnaby){mIwKANCoDF = true;}
      while(ZIfAyhQOFm == XoRwpMqpBX){filQKoBCMK = true;}
      while(PKEYMLYNiw == PKEYMLYNiw){pfHRkBBPjr = true;}
      while(VRiIPpnaby == VRiIPpnaby){hKGCKotqRx = true;}
      if(pUktkrjDoM == true){pUktkrjDoM = false;}
      if(pZCxOgIfHE == true){pZCxOgIfHE = false;}
      if(LwMVhIYWkH == true){LwMVhIYWkH = false;}
      if(spmHxuYJmU == true){spmHxuYJmU = false;}
      if(bUXWFuOlth == true){bUXWFuOlth = false;}
      if(hHTWlsHPMc == true){hHTWlsHPMc = false;}
      if(TNShSAmuzT == true){TNShSAmuzT = false;}
      if(IzslcqYpPl == true){IzslcqYpPl = false;}
      if(slbDZkVPUD == true){slbDZkVPUD = false;}
      if(mIwKANCoDF == true){mIwKANCoDF = false;}
      if(ISlaZiOgsu == true){ISlaZiOgsu = false;}
      if(URAZigkPHg == true){URAZigkPHg = false;}
      if(dWawfzChlO == true){dWawfzChlO = false;}
      if(nilKdZABcq == true){nilKdZABcq = false;}
      if(WoVYiVIVaT == true){WoVYiVIVaT = false;}
      if(cmgWakrptZ == true){cmgWakrptZ = false;}
      if(fgueGkeowJ == true){fgueGkeowJ = false;}
      if(filQKoBCMK == true){filQKoBCMK = false;}
      if(pfHRkBBPjr == true){pfHRkBBPjr = false;}
      if(hKGCKotqRx == true){hKGCKotqRx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZVGUCBDSK
{ 
  void ImWBiWjRhM()
  { 
      bool obRdhyjqmm = false;
      bool daTRBmiabt = false;
      bool YUECnIyZQh = false;
      bool LQmzFLqwGW = false;
      bool TQyoEJCxNI = false;
      bool dUMfdTWOpZ = false;
      bool zJZEaMnTMo = false;
      bool wmTEaHWPxd = false;
      bool FAMIEpDGVk = false;
      bool nbFfXJpsOr = false;
      bool VikXMqBHEV = false;
      bool xHQLUzxRzj = false;
      bool IgxaBTgngR = false;
      bool QcBFIVOowN = false;
      bool owBAmgKsLX = false;
      bool MYsdinkJVr = false;
      bool JMamETFKDy = false;
      bool jHVltMexmU = false;
      bool JmcIFriWWU = false;
      bool kESDDbUOuT = false;
      string fBthGBIUWD;
      string lwCAdQWTDG;
      string pWECjLZomV;
      string YmjQkSFEsN;
      string VyFgPoMXMx;
      string YOIQRIxryu;
      string aShAdzMkOK;
      string KRaojrQWmu;
      string zCcoxKeTyb;
      string VNGylCQFCP;
      string caIBlGmSfZ;
      string raEDuYprCT;
      string UslloxLcCh;
      string bKUWRXsbDp;
      string XLmYjuJCCN;
      string MXCiuinWLo;
      string uKPyygFgkX;
      string eNnLwIFNCt;
      string nIaoVDIkbh;
      string jWPOuNwoaC;
      if(fBthGBIUWD == caIBlGmSfZ){obRdhyjqmm = true;}
      else if(caIBlGmSfZ == fBthGBIUWD){VikXMqBHEV = true;}
      if(lwCAdQWTDG == raEDuYprCT){daTRBmiabt = true;}
      else if(raEDuYprCT == lwCAdQWTDG){xHQLUzxRzj = true;}
      if(pWECjLZomV == UslloxLcCh){YUECnIyZQh = true;}
      else if(UslloxLcCh == pWECjLZomV){IgxaBTgngR = true;}
      if(YmjQkSFEsN == bKUWRXsbDp){LQmzFLqwGW = true;}
      else if(bKUWRXsbDp == YmjQkSFEsN){QcBFIVOowN = true;}
      if(VyFgPoMXMx == XLmYjuJCCN){TQyoEJCxNI = true;}
      else if(XLmYjuJCCN == VyFgPoMXMx){owBAmgKsLX = true;}
      if(YOIQRIxryu == MXCiuinWLo){dUMfdTWOpZ = true;}
      else if(MXCiuinWLo == YOIQRIxryu){MYsdinkJVr = true;}
      if(aShAdzMkOK == uKPyygFgkX){zJZEaMnTMo = true;}
      else if(uKPyygFgkX == aShAdzMkOK){JMamETFKDy = true;}
      if(KRaojrQWmu == eNnLwIFNCt){wmTEaHWPxd = true;}
      if(zCcoxKeTyb == nIaoVDIkbh){FAMIEpDGVk = true;}
      if(VNGylCQFCP == jWPOuNwoaC){nbFfXJpsOr = true;}
      while(eNnLwIFNCt == KRaojrQWmu){jHVltMexmU = true;}
      while(nIaoVDIkbh == nIaoVDIkbh){JmcIFriWWU = true;}
      while(jWPOuNwoaC == jWPOuNwoaC){kESDDbUOuT = true;}
      if(obRdhyjqmm == true){obRdhyjqmm = false;}
      if(daTRBmiabt == true){daTRBmiabt = false;}
      if(YUECnIyZQh == true){YUECnIyZQh = false;}
      if(LQmzFLqwGW == true){LQmzFLqwGW = false;}
      if(TQyoEJCxNI == true){TQyoEJCxNI = false;}
      if(dUMfdTWOpZ == true){dUMfdTWOpZ = false;}
      if(zJZEaMnTMo == true){zJZEaMnTMo = false;}
      if(wmTEaHWPxd == true){wmTEaHWPxd = false;}
      if(FAMIEpDGVk == true){FAMIEpDGVk = false;}
      if(nbFfXJpsOr == true){nbFfXJpsOr = false;}
      if(VikXMqBHEV == true){VikXMqBHEV = false;}
      if(xHQLUzxRzj == true){xHQLUzxRzj = false;}
      if(IgxaBTgngR == true){IgxaBTgngR = false;}
      if(QcBFIVOowN == true){QcBFIVOowN = false;}
      if(owBAmgKsLX == true){owBAmgKsLX = false;}
      if(MYsdinkJVr == true){MYsdinkJVr = false;}
      if(JMamETFKDy == true){JMamETFKDy = false;}
      if(jHVltMexmU == true){jHVltMexmU = false;}
      if(JmcIFriWWU == true){JmcIFriWWU = false;}
      if(kESDDbUOuT == true){kESDDbUOuT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLKRLCMREU
{ 
  void cBspsjAEmn()
  { 
      bool TbixLVaSJf = false;
      bool VCWnLLCSHs = false;
      bool AuzZsyoCDG = false;
      bool PWDqsmLWFL = false;
      bool HXyHWEPnPq = false;
      bool nolfsXbIDM = false;
      bool gYODPzzetY = false;
      bool AfNukbxrDn = false;
      bool iAlLRZkWxV = false;
      bool KCSrdiJtqW = false;
      bool FjtqqHbpuQ = false;
      bool ZjFPdglCkp = false;
      bool ObgXNxNURC = false;
      bool RCBfiyFtUJ = false;
      bool ytbfwaxCNx = false;
      bool wHJAIcCVct = false;
      bool tGXszWhZge = false;
      bool argarTAAbm = false;
      bool AKGTFKsAWF = false;
      bool ujQaPqWhgY = false;
      string hnsndOiQbn;
      string yrARENtLWy;
      string rVwygyMXgB;
      string hlEEEfoCNe;
      string tUPTiVEpIb;
      string qjrNmMruGe;
      string CKjZGLnuMX;
      string XqyrEXFbPL;
      string tWOFJysqRq;
      string ntwhcijoNW;
      string hIckDAlAJP;
      string HQeukeuePI;
      string RxdVjctPPU;
      string mPNrcktdBI;
      string LsgBjWOAwx;
      string mEYFEkeHBZ;
      string FVknbqDmRz;
      string kRdGwYPckM;
      string OtTRgipHmr;
      string GlcaDpIsZs;
      if(hnsndOiQbn == hIckDAlAJP){TbixLVaSJf = true;}
      else if(hIckDAlAJP == hnsndOiQbn){FjtqqHbpuQ = true;}
      if(yrARENtLWy == HQeukeuePI){VCWnLLCSHs = true;}
      else if(HQeukeuePI == yrARENtLWy){ZjFPdglCkp = true;}
      if(rVwygyMXgB == RxdVjctPPU){AuzZsyoCDG = true;}
      else if(RxdVjctPPU == rVwygyMXgB){ObgXNxNURC = true;}
      if(hlEEEfoCNe == mPNrcktdBI){PWDqsmLWFL = true;}
      else if(mPNrcktdBI == hlEEEfoCNe){RCBfiyFtUJ = true;}
      if(tUPTiVEpIb == LsgBjWOAwx){HXyHWEPnPq = true;}
      else if(LsgBjWOAwx == tUPTiVEpIb){ytbfwaxCNx = true;}
      if(qjrNmMruGe == mEYFEkeHBZ){nolfsXbIDM = true;}
      else if(mEYFEkeHBZ == qjrNmMruGe){wHJAIcCVct = true;}
      if(CKjZGLnuMX == FVknbqDmRz){gYODPzzetY = true;}
      else if(FVknbqDmRz == CKjZGLnuMX){tGXszWhZge = true;}
      if(XqyrEXFbPL == kRdGwYPckM){AfNukbxrDn = true;}
      if(tWOFJysqRq == OtTRgipHmr){iAlLRZkWxV = true;}
      if(ntwhcijoNW == GlcaDpIsZs){KCSrdiJtqW = true;}
      while(kRdGwYPckM == XqyrEXFbPL){argarTAAbm = true;}
      while(OtTRgipHmr == OtTRgipHmr){AKGTFKsAWF = true;}
      while(GlcaDpIsZs == GlcaDpIsZs){ujQaPqWhgY = true;}
      if(TbixLVaSJf == true){TbixLVaSJf = false;}
      if(VCWnLLCSHs == true){VCWnLLCSHs = false;}
      if(AuzZsyoCDG == true){AuzZsyoCDG = false;}
      if(PWDqsmLWFL == true){PWDqsmLWFL = false;}
      if(HXyHWEPnPq == true){HXyHWEPnPq = false;}
      if(nolfsXbIDM == true){nolfsXbIDM = false;}
      if(gYODPzzetY == true){gYODPzzetY = false;}
      if(AfNukbxrDn == true){AfNukbxrDn = false;}
      if(iAlLRZkWxV == true){iAlLRZkWxV = false;}
      if(KCSrdiJtqW == true){KCSrdiJtqW = false;}
      if(FjtqqHbpuQ == true){FjtqqHbpuQ = false;}
      if(ZjFPdglCkp == true){ZjFPdglCkp = false;}
      if(ObgXNxNURC == true){ObgXNxNURC = false;}
      if(RCBfiyFtUJ == true){RCBfiyFtUJ = false;}
      if(ytbfwaxCNx == true){ytbfwaxCNx = false;}
      if(wHJAIcCVct == true){wHJAIcCVct = false;}
      if(tGXszWhZge == true){tGXszWhZge = false;}
      if(argarTAAbm == true){argarTAAbm = false;}
      if(AKGTFKsAWF == true){AKGTFKsAWF = false;}
      if(ujQaPqWhgY == true){ujQaPqWhgY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSBVDNYCSO
{ 
  void hSsmKfCuyf()
  { 
      bool MUEJZGmugu = false;
      bool xUsutPbepQ = false;
      bool iKfDqkDxJo = false;
      bool mFtpHaHeOm = false;
      bool ORsRsrqfHz = false;
      bool HWbdNCoASo = false;
      bool CokqIqaDnS = false;
      bool HwQCBQQOKy = false;
      bool tXoJhQcPcE = false;
      bool lHLZkYfBIB = false;
      bool RmrorKFZcw = false;
      bool kaoUuezaJq = false;
      bool NKZifzkqRb = false;
      bool jPFIfGeARW = false;
      bool KDlgTLRqeF = false;
      bool YFrRmHMJIr = false;
      bool ZOHALVUfnn = false;
      bool zzJlgKYsPU = false;
      bool hsMLCeXnVY = false;
      bool sVrYxwwkUy = false;
      string oCMTaygxXS;
      string hTYNRElpOt;
      string otcbDRjkKe;
      string cwYAOmoVyw;
      string ETcThsjJMQ;
      string BKVFetZkQI;
      string NumspluXye;
      string OPqRoVRJtJ;
      string haYtcRZTVU;
      string NEFohIfjdw;
      string xLKgBlSEPI;
      string cPpGalWsPX;
      string LbCdRKKCjf;
      string pgfxMWQqsq;
      string zVDNqxNyNu;
      string lmTFkVJfPp;
      string bPTjSujstE;
      string VezYYoYnlT;
      string wLnntCMZMp;
      string NkbCOiCStw;
      if(oCMTaygxXS == xLKgBlSEPI){MUEJZGmugu = true;}
      else if(xLKgBlSEPI == oCMTaygxXS){RmrorKFZcw = true;}
      if(hTYNRElpOt == cPpGalWsPX){xUsutPbepQ = true;}
      else if(cPpGalWsPX == hTYNRElpOt){kaoUuezaJq = true;}
      if(otcbDRjkKe == LbCdRKKCjf){iKfDqkDxJo = true;}
      else if(LbCdRKKCjf == otcbDRjkKe){NKZifzkqRb = true;}
      if(cwYAOmoVyw == pgfxMWQqsq){mFtpHaHeOm = true;}
      else if(pgfxMWQqsq == cwYAOmoVyw){jPFIfGeARW = true;}
      if(ETcThsjJMQ == zVDNqxNyNu){ORsRsrqfHz = true;}
      else if(zVDNqxNyNu == ETcThsjJMQ){KDlgTLRqeF = true;}
      if(BKVFetZkQI == lmTFkVJfPp){HWbdNCoASo = true;}
      else if(lmTFkVJfPp == BKVFetZkQI){YFrRmHMJIr = true;}
      if(NumspluXye == bPTjSujstE){CokqIqaDnS = true;}
      else if(bPTjSujstE == NumspluXye){ZOHALVUfnn = true;}
      if(OPqRoVRJtJ == VezYYoYnlT){HwQCBQQOKy = true;}
      if(haYtcRZTVU == wLnntCMZMp){tXoJhQcPcE = true;}
      if(NEFohIfjdw == NkbCOiCStw){lHLZkYfBIB = true;}
      while(VezYYoYnlT == OPqRoVRJtJ){zzJlgKYsPU = true;}
      while(wLnntCMZMp == wLnntCMZMp){hsMLCeXnVY = true;}
      while(NkbCOiCStw == NkbCOiCStw){sVrYxwwkUy = true;}
      if(MUEJZGmugu == true){MUEJZGmugu = false;}
      if(xUsutPbepQ == true){xUsutPbepQ = false;}
      if(iKfDqkDxJo == true){iKfDqkDxJo = false;}
      if(mFtpHaHeOm == true){mFtpHaHeOm = false;}
      if(ORsRsrqfHz == true){ORsRsrqfHz = false;}
      if(HWbdNCoASo == true){HWbdNCoASo = false;}
      if(CokqIqaDnS == true){CokqIqaDnS = false;}
      if(HwQCBQQOKy == true){HwQCBQQOKy = false;}
      if(tXoJhQcPcE == true){tXoJhQcPcE = false;}
      if(lHLZkYfBIB == true){lHLZkYfBIB = false;}
      if(RmrorKFZcw == true){RmrorKFZcw = false;}
      if(kaoUuezaJq == true){kaoUuezaJq = false;}
      if(NKZifzkqRb == true){NKZifzkqRb = false;}
      if(jPFIfGeARW == true){jPFIfGeARW = false;}
      if(KDlgTLRqeF == true){KDlgTLRqeF = false;}
      if(YFrRmHMJIr == true){YFrRmHMJIr = false;}
      if(ZOHALVUfnn == true){ZOHALVUfnn = false;}
      if(zzJlgKYsPU == true){zzJlgKYsPU = false;}
      if(hsMLCeXnVY == true){hsMLCeXnVY = false;}
      if(sVrYxwwkUy == true){sVrYxwwkUy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBDSIUQAXO
{ 
  void tIaFQVyqIP()
  { 
      bool aGVPgcLiBD = false;
      bool DzqxhhreyI = false;
      bool prrtYsiChE = false;
      bool SqahxHFsEH = false;
      bool jyzBrCkbZk = false;
      bool eILjxiOapn = false;
      bool tJAxjLXJAa = false;
      bool bzZpYqsqCW = false;
      bool IGbxZKfpjN = false;
      bool sdCPNZyCQf = false;
      bool dbbzIfhVLG = false;
      bool pXXTfmgDXZ = false;
      bool fgYlgywJby = false;
      bool rpZWrgecns = false;
      bool bJedXUFijZ = false;
      bool sueqzwCoRJ = false;
      bool iXsNNzyBbz = false;
      bool IDOdxVCtOL = false;
      bool rNZCFxLhWu = false;
      bool doLeKDQRQX = false;
      string HAYpitfzIs;
      string iNfxPwlgBT;
      string XoRaxeDOQI;
      string QORtRcNurB;
      string HTLHpuWXDx;
      string lpFSZSixrE;
      string pQhzbUukem;
      string hpnAMDcKkB;
      string HfLTWaJzTz;
      string sPCnLpkLeV;
      string AkrPOuBEFW;
      string oYMqxJEObB;
      string LuRfsRmAnW;
      string RRePAVnwEa;
      string YEsxKUDLqC;
      string kVjdKFTMVw;
      string IBQiEWsxpa;
      string UIKBbGBTUY;
      string OaIlkugBEu;
      string CbZHSXmKsm;
      if(HAYpitfzIs == AkrPOuBEFW){aGVPgcLiBD = true;}
      else if(AkrPOuBEFW == HAYpitfzIs){dbbzIfhVLG = true;}
      if(iNfxPwlgBT == oYMqxJEObB){DzqxhhreyI = true;}
      else if(oYMqxJEObB == iNfxPwlgBT){pXXTfmgDXZ = true;}
      if(XoRaxeDOQI == LuRfsRmAnW){prrtYsiChE = true;}
      else if(LuRfsRmAnW == XoRaxeDOQI){fgYlgywJby = true;}
      if(QORtRcNurB == RRePAVnwEa){SqahxHFsEH = true;}
      else if(RRePAVnwEa == QORtRcNurB){rpZWrgecns = true;}
      if(HTLHpuWXDx == YEsxKUDLqC){jyzBrCkbZk = true;}
      else if(YEsxKUDLqC == HTLHpuWXDx){bJedXUFijZ = true;}
      if(lpFSZSixrE == kVjdKFTMVw){eILjxiOapn = true;}
      else if(kVjdKFTMVw == lpFSZSixrE){sueqzwCoRJ = true;}
      if(pQhzbUukem == IBQiEWsxpa){tJAxjLXJAa = true;}
      else if(IBQiEWsxpa == pQhzbUukem){iXsNNzyBbz = true;}
      if(hpnAMDcKkB == UIKBbGBTUY){bzZpYqsqCW = true;}
      if(HfLTWaJzTz == OaIlkugBEu){IGbxZKfpjN = true;}
      if(sPCnLpkLeV == CbZHSXmKsm){sdCPNZyCQf = true;}
      while(UIKBbGBTUY == hpnAMDcKkB){IDOdxVCtOL = true;}
      while(OaIlkugBEu == OaIlkugBEu){rNZCFxLhWu = true;}
      while(CbZHSXmKsm == CbZHSXmKsm){doLeKDQRQX = true;}
      if(aGVPgcLiBD == true){aGVPgcLiBD = false;}
      if(DzqxhhreyI == true){DzqxhhreyI = false;}
      if(prrtYsiChE == true){prrtYsiChE = false;}
      if(SqahxHFsEH == true){SqahxHFsEH = false;}
      if(jyzBrCkbZk == true){jyzBrCkbZk = false;}
      if(eILjxiOapn == true){eILjxiOapn = false;}
      if(tJAxjLXJAa == true){tJAxjLXJAa = false;}
      if(bzZpYqsqCW == true){bzZpYqsqCW = false;}
      if(IGbxZKfpjN == true){IGbxZKfpjN = false;}
      if(sdCPNZyCQf == true){sdCPNZyCQf = false;}
      if(dbbzIfhVLG == true){dbbzIfhVLG = false;}
      if(pXXTfmgDXZ == true){pXXTfmgDXZ = false;}
      if(fgYlgywJby == true){fgYlgywJby = false;}
      if(rpZWrgecns == true){rpZWrgecns = false;}
      if(bJedXUFijZ == true){bJedXUFijZ = false;}
      if(sueqzwCoRJ == true){sueqzwCoRJ = false;}
      if(iXsNNzyBbz == true){iXsNNzyBbz = false;}
      if(IDOdxVCtOL == true){IDOdxVCtOL = false;}
      if(rNZCFxLhWu == true){rNZCFxLhWu = false;}
      if(doLeKDQRQX == true){doLeKDQRQX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTQOQFNTRQ
{ 
  void SqgEdqLtSw()
  { 
      bool uVlRKqNXAK = false;
      bool DnUZBqNnuK = false;
      bool cDinXqYCHp = false;
      bool iSzfLCXfpE = false;
      bool ClZIKsraQa = false;
      bool pMeqqqlxsS = false;
      bool SKPJaknoNz = false;
      bool SgyqHqcZcd = false;
      bool yxkgAWnInU = false;
      bool QamWlqVQhZ = false;
      bool FDMRIINniz = false;
      bool NMUOTUZiJD = false;
      bool wfAshrtbEQ = false;
      bool UMrCYujSXq = false;
      bool IAZoGDFXCQ = false;
      bool RmGddYCTiQ = false;
      bool NkiReBURpY = false;
      bool jGKStwGLmd = false;
      bool lWZnzhGNYz = false;
      bool sQjHcXRHKF = false;
      string FNllyNROlD;
      string zrESDimggP;
      string fHmhFiINfX;
      string wZMZDytjNK;
      string cgGMwmutRM;
      string DzcqXyZDgO;
      string EDhOGYfdOE;
      string nCTWlyBalR;
      string mOuSUwxVBF;
      string XpDyFYzrFW;
      string GQeNYAfGEZ;
      string xzROboHPsK;
      string bKcJfxzUQM;
      string zIUOLVjhtT;
      string PpQbIYYoWQ;
      string QiytuwnVga;
      string BLoqZndCCF;
      string FZVZtksAAH;
      string YKxAuPKZTO;
      string gNASREBZBU;
      if(FNllyNROlD == GQeNYAfGEZ){uVlRKqNXAK = true;}
      else if(GQeNYAfGEZ == FNllyNROlD){FDMRIINniz = true;}
      if(zrESDimggP == xzROboHPsK){DnUZBqNnuK = true;}
      else if(xzROboHPsK == zrESDimggP){NMUOTUZiJD = true;}
      if(fHmhFiINfX == bKcJfxzUQM){cDinXqYCHp = true;}
      else if(bKcJfxzUQM == fHmhFiINfX){wfAshrtbEQ = true;}
      if(wZMZDytjNK == zIUOLVjhtT){iSzfLCXfpE = true;}
      else if(zIUOLVjhtT == wZMZDytjNK){UMrCYujSXq = true;}
      if(cgGMwmutRM == PpQbIYYoWQ){ClZIKsraQa = true;}
      else if(PpQbIYYoWQ == cgGMwmutRM){IAZoGDFXCQ = true;}
      if(DzcqXyZDgO == QiytuwnVga){pMeqqqlxsS = true;}
      else if(QiytuwnVga == DzcqXyZDgO){RmGddYCTiQ = true;}
      if(EDhOGYfdOE == BLoqZndCCF){SKPJaknoNz = true;}
      else if(BLoqZndCCF == EDhOGYfdOE){NkiReBURpY = true;}
      if(nCTWlyBalR == FZVZtksAAH){SgyqHqcZcd = true;}
      if(mOuSUwxVBF == YKxAuPKZTO){yxkgAWnInU = true;}
      if(XpDyFYzrFW == gNASREBZBU){QamWlqVQhZ = true;}
      while(FZVZtksAAH == nCTWlyBalR){jGKStwGLmd = true;}
      while(YKxAuPKZTO == YKxAuPKZTO){lWZnzhGNYz = true;}
      while(gNASREBZBU == gNASREBZBU){sQjHcXRHKF = true;}
      if(uVlRKqNXAK == true){uVlRKqNXAK = false;}
      if(DnUZBqNnuK == true){DnUZBqNnuK = false;}
      if(cDinXqYCHp == true){cDinXqYCHp = false;}
      if(iSzfLCXfpE == true){iSzfLCXfpE = false;}
      if(ClZIKsraQa == true){ClZIKsraQa = false;}
      if(pMeqqqlxsS == true){pMeqqqlxsS = false;}
      if(SKPJaknoNz == true){SKPJaknoNz = false;}
      if(SgyqHqcZcd == true){SgyqHqcZcd = false;}
      if(yxkgAWnInU == true){yxkgAWnInU = false;}
      if(QamWlqVQhZ == true){QamWlqVQhZ = false;}
      if(FDMRIINniz == true){FDMRIINniz = false;}
      if(NMUOTUZiJD == true){NMUOTUZiJD = false;}
      if(wfAshrtbEQ == true){wfAshrtbEQ = false;}
      if(UMrCYujSXq == true){UMrCYujSXq = false;}
      if(IAZoGDFXCQ == true){IAZoGDFXCQ = false;}
      if(RmGddYCTiQ == true){RmGddYCTiQ = false;}
      if(NkiReBURpY == true){NkiReBURpY = false;}
      if(jGKStwGLmd == true){jGKStwGLmd = false;}
      if(lWZnzhGNYz == true){lWZnzhGNYz = false;}
      if(sQjHcXRHKF == true){sQjHcXRHKF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YIZWXIKZHO
{ 
  void uCmeCBKlee()
  { 
      bool HzkQsSGpdD = false;
      bool ijOfhilaBM = false;
      bool gHbUUKzTCB = false;
      bool tDFPgaqjcJ = false;
      bool KmhzRJRNlM = false;
      bool bKZYOzXPwh = false;
      bool TmnbJfdzzH = false;
      bool qBxqCtZbDK = false;
      bool skhoYjdgBg = false;
      bool DantpWzFpl = false;
      bool eROdVZMhWT = false;
      bool ZuMkohFzCZ = false;
      bool CxyRDQNDBe = false;
      bool uTlQfaVDTy = false;
      bool XuKgHHNDFH = false;
      bool RACQjhTxaE = false;
      bool MIfrYFJwEN = false;
      bool MBeEBGmQKw = false;
      bool CKxtMtQVgx = false;
      bool HYcOlOPSHB = false;
      string GCfFryzTiS;
      string eCnbCyJyYe;
      string yRNeMDytIY;
      string hfwYYnwiDi;
      string XXEwwCyxxQ;
      string UNsYRooAso;
      string AEKJkzGOCN;
      string BZtpHZMQiJ;
      string EBxrDTlWHj;
      string zwpOiSNtKw;
      string witiOuSDRq;
      string cYRijyHRGR;
      string NiHSOFifGn;
      string MRFlNVHNdH;
      string BhEPHadGej;
      string LunsiMbaTJ;
      string LmxddKSeVO;
      string qsnyPedqLn;
      string acAVbRcLDA;
      string sftUwOkakw;
      if(GCfFryzTiS == witiOuSDRq){HzkQsSGpdD = true;}
      else if(witiOuSDRq == GCfFryzTiS){eROdVZMhWT = true;}
      if(eCnbCyJyYe == cYRijyHRGR){ijOfhilaBM = true;}
      else if(cYRijyHRGR == eCnbCyJyYe){ZuMkohFzCZ = true;}
      if(yRNeMDytIY == NiHSOFifGn){gHbUUKzTCB = true;}
      else if(NiHSOFifGn == yRNeMDytIY){CxyRDQNDBe = true;}
      if(hfwYYnwiDi == MRFlNVHNdH){tDFPgaqjcJ = true;}
      else if(MRFlNVHNdH == hfwYYnwiDi){uTlQfaVDTy = true;}
      if(XXEwwCyxxQ == BhEPHadGej){KmhzRJRNlM = true;}
      else if(BhEPHadGej == XXEwwCyxxQ){XuKgHHNDFH = true;}
      if(UNsYRooAso == LunsiMbaTJ){bKZYOzXPwh = true;}
      else if(LunsiMbaTJ == UNsYRooAso){RACQjhTxaE = true;}
      if(AEKJkzGOCN == LmxddKSeVO){TmnbJfdzzH = true;}
      else if(LmxddKSeVO == AEKJkzGOCN){MIfrYFJwEN = true;}
      if(BZtpHZMQiJ == qsnyPedqLn){qBxqCtZbDK = true;}
      if(EBxrDTlWHj == acAVbRcLDA){skhoYjdgBg = true;}
      if(zwpOiSNtKw == sftUwOkakw){DantpWzFpl = true;}
      while(qsnyPedqLn == BZtpHZMQiJ){MBeEBGmQKw = true;}
      while(acAVbRcLDA == acAVbRcLDA){CKxtMtQVgx = true;}
      while(sftUwOkakw == sftUwOkakw){HYcOlOPSHB = true;}
      if(HzkQsSGpdD == true){HzkQsSGpdD = false;}
      if(ijOfhilaBM == true){ijOfhilaBM = false;}
      if(gHbUUKzTCB == true){gHbUUKzTCB = false;}
      if(tDFPgaqjcJ == true){tDFPgaqjcJ = false;}
      if(KmhzRJRNlM == true){KmhzRJRNlM = false;}
      if(bKZYOzXPwh == true){bKZYOzXPwh = false;}
      if(TmnbJfdzzH == true){TmnbJfdzzH = false;}
      if(qBxqCtZbDK == true){qBxqCtZbDK = false;}
      if(skhoYjdgBg == true){skhoYjdgBg = false;}
      if(DantpWzFpl == true){DantpWzFpl = false;}
      if(eROdVZMhWT == true){eROdVZMhWT = false;}
      if(ZuMkohFzCZ == true){ZuMkohFzCZ = false;}
      if(CxyRDQNDBe == true){CxyRDQNDBe = false;}
      if(uTlQfaVDTy == true){uTlQfaVDTy = false;}
      if(XuKgHHNDFH == true){XuKgHHNDFH = false;}
      if(RACQjhTxaE == true){RACQjhTxaE = false;}
      if(MIfrYFJwEN == true){MIfrYFJwEN = false;}
      if(MBeEBGmQKw == true){MBeEBGmQKw = false;}
      if(CKxtMtQVgx == true){CKxtMtQVgx = false;}
      if(HYcOlOPSHB == true){HYcOlOPSHB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNZMTHCPVL
{ 
  void fVIdOTUSMz()
  { 
      bool xaywaimfEe = false;
      bool jifLFYKNBm = false;
      bool psKZOjbhjs = false;
      bool nOPGLNzlbY = false;
      bool hsjeZAnlyg = false;
      bool tRORqEPXgq = false;
      bool GEwLpVSYAr = false;
      bool YYkbFwIfAO = false;
      bool upiCzWzyPG = false;
      bool xaEkRcxYnE = false;
      bool gPlGHVfmLt = false;
      bool wjXSwQVsLT = false;
      bool VTIstyTAKc = false;
      bool zirwgfDctc = false;
      bool pMmVKNDloA = false;
      bool GDMThNHrLJ = false;
      bool BfcitNrblQ = false;
      bool NszidJglig = false;
      bool uhLJVuVXOS = false;
      bool XLQjbJiEaw = false;
      string ghyYeiLYUU;
      string TNaGWaaEQG;
      string cgNzUQwkLQ;
      string BFGZJaUyuJ;
      string fXtTcboCGi;
      string hfHDIzUyEO;
      string lZNDSOHAww;
      string FbJGZFmsWs;
      string btebiVxDRK;
      string GWtgXGKpAO;
      string TnGKcFWAcD;
      string MabKlrukTx;
      string QEiloihciT;
      string twrHZnnTyd;
      string zwZNxftjte;
      string KZWDyOETVt;
      string WsRJIPhTky;
      string DalpyTeVnJ;
      string nyhDIUZoJK;
      string iTyEGFePFg;
      if(ghyYeiLYUU == TnGKcFWAcD){xaywaimfEe = true;}
      else if(TnGKcFWAcD == ghyYeiLYUU){gPlGHVfmLt = true;}
      if(TNaGWaaEQG == MabKlrukTx){jifLFYKNBm = true;}
      else if(MabKlrukTx == TNaGWaaEQG){wjXSwQVsLT = true;}
      if(cgNzUQwkLQ == QEiloihciT){psKZOjbhjs = true;}
      else if(QEiloihciT == cgNzUQwkLQ){VTIstyTAKc = true;}
      if(BFGZJaUyuJ == twrHZnnTyd){nOPGLNzlbY = true;}
      else if(twrHZnnTyd == BFGZJaUyuJ){zirwgfDctc = true;}
      if(fXtTcboCGi == zwZNxftjte){hsjeZAnlyg = true;}
      else if(zwZNxftjte == fXtTcboCGi){pMmVKNDloA = true;}
      if(hfHDIzUyEO == KZWDyOETVt){tRORqEPXgq = true;}
      else if(KZWDyOETVt == hfHDIzUyEO){GDMThNHrLJ = true;}
      if(lZNDSOHAww == WsRJIPhTky){GEwLpVSYAr = true;}
      else if(WsRJIPhTky == lZNDSOHAww){BfcitNrblQ = true;}
      if(FbJGZFmsWs == DalpyTeVnJ){YYkbFwIfAO = true;}
      if(btebiVxDRK == nyhDIUZoJK){upiCzWzyPG = true;}
      if(GWtgXGKpAO == iTyEGFePFg){xaEkRcxYnE = true;}
      while(DalpyTeVnJ == FbJGZFmsWs){NszidJglig = true;}
      while(nyhDIUZoJK == nyhDIUZoJK){uhLJVuVXOS = true;}
      while(iTyEGFePFg == iTyEGFePFg){XLQjbJiEaw = true;}
      if(xaywaimfEe == true){xaywaimfEe = false;}
      if(jifLFYKNBm == true){jifLFYKNBm = false;}
      if(psKZOjbhjs == true){psKZOjbhjs = false;}
      if(nOPGLNzlbY == true){nOPGLNzlbY = false;}
      if(hsjeZAnlyg == true){hsjeZAnlyg = false;}
      if(tRORqEPXgq == true){tRORqEPXgq = false;}
      if(GEwLpVSYAr == true){GEwLpVSYAr = false;}
      if(YYkbFwIfAO == true){YYkbFwIfAO = false;}
      if(upiCzWzyPG == true){upiCzWzyPG = false;}
      if(xaEkRcxYnE == true){xaEkRcxYnE = false;}
      if(gPlGHVfmLt == true){gPlGHVfmLt = false;}
      if(wjXSwQVsLT == true){wjXSwQVsLT = false;}
      if(VTIstyTAKc == true){VTIstyTAKc = false;}
      if(zirwgfDctc == true){zirwgfDctc = false;}
      if(pMmVKNDloA == true){pMmVKNDloA = false;}
      if(GDMThNHrLJ == true){GDMThNHrLJ = false;}
      if(BfcitNrblQ == true){BfcitNrblQ = false;}
      if(NszidJglig == true){NszidJglig = false;}
      if(uhLJVuVXOS == true){uhLJVuVXOS = false;}
      if(XLQjbJiEaw == true){XLQjbJiEaw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMZATQEOBW
{ 
  void HxpfyQteqR()
  { 
      bool GmsfyzEsOM = false;
      bool uFLTUVRkfb = false;
      bool uBQBPMDGBS = false;
      bool HdRkKsQWJc = false;
      bool ptzGxDpECe = false;
      bool hVxReEVrPl = false;
      bool wyqwFRnaJa = false;
      bool FubDlACKEM = false;
      bool WyEVjkfzFF = false;
      bool XYHXfrDCBe = false;
      bool POuaZmtsfe = false;
      bool CLmCOysULT = false;
      bool lnVDDfmEXs = false;
      bool xzJZxHDcwx = false;
      bool qlTaDLlEIg = false;
      bool yhqgsasqXs = false;
      bool zpVlgCCNFG = false;
      bool tQYOczTuAq = false;
      bool tiupuPIcfV = false;
      bool OLFDyBQhsA = false;
      string bFeXeTtdYY;
      string nUaHlkylmq;
      string dtZKlKKcxZ;
      string mHaeJOZRYM;
      string bQeHXqpqwR;
      string MoqaNgeTlU;
      string IQgykfsuyX;
      string KfMaOMOSmt;
      string UTgeNxQzRb;
      string jFfEDKjfVq;
      string xtsXGfcQMA;
      string RMgqzojBjm;
      string PtcVnFzHWD;
      string ciwuwZZIXh;
      string UAmRJWYoFO;
      string ahuhbDQXjB;
      string gUsIWiPkuY;
      string PacCSOHLLQ;
      string gKCIbumOTs;
      string ICXWBAHdta;
      if(bFeXeTtdYY == xtsXGfcQMA){GmsfyzEsOM = true;}
      else if(xtsXGfcQMA == bFeXeTtdYY){POuaZmtsfe = true;}
      if(nUaHlkylmq == RMgqzojBjm){uFLTUVRkfb = true;}
      else if(RMgqzojBjm == nUaHlkylmq){CLmCOysULT = true;}
      if(dtZKlKKcxZ == PtcVnFzHWD){uBQBPMDGBS = true;}
      else if(PtcVnFzHWD == dtZKlKKcxZ){lnVDDfmEXs = true;}
      if(mHaeJOZRYM == ciwuwZZIXh){HdRkKsQWJc = true;}
      else if(ciwuwZZIXh == mHaeJOZRYM){xzJZxHDcwx = true;}
      if(bQeHXqpqwR == UAmRJWYoFO){ptzGxDpECe = true;}
      else if(UAmRJWYoFO == bQeHXqpqwR){qlTaDLlEIg = true;}
      if(MoqaNgeTlU == ahuhbDQXjB){hVxReEVrPl = true;}
      else if(ahuhbDQXjB == MoqaNgeTlU){yhqgsasqXs = true;}
      if(IQgykfsuyX == gUsIWiPkuY){wyqwFRnaJa = true;}
      else if(gUsIWiPkuY == IQgykfsuyX){zpVlgCCNFG = true;}
      if(KfMaOMOSmt == PacCSOHLLQ){FubDlACKEM = true;}
      if(UTgeNxQzRb == gKCIbumOTs){WyEVjkfzFF = true;}
      if(jFfEDKjfVq == ICXWBAHdta){XYHXfrDCBe = true;}
      while(PacCSOHLLQ == KfMaOMOSmt){tQYOczTuAq = true;}
      while(gKCIbumOTs == gKCIbumOTs){tiupuPIcfV = true;}
      while(ICXWBAHdta == ICXWBAHdta){OLFDyBQhsA = true;}
      if(GmsfyzEsOM == true){GmsfyzEsOM = false;}
      if(uFLTUVRkfb == true){uFLTUVRkfb = false;}
      if(uBQBPMDGBS == true){uBQBPMDGBS = false;}
      if(HdRkKsQWJc == true){HdRkKsQWJc = false;}
      if(ptzGxDpECe == true){ptzGxDpECe = false;}
      if(hVxReEVrPl == true){hVxReEVrPl = false;}
      if(wyqwFRnaJa == true){wyqwFRnaJa = false;}
      if(FubDlACKEM == true){FubDlACKEM = false;}
      if(WyEVjkfzFF == true){WyEVjkfzFF = false;}
      if(XYHXfrDCBe == true){XYHXfrDCBe = false;}
      if(POuaZmtsfe == true){POuaZmtsfe = false;}
      if(CLmCOysULT == true){CLmCOysULT = false;}
      if(lnVDDfmEXs == true){lnVDDfmEXs = false;}
      if(xzJZxHDcwx == true){xzJZxHDcwx = false;}
      if(qlTaDLlEIg == true){qlTaDLlEIg = false;}
      if(yhqgsasqXs == true){yhqgsasqXs = false;}
      if(zpVlgCCNFG == true){zpVlgCCNFG = false;}
      if(tQYOczTuAq == true){tQYOczTuAq = false;}
      if(tiupuPIcfV == true){tiupuPIcfV = false;}
      if(OLFDyBQhsA == true){OLFDyBQhsA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKVVDQYZJD
{ 
  void uiCiphTAJl()
  { 
      bool CbPRsXffIR = false;
      bool coIStmpGLK = false;
      bool QWqToCXIIr = false;
      bool WBEsmtVNBb = false;
      bool uhWpYkQFrO = false;
      bool gCGomfkwcp = false;
      bool zXXQubkPeA = false;
      bool QbEjOizBtD = false;
      bool lSPsKUtOFG = false;
      bool JZkLbXJGtw = false;
      bool zAZqyFxVaE = false;
      bool fiBYDgHdFZ = false;
      bool gVJYqpqsIp = false;
      bool YsGyDksYuF = false;
      bool XXnBZZYLIu = false;
      bool PfAUPdqBAH = false;
      bool NDNjemcDUR = false;
      bool niiACJhHyQ = false;
      bool RejMasskhZ = false;
      bool trXmqTJDVm = false;
      string ZFHLxfQSAc;
      string JLMfQIukwd;
      string OLKGxHFAEt;
      string poEtgIfSGD;
      string NlgVKDClNo;
      string XMLuSNuANo;
      string ZPNGmUHSzI;
      string bbdsQbenut;
      string ESlPVcdJbS;
      string MfERcxYZio;
      string ujmFMuiRep;
      string iHETjHcxjJ;
      string qypguwWMPS;
      string DEEFyUegCZ;
      string tLdliFakgU;
      string TapYyxtGJQ;
      string YVCLleCyUP;
      string bwtJPfTExp;
      string VleuzbNfHB;
      string aYXlBXJSzE;
      if(ZFHLxfQSAc == ujmFMuiRep){CbPRsXffIR = true;}
      else if(ujmFMuiRep == ZFHLxfQSAc){zAZqyFxVaE = true;}
      if(JLMfQIukwd == iHETjHcxjJ){coIStmpGLK = true;}
      else if(iHETjHcxjJ == JLMfQIukwd){fiBYDgHdFZ = true;}
      if(OLKGxHFAEt == qypguwWMPS){QWqToCXIIr = true;}
      else if(qypguwWMPS == OLKGxHFAEt){gVJYqpqsIp = true;}
      if(poEtgIfSGD == DEEFyUegCZ){WBEsmtVNBb = true;}
      else if(DEEFyUegCZ == poEtgIfSGD){YsGyDksYuF = true;}
      if(NlgVKDClNo == tLdliFakgU){uhWpYkQFrO = true;}
      else if(tLdliFakgU == NlgVKDClNo){XXnBZZYLIu = true;}
      if(XMLuSNuANo == TapYyxtGJQ){gCGomfkwcp = true;}
      else if(TapYyxtGJQ == XMLuSNuANo){PfAUPdqBAH = true;}
      if(ZPNGmUHSzI == YVCLleCyUP){zXXQubkPeA = true;}
      else if(YVCLleCyUP == ZPNGmUHSzI){NDNjemcDUR = true;}
      if(bbdsQbenut == bwtJPfTExp){QbEjOizBtD = true;}
      if(ESlPVcdJbS == VleuzbNfHB){lSPsKUtOFG = true;}
      if(MfERcxYZio == aYXlBXJSzE){JZkLbXJGtw = true;}
      while(bwtJPfTExp == bbdsQbenut){niiACJhHyQ = true;}
      while(VleuzbNfHB == VleuzbNfHB){RejMasskhZ = true;}
      while(aYXlBXJSzE == aYXlBXJSzE){trXmqTJDVm = true;}
      if(CbPRsXffIR == true){CbPRsXffIR = false;}
      if(coIStmpGLK == true){coIStmpGLK = false;}
      if(QWqToCXIIr == true){QWqToCXIIr = false;}
      if(WBEsmtVNBb == true){WBEsmtVNBb = false;}
      if(uhWpYkQFrO == true){uhWpYkQFrO = false;}
      if(gCGomfkwcp == true){gCGomfkwcp = false;}
      if(zXXQubkPeA == true){zXXQubkPeA = false;}
      if(QbEjOizBtD == true){QbEjOizBtD = false;}
      if(lSPsKUtOFG == true){lSPsKUtOFG = false;}
      if(JZkLbXJGtw == true){JZkLbXJGtw = false;}
      if(zAZqyFxVaE == true){zAZqyFxVaE = false;}
      if(fiBYDgHdFZ == true){fiBYDgHdFZ = false;}
      if(gVJYqpqsIp == true){gVJYqpqsIp = false;}
      if(YsGyDksYuF == true){YsGyDksYuF = false;}
      if(XXnBZZYLIu == true){XXnBZZYLIu = false;}
      if(PfAUPdqBAH == true){PfAUPdqBAH = false;}
      if(NDNjemcDUR == true){NDNjemcDUR = false;}
      if(niiACJhHyQ == true){niiACJhHyQ = false;}
      if(RejMasskhZ == true){RejMasskhZ = false;}
      if(trXmqTJDVm == true){trXmqTJDVm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCOGSCBDIF
{ 
  void FrojdnLfVY()
  { 
      bool utLeVMqZTR = false;
      bool IOMPmANqtX = false;
      bool ysniBnKJui = false;
      bool fagwETqDBX = false;
      bool mVJBjsSfVr = false;
      bool OpGGLCFcdh = false;
      bool ChejkhgPKT = false;
      bool JJpWkbjlzH = false;
      bool UenCTpTajC = false;
      bool NOZSVFpYQC = false;
      bool LCUBiEzjUj = false;
      bool RSdVMWscQu = false;
      bool NGeIGujWBf = false;
      bool lLVxuSKmSP = false;
      bool pjFAjtjDGy = false;
      bool LNIVoFWMun = false;
      bool UbioxGxgZt = false;
      bool MGJAEcAeXL = false;
      bool KfQCTYCAIo = false;
      bool uxqetNBPDd = false;
      string rIbbWgDbnm;
      string OQHpMqFbki;
      string WeIZwefrWP;
      string NborVwOXXL;
      string usWmfWfAyt;
      string aWBXUMzCeq;
      string AKFYZlaOUP;
      string chDYncIVsZ;
      string zftbopZRXI;
      string wLrgKjnyNs;
      string uQfiRrScjq;
      string EdIFrUQcji;
      string MJqLSQoWNE;
      string oKHAdhAKJw;
      string XxgfESCmnp;
      string SKNegkZTPB;
      string DuOfCtWIaJ;
      string UFSnKOcKGA;
      string NChWkewcTr;
      string IfuIsbhBdK;
      if(rIbbWgDbnm == uQfiRrScjq){utLeVMqZTR = true;}
      else if(uQfiRrScjq == rIbbWgDbnm){LCUBiEzjUj = true;}
      if(OQHpMqFbki == EdIFrUQcji){IOMPmANqtX = true;}
      else if(EdIFrUQcji == OQHpMqFbki){RSdVMWscQu = true;}
      if(WeIZwefrWP == MJqLSQoWNE){ysniBnKJui = true;}
      else if(MJqLSQoWNE == WeIZwefrWP){NGeIGujWBf = true;}
      if(NborVwOXXL == oKHAdhAKJw){fagwETqDBX = true;}
      else if(oKHAdhAKJw == NborVwOXXL){lLVxuSKmSP = true;}
      if(usWmfWfAyt == XxgfESCmnp){mVJBjsSfVr = true;}
      else if(XxgfESCmnp == usWmfWfAyt){pjFAjtjDGy = true;}
      if(aWBXUMzCeq == SKNegkZTPB){OpGGLCFcdh = true;}
      else if(SKNegkZTPB == aWBXUMzCeq){LNIVoFWMun = true;}
      if(AKFYZlaOUP == DuOfCtWIaJ){ChejkhgPKT = true;}
      else if(DuOfCtWIaJ == AKFYZlaOUP){UbioxGxgZt = true;}
      if(chDYncIVsZ == UFSnKOcKGA){JJpWkbjlzH = true;}
      if(zftbopZRXI == NChWkewcTr){UenCTpTajC = true;}
      if(wLrgKjnyNs == IfuIsbhBdK){NOZSVFpYQC = true;}
      while(UFSnKOcKGA == chDYncIVsZ){MGJAEcAeXL = true;}
      while(NChWkewcTr == NChWkewcTr){KfQCTYCAIo = true;}
      while(IfuIsbhBdK == IfuIsbhBdK){uxqetNBPDd = true;}
      if(utLeVMqZTR == true){utLeVMqZTR = false;}
      if(IOMPmANqtX == true){IOMPmANqtX = false;}
      if(ysniBnKJui == true){ysniBnKJui = false;}
      if(fagwETqDBX == true){fagwETqDBX = false;}
      if(mVJBjsSfVr == true){mVJBjsSfVr = false;}
      if(OpGGLCFcdh == true){OpGGLCFcdh = false;}
      if(ChejkhgPKT == true){ChejkhgPKT = false;}
      if(JJpWkbjlzH == true){JJpWkbjlzH = false;}
      if(UenCTpTajC == true){UenCTpTajC = false;}
      if(NOZSVFpYQC == true){NOZSVFpYQC = false;}
      if(LCUBiEzjUj == true){LCUBiEzjUj = false;}
      if(RSdVMWscQu == true){RSdVMWscQu = false;}
      if(NGeIGujWBf == true){NGeIGujWBf = false;}
      if(lLVxuSKmSP == true){lLVxuSKmSP = false;}
      if(pjFAjtjDGy == true){pjFAjtjDGy = false;}
      if(LNIVoFWMun == true){LNIVoFWMun = false;}
      if(UbioxGxgZt == true){UbioxGxgZt = false;}
      if(MGJAEcAeXL == true){MGJAEcAeXL = false;}
      if(KfQCTYCAIo == true){KfQCTYCAIo = false;}
      if(uxqetNBPDd == true){uxqetNBPDd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAYQDKGJQA
{ 
  void hXuQTrTQud()
  { 
      bool hpfmZJuxZf = false;
      bool pqLedaMxAY = false;
      bool fzZfeJmkyb = false;
      bool JBzjFlsxwm = false;
      bool BYETTCsnlY = false;
      bool xaeDziPzIP = false;
      bool WKyxVnrbYq = false;
      bool hPANXHuFMc = false;
      bool QzyZeiWujW = false;
      bool VsogPpZGye = false;
      bool JQOuphZRer = false;
      bool mKmezWMXSl = false;
      bool RwrBUnZTxg = false;
      bool hnHgSzjDix = false;
      bool IFQrjLGKgs = false;
      bool dBnLNNYNZB = false;
      bool HGUyJzCFMA = false;
      bool mIoUdMfARJ = false;
      bool hPlDCfAuTE = false;
      bool aWcgpCjRhj = false;
      string ciZcanOJZr;
      string sKceujVgkc;
      string ezJlpjiOOf;
      string sxPpeJpfmo;
      string IPnIjaeaHr;
      string joZdcdYnlp;
      string EzttzwtmAl;
      string totuUOKBBO;
      string FIHVuDWkMB;
      string jCtxkIUtIn;
      string graUyuueJO;
      string SWmXkwrYyu;
      string ZIZyBruxKM;
      string sQrNhMglWA;
      string IrbyhMPVLn;
      string PwuNNXSbTG;
      string AyTwVBeYpY;
      string OGBymhgbPn;
      string bYkVwwVezJ;
      string sFSQzKXebf;
      if(ciZcanOJZr == graUyuueJO){hpfmZJuxZf = true;}
      else if(graUyuueJO == ciZcanOJZr){JQOuphZRer = true;}
      if(sKceujVgkc == SWmXkwrYyu){pqLedaMxAY = true;}
      else if(SWmXkwrYyu == sKceujVgkc){mKmezWMXSl = true;}
      if(ezJlpjiOOf == ZIZyBruxKM){fzZfeJmkyb = true;}
      else if(ZIZyBruxKM == ezJlpjiOOf){RwrBUnZTxg = true;}
      if(sxPpeJpfmo == sQrNhMglWA){JBzjFlsxwm = true;}
      else if(sQrNhMglWA == sxPpeJpfmo){hnHgSzjDix = true;}
      if(IPnIjaeaHr == IrbyhMPVLn){BYETTCsnlY = true;}
      else if(IrbyhMPVLn == IPnIjaeaHr){IFQrjLGKgs = true;}
      if(joZdcdYnlp == PwuNNXSbTG){xaeDziPzIP = true;}
      else if(PwuNNXSbTG == joZdcdYnlp){dBnLNNYNZB = true;}
      if(EzttzwtmAl == AyTwVBeYpY){WKyxVnrbYq = true;}
      else if(AyTwVBeYpY == EzttzwtmAl){HGUyJzCFMA = true;}
      if(totuUOKBBO == OGBymhgbPn){hPANXHuFMc = true;}
      if(FIHVuDWkMB == bYkVwwVezJ){QzyZeiWujW = true;}
      if(jCtxkIUtIn == sFSQzKXebf){VsogPpZGye = true;}
      while(OGBymhgbPn == totuUOKBBO){mIoUdMfARJ = true;}
      while(bYkVwwVezJ == bYkVwwVezJ){hPlDCfAuTE = true;}
      while(sFSQzKXebf == sFSQzKXebf){aWcgpCjRhj = true;}
      if(hpfmZJuxZf == true){hpfmZJuxZf = false;}
      if(pqLedaMxAY == true){pqLedaMxAY = false;}
      if(fzZfeJmkyb == true){fzZfeJmkyb = false;}
      if(JBzjFlsxwm == true){JBzjFlsxwm = false;}
      if(BYETTCsnlY == true){BYETTCsnlY = false;}
      if(xaeDziPzIP == true){xaeDziPzIP = false;}
      if(WKyxVnrbYq == true){WKyxVnrbYq = false;}
      if(hPANXHuFMc == true){hPANXHuFMc = false;}
      if(QzyZeiWujW == true){QzyZeiWujW = false;}
      if(VsogPpZGye == true){VsogPpZGye = false;}
      if(JQOuphZRer == true){JQOuphZRer = false;}
      if(mKmezWMXSl == true){mKmezWMXSl = false;}
      if(RwrBUnZTxg == true){RwrBUnZTxg = false;}
      if(hnHgSzjDix == true){hnHgSzjDix = false;}
      if(IFQrjLGKgs == true){IFQrjLGKgs = false;}
      if(dBnLNNYNZB == true){dBnLNNYNZB = false;}
      if(HGUyJzCFMA == true){HGUyJzCFMA = false;}
      if(mIoUdMfARJ == true){mIoUdMfARJ = false;}
      if(hPlDCfAuTE == true){hPlDCfAuTE = false;}
      if(aWcgpCjRhj == true){aWcgpCjRhj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AAPCOQKCWA
{ 
  void KaGegCWrtF()
  { 
      bool jpkzPSPXzw = false;
      bool waleNwcITT = false;
      bool LwdorVLTwQ = false;
      bool ZmfEZGmNYM = false;
      bool VxlUfjunQY = false;
      bool XFgHlmLwGs = false;
      bool GwbiVItgFG = false;
      bool JOjHyNKJII = false;
      bool aXCWrTGXRl = false;
      bool tpHeFZVCyW = false;
      bool oNiJPIVZJY = false;
      bool cCmxSisEpB = false;
      bool CWPSLSHFBX = false;
      bool rHKlSMorHi = false;
      bool ygNsJrDJLW = false;
      bool gQMxUSyPyw = false;
      bool BPXlgUrBeG = false;
      bool sAwGDUIWJT = false;
      bool PyseqauNQA = false;
      bool OYtLhhJbMn = false;
      string EJcqjuhKlP;
      string rjQkokIeQS;
      string PBzrZTaTqr;
      string NZUocLTzPO;
      string BRrZEmBftK;
      string FTHsCDKkQP;
      string UOStBSObIc;
      string RJOBQxJZml;
      string StZgltRblZ;
      string BihzsmzxXk;
      string YYXQswEFbE;
      string sjxexZnlHH;
      string AmpiaiaOHd;
      string yLCBNsWInp;
      string pLzhfRlCCT;
      string yMpQkkiooK;
      string UoxyFhhuRD;
      string DfxRQnnICJ;
      string xXMnekVkQc;
      string KgTdVAOAby;
      if(EJcqjuhKlP == YYXQswEFbE){jpkzPSPXzw = true;}
      else if(YYXQswEFbE == EJcqjuhKlP){oNiJPIVZJY = true;}
      if(rjQkokIeQS == sjxexZnlHH){waleNwcITT = true;}
      else if(sjxexZnlHH == rjQkokIeQS){cCmxSisEpB = true;}
      if(PBzrZTaTqr == AmpiaiaOHd){LwdorVLTwQ = true;}
      else if(AmpiaiaOHd == PBzrZTaTqr){CWPSLSHFBX = true;}
      if(NZUocLTzPO == yLCBNsWInp){ZmfEZGmNYM = true;}
      else if(yLCBNsWInp == NZUocLTzPO){rHKlSMorHi = true;}
      if(BRrZEmBftK == pLzhfRlCCT){VxlUfjunQY = true;}
      else if(pLzhfRlCCT == BRrZEmBftK){ygNsJrDJLW = true;}
      if(FTHsCDKkQP == yMpQkkiooK){XFgHlmLwGs = true;}
      else if(yMpQkkiooK == FTHsCDKkQP){gQMxUSyPyw = true;}
      if(UOStBSObIc == UoxyFhhuRD){GwbiVItgFG = true;}
      else if(UoxyFhhuRD == UOStBSObIc){BPXlgUrBeG = true;}
      if(RJOBQxJZml == DfxRQnnICJ){JOjHyNKJII = true;}
      if(StZgltRblZ == xXMnekVkQc){aXCWrTGXRl = true;}
      if(BihzsmzxXk == KgTdVAOAby){tpHeFZVCyW = true;}
      while(DfxRQnnICJ == RJOBQxJZml){sAwGDUIWJT = true;}
      while(xXMnekVkQc == xXMnekVkQc){PyseqauNQA = true;}
      while(KgTdVAOAby == KgTdVAOAby){OYtLhhJbMn = true;}
      if(jpkzPSPXzw == true){jpkzPSPXzw = false;}
      if(waleNwcITT == true){waleNwcITT = false;}
      if(LwdorVLTwQ == true){LwdorVLTwQ = false;}
      if(ZmfEZGmNYM == true){ZmfEZGmNYM = false;}
      if(VxlUfjunQY == true){VxlUfjunQY = false;}
      if(XFgHlmLwGs == true){XFgHlmLwGs = false;}
      if(GwbiVItgFG == true){GwbiVItgFG = false;}
      if(JOjHyNKJII == true){JOjHyNKJII = false;}
      if(aXCWrTGXRl == true){aXCWrTGXRl = false;}
      if(tpHeFZVCyW == true){tpHeFZVCyW = false;}
      if(oNiJPIVZJY == true){oNiJPIVZJY = false;}
      if(cCmxSisEpB == true){cCmxSisEpB = false;}
      if(CWPSLSHFBX == true){CWPSLSHFBX = false;}
      if(rHKlSMorHi == true){rHKlSMorHi = false;}
      if(ygNsJrDJLW == true){ygNsJrDJLW = false;}
      if(gQMxUSyPyw == true){gQMxUSyPyw = false;}
      if(BPXlgUrBeG == true){BPXlgUrBeG = false;}
      if(sAwGDUIWJT == true){sAwGDUIWJT = false;}
      if(PyseqauNQA == true){PyseqauNQA = false;}
      if(OYtLhhJbMn == true){OYtLhhJbMn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHYQLFCOYH
{ 
  void FsmYmGyhCk()
  { 
      bool VJtAqajzft = false;
      bool XPrgsyIVEE = false;
      bool iTtDwpkInB = false;
      bool TeLbjkOOTV = false;
      bool UzkkhZeuqp = false;
      bool qspfmBOpDB = false;
      bool paKeZrEQwI = false;
      bool jtChijiJVW = false;
      bool KpRxJanenh = false;
      bool VYKRftnGKo = false;
      bool UNzhGwpHwC = false;
      bool SFUgqAJMUz = false;
      bool DYcNmLjjCo = false;
      bool wcyfBwqjqM = false;
      bool jghkPQDcaf = false;
      bool kakLkwkkuu = false;
      bool MGEHGoHoft = false;
      bool IYVIOWpqxV = false;
      bool HGIWEVrltE = false;
      bool KFnwzcbaea = false;
      string XVyinPOEGM;
      string ZfBblHcqZK;
      string iffAyuaWyN;
      string rxYRHfNARX;
      string ICyajanPGJ;
      string wwAoaroxjs;
      string orGsUbGiTF;
      string sbYBBfhFPX;
      string GLPnRuwjqP;
      string qQPYiQwFGI;
      string TEuBQTXzmu;
      string KjgMmdbRbY;
      string fWrDNcMARk;
      string jbyHDBPOXx;
      string XwwuFHiDkF;
      string nddgcxMqmm;
      string HXhBKhkZJk;
      string NMsdBiZwyG;
      string tIOLxFyQeF;
      string oXbjoAOukW;
      if(XVyinPOEGM == TEuBQTXzmu){VJtAqajzft = true;}
      else if(TEuBQTXzmu == XVyinPOEGM){UNzhGwpHwC = true;}
      if(ZfBblHcqZK == KjgMmdbRbY){XPrgsyIVEE = true;}
      else if(KjgMmdbRbY == ZfBblHcqZK){SFUgqAJMUz = true;}
      if(iffAyuaWyN == fWrDNcMARk){iTtDwpkInB = true;}
      else if(fWrDNcMARk == iffAyuaWyN){DYcNmLjjCo = true;}
      if(rxYRHfNARX == jbyHDBPOXx){TeLbjkOOTV = true;}
      else if(jbyHDBPOXx == rxYRHfNARX){wcyfBwqjqM = true;}
      if(ICyajanPGJ == XwwuFHiDkF){UzkkhZeuqp = true;}
      else if(XwwuFHiDkF == ICyajanPGJ){jghkPQDcaf = true;}
      if(wwAoaroxjs == nddgcxMqmm){qspfmBOpDB = true;}
      else if(nddgcxMqmm == wwAoaroxjs){kakLkwkkuu = true;}
      if(orGsUbGiTF == HXhBKhkZJk){paKeZrEQwI = true;}
      else if(HXhBKhkZJk == orGsUbGiTF){MGEHGoHoft = true;}
      if(sbYBBfhFPX == NMsdBiZwyG){jtChijiJVW = true;}
      if(GLPnRuwjqP == tIOLxFyQeF){KpRxJanenh = true;}
      if(qQPYiQwFGI == oXbjoAOukW){VYKRftnGKo = true;}
      while(NMsdBiZwyG == sbYBBfhFPX){IYVIOWpqxV = true;}
      while(tIOLxFyQeF == tIOLxFyQeF){HGIWEVrltE = true;}
      while(oXbjoAOukW == oXbjoAOukW){KFnwzcbaea = true;}
      if(VJtAqajzft == true){VJtAqajzft = false;}
      if(XPrgsyIVEE == true){XPrgsyIVEE = false;}
      if(iTtDwpkInB == true){iTtDwpkInB = false;}
      if(TeLbjkOOTV == true){TeLbjkOOTV = false;}
      if(UzkkhZeuqp == true){UzkkhZeuqp = false;}
      if(qspfmBOpDB == true){qspfmBOpDB = false;}
      if(paKeZrEQwI == true){paKeZrEQwI = false;}
      if(jtChijiJVW == true){jtChijiJVW = false;}
      if(KpRxJanenh == true){KpRxJanenh = false;}
      if(VYKRftnGKo == true){VYKRftnGKo = false;}
      if(UNzhGwpHwC == true){UNzhGwpHwC = false;}
      if(SFUgqAJMUz == true){SFUgqAJMUz = false;}
      if(DYcNmLjjCo == true){DYcNmLjjCo = false;}
      if(wcyfBwqjqM == true){wcyfBwqjqM = false;}
      if(jghkPQDcaf == true){jghkPQDcaf = false;}
      if(kakLkwkkuu == true){kakLkwkkuu = false;}
      if(MGEHGoHoft == true){MGEHGoHoft = false;}
      if(IYVIOWpqxV == true){IYVIOWpqxV = false;}
      if(HGIWEVrltE == true){HGIWEVrltE = false;}
      if(KFnwzcbaea == true){KFnwzcbaea = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGYVZIFPSU
{ 
  void OzqFDyjmul()
  { 
      bool YEndTsQWIQ = false;
      bool ndnNpBqaaE = false;
      bool BsyYERtVRn = false;
      bool ClGFIEoocU = false;
      bool JmonoODDOt = false;
      bool rrDYIfFOYC = false;
      bool ytETNBWiFl = false;
      bool MCyGtODKjp = false;
      bool NpGXuKigxb = false;
      bool yZPaVPiVZm = false;
      bool qUychpswdt = false;
      bool bueinHmgXD = false;
      bool SpkcmllXke = false;
      bool ehjwysrdoF = false;
      bool QmCCzDuglN = false;
      bool bCxWTBiUou = false;
      bool EVKzOtKhjt = false;
      bool PJqSlfmicj = false;
      bool qFkXDcjNcw = false;
      bool KXntBtbDnF = false;
      string xqfeayGEgq;
      string ymmfPHbRpA;
      string QPssWMBdDQ;
      string awbqMhnhsf;
      string FZrPCzBLYh;
      string qcHBmgylHO;
      string wcBPQCKuSg;
      string SsYJupXcqX;
      string LpEUZyoZEf;
      string jCZejcYbzA;
      string oFrrPxExGw;
      string IUtjDGXgpS;
      string MjqmxQStZR;
      string RwdqhFxMEb;
      string sqSHWPHpac;
      string ErkgmENFuz;
      string eJXodMpDCx;
      string JLbOYVQjQg;
      string IcSwNZKxEc;
      string rrQFwjSdcK;
      if(xqfeayGEgq == oFrrPxExGw){YEndTsQWIQ = true;}
      else if(oFrrPxExGw == xqfeayGEgq){qUychpswdt = true;}
      if(ymmfPHbRpA == IUtjDGXgpS){ndnNpBqaaE = true;}
      else if(IUtjDGXgpS == ymmfPHbRpA){bueinHmgXD = true;}
      if(QPssWMBdDQ == MjqmxQStZR){BsyYERtVRn = true;}
      else if(MjqmxQStZR == QPssWMBdDQ){SpkcmllXke = true;}
      if(awbqMhnhsf == RwdqhFxMEb){ClGFIEoocU = true;}
      else if(RwdqhFxMEb == awbqMhnhsf){ehjwysrdoF = true;}
      if(FZrPCzBLYh == sqSHWPHpac){JmonoODDOt = true;}
      else if(sqSHWPHpac == FZrPCzBLYh){QmCCzDuglN = true;}
      if(qcHBmgylHO == ErkgmENFuz){rrDYIfFOYC = true;}
      else if(ErkgmENFuz == qcHBmgylHO){bCxWTBiUou = true;}
      if(wcBPQCKuSg == eJXodMpDCx){ytETNBWiFl = true;}
      else if(eJXodMpDCx == wcBPQCKuSg){EVKzOtKhjt = true;}
      if(SsYJupXcqX == JLbOYVQjQg){MCyGtODKjp = true;}
      if(LpEUZyoZEf == IcSwNZKxEc){NpGXuKigxb = true;}
      if(jCZejcYbzA == rrQFwjSdcK){yZPaVPiVZm = true;}
      while(JLbOYVQjQg == SsYJupXcqX){PJqSlfmicj = true;}
      while(IcSwNZKxEc == IcSwNZKxEc){qFkXDcjNcw = true;}
      while(rrQFwjSdcK == rrQFwjSdcK){KXntBtbDnF = true;}
      if(YEndTsQWIQ == true){YEndTsQWIQ = false;}
      if(ndnNpBqaaE == true){ndnNpBqaaE = false;}
      if(BsyYERtVRn == true){BsyYERtVRn = false;}
      if(ClGFIEoocU == true){ClGFIEoocU = false;}
      if(JmonoODDOt == true){JmonoODDOt = false;}
      if(rrDYIfFOYC == true){rrDYIfFOYC = false;}
      if(ytETNBWiFl == true){ytETNBWiFl = false;}
      if(MCyGtODKjp == true){MCyGtODKjp = false;}
      if(NpGXuKigxb == true){NpGXuKigxb = false;}
      if(yZPaVPiVZm == true){yZPaVPiVZm = false;}
      if(qUychpswdt == true){qUychpswdt = false;}
      if(bueinHmgXD == true){bueinHmgXD = false;}
      if(SpkcmllXke == true){SpkcmllXke = false;}
      if(ehjwysrdoF == true){ehjwysrdoF = false;}
      if(QmCCzDuglN == true){QmCCzDuglN = false;}
      if(bCxWTBiUou == true){bCxWTBiUou = false;}
      if(EVKzOtKhjt == true){EVKzOtKhjt = false;}
      if(PJqSlfmicj == true){PJqSlfmicj = false;}
      if(qFkXDcjNcw == true){qFkXDcjNcw = false;}
      if(KXntBtbDnF == true){KXntBtbDnF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HGSNJWJMUT
{ 
  void IHAcLhRVmB()
  { 
      bool DnYHxPPlxy = false;
      bool bFWYiVMdeX = false;
      bool aQATkOwdKU = false;
      bool aljaiFuCfr = false;
      bool BCglEUylqD = false;
      bool ZnXHNmnEVi = false;
      bool SkabXpUupd = false;
      bool ZJymWYiNPQ = false;
      bool QJmHulNcMw = false;
      bool QqfwYPaFON = false;
      bool ACwMcPpjjo = false;
      bool DaoFSJySfk = false;
      bool britNidBOH = false;
      bool xdzBQNNZef = false;
      bool wdrXrpBZdP = false;
      bool RHYckHSCzs = false;
      bool loVcqYanoE = false;
      bool wXnAnyzLBW = false;
      bool hDWzopFWPI = false;
      bool uKaltHIPfT = false;
      string JfwhnlcNGl;
      string ABSmXirhTm;
      string GCxAkibcCF;
      string MrLmlKfXej;
      string DpVtQniKJA;
      string FDBCrGhuxF;
      string KzLAYIoeBN;
      string DUCjiQfDjx;
      string zRTBAIpJue;
      string cjZYZDeVUI;
      string yEJwxkARSa;
      string ZdLAGrfJzP;
      string RfjVkStcKf;
      string lKiaztIWEP;
      string IYpTFyYZSg;
      string XUVEqRUmLd;
      string pWGmoPujBL;
      string jIFjHroPQl;
      string tUKcHQndjg;
      string ZULaYlRDeo;
      if(JfwhnlcNGl == yEJwxkARSa){DnYHxPPlxy = true;}
      else if(yEJwxkARSa == JfwhnlcNGl){ACwMcPpjjo = true;}
      if(ABSmXirhTm == ZdLAGrfJzP){bFWYiVMdeX = true;}
      else if(ZdLAGrfJzP == ABSmXirhTm){DaoFSJySfk = true;}
      if(GCxAkibcCF == RfjVkStcKf){aQATkOwdKU = true;}
      else if(RfjVkStcKf == GCxAkibcCF){britNidBOH = true;}
      if(MrLmlKfXej == lKiaztIWEP){aljaiFuCfr = true;}
      else if(lKiaztIWEP == MrLmlKfXej){xdzBQNNZef = true;}
      if(DpVtQniKJA == IYpTFyYZSg){BCglEUylqD = true;}
      else if(IYpTFyYZSg == DpVtQniKJA){wdrXrpBZdP = true;}
      if(FDBCrGhuxF == XUVEqRUmLd){ZnXHNmnEVi = true;}
      else if(XUVEqRUmLd == FDBCrGhuxF){RHYckHSCzs = true;}
      if(KzLAYIoeBN == pWGmoPujBL){SkabXpUupd = true;}
      else if(pWGmoPujBL == KzLAYIoeBN){loVcqYanoE = true;}
      if(DUCjiQfDjx == jIFjHroPQl){ZJymWYiNPQ = true;}
      if(zRTBAIpJue == tUKcHQndjg){QJmHulNcMw = true;}
      if(cjZYZDeVUI == ZULaYlRDeo){QqfwYPaFON = true;}
      while(jIFjHroPQl == DUCjiQfDjx){wXnAnyzLBW = true;}
      while(tUKcHQndjg == tUKcHQndjg){hDWzopFWPI = true;}
      while(ZULaYlRDeo == ZULaYlRDeo){uKaltHIPfT = true;}
      if(DnYHxPPlxy == true){DnYHxPPlxy = false;}
      if(bFWYiVMdeX == true){bFWYiVMdeX = false;}
      if(aQATkOwdKU == true){aQATkOwdKU = false;}
      if(aljaiFuCfr == true){aljaiFuCfr = false;}
      if(BCglEUylqD == true){BCglEUylqD = false;}
      if(ZnXHNmnEVi == true){ZnXHNmnEVi = false;}
      if(SkabXpUupd == true){SkabXpUupd = false;}
      if(ZJymWYiNPQ == true){ZJymWYiNPQ = false;}
      if(QJmHulNcMw == true){QJmHulNcMw = false;}
      if(QqfwYPaFON == true){QqfwYPaFON = false;}
      if(ACwMcPpjjo == true){ACwMcPpjjo = false;}
      if(DaoFSJySfk == true){DaoFSJySfk = false;}
      if(britNidBOH == true){britNidBOH = false;}
      if(xdzBQNNZef == true){xdzBQNNZef = false;}
      if(wdrXrpBZdP == true){wdrXrpBZdP = false;}
      if(RHYckHSCzs == true){RHYckHSCzs = false;}
      if(loVcqYanoE == true){loVcqYanoE = false;}
      if(wXnAnyzLBW == true){wXnAnyzLBW = false;}
      if(hDWzopFWPI == true){hDWzopFWPI = false;}
      if(uKaltHIPfT == true){uKaltHIPfT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVHPZVPRIJ
{ 
  void BYRdTXboUy()
  { 
      bool kzuedDJgno = false;
      bool oyDgFQIyOp = false;
      bool aLsWmluxlM = false;
      bool OrQZwbwWKl = false;
      bool AbygkTyVyy = false;
      bool OrUpCZFYqr = false;
      bool IMtbZxgdkd = false;
      bool TknbpyNLkS = false;
      bool nYznxWWaWW = false;
      bool VWeSdmhWGn = false;
      bool mTkTddErAE = false;
      bool LtnYDjNFdD = false;
      bool ZGGOIwGVyC = false;
      bool QqExfTneJT = false;
      bool SeaSKaiGOt = false;
      bool ZbrDOgMVLg = false;
      bool XhsxmUoqrj = false;
      bool uhwJktenDg = false;
      bool NzGEcoyBiz = false;
      bool GRTbwjkceo = false;
      string aNYXPeEITS;
      string uDdWYTKIGr;
      string GyxpLDFpQd;
      string TkysRLfsQm;
      string gnyqpmMarJ;
      string LnNJobQhML;
      string ZNrpyJFjFM;
      string mRqTLRzFzY;
      string qdyGRfXnEo;
      string uxfFNSwHsg;
      string hbVfVtxsyW;
      string bLinUuPkYS;
      string kQfPRoklGs;
      string VrMSqOHRjX;
      string heohMjOrjR;
      string CKiZuQwGOf;
      string IKmFBjyPwF;
      string myABkGbyCg;
      string arBnpKJmWZ;
      string SBDDOXqjgc;
      if(aNYXPeEITS == hbVfVtxsyW){kzuedDJgno = true;}
      else if(hbVfVtxsyW == aNYXPeEITS){mTkTddErAE = true;}
      if(uDdWYTKIGr == bLinUuPkYS){oyDgFQIyOp = true;}
      else if(bLinUuPkYS == uDdWYTKIGr){LtnYDjNFdD = true;}
      if(GyxpLDFpQd == kQfPRoklGs){aLsWmluxlM = true;}
      else if(kQfPRoklGs == GyxpLDFpQd){ZGGOIwGVyC = true;}
      if(TkysRLfsQm == VrMSqOHRjX){OrQZwbwWKl = true;}
      else if(VrMSqOHRjX == TkysRLfsQm){QqExfTneJT = true;}
      if(gnyqpmMarJ == heohMjOrjR){AbygkTyVyy = true;}
      else if(heohMjOrjR == gnyqpmMarJ){SeaSKaiGOt = true;}
      if(LnNJobQhML == CKiZuQwGOf){OrUpCZFYqr = true;}
      else if(CKiZuQwGOf == LnNJobQhML){ZbrDOgMVLg = true;}
      if(ZNrpyJFjFM == IKmFBjyPwF){IMtbZxgdkd = true;}
      else if(IKmFBjyPwF == ZNrpyJFjFM){XhsxmUoqrj = true;}
      if(mRqTLRzFzY == myABkGbyCg){TknbpyNLkS = true;}
      if(qdyGRfXnEo == arBnpKJmWZ){nYznxWWaWW = true;}
      if(uxfFNSwHsg == SBDDOXqjgc){VWeSdmhWGn = true;}
      while(myABkGbyCg == mRqTLRzFzY){uhwJktenDg = true;}
      while(arBnpKJmWZ == arBnpKJmWZ){NzGEcoyBiz = true;}
      while(SBDDOXqjgc == SBDDOXqjgc){GRTbwjkceo = true;}
      if(kzuedDJgno == true){kzuedDJgno = false;}
      if(oyDgFQIyOp == true){oyDgFQIyOp = false;}
      if(aLsWmluxlM == true){aLsWmluxlM = false;}
      if(OrQZwbwWKl == true){OrQZwbwWKl = false;}
      if(AbygkTyVyy == true){AbygkTyVyy = false;}
      if(OrUpCZFYqr == true){OrUpCZFYqr = false;}
      if(IMtbZxgdkd == true){IMtbZxgdkd = false;}
      if(TknbpyNLkS == true){TknbpyNLkS = false;}
      if(nYznxWWaWW == true){nYznxWWaWW = false;}
      if(VWeSdmhWGn == true){VWeSdmhWGn = false;}
      if(mTkTddErAE == true){mTkTddErAE = false;}
      if(LtnYDjNFdD == true){LtnYDjNFdD = false;}
      if(ZGGOIwGVyC == true){ZGGOIwGVyC = false;}
      if(QqExfTneJT == true){QqExfTneJT = false;}
      if(SeaSKaiGOt == true){SeaSKaiGOt = false;}
      if(ZbrDOgMVLg == true){ZbrDOgMVLg = false;}
      if(XhsxmUoqrj == true){XhsxmUoqrj = false;}
      if(uhwJktenDg == true){uhwJktenDg = false;}
      if(NzGEcoyBiz == true){NzGEcoyBiz = false;}
      if(GRTbwjkceo == true){GRTbwjkceo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VIAVWHQPHC
{ 
  void gFZsmYYIhh()
  { 
      bool drPrcDYIiz = false;
      bool FCRznQVaKh = false;
      bool zSwzVptRWs = false;
      bool XcUyYpiufe = false;
      bool ganGzfRqKu = false;
      bool LtsQsKwPWl = false;
      bool JHlpacgSax = false;
      bool haueBXeozo = false;
      bool XCGagdjEFN = false;
      bool tSYsVYoyeW = false;
      bool yyQNNkzNOU = false;
      bool fGPgOHBKIx = false;
      bool scNMDOBCJb = false;
      bool ifJcpZksNw = false;
      bool eVojhmCqeO = false;
      bool WdphcVjEJy = false;
      bool iwEmlAwmpn = false;
      bool VIxLSWndeQ = false;
      bool LKXuEEpbAU = false;
      bool ogiONhRCxh = false;
      string EfYFVNWuub;
      string bGDzBHwhzN;
      string EIthFhSToY;
      string VcSbmfkOsQ;
      string WgaiqBCsxU;
      string PjcHGukqzn;
      string tCFVFznaMU;
      string WgohqWhLpE;
      string eZWTJlALVq;
      string utOEWTaEcr;
      string NafbyhttPi;
      string NZAuITflLS;
      string zbFVYbRjKW;
      string uchypEttUb;
      string rFwlcVtTwC;
      string norKskVKDV;
      string PJirnjqBEE;
      string ZkQjasfSrD;
      string hynIhFjXFF;
      string ijqyMhVDys;
      if(EfYFVNWuub == NafbyhttPi){drPrcDYIiz = true;}
      else if(NafbyhttPi == EfYFVNWuub){yyQNNkzNOU = true;}
      if(bGDzBHwhzN == NZAuITflLS){FCRznQVaKh = true;}
      else if(NZAuITflLS == bGDzBHwhzN){fGPgOHBKIx = true;}
      if(EIthFhSToY == zbFVYbRjKW){zSwzVptRWs = true;}
      else if(zbFVYbRjKW == EIthFhSToY){scNMDOBCJb = true;}
      if(VcSbmfkOsQ == uchypEttUb){XcUyYpiufe = true;}
      else if(uchypEttUb == VcSbmfkOsQ){ifJcpZksNw = true;}
      if(WgaiqBCsxU == rFwlcVtTwC){ganGzfRqKu = true;}
      else if(rFwlcVtTwC == WgaiqBCsxU){eVojhmCqeO = true;}
      if(PjcHGukqzn == norKskVKDV){LtsQsKwPWl = true;}
      else if(norKskVKDV == PjcHGukqzn){WdphcVjEJy = true;}
      if(tCFVFznaMU == PJirnjqBEE){JHlpacgSax = true;}
      else if(PJirnjqBEE == tCFVFznaMU){iwEmlAwmpn = true;}
      if(WgohqWhLpE == ZkQjasfSrD){haueBXeozo = true;}
      if(eZWTJlALVq == hynIhFjXFF){XCGagdjEFN = true;}
      if(utOEWTaEcr == ijqyMhVDys){tSYsVYoyeW = true;}
      while(ZkQjasfSrD == WgohqWhLpE){VIxLSWndeQ = true;}
      while(hynIhFjXFF == hynIhFjXFF){LKXuEEpbAU = true;}
      while(ijqyMhVDys == ijqyMhVDys){ogiONhRCxh = true;}
      if(drPrcDYIiz == true){drPrcDYIiz = false;}
      if(FCRznQVaKh == true){FCRznQVaKh = false;}
      if(zSwzVptRWs == true){zSwzVptRWs = false;}
      if(XcUyYpiufe == true){XcUyYpiufe = false;}
      if(ganGzfRqKu == true){ganGzfRqKu = false;}
      if(LtsQsKwPWl == true){LtsQsKwPWl = false;}
      if(JHlpacgSax == true){JHlpacgSax = false;}
      if(haueBXeozo == true){haueBXeozo = false;}
      if(XCGagdjEFN == true){XCGagdjEFN = false;}
      if(tSYsVYoyeW == true){tSYsVYoyeW = false;}
      if(yyQNNkzNOU == true){yyQNNkzNOU = false;}
      if(fGPgOHBKIx == true){fGPgOHBKIx = false;}
      if(scNMDOBCJb == true){scNMDOBCJb = false;}
      if(ifJcpZksNw == true){ifJcpZksNw = false;}
      if(eVojhmCqeO == true){eVojhmCqeO = false;}
      if(WdphcVjEJy == true){WdphcVjEJy = false;}
      if(iwEmlAwmpn == true){iwEmlAwmpn = false;}
      if(VIxLSWndeQ == true){VIxLSWndeQ = false;}
      if(LKXuEEpbAU == true){LKXuEEpbAU = false;}
      if(ogiONhRCxh == true){ogiONhRCxh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNXRWFPAGS
{ 
  void NgBwQsqLSe()
  { 
      bool KWEPQizYiM = false;
      bool pSnlPonTAr = false;
      bool drbFYiyPXi = false;
      bool brzuXBGReG = false;
      bool CcEzAJXEkm = false;
      bool HlXtNRuyqg = false;
      bool kjAzkxSrON = false;
      bool iVntpAncFO = false;
      bool KtdkboTEhF = false;
      bool GHaxVRcFNC = false;
      bool pfoXDlxdEM = false;
      bool dSrcWpGPWw = false;
      bool dOJIHauqYX = false;
      bool XiODYeEGgp = false;
      bool qpAUbnPyae = false;
      bool KMhRXbVgPb = false;
      bool pGEfouDoDq = false;
      bool kAigEmOnfT = false;
      bool LxPsNKAxex = false;
      bool JWpEzjkTeg = false;
      string lwsLwAFsXp;
      string DONCPxjuwU;
      string ZADscCuzaF;
      string HKNwPRGcux;
      string fmVroprXrO;
      string RVTsBkszht;
      string EGRRhrBQmy;
      string pGAynmeKDm;
      string JWGMnlpUud;
      string YGuBrZUDJx;
      string oajtXLUUEN;
      string GhutjgAEdw;
      string CgUJZjKzGO;
      string SaBGyimLoc;
      string QUPhWqLAQK;
      string YPYNtHFaUn;
      string AVOptefnwB;
      string toPAegRmmi;
      string YKhuoCBmMp;
      string cLpAcuFYmq;
      if(lwsLwAFsXp == oajtXLUUEN){KWEPQizYiM = true;}
      else if(oajtXLUUEN == lwsLwAFsXp){pfoXDlxdEM = true;}
      if(DONCPxjuwU == GhutjgAEdw){pSnlPonTAr = true;}
      else if(GhutjgAEdw == DONCPxjuwU){dSrcWpGPWw = true;}
      if(ZADscCuzaF == CgUJZjKzGO){drbFYiyPXi = true;}
      else if(CgUJZjKzGO == ZADscCuzaF){dOJIHauqYX = true;}
      if(HKNwPRGcux == SaBGyimLoc){brzuXBGReG = true;}
      else if(SaBGyimLoc == HKNwPRGcux){XiODYeEGgp = true;}
      if(fmVroprXrO == QUPhWqLAQK){CcEzAJXEkm = true;}
      else if(QUPhWqLAQK == fmVroprXrO){qpAUbnPyae = true;}
      if(RVTsBkszht == YPYNtHFaUn){HlXtNRuyqg = true;}
      else if(YPYNtHFaUn == RVTsBkszht){KMhRXbVgPb = true;}
      if(EGRRhrBQmy == AVOptefnwB){kjAzkxSrON = true;}
      else if(AVOptefnwB == EGRRhrBQmy){pGEfouDoDq = true;}
      if(pGAynmeKDm == toPAegRmmi){iVntpAncFO = true;}
      if(JWGMnlpUud == YKhuoCBmMp){KtdkboTEhF = true;}
      if(YGuBrZUDJx == cLpAcuFYmq){GHaxVRcFNC = true;}
      while(toPAegRmmi == pGAynmeKDm){kAigEmOnfT = true;}
      while(YKhuoCBmMp == YKhuoCBmMp){LxPsNKAxex = true;}
      while(cLpAcuFYmq == cLpAcuFYmq){JWpEzjkTeg = true;}
      if(KWEPQizYiM == true){KWEPQizYiM = false;}
      if(pSnlPonTAr == true){pSnlPonTAr = false;}
      if(drbFYiyPXi == true){drbFYiyPXi = false;}
      if(brzuXBGReG == true){brzuXBGReG = false;}
      if(CcEzAJXEkm == true){CcEzAJXEkm = false;}
      if(HlXtNRuyqg == true){HlXtNRuyqg = false;}
      if(kjAzkxSrON == true){kjAzkxSrON = false;}
      if(iVntpAncFO == true){iVntpAncFO = false;}
      if(KtdkboTEhF == true){KtdkboTEhF = false;}
      if(GHaxVRcFNC == true){GHaxVRcFNC = false;}
      if(pfoXDlxdEM == true){pfoXDlxdEM = false;}
      if(dSrcWpGPWw == true){dSrcWpGPWw = false;}
      if(dOJIHauqYX == true){dOJIHauqYX = false;}
      if(XiODYeEGgp == true){XiODYeEGgp = false;}
      if(qpAUbnPyae == true){qpAUbnPyae = false;}
      if(KMhRXbVgPb == true){KMhRXbVgPb = false;}
      if(pGEfouDoDq == true){pGEfouDoDq = false;}
      if(kAigEmOnfT == true){kAigEmOnfT = false;}
      if(LxPsNKAxex == true){LxPsNKAxex = false;}
      if(JWpEzjkTeg == true){JWpEzjkTeg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHPUVLSFZD
{ 
  void eVRlqQBMDz()
  { 
      bool ysAVBsmwWn = false;
      bool jhRinypVPb = false;
      bool NJZGeQODll = false;
      bool EiDUPVLwmQ = false;
      bool QOLqJCWmRz = false;
      bool zjAoEnTsqk = false;
      bool djJkiAdwTR = false;
      bool mthyKzyhxb = false;
      bool tblmlUiOPa = false;
      bool CREClgEaII = false;
      bool YZSzMFBBdF = false;
      bool pkwOpCyWyN = false;
      bool ROgsPVofMd = false;
      bool tWZoDTIlZg = false;
      bool ThkJjQVpLj = false;
      bool hhbtqJsZjq = false;
      bool PUozLSLHLW = false;
      bool sLwQtidWIy = false;
      bool AzTbuLuexs = false;
      bool aiBiQyskyR = false;
      string GTWBtTSlcL;
      string jseadREuej;
      string aXfiVgtsqA;
      string UhxepGVLCd;
      string JKETcUWSYO;
      string SGIpyimnfN;
      string YYucpCuAkW;
      string wssBZQSLFB;
      string KaUbhNZGfG;
      string SgfnEjPbca;
      string YWhBSYNHQh;
      string PbidCxEStc;
      string coTdEONEwp;
      string BqidcmrSJJ;
      string ARpypqyBkG;
      string ewgAyiDEwE;
      string KJLZgXrEAP;
      string EkIkcKzUmN;
      string PMSoKEKies;
      string jnVFypGPRS;
      if(GTWBtTSlcL == YWhBSYNHQh){ysAVBsmwWn = true;}
      else if(YWhBSYNHQh == GTWBtTSlcL){YZSzMFBBdF = true;}
      if(jseadREuej == PbidCxEStc){jhRinypVPb = true;}
      else if(PbidCxEStc == jseadREuej){pkwOpCyWyN = true;}
      if(aXfiVgtsqA == coTdEONEwp){NJZGeQODll = true;}
      else if(coTdEONEwp == aXfiVgtsqA){ROgsPVofMd = true;}
      if(UhxepGVLCd == BqidcmrSJJ){EiDUPVLwmQ = true;}
      else if(BqidcmrSJJ == UhxepGVLCd){tWZoDTIlZg = true;}
      if(JKETcUWSYO == ARpypqyBkG){QOLqJCWmRz = true;}
      else if(ARpypqyBkG == JKETcUWSYO){ThkJjQVpLj = true;}
      if(SGIpyimnfN == ewgAyiDEwE){zjAoEnTsqk = true;}
      else if(ewgAyiDEwE == SGIpyimnfN){hhbtqJsZjq = true;}
      if(YYucpCuAkW == KJLZgXrEAP){djJkiAdwTR = true;}
      else if(KJLZgXrEAP == YYucpCuAkW){PUozLSLHLW = true;}
      if(wssBZQSLFB == EkIkcKzUmN){mthyKzyhxb = true;}
      if(KaUbhNZGfG == PMSoKEKies){tblmlUiOPa = true;}
      if(SgfnEjPbca == jnVFypGPRS){CREClgEaII = true;}
      while(EkIkcKzUmN == wssBZQSLFB){sLwQtidWIy = true;}
      while(PMSoKEKies == PMSoKEKies){AzTbuLuexs = true;}
      while(jnVFypGPRS == jnVFypGPRS){aiBiQyskyR = true;}
      if(ysAVBsmwWn == true){ysAVBsmwWn = false;}
      if(jhRinypVPb == true){jhRinypVPb = false;}
      if(NJZGeQODll == true){NJZGeQODll = false;}
      if(EiDUPVLwmQ == true){EiDUPVLwmQ = false;}
      if(QOLqJCWmRz == true){QOLqJCWmRz = false;}
      if(zjAoEnTsqk == true){zjAoEnTsqk = false;}
      if(djJkiAdwTR == true){djJkiAdwTR = false;}
      if(mthyKzyhxb == true){mthyKzyhxb = false;}
      if(tblmlUiOPa == true){tblmlUiOPa = false;}
      if(CREClgEaII == true){CREClgEaII = false;}
      if(YZSzMFBBdF == true){YZSzMFBBdF = false;}
      if(pkwOpCyWyN == true){pkwOpCyWyN = false;}
      if(ROgsPVofMd == true){ROgsPVofMd = false;}
      if(tWZoDTIlZg == true){tWZoDTIlZg = false;}
      if(ThkJjQVpLj == true){ThkJjQVpLj = false;}
      if(hhbtqJsZjq == true){hhbtqJsZjq = false;}
      if(PUozLSLHLW == true){PUozLSLHLW = false;}
      if(sLwQtidWIy == true){sLwQtidWIy = false;}
      if(AzTbuLuexs == true){AzTbuLuexs = false;}
      if(aiBiQyskyR == true){aiBiQyskyR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROBVHQLGCB
{ 
  void XiVmDZMrYW()
  { 
      bool qFGzjHikiq = false;
      bool sMhLsKayKJ = false;
      bool UChEzrYnhH = false;
      bool wtrAQRhPyS = false;
      bool hdgOpIKspf = false;
      bool SERgTnXBzq = false;
      bool htCbtyUgub = false;
      bool cKArapVSOq = false;
      bool hfyBorcKgb = false;
      bool sfPGjnaEUr = false;
      bool mdxNDHDZGc = false;
      bool REmIJCuAlC = false;
      bool VJzShwttHm = false;
      bool PQyWEDikyh = false;
      bool nCEEKosHxh = false;
      bool rZSRWcddfG = false;
      bool MJRSMBFQEF = false;
      bool SKCENSFuIr = false;
      bool ClxZtpyfza = false;
      bool ZEEqUekkrJ = false;
      string bjJjeiAYLf;
      string oynoQkpzFy;
      string rQrBuefoQX;
      string gjEVsUmXGb;
      string znOUetPefg;
      string zTOuDLqHoA;
      string DLInyEsSuu;
      string xRrczEBWWA;
      string OAIjXMUJRh;
      string deiGYnfaWZ;
      string Axjkihbkwz;
      string JTknlCCYPl;
      string ijBMRRikEL;
      string YZAwzQQXAp;
      string kjMRXJttUV;
      string kGKjpQwWTQ;
      string zqgjajSnnU;
      string ldXZBzWioH;
      string XnPhZROPGi;
      string UsEiqsCbqn;
      if(bjJjeiAYLf == Axjkihbkwz){qFGzjHikiq = true;}
      else if(Axjkihbkwz == bjJjeiAYLf){mdxNDHDZGc = true;}
      if(oynoQkpzFy == JTknlCCYPl){sMhLsKayKJ = true;}
      else if(JTknlCCYPl == oynoQkpzFy){REmIJCuAlC = true;}
      if(rQrBuefoQX == ijBMRRikEL){UChEzrYnhH = true;}
      else if(ijBMRRikEL == rQrBuefoQX){VJzShwttHm = true;}
      if(gjEVsUmXGb == YZAwzQQXAp){wtrAQRhPyS = true;}
      else if(YZAwzQQXAp == gjEVsUmXGb){PQyWEDikyh = true;}
      if(znOUetPefg == kjMRXJttUV){hdgOpIKspf = true;}
      else if(kjMRXJttUV == znOUetPefg){nCEEKosHxh = true;}
      if(zTOuDLqHoA == kGKjpQwWTQ){SERgTnXBzq = true;}
      else if(kGKjpQwWTQ == zTOuDLqHoA){rZSRWcddfG = true;}
      if(DLInyEsSuu == zqgjajSnnU){htCbtyUgub = true;}
      else if(zqgjajSnnU == DLInyEsSuu){MJRSMBFQEF = true;}
      if(xRrczEBWWA == ldXZBzWioH){cKArapVSOq = true;}
      if(OAIjXMUJRh == XnPhZROPGi){hfyBorcKgb = true;}
      if(deiGYnfaWZ == UsEiqsCbqn){sfPGjnaEUr = true;}
      while(ldXZBzWioH == xRrczEBWWA){SKCENSFuIr = true;}
      while(XnPhZROPGi == XnPhZROPGi){ClxZtpyfza = true;}
      while(UsEiqsCbqn == UsEiqsCbqn){ZEEqUekkrJ = true;}
      if(qFGzjHikiq == true){qFGzjHikiq = false;}
      if(sMhLsKayKJ == true){sMhLsKayKJ = false;}
      if(UChEzrYnhH == true){UChEzrYnhH = false;}
      if(wtrAQRhPyS == true){wtrAQRhPyS = false;}
      if(hdgOpIKspf == true){hdgOpIKspf = false;}
      if(SERgTnXBzq == true){SERgTnXBzq = false;}
      if(htCbtyUgub == true){htCbtyUgub = false;}
      if(cKArapVSOq == true){cKArapVSOq = false;}
      if(hfyBorcKgb == true){hfyBorcKgb = false;}
      if(sfPGjnaEUr == true){sfPGjnaEUr = false;}
      if(mdxNDHDZGc == true){mdxNDHDZGc = false;}
      if(REmIJCuAlC == true){REmIJCuAlC = false;}
      if(VJzShwttHm == true){VJzShwttHm = false;}
      if(PQyWEDikyh == true){PQyWEDikyh = false;}
      if(nCEEKosHxh == true){nCEEKosHxh = false;}
      if(rZSRWcddfG == true){rZSRWcddfG = false;}
      if(MJRSMBFQEF == true){MJRSMBFQEF = false;}
      if(SKCENSFuIr == true){SKCENSFuIr = false;}
      if(ClxZtpyfza == true){ClxZtpyfza = false;}
      if(ZEEqUekkrJ == true){ZEEqUekkrJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGNLYKUMTH
{ 
  void bXTtqhFYKm()
  { 
      bool wKbUALSJrf = false;
      bool BRwmInePeW = false;
      bool NhrYgQqSKH = false;
      bool JsSnDdOMea = false;
      bool PjlXGRcUtN = false;
      bool kVONTNRCmi = false;
      bool TAykVHzIjd = false;
      bool YSkDHdwTSP = false;
      bool nVYxVmeEUo = false;
      bool LMZuGPkABy = false;
      bool SUkPnSkKGp = false;
      bool RxiWuxbBOi = false;
      bool btntRMsoxr = false;
      bool suSTwSkIID = false;
      bool CUydWNcCzJ = false;
      bool mikSWXgqxb = false;
      bool YuMOxVeOZc = false;
      bool MSsLgHwJWD = false;
      bool jqpnEJJzxY = false;
      bool ktKgdGHigA = false;
      string NLfyEfocfc;
      string wQsqIZdjis;
      string AGpSoHYGPZ;
      string RSscTkusGi;
      string oUXchIiBRW;
      string OIRSHGUMIw;
      string HiMFKcWQXW;
      string djczDeiNjg;
      string YWorLIAZUM;
      string PikJbFIRSE;
      string kSdtrdfSOc;
      string XHbbXjtUtB;
      string cxwKHuzSWx;
      string WQufuGstzg;
      string cgKqoIGIlr;
      string LnWQbnVSlx;
      string eMuRGHMwgR;
      string qzUNXumEVz;
      string npgelisdDH;
      string jZICCQlskg;
      if(NLfyEfocfc == kSdtrdfSOc){wKbUALSJrf = true;}
      else if(kSdtrdfSOc == NLfyEfocfc){SUkPnSkKGp = true;}
      if(wQsqIZdjis == XHbbXjtUtB){BRwmInePeW = true;}
      else if(XHbbXjtUtB == wQsqIZdjis){RxiWuxbBOi = true;}
      if(AGpSoHYGPZ == cxwKHuzSWx){NhrYgQqSKH = true;}
      else if(cxwKHuzSWx == AGpSoHYGPZ){btntRMsoxr = true;}
      if(RSscTkusGi == WQufuGstzg){JsSnDdOMea = true;}
      else if(WQufuGstzg == RSscTkusGi){suSTwSkIID = true;}
      if(oUXchIiBRW == cgKqoIGIlr){PjlXGRcUtN = true;}
      else if(cgKqoIGIlr == oUXchIiBRW){CUydWNcCzJ = true;}
      if(OIRSHGUMIw == LnWQbnVSlx){kVONTNRCmi = true;}
      else if(LnWQbnVSlx == OIRSHGUMIw){mikSWXgqxb = true;}
      if(HiMFKcWQXW == eMuRGHMwgR){TAykVHzIjd = true;}
      else if(eMuRGHMwgR == HiMFKcWQXW){YuMOxVeOZc = true;}
      if(djczDeiNjg == qzUNXumEVz){YSkDHdwTSP = true;}
      if(YWorLIAZUM == npgelisdDH){nVYxVmeEUo = true;}
      if(PikJbFIRSE == jZICCQlskg){LMZuGPkABy = true;}
      while(qzUNXumEVz == djczDeiNjg){MSsLgHwJWD = true;}
      while(npgelisdDH == npgelisdDH){jqpnEJJzxY = true;}
      while(jZICCQlskg == jZICCQlskg){ktKgdGHigA = true;}
      if(wKbUALSJrf == true){wKbUALSJrf = false;}
      if(BRwmInePeW == true){BRwmInePeW = false;}
      if(NhrYgQqSKH == true){NhrYgQqSKH = false;}
      if(JsSnDdOMea == true){JsSnDdOMea = false;}
      if(PjlXGRcUtN == true){PjlXGRcUtN = false;}
      if(kVONTNRCmi == true){kVONTNRCmi = false;}
      if(TAykVHzIjd == true){TAykVHzIjd = false;}
      if(YSkDHdwTSP == true){YSkDHdwTSP = false;}
      if(nVYxVmeEUo == true){nVYxVmeEUo = false;}
      if(LMZuGPkABy == true){LMZuGPkABy = false;}
      if(SUkPnSkKGp == true){SUkPnSkKGp = false;}
      if(RxiWuxbBOi == true){RxiWuxbBOi = false;}
      if(btntRMsoxr == true){btntRMsoxr = false;}
      if(suSTwSkIID == true){suSTwSkIID = false;}
      if(CUydWNcCzJ == true){CUydWNcCzJ = false;}
      if(mikSWXgqxb == true){mikSWXgqxb = false;}
      if(YuMOxVeOZc == true){YuMOxVeOZc = false;}
      if(MSsLgHwJWD == true){MSsLgHwJWD = false;}
      if(jqpnEJJzxY == true){jqpnEJJzxY = false;}
      if(ktKgdGHigA == true){ktKgdGHigA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBKQPSPJNT
{ 
  void jdGdjQMJWC()
  { 
      bool TIYyPQGHpE = false;
      bool dPwCOidVbL = false;
      bool fEbdECqbyp = false;
      bool bNiWylgJhs = false;
      bool ExpwLnyRxJ = false;
      bool EbARMPfusN = false;
      bool YeJzbPfYDc = false;
      bool CTnhGiNfRQ = false;
      bool EYeolzNRKi = false;
      bool FlPUTZmqTu = false;
      bool HYNTHjnRKc = false;
      bool BAccIAzUMc = false;
      bool COOUXPDTOg = false;
      bool wWMVJeLLgB = false;
      bool LuGghFImLT = false;
      bool ZRdqsrKswq = false;
      bool gUDdgdmGTd = false;
      bool onmKQGHglR = false;
      bool GQHtGdrUcQ = false;
      bool TROpUpqcAD = false;
      string IMjYRufuYs;
      string tXUxjhILEh;
      string krbVIIfrae;
      string dCdYiXHmCd;
      string RYRXQVlTGP;
      string IIEorPkNQJ;
      string OmUtOqtwNL;
      string ZUIZQMaEEl;
      string VMkKVUxngT;
      string mtWsPdEWIY;
      string bpGuonAeYf;
      string ogIdmCCJYs;
      string tGOtYfyOKl;
      string HDufKeFpUh;
      string USPBdFkrGM;
      string buyOeUbLVJ;
      string olTlXkkcTH;
      string wLnpYaqMPS;
      string tFIyKLEfAo;
      string DtULrhycds;
      if(IMjYRufuYs == bpGuonAeYf){TIYyPQGHpE = true;}
      else if(bpGuonAeYf == IMjYRufuYs){HYNTHjnRKc = true;}
      if(tXUxjhILEh == ogIdmCCJYs){dPwCOidVbL = true;}
      else if(ogIdmCCJYs == tXUxjhILEh){BAccIAzUMc = true;}
      if(krbVIIfrae == tGOtYfyOKl){fEbdECqbyp = true;}
      else if(tGOtYfyOKl == krbVIIfrae){COOUXPDTOg = true;}
      if(dCdYiXHmCd == HDufKeFpUh){bNiWylgJhs = true;}
      else if(HDufKeFpUh == dCdYiXHmCd){wWMVJeLLgB = true;}
      if(RYRXQVlTGP == USPBdFkrGM){ExpwLnyRxJ = true;}
      else if(USPBdFkrGM == RYRXQVlTGP){LuGghFImLT = true;}
      if(IIEorPkNQJ == buyOeUbLVJ){EbARMPfusN = true;}
      else if(buyOeUbLVJ == IIEorPkNQJ){ZRdqsrKswq = true;}
      if(OmUtOqtwNL == olTlXkkcTH){YeJzbPfYDc = true;}
      else if(olTlXkkcTH == OmUtOqtwNL){gUDdgdmGTd = true;}
      if(ZUIZQMaEEl == wLnpYaqMPS){CTnhGiNfRQ = true;}
      if(VMkKVUxngT == tFIyKLEfAo){EYeolzNRKi = true;}
      if(mtWsPdEWIY == DtULrhycds){FlPUTZmqTu = true;}
      while(wLnpYaqMPS == ZUIZQMaEEl){onmKQGHglR = true;}
      while(tFIyKLEfAo == tFIyKLEfAo){GQHtGdrUcQ = true;}
      while(DtULrhycds == DtULrhycds){TROpUpqcAD = true;}
      if(TIYyPQGHpE == true){TIYyPQGHpE = false;}
      if(dPwCOidVbL == true){dPwCOidVbL = false;}
      if(fEbdECqbyp == true){fEbdECqbyp = false;}
      if(bNiWylgJhs == true){bNiWylgJhs = false;}
      if(ExpwLnyRxJ == true){ExpwLnyRxJ = false;}
      if(EbARMPfusN == true){EbARMPfusN = false;}
      if(YeJzbPfYDc == true){YeJzbPfYDc = false;}
      if(CTnhGiNfRQ == true){CTnhGiNfRQ = false;}
      if(EYeolzNRKi == true){EYeolzNRKi = false;}
      if(FlPUTZmqTu == true){FlPUTZmqTu = false;}
      if(HYNTHjnRKc == true){HYNTHjnRKc = false;}
      if(BAccIAzUMc == true){BAccIAzUMc = false;}
      if(COOUXPDTOg == true){COOUXPDTOg = false;}
      if(wWMVJeLLgB == true){wWMVJeLLgB = false;}
      if(LuGghFImLT == true){LuGghFImLT = false;}
      if(ZRdqsrKswq == true){ZRdqsrKswq = false;}
      if(gUDdgdmGTd == true){gUDdgdmGTd = false;}
      if(onmKQGHglR == true){onmKQGHglR = false;}
      if(GQHtGdrUcQ == true){GQHtGdrUcQ = false;}
      if(TROpUpqcAD == true){TROpUpqcAD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUVYTVCGBZ
{ 
  void fIrUCcxDoB()
  { 
      bool rXeokMRJWS = false;
      bool btmImblyie = false;
      bool MYkCdLQknG = false;
      bool mBpaKdfmLR = false;
      bool bLocYBixCa = false;
      bool YuRIrTlbKY = false;
      bool ufVQfaDMyJ = false;
      bool uymQCAjIdc = false;
      bool bThMgqjgiq = false;
      bool qEblVuoYxx = false;
      bool xWzsfaIAFq = false;
      bool idxhxbxIin = false;
      bool qWcHSqVAuH = false;
      bool KKKgeEUogG = false;
      bool hiarHNGtos = false;
      bool ygoIGatqZn = false;
      bool EIFyfYTQDr = false;
      bool HHbcGHukzF = false;
      bool kbKBIdUBaD = false;
      bool KcPsBZdbLi = false;
      string VFNPwTtBdR;
      string yzqQeVctAC;
      string cGlQNQUyPT;
      string rXyaHieRpr;
      string SmwFxsftnm;
      string sLUKBPSwCe;
      string zwkJYZBQJw;
      string pKDIjoJgSU;
      string jaJcZgCmYr;
      string PiPKrWBlfX;
      string qPjrwhHMaM;
      string FlcguYmIjq;
      string XNqRgHtrQN;
      string mXAudUpQfq;
      string ZpMMldFiPT;
      string isCnzcYSLo;
      string nOuMYhkgDZ;
      string iVbrRgBdeC;
      string BLcwdsVLuA;
      string uWFpDKtAnE;
      if(VFNPwTtBdR == qPjrwhHMaM){rXeokMRJWS = true;}
      else if(qPjrwhHMaM == VFNPwTtBdR){xWzsfaIAFq = true;}
      if(yzqQeVctAC == FlcguYmIjq){btmImblyie = true;}
      else if(FlcguYmIjq == yzqQeVctAC){idxhxbxIin = true;}
      if(cGlQNQUyPT == XNqRgHtrQN){MYkCdLQknG = true;}
      else if(XNqRgHtrQN == cGlQNQUyPT){qWcHSqVAuH = true;}
      if(rXyaHieRpr == mXAudUpQfq){mBpaKdfmLR = true;}
      else if(mXAudUpQfq == rXyaHieRpr){KKKgeEUogG = true;}
      if(SmwFxsftnm == ZpMMldFiPT){bLocYBixCa = true;}
      else if(ZpMMldFiPT == SmwFxsftnm){hiarHNGtos = true;}
      if(sLUKBPSwCe == isCnzcYSLo){YuRIrTlbKY = true;}
      else if(isCnzcYSLo == sLUKBPSwCe){ygoIGatqZn = true;}
      if(zwkJYZBQJw == nOuMYhkgDZ){ufVQfaDMyJ = true;}
      else if(nOuMYhkgDZ == zwkJYZBQJw){EIFyfYTQDr = true;}
      if(pKDIjoJgSU == iVbrRgBdeC){uymQCAjIdc = true;}
      if(jaJcZgCmYr == BLcwdsVLuA){bThMgqjgiq = true;}
      if(PiPKrWBlfX == uWFpDKtAnE){qEblVuoYxx = true;}
      while(iVbrRgBdeC == pKDIjoJgSU){HHbcGHukzF = true;}
      while(BLcwdsVLuA == BLcwdsVLuA){kbKBIdUBaD = true;}
      while(uWFpDKtAnE == uWFpDKtAnE){KcPsBZdbLi = true;}
      if(rXeokMRJWS == true){rXeokMRJWS = false;}
      if(btmImblyie == true){btmImblyie = false;}
      if(MYkCdLQknG == true){MYkCdLQknG = false;}
      if(mBpaKdfmLR == true){mBpaKdfmLR = false;}
      if(bLocYBixCa == true){bLocYBixCa = false;}
      if(YuRIrTlbKY == true){YuRIrTlbKY = false;}
      if(ufVQfaDMyJ == true){ufVQfaDMyJ = false;}
      if(uymQCAjIdc == true){uymQCAjIdc = false;}
      if(bThMgqjgiq == true){bThMgqjgiq = false;}
      if(qEblVuoYxx == true){qEblVuoYxx = false;}
      if(xWzsfaIAFq == true){xWzsfaIAFq = false;}
      if(idxhxbxIin == true){idxhxbxIin = false;}
      if(qWcHSqVAuH == true){qWcHSqVAuH = false;}
      if(KKKgeEUogG == true){KKKgeEUogG = false;}
      if(hiarHNGtos == true){hiarHNGtos = false;}
      if(ygoIGatqZn == true){ygoIGatqZn = false;}
      if(EIFyfYTQDr == true){EIFyfYTQDr = false;}
      if(HHbcGHukzF == true){HHbcGHukzF = false;}
      if(kbKBIdUBaD == true){kbKBIdUBaD = false;}
      if(KcPsBZdbLi == true){KcPsBZdbLi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKLGDSITGV
{ 
  void pTYOoxejAx()
  { 
      bool sxKpoKgJVr = false;
      bool lrABjHChRQ = false;
      bool FAGXjRkoJT = false;
      bool tnuSpnQLgT = false;
      bool nifzasinyJ = false;
      bool VtbsLsqlGX = false;
      bool ZrzBxxxgLw = false;
      bool pqBybWUGwq = false;
      bool iwqAxAMCHx = false;
      bool weFJswidBd = false;
      bool uBbBTesdQn = false;
      bool YjoOncAzEx = false;
      bool kuZNzKlqEf = false;
      bool mpESugTpfR = false;
      bool GhlSYMppUP = false;
      bool wjYErzbNBJ = false;
      bool sBYjAheVTH = false;
      bool JKSlpCJHom = false;
      bool TuWnjDRAZu = false;
      bool FGnWYFJBRq = false;
      string rbiBhwseeM;
      string zDuqYRzhJk;
      string cdHCEtYAty;
      string rtXiCghMEj;
      string gSqFZaLWIl;
      string swsRXNTgwm;
      string WskfTFfMnr;
      string imdZDJmCbc;
      string iCqHFwAFKo;
      string MBPQMmhKlU;
      string uziQDFRSNN;
      string ZRFTEUBcZW;
      string FZByegWNNQ;
      string acPGhiTaEz;
      string dhqwOuwwLq;
      string kFjOPUxjkV;
      string hEFxmxBykV;
      string BZXasWiEjj;
      string kaBWeVrBqN;
      string kiohQYctJQ;
      if(rbiBhwseeM == uziQDFRSNN){sxKpoKgJVr = true;}
      else if(uziQDFRSNN == rbiBhwseeM){uBbBTesdQn = true;}
      if(zDuqYRzhJk == ZRFTEUBcZW){lrABjHChRQ = true;}
      else if(ZRFTEUBcZW == zDuqYRzhJk){YjoOncAzEx = true;}
      if(cdHCEtYAty == FZByegWNNQ){FAGXjRkoJT = true;}
      else if(FZByegWNNQ == cdHCEtYAty){kuZNzKlqEf = true;}
      if(rtXiCghMEj == acPGhiTaEz){tnuSpnQLgT = true;}
      else if(acPGhiTaEz == rtXiCghMEj){mpESugTpfR = true;}
      if(gSqFZaLWIl == dhqwOuwwLq){nifzasinyJ = true;}
      else if(dhqwOuwwLq == gSqFZaLWIl){GhlSYMppUP = true;}
      if(swsRXNTgwm == kFjOPUxjkV){VtbsLsqlGX = true;}
      else if(kFjOPUxjkV == swsRXNTgwm){wjYErzbNBJ = true;}
      if(WskfTFfMnr == hEFxmxBykV){ZrzBxxxgLw = true;}
      else if(hEFxmxBykV == WskfTFfMnr){sBYjAheVTH = true;}
      if(imdZDJmCbc == BZXasWiEjj){pqBybWUGwq = true;}
      if(iCqHFwAFKo == kaBWeVrBqN){iwqAxAMCHx = true;}
      if(MBPQMmhKlU == kiohQYctJQ){weFJswidBd = true;}
      while(BZXasWiEjj == imdZDJmCbc){JKSlpCJHom = true;}
      while(kaBWeVrBqN == kaBWeVrBqN){TuWnjDRAZu = true;}
      while(kiohQYctJQ == kiohQYctJQ){FGnWYFJBRq = true;}
      if(sxKpoKgJVr == true){sxKpoKgJVr = false;}
      if(lrABjHChRQ == true){lrABjHChRQ = false;}
      if(FAGXjRkoJT == true){FAGXjRkoJT = false;}
      if(tnuSpnQLgT == true){tnuSpnQLgT = false;}
      if(nifzasinyJ == true){nifzasinyJ = false;}
      if(VtbsLsqlGX == true){VtbsLsqlGX = false;}
      if(ZrzBxxxgLw == true){ZrzBxxxgLw = false;}
      if(pqBybWUGwq == true){pqBybWUGwq = false;}
      if(iwqAxAMCHx == true){iwqAxAMCHx = false;}
      if(weFJswidBd == true){weFJswidBd = false;}
      if(uBbBTesdQn == true){uBbBTesdQn = false;}
      if(YjoOncAzEx == true){YjoOncAzEx = false;}
      if(kuZNzKlqEf == true){kuZNzKlqEf = false;}
      if(mpESugTpfR == true){mpESugTpfR = false;}
      if(GhlSYMppUP == true){GhlSYMppUP = false;}
      if(wjYErzbNBJ == true){wjYErzbNBJ = false;}
      if(sBYjAheVTH == true){sBYjAheVTH = false;}
      if(JKSlpCJHom == true){JKSlpCJHom = false;}
      if(TuWnjDRAZu == true){TuWnjDRAZu = false;}
      if(FGnWYFJBRq == true){FGnWYFJBRq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEPKZWTLKA
{ 
  void yfwpXhpPYk()
  { 
      bool oOaCrnesVB = false;
      bool tRMzRgRHxE = false;
      bool EnLDUaoEtN = false;
      bool pnDxQTlYDU = false;
      bool OLoIhrfGnO = false;
      bool sUBnxBDWhR = false;
      bool zazILGNPiy = false;
      bool tsEcosyCVc = false;
      bool thPfTUlPzO = false;
      bool QPqkVnMgwa = false;
      bool dPXoTAPXyE = false;
      bool DAAEXQKSop = false;
      bool TyPTheBTGB = false;
      bool fRFuyeKZMS = false;
      bool FOQuLPOlNF = false;
      bool csrGGfzEHn = false;
      bool ywRxXktFGs = false;
      bool FjGVkFgTHR = false;
      bool PPFBXmZznR = false;
      bool eFSXUIxTXa = false;
      string MZGiTSflWn;
      string pyMkUjjHcG;
      string pIoJKpTHuj;
      string CyxzOehTNj;
      string SyCJLaPrrU;
      string euEoZEjxXd;
      string zYqlkrANVp;
      string CPsrnqFexi;
      string aaOZFHsHZK;
      string tjujjsHQYT;
      string ZCWCSOCMBh;
      string zFzoDXJRgd;
      string zsnKuSTIIt;
      string joGdJXEMGp;
      string EgGqLojGgL;
      string jpitTgOLGA;
      string usDHyJzVfe;
      string TwKpYSlwyG;
      string hNawJtFLKb;
      string JsGGuLcyrB;
      if(MZGiTSflWn == ZCWCSOCMBh){oOaCrnesVB = true;}
      else if(ZCWCSOCMBh == MZGiTSflWn){dPXoTAPXyE = true;}
      if(pyMkUjjHcG == zFzoDXJRgd){tRMzRgRHxE = true;}
      else if(zFzoDXJRgd == pyMkUjjHcG){DAAEXQKSop = true;}
      if(pIoJKpTHuj == zsnKuSTIIt){EnLDUaoEtN = true;}
      else if(zsnKuSTIIt == pIoJKpTHuj){TyPTheBTGB = true;}
      if(CyxzOehTNj == joGdJXEMGp){pnDxQTlYDU = true;}
      else if(joGdJXEMGp == CyxzOehTNj){fRFuyeKZMS = true;}
      if(SyCJLaPrrU == EgGqLojGgL){OLoIhrfGnO = true;}
      else if(EgGqLojGgL == SyCJLaPrrU){FOQuLPOlNF = true;}
      if(euEoZEjxXd == jpitTgOLGA){sUBnxBDWhR = true;}
      else if(jpitTgOLGA == euEoZEjxXd){csrGGfzEHn = true;}
      if(zYqlkrANVp == usDHyJzVfe){zazILGNPiy = true;}
      else if(usDHyJzVfe == zYqlkrANVp){ywRxXktFGs = true;}
      if(CPsrnqFexi == TwKpYSlwyG){tsEcosyCVc = true;}
      if(aaOZFHsHZK == hNawJtFLKb){thPfTUlPzO = true;}
      if(tjujjsHQYT == JsGGuLcyrB){QPqkVnMgwa = true;}
      while(TwKpYSlwyG == CPsrnqFexi){FjGVkFgTHR = true;}
      while(hNawJtFLKb == hNawJtFLKb){PPFBXmZznR = true;}
      while(JsGGuLcyrB == JsGGuLcyrB){eFSXUIxTXa = true;}
      if(oOaCrnesVB == true){oOaCrnesVB = false;}
      if(tRMzRgRHxE == true){tRMzRgRHxE = false;}
      if(EnLDUaoEtN == true){EnLDUaoEtN = false;}
      if(pnDxQTlYDU == true){pnDxQTlYDU = false;}
      if(OLoIhrfGnO == true){OLoIhrfGnO = false;}
      if(sUBnxBDWhR == true){sUBnxBDWhR = false;}
      if(zazILGNPiy == true){zazILGNPiy = false;}
      if(tsEcosyCVc == true){tsEcosyCVc = false;}
      if(thPfTUlPzO == true){thPfTUlPzO = false;}
      if(QPqkVnMgwa == true){QPqkVnMgwa = false;}
      if(dPXoTAPXyE == true){dPXoTAPXyE = false;}
      if(DAAEXQKSop == true){DAAEXQKSop = false;}
      if(TyPTheBTGB == true){TyPTheBTGB = false;}
      if(fRFuyeKZMS == true){fRFuyeKZMS = false;}
      if(FOQuLPOlNF == true){FOQuLPOlNF = false;}
      if(csrGGfzEHn == true){csrGGfzEHn = false;}
      if(ywRxXktFGs == true){ywRxXktFGs = false;}
      if(FjGVkFgTHR == true){FjGVkFgTHR = false;}
      if(PPFBXmZznR == true){PPFBXmZznR = false;}
      if(eFSXUIxTXa == true){eFSXUIxTXa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVTCZUXXBF
{ 
  void uQqeiQnnNV()
  { 
      bool PnqNLGgfYo = false;
      bool rHNGOShpER = false;
      bool gotfTStXXK = false;
      bool SatUhmfCLq = false;
      bool bsewEZfCbV = false;
      bool mcJqhatKts = false;
      bool MIIOWQNsXb = false;
      bool mfdNpmKxbs = false;
      bool lqwCWoRDlH = false;
      bool sUHSeSkPZm = false;
      bool MmeAhHzwAt = false;
      bool PxiAGVMFrg = false;
      bool zJGPiRXLiW = false;
      bool CuWnfzLuTP = false;
      bool pVCqrwkGLI = false;
      bool GfXsnCfORP = false;
      bool imNdrUZtUG = false;
      bool JQkbqcHPXl = false;
      bool fRzZPWXdAd = false;
      bool TwdDgCIXzW = false;
      string djSHQNscNH;
      string tBtiwaMYPB;
      string GwRPjjIDNI;
      string KhUsedQwmk;
      string RHpCHTwJdu;
      string xOotdgRCWf;
      string FpOEwLgAES;
      string JPkdiyFOIQ;
      string myYSLwraOx;
      string LOZHfaslFu;
      string mwFLkgcLKf;
      string aCtGrGQwrA;
      string TFlGGupdxI;
      string FTJNdqsNge;
      string TgQiWITTOZ;
      string JwsFagKyEp;
      string pyNCaHsfbA;
      string NDPNfloCjy;
      string aWPXyIZDlw;
      string gtJqoVTNIP;
      if(djSHQNscNH == mwFLkgcLKf){PnqNLGgfYo = true;}
      else if(mwFLkgcLKf == djSHQNscNH){MmeAhHzwAt = true;}
      if(tBtiwaMYPB == aCtGrGQwrA){rHNGOShpER = true;}
      else if(aCtGrGQwrA == tBtiwaMYPB){PxiAGVMFrg = true;}
      if(GwRPjjIDNI == TFlGGupdxI){gotfTStXXK = true;}
      else if(TFlGGupdxI == GwRPjjIDNI){zJGPiRXLiW = true;}
      if(KhUsedQwmk == FTJNdqsNge){SatUhmfCLq = true;}
      else if(FTJNdqsNge == KhUsedQwmk){CuWnfzLuTP = true;}
      if(RHpCHTwJdu == TgQiWITTOZ){bsewEZfCbV = true;}
      else if(TgQiWITTOZ == RHpCHTwJdu){pVCqrwkGLI = true;}
      if(xOotdgRCWf == JwsFagKyEp){mcJqhatKts = true;}
      else if(JwsFagKyEp == xOotdgRCWf){GfXsnCfORP = true;}
      if(FpOEwLgAES == pyNCaHsfbA){MIIOWQNsXb = true;}
      else if(pyNCaHsfbA == FpOEwLgAES){imNdrUZtUG = true;}
      if(JPkdiyFOIQ == NDPNfloCjy){mfdNpmKxbs = true;}
      if(myYSLwraOx == aWPXyIZDlw){lqwCWoRDlH = true;}
      if(LOZHfaslFu == gtJqoVTNIP){sUHSeSkPZm = true;}
      while(NDPNfloCjy == JPkdiyFOIQ){JQkbqcHPXl = true;}
      while(aWPXyIZDlw == aWPXyIZDlw){fRzZPWXdAd = true;}
      while(gtJqoVTNIP == gtJqoVTNIP){TwdDgCIXzW = true;}
      if(PnqNLGgfYo == true){PnqNLGgfYo = false;}
      if(rHNGOShpER == true){rHNGOShpER = false;}
      if(gotfTStXXK == true){gotfTStXXK = false;}
      if(SatUhmfCLq == true){SatUhmfCLq = false;}
      if(bsewEZfCbV == true){bsewEZfCbV = false;}
      if(mcJqhatKts == true){mcJqhatKts = false;}
      if(MIIOWQNsXb == true){MIIOWQNsXb = false;}
      if(mfdNpmKxbs == true){mfdNpmKxbs = false;}
      if(lqwCWoRDlH == true){lqwCWoRDlH = false;}
      if(sUHSeSkPZm == true){sUHSeSkPZm = false;}
      if(MmeAhHzwAt == true){MmeAhHzwAt = false;}
      if(PxiAGVMFrg == true){PxiAGVMFrg = false;}
      if(zJGPiRXLiW == true){zJGPiRXLiW = false;}
      if(CuWnfzLuTP == true){CuWnfzLuTP = false;}
      if(pVCqrwkGLI == true){pVCqrwkGLI = false;}
      if(GfXsnCfORP == true){GfXsnCfORP = false;}
      if(imNdrUZtUG == true){imNdrUZtUG = false;}
      if(JQkbqcHPXl == true){JQkbqcHPXl = false;}
      if(fRzZPWXdAd == true){fRzZPWXdAd = false;}
      if(TwdDgCIXzW == true){TwdDgCIXzW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQCJSRYQCA
{ 
  void dmiENYqFIZ()
  { 
      bool eDLGAfHnPt = false;
      bool ZzdPADoVEd = false;
      bool VBHztUClYl = false;
      bool HGdSzDxrmF = false;
      bool CKKdlozBpY = false;
      bool aezQjcwLLf = false;
      bool dVPclTULQw = false;
      bool GwhzaKqdMF = false;
      bool UAuzLcHNhW = false;
      bool HkgHbguhqS = false;
      bool TmksRdwAoZ = false;
      bool lRyGKcZPQJ = false;
      bool LHdsoVPaWt = false;
      bool PIltkgOBgg = false;
      bool gGYIkolZxy = false;
      bool HeRhGMIqEw = false;
      bool OUcuJcfEVc = false;
      bool OXhicFiVIA = false;
      bool ipdXljqEmY = false;
      bool YWxkSLccyH = false;
      string MPsItsMzWU;
      string oqjHbbBBLY;
      string ledpHDclcu;
      string hRPHUOsjbu;
      string GgILsSIqsf;
      string LBLtnhlDAp;
      string QZWamXabmN;
      string hQZQSFWRwo;
      string tkrwjfFVSl;
      string bpjkdgKgYU;
      string qgDfytbubi;
      string KUGLwfgZqG;
      string SFIAkqgnlk;
      string torayMgMxo;
      string DJtibGjXoy;
      string AjpRCkYDtH;
      string MnJpoUbfMi;
      string yTbBCIKYYd;
      string HIymkKzZXM;
      string ndRpcPAEtG;
      if(MPsItsMzWU == qgDfytbubi){eDLGAfHnPt = true;}
      else if(qgDfytbubi == MPsItsMzWU){TmksRdwAoZ = true;}
      if(oqjHbbBBLY == KUGLwfgZqG){ZzdPADoVEd = true;}
      else if(KUGLwfgZqG == oqjHbbBBLY){lRyGKcZPQJ = true;}
      if(ledpHDclcu == SFIAkqgnlk){VBHztUClYl = true;}
      else if(SFIAkqgnlk == ledpHDclcu){LHdsoVPaWt = true;}
      if(hRPHUOsjbu == torayMgMxo){HGdSzDxrmF = true;}
      else if(torayMgMxo == hRPHUOsjbu){PIltkgOBgg = true;}
      if(GgILsSIqsf == DJtibGjXoy){CKKdlozBpY = true;}
      else if(DJtibGjXoy == GgILsSIqsf){gGYIkolZxy = true;}
      if(LBLtnhlDAp == AjpRCkYDtH){aezQjcwLLf = true;}
      else if(AjpRCkYDtH == LBLtnhlDAp){HeRhGMIqEw = true;}
      if(QZWamXabmN == MnJpoUbfMi){dVPclTULQw = true;}
      else if(MnJpoUbfMi == QZWamXabmN){OUcuJcfEVc = true;}
      if(hQZQSFWRwo == yTbBCIKYYd){GwhzaKqdMF = true;}
      if(tkrwjfFVSl == HIymkKzZXM){UAuzLcHNhW = true;}
      if(bpjkdgKgYU == ndRpcPAEtG){HkgHbguhqS = true;}
      while(yTbBCIKYYd == hQZQSFWRwo){OXhicFiVIA = true;}
      while(HIymkKzZXM == HIymkKzZXM){ipdXljqEmY = true;}
      while(ndRpcPAEtG == ndRpcPAEtG){YWxkSLccyH = true;}
      if(eDLGAfHnPt == true){eDLGAfHnPt = false;}
      if(ZzdPADoVEd == true){ZzdPADoVEd = false;}
      if(VBHztUClYl == true){VBHztUClYl = false;}
      if(HGdSzDxrmF == true){HGdSzDxrmF = false;}
      if(CKKdlozBpY == true){CKKdlozBpY = false;}
      if(aezQjcwLLf == true){aezQjcwLLf = false;}
      if(dVPclTULQw == true){dVPclTULQw = false;}
      if(GwhzaKqdMF == true){GwhzaKqdMF = false;}
      if(UAuzLcHNhW == true){UAuzLcHNhW = false;}
      if(HkgHbguhqS == true){HkgHbguhqS = false;}
      if(TmksRdwAoZ == true){TmksRdwAoZ = false;}
      if(lRyGKcZPQJ == true){lRyGKcZPQJ = false;}
      if(LHdsoVPaWt == true){LHdsoVPaWt = false;}
      if(PIltkgOBgg == true){PIltkgOBgg = false;}
      if(gGYIkolZxy == true){gGYIkolZxy = false;}
      if(HeRhGMIqEw == true){HeRhGMIqEw = false;}
      if(OUcuJcfEVc == true){OUcuJcfEVc = false;}
      if(OXhicFiVIA == true){OXhicFiVIA = false;}
      if(ipdXljqEmY == true){ipdXljqEmY = false;}
      if(YWxkSLccyH == true){YWxkSLccyH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCZIMLFASG
{ 
  void HOWdLnpgyj()
  { 
      bool treKPRGyNp = false;
      bool ruUPLKbOWr = false;
      bool PGCkRADbNi = false;
      bool wtJxWYeFwE = false;
      bool VyBWAECktB = false;
      bool wQLiTnosrP = false;
      bool NejdsykXsl = false;
      bool eWSSVREfkN = false;
      bool yRhMlfhZci = false;
      bool jlMgpqNWdC = false;
      bool SdrHVZysMC = false;
      bool iJIeRuwWqN = false;
      bool PLuKCsJlce = false;
      bool EgBitTZZqM = false;
      bool goMazadhPt = false;
      bool tpfQlHigFb = false;
      bool PMPhyBHYjx = false;
      bool VWfdfZzTKa = false;
      bool PbVijNBkwm = false;
      bool jsUPxTZdcy = false;
      string nYkZatmRFV;
      string OaPRzLIkaw;
      string eGqFogpFPd;
      string ywFuLAimTo;
      string rHGPVyjkKd;
      string JzNpKhgejt;
      string DhCaWSVUGy;
      string bVQlDWAbiq;
      string wFtkUyhOkc;
      string TDCZlKFerD;
      string bPeMBnialm;
      string gEusxymQGX;
      string jGiceYSqAs;
      string RUjfOfZhig;
      string PHcxwOHIbn;
      string WnYUSVfCgc;
      string UqasVMUPdR;
      string XFhZHcdkgQ;
      string QJPLVcwOMr;
      string zXBFLYfibj;
      if(nYkZatmRFV == bPeMBnialm){treKPRGyNp = true;}
      else if(bPeMBnialm == nYkZatmRFV){SdrHVZysMC = true;}
      if(OaPRzLIkaw == gEusxymQGX){ruUPLKbOWr = true;}
      else if(gEusxymQGX == OaPRzLIkaw){iJIeRuwWqN = true;}
      if(eGqFogpFPd == jGiceYSqAs){PGCkRADbNi = true;}
      else if(jGiceYSqAs == eGqFogpFPd){PLuKCsJlce = true;}
      if(ywFuLAimTo == RUjfOfZhig){wtJxWYeFwE = true;}
      else if(RUjfOfZhig == ywFuLAimTo){EgBitTZZqM = true;}
      if(rHGPVyjkKd == PHcxwOHIbn){VyBWAECktB = true;}
      else if(PHcxwOHIbn == rHGPVyjkKd){goMazadhPt = true;}
      if(JzNpKhgejt == WnYUSVfCgc){wQLiTnosrP = true;}
      else if(WnYUSVfCgc == JzNpKhgejt){tpfQlHigFb = true;}
      if(DhCaWSVUGy == UqasVMUPdR){NejdsykXsl = true;}
      else if(UqasVMUPdR == DhCaWSVUGy){PMPhyBHYjx = true;}
      if(bVQlDWAbiq == XFhZHcdkgQ){eWSSVREfkN = true;}
      if(wFtkUyhOkc == QJPLVcwOMr){yRhMlfhZci = true;}
      if(TDCZlKFerD == zXBFLYfibj){jlMgpqNWdC = true;}
      while(XFhZHcdkgQ == bVQlDWAbiq){VWfdfZzTKa = true;}
      while(QJPLVcwOMr == QJPLVcwOMr){PbVijNBkwm = true;}
      while(zXBFLYfibj == zXBFLYfibj){jsUPxTZdcy = true;}
      if(treKPRGyNp == true){treKPRGyNp = false;}
      if(ruUPLKbOWr == true){ruUPLKbOWr = false;}
      if(PGCkRADbNi == true){PGCkRADbNi = false;}
      if(wtJxWYeFwE == true){wtJxWYeFwE = false;}
      if(VyBWAECktB == true){VyBWAECktB = false;}
      if(wQLiTnosrP == true){wQLiTnosrP = false;}
      if(NejdsykXsl == true){NejdsykXsl = false;}
      if(eWSSVREfkN == true){eWSSVREfkN = false;}
      if(yRhMlfhZci == true){yRhMlfhZci = false;}
      if(jlMgpqNWdC == true){jlMgpqNWdC = false;}
      if(SdrHVZysMC == true){SdrHVZysMC = false;}
      if(iJIeRuwWqN == true){iJIeRuwWqN = false;}
      if(PLuKCsJlce == true){PLuKCsJlce = false;}
      if(EgBitTZZqM == true){EgBitTZZqM = false;}
      if(goMazadhPt == true){goMazadhPt = false;}
      if(tpfQlHigFb == true){tpfQlHigFb = false;}
      if(PMPhyBHYjx == true){PMPhyBHYjx = false;}
      if(VWfdfZzTKa == true){VWfdfZzTKa = false;}
      if(PbVijNBkwm == true){PbVijNBkwm = false;}
      if(jsUPxTZdcy == true){jsUPxTZdcy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOTCJOBWPI
{ 
  void EPECtCKcqe()
  { 
      bool zmNzFgnQZT = false;
      bool CsCDaoiJau = false;
      bool XLmUaVOVNe = false;
      bool YqjdCaYUhP = false;
      bool JLbDWMDWjo = false;
      bool NJoFPnzrYi = false;
      bool RSCtuLIYBz = false;
      bool PNbKkLijxN = false;
      bool SqkYQPCdNN = false;
      bool bgwzyqJhHL = false;
      bool DdVkYAgdTE = false;
      bool EPtKQZgcce = false;
      bool JdLmXiRcMt = false;
      bool CBblKnVAAQ = false;
      bool hXKJJMllhX = false;
      bool KfEcCYShNp = false;
      bool hERZBCmIzb = false;
      bool EgcLxkTCdL = false;
      bool wftniWxzik = false;
      bool VnlJhcFjHG = false;
      string BqQZQGbuGj;
      string zEncPxfJsY;
      string KYsRLCDHKe;
      string EHfwzZqzMm;
      string MmhKNZEDIH;
      string CAXCkbyzOO;
      string DUjafrXrco;
      string FfxFLWqhEk;
      string xAzCcDidKX;
      string brkxjrCGeU;
      string CMZSCWDSqO;
      string jPtcRCVgyc;
      string IsgFNMtAUS;
      string TjDihkafAF;
      string AQmunLyHfg;
      string VVICMIeTFo;
      string bDxXtzMKtf;
      string bogrbrGkRB;
      string OlTmxybBWZ;
      string FGaKdxSPBn;
      if(BqQZQGbuGj == CMZSCWDSqO){zmNzFgnQZT = true;}
      else if(CMZSCWDSqO == BqQZQGbuGj){DdVkYAgdTE = true;}
      if(zEncPxfJsY == jPtcRCVgyc){CsCDaoiJau = true;}
      else if(jPtcRCVgyc == zEncPxfJsY){EPtKQZgcce = true;}
      if(KYsRLCDHKe == IsgFNMtAUS){XLmUaVOVNe = true;}
      else if(IsgFNMtAUS == KYsRLCDHKe){JdLmXiRcMt = true;}
      if(EHfwzZqzMm == TjDihkafAF){YqjdCaYUhP = true;}
      else if(TjDihkafAF == EHfwzZqzMm){CBblKnVAAQ = true;}
      if(MmhKNZEDIH == AQmunLyHfg){JLbDWMDWjo = true;}
      else if(AQmunLyHfg == MmhKNZEDIH){hXKJJMllhX = true;}
      if(CAXCkbyzOO == VVICMIeTFo){NJoFPnzrYi = true;}
      else if(VVICMIeTFo == CAXCkbyzOO){KfEcCYShNp = true;}
      if(DUjafrXrco == bDxXtzMKtf){RSCtuLIYBz = true;}
      else if(bDxXtzMKtf == DUjafrXrco){hERZBCmIzb = true;}
      if(FfxFLWqhEk == bogrbrGkRB){PNbKkLijxN = true;}
      if(xAzCcDidKX == OlTmxybBWZ){SqkYQPCdNN = true;}
      if(brkxjrCGeU == FGaKdxSPBn){bgwzyqJhHL = true;}
      while(bogrbrGkRB == FfxFLWqhEk){EgcLxkTCdL = true;}
      while(OlTmxybBWZ == OlTmxybBWZ){wftniWxzik = true;}
      while(FGaKdxSPBn == FGaKdxSPBn){VnlJhcFjHG = true;}
      if(zmNzFgnQZT == true){zmNzFgnQZT = false;}
      if(CsCDaoiJau == true){CsCDaoiJau = false;}
      if(XLmUaVOVNe == true){XLmUaVOVNe = false;}
      if(YqjdCaYUhP == true){YqjdCaYUhP = false;}
      if(JLbDWMDWjo == true){JLbDWMDWjo = false;}
      if(NJoFPnzrYi == true){NJoFPnzrYi = false;}
      if(RSCtuLIYBz == true){RSCtuLIYBz = false;}
      if(PNbKkLijxN == true){PNbKkLijxN = false;}
      if(SqkYQPCdNN == true){SqkYQPCdNN = false;}
      if(bgwzyqJhHL == true){bgwzyqJhHL = false;}
      if(DdVkYAgdTE == true){DdVkYAgdTE = false;}
      if(EPtKQZgcce == true){EPtKQZgcce = false;}
      if(JdLmXiRcMt == true){JdLmXiRcMt = false;}
      if(CBblKnVAAQ == true){CBblKnVAAQ = false;}
      if(hXKJJMllhX == true){hXKJJMllhX = false;}
      if(KfEcCYShNp == true){KfEcCYShNp = false;}
      if(hERZBCmIzb == true){hERZBCmIzb = false;}
      if(EgcLxkTCdL == true){EgcLxkTCdL = false;}
      if(wftniWxzik == true){wftniWxzik = false;}
      if(VnlJhcFjHG == true){VnlJhcFjHG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXUFLOHLUX
{ 
  void kSxhFFecax()
  { 
      bool zDlEAgzCUx = false;
      bool sfsrqqzwot = false;
      bool eIqhbfPKgr = false;
      bool XmGdbArUTw = false;
      bool pIbrWBOwEh = false;
      bool TTQPPpLEbU = false;
      bool QnUcZFZOQq = false;
      bool zecsEVfzKa = false;
      bool RSFzXEVpOk = false;
      bool nmryeBnzSQ = false;
      bool azfNhoqXLt = false;
      bool JMsBDyhUFU = false;
      bool jjAeDLmdNC = false;
      bool hggtzRmrQh = false;
      bool NydUbatpug = false;
      bool TSsxgpyAJW = false;
      bool BNJJMcfzBk = false;
      bool KoDWHkFfDb = false;
      bool RwhfhOmiNI = false;
      bool SlhtgAoTIy = false;
      string KROuONFUtU;
      string ZdxsNUpYol;
      string jUPVmkrgsN;
      string JxDKlqmrga;
      string XgpykfwlWR;
      string iDowioBsHd;
      string VXafLcZmHV;
      string hyqOOCeRjH;
      string nFJbeFHHaw;
      string osjDEzGJmH;
      string FJdAjjMahf;
      string KjJAoPNzBF;
      string VSLKfnOmJO;
      string wUebCebJrt;
      string sgZtkEjjOo;
      string kGIgllxSTu;
      string VYQSjpFgxJ;
      string nEHGMnsQZa;
      string DdYUcoLxpP;
      string hIowYTPGKu;
      if(KROuONFUtU == FJdAjjMahf){zDlEAgzCUx = true;}
      else if(FJdAjjMahf == KROuONFUtU){azfNhoqXLt = true;}
      if(ZdxsNUpYol == KjJAoPNzBF){sfsrqqzwot = true;}
      else if(KjJAoPNzBF == ZdxsNUpYol){JMsBDyhUFU = true;}
      if(jUPVmkrgsN == VSLKfnOmJO){eIqhbfPKgr = true;}
      else if(VSLKfnOmJO == jUPVmkrgsN){jjAeDLmdNC = true;}
      if(JxDKlqmrga == wUebCebJrt){XmGdbArUTw = true;}
      else if(wUebCebJrt == JxDKlqmrga){hggtzRmrQh = true;}
      if(XgpykfwlWR == sgZtkEjjOo){pIbrWBOwEh = true;}
      else if(sgZtkEjjOo == XgpykfwlWR){NydUbatpug = true;}
      if(iDowioBsHd == kGIgllxSTu){TTQPPpLEbU = true;}
      else if(kGIgllxSTu == iDowioBsHd){TSsxgpyAJW = true;}
      if(VXafLcZmHV == VYQSjpFgxJ){QnUcZFZOQq = true;}
      else if(VYQSjpFgxJ == VXafLcZmHV){BNJJMcfzBk = true;}
      if(hyqOOCeRjH == nEHGMnsQZa){zecsEVfzKa = true;}
      if(nFJbeFHHaw == DdYUcoLxpP){RSFzXEVpOk = true;}
      if(osjDEzGJmH == hIowYTPGKu){nmryeBnzSQ = true;}
      while(nEHGMnsQZa == hyqOOCeRjH){KoDWHkFfDb = true;}
      while(DdYUcoLxpP == DdYUcoLxpP){RwhfhOmiNI = true;}
      while(hIowYTPGKu == hIowYTPGKu){SlhtgAoTIy = true;}
      if(zDlEAgzCUx == true){zDlEAgzCUx = false;}
      if(sfsrqqzwot == true){sfsrqqzwot = false;}
      if(eIqhbfPKgr == true){eIqhbfPKgr = false;}
      if(XmGdbArUTw == true){XmGdbArUTw = false;}
      if(pIbrWBOwEh == true){pIbrWBOwEh = false;}
      if(TTQPPpLEbU == true){TTQPPpLEbU = false;}
      if(QnUcZFZOQq == true){QnUcZFZOQq = false;}
      if(zecsEVfzKa == true){zecsEVfzKa = false;}
      if(RSFzXEVpOk == true){RSFzXEVpOk = false;}
      if(nmryeBnzSQ == true){nmryeBnzSQ = false;}
      if(azfNhoqXLt == true){azfNhoqXLt = false;}
      if(JMsBDyhUFU == true){JMsBDyhUFU = false;}
      if(jjAeDLmdNC == true){jjAeDLmdNC = false;}
      if(hggtzRmrQh == true){hggtzRmrQh = false;}
      if(NydUbatpug == true){NydUbatpug = false;}
      if(TSsxgpyAJW == true){TSsxgpyAJW = false;}
      if(BNJJMcfzBk == true){BNJJMcfzBk = false;}
      if(KoDWHkFfDb == true){KoDWHkFfDb = false;}
      if(RwhfhOmiNI == true){RwhfhOmiNI = false;}
      if(SlhtgAoTIy == true){SlhtgAoTIy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UWDWLNYUXZ
{ 
  void BGmhbRJfps()
  { 
      bool iRVtWtueIK = false;
      bool BscELZJNfg = false;
      bool ZxtotmoPTY = false;
      bool bNgHHXVTny = false;
      bool YpcILbSgkT = false;
      bool MqqkNlXfzj = false;
      bool EeKiinMVxn = false;
      bool DoZgIjUldR = false;
      bool THeAMjVusV = false;
      bool zpTDtsfsYW = false;
      bool PxjxPWQJbd = false;
      bool QlBhQxAJWy = false;
      bool RQbanNUWmP = false;
      bool DbMGCWWhko = false;
      bool TLSOFNnlmw = false;
      bool sVVaFzUIIB = false;
      bool BsWMaoYtfs = false;
      bool ZRYgeFxNVa = false;
      bool ZijqWgGlBC = false;
      bool COYjnZoGnP = false;
      string CCneIqmwca;
      string VilMnTkETU;
      string pMAzHDKpRM;
      string xoQUkpswrq;
      string bwgUjmciCx;
      string VHTfXoBnWE;
      string fxdPdgSQbx;
      string aoLcsteeOU;
      string abmTqoUjxu;
      string nEZnKeRQqD;
      string UMGFWguqmc;
      string KWYBdEJJYn;
      string LhTgIVOXRN;
      string bNnLzOVhxK;
      string sdwTkRfXJG;
      string UHrCrmrYwB;
      string RXYYBwhNCP;
      string iaMNtgkzwq;
      string pqNKsTVkTM;
      string VwlwsVFXSn;
      if(CCneIqmwca == UMGFWguqmc){iRVtWtueIK = true;}
      else if(UMGFWguqmc == CCneIqmwca){PxjxPWQJbd = true;}
      if(VilMnTkETU == KWYBdEJJYn){BscELZJNfg = true;}
      else if(KWYBdEJJYn == VilMnTkETU){QlBhQxAJWy = true;}
      if(pMAzHDKpRM == LhTgIVOXRN){ZxtotmoPTY = true;}
      else if(LhTgIVOXRN == pMAzHDKpRM){RQbanNUWmP = true;}
      if(xoQUkpswrq == bNnLzOVhxK){bNgHHXVTny = true;}
      else if(bNnLzOVhxK == xoQUkpswrq){DbMGCWWhko = true;}
      if(bwgUjmciCx == sdwTkRfXJG){YpcILbSgkT = true;}
      else if(sdwTkRfXJG == bwgUjmciCx){TLSOFNnlmw = true;}
      if(VHTfXoBnWE == UHrCrmrYwB){MqqkNlXfzj = true;}
      else if(UHrCrmrYwB == VHTfXoBnWE){sVVaFzUIIB = true;}
      if(fxdPdgSQbx == RXYYBwhNCP){EeKiinMVxn = true;}
      else if(RXYYBwhNCP == fxdPdgSQbx){BsWMaoYtfs = true;}
      if(aoLcsteeOU == iaMNtgkzwq){DoZgIjUldR = true;}
      if(abmTqoUjxu == pqNKsTVkTM){THeAMjVusV = true;}
      if(nEZnKeRQqD == VwlwsVFXSn){zpTDtsfsYW = true;}
      while(iaMNtgkzwq == aoLcsteeOU){ZRYgeFxNVa = true;}
      while(pqNKsTVkTM == pqNKsTVkTM){ZijqWgGlBC = true;}
      while(VwlwsVFXSn == VwlwsVFXSn){COYjnZoGnP = true;}
      if(iRVtWtueIK == true){iRVtWtueIK = false;}
      if(BscELZJNfg == true){BscELZJNfg = false;}
      if(ZxtotmoPTY == true){ZxtotmoPTY = false;}
      if(bNgHHXVTny == true){bNgHHXVTny = false;}
      if(YpcILbSgkT == true){YpcILbSgkT = false;}
      if(MqqkNlXfzj == true){MqqkNlXfzj = false;}
      if(EeKiinMVxn == true){EeKiinMVxn = false;}
      if(DoZgIjUldR == true){DoZgIjUldR = false;}
      if(THeAMjVusV == true){THeAMjVusV = false;}
      if(zpTDtsfsYW == true){zpTDtsfsYW = false;}
      if(PxjxPWQJbd == true){PxjxPWQJbd = false;}
      if(QlBhQxAJWy == true){QlBhQxAJWy = false;}
      if(RQbanNUWmP == true){RQbanNUWmP = false;}
      if(DbMGCWWhko == true){DbMGCWWhko = false;}
      if(TLSOFNnlmw == true){TLSOFNnlmw = false;}
      if(sVVaFzUIIB == true){sVVaFzUIIB = false;}
      if(BsWMaoYtfs == true){BsWMaoYtfs = false;}
      if(ZRYgeFxNVa == true){ZRYgeFxNVa = false;}
      if(ZijqWgGlBC == true){ZijqWgGlBC = false;}
      if(COYjnZoGnP == true){COYjnZoGnP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSWBWEPFPY
{ 
  void fjIbppndrw()
  { 
      bool dJOSEFNncc = false;
      bool hBSTBgAKEr = false;
      bool dcDWcuxGAo = false;
      bool PVphXbAWSo = false;
      bool HLBeQZpDSA = false;
      bool SloRQAGrpI = false;
      bool HGnnMMLkuY = false;
      bool gcqPkRaYGC = false;
      bool FtnAVcfXQW = false;
      bool VHgKgAXNRD = false;
      bool OFHsSpuZgy = false;
      bool ZglmDNSmRj = false;
      bool fmTXDYwghj = false;
      bool sMHCnzmtgf = false;
      bool hFqRxoVsHT = false;
      bool gkwgXbkipt = false;
      bool sNrwEMZjzD = false;
      bool ZXFkCZuBaO = false;
      bool DDZNDIQZeM = false;
      bool NDEmmTNuNk = false;
      string ZEjEOCYQHR;
      string xJDMGBbAoH;
      string fTIxgijJhX;
      string kLmpgHQZim;
      string ADQlScjeIf;
      string yWRZyFwlWe;
      string ROhiglVNez;
      string kCRCGcDVdE;
      string yFBBYOsMqb;
      string LdCDVlUgEg;
      string HWzJtwEOTU;
      string BZISfLMgKS;
      string rIVDmHzNgT;
      string IWRwxbFrGc;
      string JesWZlVjXJ;
      string ZmVloyAwVm;
      string wphzMeILVE;
      string FTZgIMPzcB;
      string lOpWtUAeHy;
      string aJWTgSxtJu;
      if(ZEjEOCYQHR == HWzJtwEOTU){dJOSEFNncc = true;}
      else if(HWzJtwEOTU == ZEjEOCYQHR){OFHsSpuZgy = true;}
      if(xJDMGBbAoH == BZISfLMgKS){hBSTBgAKEr = true;}
      else if(BZISfLMgKS == xJDMGBbAoH){ZglmDNSmRj = true;}
      if(fTIxgijJhX == rIVDmHzNgT){dcDWcuxGAo = true;}
      else if(rIVDmHzNgT == fTIxgijJhX){fmTXDYwghj = true;}
      if(kLmpgHQZim == IWRwxbFrGc){PVphXbAWSo = true;}
      else if(IWRwxbFrGc == kLmpgHQZim){sMHCnzmtgf = true;}
      if(ADQlScjeIf == JesWZlVjXJ){HLBeQZpDSA = true;}
      else if(JesWZlVjXJ == ADQlScjeIf){hFqRxoVsHT = true;}
      if(yWRZyFwlWe == ZmVloyAwVm){SloRQAGrpI = true;}
      else if(ZmVloyAwVm == yWRZyFwlWe){gkwgXbkipt = true;}
      if(ROhiglVNez == wphzMeILVE){HGnnMMLkuY = true;}
      else if(wphzMeILVE == ROhiglVNez){sNrwEMZjzD = true;}
      if(kCRCGcDVdE == FTZgIMPzcB){gcqPkRaYGC = true;}
      if(yFBBYOsMqb == lOpWtUAeHy){FtnAVcfXQW = true;}
      if(LdCDVlUgEg == aJWTgSxtJu){VHgKgAXNRD = true;}
      while(FTZgIMPzcB == kCRCGcDVdE){ZXFkCZuBaO = true;}
      while(lOpWtUAeHy == lOpWtUAeHy){DDZNDIQZeM = true;}
      while(aJWTgSxtJu == aJWTgSxtJu){NDEmmTNuNk = true;}
      if(dJOSEFNncc == true){dJOSEFNncc = false;}
      if(hBSTBgAKEr == true){hBSTBgAKEr = false;}
      if(dcDWcuxGAo == true){dcDWcuxGAo = false;}
      if(PVphXbAWSo == true){PVphXbAWSo = false;}
      if(HLBeQZpDSA == true){HLBeQZpDSA = false;}
      if(SloRQAGrpI == true){SloRQAGrpI = false;}
      if(HGnnMMLkuY == true){HGnnMMLkuY = false;}
      if(gcqPkRaYGC == true){gcqPkRaYGC = false;}
      if(FtnAVcfXQW == true){FtnAVcfXQW = false;}
      if(VHgKgAXNRD == true){VHgKgAXNRD = false;}
      if(OFHsSpuZgy == true){OFHsSpuZgy = false;}
      if(ZglmDNSmRj == true){ZglmDNSmRj = false;}
      if(fmTXDYwghj == true){fmTXDYwghj = false;}
      if(sMHCnzmtgf == true){sMHCnzmtgf = false;}
      if(hFqRxoVsHT == true){hFqRxoVsHT = false;}
      if(gkwgXbkipt == true){gkwgXbkipt = false;}
      if(sNrwEMZjzD == true){sNrwEMZjzD = false;}
      if(ZXFkCZuBaO == true){ZXFkCZuBaO = false;}
      if(DDZNDIQZeM == true){DDZNDIQZeM = false;}
      if(NDEmmTNuNk == true){NDEmmTNuNk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XDMXYZVOPQ
{ 
  void xeCXFTMiiB()
  { 
      bool zswVcnIemw = false;
      bool CjcaFkOGtE = false;
      bool DjRfbswoRH = false;
      bool xpnYcrngZz = false;
      bool XFDRXmDqng = false;
      bool KdeZuPaPti = false;
      bool qSMeyLuEyM = false;
      bool wggtfygzIn = false;
      bool pFBkxTKNdN = false;
      bool QYlpIFrYSL = false;
      bool qzrajcxktw = false;
      bool haHFslQage = false;
      bool BgZkwXuplZ = false;
      bool GIgwxqMaAT = false;
      bool WYTgeoQgxV = false;
      bool oQqmJKYHeM = false;
      bool hGzTpZtKIC = false;
      bool YoaMIbNsFG = false;
      bool GNsPkoQsll = false;
      bool SEwnlPZzqE = false;
      string SizEjqCqKr;
      string LoSkHWSwXa;
      string psxeZApqpq;
      string nfjMAuQedJ;
      string xJGuispxQG;
      string uIaDoZlTei;
      string AKBSDeEFkL;
      string GmSNdflBwf;
      string KsaiufFgXZ;
      string JwAtJmImqD;
      string ojLFAHoMYI;
      string mjXyYHjRXX;
      string ZWhKBJmXEq;
      string XzJrqZgUim;
      string prHPmZYCUC;
      string CqPTdRCBDp;
      string URIhknZfGz;
      string ZOijggPSXb;
      string kjCCngjpNZ;
      string WfRsRYjZdz;
      if(SizEjqCqKr == ojLFAHoMYI){zswVcnIemw = true;}
      else if(ojLFAHoMYI == SizEjqCqKr){qzrajcxktw = true;}
      if(LoSkHWSwXa == mjXyYHjRXX){CjcaFkOGtE = true;}
      else if(mjXyYHjRXX == LoSkHWSwXa){haHFslQage = true;}
      if(psxeZApqpq == ZWhKBJmXEq){DjRfbswoRH = true;}
      else if(ZWhKBJmXEq == psxeZApqpq){BgZkwXuplZ = true;}
      if(nfjMAuQedJ == XzJrqZgUim){xpnYcrngZz = true;}
      else if(XzJrqZgUim == nfjMAuQedJ){GIgwxqMaAT = true;}
      if(xJGuispxQG == prHPmZYCUC){XFDRXmDqng = true;}
      else if(prHPmZYCUC == xJGuispxQG){WYTgeoQgxV = true;}
      if(uIaDoZlTei == CqPTdRCBDp){KdeZuPaPti = true;}
      else if(CqPTdRCBDp == uIaDoZlTei){oQqmJKYHeM = true;}
      if(AKBSDeEFkL == URIhknZfGz){qSMeyLuEyM = true;}
      else if(URIhknZfGz == AKBSDeEFkL){hGzTpZtKIC = true;}
      if(GmSNdflBwf == ZOijggPSXb){wggtfygzIn = true;}
      if(KsaiufFgXZ == kjCCngjpNZ){pFBkxTKNdN = true;}
      if(JwAtJmImqD == WfRsRYjZdz){QYlpIFrYSL = true;}
      while(ZOijggPSXb == GmSNdflBwf){YoaMIbNsFG = true;}
      while(kjCCngjpNZ == kjCCngjpNZ){GNsPkoQsll = true;}
      while(WfRsRYjZdz == WfRsRYjZdz){SEwnlPZzqE = true;}
      if(zswVcnIemw == true){zswVcnIemw = false;}
      if(CjcaFkOGtE == true){CjcaFkOGtE = false;}
      if(DjRfbswoRH == true){DjRfbswoRH = false;}
      if(xpnYcrngZz == true){xpnYcrngZz = false;}
      if(XFDRXmDqng == true){XFDRXmDqng = false;}
      if(KdeZuPaPti == true){KdeZuPaPti = false;}
      if(qSMeyLuEyM == true){qSMeyLuEyM = false;}
      if(wggtfygzIn == true){wggtfygzIn = false;}
      if(pFBkxTKNdN == true){pFBkxTKNdN = false;}
      if(QYlpIFrYSL == true){QYlpIFrYSL = false;}
      if(qzrajcxktw == true){qzrajcxktw = false;}
      if(haHFslQage == true){haHFslQage = false;}
      if(BgZkwXuplZ == true){BgZkwXuplZ = false;}
      if(GIgwxqMaAT == true){GIgwxqMaAT = false;}
      if(WYTgeoQgxV == true){WYTgeoQgxV = false;}
      if(oQqmJKYHeM == true){oQqmJKYHeM = false;}
      if(hGzTpZtKIC == true){hGzTpZtKIC = false;}
      if(YoaMIbNsFG == true){YoaMIbNsFG = false;}
      if(GNsPkoQsll == true){GNsPkoQsll = false;}
      if(SEwnlPZzqE == true){SEwnlPZzqE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLZOWDAEVS
{ 
  void LPndDJAqSl()
  { 
      bool zstJweKbqc = false;
      bool pkdDoWMgsf = false;
      bool TpOhopIfQG = false;
      bool BEHtWqucjb = false;
      bool jOGtfQMUto = false;
      bool mgDjVJeLUF = false;
      bool VeKjblcjfx = false;
      bool ajxQuEiTBX = false;
      bool dnkbTUAXYM = false;
      bool MiHdGFEWSt = false;
      bool ncnxNCilnQ = false;
      bool aKJwagshPG = false;
      bool kFKSjqbSJp = false;
      bool ALBHjBAnNR = false;
      bool kOiIlBZLDY = false;
      bool LVGLIhRUMV = false;
      bool ZQbxQOICLZ = false;
      bool gEUyVWWCgi = false;
      bool RQPjeeFpyB = false;
      bool iebqqUlkrX = false;
      string fdcfAVKODN;
      string kHDtngxnaI;
      string qbuaILizof;
      string UtrBIGiotB;
      string AXcwaEahRo;
      string HhuaOEiCWn;
      string lKYXrpPBlh;
      string xHtYHSzzAD;
      string kAgAXmyQlD;
      string XgSFPoyEDj;
      string oYwjqAnWTu;
      string EjBSDldYAF;
      string qyPhKQnnJS;
      string UuuPNLExJW;
      string zbxqynezBc;
      string LZExrqJNZZ;
      string LzNAaJnkFq;
      string ggOcGPAXiW;
      string kolfHtpyWW;
      string CpXiLzNwQo;
      if(fdcfAVKODN == oYwjqAnWTu){zstJweKbqc = true;}
      else if(oYwjqAnWTu == fdcfAVKODN){ncnxNCilnQ = true;}
      if(kHDtngxnaI == EjBSDldYAF){pkdDoWMgsf = true;}
      else if(EjBSDldYAF == kHDtngxnaI){aKJwagshPG = true;}
      if(qbuaILizof == qyPhKQnnJS){TpOhopIfQG = true;}
      else if(qyPhKQnnJS == qbuaILizof){kFKSjqbSJp = true;}
      if(UtrBIGiotB == UuuPNLExJW){BEHtWqucjb = true;}
      else if(UuuPNLExJW == UtrBIGiotB){ALBHjBAnNR = true;}
      if(AXcwaEahRo == zbxqynezBc){jOGtfQMUto = true;}
      else if(zbxqynezBc == AXcwaEahRo){kOiIlBZLDY = true;}
      if(HhuaOEiCWn == LZExrqJNZZ){mgDjVJeLUF = true;}
      else if(LZExrqJNZZ == HhuaOEiCWn){LVGLIhRUMV = true;}
      if(lKYXrpPBlh == LzNAaJnkFq){VeKjblcjfx = true;}
      else if(LzNAaJnkFq == lKYXrpPBlh){ZQbxQOICLZ = true;}
      if(xHtYHSzzAD == ggOcGPAXiW){ajxQuEiTBX = true;}
      if(kAgAXmyQlD == kolfHtpyWW){dnkbTUAXYM = true;}
      if(XgSFPoyEDj == CpXiLzNwQo){MiHdGFEWSt = true;}
      while(ggOcGPAXiW == xHtYHSzzAD){gEUyVWWCgi = true;}
      while(kolfHtpyWW == kolfHtpyWW){RQPjeeFpyB = true;}
      while(CpXiLzNwQo == CpXiLzNwQo){iebqqUlkrX = true;}
      if(zstJweKbqc == true){zstJweKbqc = false;}
      if(pkdDoWMgsf == true){pkdDoWMgsf = false;}
      if(TpOhopIfQG == true){TpOhopIfQG = false;}
      if(BEHtWqucjb == true){BEHtWqucjb = false;}
      if(jOGtfQMUto == true){jOGtfQMUto = false;}
      if(mgDjVJeLUF == true){mgDjVJeLUF = false;}
      if(VeKjblcjfx == true){VeKjblcjfx = false;}
      if(ajxQuEiTBX == true){ajxQuEiTBX = false;}
      if(dnkbTUAXYM == true){dnkbTUAXYM = false;}
      if(MiHdGFEWSt == true){MiHdGFEWSt = false;}
      if(ncnxNCilnQ == true){ncnxNCilnQ = false;}
      if(aKJwagshPG == true){aKJwagshPG = false;}
      if(kFKSjqbSJp == true){kFKSjqbSJp = false;}
      if(ALBHjBAnNR == true){ALBHjBAnNR = false;}
      if(kOiIlBZLDY == true){kOiIlBZLDY = false;}
      if(LVGLIhRUMV == true){LVGLIhRUMV = false;}
      if(ZQbxQOICLZ == true){ZQbxQOICLZ = false;}
      if(gEUyVWWCgi == true){gEUyVWWCgi = false;}
      if(RQPjeeFpyB == true){RQPjeeFpyB = false;}
      if(iebqqUlkrX == true){iebqqUlkrX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WACZQVAPHY
{ 
  void ugmIfxMQue()
  { 
      bool ZuzenMdirZ = false;
      bool bUZAVqQqcf = false;
      bool YcYFVMfdEo = false;
      bool IqkORyelMA = false;
      bool fzogLntmZJ = false;
      bool ZFcyYxWtIb = false;
      bool gzdDRjjLiW = false;
      bool LddbAYnqsh = false;
      bool RsEuODOlpU = false;
      bool bkdjTfUlPa = false;
      bool EiDCxuaAyA = false;
      bool IeAaJnuinO = false;
      bool VyVNuaAtIT = false;
      bool DBbRcioByT = false;
      bool bNmoLwjDZf = false;
      bool klyBFGNoHV = false;
      bool tgrdwGDhxa = false;
      bool yskTlHKfCy = false;
      bool pxTbiRDaMW = false;
      bool UztbYuUIrE = false;
      string epBBeVxrcq;
      string qIjLTrzjuF;
      string dHuYSqTwGg;
      string DxkcIsYeYN;
      string gaPOPobHuH;
      string OVuHFXubhn;
      string CAkwmsWHCZ;
      string TTLhYCqfId;
      string OMBzRhBdWk;
      string ywwjKfoSbW;
      string RUEUmtJNiC;
      string fOTEZozldE;
      string rsjRbWWbWr;
      string NXElLtHfLX;
      string YmuUFjcrKV;
      string fDoXdYjmrQ;
      string WhqpoHJgrf;
      string gTZFeExPMq;
      string teQAMJigHm;
      string JUmuBpwFex;
      if(epBBeVxrcq == RUEUmtJNiC){ZuzenMdirZ = true;}
      else if(RUEUmtJNiC == epBBeVxrcq){EiDCxuaAyA = true;}
      if(qIjLTrzjuF == fOTEZozldE){bUZAVqQqcf = true;}
      else if(fOTEZozldE == qIjLTrzjuF){IeAaJnuinO = true;}
      if(dHuYSqTwGg == rsjRbWWbWr){YcYFVMfdEo = true;}
      else if(rsjRbWWbWr == dHuYSqTwGg){VyVNuaAtIT = true;}
      if(DxkcIsYeYN == NXElLtHfLX){IqkORyelMA = true;}
      else if(NXElLtHfLX == DxkcIsYeYN){DBbRcioByT = true;}
      if(gaPOPobHuH == YmuUFjcrKV){fzogLntmZJ = true;}
      else if(YmuUFjcrKV == gaPOPobHuH){bNmoLwjDZf = true;}
      if(OVuHFXubhn == fDoXdYjmrQ){ZFcyYxWtIb = true;}
      else if(fDoXdYjmrQ == OVuHFXubhn){klyBFGNoHV = true;}
      if(CAkwmsWHCZ == WhqpoHJgrf){gzdDRjjLiW = true;}
      else if(WhqpoHJgrf == CAkwmsWHCZ){tgrdwGDhxa = true;}
      if(TTLhYCqfId == gTZFeExPMq){LddbAYnqsh = true;}
      if(OMBzRhBdWk == teQAMJigHm){RsEuODOlpU = true;}
      if(ywwjKfoSbW == JUmuBpwFex){bkdjTfUlPa = true;}
      while(gTZFeExPMq == TTLhYCqfId){yskTlHKfCy = true;}
      while(teQAMJigHm == teQAMJigHm){pxTbiRDaMW = true;}
      while(JUmuBpwFex == JUmuBpwFex){UztbYuUIrE = true;}
      if(ZuzenMdirZ == true){ZuzenMdirZ = false;}
      if(bUZAVqQqcf == true){bUZAVqQqcf = false;}
      if(YcYFVMfdEo == true){YcYFVMfdEo = false;}
      if(IqkORyelMA == true){IqkORyelMA = false;}
      if(fzogLntmZJ == true){fzogLntmZJ = false;}
      if(ZFcyYxWtIb == true){ZFcyYxWtIb = false;}
      if(gzdDRjjLiW == true){gzdDRjjLiW = false;}
      if(LddbAYnqsh == true){LddbAYnqsh = false;}
      if(RsEuODOlpU == true){RsEuODOlpU = false;}
      if(bkdjTfUlPa == true){bkdjTfUlPa = false;}
      if(EiDCxuaAyA == true){EiDCxuaAyA = false;}
      if(IeAaJnuinO == true){IeAaJnuinO = false;}
      if(VyVNuaAtIT == true){VyVNuaAtIT = false;}
      if(DBbRcioByT == true){DBbRcioByT = false;}
      if(bNmoLwjDZf == true){bNmoLwjDZf = false;}
      if(klyBFGNoHV == true){klyBFGNoHV = false;}
      if(tgrdwGDhxa == true){tgrdwGDhxa = false;}
      if(yskTlHKfCy == true){yskTlHKfCy = false;}
      if(pxTbiRDaMW == true){pxTbiRDaMW = false;}
      if(UztbYuUIrE == true){UztbYuUIrE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMFDKGKEKT
{ 
  void WzMtawcnrp()
  { 
      bool zKbnMukyci = false;
      bool QghIqoJiND = false;
      bool ymBTYTcjfb = false;
      bool JMQaxODQLd = false;
      bool SKbkdMWmJQ = false;
      bool WjmUeMJIOs = false;
      bool SASBZEPGKb = false;
      bool lrWjjmLPoM = false;
      bool xpaOEYZwwk = false;
      bool EuBSLRraLZ = false;
      bool xPbgeeNDjq = false;
      bool BtSCwbZDwA = false;
      bool dSKZXppDYS = false;
      bool tjDPOgOtiZ = false;
      bool LWMFjJcyWi = false;
      bool roeKudFBIo = false;
      bool nJdRwQqCnO = false;
      bool NeTVoHGFoN = false;
      bool NqgpZFFrTj = false;
      bool bMktlBrtIT = false;
      string bNHLZMmmGg;
      string bJXMOVjpEE;
      string IfwJNhaOyU;
      string Fclpitgfjo;
      string RLkPNFYGQL;
      string yhhRdwQyyr;
      string lYnkayWhcT;
      string oEFOlwtfuI;
      string IUymVXtTMm;
      string cigrDsWAoP;
      string hqcwWsbTfg;
      string BjCojQZBOD;
      string DCUppGXNLr;
      string ZtqfaQrBQc;
      string uaneksgqHl;
      string TVklLeWmGQ;
      string VOHmHHsVOT;
      string YXjlIbNoEx;
      string YfFYYDJFUu;
      string tFuAGfSBXc;
      if(bNHLZMmmGg == hqcwWsbTfg){zKbnMukyci = true;}
      else if(hqcwWsbTfg == bNHLZMmmGg){xPbgeeNDjq = true;}
      if(bJXMOVjpEE == BjCojQZBOD){QghIqoJiND = true;}
      else if(BjCojQZBOD == bJXMOVjpEE){BtSCwbZDwA = true;}
      if(IfwJNhaOyU == DCUppGXNLr){ymBTYTcjfb = true;}
      else if(DCUppGXNLr == IfwJNhaOyU){dSKZXppDYS = true;}
      if(Fclpitgfjo == ZtqfaQrBQc){JMQaxODQLd = true;}
      else if(ZtqfaQrBQc == Fclpitgfjo){tjDPOgOtiZ = true;}
      if(RLkPNFYGQL == uaneksgqHl){SKbkdMWmJQ = true;}
      else if(uaneksgqHl == RLkPNFYGQL){LWMFjJcyWi = true;}
      if(yhhRdwQyyr == TVklLeWmGQ){WjmUeMJIOs = true;}
      else if(TVklLeWmGQ == yhhRdwQyyr){roeKudFBIo = true;}
      if(lYnkayWhcT == VOHmHHsVOT){SASBZEPGKb = true;}
      else if(VOHmHHsVOT == lYnkayWhcT){nJdRwQqCnO = true;}
      if(oEFOlwtfuI == YXjlIbNoEx){lrWjjmLPoM = true;}
      if(IUymVXtTMm == YfFYYDJFUu){xpaOEYZwwk = true;}
      if(cigrDsWAoP == tFuAGfSBXc){EuBSLRraLZ = true;}
      while(YXjlIbNoEx == oEFOlwtfuI){NeTVoHGFoN = true;}
      while(YfFYYDJFUu == YfFYYDJFUu){NqgpZFFrTj = true;}
      while(tFuAGfSBXc == tFuAGfSBXc){bMktlBrtIT = true;}
      if(zKbnMukyci == true){zKbnMukyci = false;}
      if(QghIqoJiND == true){QghIqoJiND = false;}
      if(ymBTYTcjfb == true){ymBTYTcjfb = false;}
      if(JMQaxODQLd == true){JMQaxODQLd = false;}
      if(SKbkdMWmJQ == true){SKbkdMWmJQ = false;}
      if(WjmUeMJIOs == true){WjmUeMJIOs = false;}
      if(SASBZEPGKb == true){SASBZEPGKb = false;}
      if(lrWjjmLPoM == true){lrWjjmLPoM = false;}
      if(xpaOEYZwwk == true){xpaOEYZwwk = false;}
      if(EuBSLRraLZ == true){EuBSLRraLZ = false;}
      if(xPbgeeNDjq == true){xPbgeeNDjq = false;}
      if(BtSCwbZDwA == true){BtSCwbZDwA = false;}
      if(dSKZXppDYS == true){dSKZXppDYS = false;}
      if(tjDPOgOtiZ == true){tjDPOgOtiZ = false;}
      if(LWMFjJcyWi == true){LWMFjJcyWi = false;}
      if(roeKudFBIo == true){roeKudFBIo = false;}
      if(nJdRwQqCnO == true){nJdRwQqCnO = false;}
      if(NeTVoHGFoN == true){NeTVoHGFoN = false;}
      if(NqgpZFFrTj == true){NqgpZFFrTj = false;}
      if(bMktlBrtIT == true){bMktlBrtIT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMTXZPFCVF
{ 
  void xmMiCZsqSY()
  { 
      bool EeIMVugmCd = false;
      bool dqtVVNAibk = false;
      bool qxWsWtBmMh = false;
      bool HVegjTaXzy = false;
      bool fKHPLjFCJL = false;
      bool QQEloGHPpb = false;
      bool ssaUWIMNlC = false;
      bool lcjcFgpHgl = false;
      bool nzdAQpRsrc = false;
      bool LLgXFljlsD = false;
      bool XrQGZngbgI = false;
      bool QAhEmtPZEf = false;
      bool pSUIqZuLXS = false;
      bool wENdNwiWab = false;
      bool JoMjMKdckL = false;
      bool WJgNMEXHPz = false;
      bool sUDOLLlEpp = false;
      bool LrzbVBGjuf = false;
      bool wSaMulWARJ = false;
      bool YaGainlxYA = false;
      string LwcFXVhJwi;
      string JIeXyUnShX;
      string irKwnOPhYr;
      string uxQYDRcOpZ;
      string dDlsNdYNoI;
      string xKzdqTlgQJ;
      string FAjDmMrGUf;
      string rYbHsfFRhJ;
      string oCrQukxmgj;
      string fwyfUdShFB;
      string lSsJQXhrkL;
      string NTyGUDISIC;
      string OEYjzuawlO;
      string MXMgXVIhAW;
      string DFCVWLxqLQ;
      string VzYCmgtIJU;
      string xkFVypHRiy;
      string tZSlzICCNn;
      string yikVsMyJtp;
      string bAXeZRAfXf;
      if(LwcFXVhJwi == lSsJQXhrkL){EeIMVugmCd = true;}
      else if(lSsJQXhrkL == LwcFXVhJwi){XrQGZngbgI = true;}
      if(JIeXyUnShX == NTyGUDISIC){dqtVVNAibk = true;}
      else if(NTyGUDISIC == JIeXyUnShX){QAhEmtPZEf = true;}
      if(irKwnOPhYr == OEYjzuawlO){qxWsWtBmMh = true;}
      else if(OEYjzuawlO == irKwnOPhYr){pSUIqZuLXS = true;}
      if(uxQYDRcOpZ == MXMgXVIhAW){HVegjTaXzy = true;}
      else if(MXMgXVIhAW == uxQYDRcOpZ){wENdNwiWab = true;}
      if(dDlsNdYNoI == DFCVWLxqLQ){fKHPLjFCJL = true;}
      else if(DFCVWLxqLQ == dDlsNdYNoI){JoMjMKdckL = true;}
      if(xKzdqTlgQJ == VzYCmgtIJU){QQEloGHPpb = true;}
      else if(VzYCmgtIJU == xKzdqTlgQJ){WJgNMEXHPz = true;}
      if(FAjDmMrGUf == xkFVypHRiy){ssaUWIMNlC = true;}
      else if(xkFVypHRiy == FAjDmMrGUf){sUDOLLlEpp = true;}
      if(rYbHsfFRhJ == tZSlzICCNn){lcjcFgpHgl = true;}
      if(oCrQukxmgj == yikVsMyJtp){nzdAQpRsrc = true;}
      if(fwyfUdShFB == bAXeZRAfXf){LLgXFljlsD = true;}
      while(tZSlzICCNn == rYbHsfFRhJ){LrzbVBGjuf = true;}
      while(yikVsMyJtp == yikVsMyJtp){wSaMulWARJ = true;}
      while(bAXeZRAfXf == bAXeZRAfXf){YaGainlxYA = true;}
      if(EeIMVugmCd == true){EeIMVugmCd = false;}
      if(dqtVVNAibk == true){dqtVVNAibk = false;}
      if(qxWsWtBmMh == true){qxWsWtBmMh = false;}
      if(HVegjTaXzy == true){HVegjTaXzy = false;}
      if(fKHPLjFCJL == true){fKHPLjFCJL = false;}
      if(QQEloGHPpb == true){QQEloGHPpb = false;}
      if(ssaUWIMNlC == true){ssaUWIMNlC = false;}
      if(lcjcFgpHgl == true){lcjcFgpHgl = false;}
      if(nzdAQpRsrc == true){nzdAQpRsrc = false;}
      if(LLgXFljlsD == true){LLgXFljlsD = false;}
      if(XrQGZngbgI == true){XrQGZngbgI = false;}
      if(QAhEmtPZEf == true){QAhEmtPZEf = false;}
      if(pSUIqZuLXS == true){pSUIqZuLXS = false;}
      if(wENdNwiWab == true){wENdNwiWab = false;}
      if(JoMjMKdckL == true){JoMjMKdckL = false;}
      if(WJgNMEXHPz == true){WJgNMEXHPz = false;}
      if(sUDOLLlEpp == true){sUDOLLlEpp = false;}
      if(LrzbVBGjuf == true){LrzbVBGjuf = false;}
      if(wSaMulWARJ == true){wSaMulWARJ = false;}
      if(YaGainlxYA == true){YaGainlxYA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWNEQWGFPY
{ 
  void lApuZxXKYH()
  { 
      bool zWTVDaDkHN = false;
      bool JMWyrhAHfM = false;
      bool lGddxnGhtz = false;
      bool CFauUeaiau = false;
      bool MiBjOeEmRK = false;
      bool VQmCpsroXO = false;
      bool UUpHKEladM = false;
      bool GRgjzCEtPS = false;
      bool jSQjdlRXEa = false;
      bool mkKLaqrsYJ = false;
      bool rcJEDEiDCn = false;
      bool nxZFeBEGdX = false;
      bool mNWCYUGVJI = false;
      bool JLUGaHJLfY = false;
      bool CNVQmoLFfY = false;
      bool mlPBVdGGei = false;
      bool yNttdcbTdX = false;
      bool qsZEUYqFPj = false;
      bool IAojVWuTjw = false;
      bool ADfxaoTblJ = false;
      string FGuTgZMEoY;
      string LZeAiAcMNb;
      string ofnUXVRIIO;
      string cePTIimcDM;
      string UmGYHmtsCI;
      string xekAoYRauK;
      string IDwZwfJLqA;
      string MAIBHBYPMk;
      string bXGzRxtOej;
      string QMhsDQqfca;
      string ciCBuwVism;
      string ACNKhkxwIy;
      string ltgHiASPxp;
      string KsmlHsVEEV;
      string bKVqjOyWKS;
      string TtXdoiCtSt;
      string cFlCcGPbCo;
      string PrqlVaYoXT;
      string CuEdWPUIxY;
      string qalJrWXTOc;
      if(FGuTgZMEoY == ciCBuwVism){zWTVDaDkHN = true;}
      else if(ciCBuwVism == FGuTgZMEoY){rcJEDEiDCn = true;}
      if(LZeAiAcMNb == ACNKhkxwIy){JMWyrhAHfM = true;}
      else if(ACNKhkxwIy == LZeAiAcMNb){nxZFeBEGdX = true;}
      if(ofnUXVRIIO == ltgHiASPxp){lGddxnGhtz = true;}
      else if(ltgHiASPxp == ofnUXVRIIO){mNWCYUGVJI = true;}
      if(cePTIimcDM == KsmlHsVEEV){CFauUeaiau = true;}
      else if(KsmlHsVEEV == cePTIimcDM){JLUGaHJLfY = true;}
      if(UmGYHmtsCI == bKVqjOyWKS){MiBjOeEmRK = true;}
      else if(bKVqjOyWKS == UmGYHmtsCI){CNVQmoLFfY = true;}
      if(xekAoYRauK == TtXdoiCtSt){VQmCpsroXO = true;}
      else if(TtXdoiCtSt == xekAoYRauK){mlPBVdGGei = true;}
      if(IDwZwfJLqA == cFlCcGPbCo){UUpHKEladM = true;}
      else if(cFlCcGPbCo == IDwZwfJLqA){yNttdcbTdX = true;}
      if(MAIBHBYPMk == PrqlVaYoXT){GRgjzCEtPS = true;}
      if(bXGzRxtOej == CuEdWPUIxY){jSQjdlRXEa = true;}
      if(QMhsDQqfca == qalJrWXTOc){mkKLaqrsYJ = true;}
      while(PrqlVaYoXT == MAIBHBYPMk){qsZEUYqFPj = true;}
      while(CuEdWPUIxY == CuEdWPUIxY){IAojVWuTjw = true;}
      while(qalJrWXTOc == qalJrWXTOc){ADfxaoTblJ = true;}
      if(zWTVDaDkHN == true){zWTVDaDkHN = false;}
      if(JMWyrhAHfM == true){JMWyrhAHfM = false;}
      if(lGddxnGhtz == true){lGddxnGhtz = false;}
      if(CFauUeaiau == true){CFauUeaiau = false;}
      if(MiBjOeEmRK == true){MiBjOeEmRK = false;}
      if(VQmCpsroXO == true){VQmCpsroXO = false;}
      if(UUpHKEladM == true){UUpHKEladM = false;}
      if(GRgjzCEtPS == true){GRgjzCEtPS = false;}
      if(jSQjdlRXEa == true){jSQjdlRXEa = false;}
      if(mkKLaqrsYJ == true){mkKLaqrsYJ = false;}
      if(rcJEDEiDCn == true){rcJEDEiDCn = false;}
      if(nxZFeBEGdX == true){nxZFeBEGdX = false;}
      if(mNWCYUGVJI == true){mNWCYUGVJI = false;}
      if(JLUGaHJLfY == true){JLUGaHJLfY = false;}
      if(CNVQmoLFfY == true){CNVQmoLFfY = false;}
      if(mlPBVdGGei == true){mlPBVdGGei = false;}
      if(yNttdcbTdX == true){yNttdcbTdX = false;}
      if(qsZEUYqFPj == true){qsZEUYqFPj = false;}
      if(IAojVWuTjw == true){IAojVWuTjw = false;}
      if(ADfxaoTblJ == true){ADfxaoTblJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CNUVQSXPSR
{ 
  void RuFtsGggDN()
  { 
      bool sqfJyWaJPC = false;
      bool plcHpuqAsD = false;
      bool oiiyriWTct = false;
      bool BTKIDPsjUq = false;
      bool GbrJwmBHhs = false;
      bool knBRIJIgQO = false;
      bool AHfUBWbUEZ = false;
      bool BHfCwMpYBF = false;
      bool gPljJMRszs = false;
      bool HLSFpzwWIZ = false;
      bool LgCHrcIzUu = false;
      bool TifLgkVwLn = false;
      bool EhULSooZLx = false;
      bool QSQatAMdqf = false;
      bool ERXEYXfGXF = false;
      bool cALUUcLqoC = false;
      bool nhmXeASERf = false;
      bool YqEfilKPlt = false;
      bool JhBGTQHuFQ = false;
      bool oVooqVeAZY = false;
      string SwkRrRJXHc;
      string XpxzlSNAAG;
      string yPpodiTzrL;
      string bUsQMejfti;
      string WNzXtRkwsb;
      string rKOMXDFwmI;
      string xKeuBDxflG;
      string ihGQijPRuL;
      string yWFPTRFfsJ;
      string YnrllMiDWp;
      string UFKlsKExdm;
      string mmAbKZEObi;
      string xQlbhuoTeV;
      string BMuEqrMSWJ;
      string MHCGWkmQaL;
      string ITbmrEShEy;
      string UjSHkZrukR;
      string NkrSWpOfFw;
      string HYsSNhkIMl;
      string ZdOYobnuUx;
      if(SwkRrRJXHc == UFKlsKExdm){sqfJyWaJPC = true;}
      else if(UFKlsKExdm == SwkRrRJXHc){LgCHrcIzUu = true;}
      if(XpxzlSNAAG == mmAbKZEObi){plcHpuqAsD = true;}
      else if(mmAbKZEObi == XpxzlSNAAG){TifLgkVwLn = true;}
      if(yPpodiTzrL == xQlbhuoTeV){oiiyriWTct = true;}
      else if(xQlbhuoTeV == yPpodiTzrL){EhULSooZLx = true;}
      if(bUsQMejfti == BMuEqrMSWJ){BTKIDPsjUq = true;}
      else if(BMuEqrMSWJ == bUsQMejfti){QSQatAMdqf = true;}
      if(WNzXtRkwsb == MHCGWkmQaL){GbrJwmBHhs = true;}
      else if(MHCGWkmQaL == WNzXtRkwsb){ERXEYXfGXF = true;}
      if(rKOMXDFwmI == ITbmrEShEy){knBRIJIgQO = true;}
      else if(ITbmrEShEy == rKOMXDFwmI){cALUUcLqoC = true;}
      if(xKeuBDxflG == UjSHkZrukR){AHfUBWbUEZ = true;}
      else if(UjSHkZrukR == xKeuBDxflG){nhmXeASERf = true;}
      if(ihGQijPRuL == NkrSWpOfFw){BHfCwMpYBF = true;}
      if(yWFPTRFfsJ == HYsSNhkIMl){gPljJMRszs = true;}
      if(YnrllMiDWp == ZdOYobnuUx){HLSFpzwWIZ = true;}
      while(NkrSWpOfFw == ihGQijPRuL){YqEfilKPlt = true;}
      while(HYsSNhkIMl == HYsSNhkIMl){JhBGTQHuFQ = true;}
      while(ZdOYobnuUx == ZdOYobnuUx){oVooqVeAZY = true;}
      if(sqfJyWaJPC == true){sqfJyWaJPC = false;}
      if(plcHpuqAsD == true){plcHpuqAsD = false;}
      if(oiiyriWTct == true){oiiyriWTct = false;}
      if(BTKIDPsjUq == true){BTKIDPsjUq = false;}
      if(GbrJwmBHhs == true){GbrJwmBHhs = false;}
      if(knBRIJIgQO == true){knBRIJIgQO = false;}
      if(AHfUBWbUEZ == true){AHfUBWbUEZ = false;}
      if(BHfCwMpYBF == true){BHfCwMpYBF = false;}
      if(gPljJMRszs == true){gPljJMRszs = false;}
      if(HLSFpzwWIZ == true){HLSFpzwWIZ = false;}
      if(LgCHrcIzUu == true){LgCHrcIzUu = false;}
      if(TifLgkVwLn == true){TifLgkVwLn = false;}
      if(EhULSooZLx == true){EhULSooZLx = false;}
      if(QSQatAMdqf == true){QSQatAMdqf = false;}
      if(ERXEYXfGXF == true){ERXEYXfGXF = false;}
      if(cALUUcLqoC == true){cALUUcLqoC = false;}
      if(nhmXeASERf == true){nhmXeASERf = false;}
      if(YqEfilKPlt == true){YqEfilKPlt = false;}
      if(JhBGTQHuFQ == true){JhBGTQHuFQ = false;}
      if(oVooqVeAZY == true){oVooqVeAZY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DQMGMLIUZQ
{ 
  void PoxtoHHAfI()
  { 
      bool DasxJSylRo = false;
      bool KqRtrRNbEJ = false;
      bool oDRlMfNJCH = false;
      bool BQOLGphYdY = false;
      bool iBllwCUdgf = false;
      bool hUBfiAJHjc = false;
      bool EnjJmtbFnB = false;
      bool inyeZmQfpK = false;
      bool LjcWZgOicG = false;
      bool gaoATuRczB = false;
      bool ZOpewsVWFu = false;
      bool idRZRULNjF = false;
      bool fschTIzyKe = false;
      bool VmfnjwtxZg = false;
      bool LrcgWDJOhz = false;
      bool jErsVflIKn = false;
      bool sXLaZuxcpV = false;
      bool ZNmDtnQwKQ = false;
      bool ykPKuQumSD = false;
      bool KlllmnfCGa = false;
      string BVkMoDtjwG;
      string cdgVMMsnWt;
      string GlLPdYRhoA;
      string dYGHYBxFOW;
      string escgCfEliK;
      string xkfJTPKUhP;
      string lMuwbDWYwL;
      string OmZAPMIdNy;
      string UeydCrrxnJ;
      string qbXzjSygEy;
      string IfoXwJLfsG;
      string GfHjuHNQsj;
      string LZkmTlPaPx;
      string ObYOpnoahr;
      string gMDgCKUmDb;
      string EgmUmhtCDJ;
      string tkPwqdHstG;
      string SlhADyWDjJ;
      string RbWmrhnEaH;
      string slXYyuwGoY;
      if(BVkMoDtjwG == IfoXwJLfsG){DasxJSylRo = true;}
      else if(IfoXwJLfsG == BVkMoDtjwG){ZOpewsVWFu = true;}
      if(cdgVMMsnWt == GfHjuHNQsj){KqRtrRNbEJ = true;}
      else if(GfHjuHNQsj == cdgVMMsnWt){idRZRULNjF = true;}
      if(GlLPdYRhoA == LZkmTlPaPx){oDRlMfNJCH = true;}
      else if(LZkmTlPaPx == GlLPdYRhoA){fschTIzyKe = true;}
      if(dYGHYBxFOW == ObYOpnoahr){BQOLGphYdY = true;}
      else if(ObYOpnoahr == dYGHYBxFOW){VmfnjwtxZg = true;}
      if(escgCfEliK == gMDgCKUmDb){iBllwCUdgf = true;}
      else if(gMDgCKUmDb == escgCfEliK){LrcgWDJOhz = true;}
      if(xkfJTPKUhP == EgmUmhtCDJ){hUBfiAJHjc = true;}
      else if(EgmUmhtCDJ == xkfJTPKUhP){jErsVflIKn = true;}
      if(lMuwbDWYwL == tkPwqdHstG){EnjJmtbFnB = true;}
      else if(tkPwqdHstG == lMuwbDWYwL){sXLaZuxcpV = true;}
      if(OmZAPMIdNy == SlhADyWDjJ){inyeZmQfpK = true;}
      if(UeydCrrxnJ == RbWmrhnEaH){LjcWZgOicG = true;}
      if(qbXzjSygEy == slXYyuwGoY){gaoATuRczB = true;}
      while(SlhADyWDjJ == OmZAPMIdNy){ZNmDtnQwKQ = true;}
      while(RbWmrhnEaH == RbWmrhnEaH){ykPKuQumSD = true;}
      while(slXYyuwGoY == slXYyuwGoY){KlllmnfCGa = true;}
      if(DasxJSylRo == true){DasxJSylRo = false;}
      if(KqRtrRNbEJ == true){KqRtrRNbEJ = false;}
      if(oDRlMfNJCH == true){oDRlMfNJCH = false;}
      if(BQOLGphYdY == true){BQOLGphYdY = false;}
      if(iBllwCUdgf == true){iBllwCUdgf = false;}
      if(hUBfiAJHjc == true){hUBfiAJHjc = false;}
      if(EnjJmtbFnB == true){EnjJmtbFnB = false;}
      if(inyeZmQfpK == true){inyeZmQfpK = false;}
      if(LjcWZgOicG == true){LjcWZgOicG = false;}
      if(gaoATuRczB == true){gaoATuRczB = false;}
      if(ZOpewsVWFu == true){ZOpewsVWFu = false;}
      if(idRZRULNjF == true){idRZRULNjF = false;}
      if(fschTIzyKe == true){fschTIzyKe = false;}
      if(VmfnjwtxZg == true){VmfnjwtxZg = false;}
      if(LrcgWDJOhz == true){LrcgWDJOhz = false;}
      if(jErsVflIKn == true){jErsVflIKn = false;}
      if(sXLaZuxcpV == true){sXLaZuxcpV = false;}
      if(ZNmDtnQwKQ == true){ZNmDtnQwKQ = false;}
      if(ykPKuQumSD == true){ykPKuQumSD = false;}
      if(KlllmnfCGa == true){KlllmnfCGa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEHPAFWQLJ
{ 
  void GTqrteffqa()
  { 
      bool pwTTFNJWlS = false;
      bool MjTHRZQLDo = false;
      bool PFuBxbrHXt = false;
      bool MOPRUDVzCP = false;
      bool KfCcPWedHc = false;
      bool kVVHjjBSVd = false;
      bool VBzrGxUCmN = false;
      bool EQJmeiDSka = false;
      bool xNAtIqsHhk = false;
      bool CDdXsIgKWR = false;
      bool BbqtYULhcB = false;
      bool fhgtgHBEiP = false;
      bool EMUCKAlktV = false;
      bool BruSYUWFUn = false;
      bool eLegETWiql = false;
      bool GcbHNnHniY = false;
      bool hanGzmmNUL = false;
      bool jwitjshmxq = false;
      bool dDtHPXQnFk = false;
      bool MhWwGEWXgQ = false;
      string azopLNiKdL;
      string uMZeBjRkjf;
      string THxYPhyekM;
      string PsKcGEFcLG;
      string gpLKJtMsLl;
      string qBkCzSCQad;
      string PDYQuCBwXx;
      string dnZdzcwlPU;
      string UFTzVNHIcn;
      string BoChpcQtPG;
      string sQUOHCbHDV;
      string VQAFJKjYuh;
      string tsTjuolrnV;
      string MCVIbEjFrT;
      string lAFGSjnwYf;
      string rqyhMzxkSR;
      string PjSgJStqcE;
      string ZegbusmMQK;
      string AoTHcUDnwb;
      string HylZDBgYwz;
      if(azopLNiKdL == sQUOHCbHDV){pwTTFNJWlS = true;}
      else if(sQUOHCbHDV == azopLNiKdL){BbqtYULhcB = true;}
      if(uMZeBjRkjf == VQAFJKjYuh){MjTHRZQLDo = true;}
      else if(VQAFJKjYuh == uMZeBjRkjf){fhgtgHBEiP = true;}
      if(THxYPhyekM == tsTjuolrnV){PFuBxbrHXt = true;}
      else if(tsTjuolrnV == THxYPhyekM){EMUCKAlktV = true;}
      if(PsKcGEFcLG == MCVIbEjFrT){MOPRUDVzCP = true;}
      else if(MCVIbEjFrT == PsKcGEFcLG){BruSYUWFUn = true;}
      if(gpLKJtMsLl == lAFGSjnwYf){KfCcPWedHc = true;}
      else if(lAFGSjnwYf == gpLKJtMsLl){eLegETWiql = true;}
      if(qBkCzSCQad == rqyhMzxkSR){kVVHjjBSVd = true;}
      else if(rqyhMzxkSR == qBkCzSCQad){GcbHNnHniY = true;}
      if(PDYQuCBwXx == PjSgJStqcE){VBzrGxUCmN = true;}
      else if(PjSgJStqcE == PDYQuCBwXx){hanGzmmNUL = true;}
      if(dnZdzcwlPU == ZegbusmMQK){EQJmeiDSka = true;}
      if(UFTzVNHIcn == AoTHcUDnwb){xNAtIqsHhk = true;}
      if(BoChpcQtPG == HylZDBgYwz){CDdXsIgKWR = true;}
      while(ZegbusmMQK == dnZdzcwlPU){jwitjshmxq = true;}
      while(AoTHcUDnwb == AoTHcUDnwb){dDtHPXQnFk = true;}
      while(HylZDBgYwz == HylZDBgYwz){MhWwGEWXgQ = true;}
      if(pwTTFNJWlS == true){pwTTFNJWlS = false;}
      if(MjTHRZQLDo == true){MjTHRZQLDo = false;}
      if(PFuBxbrHXt == true){PFuBxbrHXt = false;}
      if(MOPRUDVzCP == true){MOPRUDVzCP = false;}
      if(KfCcPWedHc == true){KfCcPWedHc = false;}
      if(kVVHjjBSVd == true){kVVHjjBSVd = false;}
      if(VBzrGxUCmN == true){VBzrGxUCmN = false;}
      if(EQJmeiDSka == true){EQJmeiDSka = false;}
      if(xNAtIqsHhk == true){xNAtIqsHhk = false;}
      if(CDdXsIgKWR == true){CDdXsIgKWR = false;}
      if(BbqtYULhcB == true){BbqtYULhcB = false;}
      if(fhgtgHBEiP == true){fhgtgHBEiP = false;}
      if(EMUCKAlktV == true){EMUCKAlktV = false;}
      if(BruSYUWFUn == true){BruSYUWFUn = false;}
      if(eLegETWiql == true){eLegETWiql = false;}
      if(GcbHNnHniY == true){GcbHNnHniY = false;}
      if(hanGzmmNUL == true){hanGzmmNUL = false;}
      if(jwitjshmxq == true){jwitjshmxq = false;}
      if(dDtHPXQnFk == true){dDtHPXQnFk = false;}
      if(MhWwGEWXgQ == true){MhWwGEWXgQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCSYWBPOTE
{ 
  void cfNaziccmP()
  { 
      bool hEfEtYRdmo = false;
      bool CQdcEqCjRc = false;
      bool qrwWjQekCZ = false;
      bool gsQIqqCQCk = false;
      bool eHjpLSiwMk = false;
      bool HCJwnoHJUd = false;
      bool tgbMHJzUkM = false;
      bool okggxjIFKQ = false;
      bool giXQReiTUC = false;
      bool iswXqxeWiC = false;
      bool SOKAwVUcyD = false;
      bool gCyDxKIKtc = false;
      bool ZfzicuoJoA = false;
      bool EkWIxRXXUu = false;
      bool JFVQVgtraf = false;
      bool nUbFbmOaWA = false;
      bool fLmyzuepFe = false;
      bool mkpyTTJiNu = false;
      bool AxhJLjIRfK = false;
      bool DwBUPySWQZ = false;
      string xwpWDuwRyK;
      string iUMXrfbCqp;
      string EmxmTJpMDn;
      string radhrJCpbm;
      string sBBJDlYtJH;
      string LrFLsKzCDt;
      string EiOKSHpdei;
      string dlaDwDlmjg;
      string kuCuczURoh;
      string KzlghJlpqu;
      string uuPadZRCOp;
      string YMRVJJfShS;
      string lXnxXdzsVm;
      string QuuokpfbQC;
      string hSDyIyhQXY;
      string cTIXIWGRCA;
      string ZXfbZdQcjT;
      string dEBekTUonZ;
      string wiVwJwlXfN;
      string iNYQcKlbYe;
      if(xwpWDuwRyK == uuPadZRCOp){hEfEtYRdmo = true;}
      else if(uuPadZRCOp == xwpWDuwRyK){SOKAwVUcyD = true;}
      if(iUMXrfbCqp == YMRVJJfShS){CQdcEqCjRc = true;}
      else if(YMRVJJfShS == iUMXrfbCqp){gCyDxKIKtc = true;}
      if(EmxmTJpMDn == lXnxXdzsVm){qrwWjQekCZ = true;}
      else if(lXnxXdzsVm == EmxmTJpMDn){ZfzicuoJoA = true;}
      if(radhrJCpbm == QuuokpfbQC){gsQIqqCQCk = true;}
      else if(QuuokpfbQC == radhrJCpbm){EkWIxRXXUu = true;}
      if(sBBJDlYtJH == hSDyIyhQXY){eHjpLSiwMk = true;}
      else if(hSDyIyhQXY == sBBJDlYtJH){JFVQVgtraf = true;}
      if(LrFLsKzCDt == cTIXIWGRCA){HCJwnoHJUd = true;}
      else if(cTIXIWGRCA == LrFLsKzCDt){nUbFbmOaWA = true;}
      if(EiOKSHpdei == ZXfbZdQcjT){tgbMHJzUkM = true;}
      else if(ZXfbZdQcjT == EiOKSHpdei){fLmyzuepFe = true;}
      if(dlaDwDlmjg == dEBekTUonZ){okggxjIFKQ = true;}
      if(kuCuczURoh == wiVwJwlXfN){giXQReiTUC = true;}
      if(KzlghJlpqu == iNYQcKlbYe){iswXqxeWiC = true;}
      while(dEBekTUonZ == dlaDwDlmjg){mkpyTTJiNu = true;}
      while(wiVwJwlXfN == wiVwJwlXfN){AxhJLjIRfK = true;}
      while(iNYQcKlbYe == iNYQcKlbYe){DwBUPySWQZ = true;}
      if(hEfEtYRdmo == true){hEfEtYRdmo = false;}
      if(CQdcEqCjRc == true){CQdcEqCjRc = false;}
      if(qrwWjQekCZ == true){qrwWjQekCZ = false;}
      if(gsQIqqCQCk == true){gsQIqqCQCk = false;}
      if(eHjpLSiwMk == true){eHjpLSiwMk = false;}
      if(HCJwnoHJUd == true){HCJwnoHJUd = false;}
      if(tgbMHJzUkM == true){tgbMHJzUkM = false;}
      if(okggxjIFKQ == true){okggxjIFKQ = false;}
      if(giXQReiTUC == true){giXQReiTUC = false;}
      if(iswXqxeWiC == true){iswXqxeWiC = false;}
      if(SOKAwVUcyD == true){SOKAwVUcyD = false;}
      if(gCyDxKIKtc == true){gCyDxKIKtc = false;}
      if(ZfzicuoJoA == true){ZfzicuoJoA = false;}
      if(EkWIxRXXUu == true){EkWIxRXXUu = false;}
      if(JFVQVgtraf == true){JFVQVgtraf = false;}
      if(nUbFbmOaWA == true){nUbFbmOaWA = false;}
      if(fLmyzuepFe == true){fLmyzuepFe = false;}
      if(mkpyTTJiNu == true){mkpyTTJiNu = false;}
      if(AxhJLjIRfK == true){AxhJLjIRfK = false;}
      if(DwBUPySWQZ == true){DwBUPySWQZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKYFZESHDP
{ 
  void wmEsmKpcnT()
  { 
      bool bIOJiTheMu = false;
      bool dypcCfOTpJ = false;
      bool RrmMuCZHGF = false;
      bool xDxlApgidU = false;
      bool cgBjriWjfX = false;
      bool pRRbqjUBNf = false;
      bool taYHxZBDcL = false;
      bool yfoVgjqDUL = false;
      bool foaiPflUtP = false;
      bool VfVxaBHsmR = false;
      bool hSHTZKcwuG = false;
      bool sQfBAEzpqR = false;
      bool nfJMpSJqte = false;
      bool cxQDdMhGJF = false;
      bool CpZmWEzTxV = false;
      bool CRCVdCJtdG = false;
      bool AkBQduAcXm = false;
      bool WrglOyGVok = false;
      bool SptXbKuuZa = false;
      bool DmcCERnJIb = false;
      string NjBwDTeCDd;
      string rKGeqxZgUO;
      string UCHjBSmnPL;
      string DexCdEUmSt;
      string EkVXsBcUEE;
      string JCSjoLcRtj;
      string gqlqZNMDAm;
      string cmOZJifjpA;
      string oRjLCBLNMS;
      string bCrhNNzdxf;
      string nYTQaWnsaF;
      string esbttOGaoY;
      string ByqhLZtfMu;
      string jBlJLQySje;
      string NSmHmiaxmz;
      string HYoXdohkFB;
      string bHgeUdGSid;
      string PmpJLiLiuc;
      string zwrMnLMNeV;
      string hMNiDFkHlJ;
      if(NjBwDTeCDd == nYTQaWnsaF){bIOJiTheMu = true;}
      else if(nYTQaWnsaF == NjBwDTeCDd){hSHTZKcwuG = true;}
      if(rKGeqxZgUO == esbttOGaoY){dypcCfOTpJ = true;}
      else if(esbttOGaoY == rKGeqxZgUO){sQfBAEzpqR = true;}
      if(UCHjBSmnPL == ByqhLZtfMu){RrmMuCZHGF = true;}
      else if(ByqhLZtfMu == UCHjBSmnPL){nfJMpSJqte = true;}
      if(DexCdEUmSt == jBlJLQySje){xDxlApgidU = true;}
      else if(jBlJLQySje == DexCdEUmSt){cxQDdMhGJF = true;}
      if(EkVXsBcUEE == NSmHmiaxmz){cgBjriWjfX = true;}
      else if(NSmHmiaxmz == EkVXsBcUEE){CpZmWEzTxV = true;}
      if(JCSjoLcRtj == HYoXdohkFB){pRRbqjUBNf = true;}
      else if(HYoXdohkFB == JCSjoLcRtj){CRCVdCJtdG = true;}
      if(gqlqZNMDAm == bHgeUdGSid){taYHxZBDcL = true;}
      else if(bHgeUdGSid == gqlqZNMDAm){AkBQduAcXm = true;}
      if(cmOZJifjpA == PmpJLiLiuc){yfoVgjqDUL = true;}
      if(oRjLCBLNMS == zwrMnLMNeV){foaiPflUtP = true;}
      if(bCrhNNzdxf == hMNiDFkHlJ){VfVxaBHsmR = true;}
      while(PmpJLiLiuc == cmOZJifjpA){WrglOyGVok = true;}
      while(zwrMnLMNeV == zwrMnLMNeV){SptXbKuuZa = true;}
      while(hMNiDFkHlJ == hMNiDFkHlJ){DmcCERnJIb = true;}
      if(bIOJiTheMu == true){bIOJiTheMu = false;}
      if(dypcCfOTpJ == true){dypcCfOTpJ = false;}
      if(RrmMuCZHGF == true){RrmMuCZHGF = false;}
      if(xDxlApgidU == true){xDxlApgidU = false;}
      if(cgBjriWjfX == true){cgBjriWjfX = false;}
      if(pRRbqjUBNf == true){pRRbqjUBNf = false;}
      if(taYHxZBDcL == true){taYHxZBDcL = false;}
      if(yfoVgjqDUL == true){yfoVgjqDUL = false;}
      if(foaiPflUtP == true){foaiPflUtP = false;}
      if(VfVxaBHsmR == true){VfVxaBHsmR = false;}
      if(hSHTZKcwuG == true){hSHTZKcwuG = false;}
      if(sQfBAEzpqR == true){sQfBAEzpqR = false;}
      if(nfJMpSJqte == true){nfJMpSJqte = false;}
      if(cxQDdMhGJF == true){cxQDdMhGJF = false;}
      if(CpZmWEzTxV == true){CpZmWEzTxV = false;}
      if(CRCVdCJtdG == true){CRCVdCJtdG = false;}
      if(AkBQduAcXm == true){AkBQduAcXm = false;}
      if(WrglOyGVok == true){WrglOyGVok = false;}
      if(SptXbKuuZa == true){SptXbKuuZa = false;}
      if(DmcCERnJIb == true){DmcCERnJIb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QENNEYYOXW
{ 
  void FuOWVeauUR()
  { 
      bool gcqcyUNTkZ = false;
      bool mNcfAaiWmL = false;
      bool MQkVrHmcZl = false;
      bool pJyedsquMN = false;
      bool DXQtdbusjm = false;
      bool jUMhIPqVkp = false;
      bool gktyidOyBG = false;
      bool inKZHnAprQ = false;
      bool LtrmBUwQVO = false;
      bool CVKVgScRLz = false;
      bool MxrdDwKmZT = false;
      bool PAcTemrHxN = false;
      bool hybmENdnso = false;
      bool LhesEOCOiF = false;
      bool KJpByBspqt = false;
      bool ZUUyRNUEZp = false;
      bool SWtjIgVjPP = false;
      bool kdYqDXHZoC = false;
      bool UmwyPpNgap = false;
      bool sxoslmPGsQ = false;
      string LcGCnBpfQh;
      string dPOENURCyq;
      string lowZJtNqdL;
      string fVaFAryXfy;
      string MxXbcSdIXw;
      string QNWRLVfgrs;
      string myBFBIoJEV;
      string VsWzeoRTxq;
      string QFTgtSyItd;
      string LRfmKNuRZT;
      string cUDBaWqWlW;
      string EMiBcgeTKh;
      string KfOZKENinQ;
      string szscNuBRGW;
      string baVWZzheKd;
      string hbHrIxFcqV;
      string JHhVcESFmg;
      string fNNmGiJrAK;
      string ViYKhRrBUQ;
      string oXZjNTrAsV;
      if(LcGCnBpfQh == cUDBaWqWlW){gcqcyUNTkZ = true;}
      else if(cUDBaWqWlW == LcGCnBpfQh){MxrdDwKmZT = true;}
      if(dPOENURCyq == EMiBcgeTKh){mNcfAaiWmL = true;}
      else if(EMiBcgeTKh == dPOENURCyq){PAcTemrHxN = true;}
      if(lowZJtNqdL == KfOZKENinQ){MQkVrHmcZl = true;}
      else if(KfOZKENinQ == lowZJtNqdL){hybmENdnso = true;}
      if(fVaFAryXfy == szscNuBRGW){pJyedsquMN = true;}
      else if(szscNuBRGW == fVaFAryXfy){LhesEOCOiF = true;}
      if(MxXbcSdIXw == baVWZzheKd){DXQtdbusjm = true;}
      else if(baVWZzheKd == MxXbcSdIXw){KJpByBspqt = true;}
      if(QNWRLVfgrs == hbHrIxFcqV){jUMhIPqVkp = true;}
      else if(hbHrIxFcqV == QNWRLVfgrs){ZUUyRNUEZp = true;}
      if(myBFBIoJEV == JHhVcESFmg){gktyidOyBG = true;}
      else if(JHhVcESFmg == myBFBIoJEV){SWtjIgVjPP = true;}
      if(VsWzeoRTxq == fNNmGiJrAK){inKZHnAprQ = true;}
      if(QFTgtSyItd == ViYKhRrBUQ){LtrmBUwQVO = true;}
      if(LRfmKNuRZT == oXZjNTrAsV){CVKVgScRLz = true;}
      while(fNNmGiJrAK == VsWzeoRTxq){kdYqDXHZoC = true;}
      while(ViYKhRrBUQ == ViYKhRrBUQ){UmwyPpNgap = true;}
      while(oXZjNTrAsV == oXZjNTrAsV){sxoslmPGsQ = true;}
      if(gcqcyUNTkZ == true){gcqcyUNTkZ = false;}
      if(mNcfAaiWmL == true){mNcfAaiWmL = false;}
      if(MQkVrHmcZl == true){MQkVrHmcZl = false;}
      if(pJyedsquMN == true){pJyedsquMN = false;}
      if(DXQtdbusjm == true){DXQtdbusjm = false;}
      if(jUMhIPqVkp == true){jUMhIPqVkp = false;}
      if(gktyidOyBG == true){gktyidOyBG = false;}
      if(inKZHnAprQ == true){inKZHnAprQ = false;}
      if(LtrmBUwQVO == true){LtrmBUwQVO = false;}
      if(CVKVgScRLz == true){CVKVgScRLz = false;}
      if(MxrdDwKmZT == true){MxrdDwKmZT = false;}
      if(PAcTemrHxN == true){PAcTemrHxN = false;}
      if(hybmENdnso == true){hybmENdnso = false;}
      if(LhesEOCOiF == true){LhesEOCOiF = false;}
      if(KJpByBspqt == true){KJpByBspqt = false;}
      if(ZUUyRNUEZp == true){ZUUyRNUEZp = false;}
      if(SWtjIgVjPP == true){SWtjIgVjPP = false;}
      if(kdYqDXHZoC == true){kdYqDXHZoC = false;}
      if(UmwyPpNgap == true){UmwyPpNgap = false;}
      if(sxoslmPGsQ == true){sxoslmPGsQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZAKLYQROUF
{ 
  void UmgYkTGTuV()
  { 
      bool nPqKrOFXJT = false;
      bool pfNLRAlESN = false;
      bool NaPVybsjPF = false;
      bool wlzZreuoit = false;
      bool YDpzlpuWfL = false;
      bool dBMQUMAVLQ = false;
      bool UUIDWEfmSl = false;
      bool ExVXnKjQiI = false;
      bool gWEEbuZhFf = false;
      bool dZcRZDulch = false;
      bool KHDtGgeocJ = false;
      bool bjmDjyQEba = false;
      bool dxhmHeTDyj = false;
      bool PymAyYSJxt = false;
      bool PjFuDtmZhb = false;
      bool mpJBDMZQlb = false;
      bool NbprtdwlFK = false;
      bool eGHhLsrliN = false;
      bool qsUWxYnlwk = false;
      bool zBXUgmtNAY = false;
      string gOICUzixVe;
      string WLQbcPXhgB;
      string nPYfDdESnf;
      string qGElGLzWWl;
      string IpOpcmnXFX;
      string RZgUHQobyp;
      string tPJomPHeVR;
      string QBKusyAiDP;
      string pfNQOQYieo;
      string VWXfqsgZCN;
      string fJCmGPPkbI;
      string QGXhANCsZW;
      string pXzguscdEA;
      string RafojfdZKz;
      string BmGVXOyoec;
      string pnzfWHJVrM;
      string mkgbqoaiyU;
      string jbhaVDQdIg;
      string umzbJdbASc;
      string VIhxLPGedh;
      if(gOICUzixVe == fJCmGPPkbI){nPqKrOFXJT = true;}
      else if(fJCmGPPkbI == gOICUzixVe){KHDtGgeocJ = true;}
      if(WLQbcPXhgB == QGXhANCsZW){pfNLRAlESN = true;}
      else if(QGXhANCsZW == WLQbcPXhgB){bjmDjyQEba = true;}
      if(nPYfDdESnf == pXzguscdEA){NaPVybsjPF = true;}
      else if(pXzguscdEA == nPYfDdESnf){dxhmHeTDyj = true;}
      if(qGElGLzWWl == RafojfdZKz){wlzZreuoit = true;}
      else if(RafojfdZKz == qGElGLzWWl){PymAyYSJxt = true;}
      if(IpOpcmnXFX == BmGVXOyoec){YDpzlpuWfL = true;}
      else if(BmGVXOyoec == IpOpcmnXFX){PjFuDtmZhb = true;}
      if(RZgUHQobyp == pnzfWHJVrM){dBMQUMAVLQ = true;}
      else if(pnzfWHJVrM == RZgUHQobyp){mpJBDMZQlb = true;}
      if(tPJomPHeVR == mkgbqoaiyU){UUIDWEfmSl = true;}
      else if(mkgbqoaiyU == tPJomPHeVR){NbprtdwlFK = true;}
      if(QBKusyAiDP == jbhaVDQdIg){ExVXnKjQiI = true;}
      if(pfNQOQYieo == umzbJdbASc){gWEEbuZhFf = true;}
      if(VWXfqsgZCN == VIhxLPGedh){dZcRZDulch = true;}
      while(jbhaVDQdIg == QBKusyAiDP){eGHhLsrliN = true;}
      while(umzbJdbASc == umzbJdbASc){qsUWxYnlwk = true;}
      while(VIhxLPGedh == VIhxLPGedh){zBXUgmtNAY = true;}
      if(nPqKrOFXJT == true){nPqKrOFXJT = false;}
      if(pfNLRAlESN == true){pfNLRAlESN = false;}
      if(NaPVybsjPF == true){NaPVybsjPF = false;}
      if(wlzZreuoit == true){wlzZreuoit = false;}
      if(YDpzlpuWfL == true){YDpzlpuWfL = false;}
      if(dBMQUMAVLQ == true){dBMQUMAVLQ = false;}
      if(UUIDWEfmSl == true){UUIDWEfmSl = false;}
      if(ExVXnKjQiI == true){ExVXnKjQiI = false;}
      if(gWEEbuZhFf == true){gWEEbuZhFf = false;}
      if(dZcRZDulch == true){dZcRZDulch = false;}
      if(KHDtGgeocJ == true){KHDtGgeocJ = false;}
      if(bjmDjyQEba == true){bjmDjyQEba = false;}
      if(dxhmHeTDyj == true){dxhmHeTDyj = false;}
      if(PymAyYSJxt == true){PymAyYSJxt = false;}
      if(PjFuDtmZhb == true){PjFuDtmZhb = false;}
      if(mpJBDMZQlb == true){mpJBDMZQlb = false;}
      if(NbprtdwlFK == true){NbprtdwlFK = false;}
      if(eGHhLsrliN == true){eGHhLsrliN = false;}
      if(qsUWxYnlwk == true){qsUWxYnlwk = false;}
      if(zBXUgmtNAY == true){zBXUgmtNAY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTAAIBWGUG
{ 
  void GkmCKluyUD()
  { 
      bool zKegOShZCz = false;
      bool oMmblKsHjL = false;
      bool muYwDPMKCZ = false;
      bool fJJPjGOjdw = false;
      bool aftiLczYeG = false;
      bool ubGGZDkidz = false;
      bool FWWcTeDWrf = false;
      bool wIdmjHApjZ = false;
      bool QnfwdDDCpf = false;
      bool UfGepDIROf = false;
      bool ZbfyJlySVR = false;
      bool CuyDiQpayP = false;
      bool bAgLKPBzwg = false;
      bool yibDAnHglq = false;
      bool FjgXdZgDuY = false;
      bool MhTyEZtUnt = false;
      bool kyVoTTTtDt = false;
      bool JJnGJrTJgk = false;
      bool iyDXTPPczZ = false;
      bool tmsrGHOqDJ = false;
      string rkCfctfIxH;
      string lJTTVFEsHf;
      string gLlfZWnIEI;
      string rnighxwUDb;
      string dJZsPFolKx;
      string KqqxJfyWGF;
      string GXDnPyallY;
      string JjofCXlrPT;
      string hCxHxBwkXB;
      string yYNxUGFkdR;
      string eCAlmaBLul;
      string tGGlXEZwqN;
      string BpNjajVqKw;
      string RANyoeCLTW;
      string zkplHqSbZQ;
      string fJtQPnoPLD;
      string EKBzTtrHws;
      string BNbUOPzbci;
      string QtRsPIGxiA;
      string plAQRnjpRN;
      if(rkCfctfIxH == eCAlmaBLul){zKegOShZCz = true;}
      else if(eCAlmaBLul == rkCfctfIxH){ZbfyJlySVR = true;}
      if(lJTTVFEsHf == tGGlXEZwqN){oMmblKsHjL = true;}
      else if(tGGlXEZwqN == lJTTVFEsHf){CuyDiQpayP = true;}
      if(gLlfZWnIEI == BpNjajVqKw){muYwDPMKCZ = true;}
      else if(BpNjajVqKw == gLlfZWnIEI){bAgLKPBzwg = true;}
      if(rnighxwUDb == RANyoeCLTW){fJJPjGOjdw = true;}
      else if(RANyoeCLTW == rnighxwUDb){yibDAnHglq = true;}
      if(dJZsPFolKx == zkplHqSbZQ){aftiLczYeG = true;}
      else if(zkplHqSbZQ == dJZsPFolKx){FjgXdZgDuY = true;}
      if(KqqxJfyWGF == fJtQPnoPLD){ubGGZDkidz = true;}
      else if(fJtQPnoPLD == KqqxJfyWGF){MhTyEZtUnt = true;}
      if(GXDnPyallY == EKBzTtrHws){FWWcTeDWrf = true;}
      else if(EKBzTtrHws == GXDnPyallY){kyVoTTTtDt = true;}
      if(JjofCXlrPT == BNbUOPzbci){wIdmjHApjZ = true;}
      if(hCxHxBwkXB == QtRsPIGxiA){QnfwdDDCpf = true;}
      if(yYNxUGFkdR == plAQRnjpRN){UfGepDIROf = true;}
      while(BNbUOPzbci == JjofCXlrPT){JJnGJrTJgk = true;}
      while(QtRsPIGxiA == QtRsPIGxiA){iyDXTPPczZ = true;}
      while(plAQRnjpRN == plAQRnjpRN){tmsrGHOqDJ = true;}
      if(zKegOShZCz == true){zKegOShZCz = false;}
      if(oMmblKsHjL == true){oMmblKsHjL = false;}
      if(muYwDPMKCZ == true){muYwDPMKCZ = false;}
      if(fJJPjGOjdw == true){fJJPjGOjdw = false;}
      if(aftiLczYeG == true){aftiLczYeG = false;}
      if(ubGGZDkidz == true){ubGGZDkidz = false;}
      if(FWWcTeDWrf == true){FWWcTeDWrf = false;}
      if(wIdmjHApjZ == true){wIdmjHApjZ = false;}
      if(QnfwdDDCpf == true){QnfwdDDCpf = false;}
      if(UfGepDIROf == true){UfGepDIROf = false;}
      if(ZbfyJlySVR == true){ZbfyJlySVR = false;}
      if(CuyDiQpayP == true){CuyDiQpayP = false;}
      if(bAgLKPBzwg == true){bAgLKPBzwg = false;}
      if(yibDAnHglq == true){yibDAnHglq = false;}
      if(FjgXdZgDuY == true){FjgXdZgDuY = false;}
      if(MhTyEZtUnt == true){MhTyEZtUnt = false;}
      if(kyVoTTTtDt == true){kyVoTTTtDt = false;}
      if(JJnGJrTJgk == true){JJnGJrTJgk = false;}
      if(iyDXTPPczZ == true){iyDXTPPczZ = false;}
      if(tmsrGHOqDJ == true){tmsrGHOqDJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCESXHOQRN
{ 
  void DVlQKoZbzC()
  { 
      bool uuJbzkIpxM = false;
      bool eHcWbYtIZf = false;
      bool ypseHtcFxJ = false;
      bool IHkulgdFac = false;
      bool KOVCzgxgZx = false;
      bool xRTLmEBeUF = false;
      bool ICsnDWVhku = false;
      bool uohwUiUpfZ = false;
      bool wwfzLqnZIg = false;
      bool eyjVUHVgzb = false;
      bool KPwdCIjWpD = false;
      bool jLyuIMWtbL = false;
      bool iuYDQwELbN = false;
      bool NmpDOfABwD = false;
      bool GQjFxTAoMI = false;
      bool jaFmsPprNG = false;
      bool DYucoxUtfb = false;
      bool MVyXFRLTFx = false;
      bool uOyTclgDJz = false;
      bool oHnoAhVHPA = false;
      string owAlNmClZR;
      string YIDbMAhrOo;
      string uuicnQTLfT;
      string poRPAswlps;
      string ziTwaJpFKo;
      string PkALstNWyw;
      string SqFGaiqnbS;
      string EuBUoLblCd;
      string aNBqDFoFVG;
      string fYntZIdMUq;
      string SBdrjTjeVg;
      string RaUUVFpNDV;
      string tkRUlfHHug;
      string hORLKYjJGi;
      string UKionEDTYU;
      string RPJywgjJFE;
      string McioyDJIJw;
      string UgHTBjCbfh;
      string bnhaOSESPd;
      string oaDCWratqk;
      if(owAlNmClZR == SBdrjTjeVg){uuJbzkIpxM = true;}
      else if(SBdrjTjeVg == owAlNmClZR){KPwdCIjWpD = true;}
      if(YIDbMAhrOo == RaUUVFpNDV){eHcWbYtIZf = true;}
      else if(RaUUVFpNDV == YIDbMAhrOo){jLyuIMWtbL = true;}
      if(uuicnQTLfT == tkRUlfHHug){ypseHtcFxJ = true;}
      else if(tkRUlfHHug == uuicnQTLfT){iuYDQwELbN = true;}
      if(poRPAswlps == hORLKYjJGi){IHkulgdFac = true;}
      else if(hORLKYjJGi == poRPAswlps){NmpDOfABwD = true;}
      if(ziTwaJpFKo == UKionEDTYU){KOVCzgxgZx = true;}
      else if(UKionEDTYU == ziTwaJpFKo){GQjFxTAoMI = true;}
      if(PkALstNWyw == RPJywgjJFE){xRTLmEBeUF = true;}
      else if(RPJywgjJFE == PkALstNWyw){jaFmsPprNG = true;}
      if(SqFGaiqnbS == McioyDJIJw){ICsnDWVhku = true;}
      else if(McioyDJIJw == SqFGaiqnbS){DYucoxUtfb = true;}
      if(EuBUoLblCd == UgHTBjCbfh){uohwUiUpfZ = true;}
      if(aNBqDFoFVG == bnhaOSESPd){wwfzLqnZIg = true;}
      if(fYntZIdMUq == oaDCWratqk){eyjVUHVgzb = true;}
      while(UgHTBjCbfh == EuBUoLblCd){MVyXFRLTFx = true;}
      while(bnhaOSESPd == bnhaOSESPd){uOyTclgDJz = true;}
      while(oaDCWratqk == oaDCWratqk){oHnoAhVHPA = true;}
      if(uuJbzkIpxM == true){uuJbzkIpxM = false;}
      if(eHcWbYtIZf == true){eHcWbYtIZf = false;}
      if(ypseHtcFxJ == true){ypseHtcFxJ = false;}
      if(IHkulgdFac == true){IHkulgdFac = false;}
      if(KOVCzgxgZx == true){KOVCzgxgZx = false;}
      if(xRTLmEBeUF == true){xRTLmEBeUF = false;}
      if(ICsnDWVhku == true){ICsnDWVhku = false;}
      if(uohwUiUpfZ == true){uohwUiUpfZ = false;}
      if(wwfzLqnZIg == true){wwfzLqnZIg = false;}
      if(eyjVUHVgzb == true){eyjVUHVgzb = false;}
      if(KPwdCIjWpD == true){KPwdCIjWpD = false;}
      if(jLyuIMWtbL == true){jLyuIMWtbL = false;}
      if(iuYDQwELbN == true){iuYDQwELbN = false;}
      if(NmpDOfABwD == true){NmpDOfABwD = false;}
      if(GQjFxTAoMI == true){GQjFxTAoMI = false;}
      if(jaFmsPprNG == true){jaFmsPprNG = false;}
      if(DYucoxUtfb == true){DYucoxUtfb = false;}
      if(MVyXFRLTFx == true){MVyXFRLTFx = false;}
      if(uOyTclgDJz == true){uOyTclgDJz = false;}
      if(oHnoAhVHPA == true){oHnoAhVHPA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THUWJMZEQD
{ 
  void pSPTGBloBH()
  { 
      bool jAnKXsAfAe = false;
      bool XifXELXzDt = false;
      bool bgJzlLuxJn = false;
      bool nnlqHNKRJB = false;
      bool XwnFpdBKSc = false;
      bool DOygRCqoXL = false;
      bool yDWMqjxoQq = false;
      bool BGoBVfrEJH = false;
      bool KkdfjZoEYE = false;
      bool VVsxCTYbNG = false;
      bool gLsabxYxKl = false;
      bool KmePBNYpcQ = false;
      bool urPLUfMqyC = false;
      bool GQpDayqCEl = false;
      bool Aqtmtipcwo = false;
      bool tiyxKnugGu = false;
      bool khyIesxboC = false;
      bool WWkpQDycRl = false;
      bool oiuJHWRsrl = false;
      bool CJwIBSrkHA = false;
      string hSCSzkuojL;
      string eNIGGcLuCI;
      string lhauuduGKV;
      string GJDuLZNQox;
      string oLtNzNQwtq;
      string IrjknAqHXV;
      string pndNFVJNug;
      string PuGFTamNug;
      string MzLSNNYSGL;
      string iGsTHAgfHd;
      string EDBNbMleRM;
      string McLpJpcLAq;
      string wpGjxIBlyS;
      string tHGRbJyypA;
      string btAtyGtCKQ;
      string XVfQgNwQPS;
      string LzfySEWsNz;
      string rdUzPCpMkq;
      string OzbguYbojN;
      string NgiXobNCat;
      if(hSCSzkuojL == EDBNbMleRM){jAnKXsAfAe = true;}
      else if(EDBNbMleRM == hSCSzkuojL){gLsabxYxKl = true;}
      if(eNIGGcLuCI == McLpJpcLAq){XifXELXzDt = true;}
      else if(McLpJpcLAq == eNIGGcLuCI){KmePBNYpcQ = true;}
      if(lhauuduGKV == wpGjxIBlyS){bgJzlLuxJn = true;}
      else if(wpGjxIBlyS == lhauuduGKV){urPLUfMqyC = true;}
      if(GJDuLZNQox == tHGRbJyypA){nnlqHNKRJB = true;}
      else if(tHGRbJyypA == GJDuLZNQox){GQpDayqCEl = true;}
      if(oLtNzNQwtq == btAtyGtCKQ){XwnFpdBKSc = true;}
      else if(btAtyGtCKQ == oLtNzNQwtq){Aqtmtipcwo = true;}
      if(IrjknAqHXV == XVfQgNwQPS){DOygRCqoXL = true;}
      else if(XVfQgNwQPS == IrjknAqHXV){tiyxKnugGu = true;}
      if(pndNFVJNug == LzfySEWsNz){yDWMqjxoQq = true;}
      else if(LzfySEWsNz == pndNFVJNug){khyIesxboC = true;}
      if(PuGFTamNug == rdUzPCpMkq){BGoBVfrEJH = true;}
      if(MzLSNNYSGL == OzbguYbojN){KkdfjZoEYE = true;}
      if(iGsTHAgfHd == NgiXobNCat){VVsxCTYbNG = true;}
      while(rdUzPCpMkq == PuGFTamNug){WWkpQDycRl = true;}
      while(OzbguYbojN == OzbguYbojN){oiuJHWRsrl = true;}
      while(NgiXobNCat == NgiXobNCat){CJwIBSrkHA = true;}
      if(jAnKXsAfAe == true){jAnKXsAfAe = false;}
      if(XifXELXzDt == true){XifXELXzDt = false;}
      if(bgJzlLuxJn == true){bgJzlLuxJn = false;}
      if(nnlqHNKRJB == true){nnlqHNKRJB = false;}
      if(XwnFpdBKSc == true){XwnFpdBKSc = false;}
      if(DOygRCqoXL == true){DOygRCqoXL = false;}
      if(yDWMqjxoQq == true){yDWMqjxoQq = false;}
      if(BGoBVfrEJH == true){BGoBVfrEJH = false;}
      if(KkdfjZoEYE == true){KkdfjZoEYE = false;}
      if(VVsxCTYbNG == true){VVsxCTYbNG = false;}
      if(gLsabxYxKl == true){gLsabxYxKl = false;}
      if(KmePBNYpcQ == true){KmePBNYpcQ = false;}
      if(urPLUfMqyC == true){urPLUfMqyC = false;}
      if(GQpDayqCEl == true){GQpDayqCEl = false;}
      if(Aqtmtipcwo == true){Aqtmtipcwo = false;}
      if(tiyxKnugGu == true){tiyxKnugGu = false;}
      if(khyIesxboC == true){khyIesxboC = false;}
      if(WWkpQDycRl == true){WWkpQDycRl = false;}
      if(oiuJHWRsrl == true){oiuJHWRsrl = false;}
      if(CJwIBSrkHA == true){CJwIBSrkHA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSPHWEZDUP
{ 
  void xzuQuSGXyp()
  { 
      bool tMgMFMlMnV = false;
      bool PJskCsTlsw = false;
      bool HYTLWKfPfG = false;
      bool DjEcLnWEJw = false;
      bool rgyMjGCsGA = false;
      bool taQPQVrVpt = false;
      bool gWghSfFPYO = false;
      bool WObxEZZGaQ = false;
      bool IlIeMbTnLo = false;
      bool uBOPPUAQsE = false;
      bool BlTrdezSKp = false;
      bool ultZktNBUp = false;
      bool MQEiSUALhj = false;
      bool ZJMWOVSQBh = false;
      bool cAdVtJGoeU = false;
      bool GyuDqjhjZI = false;
      bool dmkaQlYWKO = false;
      bool bxAmNLmhoI = false;
      bool NLgMcaOJfd = false;
      bool nhqrDoPCEI = false;
      string fEdnzcDRGY;
      string YMOZUqVVAi;
      string EFXWsDUByx;
      string CDJIltqJZQ;
      string CQPzlSjJdS;
      string IzMOEafGuw;
      string HCSIWVCGmZ;
      string zLujfnoYkZ;
      string SLXfoDquDL;
      string NjNdIAxHbQ;
      string QcVDSwDchQ;
      string kHVUcwdlTT;
      string dGDbMOxRae;
      string phwUJpoUNs;
      string zOMmaGNsAL;
      string VLmIlJZtpD;
      string ykBCaCLBLm;
      string GJYZTPsQAF;
      string AERPIdtmhz;
      string PudJtNMJLX;
      if(fEdnzcDRGY == QcVDSwDchQ){tMgMFMlMnV = true;}
      else if(QcVDSwDchQ == fEdnzcDRGY){BlTrdezSKp = true;}
      if(YMOZUqVVAi == kHVUcwdlTT){PJskCsTlsw = true;}
      else if(kHVUcwdlTT == YMOZUqVVAi){ultZktNBUp = true;}
      if(EFXWsDUByx == dGDbMOxRae){HYTLWKfPfG = true;}
      else if(dGDbMOxRae == EFXWsDUByx){MQEiSUALhj = true;}
      if(CDJIltqJZQ == phwUJpoUNs){DjEcLnWEJw = true;}
      else if(phwUJpoUNs == CDJIltqJZQ){ZJMWOVSQBh = true;}
      if(CQPzlSjJdS == zOMmaGNsAL){rgyMjGCsGA = true;}
      else if(zOMmaGNsAL == CQPzlSjJdS){cAdVtJGoeU = true;}
      if(IzMOEafGuw == VLmIlJZtpD){taQPQVrVpt = true;}
      else if(VLmIlJZtpD == IzMOEafGuw){GyuDqjhjZI = true;}
      if(HCSIWVCGmZ == ykBCaCLBLm){gWghSfFPYO = true;}
      else if(ykBCaCLBLm == HCSIWVCGmZ){dmkaQlYWKO = true;}
      if(zLujfnoYkZ == GJYZTPsQAF){WObxEZZGaQ = true;}
      if(SLXfoDquDL == AERPIdtmhz){IlIeMbTnLo = true;}
      if(NjNdIAxHbQ == PudJtNMJLX){uBOPPUAQsE = true;}
      while(GJYZTPsQAF == zLujfnoYkZ){bxAmNLmhoI = true;}
      while(AERPIdtmhz == AERPIdtmhz){NLgMcaOJfd = true;}
      while(PudJtNMJLX == PudJtNMJLX){nhqrDoPCEI = true;}
      if(tMgMFMlMnV == true){tMgMFMlMnV = false;}
      if(PJskCsTlsw == true){PJskCsTlsw = false;}
      if(HYTLWKfPfG == true){HYTLWKfPfG = false;}
      if(DjEcLnWEJw == true){DjEcLnWEJw = false;}
      if(rgyMjGCsGA == true){rgyMjGCsGA = false;}
      if(taQPQVrVpt == true){taQPQVrVpt = false;}
      if(gWghSfFPYO == true){gWghSfFPYO = false;}
      if(WObxEZZGaQ == true){WObxEZZGaQ = false;}
      if(IlIeMbTnLo == true){IlIeMbTnLo = false;}
      if(uBOPPUAQsE == true){uBOPPUAQsE = false;}
      if(BlTrdezSKp == true){BlTrdezSKp = false;}
      if(ultZktNBUp == true){ultZktNBUp = false;}
      if(MQEiSUALhj == true){MQEiSUALhj = false;}
      if(ZJMWOVSQBh == true){ZJMWOVSQBh = false;}
      if(cAdVtJGoeU == true){cAdVtJGoeU = false;}
      if(GyuDqjhjZI == true){GyuDqjhjZI = false;}
      if(dmkaQlYWKO == true){dmkaQlYWKO = false;}
      if(bxAmNLmhoI == true){bxAmNLmhoI = false;}
      if(NLgMcaOJfd == true){NLgMcaOJfd = false;}
      if(nhqrDoPCEI == true){nhqrDoPCEI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAJWUEHOIN
{ 
  void APlmqgWAzY()
  { 
      bool ZakVqraIwi = false;
      bool nqkKDxkaBC = false;
      bool fQCbDBYXZP = false;
      bool IFGNztfmmL = false;
      bool hYHRQPMAkZ = false;
      bool twkkGJXJSp = false;
      bool SDhfaikXLI = false;
      bool RxmpUGIjKm = false;
      bool nYmAVLTUHp = false;
      bool VWUxsepaqh = false;
      bool doncIxJuQz = false;
      bool AmzeBtPhKO = false;
      bool OQQVltcpxp = false;
      bool QhsbJzjKqY = false;
      bool CYDHoiXouy = false;
      bool OHPcSNXSpO = false;
      bool TSyahStWVC = false;
      bool KFqlLpMIfD = false;
      bool WmuyaJRPJu = false;
      bool aRTbEjZbYW = false;
      string rbxMdOKUkK;
      string tUUtNPjsZc;
      string fFDimBJfKL;
      string cdFVqiOMPd;
      string mWUtqhcogZ;
      string XQXaPmYNZc;
      string EeKZhQPyDd;
      string BXdwoIjIrF;
      string XUyknMFeFD;
      string KAmlZIMtMZ;
      string RdkDYzlblH;
      string DPVUEifYlU;
      string KkrASAjqVf;
      string wouRmsiuMn;
      string ZdryAteShq;
      string cmHqPglkjX;
      string PtFFKNUEgL;
      string zjMyufrtAY;
      string URJeDIhDBF;
      string HyLnXeXmml;
      if(rbxMdOKUkK == RdkDYzlblH){ZakVqraIwi = true;}
      else if(RdkDYzlblH == rbxMdOKUkK){doncIxJuQz = true;}
      if(tUUtNPjsZc == DPVUEifYlU){nqkKDxkaBC = true;}
      else if(DPVUEifYlU == tUUtNPjsZc){AmzeBtPhKO = true;}
      if(fFDimBJfKL == KkrASAjqVf){fQCbDBYXZP = true;}
      else if(KkrASAjqVf == fFDimBJfKL){OQQVltcpxp = true;}
      if(cdFVqiOMPd == wouRmsiuMn){IFGNztfmmL = true;}
      else if(wouRmsiuMn == cdFVqiOMPd){QhsbJzjKqY = true;}
      if(mWUtqhcogZ == ZdryAteShq){hYHRQPMAkZ = true;}
      else if(ZdryAteShq == mWUtqhcogZ){CYDHoiXouy = true;}
      if(XQXaPmYNZc == cmHqPglkjX){twkkGJXJSp = true;}
      else if(cmHqPglkjX == XQXaPmYNZc){OHPcSNXSpO = true;}
      if(EeKZhQPyDd == PtFFKNUEgL){SDhfaikXLI = true;}
      else if(PtFFKNUEgL == EeKZhQPyDd){TSyahStWVC = true;}
      if(BXdwoIjIrF == zjMyufrtAY){RxmpUGIjKm = true;}
      if(XUyknMFeFD == URJeDIhDBF){nYmAVLTUHp = true;}
      if(KAmlZIMtMZ == HyLnXeXmml){VWUxsepaqh = true;}
      while(zjMyufrtAY == BXdwoIjIrF){KFqlLpMIfD = true;}
      while(URJeDIhDBF == URJeDIhDBF){WmuyaJRPJu = true;}
      while(HyLnXeXmml == HyLnXeXmml){aRTbEjZbYW = true;}
      if(ZakVqraIwi == true){ZakVqraIwi = false;}
      if(nqkKDxkaBC == true){nqkKDxkaBC = false;}
      if(fQCbDBYXZP == true){fQCbDBYXZP = false;}
      if(IFGNztfmmL == true){IFGNztfmmL = false;}
      if(hYHRQPMAkZ == true){hYHRQPMAkZ = false;}
      if(twkkGJXJSp == true){twkkGJXJSp = false;}
      if(SDhfaikXLI == true){SDhfaikXLI = false;}
      if(RxmpUGIjKm == true){RxmpUGIjKm = false;}
      if(nYmAVLTUHp == true){nYmAVLTUHp = false;}
      if(VWUxsepaqh == true){VWUxsepaqh = false;}
      if(doncIxJuQz == true){doncIxJuQz = false;}
      if(AmzeBtPhKO == true){AmzeBtPhKO = false;}
      if(OQQVltcpxp == true){OQQVltcpxp = false;}
      if(QhsbJzjKqY == true){QhsbJzjKqY = false;}
      if(CYDHoiXouy == true){CYDHoiXouy = false;}
      if(OHPcSNXSpO == true){OHPcSNXSpO = false;}
      if(TSyahStWVC == true){TSyahStWVC = false;}
      if(KFqlLpMIfD == true){KFqlLpMIfD = false;}
      if(WmuyaJRPJu == true){WmuyaJRPJu = false;}
      if(aRTbEjZbYW == true){aRTbEjZbYW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GERDRYZMSB
{ 
  void eIAuGjDedN()
  { 
      bool fNaBRTRPoU = false;
      bool xMGPhmfAUB = false;
      bool ZnibrZzAwV = false;
      bool GbdwezmYFs = false;
      bool KuzoUGbwZg = false;
      bool jtDNarezJr = false;
      bool TQTTNUiKkh = false;
      bool zHubqensGl = false;
      bool yDaOlLXQUm = false;
      bool TnPNYsbebz = false;
      bool WQLqhbzbWw = false;
      bool DlrXtQpEgB = false;
      bool xSpxOLrhCy = false;
      bool CIRGOgrjgJ = false;
      bool MwsXjhurSI = false;
      bool DWxZCEaNbV = false;
      bool jRYYstUlIM = false;
      bool YGXXoAYRNg = false;
      bool PAOttfLqDJ = false;
      bool GdHKYtWUeo = false;
      string GMxOUukZyf;
      string DjwERykpSu;
      string ETRpbRUAsG;
      string CmpnCwqUCw;
      string SRJPMCzqQX;
      string BitFQluGlD;
      string ZkgqcQtHBU;
      string GQmVblJCdZ;
      string RdjUFSskWP;
      string BjhzWhkSlu;
      string HqpuRjuXcd;
      string crcMlwBLlJ;
      string XIkkTVinyt;
      string BqQiRZmnDU;
      string XUHrmIHUNa;
      string gZfbXyGEbu;
      string AHYickbstL;
      string IMIQlCBsxL;
      string NNaXNbKnKS;
      string TiMHUQuYOB;
      if(GMxOUukZyf == HqpuRjuXcd){fNaBRTRPoU = true;}
      else if(HqpuRjuXcd == GMxOUukZyf){WQLqhbzbWw = true;}
      if(DjwERykpSu == crcMlwBLlJ){xMGPhmfAUB = true;}
      else if(crcMlwBLlJ == DjwERykpSu){DlrXtQpEgB = true;}
      if(ETRpbRUAsG == XIkkTVinyt){ZnibrZzAwV = true;}
      else if(XIkkTVinyt == ETRpbRUAsG){xSpxOLrhCy = true;}
      if(CmpnCwqUCw == BqQiRZmnDU){GbdwezmYFs = true;}
      else if(BqQiRZmnDU == CmpnCwqUCw){CIRGOgrjgJ = true;}
      if(SRJPMCzqQX == XUHrmIHUNa){KuzoUGbwZg = true;}
      else if(XUHrmIHUNa == SRJPMCzqQX){MwsXjhurSI = true;}
      if(BitFQluGlD == gZfbXyGEbu){jtDNarezJr = true;}
      else if(gZfbXyGEbu == BitFQluGlD){DWxZCEaNbV = true;}
      if(ZkgqcQtHBU == AHYickbstL){TQTTNUiKkh = true;}
      else if(AHYickbstL == ZkgqcQtHBU){jRYYstUlIM = true;}
      if(GQmVblJCdZ == IMIQlCBsxL){zHubqensGl = true;}
      if(RdjUFSskWP == NNaXNbKnKS){yDaOlLXQUm = true;}
      if(BjhzWhkSlu == TiMHUQuYOB){TnPNYsbebz = true;}
      while(IMIQlCBsxL == GQmVblJCdZ){YGXXoAYRNg = true;}
      while(NNaXNbKnKS == NNaXNbKnKS){PAOttfLqDJ = true;}
      while(TiMHUQuYOB == TiMHUQuYOB){GdHKYtWUeo = true;}
      if(fNaBRTRPoU == true){fNaBRTRPoU = false;}
      if(xMGPhmfAUB == true){xMGPhmfAUB = false;}
      if(ZnibrZzAwV == true){ZnibrZzAwV = false;}
      if(GbdwezmYFs == true){GbdwezmYFs = false;}
      if(KuzoUGbwZg == true){KuzoUGbwZg = false;}
      if(jtDNarezJr == true){jtDNarezJr = false;}
      if(TQTTNUiKkh == true){TQTTNUiKkh = false;}
      if(zHubqensGl == true){zHubqensGl = false;}
      if(yDaOlLXQUm == true){yDaOlLXQUm = false;}
      if(TnPNYsbebz == true){TnPNYsbebz = false;}
      if(WQLqhbzbWw == true){WQLqhbzbWw = false;}
      if(DlrXtQpEgB == true){DlrXtQpEgB = false;}
      if(xSpxOLrhCy == true){xSpxOLrhCy = false;}
      if(CIRGOgrjgJ == true){CIRGOgrjgJ = false;}
      if(MwsXjhurSI == true){MwsXjhurSI = false;}
      if(DWxZCEaNbV == true){DWxZCEaNbV = false;}
      if(jRYYstUlIM == true){jRYYstUlIM = false;}
      if(YGXXoAYRNg == true){YGXXoAYRNg = false;}
      if(PAOttfLqDJ == true){PAOttfLqDJ = false;}
      if(GdHKYtWUeo == true){GdHKYtWUeo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXVDTTJMWR
{ 
  void mZkLdBAhSN()
  { 
      bool HKPTAYIUqj = false;
      bool dthAUZzmXN = false;
      bool zAIDfcGbOh = false;
      bool bYJaiazFrT = false;
      bool qEKeItoQwJ = false;
      bool mJWzEGCMnW = false;
      bool SfFJIEkGQs = false;
      bool ZtuEVupctl = false;
      bool mpfFtRCJVc = false;
      bool YmQUALyBVD = false;
      bool IhzCirORdJ = false;
      bool PYRCicAAOp = false;
      bool CajnUmcZDK = false;
      bool woGqcEpcVB = false;
      bool DjfMNzVOkX = false;
      bool KxleAhxLhw = false;
      bool PnNSMZRaYe = false;
      bool lXdMlStXaV = false;
      bool RNneAyDapu = false;
      bool HeuZlPVNzm = false;
      string wGcVYaEsOD;
      string KqYAXLTpNg;
      string KriwkcfVaC;
      string UHshyxLQLg;
      string MlFcNYGYTb;
      string PSFaoEWfkw;
      string tiRMiDxqCa;
      string ACdfTXlGiL;
      string VHBzmBBSst;
      string ZefPmdUssK;
      string bPVsaMnYGR;
      string RPwZalgRYg;
      string BeyIBUWOsp;
      string DsNYiFkIXZ;
      string McLacJiGoA;
      string xCTLIxRNqG;
      string pZfQNYCXpU;
      string AXszUYSWeq;
      string lPZrrAYBPl;
      string nXQRjmwtNE;
      if(wGcVYaEsOD == bPVsaMnYGR){HKPTAYIUqj = true;}
      else if(bPVsaMnYGR == wGcVYaEsOD){IhzCirORdJ = true;}
      if(KqYAXLTpNg == RPwZalgRYg){dthAUZzmXN = true;}
      else if(RPwZalgRYg == KqYAXLTpNg){PYRCicAAOp = true;}
      if(KriwkcfVaC == BeyIBUWOsp){zAIDfcGbOh = true;}
      else if(BeyIBUWOsp == KriwkcfVaC){CajnUmcZDK = true;}
      if(UHshyxLQLg == DsNYiFkIXZ){bYJaiazFrT = true;}
      else if(DsNYiFkIXZ == UHshyxLQLg){woGqcEpcVB = true;}
      if(MlFcNYGYTb == McLacJiGoA){qEKeItoQwJ = true;}
      else if(McLacJiGoA == MlFcNYGYTb){DjfMNzVOkX = true;}
      if(PSFaoEWfkw == xCTLIxRNqG){mJWzEGCMnW = true;}
      else if(xCTLIxRNqG == PSFaoEWfkw){KxleAhxLhw = true;}
      if(tiRMiDxqCa == pZfQNYCXpU){SfFJIEkGQs = true;}
      else if(pZfQNYCXpU == tiRMiDxqCa){PnNSMZRaYe = true;}
      if(ACdfTXlGiL == AXszUYSWeq){ZtuEVupctl = true;}
      if(VHBzmBBSst == lPZrrAYBPl){mpfFtRCJVc = true;}
      if(ZefPmdUssK == nXQRjmwtNE){YmQUALyBVD = true;}
      while(AXszUYSWeq == ACdfTXlGiL){lXdMlStXaV = true;}
      while(lPZrrAYBPl == lPZrrAYBPl){RNneAyDapu = true;}
      while(nXQRjmwtNE == nXQRjmwtNE){HeuZlPVNzm = true;}
      if(HKPTAYIUqj == true){HKPTAYIUqj = false;}
      if(dthAUZzmXN == true){dthAUZzmXN = false;}
      if(zAIDfcGbOh == true){zAIDfcGbOh = false;}
      if(bYJaiazFrT == true){bYJaiazFrT = false;}
      if(qEKeItoQwJ == true){qEKeItoQwJ = false;}
      if(mJWzEGCMnW == true){mJWzEGCMnW = false;}
      if(SfFJIEkGQs == true){SfFJIEkGQs = false;}
      if(ZtuEVupctl == true){ZtuEVupctl = false;}
      if(mpfFtRCJVc == true){mpfFtRCJVc = false;}
      if(YmQUALyBVD == true){YmQUALyBVD = false;}
      if(IhzCirORdJ == true){IhzCirORdJ = false;}
      if(PYRCicAAOp == true){PYRCicAAOp = false;}
      if(CajnUmcZDK == true){CajnUmcZDK = false;}
      if(woGqcEpcVB == true){woGqcEpcVB = false;}
      if(DjfMNzVOkX == true){DjfMNzVOkX = false;}
      if(KxleAhxLhw == true){KxleAhxLhw = false;}
      if(PnNSMZRaYe == true){PnNSMZRaYe = false;}
      if(lXdMlStXaV == true){lXdMlStXaV = false;}
      if(RNneAyDapu == true){RNneAyDapu = false;}
      if(HeuZlPVNzm == true){HeuZlPVNzm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNSNVKQVXP
{ 
  void GmnkDtBOJa()
  { 
      bool SpDhFTySyl = false;
      bool GcKYyHQTQz = false;
      bool waOZwmpmfC = false;
      bool YKrGTuhIMU = false;
      bool KsUhWJmEgq = false;
      bool AIVdPqadlR = false;
      bool dKlwMujEED = false;
      bool YHHunDFgCm = false;
      bool zkGoBQoOqc = false;
      bool TDWtqAGYVb = false;
      bool YizdRsAZpM = false;
      bool ktbzRrExuu = false;
      bool GVNbiVkNEn = false;
      bool xgKZNQkcWI = false;
      bool PPYeqZbXby = false;
      bool uIdZVDVXtw = false;
      bool HmUBPEiBkB = false;
      bool GbalepwhjI = false;
      bool sNkGrnDkEJ = false;
      bool tNhZActWPm = false;
      string BVCytsXNGe;
      string BCKKUwuogo;
      string JCqxkgjKZF;
      string wXlekZVHxP;
      string MkWsiJnpHS;
      string ZHMLIyeFNM;
      string INmBhcPfZu;
      string ZmrQcYfxNb;
      string ssCGeoLaWl;
      string tQtjGzxULF;
      string sHQMsmPwij;
      string SgqlTOKfWs;
      string RoImAJsHJd;
      string aKlIhkcpNr;
      string YOqmTNYHQr;
      string nQyRnEzdLi;
      string sHlFJIuiDh;
      string lUSeTCxVSm;
      string klqRoJLTTd;
      string lydeyRcldL;
      if(BVCytsXNGe == sHQMsmPwij){SpDhFTySyl = true;}
      else if(sHQMsmPwij == BVCytsXNGe){YizdRsAZpM = true;}
      if(BCKKUwuogo == SgqlTOKfWs){GcKYyHQTQz = true;}
      else if(SgqlTOKfWs == BCKKUwuogo){ktbzRrExuu = true;}
      if(JCqxkgjKZF == RoImAJsHJd){waOZwmpmfC = true;}
      else if(RoImAJsHJd == JCqxkgjKZF){GVNbiVkNEn = true;}
      if(wXlekZVHxP == aKlIhkcpNr){YKrGTuhIMU = true;}
      else if(aKlIhkcpNr == wXlekZVHxP){xgKZNQkcWI = true;}
      if(MkWsiJnpHS == YOqmTNYHQr){KsUhWJmEgq = true;}
      else if(YOqmTNYHQr == MkWsiJnpHS){PPYeqZbXby = true;}
      if(ZHMLIyeFNM == nQyRnEzdLi){AIVdPqadlR = true;}
      else if(nQyRnEzdLi == ZHMLIyeFNM){uIdZVDVXtw = true;}
      if(INmBhcPfZu == sHlFJIuiDh){dKlwMujEED = true;}
      else if(sHlFJIuiDh == INmBhcPfZu){HmUBPEiBkB = true;}
      if(ZmrQcYfxNb == lUSeTCxVSm){YHHunDFgCm = true;}
      if(ssCGeoLaWl == klqRoJLTTd){zkGoBQoOqc = true;}
      if(tQtjGzxULF == lydeyRcldL){TDWtqAGYVb = true;}
      while(lUSeTCxVSm == ZmrQcYfxNb){GbalepwhjI = true;}
      while(klqRoJLTTd == klqRoJLTTd){sNkGrnDkEJ = true;}
      while(lydeyRcldL == lydeyRcldL){tNhZActWPm = true;}
      if(SpDhFTySyl == true){SpDhFTySyl = false;}
      if(GcKYyHQTQz == true){GcKYyHQTQz = false;}
      if(waOZwmpmfC == true){waOZwmpmfC = false;}
      if(YKrGTuhIMU == true){YKrGTuhIMU = false;}
      if(KsUhWJmEgq == true){KsUhWJmEgq = false;}
      if(AIVdPqadlR == true){AIVdPqadlR = false;}
      if(dKlwMujEED == true){dKlwMujEED = false;}
      if(YHHunDFgCm == true){YHHunDFgCm = false;}
      if(zkGoBQoOqc == true){zkGoBQoOqc = false;}
      if(TDWtqAGYVb == true){TDWtqAGYVb = false;}
      if(YizdRsAZpM == true){YizdRsAZpM = false;}
      if(ktbzRrExuu == true){ktbzRrExuu = false;}
      if(GVNbiVkNEn == true){GVNbiVkNEn = false;}
      if(xgKZNQkcWI == true){xgKZNQkcWI = false;}
      if(PPYeqZbXby == true){PPYeqZbXby = false;}
      if(uIdZVDVXtw == true){uIdZVDVXtw = false;}
      if(HmUBPEiBkB == true){HmUBPEiBkB = false;}
      if(GbalepwhjI == true){GbalepwhjI = false;}
      if(sNkGrnDkEJ == true){sNkGrnDkEJ = false;}
      if(tNhZActWPm == true){tNhZActWPm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFSXWDCRTW
{ 
  void CFFGVdZxbP()
  { 
      bool iPgxDRjkum = false;
      bool GRMkhnAOdm = false;
      bool uXXzAtUgjw = false;
      bool VMGxmnxJlQ = false;
      bool PccUulPije = false;
      bool tFrLfKqgwJ = false;
      bool xCByRsKPyt = false;
      bool qpcNWRtDDO = false;
      bool dkwFBQTuQb = false;
      bool xPNcSMbeCC = false;
      bool aAkpmDbeoO = false;
      bool QmdheMFuwB = false;
      bool YPyVwbcAtJ = false;
      bool pPABmczGSx = false;
      bool noGBLJlexG = false;
      bool GghBcLBPtL = false;
      bool abkeYAmbuB = false;
      bool MzcyNjJwJm = false;
      bool oxCnCIhzYa = false;
      bool bjMGWLDacL = false;
      string BmdziIkndA;
      string yDJAWYDGer;
      string OJogIIOgqc;
      string joBIqjKRKE;
      string cmdxCJQEuz;
      string ONuQyryxqZ;
      string tDxBQJCBIm;
      string NluaOaeqey;
      string rJkqNVtjJy;
      string kNZkKYpbgs;
      string HPuIlcSUBX;
      string MGRrhjRFmt;
      string PRqKBzLKPp;
      string kDKlqbNcFj;
      string DYhlkeuhCZ;
      string HjnldoXkHl;
      string RIELmJwfBF;
      string WoADqpiFYV;
      string DdHohAOXIB;
      string EbUSSuUVyb;
      if(BmdziIkndA == HPuIlcSUBX){iPgxDRjkum = true;}
      else if(HPuIlcSUBX == BmdziIkndA){aAkpmDbeoO = true;}
      if(yDJAWYDGer == MGRrhjRFmt){GRMkhnAOdm = true;}
      else if(MGRrhjRFmt == yDJAWYDGer){QmdheMFuwB = true;}
      if(OJogIIOgqc == PRqKBzLKPp){uXXzAtUgjw = true;}
      else if(PRqKBzLKPp == OJogIIOgqc){YPyVwbcAtJ = true;}
      if(joBIqjKRKE == kDKlqbNcFj){VMGxmnxJlQ = true;}
      else if(kDKlqbNcFj == joBIqjKRKE){pPABmczGSx = true;}
      if(cmdxCJQEuz == DYhlkeuhCZ){PccUulPije = true;}
      else if(DYhlkeuhCZ == cmdxCJQEuz){noGBLJlexG = true;}
      if(ONuQyryxqZ == HjnldoXkHl){tFrLfKqgwJ = true;}
      else if(HjnldoXkHl == ONuQyryxqZ){GghBcLBPtL = true;}
      if(tDxBQJCBIm == RIELmJwfBF){xCByRsKPyt = true;}
      else if(RIELmJwfBF == tDxBQJCBIm){abkeYAmbuB = true;}
      if(NluaOaeqey == WoADqpiFYV){qpcNWRtDDO = true;}
      if(rJkqNVtjJy == DdHohAOXIB){dkwFBQTuQb = true;}
      if(kNZkKYpbgs == EbUSSuUVyb){xPNcSMbeCC = true;}
      while(WoADqpiFYV == NluaOaeqey){MzcyNjJwJm = true;}
      while(DdHohAOXIB == DdHohAOXIB){oxCnCIhzYa = true;}
      while(EbUSSuUVyb == EbUSSuUVyb){bjMGWLDacL = true;}
      if(iPgxDRjkum == true){iPgxDRjkum = false;}
      if(GRMkhnAOdm == true){GRMkhnAOdm = false;}
      if(uXXzAtUgjw == true){uXXzAtUgjw = false;}
      if(VMGxmnxJlQ == true){VMGxmnxJlQ = false;}
      if(PccUulPije == true){PccUulPije = false;}
      if(tFrLfKqgwJ == true){tFrLfKqgwJ = false;}
      if(xCByRsKPyt == true){xCByRsKPyt = false;}
      if(qpcNWRtDDO == true){qpcNWRtDDO = false;}
      if(dkwFBQTuQb == true){dkwFBQTuQb = false;}
      if(xPNcSMbeCC == true){xPNcSMbeCC = false;}
      if(aAkpmDbeoO == true){aAkpmDbeoO = false;}
      if(QmdheMFuwB == true){QmdheMFuwB = false;}
      if(YPyVwbcAtJ == true){YPyVwbcAtJ = false;}
      if(pPABmczGSx == true){pPABmczGSx = false;}
      if(noGBLJlexG == true){noGBLJlexG = false;}
      if(GghBcLBPtL == true){GghBcLBPtL = false;}
      if(abkeYAmbuB == true){abkeYAmbuB = false;}
      if(MzcyNjJwJm == true){MzcyNjJwJm = false;}
      if(oxCnCIhzYa == true){oxCnCIhzYa = false;}
      if(bjMGWLDacL == true){bjMGWLDacL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWDAIRJGDW
{ 
  void GGFadwmPZQ()
  { 
      bool LMTtgUUqAj = false;
      bool jpIVOqQHZo = false;
      bool poRRQMLuTT = false;
      bool BJCXBVWEfT = false;
      bool QCnwZNjuxl = false;
      bool aewshVtBcU = false;
      bool IYWfiamjUr = false;
      bool TMbGXnAVqD = false;
      bool bQxhsWMJpe = false;
      bool bUbLKreIMz = false;
      bool ZzaFROCoUs = false;
      bool UYKYsranmM = false;
      bool NdtoQzjQwf = false;
      bool JrIrdbprQe = false;
      bool TWnwJCKCRS = false;
      bool QpUzkuFkoS = false;
      bool dlsnjcPRuR = false;
      bool CiXHsqoyfN = false;
      bool nhycOSWJHh = false;
      bool WEDyAgcALg = false;
      string OdqKSPHURA;
      string GGtIDAposA;
      string UPSOySCtCe;
      string sjAyafqHND;
      string mMjmooRrJA;
      string BGJNyyKbLA;
      string NNSlGVFugX;
      string IhboMIffYJ;
      string BJkBdmamAb;
      string UOwNpZtxfT;
      string iWKkqSeTBp;
      string SeDBzDbRIT;
      string uSuFCtkNzl;
      string OhAFZdyzJK;
      string IHlKIpKtOl;
      string xboLYQaFhx;
      string hQUObjdyaU;
      string FcHxLnfkwM;
      string ipzMnlsngJ;
      string DsQLcrlWiY;
      if(OdqKSPHURA == iWKkqSeTBp){LMTtgUUqAj = true;}
      else if(iWKkqSeTBp == OdqKSPHURA){ZzaFROCoUs = true;}
      if(GGtIDAposA == SeDBzDbRIT){jpIVOqQHZo = true;}
      else if(SeDBzDbRIT == GGtIDAposA){UYKYsranmM = true;}
      if(UPSOySCtCe == uSuFCtkNzl){poRRQMLuTT = true;}
      else if(uSuFCtkNzl == UPSOySCtCe){NdtoQzjQwf = true;}
      if(sjAyafqHND == OhAFZdyzJK){BJCXBVWEfT = true;}
      else if(OhAFZdyzJK == sjAyafqHND){JrIrdbprQe = true;}
      if(mMjmooRrJA == IHlKIpKtOl){QCnwZNjuxl = true;}
      else if(IHlKIpKtOl == mMjmooRrJA){TWnwJCKCRS = true;}
      if(BGJNyyKbLA == xboLYQaFhx){aewshVtBcU = true;}
      else if(xboLYQaFhx == BGJNyyKbLA){QpUzkuFkoS = true;}
      if(NNSlGVFugX == hQUObjdyaU){IYWfiamjUr = true;}
      else if(hQUObjdyaU == NNSlGVFugX){dlsnjcPRuR = true;}
      if(IhboMIffYJ == FcHxLnfkwM){TMbGXnAVqD = true;}
      if(BJkBdmamAb == ipzMnlsngJ){bQxhsWMJpe = true;}
      if(UOwNpZtxfT == DsQLcrlWiY){bUbLKreIMz = true;}
      while(FcHxLnfkwM == IhboMIffYJ){CiXHsqoyfN = true;}
      while(ipzMnlsngJ == ipzMnlsngJ){nhycOSWJHh = true;}
      while(DsQLcrlWiY == DsQLcrlWiY){WEDyAgcALg = true;}
      if(LMTtgUUqAj == true){LMTtgUUqAj = false;}
      if(jpIVOqQHZo == true){jpIVOqQHZo = false;}
      if(poRRQMLuTT == true){poRRQMLuTT = false;}
      if(BJCXBVWEfT == true){BJCXBVWEfT = false;}
      if(QCnwZNjuxl == true){QCnwZNjuxl = false;}
      if(aewshVtBcU == true){aewshVtBcU = false;}
      if(IYWfiamjUr == true){IYWfiamjUr = false;}
      if(TMbGXnAVqD == true){TMbGXnAVqD = false;}
      if(bQxhsWMJpe == true){bQxhsWMJpe = false;}
      if(bUbLKreIMz == true){bUbLKreIMz = false;}
      if(ZzaFROCoUs == true){ZzaFROCoUs = false;}
      if(UYKYsranmM == true){UYKYsranmM = false;}
      if(NdtoQzjQwf == true){NdtoQzjQwf = false;}
      if(JrIrdbprQe == true){JrIrdbprQe = false;}
      if(TWnwJCKCRS == true){TWnwJCKCRS = false;}
      if(QpUzkuFkoS == true){QpUzkuFkoS = false;}
      if(dlsnjcPRuR == true){dlsnjcPRuR = false;}
      if(CiXHsqoyfN == true){CiXHsqoyfN = false;}
      if(nhycOSWJHh == true){nhycOSWJHh = false;}
      if(WEDyAgcALg == true){WEDyAgcALg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRTDIMIYWZ
{ 
  void ySXiLnHkLV()
  { 
      bool HAJuOWFOKg = false;
      bool aCSjAcRomi = false;
      bool jiPXcVGwpp = false;
      bool pfFTafrMlT = false;
      bool TlTdQZpuHb = false;
      bool jwjqhXkkSs = false;
      bool PJXUpuwyIU = false;
      bool jECSOyPkGC = false;
      bool fKoNFsuNkD = false;
      bool uGtsDKOymV = false;
      bool dqmlqetRcj = false;
      bool IzePNETJOx = false;
      bool AhMFZdKJPD = false;
      bool iQyjXnXCWa = false;
      bool zdkBuwbdfy = false;
      bool pEjpVwdgMN = false;
      bool UjBYBqAtqY = false;
      bool gRmnxWxLJc = false;
      bool BfcQNegIOb = false;
      bool JppIFObLzE = false;
      string zztIUSOQxF;
      string OgtoaWoSow;
      string NEDSRuHIsf;
      string YrAEuJwCqB;
      string BaFCkOmrmP;
      string qMaWdtubpY;
      string KGXRfWgosQ;
      string ambmtmyBhD;
      string IOUdnMQcZA;
      string NTLRpuDnVO;
      string gxyVnEjmcq;
      string wsslQulsdT;
      string FDOrDGaJwz;
      string iKfTVKPzoi;
      string bcAiEUaZBu;
      string JJJCIdhGSg;
      string daqcIkNZPF;
      string flEuqbDfmh;
      string fBIBpZBdKr;
      string bJfIEBlWZS;
      if(zztIUSOQxF == gxyVnEjmcq){HAJuOWFOKg = true;}
      else if(gxyVnEjmcq == zztIUSOQxF){dqmlqetRcj = true;}
      if(OgtoaWoSow == wsslQulsdT){aCSjAcRomi = true;}
      else if(wsslQulsdT == OgtoaWoSow){IzePNETJOx = true;}
      if(NEDSRuHIsf == FDOrDGaJwz){jiPXcVGwpp = true;}
      else if(FDOrDGaJwz == NEDSRuHIsf){AhMFZdKJPD = true;}
      if(YrAEuJwCqB == iKfTVKPzoi){pfFTafrMlT = true;}
      else if(iKfTVKPzoi == YrAEuJwCqB){iQyjXnXCWa = true;}
      if(BaFCkOmrmP == bcAiEUaZBu){TlTdQZpuHb = true;}
      else if(bcAiEUaZBu == BaFCkOmrmP){zdkBuwbdfy = true;}
      if(qMaWdtubpY == JJJCIdhGSg){jwjqhXkkSs = true;}
      else if(JJJCIdhGSg == qMaWdtubpY){pEjpVwdgMN = true;}
      if(KGXRfWgosQ == daqcIkNZPF){PJXUpuwyIU = true;}
      else if(daqcIkNZPF == KGXRfWgosQ){UjBYBqAtqY = true;}
      if(ambmtmyBhD == flEuqbDfmh){jECSOyPkGC = true;}
      if(IOUdnMQcZA == fBIBpZBdKr){fKoNFsuNkD = true;}
      if(NTLRpuDnVO == bJfIEBlWZS){uGtsDKOymV = true;}
      while(flEuqbDfmh == ambmtmyBhD){gRmnxWxLJc = true;}
      while(fBIBpZBdKr == fBIBpZBdKr){BfcQNegIOb = true;}
      while(bJfIEBlWZS == bJfIEBlWZS){JppIFObLzE = true;}
      if(HAJuOWFOKg == true){HAJuOWFOKg = false;}
      if(aCSjAcRomi == true){aCSjAcRomi = false;}
      if(jiPXcVGwpp == true){jiPXcVGwpp = false;}
      if(pfFTafrMlT == true){pfFTafrMlT = false;}
      if(TlTdQZpuHb == true){TlTdQZpuHb = false;}
      if(jwjqhXkkSs == true){jwjqhXkkSs = false;}
      if(PJXUpuwyIU == true){PJXUpuwyIU = false;}
      if(jECSOyPkGC == true){jECSOyPkGC = false;}
      if(fKoNFsuNkD == true){fKoNFsuNkD = false;}
      if(uGtsDKOymV == true){uGtsDKOymV = false;}
      if(dqmlqetRcj == true){dqmlqetRcj = false;}
      if(IzePNETJOx == true){IzePNETJOx = false;}
      if(AhMFZdKJPD == true){AhMFZdKJPD = false;}
      if(iQyjXnXCWa == true){iQyjXnXCWa = false;}
      if(zdkBuwbdfy == true){zdkBuwbdfy = false;}
      if(pEjpVwdgMN == true){pEjpVwdgMN = false;}
      if(UjBYBqAtqY == true){UjBYBqAtqY = false;}
      if(gRmnxWxLJc == true){gRmnxWxLJc = false;}
      if(BfcQNegIOb == true){BfcQNegIOb = false;}
      if(JppIFObLzE == true){JppIFObLzE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPCFFSQYUS
{ 
  void tbPJOxOeyV()
  { 
      bool UmDfiVuhLp = false;
      bool FfLiagwDRy = false;
      bool mnRHBMyEYy = false;
      bool XEyGmLatbq = false;
      bool robBuiLBoc = false;
      bool WAYjifVweV = false;
      bool WqJNSAhFuP = false;
      bool FCbaFxMPMR = false;
      bool BwOwaWeNWG = false;
      bool oePFTBfOit = false;
      bool BGFZWTXyek = false;
      bool TFiNUZbMlw = false;
      bool UUhoZamWGD = false;
      bool QygSPupnZG = false;
      bool yghlmjuCjs = false;
      bool ZTbmYgXQAu = false;
      bool gBqbTVYQxZ = false;
      bool inmexnlwBp = false;
      bool fjlMdxVtsi = false;
      bool WZndYxoGRR = false;
      string VgmxAtlYSn;
      string DbqgfaMlHY;
      string fKjsTQsHzo;
      string swseqlLzYP;
      string sAzgUAZlml;
      string QHjbUKwsci;
      string BdYctHhLos;
      string PNMqfeKDXT;
      string pHUNYlLRKf;
      string oSVoNOaVlN;
      string RNwsWDtrwo;
      string zsUJstJLEI;
      string uQBIDwqWdR;
      string DoQKBbKaqV;
      string qSUUfwxMwS;
      string EPRcSAMmpZ;
      string LWOdlKbJIQ;
      string jiUiRbugbH;
      string zeZKMnXmrA;
      string PWjQJTEqiV;
      if(VgmxAtlYSn == RNwsWDtrwo){UmDfiVuhLp = true;}
      else if(RNwsWDtrwo == VgmxAtlYSn){BGFZWTXyek = true;}
      if(DbqgfaMlHY == zsUJstJLEI){FfLiagwDRy = true;}
      else if(zsUJstJLEI == DbqgfaMlHY){TFiNUZbMlw = true;}
      if(fKjsTQsHzo == uQBIDwqWdR){mnRHBMyEYy = true;}
      else if(uQBIDwqWdR == fKjsTQsHzo){UUhoZamWGD = true;}
      if(swseqlLzYP == DoQKBbKaqV){XEyGmLatbq = true;}
      else if(DoQKBbKaqV == swseqlLzYP){QygSPupnZG = true;}
      if(sAzgUAZlml == qSUUfwxMwS){robBuiLBoc = true;}
      else if(qSUUfwxMwS == sAzgUAZlml){yghlmjuCjs = true;}
      if(QHjbUKwsci == EPRcSAMmpZ){WAYjifVweV = true;}
      else if(EPRcSAMmpZ == QHjbUKwsci){ZTbmYgXQAu = true;}
      if(BdYctHhLos == LWOdlKbJIQ){WqJNSAhFuP = true;}
      else if(LWOdlKbJIQ == BdYctHhLos){gBqbTVYQxZ = true;}
      if(PNMqfeKDXT == jiUiRbugbH){FCbaFxMPMR = true;}
      if(pHUNYlLRKf == zeZKMnXmrA){BwOwaWeNWG = true;}
      if(oSVoNOaVlN == PWjQJTEqiV){oePFTBfOit = true;}
      while(jiUiRbugbH == PNMqfeKDXT){inmexnlwBp = true;}
      while(zeZKMnXmrA == zeZKMnXmrA){fjlMdxVtsi = true;}
      while(PWjQJTEqiV == PWjQJTEqiV){WZndYxoGRR = true;}
      if(UmDfiVuhLp == true){UmDfiVuhLp = false;}
      if(FfLiagwDRy == true){FfLiagwDRy = false;}
      if(mnRHBMyEYy == true){mnRHBMyEYy = false;}
      if(XEyGmLatbq == true){XEyGmLatbq = false;}
      if(robBuiLBoc == true){robBuiLBoc = false;}
      if(WAYjifVweV == true){WAYjifVweV = false;}
      if(WqJNSAhFuP == true){WqJNSAhFuP = false;}
      if(FCbaFxMPMR == true){FCbaFxMPMR = false;}
      if(BwOwaWeNWG == true){BwOwaWeNWG = false;}
      if(oePFTBfOit == true){oePFTBfOit = false;}
      if(BGFZWTXyek == true){BGFZWTXyek = false;}
      if(TFiNUZbMlw == true){TFiNUZbMlw = false;}
      if(UUhoZamWGD == true){UUhoZamWGD = false;}
      if(QygSPupnZG == true){QygSPupnZG = false;}
      if(yghlmjuCjs == true){yghlmjuCjs = false;}
      if(ZTbmYgXQAu == true){ZTbmYgXQAu = false;}
      if(gBqbTVYQxZ == true){gBqbTVYQxZ = false;}
      if(inmexnlwBp == true){inmexnlwBp = false;}
      if(fjlMdxVtsi == true){fjlMdxVtsi = false;}
      if(WZndYxoGRR == true){WZndYxoGRR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VXGEDMMBZC
{ 
  void PiihchcKws()
  { 
      bool rnWRAVUHVD = false;
      bool KNYKgajcto = false;
      bool wEQkJRCmLV = false;
      bool MZBUUtlsrn = false;
      bool sbxfHzWrSw = false;
      bool yufLonXkIi = false;
      bool TguApkMDpm = false;
      bool nqkGuTGjdK = false;
      bool tJTOWQsoff = false;
      bool WBjJTMfwpV = false;
      bool lSCfIHKZPU = false;
      bool gmHxnJNgdY = false;
      bool rXXJQmGami = false;
      bool mKtIXaHmFO = false;
      bool GTYKzitmUK = false;
      bool yzSQdOusPV = false;
      bool BimggWsyZM = false;
      bool CZaOSXyMJg = false;
      bool rSGbjnqddI = false;
      bool fNXjNWgrdc = false;
      string bnlghnFrJZ;
      string TRjgTSKygP;
      string JLSTZXWtgp;
      string ROLsmFfQDU;
      string TYCQaARtQa;
      string NqpmLPUSHJ;
      string QKLTIFFqsO;
      string lsuLwjJCsY;
      string GbdFbZYXgW;
      string jNJsEJNhIU;
      string taBCoUwdqa;
      string GSYiDogFqh;
      string fhJVdXjBHl;
      string WatXeeaaQH;
      string dtfGQQoapO;
      string bIqZnMReXQ;
      string juVFEfYADX;
      string NFniEkBDFN;
      string iJLsKOjTiS;
      string NwDAXhYaBk;
      if(bnlghnFrJZ == taBCoUwdqa){rnWRAVUHVD = true;}
      else if(taBCoUwdqa == bnlghnFrJZ){lSCfIHKZPU = true;}
      if(TRjgTSKygP == GSYiDogFqh){KNYKgajcto = true;}
      else if(GSYiDogFqh == TRjgTSKygP){gmHxnJNgdY = true;}
      if(JLSTZXWtgp == fhJVdXjBHl){wEQkJRCmLV = true;}
      else if(fhJVdXjBHl == JLSTZXWtgp){rXXJQmGami = true;}
      if(ROLsmFfQDU == WatXeeaaQH){MZBUUtlsrn = true;}
      else if(WatXeeaaQH == ROLsmFfQDU){mKtIXaHmFO = true;}
      if(TYCQaARtQa == dtfGQQoapO){sbxfHzWrSw = true;}
      else if(dtfGQQoapO == TYCQaARtQa){GTYKzitmUK = true;}
      if(NqpmLPUSHJ == bIqZnMReXQ){yufLonXkIi = true;}
      else if(bIqZnMReXQ == NqpmLPUSHJ){yzSQdOusPV = true;}
      if(QKLTIFFqsO == juVFEfYADX){TguApkMDpm = true;}
      else if(juVFEfYADX == QKLTIFFqsO){BimggWsyZM = true;}
      if(lsuLwjJCsY == NFniEkBDFN){nqkGuTGjdK = true;}
      if(GbdFbZYXgW == iJLsKOjTiS){tJTOWQsoff = true;}
      if(jNJsEJNhIU == NwDAXhYaBk){WBjJTMfwpV = true;}
      while(NFniEkBDFN == lsuLwjJCsY){CZaOSXyMJg = true;}
      while(iJLsKOjTiS == iJLsKOjTiS){rSGbjnqddI = true;}
      while(NwDAXhYaBk == NwDAXhYaBk){fNXjNWgrdc = true;}
      if(rnWRAVUHVD == true){rnWRAVUHVD = false;}
      if(KNYKgajcto == true){KNYKgajcto = false;}
      if(wEQkJRCmLV == true){wEQkJRCmLV = false;}
      if(MZBUUtlsrn == true){MZBUUtlsrn = false;}
      if(sbxfHzWrSw == true){sbxfHzWrSw = false;}
      if(yufLonXkIi == true){yufLonXkIi = false;}
      if(TguApkMDpm == true){TguApkMDpm = false;}
      if(nqkGuTGjdK == true){nqkGuTGjdK = false;}
      if(tJTOWQsoff == true){tJTOWQsoff = false;}
      if(WBjJTMfwpV == true){WBjJTMfwpV = false;}
      if(lSCfIHKZPU == true){lSCfIHKZPU = false;}
      if(gmHxnJNgdY == true){gmHxnJNgdY = false;}
      if(rXXJQmGami == true){rXXJQmGami = false;}
      if(mKtIXaHmFO == true){mKtIXaHmFO = false;}
      if(GTYKzitmUK == true){GTYKzitmUK = false;}
      if(yzSQdOusPV == true){yzSQdOusPV = false;}
      if(BimggWsyZM == true){BimggWsyZM = false;}
      if(CZaOSXyMJg == true){CZaOSXyMJg = false;}
      if(rSGbjnqddI == true){rSGbjnqddI = false;}
      if(fNXjNWgrdc == true){fNXjNWgrdc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PXIMMNSIKU
{ 
  void zreGSCREYi()
  { 
      bool rKBWVBOSEE = false;
      bool FQWLWDsuwh = false;
      bool FYuZXuujYS = false;
      bool ZACDLEcbCQ = false;
      bool kMWYVynQjL = false;
      bool rhldjSPaza = false;
      bool FeskeFNTzS = false;
      bool ZQrfxrBVEY = false;
      bool GezNaqNYSr = false;
      bool oBcbLFTltP = false;
      bool kTQRkapGgr = false;
      bool QsWZTafeKm = false;
      bool qoBGdXmPTq = false;
      bool YPbnnlNgbz = false;
      bool AHrabueDHk = false;
      bool ZnbGYwSKnM = false;
      bool mZmoSBRikh = false;
      bool MyDKmjwaeh = false;
      bool sjIhQjnUOr = false;
      bool TDrPMaUCHZ = false;
      string TAYIkFPdZF;
      string YcOQVmgTSn;
      string NRkVzQLuKc;
      string oDpXzsudOF;
      string INnIcKfApd;
      string RHjkoBOCIU;
      string sUTwQUlqQc;
      string qDENeAdcso;
      string jKFgLgTEix;
      string erVtLnsqrI;
      string XoiNlOCVGn;
      string WkJSjhPmki;
      string AhISxzgKBq;
      string GlkkRubquw;
      string dxytasiCKc;
      string YGGIHofPPm;
      string hrTOhkAYBn;
      string GXrnEDiOrE;
      string PdzYRzebcb;
      string PLbHOkdiLo;
      if(TAYIkFPdZF == XoiNlOCVGn){rKBWVBOSEE = true;}
      else if(XoiNlOCVGn == TAYIkFPdZF){kTQRkapGgr = true;}
      if(YcOQVmgTSn == WkJSjhPmki){FQWLWDsuwh = true;}
      else if(WkJSjhPmki == YcOQVmgTSn){QsWZTafeKm = true;}
      if(NRkVzQLuKc == AhISxzgKBq){FYuZXuujYS = true;}
      else if(AhISxzgKBq == NRkVzQLuKc){qoBGdXmPTq = true;}
      if(oDpXzsudOF == GlkkRubquw){ZACDLEcbCQ = true;}
      else if(GlkkRubquw == oDpXzsudOF){YPbnnlNgbz = true;}
      if(INnIcKfApd == dxytasiCKc){kMWYVynQjL = true;}
      else if(dxytasiCKc == INnIcKfApd){AHrabueDHk = true;}
      if(RHjkoBOCIU == YGGIHofPPm){rhldjSPaza = true;}
      else if(YGGIHofPPm == RHjkoBOCIU){ZnbGYwSKnM = true;}
      if(sUTwQUlqQc == hrTOhkAYBn){FeskeFNTzS = true;}
      else if(hrTOhkAYBn == sUTwQUlqQc){mZmoSBRikh = true;}
      if(qDENeAdcso == GXrnEDiOrE){ZQrfxrBVEY = true;}
      if(jKFgLgTEix == PdzYRzebcb){GezNaqNYSr = true;}
      if(erVtLnsqrI == PLbHOkdiLo){oBcbLFTltP = true;}
      while(GXrnEDiOrE == qDENeAdcso){MyDKmjwaeh = true;}
      while(PdzYRzebcb == PdzYRzebcb){sjIhQjnUOr = true;}
      while(PLbHOkdiLo == PLbHOkdiLo){TDrPMaUCHZ = true;}
      if(rKBWVBOSEE == true){rKBWVBOSEE = false;}
      if(FQWLWDsuwh == true){FQWLWDsuwh = false;}
      if(FYuZXuujYS == true){FYuZXuujYS = false;}
      if(ZACDLEcbCQ == true){ZACDLEcbCQ = false;}
      if(kMWYVynQjL == true){kMWYVynQjL = false;}
      if(rhldjSPaza == true){rhldjSPaza = false;}
      if(FeskeFNTzS == true){FeskeFNTzS = false;}
      if(ZQrfxrBVEY == true){ZQrfxrBVEY = false;}
      if(GezNaqNYSr == true){GezNaqNYSr = false;}
      if(oBcbLFTltP == true){oBcbLFTltP = false;}
      if(kTQRkapGgr == true){kTQRkapGgr = false;}
      if(QsWZTafeKm == true){QsWZTafeKm = false;}
      if(qoBGdXmPTq == true){qoBGdXmPTq = false;}
      if(YPbnnlNgbz == true){YPbnnlNgbz = false;}
      if(AHrabueDHk == true){AHrabueDHk = false;}
      if(ZnbGYwSKnM == true){ZnbGYwSKnM = false;}
      if(mZmoSBRikh == true){mZmoSBRikh = false;}
      if(MyDKmjwaeh == true){MyDKmjwaeh = false;}
      if(sjIhQjnUOr == true){sjIhQjnUOr = false;}
      if(TDrPMaUCHZ == true){TDrPMaUCHZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUPLEZCJSI
{ 
  void UKaqYldxIu()
  { 
      bool kCYDrAfmTe = false;
      bool CdgzscRwAi = false;
      bool tpALVOrdEA = false;
      bool tcorXFPmbp = false;
      bool OBSXXqMpVg = false;
      bool GWgXbtCNgd = false;
      bool HBhSjZnnam = false;
      bool MdUJTrWcme = false;
      bool BBHXtXwQQd = false;
      bool DBGyiMTzmy = false;
      bool CYPhTcBWDi = false;
      bool WZaCbFsJYM = false;
      bool cXXxjKWWaH = false;
      bool YWonbclZER = false;
      bool VYNgGcaEVc = false;
      bool SJaaVeBRyI = false;
      bool FewwJAjlZy = false;
      bool TTFHpEJpqG = false;
      bool jSAynOwNSw = false;
      bool bTbuLpcQWG = false;
      string RtwiIdQRhW;
      string JaykGLqneN;
      string mKIHRUXGUy;
      string okxjlKrEUH;
      string YhbeScTPbk;
      string FNLFCHlnQm;
      string GKwjgYcNzu;
      string SmSWnFhcoo;
      string AHdjsbYqgd;
      string XEmgAOkrxs;
      string zFQfRRtnRx;
      string YIyblzfMpF;
      string zkfUXOAlWZ;
      string TpewoupySb;
      string gkZjFOFLuB;
      string hYBrsNZwIC;
      string RIRrcidClq;
      string IhsOYOLwPJ;
      string InqUqtnmCa;
      string UtoPJXThGW;
      if(RtwiIdQRhW == zFQfRRtnRx){kCYDrAfmTe = true;}
      else if(zFQfRRtnRx == RtwiIdQRhW){CYPhTcBWDi = true;}
      if(JaykGLqneN == YIyblzfMpF){CdgzscRwAi = true;}
      else if(YIyblzfMpF == JaykGLqneN){WZaCbFsJYM = true;}
      if(mKIHRUXGUy == zkfUXOAlWZ){tpALVOrdEA = true;}
      else if(zkfUXOAlWZ == mKIHRUXGUy){cXXxjKWWaH = true;}
      if(okxjlKrEUH == TpewoupySb){tcorXFPmbp = true;}
      else if(TpewoupySb == okxjlKrEUH){YWonbclZER = true;}
      if(YhbeScTPbk == gkZjFOFLuB){OBSXXqMpVg = true;}
      else if(gkZjFOFLuB == YhbeScTPbk){VYNgGcaEVc = true;}
      if(FNLFCHlnQm == hYBrsNZwIC){GWgXbtCNgd = true;}
      else if(hYBrsNZwIC == FNLFCHlnQm){SJaaVeBRyI = true;}
      if(GKwjgYcNzu == RIRrcidClq){HBhSjZnnam = true;}
      else if(RIRrcidClq == GKwjgYcNzu){FewwJAjlZy = true;}
      if(SmSWnFhcoo == IhsOYOLwPJ){MdUJTrWcme = true;}
      if(AHdjsbYqgd == InqUqtnmCa){BBHXtXwQQd = true;}
      if(XEmgAOkrxs == UtoPJXThGW){DBGyiMTzmy = true;}
      while(IhsOYOLwPJ == SmSWnFhcoo){TTFHpEJpqG = true;}
      while(InqUqtnmCa == InqUqtnmCa){jSAynOwNSw = true;}
      while(UtoPJXThGW == UtoPJXThGW){bTbuLpcQWG = true;}
      if(kCYDrAfmTe == true){kCYDrAfmTe = false;}
      if(CdgzscRwAi == true){CdgzscRwAi = false;}
      if(tpALVOrdEA == true){tpALVOrdEA = false;}
      if(tcorXFPmbp == true){tcorXFPmbp = false;}
      if(OBSXXqMpVg == true){OBSXXqMpVg = false;}
      if(GWgXbtCNgd == true){GWgXbtCNgd = false;}
      if(HBhSjZnnam == true){HBhSjZnnam = false;}
      if(MdUJTrWcme == true){MdUJTrWcme = false;}
      if(BBHXtXwQQd == true){BBHXtXwQQd = false;}
      if(DBGyiMTzmy == true){DBGyiMTzmy = false;}
      if(CYPhTcBWDi == true){CYPhTcBWDi = false;}
      if(WZaCbFsJYM == true){WZaCbFsJYM = false;}
      if(cXXxjKWWaH == true){cXXxjKWWaH = false;}
      if(YWonbclZER == true){YWonbclZER = false;}
      if(VYNgGcaEVc == true){VYNgGcaEVc = false;}
      if(SJaaVeBRyI == true){SJaaVeBRyI = false;}
      if(FewwJAjlZy == true){FewwJAjlZy = false;}
      if(TTFHpEJpqG == true){TTFHpEJpqG = false;}
      if(jSAynOwNSw == true){jSAynOwNSw = false;}
      if(bTbuLpcQWG == true){bTbuLpcQWG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEHMLETPQU
{ 
  void rkUuFMNSLS()
  { 
      bool EgasLMciCp = false;
      bool hTtHNWWIed = false;
      bool BxNIynXHwz = false;
      bool TPsmsiQIsK = false;
      bool erptzhTAoi = false;
      bool qrgkIHTRtW = false;
      bool nVmCVRaGNe = false;
      bool FOOTyJGSJP = false;
      bool UWRMIbiHdl = false;
      bool PzOWVIEnXh = false;
      bool HNmKcccMlz = false;
      bool AAIdCRDatt = false;
      bool hScbOGAryo = false;
      bool EStaIGjHje = false;
      bool yWVdkOpjTD = false;
      bool EcsdzojKuV = false;
      bool ckNwthFgVu = false;
      bool gwqOwLwypz = false;
      bool QPXtkaZQbS = false;
      bool WYLNCMIYjD = false;
      string EnqdeGYIrL;
      string xXlzVdgkBK;
      string KtJJGnSLGb;
      string ATDumcHWPK;
      string DhYeVRamtx;
      string hpXYLKehWq;
      string nNBPLcTqLr;
      string WJUpGcUdmo;
      string MfQIsJueib;
      string xZzYWpfITr;
      string yiaBaYVgRi;
      string oBthdHwrWC;
      string hnIjtwJwTQ;
      string wMKuqcFPhU;
      string nNMAmwfRtO;
      string snkQKJaqGe;
      string OYNBlcqyqA;
      string CgKBOTbHxy;
      string QrCFWIaskh;
      string CNIDFOALOJ;
      if(EnqdeGYIrL == yiaBaYVgRi){EgasLMciCp = true;}
      else if(yiaBaYVgRi == EnqdeGYIrL){HNmKcccMlz = true;}
      if(xXlzVdgkBK == oBthdHwrWC){hTtHNWWIed = true;}
      else if(oBthdHwrWC == xXlzVdgkBK){AAIdCRDatt = true;}
      if(KtJJGnSLGb == hnIjtwJwTQ){BxNIynXHwz = true;}
      else if(hnIjtwJwTQ == KtJJGnSLGb){hScbOGAryo = true;}
      if(ATDumcHWPK == wMKuqcFPhU){TPsmsiQIsK = true;}
      else if(wMKuqcFPhU == ATDumcHWPK){EStaIGjHje = true;}
      if(DhYeVRamtx == nNMAmwfRtO){erptzhTAoi = true;}
      else if(nNMAmwfRtO == DhYeVRamtx){yWVdkOpjTD = true;}
      if(hpXYLKehWq == snkQKJaqGe){qrgkIHTRtW = true;}
      else if(snkQKJaqGe == hpXYLKehWq){EcsdzojKuV = true;}
      if(nNBPLcTqLr == OYNBlcqyqA){nVmCVRaGNe = true;}
      else if(OYNBlcqyqA == nNBPLcTqLr){ckNwthFgVu = true;}
      if(WJUpGcUdmo == CgKBOTbHxy){FOOTyJGSJP = true;}
      if(MfQIsJueib == QrCFWIaskh){UWRMIbiHdl = true;}
      if(xZzYWpfITr == CNIDFOALOJ){PzOWVIEnXh = true;}
      while(CgKBOTbHxy == WJUpGcUdmo){gwqOwLwypz = true;}
      while(QrCFWIaskh == QrCFWIaskh){QPXtkaZQbS = true;}
      while(CNIDFOALOJ == CNIDFOALOJ){WYLNCMIYjD = true;}
      if(EgasLMciCp == true){EgasLMciCp = false;}
      if(hTtHNWWIed == true){hTtHNWWIed = false;}
      if(BxNIynXHwz == true){BxNIynXHwz = false;}
      if(TPsmsiQIsK == true){TPsmsiQIsK = false;}
      if(erptzhTAoi == true){erptzhTAoi = false;}
      if(qrgkIHTRtW == true){qrgkIHTRtW = false;}
      if(nVmCVRaGNe == true){nVmCVRaGNe = false;}
      if(FOOTyJGSJP == true){FOOTyJGSJP = false;}
      if(UWRMIbiHdl == true){UWRMIbiHdl = false;}
      if(PzOWVIEnXh == true){PzOWVIEnXh = false;}
      if(HNmKcccMlz == true){HNmKcccMlz = false;}
      if(AAIdCRDatt == true){AAIdCRDatt = false;}
      if(hScbOGAryo == true){hScbOGAryo = false;}
      if(EStaIGjHje == true){EStaIGjHje = false;}
      if(yWVdkOpjTD == true){yWVdkOpjTD = false;}
      if(EcsdzojKuV == true){EcsdzojKuV = false;}
      if(ckNwthFgVu == true){ckNwthFgVu = false;}
      if(gwqOwLwypz == true){gwqOwLwypz = false;}
      if(QPXtkaZQbS == true){QPXtkaZQbS = false;}
      if(WYLNCMIYjD == true){WYLNCMIYjD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZRBWGSNYSO
{ 
  void kBmEticOjl()
  { 
      bool oiTeOiAcUi = false;
      bool zsaGwfjDkB = false;
      bool yoibRoblMa = false;
      bool HqLApkbiBt = false;
      bool rTGdNfGbWj = false;
      bool BwgXDzzrNZ = false;
      bool GNPsbHhZPK = false;
      bool EACqIehENk = false;
      bool hzOcYKJnxp = false;
      bool liVbmdDNCF = false;
      bool ygMLfAtpOX = false;
      bool RtdbqGymTQ = false;
      bool ysbYYUeaDe = false;
      bool aUCIlBmDxY = false;
      bool QTZZYqEsjf = false;
      bool eQskHEEmmK = false;
      bool VTliwwrVpp = false;
      bool TuouAdTCzh = false;
      bool PlpXzKbRAg = false;
      bool xzPlDwgpcc = false;
      string ZqnWPxIqTT;
      string JSMZIqdDVA;
      string jweMlhWhzb;
      string EnGyaqIEAx;
      string BnSsnNudoy;
      string ElwlncLajh;
      string aZqqOULNyQ;
      string hYDYzudlYY;
      string lrsBWSrTKx;
      string ehUSVawadT;
      string BhfXQfiXmr;
      string zZCLwigpUw;
      string bqDBkAEjDX;
      string yDIFWEMUjq;
      string jUgSyFfIWl;
      string tGGgqJddlQ;
      string ayUOswQxoq;
      string WLFcMHKkDf;
      string TuNQcrxaNM;
      string ZhiTPkASYC;
      if(ZqnWPxIqTT == BhfXQfiXmr){oiTeOiAcUi = true;}
      else if(BhfXQfiXmr == ZqnWPxIqTT){ygMLfAtpOX = true;}
      if(JSMZIqdDVA == zZCLwigpUw){zsaGwfjDkB = true;}
      else if(zZCLwigpUw == JSMZIqdDVA){RtdbqGymTQ = true;}
      if(jweMlhWhzb == bqDBkAEjDX){yoibRoblMa = true;}
      else if(bqDBkAEjDX == jweMlhWhzb){ysbYYUeaDe = true;}
      if(EnGyaqIEAx == yDIFWEMUjq){HqLApkbiBt = true;}
      else if(yDIFWEMUjq == EnGyaqIEAx){aUCIlBmDxY = true;}
      if(BnSsnNudoy == jUgSyFfIWl){rTGdNfGbWj = true;}
      else if(jUgSyFfIWl == BnSsnNudoy){QTZZYqEsjf = true;}
      if(ElwlncLajh == tGGgqJddlQ){BwgXDzzrNZ = true;}
      else if(tGGgqJddlQ == ElwlncLajh){eQskHEEmmK = true;}
      if(aZqqOULNyQ == ayUOswQxoq){GNPsbHhZPK = true;}
      else if(ayUOswQxoq == aZqqOULNyQ){VTliwwrVpp = true;}
      if(hYDYzudlYY == WLFcMHKkDf){EACqIehENk = true;}
      if(lrsBWSrTKx == TuNQcrxaNM){hzOcYKJnxp = true;}
      if(ehUSVawadT == ZhiTPkASYC){liVbmdDNCF = true;}
      while(WLFcMHKkDf == hYDYzudlYY){TuouAdTCzh = true;}
      while(TuNQcrxaNM == TuNQcrxaNM){PlpXzKbRAg = true;}
      while(ZhiTPkASYC == ZhiTPkASYC){xzPlDwgpcc = true;}
      if(oiTeOiAcUi == true){oiTeOiAcUi = false;}
      if(zsaGwfjDkB == true){zsaGwfjDkB = false;}
      if(yoibRoblMa == true){yoibRoblMa = false;}
      if(HqLApkbiBt == true){HqLApkbiBt = false;}
      if(rTGdNfGbWj == true){rTGdNfGbWj = false;}
      if(BwgXDzzrNZ == true){BwgXDzzrNZ = false;}
      if(GNPsbHhZPK == true){GNPsbHhZPK = false;}
      if(EACqIehENk == true){EACqIehENk = false;}
      if(hzOcYKJnxp == true){hzOcYKJnxp = false;}
      if(liVbmdDNCF == true){liVbmdDNCF = false;}
      if(ygMLfAtpOX == true){ygMLfAtpOX = false;}
      if(RtdbqGymTQ == true){RtdbqGymTQ = false;}
      if(ysbYYUeaDe == true){ysbYYUeaDe = false;}
      if(aUCIlBmDxY == true){aUCIlBmDxY = false;}
      if(QTZZYqEsjf == true){QTZZYqEsjf = false;}
      if(eQskHEEmmK == true){eQskHEEmmK = false;}
      if(VTliwwrVpp == true){VTliwwrVpp = false;}
      if(TuouAdTCzh == true){TuouAdTCzh = false;}
      if(PlpXzKbRAg == true){PlpXzKbRAg = false;}
      if(xzPlDwgpcc == true){xzPlDwgpcc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGQKRQFZLO
{ 
  void LSIWXcANnj()
  { 
      bool xZmbiumPYt = false;
      bool iIGOPmamOZ = false;
      bool HaFZLDTGfO = false;
      bool uRAfsKpllo = false;
      bool ObpmUaonQm = false;
      bool LCpNqVTNPf = false;
      bool bfiKyRIaUE = false;
      bool woAYLfjSEk = false;
      bool NfprDsalnX = false;
      bool pcVGNhrfoC = false;
      bool SOSLqVBRCL = false;
      bool kBIdSwpqGE = false;
      bool qVlxOTStKc = false;
      bool nEdBSyMdBg = false;
      bool qIjclnUrmR = false;
      bool rAYjLwbUxW = false;
      bool DHHYXgXGKT = false;
      bool iLpZNikJLZ = false;
      bool zaGskmespV = false;
      bool WrgdcjBLEE = false;
      string wFImbkzhMs;
      string rpQrywjAWS;
      string ICciGNDckL;
      string OxIqDylkOz;
      string SoUhIOcEjH;
      string JMkBWsbZfN;
      string hWwAeuhYnA;
      string JzlWzTgtZq;
      string kzrdCBLGTK;
      string VMEARwrUDN;
      string gDPjxKZNCD;
      string LhzncheSyc;
      string iaFddxtkFC;
      string aMpMKgiIfq;
      string ayEQynMQXi;
      string RZVaeFxlFA;
      string QoIzbyqmdu;
      string zVlGBkWoep;
      string jcNVkBqPgE;
      string iwCfaloEnz;
      if(wFImbkzhMs == gDPjxKZNCD){xZmbiumPYt = true;}
      else if(gDPjxKZNCD == wFImbkzhMs){SOSLqVBRCL = true;}
      if(rpQrywjAWS == LhzncheSyc){iIGOPmamOZ = true;}
      else if(LhzncheSyc == rpQrywjAWS){kBIdSwpqGE = true;}
      if(ICciGNDckL == iaFddxtkFC){HaFZLDTGfO = true;}
      else if(iaFddxtkFC == ICciGNDckL){qVlxOTStKc = true;}
      if(OxIqDylkOz == aMpMKgiIfq){uRAfsKpllo = true;}
      else if(aMpMKgiIfq == OxIqDylkOz){nEdBSyMdBg = true;}
      if(SoUhIOcEjH == ayEQynMQXi){ObpmUaonQm = true;}
      else if(ayEQynMQXi == SoUhIOcEjH){qIjclnUrmR = true;}
      if(JMkBWsbZfN == RZVaeFxlFA){LCpNqVTNPf = true;}
      else if(RZVaeFxlFA == JMkBWsbZfN){rAYjLwbUxW = true;}
      if(hWwAeuhYnA == QoIzbyqmdu){bfiKyRIaUE = true;}
      else if(QoIzbyqmdu == hWwAeuhYnA){DHHYXgXGKT = true;}
      if(JzlWzTgtZq == zVlGBkWoep){woAYLfjSEk = true;}
      if(kzrdCBLGTK == jcNVkBqPgE){NfprDsalnX = true;}
      if(VMEARwrUDN == iwCfaloEnz){pcVGNhrfoC = true;}
      while(zVlGBkWoep == JzlWzTgtZq){iLpZNikJLZ = true;}
      while(jcNVkBqPgE == jcNVkBqPgE){zaGskmespV = true;}
      while(iwCfaloEnz == iwCfaloEnz){WrgdcjBLEE = true;}
      if(xZmbiumPYt == true){xZmbiumPYt = false;}
      if(iIGOPmamOZ == true){iIGOPmamOZ = false;}
      if(HaFZLDTGfO == true){HaFZLDTGfO = false;}
      if(uRAfsKpllo == true){uRAfsKpllo = false;}
      if(ObpmUaonQm == true){ObpmUaonQm = false;}
      if(LCpNqVTNPf == true){LCpNqVTNPf = false;}
      if(bfiKyRIaUE == true){bfiKyRIaUE = false;}
      if(woAYLfjSEk == true){woAYLfjSEk = false;}
      if(NfprDsalnX == true){NfprDsalnX = false;}
      if(pcVGNhrfoC == true){pcVGNhrfoC = false;}
      if(SOSLqVBRCL == true){SOSLqVBRCL = false;}
      if(kBIdSwpqGE == true){kBIdSwpqGE = false;}
      if(qVlxOTStKc == true){qVlxOTStKc = false;}
      if(nEdBSyMdBg == true){nEdBSyMdBg = false;}
      if(qIjclnUrmR == true){qIjclnUrmR = false;}
      if(rAYjLwbUxW == true){rAYjLwbUxW = false;}
      if(DHHYXgXGKT == true){DHHYXgXGKT = false;}
      if(iLpZNikJLZ == true){iLpZNikJLZ = false;}
      if(zaGskmespV == true){zaGskmespV = false;}
      if(WrgdcjBLEE == true){WrgdcjBLEE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFTRVBHAQO
{ 
  void NxOOZYJjHh()
  { 
      bool LEsFlWCKuq = false;
      bool pIYIAOXDlL = false;
      bool RyoiHxVWnu = false;
      bool HMUfwbeBCN = false;
      bool oLNAsgVXVi = false;
      bool EiYVyMPJyo = false;
      bool BeVAicmsLX = false;
      bool jWAYVGkopZ = false;
      bool ayAFpXnyhi = false;
      bool MVDNLJoMQP = false;
      bool scLyzhizAq = false;
      bool bZSXNDeQKL = false;
      bool noKbLNTlML = false;
      bool QXYZfxlCFI = false;
      bool nnypHlCezI = false;
      bool eYCEbERimk = false;
      bool NxmnaEBrrQ = false;
      bool QbKCXzqUUY = false;
      bool LnmDfrUUyb = false;
      bool fCPUtqBJPD = false;
      string ndFeaeHKaf;
      string ekeVKxTPBm;
      string brLLzYcTLs;
      string AOUIHZlHDq;
      string IrDfZiWldJ;
      string jBWIcwRsfB;
      string BmzheQQVNk;
      string KMLKdioekP;
      string CppBJyqLfL;
      string HsbBpVsVBJ;
      string SAYsyXoMes;
      string HmHPyKxxYg;
      string YEoCcRjKTI;
      string oSdbxBRwDk;
      string IeglEUkLDe;
      string XwxTkNLWQg;
      string merVEnIfSx;
      string rBsmXtXCxI;
      string gXGojrVJqi;
      string pufWycmKhQ;
      if(ndFeaeHKaf == SAYsyXoMes){LEsFlWCKuq = true;}
      else if(SAYsyXoMes == ndFeaeHKaf){scLyzhizAq = true;}
      if(ekeVKxTPBm == HmHPyKxxYg){pIYIAOXDlL = true;}
      else if(HmHPyKxxYg == ekeVKxTPBm){bZSXNDeQKL = true;}
      if(brLLzYcTLs == YEoCcRjKTI){RyoiHxVWnu = true;}
      else if(YEoCcRjKTI == brLLzYcTLs){noKbLNTlML = true;}
      if(AOUIHZlHDq == oSdbxBRwDk){HMUfwbeBCN = true;}
      else if(oSdbxBRwDk == AOUIHZlHDq){QXYZfxlCFI = true;}
      if(IrDfZiWldJ == IeglEUkLDe){oLNAsgVXVi = true;}
      else if(IeglEUkLDe == IrDfZiWldJ){nnypHlCezI = true;}
      if(jBWIcwRsfB == XwxTkNLWQg){EiYVyMPJyo = true;}
      else if(XwxTkNLWQg == jBWIcwRsfB){eYCEbERimk = true;}
      if(BmzheQQVNk == merVEnIfSx){BeVAicmsLX = true;}
      else if(merVEnIfSx == BmzheQQVNk){NxmnaEBrrQ = true;}
      if(KMLKdioekP == rBsmXtXCxI){jWAYVGkopZ = true;}
      if(CppBJyqLfL == gXGojrVJqi){ayAFpXnyhi = true;}
      if(HsbBpVsVBJ == pufWycmKhQ){MVDNLJoMQP = true;}
      while(rBsmXtXCxI == KMLKdioekP){QbKCXzqUUY = true;}
      while(gXGojrVJqi == gXGojrVJqi){LnmDfrUUyb = true;}
      while(pufWycmKhQ == pufWycmKhQ){fCPUtqBJPD = true;}
      if(LEsFlWCKuq == true){LEsFlWCKuq = false;}
      if(pIYIAOXDlL == true){pIYIAOXDlL = false;}
      if(RyoiHxVWnu == true){RyoiHxVWnu = false;}
      if(HMUfwbeBCN == true){HMUfwbeBCN = false;}
      if(oLNAsgVXVi == true){oLNAsgVXVi = false;}
      if(EiYVyMPJyo == true){EiYVyMPJyo = false;}
      if(BeVAicmsLX == true){BeVAicmsLX = false;}
      if(jWAYVGkopZ == true){jWAYVGkopZ = false;}
      if(ayAFpXnyhi == true){ayAFpXnyhi = false;}
      if(MVDNLJoMQP == true){MVDNLJoMQP = false;}
      if(scLyzhizAq == true){scLyzhizAq = false;}
      if(bZSXNDeQKL == true){bZSXNDeQKL = false;}
      if(noKbLNTlML == true){noKbLNTlML = false;}
      if(QXYZfxlCFI == true){QXYZfxlCFI = false;}
      if(nnypHlCezI == true){nnypHlCezI = false;}
      if(eYCEbERimk == true){eYCEbERimk = false;}
      if(NxmnaEBrrQ == true){NxmnaEBrrQ = false;}
      if(QbKCXzqUUY == true){QbKCXzqUUY = false;}
      if(LnmDfrUUyb == true){LnmDfrUUyb = false;}
      if(fCPUtqBJPD == true){fCPUtqBJPD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JXOMGKXZRC
{ 
  void ocPDIsMyhb()
  { 
      bool YRuhVuBfLe = false;
      bool pXRitiabxV = false;
      bool zGGErKVZsY = false;
      bool FMUqKzYLSa = false;
      bool YHaLZKRrlx = false;
      bool mgKShRKppL = false;
      bool ZalmZdCZXt = false;
      bool JPIWwqeueg = false;
      bool scnukXBCJr = false;
      bool niUHAxUnlw = false;
      bool HqUqnXYnVp = false;
      bool mPLIRxmpBB = false;
      bool bzQeFauAVz = false;
      bool WpJiZBIxHN = false;
      bool zMfSFYWLpC = false;
      bool KdljTIaokM = false;
      bool cXRWTwFbiP = false;
      bool opinBPSxZg = false;
      bool EiKTnrEYPR = false;
      bool aSLujbuJyJ = false;
      string XwyXESqwDH;
      string xBoBmmldAs;
      string cYIsuYqjNO;
      string dJtgDmEocL;
      string rnIzXNihUb;
      string mXLjSznFce;
      string bHindmGHyA;
      string hxAoAnPIVg;
      string pIOkbGxKOE;
      string yzLxikFTVj;
      string GajUspWWid;
      string ifiuoSrxMW;
      string owssBhkCFP;
      string hulkaPYtqk;
      string iabjURQQIP;
      string sHHztKgpSL;
      string EURTwmsyUZ;
      string sxGamOUJYi;
      string RUsoVanmqP;
      string hibfgOJHng;
      if(XwyXESqwDH == GajUspWWid){YRuhVuBfLe = true;}
      else if(GajUspWWid == XwyXESqwDH){HqUqnXYnVp = true;}
      if(xBoBmmldAs == ifiuoSrxMW){pXRitiabxV = true;}
      else if(ifiuoSrxMW == xBoBmmldAs){mPLIRxmpBB = true;}
      if(cYIsuYqjNO == owssBhkCFP){zGGErKVZsY = true;}
      else if(owssBhkCFP == cYIsuYqjNO){bzQeFauAVz = true;}
      if(dJtgDmEocL == hulkaPYtqk){FMUqKzYLSa = true;}
      else if(hulkaPYtqk == dJtgDmEocL){WpJiZBIxHN = true;}
      if(rnIzXNihUb == iabjURQQIP){YHaLZKRrlx = true;}
      else if(iabjURQQIP == rnIzXNihUb){zMfSFYWLpC = true;}
      if(mXLjSznFce == sHHztKgpSL){mgKShRKppL = true;}
      else if(sHHztKgpSL == mXLjSznFce){KdljTIaokM = true;}
      if(bHindmGHyA == EURTwmsyUZ){ZalmZdCZXt = true;}
      else if(EURTwmsyUZ == bHindmGHyA){cXRWTwFbiP = true;}
      if(hxAoAnPIVg == sxGamOUJYi){JPIWwqeueg = true;}
      if(pIOkbGxKOE == RUsoVanmqP){scnukXBCJr = true;}
      if(yzLxikFTVj == hibfgOJHng){niUHAxUnlw = true;}
      while(sxGamOUJYi == hxAoAnPIVg){opinBPSxZg = true;}
      while(RUsoVanmqP == RUsoVanmqP){EiKTnrEYPR = true;}
      while(hibfgOJHng == hibfgOJHng){aSLujbuJyJ = true;}
      if(YRuhVuBfLe == true){YRuhVuBfLe = false;}
      if(pXRitiabxV == true){pXRitiabxV = false;}
      if(zGGErKVZsY == true){zGGErKVZsY = false;}
      if(FMUqKzYLSa == true){FMUqKzYLSa = false;}
      if(YHaLZKRrlx == true){YHaLZKRrlx = false;}
      if(mgKShRKppL == true){mgKShRKppL = false;}
      if(ZalmZdCZXt == true){ZalmZdCZXt = false;}
      if(JPIWwqeueg == true){JPIWwqeueg = false;}
      if(scnukXBCJr == true){scnukXBCJr = false;}
      if(niUHAxUnlw == true){niUHAxUnlw = false;}
      if(HqUqnXYnVp == true){HqUqnXYnVp = false;}
      if(mPLIRxmpBB == true){mPLIRxmpBB = false;}
      if(bzQeFauAVz == true){bzQeFauAVz = false;}
      if(WpJiZBIxHN == true){WpJiZBIxHN = false;}
      if(zMfSFYWLpC == true){zMfSFYWLpC = false;}
      if(KdljTIaokM == true){KdljTIaokM = false;}
      if(cXRWTwFbiP == true){cXRWTwFbiP = false;}
      if(opinBPSxZg == true){opinBPSxZg = false;}
      if(EiKTnrEYPR == true){EiKTnrEYPR = false;}
      if(aSLujbuJyJ == true){aSLujbuJyJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQWDMPJZRM
{ 
  void VdKqUJOTiJ()
  { 
      bool LDPqzyYLkn = false;
      bool tuQRwQwacY = false;
      bool llFRwXdGUq = false;
      bool xGdGFNfKhC = false;
      bool yUrCYjgere = false;
      bool FHVUbYyxua = false;
      bool TRqtqmQKLh = false;
      bool jkraZQsDsM = false;
      bool pzOokokJeg = false;
      bool OhPGhfcyLk = false;
      bool SVSJuTOttK = false;
      bool euEhjUCCIB = false;
      bool BGfeSCVkst = false;
      bool ntqHsTgEtR = false;
      bool ZqPTBTdgVM = false;
      bool capJiLpmqr = false;
      bool ydAzWkDwnP = false;
      bool myIpaJpLcz = false;
      bool XoOfQMDgYg = false;
      bool dsNBTwqPxQ = false;
      string sHRMtwpMTL;
      string NJJHlhQGfE;
      string DEIMEsTaib;
      string AosWxwKOsC;
      string xusgNARxSC;
      string KgnLunyFIB;
      string bPdqLXQmKp;
      string WCMcHILbzD;
      string bWIgRTBgaJ;
      string xFFragRCUo;
      string jdmbeITKEl;
      string bWFEYFHxZr;
      string ViLBrRwUCZ;
      string qJGJTxjfBI;
      string zpcngazASU;
      string ZTccTASkiN;
      string MyIduSPwka;
      string VauQreFWUR;
      string RuCgAWgdpS;
      string eywnwBhysN;
      if(sHRMtwpMTL == jdmbeITKEl){LDPqzyYLkn = true;}
      else if(jdmbeITKEl == sHRMtwpMTL){SVSJuTOttK = true;}
      if(NJJHlhQGfE == bWFEYFHxZr){tuQRwQwacY = true;}
      else if(bWFEYFHxZr == NJJHlhQGfE){euEhjUCCIB = true;}
      if(DEIMEsTaib == ViLBrRwUCZ){llFRwXdGUq = true;}
      else if(ViLBrRwUCZ == DEIMEsTaib){BGfeSCVkst = true;}
      if(AosWxwKOsC == qJGJTxjfBI){xGdGFNfKhC = true;}
      else if(qJGJTxjfBI == AosWxwKOsC){ntqHsTgEtR = true;}
      if(xusgNARxSC == zpcngazASU){yUrCYjgere = true;}
      else if(zpcngazASU == xusgNARxSC){ZqPTBTdgVM = true;}
      if(KgnLunyFIB == ZTccTASkiN){FHVUbYyxua = true;}
      else if(ZTccTASkiN == KgnLunyFIB){capJiLpmqr = true;}
      if(bPdqLXQmKp == MyIduSPwka){TRqtqmQKLh = true;}
      else if(MyIduSPwka == bPdqLXQmKp){ydAzWkDwnP = true;}
      if(WCMcHILbzD == VauQreFWUR){jkraZQsDsM = true;}
      if(bWIgRTBgaJ == RuCgAWgdpS){pzOokokJeg = true;}
      if(xFFragRCUo == eywnwBhysN){OhPGhfcyLk = true;}
      while(VauQreFWUR == WCMcHILbzD){myIpaJpLcz = true;}
      while(RuCgAWgdpS == RuCgAWgdpS){XoOfQMDgYg = true;}
      while(eywnwBhysN == eywnwBhysN){dsNBTwqPxQ = true;}
      if(LDPqzyYLkn == true){LDPqzyYLkn = false;}
      if(tuQRwQwacY == true){tuQRwQwacY = false;}
      if(llFRwXdGUq == true){llFRwXdGUq = false;}
      if(xGdGFNfKhC == true){xGdGFNfKhC = false;}
      if(yUrCYjgere == true){yUrCYjgere = false;}
      if(FHVUbYyxua == true){FHVUbYyxua = false;}
      if(TRqtqmQKLh == true){TRqtqmQKLh = false;}
      if(jkraZQsDsM == true){jkraZQsDsM = false;}
      if(pzOokokJeg == true){pzOokokJeg = false;}
      if(OhPGhfcyLk == true){OhPGhfcyLk = false;}
      if(SVSJuTOttK == true){SVSJuTOttK = false;}
      if(euEhjUCCIB == true){euEhjUCCIB = false;}
      if(BGfeSCVkst == true){BGfeSCVkst = false;}
      if(ntqHsTgEtR == true){ntqHsTgEtR = false;}
      if(ZqPTBTdgVM == true){ZqPTBTdgVM = false;}
      if(capJiLpmqr == true){capJiLpmqr = false;}
      if(ydAzWkDwnP == true){ydAzWkDwnP = false;}
      if(myIpaJpLcz == true){myIpaJpLcz = false;}
      if(XoOfQMDgYg == true){XoOfQMDgYg = false;}
      if(dsNBTwqPxQ == true){dsNBTwqPxQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTLDTBCUIA
{ 
  void LCApLXNiLT()
  { 
      bool PasdLjlZKT = false;
      bool LrPmDRTckk = false;
      bool YlJubnJOGo = false;
      bool WwMlABnEQo = false;
      bool SRxbcVukXA = false;
      bool IzdFGdQxCX = false;
      bool ZWSUwPeclB = false;
      bool cOMuRHohSF = false;
      bool rYpFgWRGeW = false;
      bool jqCrOuybeM = false;
      bool pSyWXsmhnz = false;
      bool nhexeBfNnY = false;
      bool xYxPQlMTfV = false;
      bool IMCFOZZTgn = false;
      bool jiSfhCLENN = false;
      bool OknGPRUhFl = false;
      bool fTBRqbfYhF = false;
      bool aMfzoNGRhO = false;
      bool ZHGSGWYwpx = false;
      bool EqOuIPhAnG = false;
      string aWHKIoXduG;
      string RIdKGofmcJ;
      string aobXrPGHma;
      string TJumplhsOl;
      string qRJNIWXQzs;
      string xfiTgltiSs;
      string hQqTlHNpTT;
      string GlYqRIeNPV;
      string rpHscmZbFE;
      string rzaUDaaobA;
      string JgxflLHrBX;
      string GgTxArJxpy;
      string gkkPbHLDmq;
      string hplOMKsbGR;
      string fgZgxLedUL;
      string RcycTXwhDe;
      string zDEKpQuEjp;
      string zgpYRzLDRQ;
      string bhibYFqIuo;
      string OKXbSccPqf;
      if(aWHKIoXduG == JgxflLHrBX){PasdLjlZKT = true;}
      else if(JgxflLHrBX == aWHKIoXduG){pSyWXsmhnz = true;}
      if(RIdKGofmcJ == GgTxArJxpy){LrPmDRTckk = true;}
      else if(GgTxArJxpy == RIdKGofmcJ){nhexeBfNnY = true;}
      if(aobXrPGHma == gkkPbHLDmq){YlJubnJOGo = true;}
      else if(gkkPbHLDmq == aobXrPGHma){xYxPQlMTfV = true;}
      if(TJumplhsOl == hplOMKsbGR){WwMlABnEQo = true;}
      else if(hplOMKsbGR == TJumplhsOl){IMCFOZZTgn = true;}
      if(qRJNIWXQzs == fgZgxLedUL){SRxbcVukXA = true;}
      else if(fgZgxLedUL == qRJNIWXQzs){jiSfhCLENN = true;}
      if(xfiTgltiSs == RcycTXwhDe){IzdFGdQxCX = true;}
      else if(RcycTXwhDe == xfiTgltiSs){OknGPRUhFl = true;}
      if(hQqTlHNpTT == zDEKpQuEjp){ZWSUwPeclB = true;}
      else if(zDEKpQuEjp == hQqTlHNpTT){fTBRqbfYhF = true;}
      if(GlYqRIeNPV == zgpYRzLDRQ){cOMuRHohSF = true;}
      if(rpHscmZbFE == bhibYFqIuo){rYpFgWRGeW = true;}
      if(rzaUDaaobA == OKXbSccPqf){jqCrOuybeM = true;}
      while(zgpYRzLDRQ == GlYqRIeNPV){aMfzoNGRhO = true;}
      while(bhibYFqIuo == bhibYFqIuo){ZHGSGWYwpx = true;}
      while(OKXbSccPqf == OKXbSccPqf){EqOuIPhAnG = true;}
      if(PasdLjlZKT == true){PasdLjlZKT = false;}
      if(LrPmDRTckk == true){LrPmDRTckk = false;}
      if(YlJubnJOGo == true){YlJubnJOGo = false;}
      if(WwMlABnEQo == true){WwMlABnEQo = false;}
      if(SRxbcVukXA == true){SRxbcVukXA = false;}
      if(IzdFGdQxCX == true){IzdFGdQxCX = false;}
      if(ZWSUwPeclB == true){ZWSUwPeclB = false;}
      if(cOMuRHohSF == true){cOMuRHohSF = false;}
      if(rYpFgWRGeW == true){rYpFgWRGeW = false;}
      if(jqCrOuybeM == true){jqCrOuybeM = false;}
      if(pSyWXsmhnz == true){pSyWXsmhnz = false;}
      if(nhexeBfNnY == true){nhexeBfNnY = false;}
      if(xYxPQlMTfV == true){xYxPQlMTfV = false;}
      if(IMCFOZZTgn == true){IMCFOZZTgn = false;}
      if(jiSfhCLENN == true){jiSfhCLENN = false;}
      if(OknGPRUhFl == true){OknGPRUhFl = false;}
      if(fTBRqbfYhF == true){fTBRqbfYhF = false;}
      if(aMfzoNGRhO == true){aMfzoNGRhO = false;}
      if(ZHGSGWYwpx == true){ZHGSGWYwpx = false;}
      if(EqOuIPhAnG == true){EqOuIPhAnG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZHMNSUAHV
{ 
  void yJtgcVIPlK()
  { 
      bool zzDFcHyNKR = false;
      bool LYXWblpxVS = false;
      bool QUeJxVyMtz = false;
      bool BlUDLRYyqO = false;
      bool njMRkahFXw = false;
      bool SqjObdTsIH = false;
      bool IkSKQYDTLJ = false;
      bool MrGHegHNXV = false;
      bool nsoxgKBGbg = false;
      bool xeoiFCQCBL = false;
      bool WNsNjZkcjt = false;
      bool VGVlSPwUdF = false;
      bool XxreLhDWBb = false;
      bool PFLLzaAaNG = false;
      bool ZYVgKqJCQp = false;
      bool GuXunZUOCB = false;
      bool WNaHePtJmr = false;
      bool PVGWfyaKTU = false;
      bool YAFLVThPWY = false;
      bool FkXMjLyOCu = false;
      string weoWzhoSWD;
      string KMlcNVRSje;
      string FpWnXkiItA;
      string kSYHPiUOmE;
      string CplztftkNa;
      string DgVbRGHAyN;
      string ygYWRqmeNd;
      string BCfebODXtr;
      string pxtSxEwxoJ;
      string bUQYGVRPgC;
      string rPXjZAAqzC;
      string CjGGWBlGYM;
      string upoDCflGYG;
      string xnqqzaZKsw;
      string EFylHqOJCE;
      string jLpTHCaThs;
      string NtRrFOrOGw;
      string bbMcIoqCwK;
      string RbDTWlxXjw;
      string zFczhJnFgr;
      if(weoWzhoSWD == rPXjZAAqzC){zzDFcHyNKR = true;}
      else if(rPXjZAAqzC == weoWzhoSWD){WNsNjZkcjt = true;}
      if(KMlcNVRSje == CjGGWBlGYM){LYXWblpxVS = true;}
      else if(CjGGWBlGYM == KMlcNVRSje){VGVlSPwUdF = true;}
      if(FpWnXkiItA == upoDCflGYG){QUeJxVyMtz = true;}
      else if(upoDCflGYG == FpWnXkiItA){XxreLhDWBb = true;}
      if(kSYHPiUOmE == xnqqzaZKsw){BlUDLRYyqO = true;}
      else if(xnqqzaZKsw == kSYHPiUOmE){PFLLzaAaNG = true;}
      if(CplztftkNa == EFylHqOJCE){njMRkahFXw = true;}
      else if(EFylHqOJCE == CplztftkNa){ZYVgKqJCQp = true;}
      if(DgVbRGHAyN == jLpTHCaThs){SqjObdTsIH = true;}
      else if(jLpTHCaThs == DgVbRGHAyN){GuXunZUOCB = true;}
      if(ygYWRqmeNd == NtRrFOrOGw){IkSKQYDTLJ = true;}
      else if(NtRrFOrOGw == ygYWRqmeNd){WNaHePtJmr = true;}
      if(BCfebODXtr == bbMcIoqCwK){MrGHegHNXV = true;}
      if(pxtSxEwxoJ == RbDTWlxXjw){nsoxgKBGbg = true;}
      if(bUQYGVRPgC == zFczhJnFgr){xeoiFCQCBL = true;}
      while(bbMcIoqCwK == BCfebODXtr){PVGWfyaKTU = true;}
      while(RbDTWlxXjw == RbDTWlxXjw){YAFLVThPWY = true;}
      while(zFczhJnFgr == zFczhJnFgr){FkXMjLyOCu = true;}
      if(zzDFcHyNKR == true){zzDFcHyNKR = false;}
      if(LYXWblpxVS == true){LYXWblpxVS = false;}
      if(QUeJxVyMtz == true){QUeJxVyMtz = false;}
      if(BlUDLRYyqO == true){BlUDLRYyqO = false;}
      if(njMRkahFXw == true){njMRkahFXw = false;}
      if(SqjObdTsIH == true){SqjObdTsIH = false;}
      if(IkSKQYDTLJ == true){IkSKQYDTLJ = false;}
      if(MrGHegHNXV == true){MrGHegHNXV = false;}
      if(nsoxgKBGbg == true){nsoxgKBGbg = false;}
      if(xeoiFCQCBL == true){xeoiFCQCBL = false;}
      if(WNsNjZkcjt == true){WNsNjZkcjt = false;}
      if(VGVlSPwUdF == true){VGVlSPwUdF = false;}
      if(XxreLhDWBb == true){XxreLhDWBb = false;}
      if(PFLLzaAaNG == true){PFLLzaAaNG = false;}
      if(ZYVgKqJCQp == true){ZYVgKqJCQp = false;}
      if(GuXunZUOCB == true){GuXunZUOCB = false;}
      if(WNaHePtJmr == true){WNaHePtJmr = false;}
      if(PVGWfyaKTU == true){PVGWfyaKTU = false;}
      if(YAFLVThPWY == true){YAFLVThPWY = false;}
      if(FkXMjLyOCu == true){FkXMjLyOCu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYGPHYCESZ
{ 
  void UltGNSrasZ()
  { 
      bool KLSfiUxeHm = false;
      bool iGqfAlFOHJ = false;
      bool KUeTBbAJcU = false;
      bool kEOzicUiQH = false;
      bool QybopgjubV = false;
      bool jadrUogyeH = false;
      bool TmCmBdrrwX = false;
      bool RWyArMsocT = false;
      bool rEhGjJZVet = false;
      bool wVDJmdunmL = false;
      bool oqzEEMcdzH = false;
      bool uqUKOOFwCr = false;
      bool EVNBauToMO = false;
      bool QEBReAFdCX = false;
      bool gwWWyEAstX = false;
      bool XzluHTdxcI = false;
      bool smQjqqoDfN = false;
      bool JasdKHzqDV = false;
      bool uZuoqRRGKL = false;
      bool WIAsetfleH = false;
      string EyNoAtCJJG;
      string ZXjMkgjAag;
      string qqHZLZfqoh;
      string WjiyOJFgwB;
      string jHLUlazQIY;
      string aIbFENqmca;
      string OKUaipokya;
      string aCEZxjelnk;
      string ZOhPHOIctB;
      string SSDUlYmklw;
      string lOShyYDCHU;
      string hEzrAzbETU;
      string gLqxIIyimY;
      string wtAqzLwARh;
      string KFUZSOTLUm;
      string wiQROZXVYo;
      string ZUPiXnEHso;
      string DblkKbpQds;
      string omOAbNcicY;
      string naabIoplCe;
      if(EyNoAtCJJG == lOShyYDCHU){KLSfiUxeHm = true;}
      else if(lOShyYDCHU == EyNoAtCJJG){oqzEEMcdzH = true;}
      if(ZXjMkgjAag == hEzrAzbETU){iGqfAlFOHJ = true;}
      else if(hEzrAzbETU == ZXjMkgjAag){uqUKOOFwCr = true;}
      if(qqHZLZfqoh == gLqxIIyimY){KUeTBbAJcU = true;}
      else if(gLqxIIyimY == qqHZLZfqoh){EVNBauToMO = true;}
      if(WjiyOJFgwB == wtAqzLwARh){kEOzicUiQH = true;}
      else if(wtAqzLwARh == WjiyOJFgwB){QEBReAFdCX = true;}
      if(jHLUlazQIY == KFUZSOTLUm){QybopgjubV = true;}
      else if(KFUZSOTLUm == jHLUlazQIY){gwWWyEAstX = true;}
      if(aIbFENqmca == wiQROZXVYo){jadrUogyeH = true;}
      else if(wiQROZXVYo == aIbFENqmca){XzluHTdxcI = true;}
      if(OKUaipokya == ZUPiXnEHso){TmCmBdrrwX = true;}
      else if(ZUPiXnEHso == OKUaipokya){smQjqqoDfN = true;}
      if(aCEZxjelnk == DblkKbpQds){RWyArMsocT = true;}
      if(ZOhPHOIctB == omOAbNcicY){rEhGjJZVet = true;}
      if(SSDUlYmklw == naabIoplCe){wVDJmdunmL = true;}
      while(DblkKbpQds == aCEZxjelnk){JasdKHzqDV = true;}
      while(omOAbNcicY == omOAbNcicY){uZuoqRRGKL = true;}
      while(naabIoplCe == naabIoplCe){WIAsetfleH = true;}
      if(KLSfiUxeHm == true){KLSfiUxeHm = false;}
      if(iGqfAlFOHJ == true){iGqfAlFOHJ = false;}
      if(KUeTBbAJcU == true){KUeTBbAJcU = false;}
      if(kEOzicUiQH == true){kEOzicUiQH = false;}
      if(QybopgjubV == true){QybopgjubV = false;}
      if(jadrUogyeH == true){jadrUogyeH = false;}
      if(TmCmBdrrwX == true){TmCmBdrrwX = false;}
      if(RWyArMsocT == true){RWyArMsocT = false;}
      if(rEhGjJZVet == true){rEhGjJZVet = false;}
      if(wVDJmdunmL == true){wVDJmdunmL = false;}
      if(oqzEEMcdzH == true){oqzEEMcdzH = false;}
      if(uqUKOOFwCr == true){uqUKOOFwCr = false;}
      if(EVNBauToMO == true){EVNBauToMO = false;}
      if(QEBReAFdCX == true){QEBReAFdCX = false;}
      if(gwWWyEAstX == true){gwWWyEAstX = false;}
      if(XzluHTdxcI == true){XzluHTdxcI = false;}
      if(smQjqqoDfN == true){smQjqqoDfN = false;}
      if(JasdKHzqDV == true){JasdKHzqDV = false;}
      if(uZuoqRRGKL == true){uZuoqRRGKL = false;}
      if(WIAsetfleH == true){WIAsetfleH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSJYAXKFFL
{ 
  void kSyXAdYJmd()
  { 
      bool DeZuBwSbtV = false;
      bool XFTygmRgPO = false;
      bool ElfyOJseuc = false;
      bool arqLTrErYa = false;
      bool YikeDuwsLy = false;
      bool ifPVOQzagr = false;
      bool DmfRtfNIdo = false;
      bool iYHopVBBtS = false;
      bool NzTxtucUwC = false;
      bool scKgWkDTjX = false;
      bool hmOWOJXZfs = false;
      bool PygOeDThWy = false;
      bool CrLbwFNaRE = false;
      bool RgQVkZjxik = false;
      bool XCoCltwwCT = false;
      bool QUwkVobmZJ = false;
      bool uwIaaihKcE = false;
      bool SVzlazDIoB = false;
      bool IRXymxkeAu = false;
      bool xxWYoatNaD = false;
      string tsFISGRaJJ;
      string tnTHSMkuGA;
      string XtJjykilQY;
      string SGnTVdYIon;
      string NZeyGmBCGc;
      string YJbdmAiUKg;
      string WfKkqmAAlo;
      string mcGSlyOLdL;
      string jgfmzIdJfV;
      string tDyHQhOtGS;
      string mBQQowDJro;
      string kXqyxpzWki;
      string IpTQtjdyBE;
      string iUEKYhQOyD;
      string FURqjWMzKa;
      string hqJXJwhAWF;
      string RFHmGQSgZO;
      string ZkYgcnXbfX;
      string XdmaWqLfAb;
      string APrskAMekT;
      if(tsFISGRaJJ == mBQQowDJro){DeZuBwSbtV = true;}
      else if(mBQQowDJro == tsFISGRaJJ){hmOWOJXZfs = true;}
      if(tnTHSMkuGA == kXqyxpzWki){XFTygmRgPO = true;}
      else if(kXqyxpzWki == tnTHSMkuGA){PygOeDThWy = true;}
      if(XtJjykilQY == IpTQtjdyBE){ElfyOJseuc = true;}
      else if(IpTQtjdyBE == XtJjykilQY){CrLbwFNaRE = true;}
      if(SGnTVdYIon == iUEKYhQOyD){arqLTrErYa = true;}
      else if(iUEKYhQOyD == SGnTVdYIon){RgQVkZjxik = true;}
      if(NZeyGmBCGc == FURqjWMzKa){YikeDuwsLy = true;}
      else if(FURqjWMzKa == NZeyGmBCGc){XCoCltwwCT = true;}
      if(YJbdmAiUKg == hqJXJwhAWF){ifPVOQzagr = true;}
      else if(hqJXJwhAWF == YJbdmAiUKg){QUwkVobmZJ = true;}
      if(WfKkqmAAlo == RFHmGQSgZO){DmfRtfNIdo = true;}
      else if(RFHmGQSgZO == WfKkqmAAlo){uwIaaihKcE = true;}
      if(mcGSlyOLdL == ZkYgcnXbfX){iYHopVBBtS = true;}
      if(jgfmzIdJfV == XdmaWqLfAb){NzTxtucUwC = true;}
      if(tDyHQhOtGS == APrskAMekT){scKgWkDTjX = true;}
      while(ZkYgcnXbfX == mcGSlyOLdL){SVzlazDIoB = true;}
      while(XdmaWqLfAb == XdmaWqLfAb){IRXymxkeAu = true;}
      while(APrskAMekT == APrskAMekT){xxWYoatNaD = true;}
      if(DeZuBwSbtV == true){DeZuBwSbtV = false;}
      if(XFTygmRgPO == true){XFTygmRgPO = false;}
      if(ElfyOJseuc == true){ElfyOJseuc = false;}
      if(arqLTrErYa == true){arqLTrErYa = false;}
      if(YikeDuwsLy == true){YikeDuwsLy = false;}
      if(ifPVOQzagr == true){ifPVOQzagr = false;}
      if(DmfRtfNIdo == true){DmfRtfNIdo = false;}
      if(iYHopVBBtS == true){iYHopVBBtS = false;}
      if(NzTxtucUwC == true){NzTxtucUwC = false;}
      if(scKgWkDTjX == true){scKgWkDTjX = false;}
      if(hmOWOJXZfs == true){hmOWOJXZfs = false;}
      if(PygOeDThWy == true){PygOeDThWy = false;}
      if(CrLbwFNaRE == true){CrLbwFNaRE = false;}
      if(RgQVkZjxik == true){RgQVkZjxik = false;}
      if(XCoCltwwCT == true){XCoCltwwCT = false;}
      if(QUwkVobmZJ == true){QUwkVobmZJ = false;}
      if(uwIaaihKcE == true){uwIaaihKcE = false;}
      if(SVzlazDIoB == true){SVzlazDIoB = false;}
      if(IRXymxkeAu == true){IRXymxkeAu = false;}
      if(xxWYoatNaD == true){xxWYoatNaD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDBBIBDQTJ
{ 
  void MuTmSEbgUU()
  { 
      bool jsGyJUVTen = false;
      bool NHEkRJYjSl = false;
      bool YtLjVFKbIq = false;
      bool rxTTMAdHae = false;
      bool XLRwTrcjwu = false;
      bool QPViypgWcE = false;
      bool JsKmuPnjXQ = false;
      bool fQInNMbPPc = false;
      bool baeNacbkUW = false;
      bool TGdWUeBeAD = false;
      bool ErMfPzGhUl = false;
      bool NRGAbiNwMR = false;
      bool nDPBxYllSh = false;
      bool KxOMYjNzya = false;
      bool WsPhJCAdtl = false;
      bool QERhOAcLhp = false;
      bool NTOlaPCsbr = false;
      bool UNykuumgrt = false;
      bool XIrgRGffxX = false;
      bool GCQHNCdcHs = false;
      string kkQUwiJhtY;
      string PzhgDIgDYN;
      string uLMsruXRxh;
      string wceGSBYAna;
      string cMFphPMdId;
      string hVCETYXXcB;
      string LrjLbmUaNB;
      string ifOykhGWKc;
      string htJTAaZalt;
      string cBXmPjbsNt;
      string tkPGtBGESl;
      string RBMzSRiQLB;
      string NtoTYhIaiA;
      string FNJQhwdCZy;
      string UUHAbbnXUx;
      string BLgLgAwwgL;
      string seVSfEquRV;
      string mfpNgrlnqw;
      string sjGkztfxjg;
      string AhUOEozoUX;
      if(kkQUwiJhtY == tkPGtBGESl){jsGyJUVTen = true;}
      else if(tkPGtBGESl == kkQUwiJhtY){ErMfPzGhUl = true;}
      if(PzhgDIgDYN == RBMzSRiQLB){NHEkRJYjSl = true;}
      else if(RBMzSRiQLB == PzhgDIgDYN){NRGAbiNwMR = true;}
      if(uLMsruXRxh == NtoTYhIaiA){YtLjVFKbIq = true;}
      else if(NtoTYhIaiA == uLMsruXRxh){nDPBxYllSh = true;}
      if(wceGSBYAna == FNJQhwdCZy){rxTTMAdHae = true;}
      else if(FNJQhwdCZy == wceGSBYAna){KxOMYjNzya = true;}
      if(cMFphPMdId == UUHAbbnXUx){XLRwTrcjwu = true;}
      else if(UUHAbbnXUx == cMFphPMdId){WsPhJCAdtl = true;}
      if(hVCETYXXcB == BLgLgAwwgL){QPViypgWcE = true;}
      else if(BLgLgAwwgL == hVCETYXXcB){QERhOAcLhp = true;}
      if(LrjLbmUaNB == seVSfEquRV){JsKmuPnjXQ = true;}
      else if(seVSfEquRV == LrjLbmUaNB){NTOlaPCsbr = true;}
      if(ifOykhGWKc == mfpNgrlnqw){fQInNMbPPc = true;}
      if(htJTAaZalt == sjGkztfxjg){baeNacbkUW = true;}
      if(cBXmPjbsNt == AhUOEozoUX){TGdWUeBeAD = true;}
      while(mfpNgrlnqw == ifOykhGWKc){UNykuumgrt = true;}
      while(sjGkztfxjg == sjGkztfxjg){XIrgRGffxX = true;}
      while(AhUOEozoUX == AhUOEozoUX){GCQHNCdcHs = true;}
      if(jsGyJUVTen == true){jsGyJUVTen = false;}
      if(NHEkRJYjSl == true){NHEkRJYjSl = false;}
      if(YtLjVFKbIq == true){YtLjVFKbIq = false;}
      if(rxTTMAdHae == true){rxTTMAdHae = false;}
      if(XLRwTrcjwu == true){XLRwTrcjwu = false;}
      if(QPViypgWcE == true){QPViypgWcE = false;}
      if(JsKmuPnjXQ == true){JsKmuPnjXQ = false;}
      if(fQInNMbPPc == true){fQInNMbPPc = false;}
      if(baeNacbkUW == true){baeNacbkUW = false;}
      if(TGdWUeBeAD == true){TGdWUeBeAD = false;}
      if(ErMfPzGhUl == true){ErMfPzGhUl = false;}
      if(NRGAbiNwMR == true){NRGAbiNwMR = false;}
      if(nDPBxYllSh == true){nDPBxYllSh = false;}
      if(KxOMYjNzya == true){KxOMYjNzya = false;}
      if(WsPhJCAdtl == true){WsPhJCAdtl = false;}
      if(QERhOAcLhp == true){QERhOAcLhp = false;}
      if(NTOlaPCsbr == true){NTOlaPCsbr = false;}
      if(UNykuumgrt == true){UNykuumgrt = false;}
      if(XIrgRGffxX == true){XIrgRGffxX = false;}
      if(GCQHNCdcHs == true){GCQHNCdcHs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBKLWZLFDE
{ 
  void AUrEMMxoxz()
  { 
      bool LeATARECqZ = false;
      bool MjGkQGPPkc = false;
      bool udFAZKVANK = false;
      bool RtJmTqwFYE = false;
      bool HNeQcAHNGe = false;
      bool dGuFghYzso = false;
      bool uDofIRaSQY = false;
      bool KKpgUgzoWY = false;
      bool CHthfKzDFl = false;
      bool SwLiJEYyIK = false;
      bool ZowgUTPOkA = false;
      bool ijbUmmJHAy = false;
      bool SWMdFNzHWQ = false;
      bool IAgLyNLMML = false;
      bool tjSFDiTqwV = false;
      bool uQyKrDbSbH = false;
      bool UIqTqhDQVZ = false;
      bool bwtnDiDHZW = false;
      bool tILBVqCWTu = false;
      bool lskFqlrzOV = false;
      string JYzXxtPcxq;
      string UVmjZUZssH;
      string dUCePQTGCb;
      string bVzWJCuWkK;
      string diLzMcIEhJ;
      string uAVsXnWTIg;
      string aIZUOzWPaX;
      string YDIicuJDSl;
      string HPYsgazFzU;
      string fbOEjVIpjN;
      string GscJjrrmPb;
      string eTBWYKjgnn;
      string zRPGrxnDyH;
      string mSSEeNlPJo;
      string iLoXoMareY;
      string kaCwNocWQl;
      string DnoHnMAwqL;
      string YTWzEnbrQf;
      string VwYYVLQWpp;
      string kOyWltWgic;
      if(JYzXxtPcxq == GscJjrrmPb){LeATARECqZ = true;}
      else if(GscJjrrmPb == JYzXxtPcxq){ZowgUTPOkA = true;}
      if(UVmjZUZssH == eTBWYKjgnn){MjGkQGPPkc = true;}
      else if(eTBWYKjgnn == UVmjZUZssH){ijbUmmJHAy = true;}
      if(dUCePQTGCb == zRPGrxnDyH){udFAZKVANK = true;}
      else if(zRPGrxnDyH == dUCePQTGCb){SWMdFNzHWQ = true;}
      if(bVzWJCuWkK == mSSEeNlPJo){RtJmTqwFYE = true;}
      else if(mSSEeNlPJo == bVzWJCuWkK){IAgLyNLMML = true;}
      if(diLzMcIEhJ == iLoXoMareY){HNeQcAHNGe = true;}
      else if(iLoXoMareY == diLzMcIEhJ){tjSFDiTqwV = true;}
      if(uAVsXnWTIg == kaCwNocWQl){dGuFghYzso = true;}
      else if(kaCwNocWQl == uAVsXnWTIg){uQyKrDbSbH = true;}
      if(aIZUOzWPaX == DnoHnMAwqL){uDofIRaSQY = true;}
      else if(DnoHnMAwqL == aIZUOzWPaX){UIqTqhDQVZ = true;}
      if(YDIicuJDSl == YTWzEnbrQf){KKpgUgzoWY = true;}
      if(HPYsgazFzU == VwYYVLQWpp){CHthfKzDFl = true;}
      if(fbOEjVIpjN == kOyWltWgic){SwLiJEYyIK = true;}
      while(YTWzEnbrQf == YDIicuJDSl){bwtnDiDHZW = true;}
      while(VwYYVLQWpp == VwYYVLQWpp){tILBVqCWTu = true;}
      while(kOyWltWgic == kOyWltWgic){lskFqlrzOV = true;}
      if(LeATARECqZ == true){LeATARECqZ = false;}
      if(MjGkQGPPkc == true){MjGkQGPPkc = false;}
      if(udFAZKVANK == true){udFAZKVANK = false;}
      if(RtJmTqwFYE == true){RtJmTqwFYE = false;}
      if(HNeQcAHNGe == true){HNeQcAHNGe = false;}
      if(dGuFghYzso == true){dGuFghYzso = false;}
      if(uDofIRaSQY == true){uDofIRaSQY = false;}
      if(KKpgUgzoWY == true){KKpgUgzoWY = false;}
      if(CHthfKzDFl == true){CHthfKzDFl = false;}
      if(SwLiJEYyIK == true){SwLiJEYyIK = false;}
      if(ZowgUTPOkA == true){ZowgUTPOkA = false;}
      if(ijbUmmJHAy == true){ijbUmmJHAy = false;}
      if(SWMdFNzHWQ == true){SWMdFNzHWQ = false;}
      if(IAgLyNLMML == true){IAgLyNLMML = false;}
      if(tjSFDiTqwV == true){tjSFDiTqwV = false;}
      if(uQyKrDbSbH == true){uQyKrDbSbH = false;}
      if(UIqTqhDQVZ == true){UIqTqhDQVZ = false;}
      if(bwtnDiDHZW == true){bwtnDiDHZW = false;}
      if(tILBVqCWTu == true){tILBVqCWTu = false;}
      if(lskFqlrzOV == true){lskFqlrzOV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AUGGOBGNKM
{ 
  void OIipZKBKRh()
  { 
      bool itrlBdchrm = false;
      bool tUGobWAXNj = false;
      bool jSPaMRKtOh = false;
      bool OULfwIKoJO = false;
      bool iEVjTZsmIj = false;
      bool gaUSHPdQYi = false;
      bool TiSJXZIasT = false;
      bool MKNzBfxeHm = false;
      bool YWkdBnzsXf = false;
      bool dtPZtAkMMt = false;
      bool RRtoXVMVQb = false;
      bool SyJlJxxoIj = false;
      bool ZOCMoRtmEA = false;
      bool tjSMUHbwFe = false;
      bool bcbwNfkdQx = false;
      bool CuEcUCOhzG = false;
      bool bYRPghewQC = false;
      bool UAidHwmGyI = false;
      bool gQWGyyfpqS = false;
      bool rtxzDCLLPe = false;
      string PaQGWIrsas;
      string fintprSzxO;
      string DFTqwHSsTc;
      string KujIjaQuwE;
      string BdGPcqdYeo;
      string iCEdqKHYJP;
      string oyZyhjzfKP;
      string aXDrNYyDOF;
      string csNdsIqFQY;
      string TqlgOCEIhr;
      string ryOPNLyLQR;
      string LDKDlwkuEZ;
      string rsOkuikVcK;
      string UpVWNddxPh;
      string JfozNQghtS;
      string RIEHzyjdUe;
      string ZbhGwVgmpH;
      string RmfVPMDOWe;
      string CCbKrLlNWO;
      string tzckHgyiCq;
      if(PaQGWIrsas == ryOPNLyLQR){itrlBdchrm = true;}
      else if(ryOPNLyLQR == PaQGWIrsas){RRtoXVMVQb = true;}
      if(fintprSzxO == LDKDlwkuEZ){tUGobWAXNj = true;}
      else if(LDKDlwkuEZ == fintprSzxO){SyJlJxxoIj = true;}
      if(DFTqwHSsTc == rsOkuikVcK){jSPaMRKtOh = true;}
      else if(rsOkuikVcK == DFTqwHSsTc){ZOCMoRtmEA = true;}
      if(KujIjaQuwE == UpVWNddxPh){OULfwIKoJO = true;}
      else if(UpVWNddxPh == KujIjaQuwE){tjSMUHbwFe = true;}
      if(BdGPcqdYeo == JfozNQghtS){iEVjTZsmIj = true;}
      else if(JfozNQghtS == BdGPcqdYeo){bcbwNfkdQx = true;}
      if(iCEdqKHYJP == RIEHzyjdUe){gaUSHPdQYi = true;}
      else if(RIEHzyjdUe == iCEdqKHYJP){CuEcUCOhzG = true;}
      if(oyZyhjzfKP == ZbhGwVgmpH){TiSJXZIasT = true;}
      else if(ZbhGwVgmpH == oyZyhjzfKP){bYRPghewQC = true;}
      if(aXDrNYyDOF == RmfVPMDOWe){MKNzBfxeHm = true;}
      if(csNdsIqFQY == CCbKrLlNWO){YWkdBnzsXf = true;}
      if(TqlgOCEIhr == tzckHgyiCq){dtPZtAkMMt = true;}
      while(RmfVPMDOWe == aXDrNYyDOF){UAidHwmGyI = true;}
      while(CCbKrLlNWO == CCbKrLlNWO){gQWGyyfpqS = true;}
      while(tzckHgyiCq == tzckHgyiCq){rtxzDCLLPe = true;}
      if(itrlBdchrm == true){itrlBdchrm = false;}
      if(tUGobWAXNj == true){tUGobWAXNj = false;}
      if(jSPaMRKtOh == true){jSPaMRKtOh = false;}
      if(OULfwIKoJO == true){OULfwIKoJO = false;}
      if(iEVjTZsmIj == true){iEVjTZsmIj = false;}
      if(gaUSHPdQYi == true){gaUSHPdQYi = false;}
      if(TiSJXZIasT == true){TiSJXZIasT = false;}
      if(MKNzBfxeHm == true){MKNzBfxeHm = false;}
      if(YWkdBnzsXf == true){YWkdBnzsXf = false;}
      if(dtPZtAkMMt == true){dtPZtAkMMt = false;}
      if(RRtoXVMVQb == true){RRtoXVMVQb = false;}
      if(SyJlJxxoIj == true){SyJlJxxoIj = false;}
      if(ZOCMoRtmEA == true){ZOCMoRtmEA = false;}
      if(tjSMUHbwFe == true){tjSMUHbwFe = false;}
      if(bcbwNfkdQx == true){bcbwNfkdQx = false;}
      if(CuEcUCOhzG == true){CuEcUCOhzG = false;}
      if(bYRPghewQC == true){bYRPghewQC = false;}
      if(UAidHwmGyI == true){UAidHwmGyI = false;}
      if(gQWGyyfpqS == true){gQWGyyfpqS = false;}
      if(rtxzDCLLPe == true){rtxzDCLLPe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNIKUEZABI
{ 
  void rPlPNLCrXT()
  { 
      bool ZdqnKpHmIz = false;
      bool HFtVmxMMxm = false;
      bool bRjYQysVSR = false;
      bool smTdIabMPw = false;
      bool EsnkWPGCBO = false;
      bool RyDnPHtSXL = false;
      bool xlUpFTkQNL = false;
      bool UAwAhidyBA = false;
      bool rqTDAtjeNB = false;
      bool gInEzRXxfD = false;
      bool donptRBCFg = false;
      bool cwQWSGSRoK = false;
      bool jFCMeLLrBQ = false;
      bool KgSyWCCdJi = false;
      bool shZfXjrRks = false;
      bool zGHUSXlbKh = false;
      bool FJAoWudRAQ = false;
      bool DoHGRCfWot = false;
      bool TtGIRDZxfy = false;
      bool QaSbdigjJb = false;
      string rOyYqqINnp;
      string npERteioKI;
      string ZMCnBqVIpZ;
      string ZJAbmQRugy;
      string GinInIzQDK;
      string SukiVfLJWz;
      string VAXOQdocdc;
      string MmHMCpXtAs;
      string rEEeHdXRGH;
      string FIYgbFKYrK;
      string SWmaxemYge;
      string HQJcHRwrHm;
      string FXVVWEOakw;
      string eyCoZVRchb;
      string pzjaAnyuZK;
      string JSRFEuAQEs;
      string PMnjzIOTDl;
      string zSKewFmuVh;
      string FSAamMfwje;
      string UBYoLdLAar;
      if(rOyYqqINnp == SWmaxemYge){ZdqnKpHmIz = true;}
      else if(SWmaxemYge == rOyYqqINnp){donptRBCFg = true;}
      if(npERteioKI == HQJcHRwrHm){HFtVmxMMxm = true;}
      else if(HQJcHRwrHm == npERteioKI){cwQWSGSRoK = true;}
      if(ZMCnBqVIpZ == FXVVWEOakw){bRjYQysVSR = true;}
      else if(FXVVWEOakw == ZMCnBqVIpZ){jFCMeLLrBQ = true;}
      if(ZJAbmQRugy == eyCoZVRchb){smTdIabMPw = true;}
      else if(eyCoZVRchb == ZJAbmQRugy){KgSyWCCdJi = true;}
      if(GinInIzQDK == pzjaAnyuZK){EsnkWPGCBO = true;}
      else if(pzjaAnyuZK == GinInIzQDK){shZfXjrRks = true;}
      if(SukiVfLJWz == JSRFEuAQEs){RyDnPHtSXL = true;}
      else if(JSRFEuAQEs == SukiVfLJWz){zGHUSXlbKh = true;}
      if(VAXOQdocdc == PMnjzIOTDl){xlUpFTkQNL = true;}
      else if(PMnjzIOTDl == VAXOQdocdc){FJAoWudRAQ = true;}
      if(MmHMCpXtAs == zSKewFmuVh){UAwAhidyBA = true;}
      if(rEEeHdXRGH == FSAamMfwje){rqTDAtjeNB = true;}
      if(FIYgbFKYrK == UBYoLdLAar){gInEzRXxfD = true;}
      while(zSKewFmuVh == MmHMCpXtAs){DoHGRCfWot = true;}
      while(FSAamMfwje == FSAamMfwje){TtGIRDZxfy = true;}
      while(UBYoLdLAar == UBYoLdLAar){QaSbdigjJb = true;}
      if(ZdqnKpHmIz == true){ZdqnKpHmIz = false;}
      if(HFtVmxMMxm == true){HFtVmxMMxm = false;}
      if(bRjYQysVSR == true){bRjYQysVSR = false;}
      if(smTdIabMPw == true){smTdIabMPw = false;}
      if(EsnkWPGCBO == true){EsnkWPGCBO = false;}
      if(RyDnPHtSXL == true){RyDnPHtSXL = false;}
      if(xlUpFTkQNL == true){xlUpFTkQNL = false;}
      if(UAwAhidyBA == true){UAwAhidyBA = false;}
      if(rqTDAtjeNB == true){rqTDAtjeNB = false;}
      if(gInEzRXxfD == true){gInEzRXxfD = false;}
      if(donptRBCFg == true){donptRBCFg = false;}
      if(cwQWSGSRoK == true){cwQWSGSRoK = false;}
      if(jFCMeLLrBQ == true){jFCMeLLrBQ = false;}
      if(KgSyWCCdJi == true){KgSyWCCdJi = false;}
      if(shZfXjrRks == true){shZfXjrRks = false;}
      if(zGHUSXlbKh == true){zGHUSXlbKh = false;}
      if(FJAoWudRAQ == true){FJAoWudRAQ = false;}
      if(DoHGRCfWot == true){DoHGRCfWot = false;}
      if(TtGIRDZxfy == true){TtGIRDZxfy = false;}
      if(QaSbdigjJb == true){QaSbdigjJb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIVNFRVLQF
{ 
  void mZTCnPjIoB()
  { 
      bool TDHSSULkJt = false;
      bool mViJPdxOgc = false;
      bool gkqHEglCLF = false;
      bool NIrYzSxIrO = false;
      bool URkThEPfQR = false;
      bool PBsEyhMAOl = false;
      bool iJYDfedKJx = false;
      bool goVRIOAWZA = false;
      bool QFltpMOnZQ = false;
      bool GxsFfKrhmD = false;
      bool ZEWTkafbwi = false;
      bool hoaOVcXeMT = false;
      bool PpkrqjuPkx = false;
      bool WRjVZLiSJO = false;
      bool gmrqiQVejD = false;
      bool mMUTnjTdcB = false;
      bool ePpzLPFEnJ = false;
      bool sFVxlbxsJZ = false;
      bool NPegJKxPho = false;
      bool rFpHjQwseS = false;
      string TooXYUiTaB;
      string fYfVdyVKDR;
      string JHfSInKbgf;
      string JlHlHKUWkb;
      string wjcZmQFSOu;
      string YYLSJLIVOk;
      string JGmtqtQsNT;
      string dyZbVYeFer;
      string iqMkGkZobu;
      string ByHARoxhis;
      string zMFuRayjxk;
      string gCpWBSsCnG;
      string UbQRSeqZKf;
      string bxWlsWlRSf;
      string lprqOzIkyz;
      string wttcYXumcm;
      string jYZQJjeEce;
      string faiITdjZDT;
      string WFaLjgDtNV;
      string azofwNPage;
      if(TooXYUiTaB == zMFuRayjxk){TDHSSULkJt = true;}
      else if(zMFuRayjxk == TooXYUiTaB){ZEWTkafbwi = true;}
      if(fYfVdyVKDR == gCpWBSsCnG){mViJPdxOgc = true;}
      else if(gCpWBSsCnG == fYfVdyVKDR){hoaOVcXeMT = true;}
      if(JHfSInKbgf == UbQRSeqZKf){gkqHEglCLF = true;}
      else if(UbQRSeqZKf == JHfSInKbgf){PpkrqjuPkx = true;}
      if(JlHlHKUWkb == bxWlsWlRSf){NIrYzSxIrO = true;}
      else if(bxWlsWlRSf == JlHlHKUWkb){WRjVZLiSJO = true;}
      if(wjcZmQFSOu == lprqOzIkyz){URkThEPfQR = true;}
      else if(lprqOzIkyz == wjcZmQFSOu){gmrqiQVejD = true;}
      if(YYLSJLIVOk == wttcYXumcm){PBsEyhMAOl = true;}
      else if(wttcYXumcm == YYLSJLIVOk){mMUTnjTdcB = true;}
      if(JGmtqtQsNT == jYZQJjeEce){iJYDfedKJx = true;}
      else if(jYZQJjeEce == JGmtqtQsNT){ePpzLPFEnJ = true;}
      if(dyZbVYeFer == faiITdjZDT){goVRIOAWZA = true;}
      if(iqMkGkZobu == WFaLjgDtNV){QFltpMOnZQ = true;}
      if(ByHARoxhis == azofwNPage){GxsFfKrhmD = true;}
      while(faiITdjZDT == dyZbVYeFer){sFVxlbxsJZ = true;}
      while(WFaLjgDtNV == WFaLjgDtNV){NPegJKxPho = true;}
      while(azofwNPage == azofwNPage){rFpHjQwseS = true;}
      if(TDHSSULkJt == true){TDHSSULkJt = false;}
      if(mViJPdxOgc == true){mViJPdxOgc = false;}
      if(gkqHEglCLF == true){gkqHEglCLF = false;}
      if(NIrYzSxIrO == true){NIrYzSxIrO = false;}
      if(URkThEPfQR == true){URkThEPfQR = false;}
      if(PBsEyhMAOl == true){PBsEyhMAOl = false;}
      if(iJYDfedKJx == true){iJYDfedKJx = false;}
      if(goVRIOAWZA == true){goVRIOAWZA = false;}
      if(QFltpMOnZQ == true){QFltpMOnZQ = false;}
      if(GxsFfKrhmD == true){GxsFfKrhmD = false;}
      if(ZEWTkafbwi == true){ZEWTkafbwi = false;}
      if(hoaOVcXeMT == true){hoaOVcXeMT = false;}
      if(PpkrqjuPkx == true){PpkrqjuPkx = false;}
      if(WRjVZLiSJO == true){WRjVZLiSJO = false;}
      if(gmrqiQVejD == true){gmrqiQVejD = false;}
      if(mMUTnjTdcB == true){mMUTnjTdcB = false;}
      if(ePpzLPFEnJ == true){ePpzLPFEnJ = false;}
      if(sFVxlbxsJZ == true){sFVxlbxsJZ = false;}
      if(NPegJKxPho == true){NPegJKxPho = false;}
      if(rFpHjQwseS == true){rFpHjQwseS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDKLSAYFOC
{ 
  void bEQxrpZunl()
  { 
      bool bYrVJEDzDt = false;
      bool ShsKdrKlpe = false;
      bool UiwteDxVnq = false;
      bool HzxxMDPJJw = false;
      bool NHaVQJshAr = false;
      bool OtAJBrcxqG = false;
      bool GhKLmSkwxa = false;
      bool cBbtQNIZcU = false;
      bool JOUubMznuU = false;
      bool aRRDofwPhy = false;
      bool YxkZPNRFrm = false;
      bool jCUVwqMPia = false;
      bool SwAbAKiYEk = false;
      bool QsrewMdufO = false;
      bool tswIjXxuGy = false;
      bool SgfHebwIZF = false;
      bool drBGWqKoZi = false;
      bool NRjUfYArrb = false;
      bool MnSGSjMjzT = false;
      bool PUVZkBrpks = false;
      string DdDMFEidGH;
      string SdBDxRaRRE;
      string uePoJRjfjb;
      string tlhcePIyQK;
      string fjOOlfOEKc;
      string JPeLbXNNCm;
      string UDseMfwXYg;
      string IbBHYLPBDd;
      string DeVGSeHVBG;
      string CuwcocpjCF;
      string jpedUgOWmQ;
      string HMJYjphlLh;
      string XZVRdNfXSu;
      string UfyxtMzqll;
      string PkijyokWsz;
      string tDYUhJUMzH;
      string BpEqwbNLeW;
      string ppAYRmqlTo;
      string cIeSAQGdPj;
      string rmrekZfqnW;
      if(DdDMFEidGH == jpedUgOWmQ){bYrVJEDzDt = true;}
      else if(jpedUgOWmQ == DdDMFEidGH){YxkZPNRFrm = true;}
      if(SdBDxRaRRE == HMJYjphlLh){ShsKdrKlpe = true;}
      else if(HMJYjphlLh == SdBDxRaRRE){jCUVwqMPia = true;}
      if(uePoJRjfjb == XZVRdNfXSu){UiwteDxVnq = true;}
      else if(XZVRdNfXSu == uePoJRjfjb){SwAbAKiYEk = true;}
      if(tlhcePIyQK == UfyxtMzqll){HzxxMDPJJw = true;}
      else if(UfyxtMzqll == tlhcePIyQK){QsrewMdufO = true;}
      if(fjOOlfOEKc == PkijyokWsz){NHaVQJshAr = true;}
      else if(PkijyokWsz == fjOOlfOEKc){tswIjXxuGy = true;}
      if(JPeLbXNNCm == tDYUhJUMzH){OtAJBrcxqG = true;}
      else if(tDYUhJUMzH == JPeLbXNNCm){SgfHebwIZF = true;}
      if(UDseMfwXYg == BpEqwbNLeW){GhKLmSkwxa = true;}
      else if(BpEqwbNLeW == UDseMfwXYg){drBGWqKoZi = true;}
      if(IbBHYLPBDd == ppAYRmqlTo){cBbtQNIZcU = true;}
      if(DeVGSeHVBG == cIeSAQGdPj){JOUubMznuU = true;}
      if(CuwcocpjCF == rmrekZfqnW){aRRDofwPhy = true;}
      while(ppAYRmqlTo == IbBHYLPBDd){NRjUfYArrb = true;}
      while(cIeSAQGdPj == cIeSAQGdPj){MnSGSjMjzT = true;}
      while(rmrekZfqnW == rmrekZfqnW){PUVZkBrpks = true;}
      if(bYrVJEDzDt == true){bYrVJEDzDt = false;}
      if(ShsKdrKlpe == true){ShsKdrKlpe = false;}
      if(UiwteDxVnq == true){UiwteDxVnq = false;}
      if(HzxxMDPJJw == true){HzxxMDPJJw = false;}
      if(NHaVQJshAr == true){NHaVQJshAr = false;}
      if(OtAJBrcxqG == true){OtAJBrcxqG = false;}
      if(GhKLmSkwxa == true){GhKLmSkwxa = false;}
      if(cBbtQNIZcU == true){cBbtQNIZcU = false;}
      if(JOUubMznuU == true){JOUubMznuU = false;}
      if(aRRDofwPhy == true){aRRDofwPhy = false;}
      if(YxkZPNRFrm == true){YxkZPNRFrm = false;}
      if(jCUVwqMPia == true){jCUVwqMPia = false;}
      if(SwAbAKiYEk == true){SwAbAKiYEk = false;}
      if(QsrewMdufO == true){QsrewMdufO = false;}
      if(tswIjXxuGy == true){tswIjXxuGy = false;}
      if(SgfHebwIZF == true){SgfHebwIZF = false;}
      if(drBGWqKoZi == true){drBGWqKoZi = false;}
      if(NRjUfYArrb == true){NRjUfYArrb = false;}
      if(MnSGSjMjzT == true){MnSGSjMjzT = false;}
      if(PUVZkBrpks == true){PUVZkBrpks = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLGATPLAXC
{ 
  void PMNbTErPiZ()
  { 
      bool sCosPGdeLn = false;
      bool CatEmNpfLC = false;
      bool oUaIlyDGAX = false;
      bool MclDuJLtCF = false;
      bool biBxKcKgHU = false;
      bool ZxFTWYagHQ = false;
      bool DWdmaZoqJc = false;
      bool CudFaFTdxJ = false;
      bool nVzfxOXRfW = false;
      bool iemkCEFNWk = false;
      bool mSWdSeTzsQ = false;
      bool ExjybgWxpL = false;
      bool BXKmtWHrCV = false;
      bool zFHLVUyVMS = false;
      bool uXXORluoIV = false;
      bool gHXKiPIjju = false;
      bool WawXRzpXbH = false;
      bool hBkWPdzuVI = false;
      bool bSignqgwcF = false;
      bool MOkQuTaAxS = false;
      string mKnqpqAVOU;
      string FXwfHySrfx;
      string zfQwVzUpIG;
      string mWVgDRhNFH;
      string ZmFSgfmRzo;
      string foICGGsqVq;
      string VKNIhhBObo;
      string QElXWLZxOo;
      string MDpSZyNTZw;
      string XprOlPZxjz;
      string eXoKYbCket;
      string gubgdRUthj;
      string ThneQZMXlH;
      string lcNPKnOesy;
      string ucnfPbNLjT;
      string ufOAewjJsz;
      string OdyXIDhLVp;
      string DoBjoqsIPo;
      string LBnSMGNMkN;
      string EEltiQdQWM;
      if(mKnqpqAVOU == eXoKYbCket){sCosPGdeLn = true;}
      else if(eXoKYbCket == mKnqpqAVOU){mSWdSeTzsQ = true;}
      if(FXwfHySrfx == gubgdRUthj){CatEmNpfLC = true;}
      else if(gubgdRUthj == FXwfHySrfx){ExjybgWxpL = true;}
      if(zfQwVzUpIG == ThneQZMXlH){oUaIlyDGAX = true;}
      else if(ThneQZMXlH == zfQwVzUpIG){BXKmtWHrCV = true;}
      if(mWVgDRhNFH == lcNPKnOesy){MclDuJLtCF = true;}
      else if(lcNPKnOesy == mWVgDRhNFH){zFHLVUyVMS = true;}
      if(ZmFSgfmRzo == ucnfPbNLjT){biBxKcKgHU = true;}
      else if(ucnfPbNLjT == ZmFSgfmRzo){uXXORluoIV = true;}
      if(foICGGsqVq == ufOAewjJsz){ZxFTWYagHQ = true;}
      else if(ufOAewjJsz == foICGGsqVq){gHXKiPIjju = true;}
      if(VKNIhhBObo == OdyXIDhLVp){DWdmaZoqJc = true;}
      else if(OdyXIDhLVp == VKNIhhBObo){WawXRzpXbH = true;}
      if(QElXWLZxOo == DoBjoqsIPo){CudFaFTdxJ = true;}
      if(MDpSZyNTZw == LBnSMGNMkN){nVzfxOXRfW = true;}
      if(XprOlPZxjz == EEltiQdQWM){iemkCEFNWk = true;}
      while(DoBjoqsIPo == QElXWLZxOo){hBkWPdzuVI = true;}
      while(LBnSMGNMkN == LBnSMGNMkN){bSignqgwcF = true;}
      while(EEltiQdQWM == EEltiQdQWM){MOkQuTaAxS = true;}
      if(sCosPGdeLn == true){sCosPGdeLn = false;}
      if(CatEmNpfLC == true){CatEmNpfLC = false;}
      if(oUaIlyDGAX == true){oUaIlyDGAX = false;}
      if(MclDuJLtCF == true){MclDuJLtCF = false;}
      if(biBxKcKgHU == true){biBxKcKgHU = false;}
      if(ZxFTWYagHQ == true){ZxFTWYagHQ = false;}
      if(DWdmaZoqJc == true){DWdmaZoqJc = false;}
      if(CudFaFTdxJ == true){CudFaFTdxJ = false;}
      if(nVzfxOXRfW == true){nVzfxOXRfW = false;}
      if(iemkCEFNWk == true){iemkCEFNWk = false;}
      if(mSWdSeTzsQ == true){mSWdSeTzsQ = false;}
      if(ExjybgWxpL == true){ExjybgWxpL = false;}
      if(BXKmtWHrCV == true){BXKmtWHrCV = false;}
      if(zFHLVUyVMS == true){zFHLVUyVMS = false;}
      if(uXXORluoIV == true){uXXORluoIV = false;}
      if(gHXKiPIjju == true){gHXKiPIjju = false;}
      if(WawXRzpXbH == true){WawXRzpXbH = false;}
      if(hBkWPdzuVI == true){hBkWPdzuVI = false;}
      if(bSignqgwcF == true){bSignqgwcF = false;}
      if(MOkQuTaAxS == true){MOkQuTaAxS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHVUKMYNBT
{ 
  void TXGFJUBBEy()
  { 
      bool cpRBHWZZwr = false;
      bool VdFFIqrNiM = false;
      bool RNfVicoyiP = false;
      bool wmBpwRzjxO = false;
      bool QAhmYreSaS = false;
      bool QZeYzOKuSd = false;
      bool haqgwhbPIq = false;
      bool qHQUuRfsxq = false;
      bool yWXQyVHcph = false;
      bool HERSfpIBpp = false;
      bool POJiaJJKch = false;
      bool iQxafLDahZ = false;
      bool ayZajloxnF = false;
      bool IdCGaiMnoo = false;
      bool MxAIzpGpmT = false;
      bool mhSQPRohzo = false;
      bool TLVXYEOqAx = false;
      bool yOksMcyQas = false;
      bool eyKUSaKkqI = false;
      bool seozVAacjt = false;
      string rWaSQKJomC;
      string CFCRCiDPmS;
      string rjsjDsUOdC;
      string cJqiErHiWa;
      string uCNJLYMqjC;
      string cQHOrIcpPX;
      string ptKjZsOTMJ;
      string aTrLWoWjYd;
      string fcdbZMCbqw;
      string ORTyjBqciS;
      string KsdZaIXuqC;
      string lsQkrNQiJN;
      string qlbQuJAsbV;
      string ysAGTmyDBR;
      string nGjoJVBiGW;
      string jHSVbXQMeR;
      string IeSUDrsKRF;
      string OMhrYjCmHY;
      string IRlFlqaeeu;
      string VkXjJJnOkR;
      if(rWaSQKJomC == KsdZaIXuqC){cpRBHWZZwr = true;}
      else if(KsdZaIXuqC == rWaSQKJomC){POJiaJJKch = true;}
      if(CFCRCiDPmS == lsQkrNQiJN){VdFFIqrNiM = true;}
      else if(lsQkrNQiJN == CFCRCiDPmS){iQxafLDahZ = true;}
      if(rjsjDsUOdC == qlbQuJAsbV){RNfVicoyiP = true;}
      else if(qlbQuJAsbV == rjsjDsUOdC){ayZajloxnF = true;}
      if(cJqiErHiWa == ysAGTmyDBR){wmBpwRzjxO = true;}
      else if(ysAGTmyDBR == cJqiErHiWa){IdCGaiMnoo = true;}
      if(uCNJLYMqjC == nGjoJVBiGW){QAhmYreSaS = true;}
      else if(nGjoJVBiGW == uCNJLYMqjC){MxAIzpGpmT = true;}
      if(cQHOrIcpPX == jHSVbXQMeR){QZeYzOKuSd = true;}
      else if(jHSVbXQMeR == cQHOrIcpPX){mhSQPRohzo = true;}
      if(ptKjZsOTMJ == IeSUDrsKRF){haqgwhbPIq = true;}
      else if(IeSUDrsKRF == ptKjZsOTMJ){TLVXYEOqAx = true;}
      if(aTrLWoWjYd == OMhrYjCmHY){qHQUuRfsxq = true;}
      if(fcdbZMCbqw == IRlFlqaeeu){yWXQyVHcph = true;}
      if(ORTyjBqciS == VkXjJJnOkR){HERSfpIBpp = true;}
      while(OMhrYjCmHY == aTrLWoWjYd){yOksMcyQas = true;}
      while(IRlFlqaeeu == IRlFlqaeeu){eyKUSaKkqI = true;}
      while(VkXjJJnOkR == VkXjJJnOkR){seozVAacjt = true;}
      if(cpRBHWZZwr == true){cpRBHWZZwr = false;}
      if(VdFFIqrNiM == true){VdFFIqrNiM = false;}
      if(RNfVicoyiP == true){RNfVicoyiP = false;}
      if(wmBpwRzjxO == true){wmBpwRzjxO = false;}
      if(QAhmYreSaS == true){QAhmYreSaS = false;}
      if(QZeYzOKuSd == true){QZeYzOKuSd = false;}
      if(haqgwhbPIq == true){haqgwhbPIq = false;}
      if(qHQUuRfsxq == true){qHQUuRfsxq = false;}
      if(yWXQyVHcph == true){yWXQyVHcph = false;}
      if(HERSfpIBpp == true){HERSfpIBpp = false;}
      if(POJiaJJKch == true){POJiaJJKch = false;}
      if(iQxafLDahZ == true){iQxafLDahZ = false;}
      if(ayZajloxnF == true){ayZajloxnF = false;}
      if(IdCGaiMnoo == true){IdCGaiMnoo = false;}
      if(MxAIzpGpmT == true){MxAIzpGpmT = false;}
      if(mhSQPRohzo == true){mhSQPRohzo = false;}
      if(TLVXYEOqAx == true){TLVXYEOqAx = false;}
      if(yOksMcyQas == true){yOksMcyQas = false;}
      if(eyKUSaKkqI == true){eyKUSaKkqI = false;}
      if(seozVAacjt == true){seozVAacjt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTLDKMDMLF
{ 
  void BCVVqtsHrb()
  { 
      bool OTRqRjlTwL = false;
      bool hhKqhkdlUI = false;
      bool aPqthrRRVU = false;
      bool jpISBptHCo = false;
      bool TSGldJXbgF = false;
      bool uSKAbzbWIZ = false;
      bool SUybbrYror = false;
      bool qWifoIJFQY = false;
      bool UpjQYQeIqB = false;
      bool NWzcWyTdKl = false;
      bool jflnOYieKS = false;
      bool pWGiFcjhCK = false;
      bool MPAneTWGIp = false;
      bool netdonDuBA = false;
      bool gzxYLpPPWt = false;
      bool NlazYTeyJt = false;
      bool BbWUdLcbtQ = false;
      bool YnfCcNRbbn = false;
      bool DGiOcCDuFU = false;
      bool IFlHyEcctA = false;
      string pGTOPJVpKc;
      string kocKctJYOu;
      string mINhcThdmk;
      string kDccclgfcM;
      string WIHgiMnAxW;
      string MoWNRgsllu;
      string aqDZrhMAgq;
      string NdwBYdBgzP;
      string ehgQXugPKw;
      string susgleFhnB;
      string AnSFJirVnm;
      string fLmVQrKlBx;
      string AwokyRjPOs;
      string YSsyPpPaGo;
      string CLaXPgIXQt;
      string TSfpADzgHq;
      string ycGtONRnGZ;
      string bjfMtoVRVQ;
      string JMyUZGlCxL;
      string qiSOqZEfIC;
      if(pGTOPJVpKc == AnSFJirVnm){OTRqRjlTwL = true;}
      else if(AnSFJirVnm == pGTOPJVpKc){jflnOYieKS = true;}
      if(kocKctJYOu == fLmVQrKlBx){hhKqhkdlUI = true;}
      else if(fLmVQrKlBx == kocKctJYOu){pWGiFcjhCK = true;}
      if(mINhcThdmk == AwokyRjPOs){aPqthrRRVU = true;}
      else if(AwokyRjPOs == mINhcThdmk){MPAneTWGIp = true;}
      if(kDccclgfcM == YSsyPpPaGo){jpISBptHCo = true;}
      else if(YSsyPpPaGo == kDccclgfcM){netdonDuBA = true;}
      if(WIHgiMnAxW == CLaXPgIXQt){TSGldJXbgF = true;}
      else if(CLaXPgIXQt == WIHgiMnAxW){gzxYLpPPWt = true;}
      if(MoWNRgsllu == TSfpADzgHq){uSKAbzbWIZ = true;}
      else if(TSfpADzgHq == MoWNRgsllu){NlazYTeyJt = true;}
      if(aqDZrhMAgq == ycGtONRnGZ){SUybbrYror = true;}
      else if(ycGtONRnGZ == aqDZrhMAgq){BbWUdLcbtQ = true;}
      if(NdwBYdBgzP == bjfMtoVRVQ){qWifoIJFQY = true;}
      if(ehgQXugPKw == JMyUZGlCxL){UpjQYQeIqB = true;}
      if(susgleFhnB == qiSOqZEfIC){NWzcWyTdKl = true;}
      while(bjfMtoVRVQ == NdwBYdBgzP){YnfCcNRbbn = true;}
      while(JMyUZGlCxL == JMyUZGlCxL){DGiOcCDuFU = true;}
      while(qiSOqZEfIC == qiSOqZEfIC){IFlHyEcctA = true;}
      if(OTRqRjlTwL == true){OTRqRjlTwL = false;}
      if(hhKqhkdlUI == true){hhKqhkdlUI = false;}
      if(aPqthrRRVU == true){aPqthrRRVU = false;}
      if(jpISBptHCo == true){jpISBptHCo = false;}
      if(TSGldJXbgF == true){TSGldJXbgF = false;}
      if(uSKAbzbWIZ == true){uSKAbzbWIZ = false;}
      if(SUybbrYror == true){SUybbrYror = false;}
      if(qWifoIJFQY == true){qWifoIJFQY = false;}
      if(UpjQYQeIqB == true){UpjQYQeIqB = false;}
      if(NWzcWyTdKl == true){NWzcWyTdKl = false;}
      if(jflnOYieKS == true){jflnOYieKS = false;}
      if(pWGiFcjhCK == true){pWGiFcjhCK = false;}
      if(MPAneTWGIp == true){MPAneTWGIp = false;}
      if(netdonDuBA == true){netdonDuBA = false;}
      if(gzxYLpPPWt == true){gzxYLpPPWt = false;}
      if(NlazYTeyJt == true){NlazYTeyJt = false;}
      if(BbWUdLcbtQ == true){BbWUdLcbtQ = false;}
      if(YnfCcNRbbn == true){YnfCcNRbbn = false;}
      if(DGiOcCDuFU == true){DGiOcCDuFU = false;}
      if(IFlHyEcctA == true){IFlHyEcctA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XVXSEXUAGR
{ 
  void abMFGArFXK()
  { 
      bool jtofafeBcU = false;
      bool WksMEwTyXa = false;
      bool ycrFwFSbaF = false;
      bool pJLfrcNFbo = false;
      bool zlXVzqCQnu = false;
      bool JCjaKHCijV = false;
      bool NCaWeMYNTb = false;
      bool hNVhbMFWFE = false;
      bool DBmfwmYkVk = false;
      bool ZeVGbxKBpl = false;
      bool RnwMMwgBzx = false;
      bool BecfRLOuZq = false;
      bool nnriBDrOFe = false;
      bool BEfSlOEaSA = false;
      bool GXlXiuBonQ = false;
      bool hPazydwNLI = false;
      bool DRuUwxzJtD = false;
      bool HnbZkPCUAF = false;
      bool CCZowkdgUH = false;
      bool SqOKwnbRbk = false;
      string MGgylSjTah;
      string nnGogRjLep;
      string piXpqjnXiF;
      string gJZrRlELKn;
      string CYzfiWjpZn;
      string szYfBdhqGC;
      string eLjVBdONXu;
      string MYApnRjrGT;
      string zxxuLhktqn;
      string ENEIJpnceE;
      string IWSeaUyhqi;
      string spjmCgNoJS;
      string sTWjpzUrfx;
      string dGMBKceRTq;
      string iCCHuNcRFc;
      string bzTLLnzioa;
      string zGBtFldhbY;
      string BwURipROoc;
      string WDlDVdmApW;
      string cwcrqcAICI;
      if(MGgylSjTah == IWSeaUyhqi){jtofafeBcU = true;}
      else if(IWSeaUyhqi == MGgylSjTah){RnwMMwgBzx = true;}
      if(nnGogRjLep == spjmCgNoJS){WksMEwTyXa = true;}
      else if(spjmCgNoJS == nnGogRjLep){BecfRLOuZq = true;}
      if(piXpqjnXiF == sTWjpzUrfx){ycrFwFSbaF = true;}
      else if(sTWjpzUrfx == piXpqjnXiF){nnriBDrOFe = true;}
      if(gJZrRlELKn == dGMBKceRTq){pJLfrcNFbo = true;}
      else if(dGMBKceRTq == gJZrRlELKn){BEfSlOEaSA = true;}
      if(CYzfiWjpZn == iCCHuNcRFc){zlXVzqCQnu = true;}
      else if(iCCHuNcRFc == CYzfiWjpZn){GXlXiuBonQ = true;}
      if(szYfBdhqGC == bzTLLnzioa){JCjaKHCijV = true;}
      else if(bzTLLnzioa == szYfBdhqGC){hPazydwNLI = true;}
      if(eLjVBdONXu == zGBtFldhbY){NCaWeMYNTb = true;}
      else if(zGBtFldhbY == eLjVBdONXu){DRuUwxzJtD = true;}
      if(MYApnRjrGT == BwURipROoc){hNVhbMFWFE = true;}
      if(zxxuLhktqn == WDlDVdmApW){DBmfwmYkVk = true;}
      if(ENEIJpnceE == cwcrqcAICI){ZeVGbxKBpl = true;}
      while(BwURipROoc == MYApnRjrGT){HnbZkPCUAF = true;}
      while(WDlDVdmApW == WDlDVdmApW){CCZowkdgUH = true;}
      while(cwcrqcAICI == cwcrqcAICI){SqOKwnbRbk = true;}
      if(jtofafeBcU == true){jtofafeBcU = false;}
      if(WksMEwTyXa == true){WksMEwTyXa = false;}
      if(ycrFwFSbaF == true){ycrFwFSbaF = false;}
      if(pJLfrcNFbo == true){pJLfrcNFbo = false;}
      if(zlXVzqCQnu == true){zlXVzqCQnu = false;}
      if(JCjaKHCijV == true){JCjaKHCijV = false;}
      if(NCaWeMYNTb == true){NCaWeMYNTb = false;}
      if(hNVhbMFWFE == true){hNVhbMFWFE = false;}
      if(DBmfwmYkVk == true){DBmfwmYkVk = false;}
      if(ZeVGbxKBpl == true){ZeVGbxKBpl = false;}
      if(RnwMMwgBzx == true){RnwMMwgBzx = false;}
      if(BecfRLOuZq == true){BecfRLOuZq = false;}
      if(nnriBDrOFe == true){nnriBDrOFe = false;}
      if(BEfSlOEaSA == true){BEfSlOEaSA = false;}
      if(GXlXiuBonQ == true){GXlXiuBonQ = false;}
      if(hPazydwNLI == true){hPazydwNLI = false;}
      if(DRuUwxzJtD == true){DRuUwxzJtD = false;}
      if(HnbZkPCUAF == true){HnbZkPCUAF = false;}
      if(CCZowkdgUH == true){CCZowkdgUH = false;}
      if(SqOKwnbRbk == true){SqOKwnbRbk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AQZLAHLXRK
{ 
  void rSMtUbLIyz()
  { 
      bool edXGKuZlbp = false;
      bool oJcrkpCTow = false;
      bool jTwkfOqCBU = false;
      bool dTbBBqGMky = false;
      bool ytDlXOYNRm = false;
      bool wwVBRLgmau = false;
      bool DWkHMVgbqs = false;
      bool iohpxpPKNQ = false;
      bool ockNXgxaio = false;
      bool KTlouaIwZB = false;
      bool hxWYEHNeDb = false;
      bool wWZKFZlWie = false;
      bool YGsBiODruW = false;
      bool gSjMirGLIQ = false;
      bool TRXGsmtajU = false;
      bool nkNtcaEUpo = false;
      bool EUjftclNbN = false;
      bool TZNRLGilIu = false;
      bool UbIahuFpjH = false;
      bool mkVTMyhqLQ = false;
      string zGkQleRtBl;
      string EgxrXSPURZ;
      string yqNaIqrWoz;
      string aKsOoCBKRP;
      string QzxxDgJGGy;
      string cEpdWHsJHt;
      string ltFBLtniDV;
      string RFCBJysPWa;
      string hlQpWVTOqg;
      string IqCXcWtulJ;
      string saCkgXBnUY;
      string OcmfMAcOdo;
      string ZYqVMZCeYl;
      string DxcMhHieJz;
      string UftRSfEWLc;
      string seRwjUifYG;
      string VVPhUQAZyE;
      string RyFeTseYDf;
      string VeTwsYffcM;
      string YCGCdzPLxC;
      if(zGkQleRtBl == saCkgXBnUY){edXGKuZlbp = true;}
      else if(saCkgXBnUY == zGkQleRtBl){hxWYEHNeDb = true;}
      if(EgxrXSPURZ == OcmfMAcOdo){oJcrkpCTow = true;}
      else if(OcmfMAcOdo == EgxrXSPURZ){wWZKFZlWie = true;}
      if(yqNaIqrWoz == ZYqVMZCeYl){jTwkfOqCBU = true;}
      else if(ZYqVMZCeYl == yqNaIqrWoz){YGsBiODruW = true;}
      if(aKsOoCBKRP == DxcMhHieJz){dTbBBqGMky = true;}
      else if(DxcMhHieJz == aKsOoCBKRP){gSjMirGLIQ = true;}
      if(QzxxDgJGGy == UftRSfEWLc){ytDlXOYNRm = true;}
      else if(UftRSfEWLc == QzxxDgJGGy){TRXGsmtajU = true;}
      if(cEpdWHsJHt == seRwjUifYG){wwVBRLgmau = true;}
      else if(seRwjUifYG == cEpdWHsJHt){nkNtcaEUpo = true;}
      if(ltFBLtniDV == VVPhUQAZyE){DWkHMVgbqs = true;}
      else if(VVPhUQAZyE == ltFBLtniDV){EUjftclNbN = true;}
      if(RFCBJysPWa == RyFeTseYDf){iohpxpPKNQ = true;}
      if(hlQpWVTOqg == VeTwsYffcM){ockNXgxaio = true;}
      if(IqCXcWtulJ == YCGCdzPLxC){KTlouaIwZB = true;}
      while(RyFeTseYDf == RFCBJysPWa){TZNRLGilIu = true;}
      while(VeTwsYffcM == VeTwsYffcM){UbIahuFpjH = true;}
      while(YCGCdzPLxC == YCGCdzPLxC){mkVTMyhqLQ = true;}
      if(edXGKuZlbp == true){edXGKuZlbp = false;}
      if(oJcrkpCTow == true){oJcrkpCTow = false;}
      if(jTwkfOqCBU == true){jTwkfOqCBU = false;}
      if(dTbBBqGMky == true){dTbBBqGMky = false;}
      if(ytDlXOYNRm == true){ytDlXOYNRm = false;}
      if(wwVBRLgmau == true){wwVBRLgmau = false;}
      if(DWkHMVgbqs == true){DWkHMVgbqs = false;}
      if(iohpxpPKNQ == true){iohpxpPKNQ = false;}
      if(ockNXgxaio == true){ockNXgxaio = false;}
      if(KTlouaIwZB == true){KTlouaIwZB = false;}
      if(hxWYEHNeDb == true){hxWYEHNeDb = false;}
      if(wWZKFZlWie == true){wWZKFZlWie = false;}
      if(YGsBiODruW == true){YGsBiODruW = false;}
      if(gSjMirGLIQ == true){gSjMirGLIQ = false;}
      if(TRXGsmtajU == true){TRXGsmtajU = false;}
      if(nkNtcaEUpo == true){nkNtcaEUpo = false;}
      if(EUjftclNbN == true){EUjftclNbN = false;}
      if(TZNRLGilIu == true){TZNRLGilIu = false;}
      if(UbIahuFpjH == true){UbIahuFpjH = false;}
      if(mkVTMyhqLQ == true){mkVTMyhqLQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIFZJCRSUF
{ 
  void ThjZQLLTRm()
  { 
      bool CyuzGtIPUd = false;
      bool FmQExyZXsQ = false;
      bool cyeQjrerIY = false;
      bool PpTxUIoEPm = false;
      bool RHuKYRfmVx = false;
      bool ChlAnDSePO = false;
      bool OPGwOOSTin = false;
      bool IUIFzUCTqR = false;
      bool MrVLVgDTJR = false;
      bool oKoBXCBzwK = false;
      bool zLDgogZgBS = false;
      bool AymxBWstag = false;
      bool KzJRzxfGgw = false;
      bool TDXgSAnnVn = false;
      bool GWRpQqWqzB = false;
      bool IHYOzABkhq = false;
      bool BSzEzxaGeA = false;
      bool iEYlZmgTBI = false;
      bool ZoGfmLeIhS = false;
      bool yCFdmnXNqS = false;
      string NKnehGoQyr;
      string sabqDyVdDs;
      string mZmSVOxMgW;
      string EIQiyrxBbW;
      string kneTHMOGbe;
      string fYtilmWUJT;
      string IbjankJsrK;
      string BTBgIyuTLI;
      string zqkBqeNgxK;
      string VbrINIDDfW;
      string DUNQdLXMam;
      string rDJATRqijI;
      string WbwhoZbsSz;
      string uqnoFdcTWe;
      string HAGJSRSqow;
      string RUTWzaYfbD;
      string idtarAPUuo;
      string oWLEBVVlOW;
      string GkEWhaWQoe;
      string FwrTucGeRR;
      if(NKnehGoQyr == DUNQdLXMam){CyuzGtIPUd = true;}
      else if(DUNQdLXMam == NKnehGoQyr){zLDgogZgBS = true;}
      if(sabqDyVdDs == rDJATRqijI){FmQExyZXsQ = true;}
      else if(rDJATRqijI == sabqDyVdDs){AymxBWstag = true;}
      if(mZmSVOxMgW == WbwhoZbsSz){cyeQjrerIY = true;}
      else if(WbwhoZbsSz == mZmSVOxMgW){KzJRzxfGgw = true;}
      if(EIQiyrxBbW == uqnoFdcTWe){PpTxUIoEPm = true;}
      else if(uqnoFdcTWe == EIQiyrxBbW){TDXgSAnnVn = true;}
      if(kneTHMOGbe == HAGJSRSqow){RHuKYRfmVx = true;}
      else if(HAGJSRSqow == kneTHMOGbe){GWRpQqWqzB = true;}
      if(fYtilmWUJT == RUTWzaYfbD){ChlAnDSePO = true;}
      else if(RUTWzaYfbD == fYtilmWUJT){IHYOzABkhq = true;}
      if(IbjankJsrK == idtarAPUuo){OPGwOOSTin = true;}
      else if(idtarAPUuo == IbjankJsrK){BSzEzxaGeA = true;}
      if(BTBgIyuTLI == oWLEBVVlOW){IUIFzUCTqR = true;}
      if(zqkBqeNgxK == GkEWhaWQoe){MrVLVgDTJR = true;}
      if(VbrINIDDfW == FwrTucGeRR){oKoBXCBzwK = true;}
      while(oWLEBVVlOW == BTBgIyuTLI){iEYlZmgTBI = true;}
      while(GkEWhaWQoe == GkEWhaWQoe){ZoGfmLeIhS = true;}
      while(FwrTucGeRR == FwrTucGeRR){yCFdmnXNqS = true;}
      if(CyuzGtIPUd == true){CyuzGtIPUd = false;}
      if(FmQExyZXsQ == true){FmQExyZXsQ = false;}
      if(cyeQjrerIY == true){cyeQjrerIY = false;}
      if(PpTxUIoEPm == true){PpTxUIoEPm = false;}
      if(RHuKYRfmVx == true){RHuKYRfmVx = false;}
      if(ChlAnDSePO == true){ChlAnDSePO = false;}
      if(OPGwOOSTin == true){OPGwOOSTin = false;}
      if(IUIFzUCTqR == true){IUIFzUCTqR = false;}
      if(MrVLVgDTJR == true){MrVLVgDTJR = false;}
      if(oKoBXCBzwK == true){oKoBXCBzwK = false;}
      if(zLDgogZgBS == true){zLDgogZgBS = false;}
      if(AymxBWstag == true){AymxBWstag = false;}
      if(KzJRzxfGgw == true){KzJRzxfGgw = false;}
      if(TDXgSAnnVn == true){TDXgSAnnVn = false;}
      if(GWRpQqWqzB == true){GWRpQqWqzB = false;}
      if(IHYOzABkhq == true){IHYOzABkhq = false;}
      if(BSzEzxaGeA == true){BSzEzxaGeA = false;}
      if(iEYlZmgTBI == true){iEYlZmgTBI = false;}
      if(ZoGfmLeIhS == true){ZoGfmLeIhS = false;}
      if(yCFdmnXNqS == true){yCFdmnXNqS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHCRQCRACD
{ 
  void OZZPWpCyDL()
  { 
      bool eWdbKUxcco = false;
      bool EaWqXzSOEk = false;
      bool UmYhznwDFz = false;
      bool FJkDPOcTil = false;
      bool FGlprrSZJy = false;
      bool mIMMPryubV = false;
      bool YsWcitoTaI = false;
      bool WzfRfNAhpG = false;
      bool VWtGMxxYmX = false;
      bool QgqMNLiIGy = false;
      bool CzyAambtgB = false;
      bool qQFVACzQQl = false;
      bool xQfCrpISDT = false;
      bool dqarEVXseZ = false;
      bool VCrlgzbVML = false;
      bool LSrUBlTwIk = false;
      bool dIpMWzpMQd = false;
      bool dGkpPtXsVr = false;
      bool OmFrILzFqR = false;
      bool CbktuMLfOg = false;
      string xiGnWtbeKQ;
      string qxGZHDLitR;
      string BYWcXQXtkc;
      string PNPcjuJfzq;
      string eFUMDOHfbT;
      string CosmTYLcPG;
      string WhthBcgcpM;
      string tfiClwDKZJ;
      string IqSQZaUcIL;
      string ifPrUxLmKa;
      string hepPYVFpAX;
      string UBDGxfPcHa;
      string HDTecOPpho;
      string jPzyadBCrE;
      string UeckpgbJuo;
      string ghfiSeKLlK;
      string GOHLmFCEeS;
      string dMkDGcainu;
      string lGusHCjPfw;
      string TpQgxGWQxk;
      if(xiGnWtbeKQ == hepPYVFpAX){eWdbKUxcco = true;}
      else if(hepPYVFpAX == xiGnWtbeKQ){CzyAambtgB = true;}
      if(qxGZHDLitR == UBDGxfPcHa){EaWqXzSOEk = true;}
      else if(UBDGxfPcHa == qxGZHDLitR){qQFVACzQQl = true;}
      if(BYWcXQXtkc == HDTecOPpho){UmYhznwDFz = true;}
      else if(HDTecOPpho == BYWcXQXtkc){xQfCrpISDT = true;}
      if(PNPcjuJfzq == jPzyadBCrE){FJkDPOcTil = true;}
      else if(jPzyadBCrE == PNPcjuJfzq){dqarEVXseZ = true;}
      if(eFUMDOHfbT == UeckpgbJuo){FGlprrSZJy = true;}
      else if(UeckpgbJuo == eFUMDOHfbT){VCrlgzbVML = true;}
      if(CosmTYLcPG == ghfiSeKLlK){mIMMPryubV = true;}
      else if(ghfiSeKLlK == CosmTYLcPG){LSrUBlTwIk = true;}
      if(WhthBcgcpM == GOHLmFCEeS){YsWcitoTaI = true;}
      else if(GOHLmFCEeS == WhthBcgcpM){dIpMWzpMQd = true;}
      if(tfiClwDKZJ == dMkDGcainu){WzfRfNAhpG = true;}
      if(IqSQZaUcIL == lGusHCjPfw){VWtGMxxYmX = true;}
      if(ifPrUxLmKa == TpQgxGWQxk){QgqMNLiIGy = true;}
      while(dMkDGcainu == tfiClwDKZJ){dGkpPtXsVr = true;}
      while(lGusHCjPfw == lGusHCjPfw){OmFrILzFqR = true;}
      while(TpQgxGWQxk == TpQgxGWQxk){CbktuMLfOg = true;}
      if(eWdbKUxcco == true){eWdbKUxcco = false;}
      if(EaWqXzSOEk == true){EaWqXzSOEk = false;}
      if(UmYhznwDFz == true){UmYhznwDFz = false;}
      if(FJkDPOcTil == true){FJkDPOcTil = false;}
      if(FGlprrSZJy == true){FGlprrSZJy = false;}
      if(mIMMPryubV == true){mIMMPryubV = false;}
      if(YsWcitoTaI == true){YsWcitoTaI = false;}
      if(WzfRfNAhpG == true){WzfRfNAhpG = false;}
      if(VWtGMxxYmX == true){VWtGMxxYmX = false;}
      if(QgqMNLiIGy == true){QgqMNLiIGy = false;}
      if(CzyAambtgB == true){CzyAambtgB = false;}
      if(qQFVACzQQl == true){qQFVACzQQl = false;}
      if(xQfCrpISDT == true){xQfCrpISDT = false;}
      if(dqarEVXseZ == true){dqarEVXseZ = false;}
      if(VCrlgzbVML == true){VCrlgzbVML = false;}
      if(LSrUBlTwIk == true){LSrUBlTwIk = false;}
      if(dIpMWzpMQd == true){dIpMWzpMQd = false;}
      if(dGkpPtXsVr == true){dGkpPtXsVr = false;}
      if(OmFrILzFqR == true){OmFrILzFqR = false;}
      if(CbktuMLfOg == true){CbktuMLfOg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUTCKBVWXD
{ 
  void bkpTgiqXHS()
  { 
      bool PwizdiHfmf = false;
      bool PDVmucISNP = false;
      bool oJPXKohJFz = false;
      bool XTqcEJUbPI = false;
      bool MeMyornEII = false;
      bool jMoOQFgLno = false;
      bool AxamIwLsik = false;
      bool HgDFCKwRhS = false;
      bool BdBwPKebLy = false;
      bool cInaHPDZos = false;
      bool ftVWACJiMG = false;
      bool IPdUmWudWy = false;
      bool QigjIzscxl = false;
      bool GWbnmGHduN = false;
      bool BuPEoMeSmj = false;
      bool TYDqcwNkOB = false;
      bool JglZAlmpgg = false;
      bool ORhJwUTbuu = false;
      bool UZoNSgSkLq = false;
      bool rWOtEUJoEC = false;
      string eXtFWLeSun;
      string uGKTxwQEgt;
      string idzsYOkHxR;
      string YYKmonzPpS;
      string HHMQANhZIt;
      string zextzAXBgI;
      string ZXUcPVuXeI;
      string wAOOlaRhrK;
      string fLyCSsaQmo;
      string PyihrjliBe;
      string RKuzyzQiIY;
      string ipIVbOYRKV;
      string uekosxRgWC;
      string oifNrVPyET;
      string crIOGZpMFc;
      string KUXfimZFGB;
      string gjMFjzJtcG;
      string zaNqrDWViT;
      string GEasrTKAdF;
      string uJrDlseCeG;
      if(eXtFWLeSun == RKuzyzQiIY){PwizdiHfmf = true;}
      else if(RKuzyzQiIY == eXtFWLeSun){ftVWACJiMG = true;}
      if(uGKTxwQEgt == ipIVbOYRKV){PDVmucISNP = true;}
      else if(ipIVbOYRKV == uGKTxwQEgt){IPdUmWudWy = true;}
      if(idzsYOkHxR == uekosxRgWC){oJPXKohJFz = true;}
      else if(uekosxRgWC == idzsYOkHxR){QigjIzscxl = true;}
      if(YYKmonzPpS == oifNrVPyET){XTqcEJUbPI = true;}
      else if(oifNrVPyET == YYKmonzPpS){GWbnmGHduN = true;}
      if(HHMQANhZIt == crIOGZpMFc){MeMyornEII = true;}
      else if(crIOGZpMFc == HHMQANhZIt){BuPEoMeSmj = true;}
      if(zextzAXBgI == KUXfimZFGB){jMoOQFgLno = true;}
      else if(KUXfimZFGB == zextzAXBgI){TYDqcwNkOB = true;}
      if(ZXUcPVuXeI == gjMFjzJtcG){AxamIwLsik = true;}
      else if(gjMFjzJtcG == ZXUcPVuXeI){JglZAlmpgg = true;}
      if(wAOOlaRhrK == zaNqrDWViT){HgDFCKwRhS = true;}
      if(fLyCSsaQmo == GEasrTKAdF){BdBwPKebLy = true;}
      if(PyihrjliBe == uJrDlseCeG){cInaHPDZos = true;}
      while(zaNqrDWViT == wAOOlaRhrK){ORhJwUTbuu = true;}
      while(GEasrTKAdF == GEasrTKAdF){UZoNSgSkLq = true;}
      while(uJrDlseCeG == uJrDlseCeG){rWOtEUJoEC = true;}
      if(PwizdiHfmf == true){PwizdiHfmf = false;}
      if(PDVmucISNP == true){PDVmucISNP = false;}
      if(oJPXKohJFz == true){oJPXKohJFz = false;}
      if(XTqcEJUbPI == true){XTqcEJUbPI = false;}
      if(MeMyornEII == true){MeMyornEII = false;}
      if(jMoOQFgLno == true){jMoOQFgLno = false;}
      if(AxamIwLsik == true){AxamIwLsik = false;}
      if(HgDFCKwRhS == true){HgDFCKwRhS = false;}
      if(BdBwPKebLy == true){BdBwPKebLy = false;}
      if(cInaHPDZos == true){cInaHPDZos = false;}
      if(ftVWACJiMG == true){ftVWACJiMG = false;}
      if(IPdUmWudWy == true){IPdUmWudWy = false;}
      if(QigjIzscxl == true){QigjIzscxl = false;}
      if(GWbnmGHduN == true){GWbnmGHduN = false;}
      if(BuPEoMeSmj == true){BuPEoMeSmj = false;}
      if(TYDqcwNkOB == true){TYDqcwNkOB = false;}
      if(JglZAlmpgg == true){JglZAlmpgg = false;}
      if(ORhJwUTbuu == true){ORhJwUTbuu = false;}
      if(UZoNSgSkLq == true){UZoNSgSkLq = false;}
      if(rWOtEUJoEC == true){rWOtEUJoEC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKZGNPJSOI
{ 
  void gCLulsFTBL()
  { 
      bool LhuuGSAkxo = false;
      bool GaTsoabmOf = false;
      bool epHHGXeRRM = false;
      bool DyKNYrwgCw = false;
      bool WEHGKzpqKp = false;
      bool mDwnWUamoi = false;
      bool miSjlHQFTx = false;
      bool dujSJaiAwG = false;
      bool gmHaZzCVqE = false;
      bool RIqTJnkXUC = false;
      bool hjXNLqSceu = false;
      bool lZqhBzbqJl = false;
      bool FuOPeVDPJU = false;
      bool oLftXwPsOh = false;
      bool gYpuSrRISJ = false;
      bool MtNixmVIhp = false;
      bool nCTJGZtwKE = false;
      bool ihbbFfFSwm = false;
      bool EtxzItxxxk = false;
      bool aHKYtdFfor = false;
      string oUsorCyVHP;
      string EZjFbTVDSx;
      string TPwThhNfub;
      string oqIJXEpiEE;
      string ibSwbhmBtE;
      string PKJqnZYYHK;
      string nSZeaNQahX;
      string cmzOOrwzrz;
      string tMlqMegRVy;
      string fRbsPPBmVO;
      string QMSVacKtbu;
      string cYgHPaghSw;
      string fzFjqLKFyy;
      string qJddihsPQi;
      string TmoZUGkTco;
      string iSUYhQGidP;
      string REwdETuCYh;
      string hQRibsKeOk;
      string ZqcJOXoEuR;
      string aKkAROpLUB;
      if(oUsorCyVHP == QMSVacKtbu){LhuuGSAkxo = true;}
      else if(QMSVacKtbu == oUsorCyVHP){hjXNLqSceu = true;}
      if(EZjFbTVDSx == cYgHPaghSw){GaTsoabmOf = true;}
      else if(cYgHPaghSw == EZjFbTVDSx){lZqhBzbqJl = true;}
      if(TPwThhNfub == fzFjqLKFyy){epHHGXeRRM = true;}
      else if(fzFjqLKFyy == TPwThhNfub){FuOPeVDPJU = true;}
      if(oqIJXEpiEE == qJddihsPQi){DyKNYrwgCw = true;}
      else if(qJddihsPQi == oqIJXEpiEE){oLftXwPsOh = true;}
      if(ibSwbhmBtE == TmoZUGkTco){WEHGKzpqKp = true;}
      else if(TmoZUGkTco == ibSwbhmBtE){gYpuSrRISJ = true;}
      if(PKJqnZYYHK == iSUYhQGidP){mDwnWUamoi = true;}
      else if(iSUYhQGidP == PKJqnZYYHK){MtNixmVIhp = true;}
      if(nSZeaNQahX == REwdETuCYh){miSjlHQFTx = true;}
      else if(REwdETuCYh == nSZeaNQahX){nCTJGZtwKE = true;}
      if(cmzOOrwzrz == hQRibsKeOk){dujSJaiAwG = true;}
      if(tMlqMegRVy == ZqcJOXoEuR){gmHaZzCVqE = true;}
      if(fRbsPPBmVO == aKkAROpLUB){RIqTJnkXUC = true;}
      while(hQRibsKeOk == cmzOOrwzrz){ihbbFfFSwm = true;}
      while(ZqcJOXoEuR == ZqcJOXoEuR){EtxzItxxxk = true;}
      while(aKkAROpLUB == aKkAROpLUB){aHKYtdFfor = true;}
      if(LhuuGSAkxo == true){LhuuGSAkxo = false;}
      if(GaTsoabmOf == true){GaTsoabmOf = false;}
      if(epHHGXeRRM == true){epHHGXeRRM = false;}
      if(DyKNYrwgCw == true){DyKNYrwgCw = false;}
      if(WEHGKzpqKp == true){WEHGKzpqKp = false;}
      if(mDwnWUamoi == true){mDwnWUamoi = false;}
      if(miSjlHQFTx == true){miSjlHQFTx = false;}
      if(dujSJaiAwG == true){dujSJaiAwG = false;}
      if(gmHaZzCVqE == true){gmHaZzCVqE = false;}
      if(RIqTJnkXUC == true){RIqTJnkXUC = false;}
      if(hjXNLqSceu == true){hjXNLqSceu = false;}
      if(lZqhBzbqJl == true){lZqhBzbqJl = false;}
      if(FuOPeVDPJU == true){FuOPeVDPJU = false;}
      if(oLftXwPsOh == true){oLftXwPsOh = false;}
      if(gYpuSrRISJ == true){gYpuSrRISJ = false;}
      if(MtNixmVIhp == true){MtNixmVIhp = false;}
      if(nCTJGZtwKE == true){nCTJGZtwKE = false;}
      if(ihbbFfFSwm == true){ihbbFfFSwm = false;}
      if(EtxzItxxxk == true){EtxzItxxxk = false;}
      if(aHKYtdFfor == true){aHKYtdFfor = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOZAVYDXTO
{ 
  void hNhTiQVMiA()
  { 
      bool VMnCnIfJra = false;
      bool mgiKBXFAMH = false;
      bool VCBOwArCXF = false;
      bool oPkZxGSEYx = false;
      bool elnwhSelaM = false;
      bool zLZIYSLZGn = false;
      bool QckllXuJMu = false;
      bool FAbPbjOEfd = false;
      bool VFbLFcpcAe = false;
      bool tsykgCBCKK = false;
      bool XUYeHzjJgo = false;
      bool EGsbRKAYfI = false;
      bool gSJhAMCpiZ = false;
      bool hMtVFAfwEG = false;
      bool sfuLZnAVSV = false;
      bool BbVBcELpeu = false;
      bool wsZHGrLWWQ = false;
      bool dEUZPAWyIL = false;
      bool MfWNXGprrA = false;
      bool ooRJJAGnEg = false;
      string bjaFEmiKqs;
      string OCdtzNllMj;
      string otDtuaGiOq;
      string hgRUXDtgFO;
      string QgppmiaFBs;
      string PybpxhfgJc;
      string fAwzLgjIVw;
      string SEgxTHDNGL;
      string AAgVaiEbXp;
      string WNXbhQkpeF;
      string zSiEZLRdVo;
      string dRaxceSZXb;
      string cIjfYFgFPD;
      string WNiBMgRcuP;
      string RaFiLFlZyC;
      string yKRCcphDeT;
      string eMNSSQiZku;
      string NodIKBCBTT;
      string SGGNFLufXV;
      string zNxbjFMmPt;
      if(bjaFEmiKqs == zSiEZLRdVo){VMnCnIfJra = true;}
      else if(zSiEZLRdVo == bjaFEmiKqs){XUYeHzjJgo = true;}
      if(OCdtzNllMj == dRaxceSZXb){mgiKBXFAMH = true;}
      else if(dRaxceSZXb == OCdtzNllMj){EGsbRKAYfI = true;}
      if(otDtuaGiOq == cIjfYFgFPD){VCBOwArCXF = true;}
      else if(cIjfYFgFPD == otDtuaGiOq){gSJhAMCpiZ = true;}
      if(hgRUXDtgFO == WNiBMgRcuP){oPkZxGSEYx = true;}
      else if(WNiBMgRcuP == hgRUXDtgFO){hMtVFAfwEG = true;}
      if(QgppmiaFBs == RaFiLFlZyC){elnwhSelaM = true;}
      else if(RaFiLFlZyC == QgppmiaFBs){sfuLZnAVSV = true;}
      if(PybpxhfgJc == yKRCcphDeT){zLZIYSLZGn = true;}
      else if(yKRCcphDeT == PybpxhfgJc){BbVBcELpeu = true;}
      if(fAwzLgjIVw == eMNSSQiZku){QckllXuJMu = true;}
      else if(eMNSSQiZku == fAwzLgjIVw){wsZHGrLWWQ = true;}
      if(SEgxTHDNGL == NodIKBCBTT){FAbPbjOEfd = true;}
      if(AAgVaiEbXp == SGGNFLufXV){VFbLFcpcAe = true;}
      if(WNXbhQkpeF == zNxbjFMmPt){tsykgCBCKK = true;}
      while(NodIKBCBTT == SEgxTHDNGL){dEUZPAWyIL = true;}
      while(SGGNFLufXV == SGGNFLufXV){MfWNXGprrA = true;}
      while(zNxbjFMmPt == zNxbjFMmPt){ooRJJAGnEg = true;}
      if(VMnCnIfJra == true){VMnCnIfJra = false;}
      if(mgiKBXFAMH == true){mgiKBXFAMH = false;}
      if(VCBOwArCXF == true){VCBOwArCXF = false;}
      if(oPkZxGSEYx == true){oPkZxGSEYx = false;}
      if(elnwhSelaM == true){elnwhSelaM = false;}
      if(zLZIYSLZGn == true){zLZIYSLZGn = false;}
      if(QckllXuJMu == true){QckllXuJMu = false;}
      if(FAbPbjOEfd == true){FAbPbjOEfd = false;}
      if(VFbLFcpcAe == true){VFbLFcpcAe = false;}
      if(tsykgCBCKK == true){tsykgCBCKK = false;}
      if(XUYeHzjJgo == true){XUYeHzjJgo = false;}
      if(EGsbRKAYfI == true){EGsbRKAYfI = false;}
      if(gSJhAMCpiZ == true){gSJhAMCpiZ = false;}
      if(hMtVFAfwEG == true){hMtVFAfwEG = false;}
      if(sfuLZnAVSV == true){sfuLZnAVSV = false;}
      if(BbVBcELpeu == true){BbVBcELpeu = false;}
      if(wsZHGrLWWQ == true){wsZHGrLWWQ = false;}
      if(dEUZPAWyIL == true){dEUZPAWyIL = false;}
      if(MfWNXGprrA == true){MfWNXGprrA = false;}
      if(ooRJJAGnEg == true){ooRJJAGnEg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNKGTALPMI
{ 
  void aqyoZNcFLj()
  { 
      bool DnkqUYNJwr = false;
      bool RzzkNxACbk = false;
      bool ViVIhMSSIO = false;
      bool ldFlpKhHQj = false;
      bool WFqPJaHtke = false;
      bool ASblmTSbII = false;
      bool GuAhFnsNtD = false;
      bool OslqOPqFyH = false;
      bool FYhcOTCSyW = false;
      bool qFyHdaEJKV = false;
      bool gszhPGgjXX = false;
      bool bMdBDhNXTl = false;
      bool laOXLIudNm = false;
      bool KhtcZLYzMH = false;
      bool lRuatdbxEw = false;
      bool NgpYjGebWH = false;
      bool LCWjNtSBbr = false;
      bool INKLzTencg = false;
      bool gxZRYcrVrS = false;
      bool fxcFwiuKMA = false;
      string ZayQPGxuIZ;
      string TWrBUjPhCO;
      string rrXlECzdgb;
      string IapoWBQsXQ;
      string AUGtLEBNSu;
      string bJBgJgCMLM;
      string GTNfQrfCdT;
      string TVKkNXkdaz;
      string BkKlAzZIfo;
      string zDgLKgHacS;
      string XyjzbFyPSl;
      string uXlMKUJbfQ;
      string SXWoUPozag;
      string PKAIbCBKKt;
      string AKossaRUAo;
      string XeuMAAbteL;
      string QznkVkXdjI;
      string TyRkPHhcus;
      string yTylJjPnIb;
      string ZGfycBVDXI;
      if(ZayQPGxuIZ == XyjzbFyPSl){DnkqUYNJwr = true;}
      else if(XyjzbFyPSl == ZayQPGxuIZ){gszhPGgjXX = true;}
      if(TWrBUjPhCO == uXlMKUJbfQ){RzzkNxACbk = true;}
      else if(uXlMKUJbfQ == TWrBUjPhCO){bMdBDhNXTl = true;}
      if(rrXlECzdgb == SXWoUPozag){ViVIhMSSIO = true;}
      else if(SXWoUPozag == rrXlECzdgb){laOXLIudNm = true;}
      if(IapoWBQsXQ == PKAIbCBKKt){ldFlpKhHQj = true;}
      else if(PKAIbCBKKt == IapoWBQsXQ){KhtcZLYzMH = true;}
      if(AUGtLEBNSu == AKossaRUAo){WFqPJaHtke = true;}
      else if(AKossaRUAo == AUGtLEBNSu){lRuatdbxEw = true;}
      if(bJBgJgCMLM == XeuMAAbteL){ASblmTSbII = true;}
      else if(XeuMAAbteL == bJBgJgCMLM){NgpYjGebWH = true;}
      if(GTNfQrfCdT == QznkVkXdjI){GuAhFnsNtD = true;}
      else if(QznkVkXdjI == GTNfQrfCdT){LCWjNtSBbr = true;}
      if(TVKkNXkdaz == TyRkPHhcus){OslqOPqFyH = true;}
      if(BkKlAzZIfo == yTylJjPnIb){FYhcOTCSyW = true;}
      if(zDgLKgHacS == ZGfycBVDXI){qFyHdaEJKV = true;}
      while(TyRkPHhcus == TVKkNXkdaz){INKLzTencg = true;}
      while(yTylJjPnIb == yTylJjPnIb){gxZRYcrVrS = true;}
      while(ZGfycBVDXI == ZGfycBVDXI){fxcFwiuKMA = true;}
      if(DnkqUYNJwr == true){DnkqUYNJwr = false;}
      if(RzzkNxACbk == true){RzzkNxACbk = false;}
      if(ViVIhMSSIO == true){ViVIhMSSIO = false;}
      if(ldFlpKhHQj == true){ldFlpKhHQj = false;}
      if(WFqPJaHtke == true){WFqPJaHtke = false;}
      if(ASblmTSbII == true){ASblmTSbII = false;}
      if(GuAhFnsNtD == true){GuAhFnsNtD = false;}
      if(OslqOPqFyH == true){OslqOPqFyH = false;}
      if(FYhcOTCSyW == true){FYhcOTCSyW = false;}
      if(qFyHdaEJKV == true){qFyHdaEJKV = false;}
      if(gszhPGgjXX == true){gszhPGgjXX = false;}
      if(bMdBDhNXTl == true){bMdBDhNXTl = false;}
      if(laOXLIudNm == true){laOXLIudNm = false;}
      if(KhtcZLYzMH == true){KhtcZLYzMH = false;}
      if(lRuatdbxEw == true){lRuatdbxEw = false;}
      if(NgpYjGebWH == true){NgpYjGebWH = false;}
      if(LCWjNtSBbr == true){LCWjNtSBbr = false;}
      if(INKLzTencg == true){INKLzTencg = false;}
      if(gxZRYcrVrS == true){gxZRYcrVrS = false;}
      if(fxcFwiuKMA == true){fxcFwiuKMA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LNLOGKXPJV
{ 
  void NSJuCNlCZG()
  { 
      bool NIiZxNiOOT = false;
      bool ZrSdZFXntE = false;
      bool WytDBhKCLa = false;
      bool KoKwlMrJfc = false;
      bool YuWKSoTHVu = false;
      bool DObjAOOeXO = false;
      bool DfDnIjhVrN = false;
      bool MNHQfbbjkM = false;
      bool NCgPWwNZuW = false;
      bool xMlQZsqhBh = false;
      bool GxPHipGKEY = false;
      bool metKBAynRL = false;
      bool WHaUPzbqql = false;
      bool jshCFPmYgg = false;
      bool pCVWjSSaOZ = false;
      bool tCQoLzWtri = false;
      bool NOTRntwqEk = false;
      bool MZHkVUkDkw = false;
      bool gAbRrgcrqG = false;
      bool ssgxSahEhp = false;
      string QZJMuJKthN;
      string CUZoQzWDlA;
      string UqeyDSjFMS;
      string srGUufcMsi;
      string bGkYXUzDMU;
      string xJNLQYtKIb;
      string YFhPUKOFtj;
      string VJJDXNGGZi;
      string SgrqUiduEW;
      string lSDRJWYVDN;
      string FsIbzmzKmC;
      string SnkYIrMptl;
      string fTBXyDGrtB;
      string okDLdZXQqh;
      string iSHBEyheIQ;
      string KhaRgkrkdu;
      string gHQkMgjYui;
      string TwyLCNLzSz;
      string VbicqHJldr;
      string gllwAbCWoW;
      if(QZJMuJKthN == FsIbzmzKmC){NIiZxNiOOT = true;}
      else if(FsIbzmzKmC == QZJMuJKthN){GxPHipGKEY = true;}
      if(CUZoQzWDlA == SnkYIrMptl){ZrSdZFXntE = true;}
      else if(SnkYIrMptl == CUZoQzWDlA){metKBAynRL = true;}
      if(UqeyDSjFMS == fTBXyDGrtB){WytDBhKCLa = true;}
      else if(fTBXyDGrtB == UqeyDSjFMS){WHaUPzbqql = true;}
      if(srGUufcMsi == okDLdZXQqh){KoKwlMrJfc = true;}
      else if(okDLdZXQqh == srGUufcMsi){jshCFPmYgg = true;}
      if(bGkYXUzDMU == iSHBEyheIQ){YuWKSoTHVu = true;}
      else if(iSHBEyheIQ == bGkYXUzDMU){pCVWjSSaOZ = true;}
      if(xJNLQYtKIb == KhaRgkrkdu){DObjAOOeXO = true;}
      else if(KhaRgkrkdu == xJNLQYtKIb){tCQoLzWtri = true;}
      if(YFhPUKOFtj == gHQkMgjYui){DfDnIjhVrN = true;}
      else if(gHQkMgjYui == YFhPUKOFtj){NOTRntwqEk = true;}
      if(VJJDXNGGZi == TwyLCNLzSz){MNHQfbbjkM = true;}
      if(SgrqUiduEW == VbicqHJldr){NCgPWwNZuW = true;}
      if(lSDRJWYVDN == gllwAbCWoW){xMlQZsqhBh = true;}
      while(TwyLCNLzSz == VJJDXNGGZi){MZHkVUkDkw = true;}
      while(VbicqHJldr == VbicqHJldr){gAbRrgcrqG = true;}
      while(gllwAbCWoW == gllwAbCWoW){ssgxSahEhp = true;}
      if(NIiZxNiOOT == true){NIiZxNiOOT = false;}
      if(ZrSdZFXntE == true){ZrSdZFXntE = false;}
      if(WytDBhKCLa == true){WytDBhKCLa = false;}
      if(KoKwlMrJfc == true){KoKwlMrJfc = false;}
      if(YuWKSoTHVu == true){YuWKSoTHVu = false;}
      if(DObjAOOeXO == true){DObjAOOeXO = false;}
      if(DfDnIjhVrN == true){DfDnIjhVrN = false;}
      if(MNHQfbbjkM == true){MNHQfbbjkM = false;}
      if(NCgPWwNZuW == true){NCgPWwNZuW = false;}
      if(xMlQZsqhBh == true){xMlQZsqhBh = false;}
      if(GxPHipGKEY == true){GxPHipGKEY = false;}
      if(metKBAynRL == true){metKBAynRL = false;}
      if(WHaUPzbqql == true){WHaUPzbqql = false;}
      if(jshCFPmYgg == true){jshCFPmYgg = false;}
      if(pCVWjSSaOZ == true){pCVWjSSaOZ = false;}
      if(tCQoLzWtri == true){tCQoLzWtri = false;}
      if(NOTRntwqEk == true){NOTRntwqEk = false;}
      if(MZHkVUkDkw == true){MZHkVUkDkw = false;}
      if(gAbRrgcrqG == true){gAbRrgcrqG = false;}
      if(ssgxSahEhp == true){ssgxSahEhp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVKNYLPGMC
{ 
  void WiVBrqGsne()
  { 
      bool AZwGYVjsHx = false;
      bool wGOhImUSGU = false;
      bool hgoDGxEVgx = false;
      bool NwjDOQWskQ = false;
      bool OpZIcQIzoW = false;
      bool BNZjYSkszb = false;
      bool RNLJjzWKTq = false;
      bool PbgoFrHfao = false;
      bool oEgKwAVzew = false;
      bool fdsJzBdPYc = false;
      bool txfxGYfkdf = false;
      bool KESJmMfBMj = false;
      bool dWfXLliXoE = false;
      bool OrHxtqXiEX = false;
      bool TjVykaLiVm = false;
      bool UbCoyXQIlT = false;
      bool pIuYRSwUOu = false;
      bool oxwoPtAhlj = false;
      bool azBCjloRyW = false;
      bool aOxjgLoxgR = false;
      string bEkXLrcZiW;
      string mssJSnyWBZ;
      string RbmrVnRAAL;
      string QoamMCJDEl;
      string CtPruuNIrq;
      string uVxLszQrCW;
      string abZWFxSGxP;
      string duRPWWMtxa;
      string ZIIJPurOtM;
      string lQBhLaUrly;
      string bHKbMAEhnV;
      string mWuaxRSQHK;
      string FDMkdMsjEu;
      string CUIzySxfwP;
      string pKZXZOVZjs;
      string IDkarYuZxz;
      string GUcsTROucd;
      string UmTqTtcnLP;
      string qTzKmyjgGY;
      string XWhxJVggEH;
      if(bEkXLrcZiW == bHKbMAEhnV){AZwGYVjsHx = true;}
      else if(bHKbMAEhnV == bEkXLrcZiW){txfxGYfkdf = true;}
      if(mssJSnyWBZ == mWuaxRSQHK){wGOhImUSGU = true;}
      else if(mWuaxRSQHK == mssJSnyWBZ){KESJmMfBMj = true;}
      if(RbmrVnRAAL == FDMkdMsjEu){hgoDGxEVgx = true;}
      else if(FDMkdMsjEu == RbmrVnRAAL){dWfXLliXoE = true;}
      if(QoamMCJDEl == CUIzySxfwP){NwjDOQWskQ = true;}
      else if(CUIzySxfwP == QoamMCJDEl){OrHxtqXiEX = true;}
      if(CtPruuNIrq == pKZXZOVZjs){OpZIcQIzoW = true;}
      else if(pKZXZOVZjs == CtPruuNIrq){TjVykaLiVm = true;}
      if(uVxLszQrCW == IDkarYuZxz){BNZjYSkszb = true;}
      else if(IDkarYuZxz == uVxLszQrCW){UbCoyXQIlT = true;}
      if(abZWFxSGxP == GUcsTROucd){RNLJjzWKTq = true;}
      else if(GUcsTROucd == abZWFxSGxP){pIuYRSwUOu = true;}
      if(duRPWWMtxa == UmTqTtcnLP){PbgoFrHfao = true;}
      if(ZIIJPurOtM == qTzKmyjgGY){oEgKwAVzew = true;}
      if(lQBhLaUrly == XWhxJVggEH){fdsJzBdPYc = true;}
      while(UmTqTtcnLP == duRPWWMtxa){oxwoPtAhlj = true;}
      while(qTzKmyjgGY == qTzKmyjgGY){azBCjloRyW = true;}
      while(XWhxJVggEH == XWhxJVggEH){aOxjgLoxgR = true;}
      if(AZwGYVjsHx == true){AZwGYVjsHx = false;}
      if(wGOhImUSGU == true){wGOhImUSGU = false;}
      if(hgoDGxEVgx == true){hgoDGxEVgx = false;}
      if(NwjDOQWskQ == true){NwjDOQWskQ = false;}
      if(OpZIcQIzoW == true){OpZIcQIzoW = false;}
      if(BNZjYSkszb == true){BNZjYSkszb = false;}
      if(RNLJjzWKTq == true){RNLJjzWKTq = false;}
      if(PbgoFrHfao == true){PbgoFrHfao = false;}
      if(oEgKwAVzew == true){oEgKwAVzew = false;}
      if(fdsJzBdPYc == true){fdsJzBdPYc = false;}
      if(txfxGYfkdf == true){txfxGYfkdf = false;}
      if(KESJmMfBMj == true){KESJmMfBMj = false;}
      if(dWfXLliXoE == true){dWfXLliXoE = false;}
      if(OrHxtqXiEX == true){OrHxtqXiEX = false;}
      if(TjVykaLiVm == true){TjVykaLiVm = false;}
      if(UbCoyXQIlT == true){UbCoyXQIlT = false;}
      if(pIuYRSwUOu == true){pIuYRSwUOu = false;}
      if(oxwoPtAhlj == true){oxwoPtAhlj = false;}
      if(azBCjloRyW == true){azBCjloRyW = false;}
      if(aOxjgLoxgR == true){aOxjgLoxgR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCZRCWXDAJ
{ 
  void EXugcotaVS()
  { 
      bool ORIMPLJmmg = false;
      bool dWrSVbXgJB = false;
      bool yhAfyrmAyB = false;
      bool nmfPkKuHdF = false;
      bool ilbuKnuHrZ = false;
      bool HJiEZfQcOX = false;
      bool XJnlrqpbhK = false;
      bool fPCESLGFUK = false;
      bool xfHXseEapE = false;
      bool sSsGgYxpCT = false;
      bool xSYgsrGelN = false;
      bool ZKHEaqCQrM = false;
      bool lPldQNVuWs = false;
      bool NPCANdHZdA = false;
      bool XYncdiKoeo = false;
      bool VgxpggguPf = false;
      bool VKIszKIGpw = false;
      bool jclqnNbIAh = false;
      bool CgQgWgRMTf = false;
      bool wLJydMQucS = false;
      string usufFHrwOz;
      string XDrOwGKfag;
      string bdAiBNTMlm;
      string jqUqynXdpl;
      string KJwpmqxhnE;
      string sZHldRrLer;
      string meJbPfhBQI;
      string ifpoVRgKuJ;
      string PlYhtJjiNf;
      string uLzyyfAUaH;
      string JwQfVMjSPM;
      string jhQUbBGagG;
      string wzmjMWgqqp;
      string RMjmASUrMg;
      string YRSBuMtdVw;
      string YYmULKIgSy;
      string esaZtXycUI;
      string fNOAgeflnz;
      string bDUtQsYPbo;
      string KnZOBfprGX;
      if(usufFHrwOz == JwQfVMjSPM){ORIMPLJmmg = true;}
      else if(JwQfVMjSPM == usufFHrwOz){xSYgsrGelN = true;}
      if(XDrOwGKfag == jhQUbBGagG){dWrSVbXgJB = true;}
      else if(jhQUbBGagG == XDrOwGKfag){ZKHEaqCQrM = true;}
      if(bdAiBNTMlm == wzmjMWgqqp){yhAfyrmAyB = true;}
      else if(wzmjMWgqqp == bdAiBNTMlm){lPldQNVuWs = true;}
      if(jqUqynXdpl == RMjmASUrMg){nmfPkKuHdF = true;}
      else if(RMjmASUrMg == jqUqynXdpl){NPCANdHZdA = true;}
      if(KJwpmqxhnE == YRSBuMtdVw){ilbuKnuHrZ = true;}
      else if(YRSBuMtdVw == KJwpmqxhnE){XYncdiKoeo = true;}
      if(sZHldRrLer == YYmULKIgSy){HJiEZfQcOX = true;}
      else if(YYmULKIgSy == sZHldRrLer){VgxpggguPf = true;}
      if(meJbPfhBQI == esaZtXycUI){XJnlrqpbhK = true;}
      else if(esaZtXycUI == meJbPfhBQI){VKIszKIGpw = true;}
      if(ifpoVRgKuJ == fNOAgeflnz){fPCESLGFUK = true;}
      if(PlYhtJjiNf == bDUtQsYPbo){xfHXseEapE = true;}
      if(uLzyyfAUaH == KnZOBfprGX){sSsGgYxpCT = true;}
      while(fNOAgeflnz == ifpoVRgKuJ){jclqnNbIAh = true;}
      while(bDUtQsYPbo == bDUtQsYPbo){CgQgWgRMTf = true;}
      while(KnZOBfprGX == KnZOBfprGX){wLJydMQucS = true;}
      if(ORIMPLJmmg == true){ORIMPLJmmg = false;}
      if(dWrSVbXgJB == true){dWrSVbXgJB = false;}
      if(yhAfyrmAyB == true){yhAfyrmAyB = false;}
      if(nmfPkKuHdF == true){nmfPkKuHdF = false;}
      if(ilbuKnuHrZ == true){ilbuKnuHrZ = false;}
      if(HJiEZfQcOX == true){HJiEZfQcOX = false;}
      if(XJnlrqpbhK == true){XJnlrqpbhK = false;}
      if(fPCESLGFUK == true){fPCESLGFUK = false;}
      if(xfHXseEapE == true){xfHXseEapE = false;}
      if(sSsGgYxpCT == true){sSsGgYxpCT = false;}
      if(xSYgsrGelN == true){xSYgsrGelN = false;}
      if(ZKHEaqCQrM == true){ZKHEaqCQrM = false;}
      if(lPldQNVuWs == true){lPldQNVuWs = false;}
      if(NPCANdHZdA == true){NPCANdHZdA = false;}
      if(XYncdiKoeo == true){XYncdiKoeo = false;}
      if(VgxpggguPf == true){VgxpggguPf = false;}
      if(VKIszKIGpw == true){VKIszKIGpw = false;}
      if(jclqnNbIAh == true){jclqnNbIAh = false;}
      if(CgQgWgRMTf == true){CgQgWgRMTf = false;}
      if(wLJydMQucS == true){wLJydMQucS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJBQNUTVWN
{ 
  void GrICCqMUzp()
  { 
      bool IzYIJALwem = false;
      bool khLoBRBAqr = false;
      bool hcWQJZexwe = false;
      bool sVtbOJZwtq = false;
      bool SpTsLoEEfh = false;
      bool rNAHhfcHzi = false;
      bool VNAAtPmiZq = false;
      bool rEGzZqIcET = false;
      bool UZRNleUmsi = false;
      bool gRxKVEpTzw = false;
      bool CUdopnHBhq = false;
      bool WzDeOuwmNO = false;
      bool tAoqJaHucU = false;
      bool BodIRzwcWy = false;
      bool WTFCMhNRwa = false;
      bool ICGjBCemeO = false;
      bool gMXMogUtNO = false;
      bool zTPOraumeb = false;
      bool MozCMzitGP = false;
      bool UJxIRKwrNe = false;
      string SBqjDcXQmB;
      string qHVzBFfRrZ;
      string cboOmaKTfG;
      string XssmecKuzd;
      string GwnHSCeEsR;
      string mTUSXpMbwc;
      string REjgcxOhUY;
      string ujROSfngwk;
      string wGZOSDXZPo;
      string QhyWLCLGdU;
      string nwjUWCCGzq;
      string CeeLgLdVNZ;
      string ZnSeIMluCQ;
      string UgDbxAVFqQ;
      string BRaXlkDmoz;
      string XpsEuzcEMK;
      string QGDiWVbDOg;
      string pXdwYHNusW;
      string JyFDrdmzgx;
      string WQsgAtOqAQ;
      if(SBqjDcXQmB == nwjUWCCGzq){IzYIJALwem = true;}
      else if(nwjUWCCGzq == SBqjDcXQmB){CUdopnHBhq = true;}
      if(qHVzBFfRrZ == CeeLgLdVNZ){khLoBRBAqr = true;}
      else if(CeeLgLdVNZ == qHVzBFfRrZ){WzDeOuwmNO = true;}
      if(cboOmaKTfG == ZnSeIMluCQ){hcWQJZexwe = true;}
      else if(ZnSeIMluCQ == cboOmaKTfG){tAoqJaHucU = true;}
      if(XssmecKuzd == UgDbxAVFqQ){sVtbOJZwtq = true;}
      else if(UgDbxAVFqQ == XssmecKuzd){BodIRzwcWy = true;}
      if(GwnHSCeEsR == BRaXlkDmoz){SpTsLoEEfh = true;}
      else if(BRaXlkDmoz == GwnHSCeEsR){WTFCMhNRwa = true;}
      if(mTUSXpMbwc == XpsEuzcEMK){rNAHhfcHzi = true;}
      else if(XpsEuzcEMK == mTUSXpMbwc){ICGjBCemeO = true;}
      if(REjgcxOhUY == QGDiWVbDOg){VNAAtPmiZq = true;}
      else if(QGDiWVbDOg == REjgcxOhUY){gMXMogUtNO = true;}
      if(ujROSfngwk == pXdwYHNusW){rEGzZqIcET = true;}
      if(wGZOSDXZPo == JyFDrdmzgx){UZRNleUmsi = true;}
      if(QhyWLCLGdU == WQsgAtOqAQ){gRxKVEpTzw = true;}
      while(pXdwYHNusW == ujROSfngwk){zTPOraumeb = true;}
      while(JyFDrdmzgx == JyFDrdmzgx){MozCMzitGP = true;}
      while(WQsgAtOqAQ == WQsgAtOqAQ){UJxIRKwrNe = true;}
      if(IzYIJALwem == true){IzYIJALwem = false;}
      if(khLoBRBAqr == true){khLoBRBAqr = false;}
      if(hcWQJZexwe == true){hcWQJZexwe = false;}
      if(sVtbOJZwtq == true){sVtbOJZwtq = false;}
      if(SpTsLoEEfh == true){SpTsLoEEfh = false;}
      if(rNAHhfcHzi == true){rNAHhfcHzi = false;}
      if(VNAAtPmiZq == true){VNAAtPmiZq = false;}
      if(rEGzZqIcET == true){rEGzZqIcET = false;}
      if(UZRNleUmsi == true){UZRNleUmsi = false;}
      if(gRxKVEpTzw == true){gRxKVEpTzw = false;}
      if(CUdopnHBhq == true){CUdopnHBhq = false;}
      if(WzDeOuwmNO == true){WzDeOuwmNO = false;}
      if(tAoqJaHucU == true){tAoqJaHucU = false;}
      if(BodIRzwcWy == true){BodIRzwcWy = false;}
      if(WTFCMhNRwa == true){WTFCMhNRwa = false;}
      if(ICGjBCemeO == true){ICGjBCemeO = false;}
      if(gMXMogUtNO == true){gMXMogUtNO = false;}
      if(zTPOraumeb == true){zTPOraumeb = false;}
      if(MozCMzitGP == true){MozCMzitGP = false;}
      if(UJxIRKwrNe == true){UJxIRKwrNe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWFKZZOKHQ
{ 
  void aMZiPhzbld()
  { 
      bool OgeNAKrsnM = false;
      bool jfEceYYwfG = false;
      bool TkszOFKfIG = false;
      bool dfPNDAYUxf = false;
      bool yGadxeMxIL = false;
      bool tmYptdnfzt = false;
      bool zMkhhEPqZd = false;
      bool zDyAHMKPBi = false;
      bool rNWwLqHZTY = false;
      bool MsVCflVrus = false;
      bool PVWdLpnXhg = false;
      bool TYdPClonVq = false;
      bool xpXBRFguUV = false;
      bool qRTHTWprkV = false;
      bool CiqmFnPGAs = false;
      bool wgVEwZxVMF = false;
      bool IsDMoBEVue = false;
      bool uwDAoOykuc = false;
      bool pataZKwPLt = false;
      bool YUfeMIeexE = false;
      string WnEAzoKcee;
      string EnscqNpnQE;
      string BkQZYPeCtR;
      string XWnlcQwZAC;
      string MQFWwjJqDf;
      string JRdBmlWdaj;
      string JHiNHhAHAZ;
      string RPmOrkesdo;
      string GnzOHFrlyp;
      string sRzQrEgrPO;
      string jCpcNtdPJC;
      string HdAlcUIUFB;
      string oNJJgAQVVm;
      string DmdPEDyVBN;
      string bcbuiORMmX;
      string wMlOYVsfuN;
      string cHtWyUAjhZ;
      string WlTrZMkNaR;
      string hEiypqAOph;
      string KRamjTiFxN;
      if(WnEAzoKcee == jCpcNtdPJC){OgeNAKrsnM = true;}
      else if(jCpcNtdPJC == WnEAzoKcee){PVWdLpnXhg = true;}
      if(EnscqNpnQE == HdAlcUIUFB){jfEceYYwfG = true;}
      else if(HdAlcUIUFB == EnscqNpnQE){TYdPClonVq = true;}
      if(BkQZYPeCtR == oNJJgAQVVm){TkszOFKfIG = true;}
      else if(oNJJgAQVVm == BkQZYPeCtR){xpXBRFguUV = true;}
      if(XWnlcQwZAC == DmdPEDyVBN){dfPNDAYUxf = true;}
      else if(DmdPEDyVBN == XWnlcQwZAC){qRTHTWprkV = true;}
      if(MQFWwjJqDf == bcbuiORMmX){yGadxeMxIL = true;}
      else if(bcbuiORMmX == MQFWwjJqDf){CiqmFnPGAs = true;}
      if(JRdBmlWdaj == wMlOYVsfuN){tmYptdnfzt = true;}
      else if(wMlOYVsfuN == JRdBmlWdaj){wgVEwZxVMF = true;}
      if(JHiNHhAHAZ == cHtWyUAjhZ){zMkhhEPqZd = true;}
      else if(cHtWyUAjhZ == JHiNHhAHAZ){IsDMoBEVue = true;}
      if(RPmOrkesdo == WlTrZMkNaR){zDyAHMKPBi = true;}
      if(GnzOHFrlyp == hEiypqAOph){rNWwLqHZTY = true;}
      if(sRzQrEgrPO == KRamjTiFxN){MsVCflVrus = true;}
      while(WlTrZMkNaR == RPmOrkesdo){uwDAoOykuc = true;}
      while(hEiypqAOph == hEiypqAOph){pataZKwPLt = true;}
      while(KRamjTiFxN == KRamjTiFxN){YUfeMIeexE = true;}
      if(OgeNAKrsnM == true){OgeNAKrsnM = false;}
      if(jfEceYYwfG == true){jfEceYYwfG = false;}
      if(TkszOFKfIG == true){TkszOFKfIG = false;}
      if(dfPNDAYUxf == true){dfPNDAYUxf = false;}
      if(yGadxeMxIL == true){yGadxeMxIL = false;}
      if(tmYptdnfzt == true){tmYptdnfzt = false;}
      if(zMkhhEPqZd == true){zMkhhEPqZd = false;}
      if(zDyAHMKPBi == true){zDyAHMKPBi = false;}
      if(rNWwLqHZTY == true){rNWwLqHZTY = false;}
      if(MsVCflVrus == true){MsVCflVrus = false;}
      if(PVWdLpnXhg == true){PVWdLpnXhg = false;}
      if(TYdPClonVq == true){TYdPClonVq = false;}
      if(xpXBRFguUV == true){xpXBRFguUV = false;}
      if(qRTHTWprkV == true){qRTHTWprkV = false;}
      if(CiqmFnPGAs == true){CiqmFnPGAs = false;}
      if(wgVEwZxVMF == true){wgVEwZxVMF = false;}
      if(IsDMoBEVue == true){IsDMoBEVue = false;}
      if(uwDAoOykuc == true){uwDAoOykuc = false;}
      if(pataZKwPLt == true){pataZKwPLt = false;}
      if(YUfeMIeexE == true){YUfeMIeexE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ISNHTETPDI
{ 
  void fkBhIUOXKq()
  { 
      bool tZFkrmlcUH = false;
      bool SZbKdUhnLQ = false;
      bool zwJxTqjmMB = false;
      bool BDeElmSHZn = false;
      bool CshcPUBqZL = false;
      bool srwcqxPIRB = false;
      bool DzQTFOtWYq = false;
      bool BZNWNFNggy = false;
      bool prMAHIGCMn = false;
      bool WJpYjDbOWA = false;
      bool adRiJSeZOl = false;
      bool ihbTLLlPLw = false;
      bool IqKjUqjnmK = false;
      bool czKfXLZdqo = false;
      bool dgmaEnhVNY = false;
      bool QLCZriThOR = false;
      bool iplEIjXwuz = false;
      bool kHYWSbDiff = false;
      bool JNaNsQwkmn = false;
      bool qrPYGntiRU = false;
      string EDCRzosXMz;
      string cVWAFOHasD;
      string JLTxadpCOS;
      string sdedSgsTbf;
      string wZgkKcPMpt;
      string pUBtHrjFpV;
      string yqItFyqshX;
      string VmzNGjehly;
      string OdLUbYbjVZ;
      string xndGgFRmeM;
      string kVdRYDUnnX;
      string NCTrGTfmRg;
      string WHWHagJsfB;
      string SrCZMszsuY;
      string DnuyMtTkzM;
      string ZdVyodyWqq;
      string sbHmEVAteN;
      string UlqrchLYuf;
      string MYsSbnWDjh;
      string tcCEfbgIsp;
      if(EDCRzosXMz == kVdRYDUnnX){tZFkrmlcUH = true;}
      else if(kVdRYDUnnX == EDCRzosXMz){adRiJSeZOl = true;}
      if(cVWAFOHasD == NCTrGTfmRg){SZbKdUhnLQ = true;}
      else if(NCTrGTfmRg == cVWAFOHasD){ihbTLLlPLw = true;}
      if(JLTxadpCOS == WHWHagJsfB){zwJxTqjmMB = true;}
      else if(WHWHagJsfB == JLTxadpCOS){IqKjUqjnmK = true;}
      if(sdedSgsTbf == SrCZMszsuY){BDeElmSHZn = true;}
      else if(SrCZMszsuY == sdedSgsTbf){czKfXLZdqo = true;}
      if(wZgkKcPMpt == DnuyMtTkzM){CshcPUBqZL = true;}
      else if(DnuyMtTkzM == wZgkKcPMpt){dgmaEnhVNY = true;}
      if(pUBtHrjFpV == ZdVyodyWqq){srwcqxPIRB = true;}
      else if(ZdVyodyWqq == pUBtHrjFpV){QLCZriThOR = true;}
      if(yqItFyqshX == sbHmEVAteN){DzQTFOtWYq = true;}
      else if(sbHmEVAteN == yqItFyqshX){iplEIjXwuz = true;}
      if(VmzNGjehly == UlqrchLYuf){BZNWNFNggy = true;}
      if(OdLUbYbjVZ == MYsSbnWDjh){prMAHIGCMn = true;}
      if(xndGgFRmeM == tcCEfbgIsp){WJpYjDbOWA = true;}
      while(UlqrchLYuf == VmzNGjehly){kHYWSbDiff = true;}
      while(MYsSbnWDjh == MYsSbnWDjh){JNaNsQwkmn = true;}
      while(tcCEfbgIsp == tcCEfbgIsp){qrPYGntiRU = true;}
      if(tZFkrmlcUH == true){tZFkrmlcUH = false;}
      if(SZbKdUhnLQ == true){SZbKdUhnLQ = false;}
      if(zwJxTqjmMB == true){zwJxTqjmMB = false;}
      if(BDeElmSHZn == true){BDeElmSHZn = false;}
      if(CshcPUBqZL == true){CshcPUBqZL = false;}
      if(srwcqxPIRB == true){srwcqxPIRB = false;}
      if(DzQTFOtWYq == true){DzQTFOtWYq = false;}
      if(BZNWNFNggy == true){BZNWNFNggy = false;}
      if(prMAHIGCMn == true){prMAHIGCMn = false;}
      if(WJpYjDbOWA == true){WJpYjDbOWA = false;}
      if(adRiJSeZOl == true){adRiJSeZOl = false;}
      if(ihbTLLlPLw == true){ihbTLLlPLw = false;}
      if(IqKjUqjnmK == true){IqKjUqjnmK = false;}
      if(czKfXLZdqo == true){czKfXLZdqo = false;}
      if(dgmaEnhVNY == true){dgmaEnhVNY = false;}
      if(QLCZriThOR == true){QLCZriThOR = false;}
      if(iplEIjXwuz == true){iplEIjXwuz = false;}
      if(kHYWSbDiff == true){kHYWSbDiff = false;}
      if(JNaNsQwkmn == true){JNaNsQwkmn = false;}
      if(qrPYGntiRU == true){qrPYGntiRU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZPVOFEDTJR
{ 
  void nkZiwVpXAP()
  { 
      bool hWEJafhBJm = false;
      bool PGQNErCpyk = false;
      bool cCEQhJMCHQ = false;
      bool pKJOIVqqir = false;
      bool kXwUZQWdGo = false;
      bool WkDQTeRnbQ = false;
      bool TfsswEwCFi = false;
      bool BLGFzFGiqQ = false;
      bool mhuSsFHstc = false;
      bool DDOSYFdDYU = false;
      bool TUYXmLdyRO = false;
      bool XhwKdkjazq = false;
      bool xDHbeywngs = false;
      bool aDKVxRJXeh = false;
      bool aIbfEVGEnm = false;
      bool VDDhXPMxrn = false;
      bool OpQXnUWaML = false;
      bool bLwQPnbbWJ = false;
      bool rrzsXXzcxg = false;
      bool ELepTkqDrj = false;
      string pGtlWrsxeB;
      string RbTjojZzhU;
      string ACOIiCWJtB;
      string kPkaGzwkbJ;
      string WThlyEcRaM;
      string joGeAnrkCT;
      string UjCdQBqrdo;
      string moWXxfUbKe;
      string ZFhgRuJGaS;
      string HKhIomQDVx;
      string NjnlYuRigT;
      string SPaXtPBVMU;
      string rkRKhbGOiK;
      string PQGNRoQwHW;
      string daYGzqjKOY;
      string kuqAEbRcEw;
      string nDzWECINGE;
      string yENpqRMLLp;
      string ruAJYTYGIo;
      string WnrKhZaBBx;
      if(pGtlWrsxeB == NjnlYuRigT){hWEJafhBJm = true;}
      else if(NjnlYuRigT == pGtlWrsxeB){TUYXmLdyRO = true;}
      if(RbTjojZzhU == SPaXtPBVMU){PGQNErCpyk = true;}
      else if(SPaXtPBVMU == RbTjojZzhU){XhwKdkjazq = true;}
      if(ACOIiCWJtB == rkRKhbGOiK){cCEQhJMCHQ = true;}
      else if(rkRKhbGOiK == ACOIiCWJtB){xDHbeywngs = true;}
      if(kPkaGzwkbJ == PQGNRoQwHW){pKJOIVqqir = true;}
      else if(PQGNRoQwHW == kPkaGzwkbJ){aDKVxRJXeh = true;}
      if(WThlyEcRaM == daYGzqjKOY){kXwUZQWdGo = true;}
      else if(daYGzqjKOY == WThlyEcRaM){aIbfEVGEnm = true;}
      if(joGeAnrkCT == kuqAEbRcEw){WkDQTeRnbQ = true;}
      else if(kuqAEbRcEw == joGeAnrkCT){VDDhXPMxrn = true;}
      if(UjCdQBqrdo == nDzWECINGE){TfsswEwCFi = true;}
      else if(nDzWECINGE == UjCdQBqrdo){OpQXnUWaML = true;}
      if(moWXxfUbKe == yENpqRMLLp){BLGFzFGiqQ = true;}
      if(ZFhgRuJGaS == ruAJYTYGIo){mhuSsFHstc = true;}
      if(HKhIomQDVx == WnrKhZaBBx){DDOSYFdDYU = true;}
      while(yENpqRMLLp == moWXxfUbKe){bLwQPnbbWJ = true;}
      while(ruAJYTYGIo == ruAJYTYGIo){rrzsXXzcxg = true;}
      while(WnrKhZaBBx == WnrKhZaBBx){ELepTkqDrj = true;}
      if(hWEJafhBJm == true){hWEJafhBJm = false;}
      if(PGQNErCpyk == true){PGQNErCpyk = false;}
      if(cCEQhJMCHQ == true){cCEQhJMCHQ = false;}
      if(pKJOIVqqir == true){pKJOIVqqir = false;}
      if(kXwUZQWdGo == true){kXwUZQWdGo = false;}
      if(WkDQTeRnbQ == true){WkDQTeRnbQ = false;}
      if(TfsswEwCFi == true){TfsswEwCFi = false;}
      if(BLGFzFGiqQ == true){BLGFzFGiqQ = false;}
      if(mhuSsFHstc == true){mhuSsFHstc = false;}
      if(DDOSYFdDYU == true){DDOSYFdDYU = false;}
      if(TUYXmLdyRO == true){TUYXmLdyRO = false;}
      if(XhwKdkjazq == true){XhwKdkjazq = false;}
      if(xDHbeywngs == true){xDHbeywngs = false;}
      if(aDKVxRJXeh == true){aDKVxRJXeh = false;}
      if(aIbfEVGEnm == true){aIbfEVGEnm = false;}
      if(VDDhXPMxrn == true){VDDhXPMxrn = false;}
      if(OpQXnUWaML == true){OpQXnUWaML = false;}
      if(bLwQPnbbWJ == true){bLwQPnbbWJ = false;}
      if(rrzsXXzcxg == true){rrzsXXzcxg = false;}
      if(ELepTkqDrj == true){ELepTkqDrj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYQUJLTILL
{ 
  void KmhzRFQnDc()
  { 
      bool bNdICQpngX = false;
      bool DjDSXjdbkT = false;
      bool nFmaDVYldC = false;
      bool dhJOBJuElA = false;
      bool HaEMwYaKlh = false;
      bool JJzfgVZDEg = false;
      bool rDKdsUanQO = false;
      bool oZpjLMBade = false;
      bool tNzusUhchf = false;
      bool iqzFIEQZSb = false;
      bool xltXsiTPTT = false;
      bool UyYZleEPjY = false;
      bool lyGkexajbH = false;
      bool waIChITbBK = false;
      bool BSJNKkSYSd = false;
      bool zAptpzfIsw = false;
      bool HimLXtpVrc = false;
      bool KcOZWSorZt = false;
      bool dCRyHukNMh = false;
      bool cKhFCSfxpQ = false;
      string SUjMndPNbe;
      string DgxZcCjCQY;
      string XGUJNwwVDm;
      string DcyyoQKCfD;
      string qyxTeNVgDu;
      string WxTVbMzayr;
      string htKnaZiykM;
      string qhWMhYIAdA;
      string aORIQFIbVb;
      string QiDmVwnIrF;
      string dWwqDnaHnD;
      string DyxxQScBXV;
      string QHcIuIeiqk;
      string kAIYWDSZFb;
      string eBmSYRlFVC;
      string TljWnWtmwt;
      string JqPCSDpYaN;
      string ACwwpPTJjc;
      string WYMnRyPkkz;
      string JedKSmkkAU;
      if(SUjMndPNbe == dWwqDnaHnD){bNdICQpngX = true;}
      else if(dWwqDnaHnD == SUjMndPNbe){xltXsiTPTT = true;}
      if(DgxZcCjCQY == DyxxQScBXV){DjDSXjdbkT = true;}
      else if(DyxxQScBXV == DgxZcCjCQY){UyYZleEPjY = true;}
      if(XGUJNwwVDm == QHcIuIeiqk){nFmaDVYldC = true;}
      else if(QHcIuIeiqk == XGUJNwwVDm){lyGkexajbH = true;}
      if(DcyyoQKCfD == kAIYWDSZFb){dhJOBJuElA = true;}
      else if(kAIYWDSZFb == DcyyoQKCfD){waIChITbBK = true;}
      if(qyxTeNVgDu == eBmSYRlFVC){HaEMwYaKlh = true;}
      else if(eBmSYRlFVC == qyxTeNVgDu){BSJNKkSYSd = true;}
      if(WxTVbMzayr == TljWnWtmwt){JJzfgVZDEg = true;}
      else if(TljWnWtmwt == WxTVbMzayr){zAptpzfIsw = true;}
      if(htKnaZiykM == JqPCSDpYaN){rDKdsUanQO = true;}
      else if(JqPCSDpYaN == htKnaZiykM){HimLXtpVrc = true;}
      if(qhWMhYIAdA == ACwwpPTJjc){oZpjLMBade = true;}
      if(aORIQFIbVb == WYMnRyPkkz){tNzusUhchf = true;}
      if(QiDmVwnIrF == JedKSmkkAU){iqzFIEQZSb = true;}
      while(ACwwpPTJjc == qhWMhYIAdA){KcOZWSorZt = true;}
      while(WYMnRyPkkz == WYMnRyPkkz){dCRyHukNMh = true;}
      while(JedKSmkkAU == JedKSmkkAU){cKhFCSfxpQ = true;}
      if(bNdICQpngX == true){bNdICQpngX = false;}
      if(DjDSXjdbkT == true){DjDSXjdbkT = false;}
      if(nFmaDVYldC == true){nFmaDVYldC = false;}
      if(dhJOBJuElA == true){dhJOBJuElA = false;}
      if(HaEMwYaKlh == true){HaEMwYaKlh = false;}
      if(JJzfgVZDEg == true){JJzfgVZDEg = false;}
      if(rDKdsUanQO == true){rDKdsUanQO = false;}
      if(oZpjLMBade == true){oZpjLMBade = false;}
      if(tNzusUhchf == true){tNzusUhchf = false;}
      if(iqzFIEQZSb == true){iqzFIEQZSb = false;}
      if(xltXsiTPTT == true){xltXsiTPTT = false;}
      if(UyYZleEPjY == true){UyYZleEPjY = false;}
      if(lyGkexajbH == true){lyGkexajbH = false;}
      if(waIChITbBK == true){waIChITbBK = false;}
      if(BSJNKkSYSd == true){BSJNKkSYSd = false;}
      if(zAptpzfIsw == true){zAptpzfIsw = false;}
      if(HimLXtpVrc == true){HimLXtpVrc = false;}
      if(KcOZWSorZt == true){KcOZWSorZt = false;}
      if(dCRyHukNMh == true){dCRyHukNMh = false;}
      if(cKhFCSfxpQ == true){cKhFCSfxpQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXHDNXMSOJ
{ 
  void YWNWigTpHN()
  { 
      bool UrqyUgdIoi = false;
      bool kAClcJgBYh = false;
      bool rCKEKYDtPX = false;
      bool eCPWWQjUdR = false;
      bool dHnmFCJuTG = false;
      bool uPMrMRhmmu = false;
      bool dirRDikeOM = false;
      bool YLWGEkOWyI = false;
      bool PIZJbOoWKE = false;
      bool iwhhnuOWjW = false;
      bool RdfHgjsGna = false;
      bool DKnefUIion = false;
      bool sNUJdccnRI = false;
      bool WqmapkcSbr = false;
      bool VhiiBXHDCS = false;
      bool lehucDIVcE = false;
      bool GFneEMWNnu = false;
      bool rpGxSKelIF = false;
      bool UZlyWqJrxl = false;
      bool bGoXkQsEdo = false;
      string BXCBcyeCiY;
      string EPWZhbERSU;
      string ISmYFdEBTG;
      string nSSfIlksRd;
      string qgwCdSnoSM;
      string IeuTuijcwy;
      string sdickkxqRu;
      string qKzodbWktl;
      string pPhGxIXzjZ;
      string BHxTjMySRs;
      string VwWXVxfFoT;
      string LzhKHdubec;
      string NxGqsiNfFQ;
      string cDSBPsrKjz;
      string cRJQNBZlMG;
      string RVnoeYpfdm;
      string jAAXpIgguN;
      string kjreAwnpcr;
      string JaTzzHPdVq;
      string DMgxPbQkZF;
      if(BXCBcyeCiY == VwWXVxfFoT){UrqyUgdIoi = true;}
      else if(VwWXVxfFoT == BXCBcyeCiY){RdfHgjsGna = true;}
      if(EPWZhbERSU == LzhKHdubec){kAClcJgBYh = true;}
      else if(LzhKHdubec == EPWZhbERSU){DKnefUIion = true;}
      if(ISmYFdEBTG == NxGqsiNfFQ){rCKEKYDtPX = true;}
      else if(NxGqsiNfFQ == ISmYFdEBTG){sNUJdccnRI = true;}
      if(nSSfIlksRd == cDSBPsrKjz){eCPWWQjUdR = true;}
      else if(cDSBPsrKjz == nSSfIlksRd){WqmapkcSbr = true;}
      if(qgwCdSnoSM == cRJQNBZlMG){dHnmFCJuTG = true;}
      else if(cRJQNBZlMG == qgwCdSnoSM){VhiiBXHDCS = true;}
      if(IeuTuijcwy == RVnoeYpfdm){uPMrMRhmmu = true;}
      else if(RVnoeYpfdm == IeuTuijcwy){lehucDIVcE = true;}
      if(sdickkxqRu == jAAXpIgguN){dirRDikeOM = true;}
      else if(jAAXpIgguN == sdickkxqRu){GFneEMWNnu = true;}
      if(qKzodbWktl == kjreAwnpcr){YLWGEkOWyI = true;}
      if(pPhGxIXzjZ == JaTzzHPdVq){PIZJbOoWKE = true;}
      if(BHxTjMySRs == DMgxPbQkZF){iwhhnuOWjW = true;}
      while(kjreAwnpcr == qKzodbWktl){rpGxSKelIF = true;}
      while(JaTzzHPdVq == JaTzzHPdVq){UZlyWqJrxl = true;}
      while(DMgxPbQkZF == DMgxPbQkZF){bGoXkQsEdo = true;}
      if(UrqyUgdIoi == true){UrqyUgdIoi = false;}
      if(kAClcJgBYh == true){kAClcJgBYh = false;}
      if(rCKEKYDtPX == true){rCKEKYDtPX = false;}
      if(eCPWWQjUdR == true){eCPWWQjUdR = false;}
      if(dHnmFCJuTG == true){dHnmFCJuTG = false;}
      if(uPMrMRhmmu == true){uPMrMRhmmu = false;}
      if(dirRDikeOM == true){dirRDikeOM = false;}
      if(YLWGEkOWyI == true){YLWGEkOWyI = false;}
      if(PIZJbOoWKE == true){PIZJbOoWKE = false;}
      if(iwhhnuOWjW == true){iwhhnuOWjW = false;}
      if(RdfHgjsGna == true){RdfHgjsGna = false;}
      if(DKnefUIion == true){DKnefUIion = false;}
      if(sNUJdccnRI == true){sNUJdccnRI = false;}
      if(WqmapkcSbr == true){WqmapkcSbr = false;}
      if(VhiiBXHDCS == true){VhiiBXHDCS = false;}
      if(lehucDIVcE == true){lehucDIVcE = false;}
      if(GFneEMWNnu == true){GFneEMWNnu = false;}
      if(rpGxSKelIF == true){rpGxSKelIF = false;}
      if(UZlyWqJrxl == true){UZlyWqJrxl = false;}
      if(bGoXkQsEdo == true){bGoXkQsEdo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABVGFENRWK
{ 
  void tlEBNezHiD()
  { 
      bool rGlJbMcukW = false;
      bool VTsVmSoSEC = false;
      bool wJhVGgQIpc = false;
      bool Khuuzpgggi = false;
      bool rwHuhFsAXD = false;
      bool YHrizhXQDu = false;
      bool wUEHMnXyVw = false;
      bool lIkVKABmmA = false;
      bool mPjlECpLuQ = false;
      bool SQcllWqzht = false;
      bool gudbRPVVYy = false;
      bool fkcCIfkSDK = false;
      bool xMCEdVezjn = false;
      bool JBEsSrlHUo = false;
      bool fUlxkgmacF = false;
      bool lXwXxTrYyw = false;
      bool jWlkndgjiQ = false;
      bool tcxNdbZFTw = false;
      bool hEWdCkFfuy = false;
      bool AMJYFJiBIG = false;
      string bANEYgpHOb;
      string BYNsjdjnSl;
      string lIpIlCBmKQ;
      string lVCUrdpLQV;
      string WIcEfAjOEb;
      string phgKTTKFSW;
      string fCwxpfVrAF;
      string nXXwOdekbk;
      string RmhhaEorAY;
      string TjsspTLeOA;
      string erNymRJjup;
      string nYcgEsUOWl;
      string qcqblDedGt;
      string SzVbGZYitJ;
      string tExKjtHLnw;
      string zxIcJBAkMi;
      string lfcAXnCAZe;
      string TlTNqlegqq;
      string wSpJuUqsSE;
      string YmVKWOawlw;
      if(bANEYgpHOb == erNymRJjup){rGlJbMcukW = true;}
      else if(erNymRJjup == bANEYgpHOb){gudbRPVVYy = true;}
      if(BYNsjdjnSl == nYcgEsUOWl){VTsVmSoSEC = true;}
      else if(nYcgEsUOWl == BYNsjdjnSl){fkcCIfkSDK = true;}
      if(lIpIlCBmKQ == qcqblDedGt){wJhVGgQIpc = true;}
      else if(qcqblDedGt == lIpIlCBmKQ){xMCEdVezjn = true;}
      if(lVCUrdpLQV == SzVbGZYitJ){Khuuzpgggi = true;}
      else if(SzVbGZYitJ == lVCUrdpLQV){JBEsSrlHUo = true;}
      if(WIcEfAjOEb == tExKjtHLnw){rwHuhFsAXD = true;}
      else if(tExKjtHLnw == WIcEfAjOEb){fUlxkgmacF = true;}
      if(phgKTTKFSW == zxIcJBAkMi){YHrizhXQDu = true;}
      else if(zxIcJBAkMi == phgKTTKFSW){lXwXxTrYyw = true;}
      if(fCwxpfVrAF == lfcAXnCAZe){wUEHMnXyVw = true;}
      else if(lfcAXnCAZe == fCwxpfVrAF){jWlkndgjiQ = true;}
      if(nXXwOdekbk == TlTNqlegqq){lIkVKABmmA = true;}
      if(RmhhaEorAY == wSpJuUqsSE){mPjlECpLuQ = true;}
      if(TjsspTLeOA == YmVKWOawlw){SQcllWqzht = true;}
      while(TlTNqlegqq == nXXwOdekbk){tcxNdbZFTw = true;}
      while(wSpJuUqsSE == wSpJuUqsSE){hEWdCkFfuy = true;}
      while(YmVKWOawlw == YmVKWOawlw){AMJYFJiBIG = true;}
      if(rGlJbMcukW == true){rGlJbMcukW = false;}
      if(VTsVmSoSEC == true){VTsVmSoSEC = false;}
      if(wJhVGgQIpc == true){wJhVGgQIpc = false;}
      if(Khuuzpgggi == true){Khuuzpgggi = false;}
      if(rwHuhFsAXD == true){rwHuhFsAXD = false;}
      if(YHrizhXQDu == true){YHrizhXQDu = false;}
      if(wUEHMnXyVw == true){wUEHMnXyVw = false;}
      if(lIkVKABmmA == true){lIkVKABmmA = false;}
      if(mPjlECpLuQ == true){mPjlECpLuQ = false;}
      if(SQcllWqzht == true){SQcllWqzht = false;}
      if(gudbRPVVYy == true){gudbRPVVYy = false;}
      if(fkcCIfkSDK == true){fkcCIfkSDK = false;}
      if(xMCEdVezjn == true){xMCEdVezjn = false;}
      if(JBEsSrlHUo == true){JBEsSrlHUo = false;}
      if(fUlxkgmacF == true){fUlxkgmacF = false;}
      if(lXwXxTrYyw == true){lXwXxTrYyw = false;}
      if(jWlkndgjiQ == true){jWlkndgjiQ = false;}
      if(tcxNdbZFTw == true){tcxNdbZFTw = false;}
      if(hEWdCkFfuy == true){hEWdCkFfuy = false;}
      if(AMJYFJiBIG == true){AMJYFJiBIG = false;}
    } 
}; 
