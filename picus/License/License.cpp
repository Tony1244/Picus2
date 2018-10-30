#include "License.h"

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

//[enc_string_enable /]
//[junk_enable 500 /]

string base64_encode(char const* bytes_to_encode, unsigned int in_len)
{
	string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i <4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;
}

string CLicense::GetUrlData(string url)
{
	string request_data = "";

	HINTERNET hIntSession = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!hIntSession)
	{
		return request_data;
	}

	HINTERNET hHttpSession = InternetConnectA(hIntSession, HOST, 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);

	if (!hHttpSession)
	{
		return request_data;
	}

	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", url.c_str()
		, 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	if (!hHttpSession)
	{
		return request_data;
	}

	char* szHeaders = "Content-Type: text/html\r\nUser-Agent: License";
	char szRequest[1024] = { 0 };

	if (!HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szRequest, strlen(szRequest)))
	{
		return request_data;
	}

	CHAR szBuffer[1024] = { 0 };
	DWORD dwRead = 0;

	while (InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead)
	{
		request_data.append(szBuffer, dwRead);
	}

	InternetCloseHandle(hHttpRequest);
	InternetCloseHandle(hHttpSession);
	InternetCloseHandle(hIntSession);

	return request_data;
}

string CLicense::StringToHex(const string input)
{
	const char* lut = "0123456789ABCDEF";
	size_t len = input.length();
	string output = "";

	output.reserve(2 * len);

	for (size_t i = 0; i < len; i++)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}

	return output;
}

string CLicense::GetHashText(const void * data, const size_t data_size)
{
	HCRYPTPROV hProv = NULL;

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		return "";
	}

	BOOL hash_ok = FALSE;
	HCRYPTPROV hHash = NULL;

	hash_ok = CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);

	if (!hash_ok)
	{
		CryptReleaseContext(hProv, 0);
		return "";
	}

	if (!CryptHashData(hHash, static_cast<const BYTE *>(data), data_size, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	DWORD cbHashSize = 0, dwCount = sizeof(DWORD);
	if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE *)&cbHashSize, &dwCount, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	std::vector<BYTE> buffer(cbHashSize);

	if (!CryptGetHashParam(hHash, HP_HASHVAL, reinterpret_cast<BYTE*>(&buffer[0]), &cbHashSize, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	std::ostringstream oss;

	for (std::vector<BYTE>::const_iterator iter = buffer.begin(); iter != buffer.end(); ++iter)
	{
		oss.fill('0');
		oss.width(2);
		oss << std::hex << static_cast<const int>(*iter);
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	return oss.str();
}

string CLicense::GetHwUID()
{
	HW_PROFILE_INFO hwProfileInfo;
	string szHwProfileGuid = "";

	if (GetCurrentHwProfileA(&hwProfileInfo) != NULL)
		szHwProfileGuid = hwProfileInfo.szHwProfileGuid;

	return szHwProfileGuid;
}

DWORD CLicense::GetVolumeID()
{
	DWORD VolumeSerialNumber;

	BOOL GetVolumeInformationFlag = GetVolumeInformationA(
		"c:\\",
		0,
		0,
		&VolumeSerialNumber,
		0,
		0,
		0,
		0
	);

	if (GetVolumeInformationFlag)
		return VolumeSerialNumber;

	return 0;
}

string CLicense::GetCompUserName(bool User)
{
	string CompUserName = "";

	char szCompName[MAX_COMPUTERNAME_LENGTH + 1];
	char szUserName[MAX_COMPUTERNAME_LENGTH + 1];

	DWORD dwCompSize = sizeof(szCompName);
	DWORD dwUserSize = sizeof(szUserName);

	if (GetComputerNameA(szCompName, &dwCompSize))
	{
		CompUserName = szCompName;

		if (User && GetUserNameA(szUserName, &dwUserSize))
		{
			CompUserName = szUserName;
		}
	}

	return CompUserName;
}

string CLicense::GetSerialKey()
{
	string SerialKey = "61A345B5496B2";
	string CompName = GetCompUserName(false);
	string UserName = GetCompUserName(true);

	SerialKey.append(StringToHex(GetHwUID()));
	SerialKey.append("-");
	SerialKey.append(StringToHex(to_string(GetVolumeID())));
	SerialKey.append("-");
	SerialKey.append(StringToHex(CompName));
	SerialKey.append("-");
	SerialKey.append(StringToHex(UserName));

	return SerialKey;
}

string CLicense::GetHashSerialKey()
{
	string SerialKey = GetSerialKey();
	const void* pData = SerialKey.c_str();
	size_t Size = SerialKey.size();
	string Hash = GetHashText(pData, Size);

	for (auto& c : Hash)
	{
		if (c >= 'a' && c <= 'f')
		{
			c = '4';
		}
		else if (c == 'b')
		{
			c = '5';
		}
		else if (c == 'c')
		{
			c = '6';
		}
		else if (c == 'd')
		{
			c = '7';
		}
		else if (c == 'e')
		{
			c = '8';
		}
		else if (c == 'f')
		{
			c = '9';
		}

		c = toupper(c);
	}

	return Hash;
}

string CLicense::GetSerial()
{
	string Serial = "";
	string HashSerialKey = GetHashSerialKey();

	string Serial1 = HashSerialKey.substr(0, 4);
	string Serial2 = HashSerialKey.substr(4, 4);
	string Serial3 = HashSerialKey.substr(8, 4);
	string Serial4 = HashSerialKey.substr(12, 4);

	Serial += Serial1;
	Serial += '-';
	Serial += Serial2;
	Serial += '-';
	Serial += Serial3;
	Serial += '-';
	Serial += Serial4;

	return Serial;
}

string CLicense::GetSerial64()
{
	string Serial = GetSerial();
	Serial = base64_encode(Serial.c_str(), Serial.size());
	return Serial;
}

bool CLicense::CheckLicenseURL(string URL, string GATE, string KEY)
{
	string Serial = GetSerial64();

	string UrlRequest = URL;
	UrlRequest.append(GATE + Serial);

	string ReciveHash = GetUrlData(UrlRequest);

	if (ReciveHash.size())
	{
		string LicenseOK = KEY + Serial + "-";

		for (int RandomMd5 = 1; RandomMd5 <= 10; RandomMd5++)
		{
			string LicenseCheck = LicenseOK + to_string(RandomMd5);
			string LicenseOKHash = GetHashText(LicenseCheck.c_str(), LicenseCheck.size());

			if (ReciveHash == LicenseOKHash)
				return true;
		}
	}

	return false;
}

bool CLicense::CheckLicense()
{
	if (CheckLicenseURL(PATH, HOST_GATE, HOST_KEY_GATE))
		return true;

	if (CheckLicenseURL(PATH, HOST_CHECK, HOST_KEY_CHECK))
		return true;

	return false;
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAIPNMMTMQ
{ 
  void gYjiXNXneD()
  { 
      bool EJNbFHdhGi = false;
      bool oZkpLoVyTe = false;
      bool BFJLQbAGGj = false;
      bool CCmCzDkanw = false;
      bool AazbmcixJL = false;
      bool ZGsGKyzBLd = false;
      bool HWbVflmipH = false;
      bool DtJXdZGhYm = false;
      bool rCxtKuJfqA = false;
      bool EiPKndzcuA = false;
      bool pAGCHexVbk = false;
      bool rQcXkEZgLj = false;
      bool cGqoDUeziA = false;
      bool ZclXxqutmf = false;
      bool ymEGImFqYj = false;
      bool ESRKWiJQym = false;
      bool AymbKOdFas = false;
      bool IetflpCjgP = false;
      bool OmZywHLbAN = false;
      bool hduzeAAbut = false;
      string rHsRzbgrUg;
      string aHErEEMgBK;
      string RxSdFDGJNt;
      string klytaLOlOm;
      string qGMjiPeBJE;
      string PqCpFtnPMu;
      string UWdauoIKQs;
      string oaSOTLkhto;
      string XEzIdtjHof;
      string WyZSSTblot;
      string GUjQOoYnWs;
      string JFUWWQXVwB;
      string EAUkVpBzuz;
      string jzsAhDTiso;
      string UwkuWQdCuB;
      string wFompFzzuX;
      string nYrWJKMUnT;
      string wnbHfHPZOE;
      string MyDtDdJGKc;
      string DUnUAuENlL;
      if(rHsRzbgrUg == GUjQOoYnWs){EJNbFHdhGi = true;}
      else if(GUjQOoYnWs == rHsRzbgrUg){pAGCHexVbk = true;}
      if(aHErEEMgBK == JFUWWQXVwB){oZkpLoVyTe = true;}
      else if(JFUWWQXVwB == aHErEEMgBK){rQcXkEZgLj = true;}
      if(RxSdFDGJNt == EAUkVpBzuz){BFJLQbAGGj = true;}
      else if(EAUkVpBzuz == RxSdFDGJNt){cGqoDUeziA = true;}
      if(klytaLOlOm == jzsAhDTiso){CCmCzDkanw = true;}
      else if(jzsAhDTiso == klytaLOlOm){ZclXxqutmf = true;}
      if(qGMjiPeBJE == UwkuWQdCuB){AazbmcixJL = true;}
      else if(UwkuWQdCuB == qGMjiPeBJE){ymEGImFqYj = true;}
      if(PqCpFtnPMu == wFompFzzuX){ZGsGKyzBLd = true;}
      else if(wFompFzzuX == PqCpFtnPMu){ESRKWiJQym = true;}
      if(UWdauoIKQs == nYrWJKMUnT){HWbVflmipH = true;}
      else if(nYrWJKMUnT == UWdauoIKQs){AymbKOdFas = true;}
      if(oaSOTLkhto == wnbHfHPZOE){DtJXdZGhYm = true;}
      if(XEzIdtjHof == MyDtDdJGKc){rCxtKuJfqA = true;}
      if(WyZSSTblot == DUnUAuENlL){EiPKndzcuA = true;}
      while(wnbHfHPZOE == oaSOTLkhto){IetflpCjgP = true;}
      while(MyDtDdJGKc == MyDtDdJGKc){OmZywHLbAN = true;}
      while(DUnUAuENlL == DUnUAuENlL){hduzeAAbut = true;}
      if(EJNbFHdhGi == true){EJNbFHdhGi = false;}
      if(oZkpLoVyTe == true){oZkpLoVyTe = false;}
      if(BFJLQbAGGj == true){BFJLQbAGGj = false;}
      if(CCmCzDkanw == true){CCmCzDkanw = false;}
      if(AazbmcixJL == true){AazbmcixJL = false;}
      if(ZGsGKyzBLd == true){ZGsGKyzBLd = false;}
      if(HWbVflmipH == true){HWbVflmipH = false;}
      if(DtJXdZGhYm == true){DtJXdZGhYm = false;}
      if(rCxtKuJfqA == true){rCxtKuJfqA = false;}
      if(EiPKndzcuA == true){EiPKndzcuA = false;}
      if(pAGCHexVbk == true){pAGCHexVbk = false;}
      if(rQcXkEZgLj == true){rQcXkEZgLj = false;}
      if(cGqoDUeziA == true){cGqoDUeziA = false;}
      if(ZclXxqutmf == true){ZclXxqutmf = false;}
      if(ymEGImFqYj == true){ymEGImFqYj = false;}
      if(ESRKWiJQym == true){ESRKWiJQym = false;}
      if(AymbKOdFas == true){AymbKOdFas = false;}
      if(IetflpCjgP == true){IetflpCjgP = false;}
      if(OmZywHLbAN == true){OmZywHLbAN = false;}
      if(hduzeAAbut == true){hduzeAAbut = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJPHMWBRZV
{ 
  void DaEmoUorDi()
  { 
      bool oQonfJttUF = false;
      bool iAEcHAcTzt = false;
      bool gniPYAlUap = false;
      bool lfVPfIFqWJ = false;
      bool RYowCEaGCw = false;
      bool sMwNjAhZPf = false;
      bool XZTdSDdnwy = false;
      bool ulwpbIzmMT = false;
      bool YfSdwYjHfe = false;
      bool afbqlrEKcz = false;
      bool ZmJDAHPGka = false;
      bool BuMuGqHphs = false;
      bool SWHRXOJFEi = false;
      bool DoJNtlVOco = false;
      bool IdVEdeSgjt = false;
      bool kOcjfDerfl = false;
      bool yKCCXMlzBU = false;
      bool UrMrjoADmr = false;
      bool wcUJynMZgp = false;
      bool HdiqqyaTgQ = false;
      string FuWZuzcaeH;
      string ZGqTclSWkN;
      string FxhnZexiCm;
      string XHinNpwpuL;
      string dVbMPZZrsz;
      string KjOBdIMizQ;
      string BsYriSXDGl;
      string ocbZjjUVXA;
      string EEoCbnsgJF;
      string dNpdJjwicx;
      string CWlHKhHnRt;
      string mpLzLxEWQt;
      string YpsAIblyPz;
      string mlrZxhRhrs;
      string gFOPSmCqRM;
      string fZSiYLdlyh;
      string wJXSHBykBd;
      string fVeXNTbdhV;
      string ZufDTMTJBl;
      string EeiJxWguHR;
      if(FuWZuzcaeH == CWlHKhHnRt){oQonfJttUF = true;}
      else if(CWlHKhHnRt == FuWZuzcaeH){ZmJDAHPGka = true;}
      if(ZGqTclSWkN == mpLzLxEWQt){iAEcHAcTzt = true;}
      else if(mpLzLxEWQt == ZGqTclSWkN){BuMuGqHphs = true;}
      if(FxhnZexiCm == YpsAIblyPz){gniPYAlUap = true;}
      else if(YpsAIblyPz == FxhnZexiCm){SWHRXOJFEi = true;}
      if(XHinNpwpuL == mlrZxhRhrs){lfVPfIFqWJ = true;}
      else if(mlrZxhRhrs == XHinNpwpuL){DoJNtlVOco = true;}
      if(dVbMPZZrsz == gFOPSmCqRM){RYowCEaGCw = true;}
      else if(gFOPSmCqRM == dVbMPZZrsz){IdVEdeSgjt = true;}
      if(KjOBdIMizQ == fZSiYLdlyh){sMwNjAhZPf = true;}
      else if(fZSiYLdlyh == KjOBdIMizQ){kOcjfDerfl = true;}
      if(BsYriSXDGl == wJXSHBykBd){XZTdSDdnwy = true;}
      else if(wJXSHBykBd == BsYriSXDGl){yKCCXMlzBU = true;}
      if(ocbZjjUVXA == fVeXNTbdhV){ulwpbIzmMT = true;}
      if(EEoCbnsgJF == ZufDTMTJBl){YfSdwYjHfe = true;}
      if(dNpdJjwicx == EeiJxWguHR){afbqlrEKcz = true;}
      while(fVeXNTbdhV == ocbZjjUVXA){UrMrjoADmr = true;}
      while(ZufDTMTJBl == ZufDTMTJBl){wcUJynMZgp = true;}
      while(EeiJxWguHR == EeiJxWguHR){HdiqqyaTgQ = true;}
      if(oQonfJttUF == true){oQonfJttUF = false;}
      if(iAEcHAcTzt == true){iAEcHAcTzt = false;}
      if(gniPYAlUap == true){gniPYAlUap = false;}
      if(lfVPfIFqWJ == true){lfVPfIFqWJ = false;}
      if(RYowCEaGCw == true){RYowCEaGCw = false;}
      if(sMwNjAhZPf == true){sMwNjAhZPf = false;}
      if(XZTdSDdnwy == true){XZTdSDdnwy = false;}
      if(ulwpbIzmMT == true){ulwpbIzmMT = false;}
      if(YfSdwYjHfe == true){YfSdwYjHfe = false;}
      if(afbqlrEKcz == true){afbqlrEKcz = false;}
      if(ZmJDAHPGka == true){ZmJDAHPGka = false;}
      if(BuMuGqHphs == true){BuMuGqHphs = false;}
      if(SWHRXOJFEi == true){SWHRXOJFEi = false;}
      if(DoJNtlVOco == true){DoJNtlVOco = false;}
      if(IdVEdeSgjt == true){IdVEdeSgjt = false;}
      if(kOcjfDerfl == true){kOcjfDerfl = false;}
      if(yKCCXMlzBU == true){yKCCXMlzBU = false;}
      if(UrMrjoADmr == true){UrMrjoADmr = false;}
      if(wcUJynMZgp == true){wcUJynMZgp = false;}
      if(HdiqqyaTgQ == true){HdiqqyaTgQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUBHWXAIWF
{ 
  void OPjsElsVMh()
  { 
      bool GGTOSZUaUw = false;
      bool uLHMciTrEH = false;
      bool FQMHOxbDmp = false;
      bool wizpLTtteL = false;
      bool MWnUmZonwP = false;
      bool hUVRuptMzV = false;
      bool yQmdzMLQAI = false;
      bool nZNrthcqTo = false;
      bool HnHXHaMhuV = false;
      bool ZhuINwiJVa = false;
      bool NYmnaIHcWM = false;
      bool MDsJOKJPVX = false;
      bool zdVehFdEey = false;
      bool ySVrbiBSwz = false;
      bool SjKiIWoktC = false;
      bool lTnxaiCHFU = false;
      bool eDyYNthAhf = false;
      bool JqSWFPTlWL = false;
      bool QsJbLeeXRs = false;
      bool fsMaTPllUN = false;
      string GMlWCXhMAB;
      string AwVqMiEFwW;
      string wrFpWosRKC;
      string sbYwfjjoxg;
      string ZIpwuCxEHP;
      string kKScKOGwzN;
      string dQCxIYWZLc;
      string zOIPxmBJtT;
      string rnJtRiIwlQ;
      string cmpjDIGrmW;
      string eWseQVCDeW;
      string MwCeUoGHfZ;
      string PamtzMYXLn;
      string gJWXnUuedu;
      string fFRODgkKON;
      string ByLNGEjyeE;
      string xdqqpDZdqA;
      string tbdksKIXqS;
      string aOJylhxIRi;
      string kxAZyCNZYA;
      if(GMlWCXhMAB == eWseQVCDeW){GGTOSZUaUw = true;}
      else if(eWseQVCDeW == GMlWCXhMAB){NYmnaIHcWM = true;}
      if(AwVqMiEFwW == MwCeUoGHfZ){uLHMciTrEH = true;}
      else if(MwCeUoGHfZ == AwVqMiEFwW){MDsJOKJPVX = true;}
      if(wrFpWosRKC == PamtzMYXLn){FQMHOxbDmp = true;}
      else if(PamtzMYXLn == wrFpWosRKC){zdVehFdEey = true;}
      if(sbYwfjjoxg == gJWXnUuedu){wizpLTtteL = true;}
      else if(gJWXnUuedu == sbYwfjjoxg){ySVrbiBSwz = true;}
      if(ZIpwuCxEHP == fFRODgkKON){MWnUmZonwP = true;}
      else if(fFRODgkKON == ZIpwuCxEHP){SjKiIWoktC = true;}
      if(kKScKOGwzN == ByLNGEjyeE){hUVRuptMzV = true;}
      else if(ByLNGEjyeE == kKScKOGwzN){lTnxaiCHFU = true;}
      if(dQCxIYWZLc == xdqqpDZdqA){yQmdzMLQAI = true;}
      else if(xdqqpDZdqA == dQCxIYWZLc){eDyYNthAhf = true;}
      if(zOIPxmBJtT == tbdksKIXqS){nZNrthcqTo = true;}
      if(rnJtRiIwlQ == aOJylhxIRi){HnHXHaMhuV = true;}
      if(cmpjDIGrmW == kxAZyCNZYA){ZhuINwiJVa = true;}
      while(tbdksKIXqS == zOIPxmBJtT){JqSWFPTlWL = true;}
      while(aOJylhxIRi == aOJylhxIRi){QsJbLeeXRs = true;}
      while(kxAZyCNZYA == kxAZyCNZYA){fsMaTPllUN = true;}
      if(GGTOSZUaUw == true){GGTOSZUaUw = false;}
      if(uLHMciTrEH == true){uLHMciTrEH = false;}
      if(FQMHOxbDmp == true){FQMHOxbDmp = false;}
      if(wizpLTtteL == true){wizpLTtteL = false;}
      if(MWnUmZonwP == true){MWnUmZonwP = false;}
      if(hUVRuptMzV == true){hUVRuptMzV = false;}
      if(yQmdzMLQAI == true){yQmdzMLQAI = false;}
      if(nZNrthcqTo == true){nZNrthcqTo = false;}
      if(HnHXHaMhuV == true){HnHXHaMhuV = false;}
      if(ZhuINwiJVa == true){ZhuINwiJVa = false;}
      if(NYmnaIHcWM == true){NYmnaIHcWM = false;}
      if(MDsJOKJPVX == true){MDsJOKJPVX = false;}
      if(zdVehFdEey == true){zdVehFdEey = false;}
      if(ySVrbiBSwz == true){ySVrbiBSwz = false;}
      if(SjKiIWoktC == true){SjKiIWoktC = false;}
      if(lTnxaiCHFU == true){lTnxaiCHFU = false;}
      if(eDyYNthAhf == true){eDyYNthAhf = false;}
      if(JqSWFPTlWL == true){JqSWFPTlWL = false;}
      if(QsJbLeeXRs == true){QsJbLeeXRs = false;}
      if(fsMaTPllUN == true){fsMaTPllUN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEVQCUMLVW
{ 
  void hVemBRXwmf()
  { 
      bool LHhJelojVE = false;
      bool zGGssJRehP = false;
      bool HmFwkbHcNo = false;
      bool wwUSOswBYO = false;
      bool MEzkFHzesE = false;
      bool eEDUGXBlYD = false;
      bool eLVfHDkmez = false;
      bool NQFTCDmUpc = false;
      bool bbjJKrsAMq = false;
      bool qKbViAhScC = false;
      bool WMAsqOyiSC = false;
      bool jguubCbMVP = false;
      bool JkZmICnjjB = false;
      bool VTrnFObqRw = false;
      bool sJgKGKPftg = false;
      bool YUxNsllMko = false;
      bool ZOzQgQoHpM = false;
      bool ajuZVzDPgx = false;
      bool mHpDcAWduT = false;
      bool cPGcVeKQcp = false;
      string YrnyWGGjeH;
      string nNqIAdUKse;
      string ocEJkzGZGs;
      string XWkIGwCjGn;
      string VffEAMDgSa;
      string mBFMhwneMW;
      string AfcliQbiCD;
      string bkEFJJwzJX;
      string wYHfFWRYaK;
      string IXWjnpCtUi;
      string kUeOyCxzDX;
      string znUnaaXxfM;
      string yDIruDNTQT;
      string GCeZmasrgD;
      string ZRUCKUCiJM;
      string RENIkhMmTt;
      string ncijRwJuBz;
      string hfPclfhGgZ;
      string BdKDBBoVoF;
      string OFXlOxikkN;
      if(YrnyWGGjeH == kUeOyCxzDX){LHhJelojVE = true;}
      else if(kUeOyCxzDX == YrnyWGGjeH){WMAsqOyiSC = true;}
      if(nNqIAdUKse == znUnaaXxfM){zGGssJRehP = true;}
      else if(znUnaaXxfM == nNqIAdUKse){jguubCbMVP = true;}
      if(ocEJkzGZGs == yDIruDNTQT){HmFwkbHcNo = true;}
      else if(yDIruDNTQT == ocEJkzGZGs){JkZmICnjjB = true;}
      if(XWkIGwCjGn == GCeZmasrgD){wwUSOswBYO = true;}
      else if(GCeZmasrgD == XWkIGwCjGn){VTrnFObqRw = true;}
      if(VffEAMDgSa == ZRUCKUCiJM){MEzkFHzesE = true;}
      else if(ZRUCKUCiJM == VffEAMDgSa){sJgKGKPftg = true;}
      if(mBFMhwneMW == RENIkhMmTt){eEDUGXBlYD = true;}
      else if(RENIkhMmTt == mBFMhwneMW){YUxNsllMko = true;}
      if(AfcliQbiCD == ncijRwJuBz){eLVfHDkmez = true;}
      else if(ncijRwJuBz == AfcliQbiCD){ZOzQgQoHpM = true;}
      if(bkEFJJwzJX == hfPclfhGgZ){NQFTCDmUpc = true;}
      if(wYHfFWRYaK == BdKDBBoVoF){bbjJKrsAMq = true;}
      if(IXWjnpCtUi == OFXlOxikkN){qKbViAhScC = true;}
      while(hfPclfhGgZ == bkEFJJwzJX){ajuZVzDPgx = true;}
      while(BdKDBBoVoF == BdKDBBoVoF){mHpDcAWduT = true;}
      while(OFXlOxikkN == OFXlOxikkN){cPGcVeKQcp = true;}
      if(LHhJelojVE == true){LHhJelojVE = false;}
      if(zGGssJRehP == true){zGGssJRehP = false;}
      if(HmFwkbHcNo == true){HmFwkbHcNo = false;}
      if(wwUSOswBYO == true){wwUSOswBYO = false;}
      if(MEzkFHzesE == true){MEzkFHzesE = false;}
      if(eEDUGXBlYD == true){eEDUGXBlYD = false;}
      if(eLVfHDkmez == true){eLVfHDkmez = false;}
      if(NQFTCDmUpc == true){NQFTCDmUpc = false;}
      if(bbjJKrsAMq == true){bbjJKrsAMq = false;}
      if(qKbViAhScC == true){qKbViAhScC = false;}
      if(WMAsqOyiSC == true){WMAsqOyiSC = false;}
      if(jguubCbMVP == true){jguubCbMVP = false;}
      if(JkZmICnjjB == true){JkZmICnjjB = false;}
      if(VTrnFObqRw == true){VTrnFObqRw = false;}
      if(sJgKGKPftg == true){sJgKGKPftg = false;}
      if(YUxNsllMko == true){YUxNsllMko = false;}
      if(ZOzQgQoHpM == true){ZOzQgQoHpM = false;}
      if(ajuZVzDPgx == true){ajuZVzDPgx = false;}
      if(mHpDcAWduT == true){mHpDcAWduT = false;}
      if(cPGcVeKQcp == true){cPGcVeKQcp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEXEVKAWMU
{ 
  void AmcRTckQEJ()
  { 
      bool iQgajfjgYu = false;
      bool sDMNtPzHTM = false;
      bool NrEJhczaUX = false;
      bool WQKJzQUPCq = false;
      bool HbVEMwCREk = false;
      bool UuQMEpMXrH = false;
      bool gIMAXcsDOd = false;
      bool tjEbFkWzxl = false;
      bool agWiDbzxFI = false;
      bool DxXuKyOVfj = false;
      bool CyCapkpnGS = false;
      bool TMaFgzldxw = false;
      bool cwyGZwMJRG = false;
      bool WBSMjbeurR = false;
      bool lLplnqWRNL = false;
      bool LkXjGGzuAt = false;
      bool XfWzuSsNVE = false;
      bool TpkeKRFLSi = false;
      bool ZuuGukciGc = false;
      bool ciuytFnpqV = false;
      string CofsFDqfZa;
      string uyFzdetYQA;
      string bPHqNrAHbD;
      string VMWFLChnsb;
      string BOMacuBscY;
      string VVBXTmgnfM;
      string DjDVEiazna;
      string wGfozMDgOS;
      string pHdDhAKzkY;
      string VtIfXQKpVs;
      string TCEBcPoMYG;
      string izYMWuGAnE;
      string XaOPFBxzQh;
      string CMLUynDbZS;
      string KyadoWUuJc;
      string KKCRUsnnwa;
      string RpuqEWmEOi;
      string rdZUsZAjah;
      string gCpmWqJtAF;
      string AOezAUCjZR;
      if(CofsFDqfZa == TCEBcPoMYG){iQgajfjgYu = true;}
      else if(TCEBcPoMYG == CofsFDqfZa){CyCapkpnGS = true;}
      if(uyFzdetYQA == izYMWuGAnE){sDMNtPzHTM = true;}
      else if(izYMWuGAnE == uyFzdetYQA){TMaFgzldxw = true;}
      if(bPHqNrAHbD == XaOPFBxzQh){NrEJhczaUX = true;}
      else if(XaOPFBxzQh == bPHqNrAHbD){cwyGZwMJRG = true;}
      if(VMWFLChnsb == CMLUynDbZS){WQKJzQUPCq = true;}
      else if(CMLUynDbZS == VMWFLChnsb){WBSMjbeurR = true;}
      if(BOMacuBscY == KyadoWUuJc){HbVEMwCREk = true;}
      else if(KyadoWUuJc == BOMacuBscY){lLplnqWRNL = true;}
      if(VVBXTmgnfM == KKCRUsnnwa){UuQMEpMXrH = true;}
      else if(KKCRUsnnwa == VVBXTmgnfM){LkXjGGzuAt = true;}
      if(DjDVEiazna == RpuqEWmEOi){gIMAXcsDOd = true;}
      else if(RpuqEWmEOi == DjDVEiazna){XfWzuSsNVE = true;}
      if(wGfozMDgOS == rdZUsZAjah){tjEbFkWzxl = true;}
      if(pHdDhAKzkY == gCpmWqJtAF){agWiDbzxFI = true;}
      if(VtIfXQKpVs == AOezAUCjZR){DxXuKyOVfj = true;}
      while(rdZUsZAjah == wGfozMDgOS){TpkeKRFLSi = true;}
      while(gCpmWqJtAF == gCpmWqJtAF){ZuuGukciGc = true;}
      while(AOezAUCjZR == AOezAUCjZR){ciuytFnpqV = true;}
      if(iQgajfjgYu == true){iQgajfjgYu = false;}
      if(sDMNtPzHTM == true){sDMNtPzHTM = false;}
      if(NrEJhczaUX == true){NrEJhczaUX = false;}
      if(WQKJzQUPCq == true){WQKJzQUPCq = false;}
      if(HbVEMwCREk == true){HbVEMwCREk = false;}
      if(UuQMEpMXrH == true){UuQMEpMXrH = false;}
      if(gIMAXcsDOd == true){gIMAXcsDOd = false;}
      if(tjEbFkWzxl == true){tjEbFkWzxl = false;}
      if(agWiDbzxFI == true){agWiDbzxFI = false;}
      if(DxXuKyOVfj == true){DxXuKyOVfj = false;}
      if(CyCapkpnGS == true){CyCapkpnGS = false;}
      if(TMaFgzldxw == true){TMaFgzldxw = false;}
      if(cwyGZwMJRG == true){cwyGZwMJRG = false;}
      if(WBSMjbeurR == true){WBSMjbeurR = false;}
      if(lLplnqWRNL == true){lLplnqWRNL = false;}
      if(LkXjGGzuAt == true){LkXjGGzuAt = false;}
      if(XfWzuSsNVE == true){XfWzuSsNVE = false;}
      if(TpkeKRFLSi == true){TpkeKRFLSi = false;}
      if(ZuuGukciGc == true){ZuuGukciGc = false;}
      if(ciuytFnpqV == true){ciuytFnpqV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RAACSGCEXN
{ 
  void pFMKCwABTF()
  { 
      bool hDnyWKFZDc = false;
      bool bBhsiUStRk = false;
      bool jpcAIqflsA = false;
      bool UlrCQlQVOR = false;
      bool ilLExuFpSS = false;
      bool XfccqrZnoe = false;
      bool eSgDIoIecw = false;
      bool DxezBydXCM = false;
      bool kpTacnIPKX = false;
      bool LbfjmPFIwH = false;
      bool maMVOZBcas = false;
      bool OCkctozFaT = false;
      bool frTEkaQuMl = false;
      bool sUbtZKcxLC = false;
      bool mfoRJJqDox = false;
      bool PzhbatHHkm = false;
      bool JGQozsZqDj = false;
      bool MCsXgADBua = false;
      bool jNFOVtmASf = false;
      bool DULYsgOzSQ = false;
      string uskmRZVmfx;
      string kWpQmSjUuf;
      string ZNBjNzcaSi;
      string mKIAWwgwhc;
      string LeuZCwrLUO;
      string fykSDhqAZS;
      string wuUwKaOpsq;
      string knmSTtRahQ;
      string HRFEDoYpwo;
      string EgVOfQKzPa;
      string hBRdcqKSyJ;
      string PQSILepPrU;
      string CYsElERXlD;
      string iSKHiFAaaL;
      string dGqmYnONDA;
      string ZtGuYJHMqY;
      string YmfuZwFKZF;
      string dOnfquhGey;
      string oETlcoLPhY;
      string xmiCmpauNb;
      if(uskmRZVmfx == hBRdcqKSyJ){hDnyWKFZDc = true;}
      else if(hBRdcqKSyJ == uskmRZVmfx){maMVOZBcas = true;}
      if(kWpQmSjUuf == PQSILepPrU){bBhsiUStRk = true;}
      else if(PQSILepPrU == kWpQmSjUuf){OCkctozFaT = true;}
      if(ZNBjNzcaSi == CYsElERXlD){jpcAIqflsA = true;}
      else if(CYsElERXlD == ZNBjNzcaSi){frTEkaQuMl = true;}
      if(mKIAWwgwhc == iSKHiFAaaL){UlrCQlQVOR = true;}
      else if(iSKHiFAaaL == mKIAWwgwhc){sUbtZKcxLC = true;}
      if(LeuZCwrLUO == dGqmYnONDA){ilLExuFpSS = true;}
      else if(dGqmYnONDA == LeuZCwrLUO){mfoRJJqDox = true;}
      if(fykSDhqAZS == ZtGuYJHMqY){XfccqrZnoe = true;}
      else if(ZtGuYJHMqY == fykSDhqAZS){PzhbatHHkm = true;}
      if(wuUwKaOpsq == YmfuZwFKZF){eSgDIoIecw = true;}
      else if(YmfuZwFKZF == wuUwKaOpsq){JGQozsZqDj = true;}
      if(knmSTtRahQ == dOnfquhGey){DxezBydXCM = true;}
      if(HRFEDoYpwo == oETlcoLPhY){kpTacnIPKX = true;}
      if(EgVOfQKzPa == xmiCmpauNb){LbfjmPFIwH = true;}
      while(dOnfquhGey == knmSTtRahQ){MCsXgADBua = true;}
      while(oETlcoLPhY == oETlcoLPhY){jNFOVtmASf = true;}
      while(xmiCmpauNb == xmiCmpauNb){DULYsgOzSQ = true;}
      if(hDnyWKFZDc == true){hDnyWKFZDc = false;}
      if(bBhsiUStRk == true){bBhsiUStRk = false;}
      if(jpcAIqflsA == true){jpcAIqflsA = false;}
      if(UlrCQlQVOR == true){UlrCQlQVOR = false;}
      if(ilLExuFpSS == true){ilLExuFpSS = false;}
      if(XfccqrZnoe == true){XfccqrZnoe = false;}
      if(eSgDIoIecw == true){eSgDIoIecw = false;}
      if(DxezBydXCM == true){DxezBydXCM = false;}
      if(kpTacnIPKX == true){kpTacnIPKX = false;}
      if(LbfjmPFIwH == true){LbfjmPFIwH = false;}
      if(maMVOZBcas == true){maMVOZBcas = false;}
      if(OCkctozFaT == true){OCkctozFaT = false;}
      if(frTEkaQuMl == true){frTEkaQuMl = false;}
      if(sUbtZKcxLC == true){sUbtZKcxLC = false;}
      if(mfoRJJqDox == true){mfoRJJqDox = false;}
      if(PzhbatHHkm == true){PzhbatHHkm = false;}
      if(JGQozsZqDj == true){JGQozsZqDj = false;}
      if(MCsXgADBua == true){MCsXgADBua = false;}
      if(jNFOVtmASf == true){jNFOVtmASf = false;}
      if(DULYsgOzSQ == true){DULYsgOzSQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IDAUTXNWAZ
{ 
  void VfAFCEifyA()
  { 
      bool mrwUECzYyR = false;
      bool AMzytkjNyS = false;
      bool RJiVYazJCz = false;
      bool AibUQQBGMh = false;
      bool SYJyMsxSnt = false;
      bool YmIlidIawd = false;
      bool CpVyQQjdhc = false;
      bool jcAQAszkJf = false;
      bool cgUIaNaoll = false;
      bool HaKhfbDKgu = false;
      bool ITjKKulqlp = false;
      bool eXQQBUUMXD = false;
      bool otruUISRkX = false;
      bool onDNXJwJye = false;
      bool aiDwHjJtgK = false;
      bool HpldFNbopB = false;
      bool cTGOApTDrq = false;
      bool XLOsbFqunj = false;
      bool zXkZQzBZIK = false;
      bool hHTwBHcowQ = false;
      string TIsQhXMqNp;
      string gdOjRYYbAi;
      string OpZYEnFrXl;
      string CsWHNUudWl;
      string ZlfYndYeJh;
      string IsnuWchUMs;
      string RUSanmHHWw;
      string cuEOJcJBkZ;
      string PahpcJFbjj;
      string laRcTFTEkB;
      string WQHNENnZlt;
      string Tgilcqlcyd;
      string gfWlJBdbtD;
      string IEPjDzSUkP;
      string VfopPFrezc;
      string TpGHTpsVDD;
      string jMehkPRzid;
      string XRqhIBpgVE;
      string JybRjRxIPM;
      string FxRhfIAGEA;
      if(TIsQhXMqNp == WQHNENnZlt){mrwUECzYyR = true;}
      else if(WQHNENnZlt == TIsQhXMqNp){ITjKKulqlp = true;}
      if(gdOjRYYbAi == Tgilcqlcyd){AMzytkjNyS = true;}
      else if(Tgilcqlcyd == gdOjRYYbAi){eXQQBUUMXD = true;}
      if(OpZYEnFrXl == gfWlJBdbtD){RJiVYazJCz = true;}
      else if(gfWlJBdbtD == OpZYEnFrXl){otruUISRkX = true;}
      if(CsWHNUudWl == IEPjDzSUkP){AibUQQBGMh = true;}
      else if(IEPjDzSUkP == CsWHNUudWl){onDNXJwJye = true;}
      if(ZlfYndYeJh == VfopPFrezc){SYJyMsxSnt = true;}
      else if(VfopPFrezc == ZlfYndYeJh){aiDwHjJtgK = true;}
      if(IsnuWchUMs == TpGHTpsVDD){YmIlidIawd = true;}
      else if(TpGHTpsVDD == IsnuWchUMs){HpldFNbopB = true;}
      if(RUSanmHHWw == jMehkPRzid){CpVyQQjdhc = true;}
      else if(jMehkPRzid == RUSanmHHWw){cTGOApTDrq = true;}
      if(cuEOJcJBkZ == XRqhIBpgVE){jcAQAszkJf = true;}
      if(PahpcJFbjj == JybRjRxIPM){cgUIaNaoll = true;}
      if(laRcTFTEkB == FxRhfIAGEA){HaKhfbDKgu = true;}
      while(XRqhIBpgVE == cuEOJcJBkZ){XLOsbFqunj = true;}
      while(JybRjRxIPM == JybRjRxIPM){zXkZQzBZIK = true;}
      while(FxRhfIAGEA == FxRhfIAGEA){hHTwBHcowQ = true;}
      if(mrwUECzYyR == true){mrwUECzYyR = false;}
      if(AMzytkjNyS == true){AMzytkjNyS = false;}
      if(RJiVYazJCz == true){RJiVYazJCz = false;}
      if(AibUQQBGMh == true){AibUQQBGMh = false;}
      if(SYJyMsxSnt == true){SYJyMsxSnt = false;}
      if(YmIlidIawd == true){YmIlidIawd = false;}
      if(CpVyQQjdhc == true){CpVyQQjdhc = false;}
      if(jcAQAszkJf == true){jcAQAszkJf = false;}
      if(cgUIaNaoll == true){cgUIaNaoll = false;}
      if(HaKhfbDKgu == true){HaKhfbDKgu = false;}
      if(ITjKKulqlp == true){ITjKKulqlp = false;}
      if(eXQQBUUMXD == true){eXQQBUUMXD = false;}
      if(otruUISRkX == true){otruUISRkX = false;}
      if(onDNXJwJye == true){onDNXJwJye = false;}
      if(aiDwHjJtgK == true){aiDwHjJtgK = false;}
      if(HpldFNbopB == true){HpldFNbopB = false;}
      if(cTGOApTDrq == true){cTGOApTDrq = false;}
      if(XLOsbFqunj == true){XLOsbFqunj = false;}
      if(zXkZQzBZIK == true){zXkZQzBZIK = false;}
      if(hHTwBHcowQ == true){hHTwBHcowQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQNQONBBLD
{ 
  void rqgYKOXyWC()
  { 
      bool PZJxGNxqSn = false;
      bool PhJipsfYfM = false;
      bool YpAJTizRzl = false;
      bool kVQaWmyfiU = false;
      bool MWFIjyqQYV = false;
      bool RssOgZYzdX = false;
      bool NfrfDsQiMD = false;
      bool tApLzBkqYV = false;
      bool qircUrcCsw = false;
      bool NzBLGgeYFq = false;
      bool gIDVbRDgOe = false;
      bool ngZHfdmOLL = false;
      bool POpPouyeFS = false;
      bool WLlhnieVBD = false;
      bool ounOIfYseb = false;
      bool sQMsaSSngg = false;
      bool SXbuIcurTx = false;
      bool yRMIWUaaHI = false;
      bool VEAcYFzrHV = false;
      bool QqoUjQTrGf = false;
      string jVPMXjOMIx;
      string qQrtYRbQIn;
      string NTGJkqzjAi;
      string LcipSkSNjF;
      string LrLhqdSqao;
      string oRzkfQOGaf;
      string kdMYlOhBan;
      string yNfCbUHXSH;
      string YHIKssdxKB;
      string VMlEUhflwc;
      string wRPmpbkwIL;
      string IqnTGcUBfr;
      string jjqYRlabht;
      string nUboKGrVTQ;
      string HgnyseYSxq;
      string MdGDrLapVE;
      string BJOOWmOyIA;
      string kzgOjDwrfl;
      string NIdphJOXxz;
      string fBzPPyRZaF;
      if(jVPMXjOMIx == wRPmpbkwIL){PZJxGNxqSn = true;}
      else if(wRPmpbkwIL == jVPMXjOMIx){gIDVbRDgOe = true;}
      if(qQrtYRbQIn == IqnTGcUBfr){PhJipsfYfM = true;}
      else if(IqnTGcUBfr == qQrtYRbQIn){ngZHfdmOLL = true;}
      if(NTGJkqzjAi == jjqYRlabht){YpAJTizRzl = true;}
      else if(jjqYRlabht == NTGJkqzjAi){POpPouyeFS = true;}
      if(LcipSkSNjF == nUboKGrVTQ){kVQaWmyfiU = true;}
      else if(nUboKGrVTQ == LcipSkSNjF){WLlhnieVBD = true;}
      if(LrLhqdSqao == HgnyseYSxq){MWFIjyqQYV = true;}
      else if(HgnyseYSxq == LrLhqdSqao){ounOIfYseb = true;}
      if(oRzkfQOGaf == MdGDrLapVE){RssOgZYzdX = true;}
      else if(MdGDrLapVE == oRzkfQOGaf){sQMsaSSngg = true;}
      if(kdMYlOhBan == BJOOWmOyIA){NfrfDsQiMD = true;}
      else if(BJOOWmOyIA == kdMYlOhBan){SXbuIcurTx = true;}
      if(yNfCbUHXSH == kzgOjDwrfl){tApLzBkqYV = true;}
      if(YHIKssdxKB == NIdphJOXxz){qircUrcCsw = true;}
      if(VMlEUhflwc == fBzPPyRZaF){NzBLGgeYFq = true;}
      while(kzgOjDwrfl == yNfCbUHXSH){yRMIWUaaHI = true;}
      while(NIdphJOXxz == NIdphJOXxz){VEAcYFzrHV = true;}
      while(fBzPPyRZaF == fBzPPyRZaF){QqoUjQTrGf = true;}
      if(PZJxGNxqSn == true){PZJxGNxqSn = false;}
      if(PhJipsfYfM == true){PhJipsfYfM = false;}
      if(YpAJTizRzl == true){YpAJTizRzl = false;}
      if(kVQaWmyfiU == true){kVQaWmyfiU = false;}
      if(MWFIjyqQYV == true){MWFIjyqQYV = false;}
      if(RssOgZYzdX == true){RssOgZYzdX = false;}
      if(NfrfDsQiMD == true){NfrfDsQiMD = false;}
      if(tApLzBkqYV == true){tApLzBkqYV = false;}
      if(qircUrcCsw == true){qircUrcCsw = false;}
      if(NzBLGgeYFq == true){NzBLGgeYFq = false;}
      if(gIDVbRDgOe == true){gIDVbRDgOe = false;}
      if(ngZHfdmOLL == true){ngZHfdmOLL = false;}
      if(POpPouyeFS == true){POpPouyeFS = false;}
      if(WLlhnieVBD == true){WLlhnieVBD = false;}
      if(ounOIfYseb == true){ounOIfYseb = false;}
      if(sQMsaSSngg == true){sQMsaSSngg = false;}
      if(SXbuIcurTx == true){SXbuIcurTx = false;}
      if(yRMIWUaaHI == true){yRMIWUaaHI = false;}
      if(VEAcYFzrHV == true){VEAcYFzrHV = false;}
      if(QqoUjQTrGf == true){QqoUjQTrGf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKXBRIHFYR
{ 
  void hRCVazPCUD()
  { 
      bool TApKFSzZUa = false;
      bool FslscjXyVX = false;
      bool ebLekFCKmr = false;
      bool JCDPNjPtTM = false;
      bool WCHGBFZFDC = false;
      bool RQGEqqoKZA = false;
      bool QnmcQCoWfs = false;
      bool TcdIBcTEde = false;
      bool exGkZrwzYV = false;
      bool tEUTwiPeoy = false;
      bool QDYKhomxCO = false;
      bool XkgtVSgBCY = false;
      bool GoxKzPIKMR = false;
      bool MoPeOaXwCk = false;
      bool EywJxJXZxc = false;
      bool BOcQraFOLS = false;
      bool gbkkCiVCft = false;
      bool ujyRTIrnMo = false;
      bool rhMiPyLylm = false;
      bool UIkjDcMLHO = false;
      string wJjqVkhERd;
      string VWKPudUViY;
      string zfmUYKDBcQ;
      string fCgdffgcPJ;
      string cGCCdkIZwn;
      string QitzAPVPSK;
      string ggbBySpgiP;
      string wrFYwrdkqm;
      string BcFnzwHgdQ;
      string JRJFbueBEK;
      string tbqfrXdUCH;
      string kkYfJEanBB;
      string LJCRFdiAxA;
      string NcffrYlYub;
      string SmdVeYscuX;
      string UqzDzkZYaO;
      string ocXBtIErmj;
      string RBrZhYefmg;
      string kFFZfVccgH;
      string zMyglpObbW;
      if(wJjqVkhERd == tbqfrXdUCH){TApKFSzZUa = true;}
      else if(tbqfrXdUCH == wJjqVkhERd){QDYKhomxCO = true;}
      if(VWKPudUViY == kkYfJEanBB){FslscjXyVX = true;}
      else if(kkYfJEanBB == VWKPudUViY){XkgtVSgBCY = true;}
      if(zfmUYKDBcQ == LJCRFdiAxA){ebLekFCKmr = true;}
      else if(LJCRFdiAxA == zfmUYKDBcQ){GoxKzPIKMR = true;}
      if(fCgdffgcPJ == NcffrYlYub){JCDPNjPtTM = true;}
      else if(NcffrYlYub == fCgdffgcPJ){MoPeOaXwCk = true;}
      if(cGCCdkIZwn == SmdVeYscuX){WCHGBFZFDC = true;}
      else if(SmdVeYscuX == cGCCdkIZwn){EywJxJXZxc = true;}
      if(QitzAPVPSK == UqzDzkZYaO){RQGEqqoKZA = true;}
      else if(UqzDzkZYaO == QitzAPVPSK){BOcQraFOLS = true;}
      if(ggbBySpgiP == ocXBtIErmj){QnmcQCoWfs = true;}
      else if(ocXBtIErmj == ggbBySpgiP){gbkkCiVCft = true;}
      if(wrFYwrdkqm == RBrZhYefmg){TcdIBcTEde = true;}
      if(BcFnzwHgdQ == kFFZfVccgH){exGkZrwzYV = true;}
      if(JRJFbueBEK == zMyglpObbW){tEUTwiPeoy = true;}
      while(RBrZhYefmg == wrFYwrdkqm){ujyRTIrnMo = true;}
      while(kFFZfVccgH == kFFZfVccgH){rhMiPyLylm = true;}
      while(zMyglpObbW == zMyglpObbW){UIkjDcMLHO = true;}
      if(TApKFSzZUa == true){TApKFSzZUa = false;}
      if(FslscjXyVX == true){FslscjXyVX = false;}
      if(ebLekFCKmr == true){ebLekFCKmr = false;}
      if(JCDPNjPtTM == true){JCDPNjPtTM = false;}
      if(WCHGBFZFDC == true){WCHGBFZFDC = false;}
      if(RQGEqqoKZA == true){RQGEqqoKZA = false;}
      if(QnmcQCoWfs == true){QnmcQCoWfs = false;}
      if(TcdIBcTEde == true){TcdIBcTEde = false;}
      if(exGkZrwzYV == true){exGkZrwzYV = false;}
      if(tEUTwiPeoy == true){tEUTwiPeoy = false;}
      if(QDYKhomxCO == true){QDYKhomxCO = false;}
      if(XkgtVSgBCY == true){XkgtVSgBCY = false;}
      if(GoxKzPIKMR == true){GoxKzPIKMR = false;}
      if(MoPeOaXwCk == true){MoPeOaXwCk = false;}
      if(EywJxJXZxc == true){EywJxJXZxc = false;}
      if(BOcQraFOLS == true){BOcQraFOLS = false;}
      if(gbkkCiVCft == true){gbkkCiVCft = false;}
      if(ujyRTIrnMo == true){ujyRTIrnMo = false;}
      if(rhMiPyLylm == true){rhMiPyLylm = false;}
      if(UIkjDcMLHO == true){UIkjDcMLHO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SXABGYNCXA
{ 
  void LHcYURkwBP()
  { 
      bool wbkOObiPqF = false;
      bool FuQkAXYdBq = false;
      bool pBKWgaMcHQ = false;
      bool fRehddiHBH = false;
      bool eUTAaqmMFu = false;
      bool naOwmtQNhm = false;
      bool OFHZYmPhHV = false;
      bool oRctMVhKwo = false;
      bool nAWLcFDiui = false;
      bool NUYOrZMsam = false;
      bool aEEiGVyTiR = false;
      bool MFQsyNhwxT = false;
      bool jgmYIUrOBl = false;
      bool JojJOjwnFG = false;
      bool GizdVHDfPe = false;
      bool qQwGCsQfal = false;
      bool djSxHXVHeN = false;
      bool RtppMBhJCB = false;
      bool QLyWurscGU = false;
      bool SPNScWQCVy = false;
      string marBpcQsbN;
      string QcGiWGkEKN;
      string Ygszsuoodd;
      string RZpNMjASxs;
      string jcbFVHTPiL;
      string SHUjgGgrIu;
      string mbOywqmrVm;
      string GSGQduEncl;
      string aZGSLJEFfF;
      string CHJCGIOdIe;
      string TaswFzAEFl;
      string BsOVTMUwmm;
      string mgMPjyIEJV;
      string fafySAgJML;
      string IAzsEJrnht;
      string mRqUrlNcLG;
      string qutjFaMQDS;
      string eKiadlgSLa;
      string FTWPiNjKFf;
      string lDyGTMFPnc;
      if(marBpcQsbN == TaswFzAEFl){wbkOObiPqF = true;}
      else if(TaswFzAEFl == marBpcQsbN){aEEiGVyTiR = true;}
      if(QcGiWGkEKN == BsOVTMUwmm){FuQkAXYdBq = true;}
      else if(BsOVTMUwmm == QcGiWGkEKN){MFQsyNhwxT = true;}
      if(Ygszsuoodd == mgMPjyIEJV){pBKWgaMcHQ = true;}
      else if(mgMPjyIEJV == Ygszsuoodd){jgmYIUrOBl = true;}
      if(RZpNMjASxs == fafySAgJML){fRehddiHBH = true;}
      else if(fafySAgJML == RZpNMjASxs){JojJOjwnFG = true;}
      if(jcbFVHTPiL == IAzsEJrnht){eUTAaqmMFu = true;}
      else if(IAzsEJrnht == jcbFVHTPiL){GizdVHDfPe = true;}
      if(SHUjgGgrIu == mRqUrlNcLG){naOwmtQNhm = true;}
      else if(mRqUrlNcLG == SHUjgGgrIu){qQwGCsQfal = true;}
      if(mbOywqmrVm == qutjFaMQDS){OFHZYmPhHV = true;}
      else if(qutjFaMQDS == mbOywqmrVm){djSxHXVHeN = true;}
      if(GSGQduEncl == eKiadlgSLa){oRctMVhKwo = true;}
      if(aZGSLJEFfF == FTWPiNjKFf){nAWLcFDiui = true;}
      if(CHJCGIOdIe == lDyGTMFPnc){NUYOrZMsam = true;}
      while(eKiadlgSLa == GSGQduEncl){RtppMBhJCB = true;}
      while(FTWPiNjKFf == FTWPiNjKFf){QLyWurscGU = true;}
      while(lDyGTMFPnc == lDyGTMFPnc){SPNScWQCVy = true;}
      if(wbkOObiPqF == true){wbkOObiPqF = false;}
      if(FuQkAXYdBq == true){FuQkAXYdBq = false;}
      if(pBKWgaMcHQ == true){pBKWgaMcHQ = false;}
      if(fRehddiHBH == true){fRehddiHBH = false;}
      if(eUTAaqmMFu == true){eUTAaqmMFu = false;}
      if(naOwmtQNhm == true){naOwmtQNhm = false;}
      if(OFHZYmPhHV == true){OFHZYmPhHV = false;}
      if(oRctMVhKwo == true){oRctMVhKwo = false;}
      if(nAWLcFDiui == true){nAWLcFDiui = false;}
      if(NUYOrZMsam == true){NUYOrZMsam = false;}
      if(aEEiGVyTiR == true){aEEiGVyTiR = false;}
      if(MFQsyNhwxT == true){MFQsyNhwxT = false;}
      if(jgmYIUrOBl == true){jgmYIUrOBl = false;}
      if(JojJOjwnFG == true){JojJOjwnFG = false;}
      if(GizdVHDfPe == true){GizdVHDfPe = false;}
      if(qQwGCsQfal == true){qQwGCsQfal = false;}
      if(djSxHXVHeN == true){djSxHXVHeN = false;}
      if(RtppMBhJCB == true){RtppMBhJCB = false;}
      if(QLyWurscGU == true){QLyWurscGU = false;}
      if(SPNScWQCVy == true){SPNScWQCVy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWDLFGJHNV
{ 
  void IwiFfVHXBX()
  { 
      bool XFSxIMaVXk = false;
      bool raHJFaoOjg = false;
      bool TzUxwjtEbf = false;
      bool mywlzjYcDh = false;
      bool LQrgBjjDSz = false;
      bool NWHZjYkUAX = false;
      bool RVsrxsdVJV = false;
      bool CLLBUDHmwM = false;
      bool AplcRQqWCa = false;
      bool zEbeQpWzjI = false;
      bool FNswxCKFEf = false;
      bool RxYnWaiQZg = false;
      bool BHTiWxjfke = false;
      bool gHDmGmxoeP = false;
      bool FkRVIBenIo = false;
      bool GFYCGytJZz = false;
      bool ReUZzJtlgj = false;
      bool dtkKaQoxZU = false;
      bool SwXwXahAfI = false;
      bool rmOfxZQrWy = false;
      string LiZBMauUiM;
      string bYDCglJbLl;
      string rOMmFTSKWV;
      string tHrnZwtbtL;
      string DzhdPdWcaW;
      string EdWaCxVlwr;
      string HjxNSUfOcj;
      string qhhzhrfiWa;
      string wojzQPjQkb;
      string ZIeBDTBUKu;
      string yHzpeWwXsK;
      string RmOUwSAxwD;
      string kOdBKiCfwN;
      string pKXbcnpsUt;
      string TMXaKmsKFk;
      string TDXHJidyfw;
      string TPaeTGOmqH;
      string bHcCiYqDpW;
      string praLtllPRs;
      string KqMYaDkrGE;
      if(LiZBMauUiM == yHzpeWwXsK){XFSxIMaVXk = true;}
      else if(yHzpeWwXsK == LiZBMauUiM){FNswxCKFEf = true;}
      if(bYDCglJbLl == RmOUwSAxwD){raHJFaoOjg = true;}
      else if(RmOUwSAxwD == bYDCglJbLl){RxYnWaiQZg = true;}
      if(rOMmFTSKWV == kOdBKiCfwN){TzUxwjtEbf = true;}
      else if(kOdBKiCfwN == rOMmFTSKWV){BHTiWxjfke = true;}
      if(tHrnZwtbtL == pKXbcnpsUt){mywlzjYcDh = true;}
      else if(pKXbcnpsUt == tHrnZwtbtL){gHDmGmxoeP = true;}
      if(DzhdPdWcaW == TMXaKmsKFk){LQrgBjjDSz = true;}
      else if(TMXaKmsKFk == DzhdPdWcaW){FkRVIBenIo = true;}
      if(EdWaCxVlwr == TDXHJidyfw){NWHZjYkUAX = true;}
      else if(TDXHJidyfw == EdWaCxVlwr){GFYCGytJZz = true;}
      if(HjxNSUfOcj == TPaeTGOmqH){RVsrxsdVJV = true;}
      else if(TPaeTGOmqH == HjxNSUfOcj){ReUZzJtlgj = true;}
      if(qhhzhrfiWa == bHcCiYqDpW){CLLBUDHmwM = true;}
      if(wojzQPjQkb == praLtllPRs){AplcRQqWCa = true;}
      if(ZIeBDTBUKu == KqMYaDkrGE){zEbeQpWzjI = true;}
      while(bHcCiYqDpW == qhhzhrfiWa){dtkKaQoxZU = true;}
      while(praLtllPRs == praLtllPRs){SwXwXahAfI = true;}
      while(KqMYaDkrGE == KqMYaDkrGE){rmOfxZQrWy = true;}
      if(XFSxIMaVXk == true){XFSxIMaVXk = false;}
      if(raHJFaoOjg == true){raHJFaoOjg = false;}
      if(TzUxwjtEbf == true){TzUxwjtEbf = false;}
      if(mywlzjYcDh == true){mywlzjYcDh = false;}
      if(LQrgBjjDSz == true){LQrgBjjDSz = false;}
      if(NWHZjYkUAX == true){NWHZjYkUAX = false;}
      if(RVsrxsdVJV == true){RVsrxsdVJV = false;}
      if(CLLBUDHmwM == true){CLLBUDHmwM = false;}
      if(AplcRQqWCa == true){AplcRQqWCa = false;}
      if(zEbeQpWzjI == true){zEbeQpWzjI = false;}
      if(FNswxCKFEf == true){FNswxCKFEf = false;}
      if(RxYnWaiQZg == true){RxYnWaiQZg = false;}
      if(BHTiWxjfke == true){BHTiWxjfke = false;}
      if(gHDmGmxoeP == true){gHDmGmxoeP = false;}
      if(FkRVIBenIo == true){FkRVIBenIo = false;}
      if(GFYCGytJZz == true){GFYCGytJZz = false;}
      if(ReUZzJtlgj == true){ReUZzJtlgj = false;}
      if(dtkKaQoxZU == true){dtkKaQoxZU = false;}
      if(SwXwXahAfI == true){SwXwXahAfI = false;}
      if(rmOfxZQrWy == true){rmOfxZQrWy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VLWUQKUVGE
{ 
  void UEfJYbkdsV()
  { 
      bool HqXWSWgAyR = false;
      bool qELElFBYhj = false;
      bool iktankrDXk = false;
      bool tcULLtIdqk = false;
      bool JAzqxwDWoz = false;
      bool zGGnDVxwih = false;
      bool dcbNWOjArr = false;
      bool xXhwZilCdr = false;
      bool hVOYkmVfHo = false;
      bool xLuIHfYlTi = false;
      bool LCewCbYJNU = false;
      bool jtSqzIODbj = false;
      bool sErCtkbYos = false;
      bool KzhtfepRWJ = false;
      bool NLRmFCsEJz = false;
      bool RVKjpHJcCQ = false;
      bool zAUUKjLXKU = false;
      bool RwfSVglFwr = false;
      bool qXPpbooyEY = false;
      bool UNPFJNqxbU = false;
      string seQEfSxVzQ;
      string inVgNOzuwX;
      string OAAfhBnsnd;
      string DPTzcpiafX;
      string OWVozbMiIj;
      string ehlyVrejWd;
      string dEhUMSTVEX;
      string fYPXJreLgG;
      string oEjDyVcVcj;
      string LyEBtKoAbg;
      string HpekEGRNod;
      string NSDPnZTdVq;
      string oyrUMgUOdy;
      string CdiAyzZzzr;
      string EPfzVrunMT;
      string pLdkqJxKXX;
      string lDipaijDQo;
      string ATddlZRsyT;
      string lfBKIqAyIo;
      string BOaaFBfoXm;
      if(seQEfSxVzQ == HpekEGRNod){HqXWSWgAyR = true;}
      else if(HpekEGRNod == seQEfSxVzQ){LCewCbYJNU = true;}
      if(inVgNOzuwX == NSDPnZTdVq){qELElFBYhj = true;}
      else if(NSDPnZTdVq == inVgNOzuwX){jtSqzIODbj = true;}
      if(OAAfhBnsnd == oyrUMgUOdy){iktankrDXk = true;}
      else if(oyrUMgUOdy == OAAfhBnsnd){sErCtkbYos = true;}
      if(DPTzcpiafX == CdiAyzZzzr){tcULLtIdqk = true;}
      else if(CdiAyzZzzr == DPTzcpiafX){KzhtfepRWJ = true;}
      if(OWVozbMiIj == EPfzVrunMT){JAzqxwDWoz = true;}
      else if(EPfzVrunMT == OWVozbMiIj){NLRmFCsEJz = true;}
      if(ehlyVrejWd == pLdkqJxKXX){zGGnDVxwih = true;}
      else if(pLdkqJxKXX == ehlyVrejWd){RVKjpHJcCQ = true;}
      if(dEhUMSTVEX == lDipaijDQo){dcbNWOjArr = true;}
      else if(lDipaijDQo == dEhUMSTVEX){zAUUKjLXKU = true;}
      if(fYPXJreLgG == ATddlZRsyT){xXhwZilCdr = true;}
      if(oEjDyVcVcj == lfBKIqAyIo){hVOYkmVfHo = true;}
      if(LyEBtKoAbg == BOaaFBfoXm){xLuIHfYlTi = true;}
      while(ATddlZRsyT == fYPXJreLgG){RwfSVglFwr = true;}
      while(lfBKIqAyIo == lfBKIqAyIo){qXPpbooyEY = true;}
      while(BOaaFBfoXm == BOaaFBfoXm){UNPFJNqxbU = true;}
      if(HqXWSWgAyR == true){HqXWSWgAyR = false;}
      if(qELElFBYhj == true){qELElFBYhj = false;}
      if(iktankrDXk == true){iktankrDXk = false;}
      if(tcULLtIdqk == true){tcULLtIdqk = false;}
      if(JAzqxwDWoz == true){JAzqxwDWoz = false;}
      if(zGGnDVxwih == true){zGGnDVxwih = false;}
      if(dcbNWOjArr == true){dcbNWOjArr = false;}
      if(xXhwZilCdr == true){xXhwZilCdr = false;}
      if(hVOYkmVfHo == true){hVOYkmVfHo = false;}
      if(xLuIHfYlTi == true){xLuIHfYlTi = false;}
      if(LCewCbYJNU == true){LCewCbYJNU = false;}
      if(jtSqzIODbj == true){jtSqzIODbj = false;}
      if(sErCtkbYos == true){sErCtkbYos = false;}
      if(KzhtfepRWJ == true){KzhtfepRWJ = false;}
      if(NLRmFCsEJz == true){NLRmFCsEJz = false;}
      if(RVKjpHJcCQ == true){RVKjpHJcCQ = false;}
      if(zAUUKjLXKU == true){zAUUKjLXKU = false;}
      if(RwfSVglFwr == true){RwfSVglFwr = false;}
      if(qXPpbooyEY == true){qXPpbooyEY = false;}
      if(UNPFJNqxbU == true){UNPFJNqxbU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZOQXDCJDT
{ 
  void cfgXqrriox()
  { 
      bool PXJjjEFinh = false;
      bool THnEFCdRRN = false;
      bool lCyQPdiHtG = false;
      bool RcsHJUVuyl = false;
      bool oPxeURqgyC = false;
      bool imsacMZsTF = false;
      bool UynhPpNfuj = false;
      bool fhSeXVFSwy = false;
      bool mBJrXejSex = false;
      bool ubarQqaPPd = false;
      bool DLlNVATNCH = false;
      bool GGxVSSowJj = false;
      bool GuBxoEGZNg = false;
      bool toCRtaPuVW = false;
      bool LWPWpndFYy = false;
      bool BeFfWIKnYR = false;
      bool sszUMRDebr = false;
      bool DsZmYiedHA = false;
      bool ZBBPfPiWtk = false;
      bool QbWEcRXtJX = false;
      string mlLdBXAszK;
      string lgfadfjKnl;
      string RTMkSIytzA;
      string kekgkMnZYS;
      string OYSVmJVYXT;
      string lAxuNSYaKr;
      string YFszYHuzpQ;
      string qJkVXrApxJ;
      string lYVfOjgoSS;
      string mNPfsIeTwe;
      string NViGcbObWV;
      string RicAGzjNko;
      string aGfXcdtFbO;
      string MgsRwPpOCl;
      string VESxAEjOZs;
      string YRhHEHpLcz;
      string hJAHIkoLEp;
      string JULzSWmhXY;
      string sfehpuzlNn;
      string ZekDEMEKnP;
      if(mlLdBXAszK == NViGcbObWV){PXJjjEFinh = true;}
      else if(NViGcbObWV == mlLdBXAszK){DLlNVATNCH = true;}
      if(lgfadfjKnl == RicAGzjNko){THnEFCdRRN = true;}
      else if(RicAGzjNko == lgfadfjKnl){GGxVSSowJj = true;}
      if(RTMkSIytzA == aGfXcdtFbO){lCyQPdiHtG = true;}
      else if(aGfXcdtFbO == RTMkSIytzA){GuBxoEGZNg = true;}
      if(kekgkMnZYS == MgsRwPpOCl){RcsHJUVuyl = true;}
      else if(MgsRwPpOCl == kekgkMnZYS){toCRtaPuVW = true;}
      if(OYSVmJVYXT == VESxAEjOZs){oPxeURqgyC = true;}
      else if(VESxAEjOZs == OYSVmJVYXT){LWPWpndFYy = true;}
      if(lAxuNSYaKr == YRhHEHpLcz){imsacMZsTF = true;}
      else if(YRhHEHpLcz == lAxuNSYaKr){BeFfWIKnYR = true;}
      if(YFszYHuzpQ == hJAHIkoLEp){UynhPpNfuj = true;}
      else if(hJAHIkoLEp == YFszYHuzpQ){sszUMRDebr = true;}
      if(qJkVXrApxJ == JULzSWmhXY){fhSeXVFSwy = true;}
      if(lYVfOjgoSS == sfehpuzlNn){mBJrXejSex = true;}
      if(mNPfsIeTwe == ZekDEMEKnP){ubarQqaPPd = true;}
      while(JULzSWmhXY == qJkVXrApxJ){DsZmYiedHA = true;}
      while(sfehpuzlNn == sfehpuzlNn){ZBBPfPiWtk = true;}
      while(ZekDEMEKnP == ZekDEMEKnP){QbWEcRXtJX = true;}
      if(PXJjjEFinh == true){PXJjjEFinh = false;}
      if(THnEFCdRRN == true){THnEFCdRRN = false;}
      if(lCyQPdiHtG == true){lCyQPdiHtG = false;}
      if(RcsHJUVuyl == true){RcsHJUVuyl = false;}
      if(oPxeURqgyC == true){oPxeURqgyC = false;}
      if(imsacMZsTF == true){imsacMZsTF = false;}
      if(UynhPpNfuj == true){UynhPpNfuj = false;}
      if(fhSeXVFSwy == true){fhSeXVFSwy = false;}
      if(mBJrXejSex == true){mBJrXejSex = false;}
      if(ubarQqaPPd == true){ubarQqaPPd = false;}
      if(DLlNVATNCH == true){DLlNVATNCH = false;}
      if(GGxVSSowJj == true){GGxVSSowJj = false;}
      if(GuBxoEGZNg == true){GuBxoEGZNg = false;}
      if(toCRtaPuVW == true){toCRtaPuVW = false;}
      if(LWPWpndFYy == true){LWPWpndFYy = false;}
      if(BeFfWIKnYR == true){BeFfWIKnYR = false;}
      if(sszUMRDebr == true){sszUMRDebr = false;}
      if(DsZmYiedHA == true){DsZmYiedHA = false;}
      if(ZBBPfPiWtk == true){ZBBPfPiWtk = false;}
      if(QbWEcRXtJX == true){QbWEcRXtJX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSAXGNSPOC
{ 
  void GZQiRZEYZQ()
  { 
      bool ytImWzkRaC = false;
      bool jbQEkEqIMO = false;
      bool ImZbqCBbeO = false;
      bool wOKbsrZQqn = false;
      bool LHoqkSIMiT = false;
      bool KOillLUguU = false;
      bool xImMFVQoKs = false;
      bool eaQYCAxhpY = false;
      bool sorKDhfYph = false;
      bool WrVWpDUclP = false;
      bool BTBpojxJik = false;
      bool NlqVaIPcIW = false;
      bool przbVlEtiy = false;
      bool fUwaXZmCUT = false;
      bool jVoEUkBzuh = false;
      bool nqTOYIUYTC = false;
      bool eDakFsoPyA = false;
      bool UMHolTCtHj = false;
      bool kFyBKnAhBO = false;
      bool FOiSnguEza = false;
      string cdYOnYmlaI;
      string PWUWobMdTr;
      string fSGmfanAgY;
      string URNuQigDGU;
      string mcmsjMiquR;
      string kxjKsJXkhM;
      string jlFCmxJYFF;
      string tJXyFDfNCT;
      string rxEOmXgCCG;
      string LuUskAXjGm;
      string CKkpWbZkFp;
      string dKhOTmhpOO;
      string PHWyszodNF;
      string euHPQhLOrL;
      string yuwLcBMGZy;
      string ShVqWumlxX;
      string mwXALhCSxl;
      string aSxDQUKLVr;
      string lhEOmxZPsV;
      string tYRUYCXwAt;
      if(cdYOnYmlaI == CKkpWbZkFp){ytImWzkRaC = true;}
      else if(CKkpWbZkFp == cdYOnYmlaI){BTBpojxJik = true;}
      if(PWUWobMdTr == dKhOTmhpOO){jbQEkEqIMO = true;}
      else if(dKhOTmhpOO == PWUWobMdTr){NlqVaIPcIW = true;}
      if(fSGmfanAgY == PHWyszodNF){ImZbqCBbeO = true;}
      else if(PHWyszodNF == fSGmfanAgY){przbVlEtiy = true;}
      if(URNuQigDGU == euHPQhLOrL){wOKbsrZQqn = true;}
      else if(euHPQhLOrL == URNuQigDGU){fUwaXZmCUT = true;}
      if(mcmsjMiquR == yuwLcBMGZy){LHoqkSIMiT = true;}
      else if(yuwLcBMGZy == mcmsjMiquR){jVoEUkBzuh = true;}
      if(kxjKsJXkhM == ShVqWumlxX){KOillLUguU = true;}
      else if(ShVqWumlxX == kxjKsJXkhM){nqTOYIUYTC = true;}
      if(jlFCmxJYFF == mwXALhCSxl){xImMFVQoKs = true;}
      else if(mwXALhCSxl == jlFCmxJYFF){eDakFsoPyA = true;}
      if(tJXyFDfNCT == aSxDQUKLVr){eaQYCAxhpY = true;}
      if(rxEOmXgCCG == lhEOmxZPsV){sorKDhfYph = true;}
      if(LuUskAXjGm == tYRUYCXwAt){WrVWpDUclP = true;}
      while(aSxDQUKLVr == tJXyFDfNCT){UMHolTCtHj = true;}
      while(lhEOmxZPsV == lhEOmxZPsV){kFyBKnAhBO = true;}
      while(tYRUYCXwAt == tYRUYCXwAt){FOiSnguEza = true;}
      if(ytImWzkRaC == true){ytImWzkRaC = false;}
      if(jbQEkEqIMO == true){jbQEkEqIMO = false;}
      if(ImZbqCBbeO == true){ImZbqCBbeO = false;}
      if(wOKbsrZQqn == true){wOKbsrZQqn = false;}
      if(LHoqkSIMiT == true){LHoqkSIMiT = false;}
      if(KOillLUguU == true){KOillLUguU = false;}
      if(xImMFVQoKs == true){xImMFVQoKs = false;}
      if(eaQYCAxhpY == true){eaQYCAxhpY = false;}
      if(sorKDhfYph == true){sorKDhfYph = false;}
      if(WrVWpDUclP == true){WrVWpDUclP = false;}
      if(BTBpojxJik == true){BTBpojxJik = false;}
      if(NlqVaIPcIW == true){NlqVaIPcIW = false;}
      if(przbVlEtiy == true){przbVlEtiy = false;}
      if(fUwaXZmCUT == true){fUwaXZmCUT = false;}
      if(jVoEUkBzuh == true){jVoEUkBzuh = false;}
      if(nqTOYIUYTC == true){nqTOYIUYTC = false;}
      if(eDakFsoPyA == true){eDakFsoPyA = false;}
      if(UMHolTCtHj == true){UMHolTCtHj = false;}
      if(kFyBKnAhBO == true){kFyBKnAhBO = false;}
      if(FOiSnguEza == true){FOiSnguEza = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFMFMVZIIT
{ 
  void SWQYFpXxnm()
  { 
      bool ZQGbJLYiWC = false;
      bool fllHXyAdeN = false;
      bool aPSTlULBKl = false;
      bool dKeLOAaxWK = false;
      bool GBBaISHdth = false;
      bool xVoTeJylpo = false;
      bool zWYkXUGZrX = false;
      bool XCHTGZOqLT = false;
      bool NhHbnIULgE = false;
      bool BnHhLjbQDm = false;
      bool LhkVKtOVME = false;
      bool uHaVbROxwP = false;
      bool AusnViuYIW = false;
      bool yxnXIexkRt = false;
      bool szybItNlGt = false;
      bool UeTmmPnwAa = false;
      bool zpMpGySCNw = false;
      bool TdfCVAxQfa = false;
      bool UIROBScAjr = false;
      bool qAkptDmHVK = false;
      string fbVszuYGiX;
      string OxoalIOMdI;
      string ZRLfYMxQyn;
      string WquHCzJsDj;
      string sdaQwMULkT;
      string ydLtNNPpUm;
      string yIHuAWBgYl;
      string yVJsPuquiL;
      string qkeeprfAso;
      string iTYPlkVfPY;
      string LmmyVcTSeS;
      string WUGIuMccEI;
      string qAnjDewtGd;
      string YLfKzExfIN;
      string XMVaROMPTY;
      string HsaHgKzDup;
      string fZLBsLnuIq;
      string OwTqjeeMRn;
      string RgZgVfjYco;
      string EtkSgxATgG;
      if(fbVszuYGiX == LmmyVcTSeS){ZQGbJLYiWC = true;}
      else if(LmmyVcTSeS == fbVszuYGiX){LhkVKtOVME = true;}
      if(OxoalIOMdI == WUGIuMccEI){fllHXyAdeN = true;}
      else if(WUGIuMccEI == OxoalIOMdI){uHaVbROxwP = true;}
      if(ZRLfYMxQyn == qAnjDewtGd){aPSTlULBKl = true;}
      else if(qAnjDewtGd == ZRLfYMxQyn){AusnViuYIW = true;}
      if(WquHCzJsDj == YLfKzExfIN){dKeLOAaxWK = true;}
      else if(YLfKzExfIN == WquHCzJsDj){yxnXIexkRt = true;}
      if(sdaQwMULkT == XMVaROMPTY){GBBaISHdth = true;}
      else if(XMVaROMPTY == sdaQwMULkT){szybItNlGt = true;}
      if(ydLtNNPpUm == HsaHgKzDup){xVoTeJylpo = true;}
      else if(HsaHgKzDup == ydLtNNPpUm){UeTmmPnwAa = true;}
      if(yIHuAWBgYl == fZLBsLnuIq){zWYkXUGZrX = true;}
      else if(fZLBsLnuIq == yIHuAWBgYl){zpMpGySCNw = true;}
      if(yVJsPuquiL == OwTqjeeMRn){XCHTGZOqLT = true;}
      if(qkeeprfAso == RgZgVfjYco){NhHbnIULgE = true;}
      if(iTYPlkVfPY == EtkSgxATgG){BnHhLjbQDm = true;}
      while(OwTqjeeMRn == yVJsPuquiL){TdfCVAxQfa = true;}
      while(RgZgVfjYco == RgZgVfjYco){UIROBScAjr = true;}
      while(EtkSgxATgG == EtkSgxATgG){qAkptDmHVK = true;}
      if(ZQGbJLYiWC == true){ZQGbJLYiWC = false;}
      if(fllHXyAdeN == true){fllHXyAdeN = false;}
      if(aPSTlULBKl == true){aPSTlULBKl = false;}
      if(dKeLOAaxWK == true){dKeLOAaxWK = false;}
      if(GBBaISHdth == true){GBBaISHdth = false;}
      if(xVoTeJylpo == true){xVoTeJylpo = false;}
      if(zWYkXUGZrX == true){zWYkXUGZrX = false;}
      if(XCHTGZOqLT == true){XCHTGZOqLT = false;}
      if(NhHbnIULgE == true){NhHbnIULgE = false;}
      if(BnHhLjbQDm == true){BnHhLjbQDm = false;}
      if(LhkVKtOVME == true){LhkVKtOVME = false;}
      if(uHaVbROxwP == true){uHaVbROxwP = false;}
      if(AusnViuYIW == true){AusnViuYIW = false;}
      if(yxnXIexkRt == true){yxnXIexkRt = false;}
      if(szybItNlGt == true){szybItNlGt = false;}
      if(UeTmmPnwAa == true){UeTmmPnwAa = false;}
      if(zpMpGySCNw == true){zpMpGySCNw = false;}
      if(TdfCVAxQfa == true){TdfCVAxQfa = false;}
      if(UIROBScAjr == true){UIROBScAjr = false;}
      if(qAkptDmHVK == true){qAkptDmHVK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGTTEEZNNH
{ 
  void rIxqPPCfau()
  { 
      bool XnIooeWNCl = false;
      bool AETZBXFQLG = false;
      bool OBWbIAqszZ = false;
      bool wmdDQdWyFP = false;
      bool fuJEPeRSWO = false;
      bool jnGEkVRffn = false;
      bool ndNbpMaQIW = false;
      bool AGKwaTqRMd = false;
      bool hXVkpHgYSt = false;
      bool MpSRbBghOC = false;
      bool DBJzNcdJdQ = false;
      bool ezTCFPHckh = false;
      bool fCxNKKnsUY = false;
      bool mJCKZgNWWN = false;
      bool dWtCPMVPLL = false;
      bool tExfWADwoD = false;
      bool njoFdVwJbY = false;
      bool BjFWEIHuyx = false;
      bool nYhIdhLWmY = false;
      bool cRhTZshoXs = false;
      string YxsaMnWlAf;
      string xojtPsXZYH;
      string eJKNJLijrA;
      string idUHQObeDc;
      string rqaOaEeaoI;
      string bkdfmOmfRB;
      string ElszxTTccA;
      string RsWuPniulF;
      string fIuiXxAoTC;
      string bwMCXFxaRH;
      string jCynpiOhQz;
      string eqsMUwqJaz;
      string TdIaYVfUWJ;
      string pHdeUcJHro;
      string iRYTWjCAgb;
      string OnzRnFsXOU;
      string CsLGIWMNqr;
      string liQlPBFoDn;
      string SenutCILqP;
      string ilrXloFRLz;
      if(YxsaMnWlAf == jCynpiOhQz){XnIooeWNCl = true;}
      else if(jCynpiOhQz == YxsaMnWlAf){DBJzNcdJdQ = true;}
      if(xojtPsXZYH == eqsMUwqJaz){AETZBXFQLG = true;}
      else if(eqsMUwqJaz == xojtPsXZYH){ezTCFPHckh = true;}
      if(eJKNJLijrA == TdIaYVfUWJ){OBWbIAqszZ = true;}
      else if(TdIaYVfUWJ == eJKNJLijrA){fCxNKKnsUY = true;}
      if(idUHQObeDc == pHdeUcJHro){wmdDQdWyFP = true;}
      else if(pHdeUcJHro == idUHQObeDc){mJCKZgNWWN = true;}
      if(rqaOaEeaoI == iRYTWjCAgb){fuJEPeRSWO = true;}
      else if(iRYTWjCAgb == rqaOaEeaoI){dWtCPMVPLL = true;}
      if(bkdfmOmfRB == OnzRnFsXOU){jnGEkVRffn = true;}
      else if(OnzRnFsXOU == bkdfmOmfRB){tExfWADwoD = true;}
      if(ElszxTTccA == CsLGIWMNqr){ndNbpMaQIW = true;}
      else if(CsLGIWMNqr == ElszxTTccA){njoFdVwJbY = true;}
      if(RsWuPniulF == liQlPBFoDn){AGKwaTqRMd = true;}
      if(fIuiXxAoTC == SenutCILqP){hXVkpHgYSt = true;}
      if(bwMCXFxaRH == ilrXloFRLz){MpSRbBghOC = true;}
      while(liQlPBFoDn == RsWuPniulF){BjFWEIHuyx = true;}
      while(SenutCILqP == SenutCILqP){nYhIdhLWmY = true;}
      while(ilrXloFRLz == ilrXloFRLz){cRhTZshoXs = true;}
      if(XnIooeWNCl == true){XnIooeWNCl = false;}
      if(AETZBXFQLG == true){AETZBXFQLG = false;}
      if(OBWbIAqszZ == true){OBWbIAqszZ = false;}
      if(wmdDQdWyFP == true){wmdDQdWyFP = false;}
      if(fuJEPeRSWO == true){fuJEPeRSWO = false;}
      if(jnGEkVRffn == true){jnGEkVRffn = false;}
      if(ndNbpMaQIW == true){ndNbpMaQIW = false;}
      if(AGKwaTqRMd == true){AGKwaTqRMd = false;}
      if(hXVkpHgYSt == true){hXVkpHgYSt = false;}
      if(MpSRbBghOC == true){MpSRbBghOC = false;}
      if(DBJzNcdJdQ == true){DBJzNcdJdQ = false;}
      if(ezTCFPHckh == true){ezTCFPHckh = false;}
      if(fCxNKKnsUY == true){fCxNKKnsUY = false;}
      if(mJCKZgNWWN == true){mJCKZgNWWN = false;}
      if(dWtCPMVPLL == true){dWtCPMVPLL = false;}
      if(tExfWADwoD == true){tExfWADwoD = false;}
      if(njoFdVwJbY == true){njoFdVwJbY = false;}
      if(BjFWEIHuyx == true){BjFWEIHuyx = false;}
      if(nYhIdhLWmY == true){nYhIdhLWmY = false;}
      if(cRhTZshoXs == true){cRhTZshoXs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSWLNACIWM
{ 
  void KbuPlJejkV()
  { 
      bool fKGGmjeeGp = false;
      bool CyKiDbRGsK = false;
      bool CifGtQEtzf = false;
      bool UecygsiamP = false;
      bool jeFUjmCQTs = false;
      bool zyCTOxdAMV = false;
      bool ejeaVWUMBK = false;
      bool rqTcZWdLWH = false;
      bool NnaFgVbJij = false;
      bool PiOQkAzdzM = false;
      bool RpOIAHdZsq = false;
      bool SSdFIqIZtz = false;
      bool tLcRuJcDrZ = false;
      bool XzMJoXYRFZ = false;
      bool qCQrQwFJHt = false;
      bool qZjzRFMxNp = false;
      bool dahTTTGTPk = false;
      bool RqTUHrtkBy = false;
      bool ETuyhxOMri = false;
      bool KbDOuQUxXw = false;
      string QocLNlcYKa;
      string bSkaITbTex;
      string odwErfOuhF;
      string dFehjfscqG;
      string ViNOzhUINo;
      string IuwIqlsXTh;
      string XhpFxVmCpb;
      string azcYaFQhEK;
      string KFhsxiJWpy;
      string mUIJhnsHRc;
      string tSSlNISWgl;
      string ULSIXRAxIN;
      string MQLroFpSpm;
      string LIPbPrmwen;
      string QloEcbBzlQ;
      string mwzDQdGZwH;
      string SzgsZLuqse;
      string dDRUxZaHON;
      string EpgZzPJLKl;
      string kNzWVQFwdQ;
      if(QocLNlcYKa == tSSlNISWgl){fKGGmjeeGp = true;}
      else if(tSSlNISWgl == QocLNlcYKa){RpOIAHdZsq = true;}
      if(bSkaITbTex == ULSIXRAxIN){CyKiDbRGsK = true;}
      else if(ULSIXRAxIN == bSkaITbTex){SSdFIqIZtz = true;}
      if(odwErfOuhF == MQLroFpSpm){CifGtQEtzf = true;}
      else if(MQLroFpSpm == odwErfOuhF){tLcRuJcDrZ = true;}
      if(dFehjfscqG == LIPbPrmwen){UecygsiamP = true;}
      else if(LIPbPrmwen == dFehjfscqG){XzMJoXYRFZ = true;}
      if(ViNOzhUINo == QloEcbBzlQ){jeFUjmCQTs = true;}
      else if(QloEcbBzlQ == ViNOzhUINo){qCQrQwFJHt = true;}
      if(IuwIqlsXTh == mwzDQdGZwH){zyCTOxdAMV = true;}
      else if(mwzDQdGZwH == IuwIqlsXTh){qZjzRFMxNp = true;}
      if(XhpFxVmCpb == SzgsZLuqse){ejeaVWUMBK = true;}
      else if(SzgsZLuqse == XhpFxVmCpb){dahTTTGTPk = true;}
      if(azcYaFQhEK == dDRUxZaHON){rqTcZWdLWH = true;}
      if(KFhsxiJWpy == EpgZzPJLKl){NnaFgVbJij = true;}
      if(mUIJhnsHRc == kNzWVQFwdQ){PiOQkAzdzM = true;}
      while(dDRUxZaHON == azcYaFQhEK){RqTUHrtkBy = true;}
      while(EpgZzPJLKl == EpgZzPJLKl){ETuyhxOMri = true;}
      while(kNzWVQFwdQ == kNzWVQFwdQ){KbDOuQUxXw = true;}
      if(fKGGmjeeGp == true){fKGGmjeeGp = false;}
      if(CyKiDbRGsK == true){CyKiDbRGsK = false;}
      if(CifGtQEtzf == true){CifGtQEtzf = false;}
      if(UecygsiamP == true){UecygsiamP = false;}
      if(jeFUjmCQTs == true){jeFUjmCQTs = false;}
      if(zyCTOxdAMV == true){zyCTOxdAMV = false;}
      if(ejeaVWUMBK == true){ejeaVWUMBK = false;}
      if(rqTcZWdLWH == true){rqTcZWdLWH = false;}
      if(NnaFgVbJij == true){NnaFgVbJij = false;}
      if(PiOQkAzdzM == true){PiOQkAzdzM = false;}
      if(RpOIAHdZsq == true){RpOIAHdZsq = false;}
      if(SSdFIqIZtz == true){SSdFIqIZtz = false;}
      if(tLcRuJcDrZ == true){tLcRuJcDrZ = false;}
      if(XzMJoXYRFZ == true){XzMJoXYRFZ = false;}
      if(qCQrQwFJHt == true){qCQrQwFJHt = false;}
      if(qZjzRFMxNp == true){qZjzRFMxNp = false;}
      if(dahTTTGTPk == true){dahTTTGTPk = false;}
      if(RqTUHrtkBy == true){RqTUHrtkBy = false;}
      if(ETuyhxOMri == true){ETuyhxOMri = false;}
      if(KbDOuQUxXw == true){KbDOuQUxXw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSPLJPHWUK
{ 
  void AapIIPxuow()
  { 
      bool zrHNsKjlLR = false;
      bool IFZPzksDRG = false;
      bool ZwfIKFlLQj = false;
      bool eSliqdRbgL = false;
      bool eEPuNKNPuL = false;
      bool pauJVDLyCm = false;
      bool XXVbmoTqXV = false;
      bool TQWFbUgjuA = false;
      bool qWPEtDXbNn = false;
      bool RSZtnGinHX = false;
      bool pWqZrYEphA = false;
      bool WaCCuAIQgi = false;
      bool RrdiDApcQU = false;
      bool kscXJUepMU = false;
      bool zgtMRqQXym = false;
      bool ySGYGyrHVr = false;
      bool ibYMOdyera = false;
      bool UREMjjyRRM = false;
      bool jSddWSlEQL = false;
      bool cXTTlXIgxn = false;
      string LPOwiTOMsd;
      string AZDBePobqZ;
      string unJwYOrAxq;
      string MhEEqKnAIC;
      string tcZiMqtEqE;
      string LggRsWGSXT;
      string aNPCRSUzJT;
      string bnSoeSOZig;
      string TnJreeAmLT;
      string EUcnagNWRt;
      string WutWbWNrlZ;
      string IfipAmEWWl;
      string RgmpPHLdNy;
      string FqHoKYslPI;
      string RIAkLXllnm;
      string bpAfboHEHU;
      string KidnUQXtea;
      string tRGOTJfCdq;
      string VYoZVOqbNV;
      string QneuxieMPu;
      if(LPOwiTOMsd == WutWbWNrlZ){zrHNsKjlLR = true;}
      else if(WutWbWNrlZ == LPOwiTOMsd){pWqZrYEphA = true;}
      if(AZDBePobqZ == IfipAmEWWl){IFZPzksDRG = true;}
      else if(IfipAmEWWl == AZDBePobqZ){WaCCuAIQgi = true;}
      if(unJwYOrAxq == RgmpPHLdNy){ZwfIKFlLQj = true;}
      else if(RgmpPHLdNy == unJwYOrAxq){RrdiDApcQU = true;}
      if(MhEEqKnAIC == FqHoKYslPI){eSliqdRbgL = true;}
      else if(FqHoKYslPI == MhEEqKnAIC){kscXJUepMU = true;}
      if(tcZiMqtEqE == RIAkLXllnm){eEPuNKNPuL = true;}
      else if(RIAkLXllnm == tcZiMqtEqE){zgtMRqQXym = true;}
      if(LggRsWGSXT == bpAfboHEHU){pauJVDLyCm = true;}
      else if(bpAfboHEHU == LggRsWGSXT){ySGYGyrHVr = true;}
      if(aNPCRSUzJT == KidnUQXtea){XXVbmoTqXV = true;}
      else if(KidnUQXtea == aNPCRSUzJT){ibYMOdyera = true;}
      if(bnSoeSOZig == tRGOTJfCdq){TQWFbUgjuA = true;}
      if(TnJreeAmLT == VYoZVOqbNV){qWPEtDXbNn = true;}
      if(EUcnagNWRt == QneuxieMPu){RSZtnGinHX = true;}
      while(tRGOTJfCdq == bnSoeSOZig){UREMjjyRRM = true;}
      while(VYoZVOqbNV == VYoZVOqbNV){jSddWSlEQL = true;}
      while(QneuxieMPu == QneuxieMPu){cXTTlXIgxn = true;}
      if(zrHNsKjlLR == true){zrHNsKjlLR = false;}
      if(IFZPzksDRG == true){IFZPzksDRG = false;}
      if(ZwfIKFlLQj == true){ZwfIKFlLQj = false;}
      if(eSliqdRbgL == true){eSliqdRbgL = false;}
      if(eEPuNKNPuL == true){eEPuNKNPuL = false;}
      if(pauJVDLyCm == true){pauJVDLyCm = false;}
      if(XXVbmoTqXV == true){XXVbmoTqXV = false;}
      if(TQWFbUgjuA == true){TQWFbUgjuA = false;}
      if(qWPEtDXbNn == true){qWPEtDXbNn = false;}
      if(RSZtnGinHX == true){RSZtnGinHX = false;}
      if(pWqZrYEphA == true){pWqZrYEphA = false;}
      if(WaCCuAIQgi == true){WaCCuAIQgi = false;}
      if(RrdiDApcQU == true){RrdiDApcQU = false;}
      if(kscXJUepMU == true){kscXJUepMU = false;}
      if(zgtMRqQXym == true){zgtMRqQXym = false;}
      if(ySGYGyrHVr == true){ySGYGyrHVr = false;}
      if(ibYMOdyera == true){ibYMOdyera = false;}
      if(UREMjjyRRM == true){UREMjjyRRM = false;}
      if(jSddWSlEQL == true){jSddWSlEQL = false;}
      if(cXTTlXIgxn == true){cXTTlXIgxn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AIMGYKMJFL
{ 
  void TcwxVRKess()
  { 
      bool naFNtZyFTG = false;
      bool XtDZzgWdGS = false;
      bool TQxoAkTHLD = false;
      bool WZGWUoCACO = false;
      bool ttwHbTachA = false;
      bool DItTyXdQMJ = false;
      bool FqsPjxngFJ = false;
      bool dWbrXYToNf = false;
      bool KpYKzNelYw = false;
      bool LlmsIDAfWd = false;
      bool fsWXVfgCwY = false;
      bool DnCgyPRiQV = false;
      bool RBHJyrjhiU = false;
      bool YmSizQTBoT = false;
      bool gcpzrWjFts = false;
      bool lRPAMelNYd = false;
      bool wyTbAQUSgh = false;
      bool uQswooKIQb = false;
      bool IdnoiGWRWU = false;
      bool eFbLWhIOzb = false;
      string xxqRjdXDfQ;
      string IPRTBShWmO;
      string XOGfFnwLGx;
      string rlIkmGnung;
      string UTzIKfJCJt;
      string fHocuhqLMu;
      string hMwiXVGfgt;
      string dlhGtDPxUY;
      string esBLRjxfoE;
      string PciryHXQjo;
      string ZcVOPsZihq;
      string StpnQnKjRn;
      string XZpbeBDoHl;
      string fzMezBXmuX;
      string KOxxlVlubK;
      string xmzwQzmsjO;
      string pjawLTgLoO;
      string PWnscJbroJ;
      string PINxoszPOz;
      string OeDghZmBlS;
      if(xxqRjdXDfQ == ZcVOPsZihq){naFNtZyFTG = true;}
      else if(ZcVOPsZihq == xxqRjdXDfQ){fsWXVfgCwY = true;}
      if(IPRTBShWmO == StpnQnKjRn){XtDZzgWdGS = true;}
      else if(StpnQnKjRn == IPRTBShWmO){DnCgyPRiQV = true;}
      if(XOGfFnwLGx == XZpbeBDoHl){TQxoAkTHLD = true;}
      else if(XZpbeBDoHl == XOGfFnwLGx){RBHJyrjhiU = true;}
      if(rlIkmGnung == fzMezBXmuX){WZGWUoCACO = true;}
      else if(fzMezBXmuX == rlIkmGnung){YmSizQTBoT = true;}
      if(UTzIKfJCJt == KOxxlVlubK){ttwHbTachA = true;}
      else if(KOxxlVlubK == UTzIKfJCJt){gcpzrWjFts = true;}
      if(fHocuhqLMu == xmzwQzmsjO){DItTyXdQMJ = true;}
      else if(xmzwQzmsjO == fHocuhqLMu){lRPAMelNYd = true;}
      if(hMwiXVGfgt == pjawLTgLoO){FqsPjxngFJ = true;}
      else if(pjawLTgLoO == hMwiXVGfgt){wyTbAQUSgh = true;}
      if(dlhGtDPxUY == PWnscJbroJ){dWbrXYToNf = true;}
      if(esBLRjxfoE == PINxoszPOz){KpYKzNelYw = true;}
      if(PciryHXQjo == OeDghZmBlS){LlmsIDAfWd = true;}
      while(PWnscJbroJ == dlhGtDPxUY){uQswooKIQb = true;}
      while(PINxoszPOz == PINxoszPOz){IdnoiGWRWU = true;}
      while(OeDghZmBlS == OeDghZmBlS){eFbLWhIOzb = true;}
      if(naFNtZyFTG == true){naFNtZyFTG = false;}
      if(XtDZzgWdGS == true){XtDZzgWdGS = false;}
      if(TQxoAkTHLD == true){TQxoAkTHLD = false;}
      if(WZGWUoCACO == true){WZGWUoCACO = false;}
      if(ttwHbTachA == true){ttwHbTachA = false;}
      if(DItTyXdQMJ == true){DItTyXdQMJ = false;}
      if(FqsPjxngFJ == true){FqsPjxngFJ = false;}
      if(dWbrXYToNf == true){dWbrXYToNf = false;}
      if(KpYKzNelYw == true){KpYKzNelYw = false;}
      if(LlmsIDAfWd == true){LlmsIDAfWd = false;}
      if(fsWXVfgCwY == true){fsWXVfgCwY = false;}
      if(DnCgyPRiQV == true){DnCgyPRiQV = false;}
      if(RBHJyrjhiU == true){RBHJyrjhiU = false;}
      if(YmSizQTBoT == true){YmSizQTBoT = false;}
      if(gcpzrWjFts == true){gcpzrWjFts = false;}
      if(lRPAMelNYd == true){lRPAMelNYd = false;}
      if(wyTbAQUSgh == true){wyTbAQUSgh = false;}
      if(uQswooKIQb == true){uQswooKIQb = false;}
      if(IdnoiGWRWU == true){IdnoiGWRWU = false;}
      if(eFbLWhIOzb == true){eFbLWhIOzb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AFSHQXMPHM
{ 
  void mHfpafxsmY()
  { 
      bool GqWDLjszBC = false;
      bool JOiZEUNWwn = false;
      bool rmGHFCKIRo = false;
      bool tkLcSyywRO = false;
      bool zbeExiKLGu = false;
      bool NByCuSkOyJ = false;
      bool YkgLIXCGGG = false;
      bool WQEhoPIBKW = false;
      bool ryBWbsmIgz = false;
      bool MiyIoNtTwY = false;
      bool fEFzXwwQNe = false;
      bool KiEbQZjJjO = false;
      bool ktYGsmSurb = false;
      bool VoFkpnsBzf = false;
      bool wVuBnddVrO = false;
      bool djignleyGj = false;
      bool cAXlJVdTkc = false;
      bool ghKESOyWRP = false;
      bool JwDdykFXxE = false;
      bool IuuOCuyJrS = false;
      string SqjrGJxBNd;
      string uWcLXPkesW;
      string DFFGQiBedP;
      string OohqAdYbxG;
      string eKVlRDcjtg;
      string IDaRfNkdaX;
      string HRWxPFnkLt;
      string qJglqsiTnN;
      string FRkwHKNQKm;
      string suAZyMmYVM;
      string OqXApzVnZm;
      string dRoNRpgZpE;
      string qXZYAuIHmd;
      string FKxbyOskGH;
      string oYqXIaFmHI;
      string fNhQUqQzzt;
      string qNBugTTNPD;
      string wwTiPRgCQZ;
      string pVAdyrbfHH;
      string xskLQaXuqn;
      if(SqjrGJxBNd == OqXApzVnZm){GqWDLjszBC = true;}
      else if(OqXApzVnZm == SqjrGJxBNd){fEFzXwwQNe = true;}
      if(uWcLXPkesW == dRoNRpgZpE){JOiZEUNWwn = true;}
      else if(dRoNRpgZpE == uWcLXPkesW){KiEbQZjJjO = true;}
      if(DFFGQiBedP == qXZYAuIHmd){rmGHFCKIRo = true;}
      else if(qXZYAuIHmd == DFFGQiBedP){ktYGsmSurb = true;}
      if(OohqAdYbxG == FKxbyOskGH){tkLcSyywRO = true;}
      else if(FKxbyOskGH == OohqAdYbxG){VoFkpnsBzf = true;}
      if(eKVlRDcjtg == oYqXIaFmHI){zbeExiKLGu = true;}
      else if(oYqXIaFmHI == eKVlRDcjtg){wVuBnddVrO = true;}
      if(IDaRfNkdaX == fNhQUqQzzt){NByCuSkOyJ = true;}
      else if(fNhQUqQzzt == IDaRfNkdaX){djignleyGj = true;}
      if(HRWxPFnkLt == qNBugTTNPD){YkgLIXCGGG = true;}
      else if(qNBugTTNPD == HRWxPFnkLt){cAXlJVdTkc = true;}
      if(qJglqsiTnN == wwTiPRgCQZ){WQEhoPIBKW = true;}
      if(FRkwHKNQKm == pVAdyrbfHH){ryBWbsmIgz = true;}
      if(suAZyMmYVM == xskLQaXuqn){MiyIoNtTwY = true;}
      while(wwTiPRgCQZ == qJglqsiTnN){ghKESOyWRP = true;}
      while(pVAdyrbfHH == pVAdyrbfHH){JwDdykFXxE = true;}
      while(xskLQaXuqn == xskLQaXuqn){IuuOCuyJrS = true;}
      if(GqWDLjszBC == true){GqWDLjszBC = false;}
      if(JOiZEUNWwn == true){JOiZEUNWwn = false;}
      if(rmGHFCKIRo == true){rmGHFCKIRo = false;}
      if(tkLcSyywRO == true){tkLcSyywRO = false;}
      if(zbeExiKLGu == true){zbeExiKLGu = false;}
      if(NByCuSkOyJ == true){NByCuSkOyJ = false;}
      if(YkgLIXCGGG == true){YkgLIXCGGG = false;}
      if(WQEhoPIBKW == true){WQEhoPIBKW = false;}
      if(ryBWbsmIgz == true){ryBWbsmIgz = false;}
      if(MiyIoNtTwY == true){MiyIoNtTwY = false;}
      if(fEFzXwwQNe == true){fEFzXwwQNe = false;}
      if(KiEbQZjJjO == true){KiEbQZjJjO = false;}
      if(ktYGsmSurb == true){ktYGsmSurb = false;}
      if(VoFkpnsBzf == true){VoFkpnsBzf = false;}
      if(wVuBnddVrO == true){wVuBnddVrO = false;}
      if(djignleyGj == true){djignleyGj = false;}
      if(cAXlJVdTkc == true){cAXlJVdTkc = false;}
      if(ghKESOyWRP == true){ghKESOyWRP = false;}
      if(JwDdykFXxE == true){JwDdykFXxE = false;}
      if(IuuOCuyJrS == true){IuuOCuyJrS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUZSJFUHFS
{ 
  void QTnUtDVWjs()
  { 
      bool RmcUpsEaag = false;
      bool mXyyxndUQd = false;
      bool JlBWfRWkGY = false;
      bool qVURwTbNuo = false;
      bool hYPjNXsFaN = false;
      bool IaDnQfkGoX = false;
      bool WTUCoRCgBd = false;
      bool MPYaukVRIH = false;
      bool YQKrQQRfAQ = false;
      bool hVYWSODNtw = false;
      bool UMEwBrBcrf = false;
      bool JSxgzGIckY = false;
      bool AVfkuppBIg = false;
      bool gHXMmMLNpX = false;
      bool PomUGPYrXM = false;
      bool FacVuzfSBL = false;
      bool BzTLzCujsm = false;
      bool tulMJLhLef = false;
      bool RydwaFeBQm = false;
      bool fsMdVPUbVE = false;
      string mylBZbpQRj;
      string yLyAqikJXy;
      string jUSlgBdOiM;
      string lQhXtgKYCr;
      string khusqPKZdo;
      string NyWNURfzTY;
      string yagExhdaFJ;
      string XLHfMCZYtQ;
      string pDjtynsUCc;
      string BKEctKApuJ;
      string ljTURBpqBS;
      string rGEChtplGJ;
      string oJXcIMHdkC;
      string BidkdGjPcx;
      string yBTjjtGBuA;
      string TOjlUcLqLE;
      string tLFyQIcSXa;
      string KaJIKmpnrN;
      string GFhkhmzqQB;
      string urDYCluUSa;
      if(mylBZbpQRj == ljTURBpqBS){RmcUpsEaag = true;}
      else if(ljTURBpqBS == mylBZbpQRj){UMEwBrBcrf = true;}
      if(yLyAqikJXy == rGEChtplGJ){mXyyxndUQd = true;}
      else if(rGEChtplGJ == yLyAqikJXy){JSxgzGIckY = true;}
      if(jUSlgBdOiM == oJXcIMHdkC){JlBWfRWkGY = true;}
      else if(oJXcIMHdkC == jUSlgBdOiM){AVfkuppBIg = true;}
      if(lQhXtgKYCr == BidkdGjPcx){qVURwTbNuo = true;}
      else if(BidkdGjPcx == lQhXtgKYCr){gHXMmMLNpX = true;}
      if(khusqPKZdo == yBTjjtGBuA){hYPjNXsFaN = true;}
      else if(yBTjjtGBuA == khusqPKZdo){PomUGPYrXM = true;}
      if(NyWNURfzTY == TOjlUcLqLE){IaDnQfkGoX = true;}
      else if(TOjlUcLqLE == NyWNURfzTY){FacVuzfSBL = true;}
      if(yagExhdaFJ == tLFyQIcSXa){WTUCoRCgBd = true;}
      else if(tLFyQIcSXa == yagExhdaFJ){BzTLzCujsm = true;}
      if(XLHfMCZYtQ == KaJIKmpnrN){MPYaukVRIH = true;}
      if(pDjtynsUCc == GFhkhmzqQB){YQKrQQRfAQ = true;}
      if(BKEctKApuJ == urDYCluUSa){hVYWSODNtw = true;}
      while(KaJIKmpnrN == XLHfMCZYtQ){tulMJLhLef = true;}
      while(GFhkhmzqQB == GFhkhmzqQB){RydwaFeBQm = true;}
      while(urDYCluUSa == urDYCluUSa){fsMdVPUbVE = true;}
      if(RmcUpsEaag == true){RmcUpsEaag = false;}
      if(mXyyxndUQd == true){mXyyxndUQd = false;}
      if(JlBWfRWkGY == true){JlBWfRWkGY = false;}
      if(qVURwTbNuo == true){qVURwTbNuo = false;}
      if(hYPjNXsFaN == true){hYPjNXsFaN = false;}
      if(IaDnQfkGoX == true){IaDnQfkGoX = false;}
      if(WTUCoRCgBd == true){WTUCoRCgBd = false;}
      if(MPYaukVRIH == true){MPYaukVRIH = false;}
      if(YQKrQQRfAQ == true){YQKrQQRfAQ = false;}
      if(hVYWSODNtw == true){hVYWSODNtw = false;}
      if(UMEwBrBcrf == true){UMEwBrBcrf = false;}
      if(JSxgzGIckY == true){JSxgzGIckY = false;}
      if(AVfkuppBIg == true){AVfkuppBIg = false;}
      if(gHXMmMLNpX == true){gHXMmMLNpX = false;}
      if(PomUGPYrXM == true){PomUGPYrXM = false;}
      if(FacVuzfSBL == true){FacVuzfSBL = false;}
      if(BzTLzCujsm == true){BzTLzCujsm = false;}
      if(tulMJLhLef == true){tulMJLhLef = false;}
      if(RydwaFeBQm == true){RydwaFeBQm = false;}
      if(fsMdVPUbVE == true){fsMdVPUbVE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONPNZYWLDK
{ 
  void NAzTuEoiqN()
  { 
      bool gAKunfKbwr = false;
      bool FVpDYownHe = false;
      bool wPYrBgHoWH = false;
      bool CJutYgNsbM = false;
      bool MmtiODfLQe = false;
      bool HTgRIQbSsG = false;
      bool XVFoowZweq = false;
      bool aCLuSJUocy = false;
      bool BuYqAhbckH = false;
      bool FtzUnqgFtR = false;
      bool cjgYDEIkzz = false;
      bool ulouFbwNnG = false;
      bool TwKWlgCqHa = false;
      bool bPuLURNznu = false;
      bool ZpdlLSEEPL = false;
      bool tSQmxfYKlW = false;
      bool CRdXWfpdZn = false;
      bool NxZsfdSYKS = false;
      bool bxbufJyHNo = false;
      bool rDMQrIMFPf = false;
      string tHNiUdsNYF;
      string ABczugSjEV;
      string ScudgMxTwI;
      string WDcRZGQLpn;
      string YkFoXPSeqH;
      string QncrzQLjCH;
      string gYRPhxXLZn;
      string PGsQwhXFFQ;
      string tRboriZkRJ;
      string tfJiHATpGa;
      string qHFDqKuMuR;
      string sGelNPwcXz;
      string XmsPtjwKIu;
      string OgzdYmLYxg;
      string nMoAQnBXVr;
      string DpSHDENoJH;
      string NjEADLGAMZ;
      string DXepKKyrzF;
      string hYnQrXOqaU;
      string YVPpTDIoxF;
      if(tHNiUdsNYF == qHFDqKuMuR){gAKunfKbwr = true;}
      else if(qHFDqKuMuR == tHNiUdsNYF){cjgYDEIkzz = true;}
      if(ABczugSjEV == sGelNPwcXz){FVpDYownHe = true;}
      else if(sGelNPwcXz == ABczugSjEV){ulouFbwNnG = true;}
      if(ScudgMxTwI == XmsPtjwKIu){wPYrBgHoWH = true;}
      else if(XmsPtjwKIu == ScudgMxTwI){TwKWlgCqHa = true;}
      if(WDcRZGQLpn == OgzdYmLYxg){CJutYgNsbM = true;}
      else if(OgzdYmLYxg == WDcRZGQLpn){bPuLURNznu = true;}
      if(YkFoXPSeqH == nMoAQnBXVr){MmtiODfLQe = true;}
      else if(nMoAQnBXVr == YkFoXPSeqH){ZpdlLSEEPL = true;}
      if(QncrzQLjCH == DpSHDENoJH){HTgRIQbSsG = true;}
      else if(DpSHDENoJH == QncrzQLjCH){tSQmxfYKlW = true;}
      if(gYRPhxXLZn == NjEADLGAMZ){XVFoowZweq = true;}
      else if(NjEADLGAMZ == gYRPhxXLZn){CRdXWfpdZn = true;}
      if(PGsQwhXFFQ == DXepKKyrzF){aCLuSJUocy = true;}
      if(tRboriZkRJ == hYnQrXOqaU){BuYqAhbckH = true;}
      if(tfJiHATpGa == YVPpTDIoxF){FtzUnqgFtR = true;}
      while(DXepKKyrzF == PGsQwhXFFQ){NxZsfdSYKS = true;}
      while(hYnQrXOqaU == hYnQrXOqaU){bxbufJyHNo = true;}
      while(YVPpTDIoxF == YVPpTDIoxF){rDMQrIMFPf = true;}
      if(gAKunfKbwr == true){gAKunfKbwr = false;}
      if(FVpDYownHe == true){FVpDYownHe = false;}
      if(wPYrBgHoWH == true){wPYrBgHoWH = false;}
      if(CJutYgNsbM == true){CJutYgNsbM = false;}
      if(MmtiODfLQe == true){MmtiODfLQe = false;}
      if(HTgRIQbSsG == true){HTgRIQbSsG = false;}
      if(XVFoowZweq == true){XVFoowZweq = false;}
      if(aCLuSJUocy == true){aCLuSJUocy = false;}
      if(BuYqAhbckH == true){BuYqAhbckH = false;}
      if(FtzUnqgFtR == true){FtzUnqgFtR = false;}
      if(cjgYDEIkzz == true){cjgYDEIkzz = false;}
      if(ulouFbwNnG == true){ulouFbwNnG = false;}
      if(TwKWlgCqHa == true){TwKWlgCqHa = false;}
      if(bPuLURNznu == true){bPuLURNznu = false;}
      if(ZpdlLSEEPL == true){ZpdlLSEEPL = false;}
      if(tSQmxfYKlW == true){tSQmxfYKlW = false;}
      if(CRdXWfpdZn == true){CRdXWfpdZn = false;}
      if(NxZsfdSYKS == true){NxZsfdSYKS = false;}
      if(bxbufJyHNo == true){bxbufJyHNo = false;}
      if(rDMQrIMFPf == true){rDMQrIMFPf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJVCNYUIEW
{ 
  void EyABhPfRTe()
  { 
      bool WBzFKhNWYF = false;
      bool OBofbggqAF = false;
      bool gntRorzIpF = false;
      bool AlfTjefjOl = false;
      bool EpIeXVCnQh = false;
      bool zwRmxiGhQR = false;
      bool hFfTEbUUwx = false;
      bool BxcNApfPsT = false;
      bool pKqHFETsVB = false;
      bool XxTxDzKnZu = false;
      bool BgrSgBTElG = false;
      bool DqnxaXNYNA = false;
      bool IbytYDdeJB = false;
      bool fqoyRJRYaE = false;
      bool jOGPygJWWf = false;
      bool kkaYmZhxtc = false;
      bool WnujZLBpeR = false;
      bool FoxJQsUiwr = false;
      bool tHIcQtQQKr = false;
      bool bUdxguTWol = false;
      string GkKTSqSUQg;
      string jonfaQdqpD;
      string pTZkurlsuK;
      string FBTaxSNjEN;
      string DqReUfduwX;
      string nTMpEmKYYZ;
      string FYZFbhUMiI;
      string CsmbAyCuPP;
      string OqwWWkocWK;
      string HoLdIdRLCl;
      string KQLnVtfjpF;
      string kOIIKOcCiq;
      string sqpXAMhITV;
      string gpsdFyeIBb;
      string EEmQZsfCSt;
      string BOcLsSannI;
      string MXQUXtVeDM;
      string jTBGlnEYyH;
      string fepYTSMgjl;
      string XqUrPgnSre;
      if(GkKTSqSUQg == KQLnVtfjpF){WBzFKhNWYF = true;}
      else if(KQLnVtfjpF == GkKTSqSUQg){BgrSgBTElG = true;}
      if(jonfaQdqpD == kOIIKOcCiq){OBofbggqAF = true;}
      else if(kOIIKOcCiq == jonfaQdqpD){DqnxaXNYNA = true;}
      if(pTZkurlsuK == sqpXAMhITV){gntRorzIpF = true;}
      else if(sqpXAMhITV == pTZkurlsuK){IbytYDdeJB = true;}
      if(FBTaxSNjEN == gpsdFyeIBb){AlfTjefjOl = true;}
      else if(gpsdFyeIBb == FBTaxSNjEN){fqoyRJRYaE = true;}
      if(DqReUfduwX == EEmQZsfCSt){EpIeXVCnQh = true;}
      else if(EEmQZsfCSt == DqReUfduwX){jOGPygJWWf = true;}
      if(nTMpEmKYYZ == BOcLsSannI){zwRmxiGhQR = true;}
      else if(BOcLsSannI == nTMpEmKYYZ){kkaYmZhxtc = true;}
      if(FYZFbhUMiI == MXQUXtVeDM){hFfTEbUUwx = true;}
      else if(MXQUXtVeDM == FYZFbhUMiI){WnujZLBpeR = true;}
      if(CsmbAyCuPP == jTBGlnEYyH){BxcNApfPsT = true;}
      if(OqwWWkocWK == fepYTSMgjl){pKqHFETsVB = true;}
      if(HoLdIdRLCl == XqUrPgnSre){XxTxDzKnZu = true;}
      while(jTBGlnEYyH == CsmbAyCuPP){FoxJQsUiwr = true;}
      while(fepYTSMgjl == fepYTSMgjl){tHIcQtQQKr = true;}
      while(XqUrPgnSre == XqUrPgnSre){bUdxguTWol = true;}
      if(WBzFKhNWYF == true){WBzFKhNWYF = false;}
      if(OBofbggqAF == true){OBofbggqAF = false;}
      if(gntRorzIpF == true){gntRorzIpF = false;}
      if(AlfTjefjOl == true){AlfTjefjOl = false;}
      if(EpIeXVCnQh == true){EpIeXVCnQh = false;}
      if(zwRmxiGhQR == true){zwRmxiGhQR = false;}
      if(hFfTEbUUwx == true){hFfTEbUUwx = false;}
      if(BxcNApfPsT == true){BxcNApfPsT = false;}
      if(pKqHFETsVB == true){pKqHFETsVB = false;}
      if(XxTxDzKnZu == true){XxTxDzKnZu = false;}
      if(BgrSgBTElG == true){BgrSgBTElG = false;}
      if(DqnxaXNYNA == true){DqnxaXNYNA = false;}
      if(IbytYDdeJB == true){IbytYDdeJB = false;}
      if(fqoyRJRYaE == true){fqoyRJRYaE = false;}
      if(jOGPygJWWf == true){jOGPygJWWf = false;}
      if(kkaYmZhxtc == true){kkaYmZhxtc = false;}
      if(WnujZLBpeR == true){WnujZLBpeR = false;}
      if(FoxJQsUiwr == true){FoxJQsUiwr = false;}
      if(tHIcQtQQKr == true){tHIcQtQQKr = false;}
      if(bUdxguTWol == true){bUdxguTWol = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENARWPJLNK
{ 
  void PYLkTirctU()
  { 
      bool UgAQMcrxWf = false;
      bool TBTIqUpGYQ = false;
      bool OfAhJQmqZN = false;
      bool ZGsDTaRySH = false;
      bool tLshZdBlNm = false;
      bool GZNyznfRGw = false;
      bool pAXJGNHPnQ = false;
      bool DqmQVDlRIf = false;
      bool OBclGzsuEf = false;
      bool tzrVRtnjbM = false;
      bool VlxxjPlxbw = false;
      bool BNJahnWkCG = false;
      bool TMKIVDzQyb = false;
      bool OCpuJcDfBq = false;
      bool NwSIdfpRnd = false;
      bool WChUsJaoag = false;
      bool QUyAgzXOQF = false;
      bool jqjKsXsCdp = false;
      bool NhcUFMTVCz = false;
      bool BNETarxSae = false;
      string eUCzrkxZcx;
      string bjNUbARyBs;
      string IQdbEkuZUV;
      string IUrpOFlIrg;
      string JsRjQtJxbP;
      string qflosNpatH;
      string pXEHoGrXGW;
      string OJGUiPztKK;
      string bxxEdbiCwB;
      string OLNkplnJuJ;
      string CkqFBhZQGd;
      string NwPjerZzdM;
      string XoaFHDuUdw;
      string aozAHpGrDu;
      string CRwSmSucFy;
      string LnfhlNKlxy;
      string mFlJDYxOco;
      string khwhKFsISo;
      string HROfklJQOt;
      string fUtEIxflOO;
      if(eUCzrkxZcx == CkqFBhZQGd){UgAQMcrxWf = true;}
      else if(CkqFBhZQGd == eUCzrkxZcx){VlxxjPlxbw = true;}
      if(bjNUbARyBs == NwPjerZzdM){TBTIqUpGYQ = true;}
      else if(NwPjerZzdM == bjNUbARyBs){BNJahnWkCG = true;}
      if(IQdbEkuZUV == XoaFHDuUdw){OfAhJQmqZN = true;}
      else if(XoaFHDuUdw == IQdbEkuZUV){TMKIVDzQyb = true;}
      if(IUrpOFlIrg == aozAHpGrDu){ZGsDTaRySH = true;}
      else if(aozAHpGrDu == IUrpOFlIrg){OCpuJcDfBq = true;}
      if(JsRjQtJxbP == CRwSmSucFy){tLshZdBlNm = true;}
      else if(CRwSmSucFy == JsRjQtJxbP){NwSIdfpRnd = true;}
      if(qflosNpatH == LnfhlNKlxy){GZNyznfRGw = true;}
      else if(LnfhlNKlxy == qflosNpatH){WChUsJaoag = true;}
      if(pXEHoGrXGW == mFlJDYxOco){pAXJGNHPnQ = true;}
      else if(mFlJDYxOco == pXEHoGrXGW){QUyAgzXOQF = true;}
      if(OJGUiPztKK == khwhKFsISo){DqmQVDlRIf = true;}
      if(bxxEdbiCwB == HROfklJQOt){OBclGzsuEf = true;}
      if(OLNkplnJuJ == fUtEIxflOO){tzrVRtnjbM = true;}
      while(khwhKFsISo == OJGUiPztKK){jqjKsXsCdp = true;}
      while(HROfklJQOt == HROfklJQOt){NhcUFMTVCz = true;}
      while(fUtEIxflOO == fUtEIxflOO){BNETarxSae = true;}
      if(UgAQMcrxWf == true){UgAQMcrxWf = false;}
      if(TBTIqUpGYQ == true){TBTIqUpGYQ = false;}
      if(OfAhJQmqZN == true){OfAhJQmqZN = false;}
      if(ZGsDTaRySH == true){ZGsDTaRySH = false;}
      if(tLshZdBlNm == true){tLshZdBlNm = false;}
      if(GZNyznfRGw == true){GZNyznfRGw = false;}
      if(pAXJGNHPnQ == true){pAXJGNHPnQ = false;}
      if(DqmQVDlRIf == true){DqmQVDlRIf = false;}
      if(OBclGzsuEf == true){OBclGzsuEf = false;}
      if(tzrVRtnjbM == true){tzrVRtnjbM = false;}
      if(VlxxjPlxbw == true){VlxxjPlxbw = false;}
      if(BNJahnWkCG == true){BNJahnWkCG = false;}
      if(TMKIVDzQyb == true){TMKIVDzQyb = false;}
      if(OCpuJcDfBq == true){OCpuJcDfBq = false;}
      if(NwSIdfpRnd == true){NwSIdfpRnd = false;}
      if(WChUsJaoag == true){WChUsJaoag = false;}
      if(QUyAgzXOQF == true){QUyAgzXOQF = false;}
      if(jqjKsXsCdp == true){jqjKsXsCdp = false;}
      if(NhcUFMTVCz == true){NhcUFMTVCz = false;}
      if(BNETarxSae == true){BNETarxSae = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXSNUGUMSA
{ 
  void QAYCPHCopK()
  { 
      bool NOlixPHILh = false;
      bool AYWZpRChPr = false;
      bool uxEuphKUKc = false;
      bool EnincqXwDm = false;
      bool hmGXmxDCeg = false;
      bool SLYffQJpsP = false;
      bool FlxhcLoiwy = false;
      bool sFdcKHpgHr = false;
      bool dHpcKrODHM = false;
      bool ggCnguoXtb = false;
      bool HUFfnMgwVY = false;
      bool ZciAkxwUXj = false;
      bool wlajQLDpuO = false;
      bool RSmfjJCKoy = false;
      bool LShhmEyBCj = false;
      bool zUzJeVsVOc = false;
      bool IpBGGGoCPa = false;
      bool uleZYdErwL = false;
      bool MBmLPwScAO = false;
      bool QguLoURaaf = false;
      string ErhtNDPdCZ;
      string iJiyoJAYEk;
      string CiMtMsEEZl;
      string MnspsAIBhY;
      string uJSYBfqYYe;
      string FAVNNVfngT;
      string zLDQNtQrFn;
      string BzpforQnrg;
      string CeeugMSecX;
      string UUUNYjFCKH;
      string PyTkcGJpXU;
      string FruARTgIjA;
      string akPgTfebGF;
      string mNckRELtRZ;
      string CcHHRcYUwF;
      string CxRKfdhlQx;
      string bhiShqPKhM;
      string HmpJyydIOq;
      string GJfBCowSFm;
      string WZcUyUsoYa;
      if(ErhtNDPdCZ == PyTkcGJpXU){NOlixPHILh = true;}
      else if(PyTkcGJpXU == ErhtNDPdCZ){HUFfnMgwVY = true;}
      if(iJiyoJAYEk == FruARTgIjA){AYWZpRChPr = true;}
      else if(FruARTgIjA == iJiyoJAYEk){ZciAkxwUXj = true;}
      if(CiMtMsEEZl == akPgTfebGF){uxEuphKUKc = true;}
      else if(akPgTfebGF == CiMtMsEEZl){wlajQLDpuO = true;}
      if(MnspsAIBhY == mNckRELtRZ){EnincqXwDm = true;}
      else if(mNckRELtRZ == MnspsAIBhY){RSmfjJCKoy = true;}
      if(uJSYBfqYYe == CcHHRcYUwF){hmGXmxDCeg = true;}
      else if(CcHHRcYUwF == uJSYBfqYYe){LShhmEyBCj = true;}
      if(FAVNNVfngT == CxRKfdhlQx){SLYffQJpsP = true;}
      else if(CxRKfdhlQx == FAVNNVfngT){zUzJeVsVOc = true;}
      if(zLDQNtQrFn == bhiShqPKhM){FlxhcLoiwy = true;}
      else if(bhiShqPKhM == zLDQNtQrFn){IpBGGGoCPa = true;}
      if(BzpforQnrg == HmpJyydIOq){sFdcKHpgHr = true;}
      if(CeeugMSecX == GJfBCowSFm){dHpcKrODHM = true;}
      if(UUUNYjFCKH == WZcUyUsoYa){ggCnguoXtb = true;}
      while(HmpJyydIOq == BzpforQnrg){uleZYdErwL = true;}
      while(GJfBCowSFm == GJfBCowSFm){MBmLPwScAO = true;}
      while(WZcUyUsoYa == WZcUyUsoYa){QguLoURaaf = true;}
      if(NOlixPHILh == true){NOlixPHILh = false;}
      if(AYWZpRChPr == true){AYWZpRChPr = false;}
      if(uxEuphKUKc == true){uxEuphKUKc = false;}
      if(EnincqXwDm == true){EnincqXwDm = false;}
      if(hmGXmxDCeg == true){hmGXmxDCeg = false;}
      if(SLYffQJpsP == true){SLYffQJpsP = false;}
      if(FlxhcLoiwy == true){FlxhcLoiwy = false;}
      if(sFdcKHpgHr == true){sFdcKHpgHr = false;}
      if(dHpcKrODHM == true){dHpcKrODHM = false;}
      if(ggCnguoXtb == true){ggCnguoXtb = false;}
      if(HUFfnMgwVY == true){HUFfnMgwVY = false;}
      if(ZciAkxwUXj == true){ZciAkxwUXj = false;}
      if(wlajQLDpuO == true){wlajQLDpuO = false;}
      if(RSmfjJCKoy == true){RSmfjJCKoy = false;}
      if(LShhmEyBCj == true){LShhmEyBCj = false;}
      if(zUzJeVsVOc == true){zUzJeVsVOc = false;}
      if(IpBGGGoCPa == true){IpBGGGoCPa = false;}
      if(uleZYdErwL == true){uleZYdErwL = false;}
      if(MBmLPwScAO == true){MBmLPwScAO = false;}
      if(QguLoURaaf == true){QguLoURaaf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSSEOGCYBK
{ 
  void KzKylcSrMg()
  { 
      bool qEUTWZbzCs = false;
      bool JKnkgAzIsl = false;
      bool pcJseoDkqD = false;
      bool UBdjHjjwdT = false;
      bool WUFSbQMDXV = false;
      bool sVqptOubog = false;
      bool VqHzYHfDcw = false;
      bool QDeYOUWqRO = false;
      bool czNVJzKmps = false;
      bool oHGwyfMGsU = false;
      bool jIaaEppRaY = false;
      bool qDJaDWcloZ = false;
      bool wsMiHIwhai = false;
      bool IPxxdTYlQT = false;
      bool IrLQCkyfra = false;
      bool CZRTXquqTw = false;
      bool sHqrPbGMwj = false;
      bool xpVUQDgwgV = false;
      bool KPozfhydYm = false;
      bool XgSTaAATAa = false;
      string zBeMVsAIqL;
      string BrEUemVOTe;
      string WUsPRuKxZN;
      string nEOVReSFzt;
      string kThddhSbLJ;
      string aWtsFeIOuZ;
      string hCicXxdiCz;
      string UPPYtClOlj;
      string bikQmQJVPm;
      string WDKYLhkEGf;
      string DjYMnKHVyC;
      string rtbKyzQSpG;
      string mISPbQEqML;
      string RhIFfrJYbb;
      string JnWMtcazaM;
      string RSNzsuQJjW;
      string FPJmkKkVeG;
      string prpNxzlGUz;
      string oFQAtzTIMk;
      string aAnEWsejbj;
      if(zBeMVsAIqL == DjYMnKHVyC){qEUTWZbzCs = true;}
      else if(DjYMnKHVyC == zBeMVsAIqL){jIaaEppRaY = true;}
      if(BrEUemVOTe == rtbKyzQSpG){JKnkgAzIsl = true;}
      else if(rtbKyzQSpG == BrEUemVOTe){qDJaDWcloZ = true;}
      if(WUsPRuKxZN == mISPbQEqML){pcJseoDkqD = true;}
      else if(mISPbQEqML == WUsPRuKxZN){wsMiHIwhai = true;}
      if(nEOVReSFzt == RhIFfrJYbb){UBdjHjjwdT = true;}
      else if(RhIFfrJYbb == nEOVReSFzt){IPxxdTYlQT = true;}
      if(kThddhSbLJ == JnWMtcazaM){WUFSbQMDXV = true;}
      else if(JnWMtcazaM == kThddhSbLJ){IrLQCkyfra = true;}
      if(aWtsFeIOuZ == RSNzsuQJjW){sVqptOubog = true;}
      else if(RSNzsuQJjW == aWtsFeIOuZ){CZRTXquqTw = true;}
      if(hCicXxdiCz == FPJmkKkVeG){VqHzYHfDcw = true;}
      else if(FPJmkKkVeG == hCicXxdiCz){sHqrPbGMwj = true;}
      if(UPPYtClOlj == prpNxzlGUz){QDeYOUWqRO = true;}
      if(bikQmQJVPm == oFQAtzTIMk){czNVJzKmps = true;}
      if(WDKYLhkEGf == aAnEWsejbj){oHGwyfMGsU = true;}
      while(prpNxzlGUz == UPPYtClOlj){xpVUQDgwgV = true;}
      while(oFQAtzTIMk == oFQAtzTIMk){KPozfhydYm = true;}
      while(aAnEWsejbj == aAnEWsejbj){XgSTaAATAa = true;}
      if(qEUTWZbzCs == true){qEUTWZbzCs = false;}
      if(JKnkgAzIsl == true){JKnkgAzIsl = false;}
      if(pcJseoDkqD == true){pcJseoDkqD = false;}
      if(UBdjHjjwdT == true){UBdjHjjwdT = false;}
      if(WUFSbQMDXV == true){WUFSbQMDXV = false;}
      if(sVqptOubog == true){sVqptOubog = false;}
      if(VqHzYHfDcw == true){VqHzYHfDcw = false;}
      if(QDeYOUWqRO == true){QDeYOUWqRO = false;}
      if(czNVJzKmps == true){czNVJzKmps = false;}
      if(oHGwyfMGsU == true){oHGwyfMGsU = false;}
      if(jIaaEppRaY == true){jIaaEppRaY = false;}
      if(qDJaDWcloZ == true){qDJaDWcloZ = false;}
      if(wsMiHIwhai == true){wsMiHIwhai = false;}
      if(IPxxdTYlQT == true){IPxxdTYlQT = false;}
      if(IrLQCkyfra == true){IrLQCkyfra = false;}
      if(CZRTXquqTw == true){CZRTXquqTw = false;}
      if(sHqrPbGMwj == true){sHqrPbGMwj = false;}
      if(xpVUQDgwgV == true){xpVUQDgwgV = false;}
      if(KPozfhydYm == true){KPozfhydYm = false;}
      if(XgSTaAATAa == true){XgSTaAATAa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QJPGGCKJJF
{ 
  void hbiLyIPBqh()
  { 
      bool ccMcAWQgjR = false;
      bool oDNzjTTYdG = false;
      bool hLIQxWCrrU = false;
      bool EEFagOWgHw = false;
      bool nYOczNDMcp = false;
      bool MmtFmRTued = false;
      bool TXnOMjxlSV = false;
      bool xmQgRIwfQj = false;
      bool ToOCHRJAmP = false;
      bool taBdbPkzPO = false;
      bool PQtHsZVNne = false;
      bool UneuJeJlHu = false;
      bool ZxyDaVkmEB = false;
      bool XwPBTDuHIh = false;
      bool uwMItFwFTx = false;
      bool GyrToSRqfW = false;
      bool niIlGXXcaG = false;
      bool iCcYAdjpIU = false;
      bool YeSHtYEwMB = false;
      bool lEaksLnZCW = false;
      string zNQpEznJmQ;
      string pWiDzKqmDS;
      string ochHHFwWaC;
      string PEBkKPWMrE;
      string oykzhkIHql;
      string iZdebVfIiy;
      string CRijBlUxsi;
      string meuzcpqiZW;
      string xoenSoZWIn;
      string jOdsCXPBxu;
      string PKOIzEeeBl;
      string ewhLBNltQL;
      string LxoFyXBBxE;
      string apkdGmZWoO;
      string JtUWJnfRrn;
      string lVjliRVJJb;
      string DchwLnKDFO;
      string mOFCBRcRuK;
      string qiJISEGzuo;
      string QQMNKgMXLU;
      if(zNQpEznJmQ == PKOIzEeeBl){ccMcAWQgjR = true;}
      else if(PKOIzEeeBl == zNQpEznJmQ){PQtHsZVNne = true;}
      if(pWiDzKqmDS == ewhLBNltQL){oDNzjTTYdG = true;}
      else if(ewhLBNltQL == pWiDzKqmDS){UneuJeJlHu = true;}
      if(ochHHFwWaC == LxoFyXBBxE){hLIQxWCrrU = true;}
      else if(LxoFyXBBxE == ochHHFwWaC){ZxyDaVkmEB = true;}
      if(PEBkKPWMrE == apkdGmZWoO){EEFagOWgHw = true;}
      else if(apkdGmZWoO == PEBkKPWMrE){XwPBTDuHIh = true;}
      if(oykzhkIHql == JtUWJnfRrn){nYOczNDMcp = true;}
      else if(JtUWJnfRrn == oykzhkIHql){uwMItFwFTx = true;}
      if(iZdebVfIiy == lVjliRVJJb){MmtFmRTued = true;}
      else if(lVjliRVJJb == iZdebVfIiy){GyrToSRqfW = true;}
      if(CRijBlUxsi == DchwLnKDFO){TXnOMjxlSV = true;}
      else if(DchwLnKDFO == CRijBlUxsi){niIlGXXcaG = true;}
      if(meuzcpqiZW == mOFCBRcRuK){xmQgRIwfQj = true;}
      if(xoenSoZWIn == qiJISEGzuo){ToOCHRJAmP = true;}
      if(jOdsCXPBxu == QQMNKgMXLU){taBdbPkzPO = true;}
      while(mOFCBRcRuK == meuzcpqiZW){iCcYAdjpIU = true;}
      while(qiJISEGzuo == qiJISEGzuo){YeSHtYEwMB = true;}
      while(QQMNKgMXLU == QQMNKgMXLU){lEaksLnZCW = true;}
      if(ccMcAWQgjR == true){ccMcAWQgjR = false;}
      if(oDNzjTTYdG == true){oDNzjTTYdG = false;}
      if(hLIQxWCrrU == true){hLIQxWCrrU = false;}
      if(EEFagOWgHw == true){EEFagOWgHw = false;}
      if(nYOczNDMcp == true){nYOczNDMcp = false;}
      if(MmtFmRTued == true){MmtFmRTued = false;}
      if(TXnOMjxlSV == true){TXnOMjxlSV = false;}
      if(xmQgRIwfQj == true){xmQgRIwfQj = false;}
      if(ToOCHRJAmP == true){ToOCHRJAmP = false;}
      if(taBdbPkzPO == true){taBdbPkzPO = false;}
      if(PQtHsZVNne == true){PQtHsZVNne = false;}
      if(UneuJeJlHu == true){UneuJeJlHu = false;}
      if(ZxyDaVkmEB == true){ZxyDaVkmEB = false;}
      if(XwPBTDuHIh == true){XwPBTDuHIh = false;}
      if(uwMItFwFTx == true){uwMItFwFTx = false;}
      if(GyrToSRqfW == true){GyrToSRqfW = false;}
      if(niIlGXXcaG == true){niIlGXXcaG = false;}
      if(iCcYAdjpIU == true){iCcYAdjpIU = false;}
      if(YeSHtYEwMB == true){YeSHtYEwMB = false;}
      if(lEaksLnZCW == true){lEaksLnZCW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPKHJYGENX
{ 
  void YIyjCKCgYG()
  { 
      bool NTNTOcSTfn = false;
      bool mcfQKAWesJ = false;
      bool dgABHehHJC = false;
      bool BLWxXbNXfB = false;
      bool TrrjHYwxMe = false;
      bool AMBjrgSMMi = false;
      bool tKJdmbFhsi = false;
      bool myzrpknQti = false;
      bool ikueBnJlFq = false;
      bool IBLwGIiNxe = false;
      bool SODcqBNJtG = false;
      bool rBRcAJOdcy = false;
      bool SSbCZllDlg = false;
      bool CaTOPUgRnz = false;
      bool aAryyGiiuw = false;
      bool sEkyMzlBDF = false;
      bool OKWMEQhDNf = false;
      bool cwpcWSadDS = false;
      bool DDHpnxpUCP = false;
      bool heOhkQcesg = false;
      string keAulpRGhu;
      string CdcRoRYmaH;
      string XyyTziwicQ;
      string KdJuLiEqjB;
      string ThWCSojmMG;
      string umSOWmffuD;
      string shcRjXUgGG;
      string MgCZnoawAJ;
      string yJVVUXLtYY;
      string CYugHkEFRt;
      string UDgGtNkrag;
      string LiekEjLGwM;
      string MZIgDnlURD;
      string jVdGoubPbH;
      string mSSqMSsKcW;
      string YxIFhttACF;
      string bPZXwpFYwI;
      string HweoZsGRTk;
      string uarudmMYXt;
      string BbNWeWrutV;
      if(keAulpRGhu == UDgGtNkrag){NTNTOcSTfn = true;}
      else if(UDgGtNkrag == keAulpRGhu){SODcqBNJtG = true;}
      if(CdcRoRYmaH == LiekEjLGwM){mcfQKAWesJ = true;}
      else if(LiekEjLGwM == CdcRoRYmaH){rBRcAJOdcy = true;}
      if(XyyTziwicQ == MZIgDnlURD){dgABHehHJC = true;}
      else if(MZIgDnlURD == XyyTziwicQ){SSbCZllDlg = true;}
      if(KdJuLiEqjB == jVdGoubPbH){BLWxXbNXfB = true;}
      else if(jVdGoubPbH == KdJuLiEqjB){CaTOPUgRnz = true;}
      if(ThWCSojmMG == mSSqMSsKcW){TrrjHYwxMe = true;}
      else if(mSSqMSsKcW == ThWCSojmMG){aAryyGiiuw = true;}
      if(umSOWmffuD == YxIFhttACF){AMBjrgSMMi = true;}
      else if(YxIFhttACF == umSOWmffuD){sEkyMzlBDF = true;}
      if(shcRjXUgGG == bPZXwpFYwI){tKJdmbFhsi = true;}
      else if(bPZXwpFYwI == shcRjXUgGG){OKWMEQhDNf = true;}
      if(MgCZnoawAJ == HweoZsGRTk){myzrpknQti = true;}
      if(yJVVUXLtYY == uarudmMYXt){ikueBnJlFq = true;}
      if(CYugHkEFRt == BbNWeWrutV){IBLwGIiNxe = true;}
      while(HweoZsGRTk == MgCZnoawAJ){cwpcWSadDS = true;}
      while(uarudmMYXt == uarudmMYXt){DDHpnxpUCP = true;}
      while(BbNWeWrutV == BbNWeWrutV){heOhkQcesg = true;}
      if(NTNTOcSTfn == true){NTNTOcSTfn = false;}
      if(mcfQKAWesJ == true){mcfQKAWesJ = false;}
      if(dgABHehHJC == true){dgABHehHJC = false;}
      if(BLWxXbNXfB == true){BLWxXbNXfB = false;}
      if(TrrjHYwxMe == true){TrrjHYwxMe = false;}
      if(AMBjrgSMMi == true){AMBjrgSMMi = false;}
      if(tKJdmbFhsi == true){tKJdmbFhsi = false;}
      if(myzrpknQti == true){myzrpknQti = false;}
      if(ikueBnJlFq == true){ikueBnJlFq = false;}
      if(IBLwGIiNxe == true){IBLwGIiNxe = false;}
      if(SODcqBNJtG == true){SODcqBNJtG = false;}
      if(rBRcAJOdcy == true){rBRcAJOdcy = false;}
      if(SSbCZllDlg == true){SSbCZllDlg = false;}
      if(CaTOPUgRnz == true){CaTOPUgRnz = false;}
      if(aAryyGiiuw == true){aAryyGiiuw = false;}
      if(sEkyMzlBDF == true){sEkyMzlBDF = false;}
      if(OKWMEQhDNf == true){OKWMEQhDNf = false;}
      if(cwpcWSadDS == true){cwpcWSadDS = false;}
      if(DDHpnxpUCP == true){DDHpnxpUCP = false;}
      if(heOhkQcesg == true){heOhkQcesg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULGHEUZDPU
{ 
  void EPoearOeeG()
  { 
      bool wDjcoKrKqn = false;
      bool rElnTsWrjl = false;
      bool BcCGgJWKlY = false;
      bool AKAlGWfOjf = false;
      bool XeyfTDbOpu = false;
      bool dYqMkSBcuf = false;
      bool mhXSmhEAhx = false;
      bool MIIDNWdVmc = false;
      bool hHTptaTmBm = false;
      bool VCSEspGesl = false;
      bool zagshVQmzN = false;
      bool nepRyeNgXM = false;
      bool OQztbJoDKX = false;
      bool PzcBdGaaIX = false;
      bool KfnmypMAGN = false;
      bool bYHgXhblQX = false;
      bool gMbaxoConq = false;
      bool ElYABhcLwk = false;
      bool xnxxwqrwcw = false;
      bool enJjqxDMoI = false;
      string JFaiYhjDmY;
      string qYRErnNOqC;
      string iBKpQFzPbl;
      string qwhhEkLfls;
      string XQNrEHnMPZ;
      string KBEfzHtkSS;
      string iTbBgtpizH;
      string cgcydSnSkI;
      string QlACboqChx;
      string paNSKDnLKJ;
      string REMHwcYGBg;
      string TazKBwSZZr;
      string DmACRCTJma;
      string dbIbqLYsFy;
      string QkBBdOaDRN;
      string jNlSGdEKpt;
      string JOSZCqSXSo;
      string XZUaaSlzXC;
      string aPqZpQopUM;
      string HNCKoBRazl;
      if(JFaiYhjDmY == REMHwcYGBg){wDjcoKrKqn = true;}
      else if(REMHwcYGBg == JFaiYhjDmY){zagshVQmzN = true;}
      if(qYRErnNOqC == TazKBwSZZr){rElnTsWrjl = true;}
      else if(TazKBwSZZr == qYRErnNOqC){nepRyeNgXM = true;}
      if(iBKpQFzPbl == DmACRCTJma){BcCGgJWKlY = true;}
      else if(DmACRCTJma == iBKpQFzPbl){OQztbJoDKX = true;}
      if(qwhhEkLfls == dbIbqLYsFy){AKAlGWfOjf = true;}
      else if(dbIbqLYsFy == qwhhEkLfls){PzcBdGaaIX = true;}
      if(XQNrEHnMPZ == QkBBdOaDRN){XeyfTDbOpu = true;}
      else if(QkBBdOaDRN == XQNrEHnMPZ){KfnmypMAGN = true;}
      if(KBEfzHtkSS == jNlSGdEKpt){dYqMkSBcuf = true;}
      else if(jNlSGdEKpt == KBEfzHtkSS){bYHgXhblQX = true;}
      if(iTbBgtpizH == JOSZCqSXSo){mhXSmhEAhx = true;}
      else if(JOSZCqSXSo == iTbBgtpizH){gMbaxoConq = true;}
      if(cgcydSnSkI == XZUaaSlzXC){MIIDNWdVmc = true;}
      if(QlACboqChx == aPqZpQopUM){hHTptaTmBm = true;}
      if(paNSKDnLKJ == HNCKoBRazl){VCSEspGesl = true;}
      while(XZUaaSlzXC == cgcydSnSkI){ElYABhcLwk = true;}
      while(aPqZpQopUM == aPqZpQopUM){xnxxwqrwcw = true;}
      while(HNCKoBRazl == HNCKoBRazl){enJjqxDMoI = true;}
      if(wDjcoKrKqn == true){wDjcoKrKqn = false;}
      if(rElnTsWrjl == true){rElnTsWrjl = false;}
      if(BcCGgJWKlY == true){BcCGgJWKlY = false;}
      if(AKAlGWfOjf == true){AKAlGWfOjf = false;}
      if(XeyfTDbOpu == true){XeyfTDbOpu = false;}
      if(dYqMkSBcuf == true){dYqMkSBcuf = false;}
      if(mhXSmhEAhx == true){mhXSmhEAhx = false;}
      if(MIIDNWdVmc == true){MIIDNWdVmc = false;}
      if(hHTptaTmBm == true){hHTptaTmBm = false;}
      if(VCSEspGesl == true){VCSEspGesl = false;}
      if(zagshVQmzN == true){zagshVQmzN = false;}
      if(nepRyeNgXM == true){nepRyeNgXM = false;}
      if(OQztbJoDKX == true){OQztbJoDKX = false;}
      if(PzcBdGaaIX == true){PzcBdGaaIX = false;}
      if(KfnmypMAGN == true){KfnmypMAGN = false;}
      if(bYHgXhblQX == true){bYHgXhblQX = false;}
      if(gMbaxoConq == true){gMbaxoConq = false;}
      if(ElYABhcLwk == true){ElYABhcLwk = false;}
      if(xnxxwqrwcw == true){xnxxwqrwcw = false;}
      if(enJjqxDMoI == true){enJjqxDMoI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class REEVJYGCVK
{ 
  void QxMlOBVKld()
  { 
      bool QSCwIeHPZR = false;
      bool skUjTYkWNk = false;
      bool okQjmtcGJn = false;
      bool brQkLgkhgz = false;
      bool jaKuuhpukC = false;
      bool rBdNPeBRIO = false;
      bool BAGkpAUjYl = false;
      bool nDpOAOZUoE = false;
      bool DgVGwaOCUf = false;
      bool fSYRxjTZFt = false;
      bool NGWyOoKPNA = false;
      bool FfcDLTeznP = false;
      bool lSOrGUdXQP = false;
      bool uzPuqxKWrH = false;
      bool PznTaApUGc = false;
      bool ETkpIuqdrs = false;
      bool KmyxFFQhMO = false;
      bool JHHgzmdtRG = false;
      bool eJRmLbOYlw = false;
      bool FfeyxbAqOU = false;
      string QzkhAXNqMs;
      string KaejJOIgYU;
      string ybZlaMksOY;
      string wSNXyKIZTd;
      string LgLxyKzZZX;
      string JINTGnZzHn;
      string mUbmxrNHlz;
      string GhMuJQPbmP;
      string MKSpOmEsQJ;
      string jJSfppFYAG;
      string xqnaRbwSKo;
      string XxLqbbBkXJ;
      string mTqbOxPgES;
      string LqbgRUWrYm;
      string qlibllxbDO;
      string nTAqSdALLT;
      string MONqcfVeYH;
      string FJLjRAjOpb;
      string zmdpdrpkNn;
      string TLfFacYqyF;
      if(QzkhAXNqMs == xqnaRbwSKo){QSCwIeHPZR = true;}
      else if(xqnaRbwSKo == QzkhAXNqMs){NGWyOoKPNA = true;}
      if(KaejJOIgYU == XxLqbbBkXJ){skUjTYkWNk = true;}
      else if(XxLqbbBkXJ == KaejJOIgYU){FfcDLTeznP = true;}
      if(ybZlaMksOY == mTqbOxPgES){okQjmtcGJn = true;}
      else if(mTqbOxPgES == ybZlaMksOY){lSOrGUdXQP = true;}
      if(wSNXyKIZTd == LqbgRUWrYm){brQkLgkhgz = true;}
      else if(LqbgRUWrYm == wSNXyKIZTd){uzPuqxKWrH = true;}
      if(LgLxyKzZZX == qlibllxbDO){jaKuuhpukC = true;}
      else if(qlibllxbDO == LgLxyKzZZX){PznTaApUGc = true;}
      if(JINTGnZzHn == nTAqSdALLT){rBdNPeBRIO = true;}
      else if(nTAqSdALLT == JINTGnZzHn){ETkpIuqdrs = true;}
      if(mUbmxrNHlz == MONqcfVeYH){BAGkpAUjYl = true;}
      else if(MONqcfVeYH == mUbmxrNHlz){KmyxFFQhMO = true;}
      if(GhMuJQPbmP == FJLjRAjOpb){nDpOAOZUoE = true;}
      if(MKSpOmEsQJ == zmdpdrpkNn){DgVGwaOCUf = true;}
      if(jJSfppFYAG == TLfFacYqyF){fSYRxjTZFt = true;}
      while(FJLjRAjOpb == GhMuJQPbmP){JHHgzmdtRG = true;}
      while(zmdpdrpkNn == zmdpdrpkNn){eJRmLbOYlw = true;}
      while(TLfFacYqyF == TLfFacYqyF){FfeyxbAqOU = true;}
      if(QSCwIeHPZR == true){QSCwIeHPZR = false;}
      if(skUjTYkWNk == true){skUjTYkWNk = false;}
      if(okQjmtcGJn == true){okQjmtcGJn = false;}
      if(brQkLgkhgz == true){brQkLgkhgz = false;}
      if(jaKuuhpukC == true){jaKuuhpukC = false;}
      if(rBdNPeBRIO == true){rBdNPeBRIO = false;}
      if(BAGkpAUjYl == true){BAGkpAUjYl = false;}
      if(nDpOAOZUoE == true){nDpOAOZUoE = false;}
      if(DgVGwaOCUf == true){DgVGwaOCUf = false;}
      if(fSYRxjTZFt == true){fSYRxjTZFt = false;}
      if(NGWyOoKPNA == true){NGWyOoKPNA = false;}
      if(FfcDLTeznP == true){FfcDLTeznP = false;}
      if(lSOrGUdXQP == true){lSOrGUdXQP = false;}
      if(uzPuqxKWrH == true){uzPuqxKWrH = false;}
      if(PznTaApUGc == true){PznTaApUGc = false;}
      if(ETkpIuqdrs == true){ETkpIuqdrs = false;}
      if(KmyxFFQhMO == true){KmyxFFQhMO = false;}
      if(JHHgzmdtRG == true){JHHgzmdtRG = false;}
      if(eJRmLbOYlw == true){eJRmLbOYlw = false;}
      if(FfeyxbAqOU == true){FfeyxbAqOU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCPURTHYSI
{ 
  void rEZsLfVwNj()
  { 
      bool oojVzpdnGb = false;
      bool liJiKFpLZX = false;
      bool CJYqlPdtVg = false;
      bool ngnSkaBrza = false;
      bool fwqWLqYLbL = false;
      bool pAsRbeQsii = false;
      bool LiSYmFupxi = false;
      bool DyLzrGSBet = false;
      bool qSSKpnmVqG = false;
      bool KIIQOwcRiG = false;
      bool uhOsHrntZV = false;
      bool MONnqrQIiz = false;
      bool RZzqXupuju = false;
      bool cARYzIEYCx = false;
      bool AswUswtTYV = false;
      bool eUijoViWUM = false;
      bool CrJdrMwooi = false;
      bool nrGkzXcdxb = false;
      bool BVWNQHRhjc = false;
      bool ZgDouHjRbg = false;
      string pzAVtLefdx;
      string RUmbceMNVh;
      string BJnZRrLPQX;
      string NSdJxhmCjl;
      string IWbDylqAcx;
      string NcowhgLaEB;
      string APPFjzqceu;
      string qKdiYdhkae;
      string BLlTKjcgbP;
      string WMyhlrHVTz;
      string uNVhFCzGXE;
      string yZzYAncutz;
      string WJBOXdLuwf;
      string VLRbjmoENH;
      string kVJXQxNZhx;
      string PLaTblMGJa;
      string qDKqhmHXoM;
      string yYglNAzcxa;
      string QlNyQKjxzy;
      string aitmQgLSod;
      if(pzAVtLefdx == uNVhFCzGXE){oojVzpdnGb = true;}
      else if(uNVhFCzGXE == pzAVtLefdx){uhOsHrntZV = true;}
      if(RUmbceMNVh == yZzYAncutz){liJiKFpLZX = true;}
      else if(yZzYAncutz == RUmbceMNVh){MONnqrQIiz = true;}
      if(BJnZRrLPQX == WJBOXdLuwf){CJYqlPdtVg = true;}
      else if(WJBOXdLuwf == BJnZRrLPQX){RZzqXupuju = true;}
      if(NSdJxhmCjl == VLRbjmoENH){ngnSkaBrza = true;}
      else if(VLRbjmoENH == NSdJxhmCjl){cARYzIEYCx = true;}
      if(IWbDylqAcx == kVJXQxNZhx){fwqWLqYLbL = true;}
      else if(kVJXQxNZhx == IWbDylqAcx){AswUswtTYV = true;}
      if(NcowhgLaEB == PLaTblMGJa){pAsRbeQsii = true;}
      else if(PLaTblMGJa == NcowhgLaEB){eUijoViWUM = true;}
      if(APPFjzqceu == qDKqhmHXoM){LiSYmFupxi = true;}
      else if(qDKqhmHXoM == APPFjzqceu){CrJdrMwooi = true;}
      if(qKdiYdhkae == yYglNAzcxa){DyLzrGSBet = true;}
      if(BLlTKjcgbP == QlNyQKjxzy){qSSKpnmVqG = true;}
      if(WMyhlrHVTz == aitmQgLSod){KIIQOwcRiG = true;}
      while(yYglNAzcxa == qKdiYdhkae){nrGkzXcdxb = true;}
      while(QlNyQKjxzy == QlNyQKjxzy){BVWNQHRhjc = true;}
      while(aitmQgLSod == aitmQgLSod){ZgDouHjRbg = true;}
      if(oojVzpdnGb == true){oojVzpdnGb = false;}
      if(liJiKFpLZX == true){liJiKFpLZX = false;}
      if(CJYqlPdtVg == true){CJYqlPdtVg = false;}
      if(ngnSkaBrza == true){ngnSkaBrza = false;}
      if(fwqWLqYLbL == true){fwqWLqYLbL = false;}
      if(pAsRbeQsii == true){pAsRbeQsii = false;}
      if(LiSYmFupxi == true){LiSYmFupxi = false;}
      if(DyLzrGSBet == true){DyLzrGSBet = false;}
      if(qSSKpnmVqG == true){qSSKpnmVqG = false;}
      if(KIIQOwcRiG == true){KIIQOwcRiG = false;}
      if(uhOsHrntZV == true){uhOsHrntZV = false;}
      if(MONnqrQIiz == true){MONnqrQIiz = false;}
      if(RZzqXupuju == true){RZzqXupuju = false;}
      if(cARYzIEYCx == true){cARYzIEYCx = false;}
      if(AswUswtTYV == true){AswUswtTYV = false;}
      if(eUijoViWUM == true){eUijoViWUM = false;}
      if(CrJdrMwooi == true){CrJdrMwooi = false;}
      if(nrGkzXcdxb == true){nrGkzXcdxb = false;}
      if(BVWNQHRhjc == true){BVWNQHRhjc = false;}
      if(ZgDouHjRbg == true){ZgDouHjRbg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FAZLBJWBZV
{ 
  void ibNjrzAeMC()
  { 
      bool CUFmMulYMt = false;
      bool ceHUZjGtwF = false;
      bool qOIBfIXIOz = false;
      bool etjCXnEffc = false;
      bool chqwtZTTJi = false;
      bool GanVjnLEGE = false;
      bool WcJMPiuFxk = false;
      bool faOTbIXMGF = false;
      bool nEyerDFNRi = false;
      bool bzYbFAYdfK = false;
      bool eOVYDeMTtb = false;
      bool QyxAPRddTL = false;
      bool chnNJfClOb = false;
      bool jsfwaZhZbN = false;
      bool plToScCYMm = false;
      bool WtKTgxaIPW = false;
      bool caFRrXSBYo = false;
      bool jDCGVqNyuf = false;
      bool ddZaFoiLOd = false;
      bool zZKEjPfBxu = false;
      string ogZmpXDGqZ;
      string tlXCYPhkSR;
      string KLiwJLbdTz;
      string UwtGNNhLll;
      string ebteDkQbCq;
      string EQJmwcyccd;
      string uYmqFxqRnL;
      string gVzfliQDrY;
      string uzbbuEmGJk;
      string PEhHqFoDZG;
      string synqKhQcBN;
      string LukEiuxKwA;
      string KkHDubnqof;
      string sNclfwLjRN;
      string mJFwYUTdYw;
      string IeHZuIqkuh;
      string tZnUTxRzYl;
      string iMrhNAeLda;
      string IJSsXOGDpW;
      string FanjTNVkbb;
      if(ogZmpXDGqZ == synqKhQcBN){CUFmMulYMt = true;}
      else if(synqKhQcBN == ogZmpXDGqZ){eOVYDeMTtb = true;}
      if(tlXCYPhkSR == LukEiuxKwA){ceHUZjGtwF = true;}
      else if(LukEiuxKwA == tlXCYPhkSR){QyxAPRddTL = true;}
      if(KLiwJLbdTz == KkHDubnqof){qOIBfIXIOz = true;}
      else if(KkHDubnqof == KLiwJLbdTz){chnNJfClOb = true;}
      if(UwtGNNhLll == sNclfwLjRN){etjCXnEffc = true;}
      else if(sNclfwLjRN == UwtGNNhLll){jsfwaZhZbN = true;}
      if(ebteDkQbCq == mJFwYUTdYw){chqwtZTTJi = true;}
      else if(mJFwYUTdYw == ebteDkQbCq){plToScCYMm = true;}
      if(EQJmwcyccd == IeHZuIqkuh){GanVjnLEGE = true;}
      else if(IeHZuIqkuh == EQJmwcyccd){WtKTgxaIPW = true;}
      if(uYmqFxqRnL == tZnUTxRzYl){WcJMPiuFxk = true;}
      else if(tZnUTxRzYl == uYmqFxqRnL){caFRrXSBYo = true;}
      if(gVzfliQDrY == iMrhNAeLda){faOTbIXMGF = true;}
      if(uzbbuEmGJk == IJSsXOGDpW){nEyerDFNRi = true;}
      if(PEhHqFoDZG == FanjTNVkbb){bzYbFAYdfK = true;}
      while(iMrhNAeLda == gVzfliQDrY){jDCGVqNyuf = true;}
      while(IJSsXOGDpW == IJSsXOGDpW){ddZaFoiLOd = true;}
      while(FanjTNVkbb == FanjTNVkbb){zZKEjPfBxu = true;}
      if(CUFmMulYMt == true){CUFmMulYMt = false;}
      if(ceHUZjGtwF == true){ceHUZjGtwF = false;}
      if(qOIBfIXIOz == true){qOIBfIXIOz = false;}
      if(etjCXnEffc == true){etjCXnEffc = false;}
      if(chqwtZTTJi == true){chqwtZTTJi = false;}
      if(GanVjnLEGE == true){GanVjnLEGE = false;}
      if(WcJMPiuFxk == true){WcJMPiuFxk = false;}
      if(faOTbIXMGF == true){faOTbIXMGF = false;}
      if(nEyerDFNRi == true){nEyerDFNRi = false;}
      if(bzYbFAYdfK == true){bzYbFAYdfK = false;}
      if(eOVYDeMTtb == true){eOVYDeMTtb = false;}
      if(QyxAPRddTL == true){QyxAPRddTL = false;}
      if(chnNJfClOb == true){chnNJfClOb = false;}
      if(jsfwaZhZbN == true){jsfwaZhZbN = false;}
      if(plToScCYMm == true){plToScCYMm = false;}
      if(WtKTgxaIPW == true){WtKTgxaIPW = false;}
      if(caFRrXSBYo == true){caFRrXSBYo = false;}
      if(jDCGVqNyuf == true){jDCGVqNyuf = false;}
      if(ddZaFoiLOd == true){ddZaFoiLOd = false;}
      if(zZKEjPfBxu == true){zZKEjPfBxu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLBCEPOUJT
{ 
  void ExaPBCMTTt()
  { 
      bool wDFOkurDtP = false;
      bool ZjjidMaNBn = false;
      bool JIDaSnkEQn = false;
      bool zxlPwginca = false;
      bool JtOQUArITt = false;
      bool PVdxknzdww = false;
      bool JmmGQcxUlw = false;
      bool cmjaePsmGS = false;
      bool wckVYcSndH = false;
      bool hFrgQVGHAq = false;
      bool CWWWQbkDSV = false;
      bool uMXcAgCQhm = false;
      bool KJqdOXtCJI = false;
      bool IklOQYGNEw = false;
      bool rOUIMVgOgj = false;
      bool ToZNgrfrIs = false;
      bool hhsJMJZJMb = false;
      bool ZnMltuniRr = false;
      bool qfVZoSLXgX = false;
      bool rNFLOJVLuC = false;
      string NNsJbIPfNZ;
      string EAexyNFuam;
      string lyDJKdlNPF;
      string EHBNAZmtLQ;
      string XcPunfaFIO;
      string diDgxPJjyy;
      string WBQHVxyRxX;
      string aLiKPJhIUe;
      string CfEAaUDTQj;
      string PCuNsVLIZq;
      string gJHkmRArRm;
      string gBOTupxPgA;
      string seBMIYQUQt;
      string xZidxrXTMI;
      string UKCcCOnaRC;
      string YubZxCIubO;
      string BebWpHRjVC;
      string RcDXehbYKs;
      string joDNVByJfu;
      string jcqyHpielu;
      if(NNsJbIPfNZ == gJHkmRArRm){wDFOkurDtP = true;}
      else if(gJHkmRArRm == NNsJbIPfNZ){CWWWQbkDSV = true;}
      if(EAexyNFuam == gBOTupxPgA){ZjjidMaNBn = true;}
      else if(gBOTupxPgA == EAexyNFuam){uMXcAgCQhm = true;}
      if(lyDJKdlNPF == seBMIYQUQt){JIDaSnkEQn = true;}
      else if(seBMIYQUQt == lyDJKdlNPF){KJqdOXtCJI = true;}
      if(EHBNAZmtLQ == xZidxrXTMI){zxlPwginca = true;}
      else if(xZidxrXTMI == EHBNAZmtLQ){IklOQYGNEw = true;}
      if(XcPunfaFIO == UKCcCOnaRC){JtOQUArITt = true;}
      else if(UKCcCOnaRC == XcPunfaFIO){rOUIMVgOgj = true;}
      if(diDgxPJjyy == YubZxCIubO){PVdxknzdww = true;}
      else if(YubZxCIubO == diDgxPJjyy){ToZNgrfrIs = true;}
      if(WBQHVxyRxX == BebWpHRjVC){JmmGQcxUlw = true;}
      else if(BebWpHRjVC == WBQHVxyRxX){hhsJMJZJMb = true;}
      if(aLiKPJhIUe == RcDXehbYKs){cmjaePsmGS = true;}
      if(CfEAaUDTQj == joDNVByJfu){wckVYcSndH = true;}
      if(PCuNsVLIZq == jcqyHpielu){hFrgQVGHAq = true;}
      while(RcDXehbYKs == aLiKPJhIUe){ZnMltuniRr = true;}
      while(joDNVByJfu == joDNVByJfu){qfVZoSLXgX = true;}
      while(jcqyHpielu == jcqyHpielu){rNFLOJVLuC = true;}
      if(wDFOkurDtP == true){wDFOkurDtP = false;}
      if(ZjjidMaNBn == true){ZjjidMaNBn = false;}
      if(JIDaSnkEQn == true){JIDaSnkEQn = false;}
      if(zxlPwginca == true){zxlPwginca = false;}
      if(JtOQUArITt == true){JtOQUArITt = false;}
      if(PVdxknzdww == true){PVdxknzdww = false;}
      if(JmmGQcxUlw == true){JmmGQcxUlw = false;}
      if(cmjaePsmGS == true){cmjaePsmGS = false;}
      if(wckVYcSndH == true){wckVYcSndH = false;}
      if(hFrgQVGHAq == true){hFrgQVGHAq = false;}
      if(CWWWQbkDSV == true){CWWWQbkDSV = false;}
      if(uMXcAgCQhm == true){uMXcAgCQhm = false;}
      if(KJqdOXtCJI == true){KJqdOXtCJI = false;}
      if(IklOQYGNEw == true){IklOQYGNEw = false;}
      if(rOUIMVgOgj == true){rOUIMVgOgj = false;}
      if(ToZNgrfrIs == true){ToZNgrfrIs = false;}
      if(hhsJMJZJMb == true){hhsJMJZJMb = false;}
      if(ZnMltuniRr == true){ZnMltuniRr = false;}
      if(qfVZoSLXgX == true){qfVZoSLXgX = false;}
      if(rNFLOJVLuC == true){rNFLOJVLuC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHBEUTNNFX
{ 
  void jzczjNppQl()
  { 
      bool qpleBJaMJL = false;
      bool zDMySAEkZg = false;
      bool ZrdqZDewWR = false;
      bool pLoIpJYzQK = false;
      bool nMPMxehubb = false;
      bool FUjeCyLtEx = false;
      bool depqVmNEHI = false;
      bool aFUOsMbQtu = false;
      bool VjTuMUbKGq = false;
      bool xdtTfIWYqJ = false;
      bool RdmSAzAUlo = false;
      bool WuAJatKueA = false;
      bool KCxPLxLBhj = false;
      bool oDZkdrwAtM = false;
      bool UHYQUCdjrl = false;
      bool ybsqyOfXHD = false;
      bool nzlCATVOfi = false;
      bool xKARfDdguI = false;
      bool SaIwkNJhlO = false;
      bool LYrqXUVVQA = false;
      string mdXKFZneaA;
      string zXKLJWOdrN;
      string FNiuqIhtBA;
      string oMqQlgDyei;
      string aAaRBdHhyd;
      string OyflgYtcSw;
      string qscZLmgsYc;
      string SQzJlEmRtN;
      string BAuXlqfFjN;
      string laehqgWAFN;
      string wNIVKxzVzc;
      string lchEuqyEnT;
      string GbILprkQSE;
      string glLfQmrYNn;
      string rJFHaIrZmA;
      string iRMkHUExfS;
      string LhDuuzRCmI;
      string yYqzbwVBjg;
      string zLdRUOZZXw;
      string htsucJGJLb;
      if(mdXKFZneaA == wNIVKxzVzc){qpleBJaMJL = true;}
      else if(wNIVKxzVzc == mdXKFZneaA){RdmSAzAUlo = true;}
      if(zXKLJWOdrN == lchEuqyEnT){zDMySAEkZg = true;}
      else if(lchEuqyEnT == zXKLJWOdrN){WuAJatKueA = true;}
      if(FNiuqIhtBA == GbILprkQSE){ZrdqZDewWR = true;}
      else if(GbILprkQSE == FNiuqIhtBA){KCxPLxLBhj = true;}
      if(oMqQlgDyei == glLfQmrYNn){pLoIpJYzQK = true;}
      else if(glLfQmrYNn == oMqQlgDyei){oDZkdrwAtM = true;}
      if(aAaRBdHhyd == rJFHaIrZmA){nMPMxehubb = true;}
      else if(rJFHaIrZmA == aAaRBdHhyd){UHYQUCdjrl = true;}
      if(OyflgYtcSw == iRMkHUExfS){FUjeCyLtEx = true;}
      else if(iRMkHUExfS == OyflgYtcSw){ybsqyOfXHD = true;}
      if(qscZLmgsYc == LhDuuzRCmI){depqVmNEHI = true;}
      else if(LhDuuzRCmI == qscZLmgsYc){nzlCATVOfi = true;}
      if(SQzJlEmRtN == yYqzbwVBjg){aFUOsMbQtu = true;}
      if(BAuXlqfFjN == zLdRUOZZXw){VjTuMUbKGq = true;}
      if(laehqgWAFN == htsucJGJLb){xdtTfIWYqJ = true;}
      while(yYqzbwVBjg == SQzJlEmRtN){xKARfDdguI = true;}
      while(zLdRUOZZXw == zLdRUOZZXw){SaIwkNJhlO = true;}
      while(htsucJGJLb == htsucJGJLb){LYrqXUVVQA = true;}
      if(qpleBJaMJL == true){qpleBJaMJL = false;}
      if(zDMySAEkZg == true){zDMySAEkZg = false;}
      if(ZrdqZDewWR == true){ZrdqZDewWR = false;}
      if(pLoIpJYzQK == true){pLoIpJYzQK = false;}
      if(nMPMxehubb == true){nMPMxehubb = false;}
      if(FUjeCyLtEx == true){FUjeCyLtEx = false;}
      if(depqVmNEHI == true){depqVmNEHI = false;}
      if(aFUOsMbQtu == true){aFUOsMbQtu = false;}
      if(VjTuMUbKGq == true){VjTuMUbKGq = false;}
      if(xdtTfIWYqJ == true){xdtTfIWYqJ = false;}
      if(RdmSAzAUlo == true){RdmSAzAUlo = false;}
      if(WuAJatKueA == true){WuAJatKueA = false;}
      if(KCxPLxLBhj == true){KCxPLxLBhj = false;}
      if(oDZkdrwAtM == true){oDZkdrwAtM = false;}
      if(UHYQUCdjrl == true){UHYQUCdjrl = false;}
      if(ybsqyOfXHD == true){ybsqyOfXHD = false;}
      if(nzlCATVOfi == true){nzlCATVOfi = false;}
      if(xKARfDdguI == true){xKARfDdguI = false;}
      if(SaIwkNJhlO == true){SaIwkNJhlO = false;}
      if(LYrqXUVVQA == true){LYrqXUVVQA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLYMTPGCPH
{ 
  void VDxyhEGODp()
  { 
      bool MhDQWIYkqd = false;
      bool FCZHzNOjFR = false;
      bool znNPyVKDuD = false;
      bool eaoQmixFRf = false;
      bool IJOxVQDMKt = false;
      bool DsrupYUnRA = false;
      bool yVonzeNJTQ = false;
      bool PJSZJoZPsh = false;
      bool SysAAkisaO = false;
      bool NJmQglUayq = false;
      bool DsrtesaSlA = false;
      bool zFtjhAcnnO = false;
      bool uThFCFVBrW = false;
      bool UyQCdYGyUG = false;
      bool JQHZPIODhg = false;
      bool JfmjuiLlrY = false;
      bool XZZPeAnrFJ = false;
      bool tdTgEeMHos = false;
      bool qSTKMoLgGu = false;
      bool NTGwijpquO = false;
      string EePklmnaBj;
      string BjrqYEpmEK;
      string wbKCgEApEo;
      string QGDxornxHQ;
      string pzbFqcNWxW;
      string EVVpRcUNDh;
      string lyWLSuftBf;
      string PrenTxzFKE;
      string qdrhjtjNfM;
      string XatZdrbPlw;
      string xSUQGMqhVT;
      string cODypIFoaY;
      string KROoIoxFJa;
      string UiTNHXJbaX;
      string DCrMiIXuiV;
      string mmnMleEfHQ;
      string PkXtztuoqS;
      string ydNDVIYBFA;
      string RBVnngtGbb;
      string TcTKIRdyMo;
      if(EePklmnaBj == xSUQGMqhVT){MhDQWIYkqd = true;}
      else if(xSUQGMqhVT == EePklmnaBj){DsrtesaSlA = true;}
      if(BjrqYEpmEK == cODypIFoaY){FCZHzNOjFR = true;}
      else if(cODypIFoaY == BjrqYEpmEK){zFtjhAcnnO = true;}
      if(wbKCgEApEo == KROoIoxFJa){znNPyVKDuD = true;}
      else if(KROoIoxFJa == wbKCgEApEo){uThFCFVBrW = true;}
      if(QGDxornxHQ == UiTNHXJbaX){eaoQmixFRf = true;}
      else if(UiTNHXJbaX == QGDxornxHQ){UyQCdYGyUG = true;}
      if(pzbFqcNWxW == DCrMiIXuiV){IJOxVQDMKt = true;}
      else if(DCrMiIXuiV == pzbFqcNWxW){JQHZPIODhg = true;}
      if(EVVpRcUNDh == mmnMleEfHQ){DsrupYUnRA = true;}
      else if(mmnMleEfHQ == EVVpRcUNDh){JfmjuiLlrY = true;}
      if(lyWLSuftBf == PkXtztuoqS){yVonzeNJTQ = true;}
      else if(PkXtztuoqS == lyWLSuftBf){XZZPeAnrFJ = true;}
      if(PrenTxzFKE == ydNDVIYBFA){PJSZJoZPsh = true;}
      if(qdrhjtjNfM == RBVnngtGbb){SysAAkisaO = true;}
      if(XatZdrbPlw == TcTKIRdyMo){NJmQglUayq = true;}
      while(ydNDVIYBFA == PrenTxzFKE){tdTgEeMHos = true;}
      while(RBVnngtGbb == RBVnngtGbb){qSTKMoLgGu = true;}
      while(TcTKIRdyMo == TcTKIRdyMo){NTGwijpquO = true;}
      if(MhDQWIYkqd == true){MhDQWIYkqd = false;}
      if(FCZHzNOjFR == true){FCZHzNOjFR = false;}
      if(znNPyVKDuD == true){znNPyVKDuD = false;}
      if(eaoQmixFRf == true){eaoQmixFRf = false;}
      if(IJOxVQDMKt == true){IJOxVQDMKt = false;}
      if(DsrupYUnRA == true){DsrupYUnRA = false;}
      if(yVonzeNJTQ == true){yVonzeNJTQ = false;}
      if(PJSZJoZPsh == true){PJSZJoZPsh = false;}
      if(SysAAkisaO == true){SysAAkisaO = false;}
      if(NJmQglUayq == true){NJmQglUayq = false;}
      if(DsrtesaSlA == true){DsrtesaSlA = false;}
      if(zFtjhAcnnO == true){zFtjhAcnnO = false;}
      if(uThFCFVBrW == true){uThFCFVBrW = false;}
      if(UyQCdYGyUG == true){UyQCdYGyUG = false;}
      if(JQHZPIODhg == true){JQHZPIODhg = false;}
      if(JfmjuiLlrY == true){JfmjuiLlrY = false;}
      if(XZZPeAnrFJ == true){XZZPeAnrFJ = false;}
      if(tdTgEeMHos == true){tdTgEeMHos = false;}
      if(qSTKMoLgGu == true){qSTKMoLgGu = false;}
      if(NTGwijpquO == true){NTGwijpquO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDAKWHQTMB
{ 
  void TbyMAnioKP()
  { 
      bool rbimkuySxT = false;
      bool bQkROHZiKi = false;
      bool MYnbLzAAET = false;
      bool wmZwgpwLLH = false;
      bool QDFsjBeQUa = false;
      bool nqTZISnGal = false;
      bool uxNcXopokX = false;
      bool KNWCRJStqJ = false;
      bool TiecfFSzmN = false;
      bool CojZMSocVu = false;
      bool KpfxQaTRIz = false;
      bool AtORRLSjwR = false;
      bool VqBXVUcwoy = false;
      bool TpXwzcDhME = false;
      bool lAqnMHZSIB = false;
      bool AEfEYToIau = false;
      bool yWcJeJVSSn = false;
      bool IkXrfVzNKO = false;
      bool tJnnyPKSWe = false;
      bool ntGRGOXhID = false;
      string VaxUncXHwq;
      string VAWspFznBS;
      string NXiONmzJKb;
      string sEBdKUVaMP;
      string AgizmCgGCO;
      string OQRNbyriHA;
      string cOxUyQyrhU;
      string iXblSgoiaL;
      string FrGwMbmnCM;
      string clTLlkiNBV;
      string EoYheqofuu;
      string IJHutjHBIV;
      string dKpVrxDPzg;
      string xahFGQTYRV;
      string mGrGDSdXQB;
      string dhFeqtzDpg;
      string mYgNyhaCod;
      string QijmhWRiRY;
      string SfzxDOVCNM;
      string RQhjhNZeIV;
      if(VaxUncXHwq == EoYheqofuu){rbimkuySxT = true;}
      else if(EoYheqofuu == VaxUncXHwq){KpfxQaTRIz = true;}
      if(VAWspFznBS == IJHutjHBIV){bQkROHZiKi = true;}
      else if(IJHutjHBIV == VAWspFznBS){AtORRLSjwR = true;}
      if(NXiONmzJKb == dKpVrxDPzg){MYnbLzAAET = true;}
      else if(dKpVrxDPzg == NXiONmzJKb){VqBXVUcwoy = true;}
      if(sEBdKUVaMP == xahFGQTYRV){wmZwgpwLLH = true;}
      else if(xahFGQTYRV == sEBdKUVaMP){TpXwzcDhME = true;}
      if(AgizmCgGCO == mGrGDSdXQB){QDFsjBeQUa = true;}
      else if(mGrGDSdXQB == AgizmCgGCO){lAqnMHZSIB = true;}
      if(OQRNbyriHA == dhFeqtzDpg){nqTZISnGal = true;}
      else if(dhFeqtzDpg == OQRNbyriHA){AEfEYToIau = true;}
      if(cOxUyQyrhU == mYgNyhaCod){uxNcXopokX = true;}
      else if(mYgNyhaCod == cOxUyQyrhU){yWcJeJVSSn = true;}
      if(iXblSgoiaL == QijmhWRiRY){KNWCRJStqJ = true;}
      if(FrGwMbmnCM == SfzxDOVCNM){TiecfFSzmN = true;}
      if(clTLlkiNBV == RQhjhNZeIV){CojZMSocVu = true;}
      while(QijmhWRiRY == iXblSgoiaL){IkXrfVzNKO = true;}
      while(SfzxDOVCNM == SfzxDOVCNM){tJnnyPKSWe = true;}
      while(RQhjhNZeIV == RQhjhNZeIV){ntGRGOXhID = true;}
      if(rbimkuySxT == true){rbimkuySxT = false;}
      if(bQkROHZiKi == true){bQkROHZiKi = false;}
      if(MYnbLzAAET == true){MYnbLzAAET = false;}
      if(wmZwgpwLLH == true){wmZwgpwLLH = false;}
      if(QDFsjBeQUa == true){QDFsjBeQUa = false;}
      if(nqTZISnGal == true){nqTZISnGal = false;}
      if(uxNcXopokX == true){uxNcXopokX = false;}
      if(KNWCRJStqJ == true){KNWCRJStqJ = false;}
      if(TiecfFSzmN == true){TiecfFSzmN = false;}
      if(CojZMSocVu == true){CojZMSocVu = false;}
      if(KpfxQaTRIz == true){KpfxQaTRIz = false;}
      if(AtORRLSjwR == true){AtORRLSjwR = false;}
      if(VqBXVUcwoy == true){VqBXVUcwoy = false;}
      if(TpXwzcDhME == true){TpXwzcDhME = false;}
      if(lAqnMHZSIB == true){lAqnMHZSIB = false;}
      if(AEfEYToIau == true){AEfEYToIau = false;}
      if(yWcJeJVSSn == true){yWcJeJVSSn = false;}
      if(IkXrfVzNKO == true){IkXrfVzNKO = false;}
      if(tJnnyPKSWe == true){tJnnyPKSWe = false;}
      if(ntGRGOXhID == true){ntGRGOXhID = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWGABZQMMF
{ 
  void hBAmbLmaBk()
  { 
      bool kgiJcuRIzg = false;
      bool yYBZtVRJbi = false;
      bool MgfJjqCVUx = false;
      bool WhojQpCpdl = false;
      bool LCfrUXcrxi = false;
      bool FVAtXDBYYk = false;
      bool sunBJPiQIE = false;
      bool TbepWJBmoL = false;
      bool OKXlrAgtMM = false;
      bool ncQrsQOdhE = false;
      bool oLisOdqKWN = false;
      bool CNjMWiXBJJ = false;
      bool hoEwQpKmxG = false;
      bool uXFjWCaeWO = false;
      bool JWWyKasDVK = false;
      bool rMTYVAHlcY = false;
      bool SENQSdIzpT = false;
      bool HreuzLRFlo = false;
      bool wHQmOhDfOW = false;
      bool uoCxuFJGff = false;
      string MqGMclkjdG;
      string rHbNDVKZbf;
      string ggFyaQLEYc;
      string DWTDHtKAXx;
      string IQTeEsaIjm;
      string OICcnflIkL;
      string agKACUnYGI;
      string LKCdWPNasg;
      string pDTlOtUqOb;
      string IBOLWaFTbj;
      string FBBaaDGXFX;
      string SLODVXMYkI;
      string zwKezJwpGw;
      string KtyJbnBsKL;
      string nxlqJxlKpz;
      string OfhTjIqWaR;
      string HQQJNYMFbg;
      string VTOYTCKSVB;
      string WkzHgdLeZS;
      string wdRrEWfcdk;
      if(MqGMclkjdG == FBBaaDGXFX){kgiJcuRIzg = true;}
      else if(FBBaaDGXFX == MqGMclkjdG){oLisOdqKWN = true;}
      if(rHbNDVKZbf == SLODVXMYkI){yYBZtVRJbi = true;}
      else if(SLODVXMYkI == rHbNDVKZbf){CNjMWiXBJJ = true;}
      if(ggFyaQLEYc == zwKezJwpGw){MgfJjqCVUx = true;}
      else if(zwKezJwpGw == ggFyaQLEYc){hoEwQpKmxG = true;}
      if(DWTDHtKAXx == KtyJbnBsKL){WhojQpCpdl = true;}
      else if(KtyJbnBsKL == DWTDHtKAXx){uXFjWCaeWO = true;}
      if(IQTeEsaIjm == nxlqJxlKpz){LCfrUXcrxi = true;}
      else if(nxlqJxlKpz == IQTeEsaIjm){JWWyKasDVK = true;}
      if(OICcnflIkL == OfhTjIqWaR){FVAtXDBYYk = true;}
      else if(OfhTjIqWaR == OICcnflIkL){rMTYVAHlcY = true;}
      if(agKACUnYGI == HQQJNYMFbg){sunBJPiQIE = true;}
      else if(HQQJNYMFbg == agKACUnYGI){SENQSdIzpT = true;}
      if(LKCdWPNasg == VTOYTCKSVB){TbepWJBmoL = true;}
      if(pDTlOtUqOb == WkzHgdLeZS){OKXlrAgtMM = true;}
      if(IBOLWaFTbj == wdRrEWfcdk){ncQrsQOdhE = true;}
      while(VTOYTCKSVB == LKCdWPNasg){HreuzLRFlo = true;}
      while(WkzHgdLeZS == WkzHgdLeZS){wHQmOhDfOW = true;}
      while(wdRrEWfcdk == wdRrEWfcdk){uoCxuFJGff = true;}
      if(kgiJcuRIzg == true){kgiJcuRIzg = false;}
      if(yYBZtVRJbi == true){yYBZtVRJbi = false;}
      if(MgfJjqCVUx == true){MgfJjqCVUx = false;}
      if(WhojQpCpdl == true){WhojQpCpdl = false;}
      if(LCfrUXcrxi == true){LCfrUXcrxi = false;}
      if(FVAtXDBYYk == true){FVAtXDBYYk = false;}
      if(sunBJPiQIE == true){sunBJPiQIE = false;}
      if(TbepWJBmoL == true){TbepWJBmoL = false;}
      if(OKXlrAgtMM == true){OKXlrAgtMM = false;}
      if(ncQrsQOdhE == true){ncQrsQOdhE = false;}
      if(oLisOdqKWN == true){oLisOdqKWN = false;}
      if(CNjMWiXBJJ == true){CNjMWiXBJJ = false;}
      if(hoEwQpKmxG == true){hoEwQpKmxG = false;}
      if(uXFjWCaeWO == true){uXFjWCaeWO = false;}
      if(JWWyKasDVK == true){JWWyKasDVK = false;}
      if(rMTYVAHlcY == true){rMTYVAHlcY = false;}
      if(SENQSdIzpT == true){SENQSdIzpT = false;}
      if(HreuzLRFlo == true){HreuzLRFlo = false;}
      if(wHQmOhDfOW == true){wHQmOhDfOW = false;}
      if(uoCxuFJGff == true){uoCxuFJGff = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHWHLRRAIN
{ 
  void BrXOKBAIAp()
  { 
      bool kldrdeagKR = false;
      bool VFPBGydmJm = false;
      bool EydKhiJjus = false;
      bool oRjVksiapx = false;
      bool QKmsZsuBSr = false;
      bool ePZOglHTJu = false;
      bool VqkRcDUsQN = false;
      bool PDxLVsLjko = false;
      bool mHQDNZrVny = false;
      bool kPRubZYUPV = false;
      bool XCjFbbSOsm = false;
      bool aWhUINahDD = false;
      bool LzFSbzkCju = false;
      bool TpTPQkWKak = false;
      bool HccAXNhwlN = false;
      bool zqRMJXwRcb = false;
      bool pPdxSjDSDW = false;
      bool pPHRwhWEtO = false;
      bool RnPVwcYHFr = false;
      bool nEgyuqzfgn = false;
      string GTCzsNZTlm;
      string QklslcJOVb;
      string RfWHKSnfsh;
      string dEjfOnhzXa;
      string ahMjYuRqZn;
      string TftHqZwtoZ;
      string ZtaEJMAGdx;
      string tJptBiTmiO;
      string BwFFOxJcnn;
      string rmKxBfGIZM;
      string uKNcsKpAGH;
      string GJLZYcnVoL;
      string CXSpEGyrrU;
      string cKMVTqibLD;
      string HJVfhhbkYY;
      string rkSOKXrWXl;
      string MxHlewwoGg;
      string tMJlDrBlHW;
      string eNSTcrqxLu;
      string zLDZqJCjBl;
      if(GTCzsNZTlm == uKNcsKpAGH){kldrdeagKR = true;}
      else if(uKNcsKpAGH == GTCzsNZTlm){XCjFbbSOsm = true;}
      if(QklslcJOVb == GJLZYcnVoL){VFPBGydmJm = true;}
      else if(GJLZYcnVoL == QklslcJOVb){aWhUINahDD = true;}
      if(RfWHKSnfsh == CXSpEGyrrU){EydKhiJjus = true;}
      else if(CXSpEGyrrU == RfWHKSnfsh){LzFSbzkCju = true;}
      if(dEjfOnhzXa == cKMVTqibLD){oRjVksiapx = true;}
      else if(cKMVTqibLD == dEjfOnhzXa){TpTPQkWKak = true;}
      if(ahMjYuRqZn == HJVfhhbkYY){QKmsZsuBSr = true;}
      else if(HJVfhhbkYY == ahMjYuRqZn){HccAXNhwlN = true;}
      if(TftHqZwtoZ == rkSOKXrWXl){ePZOglHTJu = true;}
      else if(rkSOKXrWXl == TftHqZwtoZ){zqRMJXwRcb = true;}
      if(ZtaEJMAGdx == MxHlewwoGg){VqkRcDUsQN = true;}
      else if(MxHlewwoGg == ZtaEJMAGdx){pPdxSjDSDW = true;}
      if(tJptBiTmiO == tMJlDrBlHW){PDxLVsLjko = true;}
      if(BwFFOxJcnn == eNSTcrqxLu){mHQDNZrVny = true;}
      if(rmKxBfGIZM == zLDZqJCjBl){kPRubZYUPV = true;}
      while(tMJlDrBlHW == tJptBiTmiO){pPHRwhWEtO = true;}
      while(eNSTcrqxLu == eNSTcrqxLu){RnPVwcYHFr = true;}
      while(zLDZqJCjBl == zLDZqJCjBl){nEgyuqzfgn = true;}
      if(kldrdeagKR == true){kldrdeagKR = false;}
      if(VFPBGydmJm == true){VFPBGydmJm = false;}
      if(EydKhiJjus == true){EydKhiJjus = false;}
      if(oRjVksiapx == true){oRjVksiapx = false;}
      if(QKmsZsuBSr == true){QKmsZsuBSr = false;}
      if(ePZOglHTJu == true){ePZOglHTJu = false;}
      if(VqkRcDUsQN == true){VqkRcDUsQN = false;}
      if(PDxLVsLjko == true){PDxLVsLjko = false;}
      if(mHQDNZrVny == true){mHQDNZrVny = false;}
      if(kPRubZYUPV == true){kPRubZYUPV = false;}
      if(XCjFbbSOsm == true){XCjFbbSOsm = false;}
      if(aWhUINahDD == true){aWhUINahDD = false;}
      if(LzFSbzkCju == true){LzFSbzkCju = false;}
      if(TpTPQkWKak == true){TpTPQkWKak = false;}
      if(HccAXNhwlN == true){HccAXNhwlN = false;}
      if(zqRMJXwRcb == true){zqRMJXwRcb = false;}
      if(pPdxSjDSDW == true){pPdxSjDSDW = false;}
      if(pPHRwhWEtO == true){pPHRwhWEtO = false;}
      if(RnPVwcYHFr == true){RnPVwcYHFr = false;}
      if(nEgyuqzfgn == true){nEgyuqzfgn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTQVSAZMYT
{ 
  void PHDyoiDDhe()
  { 
      bool CINapmTyVz = false;
      bool JSDCnUPUCr = false;
      bool CAXByBtOUC = false;
      bool oUIaYJTuVe = false;
      bool ulSgkJytMQ = false;
      bool crCJZCkLbo = false;
      bool rFcTKoJcde = false;
      bool BUzXxPgpQn = false;
      bool DABEYwRzAV = false;
      bool XHSgloIzVu = false;
      bool zUQhPIseMJ = false;
      bool UtunlrDYuN = false;
      bool WKbHGsCRkH = false;
      bool HgUUohiTnP = false;
      bool DllpAdMeut = false;
      bool kjEIXnrJaV = false;
      bool GatECmZZyD = false;
      bool JjkeKkXkGc = false;
      bool gXWpVXcMxA = false;
      bool oYrRJbqhnM = false;
      string iIafSWcdca;
      string EDOawwyaLo;
      string jQLIriZiKB;
      string IbJeMlRXSB;
      string sbaLadfoIP;
      string TRuPOSxSnj;
      string wsSbRctiNJ;
      string daHJwIoAgN;
      string CjZtgpfsPs;
      string ozjiEzIzsy;
      string jwaylsKkSG;
      string cwlZgLTYtb;
      string wATTUeqXEx;
      string zpGhdFIaIm;
      string ftaIQrMJCs;
      string ejFRBicHdG;
      string ClgUHmoDwa;
      string CrPGuCZKDb;
      string SgVLSOkoft;
      string cBxBksNFBc;
      if(iIafSWcdca == jwaylsKkSG){CINapmTyVz = true;}
      else if(jwaylsKkSG == iIafSWcdca){zUQhPIseMJ = true;}
      if(EDOawwyaLo == cwlZgLTYtb){JSDCnUPUCr = true;}
      else if(cwlZgLTYtb == EDOawwyaLo){UtunlrDYuN = true;}
      if(jQLIriZiKB == wATTUeqXEx){CAXByBtOUC = true;}
      else if(wATTUeqXEx == jQLIriZiKB){WKbHGsCRkH = true;}
      if(IbJeMlRXSB == zpGhdFIaIm){oUIaYJTuVe = true;}
      else if(zpGhdFIaIm == IbJeMlRXSB){HgUUohiTnP = true;}
      if(sbaLadfoIP == ftaIQrMJCs){ulSgkJytMQ = true;}
      else if(ftaIQrMJCs == sbaLadfoIP){DllpAdMeut = true;}
      if(TRuPOSxSnj == ejFRBicHdG){crCJZCkLbo = true;}
      else if(ejFRBicHdG == TRuPOSxSnj){kjEIXnrJaV = true;}
      if(wsSbRctiNJ == ClgUHmoDwa){rFcTKoJcde = true;}
      else if(ClgUHmoDwa == wsSbRctiNJ){GatECmZZyD = true;}
      if(daHJwIoAgN == CrPGuCZKDb){BUzXxPgpQn = true;}
      if(CjZtgpfsPs == SgVLSOkoft){DABEYwRzAV = true;}
      if(ozjiEzIzsy == cBxBksNFBc){XHSgloIzVu = true;}
      while(CrPGuCZKDb == daHJwIoAgN){JjkeKkXkGc = true;}
      while(SgVLSOkoft == SgVLSOkoft){gXWpVXcMxA = true;}
      while(cBxBksNFBc == cBxBksNFBc){oYrRJbqhnM = true;}
      if(CINapmTyVz == true){CINapmTyVz = false;}
      if(JSDCnUPUCr == true){JSDCnUPUCr = false;}
      if(CAXByBtOUC == true){CAXByBtOUC = false;}
      if(oUIaYJTuVe == true){oUIaYJTuVe = false;}
      if(ulSgkJytMQ == true){ulSgkJytMQ = false;}
      if(crCJZCkLbo == true){crCJZCkLbo = false;}
      if(rFcTKoJcde == true){rFcTKoJcde = false;}
      if(BUzXxPgpQn == true){BUzXxPgpQn = false;}
      if(DABEYwRzAV == true){DABEYwRzAV = false;}
      if(XHSgloIzVu == true){XHSgloIzVu = false;}
      if(zUQhPIseMJ == true){zUQhPIseMJ = false;}
      if(UtunlrDYuN == true){UtunlrDYuN = false;}
      if(WKbHGsCRkH == true){WKbHGsCRkH = false;}
      if(HgUUohiTnP == true){HgUUohiTnP = false;}
      if(DllpAdMeut == true){DllpAdMeut = false;}
      if(kjEIXnrJaV == true){kjEIXnrJaV = false;}
      if(GatECmZZyD == true){GatECmZZyD = false;}
      if(JjkeKkXkGc == true){JjkeKkXkGc = false;}
      if(gXWpVXcMxA == true){gXWpVXcMxA = false;}
      if(oYrRJbqhnM == true){oYrRJbqhnM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFYLIHBLZX
{ 
  void EebxAFnDKS()
  { 
      bool XRuMXMuZqn = false;
      bool yqRwkdjsio = false;
      bool nAxZbiDVAd = false;
      bool ogtgrXWfZq = false;
      bool ATpEJbfpwa = false;
      bool RYZAoXTVkn = false;
      bool IZYNzRxkDM = false;
      bool HETqnTKsPA = false;
      bool CMYZLQGsqU = false;
      bool EAukhaubEq = false;
      bool euljSMEhLV = false;
      bool MaGjkuAzBi = false;
      bool KDsiHGIhIN = false;
      bool YhoXVHZoGy = false;
      bool LYgVHdtKAm = false;
      bool ZuaVgaCDbM = false;
      bool EWYywelhOc = false;
      bool UKrCWlVWad = false;
      bool MyhVncHSqt = false;
      bool FWNttoziZb = false;
      string aPCSDFOpuJ;
      string YBIpqCSTMO;
      string KCnYRhVout;
      string oIdruWQLSx;
      string QEnBZwCtFM;
      string AeIpkXacBU;
      string jYtBUPXQtT;
      string lGAPxFNlyV;
      string eajitKAmGW;
      string wmKyNqKmgK;
      string XkAkZserrf;
      string JnefoIoLGK;
      string OjKXXzwBCF;
      string taFnxtazIB;
      string eIuaMHIdIF;
      string CyfWunacMa;
      string wcplkiipiu;
      string gpDFeGojKQ;
      string pSsxDwthrI;
      string SylgEBRIod;
      if(aPCSDFOpuJ == XkAkZserrf){XRuMXMuZqn = true;}
      else if(XkAkZserrf == aPCSDFOpuJ){euljSMEhLV = true;}
      if(YBIpqCSTMO == JnefoIoLGK){yqRwkdjsio = true;}
      else if(JnefoIoLGK == YBIpqCSTMO){MaGjkuAzBi = true;}
      if(KCnYRhVout == OjKXXzwBCF){nAxZbiDVAd = true;}
      else if(OjKXXzwBCF == KCnYRhVout){KDsiHGIhIN = true;}
      if(oIdruWQLSx == taFnxtazIB){ogtgrXWfZq = true;}
      else if(taFnxtazIB == oIdruWQLSx){YhoXVHZoGy = true;}
      if(QEnBZwCtFM == eIuaMHIdIF){ATpEJbfpwa = true;}
      else if(eIuaMHIdIF == QEnBZwCtFM){LYgVHdtKAm = true;}
      if(AeIpkXacBU == CyfWunacMa){RYZAoXTVkn = true;}
      else if(CyfWunacMa == AeIpkXacBU){ZuaVgaCDbM = true;}
      if(jYtBUPXQtT == wcplkiipiu){IZYNzRxkDM = true;}
      else if(wcplkiipiu == jYtBUPXQtT){EWYywelhOc = true;}
      if(lGAPxFNlyV == gpDFeGojKQ){HETqnTKsPA = true;}
      if(eajitKAmGW == pSsxDwthrI){CMYZLQGsqU = true;}
      if(wmKyNqKmgK == SylgEBRIod){EAukhaubEq = true;}
      while(gpDFeGojKQ == lGAPxFNlyV){UKrCWlVWad = true;}
      while(pSsxDwthrI == pSsxDwthrI){MyhVncHSqt = true;}
      while(SylgEBRIod == SylgEBRIod){FWNttoziZb = true;}
      if(XRuMXMuZqn == true){XRuMXMuZqn = false;}
      if(yqRwkdjsio == true){yqRwkdjsio = false;}
      if(nAxZbiDVAd == true){nAxZbiDVAd = false;}
      if(ogtgrXWfZq == true){ogtgrXWfZq = false;}
      if(ATpEJbfpwa == true){ATpEJbfpwa = false;}
      if(RYZAoXTVkn == true){RYZAoXTVkn = false;}
      if(IZYNzRxkDM == true){IZYNzRxkDM = false;}
      if(HETqnTKsPA == true){HETqnTKsPA = false;}
      if(CMYZLQGsqU == true){CMYZLQGsqU = false;}
      if(EAukhaubEq == true){EAukhaubEq = false;}
      if(euljSMEhLV == true){euljSMEhLV = false;}
      if(MaGjkuAzBi == true){MaGjkuAzBi = false;}
      if(KDsiHGIhIN == true){KDsiHGIhIN = false;}
      if(YhoXVHZoGy == true){YhoXVHZoGy = false;}
      if(LYgVHdtKAm == true){LYgVHdtKAm = false;}
      if(ZuaVgaCDbM == true){ZuaVgaCDbM = false;}
      if(EWYywelhOc == true){EWYywelhOc = false;}
      if(UKrCWlVWad == true){UKrCWlVWad = false;}
      if(MyhVncHSqt == true){MyhVncHSqt = false;}
      if(FWNttoziZb == true){FWNttoziZb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNGDKBRWHS
{ 
  void kRNQmBfBJm()
  { 
      bool ztKOtJQtVI = false;
      bool CihkaFnVYb = false;
      bool qUOfKaMsPm = false;
      bool fffFHFWbui = false;
      bool RhueFjWVyK = false;
      bool snVkYefdDT = false;
      bool xXdibWCcdU = false;
      bool hLZpKIYjZa = false;
      bool EptFsrJtfc = false;
      bool ZrXbksEMCi = false;
      bool gtrdchNfaP = false;
      bool FwEcOHcYoi = false;
      bool NHwBuonxEQ = false;
      bool EMgqtJxQbL = false;
      bool ecTPWcnuMd = false;
      bool QfWTVYyqhn = false;
      bool sQbJLsPNhF = false;
      bool JMwcEjnfdR = false;
      bool BrjaAYoMUU = false;
      bool LGhnRNBJEd = false;
      string PgwtcqmTIy;
      string TwdDXySlDO;
      string ReINMLkmbB;
      string qJHFqCRJjV;
      string wuRdSGTUED;
      string dQLGBkXhhR;
      string FAqGHJoXLV;
      string fJChSWNetF;
      string qQhXXZyAEG;
      string dibSPwDKWJ;
      string RwIiXUOcne;
      string WsmbZoSTig;
      string KnTFqwgjRV;
      string SDHkmuIyAD;
      string LUMYjkwzsa;
      string djapydcDqa;
      string meLRLTlBod;
      string fTSfUpatVG;
      string AhppricQmI;
      string SEHZPgJuNP;
      if(PgwtcqmTIy == RwIiXUOcne){ztKOtJQtVI = true;}
      else if(RwIiXUOcne == PgwtcqmTIy){gtrdchNfaP = true;}
      if(TwdDXySlDO == WsmbZoSTig){CihkaFnVYb = true;}
      else if(WsmbZoSTig == TwdDXySlDO){FwEcOHcYoi = true;}
      if(ReINMLkmbB == KnTFqwgjRV){qUOfKaMsPm = true;}
      else if(KnTFqwgjRV == ReINMLkmbB){NHwBuonxEQ = true;}
      if(qJHFqCRJjV == SDHkmuIyAD){fffFHFWbui = true;}
      else if(SDHkmuIyAD == qJHFqCRJjV){EMgqtJxQbL = true;}
      if(wuRdSGTUED == LUMYjkwzsa){RhueFjWVyK = true;}
      else if(LUMYjkwzsa == wuRdSGTUED){ecTPWcnuMd = true;}
      if(dQLGBkXhhR == djapydcDqa){snVkYefdDT = true;}
      else if(djapydcDqa == dQLGBkXhhR){QfWTVYyqhn = true;}
      if(FAqGHJoXLV == meLRLTlBod){xXdibWCcdU = true;}
      else if(meLRLTlBod == FAqGHJoXLV){sQbJLsPNhF = true;}
      if(fJChSWNetF == fTSfUpatVG){hLZpKIYjZa = true;}
      if(qQhXXZyAEG == AhppricQmI){EptFsrJtfc = true;}
      if(dibSPwDKWJ == SEHZPgJuNP){ZrXbksEMCi = true;}
      while(fTSfUpatVG == fJChSWNetF){JMwcEjnfdR = true;}
      while(AhppricQmI == AhppricQmI){BrjaAYoMUU = true;}
      while(SEHZPgJuNP == SEHZPgJuNP){LGhnRNBJEd = true;}
      if(ztKOtJQtVI == true){ztKOtJQtVI = false;}
      if(CihkaFnVYb == true){CihkaFnVYb = false;}
      if(qUOfKaMsPm == true){qUOfKaMsPm = false;}
      if(fffFHFWbui == true){fffFHFWbui = false;}
      if(RhueFjWVyK == true){RhueFjWVyK = false;}
      if(snVkYefdDT == true){snVkYefdDT = false;}
      if(xXdibWCcdU == true){xXdibWCcdU = false;}
      if(hLZpKIYjZa == true){hLZpKIYjZa = false;}
      if(EptFsrJtfc == true){EptFsrJtfc = false;}
      if(ZrXbksEMCi == true){ZrXbksEMCi = false;}
      if(gtrdchNfaP == true){gtrdchNfaP = false;}
      if(FwEcOHcYoi == true){FwEcOHcYoi = false;}
      if(NHwBuonxEQ == true){NHwBuonxEQ = false;}
      if(EMgqtJxQbL == true){EMgqtJxQbL = false;}
      if(ecTPWcnuMd == true){ecTPWcnuMd = false;}
      if(QfWTVYyqhn == true){QfWTVYyqhn = false;}
      if(sQbJLsPNhF == true){sQbJLsPNhF = false;}
      if(JMwcEjnfdR == true){JMwcEjnfdR = false;}
      if(BrjaAYoMUU == true){BrjaAYoMUU = false;}
      if(LGhnRNBJEd == true){LGhnRNBJEd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQWUSOPSPY
{ 
  void yLjZOHLnMz()
  { 
      bool tbjNBbOXmZ = false;
      bool KRVSRjDTLk = false;
      bool aTAWzZODgZ = false;
      bool oLfDeLXHAY = false;
      bool RtYVEosVfM = false;
      bool RrhkFaaMOb = false;
      bool MKqNkylSnF = false;
      bool MuTlTgteRK = false;
      bool gsXUHwcuyD = false;
      bool kLsYMGDKjG = false;
      bool CahaAVXuRY = false;
      bool gwtDtTmWFn = false;
      bool UqTjTBCuZM = false;
      bool citLHGKwTk = false;
      bool XgcZWnQodr = false;
      bool TgFukLGxGz = false;
      bool TcVFuxCiwn = false;
      bool IpCTQnNtNf = false;
      bool jMRgrwdyZu = false;
      bool AMpTRuLXdY = false;
      string CsliNDlLbc;
      string xQRyBzhWzg;
      string FtxhGpEXnx;
      string ZMzayywQbC;
      string fpBcxwCRwU;
      string mMNuaIwEbW;
      string yNXdDjRpAD;
      string DRuxAOrUjK;
      string nmbTKMzDAp;
      string CqnEDSSWYM;
      string eLQsQVRQuM;
      string PbTRiLlDTp;
      string kNpKALdqsh;
      string uVuXfbVhCo;
      string uiHmZaXVUq;
      string fPCibQUGsF;
      string rZWNQsfwlG;
      string oEAeuBGCjZ;
      string nHVCBfSMuP;
      string HPoxxVMtWf;
      if(CsliNDlLbc == eLQsQVRQuM){tbjNBbOXmZ = true;}
      else if(eLQsQVRQuM == CsliNDlLbc){CahaAVXuRY = true;}
      if(xQRyBzhWzg == PbTRiLlDTp){KRVSRjDTLk = true;}
      else if(PbTRiLlDTp == xQRyBzhWzg){gwtDtTmWFn = true;}
      if(FtxhGpEXnx == kNpKALdqsh){aTAWzZODgZ = true;}
      else if(kNpKALdqsh == FtxhGpEXnx){UqTjTBCuZM = true;}
      if(ZMzayywQbC == uVuXfbVhCo){oLfDeLXHAY = true;}
      else if(uVuXfbVhCo == ZMzayywQbC){citLHGKwTk = true;}
      if(fpBcxwCRwU == uiHmZaXVUq){RtYVEosVfM = true;}
      else if(uiHmZaXVUq == fpBcxwCRwU){XgcZWnQodr = true;}
      if(mMNuaIwEbW == fPCibQUGsF){RrhkFaaMOb = true;}
      else if(fPCibQUGsF == mMNuaIwEbW){TgFukLGxGz = true;}
      if(yNXdDjRpAD == rZWNQsfwlG){MKqNkylSnF = true;}
      else if(rZWNQsfwlG == yNXdDjRpAD){TcVFuxCiwn = true;}
      if(DRuxAOrUjK == oEAeuBGCjZ){MuTlTgteRK = true;}
      if(nmbTKMzDAp == nHVCBfSMuP){gsXUHwcuyD = true;}
      if(CqnEDSSWYM == HPoxxVMtWf){kLsYMGDKjG = true;}
      while(oEAeuBGCjZ == DRuxAOrUjK){IpCTQnNtNf = true;}
      while(nHVCBfSMuP == nHVCBfSMuP){jMRgrwdyZu = true;}
      while(HPoxxVMtWf == HPoxxVMtWf){AMpTRuLXdY = true;}
      if(tbjNBbOXmZ == true){tbjNBbOXmZ = false;}
      if(KRVSRjDTLk == true){KRVSRjDTLk = false;}
      if(aTAWzZODgZ == true){aTAWzZODgZ = false;}
      if(oLfDeLXHAY == true){oLfDeLXHAY = false;}
      if(RtYVEosVfM == true){RtYVEosVfM = false;}
      if(RrhkFaaMOb == true){RrhkFaaMOb = false;}
      if(MKqNkylSnF == true){MKqNkylSnF = false;}
      if(MuTlTgteRK == true){MuTlTgteRK = false;}
      if(gsXUHwcuyD == true){gsXUHwcuyD = false;}
      if(kLsYMGDKjG == true){kLsYMGDKjG = false;}
      if(CahaAVXuRY == true){CahaAVXuRY = false;}
      if(gwtDtTmWFn == true){gwtDtTmWFn = false;}
      if(UqTjTBCuZM == true){UqTjTBCuZM = false;}
      if(citLHGKwTk == true){citLHGKwTk = false;}
      if(XgcZWnQodr == true){XgcZWnQodr = false;}
      if(TgFukLGxGz == true){TgFukLGxGz = false;}
      if(TcVFuxCiwn == true){TcVFuxCiwn = false;}
      if(IpCTQnNtNf == true){IpCTQnNtNf = false;}
      if(jMRgrwdyZu == true){jMRgrwdyZu = false;}
      if(AMpTRuLXdY == true){AMpTRuLXdY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPNQZTVNSN
{ 
  void lyHreIhWrw()
  { 
      bool PEjWAtOurw = false;
      bool yyoFfJcVQr = false;
      bool AkdFmtheRQ = false;
      bool DQkIJCHYGG = false;
      bool fJIIJeSDCj = false;
      bool aDyrXdadjG = false;
      bool MicbsgNfuc = false;
      bool BDOJLqbUuH = false;
      bool adchozRrjf = false;
      bool bcoAtwfgOb = false;
      bool RlIYhXnogg = false;
      bool CFibehGult = false;
      bool OUuPBYONOO = false;
      bool KtFTpoVDAR = false;
      bool KcLDcVtNVL = false;
      bool pkuUMwqsWJ = false;
      bool JaZRVHzOkp = false;
      bool MCuUikJrle = false;
      bool dArCYZzkGt = false;
      bool xbgpHjDsgV = false;
      string zDzrkgGXrP;
      string ksGaNxDPRq;
      string hQZDRHqhjF;
      string dStbZhzUeY;
      string oywxVpsgmf;
      string XreHshdwZc;
      string pYmlkSzdBf;
      string xijrCiTbhb;
      string NJtEhlnliq;
      string DCtBiPLJMD;
      string qPfGhnHlEK;
      string OBOyOfdiEz;
      string dMuJbuniJm;
      string WJOekydmVs;
      string dBgYcCnwmC;
      string kbFNYdUVem;
      string AYcRmEliMQ;
      string CpNKUbfVgZ;
      string GqwHBuEBFH;
      string cHIhsEYOkX;
      if(zDzrkgGXrP == qPfGhnHlEK){PEjWAtOurw = true;}
      else if(qPfGhnHlEK == zDzrkgGXrP){RlIYhXnogg = true;}
      if(ksGaNxDPRq == OBOyOfdiEz){yyoFfJcVQr = true;}
      else if(OBOyOfdiEz == ksGaNxDPRq){CFibehGult = true;}
      if(hQZDRHqhjF == dMuJbuniJm){AkdFmtheRQ = true;}
      else if(dMuJbuniJm == hQZDRHqhjF){OUuPBYONOO = true;}
      if(dStbZhzUeY == WJOekydmVs){DQkIJCHYGG = true;}
      else if(WJOekydmVs == dStbZhzUeY){KtFTpoVDAR = true;}
      if(oywxVpsgmf == dBgYcCnwmC){fJIIJeSDCj = true;}
      else if(dBgYcCnwmC == oywxVpsgmf){KcLDcVtNVL = true;}
      if(XreHshdwZc == kbFNYdUVem){aDyrXdadjG = true;}
      else if(kbFNYdUVem == XreHshdwZc){pkuUMwqsWJ = true;}
      if(pYmlkSzdBf == AYcRmEliMQ){MicbsgNfuc = true;}
      else if(AYcRmEliMQ == pYmlkSzdBf){JaZRVHzOkp = true;}
      if(xijrCiTbhb == CpNKUbfVgZ){BDOJLqbUuH = true;}
      if(NJtEhlnliq == GqwHBuEBFH){adchozRrjf = true;}
      if(DCtBiPLJMD == cHIhsEYOkX){bcoAtwfgOb = true;}
      while(CpNKUbfVgZ == xijrCiTbhb){MCuUikJrle = true;}
      while(GqwHBuEBFH == GqwHBuEBFH){dArCYZzkGt = true;}
      while(cHIhsEYOkX == cHIhsEYOkX){xbgpHjDsgV = true;}
      if(PEjWAtOurw == true){PEjWAtOurw = false;}
      if(yyoFfJcVQr == true){yyoFfJcVQr = false;}
      if(AkdFmtheRQ == true){AkdFmtheRQ = false;}
      if(DQkIJCHYGG == true){DQkIJCHYGG = false;}
      if(fJIIJeSDCj == true){fJIIJeSDCj = false;}
      if(aDyrXdadjG == true){aDyrXdadjG = false;}
      if(MicbsgNfuc == true){MicbsgNfuc = false;}
      if(BDOJLqbUuH == true){BDOJLqbUuH = false;}
      if(adchozRrjf == true){adchozRrjf = false;}
      if(bcoAtwfgOb == true){bcoAtwfgOb = false;}
      if(RlIYhXnogg == true){RlIYhXnogg = false;}
      if(CFibehGult == true){CFibehGult = false;}
      if(OUuPBYONOO == true){OUuPBYONOO = false;}
      if(KtFTpoVDAR == true){KtFTpoVDAR = false;}
      if(KcLDcVtNVL == true){KcLDcVtNVL = false;}
      if(pkuUMwqsWJ == true){pkuUMwqsWJ = false;}
      if(JaZRVHzOkp == true){JaZRVHzOkp = false;}
      if(MCuUikJrle == true){MCuUikJrle = false;}
      if(dArCYZzkGt == true){dArCYZzkGt = false;}
      if(xbgpHjDsgV == true){xbgpHjDsgV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XUFGRBZBFQ
{ 
  void nZFCoHuiSQ()
  { 
      bool txbrSrbAEy = false;
      bool bZhKrwzxhw = false;
      bool mdhrPVQEHJ = false;
      bool IUsVBsaiyq = false;
      bool majjSfewhj = false;
      bool XuRwYQPibw = false;
      bool aWsuoGgLIy = false;
      bool VPzpIMsxZj = false;
      bool pUWWlNDwxk = false;
      bool cqHBPPhotL = false;
      bool zSmiOHuanM = false;
      bool WSIqFGAVIa = false;
      bool DjOXVdHxar = false;
      bool dDCOkXgnIe = false;
      bool RbIjNKhPuJ = false;
      bool PMgTIOEPNj = false;
      bool zyAuhSPtFh = false;
      bool ZMNdIbadKK = false;
      bool uqCRcRWiFW = false;
      bool TQZXeTaNCt = false;
      string LlnhxWeqxN;
      string xMMjLTMsQO;
      string yEAxbsCPEd;
      string UAtkPsCADi;
      string PgdJFBbwjF;
      string eGNNzGkpFD;
      string TPlTswRbTS;
      string RMogyQaqqa;
      string QGeyyOmflI;
      string HMtAOzuJPJ;
      string iAbRnRQfPh;
      string ftyelNknUe;
      string IloKKFSoRy;
      string VQahqQdNJg;
      string xGQEbNNPNB;
      string OGokAxKQGi;
      string zaNQLPSPmV;
      string iWengBUkiw;
      string qCbQiPboht;
      string FNGZgWrzrM;
      if(LlnhxWeqxN == iAbRnRQfPh){txbrSrbAEy = true;}
      else if(iAbRnRQfPh == LlnhxWeqxN){zSmiOHuanM = true;}
      if(xMMjLTMsQO == ftyelNknUe){bZhKrwzxhw = true;}
      else if(ftyelNknUe == xMMjLTMsQO){WSIqFGAVIa = true;}
      if(yEAxbsCPEd == IloKKFSoRy){mdhrPVQEHJ = true;}
      else if(IloKKFSoRy == yEAxbsCPEd){DjOXVdHxar = true;}
      if(UAtkPsCADi == VQahqQdNJg){IUsVBsaiyq = true;}
      else if(VQahqQdNJg == UAtkPsCADi){dDCOkXgnIe = true;}
      if(PgdJFBbwjF == xGQEbNNPNB){majjSfewhj = true;}
      else if(xGQEbNNPNB == PgdJFBbwjF){RbIjNKhPuJ = true;}
      if(eGNNzGkpFD == OGokAxKQGi){XuRwYQPibw = true;}
      else if(OGokAxKQGi == eGNNzGkpFD){PMgTIOEPNj = true;}
      if(TPlTswRbTS == zaNQLPSPmV){aWsuoGgLIy = true;}
      else if(zaNQLPSPmV == TPlTswRbTS){zyAuhSPtFh = true;}
      if(RMogyQaqqa == iWengBUkiw){VPzpIMsxZj = true;}
      if(QGeyyOmflI == qCbQiPboht){pUWWlNDwxk = true;}
      if(HMtAOzuJPJ == FNGZgWrzrM){cqHBPPhotL = true;}
      while(iWengBUkiw == RMogyQaqqa){ZMNdIbadKK = true;}
      while(qCbQiPboht == qCbQiPboht){uqCRcRWiFW = true;}
      while(FNGZgWrzrM == FNGZgWrzrM){TQZXeTaNCt = true;}
      if(txbrSrbAEy == true){txbrSrbAEy = false;}
      if(bZhKrwzxhw == true){bZhKrwzxhw = false;}
      if(mdhrPVQEHJ == true){mdhrPVQEHJ = false;}
      if(IUsVBsaiyq == true){IUsVBsaiyq = false;}
      if(majjSfewhj == true){majjSfewhj = false;}
      if(XuRwYQPibw == true){XuRwYQPibw = false;}
      if(aWsuoGgLIy == true){aWsuoGgLIy = false;}
      if(VPzpIMsxZj == true){VPzpIMsxZj = false;}
      if(pUWWlNDwxk == true){pUWWlNDwxk = false;}
      if(cqHBPPhotL == true){cqHBPPhotL = false;}
      if(zSmiOHuanM == true){zSmiOHuanM = false;}
      if(WSIqFGAVIa == true){WSIqFGAVIa = false;}
      if(DjOXVdHxar == true){DjOXVdHxar = false;}
      if(dDCOkXgnIe == true){dDCOkXgnIe = false;}
      if(RbIjNKhPuJ == true){RbIjNKhPuJ = false;}
      if(PMgTIOEPNj == true){PMgTIOEPNj = false;}
      if(zyAuhSPtFh == true){zyAuhSPtFh = false;}
      if(ZMNdIbadKK == true){ZMNdIbadKK = false;}
      if(uqCRcRWiFW == true){uqCRcRWiFW = false;}
      if(TQZXeTaNCt == true){TQZXeTaNCt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DJBJDRMWTM
{ 
  void weofwCdamu()
  { 
      bool WyRDCkOLKE = false;
      bool QwNsANyKwj = false;
      bool YgfjBqCfGi = false;
      bool NechLTQLpP = false;
      bool VBGLWgYmQH = false;
      bool SopffoRhBK = false;
      bool hhEbqlTfhf = false;
      bool wmTfNXZUMU = false;
      bool SPPzQYowBV = false;
      bool CiJehmweUk = false;
      bool NsFjKfUJSI = false;
      bool OxVgrSSFLS = false;
      bool wXdLdNcoyZ = false;
      bool buAaGYKfnk = false;
      bool DfdsHEMcmP = false;
      bool UpSBopPsFx = false;
      bool CfKrfSxuZS = false;
      bool IlQaOQsjEZ = false;
      bool AACiEkcylQ = false;
      bool JQZqhXUkMn = false;
      string DclDgiLkrA;
      string aSDzzIuuDi;
      string kmfqAtBblO;
      string efKRswUmRf;
      string ysILbsGjkU;
      string cnAFLQwtCl;
      string hjycVuHkGD;
      string nIcXkreTPH;
      string nQpQkpfFFb;
      string zZjfxOtepg;
      string kUdggUKcUT;
      string kcetxQsgre;
      string PCedENYxZV;
      string yzchWSmJjQ;
      string eCklqVuphg;
      string UMmLRhoAbS;
      string wNDyVlzwXe;
      string djxaAMRsmh;
      string ShOsBkMRQn;
      string clgQUQzlQF;
      if(DclDgiLkrA == kUdggUKcUT){WyRDCkOLKE = true;}
      else if(kUdggUKcUT == DclDgiLkrA){NsFjKfUJSI = true;}
      if(aSDzzIuuDi == kcetxQsgre){QwNsANyKwj = true;}
      else if(kcetxQsgre == aSDzzIuuDi){OxVgrSSFLS = true;}
      if(kmfqAtBblO == PCedENYxZV){YgfjBqCfGi = true;}
      else if(PCedENYxZV == kmfqAtBblO){wXdLdNcoyZ = true;}
      if(efKRswUmRf == yzchWSmJjQ){NechLTQLpP = true;}
      else if(yzchWSmJjQ == efKRswUmRf){buAaGYKfnk = true;}
      if(ysILbsGjkU == eCklqVuphg){VBGLWgYmQH = true;}
      else if(eCklqVuphg == ysILbsGjkU){DfdsHEMcmP = true;}
      if(cnAFLQwtCl == UMmLRhoAbS){SopffoRhBK = true;}
      else if(UMmLRhoAbS == cnAFLQwtCl){UpSBopPsFx = true;}
      if(hjycVuHkGD == wNDyVlzwXe){hhEbqlTfhf = true;}
      else if(wNDyVlzwXe == hjycVuHkGD){CfKrfSxuZS = true;}
      if(nIcXkreTPH == djxaAMRsmh){wmTfNXZUMU = true;}
      if(nQpQkpfFFb == ShOsBkMRQn){SPPzQYowBV = true;}
      if(zZjfxOtepg == clgQUQzlQF){CiJehmweUk = true;}
      while(djxaAMRsmh == nIcXkreTPH){IlQaOQsjEZ = true;}
      while(ShOsBkMRQn == ShOsBkMRQn){AACiEkcylQ = true;}
      while(clgQUQzlQF == clgQUQzlQF){JQZqhXUkMn = true;}
      if(WyRDCkOLKE == true){WyRDCkOLKE = false;}
      if(QwNsANyKwj == true){QwNsANyKwj = false;}
      if(YgfjBqCfGi == true){YgfjBqCfGi = false;}
      if(NechLTQLpP == true){NechLTQLpP = false;}
      if(VBGLWgYmQH == true){VBGLWgYmQH = false;}
      if(SopffoRhBK == true){SopffoRhBK = false;}
      if(hhEbqlTfhf == true){hhEbqlTfhf = false;}
      if(wmTfNXZUMU == true){wmTfNXZUMU = false;}
      if(SPPzQYowBV == true){SPPzQYowBV = false;}
      if(CiJehmweUk == true){CiJehmweUk = false;}
      if(NsFjKfUJSI == true){NsFjKfUJSI = false;}
      if(OxVgrSSFLS == true){OxVgrSSFLS = false;}
      if(wXdLdNcoyZ == true){wXdLdNcoyZ = false;}
      if(buAaGYKfnk == true){buAaGYKfnk = false;}
      if(DfdsHEMcmP == true){DfdsHEMcmP = false;}
      if(UpSBopPsFx == true){UpSBopPsFx = false;}
      if(CfKrfSxuZS == true){CfKrfSxuZS = false;}
      if(IlQaOQsjEZ == true){IlQaOQsjEZ = false;}
      if(AACiEkcylQ == true){AACiEkcylQ = false;}
      if(JQZqhXUkMn == true){JQZqhXUkMn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZJEPACJAZ
{ 
  void CAqVJYkgFm()
  { 
      bool MbdAxRodKX = false;
      bool ZuskxdHtVF = false;
      bool mKiloduQQl = false;
      bool NKQUMOXdIH = false;
      bool NXgNrsNFfi = false;
      bool UbyxdCsrLT = false;
      bool VXMYKOeYYh = false;
      bool FckOqOdUsu = false;
      bool PojgQkLSpK = false;
      bool VfSokpKIDc = false;
      bool OogycqpjFO = false;
      bool YXyQDgmeHY = false;
      bool CMhNMZKudB = false;
      bool DURQgaHlEZ = false;
      bool ubMbkxgClE = false;
      bool CfAdZBGTkD = false;
      bool guGELDGhic = false;
      bool YAahdazGbP = false;
      bool sHJYzXUmpe = false;
      bool TnBBrzVIQh = false;
      string DsOKMDVZOR;
      string YXXqrgHSjM;
      string iMHrJeXcUb;
      string dDmkwTgLul;
      string nATojkfQYa;
      string OToydqkVAg;
      string esFlmVkluX;
      string zwWxYhrRHY;
      string yHDsNKOoHE;
      string iKKNHtuhBO;
      string AtUAbSwqYu;
      string zSNbiXpLYc;
      string GueponkJpd;
      string mKQsXElCRt;
      string OWPLFPwiei;
      string EiIYHFOdLn;
      string glBuIoCUEd;
      string lmteNieSkZ;
      string qCeGYDBqlR;
      string oHqcNbVUCQ;
      if(DsOKMDVZOR == AtUAbSwqYu){MbdAxRodKX = true;}
      else if(AtUAbSwqYu == DsOKMDVZOR){OogycqpjFO = true;}
      if(YXXqrgHSjM == zSNbiXpLYc){ZuskxdHtVF = true;}
      else if(zSNbiXpLYc == YXXqrgHSjM){YXyQDgmeHY = true;}
      if(iMHrJeXcUb == GueponkJpd){mKiloduQQl = true;}
      else if(GueponkJpd == iMHrJeXcUb){CMhNMZKudB = true;}
      if(dDmkwTgLul == mKQsXElCRt){NKQUMOXdIH = true;}
      else if(mKQsXElCRt == dDmkwTgLul){DURQgaHlEZ = true;}
      if(nATojkfQYa == OWPLFPwiei){NXgNrsNFfi = true;}
      else if(OWPLFPwiei == nATojkfQYa){ubMbkxgClE = true;}
      if(OToydqkVAg == EiIYHFOdLn){UbyxdCsrLT = true;}
      else if(EiIYHFOdLn == OToydqkVAg){CfAdZBGTkD = true;}
      if(esFlmVkluX == glBuIoCUEd){VXMYKOeYYh = true;}
      else if(glBuIoCUEd == esFlmVkluX){guGELDGhic = true;}
      if(zwWxYhrRHY == lmteNieSkZ){FckOqOdUsu = true;}
      if(yHDsNKOoHE == qCeGYDBqlR){PojgQkLSpK = true;}
      if(iKKNHtuhBO == oHqcNbVUCQ){VfSokpKIDc = true;}
      while(lmteNieSkZ == zwWxYhrRHY){YAahdazGbP = true;}
      while(qCeGYDBqlR == qCeGYDBqlR){sHJYzXUmpe = true;}
      while(oHqcNbVUCQ == oHqcNbVUCQ){TnBBrzVIQh = true;}
      if(MbdAxRodKX == true){MbdAxRodKX = false;}
      if(ZuskxdHtVF == true){ZuskxdHtVF = false;}
      if(mKiloduQQl == true){mKiloduQQl = false;}
      if(NKQUMOXdIH == true){NKQUMOXdIH = false;}
      if(NXgNrsNFfi == true){NXgNrsNFfi = false;}
      if(UbyxdCsrLT == true){UbyxdCsrLT = false;}
      if(VXMYKOeYYh == true){VXMYKOeYYh = false;}
      if(FckOqOdUsu == true){FckOqOdUsu = false;}
      if(PojgQkLSpK == true){PojgQkLSpK = false;}
      if(VfSokpKIDc == true){VfSokpKIDc = false;}
      if(OogycqpjFO == true){OogycqpjFO = false;}
      if(YXyQDgmeHY == true){YXyQDgmeHY = false;}
      if(CMhNMZKudB == true){CMhNMZKudB = false;}
      if(DURQgaHlEZ == true){DURQgaHlEZ = false;}
      if(ubMbkxgClE == true){ubMbkxgClE = false;}
      if(CfAdZBGTkD == true){CfAdZBGTkD = false;}
      if(guGELDGhic == true){guGELDGhic = false;}
      if(YAahdazGbP == true){YAahdazGbP = false;}
      if(sHJYzXUmpe == true){sHJYzXUmpe = false;}
      if(TnBBrzVIQh == true){TnBBrzVIQh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCTYYPIALX
{ 
  void RJZuYMXGqO()
  { 
      bool IoqUhkqctO = false;
      bool JQshaPaVhZ = false;
      bool fnQEtRKdig = false;
      bool WnBYfurOja = false;
      bool iRfDcZCJik = false;
      bool lbyOeUYlaP = false;
      bool aMsNqUPUCf = false;
      bool XLlGpNHMbT = false;
      bool OBuxutomtL = false;
      bool VFnTAWYSMH = false;
      bool JhGDNZpqXQ = false;
      bool MLKGBYRuSx = false;
      bool fcapJRXSFS = false;
      bool ooAUKgtrjU = false;
      bool EyOczKuhRa = false;
      bool FczPbgGQtu = false;
      bool CXkEaWKpwU = false;
      bool eZLxrgOxpy = false;
      bool WoAeNMpkrd = false;
      bool ZcynSgMJCc = false;
      string xWYiJVMcpw;
      string nsSwPRtgub;
      string dHWokrJwfn;
      string DpZsIBwnEw;
      string VkBzqtJlxp;
      string WdBCzoAjyQ;
      string LQxCryTYnN;
      string VGcyGsGWxq;
      string hXyoQZoXtT;
      string BMomjFmyHs;
      string ZkxjUPACuF;
      string hdmHhnRIkS;
      string IwdUMJQoNA;
      string FHODQxZOUA;
      string YmbnkWYhFw;
      string neNnjdGcWK;
      string zLnuAZOiqk;
      string OCnktVUoio;
      string jijRMataSl;
      string pwqJBNyfnK;
      if(xWYiJVMcpw == ZkxjUPACuF){IoqUhkqctO = true;}
      else if(ZkxjUPACuF == xWYiJVMcpw){JhGDNZpqXQ = true;}
      if(nsSwPRtgub == hdmHhnRIkS){JQshaPaVhZ = true;}
      else if(hdmHhnRIkS == nsSwPRtgub){MLKGBYRuSx = true;}
      if(dHWokrJwfn == IwdUMJQoNA){fnQEtRKdig = true;}
      else if(IwdUMJQoNA == dHWokrJwfn){fcapJRXSFS = true;}
      if(DpZsIBwnEw == FHODQxZOUA){WnBYfurOja = true;}
      else if(FHODQxZOUA == DpZsIBwnEw){ooAUKgtrjU = true;}
      if(VkBzqtJlxp == YmbnkWYhFw){iRfDcZCJik = true;}
      else if(YmbnkWYhFw == VkBzqtJlxp){EyOczKuhRa = true;}
      if(WdBCzoAjyQ == neNnjdGcWK){lbyOeUYlaP = true;}
      else if(neNnjdGcWK == WdBCzoAjyQ){FczPbgGQtu = true;}
      if(LQxCryTYnN == zLnuAZOiqk){aMsNqUPUCf = true;}
      else if(zLnuAZOiqk == LQxCryTYnN){CXkEaWKpwU = true;}
      if(VGcyGsGWxq == OCnktVUoio){XLlGpNHMbT = true;}
      if(hXyoQZoXtT == jijRMataSl){OBuxutomtL = true;}
      if(BMomjFmyHs == pwqJBNyfnK){VFnTAWYSMH = true;}
      while(OCnktVUoio == VGcyGsGWxq){eZLxrgOxpy = true;}
      while(jijRMataSl == jijRMataSl){WoAeNMpkrd = true;}
      while(pwqJBNyfnK == pwqJBNyfnK){ZcynSgMJCc = true;}
      if(IoqUhkqctO == true){IoqUhkqctO = false;}
      if(JQshaPaVhZ == true){JQshaPaVhZ = false;}
      if(fnQEtRKdig == true){fnQEtRKdig = false;}
      if(WnBYfurOja == true){WnBYfurOja = false;}
      if(iRfDcZCJik == true){iRfDcZCJik = false;}
      if(lbyOeUYlaP == true){lbyOeUYlaP = false;}
      if(aMsNqUPUCf == true){aMsNqUPUCf = false;}
      if(XLlGpNHMbT == true){XLlGpNHMbT = false;}
      if(OBuxutomtL == true){OBuxutomtL = false;}
      if(VFnTAWYSMH == true){VFnTAWYSMH = false;}
      if(JhGDNZpqXQ == true){JhGDNZpqXQ = false;}
      if(MLKGBYRuSx == true){MLKGBYRuSx = false;}
      if(fcapJRXSFS == true){fcapJRXSFS = false;}
      if(ooAUKgtrjU == true){ooAUKgtrjU = false;}
      if(EyOczKuhRa == true){EyOczKuhRa = false;}
      if(FczPbgGQtu == true){FczPbgGQtu = false;}
      if(CXkEaWKpwU == true){CXkEaWKpwU = false;}
      if(eZLxrgOxpy == true){eZLxrgOxpy = false;}
      if(WoAeNMpkrd == true){WoAeNMpkrd = false;}
      if(ZcynSgMJCc == true){ZcynSgMJCc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMXTDRIRTJ
{ 
  void zkkIDPnrot()
  { 
      bool rbnseeLSdY = false;
      bool yfJKcDgUGj = false;
      bool tIfFwyzbmM = false;
      bool ygNepakhNx = false;
      bool mTeLYOBdux = false;
      bool UzcZxiuiwf = false;
      bool fjeRaQReTB = false;
      bool RzHJxadUgh = false;
      bool wUfoqyDmgG = false;
      bool fCkgRDnMkH = false;
      bool wWJsfVrTcW = false;
      bool FZBOjKDpZb = false;
      bool MdxMVOOaqt = false;
      bool mQjYkZKlJV = false;
      bool FjKKBFAWxH = false;
      bool AymIuSYwXR = false;
      bool HRciiopccJ = false;
      bool zQfEVcTmLP = false;
      bool NqcjsodadS = false;
      bool AONrOnHaaM = false;
      string raNiSOJbJl;
      string UEadgjJWfN;
      string kEnwdFrVos;
      string hpRQkNCklL;
      string cFoVYohWDI;
      string sENQamlQEM;
      string WmmQDdmJsS;
      string gXjUkePSXo;
      string WVRgzdbApx;
      string blgZnoSXRt;
      string CXcjbUTsfu;
      string XSsPoBVGRY;
      string ClTwquqKfw;
      string LqBcmyrgFd;
      string KiTtYJrQjm;
      string SMFrrPEgrf;
      string cINjjfQQcp;
      string InAmOTRYXh;
      string CZarczlIjW;
      string tKnYACUjKr;
      if(raNiSOJbJl == CXcjbUTsfu){rbnseeLSdY = true;}
      else if(CXcjbUTsfu == raNiSOJbJl){wWJsfVrTcW = true;}
      if(UEadgjJWfN == XSsPoBVGRY){yfJKcDgUGj = true;}
      else if(XSsPoBVGRY == UEadgjJWfN){FZBOjKDpZb = true;}
      if(kEnwdFrVos == ClTwquqKfw){tIfFwyzbmM = true;}
      else if(ClTwquqKfw == kEnwdFrVos){MdxMVOOaqt = true;}
      if(hpRQkNCklL == LqBcmyrgFd){ygNepakhNx = true;}
      else if(LqBcmyrgFd == hpRQkNCklL){mQjYkZKlJV = true;}
      if(cFoVYohWDI == KiTtYJrQjm){mTeLYOBdux = true;}
      else if(KiTtYJrQjm == cFoVYohWDI){FjKKBFAWxH = true;}
      if(sENQamlQEM == SMFrrPEgrf){UzcZxiuiwf = true;}
      else if(SMFrrPEgrf == sENQamlQEM){AymIuSYwXR = true;}
      if(WmmQDdmJsS == cINjjfQQcp){fjeRaQReTB = true;}
      else if(cINjjfQQcp == WmmQDdmJsS){HRciiopccJ = true;}
      if(gXjUkePSXo == InAmOTRYXh){RzHJxadUgh = true;}
      if(WVRgzdbApx == CZarczlIjW){wUfoqyDmgG = true;}
      if(blgZnoSXRt == tKnYACUjKr){fCkgRDnMkH = true;}
      while(InAmOTRYXh == gXjUkePSXo){zQfEVcTmLP = true;}
      while(CZarczlIjW == CZarczlIjW){NqcjsodadS = true;}
      while(tKnYACUjKr == tKnYACUjKr){AONrOnHaaM = true;}
      if(rbnseeLSdY == true){rbnseeLSdY = false;}
      if(yfJKcDgUGj == true){yfJKcDgUGj = false;}
      if(tIfFwyzbmM == true){tIfFwyzbmM = false;}
      if(ygNepakhNx == true){ygNepakhNx = false;}
      if(mTeLYOBdux == true){mTeLYOBdux = false;}
      if(UzcZxiuiwf == true){UzcZxiuiwf = false;}
      if(fjeRaQReTB == true){fjeRaQReTB = false;}
      if(RzHJxadUgh == true){RzHJxadUgh = false;}
      if(wUfoqyDmgG == true){wUfoqyDmgG = false;}
      if(fCkgRDnMkH == true){fCkgRDnMkH = false;}
      if(wWJsfVrTcW == true){wWJsfVrTcW = false;}
      if(FZBOjKDpZb == true){FZBOjKDpZb = false;}
      if(MdxMVOOaqt == true){MdxMVOOaqt = false;}
      if(mQjYkZKlJV == true){mQjYkZKlJV = false;}
      if(FjKKBFAWxH == true){FjKKBFAWxH = false;}
      if(AymIuSYwXR == true){AymIuSYwXR = false;}
      if(HRciiopccJ == true){HRciiopccJ = false;}
      if(zQfEVcTmLP == true){zQfEVcTmLP = false;}
      if(NqcjsodadS == true){NqcjsodadS = false;}
      if(AONrOnHaaM == true){AONrOnHaaM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMWKHGDCDO
{ 
  void BGOnQwwQqP()
  { 
      bool VscFdWitrw = false;
      bool nYDopleytL = false;
      bool kpjGRNmAGA = false;
      bool AWDEQlLPsi = false;
      bool DhGUchQaMO = false;
      bool JuTwhfIWmP = false;
      bool ihmrwRVyYE = false;
      bool ZOEKHCiPdj = false;
      bool wLnrpFDGWk = false;
      bool coccAUtNYK = false;
      bool MSCInupIof = false;
      bool wsrDSWtuBq = false;
      bool OObnbjlbKl = false;
      bool HVqTWdJeDu = false;
      bool OtRqnixYJc = false;
      bool azMhwxqOgD = false;
      bool JOxCXaCYfo = false;
      bool NOqGbTwkzr = false;
      bool mMRgLIJIWY = false;
      bool luyAlAwPSM = false;
      string wtyIEwnADP;
      string RaoPaFxIRp;
      string GlefgrpXAV;
      string sqfsjwXqJu;
      string mPUjYSxMEe;
      string ZAZjOJPRbM;
      string GQzhWZuufd;
      string gGyWDqRtHN;
      string tcTVwrRudZ;
      string fGOxoWQmNz;
      string XCgZxSCDgX;
      string rVKNRcwcke;
      string IzRFxaqBhf;
      string ZegHorusYc;
      string pOOFgKuBeL;
      string ZmBhpYjbbV;
      string bAUAyNoCXZ;
      string hDEHotjLXm;
      string eoVWFlcyRQ;
      string HTQDBosNHT;
      if(wtyIEwnADP == XCgZxSCDgX){VscFdWitrw = true;}
      else if(XCgZxSCDgX == wtyIEwnADP){MSCInupIof = true;}
      if(RaoPaFxIRp == rVKNRcwcke){nYDopleytL = true;}
      else if(rVKNRcwcke == RaoPaFxIRp){wsrDSWtuBq = true;}
      if(GlefgrpXAV == IzRFxaqBhf){kpjGRNmAGA = true;}
      else if(IzRFxaqBhf == GlefgrpXAV){OObnbjlbKl = true;}
      if(sqfsjwXqJu == ZegHorusYc){AWDEQlLPsi = true;}
      else if(ZegHorusYc == sqfsjwXqJu){HVqTWdJeDu = true;}
      if(mPUjYSxMEe == pOOFgKuBeL){DhGUchQaMO = true;}
      else if(pOOFgKuBeL == mPUjYSxMEe){OtRqnixYJc = true;}
      if(ZAZjOJPRbM == ZmBhpYjbbV){JuTwhfIWmP = true;}
      else if(ZmBhpYjbbV == ZAZjOJPRbM){azMhwxqOgD = true;}
      if(GQzhWZuufd == bAUAyNoCXZ){ihmrwRVyYE = true;}
      else if(bAUAyNoCXZ == GQzhWZuufd){JOxCXaCYfo = true;}
      if(gGyWDqRtHN == hDEHotjLXm){ZOEKHCiPdj = true;}
      if(tcTVwrRudZ == eoVWFlcyRQ){wLnrpFDGWk = true;}
      if(fGOxoWQmNz == HTQDBosNHT){coccAUtNYK = true;}
      while(hDEHotjLXm == gGyWDqRtHN){NOqGbTwkzr = true;}
      while(eoVWFlcyRQ == eoVWFlcyRQ){mMRgLIJIWY = true;}
      while(HTQDBosNHT == HTQDBosNHT){luyAlAwPSM = true;}
      if(VscFdWitrw == true){VscFdWitrw = false;}
      if(nYDopleytL == true){nYDopleytL = false;}
      if(kpjGRNmAGA == true){kpjGRNmAGA = false;}
      if(AWDEQlLPsi == true){AWDEQlLPsi = false;}
      if(DhGUchQaMO == true){DhGUchQaMO = false;}
      if(JuTwhfIWmP == true){JuTwhfIWmP = false;}
      if(ihmrwRVyYE == true){ihmrwRVyYE = false;}
      if(ZOEKHCiPdj == true){ZOEKHCiPdj = false;}
      if(wLnrpFDGWk == true){wLnrpFDGWk = false;}
      if(coccAUtNYK == true){coccAUtNYK = false;}
      if(MSCInupIof == true){MSCInupIof = false;}
      if(wsrDSWtuBq == true){wsrDSWtuBq = false;}
      if(OObnbjlbKl == true){OObnbjlbKl = false;}
      if(HVqTWdJeDu == true){HVqTWdJeDu = false;}
      if(OtRqnixYJc == true){OtRqnixYJc = false;}
      if(azMhwxqOgD == true){azMhwxqOgD = false;}
      if(JOxCXaCYfo == true){JOxCXaCYfo = false;}
      if(NOqGbTwkzr == true){NOqGbTwkzr = false;}
      if(mMRgLIJIWY == true){mMRgLIJIWY = false;}
      if(luyAlAwPSM == true){luyAlAwPSM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRXRGGPXMA
{ 
  void gJBsnCBzuD()
  { 
      bool JDmaEmtDaV = false;
      bool SSbIZJbcyd = false;
      bool MXaNhGRQcS = false;
      bool ZWpThPynXX = false;
      bool ngTcUxGSme = false;
      bool llslClcYrx = false;
      bool VcaHuucIZJ = false;
      bool LmFapeEysk = false;
      bool AydxgndEQw = false;
      bool mYuaBKGLgY = false;
      bool UxscTygSuW = false;
      bool hdeHwWzcZH = false;
      bool RXqcVlreYf = false;
      bool YrQTPCFAdh = false;
      bool GLItOIsnde = false;
      bool LdlZHwGPGg = false;
      bool GCsPyoNLrt = false;
      bool RyyqAGPwON = false;
      bool sDAsTtGqMS = false;
      bool wpsxbERswY = false;
      string cVdZdLGgHn;
      string kSJJbmhJTQ;
      string IyHMknYlyE;
      string TbzdwKdzFR;
      string WrXMfRoVmA;
      string CjewheOQoo;
      string mTiCUITeNR;
      string JiEBtPatgS;
      string zCyxCixDuQ;
      string wMJPeCJUrW;
      string yJIVpTecBS;
      string DTjVojVkAk;
      string KQjwUwYoWr;
      string GFBKUptcGi;
      string DUBcNbcnZt;
      string gXUHLgZLBs;
      string tpFJMxRZBz;
      string psdRgpOGir;
      string TkObLhktym;
      string QiaNnNPqQP;
      if(cVdZdLGgHn == yJIVpTecBS){JDmaEmtDaV = true;}
      else if(yJIVpTecBS == cVdZdLGgHn){UxscTygSuW = true;}
      if(kSJJbmhJTQ == DTjVojVkAk){SSbIZJbcyd = true;}
      else if(DTjVojVkAk == kSJJbmhJTQ){hdeHwWzcZH = true;}
      if(IyHMknYlyE == KQjwUwYoWr){MXaNhGRQcS = true;}
      else if(KQjwUwYoWr == IyHMknYlyE){RXqcVlreYf = true;}
      if(TbzdwKdzFR == GFBKUptcGi){ZWpThPynXX = true;}
      else if(GFBKUptcGi == TbzdwKdzFR){YrQTPCFAdh = true;}
      if(WrXMfRoVmA == DUBcNbcnZt){ngTcUxGSme = true;}
      else if(DUBcNbcnZt == WrXMfRoVmA){GLItOIsnde = true;}
      if(CjewheOQoo == gXUHLgZLBs){llslClcYrx = true;}
      else if(gXUHLgZLBs == CjewheOQoo){LdlZHwGPGg = true;}
      if(mTiCUITeNR == tpFJMxRZBz){VcaHuucIZJ = true;}
      else if(tpFJMxRZBz == mTiCUITeNR){GCsPyoNLrt = true;}
      if(JiEBtPatgS == psdRgpOGir){LmFapeEysk = true;}
      if(zCyxCixDuQ == TkObLhktym){AydxgndEQw = true;}
      if(wMJPeCJUrW == QiaNnNPqQP){mYuaBKGLgY = true;}
      while(psdRgpOGir == JiEBtPatgS){RyyqAGPwON = true;}
      while(TkObLhktym == TkObLhktym){sDAsTtGqMS = true;}
      while(QiaNnNPqQP == QiaNnNPqQP){wpsxbERswY = true;}
      if(JDmaEmtDaV == true){JDmaEmtDaV = false;}
      if(SSbIZJbcyd == true){SSbIZJbcyd = false;}
      if(MXaNhGRQcS == true){MXaNhGRQcS = false;}
      if(ZWpThPynXX == true){ZWpThPynXX = false;}
      if(ngTcUxGSme == true){ngTcUxGSme = false;}
      if(llslClcYrx == true){llslClcYrx = false;}
      if(VcaHuucIZJ == true){VcaHuucIZJ = false;}
      if(LmFapeEysk == true){LmFapeEysk = false;}
      if(AydxgndEQw == true){AydxgndEQw = false;}
      if(mYuaBKGLgY == true){mYuaBKGLgY = false;}
      if(UxscTygSuW == true){UxscTygSuW = false;}
      if(hdeHwWzcZH == true){hdeHwWzcZH = false;}
      if(RXqcVlreYf == true){RXqcVlreYf = false;}
      if(YrQTPCFAdh == true){YrQTPCFAdh = false;}
      if(GLItOIsnde == true){GLItOIsnde = false;}
      if(LdlZHwGPGg == true){LdlZHwGPGg = false;}
      if(GCsPyoNLrt == true){GCsPyoNLrt = false;}
      if(RyyqAGPwON == true){RyyqAGPwON = false;}
      if(sDAsTtGqMS == true){sDAsTtGqMS = false;}
      if(wpsxbERswY == true){wpsxbERswY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVXDIEEGDP
{ 
  void gEYxDGhFqV()
  { 
      bool mJJOrZwmBG = false;
      bool YKZfQJerwS = false;
      bool xFMEDRsIJi = false;
      bool UTdXIndigZ = false;
      bool LfmTJMzdJk = false;
      bool rGLgTgxFKa = false;
      bool gndSkEgBXc = false;
      bool fuKWGRRrtq = false;
      bool ROyXqNIwEa = false;
      bool qXXFrXCUiE = false;
      bool fxGgFwwnaC = false;
      bool PEKTJRpFaW = false;
      bool wjxwkHWFdi = false;
      bool OxJoLTIRSt = false;
      bool RTVBLlMDwZ = false;
      bool hwsLIuAJuy = false;
      bool YqKrmSuUIo = false;
      bool JXmgFcOuky = false;
      bool tSIEARDxgP = false;
      bool TyVUUaJdOs = false;
      string ptMJpMsPgV;
      string ZVweiVOpuE;
      string XLrISwDIqK;
      string AtGArcoKXW;
      string FdKhszpaNp;
      string kiAZJeBDpt;
      string IkYVVfOwlG;
      string gESXysAJOT;
      string FctAYQsgqN;
      string alTdOUEnMN;
      string jsnHJgQbaP;
      string droWnepYwF;
      string lhEYeujnJd;
      string nMwBjMnmpr;
      string zRFaiiwwpi;
      string dfrHaBnPbO;
      string xcSxaRumma;
      string pDiEFUcdow;
      string ymyZAIToah;
      string XYKatWzIzR;
      if(ptMJpMsPgV == jsnHJgQbaP){mJJOrZwmBG = true;}
      else if(jsnHJgQbaP == ptMJpMsPgV){fxGgFwwnaC = true;}
      if(ZVweiVOpuE == droWnepYwF){YKZfQJerwS = true;}
      else if(droWnepYwF == ZVweiVOpuE){PEKTJRpFaW = true;}
      if(XLrISwDIqK == lhEYeujnJd){xFMEDRsIJi = true;}
      else if(lhEYeujnJd == XLrISwDIqK){wjxwkHWFdi = true;}
      if(AtGArcoKXW == nMwBjMnmpr){UTdXIndigZ = true;}
      else if(nMwBjMnmpr == AtGArcoKXW){OxJoLTIRSt = true;}
      if(FdKhszpaNp == zRFaiiwwpi){LfmTJMzdJk = true;}
      else if(zRFaiiwwpi == FdKhszpaNp){RTVBLlMDwZ = true;}
      if(kiAZJeBDpt == dfrHaBnPbO){rGLgTgxFKa = true;}
      else if(dfrHaBnPbO == kiAZJeBDpt){hwsLIuAJuy = true;}
      if(IkYVVfOwlG == xcSxaRumma){gndSkEgBXc = true;}
      else if(xcSxaRumma == IkYVVfOwlG){YqKrmSuUIo = true;}
      if(gESXysAJOT == pDiEFUcdow){fuKWGRRrtq = true;}
      if(FctAYQsgqN == ymyZAIToah){ROyXqNIwEa = true;}
      if(alTdOUEnMN == XYKatWzIzR){qXXFrXCUiE = true;}
      while(pDiEFUcdow == gESXysAJOT){JXmgFcOuky = true;}
      while(ymyZAIToah == ymyZAIToah){tSIEARDxgP = true;}
      while(XYKatWzIzR == XYKatWzIzR){TyVUUaJdOs = true;}
      if(mJJOrZwmBG == true){mJJOrZwmBG = false;}
      if(YKZfQJerwS == true){YKZfQJerwS = false;}
      if(xFMEDRsIJi == true){xFMEDRsIJi = false;}
      if(UTdXIndigZ == true){UTdXIndigZ = false;}
      if(LfmTJMzdJk == true){LfmTJMzdJk = false;}
      if(rGLgTgxFKa == true){rGLgTgxFKa = false;}
      if(gndSkEgBXc == true){gndSkEgBXc = false;}
      if(fuKWGRRrtq == true){fuKWGRRrtq = false;}
      if(ROyXqNIwEa == true){ROyXqNIwEa = false;}
      if(qXXFrXCUiE == true){qXXFrXCUiE = false;}
      if(fxGgFwwnaC == true){fxGgFwwnaC = false;}
      if(PEKTJRpFaW == true){PEKTJRpFaW = false;}
      if(wjxwkHWFdi == true){wjxwkHWFdi = false;}
      if(OxJoLTIRSt == true){OxJoLTIRSt = false;}
      if(RTVBLlMDwZ == true){RTVBLlMDwZ = false;}
      if(hwsLIuAJuy == true){hwsLIuAJuy = false;}
      if(YqKrmSuUIo == true){YqKrmSuUIo = false;}
      if(JXmgFcOuky == true){JXmgFcOuky = false;}
      if(tSIEARDxgP == true){tSIEARDxgP = false;}
      if(TyVUUaJdOs == true){TyVUUaJdOs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JADJMCCSVC
{ 
  void xbNaOcNlCA()
  { 
      bool wiIMQwBLLC = false;
      bool IxfxFLDRuP = false;
      bool prrECTHMkH = false;
      bool YxSUiIbaeV = false;
      bool SUqSWHWQhU = false;
      bool XZORkDqDKx = false;
      bool nnaDcKeLOw = false;
      bool jblZxUBZgu = false;
      bool wpeQiyiAje = false;
      bool RXQhgdtmoM = false;
      bool bLCkkwnnUP = false;
      bool CRVOAxJKUd = false;
      bool aebieLKDrS = false;
      bool ZNjUTknsem = false;
      bool KueTcACChi = false;
      bool TjRKkxjTFY = false;
      bool kjuBpngAuO = false;
      bool JPehSfzHFe = false;
      bool JIVJyouYjW = false;
      bool BTnGBazdcn = false;
      string gDRNFoMqff;
      string oqVdeGHzBP;
      string tLPomZrCmh;
      string IRpfDWXBKh;
      string toYUMuFuIS;
      string eoPUJVmcZe;
      string wKEyWWAoaH;
      string iFnTVFlubr;
      string UxtTCTBVWg;
      string jubfkjkZxo;
      string uQTBjZAwzE;
      string irAhKzPjuC;
      string VdSsWmdIhk;
      string ULxmwDcsjc;
      string TFWRyqusUl;
      string TAetSQyadw;
      string uqNNjWuMkH;
      string VWzSiQHAuf;
      string qjnwRTgCUf;
      string ECOmgbqJha;
      if(gDRNFoMqff == uQTBjZAwzE){wiIMQwBLLC = true;}
      else if(uQTBjZAwzE == gDRNFoMqff){bLCkkwnnUP = true;}
      if(oqVdeGHzBP == irAhKzPjuC){IxfxFLDRuP = true;}
      else if(irAhKzPjuC == oqVdeGHzBP){CRVOAxJKUd = true;}
      if(tLPomZrCmh == VdSsWmdIhk){prrECTHMkH = true;}
      else if(VdSsWmdIhk == tLPomZrCmh){aebieLKDrS = true;}
      if(IRpfDWXBKh == ULxmwDcsjc){YxSUiIbaeV = true;}
      else if(ULxmwDcsjc == IRpfDWXBKh){ZNjUTknsem = true;}
      if(toYUMuFuIS == TFWRyqusUl){SUqSWHWQhU = true;}
      else if(TFWRyqusUl == toYUMuFuIS){KueTcACChi = true;}
      if(eoPUJVmcZe == TAetSQyadw){XZORkDqDKx = true;}
      else if(TAetSQyadw == eoPUJVmcZe){TjRKkxjTFY = true;}
      if(wKEyWWAoaH == uqNNjWuMkH){nnaDcKeLOw = true;}
      else if(uqNNjWuMkH == wKEyWWAoaH){kjuBpngAuO = true;}
      if(iFnTVFlubr == VWzSiQHAuf){jblZxUBZgu = true;}
      if(UxtTCTBVWg == qjnwRTgCUf){wpeQiyiAje = true;}
      if(jubfkjkZxo == ECOmgbqJha){RXQhgdtmoM = true;}
      while(VWzSiQHAuf == iFnTVFlubr){JPehSfzHFe = true;}
      while(qjnwRTgCUf == qjnwRTgCUf){JIVJyouYjW = true;}
      while(ECOmgbqJha == ECOmgbqJha){BTnGBazdcn = true;}
      if(wiIMQwBLLC == true){wiIMQwBLLC = false;}
      if(IxfxFLDRuP == true){IxfxFLDRuP = false;}
      if(prrECTHMkH == true){prrECTHMkH = false;}
      if(YxSUiIbaeV == true){YxSUiIbaeV = false;}
      if(SUqSWHWQhU == true){SUqSWHWQhU = false;}
      if(XZORkDqDKx == true){XZORkDqDKx = false;}
      if(nnaDcKeLOw == true){nnaDcKeLOw = false;}
      if(jblZxUBZgu == true){jblZxUBZgu = false;}
      if(wpeQiyiAje == true){wpeQiyiAje = false;}
      if(RXQhgdtmoM == true){RXQhgdtmoM = false;}
      if(bLCkkwnnUP == true){bLCkkwnnUP = false;}
      if(CRVOAxJKUd == true){CRVOAxJKUd = false;}
      if(aebieLKDrS == true){aebieLKDrS = false;}
      if(ZNjUTknsem == true){ZNjUTknsem = false;}
      if(KueTcACChi == true){KueTcACChi = false;}
      if(TjRKkxjTFY == true){TjRKkxjTFY = false;}
      if(kjuBpngAuO == true){kjuBpngAuO = false;}
      if(JPehSfzHFe == true){JPehSfzHFe = false;}
      if(JIVJyouYjW == true){JIVJyouYjW = false;}
      if(BTnGBazdcn == true){BTnGBazdcn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHYLARLTJJ
{ 
  void IOtHsdmkRY()
  { 
      bool LwJifRNmHG = false;
      bool yxnMWDeXOj = false;
      bool NfkhWaRoaR = false;
      bool DjIjNbDVHW = false;
      bool UeVdFkARtO = false;
      bool GHyzPfKbMF = false;
      bool AYLoCNoEzu = false;
      bool AJPqOiKHcl = false;
      bool aztMLwlJTg = false;
      bool RbICWwTfbq = false;
      bool uuSzNxqGjg = false;
      bool VDyaeBdydG = false;
      bool bfjRcYANUS = false;
      bool OdfkpegtzO = false;
      bool EeYmLOchWV = false;
      bool SVCUPPLAWo = false;
      bool wdkRRqWMjz = false;
      bool TiyPBwGxFO = false;
      bool uSpzzsbKVa = false;
      bool TfXKRasHUU = false;
      string iMXrEVLTEQ;
      string nrTiKQNUIX;
      string MylfAQzxwV;
      string qWIxXuIYHW;
      string qOqLkrHjxu;
      string NqhlVjZrrn;
      string VOWiZRiWKP;
      string HnMkfxGatH;
      string JPzBHzoVam;
      string UQfSBcrIkT;
      string IkYhmYdwGY;
      string dzxjdFOVbZ;
      string cNuWuqIsjD;
      string FyoayYpRNh;
      string VrPCJVSuou;
      string OVfLpupClw;
      string QjMDTfJVlF;
      string OwHsDjxrNY;
      string YMEnniRdjD;
      string ineRRlfMid;
      if(iMXrEVLTEQ == IkYhmYdwGY){LwJifRNmHG = true;}
      else if(IkYhmYdwGY == iMXrEVLTEQ){uuSzNxqGjg = true;}
      if(nrTiKQNUIX == dzxjdFOVbZ){yxnMWDeXOj = true;}
      else if(dzxjdFOVbZ == nrTiKQNUIX){VDyaeBdydG = true;}
      if(MylfAQzxwV == cNuWuqIsjD){NfkhWaRoaR = true;}
      else if(cNuWuqIsjD == MylfAQzxwV){bfjRcYANUS = true;}
      if(qWIxXuIYHW == FyoayYpRNh){DjIjNbDVHW = true;}
      else if(FyoayYpRNh == qWIxXuIYHW){OdfkpegtzO = true;}
      if(qOqLkrHjxu == VrPCJVSuou){UeVdFkARtO = true;}
      else if(VrPCJVSuou == qOqLkrHjxu){EeYmLOchWV = true;}
      if(NqhlVjZrrn == OVfLpupClw){GHyzPfKbMF = true;}
      else if(OVfLpupClw == NqhlVjZrrn){SVCUPPLAWo = true;}
      if(VOWiZRiWKP == QjMDTfJVlF){AYLoCNoEzu = true;}
      else if(QjMDTfJVlF == VOWiZRiWKP){wdkRRqWMjz = true;}
      if(HnMkfxGatH == OwHsDjxrNY){AJPqOiKHcl = true;}
      if(JPzBHzoVam == YMEnniRdjD){aztMLwlJTg = true;}
      if(UQfSBcrIkT == ineRRlfMid){RbICWwTfbq = true;}
      while(OwHsDjxrNY == HnMkfxGatH){TiyPBwGxFO = true;}
      while(YMEnniRdjD == YMEnniRdjD){uSpzzsbKVa = true;}
      while(ineRRlfMid == ineRRlfMid){TfXKRasHUU = true;}
      if(LwJifRNmHG == true){LwJifRNmHG = false;}
      if(yxnMWDeXOj == true){yxnMWDeXOj = false;}
      if(NfkhWaRoaR == true){NfkhWaRoaR = false;}
      if(DjIjNbDVHW == true){DjIjNbDVHW = false;}
      if(UeVdFkARtO == true){UeVdFkARtO = false;}
      if(GHyzPfKbMF == true){GHyzPfKbMF = false;}
      if(AYLoCNoEzu == true){AYLoCNoEzu = false;}
      if(AJPqOiKHcl == true){AJPqOiKHcl = false;}
      if(aztMLwlJTg == true){aztMLwlJTg = false;}
      if(RbICWwTfbq == true){RbICWwTfbq = false;}
      if(uuSzNxqGjg == true){uuSzNxqGjg = false;}
      if(VDyaeBdydG == true){VDyaeBdydG = false;}
      if(bfjRcYANUS == true){bfjRcYANUS = false;}
      if(OdfkpegtzO == true){OdfkpegtzO = false;}
      if(EeYmLOchWV == true){EeYmLOchWV = false;}
      if(SVCUPPLAWo == true){SVCUPPLAWo = false;}
      if(wdkRRqWMjz == true){wdkRRqWMjz = false;}
      if(TiyPBwGxFO == true){TiyPBwGxFO = false;}
      if(uSpzzsbKVa == true){uSpzzsbKVa = false;}
      if(TfXKRasHUU == true){TfXKRasHUU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLUOOUHBJL
{ 
  void cUnuVDkNOA()
  { 
      bool mnEQOHWfib = false;
      bool zpXORNzFGB = false;
      bool ZNxJphfcNV = false;
      bool NpkVRPONXH = false;
      bool BzuIXgMKdR = false;
      bool NSYkFZpuZg = false;
      bool atSNNIFCxB = false;
      bool ykgzzaSokJ = false;
      bool UUzuItQzPr = false;
      bool YTmqfHfhuO = false;
      bool aKNbTblZke = false;
      bool HBJQLFtWFS = false;
      bool qGmEbdxpSr = false;
      bool tksVhKHWaf = false;
      bool IqOjkWJWeZ = false;
      bool NJcbXUWIzp = false;
      bool dwGskWHmhB = false;
      bool xXuYJAqCTE = false;
      bool UaKsdjIRyN = false;
      bool mzWkBMkUyN = false;
      string ZDOaTVJwMG;
      string MKHezfsGuA;
      string xacRKgUKrF;
      string EckMutAbRN;
      string LpnqBUuwKc;
      string EbwkCyZxPl;
      string BzEHBjYujF;
      string eRnhnGmlPo;
      string lXzOAcfzJx;
      string TDLeLMlgoR;
      string uAMFxmmOxu;
      string LngZAdzpGX;
      string DYkmkbFJVb;
      string UFwyslKtQM;
      string pRCNkfWkeh;
      string MwZRNVOZUV;
      string gdsVaFrhgN;
      string SFYshlWXBF;
      string ETemOYfejW;
      string XkZufMYfmf;
      if(ZDOaTVJwMG == uAMFxmmOxu){mnEQOHWfib = true;}
      else if(uAMFxmmOxu == ZDOaTVJwMG){aKNbTblZke = true;}
      if(MKHezfsGuA == LngZAdzpGX){zpXORNzFGB = true;}
      else if(LngZAdzpGX == MKHezfsGuA){HBJQLFtWFS = true;}
      if(xacRKgUKrF == DYkmkbFJVb){ZNxJphfcNV = true;}
      else if(DYkmkbFJVb == xacRKgUKrF){qGmEbdxpSr = true;}
      if(EckMutAbRN == UFwyslKtQM){NpkVRPONXH = true;}
      else if(UFwyslKtQM == EckMutAbRN){tksVhKHWaf = true;}
      if(LpnqBUuwKc == pRCNkfWkeh){BzuIXgMKdR = true;}
      else if(pRCNkfWkeh == LpnqBUuwKc){IqOjkWJWeZ = true;}
      if(EbwkCyZxPl == MwZRNVOZUV){NSYkFZpuZg = true;}
      else if(MwZRNVOZUV == EbwkCyZxPl){NJcbXUWIzp = true;}
      if(BzEHBjYujF == gdsVaFrhgN){atSNNIFCxB = true;}
      else if(gdsVaFrhgN == BzEHBjYujF){dwGskWHmhB = true;}
      if(eRnhnGmlPo == SFYshlWXBF){ykgzzaSokJ = true;}
      if(lXzOAcfzJx == ETemOYfejW){UUzuItQzPr = true;}
      if(TDLeLMlgoR == XkZufMYfmf){YTmqfHfhuO = true;}
      while(SFYshlWXBF == eRnhnGmlPo){xXuYJAqCTE = true;}
      while(ETemOYfejW == ETemOYfejW){UaKsdjIRyN = true;}
      while(XkZufMYfmf == XkZufMYfmf){mzWkBMkUyN = true;}
      if(mnEQOHWfib == true){mnEQOHWfib = false;}
      if(zpXORNzFGB == true){zpXORNzFGB = false;}
      if(ZNxJphfcNV == true){ZNxJphfcNV = false;}
      if(NpkVRPONXH == true){NpkVRPONXH = false;}
      if(BzuIXgMKdR == true){BzuIXgMKdR = false;}
      if(NSYkFZpuZg == true){NSYkFZpuZg = false;}
      if(atSNNIFCxB == true){atSNNIFCxB = false;}
      if(ykgzzaSokJ == true){ykgzzaSokJ = false;}
      if(UUzuItQzPr == true){UUzuItQzPr = false;}
      if(YTmqfHfhuO == true){YTmqfHfhuO = false;}
      if(aKNbTblZke == true){aKNbTblZke = false;}
      if(HBJQLFtWFS == true){HBJQLFtWFS = false;}
      if(qGmEbdxpSr == true){qGmEbdxpSr = false;}
      if(tksVhKHWaf == true){tksVhKHWaf = false;}
      if(IqOjkWJWeZ == true){IqOjkWJWeZ = false;}
      if(NJcbXUWIzp == true){NJcbXUWIzp = false;}
      if(dwGskWHmhB == true){dwGskWHmhB = false;}
      if(xXuYJAqCTE == true){xXuYJAqCTE = false;}
      if(UaKsdjIRyN == true){UaKsdjIRyN = false;}
      if(mzWkBMkUyN == true){mzWkBMkUyN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLOBUCWOSQ
{ 
  void SxSPJLrgAi()
  { 
      bool QeqKIkicEP = false;
      bool yOBseGlomh = false;
      bool DmbQLrQuuR = false;
      bool BALXQFtmrr = false;
      bool wbphWNYRwW = false;
      bool mBXajcDayQ = false;
      bool UngmOyDcbZ = false;
      bool Mywulawssy = false;
      bool SzyYdzbjmm = false;
      bool BSobWIuCTY = false;
      bool KwpVKnEboJ = false;
      bool gKhAxVoIIO = false;
      bool VSooYsJUXd = false;
      bool fsZTmWJbNp = false;
      bool uAtdGqkodB = false;
      bool SltEDqHBxR = false;
      bool eiDLcmkNMa = false;
      bool MNtSTVXKhh = false;
      bool HTqWKszUQu = false;
      bool OIewKLwiBT = false;
      string DByAcgClbT;
      string CjDNpTJoPu;
      string sekkClMyZB;
      string YeKjmnwwqD;
      string diYtBXwzIc;
      string WfeZKXPNyq;
      string UDMZuWYSZC;
      string XNxLRJGpie;
      string oNpxerzkZP;
      string XixAiaWyze;
      string ycYFEIhSIB;
      string RYdSBHMPuC;
      string XnsKeoQxcq;
      string mHqEfMnkrV;
      string KfbXxyEdzb;
      string NGCwGKjNZP;
      string rjpQOJhYmo;
      string SbXZqqLUMg;
      string jlyBdfFuxV;
      string cZKbdZpLJn;
      if(DByAcgClbT == ycYFEIhSIB){QeqKIkicEP = true;}
      else if(ycYFEIhSIB == DByAcgClbT){KwpVKnEboJ = true;}
      if(CjDNpTJoPu == RYdSBHMPuC){yOBseGlomh = true;}
      else if(RYdSBHMPuC == CjDNpTJoPu){gKhAxVoIIO = true;}
      if(sekkClMyZB == XnsKeoQxcq){DmbQLrQuuR = true;}
      else if(XnsKeoQxcq == sekkClMyZB){VSooYsJUXd = true;}
      if(YeKjmnwwqD == mHqEfMnkrV){BALXQFtmrr = true;}
      else if(mHqEfMnkrV == YeKjmnwwqD){fsZTmWJbNp = true;}
      if(diYtBXwzIc == KfbXxyEdzb){wbphWNYRwW = true;}
      else if(KfbXxyEdzb == diYtBXwzIc){uAtdGqkodB = true;}
      if(WfeZKXPNyq == NGCwGKjNZP){mBXajcDayQ = true;}
      else if(NGCwGKjNZP == WfeZKXPNyq){SltEDqHBxR = true;}
      if(UDMZuWYSZC == rjpQOJhYmo){UngmOyDcbZ = true;}
      else if(rjpQOJhYmo == UDMZuWYSZC){eiDLcmkNMa = true;}
      if(XNxLRJGpie == SbXZqqLUMg){Mywulawssy = true;}
      if(oNpxerzkZP == jlyBdfFuxV){SzyYdzbjmm = true;}
      if(XixAiaWyze == cZKbdZpLJn){BSobWIuCTY = true;}
      while(SbXZqqLUMg == XNxLRJGpie){MNtSTVXKhh = true;}
      while(jlyBdfFuxV == jlyBdfFuxV){HTqWKszUQu = true;}
      while(cZKbdZpLJn == cZKbdZpLJn){OIewKLwiBT = true;}
      if(QeqKIkicEP == true){QeqKIkicEP = false;}
      if(yOBseGlomh == true){yOBseGlomh = false;}
      if(DmbQLrQuuR == true){DmbQLrQuuR = false;}
      if(BALXQFtmrr == true){BALXQFtmrr = false;}
      if(wbphWNYRwW == true){wbphWNYRwW = false;}
      if(mBXajcDayQ == true){mBXajcDayQ = false;}
      if(UngmOyDcbZ == true){UngmOyDcbZ = false;}
      if(Mywulawssy == true){Mywulawssy = false;}
      if(SzyYdzbjmm == true){SzyYdzbjmm = false;}
      if(BSobWIuCTY == true){BSobWIuCTY = false;}
      if(KwpVKnEboJ == true){KwpVKnEboJ = false;}
      if(gKhAxVoIIO == true){gKhAxVoIIO = false;}
      if(VSooYsJUXd == true){VSooYsJUXd = false;}
      if(fsZTmWJbNp == true){fsZTmWJbNp = false;}
      if(uAtdGqkodB == true){uAtdGqkodB = false;}
      if(SltEDqHBxR == true){SltEDqHBxR = false;}
      if(eiDLcmkNMa == true){eiDLcmkNMa = false;}
      if(MNtSTVXKhh == true){MNtSTVXKhh = false;}
      if(HTqWKszUQu == true){HTqWKszUQu = false;}
      if(OIewKLwiBT == true){OIewKLwiBT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EFFVUGPBPO
{ 
  void gpntSPFIFP()
  { 
      bool CdEMJULmue = false;
      bool SheFGmLEIq = false;
      bool WSoHthKPce = false;
      bool MfImgcCxQQ = false;
      bool dCsWbkJZlc = false;
      bool YDrRGjoxSa = false;
      bool KwKQRmYqXd = false;
      bool kNnrNUYSeJ = false;
      bool YjczFImpgx = false;
      bool nEeoFgrcEo = false;
      bool LRBIrKPAEk = false;
      bool KWRICZTKKJ = false;
      bool zhKZofiylf = false;
      bool bwNpxHhTHu = false;
      bool sllumRmWmf = false;
      bool MhRupcGaSL = false;
      bool bQOXJOIbKu = false;
      bool qACPPMwPmX = false;
      bool sMLFStdRzT = false;
      bool AHAuSbWNkX = false;
      string VlFnAYWues;
      string oKaKWGBKaJ;
      string yYwCQndEfD;
      string KFwcZJPeSg;
      string pAOOrqJpyg;
      string gyeKqwpCXL;
      string tSPbhiOxkN;
      string pWqsTxKgKY;
      string enGyVMZllc;
      string TNGGlWkmfI;
      string cLEjqKGlps;
      string kIrygGLQFV;
      string JcLItcPjGw;
      string LXABuTjVHL;
      string GnurqKUIZf;
      string KUgKzAAupN;
      string tVethNIqDN;
      string WpItOUgSQj;
      string HHKakppoBu;
      string SnfsQjIBJd;
      if(VlFnAYWues == cLEjqKGlps){CdEMJULmue = true;}
      else if(cLEjqKGlps == VlFnAYWues){LRBIrKPAEk = true;}
      if(oKaKWGBKaJ == kIrygGLQFV){SheFGmLEIq = true;}
      else if(kIrygGLQFV == oKaKWGBKaJ){KWRICZTKKJ = true;}
      if(yYwCQndEfD == JcLItcPjGw){WSoHthKPce = true;}
      else if(JcLItcPjGw == yYwCQndEfD){zhKZofiylf = true;}
      if(KFwcZJPeSg == LXABuTjVHL){MfImgcCxQQ = true;}
      else if(LXABuTjVHL == KFwcZJPeSg){bwNpxHhTHu = true;}
      if(pAOOrqJpyg == GnurqKUIZf){dCsWbkJZlc = true;}
      else if(GnurqKUIZf == pAOOrqJpyg){sllumRmWmf = true;}
      if(gyeKqwpCXL == KUgKzAAupN){YDrRGjoxSa = true;}
      else if(KUgKzAAupN == gyeKqwpCXL){MhRupcGaSL = true;}
      if(tSPbhiOxkN == tVethNIqDN){KwKQRmYqXd = true;}
      else if(tVethNIqDN == tSPbhiOxkN){bQOXJOIbKu = true;}
      if(pWqsTxKgKY == WpItOUgSQj){kNnrNUYSeJ = true;}
      if(enGyVMZllc == HHKakppoBu){YjczFImpgx = true;}
      if(TNGGlWkmfI == SnfsQjIBJd){nEeoFgrcEo = true;}
      while(WpItOUgSQj == pWqsTxKgKY){qACPPMwPmX = true;}
      while(HHKakppoBu == HHKakppoBu){sMLFStdRzT = true;}
      while(SnfsQjIBJd == SnfsQjIBJd){AHAuSbWNkX = true;}
      if(CdEMJULmue == true){CdEMJULmue = false;}
      if(SheFGmLEIq == true){SheFGmLEIq = false;}
      if(WSoHthKPce == true){WSoHthKPce = false;}
      if(MfImgcCxQQ == true){MfImgcCxQQ = false;}
      if(dCsWbkJZlc == true){dCsWbkJZlc = false;}
      if(YDrRGjoxSa == true){YDrRGjoxSa = false;}
      if(KwKQRmYqXd == true){KwKQRmYqXd = false;}
      if(kNnrNUYSeJ == true){kNnrNUYSeJ = false;}
      if(YjczFImpgx == true){YjczFImpgx = false;}
      if(nEeoFgrcEo == true){nEeoFgrcEo = false;}
      if(LRBIrKPAEk == true){LRBIrKPAEk = false;}
      if(KWRICZTKKJ == true){KWRICZTKKJ = false;}
      if(zhKZofiylf == true){zhKZofiylf = false;}
      if(bwNpxHhTHu == true){bwNpxHhTHu = false;}
      if(sllumRmWmf == true){sllumRmWmf = false;}
      if(MhRupcGaSL == true){MhRupcGaSL = false;}
      if(bQOXJOIbKu == true){bQOXJOIbKu = false;}
      if(qACPPMwPmX == true){qACPPMwPmX = false;}
      if(sMLFStdRzT == true){sMLFStdRzT = false;}
      if(AHAuSbWNkX == true){AHAuSbWNkX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLENRWKMUC
{ 
  void exrsJyoUII()
  { 
      bool GokDYdKOUO = false;
      bool czTLnOUcnx = false;
      bool nkuRHPEEAK = false;
      bool mlZHqWJrAC = false;
      bool AkMsTkohEU = false;
      bool RdwbhUtSuI = false;
      bool YGOKaqYMTR = false;
      bool EcclxCXByW = false;
      bool aWzfsJoyZV = false;
      bool cpwrcsWCRc = false;
      bool MbOmPnBKde = false;
      bool wrUYhBGiQR = false;
      bool BalxoNgkID = false;
      bool eVjVJyIMPE = false;
      bool IeTtYjVWJb = false;
      bool lnkzaloQxB = false;
      bool HQBZAaHyOi = false;
      bool stSMJVGrXE = false;
      bool rJagRqjjtX = false;
      bool IrOOxqcsty = false;
      string rusLYldJrx;
      string BJuxJiQaBB;
      string HdEoUiOpTQ;
      string iKxEMmRFMA;
      string QnDhGqVWEV;
      string QWZOuOqDqo;
      string XmobNpMpkV;
      string RKOAkSaVhc;
      string NrlyzMjiJy;
      string wNOWcczaUP;
      string eekiEGIZcb;
      string nUVNafBqcB;
      string FdgmYDwqWI;
      string TzBSyiGCss;
      string DKFhKarAwx;
      string bIySKByxJA;
      string JQCUInTCPr;
      string YyxixuXzcy;
      string LuuYfKAhHx;
      string jIssimHkYV;
      if(rusLYldJrx == eekiEGIZcb){GokDYdKOUO = true;}
      else if(eekiEGIZcb == rusLYldJrx){MbOmPnBKde = true;}
      if(BJuxJiQaBB == nUVNafBqcB){czTLnOUcnx = true;}
      else if(nUVNafBqcB == BJuxJiQaBB){wrUYhBGiQR = true;}
      if(HdEoUiOpTQ == FdgmYDwqWI){nkuRHPEEAK = true;}
      else if(FdgmYDwqWI == HdEoUiOpTQ){BalxoNgkID = true;}
      if(iKxEMmRFMA == TzBSyiGCss){mlZHqWJrAC = true;}
      else if(TzBSyiGCss == iKxEMmRFMA){eVjVJyIMPE = true;}
      if(QnDhGqVWEV == DKFhKarAwx){AkMsTkohEU = true;}
      else if(DKFhKarAwx == QnDhGqVWEV){IeTtYjVWJb = true;}
      if(QWZOuOqDqo == bIySKByxJA){RdwbhUtSuI = true;}
      else if(bIySKByxJA == QWZOuOqDqo){lnkzaloQxB = true;}
      if(XmobNpMpkV == JQCUInTCPr){YGOKaqYMTR = true;}
      else if(JQCUInTCPr == XmobNpMpkV){HQBZAaHyOi = true;}
      if(RKOAkSaVhc == YyxixuXzcy){EcclxCXByW = true;}
      if(NrlyzMjiJy == LuuYfKAhHx){aWzfsJoyZV = true;}
      if(wNOWcczaUP == jIssimHkYV){cpwrcsWCRc = true;}
      while(YyxixuXzcy == RKOAkSaVhc){stSMJVGrXE = true;}
      while(LuuYfKAhHx == LuuYfKAhHx){rJagRqjjtX = true;}
      while(jIssimHkYV == jIssimHkYV){IrOOxqcsty = true;}
      if(GokDYdKOUO == true){GokDYdKOUO = false;}
      if(czTLnOUcnx == true){czTLnOUcnx = false;}
      if(nkuRHPEEAK == true){nkuRHPEEAK = false;}
      if(mlZHqWJrAC == true){mlZHqWJrAC = false;}
      if(AkMsTkohEU == true){AkMsTkohEU = false;}
      if(RdwbhUtSuI == true){RdwbhUtSuI = false;}
      if(YGOKaqYMTR == true){YGOKaqYMTR = false;}
      if(EcclxCXByW == true){EcclxCXByW = false;}
      if(aWzfsJoyZV == true){aWzfsJoyZV = false;}
      if(cpwrcsWCRc == true){cpwrcsWCRc = false;}
      if(MbOmPnBKde == true){MbOmPnBKde = false;}
      if(wrUYhBGiQR == true){wrUYhBGiQR = false;}
      if(BalxoNgkID == true){BalxoNgkID = false;}
      if(eVjVJyIMPE == true){eVjVJyIMPE = false;}
      if(IeTtYjVWJb == true){IeTtYjVWJb = false;}
      if(lnkzaloQxB == true){lnkzaloQxB = false;}
      if(HQBZAaHyOi == true){HQBZAaHyOi = false;}
      if(stSMJVGrXE == true){stSMJVGrXE = false;}
      if(rJagRqjjtX == true){rJagRqjjtX = false;}
      if(IrOOxqcsty == true){IrOOxqcsty = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSKBJINBKO
{ 
  void gwZGSJdkZe()
  { 
      bool XzBfoQgITh = false;
      bool hNaOyhcSYQ = false;
      bool EFJdmjwhEe = false;
      bool RfiJgyrBjk = false;
      bool EHQFgYjHXF = false;
      bool pshdPSpXsE = false;
      bool UyEnPBdRhA = false;
      bool pahmLwnDxO = false;
      bool AoKynXyEsO = false;
      bool HUIePGDcpe = false;
      bool tSZWPPKuSS = false;
      bool dmZdEfnFzq = false;
      bool DZXSrVRDWF = false;
      bool sLMRTgPmiY = false;
      bool NClZkUtdZj = false;
      bool SxcybUuGdt = false;
      bool xHXNZRZIKX = false;
      bool QAWadAnygX = false;
      bool amcmmuiNoz = false;
      bool lIIobFeYzS = false;
      string kucqJKqUxh;
      string NFWmhboGGN;
      string TXBjlKKAoI;
      string aUmZpDmcIx;
      string inxBnJOVTf;
      string bxMrDNtsFy;
      string ApfnGrRwxe;
      string oLyIeeazwb;
      string ungJfdIuVc;
      string JtXJxsIIuu;
      string rRYoqQzDMY;
      string mtxcDLJWIc;
      string iVaTUtnnKl;
      string WRDAjcPqSP;
      string dEhxpOwtGk;
      string ikASMVqEUw;
      string bKraBUqxrZ;
      string uSErydnddF;
      string xshZCkQknO;
      string lLVVnSMHuU;
      if(kucqJKqUxh == rRYoqQzDMY){XzBfoQgITh = true;}
      else if(rRYoqQzDMY == kucqJKqUxh){tSZWPPKuSS = true;}
      if(NFWmhboGGN == mtxcDLJWIc){hNaOyhcSYQ = true;}
      else if(mtxcDLJWIc == NFWmhboGGN){dmZdEfnFzq = true;}
      if(TXBjlKKAoI == iVaTUtnnKl){EFJdmjwhEe = true;}
      else if(iVaTUtnnKl == TXBjlKKAoI){DZXSrVRDWF = true;}
      if(aUmZpDmcIx == WRDAjcPqSP){RfiJgyrBjk = true;}
      else if(WRDAjcPqSP == aUmZpDmcIx){sLMRTgPmiY = true;}
      if(inxBnJOVTf == dEhxpOwtGk){EHQFgYjHXF = true;}
      else if(dEhxpOwtGk == inxBnJOVTf){NClZkUtdZj = true;}
      if(bxMrDNtsFy == ikASMVqEUw){pshdPSpXsE = true;}
      else if(ikASMVqEUw == bxMrDNtsFy){SxcybUuGdt = true;}
      if(ApfnGrRwxe == bKraBUqxrZ){UyEnPBdRhA = true;}
      else if(bKraBUqxrZ == ApfnGrRwxe){xHXNZRZIKX = true;}
      if(oLyIeeazwb == uSErydnddF){pahmLwnDxO = true;}
      if(ungJfdIuVc == xshZCkQknO){AoKynXyEsO = true;}
      if(JtXJxsIIuu == lLVVnSMHuU){HUIePGDcpe = true;}
      while(uSErydnddF == oLyIeeazwb){QAWadAnygX = true;}
      while(xshZCkQknO == xshZCkQknO){amcmmuiNoz = true;}
      while(lLVVnSMHuU == lLVVnSMHuU){lIIobFeYzS = true;}
      if(XzBfoQgITh == true){XzBfoQgITh = false;}
      if(hNaOyhcSYQ == true){hNaOyhcSYQ = false;}
      if(EFJdmjwhEe == true){EFJdmjwhEe = false;}
      if(RfiJgyrBjk == true){RfiJgyrBjk = false;}
      if(EHQFgYjHXF == true){EHQFgYjHXF = false;}
      if(pshdPSpXsE == true){pshdPSpXsE = false;}
      if(UyEnPBdRhA == true){UyEnPBdRhA = false;}
      if(pahmLwnDxO == true){pahmLwnDxO = false;}
      if(AoKynXyEsO == true){AoKynXyEsO = false;}
      if(HUIePGDcpe == true){HUIePGDcpe = false;}
      if(tSZWPPKuSS == true){tSZWPPKuSS = false;}
      if(dmZdEfnFzq == true){dmZdEfnFzq = false;}
      if(DZXSrVRDWF == true){DZXSrVRDWF = false;}
      if(sLMRTgPmiY == true){sLMRTgPmiY = false;}
      if(NClZkUtdZj == true){NClZkUtdZj = false;}
      if(SxcybUuGdt == true){SxcybUuGdt = false;}
      if(xHXNZRZIKX == true){xHXNZRZIKX = false;}
      if(QAWadAnygX == true){QAWadAnygX = false;}
      if(amcmmuiNoz == true){amcmmuiNoz = false;}
      if(lIIobFeYzS == true){lIIobFeYzS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENWGKVUYRC
{ 
  void OmXHIbpFJo()
  { 
      bool kofSJKePdg = false;
      bool lsggkxVgdb = false;
      bool doTEhtNXmP = false;
      bool HjchCDUqWA = false;
      bool thZEuazbJa = false;
      bool cTqhcwUakP = false;
      bool wGcOYCQzeg = false;
      bool ceKdgwOPJG = false;
      bool ukOMmmruFF = false;
      bool htGHDmFKes = false;
      bool KAxbyxJNAf = false;
      bool gFRdTLrPbl = false;
      bool JUsYyiYDZs = false;
      bool pDkPutnmOo = false;
      bool cetYYcbbmr = false;
      bool upirioHXcO = false;
      bool YGmHocTBiZ = false;
      bool WFAlJeaTAV = false;
      bool GxPhxATsfF = false;
      bool mPJzQWqliu = false;
      string OsytWlECfC;
      string mIAmlIVOhX;
      string hYPbAnGnVG;
      string NPzTbzuXIx;
      string yVlclRJGYe;
      string PTRHkpdVth;
      string fQgZnWJfKm;
      string NxGkZMmlph;
      string dzPppsxril;
      string VZdZRhoMnP;
      string IculRSNggY;
      string DqfLDfAqju;
      string ZQxYRmTfSr;
      string WayaYBEdYX;
      string fQKKidtSVl;
      string gxbsorfWTd;
      string zgOoBbsElC;
      string bWSMOIFlom;
      string sBKgKZyEkg;
      string UgJtYzBVJG;
      if(OsytWlECfC == IculRSNggY){kofSJKePdg = true;}
      else if(IculRSNggY == OsytWlECfC){KAxbyxJNAf = true;}
      if(mIAmlIVOhX == DqfLDfAqju){lsggkxVgdb = true;}
      else if(DqfLDfAqju == mIAmlIVOhX){gFRdTLrPbl = true;}
      if(hYPbAnGnVG == ZQxYRmTfSr){doTEhtNXmP = true;}
      else if(ZQxYRmTfSr == hYPbAnGnVG){JUsYyiYDZs = true;}
      if(NPzTbzuXIx == WayaYBEdYX){HjchCDUqWA = true;}
      else if(WayaYBEdYX == NPzTbzuXIx){pDkPutnmOo = true;}
      if(yVlclRJGYe == fQKKidtSVl){thZEuazbJa = true;}
      else if(fQKKidtSVl == yVlclRJGYe){cetYYcbbmr = true;}
      if(PTRHkpdVth == gxbsorfWTd){cTqhcwUakP = true;}
      else if(gxbsorfWTd == PTRHkpdVth){upirioHXcO = true;}
      if(fQgZnWJfKm == zgOoBbsElC){wGcOYCQzeg = true;}
      else if(zgOoBbsElC == fQgZnWJfKm){YGmHocTBiZ = true;}
      if(NxGkZMmlph == bWSMOIFlom){ceKdgwOPJG = true;}
      if(dzPppsxril == sBKgKZyEkg){ukOMmmruFF = true;}
      if(VZdZRhoMnP == UgJtYzBVJG){htGHDmFKes = true;}
      while(bWSMOIFlom == NxGkZMmlph){WFAlJeaTAV = true;}
      while(sBKgKZyEkg == sBKgKZyEkg){GxPhxATsfF = true;}
      while(UgJtYzBVJG == UgJtYzBVJG){mPJzQWqliu = true;}
      if(kofSJKePdg == true){kofSJKePdg = false;}
      if(lsggkxVgdb == true){lsggkxVgdb = false;}
      if(doTEhtNXmP == true){doTEhtNXmP = false;}
      if(HjchCDUqWA == true){HjchCDUqWA = false;}
      if(thZEuazbJa == true){thZEuazbJa = false;}
      if(cTqhcwUakP == true){cTqhcwUakP = false;}
      if(wGcOYCQzeg == true){wGcOYCQzeg = false;}
      if(ceKdgwOPJG == true){ceKdgwOPJG = false;}
      if(ukOMmmruFF == true){ukOMmmruFF = false;}
      if(htGHDmFKes == true){htGHDmFKes = false;}
      if(KAxbyxJNAf == true){KAxbyxJNAf = false;}
      if(gFRdTLrPbl == true){gFRdTLrPbl = false;}
      if(JUsYyiYDZs == true){JUsYyiYDZs = false;}
      if(pDkPutnmOo == true){pDkPutnmOo = false;}
      if(cetYYcbbmr == true){cetYYcbbmr = false;}
      if(upirioHXcO == true){upirioHXcO = false;}
      if(YGmHocTBiZ == true){YGmHocTBiZ = false;}
      if(WFAlJeaTAV == true){WFAlJeaTAV = false;}
      if(GxPhxATsfF == true){GxPhxATsfF = false;}
      if(mPJzQWqliu == true){mPJzQWqliu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FVISAVKYON
{ 
  void VFZiXKQGUB()
  { 
      bool mrghODkHky = false;
      bool rgDhJeOufP = false;
      bool traAkKgLTK = false;
      bool NGeUehTEbj = false;
      bool IaJJSnzqNn = false;
      bool UwlPEuRgxD = false;
      bool WZnZjlBiDa = false;
      bool KJTuGSiRhw = false;
      bool LoxepRTPPj = false;
      bool QmGXNiliYf = false;
      bool lPnldKcpIk = false;
      bool MzzAqgbJiS = false;
      bool RlTSKWCuhX = false;
      bool gzrBKwBKBf = false;
      bool odHdXQnGff = false;
      bool HcAFOAuUbG = false;
      bool HgHkEMGxpu = false;
      bool fQIDdneots = false;
      bool iwPBPDymmJ = false;
      bool AfitXIVWYK = false;
      string YjTrjastlS;
      string tbVhSEzRkc;
      string OFlRyLrtKZ;
      string aYLHClbYgA;
      string ortBMsGyZP;
      string ANoGtSxCsY;
      string izjMrVQNeg;
      string cZjjnWLjEF;
      string FtTtZNjFNi;
      string nZfIRpIhJq;
      string crSsmZcERX;
      string HNxnTofold;
      string kLAusDsbSx;
      string NdZNbMaZGz;
      string jemobZbroc;
      string JTueFQqXAj;
      string fBlUKcmiLG;
      string NGhmtGYKTS;
      string aBmpntitIK;
      string UDYWTirSey;
      if(YjTrjastlS == crSsmZcERX){mrghODkHky = true;}
      else if(crSsmZcERX == YjTrjastlS){lPnldKcpIk = true;}
      if(tbVhSEzRkc == HNxnTofold){rgDhJeOufP = true;}
      else if(HNxnTofold == tbVhSEzRkc){MzzAqgbJiS = true;}
      if(OFlRyLrtKZ == kLAusDsbSx){traAkKgLTK = true;}
      else if(kLAusDsbSx == OFlRyLrtKZ){RlTSKWCuhX = true;}
      if(aYLHClbYgA == NdZNbMaZGz){NGeUehTEbj = true;}
      else if(NdZNbMaZGz == aYLHClbYgA){gzrBKwBKBf = true;}
      if(ortBMsGyZP == jemobZbroc){IaJJSnzqNn = true;}
      else if(jemobZbroc == ortBMsGyZP){odHdXQnGff = true;}
      if(ANoGtSxCsY == JTueFQqXAj){UwlPEuRgxD = true;}
      else if(JTueFQqXAj == ANoGtSxCsY){HcAFOAuUbG = true;}
      if(izjMrVQNeg == fBlUKcmiLG){WZnZjlBiDa = true;}
      else if(fBlUKcmiLG == izjMrVQNeg){HgHkEMGxpu = true;}
      if(cZjjnWLjEF == NGhmtGYKTS){KJTuGSiRhw = true;}
      if(FtTtZNjFNi == aBmpntitIK){LoxepRTPPj = true;}
      if(nZfIRpIhJq == UDYWTirSey){QmGXNiliYf = true;}
      while(NGhmtGYKTS == cZjjnWLjEF){fQIDdneots = true;}
      while(aBmpntitIK == aBmpntitIK){iwPBPDymmJ = true;}
      while(UDYWTirSey == UDYWTirSey){AfitXIVWYK = true;}
      if(mrghODkHky == true){mrghODkHky = false;}
      if(rgDhJeOufP == true){rgDhJeOufP = false;}
      if(traAkKgLTK == true){traAkKgLTK = false;}
      if(NGeUehTEbj == true){NGeUehTEbj = false;}
      if(IaJJSnzqNn == true){IaJJSnzqNn = false;}
      if(UwlPEuRgxD == true){UwlPEuRgxD = false;}
      if(WZnZjlBiDa == true){WZnZjlBiDa = false;}
      if(KJTuGSiRhw == true){KJTuGSiRhw = false;}
      if(LoxepRTPPj == true){LoxepRTPPj = false;}
      if(QmGXNiliYf == true){QmGXNiliYf = false;}
      if(lPnldKcpIk == true){lPnldKcpIk = false;}
      if(MzzAqgbJiS == true){MzzAqgbJiS = false;}
      if(RlTSKWCuhX == true){RlTSKWCuhX = false;}
      if(gzrBKwBKBf == true){gzrBKwBKBf = false;}
      if(odHdXQnGff == true){odHdXQnGff = false;}
      if(HcAFOAuUbG == true){HcAFOAuUbG = false;}
      if(HgHkEMGxpu == true){HgHkEMGxpu = false;}
      if(fQIDdneots == true){fQIDdneots = false;}
      if(iwPBPDymmJ == true){iwPBPDymmJ = false;}
      if(AfitXIVWYK == true){AfitXIVWYK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKUBGTNLDV
{ 
  void SfNPgVVKId()
  { 
      bool dldptBEwRT = false;
      bool TYUeaVquNp = false;
      bool jIJoXsHVro = false;
      bool SVRddeNTGU = false;
      bool nrhOWnTlbJ = false;
      bool RzknLVboRA = false;
      bool siEcByGpAw = false;
      bool IWosBqZuRj = false;
      bool ZUshXTjdSI = false;
      bool CXBFaFnFMY = false;
      bool gckfBtJrlT = false;
      bool ugXhZXpVFh = false;
      bool NcXrsjViRw = false;
      bool DUhrDxiMfc = false;
      bool JrqyMVATeC = false;
      bool PRzeLDFsmQ = false;
      bool XZZoPZyedc = false;
      bool ocobXUkYeX = false;
      bool jCEPglVDgz = false;
      bool rpZPEiSBim = false;
      string oYJGIknJQT;
      string dLddcXUJwR;
      string ZJNDbaBYEq;
      string PJtxhWqzca;
      string REMaDGMhmU;
      string iTtfcfLGeh;
      string iOFYDTQfuF;
      string fUgUzVxmzU;
      string OTkjHwPOUC;
      string LkTuqDzmWj;
      string pflgnOmYfG;
      string iYGKSPcURH;
      string DCKrtuBlcw;
      string WJPOdhgEws;
      string JphOTldJbb;
      string ZdUPgmVsmr;
      string MBwjiYIrfk;
      string hYYXxMTwYH;
      string RqJAVsoAhq;
      string MnQDfItyeu;
      if(oYJGIknJQT == pflgnOmYfG){dldptBEwRT = true;}
      else if(pflgnOmYfG == oYJGIknJQT){gckfBtJrlT = true;}
      if(dLddcXUJwR == iYGKSPcURH){TYUeaVquNp = true;}
      else if(iYGKSPcURH == dLddcXUJwR){ugXhZXpVFh = true;}
      if(ZJNDbaBYEq == DCKrtuBlcw){jIJoXsHVro = true;}
      else if(DCKrtuBlcw == ZJNDbaBYEq){NcXrsjViRw = true;}
      if(PJtxhWqzca == WJPOdhgEws){SVRddeNTGU = true;}
      else if(WJPOdhgEws == PJtxhWqzca){DUhrDxiMfc = true;}
      if(REMaDGMhmU == JphOTldJbb){nrhOWnTlbJ = true;}
      else if(JphOTldJbb == REMaDGMhmU){JrqyMVATeC = true;}
      if(iTtfcfLGeh == ZdUPgmVsmr){RzknLVboRA = true;}
      else if(ZdUPgmVsmr == iTtfcfLGeh){PRzeLDFsmQ = true;}
      if(iOFYDTQfuF == MBwjiYIrfk){siEcByGpAw = true;}
      else if(MBwjiYIrfk == iOFYDTQfuF){XZZoPZyedc = true;}
      if(fUgUzVxmzU == hYYXxMTwYH){IWosBqZuRj = true;}
      if(OTkjHwPOUC == RqJAVsoAhq){ZUshXTjdSI = true;}
      if(LkTuqDzmWj == MnQDfItyeu){CXBFaFnFMY = true;}
      while(hYYXxMTwYH == fUgUzVxmzU){ocobXUkYeX = true;}
      while(RqJAVsoAhq == RqJAVsoAhq){jCEPglVDgz = true;}
      while(MnQDfItyeu == MnQDfItyeu){rpZPEiSBim = true;}
      if(dldptBEwRT == true){dldptBEwRT = false;}
      if(TYUeaVquNp == true){TYUeaVquNp = false;}
      if(jIJoXsHVro == true){jIJoXsHVro = false;}
      if(SVRddeNTGU == true){SVRddeNTGU = false;}
      if(nrhOWnTlbJ == true){nrhOWnTlbJ = false;}
      if(RzknLVboRA == true){RzknLVboRA = false;}
      if(siEcByGpAw == true){siEcByGpAw = false;}
      if(IWosBqZuRj == true){IWosBqZuRj = false;}
      if(ZUshXTjdSI == true){ZUshXTjdSI = false;}
      if(CXBFaFnFMY == true){CXBFaFnFMY = false;}
      if(gckfBtJrlT == true){gckfBtJrlT = false;}
      if(ugXhZXpVFh == true){ugXhZXpVFh = false;}
      if(NcXrsjViRw == true){NcXrsjViRw = false;}
      if(DUhrDxiMfc == true){DUhrDxiMfc = false;}
      if(JrqyMVATeC == true){JrqyMVATeC = false;}
      if(PRzeLDFsmQ == true){PRzeLDFsmQ = false;}
      if(XZZoPZyedc == true){XZZoPZyedc = false;}
      if(ocobXUkYeX == true){ocobXUkYeX = false;}
      if(jCEPglVDgz == true){jCEPglVDgz = false;}
      if(rpZPEiSBim == true){rpZPEiSBim = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFCCFGPZCD
{ 
  void SSbajlFthX()
  { 
      bool pGaSqbYZrt = false;
      bool LZtwAsJRIR = false;
      bool sqUmKbNypm = false;
      bool cIHIPHlEUU = false;
      bool AREetSWknE = false;
      bool coWVyzkmIO = false;
      bool NZiEQDSkfs = false;
      bool HExmRbmpsq = false;
      bool EcKlKnkkJP = false;
      bool VywFHaizNq = false;
      bool AkEtxXrjEW = false;
      bool MutQJjOwtc = false;
      bool SgbPWIIqfp = false;
      bool rnbBqTYPom = false;
      bool wAglDaEewW = false;
      bool LlFkYSJnXn = false;
      bool OADNdXTrYp = false;
      bool LyGGgRApMw = false;
      bool EcuJeGhpcX = false;
      bool KjrBXuwSHe = false;
      string OBbTFwZxdp;
      string xoEXaIHqOW;
      string RJYdmhHZXp;
      string DTFXYJwBKd;
      string BcwycIaWEp;
      string uIJuQEbyfX;
      string ozYnmdjfyR;
      string MFgjUoNZBe;
      string HjVgttJKGT;
      string gxVloBDHKy;
      string YtYmdpaYZb;
      string qCxAQEdqss;
      string UYZdjOituT;
      string kFOCGMLiDE;
      string SjkecdAVVj;
      string WMORdzUtCO;
      string GgdFqknttD;
      string sumnZjnuAG;
      string NNXLxYqwYG;
      string rQgoxlGfmr;
      if(OBbTFwZxdp == YtYmdpaYZb){pGaSqbYZrt = true;}
      else if(YtYmdpaYZb == OBbTFwZxdp){AkEtxXrjEW = true;}
      if(xoEXaIHqOW == qCxAQEdqss){LZtwAsJRIR = true;}
      else if(qCxAQEdqss == xoEXaIHqOW){MutQJjOwtc = true;}
      if(RJYdmhHZXp == UYZdjOituT){sqUmKbNypm = true;}
      else if(UYZdjOituT == RJYdmhHZXp){SgbPWIIqfp = true;}
      if(DTFXYJwBKd == kFOCGMLiDE){cIHIPHlEUU = true;}
      else if(kFOCGMLiDE == DTFXYJwBKd){rnbBqTYPom = true;}
      if(BcwycIaWEp == SjkecdAVVj){AREetSWknE = true;}
      else if(SjkecdAVVj == BcwycIaWEp){wAglDaEewW = true;}
      if(uIJuQEbyfX == WMORdzUtCO){coWVyzkmIO = true;}
      else if(WMORdzUtCO == uIJuQEbyfX){LlFkYSJnXn = true;}
      if(ozYnmdjfyR == GgdFqknttD){NZiEQDSkfs = true;}
      else if(GgdFqknttD == ozYnmdjfyR){OADNdXTrYp = true;}
      if(MFgjUoNZBe == sumnZjnuAG){HExmRbmpsq = true;}
      if(HjVgttJKGT == NNXLxYqwYG){EcKlKnkkJP = true;}
      if(gxVloBDHKy == rQgoxlGfmr){VywFHaizNq = true;}
      while(sumnZjnuAG == MFgjUoNZBe){LyGGgRApMw = true;}
      while(NNXLxYqwYG == NNXLxYqwYG){EcuJeGhpcX = true;}
      while(rQgoxlGfmr == rQgoxlGfmr){KjrBXuwSHe = true;}
      if(pGaSqbYZrt == true){pGaSqbYZrt = false;}
      if(LZtwAsJRIR == true){LZtwAsJRIR = false;}
      if(sqUmKbNypm == true){sqUmKbNypm = false;}
      if(cIHIPHlEUU == true){cIHIPHlEUU = false;}
      if(AREetSWknE == true){AREetSWknE = false;}
      if(coWVyzkmIO == true){coWVyzkmIO = false;}
      if(NZiEQDSkfs == true){NZiEQDSkfs = false;}
      if(HExmRbmpsq == true){HExmRbmpsq = false;}
      if(EcKlKnkkJP == true){EcKlKnkkJP = false;}
      if(VywFHaizNq == true){VywFHaizNq = false;}
      if(AkEtxXrjEW == true){AkEtxXrjEW = false;}
      if(MutQJjOwtc == true){MutQJjOwtc = false;}
      if(SgbPWIIqfp == true){SgbPWIIqfp = false;}
      if(rnbBqTYPom == true){rnbBqTYPom = false;}
      if(wAglDaEewW == true){wAglDaEewW = false;}
      if(LlFkYSJnXn == true){LlFkYSJnXn = false;}
      if(OADNdXTrYp == true){OADNdXTrYp = false;}
      if(LyGGgRApMw == true){LyGGgRApMw = false;}
      if(EcuJeGhpcX == true){EcuJeGhpcX = false;}
      if(KjrBXuwSHe == true){KjrBXuwSHe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTSVEMBSFY
{ 
  void mOVSmDmgjB()
  { 
      bool NsGOiOEAPC = false;
      bool CMrkPaawQb = false;
      bool LFwMpTkqdO = false;
      bool xzBQjnAIWa = false;
      bool fiAXSuExrt = false;
      bool fpAgiIwsYP = false;
      bool dNWBFCLbAa = false;
      bool ZRYpubFYtt = false;
      bool OnzjiGzUga = false;
      bool qGjGxSMyRP = false;
      bool jcwQTNQJkH = false;
      bool DWzdAoOmRy = false;
      bool DptYiThRrc = false;
      bool PGGeKkqhQU = false;
      bool ooiZXTHFGH = false;
      bool EYgTLtiWhz = false;
      bool fyRIqxQTTO = false;
      bool yfWwIOGTBO = false;
      bool MbLkYpYmSP = false;
      bool CTAQopWahZ = false;
      string iZJQHLICwS;
      string qUdMiFinKb;
      string OSnCyrmouP;
      string DXaZmsHbIo;
      string kPhaeCIfHt;
      string jObVBQlHRP;
      string YSGgOTtEYp;
      string yGeVpzkNXw;
      string jHhBfnuEXW;
      string HzKsQSJALK;
      string IDGQwcjGfC;
      string fXiVeRjEBZ;
      string YofChyulEX;
      string ojCMmfAQFC;
      string EnYVpjQoNz;
      string hEzklSXDix;
      string hyBHMwVWhy;
      string QSzyVjQKLy;
      string hGXFpkjQZU;
      string IxhHUGlRIt;
      if(iZJQHLICwS == IDGQwcjGfC){NsGOiOEAPC = true;}
      else if(IDGQwcjGfC == iZJQHLICwS){jcwQTNQJkH = true;}
      if(qUdMiFinKb == fXiVeRjEBZ){CMrkPaawQb = true;}
      else if(fXiVeRjEBZ == qUdMiFinKb){DWzdAoOmRy = true;}
      if(OSnCyrmouP == YofChyulEX){LFwMpTkqdO = true;}
      else if(YofChyulEX == OSnCyrmouP){DptYiThRrc = true;}
      if(DXaZmsHbIo == ojCMmfAQFC){xzBQjnAIWa = true;}
      else if(ojCMmfAQFC == DXaZmsHbIo){PGGeKkqhQU = true;}
      if(kPhaeCIfHt == EnYVpjQoNz){fiAXSuExrt = true;}
      else if(EnYVpjQoNz == kPhaeCIfHt){ooiZXTHFGH = true;}
      if(jObVBQlHRP == hEzklSXDix){fpAgiIwsYP = true;}
      else if(hEzklSXDix == jObVBQlHRP){EYgTLtiWhz = true;}
      if(YSGgOTtEYp == hyBHMwVWhy){dNWBFCLbAa = true;}
      else if(hyBHMwVWhy == YSGgOTtEYp){fyRIqxQTTO = true;}
      if(yGeVpzkNXw == QSzyVjQKLy){ZRYpubFYtt = true;}
      if(jHhBfnuEXW == hGXFpkjQZU){OnzjiGzUga = true;}
      if(HzKsQSJALK == IxhHUGlRIt){qGjGxSMyRP = true;}
      while(QSzyVjQKLy == yGeVpzkNXw){yfWwIOGTBO = true;}
      while(hGXFpkjQZU == hGXFpkjQZU){MbLkYpYmSP = true;}
      while(IxhHUGlRIt == IxhHUGlRIt){CTAQopWahZ = true;}
      if(NsGOiOEAPC == true){NsGOiOEAPC = false;}
      if(CMrkPaawQb == true){CMrkPaawQb = false;}
      if(LFwMpTkqdO == true){LFwMpTkqdO = false;}
      if(xzBQjnAIWa == true){xzBQjnAIWa = false;}
      if(fiAXSuExrt == true){fiAXSuExrt = false;}
      if(fpAgiIwsYP == true){fpAgiIwsYP = false;}
      if(dNWBFCLbAa == true){dNWBFCLbAa = false;}
      if(ZRYpubFYtt == true){ZRYpubFYtt = false;}
      if(OnzjiGzUga == true){OnzjiGzUga = false;}
      if(qGjGxSMyRP == true){qGjGxSMyRP = false;}
      if(jcwQTNQJkH == true){jcwQTNQJkH = false;}
      if(DWzdAoOmRy == true){DWzdAoOmRy = false;}
      if(DptYiThRrc == true){DptYiThRrc = false;}
      if(PGGeKkqhQU == true){PGGeKkqhQU = false;}
      if(ooiZXTHFGH == true){ooiZXTHFGH = false;}
      if(EYgTLtiWhz == true){EYgTLtiWhz = false;}
      if(fyRIqxQTTO == true){fyRIqxQTTO = false;}
      if(yfWwIOGTBO == true){yfWwIOGTBO = false;}
      if(MbLkYpYmSP == true){MbLkYpYmSP = false;}
      if(CTAQopWahZ == true){CTAQopWahZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKSYEXNCJU
{ 
  void bAUGgIKNCh()
  { 
      bool JHDCrpiRxh = false;
      bool rNkHrGAJMO = false;
      bool bqwlwcmEHZ = false;
      bool iUaihmPtte = false;
      bool wKmGHqiMHr = false;
      bool LoLmYRKQGP = false;
      bool DdKXzXlBZE = false;
      bool pFPhSQEpeE = false;
      bool sZwPNtJnKP = false;
      bool czndaRAOHj = false;
      bool FgmCBFYcUH = false;
      bool NUlBWchtJE = false;
      bool NyqJbqRkGA = false;
      bool PoitzLmtNI = false;
      bool UgSCCHMlHy = false;
      bool iGFCVHpcZK = false;
      bool mnVTqYkrCK = false;
      bool onfAigeoHT = false;
      bool decIRJifXr = false;
      bool VKTCUgLyLc = false;
      string yPcIPFuirA;
      string rFBcdzbHSi;
      string unXmOHRaWJ;
      string BuyUXWZGHO;
      string rtkborwQhD;
      string DwbqNJqotH;
      string mTMizwGfEH;
      string ZUzDqACwyW;
      string LBsSFETHHN;
      string fjMzbXhBcs;
      string kPLZdhwXAM;
      string GtqWwlatdt;
      string czYqboIzbS;
      string SBSFkuoSoX;
      string IuGuGksoDo;
      string xnXiPkqUyn;
      string ZwwhsFbllA;
      string wHEFkhscjq;
      string uTwlUecjoz;
      string ETTAyLyXBB;
      if(yPcIPFuirA == kPLZdhwXAM){JHDCrpiRxh = true;}
      else if(kPLZdhwXAM == yPcIPFuirA){FgmCBFYcUH = true;}
      if(rFBcdzbHSi == GtqWwlatdt){rNkHrGAJMO = true;}
      else if(GtqWwlatdt == rFBcdzbHSi){NUlBWchtJE = true;}
      if(unXmOHRaWJ == czYqboIzbS){bqwlwcmEHZ = true;}
      else if(czYqboIzbS == unXmOHRaWJ){NyqJbqRkGA = true;}
      if(BuyUXWZGHO == SBSFkuoSoX){iUaihmPtte = true;}
      else if(SBSFkuoSoX == BuyUXWZGHO){PoitzLmtNI = true;}
      if(rtkborwQhD == IuGuGksoDo){wKmGHqiMHr = true;}
      else if(IuGuGksoDo == rtkborwQhD){UgSCCHMlHy = true;}
      if(DwbqNJqotH == xnXiPkqUyn){LoLmYRKQGP = true;}
      else if(xnXiPkqUyn == DwbqNJqotH){iGFCVHpcZK = true;}
      if(mTMizwGfEH == ZwwhsFbllA){DdKXzXlBZE = true;}
      else if(ZwwhsFbllA == mTMizwGfEH){mnVTqYkrCK = true;}
      if(ZUzDqACwyW == wHEFkhscjq){pFPhSQEpeE = true;}
      if(LBsSFETHHN == uTwlUecjoz){sZwPNtJnKP = true;}
      if(fjMzbXhBcs == ETTAyLyXBB){czndaRAOHj = true;}
      while(wHEFkhscjq == ZUzDqACwyW){onfAigeoHT = true;}
      while(uTwlUecjoz == uTwlUecjoz){decIRJifXr = true;}
      while(ETTAyLyXBB == ETTAyLyXBB){VKTCUgLyLc = true;}
      if(JHDCrpiRxh == true){JHDCrpiRxh = false;}
      if(rNkHrGAJMO == true){rNkHrGAJMO = false;}
      if(bqwlwcmEHZ == true){bqwlwcmEHZ = false;}
      if(iUaihmPtte == true){iUaihmPtte = false;}
      if(wKmGHqiMHr == true){wKmGHqiMHr = false;}
      if(LoLmYRKQGP == true){LoLmYRKQGP = false;}
      if(DdKXzXlBZE == true){DdKXzXlBZE = false;}
      if(pFPhSQEpeE == true){pFPhSQEpeE = false;}
      if(sZwPNtJnKP == true){sZwPNtJnKP = false;}
      if(czndaRAOHj == true){czndaRAOHj = false;}
      if(FgmCBFYcUH == true){FgmCBFYcUH = false;}
      if(NUlBWchtJE == true){NUlBWchtJE = false;}
      if(NyqJbqRkGA == true){NyqJbqRkGA = false;}
      if(PoitzLmtNI == true){PoitzLmtNI = false;}
      if(UgSCCHMlHy == true){UgSCCHMlHy = false;}
      if(iGFCVHpcZK == true){iGFCVHpcZK = false;}
      if(mnVTqYkrCK == true){mnVTqYkrCK = false;}
      if(onfAigeoHT == true){onfAigeoHT = false;}
      if(decIRJifXr == true){decIRJifXr = false;}
      if(VKTCUgLyLc == true){VKTCUgLyLc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCZBZCGEPE
{ 
  void ZDxrDxxJDk()
  { 
      bool UBMrXkrrUH = false;
      bool KgoKfLGrCO = false;
      bool uzaxYwmUYA = false;
      bool uzlnEHWIyg = false;
      bool pAIStRBonL = false;
      bool kuSLbUaOTb = false;
      bool xWSTLKtAFX = false;
      bool oxtVYtqHDH = false;
      bool uygNPzgaMj = false;
      bool fHnWiShnHi = false;
      bool WAiPWmBxlh = false;
      bool dTLMgzoFEM = false;
      bool dSnVqgIWlF = false;
      bool LCATjtORqc = false;
      bool xineFMwbpj = false;
      bool cbjtEDMNXo = false;
      bool ddLfVaTqcl = false;
      bool kXOaOudJPe = false;
      bool kggBcjSFOf = false;
      bool hBtBySWIJe = false;
      string iTfQOrzDnI;
      string PdHzITdWOG;
      string fXJQtXuiuK;
      string uZKmtXkaXn;
      string PmiQTNzdqj;
      string xXXFELJPVp;
      string wQIdNoTTFj;
      string hDzZqsnrwg;
      string YQqKNWCFih;
      string NVEhqydFDe;
      string teYGBtYyNL;
      string WRSoQfYxQp;
      string mNkWVMyRhr;
      string OhoRlsrkIS;
      string yDqXLwCPQL;
      string ZgoMqgtBjo;
      string uHPVxnbBCX;
      string mnnxriVNLZ;
      string JiAWShscaF;
      string yqATXqnVaW;
      if(iTfQOrzDnI == teYGBtYyNL){UBMrXkrrUH = true;}
      else if(teYGBtYyNL == iTfQOrzDnI){WAiPWmBxlh = true;}
      if(PdHzITdWOG == WRSoQfYxQp){KgoKfLGrCO = true;}
      else if(WRSoQfYxQp == PdHzITdWOG){dTLMgzoFEM = true;}
      if(fXJQtXuiuK == mNkWVMyRhr){uzaxYwmUYA = true;}
      else if(mNkWVMyRhr == fXJQtXuiuK){dSnVqgIWlF = true;}
      if(uZKmtXkaXn == OhoRlsrkIS){uzlnEHWIyg = true;}
      else if(OhoRlsrkIS == uZKmtXkaXn){LCATjtORqc = true;}
      if(PmiQTNzdqj == yDqXLwCPQL){pAIStRBonL = true;}
      else if(yDqXLwCPQL == PmiQTNzdqj){xineFMwbpj = true;}
      if(xXXFELJPVp == ZgoMqgtBjo){kuSLbUaOTb = true;}
      else if(ZgoMqgtBjo == xXXFELJPVp){cbjtEDMNXo = true;}
      if(wQIdNoTTFj == uHPVxnbBCX){xWSTLKtAFX = true;}
      else if(uHPVxnbBCX == wQIdNoTTFj){ddLfVaTqcl = true;}
      if(hDzZqsnrwg == mnnxriVNLZ){oxtVYtqHDH = true;}
      if(YQqKNWCFih == JiAWShscaF){uygNPzgaMj = true;}
      if(NVEhqydFDe == yqATXqnVaW){fHnWiShnHi = true;}
      while(mnnxriVNLZ == hDzZqsnrwg){kXOaOudJPe = true;}
      while(JiAWShscaF == JiAWShscaF){kggBcjSFOf = true;}
      while(yqATXqnVaW == yqATXqnVaW){hBtBySWIJe = true;}
      if(UBMrXkrrUH == true){UBMrXkrrUH = false;}
      if(KgoKfLGrCO == true){KgoKfLGrCO = false;}
      if(uzaxYwmUYA == true){uzaxYwmUYA = false;}
      if(uzlnEHWIyg == true){uzlnEHWIyg = false;}
      if(pAIStRBonL == true){pAIStRBonL = false;}
      if(kuSLbUaOTb == true){kuSLbUaOTb = false;}
      if(xWSTLKtAFX == true){xWSTLKtAFX = false;}
      if(oxtVYtqHDH == true){oxtVYtqHDH = false;}
      if(uygNPzgaMj == true){uygNPzgaMj = false;}
      if(fHnWiShnHi == true){fHnWiShnHi = false;}
      if(WAiPWmBxlh == true){WAiPWmBxlh = false;}
      if(dTLMgzoFEM == true){dTLMgzoFEM = false;}
      if(dSnVqgIWlF == true){dSnVqgIWlF = false;}
      if(LCATjtORqc == true){LCATjtORqc = false;}
      if(xineFMwbpj == true){xineFMwbpj = false;}
      if(cbjtEDMNXo == true){cbjtEDMNXo = false;}
      if(ddLfVaTqcl == true){ddLfVaTqcl = false;}
      if(kXOaOudJPe == true){kXOaOudJPe = false;}
      if(kggBcjSFOf == true){kggBcjSFOf = false;}
      if(hBtBySWIJe == true){hBtBySWIJe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELKRICXCFN
{ 
  void PyHzujYsyk()
  { 
      bool kOQiuNsxEM = false;
      bool nsimPHWqit = false;
      bool qileNKcJEO = false;
      bool GBuYDZwaGP = false;
      bool JasnKUbOFS = false;
      bool nQlIwBblVj = false;
      bool kispGmyJip = false;
      bool LwjTjQoyTs = false;
      bool iNEkZpPmbB = false;
      bool xKEVdZgDgX = false;
      bool VRfPGrfRXf = false;
      bool McRcBWeIPP = false;
      bool WKhgrBqNoJ = false;
      bool jlRuWQgodh = false;
      bool JxPwoUraTG = false;
      bool uYmQBKjyWF = false;
      bool ASbNwZLVGk = false;
      bool opdhGYukqX = false;
      bool JQsiOKyAtL = false;
      bool giRYhqUBzO = false;
      string ecfjhLFADa;
      string PsaaEPDgyw;
      string IJosPGQiaB;
      string LkWDpSFHTm;
      string YDFMWmLyVF;
      string aQXGdUnlTb;
      string uWZBOdVWkl;
      string JwNLXFEbVc;
      string tSNUauNQYU;
      string eSmrrBdDyr;
      string QoMiueCMhY;
      string QLQqgbIEaS;
      string QFxQHqJVSV;
      string bAdcLFGdZw;
      string rBhzDSCwKQ;
      string rYcebLqubE;
      string UgsMxPhmea;
      string UeeeZOWxMo;
      string nMKCcDXyAz;
      string NKCUaLIUCn;
      if(ecfjhLFADa == QoMiueCMhY){kOQiuNsxEM = true;}
      else if(QoMiueCMhY == ecfjhLFADa){VRfPGrfRXf = true;}
      if(PsaaEPDgyw == QLQqgbIEaS){nsimPHWqit = true;}
      else if(QLQqgbIEaS == PsaaEPDgyw){McRcBWeIPP = true;}
      if(IJosPGQiaB == QFxQHqJVSV){qileNKcJEO = true;}
      else if(QFxQHqJVSV == IJosPGQiaB){WKhgrBqNoJ = true;}
      if(LkWDpSFHTm == bAdcLFGdZw){GBuYDZwaGP = true;}
      else if(bAdcLFGdZw == LkWDpSFHTm){jlRuWQgodh = true;}
      if(YDFMWmLyVF == rBhzDSCwKQ){JasnKUbOFS = true;}
      else if(rBhzDSCwKQ == YDFMWmLyVF){JxPwoUraTG = true;}
      if(aQXGdUnlTb == rYcebLqubE){nQlIwBblVj = true;}
      else if(rYcebLqubE == aQXGdUnlTb){uYmQBKjyWF = true;}
      if(uWZBOdVWkl == UgsMxPhmea){kispGmyJip = true;}
      else if(UgsMxPhmea == uWZBOdVWkl){ASbNwZLVGk = true;}
      if(JwNLXFEbVc == UeeeZOWxMo){LwjTjQoyTs = true;}
      if(tSNUauNQYU == nMKCcDXyAz){iNEkZpPmbB = true;}
      if(eSmrrBdDyr == NKCUaLIUCn){xKEVdZgDgX = true;}
      while(UeeeZOWxMo == JwNLXFEbVc){opdhGYukqX = true;}
      while(nMKCcDXyAz == nMKCcDXyAz){JQsiOKyAtL = true;}
      while(NKCUaLIUCn == NKCUaLIUCn){giRYhqUBzO = true;}
      if(kOQiuNsxEM == true){kOQiuNsxEM = false;}
      if(nsimPHWqit == true){nsimPHWqit = false;}
      if(qileNKcJEO == true){qileNKcJEO = false;}
      if(GBuYDZwaGP == true){GBuYDZwaGP = false;}
      if(JasnKUbOFS == true){JasnKUbOFS = false;}
      if(nQlIwBblVj == true){nQlIwBblVj = false;}
      if(kispGmyJip == true){kispGmyJip = false;}
      if(LwjTjQoyTs == true){LwjTjQoyTs = false;}
      if(iNEkZpPmbB == true){iNEkZpPmbB = false;}
      if(xKEVdZgDgX == true){xKEVdZgDgX = false;}
      if(VRfPGrfRXf == true){VRfPGrfRXf = false;}
      if(McRcBWeIPP == true){McRcBWeIPP = false;}
      if(WKhgrBqNoJ == true){WKhgrBqNoJ = false;}
      if(jlRuWQgodh == true){jlRuWQgodh = false;}
      if(JxPwoUraTG == true){JxPwoUraTG = false;}
      if(uYmQBKjyWF == true){uYmQBKjyWF = false;}
      if(ASbNwZLVGk == true){ASbNwZLVGk = false;}
      if(opdhGYukqX == true){opdhGYukqX = false;}
      if(JQsiOKyAtL == true){JQsiOKyAtL = false;}
      if(giRYhqUBzO == true){giRYhqUBzO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQFTEDYHWK
{ 
  void khGUFbqdqj()
  { 
      bool ncRfBrZRgg = false;
      bool ZMyTXeOIRz = false;
      bool WHmoFnUPsD = false;
      bool ErJyrjrSUV = false;
      bool dIXEUZcuHb = false;
      bool ihTtafpcZM = false;
      bool WJXcbhDAam = false;
      bool lwmuVNihUe = false;
      bool KZIQUWYPWM = false;
      bool tPrIyUjucl = false;
      bool WcTTpltXYM = false;
      bool wHHtBxAGHF = false;
      bool IncOsVDexA = false;
      bool cnFhIgFnah = false;
      bool bBpJPmHxGB = false;
      bool TcmWdiAFaT = false;
      bool iPaXjICZlU = false;
      bool qMfZcHxSyG = false;
      bool NGYwgAAhEY = false;
      bool gANHzLaRZH = false;
      string JNzDpSJFog;
      string ADtJOnKnqm;
      string bNgEYTWNYu;
      string axXQggjOsz;
      string WRGAwcwOPF;
      string yeJlnwfudV;
      string uwgsGDfcch;
      string EwurQKGgHw;
      string XIxSxumlbk;
      string AojWEajNss;
      string xSlhBBjRUd;
      string pzmhymyNuL;
      string QsBqhOMXmp;
      string ZrmOyEWORu;
      string KUQxuABBYR;
      string bVRhcDQtAl;
      string oMdeDxMYjs;
      string QjwABucDwg;
      string NKyVNDaElt;
      string mbOfGxpktx;
      if(JNzDpSJFog == xSlhBBjRUd){ncRfBrZRgg = true;}
      else if(xSlhBBjRUd == JNzDpSJFog){WcTTpltXYM = true;}
      if(ADtJOnKnqm == pzmhymyNuL){ZMyTXeOIRz = true;}
      else if(pzmhymyNuL == ADtJOnKnqm){wHHtBxAGHF = true;}
      if(bNgEYTWNYu == QsBqhOMXmp){WHmoFnUPsD = true;}
      else if(QsBqhOMXmp == bNgEYTWNYu){IncOsVDexA = true;}
      if(axXQggjOsz == ZrmOyEWORu){ErJyrjrSUV = true;}
      else if(ZrmOyEWORu == axXQggjOsz){cnFhIgFnah = true;}
      if(WRGAwcwOPF == KUQxuABBYR){dIXEUZcuHb = true;}
      else if(KUQxuABBYR == WRGAwcwOPF){bBpJPmHxGB = true;}
      if(yeJlnwfudV == bVRhcDQtAl){ihTtafpcZM = true;}
      else if(bVRhcDQtAl == yeJlnwfudV){TcmWdiAFaT = true;}
      if(uwgsGDfcch == oMdeDxMYjs){WJXcbhDAam = true;}
      else if(oMdeDxMYjs == uwgsGDfcch){iPaXjICZlU = true;}
      if(EwurQKGgHw == QjwABucDwg){lwmuVNihUe = true;}
      if(XIxSxumlbk == NKyVNDaElt){KZIQUWYPWM = true;}
      if(AojWEajNss == mbOfGxpktx){tPrIyUjucl = true;}
      while(QjwABucDwg == EwurQKGgHw){qMfZcHxSyG = true;}
      while(NKyVNDaElt == NKyVNDaElt){NGYwgAAhEY = true;}
      while(mbOfGxpktx == mbOfGxpktx){gANHzLaRZH = true;}
      if(ncRfBrZRgg == true){ncRfBrZRgg = false;}
      if(ZMyTXeOIRz == true){ZMyTXeOIRz = false;}
      if(WHmoFnUPsD == true){WHmoFnUPsD = false;}
      if(ErJyrjrSUV == true){ErJyrjrSUV = false;}
      if(dIXEUZcuHb == true){dIXEUZcuHb = false;}
      if(ihTtafpcZM == true){ihTtafpcZM = false;}
      if(WJXcbhDAam == true){WJXcbhDAam = false;}
      if(lwmuVNihUe == true){lwmuVNihUe = false;}
      if(KZIQUWYPWM == true){KZIQUWYPWM = false;}
      if(tPrIyUjucl == true){tPrIyUjucl = false;}
      if(WcTTpltXYM == true){WcTTpltXYM = false;}
      if(wHHtBxAGHF == true){wHHtBxAGHF = false;}
      if(IncOsVDexA == true){IncOsVDexA = false;}
      if(cnFhIgFnah == true){cnFhIgFnah = false;}
      if(bBpJPmHxGB == true){bBpJPmHxGB = false;}
      if(TcmWdiAFaT == true){TcmWdiAFaT = false;}
      if(iPaXjICZlU == true){iPaXjICZlU = false;}
      if(qMfZcHxSyG == true){qMfZcHxSyG = false;}
      if(NGYwgAAhEY == true){NGYwgAAhEY = false;}
      if(gANHzLaRZH == true){gANHzLaRZH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMTYLNEEKE
{ 
  void ysPZOxiNte()
  { 
      bool oBHRCLCICA = false;
      bool fxmfEeDoUp = false;
      bool BdkpNfRZcC = false;
      bool UdLjjfWyxu = false;
      bool nQwcSSuJIO = false;
      bool lRRYuLQREV = false;
      bool tbfAfBlDuX = false;
      bool HErYBjhHXt = false;
      bool kHRNPCMloY = false;
      bool PFtbBLkwxQ = false;
      bool grNjGhZrWK = false;
      bool cIsJklJRjc = false;
      bool nzOWIBKPWo = false;
      bool zlJGMsshHh = false;
      bool cTPduGLjpP = false;
      bool CTLUchdqbE = false;
      bool WJVhKqymwr = false;
      bool rbKCATjjaB = false;
      bool oZZHmfZode = false;
      bool OCGCKSyhTD = false;
      string doRFRyQNJp;
      string uKRActDteM;
      string zmeowOFVwp;
      string yPOhtxMrRc;
      string QqaohXddcP;
      string yHKxWqKcJD;
      string suQTrewiGe;
      string gKbCuHLoHX;
      string jasfqpFQLC;
      string mjhOjUZHwC;
      string buXximfICO;
      string eUUkSRCjbC;
      string ZeWDqxbMRZ;
      string gErFwnDuxE;
      string JxOwWRPxwR;
      string SoetbxXTFk;
      string KTpbhabOod;
      string OGmWrbQagZ;
      string geQAHqYydz;
      string QioMtpHlOw;
      if(doRFRyQNJp == buXximfICO){oBHRCLCICA = true;}
      else if(buXximfICO == doRFRyQNJp){grNjGhZrWK = true;}
      if(uKRActDteM == eUUkSRCjbC){fxmfEeDoUp = true;}
      else if(eUUkSRCjbC == uKRActDteM){cIsJklJRjc = true;}
      if(zmeowOFVwp == ZeWDqxbMRZ){BdkpNfRZcC = true;}
      else if(ZeWDqxbMRZ == zmeowOFVwp){nzOWIBKPWo = true;}
      if(yPOhtxMrRc == gErFwnDuxE){UdLjjfWyxu = true;}
      else if(gErFwnDuxE == yPOhtxMrRc){zlJGMsshHh = true;}
      if(QqaohXddcP == JxOwWRPxwR){nQwcSSuJIO = true;}
      else if(JxOwWRPxwR == QqaohXddcP){cTPduGLjpP = true;}
      if(yHKxWqKcJD == SoetbxXTFk){lRRYuLQREV = true;}
      else if(SoetbxXTFk == yHKxWqKcJD){CTLUchdqbE = true;}
      if(suQTrewiGe == KTpbhabOod){tbfAfBlDuX = true;}
      else if(KTpbhabOod == suQTrewiGe){WJVhKqymwr = true;}
      if(gKbCuHLoHX == OGmWrbQagZ){HErYBjhHXt = true;}
      if(jasfqpFQLC == geQAHqYydz){kHRNPCMloY = true;}
      if(mjhOjUZHwC == QioMtpHlOw){PFtbBLkwxQ = true;}
      while(OGmWrbQagZ == gKbCuHLoHX){rbKCATjjaB = true;}
      while(geQAHqYydz == geQAHqYydz){oZZHmfZode = true;}
      while(QioMtpHlOw == QioMtpHlOw){OCGCKSyhTD = true;}
      if(oBHRCLCICA == true){oBHRCLCICA = false;}
      if(fxmfEeDoUp == true){fxmfEeDoUp = false;}
      if(BdkpNfRZcC == true){BdkpNfRZcC = false;}
      if(UdLjjfWyxu == true){UdLjjfWyxu = false;}
      if(nQwcSSuJIO == true){nQwcSSuJIO = false;}
      if(lRRYuLQREV == true){lRRYuLQREV = false;}
      if(tbfAfBlDuX == true){tbfAfBlDuX = false;}
      if(HErYBjhHXt == true){HErYBjhHXt = false;}
      if(kHRNPCMloY == true){kHRNPCMloY = false;}
      if(PFtbBLkwxQ == true){PFtbBLkwxQ = false;}
      if(grNjGhZrWK == true){grNjGhZrWK = false;}
      if(cIsJklJRjc == true){cIsJklJRjc = false;}
      if(nzOWIBKPWo == true){nzOWIBKPWo = false;}
      if(zlJGMsshHh == true){zlJGMsshHh = false;}
      if(cTPduGLjpP == true){cTPduGLjpP = false;}
      if(CTLUchdqbE == true){CTLUchdqbE = false;}
      if(WJVhKqymwr == true){WJVhKqymwr = false;}
      if(rbKCATjjaB == true){rbKCATjjaB = false;}
      if(oZZHmfZode == true){oZZHmfZode = false;}
      if(OCGCKSyhTD == true){OCGCKSyhTD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MSCRDGDFVJ
{ 
  void fAqTiOmBgW()
  { 
      bool HlYIpxORTI = false;
      bool ygWBmNjRxj = false;
      bool XerYYqaVpJ = false;
      bool fyOixygDsa = false;
      bool airMextiil = false;
      bool DagQrcsziy = false;
      bool VsbJczRmDn = false;
      bool ffYVInlesb = false;
      bool xqlDGEQxpU = false;
      bool FgUtEhHhje = false;
      bool eGetFWCKHD = false;
      bool pNFGAeGYDX = false;
      bool iTwiizLdRa = false;
      bool gDuOxpMqxi = false;
      bool CFpmdqaOsZ = false;
      bool aheLuKKwLG = false;
      bool LXsgVlSqIK = false;
      bool SOaTVddJEq = false;
      bool XxjrzzYiSm = false;
      bool fQfqWeLIQq = false;
      string mUHBhWfuMa;
      string cVpCrkFxQA;
      string NaToonbeJg;
      string mkrDlUisio;
      string KbynogZbfJ;
      string MhJqHLARMs;
      string uAkemqdlPW;
      string CMNbolceAH;
      string OzzAUEaBwZ;
      string TRfptJpSAx;
      string DmMIHAThBU;
      string iVRFduBjKi;
      string QcppDjfXgf;
      string uJdCDampsT;
      string jrzapyAZLy;
      string HGIRgaxVFW;
      string TwAUZZqOBD;
      string IKqpyXcPzE;
      string jFLiXoBMVc;
      string dQjVAnreAQ;
      if(mUHBhWfuMa == DmMIHAThBU){HlYIpxORTI = true;}
      else if(DmMIHAThBU == mUHBhWfuMa){eGetFWCKHD = true;}
      if(cVpCrkFxQA == iVRFduBjKi){ygWBmNjRxj = true;}
      else if(iVRFduBjKi == cVpCrkFxQA){pNFGAeGYDX = true;}
      if(NaToonbeJg == QcppDjfXgf){XerYYqaVpJ = true;}
      else if(QcppDjfXgf == NaToonbeJg){iTwiizLdRa = true;}
      if(mkrDlUisio == uJdCDampsT){fyOixygDsa = true;}
      else if(uJdCDampsT == mkrDlUisio){gDuOxpMqxi = true;}
      if(KbynogZbfJ == jrzapyAZLy){airMextiil = true;}
      else if(jrzapyAZLy == KbynogZbfJ){CFpmdqaOsZ = true;}
      if(MhJqHLARMs == HGIRgaxVFW){DagQrcsziy = true;}
      else if(HGIRgaxVFW == MhJqHLARMs){aheLuKKwLG = true;}
      if(uAkemqdlPW == TwAUZZqOBD){VsbJczRmDn = true;}
      else if(TwAUZZqOBD == uAkemqdlPW){LXsgVlSqIK = true;}
      if(CMNbolceAH == IKqpyXcPzE){ffYVInlesb = true;}
      if(OzzAUEaBwZ == jFLiXoBMVc){xqlDGEQxpU = true;}
      if(TRfptJpSAx == dQjVAnreAQ){FgUtEhHhje = true;}
      while(IKqpyXcPzE == CMNbolceAH){SOaTVddJEq = true;}
      while(jFLiXoBMVc == jFLiXoBMVc){XxjrzzYiSm = true;}
      while(dQjVAnreAQ == dQjVAnreAQ){fQfqWeLIQq = true;}
      if(HlYIpxORTI == true){HlYIpxORTI = false;}
      if(ygWBmNjRxj == true){ygWBmNjRxj = false;}
      if(XerYYqaVpJ == true){XerYYqaVpJ = false;}
      if(fyOixygDsa == true){fyOixygDsa = false;}
      if(airMextiil == true){airMextiil = false;}
      if(DagQrcsziy == true){DagQrcsziy = false;}
      if(VsbJczRmDn == true){VsbJczRmDn = false;}
      if(ffYVInlesb == true){ffYVInlesb = false;}
      if(xqlDGEQxpU == true){xqlDGEQxpU = false;}
      if(FgUtEhHhje == true){FgUtEhHhje = false;}
      if(eGetFWCKHD == true){eGetFWCKHD = false;}
      if(pNFGAeGYDX == true){pNFGAeGYDX = false;}
      if(iTwiizLdRa == true){iTwiizLdRa = false;}
      if(gDuOxpMqxi == true){gDuOxpMqxi = false;}
      if(CFpmdqaOsZ == true){CFpmdqaOsZ = false;}
      if(aheLuKKwLG == true){aheLuKKwLG = false;}
      if(LXsgVlSqIK == true){LXsgVlSqIK = false;}
      if(SOaTVddJEq == true){SOaTVddJEq = false;}
      if(XxjrzzYiSm == true){XxjrzzYiSm = false;}
      if(fQfqWeLIQq == true){fQfqWeLIQq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCVIZDTPSQ
{ 
  void uehjSGcsQJ()
  { 
      bool bFXTEWGFaf = false;
      bool qlufgoiSux = false;
      bool dpwoPLkkVJ = false;
      bool OnKJRQOOoh = false;
      bool lWIBHVDlWE = false;
      bool sJYKnkJiDs = false;
      bool kVjQQCakOP = false;
      bool ZTcMLHgugt = false;
      bool IyNQPFPAVf = false;
      bool HfKwxPlqjE = false;
      bool tRXGdYfMyf = false;
      bool ENBJjlHSBL = false;
      bool maOiItJgOu = false;
      bool UpLczpaHmq = false;
      bool YDBobsdALK = false;
      bool HSpXQTDoyi = false;
      bool PyxDLNCXKt = false;
      bool LAfKmiYYGO = false;
      bool QIVEmCAmLe = false;
      bool mkJDaZGydN = false;
      string DJsAYMENLG;
      string dTiKteOGVl;
      string iuADjCouAa;
      string mlnnjdGPAR;
      string gEqMwHRxii;
      string bzZlJHIoPV;
      string WINkTreuaP;
      string XzFDFeEnHb;
      string jqLRzmLBdb;
      string VRzdtXpGrD;
      string cWWTKcsVge;
      string DUhmlewukf;
      string fcRztGzaJg;
      string nxuDzNUrHW;
      string toUyXAjMrO;
      string auUMWAFWYD;
      string cRMAqGYdnX;
      string JEnOlqISbs;
      string WmitFsbigz;
      string IySDsbbTHR;
      if(DJsAYMENLG == cWWTKcsVge){bFXTEWGFaf = true;}
      else if(cWWTKcsVge == DJsAYMENLG){tRXGdYfMyf = true;}
      if(dTiKteOGVl == DUhmlewukf){qlufgoiSux = true;}
      else if(DUhmlewukf == dTiKteOGVl){ENBJjlHSBL = true;}
      if(iuADjCouAa == fcRztGzaJg){dpwoPLkkVJ = true;}
      else if(fcRztGzaJg == iuADjCouAa){maOiItJgOu = true;}
      if(mlnnjdGPAR == nxuDzNUrHW){OnKJRQOOoh = true;}
      else if(nxuDzNUrHW == mlnnjdGPAR){UpLczpaHmq = true;}
      if(gEqMwHRxii == toUyXAjMrO){lWIBHVDlWE = true;}
      else if(toUyXAjMrO == gEqMwHRxii){YDBobsdALK = true;}
      if(bzZlJHIoPV == auUMWAFWYD){sJYKnkJiDs = true;}
      else if(auUMWAFWYD == bzZlJHIoPV){HSpXQTDoyi = true;}
      if(WINkTreuaP == cRMAqGYdnX){kVjQQCakOP = true;}
      else if(cRMAqGYdnX == WINkTreuaP){PyxDLNCXKt = true;}
      if(XzFDFeEnHb == JEnOlqISbs){ZTcMLHgugt = true;}
      if(jqLRzmLBdb == WmitFsbigz){IyNQPFPAVf = true;}
      if(VRzdtXpGrD == IySDsbbTHR){HfKwxPlqjE = true;}
      while(JEnOlqISbs == XzFDFeEnHb){LAfKmiYYGO = true;}
      while(WmitFsbigz == WmitFsbigz){QIVEmCAmLe = true;}
      while(IySDsbbTHR == IySDsbbTHR){mkJDaZGydN = true;}
      if(bFXTEWGFaf == true){bFXTEWGFaf = false;}
      if(qlufgoiSux == true){qlufgoiSux = false;}
      if(dpwoPLkkVJ == true){dpwoPLkkVJ = false;}
      if(OnKJRQOOoh == true){OnKJRQOOoh = false;}
      if(lWIBHVDlWE == true){lWIBHVDlWE = false;}
      if(sJYKnkJiDs == true){sJYKnkJiDs = false;}
      if(kVjQQCakOP == true){kVjQQCakOP = false;}
      if(ZTcMLHgugt == true){ZTcMLHgugt = false;}
      if(IyNQPFPAVf == true){IyNQPFPAVf = false;}
      if(HfKwxPlqjE == true){HfKwxPlqjE = false;}
      if(tRXGdYfMyf == true){tRXGdYfMyf = false;}
      if(ENBJjlHSBL == true){ENBJjlHSBL = false;}
      if(maOiItJgOu == true){maOiItJgOu = false;}
      if(UpLczpaHmq == true){UpLczpaHmq = false;}
      if(YDBobsdALK == true){YDBobsdALK = false;}
      if(HSpXQTDoyi == true){HSpXQTDoyi = false;}
      if(PyxDLNCXKt == true){PyxDLNCXKt = false;}
      if(LAfKmiYYGO == true){LAfKmiYYGO = false;}
      if(QIVEmCAmLe == true){QIVEmCAmLe = false;}
      if(mkJDaZGydN == true){mkJDaZGydN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXJVEDYUYE
{ 
  void xikGmrehxR()
  { 
      bool aRebxgJnXJ = false;
      bool YhkJBGfywY = false;
      bool hATduyMYzM = false;
      bool MyLGClTqWt = false;
      bool FMrtwJCsGI = false;
      bool XrONFaxAgy = false;
      bool TkoLwaVdGO = false;
      bool lnbCSUHZhk = false;
      bool wTRqnTiyBb = false;
      bool nTKXZTXfxU = false;
      bool mYlqWjQLtk = false;
      bool SXSuCzTxXb = false;
      bool rWceaScDby = false;
      bool wabMyWgZUE = false;
      bool DXEPIQBPVa = false;
      bool AZIVcQwHQE = false;
      bool GNiunruFwe = false;
      bool RscTXUSMWK = false;
      bool QNhByVSFig = false;
      bool aZJQxonIbP = false;
      string tVsMQRqkli;
      string nOxWigkTHY;
      string cOiMactofA;
      string ausDrAKVMN;
      string CmWSUuzbqU;
      string xnPQiflgkn;
      string XBEkIsUsdi;
      string WOGsWoqQrf;
      string dRxKClecUL;
      string NdkYpAilKa;
      string aFyIyihVtt;
      string oVnFKGEshV;
      string NrYRUsdhDW;
      string FFFQEXToMT;
      string EJiaWqoeOj;
      string upDoNiffmE;
      string EzRXniQWAl;
      string lOfOQEJytd;
      string DyTTaPBQDV;
      string qnCHOEqLlm;
      if(tVsMQRqkli == aFyIyihVtt){aRebxgJnXJ = true;}
      else if(aFyIyihVtt == tVsMQRqkli){mYlqWjQLtk = true;}
      if(nOxWigkTHY == oVnFKGEshV){YhkJBGfywY = true;}
      else if(oVnFKGEshV == nOxWigkTHY){SXSuCzTxXb = true;}
      if(cOiMactofA == NrYRUsdhDW){hATduyMYzM = true;}
      else if(NrYRUsdhDW == cOiMactofA){rWceaScDby = true;}
      if(ausDrAKVMN == FFFQEXToMT){MyLGClTqWt = true;}
      else if(FFFQEXToMT == ausDrAKVMN){wabMyWgZUE = true;}
      if(CmWSUuzbqU == EJiaWqoeOj){FMrtwJCsGI = true;}
      else if(EJiaWqoeOj == CmWSUuzbqU){DXEPIQBPVa = true;}
      if(xnPQiflgkn == upDoNiffmE){XrONFaxAgy = true;}
      else if(upDoNiffmE == xnPQiflgkn){AZIVcQwHQE = true;}
      if(XBEkIsUsdi == EzRXniQWAl){TkoLwaVdGO = true;}
      else if(EzRXniQWAl == XBEkIsUsdi){GNiunruFwe = true;}
      if(WOGsWoqQrf == lOfOQEJytd){lnbCSUHZhk = true;}
      if(dRxKClecUL == DyTTaPBQDV){wTRqnTiyBb = true;}
      if(NdkYpAilKa == qnCHOEqLlm){nTKXZTXfxU = true;}
      while(lOfOQEJytd == WOGsWoqQrf){RscTXUSMWK = true;}
      while(DyTTaPBQDV == DyTTaPBQDV){QNhByVSFig = true;}
      while(qnCHOEqLlm == qnCHOEqLlm){aZJQxonIbP = true;}
      if(aRebxgJnXJ == true){aRebxgJnXJ = false;}
      if(YhkJBGfywY == true){YhkJBGfywY = false;}
      if(hATduyMYzM == true){hATduyMYzM = false;}
      if(MyLGClTqWt == true){MyLGClTqWt = false;}
      if(FMrtwJCsGI == true){FMrtwJCsGI = false;}
      if(XrONFaxAgy == true){XrONFaxAgy = false;}
      if(TkoLwaVdGO == true){TkoLwaVdGO = false;}
      if(lnbCSUHZhk == true){lnbCSUHZhk = false;}
      if(wTRqnTiyBb == true){wTRqnTiyBb = false;}
      if(nTKXZTXfxU == true){nTKXZTXfxU = false;}
      if(mYlqWjQLtk == true){mYlqWjQLtk = false;}
      if(SXSuCzTxXb == true){SXSuCzTxXb = false;}
      if(rWceaScDby == true){rWceaScDby = false;}
      if(wabMyWgZUE == true){wabMyWgZUE = false;}
      if(DXEPIQBPVa == true){DXEPIQBPVa = false;}
      if(AZIVcQwHQE == true){AZIVcQwHQE = false;}
      if(GNiunruFwe == true){GNiunruFwe = false;}
      if(RscTXUSMWK == true){RscTXUSMWK = false;}
      if(QNhByVSFig == true){QNhByVSFig = false;}
      if(aZJQxonIbP == true){aZJQxonIbP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLBWNWAWDK
{ 
  void ooYWGoNspt()
  { 
      bool ayfNtfKROH = false;
      bool FANRrAgVZi = false;
      bool LIGFRbKFfH = false;
      bool ZLqPWIOmbT = false;
      bool EDGafcoNlG = false;
      bool ByrPcSqauS = false;
      bool VEkHgsJxui = false;
      bool lssFdIBeYo = false;
      bool mwTZFbTamE = false;
      bool QmrIxzRztl = false;
      bool SqSCTHEllU = false;
      bool QMBFfZkLBE = false;
      bool YiKpSzBjIe = false;
      bool pCkmWucQFy = false;
      bool WhnSmEklcX = false;
      bool NGxoMigbjU = false;
      bool FUdHdNaOij = false;
      bool wUFDhqtqDN = false;
      bool NPHjQjFuZm = false;
      bool OAfkrCEgnZ = false;
      string BxXaqigPhA;
      string QZiSBnTZKh;
      string TWKGoaSkbb;
      string kKPmKseTpo;
      string DyBZOPaCYD;
      string MbJafemRkQ;
      string PwnFPGKuHI;
      string IzjUdVVjrZ;
      string zQLYPIAnHf;
      string GNhZYHKuKH;
      string FeuQtMrnwJ;
      string ICZLQzkOpG;
      string GVnbBuRJwW;
      string LaYjUUUtdC;
      string QLqxWEnWJY;
      string WuFEBiqSOz;
      string uhrZyhcopu;
      string dpjmptdpFx;
      string HtAWAPVUik;
      string dCfeHiTRzo;
      if(BxXaqigPhA == FeuQtMrnwJ){ayfNtfKROH = true;}
      else if(FeuQtMrnwJ == BxXaqigPhA){SqSCTHEllU = true;}
      if(QZiSBnTZKh == ICZLQzkOpG){FANRrAgVZi = true;}
      else if(ICZLQzkOpG == QZiSBnTZKh){QMBFfZkLBE = true;}
      if(TWKGoaSkbb == GVnbBuRJwW){LIGFRbKFfH = true;}
      else if(GVnbBuRJwW == TWKGoaSkbb){YiKpSzBjIe = true;}
      if(kKPmKseTpo == LaYjUUUtdC){ZLqPWIOmbT = true;}
      else if(LaYjUUUtdC == kKPmKseTpo){pCkmWucQFy = true;}
      if(DyBZOPaCYD == QLqxWEnWJY){EDGafcoNlG = true;}
      else if(QLqxWEnWJY == DyBZOPaCYD){WhnSmEklcX = true;}
      if(MbJafemRkQ == WuFEBiqSOz){ByrPcSqauS = true;}
      else if(WuFEBiqSOz == MbJafemRkQ){NGxoMigbjU = true;}
      if(PwnFPGKuHI == uhrZyhcopu){VEkHgsJxui = true;}
      else if(uhrZyhcopu == PwnFPGKuHI){FUdHdNaOij = true;}
      if(IzjUdVVjrZ == dpjmptdpFx){lssFdIBeYo = true;}
      if(zQLYPIAnHf == HtAWAPVUik){mwTZFbTamE = true;}
      if(GNhZYHKuKH == dCfeHiTRzo){QmrIxzRztl = true;}
      while(dpjmptdpFx == IzjUdVVjrZ){wUFDhqtqDN = true;}
      while(HtAWAPVUik == HtAWAPVUik){NPHjQjFuZm = true;}
      while(dCfeHiTRzo == dCfeHiTRzo){OAfkrCEgnZ = true;}
      if(ayfNtfKROH == true){ayfNtfKROH = false;}
      if(FANRrAgVZi == true){FANRrAgVZi = false;}
      if(LIGFRbKFfH == true){LIGFRbKFfH = false;}
      if(ZLqPWIOmbT == true){ZLqPWIOmbT = false;}
      if(EDGafcoNlG == true){EDGafcoNlG = false;}
      if(ByrPcSqauS == true){ByrPcSqauS = false;}
      if(VEkHgsJxui == true){VEkHgsJxui = false;}
      if(lssFdIBeYo == true){lssFdIBeYo = false;}
      if(mwTZFbTamE == true){mwTZFbTamE = false;}
      if(QmrIxzRztl == true){QmrIxzRztl = false;}
      if(SqSCTHEllU == true){SqSCTHEllU = false;}
      if(QMBFfZkLBE == true){QMBFfZkLBE = false;}
      if(YiKpSzBjIe == true){YiKpSzBjIe = false;}
      if(pCkmWucQFy == true){pCkmWucQFy = false;}
      if(WhnSmEklcX == true){WhnSmEklcX = false;}
      if(NGxoMigbjU == true){NGxoMigbjU = false;}
      if(FUdHdNaOij == true){FUdHdNaOij = false;}
      if(wUFDhqtqDN == true){wUFDhqtqDN = false;}
      if(NPHjQjFuZm == true){NPHjQjFuZm = false;}
      if(OAfkrCEgnZ == true){OAfkrCEgnZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDIIFSOFKL
{ 
  void bBxNSqmVqn()
  { 
      bool KljZmacxnA = false;
      bool ZNWjNjSqJY = false;
      bool FbUrNLihkf = false;
      bool lcVJZulbOx = false;
      bool KrXMUoRfnw = false;
      bool FjZpEiRqLa = false;
      bool quLHNxrMJR = false;
      bool xqbLONDHXY = false;
      bool tDtoZCCfEq = false;
      bool dtQnGOgPyW = false;
      bool xEWVyOINbq = false;
      bool eJTmgnBWhL = false;
      bool tMHSnCanFz = false;
      bool fmJAbogXpL = false;
      bool toDNLUZcHS = false;
      bool NJhmbjwDhu = false;
      bool nTIcLqATLq = false;
      bool HcgWRFItGT = false;
      bool cxglkWFVXq = false;
      bool scptWZfaCU = false;
      string EhnFxhzqPc;
      string kZqNEgtoIH;
      string LgsIoTCURY;
      string WxwreeFImz;
      string sSJxkrICdX;
      string lPrxFXneQd;
      string fdZqGncziZ;
      string akBJOrWwXw;
      string LzqsmHEzmH;
      string paqJTOsSqx;
      string PJTEwANihM;
      string ArHUSfmfEy;
      string icLbiAtroA;
      string zEEagBflxl;
      string tURaGySWpm;
      string aMOrNlyqVu;
      string GUshMwmgmQ;
      string AAiRENLjUk;
      string hWBCYmpLMu;
      string DnQBfYbiOK;
      if(EhnFxhzqPc == PJTEwANihM){KljZmacxnA = true;}
      else if(PJTEwANihM == EhnFxhzqPc){xEWVyOINbq = true;}
      if(kZqNEgtoIH == ArHUSfmfEy){ZNWjNjSqJY = true;}
      else if(ArHUSfmfEy == kZqNEgtoIH){eJTmgnBWhL = true;}
      if(LgsIoTCURY == icLbiAtroA){FbUrNLihkf = true;}
      else if(icLbiAtroA == LgsIoTCURY){tMHSnCanFz = true;}
      if(WxwreeFImz == zEEagBflxl){lcVJZulbOx = true;}
      else if(zEEagBflxl == WxwreeFImz){fmJAbogXpL = true;}
      if(sSJxkrICdX == tURaGySWpm){KrXMUoRfnw = true;}
      else if(tURaGySWpm == sSJxkrICdX){toDNLUZcHS = true;}
      if(lPrxFXneQd == aMOrNlyqVu){FjZpEiRqLa = true;}
      else if(aMOrNlyqVu == lPrxFXneQd){NJhmbjwDhu = true;}
      if(fdZqGncziZ == GUshMwmgmQ){quLHNxrMJR = true;}
      else if(GUshMwmgmQ == fdZqGncziZ){nTIcLqATLq = true;}
      if(akBJOrWwXw == AAiRENLjUk){xqbLONDHXY = true;}
      if(LzqsmHEzmH == hWBCYmpLMu){tDtoZCCfEq = true;}
      if(paqJTOsSqx == DnQBfYbiOK){dtQnGOgPyW = true;}
      while(AAiRENLjUk == akBJOrWwXw){HcgWRFItGT = true;}
      while(hWBCYmpLMu == hWBCYmpLMu){cxglkWFVXq = true;}
      while(DnQBfYbiOK == DnQBfYbiOK){scptWZfaCU = true;}
      if(KljZmacxnA == true){KljZmacxnA = false;}
      if(ZNWjNjSqJY == true){ZNWjNjSqJY = false;}
      if(FbUrNLihkf == true){FbUrNLihkf = false;}
      if(lcVJZulbOx == true){lcVJZulbOx = false;}
      if(KrXMUoRfnw == true){KrXMUoRfnw = false;}
      if(FjZpEiRqLa == true){FjZpEiRqLa = false;}
      if(quLHNxrMJR == true){quLHNxrMJR = false;}
      if(xqbLONDHXY == true){xqbLONDHXY = false;}
      if(tDtoZCCfEq == true){tDtoZCCfEq = false;}
      if(dtQnGOgPyW == true){dtQnGOgPyW = false;}
      if(xEWVyOINbq == true){xEWVyOINbq = false;}
      if(eJTmgnBWhL == true){eJTmgnBWhL = false;}
      if(tMHSnCanFz == true){tMHSnCanFz = false;}
      if(fmJAbogXpL == true){fmJAbogXpL = false;}
      if(toDNLUZcHS == true){toDNLUZcHS = false;}
      if(NJhmbjwDhu == true){NJhmbjwDhu = false;}
      if(nTIcLqATLq == true){nTIcLqATLq = false;}
      if(HcgWRFItGT == true){HcgWRFItGT = false;}
      if(cxglkWFVXq == true){cxglkWFVXq = false;}
      if(scptWZfaCU == true){scptWZfaCU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DSGSMQTTJN
{ 
  void AIylXGQBOt()
  { 
      bool oklmBGCqdx = false;
      bool rujYOpNkoH = false;
      bool QimWPNXaeg = false;
      bool sArrHAZFCZ = false;
      bool asqDBsUJnf = false;
      bool dWqyiGyOWn = false;
      bool ibMwEqDrRO = false;
      bool PHhPfXqiVV = false;
      bool rOlyCWJtJB = false;
      bool BKiNqzfuzJ = false;
      bool pcrZPWnbRK = false;
      bool OOsBwToNth = false;
      bool hIiPMEYUXg = false;
      bool qwjLfPWMhf = false;
      bool hhcylmRhRW = false;
      bool KSARbgsbML = false;
      bool xTDjTSegUf = false;
      bool xceOzAfkcZ = false;
      bool mqCBVYuRjz = false;
      bool VuzWhOereT = false;
      string MPmApBPBYI;
      string dLsiHZxzQX;
      string ninCoiymCH;
      string tTHNJwzwkW;
      string CNkoFNQuWm;
      string RFHmXcajKG;
      string CbyRNJEfZK;
      string aAOsUaxzwb;
      string SCQPpoLTof;
      string UOkeUZPTaw;
      string JjVLMQpORx;
      string ebnimALhaX;
      string xjpsoLOjYu;
      string KdXzSigEDY;
      string yxCrBsZCqU;
      string NgsCyYtbVA;
      string CGoVlBEnQE;
      string SGdBYAgyrw;
      string kMrEgdjUBs;
      string oFiDWrHfFz;
      if(MPmApBPBYI == JjVLMQpORx){oklmBGCqdx = true;}
      else if(JjVLMQpORx == MPmApBPBYI){pcrZPWnbRK = true;}
      if(dLsiHZxzQX == ebnimALhaX){rujYOpNkoH = true;}
      else if(ebnimALhaX == dLsiHZxzQX){OOsBwToNth = true;}
      if(ninCoiymCH == xjpsoLOjYu){QimWPNXaeg = true;}
      else if(xjpsoLOjYu == ninCoiymCH){hIiPMEYUXg = true;}
      if(tTHNJwzwkW == KdXzSigEDY){sArrHAZFCZ = true;}
      else if(KdXzSigEDY == tTHNJwzwkW){qwjLfPWMhf = true;}
      if(CNkoFNQuWm == yxCrBsZCqU){asqDBsUJnf = true;}
      else if(yxCrBsZCqU == CNkoFNQuWm){hhcylmRhRW = true;}
      if(RFHmXcajKG == NgsCyYtbVA){dWqyiGyOWn = true;}
      else if(NgsCyYtbVA == RFHmXcajKG){KSARbgsbML = true;}
      if(CbyRNJEfZK == CGoVlBEnQE){ibMwEqDrRO = true;}
      else if(CGoVlBEnQE == CbyRNJEfZK){xTDjTSegUf = true;}
      if(aAOsUaxzwb == SGdBYAgyrw){PHhPfXqiVV = true;}
      if(SCQPpoLTof == kMrEgdjUBs){rOlyCWJtJB = true;}
      if(UOkeUZPTaw == oFiDWrHfFz){BKiNqzfuzJ = true;}
      while(SGdBYAgyrw == aAOsUaxzwb){xceOzAfkcZ = true;}
      while(kMrEgdjUBs == kMrEgdjUBs){mqCBVYuRjz = true;}
      while(oFiDWrHfFz == oFiDWrHfFz){VuzWhOereT = true;}
      if(oklmBGCqdx == true){oklmBGCqdx = false;}
      if(rujYOpNkoH == true){rujYOpNkoH = false;}
      if(QimWPNXaeg == true){QimWPNXaeg = false;}
      if(sArrHAZFCZ == true){sArrHAZFCZ = false;}
      if(asqDBsUJnf == true){asqDBsUJnf = false;}
      if(dWqyiGyOWn == true){dWqyiGyOWn = false;}
      if(ibMwEqDrRO == true){ibMwEqDrRO = false;}
      if(PHhPfXqiVV == true){PHhPfXqiVV = false;}
      if(rOlyCWJtJB == true){rOlyCWJtJB = false;}
      if(BKiNqzfuzJ == true){BKiNqzfuzJ = false;}
      if(pcrZPWnbRK == true){pcrZPWnbRK = false;}
      if(OOsBwToNth == true){OOsBwToNth = false;}
      if(hIiPMEYUXg == true){hIiPMEYUXg = false;}
      if(qwjLfPWMhf == true){qwjLfPWMhf = false;}
      if(hhcylmRhRW == true){hhcylmRhRW = false;}
      if(KSARbgsbML == true){KSARbgsbML = false;}
      if(xTDjTSegUf == true){xTDjTSegUf = false;}
      if(xceOzAfkcZ == true){xceOzAfkcZ = false;}
      if(mqCBVYuRjz == true){mqCBVYuRjz = false;}
      if(VuzWhOereT == true){VuzWhOereT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OIYHFDAOVK
{ 
  void tiSnqnqPKQ()
  { 
      bool qFOGXotyNj = false;
      bool xRJlkECcFc = false;
      bool rICAAlBmeQ = false;
      bool oHmyRxizRT = false;
      bool XpEceEDEyk = false;
      bool WhYxiiDNFl = false;
      bool mHTwtpdKTm = false;
      bool VCKlECEYVw = false;
      bool hwostGhpPi = false;
      bool tUtffPVHho = false;
      bool ZrkKOTWmrg = false;
      bool ddrIDpSZCm = false;
      bool HnuksAIdGo = false;
      bool fwqfVpLeeZ = false;
      bool juxhEQckco = false;
      bool wwFtgkwzQO = false;
      bool LsgDAhmLmN = false;
      bool enubDMqMgc = false;
      bool XXBQrjqwzj = false;
      bool sMNPNpOshW = false;
      string sShgRGAnuB;
      string FnOBwNQmyC;
      string mQXKRXCPHy;
      string ESJcYIFuzU;
      string yrcYArDrIV;
      string NfIKabtWOt;
      string Ekfxwmdlcn;
      string HVncEunyKZ;
      string TJGljYJzBw;
      string NhfEQMLfbN;
      string NQOUNrqfFe;
      string nwMoatdtMX;
      string cejgZYoiMq;
      string jHVxLCukXr;
      string gdsVHRVqdW;
      string hQSEjifhto;
      string CHSOugZPcX;
      string ysVUpzlNYI;
      string DxFpISnRMb;
      string WMqioYKeaa;
      if(sShgRGAnuB == NQOUNrqfFe){qFOGXotyNj = true;}
      else if(NQOUNrqfFe == sShgRGAnuB){ZrkKOTWmrg = true;}
      if(FnOBwNQmyC == nwMoatdtMX){xRJlkECcFc = true;}
      else if(nwMoatdtMX == FnOBwNQmyC){ddrIDpSZCm = true;}
      if(mQXKRXCPHy == cejgZYoiMq){rICAAlBmeQ = true;}
      else if(cejgZYoiMq == mQXKRXCPHy){HnuksAIdGo = true;}
      if(ESJcYIFuzU == jHVxLCukXr){oHmyRxizRT = true;}
      else if(jHVxLCukXr == ESJcYIFuzU){fwqfVpLeeZ = true;}
      if(yrcYArDrIV == gdsVHRVqdW){XpEceEDEyk = true;}
      else if(gdsVHRVqdW == yrcYArDrIV){juxhEQckco = true;}
      if(NfIKabtWOt == hQSEjifhto){WhYxiiDNFl = true;}
      else if(hQSEjifhto == NfIKabtWOt){wwFtgkwzQO = true;}
      if(Ekfxwmdlcn == CHSOugZPcX){mHTwtpdKTm = true;}
      else if(CHSOugZPcX == Ekfxwmdlcn){LsgDAhmLmN = true;}
      if(HVncEunyKZ == ysVUpzlNYI){VCKlECEYVw = true;}
      if(TJGljYJzBw == DxFpISnRMb){hwostGhpPi = true;}
      if(NhfEQMLfbN == WMqioYKeaa){tUtffPVHho = true;}
      while(ysVUpzlNYI == HVncEunyKZ){enubDMqMgc = true;}
      while(DxFpISnRMb == DxFpISnRMb){XXBQrjqwzj = true;}
      while(WMqioYKeaa == WMqioYKeaa){sMNPNpOshW = true;}
      if(qFOGXotyNj == true){qFOGXotyNj = false;}
      if(xRJlkECcFc == true){xRJlkECcFc = false;}
      if(rICAAlBmeQ == true){rICAAlBmeQ = false;}
      if(oHmyRxizRT == true){oHmyRxizRT = false;}
      if(XpEceEDEyk == true){XpEceEDEyk = false;}
      if(WhYxiiDNFl == true){WhYxiiDNFl = false;}
      if(mHTwtpdKTm == true){mHTwtpdKTm = false;}
      if(VCKlECEYVw == true){VCKlECEYVw = false;}
      if(hwostGhpPi == true){hwostGhpPi = false;}
      if(tUtffPVHho == true){tUtffPVHho = false;}
      if(ZrkKOTWmrg == true){ZrkKOTWmrg = false;}
      if(ddrIDpSZCm == true){ddrIDpSZCm = false;}
      if(HnuksAIdGo == true){HnuksAIdGo = false;}
      if(fwqfVpLeeZ == true){fwqfVpLeeZ = false;}
      if(juxhEQckco == true){juxhEQckco = false;}
      if(wwFtgkwzQO == true){wwFtgkwzQO = false;}
      if(LsgDAhmLmN == true){LsgDAhmLmN = false;}
      if(enubDMqMgc == true){enubDMqMgc = false;}
      if(XXBQrjqwzj == true){XXBQrjqwzj = false;}
      if(sMNPNpOshW == true){sMNPNpOshW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MRKYCIMGUX
{ 
  void ffTGfqEgGl()
  { 
      bool DHgCiXQWHR = false;
      bool BhAoXbISlz = false;
      bool SLcjhFqmMt = false;
      bool PeyakRWYbl = false;
      bool aQZKsUJEXa = false;
      bool kNGCwqdwTc = false;
      bool fdKMBWiZEF = false;
      bool FjpzYBlRqN = false;
      bool wlPkJCYwes = false;
      bool mZFyGwGMIW = false;
      bool ljARVBWGct = false;
      bool FLFGgsOYDz = false;
      bool xltKSedrsb = false;
      bool uYJUaMlyPH = false;
      bool eSTknaUzRM = false;
      bool hhJJYzopyp = false;
      bool WeNAzfCkeT = false;
      bool HQIuTeSJVq = false;
      bool KeZftMPzub = false;
      bool WuzZjAFSlH = false;
      string YRtJHzORtz;
      string SVFOpUxdRJ;
      string zeCjERaNMM;
      string EOGgxiVRBo;
      string VfSKYzBUXj;
      string daQDDsOJEo;
      string XBEguDOXQG;
      string zebcnSLrLE;
      string PFpchcyDdE;
      string TLNMRUakOU;
      string jdEQjyznPj;
      string gWxzYRKazS;
      string FLtMlmROKT;
      string rZcqTlBYrj;
      string dJnsWxNNnz;
      string JzlwOYiqex;
      string gjcwrHsGfl;
      string QlhPnwWApo;
      string YEaKJrngcu;
      string DKtuCtfrBO;
      if(YRtJHzORtz == jdEQjyznPj){DHgCiXQWHR = true;}
      else if(jdEQjyznPj == YRtJHzORtz){ljARVBWGct = true;}
      if(SVFOpUxdRJ == gWxzYRKazS){BhAoXbISlz = true;}
      else if(gWxzYRKazS == SVFOpUxdRJ){FLFGgsOYDz = true;}
      if(zeCjERaNMM == FLtMlmROKT){SLcjhFqmMt = true;}
      else if(FLtMlmROKT == zeCjERaNMM){xltKSedrsb = true;}
      if(EOGgxiVRBo == rZcqTlBYrj){PeyakRWYbl = true;}
      else if(rZcqTlBYrj == EOGgxiVRBo){uYJUaMlyPH = true;}
      if(VfSKYzBUXj == dJnsWxNNnz){aQZKsUJEXa = true;}
      else if(dJnsWxNNnz == VfSKYzBUXj){eSTknaUzRM = true;}
      if(daQDDsOJEo == JzlwOYiqex){kNGCwqdwTc = true;}
      else if(JzlwOYiqex == daQDDsOJEo){hhJJYzopyp = true;}
      if(XBEguDOXQG == gjcwrHsGfl){fdKMBWiZEF = true;}
      else if(gjcwrHsGfl == XBEguDOXQG){WeNAzfCkeT = true;}
      if(zebcnSLrLE == QlhPnwWApo){FjpzYBlRqN = true;}
      if(PFpchcyDdE == YEaKJrngcu){wlPkJCYwes = true;}
      if(TLNMRUakOU == DKtuCtfrBO){mZFyGwGMIW = true;}
      while(QlhPnwWApo == zebcnSLrLE){HQIuTeSJVq = true;}
      while(YEaKJrngcu == YEaKJrngcu){KeZftMPzub = true;}
      while(DKtuCtfrBO == DKtuCtfrBO){WuzZjAFSlH = true;}
      if(DHgCiXQWHR == true){DHgCiXQWHR = false;}
      if(BhAoXbISlz == true){BhAoXbISlz = false;}
      if(SLcjhFqmMt == true){SLcjhFqmMt = false;}
      if(PeyakRWYbl == true){PeyakRWYbl = false;}
      if(aQZKsUJEXa == true){aQZKsUJEXa = false;}
      if(kNGCwqdwTc == true){kNGCwqdwTc = false;}
      if(fdKMBWiZEF == true){fdKMBWiZEF = false;}
      if(FjpzYBlRqN == true){FjpzYBlRqN = false;}
      if(wlPkJCYwes == true){wlPkJCYwes = false;}
      if(mZFyGwGMIW == true){mZFyGwGMIW = false;}
      if(ljARVBWGct == true){ljARVBWGct = false;}
      if(FLFGgsOYDz == true){FLFGgsOYDz = false;}
      if(xltKSedrsb == true){xltKSedrsb = false;}
      if(uYJUaMlyPH == true){uYJUaMlyPH = false;}
      if(eSTknaUzRM == true){eSTknaUzRM = false;}
      if(hhJJYzopyp == true){hhJJYzopyp = false;}
      if(WeNAzfCkeT == true){WeNAzfCkeT = false;}
      if(HQIuTeSJVq == true){HQIuTeSJVq = false;}
      if(KeZftMPzub == true){KeZftMPzub = false;}
      if(WuzZjAFSlH == true){WuzZjAFSlH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDWTFGDPXV
{ 
  void ZqytdkGwSS()
  { 
      bool QWzXWtucCG = false;
      bool VfDeZIcSTe = false;
      bool lEaWWCMqFi = false;
      bool ltZHyeJUFS = false;
      bool zZtYCZOhZp = false;
      bool EXqIEMwcAU = false;
      bool gDXTTaGufu = false;
      bool yHNAfLJBTx = false;
      bool meROeNDQCl = false;
      bool ifTjluCZEa = false;
      bool STCdqwKpcs = false;
      bool CtJChBkJoG = false;
      bool XprsMRncOj = false;
      bool JixreTcmWh = false;
      bool CMmJinWQBj = false;
      bool JskyDcaIRY = false;
      bool IhbriTxQXO = false;
      bool YxlGELCiJX = false;
      bool uWaeZQyyoB = false;
      bool sTVyZUktZP = false;
      string GfSbhYrbIe;
      string szIIROLwiu;
      string wtOiDkccYC;
      string yYxNUAiPZe;
      string OJHPTbPXtn;
      string QiUrsMQjXx;
      string wODGfTCunR;
      string euVEfmlzOa;
      string UFijlODETH;
      string jzqcizFBiz;
      string ZUibIVNQMG;
      string aRUwcqfSTQ;
      string QxafhfDrUf;
      string gkPOBzVGbQ;
      string BmqNgRdtAr;
      string TlgSibsCtb;
      string RUufYpBGuc;
      string UZqDPcFNzP;
      string CIrcMtDxeY;
      string FSMzygqLnq;
      if(GfSbhYrbIe == ZUibIVNQMG){QWzXWtucCG = true;}
      else if(ZUibIVNQMG == GfSbhYrbIe){STCdqwKpcs = true;}
      if(szIIROLwiu == aRUwcqfSTQ){VfDeZIcSTe = true;}
      else if(aRUwcqfSTQ == szIIROLwiu){CtJChBkJoG = true;}
      if(wtOiDkccYC == QxafhfDrUf){lEaWWCMqFi = true;}
      else if(QxafhfDrUf == wtOiDkccYC){XprsMRncOj = true;}
      if(yYxNUAiPZe == gkPOBzVGbQ){ltZHyeJUFS = true;}
      else if(gkPOBzVGbQ == yYxNUAiPZe){JixreTcmWh = true;}
      if(OJHPTbPXtn == BmqNgRdtAr){zZtYCZOhZp = true;}
      else if(BmqNgRdtAr == OJHPTbPXtn){CMmJinWQBj = true;}
      if(QiUrsMQjXx == TlgSibsCtb){EXqIEMwcAU = true;}
      else if(TlgSibsCtb == QiUrsMQjXx){JskyDcaIRY = true;}
      if(wODGfTCunR == RUufYpBGuc){gDXTTaGufu = true;}
      else if(RUufYpBGuc == wODGfTCunR){IhbriTxQXO = true;}
      if(euVEfmlzOa == UZqDPcFNzP){yHNAfLJBTx = true;}
      if(UFijlODETH == CIrcMtDxeY){meROeNDQCl = true;}
      if(jzqcizFBiz == FSMzygqLnq){ifTjluCZEa = true;}
      while(UZqDPcFNzP == euVEfmlzOa){YxlGELCiJX = true;}
      while(CIrcMtDxeY == CIrcMtDxeY){uWaeZQyyoB = true;}
      while(FSMzygqLnq == FSMzygqLnq){sTVyZUktZP = true;}
      if(QWzXWtucCG == true){QWzXWtucCG = false;}
      if(VfDeZIcSTe == true){VfDeZIcSTe = false;}
      if(lEaWWCMqFi == true){lEaWWCMqFi = false;}
      if(ltZHyeJUFS == true){ltZHyeJUFS = false;}
      if(zZtYCZOhZp == true){zZtYCZOhZp = false;}
      if(EXqIEMwcAU == true){EXqIEMwcAU = false;}
      if(gDXTTaGufu == true){gDXTTaGufu = false;}
      if(yHNAfLJBTx == true){yHNAfLJBTx = false;}
      if(meROeNDQCl == true){meROeNDQCl = false;}
      if(ifTjluCZEa == true){ifTjluCZEa = false;}
      if(STCdqwKpcs == true){STCdqwKpcs = false;}
      if(CtJChBkJoG == true){CtJChBkJoG = false;}
      if(XprsMRncOj == true){XprsMRncOj = false;}
      if(JixreTcmWh == true){JixreTcmWh = false;}
      if(CMmJinWQBj == true){CMmJinWQBj = false;}
      if(JskyDcaIRY == true){JskyDcaIRY = false;}
      if(IhbriTxQXO == true){IhbriTxQXO = false;}
      if(YxlGELCiJX == true){YxlGELCiJX = false;}
      if(uWaeZQyyoB == true){uWaeZQyyoB = false;}
      if(sTVyZUktZP == true){sTVyZUktZP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDZRJWDJIA
{ 
  void HOZwgeunQO()
  { 
      bool cuHhVTExMt = false;
      bool QGgLgcbxhQ = false;
      bool NsXgtwgpON = false;
      bool EhsKwauTZy = false;
      bool aQgnLZhGsV = false;
      bool cVYMwjWZnY = false;
      bool mNizphNVOG = false;
      bool hHWjoxLjVT = false;
      bool OZxrjhJfOL = false;
      bool DVfALNhhxc = false;
      bool MMrlnVynWz = false;
      bool YmDTJMPpOH = false;
      bool YgGCCMbWYb = false;
      bool OdmrGChLEO = false;
      bool jUIPmQRMpy = false;
      bool xrSoEfFoib = false;
      bool taPujtAKMH = false;
      bool eEkAXDXqOl = false;
      bool tOfadVLxna = false;
      bool wrbcUIFNer = false;
      string kiOBqsNJbw;
      string yYzVSrJUBK;
      string eEOJaXndKF;
      string VljhVyMhNP;
      string EOaHKqoLxG;
      string awGqMfTEZS;
      string FizWaMoQzU;
      string eaGlGQdHyi;
      string hcfEdYerVp;
      string dHHtJVPDgy;
      string CXLcazpUkw;
      string CMGpkcCtrB;
      string gwuJqXTLbk;
      string AZZzgJQDde;
      string iKHYmQBQJg;
      string SUKfRFcCkD;
      string fdrAucmGJa;
      string LyQNSWoVVZ;
      string VCCuReOthb;
      string gORZzESGcK;
      if(kiOBqsNJbw == CXLcazpUkw){cuHhVTExMt = true;}
      else if(CXLcazpUkw == kiOBqsNJbw){MMrlnVynWz = true;}
      if(yYzVSrJUBK == CMGpkcCtrB){QGgLgcbxhQ = true;}
      else if(CMGpkcCtrB == yYzVSrJUBK){YmDTJMPpOH = true;}
      if(eEOJaXndKF == gwuJqXTLbk){NsXgtwgpON = true;}
      else if(gwuJqXTLbk == eEOJaXndKF){YgGCCMbWYb = true;}
      if(VljhVyMhNP == AZZzgJQDde){EhsKwauTZy = true;}
      else if(AZZzgJQDde == VljhVyMhNP){OdmrGChLEO = true;}
      if(EOaHKqoLxG == iKHYmQBQJg){aQgnLZhGsV = true;}
      else if(iKHYmQBQJg == EOaHKqoLxG){jUIPmQRMpy = true;}
      if(awGqMfTEZS == SUKfRFcCkD){cVYMwjWZnY = true;}
      else if(SUKfRFcCkD == awGqMfTEZS){xrSoEfFoib = true;}
      if(FizWaMoQzU == fdrAucmGJa){mNizphNVOG = true;}
      else if(fdrAucmGJa == FizWaMoQzU){taPujtAKMH = true;}
      if(eaGlGQdHyi == LyQNSWoVVZ){hHWjoxLjVT = true;}
      if(hcfEdYerVp == VCCuReOthb){OZxrjhJfOL = true;}
      if(dHHtJVPDgy == gORZzESGcK){DVfALNhhxc = true;}
      while(LyQNSWoVVZ == eaGlGQdHyi){eEkAXDXqOl = true;}
      while(VCCuReOthb == VCCuReOthb){tOfadVLxna = true;}
      while(gORZzESGcK == gORZzESGcK){wrbcUIFNer = true;}
      if(cuHhVTExMt == true){cuHhVTExMt = false;}
      if(QGgLgcbxhQ == true){QGgLgcbxhQ = false;}
      if(NsXgtwgpON == true){NsXgtwgpON = false;}
      if(EhsKwauTZy == true){EhsKwauTZy = false;}
      if(aQgnLZhGsV == true){aQgnLZhGsV = false;}
      if(cVYMwjWZnY == true){cVYMwjWZnY = false;}
      if(mNizphNVOG == true){mNizphNVOG = false;}
      if(hHWjoxLjVT == true){hHWjoxLjVT = false;}
      if(OZxrjhJfOL == true){OZxrjhJfOL = false;}
      if(DVfALNhhxc == true){DVfALNhhxc = false;}
      if(MMrlnVynWz == true){MMrlnVynWz = false;}
      if(YmDTJMPpOH == true){YmDTJMPpOH = false;}
      if(YgGCCMbWYb == true){YgGCCMbWYb = false;}
      if(OdmrGChLEO == true){OdmrGChLEO = false;}
      if(jUIPmQRMpy == true){jUIPmQRMpy = false;}
      if(xrSoEfFoib == true){xrSoEfFoib = false;}
      if(taPujtAKMH == true){taPujtAKMH = false;}
      if(eEkAXDXqOl == true){eEkAXDXqOl = false;}
      if(tOfadVLxna == true){tOfadVLxna = false;}
      if(wrbcUIFNer == true){wrbcUIFNer = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTDEIGDQXF
{ 
  void QEboRfkEPC()
  { 
      bool xRHjjrdCdi = false;
      bool yWdHlsBRNC = false;
      bool lGKFKLquRP = false;
      bool knDxfpXZrA = false;
      bool uIkwNYsHPe = false;
      bool wKOFRqGCYY = false;
      bool BikNxJSfau = false;
      bool VbZNGcUOql = false;
      bool RiemTaZyfo = false;
      bool iUATyLXWyE = false;
      bool FNgUIUkByn = false;
      bool VrKmGRExtW = false;
      bool iUAlLAaGOt = false;
      bool FyPmfECJdy = false;
      bool oYArSqJNMf = false;
      bool HZcbUkMtJH = false;
      bool temDhXcWGC = false;
      bool PuTugKTISU = false;
      bool pNshmfUnSu = false;
      bool qHAVEKlwJu = false;
      string JXJUpFFzjt;
      string EUXrjiQtpG;
      string nZZknxcLBX;
      string EHlNlrwwTk;
      string DSqEcynoaw;
      string xkuCzjxYgs;
      string ctyMpwiJFq;
      string mTaECVhVHo;
      string InkFZSMiNC;
      string tXPaIJTeOf;
      string OdiiJcKpAd;
      string BbQqjnJslW;
      string jAuDwOEzws;
      string BDGaZdECww;
      string IVijBSGYpT;
      string AarrwOhflt;
      string YKtGcxUoQG;
      string jHwoNNQLBd;
      string IeJbsZLOeL;
      string uXPBXxbbHD;
      if(JXJUpFFzjt == OdiiJcKpAd){xRHjjrdCdi = true;}
      else if(OdiiJcKpAd == JXJUpFFzjt){FNgUIUkByn = true;}
      if(EUXrjiQtpG == BbQqjnJslW){yWdHlsBRNC = true;}
      else if(BbQqjnJslW == EUXrjiQtpG){VrKmGRExtW = true;}
      if(nZZknxcLBX == jAuDwOEzws){lGKFKLquRP = true;}
      else if(jAuDwOEzws == nZZknxcLBX){iUAlLAaGOt = true;}
      if(EHlNlrwwTk == BDGaZdECww){knDxfpXZrA = true;}
      else if(BDGaZdECww == EHlNlrwwTk){FyPmfECJdy = true;}
      if(DSqEcynoaw == IVijBSGYpT){uIkwNYsHPe = true;}
      else if(IVijBSGYpT == DSqEcynoaw){oYArSqJNMf = true;}
      if(xkuCzjxYgs == AarrwOhflt){wKOFRqGCYY = true;}
      else if(AarrwOhflt == xkuCzjxYgs){HZcbUkMtJH = true;}
      if(ctyMpwiJFq == YKtGcxUoQG){BikNxJSfau = true;}
      else if(YKtGcxUoQG == ctyMpwiJFq){temDhXcWGC = true;}
      if(mTaECVhVHo == jHwoNNQLBd){VbZNGcUOql = true;}
      if(InkFZSMiNC == IeJbsZLOeL){RiemTaZyfo = true;}
      if(tXPaIJTeOf == uXPBXxbbHD){iUATyLXWyE = true;}
      while(jHwoNNQLBd == mTaECVhVHo){PuTugKTISU = true;}
      while(IeJbsZLOeL == IeJbsZLOeL){pNshmfUnSu = true;}
      while(uXPBXxbbHD == uXPBXxbbHD){qHAVEKlwJu = true;}
      if(xRHjjrdCdi == true){xRHjjrdCdi = false;}
      if(yWdHlsBRNC == true){yWdHlsBRNC = false;}
      if(lGKFKLquRP == true){lGKFKLquRP = false;}
      if(knDxfpXZrA == true){knDxfpXZrA = false;}
      if(uIkwNYsHPe == true){uIkwNYsHPe = false;}
      if(wKOFRqGCYY == true){wKOFRqGCYY = false;}
      if(BikNxJSfau == true){BikNxJSfau = false;}
      if(VbZNGcUOql == true){VbZNGcUOql = false;}
      if(RiemTaZyfo == true){RiemTaZyfo = false;}
      if(iUATyLXWyE == true){iUATyLXWyE = false;}
      if(FNgUIUkByn == true){FNgUIUkByn = false;}
      if(VrKmGRExtW == true){VrKmGRExtW = false;}
      if(iUAlLAaGOt == true){iUAlLAaGOt = false;}
      if(FyPmfECJdy == true){FyPmfECJdy = false;}
      if(oYArSqJNMf == true){oYArSqJNMf = false;}
      if(HZcbUkMtJH == true){HZcbUkMtJH = false;}
      if(temDhXcWGC == true){temDhXcWGC = false;}
      if(PuTugKTISU == true){PuTugKTISU = false;}
      if(pNshmfUnSu == true){pNshmfUnSu = false;}
      if(qHAVEKlwJu == true){qHAVEKlwJu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSWFNPRTKT
{ 
  void pWHAIDaoAO()
  { 
      bool xphIPNwgYT = false;
      bool lGVnxQnwGq = false;
      bool MLeUpHXieZ = false;
      bool WiULcXfTPb = false;
      bool iwZJegcPXh = false;
      bool UYEMgkKNSH = false;
      bool pMBzwClJLY = false;
      bool jUfeIPlVoI = false;
      bool dILwEyeHeq = false;
      bool NSAHkVtZMb = false;
      bool uSEzxAsYEQ = false;
      bool zoXJdgBFuy = false;
      bool WdeTLRTXsl = false;
      bool VLINMKEMzD = false;
      bool FFDNrYtpdD = false;
      bool UoeOEQnjmf = false;
      bool fUeRunfKxS = false;
      bool coGqrRaQbm = false;
      bool WcspRgftIu = false;
      bool WTYTWjakSD = false;
      string QDoZdbncuK;
      string aTkzioHzfP;
      string wdJDGXFals;
      string sLfCzWgVtZ;
      string ycViPYSPKg;
      string zljuWltkSF;
      string VMqBQPniAL;
      string IlEGRSIZnh;
      string FoQFsHakfM;
      string cuDnDllTRz;
      string jjOyYNgdcD;
      string dTwjAgukIJ;
      string nDCniMhQCf;
      string fnHnyVZSge;
      string ZwHbiIyTnW;
      string pAKILggaOL;
      string fQbwWoLIke;
      string GbEdiquZFZ;
      string OOcfoeczcQ;
      string nzEUzJULEs;
      if(QDoZdbncuK == jjOyYNgdcD){xphIPNwgYT = true;}
      else if(jjOyYNgdcD == QDoZdbncuK){uSEzxAsYEQ = true;}
      if(aTkzioHzfP == dTwjAgukIJ){lGVnxQnwGq = true;}
      else if(dTwjAgukIJ == aTkzioHzfP){zoXJdgBFuy = true;}
      if(wdJDGXFals == nDCniMhQCf){MLeUpHXieZ = true;}
      else if(nDCniMhQCf == wdJDGXFals){WdeTLRTXsl = true;}
      if(sLfCzWgVtZ == fnHnyVZSge){WiULcXfTPb = true;}
      else if(fnHnyVZSge == sLfCzWgVtZ){VLINMKEMzD = true;}
      if(ycViPYSPKg == ZwHbiIyTnW){iwZJegcPXh = true;}
      else if(ZwHbiIyTnW == ycViPYSPKg){FFDNrYtpdD = true;}
      if(zljuWltkSF == pAKILggaOL){UYEMgkKNSH = true;}
      else if(pAKILggaOL == zljuWltkSF){UoeOEQnjmf = true;}
      if(VMqBQPniAL == fQbwWoLIke){pMBzwClJLY = true;}
      else if(fQbwWoLIke == VMqBQPniAL){fUeRunfKxS = true;}
      if(IlEGRSIZnh == GbEdiquZFZ){jUfeIPlVoI = true;}
      if(FoQFsHakfM == OOcfoeczcQ){dILwEyeHeq = true;}
      if(cuDnDllTRz == nzEUzJULEs){NSAHkVtZMb = true;}
      while(GbEdiquZFZ == IlEGRSIZnh){coGqrRaQbm = true;}
      while(OOcfoeczcQ == OOcfoeczcQ){WcspRgftIu = true;}
      while(nzEUzJULEs == nzEUzJULEs){WTYTWjakSD = true;}
      if(xphIPNwgYT == true){xphIPNwgYT = false;}
      if(lGVnxQnwGq == true){lGVnxQnwGq = false;}
      if(MLeUpHXieZ == true){MLeUpHXieZ = false;}
      if(WiULcXfTPb == true){WiULcXfTPb = false;}
      if(iwZJegcPXh == true){iwZJegcPXh = false;}
      if(UYEMgkKNSH == true){UYEMgkKNSH = false;}
      if(pMBzwClJLY == true){pMBzwClJLY = false;}
      if(jUfeIPlVoI == true){jUfeIPlVoI = false;}
      if(dILwEyeHeq == true){dILwEyeHeq = false;}
      if(NSAHkVtZMb == true){NSAHkVtZMb = false;}
      if(uSEzxAsYEQ == true){uSEzxAsYEQ = false;}
      if(zoXJdgBFuy == true){zoXJdgBFuy = false;}
      if(WdeTLRTXsl == true){WdeTLRTXsl = false;}
      if(VLINMKEMzD == true){VLINMKEMzD = false;}
      if(FFDNrYtpdD == true){FFDNrYtpdD = false;}
      if(UoeOEQnjmf == true){UoeOEQnjmf = false;}
      if(fUeRunfKxS == true){fUeRunfKxS = false;}
      if(coGqrRaQbm == true){coGqrRaQbm = false;}
      if(WcspRgftIu == true){WcspRgftIu = false;}
      if(WTYTWjakSD == true){WTYTWjakSD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCIIKSLJOL
{ 
  void ZuBghJgsad()
  { 
      bool QwIMRqcVSk = false;
      bool twsXHuuslj = false;
      bool QJRtYLKJDU = false;
      bool hqKQHEWsxe = false;
      bool LdLUcrFCzW = false;
      bool DtscpGeOmG = false;
      bool gTRyCDlcPC = false;
      bool XBuHXlywQf = false;
      bool FIJgRmxhZA = false;
      bool ZIFqyrLNSZ = false;
      bool GclwzBzlED = false;
      bool IhxHAYJkfO = false;
      bool GECOcOuEIf = false;
      bool akdqZbVMgQ = false;
      bool nKcWrqLypY = false;
      bool hagDSBaXTk = false;
      bool GudYcWDGhY = false;
      bool DwDPZwbfVl = false;
      bool CwNjyzDaXX = false;
      bool BxswJsgEsU = false;
      string EAAohWRYqo;
      string IAPQczDkET;
      string HwYcLWRNyA;
      string psnKomaMII;
      string lzxDppioQD;
      string YKwpPHbWcK;
      string EDZpyPLEbp;
      string YqcwgHzVmU;
      string mcxtafwytg;
      string LDixEhYGEZ;
      string edMaehgAII;
      string IFjIWaGfOR;
      string SMJudVHfrz;
      string hrQMpJQVPs;
      string zwplXFTaZc;
      string bsrlHRTQwI;
      string aAIJZQnWSN;
      string KjPVSWWXXY;
      string BfFOWoAeFX;
      string ozZGRynfMG;
      if(EAAohWRYqo == edMaehgAII){QwIMRqcVSk = true;}
      else if(edMaehgAII == EAAohWRYqo){GclwzBzlED = true;}
      if(IAPQczDkET == IFjIWaGfOR){twsXHuuslj = true;}
      else if(IFjIWaGfOR == IAPQczDkET){IhxHAYJkfO = true;}
      if(HwYcLWRNyA == SMJudVHfrz){QJRtYLKJDU = true;}
      else if(SMJudVHfrz == HwYcLWRNyA){GECOcOuEIf = true;}
      if(psnKomaMII == hrQMpJQVPs){hqKQHEWsxe = true;}
      else if(hrQMpJQVPs == psnKomaMII){akdqZbVMgQ = true;}
      if(lzxDppioQD == zwplXFTaZc){LdLUcrFCzW = true;}
      else if(zwplXFTaZc == lzxDppioQD){nKcWrqLypY = true;}
      if(YKwpPHbWcK == bsrlHRTQwI){DtscpGeOmG = true;}
      else if(bsrlHRTQwI == YKwpPHbWcK){hagDSBaXTk = true;}
      if(EDZpyPLEbp == aAIJZQnWSN){gTRyCDlcPC = true;}
      else if(aAIJZQnWSN == EDZpyPLEbp){GudYcWDGhY = true;}
      if(YqcwgHzVmU == KjPVSWWXXY){XBuHXlywQf = true;}
      if(mcxtafwytg == BfFOWoAeFX){FIJgRmxhZA = true;}
      if(LDixEhYGEZ == ozZGRynfMG){ZIFqyrLNSZ = true;}
      while(KjPVSWWXXY == YqcwgHzVmU){DwDPZwbfVl = true;}
      while(BfFOWoAeFX == BfFOWoAeFX){CwNjyzDaXX = true;}
      while(ozZGRynfMG == ozZGRynfMG){BxswJsgEsU = true;}
      if(QwIMRqcVSk == true){QwIMRqcVSk = false;}
      if(twsXHuuslj == true){twsXHuuslj = false;}
      if(QJRtYLKJDU == true){QJRtYLKJDU = false;}
      if(hqKQHEWsxe == true){hqKQHEWsxe = false;}
      if(LdLUcrFCzW == true){LdLUcrFCzW = false;}
      if(DtscpGeOmG == true){DtscpGeOmG = false;}
      if(gTRyCDlcPC == true){gTRyCDlcPC = false;}
      if(XBuHXlywQf == true){XBuHXlywQf = false;}
      if(FIJgRmxhZA == true){FIJgRmxhZA = false;}
      if(ZIFqyrLNSZ == true){ZIFqyrLNSZ = false;}
      if(GclwzBzlED == true){GclwzBzlED = false;}
      if(IhxHAYJkfO == true){IhxHAYJkfO = false;}
      if(GECOcOuEIf == true){GECOcOuEIf = false;}
      if(akdqZbVMgQ == true){akdqZbVMgQ = false;}
      if(nKcWrqLypY == true){nKcWrqLypY = false;}
      if(hagDSBaXTk == true){hagDSBaXTk = false;}
      if(GudYcWDGhY == true){GudYcWDGhY = false;}
      if(DwDPZwbfVl == true){DwDPZwbfVl = false;}
      if(CwNjyzDaXX == true){CwNjyzDaXX = false;}
      if(BxswJsgEsU == true){BxswJsgEsU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSSCSSKJWC
{ 
  void ZchgZRLoHr()
  { 
      bool xYlcSuhIGE = false;
      bool tYOZORjyAG = false;
      bool tSKqEliKOO = false;
      bool ezjfgUlZDs = false;
      bool gXKlWryemL = false;
      bool DbVHIdOtYg = false;
      bool MXsrYunist = false;
      bool eJuGZVHYUL = false;
      bool mEWDKDccXC = false;
      bool FrBVgIdSMb = false;
      bool DPksfsgPhl = false;
      bool WoZMtHBphV = false;
      bool RLLqnlIYZQ = false;
      bool qoLrIXSdWQ = false;
      bool VNtkeQSnbY = false;
      bool HnkqJqDtEs = false;
      bool kIpQuhdgEW = false;
      bool nWTQzDRaMX = false;
      bool TTwAJDDTiQ = false;
      bool TYYceNXcpw = false;
      string lYEIbtOViR;
      string wBgZYqUiXJ;
      string BnymjPSrMu;
      string UlubfTtMWF;
      string CZxjXEOAUZ;
      string SCdUIxZRXM;
      string bVJmwKGEsE;
      string xIMSGapOOf;
      string ARXmcRHZSi;
      string scnKcgQKmN;
      string xKHPcKpLOg;
      string GLCrLKxVKd;
      string CgkKLTTCoY;
      string KfaBhpKIKS;
      string bwLlbhZuyS;
      string jtzJKQYxDI;
      string pnVoWZjBJV;
      string znLqCGVzhd;
      string sXDWoPfRpR;
      string RNEBcnaVOC;
      if(lYEIbtOViR == xKHPcKpLOg){xYlcSuhIGE = true;}
      else if(xKHPcKpLOg == lYEIbtOViR){DPksfsgPhl = true;}
      if(wBgZYqUiXJ == GLCrLKxVKd){tYOZORjyAG = true;}
      else if(GLCrLKxVKd == wBgZYqUiXJ){WoZMtHBphV = true;}
      if(BnymjPSrMu == CgkKLTTCoY){tSKqEliKOO = true;}
      else if(CgkKLTTCoY == BnymjPSrMu){RLLqnlIYZQ = true;}
      if(UlubfTtMWF == KfaBhpKIKS){ezjfgUlZDs = true;}
      else if(KfaBhpKIKS == UlubfTtMWF){qoLrIXSdWQ = true;}
      if(CZxjXEOAUZ == bwLlbhZuyS){gXKlWryemL = true;}
      else if(bwLlbhZuyS == CZxjXEOAUZ){VNtkeQSnbY = true;}
      if(SCdUIxZRXM == jtzJKQYxDI){DbVHIdOtYg = true;}
      else if(jtzJKQYxDI == SCdUIxZRXM){HnkqJqDtEs = true;}
      if(bVJmwKGEsE == pnVoWZjBJV){MXsrYunist = true;}
      else if(pnVoWZjBJV == bVJmwKGEsE){kIpQuhdgEW = true;}
      if(xIMSGapOOf == znLqCGVzhd){eJuGZVHYUL = true;}
      if(ARXmcRHZSi == sXDWoPfRpR){mEWDKDccXC = true;}
      if(scnKcgQKmN == RNEBcnaVOC){FrBVgIdSMb = true;}
      while(znLqCGVzhd == xIMSGapOOf){nWTQzDRaMX = true;}
      while(sXDWoPfRpR == sXDWoPfRpR){TTwAJDDTiQ = true;}
      while(RNEBcnaVOC == RNEBcnaVOC){TYYceNXcpw = true;}
      if(xYlcSuhIGE == true){xYlcSuhIGE = false;}
      if(tYOZORjyAG == true){tYOZORjyAG = false;}
      if(tSKqEliKOO == true){tSKqEliKOO = false;}
      if(ezjfgUlZDs == true){ezjfgUlZDs = false;}
      if(gXKlWryemL == true){gXKlWryemL = false;}
      if(DbVHIdOtYg == true){DbVHIdOtYg = false;}
      if(MXsrYunist == true){MXsrYunist = false;}
      if(eJuGZVHYUL == true){eJuGZVHYUL = false;}
      if(mEWDKDccXC == true){mEWDKDccXC = false;}
      if(FrBVgIdSMb == true){FrBVgIdSMb = false;}
      if(DPksfsgPhl == true){DPksfsgPhl = false;}
      if(WoZMtHBphV == true){WoZMtHBphV = false;}
      if(RLLqnlIYZQ == true){RLLqnlIYZQ = false;}
      if(qoLrIXSdWQ == true){qoLrIXSdWQ = false;}
      if(VNtkeQSnbY == true){VNtkeQSnbY = false;}
      if(HnkqJqDtEs == true){HnkqJqDtEs = false;}
      if(kIpQuhdgEW == true){kIpQuhdgEW = false;}
      if(nWTQzDRaMX == true){nWTQzDRaMX = false;}
      if(TTwAJDDTiQ == true){TTwAJDDTiQ = false;}
      if(TYYceNXcpw == true){TYYceNXcpw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPGPEIDWTN
{ 
  void NbQtDWkmha()
  { 
      bool CiUIVqkawf = false;
      bool xLVOkogLal = false;
      bool oTHcqzeWOB = false;
      bool hsFwuwfECW = false;
      bool ASoloTgjMU = false;
      bool jcjjkhbrQW = false;
      bool LOLuyDGYSo = false;
      bool JcJEkVeUmX = false;
      bool RuKtQFJULN = false;
      bool UnmeKlGsnl = false;
      bool NHQWLHTfyO = false;
      bool DGFrEPERes = false;
      bool tkNFUUodsz = false;
      bool OkgAKKdmiJ = false;
      bool ldWwJNhuZt = false;
      bool hoOuqbsLBp = false;
      bool RolzARZEht = false;
      bool kQiUHQNRuH = false;
      bool ltDzQZVlJh = false;
      bool QSkrqwqXuq = false;
      string CdTMeRsYnb;
      string rMhExKFAsW;
      string YDXHTNFYUh;
      string ywmDlXQgle;
      string dsgZqcmosz;
      string CztQtzGLsQ;
      string LTEGdwYdRY;
      string sYNOsfVyQp;
      string aQeUeyCWIm;
      string REmVSJoauu;
      string DIWUFcleXO;
      string dIuCpuniae;
      string sCUeHolrui;
      string qtCUmSsKOB;
      string LXztJIJjfX;
      string UFAPCAmqMQ;
      string qtinXiGZPW;
      string BdUYTVDaVy;
      string eBMXNktlSl;
      string fCyyKRnKVZ;
      if(CdTMeRsYnb == DIWUFcleXO){CiUIVqkawf = true;}
      else if(DIWUFcleXO == CdTMeRsYnb){NHQWLHTfyO = true;}
      if(rMhExKFAsW == dIuCpuniae){xLVOkogLal = true;}
      else if(dIuCpuniae == rMhExKFAsW){DGFrEPERes = true;}
      if(YDXHTNFYUh == sCUeHolrui){oTHcqzeWOB = true;}
      else if(sCUeHolrui == YDXHTNFYUh){tkNFUUodsz = true;}
      if(ywmDlXQgle == qtCUmSsKOB){hsFwuwfECW = true;}
      else if(qtCUmSsKOB == ywmDlXQgle){OkgAKKdmiJ = true;}
      if(dsgZqcmosz == LXztJIJjfX){ASoloTgjMU = true;}
      else if(LXztJIJjfX == dsgZqcmosz){ldWwJNhuZt = true;}
      if(CztQtzGLsQ == UFAPCAmqMQ){jcjjkhbrQW = true;}
      else if(UFAPCAmqMQ == CztQtzGLsQ){hoOuqbsLBp = true;}
      if(LTEGdwYdRY == qtinXiGZPW){LOLuyDGYSo = true;}
      else if(qtinXiGZPW == LTEGdwYdRY){RolzARZEht = true;}
      if(sYNOsfVyQp == BdUYTVDaVy){JcJEkVeUmX = true;}
      if(aQeUeyCWIm == eBMXNktlSl){RuKtQFJULN = true;}
      if(REmVSJoauu == fCyyKRnKVZ){UnmeKlGsnl = true;}
      while(BdUYTVDaVy == sYNOsfVyQp){kQiUHQNRuH = true;}
      while(eBMXNktlSl == eBMXNktlSl){ltDzQZVlJh = true;}
      while(fCyyKRnKVZ == fCyyKRnKVZ){QSkrqwqXuq = true;}
      if(CiUIVqkawf == true){CiUIVqkawf = false;}
      if(xLVOkogLal == true){xLVOkogLal = false;}
      if(oTHcqzeWOB == true){oTHcqzeWOB = false;}
      if(hsFwuwfECW == true){hsFwuwfECW = false;}
      if(ASoloTgjMU == true){ASoloTgjMU = false;}
      if(jcjjkhbrQW == true){jcjjkhbrQW = false;}
      if(LOLuyDGYSo == true){LOLuyDGYSo = false;}
      if(JcJEkVeUmX == true){JcJEkVeUmX = false;}
      if(RuKtQFJULN == true){RuKtQFJULN = false;}
      if(UnmeKlGsnl == true){UnmeKlGsnl = false;}
      if(NHQWLHTfyO == true){NHQWLHTfyO = false;}
      if(DGFrEPERes == true){DGFrEPERes = false;}
      if(tkNFUUodsz == true){tkNFUUodsz = false;}
      if(OkgAKKdmiJ == true){OkgAKKdmiJ = false;}
      if(ldWwJNhuZt == true){ldWwJNhuZt = false;}
      if(hoOuqbsLBp == true){hoOuqbsLBp = false;}
      if(RolzARZEht == true){RolzARZEht = false;}
      if(kQiUHQNRuH == true){kQiUHQNRuH = false;}
      if(ltDzQZVlJh == true){ltDzQZVlJh = false;}
      if(QSkrqwqXuq == true){QSkrqwqXuq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AWICOGXSEB
{ 
  void hoQufTEsWq()
  { 
      bool QDGVIplmRl = false;
      bool tyqUwXCpEX = false;
      bool lOMOoeuemo = false;
      bool ZabwhcqhXy = false;
      bool xIDAhcFbSp = false;
      bool sZaVzBpqgc = false;
      bool tHzcMTWtmS = false;
      bool gTSFZcKLfM = false;
      bool ZSLxwAzFwf = false;
      bool mzAtDpJanO = false;
      bool GKozIZHVwV = false;
      bool pdLUCbuBfL = false;
      bool UQxGfhSXBj = false;
      bool TiWQFPcMoW = false;
      bool scJZoInfra = false;
      bool tHtctoMhSZ = false;
      bool GjTLCHGtOm = false;
      bool yhMJSqHWRX = false;
      bool smfaoLntVQ = false;
      bool CusOPIJxXh = false;
      string AYfhaRKROc;
      string cmaHAOInhE;
      string uWwpFaTPYc;
      string oUUeQnKuyg;
      string nLLfQxnTeR;
      string cnpfGdbpcz;
      string yusknISwpL;
      string EMpAQiKQYH;
      string mzkGzAdnYm;
      string MTSyisSZqI;
      string eqcSNPyoPW;
      string SKQULyKmkm;
      string edWDzjtqRW;
      string PjZQcuWRrj;
      string CnXBUBDxmk;
      string ifnDcATZTc;
      string VGXrHhkAqQ;
      string bstBkpGViy;
      string gxEgnjuVmc;
      string awxOOuQftl;
      if(AYfhaRKROc == eqcSNPyoPW){QDGVIplmRl = true;}
      else if(eqcSNPyoPW == AYfhaRKROc){GKozIZHVwV = true;}
      if(cmaHAOInhE == SKQULyKmkm){tyqUwXCpEX = true;}
      else if(SKQULyKmkm == cmaHAOInhE){pdLUCbuBfL = true;}
      if(uWwpFaTPYc == edWDzjtqRW){lOMOoeuemo = true;}
      else if(edWDzjtqRW == uWwpFaTPYc){UQxGfhSXBj = true;}
      if(oUUeQnKuyg == PjZQcuWRrj){ZabwhcqhXy = true;}
      else if(PjZQcuWRrj == oUUeQnKuyg){TiWQFPcMoW = true;}
      if(nLLfQxnTeR == CnXBUBDxmk){xIDAhcFbSp = true;}
      else if(CnXBUBDxmk == nLLfQxnTeR){scJZoInfra = true;}
      if(cnpfGdbpcz == ifnDcATZTc){sZaVzBpqgc = true;}
      else if(ifnDcATZTc == cnpfGdbpcz){tHtctoMhSZ = true;}
      if(yusknISwpL == VGXrHhkAqQ){tHzcMTWtmS = true;}
      else if(VGXrHhkAqQ == yusknISwpL){GjTLCHGtOm = true;}
      if(EMpAQiKQYH == bstBkpGViy){gTSFZcKLfM = true;}
      if(mzkGzAdnYm == gxEgnjuVmc){ZSLxwAzFwf = true;}
      if(MTSyisSZqI == awxOOuQftl){mzAtDpJanO = true;}
      while(bstBkpGViy == EMpAQiKQYH){yhMJSqHWRX = true;}
      while(gxEgnjuVmc == gxEgnjuVmc){smfaoLntVQ = true;}
      while(awxOOuQftl == awxOOuQftl){CusOPIJxXh = true;}
      if(QDGVIplmRl == true){QDGVIplmRl = false;}
      if(tyqUwXCpEX == true){tyqUwXCpEX = false;}
      if(lOMOoeuemo == true){lOMOoeuemo = false;}
      if(ZabwhcqhXy == true){ZabwhcqhXy = false;}
      if(xIDAhcFbSp == true){xIDAhcFbSp = false;}
      if(sZaVzBpqgc == true){sZaVzBpqgc = false;}
      if(tHzcMTWtmS == true){tHzcMTWtmS = false;}
      if(gTSFZcKLfM == true){gTSFZcKLfM = false;}
      if(ZSLxwAzFwf == true){ZSLxwAzFwf = false;}
      if(mzAtDpJanO == true){mzAtDpJanO = false;}
      if(GKozIZHVwV == true){GKozIZHVwV = false;}
      if(pdLUCbuBfL == true){pdLUCbuBfL = false;}
      if(UQxGfhSXBj == true){UQxGfhSXBj = false;}
      if(TiWQFPcMoW == true){TiWQFPcMoW = false;}
      if(scJZoInfra == true){scJZoInfra = false;}
      if(tHtctoMhSZ == true){tHtctoMhSZ = false;}
      if(GjTLCHGtOm == true){GjTLCHGtOm = false;}
      if(yhMJSqHWRX == true){yhMJSqHWRX = false;}
      if(smfaoLntVQ == true){smfaoLntVQ = false;}
      if(CusOPIJxXh == true){CusOPIJxXh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIPCAEEGIL
{ 
  void sHtcNMuCbP()
  { 
      bool QqmTNFqqDU = false;
      bool qTqyCcVJPy = false;
      bool iKoCLgKlTa = false;
      bool RyQSGdqpXD = false;
      bool gkPiesLkKM = false;
      bool tmiajGBkIf = false;
      bool tEXbCsDXrX = false;
      bool kekMRxuGWR = false;
      bool VZaGgePoiz = false;
      bool bGhqIbNmgl = false;
      bool omrlbOBVIl = false;
      bool LuNpKUdQuW = false;
      bool dNnsudxsDo = false;
      bool iHYkchhndR = false;
      bool dsgxngsrgn = false;
      bool ywqJHazzqy = false;
      bool RHRTCDVbMb = false;
      bool lomdsjgqEO = false;
      bool jEMPqmQPcC = false;
      bool ihxfAVaNtj = false;
      string QxyGxqeClb;
      string VZUaisotyE;
      string ErGpCgClIj;
      string GuzCqdXADB;
      string tRIGOiNcrx;
      string mZZsWXqHDP;
      string ostCVaZRjE;
      string VnqwKlizaT;
      string SYsLwfUGfS;
      string mQxnMAXGkn;
      string Iwsnbzidij;
      string orfjwPAhGo;
      string FTlQREqCiJ;
      string NcOmKWfFjx;
      string xqXwdtjMrx;
      string AoAuinJcVW;
      string HfuYWLcsYY;
      string jtyIrOwolW;
      string UeKkJXcSDW;
      string NCiMoQwyYS;
      if(QxyGxqeClb == Iwsnbzidij){QqmTNFqqDU = true;}
      else if(Iwsnbzidij == QxyGxqeClb){omrlbOBVIl = true;}
      if(VZUaisotyE == orfjwPAhGo){qTqyCcVJPy = true;}
      else if(orfjwPAhGo == VZUaisotyE){LuNpKUdQuW = true;}
      if(ErGpCgClIj == FTlQREqCiJ){iKoCLgKlTa = true;}
      else if(FTlQREqCiJ == ErGpCgClIj){dNnsudxsDo = true;}
      if(GuzCqdXADB == NcOmKWfFjx){RyQSGdqpXD = true;}
      else if(NcOmKWfFjx == GuzCqdXADB){iHYkchhndR = true;}
      if(tRIGOiNcrx == xqXwdtjMrx){gkPiesLkKM = true;}
      else if(xqXwdtjMrx == tRIGOiNcrx){dsgxngsrgn = true;}
      if(mZZsWXqHDP == AoAuinJcVW){tmiajGBkIf = true;}
      else if(AoAuinJcVW == mZZsWXqHDP){ywqJHazzqy = true;}
      if(ostCVaZRjE == HfuYWLcsYY){tEXbCsDXrX = true;}
      else if(HfuYWLcsYY == ostCVaZRjE){RHRTCDVbMb = true;}
      if(VnqwKlizaT == jtyIrOwolW){kekMRxuGWR = true;}
      if(SYsLwfUGfS == UeKkJXcSDW){VZaGgePoiz = true;}
      if(mQxnMAXGkn == NCiMoQwyYS){bGhqIbNmgl = true;}
      while(jtyIrOwolW == VnqwKlizaT){lomdsjgqEO = true;}
      while(UeKkJXcSDW == UeKkJXcSDW){jEMPqmQPcC = true;}
      while(NCiMoQwyYS == NCiMoQwyYS){ihxfAVaNtj = true;}
      if(QqmTNFqqDU == true){QqmTNFqqDU = false;}
      if(qTqyCcVJPy == true){qTqyCcVJPy = false;}
      if(iKoCLgKlTa == true){iKoCLgKlTa = false;}
      if(RyQSGdqpXD == true){RyQSGdqpXD = false;}
      if(gkPiesLkKM == true){gkPiesLkKM = false;}
      if(tmiajGBkIf == true){tmiajGBkIf = false;}
      if(tEXbCsDXrX == true){tEXbCsDXrX = false;}
      if(kekMRxuGWR == true){kekMRxuGWR = false;}
      if(VZaGgePoiz == true){VZaGgePoiz = false;}
      if(bGhqIbNmgl == true){bGhqIbNmgl = false;}
      if(omrlbOBVIl == true){omrlbOBVIl = false;}
      if(LuNpKUdQuW == true){LuNpKUdQuW = false;}
      if(dNnsudxsDo == true){dNnsudxsDo = false;}
      if(iHYkchhndR == true){iHYkchhndR = false;}
      if(dsgxngsrgn == true){dsgxngsrgn = false;}
      if(ywqJHazzqy == true){ywqJHazzqy = false;}
      if(RHRTCDVbMb == true){RHRTCDVbMb = false;}
      if(lomdsjgqEO == true){lomdsjgqEO = false;}
      if(jEMPqmQPcC == true){jEMPqmQPcC = false;}
      if(ihxfAVaNtj == true){ihxfAVaNtj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANFZZWHJSS
{ 
  void FlPIcClZRG()
  { 
      bool zacldhhJNZ = false;
      bool dTRcDgSJId = false;
      bool QgaaNSyMYO = false;
      bool TVObYDXBQw = false;
      bool WouJTpgkam = false;
      bool WbwRVRzCYK = false;
      bool iVkzGHFoEz = false;
      bool IRsMGalQHW = false;
      bool kMllqrZwGH = false;
      bool EVbFMBEwDL = false;
      bool krgbdFhjLt = false;
      bool ehtBZWizHN = false;
      bool hIiwtmonzF = false;
      bool WoNulsfKHl = false;
      bool JpkLbVaaep = false;
      bool RFnodcJkgp = false;
      bool QtjFXpUzOg = false;
      bool pYqVEqWXUX = false;
      bool MNIJmRAXRJ = false;
      bool iucRVPGeml = false;
      string xgPloxaGqh;
      string qsxbwOWVGe;
      string xfRwdQTSqJ;
      string eMRNmYhmyW;
      string fqfVEAFnmf;
      string VccLUROSHY;
      string dHOhCdajnX;
      string fjXiyGzuqd;
      string KfeLmBiGsV;
      string JOfYsXbxTa;
      string ZVzPzlFtNN;
      string RTbcNxcCtA;
      string tTpSNRDypZ;
      string dCbQDofPLB;
      string woreDplCKu;
      string uYCSfFegBh;
      string hGDmiPqLYX;
      string RMqsEFaKPX;
      string eBnteFzJjy;
      string KzOdTpkFwm;
      if(xgPloxaGqh == ZVzPzlFtNN){zacldhhJNZ = true;}
      else if(ZVzPzlFtNN == xgPloxaGqh){krgbdFhjLt = true;}
      if(qsxbwOWVGe == RTbcNxcCtA){dTRcDgSJId = true;}
      else if(RTbcNxcCtA == qsxbwOWVGe){ehtBZWizHN = true;}
      if(xfRwdQTSqJ == tTpSNRDypZ){QgaaNSyMYO = true;}
      else if(tTpSNRDypZ == xfRwdQTSqJ){hIiwtmonzF = true;}
      if(eMRNmYhmyW == dCbQDofPLB){TVObYDXBQw = true;}
      else if(dCbQDofPLB == eMRNmYhmyW){WoNulsfKHl = true;}
      if(fqfVEAFnmf == woreDplCKu){WouJTpgkam = true;}
      else if(woreDplCKu == fqfVEAFnmf){JpkLbVaaep = true;}
      if(VccLUROSHY == uYCSfFegBh){WbwRVRzCYK = true;}
      else if(uYCSfFegBh == VccLUROSHY){RFnodcJkgp = true;}
      if(dHOhCdajnX == hGDmiPqLYX){iVkzGHFoEz = true;}
      else if(hGDmiPqLYX == dHOhCdajnX){QtjFXpUzOg = true;}
      if(fjXiyGzuqd == RMqsEFaKPX){IRsMGalQHW = true;}
      if(KfeLmBiGsV == eBnteFzJjy){kMllqrZwGH = true;}
      if(JOfYsXbxTa == KzOdTpkFwm){EVbFMBEwDL = true;}
      while(RMqsEFaKPX == fjXiyGzuqd){pYqVEqWXUX = true;}
      while(eBnteFzJjy == eBnteFzJjy){MNIJmRAXRJ = true;}
      while(KzOdTpkFwm == KzOdTpkFwm){iucRVPGeml = true;}
      if(zacldhhJNZ == true){zacldhhJNZ = false;}
      if(dTRcDgSJId == true){dTRcDgSJId = false;}
      if(QgaaNSyMYO == true){QgaaNSyMYO = false;}
      if(TVObYDXBQw == true){TVObYDXBQw = false;}
      if(WouJTpgkam == true){WouJTpgkam = false;}
      if(WbwRVRzCYK == true){WbwRVRzCYK = false;}
      if(iVkzGHFoEz == true){iVkzGHFoEz = false;}
      if(IRsMGalQHW == true){IRsMGalQHW = false;}
      if(kMllqrZwGH == true){kMllqrZwGH = false;}
      if(EVbFMBEwDL == true){EVbFMBEwDL = false;}
      if(krgbdFhjLt == true){krgbdFhjLt = false;}
      if(ehtBZWizHN == true){ehtBZWizHN = false;}
      if(hIiwtmonzF == true){hIiwtmonzF = false;}
      if(WoNulsfKHl == true){WoNulsfKHl = false;}
      if(JpkLbVaaep == true){JpkLbVaaep = false;}
      if(RFnodcJkgp == true){RFnodcJkgp = false;}
      if(QtjFXpUzOg == true){QtjFXpUzOg = false;}
      if(pYqVEqWXUX == true){pYqVEqWXUX = false;}
      if(MNIJmRAXRJ == true){MNIJmRAXRJ = false;}
      if(iucRVPGeml == true){iucRVPGeml = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXTTCZUHYD
{ 
  void XRGkLlNftw()
  { 
      bool JjyOpHQlmP = false;
      bool TTbUsRpcHk = false;
      bool pVlrlrKReq = false;
      bool eGsNeqpoRl = false;
      bool dOtNDafPiE = false;
      bool RcZqkmxGcy = false;
      bool xzHwkMZNpB = false;
      bool aALUHabYnK = false;
      bool LthZZCgCcq = false;
      bool sjMSoeHybp = false;
      bool BSYgdQQEjJ = false;
      bool LYSRlCQgVh = false;
      bool fXjzIqmrfb = false;
      bool TdwxJsVBwI = false;
      bool kbSTfUQugl = false;
      bool OZbtKdhZYl = false;
      bool dYYHohbVHs = false;
      bool gOkNxEFQTm = false;
      bool aqLsNsBClf = false;
      bool LwbJeLCKdx = false;
      string rYpHcSzziG;
      string ldQGHPfCNZ;
      string uArpzEpFNN;
      string IgWotStRmu;
      string knpkhmxmAS;
      string XKDnsrfAIY;
      string ctlVyFGbLo;
      string VNPRnHKHHM;
      string GCFtoxciuB;
      string lsJNRqBUmc;
      string fVbLxKukzl;
      string hYsuRanqfA;
      string bXfJCbDBzx;
      string FoUdfkZsxd;
      string BqiJTNAOwq;
      string CKnlAIpRJU;
      string HtkCgrEPPg;
      string AttByknWpn;
      string boEItuBhcX;
      string tIjbWHFgcb;
      if(rYpHcSzziG == fVbLxKukzl){JjyOpHQlmP = true;}
      else if(fVbLxKukzl == rYpHcSzziG){BSYgdQQEjJ = true;}
      if(ldQGHPfCNZ == hYsuRanqfA){TTbUsRpcHk = true;}
      else if(hYsuRanqfA == ldQGHPfCNZ){LYSRlCQgVh = true;}
      if(uArpzEpFNN == bXfJCbDBzx){pVlrlrKReq = true;}
      else if(bXfJCbDBzx == uArpzEpFNN){fXjzIqmrfb = true;}
      if(IgWotStRmu == FoUdfkZsxd){eGsNeqpoRl = true;}
      else if(FoUdfkZsxd == IgWotStRmu){TdwxJsVBwI = true;}
      if(knpkhmxmAS == BqiJTNAOwq){dOtNDafPiE = true;}
      else if(BqiJTNAOwq == knpkhmxmAS){kbSTfUQugl = true;}
      if(XKDnsrfAIY == CKnlAIpRJU){RcZqkmxGcy = true;}
      else if(CKnlAIpRJU == XKDnsrfAIY){OZbtKdhZYl = true;}
      if(ctlVyFGbLo == HtkCgrEPPg){xzHwkMZNpB = true;}
      else if(HtkCgrEPPg == ctlVyFGbLo){dYYHohbVHs = true;}
      if(VNPRnHKHHM == AttByknWpn){aALUHabYnK = true;}
      if(GCFtoxciuB == boEItuBhcX){LthZZCgCcq = true;}
      if(lsJNRqBUmc == tIjbWHFgcb){sjMSoeHybp = true;}
      while(AttByknWpn == VNPRnHKHHM){gOkNxEFQTm = true;}
      while(boEItuBhcX == boEItuBhcX){aqLsNsBClf = true;}
      while(tIjbWHFgcb == tIjbWHFgcb){LwbJeLCKdx = true;}
      if(JjyOpHQlmP == true){JjyOpHQlmP = false;}
      if(TTbUsRpcHk == true){TTbUsRpcHk = false;}
      if(pVlrlrKReq == true){pVlrlrKReq = false;}
      if(eGsNeqpoRl == true){eGsNeqpoRl = false;}
      if(dOtNDafPiE == true){dOtNDafPiE = false;}
      if(RcZqkmxGcy == true){RcZqkmxGcy = false;}
      if(xzHwkMZNpB == true){xzHwkMZNpB = false;}
      if(aALUHabYnK == true){aALUHabYnK = false;}
      if(LthZZCgCcq == true){LthZZCgCcq = false;}
      if(sjMSoeHybp == true){sjMSoeHybp = false;}
      if(BSYgdQQEjJ == true){BSYgdQQEjJ = false;}
      if(LYSRlCQgVh == true){LYSRlCQgVh = false;}
      if(fXjzIqmrfb == true){fXjzIqmrfb = false;}
      if(TdwxJsVBwI == true){TdwxJsVBwI = false;}
      if(kbSTfUQugl == true){kbSTfUQugl = false;}
      if(OZbtKdhZYl == true){OZbtKdhZYl = false;}
      if(dYYHohbVHs == true){dYYHohbVHs = false;}
      if(gOkNxEFQTm == true){gOkNxEFQTm = false;}
      if(aqLsNsBClf == true){aqLsNsBClf = false;}
      if(LwbJeLCKdx == true){LwbJeLCKdx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HGQHUJZAKE
{ 
  void SObKGsgXzh()
  { 
      bool fMxMWKpPLl = false;
      bool zFJLCyEuzo = false;
      bool qGRDhBgUGy = false;
      bool ucUABCQezl = false;
      bool WrWLmyVQaS = false;
      bool NYCauZuteV = false;
      bool dVINqWjIJz = false;
      bool hZuNSyiFPj = false;
      bool ePtnkVZtFb = false;
      bool HWAdHBjJUQ = false;
      bool NMGakmdoIw = false;
      bool podtpNaTcV = false;
      bool wpDhqLZRFR = false;
      bool OZkzVSJSDx = false;
      bool rkkIkSrFmt = false;
      bool ZPgyUXJYiY = false;
      bool NLiqgPDeXX = false;
      bool EHQedKEuwY = false;
      bool STdLqzsldy = false;
      bool IjidjfBtbU = false;
      string KjLNhieFMC;
      string sWdWREpeJE;
      string NbNpaJakFO;
      string RMiFPrQmFU;
      string qfoskxTcUz;
      string TNgYjhVVmX;
      string HtzyjgnYGY;
      string nCYnMhmUEc;
      string pyQGuDeJUg;
      string VtzgNxgqIE;
      string JuVuLQnrLC;
      string uBQKhJdrCf;
      string BdDYCsDqaP;
      string AwLASubUud;
      string OlyRlUcozE;
      string TnncCfqwrR;
      string MwRuBzoQql;
      string gIxXQPfkmg;
      string POrWwMHiym;
      string DebcQRUCPl;
      if(KjLNhieFMC == JuVuLQnrLC){fMxMWKpPLl = true;}
      else if(JuVuLQnrLC == KjLNhieFMC){NMGakmdoIw = true;}
      if(sWdWREpeJE == uBQKhJdrCf){zFJLCyEuzo = true;}
      else if(uBQKhJdrCf == sWdWREpeJE){podtpNaTcV = true;}
      if(NbNpaJakFO == BdDYCsDqaP){qGRDhBgUGy = true;}
      else if(BdDYCsDqaP == NbNpaJakFO){wpDhqLZRFR = true;}
      if(RMiFPrQmFU == AwLASubUud){ucUABCQezl = true;}
      else if(AwLASubUud == RMiFPrQmFU){OZkzVSJSDx = true;}
      if(qfoskxTcUz == OlyRlUcozE){WrWLmyVQaS = true;}
      else if(OlyRlUcozE == qfoskxTcUz){rkkIkSrFmt = true;}
      if(TNgYjhVVmX == TnncCfqwrR){NYCauZuteV = true;}
      else if(TnncCfqwrR == TNgYjhVVmX){ZPgyUXJYiY = true;}
      if(HtzyjgnYGY == MwRuBzoQql){dVINqWjIJz = true;}
      else if(MwRuBzoQql == HtzyjgnYGY){NLiqgPDeXX = true;}
      if(nCYnMhmUEc == gIxXQPfkmg){hZuNSyiFPj = true;}
      if(pyQGuDeJUg == POrWwMHiym){ePtnkVZtFb = true;}
      if(VtzgNxgqIE == DebcQRUCPl){HWAdHBjJUQ = true;}
      while(gIxXQPfkmg == nCYnMhmUEc){EHQedKEuwY = true;}
      while(POrWwMHiym == POrWwMHiym){STdLqzsldy = true;}
      while(DebcQRUCPl == DebcQRUCPl){IjidjfBtbU = true;}
      if(fMxMWKpPLl == true){fMxMWKpPLl = false;}
      if(zFJLCyEuzo == true){zFJLCyEuzo = false;}
      if(qGRDhBgUGy == true){qGRDhBgUGy = false;}
      if(ucUABCQezl == true){ucUABCQezl = false;}
      if(WrWLmyVQaS == true){WrWLmyVQaS = false;}
      if(NYCauZuteV == true){NYCauZuteV = false;}
      if(dVINqWjIJz == true){dVINqWjIJz = false;}
      if(hZuNSyiFPj == true){hZuNSyiFPj = false;}
      if(ePtnkVZtFb == true){ePtnkVZtFb = false;}
      if(HWAdHBjJUQ == true){HWAdHBjJUQ = false;}
      if(NMGakmdoIw == true){NMGakmdoIw = false;}
      if(podtpNaTcV == true){podtpNaTcV = false;}
      if(wpDhqLZRFR == true){wpDhqLZRFR = false;}
      if(OZkzVSJSDx == true){OZkzVSJSDx = false;}
      if(rkkIkSrFmt == true){rkkIkSrFmt = false;}
      if(ZPgyUXJYiY == true){ZPgyUXJYiY = false;}
      if(NLiqgPDeXX == true){NLiqgPDeXX = false;}
      if(EHQedKEuwY == true){EHQedKEuwY = false;}
      if(STdLqzsldy == true){STdLqzsldy = false;}
      if(IjidjfBtbU == true){IjidjfBtbU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VOCMZTONYG
{ 
  void WeoCFbRFXF()
  { 
      bool hOWGiTXhts = false;
      bool XyiwgutBTB = false;
      bool GuzSpxKsEG = false;
      bool HbfrUDseUb = false;
      bool WOnaaqrCOD = false;
      bool tsYkCmOEQk = false;
      bool IddnlwRpbd = false;
      bool BOgqerGYqy = false;
      bool EHdALOCuoh = false;
      bool noOiTrkAne = false;
      bool ZCakBeLhFK = false;
      bool fpMRfBzccX = false;
      bool sVAspMAyXm = false;
      bool GFjMYCgsyf = false;
      bool CUpeBxbxCS = false;
      bool rHXQkDBgto = false;
      bool eNKREZFArc = false;
      bool UGdwUYfVrr = false;
      bool jDuFtyhSaV = false;
      bool BzzJAoJXaa = false;
      string JNrkyfUswe;
      string RXkqYpetHQ;
      string kifoLieBNB;
      string kuxxawWYqy;
      string FewAXwHQpS;
      string XIbAKZhDZP;
      string BTftsWZnPc;
      string TFCJLGleRO;
      string aNLtdcSxlA;
      string NTzbwkzCGA;
      string VSANzRGSoD;
      string mCkKnmHkPQ;
      string DcBOOAFZMZ;
      string HjYQrHNyuL;
      string VAIiMLhomJ;
      string dNlowsRkyy;
      string MgFPwDdTRg;
      string ZJpEuCUSBC;
      string RQlDwtxiUz;
      string pbzwzourlJ;
      if(JNrkyfUswe == VSANzRGSoD){hOWGiTXhts = true;}
      else if(VSANzRGSoD == JNrkyfUswe){ZCakBeLhFK = true;}
      if(RXkqYpetHQ == mCkKnmHkPQ){XyiwgutBTB = true;}
      else if(mCkKnmHkPQ == RXkqYpetHQ){fpMRfBzccX = true;}
      if(kifoLieBNB == DcBOOAFZMZ){GuzSpxKsEG = true;}
      else if(DcBOOAFZMZ == kifoLieBNB){sVAspMAyXm = true;}
      if(kuxxawWYqy == HjYQrHNyuL){HbfrUDseUb = true;}
      else if(HjYQrHNyuL == kuxxawWYqy){GFjMYCgsyf = true;}
      if(FewAXwHQpS == VAIiMLhomJ){WOnaaqrCOD = true;}
      else if(VAIiMLhomJ == FewAXwHQpS){CUpeBxbxCS = true;}
      if(XIbAKZhDZP == dNlowsRkyy){tsYkCmOEQk = true;}
      else if(dNlowsRkyy == XIbAKZhDZP){rHXQkDBgto = true;}
      if(BTftsWZnPc == MgFPwDdTRg){IddnlwRpbd = true;}
      else if(MgFPwDdTRg == BTftsWZnPc){eNKREZFArc = true;}
      if(TFCJLGleRO == ZJpEuCUSBC){BOgqerGYqy = true;}
      if(aNLtdcSxlA == RQlDwtxiUz){EHdALOCuoh = true;}
      if(NTzbwkzCGA == pbzwzourlJ){noOiTrkAne = true;}
      while(ZJpEuCUSBC == TFCJLGleRO){UGdwUYfVrr = true;}
      while(RQlDwtxiUz == RQlDwtxiUz){jDuFtyhSaV = true;}
      while(pbzwzourlJ == pbzwzourlJ){BzzJAoJXaa = true;}
      if(hOWGiTXhts == true){hOWGiTXhts = false;}
      if(XyiwgutBTB == true){XyiwgutBTB = false;}
      if(GuzSpxKsEG == true){GuzSpxKsEG = false;}
      if(HbfrUDseUb == true){HbfrUDseUb = false;}
      if(WOnaaqrCOD == true){WOnaaqrCOD = false;}
      if(tsYkCmOEQk == true){tsYkCmOEQk = false;}
      if(IddnlwRpbd == true){IddnlwRpbd = false;}
      if(BOgqerGYqy == true){BOgqerGYqy = false;}
      if(EHdALOCuoh == true){EHdALOCuoh = false;}
      if(noOiTrkAne == true){noOiTrkAne = false;}
      if(ZCakBeLhFK == true){ZCakBeLhFK = false;}
      if(fpMRfBzccX == true){fpMRfBzccX = false;}
      if(sVAspMAyXm == true){sVAspMAyXm = false;}
      if(GFjMYCgsyf == true){GFjMYCgsyf = false;}
      if(CUpeBxbxCS == true){CUpeBxbxCS = false;}
      if(rHXQkDBgto == true){rHXQkDBgto = false;}
      if(eNKREZFArc == true){eNKREZFArc = false;}
      if(UGdwUYfVrr == true){UGdwUYfVrr = false;}
      if(jDuFtyhSaV == true){jDuFtyhSaV = false;}
      if(BzzJAoJXaa == true){BzzJAoJXaa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFTEHKLPBT
{ 
  void mWxBCoTTqY()
  { 
      bool QEMzTrjqqA = false;
      bool xXlgEoebOK = false;
      bool KxPdeDwdzu = false;
      bool enzCpKCpLT = false;
      bool KJkqwBzLmM = false;
      bool ktxxiSniUQ = false;
      bool uGruVJYjqt = false;
      bool moQuABMXhc = false;
      bool DjpmJjpBTW = false;
      bool VSVtXDQoVl = false;
      bool cPUsYwdCxg = false;
      bool FQBqMLPEll = false;
      bool SWPTYTSVWw = false;
      bool jWCuAnPxOM = false;
      bool FnEmQFRdgL = false;
      bool mMDjSFzAUE = false;
      bool dIeAwiNFqY = false;
      bool wSpYfeScCT = false;
      bool CnnLIWTSbt = false;
      bool nObJixIEph = false;
      string RTslJRfkfV;
      string mJEXUpjfwn;
      string OPhNyuBqxM;
      string VhSOLewlZk;
      string qaUBlYpwZp;
      string CUHOtBkenN;
      string PnnSzEpoLp;
      string txFKwmugbZ;
      string FFRGKBZEUK;
      string sQyMUDmBBg;
      string iAjjwEOwSG;
      string FEDOIKWgIy;
      string ekUBwczsor;
      string AtetqEUgKG;
      string lclNFoNjDK;
      string gFsDCxeinS;
      string EUHZFLYIWE;
      string poVBMBzHwG;
      string OOpeLtAbrs;
      string YlsqBQVLIs;
      if(RTslJRfkfV == iAjjwEOwSG){QEMzTrjqqA = true;}
      else if(iAjjwEOwSG == RTslJRfkfV){cPUsYwdCxg = true;}
      if(mJEXUpjfwn == FEDOIKWgIy){xXlgEoebOK = true;}
      else if(FEDOIKWgIy == mJEXUpjfwn){FQBqMLPEll = true;}
      if(OPhNyuBqxM == ekUBwczsor){KxPdeDwdzu = true;}
      else if(ekUBwczsor == OPhNyuBqxM){SWPTYTSVWw = true;}
      if(VhSOLewlZk == AtetqEUgKG){enzCpKCpLT = true;}
      else if(AtetqEUgKG == VhSOLewlZk){jWCuAnPxOM = true;}
      if(qaUBlYpwZp == lclNFoNjDK){KJkqwBzLmM = true;}
      else if(lclNFoNjDK == qaUBlYpwZp){FnEmQFRdgL = true;}
      if(CUHOtBkenN == gFsDCxeinS){ktxxiSniUQ = true;}
      else if(gFsDCxeinS == CUHOtBkenN){mMDjSFzAUE = true;}
      if(PnnSzEpoLp == EUHZFLYIWE){uGruVJYjqt = true;}
      else if(EUHZFLYIWE == PnnSzEpoLp){dIeAwiNFqY = true;}
      if(txFKwmugbZ == poVBMBzHwG){moQuABMXhc = true;}
      if(FFRGKBZEUK == OOpeLtAbrs){DjpmJjpBTW = true;}
      if(sQyMUDmBBg == YlsqBQVLIs){VSVtXDQoVl = true;}
      while(poVBMBzHwG == txFKwmugbZ){wSpYfeScCT = true;}
      while(OOpeLtAbrs == OOpeLtAbrs){CnnLIWTSbt = true;}
      while(YlsqBQVLIs == YlsqBQVLIs){nObJixIEph = true;}
      if(QEMzTrjqqA == true){QEMzTrjqqA = false;}
      if(xXlgEoebOK == true){xXlgEoebOK = false;}
      if(KxPdeDwdzu == true){KxPdeDwdzu = false;}
      if(enzCpKCpLT == true){enzCpKCpLT = false;}
      if(KJkqwBzLmM == true){KJkqwBzLmM = false;}
      if(ktxxiSniUQ == true){ktxxiSniUQ = false;}
      if(uGruVJYjqt == true){uGruVJYjqt = false;}
      if(moQuABMXhc == true){moQuABMXhc = false;}
      if(DjpmJjpBTW == true){DjpmJjpBTW = false;}
      if(VSVtXDQoVl == true){VSVtXDQoVl = false;}
      if(cPUsYwdCxg == true){cPUsYwdCxg = false;}
      if(FQBqMLPEll == true){FQBqMLPEll = false;}
      if(SWPTYTSVWw == true){SWPTYTSVWw = false;}
      if(jWCuAnPxOM == true){jWCuAnPxOM = false;}
      if(FnEmQFRdgL == true){FnEmQFRdgL = false;}
      if(mMDjSFzAUE == true){mMDjSFzAUE = false;}
      if(dIeAwiNFqY == true){dIeAwiNFqY = false;}
      if(wSpYfeScCT == true){wSpYfeScCT = false;}
      if(CnnLIWTSbt == true){CnnLIWTSbt = false;}
      if(nObJixIEph == true){nObJixIEph = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUALCCURME
{ 
  void eAZHzhmmSN()
  { 
      bool XKJtZCMlrt = false;
      bool MKeTrKiNtd = false;
      bool QuMRNDggry = false;
      bool HZNOZGTqZA = false;
      bool UXrwxwPsZS = false;
      bool peMGbcyrfW = false;
      bool UfstmlwPtk = false;
      bool qrnsJsCPTR = false;
      bool mmGZHbNGmw = false;
      bool HaLCendyJK = false;
      bool zAzoayqSwh = false;
      bool ZiXOihZTlK = false;
      bool XobxcPfkOV = false;
      bool PEFIRmnQyJ = false;
      bool kuKEWYDwTx = false;
      bool NJLzlJXBLL = false;
      bool RFEaSVcOwu = false;
      bool sIUbZceXaD = false;
      bool LiRQHFrGVH = false;
      bool PmFlreqilA = false;
      string XJVJddlpML;
      string JDqHpSKAKX;
      string RRtrwYAJuE;
      string fITrSBheCg;
      string ziDMDNEDJb;
      string iROTnGPdNE;
      string cbuIeAjzno;
      string kfycXhNhnh;
      string UxATUNszDM;
      string lEQyEXnugC;
      string dEOUpDTlwG;
      string sgofjfabmQ;
      string HjwbCgOzXz;
      string tRAlDPhfcR;
      string tGDxTEOkOY;
      string xMHPusImRJ;
      string nUNwLagDbU;
      string yuzVWAgyIx;
      string RckzChJkqJ;
      string GtNScYsGks;
      if(XJVJddlpML == dEOUpDTlwG){XKJtZCMlrt = true;}
      else if(dEOUpDTlwG == XJVJddlpML){zAzoayqSwh = true;}
      if(JDqHpSKAKX == sgofjfabmQ){MKeTrKiNtd = true;}
      else if(sgofjfabmQ == JDqHpSKAKX){ZiXOihZTlK = true;}
      if(RRtrwYAJuE == HjwbCgOzXz){QuMRNDggry = true;}
      else if(HjwbCgOzXz == RRtrwYAJuE){XobxcPfkOV = true;}
      if(fITrSBheCg == tRAlDPhfcR){HZNOZGTqZA = true;}
      else if(tRAlDPhfcR == fITrSBheCg){PEFIRmnQyJ = true;}
      if(ziDMDNEDJb == tGDxTEOkOY){UXrwxwPsZS = true;}
      else if(tGDxTEOkOY == ziDMDNEDJb){kuKEWYDwTx = true;}
      if(iROTnGPdNE == xMHPusImRJ){peMGbcyrfW = true;}
      else if(xMHPusImRJ == iROTnGPdNE){NJLzlJXBLL = true;}
      if(cbuIeAjzno == nUNwLagDbU){UfstmlwPtk = true;}
      else if(nUNwLagDbU == cbuIeAjzno){RFEaSVcOwu = true;}
      if(kfycXhNhnh == yuzVWAgyIx){qrnsJsCPTR = true;}
      if(UxATUNszDM == RckzChJkqJ){mmGZHbNGmw = true;}
      if(lEQyEXnugC == GtNScYsGks){HaLCendyJK = true;}
      while(yuzVWAgyIx == kfycXhNhnh){sIUbZceXaD = true;}
      while(RckzChJkqJ == RckzChJkqJ){LiRQHFrGVH = true;}
      while(GtNScYsGks == GtNScYsGks){PmFlreqilA = true;}
      if(XKJtZCMlrt == true){XKJtZCMlrt = false;}
      if(MKeTrKiNtd == true){MKeTrKiNtd = false;}
      if(QuMRNDggry == true){QuMRNDggry = false;}
      if(HZNOZGTqZA == true){HZNOZGTqZA = false;}
      if(UXrwxwPsZS == true){UXrwxwPsZS = false;}
      if(peMGbcyrfW == true){peMGbcyrfW = false;}
      if(UfstmlwPtk == true){UfstmlwPtk = false;}
      if(qrnsJsCPTR == true){qrnsJsCPTR = false;}
      if(mmGZHbNGmw == true){mmGZHbNGmw = false;}
      if(HaLCendyJK == true){HaLCendyJK = false;}
      if(zAzoayqSwh == true){zAzoayqSwh = false;}
      if(ZiXOihZTlK == true){ZiXOihZTlK = false;}
      if(XobxcPfkOV == true){XobxcPfkOV = false;}
      if(PEFIRmnQyJ == true){PEFIRmnQyJ = false;}
      if(kuKEWYDwTx == true){kuKEWYDwTx = false;}
      if(NJLzlJXBLL == true){NJLzlJXBLL = false;}
      if(RFEaSVcOwu == true){RFEaSVcOwu = false;}
      if(sIUbZceXaD == true){sIUbZceXaD = false;}
      if(LiRQHFrGVH == true){LiRQHFrGVH = false;}
      if(PmFlreqilA == true){PmFlreqilA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZNNUFCZUT
{ 
  void DJyRbzzNVf()
  { 
      bool qEyHfNigQx = false;
      bool wFeMBxhVds = false;
      bool VObgOJFPFe = false;
      bool TKGWoAILLi = false;
      bool fxzQKZBpQR = false;
      bool ObKoabbRrW = false;
      bool HSbkckyIWA = false;
      bool oWKtNXPLWo = false;
      bool HPznQqARuM = false;
      bool XqSnbNVNmY = false;
      bool arSPcqRPbC = false;
      bool MQuDOqSnUl = false;
      bool kgNKcyDVSA = false;
      bool CCXxNPwjKY = false;
      bool ZjprAHuPZj = false;
      bool thsBmteImd = false;
      bool nuwbAKrxoz = false;
      bool ticuLApVJU = false;
      bool CnwiFUIWKS = false;
      bool knxgkdnOqp = false;
      string nKVncaAmwc;
      string sSumsNtrUP;
      string RdrgpBIEzl;
      string hZwdpdBZzL;
      string WLCOLfuMLT;
      string SOkmuJSnyb;
      string SwmJtSWQxO;
      string MUrIsFadVJ;
      string FurfTToJhf;
      string LMaXsZYsTs;
      string IdPwGyVctp;
      string ioSnVWEHpZ;
      string dNhQDzsUOS;
      string ghJbBafuYU;
      string yLOrxWtlBW;
      string VRCsOtuysG;
      string FBNaJAepmt;
      string pIhVbRypSg;
      string FHSrxPePNG;
      string egCRPwyniw;
      if(nKVncaAmwc == IdPwGyVctp){qEyHfNigQx = true;}
      else if(IdPwGyVctp == nKVncaAmwc){arSPcqRPbC = true;}
      if(sSumsNtrUP == ioSnVWEHpZ){wFeMBxhVds = true;}
      else if(ioSnVWEHpZ == sSumsNtrUP){MQuDOqSnUl = true;}
      if(RdrgpBIEzl == dNhQDzsUOS){VObgOJFPFe = true;}
      else if(dNhQDzsUOS == RdrgpBIEzl){kgNKcyDVSA = true;}
      if(hZwdpdBZzL == ghJbBafuYU){TKGWoAILLi = true;}
      else if(ghJbBafuYU == hZwdpdBZzL){CCXxNPwjKY = true;}
      if(WLCOLfuMLT == yLOrxWtlBW){fxzQKZBpQR = true;}
      else if(yLOrxWtlBW == WLCOLfuMLT){ZjprAHuPZj = true;}
      if(SOkmuJSnyb == VRCsOtuysG){ObKoabbRrW = true;}
      else if(VRCsOtuysG == SOkmuJSnyb){thsBmteImd = true;}
      if(SwmJtSWQxO == FBNaJAepmt){HSbkckyIWA = true;}
      else if(FBNaJAepmt == SwmJtSWQxO){nuwbAKrxoz = true;}
      if(MUrIsFadVJ == pIhVbRypSg){oWKtNXPLWo = true;}
      if(FurfTToJhf == FHSrxPePNG){HPznQqARuM = true;}
      if(LMaXsZYsTs == egCRPwyniw){XqSnbNVNmY = true;}
      while(pIhVbRypSg == MUrIsFadVJ){ticuLApVJU = true;}
      while(FHSrxPePNG == FHSrxPePNG){CnwiFUIWKS = true;}
      while(egCRPwyniw == egCRPwyniw){knxgkdnOqp = true;}
      if(qEyHfNigQx == true){qEyHfNigQx = false;}
      if(wFeMBxhVds == true){wFeMBxhVds = false;}
      if(VObgOJFPFe == true){VObgOJFPFe = false;}
      if(TKGWoAILLi == true){TKGWoAILLi = false;}
      if(fxzQKZBpQR == true){fxzQKZBpQR = false;}
      if(ObKoabbRrW == true){ObKoabbRrW = false;}
      if(HSbkckyIWA == true){HSbkckyIWA = false;}
      if(oWKtNXPLWo == true){oWKtNXPLWo = false;}
      if(HPznQqARuM == true){HPznQqARuM = false;}
      if(XqSnbNVNmY == true){XqSnbNVNmY = false;}
      if(arSPcqRPbC == true){arSPcqRPbC = false;}
      if(MQuDOqSnUl == true){MQuDOqSnUl = false;}
      if(kgNKcyDVSA == true){kgNKcyDVSA = false;}
      if(CCXxNPwjKY == true){CCXxNPwjKY = false;}
      if(ZjprAHuPZj == true){ZjprAHuPZj = false;}
      if(thsBmteImd == true){thsBmteImd = false;}
      if(nuwbAKrxoz == true){nuwbAKrxoz = false;}
      if(ticuLApVJU == true){ticuLApVJU = false;}
      if(CnwiFUIWKS == true){CnwiFUIWKS = false;}
      if(knxgkdnOqp == true){knxgkdnOqp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYONYVPQJH
{ 
  void eFnKgNnJwW()
  { 
      bool YdFVUybFwf = false;
      bool wqVGGPfCPt = false;
      bool fTFONPUTRM = false;
      bool BXPHUmfnuq = false;
      bool pAlYsAdaNk = false;
      bool uIaKiFXpIE = false;
      bool dHmidXaOlT = false;
      bool irHYEfhgUN = false;
      bool lsGgRswEYP = false;
      bool OoepNhMCtV = false;
      bool YOotBDACGC = false;
      bool XpVuSjBGRj = false;
      bool aVoVEtMRLV = false;
      bool SfmznWDLeN = false;
      bool styVqYTjWc = false;
      bool gGjJuCYSpH = false;
      bool qiqkirDVGu = false;
      bool foaDqgXTef = false;
      bool acthnMucEk = false;
      bool xkVXWKCNlz = false;
      string ShBhXtoEdj;
      string DhGszpIMMN;
      string jgAKDLXwBK;
      string kNZzCenusR;
      string gBLoaeHKpf;
      string LsOegkgqdL;
      string WrCTypHGqT;
      string CNSugiVLiX;
      string ENFVzryuRR;
      string xwQhtnyrqk;
      string WBTWcxaTyy;
      string PVIFHJlgTF;
      string rLoZVFwjAr;
      string jcTxBDtirB;
      string RdxTBbnKaj;
      string CQXksKLtAX;
      string BpSFNlCKEE;
      string PDoSnNOUXt;
      string QlJPpSFhEp;
      string qzhUAaLqFP;
      if(ShBhXtoEdj == WBTWcxaTyy){YdFVUybFwf = true;}
      else if(WBTWcxaTyy == ShBhXtoEdj){YOotBDACGC = true;}
      if(DhGszpIMMN == PVIFHJlgTF){wqVGGPfCPt = true;}
      else if(PVIFHJlgTF == DhGszpIMMN){XpVuSjBGRj = true;}
      if(jgAKDLXwBK == rLoZVFwjAr){fTFONPUTRM = true;}
      else if(rLoZVFwjAr == jgAKDLXwBK){aVoVEtMRLV = true;}
      if(kNZzCenusR == jcTxBDtirB){BXPHUmfnuq = true;}
      else if(jcTxBDtirB == kNZzCenusR){SfmznWDLeN = true;}
      if(gBLoaeHKpf == RdxTBbnKaj){pAlYsAdaNk = true;}
      else if(RdxTBbnKaj == gBLoaeHKpf){styVqYTjWc = true;}
      if(LsOegkgqdL == CQXksKLtAX){uIaKiFXpIE = true;}
      else if(CQXksKLtAX == LsOegkgqdL){gGjJuCYSpH = true;}
      if(WrCTypHGqT == BpSFNlCKEE){dHmidXaOlT = true;}
      else if(BpSFNlCKEE == WrCTypHGqT){qiqkirDVGu = true;}
      if(CNSugiVLiX == PDoSnNOUXt){irHYEfhgUN = true;}
      if(ENFVzryuRR == QlJPpSFhEp){lsGgRswEYP = true;}
      if(xwQhtnyrqk == qzhUAaLqFP){OoepNhMCtV = true;}
      while(PDoSnNOUXt == CNSugiVLiX){foaDqgXTef = true;}
      while(QlJPpSFhEp == QlJPpSFhEp){acthnMucEk = true;}
      while(qzhUAaLqFP == qzhUAaLqFP){xkVXWKCNlz = true;}
      if(YdFVUybFwf == true){YdFVUybFwf = false;}
      if(wqVGGPfCPt == true){wqVGGPfCPt = false;}
      if(fTFONPUTRM == true){fTFONPUTRM = false;}
      if(BXPHUmfnuq == true){BXPHUmfnuq = false;}
      if(pAlYsAdaNk == true){pAlYsAdaNk = false;}
      if(uIaKiFXpIE == true){uIaKiFXpIE = false;}
      if(dHmidXaOlT == true){dHmidXaOlT = false;}
      if(irHYEfhgUN == true){irHYEfhgUN = false;}
      if(lsGgRswEYP == true){lsGgRswEYP = false;}
      if(OoepNhMCtV == true){OoepNhMCtV = false;}
      if(YOotBDACGC == true){YOotBDACGC = false;}
      if(XpVuSjBGRj == true){XpVuSjBGRj = false;}
      if(aVoVEtMRLV == true){aVoVEtMRLV = false;}
      if(SfmznWDLeN == true){SfmznWDLeN = false;}
      if(styVqYTjWc == true){styVqYTjWc = false;}
      if(gGjJuCYSpH == true){gGjJuCYSpH = false;}
      if(qiqkirDVGu == true){qiqkirDVGu = false;}
      if(foaDqgXTef == true){foaDqgXTef = false;}
      if(acthnMucEk == true){acthnMucEk = false;}
      if(xkVXWKCNlz == true){xkVXWKCNlz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJPRXQEIKN
{ 
  void dDDFEKAXcK()
  { 
      bool qzMyuBNqct = false;
      bool SVqIUBqQZH = false;
      bool hUeYKxSVtA = false;
      bool xmoOzWilrH = false;
      bool nsinnnIfXX = false;
      bool xyAnMWUmmy = false;
      bool irxcwffcIy = false;
      bool SFYRSnkpkW = false;
      bool nlyVCzmBBc = false;
      bool CuytYwwGqH = false;
      bool HeXZFrZhUY = false;
      bool ldCQJwsbZx = false;
      bool sebewWHesW = false;
      bool qezcOJOYPK = false;
      bool YEgbpXsgjc = false;
      bool CUfsOcDrci = false;
      bool juoxgGdZBA = false;
      bool gULPYnyznX = false;
      bool dZtQUWzFNl = false;
      bool GVugZdPitj = false;
      string hpDhsaTrHo;
      string BQUDuJaQld;
      string oNcOXrCSkC;
      string lMjmAwHXGP;
      string FiKaehdbOa;
      string ppHZtUNoJA;
      string YAHECnfhDz;
      string BCJWXGDCip;
      string NZEJLwFKrf;
      string iSNGqFaFXq;
      string CwYPZmfjBn;
      string QKFTlywysF;
      string iVoXPioDfS;
      string exdqnRBniY;
      string QUIEOXMsTr;
      string JcMRIfGBzp;
      string ybEiJTfNfU;
      string xHOUoNMkJq;
      string VwjmJBkLiH;
      string KAnsZoPZuu;
      if(hpDhsaTrHo == CwYPZmfjBn){qzMyuBNqct = true;}
      else if(CwYPZmfjBn == hpDhsaTrHo){HeXZFrZhUY = true;}
      if(BQUDuJaQld == QKFTlywysF){SVqIUBqQZH = true;}
      else if(QKFTlywysF == BQUDuJaQld){ldCQJwsbZx = true;}
      if(oNcOXrCSkC == iVoXPioDfS){hUeYKxSVtA = true;}
      else if(iVoXPioDfS == oNcOXrCSkC){sebewWHesW = true;}
      if(lMjmAwHXGP == exdqnRBniY){xmoOzWilrH = true;}
      else if(exdqnRBniY == lMjmAwHXGP){qezcOJOYPK = true;}
      if(FiKaehdbOa == QUIEOXMsTr){nsinnnIfXX = true;}
      else if(QUIEOXMsTr == FiKaehdbOa){YEgbpXsgjc = true;}
      if(ppHZtUNoJA == JcMRIfGBzp){xyAnMWUmmy = true;}
      else if(JcMRIfGBzp == ppHZtUNoJA){CUfsOcDrci = true;}
      if(YAHECnfhDz == ybEiJTfNfU){irxcwffcIy = true;}
      else if(ybEiJTfNfU == YAHECnfhDz){juoxgGdZBA = true;}
      if(BCJWXGDCip == xHOUoNMkJq){SFYRSnkpkW = true;}
      if(NZEJLwFKrf == VwjmJBkLiH){nlyVCzmBBc = true;}
      if(iSNGqFaFXq == KAnsZoPZuu){CuytYwwGqH = true;}
      while(xHOUoNMkJq == BCJWXGDCip){gULPYnyznX = true;}
      while(VwjmJBkLiH == VwjmJBkLiH){dZtQUWzFNl = true;}
      while(KAnsZoPZuu == KAnsZoPZuu){GVugZdPitj = true;}
      if(qzMyuBNqct == true){qzMyuBNqct = false;}
      if(SVqIUBqQZH == true){SVqIUBqQZH = false;}
      if(hUeYKxSVtA == true){hUeYKxSVtA = false;}
      if(xmoOzWilrH == true){xmoOzWilrH = false;}
      if(nsinnnIfXX == true){nsinnnIfXX = false;}
      if(xyAnMWUmmy == true){xyAnMWUmmy = false;}
      if(irxcwffcIy == true){irxcwffcIy = false;}
      if(SFYRSnkpkW == true){SFYRSnkpkW = false;}
      if(nlyVCzmBBc == true){nlyVCzmBBc = false;}
      if(CuytYwwGqH == true){CuytYwwGqH = false;}
      if(HeXZFrZhUY == true){HeXZFrZhUY = false;}
      if(ldCQJwsbZx == true){ldCQJwsbZx = false;}
      if(sebewWHesW == true){sebewWHesW = false;}
      if(qezcOJOYPK == true){qezcOJOYPK = false;}
      if(YEgbpXsgjc == true){YEgbpXsgjc = false;}
      if(CUfsOcDrci == true){CUfsOcDrci = false;}
      if(juoxgGdZBA == true){juoxgGdZBA = false;}
      if(gULPYnyznX == true){gULPYnyznX = false;}
      if(dZtQUWzFNl == true){dZtQUWzFNl = false;}
      if(GVugZdPitj == true){GVugZdPitj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIAPYOVJPE
{ 
  void YhsULPNHhO()
  { 
      bool LpyHxXJENl = false;
      bool nkdsnoBtJp = false;
      bool MEmYaQGmPQ = false;
      bool CYCBXsCqVG = false;
      bool YwplLnFAjE = false;
      bool KiIxPGCZgg = false;
      bool QWoxiOibVt = false;
      bool mKXDRPNBMl = false;
      bool KGCKGTPFlQ = false;
      bool pbKooCHsCw = false;
      bool FcdoRzLFeA = false;
      bool rBNtVKTdpP = false;
      bool zcpEEKAhNP = false;
      bool HUyPfhbNrG = false;
      bool IKZkXoOPSe = false;
      bool hdCmxblZjH = false;
      bool zcqPrXCxOn = false;
      bool hFliHnDEfP = false;
      bool ujOigdRLRD = false;
      bool uCckHeTJsA = false;
      string QFyDnypOAE;
      string AplBmhpMMZ;
      string NTVOnEjOFJ;
      string sIrsPJpquE;
      string YjxrhcWOKB;
      string MYlrExijPj;
      string ObJpKryrld;
      string rzRHAcVdfK;
      string gVDDxTVznR;
      string ZGaKpxZGho;
      string eecgINHerb;
      string bFDECrXFsp;
      string WyDTDlXGQD;
      string COwqfBrWuj;
      string MqHMoUCWIx;
      string YUNqSfbIcW;
      string oANnYNJMYA;
      string ABKJcfqpdi;
      string iAyTdhAEYA;
      string ZjtXtMcSnb;
      if(QFyDnypOAE == eecgINHerb){LpyHxXJENl = true;}
      else if(eecgINHerb == QFyDnypOAE){FcdoRzLFeA = true;}
      if(AplBmhpMMZ == bFDECrXFsp){nkdsnoBtJp = true;}
      else if(bFDECrXFsp == AplBmhpMMZ){rBNtVKTdpP = true;}
      if(NTVOnEjOFJ == WyDTDlXGQD){MEmYaQGmPQ = true;}
      else if(WyDTDlXGQD == NTVOnEjOFJ){zcpEEKAhNP = true;}
      if(sIrsPJpquE == COwqfBrWuj){CYCBXsCqVG = true;}
      else if(COwqfBrWuj == sIrsPJpquE){HUyPfhbNrG = true;}
      if(YjxrhcWOKB == MqHMoUCWIx){YwplLnFAjE = true;}
      else if(MqHMoUCWIx == YjxrhcWOKB){IKZkXoOPSe = true;}
      if(MYlrExijPj == YUNqSfbIcW){KiIxPGCZgg = true;}
      else if(YUNqSfbIcW == MYlrExijPj){hdCmxblZjH = true;}
      if(ObJpKryrld == oANnYNJMYA){QWoxiOibVt = true;}
      else if(oANnYNJMYA == ObJpKryrld){zcqPrXCxOn = true;}
      if(rzRHAcVdfK == ABKJcfqpdi){mKXDRPNBMl = true;}
      if(gVDDxTVznR == iAyTdhAEYA){KGCKGTPFlQ = true;}
      if(ZGaKpxZGho == ZjtXtMcSnb){pbKooCHsCw = true;}
      while(ABKJcfqpdi == rzRHAcVdfK){hFliHnDEfP = true;}
      while(iAyTdhAEYA == iAyTdhAEYA){ujOigdRLRD = true;}
      while(ZjtXtMcSnb == ZjtXtMcSnb){uCckHeTJsA = true;}
      if(LpyHxXJENl == true){LpyHxXJENl = false;}
      if(nkdsnoBtJp == true){nkdsnoBtJp = false;}
      if(MEmYaQGmPQ == true){MEmYaQGmPQ = false;}
      if(CYCBXsCqVG == true){CYCBXsCqVG = false;}
      if(YwplLnFAjE == true){YwplLnFAjE = false;}
      if(KiIxPGCZgg == true){KiIxPGCZgg = false;}
      if(QWoxiOibVt == true){QWoxiOibVt = false;}
      if(mKXDRPNBMl == true){mKXDRPNBMl = false;}
      if(KGCKGTPFlQ == true){KGCKGTPFlQ = false;}
      if(pbKooCHsCw == true){pbKooCHsCw = false;}
      if(FcdoRzLFeA == true){FcdoRzLFeA = false;}
      if(rBNtVKTdpP == true){rBNtVKTdpP = false;}
      if(zcpEEKAhNP == true){zcpEEKAhNP = false;}
      if(HUyPfhbNrG == true){HUyPfhbNrG = false;}
      if(IKZkXoOPSe == true){IKZkXoOPSe = false;}
      if(hdCmxblZjH == true){hdCmxblZjH = false;}
      if(zcqPrXCxOn == true){zcqPrXCxOn = false;}
      if(hFliHnDEfP == true){hFliHnDEfP = false;}
      if(ujOigdRLRD == true){ujOigdRLRD = false;}
      if(uCckHeTJsA == true){uCckHeTJsA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBGORJHSYT
{ 
  void wapgFYKRPK()
  { 
      bool RjsiYONJSM = false;
      bool OeozPKSPjK = false;
      bool BoZfLeYYET = false;
      bool ZNhiwLnuxT = false;
      bool XkNTjmhxpL = false;
      bool PAmjbcJMWt = false;
      bool ooEzmAwFDD = false;
      bool WWRPmQaGuY = false;
      bool waisEYayHS = false;
      bool CaYDeifOgj = false;
      bool pbtmnshXwL = false;
      bool CDRxxNFLtN = false;
      bool ZyyjBwxOkE = false;
      bool jMYLiUgwFL = false;
      bool qDCwQyJbFQ = false;
      bool cUTSJrdJkr = false;
      bool uTlqapdFOc = false;
      bool gJGiWWuCTD = false;
      bool lVIUbPrGBp = false;
      bool pWKMQXQKUa = false;
      string JtROQXRHWP;
      string AFHSJTYXpQ;
      string jdNzGOkHoV;
      string NWBTgszMRo;
      string cLZGWeNYfV;
      string KtkZAffRHC;
      string mJRACdDmlP;
      string ULFAmYEHbb;
      string ALbTLTlbSA;
      string MgFOCSsYEs;
      string bamQAynjlb;
      string bYofCahynh;
      string qaTkCnGqyT;
      string feDiAYYLSN;
      string fBoqYnqYMb;
      string ktjVCAHBNM;
      string qxlSwwVGfd;
      string CWfaCokcLO;
      string wgdWiktggz;
      string RWxGVhPWtc;
      if(JtROQXRHWP == bamQAynjlb){RjsiYONJSM = true;}
      else if(bamQAynjlb == JtROQXRHWP){pbtmnshXwL = true;}
      if(AFHSJTYXpQ == bYofCahynh){OeozPKSPjK = true;}
      else if(bYofCahynh == AFHSJTYXpQ){CDRxxNFLtN = true;}
      if(jdNzGOkHoV == qaTkCnGqyT){BoZfLeYYET = true;}
      else if(qaTkCnGqyT == jdNzGOkHoV){ZyyjBwxOkE = true;}
      if(NWBTgszMRo == feDiAYYLSN){ZNhiwLnuxT = true;}
      else if(feDiAYYLSN == NWBTgszMRo){jMYLiUgwFL = true;}
      if(cLZGWeNYfV == fBoqYnqYMb){XkNTjmhxpL = true;}
      else if(fBoqYnqYMb == cLZGWeNYfV){qDCwQyJbFQ = true;}
      if(KtkZAffRHC == ktjVCAHBNM){PAmjbcJMWt = true;}
      else if(ktjVCAHBNM == KtkZAffRHC){cUTSJrdJkr = true;}
      if(mJRACdDmlP == qxlSwwVGfd){ooEzmAwFDD = true;}
      else if(qxlSwwVGfd == mJRACdDmlP){uTlqapdFOc = true;}
      if(ULFAmYEHbb == CWfaCokcLO){WWRPmQaGuY = true;}
      if(ALbTLTlbSA == wgdWiktggz){waisEYayHS = true;}
      if(MgFOCSsYEs == RWxGVhPWtc){CaYDeifOgj = true;}
      while(CWfaCokcLO == ULFAmYEHbb){gJGiWWuCTD = true;}
      while(wgdWiktggz == wgdWiktggz){lVIUbPrGBp = true;}
      while(RWxGVhPWtc == RWxGVhPWtc){pWKMQXQKUa = true;}
      if(RjsiYONJSM == true){RjsiYONJSM = false;}
      if(OeozPKSPjK == true){OeozPKSPjK = false;}
      if(BoZfLeYYET == true){BoZfLeYYET = false;}
      if(ZNhiwLnuxT == true){ZNhiwLnuxT = false;}
      if(XkNTjmhxpL == true){XkNTjmhxpL = false;}
      if(PAmjbcJMWt == true){PAmjbcJMWt = false;}
      if(ooEzmAwFDD == true){ooEzmAwFDD = false;}
      if(WWRPmQaGuY == true){WWRPmQaGuY = false;}
      if(waisEYayHS == true){waisEYayHS = false;}
      if(CaYDeifOgj == true){CaYDeifOgj = false;}
      if(pbtmnshXwL == true){pbtmnshXwL = false;}
      if(CDRxxNFLtN == true){CDRxxNFLtN = false;}
      if(ZyyjBwxOkE == true){ZyyjBwxOkE = false;}
      if(jMYLiUgwFL == true){jMYLiUgwFL = false;}
      if(qDCwQyJbFQ == true){qDCwQyJbFQ = false;}
      if(cUTSJrdJkr == true){cUTSJrdJkr = false;}
      if(uTlqapdFOc == true){uTlqapdFOc = false;}
      if(gJGiWWuCTD == true){gJGiWWuCTD = false;}
      if(lVIUbPrGBp == true){lVIUbPrGBp = false;}
      if(pWKMQXQKUa == true){pWKMQXQKUa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNXAZNYJGZ
{ 
  void NUklAeLoMg()
  { 
      bool flEdCBKyxo = false;
      bool EMjLrWwcEa = false;
      bool qiEmJSLUhS = false;
      bool tDTWqtmnjO = false;
      bool kRPDSBzlYn = false;
      bool FHEnVxgRUj = false;
      bool opQeuAsMTy = false;
      bool jHspoYSBTI = false;
      bool TZusNlzfBt = false;
      bool MVTzYuBkIR = false;
      bool IlSaEyOOyw = false;
      bool dfyMPPtWQI = false;
      bool BNLYkNmsQs = false;
      bool WhsBzgGUoP = false;
      bool WjgFQgXHiI = false;
      bool BeTzQtaspp = false;
      bool KUxEYwmwMi = false;
      bool JZhBlRgFHD = false;
      bool pfJHrrNtkF = false;
      bool GNdyEBmbfU = false;
      string gnSXOhGkFg;
      string rMHNWYkyse;
      string BxawXIxCcn;
      string tIwkVRPOqt;
      string EhcqiZjSmx;
      string rrDVijMWzG;
      string jEHQmjQVrE;
      string IVHzaSTjMy;
      string XeOewBEZCl;
      string EsPkJzZLDz;
      string IOainVkEuQ;
      string QcKAhFocTk;
      string eqTFzPGVoa;
      string sIfMoJDfpa;
      string QAdlVbiOCD;
      string KxqSURuUiY;
      string OOOUWHwxKY;
      string BIlsUeMhjX;
      string fqSlPwQNrX;
      string OixRLBkJON;
      if(gnSXOhGkFg == IOainVkEuQ){flEdCBKyxo = true;}
      else if(IOainVkEuQ == gnSXOhGkFg){IlSaEyOOyw = true;}
      if(rMHNWYkyse == QcKAhFocTk){EMjLrWwcEa = true;}
      else if(QcKAhFocTk == rMHNWYkyse){dfyMPPtWQI = true;}
      if(BxawXIxCcn == eqTFzPGVoa){qiEmJSLUhS = true;}
      else if(eqTFzPGVoa == BxawXIxCcn){BNLYkNmsQs = true;}
      if(tIwkVRPOqt == sIfMoJDfpa){tDTWqtmnjO = true;}
      else if(sIfMoJDfpa == tIwkVRPOqt){WhsBzgGUoP = true;}
      if(EhcqiZjSmx == QAdlVbiOCD){kRPDSBzlYn = true;}
      else if(QAdlVbiOCD == EhcqiZjSmx){WjgFQgXHiI = true;}
      if(rrDVijMWzG == KxqSURuUiY){FHEnVxgRUj = true;}
      else if(KxqSURuUiY == rrDVijMWzG){BeTzQtaspp = true;}
      if(jEHQmjQVrE == OOOUWHwxKY){opQeuAsMTy = true;}
      else if(OOOUWHwxKY == jEHQmjQVrE){KUxEYwmwMi = true;}
      if(IVHzaSTjMy == BIlsUeMhjX){jHspoYSBTI = true;}
      if(XeOewBEZCl == fqSlPwQNrX){TZusNlzfBt = true;}
      if(EsPkJzZLDz == OixRLBkJON){MVTzYuBkIR = true;}
      while(BIlsUeMhjX == IVHzaSTjMy){JZhBlRgFHD = true;}
      while(fqSlPwQNrX == fqSlPwQNrX){pfJHrrNtkF = true;}
      while(OixRLBkJON == OixRLBkJON){GNdyEBmbfU = true;}
      if(flEdCBKyxo == true){flEdCBKyxo = false;}
      if(EMjLrWwcEa == true){EMjLrWwcEa = false;}
      if(qiEmJSLUhS == true){qiEmJSLUhS = false;}
      if(tDTWqtmnjO == true){tDTWqtmnjO = false;}
      if(kRPDSBzlYn == true){kRPDSBzlYn = false;}
      if(FHEnVxgRUj == true){FHEnVxgRUj = false;}
      if(opQeuAsMTy == true){opQeuAsMTy = false;}
      if(jHspoYSBTI == true){jHspoYSBTI = false;}
      if(TZusNlzfBt == true){TZusNlzfBt = false;}
      if(MVTzYuBkIR == true){MVTzYuBkIR = false;}
      if(IlSaEyOOyw == true){IlSaEyOOyw = false;}
      if(dfyMPPtWQI == true){dfyMPPtWQI = false;}
      if(BNLYkNmsQs == true){BNLYkNmsQs = false;}
      if(WhsBzgGUoP == true){WhsBzgGUoP = false;}
      if(WjgFQgXHiI == true){WjgFQgXHiI = false;}
      if(BeTzQtaspp == true){BeTzQtaspp = false;}
      if(KUxEYwmwMi == true){KUxEYwmwMi = false;}
      if(JZhBlRgFHD == true){JZhBlRgFHD = false;}
      if(pfJHrrNtkF == true){pfJHrrNtkF = false;}
      if(GNdyEBmbfU == true){GNdyEBmbfU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSOBYJFTXI
{ 
  void ArUFkGYSNO()
  { 
      bool IIhsuOyxKe = false;
      bool gXsyDcaFcu = false;
      bool KbPcPDQIKp = false;
      bool zPdEjJoqCs = false;
      bool qkbexeResV = false;
      bool JLpwlfrEcq = false;
      bool xolTeQtnNs = false;
      bool niDiEZAkek = false;
      bool klPofmZgSE = false;
      bool QjOKwBzHzf = false;
      bool kdQzhZIGrM = false;
      bool fGZrGKZxnr = false;
      bool qMVJbDUslC = false;
      bool ZrlzAGVQGG = false;
      bool eSoFXKKVDk = false;
      bool bCTGoXIGWd = false;
      bool FOTommTZrA = false;
      bool oIpgMYXPlR = false;
      bool sypBaXXeKb = false;
      bool yOtcAPyzSj = false;
      string sFCslPNhyS;
      string ouGmUspCeK;
      string FzdjuiBSXa;
      string mZBDTofnes;
      string TkprxxtHnj;
      string OfusxsbRyD;
      string OtKXfPtDTe;
      string NCXkqTJlmx;
      string ntdmMGdHFa;
      string NNpadYaSLg;
      string DqmIVMIJCd;
      string joeBPUPWKY;
      string kmxrRALwGR;
      string spZFtwGURA;
      string xUEbpXhoLJ;
      string JDHluPsuqV;
      string ALCkjsPZGS;
      string OtFKbQiVCs;
      string RWkxIohmJd;
      string DLdwzkRSqx;
      if(sFCslPNhyS == DqmIVMIJCd){IIhsuOyxKe = true;}
      else if(DqmIVMIJCd == sFCslPNhyS){kdQzhZIGrM = true;}
      if(ouGmUspCeK == joeBPUPWKY){gXsyDcaFcu = true;}
      else if(joeBPUPWKY == ouGmUspCeK){fGZrGKZxnr = true;}
      if(FzdjuiBSXa == kmxrRALwGR){KbPcPDQIKp = true;}
      else if(kmxrRALwGR == FzdjuiBSXa){qMVJbDUslC = true;}
      if(mZBDTofnes == spZFtwGURA){zPdEjJoqCs = true;}
      else if(spZFtwGURA == mZBDTofnes){ZrlzAGVQGG = true;}
      if(TkprxxtHnj == xUEbpXhoLJ){qkbexeResV = true;}
      else if(xUEbpXhoLJ == TkprxxtHnj){eSoFXKKVDk = true;}
      if(OfusxsbRyD == JDHluPsuqV){JLpwlfrEcq = true;}
      else if(JDHluPsuqV == OfusxsbRyD){bCTGoXIGWd = true;}
      if(OtKXfPtDTe == ALCkjsPZGS){xolTeQtnNs = true;}
      else if(ALCkjsPZGS == OtKXfPtDTe){FOTommTZrA = true;}
      if(NCXkqTJlmx == OtFKbQiVCs){niDiEZAkek = true;}
      if(ntdmMGdHFa == RWkxIohmJd){klPofmZgSE = true;}
      if(NNpadYaSLg == DLdwzkRSqx){QjOKwBzHzf = true;}
      while(OtFKbQiVCs == NCXkqTJlmx){oIpgMYXPlR = true;}
      while(RWkxIohmJd == RWkxIohmJd){sypBaXXeKb = true;}
      while(DLdwzkRSqx == DLdwzkRSqx){yOtcAPyzSj = true;}
      if(IIhsuOyxKe == true){IIhsuOyxKe = false;}
      if(gXsyDcaFcu == true){gXsyDcaFcu = false;}
      if(KbPcPDQIKp == true){KbPcPDQIKp = false;}
      if(zPdEjJoqCs == true){zPdEjJoqCs = false;}
      if(qkbexeResV == true){qkbexeResV = false;}
      if(JLpwlfrEcq == true){JLpwlfrEcq = false;}
      if(xolTeQtnNs == true){xolTeQtnNs = false;}
      if(niDiEZAkek == true){niDiEZAkek = false;}
      if(klPofmZgSE == true){klPofmZgSE = false;}
      if(QjOKwBzHzf == true){QjOKwBzHzf = false;}
      if(kdQzhZIGrM == true){kdQzhZIGrM = false;}
      if(fGZrGKZxnr == true){fGZrGKZxnr = false;}
      if(qMVJbDUslC == true){qMVJbDUslC = false;}
      if(ZrlzAGVQGG == true){ZrlzAGVQGG = false;}
      if(eSoFXKKVDk == true){eSoFXKKVDk = false;}
      if(bCTGoXIGWd == true){bCTGoXIGWd = false;}
      if(FOTommTZrA == true){FOTommTZrA = false;}
      if(oIpgMYXPlR == true){oIpgMYXPlR = false;}
      if(sypBaXXeKb == true){sypBaXXeKb = false;}
      if(yOtcAPyzSj == true){yOtcAPyzSj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNQVUTYXYT
{ 
  void kZInuZkqsJ()
  { 
      bool LrhXcsSzrC = false;
      bool raIZYptlVp = false;
      bool lTYciPQayV = false;
      bool fLAqMGxnPE = false;
      bool WfOPFpYXme = false;
      bool rRrMUqTEoN = false;
      bool cqBWWgZQMR = false;
      bool sFWQSGEJWr = false;
      bool prmTcOSmWU = false;
      bool mrzCbeerrY = false;
      bool PHKUlltbsO = false;
      bool mKgxWjEhtH = false;
      bool NltreAGTnm = false;
      bool aMQxbihRgq = false;
      bool TpsHhcKCer = false;
      bool axyjKdMSpk = false;
      bool eanGmasiUn = false;
      bool CmACnXrlJB = false;
      bool oEowMdOfmy = false;
      bool VOawLsCmUH = false;
      string kzbRdPNaTZ;
      string TZGNBtbhsI;
      string VhDVhVMwKE;
      string kOIKwSilbO;
      string iuyqKqKtqR;
      string ByeABDuFjH;
      string CQQPnEQuQh;
      string LpFeZZiLKq;
      string LRFrCljIJs;
      string WcCULSehCG;
      string ZPdJGKrzZa;
      string TjtrwkKYMC;
      string THkXKhnkTG;
      string uBIEQunwkr;
      string tjhhYmiJYZ;
      string HFUAlRdGyY;
      string VHfTeSbpbA;
      string xOmUHjZDyX;
      string zeMsyofHRy;
      string RgyMVlDOCG;
      if(kzbRdPNaTZ == ZPdJGKrzZa){LrhXcsSzrC = true;}
      else if(ZPdJGKrzZa == kzbRdPNaTZ){PHKUlltbsO = true;}
      if(TZGNBtbhsI == TjtrwkKYMC){raIZYptlVp = true;}
      else if(TjtrwkKYMC == TZGNBtbhsI){mKgxWjEhtH = true;}
      if(VhDVhVMwKE == THkXKhnkTG){lTYciPQayV = true;}
      else if(THkXKhnkTG == VhDVhVMwKE){NltreAGTnm = true;}
      if(kOIKwSilbO == uBIEQunwkr){fLAqMGxnPE = true;}
      else if(uBIEQunwkr == kOIKwSilbO){aMQxbihRgq = true;}
      if(iuyqKqKtqR == tjhhYmiJYZ){WfOPFpYXme = true;}
      else if(tjhhYmiJYZ == iuyqKqKtqR){TpsHhcKCer = true;}
      if(ByeABDuFjH == HFUAlRdGyY){rRrMUqTEoN = true;}
      else if(HFUAlRdGyY == ByeABDuFjH){axyjKdMSpk = true;}
      if(CQQPnEQuQh == VHfTeSbpbA){cqBWWgZQMR = true;}
      else if(VHfTeSbpbA == CQQPnEQuQh){eanGmasiUn = true;}
      if(LpFeZZiLKq == xOmUHjZDyX){sFWQSGEJWr = true;}
      if(LRFrCljIJs == zeMsyofHRy){prmTcOSmWU = true;}
      if(WcCULSehCG == RgyMVlDOCG){mrzCbeerrY = true;}
      while(xOmUHjZDyX == LpFeZZiLKq){CmACnXrlJB = true;}
      while(zeMsyofHRy == zeMsyofHRy){oEowMdOfmy = true;}
      while(RgyMVlDOCG == RgyMVlDOCG){VOawLsCmUH = true;}
      if(LrhXcsSzrC == true){LrhXcsSzrC = false;}
      if(raIZYptlVp == true){raIZYptlVp = false;}
      if(lTYciPQayV == true){lTYciPQayV = false;}
      if(fLAqMGxnPE == true){fLAqMGxnPE = false;}
      if(WfOPFpYXme == true){WfOPFpYXme = false;}
      if(rRrMUqTEoN == true){rRrMUqTEoN = false;}
      if(cqBWWgZQMR == true){cqBWWgZQMR = false;}
      if(sFWQSGEJWr == true){sFWQSGEJWr = false;}
      if(prmTcOSmWU == true){prmTcOSmWU = false;}
      if(mrzCbeerrY == true){mrzCbeerrY = false;}
      if(PHKUlltbsO == true){PHKUlltbsO = false;}
      if(mKgxWjEhtH == true){mKgxWjEhtH = false;}
      if(NltreAGTnm == true){NltreAGTnm = false;}
      if(aMQxbihRgq == true){aMQxbihRgq = false;}
      if(TpsHhcKCer == true){TpsHhcKCer = false;}
      if(axyjKdMSpk == true){axyjKdMSpk = false;}
      if(eanGmasiUn == true){eanGmasiUn = false;}
      if(CmACnXrlJB == true){CmACnXrlJB = false;}
      if(oEowMdOfmy == true){oEowMdOfmy = false;}
      if(VOawLsCmUH == true){VOawLsCmUH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPVLEVVNFX
{ 
  void ylYgCNhDZt()
  { 
      bool zCSFhBnJGZ = false;
      bool keyaJdOhKK = false;
      bool GtbEbUnSwK = false;
      bool hxnfRqAGQF = false;
      bool UxJPtzwixi = false;
      bool JJtwPFaOdM = false;
      bool MUMurnpRIR = false;
      bool cIQEpIjMJb = false;
      bool YEVMBXCrQM = false;
      bool QkbDszjOWG = false;
      bool IdZeFBspFG = false;
      bool VOFCnHzAtU = false;
      bool lyBwAqfMLp = false;
      bool XVoDTtepHA = false;
      bool eMlJqCfZPk = false;
      bool AjUBUKcdeN = false;
      bool UfdPhzYChs = false;
      bool cIsspZLqFx = false;
      bool LGxapnBmiJ = false;
      bool RALsfyhWaq = false;
      string IehLKRZziX;
      string dJakbPaiyp;
      string gFhkXtbylh;
      string rejiaXYumw;
      string eKpDxopuYJ;
      string AtekODwwmP;
      string pbMBfyZrJD;
      string qewCKVOeni;
      string DfYcgxAyUX;
      string bbHXGDynXy;
      string OylUSVybZr;
      string nRHELJCjUh;
      string yaXlbOXXuH;
      string XaGpTFtDKL;
      string yXXbiKTDLx;
      string ANSpAnaAsD;
      string yafSUNKRjG;
      string OzZJiZCuCR;
      string tTLyHJHQpf;
      string etKGNXrFHV;
      if(IehLKRZziX == OylUSVybZr){zCSFhBnJGZ = true;}
      else if(OylUSVybZr == IehLKRZziX){IdZeFBspFG = true;}
      if(dJakbPaiyp == nRHELJCjUh){keyaJdOhKK = true;}
      else if(nRHELJCjUh == dJakbPaiyp){VOFCnHzAtU = true;}
      if(gFhkXtbylh == yaXlbOXXuH){GtbEbUnSwK = true;}
      else if(yaXlbOXXuH == gFhkXtbylh){lyBwAqfMLp = true;}
      if(rejiaXYumw == XaGpTFtDKL){hxnfRqAGQF = true;}
      else if(XaGpTFtDKL == rejiaXYumw){XVoDTtepHA = true;}
      if(eKpDxopuYJ == yXXbiKTDLx){UxJPtzwixi = true;}
      else if(yXXbiKTDLx == eKpDxopuYJ){eMlJqCfZPk = true;}
      if(AtekODwwmP == ANSpAnaAsD){JJtwPFaOdM = true;}
      else if(ANSpAnaAsD == AtekODwwmP){AjUBUKcdeN = true;}
      if(pbMBfyZrJD == yafSUNKRjG){MUMurnpRIR = true;}
      else if(yafSUNKRjG == pbMBfyZrJD){UfdPhzYChs = true;}
      if(qewCKVOeni == OzZJiZCuCR){cIQEpIjMJb = true;}
      if(DfYcgxAyUX == tTLyHJHQpf){YEVMBXCrQM = true;}
      if(bbHXGDynXy == etKGNXrFHV){QkbDszjOWG = true;}
      while(OzZJiZCuCR == qewCKVOeni){cIsspZLqFx = true;}
      while(tTLyHJHQpf == tTLyHJHQpf){LGxapnBmiJ = true;}
      while(etKGNXrFHV == etKGNXrFHV){RALsfyhWaq = true;}
      if(zCSFhBnJGZ == true){zCSFhBnJGZ = false;}
      if(keyaJdOhKK == true){keyaJdOhKK = false;}
      if(GtbEbUnSwK == true){GtbEbUnSwK = false;}
      if(hxnfRqAGQF == true){hxnfRqAGQF = false;}
      if(UxJPtzwixi == true){UxJPtzwixi = false;}
      if(JJtwPFaOdM == true){JJtwPFaOdM = false;}
      if(MUMurnpRIR == true){MUMurnpRIR = false;}
      if(cIQEpIjMJb == true){cIQEpIjMJb = false;}
      if(YEVMBXCrQM == true){YEVMBXCrQM = false;}
      if(QkbDszjOWG == true){QkbDszjOWG = false;}
      if(IdZeFBspFG == true){IdZeFBspFG = false;}
      if(VOFCnHzAtU == true){VOFCnHzAtU = false;}
      if(lyBwAqfMLp == true){lyBwAqfMLp = false;}
      if(XVoDTtepHA == true){XVoDTtepHA = false;}
      if(eMlJqCfZPk == true){eMlJqCfZPk = false;}
      if(AjUBUKcdeN == true){AjUBUKcdeN = false;}
      if(UfdPhzYChs == true){UfdPhzYChs = false;}
      if(cIsspZLqFx == true){cIsspZLqFx = false;}
      if(LGxapnBmiJ == true){LGxapnBmiJ = false;}
      if(RALsfyhWaq == true){RALsfyhWaq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNUFIJRWKK
{ 
  void izmIteGGWJ()
  { 
      bool zBoMFCJjea = false;
      bool JqOpLFSwFQ = false;
      bool KSLCMCEkpA = false;
      bool OddrQfDuSV = false;
      bool hnFDNOgZHz = false;
      bool MeGpqgolzC = false;
      bool xYsdMeMWYe = false;
      bool BWdihVMIny = false;
      bool UecpmjXnAj = false;
      bool pQuPXJtbqh = false;
      bool BKBcxoAWHU = false;
      bool UgyBhSuCqc = false;
      bool HYVnnkbNKY = false;
      bool bkRGwJdAry = false;
      bool iAffPJSshF = false;
      bool NrkNaboMnM = false;
      bool NmLhsiPqFX = false;
      bool ouJrtGsoYe = false;
      bool ShfFLiADeU = false;
      bool URLfkunxmf = false;
      string rbcfJamutu;
      string NByrKVjwoV;
      string HWmoeEeuAk;
      string seFXqoSOgE;
      string HXnxmbzmwV;
      string bajnwUnnBE;
      string uqtIChwZAV;
      string DVOkNiipBC;
      string FqydJRuQbW;
      string BdNcIQdeuE;
      string eYlaRGLyaN;
      string lylyyDrPzk;
      string meydTYHlcx;
      string FDtwXfEWLD;
      string FwoNjDqPdE;
      string XNfJRzaIHs;
      string yZUdHhDpZR;
      string zUDueppjsQ;
      string grHXYqXjeX;
      string FwPSFebLGB;
      if(rbcfJamutu == eYlaRGLyaN){zBoMFCJjea = true;}
      else if(eYlaRGLyaN == rbcfJamutu){BKBcxoAWHU = true;}
      if(NByrKVjwoV == lylyyDrPzk){JqOpLFSwFQ = true;}
      else if(lylyyDrPzk == NByrKVjwoV){UgyBhSuCqc = true;}
      if(HWmoeEeuAk == meydTYHlcx){KSLCMCEkpA = true;}
      else if(meydTYHlcx == HWmoeEeuAk){HYVnnkbNKY = true;}
      if(seFXqoSOgE == FDtwXfEWLD){OddrQfDuSV = true;}
      else if(FDtwXfEWLD == seFXqoSOgE){bkRGwJdAry = true;}
      if(HXnxmbzmwV == FwoNjDqPdE){hnFDNOgZHz = true;}
      else if(FwoNjDqPdE == HXnxmbzmwV){iAffPJSshF = true;}
      if(bajnwUnnBE == XNfJRzaIHs){MeGpqgolzC = true;}
      else if(XNfJRzaIHs == bajnwUnnBE){NrkNaboMnM = true;}
      if(uqtIChwZAV == yZUdHhDpZR){xYsdMeMWYe = true;}
      else if(yZUdHhDpZR == uqtIChwZAV){NmLhsiPqFX = true;}
      if(DVOkNiipBC == zUDueppjsQ){BWdihVMIny = true;}
      if(FqydJRuQbW == grHXYqXjeX){UecpmjXnAj = true;}
      if(BdNcIQdeuE == FwPSFebLGB){pQuPXJtbqh = true;}
      while(zUDueppjsQ == DVOkNiipBC){ouJrtGsoYe = true;}
      while(grHXYqXjeX == grHXYqXjeX){ShfFLiADeU = true;}
      while(FwPSFebLGB == FwPSFebLGB){URLfkunxmf = true;}
      if(zBoMFCJjea == true){zBoMFCJjea = false;}
      if(JqOpLFSwFQ == true){JqOpLFSwFQ = false;}
      if(KSLCMCEkpA == true){KSLCMCEkpA = false;}
      if(OddrQfDuSV == true){OddrQfDuSV = false;}
      if(hnFDNOgZHz == true){hnFDNOgZHz = false;}
      if(MeGpqgolzC == true){MeGpqgolzC = false;}
      if(xYsdMeMWYe == true){xYsdMeMWYe = false;}
      if(BWdihVMIny == true){BWdihVMIny = false;}
      if(UecpmjXnAj == true){UecpmjXnAj = false;}
      if(pQuPXJtbqh == true){pQuPXJtbqh = false;}
      if(BKBcxoAWHU == true){BKBcxoAWHU = false;}
      if(UgyBhSuCqc == true){UgyBhSuCqc = false;}
      if(HYVnnkbNKY == true){HYVnnkbNKY = false;}
      if(bkRGwJdAry == true){bkRGwJdAry = false;}
      if(iAffPJSshF == true){iAffPJSshF = false;}
      if(NrkNaboMnM == true){NrkNaboMnM = false;}
      if(NmLhsiPqFX == true){NmLhsiPqFX = false;}
      if(ouJrtGsoYe == true){ouJrtGsoYe = false;}
      if(ShfFLiADeU == true){ShfFLiADeU = false;}
      if(URLfkunxmf == true){URLfkunxmf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRWAZVTWAW
{ 
  void GVWVXWBNVh()
  { 
      bool iisiXtpajz = false;
      bool CkVoqJrZle = false;
      bool BuiZIiGDPs = false;
      bool lQCRAShDcD = false;
      bool CVngNWclhR = false;
      bool xNkZHmzTao = false;
      bool nmLqMkiDoY = false;
      bool anxhbeHCLk = false;
      bool FTVxuYfcKM = false;
      bool TNcnPPJxTb = false;
      bool nZwIqIPCyb = false;
      bool fxHoiTROum = false;
      bool FGscFMLJRM = false;
      bool UJhjwfWMFm = false;
      bool IcdhfWGmEu = false;
      bool xuBgVhfTDd = false;
      bool wGjkHWOXsD = false;
      bool wFIIecbKxh = false;
      bool GYEWPZHBNN = false;
      bool zDIapCrsaJ = false;
      string WCHfOGYeGC;
      string xlZcxZEfUw;
      string xVaSsLGcXs;
      string MNVZXsHPWh;
      string IViLyBdhQL;
      string jaSBLBbolC;
      string AuHMojPzEE;
      string SnImnalOTq;
      string hXMLIltUNW;
      string QSdUgMOVWO;
      string kedLswRfMk;
      string OMUuTbiuDD;
      string oukhmzKmFb;
      string MPrFFCtASM;
      string TOHcHDyiAE;
      string cSSTZpsuYs;
      string keakXyUPoR;
      string ghcqiZnHZi;
      string BblAysxYfP;
      string IybZbonWFI;
      if(WCHfOGYeGC == kedLswRfMk){iisiXtpajz = true;}
      else if(kedLswRfMk == WCHfOGYeGC){nZwIqIPCyb = true;}
      if(xlZcxZEfUw == OMUuTbiuDD){CkVoqJrZle = true;}
      else if(OMUuTbiuDD == xlZcxZEfUw){fxHoiTROum = true;}
      if(xVaSsLGcXs == oukhmzKmFb){BuiZIiGDPs = true;}
      else if(oukhmzKmFb == xVaSsLGcXs){FGscFMLJRM = true;}
      if(MNVZXsHPWh == MPrFFCtASM){lQCRAShDcD = true;}
      else if(MPrFFCtASM == MNVZXsHPWh){UJhjwfWMFm = true;}
      if(IViLyBdhQL == TOHcHDyiAE){CVngNWclhR = true;}
      else if(TOHcHDyiAE == IViLyBdhQL){IcdhfWGmEu = true;}
      if(jaSBLBbolC == cSSTZpsuYs){xNkZHmzTao = true;}
      else if(cSSTZpsuYs == jaSBLBbolC){xuBgVhfTDd = true;}
      if(AuHMojPzEE == keakXyUPoR){nmLqMkiDoY = true;}
      else if(keakXyUPoR == AuHMojPzEE){wGjkHWOXsD = true;}
      if(SnImnalOTq == ghcqiZnHZi){anxhbeHCLk = true;}
      if(hXMLIltUNW == BblAysxYfP){FTVxuYfcKM = true;}
      if(QSdUgMOVWO == IybZbonWFI){TNcnPPJxTb = true;}
      while(ghcqiZnHZi == SnImnalOTq){wFIIecbKxh = true;}
      while(BblAysxYfP == BblAysxYfP){GYEWPZHBNN = true;}
      while(IybZbonWFI == IybZbonWFI){zDIapCrsaJ = true;}
      if(iisiXtpajz == true){iisiXtpajz = false;}
      if(CkVoqJrZle == true){CkVoqJrZle = false;}
      if(BuiZIiGDPs == true){BuiZIiGDPs = false;}
      if(lQCRAShDcD == true){lQCRAShDcD = false;}
      if(CVngNWclhR == true){CVngNWclhR = false;}
      if(xNkZHmzTao == true){xNkZHmzTao = false;}
      if(nmLqMkiDoY == true){nmLqMkiDoY = false;}
      if(anxhbeHCLk == true){anxhbeHCLk = false;}
      if(FTVxuYfcKM == true){FTVxuYfcKM = false;}
      if(TNcnPPJxTb == true){TNcnPPJxTb = false;}
      if(nZwIqIPCyb == true){nZwIqIPCyb = false;}
      if(fxHoiTROum == true){fxHoiTROum = false;}
      if(FGscFMLJRM == true){FGscFMLJRM = false;}
      if(UJhjwfWMFm == true){UJhjwfWMFm = false;}
      if(IcdhfWGmEu == true){IcdhfWGmEu = false;}
      if(xuBgVhfTDd == true){xuBgVhfTDd = false;}
      if(wGjkHWOXsD == true){wGjkHWOXsD = false;}
      if(wFIIecbKxh == true){wFIIecbKxh = false;}
      if(GYEWPZHBNN == true){GYEWPZHBNN = false;}
      if(zDIapCrsaJ == true){zDIapCrsaJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VXHCMSLAFX
{ 
  void UWSPiuQbPF()
  { 
      bool SqfJGMMOzg = false;
      bool pRlZitrStx = false;
      bool IjyrwWLRlJ = false;
      bool cdtEITQLOh = false;
      bool LifmLrBbOr = false;
      bool DAgSsirnMj = false;
      bool AtbpDMXgRP = false;
      bool cfDMkZDLfE = false;
      bool VjCtFcwaLY = false;
      bool acyegQGoiz = false;
      bool UUKzOWwUgS = false;
      bool egHINQrgka = false;
      bool PwUroAhYeU = false;
      bool SNcgiBYDfh = false;
      bool fassstUoQQ = false;
      bool YYEHiXzRJO = false;
      bool oXpMzQDaYM = false;
      bool rnBDunDbzt = false;
      bool esHOwtJVxL = false;
      bool BGsRrHkgsb = false;
      string buFzptCcuU;
      string yCXleScIhr;
      string pJqGlmPTNB;
      string zIDTUlYiNm;
      string bBinYSbaEH;
      string JsXaLSDyND;
      string ehOsUpzERs;
      string ttuuPnZDgS;
      string KoPFrGkbIB;
      string iZVJHsloSi;
      string TXILNPybLW;
      string rAQtspSIBN;
      string FWuPKTXkmV;
      string BkjyzlfDrc;
      string IIQkIhJaQR;
      string admEdwbrBs;
      string qMooUGPSuG;
      string KOQYFwFKGb;
      string KxUVtXyfTC;
      string KmCylwTbPC;
      if(buFzptCcuU == TXILNPybLW){SqfJGMMOzg = true;}
      else if(TXILNPybLW == buFzptCcuU){UUKzOWwUgS = true;}
      if(yCXleScIhr == rAQtspSIBN){pRlZitrStx = true;}
      else if(rAQtspSIBN == yCXleScIhr){egHINQrgka = true;}
      if(pJqGlmPTNB == FWuPKTXkmV){IjyrwWLRlJ = true;}
      else if(FWuPKTXkmV == pJqGlmPTNB){PwUroAhYeU = true;}
      if(zIDTUlYiNm == BkjyzlfDrc){cdtEITQLOh = true;}
      else if(BkjyzlfDrc == zIDTUlYiNm){SNcgiBYDfh = true;}
      if(bBinYSbaEH == IIQkIhJaQR){LifmLrBbOr = true;}
      else if(IIQkIhJaQR == bBinYSbaEH){fassstUoQQ = true;}
      if(JsXaLSDyND == admEdwbrBs){DAgSsirnMj = true;}
      else if(admEdwbrBs == JsXaLSDyND){YYEHiXzRJO = true;}
      if(ehOsUpzERs == qMooUGPSuG){AtbpDMXgRP = true;}
      else if(qMooUGPSuG == ehOsUpzERs){oXpMzQDaYM = true;}
      if(ttuuPnZDgS == KOQYFwFKGb){cfDMkZDLfE = true;}
      if(KoPFrGkbIB == KxUVtXyfTC){VjCtFcwaLY = true;}
      if(iZVJHsloSi == KmCylwTbPC){acyegQGoiz = true;}
      while(KOQYFwFKGb == ttuuPnZDgS){rnBDunDbzt = true;}
      while(KxUVtXyfTC == KxUVtXyfTC){esHOwtJVxL = true;}
      while(KmCylwTbPC == KmCylwTbPC){BGsRrHkgsb = true;}
      if(SqfJGMMOzg == true){SqfJGMMOzg = false;}
      if(pRlZitrStx == true){pRlZitrStx = false;}
      if(IjyrwWLRlJ == true){IjyrwWLRlJ = false;}
      if(cdtEITQLOh == true){cdtEITQLOh = false;}
      if(LifmLrBbOr == true){LifmLrBbOr = false;}
      if(DAgSsirnMj == true){DAgSsirnMj = false;}
      if(AtbpDMXgRP == true){AtbpDMXgRP = false;}
      if(cfDMkZDLfE == true){cfDMkZDLfE = false;}
      if(VjCtFcwaLY == true){VjCtFcwaLY = false;}
      if(acyegQGoiz == true){acyegQGoiz = false;}
      if(UUKzOWwUgS == true){UUKzOWwUgS = false;}
      if(egHINQrgka == true){egHINQrgka = false;}
      if(PwUroAhYeU == true){PwUroAhYeU = false;}
      if(SNcgiBYDfh == true){SNcgiBYDfh = false;}
      if(fassstUoQQ == true){fassstUoQQ = false;}
      if(YYEHiXzRJO == true){YYEHiXzRJO = false;}
      if(oXpMzQDaYM == true){oXpMzQDaYM = false;}
      if(rnBDunDbzt == true){rnBDunDbzt = false;}
      if(esHOwtJVxL == true){esHOwtJVxL = false;}
      if(BGsRrHkgsb == true){BGsRrHkgsb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VOKXRILMLT
{ 
  void gYSgSVZXyT()
  { 
      bool pITkHblmwM = false;
      bool JZTpeCiofU = false;
      bool yhGZNXpxpG = false;
      bool OalRmpmDPc = false;
      bool fFKPwLjbus = false;
      bool pDkcZIBsWi = false;
      bool lnxpyhnBDo = false;
      bool OfZDorXqcC = false;
      bool nNCwPKpIrd = false;
      bool ntffpqITRO = false;
      bool WhXGeKcgng = false;
      bool kKQUuYlBZn = false;
      bool reJYAUztNx = false;
      bool jDYOeGpwRF = false;
      bool gIUKscdKjR = false;
      bool FHscVqXyFJ = false;
      bool KiTpwgkBpo = false;
      bool ioiUGjKyfX = false;
      bool pnJwqcJwrm = false;
      bool hqqHtxndNL = false;
      string CcMPByVRnK;
      string CBEBhKVFVP;
      string CJOyYedJQc;
      string pRbgTTpcCr;
      string smaZRUDzrp;
      string IyuyesOOqW;
      string TMBLTjYXhO;
      string TrDcWOhofD;
      string beQZUqWdCa;
      string FbleXglPFh;
      string weQdVPuRaQ;
      string KYhmuoubpc;
      string MuUGJrGXFp;
      string cSjyHwNmDE;
      string wFCkQfszjh;
      string kKYcUBJKTd;
      string JWMkmrojfz;
      string aIXkfHrjpc;
      string zGnWESsHcF;
      string lDSZuZsQxX;
      if(CcMPByVRnK == weQdVPuRaQ){pITkHblmwM = true;}
      else if(weQdVPuRaQ == CcMPByVRnK){WhXGeKcgng = true;}
      if(CBEBhKVFVP == KYhmuoubpc){JZTpeCiofU = true;}
      else if(KYhmuoubpc == CBEBhKVFVP){kKQUuYlBZn = true;}
      if(CJOyYedJQc == MuUGJrGXFp){yhGZNXpxpG = true;}
      else if(MuUGJrGXFp == CJOyYedJQc){reJYAUztNx = true;}
      if(pRbgTTpcCr == cSjyHwNmDE){OalRmpmDPc = true;}
      else if(cSjyHwNmDE == pRbgTTpcCr){jDYOeGpwRF = true;}
      if(smaZRUDzrp == wFCkQfszjh){fFKPwLjbus = true;}
      else if(wFCkQfszjh == smaZRUDzrp){gIUKscdKjR = true;}
      if(IyuyesOOqW == kKYcUBJKTd){pDkcZIBsWi = true;}
      else if(kKYcUBJKTd == IyuyesOOqW){FHscVqXyFJ = true;}
      if(TMBLTjYXhO == JWMkmrojfz){lnxpyhnBDo = true;}
      else if(JWMkmrojfz == TMBLTjYXhO){KiTpwgkBpo = true;}
      if(TrDcWOhofD == aIXkfHrjpc){OfZDorXqcC = true;}
      if(beQZUqWdCa == zGnWESsHcF){nNCwPKpIrd = true;}
      if(FbleXglPFh == lDSZuZsQxX){ntffpqITRO = true;}
      while(aIXkfHrjpc == TrDcWOhofD){ioiUGjKyfX = true;}
      while(zGnWESsHcF == zGnWESsHcF){pnJwqcJwrm = true;}
      while(lDSZuZsQxX == lDSZuZsQxX){hqqHtxndNL = true;}
      if(pITkHblmwM == true){pITkHblmwM = false;}
      if(JZTpeCiofU == true){JZTpeCiofU = false;}
      if(yhGZNXpxpG == true){yhGZNXpxpG = false;}
      if(OalRmpmDPc == true){OalRmpmDPc = false;}
      if(fFKPwLjbus == true){fFKPwLjbus = false;}
      if(pDkcZIBsWi == true){pDkcZIBsWi = false;}
      if(lnxpyhnBDo == true){lnxpyhnBDo = false;}
      if(OfZDorXqcC == true){OfZDorXqcC = false;}
      if(nNCwPKpIrd == true){nNCwPKpIrd = false;}
      if(ntffpqITRO == true){ntffpqITRO = false;}
      if(WhXGeKcgng == true){WhXGeKcgng = false;}
      if(kKQUuYlBZn == true){kKQUuYlBZn = false;}
      if(reJYAUztNx == true){reJYAUztNx = false;}
      if(jDYOeGpwRF == true){jDYOeGpwRF = false;}
      if(gIUKscdKjR == true){gIUKscdKjR = false;}
      if(FHscVqXyFJ == true){FHscVqXyFJ = false;}
      if(KiTpwgkBpo == true){KiTpwgkBpo = false;}
      if(ioiUGjKyfX == true){ioiUGjKyfX = false;}
      if(pnJwqcJwrm == true){pnJwqcJwrm = false;}
      if(hqqHtxndNL == true){hqqHtxndNL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUJYOHJTNH
{ 
  void bcLnaxVHwg()
  { 
      bool tlfjGhVZdr = false;
      bool QQWmBkyAGB = false;
      bool weSWYEwqtg = false;
      bool oAOaxJfoEk = false;
      bool bJsnMQCHkW = false;
      bool qFSANOTJKB = false;
      bool keexCPBwor = false;
      bool EJwVZlldKI = false;
      bool BnGWojgONi = false;
      bool oWdCzxdukw = false;
      bool OGSrRgIxaa = false;
      bool coyCzxXIHS = false;
      bool hmhGCgftVb = false;
      bool HqsOtuVNEI = false;
      bool ajmlGAYbCC = false;
      bool YVmRNbYLpj = false;
      bool BOazSkujHE = false;
      bool aKDzrxzuAB = false;
      bool IDrTClDaAR = false;
      bool WKXTGMJnTU = false;
      string eUKChitFrI;
      string SYleVjwfTw;
      string CpjRysGedj;
      string UccOWIyDCZ;
      string IpsZsNaqhP;
      string kRCHLoksDo;
      string bPbHmouXIM;
      string lsctmMxJYk;
      string SPwNyCaUCh;
      string XEzMxsNklD;
      string RDhUdrnIUz;
      string raTSVLSNJk;
      string OaUaogsQws;
      string yLXUSPgajG;
      string NSADpxkfqk;
      string ZAbAophHfx;
      string yXLaAfCyzG;
      string erdCWwZRkr;
      string uMYKTyiWfc;
      string gZulIpGZCJ;
      if(eUKChitFrI == RDhUdrnIUz){tlfjGhVZdr = true;}
      else if(RDhUdrnIUz == eUKChitFrI){OGSrRgIxaa = true;}
      if(SYleVjwfTw == raTSVLSNJk){QQWmBkyAGB = true;}
      else if(raTSVLSNJk == SYleVjwfTw){coyCzxXIHS = true;}
      if(CpjRysGedj == OaUaogsQws){weSWYEwqtg = true;}
      else if(OaUaogsQws == CpjRysGedj){hmhGCgftVb = true;}
      if(UccOWIyDCZ == yLXUSPgajG){oAOaxJfoEk = true;}
      else if(yLXUSPgajG == UccOWIyDCZ){HqsOtuVNEI = true;}
      if(IpsZsNaqhP == NSADpxkfqk){bJsnMQCHkW = true;}
      else if(NSADpxkfqk == IpsZsNaqhP){ajmlGAYbCC = true;}
      if(kRCHLoksDo == ZAbAophHfx){qFSANOTJKB = true;}
      else if(ZAbAophHfx == kRCHLoksDo){YVmRNbYLpj = true;}
      if(bPbHmouXIM == yXLaAfCyzG){keexCPBwor = true;}
      else if(yXLaAfCyzG == bPbHmouXIM){BOazSkujHE = true;}
      if(lsctmMxJYk == erdCWwZRkr){EJwVZlldKI = true;}
      if(SPwNyCaUCh == uMYKTyiWfc){BnGWojgONi = true;}
      if(XEzMxsNklD == gZulIpGZCJ){oWdCzxdukw = true;}
      while(erdCWwZRkr == lsctmMxJYk){aKDzrxzuAB = true;}
      while(uMYKTyiWfc == uMYKTyiWfc){IDrTClDaAR = true;}
      while(gZulIpGZCJ == gZulIpGZCJ){WKXTGMJnTU = true;}
      if(tlfjGhVZdr == true){tlfjGhVZdr = false;}
      if(QQWmBkyAGB == true){QQWmBkyAGB = false;}
      if(weSWYEwqtg == true){weSWYEwqtg = false;}
      if(oAOaxJfoEk == true){oAOaxJfoEk = false;}
      if(bJsnMQCHkW == true){bJsnMQCHkW = false;}
      if(qFSANOTJKB == true){qFSANOTJKB = false;}
      if(keexCPBwor == true){keexCPBwor = false;}
      if(EJwVZlldKI == true){EJwVZlldKI = false;}
      if(BnGWojgONi == true){BnGWojgONi = false;}
      if(oWdCzxdukw == true){oWdCzxdukw = false;}
      if(OGSrRgIxaa == true){OGSrRgIxaa = false;}
      if(coyCzxXIHS == true){coyCzxXIHS = false;}
      if(hmhGCgftVb == true){hmhGCgftVb = false;}
      if(HqsOtuVNEI == true){HqsOtuVNEI = false;}
      if(ajmlGAYbCC == true){ajmlGAYbCC = false;}
      if(YVmRNbYLpj == true){YVmRNbYLpj = false;}
      if(BOazSkujHE == true){BOazSkujHE = false;}
      if(aKDzrxzuAB == true){aKDzrxzuAB = false;}
      if(IDrTClDaAR == true){IDrTClDaAR = false;}
      if(WKXTGMJnTU == true){WKXTGMJnTU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFXHYOQKTU
{ 
  void qAwVbCJAWz()
  { 
      bool mZJMNxIXhS = false;
      bool MjomzhZxdz = false;
      bool ORYUxCmjeW = false;
      bool zMcaguhgjC = false;
      bool ubQZRybxCa = false;
      bool sLXGAVBnOL = false;
      bool KXsKSAGNFE = false;
      bool zrMaEmBzDz = false;
      bool ZohDdnoVaL = false;
      bool ttRYrXiFGR = false;
      bool qNrybAywCN = false;
      bool TBkOkVooge = false;
      bool KjmsJEanig = false;
      bool DwrkHMwjbd = false;
      bool orTNqrJCmV = false;
      bool htXbGHZynW = false;
      bool ZJNVJXJzHX = false;
      bool YFMDoRPZCR = false;
      bool uXAMzJXPdA = false;
      bool lyuEEeeyET = false;
      string VqbSZoHuga;
      string KSNyIRUhjf;
      string RDkhfdaTgC;
      string IXoLWtYDVK;
      string YQLRZBPbtb;
      string sRxHBRFtlw;
      string NnNeSlcCaN;
      string sRLZGArTHe;
      string OyYFJqahJF;
      string oeQZwkCgym;
      string XMBgiaFXAA;
      string ZklHhPPIVa;
      string LusVYNBlcV;
      string xKVUHBwrWh;
      string lCgJeDrJrf;
      string UtKWbbTfHU;
      string ZSteCOPRAf;
      string SWlmoIOipU;
      string VqsxADzyre;
      string hQjBISIBGP;
      if(VqbSZoHuga == XMBgiaFXAA){mZJMNxIXhS = true;}
      else if(XMBgiaFXAA == VqbSZoHuga){qNrybAywCN = true;}
      if(KSNyIRUhjf == ZklHhPPIVa){MjomzhZxdz = true;}
      else if(ZklHhPPIVa == KSNyIRUhjf){TBkOkVooge = true;}
      if(RDkhfdaTgC == LusVYNBlcV){ORYUxCmjeW = true;}
      else if(LusVYNBlcV == RDkhfdaTgC){KjmsJEanig = true;}
      if(IXoLWtYDVK == xKVUHBwrWh){zMcaguhgjC = true;}
      else if(xKVUHBwrWh == IXoLWtYDVK){DwrkHMwjbd = true;}
      if(YQLRZBPbtb == lCgJeDrJrf){ubQZRybxCa = true;}
      else if(lCgJeDrJrf == YQLRZBPbtb){orTNqrJCmV = true;}
      if(sRxHBRFtlw == UtKWbbTfHU){sLXGAVBnOL = true;}
      else if(UtKWbbTfHU == sRxHBRFtlw){htXbGHZynW = true;}
      if(NnNeSlcCaN == ZSteCOPRAf){KXsKSAGNFE = true;}
      else if(ZSteCOPRAf == NnNeSlcCaN){ZJNVJXJzHX = true;}
      if(sRLZGArTHe == SWlmoIOipU){zrMaEmBzDz = true;}
      if(OyYFJqahJF == VqsxADzyre){ZohDdnoVaL = true;}
      if(oeQZwkCgym == hQjBISIBGP){ttRYrXiFGR = true;}
      while(SWlmoIOipU == sRLZGArTHe){YFMDoRPZCR = true;}
      while(VqsxADzyre == VqsxADzyre){uXAMzJXPdA = true;}
      while(hQjBISIBGP == hQjBISIBGP){lyuEEeeyET = true;}
      if(mZJMNxIXhS == true){mZJMNxIXhS = false;}
      if(MjomzhZxdz == true){MjomzhZxdz = false;}
      if(ORYUxCmjeW == true){ORYUxCmjeW = false;}
      if(zMcaguhgjC == true){zMcaguhgjC = false;}
      if(ubQZRybxCa == true){ubQZRybxCa = false;}
      if(sLXGAVBnOL == true){sLXGAVBnOL = false;}
      if(KXsKSAGNFE == true){KXsKSAGNFE = false;}
      if(zrMaEmBzDz == true){zrMaEmBzDz = false;}
      if(ZohDdnoVaL == true){ZohDdnoVaL = false;}
      if(ttRYrXiFGR == true){ttRYrXiFGR = false;}
      if(qNrybAywCN == true){qNrybAywCN = false;}
      if(TBkOkVooge == true){TBkOkVooge = false;}
      if(KjmsJEanig == true){KjmsJEanig = false;}
      if(DwrkHMwjbd == true){DwrkHMwjbd = false;}
      if(orTNqrJCmV == true){orTNqrJCmV = false;}
      if(htXbGHZynW == true){htXbGHZynW = false;}
      if(ZJNVJXJzHX == true){ZJNVJXJzHX = false;}
      if(YFMDoRPZCR == true){YFMDoRPZCR = false;}
      if(uXAMzJXPdA == true){uXAMzJXPdA = false;}
      if(lyuEEeeyET == true){lyuEEeeyET = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLAJTKLOCE
{ 
  void jufKwxLBBk()
  { 
      bool VxKbPNFJgZ = false;
      bool tHnJbqrppC = false;
      bool eiUmuInCyg = false;
      bool FOFTjSyKzH = false;
      bool HpToBNnjLe = false;
      bool FuTiIlbWgG = false;
      bool YDLzUfCTZI = false;
      bool rgqhtnOelg = false;
      bool TEqSbJtWLx = false;
      bool pbdriEdUUV = false;
      bool LTKCmYEknT = false;
      bool XwjzlULsXK = false;
      bool keIbSQDyzo = false;
      bool KtKQVAsneD = false;
      bool FJiqYsqeFO = false;
      bool skxJjgLhjV = false;
      bool UFlyJdkTcl = false;
      bool aWNUFbwQCY = false;
      bool YXsjwYwBfo = false;
      bool nKEJhzWjgu = false;
      string mhRIfbDsiL;
      string ufykxsLtqZ;
      string cgCUidVZFU;
      string NEkbhiwQgQ;
      string SDhToHPZol;
      string wXtkzGfwYB;
      string GcnOyqtVCO;
      string wtMZHYyhea;
      string OwjTXoJAbb;
      string DzqfKoPTUy;
      string MsWaoCLTdZ;
      string IxRxlJrTpI;
      string gtsaLxCfPR;
      string JdNgOVYJdV;
      string cpVCSFhssA;
      string wudMQSzwPq;
      string zeELQejjiQ;
      string kioTeqXqIF;
      string PImOVNzBPu;
      string VbtmVykJkn;
      if(mhRIfbDsiL == MsWaoCLTdZ){VxKbPNFJgZ = true;}
      else if(MsWaoCLTdZ == mhRIfbDsiL){LTKCmYEknT = true;}
      if(ufykxsLtqZ == IxRxlJrTpI){tHnJbqrppC = true;}
      else if(IxRxlJrTpI == ufykxsLtqZ){XwjzlULsXK = true;}
      if(cgCUidVZFU == gtsaLxCfPR){eiUmuInCyg = true;}
      else if(gtsaLxCfPR == cgCUidVZFU){keIbSQDyzo = true;}
      if(NEkbhiwQgQ == JdNgOVYJdV){FOFTjSyKzH = true;}
      else if(JdNgOVYJdV == NEkbhiwQgQ){KtKQVAsneD = true;}
      if(SDhToHPZol == cpVCSFhssA){HpToBNnjLe = true;}
      else if(cpVCSFhssA == SDhToHPZol){FJiqYsqeFO = true;}
      if(wXtkzGfwYB == wudMQSzwPq){FuTiIlbWgG = true;}
      else if(wudMQSzwPq == wXtkzGfwYB){skxJjgLhjV = true;}
      if(GcnOyqtVCO == zeELQejjiQ){YDLzUfCTZI = true;}
      else if(zeELQejjiQ == GcnOyqtVCO){UFlyJdkTcl = true;}
      if(wtMZHYyhea == kioTeqXqIF){rgqhtnOelg = true;}
      if(OwjTXoJAbb == PImOVNzBPu){TEqSbJtWLx = true;}
      if(DzqfKoPTUy == VbtmVykJkn){pbdriEdUUV = true;}
      while(kioTeqXqIF == wtMZHYyhea){aWNUFbwQCY = true;}
      while(PImOVNzBPu == PImOVNzBPu){YXsjwYwBfo = true;}
      while(VbtmVykJkn == VbtmVykJkn){nKEJhzWjgu = true;}
      if(VxKbPNFJgZ == true){VxKbPNFJgZ = false;}
      if(tHnJbqrppC == true){tHnJbqrppC = false;}
      if(eiUmuInCyg == true){eiUmuInCyg = false;}
      if(FOFTjSyKzH == true){FOFTjSyKzH = false;}
      if(HpToBNnjLe == true){HpToBNnjLe = false;}
      if(FuTiIlbWgG == true){FuTiIlbWgG = false;}
      if(YDLzUfCTZI == true){YDLzUfCTZI = false;}
      if(rgqhtnOelg == true){rgqhtnOelg = false;}
      if(TEqSbJtWLx == true){TEqSbJtWLx = false;}
      if(pbdriEdUUV == true){pbdriEdUUV = false;}
      if(LTKCmYEknT == true){LTKCmYEknT = false;}
      if(XwjzlULsXK == true){XwjzlULsXK = false;}
      if(keIbSQDyzo == true){keIbSQDyzo = false;}
      if(KtKQVAsneD == true){KtKQVAsneD = false;}
      if(FJiqYsqeFO == true){FJiqYsqeFO = false;}
      if(skxJjgLhjV == true){skxJjgLhjV = false;}
      if(UFlyJdkTcl == true){UFlyJdkTcl = false;}
      if(aWNUFbwQCY == true){aWNUFbwQCY = false;}
      if(YXsjwYwBfo == true){YXsjwYwBfo = false;}
      if(nKEJhzWjgu == true){nKEJhzWjgu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVMQUKXUQP
{ 
  void XMuqXKrZYu()
  { 
      bool lkcWNJhxBK = false;
      bool csHgUubglo = false;
      bool eztXXThlgX = false;
      bool dEUYBYdIgN = false;
      bool hPlGDgCShi = false;
      bool AExaHlqFzs = false;
      bool buPcgYXhfu = false;
      bool QTzXHONnTp = false;
      bool RPExWZHsRO = false;
      bool hYInllzJZe = false;
      bool ITllSgEYTr = false;
      bool YCkIbMqRFG = false;
      bool QeQQNqKLlU = false;
      bool PDOohxcRep = false;
      bool UhYZpenzLY = false;
      bool ugESNdDVYb = false;
      bool VrmycUnwad = false;
      bool jYmOlhFqZh = false;
      bool DLAMZhzwaE = false;
      bool tGsDUbuawU = false;
      string bMKskcPQEE;
      string AFTMgHKhrQ;
      string ipCLtufGTn;
      string XpFxdOzjLA;
      string EwRVOxHqBu;
      string QdJlglKzzo;
      string xIxPfKzWhS;
      string HZVqLmXfww;
      string nnEXXsfSPr;
      string EAkVCwyBoE;
      string xjJinqIRZt;
      string NdDDBJDZrm;
      string dgGpNHoAoP;
      string nVpqyDdVjg;
      string kOsVdZwhUs;
      string rYJCaQdTVf;
      string CHcJFqmLEx;
      string ehpLBPmkLn;
      string KGfuXPMnQg;
      string ZKADdckiQl;
      if(bMKskcPQEE == xjJinqIRZt){lkcWNJhxBK = true;}
      else if(xjJinqIRZt == bMKskcPQEE){ITllSgEYTr = true;}
      if(AFTMgHKhrQ == NdDDBJDZrm){csHgUubglo = true;}
      else if(NdDDBJDZrm == AFTMgHKhrQ){YCkIbMqRFG = true;}
      if(ipCLtufGTn == dgGpNHoAoP){eztXXThlgX = true;}
      else if(dgGpNHoAoP == ipCLtufGTn){QeQQNqKLlU = true;}
      if(XpFxdOzjLA == nVpqyDdVjg){dEUYBYdIgN = true;}
      else if(nVpqyDdVjg == XpFxdOzjLA){PDOohxcRep = true;}
      if(EwRVOxHqBu == kOsVdZwhUs){hPlGDgCShi = true;}
      else if(kOsVdZwhUs == EwRVOxHqBu){UhYZpenzLY = true;}
      if(QdJlglKzzo == rYJCaQdTVf){AExaHlqFzs = true;}
      else if(rYJCaQdTVf == QdJlglKzzo){ugESNdDVYb = true;}
      if(xIxPfKzWhS == CHcJFqmLEx){buPcgYXhfu = true;}
      else if(CHcJFqmLEx == xIxPfKzWhS){VrmycUnwad = true;}
      if(HZVqLmXfww == ehpLBPmkLn){QTzXHONnTp = true;}
      if(nnEXXsfSPr == KGfuXPMnQg){RPExWZHsRO = true;}
      if(EAkVCwyBoE == ZKADdckiQl){hYInllzJZe = true;}
      while(ehpLBPmkLn == HZVqLmXfww){jYmOlhFqZh = true;}
      while(KGfuXPMnQg == KGfuXPMnQg){DLAMZhzwaE = true;}
      while(ZKADdckiQl == ZKADdckiQl){tGsDUbuawU = true;}
      if(lkcWNJhxBK == true){lkcWNJhxBK = false;}
      if(csHgUubglo == true){csHgUubglo = false;}
      if(eztXXThlgX == true){eztXXThlgX = false;}
      if(dEUYBYdIgN == true){dEUYBYdIgN = false;}
      if(hPlGDgCShi == true){hPlGDgCShi = false;}
      if(AExaHlqFzs == true){AExaHlqFzs = false;}
      if(buPcgYXhfu == true){buPcgYXhfu = false;}
      if(QTzXHONnTp == true){QTzXHONnTp = false;}
      if(RPExWZHsRO == true){RPExWZHsRO = false;}
      if(hYInllzJZe == true){hYInllzJZe = false;}
      if(ITllSgEYTr == true){ITllSgEYTr = false;}
      if(YCkIbMqRFG == true){YCkIbMqRFG = false;}
      if(QeQQNqKLlU == true){QeQQNqKLlU = false;}
      if(PDOohxcRep == true){PDOohxcRep = false;}
      if(UhYZpenzLY == true){UhYZpenzLY = false;}
      if(ugESNdDVYb == true){ugESNdDVYb = false;}
      if(VrmycUnwad == true){VrmycUnwad = false;}
      if(jYmOlhFqZh == true){jYmOlhFqZh = false;}
      if(DLAMZhzwaE == true){DLAMZhzwaE = false;}
      if(tGsDUbuawU == true){tGsDUbuawU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZZSIHFGXJ
{ 
  void bAeHKiiQQr()
  { 
      bool RubdhIbYWk = false;
      bool LCCiGhCBOu = false;
      bool pXkwZbqtIB = false;
      bool jEojSKtfDf = false;
      bool xOAxmPlaRE = false;
      bool NAXQptKeDG = false;
      bool RgQUBHNSQu = false;
      bool nWxhxaWmIK = false;
      bool oQcDmjfXsY = false;
      bool AObxOQyewf = false;
      bool BTKWQpCpSO = false;
      bool WXWsQBDNhR = false;
      bool aoYquYuzSg = false;
      bool cqpcIUFGmx = false;
      bool gpFdCbrigM = false;
      bool MkxeEMuSar = false;
      bool uCWlkegsju = false;
      bool uxakjkjtnS = false;
      bool gLSFUrtLXw = false;
      bool ZmetBeSSsW = false;
      string PudfUCIply;
      string pQakjkTbIK;
      string pHuwxwafRG;
      string gyoZITXEJy;
      string TXoApLmXiw;
      string OKitFHAgiX;
      string acYfRqbBcQ;
      string NPRJpSStFk;
      string ICxUqVPtTA;
      string SqUlXpyJiz;
      string jluRizsZDm;
      string nGaxPXfEnu;
      string bggbxWtfkz;
      string TJLGBWHekr;
      string cppfLMPXWz;
      string KtUnWCESUM;
      string EMnDTeuTur;
      string QBSuRlqBQk;
      string GWJloYnWiz;
      string SnKXmQBlLg;
      if(PudfUCIply == jluRizsZDm){RubdhIbYWk = true;}
      else if(jluRizsZDm == PudfUCIply){BTKWQpCpSO = true;}
      if(pQakjkTbIK == nGaxPXfEnu){LCCiGhCBOu = true;}
      else if(nGaxPXfEnu == pQakjkTbIK){WXWsQBDNhR = true;}
      if(pHuwxwafRG == bggbxWtfkz){pXkwZbqtIB = true;}
      else if(bggbxWtfkz == pHuwxwafRG){aoYquYuzSg = true;}
      if(gyoZITXEJy == TJLGBWHekr){jEojSKtfDf = true;}
      else if(TJLGBWHekr == gyoZITXEJy){cqpcIUFGmx = true;}
      if(TXoApLmXiw == cppfLMPXWz){xOAxmPlaRE = true;}
      else if(cppfLMPXWz == TXoApLmXiw){gpFdCbrigM = true;}
      if(OKitFHAgiX == KtUnWCESUM){NAXQptKeDG = true;}
      else if(KtUnWCESUM == OKitFHAgiX){MkxeEMuSar = true;}
      if(acYfRqbBcQ == EMnDTeuTur){RgQUBHNSQu = true;}
      else if(EMnDTeuTur == acYfRqbBcQ){uCWlkegsju = true;}
      if(NPRJpSStFk == QBSuRlqBQk){nWxhxaWmIK = true;}
      if(ICxUqVPtTA == GWJloYnWiz){oQcDmjfXsY = true;}
      if(SqUlXpyJiz == SnKXmQBlLg){AObxOQyewf = true;}
      while(QBSuRlqBQk == NPRJpSStFk){uxakjkjtnS = true;}
      while(GWJloYnWiz == GWJloYnWiz){gLSFUrtLXw = true;}
      while(SnKXmQBlLg == SnKXmQBlLg){ZmetBeSSsW = true;}
      if(RubdhIbYWk == true){RubdhIbYWk = false;}
      if(LCCiGhCBOu == true){LCCiGhCBOu = false;}
      if(pXkwZbqtIB == true){pXkwZbqtIB = false;}
      if(jEojSKtfDf == true){jEojSKtfDf = false;}
      if(xOAxmPlaRE == true){xOAxmPlaRE = false;}
      if(NAXQptKeDG == true){NAXQptKeDG = false;}
      if(RgQUBHNSQu == true){RgQUBHNSQu = false;}
      if(nWxhxaWmIK == true){nWxhxaWmIK = false;}
      if(oQcDmjfXsY == true){oQcDmjfXsY = false;}
      if(AObxOQyewf == true){AObxOQyewf = false;}
      if(BTKWQpCpSO == true){BTKWQpCpSO = false;}
      if(WXWsQBDNhR == true){WXWsQBDNhR = false;}
      if(aoYquYuzSg == true){aoYquYuzSg = false;}
      if(cqpcIUFGmx == true){cqpcIUFGmx = false;}
      if(gpFdCbrigM == true){gpFdCbrigM = false;}
      if(MkxeEMuSar == true){MkxeEMuSar = false;}
      if(uCWlkegsju == true){uCWlkegsju = false;}
      if(uxakjkjtnS == true){uxakjkjtnS = false;}
      if(gLSFUrtLXw == true){gLSFUrtLXw = false;}
      if(ZmetBeSSsW == true){ZmetBeSSsW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SGCHLEGCRI
{ 
  void AcXSmaCCQQ()
  { 
      bool wKiFpERDGZ = false;
      bool IdayrRYsMS = false;
      bool RIKRKNBIsM = false;
      bool UaNRqjxVGM = false;
      bool qSsJefCLig = false;
      bool ZpkmlnzRub = false;
      bool DJJsEhPJHI = false;
      bool TDlzbzPBmd = false;
      bool KpYLmeoaeC = false;
      bool jfaeJgIzFw = false;
      bool PsDaNWDkKm = false;
      bool YydRQMkxGY = false;
      bool rodEXnbHpu = false;
      bool pPwpNRlxyQ = false;
      bool bEPrdlBJNx = false;
      bool wKsfEaOzDZ = false;
      bool twuPwIBnDz = false;
      bool ZmzoxnZlak = false;
      bool lSsrzeWPlm = false;
      bool CmtYWeJzuU = false;
      string GUVVLyYEga;
      string NJuMixmncV;
      string TxtulcylBY;
      string KqOXEHkAjz;
      string MFtwceVQHy;
      string HHyWCIaZih;
      string zmCHQVtWIa;
      string LmDdIODySG;
      string GhdCRDsqVw;
      string gLQBzZClfG;
      string kzIgmTDUNn;
      string EbGbbRIzpM;
      string cCBMszVBdi;
      string LRSMVHZxPx;
      string AYdhqFEoZh;
      string QCwSdhxwmm;
      string yBpebmItFT;
      string qLjrLEYTUn;
      string ugbwRIVAin;
      string JdJbzziyFD;
      if(GUVVLyYEga == kzIgmTDUNn){wKiFpERDGZ = true;}
      else if(kzIgmTDUNn == GUVVLyYEga){PsDaNWDkKm = true;}
      if(NJuMixmncV == EbGbbRIzpM){IdayrRYsMS = true;}
      else if(EbGbbRIzpM == NJuMixmncV){YydRQMkxGY = true;}
      if(TxtulcylBY == cCBMszVBdi){RIKRKNBIsM = true;}
      else if(cCBMszVBdi == TxtulcylBY){rodEXnbHpu = true;}
      if(KqOXEHkAjz == LRSMVHZxPx){UaNRqjxVGM = true;}
      else if(LRSMVHZxPx == KqOXEHkAjz){pPwpNRlxyQ = true;}
      if(MFtwceVQHy == AYdhqFEoZh){qSsJefCLig = true;}
      else if(AYdhqFEoZh == MFtwceVQHy){bEPrdlBJNx = true;}
      if(HHyWCIaZih == QCwSdhxwmm){ZpkmlnzRub = true;}
      else if(QCwSdhxwmm == HHyWCIaZih){wKsfEaOzDZ = true;}
      if(zmCHQVtWIa == yBpebmItFT){DJJsEhPJHI = true;}
      else if(yBpebmItFT == zmCHQVtWIa){twuPwIBnDz = true;}
      if(LmDdIODySG == qLjrLEYTUn){TDlzbzPBmd = true;}
      if(GhdCRDsqVw == ugbwRIVAin){KpYLmeoaeC = true;}
      if(gLQBzZClfG == JdJbzziyFD){jfaeJgIzFw = true;}
      while(qLjrLEYTUn == LmDdIODySG){ZmzoxnZlak = true;}
      while(ugbwRIVAin == ugbwRIVAin){lSsrzeWPlm = true;}
      while(JdJbzziyFD == JdJbzziyFD){CmtYWeJzuU = true;}
      if(wKiFpERDGZ == true){wKiFpERDGZ = false;}
      if(IdayrRYsMS == true){IdayrRYsMS = false;}
      if(RIKRKNBIsM == true){RIKRKNBIsM = false;}
      if(UaNRqjxVGM == true){UaNRqjxVGM = false;}
      if(qSsJefCLig == true){qSsJefCLig = false;}
      if(ZpkmlnzRub == true){ZpkmlnzRub = false;}
      if(DJJsEhPJHI == true){DJJsEhPJHI = false;}
      if(TDlzbzPBmd == true){TDlzbzPBmd = false;}
      if(KpYLmeoaeC == true){KpYLmeoaeC = false;}
      if(jfaeJgIzFw == true){jfaeJgIzFw = false;}
      if(PsDaNWDkKm == true){PsDaNWDkKm = false;}
      if(YydRQMkxGY == true){YydRQMkxGY = false;}
      if(rodEXnbHpu == true){rodEXnbHpu = false;}
      if(pPwpNRlxyQ == true){pPwpNRlxyQ = false;}
      if(bEPrdlBJNx == true){bEPrdlBJNx = false;}
      if(wKsfEaOzDZ == true){wKsfEaOzDZ = false;}
      if(twuPwIBnDz == true){twuPwIBnDz = false;}
      if(ZmzoxnZlak == true){ZmzoxnZlak = false;}
      if(lSsrzeWPlm == true){lSsrzeWPlm = false;}
      if(CmtYWeJzuU == true){CmtYWeJzuU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VPOWVEVBUJ
{ 
  void qMgWXzbacs()
  { 
      bool nslkoQsdTD = false;
      bool eGFNpxxGrZ = false;
      bool pWuHsXipZl = false;
      bool QObMPwoRte = false;
      bool eckwbHDKHO = false;
      bool TbeADRxeqR = false;
      bool hCEhlPeryt = false;
      bool HfMMtNkzel = false;
      bool UXhLSojaJy = false;
      bool yKacxbYCJM = false;
      bool cKMNGnPRFp = false;
      bool fyzEwJUrPx = false;
      bool fDizuxFiPR = false;
      bool nioSJJLUEe = false;
      bool YRUSSALVfn = false;
      bool HfmMgYbMRJ = false;
      bool hfCmBxIgtl = false;
      bool xznkXNhPfu = false;
      bool kiDaKIuckk = false;
      bool hyCuwsPhRV = false;
      string fLkrrifcRC;
      string xoCtgjecks;
      string UEnGSEAESH;
      string XAWtkrRNLG;
      string ALwUZgtTac;
      string TMcBOaXeYn;
      string hbJKdxSIIn;
      string RRRerIISfl;
      string JfcpnKXUfK;
      string UmnWXXBlpc;
      string OlLlKCtxJF;
      string SEymeBzTWS;
      string ZxcyTectGU;
      string GVcCXWUqek;
      string QZLZqPoBrV;
      string YhPWDQJMRf;
      string YzqnyxbuOH;
      string fHokCzlCHD;
      string obCjwYGFzH;
      string NIYyLQiWat;
      if(fLkrrifcRC == OlLlKCtxJF){nslkoQsdTD = true;}
      else if(OlLlKCtxJF == fLkrrifcRC){cKMNGnPRFp = true;}
      if(xoCtgjecks == SEymeBzTWS){eGFNpxxGrZ = true;}
      else if(SEymeBzTWS == xoCtgjecks){fyzEwJUrPx = true;}
      if(UEnGSEAESH == ZxcyTectGU){pWuHsXipZl = true;}
      else if(ZxcyTectGU == UEnGSEAESH){fDizuxFiPR = true;}
      if(XAWtkrRNLG == GVcCXWUqek){QObMPwoRte = true;}
      else if(GVcCXWUqek == XAWtkrRNLG){nioSJJLUEe = true;}
      if(ALwUZgtTac == QZLZqPoBrV){eckwbHDKHO = true;}
      else if(QZLZqPoBrV == ALwUZgtTac){YRUSSALVfn = true;}
      if(TMcBOaXeYn == YhPWDQJMRf){TbeADRxeqR = true;}
      else if(YhPWDQJMRf == TMcBOaXeYn){HfmMgYbMRJ = true;}
      if(hbJKdxSIIn == YzqnyxbuOH){hCEhlPeryt = true;}
      else if(YzqnyxbuOH == hbJKdxSIIn){hfCmBxIgtl = true;}
      if(RRRerIISfl == fHokCzlCHD){HfMMtNkzel = true;}
      if(JfcpnKXUfK == obCjwYGFzH){UXhLSojaJy = true;}
      if(UmnWXXBlpc == NIYyLQiWat){yKacxbYCJM = true;}
      while(fHokCzlCHD == RRRerIISfl){xznkXNhPfu = true;}
      while(obCjwYGFzH == obCjwYGFzH){kiDaKIuckk = true;}
      while(NIYyLQiWat == NIYyLQiWat){hyCuwsPhRV = true;}
      if(nslkoQsdTD == true){nslkoQsdTD = false;}
      if(eGFNpxxGrZ == true){eGFNpxxGrZ = false;}
      if(pWuHsXipZl == true){pWuHsXipZl = false;}
      if(QObMPwoRte == true){QObMPwoRte = false;}
      if(eckwbHDKHO == true){eckwbHDKHO = false;}
      if(TbeADRxeqR == true){TbeADRxeqR = false;}
      if(hCEhlPeryt == true){hCEhlPeryt = false;}
      if(HfMMtNkzel == true){HfMMtNkzel = false;}
      if(UXhLSojaJy == true){UXhLSojaJy = false;}
      if(yKacxbYCJM == true){yKacxbYCJM = false;}
      if(cKMNGnPRFp == true){cKMNGnPRFp = false;}
      if(fyzEwJUrPx == true){fyzEwJUrPx = false;}
      if(fDizuxFiPR == true){fDizuxFiPR = false;}
      if(nioSJJLUEe == true){nioSJJLUEe = false;}
      if(YRUSSALVfn == true){YRUSSALVfn = false;}
      if(HfmMgYbMRJ == true){HfmMgYbMRJ = false;}
      if(hfCmBxIgtl == true){hfCmBxIgtl = false;}
      if(xznkXNhPfu == true){xznkXNhPfu = false;}
      if(kiDaKIuckk == true){kiDaKIuckk = false;}
      if(hyCuwsPhRV == true){hyCuwsPhRV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRLDBLFQYF
{ 
  void eulQJfEnTs()
  { 
      bool HCEWWOVFjq = false;
      bool fObkfgyoUi = false;
      bool AUJzdyWRzF = false;
      bool nMrPIHwDrs = false;
      bool QpeNqoSCol = false;
      bool sejLKmrErY = false;
      bool qDGdDTVLbX = false;
      bool kuwaSJpuIn = false;
      bool eUcNMIcgEV = false;
      bool OqKTBMjAKX = false;
      bool TGZRAxhIsB = false;
      bool xxwEsWarRt = false;
      bool qnHGJskbZF = false;
      bool ZojjUYuLMP = false;
      bool aTnDYRuFae = false;
      bool lqiQgezTHH = false;
      bool LFimbHMLiU = false;
      bool aPfBTWAEgq = false;
      bool yeBtThGTDo = false;
      bool YbDFEUkAaQ = false;
      string SEORDBBdyi;
      string TIlMmEYTOm;
      string jmbIICbyES;
      string zdOAEDrctd;
      string dgYgWpqswc;
      string GdUUTecGJA;
      string YCZfjpskHj;
      string MuYkICNtlR;
      string LiCaLUItgY;
      string alTtFaHsxg;
      string wFkLQKEjLQ;
      string RhUrnpAyTO;
      string gzDiJabeeh;
      string uUxFUGxpKB;
      string QYhPHrQbFP;
      string ZJYhzxBCCo;
      string hYEcVwjOWh;
      string rKmSxIQmaQ;
      string JAZPIlwPFW;
      string EtmUSrTEtL;
      if(SEORDBBdyi == wFkLQKEjLQ){HCEWWOVFjq = true;}
      else if(wFkLQKEjLQ == SEORDBBdyi){TGZRAxhIsB = true;}
      if(TIlMmEYTOm == RhUrnpAyTO){fObkfgyoUi = true;}
      else if(RhUrnpAyTO == TIlMmEYTOm){xxwEsWarRt = true;}
      if(jmbIICbyES == gzDiJabeeh){AUJzdyWRzF = true;}
      else if(gzDiJabeeh == jmbIICbyES){qnHGJskbZF = true;}
      if(zdOAEDrctd == uUxFUGxpKB){nMrPIHwDrs = true;}
      else if(uUxFUGxpKB == zdOAEDrctd){ZojjUYuLMP = true;}
      if(dgYgWpqswc == QYhPHrQbFP){QpeNqoSCol = true;}
      else if(QYhPHrQbFP == dgYgWpqswc){aTnDYRuFae = true;}
      if(GdUUTecGJA == ZJYhzxBCCo){sejLKmrErY = true;}
      else if(ZJYhzxBCCo == GdUUTecGJA){lqiQgezTHH = true;}
      if(YCZfjpskHj == hYEcVwjOWh){qDGdDTVLbX = true;}
      else if(hYEcVwjOWh == YCZfjpskHj){LFimbHMLiU = true;}
      if(MuYkICNtlR == rKmSxIQmaQ){kuwaSJpuIn = true;}
      if(LiCaLUItgY == JAZPIlwPFW){eUcNMIcgEV = true;}
      if(alTtFaHsxg == EtmUSrTEtL){OqKTBMjAKX = true;}
      while(rKmSxIQmaQ == MuYkICNtlR){aPfBTWAEgq = true;}
      while(JAZPIlwPFW == JAZPIlwPFW){yeBtThGTDo = true;}
      while(EtmUSrTEtL == EtmUSrTEtL){YbDFEUkAaQ = true;}
      if(HCEWWOVFjq == true){HCEWWOVFjq = false;}
      if(fObkfgyoUi == true){fObkfgyoUi = false;}
      if(AUJzdyWRzF == true){AUJzdyWRzF = false;}
      if(nMrPIHwDrs == true){nMrPIHwDrs = false;}
      if(QpeNqoSCol == true){QpeNqoSCol = false;}
      if(sejLKmrErY == true){sejLKmrErY = false;}
      if(qDGdDTVLbX == true){qDGdDTVLbX = false;}
      if(kuwaSJpuIn == true){kuwaSJpuIn = false;}
      if(eUcNMIcgEV == true){eUcNMIcgEV = false;}
      if(OqKTBMjAKX == true){OqKTBMjAKX = false;}
      if(TGZRAxhIsB == true){TGZRAxhIsB = false;}
      if(xxwEsWarRt == true){xxwEsWarRt = false;}
      if(qnHGJskbZF == true){qnHGJskbZF = false;}
      if(ZojjUYuLMP == true){ZojjUYuLMP = false;}
      if(aTnDYRuFae == true){aTnDYRuFae = false;}
      if(lqiQgezTHH == true){lqiQgezTHH = false;}
      if(LFimbHMLiU == true){LFimbHMLiU = false;}
      if(aPfBTWAEgq == true){aPfBTWAEgq = false;}
      if(yeBtThGTDo == true){yeBtThGTDo = false;}
      if(YbDFEUkAaQ == true){YbDFEUkAaQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMBYGXTLFC
{ 
  void oMdCKYhzJe()
  { 
      bool fyxAVgonyo = false;
      bool MamErgLXJT = false;
      bool iDlKimlzbJ = false;
      bool WFfhThHTsK = false;
      bool ekkaPDQbSQ = false;
      bool cCnPJcLlRh = false;
      bool upMoSHuFkJ = false;
      bool ZqeynyRKuf = false;
      bool VKgKfURQYp = false;
      bool VUCKOoXuII = false;
      bool ILpIqkWoaK = false;
      bool LAqkLkIBJx = false;
      bool odgumEoTiz = false;
      bool aWClWKTXTt = false;
      bool xcoOeVdRyd = false;
      bool fVlLSdetUl = false;
      bool wDFbinyEOB = false;
      bool QjhOzMoSQR = false;
      bool aXVFSEkpTr = false;
      bool eYDgytXMep = false;
      string RwaAHpGRID;
      string PbfgPxzhlR;
      string pIbXPOXqim;
      string tiiGGIJxun;
      string UcubaIHPft;
      string bFKqXITCjr;
      string RPiVJgsYZH;
      string nBmxxNMzxG;
      string GIKoKnYrix;
      string nGNCWFsZSt;
      string PipYFZRMsJ;
      string wUFdlJEsKU;
      string IApbTgnkar;
      string UmgCqXRlik;
      string VLyYBTBiPM;
      string AzOxlOrNEY;
      string lglBoImClO;
      string qSKZywCQaA;
      string fEUOqUYjQb;
      string eEgKyoZxjs;
      if(RwaAHpGRID == PipYFZRMsJ){fyxAVgonyo = true;}
      else if(PipYFZRMsJ == RwaAHpGRID){ILpIqkWoaK = true;}
      if(PbfgPxzhlR == wUFdlJEsKU){MamErgLXJT = true;}
      else if(wUFdlJEsKU == PbfgPxzhlR){LAqkLkIBJx = true;}
      if(pIbXPOXqim == IApbTgnkar){iDlKimlzbJ = true;}
      else if(IApbTgnkar == pIbXPOXqim){odgumEoTiz = true;}
      if(tiiGGIJxun == UmgCqXRlik){WFfhThHTsK = true;}
      else if(UmgCqXRlik == tiiGGIJxun){aWClWKTXTt = true;}
      if(UcubaIHPft == VLyYBTBiPM){ekkaPDQbSQ = true;}
      else if(VLyYBTBiPM == UcubaIHPft){xcoOeVdRyd = true;}
      if(bFKqXITCjr == AzOxlOrNEY){cCnPJcLlRh = true;}
      else if(AzOxlOrNEY == bFKqXITCjr){fVlLSdetUl = true;}
      if(RPiVJgsYZH == lglBoImClO){upMoSHuFkJ = true;}
      else if(lglBoImClO == RPiVJgsYZH){wDFbinyEOB = true;}
      if(nBmxxNMzxG == qSKZywCQaA){ZqeynyRKuf = true;}
      if(GIKoKnYrix == fEUOqUYjQb){VKgKfURQYp = true;}
      if(nGNCWFsZSt == eEgKyoZxjs){VUCKOoXuII = true;}
      while(qSKZywCQaA == nBmxxNMzxG){QjhOzMoSQR = true;}
      while(fEUOqUYjQb == fEUOqUYjQb){aXVFSEkpTr = true;}
      while(eEgKyoZxjs == eEgKyoZxjs){eYDgytXMep = true;}
      if(fyxAVgonyo == true){fyxAVgonyo = false;}
      if(MamErgLXJT == true){MamErgLXJT = false;}
      if(iDlKimlzbJ == true){iDlKimlzbJ = false;}
      if(WFfhThHTsK == true){WFfhThHTsK = false;}
      if(ekkaPDQbSQ == true){ekkaPDQbSQ = false;}
      if(cCnPJcLlRh == true){cCnPJcLlRh = false;}
      if(upMoSHuFkJ == true){upMoSHuFkJ = false;}
      if(ZqeynyRKuf == true){ZqeynyRKuf = false;}
      if(VKgKfURQYp == true){VKgKfURQYp = false;}
      if(VUCKOoXuII == true){VUCKOoXuII = false;}
      if(ILpIqkWoaK == true){ILpIqkWoaK = false;}
      if(LAqkLkIBJx == true){LAqkLkIBJx = false;}
      if(odgumEoTiz == true){odgumEoTiz = false;}
      if(aWClWKTXTt == true){aWClWKTXTt = false;}
      if(xcoOeVdRyd == true){xcoOeVdRyd = false;}
      if(fVlLSdetUl == true){fVlLSdetUl = false;}
      if(wDFbinyEOB == true){wDFbinyEOB = false;}
      if(QjhOzMoSQR == true){QjhOzMoSQR = false;}
      if(aXVFSEkpTr == true){aXVFSEkpTr = false;}
      if(eYDgytXMep == true){eYDgytXMep = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHMNKRALCJ
{ 
  void CRViLIqnri()
  { 
      bool RafsCZFByB = false;
      bool IQJfwnmKuT = false;
      bool rcZmKsUfXS = false;
      bool abydNTjARU = false;
      bool DLOlVgSdeZ = false;
      bool XgcWGoBrhJ = false;
      bool EYcfagRfRc = false;
      bool EmrZPfNmQd = false;
      bool ZqByttybWX = false;
      bool RqSHQeiiLo = false;
      bool OmLCVjnDGZ = false;
      bool aObEjNXekf = false;
      bool hpIsKMUjIk = false;
      bool xeaaOmezbJ = false;
      bool FuUwxDPNXD = false;
      bool HDyeGYdRqI = false;
      bool PDtVcumAow = false;
      bool hYCaZmVMwH = false;
      bool xGMFdsgwUp = false;
      bool IMHStCAyTB = false;
      string ZFtQCJOnGy;
      string COGzlykKcd;
      string RahGzSqtTR;
      string GTxcIKBUza;
      string ZHgrpnuJZY;
      string hlZtIzWnQj;
      string SUUnrhRdpa;
      string xQKCEJspQK;
      string WhTtjUtDTJ;
      string nMDPIFmrAH;
      string WRSybQbXoz;
      string FfWFNjAZEW;
      string nNKfmjNusz;
      string VApInEOUSS;
      string rVNTDHpxBX;
      string EMncTIGlLq;
      string DgepcEpORI;
      string VeHldRApce;
      string tPsUtIMMne;
      string ycJaOLqXqy;
      if(ZFtQCJOnGy == WRSybQbXoz){RafsCZFByB = true;}
      else if(WRSybQbXoz == ZFtQCJOnGy){OmLCVjnDGZ = true;}
      if(COGzlykKcd == FfWFNjAZEW){IQJfwnmKuT = true;}
      else if(FfWFNjAZEW == COGzlykKcd){aObEjNXekf = true;}
      if(RahGzSqtTR == nNKfmjNusz){rcZmKsUfXS = true;}
      else if(nNKfmjNusz == RahGzSqtTR){hpIsKMUjIk = true;}
      if(GTxcIKBUza == VApInEOUSS){abydNTjARU = true;}
      else if(VApInEOUSS == GTxcIKBUza){xeaaOmezbJ = true;}
      if(ZHgrpnuJZY == rVNTDHpxBX){DLOlVgSdeZ = true;}
      else if(rVNTDHpxBX == ZHgrpnuJZY){FuUwxDPNXD = true;}
      if(hlZtIzWnQj == EMncTIGlLq){XgcWGoBrhJ = true;}
      else if(EMncTIGlLq == hlZtIzWnQj){HDyeGYdRqI = true;}
      if(SUUnrhRdpa == DgepcEpORI){EYcfagRfRc = true;}
      else if(DgepcEpORI == SUUnrhRdpa){PDtVcumAow = true;}
      if(xQKCEJspQK == VeHldRApce){EmrZPfNmQd = true;}
      if(WhTtjUtDTJ == tPsUtIMMne){ZqByttybWX = true;}
      if(nMDPIFmrAH == ycJaOLqXqy){RqSHQeiiLo = true;}
      while(VeHldRApce == xQKCEJspQK){hYCaZmVMwH = true;}
      while(tPsUtIMMne == tPsUtIMMne){xGMFdsgwUp = true;}
      while(ycJaOLqXqy == ycJaOLqXqy){IMHStCAyTB = true;}
      if(RafsCZFByB == true){RafsCZFByB = false;}
      if(IQJfwnmKuT == true){IQJfwnmKuT = false;}
      if(rcZmKsUfXS == true){rcZmKsUfXS = false;}
      if(abydNTjARU == true){abydNTjARU = false;}
      if(DLOlVgSdeZ == true){DLOlVgSdeZ = false;}
      if(XgcWGoBrhJ == true){XgcWGoBrhJ = false;}
      if(EYcfagRfRc == true){EYcfagRfRc = false;}
      if(EmrZPfNmQd == true){EmrZPfNmQd = false;}
      if(ZqByttybWX == true){ZqByttybWX = false;}
      if(RqSHQeiiLo == true){RqSHQeiiLo = false;}
      if(OmLCVjnDGZ == true){OmLCVjnDGZ = false;}
      if(aObEjNXekf == true){aObEjNXekf = false;}
      if(hpIsKMUjIk == true){hpIsKMUjIk = false;}
      if(xeaaOmezbJ == true){xeaaOmezbJ = false;}
      if(FuUwxDPNXD == true){FuUwxDPNXD = false;}
      if(HDyeGYdRqI == true){HDyeGYdRqI = false;}
      if(PDtVcumAow == true){PDtVcumAow = false;}
      if(hYCaZmVMwH == true){hYCaZmVMwH = false;}
      if(xGMFdsgwUp == true){xGMFdsgwUp = false;}
      if(IMHStCAyTB == true){IMHStCAyTB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKNPKAMQJM
{ 
  void OHPxgZHAcr()
  { 
      bool ZMIXSdymRj = false;
      bool iYRHlpqcjo = false;
      bool dQeTrdxfni = false;
      bool EetoCqdJWZ = false;
      bool fkKWaLJBdx = false;
      bool pukaUIgnfo = false;
      bool gRzieDdcEu = false;
      bool MhFJIrGHsf = false;
      bool TuCpsJtTTs = false;
      bool JochsOlaqW = false;
      bool hgwijHoaRb = false;
      bool CYuAUkPJoV = false;
      bool IKILkXFWQt = false;
      bool FeQVymzSFk = false;
      bool TTBrpkscMH = false;
      bool yclUNXXkyM = false;
      bool CRJXVXIYBh = false;
      bool lwDECoIQUA = false;
      bool ebKJucsuIa = false;
      bool ONUshBJcVS = false;
      string NuaqsVwqQs;
      string emPUULFaEh;
      string RWTWeyFXrD;
      string EkprkAGVsb;
      string IuWyYqAdzu;
      string joLDPqbDLu;
      string PYyMnsxWiT;
      string EigbZWzVyn;
      string xbYwSPZmct;
      string YDKyMjxJJe;
      string tcteqBHics;
      string rFEXxmzCtY;
      string TJtouBYiPo;
      string ZoMStTgsFR;
      string HqJiBSylBY;
      string ktPjLjiFjo;
      string cYSnTDsldc;
      string FGwbRbAKmb;
      string DlgpEeYcGJ;
      string kbJPnhXUPy;
      if(NuaqsVwqQs == tcteqBHics){ZMIXSdymRj = true;}
      else if(tcteqBHics == NuaqsVwqQs){hgwijHoaRb = true;}
      if(emPUULFaEh == rFEXxmzCtY){iYRHlpqcjo = true;}
      else if(rFEXxmzCtY == emPUULFaEh){CYuAUkPJoV = true;}
      if(RWTWeyFXrD == TJtouBYiPo){dQeTrdxfni = true;}
      else if(TJtouBYiPo == RWTWeyFXrD){IKILkXFWQt = true;}
      if(EkprkAGVsb == ZoMStTgsFR){EetoCqdJWZ = true;}
      else if(ZoMStTgsFR == EkprkAGVsb){FeQVymzSFk = true;}
      if(IuWyYqAdzu == HqJiBSylBY){fkKWaLJBdx = true;}
      else if(HqJiBSylBY == IuWyYqAdzu){TTBrpkscMH = true;}
      if(joLDPqbDLu == ktPjLjiFjo){pukaUIgnfo = true;}
      else if(ktPjLjiFjo == joLDPqbDLu){yclUNXXkyM = true;}
      if(PYyMnsxWiT == cYSnTDsldc){gRzieDdcEu = true;}
      else if(cYSnTDsldc == PYyMnsxWiT){CRJXVXIYBh = true;}
      if(EigbZWzVyn == FGwbRbAKmb){MhFJIrGHsf = true;}
      if(xbYwSPZmct == DlgpEeYcGJ){TuCpsJtTTs = true;}
      if(YDKyMjxJJe == kbJPnhXUPy){JochsOlaqW = true;}
      while(FGwbRbAKmb == EigbZWzVyn){lwDECoIQUA = true;}
      while(DlgpEeYcGJ == DlgpEeYcGJ){ebKJucsuIa = true;}
      while(kbJPnhXUPy == kbJPnhXUPy){ONUshBJcVS = true;}
      if(ZMIXSdymRj == true){ZMIXSdymRj = false;}
      if(iYRHlpqcjo == true){iYRHlpqcjo = false;}
      if(dQeTrdxfni == true){dQeTrdxfni = false;}
      if(EetoCqdJWZ == true){EetoCqdJWZ = false;}
      if(fkKWaLJBdx == true){fkKWaLJBdx = false;}
      if(pukaUIgnfo == true){pukaUIgnfo = false;}
      if(gRzieDdcEu == true){gRzieDdcEu = false;}
      if(MhFJIrGHsf == true){MhFJIrGHsf = false;}
      if(TuCpsJtTTs == true){TuCpsJtTTs = false;}
      if(JochsOlaqW == true){JochsOlaqW = false;}
      if(hgwijHoaRb == true){hgwijHoaRb = false;}
      if(CYuAUkPJoV == true){CYuAUkPJoV = false;}
      if(IKILkXFWQt == true){IKILkXFWQt = false;}
      if(FeQVymzSFk == true){FeQVymzSFk = false;}
      if(TTBrpkscMH == true){TTBrpkscMH = false;}
      if(yclUNXXkyM == true){yclUNXXkyM = false;}
      if(CRJXVXIYBh == true){CRJXVXIYBh = false;}
      if(lwDECoIQUA == true){lwDECoIQUA = false;}
      if(ebKJucsuIa == true){ebKJucsuIa = false;}
      if(ONUshBJcVS == true){ONUshBJcVS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GQBEVHHTBP
{ 
  void UtGqrMTPKW()
  { 
      bool SOFoKTbccK = false;
      bool ZrCsfqhQXT = false;
      bool PoVromzXJH = false;
      bool JhuAXEsKam = false;
      bool lCFtXGdaBn = false;
      bool OnLqLcrNzW = false;
      bool UDTUBrwBUa = false;
      bool xWojhNjbTi = false;
      bool JXWUsUVEnt = false;
      bool LfKEShikse = false;
      bool KcFZqqzbJx = false;
      bool sQtQNwgyaf = false;
      bool WrMZORLjQz = false;
      bool eyhnXgRwdC = false;
      bool VsuqBuktpV = false;
      bool BjKMIRPfLY = false;
      bool eOLJSuhFrg = false;
      bool ekUXKdxVYT = false;
      bool fRtuyunVfG = false;
      bool QlkEXHhkXG = false;
      string qknBOFrdoT;
      string OmuyJdxBDH;
      string NYSLGakACU;
      string wSSUhxYXFd;
      string CwymnraudN;
      string LGsdwSScum;
      string UraUXuUZPM;
      string FYuZEQZeWO;
      string zpVoIoZnYP;
      string dwcRIJUcPs;
      string XAeRIlLSZe;
      string rmFgneWlLh;
      string UfBAhJudQt;
      string wxPdpyKDfW;
      string dGOtXqpwdd;
      string mhRgXrzejy;
      string phCehuXbpo;
      string TSFoENRHcq;
      string SzzlHOehFy;
      string zfThfwEiLb;
      if(qknBOFrdoT == XAeRIlLSZe){SOFoKTbccK = true;}
      else if(XAeRIlLSZe == qknBOFrdoT){KcFZqqzbJx = true;}
      if(OmuyJdxBDH == rmFgneWlLh){ZrCsfqhQXT = true;}
      else if(rmFgneWlLh == OmuyJdxBDH){sQtQNwgyaf = true;}
      if(NYSLGakACU == UfBAhJudQt){PoVromzXJH = true;}
      else if(UfBAhJudQt == NYSLGakACU){WrMZORLjQz = true;}
      if(wSSUhxYXFd == wxPdpyKDfW){JhuAXEsKam = true;}
      else if(wxPdpyKDfW == wSSUhxYXFd){eyhnXgRwdC = true;}
      if(CwymnraudN == dGOtXqpwdd){lCFtXGdaBn = true;}
      else if(dGOtXqpwdd == CwymnraudN){VsuqBuktpV = true;}
      if(LGsdwSScum == mhRgXrzejy){OnLqLcrNzW = true;}
      else if(mhRgXrzejy == LGsdwSScum){BjKMIRPfLY = true;}
      if(UraUXuUZPM == phCehuXbpo){UDTUBrwBUa = true;}
      else if(phCehuXbpo == UraUXuUZPM){eOLJSuhFrg = true;}
      if(FYuZEQZeWO == TSFoENRHcq){xWojhNjbTi = true;}
      if(zpVoIoZnYP == SzzlHOehFy){JXWUsUVEnt = true;}
      if(dwcRIJUcPs == zfThfwEiLb){LfKEShikse = true;}
      while(TSFoENRHcq == FYuZEQZeWO){ekUXKdxVYT = true;}
      while(SzzlHOehFy == SzzlHOehFy){fRtuyunVfG = true;}
      while(zfThfwEiLb == zfThfwEiLb){QlkEXHhkXG = true;}
      if(SOFoKTbccK == true){SOFoKTbccK = false;}
      if(ZrCsfqhQXT == true){ZrCsfqhQXT = false;}
      if(PoVromzXJH == true){PoVromzXJH = false;}
      if(JhuAXEsKam == true){JhuAXEsKam = false;}
      if(lCFtXGdaBn == true){lCFtXGdaBn = false;}
      if(OnLqLcrNzW == true){OnLqLcrNzW = false;}
      if(UDTUBrwBUa == true){UDTUBrwBUa = false;}
      if(xWojhNjbTi == true){xWojhNjbTi = false;}
      if(JXWUsUVEnt == true){JXWUsUVEnt = false;}
      if(LfKEShikse == true){LfKEShikse = false;}
      if(KcFZqqzbJx == true){KcFZqqzbJx = false;}
      if(sQtQNwgyaf == true){sQtQNwgyaf = false;}
      if(WrMZORLjQz == true){WrMZORLjQz = false;}
      if(eyhnXgRwdC == true){eyhnXgRwdC = false;}
      if(VsuqBuktpV == true){VsuqBuktpV = false;}
      if(BjKMIRPfLY == true){BjKMIRPfLY = false;}
      if(eOLJSuhFrg == true){eOLJSuhFrg = false;}
      if(ekUXKdxVYT == true){ekUXKdxVYT = false;}
      if(fRtuyunVfG == true){fRtuyunVfG = false;}
      if(QlkEXHhkXG == true){QlkEXHhkXG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMWKJEXVOV
{ 
  void eBbqwMffAY()
  { 
      bool mWeGIaEoRX = false;
      bool ZPmKgrogPV = false;
      bool piVBFaeVYc = false;
      bool RfjRWfYCVn = false;
      bool xHzEqMnDna = false;
      bool crweODAcBg = false;
      bool uhQnGteVmA = false;
      bool SlLaYhjQKr = false;
      bool mbhxzYjECT = false;
      bool ewBnsOqKyx = false;
      bool hSQmIqgUGg = false;
      bool TjRJtSASng = false;
      bool KaSTVVkWgJ = false;
      bool pYSMKULtoI = false;
      bool rOyUzueqtZ = false;
      bool OYVRmGzwRm = false;
      bool FJmwpuQFyZ = false;
      bool HFcfnubxTZ = false;
      bool qscHuRCBZD = false;
      bool UObCDiaBdE = false;
      string zFhEUuYNis;
      string omSGhgoIeJ;
      string rUOATPArFP;
      string PYAJlMulHr;
      string cBFGLkWros;
      string CzluNephkF;
      string ufISdQlIUU;
      string lDBlgqOIoh;
      string rHDLNPlEwG;
      string VNBCxxrlbu;
      string yNWTHyyAOW;
      string PgrCMmcwFN;
      string dhLNzXCznj;
      string ycftiekiEO;
      string RlpZqnUyoK;
      string TwfOQQBJUi;
      string wzLeXlByTh;
      string CsqqwrqlVK;
      string CEJdPBwRcR;
      string caNUSSZLBE;
      if(zFhEUuYNis == yNWTHyyAOW){mWeGIaEoRX = true;}
      else if(yNWTHyyAOW == zFhEUuYNis){hSQmIqgUGg = true;}
      if(omSGhgoIeJ == PgrCMmcwFN){ZPmKgrogPV = true;}
      else if(PgrCMmcwFN == omSGhgoIeJ){TjRJtSASng = true;}
      if(rUOATPArFP == dhLNzXCznj){piVBFaeVYc = true;}
      else if(dhLNzXCznj == rUOATPArFP){KaSTVVkWgJ = true;}
      if(PYAJlMulHr == ycftiekiEO){RfjRWfYCVn = true;}
      else if(ycftiekiEO == PYAJlMulHr){pYSMKULtoI = true;}
      if(cBFGLkWros == RlpZqnUyoK){xHzEqMnDna = true;}
      else if(RlpZqnUyoK == cBFGLkWros){rOyUzueqtZ = true;}
      if(CzluNephkF == TwfOQQBJUi){crweODAcBg = true;}
      else if(TwfOQQBJUi == CzluNephkF){OYVRmGzwRm = true;}
      if(ufISdQlIUU == wzLeXlByTh){uhQnGteVmA = true;}
      else if(wzLeXlByTh == ufISdQlIUU){FJmwpuQFyZ = true;}
      if(lDBlgqOIoh == CsqqwrqlVK){SlLaYhjQKr = true;}
      if(rHDLNPlEwG == CEJdPBwRcR){mbhxzYjECT = true;}
      if(VNBCxxrlbu == caNUSSZLBE){ewBnsOqKyx = true;}
      while(CsqqwrqlVK == lDBlgqOIoh){HFcfnubxTZ = true;}
      while(CEJdPBwRcR == CEJdPBwRcR){qscHuRCBZD = true;}
      while(caNUSSZLBE == caNUSSZLBE){UObCDiaBdE = true;}
      if(mWeGIaEoRX == true){mWeGIaEoRX = false;}
      if(ZPmKgrogPV == true){ZPmKgrogPV = false;}
      if(piVBFaeVYc == true){piVBFaeVYc = false;}
      if(RfjRWfYCVn == true){RfjRWfYCVn = false;}
      if(xHzEqMnDna == true){xHzEqMnDna = false;}
      if(crweODAcBg == true){crweODAcBg = false;}
      if(uhQnGteVmA == true){uhQnGteVmA = false;}
      if(SlLaYhjQKr == true){SlLaYhjQKr = false;}
      if(mbhxzYjECT == true){mbhxzYjECT = false;}
      if(ewBnsOqKyx == true){ewBnsOqKyx = false;}
      if(hSQmIqgUGg == true){hSQmIqgUGg = false;}
      if(TjRJtSASng == true){TjRJtSASng = false;}
      if(KaSTVVkWgJ == true){KaSTVVkWgJ = false;}
      if(pYSMKULtoI == true){pYSMKULtoI = false;}
      if(rOyUzueqtZ == true){rOyUzueqtZ = false;}
      if(OYVRmGzwRm == true){OYVRmGzwRm = false;}
      if(FJmwpuQFyZ == true){FJmwpuQFyZ = false;}
      if(HFcfnubxTZ == true){HFcfnubxTZ = false;}
      if(qscHuRCBZD == true){qscHuRCBZD = false;}
      if(UObCDiaBdE == true){UObCDiaBdE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMBJPLCXEM
{ 
  void GfGEKoAjMO()
  { 
      bool LyKeWgUxFx = false;
      bool uHjbXxGwhb = false;
      bool OCeMnfOUFV = false;
      bool FgNerCDGXu = false;
      bool nuwPWYHKZg = false;
      bool PqXQeITxpp = false;
      bool RzqjrNsFjV = false;
      bool szXlnTGOpP = false;
      bool YDuYFNJxzi = false;
      bool hGQgdnDMXI = false;
      bool eCaDmPSkcL = false;
      bool CFHZRNESdd = false;
      bool DwFAmmiqIA = false;
      bool QtpgkVcqlp = false;
      bool tYTngcyqOP = false;
      bool jkhsFhwZPz = false;
      bool gbcctHOanw = false;
      bool jMfnjebQSK = false;
      bool nrbrPfLxbC = false;
      bool YDblJRuqsZ = false;
      string aSbhIdEPUT;
      string qOPBZfQeoM;
      string hNHONtWNkr;
      string VGYSuhApdc;
      string wIhCxaynrw;
      string oetmHMKNTN;
      string HpdbxjoxGq;
      string eaBLQZfERm;
      string whUnDqMlLh;
      string WmWQUFdFEN;
      string lBgAQOchVg;
      string gFwgQYVpYG;
      string WDlYUrDkqL;
      string wZADBuATWn;
      string OePdAQqpzw;
      string imgyphPIfY;
      string KrqKkHFreU;
      string YCSjrrmHXD;
      string ANkubIrCNS;
      string frmxdVmFss;
      if(aSbhIdEPUT == lBgAQOchVg){LyKeWgUxFx = true;}
      else if(lBgAQOchVg == aSbhIdEPUT){eCaDmPSkcL = true;}
      if(qOPBZfQeoM == gFwgQYVpYG){uHjbXxGwhb = true;}
      else if(gFwgQYVpYG == qOPBZfQeoM){CFHZRNESdd = true;}
      if(hNHONtWNkr == WDlYUrDkqL){OCeMnfOUFV = true;}
      else if(WDlYUrDkqL == hNHONtWNkr){DwFAmmiqIA = true;}
      if(VGYSuhApdc == wZADBuATWn){FgNerCDGXu = true;}
      else if(wZADBuATWn == VGYSuhApdc){QtpgkVcqlp = true;}
      if(wIhCxaynrw == OePdAQqpzw){nuwPWYHKZg = true;}
      else if(OePdAQqpzw == wIhCxaynrw){tYTngcyqOP = true;}
      if(oetmHMKNTN == imgyphPIfY){PqXQeITxpp = true;}
      else if(imgyphPIfY == oetmHMKNTN){jkhsFhwZPz = true;}
      if(HpdbxjoxGq == KrqKkHFreU){RzqjrNsFjV = true;}
      else if(KrqKkHFreU == HpdbxjoxGq){gbcctHOanw = true;}
      if(eaBLQZfERm == YCSjrrmHXD){szXlnTGOpP = true;}
      if(whUnDqMlLh == ANkubIrCNS){YDuYFNJxzi = true;}
      if(WmWQUFdFEN == frmxdVmFss){hGQgdnDMXI = true;}
      while(YCSjrrmHXD == eaBLQZfERm){jMfnjebQSK = true;}
      while(ANkubIrCNS == ANkubIrCNS){nrbrPfLxbC = true;}
      while(frmxdVmFss == frmxdVmFss){YDblJRuqsZ = true;}
      if(LyKeWgUxFx == true){LyKeWgUxFx = false;}
      if(uHjbXxGwhb == true){uHjbXxGwhb = false;}
      if(OCeMnfOUFV == true){OCeMnfOUFV = false;}
      if(FgNerCDGXu == true){FgNerCDGXu = false;}
      if(nuwPWYHKZg == true){nuwPWYHKZg = false;}
      if(PqXQeITxpp == true){PqXQeITxpp = false;}
      if(RzqjrNsFjV == true){RzqjrNsFjV = false;}
      if(szXlnTGOpP == true){szXlnTGOpP = false;}
      if(YDuYFNJxzi == true){YDuYFNJxzi = false;}
      if(hGQgdnDMXI == true){hGQgdnDMXI = false;}
      if(eCaDmPSkcL == true){eCaDmPSkcL = false;}
      if(CFHZRNESdd == true){CFHZRNESdd = false;}
      if(DwFAmmiqIA == true){DwFAmmiqIA = false;}
      if(QtpgkVcqlp == true){QtpgkVcqlp = false;}
      if(tYTngcyqOP == true){tYTngcyqOP = false;}
      if(jkhsFhwZPz == true){jkhsFhwZPz = false;}
      if(gbcctHOanw == true){gbcctHOanw = false;}
      if(jMfnjebQSK == true){jMfnjebQSK = false;}
      if(nrbrPfLxbC == true){nrbrPfLxbC = false;}
      if(YDblJRuqsZ == true){YDblJRuqsZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHSSXSQMYC
{ 
  void LwetJjlXHc()
  { 
      bool OWNZzIxLlH = false;
      bool mckyJthzwk = false;
      bool UeLTcRJOLD = false;
      bool CBQZKtoTDW = false;
      bool RfExxjUYjJ = false;
      bool NxoNAjKswh = false;
      bool zhAiElMLmP = false;
      bool FNuYSnaOWs = false;
      bool wkeBoFLCYa = false;
      bool iuWVXifVrL = false;
      bool WJkUEzCQtL = false;
      bool JwWDlODysz = false;
      bool ZJmLfJqZAi = false;
      bool IEVLVmzJxp = false;
      bool CuIMRlYSjJ = false;
      bool fhbskMWYnt = false;
      bool IbPKDEZKhy = false;
      bool OtACweBZts = false;
      bool kXpqDaccZI = false;
      bool PZVChZexIN = false;
      string mJtoYKLrZC;
      string xKzEMjsyFG;
      string frZAiNBGJo;
      string VUuJLSMoZs;
      string UVdohsyDcF;
      string VKpijuitGL;
      string JEijgcPpst;
      string XEYLkKNkRo;
      string OxdDSKdMZP;
      string iRiNjPmsIF;
      string dIJihRldxY;
      string gycQwLaeRW;
      string yCPdKGUKbU;
      string XUbLLGmtVB;
      string XzOAhknSQX;
      string oHbkGarfXb;
      string wbCcBMVQEp;
      string XfJPzzmPuZ;
      string RCtDfPrqEj;
      string NGWtEuwlzV;
      if(mJtoYKLrZC == dIJihRldxY){OWNZzIxLlH = true;}
      else if(dIJihRldxY == mJtoYKLrZC){WJkUEzCQtL = true;}
      if(xKzEMjsyFG == gycQwLaeRW){mckyJthzwk = true;}
      else if(gycQwLaeRW == xKzEMjsyFG){JwWDlODysz = true;}
      if(frZAiNBGJo == yCPdKGUKbU){UeLTcRJOLD = true;}
      else if(yCPdKGUKbU == frZAiNBGJo){ZJmLfJqZAi = true;}
      if(VUuJLSMoZs == XUbLLGmtVB){CBQZKtoTDW = true;}
      else if(XUbLLGmtVB == VUuJLSMoZs){IEVLVmzJxp = true;}
      if(UVdohsyDcF == XzOAhknSQX){RfExxjUYjJ = true;}
      else if(XzOAhknSQX == UVdohsyDcF){CuIMRlYSjJ = true;}
      if(VKpijuitGL == oHbkGarfXb){NxoNAjKswh = true;}
      else if(oHbkGarfXb == VKpijuitGL){fhbskMWYnt = true;}
      if(JEijgcPpst == wbCcBMVQEp){zhAiElMLmP = true;}
      else if(wbCcBMVQEp == JEijgcPpst){IbPKDEZKhy = true;}
      if(XEYLkKNkRo == XfJPzzmPuZ){FNuYSnaOWs = true;}
      if(OxdDSKdMZP == RCtDfPrqEj){wkeBoFLCYa = true;}
      if(iRiNjPmsIF == NGWtEuwlzV){iuWVXifVrL = true;}
      while(XfJPzzmPuZ == XEYLkKNkRo){OtACweBZts = true;}
      while(RCtDfPrqEj == RCtDfPrqEj){kXpqDaccZI = true;}
      while(NGWtEuwlzV == NGWtEuwlzV){PZVChZexIN = true;}
      if(OWNZzIxLlH == true){OWNZzIxLlH = false;}
      if(mckyJthzwk == true){mckyJthzwk = false;}
      if(UeLTcRJOLD == true){UeLTcRJOLD = false;}
      if(CBQZKtoTDW == true){CBQZKtoTDW = false;}
      if(RfExxjUYjJ == true){RfExxjUYjJ = false;}
      if(NxoNAjKswh == true){NxoNAjKswh = false;}
      if(zhAiElMLmP == true){zhAiElMLmP = false;}
      if(FNuYSnaOWs == true){FNuYSnaOWs = false;}
      if(wkeBoFLCYa == true){wkeBoFLCYa = false;}
      if(iuWVXifVrL == true){iuWVXifVrL = false;}
      if(WJkUEzCQtL == true){WJkUEzCQtL = false;}
      if(JwWDlODysz == true){JwWDlODysz = false;}
      if(ZJmLfJqZAi == true){ZJmLfJqZAi = false;}
      if(IEVLVmzJxp == true){IEVLVmzJxp = false;}
      if(CuIMRlYSjJ == true){CuIMRlYSjJ = false;}
      if(fhbskMWYnt == true){fhbskMWYnt = false;}
      if(IbPKDEZKhy == true){IbPKDEZKhy = false;}
      if(OtACweBZts == true){OtACweBZts = false;}
      if(kXpqDaccZI == true){kXpqDaccZI = false;}
      if(PZVChZexIN == true){PZVChZexIN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTRECNZRNX
{ 
  void tEZSofljbG()
  { 
      bool gkaMxAGmOy = false;
      bool NNhwltQQrA = false;
      bool yUPyQuJbAf = false;
      bool XciTwChMla = false;
      bool HllxXertcJ = false;
      bool AXGyqLUbuC = false;
      bool pdmhajeOzi = false;
      bool LDdRrMiSZl = false;
      bool CPzpfzWkck = false;
      bool gFRijdzDWn = false;
      bool ActsxwsnFe = false;
      bool bCCJzadwCa = false;
      bool NskOCFlugO = false;
      bool MewlkZVGri = false;
      bool GhfyIeDHiJ = false;
      bool zCBuaHqepq = false;
      bool KyHqRxGPXZ = false;
      bool EWESUeNmFX = false;
      bool CdLWOKdALd = false;
      bool hpPAYHangL = false;
      string euHhikdiuq;
      string tOohMxpRit;
      string xVlWJERrFA;
      string uCDFKuzxAZ;
      string BHAKDwYkWH;
      string RDLnRJJjYd;
      string TkduurKiXR;
      string ysRIrpUaSM;
      string efUxhrqPnB;
      string kOXVGQdEOL;
      string kpNFJYlCwa;
      string nhRLzmPfMD;
      string AutVfjUuCb;
      string MQMGboRPnI;
      string GnSMMCwLWS;
      string AxqLKpuqZZ;
      string EpATOXVLjK;
      string UAqEwMbgJc;
      string mJYiaOYAul;
      string sZpOEQnzyo;
      if(euHhikdiuq == kpNFJYlCwa){gkaMxAGmOy = true;}
      else if(kpNFJYlCwa == euHhikdiuq){ActsxwsnFe = true;}
      if(tOohMxpRit == nhRLzmPfMD){NNhwltQQrA = true;}
      else if(nhRLzmPfMD == tOohMxpRit){bCCJzadwCa = true;}
      if(xVlWJERrFA == AutVfjUuCb){yUPyQuJbAf = true;}
      else if(AutVfjUuCb == xVlWJERrFA){NskOCFlugO = true;}
      if(uCDFKuzxAZ == MQMGboRPnI){XciTwChMla = true;}
      else if(MQMGboRPnI == uCDFKuzxAZ){MewlkZVGri = true;}
      if(BHAKDwYkWH == GnSMMCwLWS){HllxXertcJ = true;}
      else if(GnSMMCwLWS == BHAKDwYkWH){GhfyIeDHiJ = true;}
      if(RDLnRJJjYd == AxqLKpuqZZ){AXGyqLUbuC = true;}
      else if(AxqLKpuqZZ == RDLnRJJjYd){zCBuaHqepq = true;}
      if(TkduurKiXR == EpATOXVLjK){pdmhajeOzi = true;}
      else if(EpATOXVLjK == TkduurKiXR){KyHqRxGPXZ = true;}
      if(ysRIrpUaSM == UAqEwMbgJc){LDdRrMiSZl = true;}
      if(efUxhrqPnB == mJYiaOYAul){CPzpfzWkck = true;}
      if(kOXVGQdEOL == sZpOEQnzyo){gFRijdzDWn = true;}
      while(UAqEwMbgJc == ysRIrpUaSM){EWESUeNmFX = true;}
      while(mJYiaOYAul == mJYiaOYAul){CdLWOKdALd = true;}
      while(sZpOEQnzyo == sZpOEQnzyo){hpPAYHangL = true;}
      if(gkaMxAGmOy == true){gkaMxAGmOy = false;}
      if(NNhwltQQrA == true){NNhwltQQrA = false;}
      if(yUPyQuJbAf == true){yUPyQuJbAf = false;}
      if(XciTwChMla == true){XciTwChMla = false;}
      if(HllxXertcJ == true){HllxXertcJ = false;}
      if(AXGyqLUbuC == true){AXGyqLUbuC = false;}
      if(pdmhajeOzi == true){pdmhajeOzi = false;}
      if(LDdRrMiSZl == true){LDdRrMiSZl = false;}
      if(CPzpfzWkck == true){CPzpfzWkck = false;}
      if(gFRijdzDWn == true){gFRijdzDWn = false;}
      if(ActsxwsnFe == true){ActsxwsnFe = false;}
      if(bCCJzadwCa == true){bCCJzadwCa = false;}
      if(NskOCFlugO == true){NskOCFlugO = false;}
      if(MewlkZVGri == true){MewlkZVGri = false;}
      if(GhfyIeDHiJ == true){GhfyIeDHiJ = false;}
      if(zCBuaHqepq == true){zCBuaHqepq = false;}
      if(KyHqRxGPXZ == true){KyHqRxGPXZ = false;}
      if(EWESUeNmFX == true){EWESUeNmFX = false;}
      if(CdLWOKdALd == true){CdLWOKdALd = false;}
      if(hpPAYHangL == true){hpPAYHangL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFWUBJSETT
{ 
  void ADmAtrIeHD()
  { 
      bool PDctKGMmEt = false;
      bool siLGSDXihI = false;
      bool YBzlwhIOPE = false;
      bool hqLkIwCLAd = false;
      bool eEedUwmnVm = false;
      bool lWaxJNEqxb = false;
      bool xxWALBWZxV = false;
      bool AMiDcTVURz = false;
      bool tTscSKPNbt = false;
      bool rLNXfggeRS = false;
      bool ZNpzlYnWUo = false;
      bool qiYxhcEshB = false;
      bool lJyDdoyKWu = false;
      bool mqCyZgdtqs = false;
      bool WrslDIlPpC = false;
      bool cmwQgPOmUx = false;
      bool aczYCzfaXA = false;
      bool zJCnesPLzU = false;
      bool ChUURztlRJ = false;
      bool RqYtSssTjD = false;
      string KuQsifExKu;
      string BtyiVDMCCU;
      string eshCLTqzgI;
      string DJdKQEUSus;
      string pseLTjNOVc;
      string nLIptQMOhP;
      string nEPCqrPnRR;
      string htHJdkOWia;
      string GbcDUqBnPA;
      string qGjfFkcbTa;
      string UYxEusEzLI;
      string CpeGJMbMhA;
      string qbYRZbJbDs;
      string IlDHGgeYIa;
      string lCbGyBacWr;
      string IQtSisAedT;
      string jcuSAPlXAb;
      string hCDHNoARTX;
      string AfFLjrqjXN;
      string fztnqJGIGh;
      if(KuQsifExKu == UYxEusEzLI){PDctKGMmEt = true;}
      else if(UYxEusEzLI == KuQsifExKu){ZNpzlYnWUo = true;}
      if(BtyiVDMCCU == CpeGJMbMhA){siLGSDXihI = true;}
      else if(CpeGJMbMhA == BtyiVDMCCU){qiYxhcEshB = true;}
      if(eshCLTqzgI == qbYRZbJbDs){YBzlwhIOPE = true;}
      else if(qbYRZbJbDs == eshCLTqzgI){lJyDdoyKWu = true;}
      if(DJdKQEUSus == IlDHGgeYIa){hqLkIwCLAd = true;}
      else if(IlDHGgeYIa == DJdKQEUSus){mqCyZgdtqs = true;}
      if(pseLTjNOVc == lCbGyBacWr){eEedUwmnVm = true;}
      else if(lCbGyBacWr == pseLTjNOVc){WrslDIlPpC = true;}
      if(nLIptQMOhP == IQtSisAedT){lWaxJNEqxb = true;}
      else if(IQtSisAedT == nLIptQMOhP){cmwQgPOmUx = true;}
      if(nEPCqrPnRR == jcuSAPlXAb){xxWALBWZxV = true;}
      else if(jcuSAPlXAb == nEPCqrPnRR){aczYCzfaXA = true;}
      if(htHJdkOWia == hCDHNoARTX){AMiDcTVURz = true;}
      if(GbcDUqBnPA == AfFLjrqjXN){tTscSKPNbt = true;}
      if(qGjfFkcbTa == fztnqJGIGh){rLNXfggeRS = true;}
      while(hCDHNoARTX == htHJdkOWia){zJCnesPLzU = true;}
      while(AfFLjrqjXN == AfFLjrqjXN){ChUURztlRJ = true;}
      while(fztnqJGIGh == fztnqJGIGh){RqYtSssTjD = true;}
      if(PDctKGMmEt == true){PDctKGMmEt = false;}
      if(siLGSDXihI == true){siLGSDXihI = false;}
      if(YBzlwhIOPE == true){YBzlwhIOPE = false;}
      if(hqLkIwCLAd == true){hqLkIwCLAd = false;}
      if(eEedUwmnVm == true){eEedUwmnVm = false;}
      if(lWaxJNEqxb == true){lWaxJNEqxb = false;}
      if(xxWALBWZxV == true){xxWALBWZxV = false;}
      if(AMiDcTVURz == true){AMiDcTVURz = false;}
      if(tTscSKPNbt == true){tTscSKPNbt = false;}
      if(rLNXfggeRS == true){rLNXfggeRS = false;}
      if(ZNpzlYnWUo == true){ZNpzlYnWUo = false;}
      if(qiYxhcEshB == true){qiYxhcEshB = false;}
      if(lJyDdoyKWu == true){lJyDdoyKWu = false;}
      if(mqCyZgdtqs == true){mqCyZgdtqs = false;}
      if(WrslDIlPpC == true){WrslDIlPpC = false;}
      if(cmwQgPOmUx == true){cmwQgPOmUx = false;}
      if(aczYCzfaXA == true){aczYCzfaXA = false;}
      if(zJCnesPLzU == true){zJCnesPLzU = false;}
      if(ChUURztlRJ == true){ChUURztlRJ = false;}
      if(RqYtSssTjD == true){RqYtSssTjD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWXCXZGORL
{ 
  void TtQEIJPpmh()
  { 
      bool lBTXwjpyqp = false;
      bool wRHBFxEweG = false;
      bool RXaPssZwOu = false;
      bool gzrfdJWLDk = false;
      bool wSYYcVzCNr = false;
      bool wAcQqNZDdC = false;
      bool JsiwIwZbWu = false;
      bool ZrrsJyyCmX = false;
      bool tXhWzfWbnP = false;
      bool iTgAbDicPg = false;
      bool uXeSREIjGr = false;
      bool OXQGIlKMwb = false;
      bool YymHMGKrQG = false;
      bool PVmFbVrPEt = false;
      bool XmUwALDZqo = false;
      bool rVfmIxjWFL = false;
      bool sPSAbskKel = false;
      bool stICEkcpGB = false;
      bool DjAbNtozxd = false;
      bool lUJrAHUTUH = false;
      string DRbbcLJqko;
      string dVaeqkNtaZ;
      string KtzZQmemni;
      string oWQpEjSlyf;
      string gKmXyVABMk;
      string PYmalJSBLp;
      string gWDBAGEkZG;
      string SawurAGabt;
      string ldZCSQjoDt;
      string RQaIzKGlXq;
      string RPaFSobqhl;
      string DqZRDCxAij;
      string WOgeoCAnwh;
      string sUDjbWCTjd;
      string nrHQqZqJEw;
      string MGDmUDhuQQ;
      string nnuzsinpog;
      string AcQEudHPnP;
      string KqizUlQQOY;
      string nGDToAwHXI;
      if(DRbbcLJqko == RPaFSobqhl){lBTXwjpyqp = true;}
      else if(RPaFSobqhl == DRbbcLJqko){uXeSREIjGr = true;}
      if(dVaeqkNtaZ == DqZRDCxAij){wRHBFxEweG = true;}
      else if(DqZRDCxAij == dVaeqkNtaZ){OXQGIlKMwb = true;}
      if(KtzZQmemni == WOgeoCAnwh){RXaPssZwOu = true;}
      else if(WOgeoCAnwh == KtzZQmemni){YymHMGKrQG = true;}
      if(oWQpEjSlyf == sUDjbWCTjd){gzrfdJWLDk = true;}
      else if(sUDjbWCTjd == oWQpEjSlyf){PVmFbVrPEt = true;}
      if(gKmXyVABMk == nrHQqZqJEw){wSYYcVzCNr = true;}
      else if(nrHQqZqJEw == gKmXyVABMk){XmUwALDZqo = true;}
      if(PYmalJSBLp == MGDmUDhuQQ){wAcQqNZDdC = true;}
      else if(MGDmUDhuQQ == PYmalJSBLp){rVfmIxjWFL = true;}
      if(gWDBAGEkZG == nnuzsinpog){JsiwIwZbWu = true;}
      else if(nnuzsinpog == gWDBAGEkZG){sPSAbskKel = true;}
      if(SawurAGabt == AcQEudHPnP){ZrrsJyyCmX = true;}
      if(ldZCSQjoDt == KqizUlQQOY){tXhWzfWbnP = true;}
      if(RQaIzKGlXq == nGDToAwHXI){iTgAbDicPg = true;}
      while(AcQEudHPnP == SawurAGabt){stICEkcpGB = true;}
      while(KqizUlQQOY == KqizUlQQOY){DjAbNtozxd = true;}
      while(nGDToAwHXI == nGDToAwHXI){lUJrAHUTUH = true;}
      if(lBTXwjpyqp == true){lBTXwjpyqp = false;}
      if(wRHBFxEweG == true){wRHBFxEweG = false;}
      if(RXaPssZwOu == true){RXaPssZwOu = false;}
      if(gzrfdJWLDk == true){gzrfdJWLDk = false;}
      if(wSYYcVzCNr == true){wSYYcVzCNr = false;}
      if(wAcQqNZDdC == true){wAcQqNZDdC = false;}
      if(JsiwIwZbWu == true){JsiwIwZbWu = false;}
      if(ZrrsJyyCmX == true){ZrrsJyyCmX = false;}
      if(tXhWzfWbnP == true){tXhWzfWbnP = false;}
      if(iTgAbDicPg == true){iTgAbDicPg = false;}
      if(uXeSREIjGr == true){uXeSREIjGr = false;}
      if(OXQGIlKMwb == true){OXQGIlKMwb = false;}
      if(YymHMGKrQG == true){YymHMGKrQG = false;}
      if(PVmFbVrPEt == true){PVmFbVrPEt = false;}
      if(XmUwALDZqo == true){XmUwALDZqo = false;}
      if(rVfmIxjWFL == true){rVfmIxjWFL = false;}
      if(sPSAbskKel == true){sPSAbskKel = false;}
      if(stICEkcpGB == true){stICEkcpGB = false;}
      if(DjAbNtozxd == true){DjAbNtozxd = false;}
      if(lUJrAHUTUH == true){lUJrAHUTUH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NRQEYTVCTN
{ 
  void PJZjlzennt()
  { 
      bool nVDJZtzZpX = false;
      bool EfslmymOSg = false;
      bool oHlZuEYtfw = false;
      bool EwYUNPoCRw = false;
      bool BDYDNeIuPu = false;
      bool pETLffjdOV = false;
      bool VEssTHHYXX = false;
      bool IkwVekhiLP = false;
      bool wdekFzcMng = false;
      bool eLmwaxKfjF = false;
      bool XjWqlFHxft = false;
      bool yBRyYrYImT = false;
      bool etjprxxzuh = false;
      bool aCzGrLGnyA = false;
      bool qfftidtnWh = false;
      bool YBrPZdzgyo = false;
      bool HHByTwCLGN = false;
      bool kkKmbzNpHO = false;
      bool DIcNJYJifO = false;
      bool LZoIriehZl = false;
      string PULqGPnyDl;
      string tBDljHszQn;
      string fcUMWqYsEb;
      string hoVDWLRMsQ;
      string VOmWxyqaXi;
      string KfgVxlzyUO;
      string pttbEEfzOX;
      string ofFASRoxOX;
      string AyUVQCHzGk;
      string LTrdZaULSr;
      string SqMzteZgCe;
      string wBjwOrZXLC;
      string xfsdLVnaZr;
      string xdeVFIkUak;
      string bZxanKjuPg;
      string AwAPumyinY;
      string qyHKhSWNqF;
      string HFxZZWiRoB;
      string ksLrqAdOaR;
      string KCgCtcSlsU;
      if(PULqGPnyDl == SqMzteZgCe){nVDJZtzZpX = true;}
      else if(SqMzteZgCe == PULqGPnyDl){XjWqlFHxft = true;}
      if(tBDljHszQn == wBjwOrZXLC){EfslmymOSg = true;}
      else if(wBjwOrZXLC == tBDljHszQn){yBRyYrYImT = true;}
      if(fcUMWqYsEb == xfsdLVnaZr){oHlZuEYtfw = true;}
      else if(xfsdLVnaZr == fcUMWqYsEb){etjprxxzuh = true;}
      if(hoVDWLRMsQ == xdeVFIkUak){EwYUNPoCRw = true;}
      else if(xdeVFIkUak == hoVDWLRMsQ){aCzGrLGnyA = true;}
      if(VOmWxyqaXi == bZxanKjuPg){BDYDNeIuPu = true;}
      else if(bZxanKjuPg == VOmWxyqaXi){qfftidtnWh = true;}
      if(KfgVxlzyUO == AwAPumyinY){pETLffjdOV = true;}
      else if(AwAPumyinY == KfgVxlzyUO){YBrPZdzgyo = true;}
      if(pttbEEfzOX == qyHKhSWNqF){VEssTHHYXX = true;}
      else if(qyHKhSWNqF == pttbEEfzOX){HHByTwCLGN = true;}
      if(ofFASRoxOX == HFxZZWiRoB){IkwVekhiLP = true;}
      if(AyUVQCHzGk == ksLrqAdOaR){wdekFzcMng = true;}
      if(LTrdZaULSr == KCgCtcSlsU){eLmwaxKfjF = true;}
      while(HFxZZWiRoB == ofFASRoxOX){kkKmbzNpHO = true;}
      while(ksLrqAdOaR == ksLrqAdOaR){DIcNJYJifO = true;}
      while(KCgCtcSlsU == KCgCtcSlsU){LZoIriehZl = true;}
      if(nVDJZtzZpX == true){nVDJZtzZpX = false;}
      if(EfslmymOSg == true){EfslmymOSg = false;}
      if(oHlZuEYtfw == true){oHlZuEYtfw = false;}
      if(EwYUNPoCRw == true){EwYUNPoCRw = false;}
      if(BDYDNeIuPu == true){BDYDNeIuPu = false;}
      if(pETLffjdOV == true){pETLffjdOV = false;}
      if(VEssTHHYXX == true){VEssTHHYXX = false;}
      if(IkwVekhiLP == true){IkwVekhiLP = false;}
      if(wdekFzcMng == true){wdekFzcMng = false;}
      if(eLmwaxKfjF == true){eLmwaxKfjF = false;}
      if(XjWqlFHxft == true){XjWqlFHxft = false;}
      if(yBRyYrYImT == true){yBRyYrYImT = false;}
      if(etjprxxzuh == true){etjprxxzuh = false;}
      if(aCzGrLGnyA == true){aCzGrLGnyA = false;}
      if(qfftidtnWh == true){qfftidtnWh = false;}
      if(YBrPZdzgyo == true){YBrPZdzgyo = false;}
      if(HHByTwCLGN == true){HHByTwCLGN = false;}
      if(kkKmbzNpHO == true){kkKmbzNpHO = false;}
      if(DIcNJYJifO == true){DIcNJYJifO = false;}
      if(LZoIriehZl == true){LZoIriehZl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSBRBJUUWF
{ 
  void ntmWQejjMC()
  { 
      bool zSoiuQVTqC = false;
      bool IxzZwakRPM = false;
      bool ypgYHPSmOq = false;
      bool uqfGribELO = false;
      bool udYCIQTaad = false;
      bool XtswJIlPaf = false;
      bool xiFzGQQrgM = false;
      bool zfGAQTRePq = false;
      bool wqMjTAyjxi = false;
      bool xLcfQMYYur = false;
      bool zasNeqnreo = false;
      bool qHziiGWUfG = false;
      bool SgtyPmCaiE = false;
      bool uriXrUyzFb = false;
      bool LFEIqoMswK = false;
      bool pDrnYRguxq = false;
      bool nNIatzXaqO = false;
      bool IXPEtMclHZ = false;
      bool aJdYOqzuza = false;
      bool nCBNmyxcOr = false;
      string DZfcffeeNP;
      string fhuIddwuGX;
      string NjhNWkBMfP;
      string koMyEMVCYZ;
      string mHyCuiPlfK;
      string gmqwhSrRFt;
      string eRyxdqUwER;
      string IsWgkFkeSn;
      string VOgVixxPQk;
      string TDxdtUIBXD;
      string NThOCmQKLb;
      string gNzRYPkcOg;
      string sEeSxEwrlP;
      string xjHOZCgRTu;
      string glEoEFDfFe;
      string jelqJInOQx;
      string qXYuewGkqV;
      string iSJSAHApOq;
      string BQmHfRyPER;
      string NSAWEIMIJH;
      if(DZfcffeeNP == NThOCmQKLb){zSoiuQVTqC = true;}
      else if(NThOCmQKLb == DZfcffeeNP){zasNeqnreo = true;}
      if(fhuIddwuGX == gNzRYPkcOg){IxzZwakRPM = true;}
      else if(gNzRYPkcOg == fhuIddwuGX){qHziiGWUfG = true;}
      if(NjhNWkBMfP == sEeSxEwrlP){ypgYHPSmOq = true;}
      else if(sEeSxEwrlP == NjhNWkBMfP){SgtyPmCaiE = true;}
      if(koMyEMVCYZ == xjHOZCgRTu){uqfGribELO = true;}
      else if(xjHOZCgRTu == koMyEMVCYZ){uriXrUyzFb = true;}
      if(mHyCuiPlfK == glEoEFDfFe){udYCIQTaad = true;}
      else if(glEoEFDfFe == mHyCuiPlfK){LFEIqoMswK = true;}
      if(gmqwhSrRFt == jelqJInOQx){XtswJIlPaf = true;}
      else if(jelqJInOQx == gmqwhSrRFt){pDrnYRguxq = true;}
      if(eRyxdqUwER == qXYuewGkqV){xiFzGQQrgM = true;}
      else if(qXYuewGkqV == eRyxdqUwER){nNIatzXaqO = true;}
      if(IsWgkFkeSn == iSJSAHApOq){zfGAQTRePq = true;}
      if(VOgVixxPQk == BQmHfRyPER){wqMjTAyjxi = true;}
      if(TDxdtUIBXD == NSAWEIMIJH){xLcfQMYYur = true;}
      while(iSJSAHApOq == IsWgkFkeSn){IXPEtMclHZ = true;}
      while(BQmHfRyPER == BQmHfRyPER){aJdYOqzuza = true;}
      while(NSAWEIMIJH == NSAWEIMIJH){nCBNmyxcOr = true;}
      if(zSoiuQVTqC == true){zSoiuQVTqC = false;}
      if(IxzZwakRPM == true){IxzZwakRPM = false;}
      if(ypgYHPSmOq == true){ypgYHPSmOq = false;}
      if(uqfGribELO == true){uqfGribELO = false;}
      if(udYCIQTaad == true){udYCIQTaad = false;}
      if(XtswJIlPaf == true){XtswJIlPaf = false;}
      if(xiFzGQQrgM == true){xiFzGQQrgM = false;}
      if(zfGAQTRePq == true){zfGAQTRePq = false;}
      if(wqMjTAyjxi == true){wqMjTAyjxi = false;}
      if(xLcfQMYYur == true){xLcfQMYYur = false;}
      if(zasNeqnreo == true){zasNeqnreo = false;}
      if(qHziiGWUfG == true){qHziiGWUfG = false;}
      if(SgtyPmCaiE == true){SgtyPmCaiE = false;}
      if(uriXrUyzFb == true){uriXrUyzFb = false;}
      if(LFEIqoMswK == true){LFEIqoMswK = false;}
      if(pDrnYRguxq == true){pDrnYRguxq = false;}
      if(nNIatzXaqO == true){nNIatzXaqO = false;}
      if(IXPEtMclHZ == true){IXPEtMclHZ = false;}
      if(aJdYOqzuza == true){aJdYOqzuza = false;}
      if(nCBNmyxcOr == true){nCBNmyxcOr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JLOLLQYEQT
{ 
  void qcOGVZPQrW()
  { 
      bool RAbkydPnIl = false;
      bool sPDOSxUclN = false;
      bool bhKxtQNmJx = false;
      bool QxFlDHGrLT = false;
      bool fsuRIicnjG = false;
      bool fXxCKjpepg = false;
      bool PceLUwJRLL = false;
      bool qbRRgimrnL = false;
      bool nZDCRszCaT = false;
      bool RbBdDDOiwM = false;
      bool YKbYPDFfVa = false;
      bool wxperpZbtb = false;
      bool wHqrsPZmOc = false;
      bool UDwbldxdmN = false;
      bool mTfAWUkWkN = false;
      bool cloUPRTjeA = false;
      bool cRQrFsAOsO = false;
      bool ruofncapVY = false;
      bool dDCAziOaLT = false;
      bool KNzmjUCntd = false;
      string hTYSYiniAV;
      string iVMahtDOfA;
      string BGLcifSilc;
      string WpWdQHiozU;
      string FXXAGbPJjJ;
      string DTGYqaHujs;
      string QExXyrziKZ;
      string KOOLudiLWG;
      string PIycYDjxmo;
      string AmEGEBaABN;
      string cgyKyoFtdM;
      string rwXccHFTyu;
      string IBuVZWJHGs;
      string DiJJdiJndj;
      string yoTZwEOadw;
      string uGBGFakcka;
      string fxnjJJlOzs;
      string yRpNxSgVYV;
      string HhcKxwgDEC;
      string ygDCEABjPm;
      if(hTYSYiniAV == cgyKyoFtdM){RAbkydPnIl = true;}
      else if(cgyKyoFtdM == hTYSYiniAV){YKbYPDFfVa = true;}
      if(iVMahtDOfA == rwXccHFTyu){sPDOSxUclN = true;}
      else if(rwXccHFTyu == iVMahtDOfA){wxperpZbtb = true;}
      if(BGLcifSilc == IBuVZWJHGs){bhKxtQNmJx = true;}
      else if(IBuVZWJHGs == BGLcifSilc){wHqrsPZmOc = true;}
      if(WpWdQHiozU == DiJJdiJndj){QxFlDHGrLT = true;}
      else if(DiJJdiJndj == WpWdQHiozU){UDwbldxdmN = true;}
      if(FXXAGbPJjJ == yoTZwEOadw){fsuRIicnjG = true;}
      else if(yoTZwEOadw == FXXAGbPJjJ){mTfAWUkWkN = true;}
      if(DTGYqaHujs == uGBGFakcka){fXxCKjpepg = true;}
      else if(uGBGFakcka == DTGYqaHujs){cloUPRTjeA = true;}
      if(QExXyrziKZ == fxnjJJlOzs){PceLUwJRLL = true;}
      else if(fxnjJJlOzs == QExXyrziKZ){cRQrFsAOsO = true;}
      if(KOOLudiLWG == yRpNxSgVYV){qbRRgimrnL = true;}
      if(PIycYDjxmo == HhcKxwgDEC){nZDCRszCaT = true;}
      if(AmEGEBaABN == ygDCEABjPm){RbBdDDOiwM = true;}
      while(yRpNxSgVYV == KOOLudiLWG){ruofncapVY = true;}
      while(HhcKxwgDEC == HhcKxwgDEC){dDCAziOaLT = true;}
      while(ygDCEABjPm == ygDCEABjPm){KNzmjUCntd = true;}
      if(RAbkydPnIl == true){RAbkydPnIl = false;}
      if(sPDOSxUclN == true){sPDOSxUclN = false;}
      if(bhKxtQNmJx == true){bhKxtQNmJx = false;}
      if(QxFlDHGrLT == true){QxFlDHGrLT = false;}
      if(fsuRIicnjG == true){fsuRIicnjG = false;}
      if(fXxCKjpepg == true){fXxCKjpepg = false;}
      if(PceLUwJRLL == true){PceLUwJRLL = false;}
      if(qbRRgimrnL == true){qbRRgimrnL = false;}
      if(nZDCRszCaT == true){nZDCRszCaT = false;}
      if(RbBdDDOiwM == true){RbBdDDOiwM = false;}
      if(YKbYPDFfVa == true){YKbYPDFfVa = false;}
      if(wxperpZbtb == true){wxperpZbtb = false;}
      if(wHqrsPZmOc == true){wHqrsPZmOc = false;}
      if(UDwbldxdmN == true){UDwbldxdmN = false;}
      if(mTfAWUkWkN == true){mTfAWUkWkN = false;}
      if(cloUPRTjeA == true){cloUPRTjeA = false;}
      if(cRQrFsAOsO == true){cRQrFsAOsO = false;}
      if(ruofncapVY == true){ruofncapVY = false;}
      if(dDCAziOaLT == true){dDCAziOaLT = false;}
      if(KNzmjUCntd == true){KNzmjUCntd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHUVZHJAMH
{ 
  void YeGtsNjhOo()
  { 
      bool YqrHlfVjER = false;
      bool GGEiMCHIik = false;
      bool PTdTMFXmfF = false;
      bool SFncwbsGrk = false;
      bool NQPrdizrlx = false;
      bool wXSYSEMYug = false;
      bool IhDyzBRblk = false;
      bool JAPxXzDlpd = false;
      bool FfAiJulPKq = false;
      bool OTLLceNRsc = false;
      bool QXFBnwHVBT = false;
      bool AaiRachUoD = false;
      bool OCRuWonDTr = false;
      bool klrMMhZzuN = false;
      bool mPNpqmjtjA = false;
      bool xrboNNFKdy = false;
      bool HDBJhNiVEs = false;
      bool ChZbPyoaDj = false;
      bool EtTTtsKDzy = false;
      bool bPUwFjOEIc = false;
      string SmWeWyQEwI;
      string IOwZFICZHK;
      string VbjxGpWVcO;
      string CFEYcmRWpD;
      string ECVDmiIZET;
      string CfUDfqDYYf;
      string buahGDKXxS;
      string pfjDGSGfKW;
      string gxQILVjArk;
      string jsyJbJamxj;
      string YkblcWwQxM;
      string kWOBzedSVj;
      string SKeLhxhZbx;
      string rShaywUefo;
      string ZTCfAMewKw;
      string eIRNQNGPDf;
      string nVnAURnmDC;
      string JzmgJyHzLU;
      string SlOeRiBUJj;
      string pEazADfCKi;
      if(SmWeWyQEwI == YkblcWwQxM){YqrHlfVjER = true;}
      else if(YkblcWwQxM == SmWeWyQEwI){QXFBnwHVBT = true;}
      if(IOwZFICZHK == kWOBzedSVj){GGEiMCHIik = true;}
      else if(kWOBzedSVj == IOwZFICZHK){AaiRachUoD = true;}
      if(VbjxGpWVcO == SKeLhxhZbx){PTdTMFXmfF = true;}
      else if(SKeLhxhZbx == VbjxGpWVcO){OCRuWonDTr = true;}
      if(CFEYcmRWpD == rShaywUefo){SFncwbsGrk = true;}
      else if(rShaywUefo == CFEYcmRWpD){klrMMhZzuN = true;}
      if(ECVDmiIZET == ZTCfAMewKw){NQPrdizrlx = true;}
      else if(ZTCfAMewKw == ECVDmiIZET){mPNpqmjtjA = true;}
      if(CfUDfqDYYf == eIRNQNGPDf){wXSYSEMYug = true;}
      else if(eIRNQNGPDf == CfUDfqDYYf){xrboNNFKdy = true;}
      if(buahGDKXxS == nVnAURnmDC){IhDyzBRblk = true;}
      else if(nVnAURnmDC == buahGDKXxS){HDBJhNiVEs = true;}
      if(pfjDGSGfKW == JzmgJyHzLU){JAPxXzDlpd = true;}
      if(gxQILVjArk == SlOeRiBUJj){FfAiJulPKq = true;}
      if(jsyJbJamxj == pEazADfCKi){OTLLceNRsc = true;}
      while(JzmgJyHzLU == pfjDGSGfKW){ChZbPyoaDj = true;}
      while(SlOeRiBUJj == SlOeRiBUJj){EtTTtsKDzy = true;}
      while(pEazADfCKi == pEazADfCKi){bPUwFjOEIc = true;}
      if(YqrHlfVjER == true){YqrHlfVjER = false;}
      if(GGEiMCHIik == true){GGEiMCHIik = false;}
      if(PTdTMFXmfF == true){PTdTMFXmfF = false;}
      if(SFncwbsGrk == true){SFncwbsGrk = false;}
      if(NQPrdizrlx == true){NQPrdizrlx = false;}
      if(wXSYSEMYug == true){wXSYSEMYug = false;}
      if(IhDyzBRblk == true){IhDyzBRblk = false;}
      if(JAPxXzDlpd == true){JAPxXzDlpd = false;}
      if(FfAiJulPKq == true){FfAiJulPKq = false;}
      if(OTLLceNRsc == true){OTLLceNRsc = false;}
      if(QXFBnwHVBT == true){QXFBnwHVBT = false;}
      if(AaiRachUoD == true){AaiRachUoD = false;}
      if(OCRuWonDTr == true){OCRuWonDTr = false;}
      if(klrMMhZzuN == true){klrMMhZzuN = false;}
      if(mPNpqmjtjA == true){mPNpqmjtjA = false;}
      if(xrboNNFKdy == true){xrboNNFKdy = false;}
      if(HDBJhNiVEs == true){HDBJhNiVEs = false;}
      if(ChZbPyoaDj == true){ChZbPyoaDj = false;}
      if(EtTTtsKDzy == true){EtTTtsKDzy = false;}
      if(bPUwFjOEIc == true){bPUwFjOEIc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YNGJDOXCJC
{ 
  void jepIjehABS()
  { 
      bool TGZmDewXbT = false;
      bool HZONQrAYRE = false;
      bool wiyxANiAAN = false;
      bool dKnlpMKODh = false;
      bool rKXUyUiQhI = false;
      bool NKSaqkHblo = false;
      bool uwWNowlcWE = false;
      bool glUiLlKdzf = false;
      bool eSRrzTrNtF = false;
      bool FibOlwnJeC = false;
      bool hGsdabpiOF = false;
      bool ZccFKcdeNU = false;
      bool DYhRyyJFwP = false;
      bool xAyxxYZnQW = false;
      bool dJyoebFVEJ = false;
      bool SJwKyJXbec = false;
      bool SjlzHYeeIk = false;
      bool CoOpqtZslW = false;
      bool rmBlxnEnzm = false;
      bool AxJmEsWzgG = false;
      string neSdSUYOfo;
      string uNqMaEckPX;
      string MhrfwGCXwX;
      string tCBwMZnXff;
      string JwQrCZfhkN;
      string yqkzsFllhL;
      string SBRHusMtAA;
      string PFFiNPRAdV;
      string aTlhYCQBCG;
      string nCpUNHeIwI;
      string NkhjyslCkd;
      string nlILkyOihr;
      string bKrsMNPkVG;
      string jIDUIolBjf;
      string POPYSBsdiO;
      string ruZEgCsnXk;
      string dBfesehmDw;
      string LNzCbNuSZK;
      string TkBHNohznF;
      string uxdzBOijen;
      if(neSdSUYOfo == NkhjyslCkd){TGZmDewXbT = true;}
      else if(NkhjyslCkd == neSdSUYOfo){hGsdabpiOF = true;}
      if(uNqMaEckPX == nlILkyOihr){HZONQrAYRE = true;}
      else if(nlILkyOihr == uNqMaEckPX){ZccFKcdeNU = true;}
      if(MhrfwGCXwX == bKrsMNPkVG){wiyxANiAAN = true;}
      else if(bKrsMNPkVG == MhrfwGCXwX){DYhRyyJFwP = true;}
      if(tCBwMZnXff == jIDUIolBjf){dKnlpMKODh = true;}
      else if(jIDUIolBjf == tCBwMZnXff){xAyxxYZnQW = true;}
      if(JwQrCZfhkN == POPYSBsdiO){rKXUyUiQhI = true;}
      else if(POPYSBsdiO == JwQrCZfhkN){dJyoebFVEJ = true;}
      if(yqkzsFllhL == ruZEgCsnXk){NKSaqkHblo = true;}
      else if(ruZEgCsnXk == yqkzsFllhL){SJwKyJXbec = true;}
      if(SBRHusMtAA == dBfesehmDw){uwWNowlcWE = true;}
      else if(dBfesehmDw == SBRHusMtAA){SjlzHYeeIk = true;}
      if(PFFiNPRAdV == LNzCbNuSZK){glUiLlKdzf = true;}
      if(aTlhYCQBCG == TkBHNohznF){eSRrzTrNtF = true;}
      if(nCpUNHeIwI == uxdzBOijen){FibOlwnJeC = true;}
      while(LNzCbNuSZK == PFFiNPRAdV){CoOpqtZslW = true;}
      while(TkBHNohznF == TkBHNohznF){rmBlxnEnzm = true;}
      while(uxdzBOijen == uxdzBOijen){AxJmEsWzgG = true;}
      if(TGZmDewXbT == true){TGZmDewXbT = false;}
      if(HZONQrAYRE == true){HZONQrAYRE = false;}
      if(wiyxANiAAN == true){wiyxANiAAN = false;}
      if(dKnlpMKODh == true){dKnlpMKODh = false;}
      if(rKXUyUiQhI == true){rKXUyUiQhI = false;}
      if(NKSaqkHblo == true){NKSaqkHblo = false;}
      if(uwWNowlcWE == true){uwWNowlcWE = false;}
      if(glUiLlKdzf == true){glUiLlKdzf = false;}
      if(eSRrzTrNtF == true){eSRrzTrNtF = false;}
      if(FibOlwnJeC == true){FibOlwnJeC = false;}
      if(hGsdabpiOF == true){hGsdabpiOF = false;}
      if(ZccFKcdeNU == true){ZccFKcdeNU = false;}
      if(DYhRyyJFwP == true){DYhRyyJFwP = false;}
      if(xAyxxYZnQW == true){xAyxxYZnQW = false;}
      if(dJyoebFVEJ == true){dJyoebFVEJ = false;}
      if(SJwKyJXbec == true){SJwKyJXbec = false;}
      if(SjlzHYeeIk == true){SjlzHYeeIk = false;}
      if(CoOpqtZslW == true){CoOpqtZslW = false;}
      if(rmBlxnEnzm == true){rmBlxnEnzm = false;}
      if(AxJmEsWzgG == true){AxJmEsWzgG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXYTNTLBJX
{ 
  void GmsgRnWweD()
  { 
      bool xyJJodVfjH = false;
      bool wycsnpRRzP = false;
      bool cWgHkiGYMp = false;
      bool TYbQWkoSMQ = false;
      bool ofAButedWx = false;
      bool iTJTNaRCXG = false;
      bool XwTtnXWLWC = false;
      bool AyEhZwVeLp = false;
      bool DcCPGzOHCu = false;
      bool SmtGssLGNX = false;
      bool XSGTwkPatQ = false;
      bool FlphCttEmn = false;
      bool IOIbjNEyog = false;
      bool kORnSkVhSV = false;
      bool jnNlpfwMDz = false;
      bool yHTYOIKeji = false;
      bool fQlMfqUCOR = false;
      bool XLkQETBWlD = false;
      bool QqtohcusYJ = false;
      bool aqyjoSCAFz = false;
      string xXxLNdExTw;
      string YeDrVidiBt;
      string GPdoAqiOAO;
      string FEketUIptH;
      string PTODsLFUnV;
      string lAwedhtHKV;
      string upwFqUsXyA;
      string ZnotdmBZuo;
      string lNZebFIFBL;
      string ZBeXMZWIMY;
      string RgWnwyKBAq;
      string gUMVigQRck;
      string LmWlZYIQhE;
      string PrMVWEqlhc;
      string tGFKeFnJne;
      string IEfaNeKjNX;
      string psTuanHpze;
      string peizqFhLHT;
      string jzbCuKLkIr;
      string sHXKmAlJjp;
      if(xXxLNdExTw == RgWnwyKBAq){xyJJodVfjH = true;}
      else if(RgWnwyKBAq == xXxLNdExTw){XSGTwkPatQ = true;}
      if(YeDrVidiBt == gUMVigQRck){wycsnpRRzP = true;}
      else if(gUMVigQRck == YeDrVidiBt){FlphCttEmn = true;}
      if(GPdoAqiOAO == LmWlZYIQhE){cWgHkiGYMp = true;}
      else if(LmWlZYIQhE == GPdoAqiOAO){IOIbjNEyog = true;}
      if(FEketUIptH == PrMVWEqlhc){TYbQWkoSMQ = true;}
      else if(PrMVWEqlhc == FEketUIptH){kORnSkVhSV = true;}
      if(PTODsLFUnV == tGFKeFnJne){ofAButedWx = true;}
      else if(tGFKeFnJne == PTODsLFUnV){jnNlpfwMDz = true;}
      if(lAwedhtHKV == IEfaNeKjNX){iTJTNaRCXG = true;}
      else if(IEfaNeKjNX == lAwedhtHKV){yHTYOIKeji = true;}
      if(upwFqUsXyA == psTuanHpze){XwTtnXWLWC = true;}
      else if(psTuanHpze == upwFqUsXyA){fQlMfqUCOR = true;}
      if(ZnotdmBZuo == peizqFhLHT){AyEhZwVeLp = true;}
      if(lNZebFIFBL == jzbCuKLkIr){DcCPGzOHCu = true;}
      if(ZBeXMZWIMY == sHXKmAlJjp){SmtGssLGNX = true;}
      while(peizqFhLHT == ZnotdmBZuo){XLkQETBWlD = true;}
      while(jzbCuKLkIr == jzbCuKLkIr){QqtohcusYJ = true;}
      while(sHXKmAlJjp == sHXKmAlJjp){aqyjoSCAFz = true;}
      if(xyJJodVfjH == true){xyJJodVfjH = false;}
      if(wycsnpRRzP == true){wycsnpRRzP = false;}
      if(cWgHkiGYMp == true){cWgHkiGYMp = false;}
      if(TYbQWkoSMQ == true){TYbQWkoSMQ = false;}
      if(ofAButedWx == true){ofAButedWx = false;}
      if(iTJTNaRCXG == true){iTJTNaRCXG = false;}
      if(XwTtnXWLWC == true){XwTtnXWLWC = false;}
      if(AyEhZwVeLp == true){AyEhZwVeLp = false;}
      if(DcCPGzOHCu == true){DcCPGzOHCu = false;}
      if(SmtGssLGNX == true){SmtGssLGNX = false;}
      if(XSGTwkPatQ == true){XSGTwkPatQ = false;}
      if(FlphCttEmn == true){FlphCttEmn = false;}
      if(IOIbjNEyog == true){IOIbjNEyog = false;}
      if(kORnSkVhSV == true){kORnSkVhSV = false;}
      if(jnNlpfwMDz == true){jnNlpfwMDz = false;}
      if(yHTYOIKeji == true){yHTYOIKeji = false;}
      if(fQlMfqUCOR == true){fQlMfqUCOR = false;}
      if(XLkQETBWlD == true){XLkQETBWlD = false;}
      if(QqtohcusYJ == true){QqtohcusYJ = false;}
      if(aqyjoSCAFz == true){aqyjoSCAFz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YERPSFSTPX
{ 
  void MKihoiVcLb()
  { 
      bool dECNUGhoqg = false;
      bool ndUOdQtCZN = false;
      bool aTVNxkrHfT = false;
      bool ZXbtLNSBOr = false;
      bool yyYizEdzlU = false;
      bool eZCumKhnQi = false;
      bool NaIWGPBaCP = false;
      bool xsngPculNs = false;
      bool HsULnAVfGB = false;
      bool edkeeWoBci = false;
      bool CCxVWllVeK = false;
      bool PuaWbUFwhF = false;
      bool tUUAkSIJBr = false;
      bool msJeqEuznC = false;
      bool OzBwliDNCK = false;
      bool RrSWnghxkE = false;
      bool cbTmWVlueX = false;
      bool YGIfqtTXNC = false;
      bool OtGqatalpK = false;
      bool VyNjZlfNYQ = false;
      string CRIePemIJn;
      string kFWICJVjel;
      string PDPRnjblIp;
      string FaTukAVTDW;
      string mnNyNYgkKr;
      string KAjiIyBqpf;
      string DAzTiJkbWC;
      string mBgIyboQEO;
      string CpaQfEqkll;
      string yddWSlotPD;
      string nFNIEJTbjg;
      string JkmacNZimd;
      string SApkDIXJoL;
      string ltBAaxcSLV;
      string jPAEcNqCtF;
      string MFGkjnPcEu;
      string kKlYtOilAf;
      string kGXRtDzkHp;
      string RUPizgnPQm;
      string hzNPkZcbJN;
      if(CRIePemIJn == nFNIEJTbjg){dECNUGhoqg = true;}
      else if(nFNIEJTbjg == CRIePemIJn){CCxVWllVeK = true;}
      if(kFWICJVjel == JkmacNZimd){ndUOdQtCZN = true;}
      else if(JkmacNZimd == kFWICJVjel){PuaWbUFwhF = true;}
      if(PDPRnjblIp == SApkDIXJoL){aTVNxkrHfT = true;}
      else if(SApkDIXJoL == PDPRnjblIp){tUUAkSIJBr = true;}
      if(FaTukAVTDW == ltBAaxcSLV){ZXbtLNSBOr = true;}
      else if(ltBAaxcSLV == FaTukAVTDW){msJeqEuznC = true;}
      if(mnNyNYgkKr == jPAEcNqCtF){yyYizEdzlU = true;}
      else if(jPAEcNqCtF == mnNyNYgkKr){OzBwliDNCK = true;}
      if(KAjiIyBqpf == MFGkjnPcEu){eZCumKhnQi = true;}
      else if(MFGkjnPcEu == KAjiIyBqpf){RrSWnghxkE = true;}
      if(DAzTiJkbWC == kKlYtOilAf){NaIWGPBaCP = true;}
      else if(kKlYtOilAf == DAzTiJkbWC){cbTmWVlueX = true;}
      if(mBgIyboQEO == kGXRtDzkHp){xsngPculNs = true;}
      if(CpaQfEqkll == RUPizgnPQm){HsULnAVfGB = true;}
      if(yddWSlotPD == hzNPkZcbJN){edkeeWoBci = true;}
      while(kGXRtDzkHp == mBgIyboQEO){YGIfqtTXNC = true;}
      while(RUPizgnPQm == RUPizgnPQm){OtGqatalpK = true;}
      while(hzNPkZcbJN == hzNPkZcbJN){VyNjZlfNYQ = true;}
      if(dECNUGhoqg == true){dECNUGhoqg = false;}
      if(ndUOdQtCZN == true){ndUOdQtCZN = false;}
      if(aTVNxkrHfT == true){aTVNxkrHfT = false;}
      if(ZXbtLNSBOr == true){ZXbtLNSBOr = false;}
      if(yyYizEdzlU == true){yyYizEdzlU = false;}
      if(eZCumKhnQi == true){eZCumKhnQi = false;}
      if(NaIWGPBaCP == true){NaIWGPBaCP = false;}
      if(xsngPculNs == true){xsngPculNs = false;}
      if(HsULnAVfGB == true){HsULnAVfGB = false;}
      if(edkeeWoBci == true){edkeeWoBci = false;}
      if(CCxVWllVeK == true){CCxVWllVeK = false;}
      if(PuaWbUFwhF == true){PuaWbUFwhF = false;}
      if(tUUAkSIJBr == true){tUUAkSIJBr = false;}
      if(msJeqEuznC == true){msJeqEuznC = false;}
      if(OzBwliDNCK == true){OzBwliDNCK = false;}
      if(RrSWnghxkE == true){RrSWnghxkE = false;}
      if(cbTmWVlueX == true){cbTmWVlueX = false;}
      if(YGIfqtTXNC == true){YGIfqtTXNC = false;}
      if(OtGqatalpK == true){OtGqatalpK = false;}
      if(VyNjZlfNYQ == true){VyNjZlfNYQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUAKTARZPR
{ 
  void zZtnQwTlOT()
  { 
      bool QbADYXnXxT = false;
      bool FGJPONrSDg = false;
      bool tpAlycVciV = false;
      bool UlNKYaRYRd = false;
      bool EkEYEzwJKV = false;
      bool CbZJdZbNEw = false;
      bool CLnayTszpn = false;
      bool uTAZbIkahz = false;
      bool fLRNTrMEgz = false;
      bool yETUasxdZk = false;
      bool GxSVahbzgU = false;
      bool nAfFQptaHG = false;
      bool HnRqpqAfyi = false;
      bool LHBwshsumk = false;
      bool QMWLKyXNEj = false;
      bool zWVTdRfafi = false;
      bool huByJgyiMh = false;
      bool xymWotRFgq = false;
      bool SlbOjolhSb = false;
      bool CRPDDULXCd = false;
      string SZdBopRMxm;
      string DJIsCLqEcT;
      string krGYaYzGkB;
      string kSALEkxAri;
      string ENUwpcctVD;
      string nQEpiZTFaQ;
      string pKbwBjIxoQ;
      string OpLtOWXKiy;
      string uFjgNUOKbd;
      string RqZbsslYtF;
      string TeEFoxEJaL;
      string CIWbUjathg;
      string UyUKzWQjAU;
      string kzPceQAerP;
      string PEiQbJUxHI;
      string SqpNjUKsFR;
      string fUJFaDrsxE;
      string iuCSQPPDip;
      string CSbqCsICsK;
      string FGZZiuucpX;
      if(SZdBopRMxm == TeEFoxEJaL){QbADYXnXxT = true;}
      else if(TeEFoxEJaL == SZdBopRMxm){GxSVahbzgU = true;}
      if(DJIsCLqEcT == CIWbUjathg){FGJPONrSDg = true;}
      else if(CIWbUjathg == DJIsCLqEcT){nAfFQptaHG = true;}
      if(krGYaYzGkB == UyUKzWQjAU){tpAlycVciV = true;}
      else if(UyUKzWQjAU == krGYaYzGkB){HnRqpqAfyi = true;}
      if(kSALEkxAri == kzPceQAerP){UlNKYaRYRd = true;}
      else if(kzPceQAerP == kSALEkxAri){LHBwshsumk = true;}
      if(ENUwpcctVD == PEiQbJUxHI){EkEYEzwJKV = true;}
      else if(PEiQbJUxHI == ENUwpcctVD){QMWLKyXNEj = true;}
      if(nQEpiZTFaQ == SqpNjUKsFR){CbZJdZbNEw = true;}
      else if(SqpNjUKsFR == nQEpiZTFaQ){zWVTdRfafi = true;}
      if(pKbwBjIxoQ == fUJFaDrsxE){CLnayTszpn = true;}
      else if(fUJFaDrsxE == pKbwBjIxoQ){huByJgyiMh = true;}
      if(OpLtOWXKiy == iuCSQPPDip){uTAZbIkahz = true;}
      if(uFjgNUOKbd == CSbqCsICsK){fLRNTrMEgz = true;}
      if(RqZbsslYtF == FGZZiuucpX){yETUasxdZk = true;}
      while(iuCSQPPDip == OpLtOWXKiy){xymWotRFgq = true;}
      while(CSbqCsICsK == CSbqCsICsK){SlbOjolhSb = true;}
      while(FGZZiuucpX == FGZZiuucpX){CRPDDULXCd = true;}
      if(QbADYXnXxT == true){QbADYXnXxT = false;}
      if(FGJPONrSDg == true){FGJPONrSDg = false;}
      if(tpAlycVciV == true){tpAlycVciV = false;}
      if(UlNKYaRYRd == true){UlNKYaRYRd = false;}
      if(EkEYEzwJKV == true){EkEYEzwJKV = false;}
      if(CbZJdZbNEw == true){CbZJdZbNEw = false;}
      if(CLnayTszpn == true){CLnayTszpn = false;}
      if(uTAZbIkahz == true){uTAZbIkahz = false;}
      if(fLRNTrMEgz == true){fLRNTrMEgz = false;}
      if(yETUasxdZk == true){yETUasxdZk = false;}
      if(GxSVahbzgU == true){GxSVahbzgU = false;}
      if(nAfFQptaHG == true){nAfFQptaHG = false;}
      if(HnRqpqAfyi == true){HnRqpqAfyi = false;}
      if(LHBwshsumk == true){LHBwshsumk = false;}
      if(QMWLKyXNEj == true){QMWLKyXNEj = false;}
      if(zWVTdRfafi == true){zWVTdRfafi = false;}
      if(huByJgyiMh == true){huByJgyiMh = false;}
      if(xymWotRFgq == true){xymWotRFgq = false;}
      if(SlbOjolhSb == true){SlbOjolhSb = false;}
      if(CRPDDULXCd == true){CRPDDULXCd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGDEZJVBWY
{ 
  void XcfSErJPVN()
  { 
      bool MaqqlEBdcE = false;
      bool DPTEDGqpQE = false;
      bool PmfEWVhsrW = false;
      bool pqJswpkwgS = false;
      bool OKskJadPRO = false;
      bool VIZAOYtmTP = false;
      bool VHlGNMGaHM = false;
      bool VuIyoEtuuw = false;
      bool qSbcBhRIdW = false;
      bool uybRwHYmWw = false;
      bool UCIEsazbKK = false;
      bool eyqXXDfIEf = false;
      bool txxjQXSqCh = false;
      bool fHXyboKWjZ = false;
      bool hoyTrwGEsr = false;
      bool aPhqCXFXmU = false;
      bool HIZcdXaswi = false;
      bool sIYeyEzcrT = false;
      bool QOyJGPYgwE = false;
      bool iliOSZPUoU = false;
      string dmlYiWgsuU;
      string DtqilwAnHZ;
      string sxPGIQVUTD;
      string YPjbEngpGR;
      string DsDnfJeerx;
      string eGXnBgWfQS;
      string BMZrwnJOey;
      string OKgoVzsbaz;
      string kpbWYRqwaW;
      string RBZnQqSLqq;
      string zQAthTYhRB;
      string mtEQhKjDSd;
      string xMmHfNksYd;
      string fhjizTphoE;
      string sIeZjWwIFF;
      string HPrNslcrNT;
      string ieJnUFJVRN;
      string TCONkohNXJ;
      string QbnSWQoWoM;
      string pyTUVNypEe;
      if(dmlYiWgsuU == zQAthTYhRB){MaqqlEBdcE = true;}
      else if(zQAthTYhRB == dmlYiWgsuU){UCIEsazbKK = true;}
      if(DtqilwAnHZ == mtEQhKjDSd){DPTEDGqpQE = true;}
      else if(mtEQhKjDSd == DtqilwAnHZ){eyqXXDfIEf = true;}
      if(sxPGIQVUTD == xMmHfNksYd){PmfEWVhsrW = true;}
      else if(xMmHfNksYd == sxPGIQVUTD){txxjQXSqCh = true;}
      if(YPjbEngpGR == fhjizTphoE){pqJswpkwgS = true;}
      else if(fhjizTphoE == YPjbEngpGR){fHXyboKWjZ = true;}
      if(DsDnfJeerx == sIeZjWwIFF){OKskJadPRO = true;}
      else if(sIeZjWwIFF == DsDnfJeerx){hoyTrwGEsr = true;}
      if(eGXnBgWfQS == HPrNslcrNT){VIZAOYtmTP = true;}
      else if(HPrNslcrNT == eGXnBgWfQS){aPhqCXFXmU = true;}
      if(BMZrwnJOey == ieJnUFJVRN){VHlGNMGaHM = true;}
      else if(ieJnUFJVRN == BMZrwnJOey){HIZcdXaswi = true;}
      if(OKgoVzsbaz == TCONkohNXJ){VuIyoEtuuw = true;}
      if(kpbWYRqwaW == QbnSWQoWoM){qSbcBhRIdW = true;}
      if(RBZnQqSLqq == pyTUVNypEe){uybRwHYmWw = true;}
      while(TCONkohNXJ == OKgoVzsbaz){sIYeyEzcrT = true;}
      while(QbnSWQoWoM == QbnSWQoWoM){QOyJGPYgwE = true;}
      while(pyTUVNypEe == pyTUVNypEe){iliOSZPUoU = true;}
      if(MaqqlEBdcE == true){MaqqlEBdcE = false;}
      if(DPTEDGqpQE == true){DPTEDGqpQE = false;}
      if(PmfEWVhsrW == true){PmfEWVhsrW = false;}
      if(pqJswpkwgS == true){pqJswpkwgS = false;}
      if(OKskJadPRO == true){OKskJadPRO = false;}
      if(VIZAOYtmTP == true){VIZAOYtmTP = false;}
      if(VHlGNMGaHM == true){VHlGNMGaHM = false;}
      if(VuIyoEtuuw == true){VuIyoEtuuw = false;}
      if(qSbcBhRIdW == true){qSbcBhRIdW = false;}
      if(uybRwHYmWw == true){uybRwHYmWw = false;}
      if(UCIEsazbKK == true){UCIEsazbKK = false;}
      if(eyqXXDfIEf == true){eyqXXDfIEf = false;}
      if(txxjQXSqCh == true){txxjQXSqCh = false;}
      if(fHXyboKWjZ == true){fHXyboKWjZ = false;}
      if(hoyTrwGEsr == true){hoyTrwGEsr = false;}
      if(aPhqCXFXmU == true){aPhqCXFXmU = false;}
      if(HIZcdXaswi == true){HIZcdXaswi = false;}
      if(sIYeyEzcrT == true){sIYeyEzcrT = false;}
      if(QOyJGPYgwE == true){QOyJGPYgwE = false;}
      if(iliOSZPUoU == true){iliOSZPUoU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQAAWKXEDP
{ 
  void HtIqpyXyrn()
  { 
      bool TwpIilNoiJ = false;
      bool EywkKZfzfH = false;
      bool xQqhcBYIje = false;
      bool guRqugUtsM = false;
      bool rIYDSRaKQO = false;
      bool hREhhDFHeg = false;
      bool MEFEbJfEod = false;
      bool FlGTOnqmPK = false;
      bool ZNrVxPpiIr = false;
      bool bMPLznCUaJ = false;
      bool kVVlIwKkTs = false;
      bool LRrTHzLjGM = false;
      bool SxuwCsWuTa = false;
      bool lWMGYDqFMB = false;
      bool EFPPgJTuEA = false;
      bool bSNOqnZYjP = false;
      bool ZPRrHnFltD = false;
      bool HGXFHMgfPr = false;
      bool YaqSzSIxOk = false;
      bool dSVxaonXHr = false;
      string kNXXBrFCxV;
      string UNaEenhxId;
      string mCyWTsPePf;
      string uXQqTReOZA;
      string zkdtyeDEWe;
      string MKTPUhOADH;
      string bZlRawxikM;
      string JSWIdCYEYo;
      string pLHkTjEBWk;
      string DdKSYYyLSB;
      string gTTKUsmLkR;
      string IKbOQQSAyp;
      string rwMzJfHEjF;
      string DMkWIWqxQZ;
      string xsPEbsBwBH;
      string GxNcJjGTBo;
      string kibeNwYEGs;
      string YUjXszfIWP;
      string dLCbyGyINX;
      string QXwanNRkpf;
      if(kNXXBrFCxV == gTTKUsmLkR){TwpIilNoiJ = true;}
      else if(gTTKUsmLkR == kNXXBrFCxV){kVVlIwKkTs = true;}
      if(UNaEenhxId == IKbOQQSAyp){EywkKZfzfH = true;}
      else if(IKbOQQSAyp == UNaEenhxId){LRrTHzLjGM = true;}
      if(mCyWTsPePf == rwMzJfHEjF){xQqhcBYIje = true;}
      else if(rwMzJfHEjF == mCyWTsPePf){SxuwCsWuTa = true;}
      if(uXQqTReOZA == DMkWIWqxQZ){guRqugUtsM = true;}
      else if(DMkWIWqxQZ == uXQqTReOZA){lWMGYDqFMB = true;}
      if(zkdtyeDEWe == xsPEbsBwBH){rIYDSRaKQO = true;}
      else if(xsPEbsBwBH == zkdtyeDEWe){EFPPgJTuEA = true;}
      if(MKTPUhOADH == GxNcJjGTBo){hREhhDFHeg = true;}
      else if(GxNcJjGTBo == MKTPUhOADH){bSNOqnZYjP = true;}
      if(bZlRawxikM == kibeNwYEGs){MEFEbJfEod = true;}
      else if(kibeNwYEGs == bZlRawxikM){ZPRrHnFltD = true;}
      if(JSWIdCYEYo == YUjXszfIWP){FlGTOnqmPK = true;}
      if(pLHkTjEBWk == dLCbyGyINX){ZNrVxPpiIr = true;}
      if(DdKSYYyLSB == QXwanNRkpf){bMPLznCUaJ = true;}
      while(YUjXszfIWP == JSWIdCYEYo){HGXFHMgfPr = true;}
      while(dLCbyGyINX == dLCbyGyINX){YaqSzSIxOk = true;}
      while(QXwanNRkpf == QXwanNRkpf){dSVxaonXHr = true;}
      if(TwpIilNoiJ == true){TwpIilNoiJ = false;}
      if(EywkKZfzfH == true){EywkKZfzfH = false;}
      if(xQqhcBYIje == true){xQqhcBYIje = false;}
      if(guRqugUtsM == true){guRqugUtsM = false;}
      if(rIYDSRaKQO == true){rIYDSRaKQO = false;}
      if(hREhhDFHeg == true){hREhhDFHeg = false;}
      if(MEFEbJfEod == true){MEFEbJfEod = false;}
      if(FlGTOnqmPK == true){FlGTOnqmPK = false;}
      if(ZNrVxPpiIr == true){ZNrVxPpiIr = false;}
      if(bMPLznCUaJ == true){bMPLznCUaJ = false;}
      if(kVVlIwKkTs == true){kVVlIwKkTs = false;}
      if(LRrTHzLjGM == true){LRrTHzLjGM = false;}
      if(SxuwCsWuTa == true){SxuwCsWuTa = false;}
      if(lWMGYDqFMB == true){lWMGYDqFMB = false;}
      if(EFPPgJTuEA == true){EFPPgJTuEA = false;}
      if(bSNOqnZYjP == true){bSNOqnZYjP = false;}
      if(ZPRrHnFltD == true){ZPRrHnFltD = false;}
      if(HGXFHMgfPr == true){HGXFHMgfPr = false;}
      if(YaqSzSIxOk == true){YaqSzSIxOk = false;}
      if(dSVxaonXHr == true){dSVxaonXHr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWITXWBGEQ
{ 
  void fuDWPUsioH()
  { 
      bool gRZOCYcpqb = false;
      bool wMjNrRZwLI = false;
      bool azfremNAoL = false;
      bool TEVGGwGtTY = false;
      bool idorVOgXal = false;
      bool zYczQgkhiP = false;
      bool KcBfHrpdGu = false;
      bool KfcmYwJmVQ = false;
      bool FpYCLtaWoY = false;
      bool KYKENGbJjc = false;
      bool XDRfbTupZT = false;
      bool XyLSJUDzTM = false;
      bool QTngjlUXZS = false;
      bool TACrrCYsZr = false;
      bool zkwVBMMqtr = false;
      bool CboWLDOjuo = false;
      bool yXQGzWuTaH = false;
      bool wKZbNfXSfX = false;
      bool ZddgQqKffn = false;
      bool nnyjsbUpVd = false;
      string SnHwSrRlUX;
      string xGFEdAiKfO;
      string AfRrncRsfF;
      string IempbZRMjn;
      string hyukMzMwFT;
      string lmqKhlWPIo;
      string aYGOOSSPbD;
      string hWZrfCkfeo;
      string PUmLSVncIo;
      string DCEuNJrfVt;
      string fxUBlPNyee;
      string BpjTYFktws;
      string dpGlAfReeV;
      string KFJjIRAlZC;
      string HoxcnMRkVH;
      string XxjcQophAG;
      string yhTIUwfAKG;
      string EzTskordym;
      string NgIWxMUgTS;
      string bRkTEZVnHq;
      if(SnHwSrRlUX == fxUBlPNyee){gRZOCYcpqb = true;}
      else if(fxUBlPNyee == SnHwSrRlUX){XDRfbTupZT = true;}
      if(xGFEdAiKfO == BpjTYFktws){wMjNrRZwLI = true;}
      else if(BpjTYFktws == xGFEdAiKfO){XyLSJUDzTM = true;}
      if(AfRrncRsfF == dpGlAfReeV){azfremNAoL = true;}
      else if(dpGlAfReeV == AfRrncRsfF){QTngjlUXZS = true;}
      if(IempbZRMjn == KFJjIRAlZC){TEVGGwGtTY = true;}
      else if(KFJjIRAlZC == IempbZRMjn){TACrrCYsZr = true;}
      if(hyukMzMwFT == HoxcnMRkVH){idorVOgXal = true;}
      else if(HoxcnMRkVH == hyukMzMwFT){zkwVBMMqtr = true;}
      if(lmqKhlWPIo == XxjcQophAG){zYczQgkhiP = true;}
      else if(XxjcQophAG == lmqKhlWPIo){CboWLDOjuo = true;}
      if(aYGOOSSPbD == yhTIUwfAKG){KcBfHrpdGu = true;}
      else if(yhTIUwfAKG == aYGOOSSPbD){yXQGzWuTaH = true;}
      if(hWZrfCkfeo == EzTskordym){KfcmYwJmVQ = true;}
      if(PUmLSVncIo == NgIWxMUgTS){FpYCLtaWoY = true;}
      if(DCEuNJrfVt == bRkTEZVnHq){KYKENGbJjc = true;}
      while(EzTskordym == hWZrfCkfeo){wKZbNfXSfX = true;}
      while(NgIWxMUgTS == NgIWxMUgTS){ZddgQqKffn = true;}
      while(bRkTEZVnHq == bRkTEZVnHq){nnyjsbUpVd = true;}
      if(gRZOCYcpqb == true){gRZOCYcpqb = false;}
      if(wMjNrRZwLI == true){wMjNrRZwLI = false;}
      if(azfremNAoL == true){azfremNAoL = false;}
      if(TEVGGwGtTY == true){TEVGGwGtTY = false;}
      if(idorVOgXal == true){idorVOgXal = false;}
      if(zYczQgkhiP == true){zYczQgkhiP = false;}
      if(KcBfHrpdGu == true){KcBfHrpdGu = false;}
      if(KfcmYwJmVQ == true){KfcmYwJmVQ = false;}
      if(FpYCLtaWoY == true){FpYCLtaWoY = false;}
      if(KYKENGbJjc == true){KYKENGbJjc = false;}
      if(XDRfbTupZT == true){XDRfbTupZT = false;}
      if(XyLSJUDzTM == true){XyLSJUDzTM = false;}
      if(QTngjlUXZS == true){QTngjlUXZS = false;}
      if(TACrrCYsZr == true){TACrrCYsZr = false;}
      if(zkwVBMMqtr == true){zkwVBMMqtr = false;}
      if(CboWLDOjuo == true){CboWLDOjuo = false;}
      if(yXQGzWuTaH == true){yXQGzWuTaH = false;}
      if(wKZbNfXSfX == true){wKZbNfXSfX = false;}
      if(ZddgQqKffn == true){ZddgQqKffn = false;}
      if(nnyjsbUpVd == true){nnyjsbUpVd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZWLOCEBVN
{ 
  void sjEEwKSdHx()
  { 
      bool UjMafBETIP = false;
      bool wAEsfBsuTy = false;
      bool FNZnsInHbt = false;
      bool DnlSbkGDIS = false;
      bool AjGWQbUwSf = false;
      bool iLhAYHKXgX = false;
      bool MwqOLIOlQt = false;
      bool tpmAyUGCXQ = false;
      bool nrouLqFlsT = false;
      bool ahVjGDsqLH = false;
      bool NheXlsXhCE = false;
      bool AHzPjUHwDT = false;
      bool CbswTLTDtu = false;
      bool bPqPCFMQJS = false;
      bool TXjnTShFAk = false;
      bool uwnqFkohEZ = false;
      bool YUmGckPiNd = false;
      bool IqljAerEcA = false;
      bool cOCJzeaAKR = false;
      bool QdLisyjcLh = false;
      string kkRJrmtwUY;
      string WQZFIXcQSB;
      string VYQBrTPUXE;
      string FoGSpqkfHt;
      string NoDUKbfCDF;
      string zHLbyLUPQY;
      string WZYPTgKGPR;
      string lxJYnfUwqQ;
      string mNQSExddTe;
      string WUOhWnQnBd;
      string RYlkSCylnS;
      string pXYAkIIFLV;
      string DfmkuRhaCz;
      string PguMyOaezB;
      string zqpBnywOxN;
      string eKceallBpB;
      string UWjnCJcLBV;
      string hdGJVLokwx;
      string VTdnUEEPlM;
      string cYoygbHByd;
      if(kkRJrmtwUY == RYlkSCylnS){UjMafBETIP = true;}
      else if(RYlkSCylnS == kkRJrmtwUY){NheXlsXhCE = true;}
      if(WQZFIXcQSB == pXYAkIIFLV){wAEsfBsuTy = true;}
      else if(pXYAkIIFLV == WQZFIXcQSB){AHzPjUHwDT = true;}
      if(VYQBrTPUXE == DfmkuRhaCz){FNZnsInHbt = true;}
      else if(DfmkuRhaCz == VYQBrTPUXE){CbswTLTDtu = true;}
      if(FoGSpqkfHt == PguMyOaezB){DnlSbkGDIS = true;}
      else if(PguMyOaezB == FoGSpqkfHt){bPqPCFMQJS = true;}
      if(NoDUKbfCDF == zqpBnywOxN){AjGWQbUwSf = true;}
      else if(zqpBnywOxN == NoDUKbfCDF){TXjnTShFAk = true;}
      if(zHLbyLUPQY == eKceallBpB){iLhAYHKXgX = true;}
      else if(eKceallBpB == zHLbyLUPQY){uwnqFkohEZ = true;}
      if(WZYPTgKGPR == UWjnCJcLBV){MwqOLIOlQt = true;}
      else if(UWjnCJcLBV == WZYPTgKGPR){YUmGckPiNd = true;}
      if(lxJYnfUwqQ == hdGJVLokwx){tpmAyUGCXQ = true;}
      if(mNQSExddTe == VTdnUEEPlM){nrouLqFlsT = true;}
      if(WUOhWnQnBd == cYoygbHByd){ahVjGDsqLH = true;}
      while(hdGJVLokwx == lxJYnfUwqQ){IqljAerEcA = true;}
      while(VTdnUEEPlM == VTdnUEEPlM){cOCJzeaAKR = true;}
      while(cYoygbHByd == cYoygbHByd){QdLisyjcLh = true;}
      if(UjMafBETIP == true){UjMafBETIP = false;}
      if(wAEsfBsuTy == true){wAEsfBsuTy = false;}
      if(FNZnsInHbt == true){FNZnsInHbt = false;}
      if(DnlSbkGDIS == true){DnlSbkGDIS = false;}
      if(AjGWQbUwSf == true){AjGWQbUwSf = false;}
      if(iLhAYHKXgX == true){iLhAYHKXgX = false;}
      if(MwqOLIOlQt == true){MwqOLIOlQt = false;}
      if(tpmAyUGCXQ == true){tpmAyUGCXQ = false;}
      if(nrouLqFlsT == true){nrouLqFlsT = false;}
      if(ahVjGDsqLH == true){ahVjGDsqLH = false;}
      if(NheXlsXhCE == true){NheXlsXhCE = false;}
      if(AHzPjUHwDT == true){AHzPjUHwDT = false;}
      if(CbswTLTDtu == true){CbswTLTDtu = false;}
      if(bPqPCFMQJS == true){bPqPCFMQJS = false;}
      if(TXjnTShFAk == true){TXjnTShFAk = false;}
      if(uwnqFkohEZ == true){uwnqFkohEZ = false;}
      if(YUmGckPiNd == true){YUmGckPiNd = false;}
      if(IqljAerEcA == true){IqljAerEcA = false;}
      if(cOCJzeaAKR == true){cOCJzeaAKR = false;}
      if(QdLisyjcLh == true){QdLisyjcLh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUYKRFMKYA
{ 
  void trXuKXuOkE()
  { 
      bool grljJwjcyf = false;
      bool WWhSonAkQZ = false;
      bool uZFVgoOLXM = false;
      bool VXwOSGZkQT = false;
      bool aqrrZzsUPw = false;
      bool qmkEkHmQDT = false;
      bool hYElKyZSAi = false;
      bool OOTxyEgMwg = false;
      bool usubVilrdK = false;
      bool TIgwlClGha = false;
      bool YZTghbSnFf = false;
      bool ZZUWXnccPa = false;
      bool MhopPFgXLw = false;
      bool RaeUIUYOst = false;
      bool QylxksnKXx = false;
      bool YIpGOpkdQb = false;
      bool ttcINzuzOC = false;
      bool ONiVJNwrFV = false;
      bool RVzNXIjXGR = false;
      bool juxRzVVcik = false;
      string nSPTfHiwDB;
      string iwlxpANIrS;
      string wZsiDAKyhD;
      string qIEhjiffos;
      string sYieeArjZe;
      string zyLWUOYgPe;
      string wjNAKarDNH;
      string UhSyZWpODD;
      string IaYDErwgNU;
      string JzQJwJKiUE;
      string InVRJReMxx;
      string XKcMWVKJwR;
      string dKpryUQIBP;
      string LHsztTEHsl;
      string NijPxyVEma;
      string zAmCaxxcSn;
      string AVLgkQQdRC;
      string QCQJEtaauz;
      string zMVaQLUqYw;
      string VanEkqXCdg;
      if(nSPTfHiwDB == InVRJReMxx){grljJwjcyf = true;}
      else if(InVRJReMxx == nSPTfHiwDB){YZTghbSnFf = true;}
      if(iwlxpANIrS == XKcMWVKJwR){WWhSonAkQZ = true;}
      else if(XKcMWVKJwR == iwlxpANIrS){ZZUWXnccPa = true;}
      if(wZsiDAKyhD == dKpryUQIBP){uZFVgoOLXM = true;}
      else if(dKpryUQIBP == wZsiDAKyhD){MhopPFgXLw = true;}
      if(qIEhjiffos == LHsztTEHsl){VXwOSGZkQT = true;}
      else if(LHsztTEHsl == qIEhjiffos){RaeUIUYOst = true;}
      if(sYieeArjZe == NijPxyVEma){aqrrZzsUPw = true;}
      else if(NijPxyVEma == sYieeArjZe){QylxksnKXx = true;}
      if(zyLWUOYgPe == zAmCaxxcSn){qmkEkHmQDT = true;}
      else if(zAmCaxxcSn == zyLWUOYgPe){YIpGOpkdQb = true;}
      if(wjNAKarDNH == AVLgkQQdRC){hYElKyZSAi = true;}
      else if(AVLgkQQdRC == wjNAKarDNH){ttcINzuzOC = true;}
      if(UhSyZWpODD == QCQJEtaauz){OOTxyEgMwg = true;}
      if(IaYDErwgNU == zMVaQLUqYw){usubVilrdK = true;}
      if(JzQJwJKiUE == VanEkqXCdg){TIgwlClGha = true;}
      while(QCQJEtaauz == UhSyZWpODD){ONiVJNwrFV = true;}
      while(zMVaQLUqYw == zMVaQLUqYw){RVzNXIjXGR = true;}
      while(VanEkqXCdg == VanEkqXCdg){juxRzVVcik = true;}
      if(grljJwjcyf == true){grljJwjcyf = false;}
      if(WWhSonAkQZ == true){WWhSonAkQZ = false;}
      if(uZFVgoOLXM == true){uZFVgoOLXM = false;}
      if(VXwOSGZkQT == true){VXwOSGZkQT = false;}
      if(aqrrZzsUPw == true){aqrrZzsUPw = false;}
      if(qmkEkHmQDT == true){qmkEkHmQDT = false;}
      if(hYElKyZSAi == true){hYElKyZSAi = false;}
      if(OOTxyEgMwg == true){OOTxyEgMwg = false;}
      if(usubVilrdK == true){usubVilrdK = false;}
      if(TIgwlClGha == true){TIgwlClGha = false;}
      if(YZTghbSnFf == true){YZTghbSnFf = false;}
      if(ZZUWXnccPa == true){ZZUWXnccPa = false;}
      if(MhopPFgXLw == true){MhopPFgXLw = false;}
      if(RaeUIUYOst == true){RaeUIUYOst = false;}
      if(QylxksnKXx == true){QylxksnKXx = false;}
      if(YIpGOpkdQb == true){YIpGOpkdQb = false;}
      if(ttcINzuzOC == true){ttcINzuzOC = false;}
      if(ONiVJNwrFV == true){ONiVJNwrFV = false;}
      if(RVzNXIjXGR == true){RVzNXIjXGR = false;}
      if(juxRzVVcik == true){juxRzVVcik = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFACETGGJJ
{ 
  void hsoELflaZG()
  { 
      bool JneiHOTYWh = false;
      bool hSKVNeWhUf = false;
      bool SAgPujWUlJ = false;
      bool GHCgtiZsfo = false;
      bool KYArKhWYdE = false;
      bool adRIjJGPmX = false;
      bool qzlNbaPcbe = false;
      bool EdBeUtznFN = false;
      bool Mxqhhcptxk = false;
      bool bKFIxLlmQj = false;
      bool Rtxzzxblmo = false;
      bool JRKZLtHEey = false;
      bool kVeqCsXsgI = false;
      bool ILXUuSArij = false;
      bool ADGIaJAexD = false;
      bool DhHRzwPFwF = false;
      bool YhEdgxtoer = false;
      bool tPUuygOVQr = false;
      bool sswdEZEFVy = false;
      bool DtucKRybac = false;
      string cGUpzXAOXn;
      string DGoqJyLPQr;
      string ftrEJbEgom;
      string VhgbLTxzOk;
      string nwTEYGNdAG;
      string pLPNFiNQgW;
      string TTZkRUYMfp;
      string AMBeEianfC;
      string NZfiwJSTVb;
      string FgSqRTWhlD;
      string gByKFdKjIW;
      string IYjdJsmpnH;
      string CFpDjTsKNj;
      string LrBbUMbVdS;
      string ziKzTgwngY;
      string fgteBbKtZk;
      string jAWYKQWIIx;
      string QRMUIStqjD;
      string WFcnDexWas;
      string BguriyMlnC;
      if(cGUpzXAOXn == gByKFdKjIW){JneiHOTYWh = true;}
      else if(gByKFdKjIW == cGUpzXAOXn){Rtxzzxblmo = true;}
      if(DGoqJyLPQr == IYjdJsmpnH){hSKVNeWhUf = true;}
      else if(IYjdJsmpnH == DGoqJyLPQr){JRKZLtHEey = true;}
      if(ftrEJbEgom == CFpDjTsKNj){SAgPujWUlJ = true;}
      else if(CFpDjTsKNj == ftrEJbEgom){kVeqCsXsgI = true;}
      if(VhgbLTxzOk == LrBbUMbVdS){GHCgtiZsfo = true;}
      else if(LrBbUMbVdS == VhgbLTxzOk){ILXUuSArij = true;}
      if(nwTEYGNdAG == ziKzTgwngY){KYArKhWYdE = true;}
      else if(ziKzTgwngY == nwTEYGNdAG){ADGIaJAexD = true;}
      if(pLPNFiNQgW == fgteBbKtZk){adRIjJGPmX = true;}
      else if(fgteBbKtZk == pLPNFiNQgW){DhHRzwPFwF = true;}
      if(TTZkRUYMfp == jAWYKQWIIx){qzlNbaPcbe = true;}
      else if(jAWYKQWIIx == TTZkRUYMfp){YhEdgxtoer = true;}
      if(AMBeEianfC == QRMUIStqjD){EdBeUtznFN = true;}
      if(NZfiwJSTVb == WFcnDexWas){Mxqhhcptxk = true;}
      if(FgSqRTWhlD == BguriyMlnC){bKFIxLlmQj = true;}
      while(QRMUIStqjD == AMBeEianfC){tPUuygOVQr = true;}
      while(WFcnDexWas == WFcnDexWas){sswdEZEFVy = true;}
      while(BguriyMlnC == BguriyMlnC){DtucKRybac = true;}
      if(JneiHOTYWh == true){JneiHOTYWh = false;}
      if(hSKVNeWhUf == true){hSKVNeWhUf = false;}
      if(SAgPujWUlJ == true){SAgPujWUlJ = false;}
      if(GHCgtiZsfo == true){GHCgtiZsfo = false;}
      if(KYArKhWYdE == true){KYArKhWYdE = false;}
      if(adRIjJGPmX == true){adRIjJGPmX = false;}
      if(qzlNbaPcbe == true){qzlNbaPcbe = false;}
      if(EdBeUtznFN == true){EdBeUtznFN = false;}
      if(Mxqhhcptxk == true){Mxqhhcptxk = false;}
      if(bKFIxLlmQj == true){bKFIxLlmQj = false;}
      if(Rtxzzxblmo == true){Rtxzzxblmo = false;}
      if(JRKZLtHEey == true){JRKZLtHEey = false;}
      if(kVeqCsXsgI == true){kVeqCsXsgI = false;}
      if(ILXUuSArij == true){ILXUuSArij = false;}
      if(ADGIaJAexD == true){ADGIaJAexD = false;}
      if(DhHRzwPFwF == true){DhHRzwPFwF = false;}
      if(YhEdgxtoer == true){YhEdgxtoer = false;}
      if(tPUuygOVQr == true){tPUuygOVQr = false;}
      if(sswdEZEFVy == true){sswdEZEFVy = false;}
      if(DtucKRybac == true){DtucKRybac = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZRFHNPNCXF
{ 
  void oCSOCrSceZ()
  { 
      bool azoGrUcitk = false;
      bool uuuPKQQcSi = false;
      bool bybuxBSHRI = false;
      bool elhHgLqrCz = false;
      bool QFTHSDOByB = false;
      bool ZPbKXcXsIq = false;
      bool BVQlFJNmhz = false;
      bool ZYaTSVeTct = false;
      bool lRIQhOJWjE = false;
      bool nxiLxungCJ = false;
      bool paTzbBoIqB = false;
      bool yDQNEjMADp = false;
      bool zpDcKcoOVX = false;
      bool hxRTEKxJnf = false;
      bool ZBehGkfUHM = false;
      bool hmcLJzXpnz = false;
      bool MalTTAkxJs = false;
      bool lCMWQyKUWZ = false;
      bool wTHIotTGJE = false;
      bool mHUoTyOLNF = false;
      string GRDhHBQcIk;
      string LZQRricyPT;
      string rAleszlgBK;
      string IhNezmNrcq;
      string OQTcdGHuXV;
      string OkuRrGeXoI;
      string PiaxcdMlRE;
      string UjUYFbfJBl;
      string qqIfuWmumr;
      string IpDTaeoWAz;
      string tVcTAePVMP;
      string aVVCRYZuBF;
      string pQyZuegBxZ;
      string mJIBrVNoeQ;
      string GRiWRmTACC;
      string FsUtJdWDXV;
      string xOXmcQMTKw;
      string KjQkzYhbII;
      string KgytTsoOrO;
      string yJRJSqsutA;
      if(GRDhHBQcIk == tVcTAePVMP){azoGrUcitk = true;}
      else if(tVcTAePVMP == GRDhHBQcIk){paTzbBoIqB = true;}
      if(LZQRricyPT == aVVCRYZuBF){uuuPKQQcSi = true;}
      else if(aVVCRYZuBF == LZQRricyPT){yDQNEjMADp = true;}
      if(rAleszlgBK == pQyZuegBxZ){bybuxBSHRI = true;}
      else if(pQyZuegBxZ == rAleszlgBK){zpDcKcoOVX = true;}
      if(IhNezmNrcq == mJIBrVNoeQ){elhHgLqrCz = true;}
      else if(mJIBrVNoeQ == IhNezmNrcq){hxRTEKxJnf = true;}
      if(OQTcdGHuXV == GRiWRmTACC){QFTHSDOByB = true;}
      else if(GRiWRmTACC == OQTcdGHuXV){ZBehGkfUHM = true;}
      if(OkuRrGeXoI == FsUtJdWDXV){ZPbKXcXsIq = true;}
      else if(FsUtJdWDXV == OkuRrGeXoI){hmcLJzXpnz = true;}
      if(PiaxcdMlRE == xOXmcQMTKw){BVQlFJNmhz = true;}
      else if(xOXmcQMTKw == PiaxcdMlRE){MalTTAkxJs = true;}
      if(UjUYFbfJBl == KjQkzYhbII){ZYaTSVeTct = true;}
      if(qqIfuWmumr == KgytTsoOrO){lRIQhOJWjE = true;}
      if(IpDTaeoWAz == yJRJSqsutA){nxiLxungCJ = true;}
      while(KjQkzYhbII == UjUYFbfJBl){lCMWQyKUWZ = true;}
      while(KgytTsoOrO == KgytTsoOrO){wTHIotTGJE = true;}
      while(yJRJSqsutA == yJRJSqsutA){mHUoTyOLNF = true;}
      if(azoGrUcitk == true){azoGrUcitk = false;}
      if(uuuPKQQcSi == true){uuuPKQQcSi = false;}
      if(bybuxBSHRI == true){bybuxBSHRI = false;}
      if(elhHgLqrCz == true){elhHgLqrCz = false;}
      if(QFTHSDOByB == true){QFTHSDOByB = false;}
      if(ZPbKXcXsIq == true){ZPbKXcXsIq = false;}
      if(BVQlFJNmhz == true){BVQlFJNmhz = false;}
      if(ZYaTSVeTct == true){ZYaTSVeTct = false;}
      if(lRIQhOJWjE == true){lRIQhOJWjE = false;}
      if(nxiLxungCJ == true){nxiLxungCJ = false;}
      if(paTzbBoIqB == true){paTzbBoIqB = false;}
      if(yDQNEjMADp == true){yDQNEjMADp = false;}
      if(zpDcKcoOVX == true){zpDcKcoOVX = false;}
      if(hxRTEKxJnf == true){hxRTEKxJnf = false;}
      if(ZBehGkfUHM == true){ZBehGkfUHM = false;}
      if(hmcLJzXpnz == true){hmcLJzXpnz = false;}
      if(MalTTAkxJs == true){MalTTAkxJs = false;}
      if(lCMWQyKUWZ == true){lCMWQyKUWZ = false;}
      if(wTHIotTGJE == true){wTHIotTGJE = false;}
      if(mHUoTyOLNF == true){mHUoTyOLNF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCQFVUFESY
{ 
  void qeySrpwGXx()
  { 
      bool nULVeYQxBi = false;
      bool VfHsZlRtyu = false;
      bool UhMpagQyQY = false;
      bool YjJlrKMcgf = false;
      bool FNCQaPKQSt = false;
      bool qJxTiFIVtx = false;
      bool IRgcJlVUAO = false;
      bool YnMRpGewOL = false;
      bool VAeVgPloCl = false;
      bool CqhiXmfYGo = false;
      bool soPDVDwedc = false;
      bool aMGibIlKwt = false;
      bool zgSOMgFctC = false;
      bool ZFoZRfjbAc = false;
      bool SGLZLpkyHO = false;
      bool AVcMoMWBpn = false;
      bool xSkaCUWfRu = false;
      bool XKKSbsUrCW = false;
      bool wHVeCEcbkE = false;
      bool IikLfzUkXp = false;
      string NSnNdHhFln;
      string hSZmSFNCex;
      string ZnLFxyEHAV;
      string ymetsImCuu;
      string iAzftSoQqk;
      string tPeWTYGhQf;
      string CZEPoumfsJ;
      string SKHiNYneKd;
      string ImQPahHIaT;
      string CFlPsIuiqz;
      string fJXgSjIwIt;
      string kaXlWOJnnH;
      string ndEZHMYrpF;
      string cFnLyzPixq;
      string ZKzfiagzrd;
      string zHtiLBExZF;
      string KQGDQemMmW;
      string zZpxgceYpf;
      string eYzLFVKEzx;
      string uRJrfIEuOD;
      if(NSnNdHhFln == fJXgSjIwIt){nULVeYQxBi = true;}
      else if(fJXgSjIwIt == NSnNdHhFln){soPDVDwedc = true;}
      if(hSZmSFNCex == kaXlWOJnnH){VfHsZlRtyu = true;}
      else if(kaXlWOJnnH == hSZmSFNCex){aMGibIlKwt = true;}
      if(ZnLFxyEHAV == ndEZHMYrpF){UhMpagQyQY = true;}
      else if(ndEZHMYrpF == ZnLFxyEHAV){zgSOMgFctC = true;}
      if(ymetsImCuu == cFnLyzPixq){YjJlrKMcgf = true;}
      else if(cFnLyzPixq == ymetsImCuu){ZFoZRfjbAc = true;}
      if(iAzftSoQqk == ZKzfiagzrd){FNCQaPKQSt = true;}
      else if(ZKzfiagzrd == iAzftSoQqk){SGLZLpkyHO = true;}
      if(tPeWTYGhQf == zHtiLBExZF){qJxTiFIVtx = true;}
      else if(zHtiLBExZF == tPeWTYGhQf){AVcMoMWBpn = true;}
      if(CZEPoumfsJ == KQGDQemMmW){IRgcJlVUAO = true;}
      else if(KQGDQemMmW == CZEPoumfsJ){xSkaCUWfRu = true;}
      if(SKHiNYneKd == zZpxgceYpf){YnMRpGewOL = true;}
      if(ImQPahHIaT == eYzLFVKEzx){VAeVgPloCl = true;}
      if(CFlPsIuiqz == uRJrfIEuOD){CqhiXmfYGo = true;}
      while(zZpxgceYpf == SKHiNYneKd){XKKSbsUrCW = true;}
      while(eYzLFVKEzx == eYzLFVKEzx){wHVeCEcbkE = true;}
      while(uRJrfIEuOD == uRJrfIEuOD){IikLfzUkXp = true;}
      if(nULVeYQxBi == true){nULVeYQxBi = false;}
      if(VfHsZlRtyu == true){VfHsZlRtyu = false;}
      if(UhMpagQyQY == true){UhMpagQyQY = false;}
      if(YjJlrKMcgf == true){YjJlrKMcgf = false;}
      if(FNCQaPKQSt == true){FNCQaPKQSt = false;}
      if(qJxTiFIVtx == true){qJxTiFIVtx = false;}
      if(IRgcJlVUAO == true){IRgcJlVUAO = false;}
      if(YnMRpGewOL == true){YnMRpGewOL = false;}
      if(VAeVgPloCl == true){VAeVgPloCl = false;}
      if(CqhiXmfYGo == true){CqhiXmfYGo = false;}
      if(soPDVDwedc == true){soPDVDwedc = false;}
      if(aMGibIlKwt == true){aMGibIlKwt = false;}
      if(zgSOMgFctC == true){zgSOMgFctC = false;}
      if(ZFoZRfjbAc == true){ZFoZRfjbAc = false;}
      if(SGLZLpkyHO == true){SGLZLpkyHO = false;}
      if(AVcMoMWBpn == true){AVcMoMWBpn = false;}
      if(xSkaCUWfRu == true){xSkaCUWfRu = false;}
      if(XKKSbsUrCW == true){XKKSbsUrCW = false;}
      if(wHVeCEcbkE == true){wHVeCEcbkE = false;}
      if(IikLfzUkXp == true){IikLfzUkXp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNLVETNOHQ
{ 
  void FuWqfPYXWl()
  { 
      bool ViuftOwwzD = false;
      bool FIQPSzTVsa = false;
      bool SBRoKPGueG = false;
      bool nNUwmViWiy = false;
      bool HMxQZORRmk = false;
      bool bDAFoURGUe = false;
      bool HARrOrnTbx = false;
      bool PxltTGDAOw = false;
      bool xoHtdkNOHS = false;
      bool DcBEqGuEBh = false;
      bool axopUeQFki = false;
      bool QQqYgRrWNc = false;
      bool eYMJsmuhDN = false;
      bool KyygUzARYz = false;
      bool UHcXBlkbXY = false;
      bool NXqXCCkexg = false;
      bool iiBXYSSKEg = false;
      bool QaxOIWwoIG = false;
      bool BTKdAlHZdS = false;
      bool OUTrPkGFzi = false;
      string TsuqNhyxAU;
      string ZfQPebgBsE;
      string RNXeNoIzqk;
      string rpCHolIHEX;
      string tkEAnzhntQ;
      string ylsfNGUPcX;
      string YyGPbjdIZs;
      string SYxVKfIXqO;
      string HUFamGwVti;
      string QsdfyudnXE;
      string VYOAxYnXVg;
      string xxYOQEsfcV;
      string mHOqbZtRXP;
      string CUzlshFEdN;
      string SYAMkTUPOs;
      string CyLCRNKWXW;
      string dWAGecxlUi;
      string ynBODNHBFI;
      string EeCdMDJwUf;
      string XigGjwYsgI;
      if(TsuqNhyxAU == VYOAxYnXVg){ViuftOwwzD = true;}
      else if(VYOAxYnXVg == TsuqNhyxAU){axopUeQFki = true;}
      if(ZfQPebgBsE == xxYOQEsfcV){FIQPSzTVsa = true;}
      else if(xxYOQEsfcV == ZfQPebgBsE){QQqYgRrWNc = true;}
      if(RNXeNoIzqk == mHOqbZtRXP){SBRoKPGueG = true;}
      else if(mHOqbZtRXP == RNXeNoIzqk){eYMJsmuhDN = true;}
      if(rpCHolIHEX == CUzlshFEdN){nNUwmViWiy = true;}
      else if(CUzlshFEdN == rpCHolIHEX){KyygUzARYz = true;}
      if(tkEAnzhntQ == SYAMkTUPOs){HMxQZORRmk = true;}
      else if(SYAMkTUPOs == tkEAnzhntQ){UHcXBlkbXY = true;}
      if(ylsfNGUPcX == CyLCRNKWXW){bDAFoURGUe = true;}
      else if(CyLCRNKWXW == ylsfNGUPcX){NXqXCCkexg = true;}
      if(YyGPbjdIZs == dWAGecxlUi){HARrOrnTbx = true;}
      else if(dWAGecxlUi == YyGPbjdIZs){iiBXYSSKEg = true;}
      if(SYxVKfIXqO == ynBODNHBFI){PxltTGDAOw = true;}
      if(HUFamGwVti == EeCdMDJwUf){xoHtdkNOHS = true;}
      if(QsdfyudnXE == XigGjwYsgI){DcBEqGuEBh = true;}
      while(ynBODNHBFI == SYxVKfIXqO){QaxOIWwoIG = true;}
      while(EeCdMDJwUf == EeCdMDJwUf){BTKdAlHZdS = true;}
      while(XigGjwYsgI == XigGjwYsgI){OUTrPkGFzi = true;}
      if(ViuftOwwzD == true){ViuftOwwzD = false;}
      if(FIQPSzTVsa == true){FIQPSzTVsa = false;}
      if(SBRoKPGueG == true){SBRoKPGueG = false;}
      if(nNUwmViWiy == true){nNUwmViWiy = false;}
      if(HMxQZORRmk == true){HMxQZORRmk = false;}
      if(bDAFoURGUe == true){bDAFoURGUe = false;}
      if(HARrOrnTbx == true){HARrOrnTbx = false;}
      if(PxltTGDAOw == true){PxltTGDAOw = false;}
      if(xoHtdkNOHS == true){xoHtdkNOHS = false;}
      if(DcBEqGuEBh == true){DcBEqGuEBh = false;}
      if(axopUeQFki == true){axopUeQFki = false;}
      if(QQqYgRrWNc == true){QQqYgRrWNc = false;}
      if(eYMJsmuhDN == true){eYMJsmuhDN = false;}
      if(KyygUzARYz == true){KyygUzARYz = false;}
      if(UHcXBlkbXY == true){UHcXBlkbXY = false;}
      if(NXqXCCkexg == true){NXqXCCkexg = false;}
      if(iiBXYSSKEg == true){iiBXYSSKEg = false;}
      if(QaxOIWwoIG == true){QaxOIWwoIG = false;}
      if(BTKdAlHZdS == true){BTKdAlHZdS = false;}
      if(OUTrPkGFzi == true){OUTrPkGFzi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWUCBEOJLB
{ 
  void tnJFoFRJNo()
  { 
      bool uaFJEHNYYM = false;
      bool GDpAAFwJEW = false;
      bool eVNufGOUMp = false;
      bool ReMeoxfPwY = false;
      bool XirdrSGkkI = false;
      bool HJUiSYMKcx = false;
      bool ssLhtaqLKC = false;
      bool YgNezudjCM = false;
      bool zciEiHKcMQ = false;
      bool jVlyfdWJiQ = false;
      bool buahiZwpjW = false;
      bool ubHQyPKHzl = false;
      bool QNysRDuPyU = false;
      bool YTAljDBAUI = false;
      bool LUspVHNVAQ = false;
      bool TPKxzOxgPe = false;
      bool egqOyabUft = false;
      bool NJlpawUIXK = false;
      bool oZOhBIJDlV = false;
      bool GUkpcecdru = false;
      string ySioQfAkFq;
      string TawtczdCdw;
      string VVUkDTQClu;
      string mDciFEXoGr;
      string cgltfVTUbC;
      string PDFsDbyykw;
      string PxyJEPxNoY;
      string bnukToiZEh;
      string zuZjeiyiec;
      string FYDJceicoP;
      string XFeDabITZO;
      string sXsDxTWOdV;
      string QNiMSCklIn;
      string FGkoJtPWID;
      string aeJPjhezMI;
      string HTyTyKWSkX;
      string pVKkIlmEtD;
      string DAFZulDSbj;
      string XkYAglHQpy;
      string WxlkNETYGx;
      if(ySioQfAkFq == XFeDabITZO){uaFJEHNYYM = true;}
      else if(XFeDabITZO == ySioQfAkFq){buahiZwpjW = true;}
      if(TawtczdCdw == sXsDxTWOdV){GDpAAFwJEW = true;}
      else if(sXsDxTWOdV == TawtczdCdw){ubHQyPKHzl = true;}
      if(VVUkDTQClu == QNiMSCklIn){eVNufGOUMp = true;}
      else if(QNiMSCklIn == VVUkDTQClu){QNysRDuPyU = true;}
      if(mDciFEXoGr == FGkoJtPWID){ReMeoxfPwY = true;}
      else if(FGkoJtPWID == mDciFEXoGr){YTAljDBAUI = true;}
      if(cgltfVTUbC == aeJPjhezMI){XirdrSGkkI = true;}
      else if(aeJPjhezMI == cgltfVTUbC){LUspVHNVAQ = true;}
      if(PDFsDbyykw == HTyTyKWSkX){HJUiSYMKcx = true;}
      else if(HTyTyKWSkX == PDFsDbyykw){TPKxzOxgPe = true;}
      if(PxyJEPxNoY == pVKkIlmEtD){ssLhtaqLKC = true;}
      else if(pVKkIlmEtD == PxyJEPxNoY){egqOyabUft = true;}
      if(bnukToiZEh == DAFZulDSbj){YgNezudjCM = true;}
      if(zuZjeiyiec == XkYAglHQpy){zciEiHKcMQ = true;}
      if(FYDJceicoP == WxlkNETYGx){jVlyfdWJiQ = true;}
      while(DAFZulDSbj == bnukToiZEh){NJlpawUIXK = true;}
      while(XkYAglHQpy == XkYAglHQpy){oZOhBIJDlV = true;}
      while(WxlkNETYGx == WxlkNETYGx){GUkpcecdru = true;}
      if(uaFJEHNYYM == true){uaFJEHNYYM = false;}
      if(GDpAAFwJEW == true){GDpAAFwJEW = false;}
      if(eVNufGOUMp == true){eVNufGOUMp = false;}
      if(ReMeoxfPwY == true){ReMeoxfPwY = false;}
      if(XirdrSGkkI == true){XirdrSGkkI = false;}
      if(HJUiSYMKcx == true){HJUiSYMKcx = false;}
      if(ssLhtaqLKC == true){ssLhtaqLKC = false;}
      if(YgNezudjCM == true){YgNezudjCM = false;}
      if(zciEiHKcMQ == true){zciEiHKcMQ = false;}
      if(jVlyfdWJiQ == true){jVlyfdWJiQ = false;}
      if(buahiZwpjW == true){buahiZwpjW = false;}
      if(ubHQyPKHzl == true){ubHQyPKHzl = false;}
      if(QNysRDuPyU == true){QNysRDuPyU = false;}
      if(YTAljDBAUI == true){YTAljDBAUI = false;}
      if(LUspVHNVAQ == true){LUspVHNVAQ = false;}
      if(TPKxzOxgPe == true){TPKxzOxgPe = false;}
      if(egqOyabUft == true){egqOyabUft = false;}
      if(NJlpawUIXK == true){NJlpawUIXK = false;}
      if(oZOhBIJDlV == true){oZOhBIJDlV = false;}
      if(GUkpcecdru == true){GUkpcecdru = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YPELOUIURA
{ 
  void LLNIptCoyQ()
  { 
      bool eWfcYIWKti = false;
      bool hqnHspwuyS = false;
      bool XCbeMUUeWt = false;
      bool VNxAKHmmhf = false;
      bool zRgFdQLMCo = false;
      bool VBtuybtAPE = false;
      bool mrmANTtmwl = false;
      bool DINSSFVWBu = false;
      bool IIchYTSCCh = false;
      bool MlWcsHefqJ = false;
      bool WXPQkMnbbr = false;
      bool GXzTudPEbt = false;
      bool ArkOYRkjZK = false;
      bool aoeqYkrLwL = false;
      bool eqZJaomDhO = false;
      bool rZExIdmBrT = false;
      bool bEBQRQrHtK = false;
      bool lDIPOIRami = false;
      bool dhCLRAkghu = false;
      bool yqTbjapJrJ = false;
      string aNfbfKyYkZ;
      string EMRDejzjlQ;
      string PnWICWTcRA;
      string cfTnzLTpoN;
      string ZAqrtWtHPG;
      string JWbOZmpWYJ;
      string pUGjwXscET;
      string PIuXpOwdNf;
      string bMNLqGEEOL;
      string UxQfWEsGwW;
      string dQCwqBbDYK;
      string pLIsgdGusp;
      string TnOrySqPAl;
      string UphqBLJRTp;
      string dAfDVInXys;
      string xyNGCpCKxX;
      string JMClpAdQqV;
      string ToaDLSHKVo;
      string eSQHnWbaoL;
      string IzTwfRxsNV;
      if(aNfbfKyYkZ == dQCwqBbDYK){eWfcYIWKti = true;}
      else if(dQCwqBbDYK == aNfbfKyYkZ){WXPQkMnbbr = true;}
      if(EMRDejzjlQ == pLIsgdGusp){hqnHspwuyS = true;}
      else if(pLIsgdGusp == EMRDejzjlQ){GXzTudPEbt = true;}
      if(PnWICWTcRA == TnOrySqPAl){XCbeMUUeWt = true;}
      else if(TnOrySqPAl == PnWICWTcRA){ArkOYRkjZK = true;}
      if(cfTnzLTpoN == UphqBLJRTp){VNxAKHmmhf = true;}
      else if(UphqBLJRTp == cfTnzLTpoN){aoeqYkrLwL = true;}
      if(ZAqrtWtHPG == dAfDVInXys){zRgFdQLMCo = true;}
      else if(dAfDVInXys == ZAqrtWtHPG){eqZJaomDhO = true;}
      if(JWbOZmpWYJ == xyNGCpCKxX){VBtuybtAPE = true;}
      else if(xyNGCpCKxX == JWbOZmpWYJ){rZExIdmBrT = true;}
      if(pUGjwXscET == JMClpAdQqV){mrmANTtmwl = true;}
      else if(JMClpAdQqV == pUGjwXscET){bEBQRQrHtK = true;}
      if(PIuXpOwdNf == ToaDLSHKVo){DINSSFVWBu = true;}
      if(bMNLqGEEOL == eSQHnWbaoL){IIchYTSCCh = true;}
      if(UxQfWEsGwW == IzTwfRxsNV){MlWcsHefqJ = true;}
      while(ToaDLSHKVo == PIuXpOwdNf){lDIPOIRami = true;}
      while(eSQHnWbaoL == eSQHnWbaoL){dhCLRAkghu = true;}
      while(IzTwfRxsNV == IzTwfRxsNV){yqTbjapJrJ = true;}
      if(eWfcYIWKti == true){eWfcYIWKti = false;}
      if(hqnHspwuyS == true){hqnHspwuyS = false;}
      if(XCbeMUUeWt == true){XCbeMUUeWt = false;}
      if(VNxAKHmmhf == true){VNxAKHmmhf = false;}
      if(zRgFdQLMCo == true){zRgFdQLMCo = false;}
      if(VBtuybtAPE == true){VBtuybtAPE = false;}
      if(mrmANTtmwl == true){mrmANTtmwl = false;}
      if(DINSSFVWBu == true){DINSSFVWBu = false;}
      if(IIchYTSCCh == true){IIchYTSCCh = false;}
      if(MlWcsHefqJ == true){MlWcsHefqJ = false;}
      if(WXPQkMnbbr == true){WXPQkMnbbr = false;}
      if(GXzTudPEbt == true){GXzTudPEbt = false;}
      if(ArkOYRkjZK == true){ArkOYRkjZK = false;}
      if(aoeqYkrLwL == true){aoeqYkrLwL = false;}
      if(eqZJaomDhO == true){eqZJaomDhO = false;}
      if(rZExIdmBrT == true){rZExIdmBrT = false;}
      if(bEBQRQrHtK == true){bEBQRQrHtK = false;}
      if(lDIPOIRami == true){lDIPOIRami = false;}
      if(dhCLRAkghu == true){dhCLRAkghu = false;}
      if(yqTbjapJrJ == true){yqTbjapJrJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPKXNYJDTM
{ 
  void PPmcfTmoAt()
  { 
      bool BOwOFbYMlT = false;
      bool uLrHHADDRr = false;
      bool ZLKlFZcKao = false;
      bool psluNQtSUw = false;
      bool BJePzoBNVQ = false;
      bool xYrmzpDKJf = false;
      bool yOlwdBZwtp = false;
      bool FkhVqPftlP = false;
      bool YOoKrQAzwW = false;
      bool NjIoxlXhlx = false;
      bool OETeKLqWui = false;
      bool KIXtHiZbEM = false;
      bool BaAWcVcsXE = false;
      bool rxIoBTuKzg = false;
      bool ZdDMMEMOhO = false;
      bool MudZwnDxBo = false;
      bool hxyqpMAhsm = false;
      bool nPbXlWXnJY = false;
      bool IOKJqwTirM = false;
      bool PxIKybfLVA = false;
      string RhrqCcdeYe;
      string ObpmVemcYm;
      string WKKxbqwZgC;
      string ZHoTBZSQSc;
      string WQbKRkQmOn;
      string hzYDNHXuPL;
      string gDyVEHlWkw;
      string MVKuQGhAep;
      string ZILsUaikGt;
      string BXBHwSRGFK;
      string ytCRbLncmH;
      string YWPYkXrEBc;
      string XBQptnTDyy;
      string nbtUreFsQI;
      string lGyyVeIcVX;
      string aMFclxdMXm;
      string qkdoSwctfG;
      string SznrpRCRUP;
      string fqgaXaWRit;
      string BsVcQBbJfY;
      if(RhrqCcdeYe == ytCRbLncmH){BOwOFbYMlT = true;}
      else if(ytCRbLncmH == RhrqCcdeYe){OETeKLqWui = true;}
      if(ObpmVemcYm == YWPYkXrEBc){uLrHHADDRr = true;}
      else if(YWPYkXrEBc == ObpmVemcYm){KIXtHiZbEM = true;}
      if(WKKxbqwZgC == XBQptnTDyy){ZLKlFZcKao = true;}
      else if(XBQptnTDyy == WKKxbqwZgC){BaAWcVcsXE = true;}
      if(ZHoTBZSQSc == nbtUreFsQI){psluNQtSUw = true;}
      else if(nbtUreFsQI == ZHoTBZSQSc){rxIoBTuKzg = true;}
      if(WQbKRkQmOn == lGyyVeIcVX){BJePzoBNVQ = true;}
      else if(lGyyVeIcVX == WQbKRkQmOn){ZdDMMEMOhO = true;}
      if(hzYDNHXuPL == aMFclxdMXm){xYrmzpDKJf = true;}
      else if(aMFclxdMXm == hzYDNHXuPL){MudZwnDxBo = true;}
      if(gDyVEHlWkw == qkdoSwctfG){yOlwdBZwtp = true;}
      else if(qkdoSwctfG == gDyVEHlWkw){hxyqpMAhsm = true;}
      if(MVKuQGhAep == SznrpRCRUP){FkhVqPftlP = true;}
      if(ZILsUaikGt == fqgaXaWRit){YOoKrQAzwW = true;}
      if(BXBHwSRGFK == BsVcQBbJfY){NjIoxlXhlx = true;}
      while(SznrpRCRUP == MVKuQGhAep){nPbXlWXnJY = true;}
      while(fqgaXaWRit == fqgaXaWRit){IOKJqwTirM = true;}
      while(BsVcQBbJfY == BsVcQBbJfY){PxIKybfLVA = true;}
      if(BOwOFbYMlT == true){BOwOFbYMlT = false;}
      if(uLrHHADDRr == true){uLrHHADDRr = false;}
      if(ZLKlFZcKao == true){ZLKlFZcKao = false;}
      if(psluNQtSUw == true){psluNQtSUw = false;}
      if(BJePzoBNVQ == true){BJePzoBNVQ = false;}
      if(xYrmzpDKJf == true){xYrmzpDKJf = false;}
      if(yOlwdBZwtp == true){yOlwdBZwtp = false;}
      if(FkhVqPftlP == true){FkhVqPftlP = false;}
      if(YOoKrQAzwW == true){YOoKrQAzwW = false;}
      if(NjIoxlXhlx == true){NjIoxlXhlx = false;}
      if(OETeKLqWui == true){OETeKLqWui = false;}
      if(KIXtHiZbEM == true){KIXtHiZbEM = false;}
      if(BaAWcVcsXE == true){BaAWcVcsXE = false;}
      if(rxIoBTuKzg == true){rxIoBTuKzg = false;}
      if(ZdDMMEMOhO == true){ZdDMMEMOhO = false;}
      if(MudZwnDxBo == true){MudZwnDxBo = false;}
      if(hxyqpMAhsm == true){hxyqpMAhsm = false;}
      if(nPbXlWXnJY == true){nPbXlWXnJY = false;}
      if(IOKJqwTirM == true){IOKJqwTirM = false;}
      if(PxIKybfLVA == true){PxIKybfLVA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCAEGRTUFE
{ 
  void GdXqPyBEWH()
  { 
      bool jzRcjaXLYy = false;
      bool EJmsoSYeTE = false;
      bool QXHmpGTaDm = false;
      bool MubdAWzDZK = false;
      bool tXIdIyCgQK = false;
      bool KBqwHMqdmc = false;
      bool HwIlkJgIrR = false;
      bool TVFJKsOdeq = false;
      bool DmJsbLDfWn = false;
      bool eUQwDxPWrz = false;
      bool QtozpouhlO = false;
      bool xNyuYTmOJY = false;
      bool FBlDmyFIGM = false;
      bool dqkfaJyKCm = false;
      bool QVsHpRVUWi = false;
      bool KAMSsOHkLr = false;
      bool imbYkGbRTP = false;
      bool VbMWIjHdNU = false;
      bool bjkWCceRmM = false;
      bool BMyKDdsUWj = false;
      string ZocdaOWaEG;
      string yONVDQBYlx;
      string MgPwuwoQtb;
      string piMqtBUZyj;
      string YkQaVlLrHM;
      string tmgjWsZfhd;
      string ZGgbQPBVbC;
      string uaaBXbQoaJ;
      string kwIhgCBcTA;
      string aoqTKREnJG;
      string joQFQTMfLu;
      string ckFYscxyuN;
      string OYCaaFiGqG;
      string XceUYufDQN;
      string pUQYXpjSag;
      string UFswrLmpdK;
      string jFoFWAFjAx;
      string xsggWsHdCk;
      string VQfJkSihcM;
      string HpZGdjfLBX;
      if(ZocdaOWaEG == joQFQTMfLu){jzRcjaXLYy = true;}
      else if(joQFQTMfLu == ZocdaOWaEG){QtozpouhlO = true;}
      if(yONVDQBYlx == ckFYscxyuN){EJmsoSYeTE = true;}
      else if(ckFYscxyuN == yONVDQBYlx){xNyuYTmOJY = true;}
      if(MgPwuwoQtb == OYCaaFiGqG){QXHmpGTaDm = true;}
      else if(OYCaaFiGqG == MgPwuwoQtb){FBlDmyFIGM = true;}
      if(piMqtBUZyj == XceUYufDQN){MubdAWzDZK = true;}
      else if(XceUYufDQN == piMqtBUZyj){dqkfaJyKCm = true;}
      if(YkQaVlLrHM == pUQYXpjSag){tXIdIyCgQK = true;}
      else if(pUQYXpjSag == YkQaVlLrHM){QVsHpRVUWi = true;}
      if(tmgjWsZfhd == UFswrLmpdK){KBqwHMqdmc = true;}
      else if(UFswrLmpdK == tmgjWsZfhd){KAMSsOHkLr = true;}
      if(ZGgbQPBVbC == jFoFWAFjAx){HwIlkJgIrR = true;}
      else if(jFoFWAFjAx == ZGgbQPBVbC){imbYkGbRTP = true;}
      if(uaaBXbQoaJ == xsggWsHdCk){TVFJKsOdeq = true;}
      if(kwIhgCBcTA == VQfJkSihcM){DmJsbLDfWn = true;}
      if(aoqTKREnJG == HpZGdjfLBX){eUQwDxPWrz = true;}
      while(xsggWsHdCk == uaaBXbQoaJ){VbMWIjHdNU = true;}
      while(VQfJkSihcM == VQfJkSihcM){bjkWCceRmM = true;}
      while(HpZGdjfLBX == HpZGdjfLBX){BMyKDdsUWj = true;}
      if(jzRcjaXLYy == true){jzRcjaXLYy = false;}
      if(EJmsoSYeTE == true){EJmsoSYeTE = false;}
      if(QXHmpGTaDm == true){QXHmpGTaDm = false;}
      if(MubdAWzDZK == true){MubdAWzDZK = false;}
      if(tXIdIyCgQK == true){tXIdIyCgQK = false;}
      if(KBqwHMqdmc == true){KBqwHMqdmc = false;}
      if(HwIlkJgIrR == true){HwIlkJgIrR = false;}
      if(TVFJKsOdeq == true){TVFJKsOdeq = false;}
      if(DmJsbLDfWn == true){DmJsbLDfWn = false;}
      if(eUQwDxPWrz == true){eUQwDxPWrz = false;}
      if(QtozpouhlO == true){QtozpouhlO = false;}
      if(xNyuYTmOJY == true){xNyuYTmOJY = false;}
      if(FBlDmyFIGM == true){FBlDmyFIGM = false;}
      if(dqkfaJyKCm == true){dqkfaJyKCm = false;}
      if(QVsHpRVUWi == true){QVsHpRVUWi = false;}
      if(KAMSsOHkLr == true){KAMSsOHkLr = false;}
      if(imbYkGbRTP == true){imbYkGbRTP = false;}
      if(VbMWIjHdNU == true){VbMWIjHdNU = false;}
      if(bjkWCceRmM == true){bjkWCceRmM = false;}
      if(BMyKDdsUWj == true){BMyKDdsUWj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NJSAQPXPJA
{ 
  void WPpLkMVZCh()
  { 
      bool LfRHNUmXGH = false;
      bool APTxJySaUS = false;
      bool IqwRKQDrGC = false;
      bool azybsQqxrA = false;
      bool cMjCGdjuiY = false;
      bool rArKRTiAxx = false;
      bool RtQEgARrEr = false;
      bool HVhUpuHtLf = false;
      bool fHJhJaGmJY = false;
      bool gpzuihueVF = false;
      bool MrqpRVRXUV = false;
      bool MooQQJkitF = false;
      bool sdhfLQVmkH = false;
      bool AbXFTnQSQm = false;
      bool IiSnLrBidY = false;
      bool xMkPLhKKeA = false;
      bool zelMVkQixc = false;
      bool rRRGxKLtUS = false;
      bool OmJLKnpIsk = false;
      bool dGnPmcwFRZ = false;
      string imCMXjLmQD;
      string ADUynRCaAr;
      string SDRqXRaZTX;
      string gNGydGXVHk;
      string uZFnEaBKfh;
      string lIkZPeULnF;
      string JlTsWlxWTh;
      string tfSPwsyclx;
      string QPskkYcgiz;
      string kLgBaJFLRS;
      string depynGoUcV;
      string frZqosrhIx;
      string JQnUwhzQnm;
      string mmKTTkYuxd;
      string jHDMSrlpMh;
      string RXCUJMqVBF;
      string HXgpisgGXE;
      string TwjdNBMbBE;
      string wIEGUPkpJG;
      string sDsrWLaNcZ;
      if(imCMXjLmQD == depynGoUcV){LfRHNUmXGH = true;}
      else if(depynGoUcV == imCMXjLmQD){MrqpRVRXUV = true;}
      if(ADUynRCaAr == frZqosrhIx){APTxJySaUS = true;}
      else if(frZqosrhIx == ADUynRCaAr){MooQQJkitF = true;}
      if(SDRqXRaZTX == JQnUwhzQnm){IqwRKQDrGC = true;}
      else if(JQnUwhzQnm == SDRqXRaZTX){sdhfLQVmkH = true;}
      if(gNGydGXVHk == mmKTTkYuxd){azybsQqxrA = true;}
      else if(mmKTTkYuxd == gNGydGXVHk){AbXFTnQSQm = true;}
      if(uZFnEaBKfh == jHDMSrlpMh){cMjCGdjuiY = true;}
      else if(jHDMSrlpMh == uZFnEaBKfh){IiSnLrBidY = true;}
      if(lIkZPeULnF == RXCUJMqVBF){rArKRTiAxx = true;}
      else if(RXCUJMqVBF == lIkZPeULnF){xMkPLhKKeA = true;}
      if(JlTsWlxWTh == HXgpisgGXE){RtQEgARrEr = true;}
      else if(HXgpisgGXE == JlTsWlxWTh){zelMVkQixc = true;}
      if(tfSPwsyclx == TwjdNBMbBE){HVhUpuHtLf = true;}
      if(QPskkYcgiz == wIEGUPkpJG){fHJhJaGmJY = true;}
      if(kLgBaJFLRS == sDsrWLaNcZ){gpzuihueVF = true;}
      while(TwjdNBMbBE == tfSPwsyclx){rRRGxKLtUS = true;}
      while(wIEGUPkpJG == wIEGUPkpJG){OmJLKnpIsk = true;}
      while(sDsrWLaNcZ == sDsrWLaNcZ){dGnPmcwFRZ = true;}
      if(LfRHNUmXGH == true){LfRHNUmXGH = false;}
      if(APTxJySaUS == true){APTxJySaUS = false;}
      if(IqwRKQDrGC == true){IqwRKQDrGC = false;}
      if(azybsQqxrA == true){azybsQqxrA = false;}
      if(cMjCGdjuiY == true){cMjCGdjuiY = false;}
      if(rArKRTiAxx == true){rArKRTiAxx = false;}
      if(RtQEgARrEr == true){RtQEgARrEr = false;}
      if(HVhUpuHtLf == true){HVhUpuHtLf = false;}
      if(fHJhJaGmJY == true){fHJhJaGmJY = false;}
      if(gpzuihueVF == true){gpzuihueVF = false;}
      if(MrqpRVRXUV == true){MrqpRVRXUV = false;}
      if(MooQQJkitF == true){MooQQJkitF = false;}
      if(sdhfLQVmkH == true){sdhfLQVmkH = false;}
      if(AbXFTnQSQm == true){AbXFTnQSQm = false;}
      if(IiSnLrBidY == true){IiSnLrBidY = false;}
      if(xMkPLhKKeA == true){xMkPLhKKeA = false;}
      if(zelMVkQixc == true){zelMVkQixc = false;}
      if(rRRGxKLtUS == true){rRRGxKLtUS = false;}
      if(OmJLKnpIsk == true){OmJLKnpIsk = false;}
      if(dGnPmcwFRZ == true){dGnPmcwFRZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKRCSDUWXF
{ 
  void XQynbAOmOD()
  { 
      bool sozbZBUhaJ = false;
      bool mCytowlcTu = false;
      bool IjRkkhCUXM = false;
      bool eolOkRbKhZ = false;
      bool jrTlGshnPb = false;
      bool ZVckRIXNqr = false;
      bool zAKNeyPjJW = false;
      bool UbusKPQeeq = false;
      bool zNFumILAwb = false;
      bool tOSpajhFGI = false;
      bool cyerHyajaC = false;
      bool rrhzsluPaW = false;
      bool lPnhcFIESa = false;
      bool hLXWOAiMmo = false;
      bool gbZtiBfTxn = false;
      bool oRdjVNKwPB = false;
      bool oVRATgTKjr = false;
      bool ChblpKosya = false;
      bool YoHdkQgnBB = false;
      bool plxlzKKZZC = false;
      string sVVYcumUDs;
      string QqwbjEbpqC;
      string lWlgFsBLgj;
      string adJMYhqtoT;
      string HMrdqjGrcV;
      string KUHGbVinSj;
      string tanTRlgjDB;
      string NgAXuZeHoV;
      string mJiKZGVDjC;
      string zCbFZfYYME;
      string CVoaIcUjKC;
      string qayxxjrcsL;
      string QdAACLFuyO;
      string BGukSQUHCw;
      string llrgLXDdIo;
      string mueAnYVnYx;
      string XYluAjeNef;
      string OkZwZdkSod;
      string HamIbFatws;
      string ugiFYMzwfa;
      if(sVVYcumUDs == CVoaIcUjKC){sozbZBUhaJ = true;}
      else if(CVoaIcUjKC == sVVYcumUDs){cyerHyajaC = true;}
      if(QqwbjEbpqC == qayxxjrcsL){mCytowlcTu = true;}
      else if(qayxxjrcsL == QqwbjEbpqC){rrhzsluPaW = true;}
      if(lWlgFsBLgj == QdAACLFuyO){IjRkkhCUXM = true;}
      else if(QdAACLFuyO == lWlgFsBLgj){lPnhcFIESa = true;}
      if(adJMYhqtoT == BGukSQUHCw){eolOkRbKhZ = true;}
      else if(BGukSQUHCw == adJMYhqtoT){hLXWOAiMmo = true;}
      if(HMrdqjGrcV == llrgLXDdIo){jrTlGshnPb = true;}
      else if(llrgLXDdIo == HMrdqjGrcV){gbZtiBfTxn = true;}
      if(KUHGbVinSj == mueAnYVnYx){ZVckRIXNqr = true;}
      else if(mueAnYVnYx == KUHGbVinSj){oRdjVNKwPB = true;}
      if(tanTRlgjDB == XYluAjeNef){zAKNeyPjJW = true;}
      else if(XYluAjeNef == tanTRlgjDB){oVRATgTKjr = true;}
      if(NgAXuZeHoV == OkZwZdkSod){UbusKPQeeq = true;}
      if(mJiKZGVDjC == HamIbFatws){zNFumILAwb = true;}
      if(zCbFZfYYME == ugiFYMzwfa){tOSpajhFGI = true;}
      while(OkZwZdkSod == NgAXuZeHoV){ChblpKosya = true;}
      while(HamIbFatws == HamIbFatws){YoHdkQgnBB = true;}
      while(ugiFYMzwfa == ugiFYMzwfa){plxlzKKZZC = true;}
      if(sozbZBUhaJ == true){sozbZBUhaJ = false;}
      if(mCytowlcTu == true){mCytowlcTu = false;}
      if(IjRkkhCUXM == true){IjRkkhCUXM = false;}
      if(eolOkRbKhZ == true){eolOkRbKhZ = false;}
      if(jrTlGshnPb == true){jrTlGshnPb = false;}
      if(ZVckRIXNqr == true){ZVckRIXNqr = false;}
      if(zAKNeyPjJW == true){zAKNeyPjJW = false;}
      if(UbusKPQeeq == true){UbusKPQeeq = false;}
      if(zNFumILAwb == true){zNFumILAwb = false;}
      if(tOSpajhFGI == true){tOSpajhFGI = false;}
      if(cyerHyajaC == true){cyerHyajaC = false;}
      if(rrhzsluPaW == true){rrhzsluPaW = false;}
      if(lPnhcFIESa == true){lPnhcFIESa = false;}
      if(hLXWOAiMmo == true){hLXWOAiMmo = false;}
      if(gbZtiBfTxn == true){gbZtiBfTxn = false;}
      if(oRdjVNKwPB == true){oRdjVNKwPB = false;}
      if(oVRATgTKjr == true){oVRATgTKjr = false;}
      if(ChblpKosya == true){ChblpKosya = false;}
      if(YoHdkQgnBB == true){YoHdkQgnBB = false;}
      if(plxlzKKZZC == true){plxlzKKZZC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MHBMLAZJKJ
{ 
  void jTrZFwQOmk()
  { 
      bool NwFHbdeTCp = false;
      bool uZiFysXtht = false;
      bool tMcGpbThtX = false;
      bool zYRqdaMzLI = false;
      bool xHQqXHpxGZ = false;
      bool BtizBBTzQz = false;
      bool KwZdqWIrbX = false;
      bool fYhZxlukii = false;
      bool lWaUWEoSpb = false;
      bool GNhLxAhmAA = false;
      bool zyUiscLIBO = false;
      bool FiQhNnVEGl = false;
      bool gpCzQSpWbw = false;
      bool DIjhjnBqas = false;
      bool rfQaWXxAyJ = false;
      bool ecfOSIuUSa = false;
      bool logELwyhxZ = false;
      bool lddNsAYbcs = false;
      bool UpXRRZbVPa = false;
      bool rfYAGDzLOZ = false;
      string RZoqZJIXwd;
      string ifnPxNODjr;
      string yzCQwDrAiL;
      string CHMcOQDFsr;
      string fVNePeXYQJ;
      string TdoTtRWYuV;
      string QHnkbbTKAf;
      string JIKqLblWAQ;
      string eTjZqXSsix;
      string teKWaXgbDn;
      string LMYjzKSxHR;
      string fzXepxWOtD;
      string JabDldymQm;
      string uJTMESuAaf;
      string FUkQQtHffd;
      string AShAdkkVxU;
      string MegUWVfKZX;
      string CWmNynoKlq;
      string WSHmlbbShT;
      string gZCFTZnQsu;
      if(RZoqZJIXwd == LMYjzKSxHR){NwFHbdeTCp = true;}
      else if(LMYjzKSxHR == RZoqZJIXwd){zyUiscLIBO = true;}
      if(ifnPxNODjr == fzXepxWOtD){uZiFysXtht = true;}
      else if(fzXepxWOtD == ifnPxNODjr){FiQhNnVEGl = true;}
      if(yzCQwDrAiL == JabDldymQm){tMcGpbThtX = true;}
      else if(JabDldymQm == yzCQwDrAiL){gpCzQSpWbw = true;}
      if(CHMcOQDFsr == uJTMESuAaf){zYRqdaMzLI = true;}
      else if(uJTMESuAaf == CHMcOQDFsr){DIjhjnBqas = true;}
      if(fVNePeXYQJ == FUkQQtHffd){xHQqXHpxGZ = true;}
      else if(FUkQQtHffd == fVNePeXYQJ){rfQaWXxAyJ = true;}
      if(TdoTtRWYuV == AShAdkkVxU){BtizBBTzQz = true;}
      else if(AShAdkkVxU == TdoTtRWYuV){ecfOSIuUSa = true;}
      if(QHnkbbTKAf == MegUWVfKZX){KwZdqWIrbX = true;}
      else if(MegUWVfKZX == QHnkbbTKAf){logELwyhxZ = true;}
      if(JIKqLblWAQ == CWmNynoKlq){fYhZxlukii = true;}
      if(eTjZqXSsix == WSHmlbbShT){lWaUWEoSpb = true;}
      if(teKWaXgbDn == gZCFTZnQsu){GNhLxAhmAA = true;}
      while(CWmNynoKlq == JIKqLblWAQ){lddNsAYbcs = true;}
      while(WSHmlbbShT == WSHmlbbShT){UpXRRZbVPa = true;}
      while(gZCFTZnQsu == gZCFTZnQsu){rfYAGDzLOZ = true;}
      if(NwFHbdeTCp == true){NwFHbdeTCp = false;}
      if(uZiFysXtht == true){uZiFysXtht = false;}
      if(tMcGpbThtX == true){tMcGpbThtX = false;}
      if(zYRqdaMzLI == true){zYRqdaMzLI = false;}
      if(xHQqXHpxGZ == true){xHQqXHpxGZ = false;}
      if(BtizBBTzQz == true){BtizBBTzQz = false;}
      if(KwZdqWIrbX == true){KwZdqWIrbX = false;}
      if(fYhZxlukii == true){fYhZxlukii = false;}
      if(lWaUWEoSpb == true){lWaUWEoSpb = false;}
      if(GNhLxAhmAA == true){GNhLxAhmAA = false;}
      if(zyUiscLIBO == true){zyUiscLIBO = false;}
      if(FiQhNnVEGl == true){FiQhNnVEGl = false;}
      if(gpCzQSpWbw == true){gpCzQSpWbw = false;}
      if(DIjhjnBqas == true){DIjhjnBqas = false;}
      if(rfQaWXxAyJ == true){rfQaWXxAyJ = false;}
      if(ecfOSIuUSa == true){ecfOSIuUSa = false;}
      if(logELwyhxZ == true){logELwyhxZ = false;}
      if(lddNsAYbcs == true){lddNsAYbcs = false;}
      if(UpXRRZbVPa == true){UpXRRZbVPa = false;}
      if(rfYAGDzLOZ == true){rfYAGDzLOZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALQUTREXTK
{ 
  void QgRaFVFPjy()
  { 
      bool mPoyTigOpJ = false;
      bool cduEiuoVfx = false;
      bool XgzlJqlJBC = false;
      bool BzYZbtkIAN = false;
      bool mYINkWFSmj = false;
      bool JszSJGPDoc = false;
      bool wXNmIcEVbo = false;
      bool JfVSJzXlBl = false;
      bool kTVQrHAFQV = false;
      bool dhTWQPLVEH = false;
      bool SjpyadXfJK = false;
      bool hdCCqcCwtB = false;
      bool czEFLaMyCs = false;
      bool mCgsTBcWoO = false;
      bool iTwGnzfQem = false;
      bool NOaDeSejmA = false;
      bool QYdPWfxJip = false;
      bool zeGeRJCyRM = false;
      bool uuTOfXacNA = false;
      bool VrjoxKogiI = false;
      string bVUSeNawdU;
      string ztapRbcVId;
      string CRUCewGbuF;
      string RudYzqYAUQ;
      string sKDpDMpwep;
      string QLPDqKASni;
      string HyAXCEPCqZ;
      string CcAqjrOdyS;
      string GJwEoFeago;
      string pGLkJuJenz;
      string wmFEnmKXSz;
      string uWUVcxBwiw;
      string YnVBjuQPgo;
      string hipyVSErPB;
      string tHIgsTloIM;
      string sNuqaIRDUs;
      string VuqcRLfVAK;
      string rJfgBRenHP;
      string JaGUwUnyWN;
      string ABWWeyPfPh;
      if(bVUSeNawdU == wmFEnmKXSz){mPoyTigOpJ = true;}
      else if(wmFEnmKXSz == bVUSeNawdU){SjpyadXfJK = true;}
      if(ztapRbcVId == uWUVcxBwiw){cduEiuoVfx = true;}
      else if(uWUVcxBwiw == ztapRbcVId){hdCCqcCwtB = true;}
      if(CRUCewGbuF == YnVBjuQPgo){XgzlJqlJBC = true;}
      else if(YnVBjuQPgo == CRUCewGbuF){czEFLaMyCs = true;}
      if(RudYzqYAUQ == hipyVSErPB){BzYZbtkIAN = true;}
      else if(hipyVSErPB == RudYzqYAUQ){mCgsTBcWoO = true;}
      if(sKDpDMpwep == tHIgsTloIM){mYINkWFSmj = true;}
      else if(tHIgsTloIM == sKDpDMpwep){iTwGnzfQem = true;}
      if(QLPDqKASni == sNuqaIRDUs){JszSJGPDoc = true;}
      else if(sNuqaIRDUs == QLPDqKASni){NOaDeSejmA = true;}
      if(HyAXCEPCqZ == VuqcRLfVAK){wXNmIcEVbo = true;}
      else if(VuqcRLfVAK == HyAXCEPCqZ){QYdPWfxJip = true;}
      if(CcAqjrOdyS == rJfgBRenHP){JfVSJzXlBl = true;}
      if(GJwEoFeago == JaGUwUnyWN){kTVQrHAFQV = true;}
      if(pGLkJuJenz == ABWWeyPfPh){dhTWQPLVEH = true;}
      while(rJfgBRenHP == CcAqjrOdyS){zeGeRJCyRM = true;}
      while(JaGUwUnyWN == JaGUwUnyWN){uuTOfXacNA = true;}
      while(ABWWeyPfPh == ABWWeyPfPh){VrjoxKogiI = true;}
      if(mPoyTigOpJ == true){mPoyTigOpJ = false;}
      if(cduEiuoVfx == true){cduEiuoVfx = false;}
      if(XgzlJqlJBC == true){XgzlJqlJBC = false;}
      if(BzYZbtkIAN == true){BzYZbtkIAN = false;}
      if(mYINkWFSmj == true){mYINkWFSmj = false;}
      if(JszSJGPDoc == true){JszSJGPDoc = false;}
      if(wXNmIcEVbo == true){wXNmIcEVbo = false;}
      if(JfVSJzXlBl == true){JfVSJzXlBl = false;}
      if(kTVQrHAFQV == true){kTVQrHAFQV = false;}
      if(dhTWQPLVEH == true){dhTWQPLVEH = false;}
      if(SjpyadXfJK == true){SjpyadXfJK = false;}
      if(hdCCqcCwtB == true){hdCCqcCwtB = false;}
      if(czEFLaMyCs == true){czEFLaMyCs = false;}
      if(mCgsTBcWoO == true){mCgsTBcWoO = false;}
      if(iTwGnzfQem == true){iTwGnzfQem = false;}
      if(NOaDeSejmA == true){NOaDeSejmA = false;}
      if(QYdPWfxJip == true){QYdPWfxJip = false;}
      if(zeGeRJCyRM == true){zeGeRJCyRM = false;}
      if(uuTOfXacNA == true){uuTOfXacNA = false;}
      if(VrjoxKogiI == true){VrjoxKogiI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WBUEOTDJXD
{ 
  void GJDKsnbLCZ()
  { 
      bool tdKpURMJVC = false;
      bool uYWiUkzFwT = false;
      bool ImVIjWzVNa = false;
      bool fchzVwOQHW = false;
      bool fsGqYNKZno = false;
      bool oeSGzHHCFx = false;
      bool SquuWSpWMX = false;
      bool VhyZmPgeiV = false;
      bool LYgXkAKbAN = false;
      bool oMKJEoxKUF = false;
      bool XmNPTHgrSj = false;
      bool acSjlsJWKV = false;
      bool INWyiJWnVy = false;
      bool RVKdyXLQEd = false;
      bool SRJPmMsaXK = false;
      bool fZzyxKQOgJ = false;
      bool jrWURERokN = false;
      bool grSgCqEGLW = false;
      bool QwQKSqVLfn = false;
      bool HxjtsZtnyi = false;
      string VmztgNXkJD;
      string JIRbwLoHMB;
      string niuESyfXfX;
      string TYNoTgRBkW;
      string rdJgncDOoK;
      string MxXKGmrtbi;
      string hzEkijucIP;
      string snVoIJZNQp;
      string tRhVKWAChg;
      string oXZCorZXyD;
      string gaFZQYahBw;
      string MeckoPRiZL;
      string jstaaVNTAP;
      string jBONISLIEl;
      string wSAlTKtnMY;
      string aqylTngdzu;
      string LGgkMLPPcW;
      string EIdnPQrIHQ;
      string aZHbosDcsU;
      string lgJIZokOZH;
      if(VmztgNXkJD == gaFZQYahBw){tdKpURMJVC = true;}
      else if(gaFZQYahBw == VmztgNXkJD){XmNPTHgrSj = true;}
      if(JIRbwLoHMB == MeckoPRiZL){uYWiUkzFwT = true;}
      else if(MeckoPRiZL == JIRbwLoHMB){acSjlsJWKV = true;}
      if(niuESyfXfX == jstaaVNTAP){ImVIjWzVNa = true;}
      else if(jstaaVNTAP == niuESyfXfX){INWyiJWnVy = true;}
      if(TYNoTgRBkW == jBONISLIEl){fchzVwOQHW = true;}
      else if(jBONISLIEl == TYNoTgRBkW){RVKdyXLQEd = true;}
      if(rdJgncDOoK == wSAlTKtnMY){fsGqYNKZno = true;}
      else if(wSAlTKtnMY == rdJgncDOoK){SRJPmMsaXK = true;}
      if(MxXKGmrtbi == aqylTngdzu){oeSGzHHCFx = true;}
      else if(aqylTngdzu == MxXKGmrtbi){fZzyxKQOgJ = true;}
      if(hzEkijucIP == LGgkMLPPcW){SquuWSpWMX = true;}
      else if(LGgkMLPPcW == hzEkijucIP){jrWURERokN = true;}
      if(snVoIJZNQp == EIdnPQrIHQ){VhyZmPgeiV = true;}
      if(tRhVKWAChg == aZHbosDcsU){LYgXkAKbAN = true;}
      if(oXZCorZXyD == lgJIZokOZH){oMKJEoxKUF = true;}
      while(EIdnPQrIHQ == snVoIJZNQp){grSgCqEGLW = true;}
      while(aZHbosDcsU == aZHbosDcsU){QwQKSqVLfn = true;}
      while(lgJIZokOZH == lgJIZokOZH){HxjtsZtnyi = true;}
      if(tdKpURMJVC == true){tdKpURMJVC = false;}
      if(uYWiUkzFwT == true){uYWiUkzFwT = false;}
      if(ImVIjWzVNa == true){ImVIjWzVNa = false;}
      if(fchzVwOQHW == true){fchzVwOQHW = false;}
      if(fsGqYNKZno == true){fsGqYNKZno = false;}
      if(oeSGzHHCFx == true){oeSGzHHCFx = false;}
      if(SquuWSpWMX == true){SquuWSpWMX = false;}
      if(VhyZmPgeiV == true){VhyZmPgeiV = false;}
      if(LYgXkAKbAN == true){LYgXkAKbAN = false;}
      if(oMKJEoxKUF == true){oMKJEoxKUF = false;}
      if(XmNPTHgrSj == true){XmNPTHgrSj = false;}
      if(acSjlsJWKV == true){acSjlsJWKV = false;}
      if(INWyiJWnVy == true){INWyiJWnVy = false;}
      if(RVKdyXLQEd == true){RVKdyXLQEd = false;}
      if(SRJPmMsaXK == true){SRJPmMsaXK = false;}
      if(fZzyxKQOgJ == true){fZzyxKQOgJ = false;}
      if(jrWURERokN == true){jrWURERokN = false;}
      if(grSgCqEGLW == true){grSgCqEGLW = false;}
      if(QwQKSqVLfn == true){QwQKSqVLfn = false;}
      if(HxjtsZtnyi == true){HxjtsZtnyi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXUINWQXOQ
{ 
  void YqNJZbblTV()
  { 
      bool JuIflqWpbS = false;
      bool TxGygkGdaI = false;
      bool MmCxTsQmsL = false;
      bool NyzVbBfrYd = false;
      bool WZonEFylEw = false;
      bool ZyNRBWrKMs = false;
      bool ZixPEUyjVe = false;
      bool FOExlmyNsN = false;
      bool uehwlPjgUE = false;
      bool IUfeDmcYji = false;
      bool HNPYqLsQfN = false;
      bool YeRyyuBAcn = false;
      bool kROQWjhZsy = false;
      bool JYdJGgOIFa = false;
      bool WTAGfdDggI = false;
      bool lbwuyozyCG = false;
      bool cTWgEzAHqQ = false;
      bool fruBRRQHks = false;
      bool gBrkMhciLQ = false;
      bool hPGyyCwTCf = false;
      string NMHXHKTglg;
      string SIHRJPqiJU;
      string iWLCMFEsBy;
      string HKlhqFjqEj;
      string pMnzWBBqnJ;
      string tmJoNqBELC;
      string GaemZHVYZE;
      string fzeZdWhLeK;
      string DMErDUBwUz;
      string EefCdPhAZO;
      string fbQjdtIjLq;
      string JpZAysVmjF;
      string GYEZABTcuO;
      string nglPeauUOI;
      string MQkdpNEeDj;
      string suQUIGXpjc;
      string afowCcEJVW;
      string yBYarpmZjl;
      string woYKVsPQHX;
      string DEjkhfboaN;
      if(NMHXHKTglg == fbQjdtIjLq){JuIflqWpbS = true;}
      else if(fbQjdtIjLq == NMHXHKTglg){HNPYqLsQfN = true;}
      if(SIHRJPqiJU == JpZAysVmjF){TxGygkGdaI = true;}
      else if(JpZAysVmjF == SIHRJPqiJU){YeRyyuBAcn = true;}
      if(iWLCMFEsBy == GYEZABTcuO){MmCxTsQmsL = true;}
      else if(GYEZABTcuO == iWLCMFEsBy){kROQWjhZsy = true;}
      if(HKlhqFjqEj == nglPeauUOI){NyzVbBfrYd = true;}
      else if(nglPeauUOI == HKlhqFjqEj){JYdJGgOIFa = true;}
      if(pMnzWBBqnJ == MQkdpNEeDj){WZonEFylEw = true;}
      else if(MQkdpNEeDj == pMnzWBBqnJ){WTAGfdDggI = true;}
      if(tmJoNqBELC == suQUIGXpjc){ZyNRBWrKMs = true;}
      else if(suQUIGXpjc == tmJoNqBELC){lbwuyozyCG = true;}
      if(GaemZHVYZE == afowCcEJVW){ZixPEUyjVe = true;}
      else if(afowCcEJVW == GaemZHVYZE){cTWgEzAHqQ = true;}
      if(fzeZdWhLeK == yBYarpmZjl){FOExlmyNsN = true;}
      if(DMErDUBwUz == woYKVsPQHX){uehwlPjgUE = true;}
      if(EefCdPhAZO == DEjkhfboaN){IUfeDmcYji = true;}
      while(yBYarpmZjl == fzeZdWhLeK){fruBRRQHks = true;}
      while(woYKVsPQHX == woYKVsPQHX){gBrkMhciLQ = true;}
      while(DEjkhfboaN == DEjkhfboaN){hPGyyCwTCf = true;}
      if(JuIflqWpbS == true){JuIflqWpbS = false;}
      if(TxGygkGdaI == true){TxGygkGdaI = false;}
      if(MmCxTsQmsL == true){MmCxTsQmsL = false;}
      if(NyzVbBfrYd == true){NyzVbBfrYd = false;}
      if(WZonEFylEw == true){WZonEFylEw = false;}
      if(ZyNRBWrKMs == true){ZyNRBWrKMs = false;}
      if(ZixPEUyjVe == true){ZixPEUyjVe = false;}
      if(FOExlmyNsN == true){FOExlmyNsN = false;}
      if(uehwlPjgUE == true){uehwlPjgUE = false;}
      if(IUfeDmcYji == true){IUfeDmcYji = false;}
      if(HNPYqLsQfN == true){HNPYqLsQfN = false;}
      if(YeRyyuBAcn == true){YeRyyuBAcn = false;}
      if(kROQWjhZsy == true){kROQWjhZsy = false;}
      if(JYdJGgOIFa == true){JYdJGgOIFa = false;}
      if(WTAGfdDggI == true){WTAGfdDggI = false;}
      if(lbwuyozyCG == true){lbwuyozyCG = false;}
      if(cTWgEzAHqQ == true){cTWgEzAHqQ = false;}
      if(fruBRRQHks == true){fruBRRQHks = false;}
      if(gBrkMhciLQ == true){gBrkMhciLQ = false;}
      if(hPGyyCwTCf == true){hPGyyCwTCf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OABJHKLFZZ
{ 
  void WCUKezofWq()
  { 
      bool BQaCxhSeFK = false;
      bool cbVjfnjcLV = false;
      bool RxFsaJdCgn = false;
      bool ddQsFiXHTr = false;
      bool rdWroRxihf = false;
      bool AzYXIEKgan = false;
      bool DPxRfzKbex = false;
      bool QbISdmaNEJ = false;
      bool MuUAmeEskB = false;
      bool XpgfobgEMo = false;
      bool GUDjPXqGsV = false;
      bool dxbQbIuxdA = false;
      bool tRqcZZtcdB = false;
      bool GVBPCqqjjO = false;
      bool nyzPXZNQDf = false;
      bool giaLtodaKp = false;
      bool dOcqOIwMNj = false;
      bool QKMOMwRbFz = false;
      bool LdYxUWtoUN = false;
      bool NQZtkZVIAO = false;
      string OxjWcfGkyA;
      string rEJCTLLqdi;
      string xRduOTWIZE;
      string qEEVObnQiX;
      string mGjphcNAUb;
      string VjtoSxTnHI;
      string JyKsJmAnnr;
      string XuIGwqgmNl;
      string GWnyiGKPCR;
      string IzIZNowqgt;
      string bYMbDZbmsb;
      string PfaVCmJLKC;
      string cklVjXlhsG;
      string toGSJgJLtI;
      string eWWaBbYmXa;
      string fjfdQqmprf;
      string nttlgaZHLV;
      string cxRBXGNKUH;
      string zzKRaKIcCR;
      string tTTOUjbjta;
      if(OxjWcfGkyA == bYMbDZbmsb){BQaCxhSeFK = true;}
      else if(bYMbDZbmsb == OxjWcfGkyA){GUDjPXqGsV = true;}
      if(rEJCTLLqdi == PfaVCmJLKC){cbVjfnjcLV = true;}
      else if(PfaVCmJLKC == rEJCTLLqdi){dxbQbIuxdA = true;}
      if(xRduOTWIZE == cklVjXlhsG){RxFsaJdCgn = true;}
      else if(cklVjXlhsG == xRduOTWIZE){tRqcZZtcdB = true;}
      if(qEEVObnQiX == toGSJgJLtI){ddQsFiXHTr = true;}
      else if(toGSJgJLtI == qEEVObnQiX){GVBPCqqjjO = true;}
      if(mGjphcNAUb == eWWaBbYmXa){rdWroRxihf = true;}
      else if(eWWaBbYmXa == mGjphcNAUb){nyzPXZNQDf = true;}
      if(VjtoSxTnHI == fjfdQqmprf){AzYXIEKgan = true;}
      else if(fjfdQqmprf == VjtoSxTnHI){giaLtodaKp = true;}
      if(JyKsJmAnnr == nttlgaZHLV){DPxRfzKbex = true;}
      else if(nttlgaZHLV == JyKsJmAnnr){dOcqOIwMNj = true;}
      if(XuIGwqgmNl == cxRBXGNKUH){QbISdmaNEJ = true;}
      if(GWnyiGKPCR == zzKRaKIcCR){MuUAmeEskB = true;}
      if(IzIZNowqgt == tTTOUjbjta){XpgfobgEMo = true;}
      while(cxRBXGNKUH == XuIGwqgmNl){QKMOMwRbFz = true;}
      while(zzKRaKIcCR == zzKRaKIcCR){LdYxUWtoUN = true;}
      while(tTTOUjbjta == tTTOUjbjta){NQZtkZVIAO = true;}
      if(BQaCxhSeFK == true){BQaCxhSeFK = false;}
      if(cbVjfnjcLV == true){cbVjfnjcLV = false;}
      if(RxFsaJdCgn == true){RxFsaJdCgn = false;}
      if(ddQsFiXHTr == true){ddQsFiXHTr = false;}
      if(rdWroRxihf == true){rdWroRxihf = false;}
      if(AzYXIEKgan == true){AzYXIEKgan = false;}
      if(DPxRfzKbex == true){DPxRfzKbex = false;}
      if(QbISdmaNEJ == true){QbISdmaNEJ = false;}
      if(MuUAmeEskB == true){MuUAmeEskB = false;}
      if(XpgfobgEMo == true){XpgfobgEMo = false;}
      if(GUDjPXqGsV == true){GUDjPXqGsV = false;}
      if(dxbQbIuxdA == true){dxbQbIuxdA = false;}
      if(tRqcZZtcdB == true){tRqcZZtcdB = false;}
      if(GVBPCqqjjO == true){GVBPCqqjjO = false;}
      if(nyzPXZNQDf == true){nyzPXZNQDf = false;}
      if(giaLtodaKp == true){giaLtodaKp = false;}
      if(dOcqOIwMNj == true){dOcqOIwMNj = false;}
      if(QKMOMwRbFz == true){QKMOMwRbFz = false;}
      if(LdYxUWtoUN == true){LdYxUWtoUN = false;}
      if(NQZtkZVIAO == true){NQZtkZVIAO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWJBLWOMUC
{ 
  void TVYtXjfSzy()
  { 
      bool egEuwSfSuu = false;
      bool hBNdECqweq = false;
      bool LoSwjGzqNX = false;
      bool QuACZTpAaP = false;
      bool GlRKMNuxml = false;
      bool hMmuFoNILo = false;
      bool ToEXelALDj = false;
      bool MqUOkZXIiV = false;
      bool KCDboDIFwj = false;
      bool FhnkwQgsfZ = false;
      bool MjsDZqqXJf = false;
      bool RFYodQkcia = false;
      bool ctPTdeCiRU = false;
      bool rdbIJaIACy = false;
      bool LkwQSAIyGe = false;
      bool eEKExRUZYt = false;
      bool nHFomncQfD = false;
      bool HkakOryyBd = false;
      bool WEblonSXLq = false;
      bool GibHJDeHdd = false;
      string skztyKNcEG;
      string YkcZyRNnHL;
      string kPOBhudqlm;
      string GpVaBPDqAB;
      string CmdDECwFHa;
      string KQJAdcVxMC;
      string fVqRAhOCYi;
      string NVnFJxlKxe;
      string yYjKbpfVxX;
      string tGdyUfwLDV;
      string ntgYMocEpf;
      string qKAhDHlfpK;
      string BrEAnHqpjc;
      string BaHapEqLxm;
      string MbeQgiGwtN;
      string tPVsUuogjF;
      string xmTNdPDYqy;
      string QaiDxYNnSF;
      string BuuWilENGu;
      string OJbroZIRmQ;
      if(skztyKNcEG == ntgYMocEpf){egEuwSfSuu = true;}
      else if(ntgYMocEpf == skztyKNcEG){MjsDZqqXJf = true;}
      if(YkcZyRNnHL == qKAhDHlfpK){hBNdECqweq = true;}
      else if(qKAhDHlfpK == YkcZyRNnHL){RFYodQkcia = true;}
      if(kPOBhudqlm == BrEAnHqpjc){LoSwjGzqNX = true;}
      else if(BrEAnHqpjc == kPOBhudqlm){ctPTdeCiRU = true;}
      if(GpVaBPDqAB == BaHapEqLxm){QuACZTpAaP = true;}
      else if(BaHapEqLxm == GpVaBPDqAB){rdbIJaIACy = true;}
      if(CmdDECwFHa == MbeQgiGwtN){GlRKMNuxml = true;}
      else if(MbeQgiGwtN == CmdDECwFHa){LkwQSAIyGe = true;}
      if(KQJAdcVxMC == tPVsUuogjF){hMmuFoNILo = true;}
      else if(tPVsUuogjF == KQJAdcVxMC){eEKExRUZYt = true;}
      if(fVqRAhOCYi == xmTNdPDYqy){ToEXelALDj = true;}
      else if(xmTNdPDYqy == fVqRAhOCYi){nHFomncQfD = true;}
      if(NVnFJxlKxe == QaiDxYNnSF){MqUOkZXIiV = true;}
      if(yYjKbpfVxX == BuuWilENGu){KCDboDIFwj = true;}
      if(tGdyUfwLDV == OJbroZIRmQ){FhnkwQgsfZ = true;}
      while(QaiDxYNnSF == NVnFJxlKxe){HkakOryyBd = true;}
      while(BuuWilENGu == BuuWilENGu){WEblonSXLq = true;}
      while(OJbroZIRmQ == OJbroZIRmQ){GibHJDeHdd = true;}
      if(egEuwSfSuu == true){egEuwSfSuu = false;}
      if(hBNdECqweq == true){hBNdECqweq = false;}
      if(LoSwjGzqNX == true){LoSwjGzqNX = false;}
      if(QuACZTpAaP == true){QuACZTpAaP = false;}
      if(GlRKMNuxml == true){GlRKMNuxml = false;}
      if(hMmuFoNILo == true){hMmuFoNILo = false;}
      if(ToEXelALDj == true){ToEXelALDj = false;}
      if(MqUOkZXIiV == true){MqUOkZXIiV = false;}
      if(KCDboDIFwj == true){KCDboDIFwj = false;}
      if(FhnkwQgsfZ == true){FhnkwQgsfZ = false;}
      if(MjsDZqqXJf == true){MjsDZqqXJf = false;}
      if(RFYodQkcia == true){RFYodQkcia = false;}
      if(ctPTdeCiRU == true){ctPTdeCiRU = false;}
      if(rdbIJaIACy == true){rdbIJaIACy = false;}
      if(LkwQSAIyGe == true){LkwQSAIyGe = false;}
      if(eEKExRUZYt == true){eEKExRUZYt = false;}
      if(nHFomncQfD == true){nHFomncQfD = false;}
      if(HkakOryyBd == true){HkakOryyBd = false;}
      if(WEblonSXLq == true){WEblonSXLq = false;}
      if(GibHJDeHdd == true){GibHJDeHdd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NBNZCRQOLJ
{ 
  void xYmHHWwnxF()
  { 
      bool CygsGcCVep = false;
      bool jzlFbyJzMA = false;
      bool WfixYMBzwy = false;
      bool KQsUoobCgl = false;
      bool SyNzIMNfdo = false;
      bool xjocSVPiTt = false;
      bool aCYgeSFRPm = false;
      bool VGSagXSioM = false;
      bool yVVHAabQCT = false;
      bool YrimKPZgUo = false;
      bool GwQpSpQOwt = false;
      bool DftGuFfQfE = false;
      bool qoPwNdXfPQ = false;
      bool ylOzGCFfoJ = false;
      bool JNTHPsxbqF = false;
      bool iIAPxRgTbn = false;
      bool SkyeuRRtAs = false;
      bool AAaWtdUHgU = false;
      bool gunKgokyBn = false;
      bool VkDBqYOoLy = false;
      string VPmLcRgdNz;
      string bsjLCjfHNe;
      string UxkKclTKHF;
      string quLOVHAqlc;
      string KGpIhgNeLK;
      string ZAeaOXdbhp;
      string yWWIHggVou;
      string inVkTNHcbw;
      string YnzweqQjzx;
      string cXIudnihAB;
      string AqoPalesHA;
      string QBAlRKXacQ;
      string QwVrSLeZGf;
      string dYbawgyiUs;
      string LWczgaXWdS;
      string QIFjjDVxxP;
      string GFmaVqYYpj;
      string MnFiEtSWKq;
      string mIumOVTrpr;
      string LAlFmGiBcp;
      if(VPmLcRgdNz == AqoPalesHA){CygsGcCVep = true;}
      else if(AqoPalesHA == VPmLcRgdNz){GwQpSpQOwt = true;}
      if(bsjLCjfHNe == QBAlRKXacQ){jzlFbyJzMA = true;}
      else if(QBAlRKXacQ == bsjLCjfHNe){DftGuFfQfE = true;}
      if(UxkKclTKHF == QwVrSLeZGf){WfixYMBzwy = true;}
      else if(QwVrSLeZGf == UxkKclTKHF){qoPwNdXfPQ = true;}
      if(quLOVHAqlc == dYbawgyiUs){KQsUoobCgl = true;}
      else if(dYbawgyiUs == quLOVHAqlc){ylOzGCFfoJ = true;}
      if(KGpIhgNeLK == LWczgaXWdS){SyNzIMNfdo = true;}
      else if(LWczgaXWdS == KGpIhgNeLK){JNTHPsxbqF = true;}
      if(ZAeaOXdbhp == QIFjjDVxxP){xjocSVPiTt = true;}
      else if(QIFjjDVxxP == ZAeaOXdbhp){iIAPxRgTbn = true;}
      if(yWWIHggVou == GFmaVqYYpj){aCYgeSFRPm = true;}
      else if(GFmaVqYYpj == yWWIHggVou){SkyeuRRtAs = true;}
      if(inVkTNHcbw == MnFiEtSWKq){VGSagXSioM = true;}
      if(YnzweqQjzx == mIumOVTrpr){yVVHAabQCT = true;}
      if(cXIudnihAB == LAlFmGiBcp){YrimKPZgUo = true;}
      while(MnFiEtSWKq == inVkTNHcbw){AAaWtdUHgU = true;}
      while(mIumOVTrpr == mIumOVTrpr){gunKgokyBn = true;}
      while(LAlFmGiBcp == LAlFmGiBcp){VkDBqYOoLy = true;}
      if(CygsGcCVep == true){CygsGcCVep = false;}
      if(jzlFbyJzMA == true){jzlFbyJzMA = false;}
      if(WfixYMBzwy == true){WfixYMBzwy = false;}
      if(KQsUoobCgl == true){KQsUoobCgl = false;}
      if(SyNzIMNfdo == true){SyNzIMNfdo = false;}
      if(xjocSVPiTt == true){xjocSVPiTt = false;}
      if(aCYgeSFRPm == true){aCYgeSFRPm = false;}
      if(VGSagXSioM == true){VGSagXSioM = false;}
      if(yVVHAabQCT == true){yVVHAabQCT = false;}
      if(YrimKPZgUo == true){YrimKPZgUo = false;}
      if(GwQpSpQOwt == true){GwQpSpQOwt = false;}
      if(DftGuFfQfE == true){DftGuFfQfE = false;}
      if(qoPwNdXfPQ == true){qoPwNdXfPQ = false;}
      if(ylOzGCFfoJ == true){ylOzGCFfoJ = false;}
      if(JNTHPsxbqF == true){JNTHPsxbqF = false;}
      if(iIAPxRgTbn == true){iIAPxRgTbn = false;}
      if(SkyeuRRtAs == true){SkyeuRRtAs = false;}
      if(AAaWtdUHgU == true){AAaWtdUHgU = false;}
      if(gunKgokyBn == true){gunKgokyBn = false;}
      if(VkDBqYOoLy == true){VkDBqYOoLy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFUWLYOPXW
{ 
  void SeyLwCVhxb()
  { 
      bool DNrfiGObMz = false;
      bool jzfbPpQqoc = false;
      bool iLKBBMWDBm = false;
      bool xUnhIcJyAP = false;
      bool CgEckJGtRP = false;
      bool gcVaIrDqdV = false;
      bool iKaZCOKySl = false;
      bool gRqZaCGhQr = false;
      bool FckkFUzNYP = false;
      bool ZRUdfqFeZV = false;
      bool zIaehPkuAG = false;
      bool kValQFZoUh = false;
      bool PxYDMOxNsi = false;
      bool xbHtswCFCp = false;
      bool jDNSdEqhMZ = false;
      bool QPJrFBjWST = false;
      bool RWBQJJNfsT = false;
      bool DTmdyMiFYH = false;
      bool XOATSgRPnq = false;
      bool MemiXMBxJU = false;
      string IwHlBTnZVr;
      string URyXfNTTbU;
      string anKBcINtMG;
      string BWKDpLnfui;
      string wlFScZbACY;
      string xpjFxTkFJr;
      string GtNPpyHuhT;
      string ZmYsXnirYC;
      string gMqnILlEFV;
      string ZhVCbCYpcd;
      string RfShyJRqhI;
      string ksgGLsCZGe;
      string MCoLtrRVQV;
      string PrPtjAtJoy;
      string stWxkgAOqh;
      string zzjxRPqGnG;
      string ruZLsrcmWK;
      string zrkHkRfraM;
      string qCeiVQIRcU;
      string ImVhGyTKDr;
      if(IwHlBTnZVr == RfShyJRqhI){DNrfiGObMz = true;}
      else if(RfShyJRqhI == IwHlBTnZVr){zIaehPkuAG = true;}
      if(URyXfNTTbU == ksgGLsCZGe){jzfbPpQqoc = true;}
      else if(ksgGLsCZGe == URyXfNTTbU){kValQFZoUh = true;}
      if(anKBcINtMG == MCoLtrRVQV){iLKBBMWDBm = true;}
      else if(MCoLtrRVQV == anKBcINtMG){PxYDMOxNsi = true;}
      if(BWKDpLnfui == PrPtjAtJoy){xUnhIcJyAP = true;}
      else if(PrPtjAtJoy == BWKDpLnfui){xbHtswCFCp = true;}
      if(wlFScZbACY == stWxkgAOqh){CgEckJGtRP = true;}
      else if(stWxkgAOqh == wlFScZbACY){jDNSdEqhMZ = true;}
      if(xpjFxTkFJr == zzjxRPqGnG){gcVaIrDqdV = true;}
      else if(zzjxRPqGnG == xpjFxTkFJr){QPJrFBjWST = true;}
      if(GtNPpyHuhT == ruZLsrcmWK){iKaZCOKySl = true;}
      else if(ruZLsrcmWK == GtNPpyHuhT){RWBQJJNfsT = true;}
      if(ZmYsXnirYC == zrkHkRfraM){gRqZaCGhQr = true;}
      if(gMqnILlEFV == qCeiVQIRcU){FckkFUzNYP = true;}
      if(ZhVCbCYpcd == ImVhGyTKDr){ZRUdfqFeZV = true;}
      while(zrkHkRfraM == ZmYsXnirYC){DTmdyMiFYH = true;}
      while(qCeiVQIRcU == qCeiVQIRcU){XOATSgRPnq = true;}
      while(ImVhGyTKDr == ImVhGyTKDr){MemiXMBxJU = true;}
      if(DNrfiGObMz == true){DNrfiGObMz = false;}
      if(jzfbPpQqoc == true){jzfbPpQqoc = false;}
      if(iLKBBMWDBm == true){iLKBBMWDBm = false;}
      if(xUnhIcJyAP == true){xUnhIcJyAP = false;}
      if(CgEckJGtRP == true){CgEckJGtRP = false;}
      if(gcVaIrDqdV == true){gcVaIrDqdV = false;}
      if(iKaZCOKySl == true){iKaZCOKySl = false;}
      if(gRqZaCGhQr == true){gRqZaCGhQr = false;}
      if(FckkFUzNYP == true){FckkFUzNYP = false;}
      if(ZRUdfqFeZV == true){ZRUdfqFeZV = false;}
      if(zIaehPkuAG == true){zIaehPkuAG = false;}
      if(kValQFZoUh == true){kValQFZoUh = false;}
      if(PxYDMOxNsi == true){PxYDMOxNsi = false;}
      if(xbHtswCFCp == true){xbHtswCFCp = false;}
      if(jDNSdEqhMZ == true){jDNSdEqhMZ = false;}
      if(QPJrFBjWST == true){QPJrFBjWST = false;}
      if(RWBQJJNfsT == true){RWBQJJNfsT = false;}
      if(DTmdyMiFYH == true){DTmdyMiFYH = false;}
      if(XOATSgRPnq == true){XOATSgRPnq = false;}
      if(MemiXMBxJU == true){MemiXMBxJU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLPIREEKLT
{ 
  void HSALPIOCkW()
  { 
      bool eXTtcOFdKT = false;
      bool TXFltcqbAL = false;
      bool CBEdOtAfae = false;
      bool hxDSHlKKLK = false;
      bool WTomgaeQjA = false;
      bool AsPnwcToeh = false;
      bool OYCekWUmdI = false;
      bool SfQpohMQxn = false;
      bool PiuaeogOVd = false;
      bool SUfdwxRKCK = false;
      bool GqlbhTcZzO = false;
      bool QCrqRedaAu = false;
      bool oGQzpxAltq = false;
      bool QCOmhXwTsK = false;
      bool LHOHNPcoLQ = false;
      bool TpJGUzalkj = false;
      bool TpeIxOmFJt = false;
      bool hKhpigrIlZ = false;
      bool ULacWarHRh = false;
      bool wJhIpVbFKz = false;
      string sphGScBeVX;
      string wcXeMarqZo;
      string tAeyVgqzBF;
      string OFPHcbIzhh;
      string zpqCFzkrdR;
      string fRFHkrLikk;
      string lBdQIqMPCk;
      string SsJrpEJbsV;
      string wyViYxAIWj;
      string QYOwuyLatO;
      string lUpsymINRg;
      string iipOomfuqL;
      string qEsRTsdMwq;
      string rhhdiaIbjl;
      string nlpoAgizHH;
      string SPihXhbXYE;
      string IwQZnBBLeN;
      string eDKFXENDRm;
      string KeEnYbyzGB;
      string yjDedrVQAz;
      if(sphGScBeVX == lUpsymINRg){eXTtcOFdKT = true;}
      else if(lUpsymINRg == sphGScBeVX){GqlbhTcZzO = true;}
      if(wcXeMarqZo == iipOomfuqL){TXFltcqbAL = true;}
      else if(iipOomfuqL == wcXeMarqZo){QCrqRedaAu = true;}
      if(tAeyVgqzBF == qEsRTsdMwq){CBEdOtAfae = true;}
      else if(qEsRTsdMwq == tAeyVgqzBF){oGQzpxAltq = true;}
      if(OFPHcbIzhh == rhhdiaIbjl){hxDSHlKKLK = true;}
      else if(rhhdiaIbjl == OFPHcbIzhh){QCOmhXwTsK = true;}
      if(zpqCFzkrdR == nlpoAgizHH){WTomgaeQjA = true;}
      else if(nlpoAgizHH == zpqCFzkrdR){LHOHNPcoLQ = true;}
      if(fRFHkrLikk == SPihXhbXYE){AsPnwcToeh = true;}
      else if(SPihXhbXYE == fRFHkrLikk){TpJGUzalkj = true;}
      if(lBdQIqMPCk == IwQZnBBLeN){OYCekWUmdI = true;}
      else if(IwQZnBBLeN == lBdQIqMPCk){TpeIxOmFJt = true;}
      if(SsJrpEJbsV == eDKFXENDRm){SfQpohMQxn = true;}
      if(wyViYxAIWj == KeEnYbyzGB){PiuaeogOVd = true;}
      if(QYOwuyLatO == yjDedrVQAz){SUfdwxRKCK = true;}
      while(eDKFXENDRm == SsJrpEJbsV){hKhpigrIlZ = true;}
      while(KeEnYbyzGB == KeEnYbyzGB){ULacWarHRh = true;}
      while(yjDedrVQAz == yjDedrVQAz){wJhIpVbFKz = true;}
      if(eXTtcOFdKT == true){eXTtcOFdKT = false;}
      if(TXFltcqbAL == true){TXFltcqbAL = false;}
      if(CBEdOtAfae == true){CBEdOtAfae = false;}
      if(hxDSHlKKLK == true){hxDSHlKKLK = false;}
      if(WTomgaeQjA == true){WTomgaeQjA = false;}
      if(AsPnwcToeh == true){AsPnwcToeh = false;}
      if(OYCekWUmdI == true){OYCekWUmdI = false;}
      if(SfQpohMQxn == true){SfQpohMQxn = false;}
      if(PiuaeogOVd == true){PiuaeogOVd = false;}
      if(SUfdwxRKCK == true){SUfdwxRKCK = false;}
      if(GqlbhTcZzO == true){GqlbhTcZzO = false;}
      if(QCrqRedaAu == true){QCrqRedaAu = false;}
      if(oGQzpxAltq == true){oGQzpxAltq = false;}
      if(QCOmhXwTsK == true){QCOmhXwTsK = false;}
      if(LHOHNPcoLQ == true){LHOHNPcoLQ = false;}
      if(TpJGUzalkj == true){TpJGUzalkj = false;}
      if(TpeIxOmFJt == true){TpeIxOmFJt = false;}
      if(hKhpigrIlZ == true){hKhpigrIlZ = false;}
      if(ULacWarHRh == true){ULacWarHRh = false;}
      if(wJhIpVbFKz == true){wJhIpVbFKz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNFGGNFUGX
{ 
  void YVGGfUdfkN()
  { 
      bool eflFLaQOzg = false;
      bool wjkuQeTjHJ = false;
      bool otmdVXHyMZ = false;
      bool ZUJTwQyhyr = false;
      bool CNwYEbnLRd = false;
      bool XNapaksHin = false;
      bool SSBZGbaQzz = false;
      bool flkPHaxNZs = false;
      bool jugiBMsTsK = false;
      bool XqyJYiLVSc = false;
      bool BWMRylbLiz = false;
      bool mfgpEXkSYt = false;
      bool hGXnbnmbpX = false;
      bool PatxqMiOkO = false;
      bool jhjtWrKIEB = false;
      bool ysxXtuzXpJ = false;
      bool zAUKjMkiyq = false;
      bool nVhJKzVcQi = false;
      bool ddWoZWdWCw = false;
      bool NKYaPiNZKK = false;
      string XjDfKHmUpZ;
      string BdLBANqRjW;
      string UEhTkemsOG;
      string YhWDbcNrKS;
      string deNknVoJsi;
      string QpcchSCjuf;
      string TtGjBTHHYX;
      string zzGQsopxfO;
      string odAepiEsVI;
      string ZdxeyjYdiT;
      string NgjUiRiMjs;
      string cEEfpptbtR;
      string PNlPxVBbSI;
      string QLNLAHseuX;
      string zqJbfVYQnI;
      string pxjREAtUWN;
      string PHtacQpsei;
      string wOfVRXDJib;
      string wkmJSSbwGA;
      string MYHhIrxizP;
      if(XjDfKHmUpZ == NgjUiRiMjs){eflFLaQOzg = true;}
      else if(NgjUiRiMjs == XjDfKHmUpZ){BWMRylbLiz = true;}
      if(BdLBANqRjW == cEEfpptbtR){wjkuQeTjHJ = true;}
      else if(cEEfpptbtR == BdLBANqRjW){mfgpEXkSYt = true;}
      if(UEhTkemsOG == PNlPxVBbSI){otmdVXHyMZ = true;}
      else if(PNlPxVBbSI == UEhTkemsOG){hGXnbnmbpX = true;}
      if(YhWDbcNrKS == QLNLAHseuX){ZUJTwQyhyr = true;}
      else if(QLNLAHseuX == YhWDbcNrKS){PatxqMiOkO = true;}
      if(deNknVoJsi == zqJbfVYQnI){CNwYEbnLRd = true;}
      else if(zqJbfVYQnI == deNknVoJsi){jhjtWrKIEB = true;}
      if(QpcchSCjuf == pxjREAtUWN){XNapaksHin = true;}
      else if(pxjREAtUWN == QpcchSCjuf){ysxXtuzXpJ = true;}
      if(TtGjBTHHYX == PHtacQpsei){SSBZGbaQzz = true;}
      else if(PHtacQpsei == TtGjBTHHYX){zAUKjMkiyq = true;}
      if(zzGQsopxfO == wOfVRXDJib){flkPHaxNZs = true;}
      if(odAepiEsVI == wkmJSSbwGA){jugiBMsTsK = true;}
      if(ZdxeyjYdiT == MYHhIrxizP){XqyJYiLVSc = true;}
      while(wOfVRXDJib == zzGQsopxfO){nVhJKzVcQi = true;}
      while(wkmJSSbwGA == wkmJSSbwGA){ddWoZWdWCw = true;}
      while(MYHhIrxizP == MYHhIrxizP){NKYaPiNZKK = true;}
      if(eflFLaQOzg == true){eflFLaQOzg = false;}
      if(wjkuQeTjHJ == true){wjkuQeTjHJ = false;}
      if(otmdVXHyMZ == true){otmdVXHyMZ = false;}
      if(ZUJTwQyhyr == true){ZUJTwQyhyr = false;}
      if(CNwYEbnLRd == true){CNwYEbnLRd = false;}
      if(XNapaksHin == true){XNapaksHin = false;}
      if(SSBZGbaQzz == true){SSBZGbaQzz = false;}
      if(flkPHaxNZs == true){flkPHaxNZs = false;}
      if(jugiBMsTsK == true){jugiBMsTsK = false;}
      if(XqyJYiLVSc == true){XqyJYiLVSc = false;}
      if(BWMRylbLiz == true){BWMRylbLiz = false;}
      if(mfgpEXkSYt == true){mfgpEXkSYt = false;}
      if(hGXnbnmbpX == true){hGXnbnmbpX = false;}
      if(PatxqMiOkO == true){PatxqMiOkO = false;}
      if(jhjtWrKIEB == true){jhjtWrKIEB = false;}
      if(ysxXtuzXpJ == true){ysxXtuzXpJ = false;}
      if(zAUKjMkiyq == true){zAUKjMkiyq = false;}
      if(nVhJKzVcQi == true){nVhJKzVcQi = false;}
      if(ddWoZWdWCw == true){ddWoZWdWCw = false;}
      if(NKYaPiNZKK == true){NKYaPiNZKK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDDHNBAATI
{ 
  void ztxcZYKzwa()
  { 
      bool ULuUoiHgQj = false;
      bool RWWZHAPPfW = false;
      bool bdbdCpKKki = false;
      bool FmFlnLmhtp = false;
      bool UPpylYjPmY = false;
      bool TbwLnqjQSy = false;
      bool YxwheeQkku = false;
      bool MhUoCLmdqc = false;
      bool FtWMOcqtxx = false;
      bool bVOuRWTISH = false;
      bool HzerLlGGJb = false;
      bool DFZosdZiSB = false;
      bool mWmmSqSZXe = false;
      bool rdKjVFPeAc = false;
      bool WjjUtVwZCn = false;
      bool xjpRTkMqZU = false;
      bool SgidiYuoTm = false;
      bool NthpeClRsw = false;
      bool tsWigInsPj = false;
      bool sXFfKoBGkU = false;
      string wnSnPaWuij;
      string RomEJCtLcc;
      string DjOFBTBXQK;
      string XSnsNJJkSp;
      string IWjRThdGzR;
      string FgHlVMZMmu;
      string ZydYMyAtqA;
      string rJslUgAwlS;
      string puYzEpKBWA;
      string ixxXQJrLFU;
      string giOzZunURn;
      string McaTEdZeTV;
      string mzXpQtMUVK;
      string onqQlGfYZI;
      string CpjhnGVcSl;
      string jMrjhhLYie;
      string iSyGzXkKhx;
      string xAFKSxPoBJ;
      string XiCiZbwHhE;
      string uHotZjqciP;
      if(wnSnPaWuij == giOzZunURn){ULuUoiHgQj = true;}
      else if(giOzZunURn == wnSnPaWuij){HzerLlGGJb = true;}
      if(RomEJCtLcc == McaTEdZeTV){RWWZHAPPfW = true;}
      else if(McaTEdZeTV == RomEJCtLcc){DFZosdZiSB = true;}
      if(DjOFBTBXQK == mzXpQtMUVK){bdbdCpKKki = true;}
      else if(mzXpQtMUVK == DjOFBTBXQK){mWmmSqSZXe = true;}
      if(XSnsNJJkSp == onqQlGfYZI){FmFlnLmhtp = true;}
      else if(onqQlGfYZI == XSnsNJJkSp){rdKjVFPeAc = true;}
      if(IWjRThdGzR == CpjhnGVcSl){UPpylYjPmY = true;}
      else if(CpjhnGVcSl == IWjRThdGzR){WjjUtVwZCn = true;}
      if(FgHlVMZMmu == jMrjhhLYie){TbwLnqjQSy = true;}
      else if(jMrjhhLYie == FgHlVMZMmu){xjpRTkMqZU = true;}
      if(ZydYMyAtqA == iSyGzXkKhx){YxwheeQkku = true;}
      else if(iSyGzXkKhx == ZydYMyAtqA){SgidiYuoTm = true;}
      if(rJslUgAwlS == xAFKSxPoBJ){MhUoCLmdqc = true;}
      if(puYzEpKBWA == XiCiZbwHhE){FtWMOcqtxx = true;}
      if(ixxXQJrLFU == uHotZjqciP){bVOuRWTISH = true;}
      while(xAFKSxPoBJ == rJslUgAwlS){NthpeClRsw = true;}
      while(XiCiZbwHhE == XiCiZbwHhE){tsWigInsPj = true;}
      while(uHotZjqciP == uHotZjqciP){sXFfKoBGkU = true;}
      if(ULuUoiHgQj == true){ULuUoiHgQj = false;}
      if(RWWZHAPPfW == true){RWWZHAPPfW = false;}
      if(bdbdCpKKki == true){bdbdCpKKki = false;}
      if(FmFlnLmhtp == true){FmFlnLmhtp = false;}
      if(UPpylYjPmY == true){UPpylYjPmY = false;}
      if(TbwLnqjQSy == true){TbwLnqjQSy = false;}
      if(YxwheeQkku == true){YxwheeQkku = false;}
      if(MhUoCLmdqc == true){MhUoCLmdqc = false;}
      if(FtWMOcqtxx == true){FtWMOcqtxx = false;}
      if(bVOuRWTISH == true){bVOuRWTISH = false;}
      if(HzerLlGGJb == true){HzerLlGGJb = false;}
      if(DFZosdZiSB == true){DFZosdZiSB = false;}
      if(mWmmSqSZXe == true){mWmmSqSZXe = false;}
      if(rdKjVFPeAc == true){rdKjVFPeAc = false;}
      if(WjjUtVwZCn == true){WjjUtVwZCn = false;}
      if(xjpRTkMqZU == true){xjpRTkMqZU = false;}
      if(SgidiYuoTm == true){SgidiYuoTm = false;}
      if(NthpeClRsw == true){NthpeClRsw = false;}
      if(tsWigInsPj == true){tsWigInsPj = false;}
      if(sXFfKoBGkU == true){sXFfKoBGkU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRUKJOQABU
{ 
  void phyXCSotUx()
  { 
      bool iTyrqKwOZQ = false;
      bool LBBMupEDJr = false;
      bool KDRDcxJUVm = false;
      bool zHVSBWcBCg = false;
      bool PjhlswsZKZ = false;
      bool wJyAxfCuOt = false;
      bool AarmQDfiKY = false;
      bool MCBcbaUeKg = false;
      bool DiJwppJUVV = false;
      bool ThmIgnquUo = false;
      bool PJPlMsIVYV = false;
      bool KWjgpQRwwZ = false;
      bool tLNnEdPrum = false;
      bool jYKUQtSXix = false;
      bool hmwzLwxFRP = false;
      bool WtztuEwbgi = false;
      bool cPZkllMPQw = false;
      bool xtNyrGOOcI = false;
      bool fKafQoYPZL = false;
      bool xqpzTSNKMZ = false;
      string NPUwBiyTSq;
      string wmyNkmxPiZ;
      string qnPoYSbBrP;
      string tnAAxbTSrG;
      string kQWuIobjlj;
      string fiDoNYAfXh;
      string HwaDwImyPI;
      string SdXbnZRTfi;
      string qqOIiKkLlY;
      string bnuJzopTyA;
      string CcTdQBLaBn;
      string HgznpPhSTl;
      string WaMqfeiNcz;
      string jyUffOXkqh;
      string yKKxQunGTi;
      string HWzMcbQbxl;
      string RyxCEJLTHb;
      string rwakmMQOak;
      string pbssrMyICE;
      string yumFPAMIsH;
      if(NPUwBiyTSq == CcTdQBLaBn){iTyrqKwOZQ = true;}
      else if(CcTdQBLaBn == NPUwBiyTSq){PJPlMsIVYV = true;}
      if(wmyNkmxPiZ == HgznpPhSTl){LBBMupEDJr = true;}
      else if(HgznpPhSTl == wmyNkmxPiZ){KWjgpQRwwZ = true;}
      if(qnPoYSbBrP == WaMqfeiNcz){KDRDcxJUVm = true;}
      else if(WaMqfeiNcz == qnPoYSbBrP){tLNnEdPrum = true;}
      if(tnAAxbTSrG == jyUffOXkqh){zHVSBWcBCg = true;}
      else if(jyUffOXkqh == tnAAxbTSrG){jYKUQtSXix = true;}
      if(kQWuIobjlj == yKKxQunGTi){PjhlswsZKZ = true;}
      else if(yKKxQunGTi == kQWuIobjlj){hmwzLwxFRP = true;}
      if(fiDoNYAfXh == HWzMcbQbxl){wJyAxfCuOt = true;}
      else if(HWzMcbQbxl == fiDoNYAfXh){WtztuEwbgi = true;}
      if(HwaDwImyPI == RyxCEJLTHb){AarmQDfiKY = true;}
      else if(RyxCEJLTHb == HwaDwImyPI){cPZkllMPQw = true;}
      if(SdXbnZRTfi == rwakmMQOak){MCBcbaUeKg = true;}
      if(qqOIiKkLlY == pbssrMyICE){DiJwppJUVV = true;}
      if(bnuJzopTyA == yumFPAMIsH){ThmIgnquUo = true;}
      while(rwakmMQOak == SdXbnZRTfi){xtNyrGOOcI = true;}
      while(pbssrMyICE == pbssrMyICE){fKafQoYPZL = true;}
      while(yumFPAMIsH == yumFPAMIsH){xqpzTSNKMZ = true;}
      if(iTyrqKwOZQ == true){iTyrqKwOZQ = false;}
      if(LBBMupEDJr == true){LBBMupEDJr = false;}
      if(KDRDcxJUVm == true){KDRDcxJUVm = false;}
      if(zHVSBWcBCg == true){zHVSBWcBCg = false;}
      if(PjhlswsZKZ == true){PjhlswsZKZ = false;}
      if(wJyAxfCuOt == true){wJyAxfCuOt = false;}
      if(AarmQDfiKY == true){AarmQDfiKY = false;}
      if(MCBcbaUeKg == true){MCBcbaUeKg = false;}
      if(DiJwppJUVV == true){DiJwppJUVV = false;}
      if(ThmIgnquUo == true){ThmIgnquUo = false;}
      if(PJPlMsIVYV == true){PJPlMsIVYV = false;}
      if(KWjgpQRwwZ == true){KWjgpQRwwZ = false;}
      if(tLNnEdPrum == true){tLNnEdPrum = false;}
      if(jYKUQtSXix == true){jYKUQtSXix = false;}
      if(hmwzLwxFRP == true){hmwzLwxFRP = false;}
      if(WtztuEwbgi == true){WtztuEwbgi = false;}
      if(cPZkllMPQw == true){cPZkllMPQw = false;}
      if(xtNyrGOOcI == true){xtNyrGOOcI = false;}
      if(fKafQoYPZL == true){fKafQoYPZL = false;}
      if(xqpzTSNKMZ == true){xqpzTSNKMZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SRAJDOFHNB
{ 
  void RnWPUbJFjc()
  { 
      bool tJndndqjrG = false;
      bool FrEaTboFNa = false;
      bool WDAdnjOgCl = false;
      bool TRkVcDqKIu = false;
      bool JTPVmcEJDB = false;
      bool eJWQHqIKoD = false;
      bool OJhGlmGiyP = false;
      bool jdxRQDmepK = false;
      bool fFdBGJtUNl = false;
      bool ufVEfzlJiz = false;
      bool VVLmQBMFzE = false;
      bool DdTdXJffzc = false;
      bool rlULUDIrkR = false;
      bool QdwpnKtpkF = false;
      bool xoUJhRMqgW = false;
      bool TGJFHjAzSM = false;
      bool rUThmZgdpN = false;
      bool PouteDRLcD = false;
      bool qQKOyKTpiE = false;
      bool JtXXMcUlVI = false;
      string XuoVjchnws;
      string sXyJsINbqf;
      string raVqNTukwA;
      string hweKzudpGW;
      string LtaNkcHVZL;
      string UbzNTwYyHP;
      string hwruKwsnJy;
      string eXUTUxAIFk;
      string MZLjfGxRpC;
      string VehqoPCeCn;
      string jTLbgwHfsW;
      string wQsWCHjHPE;
      string zbxGczpcdF;
      string uUFQArNjDj;
      string yQYTGElKng;
      string etPyoIWEzg;
      string GdBnbbKbVK;
      string sADfFiCdAX;
      string NeowZAEHbr;
      string VJkWcTOkre;
      if(XuoVjchnws == jTLbgwHfsW){tJndndqjrG = true;}
      else if(jTLbgwHfsW == XuoVjchnws){VVLmQBMFzE = true;}
      if(sXyJsINbqf == wQsWCHjHPE){FrEaTboFNa = true;}
      else if(wQsWCHjHPE == sXyJsINbqf){DdTdXJffzc = true;}
      if(raVqNTukwA == zbxGczpcdF){WDAdnjOgCl = true;}
      else if(zbxGczpcdF == raVqNTukwA){rlULUDIrkR = true;}
      if(hweKzudpGW == uUFQArNjDj){TRkVcDqKIu = true;}
      else if(uUFQArNjDj == hweKzudpGW){QdwpnKtpkF = true;}
      if(LtaNkcHVZL == yQYTGElKng){JTPVmcEJDB = true;}
      else if(yQYTGElKng == LtaNkcHVZL){xoUJhRMqgW = true;}
      if(UbzNTwYyHP == etPyoIWEzg){eJWQHqIKoD = true;}
      else if(etPyoIWEzg == UbzNTwYyHP){TGJFHjAzSM = true;}
      if(hwruKwsnJy == GdBnbbKbVK){OJhGlmGiyP = true;}
      else if(GdBnbbKbVK == hwruKwsnJy){rUThmZgdpN = true;}
      if(eXUTUxAIFk == sADfFiCdAX){jdxRQDmepK = true;}
      if(MZLjfGxRpC == NeowZAEHbr){fFdBGJtUNl = true;}
      if(VehqoPCeCn == VJkWcTOkre){ufVEfzlJiz = true;}
      while(sADfFiCdAX == eXUTUxAIFk){PouteDRLcD = true;}
      while(NeowZAEHbr == NeowZAEHbr){qQKOyKTpiE = true;}
      while(VJkWcTOkre == VJkWcTOkre){JtXXMcUlVI = true;}
      if(tJndndqjrG == true){tJndndqjrG = false;}
      if(FrEaTboFNa == true){FrEaTboFNa = false;}
      if(WDAdnjOgCl == true){WDAdnjOgCl = false;}
      if(TRkVcDqKIu == true){TRkVcDqKIu = false;}
      if(JTPVmcEJDB == true){JTPVmcEJDB = false;}
      if(eJWQHqIKoD == true){eJWQHqIKoD = false;}
      if(OJhGlmGiyP == true){OJhGlmGiyP = false;}
      if(jdxRQDmepK == true){jdxRQDmepK = false;}
      if(fFdBGJtUNl == true){fFdBGJtUNl = false;}
      if(ufVEfzlJiz == true){ufVEfzlJiz = false;}
      if(VVLmQBMFzE == true){VVLmQBMFzE = false;}
      if(DdTdXJffzc == true){DdTdXJffzc = false;}
      if(rlULUDIrkR == true){rlULUDIrkR = false;}
      if(QdwpnKtpkF == true){QdwpnKtpkF = false;}
      if(xoUJhRMqgW == true){xoUJhRMqgW = false;}
      if(TGJFHjAzSM == true){TGJFHjAzSM = false;}
      if(rUThmZgdpN == true){rUThmZgdpN = false;}
      if(PouteDRLcD == true){PouteDRLcD = false;}
      if(qQKOyKTpiE == true){qQKOyKTpiE = false;}
      if(JtXXMcUlVI == true){JtXXMcUlVI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXELHXFZVU
{ 
  void koQNFhJMeM()
  { 
      bool bDkSIYJmUl = false;
      bool qtPAzuhony = false;
      bool rrxmUnTLLr = false;
      bool lJDmxALyVT = false;
      bool AFKLDzumyi = false;
      bool JkEygiGyxU = false;
      bool EyacAgqbDz = false;
      bool iiSUxlhkiV = false;
      bool rfMchAFEGN = false;
      bool tMABOCegKW = false;
      bool ISizzaSjBt = false;
      bool AVObbXkytA = false;
      bool bmUpEWhQGt = false;
      bool HAZLMYxNcH = false;
      bool hVCMMXyYZp = false;
      bool RgmKuVystc = false;
      bool rBcHmAuDOC = false;
      bool aWVmSFjIcg = false;
      bool XJqQcaNOQq = false;
      bool aDTzPfruYM = false;
      string MqHZdxdZXE;
      string oYZcMhYVuR;
      string yqSLrjZtIj;
      string ijPemfmVgQ;
      string nsdCJfunfB;
      string IojioUYuhs;
      string XjRnVFIuog;
      string uCnecEMQBL;
      string olNHaszfoR;
      string HrnmsDbpgE;
      string WAzzGFBFGj;
      string HHsVElWJMb;
      string FcFWYCOAlY;
      string bWjxnomOBV;
      string rtZFKzzRiH;
      string gRdEyttbZD;
      string qATgHkXugP;
      string yIIpjLDAMY;
      string DwRerJseyt;
      string tKnxdrZsxY;
      if(MqHZdxdZXE == WAzzGFBFGj){bDkSIYJmUl = true;}
      else if(WAzzGFBFGj == MqHZdxdZXE){ISizzaSjBt = true;}
      if(oYZcMhYVuR == HHsVElWJMb){qtPAzuhony = true;}
      else if(HHsVElWJMb == oYZcMhYVuR){AVObbXkytA = true;}
      if(yqSLrjZtIj == FcFWYCOAlY){rrxmUnTLLr = true;}
      else if(FcFWYCOAlY == yqSLrjZtIj){bmUpEWhQGt = true;}
      if(ijPemfmVgQ == bWjxnomOBV){lJDmxALyVT = true;}
      else if(bWjxnomOBV == ijPemfmVgQ){HAZLMYxNcH = true;}
      if(nsdCJfunfB == rtZFKzzRiH){AFKLDzumyi = true;}
      else if(rtZFKzzRiH == nsdCJfunfB){hVCMMXyYZp = true;}
      if(IojioUYuhs == gRdEyttbZD){JkEygiGyxU = true;}
      else if(gRdEyttbZD == IojioUYuhs){RgmKuVystc = true;}
      if(XjRnVFIuog == qATgHkXugP){EyacAgqbDz = true;}
      else if(qATgHkXugP == XjRnVFIuog){rBcHmAuDOC = true;}
      if(uCnecEMQBL == yIIpjLDAMY){iiSUxlhkiV = true;}
      if(olNHaszfoR == DwRerJseyt){rfMchAFEGN = true;}
      if(HrnmsDbpgE == tKnxdrZsxY){tMABOCegKW = true;}
      while(yIIpjLDAMY == uCnecEMQBL){aWVmSFjIcg = true;}
      while(DwRerJseyt == DwRerJseyt){XJqQcaNOQq = true;}
      while(tKnxdrZsxY == tKnxdrZsxY){aDTzPfruYM = true;}
      if(bDkSIYJmUl == true){bDkSIYJmUl = false;}
      if(qtPAzuhony == true){qtPAzuhony = false;}
      if(rrxmUnTLLr == true){rrxmUnTLLr = false;}
      if(lJDmxALyVT == true){lJDmxALyVT = false;}
      if(AFKLDzumyi == true){AFKLDzumyi = false;}
      if(JkEygiGyxU == true){JkEygiGyxU = false;}
      if(EyacAgqbDz == true){EyacAgqbDz = false;}
      if(iiSUxlhkiV == true){iiSUxlhkiV = false;}
      if(rfMchAFEGN == true){rfMchAFEGN = false;}
      if(tMABOCegKW == true){tMABOCegKW = false;}
      if(ISizzaSjBt == true){ISizzaSjBt = false;}
      if(AVObbXkytA == true){AVObbXkytA = false;}
      if(bmUpEWhQGt == true){bmUpEWhQGt = false;}
      if(HAZLMYxNcH == true){HAZLMYxNcH = false;}
      if(hVCMMXyYZp == true){hVCMMXyYZp = false;}
      if(RgmKuVystc == true){RgmKuVystc = false;}
      if(rBcHmAuDOC == true){rBcHmAuDOC = false;}
      if(aWVmSFjIcg == true){aWVmSFjIcg = false;}
      if(XJqQcaNOQq == true){XJqQcaNOQq = false;}
      if(aDTzPfruYM == true){aDTzPfruYM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GICGDRLLGK
{ 
  void sQeWTjNqsC()
  { 
      bool AmoLlJxWne = false;
      bool YzkrtwqkII = false;
      bool hyJRODMKZW = false;
      bool majUUyOiey = false;
      bool NyGrIkKBLx = false;
      bool OfIlYBcWwh = false;
      bool xlwQrxOPXu = false;
      bool gHGKtjrQJc = false;
      bool rKzbHHRxwS = false;
      bool UrlwAaBoAK = false;
      bool WudPQHZyrn = false;
      bool IMMTpmmUJk = false;
      bool eRSEanUJKS = false;
      bool iDQyGwgiKA = false;
      bool hTFHKIfSGN = false;
      bool nffPfEbYob = false;
      bool lPnYFFuOMs = false;
      bool FEJIDLLLtS = false;
      bool IBCweCWBSB = false;
      bool UHsiORfgCE = false;
      string IfWfYmSCOH;
      string aVyTIaJNIc;
      string lagTnSVVaM;
      string FbTuHwLdgL;
      string ZtIlFwcMmC;
      string YXCslgyCqF;
      string RwbCByCDML;
      string PegwCrRtOr;
      string oJiYnhZZIZ;
      string xImasdRFjH;
      string sZzblsqFpt;
      string PEnyPINDOT;
      string XbtlNGrFCY;
      string ZLKGyPJHlt;
      string qTiOKsUnKk;
      string QOqQiReNNf;
      string AkCRTDsgzz;
      string zGQTbEsebU;
      string kEtRILUtXg;
      string kwtGtFQRuG;
      if(IfWfYmSCOH == sZzblsqFpt){AmoLlJxWne = true;}
      else if(sZzblsqFpt == IfWfYmSCOH){WudPQHZyrn = true;}
      if(aVyTIaJNIc == PEnyPINDOT){YzkrtwqkII = true;}
      else if(PEnyPINDOT == aVyTIaJNIc){IMMTpmmUJk = true;}
      if(lagTnSVVaM == XbtlNGrFCY){hyJRODMKZW = true;}
      else if(XbtlNGrFCY == lagTnSVVaM){eRSEanUJKS = true;}
      if(FbTuHwLdgL == ZLKGyPJHlt){majUUyOiey = true;}
      else if(ZLKGyPJHlt == FbTuHwLdgL){iDQyGwgiKA = true;}
      if(ZtIlFwcMmC == qTiOKsUnKk){NyGrIkKBLx = true;}
      else if(qTiOKsUnKk == ZtIlFwcMmC){hTFHKIfSGN = true;}
      if(YXCslgyCqF == QOqQiReNNf){OfIlYBcWwh = true;}
      else if(QOqQiReNNf == YXCslgyCqF){nffPfEbYob = true;}
      if(RwbCByCDML == AkCRTDsgzz){xlwQrxOPXu = true;}
      else if(AkCRTDsgzz == RwbCByCDML){lPnYFFuOMs = true;}
      if(PegwCrRtOr == zGQTbEsebU){gHGKtjrQJc = true;}
      if(oJiYnhZZIZ == kEtRILUtXg){rKzbHHRxwS = true;}
      if(xImasdRFjH == kwtGtFQRuG){UrlwAaBoAK = true;}
      while(zGQTbEsebU == PegwCrRtOr){FEJIDLLLtS = true;}
      while(kEtRILUtXg == kEtRILUtXg){IBCweCWBSB = true;}
      while(kwtGtFQRuG == kwtGtFQRuG){UHsiORfgCE = true;}
      if(AmoLlJxWne == true){AmoLlJxWne = false;}
      if(YzkrtwqkII == true){YzkrtwqkII = false;}
      if(hyJRODMKZW == true){hyJRODMKZW = false;}
      if(majUUyOiey == true){majUUyOiey = false;}
      if(NyGrIkKBLx == true){NyGrIkKBLx = false;}
      if(OfIlYBcWwh == true){OfIlYBcWwh = false;}
      if(xlwQrxOPXu == true){xlwQrxOPXu = false;}
      if(gHGKtjrQJc == true){gHGKtjrQJc = false;}
      if(rKzbHHRxwS == true){rKzbHHRxwS = false;}
      if(UrlwAaBoAK == true){UrlwAaBoAK = false;}
      if(WudPQHZyrn == true){WudPQHZyrn = false;}
      if(IMMTpmmUJk == true){IMMTpmmUJk = false;}
      if(eRSEanUJKS == true){eRSEanUJKS = false;}
      if(iDQyGwgiKA == true){iDQyGwgiKA = false;}
      if(hTFHKIfSGN == true){hTFHKIfSGN = false;}
      if(nffPfEbYob == true){nffPfEbYob = false;}
      if(lPnYFFuOMs == true){lPnYFFuOMs = false;}
      if(FEJIDLLLtS == true){FEJIDLLLtS = false;}
      if(IBCweCWBSB == true){IBCweCWBSB = false;}
      if(UHsiORfgCE == true){UHsiORfgCE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTFAXDANWZ
{ 
  void HORLkVcwNz()
  { 
      bool MiLIaoUNUF = false;
      bool QGJNcHYjQT = false;
      bool FeBiOklEeP = false;
      bool nRXGJPCGXY = false;
      bool jTUihypWOD = false;
      bool KEtkGhgcso = false;
      bool CQhFRziCDN = false;
      bool ERLqjkKSAQ = false;
      bool tPpbEjWlAb = false;
      bool iZNiWSkPRi = false;
      bool PnSBysrCBU = false;
      bool XObbtlaGAh = false;
      bool bwCbeeEbUQ = false;
      bool AuARBGxncL = false;
      bool qUkeDUxkoj = false;
      bool rdOjGSlpVS = false;
      bool oQgkUcNKan = false;
      bool olcnpHLWXK = false;
      bool hSmkXVfQLh = false;
      bool THSKWamzJa = false;
      string pJTVokVWpm;
      string LyJmQUgCsm;
      string dKYAlACSjM;
      string MuhcAyHEZI;
      string HWCUwdVfIO;
      string EIdkDejSin;
      string iCmdaPPflS;
      string NbcjeGIEDH;
      string eVKUIDQwZU;
      string NnUkYEjYsg;
      string NpsoAbetFw;
      string WfObINrRVX;
      string yTGREYHqKa;
      string WjKWsnbUUf;
      string XWpdyhZsbL;
      string MRCUhtibjb;
      string UnieYlUqhT;
      string kWxoAbccSW;
      string yNOzOFgpoz;
      string FzjrKjnLEL;
      if(pJTVokVWpm == NpsoAbetFw){MiLIaoUNUF = true;}
      else if(NpsoAbetFw == pJTVokVWpm){PnSBysrCBU = true;}
      if(LyJmQUgCsm == WfObINrRVX){QGJNcHYjQT = true;}
      else if(WfObINrRVX == LyJmQUgCsm){XObbtlaGAh = true;}
      if(dKYAlACSjM == yTGREYHqKa){FeBiOklEeP = true;}
      else if(yTGREYHqKa == dKYAlACSjM){bwCbeeEbUQ = true;}
      if(MuhcAyHEZI == WjKWsnbUUf){nRXGJPCGXY = true;}
      else if(WjKWsnbUUf == MuhcAyHEZI){AuARBGxncL = true;}
      if(HWCUwdVfIO == XWpdyhZsbL){jTUihypWOD = true;}
      else if(XWpdyhZsbL == HWCUwdVfIO){qUkeDUxkoj = true;}
      if(EIdkDejSin == MRCUhtibjb){KEtkGhgcso = true;}
      else if(MRCUhtibjb == EIdkDejSin){rdOjGSlpVS = true;}
      if(iCmdaPPflS == UnieYlUqhT){CQhFRziCDN = true;}
      else if(UnieYlUqhT == iCmdaPPflS){oQgkUcNKan = true;}
      if(NbcjeGIEDH == kWxoAbccSW){ERLqjkKSAQ = true;}
      if(eVKUIDQwZU == yNOzOFgpoz){tPpbEjWlAb = true;}
      if(NnUkYEjYsg == FzjrKjnLEL){iZNiWSkPRi = true;}
      while(kWxoAbccSW == NbcjeGIEDH){olcnpHLWXK = true;}
      while(yNOzOFgpoz == yNOzOFgpoz){hSmkXVfQLh = true;}
      while(FzjrKjnLEL == FzjrKjnLEL){THSKWamzJa = true;}
      if(MiLIaoUNUF == true){MiLIaoUNUF = false;}
      if(QGJNcHYjQT == true){QGJNcHYjQT = false;}
      if(FeBiOklEeP == true){FeBiOklEeP = false;}
      if(nRXGJPCGXY == true){nRXGJPCGXY = false;}
      if(jTUihypWOD == true){jTUihypWOD = false;}
      if(KEtkGhgcso == true){KEtkGhgcso = false;}
      if(CQhFRziCDN == true){CQhFRziCDN = false;}
      if(ERLqjkKSAQ == true){ERLqjkKSAQ = false;}
      if(tPpbEjWlAb == true){tPpbEjWlAb = false;}
      if(iZNiWSkPRi == true){iZNiWSkPRi = false;}
      if(PnSBysrCBU == true){PnSBysrCBU = false;}
      if(XObbtlaGAh == true){XObbtlaGAh = false;}
      if(bwCbeeEbUQ == true){bwCbeeEbUQ = false;}
      if(AuARBGxncL == true){AuARBGxncL = false;}
      if(qUkeDUxkoj == true){qUkeDUxkoj = false;}
      if(rdOjGSlpVS == true){rdOjGSlpVS = false;}
      if(oQgkUcNKan == true){oQgkUcNKan = false;}
      if(olcnpHLWXK == true){olcnpHLWXK = false;}
      if(hSmkXVfQLh == true){hSmkXVfQLh = false;}
      if(THSKWamzJa == true){THSKWamzJa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGUDQBNQRK
{ 
  void ZmEIVDkoif()
  { 
      bool MtpDhAyMjU = false;
      bool GGxQtqeqNx = false;
      bool FzZwDxUawN = false;
      bool KVMultlPMM = false;
      bool ukOMQhltmb = false;
      bool ePADZMUtzj = false;
      bool eXQWJksBdz = false;
      bool FOdBBTkNeV = false;
      bool LamThuUJVY = false;
      bool ZqPbgXUrCe = false;
      bool njQnWQkzBF = false;
      bool bGPdYEjwnO = false;
      bool PjfEYNzBTc = false;
      bool zrKzgaJzxR = false;
      bool KUHPxSbkDc = false;
      bool mXDnPDDLOI = false;
      bool QifYGiuPwx = false;
      bool tkyWEtcQHF = false;
      bool lNyqoaoWjd = false;
      bool XxjoAaoiIN = false;
      string DexFgaHGYp;
      string yFzLllonBf;
      string fYgInxtzne;
      string pzRJpNRJdl;
      string wyWmtGPDyu;
      string lVLFZeyoQi;
      string gHRsAympUY;
      string TfJPigCsOh;
      string hqArrTnMjL;
      string ObruFnfcmu;
      string SZhZaGLwVr;
      string cEZhApHZBf;
      string JaFJJqmNJt;
      string AZGSPIIaQl;
      string IrprhKCJuP;
      string gGbHlrTYPi;
      string TxlaqDyHSr;
      string gfIOXQkNaz;
      string ocStNtyygW;
      string njKgSKGOAe;
      if(DexFgaHGYp == SZhZaGLwVr){MtpDhAyMjU = true;}
      else if(SZhZaGLwVr == DexFgaHGYp){njQnWQkzBF = true;}
      if(yFzLllonBf == cEZhApHZBf){GGxQtqeqNx = true;}
      else if(cEZhApHZBf == yFzLllonBf){bGPdYEjwnO = true;}
      if(fYgInxtzne == JaFJJqmNJt){FzZwDxUawN = true;}
      else if(JaFJJqmNJt == fYgInxtzne){PjfEYNzBTc = true;}
      if(pzRJpNRJdl == AZGSPIIaQl){KVMultlPMM = true;}
      else if(AZGSPIIaQl == pzRJpNRJdl){zrKzgaJzxR = true;}
      if(wyWmtGPDyu == IrprhKCJuP){ukOMQhltmb = true;}
      else if(IrprhKCJuP == wyWmtGPDyu){KUHPxSbkDc = true;}
      if(lVLFZeyoQi == gGbHlrTYPi){ePADZMUtzj = true;}
      else if(gGbHlrTYPi == lVLFZeyoQi){mXDnPDDLOI = true;}
      if(gHRsAympUY == TxlaqDyHSr){eXQWJksBdz = true;}
      else if(TxlaqDyHSr == gHRsAympUY){QifYGiuPwx = true;}
      if(TfJPigCsOh == gfIOXQkNaz){FOdBBTkNeV = true;}
      if(hqArrTnMjL == ocStNtyygW){LamThuUJVY = true;}
      if(ObruFnfcmu == njKgSKGOAe){ZqPbgXUrCe = true;}
      while(gfIOXQkNaz == TfJPigCsOh){tkyWEtcQHF = true;}
      while(ocStNtyygW == ocStNtyygW){lNyqoaoWjd = true;}
      while(njKgSKGOAe == njKgSKGOAe){XxjoAaoiIN = true;}
      if(MtpDhAyMjU == true){MtpDhAyMjU = false;}
      if(GGxQtqeqNx == true){GGxQtqeqNx = false;}
      if(FzZwDxUawN == true){FzZwDxUawN = false;}
      if(KVMultlPMM == true){KVMultlPMM = false;}
      if(ukOMQhltmb == true){ukOMQhltmb = false;}
      if(ePADZMUtzj == true){ePADZMUtzj = false;}
      if(eXQWJksBdz == true){eXQWJksBdz = false;}
      if(FOdBBTkNeV == true){FOdBBTkNeV = false;}
      if(LamThuUJVY == true){LamThuUJVY = false;}
      if(ZqPbgXUrCe == true){ZqPbgXUrCe = false;}
      if(njQnWQkzBF == true){njQnWQkzBF = false;}
      if(bGPdYEjwnO == true){bGPdYEjwnO = false;}
      if(PjfEYNzBTc == true){PjfEYNzBTc = false;}
      if(zrKzgaJzxR == true){zrKzgaJzxR = false;}
      if(KUHPxSbkDc == true){KUHPxSbkDc = false;}
      if(mXDnPDDLOI == true){mXDnPDDLOI = false;}
      if(QifYGiuPwx == true){QifYGiuPwx = false;}
      if(tkyWEtcQHF == true){tkyWEtcQHF = false;}
      if(lNyqoaoWjd == true){lNyqoaoWjd = false;}
      if(XxjoAaoiIN == true){XxjoAaoiIN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFJMNMFHLA
{ 
  void CsiZnwUCjP()
  { 
      bool JZoQsprXgk = false;
      bool AxQPtnJKiW = false;
      bool pNPLhTggXY = false;
      bool mcHfxnoGLP = false;
      bool ZIZQNhOsSc = false;
      bool PcMfxwKchZ = false;
      bool JLAIyWpjSG = false;
      bool yCzTwhmyyA = false;
      bool FmOtIJQahA = false;
      bool dMYlGOHRSp = false;
      bool qdaLdMdsiP = false;
      bool JLegUVwGzn = false;
      bool GPBRbldNNh = false;
      bool ZUeHIaMCPu = false;
      bool eWqSqRhqQj = false;
      bool RBSeiabIjr = false;
      bool iQfBonfWXs = false;
      bool JspDIiYiZK = false;
      bool ElwcQYCAYg = false;
      bool zDSXMOqpdD = false;
      string rTlLtekYzw;
      string bFachrcPtI;
      string IssxcuqWZb;
      string FehmYLNJgr;
      string RAKYoHxPfq;
      string eROTByaohz;
      string nNyWqwXmDW;
      string dTiBqHhTIV;
      string xapiwnQNkZ;
      string kYagEDCnhr;
      string iJMJNLhMct;
      string QGgMCMWPZD;
      string fJBclFsBwm;
      string FtlPmnOgUk;
      string FDkqJdqOer;
      string gmNeMYHiXI;
      string SfPonWURZO;
      string yptoxbYJSH;
      string NdWEGRfHCN;
      string feJMRYnuCm;
      if(rTlLtekYzw == iJMJNLhMct){JZoQsprXgk = true;}
      else if(iJMJNLhMct == rTlLtekYzw){qdaLdMdsiP = true;}
      if(bFachrcPtI == QGgMCMWPZD){AxQPtnJKiW = true;}
      else if(QGgMCMWPZD == bFachrcPtI){JLegUVwGzn = true;}
      if(IssxcuqWZb == fJBclFsBwm){pNPLhTggXY = true;}
      else if(fJBclFsBwm == IssxcuqWZb){GPBRbldNNh = true;}
      if(FehmYLNJgr == FtlPmnOgUk){mcHfxnoGLP = true;}
      else if(FtlPmnOgUk == FehmYLNJgr){ZUeHIaMCPu = true;}
      if(RAKYoHxPfq == FDkqJdqOer){ZIZQNhOsSc = true;}
      else if(FDkqJdqOer == RAKYoHxPfq){eWqSqRhqQj = true;}
      if(eROTByaohz == gmNeMYHiXI){PcMfxwKchZ = true;}
      else if(gmNeMYHiXI == eROTByaohz){RBSeiabIjr = true;}
      if(nNyWqwXmDW == SfPonWURZO){JLAIyWpjSG = true;}
      else if(SfPonWURZO == nNyWqwXmDW){iQfBonfWXs = true;}
      if(dTiBqHhTIV == yptoxbYJSH){yCzTwhmyyA = true;}
      if(xapiwnQNkZ == NdWEGRfHCN){FmOtIJQahA = true;}
      if(kYagEDCnhr == feJMRYnuCm){dMYlGOHRSp = true;}
      while(yptoxbYJSH == dTiBqHhTIV){JspDIiYiZK = true;}
      while(NdWEGRfHCN == NdWEGRfHCN){ElwcQYCAYg = true;}
      while(feJMRYnuCm == feJMRYnuCm){zDSXMOqpdD = true;}
      if(JZoQsprXgk == true){JZoQsprXgk = false;}
      if(AxQPtnJKiW == true){AxQPtnJKiW = false;}
      if(pNPLhTggXY == true){pNPLhTggXY = false;}
      if(mcHfxnoGLP == true){mcHfxnoGLP = false;}
      if(ZIZQNhOsSc == true){ZIZQNhOsSc = false;}
      if(PcMfxwKchZ == true){PcMfxwKchZ = false;}
      if(JLAIyWpjSG == true){JLAIyWpjSG = false;}
      if(yCzTwhmyyA == true){yCzTwhmyyA = false;}
      if(FmOtIJQahA == true){FmOtIJQahA = false;}
      if(dMYlGOHRSp == true){dMYlGOHRSp = false;}
      if(qdaLdMdsiP == true){qdaLdMdsiP = false;}
      if(JLegUVwGzn == true){JLegUVwGzn = false;}
      if(GPBRbldNNh == true){GPBRbldNNh = false;}
      if(ZUeHIaMCPu == true){ZUeHIaMCPu = false;}
      if(eWqSqRhqQj == true){eWqSqRhqQj = false;}
      if(RBSeiabIjr == true){RBSeiabIjr = false;}
      if(iQfBonfWXs == true){iQfBonfWXs = false;}
      if(JspDIiYiZK == true){JspDIiYiZK = false;}
      if(ElwcQYCAYg == true){ElwcQYCAYg = false;}
      if(zDSXMOqpdD == true){zDSXMOqpdD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJKESPAPRG
{ 
  void YjliTLiSDU()
  { 
      bool SUzYoxNDfm = false;
      bool spfTJzTcnm = false;
      bool WotYHeyqrF = false;
      bool wFXpcxOgCI = false;
      bool klpkHakpTR = false;
      bool JzTSidaZQK = false;
      bool yWLZpmRppL = false;
      bool klaeCkzIQg = false;
      bool sHWauxlFGz = false;
      bool WnQrJOaPuT = false;
      bool IuAHgWYoQy = false;
      bool dRJjQpzjer = false;
      bool BMjqowVhUn = false;
      bool JiNwXyHPtY = false;
      bool YxoIUEefaT = false;
      bool OpkCSwLISj = false;
      bool BpTcnuEMLS = false;
      bool ijpFTEWaWj = false;
      bool QoHBYSyKdb = false;
      bool lzwJXicMTZ = false;
      string AeAgDQyYuk;
      string anKOBKLMRm;
      string DcAbVLkBOa;
      string UFQWKDORAJ;
      string lPWQGsfxmc;
      string uoHIIXeYKq;
      string exJTQVXmDy;
      string utMHBmGjVc;
      string fnOlfexIOl;
      string YpGIdoGCzj;
      string VssogAczGU;
      string RuDhLqhXnk;
      string XOXQZFmDdM;
      string gEjkHltZEe;
      string CyBsUdmYxl;
      string GhNOMGUcPb;
      string NYUtmNKRZY;
      string xITJiZNdwu;
      string SNFrGzpVXB;
      string RRKcQccHGG;
      if(AeAgDQyYuk == VssogAczGU){SUzYoxNDfm = true;}
      else if(VssogAczGU == AeAgDQyYuk){IuAHgWYoQy = true;}
      if(anKOBKLMRm == RuDhLqhXnk){spfTJzTcnm = true;}
      else if(RuDhLqhXnk == anKOBKLMRm){dRJjQpzjer = true;}
      if(DcAbVLkBOa == XOXQZFmDdM){WotYHeyqrF = true;}
      else if(XOXQZFmDdM == DcAbVLkBOa){BMjqowVhUn = true;}
      if(UFQWKDORAJ == gEjkHltZEe){wFXpcxOgCI = true;}
      else if(gEjkHltZEe == UFQWKDORAJ){JiNwXyHPtY = true;}
      if(lPWQGsfxmc == CyBsUdmYxl){klpkHakpTR = true;}
      else if(CyBsUdmYxl == lPWQGsfxmc){YxoIUEefaT = true;}
      if(uoHIIXeYKq == GhNOMGUcPb){JzTSidaZQK = true;}
      else if(GhNOMGUcPb == uoHIIXeYKq){OpkCSwLISj = true;}
      if(exJTQVXmDy == NYUtmNKRZY){yWLZpmRppL = true;}
      else if(NYUtmNKRZY == exJTQVXmDy){BpTcnuEMLS = true;}
      if(utMHBmGjVc == xITJiZNdwu){klaeCkzIQg = true;}
      if(fnOlfexIOl == SNFrGzpVXB){sHWauxlFGz = true;}
      if(YpGIdoGCzj == RRKcQccHGG){WnQrJOaPuT = true;}
      while(xITJiZNdwu == utMHBmGjVc){ijpFTEWaWj = true;}
      while(SNFrGzpVXB == SNFrGzpVXB){QoHBYSyKdb = true;}
      while(RRKcQccHGG == RRKcQccHGG){lzwJXicMTZ = true;}
      if(SUzYoxNDfm == true){SUzYoxNDfm = false;}
      if(spfTJzTcnm == true){spfTJzTcnm = false;}
      if(WotYHeyqrF == true){WotYHeyqrF = false;}
      if(wFXpcxOgCI == true){wFXpcxOgCI = false;}
      if(klpkHakpTR == true){klpkHakpTR = false;}
      if(JzTSidaZQK == true){JzTSidaZQK = false;}
      if(yWLZpmRppL == true){yWLZpmRppL = false;}
      if(klaeCkzIQg == true){klaeCkzIQg = false;}
      if(sHWauxlFGz == true){sHWauxlFGz = false;}
      if(WnQrJOaPuT == true){WnQrJOaPuT = false;}
      if(IuAHgWYoQy == true){IuAHgWYoQy = false;}
      if(dRJjQpzjer == true){dRJjQpzjer = false;}
      if(BMjqowVhUn == true){BMjqowVhUn = false;}
      if(JiNwXyHPtY == true){JiNwXyHPtY = false;}
      if(YxoIUEefaT == true){YxoIUEefaT = false;}
      if(OpkCSwLISj == true){OpkCSwLISj = false;}
      if(BpTcnuEMLS == true){BpTcnuEMLS = false;}
      if(ijpFTEWaWj == true){ijpFTEWaWj = false;}
      if(QoHBYSyKdb == true){QoHBYSyKdb = false;}
      if(lzwJXicMTZ == true){lzwJXicMTZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VUNUFHKUOG
{ 
  void Owunciwewk()
  { 
      bool tKQPFyBtRf = false;
      bool JbmwXVhZuo = false;
      bool CsVhnItdqH = false;
      bool QPVskOWWHk = false;
      bool yTLifwlpop = false;
      bool TtKdrAnibx = false;
      bool DXDKOtGtLJ = false;
      bool yLSJpihmBq = false;
      bool WEnBmWEqAk = false;
      bool antKhZQBTl = false;
      bool oqdfrHbAmI = false;
      bool RBgjZzjCWr = false;
      bool oPsaiKRHbQ = false;
      bool SfSPBeaHIf = false;
      bool tEDrSYGJji = false;
      bool pOeaxZyDxg = false;
      bool pTYWpliRiu = false;
      bool YbsqyjLBHJ = false;
      bool EHWsZEBqSa = false;
      bool gWKboaffBf = false;
      string FBGbPEjMiY;
      string tCAxbNlgBz;
      string PpKsdHtBgC;
      string kEPMGkcdme;
      string JaFwAXCSOD;
      string tdJjWPqMxH;
      string Jhegnolnqq;
      string kItVpnkNsF;
      string FblcHHuepq;
      string tPfeUauXIL;
      string kObXSljmth;
      string dcTqChuCYg;
      string sGxAwUbOAO;
      string sMFhUpAOKV;
      string WHkIMRwnbm;
      string esybReRabx;
      string JUmeoRXlWM;
      string hgqDJkVone;
      string YnlMjzOdPo;
      string YYlNLCUFTu;
      if(FBGbPEjMiY == kObXSljmth){tKQPFyBtRf = true;}
      else if(kObXSljmth == FBGbPEjMiY){oqdfrHbAmI = true;}
      if(tCAxbNlgBz == dcTqChuCYg){JbmwXVhZuo = true;}
      else if(dcTqChuCYg == tCAxbNlgBz){RBgjZzjCWr = true;}
      if(PpKsdHtBgC == sGxAwUbOAO){CsVhnItdqH = true;}
      else if(sGxAwUbOAO == PpKsdHtBgC){oPsaiKRHbQ = true;}
      if(kEPMGkcdme == sMFhUpAOKV){QPVskOWWHk = true;}
      else if(sMFhUpAOKV == kEPMGkcdme){SfSPBeaHIf = true;}
      if(JaFwAXCSOD == WHkIMRwnbm){yTLifwlpop = true;}
      else if(WHkIMRwnbm == JaFwAXCSOD){tEDrSYGJji = true;}
      if(tdJjWPqMxH == esybReRabx){TtKdrAnibx = true;}
      else if(esybReRabx == tdJjWPqMxH){pOeaxZyDxg = true;}
      if(Jhegnolnqq == JUmeoRXlWM){DXDKOtGtLJ = true;}
      else if(JUmeoRXlWM == Jhegnolnqq){pTYWpliRiu = true;}
      if(kItVpnkNsF == hgqDJkVone){yLSJpihmBq = true;}
      if(FblcHHuepq == YnlMjzOdPo){WEnBmWEqAk = true;}
      if(tPfeUauXIL == YYlNLCUFTu){antKhZQBTl = true;}
      while(hgqDJkVone == kItVpnkNsF){YbsqyjLBHJ = true;}
      while(YnlMjzOdPo == YnlMjzOdPo){EHWsZEBqSa = true;}
      while(YYlNLCUFTu == YYlNLCUFTu){gWKboaffBf = true;}
      if(tKQPFyBtRf == true){tKQPFyBtRf = false;}
      if(JbmwXVhZuo == true){JbmwXVhZuo = false;}
      if(CsVhnItdqH == true){CsVhnItdqH = false;}
      if(QPVskOWWHk == true){QPVskOWWHk = false;}
      if(yTLifwlpop == true){yTLifwlpop = false;}
      if(TtKdrAnibx == true){TtKdrAnibx = false;}
      if(DXDKOtGtLJ == true){DXDKOtGtLJ = false;}
      if(yLSJpihmBq == true){yLSJpihmBq = false;}
      if(WEnBmWEqAk == true){WEnBmWEqAk = false;}
      if(antKhZQBTl == true){antKhZQBTl = false;}
      if(oqdfrHbAmI == true){oqdfrHbAmI = false;}
      if(RBgjZzjCWr == true){RBgjZzjCWr = false;}
      if(oPsaiKRHbQ == true){oPsaiKRHbQ = false;}
      if(SfSPBeaHIf == true){SfSPBeaHIf = false;}
      if(tEDrSYGJji == true){tEDrSYGJji = false;}
      if(pOeaxZyDxg == true){pOeaxZyDxg = false;}
      if(pTYWpliRiu == true){pTYWpliRiu = false;}
      if(YbsqyjLBHJ == true){YbsqyjLBHJ = false;}
      if(EHWsZEBqSa == true){EHWsZEBqSa = false;}
      if(gWKboaffBf == true){gWKboaffBf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IMSORPCPNI
{ 
  void PZgXynladh()
  { 
      bool PepWkzsmWT = false;
      bool SrYRLYGAOK = false;
      bool iBsLjBMqkV = false;
      bool OqNVnXKfic = false;
      bool kwKIcdpLdo = false;
      bool QHxkONldmi = false;
      bool mBBBEbdDcm = false;
      bool NaQkYlqkiF = false;
      bool LANwEHscGZ = false;
      bool lfsApjtJDA = false;
      bool AmipappMLb = false;
      bool WBugXlnFwx = false;
      bool hAwCBggQto = false;
      bool qggiFXRWUO = false;
      bool QgQeDkkLcE = false;
      bool uoMGSzqfot = false;
      bool IZRWjoTMbz = false;
      bool TRjhfAjRyQ = false;
      bool uUmpsBUaPF = false;
      bool gkhaFqOstN = false;
      string WKgcfFzrVF;
      string ixHlwqZrfp;
      string ggjcDiykkQ;
      string FMYkwJuADg;
      string rRgsPDQQMO;
      string BfpIIpZDZw;
      string GNHEAWXVpm;
      string wZnyxPzqNz;
      string RhYVPYVPcG;
      string irZHaeKbrr;
      string ftaZSaqrLs;
      string pipadYokoa;
      string BIsiEEAgWS;
      string EWyUSXGyDo;
      string hcEjQzBycC;
      string oZmQqWBqVO;
      string aKUrnSjVHG;
      string RpgAsXDJSE;
      string CBDUcdjhcw;
      string VPcoOXIMux;
      if(WKgcfFzrVF == ftaZSaqrLs){PepWkzsmWT = true;}
      else if(ftaZSaqrLs == WKgcfFzrVF){AmipappMLb = true;}
      if(ixHlwqZrfp == pipadYokoa){SrYRLYGAOK = true;}
      else if(pipadYokoa == ixHlwqZrfp){WBugXlnFwx = true;}
      if(ggjcDiykkQ == BIsiEEAgWS){iBsLjBMqkV = true;}
      else if(BIsiEEAgWS == ggjcDiykkQ){hAwCBggQto = true;}
      if(FMYkwJuADg == EWyUSXGyDo){OqNVnXKfic = true;}
      else if(EWyUSXGyDo == FMYkwJuADg){qggiFXRWUO = true;}
      if(rRgsPDQQMO == hcEjQzBycC){kwKIcdpLdo = true;}
      else if(hcEjQzBycC == rRgsPDQQMO){QgQeDkkLcE = true;}
      if(BfpIIpZDZw == oZmQqWBqVO){QHxkONldmi = true;}
      else if(oZmQqWBqVO == BfpIIpZDZw){uoMGSzqfot = true;}
      if(GNHEAWXVpm == aKUrnSjVHG){mBBBEbdDcm = true;}
      else if(aKUrnSjVHG == GNHEAWXVpm){IZRWjoTMbz = true;}
      if(wZnyxPzqNz == RpgAsXDJSE){NaQkYlqkiF = true;}
      if(RhYVPYVPcG == CBDUcdjhcw){LANwEHscGZ = true;}
      if(irZHaeKbrr == VPcoOXIMux){lfsApjtJDA = true;}
      while(RpgAsXDJSE == wZnyxPzqNz){TRjhfAjRyQ = true;}
      while(CBDUcdjhcw == CBDUcdjhcw){uUmpsBUaPF = true;}
      while(VPcoOXIMux == VPcoOXIMux){gkhaFqOstN = true;}
      if(PepWkzsmWT == true){PepWkzsmWT = false;}
      if(SrYRLYGAOK == true){SrYRLYGAOK = false;}
      if(iBsLjBMqkV == true){iBsLjBMqkV = false;}
      if(OqNVnXKfic == true){OqNVnXKfic = false;}
      if(kwKIcdpLdo == true){kwKIcdpLdo = false;}
      if(QHxkONldmi == true){QHxkONldmi = false;}
      if(mBBBEbdDcm == true){mBBBEbdDcm = false;}
      if(NaQkYlqkiF == true){NaQkYlqkiF = false;}
      if(LANwEHscGZ == true){LANwEHscGZ = false;}
      if(lfsApjtJDA == true){lfsApjtJDA = false;}
      if(AmipappMLb == true){AmipappMLb = false;}
      if(WBugXlnFwx == true){WBugXlnFwx = false;}
      if(hAwCBggQto == true){hAwCBggQto = false;}
      if(qggiFXRWUO == true){qggiFXRWUO = false;}
      if(QgQeDkkLcE == true){QgQeDkkLcE = false;}
      if(uoMGSzqfot == true){uoMGSzqfot = false;}
      if(IZRWjoTMbz == true){IZRWjoTMbz = false;}
      if(TRjhfAjRyQ == true){TRjhfAjRyQ = false;}
      if(uUmpsBUaPF == true){uUmpsBUaPF = false;}
      if(gkhaFqOstN == true){gkhaFqOstN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWQLSDMYZG
{ 
  void CutEACjyCb()
  { 
      bool CzSyUgwZzT = false;
      bool xToWQHLPQt = false;
      bool TnmTZbSDxM = false;
      bool hOfHkKLTMB = false;
      bool FBaedHtqjI = false;
      bool ysTFxOMyYr = false;
      bool NrcmkhnhlG = false;
      bool uqCPnSMHpS = false;
      bool haToNouZKW = false;
      bool xNuUmMYnsu = false;
      bool TLFcMGpDQe = false;
      bool BEHGJlYmYw = false;
      bool mNXPIhwhca = false;
      bool sYOtyWVpbH = false;
      bool yrJeUsFoKA = false;
      bool nkOwIGnpTd = false;
      bool JHaokcpNHm = false;
      bool QhLQxtDruP = false;
      bool cHXbmIJRlr = false;
      bool hfVyyqRTtq = false;
      string atBWVIlUcW;
      string xGtsETfyCh;
      string rFEnzsBprj;
      string bhranUsFDy;
      string QJsaWusDAw;
      string EqPMgUpMXb;
      string HwcstOOTEj;
      string aatEQiMcQE;
      string AxowekResT;
      string dfhbpUgzfH;
      string fZzQUdwLuy;
      string HMuTbJGfNJ;
      string xiakFtrSNw;
      string CMxJXZyYaB;
      string nGjuLRkOAf;
      string NAlVKwzOKa;
      string kdxzutPluB;
      string LgEMVqzeYm;
      string JdShhBaaya;
      string aiOAPJIjzQ;
      if(atBWVIlUcW == fZzQUdwLuy){CzSyUgwZzT = true;}
      else if(fZzQUdwLuy == atBWVIlUcW){TLFcMGpDQe = true;}
      if(xGtsETfyCh == HMuTbJGfNJ){xToWQHLPQt = true;}
      else if(HMuTbJGfNJ == xGtsETfyCh){BEHGJlYmYw = true;}
      if(rFEnzsBprj == xiakFtrSNw){TnmTZbSDxM = true;}
      else if(xiakFtrSNw == rFEnzsBprj){mNXPIhwhca = true;}
      if(bhranUsFDy == CMxJXZyYaB){hOfHkKLTMB = true;}
      else if(CMxJXZyYaB == bhranUsFDy){sYOtyWVpbH = true;}
      if(QJsaWusDAw == nGjuLRkOAf){FBaedHtqjI = true;}
      else if(nGjuLRkOAf == QJsaWusDAw){yrJeUsFoKA = true;}
      if(EqPMgUpMXb == NAlVKwzOKa){ysTFxOMyYr = true;}
      else if(NAlVKwzOKa == EqPMgUpMXb){nkOwIGnpTd = true;}
      if(HwcstOOTEj == kdxzutPluB){NrcmkhnhlG = true;}
      else if(kdxzutPluB == HwcstOOTEj){JHaokcpNHm = true;}
      if(aatEQiMcQE == LgEMVqzeYm){uqCPnSMHpS = true;}
      if(AxowekResT == JdShhBaaya){haToNouZKW = true;}
      if(dfhbpUgzfH == aiOAPJIjzQ){xNuUmMYnsu = true;}
      while(LgEMVqzeYm == aatEQiMcQE){QhLQxtDruP = true;}
      while(JdShhBaaya == JdShhBaaya){cHXbmIJRlr = true;}
      while(aiOAPJIjzQ == aiOAPJIjzQ){hfVyyqRTtq = true;}
      if(CzSyUgwZzT == true){CzSyUgwZzT = false;}
      if(xToWQHLPQt == true){xToWQHLPQt = false;}
      if(TnmTZbSDxM == true){TnmTZbSDxM = false;}
      if(hOfHkKLTMB == true){hOfHkKLTMB = false;}
      if(FBaedHtqjI == true){FBaedHtqjI = false;}
      if(ysTFxOMyYr == true){ysTFxOMyYr = false;}
      if(NrcmkhnhlG == true){NrcmkhnhlG = false;}
      if(uqCPnSMHpS == true){uqCPnSMHpS = false;}
      if(haToNouZKW == true){haToNouZKW = false;}
      if(xNuUmMYnsu == true){xNuUmMYnsu = false;}
      if(TLFcMGpDQe == true){TLFcMGpDQe = false;}
      if(BEHGJlYmYw == true){BEHGJlYmYw = false;}
      if(mNXPIhwhca == true){mNXPIhwhca = false;}
      if(sYOtyWVpbH == true){sYOtyWVpbH = false;}
      if(yrJeUsFoKA == true){yrJeUsFoKA = false;}
      if(nkOwIGnpTd == true){nkOwIGnpTd = false;}
      if(JHaokcpNHm == true){JHaokcpNHm = false;}
      if(QhLQxtDruP == true){QhLQxtDruP = false;}
      if(cHXbmIJRlr == true){cHXbmIJRlr = false;}
      if(hfVyyqRTtq == true){hfVyyqRTtq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MTUOHSHSQS
{ 
  void iLYwpanhzV()
  { 
      bool aeJbQVJLsE = false;
      bool yiqcSmNxni = false;
      bool aBwanDswSj = false;
      bool qpdMZyJDLK = false;
      bool JuIgariMYi = false;
      bool DsRbMYhinM = false;
      bool bMrIMHEdCT = false;
      bool dKkdZerPzw = false;
      bool UgXigyYCzA = false;
      bool QaPyhwCATT = false;
      bool mEJEFsHnBg = false;
      bool fSjrruoIaO = false;
      bool iCeCCCtlwd = false;
      bool crufIPXTdn = false;
      bool pkBRTxpXGm = false;
      bool GsYFjkYHBC = false;
      bool yUqWEnXDic = false;
      bool XVemXyBNhF = false;
      bool LWfIWiSouX = false;
      bool pQRboVsdMf = false;
      string pHTadGKhoQ;
      string lfdMmsBbcR;
      string UZDGPnelcI;
      string ZYZscggqxQ;
      string cdzzyZMyNA;
      string twJsKPDNLp;
      string aYEgqNFkjG;
      string LJeMnpZEHo;
      string afYcNcOghM;
      string cTfGoEZSIj;
      string TbOGokRxFT;
      string pzFVOuAbSN;
      string yYDWdrdXWj;
      string QHwWUzRRnc;
      string LQaNWcNKrt;
      string ExAtkuXqcw;
      string GtaUChChAP;
      string chnoBgxoAA;
      string dTfcfSGBkZ;
      string aZoqVRpGKn;
      if(pHTadGKhoQ == TbOGokRxFT){aeJbQVJLsE = true;}
      else if(TbOGokRxFT == pHTadGKhoQ){mEJEFsHnBg = true;}
      if(lfdMmsBbcR == pzFVOuAbSN){yiqcSmNxni = true;}
      else if(pzFVOuAbSN == lfdMmsBbcR){fSjrruoIaO = true;}
      if(UZDGPnelcI == yYDWdrdXWj){aBwanDswSj = true;}
      else if(yYDWdrdXWj == UZDGPnelcI){iCeCCCtlwd = true;}
      if(ZYZscggqxQ == QHwWUzRRnc){qpdMZyJDLK = true;}
      else if(QHwWUzRRnc == ZYZscggqxQ){crufIPXTdn = true;}
      if(cdzzyZMyNA == LQaNWcNKrt){JuIgariMYi = true;}
      else if(LQaNWcNKrt == cdzzyZMyNA){pkBRTxpXGm = true;}
      if(twJsKPDNLp == ExAtkuXqcw){DsRbMYhinM = true;}
      else if(ExAtkuXqcw == twJsKPDNLp){GsYFjkYHBC = true;}
      if(aYEgqNFkjG == GtaUChChAP){bMrIMHEdCT = true;}
      else if(GtaUChChAP == aYEgqNFkjG){yUqWEnXDic = true;}
      if(LJeMnpZEHo == chnoBgxoAA){dKkdZerPzw = true;}
      if(afYcNcOghM == dTfcfSGBkZ){UgXigyYCzA = true;}
      if(cTfGoEZSIj == aZoqVRpGKn){QaPyhwCATT = true;}
      while(chnoBgxoAA == LJeMnpZEHo){XVemXyBNhF = true;}
      while(dTfcfSGBkZ == dTfcfSGBkZ){LWfIWiSouX = true;}
      while(aZoqVRpGKn == aZoqVRpGKn){pQRboVsdMf = true;}
      if(aeJbQVJLsE == true){aeJbQVJLsE = false;}
      if(yiqcSmNxni == true){yiqcSmNxni = false;}
      if(aBwanDswSj == true){aBwanDswSj = false;}
      if(qpdMZyJDLK == true){qpdMZyJDLK = false;}
      if(JuIgariMYi == true){JuIgariMYi = false;}
      if(DsRbMYhinM == true){DsRbMYhinM = false;}
      if(bMrIMHEdCT == true){bMrIMHEdCT = false;}
      if(dKkdZerPzw == true){dKkdZerPzw = false;}
      if(UgXigyYCzA == true){UgXigyYCzA = false;}
      if(QaPyhwCATT == true){QaPyhwCATT = false;}
      if(mEJEFsHnBg == true){mEJEFsHnBg = false;}
      if(fSjrruoIaO == true){fSjrruoIaO = false;}
      if(iCeCCCtlwd == true){iCeCCCtlwd = false;}
      if(crufIPXTdn == true){crufIPXTdn = false;}
      if(pkBRTxpXGm == true){pkBRTxpXGm = false;}
      if(GsYFjkYHBC == true){GsYFjkYHBC = false;}
      if(yUqWEnXDic == true){yUqWEnXDic = false;}
      if(XVemXyBNhF == true){XVemXyBNhF = false;}
      if(LWfIWiSouX == true){LWfIWiSouX = false;}
      if(pQRboVsdMf == true){pQRboVsdMf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQHHEYZTTX
{ 
  void DrOAxEnZVs()
  { 
      bool HWHTxhFGZd = false;
      bool PWJOQPlGqx = false;
      bool UItrQNaBYO = false;
      bool EyzAMfaKMr = false;
      bool SnCrYbxXYa = false;
      bool aJSwDybODj = false;
      bool HEhKZRWICk = false;
      bool oatyefFCSo = false;
      bool PCbxnteDxN = false;
      bool DLHbkOGrSH = false;
      bool EoVnlzPTQW = false;
      bool rZuNTEbjWe = false;
      bool lTLnhcTRNQ = false;
      bool ZNjLjagnLn = false;
      bool eLlZVcQsIg = false;
      bool lVVmUkcgFJ = false;
      bool exGAxdpjds = false;
      bool WnXhAahkSF = false;
      bool LaJfdDrwpz = false;
      bool xzhCJhEkcq = false;
      string QyOmjHfPJY;
      string HwchZBJAcc;
      string mnAEXVNgtr;
      string MczPzFjAZW;
      string cTsRgDkdPa;
      string fFAlJcxJON;
      string szURLexNiU;
      string QIZGzStiXT;
      string kjQTMHbNFW;
      string HZkMcdybFB;
      string GWtuJWetmp;
      string hOlucJiBFE;
      string CiHMMpXNcU;
      string URcVMNoUJo;
      string chaOnsnoiS;
      string uwWAzXPhhT;
      string yQQRVPkQhO;
      string UNqPaUHsYT;
      string CheKZXucWo;
      string yHmpqMQJsX;
      if(QyOmjHfPJY == GWtuJWetmp){HWHTxhFGZd = true;}
      else if(GWtuJWetmp == QyOmjHfPJY){EoVnlzPTQW = true;}
      if(HwchZBJAcc == hOlucJiBFE){PWJOQPlGqx = true;}
      else if(hOlucJiBFE == HwchZBJAcc){rZuNTEbjWe = true;}
      if(mnAEXVNgtr == CiHMMpXNcU){UItrQNaBYO = true;}
      else if(CiHMMpXNcU == mnAEXVNgtr){lTLnhcTRNQ = true;}
      if(MczPzFjAZW == URcVMNoUJo){EyzAMfaKMr = true;}
      else if(URcVMNoUJo == MczPzFjAZW){ZNjLjagnLn = true;}
      if(cTsRgDkdPa == chaOnsnoiS){SnCrYbxXYa = true;}
      else if(chaOnsnoiS == cTsRgDkdPa){eLlZVcQsIg = true;}
      if(fFAlJcxJON == uwWAzXPhhT){aJSwDybODj = true;}
      else if(uwWAzXPhhT == fFAlJcxJON){lVVmUkcgFJ = true;}
      if(szURLexNiU == yQQRVPkQhO){HEhKZRWICk = true;}
      else if(yQQRVPkQhO == szURLexNiU){exGAxdpjds = true;}
      if(QIZGzStiXT == UNqPaUHsYT){oatyefFCSo = true;}
      if(kjQTMHbNFW == CheKZXucWo){PCbxnteDxN = true;}
      if(HZkMcdybFB == yHmpqMQJsX){DLHbkOGrSH = true;}
      while(UNqPaUHsYT == QIZGzStiXT){WnXhAahkSF = true;}
      while(CheKZXucWo == CheKZXucWo){LaJfdDrwpz = true;}
      while(yHmpqMQJsX == yHmpqMQJsX){xzhCJhEkcq = true;}
      if(HWHTxhFGZd == true){HWHTxhFGZd = false;}
      if(PWJOQPlGqx == true){PWJOQPlGqx = false;}
      if(UItrQNaBYO == true){UItrQNaBYO = false;}
      if(EyzAMfaKMr == true){EyzAMfaKMr = false;}
      if(SnCrYbxXYa == true){SnCrYbxXYa = false;}
      if(aJSwDybODj == true){aJSwDybODj = false;}
      if(HEhKZRWICk == true){HEhKZRWICk = false;}
      if(oatyefFCSo == true){oatyefFCSo = false;}
      if(PCbxnteDxN == true){PCbxnteDxN = false;}
      if(DLHbkOGrSH == true){DLHbkOGrSH = false;}
      if(EoVnlzPTQW == true){EoVnlzPTQW = false;}
      if(rZuNTEbjWe == true){rZuNTEbjWe = false;}
      if(lTLnhcTRNQ == true){lTLnhcTRNQ = false;}
      if(ZNjLjagnLn == true){ZNjLjagnLn = false;}
      if(eLlZVcQsIg == true){eLlZVcQsIg = false;}
      if(lVVmUkcgFJ == true){lVVmUkcgFJ = false;}
      if(exGAxdpjds == true){exGAxdpjds = false;}
      if(WnXhAahkSF == true){WnXhAahkSF = false;}
      if(LaJfdDrwpz == true){LaJfdDrwpz = false;}
      if(xzhCJhEkcq == true){xzhCJhEkcq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBRSLERBOX
{ 
  void SOVTknjSrE()
  { 
      bool eEWWXMInIn = false;
      bool RhWHOepRQc = false;
      bool tHVpiYKrMZ = false;
      bool nsbjwcNhAH = false;
      bool zAKuPWtFDx = false;
      bool JzXydWhfny = false;
      bool CPbiAYGmKk = false;
      bool RIQIctwZZL = false;
      bool eFoOPnVcFY = false;
      bool tgsBFjYbuq = false;
      bool QHtReBhOUj = false;
      bool ZIFcTwZMTL = false;
      bool CcgkqjOPCs = false;
      bool VUeitXKXiO = false;
      bool FHHVzkaQgJ = false;
      bool JLIionZIZu = false;
      bool lSLbNFdWhw = false;
      bool kBcEFuUKlF = false;
      bool JyhsiJMusG = false;
      bool xCynbmufHs = false;
      string qOzXDrUnrw;
      string zomNgqmPYn;
      string bLgiYgLqSV;
      string VDPzoQICKi;
      string fLhcAhoTfT;
      string gPSybfgQyV;
      string fcVWZuYnYQ;
      string hjEpHQdEhq;
      string rrKyoFjQXJ;
      string irDoCCpLCF;
      string IBuPkwKcqL;
      string BchHdnSWhT;
      string LIPPgpfPmF;
      string ZSBcipxuMr;
      string uGZMHFJwKO;
      string jSdhsAkehu;
      string PuplkiaFYm;
      string pWKoYEhDIa;
      string gjEYUHnTjh;
      string ERMRczQnbX;
      if(qOzXDrUnrw == IBuPkwKcqL){eEWWXMInIn = true;}
      else if(IBuPkwKcqL == qOzXDrUnrw){QHtReBhOUj = true;}
      if(zomNgqmPYn == BchHdnSWhT){RhWHOepRQc = true;}
      else if(BchHdnSWhT == zomNgqmPYn){ZIFcTwZMTL = true;}
      if(bLgiYgLqSV == LIPPgpfPmF){tHVpiYKrMZ = true;}
      else if(LIPPgpfPmF == bLgiYgLqSV){CcgkqjOPCs = true;}
      if(VDPzoQICKi == ZSBcipxuMr){nsbjwcNhAH = true;}
      else if(ZSBcipxuMr == VDPzoQICKi){VUeitXKXiO = true;}
      if(fLhcAhoTfT == uGZMHFJwKO){zAKuPWtFDx = true;}
      else if(uGZMHFJwKO == fLhcAhoTfT){FHHVzkaQgJ = true;}
      if(gPSybfgQyV == jSdhsAkehu){JzXydWhfny = true;}
      else if(jSdhsAkehu == gPSybfgQyV){JLIionZIZu = true;}
      if(fcVWZuYnYQ == PuplkiaFYm){CPbiAYGmKk = true;}
      else if(PuplkiaFYm == fcVWZuYnYQ){lSLbNFdWhw = true;}
      if(hjEpHQdEhq == pWKoYEhDIa){RIQIctwZZL = true;}
      if(rrKyoFjQXJ == gjEYUHnTjh){eFoOPnVcFY = true;}
      if(irDoCCpLCF == ERMRczQnbX){tgsBFjYbuq = true;}
      while(pWKoYEhDIa == hjEpHQdEhq){kBcEFuUKlF = true;}
      while(gjEYUHnTjh == gjEYUHnTjh){JyhsiJMusG = true;}
      while(ERMRczQnbX == ERMRczQnbX){xCynbmufHs = true;}
      if(eEWWXMInIn == true){eEWWXMInIn = false;}
      if(RhWHOepRQc == true){RhWHOepRQc = false;}
      if(tHVpiYKrMZ == true){tHVpiYKrMZ = false;}
      if(nsbjwcNhAH == true){nsbjwcNhAH = false;}
      if(zAKuPWtFDx == true){zAKuPWtFDx = false;}
      if(JzXydWhfny == true){JzXydWhfny = false;}
      if(CPbiAYGmKk == true){CPbiAYGmKk = false;}
      if(RIQIctwZZL == true){RIQIctwZZL = false;}
      if(eFoOPnVcFY == true){eFoOPnVcFY = false;}
      if(tgsBFjYbuq == true){tgsBFjYbuq = false;}
      if(QHtReBhOUj == true){QHtReBhOUj = false;}
      if(ZIFcTwZMTL == true){ZIFcTwZMTL = false;}
      if(CcgkqjOPCs == true){CcgkqjOPCs = false;}
      if(VUeitXKXiO == true){VUeitXKXiO = false;}
      if(FHHVzkaQgJ == true){FHHVzkaQgJ = false;}
      if(JLIionZIZu == true){JLIionZIZu = false;}
      if(lSLbNFdWhw == true){lSLbNFdWhw = false;}
      if(kBcEFuUKlF == true){kBcEFuUKlF = false;}
      if(JyhsiJMusG == true){JyhsiJMusG = false;}
      if(xCynbmufHs == true){xCynbmufHs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPFXJYIMBZ
{ 
  void bXNamumBen()
  { 
      bool SmfegnxXzx = false;
      bool IDcjGUwcQQ = false;
      bool owZMEhutlg = false;
      bool efRiQwbwVM = false;
      bool YGIVOCRSPJ = false;
      bool GbUPlVMSaz = false;
      bool sCkSSblsTK = false;
      bool rAGDqinDxC = false;
      bool PcdcZCLCwt = false;
      bool iJVVTVUoDm = false;
      bool QXyFQGVRXD = false;
      bool hIUXjPYIrQ = false;
      bool QiwYbidjjU = false;
      bool NyAKkqdYLT = false;
      bool fsdsMZnxlD = false;
      bool xMwmVgbZch = false;
      bool bkgCoiIJlr = false;
      bool kzwXjWFDMB = false;
      bool tgxfXBBNoE = false;
      bool PEudruMaDc = false;
      string DpBEoPXOUH;
      string CrsDeUHXua;
      string NfHDXyXDSl;
      string fEMmICahzM;
      string dlxVAbYqEA;
      string bOaDxXhyfq;
      string rUuibyeGtb;
      string sZYhxailDw;
      string ZfzSJQdJok;
      string UcBHUIpOtB;
      string wRxbGCorGW;
      string nwujRLVcYK;
      string UVQIHQYRMn;
      string jTqBzHiWMH;
      string akDSwXgQpJ;
      string mNoigaBnTp;
      string cXfRmUEtkK;
      string byQQjiRxLj;
      string iHbDBVeITX;
      string FtCWdCEkfb;
      if(DpBEoPXOUH == wRxbGCorGW){SmfegnxXzx = true;}
      else if(wRxbGCorGW == DpBEoPXOUH){QXyFQGVRXD = true;}
      if(CrsDeUHXua == nwujRLVcYK){IDcjGUwcQQ = true;}
      else if(nwujRLVcYK == CrsDeUHXua){hIUXjPYIrQ = true;}
      if(NfHDXyXDSl == UVQIHQYRMn){owZMEhutlg = true;}
      else if(UVQIHQYRMn == NfHDXyXDSl){QiwYbidjjU = true;}
      if(fEMmICahzM == jTqBzHiWMH){efRiQwbwVM = true;}
      else if(jTqBzHiWMH == fEMmICahzM){NyAKkqdYLT = true;}
      if(dlxVAbYqEA == akDSwXgQpJ){YGIVOCRSPJ = true;}
      else if(akDSwXgQpJ == dlxVAbYqEA){fsdsMZnxlD = true;}
      if(bOaDxXhyfq == mNoigaBnTp){GbUPlVMSaz = true;}
      else if(mNoigaBnTp == bOaDxXhyfq){xMwmVgbZch = true;}
      if(rUuibyeGtb == cXfRmUEtkK){sCkSSblsTK = true;}
      else if(cXfRmUEtkK == rUuibyeGtb){bkgCoiIJlr = true;}
      if(sZYhxailDw == byQQjiRxLj){rAGDqinDxC = true;}
      if(ZfzSJQdJok == iHbDBVeITX){PcdcZCLCwt = true;}
      if(UcBHUIpOtB == FtCWdCEkfb){iJVVTVUoDm = true;}
      while(byQQjiRxLj == sZYhxailDw){kzwXjWFDMB = true;}
      while(iHbDBVeITX == iHbDBVeITX){tgxfXBBNoE = true;}
      while(FtCWdCEkfb == FtCWdCEkfb){PEudruMaDc = true;}
      if(SmfegnxXzx == true){SmfegnxXzx = false;}
      if(IDcjGUwcQQ == true){IDcjGUwcQQ = false;}
      if(owZMEhutlg == true){owZMEhutlg = false;}
      if(efRiQwbwVM == true){efRiQwbwVM = false;}
      if(YGIVOCRSPJ == true){YGIVOCRSPJ = false;}
      if(GbUPlVMSaz == true){GbUPlVMSaz = false;}
      if(sCkSSblsTK == true){sCkSSblsTK = false;}
      if(rAGDqinDxC == true){rAGDqinDxC = false;}
      if(PcdcZCLCwt == true){PcdcZCLCwt = false;}
      if(iJVVTVUoDm == true){iJVVTVUoDm = false;}
      if(QXyFQGVRXD == true){QXyFQGVRXD = false;}
      if(hIUXjPYIrQ == true){hIUXjPYIrQ = false;}
      if(QiwYbidjjU == true){QiwYbidjjU = false;}
      if(NyAKkqdYLT == true){NyAKkqdYLT = false;}
      if(fsdsMZnxlD == true){fsdsMZnxlD = false;}
      if(xMwmVgbZch == true){xMwmVgbZch = false;}
      if(bkgCoiIJlr == true){bkgCoiIJlr = false;}
      if(kzwXjWFDMB == true){kzwXjWFDMB = false;}
      if(tgxfXBBNoE == true){tgxfXBBNoE = false;}
      if(PEudruMaDc == true){PEudruMaDc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIGXEYXGUV
{ 
  void LZfLzluaXd()
  { 
      bool pxzDmiHswH = false;
      bool cTPmFxCMbC = false;
      bool bgynqpISJq = false;
      bool pFkcGTWbAh = false;
      bool cHHcDjTOnQ = false;
      bool UrOnJIzKLw = false;
      bool ZniFRWhlgk = false;
      bool aZLtYUZUkH = false;
      bool WtesWxqxTx = false;
      bool UMPDInXCLg = false;
      bool BghDptgUOo = false;
      bool heYEYfJphT = false;
      bool fkSiQOJHkk = false;
      bool wXIDFoMbDb = false;
      bool QVhdPomLdc = false;
      bool ehTrBPOzla = false;
      bool kYidsKVVzj = false;
      bool TgmGDJDnSa = false;
      bool bycIGODQCp = false;
      bool aMobqqmDkE = false;
      string xJLmkrocjr;
      string HSuqbVZVOb;
      string RKMxwkdBMm;
      string FDtRyaSmuO;
      string cOURGgfDIZ;
      string wmzEulxOqA;
      string NnQxlDXcrB;
      string DlZAzDpuqO;
      string EZrmqSDpVM;
      string cEwuAoyWeC;
      string IDLHVJMzEr;
      string wBWbwnucFT;
      string zhGfXzpezK;
      string FSPnGAOkQh;
      string FEkdPbgTyM;
      string sURLCZweiW;
      string ShzsmdliUu;
      string ZKMXOuxcPw;
      string RVfmRkBEkf;
      string EiBsOWEqql;
      if(xJLmkrocjr == IDLHVJMzEr){pxzDmiHswH = true;}
      else if(IDLHVJMzEr == xJLmkrocjr){BghDptgUOo = true;}
      if(HSuqbVZVOb == wBWbwnucFT){cTPmFxCMbC = true;}
      else if(wBWbwnucFT == HSuqbVZVOb){heYEYfJphT = true;}
      if(RKMxwkdBMm == zhGfXzpezK){bgynqpISJq = true;}
      else if(zhGfXzpezK == RKMxwkdBMm){fkSiQOJHkk = true;}
      if(FDtRyaSmuO == FSPnGAOkQh){pFkcGTWbAh = true;}
      else if(FSPnGAOkQh == FDtRyaSmuO){wXIDFoMbDb = true;}
      if(cOURGgfDIZ == FEkdPbgTyM){cHHcDjTOnQ = true;}
      else if(FEkdPbgTyM == cOURGgfDIZ){QVhdPomLdc = true;}
      if(wmzEulxOqA == sURLCZweiW){UrOnJIzKLw = true;}
      else if(sURLCZweiW == wmzEulxOqA){ehTrBPOzla = true;}
      if(NnQxlDXcrB == ShzsmdliUu){ZniFRWhlgk = true;}
      else if(ShzsmdliUu == NnQxlDXcrB){kYidsKVVzj = true;}
      if(DlZAzDpuqO == ZKMXOuxcPw){aZLtYUZUkH = true;}
      if(EZrmqSDpVM == RVfmRkBEkf){WtesWxqxTx = true;}
      if(cEwuAoyWeC == EiBsOWEqql){UMPDInXCLg = true;}
      while(ZKMXOuxcPw == DlZAzDpuqO){TgmGDJDnSa = true;}
      while(RVfmRkBEkf == RVfmRkBEkf){bycIGODQCp = true;}
      while(EiBsOWEqql == EiBsOWEqql){aMobqqmDkE = true;}
      if(pxzDmiHswH == true){pxzDmiHswH = false;}
      if(cTPmFxCMbC == true){cTPmFxCMbC = false;}
      if(bgynqpISJq == true){bgynqpISJq = false;}
      if(pFkcGTWbAh == true){pFkcGTWbAh = false;}
      if(cHHcDjTOnQ == true){cHHcDjTOnQ = false;}
      if(UrOnJIzKLw == true){UrOnJIzKLw = false;}
      if(ZniFRWhlgk == true){ZniFRWhlgk = false;}
      if(aZLtYUZUkH == true){aZLtYUZUkH = false;}
      if(WtesWxqxTx == true){WtesWxqxTx = false;}
      if(UMPDInXCLg == true){UMPDInXCLg = false;}
      if(BghDptgUOo == true){BghDptgUOo = false;}
      if(heYEYfJphT == true){heYEYfJphT = false;}
      if(fkSiQOJHkk == true){fkSiQOJHkk = false;}
      if(wXIDFoMbDb == true){wXIDFoMbDb = false;}
      if(QVhdPomLdc == true){QVhdPomLdc = false;}
      if(ehTrBPOzla == true){ehTrBPOzla = false;}
      if(kYidsKVVzj == true){kYidsKVVzj = false;}
      if(TgmGDJDnSa == true){TgmGDJDnSa = false;}
      if(bycIGODQCp == true){bycIGODQCp = false;}
      if(aMobqqmDkE == true){aMobqqmDkE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CWGUNTISFL
{ 
  void ShDxoCHpjV()
  { 
      bool XupDMUwHzR = false;
      bool czDwXFuioN = false;
      bool qRTkIGGbTk = false;
      bool orSKbPZqHX = false;
      bool KDKqPNpzBC = false;
      bool YXTOLFbFtG = false;
      bool NTmNckgsUH = false;
      bool eEbRDmHcVu = false;
      bool PHaQLQXEyV = false;
      bool nUwBJpPwOd = false;
      bool fxdsXUwCLX = false;
      bool yzizpGrWBL = false;
      bool NctySJHZHM = false;
      bool XKNqOSdgsq = false;
      bool TUrZXokxKD = false;
      bool ysuCQDCeaN = false;
      bool MWtyAnkrjW = false;
      bool cKcKrsjUac = false;
      bool XKOEOePLaL = false;
      bool QyGedwZsZj = false;
      string yXStKCQkzk;
      string szMBOYfuem;
      string DRtYxmxeAG;
      string zmTCgVRUYa;
      string ErhHdCtDoZ;
      string TfofifdtxW;
      string EkjskGfJTr;
      string GKVEhLjltt;
      string rtpamTxnTB;
      string rXXCWSHoWX;
      string WkixSIJkxX;
      string wqzCdKuJFQ;
      string IrpSAilTgP;
      string DtPWXHKsId;
      string KLquEAXVYM;
      string WxiFOetQwi;
      string VpEgTBbbeV;
      string zCBbGwBtNA;
      string LQtUrGKJIs;
      string MswYHUHJbC;
      if(yXStKCQkzk == WkixSIJkxX){XupDMUwHzR = true;}
      else if(WkixSIJkxX == yXStKCQkzk){fxdsXUwCLX = true;}
      if(szMBOYfuem == wqzCdKuJFQ){czDwXFuioN = true;}
      else if(wqzCdKuJFQ == szMBOYfuem){yzizpGrWBL = true;}
      if(DRtYxmxeAG == IrpSAilTgP){qRTkIGGbTk = true;}
      else if(IrpSAilTgP == DRtYxmxeAG){NctySJHZHM = true;}
      if(zmTCgVRUYa == DtPWXHKsId){orSKbPZqHX = true;}
      else if(DtPWXHKsId == zmTCgVRUYa){XKNqOSdgsq = true;}
      if(ErhHdCtDoZ == KLquEAXVYM){KDKqPNpzBC = true;}
      else if(KLquEAXVYM == ErhHdCtDoZ){TUrZXokxKD = true;}
      if(TfofifdtxW == WxiFOetQwi){YXTOLFbFtG = true;}
      else if(WxiFOetQwi == TfofifdtxW){ysuCQDCeaN = true;}
      if(EkjskGfJTr == VpEgTBbbeV){NTmNckgsUH = true;}
      else if(VpEgTBbbeV == EkjskGfJTr){MWtyAnkrjW = true;}
      if(GKVEhLjltt == zCBbGwBtNA){eEbRDmHcVu = true;}
      if(rtpamTxnTB == LQtUrGKJIs){PHaQLQXEyV = true;}
      if(rXXCWSHoWX == MswYHUHJbC){nUwBJpPwOd = true;}
      while(zCBbGwBtNA == GKVEhLjltt){cKcKrsjUac = true;}
      while(LQtUrGKJIs == LQtUrGKJIs){XKOEOePLaL = true;}
      while(MswYHUHJbC == MswYHUHJbC){QyGedwZsZj = true;}
      if(XupDMUwHzR == true){XupDMUwHzR = false;}
      if(czDwXFuioN == true){czDwXFuioN = false;}
      if(qRTkIGGbTk == true){qRTkIGGbTk = false;}
      if(orSKbPZqHX == true){orSKbPZqHX = false;}
      if(KDKqPNpzBC == true){KDKqPNpzBC = false;}
      if(YXTOLFbFtG == true){YXTOLFbFtG = false;}
      if(NTmNckgsUH == true){NTmNckgsUH = false;}
      if(eEbRDmHcVu == true){eEbRDmHcVu = false;}
      if(PHaQLQXEyV == true){PHaQLQXEyV = false;}
      if(nUwBJpPwOd == true){nUwBJpPwOd = false;}
      if(fxdsXUwCLX == true){fxdsXUwCLX = false;}
      if(yzizpGrWBL == true){yzizpGrWBL = false;}
      if(NctySJHZHM == true){NctySJHZHM = false;}
      if(XKNqOSdgsq == true){XKNqOSdgsq = false;}
      if(TUrZXokxKD == true){TUrZXokxKD = false;}
      if(ysuCQDCeaN == true){ysuCQDCeaN = false;}
      if(MWtyAnkrjW == true){MWtyAnkrjW = false;}
      if(cKcKrsjUac == true){cKcKrsjUac = false;}
      if(XKOEOePLaL == true){XKOEOePLaL = false;}
      if(QyGedwZsZj == true){QyGedwZsZj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSGPMYFHSX
{ 
  void WPYPmwOYaT()
  { 
      bool cywHXxitbq = false;
      bool zkRSQNWCal = false;
      bool bCyUWDHFic = false;
      bool GSwbGSxdLj = false;
      bool eQDRfcstbK = false;
      bool rVjuZZAakT = false;
      bool odLzkfnoMy = false;
      bool QsqpHLzfns = false;
      bool KNcXkjiABf = false;
      bool RVrquAFDgA = false;
      bool oDgdsyetnN = false;
      bool aUlrJaBmNA = false;
      bool xnmfftBztG = false;
      bool GuznEGfzel = false;
      bool EoLmExiAhU = false;
      bool zSpfCAPByy = false;
      bool xfzhHfUynC = false;
      bool tCHbuIcAbh = false;
      bool LARZHnFSkD = false;
      bool qeBfoYocfY = false;
      string sbqkeWrDtH;
      string FMNjJkGEOx;
      string OzDMnPkxyd;
      string fxlafTVFUp;
      string wLCOUCNRlS;
      string zUeJxtXdwP;
      string luEPbIamEo;
      string OAiXBCxnrl;
      string CSLedKRbcl;
      string urIFDBGlmM;
      string bZNwEzlGIu;
      string xjlKNSiYlR;
      string pyKStWqcUz;
      string uKBeJcFOae;
      string XLTgnLFxrk;
      string RgAVVdOuBh;
      string HIlIzlhGBj;
      string NUyGsedddi;
      string QskihNKfIf;
      string NKMsXPYKhC;
      if(sbqkeWrDtH == bZNwEzlGIu){cywHXxitbq = true;}
      else if(bZNwEzlGIu == sbqkeWrDtH){oDgdsyetnN = true;}
      if(FMNjJkGEOx == xjlKNSiYlR){zkRSQNWCal = true;}
      else if(xjlKNSiYlR == FMNjJkGEOx){aUlrJaBmNA = true;}
      if(OzDMnPkxyd == pyKStWqcUz){bCyUWDHFic = true;}
      else if(pyKStWqcUz == OzDMnPkxyd){xnmfftBztG = true;}
      if(fxlafTVFUp == uKBeJcFOae){GSwbGSxdLj = true;}
      else if(uKBeJcFOae == fxlafTVFUp){GuznEGfzel = true;}
      if(wLCOUCNRlS == XLTgnLFxrk){eQDRfcstbK = true;}
      else if(XLTgnLFxrk == wLCOUCNRlS){EoLmExiAhU = true;}
      if(zUeJxtXdwP == RgAVVdOuBh){rVjuZZAakT = true;}
      else if(RgAVVdOuBh == zUeJxtXdwP){zSpfCAPByy = true;}
      if(luEPbIamEo == HIlIzlhGBj){odLzkfnoMy = true;}
      else if(HIlIzlhGBj == luEPbIamEo){xfzhHfUynC = true;}
      if(OAiXBCxnrl == NUyGsedddi){QsqpHLzfns = true;}
      if(CSLedKRbcl == QskihNKfIf){KNcXkjiABf = true;}
      if(urIFDBGlmM == NKMsXPYKhC){RVrquAFDgA = true;}
      while(NUyGsedddi == OAiXBCxnrl){tCHbuIcAbh = true;}
      while(QskihNKfIf == QskihNKfIf){LARZHnFSkD = true;}
      while(NKMsXPYKhC == NKMsXPYKhC){qeBfoYocfY = true;}
      if(cywHXxitbq == true){cywHXxitbq = false;}
      if(zkRSQNWCal == true){zkRSQNWCal = false;}
      if(bCyUWDHFic == true){bCyUWDHFic = false;}
      if(GSwbGSxdLj == true){GSwbGSxdLj = false;}
      if(eQDRfcstbK == true){eQDRfcstbK = false;}
      if(rVjuZZAakT == true){rVjuZZAakT = false;}
      if(odLzkfnoMy == true){odLzkfnoMy = false;}
      if(QsqpHLzfns == true){QsqpHLzfns = false;}
      if(KNcXkjiABf == true){KNcXkjiABf = false;}
      if(RVrquAFDgA == true){RVrquAFDgA = false;}
      if(oDgdsyetnN == true){oDgdsyetnN = false;}
      if(aUlrJaBmNA == true){aUlrJaBmNA = false;}
      if(xnmfftBztG == true){xnmfftBztG = false;}
      if(GuznEGfzel == true){GuznEGfzel = false;}
      if(EoLmExiAhU == true){EoLmExiAhU = false;}
      if(zSpfCAPByy == true){zSpfCAPByy = false;}
      if(xfzhHfUynC == true){xfzhHfUynC = false;}
      if(tCHbuIcAbh == true){tCHbuIcAbh = false;}
      if(LARZHnFSkD == true){LARZHnFSkD = false;}
      if(qeBfoYocfY == true){qeBfoYocfY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRVUTQMEMH
{ 
  void QxUxPGhCuG()
  { 
      bool NgaHcpBRNo = false;
      bool EEbPBZKUqd = false;
      bool QfgSFDlTWx = false;
      bool WWeKsbEjOU = false;
      bool GrViiUsZoF = false;
      bool uuOxOhzHBZ = false;
      bool EhtPRhZQWZ = false;
      bool UZFWXYKyik = false;
      bool JLeRBbHgwK = false;
      bool cxioPXxFQB = false;
      bool tcDPkVorYo = false;
      bool WBXQPrDcOo = false;
      bool arTLxXqPGz = false;
      bool bFghpfHOgf = false;
      bool lOHHmbYRYW = false;
      bool UUqbaCJrSN = false;
      bool eZlZNRToZj = false;
      bool knuhDLkMXU = false;
      bool yYqidGNFHn = false;
      bool WPwTBMchtV = false;
      string XBhFZkOToz;
      string yXWGUbLNks;
      string qhGjjrWHzy;
      string zyycznoihc;
      string LuxcqsaUmr;
      string uLOLEotxVg;
      string OHUpAzYsGf;
      string lbeIgwkdrq;
      string RBTHDnimXK;
      string tqNBNEaHcr;
      string TgOHFSfGdI;
      string EQFeOMmMmL;
      string PlVwktNdtb;
      string VdAAWjmLBj;
      string IcIOFdlilB;
      string RNTQbhLRWK;
      string FCMCmaPFHe;
      string YaLCDmcGpH;
      string IeqrKIJiXn;
      string YUoqeFPGbe;
      if(XBhFZkOToz == TgOHFSfGdI){NgaHcpBRNo = true;}
      else if(TgOHFSfGdI == XBhFZkOToz){tcDPkVorYo = true;}
      if(yXWGUbLNks == EQFeOMmMmL){EEbPBZKUqd = true;}
      else if(EQFeOMmMmL == yXWGUbLNks){WBXQPrDcOo = true;}
      if(qhGjjrWHzy == PlVwktNdtb){QfgSFDlTWx = true;}
      else if(PlVwktNdtb == qhGjjrWHzy){arTLxXqPGz = true;}
      if(zyycznoihc == VdAAWjmLBj){WWeKsbEjOU = true;}
      else if(VdAAWjmLBj == zyycznoihc){bFghpfHOgf = true;}
      if(LuxcqsaUmr == IcIOFdlilB){GrViiUsZoF = true;}
      else if(IcIOFdlilB == LuxcqsaUmr){lOHHmbYRYW = true;}
      if(uLOLEotxVg == RNTQbhLRWK){uuOxOhzHBZ = true;}
      else if(RNTQbhLRWK == uLOLEotxVg){UUqbaCJrSN = true;}
      if(OHUpAzYsGf == FCMCmaPFHe){EhtPRhZQWZ = true;}
      else if(FCMCmaPFHe == OHUpAzYsGf){eZlZNRToZj = true;}
      if(lbeIgwkdrq == YaLCDmcGpH){UZFWXYKyik = true;}
      if(RBTHDnimXK == IeqrKIJiXn){JLeRBbHgwK = true;}
      if(tqNBNEaHcr == YUoqeFPGbe){cxioPXxFQB = true;}
      while(YaLCDmcGpH == lbeIgwkdrq){knuhDLkMXU = true;}
      while(IeqrKIJiXn == IeqrKIJiXn){yYqidGNFHn = true;}
      while(YUoqeFPGbe == YUoqeFPGbe){WPwTBMchtV = true;}
      if(NgaHcpBRNo == true){NgaHcpBRNo = false;}
      if(EEbPBZKUqd == true){EEbPBZKUqd = false;}
      if(QfgSFDlTWx == true){QfgSFDlTWx = false;}
      if(WWeKsbEjOU == true){WWeKsbEjOU = false;}
      if(GrViiUsZoF == true){GrViiUsZoF = false;}
      if(uuOxOhzHBZ == true){uuOxOhzHBZ = false;}
      if(EhtPRhZQWZ == true){EhtPRhZQWZ = false;}
      if(UZFWXYKyik == true){UZFWXYKyik = false;}
      if(JLeRBbHgwK == true){JLeRBbHgwK = false;}
      if(cxioPXxFQB == true){cxioPXxFQB = false;}
      if(tcDPkVorYo == true){tcDPkVorYo = false;}
      if(WBXQPrDcOo == true){WBXQPrDcOo = false;}
      if(arTLxXqPGz == true){arTLxXqPGz = false;}
      if(bFghpfHOgf == true){bFghpfHOgf = false;}
      if(lOHHmbYRYW == true){lOHHmbYRYW = false;}
      if(UUqbaCJrSN == true){UUqbaCJrSN = false;}
      if(eZlZNRToZj == true){eZlZNRToZj = false;}
      if(knuhDLkMXU == true){knuhDLkMXU = false;}
      if(yYqidGNFHn == true){yYqidGNFHn = false;}
      if(WPwTBMchtV == true){WPwTBMchtV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGUSGWUJXC
{ 
  void qLcSjfzJFg()
  { 
      bool zmtSXRdhbK = false;
      bool syDibEuqgg = false;
      bool KSWHQxtRIE = false;
      bool njICNMHeJa = false;
      bool WuEnQrjMCN = false;
      bool YHLDxfPmCZ = false;
      bool WMZXVJpBVO = false;
      bool xPgGKPNhqX = false;
      bool MgPuegXEEg = false;
      bool wTciDKUgRG = false;
      bool CiqmQIZEsh = false;
      bool RhueNpxero = false;
      bool kkwoRcmyDA = false;
      bool ugPjUdpbdV = false;
      bool GTLWPOYxVM = false;
      bool MoocVQlCVm = false;
      bool VbAsmkRLJj = false;
      bool zUAWiQZZYC = false;
      bool DobqmFrmND = false;
      bool qnGqAdSSid = false;
      string GjXDYmpyWO;
      string fKgWfdZuwb;
      string SmfDIpaEIh;
      string tlSoqluDCI;
      string fRuJAKyCCS;
      string pLBXLSEUui;
      string MlpoUtqqft;
      string iVrmuBrVCy;
      string qYBoqhkudX;
      string hZISwtaFnG;
      string SGVIjTSNbJ;
      string ahRwrmjBxm;
      string JwNHLINYpB;
      string alhwfjCsFX;
      string OWSTxzILaI;
      string JZIAxVsOwb;
      string GsXZinAVQH;
      string kquZYlctKM;
      string zBygrBdgzJ;
      string qnwdRUyskI;
      if(GjXDYmpyWO == SGVIjTSNbJ){zmtSXRdhbK = true;}
      else if(SGVIjTSNbJ == GjXDYmpyWO){CiqmQIZEsh = true;}
      if(fKgWfdZuwb == ahRwrmjBxm){syDibEuqgg = true;}
      else if(ahRwrmjBxm == fKgWfdZuwb){RhueNpxero = true;}
      if(SmfDIpaEIh == JwNHLINYpB){KSWHQxtRIE = true;}
      else if(JwNHLINYpB == SmfDIpaEIh){kkwoRcmyDA = true;}
      if(tlSoqluDCI == alhwfjCsFX){njICNMHeJa = true;}
      else if(alhwfjCsFX == tlSoqluDCI){ugPjUdpbdV = true;}
      if(fRuJAKyCCS == OWSTxzILaI){WuEnQrjMCN = true;}
      else if(OWSTxzILaI == fRuJAKyCCS){GTLWPOYxVM = true;}
      if(pLBXLSEUui == JZIAxVsOwb){YHLDxfPmCZ = true;}
      else if(JZIAxVsOwb == pLBXLSEUui){MoocVQlCVm = true;}
      if(MlpoUtqqft == GsXZinAVQH){WMZXVJpBVO = true;}
      else if(GsXZinAVQH == MlpoUtqqft){VbAsmkRLJj = true;}
      if(iVrmuBrVCy == kquZYlctKM){xPgGKPNhqX = true;}
      if(qYBoqhkudX == zBygrBdgzJ){MgPuegXEEg = true;}
      if(hZISwtaFnG == qnwdRUyskI){wTciDKUgRG = true;}
      while(kquZYlctKM == iVrmuBrVCy){zUAWiQZZYC = true;}
      while(zBygrBdgzJ == zBygrBdgzJ){DobqmFrmND = true;}
      while(qnwdRUyskI == qnwdRUyskI){qnGqAdSSid = true;}
      if(zmtSXRdhbK == true){zmtSXRdhbK = false;}
      if(syDibEuqgg == true){syDibEuqgg = false;}
      if(KSWHQxtRIE == true){KSWHQxtRIE = false;}
      if(njICNMHeJa == true){njICNMHeJa = false;}
      if(WuEnQrjMCN == true){WuEnQrjMCN = false;}
      if(YHLDxfPmCZ == true){YHLDxfPmCZ = false;}
      if(WMZXVJpBVO == true){WMZXVJpBVO = false;}
      if(xPgGKPNhqX == true){xPgGKPNhqX = false;}
      if(MgPuegXEEg == true){MgPuegXEEg = false;}
      if(wTciDKUgRG == true){wTciDKUgRG = false;}
      if(CiqmQIZEsh == true){CiqmQIZEsh = false;}
      if(RhueNpxero == true){RhueNpxero = false;}
      if(kkwoRcmyDA == true){kkwoRcmyDA = false;}
      if(ugPjUdpbdV == true){ugPjUdpbdV = false;}
      if(GTLWPOYxVM == true){GTLWPOYxVM = false;}
      if(MoocVQlCVm == true){MoocVQlCVm = false;}
      if(VbAsmkRLJj == true){VbAsmkRLJj = false;}
      if(zUAWiQZZYC == true){zUAWiQZZYC = false;}
      if(DobqmFrmND == true){DobqmFrmND = false;}
      if(qnGqAdSSid == true){qnGqAdSSid = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFOBEROGUS
{ 
  void FDCSSrxcFa()
  { 
      bool EEMWfRXqaw = false;
      bool otmEyDLCRP = false;
      bool aoWRCKwZya = false;
      bool FCrQtTnnsi = false;
      bool wfxZToiPfi = false;
      bool IwdSaPguUU = false;
      bool VyrAplCWJe = false;
      bool PWIiSuqxxM = false;
      bool bftORIYYoe = false;
      bool lrTXNymxih = false;
      bool mLFBTlntAf = false;
      bool XjyHsoDchh = false;
      bool NcherWCjUU = false;
      bool HsNPYQaruf = false;
      bool UdYIGCsLeX = false;
      bool tJOBUKcaJw = false;
      bool iDZeYdViib = false;
      bool OLhCMiEYXp = false;
      bool cqFwZxdMtO = false;
      bool mzizxREsjb = false;
      string TtLBfGkQqJ;
      string lAGPjGiXwz;
      string NSgyeXsGRe;
      string pRUNypYhFj;
      string xhPcygGqOY;
      string tIaDNANNVH;
      string MdyMTUesRt;
      string gBRLBfCEzy;
      string RCqsjgpRzy;
      string bLLyXTiDId;
      string BNZUrspPBg;
      string xJOXpKlFbl;
      string dNsSRVoTmh;
      string xzuVwEcWBq;
      string qZPSASxnIN;
      string gcbVzmUGDW;
      string EWbTjyNral;
      string gPEkuDyaSz;
      string XBLZBUWYVJ;
      string iWTelUywhC;
      if(TtLBfGkQqJ == BNZUrspPBg){EEMWfRXqaw = true;}
      else if(BNZUrspPBg == TtLBfGkQqJ){mLFBTlntAf = true;}
      if(lAGPjGiXwz == xJOXpKlFbl){otmEyDLCRP = true;}
      else if(xJOXpKlFbl == lAGPjGiXwz){XjyHsoDchh = true;}
      if(NSgyeXsGRe == dNsSRVoTmh){aoWRCKwZya = true;}
      else if(dNsSRVoTmh == NSgyeXsGRe){NcherWCjUU = true;}
      if(pRUNypYhFj == xzuVwEcWBq){FCrQtTnnsi = true;}
      else if(xzuVwEcWBq == pRUNypYhFj){HsNPYQaruf = true;}
      if(xhPcygGqOY == qZPSASxnIN){wfxZToiPfi = true;}
      else if(qZPSASxnIN == xhPcygGqOY){UdYIGCsLeX = true;}
      if(tIaDNANNVH == gcbVzmUGDW){IwdSaPguUU = true;}
      else if(gcbVzmUGDW == tIaDNANNVH){tJOBUKcaJw = true;}
      if(MdyMTUesRt == EWbTjyNral){VyrAplCWJe = true;}
      else if(EWbTjyNral == MdyMTUesRt){iDZeYdViib = true;}
      if(gBRLBfCEzy == gPEkuDyaSz){PWIiSuqxxM = true;}
      if(RCqsjgpRzy == XBLZBUWYVJ){bftORIYYoe = true;}
      if(bLLyXTiDId == iWTelUywhC){lrTXNymxih = true;}
      while(gPEkuDyaSz == gBRLBfCEzy){OLhCMiEYXp = true;}
      while(XBLZBUWYVJ == XBLZBUWYVJ){cqFwZxdMtO = true;}
      while(iWTelUywhC == iWTelUywhC){mzizxREsjb = true;}
      if(EEMWfRXqaw == true){EEMWfRXqaw = false;}
      if(otmEyDLCRP == true){otmEyDLCRP = false;}
      if(aoWRCKwZya == true){aoWRCKwZya = false;}
      if(FCrQtTnnsi == true){FCrQtTnnsi = false;}
      if(wfxZToiPfi == true){wfxZToiPfi = false;}
      if(IwdSaPguUU == true){IwdSaPguUU = false;}
      if(VyrAplCWJe == true){VyrAplCWJe = false;}
      if(PWIiSuqxxM == true){PWIiSuqxxM = false;}
      if(bftORIYYoe == true){bftORIYYoe = false;}
      if(lrTXNymxih == true){lrTXNymxih = false;}
      if(mLFBTlntAf == true){mLFBTlntAf = false;}
      if(XjyHsoDchh == true){XjyHsoDchh = false;}
      if(NcherWCjUU == true){NcherWCjUU = false;}
      if(HsNPYQaruf == true){HsNPYQaruf = false;}
      if(UdYIGCsLeX == true){UdYIGCsLeX = false;}
      if(tJOBUKcaJw == true){tJOBUKcaJw = false;}
      if(iDZeYdViib == true){iDZeYdViib = false;}
      if(OLhCMiEYXp == true){OLhCMiEYXp = false;}
      if(cqFwZxdMtO == true){cqFwZxdMtO = false;}
      if(mzizxREsjb == true){mzizxREsjb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTWVSKYANE
{ 
  void pawyXIQlqn()
  { 
      bool cEtyjBfKsK = false;
      bool lGHeYAOEuE = false;
      bool QZWrJkfaJg = false;
      bool axthqqCWQI = false;
      bool ywKnTnPiTr = false;
      bool DHSZwChBny = false;
      bool VFBMioMYnh = false;
      bool xrnmGTPhXV = false;
      bool VwHQdTdTln = false;
      bool JAiRlsuyFd = false;
      bool apuktKTeTb = false;
      bool mzdScZxjhO = false;
      bool KrmzXwJVBM = false;
      bool YQcsteAVWT = false;
      bool AzzJAKWQoL = false;
      bool wKQpTiDuMx = false;
      bool BxcHCVVjXx = false;
      bool ZaNOOLrczN = false;
      bool ZrfpQOAmZL = false;
      bool bEIYRCWrGd = false;
      string LfuIRuZtUw;
      string PPZDVWUWqL;
      string fuHcWmCcIB;
      string fpDGsIJhOU;
      string BSWMcoosnE;
      string ZSWWbQXRkd;
      string rwlSPYMTJM;
      string NmIWKMXuAh;
      string xJoEbMSgec;
      string kqwjbEgDwD;
      string cViaqmJAMP;
      string rcRDgiHgqD;
      string FeofbVpYtG;
      string eTywEbZNNo;
      string DSTPkHZsDs;
      string wAMsxxgCzU;
      string wkGFjXeUzE;
      string ItTBzmLZuT;
      string uwVBKeHEyG;
      string uWOrrRLNeM;
      if(LfuIRuZtUw == cViaqmJAMP){cEtyjBfKsK = true;}
      else if(cViaqmJAMP == LfuIRuZtUw){apuktKTeTb = true;}
      if(PPZDVWUWqL == rcRDgiHgqD){lGHeYAOEuE = true;}
      else if(rcRDgiHgqD == PPZDVWUWqL){mzdScZxjhO = true;}
      if(fuHcWmCcIB == FeofbVpYtG){QZWrJkfaJg = true;}
      else if(FeofbVpYtG == fuHcWmCcIB){KrmzXwJVBM = true;}
      if(fpDGsIJhOU == eTywEbZNNo){axthqqCWQI = true;}
      else if(eTywEbZNNo == fpDGsIJhOU){YQcsteAVWT = true;}
      if(BSWMcoosnE == DSTPkHZsDs){ywKnTnPiTr = true;}
      else if(DSTPkHZsDs == BSWMcoosnE){AzzJAKWQoL = true;}
      if(ZSWWbQXRkd == wAMsxxgCzU){DHSZwChBny = true;}
      else if(wAMsxxgCzU == ZSWWbQXRkd){wKQpTiDuMx = true;}
      if(rwlSPYMTJM == wkGFjXeUzE){VFBMioMYnh = true;}
      else if(wkGFjXeUzE == rwlSPYMTJM){BxcHCVVjXx = true;}
      if(NmIWKMXuAh == ItTBzmLZuT){xrnmGTPhXV = true;}
      if(xJoEbMSgec == uwVBKeHEyG){VwHQdTdTln = true;}
      if(kqwjbEgDwD == uWOrrRLNeM){JAiRlsuyFd = true;}
      while(ItTBzmLZuT == NmIWKMXuAh){ZaNOOLrczN = true;}
      while(uwVBKeHEyG == uwVBKeHEyG){ZrfpQOAmZL = true;}
      while(uWOrrRLNeM == uWOrrRLNeM){bEIYRCWrGd = true;}
      if(cEtyjBfKsK == true){cEtyjBfKsK = false;}
      if(lGHeYAOEuE == true){lGHeYAOEuE = false;}
      if(QZWrJkfaJg == true){QZWrJkfaJg = false;}
      if(axthqqCWQI == true){axthqqCWQI = false;}
      if(ywKnTnPiTr == true){ywKnTnPiTr = false;}
      if(DHSZwChBny == true){DHSZwChBny = false;}
      if(VFBMioMYnh == true){VFBMioMYnh = false;}
      if(xrnmGTPhXV == true){xrnmGTPhXV = false;}
      if(VwHQdTdTln == true){VwHQdTdTln = false;}
      if(JAiRlsuyFd == true){JAiRlsuyFd = false;}
      if(apuktKTeTb == true){apuktKTeTb = false;}
      if(mzdScZxjhO == true){mzdScZxjhO = false;}
      if(KrmzXwJVBM == true){KrmzXwJVBM = false;}
      if(YQcsteAVWT == true){YQcsteAVWT = false;}
      if(AzzJAKWQoL == true){AzzJAKWQoL = false;}
      if(wKQpTiDuMx == true){wKQpTiDuMx = false;}
      if(BxcHCVVjXx == true){BxcHCVVjXx = false;}
      if(ZaNOOLrczN == true){ZaNOOLrczN = false;}
      if(ZrfpQOAmZL == true){ZrfpQOAmZL = false;}
      if(bEIYRCWrGd == true){bEIYRCWrGd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUMCAKFXWR
{ 
  void huOXlRogRb()
  { 
      bool kYAdJrqUps = false;
      bool tAiPprQqXU = false;
      bool fNLiPjzycc = false;
      bool qFwILaBqTC = false;
      bool tUYiZTFsOP = false;
      bool ZVCwEWNRNY = false;
      bool srqMBoEaEP = false;
      bool pYXUZLobIw = false;
      bool eGjNDVDzDn = false;
      bool NjctJBcLhk = false;
      bool PenyYAxgVs = false;
      bool hkIRtmIcJf = false;
      bool lEWPBGwdLY = false;
      bool hctWgARkoC = false;
      bool XVcKFcaKzW = false;
      bool szCBzKHYxR = false;
      bool DTVxKEplkt = false;
      bool UWnGHPbMJY = false;
      bool fldneiasXV = false;
      bool rsnWyEAezA = false;
      string HGSYQeRtpU;
      string ngInXoHoBc;
      string PJZucUrtuG;
      string dlzQTwzyaN;
      string CrZwlhoxAt;
      string HhVpIyfXuw;
      string lXzjqChrUb;
      string pINnaXjdJu;
      string eutAzuPIHU;
      string PbDeaerpFi;
      string zxcXEyThPk;
      string OBNzQqdyku;
      string lYjzLNFiMw;
      string etYZugRVuA;
      string bhsWFONDNi;
      string AtEJxaNcMq;
      string skUSFUcnDj;
      string ZIDjTEfMsx;
      string ABUcukoObU;
      string ToIEHpMZQk;
      if(HGSYQeRtpU == zxcXEyThPk){kYAdJrqUps = true;}
      else if(zxcXEyThPk == HGSYQeRtpU){PenyYAxgVs = true;}
      if(ngInXoHoBc == OBNzQqdyku){tAiPprQqXU = true;}
      else if(OBNzQqdyku == ngInXoHoBc){hkIRtmIcJf = true;}
      if(PJZucUrtuG == lYjzLNFiMw){fNLiPjzycc = true;}
      else if(lYjzLNFiMw == PJZucUrtuG){lEWPBGwdLY = true;}
      if(dlzQTwzyaN == etYZugRVuA){qFwILaBqTC = true;}
      else if(etYZugRVuA == dlzQTwzyaN){hctWgARkoC = true;}
      if(CrZwlhoxAt == bhsWFONDNi){tUYiZTFsOP = true;}
      else if(bhsWFONDNi == CrZwlhoxAt){XVcKFcaKzW = true;}
      if(HhVpIyfXuw == AtEJxaNcMq){ZVCwEWNRNY = true;}
      else if(AtEJxaNcMq == HhVpIyfXuw){szCBzKHYxR = true;}
      if(lXzjqChrUb == skUSFUcnDj){srqMBoEaEP = true;}
      else if(skUSFUcnDj == lXzjqChrUb){DTVxKEplkt = true;}
      if(pINnaXjdJu == ZIDjTEfMsx){pYXUZLobIw = true;}
      if(eutAzuPIHU == ABUcukoObU){eGjNDVDzDn = true;}
      if(PbDeaerpFi == ToIEHpMZQk){NjctJBcLhk = true;}
      while(ZIDjTEfMsx == pINnaXjdJu){UWnGHPbMJY = true;}
      while(ABUcukoObU == ABUcukoObU){fldneiasXV = true;}
      while(ToIEHpMZQk == ToIEHpMZQk){rsnWyEAezA = true;}
      if(kYAdJrqUps == true){kYAdJrqUps = false;}
      if(tAiPprQqXU == true){tAiPprQqXU = false;}
      if(fNLiPjzycc == true){fNLiPjzycc = false;}
      if(qFwILaBqTC == true){qFwILaBqTC = false;}
      if(tUYiZTFsOP == true){tUYiZTFsOP = false;}
      if(ZVCwEWNRNY == true){ZVCwEWNRNY = false;}
      if(srqMBoEaEP == true){srqMBoEaEP = false;}
      if(pYXUZLobIw == true){pYXUZLobIw = false;}
      if(eGjNDVDzDn == true){eGjNDVDzDn = false;}
      if(NjctJBcLhk == true){NjctJBcLhk = false;}
      if(PenyYAxgVs == true){PenyYAxgVs = false;}
      if(hkIRtmIcJf == true){hkIRtmIcJf = false;}
      if(lEWPBGwdLY == true){lEWPBGwdLY = false;}
      if(hctWgARkoC == true){hctWgARkoC = false;}
      if(XVcKFcaKzW == true){XVcKFcaKzW = false;}
      if(szCBzKHYxR == true){szCBzKHYxR = false;}
      if(DTVxKEplkt == true){DTVxKEplkt = false;}
      if(UWnGHPbMJY == true){UWnGHPbMJY = false;}
      if(fldneiasXV == true){fldneiasXV = false;}
      if(rsnWyEAezA == true){rsnWyEAezA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RXSYIGZTFT
{ 
  void VKctyjaQky()
  { 
      bool LtxWRkJzig = false;
      bool KdMRWewPTG = false;
      bool wtACkGKRMi = false;
      bool bLQhyKkaCR = false;
      bool lpTZcnefDc = false;
      bool NXukJQtukK = false;
      bool ZqlzFyNdTM = false;
      bool sUMCTGaaZx = false;
      bool adOjUDQeXg = false;
      bool PppqqtDTTd = false;
      bool ZBMpirKrRD = false;
      bool pTVnjwcCeB = false;
      bool hiFmwCeVLY = false;
      bool CGGuWZQXAb = false;
      bool sYNUpwUCHu = false;
      bool RAoSwquZtf = false;
      bool NogrAjMZQK = false;
      bool eECCIIUkwz = false;
      bool hcOPGCQmyf = false;
      bool dqdTODqVUG = false;
      string ulJagDXPKU;
      string mSdeXkJwVJ;
      string PcDHociTlM;
      string yGziHTPlnc;
      string hXIxRRiGyC;
      string GaNtpRiBkD;
      string UEcxVfStXD;
      string UWIsaqUGpX;
      string tbUjGXrFro;
      string kNAjIdtKak;
      string ynithjSUTz;
      string wbLNJrisqy;
      string mNBhSGVYkw;
      string xJeEYFsZBV;
      string EXlssIBmaQ;
      string tBTcxklBbb;
      string NtjWBlxHoE;
      string yJrUsPaInJ;
      string EixTCuoCHm;
      string SryZHKnPqG;
      if(ulJagDXPKU == ynithjSUTz){LtxWRkJzig = true;}
      else if(ynithjSUTz == ulJagDXPKU){ZBMpirKrRD = true;}
      if(mSdeXkJwVJ == wbLNJrisqy){KdMRWewPTG = true;}
      else if(wbLNJrisqy == mSdeXkJwVJ){pTVnjwcCeB = true;}
      if(PcDHociTlM == mNBhSGVYkw){wtACkGKRMi = true;}
      else if(mNBhSGVYkw == PcDHociTlM){hiFmwCeVLY = true;}
      if(yGziHTPlnc == xJeEYFsZBV){bLQhyKkaCR = true;}
      else if(xJeEYFsZBV == yGziHTPlnc){CGGuWZQXAb = true;}
      if(hXIxRRiGyC == EXlssIBmaQ){lpTZcnefDc = true;}
      else if(EXlssIBmaQ == hXIxRRiGyC){sYNUpwUCHu = true;}
      if(GaNtpRiBkD == tBTcxklBbb){NXukJQtukK = true;}
      else if(tBTcxklBbb == GaNtpRiBkD){RAoSwquZtf = true;}
      if(UEcxVfStXD == NtjWBlxHoE){ZqlzFyNdTM = true;}
      else if(NtjWBlxHoE == UEcxVfStXD){NogrAjMZQK = true;}
      if(UWIsaqUGpX == yJrUsPaInJ){sUMCTGaaZx = true;}
      if(tbUjGXrFro == EixTCuoCHm){adOjUDQeXg = true;}
      if(kNAjIdtKak == SryZHKnPqG){PppqqtDTTd = true;}
      while(yJrUsPaInJ == UWIsaqUGpX){eECCIIUkwz = true;}
      while(EixTCuoCHm == EixTCuoCHm){hcOPGCQmyf = true;}
      while(SryZHKnPqG == SryZHKnPqG){dqdTODqVUG = true;}
      if(LtxWRkJzig == true){LtxWRkJzig = false;}
      if(KdMRWewPTG == true){KdMRWewPTG = false;}
      if(wtACkGKRMi == true){wtACkGKRMi = false;}
      if(bLQhyKkaCR == true){bLQhyKkaCR = false;}
      if(lpTZcnefDc == true){lpTZcnefDc = false;}
      if(NXukJQtukK == true){NXukJQtukK = false;}
      if(ZqlzFyNdTM == true){ZqlzFyNdTM = false;}
      if(sUMCTGaaZx == true){sUMCTGaaZx = false;}
      if(adOjUDQeXg == true){adOjUDQeXg = false;}
      if(PppqqtDTTd == true){PppqqtDTTd = false;}
      if(ZBMpirKrRD == true){ZBMpirKrRD = false;}
      if(pTVnjwcCeB == true){pTVnjwcCeB = false;}
      if(hiFmwCeVLY == true){hiFmwCeVLY = false;}
      if(CGGuWZQXAb == true){CGGuWZQXAb = false;}
      if(sYNUpwUCHu == true){sYNUpwUCHu = false;}
      if(RAoSwquZtf == true){RAoSwquZtf = false;}
      if(NogrAjMZQK == true){NogrAjMZQK = false;}
      if(eECCIIUkwz == true){eECCIIUkwz = false;}
      if(hcOPGCQmyf == true){hcOPGCQmyf = false;}
      if(dqdTODqVUG == true){dqdTODqVUG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKKBLVKVXG
{ 
  void KqOVHMdzlp()
  { 
      bool rbCdSkfbUU = false;
      bool WqzaRSJoyH = false;
      bool PoKhwIqoow = false;
      bool EYiKEoZZTA = false;
      bool whjHkbNXsp = false;
      bool yZzArCQTgJ = false;
      bool sqmYPyInWb = false;
      bool riUyLhFDwU = false;
      bool uSuzxeYhSB = false;
      bool XFrJGFtLqm = false;
      bool SYBRxOEBoK = false;
      bool xNWMOaumak = false;
      bool YaUUDlqKqG = false;
      bool mtMJBVRcBh = false;
      bool ZWsIEKhfuf = false;
      bool JGjFOrEfOL = false;
      bool XsKiWDBNKs = false;
      bool ISlsLChMQr = false;
      bool DKPKwfJGtJ = false;
      bool RkNpKfMJlA = false;
      string ihxYAPQcaM;
      string PFjIDqpOFY;
      string ONhYfKOcYB;
      string EKWONKqfCp;
      string aeBFFfoOAP;
      string dXQscVzXro;
      string BnDZHEhVts;
      string AKLOyjLbSz;
      string VAbJXgsckr;
      string KTmNolabyB;
      string ySUGPTLCus;
      string JXEsSALtBZ;
      string LEjBifWyZL;
      string IjcRBCeVtE;
      string VqhrhlOttn;
      string afZYosiSWi;
      string wNbijZtmqQ;
      string UpAxETWqTw;
      string RcDlkbJEbI;
      string TMyKIIPyII;
      if(ihxYAPQcaM == ySUGPTLCus){rbCdSkfbUU = true;}
      else if(ySUGPTLCus == ihxYAPQcaM){SYBRxOEBoK = true;}
      if(PFjIDqpOFY == JXEsSALtBZ){WqzaRSJoyH = true;}
      else if(JXEsSALtBZ == PFjIDqpOFY){xNWMOaumak = true;}
      if(ONhYfKOcYB == LEjBifWyZL){PoKhwIqoow = true;}
      else if(LEjBifWyZL == ONhYfKOcYB){YaUUDlqKqG = true;}
      if(EKWONKqfCp == IjcRBCeVtE){EYiKEoZZTA = true;}
      else if(IjcRBCeVtE == EKWONKqfCp){mtMJBVRcBh = true;}
      if(aeBFFfoOAP == VqhrhlOttn){whjHkbNXsp = true;}
      else if(VqhrhlOttn == aeBFFfoOAP){ZWsIEKhfuf = true;}
      if(dXQscVzXro == afZYosiSWi){yZzArCQTgJ = true;}
      else if(afZYosiSWi == dXQscVzXro){JGjFOrEfOL = true;}
      if(BnDZHEhVts == wNbijZtmqQ){sqmYPyInWb = true;}
      else if(wNbijZtmqQ == BnDZHEhVts){XsKiWDBNKs = true;}
      if(AKLOyjLbSz == UpAxETWqTw){riUyLhFDwU = true;}
      if(VAbJXgsckr == RcDlkbJEbI){uSuzxeYhSB = true;}
      if(KTmNolabyB == TMyKIIPyII){XFrJGFtLqm = true;}
      while(UpAxETWqTw == AKLOyjLbSz){ISlsLChMQr = true;}
      while(RcDlkbJEbI == RcDlkbJEbI){DKPKwfJGtJ = true;}
      while(TMyKIIPyII == TMyKIIPyII){RkNpKfMJlA = true;}
      if(rbCdSkfbUU == true){rbCdSkfbUU = false;}
      if(WqzaRSJoyH == true){WqzaRSJoyH = false;}
      if(PoKhwIqoow == true){PoKhwIqoow = false;}
      if(EYiKEoZZTA == true){EYiKEoZZTA = false;}
      if(whjHkbNXsp == true){whjHkbNXsp = false;}
      if(yZzArCQTgJ == true){yZzArCQTgJ = false;}
      if(sqmYPyInWb == true){sqmYPyInWb = false;}
      if(riUyLhFDwU == true){riUyLhFDwU = false;}
      if(uSuzxeYhSB == true){uSuzxeYhSB = false;}
      if(XFrJGFtLqm == true){XFrJGFtLqm = false;}
      if(SYBRxOEBoK == true){SYBRxOEBoK = false;}
      if(xNWMOaumak == true){xNWMOaumak = false;}
      if(YaUUDlqKqG == true){YaUUDlqKqG = false;}
      if(mtMJBVRcBh == true){mtMJBVRcBh = false;}
      if(ZWsIEKhfuf == true){ZWsIEKhfuf = false;}
      if(JGjFOrEfOL == true){JGjFOrEfOL = false;}
      if(XsKiWDBNKs == true){XsKiWDBNKs = false;}
      if(ISlsLChMQr == true){ISlsLChMQr = false;}
      if(DKPKwfJGtJ == true){DKPKwfJGtJ = false;}
      if(RkNpKfMJlA == true){RkNpKfMJlA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UISDDKQMEE
{ 
  void ldYMCeiEEh()
  { 
      bool YseYfAFgHh = false;
      bool WgmoLPpTCX = false;
      bool ADcLqDMSHB = false;
      bool jqQGhzqhKZ = false;
      bool FmqkJLDLWU = false;
      bool ClOxQUQSgb = false;
      bool nmYGxfQfGM = false;
      bool YIJbSNMqCf = false;
      bool AAumyxbSpN = false;
      bool iXAilROjmc = false;
      bool tXFKwtcleD = false;
      bool HYQBbmqlHA = false;
      bool EypsdAHapA = false;
      bool zcEZkbukpE = false;
      bool UonlFJHzHy = false;
      bool accmXwhLgw = false;
      bool mCwdEeTqPz = false;
      bool rGuCeOJDmT = false;
      bool sHSqZVzRBo = false;
      bool tiDtQSsJha = false;
      string nVNEHqKqRn;
      string KNSQtxCFqY;
      string doYCBjPXZB;
      string uKtVBdmffA;
      string LOFhfDJmuy;
      string AoSfPzwKDX;
      string amRPrzSxOQ;
      string KVZpNOiqWx;
      string ZbbaAGrOFC;
      string gccIZXxoof;
      string kMYemdPbSA;
      string PFmFyyKpPl;
      string HErMihsRQo;
      string RtCqMNDxnV;
      string qQuEmboWJa;
      string NHZDXfUMwE;
      string kxKdiUCurk;
      string uNBsupImYH;
      string sVHpaKTzSg;
      string sqAiksGRVR;
      if(nVNEHqKqRn == kMYemdPbSA){YseYfAFgHh = true;}
      else if(kMYemdPbSA == nVNEHqKqRn){tXFKwtcleD = true;}
      if(KNSQtxCFqY == PFmFyyKpPl){WgmoLPpTCX = true;}
      else if(PFmFyyKpPl == KNSQtxCFqY){HYQBbmqlHA = true;}
      if(doYCBjPXZB == HErMihsRQo){ADcLqDMSHB = true;}
      else if(HErMihsRQo == doYCBjPXZB){EypsdAHapA = true;}
      if(uKtVBdmffA == RtCqMNDxnV){jqQGhzqhKZ = true;}
      else if(RtCqMNDxnV == uKtVBdmffA){zcEZkbukpE = true;}
      if(LOFhfDJmuy == qQuEmboWJa){FmqkJLDLWU = true;}
      else if(qQuEmboWJa == LOFhfDJmuy){UonlFJHzHy = true;}
      if(AoSfPzwKDX == NHZDXfUMwE){ClOxQUQSgb = true;}
      else if(NHZDXfUMwE == AoSfPzwKDX){accmXwhLgw = true;}
      if(amRPrzSxOQ == kxKdiUCurk){nmYGxfQfGM = true;}
      else if(kxKdiUCurk == amRPrzSxOQ){mCwdEeTqPz = true;}
      if(KVZpNOiqWx == uNBsupImYH){YIJbSNMqCf = true;}
      if(ZbbaAGrOFC == sVHpaKTzSg){AAumyxbSpN = true;}
      if(gccIZXxoof == sqAiksGRVR){iXAilROjmc = true;}
      while(uNBsupImYH == KVZpNOiqWx){rGuCeOJDmT = true;}
      while(sVHpaKTzSg == sVHpaKTzSg){sHSqZVzRBo = true;}
      while(sqAiksGRVR == sqAiksGRVR){tiDtQSsJha = true;}
      if(YseYfAFgHh == true){YseYfAFgHh = false;}
      if(WgmoLPpTCX == true){WgmoLPpTCX = false;}
      if(ADcLqDMSHB == true){ADcLqDMSHB = false;}
      if(jqQGhzqhKZ == true){jqQGhzqhKZ = false;}
      if(FmqkJLDLWU == true){FmqkJLDLWU = false;}
      if(ClOxQUQSgb == true){ClOxQUQSgb = false;}
      if(nmYGxfQfGM == true){nmYGxfQfGM = false;}
      if(YIJbSNMqCf == true){YIJbSNMqCf = false;}
      if(AAumyxbSpN == true){AAumyxbSpN = false;}
      if(iXAilROjmc == true){iXAilROjmc = false;}
      if(tXFKwtcleD == true){tXFKwtcleD = false;}
      if(HYQBbmqlHA == true){HYQBbmqlHA = false;}
      if(EypsdAHapA == true){EypsdAHapA = false;}
      if(zcEZkbukpE == true){zcEZkbukpE = false;}
      if(UonlFJHzHy == true){UonlFJHzHy = false;}
      if(accmXwhLgw == true){accmXwhLgw = false;}
      if(mCwdEeTqPz == true){mCwdEeTqPz = false;}
      if(rGuCeOJDmT == true){rGuCeOJDmT = false;}
      if(sHSqZVzRBo == true){sHSqZVzRBo = false;}
      if(tiDtQSsJha == true){tiDtQSsJha = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOVJZGNGQC
{ 
  void PxHccIQNdV()
  { 
      bool mLVHwzacip = false;
      bool uwjBHJiTQB = false;
      bool TqWnntpYmr = false;
      bool dEbyTsTjcm = false;
      bool ZlXwYffRXL = false;
      bool PCwpmwohTB = false;
      bool JBoqMqTlhO = false;
      bool pyqcbgSaOH = false;
      bool NYAbbbHkKW = false;
      bool DkQadXxfjh = false;
      bool LtiIVRKSOG = false;
      bool cOTLmjBNOj = false;
      bool iiaKKEgQzD = false;
      bool jmpfwToqGK = false;
      bool QoVEsoQFms = false;
      bool ViQzycTYyQ = false;
      bool jtTKVpXmOT = false;
      bool uJHETtMVQU = false;
      bool mbcFgAVphT = false;
      bool AQsoZWVKiD = false;
      string yDdsXEEnTo;
      string YIIxdcjKlE;
      string RxzAXqwnIB;
      string GTJSbUorNf;
      string LIgZNtUGKb;
      string MoerqBEcUf;
      string HPeRiFzpVI;
      string nrxFrJPYmd;
      string WpdgoRoQba;
      string QMWgYucOqI;
      string uejBnUqZAh;
      string keoqIQlxcQ;
      string QhNuraUPfw;
      string fBgehrFbsU;
      string ZPQtpkWeXH;
      string JekZqMQoIM;
      string zasDBixKIQ;
      string LJEIqARTEH;
      string EprYmAPGmU;
      string bQTfUzWMrG;
      if(yDdsXEEnTo == uejBnUqZAh){mLVHwzacip = true;}
      else if(uejBnUqZAh == yDdsXEEnTo){LtiIVRKSOG = true;}
      if(YIIxdcjKlE == keoqIQlxcQ){uwjBHJiTQB = true;}
      else if(keoqIQlxcQ == YIIxdcjKlE){cOTLmjBNOj = true;}
      if(RxzAXqwnIB == QhNuraUPfw){TqWnntpYmr = true;}
      else if(QhNuraUPfw == RxzAXqwnIB){iiaKKEgQzD = true;}
      if(GTJSbUorNf == fBgehrFbsU){dEbyTsTjcm = true;}
      else if(fBgehrFbsU == GTJSbUorNf){jmpfwToqGK = true;}
      if(LIgZNtUGKb == ZPQtpkWeXH){ZlXwYffRXL = true;}
      else if(ZPQtpkWeXH == LIgZNtUGKb){QoVEsoQFms = true;}
      if(MoerqBEcUf == JekZqMQoIM){PCwpmwohTB = true;}
      else if(JekZqMQoIM == MoerqBEcUf){ViQzycTYyQ = true;}
      if(HPeRiFzpVI == zasDBixKIQ){JBoqMqTlhO = true;}
      else if(zasDBixKIQ == HPeRiFzpVI){jtTKVpXmOT = true;}
      if(nrxFrJPYmd == LJEIqARTEH){pyqcbgSaOH = true;}
      if(WpdgoRoQba == EprYmAPGmU){NYAbbbHkKW = true;}
      if(QMWgYucOqI == bQTfUzWMrG){DkQadXxfjh = true;}
      while(LJEIqARTEH == nrxFrJPYmd){uJHETtMVQU = true;}
      while(EprYmAPGmU == EprYmAPGmU){mbcFgAVphT = true;}
      while(bQTfUzWMrG == bQTfUzWMrG){AQsoZWVKiD = true;}
      if(mLVHwzacip == true){mLVHwzacip = false;}
      if(uwjBHJiTQB == true){uwjBHJiTQB = false;}
      if(TqWnntpYmr == true){TqWnntpYmr = false;}
      if(dEbyTsTjcm == true){dEbyTsTjcm = false;}
      if(ZlXwYffRXL == true){ZlXwYffRXL = false;}
      if(PCwpmwohTB == true){PCwpmwohTB = false;}
      if(JBoqMqTlhO == true){JBoqMqTlhO = false;}
      if(pyqcbgSaOH == true){pyqcbgSaOH = false;}
      if(NYAbbbHkKW == true){NYAbbbHkKW = false;}
      if(DkQadXxfjh == true){DkQadXxfjh = false;}
      if(LtiIVRKSOG == true){LtiIVRKSOG = false;}
      if(cOTLmjBNOj == true){cOTLmjBNOj = false;}
      if(iiaKKEgQzD == true){iiaKKEgQzD = false;}
      if(jmpfwToqGK == true){jmpfwToqGK = false;}
      if(QoVEsoQFms == true){QoVEsoQFms = false;}
      if(ViQzycTYyQ == true){ViQzycTYyQ = false;}
      if(jtTKVpXmOT == true){jtTKVpXmOT = false;}
      if(uJHETtMVQU == true){uJHETtMVQU = false;}
      if(mbcFgAVphT == true){mbcFgAVphT = false;}
      if(AQsoZWVKiD == true){AQsoZWVKiD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJNRGUTSSZ
{ 
  void YAifnVGhcu()
  { 
      bool QWDHQErmdX = false;
      bool UOhEfsQRqB = false;
      bool kwsrHDVrxS = false;
      bool BjFUlaomKc = false;
      bool TeJPALpXEe = false;
      bool sfdcRUdLzM = false;
      bool izoKWkIMSE = false;
      bool DcGNhGlcqw = false;
      bool NxnSYUGcCQ = false;
      bool xdmysTozsP = false;
      bool CcFzbPZPtL = false;
      bool iATCzlKWlB = false;
      bool dfJBHYoIUN = false;
      bool RmjbtjqopJ = false;
      bool uqhqgwKkyH = false;
      bool JSMqkWSDqC = false;
      bool aQugtwQrIO = false;
      bool tUfbGmxSTL = false;
      bool OEJNDyZrpW = false;
      bool QmymhewAxj = false;
      string roEYkyaYcJ;
      string nliAoVohAq;
      string yuOjtgWtho;
      string urkYhFSEAc;
      string TDdRKZjEwk;
      string gdlhnwaTdD;
      string agpnOwBKRj;
      string CkgXXtRxZU;
      string xSxxHQFCjl;
      string ezawCmNpDN;
      string YYmMhwwOJs;
      string edtJGIirgx;
      string pyafEDKkVk;
      string gatLuXfkOK;
      string UqspHBFQps;
      string DUJFXZyGHe;
      string lLsYMDjhNh;
      string cycVbzFjYD;
      string ysubhLRnnV;
      string ZYcjXJxUdD;
      if(roEYkyaYcJ == YYmMhwwOJs){QWDHQErmdX = true;}
      else if(YYmMhwwOJs == roEYkyaYcJ){CcFzbPZPtL = true;}
      if(nliAoVohAq == edtJGIirgx){UOhEfsQRqB = true;}
      else if(edtJGIirgx == nliAoVohAq){iATCzlKWlB = true;}
      if(yuOjtgWtho == pyafEDKkVk){kwsrHDVrxS = true;}
      else if(pyafEDKkVk == yuOjtgWtho){dfJBHYoIUN = true;}
      if(urkYhFSEAc == gatLuXfkOK){BjFUlaomKc = true;}
      else if(gatLuXfkOK == urkYhFSEAc){RmjbtjqopJ = true;}
      if(TDdRKZjEwk == UqspHBFQps){TeJPALpXEe = true;}
      else if(UqspHBFQps == TDdRKZjEwk){uqhqgwKkyH = true;}
      if(gdlhnwaTdD == DUJFXZyGHe){sfdcRUdLzM = true;}
      else if(DUJFXZyGHe == gdlhnwaTdD){JSMqkWSDqC = true;}
      if(agpnOwBKRj == lLsYMDjhNh){izoKWkIMSE = true;}
      else if(lLsYMDjhNh == agpnOwBKRj){aQugtwQrIO = true;}
      if(CkgXXtRxZU == cycVbzFjYD){DcGNhGlcqw = true;}
      if(xSxxHQFCjl == ysubhLRnnV){NxnSYUGcCQ = true;}
      if(ezawCmNpDN == ZYcjXJxUdD){xdmysTozsP = true;}
      while(cycVbzFjYD == CkgXXtRxZU){tUfbGmxSTL = true;}
      while(ysubhLRnnV == ysubhLRnnV){OEJNDyZrpW = true;}
      while(ZYcjXJxUdD == ZYcjXJxUdD){QmymhewAxj = true;}
      if(QWDHQErmdX == true){QWDHQErmdX = false;}
      if(UOhEfsQRqB == true){UOhEfsQRqB = false;}
      if(kwsrHDVrxS == true){kwsrHDVrxS = false;}
      if(BjFUlaomKc == true){BjFUlaomKc = false;}
      if(TeJPALpXEe == true){TeJPALpXEe = false;}
      if(sfdcRUdLzM == true){sfdcRUdLzM = false;}
      if(izoKWkIMSE == true){izoKWkIMSE = false;}
      if(DcGNhGlcqw == true){DcGNhGlcqw = false;}
      if(NxnSYUGcCQ == true){NxnSYUGcCQ = false;}
      if(xdmysTozsP == true){xdmysTozsP = false;}
      if(CcFzbPZPtL == true){CcFzbPZPtL = false;}
      if(iATCzlKWlB == true){iATCzlKWlB = false;}
      if(dfJBHYoIUN == true){dfJBHYoIUN = false;}
      if(RmjbtjqopJ == true){RmjbtjqopJ = false;}
      if(uqhqgwKkyH == true){uqhqgwKkyH = false;}
      if(JSMqkWSDqC == true){JSMqkWSDqC = false;}
      if(aQugtwQrIO == true){aQugtwQrIO = false;}
      if(tUfbGmxSTL == true){tUfbGmxSTL = false;}
      if(OEJNDyZrpW == true){OEJNDyZrpW = false;}
      if(QmymhewAxj == true){QmymhewAxj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZKECOSQDP
{ 
  void JlkEDuMqLj()
  { 
      bool JkuBbFSVKJ = false;
      bool POkxatrFwB = false;
      bool mJSaOBZswj = false;
      bool WgVViAQIrP = false;
      bool EUVGRPsnpH = false;
      bool ZRdjkASUma = false;
      bool fYYalirONa = false;
      bool cjMfxSnMIz = false;
      bool HkDnJFDljh = false;
      bool gwVRieutTi = false;
      bool WdZPepExmS = false;
      bool MGLnSuUjQg = false;
      bool eGeesfNuxR = false;
      bool WsrZbdLnJT = false;
      bool AFyRVakhyn = false;
      bool JLdlDQztWy = false;
      bool bJAUwTNlLn = false;
      bool igZwfYHMJR = false;
      bool ufwIILOFVK = false;
      bool eQRLrqFdVB = false;
      string kSMkLjMdbb;
      string PmdNOQpMAm;
      string VGJwueGRsm;
      string caqbWomHUa;
      string xDRhiSpTHw;
      string GAbsrdIPog;
      string cukozowBpY;
      string dhrZoSnaNb;
      string nmJwgcyxir;
      string gWRmxCRcis;
      string WnchSXHCEY;
      string pgCNrplnIW;
      string pzRxrGQEbl;
      string ALrTFAKadJ;
      string UwrKCzUDtH;
      string QdUMDWVfpM;
      string GCZRYdoiIr;
      string fKKyBsHHts;
      string lMKUVWpfPh;
      string ddkQCRWZkY;
      if(kSMkLjMdbb == WnchSXHCEY){JkuBbFSVKJ = true;}
      else if(WnchSXHCEY == kSMkLjMdbb){WdZPepExmS = true;}
      if(PmdNOQpMAm == pgCNrplnIW){POkxatrFwB = true;}
      else if(pgCNrplnIW == PmdNOQpMAm){MGLnSuUjQg = true;}
      if(VGJwueGRsm == pzRxrGQEbl){mJSaOBZswj = true;}
      else if(pzRxrGQEbl == VGJwueGRsm){eGeesfNuxR = true;}
      if(caqbWomHUa == ALrTFAKadJ){WgVViAQIrP = true;}
      else if(ALrTFAKadJ == caqbWomHUa){WsrZbdLnJT = true;}
      if(xDRhiSpTHw == UwrKCzUDtH){EUVGRPsnpH = true;}
      else if(UwrKCzUDtH == xDRhiSpTHw){AFyRVakhyn = true;}
      if(GAbsrdIPog == QdUMDWVfpM){ZRdjkASUma = true;}
      else if(QdUMDWVfpM == GAbsrdIPog){JLdlDQztWy = true;}
      if(cukozowBpY == GCZRYdoiIr){fYYalirONa = true;}
      else if(GCZRYdoiIr == cukozowBpY){bJAUwTNlLn = true;}
      if(dhrZoSnaNb == fKKyBsHHts){cjMfxSnMIz = true;}
      if(nmJwgcyxir == lMKUVWpfPh){HkDnJFDljh = true;}
      if(gWRmxCRcis == ddkQCRWZkY){gwVRieutTi = true;}
      while(fKKyBsHHts == dhrZoSnaNb){igZwfYHMJR = true;}
      while(lMKUVWpfPh == lMKUVWpfPh){ufwIILOFVK = true;}
      while(ddkQCRWZkY == ddkQCRWZkY){eQRLrqFdVB = true;}
      if(JkuBbFSVKJ == true){JkuBbFSVKJ = false;}
      if(POkxatrFwB == true){POkxatrFwB = false;}
      if(mJSaOBZswj == true){mJSaOBZswj = false;}
      if(WgVViAQIrP == true){WgVViAQIrP = false;}
      if(EUVGRPsnpH == true){EUVGRPsnpH = false;}
      if(ZRdjkASUma == true){ZRdjkASUma = false;}
      if(fYYalirONa == true){fYYalirONa = false;}
      if(cjMfxSnMIz == true){cjMfxSnMIz = false;}
      if(HkDnJFDljh == true){HkDnJFDljh = false;}
      if(gwVRieutTi == true){gwVRieutTi = false;}
      if(WdZPepExmS == true){WdZPepExmS = false;}
      if(MGLnSuUjQg == true){MGLnSuUjQg = false;}
      if(eGeesfNuxR == true){eGeesfNuxR = false;}
      if(WsrZbdLnJT == true){WsrZbdLnJT = false;}
      if(AFyRVakhyn == true){AFyRVakhyn = false;}
      if(JLdlDQztWy == true){JLdlDQztWy = false;}
      if(bJAUwTNlLn == true){bJAUwTNlLn = false;}
      if(igZwfYHMJR == true){igZwfYHMJR = false;}
      if(ufwIILOFVK == true){ufwIILOFVK = false;}
      if(eQRLrqFdVB == true){eQRLrqFdVB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYNECHGOVM
{ 
  void iXMiUdFQyt()
  { 
      bool wXPHucVrFl = false;
      bool qoqjHxNcYT = false;
      bool IKqHFIOCDG = false;
      bool LETWMDDXed = false;
      bool SuduxgNMPS = false;
      bool PPRlOlfICl = false;
      bool OTozamUUXE = false;
      bool tpxtBMguJY = false;
      bool tCmkpwlhHZ = false;
      bool WtVrPzGdUK = false;
      bool LsnKXZRWjC = false;
      bool FkycrLfDId = false;
      bool AmMygzTFeC = false;
      bool FCazMAObMQ = false;
      bool eOxEUlwrzD = false;
      bool SDUpKYfpdX = false;
      bool FLrhwCJyQq = false;
      bool xEpqzkoHct = false;
      bool CbFbiCgjom = false;
      bool TXyoLSWPIR = false;
      string JquNATYrVn;
      string BpXFHbJMKT;
      string sBDjHwWltr;
      string BTUWYxHqAL;
      string dcohVZFfCd;
      string OUlTLInLFD;
      string wlydlgUAfJ;
      string URLzoQLUNg;
      string pqiQcfhBKQ;
      string JukwOreLuo;
      string FFAsIwImdu;
      string wSyYMFChAG;
      string ySpOzYfPjx;
      string lzYYbkqpHg;
      string WuXPTpxMiJ;
      string owLoplOksj;
      string QsCgJwtZwb;
      string OLZTiDuZtI;
      string bSfZHonjho;
      string VFxXPcrqGX;
      if(JquNATYrVn == FFAsIwImdu){wXPHucVrFl = true;}
      else if(FFAsIwImdu == JquNATYrVn){LsnKXZRWjC = true;}
      if(BpXFHbJMKT == wSyYMFChAG){qoqjHxNcYT = true;}
      else if(wSyYMFChAG == BpXFHbJMKT){FkycrLfDId = true;}
      if(sBDjHwWltr == ySpOzYfPjx){IKqHFIOCDG = true;}
      else if(ySpOzYfPjx == sBDjHwWltr){AmMygzTFeC = true;}
      if(BTUWYxHqAL == lzYYbkqpHg){LETWMDDXed = true;}
      else if(lzYYbkqpHg == BTUWYxHqAL){FCazMAObMQ = true;}
      if(dcohVZFfCd == WuXPTpxMiJ){SuduxgNMPS = true;}
      else if(WuXPTpxMiJ == dcohVZFfCd){eOxEUlwrzD = true;}
      if(OUlTLInLFD == owLoplOksj){PPRlOlfICl = true;}
      else if(owLoplOksj == OUlTLInLFD){SDUpKYfpdX = true;}
      if(wlydlgUAfJ == QsCgJwtZwb){OTozamUUXE = true;}
      else if(QsCgJwtZwb == wlydlgUAfJ){FLrhwCJyQq = true;}
      if(URLzoQLUNg == OLZTiDuZtI){tpxtBMguJY = true;}
      if(pqiQcfhBKQ == bSfZHonjho){tCmkpwlhHZ = true;}
      if(JukwOreLuo == VFxXPcrqGX){WtVrPzGdUK = true;}
      while(OLZTiDuZtI == URLzoQLUNg){xEpqzkoHct = true;}
      while(bSfZHonjho == bSfZHonjho){CbFbiCgjom = true;}
      while(VFxXPcrqGX == VFxXPcrqGX){TXyoLSWPIR = true;}
      if(wXPHucVrFl == true){wXPHucVrFl = false;}
      if(qoqjHxNcYT == true){qoqjHxNcYT = false;}
      if(IKqHFIOCDG == true){IKqHFIOCDG = false;}
      if(LETWMDDXed == true){LETWMDDXed = false;}
      if(SuduxgNMPS == true){SuduxgNMPS = false;}
      if(PPRlOlfICl == true){PPRlOlfICl = false;}
      if(OTozamUUXE == true){OTozamUUXE = false;}
      if(tpxtBMguJY == true){tpxtBMguJY = false;}
      if(tCmkpwlhHZ == true){tCmkpwlhHZ = false;}
      if(WtVrPzGdUK == true){WtVrPzGdUK = false;}
      if(LsnKXZRWjC == true){LsnKXZRWjC = false;}
      if(FkycrLfDId == true){FkycrLfDId = false;}
      if(AmMygzTFeC == true){AmMygzTFeC = false;}
      if(FCazMAObMQ == true){FCazMAObMQ = false;}
      if(eOxEUlwrzD == true){eOxEUlwrzD = false;}
      if(SDUpKYfpdX == true){SDUpKYfpdX = false;}
      if(FLrhwCJyQq == true){FLrhwCJyQq = false;}
      if(xEpqzkoHct == true){xEpqzkoHct = false;}
      if(CbFbiCgjom == true){CbFbiCgjom = false;}
      if(TXyoLSWPIR == true){TXyoLSWPIR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PDLOFKHTWF
{ 
  void zWpNOecMAM()
  { 
      bool NlKNdcpIsV = false;
      bool ueQVPIDVIh = false;
      bool SaKmMwmXGk = false;
      bool UkKgMNIcrX = false;
      bool iZoVnbkpuf = false;
      bool qDJmzlbXBg = false;
      bool pRBHAKTjJB = false;
      bool zZdjyslnyj = false;
      bool LwcatQaXgZ = false;
      bool lkbKhQXgUd = false;
      bool HAgsfQZZnG = false;
      bool zmYQVsoaMj = false;
      bool iwCiPOySBg = false;
      bool UFSTcKPitd = false;
      bool qAjaayLKoo = false;
      bool bwUktLxydR = false;
      bool RGYGktUFnK = false;
      bool dGghsiMaIQ = false;
      bool CmdLFYjgYR = false;
      bool MQEbLjbcpf = false;
      string ZxjKOhBWOu;
      string JTPltpuZyS;
      string KdclptQldI;
      string QnWXHHzHkI;
      string BbXZzbKOgw;
      string PHeFowTyTT;
      string ROrFeVxqel;
      string pmooQiFClN;
      string jBEgsIIQiK;
      string nAmQqljRud;
      string eSjuFbSpnG;
      string pQLFjPJKMV;
      string MfITyoAXxd;
      string ynHIiQRJaQ;
      string oRccUWoggb;
      string cYEYQyKPxQ;
      string burJHCJCWS;
      string yziwftDfza;
      string ASqVBZihrj;
      string GBMKotZSUS;
      if(ZxjKOhBWOu == eSjuFbSpnG){NlKNdcpIsV = true;}
      else if(eSjuFbSpnG == ZxjKOhBWOu){HAgsfQZZnG = true;}
      if(JTPltpuZyS == pQLFjPJKMV){ueQVPIDVIh = true;}
      else if(pQLFjPJKMV == JTPltpuZyS){zmYQVsoaMj = true;}
      if(KdclptQldI == MfITyoAXxd){SaKmMwmXGk = true;}
      else if(MfITyoAXxd == KdclptQldI){iwCiPOySBg = true;}
      if(QnWXHHzHkI == ynHIiQRJaQ){UkKgMNIcrX = true;}
      else if(ynHIiQRJaQ == QnWXHHzHkI){UFSTcKPitd = true;}
      if(BbXZzbKOgw == oRccUWoggb){iZoVnbkpuf = true;}
      else if(oRccUWoggb == BbXZzbKOgw){qAjaayLKoo = true;}
      if(PHeFowTyTT == cYEYQyKPxQ){qDJmzlbXBg = true;}
      else if(cYEYQyKPxQ == PHeFowTyTT){bwUktLxydR = true;}
      if(ROrFeVxqel == burJHCJCWS){pRBHAKTjJB = true;}
      else if(burJHCJCWS == ROrFeVxqel){RGYGktUFnK = true;}
      if(pmooQiFClN == yziwftDfza){zZdjyslnyj = true;}
      if(jBEgsIIQiK == ASqVBZihrj){LwcatQaXgZ = true;}
      if(nAmQqljRud == GBMKotZSUS){lkbKhQXgUd = true;}
      while(yziwftDfza == pmooQiFClN){dGghsiMaIQ = true;}
      while(ASqVBZihrj == ASqVBZihrj){CmdLFYjgYR = true;}
      while(GBMKotZSUS == GBMKotZSUS){MQEbLjbcpf = true;}
      if(NlKNdcpIsV == true){NlKNdcpIsV = false;}
      if(ueQVPIDVIh == true){ueQVPIDVIh = false;}
      if(SaKmMwmXGk == true){SaKmMwmXGk = false;}
      if(UkKgMNIcrX == true){UkKgMNIcrX = false;}
      if(iZoVnbkpuf == true){iZoVnbkpuf = false;}
      if(qDJmzlbXBg == true){qDJmzlbXBg = false;}
      if(pRBHAKTjJB == true){pRBHAKTjJB = false;}
      if(zZdjyslnyj == true){zZdjyslnyj = false;}
      if(LwcatQaXgZ == true){LwcatQaXgZ = false;}
      if(lkbKhQXgUd == true){lkbKhQXgUd = false;}
      if(HAgsfQZZnG == true){HAgsfQZZnG = false;}
      if(zmYQVsoaMj == true){zmYQVsoaMj = false;}
      if(iwCiPOySBg == true){iwCiPOySBg = false;}
      if(UFSTcKPitd == true){UFSTcKPitd = false;}
      if(qAjaayLKoo == true){qAjaayLKoo = false;}
      if(bwUktLxydR == true){bwUktLxydR = false;}
      if(RGYGktUFnK == true){RGYGktUFnK = false;}
      if(dGghsiMaIQ == true){dGghsiMaIQ = false;}
      if(CmdLFYjgYR == true){CmdLFYjgYR = false;}
      if(MQEbLjbcpf == true){MQEbLjbcpf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWPPTJOZCW
{ 
  void YLKosLbAaJ()
  { 
      bool xagwwKnzHt = false;
      bool HJzRIASWYx = false;
      bool nYMQiTLnAe = false;
      bool goBsoCpYxW = false;
      bool rUSJQQzNzN = false;
      bool FukURXNQMb = false;
      bool yzzcNRHFcF = false;
      bool JtYBETFDzR = false;
      bool TyolZkEgaQ = false;
      bool oZLVYrUpuz = false;
      bool JsjsDLViQy = false;
      bool RKQuIzKMCc = false;
      bool NZeMQjhDcL = false;
      bool yOHAIZNuhN = false;
      bool OUQbydJQMY = false;
      bool hHmSkiOXcT = false;
      bool cSFEACCPlh = false;
      bool lOdoNrJCNm = false;
      bool aRpEcpboOZ = false;
      bool LoSOkwOLbu = false;
      string tccdPIcrHf;
      string LlBEyXDZpq;
      string cKfpDDjdsE;
      string mVNpmftReC;
      string cdPTRyFbGm;
      string CKMFwjxmaL;
      string XzzCrpYKQS;
      string dktmOytMYF;
      string yIXFCcIHtD;
      string iGqTddeNaa;
      string YtLnJQPZqx;
      string okOVNPbszP;
      string gQQMjWsaIj;
      string SgkxfDxjuk;
      string MiQwNxrVFO;
      string ClNKsHdyEm;
      string XnQGdHzQoJ;
      string SqxNDyATzl;
      string dWUthgTaEY;
      string ZyeINXRKRF;
      if(tccdPIcrHf == YtLnJQPZqx){xagwwKnzHt = true;}
      else if(YtLnJQPZqx == tccdPIcrHf){JsjsDLViQy = true;}
      if(LlBEyXDZpq == okOVNPbszP){HJzRIASWYx = true;}
      else if(okOVNPbszP == LlBEyXDZpq){RKQuIzKMCc = true;}
      if(cKfpDDjdsE == gQQMjWsaIj){nYMQiTLnAe = true;}
      else if(gQQMjWsaIj == cKfpDDjdsE){NZeMQjhDcL = true;}
      if(mVNpmftReC == SgkxfDxjuk){goBsoCpYxW = true;}
      else if(SgkxfDxjuk == mVNpmftReC){yOHAIZNuhN = true;}
      if(cdPTRyFbGm == MiQwNxrVFO){rUSJQQzNzN = true;}
      else if(MiQwNxrVFO == cdPTRyFbGm){OUQbydJQMY = true;}
      if(CKMFwjxmaL == ClNKsHdyEm){FukURXNQMb = true;}
      else if(ClNKsHdyEm == CKMFwjxmaL){hHmSkiOXcT = true;}
      if(XzzCrpYKQS == XnQGdHzQoJ){yzzcNRHFcF = true;}
      else if(XnQGdHzQoJ == XzzCrpYKQS){cSFEACCPlh = true;}
      if(dktmOytMYF == SqxNDyATzl){JtYBETFDzR = true;}
      if(yIXFCcIHtD == dWUthgTaEY){TyolZkEgaQ = true;}
      if(iGqTddeNaa == ZyeINXRKRF){oZLVYrUpuz = true;}
      while(SqxNDyATzl == dktmOytMYF){lOdoNrJCNm = true;}
      while(dWUthgTaEY == dWUthgTaEY){aRpEcpboOZ = true;}
      while(ZyeINXRKRF == ZyeINXRKRF){LoSOkwOLbu = true;}
      if(xagwwKnzHt == true){xagwwKnzHt = false;}
      if(HJzRIASWYx == true){HJzRIASWYx = false;}
      if(nYMQiTLnAe == true){nYMQiTLnAe = false;}
      if(goBsoCpYxW == true){goBsoCpYxW = false;}
      if(rUSJQQzNzN == true){rUSJQQzNzN = false;}
      if(FukURXNQMb == true){FukURXNQMb = false;}
      if(yzzcNRHFcF == true){yzzcNRHFcF = false;}
      if(JtYBETFDzR == true){JtYBETFDzR = false;}
      if(TyolZkEgaQ == true){TyolZkEgaQ = false;}
      if(oZLVYrUpuz == true){oZLVYrUpuz = false;}
      if(JsjsDLViQy == true){JsjsDLViQy = false;}
      if(RKQuIzKMCc == true){RKQuIzKMCc = false;}
      if(NZeMQjhDcL == true){NZeMQjhDcL = false;}
      if(yOHAIZNuhN == true){yOHAIZNuhN = false;}
      if(OUQbydJQMY == true){OUQbydJQMY = false;}
      if(hHmSkiOXcT == true){hHmSkiOXcT = false;}
      if(cSFEACCPlh == true){cSFEACCPlh = false;}
      if(lOdoNrJCNm == true){lOdoNrJCNm = false;}
      if(aRpEcpboOZ == true){aRpEcpboOZ = false;}
      if(LoSOkwOLbu == true){LoSOkwOLbu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QNAXSIZFQO
{ 
  void MGkuTeATgF()
  { 
      bool iHDZSrJkVc = false;
      bool pPnIqFPIDm = false;
      bool QUVdjDOyTb = false;
      bool ACuGsDOinr = false;
      bool TuzawWjgAX = false;
      bool RiFaFNlZoP = false;
      bool dKRsbnUgOn = false;
      bool qfTKTVVugN = false;
      bool SgxuJRxTAe = false;
      bool RnsYOIcGzI = false;
      bool BCRMflOtHj = false;
      bool rpsbwwNViK = false;
      bool qAgjVDluwK = false;
      bool rPwYMPOjOX = false;
      bool CCMQmauRbR = false;
      bool uGWnRAVhpc = false;
      bool ATywqctTPf = false;
      bool gcHLHnnPxu = false;
      bool IUSdPksHHL = false;
      bool sgslWiEPZJ = false;
      string JkqaGERysE;
      string lbwWbJdYpi;
      string hwuucznWTf;
      string CJBitHfUmb;
      string XRwyyhZnIa;
      string TQhhKNowyH;
      string QteMCcZMbU;
      string cIlOLPzxwt;
      string YAOrMkbSYg;
      string RiWeLcljwV;
      string HMLnxKeTWt;
      string NrADhQflAQ;
      string AGnuCtlGCh;
      string cPBZmLnauC;
      string GIweSZiTwu;
      string xAifVAYPkC;
      string XYQnQxpaPW;
      string bEqxJrKIbc;
      string LRJHkcgVEl;
      string lXprdhqINV;
      if(JkqaGERysE == HMLnxKeTWt){iHDZSrJkVc = true;}
      else if(HMLnxKeTWt == JkqaGERysE){BCRMflOtHj = true;}
      if(lbwWbJdYpi == NrADhQflAQ){pPnIqFPIDm = true;}
      else if(NrADhQflAQ == lbwWbJdYpi){rpsbwwNViK = true;}
      if(hwuucznWTf == AGnuCtlGCh){QUVdjDOyTb = true;}
      else if(AGnuCtlGCh == hwuucznWTf){qAgjVDluwK = true;}
      if(CJBitHfUmb == cPBZmLnauC){ACuGsDOinr = true;}
      else if(cPBZmLnauC == CJBitHfUmb){rPwYMPOjOX = true;}
      if(XRwyyhZnIa == GIweSZiTwu){TuzawWjgAX = true;}
      else if(GIweSZiTwu == XRwyyhZnIa){CCMQmauRbR = true;}
      if(TQhhKNowyH == xAifVAYPkC){RiFaFNlZoP = true;}
      else if(xAifVAYPkC == TQhhKNowyH){uGWnRAVhpc = true;}
      if(QteMCcZMbU == XYQnQxpaPW){dKRsbnUgOn = true;}
      else if(XYQnQxpaPW == QteMCcZMbU){ATywqctTPf = true;}
      if(cIlOLPzxwt == bEqxJrKIbc){qfTKTVVugN = true;}
      if(YAOrMkbSYg == LRJHkcgVEl){SgxuJRxTAe = true;}
      if(RiWeLcljwV == lXprdhqINV){RnsYOIcGzI = true;}
      while(bEqxJrKIbc == cIlOLPzxwt){gcHLHnnPxu = true;}
      while(LRJHkcgVEl == LRJHkcgVEl){IUSdPksHHL = true;}
      while(lXprdhqINV == lXprdhqINV){sgslWiEPZJ = true;}
      if(iHDZSrJkVc == true){iHDZSrJkVc = false;}
      if(pPnIqFPIDm == true){pPnIqFPIDm = false;}
      if(QUVdjDOyTb == true){QUVdjDOyTb = false;}
      if(ACuGsDOinr == true){ACuGsDOinr = false;}
      if(TuzawWjgAX == true){TuzawWjgAX = false;}
      if(RiFaFNlZoP == true){RiFaFNlZoP = false;}
      if(dKRsbnUgOn == true){dKRsbnUgOn = false;}
      if(qfTKTVVugN == true){qfTKTVVugN = false;}
      if(SgxuJRxTAe == true){SgxuJRxTAe = false;}
      if(RnsYOIcGzI == true){RnsYOIcGzI = false;}
      if(BCRMflOtHj == true){BCRMflOtHj = false;}
      if(rpsbwwNViK == true){rpsbwwNViK = false;}
      if(qAgjVDluwK == true){qAgjVDluwK = false;}
      if(rPwYMPOjOX == true){rPwYMPOjOX = false;}
      if(CCMQmauRbR == true){CCMQmauRbR = false;}
      if(uGWnRAVhpc == true){uGWnRAVhpc = false;}
      if(ATywqctTPf == true){ATywqctTPf = false;}
      if(gcHLHnnPxu == true){gcHLHnnPxu = false;}
      if(IUSdPksHHL == true){IUSdPksHHL = false;}
      if(sgslWiEPZJ == true){sgslWiEPZJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYVXOBVXCF
{ 
  void gAKrLLuqFD()
  { 
      bool dGQCHMoRfa = false;
      bool aqutIunOfS = false;
      bool ZZOjxXJkMf = false;
      bool ssCYXzMQFq = false;
      bool bDnwoxznTE = false;
      bool BUazUDqfFj = false;
      bool DEFAhhnVWJ = false;
      bool hWJoqVlStz = false;
      bool YUQIdXSDET = false;
      bool IfLVnXymNH = false;
      bool IcRKVdLlIy = false;
      bool RYlFKhmxVK = false;
      bool OkRDBCLmAT = false;
      bool XyEmpwDFlz = false;
      bool LgtGBjtFKG = false;
      bool jBRDrXLNJT = false;
      bool SXkoZTTyOO = false;
      bool dhKVzhpKCR = false;
      bool HGctiWgBtS = false;
      bool jpwSgmuFfg = false;
      string bLUPdYRjBy;
      string CyZCUAWhHq;
      string zNziJFKqYV;
      string PjUrCDsPzQ;
      string DUwFMySZoT;
      string bAGhiOLkFX;
      string NZLfiSdhzR;
      string GGiqmdRsWL;
      string lkCFtOclIn;
      string qHKaDdJQWt;
      string TkaWMUQPtF;
      string xROslcXGkT;
      string prYKayuImJ;
      string UAWbrAKerY;
      string yMqDqYsRnZ;
      string FDeCEbMPwO;
      string YIbkjwumAk;
      string SrNMVcAVTB;
      string FdTNEQVUXQ;
      string nticzpjGSt;
      if(bLUPdYRjBy == TkaWMUQPtF){dGQCHMoRfa = true;}
      else if(TkaWMUQPtF == bLUPdYRjBy){IcRKVdLlIy = true;}
      if(CyZCUAWhHq == xROslcXGkT){aqutIunOfS = true;}
      else if(xROslcXGkT == CyZCUAWhHq){RYlFKhmxVK = true;}
      if(zNziJFKqYV == prYKayuImJ){ZZOjxXJkMf = true;}
      else if(prYKayuImJ == zNziJFKqYV){OkRDBCLmAT = true;}
      if(PjUrCDsPzQ == UAWbrAKerY){ssCYXzMQFq = true;}
      else if(UAWbrAKerY == PjUrCDsPzQ){XyEmpwDFlz = true;}
      if(DUwFMySZoT == yMqDqYsRnZ){bDnwoxznTE = true;}
      else if(yMqDqYsRnZ == DUwFMySZoT){LgtGBjtFKG = true;}
      if(bAGhiOLkFX == FDeCEbMPwO){BUazUDqfFj = true;}
      else if(FDeCEbMPwO == bAGhiOLkFX){jBRDrXLNJT = true;}
      if(NZLfiSdhzR == YIbkjwumAk){DEFAhhnVWJ = true;}
      else if(YIbkjwumAk == NZLfiSdhzR){SXkoZTTyOO = true;}
      if(GGiqmdRsWL == SrNMVcAVTB){hWJoqVlStz = true;}
      if(lkCFtOclIn == FdTNEQVUXQ){YUQIdXSDET = true;}
      if(qHKaDdJQWt == nticzpjGSt){IfLVnXymNH = true;}
      while(SrNMVcAVTB == GGiqmdRsWL){dhKVzhpKCR = true;}
      while(FdTNEQVUXQ == FdTNEQVUXQ){HGctiWgBtS = true;}
      while(nticzpjGSt == nticzpjGSt){jpwSgmuFfg = true;}
      if(dGQCHMoRfa == true){dGQCHMoRfa = false;}
      if(aqutIunOfS == true){aqutIunOfS = false;}
      if(ZZOjxXJkMf == true){ZZOjxXJkMf = false;}
      if(ssCYXzMQFq == true){ssCYXzMQFq = false;}
      if(bDnwoxznTE == true){bDnwoxznTE = false;}
      if(BUazUDqfFj == true){BUazUDqfFj = false;}
      if(DEFAhhnVWJ == true){DEFAhhnVWJ = false;}
      if(hWJoqVlStz == true){hWJoqVlStz = false;}
      if(YUQIdXSDET == true){YUQIdXSDET = false;}
      if(IfLVnXymNH == true){IfLVnXymNH = false;}
      if(IcRKVdLlIy == true){IcRKVdLlIy = false;}
      if(RYlFKhmxVK == true){RYlFKhmxVK = false;}
      if(OkRDBCLmAT == true){OkRDBCLmAT = false;}
      if(XyEmpwDFlz == true){XyEmpwDFlz = false;}
      if(LgtGBjtFKG == true){LgtGBjtFKG = false;}
      if(jBRDrXLNJT == true){jBRDrXLNJT = false;}
      if(SXkoZTTyOO == true){SXkoZTTyOO = false;}
      if(dhKVzhpKCR == true){dhKVzhpKCR = false;}
      if(HGctiWgBtS == true){HGctiWgBtS = false;}
      if(jpwSgmuFfg == true){jpwSgmuFfg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUYHEPXKLK
{ 
  void okGoTxEzDj()
  { 
      bool caTzkcJKJN = false;
      bool QzMeQTjzVc = false;
      bool VSVytcarZK = false;
      bool yVDkwZGqhI = false;
      bool fuKHLCZBri = false;
      bool enuUXKEVFI = false;
      bool BQkyOtubiq = false;
      bool MrQNxZINmr = false;
      bool CZzqfJahMk = false;
      bool UklYGOKLsQ = false;
      bool GyRBVlWhXx = false;
      bool CpiNGbRsRE = false;
      bool TNOxVbGrGh = false;
      bool PwUVkDHyVs = false;
      bool mrKPieCYSe = false;
      bool xRtnwsjUfs = false;
      bool fdbohFUMbC = false;
      bool USXYRbDzNq = false;
      bool ZhZbkxCgYr = false;
      bool TmSbNIQUgc = false;
      string oRJhNrAiqW;
      string ouuYtwizoG;
      string WJXnbrUYsE;
      string CCfsazAIQV;
      string GfBUceVsqg;
      string pxHdJfsVFV;
      string XbpmUlOBxu;
      string wZiTAqIDKx;
      string WbgLNEtCjt;
      string FdDuxdpNzp;
      string QTuujQOncS;
      string XpLHzwtdZQ;
      string qMRCpSVmVV;
      string BtDTgCflbw;
      string pGYQWPRuwB;
      string jLniyEBrFR;
      string taSHRclqaw;
      string PHCcZkmBfZ;
      string AaqTkoGTUc;
      string BmgJCOmRyt;
      if(oRJhNrAiqW == QTuujQOncS){caTzkcJKJN = true;}
      else if(QTuujQOncS == oRJhNrAiqW){GyRBVlWhXx = true;}
      if(ouuYtwizoG == XpLHzwtdZQ){QzMeQTjzVc = true;}
      else if(XpLHzwtdZQ == ouuYtwizoG){CpiNGbRsRE = true;}
      if(WJXnbrUYsE == qMRCpSVmVV){VSVytcarZK = true;}
      else if(qMRCpSVmVV == WJXnbrUYsE){TNOxVbGrGh = true;}
      if(CCfsazAIQV == BtDTgCflbw){yVDkwZGqhI = true;}
      else if(BtDTgCflbw == CCfsazAIQV){PwUVkDHyVs = true;}
      if(GfBUceVsqg == pGYQWPRuwB){fuKHLCZBri = true;}
      else if(pGYQWPRuwB == GfBUceVsqg){mrKPieCYSe = true;}
      if(pxHdJfsVFV == jLniyEBrFR){enuUXKEVFI = true;}
      else if(jLniyEBrFR == pxHdJfsVFV){xRtnwsjUfs = true;}
      if(XbpmUlOBxu == taSHRclqaw){BQkyOtubiq = true;}
      else if(taSHRclqaw == XbpmUlOBxu){fdbohFUMbC = true;}
      if(wZiTAqIDKx == PHCcZkmBfZ){MrQNxZINmr = true;}
      if(WbgLNEtCjt == AaqTkoGTUc){CZzqfJahMk = true;}
      if(FdDuxdpNzp == BmgJCOmRyt){UklYGOKLsQ = true;}
      while(PHCcZkmBfZ == wZiTAqIDKx){USXYRbDzNq = true;}
      while(AaqTkoGTUc == AaqTkoGTUc){ZhZbkxCgYr = true;}
      while(BmgJCOmRyt == BmgJCOmRyt){TmSbNIQUgc = true;}
      if(caTzkcJKJN == true){caTzkcJKJN = false;}
      if(QzMeQTjzVc == true){QzMeQTjzVc = false;}
      if(VSVytcarZK == true){VSVytcarZK = false;}
      if(yVDkwZGqhI == true){yVDkwZGqhI = false;}
      if(fuKHLCZBri == true){fuKHLCZBri = false;}
      if(enuUXKEVFI == true){enuUXKEVFI = false;}
      if(BQkyOtubiq == true){BQkyOtubiq = false;}
      if(MrQNxZINmr == true){MrQNxZINmr = false;}
      if(CZzqfJahMk == true){CZzqfJahMk = false;}
      if(UklYGOKLsQ == true){UklYGOKLsQ = false;}
      if(GyRBVlWhXx == true){GyRBVlWhXx = false;}
      if(CpiNGbRsRE == true){CpiNGbRsRE = false;}
      if(TNOxVbGrGh == true){TNOxVbGrGh = false;}
      if(PwUVkDHyVs == true){PwUVkDHyVs = false;}
      if(mrKPieCYSe == true){mrKPieCYSe = false;}
      if(xRtnwsjUfs == true){xRtnwsjUfs = false;}
      if(fdbohFUMbC == true){fdbohFUMbC = false;}
      if(USXYRbDzNq == true){USXYRbDzNq = false;}
      if(ZhZbkxCgYr == true){ZhZbkxCgYr = false;}
      if(TmSbNIQUgc == true){TmSbNIQUgc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVCMLLBVGR
{ 
  void OwadocNJae()
  { 
      bool ZRKqgdRufu = false;
      bool pUcFNKBzJD = false;
      bool auzmwPXbyW = false;
      bool hKzUjFbzGr = false;
      bool YFrwpSwyFx = false;
      bool jVcdOeSWtQ = false;
      bool FowJNfVIVH = false;
      bool hBrQdVCCwd = false;
      bool TZWBlLgUGF = false;
      bool mFEoliIihK = false;
      bool wmcxOhcLzr = false;
      bool bQZQxfSuWB = false;
      bool yBCPUcwDdu = false;
      bool MTTlgfwYlD = false;
      bool hUUNdWenqG = false;
      bool QMLgLukMcl = false;
      bool kZhEeHwniR = false;
      bool isJSTcfoly = false;
      bool xILXdAImal = false;
      bool uiwzSImQhV = false;
      string OEChiAjnEl;
      string BQnWfqTBsf;
      string IPjWUETtNW;
      string PlXzwyUhgH;
      string unxwXwBpDo;
      string BchtUyUfNd;
      string goZhWOsnZh;
      string WlTkjUSmzX;
      string DdqYUlEcdx;
      string coTCaGOOZI;
      string DMPVSPJwKA;
      string fhfoaDyBMk;
      string KPKbFgRRKd;
      string FDNpUpNUFF;
      string cHScRtIeaW;
      string HNCnymCmQl;
      string xqlfubUpUj;
      string pcuGHCxgJK;
      string XmpmWqBYqg;
      string nZESIkUlho;
      if(OEChiAjnEl == DMPVSPJwKA){ZRKqgdRufu = true;}
      else if(DMPVSPJwKA == OEChiAjnEl){wmcxOhcLzr = true;}
      if(BQnWfqTBsf == fhfoaDyBMk){pUcFNKBzJD = true;}
      else if(fhfoaDyBMk == BQnWfqTBsf){bQZQxfSuWB = true;}
      if(IPjWUETtNW == KPKbFgRRKd){auzmwPXbyW = true;}
      else if(KPKbFgRRKd == IPjWUETtNW){yBCPUcwDdu = true;}
      if(PlXzwyUhgH == FDNpUpNUFF){hKzUjFbzGr = true;}
      else if(FDNpUpNUFF == PlXzwyUhgH){MTTlgfwYlD = true;}
      if(unxwXwBpDo == cHScRtIeaW){YFrwpSwyFx = true;}
      else if(cHScRtIeaW == unxwXwBpDo){hUUNdWenqG = true;}
      if(BchtUyUfNd == HNCnymCmQl){jVcdOeSWtQ = true;}
      else if(HNCnymCmQl == BchtUyUfNd){QMLgLukMcl = true;}
      if(goZhWOsnZh == xqlfubUpUj){FowJNfVIVH = true;}
      else if(xqlfubUpUj == goZhWOsnZh){kZhEeHwniR = true;}
      if(WlTkjUSmzX == pcuGHCxgJK){hBrQdVCCwd = true;}
      if(DdqYUlEcdx == XmpmWqBYqg){TZWBlLgUGF = true;}
      if(coTCaGOOZI == nZESIkUlho){mFEoliIihK = true;}
      while(pcuGHCxgJK == WlTkjUSmzX){isJSTcfoly = true;}
      while(XmpmWqBYqg == XmpmWqBYqg){xILXdAImal = true;}
      while(nZESIkUlho == nZESIkUlho){uiwzSImQhV = true;}
      if(ZRKqgdRufu == true){ZRKqgdRufu = false;}
      if(pUcFNKBzJD == true){pUcFNKBzJD = false;}
      if(auzmwPXbyW == true){auzmwPXbyW = false;}
      if(hKzUjFbzGr == true){hKzUjFbzGr = false;}
      if(YFrwpSwyFx == true){YFrwpSwyFx = false;}
      if(jVcdOeSWtQ == true){jVcdOeSWtQ = false;}
      if(FowJNfVIVH == true){FowJNfVIVH = false;}
      if(hBrQdVCCwd == true){hBrQdVCCwd = false;}
      if(TZWBlLgUGF == true){TZWBlLgUGF = false;}
      if(mFEoliIihK == true){mFEoliIihK = false;}
      if(wmcxOhcLzr == true){wmcxOhcLzr = false;}
      if(bQZQxfSuWB == true){bQZQxfSuWB = false;}
      if(yBCPUcwDdu == true){yBCPUcwDdu = false;}
      if(MTTlgfwYlD == true){MTTlgfwYlD = false;}
      if(hUUNdWenqG == true){hUUNdWenqG = false;}
      if(QMLgLukMcl == true){QMLgLukMcl = false;}
      if(kZhEeHwniR == true){kZhEeHwniR = false;}
      if(isJSTcfoly == true){isJSTcfoly = false;}
      if(xILXdAImal == true){xILXdAImal = false;}
      if(uiwzSImQhV == true){uiwzSImQhV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTGHVIINNO
{ 
  void tUxClhQkjB()
  { 
      bool RDLlqfTZtp = false;
      bool cOnDGblAYf = false;
      bool sVMFKzGAia = false;
      bool PnNgDwEEVB = false;
      bool oLMqnyiNgy = false;
      bool JoIwswpFaq = false;
      bool ZTpSanAGAJ = false;
      bool XhdXqgJUQL = false;
      bool QrSjQZfRnH = false;
      bool GydeaVUsQA = false;
      bool ycNWabLkFL = false;
      bool lUnPagAGCB = false;
      bool IhRsDYEzwU = false;
      bool MQEQNmeuJn = false;
      bool NuMcUlJODs = false;
      bool VOpOqPKUTB = false;
      bool XMnjzVPXBm = false;
      bool CExOmNVoXR = false;
      bool PouDzxZpZx = false;
      bool cJbIPBGccz = false;
      string KpxolCfEHg;
      string aXMCsCGRkZ;
      string bdCoaSZhYV;
      string fZgiyhfkSs;
      string SVxPGAozAa;
      string LcgALfmIOS;
      string cxflABqdEK;
      string VVzqHGfmiZ;
      string cagyJDrgWR;
      string uXWzPUoLOE;
      string JLupEpcorF;
      string zAZnoCPhbx;
      string IKHlPyyAal;
      string QUXdQRfqsS;
      string ZDnQRtyiJN;
      string EHiRuzEIZF;
      string rcNGoebuWX;
      string WYnJXFVpUV;
      string zPpNgIkGhR;
      string NWRmawphbm;
      if(KpxolCfEHg == JLupEpcorF){RDLlqfTZtp = true;}
      else if(JLupEpcorF == KpxolCfEHg){ycNWabLkFL = true;}
      if(aXMCsCGRkZ == zAZnoCPhbx){cOnDGblAYf = true;}
      else if(zAZnoCPhbx == aXMCsCGRkZ){lUnPagAGCB = true;}
      if(bdCoaSZhYV == IKHlPyyAal){sVMFKzGAia = true;}
      else if(IKHlPyyAal == bdCoaSZhYV){IhRsDYEzwU = true;}
      if(fZgiyhfkSs == QUXdQRfqsS){PnNgDwEEVB = true;}
      else if(QUXdQRfqsS == fZgiyhfkSs){MQEQNmeuJn = true;}
      if(SVxPGAozAa == ZDnQRtyiJN){oLMqnyiNgy = true;}
      else if(ZDnQRtyiJN == SVxPGAozAa){NuMcUlJODs = true;}
      if(LcgALfmIOS == EHiRuzEIZF){JoIwswpFaq = true;}
      else if(EHiRuzEIZF == LcgALfmIOS){VOpOqPKUTB = true;}
      if(cxflABqdEK == rcNGoebuWX){ZTpSanAGAJ = true;}
      else if(rcNGoebuWX == cxflABqdEK){XMnjzVPXBm = true;}
      if(VVzqHGfmiZ == WYnJXFVpUV){XhdXqgJUQL = true;}
      if(cagyJDrgWR == zPpNgIkGhR){QrSjQZfRnH = true;}
      if(uXWzPUoLOE == NWRmawphbm){GydeaVUsQA = true;}
      while(WYnJXFVpUV == VVzqHGfmiZ){CExOmNVoXR = true;}
      while(zPpNgIkGhR == zPpNgIkGhR){PouDzxZpZx = true;}
      while(NWRmawphbm == NWRmawphbm){cJbIPBGccz = true;}
      if(RDLlqfTZtp == true){RDLlqfTZtp = false;}
      if(cOnDGblAYf == true){cOnDGblAYf = false;}
      if(sVMFKzGAia == true){sVMFKzGAia = false;}
      if(PnNgDwEEVB == true){PnNgDwEEVB = false;}
      if(oLMqnyiNgy == true){oLMqnyiNgy = false;}
      if(JoIwswpFaq == true){JoIwswpFaq = false;}
      if(ZTpSanAGAJ == true){ZTpSanAGAJ = false;}
      if(XhdXqgJUQL == true){XhdXqgJUQL = false;}
      if(QrSjQZfRnH == true){QrSjQZfRnH = false;}
      if(GydeaVUsQA == true){GydeaVUsQA = false;}
      if(ycNWabLkFL == true){ycNWabLkFL = false;}
      if(lUnPagAGCB == true){lUnPagAGCB = false;}
      if(IhRsDYEzwU == true){IhRsDYEzwU = false;}
      if(MQEQNmeuJn == true){MQEQNmeuJn = false;}
      if(NuMcUlJODs == true){NuMcUlJODs = false;}
      if(VOpOqPKUTB == true){VOpOqPKUTB = false;}
      if(XMnjzVPXBm == true){XMnjzVPXBm = false;}
      if(CExOmNVoXR == true){CExOmNVoXR = false;}
      if(PouDzxZpZx == true){PouDzxZpZx = false;}
      if(cJbIPBGccz == true){cJbIPBGccz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KFGTLMKGQA
{ 
  void SsuwJKtMRQ()
  { 
      bool SFSzuBdHbQ = false;
      bool SJUEcgWSOW = false;
      bool xsdnpPdXdw = false;
      bool rhMAPUtLiw = false;
      bool psLILLfhuc = false;
      bool PdSeHYadIe = false;
      bool XFcfYjwUoI = false;
      bool mLiRfDhVbe = false;
      bool jucAgNPgrp = false;
      bool sPCDYkQfja = false;
      bool OKslpDuAzE = false;
      bool qFCcubbcyK = false;
      bool UOcyOWIeru = false;
      bool mCkAQYCqJd = false;
      bool SOhnynNZIx = false;
      bool ImgYGzhtWS = false;
      bool tPHDQoTBMV = false;
      bool YkSUrFgnza = false;
      bool JiVulAULtQ = false;
      bool qHTpiCGdWJ = false;
      string nwXzJMMNff;
      string dBnnqZDWDN;
      string ZIBVUiHdct;
      string GOWEebwrnJ;
      string phYnCTMtjP;
      string BkhAbetCdZ;
      string FhkkYOeiJP;
      string cKhtXqjNSA;
      string VMsNsVgWcz;
      string gsNNEHxmOm;
      string odkUlpCmcj;
      string ugjcDroWqD;
      string hIGJhiwUpQ;
      string twzeLrbYaD;
      string TssrEAJjKL;
      string RZuLFgXalC;
      string sgxMpygERL;
      string QQwninONFh;
      string ZMKdyTBnZd;
      string UAlXKlwgBF;
      if(nwXzJMMNff == odkUlpCmcj){SFSzuBdHbQ = true;}
      else if(odkUlpCmcj == nwXzJMMNff){OKslpDuAzE = true;}
      if(dBnnqZDWDN == ugjcDroWqD){SJUEcgWSOW = true;}
      else if(ugjcDroWqD == dBnnqZDWDN){qFCcubbcyK = true;}
      if(ZIBVUiHdct == hIGJhiwUpQ){xsdnpPdXdw = true;}
      else if(hIGJhiwUpQ == ZIBVUiHdct){UOcyOWIeru = true;}
      if(GOWEebwrnJ == twzeLrbYaD){rhMAPUtLiw = true;}
      else if(twzeLrbYaD == GOWEebwrnJ){mCkAQYCqJd = true;}
      if(phYnCTMtjP == TssrEAJjKL){psLILLfhuc = true;}
      else if(TssrEAJjKL == phYnCTMtjP){SOhnynNZIx = true;}
      if(BkhAbetCdZ == RZuLFgXalC){PdSeHYadIe = true;}
      else if(RZuLFgXalC == BkhAbetCdZ){ImgYGzhtWS = true;}
      if(FhkkYOeiJP == sgxMpygERL){XFcfYjwUoI = true;}
      else if(sgxMpygERL == FhkkYOeiJP){tPHDQoTBMV = true;}
      if(cKhtXqjNSA == QQwninONFh){mLiRfDhVbe = true;}
      if(VMsNsVgWcz == ZMKdyTBnZd){jucAgNPgrp = true;}
      if(gsNNEHxmOm == UAlXKlwgBF){sPCDYkQfja = true;}
      while(QQwninONFh == cKhtXqjNSA){YkSUrFgnza = true;}
      while(ZMKdyTBnZd == ZMKdyTBnZd){JiVulAULtQ = true;}
      while(UAlXKlwgBF == UAlXKlwgBF){qHTpiCGdWJ = true;}
      if(SFSzuBdHbQ == true){SFSzuBdHbQ = false;}
      if(SJUEcgWSOW == true){SJUEcgWSOW = false;}
      if(xsdnpPdXdw == true){xsdnpPdXdw = false;}
      if(rhMAPUtLiw == true){rhMAPUtLiw = false;}
      if(psLILLfhuc == true){psLILLfhuc = false;}
      if(PdSeHYadIe == true){PdSeHYadIe = false;}
      if(XFcfYjwUoI == true){XFcfYjwUoI = false;}
      if(mLiRfDhVbe == true){mLiRfDhVbe = false;}
      if(jucAgNPgrp == true){jucAgNPgrp = false;}
      if(sPCDYkQfja == true){sPCDYkQfja = false;}
      if(OKslpDuAzE == true){OKslpDuAzE = false;}
      if(qFCcubbcyK == true){qFCcubbcyK = false;}
      if(UOcyOWIeru == true){UOcyOWIeru = false;}
      if(mCkAQYCqJd == true){mCkAQYCqJd = false;}
      if(SOhnynNZIx == true){SOhnynNZIx = false;}
      if(ImgYGzhtWS == true){ImgYGzhtWS = false;}
      if(tPHDQoTBMV == true){tPHDQoTBMV = false;}
      if(YkSUrFgnza == true){YkSUrFgnza = false;}
      if(JiVulAULtQ == true){JiVulAULtQ = false;}
      if(qHTpiCGdWJ == true){qHTpiCGdWJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HJMNCDJTFF
{ 
  void oeDrNYXQiI()
  { 
      bool IxglFRzJhZ = false;
      bool RtLWjeTcMA = false;
      bool XXwWmCCeXc = false;
      bool jcmlQCKzlV = false;
      bool VxSqRMiIgb = false;
      bool FZpkpjBKyC = false;
      bool PTlFpnHZFh = false;
      bool TTppdZEFFa = false;
      bool SsyuXJlBuf = false;
      bool BzAjGBLNAc = false;
      bool FJCzHkjAGQ = false;
      bool fuFXiVVpgg = false;
      bool CFdZfUTGjb = false;
      bool OqEbUIqynm = false;
      bool YludAFtbAj = false;
      bool fUfTaAecSm = false;
      bool QdQeCoqcCZ = false;
      bool eXCtHPKAYa = false;
      bool ZqFzwsKkBU = false;
      bool dNfAVuVPbL = false;
      string BVVllAbNbi;
      string BQXJMUlOZz;
      string GeFYgujlOn;
      string yDjxrKCfsX;
      string AskBVPXWFP;
      string IuQoBVPwEq;
      string QpynjxfaQC;
      string SGVBzNtDDQ;
      string WMfzeDmuuW;
      string tFaBGJuxRX;
      string ixGDxBYOpn;
      string bMsmTEJyIg;
      string KketHMeTto;
      string RwlehYGbCd;
      string dXEHthMmgC;
      string AwokNyRLwj;
      string WFUBVfZOFu;
      string xhweCmfXAY;
      string AqlqnVHBRi;
      string HteRGYDDkO;
      if(BVVllAbNbi == ixGDxBYOpn){IxglFRzJhZ = true;}
      else if(ixGDxBYOpn == BVVllAbNbi){FJCzHkjAGQ = true;}
      if(BQXJMUlOZz == bMsmTEJyIg){RtLWjeTcMA = true;}
      else if(bMsmTEJyIg == BQXJMUlOZz){fuFXiVVpgg = true;}
      if(GeFYgujlOn == KketHMeTto){XXwWmCCeXc = true;}
      else if(KketHMeTto == GeFYgujlOn){CFdZfUTGjb = true;}
      if(yDjxrKCfsX == RwlehYGbCd){jcmlQCKzlV = true;}
      else if(RwlehYGbCd == yDjxrKCfsX){OqEbUIqynm = true;}
      if(AskBVPXWFP == dXEHthMmgC){VxSqRMiIgb = true;}
      else if(dXEHthMmgC == AskBVPXWFP){YludAFtbAj = true;}
      if(IuQoBVPwEq == AwokNyRLwj){FZpkpjBKyC = true;}
      else if(AwokNyRLwj == IuQoBVPwEq){fUfTaAecSm = true;}
      if(QpynjxfaQC == WFUBVfZOFu){PTlFpnHZFh = true;}
      else if(WFUBVfZOFu == QpynjxfaQC){QdQeCoqcCZ = true;}
      if(SGVBzNtDDQ == xhweCmfXAY){TTppdZEFFa = true;}
      if(WMfzeDmuuW == AqlqnVHBRi){SsyuXJlBuf = true;}
      if(tFaBGJuxRX == HteRGYDDkO){BzAjGBLNAc = true;}
      while(xhweCmfXAY == SGVBzNtDDQ){eXCtHPKAYa = true;}
      while(AqlqnVHBRi == AqlqnVHBRi){ZqFzwsKkBU = true;}
      while(HteRGYDDkO == HteRGYDDkO){dNfAVuVPbL = true;}
      if(IxglFRzJhZ == true){IxglFRzJhZ = false;}
      if(RtLWjeTcMA == true){RtLWjeTcMA = false;}
      if(XXwWmCCeXc == true){XXwWmCCeXc = false;}
      if(jcmlQCKzlV == true){jcmlQCKzlV = false;}
      if(VxSqRMiIgb == true){VxSqRMiIgb = false;}
      if(FZpkpjBKyC == true){FZpkpjBKyC = false;}
      if(PTlFpnHZFh == true){PTlFpnHZFh = false;}
      if(TTppdZEFFa == true){TTppdZEFFa = false;}
      if(SsyuXJlBuf == true){SsyuXJlBuf = false;}
      if(BzAjGBLNAc == true){BzAjGBLNAc = false;}
      if(FJCzHkjAGQ == true){FJCzHkjAGQ = false;}
      if(fuFXiVVpgg == true){fuFXiVVpgg = false;}
      if(CFdZfUTGjb == true){CFdZfUTGjb = false;}
      if(OqEbUIqynm == true){OqEbUIqynm = false;}
      if(YludAFtbAj == true){YludAFtbAj = false;}
      if(fUfTaAecSm == true){fUfTaAecSm = false;}
      if(QdQeCoqcCZ == true){QdQeCoqcCZ = false;}
      if(eXCtHPKAYa == true){eXCtHPKAYa = false;}
      if(ZqFzwsKkBU == true){ZqFzwsKkBU = false;}
      if(dNfAVuVPbL == true){dNfAVuVPbL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ISMYZMQCHB
{ 
  void dwheUHVNIk()
  { 
      bool xHxGwYgVzQ = false;
      bool LgBWJWbAmo = false;
      bool PmIOgHVjYr = false;
      bool qaERNdkfDU = false;
      bool XGkQTBMJjJ = false;
      bool VNBeTJyiZn = false;
      bool CxxGZjbiJe = false;
      bool kuxRQJBqtf = false;
      bool uMzOVdYZyD = false;
      bool fCGOSZJdqi = false;
      bool YczFYZPjNK = false;
      bool IHnsrpxiju = false;
      bool KCjGziohzp = false;
      bool zWALHRMtpu = false;
      bool NoLnuXNMWc = false;
      bool cZsuYVssGp = false;
      bool jgjWKkGcla = false;
      bool cDsngUqwLa = false;
      bool UcLWNZcFll = false;
      bool YTnzLgEocJ = false;
      string cKaXTacHjU;
      string MCrFgLljJy;
      string EFtjzlokXW;
      string jOpeyiiREo;
      string jLgcnbGpKF;
      string BBkQDWPqYg;
      string kriMjyMNHx;
      string bTeTNrYRuW;
      string ezaRUhdYab;
      string SrsXDrbTrp;
      string PriMdgVQCL;
      string yxuBBlQRrC;
      string TmmeeiaHQV;
      string QEZEHmQNnm;
      string LNWOcUxqVR;
      string bKaoWbFDgt;
      string GNzgusXpsO;
      string VCcFpFQXCK;
      string kilztFcjhe;
      string hNfsgxNoTj;
      if(cKaXTacHjU == PriMdgVQCL){xHxGwYgVzQ = true;}
      else if(PriMdgVQCL == cKaXTacHjU){YczFYZPjNK = true;}
      if(MCrFgLljJy == yxuBBlQRrC){LgBWJWbAmo = true;}
      else if(yxuBBlQRrC == MCrFgLljJy){IHnsrpxiju = true;}
      if(EFtjzlokXW == TmmeeiaHQV){PmIOgHVjYr = true;}
      else if(TmmeeiaHQV == EFtjzlokXW){KCjGziohzp = true;}
      if(jOpeyiiREo == QEZEHmQNnm){qaERNdkfDU = true;}
      else if(QEZEHmQNnm == jOpeyiiREo){zWALHRMtpu = true;}
      if(jLgcnbGpKF == LNWOcUxqVR){XGkQTBMJjJ = true;}
      else if(LNWOcUxqVR == jLgcnbGpKF){NoLnuXNMWc = true;}
      if(BBkQDWPqYg == bKaoWbFDgt){VNBeTJyiZn = true;}
      else if(bKaoWbFDgt == BBkQDWPqYg){cZsuYVssGp = true;}
      if(kriMjyMNHx == GNzgusXpsO){CxxGZjbiJe = true;}
      else if(GNzgusXpsO == kriMjyMNHx){jgjWKkGcla = true;}
      if(bTeTNrYRuW == VCcFpFQXCK){kuxRQJBqtf = true;}
      if(ezaRUhdYab == kilztFcjhe){uMzOVdYZyD = true;}
      if(SrsXDrbTrp == hNfsgxNoTj){fCGOSZJdqi = true;}
      while(VCcFpFQXCK == bTeTNrYRuW){cDsngUqwLa = true;}
      while(kilztFcjhe == kilztFcjhe){UcLWNZcFll = true;}
      while(hNfsgxNoTj == hNfsgxNoTj){YTnzLgEocJ = true;}
      if(xHxGwYgVzQ == true){xHxGwYgVzQ = false;}
      if(LgBWJWbAmo == true){LgBWJWbAmo = false;}
      if(PmIOgHVjYr == true){PmIOgHVjYr = false;}
      if(qaERNdkfDU == true){qaERNdkfDU = false;}
      if(XGkQTBMJjJ == true){XGkQTBMJjJ = false;}
      if(VNBeTJyiZn == true){VNBeTJyiZn = false;}
      if(CxxGZjbiJe == true){CxxGZjbiJe = false;}
      if(kuxRQJBqtf == true){kuxRQJBqtf = false;}
      if(uMzOVdYZyD == true){uMzOVdYZyD = false;}
      if(fCGOSZJdqi == true){fCGOSZJdqi = false;}
      if(YczFYZPjNK == true){YczFYZPjNK = false;}
      if(IHnsrpxiju == true){IHnsrpxiju = false;}
      if(KCjGziohzp == true){KCjGziohzp = false;}
      if(zWALHRMtpu == true){zWALHRMtpu = false;}
      if(NoLnuXNMWc == true){NoLnuXNMWc = false;}
      if(cZsuYVssGp == true){cZsuYVssGp = false;}
      if(jgjWKkGcla == true){jgjWKkGcla = false;}
      if(cDsngUqwLa == true){cDsngUqwLa = false;}
      if(UcLWNZcFll == true){UcLWNZcFll = false;}
      if(YTnzLgEocJ == true){YTnzLgEocJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEEKUZUCMB
{ 
  void ilfHtYIXYg()
  { 
      bool atqtHaxBbf = false;
      bool cSxfOLKOkZ = false;
      bool pACeirWqmN = false;
      bool LFpJQNNfio = false;
      bool BCQThdIqCu = false;
      bool JafbFZqLLP = false;
      bool EGNOTXcnPA = false;
      bool xdfwYnjiwE = false;
      bool ieorDkYODq = false;
      bool WBUSjtnCzK = false;
      bool BTbByeujDQ = false;
      bool pIPHfYRVKh = false;
      bool yOjXduJMLd = false;
      bool AgilDPDmsX = false;
      bool poKmANlMmL = false;
      bool cRqRLmiDXC = false;
      bool VhXYPIZdEQ = false;
      bool VeblrJDxXQ = false;
      bool IwZAAipRZP = false;
      bool fzOpCHQlWr = false;
      string PYmtFBWwmW;
      string NzNQsSFBrq;
      string bMaoqhjwhw;
      string sQAqlOfklf;
      string nSCaboybOQ;
      string WBQqmDxxDX;
      string QZOpdxzVdd;
      string mUPMCJKAMB;
      string jHgRZqzIEi;
      string RhhOOODLxe;
      string pbykcClDod;
      string rxjBnIrxQm;
      string xpRuMFlBxm;
      string FyDhLHJwnW;
      string EuTZpUxgaG;
      string WGuJhAKDXW;
      string QkFBYtsCpf;
      string yuIshBWqFr;
      string IFaqQyDszL;
      string xGXQGToRBu;
      if(PYmtFBWwmW == pbykcClDod){atqtHaxBbf = true;}
      else if(pbykcClDod == PYmtFBWwmW){BTbByeujDQ = true;}
      if(NzNQsSFBrq == rxjBnIrxQm){cSxfOLKOkZ = true;}
      else if(rxjBnIrxQm == NzNQsSFBrq){pIPHfYRVKh = true;}
      if(bMaoqhjwhw == xpRuMFlBxm){pACeirWqmN = true;}
      else if(xpRuMFlBxm == bMaoqhjwhw){yOjXduJMLd = true;}
      if(sQAqlOfklf == FyDhLHJwnW){LFpJQNNfio = true;}
      else if(FyDhLHJwnW == sQAqlOfklf){AgilDPDmsX = true;}
      if(nSCaboybOQ == EuTZpUxgaG){BCQThdIqCu = true;}
      else if(EuTZpUxgaG == nSCaboybOQ){poKmANlMmL = true;}
      if(WBQqmDxxDX == WGuJhAKDXW){JafbFZqLLP = true;}
      else if(WGuJhAKDXW == WBQqmDxxDX){cRqRLmiDXC = true;}
      if(QZOpdxzVdd == QkFBYtsCpf){EGNOTXcnPA = true;}
      else if(QkFBYtsCpf == QZOpdxzVdd){VhXYPIZdEQ = true;}
      if(mUPMCJKAMB == yuIshBWqFr){xdfwYnjiwE = true;}
      if(jHgRZqzIEi == IFaqQyDszL){ieorDkYODq = true;}
      if(RhhOOODLxe == xGXQGToRBu){WBUSjtnCzK = true;}
      while(yuIshBWqFr == mUPMCJKAMB){VeblrJDxXQ = true;}
      while(IFaqQyDszL == IFaqQyDszL){IwZAAipRZP = true;}
      while(xGXQGToRBu == xGXQGToRBu){fzOpCHQlWr = true;}
      if(atqtHaxBbf == true){atqtHaxBbf = false;}
      if(cSxfOLKOkZ == true){cSxfOLKOkZ = false;}
      if(pACeirWqmN == true){pACeirWqmN = false;}
      if(LFpJQNNfio == true){LFpJQNNfio = false;}
      if(BCQThdIqCu == true){BCQThdIqCu = false;}
      if(JafbFZqLLP == true){JafbFZqLLP = false;}
      if(EGNOTXcnPA == true){EGNOTXcnPA = false;}
      if(xdfwYnjiwE == true){xdfwYnjiwE = false;}
      if(ieorDkYODq == true){ieorDkYODq = false;}
      if(WBUSjtnCzK == true){WBUSjtnCzK = false;}
      if(BTbByeujDQ == true){BTbByeujDQ = false;}
      if(pIPHfYRVKh == true){pIPHfYRVKh = false;}
      if(yOjXduJMLd == true){yOjXduJMLd = false;}
      if(AgilDPDmsX == true){AgilDPDmsX = false;}
      if(poKmANlMmL == true){poKmANlMmL = false;}
      if(cRqRLmiDXC == true){cRqRLmiDXC = false;}
      if(VhXYPIZdEQ == true){VhXYPIZdEQ = false;}
      if(VeblrJDxXQ == true){VeblrJDxXQ = false;}
      if(IwZAAipRZP == true){IwZAAipRZP = false;}
      if(fzOpCHQlWr == true){fzOpCHQlWr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KADQSRHEFN
{ 
  void lEZyoypNNC()
  { 
      bool ECEduhTHlh = false;
      bool cxgYxFeqJi = false;
      bool SAQnFeNiKX = false;
      bool gDmKhbXyyZ = false;
      bool rYCYdyuQfU = false;
      bool mATuNDlQYP = false;
      bool TkxOAYKVqU = false;
      bool ggsipsyqKG = false;
      bool jxCokgjqxd = false;
      bool pHZiGHamXE = false;
      bool mYYLmGHjFT = false;
      bool EtFRfVhHdT = false;
      bool oTYMdZHJch = false;
      bool SKTFSKXqCd = false;
      bool ZzlcZwBHCj = false;
      bool ZTJEPTAMgN = false;
      bool yxGWBsZAzV = false;
      bool xpFzsohumh = false;
      bool XAGsIzBOoy = false;
      bool JLKofbrObf = false;
      string tRDpPWLliE;
      string NqJMzkPacV;
      string zLBtahQQgU;
      string CBFBlRUaZS;
      string kEAsVXPUYu;
      string AOqxkiPJOg;
      string GuENCMkIZh;
      string PoAJjtLIXD;
      string SwqlUmKIQD;
      string BLLsMpAlqJ;
      string lHuqfLOgMp;
      string XHlLNJESsO;
      string CcqVfEcHwt;
      string tYROQLBAFI;
      string YcuZetZAeD;
      string lgrbHJPYKb;
      string hGkRuzpWuB;
      string IDMkoYgRql;
      string ecbsIMfoGG;
      string wcodZRqcdf;
      if(tRDpPWLliE == lHuqfLOgMp){ECEduhTHlh = true;}
      else if(lHuqfLOgMp == tRDpPWLliE){mYYLmGHjFT = true;}
      if(NqJMzkPacV == XHlLNJESsO){cxgYxFeqJi = true;}
      else if(XHlLNJESsO == NqJMzkPacV){EtFRfVhHdT = true;}
      if(zLBtahQQgU == CcqVfEcHwt){SAQnFeNiKX = true;}
      else if(CcqVfEcHwt == zLBtahQQgU){oTYMdZHJch = true;}
      if(CBFBlRUaZS == tYROQLBAFI){gDmKhbXyyZ = true;}
      else if(tYROQLBAFI == CBFBlRUaZS){SKTFSKXqCd = true;}
      if(kEAsVXPUYu == YcuZetZAeD){rYCYdyuQfU = true;}
      else if(YcuZetZAeD == kEAsVXPUYu){ZzlcZwBHCj = true;}
      if(AOqxkiPJOg == lgrbHJPYKb){mATuNDlQYP = true;}
      else if(lgrbHJPYKb == AOqxkiPJOg){ZTJEPTAMgN = true;}
      if(GuENCMkIZh == hGkRuzpWuB){TkxOAYKVqU = true;}
      else if(hGkRuzpWuB == GuENCMkIZh){yxGWBsZAzV = true;}
      if(PoAJjtLIXD == IDMkoYgRql){ggsipsyqKG = true;}
      if(SwqlUmKIQD == ecbsIMfoGG){jxCokgjqxd = true;}
      if(BLLsMpAlqJ == wcodZRqcdf){pHZiGHamXE = true;}
      while(IDMkoYgRql == PoAJjtLIXD){xpFzsohumh = true;}
      while(ecbsIMfoGG == ecbsIMfoGG){XAGsIzBOoy = true;}
      while(wcodZRqcdf == wcodZRqcdf){JLKofbrObf = true;}
      if(ECEduhTHlh == true){ECEduhTHlh = false;}
      if(cxgYxFeqJi == true){cxgYxFeqJi = false;}
      if(SAQnFeNiKX == true){SAQnFeNiKX = false;}
      if(gDmKhbXyyZ == true){gDmKhbXyyZ = false;}
      if(rYCYdyuQfU == true){rYCYdyuQfU = false;}
      if(mATuNDlQYP == true){mATuNDlQYP = false;}
      if(TkxOAYKVqU == true){TkxOAYKVqU = false;}
      if(ggsipsyqKG == true){ggsipsyqKG = false;}
      if(jxCokgjqxd == true){jxCokgjqxd = false;}
      if(pHZiGHamXE == true){pHZiGHamXE = false;}
      if(mYYLmGHjFT == true){mYYLmGHjFT = false;}
      if(EtFRfVhHdT == true){EtFRfVhHdT = false;}
      if(oTYMdZHJch == true){oTYMdZHJch = false;}
      if(SKTFSKXqCd == true){SKTFSKXqCd = false;}
      if(ZzlcZwBHCj == true){ZzlcZwBHCj = false;}
      if(ZTJEPTAMgN == true){ZTJEPTAMgN = false;}
      if(yxGWBsZAzV == true){yxGWBsZAzV = false;}
      if(xpFzsohumh == true){xpFzsohumh = false;}
      if(XAGsIzBOoy == true){XAGsIzBOoy = false;}
      if(JLKofbrObf == true){JLKofbrObf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYVMOPNAGO
{ 
  void AyuLZEeICp()
  { 
      bool VVtRMQnWRt = false;
      bool xqQyLUjIAK = false;
      bool XaxNsJwcbZ = false;
      bool TuqqWxbnzL = false;
      bool KOKptOeWzg = false;
      bool nqxiKtYfXD = false;
      bool UKtqaBAZbO = false;
      bool suJnAIQGTd = false;
      bool eYdtlbyHgb = false;
      bool XuPwqATTOr = false;
      bool OFukmshIiB = false;
      bool dRMtYugAFy = false;
      bool DsszpyeNxz = false;
      bool owqaPYcsGs = false;
      bool toXeyGiVXu = false;
      bool SSNQoUMwuo = false;
      bool NUKiMgZkdz = false;
      bool SnsMENUNAi = false;
      bool PIoCgVhakt = false;
      bool MgxReZenSQ = false;
      string VtHfnuaRLt;
      string gUktZZkJtt;
      string FPeWuBGWxf;
      string JShGqkTZmB;
      string SYELTzyKzH;
      string YitQQFPjkl;
      string nDTfkOleCo;
      string GKWrafKSDw;
      string DuXpHZXQol;
      string VjoAMOFYaE;
      string MSHKANMBoj;
      string twfoisfcXL;
      string pVpQSWVWfL;
      string alryijmNot;
      string NVaEqZDAQS;
      string ibAPOqcqqd;
      string qoVcJIDgFz;
      string GRndyTtkZs;
      string SVFMcykcjq;
      string GwVKCXAyth;
      if(VtHfnuaRLt == MSHKANMBoj){VVtRMQnWRt = true;}
      else if(MSHKANMBoj == VtHfnuaRLt){OFukmshIiB = true;}
      if(gUktZZkJtt == twfoisfcXL){xqQyLUjIAK = true;}
      else if(twfoisfcXL == gUktZZkJtt){dRMtYugAFy = true;}
      if(FPeWuBGWxf == pVpQSWVWfL){XaxNsJwcbZ = true;}
      else if(pVpQSWVWfL == FPeWuBGWxf){DsszpyeNxz = true;}
      if(JShGqkTZmB == alryijmNot){TuqqWxbnzL = true;}
      else if(alryijmNot == JShGqkTZmB){owqaPYcsGs = true;}
      if(SYELTzyKzH == NVaEqZDAQS){KOKptOeWzg = true;}
      else if(NVaEqZDAQS == SYELTzyKzH){toXeyGiVXu = true;}
      if(YitQQFPjkl == ibAPOqcqqd){nqxiKtYfXD = true;}
      else if(ibAPOqcqqd == YitQQFPjkl){SSNQoUMwuo = true;}
      if(nDTfkOleCo == qoVcJIDgFz){UKtqaBAZbO = true;}
      else if(qoVcJIDgFz == nDTfkOleCo){NUKiMgZkdz = true;}
      if(GKWrafKSDw == GRndyTtkZs){suJnAIQGTd = true;}
      if(DuXpHZXQol == SVFMcykcjq){eYdtlbyHgb = true;}
      if(VjoAMOFYaE == GwVKCXAyth){XuPwqATTOr = true;}
      while(GRndyTtkZs == GKWrafKSDw){SnsMENUNAi = true;}
      while(SVFMcykcjq == SVFMcykcjq){PIoCgVhakt = true;}
      while(GwVKCXAyth == GwVKCXAyth){MgxReZenSQ = true;}
      if(VVtRMQnWRt == true){VVtRMQnWRt = false;}
      if(xqQyLUjIAK == true){xqQyLUjIAK = false;}
      if(XaxNsJwcbZ == true){XaxNsJwcbZ = false;}
      if(TuqqWxbnzL == true){TuqqWxbnzL = false;}
      if(KOKptOeWzg == true){KOKptOeWzg = false;}
      if(nqxiKtYfXD == true){nqxiKtYfXD = false;}
      if(UKtqaBAZbO == true){UKtqaBAZbO = false;}
      if(suJnAIQGTd == true){suJnAIQGTd = false;}
      if(eYdtlbyHgb == true){eYdtlbyHgb = false;}
      if(XuPwqATTOr == true){XuPwqATTOr = false;}
      if(OFukmshIiB == true){OFukmshIiB = false;}
      if(dRMtYugAFy == true){dRMtYugAFy = false;}
      if(DsszpyeNxz == true){DsszpyeNxz = false;}
      if(owqaPYcsGs == true){owqaPYcsGs = false;}
      if(toXeyGiVXu == true){toXeyGiVXu = false;}
      if(SSNQoUMwuo == true){SSNQoUMwuo = false;}
      if(NUKiMgZkdz == true){NUKiMgZkdz = false;}
      if(SnsMENUNAi == true){SnsMENUNAi = false;}
      if(PIoCgVhakt == true){PIoCgVhakt = false;}
      if(MgxReZenSQ == true){MgxReZenSQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GQZEMLXOZT
{ 
  void zWOcbtLYtz()
  { 
      bool VxHbUYeXye = false;
      bool MtOrmFilfl = false;
      bool FFCrQlaNPk = false;
      bool ftOiCrKuAB = false;
      bool mAPMgYtAZe = false;
      bool YLaGJQuPKi = false;
      bool xQIMySfeot = false;
      bool tnkeyFpoKr = false;
      bool qamjLUSIYl = false;
      bool xtjQDVrCNO = false;
      bool sOKfkjauHE = false;
      bool aFFRrWdXAd = false;
      bool zWGDxzDTbc = false;
      bool MmawzbPHyb = false;
      bool tWATKroRYf = false;
      bool rTBjPVIHhl = false;
      bool fGTermeJSP = false;
      bool HVZYjbWlrF = false;
      bool Jluujrlqgd = false;
      bool SHYMumDVbX = false;
      string VpNKcAQBjE;
      string sHWuNCapwg;
      string oPOVZBEwhg;
      string rLDwdmfYqc;
      string qrkLakdZGf;
      string mnMOYGaqjb;
      string wTTDLhEZRa;
      string VBySoweDuo;
      string XepBtEynXW;
      string MnoPgWYgzs;
      string fDIfKkosYb;
      string bWwuDQdRJH;
      string iQCtNgMilS;
      string XxECJTWKpI;
      string OFOuuoqsLP;
      string rGXqJOBNRc;
      string XGHGDeStlj;
      string tTaAsdCGzY;
      string oSWVZRYNrt;
      string SIsNkIxHrP;
      if(VpNKcAQBjE == fDIfKkosYb){VxHbUYeXye = true;}
      else if(fDIfKkosYb == VpNKcAQBjE){sOKfkjauHE = true;}
      if(sHWuNCapwg == bWwuDQdRJH){MtOrmFilfl = true;}
      else if(bWwuDQdRJH == sHWuNCapwg){aFFRrWdXAd = true;}
      if(oPOVZBEwhg == iQCtNgMilS){FFCrQlaNPk = true;}
      else if(iQCtNgMilS == oPOVZBEwhg){zWGDxzDTbc = true;}
      if(rLDwdmfYqc == XxECJTWKpI){ftOiCrKuAB = true;}
      else if(XxECJTWKpI == rLDwdmfYqc){MmawzbPHyb = true;}
      if(qrkLakdZGf == OFOuuoqsLP){mAPMgYtAZe = true;}
      else if(OFOuuoqsLP == qrkLakdZGf){tWATKroRYf = true;}
      if(mnMOYGaqjb == rGXqJOBNRc){YLaGJQuPKi = true;}
      else if(rGXqJOBNRc == mnMOYGaqjb){rTBjPVIHhl = true;}
      if(wTTDLhEZRa == XGHGDeStlj){xQIMySfeot = true;}
      else if(XGHGDeStlj == wTTDLhEZRa){fGTermeJSP = true;}
      if(VBySoweDuo == tTaAsdCGzY){tnkeyFpoKr = true;}
      if(XepBtEynXW == oSWVZRYNrt){qamjLUSIYl = true;}
      if(MnoPgWYgzs == SIsNkIxHrP){xtjQDVrCNO = true;}
      while(tTaAsdCGzY == VBySoweDuo){HVZYjbWlrF = true;}
      while(oSWVZRYNrt == oSWVZRYNrt){Jluujrlqgd = true;}
      while(SIsNkIxHrP == SIsNkIxHrP){SHYMumDVbX = true;}
      if(VxHbUYeXye == true){VxHbUYeXye = false;}
      if(MtOrmFilfl == true){MtOrmFilfl = false;}
      if(FFCrQlaNPk == true){FFCrQlaNPk = false;}
      if(ftOiCrKuAB == true){ftOiCrKuAB = false;}
      if(mAPMgYtAZe == true){mAPMgYtAZe = false;}
      if(YLaGJQuPKi == true){YLaGJQuPKi = false;}
      if(xQIMySfeot == true){xQIMySfeot = false;}
      if(tnkeyFpoKr == true){tnkeyFpoKr = false;}
      if(qamjLUSIYl == true){qamjLUSIYl = false;}
      if(xtjQDVrCNO == true){xtjQDVrCNO = false;}
      if(sOKfkjauHE == true){sOKfkjauHE = false;}
      if(aFFRrWdXAd == true){aFFRrWdXAd = false;}
      if(zWGDxzDTbc == true){zWGDxzDTbc = false;}
      if(MmawzbPHyb == true){MmawzbPHyb = false;}
      if(tWATKroRYf == true){tWATKroRYf = false;}
      if(rTBjPVIHhl == true){rTBjPVIHhl = false;}
      if(fGTermeJSP == true){fGTermeJSP = false;}
      if(HVZYjbWlrF == true){HVZYjbWlrF = false;}
      if(Jluujrlqgd == true){Jluujrlqgd = false;}
      if(SHYMumDVbX == true){SHYMumDVbX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHWDQFTHXU
{ 
  void mLzYfPtJpt()
  { 
      bool UtuKpMKXyO = false;
      bool NKRWOybePc = false;
      bool QCFkTTKBAb = false;
      bool ijlYipkyIC = false;
      bool jiaQGcwHsX = false;
      bool bAArDRoKqV = false;
      bool CIXVfcYsmY = false;
      bool McWNshaodp = false;
      bool WCHczhjsVQ = false;
      bool AZHlzaLFjd = false;
      bool EDTTKzdlzV = false;
      bool qzfAyABtVx = false;
      bool reWWXlVkNR = false;
      bool VUEAlShmRA = false;
      bool ExtAYAtHmz = false;
      bool ZQimkYgxwX = false;
      bool drYhzVufNf = false;
      bool RNcVrukVxW = false;
      bool rNxOqElQPN = false;
      bool lkqsWMYLAD = false;
      string ZPzfdPDKkF;
      string IyFYlOsoef;
      string ZbfwyjefWy;
      string eYFVRKbWcV;
      string SYGblDGFBB;
      string jaMKnxjDht;
      string kXmmajrjGa;
      string mWLJMAVEKt;
      string dZeVOELthT;
      string aXoikukSAB;
      string LVyZNNOCym;
      string aesmPKsRXV;
      string XxClzOhcYR;
      string OCDIhHaEHB;
      string pJwtsweBSZ;
      string BTudcNTLZz;
      string ekdfXYbjFI;
      string inJWfOAIsD;
      string jgJyPtHYeT;
      string nOdIVEeQVT;
      if(ZPzfdPDKkF == LVyZNNOCym){UtuKpMKXyO = true;}
      else if(LVyZNNOCym == ZPzfdPDKkF){EDTTKzdlzV = true;}
      if(IyFYlOsoef == aesmPKsRXV){NKRWOybePc = true;}
      else if(aesmPKsRXV == IyFYlOsoef){qzfAyABtVx = true;}
      if(ZbfwyjefWy == XxClzOhcYR){QCFkTTKBAb = true;}
      else if(XxClzOhcYR == ZbfwyjefWy){reWWXlVkNR = true;}
      if(eYFVRKbWcV == OCDIhHaEHB){ijlYipkyIC = true;}
      else if(OCDIhHaEHB == eYFVRKbWcV){VUEAlShmRA = true;}
      if(SYGblDGFBB == pJwtsweBSZ){jiaQGcwHsX = true;}
      else if(pJwtsweBSZ == SYGblDGFBB){ExtAYAtHmz = true;}
      if(jaMKnxjDht == BTudcNTLZz){bAArDRoKqV = true;}
      else if(BTudcNTLZz == jaMKnxjDht){ZQimkYgxwX = true;}
      if(kXmmajrjGa == ekdfXYbjFI){CIXVfcYsmY = true;}
      else if(ekdfXYbjFI == kXmmajrjGa){drYhzVufNf = true;}
      if(mWLJMAVEKt == inJWfOAIsD){McWNshaodp = true;}
      if(dZeVOELthT == jgJyPtHYeT){WCHczhjsVQ = true;}
      if(aXoikukSAB == nOdIVEeQVT){AZHlzaLFjd = true;}
      while(inJWfOAIsD == mWLJMAVEKt){RNcVrukVxW = true;}
      while(jgJyPtHYeT == jgJyPtHYeT){rNxOqElQPN = true;}
      while(nOdIVEeQVT == nOdIVEeQVT){lkqsWMYLAD = true;}
      if(UtuKpMKXyO == true){UtuKpMKXyO = false;}
      if(NKRWOybePc == true){NKRWOybePc = false;}
      if(QCFkTTKBAb == true){QCFkTTKBAb = false;}
      if(ijlYipkyIC == true){ijlYipkyIC = false;}
      if(jiaQGcwHsX == true){jiaQGcwHsX = false;}
      if(bAArDRoKqV == true){bAArDRoKqV = false;}
      if(CIXVfcYsmY == true){CIXVfcYsmY = false;}
      if(McWNshaodp == true){McWNshaodp = false;}
      if(WCHczhjsVQ == true){WCHczhjsVQ = false;}
      if(AZHlzaLFjd == true){AZHlzaLFjd = false;}
      if(EDTTKzdlzV == true){EDTTKzdlzV = false;}
      if(qzfAyABtVx == true){qzfAyABtVx = false;}
      if(reWWXlVkNR == true){reWWXlVkNR = false;}
      if(VUEAlShmRA == true){VUEAlShmRA = false;}
      if(ExtAYAtHmz == true){ExtAYAtHmz = false;}
      if(ZQimkYgxwX == true){ZQimkYgxwX = false;}
      if(drYhzVufNf == true){drYhzVufNf = false;}
      if(RNcVrukVxW == true){RNcVrukVxW = false;}
      if(rNxOqElQPN == true){rNxOqElQPN = false;}
      if(lkqsWMYLAD == true){lkqsWMYLAD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWHILJSIAR
{ 
  void PRQNsQJfJK()
  { 
      bool XKizsizqJy = false;
      bool tLdugSOuEA = false;
      bool CECqxdCaMF = false;
      bool KwqYnDAOGJ = false;
      bool iKJsNnIBMj = false;
      bool YzSnyTHrCP = false;
      bool gYdEmxTFHd = false;
      bool RzouQrtJcI = false;
      bool UANbfKdCaU = false;
      bool uILpbKfFFP = false;
      bool TDthRYKWXF = false;
      bool YyOsufLCXb = false;
      bool TRdliJmySG = false;
      bool MnENoQGeJH = false;
      bool AGeVuxtSuu = false;
      bool zdhcwCZHzI = false;
      bool kMDRsjsAEe = false;
      bool ZfrPbMlHpl = false;
      bool OUCWHhGaRl = false;
      bool pyfBVnCNbL = false;
      string PheNixMpeu;
      string aTGNTsgHld;
      string cRFrOGKlbc;
      string ihjlQTgFNG;
      string OseWumQgQZ;
      string ygkoYybmzc;
      string lZNBLsiTxA;
      string MatePjlhxa;
      string ocVCeCwtNR;
      string qtGjUnfdLB;
      string DxjQMXlFZn;
      string MtpXnJEKWI;
      string woFeIRTJKb;
      string EIVuXqrEoG;
      string PpUYFwEiwK;
      string iUGCEOrEHu;
      string DcuxjEXtAw;
      string QzUPsGTfZM;
      string NjNzriBTqI;
      string zmxtDmuWoA;
      if(PheNixMpeu == DxjQMXlFZn){XKizsizqJy = true;}
      else if(DxjQMXlFZn == PheNixMpeu){TDthRYKWXF = true;}
      if(aTGNTsgHld == MtpXnJEKWI){tLdugSOuEA = true;}
      else if(MtpXnJEKWI == aTGNTsgHld){YyOsufLCXb = true;}
      if(cRFrOGKlbc == woFeIRTJKb){CECqxdCaMF = true;}
      else if(woFeIRTJKb == cRFrOGKlbc){TRdliJmySG = true;}
      if(ihjlQTgFNG == EIVuXqrEoG){KwqYnDAOGJ = true;}
      else if(EIVuXqrEoG == ihjlQTgFNG){MnENoQGeJH = true;}
      if(OseWumQgQZ == PpUYFwEiwK){iKJsNnIBMj = true;}
      else if(PpUYFwEiwK == OseWumQgQZ){AGeVuxtSuu = true;}
      if(ygkoYybmzc == iUGCEOrEHu){YzSnyTHrCP = true;}
      else if(iUGCEOrEHu == ygkoYybmzc){zdhcwCZHzI = true;}
      if(lZNBLsiTxA == DcuxjEXtAw){gYdEmxTFHd = true;}
      else if(DcuxjEXtAw == lZNBLsiTxA){kMDRsjsAEe = true;}
      if(MatePjlhxa == QzUPsGTfZM){RzouQrtJcI = true;}
      if(ocVCeCwtNR == NjNzriBTqI){UANbfKdCaU = true;}
      if(qtGjUnfdLB == zmxtDmuWoA){uILpbKfFFP = true;}
      while(QzUPsGTfZM == MatePjlhxa){ZfrPbMlHpl = true;}
      while(NjNzriBTqI == NjNzriBTqI){OUCWHhGaRl = true;}
      while(zmxtDmuWoA == zmxtDmuWoA){pyfBVnCNbL = true;}
      if(XKizsizqJy == true){XKizsizqJy = false;}
      if(tLdugSOuEA == true){tLdugSOuEA = false;}
      if(CECqxdCaMF == true){CECqxdCaMF = false;}
      if(KwqYnDAOGJ == true){KwqYnDAOGJ = false;}
      if(iKJsNnIBMj == true){iKJsNnIBMj = false;}
      if(YzSnyTHrCP == true){YzSnyTHrCP = false;}
      if(gYdEmxTFHd == true){gYdEmxTFHd = false;}
      if(RzouQrtJcI == true){RzouQrtJcI = false;}
      if(UANbfKdCaU == true){UANbfKdCaU = false;}
      if(uILpbKfFFP == true){uILpbKfFFP = false;}
      if(TDthRYKWXF == true){TDthRYKWXF = false;}
      if(YyOsufLCXb == true){YyOsufLCXb = false;}
      if(TRdliJmySG == true){TRdliJmySG = false;}
      if(MnENoQGeJH == true){MnENoQGeJH = false;}
      if(AGeVuxtSuu == true){AGeVuxtSuu = false;}
      if(zdhcwCZHzI == true){zdhcwCZHzI = false;}
      if(kMDRsjsAEe == true){kMDRsjsAEe = false;}
      if(ZfrPbMlHpl == true){ZfrPbMlHpl = false;}
      if(OUCWHhGaRl == true){OUCWHhGaRl = false;}
      if(pyfBVnCNbL == true){pyfBVnCNbL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTSMLKHQED
{ 
  void TbbqfuSWHW()
  { 
      bool QkfbwAFoRH = false;
      bool BVRkITtnjZ = false;
      bool nKaYmmWPoL = false;
      bool NxZGuYfwbe = false;
      bool QpLPzAAhBI = false;
      bool XSTgPFKHoI = false;
      bool cozGtEwLpi = false;
      bool nyLFJyzKYl = false;
      bool mnOfmtdsqp = false;
      bool OYGTCapFVt = false;
      bool EorRUYGOXQ = false;
      bool GzhCVnaSSz = false;
      bool aDTAUPqrCh = false;
      bool ItodhxwwLN = false;
      bool nOUajOpExN = false;
      bool zWlVTBUrxF = false;
      bool hOLoHMKDUX = false;
      bool reHELLhsQF = false;
      bool YmunhkHSKf = false;
      bool cDyGfYDfSW = false;
      string PSFqgkVbpA;
      string XuVQDlyxoN;
      string JnUjgkcgiH;
      string XZRiERFuQL;
      string pZRlPCYWAs;
      string AJRKhbxUJu;
      string HoribxclLk;
      string fCfdXiViTe;
      string MGfpGNHHBc;
      string TkkVDAhiJS;
      string YmKONxcmmy;
      string FOAeiBICbN;
      string oVjhRtRKaW;
      string BlYBFYuRcJ;
      string kUTDWFjFlC;
      string qeHucDCcxS;
      string fSMPwTozZJ;
      string FqZScUBgKL;
      string KLXYeVedXB;
      string WSTJcRHEGD;
      if(PSFqgkVbpA == YmKONxcmmy){QkfbwAFoRH = true;}
      else if(YmKONxcmmy == PSFqgkVbpA){EorRUYGOXQ = true;}
      if(XuVQDlyxoN == FOAeiBICbN){BVRkITtnjZ = true;}
      else if(FOAeiBICbN == XuVQDlyxoN){GzhCVnaSSz = true;}
      if(JnUjgkcgiH == oVjhRtRKaW){nKaYmmWPoL = true;}
      else if(oVjhRtRKaW == JnUjgkcgiH){aDTAUPqrCh = true;}
      if(XZRiERFuQL == BlYBFYuRcJ){NxZGuYfwbe = true;}
      else if(BlYBFYuRcJ == XZRiERFuQL){ItodhxwwLN = true;}
      if(pZRlPCYWAs == kUTDWFjFlC){QpLPzAAhBI = true;}
      else if(kUTDWFjFlC == pZRlPCYWAs){nOUajOpExN = true;}
      if(AJRKhbxUJu == qeHucDCcxS){XSTgPFKHoI = true;}
      else if(qeHucDCcxS == AJRKhbxUJu){zWlVTBUrxF = true;}
      if(HoribxclLk == fSMPwTozZJ){cozGtEwLpi = true;}
      else if(fSMPwTozZJ == HoribxclLk){hOLoHMKDUX = true;}
      if(fCfdXiViTe == FqZScUBgKL){nyLFJyzKYl = true;}
      if(MGfpGNHHBc == KLXYeVedXB){mnOfmtdsqp = true;}
      if(TkkVDAhiJS == WSTJcRHEGD){OYGTCapFVt = true;}
      while(FqZScUBgKL == fCfdXiViTe){reHELLhsQF = true;}
      while(KLXYeVedXB == KLXYeVedXB){YmunhkHSKf = true;}
      while(WSTJcRHEGD == WSTJcRHEGD){cDyGfYDfSW = true;}
      if(QkfbwAFoRH == true){QkfbwAFoRH = false;}
      if(BVRkITtnjZ == true){BVRkITtnjZ = false;}
      if(nKaYmmWPoL == true){nKaYmmWPoL = false;}
      if(NxZGuYfwbe == true){NxZGuYfwbe = false;}
      if(QpLPzAAhBI == true){QpLPzAAhBI = false;}
      if(XSTgPFKHoI == true){XSTgPFKHoI = false;}
      if(cozGtEwLpi == true){cozGtEwLpi = false;}
      if(nyLFJyzKYl == true){nyLFJyzKYl = false;}
      if(mnOfmtdsqp == true){mnOfmtdsqp = false;}
      if(OYGTCapFVt == true){OYGTCapFVt = false;}
      if(EorRUYGOXQ == true){EorRUYGOXQ = false;}
      if(GzhCVnaSSz == true){GzhCVnaSSz = false;}
      if(aDTAUPqrCh == true){aDTAUPqrCh = false;}
      if(ItodhxwwLN == true){ItodhxwwLN = false;}
      if(nOUajOpExN == true){nOUajOpExN = false;}
      if(zWlVTBUrxF == true){zWlVTBUrxF = false;}
      if(hOLoHMKDUX == true){hOLoHMKDUX = false;}
      if(reHELLhsQF == true){reHELLhsQF = false;}
      if(YmunhkHSKf == true){YmunhkHSKf = false;}
      if(cDyGfYDfSW == true){cDyGfYDfSW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYGFMHHPIZ
{ 
  void TEZDBXFUNP()
  { 
      bool NHzEwyoErb = false;
      bool MFFdyHkIJE = false;
      bool CCUHGmAzka = false;
      bool TsZlkTAgrR = false;
      bool BlWqerjKxH = false;
      bool SFzczKlqyI = false;
      bool ypTQITeTsd = false;
      bool GDPrDPedbN = false;
      bool DoBdHNtwlZ = false;
      bool hJiiTLRFhL = false;
      bool NQRTAPoGZi = false;
      bool fHOjFInpJt = false;
      bool ZhgSuxUgYq = false;
      bool xZwQzmWgcr = false;
      bool YmWCtZtydL = false;
      bool WbwmleizYD = false;
      bool tIhhkGLyjS = false;
      bool kHMQVlLdYU = false;
      bool CVDMUVcIdU = false;
      bool DXIZxPEnRn = false;
      string DIAVVdXlpT;
      string DpsLRybMMY;
      string PtnBHxGsBp;
      string XlpEsDMVwK;
      string ZlYYUzmuUi;
      string NgOcCJTyOY;
      string XejzwQznSN;
      string kGQBydUPgH;
      string JLXScpXNCi;
      string jNGWltBZcD;
      string AybGxGPMdX;
      string nERHOMGQVF;
      string sklidXzsOD;
      string bulcGKiRVV;
      string ZLidueuzIZ;
      string mkEWJOMscZ;
      string HVxZwsRnAE;
      string couzegCHny;
      string bAkoPqqPTr;
      string xoowOENIhB;
      if(DIAVVdXlpT == AybGxGPMdX){NHzEwyoErb = true;}
      else if(AybGxGPMdX == DIAVVdXlpT){NQRTAPoGZi = true;}
      if(DpsLRybMMY == nERHOMGQVF){MFFdyHkIJE = true;}
      else if(nERHOMGQVF == DpsLRybMMY){fHOjFInpJt = true;}
      if(PtnBHxGsBp == sklidXzsOD){CCUHGmAzka = true;}
      else if(sklidXzsOD == PtnBHxGsBp){ZhgSuxUgYq = true;}
      if(XlpEsDMVwK == bulcGKiRVV){TsZlkTAgrR = true;}
      else if(bulcGKiRVV == XlpEsDMVwK){xZwQzmWgcr = true;}
      if(ZlYYUzmuUi == ZLidueuzIZ){BlWqerjKxH = true;}
      else if(ZLidueuzIZ == ZlYYUzmuUi){YmWCtZtydL = true;}
      if(NgOcCJTyOY == mkEWJOMscZ){SFzczKlqyI = true;}
      else if(mkEWJOMscZ == NgOcCJTyOY){WbwmleizYD = true;}
      if(XejzwQznSN == HVxZwsRnAE){ypTQITeTsd = true;}
      else if(HVxZwsRnAE == XejzwQznSN){tIhhkGLyjS = true;}
      if(kGQBydUPgH == couzegCHny){GDPrDPedbN = true;}
      if(JLXScpXNCi == bAkoPqqPTr){DoBdHNtwlZ = true;}
      if(jNGWltBZcD == xoowOENIhB){hJiiTLRFhL = true;}
      while(couzegCHny == kGQBydUPgH){kHMQVlLdYU = true;}
      while(bAkoPqqPTr == bAkoPqqPTr){CVDMUVcIdU = true;}
      while(xoowOENIhB == xoowOENIhB){DXIZxPEnRn = true;}
      if(NHzEwyoErb == true){NHzEwyoErb = false;}
      if(MFFdyHkIJE == true){MFFdyHkIJE = false;}
      if(CCUHGmAzka == true){CCUHGmAzka = false;}
      if(TsZlkTAgrR == true){TsZlkTAgrR = false;}
      if(BlWqerjKxH == true){BlWqerjKxH = false;}
      if(SFzczKlqyI == true){SFzczKlqyI = false;}
      if(ypTQITeTsd == true){ypTQITeTsd = false;}
      if(GDPrDPedbN == true){GDPrDPedbN = false;}
      if(DoBdHNtwlZ == true){DoBdHNtwlZ = false;}
      if(hJiiTLRFhL == true){hJiiTLRFhL = false;}
      if(NQRTAPoGZi == true){NQRTAPoGZi = false;}
      if(fHOjFInpJt == true){fHOjFInpJt = false;}
      if(ZhgSuxUgYq == true){ZhgSuxUgYq = false;}
      if(xZwQzmWgcr == true){xZwQzmWgcr = false;}
      if(YmWCtZtydL == true){YmWCtZtydL = false;}
      if(WbwmleizYD == true){WbwmleizYD = false;}
      if(tIhhkGLyjS == true){tIhhkGLyjS = false;}
      if(kHMQVlLdYU == true){kHMQVlLdYU = false;}
      if(CVDMUVcIdU == true){CVDMUVcIdU = false;}
      if(DXIZxPEnRn == true){DXIZxPEnRn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKKCBFOCSN
{ 
  void niHSRYiYrK()
  { 
      bool MEYbmxfbyo = false;
      bool GgflXLHqIZ = false;
      bool ZuusXqOtyc = false;
      bool ijApRDdggX = false;
      bool cizyFmniCM = false;
      bool kCOBLQIfEw = false;
      bool hlcUFVfpTT = false;
      bool haKkwqwwnk = false;
      bool DfqkrgVzdA = false;
      bool tyckoqFdsi = false;
      bool GxOieKqcEU = false;
      bool UMqSrCtrcY = false;
      bool AgLTYjxZwE = false;
      bool lRDFdFRHGg = false;
      bool oruIfhGJrm = false;
      bool xNBTiZltJt = false;
      bool MQgziDIlom = false;
      bool jlkuiHlCmq = false;
      bool cnhIHYQiWD = false;
      bool TWxLUYLuZb = false;
      string itUzGdDBXQ;
      string iSbqGBkMNS;
      string bWLYTKGtob;
      string bRXkbCZqoJ;
      string MoFpSTkWGE;
      string qUhngLhufw;
      string XJLunRtpPE;
      string asXEGmRVGz;
      string YjmjkHijEP;
      string TdLrlDcJCA;
      string YuHBdxwdht;
      string sMofWmVbKg;
      string iKlzkxheRD;
      string KISFadbkGn;
      string KFCKWGneVy;
      string hByUROIIQf;
      string ORLdijtiFs;
      string KjUWWcIbbd;
      string IDJTVJKynL;
      string UTUaYstXal;
      if(itUzGdDBXQ == YuHBdxwdht){MEYbmxfbyo = true;}
      else if(YuHBdxwdht == itUzGdDBXQ){GxOieKqcEU = true;}
      if(iSbqGBkMNS == sMofWmVbKg){GgflXLHqIZ = true;}
      else if(sMofWmVbKg == iSbqGBkMNS){UMqSrCtrcY = true;}
      if(bWLYTKGtob == iKlzkxheRD){ZuusXqOtyc = true;}
      else if(iKlzkxheRD == bWLYTKGtob){AgLTYjxZwE = true;}
      if(bRXkbCZqoJ == KISFadbkGn){ijApRDdggX = true;}
      else if(KISFadbkGn == bRXkbCZqoJ){lRDFdFRHGg = true;}
      if(MoFpSTkWGE == KFCKWGneVy){cizyFmniCM = true;}
      else if(KFCKWGneVy == MoFpSTkWGE){oruIfhGJrm = true;}
      if(qUhngLhufw == hByUROIIQf){kCOBLQIfEw = true;}
      else if(hByUROIIQf == qUhngLhufw){xNBTiZltJt = true;}
      if(XJLunRtpPE == ORLdijtiFs){hlcUFVfpTT = true;}
      else if(ORLdijtiFs == XJLunRtpPE){MQgziDIlom = true;}
      if(asXEGmRVGz == KjUWWcIbbd){haKkwqwwnk = true;}
      if(YjmjkHijEP == IDJTVJKynL){DfqkrgVzdA = true;}
      if(TdLrlDcJCA == UTUaYstXal){tyckoqFdsi = true;}
      while(KjUWWcIbbd == asXEGmRVGz){jlkuiHlCmq = true;}
      while(IDJTVJKynL == IDJTVJKynL){cnhIHYQiWD = true;}
      while(UTUaYstXal == UTUaYstXal){TWxLUYLuZb = true;}
      if(MEYbmxfbyo == true){MEYbmxfbyo = false;}
      if(GgflXLHqIZ == true){GgflXLHqIZ = false;}
      if(ZuusXqOtyc == true){ZuusXqOtyc = false;}
      if(ijApRDdggX == true){ijApRDdggX = false;}
      if(cizyFmniCM == true){cizyFmniCM = false;}
      if(kCOBLQIfEw == true){kCOBLQIfEw = false;}
      if(hlcUFVfpTT == true){hlcUFVfpTT = false;}
      if(haKkwqwwnk == true){haKkwqwwnk = false;}
      if(DfqkrgVzdA == true){DfqkrgVzdA = false;}
      if(tyckoqFdsi == true){tyckoqFdsi = false;}
      if(GxOieKqcEU == true){GxOieKqcEU = false;}
      if(UMqSrCtrcY == true){UMqSrCtrcY = false;}
      if(AgLTYjxZwE == true){AgLTYjxZwE = false;}
      if(lRDFdFRHGg == true){lRDFdFRHGg = false;}
      if(oruIfhGJrm == true){oruIfhGJrm = false;}
      if(xNBTiZltJt == true){xNBTiZltJt = false;}
      if(MQgziDIlom == true){MQgziDIlom = false;}
      if(jlkuiHlCmq == true){jlkuiHlCmq = false;}
      if(cnhIHYQiWD == true){cnhIHYQiWD = false;}
      if(TWxLUYLuZb == true){TWxLUYLuZb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGGJVYEZXF
{ 
  void SeEUcYpqhn()
  { 
      bool NYtipXfgOu = false;
      bool friNHuaPON = false;
      bool HysQLtyDYr = false;
      bool TywLqSjzTS = false;
      bool tfDedMeFqi = false;
      bool xocCKOedXu = false;
      bool ZbHWbgwWWo = false;
      bool KauuTauNlz = false;
      bool OsMptdUsAc = false;
      bool mGaYsRYgDw = false;
      bool PHiCXWshij = false;
      bool TQqYfgPQcx = false;
      bool MDWsBEzWBB = false;
      bool BNKoiHKJRX = false;
      bool klJQIWOCrM = false;
      bool CHEFjLkoAT = false;
      bool WVfghFFCoY = false;
      bool VFzFLZsFke = false;
      bool pxeoztJEEW = false;
      bool WUJyBPGchD = false;
      string wWgZsmRncz;
      string wbXrQYBwBQ;
      string RheDbgDXEk;
      string afBAUliYmO;
      string oVmDlkxAhW;
      string EBTPuOqdxL;
      string jtiqYPZXWd;
      string obJlbwtbQq;
      string jCpggZMlEG;
      string tFbaetludW;
      string KYcDhbqgmy;
      string TPNGagECKy;
      string DnSQjiAhHg;
      string KzysfKZlyF;
      string heyFmerUzx;
      string pjkeTVFMSz;
      string aJZFnURTaQ;
      string HRDEQXpNdF;
      string qeiJqaNSZJ;
      string ENTzeYErQR;
      if(wWgZsmRncz == KYcDhbqgmy){NYtipXfgOu = true;}
      else if(KYcDhbqgmy == wWgZsmRncz){PHiCXWshij = true;}
      if(wbXrQYBwBQ == TPNGagECKy){friNHuaPON = true;}
      else if(TPNGagECKy == wbXrQYBwBQ){TQqYfgPQcx = true;}
      if(RheDbgDXEk == DnSQjiAhHg){HysQLtyDYr = true;}
      else if(DnSQjiAhHg == RheDbgDXEk){MDWsBEzWBB = true;}
      if(afBAUliYmO == KzysfKZlyF){TywLqSjzTS = true;}
      else if(KzysfKZlyF == afBAUliYmO){BNKoiHKJRX = true;}
      if(oVmDlkxAhW == heyFmerUzx){tfDedMeFqi = true;}
      else if(heyFmerUzx == oVmDlkxAhW){klJQIWOCrM = true;}
      if(EBTPuOqdxL == pjkeTVFMSz){xocCKOedXu = true;}
      else if(pjkeTVFMSz == EBTPuOqdxL){CHEFjLkoAT = true;}
      if(jtiqYPZXWd == aJZFnURTaQ){ZbHWbgwWWo = true;}
      else if(aJZFnURTaQ == jtiqYPZXWd){WVfghFFCoY = true;}
      if(obJlbwtbQq == HRDEQXpNdF){KauuTauNlz = true;}
      if(jCpggZMlEG == qeiJqaNSZJ){OsMptdUsAc = true;}
      if(tFbaetludW == ENTzeYErQR){mGaYsRYgDw = true;}
      while(HRDEQXpNdF == obJlbwtbQq){VFzFLZsFke = true;}
      while(qeiJqaNSZJ == qeiJqaNSZJ){pxeoztJEEW = true;}
      while(ENTzeYErQR == ENTzeYErQR){WUJyBPGchD = true;}
      if(NYtipXfgOu == true){NYtipXfgOu = false;}
      if(friNHuaPON == true){friNHuaPON = false;}
      if(HysQLtyDYr == true){HysQLtyDYr = false;}
      if(TywLqSjzTS == true){TywLqSjzTS = false;}
      if(tfDedMeFqi == true){tfDedMeFqi = false;}
      if(xocCKOedXu == true){xocCKOedXu = false;}
      if(ZbHWbgwWWo == true){ZbHWbgwWWo = false;}
      if(KauuTauNlz == true){KauuTauNlz = false;}
      if(OsMptdUsAc == true){OsMptdUsAc = false;}
      if(mGaYsRYgDw == true){mGaYsRYgDw = false;}
      if(PHiCXWshij == true){PHiCXWshij = false;}
      if(TQqYfgPQcx == true){TQqYfgPQcx = false;}
      if(MDWsBEzWBB == true){MDWsBEzWBB = false;}
      if(BNKoiHKJRX == true){BNKoiHKJRX = false;}
      if(klJQIWOCrM == true){klJQIWOCrM = false;}
      if(CHEFjLkoAT == true){CHEFjLkoAT = false;}
      if(WVfghFFCoY == true){WVfghFFCoY = false;}
      if(VFzFLZsFke == true){VFzFLZsFke = false;}
      if(pxeoztJEEW == true){pxeoztJEEW = false;}
      if(WUJyBPGchD == true){WUJyBPGchD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQBSWMWZOJ
{ 
  void NyoffqChHu()
  { 
      bool fqahzCuJmG = false;
      bool EzSQLJxgzM = false;
      bool qibHaoJeaX = false;
      bool kxhqTLcHyn = false;
      bool loiNRTTKoa = false;
      bool MeUuRwOSHK = false;
      bool rPiPUGQbxA = false;
      bool goiKaCzOoG = false;
      bool UzpzKGbmZX = false;
      bool xJAmuVGTsK = false;
      bool CrNotWuKTP = false;
      bool wAcApsYiEN = false;
      bool edCYCWouOE = false;
      bool ufUeDbkBEn = false;
      bool KRSJawfzxB = false;
      bool xWPefYpnlW = false;
      bool gAuOTQeywN = false;
      bool IXdPCMLryF = false;
      bool qpxMHYPpye = false;
      bool lxOhGKVDpJ = false;
      string jUmKMxzwMw;
      string bHlhxsYZru;
      string bUdAxSuWbd;
      string LmAoYatnZK;
      string wsRkhGcZZE;
      string HHnTkOqlNs;
      string CbTijnHwIV;
      string zjAhyhDrRq;
      string pVxWWEyfEK;
      string jIagHTYhAs;
      string ygQDFWGGUC;
      string LyUVDfexMf;
      string pbqylpITZe;
      string IUrXrIEsQz;
      string xrKBzlmEcb;
      string nbVUDVoRRP;
      string NmfpspFwdt;
      string blgMhxRpzA;
      string DDpyqgyWTV;
      string TlbBkJMTHI;
      if(jUmKMxzwMw == ygQDFWGGUC){fqahzCuJmG = true;}
      else if(ygQDFWGGUC == jUmKMxzwMw){CrNotWuKTP = true;}
      if(bHlhxsYZru == LyUVDfexMf){EzSQLJxgzM = true;}
      else if(LyUVDfexMf == bHlhxsYZru){wAcApsYiEN = true;}
      if(bUdAxSuWbd == pbqylpITZe){qibHaoJeaX = true;}
      else if(pbqylpITZe == bUdAxSuWbd){edCYCWouOE = true;}
      if(LmAoYatnZK == IUrXrIEsQz){kxhqTLcHyn = true;}
      else if(IUrXrIEsQz == LmAoYatnZK){ufUeDbkBEn = true;}
      if(wsRkhGcZZE == xrKBzlmEcb){loiNRTTKoa = true;}
      else if(xrKBzlmEcb == wsRkhGcZZE){KRSJawfzxB = true;}
      if(HHnTkOqlNs == nbVUDVoRRP){MeUuRwOSHK = true;}
      else if(nbVUDVoRRP == HHnTkOqlNs){xWPefYpnlW = true;}
      if(CbTijnHwIV == NmfpspFwdt){rPiPUGQbxA = true;}
      else if(NmfpspFwdt == CbTijnHwIV){gAuOTQeywN = true;}
      if(zjAhyhDrRq == blgMhxRpzA){goiKaCzOoG = true;}
      if(pVxWWEyfEK == DDpyqgyWTV){UzpzKGbmZX = true;}
      if(jIagHTYhAs == TlbBkJMTHI){xJAmuVGTsK = true;}
      while(blgMhxRpzA == zjAhyhDrRq){IXdPCMLryF = true;}
      while(DDpyqgyWTV == DDpyqgyWTV){qpxMHYPpye = true;}
      while(TlbBkJMTHI == TlbBkJMTHI){lxOhGKVDpJ = true;}
      if(fqahzCuJmG == true){fqahzCuJmG = false;}
      if(EzSQLJxgzM == true){EzSQLJxgzM = false;}
      if(qibHaoJeaX == true){qibHaoJeaX = false;}
      if(kxhqTLcHyn == true){kxhqTLcHyn = false;}
      if(loiNRTTKoa == true){loiNRTTKoa = false;}
      if(MeUuRwOSHK == true){MeUuRwOSHK = false;}
      if(rPiPUGQbxA == true){rPiPUGQbxA = false;}
      if(goiKaCzOoG == true){goiKaCzOoG = false;}
      if(UzpzKGbmZX == true){UzpzKGbmZX = false;}
      if(xJAmuVGTsK == true){xJAmuVGTsK = false;}
      if(CrNotWuKTP == true){CrNotWuKTP = false;}
      if(wAcApsYiEN == true){wAcApsYiEN = false;}
      if(edCYCWouOE == true){edCYCWouOE = false;}
      if(ufUeDbkBEn == true){ufUeDbkBEn = false;}
      if(KRSJawfzxB == true){KRSJawfzxB = false;}
      if(xWPefYpnlW == true){xWPefYpnlW = false;}
      if(gAuOTQeywN == true){gAuOTQeywN = false;}
      if(IXdPCMLryF == true){IXdPCMLryF = false;}
      if(qpxMHYPpye == true){qpxMHYPpye = false;}
      if(lxOhGKVDpJ == true){lxOhGKVDpJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFXLDJQZAT
{ 
  void JncYTtHxwL()
  { 
      bool iftIpxjayq = false;
      bool oUaEDVgBKj = false;
      bool URbVdZXIcZ = false;
      bool SOzEuTsILG = false;
      bool WsWCmuwnJh = false;
      bool agFWIREXdQ = false;
      bool ZayXYZUWIi = false;
      bool cYpEMbuYii = false;
      bool cjzuzlJcwd = false;
      bool PUdugwuydM = false;
      bool aZeZEBpBJg = false;
      bool WeoumoaCYl = false;
      bool QrZeTIuuXQ = false;
      bool gwuVHCEZqx = false;
      bool wISOHkehHq = false;
      bool UrZqwizAGw = false;
      bool GudsAZiTmj = false;
      bool kBLapIYLWh = false;
      bool cMmfwnVEZY = false;
      bool DETtqAeZOg = false;
      string hbqAlGbISO;
      string urhVyDjLur;
      string QiKOcYlTuS;
      string AeUUjfnMDm;
      string QIDkwBxuEV;
      string NaAIOyQbXN;
      string UINzOQWNlR;
      string OWIHaIfZSb;
      string bpOYEYdMFk;
      string OLooSItDWe;
      string diJlHqSrgF;
      string SqJwldsnto;
      string lJHACCgToS;
      string NcDmxrgcRN;
      string GkezSXCsCn;
      string OGIgrUbIjE;
      string JyDOronVyt;
      string xQWghBeHhe;
      string AmQBDHUVtc;
      string PXsNDIhPHc;
      if(hbqAlGbISO == diJlHqSrgF){iftIpxjayq = true;}
      else if(diJlHqSrgF == hbqAlGbISO){aZeZEBpBJg = true;}
      if(urhVyDjLur == SqJwldsnto){oUaEDVgBKj = true;}
      else if(SqJwldsnto == urhVyDjLur){WeoumoaCYl = true;}
      if(QiKOcYlTuS == lJHACCgToS){URbVdZXIcZ = true;}
      else if(lJHACCgToS == QiKOcYlTuS){QrZeTIuuXQ = true;}
      if(AeUUjfnMDm == NcDmxrgcRN){SOzEuTsILG = true;}
      else if(NcDmxrgcRN == AeUUjfnMDm){gwuVHCEZqx = true;}
      if(QIDkwBxuEV == GkezSXCsCn){WsWCmuwnJh = true;}
      else if(GkezSXCsCn == QIDkwBxuEV){wISOHkehHq = true;}
      if(NaAIOyQbXN == OGIgrUbIjE){agFWIREXdQ = true;}
      else if(OGIgrUbIjE == NaAIOyQbXN){UrZqwizAGw = true;}
      if(UINzOQWNlR == JyDOronVyt){ZayXYZUWIi = true;}
      else if(JyDOronVyt == UINzOQWNlR){GudsAZiTmj = true;}
      if(OWIHaIfZSb == xQWghBeHhe){cYpEMbuYii = true;}
      if(bpOYEYdMFk == AmQBDHUVtc){cjzuzlJcwd = true;}
      if(OLooSItDWe == PXsNDIhPHc){PUdugwuydM = true;}
      while(xQWghBeHhe == OWIHaIfZSb){kBLapIYLWh = true;}
      while(AmQBDHUVtc == AmQBDHUVtc){cMmfwnVEZY = true;}
      while(PXsNDIhPHc == PXsNDIhPHc){DETtqAeZOg = true;}
      if(iftIpxjayq == true){iftIpxjayq = false;}
      if(oUaEDVgBKj == true){oUaEDVgBKj = false;}
      if(URbVdZXIcZ == true){URbVdZXIcZ = false;}
      if(SOzEuTsILG == true){SOzEuTsILG = false;}
      if(WsWCmuwnJh == true){WsWCmuwnJh = false;}
      if(agFWIREXdQ == true){agFWIREXdQ = false;}
      if(ZayXYZUWIi == true){ZayXYZUWIi = false;}
      if(cYpEMbuYii == true){cYpEMbuYii = false;}
      if(cjzuzlJcwd == true){cjzuzlJcwd = false;}
      if(PUdugwuydM == true){PUdugwuydM = false;}
      if(aZeZEBpBJg == true){aZeZEBpBJg = false;}
      if(WeoumoaCYl == true){WeoumoaCYl = false;}
      if(QrZeTIuuXQ == true){QrZeTIuuXQ = false;}
      if(gwuVHCEZqx == true){gwuVHCEZqx = false;}
      if(wISOHkehHq == true){wISOHkehHq = false;}
      if(UrZqwizAGw == true){UrZqwizAGw = false;}
      if(GudsAZiTmj == true){GudsAZiTmj = false;}
      if(kBLapIYLWh == true){kBLapIYLWh = false;}
      if(cMmfwnVEZY == true){cMmfwnVEZY = false;}
      if(DETtqAeZOg == true){DETtqAeZOg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EFEOGRNLKM
{ 
  void fdAqwEIVOc()
  { 
      bool nFmELHauhi = false;
      bool oLyQgotrgO = false;
      bool ZdHzGsErit = false;
      bool gCGetVhaal = false;
      bool QqxxxMXmqW = false;
      bool biqupKxnxS = false;
      bool CiLnClFTVK = false;
      bool GSRuyigJCt = false;
      bool URALRyKLoj = false;
      bool XsdIigeIuK = false;
      bool GEQfPJQwxG = false;
      bool dnlDxkizWE = false;
      bool atdklNoJLQ = false;
      bool EXNqmQATuH = false;
      bool gONiGjHZKy = false;
      bool yflqjMZetC = false;
      bool THjfCFZuQg = false;
      bool kODOWLfueC = false;
      bool GOzNRYkWGZ = false;
      bool pUZsnYdggA = false;
      string WaEgMIdYmC;
      string sWQiceBsAP;
      string VuyJzQqfQp;
      string FYKZsMCtNa;
      string bxHIbEDHwG;
      string MUVZQbcuhu;
      string QxHxxTLqoQ;
      string cGfZnYmogt;
      string NijKdjDkIR;
      string jHLRJdoKLI;
      string rLRfdFnwkq;
      string omNmhgNxTM;
      string QahXfUtOPK;
      string jcdYCCQEgX;
      string wHzRbxsYjb;
      string QqqyrQctzI;
      string LYfaHLInkf;
      string PJQuQIbQui;
      string aVemsrlegl;
      string YWEXMWbYKQ;
      if(WaEgMIdYmC == rLRfdFnwkq){nFmELHauhi = true;}
      else if(rLRfdFnwkq == WaEgMIdYmC){GEQfPJQwxG = true;}
      if(sWQiceBsAP == omNmhgNxTM){oLyQgotrgO = true;}
      else if(omNmhgNxTM == sWQiceBsAP){dnlDxkizWE = true;}
      if(VuyJzQqfQp == QahXfUtOPK){ZdHzGsErit = true;}
      else if(QahXfUtOPK == VuyJzQqfQp){atdklNoJLQ = true;}
      if(FYKZsMCtNa == jcdYCCQEgX){gCGetVhaal = true;}
      else if(jcdYCCQEgX == FYKZsMCtNa){EXNqmQATuH = true;}
      if(bxHIbEDHwG == wHzRbxsYjb){QqxxxMXmqW = true;}
      else if(wHzRbxsYjb == bxHIbEDHwG){gONiGjHZKy = true;}
      if(MUVZQbcuhu == QqqyrQctzI){biqupKxnxS = true;}
      else if(QqqyrQctzI == MUVZQbcuhu){yflqjMZetC = true;}
      if(QxHxxTLqoQ == LYfaHLInkf){CiLnClFTVK = true;}
      else if(LYfaHLInkf == QxHxxTLqoQ){THjfCFZuQg = true;}
      if(cGfZnYmogt == PJQuQIbQui){GSRuyigJCt = true;}
      if(NijKdjDkIR == aVemsrlegl){URALRyKLoj = true;}
      if(jHLRJdoKLI == YWEXMWbYKQ){XsdIigeIuK = true;}
      while(PJQuQIbQui == cGfZnYmogt){kODOWLfueC = true;}
      while(aVemsrlegl == aVemsrlegl){GOzNRYkWGZ = true;}
      while(YWEXMWbYKQ == YWEXMWbYKQ){pUZsnYdggA = true;}
      if(nFmELHauhi == true){nFmELHauhi = false;}
      if(oLyQgotrgO == true){oLyQgotrgO = false;}
      if(ZdHzGsErit == true){ZdHzGsErit = false;}
      if(gCGetVhaal == true){gCGetVhaal = false;}
      if(QqxxxMXmqW == true){QqxxxMXmqW = false;}
      if(biqupKxnxS == true){biqupKxnxS = false;}
      if(CiLnClFTVK == true){CiLnClFTVK = false;}
      if(GSRuyigJCt == true){GSRuyigJCt = false;}
      if(URALRyKLoj == true){URALRyKLoj = false;}
      if(XsdIigeIuK == true){XsdIigeIuK = false;}
      if(GEQfPJQwxG == true){GEQfPJQwxG = false;}
      if(dnlDxkizWE == true){dnlDxkizWE = false;}
      if(atdklNoJLQ == true){atdklNoJLQ = false;}
      if(EXNqmQATuH == true){EXNqmQATuH = false;}
      if(gONiGjHZKy == true){gONiGjHZKy = false;}
      if(yflqjMZetC == true){yflqjMZetC = false;}
      if(THjfCFZuQg == true){THjfCFZuQg = false;}
      if(kODOWLfueC == true){kODOWLfueC = false;}
      if(GOzNRYkWGZ == true){GOzNRYkWGZ = false;}
      if(pUZsnYdggA == true){pUZsnYdggA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEDUSPWHFS
{ 
  void eUzoVwECfx()
  { 
      bool wKLUVOrmbj = false;
      bool BbfdyAAsWq = false;
      bool KGRqVhCPll = false;
      bool VgTixeooIY = false;
      bool poXOdNnWXE = false;
      bool BoteMorUzm = false;
      bool MbApOUHxfS = false;
      bool LLjyBViDMH = false;
      bool teqhjfloWI = false;
      bool mToVMNngAJ = false;
      bool FpqErpEwdp = false;
      bool GoHqrgkSFh = false;
      bool hSaWfqVOlm = false;
      bool gBCDBDnlot = false;
      bool apKfCxMxce = false;
      bool cVaRbmPTYB = false;
      bool TpJpJElEpo = false;
      bool sydLGqHuUi = false;
      bool eXlGKLajaO = false;
      bool nTNnZkfUVy = false;
      string jLNWaJBhuS;
      string nlhGxPYatO;
      string eFJZJrmhTD;
      string FwOLjaSAiG;
      string NpUcoAcaoC;
      string KrOSbeCnMi;
      string WTOqNqXWVV;
      string wXqmAojfjI;
      string OLrQsMguiE;
      string YemAjtbcPx;
      string cGETFlAaRm;
      string tWDDTKaxyA;
      string JbmQwRjpDG;
      string MGPlfIHXLG;
      string MFcwKCbifY;
      string SdePnASmXn;
      string BKXLZmGQXL;
      string DDlqmDypGt;
      string pAJenhbzyf;
      string pUAWFBhRWX;
      if(jLNWaJBhuS == cGETFlAaRm){wKLUVOrmbj = true;}
      else if(cGETFlAaRm == jLNWaJBhuS){FpqErpEwdp = true;}
      if(nlhGxPYatO == tWDDTKaxyA){BbfdyAAsWq = true;}
      else if(tWDDTKaxyA == nlhGxPYatO){GoHqrgkSFh = true;}
      if(eFJZJrmhTD == JbmQwRjpDG){KGRqVhCPll = true;}
      else if(JbmQwRjpDG == eFJZJrmhTD){hSaWfqVOlm = true;}
      if(FwOLjaSAiG == MGPlfIHXLG){VgTixeooIY = true;}
      else if(MGPlfIHXLG == FwOLjaSAiG){gBCDBDnlot = true;}
      if(NpUcoAcaoC == MFcwKCbifY){poXOdNnWXE = true;}
      else if(MFcwKCbifY == NpUcoAcaoC){apKfCxMxce = true;}
      if(KrOSbeCnMi == SdePnASmXn){BoteMorUzm = true;}
      else if(SdePnASmXn == KrOSbeCnMi){cVaRbmPTYB = true;}
      if(WTOqNqXWVV == BKXLZmGQXL){MbApOUHxfS = true;}
      else if(BKXLZmGQXL == WTOqNqXWVV){TpJpJElEpo = true;}
      if(wXqmAojfjI == DDlqmDypGt){LLjyBViDMH = true;}
      if(OLrQsMguiE == pAJenhbzyf){teqhjfloWI = true;}
      if(YemAjtbcPx == pUAWFBhRWX){mToVMNngAJ = true;}
      while(DDlqmDypGt == wXqmAojfjI){sydLGqHuUi = true;}
      while(pAJenhbzyf == pAJenhbzyf){eXlGKLajaO = true;}
      while(pUAWFBhRWX == pUAWFBhRWX){nTNnZkfUVy = true;}
      if(wKLUVOrmbj == true){wKLUVOrmbj = false;}
      if(BbfdyAAsWq == true){BbfdyAAsWq = false;}
      if(KGRqVhCPll == true){KGRqVhCPll = false;}
      if(VgTixeooIY == true){VgTixeooIY = false;}
      if(poXOdNnWXE == true){poXOdNnWXE = false;}
      if(BoteMorUzm == true){BoteMorUzm = false;}
      if(MbApOUHxfS == true){MbApOUHxfS = false;}
      if(LLjyBViDMH == true){LLjyBViDMH = false;}
      if(teqhjfloWI == true){teqhjfloWI = false;}
      if(mToVMNngAJ == true){mToVMNngAJ = false;}
      if(FpqErpEwdp == true){FpqErpEwdp = false;}
      if(GoHqrgkSFh == true){GoHqrgkSFh = false;}
      if(hSaWfqVOlm == true){hSaWfqVOlm = false;}
      if(gBCDBDnlot == true){gBCDBDnlot = false;}
      if(apKfCxMxce == true){apKfCxMxce = false;}
      if(cVaRbmPTYB == true){cVaRbmPTYB = false;}
      if(TpJpJElEpo == true){TpJpJElEpo = false;}
      if(sydLGqHuUi == true){sydLGqHuUi = false;}
      if(eXlGKLajaO == true){eXlGKLajaO = false;}
      if(nTNnZkfUVy == true){nTNnZkfUVy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVLRFVJJIC
{ 
  void mwiihtspyz()
  { 
      bool fBkemyLyqo = false;
      bool eKzaADPSNU = false;
      bool oTkEaMOdDX = false;
      bool SLFrAyujpW = false;
      bool BeuAkVrgaY = false;
      bool rmAbpMQfDa = false;
      bool igtSWSEGZC = false;
      bool IebpTKYjTF = false;
      bool ThDeffKdBn = false;
      bool gPfPmTjbdS = false;
      bool QkGYQMKKHf = false;
      bool mfMyHBdPmq = false;
      bool HZFlUrzMCz = false;
      bool axGBnhadNS = false;
      bool UAVVABCgHl = false;
      bool pTnmKqfUDX = false;
      bool MyHIFoZLKY = false;
      bool azBTWGDikT = false;
      bool pSEQJGJSpw = false;
      bool BGapGVsNPK = false;
      string uYAPxkQMRH;
      string QqNhhTRIYh;
      string VlObZKEmWm;
      string bUuljMgjXq;
      string jpDSiaVswQ;
      string DNAXsJKXom;
      string fcodeuwaxU;
      string mgjhxfhurz;
      string nLpGjOUXsZ;
      string BJujLHAYmn;
      string duuadWcSZN;
      string aOfozTlitQ;
      string aYhXTclzVp;
      string eIIEUsPPbN;
      string kCxeymcFkq;
      string UReWNFMXHA;
      string jdwihSGbUG;
      string EWGgeXaCYg;
      string zfOdUMclpP;
      string frHbcHFOwf;
      if(uYAPxkQMRH == duuadWcSZN){fBkemyLyqo = true;}
      else if(duuadWcSZN == uYAPxkQMRH){QkGYQMKKHf = true;}
      if(QqNhhTRIYh == aOfozTlitQ){eKzaADPSNU = true;}
      else if(aOfozTlitQ == QqNhhTRIYh){mfMyHBdPmq = true;}
      if(VlObZKEmWm == aYhXTclzVp){oTkEaMOdDX = true;}
      else if(aYhXTclzVp == VlObZKEmWm){HZFlUrzMCz = true;}
      if(bUuljMgjXq == eIIEUsPPbN){SLFrAyujpW = true;}
      else if(eIIEUsPPbN == bUuljMgjXq){axGBnhadNS = true;}
      if(jpDSiaVswQ == kCxeymcFkq){BeuAkVrgaY = true;}
      else if(kCxeymcFkq == jpDSiaVswQ){UAVVABCgHl = true;}
      if(DNAXsJKXom == UReWNFMXHA){rmAbpMQfDa = true;}
      else if(UReWNFMXHA == DNAXsJKXom){pTnmKqfUDX = true;}
      if(fcodeuwaxU == jdwihSGbUG){igtSWSEGZC = true;}
      else if(jdwihSGbUG == fcodeuwaxU){MyHIFoZLKY = true;}
      if(mgjhxfhurz == EWGgeXaCYg){IebpTKYjTF = true;}
      if(nLpGjOUXsZ == zfOdUMclpP){ThDeffKdBn = true;}
      if(BJujLHAYmn == frHbcHFOwf){gPfPmTjbdS = true;}
      while(EWGgeXaCYg == mgjhxfhurz){azBTWGDikT = true;}
      while(zfOdUMclpP == zfOdUMclpP){pSEQJGJSpw = true;}
      while(frHbcHFOwf == frHbcHFOwf){BGapGVsNPK = true;}
      if(fBkemyLyqo == true){fBkemyLyqo = false;}
      if(eKzaADPSNU == true){eKzaADPSNU = false;}
      if(oTkEaMOdDX == true){oTkEaMOdDX = false;}
      if(SLFrAyujpW == true){SLFrAyujpW = false;}
      if(BeuAkVrgaY == true){BeuAkVrgaY = false;}
      if(rmAbpMQfDa == true){rmAbpMQfDa = false;}
      if(igtSWSEGZC == true){igtSWSEGZC = false;}
      if(IebpTKYjTF == true){IebpTKYjTF = false;}
      if(ThDeffKdBn == true){ThDeffKdBn = false;}
      if(gPfPmTjbdS == true){gPfPmTjbdS = false;}
      if(QkGYQMKKHf == true){QkGYQMKKHf = false;}
      if(mfMyHBdPmq == true){mfMyHBdPmq = false;}
      if(HZFlUrzMCz == true){HZFlUrzMCz = false;}
      if(axGBnhadNS == true){axGBnhadNS = false;}
      if(UAVVABCgHl == true){UAVVABCgHl = false;}
      if(pTnmKqfUDX == true){pTnmKqfUDX = false;}
      if(MyHIFoZLKY == true){MyHIFoZLKY = false;}
      if(azBTWGDikT == true){azBTWGDikT = false;}
      if(pSEQJGJSpw == true){pSEQJGJSpw = false;}
      if(BGapGVsNPK == true){BGapGVsNPK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXBRWJHBHF
{ 
  void nEJCIpccdu()
  { 
      bool uyXEBFsUJh = false;
      bool hoBbMweHEB = false;
      bool qXnFiRaTYV = false;
      bool oBTplxuPpK = false;
      bool ocBmXFEmqM = false;
      bool pgETZWJSVi = false;
      bool dZunsgULoP = false;
      bool AORsLOWAgd = false;
      bool MnbMfHwAPO = false;
      bool mctGgOgNtq = false;
      bool jsxbMbPKHL = false;
      bool AIlrVoyiHl = false;
      bool jUwabXTKMx = false;
      bool gJGosTqAAE = false;
      bool rlsDOeqCjq = false;
      bool QyFIHPxVzn = false;
      bool HEyKeqCwyC = false;
      bool yxiDtxarMx = false;
      bool fRaUfiDygc = false;
      bool WUALxmniYX = false;
      string dqStEDHzME;
      string aJHSkKdeWg;
      string NYVNHDaCpL;
      string UDKZExFfmq;
      string NLLwBdFmJQ;
      string RuxAkEVEmA;
      string bFJBjXyhOn;
      string ExqfTCMYLc;
      string xnrYsYFKnz;
      string bAsmOHCKMd;
      string fXXULTEQgi;
      string rwrJDnMkHL;
      string RnsOMDDERL;
      string zBMhxYPWMY;
      string UndEHeIjiZ;
      string uRDBLqdIII;
      string QzzUipjKLd;
      string YoXhqdJoHg;
      string uTUqQhyLVG;
      string tGOEIUoIUR;
      if(dqStEDHzME == fXXULTEQgi){uyXEBFsUJh = true;}
      else if(fXXULTEQgi == dqStEDHzME){jsxbMbPKHL = true;}
      if(aJHSkKdeWg == rwrJDnMkHL){hoBbMweHEB = true;}
      else if(rwrJDnMkHL == aJHSkKdeWg){AIlrVoyiHl = true;}
      if(NYVNHDaCpL == RnsOMDDERL){qXnFiRaTYV = true;}
      else if(RnsOMDDERL == NYVNHDaCpL){jUwabXTKMx = true;}
      if(UDKZExFfmq == zBMhxYPWMY){oBTplxuPpK = true;}
      else if(zBMhxYPWMY == UDKZExFfmq){gJGosTqAAE = true;}
      if(NLLwBdFmJQ == UndEHeIjiZ){ocBmXFEmqM = true;}
      else if(UndEHeIjiZ == NLLwBdFmJQ){rlsDOeqCjq = true;}
      if(RuxAkEVEmA == uRDBLqdIII){pgETZWJSVi = true;}
      else if(uRDBLqdIII == RuxAkEVEmA){QyFIHPxVzn = true;}
      if(bFJBjXyhOn == QzzUipjKLd){dZunsgULoP = true;}
      else if(QzzUipjKLd == bFJBjXyhOn){HEyKeqCwyC = true;}
      if(ExqfTCMYLc == YoXhqdJoHg){AORsLOWAgd = true;}
      if(xnrYsYFKnz == uTUqQhyLVG){MnbMfHwAPO = true;}
      if(bAsmOHCKMd == tGOEIUoIUR){mctGgOgNtq = true;}
      while(YoXhqdJoHg == ExqfTCMYLc){yxiDtxarMx = true;}
      while(uTUqQhyLVG == uTUqQhyLVG){fRaUfiDygc = true;}
      while(tGOEIUoIUR == tGOEIUoIUR){WUALxmniYX = true;}
      if(uyXEBFsUJh == true){uyXEBFsUJh = false;}
      if(hoBbMweHEB == true){hoBbMweHEB = false;}
      if(qXnFiRaTYV == true){qXnFiRaTYV = false;}
      if(oBTplxuPpK == true){oBTplxuPpK = false;}
      if(ocBmXFEmqM == true){ocBmXFEmqM = false;}
      if(pgETZWJSVi == true){pgETZWJSVi = false;}
      if(dZunsgULoP == true){dZunsgULoP = false;}
      if(AORsLOWAgd == true){AORsLOWAgd = false;}
      if(MnbMfHwAPO == true){MnbMfHwAPO = false;}
      if(mctGgOgNtq == true){mctGgOgNtq = false;}
      if(jsxbMbPKHL == true){jsxbMbPKHL = false;}
      if(AIlrVoyiHl == true){AIlrVoyiHl = false;}
      if(jUwabXTKMx == true){jUwabXTKMx = false;}
      if(gJGosTqAAE == true){gJGosTqAAE = false;}
      if(rlsDOeqCjq == true){rlsDOeqCjq = false;}
      if(QyFIHPxVzn == true){QyFIHPxVzn = false;}
      if(HEyKeqCwyC == true){HEyKeqCwyC = false;}
      if(yxiDtxarMx == true){yxiDtxarMx = false;}
      if(fRaUfiDygc == true){fRaUfiDygc = false;}
      if(WUALxmniYX == true){WUALxmniYX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICIUJTKGGZ
{ 
  void cqjSfKelQx()
  { 
      bool qKYRemxKKH = false;
      bool RnGTyjSXgN = false;
      bool NGjHQBkPGq = false;
      bool CORjYpYTaz = false;
      bool gHzNySGgzC = false;
      bool BLpbCjaRAc = false;
      bool ChDSEDWWuH = false;
      bool LzwhfFHVJy = false;
      bool tEPEpqYpgn = false;
      bool PGTxxzDfJt = false;
      bool wjlrqCOHww = false;
      bool cFICiyRycM = false;
      bool egoGrEeyjf = false;
      bool CaMOBJRXNm = false;
      bool cQtkKKyROy = false;
      bool gFCwOPufzl = false;
      bool XPWPtBrsAY = false;
      bool fsjpjOlEug = false;
      bool GMjkyxXPAl = false;
      bool OlXbPMsdpJ = false;
      string utQflVJUUZ;
      string iXUYnUVTMe;
      string SJAmlZPppL;
      string euUPgEPjbi;
      string SDYFfjnstX;
      string OYFtzktctL;
      string FTeJtnDFqj;
      string FlqcLPktHB;
      string kWuRwGoZQu;
      string JlpPcyYPLr;
      string giCKScgchi;
      string AAVrZiXMMm;
      string ycnuZSubzN;
      string qUiPTCUkyT;
      string ZMqguJQxos;
      string ZLDXsDuGjA;
      string hFcUreRFXX;
      string OlNrMlkGAQ;
      string BylFmeRKVQ;
      string HNBylUiWoP;
      if(utQflVJUUZ == giCKScgchi){qKYRemxKKH = true;}
      else if(giCKScgchi == utQflVJUUZ){wjlrqCOHww = true;}
      if(iXUYnUVTMe == AAVrZiXMMm){RnGTyjSXgN = true;}
      else if(AAVrZiXMMm == iXUYnUVTMe){cFICiyRycM = true;}
      if(SJAmlZPppL == ycnuZSubzN){NGjHQBkPGq = true;}
      else if(ycnuZSubzN == SJAmlZPppL){egoGrEeyjf = true;}
      if(euUPgEPjbi == qUiPTCUkyT){CORjYpYTaz = true;}
      else if(qUiPTCUkyT == euUPgEPjbi){CaMOBJRXNm = true;}
      if(SDYFfjnstX == ZMqguJQxos){gHzNySGgzC = true;}
      else if(ZMqguJQxos == SDYFfjnstX){cQtkKKyROy = true;}
      if(OYFtzktctL == ZLDXsDuGjA){BLpbCjaRAc = true;}
      else if(ZLDXsDuGjA == OYFtzktctL){gFCwOPufzl = true;}
      if(FTeJtnDFqj == hFcUreRFXX){ChDSEDWWuH = true;}
      else if(hFcUreRFXX == FTeJtnDFqj){XPWPtBrsAY = true;}
      if(FlqcLPktHB == OlNrMlkGAQ){LzwhfFHVJy = true;}
      if(kWuRwGoZQu == BylFmeRKVQ){tEPEpqYpgn = true;}
      if(JlpPcyYPLr == HNBylUiWoP){PGTxxzDfJt = true;}
      while(OlNrMlkGAQ == FlqcLPktHB){fsjpjOlEug = true;}
      while(BylFmeRKVQ == BylFmeRKVQ){GMjkyxXPAl = true;}
      while(HNBylUiWoP == HNBylUiWoP){OlXbPMsdpJ = true;}
      if(qKYRemxKKH == true){qKYRemxKKH = false;}
      if(RnGTyjSXgN == true){RnGTyjSXgN = false;}
      if(NGjHQBkPGq == true){NGjHQBkPGq = false;}
      if(CORjYpYTaz == true){CORjYpYTaz = false;}
      if(gHzNySGgzC == true){gHzNySGgzC = false;}
      if(BLpbCjaRAc == true){BLpbCjaRAc = false;}
      if(ChDSEDWWuH == true){ChDSEDWWuH = false;}
      if(LzwhfFHVJy == true){LzwhfFHVJy = false;}
      if(tEPEpqYpgn == true){tEPEpqYpgn = false;}
      if(PGTxxzDfJt == true){PGTxxzDfJt = false;}
      if(wjlrqCOHww == true){wjlrqCOHww = false;}
      if(cFICiyRycM == true){cFICiyRycM = false;}
      if(egoGrEeyjf == true){egoGrEeyjf = false;}
      if(CaMOBJRXNm == true){CaMOBJRXNm = false;}
      if(cQtkKKyROy == true){cQtkKKyROy = false;}
      if(gFCwOPufzl == true){gFCwOPufzl = false;}
      if(XPWPtBrsAY == true){XPWPtBrsAY = false;}
      if(fsjpjOlEug == true){fsjpjOlEug = false;}
      if(GMjkyxXPAl == true){GMjkyxXPAl = false;}
      if(OlXbPMsdpJ == true){OlXbPMsdpJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQKZMYXQXU
{ 
  void uQqXoKGNrx()
  { 
      bool ISVVWrqocK = false;
      bool FjKmFntWuo = false;
      bool CbKtIEHnjQ = false;
      bool MdrQrPkUnR = false;
      bool lNmAVULnXc = false;
      bool kTRgmgIbMS = false;
      bool jCFLybrsup = false;
      bool DZicCnnKXm = false;
      bool sSQHerMKdL = false;
      bool GIHVhjIaBt = false;
      bool cRshYLkndy = false;
      bool ryDYYRkxgG = false;
      bool OgPjitRNuS = false;
      bool fMIdKbZihT = false;
      bool GXfeSIFiwP = false;
      bool yKtuewBIyd = false;
      bool sXsLSeoYOx = false;
      bool rCPMzpAjRZ = false;
      bool oiQeTUSNzO = false;
      bool ZQjEaieTMm = false;
      string TzYiowjMGF;
      string dlfoSGzLGy;
      string jWuJIMZcyl;
      string RgRfrkyNgj;
      string iFYWpbERWT;
      string epOHjxEOab;
      string WGNUmxUAxg;
      string HkeWOdxXTf;
      string IHGdGaSKuu;
      string fjlEMcrEjs;
      string HDToMtLrrF;
      string zfutTOAiNL;
      string dJECBXyaJl;
      string lsnZYEnQRM;
      string PZSpuAnrjy;
      string bIpXOxzRnn;
      string ujiFSFqUVO;
      string ajRBuEqOGA;
      string iGpLKdDPKb;
      string FVbcQeqMWp;
      if(TzYiowjMGF == HDToMtLrrF){ISVVWrqocK = true;}
      else if(HDToMtLrrF == TzYiowjMGF){cRshYLkndy = true;}
      if(dlfoSGzLGy == zfutTOAiNL){FjKmFntWuo = true;}
      else if(zfutTOAiNL == dlfoSGzLGy){ryDYYRkxgG = true;}
      if(jWuJIMZcyl == dJECBXyaJl){CbKtIEHnjQ = true;}
      else if(dJECBXyaJl == jWuJIMZcyl){OgPjitRNuS = true;}
      if(RgRfrkyNgj == lsnZYEnQRM){MdrQrPkUnR = true;}
      else if(lsnZYEnQRM == RgRfrkyNgj){fMIdKbZihT = true;}
      if(iFYWpbERWT == PZSpuAnrjy){lNmAVULnXc = true;}
      else if(PZSpuAnrjy == iFYWpbERWT){GXfeSIFiwP = true;}
      if(epOHjxEOab == bIpXOxzRnn){kTRgmgIbMS = true;}
      else if(bIpXOxzRnn == epOHjxEOab){yKtuewBIyd = true;}
      if(WGNUmxUAxg == ujiFSFqUVO){jCFLybrsup = true;}
      else if(ujiFSFqUVO == WGNUmxUAxg){sXsLSeoYOx = true;}
      if(HkeWOdxXTf == ajRBuEqOGA){DZicCnnKXm = true;}
      if(IHGdGaSKuu == iGpLKdDPKb){sSQHerMKdL = true;}
      if(fjlEMcrEjs == FVbcQeqMWp){GIHVhjIaBt = true;}
      while(ajRBuEqOGA == HkeWOdxXTf){rCPMzpAjRZ = true;}
      while(iGpLKdDPKb == iGpLKdDPKb){oiQeTUSNzO = true;}
      while(FVbcQeqMWp == FVbcQeqMWp){ZQjEaieTMm = true;}
      if(ISVVWrqocK == true){ISVVWrqocK = false;}
      if(FjKmFntWuo == true){FjKmFntWuo = false;}
      if(CbKtIEHnjQ == true){CbKtIEHnjQ = false;}
      if(MdrQrPkUnR == true){MdrQrPkUnR = false;}
      if(lNmAVULnXc == true){lNmAVULnXc = false;}
      if(kTRgmgIbMS == true){kTRgmgIbMS = false;}
      if(jCFLybrsup == true){jCFLybrsup = false;}
      if(DZicCnnKXm == true){DZicCnnKXm = false;}
      if(sSQHerMKdL == true){sSQHerMKdL = false;}
      if(GIHVhjIaBt == true){GIHVhjIaBt = false;}
      if(cRshYLkndy == true){cRshYLkndy = false;}
      if(ryDYYRkxgG == true){ryDYYRkxgG = false;}
      if(OgPjitRNuS == true){OgPjitRNuS = false;}
      if(fMIdKbZihT == true){fMIdKbZihT = false;}
      if(GXfeSIFiwP == true){GXfeSIFiwP = false;}
      if(yKtuewBIyd == true){yKtuewBIyd = false;}
      if(sXsLSeoYOx == true){sXsLSeoYOx = false;}
      if(rCPMzpAjRZ == true){rCPMzpAjRZ = false;}
      if(oiQeTUSNzO == true){oiQeTUSNzO = false;}
      if(ZQjEaieTMm == true){ZQjEaieTMm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ODYGXZUEUN
{ 
  void HutqBYdDsJ()
  { 
      bool oPZuQAILtu = false;
      bool jCCGeyPRKQ = false;
      bool EbxSeBlHhI = false;
      bool NtkupGAkTL = false;
      bool JuLNqLsAaq = false;
      bool zPgFSMRGQP = false;
      bool NAclhoQGPX = false;
      bool xdxyHIPjaS = false;
      bool IlfpJxMfcd = false;
      bool osUExJRZfB = false;
      bool ulkDtUShyK = false;
      bool whfyHbTlbk = false;
      bool bkdliDJsAx = false;
      bool ppDYXVBcwn = false;
      bool edhRhGNWxV = false;
      bool pfxtYKHyTq = false;
      bool LYhATGdGak = false;
      bool ZppnFyDLDb = false;
      bool omudHKrIzM = false;
      bool NCJEbFwgxa = false;
      string SlJqfEhqgs;
      string prbjFpiAKt;
      string xEzXdPzKTL;
      string bTDiyUQZXh;
      string FPrUwKRJaS;
      string cwePFOmkMP;
      string EXXVQWnrlk;
      string YIcbngMdbT;
      string yoiBifnndj;
      string gfMHchrVEZ;
      string VYXptTSCaX;
      string BIJrROnVmk;
      string hzOBDruVzF;
      string npZByYRsHO;
      string MlNFhXWUoN;
      string tWiSrWKVlB;
      string YxDViKiHts;
      string xtOXXwlISe;
      string VagkLRGGJb;
      string OuHGoPhqWW;
      if(SlJqfEhqgs == VYXptTSCaX){oPZuQAILtu = true;}
      else if(VYXptTSCaX == SlJqfEhqgs){ulkDtUShyK = true;}
      if(prbjFpiAKt == BIJrROnVmk){jCCGeyPRKQ = true;}
      else if(BIJrROnVmk == prbjFpiAKt){whfyHbTlbk = true;}
      if(xEzXdPzKTL == hzOBDruVzF){EbxSeBlHhI = true;}
      else if(hzOBDruVzF == xEzXdPzKTL){bkdliDJsAx = true;}
      if(bTDiyUQZXh == npZByYRsHO){NtkupGAkTL = true;}
      else if(npZByYRsHO == bTDiyUQZXh){ppDYXVBcwn = true;}
      if(FPrUwKRJaS == MlNFhXWUoN){JuLNqLsAaq = true;}
      else if(MlNFhXWUoN == FPrUwKRJaS){edhRhGNWxV = true;}
      if(cwePFOmkMP == tWiSrWKVlB){zPgFSMRGQP = true;}
      else if(tWiSrWKVlB == cwePFOmkMP){pfxtYKHyTq = true;}
      if(EXXVQWnrlk == YxDViKiHts){NAclhoQGPX = true;}
      else if(YxDViKiHts == EXXVQWnrlk){LYhATGdGak = true;}
      if(YIcbngMdbT == xtOXXwlISe){xdxyHIPjaS = true;}
      if(yoiBifnndj == VagkLRGGJb){IlfpJxMfcd = true;}
      if(gfMHchrVEZ == OuHGoPhqWW){osUExJRZfB = true;}
      while(xtOXXwlISe == YIcbngMdbT){ZppnFyDLDb = true;}
      while(VagkLRGGJb == VagkLRGGJb){omudHKrIzM = true;}
      while(OuHGoPhqWW == OuHGoPhqWW){NCJEbFwgxa = true;}
      if(oPZuQAILtu == true){oPZuQAILtu = false;}
      if(jCCGeyPRKQ == true){jCCGeyPRKQ = false;}
      if(EbxSeBlHhI == true){EbxSeBlHhI = false;}
      if(NtkupGAkTL == true){NtkupGAkTL = false;}
      if(JuLNqLsAaq == true){JuLNqLsAaq = false;}
      if(zPgFSMRGQP == true){zPgFSMRGQP = false;}
      if(NAclhoQGPX == true){NAclhoQGPX = false;}
      if(xdxyHIPjaS == true){xdxyHIPjaS = false;}
      if(IlfpJxMfcd == true){IlfpJxMfcd = false;}
      if(osUExJRZfB == true){osUExJRZfB = false;}
      if(ulkDtUShyK == true){ulkDtUShyK = false;}
      if(whfyHbTlbk == true){whfyHbTlbk = false;}
      if(bkdliDJsAx == true){bkdliDJsAx = false;}
      if(ppDYXVBcwn == true){ppDYXVBcwn = false;}
      if(edhRhGNWxV == true){edhRhGNWxV = false;}
      if(pfxtYKHyTq == true){pfxtYKHyTq = false;}
      if(LYhATGdGak == true){LYhATGdGak = false;}
      if(ZppnFyDLDb == true){ZppnFyDLDb = false;}
      if(omudHKrIzM == true){omudHKrIzM = false;}
      if(NCJEbFwgxa == true){NCJEbFwgxa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKZMTQJSUG
{ 
  void BjkNDVDWlJ()
  { 
      bool WYteEwInxl = false;
      bool RyRtVCczqb = false;
      bool RbAZmmsxMc = false;
      bool uXoKUNMJVx = false;
      bool VnJLaBSNBQ = false;
      bool dQzlruXTqQ = false;
      bool DLbUpsJHYH = false;
      bool oSctFdRozk = false;
      bool UeuuyeYDRZ = false;
      bool orRFsKLoUg = false;
      bool rLnsaKmEfO = false;
      bool ciUFuYPfVL = false;
      bool TGozSxAWBt = false;
      bool RbTRsJpBTm = false;
      bool qUWDwFWLJU = false;
      bool ufSJNkVoad = false;
      bool KQDkwAPDMl = false;
      bool hNLhTzilDN = false;
      bool ZnMfzlIJEI = false;
      bool mBapcaQkGu = false;
      string hasDfOKzWw;
      string mPtoCjRrkC;
      string QQaGPMdlyI;
      string nVSkPcFrbJ;
      string RdqxNTioIy;
      string CpENBRAlnS;
      string kYAOHQwIZZ;
      string eYPbjlZdrw;
      string cnczFyRFjx;
      string bSEIYsdcow;
      string WaPiTcZbcO;
      string qWtqpwuAII;
      string zqYbxLTHCq;
      string IxnuYCXtfb;
      string YobUFFYMSb;
      string xcUgxfCnlI;
      string JRZkGtizSm;
      string XAUfjKODVq;
      string mGoatebGyr;
      string AjHWSGPpNK;
      if(hasDfOKzWw == WaPiTcZbcO){WYteEwInxl = true;}
      else if(WaPiTcZbcO == hasDfOKzWw){rLnsaKmEfO = true;}
      if(mPtoCjRrkC == qWtqpwuAII){RyRtVCczqb = true;}
      else if(qWtqpwuAII == mPtoCjRrkC){ciUFuYPfVL = true;}
      if(QQaGPMdlyI == zqYbxLTHCq){RbAZmmsxMc = true;}
      else if(zqYbxLTHCq == QQaGPMdlyI){TGozSxAWBt = true;}
      if(nVSkPcFrbJ == IxnuYCXtfb){uXoKUNMJVx = true;}
      else if(IxnuYCXtfb == nVSkPcFrbJ){RbTRsJpBTm = true;}
      if(RdqxNTioIy == YobUFFYMSb){VnJLaBSNBQ = true;}
      else if(YobUFFYMSb == RdqxNTioIy){qUWDwFWLJU = true;}
      if(CpENBRAlnS == xcUgxfCnlI){dQzlruXTqQ = true;}
      else if(xcUgxfCnlI == CpENBRAlnS){ufSJNkVoad = true;}
      if(kYAOHQwIZZ == JRZkGtizSm){DLbUpsJHYH = true;}
      else if(JRZkGtizSm == kYAOHQwIZZ){KQDkwAPDMl = true;}
      if(eYPbjlZdrw == XAUfjKODVq){oSctFdRozk = true;}
      if(cnczFyRFjx == mGoatebGyr){UeuuyeYDRZ = true;}
      if(bSEIYsdcow == AjHWSGPpNK){orRFsKLoUg = true;}
      while(XAUfjKODVq == eYPbjlZdrw){hNLhTzilDN = true;}
      while(mGoatebGyr == mGoatebGyr){ZnMfzlIJEI = true;}
      while(AjHWSGPpNK == AjHWSGPpNK){mBapcaQkGu = true;}
      if(WYteEwInxl == true){WYteEwInxl = false;}
      if(RyRtVCczqb == true){RyRtVCczqb = false;}
      if(RbAZmmsxMc == true){RbAZmmsxMc = false;}
      if(uXoKUNMJVx == true){uXoKUNMJVx = false;}
      if(VnJLaBSNBQ == true){VnJLaBSNBQ = false;}
      if(dQzlruXTqQ == true){dQzlruXTqQ = false;}
      if(DLbUpsJHYH == true){DLbUpsJHYH = false;}
      if(oSctFdRozk == true){oSctFdRozk = false;}
      if(UeuuyeYDRZ == true){UeuuyeYDRZ = false;}
      if(orRFsKLoUg == true){orRFsKLoUg = false;}
      if(rLnsaKmEfO == true){rLnsaKmEfO = false;}
      if(ciUFuYPfVL == true){ciUFuYPfVL = false;}
      if(TGozSxAWBt == true){TGozSxAWBt = false;}
      if(RbTRsJpBTm == true){RbTRsJpBTm = false;}
      if(qUWDwFWLJU == true){qUWDwFWLJU = false;}
      if(ufSJNkVoad == true){ufSJNkVoad = false;}
      if(KQDkwAPDMl == true){KQDkwAPDMl = false;}
      if(hNLhTzilDN == true){hNLhTzilDN = false;}
      if(ZnMfzlIJEI == true){ZnMfzlIJEI = false;}
      if(mBapcaQkGu == true){mBapcaQkGu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHQORLTIVH
{ 
  void PrpypBSruy()
  { 
      bool bhlIVyoEiV = false;
      bool CfEiEkVNLa = false;
      bool dLmMaaNWhh = false;
      bool LDbkIOgNsA = false;
      bool CDzCTQttWM = false;
      bool IutXgQuZht = false;
      bool jRWBKzESao = false;
      bool EITKXZLjrJ = false;
      bool gTAUYPJEDr = false;
      bool THeyPkfyrU = false;
      bool LaTgIAaiAH = false;
      bool ELgXNQQCbu = false;
      bool pAPhVwcVul = false;
      bool sNrWxFASLY = false;
      bool oZEwmIZGjz = false;
      bool TdVxeLLkLM = false;
      bool WEnNNqSKZI = false;
      bool QxqDFPuStN = false;
      bool VVluSPruql = false;
      bool tOHzBjkphw = false;
      string TWblboNgIX;
      string TbQGcYHoUP;
      string PVomxCTzfY;
      string WplKdbKcfp;
      string tRFfabCXaI;
      string YERVuyhonZ;
      string UNBjBdpFbA;
      string NdJeVxQJMV;
      string zwXXzRXQOf;
      string tVnGUfQVew;
      string lwwZtuumAy;
      string hYbSZYocji;
      string FZpuGqoCKo;
      string ftdPiCzxdE;
      string WkQQyVtVfu;
      string pnkuqMGBTC;
      string FrbKSmtLiW;
      string ZrzfMUJZwj;
      string xTWOzrIiYW;
      string wydbydIFyL;
      if(TWblboNgIX == lwwZtuumAy){bhlIVyoEiV = true;}
      else if(lwwZtuumAy == TWblboNgIX){LaTgIAaiAH = true;}
      if(TbQGcYHoUP == hYbSZYocji){CfEiEkVNLa = true;}
      else if(hYbSZYocji == TbQGcYHoUP){ELgXNQQCbu = true;}
      if(PVomxCTzfY == FZpuGqoCKo){dLmMaaNWhh = true;}
      else if(FZpuGqoCKo == PVomxCTzfY){pAPhVwcVul = true;}
      if(WplKdbKcfp == ftdPiCzxdE){LDbkIOgNsA = true;}
      else if(ftdPiCzxdE == WplKdbKcfp){sNrWxFASLY = true;}
      if(tRFfabCXaI == WkQQyVtVfu){CDzCTQttWM = true;}
      else if(WkQQyVtVfu == tRFfabCXaI){oZEwmIZGjz = true;}
      if(YERVuyhonZ == pnkuqMGBTC){IutXgQuZht = true;}
      else if(pnkuqMGBTC == YERVuyhonZ){TdVxeLLkLM = true;}
      if(UNBjBdpFbA == FrbKSmtLiW){jRWBKzESao = true;}
      else if(FrbKSmtLiW == UNBjBdpFbA){WEnNNqSKZI = true;}
      if(NdJeVxQJMV == ZrzfMUJZwj){EITKXZLjrJ = true;}
      if(zwXXzRXQOf == xTWOzrIiYW){gTAUYPJEDr = true;}
      if(tVnGUfQVew == wydbydIFyL){THeyPkfyrU = true;}
      while(ZrzfMUJZwj == NdJeVxQJMV){QxqDFPuStN = true;}
      while(xTWOzrIiYW == xTWOzrIiYW){VVluSPruql = true;}
      while(wydbydIFyL == wydbydIFyL){tOHzBjkphw = true;}
      if(bhlIVyoEiV == true){bhlIVyoEiV = false;}
      if(CfEiEkVNLa == true){CfEiEkVNLa = false;}
      if(dLmMaaNWhh == true){dLmMaaNWhh = false;}
      if(LDbkIOgNsA == true){LDbkIOgNsA = false;}
      if(CDzCTQttWM == true){CDzCTQttWM = false;}
      if(IutXgQuZht == true){IutXgQuZht = false;}
      if(jRWBKzESao == true){jRWBKzESao = false;}
      if(EITKXZLjrJ == true){EITKXZLjrJ = false;}
      if(gTAUYPJEDr == true){gTAUYPJEDr = false;}
      if(THeyPkfyrU == true){THeyPkfyrU = false;}
      if(LaTgIAaiAH == true){LaTgIAaiAH = false;}
      if(ELgXNQQCbu == true){ELgXNQQCbu = false;}
      if(pAPhVwcVul == true){pAPhVwcVul = false;}
      if(sNrWxFASLY == true){sNrWxFASLY = false;}
      if(oZEwmIZGjz == true){oZEwmIZGjz = false;}
      if(TdVxeLLkLM == true){TdVxeLLkLM = false;}
      if(WEnNNqSKZI == true){WEnNNqSKZI = false;}
      if(QxqDFPuStN == true){QxqDFPuStN = false;}
      if(VVluSPruql == true){VVluSPruql = false;}
      if(tOHzBjkphw == true){tOHzBjkphw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZATCYLADW
{ 
  void qjJCDexurM()
  { 
      bool lAXLuYlWsM = false;
      bool FhLUdIDzmq = false;
      bool wCGjoabcYr = false;
      bool JRoEBjeipi = false;
      bool XxjUPtIjUh = false;
      bool gLCDRjsmWT = false;
      bool wIxBCnrGTs = false;
      bool dUJESySkUt = false;
      bool SrIpKyOlmQ = false;
      bool qqMWlOzhRa = false;
      bool CBPaEMByjS = false;
      bool RISbAEAGpE = false;
      bool YFSCClImRD = false;
      bool zjSsrQbhly = false;
      bool wQBUzhYjVg = false;
      bool OrrNCwhMXR = false;
      bool DOfgThoYji = false;
      bool cRUqHIEyDU = false;
      bool NXQkoGrFqw = false;
      bool iOKUthjUBQ = false;
      string yGFyHRZAmI;
      string FHgcWaiKLt;
      string bTnnazyzHd;
      string peVbeRJnxB;
      string cxLCYoEYUE;
      string ljWaEeRRXH;
      string SZrISZlExF;
      string QuNKRdIkOk;
      string uYdCrFItXA;
      string zqPoiCECjz;
      string DzaPnpVMJa;
      string VgDlMswpQM;
      string RqgxGYfXaO;
      string YFAPguyONB;
      string iwjwdSnccp;
      string GOlWhMSdIO;
      string KykuBQfnFR;
      string ugbPcUGjSn;
      string kCtkHKTdhU;
      string bTFzpkLotN;
      if(yGFyHRZAmI == DzaPnpVMJa){lAXLuYlWsM = true;}
      else if(DzaPnpVMJa == yGFyHRZAmI){CBPaEMByjS = true;}
      if(FHgcWaiKLt == VgDlMswpQM){FhLUdIDzmq = true;}
      else if(VgDlMswpQM == FHgcWaiKLt){RISbAEAGpE = true;}
      if(bTnnazyzHd == RqgxGYfXaO){wCGjoabcYr = true;}
      else if(RqgxGYfXaO == bTnnazyzHd){YFSCClImRD = true;}
      if(peVbeRJnxB == YFAPguyONB){JRoEBjeipi = true;}
      else if(YFAPguyONB == peVbeRJnxB){zjSsrQbhly = true;}
      if(cxLCYoEYUE == iwjwdSnccp){XxjUPtIjUh = true;}
      else if(iwjwdSnccp == cxLCYoEYUE){wQBUzhYjVg = true;}
      if(ljWaEeRRXH == GOlWhMSdIO){gLCDRjsmWT = true;}
      else if(GOlWhMSdIO == ljWaEeRRXH){OrrNCwhMXR = true;}
      if(SZrISZlExF == KykuBQfnFR){wIxBCnrGTs = true;}
      else if(KykuBQfnFR == SZrISZlExF){DOfgThoYji = true;}
      if(QuNKRdIkOk == ugbPcUGjSn){dUJESySkUt = true;}
      if(uYdCrFItXA == kCtkHKTdhU){SrIpKyOlmQ = true;}
      if(zqPoiCECjz == bTFzpkLotN){qqMWlOzhRa = true;}
      while(ugbPcUGjSn == QuNKRdIkOk){cRUqHIEyDU = true;}
      while(kCtkHKTdhU == kCtkHKTdhU){NXQkoGrFqw = true;}
      while(bTFzpkLotN == bTFzpkLotN){iOKUthjUBQ = true;}
      if(lAXLuYlWsM == true){lAXLuYlWsM = false;}
      if(FhLUdIDzmq == true){FhLUdIDzmq = false;}
      if(wCGjoabcYr == true){wCGjoabcYr = false;}
      if(JRoEBjeipi == true){JRoEBjeipi = false;}
      if(XxjUPtIjUh == true){XxjUPtIjUh = false;}
      if(gLCDRjsmWT == true){gLCDRjsmWT = false;}
      if(wIxBCnrGTs == true){wIxBCnrGTs = false;}
      if(dUJESySkUt == true){dUJESySkUt = false;}
      if(SrIpKyOlmQ == true){SrIpKyOlmQ = false;}
      if(qqMWlOzhRa == true){qqMWlOzhRa = false;}
      if(CBPaEMByjS == true){CBPaEMByjS = false;}
      if(RISbAEAGpE == true){RISbAEAGpE = false;}
      if(YFSCClImRD == true){YFSCClImRD = false;}
      if(zjSsrQbhly == true){zjSsrQbhly = false;}
      if(wQBUzhYjVg == true){wQBUzhYjVg = false;}
      if(OrrNCwhMXR == true){OrrNCwhMXR = false;}
      if(DOfgThoYji == true){DOfgThoYji = false;}
      if(cRUqHIEyDU == true){cRUqHIEyDU = false;}
      if(NXQkoGrFqw == true){NXQkoGrFqw = false;}
      if(iOKUthjUBQ == true){iOKUthjUBQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PDRZNKCLPG
{ 
  void TToGxxIsin()
  { 
      bool ebkTLRgCIE = false;
      bool arhuTgqtuZ = false;
      bool hVFlRQSLES = false;
      bool WggoYKjkun = false;
      bool SFkquCZjUq = false;
      bool AINnfJVzBu = false;
      bool zUxpgtKsWI = false;
      bool xGyGHbjOpP = false;
      bool phqMROTsJP = false;
      bool okiAnxIuJB = false;
      bool qgNLtsJGgE = false;
      bool YGIlFQdkXR = false;
      bool aRiHTLWySJ = false;
      bool ToEnXIUeSX = false;
      bool FMLFphbxuX = false;
      bool TWWqaZxGrh = false;
      bool WLnXjjCUNw = false;
      bool uyRAMNFdRk = false;
      bool jYCtowSMNx = false;
      bool KOmkBsYmUF = false;
      string kYmBKXLTCd;
      string eDrMFkxjMV;
      string ypQbAKQCHK;
      string KxWLagQrZM;
      string EnXkqwEdWp;
      string VpwoQtILBA;
      string GJMqSgfflX;
      string TFJzRJSejD;
      string GleQoUBguf;
      string YEqZFubfRK;
      string PXrzVPfwXG;
      string bcaxtTduBy;
      string fzjGzPOjsW;
      string glNZnhtfuZ;
      string nFJnDucsfl;
      string QgdSdQmkzG;
      string BwCBZpPBIL;
      string ZyAbKZouCE;
      string lUEHFzHtuW;
      string tIfnXrCION;
      if(kYmBKXLTCd == PXrzVPfwXG){ebkTLRgCIE = true;}
      else if(PXrzVPfwXG == kYmBKXLTCd){qgNLtsJGgE = true;}
      if(eDrMFkxjMV == bcaxtTduBy){arhuTgqtuZ = true;}
      else if(bcaxtTduBy == eDrMFkxjMV){YGIlFQdkXR = true;}
      if(ypQbAKQCHK == fzjGzPOjsW){hVFlRQSLES = true;}
      else if(fzjGzPOjsW == ypQbAKQCHK){aRiHTLWySJ = true;}
      if(KxWLagQrZM == glNZnhtfuZ){WggoYKjkun = true;}
      else if(glNZnhtfuZ == KxWLagQrZM){ToEnXIUeSX = true;}
      if(EnXkqwEdWp == nFJnDucsfl){SFkquCZjUq = true;}
      else if(nFJnDucsfl == EnXkqwEdWp){FMLFphbxuX = true;}
      if(VpwoQtILBA == QgdSdQmkzG){AINnfJVzBu = true;}
      else if(QgdSdQmkzG == VpwoQtILBA){TWWqaZxGrh = true;}
      if(GJMqSgfflX == BwCBZpPBIL){zUxpgtKsWI = true;}
      else if(BwCBZpPBIL == GJMqSgfflX){WLnXjjCUNw = true;}
      if(TFJzRJSejD == ZyAbKZouCE){xGyGHbjOpP = true;}
      if(GleQoUBguf == lUEHFzHtuW){phqMROTsJP = true;}
      if(YEqZFubfRK == tIfnXrCION){okiAnxIuJB = true;}
      while(ZyAbKZouCE == TFJzRJSejD){uyRAMNFdRk = true;}
      while(lUEHFzHtuW == lUEHFzHtuW){jYCtowSMNx = true;}
      while(tIfnXrCION == tIfnXrCION){KOmkBsYmUF = true;}
      if(ebkTLRgCIE == true){ebkTLRgCIE = false;}
      if(arhuTgqtuZ == true){arhuTgqtuZ = false;}
      if(hVFlRQSLES == true){hVFlRQSLES = false;}
      if(WggoYKjkun == true){WggoYKjkun = false;}
      if(SFkquCZjUq == true){SFkquCZjUq = false;}
      if(AINnfJVzBu == true){AINnfJVzBu = false;}
      if(zUxpgtKsWI == true){zUxpgtKsWI = false;}
      if(xGyGHbjOpP == true){xGyGHbjOpP = false;}
      if(phqMROTsJP == true){phqMROTsJP = false;}
      if(okiAnxIuJB == true){okiAnxIuJB = false;}
      if(qgNLtsJGgE == true){qgNLtsJGgE = false;}
      if(YGIlFQdkXR == true){YGIlFQdkXR = false;}
      if(aRiHTLWySJ == true){aRiHTLWySJ = false;}
      if(ToEnXIUeSX == true){ToEnXIUeSX = false;}
      if(FMLFphbxuX == true){FMLFphbxuX = false;}
      if(TWWqaZxGrh == true){TWWqaZxGrh = false;}
      if(WLnXjjCUNw == true){WLnXjjCUNw = false;}
      if(uyRAMNFdRk == true){uyRAMNFdRk = false;}
      if(jYCtowSMNx == true){jYCtowSMNx = false;}
      if(KOmkBsYmUF == true){KOmkBsYmUF = false;}
    } 
}; 
